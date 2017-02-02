
#ifndef __NASGMMPROCLRESULT_H__
#define __NASGMMPROCLRESULT_H__
/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include  "vos.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "MmcLmmInterface.h"
#endif

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
#if (FEATURE_ON == FEATURE_LTE)
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;
    NAS_LMM_GUTI_STRU                   stGutiMsg;
}NAS_GMM_LOG_GUTI_INFO_STRU;
#endif

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
extern VOS_UINT32 NAS_GMM_IsGutiInfoValid( VOS_VOID );


extern VOS_VOID NAS_GMM_ConvertLmmPlmnToGmmPlmnId(
           MMC_LMM_PLMN_ID_STRU                *pstLmmPlmn,
           GMM_PLMN_ID_STRU                    *pstGmmPlmn
       );

extern VOS_VOID NAS_GMM_GetGUSecContextFromEpsSecContextInReselect(
           struct MsgCB                       *pstMsg
       );
extern VOS_VOID NAS_GMM_GetGUSecContextFromEpsSecContextInHandOver(
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32  NAS_GMM_GetGuSecuInfo(
           NAS_GUMM_UMTS_CONTEXT_STRU         *pstSecuContext
       );
extern VOS_UINT32  NAS_GMM_GetLaiInfo(
           MMC_LMM_LAI_STRU                    *pstLai
       );

extern VOS_UINT32  NAS_GMM_GetRaiInfo(
    MMC_LMM_RAI_STRU                    *pstRai
);
extern VOS_VOID  NAS_GMM_GetTmsiStatusInfo(
           MMC_LMM_TMSI_STATUS_TYPE_ENUM_UINT32 *ulTmsiStatus
       );
extern VOS_UINT32  NAS_GMM_MapLaiFromGUTI( VOS_VOID );
extern VOS_UINT32  NAS_GMM_MapPtmsiFromGUTI( VOS_VOID );
extern VOS_UINT32  NAS_GMM_MapPtmsiSignFromGUTIAndNasToken( VOS_VOID );
extern VOS_UINT32  NAS_GMM_MapRaiFromGUTI( VOS_VOID );
extern VOS_VOID  NAS_GMM_ProcLmmRejCause3( VOS_VOID );
extern VOS_VOID NAS_GMM_RcvLmmAttachCause_Handling(
    NAS_LMM_CN_CAUSE_ENUM_UINT8         enCnCause,
    VOS_UINT32                          ulAttemptCount
);

extern VOS_VOID  NAS_GMM_RcvLmmAttachResult(
           VOS_VOID                           *pstMsg
       );
extern VOS_VOID  NAS_GMM_RcvLmmAuthResult(
           VOS_VOID                           *pstMsg
       );
extern VOS_VOID  NAS_GMM_RcvLmmNwInitDetachIndCause_Handling(
           NAS_LMM_CN_CAUSE_ENUM_UINT8         enCnCause
       );

extern VOS_VOID  NAS_GMM_RcvLmmServiceCause_Handling(
            NAS_LMM_CN_CAUSE_ENUM_UINT8        enCnCause
       );
extern VOS_VOID  NAS_GMM_RcvLmmServiceResult(
           VOS_VOID                           *pstMsg
       );
extern VOS_VOID NAS_GMM_RcvLmmTauCause_Handling(
    NAS_LMM_CN_CAUSE_ENUM_UINT8                             enCnCause,
    VOS_UINT32                                              ulAttemptCount,
    MMC_LMM_TAI_IN_LIST_FLAG_ENUM_UINT8                     enTaiInListFlag,
    MMC_LMM_EPS_UPDATE_STATUS_ENUM_UINT8                    enEmmUpStat
);
extern VOS_VOID  NAS_GMM_RcvLmmTauResult(
           VOS_VOID                           *pstMsg
       );

VOS_VOID NAS_GMM_LogGutiInfo(
    NAS_LMM_GUTI_STRU                  *pstGuti
);

VOS_VOID  NAS_GMM_RcvLmmMtDetachInd(
    struct MsgCB                       *pstMsg
);

VOS_VOID NAS_GMM_RcvLmmMoDetachInd(
    struct MsgCB                       *pstMsg
);

VOS_VOID NAS_GMM_RcvLmmLocalDetachInd(
    struct MsgCB                       *pstMsg
);


VOS_VOID NAS_GMM_RcvLmmAttachRegFailOtherCause(
    VOS_UINT32                          ulAttemptCount
);

VOS_VOID NAS_GMM_RcvLmmTauRegFailOtherCause(
    VOS_UINT32                                              ulAttemptCount,
    MMC_LMM_TAI_IN_LIST_FLAG_ENUM_UINT8                     enTaiInListFlag,
    MMC_LMM_EPS_UPDATE_STATUS_ENUM_UINT8                    enEmmUpStat
);
VOS_VOID NAS_GMM_RcvLmmAttachRegFailCause42SevereNetworkFailure(
    VOS_UINT32                          ulAttemptCount
);
VOS_VOID NAS_GMM_RcvLmmTauRegFailCause42SevereNetworkFailure(
    VOS_UINT32                                              ulAttemptCount,
    MMC_LMM_TAI_IN_LIST_FLAG_ENUM_UINT8                     enTaiInListFlag,
    MMC_LMM_EPS_UPDATE_STATUS_ENUM_UINT8                    enEmmUpStat
);



extern VOS_UINT32 NAS_GMM_IsNeedUpdatePsUpdateStatus(
    VOS_UINT32                                              ulAttemptCount,
    MMC_LMM_TAI_IN_LIST_FLAG_ENUM_UINT8                     enTaiInListFlag,
    MMC_LMM_EPS_UPDATE_STATUS_ENUM_UINT8                    enEmmUpStat
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

#endif /* end of NasGmmProcLResult.h */
