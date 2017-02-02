

#ifndef __TAF_X_CALL_PROC_XCC_H__
#define __TAF_X_CALL_PROC_XCC_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "VcCallInterface.h"
#include "TafXCallCtx.h"
#include "xcc_xcall_pif.h"

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
VOS_VOID TAF_XCALL_RcvXccCallOrigCnf(VOS_VOID *pMsg);
VOS_VOID TAF_XCALL_RcvXccCallHangUpCnf(VOS_VOID *pMsg);
VOS_VOID TAF_XCALL_RcvXccCallDiscInd(VOS_VOID *pMsg);
VOS_VOID TAF_XCALL_RcvXccCallIncomingInd(VOS_VOID *pMsg);
VOS_VOID TAF_XCALL_RcvXccCallAnswerCnf(VOS_VOID *pMsg);
VOS_VOID TAF_XCALL_RcvXccCallConnectInd(VOS_VOID *pMsg);
#if 0
VOS_VOID TAF_XCALL_RcvXccSendFlashCnf(VOS_VOID *pMsg);
VOS_VOID TAF_XCALL_RcvXccInfoRecInd(VOS_VOID *pMsg);
#endif

VOS_VOID TAF_XCALL_RcvXccCodecOpenInd(VOS_VOID *pMsg);

VOS_VOID TAF_XCALL_RcvXccCodecCloseInd(VOS_VOID *pMsg);

VOS_VOID TAF_XCALL_RcvXccCodecChangedInd(VOS_VOID *pMsg);

VOS_VOID TAF_XCALL_RcvXccSoCtrlMsgInd(VOS_VOID *pMsg);

VOS_VOID TAF_XCALL_RcvXccSoCtrlOrderInd(VOS_VOID *pMsg);

VOS_UINT32 TAF_XCALL_MapSoToCodecType(
    TAF_CDMA_SO_TYPE_ENUM_UINT16        enSo,
    CALL_VC_CODEC_TYPE_ENUM_U8         *penCodecType
);

TAF_XCALL_SO_TYPE_ENUM_UINT16 TAF_XCALL_ConvertXccSoToXcallSo(
    TAF_CDMA_SO_TYPE_ENUM_UINT16        enXccSo
);

/* Added by f279542 for CDMA 1X Iteration 4, 2014-11-12, begin */
extern VOS_VOID TAF_XCALL_RcvXccSendBurstDTMFCnf(VOS_VOID *pMsg);

extern VOS_VOID TAF_XCALL_RcvXccSendFlashCnf(VOS_VOID *pMsg);

extern VOS_VOID TAF_XCALL_RscvXccInfoRecInd(VOS_VOID *pMsg);

extern VOS_VOID TAF_XCALL_RcvXccInfoRecInd(VOS_VOID *pMsg);
/* Added by f279542 for CDMA 1X Iteration 4, 2014-11-12, end */

VOS_UINT32 TAF_XCALL_IsNeedSilentRedial(
    TAF_XCC_CAUSE_ENUM_UINT32           enCause
);
VOS_UINT32 TAF_XCALL_IsNeedRedialSystemAcquire(
    TAF_XCC_CAUSE_ENUM_UINT32           enCause
);


VOS_VOID TAF_XCALL_RcvXccNdssResultInd(VOS_VOID *pMsg);

/* Added by l00324781 for CDMA Iteration 16, 2015-7-24, begin */
VOS_VOID TAF_XCALL_RcvXccSendContDTMFCnf(VOS_VOID *pMsg);
/* Added by l00324781 for CDMA Iteration 16, 2015-7-24, end */
VOS_VOID TAF_XCALL_RcvXccBurstDtmfInd(VOS_VOID *pMsg);
/* Added by k902809 for CDMA Iteration 16, 2015-7-25, begin */
VOS_VOID TAF_XCALL_RcvXccContDtmfInd(VOS_VOID *pMsg);
/* Added by k902809 for CDMA Iteration 16, 2015-7-25, end */
VOS_VOID TAF_XCALL_SavePiOfCallingPartyNum(
    XCC_XCALL_INFO_REC_IND_STRU        *pstInfoRecInd
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

#endif /* end of TafXCallProcXcc.h */

