
#ifndef __MNMSGTIMERPROC_H__
#define __MNMSGTIMERPROC_H__


/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "MnComm.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  1 ���Ͷ���
*****************************************************************************/
#define     MN_MSG_TIMER_TICK               10


/*****************************************************************************
  2 �ӿں�������
*****************************************************************************/

VOS_VOID  MN_MSG_InitAllTimers(VOS_VOID);


VOS_VOID  MN_MSG_StartTimer(
    MN_MSG_TIMER_ID_ENUM_U32            enTimerId,
    VOS_UINT32                          ulParam
);


VOS_VOID MN_MSG_StopTimer(
    MN_MSG_TIMER_ID_ENUM_U32            enTimerId
);

VOS_VOID  MN_MSG_StopAllRunningTimer(VOS_VOID);


VOS_UINT32  MN_MSG_IsTimerStarting(
    MN_MSG_TIMER_ID_ENUM_U32            enTimerId
);


VOS_VOID MN_MSG_UpdateRetryPeriod(
    MN_MSG_TIMER_ID_ENUM_U32            enTimerId,
    VOS_UINT32                          ulTimerLen
);


VOS_UINT32  MN_MSG_GetTimerRemainTime(
    MN_MSG_TIMER_ID_ENUM_U32            enTimerId
);

VOS_VOID  MN_MSG_UpdateListInfo(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    VOS_UINT32                          ulLeftReportNum,
    const MN_MSG_LIST_PARM_STRU         *pstList
);

/* Modified by wx270776 for OM�ں�, 2015-6-28, begin */
extern VOS_VOID DIAG_TraceReport(VOS_VOID *pMsg);
/* Modified by wx270776 for OM�ں�, 2015-6-28, end */

extern VOS_VOID TAF_MSG_ListLeftMsg(VOS_VOID);

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* __MNMSGTIMERPROC_H__ */

