

#ifndef _TAF_XPDS_AND_AT_H_
#define _TAF_XPDS_AND_AT_H_

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "AtMnInterface.h"
#include "AtXpdsInterface.h"
#include "TafXpdsEncode.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/


/*****************************************************************************
  3 枚举定义
*****************************************************************************/


/*****************************************************************************
  4 全局变量声明
*****************************************************************************/



/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
VOS_VOID TAF_XPDS_SndAtMsg(
    AT_APPCTRL_STRU                    *pAppCtrl,
    VOS_UINT32                          ulMsgId,
    VOS_UINT32                          ulLen,
    VOS_UINT8                          *pData
);

VOS_VOID TAF_XPDS_SndAtMsgNoData(
    AT_APPCTRL_STRU                    *pAppCtrl,
    VOS_UINT32                          ulMsgId
);

VOS_VOID TAF_XPDS_SndAtApOpenCagpsDataCall(VOS_VOID);

VOS_VOID TAF_XPDS_SndAtApCloseCagpsDataCall(VOS_VOID);

VOS_VOID TAF_XPDS_SndAtApOpenSocketReq
(
    AT_XPDS_SERVER_MODE_ENUM_UINT32     enServerMode,
    VOS_UINT32                          ulIpAddr,
    VOS_UINT32                          ulPortNum
);

VOS_VOID TAF_XPDS_SndAtApCloseSocketReq
(
    AT_XPDS_SERVER_MODE_ENUM_UINT32     enServerMode,
    VOS_UINT32                          ulIpAddr,
    VOS_UINT32                          ulPortNum
);

VOS_VOID TAF_XPDS_SndAtGpsTimeSyncInfo(
    CAS_XPDS_TIME_SYNC_IND_STRU        *pstRcvSyncTime
);

VOS_VOID TAF_XPDS_SndAtApMpcStartPosReq
(
    VOS_VOID
);

VOS_VOID TAF_XPDS_SndAtApMpcPosReportReq
(
    VOS_VOID
);

VOS_VOID TAF_XPDS_SndAtApPdeSessionEndMsg(VOS_VOID);

VOS_VOID TAF_XPDS_SndAtApPdeRejectRsp(
    TAF_XPDS_REVLINK_RSP_REJECT_STRU                       *pstRejInfo
);

VOS_VOID TAF_XPDS_FillMpcStartPosReq
(
    TAF_XPDS_MPC_START_POS_REQ_STRU    *pstStartPosReq
);

VOS_VOID TAF_XPDS_FillMpcPosReportReq
(
    TAF_XPDS_MPC_POS_REPORT_STRU       *pstPosReportReq
);

VOS_VOID TAF_XPDS_SndApMsg
(
    AT_XPDS_SERVER_MODE_ENUM_UINT32     enServerMode,
    const VOS_UINT8                          *pucData,
    VOS_UINT32                          ulLen
);

VOS_VOID TAF_XPDS_SndAtGpsAbortPosInd
(
    XPDS_AT_ABORT_POS_REASON_ENUM_UINT16                    enAbortReason
);

VOS_VOID TAF_XPDS_SndAtGpsStopCnf(VOS_VOID);

VOS_VOID TAF_XPDS_SndAtGpsNiSessionInd(
    TAF_XPDS_RCV_XSMS_POS_REQ_STRU     *pstXsmsMsg
);

VOS_VOID TAF_XPDS_SndAtGpsCancelNiSession(VOS_VOID);

VOS_VOID TAF_XPDS_SndAtGpsAcqAssistData(VOS_VOID);

VOS_VOID TAF_XPDS_SndAtGpsIonInfo(VOS_VOID);

VOS_VOID TAF_XPDS_SndAtGpsEphInfo(VOS_VOID);

VOS_VOID TAF_XPDS_SndAtGpsAlmInfo(VOS_VOID);

VOS_VOID TAF_XPDS_SndAtGpsPositionInfo(VOS_VOID);

VOS_UINT32 TAF_XPDS_CalcTimeInWeek(VOS_UINT32 ulRefTime);

VOS_UINT64 TAF_XPDS_CalcAbsTime(VOS_UINT32 ulRefTime);

VOS_VOID TAF_XPDS_SndAtGpsCpNiStop(
    VOS_VOID
);

VOS_VOID TAF_XPDS_SndAtGpsCpNiStart(
    VOS_VOID
);

VOS_VOID TAF_XPDS_SetPosReportLocInfo(
    TAF_XPDS_MPC_POS_REPORT_STRU       *pstPosReportReq
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

#endif /* end of TafXpdsSndAt.h */

