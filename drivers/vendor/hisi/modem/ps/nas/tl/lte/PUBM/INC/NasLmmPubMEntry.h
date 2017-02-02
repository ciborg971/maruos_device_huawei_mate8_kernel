/******************************************************************************

        @(#)Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
    File Name       : NasLmmPubMEntry.h
    Description     : NasLmmPubMEntry.c header file
    History     :
******************************************************************************/

#ifndef __NASLMMPUBMENTRY_H__
#define __NASLMMPUBMENTRY_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include    "vos.h"
#include    "NasLmmPublic.h"
#include    "NasLmmPubMFsm.h"
#include    "NasEmmPubUCnMsgDecode.h"

#include    "LRrcLNasInterface.h"
#include    "EmmEsmInterface.h"
#include    "EmmRabmInterface.h"
#include    "NasLmmPubMIntraMsg.h"
#include    "NasEmmcEmmInterface.h"
#include    "NasEmmSecuInterface.h"
#include    "NasLmmPubMNvim.h"

#include    "NasEmmSecuOm.h"

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
#define NAS_EMM_GET_USIM_FILE_TYPE()        g_enReadUsimFileType
#define NAS_EMM_GET_SEND_COUNTER()          g_ulSendMsgCounter
#define NAS_EMM_GET_USIM_SECU_FILE_LEN()    g_ulUsimSecuFileLen

#define NAS_LMM_GET_USIM_EPS_SECU_CONTEXT_ADDR()      g_aucUsimSecuContext


#define NAS_EMM_SOFT_USIM_SEND_MSG_NUM  1

#define NAS_EMM_INTRA_APP_START_OPID    0xffff

#define NAS_EMM_PROC_OVER               1                   /* ��Ϣ�ѱ����� */
#define NAS_EMM_PORC_NO                 0                   /* ��Ϣû�д��� */

#define NAS_EMM_SEND_MMC_ERR            VOS_ERR
#define NAS_EMM_SEND_MMC_OK             VOS_OK

#define NAS_EMM_SEND_RRC_ERR            VOS_ERR
#define NAS_EMM_SEND_RRC_OK             VOS_OK

#define NAS_EMM_BIT_NO_SLCT             0
#define NAS_EMM_BIT_SLCT                1

#define NAS_EMM_IS_SUSPEND              1
#define NAS_EMM_NOT_SUSPEND             0
#define NAS_LMM_MAX_MSG_PROC_LOOP        0x08
#define NAS_LMM_MSGID_DPID_POS           0x00FFFFFF

#define NAS_LMM_CN_MSG_MT_POS            0x1
#define NAS_LMM_INTRA_DATA_IND_MT_POS    0x2

#define NAS_LMM_CONTINUE_TO_PROC_BUF_MSG 1
#define NAS_LMM_STOP_PROCING_BUF_MSG     0

#define NAS_USIM_AVAIL                  1
#define NAS_USIM_INAVAIL                0
#define NAS_USIM_INAVAIL_CS             9

#define NAS_LMM_SERTAB_SUPPORT_NONE      0


#define NAS_LMM_BYTE_FF                 0xFF                /* 1111  1111  */
#define NAS_LMM_LOW_HALF_BYTE_F         0x0F                /* 0000  1111  */
#define NAS_LMM_LOW_3_BITS_F            0x07                /* 0000  0111  */

/*
#define NAS_LMM_TIMER_EXP_EVT_SKELETON   \
            (0x00000000UL | (VOS_PID_TIMER << NAS_LMM_MOVEMENT_16_BITS))
*/

#define NAS_LMM_SER_TABLE_UPLMN_BIT     20
#define NAS_LMM_SER_TABLE_OPLMN_BIT     42
#define NAS_LMM_SER_TABLE_HPLMNACT_BIT  43
#define NAS_LMM_SER_TABLE_LPPLMNSI_BIT  74
#define NAS_LMM_SER_TABLE_EMMINFO_BIT   85

#define NAS_LMM_ESM_CAUSE_PDN_CONNECTION_DOES_NOT_EXIST    54


/*
BYTE1 ����Ϣ���ͣ�
0x00-ģ�����Ϣ
0x01-����
0x02-�տ���Ϣ
0x03-��ͨ����
0x04-ʵʱ�������
0x05-�ؼ��¼�
0x06-͸������
*/


#define MSG_TYPE_BETWEEN_PID            0x00000000

#define NAS_LMM_CMP_MSGID(NAS_LMM_MSG_HEAD, ucMsgId)\
            (NAS_LMM_MSG_HEAD |ucMsgId)




#define NAS_LMM_PARA_FSM_ID_INVALID(enParalFsmId)\
            (NAS_LMM_PARALLEL_FSM_BUTT <= enParalFsmId)


/* ID_BETWEEN_MODEL_MSGID => EVENT TYPE */
#define NAS_LMM_GET_BT_MD_ET(ID_BT_MD_MSGID)\
            (ID_BT_MD_MSGID & NAS_LMM_MSGID_DPID_POS)

#define NAS_LMM_GET_BT_RCV_MD_ET(ID_BT_MD_MSGID)\
            (ID_BT_MD_MSGID & NAS_LMM_MSGID_DPID_POS)

#define NAS_LMM_GET_BT_SND_MD_ET(ID_BT_MD_MSGID)\
            (ID_BT_MD_MSGID & NAS_LMM_MSGID_DPID_POS)

#define NAS_LMM_GET_CN_ET(ID_BT_MD_MSGID, CN_MSG_TYPE)\
            (NAS_LMM_GET_BT_MD_ET(ID_BT_MD_MSGID) | CN_MSG_TYPE)

#define NAS_LMM_GET_RRC_MM_DATA_IND_CN_ET(CN_MSG_TYPE)\
            (NAS_LMM_GET_CN_ET((ID_LRRC_LMM_DATA_IND), (CN_MSG_TYPE<< NAS_LMM_MOVEMENT_24_BITS)))


/* TIMER EXP MSG =>  EVENT TYPE * */
/*
#define NAS_LMM_TIMER_EXP_MSG_ET(usNasMmTi)\
            (NAS_LMM_TIMER_EXP_EVT_SKELETON | usNasMmTi)
*/
/*****************************************************************************
  3 Massage Declare
*****************************************************************************/



/*****************************************************************************
  4 Enum
*****************************************************************************/


/*****************************************************************************
  �ṹ����    : NAS_LMM_LOCAL_DETACH_FLAG_ENUM
  ʹ��˵��    : CMCC��������L��ǰ�Ƿ������ܹ�����տ�DETACH��������ֻҪ�˱�ʶ
                ��Ч��LMM���յ�MMC��DETACH����ʱ��ֱ��������DETACH���˱�ʶ��ֵ��
                GUͨ��MML�ӿ��ṩ
*****************************************************************************/

enum NAS_LMM_LOCAL_DETACH_FLAG_ENUM
{
    NAS_LMM_LOCAL_DETACH_FLAG_INVALID                = 0X00,
    NAS_LMM_LOCAL_DETACH_FLAG_VALID                  = 0X01,
    NAS_LMM_LOCAL_DETACH_FLAG_BUTT
};
typedef  VOS_UINT8    NAS_LMM_LOCAL_DETACH_FLAG_ENUM_UINT8;

/*****************************************************************************
�ṹ����    : NAS_EMM_EVENT_TYPE_ENUM
ʹ��˵��    : OSA, EMM���ڲ���ϢID, �����������������Ϣ, �γ��¼�����
               EVENT_TYPE, PUBLIC_Uģ����ݵ�ǰ״̬���¼����͵��ø�ģ��
               �ṩ�ĺ���



NAS_EMM_EVENT_TYPE_ENUM
-----------------------------------------------------------
  �ֽڸ�λ                                      �ֽڵ�λ
-----------------------------------------------------------
| BYTE4��4λ + 0000 |  BYTE3    |   BYTE2    |    BYTE1   |
-----------------------------------------------------------
0000��Э��ģ�����Ϣ|  Դģ��� | CN MSG TYPE| ��Ϣ��0-255
-----------------------------------------------------------
0001��L2 LOG        |           |            |
-----------------------------------------------------------
0010���տ���Ϣ      |           |            |
-----------------------------------------------------------
0011����ͨ����      |           |            |
-----------------------------------------------------------
0100��ʵʱ�������  |           |            |
-----------------------------------------------------------
0101���ؼ��¼�      |           |            | ��������
-----------------------------------------------------------


NAS_EMM_EVENT_TYPE_ENUM �� ulMsgID�Ľṹ������:
BYTE2:  ulMsgID�е�Ŀ��ģ�����һ����MM��ģ��ţ�
        NAS_EMM_EVENT_TYPE_ENUM�и�Ϊ CN MSG TYPE��

ulMsgID����4����:
---------------------------------------------------------->
  �ֽڸ�λ                                      �ֽڵ�λ
-----------------------------------------------------------
|   BYTE1           |   BYTE2   |   BYTE3    |    BYTE4   |
-----------------------------------------------------------
0000��Э��ģ�����Ϣ|  Դģ��� |  Ŀ��ģ���| ��Ϣ��0-255
-----------------------------------------------------------

BYTE1 ����Ϣ���ͣ�
0x00-ģ�����Ϣ
0x01-����
0x02-�տ���Ϣ
0x03-��ͨ����
0x04-ʵʱ�������
0x05-�ؼ��¼�
0x06-͸������

BYTE2��Դģ��ID��ȡֵ�μ�2.1��2.2��
BYTE3��Ŀ��ģ�飬ȡֵ��ΧͬBYTE2
BYTE4����Ϣ�ţ�0~255


TIMER MSG��EVENT TYPE�ṹ
-----------------------------------------------------------
  �ֽڸ�λ                                      �ֽڵ�λ
-----------------------------------------------------------
| BYTE4��4λ + 0000 |  BYTE3    |   BYTE2    |    BYTE1   |
-----------------------------------------------------------
00FF��TIMER ��Ϣ   |VOS_PID_TIMER|  0000     |     TI
-----------------------------------------------------------
ͬ: NAS_LMM_TIMER_EXP_EVT_SKELETON

*****************************************************************************/

enum NAS_LMM_USIM_FILE_TYPE_ENUM
{
    NAS_LMM_USIM_MANDATORY_FILE                 = 0, /*�ض��ļ�*/
    NAS_LMM_USIM_OPTIONAL_FILE                  = 1, /*��ѡ�ļ�*/
    NAS_LMM_USIM_TYPE_BUTT
};
typedef  VOS_UINT32    NAS_LMM_USIM_FILE_TYPE_ENUM_UINT32;

typedef  VOS_UINT32    NAS_LMM_EVENT_TYPE_ENUM_UINT32;
typedef  VOS_UINT32    NAS_EMMC_EVENT_TYPE_ENUM_UINT32;
typedef  VOS_UINT32    NAS_EMM_EVENT_TYPE_ENUM_UINT32;



/*****************************************************************************
  5 STRUCT
*****************************************************************************/

typedef VOS_VOID (* NAS_LMM_ERRLOG_ACT_FUN )
(
    VOS_VOID*,
    EMM_OM_ERRLOG_TYPE_ENUM_UINT16
);

typedef struct
{
    NAS_LMM_MAIN_STATE_ENUM_UINT16              enCurState;
    NAS_LMM_ERRLOG_ACT_FUN                      pfErrlogFun;
}NAS_LMM_ERRLOG_ACT_STRU;

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/
extern  NAS_LMM_USIM_FILE_TYPE_ENUM_UINT32 g_enReadUsimFileType;
extern  VOS_UINT32 g_ulUsimSecuFileLen;

extern  VOS_UINT8  g_aucUsimSecuContext[NAS_NVIM_SECU_CONTEXT_MAX_LEN];


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern  VOS_UINT32  MM_FidInit (    enum VOS_INIT_PHASE_DEFINE ip );

#if (VOS_OS_VER == VOS_WIN32)/*��PC�����£��Ż����PID��ʼ�����������廷���£���GU MM�����ʼ��*/
extern  VOS_UINT32 NAS_MMC_PidInit ( enum VOS_INIT_PHASE_DEFINE ip );
extern  VOS_UINT32 NAS_GMM_PidInit ( enum VOS_INIT_PHASE_DEFINE ip );
extern  VOS_UINT32 NAS_GUMM_PidInit ( enum VOS_INIT_PHASE_DEFINE ip );

extern  VOS_UINT32 NAS_SMS_PidInit ( enum VOS_INIT_PHASE_DEFINE ip );

extern void   NAS_MmcStub_TaskEntry (MsgBlock *pMsg);
extern void   NAS_GmmStub_TaskEntry (MsgBlock *pMsg);
extern VOS_VOID  NAS_GUMmStub_TaskEntry( MsgBlock* pMsg );

VOS_VOID  NAS_SmsStub_TaskEntry( MsgBlock* pMsg );
#endif

extern  VOS_UINT32  NAS_LMM_Entry(       MsgBlock *pMsg);
extern  VOS_UINT32  NAS_LMM_MsgHandle(   MsgBlock *          pMsg,
                                        VOS_UINT32          ulEventType);
extern  VOS_UINT32  NAS_LMM_GetEventType(MsgBlock                        *pMsg,
                                        NAS_EMM_EVENT_TYPE_ENUM_UINT32  *pulEmmEt );
/*extern  VOS_VOID    NAS_LMM_PrintCnMsg(  LRRC_LMM_DATA_IND_STRU                *pMsg );*/
extern  VOS_UINT32  NAS_LMM_MsgPreProcess(MsgBlock *         pMsg );
extern  VOS_UINT32  NAS_LMM_PreProcAppStopReq(   MsgBlock  * pMsg);
extern  VOS_UINT32  NAS_LMM_PreProcAppStartReq(   MsgBlock  * pMsg);
extern VOS_UINT32  NAS_LMM_ProcAppDetReq
(
    const MMC_LMM_DETACH_REQ_STRU            *pstAppDetReq
);

extern  VOS_UINT32  NAS_LMM_PreProcAppDetReq(MsgBlock  * pMsg);
extern  VOS_UINT32  NAS_LMM_PreProcIntraSystemInfoInd(MsgBlock  * pMsg);
extern  VOS_UINT32  NAS_LMM_IntraMsgProcess(VOS_VOID);
extern  VOS_UINT32  NAS_LMM_BufMsgProcess(VOS_VOID);
extern  VOS_UINT32  NAS_LMM_EmmBufMsgProcess(    VOS_VOID );
extern  VOS_UINT32  NAS_LMM_MmcBufMsgProcess(    VOS_VOID);

/*extern  VOS_UINT32  NAS_EMM_JudgeFirstBufMsgCanBeProc(  NAS_EMM_EVENT_TYPE_ENUM_UINT32  ulEmmEt );
 */
extern  VOS_VOID    NAS_LMM_PUBM_Init(           VOS_VOID );
extern  VOS_VOID    NAS_LMM_PUBM_Init_FidInit(   VOS_VOID );
extern  VOS_VOID    NAS_LMM_MainContextInit(     VOS_VOID );
extern  VOS_VOID    NAS_LMM_AuxFsmInit(          VOS_VOID);
extern  VOS_VOID    NAS_LMM_TimerInit(           VOS_VOID);
extern  VOS_VOID    NAS_LMM_IntraMsgQueueInit(   VOS_VOID);
extern  VOS_UINT32  NAS_EMM_JudgeStableState(   VOS_VOID);

extern  VOS_UINT32  NAS_LMM_MsNullSsNullReadingUsimMsgUsimCnf( MsgBlock  * pMsg);
extern  VOS_UINT32  NAS_LMM_MsNullSsNullReadingUsimTimerExp (MsgBlock  * pMsg);
extern  VOS_VOID    NAS_LMM_EmmAndMmcGlobInfoClear( VOS_VOID );
extern  VOS_VOID    NAS_LMM_EmmSubModGlobInit(VOS_VOID );
extern VOS_VOID  NAS_LMM_EmmSubModGlobClear(VOS_VOID);
extern  VOS_UINT32  NAS_LMM_MsNullSsWaitUsimReadyMsgUsimStatusInd( VOS_VOID );
extern  VOS_UINT32  NAS_LMM_PreProcUsimSetCnf(   MsgBlock  * pMsg);
extern  VOS_VOID    NAS_LMM_SetImsiUnavail( VOS_VOID );

extern  VOS_VOID  NAS_LMM_ReadUsimEmmInfoFile( VOS_VOID );
extern  VOS_VOID  NAS_LMM_FreeDynMem( VOS_VOID );
extern  VOS_VOID  NAS_LMM_SubModFreeDyn( VOS_VOID );
extern  VOS_VOID  NAS_LMM_SendRabmRrcConRelInd(EMM_ERABM_REL_CAUSE_ENUM_UINT32      enRelCause);
/* zhaochen 00308719 begin for austin roam plmn selection optimise 2015-06-29 */
extern  VOS_VOID  NAS_LMM_SendCssStopInd( VOS_VOID );
extern  VOS_VOID  NAS_LMM_SendCssStartInd( VOS_VOID );
/* zhaochen 00308719 begin for austin roam plmn selection optimise 2015-06-29 */
extern  VOS_UINT32  NAS_LMM_PreProcMsgUsimStatusInd( MsgBlock  *pMsg );

/* lihong00150010 emergency tau&service begin */
/*extern  VOS_VOID    NAS_LMM_ProcUsimStatusIndWhenUsimInvalid( VOS_VOID );*/
/* lihong00150010 emergency tau&service end */
extern  VOS_VOID    NAS_LMM_PUBM_ClearResource(VOS_VOID);
extern  VOS_VOID    NAS_LMM_DeregReleaseResource(VOS_VOID);
extern  VOS_UINT32  NAS_LMM_MsRegSsWaitAccessGrantIndMsgUsimStausInd(VOS_VOID);
extern  VOS_UINT32  NAS_LMM_MsRegInitSsAttachWaitEsmPdnRspMsgUsimStausInd(VOS_VOID);
extern  VOS_UINT32  NAS_LMM_MsAnyStateSsWaitRrcRelIndMsgUsimStausInd(VOS_VOID);
extern  VOS_VOID    NAS_EMM_SendDetachReqMo(VOS_VOID);
extern  VOS_VOID    NAS_EMM_ProcLocalNoUsim( VOS_VOID );
extern  VOS_UINT32  NAS_EMM_PreProcMsgDelForbTaTimerExpire( MsgBlock *pMsg );
extern  VOS_UINT32  NAS_EMM_PreProcMsgWaitSyscfgCnfTimerExpire( MsgBlock *pMsg );
extern  VOS_UINT32  NAS_LMM_PreProcMmcRelReq( MsgBlock *          pMsg );
extern  VOS_UINT32  NAS_EMM_PreProcMsgT3416Exp     ( MsgBlock *        pMsg );
extern  VOS_UINT32  NAS_EMM_PreProcMsgSwithOffTimerExp( MsgBlock *        pMsg );
extern  VOS_UINT32  NAS_LMM_MsResumeSsResumeRrcOriWaitSysInfoIndMsgUsimStausInd( VOS_VOID );
extern VOS_UINT32 NAS_LMM_PreProcInfoChangeNotifyReq
(
    MsgBlock                           *pstMsg
);
extern VOS_UINT32  NAS_LMM_PreProcRrcSysCfgCnf( MsgBlock  *pMsg );
extern VOS_UINT32  NAS_LMM_PreProcMmcSysCfgReq( MsgBlock  *pMsg );
extern VOS_UINT32  NAS_LMM_SendMmcSysCfgCnf( MMC_LMM_RESULT_ID_ENUM_UINT32 ulRst );
extern VOS_VOID  NAS_LMM_SaveCurRatToPreRat(VOS_VOID );
extern VOS_UINT32  NAS_LMM_SendRrcSysCfgReq( MsgBlock  *pMsg );
extern VOS_UINT32  NAS_LMM_PreProcMsgAppMmAttachReq( MsgBlock *        pMsg );
extern VOS_VOID NAS_LMM_ImsiDetachReleaseResource( VOS_VOID );
extern MMC_LMM_ATTACH_RSLT_ENUM_UINT32  NAS_LMM_SupendResumeAttachRslt( MsgBlock  *pMsg );
extern VOS_VOID  NAS_EMM_SendLrrcOssStateReq( VOS_VOID );
extern VOS_UINT32  NAS_LMM_PreProcMmcOocStateReq( MsgBlock  *pMsg );
extern VOS_UINT32  NAS_LMM_PreProcRrcDataCnf( MsgBlock  *pMsg );

extern VOS_UINT32  NAS_LMM_PreProcIntraCoverageLostInd( MsgBlock  *pMsg );
extern VOS_UINT32  NAS_EMM_PreProcMsgT3402Exp( MsgBlock *          pMsg );

extern VOS_UINT32  NAS_EMM_PreProcMsgCsfbDelayTimerExp( MsgBlock *          pMsg );

extern VOS_UINT32  NAS_LMM_PreProcrRrcDataInd      ( MsgBlock *        pMsg );
extern  VOS_UINT32  NAS_LMM_PreProcMsgEsmClrEsmPrcResNotify
(
    MsgBlock                           *pMsg
);

extern VOS_UINT32 NAS_EMM_IsSuspended( VOS_VOID );

extern VOS_VOID  NAS_LMM_SendMmcSuspendInfoChangeRatChange(
                LMM_MMC_RAT_CHANGE_TYPE_ENUM_UINT32 ulRatChangeType);
extern VOS_VOID  NAS_EMM_TcSendRelInd(VOS_VOID);
extern VOS_UINT32 NAS_LMM_RevMmcModemInfoReq(MsgBlock *  pMsg);

extern VOS_UINT32  NAS_LMM_MsSuspendOrResumePreProcAppDetReq
(
    const MMC_LMM_DETACH_REQ_STRU            *pstAppDetReq
);

extern VOS_UINT32  NAS_LMM_IsSvlteOrLcNeedLocalDetach(VOS_VOID);

extern VOS_VOID  NAS_LMM_MsRegSsAnyLocalDetStateTrans(VOS_VOID);

extern VOS_UINT32  NAS_LMM_SvlteOrLcPsLocalDetachProc
(
    const MMC_LMM_DETACH_REQ_STRU            *pstAppDetReq
);


/*add by lifuxin for Lnas est&rel process re-construct start*/
extern VOS_UINT32  NAS_EMM_PreProcMsgRrcMmEstCnf(MsgBlock * pMsg);
extern VOS_UINT32  NAS_EMM_PreProcMsgTIWaitRrcConnTO(MsgBlock * pMsg);
extern VOS_UINT32  NAS_EMM_PreProcMsgRrcMmRelCnf(MsgBlock * pMsg);
extern VOS_UINT32  NAS_EMM_PreProcMsgTiWaitRrcRelTO(MsgBlock * pMsg);
extern VOS_UINT32  NAS_EMM_PreProcMsgWaitRrcRel3440TO(MsgBlock * pMsg);
extern VOS_UINT32  NAS_EMM_PreProcMsgReAttachDelayTO(MsgBlock * pMsg);
/*add by lifuxin for Lnas est&rel process re-construct end*/

/*chengmin for L signal report begin*/
extern VOS_UINT32 NAS_LMM_SendRrcCellSignReportNotify(VOS_UINT8 ucMinRptTimerInterval, VOS_UINT8 ucSignThreshold);
extern VOS_UINT32 NAS_LMM_SendMccCellSignReportInd(MsgBlock  *pstMsg);
extern VOS_UINT32 NAS_EMM_PreProcMsgRrcCellSignReportInd(MsgBlock  *pstMsg);
extern VOS_UINT32 NAS_LMM_PreProcMmcCellSignReportNotify(MsgBlock  *pstMsg);
/*chengmin for L signal report end*/
extern VOS_UINT32 NAS_EMM_PreProcMsgRrcPagingInd(MsgBlock  *pstMsg);

extern VOS_VOID NAS_EMM_ProcErrlogEstCnfOrDataCnfFail(
                 VOS_VOID*                         pstEmmProcessFail,
                 EMM_OM_ERRLOG_TYPE_ENUM_UINT16    enErrType);

VOS_VOID  NAS_LMM_SendRrcDisableLteNotify(VOS_VOID);

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
extern VOS_UINT32  NAS_LMM_PreProcMsgEsmClLocalDetachNotify(
    MsgBlock                           *pMsg
);
#endif
extern VOS_UINT32 NAS_LMM_PreProcMsgGradualForbTimerExpire(MsgBlock *pstMsg);
extern VOS_UINT32 NAS_LMM_PreProcMsgGradualForbAgingTimerExpire(MsgBlock *pstMsg);
/* zhaochen 00308719 add for set UE center 2015-09-10 begin */
extern VOS_UINT32 NAS_EMM_RcvMtaSetUECenterReq(MsgBlock *pstMsg);
extern VOS_UINT32  NAS_EMM_RcvMtaQryUECenterReq(MsgBlock *pMsg);
/* zhaochen 00308719 add for set UE center 2015-09-10 end */

/****************************************************************************
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

#endif /* end of NasLmmPubMEntry.h*/

