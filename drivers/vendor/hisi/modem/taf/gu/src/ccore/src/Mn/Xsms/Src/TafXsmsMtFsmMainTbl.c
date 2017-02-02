

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "TafXsmsMtFsmMain.h"
#include  "TafXsmsMtFsmMainTbl.h"
#include  "xcc_sms_pif.h"
#include  "TafXsmsTimer.h"
#include  "TafXsmsCtx.h"
#include  "cas_1x_control_main_nas_pif.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_TAF_XSMS_MT_FSM_MAIN_TBL_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/* MT״̬��״̬ȫ�ֱ��� */
TAF_FSM_DESC_STRU                       g_stTafXsmsMtFsmDesc;

/* XSMS MT_IDLE�µ��¼������ */
TAF_ACT_STRU                            g_astTafXsmsMtIdleActTbl[] =
{
    /* ���յ�DSCH_DATA_IND�Ĵ��� */
    TAF_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_DSCH_DATA_IND,
                      TAF_XSMS_RcvDataInd_MtIdle ),

    /* ���յ�CSCH_DATA_IND�Ĵ��� */
    TAF_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_CSCH_DATA_IND,
                      TAF_XSMS_RcvDataInd_MtIdle ),

    /* �յ�Incoming call�Ĵ��� */
    TAF_ACT_TBL_ITEM( UEPS_PID_XCC,
                      ID_XCC_CSMS_INCOMING_CALL_IND,
                      TAF_XSMS_RcvIncomingCall_MtIdle ),

};


/* XSMS MT_WAITING_XCC_CALL_CONN���¼������ */
TAF_ACT_STRU                            g_astTafXsmsMtWaitXccConnActTbl[] =
{
    /* �ȴ�CONN_IND��ʱ����*/
    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_XSMS_TIMER_MT_WAIT_CONN_IND,
                      TAF_XSMS_RcvCallConnTimeout_MtWaitXccCallConnCnf ),

    /* �յ���XCC_CONN_IND */
    TAF_ACT_TBL_ITEM( UEPS_PID_XCC,
                      ID_XCC_CSMS_CALL_CONN_IND,
                      TAF_XSMS_RcvCallConnCnf_MtWaitXccCallConnCnf ),

    /* �յ�ABORT��Ϣ */
    /* ����CAS����traffic channel���Ŵ��� */
    TAF_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_DSCH_DATA_IND,
                      TAF_XSMS_RcvDschDataInd_MtWaitCasDschDataInd ),

    /* �յ�ABORT��Ϣ */
    TAF_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_SMS_ABORT_IND,
                      TAF_XSMS_RcvMtLinkAbort )

};

/* XSMS MT_WAITING_XCC_CNF���¼������ */
TAF_ACT_STRU                            g_astTafXsmsMtWaitXccAnsCallCnfActTbl[] =
{
    /* �ȴ�XCC_CNF��ʱ����*/
    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_XSMS_TIMER_MT_WAIT_XCC_CNF,
                      TAF_XSMS_RcvAnsCallCnfTimeout_MtWaitXccAnsCallCnf ),

    /* �յ�XCC_CNF */
    TAF_ACT_TBL_ITEM( UEPS_PID_XCC,
                      ID_XCC_CSMS_ANSWER_CALL_CNF,
                      TAF_XSMS_RcvAnsCallCnf_MtWaitXccAnsCallCnf ),

    /* ����CAS����traffic channel���Ŵ��� */
    TAF_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_DSCH_DATA_IND,
                      TAF_XSMS_RcvDschDataInd_MtWaitCasDschDataInd ),

    /* �յ�ABORT��Ϣ */
    TAF_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_SMS_ABORT_IND,
                      TAF_XSMS_RcvMtLinkAbort )

};

/* XSMS MT_WAITING_XCC_SO_IND���¼������ */
TAF_ACT_STRU                            g_astTafXsmsMtWaitXccSoIndActTbl[] =
{
    /* �ȴ�XCC_SO_IND��ʱ����*/
    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_XSMS_TIMER_MT_WAIT_XCC_SO_IND,
                      TAF_XSMS_RcvSoIndTimeout_MtWaitXccSoInd ),

    /* �յ�XCC_SO_IND�Ĵ��� */
    TAF_ACT_TBL_ITEM( UEPS_PID_XCC,
                      ID_XCC_CSMS_SERVICE_CONNECT_IND,
                      TAF_XSMS_RcvSoInd_MtWaitXccSoInd ),

    /* ����CAS����traffic channel���Ŵ��� */
    TAF_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_DSCH_DATA_IND,
                      TAF_XSMS_RcvDschDataInd_MtWaitCasDschDataInd ),

    /* �յ�ABORT��Ϣ */
    TAF_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_SMS_ABORT_IND,
                      TAF_XSMS_RcvMtLinkAbort )

};

/* XSMS MT_WAITING_DSDH_DATA_IND״̬���¼������ */
TAF_ACT_STRU                            g_astTafXsmsMtWaitingDSCHDataIndActTbl[] =
{
    /* ����CAS����traffic channel���Ŵ��� */
    TAF_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_DSCH_DATA_IND,
                      TAF_XSMS_RcvDschDataInd_MtWaitCasDschDataInd ),


    /* �ȴ����ų�ʱ���� */
    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_XSMS_TIMER_MT_WAIT_DATA_IND,
                      TAF_XSMS_RcvDschDataIndTimeout_MtWaitCasDschDataInd ),


    /* �յ�ABORT��Ϣ */
    TAF_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_SMS_ABORT_IND,
                      TAF_XSMS_RcvMtLinkAbort )

};

/* XSMS MT_WAITING_WRITE_UIM_CNF״̬���¼������ */
TAF_ACT_STRU                            g_astTafXsmsMtWaitingWriteUimCnfActTbl[] =
{
    /* UIM��д��������� */
    TAF_ACT_TBL_ITEM( WUEPS_PID_USIM,
                      USIMM_UPDATEFILE_CNF,
                      TAF_XSMS_RcvWriteUimCnf_MtWaitWriteUimCnf ),

    /* UIM��д����ʱ���� */
    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_XSMS_TIMER_MT_WAIT_WRITE_UIM_CNF,
                      TAF_XSMS_RcvWriteUimCnfTimeout_MtWaitWriteUimCnf ),

};

/* XSMS MT_WAITING_READ_UIM_CNF״̬���¼������ */
TAF_ACT_STRU                            g_astTafXsmsMtWaitingReadUimCnfActTbl[] =
{
    /* UIM������������� */
    TAF_ACT_TBL_ITEM( WUEPS_PID_USIM,
                      USIMM_READFILE_CNF,
                      TAF_XSMS_RcvReadUimCnf_MtWaitReadUimCnf ),

    /* UIM��������ʱ���� */
    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_XSMS_TIMER_MT_WAIT_READ_UIM_CNF,
                      TAF_XSMS_RcvReadUimCnfTimeout_MtWaitReadUimCnf ),

};

/* XSMS MT_WAITING_AS_CNF״̬���¼������ */
TAF_ACT_STRU                            g_astTafXsmsMtWaitingAsCnfActTbl[] =
{
    /* ����CAS����L2 ACK���� */
    TAF_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_DSCH_DATA_CNF,
                      TAF_XSMS_RcvDschDataCnf_MtWaitCasDataCnf ),

    TAF_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_CSCH_DATA_CNF,
                      TAF_XSMS_RcvCschDataCnf_MtWaitCasDataCnf ),

    /* �ȴ�CAS����L2 ACK��ʱ���� */
    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_XSMS_TIMER_MT_WAIT_AS_CNF,
                      TAF_XSMS_RcvCasCnfTimeout_MtWaitCasDataCnf ),

    /* �ط���ʱ����ʱ */
    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_XSMS_TIMER_MT_RESEND,
                      TAF_XSMS_MtResend ),
    /* �յ�ABORT��Ϣ */
    TAF_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_SMS_ABORT_IND,
                      TAF_XSMS_RcvMtLinkAbort_MtWaitCasCnf)
};



/* XSMS MT_WAITING_END_CALL_CNF״̬���¼������ */
TAF_ACT_STRU                            g_astTafXsmsMtWaitingXccDisconnectActTbl[] =
{
    /* ����XCC���Ͳ���ŵ�������� */
    TAF_ACT_TBL_ITEM( UEPS_PID_XCC,
                      ID_XCC_CSMS_END_SMS_CALL_CNF,
                      TAF_XSMS_RcvEndCallCnf_MtWaitEndCallCnf ),

    /* �ȴ�XCC���Ͳ���ŵ������ʱ���� */
    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_XSMS_TIMER_MT_WAIT_CALL_END,
                      TAF_XSMS_RcvEndCallCnfTimeout_MtWaitEndCallCnf ),

};


/* Xsms MT״̬��״̬����� */
TAF_STA_STRU                            g_astTafXsmsMtStaTbl[] =
{
    /*****************����MT_IDLE_STATE״̬ת�Ʊ�**********************/
    TAF_STA_TBL_ITEM( TAF_XSMS_MT_IDLE_STATE,
                      g_astTafXsmsMtIdleActTbl ),

    /*****************����MT_WAITING_XCC_CALL_CONN**********************/
    TAF_STA_TBL_ITEM( TAF_XSMS_MT_WAITING_XCC_CALL_CONN_STATE,
                      g_astTafXsmsMtWaitXccConnActTbl ),

    /*****************����MT_WAITING_XCC_CNF״̬ת�Ʊ�**********************/
    TAF_STA_TBL_ITEM( TAF_XSMS_MT_WAITING_XCC_CALL_CNF_STATE,
                      g_astTafXsmsMtWaitXccAnsCallCnfActTbl ),

    /*****************����MT_WAITING_XCC_SO״̬ת�Ʊ�**********************/
    TAF_STA_TBL_ITEM( TAF_XSMS_MT_WAITING_XCC_SO_IND_STATE,
                      g_astTafXsmsMtWaitXccSoIndActTbl),

    /*****************����MT_WAITING_DSCH_DATA_IND״̬ת�Ʊ�****************/
    TAF_STA_TBL_ITEM( TAF_XSMS_MT_WAITING_DSCH_DATA_IND_STATE,
                      g_astTafXsmsMtWaitingDSCHDataIndActTbl ),

    /*****************����MT_WAITING_WRITE_UIM_CNF״̬ת�Ʊ�****************/
    TAF_STA_TBL_ITEM( TAF_XSMS_MT_WAITING_UIM_WRITE_CNF_STATE,
                      g_astTafXsmsMtWaitingWriteUimCnfActTbl ),

    /*****************����MT_WAITING_READ_UIM_CNF״̬ת�Ʊ�*****************/
    TAF_STA_TBL_ITEM( TAF_XSMS_MT_WAITING_UIM_READ_CNF_STATE,
                      g_astTafXsmsMtWaitingReadUimCnfActTbl ),

    /*****************����MT_WAITING_AS_CNF״̬ת�Ʊ�***********************/
    TAF_STA_TBL_ITEM( TAF_XSMS_MT_WAITING_AS_CNF_STATE,
                      g_astTafXsmsMtWaitingAsCnfActTbl ),

    /*****************����MT_WAITING_END_CALL_CNF״̬ת�Ʊ�***********************/
    TAF_STA_TBL_ITEM( TAF_XSMS_MT_WAITING_XCC_DISCONNECT_STATE,
                      g_astTafXsmsMtWaitingXccDisconnectActTbl ),
};
/*****************************************************************************
  3 ��������
*****************************************************************************/

VOS_UINT32 TAF_XSMS_GetMtFsmTblNum(VOS_VOID)
{
    return (sizeof(g_astTafXsmsMtStaTbl)/sizeof(TAF_STA_STRU));
}


#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



