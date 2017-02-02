

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/

#include "MnComm.h"

#include "NasMmlCtx.h"
#include "NasMmlLib.h"
#include "NasComm.h"

#if (FEATURE_ON == FEATURE_PTM)
#include "NasErrorLog.h"
#endif

#include "NasUtranCtrlInterface.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
  2 ��������
*****************************************************************************/

/*lint -e767 */
#define    THIS_FILE_ID        PS_FILE_ID_NAS_MNTN_C
/*lint +e767 */

/*****************************************************************************
  3 ���Ͷ���
*****************************************************************************/

/*****************************************************************************
  4 ��������
*****************************************************************************/

/*****************************************************************************
  5 ��������
*****************************************************************************/

VOS_UINT32   gulNasOTASwitch = NAS_OTA_SWITCH_OFF;

#if (FEATURE_ON == FEATURE_PTM)
/* NASģ��Error Log�쳣����� */
NAS_ERR_LOG_ALM_LEVEL_STRU g_astNasErrAlmLevelTb[] = {
    {NAS_ERR_LOG_ALM_CS_REG_FAIL,                           NAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {NAS_ERR_LOG_ALM_PS_REG_FAIL,                           NAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {NAS_ERR_LOG_ALM_OOS_NW_SRCH_PROC_INFO,                 NAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {NAS_ERR_LOG_ALM_CS_CALL_FAIL,                          NAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {NAS_ERR_LOG_ALM_PS_CALL_FAIL,                          NAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {NAS_ERR_LOG_ALM_SMS_FAIL,                              NAS_ERR_LOG_CTRL_LEVEL_MAJOR},
    {NAS_ERR_LOG_ALM_VC_OPT_FAIL,                           NAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {NAS_ERR_LOG_ALM_CS_PAGING_FAIL,                        NAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {NAS_ERR_LOG_ALM_CS_MT_CALL_FAIL,                       NAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {NAS_ERR_LOG_ALM_CSFB_MT_CALL_FAIL,                     NAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {NAS_ERR_LOG_ALM_MNTN,                                  NAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {NAS_ERR_LOG_ALM_NW_DETACH_IND,                         NAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {NAS_ERR_LOG_ALM_PS_SRV_REG_FAIL,                       NAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
    /* Added by zwx247453 for CHR optimize, 2015-03-13 Begin */
    {NAS_ERR_LOG_ALM_CM_SRV_REJ_IND,                        NAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {NAS_ERR_LOG_ALM_MO_DETACH_IND,                         NAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {NAS_ERR_LOG_ALM_RAT_FREQUENTLY_SWITCH,                 NAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
    /* Added by zwx247453 for CHR optimize, 2015-03-13 End */
    {NAS_ERR_LOG_ALM_OOS_BEGIN,                             NAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {NAS_ERR_LOG_ALM_OOS_END,                               NAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {NAS_ERR_LOG_ALM_PORCESS_INFO_IND,                      NAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {NAS_ERR_LOG_ALM_FFT_SRCH_MCC_INFO,                     NAS_ERR_LOG_CTRL_LEVEL_CRITICAL},

};

NAS_ERR_LOG_ALM_REPORT_TYPE_STRU g_astNasErrAlmUnsoliReportTypeTb[] = {
    {NAS_ERR_LOG_ALM_CS_PAGING_FAIL,                        NAS_ERR_LOG_FAULT_REPORT},
    {NAS_ERR_LOG_ALM_CS_MT_CALL_FAIL,                       NAS_ERR_LOG_FAULT_REPORT},
    {NAS_ERR_LOG_ALM_CSFB_MT_CALL_FAIL,                     NAS_ERR_LOG_FAULT_REPORT},
    {NAS_ERR_LOG_ALM_OOS_BEGIN,                             NAS_ERR_LOG_FAULT_REPORT},
    {NAS_ERR_LOG_ALM_OOS_END,                               NAS_ERR_LOG_FAULT_REPORT},
    {NAS_ERR_LOG_ALM_CS_CALL_FAIL,                          NAS_ERR_LOG_FAULT_REPORT},
    {NAS_ERR_LOG_ALM_RAT_FREQUENTLY_SWITCH,                 NAS_ERR_LOG_ALARM_REPORT},
};
#endif

NAS_ERR_LOG_BAST_STATE_TO_CSFB_MT_STATE_STRU    g_astNasErrBaseStateToCsfbMtState[] = {
    {NAS_ERR_LOG_BASE_STATE_NULL,                               NAS_ERR_LOG_CSFB_MT_STATE_NULL},
    {NAS_ERR_LOG_BASE_STATE_LMM_CS_PAGING_RECEIVED,             NAS_ERR_LOG_CSFB_MT_STATE_LMM_CS_PAGING_RECEIVED},
    {NAS_ERR_LOG_BASE_STATE_TRAG_NW_SEARCH_FOR_RCV_LMM_SRV_RST, NAS_ERR_LOG_CSFB_MT_STATE_TRAG_NW_SEARCH_FOR_RCV_LMM_SRV_RST},
    {NAS_ERR_LOG_BASE_STATE_END_IND_RECEIVED,                   NAS_ERR_LOG_CSFB_MT_STATE_END_IND_RECEIVED},
    {NAS_ERR_LOG_BASE_STATE_SUSPEND_IND_RECEIVED,               NAS_ERR_LOG_CSFB_MT_STATE_SUSPEND_IND_RECEIVED},
    {NAS_ERR_LOG_BASE_STATE_LTE_RESUME_IND_RECEIVED,            NAS_ERR_LOG_CSFB_MT_STATE_LTE_RESUME_IND_RECEIVED},
    {NAS_ERR_LOG_BASE_STATE_GU_RESUME_IND_RECEIVED,             NAS_ERR_LOG_CSFB_MT_STATE_GU_RESUME_IND_RECEIVED},
    {NAS_ERR_LOG_BASE_STATE_RESUME_TO_GU_FAIL,                  NAS_ERR_LOG_CSFB_MT_STATE_RESUME_TO_GU_FAIL},
    {NAS_ERR_LOG_BASE_STATE_LTE_SYS_INFO_RECEIVED,              NAS_ERR_LOG_CSFB_MT_STATE_LTE_SYS_INFO_RECEIVED},
    {NAS_ERR_LOG_BASE_STATE_GU_SYS_INFO_RECEIVED,               NAS_ERR_LOG_CSFB_MT_STATE_GU_SYS_INFO_RECEIVED},
    {NAS_ERR_LOG_BASE_STATE_PAGING_RSP_SEND,                    NAS_ERR_LOG_CSFB_MT_STATE_PAGING_RSP_SEND},
    {NAS_ERR_LOG_BASE_STATE_TRAG_LAU,                           NAS_ERR_LOG_CSFB_MT_STATE_TRAG_LAU},
    {NAS_ERR_LOG_BASE_STATE_EST_FAILED,                         NAS_ERR_LOG_CSFB_MT_STATE_EST_FAILED},
    {NAS_ERR_LOG_BASE_STATE_EST_SUCCESSED,                      NAS_ERR_LOG_CSFB_MT_STATE_EST_SUCCESSED},
    {NAS_ERR_LOG_BASE_STATE_AUTH_REJ,                           NAS_ERR_LOG_CSFB_MT_STATE_AUTH_REJ},
    {NAS_ERR_LOG_BASE_STATE_AUTH_FAIL,                          NAS_ERR_LOG_CSFB_MT_STATE_AUTH_FAIL},
    {NAS_ERR_LOG_BASE_STATE_T3240_TIMEOUT,                      NAS_ERR_LOG_CSFB_MT_STATE_T3240_TIMEOUT},
    {NAS_ERR_LOG_BASE_STATE_LAU_REJECT,                         NAS_ERR_LOG_CSFB_MT_STATE_LAU_REJECT},
    {NAS_ERR_LOG_BASE_STATE_LAU_ACCEPT,                         NAS_ERR_LOG_CSFB_MT_STATE_LAU_ACCEPT},
    {NAS_ERR_LOG_BASE_STATE_RRC_REL_IND_RECEIVED,               NAS_ERR_LOG_CSFB_MT_STATE_RRC_REL_IND_RECEIVED},
    {NAS_ERR_LOG_BASE_STATE_CSFB_MT_PROTECT_TI_TIME_OUT,        NAS_ERR_LOG_CSFB_MT_STATE_CSFB_MT_PROTECT_TI_TIME_OUT},
    {NAS_ERR_LOG_BASE_STATE_CSFB_MT_TI_TIME_OUT_RCV_REL_IND,    NAS_ERR_LOG_CSFB_MT_STATE_CSFB_MT_TI_TIME_OUT_RCV_REL_IND},
    {NAS_ERR_LOG_BASE_STATE_CM_SERVICE_MSG_RECEIVED,            NAS_ERR_LOG_CSFB_MT_STATE_CM_SERVICE_MSG_RECEIVED},
};

NAS_ERR_LOG_OOS_EVENT_TO_OOS_CAUSE_STRU     g_astNasErrOosEventToOosCause[] = {
    {NAS_ERR_LOG_OOS_EVENT_NULL,                                            NAS_ERR_LOG_OOS_CAUSE_NULL},
    {NAS_ERR_LOG_OOS_EVENT_USER_SYSCFG,                                     NAS_ERR_LOG_OOS_CAUSE_USER_SYSCFG},
    {NAS_ERR_LOG_OOS_EVENT_USER_LIST_SRCH,                                  NAS_ERR_LOG_OOS_CAUSE_USER_LIST_SRCH},
    {NAS_ERR_LOG_OOS_EVENT_USER_SPEC_SRCH,                                  NAS_ERR_LOG_OOS_CAUSE_USER_SPEC_SRCH},
    {NAS_ERR_LOG_OOS_EVENT_USER_AUTO_SEL,                                   NAS_ERR_LOG_OOS_CAUSE_USER_AUTO_SEL},
    {NAS_ERR_LOG_OOS_EVENT_USER_POWER_ON,                                   NAS_ERR_LOG_OOS_CAUSE_USER_POWER_ON},
    {NAS_ERR_LOG_OOS_EVENT_USER_POWER_OFF,                                  NAS_ERR_LOG_OOS_CAUSE_USER_POWER_OFF},
    {NAS_ERR_LOG_OOS_EVENT_USER_DETACH,                                     NAS_ERR_LOG_OOS_CAUSE_USER_DETACH},
    {NAS_ERR_LOG_OOS_EVENT_GAS_NORMAL_AREA_LOST,                            NAS_ERR_LOG_OOS_CAUSE_GAS_NORMAL_AREA_LOST},
    {NAS_ERR_LOG_OOS_EVENT_WAS_NORMAL_AREA_LOST,                            NAS_ERR_LOG_OOS_CAUSE_WAS_NORMAL_AREA_LOST},
    {NAS_ERR_LOG_OOS_EVENT_TAS_NORMAL_AREA_LOST,                            NAS_ERR_LOG_OOS_CAUSE_TAS_NORMAL_AREA_LOST},
    {NAS_ERR_LOG_OOS_EVENT_LMM_NORMAL_AREA_LOST,                            NAS_ERR_LOG_OOS_CAUSE_LMM_NORMAL_AREA_LOST},
    {NAS_ERR_LOG_OOS_EVENT_GAS_NO_RF_AREA_LOST,                             NAS_ERR_LOG_OOS_CAUSE_GAS_NO_RF_AREA_LOST},
    {NAS_ERR_LOG_OOS_EVENT_WAS_NO_RF_AREA_LOST,                             NAS_ERR_LOG_OOS_CAUSE_WAS_NO_RF_AREA_LOST},
    {NAS_ERR_LOG_OOS_EVENT_TAS_NO_RF_AREA_LOST,                             NAS_ERR_LOG_OOS_CAUSE_TAS_NO_RF_AREA_LOST},
    {NAS_ERR_LOG_OOS_EVENT_LMM_NO_RF_AREA_LOST,                             NAS_ERR_LOG_OOS_CAUSE_LMM_NO_RF_AREA_LOST},
    {NAS_ERR_LOG_OOS_EVENT_WAS_LIMITED_CAMP,                                NAS_ERR_LOG_OOS_CAUSE_WAS_LIMITED_CAMP},
    {NAS_ERR_LOG_OOS_EVENT_TAS_LIMITED_CAMP,                                NAS_ERR_LOG_OOS_CAUSE_TAS_LIMITED_CAMP},
    {NAS_ERR_LOG_OOS_EVENT_GAS_AC_INFO_CHANGE,                              NAS_ERR_LOG_OOS_CAUSE_GAS_AC_INFO_CHANGE},
    {NAS_ERR_LOG_OOS_EVENT_WAS_AC_INFO_CHANGE,                              NAS_ERR_LOG_OOS_CAUSE_WAS_AC_INFO_CHANGE},
    {NAS_ERR_LOG_OOS_EVENT_TAS_AC_INFO_CHANGE,                              NAS_ERR_LOG_OOS_CAUSE_TAS_AC_INFO_CHANGE},
    {NAS_ERR_LOG_OOS_EVENT_CS_REG_FAIL,                                     NAS_ERR_LOG_OOS_CAUSE_CS_REG_FAIL},
    {NAS_ERR_LOG_OOS_EVENT_PS_REG_FAIL,                                     NAS_ERR_LOG_OOS_CAUSE_PS_REG_FAIL},
    {NAS_ERR_LOG_OOS_EVENT_COMBINE_EPS_REG_ATTACH_FAIL,                     NAS_ERR_LOG_OOS_CAUSE_COMBINE_EPS_REG_ATTACH_FAIL},
    {NAS_ERR_LOG_OOS_EVENT_COMBINE_EPS_REG_TAU_FAIL,                        NAS_ERR_LOG_OOS_CAUSE_COMBINE_EPS_REG_TAU_FAIL},
    {NAS_ERR_LOG_OOS_EVENT_COMBINE_EPS_REG_ONLY_EPS_SUCC,                   NAS_ERR_LOG_OOS_CAUSE_COMBINE_EPS_REG_ONLY_EPS_SUCC},
    {NAS_ERR_LOG_OOS_EVENT_EPS_REG_ATTACH_FAIL,                             NAS_ERR_LOG_OOS_CAUSE_EPS_REG_ATTACH_FAIL},
    {NAS_ERR_LOG_OOS_EVENT_EPS_REG_TAU_FAIL,                                NAS_ERR_LOG_OOS_CAUSE_EPS_REG_TAU_FAIL},
    {NAS_ERR_LOG_OOS_EVENT_EPS_ONLY_ATTACH,                                 NAS_ERR_LOG_OOS_CAUSE_EPS_ONLY_ATTACH},
    {NAS_ERR_LOG_OOS_EVENT_ATTACH_AUTH_REJ,                                 NAS_ERR_LOG_OOS_CAUSE_ATTACH_AUTH_REJ},
    {NAS_ERR_LOG_OOS_EVENT_CM_SERVICE_REJ,                                  NAS_ERR_LOG_OOS_CAUSE_CM_SERVICE_REJ},
    {NAS_ERR_LOG_OOS_EVENT_PS_SERVICE_REG_FAIL,                             NAS_ERR_LOG_OOS_CAUSE_PS_SERVICE_REG_FAIL},
    {NAS_ERR_LOG_OOS_EVENT_EPS_SERVICE_REQ_FAIL,                            NAS_ERR_LOG_OOS_CAUSE_EPS_SERVICE_REQ_FAIL},
    {NAS_ERR_LOG_OOS_EVENT_GUT_NW_DETACH,                                   NAS_ERR_LOG_OOS_CAUSE_GUT_NW_DETACH},
    {NAS_ERR_LOG_OOS_EVENT_LTE_NW_DETACH,                                   NAS_ERR_LOG_OOS_CAUSE_LTE_NW_DETACH},
    {NAS_ERR_LOG_OOS_EVENT_GUT_LOCAL_DETACH,                                NAS_ERR_LOG_OOS_CAUSE_GUT_LOCAL_DETACH},
    {NAS_ERR_LOG_OOS_EVENT_LTE_LOCAL_DETACH,                                NAS_ERR_LOG_OOS_CAUSE_LTE_LOCAL_DETACH},
    {NAS_ERR_LOG_OOS_EVENT_INTER_SYS_CELL_RESEL_TI_WAIT_GAS_SYS_INFO_EXP,   NAS_ERR_LOG_OOS_CAUSE_INTER_SYS_CELL_RESEL_TI_WAIT_GAS_SYS_INFO_EXP},
    {NAS_ERR_LOG_OOS_EVENT_INTER_SYS_CELL_RESEL_TI_WAIT_WAS_SYS_INFO_EXP,   NAS_ERR_LOG_OOS_CAUSE_INTER_SYS_CELL_RESEL_TI_WAIT_WAS_SYS_INFO_EXP},
    {NAS_ERR_LOG_OOS_EVENT_INTER_SYS_CELL_RESEL_TI_WAIT_TAS_SYS_INFO_EXP,   NAS_ERR_LOG_OOS_CAUSE_INTER_SYS_CELL_RESEL_TI_WAIT_TAS_SYS_INFO_EXP},
    {NAS_ERR_LOG_OOS_EVENT_INTER_SYS_CELL_RESEL_TI_WAIT_LNAS_SYS_INFO_EXP,  NAS_ERR_LOG_OOS_CAUSE_INTER_SYS_CELL_RESEL_TI_WAIT_LNAS_SYS_INFO_EXP},
    {NAS_ERR_LOG_OOS_EVENT_INTER_SYS_CCO_TI_WAIT_GAS_SYS_INFO_EXP,          NAS_ERR_LOG_OOS_CAUSE_INTER_SYS_CCO_TI_WAIT_GAS_SYS_INFO_EXP},
    {NAS_ERR_LOG_OOS_EVENT_INTER_SYS_CCO_TI_WAIT_WAS_SYS_INFO_EXP,          NAS_ERR_LOG_OOS_CAUSE_INTER_SYS_CCO_TI_WAIT_WAS_SYS_INFO_EXP},
    {NAS_ERR_LOG_OOS_EVENT_INTER_SYS_CCO_TI_WAIT_TAS_SYS_INFO_EXP,          NAS_ERR_LOG_OOS_CAUSE_INTER_SYS_CCO_TI_WAIT_TAS_SYS_INFO_EXP},
    {NAS_ERR_LOG_OOS_EVENT_INTER_SYS_CCO_TI_WAIT_LNAS_SYS_INFO_EXP,         NAS_ERR_LOG_OOS_CAUSE_INTER_SYS_CCO_TI_WAIT_LNAS_SYS_INFO_EXP},
    {NAS_ERR_LOG_OOS_EVENT_HIGH_PRO_PLMN_SRCH_BACK_TO_ORIG_PLMN_FAIL,       NAS_ERR_LOG_OOS_CAUSE_HIGH_PRO_PLMN_SRCH_BACK_TO_ORIG_PLMN_FAIL},
    {NAS_ERR_LOG_OOS_EVENT_DISABLE_LTE,                                     NAS_ERR_LOG_OOS_CAUSE_DISABLE_LTE},
    {NAS_ERR_LOG_OOS_EVENT_ENABLE_LTE,                                      NAS_ERR_LOG_OOS_CAUSE_ENABLE_LTE},
};

NAS_MNTN_MM_INFO_STRU                   g_stNasMntnErrorLogMm;

extern NAS_MNTN_SM_INFO_STRU            g_stNasMntnErrorlogSm;

NAS_TIMER_EVENT_INFO_STRU               g_stTimerReportCfg;

VOS_UINT32                              g_ulNasTraceLevle  = NAS_TRACE_LEVEL_HIGH;
VOS_UINT32                              g_ulNasTraceOutput = NAS_TRACE_OUTPUT_ASHELL;

/*****************************************************************************
  6 ��������
*****************************************************************************/

/*lint -save -e958 */

NAS_TIMER_EVENT_INFO_STRU* NAS_GetTimerEventReportCfg()
{
    return (&g_stTimerReportCfg);
}


VOS_VOID NAS_TIMER_EventReport(
    VOS_UINT32                          ulTimerName,
    VOS_UINT32                          ulPid,
    NAS_OM_EVENT_ID_ENUM                enEventId
)
{
    VOS_UINT32                ulEventType;
    NAS_TIMER_EVENT_STRU      stNasTimerEvent;

    ulEventType                 = NAS_BuildEventType(ulPid,ulTimerName);
    stNasTimerEvent.usPid       = (VOS_UINT16)ulPid;
    stNasTimerEvent.usTimerName = (VOS_UINT16)ulTimerName;

    if (VOS_TRUE == NAS_IsNeedTimerEventReport(ulEventType))
    {
        NAS_EventReport(ulPid, enEventId, &stNasTimerEvent, sizeof(stNasTimerEvent));
    }
}


VOS_UINT32 NAS_IsNeedTimerEventReport(
    VOS_UINT32                          ulEventType
)
{
    VOS_UINT32                          ulI;
    NAS_TIMER_EVENT_INFO_STRU          *pstTimerEventInfo;

    pstTimerEventInfo = NAS_GetTimerEventReportCfg();

    for ( ulI = 0; ulI < pstTimerEventInfo->ulItems; ulI++ )
    {
        if ( ulEventType == pstTimerEventInfo->aulTimerMsg[ulI] )
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


VOS_VOID NAS_MNTN_OutputPositionInfo(NAS_MNTN_POSITION_INFO_STRU *pstPositionInfo)
{
    NAS_MML_CAMP_PLMN_INFO_STRU         *pstCampPlmnInfo;

    pstCampPlmnInfo     = NAS_MML_GetCurrCampPlmnInfo();

    pstPositionInfo->stRai.usRac        = pstCampPlmnInfo->ucRac;

    pstPositionInfo->stRai.usLac        = (VOS_UINT16)(pstCampPlmnInfo->stLai.aucLac[1]
                                                    | (pstCampPlmnInfo->stLai.aucLac[0] << 8));

    /* ����ģʽ:
    #define MMC_NW_MODE_I                     0
    #define MMC_NW_MODE_II                    1
    #define MMC_NW_MODE_III                   2
    */
    /* ����MMC */
    pstPositionInfo->ucNetworkMode      = pstCampPlmnInfo->enNetworkMode;

    /* ��gstMmcCellInfo�л�ȡС����Ϣ�� */
    pstPositionInfo->ulCellId           = pstCampPlmnInfo->stCampCellInfo.astCellInfo[0].ulCellId;

    /* ��g_RrMmSysInfoInd�л�ȡ��ϵͳģʽ��PLMN��Ϣ
    #define     MMC_NET_TYPE_GSM            0
    #define     MMC_NET_TYPE_WCDMA          1
    #define     MMC_NET_TYPE_INVALID        0xff
    */
    pstPositionInfo->enSysSubMode       = pstCampPlmnInfo->enSysSubMode;
    pstPositionInfo->stRai.stPlmn.ulMcc = pstCampPlmnInfo->stLai.stPlmnId.ulMcc;
    pstPositionInfo->stRai.stPlmn.ulMnc = pstCampPlmnInfo->stLai.stPlmnId.ulMnc;

    /* ��g_MmSubLyrShare�л�ȡ���뼼�� */
#if (FEATURE_ON == FEATURE_PTM)
    if (NAS_MML_NET_RAT_TYPE_WCDMA == pstCampPlmnInfo->enNetRatType)
    {
        if (NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode())
        {
            pstPositionInfo->ucRat      = NAS_ERR_LOG_RATMODE_WCDMA;
        }
        else
        {
            pstPositionInfo->ucRat      = NAS_ERR_LOG_RATMODE_TDS;
        }
    }
    else if (NAS_MML_NET_RAT_TYPE_GSM == pstCampPlmnInfo->enNetRatType)
    {
        pstPositionInfo->ucRat          = NAS_ERR_LOG_RATMODE_GSM;
    }
    else if (NAS_MML_NET_RAT_TYPE_LTE == pstCampPlmnInfo->enNetRatType)
    {
        pstPositionInfo->ucRat          = NAS_ERR_LOG_RATMODE_LTE;
    }
    else
    {
        pstPositionInfo->ucRat          = NAS_ERR_LOG_RATMODE_BUTT;
    }
#else
    pstPositionInfo->ucRat              = pstCampPlmnInfo->enNetRatType;
#endif

    return;
}
VOS_VOID NAS_MNTN_RecordPdpActiveFail(
    NAS_MNTN_ACTIVE_FAIL_TYPE_ENUM_UINT32                       enFailType,
    VOS_UINT8                                                   ucCntxtIndex,
    VOS_UINT8                                                   ucSmCause,
    VOS_UINT8                                                   ucRegisterFlg
)
{
    NAS_MNTN_ACTIVE_FAIL_EVENT_STRU     stPsActiveFailEvent;
    VOS_UINT32                          ulRet;

    /* �ж��Ƿ���Ҫ��¼ */
    if (g_stNasMntnErrorlogSm.ucPdpActiveFailureCounter >= NAS_MNTN_ERRORLOG_ACTIVATE_FAIL_EVENT_MAX)
    {
        NAS_NORMAL_LOG(WUEPS_PID_SM, "NAS_MNTN_RecordPdpActiveFail: counter reach NAS_MNTN_ERRORLOG_SMS_MO_FAILURE_MAX.");
        return;
    }

    PS_MEM_SET(&stPsActiveFailEvent, 0x00, sizeof(stPsActiveFailEvent));

    /* ��д����ʧ���¼���Ϣ */
    /* �洢PDP����ʧ��ֱ��������� */
    stPsActiveFailEvent.stPsActiveFail.enFailType    = enFailType;
    stPsActiveFailEvent.stPsActiveFail.ucSmCause     = ucSmCause;

    /* ��¼PS�����״̬ */
    stPsActiveFailEvent.stPsActiveFail.ucRegisterFlg = ucRegisterFlg;

    NAS_MMA_OutputUsimInfo(&stPsActiveFailEvent.stUsimInfo);

    NAS_MNTN_OutputPositionInfo(&stPsActiveFailEvent.stPositionInfo);

    /* �������ʧ���¼���Ϣ */
    ulRet = MNTN_RecordErrorLog(NAS_EVT_TYPE_DEF(WUEPS_PID_SM,MNTN_NAS_ERRORLOG_ACTIVATE_FAIL_EVENT),
                                &stPsActiveFailEvent,
                                sizeof(stPsActiveFailEvent));
    if (VOS_OK != ulRet)
    {
        NAS_WARNING_LOG(WUEPS_PID_SM, "NAS_MNTN_RecordPdpActiveFail: MNTN_RecordErrorLog fail.");
        return;
    }

    g_stNasMntnErrorlogSm.ucPdpActiveFailureCounter++;

    return;
}


VOS_UINT32 NAS_MNTN_CheckServiceUnavailableEvent(
    NAS_OM_EVENT_ID_ENUM                enEventId
)
{
    /* ���˷�ҵ���ȡʧ���¼�����CS���PS��ҵ���ȡʧ������¼�����VOS_ERR
    �������¼�5���¼���ҵ���ȡʧ���¼� */
    if ((NAS_OM_EVENT_LOCATION_UPDATE_FAILURE != enEventId)
     && (NAS_OM_EVENT_ATTACH_FAIL             != enEventId)
     && (NAS_OM_EVENT_RAU_FAIL                != enEventId)
     && (NAS_OM_EVENT_AUTH_REJECT             != enEventId)
     && (NAS_OM_EVENT_AUTH_AND_CIPHER_REJ     != enEventId))
    {
        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_VOID NAS_MNTN_RecordServiceUnavailable(
    VOS_UINT32                          ulPid,
    NAS_OM_EVENT_ID_ENUM                enEventId,
    VOS_VOID                           *pPara,
    VOS_UINT32                          ulLen
)
{
    NAS_MNTN_SERVICE_UNAVAILABLE_EVENT_STRU                 stServiceUnavailableEvent;
    VOS_UINT32                                              ulIsHomePlmn;
    VOS_UINT32                                              ulRet;
    VOS_UINT8                                               ucCause;

    /* ����ܾ�UE��RAU,LAU�����ԭ��ֵ����1���ֽڳ��� */
    if ((VOS_NULL_PTR == pPara) || (1 != ulLen))
    {
        NAS_WARNING_LOG(ulPid, "NAS_MNTN_RecordServiceUnavailable: invalid input para.");
        return;
    }

    /* ����ע��ʧ���޹ص��¼� */
    ulRet = NAS_MNTN_CheckServiceUnavailableEvent(enEventId);
    if (VOS_OK != ulRet)
    {
        return;
    }

    /* ����פ����HOME PLMN�ϵ��޷����¼����м�¼��פ���������粻��¼ */
    ulIsHomePlmn = NAS_MMC_IsRoam();
    if (VOS_TRUE == ulIsHomePlmn)
    {
        return;
    }

    /* ��¼CS���PS��ҵ���ȡʧ��ԭ�� */
    ucCause = *(VOS_UINT8 *)pPara;
    if (WUEPS_PID_MM == ulPid)
    {
        NAS_MM_StoreCsUnavailableInfo(ucCause, &g_stNasMntnErrorLogMm.stCsUnavailableInfo);
    }
    else
    {
        NAS_GMM_StorePsUnavailableInfo(ucCause, &g_stNasMntnErrorLogMm.stPsUnavailableInfo);
    }

    /* �ж��Ƿ���Ҫ��¼�¼� */
    if ((VOS_TRUE != g_stNasMntnErrorLogMm.stCsUnavailableInfo.bRecordRequired)
     && (VOS_TRUE != g_stNasMntnErrorLogMm.stPsUnavailableInfo.bRecordRequired))
    {
        return;
    }

    /* �ж��Ƿ���Ҫ��¼:���������ޣ���ֱ�ӷ��� */
    if (g_stNasMntnErrorLogMm.ucServiceUnavailableCounter >= NAS_MNTN_ERRORLOG_SERVICE_UNAVAILABLE_EVENT_MAX)
    {
        NAS_NORMAL_LOG(ulPid, "NAS_MNTN_RecordServiceUnavailable: counter reach NAS_MNTN_ERRORLOG_SERVICE_UNAVAILABLE_EVENT_MAX.");
        return;
    }

    /* ��д�޷����¼���Ϣ */
    PS_MEM_SET(&stServiceUnavailableEvent, 0x00, sizeof(stServiceUnavailableEvent));

    NAS_MMA_OutputUsimInfo(&stServiceUnavailableEvent.stUsimInfo);

    NAS_MNTN_OutputPositionInfo(&stServiceUnavailableEvent.stPositionInfo);

    PS_MEM_CPY(&stServiceUnavailableEvent.stServiceInfo.stCsUnavailable,
               &g_stNasMntnErrorLogMm.stCsUnavailableInfo,
               sizeof(stServiceUnavailableEvent.stServiceInfo.stCsUnavailable));

    PS_MEM_CPY(&stServiceUnavailableEvent.stServiceInfo.stPsUnavailable,
               &g_stNasMntnErrorLogMm.stPsUnavailableInfo,
               sizeof(stServiceUnavailableEvent.stServiceInfo.stPsUnavailable));

    /* ����޷����¼���Ϣ */
    ulRet = MNTN_RecordErrorLog(NAS_EVT_TYPE_DEF(ulPid,MNTN_NAS_ERRORLOG_SERVICE_UNAVAILABLE_EVENT),
                        &stServiceUnavailableEvent,
                        sizeof(stServiceUnavailableEvent));
    if (VOS_OK != ulRet)
    {
        NAS_WARNING_LOG(ulPid, "NAS_MNTN_RecordServiceUnavailable: Error Counter.");
        return;
    }

    /* �������ۼ� */
    g_stNasMntnErrorLogMm.ucServiceUnavailableCounter++;

    /* ����Ѽ�¼��Ϣ */
    if (VOS_TRUE == g_stNasMntnErrorLogMm.stCsUnavailableInfo.bRecordRequired)
    {
        PS_MEM_SET(&g_stNasMntnErrorLogMm.stCsUnavailableInfo,
                   0x00,
                   sizeof(g_stNasMntnErrorLogMm.stCsUnavailableInfo));
    }

    if (VOS_TRUE == g_stNasMntnErrorLogMm.stPsUnavailableInfo.bRecordRequired)
    {
        PS_MEM_SET(&g_stNasMntnErrorLogMm.stPsUnavailableInfo,
                   0x00,
                   sizeof(g_stNasMntnErrorLogMm.stPsUnavailableInfo));
    }

    return;
}


VOS_VOID NAS_MNTN_RecordPlmnUnavailable(
    VOS_UINT8                           ucValIndex,
    VOS_UINT8                           ucCurTimes
)
{
    NAS_MNTN_PLMN_UNAVAILABLE_EVENT_STRU                        *pstPlmnUnavailableEvent = VOS_NULL_PTR;
    VOS_UINT32                                                   ulRet;
    VOS_UINT32                                                   ulEventLen;
    VOS_UINT32                                                   ulPos;
    VOS_UINT8                                                    ucHighPlmnLen;
    VOS_UINT8                                                    ucLowPlmnLen;
    VOS_UINT8                                                   *pucPlmnAvailable = VOS_NULL_PTR;

    /* �ж��Ƿ���Ҫ��¼:�жϵ�ǰ���������ʱ��ʱ������������ֵ��
       �������������ʱ��ʱ��Ϊ5���5������ʱ��¼ */
    if ((NAS_MNTN_AVAILABLE_PLMN_SRCH_TIMER_LENGTH_ZERO   != ucValIndex)
     || (NAS_MNTN_AVAILABLE_PLMN_SRCH_TIMER_COUNTER_TIMES != ucCurTimes))
    {
        return;
    }

    /* �жϼ������Ƿ������ */
    if (g_stNasMntnErrorLogMm.ucPlmnUnavailableCounter >= NAS_MNTN_ERRORLOG_PLMN_UNAVAILABLE_EVENT_MAX)
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MNTN_RecordPlmnUnavailable: counter reach NAS_MNTN_ERRORLOG_PLMN_UNAVAILABLE_EVENT_MAX.");
        return;
    }

    ucHighPlmnLen = (VOS_UINT8)(g_stNasMntnErrorLogMm.stPlmnAvailableList.ulHighPlmnNum * sizeof(MNTN_PLMN_ID_STRU));
    ucLowPlmnLen  = (VOS_UINT8)(g_stNasMntnErrorLogMm.stPlmnAvailableList.ulLowPlmnNum * sizeof(NAS_MNTN_LOW_PLMN_INFO_STRU));
    /* ����PLMN�б�ĳ��Ȳ���NAS_MNTN_PLMN_UNAVAILABLE_EVENT_STRU�ṹ�м���
       aucPlmnAttempt[4]ռ�õ�4���ֽ���Ҫ��ȥ���� */
    ulEventLen = (sizeof(NAS_MNTN_PLMN_UNAVAILABLE_EVENT_STRU) - 4)
                  + ((sizeof(ucHighPlmnLen) + ucHighPlmnLen)
                  + (sizeof(ucLowPlmnLen) + ucLowPlmnLen));

    pstPlmnUnavailableEvent = (NAS_MNTN_PLMN_UNAVAILABLE_EVENT_STRU *)PS_MEM_ALLOC(
                                WUEPS_PID_MMC, ulEventLen);
    if (VOS_NULL_PTR == pstPlmnUnavailableEvent)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MNTN_RecordPlmnUnavailable: Fail to alloc memory.");
        return;
    }

    /* ��д����ʧ���¼���Ϣ */
    PS_MEM_SET(pstPlmnUnavailableEvent, 0x00, ulEventLen);

    NAS_MMA_OutputUsimInfo(&pstPlmnUnavailableEvent->stUsimInfo);

    NAS_MNTN_OutputPositionInfo(&pstPlmnUnavailableEvent->stPositionInfo);

    NAS_MMA_OutputPlmnSrchBand(&pstPlmnUnavailableEvent->ulBand);

    pucPlmnAvailable = pstPlmnUnavailableEvent->aucPlmnAttempt;
    ulPos            = 0;

    /* ��д������PLMN���ݽṹ: LV��ʽ��V���ֽṹΪMNTN_PLMN_ID_STRU */
    *(pucPlmnAvailable + ulPos) = ucHighPlmnLen;
    ulPos++;

    PS_MEM_CPY((pucPlmnAvailable + ulPos),
                g_stNasMntnErrorLogMm.stPlmnAvailableList.astHighPlmnList,
                ucHighPlmnLen);
    ulPos += ucHighPlmnLen;

    /* ��д������PLMN���ݽṹ: LV��ʽ��V���ֽṹΪNAS_MNTN_LOW_PLMN_INFO_STRU */
    *(pucPlmnAvailable + ulPos) = ucLowPlmnLen;
    ulPos++;

    PS_MEM_CPY((pucPlmnAvailable + ulPos),
                g_stNasMntnErrorLogMm.stPlmnAvailableList.astLowPlmnList,
                ucLowPlmnLen);

    /* �������ʧ���¼���Ϣ */
    ulRet = MNTN_RecordErrorLog(NAS_EVT_TYPE_DEF(WUEPS_PID_MMC, MNTN_NAS_ERRORLOG_PLMN_UNAVAILABLE_EVENT),
                         pstPlmnUnavailableEvent, ulEventLen);
    PS_MEM_FREE(WUEPS_PID_MMC, pstPlmnUnavailableEvent);

    if (VOS_OK != ulRet)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MNTN_RecordPlmnUnavailable: fail to MNTN_RecordErrorLog.");
        return;
    }

    /* �¼��������ۼ� */
    g_stNasMntnErrorLogMm.ucPlmnUnavailableCounter++;

    return;
}
VOS_VOID NAS_EventReport(
    VOS_UINT32                          ulPid,
    NAS_OM_EVENT_ID_ENUM                enEventId,
    VOS_VOID                           *pPara,
    VOS_UINT32                          ulLen
)
{
    /* Modified by wx270776 for OM�ں�, 2015-7-23, begin */
    DIAG_EVENT_IND_STRU                 stDiagEvent;
    NAS_OM_EVENT_IND_STRUCT            *pstNasOmEvent = VOS_NULL_PTR;
    VOS_VOID                           *pData = pPara;
    VOS_UINT32                          ulNasOmEventMsgLen;
    VOS_UINT32                          ulRslt;

    /* ��μ�� */
    if ( (VOS_NULL_PTR == pData) && (ulLen != 0) )
    {
        /* �����ӡ */
        PS_NAS_LOG(ulPid, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_EventReport:pPara is NULL.");
        return;
    }

    /* �����ڴ� */
    if (4 >= ulLen)
    {
        ulNasOmEventMsgLen = sizeof(NAS_OM_EVENT_IND_STRUCT);
        pstNasOmEvent = (NAS_OM_EVENT_IND_STRUCT*)PS_MEM_ALLOC(ulPid, ulNasOmEventMsgLen);
    }
    else
    {
        ulNasOmEventMsgLen = sizeof(NAS_OM_EVENT_IND_STRUCT) + ulLen -4;
        pstNasOmEvent = (NAS_OM_EVENT_IND_STRUCT*)PS_MEM_ALLOC(ulPid, ulNasOmEventMsgLen);
    }

    if (VOS_NULL_PTR == pstNasOmEvent)
    {
        PS_NAS_LOG(ulPid, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_EventReport:Alloc mem fail.");
        return;
    }

    /* ��ʼ�� */
    PS_MEM_SET((VOS_UINT8*)pstNasOmEvent, 0x0, ulNasOmEventMsgLen);

    /* ��д�¼���Ϣ���� */
    pstNasOmEvent->usEventId          = enEventId;
    pstNasOmEvent->usReserve          = 0;
    if ( (VOS_NULL_PTR != pData) && (ulLen > 0) )
    {
        PS_MEM_CPY(pstNasOmEvent->aucData, pData, ulLen);
    }

    /* ��д����DIAG�Ľṹ�� */
    stDiagEvent.ulLength              = sizeof(NAS_OM_EVENT_IND_STRUCT) - 4 + ulLen;
    stDiagEvent.ulPid                 = ulPid;
    stDiagEvent.ulEventId             = (VOS_UINT32)enEventId;
    stDiagEvent.ulModule              = DIAG_GEN_MODULE(VOS_GetModemIDFromPid(ulPid), DIAG_MODE_UMTS);
    stDiagEvent.pData                 = pstNasOmEvent;

    /* ������Ϣ */
    ulRslt = DIAG_EventReport(&stDiagEvent);
    if (VOS_OK != ulRslt)
    {
        /* �����ӡ */
        PS_NAS_LOG(ulPid, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_EventReport:DIAG_EventReport fail.");
    }

    /* �ͷ��ڴ� */
    PS_MEM_FREE(ulPid, pstNasOmEvent);
    /* Modified by wx270776 for OM�ں�, 2015-7-23, end */


    NAS_MNTN_RecordServiceUnavailable(ulPid, enEventId, pPara, ulLen);

    return;
}
VOS_VOID NAS_SendAirMsgToOM(
    VOS_UINT32                          ulPid,
    VOS_UINT16                          usMsgID,
    VOS_UINT8                           ucUpDown,
    VOS_UINT32                          ulMsgLen,
    VOS_UINT8                          *pucMsg
)
{
    /* Modified by wx270776 for OM�ں�, 2015-7-18, begin */
    NAS_AIR_MSG_STRU                   *pstNasAirMsg    = VOS_NULL_PTR;
    DIAG_AIR_IND_STRU                   stNasOtaAirInd;
    VOS_UINT32                          ulNasAirMsgLen;
    VOS_UINT32                          ulRet;


    PS_NAS_LOG(ulPid, VOS_NULL, PS_LOG_LEVEL_NORMAL, "NAS_SendAirMsgToOM!");

    /* ��ڲ������ */
    /* ���տ���Ϣ����Ϊ 0 ���� �տ���Ϣָ��Ϊ��ʱ���쳣���� */
    if ( (0 == ulMsgLen)
        || (VOS_NULL_PTR == pucMsg ))
    {
        PS_NAS_LOG(ulPid, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_SendAirMsgToOM:WARNING: Input params invalid.");
        return;
    }

    /* �������Ҫ�ϱ��տ���Ϣ����ֱ�ӷ��� */
    if ( NAS_OTA_SWITCH_OFF == gulNasOTASwitch )
    {
        return;
    }

    /* �����ڴ� */
#if 0
    if (8 >= ulMsgLen)
    {
        ulNasAirMsgLen = sizeof(NAS_AIR_MSG_STRU) + 4;
    }
    else
    {
        ulNasAirMsgLen = sizeof(NAS_AIR_MSG_STRU) - 4 + ulMsgLen;
    }
#endif

    ulNasAirMsgLen = sizeof(NAS_AIR_MSG_STRU) + ulMsgLen;

    pstNasAirMsg = (NAS_AIR_MSG_STRU*)PS_MEM_ALLOC(ulPid, ulNasAirMsgLen);
    if ( VOS_NULL_PTR == pstNasAirMsg )
    {
        NAS_WARNING_LOG(ulPid, "NAS_SendAirMsgToOM:WARNING: PS_MEM_ALLOC Failed!");
        return;
    }

    /* ��ʼ�� */
    PS_MEM_SET(pstNasAirMsg, 0x00, ulNasAirMsgLen);

    pstNasAirMsg->usMsgId             = usMsgID;
    pstNasAirMsg->ucUpDown            = ucUpDown;
    pstNasAirMsg->ucReserve           = 0;
    pstNasAirMsg->ulLengthASN         = ulMsgLen;
    PS_MEM_CPY(pstNasAirMsg->aucNasMsg, pucMsg, ulMsgLen);

    /* ��д��Ϣ���� */
    stNasOtaAirInd.ulModule           = DIAG_GEN_MODULE(VOS_GetModemIDFromPid(ulPid), DIAG_MODE_UMTS);
    stNasOtaAirInd.ulPid              = ulPid;
    stNasOtaAirInd.ulMsgId            = usMsgID;
    stNasOtaAirInd.ulLength           = ulMsgLen + NAS_OTA_MSG_ASN_LEN_OFFSET;
    stNasOtaAirInd.pData              = pstNasAirMsg;

    switch(ucUpDown)
    {
    case NAS_OTA_DIRECTION_UP:
        stNasOtaAirInd.ulDirection    = DIAG_SIDE_NET;
        break;

    case NAS_OTA_DIRECTION_DOWN:
        stNasOtaAirInd.ulDirection    = DIAG_SIDE_UE;
        break;

    default:
        stNasOtaAirInd.ulDirection    = 0;
        break;
    }

    /* ������Ϣ */
    ulRet = DIAG_AirMsgReport(&stNasOtaAirInd);
    if (VOS_OK != ulRet)
    {
        NAS_WARNING_LOG(ulPid, "NAS_SendAirMsgToOM: WARNING: Sending Air Msg To OM Failed!");
    }

    /* �ͷ��ڴ� */
    PS_MEM_FREE(ulPid, pstNasAirMsg);

    return;
    /* Modified by wx270776 for OM�ں�, 2015-7-18, end */
}

/*****************************************************************************
 �� �� ��  : NAS_SetNasOtaSwitch
 ��������  : ����OTA�Ŀ���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��22��
   ��    ��   : zhoujun 40661
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  NAS_SetNasOtaSwitch(
    VOS_UINT32                          ulNasOTASwitch
)
{
    gulNasOTASwitch = ulNasOTASwitch;
}

/*****************************************************************************
 �� �� ��  : NAS_GetNasOtaSwitch
 ��������  : ����OTA�Ŀ���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��22��
   ��    ��   : zhoujun 40661
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_GetNasOtaSwitch(VOS_VOID)
{
    return gulNasOTASwitch;
}

#if (FEATURE_ON == FEATURE_PTM)

VOS_UINT16 NAS_GetErrLogAlmLevel(NAS_ERR_LOG_ALM_ID_ENUM_U16 enAlmId)
{
    VOS_UINT16                          usTableLen;
    VOS_UINT16                          usStep;

    /* ��ȡTab���� */
    usTableLen = sizeof(g_astNasErrAlmLevelTb)/sizeof(g_astNasErrAlmLevelTb[0]);

    /* ����ض�ӦAlm ID��log�ȼ� */
    for (usStep = 0; usStep < usTableLen; usStep++)
    {
        if (g_astNasErrAlmLevelTb[usStep].enAlmID == enAlmId)
        {
            return g_astNasErrAlmLevelTb[usStep].usLogLevel;
        }
    }

    /* δ�鵽������δ����ȼ� */
    return NAS_ERR_LOG_CTRL_LEVEL_NULL;
}
NAS_ERR_LOG_UNSOLI_REPORT_TYPE_ENUM_U16 NAS_GetErrLogUnsoliReportType(NAS_ERR_LOG_ALM_ID_ENUM_U16 enAlmId)
{
    VOS_UINT16                          usTableLen;
    VOS_UINT16                          usStep;

    /* ��ȡTab���� */
    usTableLen = sizeof(g_astNasErrAlmUnsoliReportTypeTb)/sizeof(g_astNasErrAlmUnsoliReportTypeTb[0]);

    /* ����ض�ӦAlm ID��log�ȼ� */
    for (usStep = 0; usStep < usTableLen; usStep++)
    {
        if (g_astNasErrAlmUnsoliReportTypeTb[usStep].enAlmID == enAlmId)
        {
            return g_astNasErrAlmUnsoliReportTypeTb[usStep].enReportType;
        }
    }

    /* δ�鵽������δ����ȼ� */
    return NAS_ERR_LOG_REPORT_TYPE_BUTT;
}
VOS_VOID NAS_COM_MntnPutRingbuf(
    VOS_UINT32                          ulName,
    VOS_UINT32                          ulPid,
    VOS_UINT8                          *pucData,
    VOS_UINT32                          ulLen
)
{
    NAS_ERR_LOG_MNTN_PUT_BUF_INFO_STRU  *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                           ulMsgLen;
    /*lint -e961*/
    ulMsgLen = sizeof(NAS_ERR_LOG_MNTN_PUT_BUF_INFO_STRU) - 4 + ulLen;
    /*lint +e961*/

    pstMsg = (NAS_ERR_LOG_MNTN_PUT_BUF_INFO_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMC, ulMsgLen);
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_MntnPutRingbuf:ERROR:Alloc Mem Fail.");
        return;
    }

    PS_MEM_SET(pstMsg, 0, ulMsgLen);

    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = ulPid;
    /* Modified by wx270776 for OM�ں�, 2015-7-16, begin */
    pstMsg->ulReceiverPid               = MSP_PID_DIAG_APP_AGENT;
    /* Modified by wx270776 for OM�ں�, 2015-7-16, end */
    pstMsg->ulLength                    = ulMsgLen - VOS_MSG_HEAD_LENGTH;
    pstMsg->ulMsgName                   = ulName;

    /* ��ָ�뱣�� */
    if (VOS_NULL_PTR != pucData)
    {
        PS_MEM_CPY(pstMsg->aucContent, pucData, ulLen);
    }

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_MMC, pstMsg);

    return;
}

#endif
NAS_ERR_LOG_CSFB_MT_STATE_ENUM_U32 NAS_MNTN_ConvertBaseStateToCsfbMtState(
    NAS_ERR_LOG_BASE_STATE_ENUM_U32     enBaseState
)
{
    NAS_ERR_LOG_CSFB_MT_STATE_ENUM_U32  enCsfbMtState;
    VOS_UINT32                          i;

    enCsfbMtState  = NAS_ERR_LOG_CSFB_MT_CALL_CAUSE_BUTT;

    for (i = 0; i < (sizeof(g_astNasErrBaseStateToCsfbMtState) / sizeof(g_astNasErrBaseStateToCsfbMtState[0])); i++)
    {
        if (enBaseState == g_astNasErrBaseStateToCsfbMtState[i].enBaseState)
        {
            enCsfbMtState = g_astNasErrBaseStateToCsfbMtState[i].enCsfbMtState;
        }
    }

    return enCsfbMtState;
}


NAS_ERR_LOG_OOS_CAUSE_ENUM_UINT32 NAS_MNTN_ConvertOosEventToOosCause(
    NAS_ERR_LOG_OOS_EVENT_ENUM_UINT32   enOosEvent
)
{
    NAS_ERR_LOG_OOS_CAUSE_ENUM_UINT32   enOosCause;
    VOS_UINT32                          i;

    enOosCause  = NAS_ERR_LOG_OOS_CAUSE_NULL;

    for (i = 0; i < (sizeof(g_astNasErrOosEventToOosCause) / sizeof(g_astNasErrOosEventToOosCause[0])); i++)
    {
        if (enOosEvent == g_astNasErrOosEventToOosCause[i].enOosEvent)
        {
            enOosCause = g_astNasErrOosEventToOosCause[i].enOosCause;
        }
    }

    return enOosCause;
}


VOS_VOID NAS_MNTN_SndLogMsg(VOS_CHAR *pcData, VOS_UINT32 ulDataLength)
{
    TAF_MNTN_LOG_PRINT_STRU            *pstMsg;
    VOS_UINT32                          ulMsgLength;
    VOS_UINT32                          ulRet;

    /* ��Ϣ���� = sizeof(TAF_MNTN_LOG_PRINT_STRU) - 4 + ����ʵ�ʳ��� + �ַ���������'\0' */
    /*lint -e961*/
    ulMsgLength = sizeof(TAF_MNTN_LOG_PRINT_STRU) - 4 + ulDataLength + 1;
    /*lint +e961*/

    /* ������Ϣ */
    pstMsg = (TAF_MNTN_LOG_PRINT_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                WUEPS_PID_TAF,
                                ulMsgLength);
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    /* ��ʼ����Ϣ */
    PS_MEM_SET((VOS_CHAR *)pstMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               ulMsgLength - VOS_MSG_HEAD_LENGTH);

    /* ��д��Ϣͷ */
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = WUEPS_PID_AT;
    pstMsg->ulMsgName       = MN_CALLBACK_LOG_PRINT;
    pstMsg->enModemId       = VOS_GetModemIDFromPid(WUEPS_PID_TAF);

    PS_MEM_CPY(pstMsg->acLog, pcData, ulDataLength);
    pstMsg->acLog[ulDataLength] = '\0';

    ulRet = PS_SEND_MSG(WUEPS_PID_TAF, pstMsg);
    if (VOS_OK != ulRet)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MNTN_SndLogMsg:ERROR:Snd Msg Fail.");
    }
    return;
}


/*lint -esym(960,69)*/
VOS_VOID NAS_MNTN_LogPrintf(VOS_CHAR *pcFmt, ...)
{
    VOS_CHAR                            acBuf[NAS_TRACE_BUF_LEN] = {0};
    VOS_UINT32                          ulPrintLength = 0;

    /* ��ʽ�����BUFFER */
    /*lint -e530 -e830*/
    NAS_MNTN_LOG_FORMAT(ulPrintLength, acBuf, NAS_TRACE_BUF_LEN, pcFmt);
    /*lint +e530 +e830*/

    /* ѡ�����ASEHLL��CSHELL */
    if (NAS_TRACE_OUTPUT_ASHELL == (NAS_TRACE_OUTPUT_ASHELL & g_ulNasTraceOutput))
    {
        NAS_MNTN_SndLogMsg(acBuf, ulPrintLength);
    }

    if (NAS_TRACE_OUTPUT_CSHELL == (NAS_TRACE_OUTPUT_CSHELL & g_ulNasTraceOutput))
    {
        (VOS_VOID)vos_printf("%s", acBuf);
    }

    return;
}
/*lint +esym(960,69)*/


VOS_VOID NAS_MNTN_SetTraceLevel(VOS_UINT32 ulLvl)
{
    g_ulNasTraceLevle = (ulLvl >= NAS_TRACE_LEVEL_TOP) ? NAS_TRACE_LEVEL_TOP : ulLvl;
    return;
}


VOS_VOID NAS_MNTN_SetTraceOutput(VOS_UINT32 ulOutput)
{
    g_ulNasTraceOutput = (ulOutput >= NAS_TRACE_OUTPUT_ALL) ? NAS_TRACE_LEVEL_TOP : ulOutput;
    return;
}


/*lint -restore */

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

