

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "lwip/tcp.h"
#include "BST_IP_PreProc.h"
#include "BST_APP_Define.h"
#include "BST_Platform.h"
#include "BST_OS_Memory.h"
#include "BST_OS_Thread.h"
#include "BST_OS_Timer.h"
#include "BST_DRV_Net.h"
#include "BST_DRV_As.h"
#include "lwip/sockets.h"
#include "lwip/tcp_impl.h"
#include "lwip/memp.h"
#include "BST_SRV_Event.h"

/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_BST_IP_PREPROC_C
/*lint +e767*/
/*****************************************************************************
  2 �ⲿ��������
*****************************************************************************/
#ifdef BST_MODEM_SELF
extern BST_VOID DSPP_TEST_EMAIL( BST_UINT32 ulIpAddr );
#endif
/******************************************************************************
   3 ˽�ж���
******************************************************************************/
BST_STATIC BST_ERR_ENUM_UINT8 BST_IP_ParseRubbish( 
    const BST_UINT8           aucPkt[],
    const BST_UINT32          ulPktLen );

BST_STATIC BST_ERR_ENUM_UINT8 BST_IP_ProcRubbish(
    const BST_IP_IPHDR_STRU  *pstIpHdr,
    const BST_IP_TCPHDR_STRU *pstTcpHdr,
    BST_UINT16                usTotLen );

BST_STATIC BST_ERR_ENUM_UINT8 BST_IP_ProcFinRubbish(
    const BST_IP_TCPHDR_STRU   *pstTcpHdr,
    const BST_IP_IPHDR_STRU    *pstIpHdr,
    const BST_INT32             lTcpLen );

BST_STATIC BST_ERR_ENUM_UINT8 BST_IP_ProcPshRubbish(
    const BST_UINT8             aucPkt[],
    const BST_UINT32            ulPktLen,
    BST_NETIF_T                *pstNetIf );

/******************************************************************************
   4 ȫ�ֱ�������
******************************************************************************/
LIST                                    g_stBstPortPreprocList;
BST_IP_FAST_CHECK_STRU                  g_stBstIpFastPortCheck  = {0};
BST_OS_SPINLOCK_T                       g_BstPreprocSpinLock;
BST_OS_SPINLOCK_T                       g_BstRegistSpinLock;
BST_OS_SPINLOCK_T                       g_BstTotFlowSpinLock;
BST_OS_TIMERID_T                        g_BstPreprocFreeTimer    = BST_INVALID_SNID;
BST_OS_TIMERID_T                        g_BstPreprocFdTimer      = BST_INVALID_SNID;
const  BST_IP_SKT_PROPTY_STRU           g_stDefaultSocktProperty = {0u,0u,0u,0u,0u,0u,0u};
BST_UINT32                              g_ulTrafficFlowCounter   = 0;
BST_UINT32                              g_ulMirroredTimeStamp    = 0;
extern sys_mbox_t                       mbox;
/******************************************************************************
   5 ����ʵ��
******************************************************************************/


BST_VOID BST_IP_PreprocTimerCb( BST_OS_TIMERID_T ulTimerId, BST_VOID* pvArg )
{
    if( ulTimerId != g_BstPreprocFreeTimer )
    {
        return;
    }
    BST_DBG_LOG("Force Cleaning All unuseful Packet");
    BST_IP_ClearAllPkt();
}

/*****************************************************************************
�� �� ��  :
��������  :
�������  :
�������  :
�� �� ֵ  :
���ú���  :
��������  :

�޸���ʷ  :
1.����    :
  ����    :
  �޸�����:
*****************************************************************************/
BST_VOID BST_IP_FdTimerCb( BST_OS_TIMERID_T ulTimerId, BST_VOID* pvArg )
{
    BST_DRV_STRU                       *pAsDrvHandle;
    if( ulTimerId != g_BstPreprocFdTimer )
    {
        BST_RLS_LOG2( "BST_IP_FdTimerCb ulTimerId=%u, g_BstPreprocFdTimer=%u",
                      ulTimerId, g_BstPreprocFdTimer );
        return;
    }
    pAsDrvHandle                        = BST_DRV_AsGetDvcHandle();
    if( BST_NULL_PTR == pAsDrvHandle->pfIoCtrl )
    {
        return;
    }
    pAsDrvHandle->pfIoCtrl( BST_DRV_CMD_RELEASE_RRC, BST_NULL_PTR );
    BST_RLS_LOG( "Rubbish Proc Release RRC of 4G" );
}


BST_VOID BST_IP_ApiInitPortPreproc( BST_VOID )
{
    BST_OS_LOCKCNT_T                    tThreadLockCnt;

    tThreadLockCnt                      = BST_OS_ThreadLock();
    BST_OS_InitSpinLock( &g_BstPreprocSpinLock );
    BST_OS_InitSpinLock( &g_BstTotFlowSpinLock );
    BST_OS_InitSpinLock( &g_BstRegistSpinLock );
    g_BstPreprocFreeTimer               = BST_OS_TimerCreate
                                        ( BST_IP_PreprocTimerCb,
                                          BST_NULL_PTR,
                                          mbox );
    g_BstPreprocFdTimer                 = BST_OS_TimerCreate
                                        ( BST_IP_FdTimerCb,
                                          BST_NULL_PTR,
                                          mbox );
    lstInit( BST_IP_GetPreprocLstHead() );
    g_stBstIpFastPortCheck.lCnt         = 0;
    BST_OS_MEMSET( &g_stBstIpFastPortCheck.ausPortNum[0], (BST_INT32)BST_INVALID_PORT, BST_MAX_CNNT_NUMBER );
    BST_OS_ThreadUnLock( tThreadLockCnt );
}


/*lint -e438*/
/*����ǳ����ӣ���ô������Connect֮ǰ��Ӷ˿�*/
BST_VOID *BST_IP_ApiAddPort( BST_IP_PROTOCOL_TYPE usProtocol, BST_UINT16 usPortNum )
{
    BST_IP_PORT_PREPROC_STRU           *pstPortPreproc;
    LIST                               *pstPktList;
    BST_UINT32                          ulSpinlockCnt;

    if( !BST_IP_IsPortValid( usPortNum ) )
    {
        return BST_NULL_PTR;
    }
    pstPortPreproc                      = BST_NULL_PTR;
    ulSpinlockCnt                       = BST_OS_SpinLock( &g_BstPreprocSpinLock );
    pstPortPreproc                      = ( BST_IP_PORT_PREPROC_STRU *)lstFirst( BST_IP_GetPreprocLstHead() );
    /*�����������Ƿ��Ѿ����ڸ�Port��Ϣ*/
    for(;;)
    {
        if( BST_NULL_PTR == pstPortPreproc )
        {
            break;
        }
        if( ( usPortNum == pstPortPreproc->usPortNum )
          &&( usProtocol== pstPortPreproc->usProtocol ) )
        {
            /*����˿��Ѿ����ڣ���ô���³�ʼ��������*/
            BST_IP_ClearPortPkt( pstPortPreproc );

            if ( BST_IP_PORT_STATE_WORKING == pstPortPreproc->enState )
            {
                pstPortPreproc->enState = BST_IP_PORT_STATE_STOPED;
                pstPortPreproc->ucPathMode
                                        = BST_IP_PATH_MODE_SINGLE;
                BST_IP_UpdateFCT();
            }

            BST_OS_SpinUnLock( &g_BstPreprocSpinLock , ulSpinlockCnt );

            BST_DBG_LOG1("BST_IP_ApiAddPort already existed usPortNum:%u", usPortNum);

            return pstPortPreproc;
        }
        pstPortPreproc                   = ( BST_IP_PORT_PREPROC_STRU *)lstNext( (NODE *)pstPortPreproc );
    }

    pstPortPreproc                       = BST_OS_MALLOC( BST_OS_SIZEOF(BST_IP_PORT_PREPROC_STRU) );
    if ( BST_NULL_PTR == pstPortPreproc )
    {
        BST_OS_SpinUnLock( &g_BstPreprocSpinLock , ulSpinlockCnt );
        return BST_NULL_PTR;
    }

    pstPktList                           = BST_OS_MALLOC( BST_OS_SIZEOF(LIST) );
    if ( BST_NULL_PTR == pstPktList )
    {
        BST_OS_FREE( pstPortPreproc );
        BST_OS_SpinUnLock( &g_BstPreprocSpinLock , ulSpinlockCnt );
        return BST_NULL_PTR;
    }
    pstPortPreproc->enState              = BST_IP_PORT_STATE_STOPED;
    pstPortPreproc->usPortNum            = usPortNum;
    pstPortPreproc->usProtocol           = usProtocol;
    pstPortPreproc->ucPathMode           = BST_IP_PATH_MODE_SINGLE;
    pstPortPreproc->pstPktList           = pstPktList;
    pstPortPreproc->stLastSktProperty    = BST_IP_DEFAULT_SKT_PROPERTY;
    lstInit( pstPortPreproc->pstPktList );
    lstAdd( BST_IP_GetPreprocLstHead(), (NODE *)pstPortPreproc);
    BST_OS_SpinUnLock( &g_BstPreprocSpinLock , ulSpinlockCnt);
    BST_DBG_LOG1("BST_IP_ApiAddPort success usPortNum:%u", usPortNum);
    return pstPortPreproc;
}

/*lint -e438*/
BST_VOID BST_IP_ApiRmvPort(
    BST_IP_PROTOCOL_TYPE        usProtocol,
    BST_UINT16                  usPortNum,
    BST_IP_TRAFFIC_FLOW_STRU   *pstFlowOutput )
{
    BST_IP_PORT_PREPROC_STRU           *pstPortPreproc;

    pstPortPreproc                      = BST_IP_SrchPreprocByPort( usProtocol, usPortNum );

    BST_DBG_LOG2( "BST_IP_ApiRmvPort usProtocol=%u, usPortNum=%u",
                  usProtocol, usPortNum );
    /*���û���ҵ�����ô֤���Ѿ�ɾ����ֱ�ӷ��سɹ�*/
    if( BST_NULL_PTR == pstPortPreproc )
    {
        BST_RLS_LOG( "BST_IP_ApiRmvPort BST_IP_SrchPreprocByPort is NULL." );
        return;
    }

    lstDelete( BST_IP_GetPreprocLstHead(), (NODE *) pstPortPreproc);

    /*ɾ����������ÿ�����ݰ����������ڴ�ռ�*/
    BST_IP_ClearPortPkt( pstPortPreproc );
    if ( BST_NULL_PTR != pstFlowOutput )
    {
        pstFlowOutput->ulRxByte         = pstPortPreproc->stLastSktProperty.ulRxByte;
        pstFlowOutput->ulTxByte         = pstPortPreproc->stLastSktProperty.ulTxByte;
    }
    BST_OS_FREE( pstPortPreproc->pstPktList );
    BST_OS_FREE( pstPortPreproc );
    BST_IP_UpdateFCT();
}
/*lint +e438*/

BST_UINT32 BST_IP_ApiChkPort(
    const BST_UINT16 usProtocol,
    const BST_UINT16 usPortNumber )
{
    BST_IP_FAST_CHECK_STRU             *pstFastCheckTbl;
    BST_INT32                           lPortCnt;
    BST_UINT32                          ulSpinlockCnt;

    ulSpinlockCnt                       = BST_OS_SpinLock( &g_BstPreprocSpinLock );
    pstFastCheckTbl                     = BST_IP_GetFCTPtr();

    for ( lPortCnt = 0;
        ( lPortCnt < pstFastCheckTbl->lCnt )
      &&( lPortCnt < (BST_INT32)BST_MAX_CNNT_NUMBER );
          lPortCnt++ )
    {
        if( ( pstFastCheckTbl->ausPortNum[lPortCnt] == usPortNumber )
          &&( pstFastCheckTbl->ausProtocol[lPortCnt] == usProtocol ) )
        {
            BST_DBG_LOG3( "BST_IP_ApiChkPort port,protocol,priority",
              pstFastCheckTbl->ausPortNum[lPortCnt],
              pstFastCheckTbl->ausProtocol[lPortCnt],
              pstFastCheckTbl->aucPathMode[lPortCnt] );
            BST_OS_SpinUnLock( &g_BstPreprocSpinLock , ulSpinlockCnt );
            if( BST_IP_PATH_MODE_DOUBLE == pstFastCheckTbl->aucPathMode[lPortCnt] )
            {
                return BST_IP_PKT_TO_AP_BST;
            }
            else
            {
                return BST_IP_PKT_TO_BST;
            }
        }
    }
    BST_OS_SpinUnLock( &g_BstPreprocSpinLock , ulSpinlockCnt );
    return BST_IP_PKT_TO_AP;
}


/*lint -e438 -e550*/
/*�ú����ڽ��յ��տ�OTA-IP������������*/
BST_IP_PKT_PROC_ENUM_INT8 BST_IP_ApiFastCheckDL(
    const BST_UINT8 aucPkt[],
    const BST_UINT32 ulPktLen )
{
    BST_BOOL                            bNetState;
    BST_UINT32                          ulState;
    BST_DRV_STRU                       *pstNetDevice;
#if (BST_OS_VER != BST_HISI_VOS)
    BST_UINT16                          usPortNum;
    BST_IP_PROTOCOL_TYPE                usProtocol;
    BST_IP_FAST_CHECK_STRU             *pstFastCheckTbl;
    BST_INT32                           lPortCnt;
    BST_UINT32                          ulSpinlockCnt;
#endif
    BST_ASSERT_NULL_RTN( aucPkt, BST_IP_PKT_TO_AP );
    BST_ASSERT_0_RTN( ulPktLen, BST_IP_PKT_TO_AP );

    pstNetDevice                        = BST_DRV_NetGetDvcHandle();
    pstNetDevice->pfIoCtrl( BST_DRV_CMD_GET_NET_STATE, &bNetState );

    if ( BST_FALSE == bNetState )
    {
        ulState                         = BST_IP_ParseRubbish( aucPkt, ulPktLen );
        if ( BST_NO_ERROR_MSG == ulState )
        {
            return BST_IP_PKT_FREE;
        }
        else
        {
            return BST_IP_PKT_TO_AP;
        }
    }
   /*
    *Balongƽ̨�Ѿ���CDSģ������˶˿ڹ��ˣ������������
    */
#if (BST_OS_VER == BST_HISI_VOS)
    return BST_IP_PKT_TO_BST;
#else
    usPortNum                           = BST_INVALID_PORT;
    usProtocol                          = BST_IP_PROTOCOL_INVALID;
    ulState = BST_IP_GetDLPortProtocol( aucPkt, ulPktLen, &usProtocol, &usPortNum );
    if ( BST_NO_ERROR_MSG != ulState  )
    {
        BST_RLS_LOG1( "BST_IP_ApiFastCheckDL: Get protocol ErrorCode=%d",ulState );
        return BST_IP_PKT_TO_AP;
    }
#if( BST_VER_TYPE == BST_DBG_VER )
    if(BST_IP_PROTOCOL_ICMP == usProtocol)
    {
        return BST_IP_PKT_TO_BST;
    }
    else
#endif
    if( BST_INVALID_PORT == usPortNum )
    {
        return BST_IP_PKT_TO_AP;
    }
    ulSpinlockCnt                       = BST_OS_SpinLock( &g_BstPreprocSpinLock );
    pstFastCheckTbl                     = BST_IP_GetFCTPtr();

    for ( lPortCnt = 0;
        ( lPortCnt < pstFastCheckTbl->lCnt )
      &&( lPortCnt < (BST_INT32)BST_MAX_CNNT_NUMBER );
          lPortCnt++ )
    {
        if( ( pstFastCheckTbl->ausPortNum[lPortCnt] == usPortNum )
          &&( pstFastCheckTbl->ausProtocol[lPortCnt] == usProtocol ))
        {
            BST_OS_SpinUnLock( &g_BstPreprocSpinLock , ulSpinlockCnt );
            return BST_IP_PKT_TO_BST;
        }
    }
    BST_OS_SpinUnLock( &g_BstPreprocSpinLock , ulSpinlockCnt );
    return BST_IP_PKT_TO_AP;
#endif
}
/*lint +e438 +e550*/

/*�ú�����IP������տ�֮ǰ����*/
BST_UINT8 BST_IP_ApiFastCheckUL(
    const BST_UINT8     aucPkt[],
    const BST_UINT32    ulPktLen )
{
    BST_UINT16                          usPortNum;
    BST_IP_PROTOCOL_TYPE                usProtocol;
    BST_IP_PORT_PREPROC_STRU           *pstPortPreproc;
    BST_BOOL                            bNetState;
    BST_DRV_STRU                       *pstNetDevice;

    pstPortPreproc                      = BST_NULL_PTR;
    usPortNum                           = BST_INVALID_PORT;
    usProtocol                          = BST_IP_PROTOCOL_INVALID;
    pstNetDevice                        = BST_DRV_NetGetDvcHandle();

    if ( BST_TRUE != pstNetDevice->ulIsInited )
    {
        BST_RLS_LOG( "BST_IP_ApiFastCheckUL: Main Net Device is not Initialed" );
        return BST_FALSE;
    }
    if( BST_NULL_PTR != pstNetDevice->pfIoCtrl )
    {
        pstNetDevice->pfIoCtrl( BST_DRV_CMD_GET_NET_STATE, &bNetState );
    }
    else
    {
        BST_RLS_LOG( "BST_IP_ApiFastCheckUL: IoCtl Function is NOT available" );
        return BST_FALSE;
    }
    if ( BST_FALSE == bNetState )
    {
        BST_RLS_LOG( "BST_IP_ApiFastCheckUL: Main Net Device was down" );
        return BST_FALSE;
    }

    if ( BST_NO_ERROR_MSG != BST_IP_GetULPortProtocol( aucPkt, ulPktLen, &usProtocol, &usPortNum ) )
    {
        BST_RLS_LOG( "BST_IP_ApiFastCheckUL: Get protocol Error" );
        return BST_FALSE;
    }
    if( ( BST_IP_PROTOCOL_TCP != usProtocol ) && ( BST_IP_PROTOCOL_UDP != usProtocol ) )
    {
        BST_RLS_LOG1( "BST_IP_ApiFastCheckUL: Protocol Type=%d is Invalid!", usProtocol );
        return BST_FALSE;
    }

    if( BST_INVALID_PORT == usPortNum )
    {
        BST_RLS_LOG( "BST_IP_ApiFastCheckUL: Port is Invalid!" );
        return BST_FALSE;
    }


    pstPortPreproc                      = BST_IP_SrchPreprocByPort( usProtocol, usPortNum );
    if( BST_NULL_PTR == pstPortPreproc )
    {
        BST_RLS_LOG( "BST_IP_ApiFastCheckUL: Didn't find Port" );
        return BST_FALSE;

    }
    pstPortPreproc->stLastSktProperty.ulTxByte
                                        += ulPktLen;
    BST_IP_ApiUpdateTrafficFlow( BST_IP_TRAFFIC_ADD, ulPktLen);
    BST_DBG_UPDATE_TX_FLOW( usPortNum, ulPktLen );
    BST_RLS_LOG3( "BST_IP_ApiFastCheckUL: usProtocol=%d, usPortNum=%d, TxByte=%d",\
                  usProtocol,\
                  usPortNum,\
                  pstPortPreproc->stLastSktProperty.ulTxByte );
    return BST_TRUE;
}
/*lint -e429*/
/*�ú����ڵ���netif->tcp_input֮ǰ����*/
BST_UINT16 BST_IP_ApiRegistPacket( BST_IP_PKT_ID_T stPktId, BST_VOID *pstPktItem )
{
    BST_IP_PORT_PREPROC_STRU           *pstPortPreproc;
    BST_IP_PKT_INFO_STRU               *pstPktLstMem;
    struct tcp_pcb                     *pstPcb;
    BST_IP_PROTOCOL_TYPE                ucProtocol;
    BST_UINT16                          usPortNum;
    BST_UINT32                          ulSpinlockCnt;

    BST_ASSERT_NULL_RTN( stPktId, BST_NULL_PTR );
    BST_ASSERT_NULL_RTN( pstPktItem, BST_NULL_PTR );

    if( BST_NO_ERROR_MSG != BST_IP_GetDLPortProtocol(
                          BST_DRV_NetGetPktHead( pstPktItem ),
                          BST_DRV_NetGetPktLen( pstPktItem ),
                          &ucProtocol, &usPortNum) )
    {
        return BST_INVALID_PORT;
    }
    /*�ڲ��Ѿ�������ͬ���ٽ���*/
    pstPortPreproc                      = BST_IP_SrchPreprocByPort( ucProtocol, usPortNum ); 
    pstPktLstMem                        = BST_NULL_PTR;
    /*If the port didn't find in the list, return directly*/
    if( BST_NULL_PTR == pstPortPreproc )
    {
        BST_RLS_LOG2( "BST_IP_ApiRegistPacket: can't parse pkt, protocol=%d, port=%d",\
                      ucProtocol,\
                      usPortNum );
        return BST_INVALID_PORT;
    }
    if( BST_NULL_PTR == pstPortPreproc->pstPktList )
    {
        BST_RLS_LOG( "BST_IP_ApiRegistPacket: Invalid Packet list" );
        return BST_INVALID_PORT;
    }
    if( !BST_IP_IsPrprocWorking(pstPortPreproc) )
    {
        BST_RLS_LOG2( "BST_IP_ApiRegistPacket: Port don't work, protocol=%d, port=%d",\
                      ucProtocol,\
                      usPortNum );
        return BST_INVALID_PORT;
    }

    /*Get Memory resource for new packet item for buffering*/
    pstPktLstMem                        = BST_OS_MALLOC(BST_OS_SIZEOF(BST_IP_PKT_INFO_STRU));
    BST_ASSERT_NULL_RTN( pstPktLstMem, BST_NULL_PTR );

    ulSpinlockCnt                       = BST_OS_SpinLock( &g_BstRegistSpinLock );
    pstPktLstMem->pstPktItem            = pstPktItem;
    pstPktLstMem->stPktId               = stPktId;
    pstPcb                              = BST_IP_SrchPcbByPort( usPortNum );
    if ( BST_NULL_PTR != pstPcb )
    {
        BST_IP_ReadFromPcbPropertey( &pstPktLstMem->stCurrentSktProperty, pstPcb );
    }
    lstAdd( pstPortPreproc->pstPktList, (NODE *)pstPktLstMem );
    /**************************************************************************
    Don't need to add traffice flow value here
    pstPortPreproc->stLastSktProperty.ulRxByte
                                        += BST_DRV_NetGetPktLen( pstPktItem );
    ***************************************************************************/
    BST_OS_SpinUnLock( &g_BstRegistSpinLock, ulSpinlockCnt );

    if( BST_OS_IsTimerValid( g_BstPreprocFreeTimer ) )
    {
        BST_OS_TimerStart( g_BstPreprocFreeTimer, ( BST_UINT32 ) BST_IP_CLRPKT_TIMELEN );
    }
    return usPortNum;
}
/*lint +e429*/

/*lint -e438*/
BST_VOID BST_IP_ApiUnRegistPacket( BST_IP_PKT_ID_T stPktId )
{
    BST_IP_PORT_PREPROC_STRU           *pstPortPreproc;
    BST_IP_PKT_INFO_STRU               *pstPktLstMem;
    BST_DRV_STRU                       *pstNetDevice;
    BST_UINT32                          ulSpinlockCnt;
    BST_UINT32                          ulPktFlow;

    if( BST_NULL_PTR == stPktId )
    {
        return;
    }

    pstNetDevice                        = BST_DRV_NetGetDvcHandle();
    pstPortPreproc                      = BST_IP_SrchPreprocByPktId( stPktId );
    pstPktLstMem                        = BST_NULL_PTR;

    if( BST_NULL_PTR == pstPortPreproc )
    {
        return;
    }

    pstPktLstMem                        = BST_IP_SrchPackItem( stPktId );
    if( BST_NULL_PTR == pstPktLstMem )
    {
        BST_RLS_LOG( "BST_IP_ApiUnRegistPacket pstPktLstMem=NULL" );
        return;
    }
    ulSpinlockCnt                       = BST_OS_SpinLock( &g_BstRegistSpinLock );
    if( BST_NULL_PTR != pstPortPreproc->pstPktList )
    {
        lstDelete( pstPortPreproc->pstPktList, (NODE *)pstPktLstMem );
    }
    BST_OS_SpinUnLock( &g_BstRegistSpinLock, ulSpinlockCnt );
    ulPktFlow                           = BST_DRV_NetGetPktLen( pstPktLstMem->pstPktItem );
    ( BST_VOID )BST_IP_ApiUpdateTrafficFlow( BST_IP_TRAFFIC_ADD, ulPktFlow );
    pstPortPreproc->stLastSktProperty.ulRxByte
                                        += ulPktFlow;
    if( BST_NULL_PTR != pstNetDevice->pfIoCtrl )
    {
        pstNetDevice->pfIoCtrl( BST_DRV_CMD_FREE_PACKET_ITEM, pstPktLstMem->pstPktItem );
    }
    BST_OS_FREE( pstPktLstMem );
}
/*lint +e438*/

BST_VOID BST_IP_ApiForwordPacket( BST_IP_PKT_ID_T stPktId )
{
    BST_IP_PORT_PREPROC_STRU           *pstPortPreproc;
    BST_IP_PKT_INFO_STRU               *pstPktLstMem;
    BST_IP_PKT_INFO_STRU               *pstAuxPktLstMem;
    BST_DRV_STRU                       *pstNetDevice;

    pstNetDevice                        = BST_DRV_NetGetDvcHandle();
    pstPortPreproc                      = BST_IP_SrchPreprocByPktId( stPktId );
    if( BST_NULL_PTR == pstPortPreproc )
    {
        BST_RLS_LOG( "BST_IP_ApiForwordPacket pstPortPreproc=NULL" );
        return;
    }

    pstPktLstMem                        = BST_IP_SrchPackItem( stPktId );
    if( BST_NULL_PTR == pstPktLstMem )
    {
        BST_RLS_LOG( "BST_IP_ApiForwordPacket pstPktLstMem=NULL" );
        return;
    }
/*
    if( BST_IP_IsPrprocWorking( pstPortPreproc ) )
    {
        BST_RLS_LOG( "BST_IP_ApiForwordPacket");
        return;
    }
*/
    for (;;)
    {
        if( BST_NULL_PTR == pstPktLstMem )
        {
            break;
        }
        pstAuxPktLstMem                 = ( BST_IP_PKT_INFO_STRU *)lstNext( (NODE *)pstPktLstMem );

        if( BST_NULL_PTR != pstNetDevice->pfIoCtrl )
        {
            pstNetDevice->pfIoCtrl( BST_DRV_CMD_RESUME_TO_AP, pstPktLstMem->pstPktItem );
        }
        if( BST_NULL_PTR != pstPortPreproc->pstPktList )
        {
            lstDelete( pstPortPreproc->pstPktList, (NODE *)pstPktLstMem );
        }
        BST_OS_FREE( pstPktLstMem );
        pstPktLstMem                    = pstAuxPktLstMem;
    }

    BST_DBG_LOG1(">>>>>>>>>>>>>>>>>>BST_IP_ApiForwordPacket %d",
                 pstPortPreproc->stLastSktProperty.ulRxByte);
}


BST_VOID BST_IP_ApiRecordLastSktProp( BST_IP_PKT_ID_T stPktId )
{
    BST_IP_PORT_PREPROC_STRU           *pstPortPreproc;
    BST_IP_PKT_INFO_STRU               *pstPktLstMem;
    BST_UINT32                          ulTxByte;
    BST_UINT32                          ulRxByte;

    pstPktLstMem                        = BST_IP_SrchPackItem( stPktId );
    if ( BST_NULL_PTR == pstPktLstMem )
    {
        BST_RLS_LOG( "BST_IP_ApiRecordLastSktProp pstPktLstMem=NULL" );
        return;
    }

    pstPortPreproc                      = BST_IP_SrchPreprocByPktId( stPktId );
    if ( BST_NULL_PTR == pstPortPreproc )
    {
        BST_RLS_LOG( "BST_IP_ApiRecordLastSktProp pstPortPreproc=NULL" );
        return;
    }

    ulTxByte                            = pstPortPreproc->stLastSktProperty.ulTxByte;
    ulRxByte                            = pstPortPreproc->stLastSktProperty.ulRxByte;

    BST_OS_MEMCPY( &(pstPortPreproc->stLastSktProperty),                    \
                   &(pstPktLstMem->stCurrentSktProperty),                   \
                   BST_OS_SIZEOF( pstPktLstMem->stCurrentSktProperty ) );
    pstPortPreproc->stLastSktProperty.ulTxByte                              \
                                        = ulTxByte;
    pstPortPreproc->stLastSktProperty.ulRxByte                              \
                                        = ulRxByte;
    BST_DBG_LOG3("BST_IP_ApiRecordLastSktProp stPktId: %p Last SEQ: 0x%x ACK: 0x%x",\
                  stPktId,\
                  pstPortPreproc->stLastSktProperty.ulSeqNum,\
                  pstPortPreproc->stLastSktProperty.ulAckNum);

}


BST_VOID BST_IP_ApiSetPreprocWorking(
    BST_IP_PROTOCOL_TYPE            usProtocol,
    BST_UINT16                      usPortNum,
    BST_IP_SKT_PATH_MODE_ENUM_U8    ucPathMode )
{
    BST_IP_PORT_PREPROC_STRU           *pstPortPreproc;
    BST_UINT32                          ulSpinlockCnt;

    if( !BST_IP_IsPortValid( usPortNum ) )
    {
        return;
    }

    ulSpinlockCnt                       = BST_OS_SpinLock( &g_BstPreprocSpinLock );

    pstPortPreproc                      = ( BST_IP_PORT_PREPROC_STRU * )lstFirst( BST_IP_GetPreprocLstHead() );
    while ( NULL != pstPortPreproc )
    {
        if( ( usPortNum  == pstPortPreproc->usPortNum )
         && ( usProtocol == pstPortPreproc->usProtocol ) )
        {
            if( ( !BST_IP_IsPrprocWorking( pstPortPreproc ) )
              ||( ucPathMode != pstPortPreproc->ucPathMode ) )
            {
                pstPortPreproc->enState     = BST_IP_PORT_STATE_WORKING;
                pstPortPreproc->ucPathMode  = ucPathMode;
                BST_IP_UpdateFCT();
            }
            BST_DBG_LOG2("BST_IP_ApiSetPreprocWorking usPortNum:%u, PathMode",
                         usPortNum, ucPathMode );
            BST_OS_SpinUnLock( &g_BstPreprocSpinLock , ulSpinlockCnt );
            return;
        }
        pstPortPreproc                  = ( BST_IP_PORT_PREPROC_STRU * )lstNext( ( NODE * )pstPortPreproc );
    }

    BST_DBG_LOG1("BST_IP_ApiSetPreprocWorking usPortNum:%u is not exited", usPortNum);
    BST_OS_SpinUnLock( &g_BstPreprocSpinLock , ulSpinlockCnt );
}


BST_VOID BST_IP_ApiSetPreprocSuspend( BST_IP_PROTOCOL_TYPE usProtocol, BST_UINT16 usPortNum )
{
    BST_IP_PORT_PREPROC_STRU           *pstPortPreproc;
    BST_UINT32                          ulSpinlockCnt;

    if( !BST_IP_IsPortValid( usPortNum ) )
    {
        return;
    }

    ulSpinlockCnt                       = BST_OS_SpinLock( &g_BstPreprocSpinLock );

    pstPortPreproc                      = ( BST_IP_PORT_PREPROC_STRU * )lstFirst( BST_IP_GetPreprocLstHead() );
    while ( BST_NULL_PTR != pstPortPreproc )
    {
        if( ( usPortNum  == pstPortPreproc->usPortNum )
         && ( usProtocol == pstPortPreproc->usProtocol ) )
        {
            if( ( !BST_IP_IsPrprocWorking( pstPortPreproc ) )
              &&( BST_IP_PATH_MODE_SINGLE  == pstPortPreproc->ucPathMode ) )
            {
                BST_OS_SpinUnLock( &g_BstPreprocSpinLock , ulSpinlockCnt );
                return;//һ��ѭ��ֻ����һ��break����
            }
            pstPortPreproc->enState     = BST_IP_PORT_STATE_SUSPEND;
            pstPortPreproc->ucPathMode  = BST_IP_PATH_MODE_SINGLE;
            BST_IP_UpdateFCT();
            break;
        }
        pstPortPreproc                  = ( BST_IP_PORT_PREPROC_STRU * )lstNext( ( NODE * )pstPortPreproc );
    }
    BST_OS_SpinUnLock( &g_BstPreprocSpinLock , ulSpinlockCnt );
}


BST_VOID BST_IP_ApiSetPreprocStop( BST_IP_PROTOCOL_TYPE usProtocol, BST_UINT16 usPortNum )
{
    BST_IP_PKT_INFO_STRU               *pstPktLstMem;
    BST_IP_PORT_PREPROC_STRU           *pstPortPreproc;
    BST_UINT32                          ulSpinlockCnt;

    if( !BST_IP_IsPortValid( usPortNum ) )
    {
        return;
    }

    ulSpinlockCnt                       = BST_OS_SpinLock( &g_BstPreprocSpinLock );

    pstPortPreproc                      = ( BST_IP_PORT_PREPROC_STRU * )
                                          lstFirst( BST_IP_GetPreprocLstHead() );
    while ( BST_NULL_PTR != pstPortPreproc )
    {
        if( ( usPortNum  == pstPortPreproc->usPortNum )
         && ( usProtocol == pstPortPreproc->usProtocol ) )
        {
            if( ( BST_IP_PORT_STATE_STOPED == pstPortPreproc->enState )
              &&( BST_IP_PATH_MODE_SINGLE  == pstPortPreproc->ucPathMode ) )
            {
                BST_OS_SpinUnLock( &g_BstPreprocSpinLock , ulSpinlockCnt );
                return;//һ��ѭ��ֻ����һ��break����
            }

            pstPortPreproc->ucPathMode  = BST_IP_PATH_MODE_SINGLE;
            pstPortPreproc->enState     = BST_IP_PORT_STATE_STOPED;
            BST_IP_UpdateFCT();

            /* ��������ͳ��ֵ */
            pstPktLstMem                = ( BST_IP_PKT_INFO_STRU *)
                                          lstFirst( pstPortPreproc->pstPktList );
            while ( BST_NULL_PTR != pstPktLstMem )
            {
                if( pstPortPreproc->stLastSktProperty.ulRxByte
                    > BST_DRV_NetGetPktLen( pstPktLstMem->pstPktItem ) )
                {
                    pstPortPreproc->stLastSktProperty.ulRxByte
                                       -= BST_DRV_NetGetPktLen( pstPktLstMem->pstPktItem );
                }
                else
                {
                    pstPortPreproc->stLastSktProperty.ulRxByte
                                        = 0U;
                }

                pstPktLstMem            = ( BST_IP_PKT_INFO_STRU *)
                                          lstNext( (NODE *)pstPktLstMem );
            }
            break;
        }
        pstPortPreproc                  = ( BST_IP_PORT_PREPROC_STRU * )
                                          lstNext( ( NODE * )pstPortPreproc );
    }

    BST_OS_SpinUnLock( &g_BstPreprocSpinLock , ulSpinlockCnt );
}
BST_UINT32 BST_IP_ApiUpdateTrafficFlow( BST_UINT32 ulTrfcAction, BST_UINT32 ulTrfcFlow  )
{
    extern BST_UINT32                   g_ulTrfcFlowLmt;
    BST_IP_EVENT_STRU                   stEvent;
    BST_UINT32                          ulSpinlockCnt;
    BST_DRV_STRU                       *pNetDrvHandle;
    BST_BOOL                            bNetState;

    pNetDrvHandle                       = BST_DRV_NetGetDvcHandle();
    pNetDrvHandle->pfIoCtrl( BST_DRV_CMD_GET_NET_STATE, &bNetState );

    if( ( BST_TRUE != pNetDrvHandle->ulIsInited )
     || ( BST_TRUE != bNetState ) )
    {
        return BST_FALSE;
    }

    ulSpinlockCnt                       = BST_OS_SpinLock( &g_BstTotFlowSpinLock );
    if ( BST_IP_TRAFFIC_ADD == ulTrfcAction )
    {
        g_ulTrafficFlowCounter         += ulTrfcFlow;
    }
    else if ( BST_IP_TRAFFIC_DEC == ulTrfcAction )
    {
        if ( ulTrfcFlow > g_ulTrafficFlowCounter )
        {
            g_ulTrafficFlowCounter      = 0;
        }
        else
        {
            g_ulTrafficFlowCounter     -= ulTrfcFlow;
        }
    }
    BST_RLS_LOG1("BST_IP_ApiUpdateTrafficFlow, New Value=%u", g_ulTrafficFlowCounter );

    if ( BST_IP_NO_TRFC_LMT == g_ulTrfcFlowLmt )
    {
        BST_DBG_LOG("BST_IP_ApiUpdateTrafficFlow, No Limit" );
        BST_OS_SpinUnLock( &g_BstTotFlowSpinLock , ulSpinlockCnt );
        return BST_FALSE;
    }

    if ( g_ulTrafficFlowCounter < g_ulTrfcFlowLmt )
    {
        BST_DBG_LOG1("BST_IP_ApiUpdateTrafficFlow, Not overflow to u%", g_ulTrfcFlowLmt );
        BST_OS_SpinUnLock( &g_BstTotFlowSpinLock , ulSpinlockCnt );
        return BST_FALSE;
    }

    if ( BST_IP_TRAFFIC_DEC == ulTrfcAction )
    {
        BST_OS_SpinUnLock( &g_BstTotFlowSpinLock , ulSpinlockCnt );
        return BST_FALSE;
    }

    stEvent.lErrMsg                     = BST_IP_ERR_OK;
    stEvent.ulMsgId                     = BST_IP_EVENT_OVERFLOW;
    stEvent.lFd                         = ( BST_INT32 )g_ulTrafficFlowCounter;
    ( BST_VOID )BST_SRV_ApiSendTcpIpEvent( BST_NULL_PTR, &stEvent );
    BST_OS_SpinUnLock( &g_BstTotFlowSpinLock , ulSpinlockCnt );
    return BST_TRUE;
}


BST_VOID   BST_IP_UpdateFCT( BST_VOID )
{
    BST_IP_PORT_PREPROC_STRU           *pstPortPreproc;
    BST_IP_FAST_CHECK_STRU             *pstFastCheckTbl;
    BST_INT32                           lPortCnt;
    BST_UINT32                          ulSpinlockCnt;

    ulSpinlockCnt                       = BST_OS_SpinLock( &g_BstPreprocSpinLock );
    pstPortPreproc                      = ( BST_IP_PORT_PREPROC_STRU *)
                                          lstFirst( BST_IP_GetPreprocLstHead() );
    pstFastCheckTbl                     = BST_IP_GetFCTPtr();
    lPortCnt                            = 0;

    do
    {
        if( BST_NULL_PTR == pstPortPreproc )
        {
            break;
        }
        if( BST_INVALID_PORT != pstPortPreproc->usPortNum )
        {
            if( BST_IP_IsPrprocWorking( pstPortPreproc ) )
            {
                pstFastCheckTbl->ausPortNum[lPortCnt]
                                        = pstPortPreproc->usPortNum;
                pstFastCheckTbl->ausProtocol[lPortCnt]
                                        = pstPortPreproc->usProtocol;
                pstFastCheckTbl->aucPathMode[lPortCnt]
                                        = pstPortPreproc->ucPathMode;
                lPortCnt++;
            }
        }
        pstPortPreproc                  = ( BST_IP_PORT_PREPROC_STRU *)
                                          lstNext( (NODE *)pstPortPreproc );
    }
    while ( lPortCnt < ( BST_INT32 )BST_MAX_CNNT_NUMBER );
    pstFastCheckTbl->lCnt               = lPortCnt;
    BST_OS_SpinUnLock( &g_BstPreprocSpinLock , ulSpinlockCnt );
}


BST_VOID BST_IP_ClearPortPkt( BST_IP_PORT_PREPROC_STRU *pstPortPreproc )
{
    BST_IP_PKT_INFO_STRU               *pstPktLstMem;
    BST_IP_PKT_INFO_STRU               *pstAuxPktLstMem;
    BST_DRV_STRU                       *pstNetDevice;
    BST_UINT32                          ulPktFlow;

    pstNetDevice                        = BST_DRV_NetGetDvcHandle();

    /*If the port didn't find in the list, return directly*/
    BST_ASSERT_NULL( pstPortPreproc );
    /*Get the Pkt list head of certain port*/
    if( BST_NULL_PTR == pstPortPreproc->pstPktList )
    {
        BST_RLS_LOG( "BST_IP_ClearPortPkt pstPortPreproc->pstPktList=NULL" );
        return;
    }
    pstPktLstMem                        = ( BST_IP_PKT_INFO_STRU *)
                                          lstFirst( pstPortPreproc->pstPktList );

    /*ɾ�������������ݰ����������ڴ�ռ�*/
    for (;;)
    {
        if( BST_NULL_PTR == pstPktLstMem )
        {
            return;
        }
        pstAuxPktLstMem                 = ( BST_IP_PKT_INFO_STRU *)lstNext( (NODE *)pstPktLstMem );
        lstDelete( pstPortPreproc->pstPktList, (NODE *)pstPktLstMem );

        ulPktFlow                       = BST_DRV_NetGetPktLen( pstPktLstMem->pstPktItem );
        ( BST_VOID )BST_IP_ApiUpdateTrafficFlow( BST_IP_TRAFFIC_ADD, ulPktFlow );
        pstPortPreproc->stLastSktProperty.ulRxByte
                                           += ulPktFlow;

        if( BST_NULL_PTR != pstNetDevice->pfIoCtrl )
        {
            pstNetDevice->pfIoCtrl( BST_DRV_CMD_FREE_PACKET_ITEM, pstPktLstMem->pstPktItem );
        }

        BST_OS_FREE( pstPktLstMem );
        pstPktLstMem                    = pstAuxPktLstMem;
    }
}
/*���ȫ�����ݰ������Ǵ���ֹͣ*/
BST_VOID BST_IP_ClearAllPkt( BST_VOID )
{
    BST_IP_PORT_PREPROC_STRU           *pstPortPreproc;
    BST_UINT32                          ulSpinlockCnt;

    ulSpinlockCnt                       = BST_OS_SpinLock( &g_BstPreprocSpinLock );
    pstPortPreproc                      = ( BST_IP_PORT_PREPROC_STRU *)
                                          lstFirst( BST_IP_GetPreprocLstHead() );
    /*�����������Ƿ��Ѿ����ڸ�Port��Ϣ*/
    for (;;)
    {
        if ( BST_NULL_PTR == pstPortPreproc )
        {
            BST_OS_SpinUnLock( &g_BstPreprocSpinLock , ulSpinlockCnt );
            return;
        }
        BST_IP_ClearPortPkt( pstPortPreproc );
        pstPortPreproc = ( BST_IP_PORT_PREPROC_STRU * )lstNext( ( NODE * )pstPortPreproc );
    }
}


BST_IP_PKT_INFO_STRU *BST_IP_SrchPackItem( BST_IP_PKT_ID_T stPktId )
{
    BST_IP_PORT_PREPROC_STRU           *pstPortPreproc;
    BST_IP_PKT_INFO_STRU               *pstPktLstMem;
    BST_UINT32                          ulSpinlockCnt;

    if( BST_NULL_PTR == stPktId )
    {
        return BST_NULL_PTR;
    }

    ulSpinlockCnt                       = BST_OS_SpinLock( &g_BstPreprocSpinLock );
    pstPortPreproc                      = ( BST_IP_PORT_PREPROC_STRU *)
                                          lstFirst( BST_IP_GetPreprocLstHead() );

    /*�����������Ƿ��Ѿ����ڸ�Port��Ϣ*/
    for (;;)
    {
        if( BST_NULL_PTR == pstPortPreproc )
        {
            BST_OS_SpinUnLock( &g_BstPreprocSpinLock , ulSpinlockCnt );
            return BST_NULL_PTR;
        }
        if( BST_NULL_PTR == pstPortPreproc->pstPktList )
        {
            BST_OS_SpinUnLock( &g_BstPreprocSpinLock , ulSpinlockCnt );
            return BST_NULL_PTR;
        }
        /*Get the Pkt list head of certain port*/
        pstPktLstMem                    = ( BST_IP_PKT_INFO_STRU *)
                                           lstFirst( pstPortPreproc->pstPktList );

        /*ɾ�������������ݰ����������ڴ�ռ�*/
        for (;;)
        {
            if( BST_NULL_PTR == pstPktLstMem )
            {
                break;
            }

            if( stPktId == pstPktLstMem->stPktId )
            {
                BST_OS_SpinUnLock( &g_BstPreprocSpinLock , ulSpinlockCnt );
                return pstPktLstMem;
            }
            pstPktLstMem                = ( BST_IP_PKT_INFO_STRU *)
                                          lstNext( (NODE *)pstPktLstMem );
        }
        pstPortPreproc                  = ( BST_IP_PORT_PREPROC_STRU *)
                                          lstNext( (NODE *)pstPortPreproc );
    }
}
BST_IP_PORT_PREPROC_STRU *BST_IP_SrchPreprocByPktId( BST_IP_PKT_ID_T stPktId )
{
    BST_IP_PORT_PREPROC_STRU           *pstPortPreproc;
    BST_IP_PKT_INFO_STRU               *pstPktLstMem;
    BST_UINT32                          ulSpinlockCnt;

    if( BST_NULL_PTR == stPktId )
    {
        return BST_NULL_PTR;
    }

    ulSpinlockCnt                       = BST_OS_SpinLock( &g_BstPreprocSpinLock );
    pstPortPreproc                      = ( BST_IP_PORT_PREPROC_STRU *)
                                          lstFirst( BST_IP_GetPreprocLstHead() );

    /*�����������Ƿ��Ѿ����ڸ�Port��Ϣ*/
    for (;;)
    {
        if( BST_NULL_PTR == pstPortPreproc )
        {
            BST_OS_SpinUnLock( &g_BstPreprocSpinLock , ulSpinlockCnt );
            return BST_NULL_PTR;
        }
        if( BST_NULL_PTR == pstPortPreproc->pstPktList )
        {
            BST_OS_SpinUnLock( &g_BstPreprocSpinLock , ulSpinlockCnt );
            return BST_NULL_PTR;
        }
        /*Get the Pkt list head of certain port*/
        pstPktLstMem                    = ( BST_IP_PKT_INFO_STRU *)
                                          lstFirst( pstPortPreproc->pstPktList );

        /*ɾ�������������ݰ����������ڴ�ռ�*/
        for (;;)
        {
            if( BST_NULL_PTR == pstPktLstMem )
            {
                break;
            }
            if( stPktId == pstPktLstMem->stPktId )
            {
                BST_OS_SpinUnLock( &g_BstPreprocSpinLock , ulSpinlockCnt );
                return pstPortPreproc;
            }
            pstPktLstMem                = ( BST_IP_PKT_INFO_STRU *)
                                          lstNext( (NODE *)pstPktLstMem );
        }
        pstPortPreproc                  = ( BST_IP_PORT_PREPROC_STRU *)
                                          lstNext( (NODE *)pstPortPreproc );
    }
}
BST_IP_PORT_PREPROC_STRU *BST_IP_SrchPreprocByPort(
    BST_IP_PROTOCOL_TYPE ucProtocol,
    BST_UINT16 usPortNum )
{
    BST_IP_PORT_PREPROC_STRU           *pstPortPreproc;
    BST_UINT32                          ulSpinlockCnt;

    if( !BST_IP_IsPortValid( usPortNum ) )
    {
        return BST_NULL_PTR;
    }

    ulSpinlockCnt                       = BST_OS_SpinLock( &g_BstPreprocSpinLock );
    pstPortPreproc                      = ( BST_IP_PORT_PREPROC_STRU *)
                                          lstFirst( BST_IP_GetPreprocLstHead() );

    /*�����������Ƿ��Ѿ����ڸ�Port��Ϣ*/
    for(;;)
    {
        if( BST_NULL_PTR == pstPortPreproc )
        {
            break;
        }
        if( ( usPortNum  == pstPortPreproc->usPortNum )
         && ( ucProtocol == pstPortPreproc->usProtocol ) )
        {
            BST_OS_SpinUnLock( &g_BstPreprocSpinLock , ulSpinlockCnt );
            return pstPortPreproc;
        }
        pstPortPreproc                   = ( BST_IP_PORT_PREPROC_STRU *)
                                           lstNext( (NODE *)pstPortPreproc );
    }

    BST_OS_SpinUnLock( &g_BstPreprocSpinLock , ulSpinlockCnt );
    BST_RLS_LOG2( "BST_IP_SrchPreprocByPort ucProtocol=%u,usPortNum=%u",
                  ucProtocol, usPortNum );
    return BST_NULL_PTR;
}
struct tcp_pcb* BST_IP_SrchPcbByPort( BST_UINT16 usPortNum )
{
    struct tcp_pcb         *pstPcb;
    extern struct tcp_pcb  *tcp_active_pcbs;

    BST_ASSERT_NULL_RTN( tcp_active_pcbs, BST_NULL_PTR );

    if( !BST_IP_IsPortValid( usPortNum ) )
    {
        return BST_NULL_PTR;
    }

    for( pstPcb  = tcp_active_pcbs;
         pstPcb != BST_NULL_PTR;
         pstPcb  = pstPcb->next)
    {
        if( pstPcb->local_port == usPortNum )
        {
            return pstPcb;
        }
    }
    BST_RLS_LOG1( "BST_IP_SrchPcbByPort usPortNum=%u",
                  usPortNum );
    return BST_NULL_PTR;
}


BST_ERR_ENUM_UINT8 BST_IP_GetULPortProtocol(
    const BST_UINT8         aucPkt[],
    const BST_UINT32        ulPktLen,
    BST_IP_PROTOCOL_TYPE   *pucProtocol,
    BST_UINT16             *pusPortNum )
{
    BST_IP_IPHDR_STRU      *pstIpHdr;
    BST_IP_TCPHDR_STRU     *pstTcpHdr;
    BST_UINT8               ucIpHdrLen;

    if ( ( BST_NULL_PTR == aucPkt )
      || ( BST_NULL_PTR == pusPortNum )
      || ( BST_NULL_PTR == pucProtocol ) )
    {
        return( BST_ERR_PAR_UNKNOW );
    }

    ucIpHdrLen              = ( ( aucPkt[0]&0x0F ) << 2 ) + BST_IP_PORT_ADRR_LEN;
    if ( ulPktLen < ucIpHdrLen )
    {
        return BST_ERR_PAR_LEN;
    }
    pstIpHdr                = (BST_IP_IPHDR_STRU *)aucPkt;
    pstTcpHdr               = (BST_IP_TCPHDR_STRU *)
                              & ( ( ( BST_UINT8 *)pstIpHdr )[ pstIpHdr->ucIhl << 2] );
    /*
     *IP ��Ƭ������ȷ�϶˿ڣ�������
     */
    if ( ( ntohs( pstIpHdr->usFragOff ) & BST_IP_FRAG_MASK ) )
    {
        BST_RLS_LOG( "BST_IP_GetULPortProtocol IP Fragment" );
        return BST_ERR_UNREACHABLE;
    }
   *pusPortNum              = ntohs( pstTcpHdr->usSource );
   *pucProtocol             = pstIpHdr->ucProtocol;
    return BST_NO_ERROR_MSG;
}


BST_ERR_ENUM_UINT8 BST_IP_GetDLPortProtocol(
    const BST_UINT8         aucPkt[],
    const BST_UINT32        ulPktLen,
    BST_IP_PROTOCOL_TYPE   *pucProtocol,
    BST_UINT16             *pusPortNum )
{
    BST_IP_IPHDR_STRU      *pstIpHdr;
    BST_IP_TCPHDR_STRU     *pstTcpHdr;
    BST_UINT8               ucIpHdrLen;

    if ( ( BST_NULL_PTR == aucPkt )
      || ( BST_NULL_PTR == pusPortNum )
      || ( BST_NULL_PTR == pucProtocol ) )
    {
        return( BST_ERR_PAR_UNKNOW );   //���ݴ���Bastet������
    }

    ucIpHdrLen              = ( ( aucPkt[0]&0x0F ) << 2 ) + BST_IP_PORT_ADRR_LEN;
    if ( ulPktLen < ucIpHdrLen )
    {
        return BST_ERR_PAR_LEN;
    }

#if( BST_OS_VER == BST_QCOM_ROS )
    pstIpHdr                = (BST_IP_IPHDR_STRU *)BST_OS_MALLOC( ucIpHdrLen );
    if ( BST_NULL_PTR == pstIpHdr )
    {
        return BST_ERR_NO_MEMORY;
    }
    BST_OS_MEMCPY( pstIpHdr, aucPkt, ucIpHdrLen );
#else
    pstIpHdr                = (BST_IP_IPHDR_STRU *)aucPkt;
#endif

    pstTcpHdr               = (BST_IP_TCPHDR_STRU *)
                              & ( ( ( BST_UINT8 *)pstIpHdr )[ pstIpHdr->ucIhl << 2] );

    /*
     *IP�汾���ԣ����ܴ���
     */
    if ( BST_IP_VER_IPV4 != pstIpHdr->ucVersion )
    {
#if( BST_OS_VER == BST_QCOM_ROS )
        BST_OS_FREE( pstIpHdr );
#endif
        return BST_ERR_LAYER_VER;
    }
    /*
     *IP ��Ƭ������ȷ�϶˿ڣ�������
     */
    if ( ( ntohs( pstIpHdr->usFragOff ) & BST_IP_FRAG_MASK ) )
    {
#if( BST_OS_VER == BST_QCOM_ROS )
        BST_OS_FREE( pstIpHdr );
#endif
        return BST_ERR_UNREACHABLE;
    }
   *pusPortNum              = ntohs( pstTcpHdr->usDest );
   *pucProtocol             = pstIpHdr->ucProtocol;

#ifdef BST_MODEM_SELF
    if ( BST_IP_PROTOCOL_TCP == pstIpHdr->ucProtocol )
    {
        DSPP_TEST_EMAIL( pstIpHdr->ulDaddr );
        BST_DBG_LOG4("Ip_Prec Rcv From Ip Addr",    \
                    ( pstIpHdr->ulSaddr>>24 )&0xff, \
                    ( pstIpHdr->ulSaddr>>16 )&0xff, \
                    ( pstIpHdr->ulSaddr>>8 )&0xff,  \
                    ( pstIpHdr->ulSaddr )&0xff );
        BST_DBG_LOG4("Ip_Prec Rcv to Ip Addr",      \
                    ( pstIpHdr->ulDaddr>>24 )&0xff, \
                    ( pstIpHdr->ulDaddr>>16 )&0xff, \
                    ( pstIpHdr->ulDaddr>>8 )&0xff,  \
                    ( pstIpHdr->ulDaddr )&0xff );
        BST_DBG_LOG2("Ip_Rcv From Port to Port",    \
                    ntohs( pstTcpHdr->usSource ),   \
                    *pusPortNum );
    }
#endif

#if( BST_OS_VER == BST_QCOM_ROS )
    BST_OS_FREE( pstIpHdr );
#endif
    return BST_NO_ERROR_MSG;
}


BST_ERR_ENUM_UINT8  BST_IP_ApiGetTrafficFlow(
    BST_UINT16                  usIsReset,
    BST_UINT16                  ulLocalPort,
    BST_IP_TRAFFIC_FLOW_STRU   *pstCurrentProperty )
{
    BST_IP_PORT_PREPROC_STRU           *pstPortPreproc;

    BST_ASSERT_NULL_RTN( pstCurrentProperty, BST_ERR_INVALID_PTR );
    BST_ASSERT_NORM_RTN( ( !BST_IP_IsPortValid(ulLocalPort) ), BST_ERR_INVALID_PTR );

    pstPortPreproc                      = BST_IP_SrchPreprocByPort
                                          ( BST_IP_PROTOCOL_TCP, ulLocalPort );

    /*���û���ҵ�����ô֤���Ѿ�ɾ����ֱ�ӷ���*/
    if( BST_NULL_PTR == pstPortPreproc )
    {
        return BST_ERR_ITEM_NOT_EXISTED;
    }


    pstCurrentProperty->ulRxByte        = pstPortPreproc->stLastSktProperty.ulRxByte;
    pstCurrentProperty->ulTxByte        = pstPortPreproc->stLastSktProperty.ulTxByte;


    /*�������ͳ��ֵ*/
    if( usIsReset )
    {
        BST_IP_ApiUpdateTrafficFlow( BST_IP_TRAFFIC_DEC,
                                  pstPortPreproc->stLastSktProperty.ulRxByte );
        BST_IP_ApiUpdateTrafficFlow( BST_IP_TRAFFIC_DEC,
                                  pstPortPreproc->stLastSktProperty.ulTxByte );
        pstPortPreproc->stLastSktProperty.ulRxByte  = 0U;
        pstPortPreproc->stLastSktProperty.ulTxByte  = 0U;
    }
    return BST_NO_ERROR_MSG;
}


BST_ERR_ENUM_UINT8 BST_IP_ParseRubbish( const BST_UINT8 aucPkt[], const BST_UINT32 ulPktLen )
{
    BST_IP_IPHDR_STRU      *pstIpHdr;
    BST_IP_TCPHDR_STRU     *pstTcpHdr;
    BST_UINT8               ucIpHdrLen;
    BST_ERR_ENUM_UINT8      enRtnVal;

    enRtnVal                = BST_NO_ERROR_MSG;
    if( BST_NULL_PTR == aucPkt )
    {
        BST_RLS_LOG( "BST_IP_ParseRubbish aucPkt=NULL" );
        return( BST_ERR_PAR_UNKNOW );   //���ݴ���Bastet������
    }

    ucIpHdrLen              = ( ( aucPkt[0]&0x0F ) << 2 ) + BST_IP_PORT_ADRR_LEN;
    if ( ulPktLen < ucIpHdrLen )
    {
        return BST_ERR_PAR_LEN;
    }

#if( BST_OS_VER == BST_QCOM_ROS )
    pstIpHdr                = (BST_IP_IPHDR_STRU *)BST_OS_MALLOC( ulPktLen );
    if ( BST_NULL_PTR == pstIpHdr )
    {
        return BST_ERR_NO_MEMORY;
    }
    BST_OS_MEMCPY( pstIpHdr, aucPkt, ucIpHdrLen );
#else
    pstIpHdr                = (BST_IP_IPHDR_STRU *)aucPkt;
#endif
    if ( BST_IP_PROTOCOL_TCP == pstIpHdr->ucProtocol )
    {
        pstTcpHdr           = (BST_IP_TCPHDR_STRU *)
                              & ( ( ( BST_UINT8 *)pstIpHdr )[ pstIpHdr->ucIhl << 2] );
        enRtnVal            = BST_IP_ProcRubbish
                            ( pstIpHdr, pstTcpHdr, (BST_UINT16)ulPktLen );
        if ( BST_NO_ERROR_MSG == enRtnVal )
        {
            BST_DBG_UPDATE_SUC_NUM( BST_APP_TYPE_SYSTASK, BST_APP_MAIN_TASK_ID );
        }
        else
        {
            BST_DBG_UPDATE_ERR_NUM( BST_APP_TYPE_SYSTASK, BST_APP_MAIN_TASK_ID );
        }
    }

#if( BST_OS_VER == BST_QCOM_ROS )
    BST_OS_FREE( pstIpHdr );
#endif
    return enRtnVal;
}


BST_ERR_ENUM_UINT8 BST_IP_ProcRubbish(
    const BST_IP_IPHDR_STRU  *pstIpHdr,
    const BST_IP_TCPHDR_STRU *pstTcpHdr,
    BST_UINT16                usTotLen )
{
    BST_DRV_STRU                       *pstNetDevice;
    BST_INT32                           lTcpLen;
    BST_UINT32                          ulBackLocalIp;
    BST_NETIF_T                        *pstRbshNetIf;
    BST_OS_LOCKCNT_T                    tThreadLockCnt;
    BST_ERR_ENUM_UINT8                  ucRtnVal;

    BST_ASSERT_NULL_RTN ( pstIpHdr, BST_ERR_INVALID_PTR );
    BST_ASSERT_NULL_RTN ( pstTcpHdr,BST_ERR_INVALID_PTR );

    BST_DBG_LOG4( "Rubbish From Ip Addr %u.%u.%u.%u",   \
                  ( pstIpHdr->ulSaddr )&0xffU,          \
                  ( pstIpHdr->ulSaddr>>8 )&0xffU,       \
                  ( pstIpHdr->ulSaddr>>16 )&0xffU,      \
                  ( pstIpHdr->ulSaddr>>24 )&0xffU );

    BST_DBG_LOG4( "Rubbish To Ip Addr %u.%u.%u.%u",     \
                  ( pstIpHdr->ulDaddr )&0xffU,          \
                  ( pstIpHdr->ulDaddr>>8 )&0xffU,       \
                  ( pstIpHdr->ulDaddr>>16 )&0xffU,      \
                  ( pstIpHdr->ulDaddr>>24 )&0xffU );

    BST_DBG_LOG4( "Rubbish From Port %u to Port %u, SeqNo %u, AckNo %u",\
                  htons( pstTcpHdr->usSource ),                         \
                  htons( pstTcpHdr->usDest ),                           \
                  htonl( pstTcpHdr->ulSeq ),                            \
                  htonl( pstTcpHdr->ulAckSeq ) );

    BST_DBG_LOG4( "Rubbish Packet TcpFlag: FIN=%u, ACK=%u, PSH=%u, RST=%u", \
                  pstTcpHdr->usFin, pstTcpHdr->usAck,                       \
                  pstTcpHdr->usPsh, pstTcpHdr->usRst );

    BST_IP_ClrMirroredTimeStamp();

    lTcpLen                             =  usTotLen - ( pstTcpHdr->usDoff << 2 ) - ( pstIpHdr->ucIhl << 2 );
    if( ( 0 != pstTcpHdr->usFin )||( 0 != pstTcpHdr->usSyn ) )
    {
        lTcpLen                        += 1;
    }

    if ( lTcpLen < 0 )
    {
        return BST_ERR_INVALID_PTR;
    }

    BST_DBG_LOG4( "Rubbish Packet Total=u%, IpHdr=u%, TcpHdr=u%, Sdu=u%",   \
                  usTotLen, ( pstIpHdr->ucIhl << 2 ), ( pstTcpHdr->usDoff << 2 ), lTcpLen );
    pstRbshNetIf                        = BST_DRV_NetGetRbshIfHandle();
    pstNetDevice                        = BST_DRV_NetGetDvcHandle();
    if ( BST_FALSE == pstNetDevice->ulIsInited )
    {
        BST_RLS_LOG("Rubbish Can't be processed, Net isn't Inited.");
        return BST_ERR_ITEM_NOT_EXISTED;
    }

    tThreadLockCnt                      = BST_OS_ThreadLock ();
    ulBackLocalIp                       = pstRbshNetIf->ip_addr.addr;
    pstRbshNetIf->ip_addr.addr          = pstIpHdr->ulDaddr;

    if( ( pstTcpHdr->usFin ) &&( pstTcpHdr->usAck ) )
    {
        ucRtnVal        = BST_IP_ProcFinRubbish( pstTcpHdr, pstIpHdr, lTcpLen );
    }
    else
    {
        ucRtnVal        = BST_IP_ProcPshRubbish( (const BST_UINT8*)pstIpHdr,
                                                  usTotLen, pstRbshNetIf );
    }
    pstRbshNetIf->ip_addr.addr      = ulBackLocalIp;
    if( ( BST_OS_IsTimerValid( g_BstPreprocFdTimer ) )
      &&( BST_NO_ERROR_MSG == ucRtnVal ) )
    {
        BST_OS_TimerStart( g_BstPreprocFdTimer, ( BST_UINT32 ) BST_IP_FD_TIMELEN );
    }
    BST_OS_ThreadUnLock ( tThreadLockCnt );
    return ucRtnVal;
}

BST_ERR_ENUM_UINT8 BST_IP_ProcFinRubbish(
    const BST_IP_TCPHDR_STRU   *pstTcpHdr,
    const BST_IP_IPHDR_STRU    *pstIpHdr,
    const BST_INT32             lTcpLen )
{
    BST_UINT32                      ulInAckNo;
    BST_UINT32                      ulInSeqNo;
    struct tcp_pcb                 *pstRubbishPcb;
    BST_IP_TCPOPT_STRU             *pstTcpOpt;

    pstRubbishPcb                   = tcp_new();
    if ( LWIP_NULL_PTR == pstRubbishPcb )
    {
        return BST_ERR_NO_MEMORY;
    }
    ulInAckNo                       =  htonl( pstTcpHdr->ulAckSeq );
    ulInSeqNo                       =  htonl( pstTcpHdr->ulSeq );
    pstRubbishPcb->local_ip.addr    = pstIpHdr->ulDaddr;
    pstRubbishPcb->remote_ip.addr   = pstIpHdr->ulSaddr;
    pstRubbishPcb->remote_port      = htons( pstTcpHdr->usSource );
    pstRubbishPcb->rcv_wnd          = (BST_UINT16)TCP_WND;
    pstRubbishPcb->rcv_ann_wnd      = (BST_UINT16)TCP_WND;
    pstRubbishPcb->snd_wnd          = (BST_UINT16)TCP_WND;
    pstRubbishPcb->snd_wnd_max      = (BST_UINT16)TCP_WND;
    pstRubbishPcb->snd_nxt          = ulInAckNo;
    pstRubbishPcb->snd_lbb          = ulInAckNo;
    pstRubbishPcb->lastack          = ulInAckNo;
    pstRubbishPcb->snd_wl2          = ulInAckNo;
    pstRubbishPcb->snd_wl1          = ulInSeqNo;
    pstRubbishPcb->rcv_nxt          = ulInSeqNo;
    pstRubbishPcb->rcv_ann_right_edge \
                                    = 0;
    pstRubbishPcb->flags            = TF_NODELAY;
#if( TCP_MSS > 536 )
    pstRubbishPcb->mss              = 536U;
#else
    pstRubbishPcb->mss              = (BST_UINT16)TCP_MSS;
#endif
    pstRubbishPcb->cwnd             = (BST_UINT16)( pstRubbishPcb->mss * 2U );
    pstRubbishPcb->ssthresh         = (BST_UINT16)( pstRubbishPcb->mss * 10U );
    pstRubbishPcb->connected        = BST_NULL_PTR;
    pstRubbishPcb->local_port       = htons( pstTcpHdr->usDest);
    pstRubbishPcb->snd_scale        = 0;
    pstRubbishPcb->rcv_scale        = 0;
    pstRubbishPcb->ts_offset        = 0;
    pstRubbishPcb->state            = ESTABLISHED;

    if( ( pstTcpHdr->usDoff << 2 ) == BST_IP_TCP_TIME_HEAD_LEN )
    {
        pstTcpOpt                   = ( BST_IP_TCPOPT_STRU * )      \
                                    & ( ( ( BST_UINT8 *)pstTcpHdr )[ BST_IP_TCP_BASE_HDR_LEN] );

        if ( BST_IP_TIMESTAMP_FLAG == pstTcpOpt->ulOpt01 )
        {
            BST_DBG_LOG( "Rubbis Rcv FIN_ACK With TimeStamp " );
            pstRubbishPcb->flags   |= TF_TIMESTAMP;
            pstRubbishPcb->snd_wl1 += lTcpLen;
            pstRubbishPcb->rcv_nxt += lTcpLen;
            pstRubbishPcb->ts_recent= ntohl( pstTcpOpt->ulOpt02 );
            pstRubbishPcb->ts_recent_stamp \
                                    = ntohl( pstTcpOpt->ulOpt03 );
            BST_IP_SetMirroredTimeStamp( pstRubbishPcb->ts_recent_stamp ) ;
        }
    }

    TCP_REG( &tcp_active_pcbs,  pstRubbishPcb);

    tcp_close( pstRubbishPcb );

    TCP_RMV( &tcp_active_pcbs,  pstRubbishPcb);
    TCP_RMV( &tcp_tw_pcbs,      pstRubbishPcb);

    memp_free( MEMP_TCP_PCB, pstRubbishPcb );
    BST_IP_ClrMirroredTimeStamp();
    return BST_NO_ERROR_MSG;
}


BST_ERR_ENUM_UINT8 BST_IP_ProcPshRubbish(
    const BST_UINT8     aucPkt[],
    const BST_UINT32    ulPktLen,
    BST_NETIF_T        *pstNetIf )
{
    struct pbuf        *pstPbuf;
    pstPbuf             = pbuf_alloc( PBUF_LINK, (BST_UINT16)ulPktLen, PBUF_POOL );
    if ( BST_NULL_PTR == pstPbuf )
    {
        BST_RLS_LOG( " Pbuffer No Memorry " );
        return BST_ERR_NO_MEMORY;
    }
    pbuf_take( pstPbuf->payload, ( BST_UINT8 *)&aucPkt[0] , (BST_UINT16)ulPktLen );
    ip_input ( pstPbuf, pstNetIf );
    return BST_NO_ERROR_MSG;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

