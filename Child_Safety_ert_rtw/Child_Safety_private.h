/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Child_Safety_private.h
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

#ifndef RTW_HEADER_Child_Safety_private_h_
#define RTW_HEADER_Child_Safety_private_h_
#include "rtwtypes.h"
#include "Child_Safety.h"
#include "Child_Safety_types.h"

extern real_T rt_atan2d_snf(real_T u0, real_T u1);
extern void Child_Safety_Accelerometer_Init(DW_Accelerometer_Child_Safety_T
  *localDW);
extern void Child_Safety_Accelerometer(B_Accelerometer_Child_Safety_T *localB);
extern void Child_Safet_LocationSensor_Init(DW_LocationSensor_Child_Safet_T
  *localDW);
extern void Child_Safety_LocationSensor(B_LocationSensor_Child_Safety_T *localB);
extern void Child_Safety_Accelerometer_Term(DW_Accelerometer_Child_Safety_T
  *localDW);
extern void Child_Safet_LocationSensor_Term(DW_LocationSensor_Child_Safet_T
  *localDW);

#endif                                 /* RTW_HEADER_Child_Safety_private_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
