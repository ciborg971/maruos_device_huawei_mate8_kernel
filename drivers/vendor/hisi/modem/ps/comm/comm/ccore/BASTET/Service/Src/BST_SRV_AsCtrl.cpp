

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "BST_SRV_AsCtrl.h"
#include "BST_DRV_As.h"
#include "BST_OS_Memory.h"
#include "BST_DBG_MemLeak.h"
#include "BST_SRV_TaskMng.h"
/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_BST_SRV_ASCTRL_CPP
/*lint +e767*/
/******************************************************************************
  3 ����ʵ��
******************************************************************************/


BST_SRV_CAsCtrl *BST_SRV_CAsCtrl::GetInstance( BST_VOID )
{
    static BST_SRV_CAsCtrl *pcAsCtrlPtr = BST_NULL_PTR;
    if ( BST_NULL_PTR == pcAsCtrlPtr )
    {
        pcAsCtrlPtr = new BST_SRV_CAsCtrl();
    }
    return pcAsCtrlPtr;
}


BST_BOOL BST_SRV_CAsCtrl::Control( BST_PRTC_TYPE_ENUM_UINT32 enCmd, BST_VOID *pvData )
{
    BST_DRV_STRU                       *pAsDrvHandle;
    BST_ERR_ENUM_UINT8                  ucRtnVal;

    pAsDrvHandle                        = BST_DRV_AsGetDvcHandle();

    ucRtnVal                            = pAsDrvHandle->pfIoCtrl( enCmd, pvData );
    if( BST_NO_ERROR_MSG != ucRtnVal )
    {
        return BST_FALSE;
    }
    // TO DO, Call *.C File
    return BST_TRUE;
}


/*lint -e429*/
BST_VOID BST_SRV_CAsCtrl::UsingRrcVote( BST_UINT32 ulVid )
{
    BST_SRV_VOTEID_STRU *pstVoteId;

    /*
     * �����ǰͶƱ�����Ѿ����ã���ô��ⷵ��
     */
    if ( BST_FALSE == m_VoteRrcEnableFlag )
    {
        BST_RLS_LOG( "UsingRrcVote : EnableFlag is FALSE.");
        return;
    }

    /*
     * ����ͶƱ������������Ѿ�ͶƱ��������ͶƱ����������
     */
    for ( pstVoteId  = ( BST_SRV_VOTEID_STRU *)lstFirst( &m_stVoteList );
          BST_NULL_PTR != pstVoteId ;
          pstVoteId  = ( BST_SRV_VOTEID_STRU *)lstNext( (NODE *) pstVoteId ) )
    {
        if ( ulVid == pstVoteId->ulName )
        {
            BST_RLS_LOG1 ( "App Vote Vid=%d already existed", ulVid );
            return;
        }
    }

    /*
     * ΪͶƱ����������Դ
     */
    pstVoteId           = ( BST_SRV_VOTEID_STRU *)BST_OS_MALLOC
                          ( BST_OS_SIZEOF( BST_SRV_VOTEID_STRU ) );
    if ( BST_NULL_PTR == pstVoteId )
    {
        return;
    }
    pstVoteId->ulName   = ulVid;
    lstAdd( &m_stVoteList, (NODE *)pstVoteId );

    BST_RLS_LOG3 ( "App Vote RRC Using, ProcId=%u, TaskId=u%, New Voting-Count=U%",
                 ( ( ulVid>>16 ) & 0xFFFF ),
                 ( ( ulVid ) & 0xFFFF ),
                 lstCount( &m_stVoteList ) );
}
/*lint +e429*/

/*lint -e438*/
BST_VOID BST_SRV_CAsCtrl::UsingRrcDeVote( BST_UINT32 ulVid )
{
    BST_SRV_VOTEID_STRU *pstVoteId;

    /*
     * ���ͶƱ�����Ѿ���ֹ����ô��������
     */
    if ( BST_FALSE == m_VoteRrcEnableFlag )
    {
        BST_RLS_LOG( "BST_SRV_CAsCtrl::UsingRrcDeVote : EnableFlag is disabled.");
        return;
    }

    /*
     * ������Դ����ҳ�Ʊ���Ƿ��Ѿ�����
     */
    for ( pstVoteId  = ( BST_SRV_VOTEID_STRU *)lstFirst( &m_stVoteList );
          BST_NULL_PTR != pstVoteId ;
          pstVoteId  = ( BST_SRV_VOTEID_STRU *)lstNext( (NODE *) pstVoteId ) )
    {
        if ( ulVid == pstVoteId->ulName )
        {
            /*
             * �ҵ��󣬲�����Ҫ������ɾ����ͬʱ����������Դ
             */
            lstDelete( &m_stVoteList, (NODE *)pstVoteId );
            BST_OS_FREE( pstVoteId );
            break;
        }
    }
    BST_RLS_LOG3( "BST_SRV_CAsCtrl::UsingRrcDeVote, ProcId=%u, TaskId=u%, New Voting-Count=U%",
                ( ( ulVid>>16 ) & 0xFFFF ),
                ( ( ulVid ) & 0xFFFF ),
                lstCount( &m_stVoteList ) );

    /*
     * �����Ʊ��ɺ󣬽��Ϊ���ˣ���������ʱ���ƣ���ʱ����ʱ�����
     */
    if ( 0 == lstCount( &m_stVoteList ) )
    {
        if ( !BST_OS_IsTimerValid ( m_ulFdTimerId ) )
        {
            return;
        }
        BST_OS_TimerStart ( m_ulFdTimerId, BST_AS_REL_RRC_TIMER_LEN );
    }
}
/*lint +e438*/

BST_VOID BST_SRV_CAsCtrl::ProcRrcEvent( BST_UINT32 ulLength, BST_VOID *pvData )
{
    BST_BOOL                            bReportAllowedFlag;
    BST_UINT32                          ulTrxRptFlag;
    BST_DRV_STRU                       *pAsDriver;
    BST_SRV_VOTEID_STRU                *pstVoteId;
    BST_SRV_VOTEID_STRU                *pstVoteIdNext;
    BST_UINT32                          bOldRrcState;

    pAsDriver               = BST_DRV_AsGetDvcHandle();
    if( BST_OS_SIZEOF( BST_UINT32 ) != ulLength )
    {
        return;
    }

    if( BST_NULL_PTR == pvData )
    {
        return;
    }

    bOldRrcState            = m_ulRrcState;

    BST_OS_MEMCPY( &m_ulRrcState, pvData, ulLength );

    /*�������״̬û�б仯�������账��*/
    if ( BST_AS_IsRrcConnected( bOldRrcState ) == BST_AS_IsRrcConnected( m_ulRrcState ) )
    {
        return;
    }

    /* �����ǰ��������̬��������ֹͣ��ֹ�ϱ���ʱ��*/
    if ( BST_TRUE == BST_AS_IsRrcConnected( m_ulRrcState ) )
    {
        if ( BST_OS_IsTimerValid ( m_ulReportTimerId ) )
        {
            BST_OS_TimerStop( m_ulReportTimerId );
        }
        return;
    }

    /*
     * ����Ϊ�˳�����̬���̣����ȳ�ʼ��ͶƱʹ�ܿ���
     */
    m_VoteRrcEnableFlag     = BST_TRUE;

    BST_RLS_LOG ( "BST_SRV_CAsCtrl::ProcRrcEvent : BST_AS_RRC_RELEASED EnableFlag is TRUE.");

    /*
     * ���ͶƱ������ȫ����Դ
     */
    for ( pstVoteId = ( BST_SRV_VOTEID_STRU *)lstFirst( &m_stVoteList );
          BST_NULL_PTR != pstVoteId ;
          pstVoteId  = pstVoteIdNext )
    {
        pstVoteIdNext       = ( BST_SRV_VOTEID_STRU *)lstNext( (NODE *) pstVoteId );
        lstDelete( &m_stVoteList, (NODE *)pstVoteId );
        BST_OS_FREE( pstVoteId );
    }

    /*
     * ����ײ��ϱ������շ�ָʾ��Ĭ�ϲ�����CP->AP�ϱ���Ϣ
     */
    ulTrxRptFlag            = BST_TRUE;
    bReportAllowedFlag      = BST_TRUE;

    pAsDriver->pfIoCtrl( BST_DRV_CMD_SET_TX_ENABLE, &ulTrxRptFlag );
    pAsDriver->pfIoCtrl( BST_DRV_CMD_SET_RX_ENABLE, &ulTrxRptFlag );
    pAsDriver->pfIoCtrl( BST_DRV_CMD_GET_REPORT_FLAG, &bReportAllowedFlag );
    /*
     * �����ʱ���ڣ���ô��ʱ�������ϱ�����֮��򿪿��أ�����״̬�ϱ�
     */
    if ( BST_OS_IsTimerValid ( m_ulReportTimerId )
     &&( BST_FALSE == bReportAllowedFlag ) )
    {
        BST_RLS_LOG( "BST_SRV_CAsCtrl::ProcRrcEvent: Report to AP will be Allowed after 3 Sec.");
        BST_OS_TimerStart( m_ulReportTimerId, BST_AS_REPORT_ALLOWED_TIMER_LEN );
    }
    return;
}


BST_VOID BST_SRV_CAsCtrl::ProcDataTrs( BST_VOID )
{
    BST_DRV_STRU               *pAsDriver;
    BST_BOOL                    bReportAllowedFlag;
    BST_SRV_VOTEID_STRU        *pstVoteId;                     
    BST_SRV_VOTEID_STRU        *pstVoteIdNext;                     

    pAsDriver                   = BST_DRV_AsGetDvcHandle();
    bReportAllowedFlag          = BST_TRUE;
    m_VoteRrcEnableFlag         = BST_FALSE;

    for ( pstVoteId = ( BST_SRV_VOTEID_STRU *)lstFirst( &m_stVoteList );
          BST_NULL_PTR != pstVoteId ;
          pstVoteId  = pstVoteIdNext )
    {
        pstVoteIdNext           = ( BST_SRV_VOTEID_STRU *)lstNext( (NODE *) pstVoteId );
        lstDelete( &m_stVoteList, (NODE *)pstVoteId );
        BST_OS_FREE( pstVoteId );
    }

    if ( BST_OS_IsTimerValid ( m_ulReportTimerId ) )
    {
        BST_OS_TimerStop( m_ulReportTimerId );
    }

    /*
     * ֪ͨ�ײ㣬����modem��AP�ϱ��¼�
     */
    ( BST_VOID )pAsDriver->pfIoCtrl( BST_DRV_CMD_SET_REPORT_FLAG,&bReportAllowedFlag );
}

BST_VOID BST_SRV_CAsCtrl::AsEventCallback(
    BST_AS_EVT_ENUM_UINT32  enEvent,
    BST_UINT32              ulLength,
    BST_VOID               *pvData )
{
    switch( enEvent )
    {
        case BST_AS_EVT_L3_RRC_STATE:
            ProcRrcEvent( ulLength, pvData );
            break;

        case BST_AS_EVT_L3_AP_RX_RCV_IND:
            ProcDataTrs();
            break;

        case BST_AS_EVT_L3_AP_TX_SEND_IND:
            ProcDataTrs();
            break;

        default:
            break;
    }
}


BST_VOID BST_SRV_CAsCtrl::TimerExpired( BST_OS_TIMERID_T lId, BST_VOID* pvPara )
{
    BST_DRV_STRU                       *pAsDrvHandle;
    BST_BOOL                            bReportAllowedFlag;

    /*
     * ���ٶ�����ʱ�����ڣ�����Ҫ����������Ƿ�����ʹ���ߣ��Ƿ��������
     */
    if ( lId == m_ulFdTimerId )
    {
        if( ( 0 != lstCount( &m_stVoteList ) )
          ||( BST_FALSE == m_VoteRrcEnableFlag ) )
        {
            return;
        }

        pAsDrvHandle                    = BST_DRV_AsGetDvcHandle();
        if( BST_NULL_PTR == pAsDrvHandle->pfIoCtrl )
        {
            return;
        }
        pAsDrvHandle->pfIoCtrl( BST_DRV_CMD_RELEASE_RRC, BST_NULL_PTR );
        BST_RLS_LOG( "RRC Will Be released.");
    }
    /*
     * �ϱ����ƶ�ʱ����ʱ��������CP->AP�����ϱ�AT�¼�
     */
    else if ( lId == m_ulReportTimerId )
    {
        pAsDrvHandle                    = BST_DRV_AsGetDvcHandle();
        bReportAllowedFlag              = BST_TRUE;
        if( BST_NULL_PTR != pAsDrvHandle->pfIoCtrl )
        {
            ( BST_VOID )pAsDrvHandle->pfIoCtrl( BST_DRV_CMD_SET_REPORT_FLAG,
                                                &bReportAllowedFlag );
        }
    }
    else
    {
        return;
    }
}


BST_SRV_CAsCtrl::BST_SRV_CAsCtrl( BST_VOID )
    : BST_SRV_CAsRcver( BST_SRV_GetSysMsgHandle() ),
      m_ulFdTimerId( BST_OS_INVALID_TIMER_ID ),
      m_ulReportTimerId( BST_OS_INVALID_TIMER_ID )
{
    m_VoteRrcEnableFlag                 = BST_TRUE;
    m_ulFdTimerId                       = BST_OS_TimerCreateCpp( this,
                                                                 BST_NULL_PTR,
                                                                 BST_SRV_GetSysMsgHandle() );
    m_ulReportTimerId                   = BST_OS_TimerCreateCpp( this,
                                                                 BST_NULL_PTR,
                                                                 BST_SRV_GetSysMsgHandle() );
    m_ulRrcState                        = BST_RRC_STATE_BUTT;
    RegAsNotice( BST_AS_EVT_L3_RRC_STATE );
    RegAsNotice( BST_AS_EVT_L3_AP_RX_RCV_IND );
    RegAsNotice( BST_AS_EVT_L3_AP_TX_SEND_IND );
    lstInit( &m_stVoteList );
}


BST_SRV_CAsCtrl::~BST_SRV_CAsCtrl( BST_VOID )
{
    BST_RLS_LOG("BST_SRV_CAsCtrl destructor exception!");
}


