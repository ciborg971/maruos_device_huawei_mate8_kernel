

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "siapppb.h"
#include "TafXsmsCtx.h"
#include "xcc_sms_pif.h"
#include "TafXsmsTimer.h"
#include "TafXsmsMoFsmMain.h"
#include "TafAppXsmsInterface.h"
#include "TafXsmsMoFsmMainTbl.h"
#include "MmaXsmsInterface.h"
#include "TafXsmsStkInterface.h"
#include "TafXpdsXsmsInterface.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_TAF_XSMS_MO_FSM_MAIN_TBL_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/* Mo״̬��״̬ȫ�ֱ��� */
TAF_FSM_DESC_STRU                       g_stTafXsmsMoFsmDesc;

/* XSMS Mo_IDLE�µ��¼������ */
TAF_ACT_STRU                            g_astTafXsmsMoIdleActTbl[] =
{
    /* �յ�AT ��������Ĵ��� */
    TAF_ACT_TBL_ITEM( UEPS_PID_XSMS,
                      TAF_XSMS_APP_MSG_TYPE_SEND_REQ,
                      TAF_XSMS_RcvAtSendReqProc_MoIdle),

    /* �յ�STK�ķ������� */
    TAF_ACT_TBL_ITEM( MAPS_STK_PID,
                      ID_STK_XSMS_SEND_SMS_REQ,
                      TAF_XSMS_RcvStkSendReqProc_MoIdle ),

    /* �յ�MTA ��������Ĵ��� */
    TAF_ACT_TBL_ITEM( UEPS_PID_XPDS,
                      ID_XPDS_XSMS_SEND_REQ,
                      TAF_XSMS_RcvXpdsSendReqProc_MoIdle)
};

/* XSMS MoWaitFdnCnf ���¼������ */
TAF_ACT_STRU                            g_astTafXsmsMoWaitFdnCnfActTbl[] =
{
    /* �ȴ�FDN_CNF��ʱ����*/
    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_XSMS_TIMER_MO_WAIT_FDN_CNF,
                      VOS_NULL_PTR ),

    /* �յ���FDN_CNF */
    TAF_ACT_TBL_ITEM( MAPS_PB_PID,
                      SI_PB_EVENT_FDNCHECK_CNF,
                      VOS_NULL_PTR )/* FDN �Ժ�ʵ�� */
};

/* XSMS Mo_WAIT_CC_CNF���¼������ */
TAF_ACT_STRU                            g_astTafXsmsMoWaitCcCNFActTbl[] =
{
    /* �ȴ�CC_CNF��ʱ����*/
    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_XSMS_TIMER_MO_WAIT_CC_CNF,
                      VOS_NULL_PTR  ),

    /* �յ�CC_CNF */
    TAF_ACT_TBL_ITEM( MAPS_STK_PID,
                      USIMM_STKENVELOPE_CNF,
                      VOS_NULL_PTR ), /* SMS Call Control �Ժ�ʵ�� */

};

/* XSMS MO_WAITING_XCC_ORIG_CALL_CNF���¼������ */
TAF_ACT_STRU                            g_astTafXsmsMoWaitXccCallCnfActTbl[] =
{
    /* �ȴ�XCC_ORIG_CALL_CNF��ʱ����*/
    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_XSMS_TIMER_MO_WAIT_XCC_CALL_CNF,
                      TAF_XSMS_RcvXccCallCnfTimeOut_MoWaitXccCallCnf),

    /* �յ�XCC_ORIG_CALL_CNF�Ĵ��� */
    TAF_ACT_TBL_ITEM( UEPS_PID_XCC,
                      ID_XCC_CSMS_ORIG_SMS_CALL_CNF,
                      TAF_XSMS_RcvXccOrigCallCnf_MoWaitXccOrigCallCnf),

    /* �յ��ӳ��ؽ��ŵ���ʱ�Ĵ��� */
    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_XSMS_TIMER_MO_RELINK,
                      TAF_XSMS_RcvRelinkTimeOut_MoWaitXccOrigCallCnf ),


    /* �յ��ض�����ɵ���Ϣ */
    TAF_ACT_TBL_ITEM( WUEPS_PID_MMA,
                      ID_MMA_XSMS_SERVICE_STATUS_IND,
                      TAF_XSMS_RcvMmaServiceStatus_MoWaitXccOrigCallCnf ),

};

/* XSMS Mo_WAITING_XCC_SO_IND���¼������ */
TAF_ACT_STRU                            g_astTafXsmsMoWaitXccSoIndActTbl[] =
{
    /* �ȴ�XCC_SO_IND��ʱ����*/
    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_XSMS_TIMER_MO_WAIT_XCC_SO_IND,
                      TAF_XSMS_RcvXccSoIndTimeOut_MoWaitXccSoInd ),

    /* �յ�XCC_SO_IND�Ĵ��� */
    TAF_ACT_TBL_ITEM( UEPS_PID_XCC,
                      ID_XCC_CSMS_SERVICE_CONNECT_IND,
                      TAF_XSMS_RcvXccSoInd_MoWaitXccSoInd),

    /* �յ�ABORT��Ϣ */
    TAF_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_SMS_ABORT_IND,
                      TAF_XSMS_RcvMoLinkAbort_MoWaitSoInd )

};
/* XSMS MO_WAITING_AS_CNF״̬���¼������ */
TAF_ACT_STRU                            g_astTafXsmsMoWaitAsCnfActTbl[] =
{
    /* �յ������AS_CNF */
    TAF_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_DSCH_DATA_CNF,
                      TAF_XSMS_RcvDschDataCnf_MoWaitAsCnf),

    TAF_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_CSCH_DATA_CNF,
                      TAF_XSMS_RcvCschDataCnf_MoWaitAsCnf),

    /* �ȴ������AS_CNF��ʱ���� */
    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_XSMS_TIMER_MO_WAIT_AS_CNF,
                      TAF_XSMS_RcvAsCnfTimeout_MoWaitAsCnf),


    /* �ӳ����·��͵Ķ�ʱ����ʱ */
    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_XSMS_TIMER_MO_RESEND,
                      TAF_XSMS_RcvResendTimeOut_MoWaitAsCnf),

    /* �յ�ABORT��Ϣ */
    TAF_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_SMS_ABORT_IND,
                      TAF_XSMS_RcvMoLinkAbort_MoWaitAsCnf ),

    /* �յ�TL_ACK���� *//* ע���AS-ACK*/
    TAF_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_DSCH_DATA_IND,
                      TAF_XSMS_RcvDschTlACK_MoWaitTlACK ),

    TAF_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_CSCH_DATA_IND,
                      TAF_XSMS_RcvCschTlACK_MoWaitTlACK ),
};

/* XSMS MO_WAITING_TL_ACK״̬���¼������ */
TAF_ACT_STRU                            g_astTafXsmsMoWaitTlAckActTbl[] =
{
    /* �յ�TL_ACK���� *//* ע���AS-ACK*/
    TAF_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_DSCH_DATA_IND,
                      TAF_XSMS_RcvDschTlACK_MoWaitTlACK ),

    TAF_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_CSCH_DATA_IND,
                      TAF_XSMS_RcvCschTlACK_MoWaitTlACK ),

    /* MO_WAITING_TL_ACK��ʱ���� */
    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_XSMS_TIMER_MO_WAIT_TL_ACK,
                      TAF_XSMS_RcvTlAckTimeOut_MoWaitTlACK),


    /* �յ�ABORT��Ϣ */
    TAF_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_SMS_ABORT_IND,
                      TAF_XSMS_RcvMoLinkAbort_MoWaitTlAck )

};

/* XSMS MO_WAITING_XCC_END_CALL_CNF ״̬���¼������ */
TAF_ACT_STRU                            g_astTafXsmsMoWaitCallEndActTbl[] =
{
    /* ����XCC �����ɹ����� */
    TAF_ACT_TBL_ITEM( UEPS_PID_XCC,
                      ID_XCC_CSMS_END_SMS_CALL_CNF,
                      TAF_XSMS_RcvEndCallCnf_MoWaitEndCallCnf),

    /* �ȴ�������ʱ���� */
    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_XSMS_TIMER_MO_WAIT_END_CALL,
                      TAF_XSMS_RcvEndCallCnfTimeout_MoWaitEndCallCnf),

        /* ������·�Ͽ��Ĵ��� */
    TAF_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_SMS_ABORT_IND,
                      TAF_XSMS_RcvSmsAbortInd_MoWaitLinkAbort),

};


/* XSMS MO_WAITING_XCC_END_CALL_CNF ״̬���¼������ */
TAF_ACT_STRU                            g_astTafXsmsMoWaitCasAbortIndActTbl[] =
{
    /* ������·�Ͽ��Ĵ��� */
    TAF_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_SMS_ABORT_IND,
                      TAF_XSMS_RcvSmsAbortInd_MoWaitLinkAbort),

    /* �ȴ�������ʱ���� */
    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_XSMS_TIMER_MO_WAIT_SMS_ABORT,
                      TAF_XSMS_RcvSmsAbortInd_MoWaitLinkAbort),

};


/* Xsms Mo״̬��״̬����� */
TAF_STA_STRU                            g_astTafXsmsMoStaTbl[] =
{
    /*****************����Mo_IDLE_STATE״̬ת�Ʊ�**********************/
    TAF_STA_TBL_ITEM( TAF_XSMS_MO_IDLE_STATE,
                      g_astTafXsmsMoIdleActTbl ),

    /*****************����MO_WAITING_FDN_CNF**********************/
    TAF_STA_TBL_ITEM( TAF_XSMS_MO_WAITING_FDN_CNF,
                      g_astTafXsmsMoWaitFdnCnfActTbl ),

    /*****************����MO_WAITING_CC_CNF״̬ת�Ʊ�**********************/
    TAF_STA_TBL_ITEM( TAF_XSMS_MO_WAITING_CC_CNF,
                      g_astTafXsmsMoWaitCcCNFActTbl ),

    /*****************����MO_WAITING_XCC_ORIG_CALL_CNF,״̬ת�Ʊ�**********************/
    TAF_STA_TBL_ITEM( TAF_XSMS_MO_WAITING_XCC_ORIG_CALL_CNF,
                      g_astTafXsmsMoWaitXccCallCnfActTbl),

    /*****************����MO_WAITING_XCC_SO_IND״̬ת�Ʊ�****************/
    TAF_STA_TBL_ITEM( TAF_XSMS_MO_WAITING_XCC_SO_IND,
                      g_astTafXsmsMoWaitXccSoIndActTbl ),

    /*****************����MO_WAITING_AS_CNF״̬ת�Ʊ�****************/
    TAF_STA_TBL_ITEM( TAF_XSMS_MO_WAITING_AS_CNF,
                      g_astTafXsmsMoWaitAsCnfActTbl),

    /*****************����MO_WAITING_TL_ACK״̬ת�Ʊ�*****************/
    TAF_STA_TBL_ITEM( TAF_XSMS_MO_WAITING_TL_ACK,
                      g_astTafXsmsMoWaitTlAckActTbl ),

    /*****************����MO_WAITING_XCC_END_CALL_CNF״̬ת�Ʊ�***********************/
    TAF_STA_TBL_ITEM( TAF_XSMS_MO_WAITING_XCC_END_CALL_CNF,
                      g_astTafXsmsMoWaitCallEndActTbl ),


    /*****************����MO_WAITING_CAS_SMS_ABORT_IND״̬ת�Ʊ�***********************/
    TAF_STA_TBL_ITEM( TAF_XSMS_MO_WAITING_CAS_SMS_ABORT_IND,
                      g_astTafXsmsMoWaitCasAbortIndActTbl ),

};

/*****************************************************************************
  3 ��������
*****************************************************************************/

VOS_UINT32 TAF_XSMS_GetMoFsmTblNum(VOS_VOID)
{
    return (sizeof(g_astTafXsmsMoStaTbl)/sizeof(TAF_STA_STRU));
}

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

