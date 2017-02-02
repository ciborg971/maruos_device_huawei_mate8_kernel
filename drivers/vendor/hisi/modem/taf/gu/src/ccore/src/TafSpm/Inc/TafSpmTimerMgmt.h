

#ifndef __TAF_SPM_TIMERMGMT_H__
#define __TAF_SPM_TIMERMGMT_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "PsTypeDef.h"
#include "MnComm.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
/* ��ǿ�ͻ��鷢������ϵ�ˣ�����FDN/CC���ı���ʱ��������8s */
#define             TI_TAF_SPM_WAIT_PB_FDN_CHECK_CNF_LEN                (8000)
#define             TI_TAF_SPM_WAIT_USIM_CALL_CTRL_CNF_LEN              (8000)

/*
 * The following service request timer value dependence on:
 *  1. SMS: AT_SMS_CMGS_SET_PARA_TIME/AT_SMS_CMSS_SET_PARA_TIME
 *  2. SS: AT_SS_SET_PARA_TIME/AT_SS_QRY_PARA_TIME
 *  3. CC: AT_SET_PARA_TIME.
 * see ATCmdProc.h file.
 */
#define             TI_TAF_SPM_CC_SRV_REQ_PROTECT_TIMER_VAL             (25000)             /* CCҵ�����󱣻���ʱ��ֵ */
#define             TI_TAF_SPM_SMS_SRV_REQ_PROTECT_TIMER_VAL            (30000)             /* SMSҵ�����󱣻���ʱ��ֵ */
#define             TI_TAF_SPM_SS_SRV_REQ_PROTECT_TIMER_VAL             (30000)             /* SSҵ�����󱣻���ʱ��ֵ */

#define             TI_TAF_SPM_CC_SMS_SS_SRV_REQ_PROTECT_TIMER_DEFAULT_VAL      (3000)      /* CCҵ�����󱣻���ʱ��Ĭ��ֵ */

#define             TI_TAF_SPM_CC_ECALL_REQ_PROTECT_TIMER_VAL           (90000)             /* ecall CCҵ�����󱣻���ʱ��ֵ��T305+2*T308 */

#define             TAF_SPM_MAX_TIMER_NUM                               (10)                /* spm��ͬʱ���еĶ�ʱ���������Ŀ */


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/


enum TAF_SPM_TIMER_STATUS_ENUM
{
    TAF_SPM_TIMER_STATUS_STOP,              /* ��ʱ��ֹͣ״̬ */
    TAF_SPM_TIMER_STATUS_RUNING,            /* ��ʱ������״̬ */
    TAF_SPM_TIMER_STATUS_BUTT
};
typedef VOS_UINT8 TAF_SPM_TIMER_STATUS_ENUM_UINT8;


enum TAF_SPM_TIMER_ID_ENUM
{
    TI_TAF_SPM_WAIT_PB_FDN_CHECK_CNF                             = MN_TIMER_CLASS_SPM,/* �ȴ�PB��FDN�����������ʱ�� */
    TI_TAF_SPM_WAIT_USIM_CALL_CTRL_CNF,                                               /* �ȴ�USIM��call control�����������ʱ�� */
    TI_TAF_SPM_CC_SRV_REQ_PROTECT_TIMER,                                                /* CC ҵ�����󱣻���ʱ�� */
    TI_TAF_SPM_SMS_SRV_REQ_PROTECT_TIMER,                                               /* SMS ҵ�����󱣻���ʱ�� */
    TI_TAF_SPM_SS_SRV_REQ_PROTECT_TIMER,                                                /* SS ҵ�����󱣻���ʱ�� */
    
    TI_TAF_SPM_TIMER_BUTT
};
typedef VOS_UINT32 TAF_SPM_TIMER_ID_ENUM_UINT32;



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
    HTIMER                              hTimer;                                 /* ��ʱ��������ָ�� */
    TAF_SPM_TIMER_ID_ENUM_UINT32        enTimerId;                              /* ��ʱ����ID */
    TAF_SPM_TIMER_STATUS_ENUM_UINT8     enTimerStatus;                          /* ��ʱ��������״̬,������ֹͣ */
    VOS_UINT8                           aucReserve[1];                          /* ����λ */
    VOS_UINT16                          usClientId;                             /* ��ʱ��������client PID */
} TAF_SPM_TIMER_CTX_STRU;
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;
    TAF_SPM_TIMER_STATUS_ENUM_UINT8     enTimerStatus;      /* ��ʱ��״̬ */
    VOS_UINT8                           aucReserve[1];      /* ����λ */    
    VOS_UINT16                          usClientId;         /* ��ʱ������client ID */
    VOS_UINT32                          ulLen;              /* ��ʱ��ʱ�� */
}TAF_SPM_TIMER_INFO_STRU;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 �ⲿ������������
*****************************************************************************/

/*****************************************************************************
  10 ��������
*****************************************************************************/
VOS_VOID  TAF_SPM_StartTimer(
    TAF_SPM_TIMER_ID_ENUM_UINT32        enTimerId,
    VOS_UINT32                          ulLen,
    VOS_UINT16                          usClientId
);

VOS_VOID  TAF_SPM_StopTimer(
    TAF_SPM_TIMER_ID_ENUM_UINT32        enTimerId,
    VOS_UINT16                          usClientId
);

TAF_SPM_TIMER_STATUS_ENUM_UINT8  TAF_SPM_GetTimerStatus(
    TAF_SPM_TIMER_ID_ENUM_UINT32        enTimerId,
    VOS_UINT16                          usClientId
);

VOS_VOID  TAF_SPM_InitAllTimers(
    TAF_SPM_TIMER_CTX_STRU              *pstSpmTimerCtx
);

VOS_VOID  TAF_SPM_SndOmTimerStatus(
    TAF_SPM_TIMER_STATUS_ENUM_UINT8     enTimerStatus,
    TAF_SPM_TIMER_ID_ENUM_UINT32        enTimerId,
    VOS_UINT32                          ulLen,
    VOS_UINT16                          usClientId
);

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

#endif /* end of TafSpmTimerMgmt.h */

