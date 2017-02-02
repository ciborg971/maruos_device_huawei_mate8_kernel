

#ifndef _TAF_XSMS_MO_FSM_MAIN_H_
#define _TAF_XSMS_MO_FSM_MAIN_H_

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include  "vos.h"
#include  "TafXsmsCtx.h"
#include  "cas_1x_control_main_nas_pif.h"
#include  "xcc_taf_pif.h"
#include  "xcc_sms_pif.h"



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#pragma pack(4)

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

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
extern VOS_UINT32 TAF_XSMS_MoFsmMainProc(MsgBlock *pstMsg);
extern VOS_UINT32 TAF_XSMS_MoIdleRcvAtSendReqOnDschProc(VOS_VOID);
extern VOS_UINT32 TAF_XSMS_MoIdleRcvAtSendReqOnCschProc(VOS_VOID);

extern VOS_UINT32 TAF_XSMS_MoIdleRcvAtSendReqOnDschOrCschProc(TAF_XSMS_MSG_MO_REC_STRU *pstRecAddr);

extern VOS_UINT32 TAF_XSMS_MoIdleRcvAtSendReqDispatchProc(TAF_XSMS_MSG_MO_REC_STRU *pstMoRec);
extern VOS_VOID TAF_XSMS_MoIncreaseMessageId(VOS_VOID);

extern VOS_UINT32 TAF_XSMS_RcvAtSendReqProc_MoIdle(VOS_UINT32 ulEventType, struct MsgCB *pstMsg);

extern VOS_UINT32 TAF_XSMS_RcvXccOrigCallCnf_MoWaitXccOrigCallCnf(VOS_UINT32 ulEventType, struct MsgCB *pstMsg);

extern VOS_UINT32 TAF_XSMS_RcvXccCallCnfTimeOut_MoWaitXccCallCnf(VOS_UINT32 ulEventType, struct MsgCB *pstMsg);

extern VOS_UINT32 TAF_XSMS_RcvRelinkTimeOut_MoWaitXccOrigCallCnf(VOS_UINT32 ulEventType, struct MsgCB *pstMsg);


extern VOS_UINT32 TAF_XSMS_RcvMoLinkAbort_MoWaitSoInd(VOS_UINT32 ulEventType, struct MsgCB *pstMsg);

extern VOS_UINT32 TAF_XSMS_RcvXccSoIndTimeOut_MoWaitXccSoInd(VOS_UINT32 ulEventType, struct MsgCB *pstMsg);

extern VOS_UINT32 TAF_XSMS_RcvXccSoInd_MoWaitXccSoInd(VOS_UINT32 ulEventType, struct MsgCB *pstMsg);

extern VOS_UINT32 TAF_XSMS_RcvDschDataCnf_MoWaitAsCnf(VOS_UINT32 ulEventType, struct MsgCB *pstMsg);

extern VOS_UINT32 TAF_XSMS_MoAccessChanResendProc(CAS_CNAS_1X_DATA_CNF_RSLT_ENUM_UINT8 enRslt);

extern VOS_UINT32 TAF_XSMS_MoTrafficChanResendProc(CAS_CNAS_1X_DATA_CNF_RSLT_ENUM_UINT8 enRslt);

extern VOS_UINT32 TAF_XSMS_MoBothChanResendProc(CAS_CNAS_1X_DATA_CNF_RSLT_ENUM_UINT8 enRslt);

extern VOS_UINT32 TAF_XSMS_MoAsDataCnfErrProc(CAS_CNAS_1X_DATA_CNF_RSLT_ENUM_UINT8 enRslt);

extern VOS_UINT32 TAF_XSMS_RcvAsCnfTimeout_MoWaitAsCnf(VOS_UINT32 ulEventType, struct MsgCB *pstMsg);

extern VOS_UINT32 TAF_XSMS_RcvResendTimeOut_MoWaitAsCnf(VOS_UINT32 ulEventType, struct MsgCB *pstMsg);

extern VOS_UINT32 TAF_XSMS_RcvCschDataCnf_MoWaitAsCnf(VOS_UINT32 ulEventType, struct MsgCB *pstMsg);

extern VOS_UINT32 TAF_XSMS_RcvDschTlACK_MoWaitTlACK(VOS_UINT32 ulEventType, struct MsgCB *pstMsg);

extern VOS_UINT32 TAF_XSMS_RcvCschTlACK_MoWaitTlACK(VOS_UINT32 ulEventType, struct MsgCB *pstMsg);

extern VOS_UINT32 TAF_XSMS_RcvTlAckTimeOut_MoWaitTlACK(VOS_UINT32 ulEventType, struct MsgCB *pstMsg);

extern VOS_UINT32 TAF_XSMS_RcvEndCallCnf_MoWaitEndCallCnf(VOS_UINT32 ulEventType, struct MsgCB *pstMsg);

extern VOS_UINT32 TAF_XSMS_RcvEndCallCnfTimeout_MoWaitEndCallCnf(VOS_UINT32 ulEventType, struct MsgCB *pstMsg);

extern VOS_VOID TAF_XSMS_MoPrepareReturnToMoIdle(VOS_VOID);

extern VOS_UINT32 TAF_XSMS_RcvXccOrgiCallCnfRedialCheck(TAF_XCC_CAUSE_ENUM_UINT32 enRslt);

extern VOS_VOID   TAF_XSMS_RcvXccOrigCallCnfRedialProc(TAF_XSMS_MSG_MO_REC_STRU *pstMoRec, XCC_CSMS_ORIG_SMS_CALL_CNF_STRU *pstXccSmsOrigCallCnf);

extern VOS_UINT32 TAF_XSMS_RcvMmaServiceStatus_MoWaitXccOrigCallCnf(VOS_UINT32 ulEventType, struct MsgCB *pstMsg);
extern VOS_UINT32 TAF_XSMS_RcvSmsAbortInd_MoWaitLinkAbort(VOS_UINT32 ulEventType, struct MsgCB *pstMsg);
extern VOS_UINT32  TAF_XSMS_RcvMoLinkAbort_MoWaitAsCnf
(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 TAF_XSMS_RcvStkSendReqProc_MoIdle(VOS_UINT32 ulEventType, struct MsgCB *pstMsg);

extern VOS_UINT32 TAF_XSMS_RcvXpdsSendReqProc_MoIdle
(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 TAF_XSMS_EncodeXsmsMsgBearDataByContext
(
    VOS_UINT8                          *pucData,
    VOS_UINT16                          usDataLen,
    TAF_XSMS_MESSAGE_STRU              *pstXsmsMsg
);

VOS_VOID TAF_XSMS_SndXccOrigReq_MoWaitOrigCnf
(
    VOS_VOID
);

VOS_VOID TAF_XSMS_SndCasCschReq_MoWaitCasCnf
(
    VOS_VOID
);

VOS_UINT32 TAF_XSMS_RcvMoLinkAbort_MoWaitTlAck
(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif


#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif /* end of TafXsmsMoFsmMain.h */

