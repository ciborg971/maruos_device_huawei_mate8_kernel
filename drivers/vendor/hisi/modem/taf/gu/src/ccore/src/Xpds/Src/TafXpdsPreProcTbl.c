

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "TafXpdsPreProcTbl.h"
#include "TafXpdsPreProc.h"
#include "TafXpdsXsmsInterface.h"
#include "cas_1x_control_main_nas_pif.h"
#include "TafXpdsFsmMainTbl.h"



#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_TAF_XPDS_PRE_PROC_TBL_C


#if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_AGPS))

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/* XPDS Ԥ����״̬��״̬ȫ�ֱ��� */
TAF_FSM_DESC_STRU                       g_stTafXpdsPreProcFsmDesc;

/* XPDS pre proc״̬�µ��¼������ */
TAF_ACT_STRU                            g_astTafXpdsPreProcActTbl[] =
{
    /* �յ�MPC��ַ��������Ĵ��� */
    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      ID_AT_XPDS_GPS_CFG_MPC_ADDR_REQ,
                      TAF_XPDS_RcvAtGpsCfgMpcAddrReq_PreProc),

    /* �յ�PDE��ַ��������Ĵ��� */
    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      ID_AT_XPDS_GPS_CFG_PDE_ADDR_REQ,
                      TAF_XPDS_RcvAtGpsCfgPdeAddrReq_PreProc),

    /* �յ�ģʽ������������Ĵ��� */
    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      ID_AT_XPDS_GPS_CFG_POSITION_MODE_REQ,
                      TAF_XPDS_RcvAtGpsCfgPositionModeReq_PreProc),

    /* �յ�������Bind Cnf�Ĵ��� */
    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      ID_AT_XPDS_AP_SERVER_BIND_STATUS_IND,
                      TAF_XPDS_RcvAtApServerBindStatusInd_PreProc),

    /* �յ���ʼ��λ��������Ĵ��� */
    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      ID_AT_XPDS_GPS_START_REQ,
                      TAF_XPDS_RcvAtGpsStartReq_PreProc),

    /* �յ���ѯ��������Ĵ��� */
    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      ID_AT_XPDS_GPS_QRY_REFLOC_INFO_REQ,
                      TAF_XPDS_RcvAtGpsQryRefLocInfoReq_PreProc),

    /* �յ���ѯʱ�����������Ĵ��� */
    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      ID_AT_XPDS_GPS_QRY_TIME_INFO_REQ,
                      TAF_XPDS_RcvAtGpsQryTimeInfoReq_PreProc),

    /* �յ�GPS���AGPS�Ự */
    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      ID_AT_XPDS_GPS_STOP_REQ,
                      TAF_XPDS_RcvAtGpsStopReq_PreProc ),

    /* �յ���ѯ��������Ĵ��� */
    TAF_ACT_TBL_ITEM( UEPS_PID_1XCMEAS,
                      ID_CAS_XPDS_TIME_SYNC_IND,
                      TAF_XPDS_RcvCasTimeSyncInd_PreProc),

    /* �յ���ѯ��������Ĵ��� */
    TAF_ACT_TBL_ITEM( UEPS_PID_HRUP,
                      ID_CAS_XPDS_TIME_SYNC_IND,
                      TAF_XPDS_RcvCasTimeSyncInd_PreProc),

    /* �յ���ѯ��������Ĵ��� */
    TAF_ACT_TBL_ITEM( UEPS_PID_1XCMEAS,
                      ID_CAS_XPDS_REF_LOC_IND,
                      TAF_XPDS_RcvCasRefLocInd_PreProc),

    /* �յ���ѯ��������Ĵ��� */
    TAF_ACT_TBL_ITEM( UEPS_PID_HRUP,
                      ID_CAS_XPDS_REF_LOC_IND,
                      TAF_XPDS_RcvCasRefLocInd_PreProc),

    /* �յ�PDE���ݰ� */
    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      ID_AT_XPDS_AP_FORWARD_DATA_IND,
                      TAF_XPDS_RcvApForwardDataInd_PreProc),

    /* �յ�XSMS DATA IND�Ĵ��� */
    TAF_ACT_TBL_ITEM( UEPS_PID_XSMS,
                      ID_XSMS_XPDS_RCV_IND,
                      TAF_XPDS_RcvXsmsRcvInd_PreProc),

    TAF_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_DSCH_DATA_IND,
                      TAF_XPDS_RcvCasDschDataInd_PreProc),

    TAF_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_XPDS_REF_LOC_CNF,
                      TAF_XPDS_RcvCasRefLocCnf_PreProc),


    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_XPDS_CP_L2_PDE_MSA_WAIT_PPM_COMPLETE_NI_QUALITY,
                      TAF_XPDS_RcvPpmTimerExpire_PreProc),

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_XPDS_IS801_SESSION,
                      TAF_XPDS_RcvTiXpdsIs801SessionExpired_PreProc),

    /* δ�յ�NI�ظ�����ʱ���� */
    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_XPDS_WAIT_GPS_ANSWER_NI_REQ_CNF,
                      TAF_XPDS_RcvTiWaitGpsAnswerNiReqExpire_PreProc ),
};

/* Ԥ�������Ϣ״̬�� */
TAF_STA_STRU g_astTafXpdsPreStaTbl[] =
{
    TAF_STA_TBL_ITEM( TAF_XPDS_L1_STA_PREPROC,
                      g_astTafXpdsPreProcActTbl)
};


/*****************************************************************************
  3 ��������
*****************************************************************************/

VOS_UINT32 TAF_XPDS_GetPreProcStaTblSize( VOS_VOID )
{
    return (sizeof(g_astTafXpdsPreStaTbl)/sizeof(TAF_STA_STRU));
}


TAF_STA_STRU* TAF_XPDS_GetPreProcStaTblAddr( VOS_VOID )
{
    return (g_astTafXpdsPreStaTbl);
}


TAF_FSM_DESC_STRU* TAF_XPDS_GetPreProcFsmDescAddr( VOS_VOID )
{
    return (&g_stTafXpdsPreProcFsmDesc);
}

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


