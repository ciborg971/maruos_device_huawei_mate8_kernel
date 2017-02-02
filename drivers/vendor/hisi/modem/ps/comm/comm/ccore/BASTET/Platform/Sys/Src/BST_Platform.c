

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "BST_Platform.h"
#include "BST_OS_Thread.h"
#include "BST_OS_Memory.h"
#include "BST_OS_Timer.h"
#include "BST_OS_Log.h"
#include "BST_DRV_Acom.h"
#include "BST_DRV_As.h"
#include "BST_DRV_Net.h"
#include "BST_PAL_Acom.h"
#include "BST_SYS_MsgProc.h"
#include "BST_PAL_As.h"
#include "NVIM_Interface.h"
#include "BST_DRV_LinkSta.h"
#include "TafNvInterface.h"

/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_BST_PLATFORM_C
/*lint +e767*/
/*****************************************************************************
  2 ��������
*****************************************************************************/
extern BST_VOID BST_SRV_InitInstance( BST_VOID );
extern BST_VOID BST_SRV_InitMultiThread( BST_VOID );
extern BST_VOID BST_PAL_NetApiInitial   ( BST_VOID );
extern BST_VOID BST_OS_PalTimerCallBack ( BST_VOID );
extern BST_VOID BST_IP_ApiInitPortPreproc( BST_VOID );
BST_VOID        BST_SYS_InitDriver      ( BST_VOID );
BST_UINT32      BST_SYS_InitThread      ( BST_VOID );
/******************************************************************************
  3 ȫ�ֱ�������
******************************************************************************/
BST_UINT32                              g_ulBastetTaskId    = 0;
BST_UINT32                              g_BstThreadInitFlags= 0;
BST_UINT32                              g_ulBstTaskReadyFlag= BST_FALSE;
extern BST_OS_SPINLOCK_T                g_MboxLock;
BST_BOOL                                g_BstBastetFlg = BST_FALSE;
/******************************************************************************
  4 ����ʵ��
******************************************************************************/


BST_VOID BST_SYS_InitPlatform( BST_VOID )
{
    if(BST_FALSE == BST_SYS_ApiGetSupported())
    {
        BST_DBG_LOG("BST_SYS_InitPlatform: bastet nv disabled");
        return;
    }

    BST_OS_InitLock();
    BST_OS_InitSpinLock( &g_MboxLock );
    BST_OS_MemInit();
    BST_OS_TimerSysInit();
    if( BST_TRUE == BST_SYS_InitThread() )
    {
        BST_DBG_INITIAL();
        BST_SYS_InitDriver();
    }
}


BST_VOID BST_SYS_InitDriver( BST_VOID )
{
    BST_DRV_STRU   *pDrvHandle;

    pDrvHandle      = BST_DRV_AcomGetDvcHandle();
    pDrvHandle->pfInit( pDrvHandle );

    pDrvHandle      = BST_DRV_AsGetDvcHandle();
    pDrvHandle->pfInit( pDrvHandle );

    pDrvHandle      = BST_DRV_LsGetDvcHandle();
    pDrvHandle->pfInit( pDrvHandle );
}


BST_UINT32 BST_SYS_InitThread( BST_VOID )
{
    BST_SRV_InitMultiThread();
    /*
     * �л��̣߳����߳���ȫ������
     * ֮��BST_SRV_CAsCtrl���ڹ��캯����
     * ��ʼ���б��л�ȡ�̵߳ľ��ʱ�Ų���ʧ��
     */
    BST_OS_SleepMs( 500 );
    BST_IP_ApiInitPortPreproc();
    BST_PAL_NetApiInitial();
    BST_SRV_InitInstance();
    return BST_TRUE;
}


BST_VOID BST_SYS_InitBastetNvFlag(BST_VOID)
{
    BASTET_SUPPORT_FLG_STRU                     stBastetFlag;
    TAF_NV_LC_CTRL_PARA_STRU                    stLcCtrlPara;

    PS_MEM_SET(&stBastetFlag, 0x00, sizeof(BASTET_SUPPORT_FLG_STRU));
    PS_MEM_SET(&stLcCtrlPara, 0x00, sizeof(stLcCtrlPara));

    /* ��NV��en_NV_MODEM_RF_SHARE_CFG��ʧ�ܣ�ֱ�ӷ��� */
    if (NV_OK != NV_Read(en_NV_Item_Bastet_CONFIG,
                         &stBastetFlag, sizeof(BASTET_SUPPORT_FLG_STRU)))
    {
        BST_RLS_LOG("BST_SYS_InitBastetNvFlag():WARNING: read en_NV_Item_Bastet_CONFIG Error");

        return;
    }

    if (BST_TRUE != stBastetFlag.ucActiveFlg)
    {
        /* NV�����쳣���� */
        g_BstBastetFlg  = BST_FALSE;
    }
    else
    {
        g_BstBastetFlg  = BST_TRUE;
        BST_PAL_SetLogSwitch(stBastetFlag.ucHookFlg);
    }

    /* ��NV���Ƿ�CLģʽnv�ʧ�ܣ�ֱ�ӷ��� */
    if (NV_OK != NV_Read(en_NV_Item_LC_Ctrl_PARA,
                         &stLcCtrlPara,
                         sizeof(stLcCtrlPara)))
    {
        BST_RLS_LOG("BST_SYS_InitBastetNvFlag():WARNING: read en_NV_Item_LC_Ctrl_PARA Error");
        return;
    }

    /*�����ǰ������CLģʽ��bastetģ���ݲ�֧��*/
    if ((BST_TRUE == stLcCtrlPara.ucLCEnableFlg )
        && (TAF_NVIM_LC_RAT_COMBINED_CL == stLcCtrlPara.enRatCombined))
    {
        g_BstBastetFlg  = BST_FALSE;
    }

    return;
}


BST_BOOL BST_SYS_ApiGetSupported(BST_VOID)
{
    return g_BstBastetFlg;
}




VOS_VOID BST_SYS_MsgProcEntry( MsgBlock  *pstMsg )
{
    if(BST_FALSE == BST_SYS_ApiGetSupported())
    {
        BST_DBG_LOG("BST_SYS_MsgProcEntry: bastet nv disabled");
        return;
    }

    switch(pstMsg->ulSenderPid)
    {
        case VOS_PID_TIMER:
            BST_DBG_LOG("BST_SYS_MsgProcEntry: VOS_PID_TIMER");
            BST_OS_PalTimerCallBack();
            break;

        case ACPU_PID_BASTET_COMM:
            BST_DBG_LOG("BST_SYS_MsgProcEntry: ACPU_PID_BASTET_COMM");
            BST_Pal_DrvAcomRecv( ( BST_UINT32 ) BST_OS_SIZEOF( BST_ACOM_MSG_STRU ),
                                 ( BST_UINT8 *) pstMsg );
            break;

        case UEPS_PID_CDS:
            BST_DBG_LOG("BST_SYS_MsgProcEntry: UEPS_PID_CDS");
            DIAG_TraceReport(pstMsg);
            BST_PAL_NetMsgEntry( pstMsg );
            break;

        case I0_WUEPS_PID_MMA:
            DIAG_TraceReport(pstMsg);
            BST_MSG_ProcMmaRecv(pstMsg,BST_MODEM_ID_1);
            break;

#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
        case I1_WUEPS_PID_MMA:
            DIAG_TraceReport(pstMsg);
            BST_MSG_ProcMmaRecv(pstMsg,BST_MODEM_ID_2);
            break;

#if ( 3 == MULTI_MODEM_NUMBER )
        case I2_WUEPS_PID_MMA:
            DIAG_TraceReport(pstMsg);
            BST_MSG_ProcMmaRecv(pstMsg,BST_MODEM_ID_3);
            break;
#endif
#endif

        case WUEPS_PID_WRR:
            DIAG_TraceReport(pstMsg);
            BST_MSG_ProcWrrcRecv(pstMsg);
            break;
        case TPS_PID_RRC:
            DIAG_TraceReport(pstMsg);
            BST_MSG_ProcTrrcRecv(pstMsg);
            break;
        case PS_PID_ERRC:
            DIAG_TraceReport(pstMsg);
            BST_MSG_ProcLrrcRecv(pstMsg);
            break;
        case WUEPS_PID_RLC:
            DIAG_TraceReport(pstMsg);
            BST_MSG_ProcWRlcRecv(pstMsg);
            break;
        case I0_UEPS_PID_SN:
            DIAG_TraceReport(pstMsg);
            BST_MSG_ProcGRlcRecv(pstMsg);
            break;

#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
        case I1_UEPS_PID_SN:
            DIAG_TraceReport(pstMsg);
            BST_MSG_ProcGRlcRecv(pstMsg);
            break;

#if ( 3 == MULTI_MODEM_NUMBER )
        case I2_UEPS_PID_SN:
            DIAG_TraceReport(pstMsg);
            BST_MSG_ProcGRlcRecv(pstMsg);
            break;
#endif
#endif

        default:
            break;
    }
}


VOS_VOID BST_SYS_EvtProcEntry(VOS_UINT32 ulEvent)
{
    /*��������CDS IP���յ�����*/
    if (ulEvent & BST_CDS_EVENT_RCV_DL_PROC)
    {
        BST_PAL_NetDLEvtProc();
    }
    return;
}
BST_VOID BST_SYS_ApiSndEvtToBastet(BST_UINT32 ulEvent)
{
    if ( BST_TRUE == g_ulBstTaskReadyFlag )
    {
        (VOS_VOID)VOS_EventWrite(g_ulBastetTaskId, ulEvent);
    }
    return;
}


VOS_VOID BST_FidTask ( VOS_UINT32 Para1, VOS_UINT32 Para2,
                       VOS_UINT32 Para3, VOS_UINT32 Para4 )
{
    MsgBlock       *pMsg                = VOS_NULL_PTR;
    VOS_UINT32      ulEvent             = 0;
    VOS_UINT32      ulTaskID            = 0;
    VOS_UINT32      ulEventMask         = 0;
    VOS_UINT32      ulExpectEvent       = 0;

    ulTaskID                = VOS_GetCurrentTaskID();

    if ( PS_NULL_UINT32 == ulTaskID )
    {
        BST_RLS_LOG ( "BST_FidTask: This Task Id is Error" );
        return;
    }

    if ( VOS_OK != VOS_CreateEvent(ulTaskID) )
    {
        BST_RLS_LOG ( "BST_FidTask:, Create Event Fail");
        return;
    }

    ulExpectEvent           = VOS_MSG_SYNC_EVENT|BST_CDS_EVENT_RCV_DL_PROC;
    ulEventMask             = (VOS_EVENT_ANY | VOS_EVENT_WAIT);
    g_ulBastetTaskId        = VOS_GetCurrentTaskID();
    g_ulBstTaskReadyFlag    = BST_TRUE;

    for (;;)
    {
        if ( VOS_OK != VOS_EventRead(ulExpectEvent,ulEventMask,0,&ulEvent) )
        {
            BST_RLS_LOG ( "BST_FidTask: BASTET Read Event Error" );
            continue;
        }
        /*�¼�����*/
        if (VOS_MSG_SYNC_EVENT != ulEvent)
        {
            BST_SYS_EvtProcEntry(ulEvent);
            continue;
        }

        pMsg                = (MsgBlock *)VOS_GetMsg(ulTaskID);
        if ( VOS_NULL_PTR != pMsg )
        {
            switch ( TTF_GET_MSG_RECV_PID( pMsg ) )
            {
                case UEPS_PID_BASTET:
                    BST_SYS_MsgProcEntry( pMsg );
                    break;

                default:
                    BST_RLS_LOG1 ( "BST_FidTask: Recv Unkown Message %d\r\n", TTF_GET_MSG_NAME(pMsg) );
                    break;
            }
            PS_FREE_MSG ( UEPS_PID_BASTET, pMsg );
        }

    }
}
VOS_UINT32 BST_PidInit(enum VOS_INIT_PHASE_DEFINE enPhase)
{

    switch (enPhase)
    {
        case   VOS_IP_LOAD_CONFIG:
            BST_SYS_InitBastetNvFlag();
            BST_SYS_InitPlatform();
            break;
        case   VOS_IP_FARMALLOC:
        case   VOS_IP_INITIAL:
        case   VOS_IP_ENROLLMENT:
        case   VOS_IP_LOAD_DATA:
        case   VOS_IP_FETCH_DATA:
        case   VOS_IP_STARTUP:
        case   VOS_IP_RIVAL:
        case   VOS_IP_KICKOFF:
        case   VOS_IP_STANDBY:
        case   VOS_IP_BROADCAST_STATE:
        case   VOS_IP_RESTART:
        case   VOS_IP_BUTT:
            break;
        default:
            break;
    }

    return VOS_OK;
}



VOS_UINT32 BST_FidInit(enum VOS_INIT_PHASE_DEFINE enPhase)
{
    VOS_UINT32   ulResult = PS_FAIL;

    switch (enPhase)
    {
        case   VOS_IP_LOAD_CONFIG:
            ulResult = VOS_RegisterPIDInfo(UEPS_PID_BASTET,
                                BST_PidInit,
                                BST_SYS_MsgProcEntry);
            if (PS_SUCC != ulResult)
            {
                return (VOS_UINT32)PS_FAIL;
            }

            ulResult = VOS_RegisterMsgTaskEntry(UEPS_FID_BASTET, (VOS_VOIDFUNCPTR)BST_FidTask);
            if (PS_SUCC != ulResult)
            {
                vos_printf("UEPS_FID_BASTET Reg msg routine FAIL!,ulRslt\n", ulResult);
                return (VOS_UINT32)PS_FAIL;
            }


            ulResult = VOS_RegisterMsgTaskPrio(UEPS_FID_BASTET, VOS_PRIORITY_P3);

            if( PS_SUCC != ulResult )
            {
                vos_printf("Error: UEPS_FID_BASTET VOS_RegisterMsgTaskPrio failed!");
                return (VOS_UINT32)PS_FAIL;
            }
            break;
        case   VOS_IP_FARMALLOC:
        case   VOS_IP_INITIAL:
        case   VOS_IP_ENROLLMENT:
        case   VOS_IP_LOAD_DATA:
        case   VOS_IP_FETCH_DATA:
        case   VOS_IP_STARTUP:
        case   VOS_IP_RIVAL:
        case   VOS_IP_KICKOFF:
        case   VOS_IP_STANDBY:
        case   VOS_IP_BROADCAST_STATE:
        case   VOS_IP_RESTART:
        case   VOS_IP_BUTT:
            break;
        default:
            break;
    }

    return VOS_OK;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


