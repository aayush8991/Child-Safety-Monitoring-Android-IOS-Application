/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Child_Safety.h
 *
 * Code generated for Simulink model 'Child_Safety'.
 *
 * Model version                  : 1.32
 * Simulink Coder version         : 9.9 (R2023a) 19-Nov-2022
 * C/C++ source code generated on : Wed Sep 20 22:27:33 2023
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 *    3. ROM efficiency
 * Validation result: Not run
 */

#ifndef RTW_HEADER_Child_Safety_h_
#define RTW_HEADER_Child_Safety_h_
#ifndef Child_Safety_COMMON_INCLUDES_
#define Child_Safety_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "driver_android_accelerometer.h"
#include "driver_android_datadisplay.h"
#include "driver_android_audiofileread.h"
#include "driver_android_audioplayback.h"
#include "driver_android_gyroscope.h"
#include "driver_android_location.h"
#endif                                 /* Child_Safety_COMMON_INCLUDES_ */

#include "Child_Safety_types.h"
#include "rtGetNaN.h"
#include "rt_nonfinite.h"
#include <stddef.h>

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Block signals for system '<S1>/Accelerometer' */
typedef struct {
  real32_T Accelerometer_o1;           /* '<S1>/Accelerometer' */
  real32_T Accelerometer_o2;           /* '<S1>/Accelerometer' */
  real32_T Accelerometer_o3;           /* '<S1>/Accelerometer' */
} B_Accelerometer_Child_Safety_T;

/* Block states (default storage) for system '<S1>/Accelerometer' */
typedef struct {
  codertarget_internal_androidA_T obj; /* '<S1>/Accelerometer' */
  boolean_T objisempty;                /* '<S1>/Accelerometer' */
} DW_Accelerometer_Child_Safety_T;

/* Block signals for system '<S8>/Location Sensor' */
typedef struct {
  real_T LocationSensor_o1;            /* '<S8>/Location Sensor' */
  real_T LocationSensor_o2;            /* '<S8>/Location Sensor' */
  real_T LocationSensor_o3;            /* '<S8>/Location Sensor' */
} B_LocationSensor_Child_Safety_T;

/* Block states (default storage) for system '<S8>/Location Sensor' */
typedef struct {
  codertarget_internal_androidL_T obj; /* '<S8>/Location Sensor' */
  boolean_T objisempty;                /* '<S8>/Location Sensor' */
} DW_LocationSensor_Child_Safet_T;

/* Block signals (default storage) */
typedef struct {
  int16_T iv[8820];
  int16_T outData[8820];
  real32_T out[3];
  real_T lat2_rad;
  real_T b_a;
  B_LocationSensor_Child_Safety_T LocationSensor_o;/* '<S8>/Location Sensor' */
  B_LocationSensor_Child_Safety_T LocationSensor;/* '<S8>/Location Sensor' */
  B_Accelerometer_Child_Safety_T Accelerometer_d;/* '<S1>/Accelerometer' */
  B_Accelerometer_Child_Safety_T Accelerometer;/* '<S1>/Accelerometer' */
} B_Child_Safety_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  codertarget_internal_andro_fk_T obj; /* '<Root>/Audio File Read1' */
  codertarget_internal_androi_f_T obj_m;/* '<S4>/Audio Playback' */
  codertarget_internal_androidG_T obj_i;/* '<S6>/MATLAB System' */
  boolean_T Delay_DSTATE;              /* '<Root>/Delay' */
  DW_LocationSensor_Child_Safet_T LocationSensor_o;/* '<S8>/Location Sensor' */
  DW_LocationSensor_Child_Safet_T LocationSensor;/* '<S8>/Location Sensor' */
  DW_Accelerometer_Child_Safety_T Accelerometer_d;/* '<S1>/Accelerometer' */
  DW_Accelerometer_Child_Safety_T Accelerometer;/* '<S1>/Accelerometer' */
} DW_Child_Safety_T;

/* Parameters (default storage) */
struct P_Child_Safety_T_ {
  real_T AudioPlayback_SampleFreq;     /* Expression: SampleFreq
                                        * Referenced by: '<S4>/Audio Playback'
                                        */
  boolean_T Delay_InitialCondition;/* Computed Parameter: Delay_InitialCondition
                                    * Referenced by: '<Root>/Delay'
                                    */
};

/* Real-time Model Data Structure */
struct tag_RTM_Child_Safety_T {
  const char_T * volatile errorStatus;
};

/* Block parameters (default storage) */
extern P_Child_Safety_T Child_Safety_P;

/* Block signals (default storage) */
extern B_Child_Safety_T Child_Safety_B;

/* Block states (default storage) */
extern DW_Child_Safety_T Child_Safety_DW;

/* Model entry point functions */
extern void Child_Safety_initialize(void);
extern void Child_Safety_step(void);
extern void Child_Safety_terminate(void);

/* Real-time Model object */
extern RT_MODEL_Child_Safety_T *const Child_Safety_M;
extern volatile boolean_T stopRequested;
extern volatile boolean_T runModel;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'Child_Safety'
 * '<S1>'   : 'Child_Safety/Accelerometer'
 * '<S2>'   : 'Child_Safety/Accelerometer3'
 * '<S3>'   : 'Child_Safety/Alt'
 * '<S4>'   : 'Child_Safety/Audio Playback'
 * '<S5>'   : 'Child_Safety/Distance Function'
 * '<S6>'   : 'Child_Safety/Gyroscope'
 * '<S7>'   : 'Child_Safety/Lat'
 * '<S8>'   : 'Child_Safety/Location Sensor'
 * '<S9>'   : 'Child_Safety/Location Sensor1'
 * '<S10>'  : 'Child_Safety/Lon'
 * '<S11>'  : 'Child_Safety/MATLAB Function'
 * '<S12>'  : 'Child_Safety/X_Acc'
 * '<S13>'  : 'Child_Safety/X_Gyro'
 * '<S14>'  : 'Child_Safety/Y_Acc'
 * '<S15>'  : 'Child_Safety/Y_Gyro'
 * '<S16>'  : 'Child_Safety/Z_Acc'
 * '<S17>'  : 'Child_Safety/Z_Gyro'
 */
#endif                                 /* RTW_HEADER_Child_Safety_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
