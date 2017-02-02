
#ifndef _NAS_MMC_PROC_REGINFO_H
#define _NAS_MMC_PROC_REGINFO_H_

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include  "vos.h"
#include "MMC_Global.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "MmcLmmInterface.h"
#endif
#include "MmcGmmInterface.h"
#include "MmcMmInterface.h"
#include "Nasrrcinterface.h"
#include "NasMmcCtx.h"


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
VOS_VOID NAS_MMC_ProcServiceReqRejCause(
    VOS_UINT8                           ucCause
);

VOS_VOID NAS_MMC_ComAcceptAutoPlmnSrch(
    VOS_UINT32                          ulEquPlmnNum,
    MMC_PLMN_ID_STRU                   *pstEquPlmnList
);

VOS_VOID NAS_MMC_SetCurrentPlmnEplmnList(VOS_VOID);


NAS_MMC_PLMN_SRCH_TYPE_ENUM_U8 NAS_MMC_GetCsPlmnSrchType(
    NAS_MMC_REG_FAIL_INFO_STRU         *pstCsRegFailInfo
);

NAS_MMC_PLMN_SRCH_TYPE_ENUM_U8 NAS_MMC_GetPsPlmnSrchType(
    NAS_MMC_REG_FAIL_INFO_STRU         *pstCsRegFailInfo
);

NAS_MMC_PLMN_SRCH_TYPE_ENUM_U8 NAS_MMC_GetPlmnSrchType( VOS_VOID );


VOS_VOID   NAS_MMC_RcvMmRrConnInfoInd (
    MMCMM_RR_CONN_INFO_IND_STRU         *pstMsg
);

VOS_VOID   NAS_MMC_RcvGmmSignalingStatusInd (
    MMCGMM_SIGNALING_STATUS_IND_STRU   *pstMsg
);

VOS_VOID NAS_MMC_RcvRrMmRelInd(
    RRMM_REL_IND_STRU                  *pstMsg
);

VOS_UINT32 NAS_MMC_ProcMmLuResultInd(
        VOS_UINT32                      ulEventType,
        struct MsgCB                   *pstMsg
);

VOS_UINT32 NAS_MMC_ComLuRejProc(
    VOS_UINT8                           ucCause,
    VOS_UINT32                          ulCsUpdateStatus,
    VOS_UINT32                          ulLuAttemptCnt,
    MMC_LAI_STRU                       *pstOldLai
);

VOS_UINT32 NAS_MMC_ProcCombinedRsltRejCause(
    VOS_UINT8                           ucCause,
    VOS_UINT32                          ulAttachAttCounter
);

VOS_VOID NAS_MMC_ProcDetachIndRejCause(
    VOS_UINT8                           ucCause
);

VOS_UINT32 NAS_MMC_ComGprsAttachRauRejProc(
    VOS_UINT8                           ucCause,
    VOS_UINT32                          ulAttachAttCounter
);

VOS_UINT32 NAS_MMC_RcvGmmRegResultInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_IsVodafoneNeedPlmnSrch( VOS_VOID );

NAS_MMC_PLMN_SRCH_TYPE_ENUM_U8  NAS_MMC_GetCSPlmnSrchTypeOnPlmn(
    NAS_MM_CAUSE_ENUM_U8                enRejCause,
    VOS_UINT32                          ulAttemptCounter
);

NAS_MMC_PLMN_SRCH_TYPE_ENUM_U8  NAS_MMC_GetPSPlmnSrchTypeOnPlmn(
    NAS_MM_CAUSE_ENUM_U8                enRejCause,
    VOS_UINT32                          ulAttemptCounter,
    VOS_UINT32                          ulWaitCsRslt
);

#if (FEATURE_ON == FEATURE_LTE)

VOS_VOID NAS_MMC_ProcLmmRejectedCause3(
    NAS_MMC_PLMN_SRCH_INFO_STRU        *pstPlmnSrchInfo
);

VOS_VOID NAS_MMC_ProcLmmRejectedCause9(
    NAS_MMC_PLMN_SRCH_INFO_STRU        *pstPlmnSrchInfo
);

VOS_VOID NAS_MMC_ProcLmmRejectedCause10(
   NAS_MMC_PLMN_SRCH_INFO_STRU         *pstPlmnSrchInfo
);

VOS_VOID NAS_MMC_ProcLmmRejectedCause11(
    NAS_MMC_PLMN_SRCH_INFO_STRU        *pstPlmnSrchInfo
);

VOS_VOID NAS_MMC_ProcLmmRejectedCause12(
    NAS_MMC_PLMN_SRCH_INFO_STRU        *pstPlmnSrchInfo
);

VOS_VOID NAS_MMC_ProcLmmRejectedCause13(
    NAS_MMC_PLMN_SRCH_INFO_STRU        *pstPlmnSrchInfo
);

VOS_VOID NAS_MMC_ProcLmmRejectedCause14(
    NAS_MMC_PLMN_SRCH_INFO_STRU        *pstPlmnSrchInfo
);

VOS_VOID NAS_MMC_ProcLmmRejectedCause15(
    NAS_MMC_PLMN_SRCH_INFO_STRU        *pstPlmnSrchInfo
);

VOS_VOID NAS_MMC_ProcLmmRejectedCause40(
    NAS_MMC_PLMN_SRCH_INFO_STRU        *pstPlmnSrchInfo
);

VOS_VOID NAS_MMC_ProcEpsRegOtherCause(
    VOS_UINT32                          ulRauAttCounter,
    NAS_MMC_PLMN_SRCH_INFO_STRU        *pstPlmnSrchInfo
);

VOS_VOID NAS_MMC_ProcAuthRejCause(
    NAS_MMC_PLMN_SRCH_INFO_STRU        *pstPlmnSrchInfo
);

VOS_VOID NAS_MMC_ProcLmmAttachRej(
    VOS_UINT8                           ucCause,
    VOS_UINT32                          ulAttachAttCounter,
    NAS_MMC_PLMN_SRCH_INFO_STRU        *pstPlmnSrchInfo
);

VOS_VOID NAS_MMC_ProcLmmDetachRej(
    VOS_UINT8                           ucCause,
    NAS_MMC_PLMN_SRCH_INFO_STRU        *pstPlmnSrchInfo
);

VOS_VOID NAS_MMC_ProcLmmTauRej(
    VOS_UINT8                           ucCause,
    VOS_UINT32                          ulAttachAttCounter,
    NAS_MMC_PLMN_SRCH_INFO_STRU        *pstPlmnSrchInfo
);

VOS_VOID NAS_MMC_ProcLmmSerRej(
    VOS_UINT8                           ucCause,
    NAS_MMC_PLMN_SRCH_INFO_STRU        *pstPlmnSrchInfo
);

VOS_VOID NAS_MMC_ProcLmmAttachBar(
    NAS_MMC_PLMN_SRCH_INFO_STRU        *pstPlmnSrchInfo
);

VOS_VOID NAS_MMC_ProcLmmAttachExp(
    VOS_UINT32                          ulAttCounter,
    NAS_MMC_PLMN_SRCH_INFO_STRU        *pstPlmnSrchInfo
);

VOS_VOID NAS_MMC_ProcLmmRegRsltSuccess(
    VOS_UINT32                          ulPlmnNum,
    MMC_PLMN_ID_STRU                   *pstEquPlmnList,
    NAS_MMC_PLMN_SRCH_INFO_STRU        *pstPlmnSrchInfo
);

VOS_VOID  NAS_MMC_ProcTauRslt(
    LMM_MMC_TAU_RESULT_IND_STRU        *pstLmmTauIndMsg,
    NAS_MMC_PLMN_SRCH_INFO_STRU        *pstPlmnSrchInfo
);

VOS_VOID  NAS_MMC_ProcAttachRslt(
    LMM_MMC_ATTACH_IND_STRU            *pstLmmAttachIndMsg,
    NAS_MMC_PLMN_SRCH_INFO_STRU        *pstPlmnSrchInfo
);

VOS_VOID  NAS_MMC_ProcSerRslt(
    LMM_MMC_SERVICE_RESULT_IND_STRU    *pstSerRsltMsg,
    NAS_MMC_PLMN_SRCH_INFO_STRU        *pstPlmnSrchInfo
);

VOS_UINT32 NAS_MMC_JudgeLmmAttachedAttemptCounterValid(
    LMM_MMC_ATTACH_IND_STRU            *pstLmmAttachIndMsg
);

VOS_UINT32 NAS_MMC_JudgeLmmTauAttemptCounterValid(
    LMM_MMC_TAU_RESULT_IND_STRU        *pstLmmTauIndMsg
);

VOS_VOID NAS_MMC_ProcLmmSysInfoInd(
     LMM_MMC_SYS_INFO_IND_STRU         *pstLmmSysInfoMsg
);

#endif


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

