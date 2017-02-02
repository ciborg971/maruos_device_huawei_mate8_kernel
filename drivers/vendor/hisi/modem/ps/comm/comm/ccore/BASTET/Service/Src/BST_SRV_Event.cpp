

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "BST_SRV_Event.h"
#include "BST_OS_Memory.h"
#include "BST_DBG_MemLeak.h"
#include "BST_SRV_AsEvnt.h"
#include "BST_SRV_AsCtrl.h"
#include "BST_DSPP_TrsLayer.h"
#include "BST_APP_MainTask.h"
#include "BST_DSPP_AppLayer.h"
#include "BST_CORE_Schd.h"
#include "lwip/tcpip.h"

/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_BST_SRV_EVENT_CPP
/*lint +e767*/

/******************************************************************************
   2 �궨��
******************************************************************************/

/*****************************************************************************
  3 ��������
*****************************************************************************/
extern "C" sys_mbox_t   mbox;
/******************************************************************************
   4 ˽�ж���
******************************************************************************/

/******************************************************************************
   5 ȫ�ֱ�������
******************************************************************************/

/******************************************************************************
   6 ����ʵ��
******************************************************************************/


BST_VOID BST_SRV_InitInstance( BST_VOID )
{
    BST_SRV_CAsEvt::GetInstance();
    BST_SRV_CAsCtrl::GetInstance();
    BST_CTaskSchdler::GetInstance ();
    BST_APP_CMainTask::GetInstance();
    BST_IP_CAsRcver::GetInstance();
}


BST_UINT32 BST_SRV_ApiSendAcomRxEvent( BST_UINT32 ulLength, BST_UINT8 *pucData )
{
    BST_ACOM_EVT_STRU      *pstAcpuEvent;
    BST_OS_MBX_T           *pstEventMbx;
    BST_ERR_ENUM_UINT8      enSndResult;

    if( BST_NULL_PTR == pucData )
    {
        return 0;
    }
    if( 0 == ulLength )
    {
        return 0;
    }

    pstEventMbx             = BST_SRV_GetSysMsgHandle();
    if( BST_NULL_PTR == pstEventMbx )
    {
        return 0;
    }

    pstAcpuEvent            = (BST_ACOM_EVT_STRU *)
                               BST_OS_MALLOC( BST_OS_SIZEOF(BST_ACOM_EVT_STRU) );
    BST_ASSERT_NULL_RTN( pstAcpuEvent, BST_ERR_NO_MEMORY );

    pstAcpuEvent->pucData   = (BST_UINT8 *)BST_OS_MALLOC( ulLength );
    if ( BST_NULL_PTR == pstAcpuEvent->pucData )
    {
        BST_OS_FREE( pstAcpuEvent );
        return 0;
    }

    pstAcpuEvent->enId      = BST_SRV_ACOM_EVENT;
    pstAcpuEvent->ulLength  = ulLength;
    BST_OS_MEMCPY( pstAcpuEvent->pucData, pucData, ulLength );
    enSndResult             = BST_OS_SendMail( pstEventMbx, pstAcpuEvent );
    if( BST_NO_ERROR_MSG == enSndResult )
    {
        return ulLength;
    }
    else
    {
        BST_OS_FREE( pstAcpuEvent->pucData );
        BST_OS_FREE( pstAcpuEvent );
        return 0;
    }
}


BST_UINT32 BST_SRV_ApiSendPTaskEvent(
    BST_VOID               *pvTask,
    BST_UINT16              enComdId,
    BST_UINT16              usContnt )
{
    BST_PTASK_EVT_STRU             *pcPTaskEvent;
    BST_OS_MBX_T                   *pstMsgHandle;
    BST_CORE_CPTask                *pPtackIns;
    BST_ERR_ENUM_UINT8              enSndResult;

    pPtackIns                       = ( BST_CORE_CPTask *)pvTask;
    if( BST_NULL_PTR == pPtackIns )
    {
        return 0;
    }
    /**
     �����schd���͵�����ģ���ô���������ȡ����Ϣ���
    */
    if( BST_CORE_IS_S2T_CMD( enComdId ) )
    {
        pstMsgHandle                = BST_SRV_GetTaskMsgHandle
                                    ( pPtackIns->m_usProcId, pPtackIns->m_usTaskId );
    }
    /**
     �����task���͵�schd�ģ���ôȡϵͳ��Ϣ���
    */
    else if( enComdId < BST_SRV_SCHD_EVEN_BUTT )
    {
        pstMsgHandle                = BST_SRV_GetSysMsgHandle();
    }
    else
    {
        pstMsgHandle                = BST_NULL_PTR;
    }
    if( BST_NULL_PTR == pstMsgHandle )
    {
        return 0;
    }

    pcPTaskEvent                    = ( BST_PTASK_EVT_STRU *)BST_OS_MALLOC
                                      ( BST_OS_SIZEOF(BST_PTASK_EVT_STRU) );
    BST_ASSERT_NULL_RTN( pcPTaskEvent, 0 );

    pcPTaskEvent->pucData           = ( BST_UINT8 *)pvTask;
    pcPTaskEvent->ulLength          = BST_OS_SIZEOF( BST_PTASK_EVT_STRU );
    pcPTaskEvent->enId              = BST_SRV_PTASK_EVENT;
    pcPTaskEvent->usContent         = usContnt;
    pcPTaskEvent->usMsgId           = enComdId;
    enSndResult                     = BST_OS_SendMail( pstMsgHandle, pcPTaskEvent );
    if( BST_NO_ERROR_MSG == enSndResult )
    {
        return BST_OS_SIZEOF( BST_PTASK_EVT_STRU );
    }
    else
    {
        BST_OS_FREE( pcPTaskEvent );
        return 0;
    }
}


BST_UINT32 BST_SRV_ApiSendAsEvent(
    BST_VOID               *pcInAsRcver,
    BST_AS_EVT_ENUM_UINT32  enAsEvent,
    BST_UINT32              ulLength,
    BST_VOID               *pvData )
{
    BST_SRV_CAsRcver       *pcAsRcver;
    BST_AS_EVT_STRU        *pstSendAsEvent;
    BST_ERR_ENUM_UINT8      enSndResult;

    pcAsRcver               = ( BST_SRV_CAsRcver *)pcInAsRcver;

    if( BST_NULL_PTR == pcAsRcver )
    {
        return BST_ERR_INVALID_PTR;
    }
    if ( pcAsRcver->m_pstRcvMbox == (BST_OS_MBX_T *)mbox )
    {
        BST_DBG_LOG("BST_SRV_ApiSendAsEvent");
        return BST_SRV_ApiSendLwipAsEvent( pcInAsRcver, enAsEvent, ulLength, pvData );
    }
    if( !BST_SRV_IsValidAsEvent( enAsEvent ) )
    {
        return BST_ERR_INVALID_PTR;
    }
    pstSendAsEvent          = (BST_AS_EVT_STRU *)
                               BST_OS_MALLOC( BST_OS_SIZEOF(BST_AS_EVT_STRU) );
    BST_ASSERT_NULL_RTN( pstSendAsEvent, BST_ERR_NO_MEMORY );

    pstSendAsEvent->pucData = ( BST_UINT8 *)BST_OS_MALLOC( ulLength );
    if ( BST_NULL_PTR == pstSendAsEvent->pucData )
    {
        BST_OS_FREE( pstSendAsEvent );
        return 0;
    }
    BST_OS_MEMCPY( pstSendAsEvent->pucData, pvData, ulLength );
    pstSendAsEvent->pcRcver = pcAsRcver;
    pstSendAsEvent->enMsgId = enAsEvent;
    pstSendAsEvent->ulLength= ulLength;
    pstSendAsEvent->enId    = BST_SRV_AS_EVENT;

    enSndResult             = BST_OS_SendMail( 
                            ( BST_OS_MBX_T * )pcAsRcver->m_pstRcvMbox,
                                              pstSendAsEvent );
    if( BST_NO_ERROR_MSG == enSndResult )
    {
        return ( BST_UINT32 )BST_OS_SIZEOF( pcAsRcver );
    }
    else
    {
        BST_OS_FREE( pstSendAsEvent->pucData );
        BST_OS_FREE( pstSendAsEvent );
        return 0;
    }
}

BST_UINT32 BST_SRV_ApiSendLwipAsEvent(
    BST_VOID               *pcInAsRcver,
    BST_AS_EVT_ENUM_UINT32  enAsEvent,
    BST_UINT32              ulLength,
    BST_VOID               *pvData )
{
    BST_SRV_CAsRcver           *pcAsRcver;
    struct tcpip_msg           *pstLwipMsg;
    BST_UINT8                  *pucData;
    BST_ERR_ENUM_UINT8          enSndResult;

    pcAsRcver               = ( BST_SRV_CAsRcver *)pcInAsRcver;

    if( BST_NULL_PTR == pcAsRcver )
    {
        return BST_ERR_INVALID_PTR;
    }

    if( !BST_SRV_IsValidAsEvent( enAsEvent ) )
    {
        return BST_ERR_INVALID_PTR;
    }

    pstLwipMsg                  = ( struct tcpip_msg *)BST_OS_MALLOC
                                  ( BST_OS_SIZEOF(struct tcpip_msg) );
    if ( BST_NULL_PTR == pstLwipMsg )
    {
        return 0;
    }

    pucData                     = ( BST_UINT8 *)BST_OS_MALLOC( ulLength );
    if ( BST_NULL_PTR == pucData )
    {
        BST_OS_FREE(pstLwipMsg);
        return 0;
    }
    BST_OS_MEMCPY( pucData, pvData, ulLength );
    pstLwipMsg->type            = TCPIP_MSG_BST_ASEVENT;
    pstLwipMsg->msg.bst_asevent.stAsEvent.pcRcver
                                = pcAsRcver;
    pstLwipMsg->msg.bst_asevent.stAsEvent.enMsgId
                                = enAsEvent;
    pstLwipMsg->msg.bst_asevent.stAsEvent.enId
                                = BST_SRV_AS_EVENT;
    pstLwipMsg->msg.bst_asevent.stAsEvent.pucData
                                = pucData;
    pstLwipMsg->msg.bst_asevent.stAsEvent.ulLength
                                = ulLength;

    enSndResult                 = BST_OS_SendMail( (BST_OS_MBX_T *)mbox, pstLwipMsg );
    if( BST_NO_ERROR_MSG == enSndResult )
    {
        return ( BST_UINT32 )BST_OS_SIZEOF( struct tcpip_msg );
    }
    else
    {
        BST_OS_FREE( pucData );
        BST_OS_FREE( pstLwipMsg );
        return 0;
    }
}


BST_UINT32 BST_SRV_ApiSendLwipTimerEvent( BST_OS_TIMERID_T ulTimerId )
{
    struct tcpip_msg           *pstLwipMsg;
    BST_ERR_ENUM_UINT8          enSndResult;

    pstLwipMsg                  = ( struct tcpip_msg *)BST_OS_MALLOC
                                  ( BST_OS_SIZEOF(struct tcpip_msg) );
    if ( BST_NULL_PTR == pstLwipMsg )
    {
        return 0;
    }

    pstLwipMsg->type            = TCPIP_MSG_BST_TIMEOUT;
    pstLwipMsg->msg.bst_tmo.id  = ulTimerId;
    enSndResult                 = BST_OS_SendMail( (BST_OS_MBX_T *)mbox, pstLwipMsg );
    if( BST_NO_ERROR_MSG == enSndResult )
    {
        return ( BST_UINT32 )BST_OS_SIZEOF( struct tcpip_msg );
    }
    else
    {
        BST_OS_FREE( pstLwipMsg );
        return 0;
    }
}


BST_UINT32 BST_SRV_ApiSendExpiredEvent(
    BST_VOID           *pstRcvHandle,
    BST_UINT32          ulTimerId )
{
    BST_TIMER_EVT_STRU                 *pstSendTimerEvent;
    BST_ERR_ENUM_UINT8                  enSndResult;

    BST_ASSERT_NULL_RTN( pstRcvHandle, BST_ERR_NO_MEMORY );

    if ( pstRcvHandle == (BST_VOID *)mbox )
    {
        return BST_SRV_ApiSendLwipTimerEvent( ulTimerId );
    }
    pstSendTimerEvent                   = ( BST_TIMER_EVT_STRU *)BST_OS_MALLOC
                                          ( BST_OS_SIZEOF(BST_TIMER_EVT_STRU) );
    BST_ASSERT_NULL_RTN( pstSendTimerEvent, BST_ERR_NO_MEMORY );

    pstSendTimerEvent->pucData          = ( BST_UINT8 *)BST_OS_MALLOC
                                          ( BST_OS_SIZEOF(ulTimerId) );
    if ( BST_NULL_PTR == pstSendTimerEvent->pucData )
    {
        BST_OS_FREE( pstSendTimerEvent );
        return 0;
    }

    pstSendTimerEvent->ulLength         = BST_OS_SIZEOF( ulTimerId );
    BST_OS_MEMCPY( pstSendTimerEvent->pucData,
                  &ulTimerId,
                   pstSendTimerEvent->ulLength );

    pstSendTimerEvent->enId             = BST_SRV_TIMER_EVENT;

    enSndResult                         = BST_OS_SendMail(
                                          (BST_OS_MBX_T *)pstRcvHandle,
                                                          pstSendTimerEvent );
    if( BST_NO_ERROR_MSG == enSndResult )
    {
        return BST_OS_SIZEOF(BST_OS_TIMER_STRU);
    }
    else
    {
        BST_OS_FREE( pstSendTimerEvent->pucData );
        BST_OS_FREE( pstSendTimerEvent );
        return 0;
    }
}


BST_UINT32 BST_SRV_ApiSendTcpIpEvent(
    BST_VOID           *pstRcver,
    BST_VOID           *pstEvent )
{
    BST_IP_EVENT_STRU                  *pstNetEvent;
    BST_ERR_ENUM_UINT8                  enSndResult;

    if ( BST_NULL_PTR == pstEvent )
    {
        return 0;
    }
    if ( BST_NULL_PTR == pstRcver )
    {
        pstRcver                        = BST_SRV_GetSysMsgHandle();
    }

    pstNetEvent                         = ( BST_IP_EVENT_STRU  *)BST_OS_MALLOC
                                          ( BST_OS_SIZEOF ( BST_IP_EVENT_STRU ) );
    if ( BST_NULL_PTR == pstNetEvent )
    {
        return 0;
    }

    BST_OS_MEMCPY ( pstNetEvent, pstEvent, BST_OS_SIZEOF ( BST_IP_EVENT_STRU ) );

    pstNetEvent->enId                   = BST_SRV_TCPIP_EVENT;
    pstNetEvent->pucData                = BST_NULL_PTR;
    pstNetEvent->ulLength               = 0;
    enSndResult                         = BST_OS_SendMail(
                                          (BST_OS_MBX_T *)pstRcver,
                                                          pstNetEvent );
    if( BST_NO_ERROR_MSG == enSndResult )
    {
        return BST_OS_SIZEOF(BST_IP_EVENT_STRU);
    }
    else
    {
        BST_OS_FREE( pstNetEvent );
        return 0;
    }
}


BST_UINT32 BST_SRV_ApiSendDsppEvent(
    BST_UINT32             ulMsgId,
    BST_UINT32             ulApVer,
    BST_UINT32             const ulBufLen,
    BST_VOID              *const pstHeadInfo,
    BST_VOID              *pstRcvHandle )
{
    BST_DSPP_EVT_STRU                  *pstEvent;
    BST_UINT8                          *pstHeadCopy;
    BST_ERR_ENUM_UINT8                  enSndResult;

    if ( BST_NULL_PTR == pstHeadInfo )
    {
        return 0;
    }
    if ( BST_NULL_PTR == pstRcvHandle )
    {
        return 0;
    }
    pstEvent                            = ( BST_DSPP_EVT_STRU *)BST_OS_MALLOC
                                          ( BST_OS_SIZEOF ( BST_DSPP_EVT_STRU ) );
    if ( BST_NULL_PTR == pstEvent )
    {
        return 0;
    }
    /*
     * ����DSPPЭ��汾��ȷ��ʹ���ڴ���䷽�� 
     */
    if ( BST_DSPP_VER_C == ulApVer )
    {
        pstHeadCopy                         = ( BST_UINT8 *)pstHeadInfo;
    }
    else
    {
        pstHeadCopy                         = ( BST_UINT8 *)BST_OS_MALLOC( ulBufLen );
        if ( BST_NULL_PTR == pstHeadCopy )
        {
            BST_OS_FREE( pstEvent );
            return 0;
        }
        /*pstHeadInfoָ�����һ����ʱ����*/
        BST_OS_MEMCPY ( pstHeadCopy, pstHeadInfo, ulBufLen );
    }

    pstEvent->enId                      = BST_SRV_DSPP_EVENT;
    pstEvent->ulMsgId                   = ulMsgId;
    pstEvent->pucData                   = pstHeadCopy;
    pstEvent->ulLength                  = ulBufLen;
    pstEvent->ulAPVer                   = ulApVer;
    enSndResult                         = BST_OS_SendMail( (BST_OS_MBX_T *)pstRcvHandle, pstEvent );
    BST_DBG_LOG1( "CPC_PACKET_DROP BST_OS_SendMail Result", enSndResult );
    if( BST_NO_ERROR_MSG == enSndResult )
    {
        return ulBufLen;
    }
    else
    {
        BST_OS_FREE( pstEvent->pucData );
        BST_OS_FREE( pstEvent );
        return 0;
    }
}
BST_VOID BST_SRV_EvtProcRxAcom( BST_EVT_HEAD_STRU *pvInData )
{
    BST_DSPP_CTrsDlVa      *pcTrslayer;
    BST_ACOM_EVT_STRU      *pstEvtData;

    pstEvtData              = ( BST_ACOM_EVT_STRU * )pvInData;
    pcTrslayer              = BST_DSPP_CTrsDlVa::GetInstance();
    if ( BST_NULL_PTR == pcTrslayer )
    {
        return;
    }
    pcTrslayer->RxApi( pstEvtData->pucData, (BST_UINT16)pstEvtData->ulLength );
    pstEvtData->pucData     = BST_NULL_PTR;
    pstEvtData->ulLength    = 0;
}


BST_VOID BST_SRV_EvtProcRcvAs( BST_EVT_HEAD_STRU *pvInData )
{
    BST_AS_EVT_STRU        *pstEvtData;
    BST_SRV_CAsEvt         *pcAsMng;
    pcAsMng                 = BST_SRV_CAsEvt::GetInstance();
    pstEvtData              = ( BST_AS_EVT_STRU * )pvInData;

    pcAsMng->Forward( ( BST_SRV_CAsRcver *)pstEvtData->pcRcver,
                                           pstEvtData->enMsgId,
                                           pstEvtData->ulLength,
                               (BST_VOID *)pstEvtData->pucData );

}


BST_VOID BST_SRV_EvtProcExpired( BST_EVT_HEAD_STRU *pvInData )
{
    BST_OS_TIMER_STRU                  *pstTimer;
    BST_TIMER_EVT_STRU                 *pstTimerEvt;
    BST_OS_TIMERID_T                    ulId;

    pstTimerEvt                         = (BST_TIMER_EVT_STRU *)pvInData;
    if( BST_OS_SIZEOF(ulId) != pstTimerEvt->ulLength )
    {
        return;
    }
    BST_OS_MEMCPY( &ulId, pstTimerEvt->pucData, BST_OS_SIZEOF(ulId) );

    pstTimer                            = BST_OS_TimerSrch( ulId );
    if( BST_NULL_PTR == pstTimer )
    {
        return;
    }
    if( BST_OS_TIMER_CB_CLASS == pstTimer->enCbMode )
    {
        if( BST_NULL_PTR == pstTimer->unCallBack.pc )
        {
            return;
        }
        pstTimer->unCallBack.pc->TimerExpired( pstTimer->ulId , pstTimer->pvPara );
    }
    else if( BST_OS_TIMER_CB_FUN == pstTimer->enCbMode )
    {
        if( BST_NULL_PTR == pstTimer->unCallBack.pf )
        {
            return;
        }
        pstTimer->unCallBack.pf( pstTimer->ulId , pstTimer->pvPara );
    }
}


BST_VOID BST_SRV_EvtProcLwipExpired( BST_VOID *pstLwipMsg )
{
    BST_OS_TIMER_STRU                  *pstTimer;
    if( BST_NULL_PTR == pstLwipMsg )
    {
        return;
    }
    pstTimer                            = BST_OS_TimerSrch(
                                          ( ( struct tcpip_msg *)pstLwipMsg )->msg.bst_tmo.id);
    if( BST_NULL_PTR == pstTimer )
    {
        BST_OS_FREE( pstLwipMsg );
        return;
    }
    if( BST_OS_TIMER_CB_CLASS == pstTimer->enCbMode )
    {
        if( BST_NULL_PTR == pstTimer->unCallBack.pc )
        {
            BST_OS_FREE( pstLwipMsg );
            return;
        }
        pstTimer->unCallBack.pc->TimerExpired( pstTimer->ulId , pstTimer->pvPara );
    }
    else if( BST_OS_TIMER_CB_FUN == pstTimer->enCbMode )
    {
        if( BST_NULL_PTR == pstTimer->unCallBack.pf )
        {
            BST_OS_FREE( pstLwipMsg );
            return;
        }
        pstTimer->unCallBack.pf( pstTimer->ulId , pstTimer->pvPara );
    }
    BST_OS_FREE( pstLwipMsg );
}

BST_VOID BST_SRV_EvtProcLwipAsEvent( BST_VOID *pstLwipMsg )
{
    BST_AS_EVT_STRU         stEvtData;
    BST_SRV_CAsEvt         *pcAsMng;
    pcAsMng                 = BST_SRV_CAsEvt::GetInstance();
    stEvtData               = ( (struct tcpip_msg *)pstLwipMsg )->msg.bst_asevent.stAsEvent;
    if ( BST_NULL_PTR == pcAsMng )
    {
        BST_OS_FREE( stEvtData.pucData );
        BST_OS_FREE( pstLwipMsg );
        return;
    }
    pcAsMng->Forward( ( BST_SRV_CAsRcver *)stEvtData.pcRcver,
                                           stEvtData.enMsgId,
                                           stEvtData.ulLength,
                               (BST_VOID *)stEvtData.pucData );
    BST_OS_FREE( stEvtData.pucData );
    BST_OS_FREE( pstLwipMsg );
}


BST_VOID BST_SRV_EvtProcStoT( BST_EVT_HEAD_STRU *pstEvent )
{
    BST_PTASK_EVT_STRU         *pstPtskEvent;
    BST_CORE_CPTask            *pPtackIns;
    BST_OS_MBX_T               *pstMsgHandle;
    BST_DBG_LOG("BST_SRV_EvtProcStoT");


    pstPtskEvent                = ( BST_PTASK_EVT_STRU *)pstEvent;
    if( BST_NULL_PTR == pstPtskEvent )
    {
        return;
    }
    /**
     ��������Ƿ���ڣ���������ɾ����Ĵ������
    */
    pPtackIns                   = ( BST_CORE_CPTask* )pstPtskEvent->pucData;

    if( BST_NULL_PTR == pPtackIns )
    {
        BST_DBG_LOG("pPtackIns is null");
        return;
    }
    
    pstMsgHandle                = BST_SRV_GetTaskMsgHandle
                                ( pPtackIns->m_usProcId, pPtackIns->m_usTaskId );
    if( BST_NULL_PTR == pstMsgHandle )
    {
    
        BST_DBG_LOG("pstMsgHandle is null");
        return;
    }
    
    BST_DBG_LOG1("pstPtskEvent->usMsgId:%d",pstPtskEvent->usMsgId);

    switch( pstPtskEvent->usMsgId )
    {
         /*schd֪ͨtask ִ����������*/        
        case BST_SRV_S2T_EXE_COMAND:
            pPtackIns->onExecute();
        break;

         /*schd֪ͨtask socket���쳣�ر���*/  
        case BST_SRV_S2T_ERR_CLOSED:
            pPtackIns->onCycleError();
        break;

         /*schd֪ͨtask ���ڱ�����*/          
        case BST_SRV_S2T_CYC_UPDATE:
            pPtackIns->onUpdateCycle( pstPtskEvent->usContent );
        break;

        default:
        break;
    }
    pstPtskEvent->pucData       = BST_NULL_PTR;
}
BST_VOID BST_SRV_EvtProcTtoS( BST_EVT_HEAD_STRU *pstEvent )
{
    BST_CTaskSchdler           *pcSchdler;
    BST_PTASK_EVT_STRU         *pstPtskEvent;

    pcSchdler                   = BST_CTaskSchdler::GetInstance();
    pstPtskEvent                = ( BST_PTASK_EVT_STRU *)pstEvent;

    if( BST_NULL_PTR == pstPtskEvent )
    {
        BST_RLS_LOG("BST_SRV_EvtProcTtoS pstPtskEvent is null");
        return;
    }

    if( BST_NULL_PTR == pcSchdler )
    {
        BST_RLS_LOG("BST_SRV_EvtProcTtoS pcSchdler is null");
        return;
    }

    if( BST_NULL_PTR == pstPtskEvent->pucData )
    {
        BST_RLS_LOG("BST_SRV_EvtProcTtoS pstPtskEvent->pucData is null");
        return;
    }

    switch( pstPtskEvent->usMsgId )
    {
         /*task֪ͨschd �����񴴽�������*/    
        case BST_SRV_T2S_TSK_ATTACH:
            pcSchdler->Attach( (BST_CORE_CPTask *) pstPtskEvent->pucData );
        break;

         /*task֪ͨschd ����ȥ����*/          
        case BST_SRV_T2S_TSK_DETACH:
            pcSchdler->Detach( (BST_CORE_CPTask *) pstPtskEvent->pucData );
        break;

         /*task֪ͨschd ֪�ᵱǰ����ִ�н��*/
        case BST_SRV_T2S_ACK_RESULT:
            pcSchdler->AckSendResult
                    ( (BST_CORE_CPTask *) pstPtskEvent->pucData, pstPtskEvent->usContent );
        break;

         /*task֪ͨschd ����ֹͣ(��̽����)*/
        case BST_SRV_T2S_RUN_STOPED:
            pcSchdler->TaskStoped( (BST_CORE_CPTask *) pstPtskEvent->pucData );
        break;

         /*task֪ͨschd ����ָ�(��̽����)*/  
        case BST_SRV_T2S_RUN_RESUME:
            pcSchdler->TaskStarted( (BST_CORE_CPTask *) pstPtskEvent->pucData );
        break;

         /*task֪ͨschd ����̽��������ID*/    
        case BST_SRV_T2S_DEF_DETCET:
            pcSchdler->DefineDetector( (BST_CORE_CPTask *) pstPtskEvent->pucData );
        break;

        default:
        break;
    }
    pstPtskEvent->pucData       = BST_NULL_PTR;
}


BST_VOID BST_SRV_EvtProcDsppCmd( BST_EVT_HEAD_STRU *pstEvent )
{
    BST_DSPP_CAppDlVa          *pcApalayer;
    BST_DSPP_CAppDlVc          *pcApclayer;
    BST_DSPP_EVT_STRU          *pstDsppEvt;
    BST_DSPP_HEAD_STRU         *pstDsppHeadInfo;

    pstDsppEvt                  = ( BST_DSPP_EVT_STRU  *)pstEvent;
    if ( BST_NULL_PTR == pstDsppEvt )
    {
        return;
    }

    BST_DBG_LOG1( "CPC_PACKET_DROP BST_SRV_EvtProcDsppCmd Vesion", pstDsppEvt->ulAPVer );
    if( BST_DSPP_VER_C == pstDsppEvt->ulAPVer)
    {
        pcApclayer              = BST_DSPP_CAppDlVc::GetInstance();
        if ( BST_NULL_PTR == pcApclayer )
        {
            return;
        }
        pcApclayer->ProcAction( ( BST_SRV_CHNL_HEAD_STRU * )pstDsppEvt->pucData );
        /**
         * To avoid the thread free this data
         */
        pstDsppEvt->pucData     = BST_NULL_PTR;
    }
    else
    {
        pstDsppHeadInfo         = ( BST_DSPP_HEAD_STRU *)pstDsppEvt->pucData;
        if ( BST_NULL_PTR == pstDsppHeadInfo )
        {
            return;
        }
        pcApalayer              = BST_DSPP_CAppDlVa::GetInstance();
        if ( BST_NULL_PTR == pcApalayer )
        {
            return;
        }
        pcApalayer->ProcAction( ( BST_DSPP_HEAD_STRU *const )pstDsppHeadInfo,
                                pstDsppHeadInfo->stCpVerA.usOfstAddr,
                                pstDsppHeadInfo->stCpVerA.usObjtAddr );
   }
}


BST_VOID BST_SRV_EvtProcTCPIP( BST_EVT_HEAD_STRU *pstEvent )
{
    BST_IP_EVENT_STRU          *pstNetEvt;

    pstNetEvt                   = ( BST_IP_EVENT_STRU  *)pstEvent;
    if( BST_NULL_PTR == pstEvent )
    {
        return;
    }
    switch ( pstNetEvt->ulMsgId )
    {
        case BST_IP_EVENT_RECV:
            BST_IP_ReceivedCB( pstNetEvt->lFd );
            break;

        case BST_IP_EVENT_CONNECTED:
            BST_IP_TcpConnectedCB( pstNetEvt->lFd );
            break;

        case BST_IP_EVENT_ERR:
            BST_IP_TcpErrorCB( pstNetEvt->lFd, pstNetEvt->lErrMsg );
            break;

        case BST_IP_EVENT_OVERFLOW:
            BST_IP_TcpOverFlowCB( pstNetEvt->lFd );
            break;

        case BST_IP_EVENT_ACKED:
            BST_IP_TcpAckedCB( pstNetEvt->lFd, pstNetEvt->ulMinNumber, pstNetEvt->ulMaxNumber );
            break;

        default:
            break;
    }
}


BST_VOID BST_SRV_ProcAppEvent( BST_EVT_HEAD_STRU *pstEvent )
{
    switch( pstEvent->enId )
    {
        case BST_SRV_AS_EVENT:
            BST_SRV_EvtProcRcvAs( pstEvent );
            break;

        case BST_SRV_TIMER_EVENT:
            BST_SRV_EvtProcExpired( pstEvent );
            break;

        case BST_SRV_TCPIP_EVENT:
            BST_SRV_EvtProcTCPIP ( pstEvent );
            break;

        case BST_SRV_DSPP_EVENT:
            BST_SRV_EvtProcDsppCmd( pstEvent );
            break;

        case BST_SRV_PTASK_EVENT:
            BST_SRV_EvtProcStoT( pstEvent );
            break;

        default:
            break;
    }
}


BST_VOID BST_SRV_ProcSysEvent( BST_EVT_HEAD_STRU *pstEvent )
{
    switch( pstEvent->enId )
    {
        case BST_SRV_ACOM_EVENT:
            BST_SRV_EvtProcRxAcom( pstEvent );
            break;

        case BST_SRV_AS_EVENT:
            BST_SRV_EvtProcRcvAs( pstEvent );
            break;

        case BST_SRV_TIMER_EVENT:
            BST_SRV_EvtProcExpired( pstEvent );
            break;

        case BST_SRV_TCPIP_EVENT:
            BST_SRV_EvtProcTCPIP ( pstEvent );
            break;

        case BST_SRV_DSPP_EVENT:
            BST_SRV_EvtProcDsppCmd( pstEvent );
            break;

        case BST_SRV_PTASK_EVENT:
            BST_SRV_EvtProcTtoS( pstEvent );
            break;

        default:
            break;
    }
}



BST_VOID BST_SRV_ProcChnlCtrEvent( BST_EVT_HEAD_STRU *pstEvent )
{
    switch( pstEvent->enId )
    {
        case BST_SRV_AS_EVENT:
            BST_SRV_EvtProcRcvAs( pstEvent );
            break;

        case BST_SRV_TIMER_EVENT:
            BST_SRV_EvtProcExpired( pstEvent );
            break;

        case BST_SRV_TCPIP_EVENT:
            BST_SRV_EvtProcTCPIP ( pstEvent );
            break;

        case BST_SRV_DSPP_EVENT:
            BST_SRV_EvtProcDsppCmd( pstEvent );
            break;

        default:
            break;
    }
}

