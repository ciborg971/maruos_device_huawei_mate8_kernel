

#ifndef _TAF_XPDS_CP_FSM_PDE_PROC_H_
#define _TAF_XPDS_CP_FSM_PDE_PROC_H_

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "TafXpdsCommFunc.h"

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
#define TAF_XPDS_PPM_TIMER_FRACTION 2

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

extern VOS_VOID TAF_XPDS_SendSessionEndAndQuitL2Fsm(VOS_VOID);
extern VOS_VOID TAF_XPDS_HandleXpdsCpMsaModePdeOperationNI(VOS_VOID);
extern VOS_VOID TAF_XPDS_HandleXpdsCpMsaModePdeOperationSI(VOS_VOID);
extern VOS_VOID TAF_XPDS_HandleXpdsCpMsbModePdeOperation(VOS_VOID);
extern VOS_UINT32 TAF_XPDS_RcvAtGpsPrmInfoRsp_CpL2Pde_MsaWaitGpsPseudoInfo(
   VOS_UINT32                           ulEventType,
   struct MsgCB                        *pstMsg
);

extern VOS_UINT32 TAF_XPDS_RcvAtGpsStopReq_L2Pde(
   VOS_UINT32                           ulEventType,
   struct MsgCB                        *pstMsg
);
extern VOS_UINT32 TAF_XPDS_RcvXpdsCpGeneralTimerTimeout(
   VOS_UINT32                           ulEventType,
   struct MsgCB                        *pstMsg
);
extern VOS_UINT32 TAF_XPDS_RcvXpdsCpMsaModeRecieveCasCnf_AfterPPM(
   VOS_UINT32                           ulEventType,
   struct MsgCB                        *pstMsg
);
extern VOS_UINT32 TAF_XPDS_RcvXpdsCpMsaModeRecieveCasCnf_AfterReqLocRsp(
   VOS_UINT32                           ulEventType,
   struct MsgCB                        *pstMsg
);
extern VOS_UINT32 TAF_XPDS_RcvXpdsCpMsbModeRecieveCasCnf(
   VOS_UINT32                           ulEventType,
   struct MsgCB                        *pstMsg
);
extern VOS_UINT32 TAF_XPDS_RcvXpdsCpMsbModeRecieveGpsLocResp(
   VOS_UINT32                           ulEventType,
   struct MsgCB                        *pstMsg
);
extern VOS_UINT32 TAF_XPDS_RcvXpdsCpMsbModeRecievePdeResp(
   VOS_UINT32                           ulEventType,
   struct MsgCB                        *pstMsg
);
extern VOS_UINT32 TAF_XPDS_RcvXpdsCpPdeProcStart_CpL2Pde_Init(
   VOS_UINT32                           ulEventType,
   struct MsgCB                        *pstMsg
);
extern VOS_UINT32 TAF_XPDS_RcvXpdsForwardPdeDataInd_CpL2Pde_MsaWaitPdeAssistInfo(
   VOS_UINT32                           ulEventType,
   struct MsgCB                        *pstMsg
);
extern VOS_UINT32 TAF_XPDS_RcvXpdsForwardPdeDataInd_CpL2Pde_MsaWaitPdeLocRespInfo(
   VOS_UINT32                           ulEventType,
   struct MsgCB                        *pstMsg
);

extern VOS_UINT32 TAF_XPDS_RcvXpdsCpMsaModeRecieveCasCnf_AfterMsInfo(
   VOS_UINT32                           ulEventType,
   struct MsgCB                        *pstMsg
);

extern VOS_UINT32 TAF_XPDS_RcvXpdsCpMsaModeRecieveCasCnf_AfterPPM_NI(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 TAF_XPDS_RcvXpdsCpMsaModeRecieveCasCnf_AfterAquiAssis_NI(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 TAF_XPDS_RcvXpdsCpMsaModeRecievePrmReq_NI(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 TAF_XPDS_RcvXpdsCpMsaModePPMComplete_NI(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_VOID TAF_XPDS_SendPilotPhaseMeasurement(VOS_VOID);

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


