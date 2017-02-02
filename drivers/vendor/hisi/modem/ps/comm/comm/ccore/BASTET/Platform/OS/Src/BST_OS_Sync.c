

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "BST_OS_Sync.h"
#include "BST_OS_Memory.h"
#include "BST_OS_Timer.h"
#include "BST_OS_Thread.h"
/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_BST_OS_SYNC_C
/*lint +e767*/
/******************************************************************************
   2 �궨��
******************************************************************************/
/*****************************************************************************
  3 ��������
*****************************************************************************/

/******************************************************************************
   4 ˽�ж���
******************************************************************************/

/******************************************************************************
   5 ȫ�ֱ�������
******************************************************************************/
BST_OS_SPINLOCK_T                       g_MboxLock;
/******************************************************************************
   6 ����ʵ��
******************************************************************************/


BST_OS_SEM_STRU *BST_OS_CreateSem( BST_VOID *pvArg, BST_UINT32 ulInitCnt )
{
    BST_OS_SEM_STRU                    *pstOsSem;
    BST_OS_LOCKCNT_T                    tThreadLockCnt;

    pstOsSem                            = (BST_OS_SEM_STRU *)BST_OS_MALLOC( BST_OS_SIZEOF( BST_OS_SEM_STRU ) );

    if( BST_NULL_PTR == pstOsSem )
    {
        return BST_NULL_PTR;
    }

    tThreadLockCnt                      = BST_OS_ThreadLock();

    pstOsSem->pvArg                     = BST_OS_GetCurrentThreadId();
    pstOsSem->stHandle                  = BST_OS_PalCreateSem( ulInitCnt );
    if ( BST_OS_SYS_IsSemValid(pstOsSem->stHandle) )
    {
        BST_OS_FREE( pstOsSem );
        BST_OS_ThreadUnLock( tThreadLockCnt );
        /*lint -e438*/
        return BST_NULL_PTR;
        /*lint +e438*/
    }

#ifdef BST_OS_SIGNAL_COUNTER
    pstOsSem->ulCounter                 = ulInitCnt;
    if ( 0U != pstOsSem->ulCounter )
    {
        BST_OS_PalSendSem( pstOsSem->stHandle, pstOsSem->pvArg );
    }
#endif
    BST_OS_ThreadUnLock( tThreadLockCnt );
    return pstOsSem;
}

BST_UINT32 BST_OS_RecvSem( BST_OS_SEM_STRU *pstSemHandle, BST_UINT32 ulTimeOut )
{
    BST_UINT32                          ulStartTime;
    BST_UINT32                          ulEndTime;
    BST_ERR_ENUM_UINT8                  ucRtnVal;

    if( BST_NULL_PTR == pstSemHandle )
    {
        return BST_OS_SYS_TIMEOUT;
    }
    ulStartTime                         = BST_OS_TimerNowMs();
    pstSemHandle->pvArg                 = BST_OS_GetCurrentThreadId();
#ifdef BST_OS_SIGNAL_COUNTER
    do
    {
        ucRtnVal                        = BST_OS_PalRecvSem( pstSemHandle->stHandle,
                                                             ulTimeOut );
        if ( BST_NO_ERROR_MSG != ucRtnVal )
        {
            break;
        }
    }while( 0U == pstSemHandle->ulCounter );
#else
    ucRtnVal                            = BST_OS_PalRecvSem( pstSemHandle->stHandle,
                                                             ulTimeOut );
#endif
    if( BST_NO_ERROR_MSG == ucRtnVal )
    {
        ulEndTime                       = BST_OS_TimerNowMs();
#ifdef BST_OS_SIGNAL_COUNTER
        if( pstSemHandle->ulCounter > 0U )
        {
            pstSemHandle->ulCounter--;
        }
        if( pstSemHandle->ulCounter > 0U )
        {
            BST_OS_PalSendSem( pstSemHandle->stHandle, pstSemHandle->pvArg );
        }
#endif
        if( ulEndTime > ulStartTime )
        {
            return( ulEndTime - ulStartTime );
        }
        else
        {
            return 0U;
        }       
    }
    else
    {
        return BST_OS_SYS_TIMEOUT;
    }
}


BST_ERR_ENUM_UINT8 BST_OS_SendSem( BST_OS_SEM_STRU *pstSemHandle )
{
    if( BST_NULL_PTR == pstSemHandle )
    {
        return BST_ERR_INVALID_PTR;
    }
#ifdef BST_OS_SIGNAL_COUNTER
    pstSemHandle->ulCounter++;
#endif
    return( BST_OS_PalSendSem( pstSemHandle->stHandle, pstSemHandle->pvArg ) );
}


BST_ERR_ENUM_UINT8 BST_OS_DeleteSem( BST_OS_SEM_STRU *pstSemHandle )
{
    BST_ERR_ENUM_UINT8                  ucRtnVal;
    if( BST_NULL_PTR == pstSemHandle )
    {
        return BST_ERR_INVALID_PTR;
    }

    ucRtnVal                            = BST_OS_PalDeleteSem( pstSemHandle->stHandle );

    if( BST_NO_ERROR_MSG == ucRtnVal )
    {
        BST_OS_FREE( pstSemHandle );
    }
/*lint -e438*/
    return ucRtnVal;
/*lint +e438*/
}


BST_OS_MBX_T *BST_OS_CreateMbx( BST_VOID *pvArg, BST_UINT32 ulSize )
{
    BST_OS_MBX_T                       *pstMbx;

    if( ( 0 == ulSize ) || ( ulSize > BST_L_MBOX_SIZE ) )
    {
        return BST_NULL_PTR;
    }
    pstMbx                              = BST_OS_MALLOC( BST_OS_SIZEOF(BST_OS_MBX_T) );
    BST_ASSERT_NULL_RTN( pstMbx, BST_NULL_PTR );
    pstMbx->hSem                        = BST_NULL_PTR;

    lstInit( &pstMbx->hList );
    pstMbx->hSem                        = BST_OS_CreateSem( pvArg, 0U );
    pstMbx->ulSize                      = ulSize;

    if( BST_NULL_PTR == pstMbx->hSem )
    {
        BST_DBG_LOG("Create Mail Box Fail.\n");
        lstFree( &pstMbx->hList );
        BST_OS_FREE(pstMbx);
        /*lint -e438*/
        return BST_NULL_PTR;
        /*lint +e438*/
    }
    return( pstMbx );
}


//lint -sem(lstAdd,custodial(2))
BST_ERR_ENUM_UINT8 BST_OS_SendMail( BST_OS_MBX_T *pstMbx, BST_VOID *pMsg )
{
    BST_OS_MAIL_T                      *pstContent;
    BST_OS_LOCKCNT_T                    tThreadLockCnt;

    BST_ASSERT_NULL_RTN( pstMbx, BST_ERR_INVALID_PTR );
    BST_ASSERT_NULL_RTN( pstMbx->hSem, BST_ERR_INVALID_PTR );

    if( ( (BST_UINT32)lstCount( &pstMbx->hList ) )
           >= pstMbx->ulSize )
    {
        BST_RLS_LOG3( "BST_OS_SendMail Error: Out of the capacity, MbxName=%p, Max=%u, Count=%u",
                      pstMbx, pstMbx->ulSize, lstCount( &pstMbx->hList ) );
        return BST_ERR_PAR_OVERRUN;
    }
    pstContent                          = BST_OS_MALLOC( BST_OS_SIZEOF(BST_OS_MAIL_T) );
    BST_ASSERT_NULL_RTN( pstContent, BST_ERR_NO_MEMORY );

    tThreadLockCnt                      = (BST_OS_LOCKCNT_T)BST_OS_SpinLock( &g_MboxLock );
    pstContent->ulContent               = pMsg;

    lstAdd( &pstMbx->hList, ( NODE * )pstContent );
    BST_OS_SpinUnLock( &g_MboxLock,(BST_UINT32)tThreadLockCnt );
    BST_OS_SendSem( pstMbx->hSem );

    return( BST_NO_ERROR_MSG );
}


BST_UINT32 BST_OS_RecvMail(
    BST_OS_MBX_T   *pstMbx,
    BST_VOID      **pMsg,
    BST_UINT32      ulExTime )
{
    BST_OS_MAIL_T                      *pstContent;
    BST_UINT32                          ulPendTime;
    BST_UINT32                          ulPastTime;
    BST_OS_LOCKCNT_T                    tThreadLockCnt;

    BST_ASSERT_NULL_RTN( pstMbx,        BST_ERR_INVALID_PTR );
    BST_ASSERT_NULL_RTN( pstMbx->hSem,  BST_ERR_INVALID_PTR );
    BST_ASSERT_NULL_RTN( pMsg,          BST_ERR_INVALID_PTR );

    *pMsg                               = BST_NULL_PTR;

    if( (BST_UINT32)BST_OS_SYS_FOREVER == ulExTime )
    {
        ulPendTime                      = (BST_UINT32)BST_OS_SYS_FOREVER;
    }
    else if( ulExTime < BST_OS_TICKS_MS )
    {
        ulPendTime                      = BST_OS_TICKS_MS;
    }
    else
    {
        ulPendTime                      = ulExTime;
    }

    ulPastTime = BST_OS_RecvSem( pstMbx->hSem, ulPendTime );

    if( BST_OS_SYS_TIMEOUT == ulPastTime )
    {
        return BST_OS_SYS_TIMEOUT;
    }

    tThreadLockCnt                      = (BST_OS_LOCKCNT_T)BST_OS_SpinLock( &g_MboxLock );

    pstContent                          = (BST_OS_MAIL_T *)lstGet( &pstMbx->hList );


    if ( BST_NULL_PTR == pstContent )
    {
       *pMsg                           = BST_NULL_PTR;
        BST_OS_SpinUnLock( &g_MboxLock, (BST_UINT32)tThreadLockCnt );
        return BST_OS_SYS_TIMEOUT;
    }
    *pMsg                               = pstContent->ulContent;

    BST_OS_FREE( pstContent );
    BST_OS_SpinUnLock( &g_MboxLock, (BST_UINT32)tThreadLockCnt );
    /*lint -e438*/
    return( ulPastTime );
    /*lint +e438*/
}

BST_ERR_ENUM_UINT8 BST_OS_DeleteMbx( BST_OS_MBX_T *pstMbx )
{
    BST_OS_MAIL_T                     *pstContent;
    BST_OS_LOCKCNT_T                    tThreadLockCnt;

    BST_ASSERT_NULL_RTN( pstMbx,        BST_ERR_INVALID_PTR );
    BST_ASSERT_NULL_RTN( pstMbx->hSem,  BST_ERR_INVALID_PTR );

    BST_OS_DeleteSem( pstMbx->hSem );

    tThreadLockCnt                      = BST_OS_ThreadLock();    
    for (;;)
    {
        if( 0 == lstCount( &pstMbx->hList ) )
        {
            break;
        }
        pstContent                      = (BST_OS_MAIL_T *)lstGet( &pstMbx->hList );
        BST_OS_FREE( pstContent );
    }

    lstFree( &pstMbx->hList);
    
    BST_OS_FREE( pstMbx );

    BST_OS_ThreadUnLock( tThreadLockCnt );
/*lint -e438*/
    return( BST_NO_ERROR_MSG );
/*lint +e438*/
}


BST_UINT32 BST_OS_GetMailAmount( BST_OS_MBX_T *pstMbx )
{
    BST_ASSERT_NULL_RTN( pstMbx,        0U );
    BST_ASSERT_NULL_RTN( pstMbx->hSem,  0U );
    return( (BST_UINT32)lstCount( &pstMbx->hList ) );
}


BST_UINT32 BST_OS_PeekMail( BST_OS_MBX_T *pstMbx, BST_VOID **pMsg )
{
    BST_OS_MAIL_T                      *pstContent;
    BST_OS_LOCKCNT_T                    tThreadLockCnt;

    BST_ASSERT_NULL_RTN( pstMbx,        BST_ERR_INVALID_PTR );
    BST_ASSERT_NULL_RTN( pstMbx->hSem,  BST_ERR_INVALID_PTR );
    BST_ASSERT_NULL_RTN( pMsg,          BST_ERR_INVALID_PTR );

    *pMsg                               = BST_NULL_PTR;

    if( BST_OS_SYS_TIMEOUT == BST_OS_RecvSem( pstMbx->hSem, BST_OS_SYS_NOWAIT ) )
    {
        return BST_OS_SYS_TIMEOUT;
    }

    tThreadLockCnt                      = BST_OS_ThreadLock();

    pstContent                          = (BST_OS_MAIL_T *)lstGet( &pstMbx->hList );

    if ( BST_NULL_PTR == pstContent )        
    {
        BST_OS_ThreadUnLock( tThreadLockCnt );
        return BST_OS_SYS_TIMEOUT;
    }
    *pMsg                               = pstContent->ulContent;
#ifdef BST_OS_SIGNAL_COUNTER
    if ( pstMbx->hSem->ulCounter > 0U )
    {
        pstMbx->hSem->ulCounter--;
    }
#endif
    BST_OS_FREE( pstContent );
    BST_OS_ThreadUnLock( tThreadLockCnt );
    /*lint -e438*/
    return( BST_NO_ERROR_MSG );
    /*lint +e438*/
}

