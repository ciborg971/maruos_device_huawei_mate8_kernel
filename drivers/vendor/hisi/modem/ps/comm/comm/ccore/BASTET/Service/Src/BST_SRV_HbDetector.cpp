

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "BST_SRV_HbDetector.h"
#include "BST_SRV_TaskMng.h"
#include "BST_SRV_Event.h"

/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_BST_SRV_HB_DETECTOR_CPP
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

/******************************************************************************
   6 ����ʵ��
******************************************************************************/


BST_SRV_CHbDetector* BST_SRV_CHbDetector::GetInstance( BST_VOID )
{
    static  BST_SRV_CHbDetector    *pHbDector = BST_NULL_PTR;

    if ( BST_NULL_PTR == pHbDector )
    {
        pHbDector                       = new BST_SRV_CHbDetector();
    }
    return pHbDector;
}

BST_SRV_CHbDetector::BST_SRV_CHbDetector( BST_VOID )
{
    BST_UINT32                          ulCnt;

    m_ulDetectingOfset                  = 0;
    m_ulCfmSysTick_Ms                   = BST_SRV_DTC_BAS_UNT;
    m_ucDetectingCycle                  = BST_SRV_DTC_INI_PNT;
    m_enDtcState                        = BST_SRV_DET_STATE_INIT;
    pcTaskItem                          = BST_NULL_PTR;
    m_bIsBlocked                        = BST_FALSE;
    m_ulDetectingTmr                    = BST_OS_TimerCreateCpp(
                                          this, BST_NULL_PTR,
                                          BST_SRV_GetSysMsgHandle() );
    for( ulCnt = 0; ulCnt <= BST_SRV_DTC_MAX_LEN; ulCnt++ )
    {
        m_ucCfmTable[ulCnt]             = BST_SRV_DTC_MIN_PNT;
    }
    return;
}

BST_VOID BST_SRV_CHbDetector::Initial( BST_VOID )
{
    BST_UINT32                          ulCnt;

    m_ulDetectingOfset                  = 0;
    m_ulCfmSysTick_Ms                   = BST_SRV_DTC_BAS_UNT;
    m_ucDetectingCycle                  = BST_SRV_DTC_INI_PNT;

    for( ulCnt = 0; ulCnt <= BST_SRV_DTC_MAX_LEN; ulCnt++ )
    {
        m_ucCfmTable[ulCnt]             = BST_SRV_DTC_MIN_PNT;
    }
    /**
     ��ʼ����ɣ�����ǰ��ģʽ�����û��̽��������ôֱ�ӽ����ս�
     */
    if( BST_NULL_PTR == pcTaskItem )
    {
        m_enDtcState                    = BST_SRV_DET_STATE_FINISH;
    }
    else
    {
        m_enDtcState                    = BST_SRV_DET_STATE_FORWARD;
    }
    if( BST_OS_IsTimerValid( m_ulDetectingTmr ) )
    {
        BST_OS_TimerStop( m_ulDetectingTmr );
    }

    BST_DBG_LOG1("BST_SRV_CHbDetector,m_enDtcState:%d",m_enDtcState);
}

BST_ERR_ENUM_UINT8 BST_SRV_CHbDetector::DefTask( BST_CORE_PTASK_NODE_STRU *pDetTask )
{
    BST_ASSERT_NULL_RTN( pDetTask, BST_ERR_INVALID_PTR );
    BST_ASSERT_NULL_RTN( pDetTask->pcTask, BST_ERR_INVALID_PTR );

    if( ( BST_NULL_PTR != pcTaskItem )
      &&( pDetTask != pcTaskItem ) )
    {
        Initial();
    }
    pcTaskItem = pDetTask;
    return BST_NO_ERROR_MSG;
}

BST_ERR_ENUM_UINT8 BST_SRV_CHbDetector::ClrTask( BST_VOID )
{
    BST_DBG_LOG1("HB clr task m_enDtcState:%d",m_enDtcState);
    pcTaskItem  = BST_NULL_PTR;
    if( BST_SRV_DET_STATE_FINISH == m_enDtcState )
    {
        return BST_NO_ERROR_MSG;
    }
    if( BST_OS_IsTimerValid( m_ulDetectingTmr ) )
    {
        BST_OS_TimerStop( m_ulDetectingTmr );
    }
    return BST_NO_ERROR_MSG;
}

BST_VOID BST_SRV_CHbDetector::AckSendResult( BST_UINT16 ucResult )
{
    BST_ASSERT_NULL( pcTaskItem );

    if( BST_CORE_SCHD_ACK_SUC == ucResult )
    {
        ProcHbSuc();
    }
    else
    {
        ProcHbErr();
    }
}


BST_VOID BST_SRV_CHbDetector::ReStart( BST_VOID )
{
    if( BST_NULL_PTR == pcTaskItem )
    {
        Initial();
        return;
    }
    if( BST_NULL_PTR == pcTaskItem->pcTask )
    {
        Initial();
        return;
    }

    /*
     * ���̽���Ѿ���������Ŀǰ�������ϵͳ���ڣ���Ϊ̽��Ҫ���¿�ʼ��Ҫ�����������ڵ������
     */
    if( ( BST_FALSE == IsRuning() )
      &&( m_ucDetectingCycle < BST_SRV_DTC_MAX_LEN ) )
    {
        BST_SRV_ApiSendPTaskEvent( pcTaskItem->pcTask,
                                   BST_SRV_S2T_CYC_UPDATE,
                                   BST_SRV_DTC_MAX_LEN );
    }
    Initial();
    /**
     ��ʼ����ɣ�����ǰ��ģʽ�����û��̽��������ôֱ�ӽ����ս�
     */

    /*
     * ����ϴ�ִ�е��¼���δ��ɣ����β�����
     */
    pcTaskItem->enSendState         = BST_APP_SEND_STATE_FIRST;
    if ( BST_TRUE == pcTaskItem->pcTask->IsBusy () )
    {
        BST_RLS_LOG( "BST_SRV_CHbDetector::ReStart pC_PTask Is Busy" );
        return;
    }
    if( BST_TASK_STATE_START != pcTaskItem->pcTask->GetState () )
    {
        BST_RLS_LOG( "BST_SRV_CHbDetector::ReStart pC_PTask Is not start state" );
        return;
    }
    BST_SRV_ApiSendPTaskEvent( pcTaskItem->pcTask, BST_SRV_S2T_EXE_COMAND, 0 );
    pcTaskItem->ulLastSendTime      = BST_OS_TimerNowMs();
    RunTimer();
}


BST_VOID BST_SRV_CHbDetector::Resume( BST_VOID )
{
    if( BST_NULL_PTR == pcTaskItem )
    {
        return;
    }

    if( BST_NULL_PTR == pcTaskItem->pcTask )
    {
        return;
    }

    pcTaskItem->enSendState             = BST_APP_SEND_STATE_NORM;

    BST_RLS_LOG2( "BST_SRV_CHbDetector::Resume,m_enDtcState:%d,m_ucDetectingCycle:%d",m_enDtcState, m_ucDetectingCycle);

HB_DTCT_RSUM_STATE:
    switch( m_enDtcState )
    {
        case BST_SRV_DET_STATE_INIT:
            Initial();
        case BST_SRV_DET_STATE_FORWARD:
        case BST_SRV_DET_STATE_REVERSE:
            pcTaskItem->ulLastSendTime      = BST_OS_TimerNowMs();
            if( pcTaskItem->ulLastSendTime > BST_SRV_DTC_SYS_DLY )
            {
                pcTaskItem->ulLastSendTime -= BST_SRV_DTC_SYS_DLY;
            }
            else
            {
                pcTaskItem->ulLastSendTime  = 0;
            }
            RunTimer();
        break;

        case BST_SRV_DET_STATE_FINISH:
            if( m_ucDetectingCycle < BST_SRV_DTC_MAX_LEN )
            {
                if( BST_FALSE == BST_OS_TimerIsStop( m_ulDetectingTmr ))
                {
                    BST_RLS_LOG( "BST_SRV_CHbDetector::timer is still running" );
                    return;
                }
                m_enDtcState                = BST_SRV_DET_STATE_FORWARD;
                goto HB_DTCT_RSUM_STATE;
            }
        break; 

        default:
        break;
    }
}

BST_VOID BST_SRV_CHbDetector::Pause( BST_VOID )
{
    BST_DBG_LOG1("HB Pause task m_enDtcState:%d",m_enDtcState);

    if( BST_SRV_DET_STATE_FINISH == m_enDtcState )
    {
        return;
    }
    if( BST_OS_IsTimerValid( m_ulDetectingTmr ) )
    {
        BST_OS_TimerStop( m_ulDetectingTmr );
    }
}

BST_UINT32 BST_SRV_CHbDetector::GetCurrentTick( BST_VOID )
{
    return( m_ulCfmSysTick_Ms - BST_SRV_DTC_GAD_OFS );
}

BST_VOID BST_SRV_CHbDetector::onBlock( BST_VOID )
{
    m_bIsBlocked = BST_TRUE;
}

BST_VOID BST_SRV_CHbDetector::onUnBlock( BST_VOID )
{
    BST_UINT32          ulTimeDiff;
    BST_UINT32          ulTimeNow;
    BST_UINT32          ulLongestTime;

    if( m_bIsBlocked != BST_TRUE )
    {
        return;
    }
    m_bIsBlocked    = BST_FALSE;

    BST_ASSERT_NULL( pcTaskItem );

    if( IsRuning() == BST_FALSE )
    {
        return;
    }

    if( pcTaskItem->enSendState != BST_APP_SEND_STATE_BLOCK )
    {
        return;
    }
    ulTimeNow           = BST_OS_TimerNowMs();

    /**
     *���ʱ�䷢�����أ��ϴ�ʱ���Ѿ��޷�ȷ�ϣ�����Ϊ��ʱ
     */
    if( ulTimeNow < pcTaskItem->ulLastSendTime )
    {
        BST_SRV_ApiSendPTaskEvent( pcTaskItem->pcTask, BST_SRV_S2T_ERR_CLOSED, 0 );
        return;
    }
    else
    {
        ulTimeDiff      = ulTimeNow - pcTaskItem->ulLastSendTime;
    }

    /**
     *���APKҪ����������
     */
    ulLongestTime       = pcTaskItem->pcTask->m_ulCycle * BST_SRV_DTC_BAS_UNT;
    /**
     *�������ʱ���APK�涨�̣���ô��������һ�·�����
     */
    if( ulTimeDiff <= ulLongestTime )
    {
        BST_SRV_ApiSendPTaskEvent( pcTaskItem->pcTask, BST_SRV_S2T_EXE_COMAND, 0 );
        pcTaskItem->ulLastSendTime      = ulTimeNow;
    }
    else
    {
        BST_SRV_ApiSendPTaskEvent( pcTaskItem->pcTask, BST_SRV_S2T_ERR_CLOSED, 0 );
    }
}

BST_BOOL BST_SRV_CHbDetector::IsRuning( BST_VOID )
{
    BST_ASSERT_NULL_RTN( pcTaskItem, BST_FALSE );

    switch( m_enDtcState )
    {
        case BST_SRV_DET_STATE_FORWARD:
        case BST_SRV_DET_STATE_REVERSE:
            return BST_TRUE;

        default:
            break;
    }
    return BST_FALSE;
}

BST_BOOL BST_SRV_CHbDetector::IsTask( BST_CORE_CPTask *pcTask )
{
    BST_ASSERT_NULL_RTN( pcTaskItem, BST_FALSE );

    if( pcTask != pcTaskItem->pcTask )
    {
        return BST_FALSE;
    }
    return BST_TRUE;
}

BST_UINT16 BST_SRV_CHbDetector::GetConfCyc( BST_UINT16 usInAppCyc )
{
    if( usInAppCyc > BST_SRV_DTC_MAX_LEN )
    {
        return BST_SRV_DTC_MAX_LEN;
    }
    if( 0 == usInAppCyc )
    {
        return 0;
    }
    return m_ucCfmTable[usInAppCyc];
}

BST_VOID BST_SRV_CHbDetector::Finish( BST_VOID )
{
    BST_CTaskSchdler           *pschd;

    UpdateConfCyc( m_ucDetectingCycle );
    m_enDtcState        = BST_SRV_DET_STATE_FINISH;

    /**
     �����������Ѿ�̽����������������ֱ������ʧ�ܺ�����
    */
    if( m_ucDetectingCycle >= BST_SRV_DTC_MAX_LEN )
    {
        BST_OS_TimerStop( m_ulDetectingTmr );
    }
    /**
     ���̽����Ϊ��С����(5��������)����ô3Сʱ���Ҫˢ��
    */
    else if( m_ucDetectingCycle == BST_SRV_DTC_MIN_PNT )
    {
        BST_OS_TimerStart( m_ulDetectingTmr, BST_SRV_DTC_THR_HUR );
    }
    /**
     ��������������С����֮�䣬��6Сʱ��ˢ��
    */
    else
    {
        BST_OS_TimerStart( m_ulDetectingTmr, BST_SRV_DTC_SIX_HUR );
    }
    pschd                      = BST_CTaskSchdler::GetInstance();
    if( BST_NULL_PTR != pschd )
    {
        pschd->onDetFinished ( m_ucDetectingCycle );
    }
}

BST_VOID BST_SRV_CHbDetector::ProcHbSuc( BST_VOID )
{
    BST_ASSERT_NULL( pcTaskItem );
    pcTaskItem->enLastErrType       = BST_CORE_SCHD_ACK_SUC;
    pcTaskItem->enSendState         = BST_APP_SEND_STATE_NORM;

    switch( m_enDtcState )
    {
        case BST_SRV_DET_STATE_INIT:
            Initial();
            RunTimer();
        break;

        case BST_SRV_DET_STATE_FORWARD:
            if( m_ucDetectingCycle >= BST_SRV_DTC_MAX_LEN )
            {
                Finish();
            }
            else
            {
                UpdateConfCyc( m_ucDetectingCycle );
                m_ulDetectingOfset  = 0;
                m_ucDetectingCycle++;
                RunTimer();
            }
        break;

        /**
         * ���˺������ɹ�����ζ��̽�����
         **/
        case BST_SRV_DET_STATE_REVERSE:
            Finish();
        break;

        case BST_SRV_DET_STATE_FINISH:
        break;

        default:
        break;
    }
}

BST_VOID BST_SRV_CHbDetector::ProcHbErr( BST_VOID )
{
    BST_ASSERT_NULL( pcTaskItem );
    switch( m_enDtcState )
    {
        /**
         ǰ��̽��ʧ�ܺ������������״̬,ǰ��/���˶��ø����÷���
         */
        case BST_SRV_DET_STATE_FORWARD:
        case BST_SRV_DET_STATE_REVERSE:
            m_enDtcState                = BST_SRV_DET_STATE_REVERSE;
            m_ulDetectingOfset         += BST_SRV_DTC_UNT_REW;
            
            /**
             ����Ѿ�̽�⵽��Сƫ��ֵ����ô��Ҫ����һ�����ڵ�
             */
            if( m_ulDetectingOfset > BST_SRV_DTC_MAX_REW )
            {
                /**
                 ���û�л�̽����С����(5����)����ô������̽��
                 */
                if( m_ucDetectingCycle > BST_SRV_DTC_MIN_PNT )
                {
                    m_ucDetectingCycle--;
                    m_ulDetectingOfset  = 0;
                }
                /**
                 ����Ѿ�̽�⵽��(3����)����ô���۽����Σ�����Ҫͣ����3Сʱ����̽
                 */
                else
                {
                    Finish();
                }
            }
        break;

        default:
        break;
    }
}

BST_ERR_ENUM_UINT8 BST_SRV_CHbDetector::UpdateConfCyc( BST_UINT8 ucPoint )
{
    BST_UINT32                          ulCnt;

    if( ucPoint > BST_SRV_DTC_MAX_LEN )
    {
        return BST_ERR_ITEM_NOT_EXISTED;
    }
    if( 0 == ucPoint )
    {
        return BST_ERR_ILLEGAL_PARAM;
    }

    /**
     * �õ�֮ǰ�ĵ㣬��������Ϊ����ʵֵ���õ㼰��֮��ĵ㣬����Ϊ��δ̽��,��2Ϊ��
     *  0-->0
     *  1-->1
     *  2-->2
     *  3-->2(3������15min����δ̽����ֻ����10����)
     **/
    for( ulCnt = 0; ulCnt < ucPoint; ulCnt++ )
    {
        m_ucCfmTable[ulCnt]             = ulCnt;
    }
    for( ulCnt = ucPoint; ulCnt <= BST_SRV_DTC_MAX_LEN; ulCnt++ )
    {
        m_ucCfmTable[ulCnt]             = ucPoint;
    }
    /**
        |<-              5���ӵ�������               ->|
        |------------------------|-Guard-|----Ofset----|
                                                ^̽����offset��˵������5����������
                                        ^����ʱ�䣬�������������ӳ���������ﵽ��ʱ��һ��ȡ20S
                        ^����̽����ϵͳ�������ʱ���������������ȷ֣���ΪTick����
    */
    m_ulCfmSysTick_Ms                   = ( ucPoint * BST_SRV_DTC_BAS_UNT 
                                          - m_ulDetectingOfset
                                          - 2*BST_SRV_DTC_GAD_OFS )/ucPoint;
    BST_DBG_LOG3("UpdateConfCyc,ucPoint:%d,m_ulCfmSysTick_Ms:%d,m_ulDetectingOfset:%d",ucPoint,m_ulCfmSysTick_Ms,m_ulDetectingOfset);
    return BST_NO_ERROR_MSG;
}


BST_VOID BST_SRV_CHbDetector::RunTimer( BST_VOID )
{
    BST_UINT32      ulTimerLen;
    BST_ASSERT_NULL( pcTaskItem );

    ulTimerLen                      = m_ucDetectingCycle*BST_SRV_DTC_BAS_UNT;

    if( ulTimerLen <= m_ulDetectingOfset )
    {
        return;
    }
    ulTimerLen                     -= m_ulDetectingOfset;

    if( ulTimerLen <= 2*BST_SRV_DTC_GAD_OFS )
    {
        return;
    }
    ulTimerLen                     -= 2*BST_SRV_DTC_GAD_OFS;
    BST_OS_TimerStart( m_ulDetectingTmr, ulTimerLen );
}


BST_VOID BST_SRV_CHbDetector::TimerExpired( BST_OS_TIMERID_T ulId, BST_VOID *pvPara )
{
    BST_ASSERT_NULL( pcTaskItem );
    switch( m_enDtcState )
    {
        case BST_SRV_DET_STATE_FORWARD:
        case BST_SRV_DET_STATE_REVERSE:
            /**
             * �����ʱ�����������ͣ���ôֻ�Ǽ�¼������ʶ
             **/
            if( BST_TRUE == m_bIsBlocked )
            {
                pcTaskItem->enSendState = BST_APP_SEND_STATE_BLOCK;
                BST_OS_TimerStop( m_ulDetectingTmr );
                return;
            }
        break;

        case BST_SRV_DET_STATE_FINISH:
            /**
             * ����Ѿ�̽�⵽������ڣ���ôֱ�ӷ���
             **/
            if( m_ucDetectingCycle >= BST_SRV_DTC_MAX_LEN )
            {
                return;
            }
            /**
             * �����ʱ���粻�ȣ���ô����������̽�⣬��Ҫ�Ӻ�1Сʱ
             **/
            if( BST_TRUE == m_bIsBlocked )
            {
                BST_OS_TimerStart( m_ulDetectingTmr, BST_SRV_DTC_ONE_HUR );
                return;
            }
            /**
             * ��ǰ����̽��
             **/
            m_ucDetectingCycle++;
            m_ulDetectingOfset      = 0;
            m_enDtcState            = BST_SRV_DET_STATE_FORWARD;
            pcTaskItem->enSendState = BST_APP_SEND_STATE_FIRST;
            BST_SRV_ApiSendPTaskEvent( pcTaskItem->pcTask,
                           BST_SRV_S2T_CYC_UPDATE,
                           BST_SRV_DTC_MAX_LEN );
            if ( BST_TRUE == pcTaskItem->pcTask->IsBusy () )
            {
                BST_RLS_LOG( "BST_SRV_CHbDetector::ReStart pC_PTask Is Busy" );
                return;
            }
            if( BST_TASK_STATE_START != pcTaskItem->pcTask->GetState () )
            {
                BST_RLS_LOG( "BST_SRV_CHbDetector::ReStart pC_PTask Is not start state" );
                return;
            }
            RunTimer();
        break;

        default:
        return;
    }
    BST_SRV_ApiSendPTaskEvent( pcTaskItem->pcTask, BST_SRV_S2T_EXE_COMAND, 0 );
    pcTaskItem->ulLastSendTime      = BST_OS_TimerNowMs();

}


BST_SRV_CHbDetector::~BST_SRV_CHbDetector( BST_VOID )
{
    BST_OS_TimerRemove( m_ulDetectingTmr );
}

