LOCAL_PATH := ..
include $(CLEAR_VARS)
LOCAL_MODULE := Child_Safety
LOCAL_CFLAGS += -DMODEL=Child_Safety -DNUMST=1 -DNCSTATES=0 -DHAVESTDIO -DMODEL_HAS_DYNAMICALLY_LOADED_SFCNS=0 -DCLASSIC_INTERFACE=0 -DALLOCATIONFCN=0 -DTID01EQ=0 -DTERMFCN=1 -DONESTEPFCN=1 -DMAT_FILE=0 -DMULTI_INSTANCE_CODE=0 -DINTEGER_CODE=0 -DMT=0 -DSTACK_SIZE=64 -D__MW_TARGET_USE_HARDWARE_RESOURCES_H__ -DRT -DPORTABLE_WORDSIZES -DDRIVER_ANDROID_AUDIOPLAYBACK 
LOCAL_CPPFLAGS := -std=c++11
LOCAL_SRC_FILES := ert_main.c Child_Safety.c Child_Safety_data.c rtGetInf.c rtGetNaN.c rt_nonfinite.c androidinitialize.c driver_android_accelerometer.c driver_android_audiofileread.c driver_android_audioplayback.c audio_engine.cpp audio_player.cpp driver_android_gyroscope.c driver_android_location.c driver_android_datadisplay.c 
LOCAL_C_INCLUDES += D:/Aayush/Aayush/Matlab C:/PROGRA~3/MATLAB/SUPPOR~1/R2023a/toolbox/target/SUPPOR~1/android/include D:/Aayush/Aayush/Matlab/CHILD_~1 D:/APPS2~1/Matlab/extern/include D:/APPS2~1/Matlab/simulink/include D:/APPS2~1/Matlab/rtw/c/src D:/APPS2~1/Matlab/rtw/c/src/ext_mode/common D:/APPS2~1/Matlab/rtw/c/ert 
LOCAL_LDLIBS  +=  -llog -ldl -lOpenSLES -latomic
include $(BUILD_SHARED_LIBRARY)
