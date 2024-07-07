/*
 * driver_android_location.c
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
static jmethodID sgLocationSensorGetDataID;

void initLocationSensor()
{
   JNIEnv *pEnv;
    (*cachedJvm)->AttachCurrentThread(cachedJvm, &pEnv, NULL);
    sgLocationSensorGetDataID = (*pEnv)->GetMethodID(pEnv, cachedMainActivityCls, "getGPSData",
    "()[D"); 
}

void getLocationData(double *outLatitude, double *outLongitude, double *outAltitude)
{
    if (sgLocationSensorGetDataID != NULL)
    {

        JNIEnv *pEnv;
        jdoubleArray ret;
        jdouble values[3];
        
        (*cachedJvm)->AttachCurrentThread(cachedJvm, &pEnv, NULL);
        
        ret = (jdoubleArray)(*pEnv)->CallObjectMethod(pEnv, cachedActivityObj, sgLocationSensorGetDataID);       
        if ((*pEnv)->ExceptionCheck(pEnv)) 
            return; /* Exception during execution of getGPSData */
        
        (*pEnv)->GetDoubleArrayRegion(pEnv, ret, 0, 3, values);
        if ((*pEnv)->ExceptionCheck(pEnv)) 
        {
            (*pEnv)->DeleteLocalRef(pEnv, ret);
            return; /* ArrayIndexOutOfBoundsException */
        }
        
        *outLatitude  = values[0];
        *outLongitude = values[1];
        *outAltitude  = values[2];

        (*pEnv)->DeleteLocalRef(pEnv, ret);
    }
}

void terminateLocationSensor()
{
}