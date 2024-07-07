/*
 * driver_android_videodisplay.cpp
 *
 * Driver code
 *
 * Copyright 2013-2016 The MathWorks, Inc.
 */
#include <jni.h>
#include <stdlib.h>
#include <android/log.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

extern JavaVM *cachedJvm;
extern jobject cachedActivityObj;
extern jclass cachedMainActivityCls;

typedef struct _DisplayContext
{
	jmethodID CameraGetOutputBufferID;
	jmethodID InitDisplayID;
	
    int Width;
	int Height;
    
    cv::Mat Temp;
    cv::Mat TempAlpha;
} DisplayContext;

static DisplayContext sgDisplayContext;

extern "C" 
void initVideoDisplay(int width, int height )
{
     JNIEnv *pEnv;
     (cachedJvm)->AttachCurrentThread(&pEnv, NULL);
     sgDisplayContext.CameraGetOutputBufferID = (pEnv)->GetMethodID(cachedMainActivityCls, "getCameraOutputBuffer","()J");
     sgDisplayContext.InitDisplayID = (pEnv)->GetMethodID(cachedMainActivityCls, "initVideoDisplay","(II)I");
     sgDisplayContext.Width = width;
     sgDisplayContext.Height = height;
     sgDisplayContext.TempAlpha = cv::Mat::ones(height, width, CV_8UC1) * 255; 
     if (sgDisplayContext.InitDisplayID != NULL)
     {
         JNIEnv *pEnv;
         jint ret;
         
         (cachedJvm)->AttachCurrentThread(&pEnv, NULL);
         ret = (jint)(pEnv)->CallIntMethod(cachedActivityObj, sgDisplayContext.InitDisplayID, width, height);       
         if (ret != 1)
         {
             /* set the error condition */
         }
     }
}

extern "C" 
void putVideoDisplayData(uint8_t *inCh1, uint8_t *inCh2, uint8_t *inCh3)
{
     if (sgDisplayContext.CameraGetOutputBufferID != NULL)
     {
        JNIEnv *pEnv;
 		jlong ret;
         
        (cachedJvm)->AttachCurrentThread(&pEnv, NULL);
        ret = (jlong)((pEnv)->CallLongMethod(cachedActivityObj, sgDisplayContext.CameraGetOutputBufferID));
        if (ret != 0)
        {
            cv::Mat&   output = *(cv::Mat *)ret;
            
            // __android_log_print(ANDROID_LOG_INFO, "CAMERAOUTPUT", "%d, %d, %d", 
            //     *inCh1, *inCh2, *inCh3);
            std::vector<cv::Mat> channels;
            cv::Mat  JustCh1Mat = cv::Mat(sgDisplayContext.Height, sgDisplayContext.Width, CV_8UC1, inCh1);
            cv::Mat  JustCh2Mat = cv::Mat(sgDisplayContext.Height, sgDisplayContext.Width, CV_8UC1, inCh2);
            cv::Mat  JustCh3Mat = cv::Mat(sgDisplayContext.Height, sgDisplayContext.Width, CV_8UC1, inCh3);
            channels.push_back(JustCh1Mat);
            channels.push_back(JustCh2Mat);
            channels.push_back(JustCh3Mat);
            channels.push_back(sgDisplayContext.TempAlpha);
            if ((sgDisplayContext.Width !=  output.cols) || (sgDisplayContext.Height != output.rows))
            {
               cv::merge(channels, sgDisplayContext.Temp);
               //find the overlapping rectangle - Temp and Output.
               //Copy from Temp to Output 
               int TempLeft = 0;
               int OutputLeft = 0;
               int Width = sgDisplayContext.Width;
               if (sgDisplayContext.Width > output.cols) 
               {
                   TempLeft = (sgDisplayContext.Width  - output.cols) >> 1;
                   Width = output.cols;
               }
               else
               {
                   OutputLeft = (output.cols - sgDisplayContext.Width)  >> 1;
               }
               int TempTop = 0;
               int OutputTop = 0;
               int Height = sgDisplayContext.Height;
               if (sgDisplayContext.Height > output.rows) 
               {
                   TempTop = (sgDisplayContext.Height  - output.rows) >> 1;
                   Height = output.rows;
               }
               else
               {
                   OutputTop = (output.rows - sgDisplayContext.Height)  >> 1;
               }
               cv::Mat OutputRoi(output, cv::Rect(OutputLeft,OutputTop,Width, Height));
               cv::Mat TempRoi(sgDisplayContext.Temp, cv::Rect(TempLeft,TempTop,Width,Height));
               TempRoi.copyTo(OutputRoi);
            }
            else
            {
                cv::merge(channels, output);
            }
        }
     }
}

extern "C" 
void terminateVideoDisplay()
{
}
// LocalWords:  CAMERAOUTPUT sgDisplayContext
