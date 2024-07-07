LOCAL_PATH := ..
include $(CLEAR_VARS)
OPENCV_INSTALL_MODULES:=on
include D:\OpenCV_452\opencv-android-sdk\opencv-android-sdk\sdk\native\jni\OpenCV.mk
LOCAL_MODULE := Map_Trial
LOCAL_CFLAGS += -DMODEL=Map_Trial -DNUMST=1 -DNCSTATES=0 -DHAVESTDIO -DMODEL_HAS_DYNAMICALLY_LOADED_SFCNS=0 -DCLASSIC_INTERFACE=0 -DALLOCATIONFCN=0 -DTID01EQ=0 -DTERMFCN=1 -DONESTEPFCN=1 -DMAT_FILE=0 -DMULTI_INSTANCE_CODE=0 -DINTEGER_CODE=0 -DMT=0 -DSTACK_SIZE=64 -D__MW_TARGET_USE_HARDWARE_RESOURCES_H__ -DRT -DPORTABLE_WORDSIZES 
LOCAL_SRC_FILES := ert_main.c Map_Trial.c Map_Trial_data.c androidinitialize.c driver_android_videodisplay.cpp driver_android_location.c driver_android_datadisplay.c 
LOCAL_C_INCLUDES += D:/Aayush/Aayush/Matlab C:/PROGRA~3/MATLAB/SUPPOR~1/R2023a/toolbox/target/SUPPOR~1/android/include D:/Aayush/Aayush/Matlab/MAP_TR~1 D:/APPS2~1/Matlab/extern/include D:/APPS2~1/Matlab/simulink/include D:/APPS2~1/Matlab/rtw/c/src D:/APPS2~1/Matlab/rtw/c/src/ext_mode/common D:/APPS2~1/Matlab/rtw/c/ert 
LOCAL_LDLIBS  +=  -llog -ldl
include $(BUILD_SHARED_LIBRARY)
