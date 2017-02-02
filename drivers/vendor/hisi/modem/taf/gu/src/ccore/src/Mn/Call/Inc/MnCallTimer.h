/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : MnCallTimer.h
  �� �� ��   : ����
  ��    ��   : dfakl;f
  ��������   : 2010��5��19��
  ����޸�   :
  ��������   : MnCallTimer.h ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2010��5��19��
    ��    ��   : dfakl;f
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __MNCALLTIMER_H__
#define __MNCALLTIMER_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "MnComm.h"
#include "MnCallMgmt.h"


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define MN_CALL_TIMER_TICK              (10)


/*****************************************************************************
  3 ö�ٶ���
*************************************************************************/
/*CALLģ�鶨ʱ��ID�Ķ���*/
enum MN_CALL_TIMER_ID_ENUM
{
    MN_CALL_TID_WAIT_CST_SETUP           = MN_TIMER_CLASS_CCA,                  /* ��CSTģ�鷢��SETUP��Ϣ֮�������ö�ʱ�������ڱ��� */
    MN_CALL_TID_RING,
    
    /* FDN��CALL control����Ƶ�SPM�����ﶨʱ��IDɾ�� */

    MN_CALL_TID_WAIT_CALL_REDIAL_PERIOD,
    MN_CALL_TID_WAIT_CALL_REDAIL_INTERVAL,

    TAF_CALL_TID_DTMF_ON_LENGTH,               /* start dtmf ack��stop dtmf req֮���ʱ������ʱ�� */
    TAF_CALL_TID_DTMF_OFF_LENGTH,              /* stop dtmf ack ��start dtmf req֮���ʱ������ʱ�� */

    TAF_CALL_TID_WAIT_ECALL_REDIAL_PERIOD,                                       /* eCall�ز�ʱ����ʱ�� */
    TAF_CALL_TID_WAIT_ECALL_REDAIL_INTERVAL,                                     /* eCall�ز������ʱ�� */
    TAF_CALL_TID_T2,                                                             /* eCallͨ��ʱ����ʱ�� */
    TAF_CALL_TID_T9,                                                             /* �ȴ�MT eCallʱ����ʱ�� */

    MN_CALL_TID_BUTT
};
typedef VOS_UINT32  MN_CALL_TIMER_ID_ENUM_U32;
enum MN_CALL_TIMER_STATUS_ENUM
{
    MN_CALL_TIMER_STATUS_STOP,              /* ��ʱ��ֹͣ״̬ */
    MN_CALL_TIMER_STATUS_RUNING,            /* ��ʱ������״̬ */
    MN_CALL_TIMER_STATUS_BUTT
};
typedef VOS_UINT8 MN_CALL_TIMER_STATUS_ENUM_U8;





/*****************************************************************************
  4 ���Ͷ���
*****************************************************************************/

/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/
/* ��ʱ�����������Ͷ��� */
typedef VOS_VOID (* MN_CALL_TIMEOUT_PROC_FUNC)(VOS_UINT32 ulParam);


typedef struct
{
    HTIMER                              hTimer;
    MN_CALL_TIMER_ID_ENUM_U32           enTimerId;

    MN_CALL_TIMER_STATUS_ENUM_U8        enTimerStatus;                          /* ��ʱ��������״̬,������ֹͣ */
    VOS_UINT8                           aucReserved1[3];
}MN_CALL_TIMER_HANDLE_STRU;

/* ��ʱ����Ϣ�ṹ */
typedef struct
{
    VOS_UINT32                          ulTimeout;
    MN_CALL_TIMEOUT_PROC_FUNC           pfnTimeoutProc;
} MN_CALL_TIMER_INFO_STRU;




/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/

extern VOS_VOID  MN_CALL_ProcTimeoutMsg(
    REL_TIMER_MSG                       *pTmrMsg
);


extern VOS_VOID  MN_CALL_StartTimer(
    MN_CALL_TIMER_ID_ENUM_U32           enTimerId,
    VOS_UINT32                          ulParam,
    VOS_UINT32                          ulLength,
    VOS_UINT8                           ucTimerMode
);


extern VOS_VOID MN_CALL_StopTimer(
    MN_CALL_TIMER_ID_ENUM_U32            enTimerId
);


extern VOS_VOID  MN_CALL_InitAllTimers(MN_CALL_POWER_STATE_ENUM_U8 enPowerState);


extern VOS_VOID  MN_CALL_CstSetupTimeout(
    VOS_UINT32                          ulParam
);


VOS_VOID MN_CALL_RingTimerTimeout(
    VOS_UINT32                          ulParam
);



VOS_VOID MN_CALL_UpdateTimerPeriod(
    MN_CALL_TIMER_ID_ENUM_U32           enTimerId,
    VOS_UINT32                          ulTimerLen
);
VOS_VOID MN_CALL_CallRedialPeriodTimeout(VOS_UINT32 ulParam);

VOS_VOID MN_CALL_CallRedialIntervalTimeout(VOS_UINT32 ulParam);

VOS_UINT32  MN_CALL_GetTimerRemainLen(
    MN_CALL_TIMER_ID_ENUM_U32           enTimerId
);

VOS_UINT32 MN_CALL_GetTimerLen(
    MN_CALL_TIMER_ID_ENUM_U32           enTimerId
);

MN_CALL_TIMER_STATUS_ENUM_U8  MN_CALL_GetTimerStatus(
    MN_CALL_TIMER_ID_ENUM_U32           enTimerId
);



VOS_VOID TAF_CALL_RcvTiDtmfOnLengthExpired(
    VOS_UINT32                          ulParam
);

VOS_VOID TAF_CALL_RcvTiDtmfOffLengthExpired(
    VOS_UINT32                          ulParam
);

VOS_UINT32 TAF_CALL_GetTimerLen(
    MN_CALL_TIMER_ID_ENUM_U32           enTimerId
);

#if (FEATURE_ON == FEATURE_ECALL)
VOS_VOID TAF_CALL_EcallRedialPeriodTimeout(VOS_UINT32 ulParam);

VOS_VOID TAF_CALL_EcallRedialIntervalTimeout(VOS_UINT32 ulParam);

VOS_VOID TAF_CALL_RcvT2TimerExpired(
    VOS_UINT32                          ulParam
);

VOS_VOID TAF_CALL_RcvT9TimerExpired(
    VOS_UINT32                          ulParam
);
#endif

VOS_VOID TAF_CALL_StopAllRedialTimers(VOS_UINT8 ucCallId);

VOS_UINT32 TAF_CALL_GetRedialIntervalTimerLen(VOS_UINT8 ucCallId);

VOS_UINT32 TAF_CALL_GetRemainRedialPeriodTimerLen(VOS_UINT8 ucCallId);

VOS_VOID TAF_CALL_StartRedialPeriodTimer(VOS_UINT8 ucCallId);

MN_CALL_TIMER_STATUS_ENUM_U8 TAF_CALL_GetRedialIntervalTimerStatus(VOS_UINT8 ucCallId);

#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of MnCallTimer.h */
