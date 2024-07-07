/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Map_Trial.h
 *
 * Code generated for Simulink model 'Map_Trial'.
 *
 * Model version                  : 1.2
 * Simulink Coder version         : 9.9 (R2023a) 19-Nov-2022
 * C/C++ source code generated on : Sat Sep 30 14:36:53 2023
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 *    3. ROM efficiency
 * Validation result: Not run
 */

#ifndef RTW_HEADER_Map_Trial_h_
#define RTW_HEADER_Map_Trial_h_
#ifndef Map_Trial_COMMON_INCLUDES_
#define Map_Trial_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "driver_android_datadisplay.h"
#include "driver_android_location.h"
#include "driver_android_videodisplay.h"
#endif                                 /* Map_Trial_COMMON_INCLUDES_ */

#include "Map_Trial_types.h"
#include <stddef.h>

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Block signals (default storage) */
typedef struct {
  uint8_T RMU[576232];                 /* '<Root>/MATLAB Function6' */
  uint8_T GMU[576232];                 /* '<Root>/MATLAB Function6' */
  uint8_T BMU[576232];                 /* '<Root>/MATLAB Function6' */
  real_T out[3];
  real_T dx;
} B_Map_Trial_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  codertarget_internal_androidL_T obj; /* '<S2>/Location Sensor' */
} DW_Map_Trial_T;

/* Parameters (default storage) */
struct P_Map_Trial_T_ {
  real_T DataStoreMemory_InitialValue; /* Expression: 0
                                        * Referenced by: '<Root>/Data Store Memory'
                                        */
  real_T DataStoreMemory1_InitialValue;/* Expression: 0
                                        * Referenced by: '<Root>/Data Store Memory1'
                                        */
  boolean_T DataStoreMemory2_InitialValue;
                            /* Computed Parameter: DataStoreMemory2_InitialValue
                             * Referenced by: '<Root>/Data Store Memory2'
                             */
  uint8_T R_Value[576232];             /* Expression: img(:,:,1)
                                        * Referenced by: '<Root>/R'
                                        */
  uint8_T G_Value[576232];             /* Expression: img(:,:,2)
                                        * Referenced by: '<Root>/G'
                                        */
  uint8_T B_Value[576232];             /* Expression: img(:,:,3)
                                        * Referenced by: '<Root>/B'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_Map_Trial_T {
  const char_T * volatile errorStatus;
};

/* Block parameters (default storage) */
extern P_Map_Trial_T Map_Trial_P;

/* Block signals (default storage) */
extern B_Map_Trial_T Map_Trial_B;

/* Block states (default storage) */
extern DW_Map_Trial_T Map_Trial_DW;

/* Model entry point functions */
extern void Map_Trial_initialize(void);
extern void Map_Trial_step(void);
extern void Map_Trial_terminate(void);

/* Real-time Model object */
extern RT_MODEL_Map_Trial_T *const Map_Trial_M;
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
 * '<Root>' : 'Map_Trial'
 * '<S1>'   : 'Map_Trial/Latitude'
 * '<S2>'   : 'Map_Trial/Location Sensor2'
 * '<S3>'   : 'Map_Trial/Longitude'
 * '<S4>'   : 'Map_Trial/MATLAB Function10'
 * '<S5>'   : 'Map_Trial/MATLAB Function6'
 * '<S6>'   : 'Map_Trial/MATLAB Function7'
 * '<S7>'   : 'Map_Trial/MATLAB Function8'
 * '<S8>'   : 'Map_Trial/MATLAB Function9'
 * '<S9>'   : 'Map_Trial/Video Display1'
 * '<S10>'  : 'Map_Trial/dr'
 * '<S11>'  : 'Map_Trial/dx'
 * '<S12>'  : 'Map_Trial/dy'
 */
#endif                                 /* RTW_HEADER_Map_Trial_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
