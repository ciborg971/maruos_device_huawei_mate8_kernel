
#ifndef _NAS_MM_PROCLREGRST_H_
#define _NAS_MM_PROCLREGRST_H_
/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include  "vos.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "MmcLmmInterface.h"
#endif
#include  "GmmStru.h"
#include "NasMmlCtx.h"






#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define MM_EMM_MAX_ATTEMPT_COUNTER      (5)

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
VOS_VOID  NAS_MM_ProcLmmAttachCause_Handling(
    NAS_LMM_CN_CAUSE_ENUM_UINT8         enRejectCause
);

VOS_VOID  NAS_MM_ProcLmmAttachRstInd(
    MMCMM_LMM_ATTACH_IND_STRU          *pstLmmAttachInd
);

VOS_VOID  NAS_MM_ProcLmmAuthRstInd(VOS_VOID);

VOS_VOID  NAS_MM_ProcLmmNwDetachIndCause_Handling(
    NAS_LMM_CN_CAUSE_ENUM_UINT8         enRejectCause
);

VOS_VOID NAS_MM_ProcLmmTauCause_Handling(
    NAS_LMM_CN_CAUSE_ENUM_UINT8         enRejectCause
);


VOS_VOID NAS_MM_ProcLmmRejOtherCause(
    VOS_UINT32                          ulAttemptCounter,
    VOS_UINT32                          ulLmmBitOpAtmpCnt
);

VOS_VOID  NAS_MM_ProcLmmCombinedAttachCause(
    NAS_LMM_CN_CAUSE_ENUM_UINT8         enRejectCause,
    VOS_UINT32                          ulAttemptCounter,
    VOS_UINT32                          ulLmmBitOpAtmpCnt
);

VOS_VOID  NAS_MM_ProcLmmCombinedTauCause(
    NAS_LMM_CN_CAUSE_ENUM_UINT8         enRejectCause,
    VOS_UINT32                          ulAttemptCounter,
    VOS_UINT32                          ulLmmBitOpAtmpCnt
);

VOS_VOID NAS_MM_ProcLmmCombinedAttachOnlyEpsSucc(
    MMCMM_LMM_ATTACH_IND_STRU          *pstLmmCombinedAttachInd
);

VOS_VOID NAS_MM_ProcLmmCombinedAttachSucc(
    MMCMM_LMM_ATTACH_IND_STRU          *pstLmmCombinedAttachInd
);

VOS_VOID NAS_MM_ProcLmmCombinedAttachFail(
    MMCMM_LMM_ATTACH_IND_STRU          *pstLmmCombinedAttachInd
);

VOS_VOID NAS_MM_ProcLmmCombinedTauOnlyEpsSucc(
    MMCMM_LMM_TAU_RESULT_IND_STRU      *pstCombinedTauInd
);

VOS_VOID NAS_MM_ProcLmmCombinedTauSucc(
    MMCMM_LMM_TAU_RESULT_IND_STRU      *pstCombinedTauInd
);

VOS_VOID NAS_MM_ProcLmmCombinedTauFail(
    MMCMM_LMM_TAU_RESULT_IND_STRU      *pstCombinedTauInd
);

VOS_VOID NAS_MM_ProcLmmCombinedTauInd(
    MMCMM_LMM_TAU_RESULT_IND_STRU      *pstCombinedTauInd
);

VOS_UINT8 NAS_MM_RcvLmmAttachInd(
    struct MsgCB                       *pstMsg
);

VOS_UINT8 NAS_MM_RcvLmmTauInd(
    struct MsgCB                       *pstMsg
);

VOS_UINT8 NAS_MM_RcvLmmMTDetachInd(
    struct MsgCB                       *pstMsg
);

VOS_UINT8 NAS_MM_RcvLmmMoDetachInd(
    struct MsgCB                       *pstMsg
);

VOS_UINT8 NAS_MM_RcvLmmServiceRsltInd(
    struct MsgCB                       *pstMsg
);

VOS_UINT8 NAS_MM_RcvLmmSysInfoInd(
    struct MsgCB                       *pstMsg
);

VOS_UINT8 NAS_MM_RcvLmmCombinedStartNotifyReq(
    VOS_VOID                           *pstMsg
);

VOS_VOID  NAS_MM_ConvertLmmPlmnToNasPLMN(
    VOS_UINT8                          *pucLmmPlmn,
    NAS_MML_PLMN_ID_STRU               *pstNasPlmn
);

#endif

#if (FEATURE_ON == FEATURE_LTE)
VOS_UINT8 NAS_MM_RcvLmmCsfbServiceEndInd(
    VOS_VOID                           *pstMsg
);

VOS_UINT8 NAS_MM_RcvLmmCsPagingInd(
    VOS_VOID                           *pstMsg
);

VOS_UINT8 NAS_MM_RcvLmmTimerInfoNotify(
    struct MsgCB                       *pstMsg
);

/*  ɾ��LMM��MM����Ϣ�ı�ָʾ�����Ƶ�LMM��GMM����Ϣ�ı�ָʾ��Ϣ�д��� */
#endif


VOS_UINT8 NAS_MM_RcvLmmHoSecuInfoCnf(
    VOS_VOID                           *pstMsg
);


VOS_VOID NAS_MM_ProcBufferedCsfbService(VOS_VOID);

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

#endif /* end of NasMmProcLRegRst.h */
