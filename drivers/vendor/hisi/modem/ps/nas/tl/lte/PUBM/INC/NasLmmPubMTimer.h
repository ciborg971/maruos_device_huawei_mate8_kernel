

#ifndef __NASLMMPUBMTIMER_H__
#define __NASLMMPUBMTIMER_H__

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include  "NasLmmPubMOsa.h"
#include  "NasLmmPubMFsm.h"
#include  "NasEmmPubUGlobal.h"
#include  "NasLmmPublic.h"


/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  #pragma pack(*)    �����ֽڶ��뷽ʽ
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 macro
*****************************************************************************/

/*״̬��ʱ��*/
#define NAS_LMM_TIMER_ATTACH_WAIT_ESM_PDN_RSP_LEN    10000 /*ATTACH�ȴ�ESM���ؽ�������:10s*/
#define NAS_LMM_TIMER_ATTACH_WAIT_ESM_BEARER_CNF_LEN 10000 /*ATTACH�ȴ�ESM���ؼ�����:10s*/
#define NAS_LMM_TIMER_PLMN_WAIT_MMC_START_CNF_LEN    5000  /*PLMN�ȴ�MMC�������:5s*/
#define NAS_LMM_TIMER_PLMN_WAIT_MMC_STOP_CNF_LEN     5000  /*PLMN�ȴ�MMCֹͣ���:5s*/
#define NAS_LMM_TIMER_PLMN_WAIT_RRC_START_CNF_LEN    5000  /*PLMN�ȴ�RRC�������:5s*/
#define NAS_LMM_TIMER_MMC_USER_RES_PROTECT           10000 /*�ֶ�ģʽ�£�MMC�ȴ��û�ѡ��PLMN:10s*/
#define NAS_LMM_TIMER_MMC_DEFAULT_HPLMN_SRCH_PRIOD_LEN   3600000/* MMC VPLMN�£����ڽ���HPLMN������Ĭ������*/
#define NAS_LMM_TIMER_EMM_DEL_FORB_TA_PRIOD_LEN      (12*60*60*1000)/*MMCɾ�� ForbTA������*/
#define NAS_LMM_TIMER_WAIT_USIM_READY_START_LEN      5000 /*�ȴ�USIM����ʼ��*/
#define NAS_LMM_TIMER_DETACH_SWITCH_OFF_LEN          5000 /*���Է��͹ػ�detach�ĵȴ���ʱ��:5s*/

#define NAS_LMM_TIMER_REATTACH_DELAY_LEN             800       /*�յ�Rej #9��#10��#40���ܺ����·���attach����ʱ��ʱ�� */

#define NAS_LMM_TIMER_CSFB_DELAY_LEN                 3000  /* NORMAL̬���ͷŹ������յ�MM��CSFB����ʱ��ʱ��: 2s */

#ifndef PS_ITT_PC_TEST
#define NAS_LMM_TIMER_T3440_LEN                      10000 /*T3440:10s*/
#define NAS_LMM_TIMER_PUB_WAIT_MRRC_REL_CNF_LEN      5000  /*��ģ��ȴ��ڲ������ͷ�:5s*/
#define NAS_LMM_TIMER_DETACH_T3421_LEN               15000 /*DETACH�ȴ�������Ӧ:15S*/
#define NAS_LMM_TIMER_TAU_T3430                      15000 /*TAU�ȴ�������Ӧ:15s*/
#define NAS_LMM_TIMER_AUTH_T3418_LEN                 20000 /*AUTH MAC FAIL�ȴ�������Ӧ:20s*/
#define NAS_LMM_TIMER_AUTH_T3420_LEN                 15000 /*AUTH SYN FAIL�ȴ�������Ӧ:15s*/
#define NAS_LMM_TIMER_MMC_WAIT_AS_RESULT_LEN         (60000*5) /*MMC�ȴ��������:5min*/
#define NAS_LMM_TIMER_MMC_WAIT_PLMN_LIST_LEN         (60000*5) /*MMC�ȴ�PLMN LIST�������:5min*/
#define NAS_LMM_TIMER_MRRC_WAIT_RRC_CONN_CNF_LEN     5000  /*MRRC�ȴ����ӽ���:5s*/
#define NAS_LMM_TIMER_MRRC_WAIT_RRC_REL_CNF_LEN      5000  /*MRRC�ȴ������ͷ�:5s*/
#define NAS_LMM_TIMER_ATTACH_T3410_LEN               15000 /*ATTACH�ȴ�������Ӧ:15s*/
#define NAS_LMM_TIMER_T3411_LEN                      10000 /*ATTACH&TAU T3411:10S*/
#define NAS_LMM_TIMER_SER_T3417_LEN                  5000  /*SER�ȴ�������Ӧ:5s*/
#define NAS_LMM_TIMER_SER_T3417_EXT_LEN              10000  /*SER�ȴ�������Ӧ:10s*/
#define NAS_LMM_TIMER_PLMN_WAIT_RRC_STOP_CNF_LEN     5000  /*PLMN�ȴ�RRCֹͣ���:5s*/
#define NAS_LMM_TIMER_MMC_AVAILABLE_PLMN_SRCH_LEN    180000/*MMC��������AVAILABLEС��:3min*/
#define NAS_LMM_TIMER_MMC_INITIAL_HPLMN_SRCH_PRIOD_LEN   120000
#define NAS_LMM_TIMER_WAIT_USIM_CNF_LEN              30000 /*�ȴ�USIM����Ӧ��ʱ��:30s*/
#define NAS_LMM_TIMER_WAIT_RRC_DATA_CNF_LEN          6000 /*�ȴ�RRC��ֱ����Ϣȷ�ϵĶ�ʱ��:6s*/
#define NAS_LMM_TIMER_MMC_SUIT_CELL_SRCH_LEN         120000 /*MMC����suitС��:2min*/
#define NAS_LMM_TIMER_SUSPEND_RESUME_WAIT_LEN        5000 /*�ȴ�MMC,ESM,ERABM����Ķ�ʱ��ʱ��:5s*/
#define NAS_LMM_TIMER_SUSPEND_WAIT_END_LEN           200000 /*�ȴ�MMC GU RESUME NOTIFY�Ķ�ʱ��ʱ��:200s*/
#define NAS_LMM_TIMER_WAIT_SYS_INFO_IND_LEN          20000  /*�ȴ�ϵͳ��Ϣ��ʱ��:20s*/

#define NAS_LMM_TIMER_SYSCFG_CNF_WAIT_LEN            8000 /*�ȴ�SYSCFG_CNF�Ķ�ʱ��ʱ��:8s*/
#define NAS_LMM_TIMER_PLMN_SRCH_CNF_WAIT_LEN         100000 /*�ȴ�PLMN_SRCH_CNF�Ķ�ʱ��ʱ��:100s*/

#define NAS_LMM_TIMER_T3346_LEN                      15000 /*T3346Ĭ��ʱ��:15s*/
#else
    #ifdef PS_ITT_PC_TEST_NAS
    /* lihong00150010 emergency tau&service begin */
    #define NAS_LMM_TIMER_T3440_LEN                      5000 /*T3440:10s*/
    /* lihong00150010 emergency tau&service end */
    #define NAS_LMM_TIMER_PUB_WAIT_MRRC_REL_CNF_LEN      3000  /*��ģ��ȴ��ڲ������ͷ�:5s*/
    #define NAS_LMM_TIMER_DETACH_T3421_LEN               4000 /*DETACH�ȴ�������Ӧ:15S*/
    #define NAS_LMM_TIMER_TAU_T3430                      5000 /*TAU�ȴ�������Ӧ:15s*/
    #define NAS_LMM_TIMER_AUTH_T3418_LEN                 5000 /*AUTH MAC FAIL�ȴ�������Ӧ:20s*/
    #define NAS_LMM_TIMER_AUTH_T3420_LEN                 5000 /*AUTH SYN FAIL�ȴ�������Ӧ:15s*/
    #define NAS_LMM_TIMER_MMC_WAIT_AS_RESULT_LEN         5000 /*MMC�ȴ��������:1min*/
    #define NAS_LMM_TIMER_MMC_WAIT_PLMN_LIST_LEN         5000 /*MMC�ȴ�PLMN LIST�������:1min*/
    #define NAS_LMM_TIMER_MRRC_WAIT_RRC_CONN_CNF_LEN     20000  /*MRRC�ȴ����ӽ���:4s*/
    #define NAS_LMM_TIMER_MRRC_WAIT_RRC_REL_CNF_LEN      5000  /*MRRC�ȴ������ͷ�:5s*/
    /* lihong00150010 emergency tau&service begin */
    #define NAS_LMM_TIMER_ATTACH_T3410_LEN               7000 /*ATTACH�ȴ�������Ӧ:15s*/
    /* lihong00150010 emergency tau&service end */
    #define NAS_LMM_TIMER_T3411_LEN                      7000 /*ATTACH&TAU T3411:7S*/
    #define NAS_LMM_TIMER_SER_T3417_LEN                  15000  /*SER�ȴ�������Ӧ:15s*/
    #define NAS_LMM_TIMER_SER_T3417_EXT_LEN              15000  /*SER�ȴ�������Ӧ:15s*/
    #define NAS_LMM_TIMER_PLMN_WAIT_RRC_STOP_CNF_LEN     3000  /*PLMN�ȴ�RRCֹͣ���:5s*/
    #define NAS_LMM_TIMER_MMC_AVAILABLE_PLMN_SRCH_LEN    7000 /*MMC��������AVAILABLEС��:7s*/
    #define NAS_LMM_TIMER_MMC_INITIAL_HPLMN_SRCH_PRIOD_LEN   15000
    #define NAS_LMM_TIMER_WAIT_USIM_CNF_LEN              30000 /*�ȴ�USIM����Ӧ��ʱ��:30s*/
    #define NAS_LMM_TIMER_WAIT_RRC_DATA_CNF_LEN          6000 /*�ȴ�RRC��ֱ����Ϣȷ�ϵĶ�ʱ��:2s*/
    #define NAS_LMM_TIMER_MMC_SUIT_CELL_SRCH_LEN         7000 /*MMC����suitС��:7s*/
    #define NAS_LMM_TIMER_SUSPEND_RESUME_WAIT_LEN        4000 /*�ȴ�MMC,ESM,ERABM����Ķ�ʱ��ʱ��:5s*/
    #define NAS_LMM_TIMER_WAIT_SYS_INFO_IND_LEN          4000  /*�ȴ�ϵͳ��Ϣ��ʱ��:4s*/
    #define NAS_LMM_TIMER_SYSCFG_CNF_WAIT_LEN            5000 /*�ȴ�SYSCFG_CNF�Ķ�ʱ��ʱ��:5s*/
    #define NAS_LMM_TIMER_PLMN_SRCH_CNF_WAIT_LEN         10000 /*�ȴ�PLMN_SRCH_CNF�Ķ�ʱ��ʱ��:10s*/
    #define NAS_LMM_TIMER_SUSPEND_WAIT_END_LEN           200000 /*�ȴ�MMC GU RESUME NOTIFY�Ķ�ʱ��ʱ��:200s*/

    #define NAS_LMM_TIMER_T3346_LEN                      15000 /*T3346Ĭ��ʱ��:15s*/
    #else
    #define NAS_LMM_TIMER_T3440_LEN                      10000 /*T3440:10s*/
    #define NAS_LMM_TIMER_PUB_WAIT_MRRC_REL_CNF_LEN      5000  /*��ģ��ȴ��ڲ������ͷ�:5s*/
    #define NAS_LMM_TIMER_DETACH_T3421_LEN               15000 /*DETACH�ȴ�������Ӧ:15S*/
    #define NAS_LMM_TIMER_TAU_T3430                      15000 /*TAU�ȴ�������Ӧ:15s*/
    #define NAS_LMM_TIMER_AUTH_T3418_LEN                 20000 /*AUTH MAC FAIL�ȴ�������Ӧ:20s*/
    #define NAS_LMM_TIMER_AUTH_T3420_LEN                 15000 /*AUTH SYN FAIL�ȴ�������Ӧ:15s*/
    #define NAS_LMM_TIMER_MMC_WAIT_AS_RESULT_LEN         (60000*5) /*MMC�ȴ��������:5min*/
    #define NAS_LMM_TIMER_MMC_WAIT_PLMN_LIST_LEN         (60000*5) /*MMC�ȴ�PLMN LIST�������:5min*/
    #define NAS_LMM_TIMER_MRRC_WAIT_RRC_CONN_CNF_LEN     50000 /*MRRC�ȴ����ӽ���:50s*/
    #define NAS_LMM_TIMER_MRRC_WAIT_RRC_REL_CNF_LEN      50000 /*MRRC�ȴ������ͷ�:50s*/
    #define NAS_LMM_TIMER_ATTACH_T3410_LEN               30000 /*ATTACH�ȴ�������Ӧ:30s*/
    #define NAS_LMM_TIMER_T3411_LEN                      30000 /*ATTACH&TAU T3411:30S*/
    #define NAS_LMM_TIMER_SER_T3417_LEN                  15000 /*SER�ȴ�������Ӧ:15s*/
    #define NAS_LMM_TIMER_SER_T3417_EXT_LEN              15000  /*SER�ȴ�������Ӧ:15s*/
    #define NAS_LMM_TIMER_PLMN_WAIT_RRC_STOP_CNF_LEN     120000 /*PLMN�ȴ�RRCֹͣ���:120s*/
    #define NAS_LMM_TIMER_MMC_AVAILABLE_PLMN_SRCH_LEN    60000 /*MMC��������AVAILABLEС��:60s*/
    #define NAS_LMM_TIMER_MMC_INITIAL_HPLMN_SRCH_PRIOD_LEN   120000
    #define NAS_LMM_TIMER_WAIT_USIM_CNF_LEN              30000 /*�ȴ�USIM����Ӧ��ʱ��:30s*/
    #define NAS_LMM_TIMER_WAIT_RRC_DATA_CNF_LEN          6000 /*�ȴ�RRC��ֱ����Ϣȷ�ϵĶ�ʱ��:2s*/
    #define NAS_LMM_TIMER_MMC_SUIT_CELL_SRCH_LEN         60000 /*MMC����suitС��:60s*/
    #define NAS_LMM_TIMER_SUSPEND_RESUME_WAIT_LEN        5000 /*�ȴ�MMC,ESM,ERABM����Ķ�ʱ��ʱ��:5s*/
    #define NAS_LMM_TIMER_WAIT_SYS_INFO_IND_LEN          5000  /*�ȴ�ϵͳ��Ϣ��ʱ��:5s*/
    #define NAS_LMM_TIMER_SYSCFG_CNF_WAIT_LEN            5000 /*�ȴ�SYSCFG_CNF�Ķ�ʱ��ʱ��:2s*/
    #define NAS_LMM_TIMER_PLMN_SRCH_CNF_WAIT_LEN         10000 /*�ȴ�PLMN_SRCH_CNF�Ķ�ʱ��ʱ��:10s*/
    #define NAS_LMM_TIMER_SUSPEND_WAIT_END_LEN           200000 /*�ȴ�MMC GU RESUME NOTIFY�Ķ�ʱ��ʱ��:200s*/
    #endif

#endif

/*leili modify for isr begin*/
/*Э�鶨ʱ��*/
#ifndef PS_ITT_PC_TEST
#define NAS_LMM_TIMER_T3402_LEN                          720000/*ATTACH&TAU T3402:12min*/
#define NAS_LMM_TIMER_T3412_LEN                          (54*60*1000) /*TAU T3412:54min*/
#define NAS_LMM_TIMER_AUTH_T3416_LEN                     20000 /*AUTHȷ�ϼ�Ȩ���T3416:30s*/
#define NAS_LMM_TIMER_T3423_LEN                          (54*60*1000) /*T3423:54min*/

#else
     #ifdef PS_ITT_PC_TEST_NAS
     #define NAS_LMM_TIMER_T3402_LEN                     30000 /*ATTACH&TAU T3402:1min*/
     #define NAS_LMM_TIMER_T3412_LEN                     15000 /*TAU T3412:15s*/
     #define NAS_LMM_TIMER_AUTH_T3416_LEN                 3000 /*AUTHȷ�ϼ�Ȩ���T3416:30s*/
     #define NAS_LMM_TIMER_T3423_LEN                     15000 /*T3423: 15s*/

     #else
     #define NAS_LMM_TIMER_T3402_LEN                     60000 /*ATTACH&TAU T3402:1min*/
     #define NAS_LMM_TIMER_T3412_LEN                     (54*60*1000) /*TAU T3412:54min*/
     #define NAS_LMM_TIMER_AUTH_T3416_LEN                30000 /*AUTHȷ�ϼ�Ȩ���T3416:30s*/
     #define NAS_LMM_TIMER_T3423_LEN                     (54*60*1000) /*T3412:54min*/
     #endif
#endif
/*leili modify for isr end*/
#define NAS_LMM_TIMER_NOT_CARE           (0)
#define NAS_LMM_TIMER_ZERO_VALUE         (0)
#define TI_NAS_LMM_TIMER_MAX_LEN         (18*60*60*1000)     /* 18Сʱ */

#define NAS_LMM_TIMER_161722Atmpt5CSPS1_TRUE             (1)
#define NAS_LMM_TIMER_161722Atmpt5CSPS1_FALSE            (0)

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
/*****************************************************************************
    ö����    : NAS_LMM_TIMER_RUN_STA_ENUM
    ö��˵��  : ��ʱ����״̬:��������,ֹͣ
*****************************************************************************/
enum    NAS_LMM_TIMER_RUN_STA_ENUM
{
    NAS_LMM_TIMER_RUNNING                = 0x00,
    NAS_LMM_TIMER_STOPED,
    NAS_LMM_TIMER_INVALID,

    NAS_LMM_TIMER_BUTT
};
typedef VOS_UINT32   NAS_LMM_TIMER_RUN_STA_ENUM_UINT32;



typedef struct
{
    MSG_HEADER_STRU                          stMsgHeader;     /*_H2ASN_Skip*/
    NAS_LMM_TIMER_RUN_STA_ENUM_UINT32        enTimerStatus;   /* ��ʱ��״̬*/

    VOS_UINT16                               usTimerId;       /* ��ʱ��ID*/
    VOS_UINT16                               usRsv;
    VOS_UINT32                               ulTimerRemainLen;/* ��ʱ����ʱ�� */
}NAS_EMM_TIMER_INFO_STRU;


/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern VOS_VOID    NAS_LMM_InitAllPtlTimer( VOS_VOID );
extern VOS_VOID    NAS_LMM_InitAllStateTimer( VOS_VOID );
extern VOS_VOID    NAS_LMM_InitStateTimer(
                    NAS_LMM_STATE_TI_ENUM_UINT16             enStateTimerId,
                    VOS_UINT32                              ulTimerLen );
extern VOS_VOID    NAS_LMM_InitPtlTimer(
                    NAS_LMM_PTL_TI_ENUM_UINT16             enPtlTimerId,
                    VOS_UINT32                            ulTimerLen );

extern VOS_VOID    NAS_LMM_ModifyPtlTimer(
                           NAS_LMM_PTL_TI_ENUM_UINT16               enPtlTimerId,
                           VOS_UINT32                              ulTimerLen );
extern VOS_VOID    NAS_LMM_ModifyStateTimer(
                           NAS_LMM_STATE_TI_ENUM_UINT16             enStateTimerId,
                           VOS_UINT32                              ulTimerLen );
extern VOS_VOID    NAS_LMM_ResumeStateTimer(
                           NAS_LMM_STATE_TI_ENUM_UINT16             enStateTimerId );
extern VOS_VOID    NAS_LMM_StartStateTimer(
                           NAS_LMM_STATE_TI_ENUM_UINT16             enStateTimerId );
extern VOS_VOID    NAS_LMM_StartPtlTimer(
                           NAS_LMM_PTL_TI_ENUM_UINT16               enPtlTimerId );
extern VOS_VOID    NAS_LMM_Start3402Timer(VOS_UINT8 ucIs161722Atmpt5CsPs1);
/* mod by yanglei 00307272 for VIA_CL_MT_DETACH_NDIS_COLLISION, 2015-07-21, begin */
extern VOS_VOID NAS_LMM_Stop3402Timer(VOS_VOID);
/* mod by yanglei 00307272 for VIA_CL_MT_DETACH_NDIS_COLLISION, 2015-07-21, end */
extern VOS_UINT32  NAS_LMM_IsNeedStop3402Timer(VOS_VOID);
extern VOS_VOID    NAS_LMM_StopAllPtlTimer( VOS_VOID );
extern VOS_VOID    NAS_LMM_StopAllStateTimer( VOS_VOID );
extern VOS_VOID    NAS_LMM_StopPtlTimer(
                           NAS_LMM_PTL_TI_ENUM_UINT16               enPtlTimerId );
extern VOS_VOID    NAS_LMM_StopStateTimer(
                           NAS_LMM_STATE_TI_ENUM_UINT16             enStateTimerId );
extern VOS_VOID    NAS_LMM_SuspendStateTimer(
                           NAS_LMM_STATE_TI_ENUM_UINT16             enStateTimerId );
extern VOS_VOID    NAS_LMM_StopAllStateTimerExceptDelForbTaProidTimer(VOS_VOID);
extern VOS_VOID  NAS_LMM_StartInactivePtlTimer( NAS_LMM_PTL_TI_ENUM_UINT16  enPtlTimerId);
extern VOS_VOID  NAS_LMM_StartInactiveStateTimer( NAS_LMM_STATE_TI_ENUM_UINT16 enStateTimerId );
extern VOS_VOID  NAS_LMM_GetStateTimerLen( NAS_LMM_STATE_TI_ENUM_UINT16   enStateTimerId,
                                          VOS_UINT32   *pulTimerLen);
extern VOS_VOID  NAS_LMM_GetPtlTimerLen( NAS_LMM_PTL_TI_ENUM_UINT16   enStateTimerId,
                                          VOS_UINT32   *pulTimerLen);

extern NAS_LMM_TIMER_RUN_STA_ENUM_UINT32  NAS_LMM_IsStaTimerRunning(
                                    NAS_LMM_STATE_TI_ENUM_UINT16 enStateTimerId );
extern NAS_LMM_TIMER_RUN_STA_ENUM_UINT32  NAS_LMM_IsPtlTimerRunning(
                                    NAS_LMM_PTL_TI_ENUM_UINT16 enPtlTimerId );
extern VOS_VOID    NAS_LMM_StopAllEmmPtlTimer( VOS_VOID );
/* ɾ�����ú��� */
extern VOS_VOID    NAS_LMM_SuspendAllPtlTimerExpT3412( VOS_VOID );
extern VOS_VOID    NAS_LMM_ResumeAllPtlTimer( VOS_VOID );
extern VOS_VOID    NAS_LMM_SuspendAllPtlTimer( VOS_VOID );
extern VOS_VOID    NAS_LMM_StopAllAttachTimer( VOS_VOID );
extern VOS_VOID    NAS_LMM_SuspendInitStopLmmTimer( VOS_VOID );

extern VOS_VOID  NAS_LMM_SndOmEmmTimerStatus(
    NAS_LMM_TIMER_RUN_STA_ENUM_UINT32          enTimerStatus,
    VOS_UINT16                          usTimerId,
    VOS_UINT32                          ulTimerRemainLen
);
extern NAS_LMM_TIMER_CTRL_STRU *NAS_LMM_GetGradualForbidenTimer
(
    VOS_UINT32 ulIndex,
    NAS_LMM_PTL_TI_ENUM_UINT16 enPtlTimerId
);
extern VOS_UINT32  NAS_LMM_IsGradualForbiddenTimerNameValid
(
    VOS_UINT32                          ulIndex,
    NAS_LMM_PTL_TI_ENUM_UINT16          enPtlTimerId
);
extern VOS_UINT32 NAS_LMM_GetGradualForbiddenTimerLen(VOS_UINT32 ulIndex, NAS_LMM_PTL_TI_ENUM_UINT16 enPtlTimerId);
extern VOS_VOID NAS_LMM_StartGradualForbiddenTimer(VOS_UINT32 ulIndex, NAS_LMM_PTL_TI_ENUM_UINT16 enPtlTimerId, VOS_UINT32 ulTimerPara);
extern VOS_VOID  NAS_LMM_StopGradualForbiddenTimer(VOS_UINT32 ulIndex, NAS_LMM_PTL_TI_ENUM_UINT16  enPtlTimerId);
extern NAS_LMM_TIMER_RUN_STA_ENUM_UINT32 NAS_LMM_IsGradualForbiddenTimerRunning(VOS_UINT32 ulIndex,
                                                                        NAS_LMM_PTL_TI_ENUM_UINT16  enPtlTimerId);
/*****************************************************************************
  9 OTHERS
*****************************************************************************/










#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of NasLmmPubMTimer.h */
