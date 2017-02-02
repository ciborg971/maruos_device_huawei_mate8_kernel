/*****************************************************************************/
/*                                                                           */
/*                Copyright 1999 - 2003, Huawei Tech. Co., Ltd.              */
/*                           ALL RIGHTS RESERVED                             */
/*                                                                           */
/* FileName: v_task.c                                                        */
/*                                                                           */
/* Author: Yang Xiangqian                                                    */
/*                                                                           */
/* Version: 1.0                                                              */
/*                                                                           */
/* Date: 2006-10                                                             */
/*                                                                           */
/* Description: implement task                                               */
/*                                                                           */
/* Others:                                                                   */
/*                                                                           */
/* History:                                                                  */
/* 1. Date:                                                                  */
/*    Author:                                                                */
/*    Modification: Create this file                                         */
/*                                                                           */
/* 2. Date: 2006-10                                                          */
/*    Author: Xu Cheng                                                       */
/*    Modification: Standardize code                                         */
/*                                                                           */
/*****************************************************************************/

#include "stdlib.h"
#include "stdio.h"
#include "vos_config.h"
#include "v_typdef.h"
#include "v_task.h"
#include "v_IO.h"
#include "v_int.h"
#include "vos_Id.h"
#include "v_sem.h"
#include "v_IO.h"
#include "v_timer.h"

#if (VOS_RTOSCK == VOS_OS_VER)
#include "sre_task.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif /* __cpluscplus */
#endif /* __cpluscplus */


#if (VOS_RTOSCK == VOS_OS_VER)


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_V_RTOSCK_TASK_C


typedef struct
{
    int                 Flag;
    int                 Tid;/* task ID */
    VOS_TASK_ENTRY_TYPE Function;/* the entry of task */
    VOS_UINT32          Priority;
    VOS_UINT32          StackSize;
    VOS_UINT32          Args[VOS_TARG_NUM];/* the argument of the entry */
    VOS_UINT32          ulRtosckTID; /* maped RTOSck PID */
    VOS_CHAR            Name[VOS_MAX_LENGTH_TASK_NAME];
    VOS_UINT32          ulEventIsCreate;/* event create or not */
    VOS_UINT32          ulEvents;/* current event */
    VOS_UINT32          ulExpects;/* expected event */
    VOS_UINT32          ulReceives;/* have been received event */
    VOS_UINT32          ulFlags;/* event mode */
    VOS_UINT32          ulFid;/* belong to a FID or not */
} VOS_TASK_CONTROL_BLOCK;

/* the number of task's control block */
VOS_UINT32              vos_TaskCtrlBlkNumber;

/* the start address of task's control block */
VOS_TASK_CONTROL_BLOCK *vos_TaskCtrlBlk;

#define VOS_TASK_CTRL_BUF_SIZE (sizeof(VOS_TASK_CONTROL_BLOCK)*VOS_MAX_TASK_NUMBER)

VOS_UINT32 g_acVosTaskCtrlBuf[VOS_TASK_CTRL_BUF_SIZE/4];

#if (VOS_DEBUG == VOS_CHECK_TASKLOCK)

/* VOS ֧�ֵ����������Ƕ����Ŀ */
#define VOS_NESTED_TASKLOCK_MAX_NUM     (128)

/* VOS ͳ�Ƶ�������ʱ���� ��λslice 30us */
#define VOS_TASKLOCK_MAX_INTERVAL       (900)

/* Ƕ����Ϣ��¼ */
typedef struct
{
    VOS_UINT32                          ulSuffix; /* �����±� */
    VOS_NESTED_LOCK_INFO_STRU           astNestedInfo[VOS_NESTED_TASKLOCK_MAX_NUM];
}VOS_NESTED_TASKLOCK_STRU;

VOS_NESTED_TASKLOCK_STRU g_stVosTaskLockNestedInfo = {0};

#endif

/*****************************************************************************
 Function   : VOS_TaskCtrlBlkInit
 Description: Init task's control block
 Input      : ulTaskCtrlBlkNumber -- number
 Return     : None.
 Other      :
 *****************************************************************************/
VOS_VOID VOS_TaskCtrlBlkInit(VOS_VOID)
{
    int i;

    vos_TaskCtrlBlkNumber = VOS_MAX_TASK_NUMBER;

    vos_TaskCtrlBlk = (VOS_TASK_CONTROL_BLOCK*)g_acVosTaskCtrlBuf;

    for(i=0; i<(int)vos_TaskCtrlBlkNumber; i++)
    {
        vos_TaskCtrlBlk[i].Flag       = VOS_TASK_CTRL_BLK_IDLE;
        vos_TaskCtrlBlk[i].Tid        = i;
        vos_TaskCtrlBlk[i].ulRtosckTID     = (VOS_UINT32)VOS_TASK_CTRL_BLK_VXWORKS_TASKID_NULL;
        vos_TaskCtrlBlk[i].ulEventIsCreate = VOS_FALSE;
        vos_TaskCtrlBlk[i].ulEvents   = 0;
        vos_TaskCtrlBlk[i].ulExpects  = 0;
        vos_TaskCtrlBlk[i].ulReceives = 0;
        vos_TaskCtrlBlk[i].ulFlags    = VOS_EVENT_NOWAIT;
        vos_TaskCtrlBlk[i].ulFid      = 0xffffffff;
    }
    return;
}

/*****************************************************************************
 Function   : VOS_TaskCtrlBlkGet
 Description: allocate a block
 Input      : void
            : void
 Return     : VOS_OK on success or errno on failure.
 Other      :
 *****************************************************************************/
VOS_UINT32 VOS_TaskCtrlBlkGet(VOS_VOID)
{
    VOS_UINT32       i;
    int              intLockLevel;

    intLockLevel = VOS_SplIMP();

    for(i=0; i<vos_TaskCtrlBlkNumber; i++)
    {
        if(vos_TaskCtrlBlk[i].Flag == VOS_TASK_CTRL_BLK_IDLE)
        {
            vos_TaskCtrlBlk[i].Flag = VOS_TASK_CTRL_BLK_BUSY;

            break;
        }
    }

    VOS_Splx(intLockLevel);

    if( i < vos_TaskCtrlBlkNumber)
    {
        return i;
    }
    else
    {
        /*lint -e534*/
        Print("# allocate task control block fail.\r\n");
        /*lint +e534*/

        return(VOS_TASK_CTRL_BLK_NULL);
    }
}

/*****************************************************************************
 Function   : VOS_TaskCtrlBlkFree
 Description: free a block
 Input      : Tid -- task ID
 Return     : VOS_OK on success or errno on failure.
 Other      :
 *****************************************************************************/
VOS_UINT32 VOS_TaskCtrlBlkFree(VOS_UINT32 Tid)
{
    int              intLockLevel;

    if( Tid < vos_TaskCtrlBlkNumber )
    {
        if(vos_TaskCtrlBlk[Tid].Flag == VOS_TASK_CTRL_BLK_IDLE)
        {
            /*lint -e534*/
            Print("# VOS_TaskCtrlBlkFree free Idle Task.\r\n");
            /*lint +e534*/

            return VOS_ERR;
        }
        else
        {
            intLockLevel = VOS_SplIMP();
            vos_TaskCtrlBlk[Tid].Flag = VOS_TASK_CTRL_BLK_IDLE;
            VOS_Splx(intLockLevel);

            return VOS_OK;
        }
    }
    else
    {
        /*lint -e534*/
        Print("# VOS_TaskCtrlBlkFree Error.\r\n");
        /*lint +e534*/

        return VOS_ERR;
    }
}

/*****************************************************************************
 Function   : VOS_CreateTask
 Description: create task with default task mode:
              VOS_T_PREEMPT | VOS_T_NO_TSLICE | VOS_T_SUPV
 Input      : puchName              -- name identify task
              pfnFunc               -- task entry function
              ulPriority            -- task priority
              ulStackSize           -- task stack size
              aulArgs[VOS_TARG_NUM] -- arguments for task
 Output     : pulTaskID             -- task id allocated by dopra
 Return     : result of VOS_CreateTaskEx
 *****************************************************************************/
VOS_UINT32 VOS_CreateTask( VOS_CHAR * puchName,
                           VOS_UINT32 * pulTaskID,
                           VOS_TASK_ENTRY_TYPE pfnFunc,
                           VOS_UINT32 ulPriority,
                           VOS_UINT32 ulStackSize,
                           VOS_UINT32 aulArgs[VOS_TARG_NUM] )
{
    int                                 i;
    VOS_UINT32                          ulTid;
    VOS_UINT32                          ulRTOSckTid;
    VOS_CHAR                            default_name[8] = {0};
    VOS_UCHAR                           value;
    VOS_UINT32                          ulResult;
    TSK_INIT_PARAM_S                    stTaskPara;

    ulTid = VOS_TaskCtrlBlkGet();
    if( ulTid == (VOS_UINT32)VOS_TASK_CTRL_BLK_NULL )
    {
        /*lint -e534*/
        VOS_SetErrorNo(VOS_ERRNO_TASK_CREATE_NOFREETCB);
        /*lint +e534*/
        VOS_ProtectionReboot(VOS_ERRNO_TASK_CREATE_NOFREETCB, 0, 0, VOS_NULL_PTR, 0);

        return( VOS_ERRNO_TASK_CREATE_NOFREETCB );
    }

    stTaskPara.pfnTaskEntry  = (TSK_ENTRY_FUNC)pfnFunc;
    stTaskPara.usTaskPrio    = (TSK_PRIOR_T)ulPriority;
    stTaskPara.usQNum        = 0;
    stTaskPara.auwArgs[0]    = aulArgs[0];
    stTaskPara.auwArgs[1]    = aulArgs[1];
    stTaskPara.auwArgs[2]    = aulArgs[2];
    stTaskPara.auwArgs[3]    = aulArgs[3];
    stTaskPara.uwStackSize   = ulStackSize;
    stTaskPara.uwStackAddr   = 0;
    stTaskPara.uwPrivateData = ulTid;

    /* caller not use name asign a default name */
    if ( VOS_NULL_PTR == puchName )
    {
        default_name[0]= 't';
        default_name[1]= 'i';
        default_name[2]= 'd';
        default_name[3] = (VOS_CHAR)(48 + ulTid/100);
        value = (VOS_UCHAR)(ulTid%100);
        default_name[4] = (VOS_CHAR)(48 + value/10);
        default_name[5] = (VOS_CHAR)(48 + value%10);
        default_name[6]= '\0';

        stTaskPara.pcName = default_name;

        ulResult = SRE_TaskCreate((VOS_UINT*)&ulRTOSckTid, &stTaskPara);
    }
    else
    {
        stTaskPara.pcName = puchName;

        ulResult = SRE_TaskCreate((VOS_UINT*)&ulRTOSckTid, &stTaskPara);
    }

    if (SRE_OK != ulResult)
    {
        /*lint -e534*/
        VOS_TaskCtrlBlkFree(ulTid);
        VOS_SetErrorNo(VOS_ERRNO_TASK_CREATE_OSALCREATEFAIL);
        /*lint +e534*/
        VOS_ProtectionReboot(VOS_ERRNO_TASK_CREATE_OSALCREATEFAIL, (VOS_INT)ulResult, 0,
                             VOS_NULL_PTR, 0);
        return( VOS_ERRNO_TASK_CREATE_OSALCREATEFAIL );
    }
    else
    {
        *pulTaskID = ulTid;

        if ( VOS_NULL_PTR != puchName )
        {
            for(i=0; i<VOS_MAX_LENGTH_TASK_NAME; i++)
            {
                vos_TaskCtrlBlk[ulTid].Name[i]= puchName[i];
            }
            vos_TaskCtrlBlk[ulTid].Name[i-1]  = '\0';
        }
        else
        {
            vos_TaskCtrlBlk[ulTid].Name[0] = default_name[0];
            vos_TaskCtrlBlk[ulTid].Name[1] = default_name[1];
            vos_TaskCtrlBlk[ulTid].Name[2] = default_name[2];
            vos_TaskCtrlBlk[ulTid].Name[3] = default_name[3];
            vos_TaskCtrlBlk[ulTid].Name[4] = default_name[4];
            vos_TaskCtrlBlk[ulTid].Name[5] = default_name[5];
            vos_TaskCtrlBlk[ulTid].Name[6] = default_name[6];
        }

        vos_TaskCtrlBlk[ulTid].Function   = pfnFunc;
        vos_TaskCtrlBlk[ulTid].Priority   = ulPriority;
        vos_TaskCtrlBlk[ulTid].StackSize  = ulStackSize;

        for ( i=0; i<VOS_TARG_NUM; i++ )
        {
            vos_TaskCtrlBlk[ulTid].Args[i]    = aulArgs[i];
        }

        vos_TaskCtrlBlk[ulTid].ulRtosckTID= ulRTOSckTid;

        return( VOS_OK );
    }
}

/*****************************************************************************
 Function   : VOS_SuspendTask
 Description: Suspend a task
 Calls      : OSAL_SuspendTask
 Called By  :
 Input      : ulTaskID  --  id of a task
 Output     : none
 Return     : return VOS_OK if success
 Other      : none
 *****************************************************************************/
VOS_UINT32 VOS_SuspendTask( VOS_UINT32 ulTaskID )
{
    VOS_UINT32                          ulTaskPID;
    VOS_UINT32                          ulResult;

    if(ulTaskID >= vos_TaskCtrlBlkNumber)
    {
        if(ulTaskID == 0xFFFFFFFF)
        {
            ulTaskPID = 0;
        }
        else
        {
            return(VOS_ERR);
        }
    }
    else
    {
        ulTaskPID  = vos_TaskCtrlBlk[ulTaskID].ulRtosckTID;
        if(ulTaskPID == (VOS_UINT32)VOS_TASK_CTRL_BLK_VXWORKS_TASKID_NULL)
        {
            return(VOS_ERR);
        }
    }

    ulResult = SRE_TaskSuspend( ulTaskPID );

    if ( SRE_OK == ulResult )
    {
        return(VOS_OK);
    }
    else
    {
        /*lint -e534*/
        Print1("# taskSuspend errno is %x.\r\n", ulResult);
        /*lint +e534*/
        return(VOS_ERR);
    }
}

/*****************************************************************************
 Function   : VOS_ResumeTask
 Description: Resume a task
 Input      : ulTaskID  --  ID of task
 Return     : Return VOS_OK if successd
 *****************************************************************************/
VOS_UINT32 VOS_ResumeTask( VOS_UINT32 ulTaskID )
{
    VOS_UINT32                          ulTaskPID;
    VOS_UINT32                          ulResult;

    if(ulTaskID >= vos_TaskCtrlBlkNumber)
    {
        return(VOS_ERR);
    }
    else
    {
        ulTaskPID  = vos_TaskCtrlBlk[ulTaskID].ulRtosckTID;
        if(ulTaskPID == (VOS_UINT32)VOS_TASK_CTRL_BLK_VXWORKS_TASKID_NULL)
        {
            return(VOS_ERR);
        }
    }

    ulResult = SRE_TaskResume(ulTaskPID);

    if (SRE_OK == ulResult)
    {
        return(VOS_OK);
    }
    else
    {
        /*lint -e534*/
        Print1("# taskResume errno is %x.\r\n", ulResult);
        /*lint +e534*/
        return(VOS_ERR);
    }
}

/*****************************************************************************
 Function   : VOS_TaskDelay
 Description: Let the task sleep specified millseconds, only tick precision
 Output     : None
 Input      : ulMillSecs: specified millseconds
 Return     : VOS_OK on success or error code on failed
 *****************************************************************************/
VOS_UINT32 VOS_TaskDelay( VOS_UINT32 ulMillSecs )
{
    VOS_UINT32                          ulResult;

    ulResult = SRE_TaskDelay(ulMillSecs/10 + 1);

    if (SRE_OK == ulResult)
    {
        return(VOS_OK);
    }
    else
    {
        /*lint -e534*/
        Print1("taskDelay errno is %x.\r\n", ulResult);
        /*lint +e534*/
        return(VOS_ERR);
    }
}

#if (VOS_DEBUG == VOS_CHECK_TASKLOCK)

/*****************************************************************************
 Function   : V_TaskLock
 Description: forbid task attemper.
 Input      : file line
 Output     : None
 Return     : VOS_OK on success and others on failure
 Other      : This functin can not be called in interrupt routine.
 *****************************************************************************/
VOS_UINT32 V_TaskLock( VOS_UINT32 ulFileID, VOS_INT32 lLineNo )
{
    SRE_TaskLock();

    if ( VOS_NESTED_TASKLOCK_MAX_NUM <= g_stVosTaskLockNestedInfo.ulSuffix )
    {
        g_stVosTaskLockNestedInfo.ulSuffix++;

        /*lint -e534*/
        LogPrint2("# Info: tasklock nested too big.F %d L %d.\r\n", (VOS_INT32)ulFileID, (VOS_INT32)lLineNo);
        /*lint +e534*/

        return VOS_OK;
    }

    g_stVosTaskLockNestedInfo.astNestedInfo[g_stVosTaskLockNestedInfo.ulSuffix].ulFile  = ulFileID;
    g_stVosTaskLockNestedInfo.astNestedInfo[g_stVosTaskLockNestedInfo.ulSuffix].lLine   = lLineNo;
    g_stVosTaskLockNestedInfo.astNestedInfo[g_stVosTaskLockNestedInfo.ulSuffix].ulSlice = VOS_GetSlice();

    g_stVosTaskLockNestedInfo.ulSuffix++;

    return VOS_OK;
}

/*****************************************************************************
 Function   : V_TaskUnlock
 Description: permit task attemper.
 Input      : None
 Output     : None
 Return     : VOS_OK on success and others on failure
 Other      : This functin can not be called in interrupt routine.
 *****************************************************************************/
VOS_UINT32 V_TaskUnlock( VOS_VOID )
{
    g_stVosTaskLockNestedInfo.ulSuffix--;

    if ( VOS_NESTED_TASKLOCK_MAX_NUM > g_stVosTaskLockNestedInfo.ulSuffix )
    {
        if ( VOS_TASKLOCK_MAX_INTERVAL <
            (VOS_GetSlice() - g_stVosTaskLockNestedInfo.astNestedInfo[g_stVosTaskLockNestedInfo.ulSuffix].ulSlice) )
        {
             /*lint -e534*/
             LogPrint2("# Info: tasklock time too big.F %d L %d.\r\n",
                (VOS_INT32)g_stVosTaskLockNestedInfo.astNestedInfo[g_stVosTaskLockNestedInfo.ulSuffix].ulFile,
                (VOS_INT32)g_stVosTaskLockNestedInfo.astNestedInfo[g_stVosTaskLockNestedInfo.ulSuffix].lLine);
             /*lint +e534*/
        }
    }

    SRE_TaskUnlock();

    return VOS_ERR;
}

#else

/*****************************************************************************
 Function   : VOS_TaskLock
 Description: forbid task attemper.
 Input      : None
 Output     : None
 Return     : VOS_OK on success and others on failure
 Other      : This functin can not be called in interrupt routine.
 *****************************************************************************/
VOS_UINT32 VOS_TaskLock( VOS_VOID )
{
    SRE_TaskLock();

    return VOS_OK;
}

/*****************************************************************************
 Function   : VOS_TaskUnlock
 Description: permit task attemper.
 Input      : None
 Output     : None
 Return     : VOS_OK on success and others on failure
 Other      : This functin can not be called in interrupt routine.
 *****************************************************************************/
VOS_UINT32 VOS_TaskUnlock( VOS_VOID )
{
    SRE_TaskUnlock();

    return VOS_OK;
}

#endif

/*****************************************************************************
 Function   : VOS_DeleteTask
 Description: Delete a task, on some platform this operation is prohibited.
 Input      : ulTaskID -- ID of task to delete, 0 for current task ID
                          VOS_NULL_DWORD means current task exit normally,
                          so only need to free the dopra task resource,
                          do not need to call OSAL_DeleteTask.
 Output     : None
 Return     : VOS_OK on success or error code on failed
 *****************************************************************************/
VOS_UINT32 VOS_DeleteTask( VOS_UINT32 ulTaskID )
{
    return(VOS_OK);
}

/*****************************************************************************
 Function   : VOS_GetCurrentTaskID
 Description: Get current task's ID
 Input      : none
 Output     : none
 Return     : Return task's ID if success or fail information if fail
 Other      : none
 *****************************************************************************/
VOS_UINT32 VOS_GetCurrentTaskID( VOS_VOID )
{
    int                                 intLockLevel;
    VOS_UINT32                          ulTid;
    VOS_UINT32                          ulTaskPID;

    intLockLevel = VOS_SplIMP();

    if (SRE_OK != SRE_TaskSelf((VOS_UINT*)&ulTaskPID))
    {
        VOS_Splx(intLockLevel);

        /*lint -e534*/
        LogPrint("# VOS_GetCurrentTaskID: SRE_TaskSelf error.\r\n");
        /*lint +e534*/

        return VOS_NULL_DWORD;
    }

    ulTid = SRE_TaskPrivateDataGet();

    if (ulTaskPID != vos_TaskCtrlBlk[ulTid].ulRtosckTID)
    {
        VOS_Splx(intLockLevel);

        /*lint -e534*/
        LogPrint("# VOS_GetCurrentTaskID fatal error.\r\n");
        /*lint +e534*/

        return VOS_NULL_DWORD;
    }

    VOS_Splx(intLockLevel);

    return ulTid;
}

/*****************************************************************************
 Function   :VOS_UINT32 VOS_CreateEvent( VOS_UINT32 ulTaskID )
 Description:Create resource for the Event.
 Calls      :no
 Called By  :Application
 Input      :
            ulTaskID  The Task ID
 Output     :
            NULL
 Return     :
            VOS_OK    when success
            ErrorNo   when failure
 Other      :
 *****************************************************************************/
VOS_UINT32 VOS_CreateEvent( VOS_UINT32 ulTaskID )
{
    if ( VOS_TASK_CTRL_BLK_IDLE == vos_TaskCtrlBlk[ulTaskID].Flag )
    {
        return VOS_ERR;
    }

    vos_TaskCtrlBlk[ulTaskID].ulEventIsCreate = VOS_TRUE;
    vos_TaskCtrlBlk[ulTaskID].ulEvents   = 0;
    vos_TaskCtrlBlk[ulTaskID].ulExpects  = 0;
    vos_TaskCtrlBlk[ulTaskID].ulReceives = 0;
    vos_TaskCtrlBlk[ulTaskID].ulFlags    = VOS_EVENT_NOWAIT;

    return VOS_OK;
}

/*****************************************************************************
 Function   : VOS_CheckEvent
 Description: checke a event exists or not
 Input      : none
 Output     : none
 Return     : VOS_OK or VOS_ERR
 Other      : none
 *****************************************************************************/
VOS_UINT32 VOS_CheckEvent( VOS_UINT32 ulTaskID )
{
#if (VOS_YES == VOS_CHECK_PARA)
    if ( VOS_TASK_CTRL_BLK_IDLE == vos_TaskCtrlBlk[ulTaskID].Flag )
    {
        return VOS_ERR;
    }

    if ( VOS_FALSE == vos_TaskCtrlBlk[ulTaskID].ulEventIsCreate )
    {
        return VOS_ERR;
    }

    if ( 0xffffffff == vos_TaskCtrlBlk[ulTaskID].ulFid )
    {
        return VOS_ERR;
    }
#endif

    return VOS_OK;
}

/*****************************************************************************
 Function   : VOS_RecordFIDTIDInfo
 Description: record corresponding of FID&TID
 Input      : none
 Output     : none
 Return     : VOS_OK or VOS_ERR
 Other      : none
 *****************************************************************************/
VOS_UINT32 VOS_RecordFIDTIDInfo( VOS_UINT32 ulFid, VOS_UINT32 ulTid )
{
    vos_TaskCtrlBlk[ulTid].ulFid = ulFid;

    return VOS_OK;
}

/*****************************************************************************
 Function   :VOS_UINT32   VOS_EventWrite( VOS_UINT32 ulTaskID, VOS_UINT32 ulEvents )
 Description:Send Event to the TaskID.
 Calls      :VOS_TRACE_SEND_EVENT(), VOS_CheckTaskIDValid(),VOS_SplIMP(),VOS_Splx()
 Called By  :Application
 Input      :ulTaskID, ulEvents
 Output     :NULL
 Return     :
            VOS_OK   when sucess
            ERRNO   when fail
 Other      :
 *****************************************************************************/
VOS_UINT32 VOS_EventWrite( VOS_UINT32 ulTaskID, VOS_UINT32 ulEvents )
{
    /* the functin should be full later */
    int                      intLockLevel;
    VOS_UINT32               ulTempQueue;
    VOS_SEM                  ulTempSem;

    if ( VOS_OK != VOS_CheckEvent(ulTaskID) )
    {
        /*lint -e534*/
        LogPrint("# VOS_EventWrite EVENT not exist.\r\n");
        /*lint +e534*/
        return VOS_ERR;
    }

    intLockLevel = VOS_SplIMP();

    vos_TaskCtrlBlk[ulTaskID].ulEvents |= ulEvents;

    VOS_Splx( intLockLevel );

    ulTempQueue = VOS_GetQueueIDFromFid(vos_TaskCtrlBlk[ulTaskID].ulFid);
#if (VOS_YES == VOS_CHECK_PARA)
    if ( 0xffffffff == ulTempQueue )
    {
        return VOS_ERR;
    }
#endif

    ulTempSem = VOS_GetSemIDFromQueue(ulTempQueue);
#if (VOS_YES == VOS_CHECK_PARA)
    if ( 0xffffffff == ulTempSem )
    {
        return VOS_ERR;
    }
#endif

    if ( VOS_OK != VOS_SmV( ulTempSem ) )
    {
        /*lint -e534*/
        LogPrint("# VOS_EventWrite VOS_SmV errno .\r\n");
        /*lint +e534*/

        return VOS_ERR;
    }
    else
    {
        return VOS_OK;
    }
}

/*****************************************************************************
 Function   :VOS_UINT32 VOS_EventRead( VOS_UINT32 ulEvents,
                            VOS_UINT32 ulFlags,
                            VOS_UINT32  ulTimeOutInMillSec,
                            VOS_UINT32 * pulRetEvents )
 Description:Read event
 Calls      :VOS_TRACE_SEND_EVENT(),VOS_GetCurrentTaskID(),
             VOS_SplIMP(),VOS_Splx(),VOS_Dispater()
 Called By  :Application
 Input      :
            ulEvents    the expect event, while 0 refers to check event only,
                        NOT get it while return.
            ulFlags     the Flags, refers to WAIT or NOWAIT, ANY or ALL, etc.
            ulTimeOutInMillSec  the deadline while WAIT for event
 Output     :pulRetEvents       the received Event.
 Return     :
            VOS_OK when sucess
            ERRNO when failure
 Other      :
 *****************************************************************************/
VOS_UINT32 VOS_EventRead( VOS_UINT32 ulEvents,
                          VOS_UINT32 ulFlags,
                          VOS_UINT32 ulTimeOutInMillSec,
                          VOS_UINT32 *pulRetEvents )
{
    /* the functin should be full later */
    VOS_UINT32     ulTaskSelf;       /*Self task ID*/
    VOS_UINT32     ulTempQueue;
    VOS_SEM        ulTempSem;
    int            intLockLevel;
    VOS_UINT32     ulTempEvent;

    ulTaskSelf = VOS_GetCurrentTaskID();
#if (VOS_YES == VOS_CHECK_PARA)
    if ( 0xffffffff == ulTaskSelf )
    {
        return VOS_ERR;
    }

    if( VOS_EVENT_NOWAIT & ulFlags )
    {
        /*lint -e534*/
        LogPrint("# OSA don't support VOS_EVENT_NOWAIT.\r\n");

        VOS_SuspendTask(ulTaskSelf);
        /*lint +e534*/

        return VOS_ERR;
    }
#endif

    if( !(VOS_EVENT_ANY & ulFlags) )
    {
        /*lint -e534*/
        LogPrint("# OSA don't support VOS_EVENT_ALL.\r\n");

        VOS_SuspendTask(ulTaskSelf);
        /*lint +e534*/

        return VOS_ERR;
    }

    if( 0 == ulEvents )
    {
        /*lint -e534*/
        LogPrint("# OSA don't support event = 0.\r\n");

        VOS_SuspendTask(ulTaskSelf);
        /*lint +e534*/

        return VOS_ERR;
    }

    if ( VOS_OK != VOS_CheckEvent(ulTaskSelf) )
    {
        /*lint -e534*/
        LogPrint("# VOS_EventRead EVENT not exist.\r\n");

        VOS_SuspendTask(ulTaskSelf);
        /*lint +e534*/

        return VOS_ERR;
    }

    ulTempQueue = VOS_GetQueueIDFromFid(vos_TaskCtrlBlk[ulTaskSelf].ulFid);
#if (VOS_YES == VOS_CHECK_PARA)
    if ( 0xffffffff == ulTempQueue )
    {
        return VOS_ERR;
    }
#endif

    ulTempSem = VOS_GetSemIDFromQueue(ulTempQueue);
#if (VOS_YES == VOS_CHECK_PARA)
    if ( 0xffffffff == ulTempSem )
    {
        return VOS_ERR;
    }
#endif

    if( VOS_OK != VOS_SmP( ulTempSem, ulTimeOutInMillSec ) )
    {
        /*lint -e534*/
        Print("# VOS_EventRead VOS_SmP errno.\r\n");
        /*lint +e534*/
        return VOS_ERR;
    }

    intLockLevel = VOS_SplIMP();

    ulTempEvent = vos_TaskCtrlBlk[ulTaskSelf].ulEvents & ulEvents;

    if (  ulTempEvent )
    {
        vos_TaskCtrlBlk[ulTaskSelf].ulEvents &= ~ulTempEvent;
        *pulRetEvents  = ulTempEvent;
    }
    else
    {
        *pulRetEvents = VOS_MSG_SYNC_EVENT;
    }

    VOS_Splx( intLockLevel );

    return VOS_OK;
}

/*****************************************************************************
 Function   : VOS_GetQueueIDFromTID
 Description: get the queue ID of a TId
 Input      : ulFID      -- Function module Identifier

 Return     : the queue ID
 *****************************************************************************/
VOS_UINT32 VOS_GetQueueIDFromTID(VOS_UINT32 ulTid)
{
#if (VOS_YES == VOS_CHECK_PARA)
    if ( ulTid >= vos_TaskCtrlBlkNumber )
    {
        /*lint -e534*/
        LogPrint("VOS_GetQueueIDFromTID TID invaild.\r\n");
        /*lint +e534*/

        return 0xffffffff;
    }

    if ( 0xffffffff == vos_TaskCtrlBlk[ulTid].ulFid )
    {
        /*lint -e534*/
        LogPrint("VOS_GetQueueIDFromTID FID invaild.\r\n");
        /*lint +e534*/

        return 0xffffffff;
    }
#endif

    return VOS_GetQueueIDFromFid(vos_TaskCtrlBlk[ulTid].ulFid);
}

/*****************************************************************************
 Function   : VOS_GetTCBFromTID
 Description: get the task tcb of a TId
 Input      : ulTid      -- task id

 Return     : tcb
 *****************************************************************************/
VOS_UINT32 VOS_GetTCBFromTID(VOS_UINT32 ulTid)
{
    VOS_UINT32                          ulTcbAddr;

    if (SRE_OK != SRE_TaskTcbAddrGet(vos_TaskCtrlBlk[ulTid].ulRtosckTID, (VOS_UINT*)&ulTcbAddr))
    {
        return VOS_NULL;
    }

    return ulTcbAddr;
}

#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


