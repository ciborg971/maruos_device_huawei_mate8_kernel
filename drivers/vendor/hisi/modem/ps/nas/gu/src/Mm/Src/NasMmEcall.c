

/*****************************************************************************
   1 ͷ�ļ�����
*****************************************************************************/
#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

#include "MM_Ext.h"
#include "NasMmEcall.h"
#include "NasMmSndOm.h"
#include "MmCcInterface.h"
#include "SmsMmInterface.h"
#include "MmSsInterface.h"

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_NAS_MM_ECALL_C

#if (FEATURE_ON == FEATURE_ECALL)
/*****************************************************************************
   2 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
   3 ����ʵ��
*****************************************************************************/

NAS_MM_ECALL_INFO_STRU *NAS_MM_GetEcallInfoAddr(VOS_VOID)
{
    return &(g_MmGlobalInfo.stEcallInfo);
}


VOS_VOID NAS_MM_SetT3242ExpiredFlg(VOS_UINT8 ucT3242ExpiredFlg)
{
    NAS_MM_GetEcallInfoAddr()->ucT3242ExpiredFlg = ucT3242ExpiredFlg;
}


VOS_UINT8 NAS_MM_GetT3242ExpiredFlg(VOS_VOID)
{
    return (NAS_MM_GetEcallInfoAddr()->ucT3242ExpiredFlg);
}


VOS_VOID NAS_MM_SetT3243ExpiredFlg(VOS_UINT8 ucT3243ExpiredFlg)
{
    NAS_MM_GetEcallInfoAddr()->ucT3243ExpiredFlg = ucT3243ExpiredFlg;
}


VOS_UINT8 NAS_MM_GetT3243ExpiredFlg(VOS_VOID)
{
    return (NAS_MM_GetEcallInfoAddr()->ucT3243ExpiredFlg);
}


VOS_UINT8 NAS_MM_GetT3242StartNeededFlg(VOS_VOID)
{
    return (NAS_MM_GetEcallInfoAddr()->ucT3242StartNeededFlg);
}


VOS_VOID NAS_MM_SetT3242StartNeededFlg(VOS_UINT8 ucT3242StartNeededFlg)
{
    NAS_MM_GetEcallInfoAddr()->ucT3242StartNeededFlg = ucT3242StartNeededFlg;
}


VOS_UINT8 NAS_MM_GetT3243StartNeededFlg(VOS_VOID)
{
    return (NAS_MM_GetEcallInfoAddr()->ucT3243StartNeededFlg);
}


VOS_VOID NAS_MM_SetT3243StartNeededFlg(VOS_UINT8 ucT3243StartNeededFlg)
{
    NAS_MM_GetEcallInfoAddr()->ucT3243StartNeededFlg = ucT3243StartNeededFlg;
}


VOS_VOID NAS_MM_RcvT3242Expired_MmIdleNoCellAvailable(VOS_VOID *pRcvMsg)
{
    NAS_MM_SetT3242ExpiredFlg(VOS_TRUE);
}


VOS_VOID NAS_MM_RcvT3242Expired_MmIdleNormalService(VOS_VOID *pRcvMsg)
{
    /* ����eCall inactivity ���� */
    NAS_MM_PerformECallInactivity();
}
VOS_VOID NAS_MM_RcvT3243Expired_MmIdleNoCellAvailable(VOS_VOID *pRcvMsg)
{
    NAS_MM_SetT3243ExpiredFlg(VOS_TRUE);
}


VOS_VOID NAS_MM_RcvT3243Expired_MmIdleNormalService(VOS_VOID *pRcvMsg)
{
    /* ����eCall inactivity ���� */
    NAS_MM_PerformECallInactivity();
}
VOS_VOID NAS_MM_StopAllTimersRelatedToEcall(VOS_VOID)
{
    Mm_TimerStop(MM_TIMER_T3242);

    Mm_TimerStop(MM_TIMER_T3243);
}


VOS_VOID NAS_MM_ClearAllEcallTimersExpiredFlg(VOS_VOID)
{
    NAS_MM_SetT3242ExpiredFlg(VOS_FALSE);

    NAS_MM_SetT3243ExpiredFlg(VOS_FALSE);
}


VOS_VOID NAS_MM_ClearAllEcallTimersStartNeededFlg(VOS_VOID)
{
    NAS_MM_SetT3242StartNeededFlg(VOS_FALSE);

    NAS_MM_SetT3243StartNeededFlg(VOS_FALSE);
}


VOS_VOID NAS_MM_RcvMmcMmSysInfo_MmIdleECallInactive(
    VOS_VOID                           *pRcvMsg
)
{
    if (VOS_TRUE == NAS_MM_IsCsForbidden())
    {
        NAS_MM_SndMmcForbidenRslt();
    }
    else
    {
        /* ֪ͨMMC��ǰCS��ע���� */
        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                    MM_MMC_LU_RESULT_FAILURE,
                                    NAS_MML_REG_FAIL_CAUSE_ECALL_INACTIVE);
    }

    NAS_MM_ProcBufferMsg_MmIdleECallInactive();
    
    return;
}
VOS_VOID NAS_MM_RcvMmcMmAttachReq_MmIdleECallInactive(
    VOS_VOID                           *pRcvMsg
)
{
    MMCMM_ATTACH_REQ_STRU              *pstAttchReq             = VOS_NULL_PTR;

    pstAttchReq = (MMCMM_ATTACH_REQ_STRU*)pRcvMsg;

    if (MM_TRUE == Mm_RcvMmcAttachReq(pstAttchReq))
    {
        /* �ظ�MMCMM_ATTACH_CNF�Ĳ���,����ȴ�ATTACH�����־λ */
        if (MM_WAIT_CS_ATTACH == (g_MmGlobalInfo.stAttachInfo.enAttachType
                                & MM_WAIT_CS_ATTACH))
        {
            NAS_MM_SndMmcAttachCnf();
        }
        g_MmGlobalInfo.stAttachInfo.enAttachType = MM_WAIT_NULL_ATTACH;
    }

    return;
}
VOS_VOID NAS_MM_ProcMmcMmDetachReq_MmIdleECallInactive( VOS_VOID )
{
    /* �жϵȴ���־�Ƿ���ڣ������������MMCMM_DETACH CNF */
    if (MM_WAIT_CS_DETACH== (g_MmGlobalInfo.stDetachInfo.enDetachType
                 & MM_WAIT_CS_DETACH))
    {
        NAS_MM_SndMmcDetachCnf(MM_DETACHED);
        /* ����ȴ���־ */
        g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_NULL_DETACH;
    }

    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                MM_MMC_LU_RESULT_FAILURE,
                                NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);

    return;
}



VOS_VOID NAS_MM_RcvMmcMmPlmnSrchInit_MmIdleECallInactive(
    VOS_VOID                           *pRcvMsg
)
{
    g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;
    g_MmGlobalInfo.ucNotCampONPreState = g_MmGlobalInfo.ucState;
    Mm_ComSetMmState(MM_IDLE_PLMN_SEARCH);

    return;
}



VOS_VOID NAS_MM_RcvMmcMmCoverageLostInd_MmIdleECallInactive(
    VOS_VOID                           *pRcvMsg
)
{
    g_MmGlobalInfo.ucSysInfoFlg = MM_FALSE;

    g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;
    g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;

    /* �����������ǰ��״̬,�������ɹ��������ж�LAI�Ƿ�ı� */
    g_MmGlobalInfo.ucNotCampONPreState = g_MmGlobalInfo.ucState;

    Mm_ComSetMmState(MM_IDLE_NO_CELL_AVAILABLE);

    g_MmSubLyrShare.MmShare.ucPagingPlmnSrch = MM_PAGING_PLMNSRCH_FALSE;

    return;
}
VOS_VOID NAS_MM_RcvMmcMmPowerOffReq_MmIdleECallInactive(
    VOS_VOID                           *pRcvMsg
)
{
    if (MM_TRUE == Mm_RcvMmcPowerOffReq(pRcvMsg))
    {
        /* ��MMC����MMCMM_POWER_OFF_CNF */
        Mm_SndMmcPowerOffCnf();
        
        Mm_ComSetMmState(MM_STATE_NULL);
    }

    return;
}
VOS_VOID NAS_MM_RcvMmcMmWAcInfoChangeInd_MmIdleECallInactive(
    VOS_VOID                           *pRcvMsg
)
{
    MMCMM_W_AC_INFO_CHANGE_IND_STRU  *pstAcInfoChangeInd = VOS_NULL_PTR;

    pstAcInfoChangeInd = (MMCMM_W_AC_INFO_CHANGE_IND_STRU*)pRcvMsg;

    /* ��ǰС����Ϊע�����ޣ�����ҪǨ��MM״̬ */
    if (NAS_MML_RESTRICTION_UNBAR_TO_BAR == pstAcInfoChangeInd->enCsRestrictRegisterChange)
    {
        g_MmGlobalInfo.ucMmServiceState = NAS_MM_GetLauUptNeededCsSrvStatus();
    }

    return;
}
VOS_VOID NAS_MM_RcvSmsEstReq_MmIdleECallInactive(
    VOS_VOID                           *pRcvMsg
)
{
    if (MM_TRUE == Mm_RcvSmsEstReq(pRcvMsg))
    {
        /* �ظ�SMSʧ��,����Ҫ�ز� */    
        Mm_SndSmsRelInd(g_MmSmsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_ECALL_INACTIVE); 
    }

    return;
}
VOS_VOID NAS_MM_RcvSsEstReq_MmIdleECallInactive(
    VOS_VOID                           *pRcvMsg
)
{
    if (MM_TRUE == Mm_RcvSsEstReq(pRcvMsg))
    {
        /* �ظ�SSʧ��,����Ҫ�ز� */
        Mm_SndSsRelInd(g_MmSsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_ECALL_INACTIVE);
    }

    return;
}
VOS_VOID NAS_MM_RcvCcEstReq_MmIdleECallInactive(
    VOS_VOID                           *pRcvMsg
)
{
    VOS_UINT32                          ulCsForbiddenFlg;
    
    if (MM_FALSE == Mm_RcvCcEstReq(pRcvMsg))
    {
        return;
    }

    if ((MM_CONST_NUM_8  > g_MmCcEstReq.ulTransactionId)
     || (MM_CONST_NUM_14 < g_MmCcEstReq.ulTransactionId))
    {
        /* TI���Ϸ�,ֱ�ӻظ�ʧ�� */
        Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);
        return;
    }

#if (FEATURE_ON == FEATURE_LTE)
    /* ��ǰ��LTE��,ֱ�ӻظ�ʧ��,�쳣����,ʵ��LTE�²���������״̬(��ѡ����) */
    if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
    {
        Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_UE_INVALID_STATE);
        return;
    }
#endif

    ulCsForbiddenFlg = NAS_MM_IsCsForbidden();

    /* ��ֹ�뿪ecall inactiveʱ����״̬���ô˱��ΪVOS_FALSE */
    NAS_MML_SetCsAttachAllowFlg(VOS_TRUE);

    /* �������� */
    if (MMCC_EMERGENCY_CALL == g_MmCcEstReq.ulCallType)
    {
        /* CS��bar��CS��forbidden������ע��,ֱ�ӷ���CS�Ľ���ҵ�� */
        if (VOS_TRUE == NAS_MML_GetCsRestrictRegisterFlg())
        {  
            /* ��¼�յ���������ʱ��״̬ */
            g_MmGlobalInfo.ucStaOfRcvXXEstReq = MM_IDLE_LOCATION_UPDATE_NEEDED;
    
            NAS_MM_EstMmConnection(MM_CONN_CTRL_CC);

            return;
        }

         /* CS��bar��CS��forbidden������ע��,ֱ�ӷ���CS�Ľ���ҵ�� */
        if (VOS_TRUE == ulCsForbiddenFlg)
        {  
            /* ��¼�յ���������ʱ��״̬ */
            g_MmGlobalInfo.ucStaOfRcvXXEstReq = MM_IDLE_LIMITED_SERVICE;
    
            NAS_MM_EstMmConnection(MM_CONN_CTRL_CC);

            return;
        }
    }
    else
    {
        /* CS����ҵ��bar��CS��forbidden��ֱ�ӻظ�����ʧ�� */
        if ((VOS_TRUE == NAS_MML_GetCsRestrictNormalServiceFlg())
         || (VOS_TRUE == ulCsForbiddenFlg))
        {  
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                            NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);
            return;
        }
    }

    /* ��¼�յ���������ʱ��״̬ */
    g_MmGlobalInfo.ucStaOfRcvXXEstReq = g_MmGlobalInfo.ucState;

    /* �Ȼ���������� */
    NAS_MM_UpdateConnCtrlInfo(MM_CONN_CTRL_CC);

    /* ����LAU */
    g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;
    g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = 0;
    
    Mm_ComLuOnly();

    return;
}




VOS_VOID NAS_MM_PerformECallInactivity( VOS_VOID )
{
    MM_MSG_IMSI_DETACH_IND_STRU         stDetachIndMsg;
    VOS_UINT8                           ucRestrictRegister;
    VOS_UINT32                          ulCsForbFlg;

    PS_MEM_SET(&stDetachIndMsg, 0x0, sizeof(stDetachIndMsg));
    
    ucRestrictRegister = NAS_MML_GetCsRestrictRegisterFlg();
    ulCsForbFlg        = NAS_MM_IsCsForbidden();
    
    /* ���CS�ĸ���״̬ΪU1��CS�Ѿ�attach�Ҳ�����CS��ע����CS��forbidden,ϵͳ��Ϣָʾ��Ҫattach,���Ƚ���CS��detach���� */
    if ((NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == NAS_MML_GetCsUpdateStatus())
     && (VOS_FALSE                              == ucRestrictRegister)
     && (VOS_FALSE                              == ulCsForbFlg)) 
    {
        if ((MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState)
         && (MM_ATT_NEED        == g_MmGlobalInfo.ucAttFlg))
        {
            g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_NORMAL;

            NAS_MM_FillMobileID(&(stDetachIndMsg.MmIeMobileId.MobileID));

            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;
            Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_IMSI_DETACH);

            Mm_ComMsgImsiDetachIniSndOfEstReq(&stDetachIndMsg);
            Mm_TimerStart(MM_TIMER_PROTECT_SIGNALLING);
            
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_ESTING);


            /* ����MM�ķ���״̬ΪMM_DETACHED */
            g_MmGlobalInfo.ucMmServiceState = MM_DETACHED;

            return;
        }
    }

    /* ����MM�ķ���״̬ΪMM_DETACHED */
    g_MmGlobalInfo.ucMmServiceState = MM_DETACHED;

    /* ֪ͨRRC��SMSģ��attach״̬�����仯 */
    Mm_ComNasInfoSav(MM_STATUS_DETACHED, NAS_MML_GetSimCsSecurityCksn());

    /* ����MM״̬Ϊmm_ecall_inactive״̬ */
    Mm_ComSetMmState(MM_IDLE_ECALL_INACTIVE);

    /* ֹͣMM���е����ж�ʱ�� */    
    Mm_TimerStop(MM_TIMER_STOP_ALL);

    /* ���attempt counter�Լ������LU���ֵ,��Ϊ�п���ǰ��LAU����ʧ�� */
    g_MmGlobalInfo.LuInfo.ucLuAttmptCnt          = 0;
    g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg      = MM_FALSE;    
    g_MmGlobalInfo.LuInfo.ucRetryFlg             = MM_FALSE;
    g_MmGlobalInfo.LuInfo.ucT3213AttmptCnt       = 0;
    g_MmGlobalInfo.LuInfo.ucImmAccRejLuAttmptCnt = 0;
    
    /* ���T3242��T3243��ʱ��� */
    NAS_MM_ClearAllEcallTimersExpiredFlg();

    /* ����CS�ĸ���״̬Ϊnot updatd */
    NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED);

    /* дusim���ļ�(Uֵ����not updateд��) */    
    NAS_MM_DelLaiTmsiCK();

    NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_DISABLED);

    return;
}


VOS_VOID NAS_MM_RecordEcallTimerStartNeededFlag(VOS_VOID)
{
    /* ��eCall onlyģʽ������Ҫ����T3243/T3243 */
    if (NAS_MML_ECALL_ONLY != NAS_MML_GetCallMode())
    {
        return;
    }
    
    /*���T3242��T3243�����У���ֹͣ�ö�ʱ�� */
    if (MM_TIMER_RUNNING == NAS_MM_QryTimerStatus(MM_TIMER_T3242))
    {
        Mm_TimerStop(MM_TIMER_T3242);
    }

    if (MM_TIMER_RUNNING == NAS_MM_QryTimerStatus(MM_TIMER_T3243))
    {
        Mm_TimerStop(MM_TIMER_T3243);
    }
    
    if (MMCC_EMERGENCY_CALL == g_MmCcEstReq.ulCallType)
    {
        /* ���Ϊ��������, ��������T3242��ʶ */
        NAS_MM_SetT3242StartNeededFlg(VOS_TRUE);
        
        NAS_MM_SetT3243ExpiredFlg(VOS_FALSE);
    }
    else
    {
        /* ���Ϊnormal����, ��������T3243��ʶ */
        NAS_MM_SetT3243StartNeededFlg(VOS_TRUE);
        
        NAS_MM_SetT3242ExpiredFlg(VOS_FALSE);
    }
}


VOS_VOID NAS_MM_ClearEcallTimerInfo(VOS_VOID)
{
    /* ֹͣ����eCall��ض�ʱ�� */
    NAS_MM_StopAllTimersRelatedToEcall();

    /* ���eCall T3242/T3243��ʱ��������ʶ */
    NAS_MM_ClearAllEcallTimersStartNeededFlg();

    /* ���eCall T3242/T3243��ʱ����ʱ��ʶ */
    NAS_MM_ClearAllEcallTimersExpiredFlg();

}
VOS_VOID NAS_MM_InitEcallInfo(VOS_VOID)
{
    /* ���eCall T3242/T3243��ʱ��������ʶ */
    NAS_MM_ClearAllEcallTimersStartNeededFlg();

    /* ���eCall T3242/T3243��ʱ����ʱ��ʶ */
    NAS_MM_ClearAllEcallTimersExpiredFlg();
}


VOS_VOID NAS_MM_ProcEcallTimerStartNeededFlg(VOS_VOID)
{
    if (VOS_TRUE == NAS_MM_GetT3242StartNeededFlg())
    {
        Mm_TimerStart(MM_TIMER_T3242);

        NAS_MM_SetT3242StartNeededFlg(VOS_FALSE);
    }

    if (VOS_TRUE == NAS_MM_GetT3243StartNeededFlg())
    {
        Mm_TimerStart(MM_TIMER_T3243);

        NAS_MM_SetT3243StartNeededFlg(VOS_FALSE);
    }
}


VOS_VOID NAS_MM_ProcBufferMsg_MmIdleECallInactive( VOS_VOID )
{
    MMCC_EST_REQ_STRU                   stCcEstReqMsg;
    MMSMS_EST_REQ_STRU                  stSmsMsg; 
    MMSS_EST_REQ_STRU                   stSsMsg;

    /* ��������״̬�����������anycellפ������Ҫȡ�����洦�� */
    if (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg)
    {
        Mm_MakeCcEstReq(&stCcEstReqMsg);
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg = MM_FALSE;
        NAS_MM_RcvCcEstReq_MmIdleECallInactive(&stCcEstReqMsg);
    }
    else if (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg)
    {
        Mm_MakeSmsEstReq(&stSmsMsg);
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg = MM_FALSE;
        NAS_MM_RcvSmsEstReq_MmIdleECallInactive(&stSmsMsg);
    }
    else if (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg)
    {
        Mm_MakeSsEstReq(&stSsMsg);
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg = MM_FALSE;
        NAS_MM_RcvSsEstReq_MmIdleECallInactive(&stSsMsg);
    }
    else
    {
        
    }
    
    NAS_MM_UpdateCsServiceBufferStatusFlg();
    
    return;
}

#endif



#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif
