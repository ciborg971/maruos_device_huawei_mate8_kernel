

#ifndef __TAF_X_CALL_MNTN_H__
#define __TAF_X_CALL_MNTN_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "PsCommonDef.h"
#include "PsLogdef.h"


#include "TafMntn.h"
#include "TafXCallCtx.h"

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


enum TAF_XCALL_MNTN_MSG_ID_ENUM
{
    ID_TAF_XCALL_MNTN_LOG_CALL_INFO_IND   = ID_TAF_MNTN_XCALL_BASE,             /*_H2ASN_MsgChoice  TAF_XCALL_MNTN_LOG_CALL_INFO_STRU */
    ID_TAF_XCALL_MNTN_LOG_SUPS_CMD_MGMT,                                        /*_H2ASN_MsgChoice  TAF_XCALL_MNTN_LOG_SUPS_CMD_MGMT_STRU*/
    /* Added by h00313353 for Iteration 17, 2015-8-7, begin */
    ID_TAF_XCALL_MNTN_LOG_EMC_CALL_REDIAL_PERIOD,
    /* Added by h00313353 for Iteration 17, 2015-8-7, end */
    ID_TAF_XCALL_MNTN_LOG_START_AND_STOP_CONT_DTMF_INTERVAL,                    /*_H2ASN_MsgChoice  TAF_XCALL_MNTN_LOG_START_AND_STOP_CONT_DTMF_INTERVAL_STRU*/
    ID_TAF_XCALL_MNTN_MSG_ID_BUTT
};
typedef VOS_UINT32 TAF_XCALL_MNTN_MSG_ID_ENUM_UINT32;


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

typedef struct
{
    VOS_MSG_HEADER                                                              /* 消息头 */    /* _H2ASN_Skip */
    TAF_XCALL_MNTN_MSG_ID_ENUM_UINT32   enMsgId;                                /* 消息ID */    /* _H2ASN_Skip */
    TAF_XCALL_CALL_ENTITY_STRU          astCallEntity[TAF_XCALL_CALL_ENTITY_MAX_NUM];
}TAF_XCALL_MNTN_LOG_CALL_INFO_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /* 消息头 */    /* _H2ASN_Skip */
    TAF_XCALL_MNTN_MSG_ID_ENUM_UINT32   enMsgId;                                /* 消息ID */    /* _H2ASN_Skip */
    TAF_XCALL_SUPS_CMD_MGMT_STRU        stSupsCmdMgmt;
}TAF_XCALL_MNTN_LOG_SUPS_CMD_MGMT_STRU;

/* Added by h00313353 for Iteration 17, 2015-8-7, begin */
/*****************************************************************************
 结构名    : TAF_XCALL_MNTN_LOG_CALL_REDIAL_PERIOD_STRU
 结构说明  : ID_TAF_XCALL_MNTN_LOG_SUPS_CMD_MGMT的消息结构
 1.日    期   : 2015年08月09日
   作    者   : h00313353
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* 消息头 */    /* _H2ASN_Skip */
    TAF_XCALL_MNTN_MSG_ID_ENUM_UINT32   enMsgId;                                /* 消息ID */    /* _H2ASN_Skip */
    VOS_UINT32                          ulEmcRedialPeriod;                      /* 紧急呼重拨定时器时长 */
} TAF_XCALL_MNTN_LOG_CALL_REDIAL_PERIOD_STRU;

/* Added by h00313353 for Iteration 17, 2015-8-7, end */

/*****************************************************************************
 结构名    : TAF_XCALL_MNTN_LOG_START_AND_STOP_CONT_DTMF_INTERVAL_STRU
 结构说明  : ID_TAF_XCALL_MNTN_LOG_START_AND_STOP_CONT_DTMF_INTERVAL的消息结构
 1.日    期   : 2015年08月18日
   作    者   : l00324781
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* 消息头 */    /* _H2ASN_Skip */
    TAF_XCALL_MNTN_MSG_ID_ENUM_UINT32   enMsgId;                                /* 消息ID */    /* _H2ASN_Skip */
    VOS_UINT32                          ulStartAndStopContDtmfInterval;         /* Stop Cont DTMF 和Start Cont DTMF消息发送间隔定时器时长 */
} TAF_XCALL_MNTN_LOG_START_AND_STOP_CONT_DTMF_INTERVAL_STRU;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

/*****************************************************************************
  H2ASN顶级消息结构定义
*****************************************************************************/
typedef struct
{
    TAF_XCALL_MNTN_MSG_ID_ENUM_UINT32   enMsgId;            /* _H2ASN_MsgChoice_Export TAF_XCALL_MNTN_MSG_ID_ENUM_UINT32 */

    VOS_UINT8                           aucMsgBlock[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          TAF_XCALL_MNTN_MSG_ID_ENUM_UINT32
    ****************************************************************************/
}TAF_XCALL_MNTN_MSG_DATA;
/*_H2ASN_Length UINT32*/


typedef struct
{
    VOS_MSG_HEADER
    TAF_XCALL_MNTN_MSG_DATA             stMsgData;
}TAF_XCALL_MNTN_MSG;


/*****************************************************************************
  10 函数声明
*****************************************************************************/

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_VOID TAF_XCALL_MNTN_LogCallInfo(VOS_VOID);
VOS_VOID TAF_XCALL_MNTN_LogSupsCmdMgmt(VOS_VOID);

/* Added by h00313353 for Iteration 17, 2015-8-7, begin */
VOS_VOID TAF_XCALL_MNTN_LogEmcCallRedialPeriod(VOS_VOID);
/* Added by h00313353 for Iteration 17, 2015-8-7, end */

VOS_VOID TAF_XCALL_MNTN_LogStartAndStopContDtmfInterval(VOS_VOID);

/* Deleted by wx270776 for OM融合, 2015-6-28, begin */
/* Deleted by wx270776 for OM融合, 2015-6-28, end */
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

#endif /* end of TafXCallMntn.h */
