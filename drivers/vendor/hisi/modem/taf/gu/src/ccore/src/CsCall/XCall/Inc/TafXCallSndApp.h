

#ifndef __TAF_X_CALL_SND_APP_H__
#define __TAF_X_CALL_SND_APP_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "MnCallApi.h"
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
VOS_VOID TAF_XCALL_SndCsEvtToAt(
    VOS_UINT32                          ulEvtId,
    VOS_UINT16                          usClientId,
    VOS_UINT16                          usLength,
    VOS_VOID                           *pData
);

VOS_VOID TAF_XCALL_SndCsEvtToStk(
    VOS_UINT32                          ulEvtId,
    VOS_UINT32                          ulModuleId,
    MN_CALL_INFO_STRU                  *pstCallInfo
);

VOS_VOID TAF_XCALL_SndCallOrigCnf(
    TAF_CS_CAUSE_ENUM_UINT32            enCause,
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientid,
    MN_CALL_TYPE_ENUM_U8                enCallType
);


VOS_VOID TAF_XCALL_SndSupsCmdCnf(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucCallId,
    TAF_CS_CAUSE_ENUM_UINT32            enCause
);

VOS_VOID TAF_XCALL_SndSupsResult(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucCallId,
    MN_CALL_SS_RESULT_ENUM_U8           enSsResult
);

VOS_VOID TAF_XCALL_SndCallIncomingInd(
    VOS_UINT8                           ucCallId
);

VOS_VOID TAF_XCALL_SndCallOrigInd(
    VOS_UINT8                           ucCallId
);

VOS_VOID TAF_XCALL_SndCallConnectInd(
    VOS_UINT8                           ucCallId
);

VOS_VOID TAF_XCALL_SndCallReleaseInd(
    VOS_UINT8                           ucCallId
);

VOS_VOID TAF_XCALL_SndCallAllReleaseInd(
    VOS_UINT32                          ulModuleId
);

/* Modified by y00307564 for 1X SS Project, 2014-11-10, begin */
extern VOS_VOID TAF_XCALL_SndCalledNumInfoInd(
    XCC_XCALL_INFO_REC_IND_STRU        *pstInfoRecInd
);

extern VOS_VOID TAF_XCALL_SndCallingPratNumInfoInd(
    XCC_XCALL_INFO_REC_IND_STRU        *pstInfoRecInd
);

extern VOS_VOID TAF_XCALL_SndConnNumInfoInd(
    XCC_XCALL_INFO_REC_IND_STRU        *pstInfoRecInd
);

extern VOS_VOID TAF_XCALL_SndRedirNumInfoInd(
    XCC_XCALL_INFO_REC_IND_STRU        *pstInfoRecInd
);

extern VOS_VOID TAF_XCALL_SndDisplayInfoInd(
    XCC_XCALL_INFO_REC_IND_STRU        *pstInfoRecInd
);

extern VOS_VOID TAF_XCALL_SndExtDisplayInfoInd(
    XCC_XCALL_INFO_REC_IND_STRU        *pstInfoRecInd
);

extern VOS_VOID TAF_XCALL_SndLineCtrlInfoInd(
    XCC_XCALL_INFO_REC_IND_STRU        *pstInfoRecInd
);

extern VOS_VOID TAF_XCALL_SndSignalInfoInd(
    XCC_XCALL_INFO_REC_IND_STRU        *pstInfoRecInd
);

extern VOS_VOID TAF_XCALL_SndCCWACInfoInd(
    XCC_XCALL_INFO_REC_IND_STRU        *pstInfoRecInd
);

extern VOS_VOID TAF_XCALL_SndCallingNumSignalInfoInd(
    XCC_XCALL_INFO_REC_IND_STRU        *pstInfoRecInd
);
/* Modified by y00307564 for 1X SS Project, 2014-11-10, end */

/* Added by f279542 for CDMA 1X Iteration 4, 2014-11-12, begin */
extern VOS_VOID TAF_XCALL_SndFlashRslt(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucResult
);

extern VOS_VOID TAF_XCALL_SndBurstDTMFRslt(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucResult
);

extern VOS_VOID TAF_XCALL_SndBurstDTMFCnf(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucResult,
    VOS_UINT8                           ucCallId
);
/* Added by f279542 for CDMA 1X Iteration 4, 2014-11-12, end */

VOS_VOID TAF_XCALL_SndXlemaCnf(
    MN_CALL_ECC_NUM_INFO_STRU          *pstEccNumInfo
);

/* Added by l00324781 for CDMA Iteration 16, 2015-7-24, begin */
extern VOS_VOID TAF_XCALL_SndContDTMFCnf(
    VOS_UINT16                                  usClientId,
    VOS_UINT8                                   ucOpId,
    TAF_CALL_SEND_CONT_DTMF_CNF_RESULT_ENUM_U8  enResult,
    VOS_UINT8                                   ucCallId
);

extern VOS_VOID TAF_XCALL_SndContDTMFRslt(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucResult
);
/* Added by l00324781 for CDMA Iteration 16, 2015-7-24, end */



VOS_VOID TAF_XCALL_SndBurstDTMFInd(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    XCC_XCALL_BURST_DTMF_IND_STRU      *pstBurstDtmfInd
);
/* Added by k902809 for CDMA Iteration 16, 2015-7-25, begin */
VOS_VOID TAF_XCALL_SndContDTMFInd(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    XCC_XCALL_CONT_DTMF_IND_STRU       *pstContDtmfInd
);
/* Added by k902809 for CDMA Iteration 16, 2015-7-25, end */
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

#endif /* end of TafXCallSndApp.h */

