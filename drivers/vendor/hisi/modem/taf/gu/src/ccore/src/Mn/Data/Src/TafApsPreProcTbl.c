


/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "TafFsm.h"
#include "AtMnInterface.h"
#include "TafApsFsmMainTbl.h"
#include "TafApsPreProcTbl.h"
#include "TafApsPreproc.h"
#include "TafApsTimerMgmt.h"
#include "TafApsDsFlowStats.h"
#include "ExtAppCmInterface.h"
#include "ApsNdInterface.h"
#include "Taf_ApsForSndcp.h"
#include "TafAgentInterface.h"
#include "TafApsGetPdpIdList.h"
#include "NasOmTrans.h"

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
#include "taf_aps_ppp_pif.h"
#include "ApsCdsInterface.h"
#include "xcc_aps_pif.h"
#include "xreg_aps_pif.h"
/* Added by y00314741 for CDMA 1X Iteration 9, 2015-2-5, begin */
#include "hsm_aps_pif.h"
/* Added by y00314741 for CDMA 1X Iteration 9, 2015-2-5, end */
/* Added by y00314741 for CDMA Iteration 15, 2015-5-14, begin */
#include "ehsm_aps_pif.h"
#include "taf_aps_dhcp_pif.h"
/* Added by y00314741 for CDMA Iteration 15, 2015-5-14, end */
#endif
#include "TafMmaInterface.h"
#include "TafApsSndInternalMsg.h"


#ifdef __cplusplus
#if __cplusplus
    extern "C" {
#endif
#endif

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_TAF_APS_PREPROCTAL_C

/******************************************************************************
   2 �ⲿ������������
******************************************************************************/

/******************************************************************************
   3 ˽�ж���
******************************************************************************/


/******************************************************************************
   4 ȫ�ֱ�������
*****************************************************************************/
/* Ԥ����״̬�� */
TAF_FSM_DESC_STRU                       g_stTafApsPreFsmDesc;

/* ����״̬���������Ϣ ������ */
TAF_ACT_STRU        g_astTafApsPreProcessActTbl[]   =
{
    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_APS_DSFLOW_REPORT,
                      TAF_APS_RcvTiDsFlowReportExpired_PreProc),

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_APS_DSFLOW_WRITE_NV,
                      TAF_APS_RcvTiDsFlowWriteNvExpired_PreProc),



    /* +CGDCONT */
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_MSG_TAF_PS_SET_PRIM_PDP_CONTEXT_INFO_REQ,
                      TAF_APS_RcvAtSetPrimPdpCtxInfoReq_PreProc),
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_MSG_TAF_PS_GET_PRIM_PDP_CONTEXT_INFO_REQ,
                      TAF_APS_RcvAtGetPrimPdpCtxInfoReq_PreProc),

    /* +CGDSCONT */
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_MSG_TAF_PS_SET_SEC_PDP_CONTEXT_INFO_REQ,
                      TAF_APS_RcvAtSetSecPdpCtxInfoReq_PreProc),
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_MSG_TAF_PS_GET_SEC_PDP_CONTEXT_INFO_REQ,
                      TAF_APS_RcvAtGetSecPdpCtxInfoReq_PreProc),

    /* +CGTFT */
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_MSG_TAF_PS_SET_TFT_INFO_REQ,
                      TAF_APS_RcvAtSetTftInfoReq_PreProc),
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_MSG_TAF_PS_GET_TFT_INFO_REQ,
                      TAF_APS_RcvAtGetTftInfoReq_PreProc),

    /* +CGQREQ: ��֧�� */
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_MSG_TAF_PS_SET_GPRS_QOS_INFO_REQ,
                      VOS_NULL_PTR),
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_MSG_TAF_PS_GET_GPRS_QOS_INFO_REQ,
                      VOS_NULL_PTR),

    /* +CGQMIN: ��֧�� */
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_MSG_TAF_PS_SET_GPRS_QOS_MIN_INFO_REQ,
                      VOS_NULL_PTR),
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_MSG_TAF_PS_GET_GPRS_QOS_MIN_INFO_REQ,
                      VOS_NULL_PTR),

    /* +CGEQREQ */
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_MSG_TAF_PS_SET_UMTS_QOS_INFO_REQ,
                      TAF_APS_RcvAtSetUmtsQosInfoReq_PreProc),
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_MSG_TAF_PS_GET_UMTS_QOS_INFO_REQ,
                      TAF_APS_RcvAtGetUmtsQosInfoReq_PreProc),

    /* +CGEQMIN */
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_MSG_TAF_PS_SET_UMTS_QOS_MIN_INFO_REQ,
                      TAF_APS_RcvAtSetUmtsQosMinInfoReq_PreProc),
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_MSG_TAF_PS_GET_UMTS_QOS_MIN_INFO_REQ,
                      TAF_APS_RcvAtGetUmtsQosMinInfoReq_PreProc),

    /* +CGEQNEG */
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_MSG_TAF_PS_GET_DYNAMIC_UMTS_QOS_INFO_REQ,
                      TAF_APS_RcvAtGetDynamicUmtsQosInfoReq_PreProc),

    /* +CGPADDR */
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_MSG_TAF_PS_GET_PDP_IP_ADDR_INFO_REQ,
                      TAF_APS_RcvAtGetPdpIpAddrInfoReq_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_MSG_TAF_PS_GET_PDPCONT_INFO_REQ,
                      TAF_APS_RcvAtGetPdpInfoReq_PreProc),

    /* +CGAUTO */
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_MSG_TAF_PS_SET_ANSWER_MODE_INFO_REQ,
                      TAF_APS_RcvAtSetAnsModeInfoReq_PreProc),
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_MSG_TAF_PS_GET_ANSWER_MODE_INFO_REQ,
                      TAF_APS_RcvAtGetAnsModeInfoReq_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_MSG_TAF_PS_GET_PDP_CONTEXT_STATE_REQ,
                      TAF_APS_RcvAtGetPdpContextStateReq_PreProc),


#if ( FEATURE_ON == FEATURE_LTE )
    /* +CGCONTRDP */
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_MSG_TAF_PS_GET_DYNAMIC_PRIM_PDP_CONTEXT_INFO_REQ,
                      TAF_APS_RcvAtGetDynamicPrimPdpCtxInfoReq_PreProc),

    /* +CGSCONTRDP */
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_MSG_TAF_PS_GET_DYNAMIC_SEC_PDP_CONTEXT_INFO_REQ,
                      TAF_APS_RcvAtGetDynamicSecPdpCtxInfoReq_PreProc),

    /* +CGTFTRDP */
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_MSG_TAF_PS_GET_DYNAMIC_TFT_INFO_REQ,
                      TAF_APS_RcvAtGetDynamicTftInfoReq_PreProc),

    /* +CGEQOS */
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_MSG_TAF_PS_SET_EPS_QOS_INFO_REQ,
                      TAF_APS_RcvAtSetEpsQosInfoReq_PreProc),
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_MSG_TAF_PS_GET_EPS_QOS_INFO_REQ,
                      TAF_APS_RcvAtGetEpsQosInfoReq_PreProc),

    /* +CGEQOSRDP */
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_MSG_TAF_PS_GET_DYNAMIC_EPS_QOS_INFO_REQ,
                      TAF_APS_RcvAtGetDynamicEpsQosInfoReq_PreProc),

      /* ^LTECS*/
     TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_MSG_TAF_PS_GET_LTE_CS_REQ,
                      TAF_APS_RcvAtGetLteCsInfoReq_PreProc),

    /* +CEMODE*/
     TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_MSG_TAF_PS_GET_CEMODE_REQ,
                      TAF_APS_RcvAtGetCemodeInfoReq_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_MSG_TAF_PS_SET_PDPROFMOD_INFO_REQ,
                      TAF_APS_RcvAtSetPdprofInfoReq_PreProc),

#endif

    /* ^NDISCONN/^NDISDUP */

    /* ^DSFLOWQRY */
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_MSG_TAF_PS_GET_DSFLOW_INFO_REQ,
                      TAF_APS_RcvAtGetDsFlowInfoReq_PreProc),

    /* ^DSFLOWCLR */
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_MSG_TAF_PS_CLEAR_DSFLOW_REQ,
                      TAF_APS_RcvAtClearDsFlowReq_PreProc),

    /* ^DSFLOWRPT */
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_MSG_TAF_PS_CONFIG_DSFLOW_RPT_REQ,
                      TAF_APS_RcvAtConfigDsFlowRptReq_PreProc),

    /* ^APDSFLOWRPTCFG */
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_MSG_TAF_PS_SET_APDSFLOW_RPT_CFG_REQ,
                      TAF_APS_RcvSetApDsFlowRptCfgReq_PreProc),
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_MSG_TAF_PS_GET_APDSFLOW_RPT_CFG_REQ,
                      TAF_APS_RcvGetApDsFlowRptCfgReq_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_MSG_TAF_PS_SET_DSFLOW_NV_WRITE_CFG_REQ,
                      TAF_APS_RcvSetDsFlowNvWriteCfgReq_PreProc),
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_MSG_TAF_PS_GET_DSFLOW_NV_WRITE_CFG_REQ,
                      TAF_APS_RcvGetDsFlowNvWriteCfgReq_PreProc),

    /* ^CGAUTH */
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_MSG_TAF_PS_SET_PDP_AUTH_INFO_REQ,
                      TAF_APS_RcvAtSetPdpAuthInfoReq_PreProc),
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_MSG_TAF_PS_GET_PDP_AUTH_INFO_REQ,
                      TAF_APS_RcvAtGetPdpAuthInfoReq_PreProc),

    /* ^CGDNS */
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_MSG_TAF_PS_SET_PDP_DNS_INFO_REQ,
                      TAF_APS_RcvAtSetPdpDnsInfoReq_PreProc),
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_MSG_TAF_PS_GET_PDP_DNS_INFO_REQ,
                      TAF_APS_RcvAtGetPdpDnsInfoReq_PreProc),

    /* ^TRIG */
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_MSG_TAF_PS_TRIG_GPRS_DATA_REQ,
                      TAF_APS_RcvAtTrigGprsDataReq_PreProc),


    /* ^DWINS */
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_MSG_TAF_PS_CONFIG_NBNS_FUNCTION_REQ,
                      TAF_APS_RcvAtConfigNbnsFunctionReq_PreProc),


    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_MSG_TAF_PS_GET_CID_SDF_REQ,
                      TAF_APS_RcvPsGetCidSdfReq_PreProc),



#if ( FEATURE_ON == FEATURE_LTE )
    /* ^NDISCONN | ^NDISSTATQRY */
#endif

    /* ^AUTHDATA */
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_MSG_TAF_PS_SET_AUTHDATA_INFO_REQ,
                      TAF_APS_RcvAtSetAuthDataInfoReq_PreProc),
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_MSG_TAF_PS_GET_AUTHDATA_INFO_REQ,
                      TAF_APS_RcvAtGetAuthDataInfoReq_PreProc),

    /* D | PPP */

#if ( FEATURE_ON == FEATURE_LTE )
    /* +CGDCONT */
    TAF_ACT_TBL_ITEM( MSP_L4_L4A_PID,
                      ID_L4A_APS_SET_CGDCONT_CNF,
                      TAF_APS_RcvL4aSetCgdcontCnf_PreProc),

    /* +CGDSCONT */
    TAF_ACT_TBL_ITEM( MSP_L4_L4A_PID,
                      ID_L4A_APS_SET_CGDSCONT_CNF,
                      TAF_APS_RcvL4aSetCgdscontCnf_PreProc),

    /* +CGTFT */
    TAF_ACT_TBL_ITEM( MSP_L4_L4A_PID,
                      ID_L4A_APS_SET_CGTFT_CNF,
                      TAF_APS_RcvL4aSetCgtftCnf_PreProc),

    /* +CGAUTO */
    TAF_ACT_TBL_ITEM( MSP_L4_L4A_PID,
                      ID_L4A_APS_SET_CGAUTO_CNF,
                      TAF_APS_RcvL4aSetCgautoCnf_PreProc),

    /* +CGANS */
    TAF_ACT_TBL_ITEM( MSP_L4_L4A_PID,
                      ID_L4A_APS_SET_CGANS_CNF,
                      TAF_APS_RcvL4aSetCgansCnf_PreProc),

    /* +CGEQOS */
    TAF_ACT_TBL_ITEM( MSP_L4_L4A_PID,
                      ID_L4A_APS_SET_CGEQOS_CNF,
                      TAF_APS_RcvL4aSetCgeqosCnf_PreProc),

    /* ^AUTHDATA */
    TAF_ACT_TBL_ITEM( MSP_L4_L4A_PID,
                      ID_L4A_APS_SET_AUTHDATA_CNF,
                      TAF_APS_RcvL4aSetAuthdataCnf_PreProc),

    /* +CGCONTRDP */
    TAF_ACT_TBL_ITEM( MSP_L4_L4A_PID,
                      ID_L4A_APS_SET_CGCONTRDP_CNF,
                      TAF_APS_RcvL4aSetCgcontrdpCnf_PreProc),

    /* +CGSCONTRDP */
    TAF_ACT_TBL_ITEM( MSP_L4_L4A_PID,
                      ID_L4A_APS_SET_CGSCONTRDP_CNF,
                      TAF_APS_RcvL4aSetCgscontrdpCnf_PreProc),

    /* +CGTFTRDP */
    TAF_ACT_TBL_ITEM( MSP_L4_L4A_PID,
                      ID_L4A_APS_SET_CGTFTRDP_CNF,
                      TAF_APS_RcvL4aSetCgtftrdpCnf_PreProc),

    /* +CGEQOSRDP */
    TAF_ACT_TBL_ITEM( MSP_L4_L4A_PID,
                      ID_L4A_APS_SET_CGEQOSRDP_CNF,
                      TAF_APS_RcvL4aSetCgeqosrdpCnf_PreProc),
     /*^LTECS*/
      TAF_ACT_TBL_ITEM( MSP_L4_L4A_PID,
                      ID_L4A_APS_GET_LTE_CS_CNF,
                      TAF_APS_RcvL4aGetLteCsCnf_PreProc),

    /*+CEMODE*/
      TAF_ACT_TBL_ITEM( MSP_L4_L4A_PID,
                      ID_L4A_APS_GET_CEMODE_CNF,
                      TAF_APS_RcvL4aGetCemodeCnf_PreProc),

    TAF_ACT_TBL_ITEM( MSP_L4_L4A_PID,
                      ID_L4A_APS_SET_PDPROFMOD_CNF,
                      TAF_APS_RcvL4aSetPdprofInfoCnf_PreProc),


    /* L4A��ʱ����ʱ���� */
    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_APS_WAIT_SET_CGDCONT_CNF,
                      TAF_APS_RcvTiSetCgdcontCnfExpired_PreProc),
    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_APS_WAIT_SET_CGDSCONT_CNF,
                      TAF_APS_RcvTiSetCgdscontCnfExpired_PreProc),
    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_APS_WAIT_SET_CGTFT_CNF,
                      TAF_APS_RcvTiSetCgtftCnfExpired_PreProc),
    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_APS_WAIT_SET_CGAUTO_CNF,
                      TAF_APS_RcvTiSetCgautoCnfExpired_PreProc),
    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_APS_WAIT_SET_CGEQOS_CNF,
                      TAF_APS_RcvTiSetCgeqosCnfExpired_PreProc),
    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_APS_WAIT_SET_AUTHDATA_CNF,
                      TAF_APS_RcvTiSetAuthdataCnfExpired_PreProc),


    /*+CEMODE*/
    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_APS_WAIT_GET_CEMODE_CNF,
                      TAF_APS_RcvTiGetCemodeCnfExpired_PreProc),
    /*^LTECS*/
    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_APS_WAIT_GET_LTE_CS_CNF,
                      TAF_APS_RcvTiGetLtecsCnfExpired_PreProc),

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_APS_WAIT_SET_PDPROF_CNF,
                      TAF_APS_RcvTiSetPdprofInfoExpired_PreProc),


    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_APS_WAIT_SET_CGCONTRDP_CNF,
                      TAF_APS_RcvTiSetCgcontrdpCnfExpired_PreProc),
    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_APS_WAIT_SET_CGSCONTRDP_CNF,
                      TAF_APS_RcvTiSetCgscontrdpCnfExpired_PreProc),
    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_APS_WAIT_SET_CGTFTRDP_CNF,
                      TAF_APS_RcvTiSetCgtftrdpCnfExpired_PreProc),
    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_APS_WAIT_SET_CGEQOSRDP_CNF,
                      TAF_APS_RcvTiSetCgeqosrdpCnfExpired_PreProc),

#endif


    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_APS_LIMIT_PDP_ACT,
                      TAF_APS_RcvTiApsLimitPdpActExpired_PreProc),

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_APS_MS_ACTIVATING,
                      TAF_APS_RcvTiApsMsActvaingExpired_PreProc),

    TAF_ACT_TBL_ITEM( ACPU_PID_TAFAGENT,
                      ID_TAFAGENT_APS_FIND_CID_FOR_DIAL_REQ,
                      TAF_APS_RcvAtFindCidForDialReq_PreProc),

    TAF_ACT_TBL_ITEM( ACPU_PID_TAFAGENT,
                      ID_TAFAGENT_APS_GET_CID_PARA_REQ,
                      TAF_APS_RcvAtGetCidParaReq_PreProc),

    TAF_ACT_TBL_ITEM( ACPU_PID_TAFAGENT,
                      ID_TAFAGENT_APS_SET_CID_PARA_REQ,
                      TAF_APS_RcvAtSetCidParaReq_PreProc),

    TAF_ACT_TBL_ITEM( ACPU_PID_TAFAGENT,
                      ID_TAFAGENT_APS_SET_CID_QOS_PARA_REQ,
                      TAF_APS_RcvAtSetCidQosParaReq_PreProc),

    TAF_ACT_TBL_ITEM( ACPU_PID_TAFAGENT,
                      ID_TAFAGENT_APS_GET_CID_QOS_PARA_REQ,
                      TAF_APS_RcvAtGetCidQosParaReq_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ,
                      TAF_APS_RcvAtSetPdpContextStateReq_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_MSG_TAF_PS_CALL_MODIFY_REQ,
                      TAF_APS_RcvAtPsCallModifyReq_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_MSG_TAF_PS_CALL_ORIG_REQ,
                      TAF_APS_RcvAtPsCallOrigReq_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_MSG_TAF_PS_GET_D_GPRS_ACTIVE_TYPE_REQ,
                      TAF_APS_RcvAtGetGprsActiveTypeReq_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ,
                      TAF_APS_RcvAtPppDialOrigReq_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_MSG_TAF_PS_CALL_END_REQ,
                      TAF_APS_RcvAtPsCallEndReq_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_MSG_TAF_PS_CALL_ANSWER_REQ,
                      TAF_APS_RcvAtPsCallAnswerReq_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_MSG_TAF_PS_CALL_HANGUP_REQ,
                      TAF_APS_RcvAtPsCallHangupReq_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_SM,
                      ID_SMREG_PDP_ACTIVATE_CNF,
                      TAF_APS_RcvSmRegPdpActCnf_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_SM,
                      ID_SMREG_PDP_ACTIVATE_REJ,
                      TAF_APS_RcvSmRegPdpActRej_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_SM,
                      ID_SMREG_PDP_ACTIVATE_IND,
                      TAF_APS_RcvSmRegPdpActInd_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_SM,
                      ID_SMREG_PDP_MODIFY_CNF,
                      TAF_APS_RcvSmRegPdpModifyCnf_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_SM,
                      ID_SMREG_PDP_MODIFY_REJ,
                      TAF_APS_RcvSmRegPdpModifyRej_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_SM,
                      ID_SMREG_PDP_MODIFY_IND,
                      TAF_APS_RcvSmRegPdpModifyInd_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_SM,
                      ID_SMREG_PDP_DEACTIVATE_IND,
                      TAF_APS_RcvSmRegPdpDeactivInd_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_SM,
                      ID_SMREG_PDP_DEACTIVATE_CNF,
                      TAF_APS_RcvSmRegPdpDeactivCnf_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_SM,
                      ID_SMREG_PDP_ACTIVATE_SEC_CNF,
                      TAF_APS_RcvSmRegPdpActSecCnf_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_SM,
                      ID_SMREG_PDP_ACTIVATE_SEC_REJ,
                      TAF_APS_RcvSmRegPdpActSecRej_PreProc),

#if (FEATURE_ON == FEATURE_LTE)
    TAF_ACT_TBL_ITEM( MSP_L4_L4A_PID,
                      ID_L4A_APS_PDP_ACTIVATE_CNF,
                      TAF_APS_RcvL4aApsPdpActivateCnf_PreProc),

    TAF_ACT_TBL_ITEM( MSP_L4_L4A_PID,
                      ID_L4A_APS_PDP_ACTIVATE_REJ,
                      TAF_APS_RcvL4aApsPdpActivateRej_PreProc),

    TAF_ACT_TBL_ITEM( MSP_L4_L4A_PID,
                      ID_L4A_APS_PDP_ACTIVATE_IND,
                      TAF_APS_RcvL4aApsPdpActivateInd_PreProc),

    TAF_ACT_TBL_ITEM( MSP_L4_L4A_PID,
                      ID_L4A_APS_PDP_MODIFY_CNF,
                      TAF_APS_RcvL4aApsPdpModifyCnf_PreProc),

    TAF_ACT_TBL_ITEM( MSP_L4_L4A_PID,
                      ID_L4A_APS_PDP_MODIFY_REJ,
                      TAF_APS_RcvL4aApsPdpModifyRej_PreProc),

    TAF_ACT_TBL_ITEM( MSP_L4_L4A_PID,
                      ID_L4A_APS_PDP_MODIFY_IND,
                      TAF_APS_RcvL4aApsPdpModifyInd_PreProc),

    TAF_ACT_TBL_ITEM( MSP_L4_L4A_PID,
                      ID_L4A_APS_PDP_DEACTIVATE_CNF,
                      TAF_APS_RcvL4aApsPdpDeactivateCnf_PreProc),

    TAF_ACT_TBL_ITEM( MSP_L4_L4A_PID,
                      ID_L4A_APS_PDP_DEACTIVATE_REJ,
                      TAF_APS_RcvL4aApsPdpDeactivateRej_PreProc),

    TAF_ACT_TBL_ITEM( MSP_L4_L4A_PID,
                      ID_L4A_APS_PDP_DEACTIVATE_IND,
                      TAF_APS_RcvL4aApsPdpDeactivateInd_PreProc),

    TAF_ACT_TBL_ITEM( MSP_L4_L4A_PID,
                      ID_L4A_APS_PDP_SETUP_IND,
                      TAF_APS_RcvL4aApsPdpSetupInd_PreProc),

    TAF_ACT_TBL_ITEM( MSP_L4_L4A_PID,
                      ID_L4A_APS_SET_NDISCONN_CNF,
                      TAF_APS_RcvL4aSenNdisconnCnf_PreProc),

    TAF_ACT_TBL_ITEM( MSP_L4_L4A_PID,
                      ID_L4A_APS_PPP_DIAL_CNF,
                      TAF_APS_RcvL4aPppDialCnf_PreProc),

    TAF_ACT_TBL_ITEM( MSP_L4_L4A_PID,
                      ID_L4A_APS_PS_CALL_END_CNF,
                      TAF_APS_RcvL4aPsCallEndCnf_PreProc),

    TAF_ACT_TBL_ITEM( PS_PID_ESM,
                      ID_ESM_SM_EPS_BEARER_INFO_IND,
                      TAF_APS_RcvEsmEpsBearInfoInd_PreProc),
#if (FEATURE_ON == FEATURE_IMS)
    TAF_ACT_TBL_ITEM( PS_PID_ESM,
                      ID_ESM_APS_ESM_NOTIFICATION_IND,
                      TAF_APS_RcvEsmNotificationInd_PreProc),

#endif
#endif

    TAF_ACT_TBL_ITEM( UEPS_PID_SN,
                      APS_SN_ACT_RSP_MSG_TYPE,
                      TAF_APS_RcvSndcpActivateRsp_PreProc),

    TAF_ACT_TBL_ITEM( UEPS_PID_SN,
                      APS_SN_MDF_RSP_MSG_TYPE,
                      TAF_APS_RcvSndcpModifyRsp_PreProc),

    TAF_ACT_TBL_ITEM( UEPS_PID_SN,
                      APS_SN_DEACT_RSP_MSG_TYPE,
                      TAF_APS_RcvSndcpDeactRsp_PreProc),


#if (FEATURE_ON == FEATURE_IPV6)
    TAF_ACT_TBL_ITEM( UEPS_PID_NDCLIENT,
                      ID_NDCLIENT_APS_PARA_INFO_NOTIFY,
                      TAF_APS_RcvNdIpv6ParaInfoNotifyInd_PreProc),
#endif

    /* ^DNSQUERY */
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_MSG_TAF_PS_GET_NEGOTIATION_DNS_REQ,
                      TAF_APS_RcvAtSetDnsQueryReq_PreProc),

    /* OM��Ϣ���������ϱ� */
    TAF_ACT_TBL_ITEM( MSP_PID_DIAG_APP_AGENT,
                      ID_NAS_OM_SET_DSFLOW_RPT_REQ,
                      TAF_APS_RcvOmSetDsflowRptReq_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      ID_MMC_APS_SERVICE_STATUS_IND,
                      TAF_APS_RcvMmcServiceStatusInd_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_MSG_TAF_PS_SET_IMS_PDP_CFG_REQ,
                      TAF_APS_RcvSetImsPdpCfgReq_PreProc),

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_MSG_TAF_PS_SET_CQOS_PRI_REQ,
                      TAF_APS_SetCqosPriReq_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_MSG_TAF_PS_CALL_ENTER_DORMANT_IND,
                      TAF_APS_RcvPsCallEnterDormantInd_PreProc),

    TAF_ACT_TBL_ITEM( UEPS_PID_XCC,
                      ID_XCC_APS_DATA_CALL_SUSPEND_IND,
                      TAF_APS_RcvXccDataCallSuspendInd_PreProc),

    TAF_ACT_TBL_ITEM( UEPS_PID_XCC,
                      ID_XCC_APS_DATA_CALL_RESUME_IND,
                      TAF_APS_RcvXccDataCallResumeInd_PreProc),

    TAF_ACT_TBL_ITEM( UEPS_PID_XCC,
                      ID_XCC_APS_ORIG_DATA_CALL_CNF,
                      TAF_APS_RcvXccOrigDataCallCnf_PreProc),

    TAF_ACT_TBL_ITEM( UEPS_PID_XCC,
                      ID_XCC_APS_HANGUP_DATA_CALL_CNF,
                      TAF_APS_RcvXccHangupDataCallCnf_PreProc),

    TAF_ACT_TBL_ITEM( UEPS_PID_XCC,
                      ID_XCC_APS_DATA_CALL_DISC_IND,
                      TAF_APS_RcvXccDataCallDiscInd_PreProc),

    TAF_ACT_TBL_ITEM( UEPS_PID_XCC,
                      ID_XCC_APS_INCOMING_CALL_IND,
                      TAF_APS_RcvXccIncomingCallInd_PreProc),

    TAF_ACT_TBL_ITEM( UEPS_PID_XCC,
                      ID_XCC_APS_DATA_CALL_CONN_IND,
                      TAF_APS_RcvXccDataCallConnInd_PreProc),

    TAF_ACT_TBL_ITEM( UEPS_PID_XCC,
                      ID_XCC_APS_DATA_SERVICE_CONNECT_IND,
                      TAF_APS_RcvXccDataServiceConnInd_PreProc),

    TAF_ACT_TBL_ITEM( UEPS_PID_XCC,
                      ID_XCC_APS_ANSWER_DATA_CALL_CNF,
                      TAF_APS_RcvXccAnswerDataCallCnf_PreProc),

    TAF_ACT_TBL_ITEM( UEPS_PID_XCC,
                      ID_XCC_APS_SO_CTRL_MSG_IND,
                      TAF_APS_RcvXccSoCtrlMsg_PreProc),

    TAF_ACT_TBL_ITEM( MSPS_PID_PPPC,
                      ID_PPP_APS_ACT_CNF,
                      TAF_APS_RcvPppActCnf_PreProc),

    TAF_ACT_TBL_ITEM( MSPS_PID_PPPC,
                      ID_PPP_APS_DEACT_CNF,
                      TAF_APS_RcvPppDeactCnf_PreProc),

    TAF_ACT_TBL_ITEM( MSPS_PID_PPPC,
                      ID_PPP_APS_DEACT_NTF,
                      TAF_APS_RcvPppDeactNtf_PreProc),

/* Added by y00314741 for CDMA Iteration 11, 2015-3-27, begin */
    TAF_ACT_TBL_ITEM( MSPS_PID_PPPC,
                      ID_PPP_APS_MODIFY_IND,
                      TAF_APS_RcvPppModifyInd_PreProc),
/* Added by y00314741 for CDMA Iteration 11, 2015-3-27, end */

    TAF_ACT_TBL_ITEM( UEPS_PID_CDS,
                      ID_CDS_APS_CDATA_SERVICE_IND,
                      TAF_APS_RcvCdsServiceInd_PreProc),

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_APS_CDATA_EPZID_HAT,
                      TAF_APS_RcvTiHatExpired_PreProc),

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_APS_CDATA_EPZID_HT,
                      TAF_APS_RcvTiHtExpired_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_MMA,
                      ID_MMA_APS_EPDSZID_INFO_IND,
                      TAF_APS_RcvMmaEpdszidInfo_PreProc),

    TAF_ACT_TBL_ITEM( UEPS_PID_XREG,
                      ID_XREG_APS_REG_BEGIN_IND,
                      TAF_APS_RcvXregRegBeginInd_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_MSG_TAF_PS_INTER_EPDSZID_REORIG_REQ,
                      TAF_APS_RcvPsInterEpdszidReOrig_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_MSG_TAF_PS_INTER_HT_EXPIRED_REQ,
                      TAF_APS_RcvTiHtExpired_PreProc),

    /* Added by y00314741 for CDMA 1X Iteration 7, 2015-1-4, begin */
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_MSG_TAF_PS_HAI_CHANGE_IND,
                      TAF_APS_RcvPsHaiChangeInd_PreProc),
    /* Added by y00314741 for CDMA 1X Iteration 7, 2015-1-4, end */

    TAF_ACT_TBL_ITEM( UEPS_PID_XCC,
                      ID_XCC_APS_UPDATE_DATA_CALL_INFO_IND,
                      TAF_APS_RcvXccUpdateDataCallInfoInd_PreProc),
    /* Added by y00314741 for CDMA 1X Iteration 9, 2015-2-5, begin */
    TAF_ACT_TBL_ITEM( UEPS_PID_HSM,
                      ID_HSM_APS_ORIG_CNF,
                      TAF_APS_RcvHsmOrigCnf_PreProc),

    TAF_ACT_TBL_ITEM( UEPS_PID_HSM,
                      ID_HSM_APS_CONNECT_IND,
                      TAF_APS_RcvHsmConnectInd_PreProc),

    TAF_ACT_TBL_ITEM( UEPS_PID_HSM,
                      ID_HSM_APS_DISC_CNF,
                      TAF_APS_RcvHsmDiscCnf_PreProc),

    TAF_ACT_TBL_ITEM( UEPS_PID_HSM,
                      ID_HSM_APS_DISC_IND,
                      TAF_APS_RcvHsmDiscInd_PreProc),

    TAF_ACT_TBL_ITEM( UEPS_PID_HSM,
                      ID_HSM_APS_LOC_CHANGED_IND,
                      TAF_APS_RcvHsmLocChangedInd_PreProc),

    TAF_ACT_TBL_ITEM( UEPS_PID_HSM,
                      ID_HSM_APS_1X_TO_HRPD_HANDOFF_CNF,
                      TAF_APS_RcvHsm1XToHrpdHandOff_PreProc),


    /* Added by y00314741 for CDMA 1X Iteration 9, 2015-2-5, end */

    /* Modified by y00314741 for  CDMA Iteration 17, 2015-7-17, begin */
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_MSG_TAF_PS_SET_CTA_INFO_REQ,
                      TAF_APS_RcvPsSet1xPktDataInactivityTimeLenReq_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_MSG_TAF_PS_GET_CTA_INFO_REQ,
                      TAF_APS_RcvPsGet1xPktDataInactivityTimerLenReq_PreProc),
    /* Modified by y00314741 for  CDMA Iteration 17, 2015-7-17, end */

    TAF_ACT_TBL_ITEM( WUEPS_PID_MMA,
                      ID_MMA_TAF_POWER_ON_IND,
                      TAF_APS_RcvPowerOnInd_Preproc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_MSG_TAF_PS_GET_CGMTU_VALUE_REQ,
                      TAF_APS_RcvGetCgmtuValue_PreProc),

    /* Added by y00314741 for CDMA Iteration 11, 2015-4-2, begin */
     TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_MSG_TAF_PS_SET_CDMA_DIAL_MODE_REQ,
                      TAF_APS_RcvPsSetDialModeReq_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_MMA,
                      ID_MMA_TAF_1X_SERVICE_STATUS_IND,
                      TAF_APS_RcvMma1XServiceStatusInd_PreProc),
    /* Added by y00314741 for CDMA Iteration 11, 2015-4-2, end */

    TAF_ACT_TBL_ITEM( WUEPS_PID_MMA,
                      ID_MMA_APS_CL_SERVICE_STATUS_IND,
                      TAF_APS_RcvMmaCLServiceStatusInd_PreProc),

    /* Added by y00314741 for CDMA Iteration 15, 2015-5-16, begin */
    TAF_ACT_TBL_ITEM( UEPS_PID_EHSM,
                      ID_EHSM_APS_PDN_ACTIVATE_IND,
                      TAF_APS_RcvEhsmPdnActInd_PreProc),

    TAF_ACT_TBL_ITEM( UEPS_PID_EHSM,
                      ID_EHSM_APS_PDN_DEACTIVATE_IND,
                      TAF_APS_RcvEhsmPdnDeactInd_PreProc),

    TAF_ACT_TBL_ITEM( UEPS_PID_EHSM,
                      ID_EHSM_APS_LTE_HANDOVER_TO_EHRPD_IND,
                      TAF_APS_RcvEhsmLteHandoverToEhrpdInd_PreProc),

    TAF_ACT_TBL_ITEM( UEPS_PID_EHSM,
                      ID_EHSM_APS_PDN_ACTIVATE_CNF,
                      TAF_APS_RcvEhsmPdnActCnf_PreProc),

    TAF_ACT_TBL_ITEM( UEPS_PID_EHSM,
                      ID_EHSM_APS_PDN_DEACTIVATE_CNF,
                      TAF_APS_RcvEhsmPdnDeactCnf_PreProc),

    TAF_ACT_TBL_ITEM( UEPS_PID_EHSM,
                      ID_EHSM_APS_RECONN_CNF,
                      TAF_APS_RcvEhsmReconnCnf_PreProc),

    TAF_ACT_TBL_ITEM( UEPS_PID_DHCP,
                      ID_DHCP_APS_GET_DNS_IPV4_CNF,
                      TAF_APS_RcvDhcpDnsIpv4Cnf_PreProc),

    TAF_ACT_TBL_ITEM( UEPS_PID_DHCP,
                      ID_DHCP_APS_GET_DNS_IPV6_CNF,
                      TAF_APS_RcvDhcpDnsIpv6Cnf_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_MSG_TAF_PS_INTER_PS_SERVICE_MODE_MODIFY_IND,
                      TAF_APS_RcvInterPsServiceModeModifyInd_PreProc),

    /* Added by y00314741 for CDMA Iteration 15, 2015-5-16, end */

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_MSG_TAF_PS_SET_1X_DORM_TIMER_REQ,
                      TAF_APS_RcvAtSet1xDormantTimer_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_MSG_TAF_PS_GET_1X_DORM_TIEMR_REQ,
                      TAF_APS_RcvAtGet1xDormantTimer_PreProc),

#endif

};

/* ����״̬���������Ϣ ״̬�� */
TAF_STA_STRU        g_astTafApsPreProcessFsmTbl[]   =
{
    TAF_STA_TBL_ITEM( TAF_APS_STA_PREPROC,
                      g_astTafApsPreProcessActTbl ),
};

/******************************************************************************
   5 ����ʵ��
******************************************************************************/

VOS_UINT32 TAF_APS_GetPreProcessStaTblSize( VOS_VOID  )
{
    return (sizeof(g_astTafApsPreProcessFsmTbl)/sizeof(TAF_STA_STRU));
}

TAF_FSM_DESC_STRU * TAF_APS_GetPreFsmDescAddr(VOS_VOID)
{
    return (&g_stTafApsPreFsmDesc);
}




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



