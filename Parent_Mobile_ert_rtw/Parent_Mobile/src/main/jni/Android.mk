LOCAL_PATH := ..
include $(CLEAR_VARS)
OPENCV_INSTALL_MODULES:=on
include D:\OpenCV_452\opencv-android-sdk\opencv-android-sdk\sdk\native\jni\OpenCV.mk
LOCAL_MODULE := Parent_Mobile
LOCAL_CFLAGS += -DDEBUG_ANDROID -DMODEL=Parent_Mobile -DNUMST=2 -DNCSTATES=0 -DHAVESTDIO -DMODEL_HAS_DYNAMICALLY_LOADED_SFCNS=0 -DCLASSIC_INTERFACE=0 -DALLOCATIONFCN=0 -DTID01EQ=0 -DTERMFCN=1 -DONESTEPFCN=1 -DMAT_FILE=0 -DMULTI_INSTANCE_CODE=0 -DINTEGER_CODE=0 -DMT=0 -DSTACK_SIZE=64 -D__MW_TARGET_USE_HARDWARE_RESOURCES_H__ -DRT -D_USE_TARGET_UDP_ -DPORTABLE_WORDSIZES -DDRIVER_ANDROID_AUDIOPLAYBACK 
LOCAL_CPPFLAGS := -std=c++11
LOCAL_SRC_FILES := MW_TCPSendReceive.c DAHostLib_Network.c DAHostLib_rtw.c ert_main.c Parent_Mobile.c Parent_Mobile_data.c androidinitialize.c driver_android_audioplayback.c audio_engine.cpp audio_player.cpp driver_android_videodisplay.cpp driver_android_datadisplay.c driver_android_tcp_log.c linuxUDP.c 
LOCAL_C_INCLUDES += D:/Aayush/Aayush/Matlab C:/PROGRA~3/MATLAB/SUPPOR~1/R2023a/toolbox/target/SUPPOR~1/android/include C:/PROGRA~3/MATLAB/SUPPOR~1/R2023a/toolbox/target/SUPPOR~1/SHARED~1/include D:/APPS2~1/Matlab/toolbox/shared/spc/src_ml/extern/include D:/Aayush/Aayush/Matlab/PARENT~1 D:/APPS2~1/Matlab/extern/include D:/APPS2~1/Matlab/simulink/include D:/APPS2~1/Matlab/rtw/c/src D:/APPS2~1/Matlab/rtw/c/src/ext_mode/common D:/APPS2~1/Matlab/rtw/c/ert 
LOCAL_LDLIBS  +=  -llog -ldl -lOpenSLES -latomic
include $(BUILD_SHARED_LIBRARY)
