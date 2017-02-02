

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "BST_CORE_Regedit.h"
#include "BST_DSPP_CtrLayer.h"
#include "BST_APP_HeartBeat.h"
#include "BST_APP_EmailBox.h"
#include "BST_SRV_TaskMng.h"
#include "BST_SRV_Event.h"
#include "BST_DBG_MemLeak.h"
#include "BST_APP_MainTask.h"
#include "arch/sys_arch.h"
/*lint -e767*/
#define    THIS_FILE_ID     PS_FILE_ID_BST_SRV_TASKMNG_CPP
/*lint +e767*/
/******************************************************************************
   2 �궨��
******************************************************************************/
#define BST_SRV_GetThreadTreeRoot()     ( &g_lstThreadTree[0] )
#define BST_SRV_GetAppThreadAddress()   ( &g_lstThreadTree[BST_SRV_APP_THRD_ADDR] )
#define BST_SRV_GetIpThreadNode()       ( &g_lstThreadTree[BST_SRV_IP_THRD_ADDR] )
#define BST_SRV_GetChnlThreadNode()     ( &g_lstThreadTree[BST_SRV_CHNL_THRD_ADDR] )
#define BST_SRV_GetSysThreadNode()      ( &g_lstThreadTree[BST_SRV_SYS_THRD_ADDR] )

/*****************************************************************************
  3 ��������
*****************************************************************************/
extern "C"
{
    BST_VOID BST_IP_LwipLockInit( BST_VOID );
    BST_VOID BST_SRV_InitMultiThread( BST_VOID );
    BST_VOID BST_DRV_NET_Thread( BST_VOID *pvArg );
}
#if( BST_CFG_RT_THRD_NUM != 0 )
BST_STATIC BST_VOID BST_SRV_RT_AppThreadEntry( BST_VOID *pvArg );
#endif
#if( BST_CFG_NRT_THRD_NUM != 0 )
BST_STATIC BST_VOID BST_SRV_NRT_AppThreadEntry( BST_VOID *pvArg );
#endif
BST_STATIC BST_VOID BST_SRV_SysThreadEntry( BST_VOID *pvArg );
extern BST_VOID BST_SRV_CHNL_ThreadEntry( BST_VOID *pvArg );

/******************************************************************************
   4 ˽�ж���
******************************************************************************/
BST_STATIC BST_SRV_THREAD_ITEM_STRU g_lstThreadTree[ BST_SRV_THRD_AMOUNT ]  = { {0} };
BST_STATIC BST_UINT16               g_usAppInitCnt = 0;
BST_STATIC BST_OS_SPINLOCK_T        g_ThreadTreeLock;
extern "C" sys_mbox_t   mbox;
/******************************************************************************
   5 ����ʵ��
******************************************************************************/


BST_VOID    BST_SRV_InitMultiThread( BST_VOID )
{
    BST_SRV_THREAD_ITEM_STRU   *pThreadItem;
    BST_SRV_TASK_ITEM_STRU     *pTaskNode;
    BST_UINT16                  usCnt;
    BST_OS_LOCKCNT_T            lcTreeCnt;
    BST_CHAR                    cThreadName[ BST_SRV_APP_NAME_LEN ];

    BST_OS_MEMSET( cThreadName, 0, BST_OS_SIZEOF( cThreadName ) );
    BST_OS_InitSpinLock( &g_ThreadTreeLock );
    lcTreeCnt                   = BST_OS_SpinLock( &g_ThreadTreeLock );
    pThreadItem                 = BST_SRV_GetThreadTreeRoot();
    for( usCnt=0; usCnt<BST_SRV_THRD_AMOUNT; usCnt ++ )
    {
        pThreadItem->pMsgHandle = BST_NULL_PTR;
        lstInit( &pThreadItem->lstTaskTree );
        pThreadItem ++;
    }
    pThreadItem                 = BST_SRV_GetThreadTreeRoot();
    /*
     * ��ʼ��ϵͳ�������߳�
     */
#if( BST_CFG_SYS_THRD_NUM != 0 )
    BST_OS_CreateThread ( (BST_INT8 *)"BST_SYS_Thread",
                          (BST_OS_THREAD_T)BST_SRV_SysThreadEntry,
                          &pThreadItem[ BST_SRV_SYS_THRD_ADDR ].pMsgHandle,
                           BST_OS_STACK_SIZE_XL,
                           BST_OS_PRIO_HIGH );
    pTaskNode                   = ( BST_SRV_TASK_ITEM_STRU *)BST_OS_MALLOC
                                  ( BST_OS_SIZEOF( BST_SRV_TASK_ITEM_STRU ) );
    BST_ASSERT_NULL( pTaskNode );
    pTaskNode->usProcId         = BST_APP_TYPE_SYSTASK;
    pTaskNode->usTaskId         = BST_APP_MAIN_TASK_ID;
    lstAdd( &pThreadItem[BST_SRV_SYS_THRD_ADDR].lstTaskTree, (NODE *)pTaskNode );
#endif


    /*
     * ��ʼ��ʵʱִ�������߳�
     */
#if( BST_CFG_RT_THRD_NUM != 0 )
    for ( usCnt = 0; usCnt < BST_CFG_RT_THRD_NUM; usCnt ++ )
    {
        snprintf( cThreadName, BST_OS_SIZEOF( cThreadName ), "BST_RT_APP_%d", usCnt );
        BST_OS_CreateThread ( (BST_INT8 *)cThreadName,
                              (BST_OS_THREAD_T)BST_SRV_RT_AppThreadEntry,
                              &pThreadItem[ BST_SRV_RT_THRD_ADDR + usCnt].pMsgHandle,
                               BST_OS_STACK_SIZE_XL,
                               BST_OS_PRIO_MIDL );
    }
#endif

    /*
     * ��ʼ����ʵʱִ�������߳�
     */
#if( BST_CFG_NRT_THRD_NUM != 0 )
    for ( usCnt = 0; usCnt < BST_CFG_NRT_THRD_NUM; usCnt ++ )
    {
        snprintf( cThreadName, BST_OS_SIZEOF( cThreadName ), "BST_NRT_APP_%d", usCnt );
        BST_OS_CreateThread ( (BST_INT8 *)cThreadName,
                              (BST_OS_THREAD_T)BST_SRV_NRT_AppThreadEntry,
                              &pThreadItem[ BST_SRV_NRT_THRD_ADDR + usCnt].pMsgHandle,
                               BST_OS_STACK_SIZE_XL,
                               BST_OS_PRIO_MIDL );
    }
#endif

    /*
     * ��ʼ��IPЭ��ջ�����߳�
     */
#if( BST_CFG_IP_THRD_NUM != 0 )
    pThreadItem                 = BST_SRV_GetIpThreadNode();
    pThreadItem->pMsgHandle     = ( BST_OS_MBX_T *)mbox;
    BST_OS_CreateThread ( ( BST_INT8 *)"BST_IP_Thread",
                          ( BST_OS_THREAD_T)BST_DRV_NET_Thread,
                            BST_NULL_PTR,
                            BST_OS_STACK_SIZE_XL,
                            BST_OS_PRIO_MIDL );
    BST_IP_LwipLockInit();
#endif
    /*
     * ��ʼ���ŵ��ּ������߳�
     */
#if( BST_CFG_CHNL_THRD_NUM != 0 )
    pThreadItem                 = BST_SRV_GetChnlThreadNode();
    for ( usCnt = 0; usCnt < BST_CFG_CHNL_THRD_NUM; usCnt ++ )
    {
        snprintf( cThreadName, BST_OS_SIZEOF( cThreadName ), "BST_CHNL_%d", usCnt );
        BST_OS_CreateThread ( (BST_INT8 *)cThreadName,
                              (BST_OS_THREAD_T)BST_SRV_CHNL_ThreadEntry,
                              &pThreadItem[usCnt].pMsgHandle,
                               BST_OS_STACK_SIZE_XL,
                               BST_OS_PRIO_MIDL );
    }
#endif
    BST_OS_SpinUnLock( &g_ThreadTreeLock, lcTreeCnt );
}


BST_OS_MBX_T * BST_SRV_GetTaskMsgHandle(
    BST_PROCID_T    usProcId,
    BST_TASKID_T    usTaskId )
{
    BST_SRV_THREAD_ITEM_STRU   *pstTargetThread;
    BST_SRV_TASK_ITEM_STRU     *pTaskNode;
    BST_UINT16                  usCnt;

    if( BST_APP_TYPE_SYSTASK == usProcId )
    {
        return BST_SRV_GetSysMsgHandle();
    }
    pstTargetThread             = BST_SRV_GetAppThreadAddress();
    usCnt                       = 0;
    for( usCnt = 0; usCnt < BST_SRV_APP_THRD_AMOUNT; usCnt++ )
    {
        for( pTaskNode = ( BST_SRV_TASK_ITEM_STRU *)
                         lstFirst( &pstTargetThread[usCnt].lstTaskTree );
             pTaskNode!= BST_NULL_PTR;
             pTaskNode = ( BST_SRV_TASK_ITEM_STRU *)lstNext( (NODE *)pTaskNode) )
        {
            if( ( pTaskNode->usProcId == usProcId )
              &&( pTaskNode->usTaskId == usTaskId ) )
            {
                return pstTargetThread[usCnt].pMsgHandle;
            }
        }
    }
    return BST_NULL_PTR;
}



BST_OS_MBX_T * BST_SRV_GetChnlCtrlHandle(
    BST_UINT32      ulThdNumber )
{
    BST_SRV_THREAD_ITEM_STRU   *pstTargetThread;

    ulThdNumber                 = ulThdNumber;
    pstTargetThread             = BST_SRV_GetChnlThreadNode();

    if( BST_NULL_PTR == pstTargetThread )
    {
        return BST_NULL_PTR;
    }

    return pstTargetThread->pMsgHandle;
}


BST_OS_MBX_T * BST_SRV_GetSysMsgHandle( BST_VOID )
{
    return( BST_SRV_GetSysThreadNode()->pMsgHandle );
}

#if( BST_CFG_RT_THRD_NUM != 0 )

BST_STATIC BST_VOID BST_SRV_RT_AppThreadEntry( BST_VOID *pvArg )
{
    BST_OS_MBX_T      **pstMailBox;
    BST_OS_LOCKCNT_T    tThreadLockCnt;
    BST_EVT_HEAD_STRU  *pstEvent;
    BST_UINT32          ulRtnVal;

    if ( BST_NULL_PTR == pvArg )
    {
        return;
    }
    /*
     * �̲߳�����ʼ�����������䣬���б�ʶ
     */
    tThreadLockCnt      = BST_OS_ThreadLock ();
    pstMailBox          = (BST_OS_MBX_T **)pvArg;
   *pstMailBox          = BST_OS_CreateMbx
                        ( BST_OS_GetCurrentThreadId(), BST_M_MBOX_SIZE );
    BST_ASSERT_NULL( pstMailBox );
    BST_SetThreadInitFlag( BST_APP_THREAD_FLAG << g_usAppInitCnt );
    g_usAppInitCnt++;
    BST_OS_ThreadUnLock ( tThreadLockCnt );

    /*
     * �����߳���ѭ�����ȴ��ʼ����ʼ�����Ϊ����ִ�е�����
     */
    for(;;)
    {
        ulRtnVal        = BST_OS_RecvMail
                       ( *pstMailBox, (BST_VOID **)&pstEvent, BST_OS_SYS_FOREVER );
        BST_ASSERT_NORM( BST_OS_SYS_TIMEOUT == ulRtnVal );
        BST_SRV_ProcAppEvent( pstEvent );

        if( BST_NULL_PTR != pstEvent->pucData )
        {
            BST_OS_FREE( pstEvent->pucData );
        }
        BST_OS_FREE( pstEvent );
#if ( BST_VER_TYPE == BST_UT_VER )
        break;
#endif
     }
}
#endif

#if( BST_CFG_NRT_THRD_NUM != 0 )

BST_STATIC BST_VOID BST_SRV_NRT_AppThreadEntry( BST_VOID *pvArg )
{
    BST_OS_MBX_T      **pstMailBox;
    BST_OS_LOCKCNT_T    tThreadLockCnt;
    BST_EVT_HEAD_STRU  *pstEvent;
    BST_UINT32          ulRtnVal;

    if ( BST_NULL_PTR == pvArg )
    {
        return;
    }
    /*
     * �̲߳�����ʼ�����������䣬���б�ʶ
     */
    tThreadLockCnt      = BST_OS_ThreadLock ();
    pstMailBox          = (BST_OS_MBX_T **)pvArg;
   *pstMailBox          = BST_OS_CreateMbx
                        ( BST_OS_GetCurrentThreadId(), BST_M_MBOX_SIZE );
    BST_ASSERT_NULL( pstMailBox );
    BST_SetThreadInitFlag( BST_APP_THREAD_FLAG << g_usAppInitCnt );
    g_usAppInitCnt++;
    BST_OS_ThreadUnLock ( tThreadLockCnt );

    /*
     * �����߳���ѭ�����ȴ��ʼ����ʼ�����Ϊ����ִ�е�����
     */
    for(;;)
    {
        ulRtnVal        = BST_OS_RecvMail
                       ( *pstMailBox, (BST_VOID **)&pstEvent, BST_OS_SYS_FOREVER );
        BST_ASSERT_NORM( BST_OS_SYS_TIMEOUT == ulRtnVal );
        BST_SRV_ProcAppEvent( pstEvent );

        if( BST_NULL_PTR != pstEvent->pucData )
        {
            BST_OS_FREE( pstEvent->pucData );
        }
        BST_OS_FREE( pstEvent );
#if ( BST_VER_TYPE == BST_UT_VER )
        break;
#endif
     }
}
#endif


BST_STATIC BST_VOID BST_SRV_SysThreadEntry( BST_VOID *pvArg )
{
    BST_OS_MBX_T      **pstMailBox;
    BST_OS_LOCKCNT_T    tThreadLockCnt;
    BST_EVT_HEAD_STRU  *pstEvent;
    BST_UINT32          ulRtnVal;

    if ( BST_NULL_PTR == pvArg )
    {
        return;
    }
    /*
     * �̲߳�����ʼ�����������䣬���б�ʶ
     */
    tThreadLockCnt      = BST_OS_ThreadLock ();
    pstMailBox          = (BST_OS_MBX_T **)pvArg;
   *pstMailBox          = BST_OS_CreateMbx
                        ( BST_OS_GetCurrentThreadId(), BST_S_MBOX_SIZE );
    BST_ASSERT_NULL( pstMailBox );
    BST_SetThreadInitFlag( BST_MAIN_THREAD_FLAG );
    BST_OS_ThreadUnLock ( tThreadLockCnt );

    /*
     * �����߳���ѭ�����ȴ��ʼ����ʼ�����Ϊ����ִ�е�����
     */
    for(;;)
    {
        ulRtnVal        = BST_OS_RecvMail
                       ( *pstMailBox, (BST_VOID **)&pstEvent, BST_OS_SYS_FOREVER );
        BST_ASSERT_NORM( BST_OS_SYS_TIMEOUT == ulRtnVal );
        BST_SRV_ProcSysEvent( pstEvent );

        if( BST_NULL_PTR != pstEvent->pucData )
        {
            BST_OS_FREE( pstEvent->pucData );
        }
        BST_OS_FREE( pstEvent );
#if ( BST_VER_TYPE == BST_UT_VER )
        break;
#endif
     }
}



BST_SRV_CTaskMng *BST_SRV_CTaskMng::GetInstance( BST_VOID )
{
    static BST_SRV_CTaskMng            *pcTaskManager = BST_NULL_PTR;

    if( BST_NULL_PTR == pcTaskManager )
    {
        pcTaskManager                   = new BST_SRV_CTaskMng;
    }
    return pcTaskManager;
}

/*lint -e429*/
BST_SRV_CTaskMng::BST_SRV_CTaskMng( BST_VOID )
{
    BST_UINT32              ulCnt;
    for( ulCnt = 0; ulCnt<BST_OBJ_TYPE_MAX; ulCnt++ )
    {
        m_apcTaskIdGnrtor[ ulCnt ]  = new BST_Lib_CSnGenrator<BST_DSPP_OFSTADDR_T>
                                      ( BST_DSPP_OFFSET_ADDR_MIN,
                                        BST_DSPP_OFFSET_ADDR_MAX );
    }
    m_pcRegedit             = BST_CORE_CRegedit::GetInstance();
}
/*lint +e429*/

/*lint -e429*/
BST_DSPP_OFSTADDR_T BST_SRV_CTaskMng::Assign(
    BST_DSPP_OBJTADDR_T     usObjAddr,
    BST_DSPP_OFSTADDR_T     usOfstAddr,
    BST_OS_MBX_T          **ppstMbox )
{
    BST_DSPP_OFSTADDR_T     usNewOfstAddr;
    BST_OS_MBX_T           *pstMsgHandle;
    BST_UINT16              usTotalAppNum;

    if( !BST_DSPP_IsObjIdValid(usObjAddr) )
    {
        return BST_INVALID_SNID;
    }
    if ( BST_NULL_PTR == m_pcRegedit )
    {
        return BST_INVALID_SNID;
    }
    if ( BST_NULL_PTR == ppstMbox )
    {
        return BST_INVALID_SNID;
    }
   *ppstMbox                = BST_NULL_PTR;
    /*
     *Main Task is also a Task, But it don't use app-resource.
     */
    usTotalAppNum           = GetAppTaskTotle();
    if ( usTotalAppNum >= BST_MAX_APP_NUMBER )
    {
        return BST_INVALID_SNID;
    }

    if( BST_DSPP_IsVoidOfstAddr( usOfstAddr ) )
    {
        usNewOfstAddr       = m_apcTaskIdGnrtor[usObjAddr]->NewId();
    }
    else
    {
        usNewOfstAddr       = usOfstAddr;
    }
    if( BST_INVALID_SNID == usNewOfstAddr )
    {
        BST_RLS_LOG( "BST_SRV_CTaskMng::Assign usOfstAddr=NULL" );
        return BST_INVALID_SNID;
    }
    pstMsgHandle            = BST_NULL_PTR;
    switch ( usObjAddr )
    {
        case BST_APP_TYPE_MAILBOX:
            pstMsgHandle                = AssignToThread(
                                          usObjAddr,
                                          usNewOfstAddr,
                                          BST_SRV_APP_TYPE_NRT );
            break;

        case BST_APP_TYPE_HEARTBEAT:
            pstMsgHandle                = AssignToThread(
                                          usObjAddr,
                                          usNewOfstAddr,
                                          BST_SRV_APP_TYPE_NRT );
            break;
        default:
            pstMsgHandle                = BST_NULL_PTR;
            break;
    }
    if ( BST_NULL_PTR == pstMsgHandle )
    {
        if( BST_DSPP_IsVoidOfstAddr( usOfstAddr ) )
        {
            m_apcTaskIdGnrtor[usObjAddr]->RmvId( usNewOfstAddr );
        }
        return BST_INVALID_SNID;
    }
    else
    {
       *ppstMbox                        = pstMsgHandle;
        return usNewOfstAddr;
    }
}
/*lint +e429*/

/*lint -e438*/
BST_ERR_ENUM_UINT8  BST_SRV_CTaskMng::Remove(
    BST_DSPP_OBJTADDR_T usObjAddr,
    BST_DSPP_OFSTADDR_T usOfstAddr )
{
    BST_SRV_TASK_ITEM_STRU     *pstTaskIdx;
    BST_SRV_TASK_ITEM_STRU     *pstTaskNextIdx;
    BST_SRV_THREAD_ITEM_STRU   *pstThreadNode;
    BST_CTask                  *pcTask;
    BST_UINT16                  usCnt;
    BST_ERR_ENUM_UINT8          ucRtnVal;
    BST_OS_LOCKCNT_T            lcTreeCnt;

    if( !BST_DSPP_IsObjIdValid(usObjAddr) )
    {
        return BST_ERR_UNKNOW_OBJ;
    }
    if( BST_INVALID_SNID == usOfstAddr )
    {
        return BST_ERR_UNKNOW_OBJ;
    }
    if( BST_APP_TYPE_SYSTASK == usObjAddr )
    {
        return BST_ERR_ILLEGAL_PARAM;
    }

    lcTreeCnt                   = BST_OS_SpinLock( &g_ThreadTreeLock );
    pstThreadNode               = BST_SRV_GetAppThreadAddress();
    pstTaskNextIdx              = BST_NULL_PTR;
    ucRtnVal                    = BST_ERR_UNKNOW_OBJ;
    pcTask                      = BST_NULL_PTR;

    for( usCnt = 0; usCnt < BST_SRV_APP_THRD_AMOUNT; usCnt++ )
    {
        for( pstTaskIdx = ( BST_SRV_TASK_ITEM_STRU *)
                          lstFirst( &pstThreadNode[usCnt].lstTaskTree );
             pstTaskIdx!= BST_NULL_PTR;
             pstTaskIdx = pstTaskNextIdx )
        {
            pstTaskNextIdx      = ( BST_SRV_TASK_ITEM_STRU *)
                                  lstNext( (NODE *) pstTaskIdx );

            if ( ( ( pstTaskIdx->usTaskId != usOfstAddr )
                && ( BST_DSPP_BROADCASE_ADDRESS != usOfstAddr ) )
                || ( pstTaskIdx->usProcId != usObjAddr ) )
            {
                continue;
            }
            pcTask              = pstTaskIdx->pcTask;
            lstDelete( &pstThreadNode[usCnt].lstTaskTree, (NODE *)pstTaskIdx );
            BST_OS_FREE( pstTaskIdx );
            BST_OS_SpinUnLock( &g_ThreadTreeLock, lcTreeCnt );
            if ( BST_NULL_PTR != pcTask )
            {
                pcTask->Stop();
                delete pcTask;
            }
            BST_DBG_LOG2( "BST_SRV_CTaskMng::Remove usObjAddr, usOfstAddr",\
                           usObjAddr, usOfstAddr );
            ucRtnVal                = BST_NO_ERROR_MSG;
            m_apcTaskIdGnrtor[usObjAddr]->RmvId( usOfstAddr );
            break;//ƥ��ɹ���ɾ��Ȼ�����������������±���
        }
    }
    return ucRtnVal;
}
/*lint +e438*/

BST_ERR_ENUM_UINT8  BST_SRV_CTaskMng::RemoveAll( BST_VOID )
{
    BST_SRV_TASK_ITEM_STRU     *pstTaskIdx;
    BST_SRV_TASK_ITEM_STRU     *pstTaskNextIdx;
    BST_SRV_THREAD_ITEM_STRU   *pstThreadNode;
    BST_UINT32                  ulCnt;
    BST_OS_LOCKCNT_T            lcTreeCnt;

    lcTreeCnt                   = BST_OS_SpinLock( &g_ThreadTreeLock );
    pstThreadNode               = BST_SRV_GetAppThreadAddress();
    pstTaskNextIdx              = BST_NULL_PTR;
    for( ulCnt = 0; ulCnt < BST_SRV_APP_THRD_AMOUNT; ulCnt++ )
    {
        for( pstTaskIdx = ( BST_SRV_TASK_ITEM_STRU *)
                          lstFirst( &pstThreadNode[ulCnt].lstTaskTree );
             pstTaskIdx!= BST_NULL_PTR;
             pstTaskIdx = pstTaskNextIdx )
        {
            pstTaskNextIdx  = ( BST_SRV_TASK_ITEM_STRU *)
                              lstNext( (NODE *) pstTaskIdx );

            if ( BST_NULL_PTR != pstTaskIdx->pcTask )
            {
                pstTaskIdx->pcTask->Stop();
                delete pstTaskIdx->pcTask;
            }
            lstDelete( &pstThreadNode[ulCnt].lstTaskTree, (NODE *)pstTaskIdx );
            BST_DBG_LOG2( "BST_SRV_CTaskMng::Remove usObjAddr, usOfstAddr",
                           pstTaskIdx->usProcId, pstTaskIdx->usTaskId );
            BST_OS_FREE( pstTaskIdx );
        }
    }
    BST_OS_SpinUnLock( &g_ThreadTreeLock, lcTreeCnt );
    for( ulCnt = 0; ulCnt<BST_OBJ_TYPE_MAX; ulCnt++ )
    {
        m_apcTaskIdGnrtor[ ulCnt ]->RmvId();
    }
    BST_DBG_LOG( "BST_SRV_CTaskMng::RemoveAll" );
    return BST_NO_ERROR_MSG;
}

BST_ERR_ENUM_UINT8  BST_SRV_CTaskMng::Start(
        BST_DSPP_OBJTADDR_T         usObjAddr,
        BST_DSPP_OFSTADDR_T         usOfstAddr )
{
    BST_SRV_TASK_ITEM_STRU     *pstTaskIdx;
    BST_SRV_TASK_ITEM_STRU     *pstTaskNextIdx;
    BST_SRV_THREAD_ITEM_STRU   *pstThreadNode;
    BST_UINT16                  usCnt;
    BST_ERR_ENUM_UINT8          ucRtnVal;
    BST_OS_LOCKCNT_T            lcTreeCnt;

    if( !BST_DSPP_IsObjIdValid(usObjAddr) )
    {
        return BST_ERR_UNKNOW_OBJ;
    }
    if( BST_INVALID_SNID == usOfstAddr )
    {
        return BST_ERR_UNKNOW_OBJ;
    }
    lcTreeCnt                   = BST_OS_SpinLock( &g_ThreadTreeLock );
    pstThreadNode               = BST_SRV_GetAppThreadAddress();
    pstTaskNextIdx              = BST_NULL_PTR;
    ucRtnVal                    = BST_ERR_UNKNOW_OBJ;
    for( usCnt = 0; usCnt < BST_SRV_APP_THRD_AMOUNT; usCnt++ )
    {
        for( pstTaskIdx = ( BST_SRV_TASK_ITEM_STRU *)
                          lstFirst( &pstThreadNode[usCnt].lstTaskTree );
             pstTaskIdx!= BST_NULL_PTR;
             pstTaskIdx = pstTaskNextIdx )
        {
            pstTaskNextIdx  = ( BST_SRV_TASK_ITEM_STRU *)
                              lstNext( (NODE *) pstTaskIdx );

            if ( ( ( pstTaskIdx->usTaskId != usOfstAddr )
                && ( BST_DSPP_BROADCASE_ADDRESS != usOfstAddr ) )
                || ( pstTaskIdx->usProcId != usObjAddr ) )
            {
                continue;
            }
            BST_DBG_LOG2( "BST_SRV_CTaskMng::Start ProcId=%d, TaskId=%d is Started!",
                          usObjAddr, usOfstAddr );
            pstTaskIdx->pcTask->Start();
            ucRtnVal                    = BST_NO_ERROR_MSG;
            break;//ƥ��ɹ������������������±���
        }
    }
    BST_OS_SpinUnLock( &g_ThreadTreeLock, lcTreeCnt );
    return ucRtnVal;
}

BST_ERR_ENUM_UINT8  BST_SRV_CTaskMng::StartAll( BST_VOID )
{
    BST_SRV_TASK_ITEM_STRU     *pstTaskIdx;
    BST_SRV_TASK_ITEM_STRU     *pstTaskNextIdx;
    BST_SRV_THREAD_ITEM_STRU   *pstThreadNode;
    BST_UINT32                  ulCnt;
    BST_OS_LOCKCNT_T            lcTreeCnt;

    lcTreeCnt                   = BST_OS_SpinLock( &g_ThreadTreeLock );
    pstThreadNode               = BST_SRV_GetAppThreadAddress();
    pstTaskNextIdx              = BST_NULL_PTR;
    for( ulCnt = 0; ulCnt < BST_SRV_APP_THRD_AMOUNT; ulCnt++ )
    {
        for( pstTaskIdx = ( BST_SRV_TASK_ITEM_STRU *)lstFirst( &pstThreadNode[ulCnt].lstTaskTree );
             pstTaskIdx!= BST_NULL_PTR;
             pstTaskIdx = pstTaskNextIdx )
        {
            pstTaskNextIdx  = ( BST_SRV_TASK_ITEM_STRU *)
                              lstNext( (NODE *) pstTaskIdx );

            if ( BST_NULL_PTR != pstTaskIdx->pcTask )
            {
                BST_DBG_LOG2( "BST_SRV_CTaskMng::StartAll: ProcId=%d, TaskId=%d is Started!",
                              pstTaskIdx->pcTask->m_usProcId,
                              pstTaskIdx->pcTask->m_usTaskId );
                pstTaskIdx->pcTask->Start();
            }
        }
    }
    BST_OS_SpinUnLock( &g_ThreadTreeLock, lcTreeCnt );
    return BST_NO_ERROR_MSG;
}


BST_ERR_ENUM_UINT8  BST_SRV_CTaskMng::StopAll( BST_VOID )
{
    BST_SRV_TASK_ITEM_STRU     *pstTaskIdx;
    BST_SRV_TASK_ITEM_STRU     *pstTaskNextIdx;
    BST_SRV_THREAD_ITEM_STRU   *pstThreadNode;
    BST_UINT32                  ulCnt;
    BST_OS_LOCKCNT_T            lcTreeCnt;

    lcTreeCnt                   = BST_OS_SpinLock( &g_ThreadTreeLock );
    pstThreadNode               = BST_SRV_GetAppThreadAddress();
    pstTaskNextIdx              = BST_NULL_PTR;
    for( ulCnt = 0; ulCnt < BST_SRV_APP_THRD_AMOUNT; ulCnt++ )
    {
        for( pstTaskIdx = ( BST_SRV_TASK_ITEM_STRU *)lstFirst( &pstThreadNode[ulCnt].lstTaskTree );
             pstTaskIdx!= BST_NULL_PTR;
             pstTaskIdx = pstTaskNextIdx )
        {
            pstTaskNextIdx  = ( BST_SRV_TASK_ITEM_STRU *)
                              lstNext( (NODE *) pstTaskIdx );

            if ( BST_NULL_PTR != pstTaskIdx->pcTask )
            {
                BST_DBG_LOG2( "BST_SRV_CTaskMng::StopAll: ProcId=%d, TaskId=%d is Stoped!",
                              pstTaskIdx->pcTask->m_usProcId,
                              pstTaskIdx->pcTask->m_usTaskId );
                pstTaskIdx->pcTask->Stop();
            }
        }
    }
    BST_OS_SpinUnLock( &g_ThreadTreeLock, lcTreeCnt );
    return BST_NO_ERROR_MSG;
}

BST_ERR_ENUM_UINT8  BST_SRV_CTaskMng::Stop(
        BST_DSPP_OBJTADDR_T         usObjAddr,
        BST_DSPP_OFSTADDR_T         usOfstAddr )
{
    BST_SRV_TASK_ITEM_STRU     *pstTaskIdx;
    BST_SRV_TASK_ITEM_STRU     *pstTaskNextIdx;
    BST_SRV_THREAD_ITEM_STRU   *pstThreadNode;
    BST_UINT16                  usCnt;
    BST_ERR_ENUM_UINT8          ucRtnVal;
    BST_OS_LOCKCNT_T            lcTreeCnt;

    if( !BST_DSPP_IsObjIdValid(usObjAddr) )
    {
        return BST_ERR_UNKNOW_OBJ;
    }
    if( BST_INVALID_SNID == usOfstAddr )
    {
        return BST_ERR_UNKNOW_OBJ;
    }
    lcTreeCnt                   = BST_OS_SpinLock( &g_ThreadTreeLock );
    pstThreadNode               = BST_SRV_GetAppThreadAddress();
    pstTaskNextIdx              = BST_NULL_PTR;
    ucRtnVal                    = BST_ERR_UNKNOW_OBJ;
    for( usCnt = 0; usCnt < BST_SRV_APP_THRD_AMOUNT; usCnt++ )
    {
        for( pstTaskIdx = ( BST_SRV_TASK_ITEM_STRU *)lstFirst( &pstThreadNode[usCnt].lstTaskTree );
             pstTaskIdx!= BST_NULL_PTR;
             pstTaskIdx = pstTaskNextIdx )
        {
            pstTaskNextIdx      = ( BST_SRV_TASK_ITEM_STRU *)
                                  lstNext( (NODE *) pstTaskIdx );

            if ( ( ( pstTaskIdx->usTaskId != usOfstAddr )
                && ( BST_DSPP_BROADCASE_ADDRESS != usOfstAddr ) )
                || ( pstTaskIdx->usProcId != usObjAddr ) )
            {
                continue;
            }
            BST_DBG_LOG2( "BST_SRV_CTaskMng::Stop ProcId=%d, TaskId=%d is Stoped!",usObjAddr, usOfstAddr );
            pstTaskIdx->pcTask->Stop();
            ucRtnVal                    = BST_NO_ERROR_MSG;
            break;//ƥ��ɹ������������������±���
        }
    }
    BST_OS_SpinUnLock( &g_ThreadTreeLock, lcTreeCnt );
    return ucRtnVal;
}

BST_UINT16 BST_SRV_CTaskMng::GetLen(
        BST_DSPP_OBJTADDR_T         usObjAddr,
        BST_DSPP_OFSTADDR_T         usOfstAddr,
        BST_CORE_PID_ENUM_UINT16    enPid )
{
    if ( !BST_CORE_IsPidValid( enPid ) )
    {
        return 0;
    }
    if( BST_NULL_PTR == m_pcRegedit )
    {
        return 0;
    }
    return m_pcRegedit->GetLen( usObjAddr, usOfstAddr, enPid );
}

BST_UINT16 BST_SRV_CTaskMng::Inquire(
        BST_DSPP_OBJTADDR_T         usObjAddr,
        BST_DSPP_OFSTADDR_T         usOfstAddr,
        BST_CORE_PID_ENUM_UINT16    enPid,
        BST_DSPP_CMDLEN_T           usLength,
        BST_VOID                   *pData )
{
    if ( !BST_CORE_IsPidValid( enPid ) )
    {
        return 0;
    }
    if( BST_NULL_PTR == m_pcRegedit )
    {
        return 0;
    }
    if( BST_NULL_PTR == pData )
    {
        return 0;
    }
    if( 0 == usLength )
    {
        return 0;
    }
    return  m_pcRegedit->Inquire( usObjAddr, usOfstAddr, enPid, usLength, pData );
}

BST_ERR_ENUM_UINT8  BST_SRV_CTaskMng::Config(
        BST_DSPP_OBJTADDR_T         usObjAddr,
        BST_DSPP_OFSTADDR_T         usOfstAddr,
        BST_CORE_PID_ENUM_UINT16    enPid,
        BST_DSPP_CMDLEN_T           usLength,
        BST_VOID                   *pData )
{
    BST_ERR_ENUM_UINT8      enRtnVal;
    enRtnVal                = BST_NO_ERROR_MSG;

    if ( !BST_CORE_IsPidValid( enPid ) )
    {
        return BST_ERR_PAR_UNKNOW;
    }
    if( BST_NULL_PTR == m_pcRegedit )
    {
        return BST_ERR_NO_MEMORY;
    }
    if( BST_NULL_PTR == pData )
    {
        return BST_ERR_INVALID_PTR;
    }
    if( 0 == usLength )
    {
        return BST_ERR_PAR_LEN;
    }

    enRtnVal            = m_pcRegedit->Config( usObjAddr, usOfstAddr,
                                               enPid, usLength, pData );
    return enRtnVal;
}

BST_ERR_ENUM_UINT8 BST_SRV_CTaskMng::Create(
    BST_DSPP_OBJTADDR_T     usObjAddr,
    BST_DSPP_OFSTADDR_T     usOfstAddr )
{
    BST_PROCID_T                usProcId;
    BST_TASKID_T                usTaskId;
    BST_CTask                  *pcTask;
    BST_SRV_TASK_ITEM_STRU     *pstTaskItem;
    BST_SRV_THREAD_ITEM_STRU   *pstAppThreads;
    BST_UINT16                  usCnt;
    BST_OS_LOCKCNT_T            lcTreeCnt;

    if( !BST_DSPP_IsObjIdValid(usObjAddr) )
    {
        return BST_ERR_UNKNOW_OBJ;
    }
    if( BST_INVALID_SNID == usOfstAddr )
    {
        return BST_ERR_UNKNOW_OBJ;
    }
    usTaskId                    = usOfstAddr;
    usProcId                    = usObjAddr;
    pcTask                      = BST_NULL_PTR;

    switch ( usObjAddr )
    {
        case BST_APP_TYPE_MAILBOX:
            pcTask              = new BST_APP_CEmailBox( usProcId, usTaskId );
            break;

        case BST_APP_TYPE_HEARTBEAT:
            pcTask              = new HeartBeat( usProcId, usTaskId );
            break;

        default:
            pcTask              = BST_NULL_PTR;
            break;
    }

    if( BST_NULL_PTR == pcTask )
    {
        Remove( usProcId, usTaskId );
        return  BST_ERR_UNKNOW_OBJ;
    }
    lcTreeCnt                   = BST_OS_SpinLock( &g_ThreadTreeLock );
    pstAppThreads               = BST_SRV_GetAppThreadAddress();
    for( usCnt = 0; usCnt < BST_SRV_APP_THRD_AMOUNT; usCnt++ )
    {
        for( pstTaskItem = ( BST_SRV_TASK_ITEM_STRU *)
                            lstFirst( &pstAppThreads[usCnt].lstTaskTree );
             pstTaskItem!= BST_NULL_PTR;
             pstTaskItem = ( BST_SRV_TASK_ITEM_STRU *)lstNext( (NODE *)pstTaskItem) )
        {
            if( ( pstTaskItem->usProcId == usProcId )
              &&( pstTaskItem->usTaskId == usTaskId ) )
            {
                pstTaskItem->pcTask = pcTask;
                break;
            }
        }
        if( pstTaskItem!= BST_NULL_PTR )
        {
            break;
        }
    }
    BST_OS_SpinUnLock( &g_ThreadTreeLock, lcTreeCnt );
    if( BST_NULL_PTR == pstTaskItem )
    {
        m_apcTaskIdGnrtor[usObjAddr]->RmvId( usOfstAddr );
        delete pcTask;
        return  BST_ERR_NO_MEMORY;
    }
    return BST_NO_ERROR_MSG;
}


BST_OS_MBX_T *BST_SRV_CTaskMng::AssignToThread(
    BST_PROCID_T                usProcId,
    BST_TASKID_T                usTaskId,
    BST_UINT32                  ulTaskType )
{
    BST_SRV_THREAD_ITEM_STRU   *pstThreadPool;
    BST_SRV_THREAD_ITEM_STRU   *pstTargetThread;
    BST_SRV_TASK_ITEM_STRU     *pTaskNode;
    BST_UINT16                  usMax;
    BST_UINT16                  usCnt;
    BST_OS_LOCKCNT_T            lcTreeCnt;

    pstTargetThread         = BST_SRV_GetThreadTreeRoot();
    pstThreadPool           = BST_NULL_PTR;
    usMax                   = 0;
    usCnt                   = 0;
    switch( ulTaskType )
    {
#if ( 0 != BST_CFG_NRT_THRD_NUM )
        case BST_SRV_APP_TYPE_NRT:
            pstThreadPool   = &pstTargetThread[ BST_SRV_NRT_THRD_ADDR ];
            usMax           = BST_CFG_NRT_THRD_NUM;
            break;
#endif

#if( 0 != BST_CFG_RT_THRD_NUM )
        case BST_SRV_APP_TYPE_RT:
            pstThreadPool   = &pstTargetThread[ BST_SRV_RT_THRD_ADDR ];
            usMax           = BST_CFG_RT_THRD_NUM;
            break;
#endif
        default:
            return BST_NULL_PTR;
    }

    lcTreeCnt               = BST_OS_SpinLock( &g_ThreadTreeLock );
    pstTargetThread         = pstThreadPool;
    for( usCnt = 0; usCnt < usMax; usCnt++ )
    {
        if( pstThreadPool[usCnt].lstTaskTree.count < pstTargetThread->lstTaskTree.count )
        {
            pstTargetThread = &pstThreadPool[usCnt];
        }
    }
    BST_OS_SpinUnLock( &g_ThreadTreeLock, lcTreeCnt );
    pTaskNode                   = ( BST_SRV_TASK_ITEM_STRU *)BST_OS_MALLOC
                                  ( BST_OS_SIZEOF( BST_SRV_TASK_ITEM_STRU ) );
    BST_ASSERT_NULL_RTN( pTaskNode, BST_NULL_PTR );
    pTaskNode->usProcId         = usProcId;
    pTaskNode->usTaskId         = usTaskId;
    pTaskNode->pcTask           = BST_NULL_PTR;
    lstAdd( &pstTargetThread->lstTaskTree, (NODE *)pTaskNode );

    return pstTargetThread->pMsgHandle;
}



BST_UINT16  BST_SRV_CTaskMng::GetAppTaskTotle( BST_VOID )
{

    BST_SRV_THREAD_ITEM_STRU   *pstThreadNode;
    BST_UINT16                  usCnt, usTotal;
    BST_OS_LOCKCNT_T            lcTreeCnt;

    lcTreeCnt                   = BST_OS_SpinLock( &g_ThreadTreeLock );
    pstThreadNode               = BST_SRV_GetAppThreadAddress();
    usCnt                       = 0;
    usTotal                     = 0;
    for( usCnt = 0; usCnt < BST_SRV_APP_THRD_AMOUNT; usCnt++ )
    {
        usTotal                += pstThreadNode[usCnt].lstTaskTree.count;
    }
    BST_OS_SpinUnLock( &g_ThreadTreeLock, lcTreeCnt );
    return usTotal;
}


BST_SRV_CTaskMng::~BST_SRV_CTaskMng()
{
    BST_UINT32                          ulCnt;
    m_pcRegedit                         = BST_NULL_PTR;
#if ( BST_OS_VER != BST_QCOM_ROS )
    try
    {
#endif
        for( ulCnt = 0; ulCnt<BST_OBJ_TYPE_MAX; ulCnt++ )
        {
            if( BST_NULL_PTR != m_apcTaskIdGnrtor[ ulCnt ] )
            {
                delete m_apcTaskIdGnrtor[ ulCnt ];
            }
        }
#if ( BST_OS_VER != BST_QCOM_ROS )
    }
    catch (...)
    {
        BST_RLS_LOG("BST_SRV_CTaskMng destructor exception");
    }
#endif
}

