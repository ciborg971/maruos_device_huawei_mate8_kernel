

#ifndef __TAFAPSFSMMSMODIFYING_H__
#define __TAFAPSFSMMSMODIFYING_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include  "vos.h"


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
VOS_UINT32 TAF_APS_RcvAtPsCallAnswerReq_MsModifying_WaitSmModifyCnf(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallAnswerReq_MsModifying_WaitSmModifyCnfSuspend(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallAnswerReq_MsModifying_WaitSndcpModifyRsp(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallAnswerReq_MsModifying_WaitSndcpModifyRspSuspend(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallEndReq_MsModifying_WaitSmModifyCnf(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallEndReq_MsModifying_WaitSmModifyCnfSuspend(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallEndReq_MsModifying_WaitSndcpModifyRsp(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallEndReq_MsModifying_WaitSndcpModifyRspSuspend(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallHangupReq_MsModifying_WaitSmModifyCnf(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallHangupReq_MsModifying_WaitSmModifyCnfSuspend(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallHangupReq_MsModifying_WaitSndcpModifyRsp(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallHangupReq_MsModifying_WaitSndcpModifyRspSuspend(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_VOID TAF_APS_RcvAtPsCallModifyReq_MsModifying_GuMode(VOS_VOID);
VOS_UINT32 TAF_APS_RcvAtPsCallModifyReq_MsModifying_Init(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32  TAF_APS_RcvSmPdpModifyInd_MsModifying_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallModifyReq_MsModifying_WaitSmModifyCnf(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallModifyReq_MsModifying_WaitSmModifyCnfSuspend(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallModifyReq_MsModifying_WaitSndcpModifyRsp(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallModifyReq_MsModifying_WaitSndcpModifyRspSuspend(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallOrigReq_MsModifying_WaitSmModifyCnf(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallOrigReq_MsModifying_WaitSmModifyCnfSuspend(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallOrigReq_MsModifying_WaitSndcpModifyRsp(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallOrigReq_MsModifying_WaitSndcpModifyRspSuspend(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsPppDailOrigReq_MsModifying_WaitSmModifyCnf(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsPppDailOrigReq_MsModifying_WaitSmModifyCnfSuspend(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsPppDailOrigReq_MsModifying_WaitSndcpModifyRsp(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsPppDailOrigReq_MsModifying_WaitSndcpModifyRspSuspend(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_MsModifying_WaitSmModifyCnf(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_MsModifying_WaitSmModifyCnfSuspend(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_MsModifying_WaitSndcpModifyRsp(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_MsModifying_WaitSndcpModifyRspSuspend(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_MsModifying_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsPppDailOrigReq_MsModifying_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallOrigReq_MsModifying_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallEndReq_MsModifying_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32  TAF_APS_RcvAtPsCallModifyReq_MsModifying_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32  TAF_APS_RcvAtPsCallAnswerReq_MsModifying_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32  TAF_APS_RcvAtPsCallHangupReq_MsModifying_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvSmPdpDeactivateInd_MsModifying_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32  TAF_APS_RcvRabmLocalPdpDeactReq_MsModifying_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvInterServiceStatusChangeInd_MsModifying_Suspend(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvInterServiceStatusChangeInd_MsModifying_WaitSmModifyCnf(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvInterServiceStatusChangeInd_MsModifying_WaitSmModifyCnfSuspend(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvInterServiceStatusChangeInd_MsModifying_WaitSndcpModifyRsp(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvInterServiceStatusChangeInd_MsModifying_WaitSndcpModifyRspSuspend(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvSmPdpDeactivateInd_MsModifying_WaitSmModifyCnf(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvSmPdpDeactivateInd_MsModifying_WaitSmModifyCnfSuspend(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvSmPdpModifyCnf_MsModifying_WaitSmModifyCnf(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvSmPdpModifyRej_MsModifying_WaitSmModifyCnf(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvSmPdpModifyRej_MsModifying_WaitSmModifyCnfSuspend(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvSndcpModifyRsp_MsModifying_WaitSndcpModifyRsp(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvSndcpModifyRsp_MsModifying_WaitSndcpModifyRspSuspend(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvSndcpStatusReq_MsModifying_WaitSndcpModifyRsp(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32  TAF_APS_RcvTafInternalPdpDeaReq_MsModifying_WaitSndcpModifyRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvSndcpStatusReq_MsModifying_WaitSndcpModifyRspSuspend(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvTiTafApsMsModifyingExpired_MsModifying_Suspend(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvTiTafApsMsModifyingExpired_MsModifying_WaitSmModifyCnf(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32  TAF_APS_RcvRabmLocalPdpDeactReq_MsModifying_WaitSmModifyCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32  TAF_APS_RcvTafInternalPdpDeaReq_MsModifying_WaitSmModifyCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvTiTafApsMsModifyingExpired_MsModifying_WaitSmModifyCnfSuspend(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvTiTafApsMsModifyingExpired_MsModifying_WaitSndcpModifyRsp(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvTiTafApsMsModifyingExpired_MsModifying_WaitSndcpModifyRspSuspend(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32  TAF_APS_RcvTafInternalPdpDeaReq_MsModifying_WaitSndcpModifyRspSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvApsLocalPdpDeactivateInd_MsModifying_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvApsLocalPdpDeactivateInd_MsModifying_WaitSmModifyCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvApsLocalPdpDeactivateInd_MsModifying_WaitSmModifyCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

#if (FEATURE_ON == FEATURE_LTE)
VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_MsModifying_WaitL4aModifyCnf(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallAnswerReq_MsModifying_WaitL4aModifyCnf(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallAnswerReq_MsModifying_WaitL4aModifyCnfSuspend(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallEndReq_MsModifying_WaitL4aModifyCnf(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallEndReq_MsModifying_WaitL4aModifyCnfSuspend(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallModifyReq_MsModifying_WaitL4aModifyCnf(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallModifyReq_MsModifying_WaitL4aModifyCnfSuspend(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallOrigReq_MsModifying_WaitL4aModifyCnf(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallOrigReq_MsModifying_WaitL4aModifyCnfSuspend(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsPppDailOrigReq_MsModifying_WaitL4aModifyCnf(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsPppDailOrigReq_MsModifying_WaitL4aModifyCnfSuspend(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_MsModifying_WaitL4aModifyCnfSuspend(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvL4aPdpModifyCnf_MsModifying_WaitL4aModifyCnfSuspend(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvL4aPdpModifyCnf_MsModifying_WaitL4aModifyCnf(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvL4aPdpModifyRej_MsModifying_WaitL4aModifyCnfSuspend(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32  TAF_APS_RcvInterServiceStatusChangeInd_MsModifying_WaitL4aModifyCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvEsmSmEpsBearerInfoInd_MsModifying_WaitL4aModifyCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvL4aPdpModifyRej_MsModifying_WaitL4aModifyCnf(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallHangupReq_MsModifying_WaitL4aModifyCnf(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallHangupReq_MsModifying_WaitL4aModifyCnfSuspend(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvInterServiceStatusChangeInd_MsModifying_WaitL4aModifyCnf(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvEsmSmEpsBearerInfoInd_MsModifying_WaitL4aModifyCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvTiTafApsMsModifyingExpired_MsModifying_WaitL4aModifyCnf(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvTiTafApsMsModifyingExpired_MsModifying_WaitL4aModifyCnfSuspend(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_VOID TAF_APS_RcvAtPsCallModifyReq_MsModifying_LteMode(VOS_VOID);

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

#endif /* end of TafApsFsmMsModifying.h */
