

#ifndef __TAF_XCALL_TIMERMGMT_H__
#define __TAF_XCALL_TIMERMGMT_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "PsTypeDef.h"
#include "MnComm.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define             TI_TAF_XCALL_WAIT_CALL_REDIAL_PERIOD_LEN                (30000)  /* silently redial 总定时器时长 */
#define             TI_TAF_XCALL_WAIT_CALL_REDAIL_INTERVAL_LEN              (4000)   /* silently redial 间隔时长 */
#define             TAF_XCALL_TIMER_TICK                                     (10)

#define             TI_TAF_XCALL_START_AND_STOP_CONT_DTMF_INTERVAL_MIN      (360)   /* 同一对Stop Cont DTMF和Start的间隔时长，最小值,单位:ms */
#define             TI_TAF_XCALL_START_AND_STOP_CONT_DTMF_INTERVAL_MAX      (1000)  /* 同一对Stop Cont DTMF和Start的间隔时长，最大值,单位:ms */

/*****************************************************************************
  3 枚举定义
*****************************************************************************/


enum TAF_SPM_TIMER_STATUS_ENUM
{
    TAF_XCALL_TIMER_STATUS_STOP,              /* 定时器停止状态 */
    TAF_XCALL_TIMER_STATUS_RUNING,            /* 定时器运行状态 */
    TAF_XCALL_TIMER_STATUS_BUTT
};
typedef VOS_UINT8 TAF_XCALL_TIMER_STATUS_ENUM_UINT8;


enum TAF_XCALL_TIMER_ID_ENUM
{
    TI_TAF_XCALL_WAIT_CALL_REDIAL_PERIOD                             = MN_TIMER_CLASS_XCALL,/* silently redial 总定时器 */
    TI_TAF_XCALL_WAIT_CALL_REDAIL_INTERVAL,                                               /* silently redial 间隔定时器 */

    TI_TAF_XCALL_START_AND_STOP_CONT_DTMF_INTERVAL,                 /* Stop CONT DTMF命令和Start Cont DTMF命令之间的间隔，
                                                                        在收到Start Cont DTMF后启动，默认时长360ms，可通过nv配置 */
    TI_TAF_XCALL_TIMER_BUTT
};
typedef VOS_UINT32 TAF_XCALL_TIMER_ID_ENUM_UINT32;



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
    HTIMER                              hTimer;                                 /* 定时器的运行指针 */
    TAF_XCALL_TIMER_ID_ENUM_UINT32      enTimerId;                              /* 定时器的ID */
    TAF_XCALL_TIMER_STATUS_ENUM_UINT8   enTimerStatus;                          /* 定时器的运行状态,启动或停止 */
    VOS_UINT8                           ucCallId;                               /* 定时器关联call ID */
    VOS_UINT8                           aucReserve[2];                          /* 保留位 */
} TAF_XCALL_TIMER_CTX_STRU;
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;
    TAF_XCALL_TIMER_STATUS_ENUM_UINT8   enTimerStatus;      /* 定时器状态 */
    VOS_UINT8                           ucCallId;           /* 定时器关联call ID */
    VOS_UINT8                           aucReserve[2];      /* 保留位 */
    VOS_UINT32                          ulLen;              /* 定时器时长 */
}TAF_XCALL_TIMER_INFO_STRU;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 外部函数变量声明
*****************************************************************************/

/*****************************************************************************
  10 函数声明
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

VOS_VOID  TAF_XCALL_StartTimer(
    TAF_XCALL_TIMER_ID_ENUM_UINT32      enTimerId,
    VOS_UINT32                          ulLen,
    VOS_UINT8                           ucCallId
);

VOS_VOID  TAF_XCALL_StopTimer(
    TAF_XCALL_TIMER_ID_ENUM_UINT32      enTimerId,
    VOS_UINT8                           ucCallId
);

TAF_XCALL_TIMER_STATUS_ENUM_UINT8  TAF_XCALL_GetTimerStatus(
    TAF_XCALL_TIMER_ID_ENUM_UINT32      enTimerId,
    VOS_UINT8                           ucCallId
);

VOS_VOID  TAF_XCALL_InitAllTimers(
    TAF_XCALL_TIMER_CTX_STRU           *pstXcallTimerCtx
);

VOS_VOID  TAF_XCALL_SndOmTimerStatus(
    TAF_XCALL_TIMER_STATUS_ENUM_UINT8   enTimerStatus,
    TAF_XCALL_TIMER_ID_ENUM_UINT32      enTimerId,
    VOS_UINT32                          ulLen,
    VOS_UINT8                           ucCallId
);

VOS_VOID TAF_XCALL_GetRemainTimerLen(
    TAF_XCALL_TIMER_ID_ENUM_UINT32      enTimerId,
    VOS_UINT8                           ucCallId,
    VOS_UINT32                         *pulRemainTimeLen
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

#endif /* end of TafXCallTimerMgmt.h */


