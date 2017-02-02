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
#include "TafXpdsFsmPdeProc.h"
#include "TafXpdsFsmPdeProcComm.h"
#include "TafXpdsSndInternalMsg.h"
#include "TafXpdsFsmPdeProcTbl.h"


#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_TAF_XPDS_FSM_PDE_PROC_TBL_C

#if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_AGPS))

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/* XPDS l2 PDE״̬��״̬ȫ�ֱ��� */
TAF_FSM_DESC_STRU                       g_stTafXpdsL2PdeProcFsmDesc;

/* XPDS L2 PDE״̬�� STA_INIT ״̬�µ��¼������ */
TAF_ACT_STRU    g_astTafXpdsL2PdeProcInitActTbl[] =
{
    /* Added by x00314862 for CDMA XPDS Iteration 2 2015-8-26 begin */

    /* �յ�ID_TAF_XPDS_XPDS_PDE_PROC_START_REQ����Ĵ��� */
    TAF_ACT_TBL_ITEM( UEPS_PID_XPDS,
                      ID_TAF_XPDS_XPDS_PDE_PROC_START_REQ,
                      TAF_XPDS_RcvXpdsPdeProcStartReq_L2Pde_Init),

    /* Added by x00314862 for CDMA XPDS Iteration 2 2015-8-26 end */
};

/* XPDS L2 PDE״̬�� STA_MSA_WAIT_PDE_ASSIST_INFO ״̬�µ��¼������ */
TAF_ACT_STRU    g_astTafXpdsL2PdeProcStaMsaWaitPdeAssistInfoActTble[] =
{
    /* �յ�ID_TAF_XPDS_XPDS_RECEIVE_PDE_DATA_IND����Ĵ��� */
    TAF_ACT_TBL_ITEM( UEPS_PID_XPDS,
                      ID_TAF_XPDS_XPDS_FORWARD_PDE_DATA_IND,
                      TAF_XPDS_RcvXpdsForwardPdeDataInd_L2Pde_MsaWaitPdeAssistInfo),


    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_XPDS_WAIT_PDE_ASSIST_DATA_CNF,
                      TAF_XPDS_RcvTiXpdsForwardPdeDataIndExpired_L2Pde_MsaWaitPdeAssistInfo),

    TAF_ACT_TBL_ITEM( UEPS_PID_XPDS,
                      ID_TAF_XPDS_XPDS_INT_ABNORMAL_ABORT_AGPS_SESSION_IND,
                      TAF_XPDS_RcvXpdsAbnormalAbortSessionInd_L2Pde),
};

/* XPDS L2 PDE״̬�� STA_MSA_WAIT_GPS_PSEUDO_INFO ״̬�µ��¼������ */
TAF_ACT_STRU    g_astTafXpdsL2PdeProcStaMsaWaitGpsPseudoInfoActTbl[] =
{
    TAF_ACT_TBL_ITEM( UEPS_PID_XPDS,
                      ID_TAF_XPDS_XPDS_FORWARD_PDE_DATA_IND,
                      TAF_XPDS_RcvXpdsForwardPdeDataInd_L2Pde_MsaWaitGpsPseudoInfo),

    /* �յ�ID_AT_XPDS_PRM_INFO_RSP����Ĵ��� */
    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      ID_AT_XPDS_GPS_PRM_INFO_RSP,
                      TAF_XPDS_RcvAtGpsPrmInfoRsp_L2Pde_MsaWaitGpsPseudoInfo),

    /* Quality��ʱ����ʱ���� */
    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_XPDS_WAIT_RSP_PDE_PSEUDORANGE_REQ_QUALITY,
                      TAF_XPDS_RcvTiPrmInfoRspExpired_L2Pde_MsaWaitGpsPseudoInfo),

    /* ���ھ��Ȳ��Զ�ʱ�� */
    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_XPDS_WAIT_GPS_PRECISION_PSEUDORANGE_INFO,
                      TAF_XPDS_RcvTiWaitGpsPrecisionPseudoRangeExpired_L2Pde_MsaWaitGpsPseudoInfo),

    /* �Ⱥ�GPSα�ౣ����ʱ�� */
    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_XPDS_WAIT_GPS_PSEUDORANGE_CNF,
                      TAF_XPDS_RcvTiWaitGpsPseudoRangeCnfExpired_L2Pde_MsaWaitGpsPseudoInfo),

   TAF_ACT_TBL_ITEM( UEPS_PID_XPDS,
                      ID_TAF_XPDS_XPDS_INT_ABNORMAL_ABORT_AGPS_SESSION_IND,
                      TAF_XPDS_RcvXpdsAbnormalAbortSessionInd_L2Pde),
};

/* XPDS L2 PDE״̬�� STA_MSA_WAIT_PDE_LOC_RSP ״̬�µ��¼������ */
TAF_ACT_STRU    g_astTafXpdsL2PdeProcStaMsaWaitPdeLocRspActTbl[] =
{
    /* �յ�XX����Ĵ��� */
    TAF_ACT_TBL_ITEM( UEPS_PID_XPDS,
                      ID_TAF_XPDS_XPDS_FORWARD_PDE_DATA_IND,
                      TAF_XPDS_RcvXpdsForwardPdeDataInd_L2Pde_MsaWaitPdeLocRespInfo),

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_XPDS_WAIT_PDE_LOCATION_INFO_CNF,
                      TAF_XPDS_RcvTiXpdsForwardPdeDataIndExpired_L2Pde_MsaWaitPdeLocRespInfo),

    TAF_ACT_TBL_ITEM( UEPS_PID_XPDS,
                      ID_TAF_XPDS_XPDS_INT_ABNORMAL_ABORT_AGPS_SESSION_IND,
                      TAF_XPDS_RcvXpdsAbnormalAbortSessionInd_L2Pde),
};

/* XPDS L2 PDE״̬�� STA_MSB_WAIT_PDE_DATA ״̬�µ��¼������ */
TAF_ACT_STRU    g_astTafXpdsL2PdeProcStaMsbWaitPdeDataActTbl[] =
{
    TAF_ACT_TBL_ITEM( UEPS_PID_XPDS,
                      ID_TAF_XPDS_XPDS_FORWARD_PDE_DATA_IND,
                      TAF_XPDS_RcvXpdsForwardPdeDataInd_L2Pde_MsbWaitPdeData),

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_XPDS_WAIT_PDE_MSB_DATA,
                      TAF_XPDS_RcvTiWaitPdeMsbDataExpired_L2Pde_MsbWaitPdeData),

    TAF_ACT_TBL_ITEM( UEPS_PID_XPDS,
                      ID_TAF_XPDS_XPDS_INT_ABNORMAL_ABORT_AGPS_SESSION_IND,
                      TAF_XPDS_RcvXpdsAbnormalAbortSessionInd_L2Pde),
};


/* XPDS L2 PDE״̬��״̬����� */
TAF_STA_STRU    g_astTafXpdsL2PdeProcStaTbl[] =
{
    /*****************����MPC INIT״̬ת�Ʊ�**********************/
    TAF_STA_TBL_ITEM( TAF_XPDS_L2_PDE_PROC_STA_INIT,
                      g_astTafXpdsL2PdeProcInitActTbl ),

    /*****************����MPC WAIT RESP״̬ת�Ʊ�**********************/
    TAF_STA_TBL_ITEM( TAF_XPDS_L2_PDE_PROC_STA_MSA_WAIT_PDE_ASSIST_INFO,
                      g_astTafXpdsL2PdeProcStaMsaWaitPdeAssistInfoActTble ),

    TAF_STA_TBL_ITEM( TAF_XPDS_L2_PDE_PROC_STA_MSA_WAIT_GPS_PSEUDO_INFO,
                      g_astTafXpdsL2PdeProcStaMsaWaitGpsPseudoInfoActTbl ),

    TAF_STA_TBL_ITEM( TAF_XPDS_L2_PDE_PROC_STA_MSA_WAIT_PDE_LOC_RSP,
                      g_astTafXpdsL2PdeProcStaMsaWaitPdeLocRspActTbl ),

    TAF_STA_TBL_ITEM( TAF_XPDS_L2_PDE_PROC_STA_MSB_WAIT_PDE_DATA,
                      g_astTafXpdsL2PdeProcStaMsbWaitPdeDataActTbl ),
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
VOS_UINT32 TAF_XPDS_GetL2PdeProcStaTblSize( VOS_VOID )
{
    return (sizeof(g_astTafXpdsL2PdeProcStaTbl)/sizeof(TAF_STA_STRU));
}


TAF_STA_STRU* TAF_XPDS_GetL2PdeProcStaTblAddr( VOS_VOID )
{
    return (g_astTafXpdsL2PdeProcStaTbl);
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
TAF_FSM_DESC_STRU* TAF_XPDS_GetL2PdeProcFsmDescAddr( VOS_VOID )
{
    return (&g_stTafXpdsL2PdeProcFsmDesc);
}

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */




