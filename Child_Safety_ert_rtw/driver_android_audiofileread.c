/*
 * driver_android_audiofileread.c
 *
 * Driver code for Audio File Read
 *
 * Copyright 2016 The MathWorks, Inc.
 */

#include <jni.h>
#include <stdlib.h>
#include <android/log.h>

extern JavaVM *cachedJvm;
extern jobject cachedActivityObj;
extern jclass cachedMainActivityCls;
static jmethodID methodAudioFileReadInitID;
static jmethodID methodAudioFileReadStepID;
static jmethodID methodAudioFileReadTerminateID;

// JNI - initialization function
void initAudioFileRead(char* fName, char* fExt, int frameSize, int* idxP)
{
     JNIEnv *pEnv;
     jstring jFileName;
     jint jFrameSize;
     jint jIdx;
     
     (*cachedJvm)->AttachCurrentThread(cachedJvm, &pEnv, NULL);
     
     jFileName = (*pEnv)->NewStringUTF(pEnv, fName);
     jFrameSize = frameSize;
     
     methodAudioFileReadInitID = (*pEnv)->GetMethodID(pEnv, cachedMainActivityCls, "audioFileReadInit", "(Ljava/lang/String;I)I");
     jIdx = (*pEnv)->CallIntMethod(pEnv, cachedActivityObj, methodAudioFileReadInitID, jFileName, jFrameSize);
     *idxP = jIdx;

     __android_log_print(ANDROID_LOG_INFO, "initAudioFileRead", "Index is %d", *idxP);
     
     (*pEnv)->DeleteLocalRef(pEnv, jFileName);
}

// JNI - step function
void readAudioFileData(int frameSize, int numChannels, short *out, int idx)
{
     JNIEnv *pEnv;
     jshortArray jData;
     (*cachedJvm)->AttachCurrentThread(cachedJvm, &pEnv, NULL);
     
     methodAudioFileReadStepID = (*pEnv)->GetMethodID(pEnv, cachedMainActivityCls, "audioFileReadStep", "(I)[S");
     jData = (*pEnv)->CallObjectMethod(pEnv, cachedActivityObj, methodAudioFileReadStepID, idx);
     (*pEnv)->GetShortArrayRegion(pEnv, jData, 0, frameSize*numChannels, out);
     (*pEnv)->DeleteLocalRef(pEnv, jData);
 }

// JNI - terminate function
void terminateAudioFileRead(int idx)
{
     JNIEnv *pEnv;
     (*cachedJvm)->AttachCurrentThread(cachedJvm, &pEnv, NULL);
     
     methodAudioFileReadTerminateID = (*pEnv)->GetMethodID(pEnv, cachedMainActivityCls, "audioFileReadTerminate", "(I)V");
     (*pEnv)->CallVoidMethod(pEnv, cachedActivityObj, methodAudioFileReadTerminateID, idx);
}