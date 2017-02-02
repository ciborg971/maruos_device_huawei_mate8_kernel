/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafXsmsMtFsmMain.h
  �� �� ��   : ����
  ��    ��   : h00300778
  ��������   : 2014��10��31��
  ��������   : TafXsmsMtFsmMain.cͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��10��31��
    ��    ��   : h00300778
    �޸�����   : �����ļ�
******************************************************************************/

#ifndef _TAF_XSMS_MT_FSM_MAIN_H_
#define _TAF_XSMS_MT_FSM_MAIN_H_

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include  "vos.h"
#include  "TafXsmsCtx.h"
#include  "cas_1x_control_main_nas_pif.h"
#include  "TafXsmsMsgProc.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#pragma pack(4)


/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define TAF_XSMS_BEAR_REPLY_SEQ_PRL    (63)
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
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

extern VOS_UINT32 TAF_XSMS_MtFsmMainProc(MsgBlock *pstMsg);

extern VOS_UINT32 TAF_XSMS_RcvIncomingCall_MtIdle
(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 TAF_XSMS_RcvDataInd_MtIdle
(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 TAF_XSMS_RcvCallConnCnf_MtWaitXccCallConnCnf
(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 TAF_XSMS_RcvCallConnTimeout_MtWaitXccCallConnCnf
(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 TAF_XSMS_RcvSoInd_MtWaitXccSoInd
(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 TAF_XSMS_RcvSoIndTimeout_MtWaitXccSoInd
(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 TAF_XSMS_RcvAnsCallCnf_MtWaitXccAnsCallCnf
(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 TAF_XSMS_RcvAnsCallCnfTimeout_MtWaitXccAnsCallCnf
(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 TAF_XSMS_RcvDschDataInd_MtWaitCasDschDataInd
(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 TAF_XSMS_RcvDschDataIndTimeout_MtWaitCasDschDataInd
(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 TAF_XSMS_RcvWriteUimCnf_MtWaitWriteUimCnf
(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 TAF_XSMS_RcvWriteUimCnfTimeout_MtWaitWriteUimCnf
(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 TAF_XSMS_RcvReadUimCnf_MtWaitReadUimCnf
(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 TAF_XSMS_RcvReadUimCnfTimeout_MtWaitReadUimCnf
(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 TAF_XSMS_RcvDschDataCnf_MtWaitCasDataCnf
(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 TAF_XSMS_RcvCschDataCnf_MtWaitCasDataCnf
(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 TAF_XSMS_RcvCasCnfTimeout_MtWaitCasDataCnf
(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 TAF_XSMS_RcvEndCallCnf_MtWaitEndCallCnf
(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 TAF_XSMS_RcvEndCallCnfTimeout_MtWaitEndCallCnf
(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_VOID TAF_XSMS_MtEndcallReq
(
    VOS_UINT8                           enEndReason
);

extern VOS_UINT32 TAF_XSMS_MtResend
(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 TAF_XSMS_RcvMtLinkAbort
(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_VOID TAF_XSMS_MtDealDataInd(TAF_XSMS_CAS_DATA_IND_MSG_STRU *pstDataInd);

extern VOS_VOID TAF_XSMS_MtDealPrl(VOS_VOID);

extern VOS_UINT32 TAF_XSMS_MtSendCasTlAck(
    TAF_XSMS_TL_CAUSE_CODE_ENUM8        enCauseCode,
    TAF_XSMS_TL_ERROR_CLASS_ENUM8       enErrorClass
);

extern VOS_VOID TAF_XSMS_MtDealTlAck
(
    TAF_XSMS_TL_CAUSE_CODE_ENUM8        enCauseCode,
    TAF_XSMS_TL_ERROR_CLASS_ENUM8       enErrorClass
);


extern VOS_UINT32 TAF_XSMS_MtDealSndCasDataReq(VOS_VOID);

extern VOS_UINT32 TAF_XSMS_SndCasDschDataReq(VOS_UINT8 ucMsgSeqNum, TAF_XSMS_DATA_BURST_MSG_STRU *pstDbm);

extern VOS_UINT32 TAF_XSMS_SndCasCschDataReq(VOS_UINT8 ucMsgSeqNum, VOS_UINT8 *paucData, TAF_XSMS_DATA_BURST_MSG_STRU *pstDbm);
extern VOS_UINT32 TAF_XSMS_MtAgpsSmsHandle(
    TAF_XSMS_MESSAGE_STRU              *pstMessage
);

extern VOS_VOID TAF_XSMS_MtDealCatptMsgProc(TAF_XSMS_CAS_DATA_IND_MSG_STRU *pstDataInd);

extern VOS_UINT32 TAF_XSMS_RcvMtLinkAbort_MtWaitCasCnf
(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 TAF_XSMS_EncodeTlAckInMtRec
(
    TAF_XSMS_TL_CAUSE_CODE_ENUM8        enCauseCode,
    TAF_XSMS_TL_ERROR_CLASS_ENUM8       enErrorClass
);

extern VOS_UINT32 TAF_XSMS_SndCasTlAckAccordingCurUeState
(
    VOS_VOID
);

#endif

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif
