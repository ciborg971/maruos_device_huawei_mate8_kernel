

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "BST_SRV_ChnlCtrl.h"
#include "BST_DSPP_AppLayer.h"
#include "BST_IP_Socket.h"
#include "BST_SRV_Event.h"
#include "BST_SRV_TaskMng.h"
#include "BST_DRV_Net.h"
/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_BST_SRV_CHNL_CTRL_CPP
/*lint +e767*/

/******************************************************************************
   2 ȫ�ֱ�������
******************************************************************************/
BST_STATIC BST_SRV_CHNL_LINK_STRU  *g_lstChnlMng    = BST_NULL_PTR;
BST_OS_SPINLOCK_T                   g_HighPriCntSpinLock;
BST_STATIC BST_UINT32               g_ulHighPriCnt  = 0;
/******************************************************************************
   3 ����ʵ��
******************************************************************************/


BST_VOID BST_SRV_CHNL_InitLink(
    BST_SRV_CHNL_LINK_STRU     *pstChnlLink,
    BST_IP_CSocket             *pcSocket,
    BST_OS_TIMERID_T            ulTimerId )
{
    BST_ASSERT_NULL( pcSocket );
    BST_ASSERT_NULL( pstChnlLink );
    BST_ASSERT_NORM( BST_OS_INVALID_TIMER_ID == ulTimerId );
    pstChnlLink->enState                = BST_SRV_CHNL_STATE_UN_INITED;
    pstChnlLink->pNext                  = BST_NULL_PTR;
    pstChnlLink->pSentList              = BST_NULL_PTR;
    pstChnlLink->pUnsendList            = BST_NULL_PTR;
    pstChnlLink->stLink.ulMainLinkId    = 0;
    pstChnlLink->stLink.ulAuxLinkId     = 0;
    pstChnlLink->ulRetryTimes           = 0;
    pstChnlLink->ulCurrentSeq           = 0;
    pstChnlLink->ulIsPropSet            = BST_FALSE;
    pstChnlLink->ulAddrType             = BST_DSPP_FLG_ADDTYPE_VOID;
    pstChnlLink->ulTimerId              = ulTimerId;
    pstChnlLink->pcSocket               = pcSocket;
}


BST_VOID BST_SRV_CHNL_Send_Suspend( 
    BST_SRV_CHNL_LINK_STRU     *pstChnlLink,
    BST_SRV_CHNL_HEAD_STRU     *pstPktItem )
{
    BST_ASSERT_NULL( pstChnlLink );
    BST_ASSERT_NULL( pstPktItem );

    BST_DBG_LOG1("BST_SRV_CHNL_Send_Suspend state",pstChnlLink->enState);
    BST_SRV_Q_PushToTail( (BST_SRV_CHNL_Q **)&pstChnlLink->pUnsendList,
                          (BST_SRV_CHNL_Q *)pstPktItem );
    if( BST_SRV_CHNL_STATE_RUN == pstChnlLink->enState )
    {
        pstChnlLink->ulRetryTimes   = 0;
    }
    if( BST_OS_TimerIsStop( pstChnlLink->ulTimerId ) )
    {
        BST_OS_TimerStart( pstChnlLink->ulTimerId, BST_SRV_CHNL_RTX_INTERVAL );
    }
}


BST_VOID BST_SRV_CHNL_Set_LinkProp( 
    BST_SRV_CHNL_LINK_STRU     *pstChnlLink,
    BST_SRV_CHNL_HEAD_STRU     *pstPktItem )
{
    BST_IP_ERR_T                enIpErrMsg;

    BST_ASSERT_NULL( pstChnlLink );
    BST_ASSERT_NULL( pstPktItem );
    BST_ASSERT_NULL( pstChnlLink->pcSocket );

    enIpErrMsg                  = BST_IP_ERR_OK;
    BST_DBG_LOG1("BST_SRV_CHNL_Set_LinkProp pstPktItem->ucPropType",
            pstPktItem->ucPropType);
    BST_DBG_LOG4("BST_SRV_CHNL_Set_LinkProp seq,ack,sndwnd,sndscale",
        pstPktItem->stProp.ulSeqNum,
        pstPktItem->stProp.ulAckNum,
        pstPktItem->stProp.ulSndWnd,
        pstPktItem->stProp.usSndWscale);

    switch( pstPktItem->ucPropType )
    {
        case BST_IP_SKT_PROP_NONE:        /* 0 û��property */
            return;

        case BST_IP_SKT_PROP_SEQNO:       /* 1 ֻ��seqno */
            enIpErrMsg          = pstChnlLink->pcSocket->IoCtrl 
                                ( BST_SCKT_CMD_SET_SEQNO,
                                ( BST_VOID  *)&(pstPktItem->stProp) );
        break;

        case BST_IP_SKT_PROP_SEQNO_TS:    /* 2 ֻ��seqno+timestamp */
            enIpErrMsg          = pstChnlLink->pcSocket->IoCtrl 
                                ( BST_SCKT_CMD_SET_SEQNO_TS,
                                ( BST_VOID  *)&(pstPktItem->stProp) );
        break;

        case BST_IP_SKT_PROP_TOTAL:       /* 3 ����property */
            if( BST_TRUE == pstChnlLink->ulIsPropSet )
            {
                enIpErrMsg      = pstChnlLink->pcSocket->IoCtrl 
                                ( BST_SCKT_CMD_SET_SEQNO_TS,
                                ( BST_VOID  *)&(pstPktItem->stProp) );
                break;
            }
            enIpErrMsg          = pstChnlLink->pcSocket->IoCtrl 
                                ( BST_SCKT_CMD_DBL_PROPERTY,
                                ( BST_VOID  *)&(pstPktItem->stProp) );
            if( BST_IP_ERR_OK == enIpErrMsg )
            {
                pstChnlLink->ulIsPropSet
                                = BST_TRUE;
            }
        break;

        default:                            /*4 ��Ч*/
             return;
    }
    BST_DBG_LOG1( "BST_SRV_CHNL_Set_LinkProp enIpErrMsg=%d",
                  enIpErrMsg );
}

BST_ERR_ENUM_UINT8 BST_SRV_CHNL_Send_InCB( 
    BST_SRV_CHNL_LINK_STRU     *pstChnlLink,
    BST_SRV_CHNL_HEAD_STRU     *pstPktItem )
{
    BST_SRV_CHNL_SENT_STRU     *pSentItem;
    BST_IP_ERR_T                enIpErr;
    BST_UINT16                  usFlags;
    BST_UINT32                  ulSpinlockCnt;

    BST_ASSERT_NULL_RTN( pstChnlLink, BST_ERR_INVALID_PTR );
    BST_ASSERT_NULL_RTN( pstPktItem, BST_ERR_INVALID_PTR );
    enIpErr                     = BST_IP_ERR_OK;
    if( BST_SRV_ChnlIsTail(pstPktItem) )
    {
        usFlags                 = BST_IP_SEND_FLAG_VOID;
    }
    else
    {
        usFlags                 = BST_IP_SEND_FLAG_MORE;
    }

    if( BST_IP_SKT_PROP_NONE != pstPktItem->ucPropType )
    {
        BST_SRV_CHNL_Set_LinkProp( pstChnlLink, pstPktItem );
        pstChnlLink->ulCurrentSeq= pstPktItem->stProp.ulSeqNum;
    }
    BST_DBG_LOG4("BST_SRV_CHNL_Send_InCB Length, ProcLevel, PackAddr, Flag",
                    pstPktItem->ulUsed,
                    pstPktItem->usProcLevel,
                    pstPktItem->ucPktAddr,
                    usFlags );

    switch( pstPktItem->usProcLevel )
    {
        case BST_DSPP_FLG_LVLTYPE_NORMAL:
            enIpErr             = pstChnlLink->pcSocket->Write
                                  ( (const BST_UINT8 *)&pstPktItem->aucData[0],
                                    (BST_UINT16)pstPktItem->ulUsed, BST_IP_BSTT_DATA, usFlags );
        break;

        case BST_DSPP_FLG_LVLTYPE_HS:
            enIpErr             = pstChnlLink->pcSocket->Write
                                  ( (const BST_UINT8 *)&pstPktItem->aucData[0],
                                    (BST_UINT16)pstPktItem->ulUsed,
                                    BST_IP_HPRI_DATA,
                                    usFlags );
        break;

        case BST_DSPP_FLG_LVLTYPE_LP:
            enIpErr             = pstChnlLink->pcSocket->Write
                                  ( (const BST_UINT8 *)&pstPktItem->aucData[0],
                                    (BST_UINT16)pstPktItem->ulUsed,
                                    BST_IP_LPWR_DATA,
                                    usFlags );
        break;

        default:
            return BST_ERR_PAR_UNKNOW;
    }
    if( BST_IP_ERR_OK == enIpErr )
    {
        pSentItem               = ( BST_SRV_CHNL_SENT_STRU *)BST_OS_MALLOC(
                                  BST_OS_SIZEOF( BST_SRV_CHNL_SENT_STRU ) );
        if( BST_NULL_PTR == pSentItem )
        {
            return BST_ERR_INVALID_PTR;
        }
        pstChnlLink->ulCurrentSeq += pstPktItem->ulUsed;
        pstChnlLink->ulRetryTimes  = 0;
        pSentItem->usProcLevel  = pstPktItem->usProcLevel;
        pSentItem->pNext        = BST_NULL_PTR;
        pSentItem->ulAckNo      = pstChnlLink->ulCurrentSeq;
        BST_SRV_Q_PushToTail( (BST_SRV_CHNL_Q **)&pstChnlLink->pSentList,
                              (BST_SRV_CHNL_Q *)pSentItem );
        if ( BST_DSPP_FLG_LVLTYPE_HS == pstPktItem->usProcLevel )
        {
            ulSpinlockCnt       = BST_OS_SpinLock( &g_HighPriCntSpinLock );
            g_ulHighPriCnt++;
            BST_OS_SpinUnLock( &g_HighPriCntSpinLock , ulSpinlockCnt );
            BST_DBG_LOG2(" g_ulHighPriCnt++, sent", g_ulHighPriCnt, pstPktItem->ulUsed);
        }
    }
    else if( BST_IP_ERR_MEM == enIpErr )
    {
        pstChnlLink->ulRetryTimes++;
        BST_OS_TimerStart( pstChnlLink->ulTimerId, BST_SRV_CHNL_RTX_INTERVAL );
        return BST_ERR_NO_MEMORY;
    }
    else
    {
        return BST_ERR_SOCKET_CLSD;
    }
    return BST_NO_ERROR_MSG;
}


BST_ERR_ENUM_UINT8 BST_SRV_CHNL_Send_Runing( 
    BST_SRV_CHNL_LINK_STRU     *pstChnlLink,
    BST_SRV_CHNL_HEAD_STRU     *pstPktItem )
{
    BST_SRV_CHNL_SENT_STRU     *pSentItem;
    BST_SRV_CHNL_HEAD_STRU     *pstUnsendItem;
    BST_SRV_CHNL_LINK_STRU     *pstLinkItem2;
    BST_IP_ERR_T                enIpErr;
    BST_DSPP_CAppUlVc          *pstDsppUl;
    BST_UINT32                  ulSpinlockCnt;
    BST_UINT16                  usFlags;

    BST_ASSERT_NULL_RTN( pstChnlLink, BST_ERR_INVALID_PTR );
    BST_ASSERT_NULL_RTN( pstPktItem, BST_ERR_INVALID_PTR );
    enIpErr                     = BST_IP_ERR_OK;
    if( BST_SRV_ChnlIsTail(pstPktItem) )
    {
        usFlags                 = BST_IP_SEND_FLAG_VOID;
    }
    else
    {
        usFlags                 = BST_IP_SEND_FLAG_MORE;
    }
    if( BST_IP_SKT_PROP_NONE != pstPktItem->ucPropType )
    {
        BST_SRV_CHNL_Set_LinkProp( pstChnlLink, pstPktItem );
        pstChnlLink->ulCurrentSeq
                                = pstPktItem->stProp.ulSeqNum;
    }

    BST_DBG_LOG4("BST_SRV_CHNL_Send_Runing Length, ProcLevel, PackAddr, Flag",
                    pstPktItem->ulUsed,
                    pstPktItem->usProcLevel,
                    pstPktItem->ucPktAddr,
                    usFlags );
    switch( pstPktItem->usProcLevel )
    {
        case BST_DSPP_FLG_LVLTYPE_NORMAL:
            enIpErr             = pstChnlLink->pcSocket->Write
                                  ( (const BST_UINT8 *)&pstPktItem->aucData[0],
                                    (BST_UINT16)pstPktItem->ulUsed, BST_IP_BSTT_DATA, usFlags );
        break;

        case BST_DSPP_FLG_LVLTYPE_HS:
            enIpErr             = pstChnlLink->pcSocket->Write
                                  ( (const BST_UINT8 *)&pstPktItem->aucData[0],
                                    (BST_UINT16)pstPktItem->ulUsed,
                                    BST_IP_HPRI_DATA,
                                    usFlags );
        break;

        case BST_DSPP_FLG_LVLTYPE_LP:
            enIpErr             = pstChnlLink->pcSocket->Write
                                  ( (const BST_UINT8 *)&pstPktItem->aucData[0],
                                    (BST_UINT16)pstPktItem->ulUsed,
                                    BST_IP_LPWR_DATA,
                                    usFlags );
        break;

        default:
            return BST_ERR_PAR_UNKNOW;
    }
    if( BST_IP_ERR_OK == enIpErr )
    {
        pSentItem               = ( BST_SRV_CHNL_SENT_STRU *)BST_OS_MALLOC(
                                  BST_OS_SIZEOF( BST_SRV_CHNL_SENT_STRU ) );
        if( BST_NULL_PTR == pSentItem )
        {
            return BST_ERR_NO_MEMORY;
        }
        pstChnlLink->ulCurrentSeq += pstPktItem->ulUsed;
        pSentItem->pNext        = BST_NULL_PTR;
        if ( BST_DSPP_FLG_LVLTYPE_HS == pstPktItem->usProcLevel )
        {
            ulSpinlockCnt       = BST_OS_SpinLock( &g_HighPriCntSpinLock );
            g_ulHighPriCnt++;
            BST_OS_SpinUnLock( &g_HighPriCntSpinLock , ulSpinlockCnt );
        }
        pSentItem->usProcLevel  = pstPktItem->usProcLevel;
        pSentItem->ulAckNo      = pstChnlLink->ulCurrentSeq;
        BST_SRV_Q_PushToTail( (BST_SRV_CHNL_Q **)&pstChnlLink->pSentList,
                              (BST_SRV_CHNL_Q *)pSentItem );
        BST_DBG_LOG3("tiger BST_SRV_FreeIpBlock1 g_ulHighPriCnt++, sent",pstPktItem, g_ulHighPriCnt, pstPktItem->ulUsed);
        BST_SRV_FreeIpBlock( pstPktItem );
    }
    else if( BST_IP_ERR_MEM == enIpErr )
    {
        /*����ռ�洢δ���͵�����,�����ڴ������ʱ�������ͷ�*/
        pstUnsendItem           = BST_SRV_AlocIpBlock();
        if ( BST_NULL_PTR == pstUnsendItem )
        {
            return BST_ERR_NO_MEMORY;
        }
        BST_OS_MEMCPY( pstUnsendItem, pstPktItem, BST_OS_SIZEOF(BST_SRV_CHNL_HEAD_STRU));
        BST_SRV_CHNL_Send_Suspend( pstChnlLink, pstUnsendItem );
        pstChnlLink->enState    = BST_SRV_CHNL_STATE_SUSPEND;
        return BST_ERR_NO_MEMORY;
    }
    else
    {
        pstDsppUl               = BST_DSPP_CAppUlVc::GetInstance();
        if( pstChnlLink->ulAddrType == BST_DSPP_FLG_ADDTYPE_INET )
        {
            pstDsppUl->Report( BST_DSPP_FLG_CMD_CLOSE,
                               pstChnlLink->stLink.ulMainLinkId,
                               pstChnlLink->stLink.ulAuxLinkId );
            BST_SRV_CHNL_ReportTrafficFlow( pstChnlLink );
        }
        else
        {
            pstDsppUl->Report( BST_DSPP_FLG_CMD_CLOSE,
                               pstChnlLink->stDspp.usProcId,
                               pstChnlLink->stDspp.usTaskId );
        }
        BST_SRV_CHNL_Close( pstChnlLink );
        delete pstChnlLink->pcSocket;
        BST_SRV_Q_RmvItem( (BST_SRV_CHNL_Q **)&g_lstChnlMng,
                           (BST_SRV_CHNL_Q *)pstChnlLink,
                           (BST_SRV_CHNL_Q **)&pstLinkItem2 );
        BST_OS_FREE(pstChnlLink);
        return BST_ERR_SOCKET_CLSD;
    }
    return BST_NO_ERROR_MSG;
}
BST_ERR_ENUM_UINT8 BST_SRV_CHNL_Send( 
    BST_SRV_CHNL_LINK_STRU     *pstChnlLink,
    BST_SRV_CHNL_HEAD_STRU     *pstPktItem )
{
    BST_ERR_ENUM_UINT8              enRtnVal;

    BST_ASSERT_NULL_RTN( pstChnlLink, BST_ERR_INVALID_PTR );
    BST_ASSERT_NULL_RTN( pstPktItem, BST_ERR_INVALID_PTR );

    enRtnVal                        = BST_ERR_UNREACHABLE;

    switch( pstChnlLink->enState )
    {
        case BST_SRV_CHNL_STATE_UN_INITED:
            if( (BST_DSPP_FLG_ADDTYPE_INET != pstPktItem->ucAddrType)
             && (BST_DSPP_FLG_ADDTYPE_TASK != pstPktItem->ucAddrType))
            {
                enRtnVal            = BST_ERR_ILLEGAL_PARAM;
                goto err_drop;
            }
            pstChnlLink->enState    = BST_SRV_CHNL_STATE_RUN;

        case BST_SRV_CHNL_STATE_RUN:
            enRtnVal                = BST_SRV_CHNL_Send_Runing( pstChnlLink, pstPktItem );
            if( BST_NO_ERROR_MSG != enRtnVal )
            {
                goto err_drop;
            }
        break;

        case BST_SRV_CHNL_STATE_SUSPEND:
            BST_SRV_CHNL_Send_Suspend( pstChnlLink, pstPktItem );
        break;

        default:
            enRtnVal                = BST_ERR_UNREACHABLE;
            goto err_drop;
    }
    return BST_NO_ERROR_MSG;
err_drop:
    BST_SRV_FreeIpBlock( pstPktItem );

    return enRtnVal;
}



BST_ERR_ENUM_UINT8 BST_SRV_CHNL_Acked (
    BST_SRV_CHNL_LINK_STRU     *pstLinkItem,
    const BST_UINT32            ulMinNumber,
    const BST_UINT32            ulMaxNumber )
{
    BST_SRV_CHNL_SENT_STRU             *pSentItem;
    BST_SRV_CHNL_SENT_STRU             *pSentItem2;
    BST_SRV_CHNL_HEAD_STRU             *pstPktItem;
    BST_SRV_CHNL_HEAD_STRU             *pstPktItem2;
    BST_UINT32                          ulSpinlockCnt;
    BST_UINT32                          ulOrigCounter;
    BST_DRV_STRU                       *pNetDrvHandle;
    BST_ERR_ENUM_UINT8                  enRtnVal;

    BST_ASSERT_NULL_RTN( pstLinkItem, BST_ERR_INVALID_PTR );
    BST_ASSERT_NORM_RTN( ulMaxNumber < ulMinNumber, BST_ERR_ILLEGAL_PARAM );

    BST_DBG_LOG2( "BST_SRV_CHNL_Acked ulMinNumber, ulMaxNumber",
                  ulMinNumber, ulMaxNumber );
    /*�����ѷ��͵����ݰ���*/
    pSentItem                           = BST_SRV_Q_PeekHead(pstLinkItem->pSentList);
    ulOrigCounter                       = g_ulHighPriCnt;
    pSentItem2                          = BST_NULL_PTR;
    pstPktItem2                         = BST_NULL_PTR;
    while( pSentItem != BST_NULL_PTR )
    {
        if ( ( pSentItem->ulAckNo > ulMinNumber )
           &&( pSentItem->ulAckNo <=ulMaxNumber ) )
        {
            if( BST_DSPP_FLG_LVLTYPE_HS == pSentItem->usProcLevel )
            {
                ulSpinlockCnt           = BST_OS_SpinLock( &g_HighPriCntSpinLock );
                if ( g_ulHighPriCnt > 0 )
                {
                    g_ulHighPriCnt--;
                }
                BST_OS_SpinUnLock( &g_HighPriCntSpinLock , ulSpinlockCnt );
            }
            BST_DBG_LOG1("BST_SRV_CHNL_Acked,g_ulHighPriCnt--",g_ulHighPriCnt);
            BST_SRV_Q_RmvItem( (BST_SRV_CHNL_Q **)&pstLinkItem->pSentList,
                               (BST_SRV_CHNL_Q *)pSentItem,
                               (BST_SRV_CHNL_Q **)&pSentItem2 );
            BST_OS_FREE( pSentItem );
        }
        else
        {
            pSentItem2                  = pSentItem->pNext;
        }
        pSentItem                       = pSentItem2;
    }

    pstPktItem                          = BST_SRV_Q_PeekHead(pstLinkItem->pUnsendList);
    while ( pstPktItem != BST_NULL_PTR )
    {
        if( BST_IP_SKT_PROP_NONE != pstPktItem->ucPropType )
        {
            if( ( ( pstPktItem->stProp.ulSeqNum + pstPktItem->ulUsed  ) > ulMinNumber )
              &&( ( pstPktItem->stProp.ulSeqNum + pstPktItem->ulUsed  ) <=ulMaxNumber ) )
            {
                BST_SRV_Q_RmvItem( (BST_SRV_CHNL_Q **)&pstLinkItem->pUnsendList,
                                   (BST_SRV_CHNL_Q *)pstPktItem,
                                   (BST_SRV_CHNL_Q **)&pstPktItem2 );
                BST_SRV_FreeIpBlock( pstPktItem );
            }
            else
            {
                pstPktItem2             = pstPktItem->pNext;
            }
        }
        else
        {
            pstPktItem2                 = pstPktItem->pNext;
        }
        pstPktItem                      = pstPktItem2;
    }
    enRtnVal                            = BST_NO_ERROR_MSG;
    if( BST_NULL_PTR != pstLinkItem->pUnsendList )
    {
        BST_OS_TimerStop( pstLinkItem->ulTimerId );
        BST_DBG_LOG( "BST_SRV_CHNL_Acked, Proc Unsent List" );
        enRtnVal                        = BST_SRV_CHNL_ProcInCB( pstLinkItem );
    }

    /**
     * �ո���ֵ��������ֵ����ô˵��ȫ�����������ݷ������
     */
    if( ( 0 != ulOrigCounter ) && ( 0 == g_ulHighPriCnt ) )
    {
        pNetDrvHandle   = BST_DRV_NetGetDvcHandle();
        enRtnVal        = 0;
        pNetDrvHandle->pfIoCtrl( BST_DRV_CMD_HPR_DATA_FINISH, (BST_VOID *)&enRtnVal );
        BST_DBG_LOG( "BST_SRV_CHNL_Acked, BST_DRV_CMD_HPR_DATA_FINISH" );
    }

    return enRtnVal;
}


BST_VOID BST_SRV_CHNL_Clear(
    BST_SRV_CHNL_LINK_STRU     *pstChnlLink )
{
    BST_SRV_CHNL_SENT_STRU     *pSentItem;
    BST_SRV_CHNL_SENT_STRU     *pSentItem2;
    BST_SRV_CHNL_HEAD_STRU     *pstPktItem;
    BST_SRV_CHNL_HEAD_STRU     *pstPktItem2;
    BST_DRV_STRU               *pNetDrvHandle;
    BST_UINT8                   ucUnused;
    BST_UINT32                  ulSpinlockCnt;

    BST_ASSERT_NULL( pstChnlLink );
    pstChnlLink->ulIsPropSet    = BST_FALSE;
    for(;;)
    {
        pSentItem               = BST_SRV_Q_PeekHead(pstChnlLink->pSentList);
        if( BST_NULL_PTR == pSentItem )
        {
            break;
        }
        if( BST_DSPP_FLG_LVLTYPE_HS == pSentItem->usProcLevel )
        {
            ulSpinlockCnt       = BST_OS_SpinLock( &g_HighPriCntSpinLock );
            if ( g_ulHighPriCnt > 0 )
            {
                g_ulHighPriCnt--;
                if ( 0 == g_ulHighPriCnt )
                {
                    pNetDrvHandle= BST_DRV_NetGetDvcHandle();
                    ucUnused     = 0;
                    pNetDrvHandle->pfIoCtrl( BST_DRV_CMD_HPR_DATA_FINISH, (BST_VOID *)&ucUnused );
                }
            }
            BST_OS_SpinUnLock( &g_HighPriCntSpinLock , ulSpinlockCnt );
        }
        BST_DBG_LOG1("BST_SRV_CHNL_Clear,g_ulHighPriCnt--",g_ulHighPriCnt);
        BST_SRV_Q_RmvItem( (BST_SRV_CHNL_Q **)&pstChnlLink->pSentList,
                           (BST_SRV_CHNL_Q *)pSentItem,
                           (BST_SRV_CHNL_Q **)&pSentItem2 );
        BST_OS_FREE( pSentItem );
    }
    for(;;)
    {
        pstPktItem              = BST_SRV_Q_PeekHead(pstChnlLink->pUnsendList);
        if( BST_NULL_PTR == pstPktItem )
        {
            break;
        }
        BST_SRV_Q_RmvItem( (BST_SRV_CHNL_Q **)&pstChnlLink->pUnsendList,
                           (BST_SRV_CHNL_Q *)pstPktItem,
                           (BST_SRV_CHNL_Q **)&pstPktItem2 );
        BST_SRV_FreeIpBlock( pstPktItem );
    }

}

BST_VOID BST_SRV_CHNL_Close(
    BST_SRV_CHNL_LINK_STRU     *pstChnlLink )
{
    BST_ASSERT_NULL( pstChnlLink );
    BST_SRV_CHNL_Clear( pstChnlLink );
    BST_DBG_LOG("BST_SRV_CHNL_Close");

    pstChnlLink->ulIsPropSet    = BST_FALSE;
    if( BST_NULL_PTR != pstChnlLink->pcSocket )
    {
        pstChnlLink->pcSocket->CloneClose();
    }
    return;
}

BST_IP_CSocket *BST_SRV_CHNL_CreateSocket(
    BST_SRV_CHNL_HEAD_STRU     *pstPktItem )
{
    BST_IP_CSocket             *pcSocket;
    BST_IP_CNetRcver           *pNetRcver;
    BST_SCKT_TYPE_ENUM_UINT32   enSocketType;
    BST_IP_ERR_T                enIpErrMsg;

    BST_ASSERT_NULL_RTN( pstPktItem, BST_NULL_PTR );
    enSocketType                = BST_SCKT_TYPE_TCP;

#if( BST_VER_TYPE == BST_DBG_VER )
    pcSocket                    = new BST_IP_CSocket ( 0, 0 );
#else
    pcSocket                    = new BST_IP_CSocket ();
#endif
    pNetRcver                   = BST_SRV_CChnlIpRcver::GetInstance();
    if ( BST_NULL_PTR == pNetRcver )
    {
        delete pcSocket;
        return BST_NULL_PTR;
    }

    enIpErrMsg                  = pcSocket->IoCtrl ( BST_SCKT_CMD_DEF_TYPE,
                                                    ( BST_VOID  *)&enSocketType );
    if ( BST_IP_ERR_OK != enIpErrMsg )
    {
        BST_DBG_LOG("BST_APP_CPRITask CreateSocket BST_SCKT_CMD_DEF_TYPE");
        delete pcSocket;
        return BST_NULL_PTR;
    }
    enIpErrMsg                  = pcSocket->IoCtrl( BST_SCKT_CMD_SET_ADDRESS,
                                                    ( BST_VOID  *)&pstPktItem->stAddr.stInet );
    if ( BST_IP_ERR_OK != enIpErrMsg )
    {
        BST_DBG_LOG("BST_APP_CPRITask CreateSocket BST_SCKT_CMD_SET_ADDRESS");
        delete pcSocket;
        return BST_NULL_PTR;
    }

    enIpErrMsg                  = pcSocket->IoCtrl( BST_SCKT_CMD_REG_CALLBACK,
                                                    pNetRcver ); 
    if ( BST_IP_ERR_OK != enIpErrMsg )
    {
        BST_DBG_LOG("BST_APP_CPRITask CreateSocket BST_SCKT_CMD_REG_CALLBACK");
        delete pcSocket;
        return BST_NULL_PTR;
    }
    enIpErrMsg                  = pcSocket->Socket( BST_SRV_GetChnlCtrlHandle( 0 ) );
    if ( BST_IP_ERR_OK != enIpErrMsg )
    {
        BST_DBG_LOG("BST_APP_CPRITask CreateSocket Socket error");
        delete pcSocket;
        return BST_NULL_PTR;
    }
#if ( ( BST_OS_VER == BST_WIN32 && BST_VER_TYPE == BST_DBG_VER )||( BST_MODEM_SELF == 1 ) )
    pcSocket->Bind();
    pcSocket->Connect();
#else
    enIpErrMsg                  = pcSocket->Clone();
#endif
    if ( BST_IP_ERR_OK != enIpErrMsg )
    {
        BST_RLS_LOG( "BST_APP_CPRITask Clone err" );
        return BST_NULL_PTR;
    }
    return pcSocket;
}


BST_VOID BST_SRV_CHNL_SysTimerExpired(
    BST_OS_TIMERID_T            ulTimerId,
    BST_VOID                   *pvArg )
{
    BST_SRV_CHNL_LINK_STRU     *pstLinkItem;
    BST_SRV_CHNL_LINK_STRU     *pstLinkItem2;
    BST_ERR_ENUM_UINT8          enRtnVal;
    BST_DSPP_CAppUlVc          *pstDsppUl;

    pstLinkItem                 = BST_SRV_Q_PeekHead( g_lstChnlMng );
    for(;;)
    {
        if( BST_NULL_PTR == pstLinkItem )
        {
            break;
        }
        if( pstLinkItem->ulTimerId != ulTimerId )
        {
            pstLinkItem         = pstLinkItem->pNext;
            continue;
        }
        
        if( pstLinkItem->ulRetryTimes > BST_SRV_CHNL_RTX_MAX )
        {
            pstDsppUl           = BST_DSPP_CAppUlVc::GetInstance();
            pstDsppUl->Report( BST_DSPP_FLG_CMD_CLEAR,
                               pstLinkItem->stLink.ulMainLinkId,
                               pstLinkItem->stLink.ulAuxLinkId );
            BST_SRV_CHNL_ReportTrafficFlow( pstLinkItem );

            BST_SRV_CHNL_Close( pstLinkItem );
            delete pstLinkItem->pcSocket;
            BST_SRV_Q_RmvItem( (BST_SRV_CHNL_Q **)&g_lstChnlMng,
                               (BST_SRV_CHNL_Q *)pstLinkItem, 
                               (BST_SRV_CHNL_Q **)&pstLinkItem2 );
            BST_OS_TimerRemove( pstLinkItem->ulTimerId );
            BST_OS_FREE( pstLinkItem );
        }
        else
        {
            enRtnVal            = BST_SRV_CHNL_ProcInCB( pstLinkItem );
            if( ( BST_NO_ERROR_MSG == enRtnVal )
              ||( BST_ERR_NO_MEMORY == enRtnVal ) )
            {
                break;
            }
            else/*Socket is closed*/
            {
                pstDsppUl       = BST_DSPP_CAppUlVc::GetInstance();
                pstDsppUl->Report( BST_DSPP_FLG_CMD_CLEAR,
                                   pstLinkItem->stLink.ulMainLinkId,
                                   pstLinkItem->stLink.ulAuxLinkId );
                BST_SRV_CHNL_ReportTrafficFlow( pstLinkItem );

                BST_SRV_CHNL_Close( pstLinkItem );
                delete pstLinkItem->pcSocket;
                BST_SRV_Q_RmvItem( (BST_SRV_CHNL_Q **)&g_lstChnlMng,
                                   (BST_SRV_CHNL_Q *)pstLinkItem,
                                   (BST_SRV_CHNL_Q **)&pstLinkItem2 );
                BST_OS_TimerRemove( pstLinkItem->ulTimerId );
                BST_OS_FREE( pstLinkItem );
            }
        }
        return;
    }
}
BST_ERR_ENUM_UINT8 BST_SRV_CHNL_Itf(
    BST_SRV_CHNL_HEAD_STRU     *pstPktItem )
{
    BST_SRV_CHNL_LINK_STRU     *pstLinkItem = BST_NULL_PTR;
    BST_SRV_CHNL_LINK_STRU     *pstLinkItem2;
    BST_IP_CSocket             *pcSocket;
    BST_OS_TIMERID_T            ulTimerId;
    BST_ERR_ENUM_UINT8          enRtnVal;

    BST_ASSERT_NULL_RTN( pstPktItem, BST_ERR_INVALID_PTR );
    pstLinkItem                 = BST_SRV_Q_PeekHead( g_lstChnlMng );
    enRtnVal                    = BST_NO_ERROR_MSG;
    for(;;)
    {
        if( BST_NULL_PTR == pstLinkItem )
        {
            break;
        }
        if( ( pstLinkItem->stLink.ulMainLinkId == pstPktItem->ulMainLinkId )
          &&( pstLinkItem->stLink.ulAuxLinkId == pstPktItem->ulAuxLinkId ) )
        {
            break;
        }
        pstLinkItem             = pstLinkItem->pNext;
    }

    BST_DBG_LOG1( "CPC_PACKET_DROP pstPktItem->usCmdId", pstPktItem->usCmdId );
    switch( pstPktItem->usCmdId )
    {
        case BST_DSPP_FLG_CMD_CLEAR:
            if( BST_NULL_PTR != pstLinkItem )
            {
                BST_SRV_CHNL_Close( pstLinkItem );
                delete pstLinkItem->pcSocket;
                BST_SRV_Q_RmvItem( (BST_SRV_CHNL_Q **)&g_lstChnlMng,
                                   (BST_SRV_CHNL_Q *)pstLinkItem,
                                   (BST_SRV_CHNL_Q **)&pstLinkItem2 );
                BST_OS_TimerRemove( pstLinkItem->ulTimerId );
                BST_OS_FREE( pstLinkItem );
            }
            else
            {
                enRtnVal        = BST_ERR_UNKNOW_OBJ;
            }
        break;

        case BST_DSPP_FLG_CMD_CLOSE:
            if( BST_NULL_PTR != pstLinkItem )
            {
                BST_SRV_CHNL_Close( pstLinkItem );
                delete pstLinkItem->pcSocket;
                BST_SRV_Q_RmvItem( (BST_SRV_CHNL_Q **)&g_lstChnlMng,
                                   (BST_SRV_CHNL_Q *)pstLinkItem,
                                   (BST_SRV_CHNL_Q **)&pstLinkItem2 );
                BST_OS_TimerRemove( pstLinkItem->ulTimerId );
                BST_OS_FREE( pstLinkItem );
            }
            else
            {
                enRtnVal        = BST_ERR_UNKNOW_OBJ;
            }
        break;

        case BST_DSPP_FLG_CMD_SEND:
            BST_DBG_LOG1("BST_SRV_CHNL_Itf send pstLinkItem",pstLinkItem);
            if( BST_NULL_PTR == pstLinkItem )
            {
                pstLinkItem     = (BST_SRV_CHNL_LINK_STRU *)BST_OS_MALLOC
                                  ( BST_OS_SIZEOF(BST_SRV_CHNL_LINK_STRU) );
                if( BST_NULL_PTR == pstLinkItem )
                {
                    enRtnVal    = BST_ERR_NO_MEMORY;
                    break;
                }
                pcSocket        = BST_SRV_CHNL_CreateSocket( pstPktItem );
                if ( BST_NULL_PTR == pcSocket )
                {
                    BST_RLS_LOG("BST_SRV_CHNL_CreateSocket error");
                    enRtnVal    = BST_ERR_PAR_UNKNOW;
                    break;
                }
                ulTimerId       = BST_OS_TimerCreate
                                ( BST_SRV_CHNL_SysTimerExpired, BST_NULL_PTR, 
                                  BST_SRV_GetChnlCtrlHandle( 0 ) );
                BST_SRV_CHNL_InitLink( pstLinkItem, pcSocket, ulTimerId );
                pstLinkItem->ulAddrType             = BST_DSPP_FLG_ADDTYPE_INET;
                pstLinkItem->stLink.ulMainLinkId    = pstPktItem->ulMainLinkId;
                pstLinkItem->stLink.ulAuxLinkId     = pstPktItem->ulAuxLinkId;
                BST_SRV_Q_PushToTail( (BST_SRV_CHNL_Q **)&g_lstChnlMng,
                                      (BST_SRV_CHNL_Q *)pstLinkItem );
            }

            enRtnVal            = BST_SRV_CHNL_Send( pstLinkItem, pstPktItem );
            if( BST_ERR_ILLEGAL_PARAM == enRtnVal )
            {
                BST_SRV_Q_RmvItem( (BST_SRV_CHNL_Q **)&g_lstChnlMng,
                                   (BST_SRV_CHNL_Q *)pstLinkItem,
                                   (BST_SRV_CHNL_Q **)&pstLinkItem2 );
                BST_OS_FREE( pstLinkItem );
            }

            return enRtnVal;

        default:
        break;
    }
    BST_SRV_FreeIpBlock( pstPktItem );
    return enRtnVal;
}


BST_ERR_ENUM_UINT8 BST_SRV_CHNL_ProcInCB(
    BST_SRV_CHNL_LINK_STRU     *pstChnlLink )
{
    BST_SRV_CHNL_HEAD_STRU     *pstPktItem;
    BST_SRV_CHNL_HEAD_STRU     *pstPktItem2;
    BST_ERR_ENUM_UINT8          enRtnVal;

    BST_ASSERT_NULL_RTN( pstChnlLink, BST_ERR_INVALID_PTR );
    pstChnlLink->enState        = BST_SRV_CHNL_STATE_SUSPEND;
    BST_DBG_LOG("BST_SRV_CHNL_ProcInCB"); 
    for(;;)
    {
        pstPktItem              = BST_SRV_Q_PeekHead(pstChnlLink->pUnsendList);
        enRtnVal                = BST_NO_ERROR_MSG;
        if( BST_NULL_PTR == pstPktItem )
        {
            break;
        }
        enRtnVal                = BST_SRV_CHNL_Send_InCB( pstChnlLink, pstPktItem );
        if( BST_NO_ERROR_MSG == enRtnVal )
        {
            BST_SRV_Q_RmvItem( (BST_SRV_CHNL_Q **)&pstChnlLink->pUnsendList,
                               (BST_SRV_CHNL_Q *)pstPktItem,
                               (BST_SRV_CHNL_Q **)&pstPktItem2 );
            BST_SRV_FreeIpBlock( pstPktItem );
            continue;
        }
        else
        {
            break;
        }
    }
    if( BST_SRV_Q_IsEmpty( pstChnlLink->pUnsendList ) )
    {
        pstChnlLink->enState    = BST_SRV_CHNL_STATE_RUN;
    }
    return BST_NO_ERROR_MSG;
}

BST_VOID BST_SRV_CHNL_ThreadEntry( BST_VOID *pvArg )
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
                        ( BST_OS_GetCurrentThreadId(), BST_L_MBOX_SIZE );
    if ( BST_NULL_PTR == *pstMailBox )
    {
        BST_OS_ThreadUnLock ( tThreadLockCnt );
        return;
    }

    BST_SetThreadInitFlag( BST_CHNL_CTRL_THREAD_FLAG );
    g_lstChnlMng        = BST_NULL_PTR;
    BST_OS_InitSpinLock( &g_HighPriCntSpinLock );
    BST_OS_ThreadUnLock ( tThreadLockCnt );

    /*
     * �����߳���ѭ�����ȴ��ʼ����ʼ�����Ϊ����ִ�е�����
     */
    for(;;)
    {
        ulRtnVal        = BST_OS_RecvMail
                       ( *pstMailBox, (BST_VOID **)&pstEvent, BST_OS_SYS_FOREVER );
        BST_ASSERT_NORM( BST_OS_SYS_TIMEOUT == ulRtnVal );
        BST_SRV_ProcChnlCtrEvent( pstEvent );
        /*�����ж�ָ�벻Ϊ���ٴ��ͷţ������Ҫ����ָ���ָ��*/
        if( BST_NULL_PTR != pstEvent->pucData )
        {
            BST_DBG_LOG1( "tiger BST_OS_FREE 8,", pstEvent->pucData );
            BST_OS_FREE( pstEvent->pucData );
        }
        BST_OS_FREE( pstEvent );
#if ( BST_VER_TYPE == BST_UT_VER )
        break;
#endif
     }
}
BST_VOID BST_SRV_CHNL_ReportTrafficFlow(
    BST_SRV_CHNL_LINK_STRU     *pstLinkItem )
{
    BST_IP_TRAFFIC_FLOW_STRU    stFlowInfo;
    BST_IP_ERR_T                stRtnVal;
    BST_DSPP_CAppUlVc          *pstDsppUl;
    if ( BST_NULL_PTR == pstLinkItem )
    {
        return;
    }
    if ( BST_NULL_PTR == pstLinkItem->pcSocket )
    {
        return;
    }
    pstDsppUl           = BST_DSPP_CAppUlVc::GetInstance();
    if ( BST_NULL_PTR == pstDsppUl )
    {
        return;
    }
    stRtnVal            = pstLinkItem->pcSocket->IoCtrl(
                            BST_SCKT_CMD_GET_TRAFFIC_FLOW,
                            &stFlowInfo );
    if ( BST_IP_ERR_OK != stRtnVal )
    {
        return;
    }
    pstDsppUl->ReportFlow( &stFlowInfo,
                           pstLinkItem->stLink.ulMainLinkId,
                           pstLinkItem->stLink.ulAuxLinkId );
}



BST_SRV_CChnlIpRcver *BST_SRV_CChnlIpRcver::GetInstance( BST_VOID )
{
    static BST_SRV_CChnlIpRcver    *s_pInstance = BST_NULL_PTR;

    if ( BST_NULL_PTR == s_pInstance )
    {
        s_pInstance                 = new BST_SRV_CChnlIpRcver ();
    }
    return s_pInstance;
}


BST_SRV_CChnlIpRcver::BST_SRV_CChnlIpRcver( BST_VOID )
{
}


BST_SRV_CChnlIpRcver::~BST_SRV_CChnlIpRcver( BST_VOID )
{
}


BST_IP_ERR_T BST_SRV_CChnlIpRcver::Connectd( BST_IP_CSocket *pcSocket )
{
    BST_DBG_LOG("BST_SRV_CChnlIpRcver Connectd. ");
#if ( ( BST_OS_VER == BST_WIN32 && BST_VER_TYPE == BST_DBG_VER ) || (BST_MODEM_SELF == 1) )
    BST_SRV_CHNL_LINK_STRU     *pstLinkItem = BST_NULL_PTR;
    BST_SRV_CHNL_LINK_STRU     *pstLinkItem2;
    BST_SRV_CHNL_HEAD_STRU     *pstPktItem;
    BST_ERR_ENUM_UINT8          enRtnVal;
    
    pstLinkItem                 = BST_SRV_Q_PeekHead( g_lstChnlMng );
    pstPktItem                  = BST_SRV_Q_PeekHead( pstLinkItem->pUnsendList );
    pstPktItem->ucPropType      = BST_IP_SKT_PROP_NONE; /*��ʹ�ð��е�socket����*/
    enRtnVal                    = BST_SRV_CHNL_Send_Runing( pstLinkItem, pstPktItem );
    if( BST_ERR_ILLEGAL_PARAM == enRtnVal )
    {
        BST_SRV_Q_RmvItem( (BST_SRV_CHNL_Q **)&g_lstChnlMng,
                           (BST_SRV_CHNL_Q *)pstLinkItem,
                           (BST_SRV_CHNL_Q **)&pstLinkItem2 );
        BST_OS_TimerRemove( pstLinkItem->ulTimerId );
        BST_DBG_LOG1( "tiger BST_OS_FREE 10,", pstLinkItem );
        BST_OS_FREE( pstLinkItem );
    }
#endif
    return BST_IP_ERR_OK;
}

BST_IP_PKTPROC_MODE_ENUM BST_SRV_CChnlIpRcver::Received(
    BST_IP_CSocket             *pcSocket,
    const BST_UINT8            *const pucData,
    const BST_UINT16            usLength )
{
    BST_DBG_LOG1( "BST_SRV_CChnlIpRcver::Received len", usLength );
    return BST_IP_PKT_REMOVE_PROC;/*CDS�Ѿ��������������ɾ��*/
}

BST_VOID BST_SRV_CChnlIpRcver::Acked (
    BST_IP_CSocket             *pcSocket,
    const BST_UINT32            ulMinNumber,
    const BST_UINT32            ulMaxNumber )
{
    BST_SRV_CHNL_LINK_STRU     *pstLinkItem;
    BST_SRV_CHNL_LINK_STRU     *pstLinkItem2;
    BST_DSPP_CAppUlVc          *pstDsppUl;
    BST_ERR_ENUM_UINT8          enRtnVal;

    pstLinkItem                 = BST_SRV_Q_PeekHead( g_lstChnlMng );
    /*�ҵ�ͬһ��socket*/
    while ( pstLinkItem != BST_NULL_PTR )
    {
        if ( pstLinkItem->pcSocket == pcSocket )
        {
            break;
        }
        pstLinkItem             = pstLinkItem->pNext;
    }
    if( BST_NULL_PTR == pstLinkItem )
    {
        return;
    }

    enRtnVal                    = BST_SRV_CHNL_Acked( pstLinkItem, ulMinNumber, ulMaxNumber );
    if( BST_ERR_SOCKET_CLSD == enRtnVal )/*Socket is closed*/
    {
        pstDsppUl                   = BST_DSPP_CAppUlVc::GetInstance();
        pstDsppUl->Report( BST_DSPP_FLG_CMD_CLEAR,
                           pstLinkItem->stLink.ulMainLinkId,
                           pstLinkItem->stLink.ulAuxLinkId );
        BST_SRV_CHNL_ReportTrafficFlow( pstLinkItem );
        BST_SRV_CHNL_Close( pstLinkItem );
        delete pstLinkItem->pcSocket;
        BST_SRV_Q_RmvItem( (BST_SRV_CHNL_Q **)&g_lstChnlMng, 
                           (BST_SRV_CHNL_Q *)pstLinkItem,
                           (BST_SRV_CHNL_Q **)&pstLinkItem2 );
        BST_OS_TimerRemove( pstLinkItem->ulTimerId );
        BST_OS_FREE( pstLinkItem );
        return;
    }

    /*��������ϱ���AP��֪ͨ�ײ�*/
    if( BST_SRV_IsChnlEmpty( pstLinkItem) )
    {
        pstDsppUl               = BST_DSPP_CAppUlVc::GetInstance();
        pstDsppUl->Report( BST_DSPP_FLG_CMD_SEND,
                           pstLinkItem->stLink.ulMainLinkId,
                           pstLinkItem->stLink.ulAuxLinkId );

        BST_SRV_CHNL_ReportTrafficFlow( pstLinkItem );

        BST_SRV_CHNL_Close( pstLinkItem );
        delete pstLinkItem->pcSocket;
        BST_SRV_Q_RmvItem( (BST_SRV_CHNL_Q **)&g_lstChnlMng,
                           (BST_SRV_CHNL_Q *)pstLinkItem,
                           (BST_SRV_CHNL_Q **)&pstLinkItem2 );
        BST_OS_TimerRemove( pstLinkItem->ulTimerId );
        BST_OS_FREE( pstLinkItem );
    }
}
BST_VOID BST_SRV_CChnlIpRcver::IpErr (
    BST_IP_CSocket             *pcSocket,
    BST_IP_ERR_T                InIpErrMsg )
{

    BST_SRV_CHNL_LINK_STRU     *pstLinkItem;
    BST_SRV_CHNL_LINK_STRU     *pstLinkItem2;
    BST_DSPP_CAppUlVc          *pstDsppUl;

    pstDsppUl                   = BST_DSPP_CAppUlVc::GetInstance();
    pstLinkItem                 = BST_SRV_Q_PeekHead( g_lstChnlMng );
    for(;;)
    {
        if( BST_NULL_PTR == pstLinkItem )
        {
            break;
        }
        if( pstLinkItem->pcSocket == pcSocket )
        {
            break;
        }
        pstLinkItem             = pstLinkItem->pNext;
    }

    if( BST_NULL_PTR == pstLinkItem )
    {
        return;
    }
    pstDsppUl->Report( BST_DSPP_FLG_CMD_CLOSE,
                       pstLinkItem->stLink.ulMainLinkId,
                       pstLinkItem->stLink.ulAuxLinkId );
    BST_SRV_CHNL_ReportTrafficFlow( pstLinkItem );

    BST_SRV_CHNL_Close( pstLinkItem );
    delete pstLinkItem->pcSocket;
    BST_SRV_Q_RmvItem( (BST_SRV_CHNL_Q **)&g_lstChnlMng,
                       (BST_SRV_CHNL_Q *)pstLinkItem,
                       (BST_SRV_CHNL_Q **)&pstLinkItem2 );
    BST_OS_TimerRemove( pstLinkItem->ulTimerId );
    BST_OS_FREE( pstLinkItem );
}

