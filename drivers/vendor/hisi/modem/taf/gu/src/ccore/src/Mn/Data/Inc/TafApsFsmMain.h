

#ifndef _TAF_APS_FSM_MAIN_H
#define _TAF_APS_FSM_MAIN_H

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"

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
VOS_UINT32 TAF_APS_RcvAtPsCallAnswerReq_Active(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallAnswerReq_Inactive(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallEndReq_Active(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallHangupReq_Active(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallHangupReq_Inactive(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallModifyReq_Active(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallModifyReq_Inactive(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallOrigReq_Active(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallOrigReq_Inactive(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
#if (FEATURE_ON == FEATURE_LTE)
VOS_UINT32 TAF_APS_RcvL4aPdpActivateInd_Inactive(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvEsmSmEpsBearerInfoInd_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvL4aPdpDeactivateInd_Active(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvL4aPdpSetupInd_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvEsmSmEpsBearerInfoInd_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvL4aPdpModifyInd_Active(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
#endif
VOS_UINT32 TAF_APS_RcvApsInternalPdpDeactivateReq_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvPsInterServiceStatusChangeInd_Active(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsPppDialOrigReq_Active(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsPppDialOrigReq_Inactive(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvRabmSysChgToGprs_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvRabmLocalPdpDeactivateReq_Active(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvSetPdpContextStateReq_Active(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_Inactive(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvSmPdpActivateInd_Inactive(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvSmPdpDeactivateInd_Active(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvSmPdpModifyInd_Active(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvSndcpActivateRsp_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvSndcpDeactivateRsp_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvSndcpStatusReq_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvApsLocalPdpDeactivateInd_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

VOS_UINT32 TAF_APS_RcvPppDeactInd_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvXccDiscInd_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 TAF_APS_RcvPsCallEnterDormantInd_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvCdsServiceInd_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

/* Modified by y00314741 for CDMA Iteration 11, 2015-4-9, begin */
VOS_UINT32 TAF_APS_RcvPsInterServiceStatusChangeReq_Dormant(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
/* Modified by y00314741 for CDMA Iteration 11, 2015-4-9, end */

VOS_UINT32 TAF_APS_RcvCdsServiceInd_Dormant(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvXccIncomingCallInd_Dormant(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 TAF_APS_RcvPsCallOrigReq_Dormant(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvPsCallEndReq_Dormant(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 TAF_APS_RcvPsCallInterEpdszidReOrig_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvPsCallInterEpdszidReOrig_Dormant(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvTiDormantTimerExpired_Dormant(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvXccResumeInd_Dormant(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 TAF_APS_RcvXccUpdateDataCallInfoInd_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

/* Added by y00314741 for CDMA 1X Iteration 9, 2015-2-5, begin */
VOS_UINT32 TAF_APS_RcvHsmCalConnectInd_Dormant(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvTiHrpdLostExpired_Dormant(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

/* Added by y00314741 for CDMA 1X Iteration 9, 2015-2-5, end */

VOS_UINT32 TAF_APS_RcvPppActCnf_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvPppDeactCnf_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

/* Added by y00314741 for CDMA Iteration 11, 2015-3-28, begin */
VOS_UINT32 TAF_APS_RcvPppModifyInd_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvPsCallInter1XToHrpdHandOff_Dormant(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvPsCallInterHrpdTo1XHandOff_Dormant(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
/* Added by y00314741 for CDMA Iteration 11, 2015-3-28, end */

VOS_UINT32 TAF_APS_RcvHsmDiscInd_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvTiPppDectCnfExpired_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvTiPppActCnfExpired_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvInterEndCdmaCallReq_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvPsPppDialOrigReq_Dormant(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

/* Added by y00314741 for CDMA Iteration 15, 2015-5-8, begin */
VOS_UINT32 TAF_APS_RcvEHsmPdnDeactInd_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvEhsmLteHandoverToEhrpdInd_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvEhsmPdnActInd_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvTiDhcpActIpv4Expired_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvTiDhcpActIpv6Expired_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

/* Added by y00314741 for CDMA Iteration 15, 2015-5-8, end */

/* Added by y00314741 for  CDMA Iteration 17, 2015-7-4, begin */
VOS_UINT32 TAF_APS_RcvPsInterEnd1xService_Dormant(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
/* Added by y00314741 for  CDMA Iteration 17, 2015-7-4, end */
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

#endif /* end of _NAS_MMC_FSM_MAIN.h */

