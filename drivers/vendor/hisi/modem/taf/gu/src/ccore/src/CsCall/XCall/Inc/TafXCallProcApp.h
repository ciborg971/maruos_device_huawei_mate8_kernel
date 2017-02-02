

#ifndef __TAF_X_CALL_PROC_APP_H__
#define __TAF_X_CALL_PROC_APP_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "MnCallApi.h"
#include "TafXCallCtx.h"
#include "xcc_xcall_pif.h"
#include "hi_list.h"

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

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_VOID TAF_XCALL_RcvAppCallOrigReq(VOS_VOID *pMsg);

VOS_VOID TAF_XCALL_RcvAppSupsCmdReq(VOS_VOID *pMsg);

#if 0
VOS_VOID TAF_XCALL_RcvAppSendFlashReq(VOS_VOID *pMsg);
#endif

VOS_VOID TAF_XCALL_ProcCallSupsCmdRelHoldOrUdubReq(
    MN_CALL_APP_REQ_MSG_STRU           *pstAppCallSupsReq
);

VOS_VOID TAF_XCALL_ProcCallSupsCmdRelActAcptOthReq(
    MN_CALL_APP_REQ_MSG_STRU           *pstAppCallSupsReq
);

VOS_VOID TAF_XCALL_ProcCallSupsCmdRelCallXReq(
    MN_CALL_APP_REQ_MSG_STRU           *pstAppCallSupsReq
);

VOS_VOID TAF_XCALL_ProcCallSupsCmdRelAllCallReq(
    MN_CALL_APP_REQ_MSG_STRU           *pstAppCallSupsReq
);

VOS_VOID TAF_XCALL_ProcCallSupsCmdHoldActAcptOthReq(
    MN_CALL_APP_REQ_MSG_STRU           *pstAppCallSupsReq
);

/* Added by f279542 for CDMA 1X Iteration 4, 2014-11-12, begin */

extern VOS_VOID TAF_XCALL_RcvAppSendBurstDTMFReq(VOS_VOID *pMsg);

extern VOS_VOID TAF_XCALL_RcvAppSendFlashReq(VOS_VOID *pMsg);

/* Deleted by l00324781 for CDMA Iteration 16, 2015-7-29, begin */
/* Buffer操作函数从XCallProcApp挪到XCallCtx.c中 */
/* Deleted by l00324781 for CDMA Iteration 16, 2015-7-29, end */

/* Added by f279542 for CDMA 1X Iteration 4, 2014-11-12, end */

VOS_VOID TAF_XCALL_RcvAgentGetCallInfoReq(VOS_VOID *pMsg);
VOS_VOID TAF_XCALL_RcvAppGetCallInfoReq(VOS_VOID *pMsg);
VOS_VOID TAF_XCALL_RcvAppXlemaReq(VOS_VOID *pMsg);


VOS_VOID TAF_XCALL_RcvAppCustomDialReq(VOS_VOID *pMsg);

/* Added by y00314741 for  CDMA Iteration 17, 2015-7-14, begin */
VOS_UINT32 TAF_XCALL_GetRedialPeriodTimerLen(
    VOS_UINT8                           ucCallId
);
/* Added by y00314741 for  CDMA Iteration 17, 2015-7-14, end */


/* Added by l00324781 for CDMA Iteration 16, 2015-7-24, begin */
VOS_VOID TAF_XCALL_RcvAppSendContDTMFReq(VOS_VOID *pMsg);

/* Added by l00324781 for CDMA Iteration 16, 2015-7-24, end */

/* Added by y00307564 for CDMA Iteration 16 2015-7-25 begin */
VOS_VOID TAF_XCALL_ReplaceFlashPlusWithDigit(
    VOS_UINT8                           ucSrcDigitNum,
    VOS_UINT8                          *pucSrcDigit,
    VOS_UINT8                          *pucDstDigitNum,
    VOS_UINT8                          *pucDstDigit
);
/* Added by y00307564 for CDMA Iteration 16 2015-7-25 end */

VOS_VOID TAF_XCALL_RcvAtCclprGetReq(VOS_VOID *pstMsg);
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

#endif /* end of TafXCallProcApp.h */

