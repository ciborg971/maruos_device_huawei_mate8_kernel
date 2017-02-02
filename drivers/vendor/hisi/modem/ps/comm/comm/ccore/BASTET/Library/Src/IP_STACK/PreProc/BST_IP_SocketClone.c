

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "lwip/tcp_impl.h"
#include "lwip/snmp.h"
#include "lwip/memp.h"
#include "BST_IP_PreProc.h"
#include "BST_IP_SocketClone.h"
#include "BST_OS_Thread.h"
/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_BST_IP_SOCKETCLONE_C
/*lint +e767*/
/*****************************************************************************
  2 �ⲿ��������
*****************************************************************************/

/******************************************************************************
   3 ˽�ж���
******************************************************************************/

/******************************************************************************
   4 ȫ�ֱ�������
******************************************************************************/


/******************************************************************************
   5 ����ʵ��
******************************************************************************/


BST_STATIC BST_UINT32 BST_IP_IsInPcbSet( const struct tcp_pcb *pstPcb, const struct tcp_pcb *pstPcbSet )
{
    const struct tcp_pcb               *pstTmpPcbSet;

    if ( LWIP_NULL_PTR == pstPcb )
    {
        BST_DBG_LOG( "BST_IP_IsInPcbSet No" );
        return BST_FALSE;
    }
    if ( LWIP_NULL_PTR == pstPcbSet )
    {
        BST_DBG_LOG( "BST_IP_IsInPcbSet No" );
        return BST_FALSE;
    }

    pstTmpPcbSet                        = pstPcbSet;
    for (;;)
    {
        if ( pstTmpPcbSet == pstPcb )
        {
            BST_DBG_LOG( "BST_IP_IsInPcbSet Yes" );
            return BST_TRUE;
        }
        pstTmpPcbSet                    = pstTmpPcbSet->next;
        if ( LWIP_NULL_PTR == pstTmpPcbSet )
        {
            BST_DBG_LOG( "BST_IP_IsInPcbSet No" );
            return BST_FALSE;
        }
    }
}


BST_IP_ERR_T BST_IP_TcpCloneConn( struct tcp_pcb *pstPcb, struct  ip_addr *pstIpAddr, tcp_connected_fn connected, BST_UINT16 port )
{
    err_t                               ret;

    ret                                 = ERR_OK;
    if( NULL == pstPcb )
    {
        return BST_IP_ERR_VAL;
    }

    if ( pstIpAddr != NULL )
    {
        pstPcb->remote_ip               = *pstIpAddr;
    }
    else
    {
        return BST_IP_ERR_VAL;
    }

    pstPcb->remote_port                 = port;

    /* check if we have a route to the remote host */
    if ( IPADDR_ANY == pstPcb->local_ip.addr )
    {
        /* no local IP address set, yet. */
        struct netif *netif             = ip_route( &( pstPcb->remote_ip ) );

        if ( netif == NULL )
        {
            /* Don't even try to send a SYN packet if we have no route
               since that will fail. */
            return BST_IP_ERR_RTE;
        }

        /* Use the netif's IP address as local address. */
        ip_addr_copy( pstPcb->local_ip, netif->ip_addr );
    }

    if ( !BST_IP_IsPortValid( pstPcb->local_port ) )
    {
        return BST_IP_ERR_VAL;
    }

    pstPcb->state                       = ESTABLISHED;
    pstPcb->rcv_wnd                     = (BST_UINT16)TCP_WND;
    pstPcb->rcv_ann_wnd                 = (BST_UINT16)TCP_WND;
    pstPcb->rcv_ann_right_edge          = pstPcb->rcv_nxt;
    pstPcb->snd_wnd_max                 = (BST_UINT16)TCP_WND;
    pstPcb->flags                      |= TF_NODELAY;

    /* As initial send MSS, we use TCP_MSS but limit it to 536.
       The send MSS is updated when an MSS option is received. */

    pstPcb->mss                         = (BST_UINT16)TCP_MSS;

    pstPcb->cwnd                        = (BST_UINT16)TCP_SND_BUF;
    pstPcb->ssthresh                    = (BST_UINT16)( pstPcb->mss * (BST_UINT16)10 );
    pstPcb->connected                   = connected;

    BST_DBG_LOG1( "BST_IP_TcpCloneConn TCP_EVENT_CONNECTED ret=%d",
                   ret );
    snmp_inc_tcpactiveopens();

    if ( BST_FALSE == BST_IP_IsInPcbSet ( pstPcb, tcp_active_pcbs ) )
    {
        TCP_REG_ACTIVE( pstPcb );
    }

    return BST_IP_ERR_OK;
}


BST_VOID  BST_IP_ApiRecordTcpProperty(
    BST_IP_PKT_ID_T             stPktId,
    struct tcp_pcb             *pstPcb )
{
    BST_IP_PKT_INFO_STRU               *pstPktLstMem;
    BST_IP_PORT_PREPROC_STRU           *pstPortPreproc;

    BST_ASSERT_NULL( pstPcb );
    BST_ASSERT_NULL( stPktId );

    pstPortPreproc                      = BST_IP_SrchPreprocByPort( BST_IP_PROTOCOL_TCP, pstPcb->local_port );

    /*���û���ҵ�����ô֤���Ѿ�ɾ����ֱ�ӷ���*/
    if ( BST_NULL_PTR == pstPortPreproc )
    {
        return;
    }

    if ( !BST_IP_IsPrprocWorking( pstPortPreproc ) )
    {
        return;
    }

    pstPktLstMem                        = BST_IP_SrchPackItem( stPktId );

    if ( BST_NULL_PTR == pstPktLstMem )
    {
        return;
    }

    BST_IP_ReadFromPcbPropertey( &( pstPktLstMem->stCurrentSktProperty ), pstPcb );
}
BST_ERR_ENUM_UINT8 BST_IP_ApiSetTcpPcbProperty(
    struct tcp_pcb                 *pstPcb,
    BST_IP_SKT_PROPTY_STRU         *pstCurrentProperty,
    BST_UINT8                       ucFlag )
{
    BST_IP_SKT_PROP_TYPE_ENUM_U8    enPropType;
    BST_IP_SKT_PATH_MODE_ENUM_U8    enPathMode;

    BST_ASSERT_NULL_RTN( pstCurrentProperty, BST_ERR_INVALID_PTR );
    BST_ASSERT_NULL_RTN( pstPcb, BST_ERR_INVALID_PTR );
    BST_DBG_LOG4( "BST_IP_ApiSetTcpPcbProperty pstCurrentProperty seq,ack,sndwnd,scale",
                  pstCurrentProperty->ulSeqNum,
                  pstCurrentProperty->ulAckNum,
                  pstCurrentProperty->ulSndWnd,
                  pstCurrentProperty->usSndWscale );

    enPropType                      = BST_IP_GetPropType( ucFlag );
    enPathMode                      = BST_IP_GetPathMode( ucFlag );
    BST_DBG_LOG2( "BST_IP_ApiSetTcpPcbProperty enPropType",
                  enPropType,
                  enPathMode );

    switch( enPropType )
    {
        case BST_IP_SKT_PROP_NONE:        /* 0 û��property */
        break;

        case BST_IP_SKT_PROP_SEQNO:       /* 1 ֻ��seqno */
            pstPcb->snd_nxt     = pstCurrentProperty->ulSeqNum;
        break;

        case BST_IP_SKT_PROP_SEQNO_TS:    /* 2 ֻ��seqno+timestamp */
            pstPcb->snd_nxt     = pstCurrentProperty->ulSeqNum;
            pstPcb->ts_offset   = pstCurrentProperty->ulTsCurrent - sys_timestamp();
        break;

        case BST_IP_SKT_PROP_TOTAL:       /* 3 ����property */
            BST_IP_WriteToPcbPropertey( pstPcb, pstCurrentProperty );
#if LWIP_TCP_TIMESTAMPS
            if ( ( BST_INVALID_TIMESTAMP != pstCurrentProperty->ulTsRecent )
                && ( BST_INVALID_TIMESTAMP != pstCurrentProperty->ulTsCurrent ) )
            {
                pstPcb->flags  |= TF_TIMESTAMP;
            }
#endif
        break;

        default:                            /*4 ��Ч*/
             return BST_ERR_PAR_UNKNOW;
    }

    if( BST_IP_PATH_MODE_NO_CHG != enPathMode )
    {
        BST_IP_ApiSetPreprocWorking( BST_IP_PROTOCOL_TCP,
                                     pstPcb->local_port,
                                     enPathMode );
    }
    return BST_NO_ERROR_MSG;
}
BST_ERR_ENUM_UINT8  BST_IP_ApiGetTcpPcbProperty(
    struct tcp_pcb             *pstPcb,
    BST_IP_SKT_PROPTY_STRU     *pstCurrentProperty,
    BST_UINT8                   ucFlag )
{
    BST_IP_PORT_PREPROC_STRU           *pstPortPreproc;

    BST_ASSERT_NULL_RTN( pstCurrentProperty, BST_ERR_INVALID_PTR );
    BST_ASSERT_NULL_RTN( pstPcb, BST_ERR_INVALID_PTR );

    pstPortPreproc                       = BST_IP_SrchPreprocByPort( BST_IP_PROTOCOL_TCP, pstPcb->local_port );

    /*���û���ҵ�����ô֤���Ѿ�ɾ����ֱ�ӷ���*/
    if( BST_NULL_PTR == pstPortPreproc )
    {
        return BST_ERR_INVALID_PTR;
    }
    /*����˿ڴ��ڻ״̬����ô˵��ͬ����AP���𣬴�Э��ջֱ�Ӷ�ȡ*/
    if( BST_IP_IsPrprocWorking(pstPortPreproc) )
    {
        //��Э��ջpcb��ȡproperty
        BST_IP_ReadFromPcbPropertey( pstCurrentProperty, pstPcb );
        pstCurrentProperty->ulRxByte    = pstPortPreproc->stLastSktProperty.ulRxByte;
        pstCurrentProperty->ulTxByte    = pstPortPreproc->stLastSktProperty.ulTxByte;
        if( BST_IP_PATH_MODE_STOP == ucFlag )
        {
            /*ȷ���ĸ���ACK NUM*/
            BST_DBG_LOG4( "bastet socket info:  snd_nxt:%u, snd_wl1:%u, snd_wl2:%u, snd_lbb:%u",\
                        pstPcb->snd_nxt, pstPcb->snd_wl1, pstPcb->snd_wl2, pstPcb->snd_lbb);

            /*modem�ڸշ�����������ȥ��δ�յ�ackʱ��AP����SEQ�Ĵ���*/
            BST_IP_ApiResetTcpPcb( pstPcb );
        }
    }
    /*����˿��Ѿ�������ô˵��ͬ����Modem���𣬴�Ԥ����ȡ����ֵ����Э��ջȡseq��timestamp*/
    else if ( BST_IP_IsPrprocSuspend(pstPortPreproc) )
    {
       *pstCurrentProperty                  = pstPortPreproc->stLastSktProperty;
        pstCurrentProperty->ulSeqNum        = pstPcb->snd_nxt;
        pstCurrentProperty->ulTsRecentStamp = sys_timestamp() + pstPcb->ts_offset;
    }
    else
    {
        return BST_ERR_ILLEGAL_PARAM;
    }
    /**
     * ȡ��SEQ�������Ȼ��Ҫʹ��(NO STOP)����ô���¶˿�״̬ģʽ
     */
    if( BST_IP_PATH_MODE_STOP == ucFlag )
    {
        BST_IP_ApiSetPreprocStop ( BST_IP_PROTOCOL_TCP, pstPcb->local_port );
    }
    else
    {
        if( BST_IP_PATH_MODE_NO_CHG != ucFlag )
        {
            BST_IP_ApiSetPreprocWorking( BST_IP_PROTOCOL_TCP, pstPcb->local_port, ucFlag );
        }
    }

    BST_DBG_LOG3( "BST_IP_ApiGetTcpPcbProperty ulTxByte: %d ulRxByte: %d",\
                  pstPortPreproc->stLastSktProperty.ulTxByte,\
                  pstPortPreproc->stLastSktProperty.ulRxByte,\
                  ucFlag );
    /*�������ͳ��ֵ*/
    BST_IP_ApiUpdateTrafficFlow( BST_IP_TRAFFIC_DEC,
                                 pstPortPreproc->stLastSktProperty.ulRxByte );
    BST_IP_ApiUpdateTrafficFlow( BST_IP_TRAFFIC_DEC,
                                 pstPortPreproc->stLastSktProperty.ulTxByte );
    pstPortPreproc->stLastSktProperty.ulRxByte
                                        = 0U;
    pstPortPreproc->stLastSktProperty.ulTxByte
                                        = 0U;
    return BST_NO_ERROR_MSG;
}
BST_VOID BST_IP_ApiDropTcpPcb( struct tcp_pcb *pstPcb )
{
    if ( BST_NULL_PTR == pstPcb )
    {
        return;
    }

    /* Avoid the Freed pcb live in any PCBS */
    if ( BST_TRUE == BST_IP_IsInPcbSet ( pstPcb, tcp_active_pcbs ) )
    {
        TCP_RMV_ACTIVE( pstPcb );
    }
    if ( BST_TRUE == BST_IP_IsInPcbSet ( pstPcb, tcp_bound_pcbs ) )
    {
        tcp_pcb_remove( &tcp_bound_pcbs, pstPcb);
    }
    if ( BST_TRUE == BST_IP_IsInPcbSet ( pstPcb, tcp_listen_pcbs.pcbs ) )
    {
        tcp_pcb_remove( &tcp_listen_pcbs.pcbs, pstPcb );
    }
    if ( BST_TRUE == BST_IP_IsInPcbSet ( pstPcb, tcp_tw_pcbs ) )
    {
        tcp_pcb_remove( &tcp_tw_pcbs, pstPcb);
    }
    memp_free( MEMP_TCP_PCB, pstPcb );
}
BST_VOID BST_IP_ApiResetTcpPcb( struct tcp_pcb *pstPcb )
{
    if ( BST_NULL_PTR == pstPcb )
    {
        return;
    }

    if ( ( BST_NULL_PTR == pstPcb->unacked ) && ( BST_NULL_PTR == pstPcb->unsent ) )
    {
        /* No need to reset */
        return;
    }

    BST_RLS_LOG( "Reset Tcp pcb Notice" );

    pstPcb->snd_wl1                     = pstPcb->rcv_nxt;
    pstPcb->snd_wl2                     = pstPcb->snd_nxt;

    /* Reset the "IN Fast Retransmit" flag, since we are no longer
    in fast retransmit. Also reset the congestion window to the
    slow start threshold. */
    if ( pstPcb->flags & TF_INFR )
    {
        pstPcb->flags                  &= ~TF_INFR;
        pstPcb->cwnd                    = pstPcb->ssthresh;
    }

    /* Reset the number of retransmissions. */
    pstPcb->nrtx                        = 0;
    /* Reset the retransmission time-out. */
    pstPcb->rto                         = ( ((BST_UINT16)pstPcb->sa) >> 3 ) + pstPcb->sv;

    /* Update the send buffer space. Diff between the two can never exceed 64K? */
    pstPcb->acked                       = ( u16_t )( pstPcb->snd_nxt - pstPcb->lastack );
    pstPcb->snd_buf                    += pstPcb->acked;

    /* Reset the fast retransmit variables. */
    pstPcb->dupacks                     = 0;
    pstPcb->lastack                     = pstPcb->snd_nxt;

    tcp_pcb_purge(pstPcb);
    /* After clear unsent and unacked segs, reset snd_queuelen 0 */
    pstPcb->snd_queuelen                = 0;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


