/*
 * driver_android_tcp_log.c
 *
 * Driver code
 *
 * Copyright 2016 The MathWorks, Inc.
 */
#include <jni.h>
#include <stdlib.h>
#include <string.h>
#include <android/log.h>
#include "driver_android_tcp_log.h"

extern JavaVM *cachedJvm;
extern jobject cachedActivityObj;
extern jclass cachedMainActivityCls;


void updateTCPLogI(int16_t errorNo, int blockId, int8_t isReceive, int16_t portNumber) {
    char argument[16];
    sprintf(argument,"%d",portNumber);
    updateTCPLogS(errorNo, blockId, isReceive,argument);
}

void updateTCPLogS(int16_t errorNo, int blockId, int8_t isReceive, char* argument) {
    jmethodID displayTCPLogsMethodID;
    JNIEnv *pEnv;
    (*cachedJvm)->AttachCurrentThread(cachedJvm, &pEnv, NULL);
    char format[] = {"(SISLjava/lang/String;)V"};

    displayTCPLogsMethodID = (*pEnv)->GetMethodID(pEnv, cachedMainActivityCls, "displayTCPLogs", format);
    if ((*pEnv)->ExceptionCheck(pEnv))
    {
        __android_log_print(ANDROID_LOG_DEBUG, "driver_android_tcp_log", "Exception: exception occurred on calling GetMethodID.");
        (*pEnv)->ExceptionDescribe(pEnv);
        (*pEnv)->ExceptionClear(pEnv);
        return;
    }
    
    if (displayTCPLogsMethodID != NULL) {
        jstring str = (*pEnv)->NewStringUTF(pEnv, argument);
        if ((*pEnv)->ExceptionCheck(pEnv))
        {
            __android_log_write(ANDROID_LOG_ERROR, "driver_android_tcp_log", "exception occurred on setting data array.");
            (*pEnv)->ExceptionDescribe(pEnv);
            (*pEnv)->DeleteLocalRef(pEnv, str);
            (*pEnv)->ExceptionClear(pEnv);
            return;
        }
        (*pEnv)->CallVoidMethod(pEnv, cachedActivityObj, displayTCPLogsMethodID, errorNo, blockId,isReceive,str);
        
        // Clear the exception so user can proceed
        if ((*pEnv)->ExceptionCheck(pEnv)) {
            __android_log_write(ANDROID_LOG_ERROR, "driver_android_tcp_log", "Exception: exception occurred on calling CallVoidMethod.");
            (*pEnv)->ExceptionDescribe(pEnv);
            (*pEnv)->ExceptionClear(pEnv);
        }
        (*pEnv)->DeleteLocalRef(pEnv, str);
    }
}