

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "BST_CORE_Schd.h"
#include "BST_OS_Thread.h"
#include "BST_DBG_MemLeak.h"
#include "BST_SRV_TaskMng.h"
#include "BST_SRV_Event.h"
#include "BST_DRV_LinkSta.h"
#include "BST_DSPP_Define.h"
#include "BST_SRV_HbDetector.h"

/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_BST_CORE_SCHD_CPP
/*lint +e767*/
/*****************************************************************************
  2 ��������
*****************************************************************************/

/******************************************************************************
   4 ˽�ж���
******************************************************************************/

/******************************************************************************
   5 ȫ�ֱ�������
******************************************************************************/
LIST        g_stPTaskList;
BST_UINT8   g_aucCycErrCnt[ BST_SRV_DTC_MAX_LEN ];
/******************************************************************************
   6 ����ʵ��
******************************************************************************/


/*lint -e429*/
BST_VOID BST_CTaskSchdler::Attach ( BST_CORE_CPTask *pC_PTask )
{
    BST_CORE_PTASK_NODE_STRU   *pstPtaskNode;
    BST_UINT32                  ulSysTickMs;

    if ( !BST_OS_IsTimerValid (m_ulTimerId) )
    {
        BST_RLS_LOG1( "BST_CTaskSchdler::Attach m_ulTimerId=%u is invalid",
                      m_ulTimerId );
        return;
    }
    if ( BST_NULL_PTR == pC_PTask )
    {
        BST_RLS_LOG( "BST_CTaskSchdler::Attach pC_PTask=NULL" );
        return;
    }
    for ( pstPtaskNode = (BST_CORE_PTASK_NODE_STRU *)lstFirst( &g_stPTaskList );
          pstPtaskNode!= BST_NULL_PTR;
          pstPtaskNode = (BST_CORE_PTASK_NODE_STRU *)lstNext((NODE *)pstPtaskNode) )
    {
        if( pstPtaskNode->pcTask == pC_PTask )
        {
            return;
        }
    }
    /*
     * ��������ڵ���Դ�����ڴ洢����
     */
    pstPtaskNode                = ( BST_CORE_PTASK_NODE_STRU *)BST_OS_MALLOC
                                  ( BST_OS_SIZEOF( BST_CORE_PTASK_NODE_STRU ) );
    if( BST_NULL_PTR == pstPtaskNode )
    {
        BST_RLS_LOG( "BST_CTaskSchdler::Attach pstPtaskNode=NULL" );
        return;
    }
    /*
     * ��ʼ���������ݣ�����������б�
     */
    pC_PTask->m_ulSuspCounter   = 0;
    pstPtaskNode->pcTask        = pC_PTask;
    pstPtaskNode->ulLastSendTime= 0;
    pstPtaskNode->enSendState   = BST_APP_SEND_STATE_FIRST;   
    pstPtaskNode->enLastErrType = BST_CORE_SCHD_ACK_SUC; 
    pstPtaskNode->usSelfCyc     = BST_CORE_INVALID_CYC;     

    lstAdd( &g_stPTaskList, (NODE *)pstPtaskNode );
    /*
     * �����ʱϵͳTICK��ʱ�Ѿ��رգ���PS�����״̬��������ô��Ҫ�ٴ�������ʱ
     */
    if( BST_TRUE == BST_OS_TimerIsStop( m_ulTimerId ) )
    {
        m_usSysTickCnt          = 0;
        ulSysTickMs             = BST_SRV_CHbDetector::GetInstance()->GetCurrentTick();
        BST_OS_TimerStart ( m_ulTimerId, ulSysTickMs );
        BST_DBG_LOG1( "BST_CTaskSchdler::Attach Start Scheduler Timer:%u",
                      ulSysTickMs );
    }
}
/*lint +e429*/

/*lint -e438*/
BST_VOID BST_CTaskSchdler::Detach ( BST_CORE_CPTask *pC_PTask )
{
    BST_CORE_PTASK_NODE_STRU   *pstPtaskNode;

    if ( !BST_OS_IsTimerValid (m_ulTimerId) )
    {
        BST_RLS_LOG1( "BST_CTaskSchdler::Detach m_ulTimerId=%u is invalid",
                      m_ulTimerId );
        return;
    }
    if ( BST_NULL_PTR == pC_PTask )
    {
        BST_RLS_LOG( "BST_CTaskSchdler::Detach pC_PTask=NULL" );
        return;
    }
    /*
     * �����б��ҵ�pctask��������񣬴�����ɾ�����ͷ���Դ
     */
    for ( pstPtaskNode = (BST_CORE_PTASK_NODE_STRU *)lstFirst( &g_stPTaskList );
          pstPtaskNode!= BST_NULL_PTR;
          pstPtaskNode = (BST_CORE_PTASK_NODE_STRU *)lstNext((NODE *)pstPtaskNode) )
    {
        if( pstPtaskNode->pcTask != pC_PTask )
        {
            continue;
        }
        lstDelete( &g_stPTaskList, (NODE *)pstPtaskNode );
        if( BST_SRV_CHbDetector::GetInstance()->IsTask( pstPtaskNode->pcTask ) )
        {
            BST_SRV_CHbDetector::GetInstance()->ClrTask();
        }
        BST_OS_FREE( pstPtaskNode );
        break;
    }
    /*
     * ע���������Ϊ�б�Ϊ�գ���ֱ�ӹرն�ʱ�����������κε���
     */
    if ( 0 == lstCount( &g_stPTaskList ) )
    {
        BST_DBG_LOG( "BST_CTaskSchdler::Detach Stop Scheduler Timer" );
        BST_OS_TimerStop ( m_ulTimerId );
        BST_OS_TimerStop ( m_ulDelayTimerId );
    }
}
/*lint +e438*/

BST_VOID BST_CTaskSchdler::Suspend ( BST_VOID )
{
    BST_CORE_PTASK_NODE_STRU   *pstPtaskNode;

    if ( 0 == lstCount( &g_stPTaskList ) )
    {
        BST_RLS_LOG( "BST_CTaskSchdler::Suspend g_stPTaskList count=0" );
        return;
    }
    /*
     * ����������ҵ�������������й���
     */
    for ( pstPtaskNode = (BST_CORE_PTASK_NODE_STRU *)lstFirst( &g_stPTaskList );
          pstPtaskNode!= BST_NULL_PTR;
          pstPtaskNode = (BST_CORE_PTASK_NODE_STRU *)lstNext((NODE *)pstPtaskNode) )
    {
        if ( BST_NULL_PTR == pstPtaskNode->pcTask )
        {
            continue;
        }
        if ( BST_TASK_STATE_START == pstPtaskNode->pcTask->GetState () )
        {
            pstPtaskNode->pcTask->Suspend();
        }
    }
}


BST_CTaskSchdler* BST_CTaskSchdler::GetInstance ( BST_VOID )
{
    static BST_CTaskSchdler    *pTaskScheduler = BST_NULL_PTR;

    if ( BST_NULL_PTR == pTaskScheduler )
    {
        pTaskScheduler          = new BST_CTaskSchdler;
    }
    return pTaskScheduler;
}


BST_CTaskSchdler::BST_CTaskSchdler ( BST_VOID ) 
    : BST_SRV_CAsRcver( BST_SRV_GetSysMsgHandle() )
{
    BST_UINT16              usMaxCnt;
    BST_DRV_STRU           *pstLsDriver;

    m_ulTimerId             = BST_OS_TimerCreateCpp ( this,
                                                      BST_NULL_PTR,
                                                      BST_SRV_GetSysMsgHandle() );
    m_ulDelayTimerId        = BST_OS_TimerCreateCpp ( this,
                                                      BST_NULL_PTR,
                                                      BST_SRV_GetSysMsgHandle() );
    m_usSysTickCnt          = 0;
    
    m_usSysTickMax          = 1;
    usMaxCnt                = BST_SRV_DTC_MAX_LEN;
    /**
     * ������ܳ������ڵ���󹫱�������Ϊtick����ѭ��������
     */
    for(;;)
    {
        m_usSysTickMax     *= usMaxCnt;
        usMaxCnt--;
        if( usMaxCnt <= 1)
        {
            break;
        }
    }
    for( usMaxCnt = 0; usMaxCnt < BST_SRV_DTC_MAX_LEN; usMaxCnt++ )
    {
        g_aucCycErrCnt[usMaxCnt] = 0;
    }
    m_usSendingCnt          = 0;
    m_usCalledBitRecord     = 0;

    pstLsDriver             = BST_DRV_LsGetDvcHandle();
    if( BST_NULL_PTR != pstLsDriver->pfRead )
    {
        pstLsDriver->pfRead( BST_OS_SIZEOF(m_enLinkStaRank), (BST_UINT8 *)&m_enLinkStaRank );
    }
    else
    {
        m_enLinkStaRank     = BST_AS_NET_RANK_MIDDLE;
    }

    BST_DBG_LOG1("BST_CTaskSchdler:%d",m_enLinkStaRank);

    lstInit( &g_stPTaskList );
    RegAsNotice( BST_AS_EVT_L3_RRC_STATE );
    RegAsNotice( BST_AS_EVT_L3_NET_RANK );
}


BST_CTaskSchdler::~BST_CTaskSchdler ( BST_VOID )
{
    if ( BST_OS_IsTimerValid( m_ulTimerId ) )
    {
        BST_OS_TimerRemove( m_ulTimerId );
        m_ulTimerId                     = BST_OS_INVALID_TIMER_ID;
    }
    if ( BST_OS_IsTimerValid( m_ulDelayTimerId ) )
    {
        BST_OS_TimerRemove( m_ulDelayTimerId );
        m_ulDelayTimerId                = BST_OS_INVALID_TIMER_ID;
    }
}


BST_VOID BST_CTaskSchdler::TimerExpired(
    BST_OS_TIMERID_T    ulId,
    BST_VOID           *pvPara)
{
    BST_CORE_PTASK_NODE_STRU   *pstPtaskNode;
    BST_CORE_PTASK_NODE_STRU   *pstPtaskNodeNext;
    BST_UINT32                  ulSysTickMs;

    if ( !BST_OS_IsTimerValid (m_ulTimerId) )
    {
        BST_RLS_LOG1( "BST_CTaskSchdler::TimerExpired m_ulTimerId=%u is invalid",
                      m_ulTimerId );
        return;
    }
    if ( !BST_OS_IsTimerValid (m_ulDelayTimerId) )
    {
        BST_RLS_LOG1( "BST_CTaskSchdler::TimerExpired m_ulDelayTimerId=%u is invalid",
                      m_ulTimerId );
        return;
    }

    if ( ulId == m_ulDelayTimerId )
    {
        BST_RLS_LOG1( "BST_CTaskSchdler::delay TimerExpired m_enLinkStaRank:%d",m_enLinkStaRank );
        if( BST_AS_NET_RANK_INVALID != m_enLinkStaRank )
        {
            ScheduleBlockedTask();
        }
        return;
    }

    if ( ulId != m_ulTimerId )
    {
        BST_RLS_LOG2( "BST_CTaskSchdler::TimerExpired ulId=%u,m_ulTimerId=%u",
                      ulId, m_ulTimerId );
        return;
    }
    /*
     * ����ϵͳTICKֵ
     */
    m_usSysTickCnt++;
    m_usCalledBitRecord         = 0;
    m_usSendingCnt              = 0;

    BST_DBG_LOG1 ( "BST_CTaskSchdler::TimerExpired Scheduler TimeOut, Tick=%d ",
                   m_usSysTickCnt );

    if( m_usSysTickCnt >= m_usSysTickMax )
    {
        /*
         * �������ֵ�Ժ󻷻أ�����������
         */
        m_usSysTickCnt         = 0;
    }

    /*
     * ���������б���ȡ���񲢽�����Ӧ����
     */
    for ( pstPtaskNode = ( BST_CORE_PTASK_NODE_STRU *)lstFirst( &g_stPTaskList );
          pstPtaskNode!= BST_NULL_PTR;
          pstPtaskNode = pstPtaskNodeNext )
    {
        pstPtaskNodeNext    = ( BST_CORE_PTASK_NODE_STRU *)
                              lstNext((NODE *)pstPtaskNode);
        if ( BST_NULL_PTR == pstPtaskNode->pcTask )
        {
            continue;
        }
        /*
         * �������Ϊ�գ������״̬���е���
         */
        ScheduleTask( pstPtaskNode );
    }
    /*
     * �ٴ�����ϵͳTICK��ʱ��
     */
    ulSysTickMs             = BST_SRV_CHbDetector::GetInstance()->GetCurrentTick();
    BST_OS_TimerStart ( m_ulTimerId, ulSysTickMs );
}


BST_CORE_CPTask* BST_CTaskSchdler::GetPtaskIns( BST_UINT16 usProcId, BST_UINT16 usTaskId )
{
    BST_CORE_CPTask            *pC_PTask;
    BST_CORE_PTASK_NODE_STRU   *pstPtaskNode;

    if ( 0 == lstCount( &g_stPTaskList ) )
    {
        return BST_NULL_PTR;
    }
    pC_PTask                    = BST_NULL_PTR;
    /*
     * ����������ҵ������������
     */
    for ( pstPtaskNode = (BST_CORE_PTASK_NODE_STRU *)lstFirst( &g_stPTaskList );
          pstPtaskNode!= BST_NULL_PTR;
          pstPtaskNode = (BST_CORE_PTASK_NODE_STRU *)lstNext((NODE *)pstPtaskNode) )
    {
        if ( BST_NULL_PTR == pstPtaskNode->pcTask )
        {
            continue;
        }

        if( ( pstPtaskNode->pcTask->m_usProcId == usProcId )
          &&( pstPtaskNode->pcTask->m_usTaskId == usTaskId ) )
        {
            pC_PTask            = pstPtaskNode->pcTask;
            break;
        }
    }
    return pC_PTask;
}


BST_VOID    BST_CTaskSchdler::ScheduleTask( BST_CORE_PTASK_NODE_STRU *pTaskItem )
{
    BST_SRV_CTaskMng                   *pcTaskManager;
    BST_CORE_CPTask                    *pTask;
    BST_TASK_STATE_ENUM_UINT8           enTaskState;
    BST_UINT16                          usRealCyc;

    pcTaskManager                       = BST_SRV_CTaskMng::GetInstance ();
    BST_ASSERT_NULL( pcTaskManager );

    /*
     * ��ڼ��
     */
    BST_ASSERT_NULL( pTaskItem );
    pTask                               = pTaskItem->pcTask;

    BST_ASSERT_NULL( pTask );

    if( BST_CORE_IsRuningDetector( pTask ) )
    {
        BST_RLS_LOG2( "BST_CTaskSchdler::ScheduleTask ProcId=%u ,TaskId=%u is Runing Detector",
                      pTask->m_usProcId, pTask->m_usTaskId );
        return;
    }
    /*
     * ����ϴ�ִ�е��¼���δ��ɣ����β�����
     */
    if ( BST_TRUE == pTask->IsBusy () )
    {
        BST_RLS_LOG( "BST_CTaskSchdler::ScheduleTask pTask Is Busy" );
        return;
    }
    usRealCyc                           = GetTaskCycle( pTaskItem );
    if( BST_CORE_INVALID_CYC == usRealCyc )
    {
        return;
    }
    /*
     * ���ϵͳTICK���Ա���������������˵����������������ʱ��
     */
    if ( 0 != m_usSysTickCnt % usRealCyc )
    {
        return;
    }

    enTaskState                         = pTask->GetState ();
    switch ( enTaskState )
    {
        /*
         * �������ֹͣ��ֻ����suspendCounterΪ0�������κ�����
         */
        case BST_TASK_STATE_STOPED:
            pTask->m_ulSuspCounter      = 0;
            break;

        /*
         * ���������𳬹�����޶ȣ�������ɾ��֮
         */
        case BST_TASK_STATE_SUSPEND:
            pTask->m_ulSuspCounter ++;
            if ( pTask->m_ulSuspCounter >= BST_TASK_MAX_SYSPEND )
            {
                pcTaskManager->Remove ( pTask->m_usProcId, pTask->m_usTaskId );
            }
            break;
        /*
         * �����Ϊ��������̬�������ִ��
         */
        case BST_TASK_STATE_START:

            BST_DBG_LOG1( "BST_CTaskSchdler::ScheduleTask m_enLinkStaRank:%d",m_enLinkStaRank );
            if( BST_AS_NET_RANK_INVALID == m_enLinkStaRank )
            {
                pTaskItem->enSendState  = BST_APP_SEND_STATE_BLOCK;
                break;
            }

            if( BST_AS_NET_RANK_MIDDLE > m_enLinkStaRank )
            {
                pTaskItem->enSendState  = BST_APP_SEND_STATE_BLOCK;
                if( BST_TRUE == BST_OS_TimerIsStop( m_ulDelayTimerId ) )
                {
                    BST_DBG_LOG( "BST_CTaskSchdler::Task start delay timer" );
                    BST_OS_TimerStart ( m_ulDelayTimerId, BST_TASK_DELAY_TIME_MS );
                }
                break;
            }
            BST_SRV_ApiSendPTaskEvent( pTask, BST_SRV_S2T_EXE_COMAND, 0 );
            pTaskItem->ulLastSendTime   = BST_OS_TimerNowMs();

            if( BST_APP_SEND_STATE_NORM == pTaskItem->enSendState )
            {
                BST_CORE_MARK_CYC_BIT( m_usCalledBitRecord, usRealCyc );
                m_usSendingCnt++;
            }
            break;

        default:
            break;
    }
}


BST_VOID BST_CTaskSchdler::LinkStateChgProc( BST_AS_NET_RANK_ENUM_UINT32 enNetRank )
{
    BST_DBG_LOG2( "BST_CTaskSchdler::LinkStateChgProc RANK_Old=u%, RANK_NEW=u%",
                  m_enLinkStaRank,
                  enNetRank );
    if ( m_enLinkStaRank == enNetRank )
    {
        return;
    }
    m_enLinkStaRank          = enNetRank;

    if ( m_enLinkStaRank <= BST_AS_NET_RANK_POOR )
    {
        BST_SRV_CHbDetector::GetInstance()->onBlock();
    }
    else
    {
        BST_SRV_CHbDetector::GetInstance()->onUnBlock();
        /*�ڵ�������block����֮ǰ����ֹͣ������ʱ�Ķ�ʱ��*/
        if( BST_FALSE == BST_OS_TimerIsStop( m_ulDelayTimerId ) )
        {
            BST_DBG_LOG( "BST_CTaskSchdler::Task exec, stop delay time" );
            BST_OS_TimerStop ( m_ulDelayTimerId );
        }
        
        /*���������б���ȡ���񲢽�����Ӧ���� */
        ScheduleBlockedTask();
    }

}


BST_VOID BST_CTaskSchdler::AsEventCallback(
    BST_AS_EVT_ENUM_UINT32    enEvent,
    BST_UINT32                ulLength,
    BST_VOID                 *pvData )
{
    BST_UINT32          ulPara;
    BST_UINT32          ulOldRrcState;

    switch( enEvent )
    {
        /*
         * ������RRC״̬��Ϣ����RRC���ӳɹ�ʱ���鿴��ǰʣ��ʱ���Ƿ񿿽�
         */
        case BST_AS_EVT_L3_RRC_STATE:
            if ( BST_OS_SIZEOF(ulPara) != ulLength )
            {
                break;
            }
            if ( BST_NULL_PTR == pvData )
            {
                break;
            }
            ulOldRrcState   = m_ulRrcState;
            BST_OS_MEMCPY( &m_ulRrcState, pvData, ulLength );

            if((BST_TRUE == BST_AS_IsRrcConnected(m_ulRrcState))
                && (BST_FALSE == BST_AS_IsRrcConnected(ulOldRrcState)))
            {
                ulPara      = BST_OS_TimerIsStop( m_ulTimerId );
                if ( BST_TRUE == ulPara )
                {
                    break;
                }
                ulPara      = BST_OS_TimeGetRemain( m_ulTimerId );
                if ( 0 == ulPara )
                {
                    break;
                }
                ulPara      = NearRrcTrig ( ulPara );
                BST_OS_TimerStart( m_ulTimerId, ulPara );
            }
            break;
        case BST_AS_EVT_L3_NET_RANK:
            if ( BST_OS_SIZEOF(BST_AS_NET_RANK_ENUM_UINT32) != ulLength )
            {
                BST_RLS_LOG1("BST_CTaskSchdler::AsEventCallback Error Net Rank Length = %u:", ulLength );
                break;
            }
            LinkStateChgProc( *( (BST_AS_NET_RANK_ENUM_UINT32 *)pvData ) );
            break;
        default:
            break;
    }
}


BST_UINT32 BST_CTaskSchdler::NearRrcTrig ( BST_UINT32 const ulSysTimerRemainMs )
{
    BST_CORE_PTASK_NODE_STRU   *pstPtaskNode;
    BST_UINT32                  ulNextSysTick;
    BST_UINT32                  ulNextLongCycle;
    BST_UINT16                  usRealCyc;

    ulNextLongCycle             = 0;
    ulNextSysTick               = m_usSysTickCnt;
    /*
     * ���������б��ҳ�������Ч����
     */
    for( pstPtaskNode = (BST_CORE_PTASK_NODE_STRU *)lstFirst( &g_stPTaskList );
         pstPtaskNode!= BST_NULL_PTR;
         pstPtaskNode = (BST_CORE_PTASK_NODE_STRU *)lstNext((NODE *)pstPtaskNode) )
    {
        if( BST_NULL_PTR == pstPtaskNode->pcTask )
        {
            continue;
        }
        if( 0 == pstPtaskNode->pcTask->m_ulCycle )
        {
            continue;
        }
        if( BST_TRUE == pstPtaskNode->pcTask->IsBusy () )
        {
            continue;
        }
        if( BST_TASK_STATE_START != pstPtaskNode->pcTask->GetState () )
        {
            continue;
        }
        if( BST_CORE_IsRuningDetector( pstPtaskNode->pcTask ) )
        {
            continue;
        }
        /*
         * �鿴�Ƿ�������������Tick������������ڵ���
         */
        usRealCyc                   = GetTaskCycle( pstPtaskNode );
        if( BST_CORE_INVALID_CYC == usRealCyc )
        {
            continue;
        }
        if( 0 == ( ulNextSysTick % usRealCyc ) )
        {
            if( usRealCyc > ulNextLongCycle )
            {
                ulNextLongCycle = usRealCyc;
            }
        }
    }
    /*
     * ��ȡ��ǰϵͳ���ڣ���ȡ���������ʣ��ʱ����ڸ�ֵ����˵���㹻����
     */
    ulNextLongCycle             = BST_CORE_GetCycleToMs( ulNextLongCycle );
    if( BST_TASK_IsNearEnough( ulSysTimerRemainMs, ulNextLongCycle ) )
    {
        BST_RLS_LOG("BST_CTaskSchdler::NearRrcTrig Closing To RRC Enough, Periodic Runing after 200Ms");
        return BST_TASK_RRC_SEND_TIMER;
    }
    else
    {
        return ulSysTimerRemainMs;
    }
}


BST_VOID BST_CTaskSchdler::AckSendResult(
    BST_CORE_CPTask *pcPTask, BST_UINT16 ucResult )
{
    BST_CORE_PTASK_NODE_STRU   *pstPtaskNode;

    pstPtaskNode                = GetTaskItem( pcPTask );
    if ( BST_NULL_PTR == pstPtaskNode )
    {
        return;
    }
    /**
     * ��̽����Ӧ�ã����ϴη��������������͵ģ����ڴ�--
     */
    if( ( BST_APP_SEND_STATE_NORM == pstPtaskNode->enSendState )
     && ( !BST_CORE_IsRuningDetector( pcPTask ) ) )
    {
        m_usSendingCnt--;
    }

    if( BST_CORE_SCHD_ACK_SUC == ucResult )
    {
        ProcAckSuc( pstPtaskNode );
    }
    else
    {
        ProcAckErr( pstPtaskNode );
    }

    if( 0 == m_usSendingCnt )
    {
        ProcFinish();
    }

}


BST_VOID BST_CTaskSchdler::ProcAckSuc( BST_CORE_PTASK_NODE_STRU *pstTaskItem )
{
    BST_UINT16                  usUsingCycle;

    /*
     * �״��������ͣ����ܲ���һ���������ڣ������κδ�����λ�������ڷ���״̬
     */
    if( BST_APP_SEND_STATE_FIRST == pstTaskItem->enSendState )
    {
        pstTaskItem->enSendState       = BST_APP_SEND_STATE_NORM;
        return;
    }
    if( BST_CORE_IsRuningDetector( pstTaskItem->pcTask ) )
    {
        BST_SRV_CHbDetector::GetInstance()->AckSendResult( BST_CORE_SCHD_ACK_SUC );
        return;
    }
    /*
     * �������͵������������ζ����������ռ�¼
     */
    if( BST_APP_SEND_STATE_BLOCK == pstTaskItem->enSendState )
    {
        pstTaskItem->enSendState       = BST_APP_SEND_STATE_NORM;
        return;
    }
    pstTaskItem->enLastErrType          = BST_CORE_SCHD_ACK_SUC;
    usUsingCycle                        = GetTaskCycle( pstTaskItem );

    if( ( usUsingCycle <= BST_SRV_DTC_MAX_LEN )&&( usUsingCycle != BST_CORE_INVALID_CYC ) )
    {        
        g_aucCycErrCnt[ usUsingCycle ]  = 0;
        BST_CORE_CLR_CYC_BIT( m_usCalledBitRecord, usUsingCycle );
    }
}


BST_VOID BST_CTaskSchdler::ProcAckErr( BST_CORE_PTASK_NODE_STRU *pstTaskItem )
{
    pstTaskItem->ulLastSendTime    = 0;
    /*
     * �������͵������������ζ����������ռ�¼?
     */
    if( BST_APP_SEND_STATE_BLOCK == pstTaskItem->enSendState )
    {
        pstTaskItem->enSendState       = BST_APP_SEND_STATE_NORM;
        return;
    }
    if( BST_CORE_IsRuningDetector( pstTaskItem->pcTask) )
    {
        BST_SRV_CHbDetector::GetInstance()->AckSendResult( BST_CORE_SCHD_ACK_ERR );
        return;
    }
    /*
     * ����ϴ�������û�гɹ�����ô��Ҫע�ؿ���
     */
    if( pstTaskItem->enLastErrType != BST_CORE_SCHD_ACK_SUC )
    {
        /*
         * ����ϴβ��õ���ϵͳ����û�ɹ�����ô�����Ҫ����һ������
         */
        if( BST_CORE_INVALID_CYC == pstTaskItem->usSelfCyc )
        {
            pstTaskItem->usSelfCyc  = BST_SRV_CHbDetector::GetInstance()
                                    ->GetConfCyc( pstTaskItem->pcTask->m_ulCycle );
        }
        if( pstTaskItem->usSelfCyc > 1 )
        {
            pstTaskItem->usSelfCyc--;
        }
    }
    pstTaskItem->enLastErrType = BST_CORE_SCHD_ACK_ERR;
}


BST_VOID BST_CTaskSchdler::ProcFinish( BST_VOID )
{
    BST_UINT16                      usCounter;
    BST_CORE_PTASK_NODE_STRU       *pstPtaskNode;
    
    /*
     * ȫ�������������۳ɹ�����ʧ�ܣ�����Ӧ��ɣ�����ĳЩ���ڵ�����û�гɹ�
     */
    for( ;; )
    {
        if( 0 == m_usCalledBitRecord )
        {
            break;
        }
        usCounter                   = GetErrorCycle( m_usCalledBitRecord );
        BST_CORE_CLR_CYC_BIT( m_usCalledBitRecord, usCounter );
        if( ( usCounter <= BST_SRV_DTC_MAX_LEN )&&( usCounter != BST_CORE_INVALID_CYC ) )
        {
            g_aucCycErrCnt[usCounter]++;
            /*
             * ������ĳ�����ڵ�ȫ�������Ѿ���������ʧ����, ˵��Ŀǰ������ڴ������⣬��Ҫ����̽��
             */
            if( g_aucCycErrCnt[usCounter] >= BST_CORE_MAX_CYC_ERRNO )
            {
                m_usCalledBitRecord = 0;
                for( usCounter = 0; usCounter < BST_SRV_DTC_MAX_LEN; usCounter++ )
                {
                    g_aucCycErrCnt[usCounter]   = 0;
                }
                /*
                 * ����������������������̽����
                 */
                for ( pstPtaskNode = (BST_CORE_PTASK_NODE_STRU *)lstFirst( &g_stPTaskList );
                      pstPtaskNode!= BST_NULL_PTR;
                      pstPtaskNode = (BST_CORE_PTASK_NODE_STRU *)lstNext((NODE *)pstPtaskNode) )
                {
                    pstPtaskNode->usSelfCyc     = BST_CORE_INVALID_CYC;
                }
                BST_SRV_CHbDetector::GetInstance()->ReStart();
            }
        }
    }
}


BST_VOID BST_CTaskSchdler::TaskStarted( BST_CORE_CPTask *pcPTask )
{
    BST_CORE_PTASK_NODE_STRU       *pTaskItem;

    if( BST_TRUE == BST_SRV_CHbDetector::GetInstance()->IsTask( pcPTask ) )
    {
        BST_SRV_CHbDetector::GetInstance()->Resume();
    }
    else
    {
        pTaskItem                   = GetTaskItem( pcPTask );
        if( BST_NULL_PTR == pTaskItem )
        {
            return;
        }
        pTaskItem->enSendState      = BST_APP_SEND_STATE_FIRST;
        pTaskItem->ulLastSendTime   = 0;
    }
}

BST_VOID BST_CTaskSchdler::TaskStoped( BST_CORE_CPTask *pcPTask )
{
    if( BST_TRUE == BST_SRV_CHbDetector::GetInstance()->IsTask( pcPTask ) )
    {
        BST_SRV_CHbDetector::GetInstance()->Pause();
    }
}

BST_VOID BST_CTaskSchdler::DefineDetector( BST_CORE_CPTask *pcPTask )
{
    BST_CORE_PTASK_NODE_STRU   *pstPtaskNode;

    pstPtaskNode                = GetTaskItem( pcPTask );
    if ( BST_NULL_PTR == pstPtaskNode )
    {
        BST_DBG_LOG("DefineDetector,pstPtaskNode is null");
        return;
    }
    BST_SRV_CHbDetector::GetInstance()->DefTask( pstPtaskNode );
}


BST_CORE_PTASK_NODE_STRU* BST_CTaskSchdler::GetTaskItem( BST_CORE_CPTask *pcPTask )
{
    BST_CORE_PTASK_NODE_STRU   *pstPtaskNode;
    
    if ( 0 == lstCount( &g_stPTaskList ) )
    {
        return BST_NULL_PTR;
    }
    /*
     * ����������ҵ������������
     */
    for ( pstPtaskNode = (BST_CORE_PTASK_NODE_STRU *)lstFirst( &g_stPTaskList );
          pstPtaskNode!= BST_NULL_PTR;
          pstPtaskNode = (BST_CORE_PTASK_NODE_STRU *)lstNext((NODE *)pstPtaskNode) )
    {
        if ( BST_NULL_PTR == pstPtaskNode->pcTask )
        {
            continue;
        }
        if( pstPtaskNode->pcTask == pcPTask )
        {
            return pstPtaskNode;
        }
    }
    return BST_NULL_PTR;
}


BST_UINT16 BST_CTaskSchdler::GetTaskCycle( BST_CORE_PTASK_NODE_STRU *pstTaskItem )
{
    BST_UINT16              usTaskCycle;

    if( BST_CORE_INVALID_CYC ==  pstTaskItem->pcTask->m_ulCycle )
    {
        return BST_CORE_INVALID_CYC;
    }
    /*
     * ���self������Ч����ô�����������Լ���self����
     */
    if( BST_CORE_INVALID_CYC != pstTaskItem->usSelfCyc )
    {
        return pstTaskItem->usSelfCyc;
    }

    usTaskCycle             = BST_SRV_CHbDetector::GetInstance()
                            ->GetConfCyc( pstTaskItem->pcTask->m_ulCycle );
    return usTaskCycle;
}


BST_VOID BST_CTaskSchdler::onDetFinished( BST_UINT8 ucLongestCyc )
{
    BST_CORE_PTASK_NODE_STRU   *pstPtaskNode;

    if ( 0 == lstCount( &g_stPTaskList ) )
    {
        return;
    }
    /*
     * ����������ҵ������������
     */
    for ( pstPtaskNode = (BST_CORE_PTASK_NODE_STRU *)lstFirst( &g_stPTaskList );
          pstPtaskNode!= BST_NULL_PTR;
          pstPtaskNode = (BST_CORE_PTASK_NODE_STRU *)lstNext((NODE *)pstPtaskNode) )
    {
        BST_DBG_LOG2("onDetFinished,m_ulCycle:%d,ucLongestCyc:%d", 
        pstPtaskNode->pcTask->m_ulCycle,ucLongestCyc);
        if( pstPtaskNode->pcTask->m_ulCycle > ucLongestCyc )
        {
            BST_SRV_ApiSendPTaskEvent( pstPtaskNode->pcTask,
                                       BST_SRV_S2T_CYC_UPDATE,
                                       ucLongestCyc );
        }
    }
}


BST_UINT16 BST_CTaskSchdler::GetErrorCycle( const BST_UINT16 usErrorMsg )
{
    BST_UINT16  usCnt;
    
    for( usCnt=0; usCnt<16; usCnt++ )
    {
        if( ( usErrorMsg & (~(0x01<<usCnt) ) ) != usErrorMsg )
        {
            return usCnt;
        }
    }
    return BST_CORE_NO_ERR_BIT;
}



BST_VOID BST_CTaskSchdler::ScheduleBlockedTask(BST_VOID )
{
    BST_CORE_PTASK_NODE_STRU   *pstPtaskNode;
    BST_CORE_PTASK_NODE_STRU   *pstPtaskNodeNext;
    BST_DBG_LOG( "BST_CTaskSchdler::ScheduleBlockedTask" );

    /*
     * ���������б���ȡ���񲢽�����Ӧ����
     */

    for ( pstPtaskNode = ( BST_CORE_PTASK_NODE_STRU *)lstFirst( &g_stPTaskList );
          pstPtaskNode!= BST_NULL_PTR;
          pstPtaskNode = pstPtaskNodeNext )
    {
        pstPtaskNodeNext    = ( BST_CORE_PTASK_NODE_STRU *)
                              lstNext((NODE *)pstPtaskNode);
        if ( BST_NULL_PTR == pstPtaskNode->pcTask )
        {
            continue;
        }

        if( BST_CORE_IsRuningDetector( pstPtaskNode->pcTask ) )
        {
            BST_DBG_LOG2( "ScheduleBlockedTask:: ProcId=%u ,TaskId=%u is Runing Detector",
                 pstPtaskNode->pcTask->m_usProcId, pstPtaskNode->pcTask->m_usTaskId );
            continue;
        }

        if( BST_APP_SEND_STATE_BLOCK != pstPtaskNode->enSendState )
        {
            BST_DBG_LOG3( "ScheduleBlockedTask:: ProcId=%u ,TaskId=%u enSendState=%u",
                 pstPtaskNode->enSendState, pstPtaskNode->pcTask->m_usProcId, pstPtaskNode->pcTask->m_usTaskId );
            continue;
        }
        if( BST_TRUE == pstPtaskNode->pcTask->IsBusy() )
        {
            BST_DBG_LOG2( "ScheduleBlockedTask:: ProcId=%u ,TaskId=%u is Busy",
                 pstPtaskNode->pcTask->m_usProcId, pstPtaskNode->pcTask->m_usTaskId );
            continue;
        }
        if( BST_TASK_STATE_START != pstPtaskNode->pcTask->GetState() )
        {
            continue;
        }

        BST_DBG_LOG2( "ScheduleBlockedTask:: ProcId=%u ,TaskId=%u",
             pstPtaskNode->pcTask->m_usProcId, pstPtaskNode->pcTask->m_usTaskId ); 

        BST_SRV_ApiSendPTaskEvent( pstPtaskNode->pcTask, BST_SRV_S2T_EXE_COMAND, 0 );
        pstPtaskNode->ulLastSendTime      = BST_OS_TimerNowMs();
    }
}

