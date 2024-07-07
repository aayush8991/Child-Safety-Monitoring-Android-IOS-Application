/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Parent_Mobile.h
 *
 * Code generated for Simulink model 'Parent_Mobile'.
 *
 * Model version                  : 1.37
 * Simulink Coder version         : 9.9 (R2023a) 19-Nov-2022
 * C/C++ source code generated on : Sat Sep 30 10:46:18 2023
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 *    3. ROM efficiency
 * Validation result: Not run
 */

#ifndef RTW_HEADER_Parent_Mobile_h_
#define RTW_HEADER_Parent_Mobile_h_
#ifndef Parent_Mobile_COMMON_INCLUDES_
#define Parent_Mobile_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "driver_android_audioplayback.h"
#include "driver_android_datadisplay.h"
#include "MW_TCPSendReceive.h"
#include "driver_android_tcp_log.h"
#include "driver_android_videodisplay.h"
#include "DAHostLib_Network.h"
#endif                                 /* Parent_Mobile_COMMON_INCLUDES_ */

#include "Parent_Mobile_types.h"
#include <stddef.h>

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
#define rtmGetStopRequested(rtm)       ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
#define rtmSetStopRequested(rtm, val)  ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
#define rtmGetStopRequestedPtr(rtm)    (&((rtm)->Timing.stopRequestedFlag))
#endif

/* Block signals (default storage) */
typedef struct {
  uint8_T y_c[76800];                  /* '<Root>/MATLAB Function2' */
  uint8_T y_j[76800];                  /* '<Root>/MATLAB Function4' */
  uint8_T y_p[76800];                  /* '<Root>/MATLAB Function3' */
  int16_T outData[8820];
  int16_T y[8820];                     /* '<Root>/MATLAB Function5' */
  char_T str_data[11];
  char_T b_str_data[11];
  real_T UDPReceive3_o1;               /* '<Root>/UDP Receive3' */
  real_T UDPReceive5_o1;               /* '<Root>/UDP Receive5' */
  real_T UDPReceive6_o1;               /* '<Root>/UDP Receive6' */
  int16_T UDPReceive_o1[4410];         /* '<Root>/UDP Receive' */
  int16_T UDPReceive1_o1[4410];        /* '<Root>/UDP Receive1' */
  uint8_T TCPIPReceive6_o1[76800];     /* '<Root>/TCP//IP Receive6' */
  uint8_T TCPIPReceive5_o1[76800];     /* '<Root>/TCP//IP Receive5' */
  uint8_T TCPIPReceive4_o1[76800];     /* '<Root>/TCP//IP Receive4' */
  real_T u0;
  real32_T UDPReceive4_o1;             /* '<Root>/UDP Receive4' */
} B_Parent_Mobile_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  codertarget_internal_androidA_T obj; /* '<S1>/Audio Playback' */
  codertarget_internal_androidT_T obj_c;/* '<Root>/TCP//IP Receive6' */
  codertarget_internal_androidT_T obj_a;/* '<Root>/TCP//IP Receive5' */
  codertarget_internal_androidT_T obj_n;/* '<Root>/TCP//IP Receive4' */
  real_T UDPReceive_NetworkLib[137];   /* '<Root>/UDP Receive' */
  real_T UDPReceive1_NetworkLib[137];  /* '<Root>/UDP Receive1' */
  real_T UDPReceive4_NetworkLib[137];  /* '<Root>/UDP Receive4' */
  real_T UDPReceive3_NetworkLib[137];  /* '<Root>/UDP Receive3' */
  real_T UDPReceive5_NetworkLib[137];  /* '<Root>/UDP Receive5' */
  real_T UDPReceive6_NetworkLib[137];  /* '<Root>/UDP Receive6' */
} DW_Parent_Mobile_T;

/* Parameters (default storage) */
struct P_Parent_Mobile_T_ {
  real_T AudioPlayback_SampleFreq;     /* Expression: SampleFreq
                                        * Referenced by: '<S1>/Audio Playback'
                                        */
  int32_T UDPReceive_Port;             /* Computed Parameter: UDPReceive_Port
                                        * Referenced by: '<Root>/UDP Receive'
                                        */
  int32_T UDPReceive1_Port;            /* Computed Parameter: UDPReceive1_Port
                                        * Referenced by: '<Root>/UDP Receive1'
                                        */
  int32_T UDPReceive4_Port;            /* Computed Parameter: UDPReceive4_Port
                                        * Referenced by: '<Root>/UDP Receive4'
                                        */
  int32_T UDPReceive3_Port;            /* Computed Parameter: UDPReceive3_Port
                                        * Referenced by: '<Root>/UDP Receive3'
                                        */
  int32_T UDPReceive5_Port;            /* Computed Parameter: UDPReceive5_Port
                                        * Referenced by: '<Root>/UDP Receive5'
                                        */
  int32_T UDPReceive6_Port;            /* Computed Parameter: UDPReceive6_Port
                                        * Referenced by: '<Root>/UDP Receive6'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_Parent_Mobile_T {
  const char_T * volatile errorStatus;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    struct {
      uint8_T TID[2];
    } TaskCounters;

    boolean_T stopRequestedFlag;
  } Timing;
};

/* Block parameters (default storage) */
extern P_Parent_Mobile_T Parent_Mobile_P;

/* Block signals (default storage) */
extern B_Parent_Mobile_T Parent_Mobile_B;

/* Block states (default storage) */
extern DW_Parent_Mobile_T Parent_Mobile_DW;

/* Model entry point functions */
extern void Parent_Mobile_initialize(void);
extern void Parent_Mobile_step(void);
extern void Parent_Mobile_terminate(void);

/* Real-time Model object */
extern RT_MODEL_Parent_Mobile_T *const Parent_Mobile_M;
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
 * '<Root>' : 'Parent_Mobile'
 * '<S1>'   : 'Parent_Mobile/Audio Playback2'
 * '<S2>'   : 'Parent_Mobile/Distance From Home'
 * '<S3>'   : 'Parent_Mobile/Latitude'
 * '<S4>'   : 'Parent_Mobile/Longitude'
 * '<S5>'   : 'Parent_Mobile/MATLAB Function2'
 * '<S6>'   : 'Parent_Mobile/MATLAB Function3'
 * '<S7>'   : 'Parent_Mobile/MATLAB Function4'
 * '<S8>'   : 'Parent_Mobile/MATLAB Function5'
 * '<S9>'   : 'Parent_Mobile/Video Display'
 */
#endif                                 /* RTW_HEADER_Parent_Mobile_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
