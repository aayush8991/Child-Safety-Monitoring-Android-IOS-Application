/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Child_Safety.c
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

#include "Child_Safety.h"
#include "rtwtypes.h"
#include "Child_Safety_private.h"
#include <string.h>
#include <math.h>
#include "rt_nonfinite.h"
#include "rt_defines.h"

/* Block signals (default storage) */
B_Child_Safety_T Child_Safety_B;

/* Block states (default storage) */
DW_Child_Safety_T Child_Safety_DW;

/* Real-time model */
static RT_MODEL_Child_Safety_T Child_Safety_M_;
RT_MODEL_Child_Safety_T *const Child_Safety_M = &Child_Safety_M_;

/* System initialize for atomic system: */
void Child_Safety_Accelerometer_Init(DW_Accelerometer_Child_Safety_T *localDW)
{
  /* Start for MATLABSystem: '<S1>/Accelerometer' */
  localDW->obj.matlabCodegenIsDeleted = false;
  localDW->objisempty = true;
  localDW->obj.isInitialized = 1;
  INITIALIZE_ACCELEROMETER();
  localDW->obj.isSetupComplete = true;
}

/* Output and update for atomic system: */
void Child_Safety_Accelerometer(B_Accelerometer_Child_Safety_T *localB)
{
  real32_T out[3];

  /* MATLABSystem: '<S1>/Accelerometer' */
  out[0] = 0.0F;
  out[1] = 0.0F;
  out[2] = 0.0F;
  GET_ACCELEROMETER_DATA(&out[0], &out[1], &out[2]);

  /* MATLABSystem: '<S1>/Accelerometer' */
  localB->Accelerometer_o1 = out[0];

  /* MATLABSystem: '<S1>/Accelerometer' */
  localB->Accelerometer_o2 = out[1];

  /* MATLABSystem: '<S1>/Accelerometer' */
  localB->Accelerometer_o3 = out[2];
}

/* Termination for atomic system: */
void Child_Safety_Accelerometer_Term(DW_Accelerometer_Child_Safety_T *localDW)
{
  /* Terminate for MATLABSystem: '<S1>/Accelerometer' */
  if (!localDW->obj.matlabCodegenIsDeleted) {
    localDW->obj.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<S1>/Accelerometer' */
}

/* System initialize for atomic system: */
void Child_Safet_LocationSensor_Init(DW_LocationSensor_Child_Safet_T *localDW)
{
  /* Start for MATLABSystem: '<S8>/Location Sensor' */
  localDW->obj.matlabCodegenIsDeleted = false;
  localDW->objisempty = true;
  localDW->obj.isInitialized = 1;
  INIT_LOCATION_SENSOR();
  localDW->obj.isSetupComplete = true;
}

/* Output and update for atomic system: */
void Child_Safety_LocationSensor(B_LocationSensor_Child_Safety_T *localB)
{
  real_T out[3];

  /* MATLABSystem: '<S8>/Location Sensor' */
  out[0] = 0.0;
  out[1] = 0.0;
  out[2] = 0.0;
  GET_LOCATION_DATA(&out[0], &out[1], &out[2]);

  /* MATLABSystem: '<S8>/Location Sensor' */
  localB->LocationSensor_o1 = out[0];

  /* MATLABSystem: '<S8>/Location Sensor' */
  localB->LocationSensor_o2 = out[1];

  /* MATLABSystem: '<S8>/Location Sensor' */
  localB->LocationSensor_o3 = out[2];
}

/* Termination for atomic system: */
void Child_Safet_LocationSensor_Term(DW_LocationSensor_Child_Safet_T *localDW)
{
  /* Terminate for MATLABSystem: '<S8>/Location Sensor' */
  if (!localDW->obj.matlabCodegenIsDeleted) {
    localDW->obj.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<S8>/Location Sensor' */
}

real_T rt_atan2d_snf(real_T u0, real_T u1)
{
  real_T y;
  int32_T tmp;
  int32_T tmp_0;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = (rtNaN);
  } else if (rtIsInf(u0) && rtIsInf(u1)) {
    if (u0 > 0.0) {
      tmp = 1;
    } else {
      tmp = -1;
    }

    if (u1 > 0.0) {
      tmp_0 = 1;
    } else {
      tmp_0 = -1;
    }

    y = atan2(tmp, tmp_0);
  } else if (u1 == 0.0) {
    if (u0 > 0.0) {
      y = RT_PI / 2.0;
    } else if (u0 < 0.0) {
      y = -(RT_PI / 2.0);
    } else {
      y = 0.0;
    }
  } else {
    y = atan2(u0, u1);
  }

  return y;
}

/* Model step function */
void Child_Safety_step(void)
{
  real_T c_a;
  int32_T i;
  int32_T outData_tmp;
  char_T b_FormatStringTerminated[5];
  char_T b_FormatStringTerminated_0[5];
  boolean_T rtb_LogicalOperator;

  /* MATLABSystem: '<Root>/Audio File Read1' */
  memset(&Child_Safety_B.iv[0], 0, 8820U * sizeof(int16_T));
  i = Child_Safety_DW.obj.Idx;
  if (Child_Safety_DW.obj.Idx < 0) {
    i = 0;
  }

  READ_AUDIOFILE_DATA(4410U, 2U, &Child_Safety_B.iv[0], (uint32_T)i);
  Child_Safety_Accelerometer(&Child_Safety_B.Accelerometer_d);

  /* Logic: '<Root>/Logical Operator1' incorporates:
   *  Delay: '<Root>/Delay'
   *  MATLAB Function: '<Root>/MATLAB Function'
   */
  Child_Safety_DW.Delay_DSTATE = (((real32_T)sqrt
    ((Child_Safety_B.Accelerometer_d.Accelerometer_o1 *
      Child_Safety_B.Accelerometer_d.Accelerometer_o1 +
      Child_Safety_B.Accelerometer_d.Accelerometer_o2 *
      Child_Safety_B.Accelerometer_d.Accelerometer_o2) +
     Child_Safety_B.Accelerometer_d.Accelerometer_o3 *
     Child_Safety_B.Accelerometer_d.Accelerometer_o3) > 15.0F) ||
    Child_Safety_DW.Delay_DSTATE);
  Child_Safety_LocationSensor(&Child_Safety_B.LocationSensor_o);

  /* MATLAB Function: '<Root>/Distance Function' */
  Child_Safety_B.lat2_rad = 0.017453292519943295 *
    Child_Safety_B.LocationSensor_o.LocationSensor_o1;
  Child_Safety_B.b_a = sin((Child_Safety_B.lat2_rad - 0.40509800542464697) / 2.0);
  c_a = sin((0.017453292519943295 *
             Child_Safety_B.LocationSensor_o.LocationSensor_o2 -
             1.2685693364797344) / 2.0);
  Child_Safety_B.lat2_rad = 0.91906377677588924 * cos(Child_Safety_B.lat2_rad) *
    (c_a * c_a) + Child_Safety_B.b_a * Child_Safety_B.b_a;

  /* Logic: '<Root>/Logical Operator' incorporates:
   *  Delay: '<Root>/Delay'
   *  MATLAB Function: '<Root>/Distance Function'
   */
  rtb_LogicalOperator = (Child_Safety_DW.Delay_DSTATE || (rt_atan2d_snf(sqrt
    (Child_Safety_B.lat2_rad), sqrt(1.0 - Child_Safety_B.lat2_rad)) * 2.0 *
    6371.0 > 0.1));

  /* MATLABSystem: '<S4>/Audio Playback' */
  if (Child_Safety_DW.obj_m.SampleFreq !=
      Child_Safety_P.AudioPlayback_SampleFreq) {
    Child_Safety_DW.obj_m.SampleFreq = Child_Safety_P.AudioPlayback_SampleFreq;
  }

  for (i = 0; i < 4410; i++) {
    /* Switch: '<Root>/Switch1' incorporates:
     *  MATLABSystem: '<Root>/Audio File Read1'
     */
    if (rtb_LogicalOperator) {
      outData_tmp = i << 1;
      Child_Safety_B.outData[outData_tmp] = Child_Safety_B.iv[i];
      Child_Safety_B.outData[outData_tmp + 1] = Child_Safety_B.iv[i + 4410];
    } else {
      outData_tmp = i << 1;
      Child_Safety_B.outData[outData_tmp] = 0;
      Child_Safety_B.outData[outData_tmp + 1] = 0;
    }

    /* End of Switch: '<Root>/Switch1' */
  }

  AUDIO_PLAYBACK(&Child_Safety_B.outData[0], Child_Safety_DW.obj_m.FrameSize);

  /* End of MATLABSystem: '<S4>/Audio Playback' */
  Child_Safety_Accelerometer(&Child_Safety_B.Accelerometer);

  /* MATLABSystem: '<S12>/DataDisplay' incorporates:
   *  MATLABSystem: '<S10>/DataDisplay'
   *  MATLABSystem: '<S13>/DataDisplay'
   *  MATLABSystem: '<S14>/DataDisplay'
   *  MATLABSystem: '<S15>/DataDisplay'
   *  MATLABSystem: '<S16>/DataDisplay'
   *  MATLABSystem: '<S17>/DataDisplay'
   *  MATLABSystem: '<S3>/DataDisplay'
   *  MATLABSystem: '<S7>/DataDisplay'
   */
  Child_Safety_B.lat2_rad = Child_Safety_B.Accelerometer.Accelerometer_o1;
  b_FormatStringTerminated_0[0] = '%';
  b_FormatStringTerminated_0[1] = '.';
  b_FormatStringTerminated_0[2] = '6';
  b_FormatStringTerminated_0[3] = 'f';
  b_FormatStringTerminated_0[4] = '\x00';
  for (i = 0; i < 5; i++) {
    b_FormatStringTerminated[i] = b_FormatStringTerminated_0[i];
  }

  PUT_DATADISPLAY_DATA(&Child_Safety_B.lat2_rad, 4.0, 9, 1,
                       &b_FormatStringTerminated[0]);

  /* End of MATLABSystem: '<S12>/DataDisplay' */

  /* MATLABSystem: '<S14>/DataDisplay' */
  Child_Safety_B.lat2_rad = Child_Safety_B.Accelerometer.Accelerometer_o2;
  for (i = 0; i < 5; i++) {
    b_FormatStringTerminated[i] = b_FormatStringTerminated_0[i];
  }

  PUT_DATADISPLAY_DATA(&Child_Safety_B.lat2_rad, 6.0, 9, 1,
                       &b_FormatStringTerminated[0]);

  /* MATLABSystem: '<S16>/DataDisplay' */
  Child_Safety_B.lat2_rad = Child_Safety_B.Accelerometer.Accelerometer_o3;
  for (i = 0; i < 5; i++) {
    b_FormatStringTerminated[i] = b_FormatStringTerminated_0[i];
  }

  PUT_DATADISPLAY_DATA(&Child_Safety_B.lat2_rad, 8.0, 9, 1,
                       &b_FormatStringTerminated[0]);
  Child_Safety_LocationSensor(&Child_Safety_B.LocationSensor);

  /* MATLABSystem: '<S3>/DataDisplay' */
  for (i = 0; i < 5; i++) {
    b_FormatStringTerminated[i] = b_FormatStringTerminated_0[i];
  }

  PUT_DATADISPLAY_DATA(&Child_Safety_B.LocationSensor.LocationSensor_o3, 1.0, 9,
                       1, &b_FormatStringTerminated[0]);

  /* MATLABSystem: '<S7>/DataDisplay' */
  for (i = 0; i < 5; i++) {
    b_FormatStringTerminated[i] = b_FormatStringTerminated_0[i];
  }

  PUT_DATADISPLAY_DATA(&Child_Safety_B.LocationSensor.LocationSensor_o1, 2.0, 9,
                       1, &b_FormatStringTerminated[0]);

  /* MATLABSystem: '<S10>/DataDisplay' */
  for (i = 0; i < 5; i++) {
    b_FormatStringTerminated[i] = b_FormatStringTerminated_0[i];
  }

  PUT_DATADISPLAY_DATA(&Child_Safety_B.LocationSensor.LocationSensor_o2, 3.0, 9,
                       1, &b_FormatStringTerminated[0]);

  /* MATLABSystem: '<S6>/MATLAB System' */
  Child_Safety_B.out[0] = 0.0F;
  Child_Safety_B.out[1] = 0.0F;
  Child_Safety_B.out[2] = 0.0F;
  GET_GYROSCOPE_DATA(&Child_Safety_B.out[0], &Child_Safety_B.out[1],
                     &Child_Safety_B.out[2]);

  /* MATLABSystem: '<S13>/DataDisplay' incorporates:
   *  MATLABSystem: '<S6>/MATLAB System'
   */
  Child_Safety_B.lat2_rad = Child_Safety_B.out[0];
  for (i = 0; i < 5; i++) {
    b_FormatStringTerminated[i] = b_FormatStringTerminated_0[i];
  }

  PUT_DATADISPLAY_DATA(&Child_Safety_B.lat2_rad, 5.0, 9, 1,
                       &b_FormatStringTerminated[0]);

  /* MATLABSystem: '<S15>/DataDisplay' incorporates:
   *  MATLABSystem: '<S6>/MATLAB System'
   */
  Child_Safety_B.lat2_rad = Child_Safety_B.out[1];
  for (i = 0; i < 5; i++) {
    b_FormatStringTerminated[i] = b_FormatStringTerminated_0[i];
  }

  PUT_DATADISPLAY_DATA(&Child_Safety_B.lat2_rad, 7.0, 9, 1,
                       &b_FormatStringTerminated[0]);

  /* MATLABSystem: '<S17>/DataDisplay' incorporates:
   *  MATLABSystem: '<S6>/MATLAB System'
   */
  Child_Safety_B.lat2_rad = Child_Safety_B.out[2];
  PUT_DATADISPLAY_DATA(&Child_Safety_B.lat2_rad, 9.0, 9, 1,
                       &b_FormatStringTerminated_0[0]);
}

/* Model initialize function */
void Child_Safety_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  {
    int32_T i;
    char_T b[34];
    char_T c[4];
    char_T obj;
    static const char_T tmp[33] = { 'm', 'i', 'x', 'k', 'i', 't', 'c', 'e', 'n',
      's', 'o', 'r', 's', 'h', 'i', 'p', 'b', 'e', 'e', 'p', '1', '0', '8', '2',
      'm', 'p', '3', 'c', 'u', 't', 'n', 'e', 't' };

    /* InitializeConditions for Delay: '<Root>/Delay' */
    Child_Safety_DW.Delay_DSTATE = Child_Safety_P.Delay_InitialCondition;

    /* Start for MATLABSystem: '<Root>/Audio File Read1' */
    Child_Safety_DW.obj.matlabCodegenIsDeleted = false;
    Child_Safety_DW.obj.FExt[0] = 'w';
    Child_Safety_DW.obj.FExt[1] = 'a';
    Child_Safety_DW.obj.FExt[2] = 'v';
    Child_Safety_DW.obj.FExt[3] = '\x00';
    Child_Safety_DW.obj.isInitialized = 1;
    for (i = 0; i < 33; i++) {
      obj = tmp[i];
      Child_Safety_DW.obj.RName[i] = obj;
      b[i] = obj;
    }

    b[33] = '\x00';
    c[0] = Child_Safety_DW.obj.FExt[0];
    c[1] = Child_Safety_DW.obj.FExt[1];
    c[2] = Child_Safety_DW.obj.FExt[2];
    c[3] = Child_Safety_DW.obj.FExt[3];
    INITIALIZE_AUDIOFILEREAD(&b[0], &c[0], 4410U, &Child_Safety_DW.obj.Idx);
    Child_Safety_DW.obj.isSetupComplete = true;

    /* End of Start for MATLABSystem: '<Root>/Audio File Read1' */
    Child_Safety_Accelerometer_Init(&Child_Safety_DW.Accelerometer_d);
    Child_Safet_LocationSensor_Init(&Child_Safety_DW.LocationSensor_o);

    /* Start for MATLABSystem: '<S4>/Audio Playback' */
    Child_Safety_DW.obj_m.matlabCodegenIsDeleted = false;
    Child_Safety_DW.obj_m.SampleFreq = Child_Safety_P.AudioPlayback_SampleFreq;
    Child_Safety_DW.obj_m.isInitialized = 1;
    Child_Safety_DW.obj_m.FrameSize = 4410.0;
    INIT_AUDIO_PLAYBACK(Child_Safety_DW.obj_m.SampleFreq,
                        Child_Safety_DW.obj_m.FrameSize);
    Child_Safety_DW.obj_m.isSetupComplete = true;
    Child_Safety_Accelerometer_Init(&Child_Safety_DW.Accelerometer);

    /* Start for MATLABSystem: '<S12>/DataDisplay' */
    INITIALIZE_DATADISPLAY();

    /* Start for MATLABSystem: '<S14>/DataDisplay' */
    INITIALIZE_DATADISPLAY();

    /* Start for MATLABSystem: '<S16>/DataDisplay' */
    INITIALIZE_DATADISPLAY();
    Child_Safet_LocationSensor_Init(&Child_Safety_DW.LocationSensor);

    /* Start for MATLABSystem: '<S3>/DataDisplay' */
    INITIALIZE_DATADISPLAY();

    /* Start for MATLABSystem: '<S7>/DataDisplay' */
    INITIALIZE_DATADISPLAY();

    /* Start for MATLABSystem: '<S10>/DataDisplay' */
    INITIALIZE_DATADISPLAY();

    /* Start for MATLABSystem: '<S6>/MATLAB System' */
    Child_Safety_DW.obj_i.matlabCodegenIsDeleted = false;
    Child_Safety_DW.obj_i.isInitialized = 1;
    INITIALIZE_GYROSCOPE();
    Child_Safety_DW.obj_i.isSetupComplete = true;

    /* Start for MATLABSystem: '<S13>/DataDisplay' */
    INITIALIZE_DATADISPLAY();

    /* Start for MATLABSystem: '<S15>/DataDisplay' */
    INITIALIZE_DATADISPLAY();

    /* Start for MATLABSystem: '<S17>/DataDisplay' */
    INITIALIZE_DATADISPLAY();
  }
}

/* Model terminate function */
void Child_Safety_terminate(void)
{
  int32_T tmp;

  /* Terminate for MATLABSystem: '<Root>/Audio File Read1' */
  if (!Child_Safety_DW.obj.matlabCodegenIsDeleted) {
    Child_Safety_DW.obj.matlabCodegenIsDeleted = true;
    if ((Child_Safety_DW.obj.isInitialized == 1) &&
        Child_Safety_DW.obj.isSetupComplete) {
      tmp = Child_Safety_DW.obj.Idx;
      if (Child_Safety_DW.obj.Idx < 0) {
        tmp = 0;
      }

      TERMINATE_AUDIOFILEREAD((uint32_T)tmp);
    }
  }

  /* End of Terminate for MATLABSystem: '<Root>/Audio File Read1' */
  Child_Safety_Accelerometer_Term(&Child_Safety_DW.Accelerometer_d);
  Child_Safet_LocationSensor_Term(&Child_Safety_DW.LocationSensor_o);

  /* Terminate for MATLABSystem: '<S4>/Audio Playback' */
  if (!Child_Safety_DW.obj_m.matlabCodegenIsDeleted) {
    Child_Safety_DW.obj_m.matlabCodegenIsDeleted = true;
    if ((Child_Safety_DW.obj_m.isInitialized == 1) &&
        Child_Safety_DW.obj_m.isSetupComplete) {
      TERMINATE_AUDIO_PLAYBACK();
    }
  }

  /* End of Terminate for MATLABSystem: '<S4>/Audio Playback' */
  Child_Safety_Accelerometer_Term(&Child_Safety_DW.Accelerometer);
  Child_Safet_LocationSensor_Term(&Child_Safety_DW.LocationSensor);

  /* Terminate for MATLABSystem: '<S6>/MATLAB System' */
  if (!Child_Safety_DW.obj_i.matlabCodegenIsDeleted) {
    Child_Safety_DW.obj_i.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<S6>/MATLAB System' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
