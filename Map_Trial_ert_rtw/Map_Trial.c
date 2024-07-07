/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Map_Trial.c
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

#include "Map_Trial.h"
#include "rtwtypes.h"
#include <math.h>
#include <string.h>
#include "Map_Trial_private.h"

/* Block signals (default storage) */
B_Map_Trial_T Map_Trial_B;

/* Block states (default storage) */
DW_Map_Trial_T Map_Trial_DW;

/* Real-time model */
static RT_MODEL_Map_Trial_T Map_Trial_M_;
RT_MODEL_Map_Trial_T *const Map_Trial_M = &Map_Trial_M_;
real_T rt_roundd_snf(real_T u)
{
  real_T y;
  if (fabs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = floor(u + 0.5);
    } else if (u > -0.5) {
      y = u * 0.0;
    } else {
      y = ceil(u - 0.5);
    }
  } else {
    y = u;
  }

  return y;
}

/* Model step function */
void Map_Trial_step(void)
{
  real_T dy;
  real_T rtb_dr;
  real_T tmp;
  int32_T b;
  int32_T b_idx_1;
  int32_T d;
  int32_T e;
  int32_T i;
  int16_T colend;
  int16_T colstart;
  int16_T rend;
  int16_T rstart;
  char_T b_FormatStringTerminated[5];
  char_T b_FormatStringTerminated_0[5];

  /* MATLABSystem: '<S2>/Location Sensor' */
  Map_Trial_B.out[0] = 0.0;
  Map_Trial_B.out[1] = 0.0;
  Map_Trial_B.out[2] = 0.0;
  GET_LOCATION_DATA(&Map_Trial_B.out[0], &Map_Trial_B.out[1], &Map_Trial_B.out[2]);

  /* MATLABSystem: '<S1>/DataDisplay' incorporates:
   *  MATLABSystem: '<S10>/DataDisplay'
   *  MATLABSystem: '<S11>/DataDisplay'
   *  MATLABSystem: '<S12>/DataDisplay'
   *  MATLABSystem: '<S2>/Location Sensor'
   *  MATLABSystem: '<S3>/DataDisplay'
   */
  b_FormatStringTerminated_0[0] = '%';
  b_FormatStringTerminated_0[1] = '.';
  b_FormatStringTerminated_0[2] = '6';
  b_FormatStringTerminated_0[3] = 'f';
  b_FormatStringTerminated_0[4] = '\x00';
  for (d = 0; d < 5; d++) {
    b_FormatStringTerminated[d] = b_FormatStringTerminated_0[d];
  }

  PUT_DATADISPLAY_DATA(&Map_Trial_B.out[0], 1.0, 9, 1,
                       &b_FormatStringTerminated[0]);

  /* End of MATLABSystem: '<S1>/DataDisplay' */

  /* MATLABSystem: '<S3>/DataDisplay' incorporates:
   *  MATLABSystem: '<S2>/Location Sensor'
   */
  for (d = 0; d < 5; d++) {
    b_FormatStringTerminated[d] = b_FormatStringTerminated_0[d];
  }

  PUT_DATADISPLAY_DATA(&Map_Trial_B.out[1], 2.0, 9, 1,
                       &b_FormatStringTerminated[0]);

  /* MATLAB Function: '<Root>/MATLAB Function9' incorporates:
   *  MATLABSystem: '<S2>/Location Sensor'
   */
  Map_Trial_B.dx = (Map_Trial_B.out[1] - 72.683671) * 102200.0;
  dy = (Map_Trial_B.out[0] - 23.210461) * 111200.0;
  rtb_dr = sqrt(Map_Trial_B.dx * Map_Trial_B.dx + dy * dy);

  /* MATLAB Function: '<Root>/MATLAB Function6' incorporates:
   *  Constant: '<Root>/B'
   *  Constant: '<Root>/G'
   *  Constant: '<Root>/R'
   */
  memcpy(&Map_Trial_B.RMU[0], &Map_Trial_P.R_Value[0], 576232U * sizeof(uint8_T));
  memcpy(&Map_Trial_B.GMU[0], &Map_Trial_P.G_Value[0], 576232U * sizeof(uint8_T));
  memcpy(&Map_Trial_B.BMU[0], &Map_Trial_P.B_Value[0], 576232U * sizeof(uint8_T));

  /* MATLAB Function: '<Root>/MATLAB Function9' incorporates:
   *  MATLABSystem: '<S2>/Location Sensor'
   */
  tmp = rt_roundd_snf((Map_Trial_B.out[0] - 23.210461) * 36000.0);
  if (tmp < 32768.0) {
    if (tmp >= -32768.0) {
      rstart = (int16_T)tmp;
    } else {
      rstart = MIN_int16_T;
    }
  } else {
    rstart = MAX_int16_T;
  }

  /* MATLAB Function: '<Root>/MATLAB Function6' incorporates:
   *  MATLAB Function: '<Root>/MATLAB Function9'
   */
  d = rstart + 323;

  /* MATLAB Function: '<Root>/MATLAB Function9' */
  if (tmp < 32768.0) {
    if (tmp >= -32768.0) {
      rstart = (int16_T)tmp;
    } else {
      rstart = MIN_int16_T;
    }
  } else {
    rstart = MAX_int16_T;
  }

  /* MATLAB Function: '<Root>/MATLAB Function6' incorporates:
   *  MATLAB Function: '<Root>/MATLAB Function9'
   */
  if (rstart + 323 > 32767) {
    d = 32767;
  }

  /* MATLAB Function: '<Root>/MATLAB Function9' incorporates:
   *  MATLABSystem: '<S2>/Location Sensor'
   */
  tmp = rt_roundd_snf((Map_Trial_B.out[1] - 72.683671) * 45600.0);
  if (tmp < 32768.0) {
    if (tmp >= -32768.0) {
      rstart = (int16_T)tmp;
    } else {
      rstart = MIN_int16_T;
    }
  } else {
    rstart = MAX_int16_T;
  }

  /* MATLAB Function: '<Root>/MATLAB Function6' incorporates:
   *  MATLAB Function: '<Root>/MATLAB Function9'
   */
  b = rstart + 446;

  /* MATLAB Function: '<Root>/MATLAB Function9' */
  if (tmp < 32768.0) {
    if (tmp >= -32768.0) {
      rstart = (int16_T)tmp;
    } else {
      rstart = MIN_int16_T;
    }
  } else {
    rstart = MAX_int16_T;
  }

  /* MATLAB Function: '<Root>/MATLAB Function6' incorporates:
   *  MATLAB Function: '<Root>/MATLAB Function9'
   */
  if (rstart + 446 > 32767) {
    b = 32767;
  }

  i = (int16_T)d + 5;
  if ((int16_T)d + 5 > 32767) {
    i = 32767;
  }

  e = (int16_T)b + 5;
  if ((int16_T)b + 5 > 32767) {
    e = 32767;
  }

  if ((int16_T)d - 5 > 1) {
    rstart = (int16_T)((int16_T)d - 5);
  } else {
    rstart = 1;
  }

  if ((int16_T)i < 646) {
    rend = (int16_T)i;
  } else {
    rend = 646;
  }

  if ((int16_T)b - 5 > 1) {
    colstart = (int16_T)((int16_T)b - 5);
  } else {
    colstart = 1;
  }

  if ((int16_T)e < 892) {
    colend = (int16_T)e;
  } else {
    colend = 892;
  }

  if (rstart > rend) {
    i = 0;
    b = 0;
  } else {
    i = rstart - 1;
    b = rend;
  }

  if (colstart > colend) {
    e = 0;
    d = 0;
  } else {
    e = colstart - 1;
    d = colend;
  }

  b -= i;
  b_idx_1 = d - e;
  for (d = 0; d < b_idx_1; d++) {
    if (b - 1 >= 0) {
      memset(&Map_Trial_B.RMU[d * 646 + (i + e * 646)], 0, (uint32_T)((((b + i)
                + e * 646) - i) - e * 646) * sizeof(uint8_T));
    }
  }

  if (rstart > rend) {
    e = 0;
    b = 0;
  } else {
    e = rstart - 1;
    b = rend;
  }

  if (colstart > colend) {
    i = 0;
    d = 0;
  } else {
    i = colstart - 1;
    d = colend;
  }

  b -= e;
  b_idx_1 = d - i;
  for (d = 0; d < b_idx_1; d++) {
    if (b - 1 >= 0) {
      memset(&Map_Trial_B.GMU[d * 646 + (e + i * 646)], 0, (uint32_T)((((b + e)
                + i * 646) - e) - i * 646) * sizeof(uint8_T));
    }
  }

  if (rstart > rend) {
    i = 0;
    b = 0;
  } else {
    i = rstart - 1;
    b = rend;
  }

  if (colstart > colend) {
    e = 0;
    d = 0;
  } else {
    e = colstart - 1;
    d = colend;
  }

  b -= i;
  b_idx_1 = d - e;
  for (d = 0; d < b_idx_1; d++) {
    if (b - 1 >= 0) {
      memset(&Map_Trial_B.BMU[d * 646 + (i + e * 646)], 255, (uint32_T)((((b + i)
                + e * 646) - i) - e * 646) * sizeof(uint8_T));
    }
  }

  /* MATLABSystem: '<S9>/Video Display' */
  PUT_VIDEO_DISPLAY_DATA(&Map_Trial_B.RMU[0], &Map_Trial_B.GMU[0],
    &Map_Trial_B.BMU[0]);

  /* MATLABSystem: '<S10>/DataDisplay' */
  for (d = 0; d < 5; d++) {
    b_FormatStringTerminated[d] = b_FormatStringTerminated_0[d];
  }

  PUT_DATADISPLAY_DATA(&rtb_dr, 3.0, 9, 1, &b_FormatStringTerminated[0]);

  /* MATLABSystem: '<S11>/DataDisplay' incorporates:
   *  MATLAB Function: '<Root>/MATLAB Function9'
   */
  for (d = 0; d < 5; d++) {
    b_FormatStringTerminated[d] = b_FormatStringTerminated_0[d];
  }

  PUT_DATADISPLAY_DATA(&Map_Trial_B.dx, 4.0, 9, 1, &b_FormatStringTerminated[0]);

  /* MATLABSystem: '<S12>/DataDisplay' incorporates:
   *  MATLAB Function: '<Root>/MATLAB Function9'
   */
  PUT_DATADISPLAY_DATA(&dy, 5.0, 9, 1, &b_FormatStringTerminated_0[0]);
}

/* Model initialize function */
void Map_Trial_initialize(void)
{
  /* Start for MATLABSystem: '<S2>/Location Sensor' */
  Map_Trial_DW.obj.matlabCodegenIsDeleted = false;
  Map_Trial_DW.obj.isInitialized = 1;
  INIT_LOCATION_SENSOR();
  Map_Trial_DW.obj.isSetupComplete = true;

  /* Start for MATLABSystem: '<S1>/DataDisplay' */
  INITIALIZE_DATADISPLAY();

  /* Start for MATLABSystem: '<S3>/DataDisplay' */
  INITIALIZE_DATADISPLAY();

  /* Start for MATLABSystem: '<S9>/Video Display' */
  INITIALIZE_VIDEO_DISPLAY(646, 892);

  /* Start for MATLABSystem: '<S10>/DataDisplay' */
  INITIALIZE_DATADISPLAY();

  /* Start for MATLABSystem: '<S11>/DataDisplay' */
  INITIALIZE_DATADISPLAY();

  /* Start for MATLABSystem: '<S12>/DataDisplay' */
  INITIALIZE_DATADISPLAY();
}

/* Model terminate function */
void Map_Trial_terminate(void)
{
  /* Terminate for MATLABSystem: '<S2>/Location Sensor' */
  if (!Map_Trial_DW.obj.matlabCodegenIsDeleted) {
    Map_Trial_DW.obj.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<S2>/Location Sensor' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
