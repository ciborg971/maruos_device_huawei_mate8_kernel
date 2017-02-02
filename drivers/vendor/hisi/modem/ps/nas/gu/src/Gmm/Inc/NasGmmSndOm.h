
#ifndef _NAS_GMM_SND_OM_H
#define _NAS_GMM_SND_OM_H_

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include  "vos.h"
#include  "PsTypeDef.h"

#include "NasUtranCtrlInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/


enum NAS_GMM_OM_MSG_ID_ENUM
{
    /* MM���͸�OM����Ϣ */
    GMMOM_LOG_STATE_INFO_IND                       = 0x1000,      /*_H2ASN_MsgChoice  NAS_GMM_LOG_STATE_INFO_STRU */
    GMMOM_LOG_AUTH_INFO_IND                        = 0x1001,      /*_H2ASN_MsgChoice  NAS_GMM_LOG_AUTH_INFO_STRU */
    GMMOM_LOG_RADIAO_ACCESS_CAP                    = 0x1002,      /*_H2ASN_MsgChoice  NAS_GMM_LOG_GAS_RADIO_ACCESS_CAP_STRU */

    GMMOM_LOG_CTX_INFO_IND                         = 0x1003,      /*_H2ASN_MsgChoice  GMMOM_LOG_CTX_INFO_STRU */
    GMMOM_LOG_BUTT
};
typedef VOS_UINT32 NAS_GMM_OM_MSG_ID_ENUM_UINT32;
enum NAS_GMM_STATE_ID_ENUM
{
    STATE_GMM_ID_NULL                                     =  0x00,              /* GMM_NULL״̬                             */
    STATE_GMM_REGISTERED_INITIATED                        =  0x01,              /* GMM-REGISTERED-INITIATED״̬             */
    STATE_GMM_DEREGISTERED_INITIATED                      =  0x02,              /* GMM_DEREGISTERED_INITIATED               */
    STATE_GMM_ROUTING_AREA_UPDATING_INITIATED             =  0x03,              /* GMM_ROUTING_AREA_UPDATING_INITIATED      */
    STATE_GMM_SERVICE_REQUEST_INITIATED                   =  0x04,              /* GMM-SERVICE-REQUEST-INITIATED            */

    STATE_GMM_TC_ACTIVE                                   =  0x05,              /* GMM-TC-ACTIVE(����TCʱ��״̬)            */
    STATE_GMM_GPRS_SUSPENSION                             =  0x06,              /* (GSM only)GMM_GPRS_SUSPENSION */

    STATE_GMM_DEREGISTERED_NORMAL_SERVICE                 =  0x10,              /* GMM-DEREGISTERED.NORMAL-SERVICE          */
    STATE_GMM_DEREGISTERED_LIMITED_SERVICE                =  0x11,              /* GMM-DEREGISTERED.LIMITED-SERVICE         */
    STATE_GMM_DEREGISTERED_ATTACH_NEEDED                  =  0x12,              /* GMM-DEREGISTERED.ATTACH-NEEDED           */
    STATE_GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH           =  0x13,              /* GMM-DEREGISTERED.ATTEMPTING-TO-ATTACH    */
    STATE_GMM_DEREGISTERED_NO_CELL_AVAILABLE              =  0x14,              /* GMM-DEREGISTERED.NO-CELL-AVAILABLE       */
    STATE_GMM_DEREGISTERED_PLMN_SEARCH                    =  0x15,              /* GMM-DEREGISTERED.PLMN-SEARCH             */
    STATE_GMM_DEREGISTERED_NO_IMSI                        =  0x16,              /* GMM-DEREGISTERED.NO-IMSI                 */

    STATE_GMM_REGISTERED_NORMAL_SERVICE                   =  0x20,              /* GMM-REGISTERED.NORMAL-SERVICE            */
    STATE_GMM_REGISTERED_LIMITED_SERVICE                  =  0x21,              /* GMM-REGISTERED.LIMITED-SERVICE           */
    STATE_GMM_REGISTERED_UPDATE_NEEDED                    =  0x22,              /* GMM-REGISTERED.UPDATE-NEEDED             */
    STATE_GMM_REGISTERED_ATTEMPTING_TO_UPDATE             =  0x23,              /* GMM-REGISTERED.ATTEMPTING-TO-UPDATE      */
    STATE_GMM_REGISTERED_NO_CELL_AVAILABLE                =  0x24,              /* GMM-REGISTERED.NO-CELL-AVAILABLE         */
    STATE_GMM_REGISTERED_PLMN_SEARCH                      =  0x25,              /* GMM-REGISTERED.PLMN-SEARCH               */
    STATE_GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM          =  0x26,              /* GMM-REGISTERED.ATTEMPTING-TO-UPDATE-MM   */
    STATE_GMM_REGISTERED_IMSI_DETACH_INITIATED            =  0x27,              /* GMM-REGISTERED.IMSI-DETACH-INITIATED     */

    STATE_GMM_SUSPENDED_NORMAL_SERVICE                    =  0x30,              /* GMM-SUSPENDED.NORMAL-SERVICE             */
    STATE_GMM_SUSPENDED_GPRS_SUSPENSION                   =  0x31,              /* GMM-SUSPENDED.GPRS-SUSPENSION            */
    STATE_GMM_SUSPENDED_WAIT_FOR_SYSINFO                  =  0x32,              /* GMM-SUSPENDED.WAIT-FOR-SYSINFO           */

    STATE_GMM_TYPE_BUTT
};
typedef VOS_UINT8 NAS_GMM_STATE_ID_ENUM_UINT8;

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
    MSG_HEADER_STRU                     stMsgHeader;/* ��Ϣͷ */ /*_H2ASN_Skip*/

    NAS_GMM_STATE_ID_ENUM_UINT8         enGmmState;
    VOS_UINT8                           aucRsv3[3];
}NAS_GMM_LOG_STATE_INFO_STRU;
typedef struct
{
    VOS_UINT8                           ucT3312ExpiredFlg; /* ��¼g_GmmRauCtrl.ucT3312ExpiredFlg T3312��ʱ���Ƿ�ʱ��ʶ */
    VOS_UINT8                           ucT3311ExpiredFlg; /* ��¼g_GmmRauCtrl.ucT3311ExpiredFlg T3311�Ƿ�ʱ��ʶ */
    VOS_UINT8                           aucReserved[2];
}GMMOM_LOG_GMM_RAU_CTRL_INFO_STRU;



typedef struct
{
    VOS_UINT8                               ucCnfMask;     /* ��¼g_GmmReqCnfMng.ucCnfMask*/
    VOS_UINT8                               aucReserved[3];
}GMMOM_LOG_GMM_REQ_CNF_MNG_INFO_STRU;
typedef struct
{
    VOS_UINT8                               ucRetrySrForRelCtrlFlg;     /* ��¼g_GmmServiceCtrl.ucRetrySrForRelCtrlFlg*/
    VOS_UINT8                               aucReserved[3];
}GMMOM_LOG_GMM_SERVICE_CTRL_INFO_STRU;
typedef struct
{
    VOS_UINT32                               ulTimerRunMask;     /* ��¼g_GmmTimerMng.ulTimerRunMask*/
}GMMOM_LOG_GMM_TIMER_MNG_INFO_STRU;
typedef struct
{
    VOS_UINT8                           ucPreRat;     /* ��¼gstGmmSuspendCtrl.ucPreRat�л�ʱ���뼼�� */
    VOS_UINT8                           ucT3312State; /* ��¼gstGmmSuspendCtrl.ucT3312State T3312��ʱ������״̬ */
    VOS_UINT8                           ucNetModeChange; /*��¼gstGmmSuspendCtrl.ucNetModeChange ��ϵͳ�ı�ʱ����ģʽ�ı������ */
    VOS_UINT8                           ucPreSrvState;   /* ��¼gstGmmSuspendCtrl.ucPreSrvState*/
}GMMOM_LOG_GMM_SUSPEND_CTRL_INFO_STRU;


typedef struct
{
    VOS_UINT8                                   ucPlmnSrchPreSta;        /* ��¼����ǰ��״̬ */
    VOS_UINT8                                   ucSpecProc;              /* ��¼g_GmmGlobalCtrl.ucSpecProc��ǰgmm��ר������ */
    VOS_UINT8                                   UeInfo_UeId_ucUeIdMask;  /* ��¼g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask UeId���ڱ�ʶ */
    VOS_UINT8                                   CsInfo_ucCsTransFlg;     /* ��¼g_GmmGlobalCtrl.CsInfo.ucCsTransFlg CS���Ƿ�ͨ���б�־*/
    VOS_UINT8                                   ucSigConFlg;             /* ��¼g_GmmGlobalCtrl.ucSigConFlg*/
    VOS_UINT8                                   ucRaiChgRelFlg;          /* ��¼g_GmmGlobalCtrl.ucRaiChgRelFlg*/
    VOS_UINT8                                   SysInfo_ucNetMod;        /* ��¼g_GmmGlobalCtrl.SysInfo.ucNetMod*/
    VOS_UINT8                                   ucCvrgAreaLostFlg;       /* ��¼g_GmmGlobalCtrl.ucCvrgAreaLostFlg*/
    VOS_UINT8                                   ucDetachType;            /* ��¼g_GmmGlobalCtrl.stDetachInfo.enDetachType*/
    VOS_UINT8                                   ucRelCause;              /*��¼g_GmmGlobalCtrl.ucRelCause*/
    VOS_UINT8                                   ucSpecProcInCsTrans;     /*��¼g_GmmGlobalCtrl.ucSpecProcInCsTrans*/
    VOS_UINT8                                   SysInfo_ucCellChgFlg;    /*��¼g_GmmGlobalCtrl.SysInfo.ucCellChgFlg*/
    VOS_UINT8                                   UeInfo_ucMsRadioCapSupportLteFromAs; /*��¼g_GmmGlobalCtrl.UeInfo.ucMsRadioCapSupportLteFromAs*/
    GMM_RAI_STRU                                SysInfo_Rai;             /* ��¼g_GmmGlobalCtrl.SysInfo.Rai*/
    VOS_UINT8                                   UeInfo_ucMsRadioCapSupportLteFromRegReq; /*��¼g_GmmGlobalCtrl.UeInfo.ucMsRadioCapSupportLteFromRegReq*/
    NAS_MML_RAI_STRU                            stAttemptToUpdateRai;    /* ��¼GMMǨ��ATTEMPT TO UPDATE״̬��update statusǨ��2ʱ��RAI��Ϣ */
    NAS_MML_VOICE_DOMAIN_PREFERENCE_ENUM_UINT8  UeInfo_enVoiceDomainFromRegRq; /* ��¼g_GmmGlobalCtrl.UeInfo.enVoiceDomainFromRegReq */
    VOS_UINT8                                   aucReserved[3];

    NAS_MML_PLMN_WITH_RAT_STRU                  stAllocT3302ValuePlmnWithRat; /* g_GmmGlobalCtrl.stAllocT3302ValuePlmnWithRat*/
}GMMOM_LOG_GMM_GLOBAL_CTRL_INFO_STRU;


typedef struct
{
    VOS_UINT8                           ucRetryAttachForRelCtrlFlg;     /* ��¼GmmAttachCtrl.ucRetryAttachForRelCtrlFlg Attach���̱��쳣�ͷţ���Ҫ���յ�ϵͳ��Ϣ�����·��� */
    VOS_UINT8                           ucRetryFlg;                     /*��¼g_GmmAttachCtrl.ucRetryFlg*/
    VOS_UINT8                           ucAttachAttmptCnt;              /*��¼g_GmmAttachCtrl.ucAttachAttmptCnt*/
    VOS_UINT8                           ucReserved;
}GMMOM_LOG_GMM_ATTACH_CTRL_INFO_STRU;
typedef struct
{
    VOS_UINT8               ucLastDataSender;            /*��¼gstGmmCasGlobalCtrl.ucLastDataSender*/
    VOS_UINT8               ucSuspendLlcCause;           /*��¼gstGmmCasGlobalCtrl.ucSuspendLlcCause*/
    VOS_UINT8               ucTlliAssignFlg;             /*��¼gstGmmCasGlobalCtrl.ucTlliAssignFlg*/
    VOS_UINT8               ucReserved;
}GMMOM_LOG_GMM_CAS_GLOBAL_CTRL_INFO_STRU;
typedef struct
{
    NAS_MML_TIN_TYPE_ENUM_UINT8              enTinType;     /* ��¼NAS_MML_GetTinType TIN���� */
    VOS_UINT8                                ucT3423State;  /* ��¼NAS_MML_GetT3423Status T3423��ʱ������״̬ */
    VOS_UINT8                                ucPsRegStatus; /* ��¼NAS_MML_GetSimPsRegStatus PS���SIM��ע����Ϣ*/
    VOS_UINT8                                ucWSysInfoDrxLen; /*��¼NAS_MML_GetWSysInfoDrxLen*/
    NAS_MML_RAI_STRU                         stPsLastSuccRai;  /*��¼NAS_MML_GetPsLastSuccRai*/
    NAS_MML_ROUTING_UPDATE_STATUS_ENUM_UINT8 enPsUpdateStatus; /*��¼NAS_MML_GetPsUpdateStatus*/
    VOS_UINT8                                ucPsServiceBufferStatusFlg; /*��¼NAS_MML_GetPsServiceBufferStatusFlg*/
    NAS_MML_MS_MODE_ENUM_UINT8               enMsMode;         /*��¼NAS_MML_GetMsMode*/
    VOS_UINT8                                ucIsTmsiValid;    /*��¼NAS_MML_IsTmsiValid*/
    NAS_MML_PS_BEARER_CONTEXT_STRU           astPsBearerContext[NAS_MML_MAX_PS_BEARER_NUM];  /* ��¼NAS_MML_GetPsBearerCtx */
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8      enCurrUtranMode;  /*��¼NAS_UTRANCTRL_GetCurrUtranMode*/
    VOS_UINT8                                aucReserved[3];
}GMMOM_LOG_MML_CTX_INFO_STRU;
typedef struct
{
    VOS_UINT8               GmmShare_ucGsAssociationFlg;            /*��¼g_MmSubLyrShare.GmmShare.ucGsAssociationFlg*/
    VOS_UINT8               aucReserved[3];
}GMMOM_LOG_MM_SUB_LYR_SHARE_INFO_STRU;
typedef struct
{
    MSG_HEADER_STRU                          stMsgHeader;/* ��Ϣͷ */ /*_H2ASN_Skip*/

    GMMOM_LOG_GMM_SUSPEND_CTRL_INFO_STRU     stGmmSuspendCtrlInfo;
    GMMOM_LOG_GMM_RAU_CTRL_INFO_STRU         stGmmRauCtrlInfo;
    GMMOM_LOG_GMM_GLOBAL_CTRL_INFO_STRU      stGmmGlobalCtrlInfo;
    GMMOM_LOG_GMM_CAS_GLOBAL_CTRL_INFO_STRU  stGmmGasGlobalCtrlInfo;
    GMMOM_LOG_GMM_REQ_CNF_MNG_INFO_STRU      stGmmReqCnfMngInfo;
    GMMOM_LOG_GMM_SERVICE_CTRL_INFO_STRU     stGmmServiceCtrlInfo;
    GMMOM_LOG_GMM_TIMER_MNG_INFO_STRU        stGmmTimerMngInfo;
    GMMOM_LOG_MML_CTX_INFO_STRU              stMmlCtxInfo;
    GMMOM_LOG_MM_SUB_LYR_SHARE_INFO_STRU     stMmSubLyrShareInfo;
}GMMOM_LOG_CTX_INFO_STRU;




/*****************************************************************************
 �ṹ��    : NAS_GMM_LOG_GAS_RADIO_ACCESS_CAP_STRU
 �ṹ˵��  : ��GMM����GAS�ӿڻ�ȡ������ֵ

 �޸ļ�¼  :
 1.��    ��   : 2014��2��27��
   ��    ��   : w0024274
   �޸�����   : ����

*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;/* ��Ϣͷ */ /*_H2ASN_Skip*/

    VOS_UINT32                          ulRst;
    VOS_UINT8                           ucMsCapType;
    VOS_UINT8                           ucRsv;
    VOS_UINT16                          usSize;
    VOS_UINT8                           aucData[MS_RADIO_ACCESS_CAPABILITY_MAX_SIZE];
}NAS_GMM_LOG_GAS_RADIO_ACCESS_CAP_STRU;
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;/* ??? */ /*_H2ASN_Skip*/
    VOS_UINT8                           ucExpectOpId;
    VOS_UINT8                           ucRcvOpId;
    VOS_UINT8                           aucRsv[2];
}NAS_GMM_LOG_AUTH_INFO_STRU;


/*****************************************************************************
  H2ASN������Ϣ�ṹ����
*****************************************************************************/
typedef struct
{
    NAS_GMM_OM_MSG_ID_ENUM_UINT32       enMsgID;    /*_H2ASN_MsgChoice_Export NAS_GMM_OM_MSG_ID_ENUM_UINT32*/

    VOS_UINT8                           aucMsgBlock[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          NAS_GMM_OM_MSG_ID_ENUM_UINT32
    ****************************************************************************/
}NAS_GMM_SND_OM_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    NAS_GMM_SND_OM_MSG_DATA             stMsgData;
}NasGmmSndOm_MSG;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
extern VOS_VOID  NAS_GMM_LogGmmStateInfo(
    VOS_UINT8                           ucGmmState
);

extern VOS_VOID  NAS_GMM_LogGmmCtxInfo(VOS_VOID);

extern VOS_VOID NAS_GMM_LogGasGmmRadioAccessCapability(
    VOS_UINT32                          ulRst,
    VOS_UINT8                           ucMsCapType,
    VOS_UINT16                          usSize,
    VOS_UINT8                          *pucData
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

#endif


