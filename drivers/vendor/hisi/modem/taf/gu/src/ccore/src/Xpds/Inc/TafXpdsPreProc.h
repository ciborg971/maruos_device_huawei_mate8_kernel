

#ifndef _TAF_XPDS_PRE_PROC_H_
#define _TAF_XPDS_PRE_PROC_H_

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "AtXpdsInterface.h"
#include "TafXpdsCtx.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define TAF_XPDS_ATDOWN_MAX_LEN            (2*1024)


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


typedef struct
{
    VOS_UINT32                          ulCurIndex;
    VOS_UINT32                          ulTotalNum;
    VOS_UINT32                          ulTotalLen;
    VOS_UINT8                          *pucData;
}TAF_XPDS_DOWN_DATA_CTRL_STRU;


/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvAtGpsStartReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_XPDS_RcvAtGpsCfgMpcAddrReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_XPDS_RcvAtGpsCfgPdeAddrReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_XPDS_RcvAtGpsCfgPositionModeReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_XPDS_RcvAtGpsQryRefLocInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_XPDS_RcvAtGpsQryTimeInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_XPDS_RcvAtApServerBindStatusInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_XPDS_RcvAtGpsStopReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_XPDS_RcvCasTimeSyncInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_XPDS_RcvCasRefLocInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_XPDS_CheckForwardData_PreProc(
    AT_XPDS_AP_FORWARD_DATA_IND_STRU   *pstDownDataInd
);

VOS_UINT32 TAF_XPDS_RcvApForwardDataInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_VOID TAF_XPDS_ProcForwardMpcMsg_PreProc(
    VOS_UINT8                          *pucData,
    VOS_UINT32                          ulDataLen
);

VOS_VOID TAF_XPDS_ProcForwardPdeMsg_PreProc(
    VOS_UINT8                          *pucMsgBuf,
    VOS_UINT32                          ulTotLength
);

VOS_VOID TAF_XPDS_ProcEphData_PreProc(VOS_VOID);

VOS_VOID TAF_XPDS_ProcAlmData_PreProc(VOS_VOID);

VOS_UINT32 TAF_XPDS_RcvXsmsRcvInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  TAF_XPDS_ProcXsmsMsg_PreProc(
    TAF_XPDS_RCV_XSMS_MSG_STRU         *pstXsmsMsg
);
VOS_UINT32  TAF_XPDS_XsmsNiPosReqHandle_PreProc(
    TAF_XPDS_RCV_XSMS_POS_REQ_STRU     *pstXsmsMsg
);
VOS_UINT32  TAF_XPDS_XsmsCancelPosHandle_PreProc(
    TAF_XPDS_RCV_CANCEL_NI_TRACK_STRU  *pstXsmsMsg
);
VOS_UINT32  TAF_XPDS_XsmsRefreshMrSessionHandle_PreProc(
    TAF_XPDS_RCV_REFRESH_MR_TRACK_STRU *pstXsmsMsg
);

VOS_VOID TAF_XPDS_RcvAtMpcStartPosRespHandle_PreProc(
    VOS_UINT32                          ulDataLen,
    VOS_UINT8                          *pucData
);

VOS_VOID TAF_XPDS_RcvAtMpcPosReportRspHandle_PreProc(
    VOS_UINT32                          ulDataLen,
    VOS_UINT8                          *pucData
);

VOS_UINT32 TAF_XPDS_RcvTiXpdsIs801SessionExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_XPDS_RcvTiWaitGpsAnswerNiReqExpire_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_XPDS_RcvCasDschDataInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_XPDS_RcvPpmTimerExpire_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_XPDS_RcvCasRefLocCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


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
