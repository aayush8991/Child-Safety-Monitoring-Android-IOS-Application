/*
 * driver_android_accelerometer.c
 *
 * Driver code
 *
 * Copyright 2013-2015 The MathWorks, Inc.
 */
#include <jni.h>
#include <stdlib.h>

extern JavaVM *cachedJvm;
extern jobject cachedActivityObj;
extern jclass cachedMainActivityCls;
static jmethodID sgAccelSensorGetDataID;

void initAccelerometer()
{
    JNIEnv *pEnv;
    (*cachedJvm)->AttachCurrentThread(cachedJvm, &pEnv, NULL);
    sgAccelSensorGetDataID = (*pEnv)->GetMethodID(pEnv, cachedMainActivityCls, "getAccelerometerData",
    "()[F");    
}

void getAccelerometerData(float *outX, float *outY ,float *outZ)
{
    if (sgAccelSensorGetDataID != NULL)
    {
        JNIEnv *pEnv;
        jfloatArray ret;
        jfloat values[3];        
        
        (*cachedJvm)->AttachCurrentThread(cachedJvm, &pEnv, NULL);
        
        ret = (jfloatArray)(*pEnv)->CallObjectMethod(pEnv, cachedActivityObj, sgAccelSensorGetDataID);       
        if ((*pEnv)->ExceptionCheck(pEnv)) 
            return; /* Exception during execution of getAccelerometerData */
        
        (*pEnv)->GetFloatArrayRegion(pEnv, ret, 0, 3, values);
        if ((*pEnv)->ExceptionCheck(pEnv)) 
        {
            (*pEnv)->DeleteLocalRef(pEnv, ret);
            return; /* ArrayIndexOutOfBoundsException */
        }

        *outX = values[0];
        *outY = values[1];
        *outZ = values[2];
        
        (*pEnv)->DeleteLocalRef(pEnv, ret);
    }
}

void terminateAccelerometer()
{
}