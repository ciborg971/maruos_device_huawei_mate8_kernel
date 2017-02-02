

#ifndef  _CPU_VIEW_ADAPTER_H
#define  _CPU_VIEW_ADAPTER_H

/******************************************************************************
   1 ͷ�ļ�����
******************************************************************************/
#include "PsCommonDef.h"
#include <stdio.h>
#include <string.h>

/******************************************************************************
                                vxWorks
******************************************************************************/
#if (VOS_VXWORKS == VOS_OS_VER)
#include <vxWorks.h>
#include <taskLib.h>

/******************************************************************************
   1 �궨��
******************************************************************************/
typedef WIND_TCB    CPUVIEW_TCB;

extern STATUS taskSwitchHookAdd(FUNCPTR switchHook);
extern STATUS taskSwitchHookDelete(FUNCPTR switchHook);

#define CPU_VIEW_ADD_TASK_SWITCH_HOOK(switchHook)       taskSwitchHookAdd(switchHook)
#define CPU_VIEW_DEL_TASK_SWITCH_HOOK(switchHook)       taskSwitchHookDelete(switchHook)

#define CPU_VIEW_TASK_DELAY(ticks)                      taskDelay(ticks)
#define CPU_VIEW_GET_TASK_PC(pTcb)                      (pTcb->regs.pc)
#define CPU_VIEW_LOG_PRINT(pstr)       \
        logMsg(pstr, 0, 0, 0, 0, 0, 0)
#define CPU_VIEW_LOG_PRINT1(pstr, param1)       \
        logMsg(pstr, param1, 0, 0, 0, 0, 0)
#define CPU_VIEW_LOG_PRINT2(pstr, param1, param2)       \
        logMsg(pstr, param1, param2, 0, 0, 0, 0)
#define CPU_VIEW_LOG_PRINT6(pstr, param1, param2, param3, param4, param5, param6)       \
        logMsg(pstr, param1, param2, param3, param4, param5, param6)

/******************************************************************************
                                RTOS
******************************************************************************/
#elif ((VOS_RTOSCK == VOS_OS_VER) || (VOS_NUCLEUS == VOS_OS_VER) || (VOS_WIN32 == VOS_OS_VER))
#include <sre_task.h>
#include <sre_hook.h>

/******************************************************************************
   1 �궨��
******************************************************************************/
typedef unsigned long  CPUVIEW_TCB;

#define CPU_VIEW_ADD_TASK_SWITCH_HOOK(switchHook)       SRE_TaskSwitchHookAdd(switchHook)
#define CPU_VIEW_DEL_TASK_SWITCH_HOOK(switchHook)       SRE_TaskSwitchHookDelete(switchHook)

#define CPU_VIEW_TASK_DELAY(ticks)                      SRE_TaskDelay(ticks)
#define CPU_VIEW_GET_TASK_PC(pTcb)                      (pTcb)
#define CPU_VIEW_LOG_PRINT(pstr)       \
        (VOS_VOID)LogPrint(pstr)
#define CPU_VIEW_LOG_PRINT1(pstr, param1)       \
        (VOS_VOID)LogPrint1(pstr, param1)
#define CPU_VIEW_LOG_PRINT2(pstr, param1, param2)       \
        (VOS_VOID)LogPrint2(pstr, param1, param2)
#define CPU_VIEW_LOG_PRINT6(pstr, param1, param2, param3, param4, param5, param6)       \
        (VOS_VOID)LogPrint6(pstr, param1, param2, param3, param4, param5, param6)
#endif

VOS_UINT16 OS_GetTaskIdList(int iTaskIdList[], int iTaskMaxNum);
char * OS_GetTaskName(VOS_UINT32 ulTaskId);

#endif  /* _CPU_VIEW_ADAPTER_H */


