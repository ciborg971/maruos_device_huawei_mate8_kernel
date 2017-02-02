
#ifndef __SLEEPSLEEP_H__
#define __SLEEPSLEEP_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#include "vos.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/*****************************************************************************
  2 �궨��
*****************************************************************************/

#define DSP_PLL_LOCK   0  /* DSP PLL�����໷����ȶ� */
#define DSP_PLL_UNLOCK 1  /* DSP PLL�����໷������ȶ� */

/* SLEEP ģ����Ʊ��� */
#define CURRENT_MODULE_SLEEP    (0)
#define CURRENT_MODULE_RUN      (1)

/* ��ģ�͹��Ŀ��Ʊ��� */
#define SLAVE_MODULE_SLEEP      (0)
#define SLAVE_MODULE_RUN        (1)

#define HPA_LOAD_PHY_TRACE_NUM  (5)
#define SLEEP_RECORD_TRACK_NUM  (3)

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

/*****************************************************************************
  4 ȫ�ֱ�������
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

typedef struct
{
    VOS_UINT32 ulSystemState;
    VOS_UINT32 ulSlaveSystemState;   /* ��ģ�͹���״̬ */
    VOS_UINT32 ulDspPllState;        /* DSP PLL ��״̬ 0 �ѹر� 1 δ�ر� */
    VOS_UINT32 ulBbpPllState;        /* BBP PLL ��״̬ 0 �ѹر� 1 δ�ر� */
    VOS_UINT32 ulRfLdoState;         /* RF LDO ��״̬ 0 �ѹر� 1 δ�ر� */
    VOS_UINT32 ulMpuState;           /* MPU ��״̬ 0 SLEEP ״̬ 1 NORMAL ״̬ */
}SLEEP_CTRL_STRU;

typedef struct
{
    VOS_UINT32 ulCount;              /* ��¼�����Ĵ��� */
    VOS_UINT32 ulSlice;              /* ��¼������Sliceֵ */
}SLEEP_RECORD_STRU;

/*****************************************************************************
 �ṹ��    : SLEEP_RECORD_TRACK_STRU
 �ṹ˵��  : ��¼�͹��Ĵ���ʱ��켣
*****************************************************************************/
typedef struct
{
    VOS_UINT32 ulCount;                         /* ��¼�����Ĵ��� */
    VOS_UINT32 aulSlice[SLEEP_RECORD_TRACK_NUM]; /* ��¼������Sliceֵ */
}SLEEP_RECORD_TRACK_STRU;

typedef struct
{
    /*�����͹�������*/
    SLEEP_RECORD_STRU  stEnterLowPowerErr;  /*��¼����͹���ģʽʧ�� */
    SLEEP_RECORD_STRU  stLowPowerIpc;       /*��¼����IPC�ж�֪ͨDSP����HALT */
    SLEEP_RECORD_STRU  stExitLowPowerRet;   /*��¼��ǰ���ڵ͹����£����ó��͹��ĺ��� */
    SLEEP_RECORD_STRU  stLowPowerNMI;       /*��¼����NMI�жϻ���DSP */

    /*����ģʽ����*/
    SLEEP_RECORD_STRU  stFlyModeIpc;        /*��¼����IPC�ж�֪ͨDSP����HALT */
    SLEEP_RECORD_STRU  stFlyModeNMI;        /*��¼����NMI�жϻ���DSP */

    /*CONNET&IDLE��¼*/
    SLEEP_RECORD_STRU  stConnectMode;       /*��¼DSP֪ͨARM��������̬ʱ */
    SLEEP_RECORD_STRU  stIdleMode;          /*��¼DSP֪ͨARM����IDLE̬ʱ */

    SLEEP_RECORD_STRU  stWDrxReadPcchData;  /*��¼��DSP����HALT��֪ͨ�����ȡ����������*/
}LOWPOWER_STATE_STRU;


typedef struct
{
    SLEEP_RECORD_STRU  stLoadHifiReq;       /* ��¼����HIFI */
    SLEEP_RECORD_STRU  stLoadTimeout;       /* ��¼����HIFI��ʱ */
    SLEEP_RECORD_STRU  stHifiLoadIpc;       /* ��¼����HIFI�жϻظ� */
    SLEEP_RECORD_STRU  stHifiSleepIpc;      /* ��¼HIFI˯������ */
    SLEEP_RECORD_STRU  stHifiStateErr;      /* ��¼HIFI״̬����ȷ */
}HIFI_STATE_STRU;

typedef struct
{
    VOS_UINT32 ulPAState;                                           /* ��¼PA״̬ 0 Ϊ�µ� 1 Ϊ�ϵ� */
    VOS_UINT32 ulRFState;                                           /* ��¼RF״̬ 0 Ϊ�µ� 1 Ϊ�ϵ� */
    VOS_UINT32 ulBBPSocPwState;                                     /* ��¼BBP SOC״̬  0 Ϊ�µ� 1 Ϊ�ϵ� */
    VOS_UINT32 ulBBPPwState;                                        /* ��¼BBP PW״̬ 0 Ϊ�µ� 1 Ϊ�ϵ� */
    VOS_UINT32 ulDspPwState;                                        /* ��¼DSP PW״̬ 0 Ϊ�µ� 1 Ϊ�ϵ� */
    VOS_UINT32 ulABBPwState;                                        /* ��¼ABB PW״̬ 0 Ϊ�µ� 1 Ϊ�ϵ� */
    VOS_UINT32 ulDspPllState;                                       /* ��¼DSP PLL״̬ 0 Ϊ�ر� 1 Ϊ���� */
    VOS_UINT32 ulBBPPllState;                                       /* ��¼BBP PLL״̬ 0 Ϊ�ر� 1 Ϊ����*/
}SLEEP_SLAVE_CTRL_STRU;

/* ��ģ�͹��ļ�¼ */
typedef struct
{
    SLEEP_RECORD_STRU       astEnterSlaveMode[PWC_COMM_MODE_BUTT];      /* ��¼�����ģ�͹��� ��1ΪW ��2ΪG ��3ΪL(��ʹ��) */
    SLEEP_RECORD_STRU       astEnterSlaveModeErr[PWC_COMM_MODE_BUTT];   /* ��¼�����ģ�͹���ʧ�� ��1ΪW ��2ΪG ��3ΪL(��ʹ��) */
    SLEEP_RECORD_STRU       astExitSlaveMode[PWC_COMM_MODE_BUTT];       /* ��¼�˳���ģ�͹��� ��1ΪW ��2ΪG ��3ΪL(��ʹ��) */
    SLEEP_RECORD_STRU       astExitSlaveModeErr[PWC_COMM_MODE_BUTT];    /* ��¼�˳���ģ�͹���ʧ�� ��1ΪW ��2ΪG ��3ΪL(��ʹ��) */
    SLEEP_RECORD_STRU       stActiveHw;                                 /* ��¼�ϵ�״̬ */
    SLEEP_RECORD_STRU       stDeactiveHw;                               /* ��¼�µ�״̬ */
    SLEEP_SLAVE_CTRL_STRU   astSlaveRTTState[PWC_COMM_MODE_BUTT];       /* ��¼RTT��ϵͳ״̬ ��1ΪW ��2ΪG ��3ΪL(��ʹ��) */
}SLAVE_LOW_POWER_STATE_STRU;

typedef struct
{
    VOS_UINT32              ulloadPhyStart;
    VOS_UINT32              ulLoadPhyReqCount;
    VOS_UINT32              ulLoadPhyReqTime[HPA_LOAD_PHY_TRACE_NUM];
    VOS_UINT32              ulLoadPhyCnfCount;
    VOS_UINT32              ulLoadPhyCnfTime[HPA_LOAD_PHY_TRACE_NUM];
    VOS_UINT32              ulLoadPhyCnfResult[HPA_LOAD_PHY_TRACE_NUM];
    VOS_UINT32              ulLoadPhyCount;
    VOS_UINT32              ulLoadPhySuccessCount;
    VOS_UINT32              ulLoadPhyFailCount;
    VOS_UINT32              ulLoadPhyState;
    VOS_UINT32              ulLoadPhyErrMsgIdCnt;
    VOS_UINT32              ulLoadPhyErrMsgId;
    VOS_UINT32              ulLoadPhyErrResult;
    VOS_UINT32              ulLoadPhyErrMsgIdSlice[HPA_LOAD_PHY_TRACE_NUM];
    VOS_UINT32              ulLoadPhyIpcCount;
    VOS_UINT32              ulLoadPhyIpcSlice[HPA_LOAD_PHY_TRACE_NUM];
    VOS_UINT32              ulLoadPhyIpcMask[HPA_LOAD_PHY_TRACE_NUM];
    VOS_UINT32              ulLoadPhyIpcClearMask[HPA_LOAD_PHY_TRACE_NUM];
    VOS_UINT32              ulLoadPhyResult;
    VOS_UINT32              ulLoadPhyResultSlice;
}HPA_LOAD_PHY_STATE_STRU;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/

extern HIFI_STATE_STRU              *g_pstHifiStateSlice;
extern HPA_LOAD_PHY_STATE_STRU      *g_pstLoadPhyState;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __SLEEPSLEEP_H__ */
