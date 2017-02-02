
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_XPDS_FSM_UP_LINK_CTRL_TBL_C

/*****************************************************************************
  1 Header File Include
*****************************************************************************/
#include "TafXpdsFsmUpLinkCtrlTbl.h"
#include "TafXpdsFsmUpLinkCtrl.h"
#include "TafXpdsSndInternalMsg.h"
#include "AtXpdsInterface.h"


#if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_AGPS))

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
/* TAF XPDS LINK״̬������:CDATA LINK Ctrl ״̬������*/
TAF_FSM_DESC_STRU                       g_stTafXpdsUpLinkCtrlFsmDesc;

/* TAF_XPDS_UP_LINK_CTRL_SUBSTA_INIT������ */
TAF_ACT_STRU   g_astTafXpdsUpLinkCtrlSubStaInitTbl[] =
{
    TAF_ACT_TBL_ITEM( UEPS_PID_XPDS,
                      ID_TAF_XPDS_XPDS_UP_LINK_CTRL_REQ,
                      TAF_XPDS_RcvXpdsServerBindReq_UpLinkCtrl_Init),
};

/* TAF_XPDS_UP_LINK_CTRL_SUBSTA_WAIT_DATA_CAll_CONNECT_CNF������ */
TAF_ACT_STRU   g_astTafXpdsUpLinkCtrlSubStaWaitDataCallConnectCnfTbl[] =
{
    TAF_ACT_TBL_ITEM(WUEPS_PID_AT,
                      ID_AT_XPDS_AP_DATA_CALL_STATUS_IND,
                      TAF_XPDS_RcvAtApDataCallStatusInd_UpLinkCtrl_WaitDataCallConnCnf),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                      TI_TAF_XPDS_WAIT_AT_DATA_CALL_IND,
                      TAF_XPDS_RcvTiWaitDataCallIndExpired_UpLinkCtrl_WaitDataCallConnCnf),

    TAF_ACT_TBL_ITEM( UEPS_PID_XPDS,
                      ID_TAF_XPDS_XPDS_INT_ABNORMAL_ABORT_AGPS_SESSION_IND,
                      TAF_XPDS_RcvXpdsAbortAgpsSessionInd_L2UpLink),
};

/* TAF_XPDS_UP_LINK_CTRL_SUBSTA_WAIT_OPEN_MPC_SOCKET_CNF������ */
TAF_ACT_STRU   g_astTafXpdsUpLinkCtrlSubStaWaitOpenMpcSocketCnfTbl[] =
{
    TAF_ACT_TBL_ITEM(WUEPS_PID_AT,
                      ID_AT_XPDS_AP_SERVER_BIND_STATUS_IND,
                      TAF_XPDS_RcvAtApBindServerStatusInd_UpLinkCtrl_WaitOpenMpcSocket),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                      TI_TAF_XPDS_WAIT_AT_BINDUP_IND,
                      TAF_XPDS_RcvTiWaitOpenMpcSocketExpired_UpLinkCtrl_WaitOpenMpcSocket),

    TAF_ACT_TBL_ITEM( UEPS_PID_XPDS,
                      ID_TAF_XPDS_XPDS_INT_ABNORMAL_ABORT_AGPS_SESSION_IND,
                      TAF_XPDS_RcvXpdsAbortAgpsSessionInd_L2UpLink),

};

/* TAF_XPDS_UP_LINK_CTRL_SUBSTA_WAIT_CLOSE_MPC_SOCKET_CNF������ */
TAF_ACT_STRU   g_astTafXpdsUpLinkCtrlSubStaWaitCloseMpcSocketCnfTbl[] =
{
    TAF_ACT_TBL_ITEM(WUEPS_PID_AT,
                      ID_AT_XPDS_AP_SERVER_BIND_STATUS_IND,
                      TAF_XPDS_RcvAtApBindServerStatusInd_UpLinkCtrl_WaitCloseMpcSocket),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                      TI_TAF_XPDS_WAIT_AT_BINDUP_IND,
                      TAF_XPDS_RcvTiWaitCloseMpcSocketExpired_UpLinkCtrl_WaitCloseMpcSocket),

    TAF_ACT_TBL_ITEM( UEPS_PID_XPDS,
                      ID_TAF_XPDS_XPDS_INT_ABNORMAL_ABORT_AGPS_SESSION_IND,
                      TAF_XPDS_RcvXpdsAbortAgpsSessionInd_L2UpLink),

};

/* TAF_XPDS_UP_LINK_CTRL_SUBSTA_WAIT_OPEN_PDE_SOCKET_CNF������ */
TAF_ACT_STRU   g_astTafXpdsUpLinkCtrlSubStaWaitOpenPdeSocketCnfTbl[] =
{
    TAF_ACT_TBL_ITEM(WUEPS_PID_AT,
                      ID_AT_XPDS_AP_SERVER_BIND_STATUS_IND,
                      TAF_XPDS_RcvAtApBindServerStatusInd_UpLinkCtrl_WaitOpenPdeSocket),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                      TI_TAF_XPDS_WAIT_AT_BINDUP_IND,
                      TAF_XPDS_RcvTiWaitOpenPdeSocketExpired_UpLinkCtrl_WaitOpenPdeSocket),

    TAF_ACT_TBL_ITEM( UEPS_PID_XPDS,
                      ID_TAF_XPDS_XPDS_INT_ABNORMAL_ABORT_AGPS_SESSION_IND,
                      TAF_XPDS_RcvXpdsAbortAgpsSessionInd_L2UpLink),

};

/* TAF_XPDS_UP_LINK_CTRL_SUBSTA_WAIT_CLOSE_PDE_SOCKET_CNF������ */
TAF_ACT_STRU   g_astTafXpdsUpLinkCtrlSubStaWaitClosePdeSocketCnfTbl[] =
{
    TAF_ACT_TBL_ITEM(WUEPS_PID_AT,
                      ID_AT_XPDS_AP_SERVER_BIND_STATUS_IND,
                      TAF_XPDS_RcvAtApBindServerStatusInd_UpLinkCtrl_WaitClosePdeSocket),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                      TI_TAF_XPDS_WAIT_AT_BINDUP_IND,
                      TAF_XPDS_RcvTiWaitClosePdeSocketExpired_UpLinkCtrl_WaitClosePdeSocket),

    TAF_ACT_TBL_ITEM( UEPS_PID_XPDS,
                      ID_TAF_XPDS_XPDS_INT_ABNORMAL_ABORT_AGPS_SESSION_IND,
                      TAF_XPDS_RcvXpdsAbortAgpsSessionInd_L2UpLink),
};

TAF_STA_STRU g_astTafXpdsUpLinkCtrlStaTbl[] =
{

    TAF_STA_TBL_ITEM( TAF_XPDS_UP_LINK_CTRL_SUBSTA_INIT,
                      g_astTafXpdsUpLinkCtrlSubStaInitTbl ),

    TAF_STA_TBL_ITEM( TAF_XPDS_UP_LINK_CTRL_SUBSTA_WAIT_DATA_CAll_CONNECT_CNF,
                      g_astTafXpdsUpLinkCtrlSubStaWaitDataCallConnectCnfTbl ),

    TAF_STA_TBL_ITEM( TAF_XPDS_UP_LINK_CTRL_SUBSTA_WAIT_OPEN_MPC_SOCKET_CNF,
                      g_astTafXpdsUpLinkCtrlSubStaWaitOpenMpcSocketCnfTbl ),

    TAF_STA_TBL_ITEM( TAF_XPDS_UP_LINK_CTRL_SUBSTA_WAIT_CLOSE_MPC_SOCKET_CNF,
                      g_astTafXpdsUpLinkCtrlSubStaWaitCloseMpcSocketCnfTbl ),

    TAF_STA_TBL_ITEM( TAF_XPDS_UP_LINK_CTRL_SUBSTA_WAIT_OPEN_PDE_SOCKET_CNF,
                      g_astTafXpdsUpLinkCtrlSubStaWaitOpenPdeSocketCnfTbl ),

    TAF_STA_TBL_ITEM( TAF_XPDS_UP_LINK_CTRL_SUBSTA_WAIT_CLOSE_PDE_SOCKET_CNF,
                      g_astTafXpdsUpLinkCtrlSubStaWaitClosePdeSocketCnfTbl ),

};
VOS_UINT32 TAF_XPDS_GetUpLinkCtrlStaTblSize( VOS_VOID )
{
    return (sizeof(g_astTafXpdsUpLinkCtrlStaTbl)/sizeof(TAF_STA_STRU));
}


TAF_STA_STRU* TAF_XPDS_GetUpLinkCtrlStaTblAddr( VOS_VOID )
{
    return g_astTafXpdsUpLinkCtrlStaTbl;
}


TAF_FSM_DESC_STRU * TAF_XPDS_GetFsmUpLinkFsmDescAddr( VOS_VOID )
{
    return (&g_stTafXpdsUpLinkCtrlFsmDesc);
}


#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif



