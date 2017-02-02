/******************************************************************************

                  ��Ȩ���� (C), 2001-2014, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafXpdsFsmPdeProcTbl.c
  �� �� ��   : ����
  ��    ��   : x00314862
  ��������   : 2015��08��21��
  ��������   : 1X PDS״̬����״̬���ACT��
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��08��21��
    ��    ��   : x00314862
    �޸�����   : �����ļ�
******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "TafFsm.h"
#include "TafXpdsCtx.h"
#include "TafXpdsFsmCpPdeProc.h"
#include "TafXpdsFsmPdeProcComm.h"
#include "TafXpdsSndInternalMsg.h"
#include "TafXpdsFsmCpPdeProcTbl.h"
#include "cas_1x_control_main_nas_pif.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_TAF_XPDS_CP_FSM_PDE_PROC_TBL_C

#if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_AGPS))

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/* XPDS l2 PDE״̬��״̬ȫ�ֱ��� */
TAF_FSM_DESC_STRU                       g_stTafXpdsCpL2PdeProcFsmDesc;


/* added by L00902690, AGPS IT2 - begin */

/* XPDS L2 PDE״̬�� STA_INIT ״̬�µ��¼������ */
TAF_ACT_STRU    g_astTafXpdsCpL2PdeProcInitActTbl[] =
{
    /* Added by x00314862 for CDMA XPDS Iteration 2 2015-8-26 begin */

    /* �յ�ID_TAF_XPDS_XPDS_PDE_PROC_START_REQ����Ĵ��� */
    TAF_ACT_TBL_ITEM( UEPS_PID_XPDS,
                      ID_TAF_XPDS_XPDS_CP_PDE_PROC_START_REQ,
                      TAF_XPDS_RcvXpdsCpPdeProcStart_CpL2Pde_Init),

    /* Added by x00314862 for CDMA XPDS Iteration 2 2015-8-26 end */
};

/* XPDS l2 PDE wait for CAS CNF */
TAF_ACT_STRU                            g_astTafXpdsCpL2PdeProcStaMsbWaitCasCnfActTbl[] =
{
    TAF_ACT_TBL_ITEM( UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_DSCH_DATA_CNF,
                      TAF_XPDS_RcvXpdsCpMsbModeRecieveCasCnf),

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_XPDS_CP_L2_PDE_MSB_WAIT_CAS_CNF,
                      TAF_XPDS_RcvXpdsCpGeneralTimerTimeout),

    TAF_ACT_TBL_ITEM( UEPS_PID_XPDS,
                      ID_TAF_XPDS_XPDS_INT_ABNORMAL_ABORT_AGPS_SESSION_IND,
                      TAF_XPDS_RcvAtGpsStopReq_L2Pde)

};

/* XPDS l2 PDE wait for PDE response indicating both EPHI and ALM completely recieved */
TAF_ACT_STRU                            g_astTafXpdsCpL2PdeProcStaMsbWaitPdeRspActTbl[] =
{
    TAF_ACT_TBL_ITEM( UEPS_PID_XPDS,
                      ID_TAF_XPDS_XPDS_FORWARD_PDE_DATA_IND,
                      TAF_XPDS_RcvXpdsCpMsbModeRecievePdeResp),

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_XPDS_CP_L2_PDE_MSB_WAIT_ALM_EPHI_RESP,
                      TAF_XPDS_RcvXpdsCpGeneralTimerTimeout),

    TAF_ACT_TBL_ITEM( UEPS_PID_XPDS,
                      ID_TAF_XPDS_XPDS_INT_ABNORMAL_ABORT_AGPS_SESSION_IND,
                      TAF_XPDS_RcvAtGpsStopReq_L2Pde)

};

TAF_ACT_STRU                            g_astTafXpdsCpL2PdeProcStaMsaWaitPrmReqActTbl[] =
{
    TAF_ACT_TBL_ITEM( UEPS_PID_XPDS,
                      ID_TAF_XPDS_XPDS_FORWARD_PDE_DATA_IND,
                      TAF_XPDS_RcvXpdsCpMsaModeRecievePrmReq_NI),

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_XPDS_CP_L2_PDE_MSA_WAIT_PRM_REQ_AFTER_PPM,
                      TAF_XPDS_RcvXpdsCpGeneralTimerTimeout),

    TAF_ACT_TBL_ITEM( UEPS_PID_XPDS,
                      ID_TAF_XPDS_XPDS_INT_ABNORMAL_ABORT_AGPS_SESSION_IND,
                      TAF_XPDS_RcvAtGpsStopReq_L2Pde)

};

/* XPDS l2 PDE wait for GPS location response */
TAF_ACT_STRU                            g_astTafXpdsCpL2PdeProcStaMsbWaitGpsLocRspActTbl[] =
{
    /* �յ�XX����Ĵ��� */
    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      ID_AT_XPDS_GPS_POS_INFO_RSP,
                      TAF_XPDS_RcvXpdsCpMsbModeRecieveGpsLocResp),

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_XPDS_CP_L2_PDE_MSB_WAIT_GPS_LOC_RESP,
                      TAF_XPDS_RcvXpdsCpGeneralTimerTimeout),

    TAF_ACT_TBL_ITEM( UEPS_PID_XPDS,
                      ID_TAF_XPDS_XPDS_INT_ABNORMAL_ABORT_AGPS_SESSION_IND,
                      TAF_XPDS_RcvAtGpsStopReq_L2Pde)

};
/* XPDS l2 PDE wait at stop after GPS location response */
TAF_ACT_STRU                            g_astTafXpdsCpL2PdeProcStaMsbWaitGpsStopActTbl[] =
{

    TAF_ACT_TBL_ITEM( UEPS_PID_XPDS,
                      ID_TAF_XPDS_XPDS_INT_ABNORMAL_ABORT_AGPS_SESSION_IND,
                      TAF_XPDS_RcvAtGpsStopReq_L2Pde),

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_XPDS_CP_L2_PDE_MSB_WAIT_GPS_LOC_RESP,
                      TAF_XPDS_RcvXpdsCpGeneralTimerTimeout)

};


/* added by L00902690, AGPS IT2 - end */

/* added by A00903922, AGPS IT2 01-09-2015 : begin */
/* CP MSB XPDS l2 PDE wait for CAS CNF */
TAF_ACT_STRU    g_astTafXpdsCpL2PdeProcStaMsaWaitCasCnfAfterPpmActTbl[] =
{
    TAF_ACT_TBL_ITEM(UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_DSCH_DATA_CNF,
                      TAF_XPDS_RcvXpdsCpMsaModeRecieveCasCnf_AfterPPM),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                      TI_TAF_XPDS_CP_L2_PDE_MSA_WAIT_CAS_CNF_AFTER_PPM,
                      TAF_XPDS_RcvXpdsCpGeneralTimerTimeout),

    TAF_ACT_TBL_ITEM( UEPS_PID_XPDS,
                      ID_TAF_XPDS_XPDS_INT_ABNORMAL_ABORT_AGPS_SESSION_IND,
                      TAF_XPDS_RcvAtGpsStopReq_L2Pde)

};

TAF_ACT_STRU    g_astTafXpdsCpL2PdeProcStaMsaWaitCasCnfAfterPpmNIActTbl[] =
{
    TAF_ACT_TBL_ITEM(UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_DSCH_DATA_CNF,
                      TAF_XPDS_RcvXpdsCpMsaModeRecieveCasCnf_AfterPPM_NI),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                      TI_TAF_XPDS_CP_L2_PDE_MSA_WAIT_CAS_CNF_AFTER_PPM,
                      TAF_XPDS_RcvXpdsCpGeneralTimerTimeout),

    TAF_ACT_TBL_ITEM( UEPS_PID_XPDS,
                      ID_TAF_XPDS_XPDS_INT_ABNORMAL_ABORT_AGPS_SESSION_IND,
                      TAF_XPDS_RcvAtGpsStopReq_L2Pde),

};

TAF_ACT_STRU    g_astTafXpdsCpL2PdeProcStaMsaWaitCasCnfAfterAquiAssisNIActTbl[] =
{
    TAF_ACT_TBL_ITEM(UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_DSCH_DATA_CNF,
                      TAF_XPDS_RcvXpdsCpMsaModeRecieveCasCnf_AfterAquiAssis_NI),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                      TI_TAF_XPDS_CP_L2_PDE_MSA_WAIT_CAS_CNF_AFTER_AQUI_ASSI,
                      TAF_XPDS_RcvXpdsCpGeneralTimerTimeout),

    TAF_ACT_TBL_ITEM( UEPS_PID_XPDS,
                      ID_TAF_XPDS_XPDS_INT_ABNORMAL_ABORT_AGPS_SESSION_IND,
                      TAF_XPDS_RcvAtGpsStopReq_L2Pde),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                      TI_TAF_XPDS_CP_L2_PDE_MSA_WAIT_PRM_COMPLETE_NI_QUALITY,
                      TAF_XPDS_RcvXpdsCpGeneralTimerTimeout),


};

TAF_ACT_STRU    g_astTafXpdsCpL2PdeProcStaMsaWaitCasCnfAfterMsInfoActTbl[] =
{
    TAF_ACT_TBL_ITEM(UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_DSCH_DATA_CNF,
                      TAF_XPDS_RcvXpdsCpMsaModeRecieveCasCnf_AfterMsInfo),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                      TI_TAF_XPDS_CP_L2_PDE_MSA_WAIT_CAS_CNF_AFTER_PPM,
                      TAF_XPDS_RcvXpdsCpGeneralTimerTimeout),

    TAF_ACT_TBL_ITEM( UEPS_PID_XPDS,
                      ID_TAF_XPDS_XPDS_INT_ABNORMAL_ABORT_AGPS_SESSION_IND,
                      TAF_XPDS_RcvAtGpsStopReq_L2Pde),

};

TAF_ACT_STRU    g_astTafXpdsCpL2PdeProcStaMsaWaitCasCnfAfterLocRespActTbl[] =
{
    TAF_ACT_TBL_ITEM(UEPS_PID_1XCASM,
                      ID_CAS_CNAS_1X_DSCH_DATA_CNF,
                      TAF_XPDS_RcvXpdsCpMsaModeRecieveCasCnf_AfterReqLocRsp),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                      TI_TAF_XPDS_CP_L2_PDE_MSA_WAIT_CAS_CNF_AFTER_REQ_LOC_RSP,
                      TAF_XPDS_RcvXpdsCpGeneralTimerTimeout),

    TAF_ACT_TBL_ITEM(UEPS_PID_XPDS,
                      ID_TAF_XPDS_XPDS_INT_ABNORMAL_ABORT_AGPS_SESSION_IND,
                      TAF_XPDS_RcvAtGpsStopReq_L2Pde),

};

TAF_ACT_STRU    g_astTafXpdsCpL2PdeProcStaMsaWaitPpmCompleteNIActTbl[] =
{
    TAF_ACT_TBL_ITEM(UEPS_PID_XPDS,
                      ID_TAF_XPDS_XPDS_PPM_COMPLETE_NI,
                      TAF_XPDS_RcvXpdsCpMsaModePPMComplete_NI),

    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      ID_TAF_XPDS_XPDS_INT_ABNORMAL_ABORT_AGPS_SESSION_IND,
                      TAF_XPDS_RcvAtGpsStopReq_L2Pde),

};

TAF_ACT_STRU    g_astTafXpdsCpL2PdeProcStaMsaWaitProvPdeAssistInfoActTble[] =
{
    /* �յ�ID_TAF_XPDS_XPDS_RECEIVE_PDE_DATA_IND����Ĵ��� */
    TAF_ACT_TBL_ITEM( UEPS_PID_XPDS,
                      ID_TAF_XPDS_XPDS_FORWARD_PDE_DATA_IND,
                      TAF_XPDS_RcvXpdsForwardPdeDataInd_CpL2Pde_MsaWaitPdeAssistInfo),

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_XPDS_WAIT_PDE_ASSIST_DATA_CNF,
                      TAF_XPDS_RcvXpdsCpGeneralTimerTimeout),

    TAF_ACT_TBL_ITEM( UEPS_PID_XPDS,
                      ID_TAF_XPDS_XPDS_INT_ABNORMAL_ABORT_AGPS_SESSION_IND,
                      TAF_XPDS_RcvAtGpsStopReq_L2Pde),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                      TI_TAF_XPDS_CP_L2_PDE_MSA_WAIT_PRM_COMPLETE_NI_QUALITY,
                      TAF_XPDS_RcvXpdsCpGeneralTimerTimeout),

};

TAF_ACT_STRU    g_astTafXpdsCpL2PdeProcStaMsaWaitGpsPseudoInfoActTbl[] =
{
    /* �յ�ID_AT_XPDS_PRM_INFO_RSP����Ĵ��� */
    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      ID_AT_XPDS_GPS_PRM_INFO_RSP,
                      TAF_XPDS_RcvAtGpsPrmInfoRsp_CpL2Pde_MsaWaitGpsPseudoInfo),

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_XPDS_CP_L2_PDE_MSA_WAIT_PRM_COMPLETE_NI_QUALITY,
                      TAF_XPDS_RcvXpdsCpGeneralTimerTimeout),

    TAF_ACT_TBL_ITEM( UEPS_PID_XPDS,
                      ID_TAF_XPDS_XPDS_INT_ABNORMAL_ABORT_AGPS_SESSION_IND,
                      TAF_XPDS_RcvAtGpsStopReq_L2Pde),
};

TAF_ACT_STRU    g_astTafXpdsCpL2PdeProcStaMsaWaitPdeLocRspActTbl[] =
{
    /* �յ�XX����Ĵ��� */
    TAF_ACT_TBL_ITEM( UEPS_PID_XPDS,
                      ID_TAF_XPDS_XPDS_FORWARD_PDE_DATA_IND,
                      TAF_XPDS_RcvXpdsForwardPdeDataInd_CpL2Pde_MsaWaitPdeLocRespInfo),

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_XPDS_WAIT_PDE_LOCATION_INFO_CNF,
                      TAF_XPDS_RcvXpdsCpGeneralTimerTimeout),

    TAF_ACT_TBL_ITEM( UEPS_PID_XPDS,
                      ID_TAF_XPDS_XPDS_INT_ABNORMAL_ABORT_AGPS_SESSION_IND,
                      TAF_XPDS_RcvAtGpsStopReq_L2Pde),

};

/* added by A00903922, AGPS IT2 01-09-2015 : end */

/* XPDS CP L2 PDE״̬��״̬����� */
TAF_STA_STRU                            g_astTafXpdsCpL2PdeProcStaTbl[] =
{
    /*****************����MPC INIT״̬ת�Ʊ�**********************/
    TAF_STA_TBL_ITEM( TAF_XPDS_CP_L2_PDE_PROC_STA_INIT,
                      g_astTafXpdsCpL2PdeProcInitActTbl ),

    /* added by L00902690, AGPS IT2 - begin */

    TAF_STA_TBL_ITEM( TAF_XPDS_CP_L2_PDE_PROC_STA_MSB_WAIT_CAS_CNF,
                      g_astTafXpdsCpL2PdeProcStaMsbWaitCasCnfActTbl ),

    TAF_STA_TBL_ITEM( TAF_XPDS_CP_L2_PDE_PROC_STA_MSB_WAIT_PDE_EPHI_ALM_RESP,
                      g_astTafXpdsCpL2PdeProcStaMsbWaitPdeRspActTbl ),

    TAF_STA_TBL_ITEM( TAF_XPDS_CP_L2_PDE_PROC_STA_MSB_WAIT_GPS_LOC_RESP,
                      g_astTafXpdsCpL2PdeProcStaMsbWaitGpsLocRspActTbl ),

    TAF_STA_TBL_ITEM( TAF_XPDS_CP_L2_PDE_PROC_STA_MSB_WAIT_AT_GPS_STOP,
                      g_astTafXpdsCpL2PdeProcStaMsbWaitGpsStopActTbl ),


    /* added by L00902690, AGPS IT2 - end */

    /* added by A00903922, AGPS IT2 01-09-2015 : begin */

    TAF_STA_TBL_ITEM(TAF_XPDS_CP_L2_PDE_PROC_STA_MSA_WAIT_CAS_CNF_AFTER_PPM,
                     g_astTafXpdsCpL2PdeProcStaMsaWaitCasCnfAfterPpmActTbl),

    TAF_STA_TBL_ITEM(TAF_XPDS_CP_L2_PDE_PROC_STA_MSA_WAIT_PDE_ASSIST_INFO,
                     g_astTafXpdsCpL2PdeProcStaMsaWaitProvPdeAssistInfoActTble),

    TAF_STA_TBL_ITEM(TAF_XPDS_CP_L2_PDE_PROC_STA_MSA_WAIT_GPS_PSEUDO_INFO,
                     g_astTafXpdsCpL2PdeProcStaMsaWaitGpsPseudoInfoActTbl ),

    TAF_STA_TBL_ITEM(TAF_XPDS_CP_L2_PDE_PROC_STA_MSA_WAIT_CAS_CNF_AFTER_REQ_LOC_RSP,
                     g_astTafXpdsCpL2PdeProcStaMsaWaitCasCnfAfterLocRespActTbl ),

    TAF_STA_TBL_ITEM( TAF_XPDS_CP_L2_PDE_PROC_STA_MSA_WAIT_PDE_LOC_RSP,
                     g_astTafXpdsCpL2PdeProcStaMsaWaitPdeLocRspActTbl ),

    TAF_STA_TBL_ITEM(TAF_XPDS_CP_L2_PDE_PROC_STA_MSA_WAIT_CAS_CNF_AFTER_MS_INFO,
                     g_astTafXpdsCpL2PdeProcStaMsaWaitCasCnfAfterMsInfoActTbl),

    TAF_STA_TBL_ITEM(TAF_XPDS_CP_L2_PDE_PROC_STA_MSA_WAIT_CAS_CNF_AFTER_PPM_NI,
                     g_astTafXpdsCpL2PdeProcStaMsaWaitCasCnfAfterPpmNIActTbl),

    TAF_STA_TBL_ITEM(TAF_XPDS_CP_L2_PDE_PROC_STA_MSA_WAIT_CAS_CNF_AFTER_AQUI_ASSIS_NI,
                     g_astTafXpdsCpL2PdeProcStaMsaWaitCasCnfAfterAquiAssisNIActTbl),

    TAF_STA_TBL_ITEM(TAF_XPDS_CP_L2_PDE_PROC_STA_MSA_WAIT_PRM_REQ_NI,
                     g_astTafXpdsCpL2PdeProcStaMsaWaitPrmReqActTbl),

    TAF_STA_TBL_ITEM(TAF_XPDS_CP_L2_PDE_PROC_STA_MSA_WAIT_PPM_COMPLETE_NI,
                     g_astTafXpdsCpL2PdeProcStaMsaWaitPpmCompleteNIActTbl),



    /* added by A00903922, AGPS IT2 01-09-2015 : end */

};

/*****************************************************************************
  3 ��������
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : TAF_XPDS_GetL2PdeProcStaTblSize
 ��������  : ��ȡXPDS pde״̬���Ĵ�С
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32:״̬���Ĵ�С
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��21��
    ��    ��   : x00314862
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_XPDS_GetCpL2PdeProcStaTblSize( VOS_VOID )
{
    return (sizeof(g_astTafXpdsCpL2PdeProcStaTbl)/sizeof(TAF_STA_STRU));
}


TAF_STA_STRU* TAF_XPDS_GetCpL2PdeProcStaTblAddr( VOS_VOID )
{
    return (g_astTafXpdsCpL2PdeProcStaTbl);
}

/*****************************************************************************
 �� �� ��  : TAF_XPDS_GetL2PdeProcFsmDescAddr
 ��������  : ��ȡXPDS PDE״̬����������
 �������  : ��
 �������  : ��
 �� �� ֵ  : TAF_FSM_DESC_STRU:ָ��״̬����������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��21��
    ��    ��   : x00314862
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_FSM_DESC_STRU* TAF_XPDS_GetCpL2PdeProcFsmDescAddr( VOS_VOID )
{
    return (&g_stTafXpdsCpL2PdeProcFsmDesc);
}

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */




