/*
 * driver_android_audioplayback.c
 *
 * Driver code
 *
 * Copyright 2013-2018 The MathWorks, Inc.
 */
#include <jni.h>
#include <stdlib.h>
#include <SLES/OpenSLES.h>
/*#include <time.h>*/

#include "audio_engine.h"

extern JavaVM *cachedJvm;
extern jobject cachedActivityObj;
extern jclass cachedMainActivityCls;

static int isPaused;

void audioPlaybackInit(int sampleRate, int frameSize) {
    JNIEnv *pEnv;
    (*cachedJvm)->AttachCurrentThread(cachedJvm, &pEnv, NULL);
    jmethodID SampleRateMethodID;
    jmethodID BufSizeMethodID;

    char format[] = {"()I"};

    int outData[2];

    /****** get native sample rate from activity ******/
    SampleRateMethodID = (*pEnv)->GetMethodID(pEnv, cachedMainActivityCls, "getNativeSampleRate",
                                           format);

    if ((*pEnv)->ExceptionCheck(pEnv)) {
        LOGE("@%s: Exception occurred on calling GetMethodID for SampleRate.", __FUNCTION__);
        (*pEnv)->ExceptionDescribe(pEnv);
        (*pEnv)->ExceptionClear(pEnv);
        return;
    }

    if (SampleRateMethodID != NULL) {
        jint ret;

        ret = (*pEnv)->CallIntMethod(pEnv, cachedActivityObj, SampleRateMethodID);
        outData[0] = ret ? ret : 44100;

        if ((*pEnv)->ExceptionCheck(pEnv)) {
            LOGE("@%s: Exception occurred on calling CallIntMethod for SampleRate.", __FUNCTION__);
            (*pEnv)->ExceptionDescribe(pEnv);
            (*pEnv)->ExceptionClear(pEnv);
            return;
        }
    }

    /****** get native buffer size from activity ******/
    BufSizeMethodID = (*pEnv)->GetMethodID(pEnv, cachedMainActivityCls, "getNativeSampleBufSize",
                                        format);

    if ((*pEnv)->ExceptionCheck(pEnv)) {
        LOGE("@%s Exception:: calling GetMethodID for getNativeSampleBufSize.", __FUNCTION__);
        (*pEnv)->ExceptionDescribe(pEnv);
        (*pEnv)->ExceptionClear(pEnv);
        return;
    }

    if (BufSizeMethodID != NULL) {
        jint ret;

        ret = (*pEnv)->CallIntMethod(pEnv, cachedActivityObj, BufSizeMethodID);
        outData[1] = ret ? ret : 960;

        if ((*pEnv)->ExceptionCheck(pEnv)) {
            LOGE("@%s Exception:: calling CallIntMethod for getNativeSampleBufSize.", __FUNCTION__);
            (*pEnv)->ExceptionDescribe(pEnv);
            (*pEnv)->ExceptionClear(pEnv);
            return;
        }
    }

    LOGD("getNativeAudioParameters: %d, %d", outData[0], outData[1]);
    uint32_t dataSourceSampleRate;
    switch (sampleRate) {
        case 8000:
            dataSourceSampleRate = SL_SAMPLINGRATE_8;
            break;
        case 11025:
            dataSourceSampleRate = SL_SAMPLINGRATE_11_025;
            break;
        case 12000:
            dataSourceSampleRate = SL_SAMPLINGRATE_12;
            break;
        case 16000:
            dataSourceSampleRate = SL_SAMPLINGRATE_16;
            break;
        case 22050:
            dataSourceSampleRate = SL_SAMPLINGRATE_22_05;
            break;
        case 24000:
            dataSourceSampleRate = SL_SAMPLINGRATE_24;
            break;
        case 32000:
            dataSourceSampleRate = SL_SAMPLINGRATE_32;
            break;
        case 44100:
            dataSourceSampleRate = SL_SAMPLINGRATE_44_1;
            break;
        case 48000:
            dataSourceSampleRate = SL_SAMPLINGRATE_48;
            break;
    }

    createSLEngine(outData[0], outData[1], dataSourceSampleRate, frameSize);
    if (!createSLBufferQueueAudioPlayer()) {
        LOGE("@%s: Failed to create Audio Player", __FUNCTION__);
        return;
    }
    startPlay();
}

/*long getTimeNsec() {
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    return now.tv_nsec;
}*/

void audioPlayback(int16_t *inData, int frameSize) {
    //long startTime = getTimeNsec();
    if (!isPaused) {
        enqueueStepInput(inData, (uint32_t) frameSize);
    }
    //long endTime = getTimeNsec();
    //LOGI("@%s: exec time: %ld ms",__FUNCTION__, (endTime - startTime));
}

void audioPlaybackTerminate() {
    stopPlay();
    deleteSLBufferQueueAudioPlayer();
    deleteSLEngine();
}

void onAudioPlaybackStateChange(int state) {
    switch (state) {
        case 3:
            isPaused = 0;
            break;
        case 4:
            isPaused = 1;
            break;
    }
}
