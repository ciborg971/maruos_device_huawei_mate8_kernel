

#ifndef _NASEMMTAUPROC_H
#define _NASEMMTAUPROC_H


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include    "vos.h"
#include    "NasLmmPublic.h"
#include    "NasLmmPubMIntraMsg.h"
#include    "NasLmmPubMFsm.h"
#include    "NasEmmcEmmInterface.h"
#include    "EmmEsmInterface.h"
#include    "NasEmmPubUCnMsgDecode.h"
#include    "NasLmmPubMOsa.h"
#include    "LRrcLNasInterface.h"



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
#define NAS_EMM_NO                              0
#define NAS_EMM_YES                             1

#define EMM_TAU_AD_BIT_SLCT                     1
#define EMM_TAU_AD_BIT_NO_SLCT                  0
#define EMM_TAUSER_LOW5_BITS                    0x0000001F

#define EMM_TAU_REQ_MSG_PD_AND_SEC_TY           0x07

#define NAS_EMM_CN_FO         0xf0
#define NAS_EMM_CN_PLMNID_LEN                   3
#define NAS_EMM_CN_EPS_CONTEXT_LEN              2

#define EMM_COMP_RRC_MSG_HEADER(pMsg,ulMsgLenthNoHeader)\
        {\
            (pMsg)->ulSenderCpuId       = VOS_LOCAL_CPUID;\
            (pMsg)->ulSenderPid         = PS_PID_MM;\
            (pMsg)->ulReceiverCpuId     = VOS_LOCAL_CPUID;\
            (pMsg)->ulReceiverPid       = PS_PID_ERRC;\
            (pMsg)->ulLength            = (ulMsgLenthNoHeader);\
        }

#define EMM_COMP_ESM_MSG_HEADER(pMsg,ulMsgLenthNoHeader)\
        {\
            (pMsg)->ulSenderCpuId       = VOS_LOCAL_CPUID;\
            (pMsg)->ulSenderPid         = PS_PID_MM;\
            (pMsg)->ulReceiverCpuId     = VOS_LOCAL_CPUID;\
            (pMsg)->ulReceiverPid       = PS_PID_ESM;\
            (pMsg)->ulLength            = (ulMsgLenthNoHeader);\
        }


#define NAS_EMM_EPS_BEARER_STATUS_NUM_SEVEN     7
#define NAS_EMM_EPS_BEARER_STATUS_NUM_EIGNT     8

#define NAS_EMM_MS_ID_TYPE_TMSI_PTMSI_MTMSI     (4)

/* TAUģ��ȫ�ֱ��� g_stEmmTAUCtrlTbl�ĺ����*/
#define NAS_EMM_TAU_GetEmmTAUCtrlAddr()                     (&g_stEmmTAUCtrlTbl)

#define NAS_EMM_TAU_GetTAUtype()                            (g_stEmmTAUCtrlTbl.enEmmTauType)
/*#define NAS_EMM_TAU_GetTAUresult()                          (g_stEmmTAUCtrlTbl.enEmmTAUresult)*/
/*#define NAS_EMM_TAU_GetEmmTAURejCause()                     (g_stEmmTAUCtrlTbl.enEmmTAURejCause)*/
#define NAS_EMM_TAU_GetEmmTAUStartCause()                   (g_stEmmTAUCtrlTbl.enEmmTAUStartCause)
#define NAS_EMM_TAU_GetEmmCollisionCtrl()                   (g_stEmmTAUCtrlTbl.enEmmCollisionCtrl)

#define NAS_EMM_TAU_GetEmmTAUAttemptCnt()                   (g_stEmmTAUCtrlTbl.ucTAUAttemptCnt)
#define NAS_EMM_TAU_GetEmmTauReqActiveCtrl()                (g_stEmmTAUCtrlTbl.enEmmTauReqActiveCtrl)
#define NAS_EMM_TAU_GetEmmTauStartConnSta()                 (g_stEmmTAUCtrlTbl.ucTauStartConnSta)
#define NAS_EMM_TAU_GetEmmUplinkPending()                   (g_stEmmTAUCtrlTbl.enUplinkPending)
#define NAS_EMM_TAU_GetEmmCombinedDetachBlockFlag()         (g_stEmmTAUCtrlTbl.enCombinedDetachBlockFlag)
#define NAS_EMM_TAU_GetEmmTauCnRejCause()                      (g_stEmmTAUCtrlTbl.enTauEmmCause)
#define NAS_EMM_TAU_GetEmmTauCnEmmExtRejCauseOp()           (g_stEmmTAUCtrlTbl.bitOpExtCause)
#define NAS_EMM_TAU_GetEmmTauCnEmmExtRejCause()             (g_stEmmTAUCtrlTbl.ucTauRejEmmExtCause)

#define NAS_EMM_TAU_GetEmmForbInfo()                        (g_stEmmTAUCtrlTbl.ulForbInfo)
#define NAS_EMM_TAU_GetOpLai()                              (g_stEmmTAUCtrlTbl.bitOpLai)
#define NAS_EMM_TAU_GetLaiAddr()                            (&(g_stEmmTAUCtrlTbl.stLai))
#define NAS_EMM_TAU_GetOpMsId()                             (g_stEmmTAUCtrlTbl.bitOpMsId)
#define NAS_EMM_TAU_GetMsIdAddr()                           (&(g_stEmmTAUCtrlTbl.stMsId))
#define NAS_EMM_TAU_GetOpCnCause()                          (g_stEmmTAUCtrlTbl.bitOpCnCause)
#define NAS_EMM_TAU_GetCnCause()                            (g_stEmmTAUCtrlTbl.enCnCause)
#define NAS_EMM_TAU_GetEpsUpdateRslt()                      (g_stEmmTAUCtrlTbl.ucEpsUpdataRst)
#define NAS_EMM_TAU_SaveEpsUpdateRslt(EpsUpdatRslt)         (NAS_EMM_TAU_GetEpsUpdateRslt() = (EpsUpdatRslt))
#define NAS_EMM_TAU_SaveForbInfo(ulForbInfo)                (NAS_EMM_TAU_GetEmmForbInfo() = ulForbInfo)
#define NAS_EMM_TAU_GetPeriodTauRegDomain()                 (g_stEmmTAUCtrlTbl.ulPeriodTauRegDomain)
#define NAS_EMM_TAU_SavePeriodTauRegDomain(RegDomain)       (NAS_EMM_TAU_GetPeriodTauRegDomain() = (RegDomain))

#define NAS_EMM_TAU_GetEmmTmoActiveFlagCtrl()               (g_stEmmTAUCtrlTbl.enTmoActiveFlagCtrl)
#define NAS_EMM_TAU_SaveEmmTmoActiveFlagCtrl(ActiveFlag)    (NAS_EMM_TAU_GetEmmTmoActiveFlagCtrl() = (ActiveFlag))

#define NAS_EMM_TAU_GetEmmPtmsiActiveFlagCtrl()             (g_stEmmTAUCtrlTbl.enPtmsiActiveFlagCtrl)
#define NAS_EMM_TAU_SaveEmmPtmsiActiveFlagCtrl(ActiveFlag)  (NAS_EMM_TAU_GetEmmPtmsiActiveFlagCtrl() = (ActiveFlag))


#define NAS_EMM_TAU_GetEmmTauImsiDetachFlag()               (g_stEmmTAUCtrlTbl.enImsiCnDetachFlag)
#define NAS_EMM_TAU_SaveEmmTauImsiDetachFlag(ImsiDetachFlag) (NAS_EMM_TAU_GetEmmTauImsiDetachFlag() = (ImsiDetachFlag))

#define NAS_EMM_TAU_GetEmmTauCompleteFlag()               (g_stEmmTAUCtrlTbl.enTauCompleteFlag)
#define NAS_EMM_TAU_SaveEmmTauCompleteFlag(TauCompleteFlag) (NAS_EMM_TAU_GetEmmTauCompleteFlag() = (TauCompleteFlag))
#define NAS_EMM_TAU_GetEmmTauContainDrxFlag()               (g_stEmmTAUCtrlTbl.ucTauContainDrxFlag)
#define NAS_EMM_TAU_SaveEmmTauContainDrxFlag(DrxFlag)       (NAS_EMM_TAU_GetEmmTauContainDrxFlag() = (DrxFlag))

#define NAS_EMM_TAU_SaveTAUtype(TauType)                    (NAS_EMM_TAU_GetTAUtype() = (TauType))
#define NAS_EMM_TAU_SaveEmmTAUStartCause(SERStartCause)     (NAS_EMM_TAU_GetEmmTAUStartCause() = (SERStartCause))
#define NAS_EMM_TAU_SaveEmmCollisionCtrl(EmmCollisionCtrl)  (NAS_EMM_TAU_GetEmmCollisionCtrl() =  (EmmCollisionCtrl))

#define NAS_EMM_TAU_SaveEmmTAUAttemptCnt(TAUAttemptCnt)     (NAS_EMM_TAU_GetEmmTAUAttemptCnt() = (TAUAttemptCnt))
#define NAS_EMM_TAU_SaveEmmTauReqActiveCtrl(TauReqActiveCtrl) (NAS_EMM_TAU_GetEmmTauReqActiveCtrl() = (TauReqActiveCtrl))
#define NAS_EMM_TAU_SaveEmmTauStartConnSta(TauStartConnSta)   (NAS_EMM_TAU_GetEmmTauStartConnSta() = (TauStartConnSta))
#define NAS_EMM_TAU_SetEmmUplinkPending(UplinkPending)      ((NAS_EMM_TAU_GetEmmUplinkPending()) = (UplinkPending))
#define NAS_EMM_TAU_SetEmmCombinedDetachBlockFlag(enComDetBloFlag) ((NAS_EMM_TAU_GetEmmCombinedDetachBlockFlag()) = enComDetBloFlag)

/*g_stEmmRegStateBarInfo*/
#define NAS_EMM_TAU_GetRegBarInfoAddr()         (&g_stEmmRegStateBarInfo)

#define NAS_EMM_TAU_GetRegBarType()             ((NAS_EMM_TAU_GetRegBarInfoAddr())->ucBitBarType)
#define NAS_EMM_TAU_SetRegBarType(BarType)      (((NAS_EMM_TAU_GetRegBarInfoAddr())->ucBitBarType) = (BarType))

#define NAS_EMM_TAU_GetRegBarProcedure()         ((NAS_EMM_TAU_GetRegBarInfoAddr())->enBarProcedure)
#define NAS_EMM_TAU_SetRegBarProcedure(BarProc)  (((NAS_EMM_TAU_GetRegBarInfoAddr())->enBarProcedure) = (BarProc))


/* TAUģ��ȫ�ֱ��� g_stEmmTAUCtrlTbl�ĺ���� END*/

#define NAS_EMM_TAU_ESM_BEARER_LEFT_N(n)                     ((VOS_UINT8)(EMM_TAU_AD_BIT_SLCT << n))


/* EMM״̬��ز����������õ��ͱ��� */
#define NAS_EMM_TAUSER_GetEmmStat()                            (g_stMmMainContext.stNasMmAuxFsm.ucRrcConnState)

#define NAS_EMM_TAUSER_GetAuxFsmAddr()  (&(g_stMmMainContext.stNasMmAuxFsm))
#define NAS_EMM_TAUSER_GetAuxFsmUpStat()    (g_stMmMainContext.stNasMmAuxFsm.ucEmmUpStat)
#define NAS_EMM_TAUSER_SaveAuxFsmUpStat(updatastaute)    (NAS_EMM_TAUSER_GetAuxFsmUpStat() = (updatastaute) )

#define NAS_EMM_TAU_PTMSI_BIT()                     (g_stEmmInfo.stMmUeId.bitOpPtmsi)
#define NAS_EMM_TAU_GUTI_BIT()                      (g_stEmmInfo.stMmUeId.bitOpGuti)
#define NAS_EMM_TAU_PTMSI_1                         (g_stEmmInfo.stMmUeId.aucPtmsi[0])
#define NAS_EMM_TAU_PTMSI_2                         (g_stEmmInfo.stMmUeId.aucPtmsi[1])
#define NAS_EMM_TAU_PTMSI_3                         (g_stEmmInfo.stMmUeId.aucPtmsi[2])

#define NAS_EMM_TAU_MS_NET_CAP_BIT()                (g_stEmmInfo.bitOpMsNetCap)
#define NAS_EMM_TAU_UE_NET_CAP_BIT()                (g_stEmmInfo.bitOpUeNetCap)
#define NAS_EMM_TAU_DRX_BIT()                       (g_stEmmInfo.bitOpDrx)

#define NAS_EMM_TAU_GetMsIdentityType(stMsId)       ((stMsId).aucMsId[1] & NAS_LMM_LOW_3_BITS_F)


#define NAS_EMM_TAU_REQ_OLD_PTMSI_IEI               0x19
#define NAS_EMM_TAU_REQ_Nonce_UE_IEI                0x55
#define NAS_EMM_TAU_REQ_UE_NET_CAP_IEI              0x58
#define NAS_EMM_TAU_REQ_MS_NET_CAP_IEI              0x31
#define NAS_EMM_TAU_REQ_LAST_REG_TAI_IEI            0x52
#define NAS_EMM_TAU_REQ_EPS_STATUS_IEI              0x57
#define NAS_EMM_TAU_REQ_DRX_PARA_IEI                0x5C
#define NAS_EMM_TAU_REQ_OLD_LA_ID_IEI               0x13
#define NAS_EMM_TAU_REQ_TMSI_STATUS_IEI             0x9
#define NAS_EMM_TAU_REQ_GUTI_TYPE_IEI               0xE0
#define NAS_EMM_TAU_REQ_IE_SPARE                    0xF0
#define NAS_EMM_TAU_REQ_NON_CURRENT_NATIVE_KSI      0xB0
#define NAS_EMM_TAU_REQ_GPRS_CK_SN                  0x80
#define NAS_EMM_TAU_REQ_RADIO_CAP_UPDATE_NEED_IEI   0xA0


/*TAU���������ֵ  5*/
#define NAS_EMM_TAU_ATTEMPT_CNT_MAX                 5

/*TAU����������    0*/
#define NAS_EMM_TAU_ATTEMPT_CNT_ZERO                0


#define NAS_EMM_TAU_LOG_INFO(String)         NAS_LMM_LOG_INFO(LOG_SUBMOD_ID_NAS_LMM_EMM_TAU, String)
#define NAS_EMM_TAU_LOG_NORM(String)         NAS_LMM_LOG_NORM(LOG_SUBMOD_ID_NAS_LMM_EMM_TAU, String)
#define NAS_EMM_TAU_LOG_WARN(String)         NAS_LMM_LOG_WARN(LOG_SUBMOD_ID_NAS_LMM_EMM_TAU, String)
#define NAS_EMM_TAU_LOG_ERR(String)          NAS_LMM_LOG_ERR(LOG_SUBMOD_ID_NAS_LMM_EMM_TAU, String)

#define NAS_EMM_TAU_LOG1_INFO(String, Para1) NAS_LMM_LOG1_INFO(LOG_SUBMOD_ID_NAS_LMM_EMM_TAU, String, Para1)
#define NAS_EMM_TAU_LOG1_NORM(String, Para1) NAS_LMM_LOG1_NORM(LOG_SUBMOD_ID_NAS_LMM_EMM_TAU, String, Para1)
#define NAS_EMM_TAU_LOG1_WARN(String, Para1) NAS_LMM_LOG1_WARN(LOG_SUBMOD_ID_NAS_LMM_EMM_TAU, String, Para1)
#define NAS_EMM_TAU_LOG1_ERR(String,  Para1) NAS_LMM_LOG1_ERR(LOG_SUBMOD_ID_NAS_LMM_EMM_TAU, String,  Para1)

#define NAS_EMM_TAU_LOG2_INFO(String, Para1, Para2)   NAS_LMM_LOG2_INFO(LOG_SUBMOD_ID_NAS_LMM_EMM_TAU, String, Para1, Para2)
#define NAS_EMM_TAU_LOG2_NORM(String, Para1, Para2)   NAS_LMM_LOG2_NORM(LOG_SUBMOD_ID_NAS_LMM_EMM_TAU, String, Para1, Para2)
#define NAS_EMM_TAU_LOG2_WARN(String, Para1, Para2)   NAS_LMM_LOG2_WARN(LOG_SUBMOD_ID_NAS_LMM_EMM_TAU, String, Para1, Para2)
#define NAS_EMM_TAU_LOG2_ERR(String,  Para1, Para2)   NAS_LMM_LOG2_ERR(LOG_SUBMOD_ID_NAS_LMM_EMM_TAU, String,  Para1, Para2)


#define NAS_EMM_SER_LOG_INFO(String)         NAS_LMM_LOG_INFO(LOG_SUBMOD_ID_NAS_LMM_EMM_SERVICE, String)
#define NAS_EMM_SER_LOG_NORM(String)         NAS_LMM_LOG_NORM(LOG_SUBMOD_ID_NAS_LMM_EMM_SERVICE, String)
#define NAS_EMM_SER_LOG_WARN(String)         NAS_LMM_LOG_WARN(LOG_SUBMOD_ID_NAS_LMM_EMM_SERVICE, String)
#define NAS_EMM_SER_LOG_ERR(String)          NAS_LMM_LOG_ERR(LOG_SUBMOD_ID_NAS_LMM_EMM_SERVICE, String)

#define NAS_EMM_SER_LOG1_INFO(String, Para1) NAS_LMM_LOG1_INFO(LOG_SUBMOD_ID_NAS_LMM_EMM_SERVICE, String, Para1)
#define NAS_EMM_SER_LOG1_NORM(String, Para1) NAS_LMM_LOG1_NORM(LOG_SUBMOD_ID_NAS_LMM_EMM_SERVICE, String, Para1)
#define NAS_EMM_SER_LOG1_WARN(String, Para1) NAS_LMM_LOG1_WARN(LOG_SUBMOD_ID_NAS_LMM_EMM_SERVICE, String, Para1)
#define NAS_EMM_SER_LOG1_ERR(String,  Para1) NAS_LMM_LOG1_ERR(LOG_SUBMOD_ID_NAS_LMM_EMM_SERVICE, String,  Para1)

#define NAS_EMM_SER_LOG2_INFO(String, Para1, Para2)   NAS_LMM_LOG2_INFO(LOG_SUBMOD_ID_NAS_LMM_EMM_SERVICE, String, Para1, Para2)
#define NAS_EMM_SER_LOG2_NORM(String, Para1, Para2)   NAS_LMM_LOG2_NORM(LOG_SUBMOD_ID_NAS_LMM_EMM_SERVICE, String, Para1, Para2)
#define NAS_EMM_SER_LOG2_WARN(String, Para1, Para2)   NAS_LMM_LOG2_WARN(LOG_SUBMOD_ID_NAS_LMM_EMM_SERVICE, String, Para1, Para2)
#define NAS_EMM_SER_LOG2_ERR(String,  Para1, Para2)   NAS_LMM_LOG2_ERR(LOG_SUBMOD_ID_NAS_LMM_EMM_SERVICE, String,  Para1, Para2)



#define NAS_EMM_TAU_SEND_MMC_RESULT_IND(pfSendTauRslt,pvPara) \
        {\
            if (NAS_EMM_NULL_PTR != pfSendTauRslt)\
            {\
                (*pfSendTauRslt)(pvPara);\
            }\
        }




/*****************************************************************************
  3 Massage Declare
*****************************************************************************/



/*****************************************************************************
  4 Enum
*****************************************************************************/

/*======================= TAU������ؽṹ =======================*/
enum    NAS_EMM_TAU_TYPE_ENUM
{
    NAS_EMM_TAU_TYPE_TA_UPDATING                        = 0x00,
    NAS_EMM_TAU_TYPE_COMB_TA_LA_UPDATING                = 0x01,
    NAS_EMM_TAU_TYPE_COMB_TA_LA_UPDATE_WITH_IMSI_ATTACH = 0x02,
    NAS_EMM_TAU_TYPE_PERI_UPDATE                        = 0x03,

    NAS_EMM_TAU_TYPE_BUTT
};
typedef VOS_UINT8   NAS_EMM_TAU_TYPE_ENUM_UINT8;

enum    NAS_EMM_TMO_ACTIVE_FLAG_CTRL_ENUM
{
    NAS_EMM_TMO_ACTIVE_FLAG_CTRL_INVALID                 = 0x00,
    NAS_EMM_TMO_ACTIVE_FLAG_CTRL_VALID                   = 0x01,

    NAS_EMM_TMO_ACTIVE_FLAG_CTRL_BUTT
};
typedef VOS_UINT8   NAS_EMM_TMO_ACTIVE_FLAG_CTRL_ENUM_UINT8;

enum    NAS_EMM_PTMSI_ACTIVE_FLAG_CTRL_ENUM
{
    NAS_EMM_PTMSI_ACTIVE_FLAG_CTRL_INVALID                 = 0x00,
    NAS_EMM_PTMSI_ACTIVE_FLAG_CTRL_VALID                   = 0x01,

    NAS_EMM_PTMSI_ACTIVE_FLAG_CTRL_BUTT
};
typedef VOS_UINT8   NAS_EMM_PTMSI_ACTIVE_FLAG_CTRL_ENUM_UINT8;

enum    NAS_EMM_TAU_ACTIVE_FLAG_ENUM
{
    NAS_EMM_TAU_NO_BEARER_EST_REQ                        = 0x00,
    NAS_EMM_TAU_WITH_BEARER_EST_REQ                      = 0x01,

    NAS_EMM_TAU_ACTIVE_BUTT
};
typedef VOS_UINT8   NAS_EMM_TAU_ACTIVE_FLAG_ENUM_UINT8;

enum    NAS_EMM_TAU_RESULT_ENUM
{
    NAS_EMM_TAU_RESULT_SUCC         = 0x00,
    NAS_EMM_TAU_RESULT_REJ          = 0x01,
    NAS_EMM_TAU_RESULT_ABNORMAL     = 0x02,

    NAS_EMM_TAU_RESULT_BUTT
};
typedef VOS_UINT8   NAS_EMM_TAU_RESULT_ENUM_UINT8;

enum    NAS_EMM_COLLISION_ENUM
{
    NAS_EMM_COLLISION_NONE                      = 0,
    NAS_EMM_COLLISION_DETACH                    = 1,
    NAS_EMM_COLLISION_SERVICE                   = 2,

    NAS_EMM_COLLISION_BUTT
};
typedef VOS_UINT8   NAS_EMM_COLLISION_ENUM_UINT8;



enum    NAS_EMM_BAR_PROCEDURE_ENUM
{
    NAS_EMM_BAR_PROCEDURE_NULL                    = 0x00,
    NAS_EMM_BAR_PROCEDURE_TAU                     = 0x01,
    NAS_EMM_BAR_PROCEDURE_SERVICE                 = 0x02,

    NAS_EMM_BAR_PROCEDURE_BUTT
};
typedef VOS_UINT32 NAS_EMM_BAR_PROCEDURE_ENUM_UINT32;


enum NAS_EMM_BAR_TYPE_ENUM
{
    NAS_EMM_BAR_TYPE_MT              = 0,          /* �����Խ���MT */
    NAS_EMM_BAR_TYPE_MO_CALL         = 1,          /* �����Խ���MO Call */
    NAS_EMM_BAR_TYPE_MO_SIGNAL       = 2,          /* �����Խ���MO Signalling */
    NAS_EMM_BAR_TYPE_MO_CALL_AND_MT  = 3,          /* �����Խ���MO Call�� MT */
    NAS_EMM_BAR_TYPE_MO_SIGNAL_AND_MT= 4,          /* �����Խ���MO Signalling �� MT */
    NAS_EMM_BAR_TYPE_MO              = 5,          /* �����Խ���MO Call��MO Signalling */
    NAS_EMM_BAR_TYPE_ALL             = 6,          /* �������Խ��� */
    NAS_EMM_BAR_TYPE_MO_CSFB           = 7,        /* access barred when MO CSFB  */
    NAS_EMM_BAR_TYPE_MO_CALL_AND_CSFB  = 8,
    NAS_EMM_BAR_TYPE_BUTT

};
typedef VOS_UINT32 NAS_EMM_BAR_TYPE_ENUM_UINT32;

enum NAS_EMM_UPLINK_PENDING_ENUM
{
    NAS_EMM_NO_UPLINK_PENDING           = 0,        /* ��������������*/
    NAS_EMM_UPLINK_PENDING              = 1,        /* �����������������������*/

    NAS_EMM_UPLINK_PENDING_BUTT
};
typedef VOS_UINT8 NAS_EMM_UPLINK_PENDING_ENUM_UINT8;

enum NAS_EMM_GUTI_TYPE_ENUM
{
    NAS_EMM_GUTI_TYPE_NATIVE            = 0,
    NAS_EMM_GUTI_TYPE_MAPPED            = 1,

    NAS_EMM_GUTI_TYPE_BUTT
};
typedef VOS_UINT8 NAS_EMM_GUTI_TYPE_ENUM_UINT8;


enum NAS_EMM_URC_UPDATE_ENUM
{
    NAS_EMM_URC_UPDATE_NOT_NEED         = 0,
    NAS_EMM_URC_UPDATE_NEED             = 1,

    NAS_EMM_URC_UPDATE_BUTT
};
typedef VOS_UINT8 NAS_EMM_URC_UPDATE_ENUM_UINT8;

/*****************************************************************************
 ö����    : NAS_EMM_CN_TAU_TYPE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : UE������TAU����(CN��Ϣ������)
*****************************************************************************/
enum NAS_EMM_CN_TAU_TYPE_ENUM
{
    NAS_EMM_CN_TAU_TYPE_TA_UPDATING                     = 0,
    NAS_EMM_CN_TAU_TYPE_COMBINED_TA_LA_UPDATING         = 1,
    NAS_EMM_CN_TAU_TYPE_COMBINED_TA_LA_WITH_IMSI        = 2,
    NAS_EMM_CN_TAU_TYPE_PERIODIC_UPDATING              = 3,
    NAS_EMM_CN_TAU_TYPE_BUTT
};
typedef VOS_UINT32 NAS_EMM_CN_TAU_TYPE_ENUM_UINT32;



/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/*****************************************************************************
�ṹ����    :NAS_LMM_OM_LOG_ACTIVE_FLAG_INFO_STRU
ʹ��˵��    :����ָʾ��ʲôԭ�򴥷���TAU REQ��Ϣ��Я��ACTIVE��ʶ
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                 stMsgHeader;     /*_H2ASN_Skip*/
    NAS_EMM_COLLISION_ENUM_UINT8                    enEmmCollisionCtrl;
    VOS_UINT8                                       ucEsmEmcPdnReq;
    VOS_UINT8                                       ucCsAttachAllowFlag;
    NAS_EMM_TMO_ACTIVE_FLAG_CTRL_ENUM_UINT8         enTmoActiveFlag;
    VOS_UINT8                                       ucImsProcedureOngoing;
    VOS_UINT8                                       ucDataPendingFlag;
    VOS_UINT8                                       ucUpSignalPendingFlag;
    NAS_EMM_PTMSI_ACTIVE_FLAG_CTRL_ENUM_UINT8       enPtmsiActiveFlag;
}NAS_LMM_OM_LOG_ACTIVE_FLAG_INFO_STRU;

/*======================= TAU���ƽṹ =======================*/
typedef struct
{
    VOS_UINT32                              bitOpLai        : 1;
    VOS_UINT32                              bitOpMsId       : 1;
    VOS_UINT32                              bitOpCnCause    : 1;
    VOS_UINT32                              bitOpExtCause   : 1;
    VOS_UINT32                              bitOpRsv        : 28;

    NAS_EMM_CN_TAU_TYPE_ENUM_UINT32         enEmmTauType;           /*TAU����*/
    NAS_EMM_TAU_START_CAUSE_ENUM_UINT8      enEmmTAUStartCause;     /*TAU����ԭ��*/
    NAS_EMM_COLLISION_ENUM_UINT8            enEmmCollisionCtrl;     /*TAU��ͻ����*/
    VOS_UINT8                               ucTauContainDrxFlag;

    NAS_EMM_TMO_ACTIVE_FLAG_CTRL_ENUM_UINT8 enTmoActiveFlagCtrl;   /* TMO����������Ч��ʶ */

    VOS_UINT8                               ucTAUAttemptCnt;        /*TAU������*/
    NAS_EMM_RRC_CONN_STATE_ENUM_UINT8       ucTauStartConnSta;      /*TAU����ʱ������״̬*/
    NAS_EMM_TAU_ACTIVE_FLAG_ENUM_UINT8      enEmmTauReqActiveCtrl;
    NAS_EMM_UPLINK_PENDING_ENUM_UINT8       enUplinkPending;        /*����������־*/
    NAS_EMM_COM_DET_BLO_FLAG_ENUM_UINT32    enCombinedDetachBlockFlag;  /* ��¼TAU�Ƿ���������DETACH������IMSI DETACH��EPS/IMSI DETACH */
    NAS_EMM_LA_STRU                         stLai;
    NAS_EMM_MSID_STRU                       stMsId;
    NAS_EMM_CN_CAUSE_ENUM_UINT8             enCnCause;
    NAS_EMM_EPS_UPDATE_RST_ENUM_UINT8       ucEpsUpdataRst;
    NAS_EMM_CN_CAUSE_ENUM_UINT8             enTauEmmCause;
    NAS_EMM_IMSI_DETACH_FLAG_ENUM_UINT8     enImsiCnDetachFlag;
    NAS_EMM_TAU_COMPLETE_FLAG_ENUM_UINT8     enTauCompleteFlag;
    EMMC_EMM_FORBIDDEN_INFO_ENUM_UINT32     ulForbInfo;
    NAS_LMM_REG_DOMAIN_ENUM_UINT32          ulPeriodTauRegDomain;
    VOS_UINT8                               ucTauRejEmmExtCause;

    NAS_EMM_PTMSI_ACTIVE_FLAG_CTRL_ENUM_UINT8 enPtmsiActiveFlagCtrl;   /* P-TMSIҪ��active flag����������Ч��ʶ */
    VOS_UINT8                               aucRsv[2];


}EMM_TAU_CTRL_STRU;
typedef struct
{
    NAS_EMM_BAR_PROCEDURE_ENUM_UINT32   enBarProcedure;
    VOS_UINT8                           ucBitBarType;/*һ��bit��Ӧһ�ֱ�bar����
                                                   ��һ��bit:��ʾMO-SIGNAL bar
                                                   �ڶ���bit:��ʾMO-CALL bar
                                                   ������bit:��ʾMT-CALL bar
                                                   ���ĸ�bit:��ʾMO CSFB bar*/
    VOS_UINT8                           aucRsv[3];
}NAS_EMM_BAR_STRU;

/* ��bar������ṹ */
typedef struct
{
    LRRC_LNAS_ACCESS_GRANT_ENUM_UINT32  enGrantType;       /* ��bar���� */
    VOS_UINT8                           ucGrantValue;      /* ��barʱ��Ҫ���¼�¼bar���͵�ֵ */
}NAS_EMM_GRANT_ACT_STRU;


/*****************************************************************************
�ṹ����    :NAS_LMM_TAU_COLLISION_SER_RCV_CN_REJ_PROC_STRU
ʹ��˵��    :TAU���SER��ͻʱ�յ�����REJ��ͬԭ��ֵ������ָ��ͽṹ
*****************************************************************************/
typedef VOS_VOID (*NAS_LMM_TAU_COLLISION_SER_RCV_CN_REJ_PROC_FUN)(
    NAS_EMM_CN_CAUSE_ENUM_UINT8         enRejCauseVal
);

typedef struct
{
    NAS_EMM_CN_CAUSE_ENUM_UINT8                             enRejCauseVal;     /* �ܾ�ԭ��ֵ */
    NAS_LMM_TAU_COLLISION_SER_RCV_CN_REJ_PROC_FUN           pfProcFun;         /* �ܾ�ԭ��ֵ�Ĵ����� */
}NAS_LMM_TAU_COLLISION_SER_RCV_CN_REJ_PROC_STRU;

/*****************************************************************************
�ṹ����    :NAS_LMM_TAU_COLLISION_DETACH_RCV_CN_REJ_PROC_STRU
ʹ��˵��    :TAU���DETACH��ͻʱ�յ�����REJ��ͬԭ��ֵ������ָ��ͽṹ
*****************************************************************************/
typedef VOS_VOID (*NAS_LMM_TAU_COLLISION_DETACH_RCV_CN_REJ_PROC_FUN)(
    NAS_EMM_CN_CAUSE_ENUM_UINT8         enRejCauseVal
);

typedef struct
{
    NAS_EMM_CN_CAUSE_ENUM_UINT8                             enRejCauseVal;     /* �ܾ�ԭ��ֵ */
    NAS_LMM_TAU_COLLISION_DETACH_RCV_CN_REJ_PROC_FUN        pfProcFun;         /* �ܾ�ԭ��ֵ�Ĵ����� */
}NAS_LMM_TAU_COLLISION_DETACH_RCV_CN_REJ_PROC_STRU;



/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/

extern EMM_TAU_CTRL_STRU                g_stEmmTAUCtrlTbl;
extern  NAS_EMM_BAR_STRU                g_stEmmRegStateBarInfo;


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern VOS_VOID NAS_EMM_TauRstLeadSndAttachRst(MMC_LMM_ATTACH_RSLT_ENUM_UINT32 ulAttRst);
extern VOS_VOID   NAS_EMM_TAU_RcvT3440Exp(VOS_VOID);
extern VOS_VOID   NAS_EMM_TAU_RcvT3430Exp(VOS_VOID);

extern VOS_VOID   NAS_EMM_TAU_ProcEnterForbTA
(
    EMMC_EMM_FORBIDDEN_INFO_ENUM_UINT32 ulForbInfo
);
extern VOS_VOID  NAS_EMM_TAU_ProcCause161722TauAttemptCont(VOS_VOID );
extern VOS_VOID  NAS_EMM_TAU_ProcCause22TauAttemptContR11(VOS_VOID );

extern VOS_VOID  NAS_EMM_TAU_RelIndCollisionProc
(
    NAS_LMM_SEND_TAU_RESULT_ACT_FUN  pfTauRslt,
    const VOS_VOID  *pvPara
);


extern VOS_VOID   NAS_EMM_TAU_RcvRrcRelInd(VOS_VOID);
extern VOS_VOID   NAS_EMM_TAU_TauAcpCollisionProc(VOS_VOID);
extern VOS_VOID NAS_EMM_TAU_TauAcpTaOnlyCollisionProc
(
    VOS_VOID                           *pMsgStru
);
extern VOS_VOID   NAS_EMM_TAU_RcvTAUAcp(VOS_VOID *pMsgStru);


extern VOS_VOID   NAS_EMM_TAUSER_FSMTranState(
                                    NAS_EMM_MAIN_STATE_ENUM_UINT16  stMS,
                                    NAS_EMM_SUB_STATE_ENUM_UINT16   stSS,
                                    NAS_EMM_STATE_TI_ENUM_UINT16    stTI);
extern VOS_VOID    NAS_EMM_TauUpdateGutiFromCnMsg(
                                    const NAS_EMM_CN_TAU_ACP_STRU     *pstTAUAcp);

extern VOS_VOID   NAS_EMM_TAUSER_TaiListSet( const NAS_EMM_TA_LIST_STRU *pstTALIST);
extern NasMmIntraMsgBlock *    NAS_EMM_TAUSER_GetSendIntraMsgBuffAddr(VOS_UINT32 ulBuffSize);
extern VOS_VOID   NAS_EMM_TAU_AbnormalOver( VOS_VOID);
extern NAS_EMM_UPDATE_STATE_ENUM_UINT8 NAS_EMM_TAU_GetEmmEPSUPState(VOS_VOID);
extern VOS_VOID   NAS_EMM_TAU_SendEsmStatusInd( EMM_ESM_ATTACH_STATUS_ENUM_UINT32  stATTACHStatus);
extern VOS_VOID   NAS_EMM_TAU_SendMrrcDataReq_TAUReq( NAS_EMM_MSG_TYPE_ENUM_UINT32 ulEmmMsgType);
extern VOS_VOID   NAS_EMM_TAU_SendEsmBearerStatusInd(const NAS_EMM_CN_TAU_ACP_STRU   *pMsgStru);
extern VOS_VOID   NAS_EMM_TAU_SendDetachReq(VOS_VOID);
extern VOS_VOID   NAS_EMM_TAU_CompCnTAUCmpl(LRRC_LNAS_MSG_STRU  *pNasMsg,VOS_UINT32 *pulIndex);
extern VOS_VOID   NAS_EMM_TAU_SendMrrcDataReqTauCmpl( VOS_VOID);
extern VOS_UINT32 NAS_EMM_TAU_CHKFSMStateMsgp(
                                    NAS_EMM_MAIN_STATE_ENUM_UINT16  stMS,
                                    NAS_EMM_SUB_STATE_ENUM_UINT16   stSS,
                                    VOS_VOID   *pMsgStru);

extern VOS_VOID NAS_EMM_TAU_TAUReqRejectCasue367
(
    NAS_EMM_CN_CAUSE_ENUM_UINT8   ucTAUrejcause,
    NAS_EMM_CN_TAU_REJ_STRU      *pstTAURej
);

extern VOS_VOID NAS_EMM_TAU_TAUReqRejectCasue8
(
    NAS_EMM_CN_CAUSE_ENUM_UINT8   ucTAUrejcause,
    NAS_EMM_CN_TAU_REJ_STRU      *pstTAURej

);
extern VOS_VOID   NAS_EMM_TAU_TAUReqRejectCasue9
(
    NAS_EMM_CN_CAUSE_ENUM_UINT8   ucTAUrejcause,
    NAS_EMM_CN_TAU_REJ_STRU      *pstTAURej

);
extern VOS_VOID   NAS_EMM_TAU_TAUReqRejectCasue10
(
    NAS_EMM_CN_CAUSE_ENUM_UINT8   ucTAUrejcause,
    NAS_EMM_CN_TAU_REJ_STRU      *pstTAURej

);
extern VOS_VOID   NAS_EMM_TAU_TAUReqRejectCasue11
(
    NAS_EMM_CN_CAUSE_ENUM_UINT8   ucTAUrejcause,
    NAS_EMM_CN_TAU_REJ_STRU      *pstTAURej

);
extern VOS_VOID   NAS_EMM_TAU_TAUReqRejectCasue12
(
    NAS_EMM_CN_CAUSE_ENUM_UINT8   ucTAUrejcause,
    NAS_EMM_CN_TAU_REJ_STRU      *pstTAURej

);
extern VOS_VOID   NAS_EMM_TAU_TAUReqRejectCasue13
(
    NAS_EMM_CN_CAUSE_ENUM_UINT8   ucTAUrejcause,
    NAS_EMM_CN_TAU_REJ_STRU      *pstTAURej

);
extern VOS_VOID   NAS_EMM_TAU_TAUReqRejectCasue14
(
    NAS_EMM_CN_CAUSE_ENUM_UINT8   ucTAUrejcause,
    NAS_EMM_CN_TAU_REJ_STRU      *pstTAURej

);
extern VOS_VOID   NAS_EMM_TAU_TAUReqRejectCasue15
(
    NAS_EMM_CN_CAUSE_ENUM_UINT8   ucTAUrejcause,
    NAS_EMM_CN_TAU_REJ_STRU      *pstTAURej

);
extern VOS_VOID   NAS_EMM_TAU_TAUReqRejectCasue22
(
    NAS_EMM_CN_CAUSE_ENUM_UINT8   ucTAUrejcause,
    NAS_EMM_CN_TAU_REJ_STRU      *pstTAURej

);

/* lihong00150010 emergency tau&service begin */
/*extern VOS_VOID   NAS_EMM_TAU_TAUReqRejectCasue25();*/
/* lihong00150010 emergency tau&service end */
extern VOS_VOID   NAS_EMM_TAU_TAUReqRejectCasue40
(
    NAS_EMM_CN_CAUSE_ENUM_UINT8   ucTAUrejcause,
    NAS_EMM_CN_TAU_REJ_STRU      *pstTAURej

);
extern VOS_VOID NAS_EMM_TAU_TAUReqRejectCasue35
(
    NAS_EMM_CN_CAUSE_ENUM_UINT8   ucTAUrejcause,
    NAS_EMM_CN_TAU_REJ_STRU      *pstTAURej

);

extern VOS_VOID NAS_EMM_TAU_TAUReqRejectCasue42Release11
(
    NAS_EMM_CN_CAUSE_ENUM_UINT8         ucTAUrejcause,
    NAS_EMM_CN_TAU_REJ_STRU            *pstTAURej
);

extern VOS_VOID NAS_EMM_TAU_TAUReqRejectCasue42
(
    NAS_EMM_CN_CAUSE_ENUM_UINT8   ucTAUrejcause,
    NAS_EMM_CN_TAU_REJ_STRU      *pstTAURej

);

extern VOS_VOID   NAS_EMM_TAU_TAUReqRejectOtherCause
(
    NAS_EMM_CN_CAUSE_ENUM_UINT8   ucTAUrejcause,
    NAS_EMM_CN_TAU_REJ_STRU      *pstTAURej

);
extern VOS_VOID    NAS_EMM_TAU_RcvTAURej
(
    const NAS_EMM_CN_CAUSE_ENUM_UINT8   ucTAUrejcause,
    NAS_EMM_CN_TAU_REJ_STRU            *pstTAURej
);
/* �������TAU����ԭ�� */
extern VOS_VOID   NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_ENUM_UINT32 enTauStartType);

extern VOS_UINT32 NAS_EMM_TAU_IsCurrentTAInTaList(VOS_VOID);

extern VOS_VOID   NAS_EMM_TAU_RrcRelCause_T3440Exp(VOS_VOID);
extern VOS_VOID    NAS_EMM_TAU_ProcTaUpdatedOnlyNoCause(VOS_VOID *pstRcvMsg  );
extern VOS_VOID    NAS_EMM_TAU_ProcTaUpdatedOnlySucc
(
    VOS_VOID                *pstRcvMsg
);
extern VOS_VOID NAS_EMM_TAU_ProcTauAcpCauseVal18
(
    VOS_VOID                           *pstRcvMsg
);
extern VOS_VOID NAS_EMM_TAU_ProcTauAcpCauseVal2
(
    VOS_VOID                           *pstRcvMsg
);
extern VOS_VOID NAS_EMM_TAU_ProcTauAcpCauseVal1617
(
    VOS_VOID                           *pstRcvMsg
);
extern VOS_VOID NAS_EMM_TAU_ProcTauAcpCauseVal22
(
    VOS_VOID                           *pstRcvMsg
);

extern VOS_VOID  NAS_EMM_MmcSendTauActionResultIndSucc(VOS_VOID);

extern VOS_VOID    NAS_EMM_TAU_ProcTaUpdatedOnlyWithCause
(
    VOS_VOID                *pstRcvMsg
);
extern VOS_VOID  NAS_EMM_TAU_SaveTauAcpIe
(
    VOS_VOID                           *pMsgStru
);
extern VOS_VOID  NAS_EMM_TAU_TauSuccProc
(
    VOS_VOID                           *pMsgStru
);

extern VOS_UINT32  NAS_EMM_TAU_IsCombinedTauTaUpdatedOnly
(
    MMC_LMM_TAU_TYPE_ENUM_UINT32            enEmmTauType,
    NAS_EMM_EPS_UPDATE_RST_ENUM_UINT8       enEpsUpdateRslt
);


/* �ĵ� TAUINTERFACE.H������ extern VOS_VOID   NAS_EMM_TAU_IsUplinkPending( VOS_VOID );*/
extern VOS_VOID   NAS_EMM_RegSomeStateMsgSysInfoCommProc( VOS_VOID );
extern VOS_VOID NAS_EMM_RegStateMmcOriResumeSysInfoWithTmsiProc(VOS_VOID);


extern VOS_VOID  NAS_EMM_RegStateMmcOriResumeSysInfoNeednotWaitTimerExpProc( VOS_VOID );
extern VOS_UINT32  NAS_EMM_RegStateMmcOriResumeSysInfoRecogniseWaitTimerExp( VOS_VOID );
/*add for test
 */
/* �������,�����ж�С����Ϣ�Ƿ����ı� */
extern VOS_VOID  NAS_EMM_RegNormalServiceOrUpdateMMMsgSysInfoCommProc( EMMC_EMM_CHANGE_INFO_ENUM_UINT32    ulChangeInfo);

/* �������,�����ж�С����Ϣ�Ƿ����ı� */
extern VOS_VOID NAS_EMM_MsRegSsNormalCsfbDelayProc(EMMC_EMM_CHANGE_INFO_ENUM_UINT32    ulChangeInfo);

extern VOS_VOID NAS_EMM_DetachToTAU(VOS_VOID);
extern VOS_VOID NAS_EMM_MsTauInitSsWaitCNCnfProcMsgRrcRelInd( VOS_UINT32 ulCause );

extern VOS_VOID  NAS_EMM_MmcSendTauActionResultIndSucc(VOS_VOID);


extern VOS_VOID  NAS_EMM_MmcSendTauActionResultIndRejTaUpdatedOnly
(
    const VOS_VOID  *pvTauRslt
);
extern VOS_VOID  NAS_EMM_MmcSendTauActionResultIndSuccWithoutPara(VOS_VOID);

extern VOS_VOID  NAS_EMM_MmcSendTauActionResultIndForbType
(
    const VOS_VOID  *pvForbInfo
);

extern VOS_VOID  NAS_EMM_MmcSendTauActionResultIndRej
(
    const VOS_VOID  *pvTauRslt
);
extern VOS_VOID  NAS_EMM_MmcSendTauActionResultIndTimerExp
(
    const VOS_VOID *pvTauRslt
);
extern NAS_EMM_CN_TAU_TYPE_ENUM_UINT32 NAS_EMM_TAU_GetEpsUpdateType
(
    NAS_EMM_TAU_START_CAUSE_ENUM_UINT8      enTauStartCause
);
extern VOS_VOID* NAS_EMM_TauRsltCommProc( VOS_VOID );

extern VOS_VOID  NAS_EMM_MmcSendTauActionResultIndFailWithPara
(
    const VOS_VOID  *pvTauRslt
);

extern VOS_VOID    NAS_EMM_TAU_CompCnTAUReqNasMsg
(
    VOS_UINT8      *pucCnNasMsg,
    VOS_UINT32     *pulIndex
);
extern VOS_VOID  NAS_EMM_EncodeOldGuti
(
    VOS_UINT8       *pMsg,
    VOS_UINT32      *pulIeLength
);

extern VOS_VOID  NAS_EMM_EncodeNonCurrentNativeKSI
(
    VOS_UINT8       *pMsg,
    VOS_UINT32      *pulIeLength
);

extern VOS_VOID  NAS_EMM_EncodeGprsCkSn
(
    VOS_UINT8       *pMsg,
    VOS_UINT32      *pulIeLength
);
extern VOS_VOID  NAS_EMM_EncodeNonceUE
(
    VOS_UINT8       *pMsg,
    VOS_UINT32      *pulIeLength
);

extern VOS_VOID  NAS_EMM_EncodeURCUpdateNeed
(
    VOS_UINT8       *pMsg,
    VOS_UINT32      *pulIeLength
);

extern VOS_VOID  NAS_EMM_EncodeGutiType
(
    VOS_UINT8 *pMsg,
    VOS_UINT32      *pulIeLength
);
/*leili modify for isr begin*/
extern VOS_VOID  NAS_EMM_EncodeEpsBearStatus
(
    VOS_UINT8       *pMsg,
    VOS_UINT32      *pulIeLength
);
/*leili modify for isr end*/
extern VOS_UINT32  NAS_EMM_IsConnChangeToLte( VOS_VOID );
extern VOS_UINT32  NAS_EMM_RegSomeStateMsgSysInfoT3412ExpProc( VOS_VOID );


extern VOS_UINT32  NAS_EMM_MsRegSsLimitedSrvMsgRrcRelInd
(
    VOS_UINT32  ulMsgId,
    VOS_VOID   *pMsgStru
);

extern VOS_UINT32  NAS_EMM_AnyStateMsgMrrcRelInd
(
    VOS_UINT32  ulMsgId,
   const VOS_VOID   *pMsgStru
);
/*leili modify for isr begin*/
extern VOS_UINT32  NAS_EMM_GetUeSuppISR(VOS_VOID );

extern VOS_VOID  NAS_EMM_TAU_SetISRAct
(
    NAS_EMM_EPS_UPDATE_RST_ENUM_UINT8   enEPSupdataRst
);
extern VOS_UINT32  NAS_EMM_IsPtmsiAndIdle( VOS_VOID );
/*leili modify for isr end*/
extern VOS_UINT32  NAS_EMM_TAU_RrcRelCauseTriggerTau(VOS_VOID);
extern VOS_UINT32 NAS_EMM_SndTauCompleteFailProc(VOS_VOID* pMsg,VOS_UINT32 *pulIsDelBuff);
extern VOS_UINT32 NAS_EMM_SndTauReqFailProc(VOS_VOID* pMsg,VOS_UINT32 *pulIsDelBuff);

extern VOS_UINT32 NAS_EMM_SndTauCmpSuccProc(VOS_VOID* pMsg);

extern VOS_VOID  NAS_EMM_TAU_ProcAbnormal(VOS_VOID);

extern VOS_UINT32  NAS_EMM_RegSomeStateStartTAUNeeded( VOS_VOID );

/*extern VOS_UINT32  NAS_EMM_SomeStateRcvUtranModChgCommProc(VOS_VOID);*/
extern VOS_UINT32  NAS_LMM_PreProcMmcUtranModeReq( MsgBlock  *pMsg );
extern VOS_UINT32  NAS_LMM_SendRrcUtranModeReq
(
    LRRC_LNAS_UTRAN_MODE_ENUM_UINT8       enUtranMode
);
extern VOS_UINT32  NAS_LMM_PreProcRrcUtranModeCnf( MsgBlock  *pMsg );
extern VOS_VOID NAS_EMM_TauRstLeadSndAttachRst(MMC_LMM_ATTACH_RSLT_ENUM_UINT32 ulAttRst);

extern VOS_UINT32 NAS_EMM_IsAnnexP5AConditionSatisfied(VOS_VOID);
extern VOS_UINT32 NAS_EMM_IsAnnexP5BConditionSatisfied(VOS_VOID);
extern VOS_UINT32  NAS_EMM_IsAnnexP5ConditionSatisfied(VOS_VOID);

extern VOS_UINT32 NAS_EMM_IsIntraHoIgnoreForbSysInfo(VOS_VOID);
extern  VOS_VOID  NAS_EMM_TAU_SendRrcDsdsBeginNotify(VOS_VOID);
extern  VOS_VOID  NAS_EMM_TAU_SendRrcDsdsEndNotify(VOS_VOID);

#if (VOS_WIN32 != VOS_OS_VER)
extern  VOS_UINT32  NAS_EMM_CheckEnterRegNormal(VOS_VOID);
#endif



extern VOS_VOID  NAS_EMM_TAU_ClearActiveFlagProc(VOS_VOID);

extern VOS_UINT8  NAS_EMM_IsPtmsiTauActiveFlagSatified(VOS_VOID);

extern NAS_EMM_COLLISION_ENUM_UINT8 NAS_EMM_TAU_RcvTauRejCollisionProc
(
    NAS_EMM_CN_CAUSE_ENUM_UINT8         enTauRejcause
);
extern VOS_VOID  NAS_EMM_TAU_CollisionServiceRcvCnRejProc
(
    NAS_EMM_CN_CAUSE_ENUM_UINT8         enTauRejcause
);
extern VOS_VOID NAS_EMM_TAU_TAUCollisionSerRejCasue3
(
    NAS_EMM_CN_CAUSE_ENUM_UINT8         enTauRejcause
);
extern VOS_VOID NAS_EMM_TAU_TAUCollisionSerRejCasue7
(
    NAS_EMM_CN_CAUSE_ENUM_UINT8         enTauRejcause
);
extern VOS_VOID NAS_EMM_TAU_TAUCollisionSerRejCasueOther
(
    NAS_EMM_CN_CAUSE_ENUM_UINT8         enTauRejcause
);
extern VOS_VOID  NAS_EMM_TAU_CollisionDetachRcvCnRejProc
(
    NAS_EMM_CN_CAUSE_ENUM_UINT8         enTauRejcause
);
extern VOS_VOID NAS_EMM_TAU_TAUCollisionDetachRejCasue3
(
    NAS_EMM_CN_CAUSE_ENUM_UINT8         enTauRejcause
);
extern VOS_VOID NAS_EMM_TAU_TAUCollisionDetachRejCasue9
(
    NAS_EMM_CN_CAUSE_ENUM_UINT8         enTauRejcause
);
extern VOS_VOID NAS_EMM_TAU_TAUCollisionDetachRejCasue13
(
    NAS_EMM_CN_CAUSE_ENUM_UINT8         enTauRejcause
);
extern VOS_VOID NAS_EMM_TAU_TAUCollisionDetachRejCasue22
(
    NAS_EMM_CN_CAUSE_ENUM_UINT8         enTauRejcause
);
extern VOS_VOID NAS_EMM_TAU_TAUCollisionDetachRejCasueOther
(
    NAS_EMM_CN_CAUSE_ENUM_UINT8         enTauRejcause
);

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

#endif /* end of MapsTemplate.h*/


