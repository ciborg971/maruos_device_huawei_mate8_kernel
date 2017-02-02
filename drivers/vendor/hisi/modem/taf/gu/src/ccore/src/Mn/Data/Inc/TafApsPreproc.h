

#ifndef __TAFAPSPREPROC_H__
#define __TAFAPSPREPROC_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "Ps.h"
#include "TafApsFsmMainTbl.h"
#include "TafApsFsmMsActivatingTbl.h"
#include "TafApsFsmNwActivatingTbl.h"
#include "TafApsApi.h"

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


VOS_UINT32 TAF_APS_RcvAtGetDsFlowInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvAtClearDsFlowReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvAtConfigDsFlowRptReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvSetApDsFlowRptCfgReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvGetApDsFlowRptCfgReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvSetDsFlowNvWriteCfgReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvGetDsFlowNvWriteCfgReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvTiDsFlowReportExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvTiDsFlowWriteNvExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 TAF_APS_RcvAtGetPdpInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvAtGetPrimPdpCtxInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvAtGetSecPdpCtxInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvAtGetTftInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvAtGetPdpIpAddrInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvAtGetAnsModeInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtGetPdpContextStateReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

#if ( FEATURE_ON == FEATURE_LTE )

VOS_UINT32 TAF_APS_RcvAtGetDynamicPrimPdpCtxInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvAtGetDynamicSecPdpCtxInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvAtGetDynamicTftInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvAtGetEpsQosInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvAtGetDynamicEpsQosInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvAtGetLteCsInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 TAF_APS_RcvL4aGetLteCsCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvAtGetCemodeInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 TAF_APS_RcvL4aGetCemodeCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 TAF_APS_RcvAtSetPdprofInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvL4aSetPdprofInfoCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvTiSetPdprofInfoExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


#endif

VOS_UINT32 TAF_APS_RcvAtGetAuthDataInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvAtGetUmtsQosInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvAtGetUmtsQosMinInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvAtGetDynamicUmtsQosInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvAtGetPdpAuthInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvAtGetPdpDnsInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvAtSetPrimPdpCtxInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvAtSetSecPdpCtxInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvAtSetTftInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvAtSetAnsModeInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


#if ( FEATURE_ON == FEATURE_LTE )
VOS_UINT32 TAF_APS_RcvAtSetEpsQosInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
#endif

VOS_UINT32 TAF_APS_RcvAtSetAuthDataInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvAtSetUmtsQosInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvAtSetUmtsQosMinInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvAtSetPdpAuthInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvAtSetPdpDnsInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvAtTrigGprsDataReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvAtConfigNbnsFunctionReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvAtConfigCallStubReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

#if ( FEATURE_ON == FEATURE_LTE )
VOS_UINT32 TAF_APS_RcvL4aSetCgdcontCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvL4aSetCgdscontCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvL4aSetCgtftCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvL4aSetCgautoCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvL4aSetCgansCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvL4aSetCgeqosCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvL4aSetAuthdataCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvL4aSetCgcontrdpCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvL4aSetCgscontrdpCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvL4aSetCgtftrdpCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvL4aSetCgeqosrdpCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvTiSetCgdcontCnfExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvTiSetCgdscontCnfExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvTiSetCgtftCnfExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvTiSetCgautoCnfExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvTiSetCgeqosCnfExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvTiSetAuthdataCnfExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvTiGetCemodeCnfExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvTiGetLtecsCnfExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvTiSetCgcontrdpCnfExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvTiSetCgscontrdpCnfExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvTiSetCgtftrdpCnfExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvTiSetCgeqosrdpCnfExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

TAF_PS_CAUSE_ENUM_UINT32 TAF_APS_TransL4aErrorCode(
    VOS_UINT32                          ulL4aErrCode
);


#endif


VOS_UINT32 TAF_APS_RcvAtFindCidForDialReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvAtGetCidParaReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvAtSetCidParaReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvAtGetCidQosParaReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvAtSetCidQosParaReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvAtPsCallModifyReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvAtPsCallOrigReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvAtPppDialOrigReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvSmRegMsg_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvL4aRegMsg_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvEsmRegMsg_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvRabmRegMsg_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvSndcpRegMsg_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);




/* Deleted by y00314741 for CDMA Iteration 15, 2015-5-19, begin */

/* Deleted by y00314741 for CDMA Iteration 15, 2015-5-19, end */

VOS_UINT32 TAF_APS_ProcActivatePdpContext_PreProc(
    VOS_UINT8                           ucCidValue,
    TAF_PS_SET_PDP_STATE_REQ_STRU      *pstSetPdpStateReq
);

VOS_UINT32 TAF_APS_ProcDeactivatePdpContext_PreProc(
    VOS_UINT8                           ucCidValue,
    TAF_PS_SET_PDP_STATE_REQ_STRU      *pstSetPdpStateReq
);

/* Deleted by y00314741 for CDMA Iteration 15, 2015-5-19, begin */

/* Deleted by y00314741 for CDMA Iteration 15, 2015-5-19, end */
VOS_UINT32 TAF_APS_RcvAtGetGprsActiveTypeReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallEndReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallAnswerReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallHangupReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvSmRegPdpActCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvSmRegPdpActRej_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvSmRegPdpActInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvSmRegPdpModifyInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvSmRegPdpModifyCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvSmRegPdpModifyRej_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvSmRegPdpDeactivInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvSmRegPdpDeactivCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvSmRegPdpActSecCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvSmRegPdpActSecRej_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

#if (FEATURE_ON == FEATURE_LTE)
VOS_UINT32 TAF_APS_RcvL4aApsPdpActivateCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvL4aApsPdpActivateRej_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvL4aApsPdpActivateInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvL4aApsPdpModifyCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvL4aApsPdpModifyRej_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvL4aApsPdpModifyInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvL4aApsPdpDeactivateCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvL4aApsPdpDeactivateRej_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvL4aApsPdpDeactivateInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvL4aApsPdpSetupInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvL4aSenNdisconnCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvL4aPppDialCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvL4aPsCallEndCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvEsmEpsBearInfoInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

#if (FEATURE_ON == FEATURE_IMS)
VOS_UINT32 TAF_APS_RcvEsmNotificationInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
#endif

#endif
VOS_UINT32 TAF_APS_RcvSndcpActivateRsp_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvSndcpModifyRsp_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvSndcpDeactRsp_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

#if (FEATURE_ON == FEATURE_IPV6)
VOS_UINT32 TAF_APS_RcvNdIpv6ParaInfoNotifyInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
#endif


VOS_UINT32 TAF_APS_RcvAtSetDnsQueryReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 TAF_APS_GetActPdpLimitTimerLen(
    VOS_UINT8                           ucFailCount
);
VOS_VOID TAF_APS_ProcPdpActLimit_PreProc(
    VOS_UINT8                           ucTryingCount
);

VOS_UINT32 TAF_APS_RcvTiApsMsActvaingExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvTiApsLimitPdpActExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_IsPdpActLimit_PreProc(VOS_VOID);

VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_PdpActLimit_PreProc(
    TAF_PS_SET_PDP_STATE_REQ_STRU      *pstSetPdpStateReq
);

VOS_UINT32 TAF_APS_RcvOmSetDsflowRptReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvMmcServiceStatusInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

/*****************************************************************************
 �� �� ��  : TAF_Aps_RcvGetCidSdfReq
 ��������  : ���ڻ�ȡ����NV���е�SDF������ϢԤ����
 �������  : VOS_VOID                           *pMsgData
 �������  : ��
 �� �� ֵ  : VOS_UINT32
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPsGetCidSdfReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvSetImsPdpCfgReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

#if (FEATURE_ON == FEATURE_CL_INTERWORK)
VOS_UINT8 TAF_APS_LCCheckReqValid(
    TAF_CTRL_STRU                       *pstCtrlInfo
);
#endif

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

VOS_UINT32 TAF_APS_RcvXccDataCallSuspendInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvXccDataCallResumeInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvXccAnswerDataCallCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvXccDataCallConnInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvXccDataCallDiscInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvXccDataCallResumeInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvXccDataCallSuspendInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvXccDataServiceConnInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvXccHangupDataCallCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvXccHangupDataCallCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvXccHangupDataCallCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvXccIncomingCallInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvXccOrigDataCallCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvXccSoCtrlMsg_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvPppActCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvPppDeactCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvPppDeactNtf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

/* Added by y00314741 for CDMA Iteration 11, 2015-3-27, begin */
VOS_UINT32 TAF_APS_RcvPppModifyInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
/* Added by y00314741 for CDMA Iteration 11, 2015-3-27, end */
VOS_UINT32 TAF_APS_RcvCdsServiceInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_SetCqosPriReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
/* Deleted by y00314741 for CDMA Iteration 11, 2015-4-8, begin */

/* Deleted by y00314741 for CDMA Iteration 11, 2015-4-8, end */
VOS_UINT32 TAF_APS_RcvPsCallEnterDormantInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvTiHatExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvTiHtExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvMmaEpdszidInfo_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvXregRegBeginInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvPsInterEpdszidReOrig_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


/* Added by y00314741 for CDMA 1X Iteration 7, 2015-1-4, begin */
VOS_UINT32 TAF_APS_RcvPsHaiChangeInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
/* Added by y00314741 for CDMA 1X Iteration 7, 2015-1-4, end */
VOS_UINT32 TAF_APS_RcvXccUpdateDataCallInfoInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

/* Added by y00314741 for CDMA 1X Iteration 9, 2015-2-5, begin */
VOS_UINT32 TAF_APS_RcvHsmOrigCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvHsmConnectInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvHsmDiscCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvHsmDiscInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvHsmLocChangedInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvHsm1XToHrpdHandOff_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

/* Added by y00314741 for CDMA 1X Iteration 9, 2015-2-5, end */

VOS_UINT32 TAF_APS_RcvPsSet1xPktDataInactivityTimeLenReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvPsGet1xPktDataInactivityTimerLenReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvPowerOnInd_Preproc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

/* Added by y00314741 for CDMA 1X Iteration 9, 2015-2-5, end */

VOS_UINT32 TAF_APS_RcvGetCgmtuValue_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
/* Added by y00314741 for CDMA Iteration 11, 2015-4-2, begin */
VOS_UINT32 TAF_APS_RcvPsSetDialModeReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvMma1XServiceStatusInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvMmaCLServiceStatusInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


/* Added by y00314741 for CDMA Iteration 11, 2015-4-2, end */
/* Added by y00314741 for CDMA Iteration 15, 2015-5-8, begin */
VOS_UINT32 TAF_APS_RcvEhsmPdnActInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvEhsmPdnDeactInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvEhsmLteHandoverToEhrpdInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvEhsmPdnActCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvEhsmPdnDeactCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvEhsmReconnCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvDhcpDnsIpv4Cnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvDhcpDnsIpv6Cnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvInterPsServiceModeModifyInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

/* Added by y00314741 for CDMA Iteration 15, 2015-5-8, end */

VOS_UINT32 TAF_APS_RcvAtSet1xDormantTimer_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvAtGet1xDormantTimer_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
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

#endif /* end of TafApsPreproc.h */
