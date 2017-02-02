

/*****************************************************************************
   1 ͷ�ļ�����
*****************************************************************************/
#include "GmmInc.h"
#include "GmmCasGlobal.h"
#include "GmmCasComm.h"
#include "GmmCasMain.h"
#include "GmmCasSuspend.h"
#include "GmmCasSend.h"
#include "GmmCasGsm.h"
#include "GmmMmInterface.h"
#include "GmmExt.h"
#include "NasGmmSndOm.h"
#include "NasUtranCtrlInterface.h"
#include "NasUsimmApi.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_GMM_CASGSM_C

extern VOS_VOID Gmm_RcvRoutingAreaUpdateRejectMsg_AttachFlg_Handling(VOS_VOID);


/*lint -save -e958 */

/*****************************************************************************
 Prototype      : GMM_CasCellS0E45
 Description    :
                  ����ID_LL_GMM_STATUS_IND��Ϣ����
                  HSS 4100 V200R001 ����
                  ���յ�LLC�ϱ�״̬��ϢID_LL_GMM_STATUS_IND�Ĵ���

 Input          : VOS_VOID*     pRcvMsg     �����Ϣָ��
 Output         :
 Return Value   :
 Calls          :
 Called By      :
 History        :
  1.Date        : 2005-08-25
    Author      : Roger Leo
    Modification: Created function
*****************************************************************************/
VOS_VOID GMM_CasCellS0E45(VOS_VOID *pRcvMsg)
{
    LL_GMM_STATUS_IND_MSG   *pStatusInd;

    if ((GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
        || (GMM_DEREGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
        || (GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState)
        || (GMM_TC_ACTIVE == g_GmmGlobalCtrl.ucState)
        || (0x20 == (g_GmmGlobalCtrl.ucState & 0xF0)))
    {
        /* GSMģʽ������� */
        pStatusInd = (LL_GMM_STATUS_IND_MSG*)pRcvMsg;

        /* ���TLLIֵ */
        if (gstGmmCasGlobalCtrl.ulTLLI != pStatusInd->stLlGmmStatusInd.ulTlli)
        {
            #ifdef __PS_WIN32_RECUR__
            if ((pStatusInd->stLlGmmStatusInd.ulTlli & 0xf0000000) != 0x70000000)
            {
                GMM_AssignSysTlli();                                                /* ͬ������LLC��new TLLI */
            }
            #else
                GMM_AssignSysTlli();                                                /* ͬ������LLC��new TLLI */
            #endif

        }

        if (GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState)
        {
            /*��������û�й�����Ҫ����*/
            if (GMM_NOT_SUSPEND_LLC == gstGmmCasGlobalCtrl.ucSuspendLlcCause)
            {
                GMM_SndLlcSuspendReq();
            }

            /*��GMM_ROUTING_AREA_UPDATING_INITIATED״̬��û����GMM_SUSPEND_LLC_FOR_RAU*/
            if (GMM_SUSPEND_LLC_FOR_RAU != (GMM_SUSPEND_LLC_FOR_RAU & gstGmmCasGlobalCtrl.ucSuspendLlcCause))
            {
                gstGmmCasGlobalCtrl.ucSuspendLlcCause |= GMM_SUSPEND_LLC_FOR_RAU;
            }
        }
        /* ����ucCauseԭ��ֵ */
        GMM_ExecLlgmmStatusIndCause(pStatusInd->stLlGmmStatusInd.usCause);
    }

    return;
}
VOS_VOID NAS_GMM_RcvGmmRabmRoutingAreaUpdateRsp(VOS_VOID *pRcvMsg)
{
    VOS_UINT8                                ucNum = 0;
    GMMRABM_ROUTING_AREA_UPDATE_RSP_MSG     *pRabmRauRspMsg;

    Gmm_TimerStop(GMM_TIMER_RAU_RSP);

    gstGmmCasGlobalCtrl.ucRabmRauRspRcvdFlg = VOS_TRUE;

    if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
    {
        return;
    }
    pRabmRauRspMsg = (GMMRABM_ROUTING_AREA_UPDATE_RSP_MSG*)pRcvMsg;

    /* ������Ϣ��NPDU������ */
    if (GMM_RABM_NPDU_VALID == pRabmRauRspMsg->ucNpduValidFlg)
    {
        g_GmmRauCtrl.ucNpduCnt = pRabmRauRspMsg->aucRecvNPDUNumListIE[1];
        g_GmmDownLinkNpduBake.ucNpduCnt = pRabmRauRspMsg->aucRecvNPDUNumListIE[1];
        for (ucNum=0; ucNum<g_GmmRauCtrl.ucNpduCnt; ucNum++)
        {
            g_GmmRauCtrl.aucNpduNum[ucNum] =
                pRabmRauRspMsg->aucRecvNPDUNumListIE[ucNum+2];
            g_GmmDownLinkNpduBake.aucNpduNum[ucNum] =
                pRabmRauRspMsg->aucRecvNPDUNumListIE[ucNum+2];
        }
    }
    else
    {
        g_GmmRauCtrl.ucNpduCnt = 0;     /* UE��NPDU����Ч���� */
        g_GmmDownLinkNpduBake.ucNpduCnt = 0;
    }

    /* ����Ҫ�ȴ�WRR�Ļظ���Ϣ�������Ѿ��յ�WRR�Ļظ���Ϣ������RAU���̽�������Ӧ���� */
    if (   (VOS_FALSE == g_GmmInterRatInfoCtrl.ucRauCmpWaitInterRatCnfMsg)
        || (VOS_TRUE == g_GmmInterRatInfoCtrl.ucInterRatCnfMsgRcvdFlg))
    {
        NAS_GMM_RauCompleteHandling();
    }

    return;
}
/*****************************************************************************
 Prototype      : GMM_RcvGasPagingInd
 Description    :
                  ����GRRMM_PAGING_IND��Ϣ��ڴ���
                  HSS 4100 V200R001 ����

 Input          : VOS_VOID*     pMsg     �����Ϣָ��
 Output         :
 Return Value   :
 Calls          :
 Called By      :
 History        :
  1.Date        : 2005-08-25
    Author      : Roger Leo
    Modification: Created function
*****************************************************************************/
VOS_VOID GMM_RcvGasPagingInd(VOS_VOID *pMsg)
{
    GRRMM_PAGING_IND_ST     *pIndMsg;

    if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
    {
        GMM_LOG_WARN("GMM_RcvGasPagingInd():Warning: message only use for GSM");
        return;
    }

    pIndMsg = (GRRMM_PAGING_IND_ST*)pMsg;
    /* �ж�Ѱ��������� */
    if (GAS_PAGING_CS == pIndMsg->ucPagingType)
    {/* CSѰ�� */
        return;                                                                 /* ������ֱ�ӽ��� */
    }

    switch (g_GmmGlobalCtrl.ucState)
    {
    case GMM_DEREGISTERED_INITIATED:
    case GMM_REGISTERED_IMSI_DETACH_INITIATED:
       GMM_RcvGsmPagingAtDeregInit(pIndMsg);
       break;

    case GMM_ROUTING_AREA_UPDATING_INITIATED:
       GMM_RcvGsmPagingAtRauInit(pIndMsg);
       break;

    case GMM_REGISTERED_NORMAL_SERVICE:
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:
       GMM_RcvGsmPagingAtRegNmlServ(pIndMsg);
       break;
    case GMM_REGISTERED_PLMN_SEARCH:
        GMM_RcvGsmPaging_RegPlmnSrch(pIndMsg);
        break;
    default:
       break;
    }

    return;
}
VOS_UINT32 NAS_GMM_GsmAccessBarredProcess(VOS_VOID)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8    enRatType;


    g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;
    enRatType   = NAS_MML_GetCurrNetRatType();

    if ( (VOS_TRUE == NAS_MML_GetGsmForbidFlg())
      && (NAS_MML_NET_RAT_TYPE_GSM == enRatType))
    {
        Gmm_ComStaChg(GMM_DEREGISTERED_ATTACH_NEEDED);
        return VOS_ERR;
    }
    if ((GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
        || ((0x10 == (g_GmmGlobalCtrl.ucState & 0xF0))
        && (GMM_NULL != g_GmmGlobalCtrl.ucState)
        && (GMM_DEREGISTERED_NO_IMSI != g_GmmGlobalCtrl.ucState)))
    {                                                                       /* PS��û��ע��                             */
        Gmm_ComStaChg(GMM_DEREGISTERED_ATTACH_NEEDED);
        return VOS_ERR;
    }
    else if (GMM_REGISTERED_IMSI_DETACH_INITIATED == g_GmmGlobalCtrl.ucState)
    {
        Gmm_TimerStop(GMM_TIMER_T3321);                                     /* ͣT3321                                  */
        Gmm_ComStaChg(GMM_REGISTERED_UPDATE_NEEDED);

        /* �жϵȴ���־�Ƿ���ڣ������������MMC,MM����DETACH��Ϣ */
        if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
        {
            NAS_GMM_SndMmcMmDetachInfo();
        }
        return VOS_ERR;
    }
    else if (GMM_DEREGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
    {
        Gmm_TimerStop(GMM_TIMER_T3321);                                     /* ͣT3321                                  */
        NAS_MML_SetPsAttachAllowFlg(VOS_FALSE);
        Gmm_ComStaChg(GMM_DEREGISTERED_ATTACH_NEEDED);

        Gmm_ClearLlcData(LL_GMM_CLEAR_DATA_TYPE_ALL);                       /* ȥָ��TLLI���ͷ�LLC������ */
        Gmm_TimerStop(GMM_TIMER_T3314);
        gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_IDLE;
        gstGmmCasGlobalCtrl.ulReadyTimerValue = 44000;


#if (FEATURE_LTE == FEATURE_ON)
        if (GMM_TIMER_T3312_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3312_FLG))
        {
            NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_STOP);
        }
#endif
        Gmm_TimerStop(GMM_TIMER_T3312);
        NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_GSM_GMM_STATE);
        if (GMM_UEID_P_TMSI_SIGNATURE
            == (g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask & GMM_UEID_P_TMSI_SIGNATURE))
        {                                                                           /* DETACH�ɹ���ʹ����P_TMSI_SIGNATURE       */
            g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask &= ~GMM_UEID_P_TMSI_SIGNATURE;   /* ���P_TMSI_SIGNATURE                     */

            NAS_MML_InitUeIdPtmsiSignatureInvalid();
            /* Modified by h00313353 for iteration 9, 2015-2-4, begin */
            if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
            {
                Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* ����SIM����Ϣ                            */
            }
            else
            {
                Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
            }
            /* Modified by h00313353 for iteration 9, 2015-2-4, end */
        }

        /* �жϵȴ���־�Ƿ���ڣ������������MMC,MM����DETACH��Ϣ */
        if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
        {
            if (GMM_WAIT_PS_DETACH == (g_GmmGlobalCtrl.stDetachInfo.enDetachType & GMM_WAIT_PS_DETACH))
            {
                NAS_MML_SetPsAttachAllowFlg(VOS_FALSE);
            }
            NAS_GMM_SndMmcMmDetachInfo();
        }
        else
        {
            /* �յ������ȥע��ɹ�����Ҫ֪ͨMM������MM������T3212��ʱ�� */
            NAS_GMM_SndMmGprsDetachComplete();
        }

        return VOS_ERR;
    }
    else if ((GMM_NULL != g_GmmGlobalCtrl.ucState)
        && (GMM_DEREGISTERED_NO_IMSI != g_GmmGlobalCtrl.ucState))
    {
        Gmm_ComStaChg(GMM_REGISTERED_UPDATE_NEEDED);
        return VOS_ERR;
    }
    else
    {
    }

    return VOS_OK;
}


VOS_UINT32 NAS_GMM_GasSysInfoPreCheck(VOS_VOID *pMsg)
{
    MMCGMM_GSM_SYS_INFO_IND_ST  *pSysInfoMsg;
    VOS_UINT32                  ulResult;
    VOS_UINT8                           ucSimPsRegStatus;

    pSysInfoMsg = (MMCGMM_GSM_SYS_INFO_IND_ST *)pMsg;

    Gmm_SndSmSysInfoInd(pSysInfoMsg->ucSgsnRelease);

    gstGmmCasGlobalCtrl.ucCellReselFlg = VOS_FALSE;

    ucSimPsRegStatus = NAS_MML_GetSimPsRegStatus();

    if ( (VOS_TRUE == ucSimPsRegStatus)
      && (MMC_GMM_NO_FORBIDDEN == pSysInfoMsg->ulForbiddenFlg) )
    {
        if ((RRC_NAS_ACCESS_RESTRICTION_NORMAL_SERVICE  == pSysInfoMsg->unAcInfo.ucRestrictType)
         || (RRC_NAS_ACCESS_RESTRICTION_ALL_SERVICE     == pSysInfoMsg->unAcInfo.ucRestrictType))
        {
            GMM_BufferMsgDump();

            ulResult = NAS_GMM_GsmAccessBarredProcess();
            if (VOS_ERR == ulResult)
            {

                NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED);

                return VOS_ERR;
            }
        }
    }

    /* ����������Ϣ���޸Ĳ�����־ */
    if (GMM_FAILURE == GMM_SaveGsmSysInfoIndMsgPara(pSysInfoMsg))
    {
        GMM_LOG_NORM("GMM_RcvGasSysInfoInd():Normal: Sys info handle finish in GMM_SaveGsmSysInfoIndMsgPara.");
        return VOS_ERR;
    }

    if ((GMM_REGISTERED_PLMN_SEARCH == g_GmmGlobalCtrl.ucState)
        || (GMM_DEREGISTERED_PLMN_SEARCH == g_GmmGlobalCtrl.ucState))
    {
        NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_PTMSI_RAI);
    }

    if ((GMM_REGISTERED_PLMN_SEARCH == g_GmmGlobalCtrl.ucState)
        && (GMM_TRUE == g_GmmGlobalCtrl.ucCvrgAreaLostFlg))
    {
        if(GMM_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
        {
            g_GmmGlobalCtrl.ucNeedChgServiceStatus = VOS_FALSE;
        }
        Gmm_ComStaChg(GMM_REGISTERED_NO_CELL_AVAILABLE);
        g_GmmGlobalCtrl.ucNeedChgServiceStatus = VOS_TRUE;
    }

    return VOS_OK;
}


VOS_VOID NAS_GMM_GasSysInfoDistribute(VOS_VOID *pMsg)
{
    switch (g_GmmGlobalCtrl.ucState)
    {
    case GMM_DEREGISTERED_NORMAL_SERVICE:
    case GMM_DEREGISTERED_LIMITED_SERVICE:
    case GMM_DEREGISTERED_ATTACH_NEEDED:
    case GMM_DEREGISTERED_NO_CELL_AVAILABLE:
    case GMM_DEREGISTERED_PLMN_SEARCH:
       GMM_CasCellS1E49(pMsg);
       break;

    case GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH:
       GMM_CasCellS4E49(pMsg);
       break;

    case GMM_REGISTERED_INITIATED:
       GMM_CasCellS8E49(pMsg);
       break;

    case GMM_REGISTERED_NORMAL_SERVICE:
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:
       GMM_CasCellS9E49(pMsg);
       break;

    case GMM_REGISTERED_LIMITED_SERVICE:
    case GMM_REGISTERED_PLMN_SEARCH:
       GMM_CasCellS10E49(pMsg);
       break;

    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE:
       GMM_CasCellS11E49(pMsg);
       break;

    case GMM_REGISTERED_UPDATE_NEEDED:
    case GMM_REGISTERED_NO_CELL_AVAILABLE:
       NAS_GMM_EnterCovery(pMsg);
       break;

    case GMM_REGISTERED_IMSI_DETACH_INITIATED:
    case GMM_DEREGISTERED_INITIATED:
       GMM_CasCellS18E49(pMsg);
       break;

    case GMM_ROUTING_AREA_UPDATING_INITIATED:
       GMM_CasCellS19E49(pMsg);
       break;
    case GMM_SUSPENDED_WAIT_FOR_SYSINFO:
       GMM_RcvGasSysInfoInd_SuspWaitSys(pMsg);
       break;
    default:
       break;
    }

    return;
}


VOS_VOID GMM_RcvGasSysInfoInd(VOS_VOID *pMsg)
{
    VOS_UINT32                          ulRestul;
    VOS_UINT8                           ucSimPsRegStatus;

    NAS_MML_CONN_STATUS_INFO_STRU      *pstConnStatus;

    VOS_UINT8                           ucPsAttachAllowFlg;

    MMCGMM_GSM_SYS_INFO_IND_ST         *pSysInfo;

#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulT3423StatuChgNeedRegFlg;
    VOS_UINT32                          ulIsNeedDeactiveIsrFlg;
    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRplmnCfgInfo;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrNetType;

    pstRplmnCfgInfo           = NAS_MML_GetRplmnCfg();
    enCurrNetType             = NAS_MML_GetCurrNetRatType();
    ulT3423StatuChgNeedRegFlg = NAS_GMM_IsT3423StatusChangeNeedRegist(NAS_MML_GetLteCsServiceCfg(),
                                 NAS_MML_GetTinType(), NAS_MML_GetT3423Status());
#endif

    pstConnStatus       = NAS_MML_GetConnStatus();

    NAS_GMM_LogGmmCtxInfo();

    /* ͣHO�ȴ�ϵͳ��Ϣ��ʱ�� */
    Gmm_TimerStop(GMM_TIMER_HO_WAIT_SYSINFO);

    /* ���CS���ڽ������ӻ��������Ѿ������ɹ� */
    pSysInfo           = (MMCGMM_GSM_SYS_INFO_IND_ST *)pMsg;
    ucPsAttachAllowFlg = NAS_MML_GetPsAttachAllowFlg();

    /* PS���Է���ע��ʱ����Ҫ����ϵͳ��Ϣ */
    if ((VOS_FALSE == NAS_MML_GetPsRestrictRegisterFlg())
     && (0 != pSysInfo->ucGprsSupportInd)
     && (MMCGMM_GSM_NO_FORBIDDEN == pSysInfo->ulForbiddenFlg)
     && (VOS_TRUE  == ucPsAttachAllowFlg))
    {
        if (VOS_TRUE == pstConnStatus->ucCsSigConnStatusFlg)
        {
            /* RR���Ӳ����ڱ�ʾCS���ڽ�������,��ʱ����ϵͳ��Ϣ */
            if (VOS_FALSE == pstConnStatus->ucRrcStatusFlg)
            {
                NAS_GMM_SaveGsmSysInfo((MMCGMM_GSM_SYS_INFO_IND_ST*)pMsg);
            }
            return;
        }
    }

#if (FEATURE_ON == FEATURE_LTE)
    if (GMM_REGISTERED_PLMN_SEARCH == g_GmmGlobalCtrl.ucState)
    {
        /* L�¶�����������GU����Ҫ�ж������ISR����󼤻��pdp�����ģ���Ҫȥ����ISR*/
        ulIsNeedDeactiveIsrFlg = NAS_GMM_IsNeedDeactiveIsr_InterSys(gstGmmSuspendCtrl.ucPreRat, enCurrNetType, MMC_SUSPEND_CAUSE_BUTT);

        if (VOS_TRUE == ulIsNeedDeactiveIsrFlg)
        {
            NAS_GMM_WriteTinInfoNvim(NAS_MML_TIN_TYPE_GUTI, pstRplmnCfgInfo->aucLastImsi);

            /* ISRȥ�����Ҫ����pdp��������ISR����ǰ����� */
            NAS_MML_UpdateAllPsBearIsrFlg(NAS_MML_PS_BEARER_EXIST_BEFORE_ISR_ACT);
        }
    }
#endif

    ulRestul = NAS_GMM_GasSysInfoPreCheck(pMsg);

    if (VOS_ERR == ulRestul)
    {
        /* ϵͳ��Ϣ������ͷŻ����ϵͳ��Ϣ */
        NAS_GMM_FreeGsmSysInfo();

        gstGmmSuspendCtrl.ucPreRat = NAS_MML_NET_RAT_TYPE_GSM;
        return;
    }

    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {
        /*  suspend�������յ�T3312��ʱ����GPRS NOT SUPPORT,�����ٽ���suspend�Ĵ���ת��ΪexpiredFlag */
        if (GMM_T3312_TIMEOUT == gstGmmSuspendCtrl.ucT3312State)
        {
            g_GmmRauCtrl.ucT3312ExpiredFlg = GMM_TRUE;
            gstGmmSuspendCtrl.ucT3312State = GMM_T3312_NOT_TIMEOUT;
        }
    }

    /* ��ѡ��PS��BARRED��С��,������ģʽI,����T3312��ʱ */
    if (VOS_TRUE == NAS_MML_GetPsRestrictRegisterFlg())
    {
        /*  suspend�������յ�T3312��ʱ����PS barred,�����ٽ���suspend�Ĵ���ת��ΪexpiredFlag */
        if (GMM_T3312_TIMEOUT == gstGmmSuspendCtrl.ucT3312State)
        {
            g_GmmRauCtrl.ucT3312ExpiredFlg = GMM_TRUE;
            gstGmmSuspendCtrl.ucT3312State = GMM_T3312_NOT_TIMEOUT;
        }

        if ((VOS_TRUE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg)
          && (GMM_TRUE == g_GmmRauCtrl.ucT3312ExpiredFlg))
        {
            NAS_GMM_SndMmLuInitiation(GMMMM_T3312_EXPIRED);
        }
#if (FEATURE_ON == FEATURE_LTE)
        else if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
              && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod)
              && (VOS_TRUE == ulT3423StatuChgNeedRegFlg))
        {
            NAS_GMM_SndMmLuInitiation(GMMMM_T3412OrT3423_EXPIRED);
        }
        else
        {
        }
#endif
    }

    NAS_GMM_GasSysInfoDistribute(pMsg);

    /* ϵͳ��Ϣ������ͷŻ����ϵͳ��Ϣ */
    NAS_GMM_FreeGsmSysInfo();

    gstGmmSuspendCtrl.ucPreRat = NAS_MML_NET_RAT_TYPE_GSM;

    if ((GMM_AGB_GPRS_READY == gstGmmCasGlobalCtrl.GmmSrvState)
        && (GMM_ROUTING_AREA_UPDATING_INITIATED != g_GmmGlobalCtrl.ucState))
    {
        if (GMM_TRUE == gstGmmCasGlobalCtrl.ucCellUpdateFlg)
        {
            NAS_GMM_InitCellUpdate_RcvSysInfo(GMM_FALSE);                                               /* С������ */
            gstGmmCasGlobalCtrl.ucCellUpdateFlg = GMM_FALSE;
        }
    }

    /*  ��ȡSIM��PS�Ƿ���Ч��־ */
    ucSimPsRegStatus = NAS_MML_GetSimPsRegStatus();

    if (VOS_TRUE != ucSimPsRegStatus)
    {
        g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;
        /* ��MMC����PSע���� */
        NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                     GMM_MMC_ACTION_RESULT_FAILURE,
                                     NAS_MML_REG_FAIL_CAUSE_SIM_INVALID);

        g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;
        return;
    }

    /*�յ�ϵͳ��Ϣ��������С����ѡ������Ҳ������out of service֮�������ѵ���
      ������3G��ѡ��2G��������CSҵ����3G���ͷţ�ֻ��RAI���ı䣬������ǰ��������2������ָʾresume*/
    if (GMM_NOT_SUSPEND_LLC != gstGmmCasGlobalCtrl.ucSuspendLlcCause)
    {
        if (GMM_SUSPEND_LLC_FOR_RAU != (GMM_SUSPEND_LLC_FOR_RAU & gstGmmCasGlobalCtrl.ucSuspendLlcCause))
        {
            GMM_SndLlcResumeReq(LL_GMM_RESUME_TYPE_ALL);
            gstGmmCasGlobalCtrl.ucSuspendLlcCause = GMM_NOT_SUSPEND_LLC;
        }
        else
        {
            gstGmmCasGlobalCtrl.ucSuspendLlcCause = GMM_SUSPEND_LLC_FOR_RAU;
        }
    }

    /* �յ�Gģϵͳ��Ϣ, ָʾRABM��ǰϵͳģʽ, �����Ƿ�֧��GPRS, �����ָ�RABM */
    if ((VOS_TRUE == NAS_MML_GetPsRestrictNormalServiceFlg())
     || (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
     || (GMM_FALSE == gstGmmCasGlobalCtrl.ucTlliAssignFlg))
    {
        /* ��֧��GPRS��PS bar����û��ָ�ɲ�2, ����RABM, bRatChangeFlgΪFALSE
           û��ָ�ɲ�2ʱ���������RABM��RABM����SN�������ݣ�SN�ᷢ�͵�LLC��
           ��LLC��δָ������½��յ����ݻ��ͷ��ڴ浼�½������,��������С���Ὣ��Ϣ���й��� */
        NAS_GMM_SndRabmSysSrvChgInd(NAS_MML_NET_RAT_TYPE_GSM,
                                    VOS_FALSE,
                                    VOS_TRUE,
                                    VOS_TRUE);
    }
    else
    {
        /* ֧��GPRS, �ָ�RABM, bRatChangeFlgΪFALSE */
        NAS_GMM_SndRabmSysSrvChgInd(NAS_MML_NET_RAT_TYPE_GSM,
                                    VOS_FALSE,
                                    VOS_FALSE,
                                    VOS_TRUE);
    }

    return;
}
VOS_VOID GMM_CasCellS1E49(VOS_VOID *pRcvMsg)
{
    MMCGMM_GSM_SYS_INFO_IND_ST         *pSysInfo;
    VOS_UINT8                           ucLaiChgFlg;
    VOS_UINT8                           ucRaiChgFlg;

    pSysInfo    = (MMCGMM_GSM_SYS_INFO_IND_ST*)pRcvMsg;
    ucLaiChgFlg = gstGmmCasGlobalCtrl.TempMsgPara.ucLaiChgFlg;
    ucRaiChgFlg = gstGmmCasGlobalCtrl.TempMsgPara.ucRaiChgFlg;

    if (VOS_TRUE != NAS_MML_GetSimPsRegStatus())
    {                                                                           /* ԭ��SIM��Ч                              */
        g_GmmGlobalCtrl.ucCvrgAreaLostFlg = GMM_FALSE;                          /* �������������־                         */

        GMM_CasFsmStateChangeTo(GMM_DEREGISTERED_NO_IMSI);

        g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;

        /* ��MMC����PSע���� */
        NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                     GMM_MMC_ACTION_RESULT_FAILURE,
                                     NAS_MML_REG_FAIL_CAUSE_SIM_INVALID);
        g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;

        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_RcvMmcSysInfoInd_DeregNmlServ:NORMAL: STATUS IS GMM_DEREGISTERED_NO_IMSI");
        return;
    }

    if (VOS_FALSE == NAS_MML_GetPsAttachAllowFlg())
    {
        g_GmmGlobalCtrl.ucCvrgAreaLostFlg = GMM_FALSE;                          /* �������������־                         */
        if(MMC_GMM_NO_FORBIDDEN != pSysInfo->ulForbiddenFlg)
        {
            Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);                    /* ����״̬�Ĺ�������                       */
        }
        else
        {
            Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);                     /* ����״̬�Ĺ�������                       */
        }
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvMmcSysInfoInd_DeregNmlServ:WARNING: Not allow Attach");

        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);


        /* ��ʱ�����л����SMע��������Ϣ */
        GMM_BufferMsgResume();

        return;
    }

    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {                                                                           /* ��֧��GPRS                               */
        if ((GMM_DEREGISTERED_NO_CELL_AVAILABLE == g_GmmGlobalCtrl.ucState)
            && (GMM_FALSE == g_GmmGlobalCtrl.ucCvrgAreaLostFlg))
        {                                                                       /* ǰһ��С��Ҳ��֧��GPRS                   */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvMmcSysInfoInd_DeregNmlServ:WARNING: Not support GPRS and No cell available");
            NAS_GMM_CnfSmNotAttach(GMM_SM_CAUSE_GPRS_NOT_SUPPORT);
            NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);
            return;
        }
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* ͣT3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* ͣT3302                                  */
        g_GmmGlobalCtrl.ucCvrgAreaLostFlg = GMM_FALSE;                          /* �������������־                         */
        Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);                        /* ����״̬�Ĺ�������                       */


        if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
         && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
        {                                                                       /* A+I                                      */

            if (GMM_FALSE == ucLaiChgFlg)
            {                                                                   /* LAû��                                   */
                NAS_GMM_SndMmLuInitiation(GMMMM_NO_TIMER_EXPIRED);          /* ֪ͨMM����LU                             */
            }
        }

        NAS_GMM_CnfSmNotAttach(GMM_SM_CAUSE_GPRS_NOT_SUPPORT);


        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);


    }
    else if ( (VOS_FALSE == NAS_GMM_QryTimerStatus(GMM_TIMER_T3311))
           && (GMM_FALSE == ucRaiChgFlg)
           && (VOS_TRUE == pSysInfo->ulUserSrchFlg))
    {
        /* �û������ָ��������ǿ�Ʒ���ע�� */
        Gmm_TimerStop(GMM_TIMER_T3311);
        Gmm_TimerStop(GMM_TIMER_T3302);
        Gmm_AttachInitiate(GMM_NULL_PROCEDURE);
    }
    else if (MMCGMM_GSM_NO_FORBIDDEN != pSysInfo->ulForbiddenFlg)
    {                                                                           /* ��forbidden�б���                        */
        g_GmmGlobalCtrl.ucCvrgAreaLostFlg = GMM_FALSE;                          /* �������������־                         */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* ͣT3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* ͣT3302                                  */
        Gmm_ComForbiddenList(pSysInfo->ulForbiddenFlg);                         /* ���öԽ�ֹ�б�Ĳ���                     */

        NAS_GMM_CnfSmNotAttach(GMM_SM_CAUSE_FORBID_LA);

        NAS_GMM_SndMmcActionResultIndWhenInForbiddenList(pSysInfo->ulForbiddenFlg);

    }
    else if (GMM_TRUE == ucRaiChgFlg)
    {                                                                           /* RA�ı�                                   */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* ͣT3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* ͣT3302                                  */
        g_GmmAttachCtrl.ucAttachAttmptCnt = 0;                                  /* Attach attempt counter��0                */
        Gmm_AttachInitiate(GMM_NULL_PROCEDURE);                                                   /* ����Attach                               */
    }
    else
    {                                                                           /* С���ı�                                 */
        g_GmmGlobalCtrl.ucCvrgAreaLostFlg = GMM_FALSE;                          /* �������������־                         */
        NAS_GMM_HandleModeANOIWhenDeregister();
    }

    return;
}
VOS_VOID GMM_CasCellS4E49(VOS_VOID *pRcvMsg)
{
    MMCGMM_GSM_SYS_INFO_IND_ST *pSysInfo;
    VOS_UINT8                   ucRaiChgFlg;
    VOS_UINT8                   ucDrxLengthChgFlg;
    VOS_UINT8                   ucLaiChgFlg;

    pSysInfo          = (MMCGMM_GSM_SYS_INFO_IND_ST*)pRcvMsg;
    ucRaiChgFlg       = gstGmmCasGlobalCtrl.TempMsgPara.ucRaiChgFlg;
    ucDrxLengthChgFlg = gstGmmCasGlobalCtrl.TempMsgPara.ucDrxLengthChgFlg;
    ucLaiChgFlg       = gstGmmCasGlobalCtrl.TempMsgPara.ucLaiChgFlg;

    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {                                                                           /* ��֧��GPRS                               */
        if (GMM_TRUE == ucRaiChgFlg)
        {
            if (MMCGMM_GSM_NO_FORBIDDEN == pSysInfo->ulForbiddenFlg)
            {
                g_GmmAttachCtrl.ucAttachAttmptCnt = 0;                              /* attach attempt counter��0                */
            }
        }
        Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);                        /* ����״̬�Ĺ�������                       */
        Gmm_TimerStop(GMM_TIMER_ALL);                                           /* ͣ����Timer                              */


        if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
         && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
        {                                                                       /* A+I                                      */

            if (GMM_FALSE == ucLaiChgFlg)
            {                                                                   /* LAû��                                   */
                NAS_GMM_SndMmLuInitiation(GMMMM_NO_TIMER_EXPIRED);          /* ֪ͨMM����LU                             */
            }
        }

        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);

    }
    else if (VOS_TRUE == pSysInfo->ulUserSrchFlg)
    {
        /* �û������ָ��������ǿ�Ʒ���ע�� */
        Gmm_TimerStop(GMM_TIMER_T3311);
        Gmm_TimerStop(GMM_TIMER_T3302);
        Gmm_AttachInitiate(GMM_NULL_PROCEDURE);
    }
    else if (MMCGMM_GSM_NO_FORBIDDEN != pSysInfo->ulForbiddenFlg)
    {                                                                           /* ��forbidden�б���                        */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* ͣT3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* ͣT3302                                  */

        Gmm_ComForbiddenList(pSysInfo->ulForbiddenFlg);                        /* ���öԽ�ֹ�б�Ĳ���                     */

        NAS_GMM_SndMmcActionResultIndWhenInForbiddenList(pSysInfo->ulForbiddenFlg);


    }
    else if (GMM_TRUE == ucRaiChgFlg)
    {                                                                           /* RA�ı�                                   */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* ͣT3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* ͣT3302                                  */
        g_GmmAttachCtrl.ucAttachAttmptCnt = 0;                                  /* Attach attempt counter��0                */
        Gmm_AttachInitiate(GMM_NULL_PROCEDURE);                                                   /* ����Attach                               */
    }
    else if (GMM_TRUE == ucDrxLengthChgFlg)
    {                                                                           /* DRX�ı�                                  */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* ͣT3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* ͣT3302                                  */
        Gmm_AttachInitiate(GMM_NULL_PROCEDURE);                                                   /* ����Attach                               */
    }
    else
    {
        if ((GMM_TRUE == g_GmmAttachCtrl.ucRetryFlg)
            && (GMM_TRUE == gstGmmCasGlobalCtrl.TempMsgPara.ucGsmCellChgFlg))
        {                                                                       /* ��С����Ҫ����attach                     */
            Gmm_TimerStop(GMM_TIMER_T3311);                                     /* ͣT3311                                  */
            Gmm_TimerStop(GMM_TIMER_T3302);                                     /* ͣT3302                                  */
            Gmm_AttachInitiate(GMM_NULL_PROCEDURE);                                               /* ����Attach                               */
        }
        else
        {
            /* �����������T3302��ʱ��ʱ��Ϊ0ʱ������T3302��ʱ��������������һ���жϣ�UE��һֱ����ATTACH */
            if ((GMM_TIMER_T3302_FLG
                != (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3302_FLG))
            && ((GMM_TIMER_T3311_FLG
                != (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3311_FLG)))
            && (0 != g_GmmTimerMng.aTimerInf[GMM_TIMER_T3302].ulTimerVal))
            {
                Gmm_AttachInitiate(GMM_NULL_PROCEDURE);
            }

            else
            {
                NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE);

                if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
                 && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
                {
                    g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;

                    NAS_GMM_SndMmCombinedAttachInitiation();

                    NAS_GMM_SndMmCombinedAttachRejected(NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE_REG_MAX_TIMES);

                    g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;
                }

            }
        }
    }

    return;
}

VOS_VOID GMM_CasCellS8E49(VOS_VOID *pRcvMsg)
{
    MMCGMM_GSM_SYS_INFO_IND_ST *pSysInfo;
    VOS_UINT8                   ucRaiChgFlg;
    VOS_UINT8                   ucDrxLengthChgFlg;
    VOS_UINT8                   ucLaiChgFlg;

    pSysInfo          = (MMCGMM_GSM_SYS_INFO_IND_ST*)pRcvMsg;
    ucRaiChgFlg       = gstGmmCasGlobalCtrl.TempMsgPara.ucRaiChgFlg;
    ucDrxLengthChgFlg = gstGmmCasGlobalCtrl.TempMsgPara.ucDrxLengthChgFlg;
    ucLaiChgFlg       = gstGmmCasGlobalCtrl.TempMsgPara.ucLaiChgFlg;

    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {                                                                           /* ��֧��GPRS                               */
        g_GmmReqCnfMng.ucCnfMask = 0;                                           /* ���ԭ��ȴ���־                         */
        Gmm_TimerStop(GMM_TIMER_ALL);                                           /* ͣ����Timer                              */
        Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);                        /* ����״̬�Ĺ�������                       */
        if (GMM_TRUE == g_GmmAttachCtrl.ucSmCnfFlg)
        {
            Gmm_SndSmEstablishCnf(GMM_SM_EST_FAILURE, GMM_SM_CAUSE_GPRS_NOT_SUPPORT);    /* ֪ͨSM GMMע��ʧ��                       */

            g_GmmAttachCtrl.ucSmCnfFlg = GMM_FALSE;                             /* ��ucSmCnfFlg��־                         */
        }
        g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                        /* �嵱ǰ����                               */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcSysInfoInd_RegInit:INFO: specific procedure ended");

        if (((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
          && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
          && (GMM_FALSE == ucLaiChgFlg))
        {                                                                       /* LAû��,������A+I                         */
            NAS_GMM_SndMmLuInitiation(GMMMM_NO_TIMER_EXPIRED);          /* ֪ͨMM����LU                             */
        }


        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);

    }
    else if (MMCGMM_GSM_NO_FORBIDDEN != pSysInfo->ulForbiddenFlg)
    {                                                                           /* ��forbidden�б���                        */
        Gmm_TimerStop(GMM_TIMER_T3310);                                         /* ͣT3310                                  */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* ֹͣT3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* ֹͣT3320                                */

        if (GMM_TRUE == g_GmmAttachCtrl.ucSmCnfFlg)
        {                                                                       /* ATTACH��������SM������                   */
            Gmm_SndSmEstablishCnf(GMM_SM_EST_FAILURE, GMM_SM_CAUSE_FORBID_LA);  /* ֪ͨSM GMMע��ʧ��                       */

            g_GmmAttachCtrl.ucSmCnfFlg = GMM_FALSE;                             /* ��ucSmCnfFlg��־                         */
        }
        if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG ==
            (g_GmmReqCnfMng.ucCnfMask
                    & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
        {                                                                       /* �ȴ���Ȩ��Ӧ                             */
            Gmm_TimerStop(GMM_TIMER_PROTECT);                                   /* ͣ������ʱ��                             */
            g_GmmReqCnfMng.ucCnfMask &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG; /* ���ԭ��ȴ���־                         */
        }
        Gmm_ComForbiddenList(pSysInfo->ulForbiddenFlg);                        /* ���öԽ�ֹ�б�Ĳ���                     */


        NAS_GMM_SndMmcActionResultIndWhenInForbiddenList(pSysInfo->ulForbiddenFlg);


    }
    else if (GMM_TRUE == ucRaiChgFlg)
    {                                                                           /* RA�ı�                                   */
        Gmm_TimerStop(GMM_TIMER_T3310);                                         /* ͣT3310                                  */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* ֹͣT3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* ֹͣT3320                                */

        if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG ==
            (g_GmmReqCnfMng.ucCnfMask
                    & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
        {                                                                       /* �ȴ���Ȩ��Ӧ                             */
            Gmm_TimerStop(GMM_TIMER_PROTECT);                                   /* ͣ������ʱ��                             */
            g_GmmReqCnfMng.ucCnfMask
                &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;                      /* ���ԭ��ȴ���־                         */
        }
        Gmm_AttachInitiate(GMM_NULL_PROCEDURE);                                                   /* ����Attach                               */
    }
    else if ((GMM_TRUE == ucDrxLengthChgFlg)
        || (GMM_TRUE == gstGmmCasGlobalCtrl.ucCellUpdateFlg))
    {                                                                           /* DRX�ı�                                  */
        if (GMM_TRUE == ucDrxLengthChgFlg)
        {
            g_GmmGlobalCtrl.MsgHold.ucHandleRauFlg = GMM_TRUE;                      /* ���̽���֮�����RAU                      */
            g_GmmGlobalCtrl.MsgHold.ucInitiateLuFlg = GMM_FALSE;                    /* ���GMM���ܽ���RAUʱ����Ҫ����MM��LU���� */
        }
        if (GMM_TRUE == gstGmmCasGlobalCtrl.ucCellUpdateFlg)
        {
            GMM_SndLlcTriggerReq(LL_GMM_TRIG_CAUSE_CELUPD_CELL_NOTIFY);
            gstGmmCasGlobalCtrl.ucCellUpdateFlg = GMM_FALSE;
        }
    }
    else
    {
    }

    return;
}
VOS_VOID GMM_CasCellS9E49(VOS_VOID *pRcvMsg)
{
    MMCGMM_GSM_SYS_INFO_IND_ST *pSysInfo;
    VOS_UINT8                   ucRaiChgFlg;
    VOS_UINT8                   ucDrxLengthChgFlg;
    VOS_UINT8                   ucSimCsRegStatus;

#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulT3423StatusChgNeedRegFlg;
#endif
    NAS_MML_LAI_STRU                   *pstCsSuccLai = VOS_NULL_PTR;

    GMM_RAI_STRU                        stRai;
    VOS_UINT8                           ucCmpWithLastSucRaiChgFlg;
    VOS_UINT8                           ucCsRestrictFlg;

    pstCsSuccLai     = NAS_MML_GetCsLastSuccLai( );
    stRai.ucRac = pstCsSuccLai->ucRac;
    /* ��дLAC */
    stRai.Lai.aucLac[0] = pstCsSuccLai->aucLac[0];
    stRai.Lai.aucLac[1] = pstCsSuccLai->aucLac[1];                       /* LAC */
    /* ��дPLMN */
    stRai.Lai.PlmnId.aucMccDigit[0] =
        (VOS_UINT8)(pstCsSuccLai->stPlmnId.ulMcc & 0x0F);                           /* MCC Digit 1                              */
    stRai.Lai.PlmnId.aucMccDigit[1] =
        (VOS_UINT8)((pstCsSuccLai->stPlmnId.ulMcc >> 8) & 0x0F);                    /* MCC Digit 2                              */
    stRai.Lai.PlmnId.aucMccDigit[2] =
        (VOS_UINT8)((pstCsSuccLai->stPlmnId.ulMcc >> 16) & 0x0F);                   /* MCC Digit 3                              */
    stRai.Lai.PlmnId.aucMncDigit[0] =
        (VOS_UINT8)(pstCsSuccLai->stPlmnId.ulMnc & 0x0F);                           /* MNC Digit 1                              */
    stRai.Lai.PlmnId.aucMncDigit[1] =
        (VOS_UINT8)((pstCsSuccLai->stPlmnId.ulMnc >> 8) & 0x0F);                    /* MNC Digit 2                              */
    stRai.Lai.PlmnId.aucMncDigit[2] =
        (VOS_UINT8)((pstCsSuccLai->stPlmnId.ulMnc >> 16) & 0x0F);                   /* MNC Digit 3                              */
    stRai.Lai.PlmnId.ucMncCnt = 3;                                          /* MNC Degit count                          */
    if (GMM_PLMNID_MNC3_INVALID == stRai.Lai.PlmnId.aucMncDigit[2])
    {
        stRai.Lai.PlmnId.ucMncCnt = 2;                                      /* MNC Degit count                          */
    }
    ucCmpWithLastSucRaiChgFlg = Gmm_Compare_Rai(&stRai, &(g_GmmGlobalCtrl.SysInfo.Rai));
    ucCsRestrictFlg = NAS_MML_GetCsRestrictRegisterFlg();


    pSysInfo          = (MMCGMM_GSM_SYS_INFO_IND_ST*)pRcvMsg;
    ucRaiChgFlg       = gstGmmCasGlobalCtrl.TempMsgPara.ucRaiChgFlg;
    ucDrxLengthChgFlg = gstGmmCasGlobalCtrl.TempMsgPara.ucDrxLengthChgFlg;

#if (FEATURE_ON == FEATURE_LTE)
    ulT3423StatusChgNeedRegFlg = NAS_GMM_IsT3423StatusChangeNeedRegist(NAS_MML_GetLteCsServiceCfg(),
                                 NAS_MML_GetTinType(), NAS_MML_GetT3423Status());
#endif

    ucSimCsRegStatus = NAS_MML_GetSimCsRegStatus();

    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {                                                                           /* ��֧��GPRS                               */
        Gmm_ComStaChg(GMM_REGISTERED_LIMITED_SERVICE);                          /* ����״̬�Ĺ�������                       */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* ͣT3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* ͣT3302                                  */

        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);


    }
    else if (MMCGMM_GSM_NO_FORBIDDEN != pSysInfo->ulForbiddenFlg)
    {                                                                           /* ��forbidden�б���                        */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* ͣT3311                                  */
        Gmm_ComForbiddenList(pSysInfo->ulForbiddenFlg);                         /* ���öԽ�ֹ�б�Ĳ���                     */

        NAS_GMM_SndMmcActionResultIndWhenInForbiddenList(pSysInfo->ulForbiddenFlg);


    }
    else if (GMM_TRUE == ucDrxLengthChgFlg)
    {                                                                           /* DRX�ı�                                  */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* ͣT3311                                  */
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);               /* ����RAU                                  */
    }
#if (FEATURE_ON == FEATURE_LTE)
    else if (VOS_TRUE == ulT3423StatusChgNeedRegFlg)
    {
        NAS_GMM_RcvLmmTimerInfoNotify_RegNmlServ();
    }
#endif
    else if ((GMM_TRUE == ucRaiChgFlg)
        || (GMM_TRUE == g_GmmGlobalCtrl.ucGprsResumeFlg))
    {                                                                           /* RA�ı�                                   */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* ͣT3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);
        /*4.2.5.1.7 Substate, ATTEMPTING-TO-UPDATE-MM
        - perform routing area update indicating "combined RA/LA updating with
        IMSI attach" when the routing area of the serving cell has changed and
        the location area this cell is belonging to is not in the list of forbidden LAs.*/

        if ( (VOS_TRUE == NAS_GMM_IsAllowedCombinedAttach_GmmRegisteredAttemptingToUpdateMm())
          && (GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM == g_GmmGlobalCtrl.ucState) )
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);
        }
        else
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
        }
    }
    else if (GMM_TRUE == g_GmmRauCtrl.ucT3312ExpiredFlg)
    {
        /*�˷�֦Ԥ����G��С����ѡ������T3312��ʱʱ�Ż����*/
        /* T3311��������ʱ�ŷ���RAU */
        if (VOS_FALSE == NAS_GMM_QryTimerStatus(GMM_TIMER_T3311))
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_PERIODC_UPDATING);
        }
    }
    else if (VOS_TRUE == NAS_GMM_IsUeInfoChangeTriggerRau())
    {
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
    }
    else if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
          && (GMM_TRUE == g_GmmRauCtrl.ucCsSpringRauFlg)
          && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod)
          && (VOS_TRUE == ucSimCsRegStatus))
    {
        Gmm_TimerStop(GMM_TIMER_T3311);                                             /* ͣT3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                             /* ͣT3302                                  */
        Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);         /* ִ��RAU                                  */
        g_GmmRauCtrl.ucCsSpringRauFlg = GMM_FALSE;                                  /* ���CS����RAU�ı�־                      */
    }
    /* NMO1�����LAU�ɹ�ʱЯ����RAC�뵱ǰפ����RAC��һ��,Ҳ��ΪRAI�ı�,��Ҫ����RAU */
    else if  ((VOS_TRUE                             == NAS_MML_GetCsAttachAllowFlg())
           && (VOS_FALSE                            == ucCmpWithLastSucRaiChgFlg)
           && (GMM_NET_MODE_I                       == g_GmmGlobalCtrl.ucNetMod)
           && (VOS_TRUE                             == ucSimCsRegStatus)
           && (VOS_FALSE                            == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg)
           && (VOS_FALSE                            == ucCsRestrictFlg))
    {
        Gmm_TimerStop(GMM_TIMER_T3311);                                             /* ͣT3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                             /* ͣT3302                                  */

        Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);
    }
    else
    {
        g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;

        /* ��MMC����PSע���� */
        NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                     GMM_MMC_ACTION_RESULT_SUCCESS,
                                     NAS_MML_REG_FAIL_CAUSE_NULL);


        if ( (VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
          && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
        {
            NAS_GMM_NotifyMmUnrealCombinedRauResult();
        }


        g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;

        /* ������ڻ����PDP��������,��ô������ */
        Gmm_DealWithBuffAfterProc();
    }

    NAS_GMM_ProcSavedMmT3211ExpiredNotify();

    return;
}
VOS_VOID GMM_CasCellS10E49(VOS_VOID *pRcvMsg)
{
    MMCGMM_GSM_SYS_INFO_IND_ST         *pSysInfo;
    VOS_UINT8                           ucLaiChgFlg;
    VOS_UINT8                           ucRauFlg = GMM_TRUE;
    VOS_UINT8                           ucOldSpecProc;
    VOS_UINT8                           ucCsAttachAllow;
    VOS_UINT8                           ucCsRestrictionFlg;
     VOS_UINT8                          ucRaiChgFlg;

#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulT3423StatusChgNeedRegFlg;
    ulT3423StatusChgNeedRegFlg = NAS_GMM_IsT3423StatusChangeNeedRegist(NAS_MML_GetLteCsServiceCfg(),
                                          NAS_MML_GetTinType(), NAS_MML_GetT3423Status());

#endif

    pSysInfo    = (MMCGMM_GSM_SYS_INFO_IND_ST*)pRcvMsg;
    ucLaiChgFlg = gstGmmCasGlobalCtrl.TempMsgPara.ucLaiChgFlg;

    ucRaiChgFlg = gstGmmCasGlobalCtrl.TempMsgPara.ucRaiChgFlg;

    if ( (GMM_TRUE                   == ucRaiChgFlg)
      && (GMM_REGISTERED_PLMN_SEARCH == g_GmmGlobalCtrl.ucState))
    {
        if ( (GMM_REGISTERED_NO_CELL_AVAILABLE    == g_GmmGlobalCtrl.ucPlmnSrchPreSta)
          || (GMM_REGISTERED_ATTEMPTING_TO_UPDATE == g_GmmGlobalCtrl.ucPlmnSrchPreSta))
        {
            /* ����ATTEMPT TO UPDATE����REGISTERED_NO_CELL_AVAILABLE״̬����
               �������յ�ϵͳ��Ϣ����Ҫ���ATTEMPT COUNTER */
            if (MMCGMM_GSM_NO_FORBIDDEN == pSysInfo->ulForbiddenFlg)
            {
                g_GmmRauCtrl.ucRauAttmptCnt = 0;
            }
        }
    }

    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {                                                                           /* ��֧��GPRS                               */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* ͣT3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* ͣT3302                                  */
        Gmm_ComStaChg(GMM_REGISTERED_LIMITED_SERVICE);                          /* ����״̬�Ĺ�������                       */

        if (VOS_TRUE == NAS_GMM_IsAModeAndNetworkI())
        {                                                                       /* A+I                                      */
            if ((GMM_FALSE == ucLaiChgFlg)
             && (GMM_TRUE == g_GmmRauCtrl.ucT3312ExpiredFlg)
             && (VOS_TRUE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg))
            {                                                                   /* LAû��                                   */
                NAS_GMM_SndMmLuInitiation(GMMMM_T3312_EXPIRED);          /* ֪ͨMM����LU                             */
            }
        }


        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);

    }
    else if (VOS_TRUE == pSysInfo->ulUserSrchFlg)
    {
        /* �û������ָ��������ǿ�Ʒ���ע�� */
        Gmm_TimerStop(GMM_TIMER_T3311);
        Gmm_TimerStop(GMM_TIMER_T3302);

        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
    }
    else if (MMCGMM_GSM_NO_FORBIDDEN != pSysInfo->ulForbiddenFlg)
    {                                                                           /* ��forbidden�б���                        */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* ͣT3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* ͣT3302                                  */
        Gmm_ComForbiddenList(pSysInfo->ulForbiddenFlg);                         /* ���öԽ�ֹ�б�Ĳ���                     */

        NAS_GMM_SndMmcActionResultIndWhenInForbiddenList(pSysInfo->ulForbiddenFlg);

    }
#if (FEATURE_ON == FEATURE_LTE)
    else if (VOS_TRUE == ulT3423StatusChgNeedRegFlg)
    {
        if (GMM_REGISTERED_LIMITED_SERVICE == g_GmmGlobalCtrl.ucState)
        {
            NAS_GMM_RcvLmmTimerInfoNotify_RegLimitServ();
            return;
        }

        if (GMM_REGISTERED_PLMN_SEARCH == g_GmmGlobalCtrl.ucState)
        {
            NAS_GMM_RcvLmmTimerInfoNotify_RegNmlServ();
        }
    }
#endif
    else
    {                                                                           /* С���ı�                                 */
        /* g��attach�ɹ�lau #17 9088nv��������������hplmnʧ�ܣ�anycell�ɹ���ԭlau����С����
        gmm��gprs suspend״̬�ѵ�mmc����ָʾ��g_GmmGlobalCtrl.ucPlmnSrchPreSta����Ϊ6
        gprs suspend������������״̬�յ�gprs resume��ϵͳ��Ϣ�෢��rau*/
        if (((GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucPlmnSrchPreSta)
          || (GMM_GPRS_SUSPENSION == g_GmmGlobalCtrl.ucPlmnSrchPreSta)
          || (GMM_REGISTERED_ATTEMPTING_TO_UPDATE == g_GmmGlobalCtrl.ucPlmnSrchPreSta)
          || (GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM == g_GmmGlobalCtrl.ucPlmnSrchPreSta)
          || ((GMM_REGISTERED_NO_CELL_AVAILABLE == g_GmmGlobalCtrl.ucPlmnSrchPreSta)
             && (NAS_MML_NET_RAT_TYPE_LTE == gstGmmSuspendCtrl.ucPreRat)))
            && (GMM_REGISTERED_PLMN_SEARCH == g_GmmGlobalCtrl.ucState))
        {
            if ((GMM_FALSE == gstGmmCasGlobalCtrl.TempMsgPara.ucRaiChgFlg)
                && (GMM_FALSE == gstGmmCasGlobalCtrl.TempMsgPara.ucDrxLengthChgFlg)
                && (GMM_FALSE == g_GmmGlobalCtrl.ucGprsResumeFlg))
            {
                ucRauFlg = GMM_FALSE;
            }
        }

        ucCsAttachAllow    = NAS_MML_GetCsAttachAllowFlg();
        ucCsRestrictionFlg = NAS_MML_GetCsRestrictRegisterFlg();

        if (GMM_TRUE == ucRauFlg)
        {
            Gmm_TimerStop(GMM_TIMER_T3311);                                         /* ͣT3311                                  */
            Gmm_TimerStop(GMM_TIMER_T3302);                                         /* ͣT3302                                  */
            if ((GMM_TRUE == g_GmmRauCtrl.ucT3312ExpiredFlg)
                &&(GMM_FALSE == gstGmmCasGlobalCtrl.ucSysRauFlg))
            {
                if ((VOS_TRUE == NAS_MML_GetSimCsRegStatus())
                 && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod)
                 && (VOS_FALSE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg)
                 && (VOS_TRUE == ucCsAttachAllow)
                 && (VOS_FALSE == ucCsRestrictionFlg))
                {
                    Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
                }
                else
                {
                    Gmm_RoutingAreaUpdateInitiate(GMM_PERIODC_UPDATING);
                    g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;
                }
            }
            else
            {
                Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);               /* ����RAU                                  */
            }
        }
        else
        {
#if (FEATURE_ON == FEATURE_LTE)
            if ((NAS_MML_TIN_TYPE_RAT_RELATED_TMSI == NAS_MML_GetTinType())
             && (GMM_REGISTERED_PLMN_SEARCH == g_GmmGlobalCtrl.ucState)
             && (NAS_MML_NET_RAT_TYPE_LTE == gstGmmSuspendCtrl.ucPreRat))
            {
                NAS_GMM_IsrActiveRaiNoChg_InterSys();
            }
            else if ((NAS_MML_ROUTING_UPDATE_STATUS_UPDATED != NAS_MML_GetPsUpdateStatus())
                  && (GMM_REGISTERED_PLMN_SEARCH == g_GmmGlobalCtrl.ucState))
#else
            if ((NAS_MML_ROUTING_UPDATE_STATUS_UPDATED != NAS_MML_GetPsUpdateStatus())
                  && (GMM_REGISTERED_PLMN_SEARCH == g_GmmGlobalCtrl.ucState))
#endif
            {
                /* �����������T3302��ʱ��ʱ��Ϊ0ʱ������T3302��ʱ��������������һ���жϣ�UE��һֱ����ATTACH */
                if ((GMM_TIMER_T3302_FLG
                    != (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3302_FLG))
                && ((GMM_TIMER_T3311_FLG
                    != (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3311_FLG)))
                && (0 != g_GmmTimerMng.aTimerInf[GMM_TIMER_T3302].ulTimerVal))
                {                                                                       /* Timer3302��������                        */
                    Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);               /* ����RAU                                  */
                }
                else
                {
                    Gmm_ComStaChg(GMM_REGISTERED_ATTEMPTING_TO_UPDATE);
                    NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE);
                }

            }
            else if (GMM_TRUE == g_GmmRauCtrl.ucT3312ExpiredFlg)
            {
                Gmm_RoutingAreaUpdateInitiate(GMM_PERIODC_UPDATING);
                g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;
            }

            /*3G��ѡ����������2G���磬����RAI��ȫ��ͬ������UE֮ǰ��3G��
              �͹�������û����ݣ���ʱ��2G��PSҵ��ʱû�н���RAU������ҵ
              ��ʧ�ܣ��޸ķ�������������RAU(��Э�鲻��ȫһ�£���CCB�þ�)*/
            else if (gstGmmCasGlobalCtrl.ucLastDataSender !=
                        NAS_MML_GetCurrNetRatType())
            {
                Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
            }
            /* attahc��rau��Я����ms radio capability�Ƿ�֧��L�����������ϱ���ms radio capabitlity�Ƿ�֧��L������һ����Ҫ����Rau*/
            else if (VOS_TRUE == NAS_GMM_IsUeInfoChangeTriggerRau())
            {
                Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
            }

            else
            {
                if ((VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
                 && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod)
                 && (VOS_TRUE == ucCsAttachAllow))
                {
                    NAS_GMM_HandleModeANOIWhenRAInotChange();
                }
                else
                {
                    Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);
                    g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;
                    ucOldSpecProc = g_GmmGlobalCtrl.ucSpecProc;
                    g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_NORMAL;


                    /* ��MMC����PSע���� */
                    NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                                 GMM_MMC_ACTION_RESULT_SUCCESS,
                                                 NAS_MML_REG_FAIL_CAUSE_NULL);

                    g_GmmGlobalCtrl.ucSpecProc = ucOldSpecProc;
                    g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;
                }
            }



            if (GMM_ROUTING_AREA_UPDATING_INITIATED != g_GmmGlobalCtrl.ucState)
            {
                if (GMM_SERVICE_REQ_PAGING == g_GmmGlobalCtrl.enServReq)
                {
                    if (GMM_FALSE == gstGmmCasGlobalCtrl.ucTlliAssignFlg)
                    {
                        GMM_UpdateSysTlli(GMM_LOCAL_TLLI);
                        GMM_AssignSysTlli();
                    }

                    Gmm_TimerStop(GMM_TIMER_T3314);

#if (FEATURE_LTE == FEATURE_ON)
                    if (GMM_TIMER_T3312_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3312_FLG))
                    {
                        NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_STOP);
                    }
#endif

                    Gmm_TimerStop(GMM_TIMER_T3312);

                    if ( 0xffffffff == gstGmmCasGlobalCtrl.ulReadyTimerValue )
                    {
                        gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_READY;
#if (FEATURE_LTE == FEATURE_ON)
                    if (NAS_GMM_TIMER_T3323_FLG == (NAS_GMM_TIMER_T3323_FLG & g_GmmTimerMng.ulTimerRunMask))
                    {
                        Gmm_TimerStop(GMM_TIMER_T3323);
                    }
#endif
                    }
                    else if ( 0 == gstGmmCasGlobalCtrl.ulReadyTimerValue )
                    {
                        gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_STANDBY;
                        Gmm_TimerStart(GMM_TIMER_T3312);
                    }
                    else
                    {
                        gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_READY;
#if (FEATURE_LTE == FEATURE_ON)
                        if (NAS_GMM_TIMER_T3323_FLG == (NAS_GMM_TIMER_T3323_FLG & g_GmmTimerMng.ulTimerRunMask))
                        {
                            Gmm_TimerStop(GMM_TIMER_T3323);
                        }
#endif
                        g_GmmTimerMng.aTimerInf[GMM_TIMER_T3314].ulTimerVal
                            = gstGmmCasGlobalCtrl.ulReadyTimerValue;
                        g_GmmTimerMng.ulTimerValMask |= GMM_TIMER_T3314_FLG;
                        Gmm_TimerStart(GMM_TIMER_T3314);
                    }
                    NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_GSM_GMM_STATE);

                    GMM_SndLlcTriggerReq(LL_GMM_TRIG_CAUSE_PAG_RSP);
                }
                else if (GMM_SERVICE_REQ_PDPACT == g_GmmGlobalCtrl.enServReq)
                {
                    if (GMM_FALSE == gstGmmCasGlobalCtrl.ucTlliAssignFlg)
                    {
                        GMM_UpdateSysTlli(GMM_LOCAL_TLLI);
                        GMM_AssignSysTlli();
                    }

                    Gmm_DealWithBuffAfterProc();
                }
                else
                {
                    if (GMM_FALSE == gstGmmCasGlobalCtrl.ucTlliAssignFlg)
                    {
                        GMM_UpdateSysTlli(GMM_LOCAL_TLLI);
                        GMM_AssignSysTlli();
                    }
                }
            }
        }
    }


    g_GmmGlobalCtrl.enServReq = GMM_SERVICE_REQ_NONE;

    return;
}

VOS_VOID GMM_CasCellS11E49(VOS_VOID *pRcvMsg)
{
    MMCGMM_GSM_SYS_INFO_IND_ST         *pSysInfo;
    VOS_UINT8                           ucRaiChgFlg;
    VOS_UINT8                           ucDrxLengthChgFlg;
    VOS_UINT8                           ucLaiChgFlg;

    pSysInfo          = (MMCGMM_GSM_SYS_INFO_IND_ST*)pRcvMsg;
    ucRaiChgFlg       = gstGmmCasGlobalCtrl.TempMsgPara.ucRaiChgFlg;
    ucDrxLengthChgFlg = gstGmmCasGlobalCtrl.TempMsgPara.ucDrxLengthChgFlg;
    ucLaiChgFlg       = gstGmmCasGlobalCtrl.TempMsgPara.ucLaiChgFlg;

    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {                                                                           /* ��֧��GPRS                               */
        Gmm_ComStaChg(GMM_REGISTERED_LIMITED_SERVICE);                          /* ����״̬�Ĺ�������                       */
        Gmm_TimerStop(GMM_TIMER_ALL);                                           /* ͣ����Timer                              */
        if (GMM_TRUE == ucRaiChgFlg)
        {
            if (MMCGMM_GSM_NO_FORBIDDEN == pSysInfo->ulForbiddenFlg)
            {
                g_GmmRauCtrl.ucRauAttmptCnt = 0;                                    /* RAU attempt counter��0                   */
            }
        }

        if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
         && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
        {                                                                       /* A+I                                      */
            if (GMM_FALSE == ucLaiChgFlg)
            {                                                                   /* LAû��                                   */
                NAS_GMM_SndMmLuInitiation(GMMMM_NO_TIMER_EXPIRED);          /* ֪ͨMM����LU                             */
            }
        }

        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);



    }

    else if ( (VOS_FALSE == NAS_GMM_QryTimerStatus(GMM_TIMER_T3311))
           && (GMM_FALSE == ucRaiChgFlg)
           && (VOS_TRUE == pSysInfo->ulUserSrchFlg))
    {
        /* �û������ָ��������ǿ�Ʒ���ע�� */
        Gmm_TimerStop(GMM_TIMER_T3311);
        Gmm_TimerStop(GMM_TIMER_T3302);

        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
    }
    else if (MMCGMM_GSM_NO_FORBIDDEN != pSysInfo->ulForbiddenFlg)
    {                                                                           /* ��forbidden�б���                        */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* ͣT3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* ͣT3302                                  */

        Gmm_ComForbiddenList(pSysInfo->ulForbiddenFlg);                         /* ���öԽ�ֹ�б�Ĳ���                     */

        NAS_GMM_SndMmcActionResultIndWhenInForbiddenList(pSysInfo->ulForbiddenFlg);


    }
    else if (GMM_TRUE == ucRaiChgFlg)
    {                                                                           /* RA�ı�                                   */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* ͣT3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* ͣT3302                                  */
        g_GmmRauCtrl.ucRauAttmptCnt = 0;                                        /* RAU attempt counter��0                   */
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);               /* ����RAU                                  */
    }
    else if (GMM_TRUE == ucDrxLengthChgFlg)
    {                                                                           /* DRX�ı�                                  */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* ͣT3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* ͣT3302                                  */
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);               /* ����RAU                                  */
    }
    else
    {
        if ((GMM_TRUE == g_GmmRauCtrl.ucRetryFlg)
         && (GMM_TRUE == gstGmmCasGlobalCtrl.TempMsgPara.ucGsmCellChgFlg))
        {                                                                       /* ��С����Ҫ����RAU                        */
            Gmm_TimerStop(GMM_TIMER_T3311);                                     /* ͣT3311                                  */
            Gmm_TimerStop(GMM_TIMER_T3302);                                     /* ͣT3302                                  */
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);           /* ����RAU                                  */
        }

        else
        {
            NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE);

            if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
             && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
            {
                g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;

                NAS_GMM_SndMmCombinedRauInitiation();
                NAS_GMM_SndMmCombinedRauRejected(NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE_REG_MAX_TIMES);
                g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;
            }

        }
    }

    return;
}
VOS_VOID NAS_GMM_ProcessSmMsgInBuff()
{
    if(GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState)
    {
        if(GMM_SERVICE_REQ_PDPACT == g_GmmGlobalCtrl.enServReq)
        {
            Gmm_DealWithBuffAfterProc();
            g_GmmGlobalCtrl.enServReq = GMM_SERVICE_REQ_NONE;
        }
    }
}


VOS_VOID NAS_GMM_EnterCoveryRaiNoChg_BeforeT3312Exp(VOS_VOID)
{
    VOS_UINT8                           ucCsRestrictionFlg;
    VOS_UINT8                           ucCsAttachAllow;
    VOS_UINT8                           ucSimCsRegStatus;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType;

    enRatType        = NAS_MML_GetCurrNetRatType();
    ucCsAttachAllow  = NAS_MML_GetCsAttachAllowFlg();
    ucSimCsRegStatus = NAS_MML_GetSimCsRegStatus();
    ucCsRestrictionFlg  =   NAS_MML_GetCsRestrictRegisterFlg();

    if ( (NAS_MML_ROUTING_UPDATE_STATUS_UPDATED == NAS_MML_GetPsUpdateStatus())
       && ( gstGmmCasGlobalCtrl.ucLastDataSender == enRatType ))
    {
        g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;            /* ���ü����̱�־                           */

        if ((VOS_TRUE != NAS_MML_GetCsAttachAllowFlg())
         || (GMM_NET_MODE_I != g_GmmGlobalCtrl.ucNetMod)
         || (VOS_TRUE == ucCsRestrictionFlg))
        {                                                               /* ��A+I                                    */
            Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);               /* ����״̬�Ĺ�������                       */
#if (FEATURE_LTE == FEATURE_ON)
            if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
            {
                NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
            }

            /* ���֮ǰ����������T3312��ʱ��������T3323,���ؽ�����������ҪֹͣT3323*/
            Gmm_TimerStop(GMM_TIMER_T3323);
#endif

            Gmm_TimerStart(GMM_TIMER_T3312);                            /* ����T3312                                */
            g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_NORMAL;
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcSysInfoInd_RegNoCell:INFO: normal RAU procedure started");


            /* ��MMC����PSע���� */
            NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                         GMM_MMC_ACTION_RESULT_SUCCESS,
                                         NAS_MML_REG_FAIL_CAUSE_NULL);

            g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;
        }
        else
        {                                                               /* A+I                                      */
            if (  (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == NAS_MML_GetCsUpdateStatus())
                &&(VOS_TRUE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg))
            {                                                           /* ����״̬��U1                             */
                Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);           /* ����״̬�Ĺ�������                       */
#if (FEATURE_LTE == FEATURE_ON)
                if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
                {
                    NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
                }

                /* ���֮ǰ����������T3312��ʱ��������T3323,���ؽ�����������ҪֹͣT3323*/
                Gmm_TimerStop(GMM_TIMER_T3323);
#endif

                Gmm_TimerStart(GMM_TIMER_T3312);                        /* ����T3312                                */
                if (GMM_TRUE == g_GmmAttachCtrl.ucSmCnfFlg)
                {                                                       /* ��Ҫ��SM��EST_CNF                        */
                    g_GmmAttachCtrl.ucSmCnfFlg = GMM_FALSE;

                    Gmm_SndSmEstablishCnf(GMM_SM_EST_SUCCESS, GMM_SM_CAUSE_SUCCESS);    /* ��SM�ؽ����ɹ�����Ӧ                     */
                }
                if (VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
                {                                                       /* CS������ע��                             */
                    NAS_GMM_SndMmCombinedRauInitiation();
                    NAS_GMM_SndMmCombinedRauAccept(GMMMM_RAU_RESULT_COMBINED,
                                                   NAS_MML_REG_FAIL_CAUSE_NULL,
                                                   VOS_NULL_PTR,
                                                   VOS_NULL_PTR);            /* ���� MMCGMM_COMBINED_RAU_ACCEPTED        */
                }


                /* ��MMC����PSע���� */
                NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                             GMM_MMC_ACTION_RESULT_SUCCESS,
                                             NAS_MML_REG_FAIL_CAUSE_NULL);

            }
            else
            {                                                           /* ����״̬����U1                           */
                if ((VOS_FALSE == ucCsAttachAllow)
                 || (VOS_TRUE != ucSimCsRegStatus))
                {                                                       /* sim��Ч����CS������ע��                */
                    Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);       /* ����״̬�Ĺ�������                       */
#if (FEATURE_LTE == FEATURE_ON)
                    if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
                    {
                        NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
                    }

                    /* ���֮ǰ����������T3312��ʱ��������T3323,���ؽ�����������ҪֹͣT3323*/
                    Gmm_TimerStop(GMM_TIMER_T3323);
#endif

                    Gmm_TimerStart(GMM_TIMER_T3312);                    /* ����T3312                                */
                    if (GMM_TRUE == g_GmmAttachCtrl.ucSmCnfFlg)
                    {                                                   /* ��Ҫ��SM��EST_CNF                        */
                        g_GmmAttachCtrl.ucSmCnfFlg = GMM_FALSE;
                        Gmm_SndSmEstablishCnf(GMM_SM_EST_SUCCESS, GMM_SM_CAUSE_SUCCESS);    /* ��SM�ؽ����ɹ�����Ӧ                     */
                    }
                    g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_NORMAL;
                    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcSysInfoInd_RegNoCell:INFO: normal RAU procedure started");


                    /* ��MMC����PSע���� */
                    NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                                 GMM_MMC_ACTION_RESULT_SUCCESS,
                                                 NAS_MML_REG_FAIL_CAUSE_NULL);

                    g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;
                }
                else
                {
                    Gmm_RoutingAreaUpdateInitiate(
                                        GMM_UPDATING_TYPE_INVALID);     /* ����RAU                                  */
                }
            }
        }
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcSysInfoInd_RegNoCell:INFO: specific procedure ended");
        g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;              /* ���������̱�־                           */
    }
    else
    {                                                                   /* ����״̬����GU1                          */
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);       /* ����RAU                                  */
    }

    NAS_GMM_ProcessSmMsgInBuff();
}


VOS_VOID NAS_GMM_EnterCoveryRaiNoChg_AfterT3312Exp(VOS_VOID)
{
    g_GmmGlobalCtrl.ucCvrgAreaLostFlg = GMM_FALSE;                      /* �������������־                         */

    if ((VOS_TRUE != NAS_MML_GetCsAttachAllowFlg())
     || (GMM_NET_MODE_I != g_GmmGlobalCtrl.ucNetMod))
    {                                                                   /* ��A+I                                    */
        Gmm_RoutingAreaUpdateInitiate(GMM_PERIODC_UPDATING);
    }
    else
    {                                                                   /* A+I                                      */
        Gmm_RoutingAreaUpdateInitiate(
                            GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);       /* ����RAU����combined RAU with IMSI attach */
    }
}


VOS_VOID NAS_GMM_EnterCovery(VOS_VOID *pRcvMsg)
{
    MMCGMM_GSM_SYS_INFO_IND_ST         *pSysInfo;
    VOS_UINT8                           ucRaiChgFlg;
    VOS_UINT8                           ucDrxLengthChgFlg;
    VOS_UINT8                           ucLaiChgFlg;
     NAS_MML_RAI_STRU                       *pstLastSuccRai;
     GMM_RAI_STRU                            stGmmRai;

#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulT3423StatusChgNeedRegFlg;

    ulT3423StatusChgNeedRegFlg = NAS_GMM_IsT3423StatusChangeNeedRegist(NAS_MML_GetLteCsServiceCfg(),
                                                 NAS_MML_GetTinType(), NAS_MML_GetT3423Status());
#endif



    pstLastSuccRai    = NAS_MML_GetPsLastSuccRai();
    NAS_GMM_ConvertPlmnIdToGmmFormat(&(pstLastSuccRai->stLai.stPlmnId), &stGmmRai.Lai.PlmnId);

    stGmmRai.ucRac          = pstLastSuccRai->ucRac;
    stGmmRai.Lai.aucLac[0]  = pstLastSuccRai->stLai.aucLac[0];
    stGmmRai.Lai.aucLac[1]  = pstLastSuccRai->stLai.aucLac[1];

    pSysInfo          = (MMCGMM_GSM_SYS_INFO_IND_ST*)pRcvMsg;
    ucRaiChgFlg       = gstGmmCasGlobalCtrl.TempMsgPara.ucRaiChgFlg;
    ucDrxLengthChgFlg = gstGmmCasGlobalCtrl.TempMsgPara.ucDrxLengthChgFlg;
    ucLaiChgFlg       = gstGmmCasGlobalCtrl.TempMsgPara.ucLaiChgFlg;

    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {                                                                           /* ��֧��GPRS                               */
        if (GMM_TRUE == g_GmmGlobalCtrl.ucCvrgAreaLostFlg)
        {
            g_GmmGlobalCtrl.ucCvrgAreaLostFlg = GMM_FALSE;

            if (GMM_FALSE == ucLaiChgFlg)
            {
                if (GMM_TRUE == g_GmmRauCtrl.ucT3312ExpiredFlg)
                {
                    NAS_GMM_SndMmLuInitiation(GMMMM_T3312_EXPIRED);             /* ֪ͨMM����LU                             */
                }
            }
        }

        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);


        Gmm_ComStaChg(GMM_REGISTERED_LIMITED_SERVICE);
    }
    else if (MMCGMM_GSM_NO_FORBIDDEN != pSysInfo->ulForbiddenFlg)
    {                                                                           /* ��forbidden�б���                        */
        g_GmmGlobalCtrl.ucCvrgAreaLostFlg = GMM_FALSE;                          /* �������������־                         */
        Gmm_ComForbiddenList(pSysInfo->ulForbiddenFlg);                        /* ���öԽ�ֹ�б�Ĳ���                     */

        NAS_GMM_SndMmcActionResultIndWhenInForbiddenList(pSysInfo->ulForbiddenFlg);


    }
#if (FEATURE_ON == FEATURE_LTE)
    else if (VOS_TRUE == ulT3423StatusChgNeedRegFlg)
    {
        NAS_GMM_RcvLmmTimerInfoNotify_RegNmlServ();
    }

    else if (VOS_TRUE == NAS_GMM_IsUeInfoChangeTriggerRau())
    {
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
    }

#endif
    else if ((GMM_TRUE == Gmm_Compare_Rai(&g_GmmGlobalCtrl.SysInfo.Rai, &stGmmRai))
          && (GMM_FALSE == ucRaiChgFlg) && (GMM_FALSE == ucDrxLengthChgFlg)
          && (GMM_FALSE == g_GmmGlobalCtrl.ucGprsResumeFlg))
    {                                                                           /* �ص�ԭ����RA����DRX����û�иı�          */
        g_GmmGlobalCtrl.ucCvrgAreaLostFlg = GMM_FALSE;                          /* �������������־                         */

#if (FEATURE_ON == FEATURE_LTE)
        if ((NAS_MML_TIN_TYPE_RAT_RELATED_TMSI == NAS_MML_GetTinType())
         && (GMM_REGISTERED_NO_CELL_AVAILABLE == g_GmmGlobalCtrl.ucState)
         && (NAS_MML_NET_RAT_TYPE_LTE == gstGmmSuspendCtrl.ucPreRat))
        {
            NAS_GMM_IsrActiveRaiNoChg_InterSys();
            return;
        }
#endif

        if (GMM_FALSE == g_GmmRauCtrl.ucT3312ExpiredFlg)
        {                                                                       /* ��������ʱT3312δ���                    */
            NAS_GMM_EnterCoveryRaiNoChg_BeforeT3312Exp();
        }
        else
        {                                                                       /* ��������ʱT3312���                      */
            NAS_GMM_EnterCoveryRaiNoChg_AfterT3312Exp();
        }
    }
    else
    {                                                                           /* RA�ı����DRX�����仯                    */
        g_GmmGlobalCtrl.ucCvrgAreaLostFlg = GMM_FALSE;                          /* �������������־                         */
        g_GmmRauCtrl.ucT3312ExpiredFlg    = GMM_FALSE;                          /* ���T3312������                        */

        if (VOS_FALSE == NAS_GMM_IsAModeAndNetworkI())
        {                                                                       /* ��A+I                                    */
            Gmm_RoutingAreaUpdateInitiate(GMM_RA_UPDATING);
        }
        else
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
        }
    }

    return;
}
VOS_VOID GMM_CasCellS18E49(VOS_VOID *pRcvMsg)
{
    MMCGMM_GSM_SYS_INFO_IND_ST *pSysInfo;
    VOS_UINT8                   ucRaiChgFlg;
    VOS_UINT8                   ucDrxLengthChgFlg;

    pSysInfo          = (MMCGMM_GSM_SYS_INFO_IND_ST*)pRcvMsg;
    ucRaiChgFlg       = gstGmmCasGlobalCtrl.TempMsgPara.ucRaiChgFlg;
    ucDrxLengthChgFlg = gstGmmCasGlobalCtrl.TempMsgPara.ucDrxLengthChgFlg;

    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {                                                                           /* ��֧��GPRS                               */
        Gmm_TimerStop(GMM_TIMER_T3321);                                         /* ͣT3321                                  */
        Gmm_TimerStop(GMM_TIMER_PROTECT);                                       /* ͣ������ʱ��                             */

        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* ֹͣT3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* ֹͣT3320                                */

        g_GmmReqCnfMng.ucCnfMask = 0;                                           /* ���ԭ��ȴ���־                         */
        Gmm_ComStaChg(GMM_REGISTERED_LIMITED_SERVICE);                          /* ����״̬�Ĺ�������                       */
        g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                        /* �嵱ǰ����                               */

        /* �жϵȴ���־�Ƿ���ڣ������������MMC,MM����DETACH��Ϣ */
        if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
        {
            /* ����detach��,��ҪǨ�Ƶ���Ӧ��״̬ */
            if (GMM_WAIT_PS_DETACH == (g_GmmGlobalCtrl.stDetachInfo.enDetachType & GMM_WAIT_PS_DETACH))
            {
                NAS_MML_SetPsAttachAllowFlg(VOS_FALSE);

                Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);
            }
            NAS_GMM_SndMmcMmDetachInfo();
        }

        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcSysInfoInd_DeregInit:INFO: specific procedure ended");

        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);


    }
    else if (MMCGMM_GSM_NO_FORBIDDEN != pSysInfo->ulForbiddenFlg)
    {                                                                           /* ��forbidden�б���                        */
        Gmm_TimerStop(GMM_TIMER_T3321);                                         /* ͣT3321                                  */

        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* ֹͣT3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* ֹͣT3320                                */

        if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG ==
            (g_GmmReqCnfMng.ucCnfMask
                        & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
        {                                                                       /* �ȴ���Ȩ��Ӧ                             */
            Gmm_TimerStop(GMM_TIMER_PROTECT);                                   /* ͣ������ʱ��                             */
            g_GmmReqCnfMng.ucCnfMask &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG; /* ���ԭ��ȴ���־                         */
        }
        Gmm_ComForbiddenList(pSysInfo->ulForbiddenFlg);                         /* ���öԽ�ֹ�б�Ĳ���                     */

        NAS_GMM_SndMmcActionResultIndWhenInForbiddenList(pSysInfo->ulForbiddenFlg);


    }
    else if ((GMM_TRUE == ucRaiChgFlg) || (GMM_TRUE == ucDrxLengthChgFlg))
    {                                                                           /* RA�ı����DRX�ı�                        */
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
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);               /* ����RAU                                  */
    }
    else if (GMM_TRUE == gstGmmCasGlobalCtrl.ucCellUpdateFlg)
    {
        GMM_SndLlcTriggerReq(LL_GMM_TRIG_CAUSE_CELUPD_CELL_NOTIFY);
        gstGmmCasGlobalCtrl.ucCellUpdateFlg = GMM_FALSE;
    }
    else
    {
    }
    return;
}

VOS_VOID GMM_CasCellS19E49(VOS_VOID *pRcvMsg)
{
    MMCGMM_GSM_SYS_INFO_IND_ST *pSysInfo;
    VOS_UINT8                   ucRaiChgFlg;
    VOS_UINT8                   ucDrxLengthChgFlg;
    VOS_UINT8                   ucLaiChgFlg;

    pSysInfo          = (MMCGMM_GSM_SYS_INFO_IND_ST*)pRcvMsg;
    ucRaiChgFlg       = gstGmmCasGlobalCtrl.TempMsgPara.ucRaiChgFlg;
    ucDrxLengthChgFlg = gstGmmCasGlobalCtrl.TempMsgPara.ucDrxLengthChgFlg;
    ucLaiChgFlg       = gstGmmCasGlobalCtrl.TempMsgPara.ucLaiChgFlg;

    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {                                                                           /* ��֧��GPRS                               */
        Gmm_ComStaChg(GMM_REGISTERED_LIMITED_SERVICE);                          /* ����״̬�Ĺ�������                       */
        Gmm_TimerStop(GMM_TIMER_PROTECT);                                       /* ͣ������ʱ��                             */
        g_GmmReqCnfMng.ucCnfMask = 0;                                           /* ���ԭ��ȴ���־                         */
        Gmm_TimerStop(GMM_TIMER_T3330);                                         /* ͣT3330                                  */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* ֹͣT3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* ֹͣT3320                                */

        if (GMM_FALSE == ucLaiChgFlg)
        {
            /* ��ǰפ����λ������֮ǰפ����λ����LAIû�ı�,����������ģʽI,����T3312��ʱ */
            if ((VOS_TRUE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg)
             && (GMM_TRUE == g_GmmRauCtrl.ucT3312ExpiredFlg))
            {
                NAS_GMM_SndMmLuInitiation(GMMMM_T3312_EXPIRED);                    /* ֪ͨMM����LU                             */
            }
            else if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
                  && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
            {                                                                   /* LAû��,������A+I                         */
                NAS_GMM_SndMmLuInitiation(GMMMM_NO_TIMER_EXPIRED);              /* ֪ͨMM����LU                             */
            }
            else
            {
            }
        }


        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);


    }
    else if (MMCGMM_GSM_NO_FORBIDDEN != pSysInfo->ulForbiddenFlg)
    {                                                                           /* ��forbidden�б���                        */
        Gmm_TimerStop(GMM_TIMER_T3330);                                         /* ͣT3330                                  */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* ֹͣT3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* ֹͣT3320                                */

        if (GMM_TRUE == g_GmmAttachCtrl.ucSmCnfFlg)
        {                                                                       /* RAU��������SM������                      */
            Gmm_SndSmEstablishCnf(GMM_SM_EST_FAILURE, GMM_SM_CAUSE_FORBID_LA);  /* ֪ͨSM GMMע��ʧ��                       */

            g_GmmAttachCtrl.ucSmCnfFlg = GMM_FALSE;                             /* ��ucSmCnfFlg��־                         */
        }
        if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG ==
            (g_GmmReqCnfMng.ucCnfMask
                        & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
        {                                                                       /* �ȴ���Ȩ��Ӧ                             */
            Gmm_TimerStop(GMM_TIMER_PROTECT);                                   /* ͣ������ʱ��                             */
            g_GmmReqCnfMng.ucCnfMask &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG; /* ���ԭ��ȴ���־                         */
        }
        Gmm_ComForbiddenList(pSysInfo->ulForbiddenFlg);                        /* ���öԽ�ֹ�б�Ĳ���                     */

        NAS_GMM_SndMmcActionResultIndWhenInForbiddenList(pSysInfo->ulForbiddenFlg);


    }
    else if (GMM_TRUE == ucRaiChgFlg)
    {                                                                           /* RA�ı�                                   */
        NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_NOT_UPDATED);                                    /* ����״̬��ΪGU2                          */
        /* Modified by h00313353 for iteration 9, 2015-2-4, begin */
        if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
        {
            Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* ����SIM����Ϣ                            */
        }
        else
        {
            Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
        }
        /* Modified by h00313353 for iteration 9, 2015-2-4, end */

        if (GMM_TRUE == g_GmmGlobalCtrl.ucGprsResumeFlg)
        {
            g_GmmRauCtrl.ucT3312ExpiredFlg = GMM_FALSE;
            g_GmmRauCtrl.ucPeriodicRauFlg = GMM_FALSE;

            GMM_LOG_WARN("GMM_CasCellS19E49 warning:Not Start RAU in GMM_RAU_NORMAL_GPRS_RESUME.");
        }
        Gmm_TimerStop(GMM_TIMER_T3330);                                         /* ͣT3330                                  */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* ֹͣT3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* ֹͣT3320                                */

        if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG ==
            (g_GmmReqCnfMng.ucCnfMask
                        & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
        {                                                                       /* �ȴ���Ȩ��Ӧ                             */
            Gmm_TimerStop(GMM_TIMER_PROTECT);                                   /* ͣ������ʱ��                             */
            g_GmmReqCnfMng.ucCnfMask
                &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;                      /* ���ԭ��ȴ���־                         */
        }
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);               /* ����RAU                                  */
    }
    else if (GMM_TRUE == ucDrxLengthChgFlg)
    {                                                                           /* DRX�ı�                                  */
        g_GmmGlobalCtrl.MsgHold.ucHandleRauFlg = GMM_TRUE;                      /* ���̽���֮�����RAU                      */
        g_GmmGlobalCtrl.MsgHold.ucInitiateLuFlg = GMM_TRUE;                     /* ���GMM���ܽ���RAUʱҪ����MM��LU����     */
    }
    else
    {
    }

    return;
}

VOS_VOID NAS_GMM_CheckBufferDetach(VOS_VOID)
{
	VOS_VOID                           *pMsg;
	MMCGMM_DETACH_REQ_STRU             *pstDetach;

	if (GMM_MSG_HOLD_FOR_DETACH
		== (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_DETACH))
	{                                                                           /* ����б�����SRԭ��                       */
		g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_DETACH;      /* ��������־                             */

		pMsg = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForDetach;

		/*����ַ���Ϣ*/
		pstDetach = (MMCGMM_DETACH_REQ_STRU *)Gmm_MemMalloc(sizeof(MMCGMM_DETACH_REQ_STRU));

		if (VOS_NULL_PTR == pstDetach)
		{
			Gmm_MemFree(pMsg);
			PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR,
				"Gmm_DealWithBuffAfterProc:ERROR: Gmm_MemMalloc fail !! ");
			return;
		}

		Gmm_MemCpy(pstDetach, pMsg, sizeof(MMCGMM_DETACH_REQ_STRU));

		/*�ͷű����detach��Ϣ*/
		Gmm_MemFree(pMsg);

		/*�ַ������detach��Ϣ*/
		Gmm_MsgDistribute((VOS_VOID *)(pstDetach));

		/*�ͷ���������ڴ�*/
		Gmm_MemFree(pstDetach);
	}
}

VOS_VOID GMM_RcvGasSysInfoInd_SuspWaitSys(VOS_VOID *pRcvMsg)
{
    MMCGMM_GSM_SYS_INFO_IND_ST         *pSysInfo;
    VOS_UINT8                           ucRaiChgFlg;
    VOS_UINT8                           ucLaiChgFlg;

#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulT3423StatuChgNeedRegFlg;
    ulT3423StatuChgNeedRegFlg = NAS_GMM_IsT3423StatusChangeNeedRegist(NAS_MML_GetLteCsServiceCfg(),
                                    NAS_MML_GetTinType(), NAS_MML_GetT3423Status());
#endif

    pSysInfo    = (MMCGMM_GSM_SYS_INFO_IND_ST*)pRcvMsg;
    ucRaiChgFlg = gstGmmCasGlobalCtrl.TempMsgPara.ucRaiChgFlg;
    ucLaiChgFlg = gstGmmCasGlobalCtrl.TempMsgPara.ucLaiChgFlg;

    Gmm_TimerStop(GMM_TIMER_SUSPENDED);

    GMM_ResumeTimer(GMM_TIMER_RESUME);

    if (VOS_TRUE != NAS_MML_GetSimPsRegStatus())
    {                                                                           /* ԭ��SIM��Ч                              */
        g_GmmGlobalCtrl.ucCvrgAreaLostFlg = GMM_FALSE;                          /* �������������־                         */

        GMM_CasFsmStateChangeTo(GMM_DEREGISTERED_NO_IMSI);

        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SIM_INVALID);

        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "GMM_RcvGasSysInfoInd_SuspWaitSys:NORMAL: STATUS IS GMM_DEREGISTERED_NO_IMSI");
        return;
    }
    if (VOS_FALSE == NAS_MML_GetPsAttachAllowFlg())
    {
        g_GmmGlobalCtrl.ucCvrgAreaLostFlg = GMM_FALSE;                          /* �������������־                         */
        Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);                         /* ����״̬�Ĺ�������                       */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "GMM_RcvGasSysInfoInd_SuspWaitSys:WARNING: Not allow Attach");

        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);


        return;
    }
    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {                                                                           /* ��֧��GPRS                               */
        GMM_LOG_INFO("GMM_RcvGasSysInfoInd_SuspWaitSys:the cell not support GPRS.");
        Gmm_ComStaChg(GMM_REGISTERED_LIMITED_SERVICE);                          /* ����״̬�Ĺ�������                       */
        Gmm_TimerStop(GMM_REGSTER_AND_SHUTDOWN_TIMER);                                           /* ͣ����Timer                              */

        if (GMM_TRUE == ucRaiChgFlg)
        {
            if (MMCGMM_GSM_NO_FORBIDDEN == pSysInfo->ulForbiddenFlg)
            {
                g_GmmRauCtrl.ucRauAttmptCnt = 0;                                    /* RAU attempt counter��0                   */
            }
        }

        if (VOS_TRUE == NAS_GMM_IsAModeAndNetworkI())
        {                                                                       /* A+I                                      */
            if ((GMM_FALSE == ucLaiChgFlg)
             && (GMM_TRUE == g_GmmRauCtrl.ucT3312ExpiredFlg)
             && (VOS_TRUE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg))
            {                                                                   /* LAû��                                   */
                NAS_GMM_SndMmLuInitiation(GMMMM_T3312_EXPIRED);                 /* ֪ͨMM����LU                             */
            }
        }

        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);

    }
    else if (MMCGMM_GSM_NO_FORBIDDEN != pSysInfo->ulForbiddenFlg)
    {                                                                           /* ��forbidden�б���                        */
        g_GmmRauCtrl.ucNpduCnt = 0x0;
        GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_HANDOVER, GMM_RABM_RAU_FAILURE);

        Gmm_ComForbiddenList(pSysInfo->ulForbiddenFlg);                        /* ���öԽ�ֹ�б�Ĳ���                     */

        NAS_GMM_SndMmcActionResultIndWhenInForbiddenList(pSysInfo->ulForbiddenFlg);


    }
    else if (GMM_TRUE == ucRaiChgFlg)
    {                                                                           /* RA�ı�                                   */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* ͣT3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* ͣT3302                                  */

        Gmm_TimerStop(GMM_TIMER_T3330);
        Gmm_TimerStop(GMM_TIMER_T3318);
        Gmm_TimerStop(GMM_TIMER_T3320);
        g_GmmRauCtrl.ucRauAttmptCnt = 0;                                        /* RAU attempt counter��0                   */
        gstGmmSuspendCtrl.ucRauCause = GMM_RAU_FOR_INTERSYSTEM;


        if (GMM_NETMODE_CHG_NULL == gstGmmSuspendCtrl.ucNetModeChange)
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);           /* ����RAU                                  */
        }
        else
        {
            GMM_ProcedureByNetMode(gstGmmSuspendCtrl.ucNetModeChange);
        }
    }
    else if (RR_REL_CAUSE_DIRECTED_SINGNALING_CONNECTION_RE_ESTABLISHMENT
        == g_GmmGlobalCtrl.ucRelCause)
    {
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* ͣT3311                                  */
        Gmm_RoutingAreaUpdateInitiateWithReEstRR();
    }
    else
    {
        if ((GMM_IU_PMM_CONNECTED == gstGmmSuspendCtrl.ucPreSrvState)
         && (NAS_MML_NET_RAT_TYPE_LTE != gstGmmSuspendCtrl.ucPreRat))
        {
            GMM_LOG_INFO("GMM_RcvGasSysInfoInd_SuspWaitSys:Need immediately RAU.");
#if 0
            GMM_SndRabmGprsInfoInd(GMM_RABM_GPRS_SUPPORTED, GMM_RABM_PROC_HANDOVER,
                                   GMM_RABM_IMMEDIATELY_RAU);
#endif
            Gmm_TimerStop(GMM_TIMER_T3311);                                     /* ͣT3311                                  */
            Gmm_TimerStop(GMM_TIMER_T3302);                                     /* ͣT3302                                  */
            Gmm_TimerStop(GMM_TIMER_T3330);
            Gmm_TimerStop(GMM_TIMER_T3318);
            Gmm_TimerStop(GMM_TIMER_T3320);
            g_GmmRauCtrl.ucRauAttmptCnt = 0;                                    /* RAU attempt counter��0                   */
            gstGmmSuspendCtrl.ucRauCause = GMM_RAU_FOR_INTERSYSTEM;
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);           /* ����RAU                                  */

        }
        else if ( (gstGmmCasGlobalCtrl.ucLastDataSender !=
                            NAS_MML_GetCurrNetRatType())
#if (FEATURE_ON == FEATURE_LTE)
                      && (gstGmmCasGlobalCtrl.ucLastDataSender != NAS_MML_NET_RAT_TYPE_LTE)
#endif
                )
        {
            GMM_LOG_INFO("GMM_RcvGasSysInfoInd_SuspWaitSys:Need selective RAU.");

            Gmm_TimerStop(GMM_TIMER_T3311);                                     /* ͣT3311                                  */
            Gmm_TimerStop(GMM_TIMER_T3302);                                     /* ͣT3302                                  */
            Gmm_TimerStop(GMM_TIMER_T3330);
            Gmm_TimerStop(GMM_TIMER_T3318);
            Gmm_TimerStop(GMM_TIMER_T3320);

            gstGmmSuspendCtrl.ucRauCause = GMM_RAU_FOR_INTERSYSTEM;
            if (GMM_T3312_TIMEOUT == gstGmmSuspendCtrl.ucT3312State)
            {
                Gmm_RoutingAreaUpdateInitiate(GMM_PERIODC_UPDATING);
                gstGmmSuspendCtrl.ucT3312State = GMM_T3312_NOT_TIMEOUT;
            }
            else
            {
                /* ����������һ��RAU */
                Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
            }
        }
#if (FEATURE_ON == FEATURE_LTE)
        else if (VOS_TRUE == ulT3423StatuChgNeedRegFlg)
        {
            NAS_GMM_RcvLmmTimerInfoNotify_RegNmlServ();
        }
        else if (VOS_TRUE == NAS_GMM_IsUeInfoChangeTriggerRau())
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
        }
#endif
        else
        {
            GMM_LOG_INFO("GMM_RcvGasSysInfoInd_SuspWaitSys:Need not RAU.");
            g_GmmRauCtrl.ucNpduCnt = 0x0;
            GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_HANDOVER, GMM_RABM_RAU_SUCCESS);

            /* W->G, W�½����ֹ���߲�֧��GPRS����G�º����RAC���ı䣬
               ���µ�����GMM_REGISTERED_UPDATE_NEEDED״̬�µ�ϵͳ��Ϣ������ */
            if ((GMM_REGISTERED_UPDATE_NEEDED == gstGmmSuspendCtrl.ucPreState)
             || (GMM_REGISTERED_LIMITED_SERVICE== gstGmmSuspendCtrl.ucPreState))
            {
                NAS_GMM_EnterCovery(pRcvMsg);
            }
            else
            {
                Gmm_ComStaChg(gstGmmSuspendCtrl.ucPreState);
                GMM_ResumeSuccess();
                if (GMM_TRUE == g_GmmGlobalCtrl.ucFollowOnFlg)
                {
                    g_GmmGlobalCtrl.ucFollowOnFlg = GMM_FALSE;
                    NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);

                    Gmm_RoutingAreaUpdateHandleFollowOn();
                }
                else
                {
                    if (GMM_FALSE == gstGmmCasGlobalCtrl.ucTlliAssignFlg)
                    {
                        GMM_UpdateSysTlli(GMM_LOCAL_TLLI);
                        GMM_AssignSysTlli();
                    }
                }

#if   (FEATURE_ON == FEATURE_LTE)
                /* L��ѡ��G,·����δ�ı䣬ISR���������RAUʱ��Ҫ����״̬��
                  ����Ϊregister no cell available�������޷���ҵ�� */
                if ((NAS_MML_TIN_TYPE_RAT_RELATED_TMSI == NAS_MML_GetTinType())
                 && (NAS_MML_NET_RAT_TYPE_LTE == gstGmmSuspendCtrl.ucPreRat))

                {
                    NAS_GMM_IsrActiveRaiNoChg_InterSys();
                }
#endif
            }
        }
    }

    if ( GMM_ROUTING_AREA_UPDATING_INITIATED != g_GmmGlobalCtrl.ucState)
	{
		NAS_GMM_CheckBufferDetach();
	}

    return;
}

VOS_VOID GMM_RcvLlcDataInd(VOS_VOID *pRcvMsg)
{
    LL_NAS_UNITDATA_IND_MSG *pDataInd;
    RRMM_DATA_IND_STRU      *pRrmmDataInd;
    VOS_UINT8                aucBuffer[300];
    VOS_UINT8                ucGprsCipher;

    pDataInd = (LL_NAS_UNITDATA_IND_MSG*)pRcvMsg;

    pRrmmDataInd = (RRMM_DATA_IND_STRU*)aucBuffer;
    /*������Gmm_RcvRrmmDataInd�����м�飬��������*/
    pRrmmDataInd->ulCnDomainId       = RRC_NAS_PS_DOMAIN;
    /*������Gmm_RcvRrmmDataInd�����м�飬��������*/
    /*
    pRrmmDataInd->ulIntegCheckResult = RRC_NAS_MSG_INTEGRITY_CHECK_SUCCESS;
    */
    /*NAS��Ϣ������*/
    pRrmmDataInd->RcvNasMsg.ulNasMsgSize = pDataInd->stUnitDataInd.usPduLen;
    /*��LLC�������ݿ�����RRMM_DATA_IND���ݽṹ�е����ݲ���*/

    if (pDataInd->stUnitDataInd.usPduLen > 252)
    {
        GMM_LOG_WARN("The length of Msg from LLC is too large!");
        return;
    }

    Gmm_MemCpy(pRrmmDataInd->RcvNasMsg.aucNasMsg,
               pDataInd->stUnitDataInd.aucPdu,
               pDataInd->stUnitDataInd.usPduLen);

    /* 2G��ϢĬ����Ϣ������ͨ�� */
    if (GMM_FALSE == g_GmmGlobalCtrl.ucIntegrityProtStart)
    {
        g_GmmGlobalCtrl.ucIntegrityProtStart = GMM_TRUE;
    }

    if ((GMM_PD_GMM == (pRrmmDataInd->RcvNasMsg.aucNasMsg[0] & 0x0F))
     && (GMM_MSG_RAU_ACCEPT == pRrmmDataInd->RcvNasMsg.aucNasMsg[1]))
    {
        /* ucCiphInd LLʹ�õĺ궨����LL_NONZERO_VALUE = 1,GMM��Ҫ����ͬ�� */
        if (1 == pDataInd->stUnitDataInd.ucCiphInd)
        {
            ucGprsCipher = VOS_TRUE;
        }
        else
        {
            ucGprsCipher = VOS_FALSE;
        }
        if (ucGprsCipher != gstGmmCasGlobalCtrl.ucGprsCipher)
        {
            gstGmmCasGlobalCtrl.ucGprsCipher = ucGprsCipher;

            NAS_GMM_SndMmcCipherInfoInd();

            /* ָ��Kc�ͼ����㷨 */
            GMM_AssignGsmKc();
        }
    }

    /*��ԭ��3G�ķ�֧ */
    Gmm_RcvRrmmDataInd(pRrmmDataInd);

    return;
}

/*****************************************************************************
  �� �� ��  : NAS_GMM_RcvLlcDataCnf
  ��������  : ����IDD_LL_UINTDATA_CNF��Ϣ������
  �������  : VOS_VOID*    pRcvMsg    �����Ϣָ��
  �������  : ��
  �� �� ֵ  : ��
  ���ú���  :
  ��������  :

  �޸���ʷ  :
1.��    ��  : 2015��4��7��
  ��    ��  : wx270776
  �޸�����  : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_GMM_RcvLlcDataCnf(
    VOS_VOID                           *pRcvMsg
)
{
    LL_NAS_UNITDATA_CNF_MSG            *pstLlNasUintdataCnf = VOS_NULL_PTR;

    pstLlNasUintdataCnf                 = (LL_NAS_UNITDATA_CNF_MSG*)pRcvMsg;

    /* �ж��Ƿ�Ϊ�ػ����� */
    if ( (GMM_DETACH_COMBINED_POWER_OFF == g_GmmGlobalCtrl.ucSpecProc)
      || (GMM_DETACH_NORMAL_POWER_OFF   == g_GmmGlobalCtrl.ucSpecProc) )
    {
        if ( pstLlNasUintdataCnf->usMui  != NAS_GMM_GetPowerOffDetachPsMui() )
        {
            NAS_WARNING_LOG(WUEPS_PID_GMM, "GMM_RcvLlcDataCnf:The Result Of ID_LL_UNITDATA_CNF Is Wrong!");

            return;
        }

        /* �ػ�DETACH��Ϣ���͸������Ĵ��� */
        NAS_GMM_RcvLlcDataCnf_PowerOff();

        return;
    }

    return;
}

/*****************************************************************************
  �� �� ��  : NAS_GMM_RcvLlcDataCnf_PowerOff
  ��������  : GMM�յ�LLC������IDD_LL_UINTDATA_CNF��Ϣ��Ĺػ�������
  �������  : ��
  �������  : ��
  �� �� ֵ  : ��
  ���ú���  :
  ��������  :

  �޸���ʷ  :
1.��    ��  : 2015��4��7��
  ��    ��  : wx270776
  �޸�����  : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_GMM_RcvLlcDataCnf_PowerOff(VOS_VOID)
{
    /* ��OM�ϱ�NAS�¼� */
    NAS_EventReport(WUEPS_PID_GMM,
                    NAS_OM_EVENT_DETACH_FINISH,
                    VOS_NULL_PTR,
                    NAS_OM_EVENT_NO_PARA);

    /* �жϵ�ǰ����ģʽ�Ƿ�GSM���� */
    if (GMM_TRUE != GMM_IsCasGsmMode())
    {
        NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_RcvLlcDataCnf_PowerOff:Power Off Failure Due To GMM Is CasGsmMode!");
        return;
    }

    /* ֹͣ��ʱ�� */
    Gmm_TimerStop(GMM_TIMER_1S);
    Gmm_TimerStop(GMM_TIMER_DETACH_FOR_POWER_OFF);

    /* ���P_TMSI_SIGNATURE */
    if (GMM_UEID_P_TMSI_SIGNATURE
            == (g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask & GMM_UEID_P_TMSI_SIGNATURE))
    {
        g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask &= ~GMM_UEID_P_TMSI_SIGNATURE;

        NAS_MML_InitUeIdPtmsiSignatureInvalid();

        Gmm_SndAgentUsimUpdateFileReq(GMM_USIM_FILE_PS_LOC_INFO);
    }

    /* ��MMC�������Ӧ��ģ��ظ���Ϣ */
    Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);

    if (GMM_DETACH_COMBINED_POWER_OFF == g_GmmGlobalCtrl.ucSpecProc)
    {
        NAS_GMM_SndMmGprsDetachComplete();
    }

    Gmm_SndMmcPowerOffCnf();
    Gmm_ComCnfHandle();
    NAS_GMM_FreeTlliForPowerOff();

    /* ���ȫ�ֱ��� */
    if (GMM_MSG_HOLD_FOR_POWEROFF == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_POWEROFF))
    {
        Gmm_MemFree(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForPowerOff);
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_POWEROFF;
    }
    Gmm_HoldBufferFree();

    GMM_BufferMsgDump();

    Gmm_ComVariantInit();

    return;
}


VOS_VOID GMM_RcvGasSuspensionInd(VOS_VOID *pRcvMsg)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    GMM_LOG_INFO("GMM_RcvGasSuspensionInd:Receive RRMM_GPRS_SUSPENSION_IND");

    enCurRat = NAS_MML_GetCurrNetRatType();

    /* ��ʱCS�����ӿ϶����ڣ���MMCGMM_SERVICE_IND���ܲ����յ� */
    g_GmmGlobalCtrl.CsInfo.ucCsTransFlg       = GMM_TRUE;

#if (FEATURE_LTE == FEATURE_ON)

    /* ֪ͨL,ps��״̬Ϊ���� */
    NAS_GMM_SndLmmInfoChangeNotifyReq(NAS_MML_GetCurrNetRatType(),
                                      VOS_FALSE,
                                      VOS_TRUE,
                                      gstGmmCasGlobalCtrl.GmmSrvState,
                                      VOS_TRUE);
#endif

    switch (g_GmmGlobalCtrl.ucState)
    {
        case GMM_SUSPENDED_WAIT_FOR_SYSINFO:
            g_GmmGlobalCtrl.ucInterRatFlg = VOS_TRUE;
            Gmm_TimerStop(GMM_TIMER_SUSPENDED);
            Gmm_ComStaChg(GMM_SUSPENDED_GPRS_SUSPENSION);
            return;
        case GMM_GPRS_SUSPENSION:
        case GMM_SUSPENDED_GPRS_SUSPENSION:
        case GMM_SUSPENDED_NORMAL_SERVICE:
            GMM_LOG_INFO("GMM_RcvGasSuspensionInd:Receive RRMM_GPRS_SUSPENSION_IND in abnormal state.");
            return;
        default:
            break;
    }

    GMM_SuspendTimer();

    /* <==A32D09766 ���֮ǰLLCû�б����𣬴�ʱ��Ҫ����LLC */
    if (GMM_TRUE == gstGmmCasGlobalCtrl.ucTlliAssignFlg)
    {
        if(GMM_NOT_SUSPEND_LLC == gstGmmCasGlobalCtrl.ucSuspendLlcCause)
        {
            GMM_SndLlcSuspendReq();
        }
        gstGmmCasGlobalCtrl.ucSuspendLlcCause |= GMM_SUSPEND_LLC_FOR_CS;
    }

    gstGmmSuspendCtrl.ucPreSrvState = gstGmmCasGlobalCtrl.GmmSrvState;
    gstGmmSuspendCtrl.ucPreState = g_GmmGlobalCtrl.ucState;

    Gmm_ComStaChg(GMM_GPRS_SUSPENSION);

    /* ָʾRABM��ǰϵͳģʽ, ������RABM, bRatChangeFlgΪFALSE */
    NAS_GMM_SndRabmSysSrvChgInd(enCurRat,
                                VOS_FALSE,
                                VOS_TRUE,
                                VOS_TRUE);

    return;
}


VOS_VOID GMM_PowerOffHandle()
{
    MMCGMM_POWER_OFF_REQ_STRU stPowerOffReq;

    stPowerOffReq.MsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    stPowerOffReq.MsgHeader.ulSenderPid     = WUEPS_PID_MMC;
    stPowerOffReq.MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    stPowerOffReq.MsgHeader.ulReceiverPid   = WUEPS_PID_GMM;
    stPowerOffReq.MsgHeader.ulLength        = sizeof(MMCGMM_POWER_OFF_REQ_STRU)
                                                    - VOS_MSG_HEAD_LENGTH;
    stPowerOffReq.MsgHeader.ulMsgName       = MMCGMM_POWER_OFF_REQ;

    Gmm_RcvMmcPowerOffReq(&stPowerOffReq);
}


VOS_VOID NAS_GMM_HandleGrpsResumeFail()
{
    if (GMM_GPRS_SUSPENSION == g_GmmGlobalCtrl.ucState)
    {
        gstGmmSuspendCtrl.ucRauCause = GMM_RAU_FOR_NORMAL;
        GMM_ResumeTimer(GMM_TIMER_RESUME);
        if (GMM_T3312_TIMEOUT == gstGmmSuspendCtrl.ucT3312State)
        {
            gstGmmSuspendCtrl.ucT3312State = GMM_T3312_NOT_TIMEOUT;
        }

        /*����PDP����ʱ������·���������Իظ�PS��ҵ��A32D10990==>*/
        /*������������״̬������·���������Իظ�PS��ҵ��AT2D18123==>*/
        Gmm_ComStaChg(gstGmmSuspendCtrl.ucPreState);
        if ((GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState)
         || (GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState)
         || (GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM == g_GmmGlobalCtrl.ucState)
         || (GMM_REGISTERED_NO_CELL_AVAILABLE == g_GmmGlobalCtrl.ucState)
         || (GMM_REGISTERED_PLMN_SEARCH == g_GmmGlobalCtrl.ucState)
         || (GMM_TRUE == g_GmmGlobalCtrl.ucSuspendProc))
        {
            g_GmmGlobalCtrl.ucGprsResumeFlg = GMM_TRUE;
            g_GmmGlobalCtrl.ucSuspendProc   = GMM_FALSE;
        }
        /*<==A32D10990*/
    }
    else
    {
        /*��ϵͳ�ı�֮ǰGMM����ע��״̬*/
        if ((0x20 == (gstGmmSuspendCtrl.ucPreState & 0xF0))
         || (GMM_ROUTING_AREA_UPDATING_INITIATED == gstGmmSuspendCtrl.ucPreState))
        {

            Gmm_ComStaChg(GMM_SUSPENDED_WAIT_FOR_SYSINFO);
            Gmm_TimerStart(GMM_TIMER_SUSPENDED);
        }
        else
        {
            if (GMM_TC_ACTIVE == gstGmmSuspendCtrl.ucPreState)
            {
                if ((gstGmmCasGlobalCtrl.ucLastDataSender != NAS_MML_GetCurrNetRatType())
                 && (GMM_STATUS_ATTACHED == g_MmSubLyrShare.GmmShare.ucAttachSta))
                {
                    Gmm_ComStaChg(GMM_SUSPENDED_WAIT_FOR_SYSINFO);
                }
                else
                {
                    Gmm_ComStaChg(g_GmmGlobalCtrl.ucTcPreSta);
                }
            }
            else
            {
                Gmm_ComStaChg(gstGmmSuspendCtrl.ucPreState);
            }

            GMM_ResumeTimer(GMM_TIMER_RESUME);
            GMM_BufferMsgDump();
            Gmm_HoldBufferFree();                                           /* ���������Ϣ                             */
            Gmm_ComCnfHandle();
        }
    }
}
VOS_VOID GMM_RcvGasGprsResumeInd( VOS_VOID *pRcvMsg )
{
    RRMM_GPRS_RESUME_IND_ST *pstGprsResumeMsg;

    pstGprsResumeMsg = (RRMM_GPRS_RESUME_IND_ST*)pRcvMsg;

    GMM_LOG_INFO("GMM_RcvGasGprsResumeInd:Receive RRMM_GPRS_RESUME_IND");

    if ((GMM_GPRS_SUSPENSION != g_GmmGlobalCtrl.ucState)
      && (GMM_SUSPENDED_GPRS_SUSPENSION != g_GmmGlobalCtrl.ucState))
    {
        GMM_LOG_WARN("GMM_RcvGasResumeInd:Receive RRMM_GPRS_RESUME_IND in abnormal state.");
        return;
    }

    if (GMM_POWER_OFF_RCV == gstGmmSuspendCtrl.ucPowerOff)
    {
        if (GMM_TRUE == gstGmmCasGlobalCtrl.ucTlliAssignFlg)
        {
            GMM_SndLlcResumeReq(LL_GMM_RESUME_TYPE_SIGNAL);
        }
        Gmm_TimerStop(GMM_TIMER_1S);
        Gmm_ComStaChg(gstGmmSuspendCtrl.ucPreState);
        GMM_PowerOffHandle();
        gstGmmSuspendCtrl.ucPowerOff = GMM_POWER_OFF_NOT_RCV;
        return;
    }

    /* ��ʱCS�����ӿ϶������ڣ���˽�MMCGMM_SERVICE_IND��Ϣ�еĴ�����ǰ�ŵ��˴� */
    g_GmmGlobalCtrl.CsInfo.ucCsTransFlg = GMM_FALSE;
    /* GSM�¸ñ�־��ʹ��GMM_RAU_NORMAL_CS_UPDATED���������Ժ�������Ӱ�� */
    if (GMM_RAU_NORMAL_CS_UPDATED != g_GmmGlobalCtrl.ucSpecProcInCsTrans)
    {
        g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;
    }

    if ((GRR_GMM_GPRS_RESUME_SUCCESS == pstGprsResumeMsg->ucResult)
        && (VOS_FALSE == g_GmmGlobalCtrl.ucInterRatFlg))
    {

        /* ��W�µ绰�л���GSM�󣬻��ؽ�����GMM״̬Ǩ�Ƶ�GMM_TC_ACTIVE״̬������û�д���ϵͳ��Ϣ */
        if (GMM_TC_ACTIVE ==  gstGmmSuspendCtrl.ucPreState)
        {
            if (GMM_STATUS_ATTACHED == g_MmSubLyrShare.GmmShare.ucAttachSta)
            {
                Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);
            }
            else
            {
                Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);
            }
        }
        else
        {
            /*ֻ�����ڷ���ϵͳ�ı������*/
            Gmm_ComStaChg(gstGmmSuspendCtrl.ucPreState);
        }

        GMM_ResumeTimer(GMM_TIMER_RESUME);

        GMM_BufferMsgResume();

        if (GMM_T3312_TIMEOUT == gstGmmSuspendCtrl.ucT3312State)
        {
            g_GmmRauCtrl.ucT3312ExpiredFlg = GMM_TRUE;
            gstGmmSuspendCtrl.ucT3312State = GMM_T3312_NOT_TIMEOUT;
        }
    }
    else
    {
        NAS_GMM_HandleGrpsResumeFail();

        GMM_BufferMsgResume();
    }

    g_GmmGlobalCtrl.ucInterRatFlg = VOS_FALSE;

    NAS_GMM_ProcSavedGsmSysInfo();

    return;
}


VOS_VOID GMM_RcvCellReselectInd( VOS_VOID *pRcvMsg )
{
    RRMM_CELL_RESELECT_IND_ST *pstCellReselMsg;

    pstCellReselMsg = (RRMM_CELL_RESELECT_IND_ST *)pRcvMsg;

    GMM_LOG_INFO("GMM_RcvCellReselectInd:Receive RRMM_CELL_RESELECT_IND");

    if(GMM_FALSE == GMM_IsCasGsmMode())
    {
        return;
    }

    if(RRMM_CELL_RESEL_START == pstCellReselMsg->ucCellReselProc)
    {
        gstGmmCasGlobalCtrl.ucCellReselFlg = VOS_TRUE;
    }
    else
    {
        gstGmmCasGlobalCtrl.ucCellReselFlg = VOS_FALSE;
    }

    if(VOS_FALSE == NAS_MML_GetPsAttachAllowFlg())
    {
        return;
    }
    if ( VOS_FALSE == NAS_MML_GetSimPsRegStatus()  )
    {
        return;
    }

    /*
    ����ʼ��ѡʱ��GMM��Ҫ֪ͨLLC�����û������ݣ������LLC������������
    */
    if(RRMM_CELL_RESEL_START == pstCellReselMsg->ucCellReselProc)
    {
        if (GMM_TRUE == gstGmmCasGlobalCtrl.ucTlliAssignFlg)
        {
            if (GMM_NOT_SUSPEND_LLC == gstGmmCasGlobalCtrl.ucSuspendLlcCause)
            {
                GMM_SndLlcSuspendReq();
            }

            gstGmmCasGlobalCtrl.ucSuspendLlcCause |= GMM_SUSPEND_LLC_FOR_CELL_RESEL;
        }
    }
    else
    {
        if (VOS_TRUE == NAS_USIMMAPI_IsTestCard())
        {
            Gmm_SndLlcAbortReq(LL_GMM_CLEAR_DATA_TYPE_NO_SM_SIGNALLING);
        }
        else
        {
            Gmm_SndLlcAbortReq(LL_GMM_CLEAR_DATA_TYPE_TRIG);
        }
    }


    return;
}


VOS_UINT8 GMM_IsGasCellReselect(VOS_VOID)
{
    return gstGmmCasGlobalCtrl.ucCellReselFlg;
}

VOS_VOID GMM_RcvGasTbfRleInd( VOS_VOID *pRcvMsg )
{
    Gmm_SndMmcTBFRelInd();

    if ((GMM_DEREGISTERED_PLMN_SEARCH == g_GmmGlobalCtrl.ucState)
     || (GMM_REGISTERED_PLMN_SEARCH == g_GmmGlobalCtrl.ucState))
    {
        Gmm_TimerStop(GMM_TIMER_WAIT_CONNECT_REL);
    }
    else
    {
        if(GMM_TRUE == g_GmmGlobalCtrl.ulGmmAttachFlg)
        {
            if((VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
            && (GMM_DEREGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState))
            {
                Gmm_RcvRoutingAreaUpdateRejectMsg_AttachFlg_Handling();
            }
            g_GmmGlobalCtrl.ulGmmAttachFlg = GMM_FALSE;
        }
    }
}

#if (FEATURE_ON == FEATURE_LTE)

VOS_VOID NAS_GMM_RcvMsRadioCapaInfo_TimerWaitAsMsRadioCapaRunning(VOS_VOID)
{

    if (GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState)
    {
        NAS_GMM_SndRoutingAreaUpdateReq(NAS_GMM_GetRauUpdateType());
        return;
    }

    if (GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
    {
        NAS_GMM_SndAttachReq();
    }

    return;
}

#endif

VOS_VOID GMM_RcvGasRadioAccessCapa( VOS_VOID *pRcvMsg )
{
    VOS_UINT8                                               ucLen;
    GRRMM_MS_RADIO_ACCESS_CAPABILITIES_IND_STRU            *pstRacMsg;


#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                                              ulIsWaitMsRadioCapaTimerRunning;

    ulIsWaitMsRadioCapaTimerRunning = NAS_GMM_QryTimerStatus(GMM_TIMER_WAIT_AS_MS_RADIO_CAPA_INFO);
#endif

    if (VOS_NULL_PTR == pRcvMsg)
    {
        return;
    }

    pstRacMsg = (GRRMM_MS_RADIO_ACCESS_CAPABILITIES_IND_STRU *)pRcvMsg;

    ucLen = pstRacMsg->aucData[0] + 1;

    if ((ucLen > MS_RADIO_ACCESS_CAPABILITY_MAX_SIZE) || (ucLen < MS_RADIO_ACCESS_CAPABILITY_MIN_SIZE))
    {
        NAS_ERROR_LOG1(WUEPS_PID_GMM, "GMM_RcvGasRadioAccessCapa: Wrong RAC Len: ", ucLen);
    }
    else
    {
        if (0 != VOS_MemCmp(g_GmmGlobalCtrl.UeInfo.aucRadioCpb,
                    pstRacMsg->aucData, MS_RADIO_ACCESS_CAPABILITY_MAX_SIZE))
        {
            PS_MEM_CPY(g_GmmGlobalCtrl.UeInfo.aucRadioCpb, pstRacMsg->aucData,
                       MS_RADIO_ACCESS_CAPABILITY_MAX_SIZE);

#if (FEATURE_ON == FEATURE_LTE)
            if (NAS_UTRANCTRL_UTRAN_MODE_TDD == NAS_UTRANCTRL_GetCurrUtranMode())
            {
                return;
            }

            /* ����syscfg�����Ƿ�֧��L��L�Ƿ�enable״̬����ucMsRadioCapSupportLteFromAs*/
            g_GmmGlobalCtrl.UeInfo.ucMsRadioCapSupportLteFromAs = (VOS_UINT8)NAS_MML_IsSupportLteCapability();

            if (VOS_TRUE == ulIsWaitMsRadioCapaTimerRunning)
            {
                Gmm_TimerStop(GMM_TIMER_WAIT_AS_MS_RADIO_CAPA_INFO);

                if ((GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState)
                 || (GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState))
                {
                    NAS_GMM_RcvMsRadioCapaInfo_TimerWaitAsMsRadioCapaRunning();

                    return;
                }
            }

            /* ��ǰ�Ѿ�����ʱ���������� */
            if (VOS_TRUE == NAS_GMM_QryTimerStatus(GMM_TIMER_DELAY_RADIO_CAPA_TRIGED_RAU))
            {
                Gmm_TimerStop(GMM_TIMER_DELAY_RADIO_CAPA_TRIGED_RAU);
                Gmm_TimerStart(GMM_TIMER_DELAY_RADIO_CAPA_TRIGED_RAU);
                return;
            }

            if (g_GmmGlobalCtrl.UeInfo.ucMsRadioCapSupportLteFromAs != g_GmmGlobalCtrl.UeInfo.ucMsRadioCapSupportLteFromRegReq)
            {
                NAS_GMM_HandleMsRadioCapLteSupportChanged();
            }
#endif
        }

    }

    return;
}


VOS_VOID GMM_RcvGasTdsRadioAccessCapa(
    VOS_VOID                           *pstRcvMsg
)
{
    VOS_UINT8                                               ucLen;
    GRRMM_MS_RADIO_ACCESS_CAPABILITIES_IND_STRU            *pstRacMsg = VOS_NULL_PTR;

#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                                              ulIsWaitMsRadioCapaTimerRunning;

    ulIsWaitMsRadioCapaTimerRunning = NAS_GMM_QryTimerStatus(GMM_TIMER_WAIT_AS_MS_RADIO_CAPA_INFO);
#endif

    if (VOS_NULL_PTR == pstRcvMsg)
    {
        return;
    }

    pstRacMsg = (GRRMM_MS_RADIO_ACCESS_CAPABILITIES_IND_STRU *)pstRcvMsg;

    ucLen     = pstRacMsg->aucData[0] + 1;

    if ((ucLen > MS_RADIO_ACCESS_CAPABILITY_MAX_SIZE) || (ucLen < MS_RADIO_ACCESS_CAPABILITY_MIN_SIZE))
    {
        NAS_ERROR_LOG1(WUEPS_PID_GMM, "GMM_RcvGasTdsRadioAccessCapa: Wrong RAC Len: ", ucLen);
    }
    else
    {
        if (0 != VOS_MemCmp(g_GmmGlobalCtrl.UeInfo.aucTdsRadioCpb,
                    pstRacMsg->aucData, MS_RADIO_ACCESS_CAPABILITY_MAX_SIZE))
        {
            PS_MEM_CPY(g_GmmGlobalCtrl.UeInfo.aucTdsRadioCpb, pstRacMsg->aucData,
                       MS_RADIO_ACCESS_CAPABILITY_MAX_SIZE);

#if (FEATURE_ON == FEATURE_LTE)
            /* ����syscfg�����Ƿ�֧��L��L�Ƿ�enable״̬����ucMsRadioCapSupportLteFromAs*/
            if (NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode())
            {
                return;
            }

            g_GmmGlobalCtrl.UeInfo.ucMsRadioCapSupportLteFromAs = (VOS_UINT8)NAS_MML_IsSupportLteCapability();

            if (VOS_TRUE == ulIsWaitMsRadioCapaTimerRunning)
            {
                Gmm_TimerStop(GMM_TIMER_WAIT_AS_MS_RADIO_CAPA_INFO);

                if ((GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState)
                 || (GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState))
                {
                    NAS_GMM_RcvMsRadioCapaInfo_TimerWaitAsMsRadioCapaRunning();

                    return;
                }
            }


            /* ��ǰ�Ѿ�����ʱ���������� */
            if (VOS_TRUE == NAS_GMM_QryTimerStatus(GMM_TIMER_DELAY_RADIO_CAPA_TRIGED_RAU))
            {
                Gmm_TimerStop(GMM_TIMER_DELAY_RADIO_CAPA_TRIGED_RAU);
                Gmm_TimerStart(GMM_TIMER_DELAY_RADIO_CAPA_TRIGED_RAU);
                return;
            }

            if (g_GmmGlobalCtrl.UeInfo.ucMsRadioCapSupportLteFromAs != g_GmmGlobalCtrl.UeInfo.ucMsRadioCapSupportLteFromRegReq)
            {
                NAS_GMM_HandleMsRadioCapLteSupportChanged();
            }
#endif
        }

    }

    return;
}

VOS_VOID GMM_InitCellUpdate(VOS_UINT8 ucReadychangFLG)
{
    if (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask)
    {
        Gmm_TimerStop(GMM_TIMER_T3312);

#if (FEATURE_LTE == FEATURE_ON)
        NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_STOP);
#endif
    }

    /* force to standby״̬�������� */
    if (GMM_TRUE == gstGmmCasGlobalCtrl.ucFtsFlg)
    {
        Gmm_TimerStop(GMM_TIMER_T3314);

        gstGmmCasGlobalCtrl.ucFtsFlg = GMM_FALSE;

        if ( 0xffffffff == gstGmmCasGlobalCtrl.ulReadyTimerValue )
        {
             gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_READY;
#if (FEATURE_LTE == FEATURE_ON)
             if (NAS_GMM_TIMER_T3323_FLG == (NAS_GMM_TIMER_T3323_FLG & g_GmmTimerMng.ulTimerRunMask))
             {
                 Gmm_TimerStop(GMM_TIMER_T3323);
             }
#endif
        }
        else
        {
            gstGmmCasGlobalCtrl.ulReadyTimerValue = 0x0;
            gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_STANDBY;
#if (FEATURE_LTE == FEATURE_ON)
            if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
            {
                NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
            }
#endif
            Gmm_TimerStart(GMM_TIMER_T3312);
        }
        NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_GSM_GMM_STATE);
        gstGmmCasGlobalCtrl.ucCellUpdateFlg = GMM_FALSE;
        return;
    }

    /* READY TIMERֵΪ0�������� */
    if (0 == gstGmmCasGlobalCtrl.ulReadyTimerValue)
    {
        Gmm_TimerStop(GMM_TIMER_T3314);

        gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_STANDBY;
        NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_GSM_GMM_STATE);
        Gmm_TimerStart(GMM_TIMER_T3312);

        gstGmmCasGlobalCtrl.ucCellUpdateFlg = GMM_FALSE;
        return;
    }

    /* ����READY TIMER */
    if ( 0xffffffff != gstGmmCasGlobalCtrl.ulReadyTimerValue )
    {
        g_GmmTimerMng.aTimerInf[GMM_TIMER_T3314].ulTimerVal
            = gstGmmCasGlobalCtrl.ulReadyTimerValue;

        g_GmmTimerMng.ulTimerValMask |= GMM_TIMER_T3314_FLG;
        if ((GMM_TRUE == ucReadychangFLG))
        {
            Gmm_TimerStop(GMM_TIMER_T3314);
        }
        Gmm_TimerStart(GMM_TIMER_T3314);
    }
    else
    {
        Gmm_TimerStop(GMM_TIMER_T3314);
    }


    gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_READY;   /* GSM READY̬��־ */

#if (FEATURE_LTE == FEATURE_ON)
    if (NAS_GMM_TIMER_T3323_FLG == (NAS_GMM_TIMER_T3323_FLG & g_GmmTimerMng.ulTimerRunMask))
    {
        Gmm_TimerStop(GMM_TIMER_T3323);
    }
#endif


    NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_GSM_GMM_STATE);


    if (GMM_FALSE == gstGmmCasGlobalCtrl.ucCellUpdateFlg)
    {/* С�����±�־��Ч������֪ͨLLC����С������ */
        return;
    }

    if ( VOS_FALSE == gstGmmCasGlobalCtrl.ucReadyTimerChgFlg )
    {
        gstGmmCasGlobalCtrl.ucCellUpdateFlg     = GMM_FALSE;
        return;
    }

    /* ֪ͨLLC */
    if ((GMM_TRUE == gstGmmCasGlobalCtrl.ucCellNotifyFlg)
        && (GMM_FALSE == ucReadychangFLG))
    {
        GMM_SndLlcTriggerReq(LL_GMM_TRIG_CAUSE_CELUPD_CELL_NOTIFY);
    }
    else
    {
        GMM_SndLlcTriggerReq(LL_GMM_TRIG_CAUSE_CELUPD_NO_CELL_NOTIFY);
    }

    gstGmmCasGlobalCtrl.ucCellUpdateFlg     = GMM_FALSE;
    gstGmmCasGlobalCtrl.ucReadyTimerChgFlg   = VOS_FALSE;
    return;
}


VOS_VOID GMM_RcvGasClassMarkChangeInd( VOS_VOID *pRcvMsg )
{
    RRMM_CLASSMARK_CHANGE_IND_STRU     *pstClassMarkMsg = VOS_NULL_PTR;
    NAS_MML_MS_CAPACILITY_INFO_STRU    *pstMsCapability = VOS_NULL_PTR;

    pstClassMarkMsg = (RRMM_CLASSMARK_CHANGE_IND_STRU *)pRcvMsg;
    pstMsCapability = NAS_MML_GetMsCapability();

    /* ����classmark1 */
    NAS_GMM_UpdateClassmark1(pstMsCapability, pstClassMarkMsg);

    /* ����classmark2 */
    NAS_GMM_UpdateClassmark2(pstMsCapability, pstClassMarkMsg);

    /* ����classmark3 */
    NAS_GMM_UpdateClassmark3(pstMsCapability, pstClassMarkMsg);

    return;
}



VOS_VOID GMM_SaveReadyTimerValue(
                        VOS_UINT8 ucMsgByte                 /* ��Ϣ��ʱ��λ�õ��ֽ� */
                        )
{
    VOS_UINT8   ucUnit       = 0;       /* ������ʱ�����洢ʱ����λ */
    VOS_UINT8   ucTimerValue = 0;       /* ������ʱ�����洢ʱ�� */
    VOS_UINT32  ulLocalReadyTimer;

    #if 0
    if (GMM_FALSE == gstGmmCasGlobalCtrl.ucReadyTimerNgtFlg)
    {/* ������Э��READY TIMER */
        return;
    }

    ucUnit       = (VOS_UINT8)(ucMsgByte >> 5);             /* �õ�ʱ����λ */
    ucTimerValue = (VOS_UINT8)(ucMsgByte & 0x1F);           /* �õ�Timer Value */

    switch (ucUnit)
    {/* �ж�ʱ����λ */
    case 0:                             /* 2 seconds */
        g_GmmTimerMng.aTimerInf[GMM_TIMER_T3314].ulTimerVal
            = GMM_TIMER_T3314_VALUE;    /* ��ΪREADY TIMER��ʱ������λ�����ı� */
        gstGmmCasGlobalCtrl.ulReadyTimerValue = ucTimerValue * 2 * 1000;
        break;
    case 1:                             /* 1 minute */
        g_GmmTimerMng.aTimerInf[GMM_TIMER_T3314].ulTimerVal
            = GMM_TIMER_T3314_VALUE;    /* ��ΪREADY TIMER��ʱ������λ�����ı� */
        gstGmmCasGlobalCtrl.ulReadyTimerValue = ucTimerValue * 60 * 1000;
        break;
    case 2:                             /* decihours */
        g_GmmTimerMng.aTimerInf[GMM_TIMER_T3314].ulTimerVal
            = GMM_TIMER_T3314_VALUE;    /* ��ΪREADY TIMER��ʱ������λ�����ı� */
        gstGmmCasGlobalCtrl.ulReadyTimerValue = ucTimerValue * 360 * 1000;
        break;
    case 7:                             /* timer is deactivated */
        g_GmmTimerMng.aTimerInf[GMM_TIMER_T3314].ulTimerVal = 0;
        gstGmmCasGlobalCtrl.ulReadyTimerValue = 0;
        break;
    default:
        g_GmmTimerMng.aTimerInf[GMM_TIMER_T3314].ulTimerVal
            = GMM_TIMER_T3314_VALUE;    /* ��ΪREADY TIMER��ʱ������λ�����ı� */
        gstGmmCasGlobalCtrl.ulReadyTimerValue = ucTimerValue * 60 * 1000;
        break;
    }

    /* READY TIMER��ʱ���������� */
    gstGmmCasGlobalCtrl.ulReadyTimerCntMax
            = gstGmmCasGlobalCtrl.ulReadyTimerValue / GMM_TIMER_T3314_VALUE;
    #endif

    ucUnit       = (VOS_UINT8)(ucMsgByte >> 5);             /* �õ�ʱ����λ */
    ucTimerValue = (VOS_UINT8)(ucMsgByte & 0x1F);           /* �õ�Timer Value */
    gstGmmCasGlobalCtrl.ucReadyTimerChgFlg = VOS_FALSE;
    ulLocalReadyTimer                   = gstGmmCasGlobalCtrl.ulReadyTimerValue;
    switch (ucUnit)
    {
        case 0 :/* 2 seconds */
            gstGmmCasGlobalCtrl.ulReadyTimerValue = ucTimerValue * 2 * 1000;
            break;

        case 1 :/* 1 minute */
            gstGmmCasGlobalCtrl.ulReadyTimerValue = ucTimerValue * 60 * 1000;
            break;

        case 2 :/* decihours */
            gstGmmCasGlobalCtrl.ulReadyTimerValue = ucTimerValue * 360 * 1000;
            break;

        case 7 : /* timer is deactivated */
            gstGmmCasGlobalCtrl.ulReadyTimerValue = 0xffffffff;
            break;

        default:break;

    }
    if ( gstGmmCasGlobalCtrl.ucReadyTimerChgFlg != ulLocalReadyTimer )
    {
        gstGmmCasGlobalCtrl.ucReadyTimerChgFlg = VOS_TRUE;
    }
    return;
}

/* BEGIN: Added by liurui id:40632, 2006/3/29   PN:A32D02716 */
/*****************************************************************************
 Prototype      : GMM_CasGetMsGprsMode
 Description    : ��ȡGMM��ǰMS GPRSģʽ
                  HSS 4100 V200R001 ����
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2006-03-29
    Author      : Roger Leo
    Modification: Created function
*****************************************************************************/
VOS_UINT8 GMM_CasGetMsGprsMode(VOS_VOID)
{
    VOS_UINT8   ucMsMode = NAS_GSM_GPRS_MODE_A;
    NAS_MML_MS_MODE_ENUM_UINT8      enMsMode;

    enMsMode    = NAS_MML_GetMsMode();

    switch (enMsMode)
    {
        case NAS_MML_MS_MODE_PS_CS:
            ucMsMode = NAS_GSM_GPRS_MODE_A;
            break;
        case NAS_MML_MS_MODE_PS_ONLY:
            ucMsMode = NAS_GSM_GPRS_MODE_C_GPRS;
            break;
        case NAS_MML_MS_MODE_CS_ONLY:
            ucMsMode = NAS_GSM_GPRS_MODE_C_GSM;
            break;
        default:
            ucMsMode = NAS_GSM_GPRS_MODE_B;
            break;
    }

    return ucMsMode;
}

/*****************************************************************************
 Prototype      : GMM_CasGetGmmState
 Description    : ��ȡGMM��ǰ����״̬���Ƿ���READY״̬
                  HSS 4100 V200R001 ����
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2006-03-29
    Author      : Roger Leo
    Modification: Created function
*****************************************************************************/
VOS_UINT8 GMM_CasGetGmmState(VOS_VOID)
{
    VOS_UINT8   ucGmmState = NAS_GMM_STATE_IDLE;

    switch (gstGmmCasGlobalCtrl.GmmSrvState)
    {
        case GMM_AGB_GPRS_IDLE:
            ucGmmState = NAS_GMM_STATE_IDLE;
            break;
        case GMM_AGB_GPRS_STANDBY:
            ucGmmState = NAS_GMM_STATE_STANDYBY;
            break;
        case GMM_AGB_GPRS_READY:
            ucGmmState = NAS_GMM_STATE_READY;
            break;
        default:
            ucGmmState = NAS_GMM_STATE_IDLE;
            break;
    }

    return ucGmmState;
}
/* END:   Added by liurui id:40632, 2006/3/29   PN:A32D02716 */

/* BEGIN: Added by liurui id:40632, 2006/4/5   PN:A32D02352 */

VOS_VOID GMM_CasFsmStateChangeTo(VOS_UINT8 ucFsmSta)
{

    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    enCurRat = NAS_MML_GetCurrNetRatType();
    if ( (NAS_MML_NET_RAT_TYPE_GSM == enCurRat)
      || (NAS_MML_NET_RAT_TYPE_WCDMA == enCurRat) )
    {
        NAS_GMM_NotifyRrmmChgNonDrxMode(g_GmmGlobalCtrl.ucState, ucFsmSta);
    }

#if(FEATURE_ON == FEATURE_DSDS)
    NAS_GMM_NotifySessionAccordingStateChg(g_GmmGlobalCtrl.ucState, ucFsmSta);
#endif

    g_GmmGlobalCtrl.ucState = ucFsmSta;

    NAS_GMM_LogGmmStateInfo(g_GmmGlobalCtrl.ucState);


    NAS_GMM_StopReadyTimer_DeregStat();

    NAS_GMM_SetIdleSrvState_DeregStat();


    GMM_PrintState();

    Gmm_Com_ServiceStatus_Handle();                                               /* ֪ͨMMC����״̬                          */


    return;
}
/* END:   Added by liurui id:40632, 2006/4/5   PN:A32D02352 */


VOS_VOID NAS_GMM_RcvGprsAccessResultInd(
    VOS_VOID                           *pstMsg
)
{
    GRRGMM_GPRS_ACCESS_RESULT_IND_STRU *pstRcvMsg;

    pstRcvMsg = (GRRGMM_GPRS_ACCESS_RESULT_IND_STRU*)pstMsg;

    /* ����GAS�ϱ������ݣ�֪ͨMMC��ǰ����������״̬ */
    if (NAS_GPRS_ACCESS_SUCCESS == pstRcvMsg->enResult )
    {
        /* ����GSMģʽ��PS�����ҵ������ڽ���ע�� */
        NAS_MML_SetPsTbfStatusFlg(VOS_TRUE);

        Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_PRESENT);


#if (FEATURE_LTE == FEATURE_ON)
        if (NAS_GMM_TIMER_T3323_FLG == (NAS_GMM_TIMER_T3323_FLG & g_GmmTimerMng.ulTimerRunMask))
        {
            Gmm_TimerStop(GMM_TIMER_T3323);
        }
#endif
    }
    else
    {
        Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);
    }
}


VOS_VOID NAS_GMM_SaveGsmSysInfo(
    MMCGMM_GSM_SYS_INFO_IND_ST         *pstGsmSysInfo
)
{
    MMCGMM_GSM_SYS_INFO_IND_ST         *pstHoldGsmSysInfo = VOS_NULL_PTR;



    /* ֻ����һ��GSM��ϵͳ��Ϣ�����ͷ�ԭ���洢����Ϣ�������ڴ�й¶ */
    NAS_GMM_FreeGsmSysInfo();

    pstHoldGsmSysInfo = (MMCGMM_GSM_SYS_INFO_IND_ST *)Gmm_MemMalloc(sizeof(MMCGMM_GSM_SYS_INFO_IND_ST));
    if (VOS_NULL_PTR == pstHoldGsmSysInfo)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_GMM_SaveGsmSysInfo:WARNING: Mem alloc fail.");
        return;
    }

    /* �û����־ */
    g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk |= GMM_MSG_HOLD_FOR_GSM_SYSINFO;

    /* ����ϵͳ��Ϣ */
    Gmm_MemCpy(pstHoldGsmSysInfo, pstGsmSysInfo, sizeof(MMCGMM_GSM_SYS_INFO_IND_ST));
    g_GmmGlobalCtrl.MsgHold.ulMsgAddrForGsmSysinfo = (VOS_UINT32)pstHoldGsmSysInfo;

    return;
}
VOS_VOID NAS_GMM_SetMmT3211ExpiredDelayRauFlag(
    VOS_UINT8                           ucMmT3211ExpiredDelayRauFlag
)
{
    g_GmmGlobalCtrl.MsgHold.ucMmT3211ExpiredDelayRauFlag = ucMmT3211ExpiredDelayRauFlag;
}


VOS_UINT8 NAS_GMM_GetMmT3211ExpiredDelayRauFlag(VOS_VOID)
{
    return g_GmmGlobalCtrl.MsgHold.ucMmT3211ExpiredDelayRauFlag;
}


VOS_VOID NAS_GMM_ProcSavedMmT3211ExpiredNotify(VOS_VOID)
{
    if (VOS_FALSE == NAS_MML_IsPlmnSupportDam(NAS_MML_GetCurrCampPlmnId()))
    {
        return;
    }

    if (VOS_FALSE == NAS_GMM_GetMmT3211ExpiredDelayRauFlag())
    {
        return;
    }

    if (GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState)
    {
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
    }

    return;
}

VOS_VOID NAS_GMM_ProcSavedGsmSysInfo()
{
    if (NAS_MML_NET_RAT_TYPE_GSM != NAS_MML_GetCurrNetRatType())
    {
        return;
    }


    if (GMM_MSG_HOLD_FOR_GSM_SYSINFO
        != (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_GSM_SYSINFO))
    {
        return;
    }

    if ((GMM_GPRS_SUSPENSION == g_GmmGlobalCtrl.ucState)
     || (GMM_SUSPENDED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState)
     || (GMM_SUSPENDED_GPRS_SUSPENSION == g_GmmGlobalCtrl.ucState))
    {
        return;
    }



    if (VOS_NULL_PTR != g_GmmGlobalCtrl.MsgHold.ulMsgAddrForGsmSysinfo)
    {
        Gmm_MsgDistribute((VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForGsmSysinfo);
    }


    return;
}



VOS_VOID NAS_GMM_FreeGsmSysInfo()
{
    VOS_VOID                           *pAddr = VOS_NULL_PTR;

    if (GMM_MSG_HOLD_FOR_GSM_SYSINFO
        != (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_GSM_SYSINFO))
    {
        return;
    }

    /* ���������־ */
    g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_GSM_SYSINFO;

    /* ������buffer�����е���Ϣ�ͷ� */
    if (VOS_NULL_PTR != g_GmmGlobalCtrl.MsgHold.ulMsgAddrForGsmSysinfo)
    {
        pAddr = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForGsmSysinfo;
        Gmm_MemFree(pAddr);
        g_GmmGlobalCtrl.MsgHold.ulMsgAddrForGsmSysinfo = VOS_NULL_PTR;
    }

    return;
}


VOS_VOID NAS_GMM_InitCellUpdate_RcvSysInfo(VOS_UINT8 ucReadychangFLG)
{
    if (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask)
    {
        Gmm_TimerStop(GMM_TIMER_T3312);

#if (FEATURE_LTE == FEATURE_ON)
        NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_STOP);
#endif
    }

    /* force to standby״̬�������� */
    if (GMM_TRUE == gstGmmCasGlobalCtrl.ucFtsFlg)
    {
        Gmm_TimerStop(GMM_TIMER_T3314);

        gstGmmCasGlobalCtrl.ucFtsFlg = GMM_FALSE;

        if ( 0xffffffff == gstGmmCasGlobalCtrl.ulReadyTimerValue )
        {
             gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_READY;
#if (FEATURE_LTE == FEATURE_ON)
             if (NAS_GMM_TIMER_T3323_FLG == (NAS_GMM_TIMER_T3323_FLG & g_GmmTimerMng.ulTimerRunMask))
             {
                 Gmm_TimerStop(GMM_TIMER_T3323);
             }
#endif
        }
        else
        {
            gstGmmCasGlobalCtrl.ulReadyTimerValue = 0x0;
            gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_STANDBY;
#if (FEATURE_LTE == FEATURE_ON)
            if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
            {
                NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
            }
#endif
            Gmm_TimerStart(GMM_TIMER_T3312);
        }
        NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_GSM_GMM_STATE);
        gstGmmCasGlobalCtrl.ucCellUpdateFlg = GMM_FALSE;
        return;
    }

    /* READY TIMERֵΪ0�������� */
    if (0 == gstGmmCasGlobalCtrl.ulReadyTimerValue)
    {
        Gmm_TimerStop(GMM_TIMER_T3314);

        gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_STANDBY;
        NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_GSM_GMM_STATE);
        Gmm_TimerStart(GMM_TIMER_T3312);

        gstGmmCasGlobalCtrl.ucCellUpdateFlg = GMM_FALSE;
        return;
    }

    /* ����READY TIMER */
    if ( 0xffffffff != gstGmmCasGlobalCtrl.ulReadyTimerValue )
    {
        g_GmmTimerMng.aTimerInf[GMM_TIMER_T3314].ulTimerVal
            = gstGmmCasGlobalCtrl.ulReadyTimerValue;

        g_GmmTimerMng.ulTimerValMask |= GMM_TIMER_T3314_FLG;
        if ((GMM_TRUE == ucReadychangFLG))
        {
            Gmm_TimerStop(GMM_TIMER_T3314);
        }
        Gmm_TimerStart(GMM_TIMER_T3314);
    }
    else
    {
        Gmm_TimerStop(GMM_TIMER_T3314);
    }


    gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_READY;   /* GSM READY̬��־ */

#if (FEATURE_LTE == FEATURE_ON)
    if (NAS_GMM_TIMER_T3323_FLG == (NAS_GMM_TIMER_T3323_FLG & g_GmmTimerMng.ulTimerRunMask))
    {
        Gmm_TimerStop(GMM_TIMER_T3323);
    }
#endif


    NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_GSM_GMM_STATE);


    if (GMM_FALSE == gstGmmCasGlobalCtrl.ucCellUpdateFlg)
    {/* С�����±�־��Ч������֪ͨLLC����С������ */
        return;
    }

    /* ֪ͨLLC */
    if ((GMM_TRUE == gstGmmCasGlobalCtrl.ucCellNotifyFlg)
      && (GMM_FALSE == ucReadychangFLG))
    {
        GMM_SndLlcTriggerReq(LL_GMM_TRIG_CAUSE_CELUPD_CELL_NOTIFY);
    }
    else
    {
        GMM_SndLlcTriggerReq(LL_GMM_TRIG_CAUSE_CELUPD_NO_CELL_NOTIFY);
    }

    gstGmmCasGlobalCtrl.ucCellUpdateFlg     = GMM_FALSE;
    gstGmmCasGlobalCtrl.ucReadyTimerChgFlg   = VOS_FALSE;
    return;
}


VOS_VOID NAS_GMM_NotifyRrmmChgNonDrxMode(
    VOS_UINT8                           ucCurState,
    VOS_UINT8                           ucTargetState
)
{

    /* 44060Э��5.5.1.5������:
    When initiating the MM procedures for GPRS attach and routeing area update defined in 3GPP TS 24.008,
    the mobile station shall enter the MM non-DRX mode period. This period ends when either of the messages GPRS ATTACH ACCEPT,
    GPRS ATTACH REJECT, ROUTING AREA UPDATE ACCEPT or ROUTING AREA UPDATE REJECT is received by the mobile station.
    This period also ends after timeout when waiting for any of these messages
    ��ATTACH��RAU��ʼ������Ӧ�ñ�����MM non-DRX״̬,����������GMM
        ״̬�ĸı��ж��Ƿ�Ӧ�ø�GAS����֪ͨ��Ϣ��������
    */
    RRMM_GMM_PROC_TYPE_ENUM_UINT16      enGprsProcType;
    RRMM_GMM_PROC_FLAG_ENUM_UINT16      enGprsProcFlg;

    NAS_MML_GMM_PROC_TYPE_ENUM_UINT16   enMmlGmmProcType;
    NAS_MML_GMM_PROC_FLAG_ENUM_UINT16   enMmlGmmProcFlag;

    enGprsProcType = RRMM_GMM_PROC_TYPE_INVALID;
    enGprsProcFlg  = RRMM_GMM_PROC_FLAG_INVALID;

    if ( GMM_REGISTERED_INITIATED == ucCurState )
    {
        enGprsProcType = RRMM_GMM_PROC_TYPE_ATTACH;

        if ( GMM_REGISTERED_INITIATED != ucTargetState )
        {
            enGprsProcFlg = RRMM_GMM_PROC_FLAG_FINISH;
        }
        else
        {
            enGprsProcFlg = RRMM_GMM_PROC_FLAG_START;
        }
    }
    else if ( GMM_ROUTING_AREA_UPDATING_INITIATED == ucCurState )
    {
        if ( GMM_TRUE == g_GmmRauCtrl.ucPeriodicRauFlg )
        {
            enGprsProcType = RRMM_GMM_PROC_TYPE_PERIOD_RAU;
        }
        else
        {
            enGprsProcType = RRMM_GMM_PROC_TYPE_NORMAL_RAU;
        }

        if ( GMM_ROUTING_AREA_UPDATING_INITIATED != ucTargetState )
        {
            enGprsProcFlg = RRMM_GMM_PROC_FLAG_FINISH;
        }
        else
        {
            enGprsProcFlg = RRMM_GMM_PROC_FLAG_START;
        }
    }
    else if ( GMM_REGISTERED_INITIATED == ucTargetState )
    {
        enGprsProcType = RRMM_GMM_PROC_TYPE_ATTACH;
        enGprsProcFlg = RRMM_GMM_PROC_FLAG_START;
    }
    else if ( GMM_ROUTING_AREA_UPDATING_INITIATED == ucTargetState )
    {
        if ( GMM_TRUE == g_GmmRauCtrl.ucPeriodicRauFlg )
        {
            enGprsProcType = RRMM_GMM_PROC_TYPE_PERIOD_RAU;
        }
        else
        {
            enGprsProcType = RRMM_GMM_PROC_TYPE_NORMAL_RAU;
        }

        enGprsProcFlg = RRMM_GMM_PROC_FLAG_START;
    }
    else
    {
    }

    if ( RRMM_GMM_PROC_TYPE_INVALID != enGprsProcType )
    {
        NAS_GMM_SndRrmmGmmProcNotify(enGprsProcType, enGprsProcFlg);

        NAS_GMM_ConverRrcGmmProcTypeToMml(enGprsProcType, &enMmlGmmProcType);
        NAS_GMM_ConverRrcGmmProcFlagToMml(enGprsProcFlg, &enMmlGmmProcFlag);
        NAS_MML_SetGmmProcType(enMmlGmmProcType);
        NAS_MML_SetGmmProcFlag(enMmlGmmProcFlag);
    }
}

VOS_VOID NAS_GMM_UpdateClassmark1(
    NAS_MML_MS_CAPACILITY_INFO_STRU    *pstMsCapability,
    RRMM_CLASSMARK_CHANGE_IND_STRU     *pstClassMarkMsg
)
{
    VOS_UINT8                           ucClassmark2Len;


    ucClassmark2Len = pstClassMarkMsg->ucClassmark2Len;

    /* ���ȷǷ���Ϊ0��ʹ�� */
    if ((MS_CLASSMARK2_MAX_LEN < ucClassmark2Len)
     || (0                    == ucClassmark2Len))
    {
        NAS_ERROR_LOG1(WUEPS_PID_GMM, "NAS_GMM_UpdateClassmark2: Wrong classmark2 Len: ", ucClassmark2Len);
    }
    else
    {
        /* pstClassMarkMsg->aucClassmark2[0]��classmark2��ʵ�ʳ��ȣ���aucClassmark2[1]��ʼ����ʵ�ʵ�ֵ */
        pstMsCapability->ucClassmark1 = pstClassMarkMsg->aucClassmark2[1];
    }

    return;
}



VOS_VOID NAS_GMM_UpdateClassmark2(
    NAS_MML_MS_CAPACILITY_INFO_STRU    *pstMsCapability,
    RRMM_CLASSMARK_CHANGE_IND_STRU     *pstClassMarkMsg
)
{
    VOS_UINT8                           ucClassmark2Len;


    ucClassmark2Len = pstClassMarkMsg->ucClassmark2Len;

    /* ���ȷǷ���Ϊ0��ʹ�� */
    if ((MS_CLASSMARK2_MAX_LEN < ucClassmark2Len)
     || (0                    == ucClassmark2Len))
    {
        NAS_ERROR_LOG1(WUEPS_PID_GMM, "NAS_GMM_UpdateClassmark2: Wrong classmark2 Len: ", ucClassmark2Len);
    }
    else
    {
        if (0 != PS_MEM_CMP(pstMsCapability->aucClassmark2,
                            pstClassMarkMsg->aucClassmark2, MS_CLASSMARK2_MAX_LEN))
        {
            /* pstClassMarkMsg->aucClassmark2[0]��classmark2��ʵ�ʳ��ȣ���aucClassmark2[1]��ʼ����ʵ�ʵ�ֵ */
            pstMsCapability->aucClassmark2[0]   = pstClassMarkMsg->aucClassmark2[0];

            PS_MEM_CPY(&(pstMsCapability->aucClassmark2[1]), &(pstClassMarkMsg->aucClassmark2[1]), pstClassMarkMsg->aucClassmark2[0]);
        }
    }

    return;

}


VOS_VOID NAS_GMM_UpdateClassmark3(
    NAS_MML_MS_CAPACILITY_INFO_STRU    *pstMsCapability,
    RRMM_CLASSMARK_CHANGE_IND_STRU     *pstClassMarkMsg
)
{
    VOS_UINT8                           ucFddLen;
    VOS_UINT8                           ucTddLen;


    ucFddLen = pstClassMarkMsg->ucClassmark3FddLen;

    /* ���ȷǷ���Ϊ0��ʹ�� */
    if ((MS_CLASSMARK3_MAX_LEN < ucFddLen)
     || (0                    == ucFddLen))
    {
        NAS_ERROR_LOG1(WUEPS_PID_GMM, "GMM_RcvGasClassMarkChangeInd: Wrong fdd classmark3 Len: ", ucFddLen);
    }
    else
    {
        if (0 != PS_MEM_CMP(&(pstMsCapability->aucFddClassmark3[1]),
                            pstClassMarkMsg->aucClassmark3Fdd, MS_CLASSMARK3_MAX_LEN))
        {
            pstMsCapability->aucFddClassmark3[0] = ucFddLen;
            PS_MEM_CPY(&(pstMsCapability->aucFddClassmark3[1]), pstClassMarkMsg->aucClassmark3Fdd, ucFddLen);
        }
    }

    ucTddLen = pstClassMarkMsg->ucClassmark3TddLen;

    if ((MS_CLASSMARK3_MAX_LEN < ucTddLen)
     || (0                     == ucTddLen))
    {
        NAS_ERROR_LOG1(WUEPS_PID_GMM, "GMM_RcvGasClassMarkChangeInd: Wrong tdd classmark3 Len: ", ucTddLen);
    }
    else
    {
        if (0 != VOS_MemCmp(&(pstMsCapability->aucTddClassmark3[1]),
                            pstClassMarkMsg->aucClassmark3Tdd, MS_CLASSMARK3_MAX_LEN))
        {
            pstMsCapability->aucTddClassmark3[0] = ucTddLen;
            PS_MEM_CPY(&(pstMsCapability->aucTddClassmark3[1]), pstClassMarkMsg->aucClassmark3Tdd, ucTddLen);
        }
    }

    return;

}


/*lint -restore */


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif
