

/*****************************************************************************
   1 ͷ�ļ�����
*****************************************************************************/

#include "GmmInc.h"
#include "MM_Share.h"
#include "GmmCasGlobal.h"
#include "GmmCasSuspend.h"
#include "GmmCasMain.h"
#include "GmmCasComm.h"


#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_GMM_CASMAIN_C



/*****************************************************************************
   2 ȫ�ֱ�������
******************************************************************************/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/*---------------2.1 ����ģ���ڲ�ȫ�ֱ��� ---------------*/
/*=======================================================*/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/*---------------2.2 ��ģ���ڲ�ȫ�ֱ��� -----------------*/
/*=======================================================*/
GMM_CAS_CTRL_STRU       gstGmmCasGlobalCtrl;        /* GMM CASȫ�ֿ��ƽṹ���� */

GMM_SUSPEND_CTRL_STRU   gstGmmSuspendCtrl;

VOS_UINT8     g_GmmInterRatCellReselect = 0;

/*****************************************************************************
   3 ����ʵ��
******************************************************************************/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/*---------------3.1 GMM������Ϣ����        -------------*/
/*=======================================================*/


VOS_VOID GMM_CasMsgProc(struct MsgCB* pMsg, VOS_UINT8 *pucFollowOn)
{
    /* �ֲ��������� */
    REL_TIMER_MSG           *pTimerMsg;
    MSG_HEADER_STRU         *pNasMsgHeader;

    /* ��Ϣ�������� */
    *pucFollowOn = GMM_FALSE;                               /* Ĭ�ϲ��ٽ���ԭ��Ϣ��ں������� */

    /* Modified by wx270776 for OM�ں�, 2015-7-16, begin */
    if (WUEPS_PID_ADMIN == pMsg->ulSenderPid)
    /* Modified by wx270776 for OM�ں�, 2015-7-16, end */
    {
        *pucFollowOn = GMM_TRUE;
        return;
    }

    pNasMsgHeader = (MSG_HEADER_STRU*)pMsg;
    pTimerMsg = (REL_TIMER_MSG*)pMsg;

    /* �����л�״̬�µ���Ϣ */
    switch (g_GmmGlobalCtrl.ucState)
    {
        case GMM_SUSPENDED_NORMAL_SERVICE:

            GMM_CasMsgProc_GmmSuspendNormalService(pMsg, pucFollowOn);

            break;

        case GMM_SUSPENDED_WAIT_FOR_SYSINFO:
            if (WUEPS_PID_MMC == pMsg->ulSenderPid)
            {
                if (MMCGMM_GSM_SYS_INFO_IND == pNasMsgHeader->ulMsgName)
                {
                    if (GMM_TRUE == GMM_IsCasGsmMode())
                    {
                        /* ������Ϣ�ַ��������������Ϣ */
                        GMM_LOG_INFO("GMM_CasMsgProc:Receive MMCGMM_GSM_SYS_INFO_IND in GMM_SUSPENDED_WAIT_FOR_SYSINFO state.");
                        *pucFollowOn = GMM_TRUE;
                        return;
                    }
                }
                else if(MMCGMM_SYS_INFO_IND == pNasMsgHeader->ulMsgName)
                {
                    if (GMM_FALSE == GMM_IsCasGsmMode())
                    {
                        /* ������Ϣ�ַ��������������Ϣ */
                        GMM_LOG_INFO("GMM_CasMsgProc:Receive MMCGMM_SYS_INFO_IND in GMM_SUSPENDED_WAIT_FOR_SYSINFO state.");
                        *pucFollowOn = GMM_TRUE;
                        return;
                    }
                }
                else if (MMCGMM_SUSPEND_IND == pNasMsgHeader->ulMsgName)
                {
                    GMM_LOG_INFO("GMM_CasMsgProc:Receive MMCGMM_SUSPEND_IND in GMM_SUSPENDED_WAIT_FOR_SYSINFO state.");
                    *pucFollowOn = GMM_TRUE;
                    return;
                }
                else if (MMCGMM_POWER_OFF_REQ == pNasMsgHeader->ulMsgName)
                {
                    GMM_BufferMsgDump();
                    Gmm_TimerStop(GMM_TIMER_SUSPENDED);
                    Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);
                    *pucFollowOn = GMM_TRUE;
                    return;
                }
                else if (MMCGMM_COVERAGE_LOST_IND == pNasMsgHeader->ulMsgName)
                {
                    *pucFollowOn = GMM_TRUE;
                    return;
                }
                else if (MMCGMM_PLMN_SEARCH_INITIATED == pNasMsgHeader->ulMsgName)
                {
                    *pucFollowOn = GMM_TRUE;
                    return;
                }

                /* �յ�MMCGMM_ATTACH_REQ��Ϣ���򲻽��л��棬����ֱ�ӻظ�Attach�ɹ���
                   ������פ��������������Attach */
                else if ( MMCGMM_ATTACH_REQ == pNasMsgHeader->ulMsgName )
                {
                    *pucFollowOn = GMM_TRUE;
                    return;
                }

                /* �յ�MMCGMM_DETACH_REQ��Ϣ���򲻽��л��� */
                else if (MMCGMM_DETACH_REQ == pNasMsgHeader->ulMsgName)
                {
                    *pucFollowOn = GMM_TRUE;
                    return;
                }
                else
                {
                }
            }
            else if (UEPS_PID_GAS == pMsg->ulSenderPid)
            {
                if (RRMM_GPRS_SUSPENSION_IND == pNasMsgHeader->ulMsgName)
                {
                    /* ������Ϣ�ַ��������������Ϣ */
                    GMM_LOG_INFO("GMM_CasMsgProc:Receive RRMM_GPRS_SUSPENSION_IND in GMM_SUSPENDED_WAIT_FOR_SYSINFO state.");
                    *pucFollowOn = GMM_TRUE;
                    return;
                }

                if (GRRMM_MS_RADIO_ACCESS_CAPABILITIES_IND == pNasMsgHeader->ulMsgName)
                {
                    /* ������Ϣ�ַ��������������Ϣ */
                    GMM_LOG_INFO("GMM_CasMsgProc:Receive GRRMM_MS_RADIO_ACCESS_CAPABILITIES_IND in GMM_SUSPENDED_WAIT_FOR_SYSINFO state.");
                    *pucFollowOn = GMM_TRUE;
                    return;
                }

                if (GRRMM_MS_RADIO_ACCESS_CAPABILITIES_TDS_IND == pNasMsgHeader->ulMsgName)
                {
                    /* ������Ϣ�ַ��������������Ϣ */
                    GMM_LOG_INFO("GMM_CasMsgProc:Receive GRRMM_MS_RADIO_ACCESS_CAPABILITIES_TDS_IND in GMM_SUSPENDED_WAIT_FOR_SYSINFO state.");
                    *pucFollowOn = GMM_TRUE;
                    return;
                }
            }
            else if (WUEPS_PID_WRR == pMsg->ulSenderPid)
            {
                if (RRMM_SECURITY_IND == pNasMsgHeader->ulMsgName)
                {
                    *pucFollowOn = GMM_TRUE;
                    return;
                }

                if (RRMM_REL_IND == pNasMsgHeader->ulMsgName)
                {
                    /* ������Ϣ�ַ��������������Ϣ */
                    *pucFollowOn = GMM_TRUE;
                    return;
                }
            }
            else
            {
                if (RRMM_REL_IND == pNasMsgHeader->ulMsgName)
                {
                    /* ������Ϣ�ַ��������������Ϣ */
                    *pucFollowOn = GMM_TRUE;
                    return;
                }
            }
            if ((NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
             && (MMC_SUSPEND_CAUSE_HANDOVER == gstGmmSuspendCtrl.ucSuspendCause)
             && (NAS_MML_NET_RAT_TYPE_GSM   == gstGmmSuspendCtrl.ucPreRat))
            {
                if (WUEPS_PID_SM == pMsg->ulSenderPid)
                {
                    if (GMMSM_DATA_REQ == pNasMsgHeader->ulMsgName)
                    {
                        *pucFollowOn = GMM_TRUE;
                        return;
                    }
                }
                else if (WUEPS_PID_SMS == pMsg->ulSenderPid)
                {
                    if (PMMSMS_EST_REQ == pNasMsgHeader->ulMsgName)
                    {
                        *pucFollowOn = GMM_TRUE;
                        return;
                    }
                }
                else if (WUEPS_PID_RABM == pMsg->ulSenderPid)
                {
                    if (ID_RABM_GMM_REESTABLISH_REQ == pNasMsgHeader->ulMsgName)
                    {
                        *pucFollowOn = GMM_TRUE;
                        return;
                    }
                }
                else
                {
                }
            }
            GMM_SuspendMsgProc(pMsg, pucFollowOn);
            break;

        case GMM_GPRS_SUSPENSION:
        case GMM_SUSPENDED_GPRS_SUSPENSION:
            if (UEPS_PID_GAS == pMsg->ulSenderPid)
            {
                if (RRMM_GPRS_RESUME_IND == pNasMsgHeader->ulMsgName)
                {
                    /* ������Ϣ�ַ��������������Ϣ */
                    GMM_LOG_INFO("GMM_CasMsgProc:Receive RRMM_GPRS_RESUME_IND in GMM_GPRS_SUSPENSION state.");
                    *pucFollowOn = GMM_TRUE;
                    return;
                }

                if (GRRMM_MS_RADIO_ACCESS_CAPABILITIES_IND == pNasMsgHeader->ulMsgName)
                {
                    /* ������Ϣ�ַ��������������Ϣ */
                    GMM_LOG_INFO("GMM_CasMsgProc:Receive GRRMM_MS_RADIO_ACCESS_CAPABILITIES_IND in GMM_SUSPENDED_WAIT_FOR_SYSINFO state.");
                    *pucFollowOn = GMM_TRUE;
                    return;
                }

                if (GRRMM_MS_RADIO_ACCESS_CAPABILITIES_TDS_IND == pNasMsgHeader->ulMsgName)
                {
                    /* ������Ϣ�ַ��������������Ϣ */
                    GMM_LOG_INFO("GMM_CasMsgProc:Receive GRRMM_MS_RADIO_ACCESS_CAPABILITIES_TDS_IND in GMM_SUSPENDED_WAIT_FOR_SYSINFO state.");
                    *pucFollowOn = GMM_TRUE;
                    return;
                }
            }
            else if (WUEPS_PID_MMC == pMsg->ulSenderPid)
            {
                /* ��ȡ������Ȧ���Ӷ� */
                if (VOS_TRUE == NAS_GMM_RcvMmcMsg_PreProc_GprsSuspension(pMsg, pucFollowOn))
                {
                    return;
                }
            }
            else if (VOS_PID_TIMER == pMsg->ulSenderPid)
            {
                if (GMM_TIMER_T3314 == pTimerMsg->ulName)
                {
                    /* ������Ϣ�ַ��������������Ϣ */
                    GMM_LOG_INFO("GMM_CasMsgProc:Ready time expired in GMM_GPRS_SUSPENSION state.");
                    *pucFollowOn = GMM_TRUE;
                    return;
                }
                else if (GMM_TIMER_T3312 == pTimerMsg->ulName)
                {
                    gstGmmSuspendCtrl.ucT3312State = GMM_T3312_TIMEOUT;
                    Gmm_TimerStop(GMM_TIMER_T3312);
#if (FEATURE_LTE == FEATURE_ON)
                    NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_EXP);
#endif
                    return;
                }
                else if (GMM_TIMER_1S == pTimerMsg->ulName)
                {
                    /* ������Ϣ�ַ��������������Ϣ */
                    GMM_LOG_INFO("GMM_CasMsgProc:GMM_TIMER_5S timer expired in GMM_GPRS_SUSPENSION state");
                    *pucFollowOn = GMM_TRUE;
                    return;
                }
                else
                {
                }
            }
            else
            {
            }

            /* ������Ϣȫ������ */
            GMM_SuspendMsgProc(pMsg, pucFollowOn);
            break;
        default:
            *pucFollowOn = GMM_TRUE;
            break;
    }
    return;
}


VOS_VOID GMM_SaveMsg(VOS_VOID *pMsg, VOS_UINT8 *pucFollowOn)
{
    MSG_HEADER_STRU         *pNasMsgHeader;

    pNasMsgHeader = (MSG_HEADER_STRU*)pMsg;

    switch (pNasMsgHeader->ulSenderPid)
    {
    case WUEPS_PID_USIM:
        /*��Ȩ��Ӧ��Ϣ�������־ͣ��ʱ�������������³ɹ�������·�����Ӧ���̣�
          ���˵ȴ������ط���Ȩ*/
        if (USIMM_AUTHENTICATION_CNF == pNasMsgHeader->ulMsgName)
        {
            Gmm_TimerStop(GMM_TIMER_PROTECT);                                           /* ͣ����Timer                              */
            g_GmmReqCnfMng.ucCnfMask &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;         /* ��ȴ���־                               */
            GMM_LOG_NORM("GMM_SaveMsg:Receive USIM AUTHENTICATION CNF,Discard.");
        }
        break;

    case WUEPS_PID_WRR:/*RRC_NAS_AP_CLASS:
 */
        GMM_LOG_WARN("GMM_SaveMsg:Receive unexpected msg of RRC.");
        break;

    case WUEPS_PID_RABM:/*GMM_RABM_AP_CLASS:
 */
        if (ID_RABM_GMM_REESTABLISH_REQ == pNasMsgHeader->ulMsgName)
        {
            /*GMM_BufferMsgReceive(pMsg);*/
            /* �л�����W����Ŵ���RABM��Ϣ��G��������RABM */
            if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
            {
                /* ����л�֮ǰ�б��жϵ�Detach���̣��򲻻���RABM���ؽ����� */
                if ((GMM_TRUE == g_GmmGlobalCtrl.ucFollowOnFlg)
                    && ((GMM_DETACH_COMBINED == g_GmmGlobalCtrl.ucSpecProcHold)
                     || (GMM_DETACH_NORMAL == g_GmmGlobalCtrl.ucSpecProcHold)
                     || (GMM_DETACH_NORMAL_NETMODE_CHANGE == g_GmmGlobalCtrl.ucSpecProcHold)
                     || (GMM_DETACH_WITH_IMSI == g_GmmGlobalCtrl.ucSpecProcHold)))
                {
                    Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);     /* ����GMMRABM_REESTABLISH_CNF(fail)        */
                }
                else
                {
                    g_GmmGlobalCtrl.ucFollowOnFlg       = GMM_TRUE;
                    g_GmmGlobalCtrl.ucSpecProcHold      = GMM_SERVICE_REQUEST_DATA_IDLE;
                    NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

                    #if(PS_UE_REL_VER >= PS_PTL_VER_R7)
                    g_GmmGlobalCtrl.usUplinkDataStatus  = ((GMMRABM_REESTABLISH_REQ_STRU *)pMsg)->usUplinkDataStatus;
                    #endif
                }
            }
            else
            {
                Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);         /* ����GMMRABM_REESTABLISH_CNF(fail)        */
                GMM_LOG_NORM("GMM_SaveMsg:Receive Rabm Reestablish In 2G,Discard.");
            }
        }
        /* RAU RSP��Ϣ��*/
        else if (ID_RABM_GMM_ROUTING_AREA_UPDATE_RSP == pNasMsgHeader->ulMsgName)
        {
            Gmm_TimerStop(GMM_TIMER_RAU_RSP);
        }
        else
        {
        }
        break;

    case WUEPS_PID_MMC:/*MMC_GMM_AP_CLASS:
 */
        switch (pNasMsgHeader->ulMsgName)
        {
            case MMCGMM_REGISTER_INITIATION:
            case MMCGMM_REL_REQ:
                *pucFollowOn = GMM_TRUE;
                break;
            case MMCGMM_ATTACH_REQ:
                g_GmmGlobalCtrl.stAttachInfo.enAttachType = GMM_WAIT_NULL_ATTACH;
                GMM_BufferMsgReceive((struct MsgCB *)pMsg);
                break;
            case MMCGMM_DETACH_REQ:
                NAS_GMM_SaveDetachMsg(pMsg);
                break;

            case MMCGMM_MODE_CHANGE_REQ:
                GMM_BufferMsgReceive((struct MsgCB *)pMsg);
                break;
            default:
                GMM_LOG_WARN("GMM_SaveMsg:Receive unexpected msg of MMC.");
                break;
        }
        break;

    case WUEPS_PID_MM:
        switch (pNasMsgHeader->ulMsgName)
        {
            case MMGMM_CS_CONNECT_IND:
            case MMGMM_CM_SERVICE_REJECT_IND:
            case MMGMM_AUTHENTICATON_FAILURE_IND:
            case MMGMM_LU_RESULT_IND:

                *pucFollowOn = GMM_TRUE;
                break;

            default:
                 break;
        }
        break;

    case WUEPS_PID_SM:/*GMM_SM_AP_CLASS:
 */
        switch (pNasMsgHeader->ulMsgName)
        {
            case GMMSM_ESTABLISH_REQ:
            case GMMSM_PDP_DEACTIVATED_IND:
                GMM_BufferMsgReceive((struct MsgCB *)pMsg);
                break;
            case GMMSM_DATA_REQ:
                /*GMM_BufferMsgReceive(pMsg);*/
                g_GmmGlobalCtrl.ucFollowOnFlg = GMM_TRUE;
                NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

                g_GmmGlobalCtrl.ucSpecProcHold = GMM_SERVICE_REQUEST_SIGNALLING;
                Gmm_BufSmDataReqMsg(pMsg);
                break;
            case GMMSM_PDP_STATUS_IND:
                Gmm_RcvSmPdpStatusInd(pMsg);
                break;
            default :
                GMM_LOG_WARN("GMM_SaveMsg:Receive unexpected msg of SM.");
                break;
        }
        break;

    case WUEPS_PID_SMS:/*GMM_SMS_AP_CLASS:
 */
        switch (pNasMsgHeader->ulMsgName)
        {
            case PMMSMS_EST_REQ:
                Gmm_SndSmsErrorInd(GMM_SMS_SIGN_NO_EXIST);
                break;
            case PMMSMS_UNITDATA_REQ:
                GMM_BufferMsgReceive((struct MsgCB *)pMsg);
                break;
            default :
                GMM_LOG_WARN("GMM_SaveMsg:Receive unexpected msg of SMS.");
                break;
        }
        break;

    case UEPS_PID_LL:/*LLC_GMM_AP_CLASS:
 */
        GMM_LOG_WARN("GMM_SaveMsg:Receive unexpected msg of LLC.");
        break;
    case UEPS_PID_GAS:/*GAS_GMM_AP_CLASS:
 */
        GMM_LOG_WARN("GMM_SaveMsg:Receive unexpected msg of GAS.");
        break;
    default :
        GMM_LOG_WARN("GMM_SaveMsg:Receive unexpected msg of others.");
        break;
    }
}


VOS_VOID GMM_SuspendMsgProc(struct MsgCB* pMsg, VOS_UINT8 *pucFollowOn)
{
    /* �ֲ��������� */
    REL_TIMER_MSG           *pTimerMsg;

    if (VOS_PID_TIMER == pMsg->ulSenderPid)
    {
        pTimerMsg = (REL_TIMER_MSG*)pMsg;
        if ((GMM_TIMER_SUSPENDED == pTimerMsg->ulName) || (GMM_TIMER_T3314 == pTimerMsg->ulName) || (GMM_TIMER_TC_DELAY_SUSPEND_RSP == pTimerMsg->ulName) || (GMM_TIMER_T3323 == pTimerMsg->ulName))
        {
            *pucFollowOn = GMM_TRUE;
            return;
        }
        else if (GMM_TIMER_T3312 == pTimerMsg->ulName)
        {
            gstGmmSuspendCtrl.ucT3312State = GMM_T3312_TIMEOUT;
            Gmm_TimerStop(GMM_TIMER_T3312);
#if (FEATURE_LTE == FEATURE_ON)
            NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_EXP);
#endif
            return;
        }
        /* ����״̬����Ҫ����LMM�İ�ȫ�����Ļظ���Ϣ */
#if (FEATURE_ON == FEATURE_LTE)
        else if (GMM_TIMER_WAIT_GET_HO_SECU_INFO_CNF == pTimerMsg->ulName)
        {
            *pucFollowOn = GMM_TRUE;
            GMM_LOG_INFO("GMM_SuspendMsgProc:Receive GMM_TIMER_WAIT_GET_HO_SECU_INFO_CNF in SUSPENDED_NORMAL_SERVICE state.");
            return;
        }
#endif

        else if (GMM_TIMER_HO_WAIT_SYSINFO == pTimerMsg->ulName)
        {
            *pucFollowOn = GMM_TRUE;
            GMM_LOG_INFO("GMM_SuspendMsgProc:Receive GMM_TIMER_HO_WAIT_SYSINFO in SUSPENDED_NORMAL_SERVICE state.");
            return;

        }

        else
        {
            GMM_LOG_WARN("GMM_SuspendMsgProc:Receive unexpected timer expired msg.");
            return;
        }
    }

    GMM_SaveMsg((VOS_VOID *)pMsg, pucFollowOn);

    return;
}

/* BEGIN: Added by liurui id:40632, 2006/7/26   PN:A32D03975 */

VOS_VOID GMM_CasNetModeChangeByRau(
                GMM_NETMODE_CHG_TYPE ucNetChgTyp,
                VOS_UINT8            ucRaiChgFlg)
{
    VOS_UINT8                           ucSimCsRegStatus;
    VOS_UINT8                           ucCsAttachAllow;

    ucSimCsRegStatus = NAS_MML_GetSimCsRegStatus();
    ucCsAttachAllow  = NAS_MML_GetCsAttachAllowFlg();

    switch (g_GmmGlobalCtrl.ucState)
    {
    case GMM_REGISTERED_NORMAL_SERVICE:
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE:
    case GMM_REGISTERED_LIMITED_SERVICE:
    case GMM_REGISTERED_UPDATE_NEEDED:
    case GMM_REGISTERED_NO_CELL_AVAILABLE:
    case GMM_REGISTERED_PLMN_SEARCH:
        Gmm_TimerStop(GMM_TIMER_T3311);
        Gmm_TimerStop(GMM_TIMER_T3302);

        if ((GMM_NETMODE_CHG_I_II == ucNetChgTyp)
          ||(GMM_NETMODE_CHG_I_III == ucNetChgTyp)
          ||(GMM_NETMODE_CHG_II_III == ucNetChgTyp)
          ||(GMM_NETMODE_CHG_III_II == ucNetChgTyp))
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_RA_UPDATING);
        }
        else if ((GMM_NETMODE_CHG_II_I == ucNetChgTyp)
          ||(GMM_NETMODE_CHG_III_I == ucNetChgTyp))
        {
            if ((VOS_TRUE != ucSimCsRegStatus)
             || (VOS_FALSE == ucCsAttachAllow))
            {
                Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
            }
            else
            {
                Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);
            }
        }
        else
        {
        }

        break;

    case GMM_REGISTERED_IMSI_DETACH_INITIATED:
        Gmm_TimerStop(GMM_TIMER_T3321);
        Gmm_TimerStop(GMM_TIMER_PROTECT);
        Gmm_TimerStop(GMM_TIMER_T3318);
        Gmm_TimerStop(GMM_TIMER_T3320);
        g_GmmReqCnfMng.ucCnfMask = 0;

        if ((GMM_NETMODE_CHG_I_II == ucNetChgTyp)
          ||(GMM_NETMODE_CHG_I_III == ucNetChgTyp)
          ||(GMM_NETMODE_CHG_II_III == ucNetChgTyp)
          ||(GMM_NETMODE_CHG_III_II == ucNetChgTyp))
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_RA_UPDATING);
        }
        else if ((GMM_NETMODE_CHG_II_I == ucNetChgTyp)
          ||(GMM_NETMODE_CHG_III_I == ucNetChgTyp))
        {
            if ((VOS_TRUE != ucSimCsRegStatus)
             || (VOS_FALSE == ucCsAttachAllow))
            {
                Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
            }
            else
            {
                Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);
            }
        }
        else
        {
        }
        break;

    case GMM_SERVICE_REQUEST_INITIATED:
        Gmm_TimerStop(GMM_TIMER_T3311);
        Gmm_TimerStop(GMM_TIMER_T3302);
        Gmm_TimerStop(GMM_TIMER_T3317);
        Gmm_TimerStop(GMM_TIMER_PROTECT);
        Gmm_TimerStop(GMM_TIMER_T3318);
        Gmm_TimerStop(GMM_TIMER_T3320);
        g_GmmReqCnfMng.ucCnfMask = 0;
        if ((GMM_SERVICE_REQUEST_DATA_IDLE == g_GmmGlobalCtrl.ucSpecProc)
         || (GMM_SERVICE_REQUEST_DATA_CONN == g_GmmGlobalCtrl.ucSpecProc))
        {/* ��ǰ����ΪSR_DATA */
            g_GmmGlobalCtrl.ucSpecProcHold = g_GmmGlobalCtrl.ucSpecProc;        /* �������жϵ�SR����                       */
            g_GmmGlobalCtrl.ucFollowOnFlg = GMM_TRUE;                           /* ����follow on��־                        */
            NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);
        }

        if ((GMM_NETMODE_CHG_I_II == ucNetChgTyp)
          ||(GMM_NETMODE_CHG_I_III == ucNetChgTyp)
          ||(GMM_NETMODE_CHG_II_III == ucNetChgTyp)
          ||(GMM_NETMODE_CHG_III_II == ucNetChgTyp))
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_RA_UPDATING);
        }
        else if ((GMM_NETMODE_CHG_II_I == ucNetChgTyp)
          ||(GMM_NETMODE_CHG_III_I == ucNetChgTyp))
        {
            if ((VOS_TRUE !=  ucSimCsRegStatus)
             || (VOS_FALSE == ucCsAttachAllow))
            {
                Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
            }
            else
            {
                Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);
            }
        }
        else
        {
        }

        break;

    case GMM_ROUTING_AREA_UPDATING_INITIATED:
        /* ��ǰRAU��ֹ�����µ�RAU */
        Gmm_TimerStop(GMM_TIMER_T3330);
        Gmm_TimerStop(GMM_TIMER_T3318);
        Gmm_TimerStop(GMM_TIMER_T3320);
        if ((GMM_NETMODE_CHG_I_II == ucNetChgTyp)
          ||(GMM_NETMODE_CHG_I_III == ucNetChgTyp)
          ||(GMM_NETMODE_CHG_II_III == ucNetChgTyp)
          ||(GMM_NETMODE_CHG_III_II == ucNetChgTyp))
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_RA_UPDATING);
        }
        else if ((GMM_NETMODE_CHG_II_I == ucNetChgTyp)
          ||(GMM_NETMODE_CHG_III_I == ucNetChgTyp))
        {
            if ((VOS_TRUE !=  ucSimCsRegStatus)
             || (VOS_FALSE == ucCsAttachAllow))
            {
                Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
            }
            else
            {
                Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);

            }
        }
        else
        {
        }

        break;

    case GMM_REGISTERED_INITIATED:

        if (GMM_FALSE == ucRaiChgFlg)
        {/* RAδ�ı䣬��ǰRAU��ɺ��ٷ����µ�RAU */
            g_GmmGlobalCtrl.MsgHold.ucHandleRauFlg = GMM_TRUE;
            return;
        }
        /* RA�ı䣬��ǰRAU��ֹ�����µ�RAU */
        Gmm_TimerStop(GMM_TIMER_T3310);
        Gmm_TimerStop(GMM_TIMER_T3318);
        Gmm_TimerStop(GMM_TIMER_T3320);
        NAS_MML_SetPsAttachAllowFlg( VOS_TRUE );      /* ����ע�������־ */
        Gmm_AttachInitiate(GMM_NULL_PROCEDURE);

        break;

    case GMM_DEREGISTERED_INITIATED:

        Gmm_TimerStop(GMM_TIMER_T3321);                                         /* ͣT3321                                  */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* ֹͣT3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* ֹͣT3320                                */

        if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
            == (g_GmmReqCnfMng.ucCnfMask
            & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
        {                                                                       /* �ȴ���Ȩ��Ӧ                             */
            Gmm_TimerStop(GMM_TIMER_PROTECT);                                   /* ͣ������ʱ��                             */
            g_GmmReqCnfMng.ucCnfMask
                &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;                      /* ���ԭ��ȴ���־                         */
        }

        g_GmmGlobalCtrl.ucFollowOnFlg = GMM_TRUE;
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

        g_GmmGlobalCtrl.ucSpecProcHold = g_GmmGlobalCtrl.ucSpecProc;

        if ((GMM_NETMODE_CHG_I_II == ucNetChgTyp)
         || (GMM_NETMODE_CHG_I_III == ucNetChgTyp)
         || (GMM_NETMODE_CHG_II_III == ucNetChgTyp)
         || (GMM_NETMODE_CHG_III_II == ucNetChgTyp))
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_RA_UPDATING);
        }
        else if ((GMM_NETMODE_CHG_II_I == ucNetChgTyp)
          ||(GMM_NETMODE_CHG_III_I == ucNetChgTyp))
        {
            if ((VOS_TRUE !=  ucSimCsRegStatus)
             || (VOS_FALSE == ucCsAttachAllow))
            {
                Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
            }
            else
            {
                Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);
            }
        }
        else
        {
        }

        break;

    case GMM_DEREGISTERED_NORMAL_SERVICE:
    case GMM_DEREGISTERED_PLMN_SEARCH:
    case GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH:
    case GMM_DEREGISTERED_ATTACH_NEEDED:
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING,
            "GMM_CasNetModeChangeByRau:WARNING: not surpport NetMode Change!");
        break;

    default:
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING,
               "GMM_CasNetModeChangeByRau:WARNING: g_GmmGlobalCtrl.ucState is Error");
        break;
    }
    return;
}


VOS_UINT8 GMM_CasGetNetChgType(VOS_UINT8 ucNewNetMod)
{
    GMM_NETMODE_CHG_TYPE   ucNetChgType = GMM_NETMODE_CHG_NULL;

    if (GMM_NET_MODE_I == g_GmmGlobalCtrl.SysInfo.ucNetMod)
    {
        if (GMM_NET_MODE_II == ucNewNetMod)
        {
            ucNetChgType = GMM_NETMODE_CHG_I_II;
        }
        else if (GMM_NET_MODE_III == ucNewNetMod)
        {
            ucNetChgType = GMM_NETMODE_CHG_I_III;
        }
        else
        {
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING,
                    "GMM_CasGetNetChgType:WARNING: New Netmode is incorrect!");
        }
    }
    else if (GMM_NET_MODE_II == g_GmmGlobalCtrl.SysInfo.ucNetMod)
    {
        if (GMM_NET_MODE_I == ucNewNetMod)
        {
            ucNetChgType = GMM_NETMODE_CHG_II_I;
        }
        else if (GMM_NET_MODE_III == ucNewNetMod)
        {
            ucNetChgType = GMM_NETMODE_CHG_II_III;
        }
        else
        {
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING,
                    "GMM_CasGetNetChgType:WARNING: New Netmode is incorrect!");
        }
    }
    else if (GMM_NET_MODE_III == g_GmmGlobalCtrl.SysInfo.ucNetMod)
    {
        if (GMM_NET_MODE_I == ucNewNetMod)
        {
            ucNetChgType = GMM_NETMODE_CHG_III_I;
        }
        else if (GMM_NET_MODE_II == ucNewNetMod)
        {
            ucNetChgType = GMM_NETMODE_CHG_III_II;
        }
        else
        {
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING,
                    "GMM_CasGetNetChgType:WARNING: New Netmode is incorrect!");
        }
    }
    else
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING,
                    "GMM_CasGetNetChgType:WARNING: Old Netmode is incorrect!");
    }

    return ucNetChgType;
}


VOS_VOID GMM_ProcedureByNetMode(VOS_UINT8 ucNetModChangeType)
{
    if (GMM_NETMODE_CHG_I_II == ucNetModChangeType)
    {
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
    }
    else if ((GMM_NETMODE_CHG_I_III == ucNetModChangeType)
          || (GMM_NETMODE_CHG_II_III == ucNetModChangeType))
    {
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
    }
    else if (GMM_NETMODE_CHG_II_I == ucNetModChangeType)
    {
        if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
         && (GMM_FALSE == g_GmmGlobalCtrl.CsInfo.ucCsTransFlg))
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);
        }
        else
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
        }
    }
    else if (GMM_NETMODE_CHG_III_I == ucNetModChangeType)
    {
        if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
         && (GMM_FALSE == g_GmmGlobalCtrl.CsInfo.ucCsTransFlg))
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);
        }
        else
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
        }
    }
    else if (GMM_NETMODE_CHG_III_II == ucNetModChangeType)
    {
        if (NAS_MML_MS_MODE_PS_ONLY == NAS_MML_GetMsMode())
        {
            Gmm_AttachInitiate(GMM_NULL_PROCEDURE);
        }
        else
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
        }
    }
    else
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING,
                    "GMM_ProcedureByNetMode:WARNING: Netmode change type is incorrect!");
    }
}


VOS_VOID GMM_CasChangSysMode(VOS_UINT8 ucState)
{
    /* BEGIN: Deleted by liurui id:40632, 2006/4/10   PN:A32D02830 */
    /* �����������ģʽ��ͬ�������ı䴦�� */
    /*if (ulState == gstGmmCasGlobalCtrl.ulGmmCasPreState)*/
    /*{*/
    /*    return;*/
    /*}*/
    /* END:   Deleted by liurui id:40632, 2006/4/10   PN:A32D02830 */

    /* ��ģʽ��ϵͳ״̬������ʼ�� */
    if (NAS_MML_NET_RAT_TYPE_GSM == ucState)
    {/* �л���2G����ģʽ */
        /* ϵͳCAS״̬ά�� */
        gstGmmCasGlobalCtrl.ucGmmCasPreState
                    = gstGmmCasGlobalCtrl.ucGmmCasState;
        gstGmmCasGlobalCtrl.ucGmmCasState
                    = GMM_CAS_GSM_AS;

        /* TLLI��ʼ�� */
        gstGmmCasGlobalCtrl.ulTLLI    = 0xffffffff;         /* ��ЧTLLIֵ */
        gstGmmCasGlobalCtrl.ulOldTLLI = 0xffffffff;         /* ��ЧTLLIֵ */
        /* BEGIN: Modified by liurui id:40632, 2006/3/4   PN:A32D02288*/
        gstGmmCasGlobalCtrl.ucflgTLLI = GMM_INVALID_TLLI;   /* ��TLLI��Ч��־ */
        gstGmmCasGlobalCtrl.ucTlliAssignFlg = GMM_FALSE;    /* δ���TLLIָ�� */
        /* END:   Modified by liurui id:40632, 2006/3/4 */

        /* READY TIMER��ʼ�� */
        /*gstGmmCasGlobalCtrl.ulReadyTimerValue
            = GMM_TIMER_T3314_VALUE * GMM_TIMER_T3314_CNT*/;                      /* Ĭ��ֵ */
        /*gstGmmCasGlobalCtrl.ulReadyTimerCntMax = GMM_TIMER_T3314_CNT*/;           /* Ĭ��ֵ */
        /* gstGmmCasGlobalCtrl.ulReadyTimerCnt    = 0;  */       /* ���������� */
        gstGmmCasGlobalCtrl.ucReadyTimerNgtFlg = GMM_FALSE;  /* ����Э�̱�־ */

        /* 2G���̱����ͱ�־��λ */
        gstGmmCasGlobalCtrl.ucRabmResumeFlg = GMM_FALSE;
        gstGmmCasGlobalCtrl.ucRauCmpFlg     = GMM_FALSE;
        gstGmmCasGlobalCtrl.ucGprsCipherAlg = LL_GEA0;      /* �޼����㷨 */

        NAS_GMM_SndMmcCipherInfoInd();

        gstGmmCasGlobalCtrl.ucCellNotifyFlg = GMM_FALSE;
        gstGmmCasGlobalCtrl.ucFtsFlg        = GMM_FALSE;
        gstGmmCasGlobalCtrl.ucCellUpdateFlg = GMM_FALSE;
        gstGmmCasGlobalCtrl.ucSysRauFlg     = GMM_FALSE;

        /*add,sunxibo,2006-03-03,itt begin*/
        g_GmmGlobalCtrl.ucSigConFlg         = GMM_TRUE;
        /*add,sunxibo,2006-03-03,itt end*/
    }
#if 0
    else if (GMM_CAS_WCDMA_AS == ulState)
    {/* �л���3G����ģʽ */
        /* ϵͳCAS״̬ά�� */
        gstGmmCasGlobalCtrl.ucGmmCasPreState
                    = gstGmmCasGlobalCtrl.ucGmmCasState;
        gstGmmCasGlobalCtrl.ucGmmCasState
                    = GMM_CAS_WCDMA_AS;

        /* TLLI 3G���粻ʹ�ã����ֲ��� */
        /* READY TIMER 3G���粻ʹ�ã����ֲ��� */
        /* 2G���̱����ͱ�־3G���粻ʹ�ã����ֲ��� */
        gstGmmCasGlobalCtrl.ucSysRauFlg     = GMM_FALSE;
        /* BEGIN: Added by liurui id:40632, 2006/4/12   PN:A32D02830 */
        g_GmmGlobalCtrl.ucSigConFlg         = GMM_FALSE;
        /* END:   Added by liurui id:40632, 2006/4/12   PN:A32D02830 */
    }
    else
    {/* �л���SUSPENDģʽ */
        /* ��GMM CAS״̬ */
        gstGmmCasGlobalCtrl.ucGmmCasPreState
            = gstGmmCasGlobalCtrl.ucGmmCasState;
        gstGmmCasGlobalCtrl.ucGmmCasState
            = GMM_CAS_SUSPEND;

        /* ׼��������Ϣ���棬֪ͨCM��ģ�����ָʾ */
        Gmm_TimerStart(GMM_TIMER_BUFFER_QUEUE);
        GMM_SndRabmSuspendInd();                /* ֪ͨRABM CAS������Ϣ*/
        return;
    }

    /* ����������Ϣ�󣬲���Ҫ�ϱ�RAU������Ϣ */
    if (GMM_NULL == g_GmmGlobalCtrl.ucState)
    {
        return;
    }

    /* inter-system change���RA update���� */
    GMM_CasGetRauType(&ucRauType, ulState);
    GMM_CasExecRauInSysChg(ucRauType);
#endif

    gstGmmCasGlobalCtrl.ucGprsCipherAssign    = VOS_FALSE;  /* �����㷨û��֧�� */
    gstGmmCasGlobalCtrl.ucGprsCipher          = VOS_FALSE;

    NAS_GMM_SndMmcCipherInfoInd();

    return;
}

/**************************************/
/* �����ⲿģ��(RABM,APS)���ýӿ�     */
/**************************************/

VOS_UINT8 GMM_GetCurNetwork (VOS_VOID)
{
    /* ��ȷ���������ģʽ */
    if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
    {
        return NAS_GMM_NET_RAT_TYPE_GSM;
    }
    else if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
    {
        return NAS_GMM_NET_RAT_TYPE_WCDMA;
    }
#if (FEATURE_ON == FEATURE_LTE)
    else if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
    {
        return NAS_GMM_NET_RAT_TYPE_LTE;
    }
#endif
    else
    {
        /* ����״̬Ĭ������ģʽΪ3G */
        return NAS_GMM_NET_RAT_TYPE_WCDMA;
    }
}

/*****************************************************************************
 Prototype      : GMM_GetTlli
 Description    : ��ȡGMM�ĵ�ǰTLLIֵ
                  HSS 4100 V200R001 ����
                  ��GMMģ��ʹ��
 Input          :
 Output         :
 Return Value   : GMM��ǰʹ�õ�TLLIֵ
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-12-08
    Author      : Roger Leo
    Modification: Created function
*****************************************************************************/
VOS_UINT32 GMM_GetTlli (VOS_VOID)
{
    return gstGmmCasGlobalCtrl.ulTLLI;
}


VOS_UINT32 GMM_ServiceStatusForSms(VOS_VOID)
{
#if (FEATURE_ON == FEATURE_LTE)
    if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
    {
        /* ��ǰפ��Lģ�������ж�GMM״̬ */
        return GMM_SMS_SERVICE_AVAILABLE;
    }
    else
#endif
    {
        if (VOS_TRUE == NAS_MML_GetPsRestrictNormalServiceFlg())
        {
            return GMM_SMS_SERVICE_UNAVAILABLE;
        }

        if ((MM_COM_SRVST_NORMAL_SERVICE == NAS_GMM_GetRegUptNeededPsSrvStatus())
         && (GMM_REGISTERED_UPDATE_NEEDED == g_GmmGlobalCtrl.ucState))
        {
            return GMM_SMS_SERVICE_UNAVAILABLE;
        }

        switch (g_GmmGlobalCtrl.ucState)
        {
            case GMM_ROUTING_AREA_UPDATING_INITIATED:
            case GMM_SERVICE_REQUEST_INITIATED:
            case GMM_REGISTERED_NORMAL_SERVICE:
            case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:
            case GMM_REGISTERED_IMSI_DETACH_INITIATED:
                return GMM_SMS_SERVICE_AVAILABLE;
            case GMM_SUSPENDED_WAIT_FOR_SYSINFO:
                /* �ڴ�G�л���W,SMS���԰�ҵ��֪ͨGMM,��GMM����һ��RAU���� */
                if ((NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
                 && (MMC_SUSPEND_CAUSE_HANDOVER == gstGmmSuspendCtrl.ucSuspendCause)
                 && (NAS_MML_NET_RAT_TYPE_GSM   == gstGmmSuspendCtrl.ucPreRat))
                {
                    return GMM_SMS_SERVICE_AVAILABLE;
                }
                else
                {
                    return GMM_SMS_SERVICE_UNAVAILABLE;
                }
            default:
                return GMM_SMS_SERVICE_UNAVAILABLE;
        }
    }
}


VOS_UINT8 GMM_GetRaPrioForSms (VOS_VOID)
{
    VOS_UINT8   ucRaPrioLevFosSms;

    ucRaPrioLevFosSms = gstGmmCasGlobalCtrl.enRaPrioLevFosSms - 1;
    return ucRaPrioLevFosSms;

}


VOS_VOID GMM_CasMsgProc_GmmSuspendNormalService(
    struct MsgCB                       *pMsg,
    VOS_UINT8                          *pucFollowOn
)
{
    /* �ֲ��������� */
    MSG_HEADER_STRU         *pNasMsgHeader;

    RRMM_DATA_IND_FOR_PCLINT_STRU  *pstRrmmDataInd          = VOS_NULL_PTR;
    NAS_MSG_FOR_PCLINT_STRU        *pstNasMsg               = VOS_NULL_PTR;
    LL_NAS_UNITDATA_IND_MSG        *pstLLUnitDataInd        = VOS_NULL_PTR;

    pstRrmmDataInd = (RRMM_DATA_IND_FOR_PCLINT_STRU *)pMsg;
    pstNasMsg      = &pstRrmmDataInd->RcvNasMsg;
    pstLLUnitDataInd = (LL_NAS_UNITDATA_IND_MSG *)pMsg;

    /* ��Ϣ�������� */
    *pucFollowOn = GMM_FALSE;                                                   /* Ĭ�ϲ��ٽ���ԭ��Ϣ��ں������� */

    pNasMsgHeader = (MSG_HEADER_STRU*)pMsg;


    if (WUEPS_PID_MMC == pMsg->ulSenderPid)
    {
        if (MMCGMM_RESUME_IND == pNasMsgHeader->ulMsgName)
        {
            GMM_LOG_INFO("GMM_CasMsgProc:Receive MMCGMM_RESUME_IND in SUSPENDED_NORMAL_SERVICE state.");
            /* ������Ϣ�ַ��������������Ϣ */
            *pucFollowOn = GMM_TRUE;
            return;
        }

        if (MMCGMM_POWER_OFF_REQ == pNasMsgHeader->ulMsgName)
        {
            GMM_BufferMsgDump();
            Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);
            *pucFollowOn = GMM_TRUE;
            return;
        }

        if (MMCGMM_DETACH_REQ == pNasMsgHeader->ulMsgName)
        {
            *pucFollowOn = GMM_TRUE;
            return;
        }


        /* �յ�MMCGMM_ATTACH_REQ��Ϣ���򲻽��л��棬����ֱ�ӻظ�Attach�ɹ���
           ������פ��������������Attach */
        if ( MMCGMM_ATTACH_REQ == pNasMsgHeader->ulMsgName )
        {
            *pucFollowOn = GMM_TRUE;
            return;
        }
    }
    else if (WUEPS_PID_WRR == pMsg->ulSenderPid)
    {
        /* ����״̬�յ�REL_IND GMM��Ҫ����:�����֪ͨMMC�������ӱ�־ */
        if (RRMM_REL_IND == pNasMsgHeader->ulMsgName)
        {
            *pucFollowOn = GMM_TRUE;
            GMM_LOG_INFO("GMM_CasMsgProc:Receive RRMM_REL_IND in SUSPENDED_NORMAL_SERVICE state.");
            return;
        }


        /* ͸����SM��ǰDATA_IND��Ϣ */
        if ( (RRMM_DATA_IND == pNasMsgHeader->ulMsgName)
          && (GMM_PD_SM     == (pstNasMsg->aucNasMsg[0] & 0x0F)) )
        {
            *pucFollowOn = GMM_TRUE;
            GMM_LOG_INFO("GMM_CasMsgProc:Receive RRMM_DATA_IND in SUSPENDED_NORMAL_SERVICE state.");
            return;
        }
    }
    else if (UEPS_PID_LL == pMsg->ulSenderPid)
    {
        /* LL͸����SM��ǰDATA_IND��Ϣ */
        if ( (ID_LL_UNITDATA_IND    == pNasMsgHeader->ulMsgName)
          && (GMM_PD_SM             == (pstLLUnitDataInd->stUnitDataInd.aucPdu[0] & 0x0F)) )
        {
            *pucFollowOn = GMM_TRUE;
            GMM_LOG_INFO("GMM_CasMsgProc:Receive ID_LL_UNITDATA_IND in SUSPENDED_NORMAL_SERVICE state.");
            return;
        }
    }

    /* ����״̬����Ҫ����LMM�İ�ȫ�����Ļظ���Ϣ */
#if (FEATURE_ON == FEATURE_LTE)
    else if (PS_PID_MM == pMsg->ulSenderPid)
    {
        if (ID_LMM_GMM_HO_SECU_INFO_CNF == pNasMsgHeader->ulMsgName)
        {
            *pucFollowOn = GMM_TRUE;
            GMM_LOG_INFO("GMM_CasMsgProc:Receive ID_LMM_GMM_HO_SECU_INFO_CNF in SUSPENDED_NORMAL_SERVICE state.");
            return;
        }
    }
#endif
    else
    {
    }

    GMM_SuspendMsgProc(pMsg, pucFollowOn);

    return;

}

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif
