

#ifndef _NAS_COMM_H_
#define _NAS_COMM_H_

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "Nas_Mem.h"

#include "NasCommDef.h"
#include "TafAppMma.h"

#include "NasMntn.h"

#include "Nasrrcinterface.h"
#include "TafMtcApi.h"



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 ��������
*****************************************************************************/

/*********************************************************************/
/************** MTF��ַ�궨�� ****************************************/
/*********************************************************************/
#define              ADDRESS_MTF                            32
#define              ADDRESS_TAF                            100

/*********************************************************************/
/************** PD���� (27.A02) **************************************/
/*********************************************************************/
#define              PD_ACMP                                1
#define              PD_RSMP                                2
#define              PD_CCP                                 3
#define              PD_PCP                                 4
#define              PD_SSP                                 5
#define              PD_MTMP                                21
#define              PD_DCP                                 22

/*********************************************************************/
/************** PD���� (24.008) **************************************/
/*********************************************************************/
#define              NAS_PD_GCC                             0x00
#define              NAS_PD_BCC                             0x01
#define              NAS_PD_CC                              0x03
#define              NAS_PD_GTTP                            0x04
#define              NAS_PD_MM                              0x05
#define              NAS_PD_RR                              0x06
#define              NAS_PD_GMM                             0x08
#define              NAS_PD_SMS                             0x09
#define              NAS_PD_SM                              0x0A
#define              NAS_PD_SS                              0x0B
#define              NAS_PD_LS                              0x0C

/* SM����TAF����Ϣ */
#define     NAS_SND_TAFMSG_SM2TAF                           0
/* SM����TAF��ԭ�� */
#define     NAS_RCV_TAFMSG_TAF2SM                           1


/* TAF����MMC��ԭ�� */
#define     NAS_RCV_TAFMSG_TAF2MMC                          2
/* MMC����TAF��ԭ�� */
#define     NAS_SND_TAFMSG_MMC2TAF                          3


/* TAF���͸�RABM��ԭ�� */
#define     NAS_RCV_TAFMSG_TAF2RABM                         4
/* RABM���͸�TAF��ԭ��  */
#define     NAS_SND_TAFMSG_RABM2TAF                         5

/* TAF����CC�ĺ궨�� */
#define     NAS_RCV_TAFMSG_TAF2CC                           6
/* CC����TAF�ĺ궨�� */
#define     NAS_SND_TAFMSG_CC2TAF                           7

/* TAF����SS�ĺ궨�� */
#define     NAS_RCV_TAFMSG_TAF2SS                           8
/* SS����TAF�ĺ궨�� */
#define     NAS_SND_TAFMSG_SS2TAF                           9

#define PS_PTL_VER_R10                                      (7)
#define PS_PTL_VER_R11                                      (8)

/*********************************************************************/
/************** NAS TIMER ID ���� ************************************/
/*********************************************************************/
#define NAS_TIMER_ALL                   0xFF

/* SMS TIMER ID */
#define SMC_TIMER_ID_PS_TC1M_MO         0                                             /* TC1M                                     */
#define SMC_TIMER_ID_PS_TC1M_MT         1                                             /* TC1M                                     */
#define SMC_TIMER_ID_CS_TC1M_MO         2                                             /* TC1M                                     */
#define SMC_TIMER_ID_CS_TC1M_MT         3                                             /* TC1M                                     */
#define SMC_TIMER_ID_TR1M               4
#define SMC_TIMER_ID_TR2M               5
#define SMC_TIMER_ID_TRAM               6

/* GMM TIMER ID */
#define     GMM_TIMER_T3302                              0                      /* T3302��ʱ��                              */
#define     GMM_TIMER_T3310                              1                      /* T3310��ʱ��                              */
#define     GMM_TIMER_T3311                              2                      /* T3311��ʱ��                              */
#define     GMM_TIMER_T3312                              3                      /* T3312��ʱ��                              */
#define     GMM_TIMER_T3316                              4                      /* T3316��ʱ��                              */
#define     GMM_TIMER_T3317                              5                      /* T3317��ʱ��                              */
#define     GMM_TIMER_T3318                              6                      /* T3318��ʱ��                              */
#define     GMM_TIMER_T3320                              7                      /* T3320��ʱ��                              */
#define     GMM_TIMER_T3321                              8                      /* T3321��ʱ��                              */
#define     GMM_TIMER_T3330                              9                      /* T3330��ʱ��                              */
#define     GMM_TIMER_1S                                10                      /* 5�붨ʱ��                                */
#define     GMM_TIMER_PROTECT                           11                      /* ����TIMER(agent)*/
#define     GMM_TIMER_PROTECT_FOR_SIGNALING             12                      /* ����TIMER(������)                        */
#define     GMM_TIMER_SUSPENDED                         13                      /* ��������״̬ */
#define     GMM_TIMER_T3314                             14                      /* GPRS READY TIMER��ʱ�� */
#define     GMM_TIMER_RAU_RSP                           15                      /* GMM RAU RSP TIMER��ʱ�� */
#define     GMM_TIMER_PROTECT_FOR_RR_REL                16                      /* ����TIMER(�ͷ���������)                  */
#define     GMM_TIMER_PROTECT_OLD_TLLI                  17
#define     GMM_TIMER_T3319                             18                      /* T3319��ʱ��                              */
#define     GMM_TIMER_T3340                             19                      /* T3340��ʱ��                              */
#define     GMM_TIMER_INTERRAT_HANDOVER_INFO_CNF        20                      /* �ȴ�WRR�ظ�InterRatHoInfoCnf������ʱ��   */
#define     GMM_TIMER_WAIT_GET_RESEL_SECU_INFO_CNF      (21)                      /* �ȴ�LMM�ظ���ѡ��ȫ�����ı�����ʱ��   */
#define     GMM_TIMER_WAIT_GET_HO_SECU_INFO_CNF         (22)                      /* �ȴ�LMM�ظ��л���ȫ�����ı�����ʱ��   */


#define     GMM_TIMER_WAIT_CONNECT_REL                  (23)                    /* �ȴ������ͷű�����ʱ��   */

#define     GMM_TIMER_TC_DELAY_SUSPEND_RSP              (24)                    /* ��TC��GCF�����У�GMM�ӳ���MMC�ظ�SUSPEND_RSP��ʱ�� */

#define     GMM_TIMER_T3323                             (25)                    /* ISRȥ���ʱ�� */

#define     GMM_TIMER_HO_WAIT_SYSINFO                   (26)                    /* GMM�յ�MM��cs�������Ӳ�������Ϣʱ�ж����W�£�GS���������ڣ�RRC���Ӵ�������ģʽI,cs ps mode��Ҫ������ϵͳ��Ϣ��ʱ����D̬WAS�����ϱ�ϵͳ��Ϣ����ʱ����ʱ��Ҫ������rau*/


#define     GMM_TIMER_DELAY_RADIO_CAPA_TRIGED_RAU       (27)                    /* ��TC��GCF�����У�GMM�ӳ���MMC�ظ�SUSPEND_RSP��ʱ�� */


#define    GMM_TIMER_WAIT_AS_MS_RADIO_CAPA_INFO         (28)                    /* ��rau��attachǰ�жϵ�ǰL������g_GmmGlobalCtrl.ucMsRadioCapSupportLteFromAs�м�¼�Ĳ�һ�£�������ʱ���Ƚ�����ϱ����µ�MS Radio Access capability IE��Ϣ*/

#define     GMM_TIMER_DETACH_FOR_POWER_OFF              (29)                    /* GMM�ػ�detach��ʱ�� */

#define     GMM_TIMER_PROTECT_PS_DETACH                 (30)                    /* GMMCS��detach������ʱ�� */

#define     GMM_TIMER_DELAY_VOICE_DOMAIN_TRIG_RAU       (31)                    /* VOICE DOMAIN�����仯ʱ��GMM��ʱ������RAU,��������ʱ�� */

#define     GMM_TIMER_DELAY_PS_SMS_CONN_REL             (32)                    /* ��ʱ�ͷ�ps��SMS������ */

/* ע��:    �����¶�ʱ������ͬ������ GMM_TIMER_NUM */


/* �������е�TIMER������ͬʱ������ʹ������ĺ���ΪTIMER������ */
#define     GMM_REGSTER_AND_SHUTDOWN_TIMER               99                     /* ��֧��GPRSʱ��Ҫֹͣ�Ķ�ʱ�� */
#define     GMM_TIMER_ALL                                100

#define     GMM_TIMER_ALL_EXCEPT_T3312_T3323                (101)

/* MM TIMER ID */
typedef enum NAS_MM_TIMER_ID
{
    MM_TIMER_T3210                          = 0,
    MM_TIMER_T3211                          = 1,
    MM_TIMER_T3212                          = 2,
    MM_TIMER_T3213                          = 3,
    MM_TIMER_T3214                          = 4,
    MM_TIMER_T3216                          = 5,
    MM_TIMER_T3218                          = 6,
    MM_TIMER_T3220                          = 7,
    MM_TIMER_T3230                          = 8,
    MM_TIMER_T3240                          = 9,
    MM_TIMER_PROTECT_AGENT                  = 10,
    MM_TIMER_PROTECT_DETACH                 = 11,
    MM_TIMER_PROTECT_SIGNALLING             = 12,
    MM_TIMER_PROTECT_CC                     = 13,
    MM_TIMER_PROTECT_CCBS                   = 14,
    MM_TIMER_PROTECT_SUSPEND                = 15,
/* G�£�����ע��, CSʧ��5�κ��ӳ�1�뷢��LU*/
    MM_TIMER_DELAY_LU_GSM                   = 16,
/* G�£�����ע��ɹ���CS��Ҫ�ӳٷ��𻺴��CSҵ�񣬵ȴ�GMM RAU������ȫ����,
   �ݶ��ӳ�1�� */
    MM_TIMER_DELAY_CS_SERVICE_GSM           = 17,

/* ��������ײ��ͷ����Ӻ������ײ������ͷŵı�����ʱ�� */
    MM_TIMER_WAIT_CONNECT_REL               = 18,

/* CSFB ���̴�L HO��GU���ϵͳ��Ϣʱ����ʱ�� */
    MM_TIMER_NORMAL_CSFB_HO_WAIT_SYSINFO    = 19,

/* ������CSFB ���̴�L HO��GU���ϵͳ��Ϣʱ����ʱ�� */
    MM_TIMER_EMERGENCY_CSFB_HO_WAIT_SYSINFO = 20,

/* CSPS ����ģʽI�������, �ػ�ʱ����MM�ĺܶ�״̬��������GMMMM_GPRS_DETACH_COMPLETED,
   ����MM����MMC�ظ�POWER_OFF_CNF. Ϊ��ܴ�����, ��MM�յ�POWER_OFF_REQʱ������ʱ��,
   ����ʱ����ʱ��, MM��MMC�ظ�POWER_OFF_CNF.
   ����ԭ��:
   1. �յ��ػ�����ʱ�������MMC�ظ�POWER_OFF_CNF, ��������
   2. �յ��ػ�����ʱ�������������������ʱ��,��MM_TIMER_PROTECT_DETACH, ��������
   3. �������, �����CSPS ����ģʽI�����, ����Ҫ�����˶�ʱ��
   ������ʾֹͣ�˶�ʱ��, ��Ϊ�ٻظ�POWER_OFF_CNFʱ�� Mm_TimerStop(MM_TIMER_STOP_ALL). */
    MM_TIMER_MODE_I_CS_PS_POWER_OFF_PROTECT = 21,

    MM_TIMER_PROTECT_CS_DETACH              = 22,


    MM_TIMER_WAIT_GET_HO_SECU_INFO_CNF      = 23,

    MM_TIMER_T3242                          = 24,
    MM_TIMER_T3243                          = 25,

    MM_TIMER_PROTECT_MT_CSFB_PAGING_PROCEDURE               = 26,

/* CS HO��ϵͳ��Ϣʱ����ʱ��������ultra Flash CSFB��SRVCC, GU֮��绰�����е�HO */
    MM_TIMER_CS_HO_WAIT_SYSINFO             = 27,

    MM_TIMER_MAX
}NAS_MM_TIMER_ID_ENUM;
typedef VOS_UINT8 NAS_MM_TIMER_ID_ENUM_UINT8;


/* MMA TIMER ID List */
#define TAF_USIM_OPPIN                  (80)      /*����PIN�Ķ�ʱ��ID */
#define MMA_INTERNAL_TIMER_ID           (0x82)    /*�ڲ�������ʱ��������ATTACH������DETACH����*/
#define MMA_TIMER_FOR_PC_REPLAY         (40)      /* �����Ӷ�ʱ�������������MM��ط���Ϣ */
#define TI_MN_PH_RESET                  (41)
#define TI_MN_PH_PIN_OPER               (42)
#define TI_MN_PH_CPHS_SIM_ONS           (43)



/* 6F15�ļ�Refresh�����Զ������������Գ��Զ�ʱ�� */
#define TI_TAF_MMA_PERIOD_TRYING_NETWORK_SELECTION_MENU      (45)

#define TI_TAF_MMA_PNN_LIST_MEM_PROTECT_TIMER           (47)     /* �յ�AT^PNN��ѯPNN LIST������ʱ������ʱ����ʱ��Ϊ15s */


/* �ӳٵ���ػ���ʱ��: E5����ػ�ǰ���ӳ�50ms��AT����ظ�����TASKDELAY�޸�Ϊ��ʱ�� */
#define TI_TAF_MMA_DELAY_POWER_DOWN                          (48)

#define TI_TAF_MMA_NET_SCAN_TIMER                           (49)
#define TI_TAF_MMA_ABORT_NET_SCAN_TIMER                     (50)

/******************************************************************************/
/* End of NAS Timer List */
/******************************************************************************/

#define     MAX_DYNAMIC_MSG_LEN                             1024

#ifndef WUEPS_MEM_NO_WAIT
#define     WUEPS_MEM_NO_WAIT                               (VOS_UINT32)1       /* ���ȴ�   */
#endif

#ifndef WUEPS_MEM_WAIT
#define     WUEPS_MEM_WAIT                                  (VOS_UINT32)(-1)    /* �ȴ�     */
#endif

#define NAS_COMM_BUILD_USIM_GET_FILE_INFO(pstGetfileInfo, enAppTypePara, usEfIdPara, ucRecordNumPara) \
{ \
    (pstGetfileInfo)->usEfId       = usEfIdPara; \
    (pstGetfileInfo)->ucRecordNum  = ucRecordNumPara; \
    (pstGetfileInfo)->enAppType    = enAppTypePara; \
    (pstGetfileInfo)->ucRsv        = 0; \
}

#define NAS_COMM_BUILD_USIM_SET_FILE_INFO(pstSetfileInfo, enAppTypePara, usEfIdPara, ucRecordNumPara, ulEfLenPara, pucEfPara) \
{ \
    (pstSetfileInfo)->enAppType    = enAppTypePara; \
    (pstSetfileInfo)->usEfId       = usEfIdPara; \
    (pstSetfileInfo)->ucRecordNum  = ucRecordNumPara; \
    (pstSetfileInfo)->ucRsv        = 0; \
    (pstSetfileInfo)->ulEfLen      = ulEfLenPara; \
    (pstSetfileInfo)->pucEfContent = pucEfPara; \
}

#define NAS_COMM_MIN(ucValue1, ucValue2) \
   ( (ucValue1) > (ucValue2)) ? (ucValue2) : (ucValue1);


/*****************************************************************************
  3���Ͷ���
*****************************************************************************/
typedef struct
{
    VOS_PID                             ulPid;                    /* ����Timer��PID */
    VOS_UINT32                          ulTimerName;              /* Timer�� */
    VOS_TIMER_PRECISION_ENUM_UINT32     ulPrecision;              /* ��ʱ������ */
}NAS_TIMER_PRECISION_STRU;


enum NAS_TIMER_OPERATION_TYPE_ENUM
{
    NAS_TIMER_OPERATION_START,
    NAS_TIMER_OPERATION_STOP
};
typedef VOS_UINT32  NAS_TIMER_OPERATION_TYPE_ENUM_UINT32;


typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;
    VOS_UINT32                          ulTimeLen;
    NAS_TIMER_OPERATION_TYPE_ENUM_UINT32        ulTimeAction;
}NAS_TIMER_OPERATION_STRU;

/* ����TIM���Ŵ�����ṹ�� */
typedef struct
{
    VOS_UINT32    ulUsed;                           /* 1: ��������Ч 0����������Ч */
    VOS_UINT32    ulErrCode;
}SM_PDP_ACT_ERR_CODE_STRU;
typedef struct
{
    RRC_NAS_SESSION_TYPE_ENUM_UINT8     enNasSessionType;
    MTC_SESSION_TYPE_ENUM_UINT8         enMtcSessionType;
    VOS_UINT8                           aucReserved[2];
}NAS_CONVERT_MTC_SESSION_STRU;




/*****************************************************************************
  4 �궨��
*****************************************************************************/

#define     Cm_MemSet(pBuf,Data,Len)    PS_NAS_MEM_SET((pBuf),(Data),(Len))
#define     Cm_MemCpy(pDst,pSrc,Len)    PS_NAS_MEM_CPY((pDst),(pSrc),(Len))
#define     Cm_Malloc(ulPid, ulSize)    PS_NAS_MEM_ALLOC((ulPid),(ulSize), WUEPS_MEM_NO_WAIT)
#define     Cm_Free(ulPid, pMem)        PS_NAS_MEM_FREE((ulPid),(pMem))

#define     NAS_MEM_FAIL()              PS_NAS_LOG(WUEPS_PID_SS, 0, PS_LOG_LEVEL_ERROR, "NAS Mem Operation Failed!");
#define     NAS_MSG_FAIL()              PS_NAS_LOG(WUEPS_PID_SS, 0, PS_LOG_LEVEL_ERROR, "NAS Msg Opration Failed!");
#define     NAS_TIMER_FAIL()            PS_NAS_LOG(WUEPS_PID_SS, 0, PS_LOG_LEVEL_ERROR, "NAS Timer Opration Failed!");

/* ��PID,MsgName,�Լ�EventType�Ĳ��� */
/*
    Լ��: PID�ṹ Bit0~Bit11: ģ��ID  Bit12~Bit15: ���� Bit16~Bit19: CPU ID Bit20~Bit31: ����
    ��: PID: 0x000A0BCD  ->  0x0000ABCD  ->  0xABCD0000
        MSG: 0x0000abcd
        EVT: 0xABCDabcd
*/
#define NAS_BuildEventType(ulSndPid, usMsgName) \
    (((VOS_UINT32)(/*lint -e778*/((ulSndPid) & 0xF0000)/*lint +e778*/ \
    | (((ulSndPid) & 0xFFF) << 4)) << 12) | (usMsgName))      /* ���� Pid�Լ�usMsgName ����EventType  */

#define NAS_ExtractMsgNameFromEvtType(ulEventType)     ((VOS_UINT16)((ulEventType) & 0x0000FFFF))          /* ��EventType�л�ȡMsgName     */
#define NAS_ExtractSndPidFromEvtType(ulEventType)  \
    ((((ulEventType) & 0xFFF0000) >> 16) | (((ulEventType) & 0xF0000000) >> 12))   /* ��EventType�л�ȡSndPid      */

#define NAS_GetMsgSenderPid(pMsg)                      (((MSG_HEADER_STRU*)pMsg)->ulSenderPid)
#define NAS_GetMsgLength(pMsg)                         (((MSG_HEADER_STRU*)pMsg)->ulLength)
#define NAS_GetMsgName(pMsg)                           (((MSG_HEADER_STRU*)pMsg)->ulMsgName)
#define NAS_GetTimerName(pMsg)                         (PS_GET_REL_TIMER_NAME(pMsg))




/*****************************************************************************
  5 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  6 �ӿں�������
*****************************************************************************/
extern VOS_VOID DIAG_TraceReport(VOS_VOID *pMsg);

extern VOS_UINT32   NAS_StartRelTimer(
    HTIMER                              *phTm,
    VOS_PID                             Pid,
    VOS_UINT32                          ulLength,
    VOS_UINT32                          ulName,
    VOS_UINT32                          ulParam,
    VOS_UINT8                           ucMode
);

extern VOS_TIMER_PRECISION_ENUM_UINT32 NAS_GetTimerPrecision(
        VOS_PID                             Pid,
        VOS_UINT32                          ulName
    );
extern VOS_UINT32   NAS_StopRelTimer(
    VOS_PID                             Pid,
    VOS_UINT32                          ulName,
    HTIMER                              *phTm
);

/***  All the following functions are defined in MM_CellProc1.c  ***/
extern VOS_VOID NAS_MM_StoreCsUnavailableInfo(
    VOS_UINT16                          usCause,
    NAS_MNTN_CS_UNAVAILABLE_INFO_STRU  *pstCsUnavailableInfo
);

/***  All the following functions are defined in GmmAttach.c  ***/
extern VOS_VOID NAS_GMM_StorePsUnavailableInfo(
    VOS_UINT8                           ucCause,
    NAS_MNTN_PS_UNAVAILABLE_INFO_STRU  *pstPsUnavailableInfo
);

extern VOS_BOOL NAS_PreventTestImsiRegFlg(VOS_VOID);

VOS_UINT32 NAS_ConvertSessionTypeToMTCFormat(
    RRC_NAS_SESSION_TYPE_ENUM_UINT8     enNasSessionType,
    MTC_SESSION_TYPE_ENUM_UINT8        *penMtcSessionType
);


#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif                                        /* __cpluscplus         */

#endif
