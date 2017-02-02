
#ifndef _NAS_MMC_SND_LMM_H
#define _NAS_MMC_SND_LMM_H_

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include  "vos.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "MmcLmmInterface.h"
#endif
#include  "MmcGmmInterface.h"
#include "MsccMmcInterface.h"
#include  "NasCommDef.h"
#include  "NasMmcCtx.h"

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

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
#if (FEATURE_ON == FEATURE_LTE)
VOS_VOID NAS_MMC_SndLmmStopReq( VOS_VOID );

VOS_VOID NAS_MMC_SndLmmPlmnAnyCellSrchReq(VOS_VOID);

VOS_VOID NAS_MMC_SndLmmPlmnListReq(VOS_VOID);

VOS_VOID NAS_MMC_SndLmmUsimStatusReq(
    MMC_LMM_USIM_STATUS_ENUM_UINT32     enUsimState
);

VOS_VOID NAS_MMC_SndLmmSuspendReq(VOS_VOID);

VOS_VOID NAS_MMC_SndLmmPlmnSrchStopReq(VOS_VOID);

VOS_VOID NAS_MMC_SndLmmStartReq(VOS_VOID);

VOS_VOID NAS_MMC_SndLmmEquPlmnReq(
    NAS_MML_EQUPLMN_INFO_STRU          *pstEquPlmnInfo
);

VOS_VOID NAS_MMC_BuildSndLmmEquPlmnInfo(
     NAS_MML_EQUPLMN_INFO_STRU          *pstEquPlmnInfo
);

VOS_VOID NAS_MMC_SndLmmMtDetachIndActionResultReq(
    NAS_MMC_GMM_NT_DETACH_ENUM_U32      enMtType,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCnCause
);

VOS_VOID NAS_MMC_SndLmmLocalDetachIndActionResultReq(
    MMC_LMM_GU_LOCAL_DETACH_TYPE_ENUM_UINT32                ulLocalDetachType
);

VOS_VOID NAS_MMC_SndLmmMoDetachIndActionResultReq(
    MMC_LMM_MO_DETACH_TYPE_ENUM_UINT32  ulMoDetachType
);


VOS_VOID NAS_MMC_SndLmmRegActionResultReq(
    NAS_MMC_GU_ACTION_RSLT_INFO_STRU   *pstGuActionRslt
);

VOS_VOID NAS_MMC_SndLmmRelReq( VOS_VOID );

VOS_VOID NAS_MMC_SndLmmAttachReq(
    VOS_UINT32                                              ulOpId,
    VOS_UINT32                                              ulAttachType,
    NAS_MSCC_PIF_EPS_ATTACH_REASON_ENUM_UINT32                   enEpsAttachReason
);

VOS_VOID NAS_MMC_SndLmmDetachReq(
    VOS_UINT32                          ulOpId,
    VOS_UINT32                          ulDetachType,
    NAS_MSCC_PIF_DETACH_REASON_ENUM_UINT32   enDetachReason
);


VOS_VOID NAS_MMC_SndLmmResumeNotify( VOS_VOID );

VOS_VOID NAS_MMC_SndLmmSuspendRsp(
    VOS_UINT32                          ulRst
);

VOS_UINT32  NAS_MMC_FormatProcTypeToLmm(
    NAS_MML_PROC_TYPE_ENUM_U32          enProcType,
    MMC_LMM_ACTION_TYPE_ENUM_UINT32    *penActionType
);

VOS_UINT32  NAS_MMC_ConvertAttachTypeToLmm(
    VOS_UINT32                          ulAttachType,
    MMC_LMM_ATT_REQ_TYPE_ENUM_UINT32   *penLmmAttachType
);


VOS_VOID  NAS_MMC_ConvertLmmPlmnToGUNasFormat(
    MMC_LMM_PLMN_ID_STRU               *pstLMMPlmn,
    NAS_MML_PLMN_ID_STRU               *pstGUNasPlmn
);

VOS_VOID NAS_MMC_ConvertLmmPlmnToGUNasPlmn(
    VOS_UINT32                          ulLmmPlmnNum,
    MMC_LMM_PLMN_ID_STRU               *pstLmmPlmn,
    NAS_MML_PLMN_ID_STRU               *pstGUNasPlmn
);

VOS_UINT32  NAS_MMC_ConvertDetachTypeToLmm(
    VOS_UINT32                          ulDetachType,
    MMC_LMM_MO_DETACH_TYPE_ENUM_UINT32 *penLmmDetachType
);

VOS_VOID  NAS_MMC_SndLmmSyscfgReq(
    MSCC_MMC_SYS_CFG_SET_REQ_STRU        *pstSysCfgMsg
);

VOS_VOID  NAS_MMC_SndLmmDisableLteNotify(
    MMC_LMM_DISABLE_LTE_REASON_ENUM_UINT32                  enDisableLteReason
);

VOS_VOID  NAS_MMC_SndLmmEnableLteNotify(VOS_VOID);

VOS_VOID NAS_MMC_SndLmmCsConnStatusNotify(
    VOS_UINT8                           ucCsRrConnStatusFlg,
    VOS_UINT8                           ucCsEmergencyConnStatusFlg
);


VOS_VOID NAS_MMC_FillGprsRegInfoInLmmActionRslt(
    MMC_LMM_ACTION_RESULT_REQ_STRU                         *pstMsg
);

VOS_VOID NAS_MMC_FillCsRegInfoInLmmActionRslt(
    MMC_LMM_ACTION_RESULT_REQ_STRU                         *pstMsg
);

VOS_VOID NAS_MMC_BuildLmmSpecPlmnSearchReqMsg(
    MMC_LMM_PLMN_SRCH_REQ_STRU         *pstMsg,
    NAS_MML_PLMN_LIST_WITH_RAT_STRU    *pstDestPlmnList,
    VOS_UINT32                          ulUserSpecFlag
);

VOS_VOID NAS_MMC_SndLmmSpecPlmnSearchReq(
    NAS_MML_PLMN_LIST_WITH_RAT_STRU    *pstDestPlmnList,
    VOS_UINT32                          ulUserSpecFlag
);

VOS_VOID NAS_MMC_BuildLmmHistoryPlmnSearchReqMsg(
    MMC_LMM_PLMN_SRCH_REQ_STRU         *pstMsg,
    NAS_MML_PLMN_LIST_WITH_RAT_STRU    *pstDestPlmnList
);
VOS_VOID NAS_MMC_SndLmmHistoryPlmnSearchReq(
    NAS_MML_PLMN_LIST_WITH_RAT_STRU    *pstDestPlmnList
);

VOS_VOID NAS_MMC_SndLmmNcellSpecPlmnSearchReq(
    NAS_MMC_LTE_NCELL_INFO_STRU        *pstLteNcellInfo,
    NAS_MML_EQUPLMN_INFO_STRU          *pstOtherModemEplmnInfo
);

VOS_VOID NAS_MMC_BuildLmmStartReqMsg(
    MMC_LMM_START_REQ_STRU             *pstLmmStartReqStru,
    MMC_LMM_USIM_STATUS_ENUM_UINT32     ulSimStatus,
    VOS_UINT32                         *pulRat
);

VOS_VOID NAS_MMC_BuildMmcLmmDetachIndActionResultReqMsg(
    NAS_MMC_GMM_NT_DETACH_ENUM_U32      enMtType,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCnCause,
    MMC_LMM_ACTION_RESULT_REQ_STRU     *pstMsg
);




VOS_VOID NAS_MMC_BuildMmcLmmPlmnSrchReqMsg(
    MMC_LMM_PLMN_SRCH_TYPE_ENUM_UINT32  enSrchType,
    NAS_MML_PLMN_ID_STRU               *pstPlmnId,
    MMC_LMM_PLMN_SRCH_REQ_STRU         *pstMsg
);

VOS_UINT32  NAS_MMC_ConvertMmCauseToEmmCause(
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCnCause,
    NAS_LMM_CN_CAUSE_ENUM_UINT8        *penCnRejCause
);

VOS_UINT32 NAS_MMC_ConverCnDomainToLmm(
    NAS_MMC_REG_DOMAIN_ENUM_UINT8      enCnDoamin,
    MMC_LMM_DOMAIN_ENUM_UINT32         *penLmmDomain
);


VOS_VOID NAS_MMC_ConvertGuRsltToLmmFormat(
    NAS_MML_REG_RESULT_ENUM_UINT8       enGuRegRslt,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enGuCnCause,
    MMC_LMM_RSLT_TYPE_ENUM_UINT32      *penLmmActRslt
);

VOS_VOID NAS_MMC_SndLmmUserSpecPlmnSearchEndNotify( VOS_VOID );

VOS_VOID NAS_MMC_SndLmmBgStopPlmnSearchReq(VOS_VOID);
VOS_VOID NAS_MMC_SndLmmFastPlmnSearchReq(
    NAS_MML_PLMN_ID_STRU               *pstDestPlmn
);

VOS_VOID NAS_MMC_SndLmmBgPlmnSearchReq(
    NAS_MML_PLMN_WITH_RAT_STRU         *pstDestPlmn
);




VOS_VOID NAS_MMC_SndLmmGetGeoPlmnSearchReq(VOS_VOID);

VOS_VOID NAS_MMC_SndLmmStopGetGeoPlmnSearchReq(VOS_VOID);



VOS_VOID  NAS_MMC_SndLmmUeOocStatusInd( VOS_VOID );


VOS_VOID NAS_MMC_SndLmmWcdmaSysInfoInd(
    struct MsgCB                       *pstMsg
);

VOS_VOID NAS_MMC_SndLmmGsmSysInfoInd(
    struct MsgCB                       *pstMsg
);

VOS_VOID NAS_MMC_SndLmmCellSelReq(
    MMC_LMM_CELL_SEL_TYPE_ENUM_UINT32       ulSelType
);

VOS_VOID NAS_MMC_SndLmmSuspendRelReq(VOS_VOID);

VOS_VOID NAS_MMC_SndLmmOtherModemInfoNotify(
    MMC_LMM_OTHER_MODEM_INFO_NOTIFY_STRU                   *pstOtherModemInfoMsg
);

VOS_VOID NAS_MMC_SndLmmLteSysInfoInd(
    LMM_MMC_SYS_INFO_IND_STRU          *pstLmmSysInfoMsg
);

#if (FEATURE_ON == FEATURE_DSDS)
VOS_VOID NAS_MMC_SndLmmBeginSessionNotify(
    MMC_LMM_SESSION_TYPE_ENUM_UINT8     enSessionType
);
VOS_VOID NAS_MMC_SndLmmEndSessionNotify(
    MMC_LMM_SESSION_TYPE_ENUM_UINT8     enSessionType
);

#endif


VOS_VOID NAS_MMC_SndLmmImsVoiceCapChangeNtf(
    VOS_UINT8                           ucImsVoiceAvail
);
VOS_VOID NAS_MMC_SndLmmCellSignReportNotify(VOS_VOID);

VOS_VOID NAS_MMC_SndLmmVoiceDomainChangeInd(
    MMC_LMM_VOICE_DOMAIN_ENUM_UINT32    enVoiceDomain
);
#endif

/* Added by l00324781 for CDMA Iteration 10, 2015-4-7, start */
VOS_VOID NAS_MMC_SndLmmBgSearchHrpdReq(VOS_VOID);
VOS_VOID NAS_MMC_SndLmmStopBgSearchHrpdReq(VOS_VOID);
/* Added by l00324781 for CDMA Iteration 10, 2015-4-7, end */


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

