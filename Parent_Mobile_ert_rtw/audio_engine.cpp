/* Copyright 2016-2018 The MathWorks, Inc. */
#include <sys/types.h>
#include <SLES/OpenSLES.h>
#include "audio_engine.h"
#include "buf_manager.hpp"

#ifdef DRIVER_ANDROID_AUDIOPLAYBACK
#include "audio_player.hpp"
#endif

#ifdef DRIVER_ANDROID_AUDIOCAPTURE
#include "audio_recorder.h"
#endif

struct AudioEngine {
    SLmilliHertz fastPathSampleRate_;
    uint32_t fastPathFramesPerBuf_;
    SLmilliHertz usrRqstdSampleRate_;
    uint32_t usrRqstdFrameSize_;

    uint16_t sampleChannels_;
    uint16_t bitsPerSample_;

    SLObjectItf slEngineObj_;
    SLEngineItf slEngineItf_;

#ifdef DRIVER_ANDROID_AUDIOPLAYBACK
    AudioPlayer *player_;
    AudioQueue *freePlayBufQueue_;    //Owner of the queue
    AudioQueue *playBufQueue_;     //Owner of the queue
    sample_buf *playerBufs_;
#endif
#ifdef DRIVER_ANDROID_AUDIOCAPTURE
    AudioRecorder *recorder_;
    AudioQueue *freeRecBufQueue_;    //Owner of the queue
    AudioQueue *recBufQueue_;     //Owner of the queue
    sample_buf *recorderBufs_;
#endif
    uint32_t bufCount_;
    uint32_t bufSizeInBytes_;
    uint32_t usrFramesByteCount;
};

static AudioEngine engine;
static int isEngineCreated = 0;

extern "C"
void createSLEngine(int sampleRate, int framesPerBuf, uint32_t dataSourceSampleRate,
                    uint16_t frameSize) {
    SLresult result;
    if (isEngineCreated)
        return;

    memset(&engine, 0, sizeof(engine));

    LOGD("@%s native: sample rate = %d, fpb=%d, and data source sample rate=%d, framesize=%d",
         __FUNCTION__, sampleRate, framesPerBuf, dataSourceSampleRate, frameSize);

    engine.fastPathSampleRate_ = static_cast<SLmilliHertz>(sampleRate) * 1000;
    uint32_t fpfpb = static_cast<uint32_t>(framesPerBuf);
    engine.fastPathFramesPerBuf_ = fpfpb<frameSize?fpfpb:frameSize; //static_cast<uint32_t>(framesPerBuf);
    engine.sampleChannels_ = AUDIO_SAMPLE_CHANNELS;
    engine.bitsPerSample_ = SL_PCMSAMPLEFORMAT_FIXED_16;
    engine.usrRqstdSampleRate_ = dataSourceSampleRate;
    engine.usrRqstdFrameSize_ = frameSize;

    result = slCreateEngine(&engine.slEngineObj_, 0, NULL, 0, NULL, NULL);
    SLASSERT(result);

    result = (*engine.slEngineObj_)->Realize(engine.slEngineObj_, SL_BOOLEAN_FALSE);
    SLASSERT(result);

    result = (*engine.slEngineObj_)->GetInterface(engine.slEngineObj_, SL_IID_ENGINE,
                                                  &engine.slEngineItf_);
    SLASSERT(result);

    // compute the User requested audio buffer size in bytes:
    uint32_t byteCount = frameSize * engine.sampleChannels_
                         * engine.bitsPerSample_;
    engine.usrFramesByteCount = (byteCount + 7) >> 3;               // bits --> byte

    // compute the RECOMMENDED fast audio buffer size:
    uint32_t bufSize = engine.fastPathFramesPerBuf_ * engine.sampleChannels_
                       * engine.bitsPerSample_;
    bufSize = (bufSize + 7) >> 3;            // bits --> byte
    engine.bufSizeInBytes_ = bufSize;
    engine.bufCount_ = BUF_COUNT;
#ifdef DRIVER_ANDROID_AUDIOPLAYBACK
    engine.playerBufs_ = allocateSampleBufs(engine.bufCount_, bufSize);
    assert(engine.playerBufs_);

    engine.freePlayBufQueue_ = new AudioQueue(engine.bufCount_);
    engine.playBufQueue_ = new AudioQueue(engine.bufCount_);
    assert(engine.freePlayBufQueue_ && engine.playBufQueue_);
    for (uint32_t i = 0; i < engine.bufCount_; i++) {
        engine.freePlayBufQueue_->push(&engine.playerBufs_[i]);
    }
#endif
#ifdef DRIVER_ANDROID_AUDIOCAPTURE
    engine.freeRecBufQueue_ = new AudioQueue(engine.bufCount_);
    engine.recBufQueue_ = new AudioQueue(engine.bufCount_);
    assert(engine.freeRecBufQueue_ && engine.recBufQueue_ );
    engine.recorderBufs_ = allocateSampleBufs(engine.bufCount_, bufSize);
    assert(engine.recorderBufs_);
    for (uint32_t i = 0; i < engine.bufCount_; i++) {
        engine.freeRecBufQueue_->push(&engine.recorderBufs_[i]);
    }
#endif
    isEngineCreated = 1;
}

extern "C"
void deleteSLEngine() {
    if (!isEngineCreated)
        return;
#if defined(DRIVER_ANDROID_AUDIOPLAYBACK) && defined(DRIVER_ANDROID_AUDIOCAPTURE)
    if (engine.recorder_ == nullptr && engine.player_ == nullptr && engine.slEngineObj_ != NULL) {
#elif DRIVER_ANDROID_AUDIOPLAYBACK
    if (engine.player_ == nullptr && engine.slEngineObj_ != NULL) {
#elif DRIVER_ANDROID_AUDIOCAPTURE
    if (engine.recorder_ == nullptr && engine.slEngineObj_ != NULL) {
#endif
#ifdef DRIVER_ANDROID_AUDIOPLAYBACK
        delete engine.playBufQueue_;
        delete engine.freePlayBufQueue_;
        releaseSampleBufs(engine.playerBufs_, engine.bufCount_);
#endif
#ifdef DRIVER_ANDROID_AUDIOCAPTURE
        delete engine.recBufQueue_;
        delete engine.freeRecBufQueue_;
        releaseSampleBufs(engine.recorderBufs_, engine.bufCount_);
#endif
        if (engine.slEngineObj_ != NULL) {
            (*engine.slEngineObj_)->Destroy(engine.slEngineObj_);
            engine.slEngineObj_ = NULL;
            engine.slEngineItf_ = NULL;
        }
        isEngineCreated = 0;
    }
}

extern "C"
uint32_t dbgEngineGetBufCount(void) {
#ifdef DRIVER_ANDROID_AUDIOPLAYBACK
    uint32_t countPlay = engine.player_->dbgGetDevBufCount();
    countPlay += engine.freePlayBufQueue_->size();
    countPlay += engine.playBufQueue_->size();

    LOGW("Buf Distributions: DevPlayerQ=%d, FreePlayQ=%d, PlayBufQ=%d",
         engine.player_->dbgGetDevBufCount(),
         engine.freePlayBufQueue_->size(),
         engine.playBufQueue_->size());
    if (countPlay != engine.bufCount_) {
        LOGE("==Play==Lost Buffs among the queue(supposed = %d, found = %d)",
             BUF_COUNT, countPlay);
    }
#endif
#ifdef DRIVER_ANDROID_AUDIOCAPTURE
    uint32_t countRec = engine.recorder_->dbgGetDevBufCount();
    countRec += engine.freeRecBufQueue_->size();
    countRec += engine.recBufQueue_->size();
    LOGW("Buf Distributions: DevRecorderQ=%d, FreeRecQ=%d, RecQ=%d",
         engine.recorder_->dbgGetDevBufCount(),
         engine.freeRecBufQueue_->size(),
        engine.recBufQueue_->size());
    if (countRec != engine.bufCount_) {
        LOGE("==Rec==Lost Buffs among the queue(supposed = %d, found = %d)",
             BUF_COUNT, countRec);
    }
#endif
    return 1;
}

/*
 * simple message passing for player/recorder to communicate with engine
 */
extern "C"
int EngineService(void *ctx, uint32_t msg, void *data) {
    assert(ctx == &engine);
    switch (msg) {
        case ENGINE_SERVICE_MSG_KICKSTART_PLAYER:
            return 0;
        case ENGINE_SERVICE_MSG_RETRIEVE_DUMP_BUFS:
            *(static_cast<uint32_t *>(data)) = dbgEngineGetBufCount();
            return 0;
        default:
            assert(false);
            return 0;
    }

    return 1;
}

#ifdef DRIVER_ANDROID_AUDIOPLAYBACK
extern "C"
int createSLBufferQueueAudioPlayer() {
    SampleFormat sampleFormat;
    memset(&sampleFormat, 0, sizeof(sampleFormat));
    sampleFormat.pcmFormat_ = (uint16_t) engine.bitsPerSample_;
    sampleFormat.framesPerBuf_ = engine.fastPathFramesPerBuf_;
    sampleFormat.channels_ = (uint16_t) engine.sampleChannels_;
    sampleFormat.sampleRate_ = engine.usrRqstdSampleRate_; //engine.fastPathSampleRate_; //

    engine.player_ = new AudioPlayer(&sampleFormat, engine.slEngineItf_);
    assert(engine.player_);
    if (engine.player_ == nullptr)
        return 0;

    engine.player_->SetBufQueue(engine.playBufQueue_, engine.freePlayBufQueue_);
    engine.player_->RegisterCallback(EngineService, (void *) &engine);

    return 1;
}

extern "C"
void deleteSLBufferQueueAudioPlayer() {
    if (engine.player_) {
        delete engine.player_;
        engine.player_ = nullptr;
    }
}

extern "C"
void startPlay() {
    /*
     * start player: make it into waitForData state
     */
    if (SL_BOOLEAN_FALSE == engine.player_->Start()) {
        LOGE("====%s failed", __FUNCTION__);
        return;
    }
}

extern "C"
void stopPlay() {
    engine.player_->Stop();

    delete engine.player_;
    engine.player_ = NULL;
}

extern "C"
void enqueueStepInput(int16_t *inData, uint32_t frameSize) {
    uint32_t frameCount = engine.usrFramesByteCount / engine.bufSizeInBytes_;
    uint32_t lastFrameSize = engine.usrFramesByteCount % engine.bufSizeInBytes_;
    if (lastFrameSize) {
        ++frameCount;
    }
    engine.player_->enqueueStepInput(inData, frameCount, lastFrameSize);
}

#endif //DRIVER_ANDROID_AUDIOPLAYBACK

#ifdef DRIVER_ANDROID_AUDIOCAPTURE
extern "C"
int createAudioRecorder() {
    SampleFormat sampleFormat;
    memset(&sampleFormat, 0, sizeof(sampleFormat));
    sampleFormat.pcmFormat_ = static_cast<uint16_t>(engine.bitsPerSample_);

    //sampleFormat.representation_ = SL_ANDROID_PCM_REPRESENTATION_SIGNED_INT;
    sampleFormat.channels_ = engine.sampleChannels_;
    sampleFormat.sampleRate_ = engine.usrRqstdSampleRate_; //engine.fastPathSampleRate_; //
    sampleFormat.framesPerBuf_ = engine.fastPathFramesPerBuf_;
    engine.recorder_ = new AudioRecorder(&sampleFormat, engine.slEngineItf_);
    if (!engine.recorder_) {
        return 0;
    }
    engine.recorder_->SetBufQueues(engine.freeRecBufQueue_, engine.recBufQueue_);
    engine.recorder_->RegisterCallback(EngineService, (void *) &engine);
    return 1;
}

extern "C"
void deleteAudioRecorder() {
    if (engine.recorder_)
        delete engine.recorder_;

    engine.recorder_ = nullptr;
}

extern "C"
void startRecord() {
    /*
     * start player: make it into waitForData state
     */
    if (SL_BOOLEAN_FALSE == engine.recorder_->Start()) {
        LOGE("====%s failed", __FUNCTION__);
        return;
    }
}

extern "C"
void stopRecord() {
    engine.recorder_->Stop();

    delete engine.recorder_;
    engine.recorder_ = NULL;
}

extern "C"
void dequeueStepOutput(int16_t *outData, uint32_t frameSize) {
    engine.recorder_->dequeueStepOutput(outData, engine.usrFramesByteCount);
}

#endif  //DRIVER_ANDROID_AUDIOCAPTURE
