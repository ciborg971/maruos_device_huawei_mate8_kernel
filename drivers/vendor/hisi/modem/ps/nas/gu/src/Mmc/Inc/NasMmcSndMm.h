
#ifndef _NAS_MMC_SND_MM_H
#define _NAS_MMC_SND_MM_H_

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include  "vos.h"
#include  "Nasrrcinterface.h"
#include  "MmcGmmInterface.h"
#include  "MmcMmInterface.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "MmcLmmInterface.h"
#endif
#include  "NasCommDef.h"
#include  "NasMmlCtx.h"
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
VOS_VOID NAS_MMC_SndMmStartReq(VOS_VOID);

VOS_VOID   NAS_MMC_SndMmPlmnSchInit(VOS_VOID);

VOS_VOID   NAS_MMC_SndMmWasSysInfoInd(
    VOS_UINT32                          ulForbiddenFlg,
    VOS_UINT32                          ulUserSpecSrchPlmnFlg,
    struct MsgCB                       *pstMsg
);

VOS_VOID   NAS_MMC_SndMmGsmSysInfoInd(
    VOS_UINT32                          ulForbiddenFlg,
    VOS_UINT32                          ulUserSpecSrchPlmnFlg,
    struct MsgCB                       *pstMsg
);

VOS_VOID NAS_MMC_SndMmPowerOffReq(VOS_VOID);

VOS_VOID NAS_MMC_SndMmSuspendInd(
    RRMM_SUSPEND_IND_ST                *pstMsg
);

VOS_VOID NAS_MMC_SndMmResumeInd(
    RRMM_RESUME_IND_ST                 *pstMsg
);

VOS_VOID  NAS_MMC_SndMmCoverageLostInd(VOS_VOID);

VOS_VOID NAS_MMC_SndMmRelReq(VOS_VOID);

VOS_VOID NAS_MMC_SndMmAttachReq(
                                            VOS_UINT32 ulOpid,
                                            VOS_UINT32 ulAttachType);
VOS_VOID NAS_MMC_SndMmDetachReq(
    VOS_UINT32                          ulOpid,
    MMC_MM_DETACH_TYPE_ENUM_UINT32      enDetachType,  /* detach���� */
    MMC_MM_DETACH_REASON_ENUM_UINT32    enDetachReason /* detachԭ�� */
);

VOS_VOID NAS_MMC_SndMmRatChangeInd(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enNetRatType
);

#if (FEATURE_ON == FEATURE_LTE)
VOS_VOID NAS_MMC_SndMmLteSysinfoInd(
    LMM_MMC_SYS_INFO_IND_STRU          *pstLmmSysInfoMsg
);


VOS_VOID  NAS_MMC_SndMmLmmAttachInd(
    LMM_MMC_ATTACH_IND_STRU            *pstAttachInd
);

VOS_VOID  NAS_MMC_SndMmLmmTauResultInd(
    LMM_MMC_TAU_RESULT_IND_STRU        *pstTauResultInd
);

VOS_VOID  NAS_MMC_SndMmLmmSerResultnd(
    LMM_MMC_SERVICE_RESULT_IND_STRU    *pstSerInd
);


VOS_VOID  NAS_MMC_SndMmLmmMtDetachInd(
    LMM_MMC_DETACH_IND_STRU            *pstDetachInd
);

VOS_VOID  NAS_MMC_SndMmLmmMoDetachInd(
    LMM_MMC_DETACH_CNF_STRU            *pstDetachCnf
);

VOS_VOID  NAS_MMC_SndMmLmmLocalDetachInd(
    LMM_MMC_DETACH_IND_STRU            *pstDetachInd
);

VOS_VOID  NAS_MMC_SndMmLmmTimerStateNotify(
    LMM_MMC_TIMER_STATE_NOTIFY_STRU    *pstTimerStatusNotify
);


#endif


VOS_VOID NAS_MMC_SndMmModeChangeReq(
    NAS_MML_MS_MODE_ENUM_UINT8          enMsMode
);

VOS_VOID NAS_MMC_SndMmLauReq(
    MMC_MM_LAU_REQ_REASON_ENUM_UINT32   enLauReqReason
);
VOS_VOID  NAS_MMC_SndMmWasAcInfoChangeInd(
    VOS_UINT8                           ucCsResTrictionRegister,
    VOS_UINT8                           ucPsResTrictionRegister,
    VOS_UINT8                           ucOldCsResTrictionRegister,
    VOS_UINT8                           ucOldPsResTrictionRegister
);

VOS_VOID NAS_MMC_SndMmSrvccInfoNotify(VOS_VOID);

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


