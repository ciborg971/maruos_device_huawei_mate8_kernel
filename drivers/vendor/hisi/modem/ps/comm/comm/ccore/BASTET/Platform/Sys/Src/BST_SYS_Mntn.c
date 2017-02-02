


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "BST_SYS_Mntn.h"
#include "BST_OS_Thread.h"

/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_BST_SYSMNTN_C
/*lint +e767*/

/*****************************************************************************
  2 �ⲿ��������
*****************************************************************************/
BST_OS_MBX_T   *BST_SRV_GetSysMsgHandle( BST_VOID );

/******************************************************************************
   3 ˽�ж���
******************************************************************************/
BST_VOID BST_SYS_MntnTimerExpired(
    BST_OS_TIMERID_T                ulTimerId,
    BST_VOID                       *pvArg );

BST_UINT32 BST_SYS_MntnBuildAgentInfoInd(
    OM_BST_APP_INFO_STRU           *pstAgentInfo,
    const BST_UINT16                usAppNumber );

BST_UINT8* BST_SYS_MntnGetSendExternalMsgBuffAddr(
    BST_UINT32                      ulPid,
    BST_UINT32                      ulBuffSize );

OM_BST_APP_INFO_STRU *BST_SYS_MntnSrchAppByTask(
    BST_UINT16                      usType,
    BST_UINT16                      usTaskId );

OM_BST_APP_INFO_STRU *BST_SYS_MntnSrchAppByPort(
    BST_UINT16                      usLocalPortNumber );

BST_VOID BST_SYS_MntnChangedInd( BST_VOID );

BST_VOID BST_SYS_MntnTrigReport( BST_VOID );

/******************************************************************************
   4 ȫ�ֱ�������
******************************************************************************/
BST_STATIC  BST_SYS_MNTN_ENTITY_STRU        g_stBstMntnEntity;
/******************************************************************************
   5 ����ʵ��
******************************************************************************/


BST_VOID BST_SYS_MntnInit( BST_VOID )
{
    BST_OS_LOCKCNT_T                    tThreadLockCnt;

    tThreadLockCnt                      = BST_OS_ThreadLock();
    g_stBstMntnEntity.stReportTimer     = BST_OS_TimerCreate
                                        ( BST_SYS_MntnTimerExpired,
                                          BST_NULL_PTR,
                                          BST_SRV_GetSysMsgHandle() );
    lstInit( &g_stBstMntnEntity.stAppList );
    BST_OS_MEMSET( &g_stBstMntnEntity.aucLocalIp[0],
                   0, OM_BST_IP_ADDR_LEN );
    g_stBstMntnEntity.ucChanged         = BST_FALSE;
    g_stBstMntnEntity.ucIsInit          = BST_TRUE;
    BST_RLS_LOG( "[Mntn] Initial System" );
    BST_OS_ThreadUnLock( tThreadLockCnt );
    return;
}



BST_VOID BST_SYS_MntnCofigLoacalIpAddress(
    BST_UINT8      *aucLocalIp,
    BST_UINT16      usBufLen )
{
    if ( BST_NULL_PTR == aucLocalIp )
    {
        BST_RLS_LOG( "[Mntn] BST_SYS_MntnCofigLoacalIpAddress Error Pointer" );
        return;
    }
    if ( OM_BST_IP_ADDR_LEN > usBufLen )
    {
        BST_RLS_LOG1( "[Mntn] BST_SYS_MntnCofigLoacalIpAddress Error Size:", usBufLen );
        return;
    }
    BST_OS_MEMCPY( &g_stBstMntnEntity.aucLocalIp[0],
                   aucLocalIp, OM_BST_IP_ADDR_LEN );
    return;
}


BST_VOID BST_SYS_MntnChangedInd( BST_VOID )
{
    BST_SYS_MNTN_SetMntnMsgChgFlag();

    if ( BST_TRUE == BST_OS_TimerIsStop( BST_SYS_MNTN_GetTimerId() ) )
    {
        BST_OS_TimerStart( BST_SYS_MNTN_GetTimerId(),
                           BST_SYS_MNTN_REPORT_TIMER_LEN );
    }
    return;
}


BST_VOID BST_SYS_MntnAddTask(
    BST_UINT16  usType,
    BST_UINT16  usTaskId )
{
    BST_SYS_MNTN_APP_NODE_STRU             *pstAppInfoNode;
    BST_OS_LOCKCNT_T                    tThreadLockCnt;

    if ( !BST_SYS_MNTN_IsMntnInited() )
    {
        return;
    }

    if ( (BST_UINT32)BST_SYS_MNTN_GetAppNumber() >= BST_SYS_MNTN_MAX_APP_NUMBER )
    {
        return;
    }

    tThreadLockCnt                      = BST_OS_ThreadLock();
    if ( BST_NULL_PTR != BST_SYS_MntnSrchAppByTask( usType, usTaskId ) )
    {
        BST_OS_ThreadUnLock( tThreadLockCnt );
        return;
    }
    pstAppInfoNode                      = ( BST_SYS_MNTN_APP_NODE_STRU *)BST_OS_MALLOC
                                          ( BST_OS_SIZEOF(BST_SYS_MNTN_APP_NODE_STRU) );
    if ( BST_NULL_PTR == pstAppInfoNode )
    {
        BST_OS_ThreadUnLock( tThreadLockCnt );
        return;
    }
    BST_OS_MEMSET( &(pstAppInfoNode->stAppInfo),
                   0,
                   BST_OS_SIZEOF(OM_BST_APP_INFO_STRU) );

    pstAppInfoNode->stAppInfo.usAppType = usType;
    pstAppInfoNode->stAppInfo.usTaskId  = usTaskId;

    lstAdd( BST_SYS_MNTN_GetAppListHead(), (NODE *)pstAppInfoNode );
    BST_RLS_LOG3( "[Mntn] Add Task: TypeId=, TaskId=, Total=",
                  usType, usTaskId, BST_SYS_MNTN_GetAppNumber() );
    BST_SYS_MntnChangedInd();
    BST_OS_ThreadUnLock( tThreadLockCnt );
/*lint -e429*/
}
/*lint +e429*/

BST_VOID BST_SYS_MntnUpdateState(
    BST_UINT16  usType,
    BST_UINT16  usTaskId,
    BST_UINT16  usState )
{
    OM_BST_APP_INFO_STRU               *pstAppInfo;
    BST_OS_LOCKCNT_T                    tThreadLockCnt;

    if ( !BST_SYS_MNTN_IsMntnInited() )
    {
        return;
    }
    tThreadLockCnt                      = BST_OS_ThreadLock();
    pstAppInfo                          = BST_SYS_MntnSrchAppByTask( usType, usTaskId );
    if ( BST_NULL_PTR == pstAppInfo )
    {
        BST_OS_ThreadUnLock( tThreadLockCnt );
        return;
    }
    pstAppInfo->usTaskState = usState;
    BST_RLS_LOG3( "[Mntn] State Updated: TypeId=, TaskId=, NewState=",
                  usType, usTaskId, usState );
    BST_SYS_MntnChangedInd();
    BST_OS_ThreadUnLock( tThreadLockCnt );
}


BST_VOID BST_SYS_MntnUpdateIpInfo(
    BST_UINT16  usType,
    BST_UINT16  usTaskId,
    BST_VOID   *pstIpInfo )
{
    OM_BST_APP_INFO_STRU               *pstAppInfo;
    BST_IP_SOCKET_ADD_T                *pstSocketInfo;
    BST_OS_LOCKCNT_T                    tThreadLockCnt;

    if ( !BST_SYS_MNTN_IsMntnInited() )
    {
        return;
    }
    if ( BST_NULL_PTR == pstIpInfo )
    {
        return;
    }
    pstSocketInfo                       = ( BST_IP_SOCKET_ADD_T *)pstIpInfo;
    tThreadLockCnt                      = BST_OS_ThreadLock();
    pstAppInfo                          = BST_SYS_MntnSrchAppByTask( usType, usTaskId );
    if ( BST_NULL_PTR == pstAppInfo )
    {
        BST_OS_ThreadUnLock( tThreadLockCnt );
        return;
    }

    pstAppInfo->usLocalPort             = pstSocketInfo->usLocalPort;
    pstAppInfo->usRemotePort            = pstSocketInfo->usRemotePort;

    BST_OS_MEMCPY( &pstAppInfo->aucLocalIp[0],
                   BST_SYS_MNTN_GetLocalIpHead(), OM_BST_IP_ADDR_LEN );

    BST_OS_MEMCPY( &pstAppInfo->aucRemoteIp[0],
                   &pstSocketInfo->aucRemoteIp[0], OM_BST_IP_ADDR_LEN );

    BST_RLS_LOG4( "[Mntn] Socket Configed_01: TypeId=, TaskId=, LocalPort=, RemotePort=",
            usType, usTaskId, (pstSocketInfo)->usLocalPort, (pstSocketInfo)->usRemotePort );

    BST_RLS_LOG4( "[Mntn] Socket Configed_02: Remote Ip Address",
            (pstAppInfo)->aucRemoteIp[3], (pstAppInfo)->aucRemoteIp[2],
            (pstAppInfo)->aucRemoteIp[1], (pstAppInfo)->aucRemoteIp[0]);

    BST_RLS_LOG4( "[Mntn] Socket Configed_02: Local Ip Address",
            (pstAppInfo)->aucLocalIp[3], (pstAppInfo)->aucLocalIp[2],
            (pstAppInfo)->aucLocalIp[1], (pstAppInfo)->aucLocalIp[0]);

    BST_SYS_MntnChangedInd();
    BST_OS_ThreadUnLock( tThreadLockCnt );
}


BST_VOID BST_SYS_MntnUpdateCycleLen(
    BST_UINT16  usType,
    BST_UINT16  usTaskId,
    BST_UINT16  usCycleLen )
{
    OM_BST_APP_INFO_STRU               *pstAppInfo;
    BST_OS_LOCKCNT_T                    tThreadLockCnt;

    if ( !BST_SYS_MNTN_IsMntnInited() )
    {
        return;
    }
    tThreadLockCnt                      = BST_OS_ThreadLock();
    pstAppInfo                          = BST_SYS_MntnSrchAppByTask( usType, usTaskId );
    if ( BST_NULL_PTR == pstAppInfo )
    {
        BST_OS_ThreadUnLock( tThreadLockCnt );
        return;
    }

    pstAppInfo->usCycleLen              = usCycleLen;
    BST_RLS_LOG3("[Mntn] Periodic Configed: TypeId=, TaskId=, Cycle=",
                 usType, usTaskId, usCycleLen );
    BST_SYS_MntnChangedInd();
    BST_OS_ThreadUnLock( tThreadLockCnt );
}


BST_VOID BST_SYS_MntnUpdateSuccNum(
    BST_UINT16  usType,
    BST_UINT16  usTaskId )
{
    OM_BST_APP_INFO_STRU               *pstAppInfo;
    BST_OS_LOCKCNT_T                    tThreadLockCnt;

    if ( !BST_SYS_MNTN_IsMntnInited() )
    {
        return;
    }
    tThreadLockCnt                      = BST_OS_ThreadLock();
    pstAppInfo                          = BST_SYS_MntnSrchAppByTask( usType, usTaskId );
    if ( BST_NULL_PTR == pstAppInfo )
    {
        BST_OS_ThreadUnLock( tThreadLockCnt );
        return;
    }

    pstAppInfo->usSuccNum++;
    BST_RLS_LOG3("[Mntn] Task Run Success: TypeId=, TaskId=",
                 usType, usTaskId, pstAppInfo->usSuccNum );
    BST_SYS_MntnChangedInd();
    BST_OS_ThreadUnLock( tThreadLockCnt );
}


BST_VOID BST_SYS_MntnUpdateErrorNum(
    BST_UINT16  usType,
    BST_UINT16  usTaskId )
{
    OM_BST_APP_INFO_STRU               *pstAppInfo;
    BST_OS_LOCKCNT_T                    tThreadLockCnt;

    if ( !BST_SYS_MNTN_IsMntnInited() )
    {
        return;
    }
    tThreadLockCnt                      = BST_OS_ThreadLock();
    pstAppInfo                          = BST_SYS_MntnSrchAppByTask( usType, usTaskId );
    if ( BST_NULL_PTR == pstAppInfo )
    {
        BST_OS_ThreadUnLock( tThreadLockCnt );
        return;
    }

    pstAppInfo->usErrorNum++;
    BST_RLS_LOG3("[Mntn] Task Run Fail: TypeId=, TaskId=",
                 usType, usTaskId, pstAppInfo->usErrorNum );
    BST_SYS_MntnChangedInd();
    BST_OS_ThreadUnLock( tThreadLockCnt );
}


BST_VOID BST_SYS_MntnUpdateTxFlow(
    BST_UINT16  usLocalPort,
    BST_UINT32  ulTxFlow )
{
    OM_BST_APP_INFO_STRU               *pstAppInfo;
    BST_OS_LOCKCNT_T                    tThreadLockCnt;

    if ( !BST_SYS_MNTN_IsMntnInited() )
    {
        return;
    }
    tThreadLockCnt                      = BST_OS_ThreadLock();
    pstAppInfo                          = BST_SYS_MntnSrchAppByPort( usLocalPort );
    if ( BST_NULL_PTR == pstAppInfo )
    {
        BST_OS_ThreadUnLock( tThreadLockCnt );
        return;
    }

    pstAppInfo->ulTxFlow               += ulTxFlow;
    pstAppInfo->ulTxFlow               &= BST_SYS_MNTN_MAX_TRAFFIC_FLOW;
    BST_RLS_LOG4( "[Mntn] Local Port Tx Flow New:  TypeId=, TaskId=, PortNumber=, TrafficeFlow=",
                  pstAppInfo->usAppType, pstAppInfo->usTaskId, usLocalPort, ulTxFlow );
    BST_OS_ThreadUnLock( tThreadLockCnt );
}


BST_VOID BST_SYS_MntnUpdateRxFlow(
    BST_UINT16  usLocalPort,
    BST_UINT32  ulRxFlow )
{
    OM_BST_APP_INFO_STRU               *pstAppInfo;
    BST_OS_LOCKCNT_T                    tThreadLockCnt;

    if ( !BST_SYS_MNTN_IsMntnInited() )
    {
        return;
    }
    tThreadLockCnt                      = BST_OS_ThreadLock();
    pstAppInfo                          = BST_SYS_MntnSrchAppByPort( usLocalPort );
    if ( BST_NULL_PTR == pstAppInfo )
    {
        BST_OS_ThreadUnLock( tThreadLockCnt );
        return;
    }

    pstAppInfo->ulRxFlow               += ulRxFlow;
    pstAppInfo->ulRxFlow               &= BST_SYS_MNTN_MAX_TRAFFIC_FLOW;
    BST_RLS_LOG4( "[Mntn] Local Port Rx Flow New:  TypeId=, TaskId=, PortNumber=, TrafficeFlow=",
                  pstAppInfo->usAppType, pstAppInfo->usTaskId, usLocalPort, ulRxFlow );
    BST_OS_ThreadUnLock( tThreadLockCnt );
}


BST_VOID BST_SYS_MntnRemoveTask(
    BST_UINT16  usType,
    BST_UINT16  usTaskId )
{
    BST_SYS_MNTN_APP_NODE_STRU             *pstAppNode;
    BST_OS_LOCKCNT_T                    tThreadLockCnt;

    if ( !BST_SYS_MNTN_IsMntnInited() )
    {
        return;
    }
    tThreadLockCnt                      = BST_OS_ThreadLock();
    /* �����������Ƿ��Ѿ����ڸ�Task��Ϣ */
    for ( pstAppNode = ( BST_SYS_MNTN_APP_NODE_STRU *)lstFirst(BST_SYS_MNTN_GetAppListHead());
          pstAppNode != BST_NULL_PTR;
          pstAppNode = ( BST_SYS_MNTN_APP_NODE_STRU *)lstNext( (NODE *)pstAppNode ) )
    {
        if ( ( usTaskId == pstAppNode->stAppInfo.usTaskId )
          && ( usType == pstAppNode->stAppInfo.usAppType ) )
        {
            break;
        }
    }

    if ( BST_NULL_PTR == pstAppNode )
    {
        BST_OS_ThreadUnLock( tThreadLockCnt );
        return;
    }

    lstDelete( BST_SYS_MNTN_GetAppListHead(), (NODE *)pstAppNode );
    BST_OS_FREE( pstAppNode );
    BST_RLS_LOG3( "[Mntn] Remove Task: TypeId=, TaskId=, Total=",
                  usType, usTaskId, BST_SYS_MNTN_GetAppNumber() );
    BST_SYS_MntnChangedInd();
    BST_OS_ThreadUnLock( tThreadLockCnt );
/*lint -e438*/
}
/*lint +e438*/

BST_UINT32 BST_SYS_MntnBuildAgentInfoInd(
    OM_BST_APP_INFO_STRU   *pstAgentInfo,
    const BST_UINT16        usAppNumber )
{
    BST_SYS_MNTN_APP_NODE_STRU             *pstAppNode;
    BST_UINT16                          usAppCounter;
    BST_OS_LOCKCNT_T                    tThreadLockCnt;

    if ( BST_NULL_PTR == pstAgentInfo )
    {
        return BST_FALSE;
    }

    tThreadLockCnt                      = BST_OS_ThreadLock();
    usAppCounter                        = 0;
    /* �����������Ƿ��Ѿ����ڸ�Task��Ϣ */
    for ( pstAppNode = ( BST_SYS_MNTN_APP_NODE_STRU *)lstFirst(BST_SYS_MNTN_GetAppListHead());
          pstAppNode != BST_NULL_PTR;
          pstAppNode = ( BST_SYS_MNTN_APP_NODE_STRU *)lstNext( (NODE *)pstAppNode ) )
    {
        if ( ID_BST_OM_TASK_TYPE_MAIN == pstAppNode->stAppInfo.usAppType )
        {
            continue;
        }

        BST_OS_MEMCPY( &pstAgentInfo[usAppCounter],
                       &(pstAppNode->stAppInfo),
                       BST_OS_SIZEOF(OM_BST_APP_INFO_STRU) );
        usAppCounter++;
        if ( usAppCounter >= usAppNumber )
        {
            break;
        }
    }
    BST_OS_ThreadUnLock( tThreadLockCnt );
    return BST_TRUE;
}
BST_UINT8* BST_SYS_MntnGetSendExternalMsgBuffAddr( BST_UINT32  ulPid,
                                                   BST_UINT32  ulBuffSize )
{
    BST_VOID                   *pMsgBuff;

    BST_ALLOC_MSG(ulPid, pMsgBuff, ulBuffSize);

    if( BST_NULL_PTR == pMsgBuff )
    {
        BST_DBG_LOG1("BST_SYS_MNTN_BuildMntnAgentInfoInd, Alloc Msg Buff Fail, buffersize",
                     ulBuffSize);
        return BST_NULL_PTR;
    }

    return (BST_UINT8 *)pMsgBuff;
}


BST_VOID BST_SYS_MntnTrigReport( BST_VOID )
{
    OM_BST_MSG_STRU                    *pstBstOmIndMsg;
    OM_BST_AGENT_APP_NUM_STRU          *pstBstAppNum;
    BST_UINT32                          ulRslt;
    BST_UINT32                          ulLength;
    BST_UINT16                          usAppNum;
    OM_BST_APP_INFO_STRU               *pstAppInfo;
    DIAG_TRANS_IND_STRU                 stTransData;
    MODEM_ID_ENUM_UINT16                enModemId;

    ulRslt                              = BST_TRUE;

    /* ����Ĵ�С������ϢͷBST_OM_MSG_STRU -4���ֽڵ�ָ��ռλ + ʵ�ʴ�����Ϣ��С */
    usAppNum                            = (BST_UINT16)BST_SYS_MNTN_GetAppNumber();
    ulLength                            = (BST_OS_SIZEOF(OM_BST_MSG_STRU) - 4)
                                          + (BST_OS_SIZEOF(OM_BST_AGENT_APP_NUM_STRU));
    pstBstOmIndMsg                      = (OM_BST_MSG_STRU *)BST_SYS_MntnGetSendExternalMsgBuffAddr(UEPS_PID_BASTET, ulLength);
    if (BST_NULL_PTR == pstBstOmIndMsg)
    {
        BST_DBG_LOG1("BST_SYS_MntnTrigReport, Agent Info Msg Alloc Mem Fail",
                      0);
        return;
    }

    pstBstAppNum                        = (OM_BST_AGENT_APP_NUM_STRU *)(pstBstOmIndMsg->aucData);
    pstBstAppNum->usAgentAppNum         = usAppNum;
    pstAppInfo                          = ( (OM_BST_APP_INFO_STRU *)(pstBstAppNum->stBstAppList ) );

    ulRslt                              = BST_SYS_MntnBuildAgentInfoInd( pstAppInfo, usAppNum );

    if (BST_TRUE != ulRslt)
    {
        BST_DBG_LOG1("BST_SYS_MntnTrigReport, Get Bst Agent Info Error: ulRslt",
                      ulRslt);

        /* �ͷŴ������Ϣ�� */
        BST_FREE_MSG( UEPS_PID_BASTET, pstBstOmIndMsg );

        return;
    }

    pstBstOmIndMsg->usPrimId    = ID_BST_OM_AGENT_INFO_IND;
    pstBstOmIndMsg->usToolId    = 0;

    enModemId                   = VOS_GetModemIDFromPid(UEPS_PID_BASTET);

    /* �����Ϣ */
    stTransData.ulPid           = UEPS_PID_BASTET;
    stTransData.ulMsgId         = ID_BST_OM_AGENT_INFO_IND;
    stTransData.ulModule        = DIAG_GEN_MODULE(enModemId, DIAG_MODE_UMTS);
    stTransData.ulLength        = ulLength;
    stTransData.pData           = (VOS_VOID *)pstBstOmIndMsg;

    if ( VOS_OK != DIAG_TransReport((DIAG_TRANS_IND_STRU *)&stTransData) )
    {
        BST_RLS_LOG( "[Mntn] Send Maintain Message Fail:" );
    }
    else
    {
        BST_RLS_LOG( "[Mntn] Send Maintain Message Success" );
    }

    /* �ͷŴ������Ϣ�� */
    BST_FREE_MSG( UEPS_PID_BASTET, pstBstOmIndMsg );

    return;
}

OM_BST_APP_INFO_STRU *BST_SYS_MntnSrchAppByTask(
    BST_UINT16                      usType,
    BST_UINT16                      usTaskId )
{
    BST_SYS_MNTN_APP_NODE_STRU             *pstAppNode;

    /* �����������Ƿ��Ѿ����ڸ�Task��Ϣ */
    for ( pstAppNode = ( BST_SYS_MNTN_APP_NODE_STRU *)lstFirst(BST_SYS_MNTN_GetAppListHead());
          pstAppNode != BST_NULL_PTR;
          pstAppNode = ( BST_SYS_MNTN_APP_NODE_STRU *)lstNext( (NODE *)pstAppNode ) )
    {
        if ( ( usTaskId == pstAppNode->stAppInfo.usTaskId )
          && ( usType == pstAppNode->stAppInfo.usAppType ) )
        {
            return &pstAppNode->stAppInfo;
        }
    }
    return BST_NULL_PTR;
}
OM_BST_APP_INFO_STRU *BST_SYS_MntnSrchAppByPort( BST_UINT16 usLocalPortNumber )
{
    BST_SYS_MNTN_APP_NODE_STRU             *pstAppNode;
    /* �����������Ƿ��Ѿ����ڸ�Port��Ϣ */
    for ( pstAppNode = ( BST_SYS_MNTN_APP_NODE_STRU *)lstFirst(BST_SYS_MNTN_GetAppListHead());
          pstAppNode != BST_NULL_PTR;
          pstAppNode = ( BST_SYS_MNTN_APP_NODE_STRU *)lstNext( (NODE *)pstAppNode ) )
    {
        if ( usLocalPortNumber == pstAppNode->stAppInfo.usLocalPort )
        {
            return &pstAppNode->stAppInfo;
        }
    }
    return BST_NULL_PTR;
}
BST_VOID BST_SYS_MntnTimerExpired(
    BST_OS_TIMERID_T                ulTimerId,
    BST_VOID                       *pvArg )
{
    if ( BST_SYS_MNTN_IsMntnMsgChanged() )
    {
        BST_SYS_MNTN_ClrMntnMsgChgFlag();
        BST_OS_TimerStart( BST_SYS_MNTN_GetTimerId(),
                           BST_SYS_MNTN_REPORT_TIMER_LEN );
    }
    else
    {
        BST_RLS_LOG( "[Mntn] Send Maintain Message Triged" );
        BST_SYS_MntnTrigReport();
    }
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



