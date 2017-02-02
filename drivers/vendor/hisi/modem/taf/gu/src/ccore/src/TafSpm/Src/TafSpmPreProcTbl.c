

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/


#include "TafFsm.h"
#include "MnCallApi.h"
#include "TafSpmPreProcTbl.h"
#include "TafSpmPreProcAct.h"
#include "NasStkInterface.h"
#include "MnComm.h"
#include "TafSpmTimerMgmt.h"
#include "TafSpmSndInternalMsg.h"
#include "TafSpmFsmMainTbl.h"
#if (FEATURE_ON == FEATURE_IMS)
#include "CallImsaInterface.h"
#include "SpmImsaInterface.h"
#include "ImsaInterface.h"
#endif

#include "TafMmaInterface.h"
#include "TafInternalInterface.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_SPM_PREPROC_TBL_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/* Ԥ����״̬�� */
TAF_FSM_DESC_STRU                       g_stTafSpmPreFsmDesc;

/*****************************************************************************
  3 ���Ͷ���
*****************************************************************************/


/*****************************************************************************
  4 ��������
*****************************************************************************/

/*****************************************************************************
  5 ��������
*****************************************************************************/
#if (FEATURE_ON == FEATURE_IMS)
TAF_SPM_PROC_IMSA_CALL_MSG_STRU g_astTafSpmProcImsaCallMsgTbl[]=
{
    /* ID_IMSA_SPM_CALL_MSG��Ϣ�в�ͬ��EventType��Ӧ�Ĵ����� */
    {MN_CALL_EVT_CALL_ORIG_CNF,         TAF_SPM_RcvImsaCallOrigCnf_PreProc     },
    {MN_CALL_EVT_ORIG,                  TAF_SPM_RcvImsaCallOrig_PreProc        },
    {MN_CALL_EVT_CALL_PROC,             TAF_SPM_RcvImsaCallProc_PreProc        },
    {MN_CALL_EVT_ALERTING,              TAF_SPM_RcvImsaCallAlerting_PreProc    },
    {MN_CALL_EVT_CONNECT,               TAF_SPM_RcvImsaCallConnect_PreProc     },
    {MN_CALL_EVT_SUPS_CMD_CNF,          TAF_SPM_RcvImsaCallSupsCmdCnf_PreProc  },
    {MN_CALL_EVT_RELEASED,              TAF_SPM_RcvImsaCallRelease_PreProc     },
    {MN_CALL_EVT_INCOMING,              TAF_SPM_RcvImsaCallIncoming_PreProc    },
    {MN_CALL_EVT_SS_CMD_RSLT,           TAF_SPM_RcvImsaCallSsCmdRslt_PreProc   },
    {MN_CALL_EVT_SS_NOTIFY,             TAF_SPM_RcvImsaCallSsNotify_PreProc    },
    {MN_CALL_EVT_ALL_RELEASED,          TAF_SPM_RcvImsaCallAllRelease_PreProc  },
    {MN_CALL_EVT_HOLD,                  TAF_SPM_RcvImsaCallHold_PreProc        },
    {MN_CALL_EVT_RETRIEVE,              TAF_SPM_RcvImsaCallRetrieve_PreProc    },
};

#endif


/*����״̬��������� */

/* ����״̬���������Ϣ ������ */
TAF_ACT_STRU        g_astTafSpmPreProcessActTbl[]   =
{

    /* AT CALL message */
    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      MN_CALL_APP_ORIG_REQ,
                      TAF_SPM_RcvAppOrigReq_PreProc ),

    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      MN_CALL_APP_SUPS_CMD_REQ,
                      TAF_SPM_RcvAppSupsCmdReq_PreProc ),

    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      MN_CALL_APP_GET_INFO_REQ,
                      TAF_SPM_RcvAppGetInfoReq_PreProc ),

    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      MN_CALL_APP_START_DTMF_REQ,
                      TAF_SPM_RcvAppStartDtmfReq_PreProc ),

    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      MN_CALL_APP_STOP_DTMF_REQ,
                      TAF_SPM_RcvAppStopDtmfReq_PreProc ),

    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      MN_CALL_APP_GET_CDUR_REQ,
                      TAF_SPM_RcvAppGetCdurReq_PreProc ),

    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      ID_TAFAGENT_MN_GET_CALL_INFO_REQ,
                      TAF_SPM_RcvAppGetCallInfoReq_PreProc ),

    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      MN_CALL_APP_CLPR_GET_REQ,
                      TAF_SPM_RcvAppGetClprReq_PreProc ),

    /* AT SMS message */
    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      MN_MSG_MSGTYPE_SEND_RPDATA_DIRECT,
                      TAF_SPM_RcvAppSendRpdataDirect_PreProc ),

    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      MN_MSG_MSGTYPE_SEND_RPDATA_FROMMEM,
                      TAF_SPM_RcvAppSendRpdataDirect_PreProc ),

    /* AT SS message */
    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      TAF_MSG_PROCESS_USS_MSG,
                      TAF_SPM_RcvProcUssSsReq_PreProc ),

    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      TAF_MSG_REGISTERSS_MSG,
                      TAF_SPM_RcvRegisterSsReq_PreProc ),

    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      TAF_MSG_ERASESS_MSG,
                      TAF_SPM_RcvEraseSsReq_PreProc ),

    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      TAF_MSG_ACTIVATESS_MSG,
                      TAF_SPM_RcvActivateSsReq_PreProc ),

    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      TAF_MSG_DEACTIVATESS_MSG,
                      TAF_SPM_RcvDeactivateSsReq_PreProc ),

    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      TAF_MSG_INTERROGATESS_MSG,
                      TAF_SPM_RcvInterrogateSsReq_PreProc ),

    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      TAF_MSG_REGPWD_MSG,
                      TAF_SPM_RcvRegPwdSsReq_PreProc ),

    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      TAF_MSG_ERASECCENTRY_MSG,
                      TAF_SPM_RcvEraseCCentrySsReq_PreProc ),

    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      TAF_MSG_RLEASE_MSG,
                      TAF_SPM_RcvRleaseSsReq_PreProc ),

    /* STK CALL message */
    TAF_ACT_TBL_ITEM( MAPS_STK_PID,
                      STK_CALL_CALLORIG_REQ,
                      TAF_SPM_RcvStkOrigReq_PreProc ),

    TAF_ACT_TBL_ITEM( MAPS_STK_PID,
                      STK_CALL_SUPS_CMD_REQ,
                      TAF_SPM_RcvAppSupsCmdReq_PreProc ),

    TAF_ACT_TBL_ITEM( MAPS_STK_PID,
                      STK_CALL_START_DTMF_REQ,
                      TAF_SPM_RcvAppStartDtmfReq_PreProc ),

    TAF_ACT_TBL_ITEM( MAPS_STK_PID,
                      STK_CALL_STOP_DTMF_REQ,
                      TAF_SPM_RcvAppStopDtmfReq_PreProc ),

    /* STK SS message */
    TAF_ACT_TBL_ITEM( MAPS_STK_PID,
                      STK_SS_REGISTERSS_REQ,
                      TAF_SPM_RcvRegisterSsReq_PreProc ),

    TAF_ACT_TBL_ITEM( MAPS_STK_PID,
                      STK_SS_ERASESS_REQ,
                      TAF_SPM_RcvEraseSsReq_PreProc ),

    TAF_ACT_TBL_ITEM( MAPS_STK_PID,
                      STK_SS_ACTIVATESS_REQ,
                      TAF_SPM_RcvActivateSsReq_PreProc ),

    TAF_ACT_TBL_ITEM( MAPS_STK_PID,
                      STK_SS_DEACTIVATESS_REQ,
                      TAF_SPM_RcvDeactivateSsReq_PreProc ),

    TAF_ACT_TBL_ITEM( MAPS_STK_PID,
                      STK_SS_INTERROGATESS_REQ,
                      TAF_SPM_RcvInterrogateSsReq_PreProc ),

    TAF_ACT_TBL_ITEM( MAPS_STK_PID,
                      STK_SS_USSD_REQ,
                      TAF_SPM_RcvProcUssSsReq_PreProc ),


    /* STK SMS message */
    TAF_ACT_TBL_ITEM( MAPS_STK_PID,
                      STK_MSG_SEND_REQ,
                      TAF_SPM_RcvAppSendRpdataDirect_PreProc ),

#if (FEATURE_ON == FEATURE_IMS)
    /* IMSA CALL message */
    TAF_ACT_TBL_ITEM( PS_PID_IMSA,
                      ID_IMSA_SPM_CALL_MSG,
                      TAF_SPM_RcvImsaCallMsg_PreProc ),

    TAF_ACT_TBL_ITEM( PS_PID_IMSA,
                      ID_IMSA_SPM_CALL_GET_CALL_INFO_CNF,
                      TAF_SPM_RcvImsaGetCallInfoCnf_PreProc ),

    TAF_ACT_TBL_ITEM( PS_PID_IMSA,
                      ID_IMSA_SPM_CHANNEL_INFO_IND,
                      TAF_SPM_RcvImsaChannelInfoInd_PreProc ),

    TAF_ACT_TBL_ITEM( PS_PID_IMSA,
                      ID_IMSA_SPM_CALL_GET_CLPR_CNF,
                      TAF_SPM_RcvImsaGetClprCnf_PreProc ),


    TAF_ACT_TBL_ITEM( PS_PID_IMSA,
                      ID_IMSA_SPM_CALL_START_DTMF_CNF,
                      TAF_SPM_RcvImsaCallStartDtmfCnf_PreProc ),

    TAF_ACT_TBL_ITEM( PS_PID_IMSA,
                      ID_IMSA_SPM_CALL_START_DTMF_RSLT_IND,
                      TAF_SPM_RcvImsaCallStartDtmfRsltInd_PreProc ),

    TAF_ACT_TBL_ITEM( PS_PID_IMSA,
                      ID_IMSA_SPM_CALL_STOP_DTMF_CNF,
                      TAF_SPM_RcvImsaCallStopDtmfCnf_PreProc ),

    TAF_ACT_TBL_ITEM( PS_PID_IMSA,
                      ID_IMSA_SPM_CALL_STOP_DTMF_RSLT_IND,
                      TAF_SPM_RcvImsaCallStopDtmfRsltInd_PreProc ),

    TAF_ACT_TBL_ITEM( PS_PID_IMSA,
                      ID_IMSA_CALL_MSG_SYNC_IND,
                      TAF_SPM_RcvImsaCallMsgSyncInd_PreProc ),


    /* IMSA SS message */
    TAF_ACT_TBL_ITEM( PS_PID_IMSA,
                      ID_IMSA_SPM_SS_MSG,
                      TAF_SPM_RcvImsaSsMsg_PreProc ),


    /* IMS register status notify message */
    TAF_ACT_TBL_ITEM( PS_PID_IMSA,
                      ID_IMSA_NORMAL_REG_STATUS_NOTIFY,
                      TAF_SPM_RcvImsaNormalRegStatusNotify_PreProc ),

    TAF_ACT_TBL_ITEM( PS_PID_IMSA,
                      ID_IMSA_SPM_CALL_INVITE_NEW_PTPT_CNF,
                      TAF_SPM_RcvImsaCallInviteNewPtptCnf_PreProc ),


    TAF_ACT_TBL_ITEM( PS_PID_IMSA,
                      ID_IMSA_SPM_CALL_TYPE_CHANGE_INFO_IND,
                      TAF_SPM_RcvImsaCallTypeChangeInfoInd_PreProc ),

    /* TAF INTERNAL message */
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      TAF_SPM_INTERNAL_DOMAIN_SEL_IND,
                      TAF_SPM_RcvInternalDomainSelInd_PreProc ),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_SPM_SMMA_IND,
                      TAF_SPM_RcvMsgSmmaInd_PreProc ),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_SPM_MSG_REPORT_IND,
                      TAF_SPM_RcvMsgReportInd_PreProc ),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_SPM_MSG_CHECK_RESULT_IND,
                      TAF_SPM_RcvMsgCheckRsltInd_PreProc ),

    /* MMA message */
    TAF_ACT_TBL_ITEM( WUEPS_PID_MMA,
                      ID_MMA_TAF_SERVICE_STATUS_CHANGE_NOTIFY,
                      TAF_SPM_RcvMmaServiceStatusChangeNotify_PreProc ),

    TAF_ACT_TBL_ITEM( WUEPS_PID_MMA,
                      ID_MMA_TAF_NETWORK_CAPABILITY_CHANGE_NOTIFY,
                      TAF_SPM_RcvMmaNetworkCapabilityChangeNotify_PreProc ),

    TAF_ACT_TBL_ITEM( WUEPS_PID_MMA,
                      ID_MMA_TAF_RAT_CHANGE_NOTIFY,
                      TAF_SPM_RcvMmaRatChangeNotify_PreProc ),

    TAF_ACT_TBL_ITEM( WUEPS_PID_MMA,
                      ID_MMA_TAF_IMS_VOICE_CAP_IND,
                      TAF_SPM_RcvMmaImsVoiceCapInd_PreProc ),

    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      MN_CALL_APP_CALL_MODIFY_REQ,
                      TAF_SPM_RcvAppCallModifyReq_PreProc ),

    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      MN_CALL_APP_CALL_ANSWER_REMOTE_MODIFY_REQ,
                      TAF_SPM_RcvAppCallAnswerRemoteModifyReq_PreProc ),

    TAF_ACT_TBL_ITEM( PS_PID_IMSA,
                      ID_IMSA_SPM_CALL_MODIFY_CNF,
                      TAF_SPM_RcvImsaCallModifyCnf_PreProc ),

    TAF_ACT_TBL_ITEM( PS_PID_IMSA,
                      ID_IMSA_SPM_CALL_ANSWER_REMOTE_MODIFY_CNF,
                      TAF_SPM_RcvImsaCallAnswerRemoteModifyCnf_PreProc ),

    TAF_ACT_TBL_ITEM( PS_PID_IMSA,
                      ID_IMSA_SPM_CALL_MODIFY_STATUS_IND,
                      TAF_SPM_RcvImsaCallModifyStatusInd_PreProc ),


    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      TAF_CALL_APP_ECONF_DIAL_REQ,
                      TAF_SPM_RcvAppEconfDialReq_PreProc ),

    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      TAF_CALL_APP_GET_ECONF_CALLED_INFO_REQ,
                      TAF_SPM_RcvAppGetEconfInfoReq_PreProc ),

    TAF_ACT_TBL_ITEM( PS_PID_IMSA,
                      ID_IMSA_SPM_CALL_ECONF_DIAL_CNF,
                      TAF_SPM_RcvImsaEconfDialCnf_PreProc ),

    TAF_ACT_TBL_ITEM( PS_PID_IMSA,
                      ID_IMSA_SPM_CALL_ECONF_ADD_USERS_CNF,
                      TAF_SPM_RcvImsaEconfAddUsersCnf_PreProc ),

    TAF_ACT_TBL_ITEM( PS_PID_IMSA,
                      ID_IMSA_SPM_CALL_ECONF_NOTIFY_IND,
                      TAF_SPM_RcvImsaEconfNotifyInd_PreProc ),

    TAF_ACT_TBL_ITEM( PS_PID_IMSA,
                      ID_IMSA_SPM_CALL_GET_ECONF_CALLED_INFO_CNF,
                      TAF_SPM_RcvImsaGetEconfInfoCnf_PreProc ),

#endif

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_SPM_CC_SRV_REQ_PROTECT_TIMER,
                      TAF_SPM_RcvCcSrvReqProtectTimerExpired_PreProc ),

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_SPM_SMS_SRV_REQ_PROTECT_TIMER,
                      TAF_SPM_RcvSmsSrvReqProtectTimerExpired_PreProc ),

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_SPM_SS_SRV_REQ_PROTECT_TIMER,
                      TAF_SPM_RcvSsSrvReqProtectTimerExpired_PreProc ),

#if (FEATURE_ON == FEATURE_ECALL)
    TAF_ACT_TBL_ITEM( WUEPS_PID_MMA,
                      ID_TAF_MMA_PHONE_MODE_SET_CNF,
                      TAF_SPM_RcvMmaPhoneModeSetCnf_PreProc ),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      TAF_CALL_TAF_REL_CALL_CNF,
                      TAF_SPM_RcvTafRelCallCnf_PreProc ),


    TAF_ACT_TBL_ITEM( MAPS_PB_PID,
                      SI_PB_EVENT_ECALLQUERY_CNF,
                      TAF_SPM_RcvPbQryECallNumCnf_PreProc),

    TAF_ACT_TBL_ITEM( MAPS_PB_PID,
                      SI_PB_EVENT_ECALLINIT_IND,
                      TAF_SPM_RcvPbECallInitInd_PreProc),


#endif
    /* Modified by l00301449 for CDMA Iteration 15, 2015-5-18, begin */
    TAF_ACT_TBL_ITEM( WUEPS_PID_MMA,
                      ID_TAF_MMA_SRV_ACQ_CNF,
                      TAF_SPM_RcvMmaSrvAcqCnf_PreProc),
    /* Modified by l00301449 for CDMA Iteration 15, 2015-5-18, end */

    TAF_ACT_TBL_ITEM( WUEPS_PID_MMA,
                      MMA_TAF_POWER_OFF_IND,
                      TAF_SPM_RcvMmaPowerOffInd_PreProc )

};

/* ����״̬���������Ϣ ״̬�� */
TAF_STA_STRU        g_astTafSpmPreProcessFsmTbl[]   =
{
    TAF_STA_TBL_ITEM( TAF_SPM_MAIN_STA_PREPROC,
                      g_astTafSpmPreProcessActTbl )
};
VOS_UINT32 TAF_SPM_GetPreProcessStaTblSize( VOS_VOID  )
{
    return (sizeof(g_astTafSpmPreProcessFsmTbl)/sizeof(TAF_STA_STRU));
}



TAF_FSM_DESC_STRU * TAF_SPM_GetPreFsmDescAddr(VOS_VOID)
{
    return (&g_stTafSpmPreFsmDesc);
}

#if (FEATURE_ON == FEATURE_IMS)


TAF_SPM_PROC_IMSA_CALL_MSG_STRU *TAF_SPM_GetImsaCallMsgTabAddr(VOS_VOID)
{
    return (&g_astTafSpmProcImsaCallMsgTbl[0]);
}



VOS_UINT32 TAF_SPM_GetImsaCallMsgTabSize( VOS_VOID )
{
    return sizeof(g_astTafSpmProcImsaCallMsgTbl)/sizeof(TAF_SPM_PROC_IMSA_CALL_MSG_STRU);
}
#endif

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

