/* Copyright 2016-2018 The MathWorks, Inc. */

#include <SLES/OpenSLES_Android.h>
#include "audio_player.hpp"
#include "audio_engine.h"

/*
 * Called by OpenSL SimpleBufferQueue for every audio buffer played
 * directly pass thru to our handler.
 * The regularity of this callback from openSL/Android System affects
 * playback continuity. If it does not callback in the regular time
 * slot, you are under big pressure for audio processing[here we do
 * not do any filtering/mixing]. Callback from fast audio path are
 * much more regular than other audio paths by my observation. If it
 * very regular, you could buffer much less audio samples between
 * recorder and player, hence lower latency.
 */

void bqPlayerCallback(SLAndroidSimpleBufferQueueItf bq, void *ctx) {
    (static_cast<AudioPlayer *>(ctx))->ProcessSLCallback(bq);
}

void AudioPlayer::ProcessSLCallback(SLAndroidSimpleBufferQueueItf bq) {

    std::lock_guard<std::mutex> lock(stopMutex_);

    // retrieve the finished device buf and put onto the free queue
    // so recorder could re-use it
    sample_buf *buf;
    if (!devShadowQueue_->front(&buf)) {
        /*
         * This should not happen: we got a callback,
         * but we have no buffer in deviceShadowedQueue
         * we lost buffers this way...(ERROR)
         */
        if (callback_) {
            uint32_t count;
            callback_(ctx_, ENGINE_SERVICE_MSG_RETRIEVE_DUMP_BUFS, &count);
        }
        return;
    }
    devShadowQueue_->pop();

    if (buf != &silentBuf_) {
        buf->size_ = 0;
        freeQueue_->push(buf);

        if (!playQueue_->front(&buf)) {
            playerNeedToStart = true;
            return;
        }

        devShadowQueue_->push(buf);
        (*bq)->Enqueue(bq, buf->buf_, buf->size_);
        playQueue_->pop();
        return;
    }

    if (playQueue_->size() < PLAY_KICKSTART_BUFFER_COUNT) {
        (*bq)->Enqueue(bq, buf->buf_, buf->size_);
        devShadowQueue_->push(&silentBuf_);
        return;
    }

    assert(PLAY_KICKSTART_BUFFER_COUNT <=
           (DEVICE_SHADOW_BUFFER_QUEUE_LEN - devShadowQueue_->size()));
    for (int32_t idx = 0; idx < PLAY_KICKSTART_BUFFER_COUNT; idx++) {
        playQueue_->front(&buf);
        playQueue_->pop();
        devShadowQueue_->push(buf);
        (*bq)->Enqueue(bq, buf->buf_, buf->size_);
    }

}

AudioPlayer::AudioPlayer(SampleFormat *sampleFormat, SLEngineItf slEngine) :
        freeQueue_(nullptr), playQueue_(nullptr), devShadowQueue_(nullptr),
        callback_(nullptr) {
    SLresult result;
    assert(sampleFormat);

    result = (*slEngine)->CreateOutputMix(slEngine, &outputMixObjectItf_,
                                          0, NULL, NULL);
    SLASSERT(result);

    // realize the output mix
    result = (*outputMixObjectItf_)->Realize(outputMixObjectItf_, SL_BOOLEAN_FALSE);
    SLASSERT(result);

    // configure audio source
    SLDataLocator_AndroidSimpleBufferQueue loc_bufq = {
            SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE,
            DEVICE_SHADOW_BUFFER_QUEUE_LEN};
    SLDataFormat_PCM format_pcm;
    format_pcm.formatType = SL_DATAFORMAT_PCM;
    if (sampleFormat->channels_ <= 1) {
        format_pcm.numChannels = 1;
        format_pcm.channelMask = SL_SPEAKER_FRONT_CENTER;
    } else {
        format_pcm.numChannels = 2;
        format_pcm.channelMask = SL_SPEAKER_FRONT_LEFT | SL_SPEAKER_FRONT_RIGHT;
    }
    format_pcm.samplesPerSec = sampleFormat->sampleRate_;
    format_pcm.bitsPerSample = sampleFormat->pcmFormat_;
    format_pcm.containerSize = sampleFormat->pcmFormat_;
    format_pcm.endianness = SL_BYTEORDER_LITTLEENDIAN;
    SLDataSource audioSrc = {&loc_bufq, &format_pcm};

    // configure audio sink
    SLDataLocator_OutputMix loc_outmix = {SL_DATALOCATOR_OUTPUTMIX, outputMixObjectItf_};
    SLDataSink audioSnk = {&loc_outmix, NULL};
    /*
     * create fast path audio player: SL_IID_BUFFERQUEUE and SL_IID_VOLUME interfaces ok,
     * NO others!
     */
    SLInterfaceID ids[2] = {SL_IID_BUFFERQUEUE, SL_IID_VOLUME};
    SLboolean req[2] = {SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE};
    result = (*slEngine)->CreateAudioPlayer(slEngine, &playerObjectItf_, &audioSrc, &audioSnk,
                                            sizeof(ids) / sizeof(ids[0]), ids, req);
    SLASSERT(result);

    // realize the player
    result = (*playerObjectItf_)->Realize(playerObjectItf_, SL_BOOLEAN_FALSE);
    SLASSERT(result);

    // get the play interface
    result = (*playerObjectItf_)->GetInterface(playerObjectItf_, SL_IID_PLAY, &playItf_);
    SLASSERT(result);

    // get the buffer queue interface
    result = (*playerObjectItf_)->GetInterface(playerObjectItf_, SL_IID_BUFFERQUEUE,
                                               &playBufferQueueItf_);
    SLASSERT(result);

    // register callback on the buffer queue
    result = (*playBufferQueueItf_)->RegisterCallback(playBufferQueueItf_, bqPlayerCallback, this);
    SLASSERT(result);

    result = (*playItf_)->SetPlayState(playItf_, SL_PLAYSTATE_STOPPED);
    SLASSERT(result);

    // create an empty queue to track deviceQueue
    devShadowQueue_ = new AudioQueue(DEVICE_SHADOW_BUFFER_QUEUE_LEN);
    assert(devShadowQueue_);

    silentBuf_.cap_ = (format_pcm.containerSize >> 3) *
                      format_pcm.numChannels * sampleFormat->framesPerBuf_;
    silentBuf_.buf_ = new uint8_t[silentBuf_.cap_];
    memset(silentBuf_.buf_, 0, silentBuf_.cap_);
    silentBuf_.size_ = silentBuf_.cap_;

#ifdef  ENABLE_LOG
    std::string name = "play";
    logFile_ = new AndroidLog(name);
#endif
}

AudioPlayer::~AudioPlayer() {

    std::lock_guard<std::mutex> lock(stopMutex_);

    // destroy buffer queue audio player object, and invalidate all associated interfaces
    if (playerObjectItf_ != NULL) {
        (*playerObjectItf_)->Destroy(playerObjectItf_);
    }
    // Consume all non-completed audio buffers
    sample_buf *buf = NULL;
    while (devShadowQueue_->front(&buf)) {
        buf->size_ = 0;
        devShadowQueue_->pop();
        freeQueue_->push(buf);
    }
    delete devShadowQueue_;

    while (playQueue_->front(&buf)) {
        buf->size_ = 0;
        playQueue_->pop();
        freeQueue_->push(buf);
    }

    // destroy output mix object, and invalidate all associated interfaces
    if (outputMixObjectItf_) {
        (*outputMixObjectItf_)->Destroy(outputMixObjectItf_);
    }

    delete[] silentBuf_.buf_;
}

void AudioPlayer::SetBufQueue(AudioQueue *playQ, AudioQueue *freeQ) {
    playQueue_ = playQ;
    freeQueue_ = freeQ;
}

SLresult AudioPlayer::Start(void) {
    SLuint32 state;
    SLresult result = (*playItf_)->GetPlayState(playItf_, &state);
    if (result != SL_RESULT_SUCCESS) {
        return SL_BOOLEAN_FALSE;
    }
    if (state == SL_PLAYSTATE_PLAYING) {
        return SL_BOOLEAN_TRUE;
    }

    result = (*playItf_)->SetPlayState(playItf_, SL_PLAYSTATE_STOPPED);
    SLASSERT(result);

    result = (*playBufferQueueItf_)->Enqueue(playBufferQueueItf_,
                                             silentBuf_.buf_,
                                             silentBuf_.size_);
    SLASSERT(result);
    devShadowQueue_->push(&silentBuf_);

    result = (*playItf_)->SetPlayState(playItf_, SL_PLAYSTATE_PLAYING);
    SLASSERT(result);
    playerNeedToStart = false;
    return SL_BOOLEAN_TRUE;
}

void AudioPlayer::Stop(void) {
    SLuint32 state;

    SLresult result = (*playItf_)->GetPlayState(playItf_, &state);
    SLASSERT(result);

    if (state == SL_PLAYSTATE_STOPPED)
        return;

    std::lock_guard<std::mutex> lock(stopMutex_);

    result = (*playItf_)->SetPlayState(playItf_, SL_PLAYSTATE_STOPPED);
    SLASSERT(result);
    (*playBufferQueueItf_)->Clear(playBufferQueueItf_);

    // Consume all non-completed audio buffers
    sample_buf *buf = NULL;
    while (devShadowQueue_->front(&buf)) {
        buf->size_ = 0;
        devShadowQueue_->pop();
        freeQueue_->push(buf);
    }
    while (playQueue_->front(&buf)) {
        buf->size_ = 0;
        playQueue_->pop();
        freeQueue_->push(buf);
    }
}

void AudioPlayer::PlayAudioBuffers(int32_t count) {
    if (!count) {
        return;
    }

    while (count--) {
        std::lock_guard<std::mutex> lock(stopMutex_);
        sample_buf *buf = NULL;
        if (!playQueue_->front(&buf)) {
            uint32_t totalBufCount;
            callback_(ctx_, ENGINE_SERVICE_MSG_RETRIEVE_DUMP_BUFS,
                      &totalBufCount);
            LOGE("====Run out of buffers in %s @(count = %d), totalBuf =%d",
                 __FUNCTION__, count, totalBufCount);
            break;
        }
        if (!devShadowQueue_->push(buf)) {
            LOGW("@%s PlayerBufferQueue is full!!!", __FUNCTION__);
            break;  // PlayerBufferQueue is full!!!
        }

        SLresult result = (*playBufferQueueItf_)->Enqueue(playBufferQueueItf_,
                                                          buf->buf_, buf->size_);
        if (result != SL_RESULT_SUCCESS) {
            LOGE("%s Error @( %p, %d ), result = %d", __FUNCTION__,
                 (void *) buf->buf_, buf->size_, result);

            devShadowQueue_->front(&buf);
            devShadowQueue_->pop();
            freeQueue_->push(buf);
            if (callback_) {
                uint32_t totalBufCount;
                callback_(ctx_, ENGINE_SERVICE_MSG_RETRIEVE_DUMP_BUFS,
                          &totalBufCount);
            }
            break;
        }
        playQueue_->pop();   // really pop out the buffer
    }
}

void AudioPlayer::RegisterCallback(ENGINE_CALLBACK cb, void *ctx) {
    callback_ = cb;
    ctx_ = ctx;
}

uint32_t AudioPlayer::dbgGetDevBufCount(void) {
    return (devShadowQueue_->size());
}

void AudioPlayer::enqueueStepInput(int16_t *inData, uint16_t frameCount, uint16_t lastFrameSize) {
    uint8_t *data = (uint8_t *) inData;
    sample_buf *buf = NULL;
    while (frameCount--) {
        std::lock_guard<std::mutex> lock(stopMutex_);
        if (!freeQueue_->front(&buf)) {
            LOGE("@%s: ***No free buffer***", __FUNCTION__);
            playerNeedToStart = true;
            break;
        }
        freeQueue_->pop();
        uint16_t bufSize = frameCount ? buf->cap_ : lastFrameSize ? lastFrameSize : buf->cap_;

        memcpy(buf->buf_, data, bufSize);
        buf->size_ = bufSize;
        data += bufSize;

        if (!playQueue_->push(buf)) {
            LOGE("@%s: Can't push to play queue.", __FUNCTION__);
            playerNeedToStart = true;
            break;
        }
    }

    //finally play it!!!
    if (playerNeedToStart) {
        playerNeedToStart = false;
        PlayAudioBuffers(PLAY_KICKSTART_BUFFER_COUNT);
    }
}
