/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Parent_Mobile.c
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

#include "Parent_Mobile.h"
#include "rtwtypes.h"
#include "Parent_Mobile_types.h"
#include "Parent_Mobile_private.h"
#include <string.h>
#include <math.h>

/* Block signals (default storage) */
B_Parent_Mobile_T Parent_Mobile_B;

/* Block states (default storage) */
DW_Parent_Mobile_T Parent_Mobile_DW;

/* Real-time model */
static RT_MODEL_Parent_Mobile_T Parent_Mobile_M_;
RT_MODEL_Parent_Mobile_T *const Parent_Mobile_M = &Parent_Mobile_M_;

/* Forward declaration for local functions */
static void Parent_Mobile_SystemCore_setup(codertarget_internal_androidT_T *obj);
static void Parent_Mobil_SystemCore_setup_b(codertarget_internal_androidT_T *obj);
static void Parent_Mobi_SystemCore_setup_by(codertarget_internal_androidT_T *obj);
static void rate_scheduler(void);

/*
 *         This function updates active task flag for each subrate.
 *         The function is called at model base rate, hence the
 *         generated code self-manages all its subrates.
 */
static void rate_scheduler(void)
{
  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (Parent_Mobile_M->Timing.TaskCounters.TID[1])++;
  if ((Parent_Mobile_M->Timing.TaskCounters.TID[1]) > 19) {/* Sample time: [2.0s, 0.0s] */
    Parent_Mobile_M->Timing.TaskCounters.TID[1] = 0;
  }
}

/*
 * Output and update for atomic system:
 *    '<Root>/MATLAB Function2'
 *    '<Root>/MATLAB Function3'
 *    '<Root>/MATLAB Function4'
 */
void Parent_Mobile_MATLABFunction2(const uint8_T rtu_u[76800], real32_T rtu_v,
  uint8_T rty_y[76800])
{
  int32_T i;
  for (i = 0; i < 76800; i++) {
    if (rtu_v == 0.0F) {
      rty_y[i] = 0U;
    } else {
      rty_y[i] = rtu_u[i];
    }
  }
}

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

static void Parent_Mobile_SystemCore_setup(codertarget_internal_androidT_T *obj)
{
  real_T tmp;
  int32_T i;
  int16_T errorNo;
  uint16_T tmp_0;
  char_T b_str_data[11];
  char_T ipaddr[11];
  uint8_T isLittleEndian;
  static const char_T tmp_1[11] = "10.7.2.217";
  int32_T str_size_idx_1;
  obj->isInitialized = 1;
  errorNo = obj->errorNo_;
  obj->isServer_ = 0.0;
  for (i = 0; i < 11; i++) {
    ipaddr[i] = tmp_1[i];
  }

  tmp = rt_roundd_snf(obj->isServer_);
  if (tmp < 65536.0) {
    if (tmp >= 0.0) {
      tmp_0 = (uint16_T)tmp;
    } else {
      tmp_0 = 0U;
    }
  } else {
    tmp_0 = MAX_uint16_T;
  }

  TCPStreamSetup(39152, 0, &obj->connStream_, tmp_0, 0.0, &obj->errorNo_,
                 &ipaddr[0]);
  littleEndianCheck(&isLittleEndian);
  if ((errorNo != obj->errorNo_) && (obj->errorNo_ > 0) && (obj->errorNo_ < 10))
  {
    str_size_idx_1 = 1;
    ipaddr[0] = '\x00';
    if (obj->errorNo_ == 4) {
      UPDATE_TCP_LOGI(obj->errorNo_, 1.0, 1, MAX_int16_T);
    } else {
      if (obj->errorNo_ == 5) {
        str_size_idx_1 = 11;
        for (i = 0; i < 11; i++) {
          ipaddr[i] = tmp_1[i];
        }
      }

      memcpy(&b_str_data[0], &ipaddr[0], (uint32_T)str_size_idx_1 * sizeof
             (char_T));
      UPDATE_TCP_LOGS(obj->errorNo_, 1.0, 1, &b_str_data[0]);
    }
  }
}

static void Parent_Mobil_SystemCore_setup_b(codertarget_internal_androidT_T *obj)
{
  real_T tmp;
  int32_T i;
  int16_T errorNo;
  uint16_T tmp_0;
  char_T b_str_data[11];
  char_T ipaddr[11];
  uint8_T isLittleEndian;
  static const char_T tmp_1[11] = "10.7.2.217";
  int32_T str_size_idx_1;
  obj->isInitialized = 1;
  errorNo = obj->errorNo_;
  obj->isServer_ = 0.0;
  for (i = 0; i < 11; i++) {
    ipaddr[i] = tmp_1[i];
  }

  tmp = rt_roundd_snf(obj->isServer_);
  if (tmp < 65536.0) {
    if (tmp >= 0.0) {
      tmp_0 = (uint16_T)tmp;
    } else {
      tmp_0 = 0U;
    }
  } else {
    tmp_0 = MAX_uint16_T;
  }

  TCPStreamSetup(39153, 0, &obj->connStream_, tmp_0, 0.0, &obj->errorNo_,
                 &ipaddr[0]);
  littleEndianCheck(&isLittleEndian);
  if ((errorNo != obj->errorNo_) && (obj->errorNo_ > 0) && (obj->errorNo_ < 10))
  {
    str_size_idx_1 = 1;
    ipaddr[0] = '\x00';
    if (obj->errorNo_ == 4) {
      UPDATE_TCP_LOGI(obj->errorNo_, 2.0, 1, MAX_int16_T);
    } else {
      if (obj->errorNo_ == 5) {
        str_size_idx_1 = 11;
        for (i = 0; i < 11; i++) {
          ipaddr[i] = tmp_1[i];
        }
      }

      memcpy(&b_str_data[0], &ipaddr[0], (uint32_T)str_size_idx_1 * sizeof
             (char_T));
      UPDATE_TCP_LOGS(obj->errorNo_, 2.0, 1, &b_str_data[0]);
    }
  }
}

static void Parent_Mobi_SystemCore_setup_by(codertarget_internal_androidT_T *obj)
{
  real_T tmp;
  int32_T i;
  int16_T errorNo;
  uint16_T tmp_0;
  char_T b_str_data[11];
  char_T ipaddr[11];
  uint8_T isLittleEndian;
  static const char_T tmp_1[11] = "10.7.2.217";
  int32_T str_size_idx_1;
  obj->isInitialized = 1;
  errorNo = obj->errorNo_;
  obj->isServer_ = 0.0;
  for (i = 0; i < 11; i++) {
    ipaddr[i] = tmp_1[i];
  }

  tmp = rt_roundd_snf(obj->isServer_);
  if (tmp < 65536.0) {
    if (tmp >= 0.0) {
      tmp_0 = (uint16_T)tmp;
    } else {
      tmp_0 = 0U;
    }
  } else {
    tmp_0 = MAX_uint16_T;
  }

  TCPStreamSetup(39154, 0, &obj->connStream_, tmp_0, 0.0, &obj->errorNo_,
                 &ipaddr[0]);
  littleEndianCheck(&isLittleEndian);
  if ((errorNo != obj->errorNo_) && (obj->errorNo_ > 0) && (obj->errorNo_ < 10))
  {
    str_size_idx_1 = 1;
    ipaddr[0] = '\x00';
    if (obj->errorNo_ == 4) {
      UPDATE_TCP_LOGI(obj->errorNo_, 3.0, 1, MAX_int16_T);
    } else {
      if (obj->errorNo_ == 5) {
        str_size_idx_1 = 11;
        for (i = 0; i < 11; i++) {
          ipaddr[i] = tmp_1[i];
        }
      }

      memcpy(&b_str_data[0], &ipaddr[0], (uint32_T)str_size_idx_1 * sizeof
             (char_T));
      UPDATE_TCP_LOGS(obj->errorNo_, 3.0, 1, &b_str_data[0]);
    }
  }
}

/* Model step function */
void Parent_Mobile_step(void)
{
  int32_T i;
  int32_T samplesRead;
  int32_T samplesRead_0;
  int32_T samplesRead_1;
  int32_T samplesRead_2;
  int32_T samplesRead_3;
  int32_T samplesRead_4;
  int16_T errorNo;
  uint16_T tmp;
  char_T b_FormatStringTerminated[5];
  char_T b_FormatStringTerminated_0[5];
  char_T *sErr;
  int8_T b_status;
  static const char_T tmp_0[11] = "10.7.2.217";
  int32_T str_size_idx_1;
  if (Parent_Mobile_M->Timing.TaskCounters.TID[1] == 0) {
    /* MATLABSystem: '<Root>/TCP//IP Receive4' */
    errorNo = Parent_Mobile_DW.obj_n.errorNo_;
    Parent_Mobile_B.u0 = rt_roundd_snf(Parent_Mobile_DW.obj_n.isServer_);
    if (Parent_Mobile_B.u0 < 65536.0) {
      if (Parent_Mobile_B.u0 >= 0.0) {
        tmp = (uint16_T)Parent_Mobile_B.u0;
      } else {
        tmp = 0U;
      }
    } else {
      tmp = MAX_uint16_T;
    }

    TCPStreamStepRecv(&Parent_Mobile_B.TCPIPReceive4_o1[0], &b_status,
                      MAX_uint16_T, Parent_Mobile_DW.obj_n.connStream_,
                      &Parent_Mobile_DW.obj_n.errorNo_, tmp);
    if ((errorNo != Parent_Mobile_DW.obj_n.errorNo_) &&
        (Parent_Mobile_DW.obj_n.errorNo_ > 0) &&
        (Parent_Mobile_DW.obj_n.errorNo_ < 10)) {
      str_size_idx_1 = 1;
      Parent_Mobile_B.str_data[0] = '\x00';
      if (Parent_Mobile_DW.obj_n.errorNo_ == 4) {
        UPDATE_TCP_LOGI(Parent_Mobile_DW.obj_n.errorNo_, 1.0, 1, MAX_int16_T);
      } else {
        if (Parent_Mobile_DW.obj_n.errorNo_ == 5) {
          str_size_idx_1 = 11;
          for (i = 0; i < 11; i++) {
            Parent_Mobile_B.str_data[i] = tmp_0[i];
          }
        }

        memcpy(&Parent_Mobile_B.b_str_data[0], &Parent_Mobile_B.str_data[0],
               (uint32_T)str_size_idx_1 * sizeof(char_T));
        UPDATE_TCP_LOGS(Parent_Mobile_DW.obj_n.errorNo_, 1.0, 1,
                        &Parent_Mobile_B.b_str_data[0]);
      }
    }

    /* End of MATLABSystem: '<Root>/TCP//IP Receive4' */
  }

  /* S-Function (sdspFromNetwork): '<Root>/UDP Receive' */
  sErr = GetErrorBuffer(&Parent_Mobile_DW.UDPReceive_NetworkLib[0U]);
  samplesRead = 4410;
  LibOutputs_Network(&Parent_Mobile_DW.UDPReceive_NetworkLib[0U],
                     &Parent_Mobile_B.UDPReceive_o1[0U], &samplesRead);
  if (*sErr != 0) {
    rtmSetErrorStatus(Parent_Mobile_M, sErr);
    rtmSetStopRequested(Parent_Mobile_M, 1);
  }

  /* End of S-Function (sdspFromNetwork): '<Root>/UDP Receive' */

  /* S-Function (sdspFromNetwork): '<Root>/UDP Receive1' */
  sErr = GetErrorBuffer(&Parent_Mobile_DW.UDPReceive1_NetworkLib[0U]);
  samplesRead_0 = 4410;
  LibOutputs_Network(&Parent_Mobile_DW.UDPReceive1_NetworkLib[0U],
                     &Parent_Mobile_B.UDPReceive1_o1[0U], &samplesRead_0);
  if (*sErr != 0) {
    rtmSetErrorStatus(Parent_Mobile_M, sErr);
    rtmSetStopRequested(Parent_Mobile_M, 1);
  }

  /* End of S-Function (sdspFromNetwork): '<Root>/UDP Receive1' */

  /* S-Function (sdspFromNetwork): '<Root>/UDP Receive4' */
  sErr = GetErrorBuffer(&Parent_Mobile_DW.UDPReceive4_NetworkLib[0U]);
  samplesRead_1 = 1;
  LibOutputs_Network(&Parent_Mobile_DW.UDPReceive4_NetworkLib[0U],
                     &Parent_Mobile_B.UDPReceive4_o1, &samplesRead_1);
  if (*sErr != 0) {
    rtmSetErrorStatus(Parent_Mobile_M, sErr);
    rtmSetStopRequested(Parent_Mobile_M, 1);
  }

  /* End of S-Function (sdspFromNetwork): '<Root>/UDP Receive4' */

  /* MATLAB Function: '<Root>/MATLAB Function2' */
  Parent_Mobile_MATLABFunction2(Parent_Mobile_B.TCPIPReceive4_o1,
    Parent_Mobile_B.UDPReceive4_o1, Parent_Mobile_B.y_c);
  if (Parent_Mobile_M->Timing.TaskCounters.TID[1] == 0) {
    /* MATLABSystem: '<Root>/TCP//IP Receive5' */
    errorNo = Parent_Mobile_DW.obj_a.errorNo_;
    Parent_Mobile_B.u0 = rt_roundd_snf(Parent_Mobile_DW.obj_a.isServer_);
    if (Parent_Mobile_B.u0 < 65536.0) {
      if (Parent_Mobile_B.u0 >= 0.0) {
        tmp = (uint16_T)Parent_Mobile_B.u0;
      } else {
        tmp = 0U;
      }
    } else {
      tmp = MAX_uint16_T;
    }

    TCPStreamStepRecv(&Parent_Mobile_B.TCPIPReceive5_o1[0], &b_status,
                      MAX_uint16_T, Parent_Mobile_DW.obj_a.connStream_,
                      &Parent_Mobile_DW.obj_a.errorNo_, tmp);
    if ((errorNo != Parent_Mobile_DW.obj_a.errorNo_) &&
        (Parent_Mobile_DW.obj_a.errorNo_ > 0) &&
        (Parent_Mobile_DW.obj_a.errorNo_ < 10)) {
      str_size_idx_1 = 1;
      Parent_Mobile_B.str_data[0] = '\x00';
      if (Parent_Mobile_DW.obj_a.errorNo_ == 4) {
        UPDATE_TCP_LOGI(Parent_Mobile_DW.obj_a.errorNo_, 2.0, 1, MAX_int16_T);
      } else {
        if (Parent_Mobile_DW.obj_a.errorNo_ == 5) {
          str_size_idx_1 = 11;
          for (i = 0; i < 11; i++) {
            Parent_Mobile_B.str_data[i] = tmp_0[i];
          }
        }

        memcpy(&Parent_Mobile_B.b_str_data[0], &Parent_Mobile_B.str_data[0],
               (uint32_T)str_size_idx_1 * sizeof(char_T));
        UPDATE_TCP_LOGS(Parent_Mobile_DW.obj_a.errorNo_, 2.0, 1,
                        &Parent_Mobile_B.b_str_data[0]);
      }
    }

    /* End of MATLABSystem: '<Root>/TCP//IP Receive5' */
  }

  /* MATLAB Function: '<Root>/MATLAB Function4' */
  Parent_Mobile_MATLABFunction2(Parent_Mobile_B.TCPIPReceive5_o1,
    Parent_Mobile_B.UDPReceive4_o1, Parent_Mobile_B.y_j);
  if (Parent_Mobile_M->Timing.TaskCounters.TID[1] == 0) {
    /* MATLABSystem: '<Root>/TCP//IP Receive6' */
    errorNo = Parent_Mobile_DW.obj_c.errorNo_;
    Parent_Mobile_B.u0 = rt_roundd_snf(Parent_Mobile_DW.obj_c.isServer_);
    if (Parent_Mobile_B.u0 < 65536.0) {
      if (Parent_Mobile_B.u0 >= 0.0) {
        tmp = (uint16_T)Parent_Mobile_B.u0;
      } else {
        tmp = 0U;
      }
    } else {
      tmp = MAX_uint16_T;
    }

    TCPStreamStepRecv(&Parent_Mobile_B.TCPIPReceive6_o1[0], &b_status,
                      MAX_uint16_T, Parent_Mobile_DW.obj_c.connStream_,
                      &Parent_Mobile_DW.obj_c.errorNo_, tmp);
    if ((errorNo != Parent_Mobile_DW.obj_c.errorNo_) &&
        (Parent_Mobile_DW.obj_c.errorNo_ > 0) &&
        (Parent_Mobile_DW.obj_c.errorNo_ < 10)) {
      str_size_idx_1 = 1;
      Parent_Mobile_B.str_data[0] = '\x00';
      if (Parent_Mobile_DW.obj_c.errorNo_ == 4) {
        UPDATE_TCP_LOGI(Parent_Mobile_DW.obj_c.errorNo_, 3.0, 1, MAX_int16_T);
      } else {
        if (Parent_Mobile_DW.obj_c.errorNo_ == 5) {
          str_size_idx_1 = 11;
          for (i = 0; i < 11; i++) {
            Parent_Mobile_B.str_data[i] = tmp_0[i];
          }
        }

        memcpy(&Parent_Mobile_B.b_str_data[0], &Parent_Mobile_B.str_data[0],
               (uint32_T)str_size_idx_1 * sizeof(char_T));
        UPDATE_TCP_LOGS(Parent_Mobile_DW.obj_c.errorNo_, 3.0, 1,
                        &Parent_Mobile_B.b_str_data[0]);
      }
    }

    /* End of MATLABSystem: '<Root>/TCP//IP Receive6' */
  }

  /* MATLAB Function: '<Root>/MATLAB Function3' */
  Parent_Mobile_MATLABFunction2(Parent_Mobile_B.TCPIPReceive6_o1,
    Parent_Mobile_B.UDPReceive4_o1, Parent_Mobile_B.y_p);

  /* MATLABSystem: '<S9>/Video Display' */
  PUT_VIDEO_DISPLAY_DATA(&Parent_Mobile_B.y_c[0], &Parent_Mobile_B.y_j[0],
    &Parent_Mobile_B.y_p[0]);

  /* MATLAB Function: '<Root>/MATLAB Function5' incorporates:
   *  S-Function (sdspFromNetwork): '<Root>/UDP Receive'
   *  S-Function (sdspFromNetwork): '<Root>/UDP Receive1'
   */
  for (i = 0; i < 4410; i++) {
    if (Parent_Mobile_B.UDPReceive4_o1 == 0.0F) {
      Parent_Mobile_B.y[i] = 0;
    } else {
      Parent_Mobile_B.y[i] = Parent_Mobile_B.UDPReceive_o1[i];
    }
  }

  for (i = 0; i < 4410; i++) {
    if (Parent_Mobile_B.UDPReceive4_o1 == 0.0F) {
      Parent_Mobile_B.y[i + 4410] = 0;
    } else {
      Parent_Mobile_B.y[i + 4410] = Parent_Mobile_B.UDPReceive1_o1[i];
    }
  }

  /* End of MATLAB Function: '<Root>/MATLAB Function5' */

  /* MATLABSystem: '<S1>/Audio Playback' */
  if (Parent_Mobile_DW.obj.SampleFreq !=
      Parent_Mobile_P.AudioPlayback_SampleFreq) {
    Parent_Mobile_DW.obj.SampleFreq = Parent_Mobile_P.AudioPlayback_SampleFreq;
  }

  for (i = 0; i < 4410; i++) {
    str_size_idx_1 = i << 1;
    Parent_Mobile_B.outData[str_size_idx_1] = Parent_Mobile_B.y[i];
    Parent_Mobile_B.outData[str_size_idx_1 + 1] = Parent_Mobile_B.y[i + 4410];
  }

  AUDIO_PLAYBACK(&Parent_Mobile_B.outData[0], Parent_Mobile_DW.obj.FrameSize);

  /* End of MATLABSystem: '<S1>/Audio Playback' */

  /* S-Function (sdspFromNetwork): '<Root>/UDP Receive3' */
  sErr = GetErrorBuffer(&Parent_Mobile_DW.UDPReceive3_NetworkLib[0U]);
  samplesRead_2 = 1;
  LibOutputs_Network(&Parent_Mobile_DW.UDPReceive3_NetworkLib[0U],
                     &Parent_Mobile_B.UDPReceive3_o1, &samplesRead_2);
  if (*sErr != 0) {
    rtmSetErrorStatus(Parent_Mobile_M, sErr);
    rtmSetStopRequested(Parent_Mobile_M, 1);
  }

  /* End of S-Function (sdspFromNetwork): '<Root>/UDP Receive3' */

  /* MATLABSystem: '<S2>/DataDisplay' incorporates:
   *  MATLABSystem: '<S3>/DataDisplay'
   *  MATLABSystem: '<S4>/DataDisplay'
   */
  Parent_Mobile_B.u0 = Parent_Mobile_B.UDPReceive3_o1;
  b_FormatStringTerminated_0[0] = '%';
  b_FormatStringTerminated_0[1] = '.';
  b_FormatStringTerminated_0[2] = '6';
  b_FormatStringTerminated_0[3] = 'f';
  b_FormatStringTerminated_0[4] = '\x00';
  for (i = 0; i < 5; i++) {
    b_FormatStringTerminated[i] = b_FormatStringTerminated_0[i];
  }

  PUT_DATADISPLAY_DATA(&Parent_Mobile_B.u0, 1.0, 9, 1,
                       &b_FormatStringTerminated[0]);

  /* End of MATLABSystem: '<S2>/DataDisplay' */

  /* S-Function (sdspFromNetwork): '<Root>/UDP Receive5' */
  sErr = GetErrorBuffer(&Parent_Mobile_DW.UDPReceive5_NetworkLib[0U]);
  samplesRead_3 = 1;
  LibOutputs_Network(&Parent_Mobile_DW.UDPReceive5_NetworkLib[0U],
                     &Parent_Mobile_B.UDPReceive5_o1, &samplesRead_3);
  if (*sErr != 0) {
    rtmSetErrorStatus(Parent_Mobile_M, sErr);
    rtmSetStopRequested(Parent_Mobile_M, 1);
  }

  /* End of S-Function (sdspFromNetwork): '<Root>/UDP Receive5' */

  /* MATLABSystem: '<S3>/DataDisplay' */
  Parent_Mobile_B.u0 = Parent_Mobile_B.UDPReceive5_o1;
  for (i = 0; i < 5; i++) {
    b_FormatStringTerminated[i] = b_FormatStringTerminated_0[i];
  }

  PUT_DATADISPLAY_DATA(&Parent_Mobile_B.u0, 2.0, 9, 1,
                       &b_FormatStringTerminated[0]);

  /* S-Function (sdspFromNetwork): '<Root>/UDP Receive6' */
  sErr = GetErrorBuffer(&Parent_Mobile_DW.UDPReceive6_NetworkLib[0U]);
  samplesRead_4 = 1;
  LibOutputs_Network(&Parent_Mobile_DW.UDPReceive6_NetworkLib[0U],
                     &Parent_Mobile_B.UDPReceive6_o1, &samplesRead_4);
  if (*sErr != 0) {
    rtmSetErrorStatus(Parent_Mobile_M, sErr);
    rtmSetStopRequested(Parent_Mobile_M, 1);
  }

  /* End of S-Function (sdspFromNetwork): '<Root>/UDP Receive6' */

  /* MATLABSystem: '<S4>/DataDisplay' */
  Parent_Mobile_B.u0 = Parent_Mobile_B.UDPReceive6_o1;
  PUT_DATADISPLAY_DATA(&Parent_Mobile_B.u0, 3.0, 9, 1,
                       &b_FormatStringTerminated_0[0]);
  rate_scheduler();
}

/* Model initialize function */
void Parent_Mobile_initialize(void)
{
  {
    char_T *sErr;

    /* Start for S-Function (sdspFromNetwork): '<Root>/UDP Receive' */
    sErr = GetErrorBuffer(&Parent_Mobile_DW.UDPReceive_NetworkLib[0U]);
    CreateUDPInterface(&Parent_Mobile_DW.UDPReceive_NetworkLib[0U]);
    if (*sErr == 0) {
      LibCreate_Network(&Parent_Mobile_DW.UDPReceive_NetworkLib[0U], 0,
                        "0.0.0.0", Parent_Mobile_P.UDPReceive_Port, "0.0.0.0",
                        -1, 8192, 2, 0);
    }

    if (*sErr == 0) {
      LibStart(&Parent_Mobile_DW.UDPReceive_NetworkLib[0U]);
    }

    if (*sErr != 0) {
      DestroyUDPInterface(&Parent_Mobile_DW.UDPReceive_NetworkLib[0U]);
      if (*sErr != 0) {
        rtmSetErrorStatus(Parent_Mobile_M, sErr);
        rtmSetStopRequested(Parent_Mobile_M, 1);
      }
    }

    /* End of Start for S-Function (sdspFromNetwork): '<Root>/UDP Receive' */

    /* Start for S-Function (sdspFromNetwork): '<Root>/UDP Receive1' */
    sErr = GetErrorBuffer(&Parent_Mobile_DW.UDPReceive1_NetworkLib[0U]);
    CreateUDPInterface(&Parent_Mobile_DW.UDPReceive1_NetworkLib[0U]);
    if (*sErr == 0) {
      LibCreate_Network(&Parent_Mobile_DW.UDPReceive1_NetworkLib[0U], 0,
                        "0.0.0.0", Parent_Mobile_P.UDPReceive1_Port, "0.0.0.0",
                        -1, 8192, 2, 0);
    }

    if (*sErr == 0) {
      LibStart(&Parent_Mobile_DW.UDPReceive1_NetworkLib[0U]);
    }

    if (*sErr != 0) {
      DestroyUDPInterface(&Parent_Mobile_DW.UDPReceive1_NetworkLib[0U]);
      if (*sErr != 0) {
        rtmSetErrorStatus(Parent_Mobile_M, sErr);
        rtmSetStopRequested(Parent_Mobile_M, 1);
      }
    }

    /* End of Start for S-Function (sdspFromNetwork): '<Root>/UDP Receive1' */

    /* Start for S-Function (sdspFromNetwork): '<Root>/UDP Receive4' */
    sErr = GetErrorBuffer(&Parent_Mobile_DW.UDPReceive4_NetworkLib[0U]);
    CreateUDPInterface(&Parent_Mobile_DW.UDPReceive4_NetworkLib[0U]);
    if (*sErr == 0) {
      LibCreate_Network(&Parent_Mobile_DW.UDPReceive4_NetworkLib[0U], 0,
                        "0.0.0.0", Parent_Mobile_P.UDPReceive4_Port, "0.0.0.0",
                        -1, 8192, 4, 0);
    }

    if (*sErr == 0) {
      LibStart(&Parent_Mobile_DW.UDPReceive4_NetworkLib[0U]);
    }

    if (*sErr != 0) {
      DestroyUDPInterface(&Parent_Mobile_DW.UDPReceive4_NetworkLib[0U]);
      if (*sErr != 0) {
        rtmSetErrorStatus(Parent_Mobile_M, sErr);
        rtmSetStopRequested(Parent_Mobile_M, 1);
      }
    }

    /* End of Start for S-Function (sdspFromNetwork): '<Root>/UDP Receive4' */

    /* Start for S-Function (sdspFromNetwork): '<Root>/UDP Receive3' */
    sErr = GetErrorBuffer(&Parent_Mobile_DW.UDPReceive3_NetworkLib[0U]);
    CreateUDPInterface(&Parent_Mobile_DW.UDPReceive3_NetworkLib[0U]);
    if (*sErr == 0) {
      LibCreate_Network(&Parent_Mobile_DW.UDPReceive3_NetworkLib[0U], 0,
                        "0.0.0.0", Parent_Mobile_P.UDPReceive3_Port, "0.0.0.0",
                        -1, 8192, 8, 0);
    }

    if (*sErr == 0) {
      LibStart(&Parent_Mobile_DW.UDPReceive3_NetworkLib[0U]);
    }

    if (*sErr != 0) {
      DestroyUDPInterface(&Parent_Mobile_DW.UDPReceive3_NetworkLib[0U]);
      if (*sErr != 0) {
        rtmSetErrorStatus(Parent_Mobile_M, sErr);
        rtmSetStopRequested(Parent_Mobile_M, 1);
      }
    }

    /* End of Start for S-Function (sdspFromNetwork): '<Root>/UDP Receive3' */

    /* Start for S-Function (sdspFromNetwork): '<Root>/UDP Receive5' */
    sErr = GetErrorBuffer(&Parent_Mobile_DW.UDPReceive5_NetworkLib[0U]);
    CreateUDPInterface(&Parent_Mobile_DW.UDPReceive5_NetworkLib[0U]);
    if (*sErr == 0) {
      LibCreate_Network(&Parent_Mobile_DW.UDPReceive5_NetworkLib[0U], 0,
                        "0.0.0.0", Parent_Mobile_P.UDPReceive5_Port, "0.0.0.0",
                        -1, 8192, 8, 0);
    }

    if (*sErr == 0) {
      LibStart(&Parent_Mobile_DW.UDPReceive5_NetworkLib[0U]);
    }

    if (*sErr != 0) {
      DestroyUDPInterface(&Parent_Mobile_DW.UDPReceive5_NetworkLib[0U]);
      if (*sErr != 0) {
        rtmSetErrorStatus(Parent_Mobile_M, sErr);
        rtmSetStopRequested(Parent_Mobile_M, 1);
      }
    }

    /* End of Start for S-Function (sdspFromNetwork): '<Root>/UDP Receive5' */

    /* Start for S-Function (sdspFromNetwork): '<Root>/UDP Receive6' */
    sErr = GetErrorBuffer(&Parent_Mobile_DW.UDPReceive6_NetworkLib[0U]);
    CreateUDPInterface(&Parent_Mobile_DW.UDPReceive6_NetworkLib[0U]);
    if (*sErr == 0) {
      LibCreate_Network(&Parent_Mobile_DW.UDPReceive6_NetworkLib[0U], 0,
                        "0.0.0.0", Parent_Mobile_P.UDPReceive6_Port, "0.0.0.0",
                        -1, 8192, 8, 0);
    }

    if (*sErr == 0) {
      LibStart(&Parent_Mobile_DW.UDPReceive6_NetworkLib[0U]);
    }

    if (*sErr != 0) {
      DestroyUDPInterface(&Parent_Mobile_DW.UDPReceive6_NetworkLib[0U]);
      if (*sErr != 0) {
        rtmSetErrorStatus(Parent_Mobile_M, sErr);
        rtmSetStopRequested(Parent_Mobile_M, 1);
      }
    }

    /* End of Start for S-Function (sdspFromNetwork): '<Root>/UDP Receive6' */

    /* Start for MATLABSystem: '<Root>/TCP//IP Receive4' */
    Parent_Mobile_DW.obj_n.errorNo_ = 0;
    Parent_Mobile_DW.obj_n.isInitialized = 0;
    Parent_Mobile_SystemCore_setup(&Parent_Mobile_DW.obj_n);

    /* Start for MATLABSystem: '<Root>/TCP//IP Receive5' */
    Parent_Mobile_DW.obj_a.errorNo_ = 0;
    Parent_Mobile_DW.obj_a.isInitialized = 0;
    Parent_Mobil_SystemCore_setup_b(&Parent_Mobile_DW.obj_a);

    /* Start for MATLABSystem: '<Root>/TCP//IP Receive6' */
    Parent_Mobile_DW.obj_c.errorNo_ = 0;
    Parent_Mobile_DW.obj_c.isInitialized = 0;
    Parent_Mobi_SystemCore_setup_by(&Parent_Mobile_DW.obj_c);

    /* Start for MATLABSystem: '<S9>/Video Display' */
    INITIALIZE_VIDEO_DISPLAY(320, 240);

    /* Start for MATLABSystem: '<S1>/Audio Playback' */
    Parent_Mobile_DW.obj.matlabCodegenIsDeleted = false;
    Parent_Mobile_DW.obj.SampleFreq = Parent_Mobile_P.AudioPlayback_SampleFreq;
    Parent_Mobile_DW.obj.isInitialized = 1;
    Parent_Mobile_DW.obj.FrameSize = 4410.0;
    INIT_AUDIO_PLAYBACK(Parent_Mobile_DW.obj.SampleFreq,
                        Parent_Mobile_DW.obj.FrameSize);
    Parent_Mobile_DW.obj.isSetupComplete = true;

    /* Start for MATLABSystem: '<S2>/DataDisplay' */
    INITIALIZE_DATADISPLAY();

    /* Start for MATLABSystem: '<S3>/DataDisplay' */
    INITIALIZE_DATADISPLAY();

    /* Start for MATLABSystem: '<S4>/DataDisplay' */
    INITIALIZE_DATADISPLAY();
  }
}

/* Model terminate function */
void Parent_Mobile_terminate(void)
{
  char_T *sErr;

  /* Terminate for S-Function (sdspFromNetwork): '<Root>/UDP Receive' */
  sErr = GetErrorBuffer(&Parent_Mobile_DW.UDPReceive_NetworkLib[0U]);
  LibTerminate(&Parent_Mobile_DW.UDPReceive_NetworkLib[0U]);
  if (*sErr != 0) {
    rtmSetErrorStatus(Parent_Mobile_M, sErr);
    rtmSetStopRequested(Parent_Mobile_M, 1);
  }

  LibDestroy(&Parent_Mobile_DW.UDPReceive_NetworkLib[0U], 0);
  DestroyUDPInterface(&Parent_Mobile_DW.UDPReceive_NetworkLib[0U]);

  /* End of Terminate for S-Function (sdspFromNetwork): '<Root>/UDP Receive' */

  /* Terminate for S-Function (sdspFromNetwork): '<Root>/UDP Receive1' */
  sErr = GetErrorBuffer(&Parent_Mobile_DW.UDPReceive1_NetworkLib[0U]);
  LibTerminate(&Parent_Mobile_DW.UDPReceive1_NetworkLib[0U]);
  if (*sErr != 0) {
    rtmSetErrorStatus(Parent_Mobile_M, sErr);
    rtmSetStopRequested(Parent_Mobile_M, 1);
  }

  LibDestroy(&Parent_Mobile_DW.UDPReceive1_NetworkLib[0U], 0);
  DestroyUDPInterface(&Parent_Mobile_DW.UDPReceive1_NetworkLib[0U]);

  /* End of Terminate for S-Function (sdspFromNetwork): '<Root>/UDP Receive1' */

  /* Terminate for S-Function (sdspFromNetwork): '<Root>/UDP Receive4' */
  sErr = GetErrorBuffer(&Parent_Mobile_DW.UDPReceive4_NetworkLib[0U]);
  LibTerminate(&Parent_Mobile_DW.UDPReceive4_NetworkLib[0U]);
  if (*sErr != 0) {
    rtmSetErrorStatus(Parent_Mobile_M, sErr);
    rtmSetStopRequested(Parent_Mobile_M, 1);
  }

  LibDestroy(&Parent_Mobile_DW.UDPReceive4_NetworkLib[0U], 0);
  DestroyUDPInterface(&Parent_Mobile_DW.UDPReceive4_NetworkLib[0U]);

  /* End of Terminate for S-Function (sdspFromNetwork): '<Root>/UDP Receive4' */

  /* Terminate for MATLABSystem: '<S1>/Audio Playback' */
  if (!Parent_Mobile_DW.obj.matlabCodegenIsDeleted) {
    Parent_Mobile_DW.obj.matlabCodegenIsDeleted = true;
    if ((Parent_Mobile_DW.obj.isInitialized == 1) &&
        Parent_Mobile_DW.obj.isSetupComplete) {
      TERMINATE_AUDIO_PLAYBACK();
    }
  }

  /* End of Terminate for MATLABSystem: '<S1>/Audio Playback' */

  /* Terminate for S-Function (sdspFromNetwork): '<Root>/UDP Receive3' */
  sErr = GetErrorBuffer(&Parent_Mobile_DW.UDPReceive3_NetworkLib[0U]);
  LibTerminate(&Parent_Mobile_DW.UDPReceive3_NetworkLib[0U]);
  if (*sErr != 0) {
    rtmSetErrorStatus(Parent_Mobile_M, sErr);
    rtmSetStopRequested(Parent_Mobile_M, 1);
  }

  LibDestroy(&Parent_Mobile_DW.UDPReceive3_NetworkLib[0U], 0);
  DestroyUDPInterface(&Parent_Mobile_DW.UDPReceive3_NetworkLib[0U]);

  /* End of Terminate for S-Function (sdspFromNetwork): '<Root>/UDP Receive3' */

  /* Terminate for S-Function (sdspFromNetwork): '<Root>/UDP Receive5' */
  sErr = GetErrorBuffer(&Parent_Mobile_DW.UDPReceive5_NetworkLib[0U]);
  LibTerminate(&Parent_Mobile_DW.UDPReceive5_NetworkLib[0U]);
  if (*sErr != 0) {
    rtmSetErrorStatus(Parent_Mobile_M, sErr);
    rtmSetStopRequested(Parent_Mobile_M, 1);
  }

  LibDestroy(&Parent_Mobile_DW.UDPReceive5_NetworkLib[0U], 0);
  DestroyUDPInterface(&Parent_Mobile_DW.UDPReceive5_NetworkLib[0U]);

  /* End of Terminate for S-Function (sdspFromNetwork): '<Root>/UDP Receive5' */

  /* Terminate for S-Function (sdspFromNetwork): '<Root>/UDP Receive6' */
  sErr = GetErrorBuffer(&Parent_Mobile_DW.UDPReceive6_NetworkLib[0U]);
  LibTerminate(&Parent_Mobile_DW.UDPReceive6_NetworkLib[0U]);
  if (*sErr != 0) {
    rtmSetErrorStatus(Parent_Mobile_M, sErr);
    rtmSetStopRequested(Parent_Mobile_M, 1);
  }

  LibDestroy(&Parent_Mobile_DW.UDPReceive6_NetworkLib[0U], 0);
  DestroyUDPInterface(&Parent_Mobile_DW.UDPReceive6_NetworkLib[0U]);

  /* End of Terminate for S-Function (sdspFromNetwork): '<Root>/UDP Receive6' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
