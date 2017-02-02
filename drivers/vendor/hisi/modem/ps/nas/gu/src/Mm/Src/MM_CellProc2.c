

#include        "MM_Inc.h"
#include        "GmmMmInterface.h"
#include        "NasMmcProcNvim.h"
#include        "MM_Ext.h"
#include        "NasMmEcall.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_MM_CELLPROC2_C

/*lint -save -e958 */


VOS_VOID Mm_Cell_S3_E13(VOS_VOID *pMsg)
{
    GMMMM_NETWORK_DETACH_IND_STRU      *pstNetWkDetachInd;


    if (MM_FALSE == NAS_MM_RcvGmmNetworkDetechInd(pMsg))
    {
        return;

    }

    if (NAS_MML_MS_MODE_PS_CS == NAS_MML_GetMsMode())
    {
    }

    pstNetWkDetachInd = (GMMMM_NETWORK_DETACH_IND_STRU*)pMsg;

    if (VOS_TRUE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNtMod))
    {                                                                           /* ���ΪA+I,�Ҳ�������B��A+II����ĳ���    */
        if (GMMMM_NET_DETACH_REATTACH == pstNetWkDetachInd->enDetachType)
        {
            NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
        }
        else if (GMMMM_NET_DETACH_IMSI == pstNetWkDetachInd->enDetachType)
        {
            Mm_ComSaveProcAndCauseVal(MM_NET_DETACH_PROC,
                                      NAS_MML_REG_FAIL_CAUSE_NTDTH_IMSI);       /* ��¼���̺�ԭ��ֵ                         */

            g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;          /* ���÷���״̬                             */
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                 /* ��¼ǰ״̬                               */
            Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S3_E13:INFO: MmServiceState is MM_ATTEMPTING_TO_UPDATE");

            NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED);
            g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                                                    ~MM_MS_ID_TMSI_PRESENT;     /* �����־λ                               */
            NAS_MML_InitUeIdTmsiInvalid();
            Mm_ComDelLai();                                                     /* ɾ��LAI                                  */
            Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                             MM_CKSN_INVALID);
            /* Modified by h00313353 for iteration 9, 2015-2-4, begin */
            if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
            {
                Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);
                Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFKC_ID);               /* ����SIM������״̬                        */
            }
            else
            {
                Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);
                Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKEYS_ID);            /* ����SIM������״̬                        */
            }
            /* Modified by h00313353 for iteration 9, 2015-2-4, end */



            Mm_ComProcCauseClear();
        }
        else
        {
            Mm_ComNetDetachCauseHandle(
                (VOS_UINT8)pstNetWkDetachInd->ulDetachCause);                     /* ����DETACHԭ��ֵ�Ĺ�������               */
        }
    }
    else
    {                                                                           /* ���Ϊ��A+Iģʽ                          */
        if (GMMMM_NET_DETACH_REATTACH == pstNetWkDetachInd->enDetachType)
        {
            NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
        }
        else if (GMMMM_NET_DETACH_IMSI == pstNetWkDetachInd->enDetachType)
        {
            Mm_ComSaveProcAndCauseVal(MM_NET_DETACH_PROC,
                                      NAS_MML_REG_FAIL_CAUSE_NTDTH_IMSI);                 /* ��¼���̺�ԭ��ֵ                         */

            g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;          /* ���÷���״̬                             */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S3_E13:INFO: MmServiceState is MM_ATTEMPTING_TO_UPDATE");

            NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED);
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                 /* ��¼ǰ״̬                               */
            Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);
            g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                                                    ~MM_MS_ID_TMSI_PRESENT;     /* �����־λ                               */
            NAS_MML_InitUeIdTmsiInvalid();
            Mm_ComDelLai();                                                     /* ɾ��LAI                                  */
            Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                             MM_CKSN_INVALID);

            /* Modified by h00313353 for iteration 9, 2015-2-4, begin */
            if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
            {
                Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);
                Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFKC_ID);               /* ����SIM������״̬                        */
            }
            else
            {
                Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);
                Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKEYS_ID);            /* ����SIM������״̬                        */
            }
            /* Modified by h00313353 for iteration 9, 2015-2-4, end */



            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S3_E13:NORMAL: STATUS is MM_IDLE_ATTEMPTING_TO_UPDATE");
            Mm_ComProcCauseClear();
        }
        else
        {
            Mm_ComNetDetachCauseHandle(
                (VOS_UINT8)pstNetWkDetachInd->ulDetachCause);                     /* ����DETACHԭ��ֵ�Ĺ�������               */
        }
    }
}
VOS_VOID Mm_Cell_S3_E15(VOS_VOID *pMsg)
{
    GMMMM_LU_INITIATION_STRU    *pstMmcLuIni;

    if (MM_FALSE == Mm_RcvGmmLuIni(pMsg))
    {
        return;
    }

    pstMmcLuIni = (GMMMM_LU_INITIATION_STRU*)pMsg;

    if(  (GMMMM_NO_TIMER_EXPIRED == pstMmcLuIni->enTimerExpiredFlg)
       &&(VOS_FALSE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg))
    {
        return;                                                              /*�Ƕ�ʱ����ʱ�����LU�����ǵ�LAIû�ı�ʱΪ��ȥ��Gs������ */
    }

    if ((VOS_FALSE == NAS_MML_GetPsRestrictRegisterFlg())
     && ((GMMMM_T3312_EXPIRED == pstMmcLuIni->enTimerExpiredFlg)
      || (GMMMM_T3412OrT3423_EXPIRED == pstMmcLuIni->enTimerExpiredFlg)))
    {
        g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_PERIODIC_UPDATING;        /* ����LU����Ϊ����                         */
    }
    else
    {
        g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;                /* ����LU����ΪNORMAL                       */
    }

    Mm_ComLuOnly();                                                          /* ����LU����                               */

    return;
}

/*******************************************************************************
  Module:   Mm_Cell_S3_E16
  Function: ��MM IDLE NORMAL SERVICE״̬���յ�
            GMMMM_AUTHENTICATON_FAILURE_IND�Ĵ���
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��     2003.12.09  �°�����
*******************************************************************************/
VOS_VOID Mm_Cell_S3_E16(VOS_VOID *pMsg)
{
    VOS_UINT8 ucCause;

    if (MM_FALSE == Mm_RcvGmmAuthFailInd(pMsg))
    {
        return;
    }

    if (LOCATION_UPDATING_INITIATED == g_MmGlobalInfo.ucState)
    {
        ucCause = NAS_OM_MM_CAUSE_AUT_NETWORK_REJECT;
        NAS_EventReport(WUEPS_PID_MM, NAS_OM_EVENT_LOCATION_UPDATE_FAILURE,
                        &ucCause, NAS_OM_EVENT_LAU_FAIL_LEN);
    }
    Mm_ComAuthenRcvAuthenRej();                                                 /* ���ü�Ȩʧ�ܵĹ�������                   */

    NAS_MM_UpdateEquPlmnInfo(NAS_MML_REG_FAIL_CAUSE_AUTH_REJ);

    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                MM_MMC_LU_RESULT_FAILURE,
                                NAS_MML_REG_FAIL_CAUSE_AUTH_REJ);
}
VOS_VOID Mm_Cell_S3_E17(VOS_VOID *pMsg)
{
    if (MM_FALSE == Mm_RcvGmmCombinedRauInitiation(pMsg))
    {
        return;
    }
    NAS_MML_SetDelayedCsfbLauFlg(VOS_FALSE);

    if (VOS_FALSE == NAS_MML_GetCsAttachAllowFlg())
    {
        return;
    }

    /* ��ΪMM_WAIT_FOR_ATTACHΪ��̬,�����ʱ����,������ע��ʧ��ʱ,
       ��ָ���ע��ǰ��״̬,��ʱ�ָ���MM_WAIT_FOR_ATTACH��Ӱ��ҵ�� */
    if (MM_WAIT_FOR_ATTACH != g_MmGlobalInfo.ucState)
    {
        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                         /* ��¼ǰ״̬                               */
    }
    Mm_ComSetMmState(LOCATION_UPDATING_PENDING);

    g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg = MM_FALSE;


    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S3_E17:NORMAL: STATUS is  LOCATION_UPDATING_PENDING");
}

/*******************************************************************************
  Module:   Mm_Cell_S17_E17
  Function: ��LOCATION UPDATING PENDING״̬���յ�GMMMM_COMBINED_RAU_INITIATION�Ĵ���
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ŷ����      2009.03.11   �°�����
*******************************************************************************/
VOS_VOID Mm_Cell_S17_E17(VOS_VOID *pMsg)
{
    /* ��GSM�£����ԭ���յ�COMBINED_RAU_ACCEPTED with PS ONLY ACCEPTED, 5��ʧ�ܺ�MM������ʱ��MM_TIMER_DELAY_LU_GSM
       �ӳ�1�뷢��LU, �����ʱ���յ�GMM������ע�Ὺʼ��Ϣ������ͣ���ö�ʱ��������ͬʱ����RAU��LU */
    Mm_TimerStop(MM_TIMER_DELAY_LU_GSM);
}




VOS_VOID Mm_Cell_S4_E5(VOS_VOID *pMsg)
{
    VOS_UINT8                           ucLaChgFlg = VOS_FALSE;
    VOS_UINT8                           ucUserSpecificSearchFLg;
#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulCsfbExistFlag;

    /* ȡ��CSFB�Ƿ���ڵı�־ */
    ulCsfbExistFlag         = NAS_MML_IsCsfbServiceStatusExist();
#endif

    if (VOS_FALSE == NAS_MML_GetCsAttachAllowFlg())
    {
        NAS_MM_ProcMmcMmSysInfoInd_CsAttachNotAllow();

        return;
    }

    if (VOS_TRUE == NAS_MM_IsCsForbidden())
    {
        NAS_MM_ProcCsForbidenFlg_RcvSysInfoInd(g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg);

        return;
    }

    if (VOS_TRUE == NAS_MML_GetCsRestrictRegisterFlg())
    {
        NAS_MM_ProcMmcMmSysInfoInd_CsRegisterRestrict();

        return;
    }

    ucUserSpecificSearchFLg = Mm_Get_UserSpecificSearchFlg_From_SysInfo(pMsg);

    ucLaChgFlg = NAS_MML_IsCsLaiChanged();


    if ((VOS_TRUE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNewNtMod))
#if  (FEATURE_ON == FEATURE_LTE)
     && (VOS_FALSE == ulCsfbExistFlag)
#endif
     )
    {                                                                           /* ���ΪA+I,�Ҳ�������B��A+II����ĳ���    */
        g_MmGlobalInfo.ucNtMod = g_MmGlobalInfo.ucNewNtMod;

        /* RACΪ0�ĳ��� */
        if ((MM_UNSUPPORT_GPRS == g_MmGlobalInfo.usRac)
         || (MMCMM_FORBIDDEN_PLMN_FOR_GPRS == g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg))
        {
            NAS_MM_SetLikeBFlg();
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S4_E5:INFO: MmLikeB is MM_TRUE");

            if ((VOS_TRUE == NAS_MML_IsCampLaiInfoChanged())
             || (VOS_TRUE == ucUserSpecificSearchFLg))
            {
                /* LAI�ı�,�����û������ָ������ʱ,����LU���� */
                g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;       /* ����LU����                               */
                Mm_ComLuOnly();                                             /* LU REQ                                   */
            }
        }
    }
    else
    {                                                                           /* ��A+Iģʽ                                */
#if (FEATURE_ON == FEATURE_LTE)
        if (VOS_TRUE == NAS_MM_RcvSysInfoSurpportLte_PreProc())
        {
            return;
        }
#endif

        if (g_MmGlobalInfo.ucNtMod == g_MmGlobalInfo.ucNewNtMod)
        {
            if ((NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == NAS_MML_GetCsUpdateStatus())
                && (MM_TRUE == g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg)
                && (VOS_FALSE == ucLaChgFlg))
            {
                g_MmGlobalInfo.LuInfo.ucLuType =
                                MM_IE_LUT_PERIODIC_UPDATING;            /* ����LU����                               */
                Mm_ComLuOnly();                                         /* ����LU REQ                               */
            }
            else if ( (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == NAS_MML_GetCsUpdateStatus())
                   && (VOS_FALSE == ucLaChgFlg))
            {
                if ((MM_TRUE == g_MmGlobalInfo.ucPowerOnFlg)
                 && (MM_ATT_NEED == g_MmGlobalInfo.ucAttFlg))
                {
                    g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_IMSI_ATTACH;
                    Mm_ComLuOnly();
                }
                else if (VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
                {
                    g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;
                    Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL,
                           "Mm_Cell_S4_E5:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");


                    Mm_SndRrNasInfoChgReq(MM_NAS_INFO_SYNC_AS_FLG);


                    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                                MM_MMC_LU_RESULT_SUCCESS,
                                                NAS_MML_REG_FAIL_CAUSE_NULL);
                }
                else
                {
                }
            }
            else if ((VOS_FALSE        == NAS_MML_IsCampLaiInfoChanged())
                  && (MM_TIMER_RUNNING == gstMmTimer[MM_TIMER_T3212].ucTimerStatus)
                  && (VOS_FALSE        == ucUserSpecificSearchFLg))
            {
                /* ��ǰפ��С�����ϴ�פ��С����ͬ������T3212�������У���ʱ����Ҫ����LAU����T3212��ʱ���� */
                Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);


                Mm_SndRrNasInfoChgReq(MM_NAS_INFO_SYNC_AS_FLG);


                /* �ϱ�ע��ʧ��,��֤����״̬����ȷ�� */
                NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                            MM_MMC_LU_RESULT_FAILURE,
                                            NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE);

                NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                         NAS_MML_REG_FAIL_CAUSE_NULL);
            }
            else
            {
                g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;   /* ����LU����                               */
                Mm_ComLuOnly();                                         /* ����LU REQ                               */
            }
        }
        else
        {
            Mm_ComNetModeChange();
        }
    }

}
VOS_VOID Mm_Cell_S4_E15(VOS_VOID *pMsg)
{
    GMMMM_LU_INITIATION_STRU            *pstLuIniMsg;

    pstLuIniMsg  = (GMMMM_LU_INITIATION_STRU *)pMsg;

    if (MM_FALSE == Mm_RcvGmmLuIni(pMsg))
    {
        return;

    }

    if (GMMMM_T3412OrT3423_EXPIRED == pstLuIniMsg->enTimerExpiredFlg)
    {
        /* ����LU����Ϊ���� */
        g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_PERIODIC_UPDATING;
    }
    else
    {
        g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;                       /* ����LU����ΪNORMAL                       */
    }

    Mm_ComLuOnly();                                                             /* ����LU����                               */
}
VOS_VOID Mm_Cell_S6_E15(VOS_VOID *pMsg)
{
    GMMMM_LU_INITIATION_STRU    *pstMmcLuIni;

    if (MM_FALSE == Mm_RcvGmmLuIni(pMsg))
    {
        return;

    }

    pstMmcLuIni = (GMMMM_LU_INITIATION_STRU*)pMsg;

    if ((VOS_TRUE == NAS_MML_GetCsRestrictRegisterFlg())
        && (GMMMM_T3312_EXPIRED == pstMmcLuIni->enTimerExpiredFlg) )
    {
        g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg = MM_TRUE;
    }

    return;
}


VOS_VOID Mm_Cell_S5_E5(VOS_VOID *pMsg)
{
    VOS_UINT32                          ucLaChgFlg;

    VOS_UINT8                           ucUserSpecificSearchFlg;
    VOS_UINT32                          ul3211Status;

    VOS_UINT32                          ulT3213Status;

#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                                              ulCsfbExistFlag;
    VOS_UINT32                          ulIsTestCard;

    ulIsTestCard    = NAS_USIMMAPI_IsTestCard();

    /* ȡ��CSFB�Ƿ���ڵı�־ */
    ulCsfbExistFlag     = NAS_MML_IsCsfbServiceStatusExist();

#endif

    if (VOS_FALSE == NAS_MML_GetCsAttachAllowFlg())
    {
        NAS_MM_ProcMmcMmSysInfoInd_CsAttachNotAllow();

        return;
    }

    if (VOS_TRUE == NAS_MM_IsCsForbidden())
    {
        NAS_MM_ProcCsForbidenFlg_RcvSysInfoInd(g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg);

        return;
    }

    if (VOS_TRUE == NAS_MML_GetCsRestrictRegisterFlg())
    {
        NAS_MM_ProcMmcMmSysInfoInd_CsRegisterRestrict();

        return;
    }



    ul3211Status = NAS_MM_QryTimerStatus(MM_TIMER_T3211);


    ulT3213Status = NAS_MM_QryTimerStatus(MM_TIMER_T3213);

    ucUserSpecificSearchFlg = Mm_Get_UserSpecificSearchFlg_From_SysInfo(pMsg);

    ucLaChgFlg   = NAS_MML_IsCsLaiChanged();

    if (VOS_TRUE == NAS_MML_IsCampLaiInfoChanged())
    {
        g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = 0;
        g_MmGlobalInfo.LuInfo.ucImmAccRejLuAttmptCnt = 0;
        g_MmGlobalInfo.LuInfo.ucT3213AttmptCnt = 0;
    }

    if ( (MM_TIMER_RUNNING == NAS_MM_QryTimerStatus(MM_TIMER_T3213))
      && (MM_TRUE == g_MmGlobalInfo.MsCsInfo.ucCellChgFlg) )
    {
        /* ���С����Ϣ�ı䣬���������ʧ��ԭ��ֵ����T3213��ʱ����ʱʱ������LAU */
        NAS_MM_SetEstCnfResult(RRC_NAS_EST_RESULT_BUTT);
    }

    if ((VOS_TRUE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNewNtMod))
     && (MM_FALSE == g_MmGlobalInfo.ucLikeNetmode2)
#if  (FEATURE_ON == FEATURE_LTE)
     && (VOS_FALSE == ulCsfbExistFlag)
#endif
       )
    {                                                                           /* ���ΪA+I,�Ҳ�������B��A+II����ĳ���    */
        g_MmGlobalInfo.ucNtMod = g_MmGlobalInfo.ucNewNtMod;

        if ( (VOS_TRUE == NAS_MML_GetPsRestrictRegisterFlg())
          || (MM_UNSUPPORT_GPRS == g_MmGlobalInfo.usRac)
          || (MMCMM_FORBIDDEN_PLMN_FOR_GPRS == g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg))
        {                                                                       /* RACΪ0�ĳ���                             */
            NAS_MM_SetLikeBFlg();

            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S5_E5:INFO: MmLikeB is MM_TRUE");

            if ((VOS_TRUE       == NAS_MML_IsCampLaiInfoChanged())
             || ((VOS_TRUE      == ucUserSpecificSearchFlg)
              && (MM_TIMER_STOP == ul3211Status)))
            {
                /* LAI�����ı�,�����û�ָ������ʱ,ǿ��ִ��LU���� */
                g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;       /* ����LU����                               */
                Mm_ComLuOnly();                                             /* LU REQ                                   */
            }
            else if ((MM_TRUE == g_MmGlobalInfo.LuInfo.ucRetryFlg)
                   &&(MM_TRUE == g_MmGlobalInfo.MsCsInfo.ucCellChgFlg))
            {
                g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;       /* ����LU����                               */
                Mm_ComLuOnly();                                             /* ����LU REQ                               */
                g_MmGlobalInfo.MsCsInfo.ucCellChgFlg = MM_FALSE;
            }
            else if (VOS_TRUE == NAS_MML_GetDelayedCsfbLauFlg())
            {
                g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;       /* ����LU����                               */
                Mm_ComLuOnly();                                             /* LU REQ                                   */
            }
            else
            {
                g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;       /* ����LU����                               */
                if (VOS_FALSE == g_MmGlobalInfo.ucRetryLauFlg)
                {
                    /* ��MMC����CSע����,��PSע��ʧ�ܣ���������Ҫ��MMC�ϱ�ԭ��ֵΪOTHER CAUSE */
                    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                                MM_MMC_LU_RESULT_FAILURE,
                                                NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE);          /* ��MMC����MMCMM_LU_RESULT_IND,ʹMMCǨ��״̬ */
                    NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                             NAS_MML_REG_FAIL_CAUSE_NULL);                    /* ��MMC����MMCMM_LU_RESULT_IND,ʹMMCǨ��״̬ */
                }

            }
        }
        else
        {                                                                       /* RAC��������                              */
            /*stop T3211*/
            Mm_TimerStop(MM_TIMER_T3211);
            g_MmGlobalInfo.LuInfo.ucImmAccRejLuAttmptCnt = 0;
            g_MmGlobalInfo.LuInfo.ucLuAttmptCnt          = 0;
        }
    }
    else
    {                                                                           /* ��A+I                                    */
#if (FEATURE_ON == FEATURE_LTE)
        if (VOS_TRUE == NAS_MM_RcvSysInfoSurpportLte_PreProc())
        {
            return;
        }
#endif

        if (g_MmGlobalInfo.ucNtMod != g_MmGlobalInfo.ucNewNtMod)
        {
            Mm_TimerStop(MM_TIMER_T3211);
            Mm_ComNetModeChange();
        }
        else if((NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == NAS_MML_GetCsUpdateStatus())
             && (VOS_FALSE                              == ucLaChgFlg))
        {
            Mm_ComSysInfoHandleWithLaiNoChange(0);
            if (VOS_TRUE == ulIsTestCard)
            {
                Mm_TimerStop(MM_TIMER_T3213);
            }
        }
        else if ((VOS_TRUE == NAS_MML_IsCampLaiInfoChanged())
              || ((VOS_TRUE      == ucUserSpecificSearchFlg)
               && (MM_TIMER_STOP == ul3211Status)))
        {
            /* LAI�����ı�,�����û�ָ������ʱ,ǿ��ִ��LU���� */
            g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;
            Mm_ComLuOnly();
        }
        else if ((MM_TRUE == g_MmGlobalInfo.LuInfo.ucRetryFlg)
            && (MM_TRUE == g_MmGlobalInfo.MsCsInfo.ucCellChgFlg))
        {
            g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;           /* ����LU����                               */
            Mm_ComLuOnly();                                                 /* ����LU REQ                               */
            g_MmGlobalInfo.MsCsInfo.ucCellChgFlg = MM_FALSE;
        }
        else
        {
            g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;

            if (VOS_FALSE == g_MmGlobalInfo.ucRetryLauFlg)
            {
                /* ��MMC����CSע����,��PSע��ʧ�ܣ���������Ҫ��MMC�ϱ�ԭ��ֵΪOTHER CAUSE */
                NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                            MM_MMC_LU_RESULT_FAILURE,
                                            NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE);                 /* ��MMC����MMCMM_LU_RESULT_IND,ʹMMCǨ��״̬ */
                NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                         NAS_MML_REG_FAIL_CAUSE_NULL);                    /* ��MMC����MMCMM_LU_RESULT_IND,ʹMMCǨ��״̬ */
            }

        }

        /* ��·�ͷź������·���LAU,�������յ�sysinfo��û�з���LAU */
        if ((VOS_TRUE == g_MmGlobalInfo.ucRetryLauFlg)
            && (WAIT_FOR_RR_CONNECTION_LOCATION_UPDATING != g_MmGlobalInfo.ucState))
        {
            Mm_ComLuOnly();
        }

    }

    NAS_MM_ProcT3213AttemptCounter(ulT3213Status);

    /* ��־��λ */
    g_MmGlobalInfo.ucRetryLauFlg = VOS_FALSE;

    Mm_DealWithBuffMsg();

}


VOS_VOID Mm_Cell_S6_E5(VOS_VOID *pMsg)
{
    VOS_UINT32                          ulLaiChangeFlag;
    VOS_UINT8                           ucUserSpecificSearchFlg = 0;

#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulCsfbExistFlag;

    /* ȡ��CSFB�Ƿ���ڵı�־ */
    ulCsfbExistFlag     = NAS_MML_IsCsfbServiceStatusExist();
#endif



    /* ==>AT2D01490 */
    ulLaiChangeFlag =  NAS_MML_IsCsLaiChanged();
    if ((VOS_TRUE == ulLaiChangeFlag)
        || (g_MmGlobalInfo.MsCsInfo.ucCellChgFlg == MM_TRUE))
    {
        Mm_TimerStop(MM_TIMER_T3211);
    }
    /* <==AT2D01490 */

    if (VOS_FALSE == NAS_MML_GetCsAttachAllowFlg())
    {
        NAS_MM_ProcMmcMmSysInfoInd_CsAttachNotAllow();

        return;
    }

    if (VOS_TRUE == NAS_MM_IsCsForbidden())
    {
        NAS_MM_ProcCsForbidenFlg_RcvSysInfoInd(g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg);

        return;
    }

    if (VOS_TRUE == NAS_MML_GetCsRestrictRegisterFlg())
    {
        NAS_MM_ProcMmcMmSysInfoInd_CsRegisterRestrict();

        return;
    }

    if ((VOS_TRUE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNewNtMod))
#if  (FEATURE_ON == FEATURE_LTE)
     && (VOS_FALSE == ulCsfbExistFlag)
#endif
       )
    {                                                                           /* ���ΪA+I,�Ҳ�������B��A+II����ĳ���    */
        g_MmGlobalInfo.ucNtMod = g_MmGlobalInfo.ucNewNtMod;

        /* RACΪ0�ĳ��� */
        if ((MM_UNSUPPORT_GPRS             == g_MmGlobalInfo.usRac)
         || (MMCMM_FORBIDDEN_PLMN_FOR_GPRS == g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg))
        {
            NAS_MM_SetLikeBFlg();

            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S6_E5:INFO: MmLikeB is MM_TRUE");

            if (VOS_FALSE == ulLaiChangeFlag)
            {                                                               /* ���LAI����,����״̬ΪU1                 */
                if (MM_TRUE == g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg)
                {
                    g_MmGlobalInfo.LuInfo.ucLuType =
                                    MM_IE_LUT_PERIODIC_UPDATING;            /* ����LU����                               */
                    Mm_ComLuOnly();                                         /* ����LU REQ                               */
                }
                else if (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED !=
                    NAS_MML_GetCsUpdateStatus())
                {
                    g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;   /* ����LU����                               */
                    Mm_ComLuOnly();                                         /* ����LU REQ                               */
                }
                else
                {
                    Mm_ComNasInfoSav(
                             MM_STATUS_ATTACHED,
                             NAS_MML_GetSimCsSecurityCksn()
                             );
                    g_MmGlobalInfo.ucMmServiceState =
                        MM_NORMAL_SERVICE;                          /* ���÷���״̬                             */
                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S6_E5:INFO: MmServiceState is MM_NORMAL_SERVICE");
                    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                                MM_MMC_LU_RESULT_SUCCESS,
                                                NAS_MML_REG_FAIL_CAUSE_NULL);        /* ��MMC����MMCMM_LU_RESULT_IND             */
                    NAS_MM_SndGmmLuResultInd(MMGMM_LU_SUCCESS,
                                             NAS_MML_REG_FAIL_CAUSE_NULL);        /* ��MMC����MMCMM_LU_RESULT_IND             */


                    Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S6_E5:NORMAL: STATUS is  MM_IDLE_NORMAL_SERVICE");
                    NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                }
            }
            else
            {
                Mm_TimerStop(MM_TIMER_T3213);
                g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;       /* ����LU����                               */
                Mm_ComLuOnly();                                             /* ����LU REQ                               */
            }
        }
        else if (VOS_TRUE == NAS_MML_GetPsRestrictRegisterFlg())
        {
            if (VOS_FALSE == ulLaiChangeFlag)
            {                                                                   /* ���LAI����,����״̬ΪU1                 */
                if (MM_TRUE == g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg)
                {
                    g_MmGlobalInfo.LuInfo.ucLuType =
                                    MM_IE_LUT_PERIODIC_UPDATING;                /* ����LU����                               */
                    Mm_ComLuOnly();                                             /* ����LU REQ                               */
                }
                else if (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED !=
                    NAS_MML_GetCsUpdateStatus())
                {
                    g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;       /* ����LU����                               */
                    Mm_ComLuOnly();                                             /* ����LU REQ                               */
                }
                else
                {
                    NAS_MM_RcvSysInfoPsRestrictRegLaiNoChangeU1();
                }
            }
            else
            {
                Mm_TimerStop(MM_TIMER_T3213);
                g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;           /* ����LU����                               */
                Mm_ComLuOnly();                                                 /* ����LU REQ                               */
            }
        }
        else
        {                                                                       /* RAC��������                              */
            ;
        }
    }
    else
    {
        ucUserSpecificSearchFlg = Mm_Get_UserSpecificSearchFlg_From_SysInfo(pMsg);
        Mm_ComRcvSysHandle(ucUserSpecificSearchFlg);                       /* ������ϵͳ��Ϣ�Ĺ�������                 */
    }


    Mm_DealWithBuffMsg();
}


VOS_VOID Mm_Cell_S9_E13(VOS_VOID *pMsg)
{
    GMMMM_NETWORK_DETACH_IND_STRU       *pstNetWkDetachInd;


    if (MM_FALSE == NAS_MM_RcvGmmNetworkDetechInd(pMsg))
    {
        return;
    }

    if (NAS_MML_MS_MODE_PS_CS == NAS_MML_GetMsMode())
    {
    }
    pstNetWkDetachInd = (GMMMM_NETWORK_DETACH_IND_STRU*)pMsg;

    if (GMMMM_NET_DETACH_REATTACH == pstNetWkDetachInd->enDetachType)
    {
        g_MmGlobalInfo.ucLikeB = MM_TRUE;
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S9_E13:INFO: MmLikeB is MM_TRUE");
    }
    else if (GMMMM_NET_DETACH_IMSI == pstNetWkDetachInd->enDetachType)
    {
        Mm_ComSaveProcAndCauseVal(MM_NET_DETACH_PROC,
                                  NAS_MML_REG_FAIL_CAUSE_NTDTH_IMSI);                     /* ��¼���̺�ԭ��ֵ                         */
    }
    else
    {
        switch (pstNetWkDetachInd->ulDetachCause)
        {
        case NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR:
        case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
        case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW:
            Mm_TimerStop(MM_TIMER_PROTECT_AGENT);
            g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;
            Mm_TimerStop(MM_TIMER_T3230);                                       /* ֹͣT3230                                */
            if (NAS_MML_MS_MODE_PS_CS == NAS_MML_GetMsMode())
            {
                /* �ͷų������������д��ں����ڽ�����MM���� */
                Mm_ComRelAllMmConnExcEmergencyCall(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_SIM_INVALID);
            }
            Mm_ComSaveProcAndCauseVal(MM_NET_DETACH_PROC,
                                      (VOS_UINT8)pstNetWkDetachInd->ulDetachCause);   /* ��¼���̺�ԭ��ֵ                         */
            g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;                       /* ���÷���״̬                             */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S9_E13:INFO: MmServiceState is MM_NO_IMSI");
            Mm_ComToNoImsiHandle();                                             /* ����ɾ��IMSI�Ĺ�������                   */
            if ((MM_FALSE ==
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                ucEstingCallTypeFlg)
                && (MMCC_EMERGENCY_CALL !=
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                RcvXXEstReq.ulCallType))
            {
                Mm_TimerStart(MM_TIMER_T3240);                                  /* ����T3240                                */
                g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;             /* ��¼ǰ״̬                               */
                Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E14:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
            }
            break;
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN:
            g_MmGlobalInfo.ucLikeB = MM_TRUE;                                   /* ������Bģʽ��ȫ����                      */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S9_E13:INFO: MmLikeB is MM_TRUE");
            break;
        case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
            Mm_ComSaveProcAndCauseVal(MM_NET_DETACH_PROC,
                                      (VOS_UINT8)pstNetWkDetachInd->ulDetachCause);   /* ��¼���̺�ԭ��ֵ                         */
            break;
        case NAS_MML_REG_FAIL_CAUSE_NULL:
            NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
            g_MmGlobalInfo.ucLikeB = MM_TRUE;
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S9_E13:INFO: MmLikeB is MM_TRUE");
            break;
        default:
            break;
        }
    }
}


VOS_VOID Mm_Cell_S9_E14(VOS_VOID* pMsg)
{
    VOS_UINT8                               ucActionType;
    GMMMM_GMM_ACTION_RESULT_IND_STRU       *pstGmmActionRstInd;


    if (MM_FALSE == Mm_RcvGmmGmmActionResultInd(pMsg))
    {
        return;
    }

    if (NAS_MML_MS_MODE_PS_CS == NAS_MML_GetMsMode())
    {
    }

    pstGmmActionRstInd = (GMMMM_GMM_ACTION_RESULT_IND_STRU*)pMsg;

    if (GMMMM_ACTION_FAILURE == pstGmmActionRstInd->enActionResult)
    {                                                                           /* ���Ϊʧ�ܵĳ���                         */
        switch (pstGmmActionRstInd->enGmmActionType)
        {
        case GMMMM_ACTION_RAU:                                                 /* ����ΪRAU�ĳ���                          */
            ucActionType = MM_GMM_RAU_PROC;
            break;
        case GMMMM_ACTION_ATTACH:                                              /* ����ΪATTACH�ĳ���                       */
            ucActionType = MM_GMM_ATTACH_PROC;
            break;
        case GMMMM_ACTION_SR:                                                  /* ����ΪSR�ĳ���                           */
            ucActionType = MM_GMM_SR_PROC;
            break;
        default:
            ucActionType = MM_NULL_PROC;
            break;
        }
        if (MM_NULL_PROC != ucActionType)
        {                                                                       /* ������Ͳ�Ϊ�յĳ���                     */
            switch (pstGmmActionRstInd->enCause)
            {
            case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
            case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
                Mm_TimerStop(MM_TIMER_T3230);                                   /* ֹͣT3230                                */
                Mm_TimerStop(MM_TIMER_PROTECT_AGENT);
                g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;
                Mm_TimerStop(MM_TIMER_T3210);                               /* ֹͣT3210                                */
                Mm_ComSaveProcAndCauseVal(ucActionType,
                                       (VOS_UINT8)pstGmmActionRstInd->enCause);   /* ��¼���̺�ԭ��ֵ                         */
                g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;               /* ���÷���״̬                             */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S9_E14:INFO: MmServiceState is MM_NO_IMSI");

                if (NAS_MML_MS_MODE_PS_CS == NAS_MML_GetMsMode())
                {
                    /* �ͷų������������д��ں����ڽ�����MM���� */
                    Mm_ComRelAllMmConnExcEmergencyCall(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_SIM_INVALID);
                }
                Mm_ComToNoImsiHandle();                                     /* ����ɾ��IMSI�Ĺ�������                   */
                if ((MM_FALSE ==
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                    ucEstingCallTypeFlg)
                    && (MMCC_EMERGENCY_CALL !=
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                    RcvXXEstReq.ulCallType))
                {
                    Mm_TimerStart(MM_TIMER_T3240);                          /* ����T3240                                */
                    Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E14:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
                }
                break;
            case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW:
                if ( MM_GMM_ATTACH_PROC == ucActionType )
                {
                    Mm_TimerStop(MM_TIMER_PROTECT_AGENT);
                    g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;
                    Mm_TimerStop(MM_TIMER_T3210);                               /* ֹͣT3210                                */
                    Mm_ComSaveProcAndCauseVal(ucActionType,
                                           (VOS_UINT8)pstGmmActionRstInd->enCause);   /* ��¼���̺�ԭ��ֵ                         */
                    g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;               /* ���÷���״̬                             */
                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S9_E14:INFO: MmServiceState is MM_NO_IMSI");

                    if (NAS_MML_MS_MODE_PS_CS == NAS_MML_GetMsMode())
                    {
                        /* �ͷų������������д��ں����ڽ�����MM���� */
                        Mm_ComRelAllMmConnExcEmergencyCall(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_SIM_INVALID);
                    }
                    Mm_ComToNoImsiHandle();                                     /* ����ɾ��IMSI�Ĺ�������                   */

                    if ((MM_FALSE ==
                        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                        ucEstingCallTypeFlg)
                        && (MMCC_EMERGENCY_CALL !=
                        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                        RcvXXEstReq.ulCallType))
                    {
                        Mm_TimerStart(MM_TIMER_T3240);                          /* ����T3240                                */
                        Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
                        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E14:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
                    }
                }
                break;
            case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW:
            case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN:
                g_MmGlobalInfo.ucLikeB = MM_TRUE;                               /* ������Bģʽ��ȫ����                      */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S9_E14:INFO: MmLikeB is MM_TRUE");
                break;
            case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
            case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
            case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
            case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
                Mm_ComSaveProcAndCauseVal(ucActionType,
                                           (VOS_UINT8)pstGmmActionRstInd->enCause);   /* ��¼���̺�ԭ��ֵ                         */
                break;
            case NAS_MML_REG_FAIL_CAUSE_NO_PDP_CONTEXT_ACT:
            case NAS_MML_REG_FAIL_CAUSE_MS_ID_NOT_DERIVED:
            case NAS_MML_REG_FAIL_CAUSE_IMPLICIT_DETACHED:
                break;
            default:

                /* A+I��,PSע��ʧ�ܴﵽ������,MM���ڽ��н�������,��ʱ��Ҫ֪ͨMMC��ǰCS��������ע��
                   �ȴ�RRC����פ������LAU������attach */
                if ((VOS_TRUE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNewNtMod))
                 && (pstGmmActionRstInd->ucAttCounter >= 5)
                 && (NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE_REG_MAX_TIMES != pstGmmActionRstInd->enCause))
                {
                    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                                MM_MMC_LU_RESULT_FAILURE,
                                                NAS_MML_REG_FAIL_CAUSE_DELAY_CS_IN_TRANS_LAU);

                    g_MmGlobalInfo.ucLikeB = MM_TRUE;
                }

                break;
            }
        }
    }
}

/*******************************************************************************
  Module:   Mm_Cell_S9_E44
  Function: ��WAIT FOR OUTGOING MM CONNECTION״̬��
            �յ�RRMM_DATA_IND(MM STATUS)�Ĵ���
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
        1.  ��־��     2003.12.09  �°�����
*******************************************************************************/

VOS_VOID Mm_Cell_S9_E44(VOS_VOID *pMsg)
{
    if (MM_LIMITED_SERVICE != g_MmGlobalInfo.ucMmServiceState)
    {
        Mm_TimerStop( MM_TIMER_T3212 );                                         /* ͣT3212                                  */
    }
}

VOS_VOID Mm_Cell_S11_E9(VOS_VOID *pMsg)
{

    if ( MM_FALSE == Mm_RcvGmmImsiDetechIni(pMsg) )
    {
        return;

    }

    Mm_TimerStop(MM_TIMER_T3240);                                               /* ͣT3240                                  */

    Mm_SndRrRelReq(RRC_CELL_UNBARRED);

    g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                         /* ��¼ǰ״̬                               */
    Mm_ComSetMmState(IMSI_DETACH_PENDING);
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S11_E9:NORMAL: STATUS is IMSI_DETACH_PENDING");
}


VOS_VOID Mm_Cell_S11_E11(VOS_VOID *pMsg)
{
    if (MM_FALSE == NAS_MM_RcvGmmGprsDetechIni(pMsg))
    {
        return;
    }

    Mm_TimerStop(MM_TIMER_T3240);                                               /* ͣT3240                                  */
    Mm_SndRrRelReq(RRC_CELL_UNBARRED);

    g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                         /* ��¼ǰ״̬                               */
    Mm_ComSetMmState(IMSI_DETACH_PENDING);
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S11_E11:NORMAL: STATUS is IMSI_DETACH_PENDING");
}



VOS_VOID Mm_Cell_S11_E13(VOS_VOID *pMsg)
{
    GMMMM_NETWORK_DETACH_IND_STRU       *pstNetWkDetachInd;


    if (MM_FALSE == NAS_MM_RcvGmmNetworkDetechInd(pMsg))
    {
        return;

    }

    if (NAS_MML_MS_MODE_PS_CS == NAS_MML_GetMsMode())
    {
    }

    pstNetWkDetachInd = (GMMMM_NETWORK_DETACH_IND_STRU*)pMsg;

    if ( GMMMM_NET_DETACH_REATTACH == pstNetWkDetachInd->enDetachType )
    {
        NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);

        g_MmGlobalInfo.ucLikeB = MM_TRUE;
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S11_E13:INFO: MmLikeB is MM_TRUE");
    }
    else if ( GMMMM_NET_DETACH_IMSI == pstNetWkDetachInd->enDetachType )
    {
        Mm_TimerStop(MM_TIMER_PROTECT_AGENT);
        g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;
        Mm_ComSaveProcAndCauseVal(MM_NET_DETACH_PROC,
                                                    NAS_MML_REG_FAIL_CAUSE_NTDTH_IMSI);   /* ��¼���̺�ԭ��ֵ                         */
    }
    else
    {
        switch ( pstNetWkDetachInd->ulDetachCause )
        {
        case NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR:
        case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
        case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW:
            Mm_TimerStop(MM_TIMER_PROTECT_AGENT);
            g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;
            Mm_ComSaveProcAndCauseVal(MM_NET_DETACH_PROC,
                                      (VOS_UINT8)pstNetWkDetachInd->ulDetachCause);   /* ��¼���̺�ԭ��ֵ                         */
            g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;                       /* ���÷���״̬                             */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S11_E13:INFO: MmServiceState is MM_NO_IMSI");
            Mm_ComToNoImsiHandle();                                             /* ����ɾ��IMSI�Ĺ�������                   */
            break;
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN:
            g_MmGlobalInfo.ucLikeB = MM_TRUE;                                   /* ������Bģʽ��ȫ����                      */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S11_E13:INFO: MmLikeB is MM_TRUE");
            break;
        case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
            Mm_ComSaveProcAndCauseVal(MM_NET_DETACH_PROC,
                                      (VOS_UINT8)pstNetWkDetachInd->ulDetachCause);   /* ��¼���̺�ԭ��ֵ                         */
            break;
        case NAS_MML_REG_FAIL_CAUSE_NULL:
            NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
            g_MmGlobalInfo.ucLikeB = MM_TRUE;
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S11_E13:INFO: MmLikeB is MM_TRUE");
            break;
        default:
            break;
        }
    }
}


VOS_VOID Mm_Cell_S11_E14(VOS_VOID* pMsg)
{
    VOS_UINT8                                   ucActionType = MM_NULL_PROC;
    GMMMM_GMM_ACTION_RESULT_IND_STRU        *pstGmmActionRstInd;


    if ( MM_FALSE == Mm_RcvGmmGmmActionResultInd(pMsg) )
    {
        return;

    }

    if (NAS_MML_MS_MODE_PS_CS == NAS_MML_GetMsMode())
    {
    }

    pstGmmActionRstInd = (GMMMM_GMM_ACTION_RESULT_IND_STRU*)pMsg;

    if (GMMMM_ACTION_FAILURE == pstGmmActionRstInd->enActionResult )
    {                                                                           /* ���Ϊʧ�ܵĳ���                         */
        switch ( pstGmmActionRstInd->enGmmActionType )
        {
        case GMMMM_ACTION_RAU:                                                 /* ����ΪRAU�ĳ���                          */
            ucActionType = MM_GMM_RAU_PROC;
            break;
        case GMMMM_ACTION_ATTACH:                                              /* ����ΪATTACH�ĳ���                       */
            ucActionType = MM_GMM_ATTACH_PROC;
            break;
        case GMMMM_ACTION_SR:                                                  /* ����ΪSR�ĳ���                           */
            ucActionType = MM_GMM_SR_PROC;
            break;
        default:
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S11_E14:WARNING: ulGmmActionType Abnormal");
            break;
        }
        if ( MM_NULL_PROC != ucActionType )
        {                                                                       /* �������Ϊ�յĳ���                       */
            switch ( pstGmmActionRstInd->enCause )
            {
            case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
            case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
                Mm_TimerStop(MM_TIMER_PROTECT_AGENT);
                g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;
                Mm_ComSaveProcAndCauseVal(ucActionType,
                                  (VOS_UINT8)pstGmmActionRstInd->enCause);        /* ��¼���̺�ԭ��ֵ                         */
                g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;               /* ���÷���״̬                             */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S11_E14:INFO: MmServiceState is MM_NO_IMSI");
                Mm_ComToNoImsiHandle();                                     /* ����ɾ��IMSI�Ĺ�������                   */
                Mm_SndRrRelReq(RRC_CELL_UNBARRED);
                break;
            case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW:
                if ( MM_GMM_ATTACH_PROC == ucActionType )
                {
                    Mm_TimerStop(MM_TIMER_PROTECT_AGENT);
                    g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;
                    Mm_ComSaveProcAndCauseVal(ucActionType,
                                      (VOS_UINT8)pstGmmActionRstInd->enCause);        /* ��¼���̺�ԭ��ֵ                         */
                    g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;               /* ���÷���״̬                             */
                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S11_E14:INFO: MmServiceState is MM_NO_IMSI");
                    Mm_ComToNoImsiHandle();                                     /* ����ɾ��IMSI�Ĺ�������                   */
                }
                break;
            case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW:
            case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN:
                g_MmGlobalInfo.ucLikeB = MM_TRUE;                               /* ������Bģʽ��ȫ����                      */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S11_E14:INFO: MmLikeB is MM_TRUE");
                break;
            case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
            case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
            case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
            case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
                    Mm_ComSaveProcAndCauseVal(ucActionType,
                                      (VOS_UINT8)pstGmmActionRstInd->enCause);        /* ��¼���̺�ԭ��ֵ                         */
                break;
            case NAS_MML_REG_FAIL_CAUSE_NO_PDP_CONTEXT_ACT:
            case NAS_MML_REG_FAIL_CAUSE_MS_ID_NOT_DERIVED:
            case NAS_MML_REG_FAIL_CAUSE_IMPLICIT_DETACHED:
                break;
            default:
                /* A+I��,PSע��ʧ�ܴﵽ������,MM���ڽ��н�������,��ʱ��Ҫ֪ͨMMC��ǰCS��������ע��
                   �ȴ�RRC����פ������LAU������attach */
                if ((VOS_TRUE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNewNtMod))
                 && (pstGmmActionRstInd->ucAttCounter >= 5)
                 && (NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE_REG_MAX_TIMES != pstGmmActionRstInd->enCause))
                {
                    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                                MM_MMC_LU_RESULT_FAILURE,
                                                NAS_MML_REG_FAIL_CAUSE_DELAY_CS_IN_TRANS_LAU);

                    g_MmGlobalInfo.ucLikeB = MM_TRUE;
                }
                break;
            }
        }
    }
}

/*******************************************************************************
  Module:   Mm_Cell_S11_E16
  Function: ��WAIT_FOR_NETWORK_COMMAND״̬��
            �յ�GMMMM_AUTHENTICATON_FAILURE_IND�Ĵ���
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��     2003.12.09  �°�����
*******************************************************************************/
VOS_VOID Mm_Cell_S11_E16(VOS_VOID *pMsg)
{
    if ( MM_FALSE == Mm_RcvGmmAuthFailInd(pMsg) )
    {
        return;

    }
    Mm_ComSaveProcAndCauseVal(MM_AUTH_FAIL_PROC, NAS_MML_REG_FAIL_CAUSE_NULL);            /* ��¼���̺�ԭ��ֵ                         */
    g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;                               /* ���÷���״̬                             */
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S11_E16:INFO: MmServiceState is MM_NO_IMSI");
    Mm_ComToNoImsiHandle();                                                     /* ����ɾ��IMSI�Ĺ�������                   */
}
VOS_VOID Mm_Cell_S12_E13(VOS_VOID *pMsg)
{
    GMMMM_NETWORK_DETACH_IND_STRU      *pstNetWkDetachInd;


    if ( MM_FALSE == NAS_MM_RcvGmmNetworkDetechInd(pMsg) )
    {
        return;
    }

    if (NAS_MML_MS_MODE_PS_CS == NAS_MML_GetMsMode())
    {
    }

    pstNetWkDetachInd = (GMMMM_NETWORK_DETACH_IND_STRU*)pMsg;

    g_MmGlobalInfo.ucProc = MM_NET_DETACH_PROC;                                 /* ��¼��ǰ������                           */
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S12_E13:INFO: MmServiceState is MM_NET_DETACH_PROC");
    if ( GMMMM_NET_DETACH_REATTACH == pstNetWkDetachInd->enDetachType )
    {
        NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
        g_MmGlobalInfo.ucLikeB = MM_TRUE;
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S12_E13:INFO: MmLikeB is MM_TRUE");
    }
    else if ( GMMMM_NET_DETACH_IMSI == pstNetWkDetachInd->enDetachType )
    {
        Mm_TimerStop(MM_TIMER_T3230);                                           /* ֹͣT3230                                */
        Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);

        Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);

        Mm_ComSaveProcAndCauseVal(MM_NET_DETACH_PROC,
                                                    NAS_MML_REG_FAIL_CAUSE_NTDTH_IMSI);   /* ��¼���̺�ԭ��ֵ                         */
        g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;              /* ���÷���״̬                             */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S12_E13:INFO: MmServiceState is MM_ATTEMPTING_TO_UPDATE");
        Mm_ComToU2Handle();                                                     /* ����MM��U2�Ĵ���                         */
        Mm_SndRrRelReq(RRC_CELL_UNBARRED);
        /* Mm_SndMmcCmSvcInd��Mm_ComRelAllMmConn���ϱ� */
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        Mm_TimerStop(MM_TIMER_T3218);                                           /* ͣT3218                                  */
        Mm_ComDelRandRes();                                                     /* ɾ��RAND��RES                            */
    }
    else
    {
        switch ( pstNetWkDetachInd->ulDetachCause )
        {
        case NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR:
        case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
        case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW:
            Mm_TimerStop(MM_TIMER_T3230);                                       /* ֹͣT3230                                */
            Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);

            Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_SIM_INVALID);

            Mm_ComNetDetachCauseHandle((VOS_UINT8)pstNetWkDetachInd->ulDetachCause);
            Mm_SndRrRelReq(RRC_CELL_UNBARRED);

            Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);                            /* ֪ͨMMC��CS���ҵ���Ѿ�ֹͣ              */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
            break;
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN:
            g_MmGlobalInfo.ucLikeB = MM_TRUE;                                   /* ������Bģʽ��ȫ����                      */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S12_E13:INFO: MmLikeB is MM_TRUE");
            break;
        case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
            Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);

            /* ���緢�� DETACH��MS����ATTACH:����ط��ظ�cs detach�����ʣ���Ӧ�ûظ�forb other */
            Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);

            Mm_ComNetDetachCauseHandle((VOS_UINT8)pstNetWkDetachInd->ulDetachCause);
            Mm_SndRrRelReq(RRC_CELL_UNBARRED);
            Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);                            /* ֪ͨMMC��CS���ҵ���Ѿ�ֹͣ              */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
            break;
        case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
            if ( MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState )
            {
                Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);

                /* ���緢�� DETACH��MS����ATTACH:����ط��ظ�cs detach�����ʣ���Ӧ�ûظ�forb other */
                Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);

                Mm_ComNetDetachCauseHandle(
                                    (VOS_UINT8)pstNetWkDetachInd->ulDetachCause );
                Mm_SndRrRelReq(RRC_CELL_UNBARRED);

                Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);                        /* ֪ͨMMC��CS���ҵ���Ѿ�ֹͣ              */
                NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);

            }
            break;
        case NAS_MML_REG_FAIL_CAUSE_NULL:
            NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
            g_MmGlobalInfo.ucLikeB = MM_TRUE;
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S12_E13:INFO: MmLikeB is MM_TRUE");
            break;
        default:
            break;
        }
    }
}
VOS_VOID Mm_Cell_S12_E14(VOS_VOID* pMsg)
{

    VOS_UINT8                                ucActionType = MM_NULL_PROC;
    GMMMM_GMM_ACTION_RESULT_IND_STRU        *pstGmmActionRstInd;
    VOS_UINT32                               ulCsServExist;

    if (MM_FALSE == Mm_RcvGmmGmmActionResultInd(pMsg))
    {
        return;

    }

    ulCsServExist  = Mm_ComJudgeCsServExist();
    if (MM_CS_SERV_EMERGENCY_CALL_EXIST == ulCsServExist)
    {
        return;
    }

    pstGmmActionRstInd = (GMMMM_GMM_ACTION_RESULT_IND_STRU*)pMsg;

    if (GMMMM_ACTION_FAILURE == pstGmmActionRstInd->enActionResult)
    {                                                                           /* ���Ϊʧ�ܵĳ���                         */
        switch (pstGmmActionRstInd->enGmmActionType)
        {
        case GMMMM_ACTION_RAU:                                                 /* ����ΪRAU�ĳ���                          */
            ucActionType = MM_GMM_RAU_PROC;
            break;
        case GMMMM_ACTION_ATTACH:                                              /* ����ΪATTACH�ĳ���                       */
            ucActionType = MM_GMM_ATTACH_PROC;
            break;
        case GMMMM_ACTION_SR:                                                  /* ����ΪSR�ĳ���                           */
            ucActionType = MM_GMM_SR_PROC;
            break;
        default:
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S12_E14:WARNING: ulGmmActionType Abnormal");
            break;
        }

        if (MM_NULL_PROC != ucActionType)
        {
            switch (pstGmmActionRstInd->enCause)
            {
            case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
            case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
                Mm_TimerStop(MM_TIMER_T3230);                                   /* ֹͣT3230                                */
                if ( ( MM_GMM_SR_PROC == ucActionType ) ||
                    ( ( MM_GMM_ATTACH_PROC == ucActionType ) &&
                    ( MM_STATUS_ATTACHED ==
                            g_MmSubLyrShare.MmShare.ucCsAttachState ) ) ||
                    ( ( MM_GMM_RAU_PROC == ucActionType ) &&
                    ( MM_STATUS_ATTACHED ==
                                g_MmSubLyrShare.MmShare.ucCsAttachState ) ) )
                {
                    Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);

                    Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_SIM_INVALID);

                    Mm_ComCauseHandleAllProc(
                                            ucActionType,
                                            pstGmmActionRstInd->enCause);
                    Mm_SndRrRelReq(RRC_CELL_UNBARRED);
                    /* Mm_SndMmcCmSvcInd��Mm_ComRelAllMmConn���ϱ� */
                    NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);

                }
                break;
            case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW:
                if ( MM_GMM_ATTACH_PROC == ucActionType )
                {
                    Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);

                    Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_SIM_INVALID);

                    Mm_ComCauseHandleAllProc(
                                            ucActionType,
                                            pstGmmActionRstInd->enCause);
                    Mm_SndRrRelReq(RRC_CELL_UNBARRED);
                    Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);
                    Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);                    /* ֪ͨMMC��CS���ҵ���Ѿ�ֹͣ              */
                    NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
                }
                break;
            case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW:
            case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN:
                g_MmGlobalInfo.ucLikeB = MM_TRUE;                               /* ������Bģʽ��ȫ����                      */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S12_E14:INFO: MmLikeB is MM_TRUE");
                break;
            case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
                if ( ( MM_GMM_SR_PROC == ucActionType ) ||
                    ( ( MM_GMM_ATTACH_PROC == ucActionType ) &&
                    ( MM_STATUS_ATTACHED ==
                                g_MmSubLyrShare.MmShare.ucCsAttachState ) ) ||
                    ( ( MM_GMM_RAU_PROC == ucActionType ) &&
                    ( MM_STATUS_ATTACHED ==
                                g_MmSubLyrShare.MmShare.ucCsAttachState ) ) )
                {
                    Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);

                    Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_FORB_OTHER);

                    Mm_ComCauseHandleAllProc(
                                            ucActionType,
                                            pstGmmActionRstInd->enCause);
                    Mm_SndRrRelReq(RRC_CELL_UNBARRED);
                    Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);                    /* ֪ͨMMC��CS���ҵ���Ѿ�ֹͣ              */
                    NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);

                }
                break;
            case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
            case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
            case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
                if (MM_STATUS_ATTACHED ==
                                    g_MmSubLyrShare.MmShare.ucCsAttachState)
                {
                    Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);

                        /* ԭ��ֵ12���ܲ������������Ų������ٳ����ز�������״̬��MM_COM_SRVST_LIMITED_SERVICE_REGION,*/
                        if (NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW == pstGmmActionRstInd->enCause)
                        {
                            Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_FORB_LA);
                        }
                        else
                        {
                            Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_FORB_OTHER);
                        }

                    Mm_ComCauseHandleAllProc(
                                            ucActionType,
                                            pstGmmActionRstInd->enCause);
                    Mm_SndRrRelReq(RRC_CELL_UNBARRED);
                    Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);                    /* ֪ͨMMC��CS���ҵ���Ѿ�ֹͣ              */
                    NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);

                }
                break;

            default:
                /* A+I��,PSע��ʧ�ܴﵽ������,MM���ڽ��н�������,��ʱ��Ҫ֪ͨMMC��ǰCS��������ע��
                   �ȴ�RRC����פ������LAU������attach */
                if ((VOS_TRUE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNewNtMod))
                 && (pstGmmActionRstInd->ucAttCounter >= 5)
                 && (NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE_REG_MAX_TIMES != pstGmmActionRstInd->enCause))
                {
                    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                                MM_MMC_LU_RESULT_FAILURE,
                                                NAS_MML_REG_FAIL_CAUSE_DELAY_CS_IN_TRANS_LAU);

                    g_MmGlobalInfo.ucLikeB = MM_TRUE;
                }
                break;
            }
        }
    }
}



VOS_VOID Mm_Cell_S12_E16(VOS_VOID *pMsg)
{
    if (MM_FALSE == Mm_RcvGmmAuthFailInd(pMsg))
    {
        return;
    }

    Mm_TimerStop(MM_TIMER_STOP_ALL);                                            /* ͣ������ʱ��                             */

    Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_SIM_INVALID);

    Mm_ComAuthenRcvAuthenRej();                                                 /* ���ü�Ȩʧ�ܵĹ�������                   */
    Mm_SndRrRelReq(RRC_CELL_UNBARRED);
    /* Mm_SndMmcCmSvcInd��Mm_ComRelAllMmConn���ϱ� */
    NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
    Mm_TimerStop(MM_TIMER_T3218);                                               /* ͣT3218                                  */
    Mm_ComDelRandRes();                                                         /* ɾ��RAND��RES                            */

}
/*******************************************************************************
  Module:   Mm_Cell_S14_E13
  Function: ��WAIT FOR REESTABLISH��WAIT FOR EST_CNF��״̬��,
                �յ�GMMMM_NETWORK_DETACH_IND�Ĵ���
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��     2004.03.11  ���ݶ��ڽӿڸ���,�°�����
*******************************************************************************/

VOS_VOID Mm_Cell_S14_E13(VOS_VOID *pMsg)
{
    if (MM_CS_SIG_CONN_PRESENT == g_MmGlobalInfo.ucCsSigConnFlg)
    {
        Mm_Cell_S9_E13(pMsg);
        Mm_TimerStop(MM_TIMER_T3230);                                           /* ֹͣT3230                                */
    }
    else
    {
        Mm_Cell_S12_E13(pMsg);
    }
}

/*******************************************************************************
  Module:   Mm_Cell_S14_E14
  Function: ��WAIT FOR REESTABLISH��WAIT FOR EST_CNF��״̬��,
                �յ�GMMMM_GMM_ACTION_RESULT_IND�Ĵ���
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��     2004.03.11  ���ݶ��ڽӿڸ���,�°�����
*******************************************************************************/

VOS_VOID Mm_Cell_S14_E14(VOS_VOID *pMsg)
{
    if ( MM_CS_SIG_CONN_PRESENT == g_MmGlobalInfo.ucCsSigConnFlg )
    {
        Mm_Cell_S9_E14(pMsg);
    }
    else
    {
        Mm_Cell_S12_E14(pMsg);
    }
}


/*******************************************************************************
  Module:   Mm_Cell_S14_E16
  Function: ��WAIT FOR REESTABLISH��WAIT FOR EST_CNF��״̬��,
                �յ�GMMMM_AUTHENTICATON_FAILURE_IND�Ĵ���
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��     2004.03.11  ���ݶ��ڽӿڸ���,�°�����
*******************************************************************************/
VOS_VOID Mm_Cell_S14_E16(VOS_VOID *pMsg)
{
    Mm_ComAuthenRcvAuthenRej();
}


VOS_VOID Mm_Cell_S17_E5(VOS_VOID *pMsg)
{
    VOS_UINT8                           ucUserSpecificSearchFlg = 0;

#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulCsfbExistFlag;

    /* ȡ��CSFB�Ƿ���ڵı�־ */
    ulCsfbExistFlag     = NAS_MML_IsCsfbServiceStatusExist();
#endif

    if (VOS_FALSE == NAS_MML_GetCsAttachAllowFlg())
    {
        NAS_MM_ProcMmcMmSysInfoInd_CsAttachNotAllow();

        return;
    }

    if (VOS_TRUE == NAS_MM_IsCsForbidden())
    {
        NAS_MM_ProcCsForbidenFlg_RcvSysInfoInd(g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg);

        return;
    }

    if (VOS_TRUE == NAS_MML_GetCsRestrictRegisterFlg())
    {
        NAS_MM_ProcMmcMmSysInfoInd_CsRegisterRestrict();

        return;
    }

    /* CS ONLY��PS ONLY��nmo1��GMM��������ע�� */
    if ((VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
     && (MM_NET_MODE_I == g_MmGlobalInfo.ucNewNtMod)
     /* pending״̬����Ҫ�ж�like B��� */
#if  (FEATURE_ON == FEATURE_LTE)
     && (VOS_FALSE == ulCsfbExistFlag)
#endif
    )
    {                                                                           /* ���ΪA+I,�Ҳ�������B��A+II����ĳ���    */
        g_MmGlobalInfo.ucNtMod = g_MmGlobalInfo.ucNewNtMod;

        /* RACΪ0�ĳ��� */
        if ((MM_UNSUPPORT_GPRS == g_MmGlobalInfo.usRac)
         || (MMCMM_FORBIDDEN_PLMN_FOR_GPRS == g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg))
        {
            NAS_MM_SetLikeBFlg();

            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E5:INFO: MmLikeB is MM_TRUE");

            if (VOS_TRUE == NAS_MML_IsCampLaiInfoChanged())
            {                                                               /* LAI�仯�ĳ���                            */
                Mm_ComSetMmState(g_MmGlobalInfo.ucPreState);
                PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E5:NORMAL: ucState = ", g_MmGlobalInfo.ucState);
                g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;       /* ����LU����                               */
                Mm_ComLuOnly();                                             /* LU REQ                                   */
            }
        }
    }
    else
    {                                                                           /* ��A+Iģʽ                                */
        if ( g_MmGlobalInfo.ucNtMod != g_MmGlobalInfo.ucNewNtMod )
        {
            Mm_ComSetMmState(g_MmGlobalInfo.ucPreState);
            PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E5:NORMAL: ucState = ", g_MmGlobalInfo.ucState);
            Mm_ComNetModeChange();
        }
        else
        {   /* A+II����Bģʽ                            */
            ucUserSpecificSearchFlg = Mm_Get_UserSpecificSearchFlg_From_SysInfo(pMsg);
            Mm_ComRcvSysHandle(ucUserSpecificSearchFlg);                                               /* ������ϵͳ��Ϣ�Ĺ�������                 */
        }
    }

    Mm_DealWithBuffMsg();
}

VOS_VOID Mm_Cell_S17_E7(VOS_VOID *pMsg)
{

    GMMMM_COMBINED_ATTACH_ACCEPTED_STRU     *pCombinedAttatchAccpt;
    NAS_MML_LAI_STRU                   *pstCsSuccLai = VOS_NULL_PTR;
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8   enCsUpdateStatus;
    NAS_MML_IGNORE_AUTH_REJ_INFO_STRU      *pstAuthRejInfo;

    pstCsSuccLai    = NAS_MML_GetCsLastSuccLai(  );


    if ( MM_FALSE == Mm_RcvGmmCombinedAttachAccept(pMsg) )
    {
        return;
    }

    g_MmGlobalInfo.LuInfo.ucPsRandomAccessFailCnt = 0;

    pCombinedAttatchAccpt = (GMMMM_COMBINED_ATTACH_ACCEPTED_STRU*)pMsg;
    if ( GMMMM_ATTACH_RESLUT_COMBINED ==
                        pCombinedAttatchAccpt->enAttachResult )
    {
        g_MmGlobalInfo.ucLikeNetmode2 = MM_FALSE;
        g_MmGlobalInfo.ucLikeB = MM_FALSE;                                      /* ����������Bģʽ��ȫ����                  */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E7:INFO: MmLikeB is MM_FALSE");
        Mm_TimerStop( MM_TIMER_T3212 );                                         /* ͣT3212                                  */
        Mm_TimerStop( MM_TIMER_T3211 );                                         /* ͣT3211                                  */
        Mm_ComSaveProcAndCauseVal(MM_COMB_ATTACH_PROC, NAS_MML_REG_FAIL_CAUSE_NULL);      /* ��¼���̺�ԭ��ֵ                         */
        g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;                    /* ���÷���״̬                             */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E7:INFO: MmServiceState is MM_NORMAL_SERVICE");


        /* ��¼ע��ɹ���RAC����������ģʽ�ı�,�Ƚ�RAI�Ƿ����ı� */
        g_MmGlobalInfo.MsCsInfo.ucOldRac = NAS_MML_GetCurrCampRac();

        /* ��������ģʽ�ı�,RAI���ı�ʱ,MMû�и�������ģʽ,��GMMģ����ܻ�
           �������Ϲ��̣�Ϊ��֤����������GMMһ�£��˴���Ҫ��������ģʽ */
        g_MmGlobalInfo.ucNtMod           = g_MmGlobalInfo.ucNewNtMod;

        pstCsSuccLai->stPlmnId.ulMcc = NAS_MML_GetCurrCampPlmnId()->ulMcc;
        pstCsSuccLai->stPlmnId.ulMnc = NAS_MML_GetCurrCampPlmnId()->ulMnc;
        pstCsSuccLai->aucLac[0] = NAS_MML_GetCurrCampLai()->aucLac[0];
        pstCsSuccLai->aucLac[1] = NAS_MML_GetCurrCampLai()->aucLac[1];

        pstCsSuccLai->ucRac = g_MmGlobalInfo.MsCsInfo.ucOldRac;

        NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_UPDATED);

        g_MmSubLyrShare.MmShare.ucSpecProFlg =  MM_NOT_UPDATED_SPECIFIC_PROCEDURE;

        if ( GMMMM_MS_ID_TYPE_IMSI ==
                                pCombinedAttatchAccpt->stMsIdentity.enMsIdType )
        {
            g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                                                    ~MM_MS_ID_TMSI_PRESENT;     /* ����TMSI��Ч                             */
            NAS_MML_InitUeIdTmsiInvalid();
        }
        else if ( GMMMM_MS_ID_TYPE_TMSI ==
                            pCombinedAttatchAccpt->stMsIdentity.enMsIdType )
        {
            g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg |=
                                                    MM_MS_ID_TMSI_PRESENT;      /* ����TMSI��Ч                             */
            PS_MEM_CPY(NAS_MML_GetUeIdTmsi(),
                       pCombinedAttatchAccpt->stMsIdentity.aucTmsi,
                       NAS_MML_MAX_TMSI_LEN);
            g_MmGlobalInfo.MsCsInfo.stPlmnId.ulMcc = NAS_MML_GetCsLastSuccMcc();
            g_MmGlobalInfo.MsCsInfo.stPlmnId.ulMnc = NAS_MML_GetCsLastSuccMnc();
        }
        else
        {

        }
        Mm_ComNasInfoSav(
                        MM_STATUS_ATTACHED,
                        NAS_MML_GetSimCsSecurityCksn()
                        );

        if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
        {/* 3G USIM */
            Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);
        }
        else
        {/* 2G SIM */
            Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);
        }



        if (MM_TRUE == g_MmGlobalInfo.ucPowerOnFlg)
        {
            g_MmGlobalInfo.ucPowerOnFlg = MM_FALSE;
        }

        g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = MM_CONST_NUM_0;                   /* LAU ���������� */

        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* ��¼ǰ״̬                               */
        Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);

        pstAuthRejInfo = NAS_MML_GetAuthRejInfo();
        pstAuthRejInfo->ucHplmnCsAuthRejCounter = 0;


        /* ��ʾMM���ڽ�������ע�� */
        g_MmGlobalInfo.ucIsComBined = VOS_TRUE;

        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                    MM_MMC_LU_RESULT_SUCCESS,
                                    NAS_MML_REG_FAIL_CAUSE_NULL);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E7:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");
    }
    else
    {
        switch(pCombinedAttatchAccpt->enCause)
        {
        case NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR:
            g_MmGlobalInfo.ucLikeNetmode2 = MM_FALSE;
            Mm_TimerStop( MM_TIMER_T3212 );                                         /* ͣT3212                                  */
            Mm_TimerStop( MM_TIMER_T3211 );                                         /* ͣT3211                                  */
            Mm_ComSaveProcAndCauseVal(
                                      MM_COMB_ATTACH_PROC,
                                      (VOS_UINT8)pCombinedAttatchAccpt->enCause);   /* ��¼���̺�ԭ��ֵ                         */
            g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;                       /* ���÷���״̬                             */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E7:INFO: MmServiceState is MM_NO_IMSI");
            Mm_ComToNoImsiHandle();                                             /* ���ý�NO IMSI�Ĺ�������                  */
            Mm_ComSetMmState(MM_IDLE_NO_IMSI);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E7:NORMAL: STATUS is MM_IDLE_NO_IMSI");
            break;
        case NAS_MML_REG_FAIL_CAUSE_MSC_UNREACHABLE:
        case NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE:
        case NAS_MML_REG_FAIL_CAUSE_PROCEDURE_CONGESTION:
            if ( pCombinedAttatchAccpt->ulAttachAttCounter < MM_RAU_ATTACH_COUNTER_MAX)
            {
                enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();
                if ( (VOS_FALSE == NAS_MML_IsCsLaiChanged() )
                  && (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus) )
                {

                    Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
                }
                else
                {
                    Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);
                }

                if( MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState)
                {
                }
            }
            else
            {
                /**************************************************************
                The MM sublayer shall act as in network operation mode II or III
                (depending whether a PCCCH is present) as long as the combined
                GMM procedures are not successful and no new RA is entered. The
                new MM state is MM IDLE. 3gpp 24.008 4.7.3.2.3.2
                ***************************************************************/
                g_MmGlobalInfo.ucLikeNetmode2 = MM_TRUE;
                g_MmGlobalInfo.ucLikeB        = MM_TRUE;

                /*if CS is already attached,don't LAU any more*/
                if(MM_STATUS_ATTACHED != g_MmSubLyrShare.MmShare.ucCsAttachState)
                {
                    if(( MM_ATT_NEED == g_MmGlobalInfo.ucAttFlg ) && ( MM_TRUE == g_MmGlobalInfo.ucPowerOnFlg ))
                    {
                        g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_IMSI_ATTACH;             /* ����LU����                               */
                    }
                    else
                    {
                        g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;              /* ����LU����                               */
                    }
                    Mm_ComLuOnly();                                                                     /* ����LU REQ                               */
                }
                else
                {
                    Mm_ComSetMmState(g_MmGlobalInfo.ucPreState);

                    NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                }
            }
            break;
        default:
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S17_E7:WARNING: Cause Abnormal");
            /* WUEPS_ASSERT(0); */                                                    /* �쳣������                             */
            break;
        }

        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                    MM_MMC_LU_RESULT_FAILURE,
                                    pCombinedAttatchAccpt->enCause);
    }
    Mm_ComProcCauseClear();
    Mm_ComCheckDelayMmConn( MM_TRUE );
}

VOS_VOID Mm_Cell_S17_E8(VOS_VOID *pMsg)
{
    GMMMM_COMBINED_ATTACH_REJECTED_STRU        *pCombinedAttachRjct;
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8   enCsUpdateStatus;
    VOS_UINT8                                   ucState;                           /* MM״̬                                   */

    if ( MM_FALSE == NAS_MM_RcvGmmCombinedAttachRej(pMsg) )
    {
        return;
    }

    pCombinedAttachRjct = (GMMMM_COMBINED_ATTACH_REJECTED_STRU*)pMsg;

    /* ��ʾMM���ڽ�������ע�� */
    g_MmGlobalInfo.ucIsComBined = VOS_TRUE;

    NAS_MM_ComProcPsRandomAccessFailCnt(pCombinedAttachRjct->enCause,pCombinedAttachRjct->ulAttachAttCounter);

    switch(pCombinedAttachRjct->enCause)
    {
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
    case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW:
        Mm_ComSaveProcAndCauseVal(
                                  MM_COMB_ATTACH_PROC,
                                  (VOS_UINT8)pCombinedAttachRjct->enCause);     /* ��¼���̺�ԭ��ֵ                         */
        g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;                           /* ���÷���״̬                             */

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E8:INFO: MmServiceState is MM_NO_IMSI");

        Mm_ComToNoImsiHandle();                                                 /* ���ý�NO IMSI�Ĺ�������                  */

        Mm_ComSetMmState(MM_IDLE_NO_IMSI);

        NAS_MML_SetSimCsRegStatus(VOS_FALSE);

        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                    MM_MMC_LU_RESULT_FAILURE,
                                    pCombinedAttachRjct->enCause);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E8:NORMAL: STATUS is MM_IDLE_NO_IMSI");

        break;
    case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN:
        g_MmGlobalInfo.ucLikeB = MM_TRUE;                                       /* ����������Bģʽ��ȫ����                  */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E8:INFO: MmLikeB is MM_TRUE");
        if ( MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState )
        {
            if ( VOS_FALSE == NAS_MML_IsCsLaiChanged() )
            {
                Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E8:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");

                NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);


                Mm_SndRrNasInfoChgReq(MM_NAS_INFO_SYNC_AS_FLG);


                NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                            MM_MMC_LU_RESULT_SUCCESS,
                                            NAS_MML_REG_FAIL_CAUSE_NULL);

            }
            else
            {
                g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;           /* ����LU����                               */
                Mm_ComLuOnly();                                                 /* LU REQ                                   */
            }
        }
        else
        {
            enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();
            if ( (VOS_FALSE == NAS_MML_IsCsLaiChanged() ) &&
                (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus) )
            {                                                                   /* ���LAI����,����״̬ΪU1�ĳ���           */
                if ( MM_ATT_NEED == g_MmGlobalInfo.ucAttFlg )
                {
                    g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_IMSI_ATTACH;     /* ����LU����                               */
                    Mm_ComLuOnly();                                             /* LU REQ                                   */
                }
                else
                {
                    Mm_ComNasInfoSav(
                                     MM_STATUS_ATTACHED,
                                     NAS_MML_GetSimCsSecurityCksn()
                                     );
                    g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;        /* ���÷���״̬                             */
                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E8:INFO: MmServiceState is MM_NORMAL_SERVICE");


                    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                                MM_MMC_LU_RESULT_SUCCESS,
                                                NAS_MML_REG_FAIL_CAUSE_NULL);                    /* ��MMC����MMCMM_LU_RESULT_IND             */

                    Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E8:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");
                    NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                }
            }
            else
            {
                g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;           /* ����LU����                               */
                Mm_ComLuOnly();                                                 /* LU REQ                                   */
            }
        }
        break;
    case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
        Mm_ComSaveProcAndCauseVal(
                                  MM_COMB_ATTACH_PROC,
                                  (VOS_UINT8)pCombinedAttachRjct->enCause);         /* ��¼���̺�ԭ��ֵ                         */
        Mm_ComRejectCause11(MM_ATTACH);                                         /* ����ԭ��ֵΪ#11�Ĵ���                    */
        g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = MM_CONST_NUM_0;


        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                    MM_MMC_LU_RESULT_FAILURE,
                                    pCombinedAttachRjct->enCause);


        break;
    case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
        Mm_ComSaveProcAndCauseVal(
                                  MM_COMB_ATTACH_PROC,
                                  (VOS_UINT8)pCombinedAttachRjct->enCause);         /* ��¼���̺�ԭ��ֵ                         */
        Mm_ComRejectCause13(MM_ATTACH);                                         /* ����ԭ��ֵΪ#13�Ĵ���                    */
        g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = MM_CONST_NUM_0;


        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                    MM_MMC_LU_RESULT_FAILURE,
                                    pCombinedAttachRjct->enCause);


        break;
    case NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED:
        Mm_ComSetMmState(MM_IDLE_LOCATION_UPDATE_NEEDED);

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E8:NORMAL: STATUS is MM_IDLE_LOCATION_UPDATE_NEEDED");
        Mm_ComSaveProcAndCauseVal(
                                  MM_COMB_RAU_PROC,
                                  (VOS_UINT8)pCombinedAttachRjct->enCause);         /* ��¼���̺�ԭ��ֵ                         */


        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                    MM_MMC_LU_RESULT_FAILURE,
                                    pCombinedAttachRjct->enCause);


        break;
    default:

        if (pCombinedAttachRjct->ulAttachAttCounter == 0x0)
        {
            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                            MM_MMC_LU_RESULT_FAILURE,
                            pCombinedAttachRjct->enCause);
        }

        else if ( pCombinedAttachRjct->ulAttachAttCounter < 5)
        {
            enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();
            if ( (VOS_FALSE == NAS_MML_IsCsLaiChanged() )
              && (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus) )
            {                                                                   /* ���LAI����,����״̬ΪU1�ĳ���           */
                Mm_ComSaveProcAndCauseVal(
                                        MM_COMB_ATTACH_PROC,
                                        (VOS_UINT8)pCombinedAttachRjct->enCause);   /* ��¼���̺�ԭ��ֵ                         */
                g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;            /* ���÷���״̬                             */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E8:INFO: MmServiceState is MM_NORMAL_SERVICE");
                Mm_ComNasInfoSav(
                                 MM_STATUS_ATTACHED,
                                 NAS_MML_GetSimCsSecurityCksn()
                                 );
                g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;             /* ��¼ǰ״̬                               */
                Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);

                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E8:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");

                NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                            MM_MMC_LU_RESULT_SUCCESS,
                                            NAS_MML_REG_FAIL_CAUSE_NULL);

            }
            else
            {
                Mm_ComSaveProcAndCauseVal(
                                        MM_COMB_ATTACH_PROC,
                                        (VOS_UINT8)pCombinedAttachRjct->enCause);   /* ��¼���̺�ԭ��ֵ                         */
                g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;      /* ���÷���״̬                             */


                NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                            MM_MMC_LU_RESULT_FAILURE,
                                            pCombinedAttachRjct->enCause);


                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E8:INFO: MmServiceState is MM_ATTEMPTING_TO_UPDATE");
                g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;             /* ��¼ǰ״̬                               */
                Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);
                NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED);

                NAS_MM_UpdateEquPlmnInfo(pCombinedAttachRjct->enCause);

                Mm_ComNasInfoSav(
                                MM_STATUS_DETACHED,
                                MM_CKSN_INVALID
                                );                                              /* ����MM��Ϣ                               */
                Mm_ComDelLai();                                                 /* ɾ��LAI                                  */
                g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                    ~MM_MS_ID_TMSI_PRESENT;
                NAS_MML_InitUeIdTmsiInvalid();
                /* Modified by h00313353 for iteration 9, 2015-2-4, begin */
                if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
                {
                    Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);
                    Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFKC_ID);               /* ����SIM������״̬                        */
                }
                else
                {
                    Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);
                    Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKEYS_ID);            /* ����SIM������״̬                        */
                }
                /* Modified by h00313353 for iteration 9, 2015-2-4, end */

                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E8:NORMAL: STATUS is MM_IDLE_ATTEMPTING_TO_UPDATE");
            }
        }
        else if (NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE_REG_MAX_TIMES != pCombinedAttachRjct->enCause)
        {
            Mm_ComSaveProcAndCauseVal(
                                        MM_COMB_ATTACH_PROC,
                                        (VOS_UINT8)pCombinedAttachRjct->enCause);   /* ��¼���̺�ԭ��ֵ                         */
            g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;          /* ���÷���״̬                             */


            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E8:INFO: MmServiceState is MM_ATTEMPTING_TO_UPDATE");

            NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED);
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                 /* ��¼ǰ״̬                               */
            Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);

            Mm_ComNasInfoSav(
                            MM_STATUS_DETACHED,
                            MM_CKSN_INVALID
                            );                                                  /* ����MM��Ϣ                               */
            Mm_ComDelLai();                                                     /* ɾ��LAI                                  */
            g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                ~MM_MS_ID_TMSI_PRESENT;
            NAS_MML_InitUeIdTmsiInvalid();

            /* Modified by h00313353 for iteration 9, 2015-2-4, begin */
            if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
            {
                Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);
                Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFKC_ID);               /* ����SIM������״̬                        */
            }
            else
            {
                Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);
                Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKEYS_ID);            /* ����SIM������״̬                        */
            }
            /* Modified by h00313353 for iteration 9, 2015-2-4, end */


            /**************************************************************
            The MM sublayer shall act as in network operation mode II or III
            (depending whether a PCCCH is present) as long as the combined
            GMM procedures are not successful and no new RA is entered. The
            new MM state is MM IDLE. 3gpp 24.008 4.7.3.2.3.2
            ***************************************************************/
            g_MmGlobalInfo.ucLikeNetmode2 = MM_TRUE;
            g_MmGlobalInfo.ucLikeB        = MM_TRUE;

            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E8:NORMAL: STATUS is MM_IDLE_ATTEMPTING_TO_UPDATE");

            /*PS����ʧ�ܺ�CS���Ե�������һ��λ�ø���A32D10820==>*/
            Mm_ComProcCauseClear();
            g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;
            if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
            {
                Mm_ComLuOnly();
            }
            else
            {
                /* G�£�GASͬʱ����CELL UPDATE��LU�����⣬GCF 44.2.1.2.8 FAIL, �˴����⴦��
                   �ӳ�1���ٷ��� LU ���̡� */
                /* ��ʱ״̬���䣬��Ϊ: LOCATION UPDATING PENDING */
                Mm_TimerStart(MM_TIMER_DELAY_LU_GSM);
            }
            return;
        }
        else
        {
            ucState = g_MmGlobalInfo.ucState;
            Mm_ComSetMmState(g_MmGlobalInfo.ucPreState);
            g_MmGlobalInfo.ucPreState = ucState;                 /* ��¼ǰ״̬                               */
        }
        break;
    }

    g_MmGlobalInfo.ucProc     = MM_NULL_PROC;
    Mm_ComCheckDelayMmConn( MM_TRUE );
    g_MmGlobalInfo.usCauseVal = NAS_MML_REG_FAIL_CAUSE_NULL;
}




VOS_VOID Mm_Cell_S17_E11(VOS_VOID *pMsg)
{
    if ( MM_FALSE == NAS_MM_RcvGmmGprsDetechIni(pMsg) )
    {
        return;
    }

    g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                         /* ��¼ǰ״̬                               */
    Mm_ComSetMmState(IMSI_DETACH_PENDING);
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E11:NORMAL: STATUS is IMSI_DETACH_PENDING");
}

VOS_VOID Mm_Cell_S17_E13(VOS_VOID *pMsg)
{
    GMMMM_NETWORK_DETACH_IND_STRU       *pstNetWkDetachInd;

    if ( MM_FALSE == NAS_MM_RcvGmmNetworkDetechInd(pMsg) )
    {
        return;
    }

    pstNetWkDetachInd = (GMMMM_NETWORK_DETACH_IND_STRU*)pMsg;

    if ( GMMMM_NET_DETACH_REATTACH == pstNetWkDetachInd->enDetachType )
    {
        NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
    }
    else if ( GMMMM_NET_DETACH_NOATTACH == pstNetWkDetachInd->enDetachType )
    {
        switch ( pstNetWkDetachInd->ulDetachCause )
        {
        case NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR:
        case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
        case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW:
            Mm_ComNetDetachCauseHandle(
                            (VOS_UINT8)pstNetWkDetachInd->ulDetachCause );        /* ����Net Detach�Ĵ���                     */
            NAS_MM_UpdateEquPlmnInfo(NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR);

            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                        MM_MMC_LU_RESULT_FAILURE,
                                        NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR);
            break;
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN:
            g_MmGlobalInfo.ucLikeB = MM_TRUE;                                   /* ����������Bģʽ��ȫ����                  */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E13:INFO: MmLikeB is MM_TRUE");
            switch(g_MmGlobalInfo.ucMmServiceState)
            {
            case MM_NORMAL_SERVICE:
                Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E13:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");
                NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                break;
            case MM_LIMITED_SERVICE:
                Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E13:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
                break;
            case MM_ATTEMPTING_TO_UPDATE:
                Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E13:NORMAL: STATUS is MM_IDLE_ATTEMPTING_TO_UPDATE");
                NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                break;
            case MM_NO_IMSI:
                Mm_ComSetMmState(MM_IDLE_NO_IMSI);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E13:NORMAL: STATUS is MM_IDLE_NO_IMSI");
                break;

            case MM_NO_SERVICE:
                Mm_ComSetMmState(MM_IDLE_NO_CELL_AVAILABLE);

                if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
                {
                    /* gsm��tbf�ͷź󲻻�����ϵͳ��Ϣ����Ҫ����MM_TIMER_DELAY_LU_GSM��ʱ����lau */
                    Mm_TimerStart(MM_TIMER_DELAY_LU_GSM);
                }
                break;

            default:
                break;
            }
            break;
        case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
            Mm_ComNetDetachCauseHandle(
                            (VOS_UINT8)pstNetWkDetachInd->ulDetachCause );        /* ����Net Detach�Ĵ���                     */
            NAS_MM_UpdateEquPlmnInfo(pstNetWkDetachInd->ulDetachCause);

            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                        MM_MMC_LU_RESULT_FAILURE,
                                        pstNetWkDetachInd->ulDetachCause);
            break;
        case NAS_MML_REG_FAIL_CAUSE_NULL:
            switch(g_MmGlobalInfo.ucMmServiceState)
            {
            case MM_NORMAL_SERVICE:
                Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E13:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");
                NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                break;
            case MM_LIMITED_SERVICE:
                Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E13:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
                break;
            case MM_ATTEMPTING_TO_UPDATE:
                Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E13:NORMAL: STATUS is MM_IDLE_ATTEMPTING_TO_UPDATE");
                NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                break;
            case MM_NO_IMSI:
                Mm_ComSetMmState(MM_IDLE_NO_IMSI);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E13:NORMAL: STATUS is MM_IDLE_NO_IMSI");
                break;

            case MM_NO_SERVICE:
                Mm_ComSetMmState(MM_IDLE_NO_CELL_AVAILABLE);

                if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
                {
                    /* gsm��tbf�ͷź󲻻�����ϵͳ��Ϣ����Ҫ����MM_TIMER_DELAY_LU_GSM��ʱ����lau */
                    Mm_TimerStart(MM_TIMER_DELAY_LU_GSM);
                }
                break;

            default:
                break;
            }

            g_MmGlobalInfo.ucLikeB = MM_TRUE;
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E13:INFO: MmLikeB is MM_TRUE");
            break;
        default:
            break;
        }
    }
    else
    {

    }
}


VOS_VOID Mm_Cell_S17_E15(VOS_VOID *pMsg)
{
    GMMMM_LU_INITIATION_STRU    *pstMmcLuIni;
    VOS_UINT8                    ucPsRestrictionFlg;

    ucPsRestrictionFlg      = NAS_MML_GetPsRestrictRegisterFlg();

    if ( MM_FALSE == Mm_RcvGmmLuIni(pMsg) )
    {
        return;
    }

    pstMmcLuIni = ( GMMMM_LU_INITIATION_STRU* )pMsg;

    if ( GMMMM_NO_TIMER_EXPIRED == pstMmcLuIni->enTimerExpiredFlg )
    {
        g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;                   /* ����LU����ΪNORMAL                       */
    }
    else
    {
        if (((NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == NAS_MML_GetCsUpdateStatus() )
           && (VOS_FALSE == ucPsRestrictionFlg)
           && (GMMMM_T3312_EXPIRED == pstMmcLuIni->enTimerExpiredFlg))
          || (GMMMM_T3412OrT3423_EXPIRED == pstMmcLuIni->enTimerExpiredFlg))
        {                                                                       /* �������״̬ΪU1�ĳ���                   */
            g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_PERIODIC_UPDATING;       /* ����LU����Ϊ����                         */
        }
        else
        {
            g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;               /* ����LU����ΪNORMAL                       */
        }
    }
    Mm_ComLuOnly();                                                             /* ����LU����                               */
}

VOS_VOID Mm_Cell_S17_E18(VOS_VOID *pMsg)
{

    VOS_UINT32                              ulCsServExist;
    NAS_MML_LAI_STRU                       *pstCsSuccLai        = VOS_NULL_PTR;
    GMMMM_COMBINED_RAU_ACCEPTED_STRU       *pstCombinedRauAccpt = VOS_NULL_PTR;
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8   enCsUpdateStatus;

    pstCsSuccLai    = NAS_MML_GetCsLastSuccLai(  );

    if ( MM_FALSE == Mm_RcvGmmCombinedRauAccepted(pMsg) )
    {
        return;
    }

    g_MmGlobalInfo.LuInfo.ucPsRandomAccessFailCnt = 0;

    pstCombinedRauAccpt = (GMMMM_COMBINED_RAU_ACCEPTED_STRU*)pMsg;

    if ( GMMMM_RAU_RESULT_COMBINED == pstCombinedRauAccpt->enRauResult )
    {
        g_MmGlobalInfo.ucLikeB = MM_FALSE;                                      /* ����������Bģʽ��ȫ����                  */
        g_MmGlobalInfo.ucLikeNetmode2 = MM_FALSE;
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E18:INFO: MmLikeB is MM_FALSE");
        Mm_TimerStop( MM_TIMER_T3212 );                                         /* ͣT3212                                  */
        Mm_TimerStop( MM_TIMER_T3211 );                                         /* ͣT3211                                  */
        Mm_ComSaveProcAndCauseVal(
                                  MM_COMB_RAU_PROC,
                                  NAS_MML_REG_FAIL_CAUSE_NULL);                           /* ��¼���̺�ԭ��ֵ                         */
        g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;                    /* ���÷���״̬                             */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E18:INFO: MmServiceState is MM_NORMAL_SERVICE");

        /* ��¼ע��ɹ���RAC����������ģʽ�ı�,�Ƚ�RAI�Ƿ����ı� */
        g_MmGlobalInfo.MsCsInfo.ucOldRac = NAS_MML_GetCurrCampRac();

        /* ��������ģʽ�ı�,RAI���ı�ʱ,MMû�и�������ģʽ,��GMMģ����ܻ�
           �������Ϲ��̣�Ϊ��֤����������GMMһ�£��˴���Ҫ��������ģʽ */
        g_MmGlobalInfo.ucNtMod           = g_MmGlobalInfo.ucNewNtMod;

        pstCsSuccLai->stPlmnId.ulMcc = NAS_MML_GetCurrCampPlmnId()->ulMcc;
        pstCsSuccLai->stPlmnId.ulMnc = NAS_MML_GetCurrCampPlmnId()->ulMnc;
        pstCsSuccLai->aucLac[0] = NAS_MML_GetCurrCampLai()->aucLac[0];
        pstCsSuccLai->aucLac[1] = NAS_MML_GetCurrCampLai()->aucLac[1];

        pstCsSuccLai->ucRac = g_MmGlobalInfo.MsCsInfo.ucOldRac;

        NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_UPDATED);              /* ���ø���״̬                             */
        g_MmSubLyrShare.MmShare.ucSpecProFlg =  MM_NOT_UPDATED_SPECIFIC_PROCEDURE;

        /* ==>AT2D01703 */
        if (GMMMM_REAL_PROCEDURE == pstCombinedRauAccpt->enRealProFlg)
        {
            if ( GMMMM_MS_ID_TYPE_IMSI == pstCombinedRauAccpt->stMsIdentity.enMsIdType )
            {
                g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                                                        ~MM_MS_ID_TMSI_PRESENT; /* ����TMSI��Ч                             */
                NAS_MML_InitUeIdTmsiInvalid();
            }
            else if ( GMMMM_MS_ID_TYPE_TMSI ==
                                pstCombinedRauAccpt->stMsIdentity.enMsIdType )
            {
                g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg |=
                                                        MM_MS_ID_TMSI_PRESENT;
                PS_MEM_CPY(NAS_MML_GetUeIdTmsi(),
                           pstCombinedRauAccpt->stMsIdentity.aucTmsi,
                           NAS_MML_MAX_TMSI_LEN);

                g_MmGlobalInfo.MsCsInfo.stPlmnId.ulMcc = NAS_MML_GetCsLastSuccMcc();
                g_MmGlobalInfo.MsCsInfo.stPlmnId.ulMnc = NAS_MML_GetCsLastSuccMnc();
            }
            else
            {

            }
        }
        /* <==AT2D01703 */
        Mm_ComNasInfoSav(
                        MM_STATUS_ATTACHED,
                        NAS_MML_GetSimCsSecurityCksn()
                        );

        if (GMMMM_REAL_PROCEDURE == pstCombinedRauAccpt->enRealProFlg)
        {
            /* Modified by h00313353 for iteration 9, 2015-2-4, begin */
            if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
            {/* 3G USIM */
                Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);
            }
            else
            {/* 2G SIM */
                Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);
            }
            /* Modified by h00313353 for iteration 9, 2015-2-4, end */
        }
        else
        {
            Mm_SndRrNasInfoChgReq(MM_NAS_INFO_LOCA_INFO_FLG);
        }


        g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = MM_CONST_NUM_0;                   /*LAU ���������� */
        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* ��¼ǰ״̬                               */
        Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);

        /* ��ʾMM���ڽ�������ע�� */
        g_MmGlobalInfo.ucIsComBined = VOS_TRUE;

        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                    MM_MMC_LU_RESULT_SUCCESS,
                                    NAS_MML_REG_FAIL_CAUSE_NULL);

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E18:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");
    }
    else
    {
        switch(pstCombinedRauAccpt->enCause)
        {
        case NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR:
            Mm_ComSaveProcAndCauseVal(
                                      MM_COMB_RAU_PROC,
                                      (VOS_UINT8)pstCombinedRauAccpt->enCause);   /* ��¼���̺�ԭ��ֵ                         */
            g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;                       /* ���÷���״̬                             */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E18:INFO: MmServiceState is MM_NO_IMSI");

            Mm_ComToNoImsiHandle();                                             /* ���ý�NO IMSI�Ĺ�������                  */
            Mm_ComSetMmState(MM_IDLE_NO_IMSI);

            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E18:NORMAL: STATUS is MM_IDLE_NO_IMSI");
            break;
        case NAS_MML_REG_FAIL_CAUSE_MSC_UNREACHABLE:
        case NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE:
        case NAS_MML_REG_FAIL_CAUSE_PROCEDURE_CONGESTION:


            /* �˴�Э��δ��ȷ����������������������´���
               ע��ʧ�ܴ���С��5������LAI�����ҵ�ǰMM��״̬ΪUPDATED,�����Ϊ
               NORMAL SERVICE,����ǰ״̬ΪMM_IDLE_ATTEMPTING_TO_UPDATE��
               �ο�Э��24008:4.7.5.2.6 */
            if ( (pstCombinedRauAccpt->ulRauAttCounter < MM_RAU_ATTACH_COUNTER_MAX)
              || (GMMMM_REAL_PROCEDURE != pstCombinedRauAccpt->enRealProFlg))
            {
                enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();
                if ( (VOS_FALSE == NAS_MML_IsCsLaiChanged())
                  && (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus))
                {                                                               /* ���LAI����,����״̬ΪU1�ĳ��� */
                    g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;
                    g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;         /* ��¼ǰ״̬ */

                    Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
                }
                else
                {
                    g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;  /* ���÷���״̬ */

                    g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;         /* ��¼ǰ״̬ */

                    Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);

                }
            }

            else if ((NAS_MML_NET_RAT_TYPE_GSM != NAS_MML_GetCurrNetRatType())
                  || (MM_FALSE == g_MmGlobalInfo.ucLikeB))
            {
                /**************************************************************
                The MM sublayer shall act as in network operation mode II or III
                (depending whether a PCCCH is present) as long as the combined
                GMM procedures are not successful and no new RA is entered. The
                new MM state is MM IDLE. 3gpp 24.008 4.7.3.2.3.2
                ***************************************************************/
                g_MmGlobalInfo.ucLikeNetmode2 = MM_TRUE;
                g_MmGlobalInfo.ucLikeB        = MM_TRUE;

                /*if CS is already attached,don't LAU any more*/
                if(MM_STATUS_ATTACHED != g_MmSubLyrShare.MmShare.ucCsAttachState)
                {
                    enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();
                    if ((VOS_FALSE == NAS_MML_IsCsLaiChanged())
                     && (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus)
                     && (MM_ATT_NEED == g_MmGlobalInfo.ucAttFlg)
                     && (MM_TRUE == g_MmGlobalInfo.ucPowerOnFlg))
                    {
                        g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_IMSI_ATTACH; /* ����LU����                               */
                    }
                    else
                    {
                        g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;   /* ����LU����                               */
                    }
                }
                else
                {

                    g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;
                }
                if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
                {
                    Mm_ComLuOnly();
                }
                else
                {
                    /* G�£�GASͬʱ����CELL UPDATE��LU�����⣬GCF 44.2.3.2.3-2 FAIL, �˴����⴦��
                       �ӳ�1���ٷ��� LU ���̡� */
                    /* ��ʱ״̬���䣬��Ϊ: LOCATION UPDATING PENDING */
                    Mm_TimerStart(MM_TIMER_DELAY_LU_GSM);
                }
            }
            else
            {
                NAS_MM_ResumeMmStateToPreState_LocationUpdatingPending();

                g_MmGlobalInfo.ucPreState = LOCATION_UPDATING_PENDING;
            }
            break;


        /* GMM�յ�ϵͳ��Ϣʱ��֪ͨMM�ļ�����ԭ��ֵ�����ᴥ��MMC�������� */
        case NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE:
            NAS_MM_ResumeMmStateToPreState_LocationUpdatingPending();

            g_MmGlobalInfo.ucPreState = LOCATION_UPDATING_PENDING;
            break;

        default:
            NAS_MM_ResumeMmStateToPreState_LocationUpdatingPending();

            g_MmGlobalInfo.ucPreState = LOCATION_UPDATING_PENDING;
            break;
        }

        NAS_MM_SndMmcCsRegResultInd(pstCombinedRauAccpt->enRealProFlg,
                                    MM_MMC_LU_RESULT_FAILURE,
                                    pstCombinedRauAccpt->enCause);
    }
    Mm_ComProcCauseClear();

    if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
    {
        Mm_ComCheckDelayMmConn( MM_TRUE );
        Mm_ComCheckDelayDetach();
    }
    else
    {
        /* G�£����յ�GMM ����RAU�ɹ���Ϣ�󣬲������Ϸ��𻺴��CSҵ����Ϊ��ʱGMM��RAU���̻�δ��ȫ����,
           ���ܻ���RAU COMPLETE��Ϣ��Ҫ�ظ�������TLLI ָ�ɵȵȣ������ʱ���Ϸ���MM�Ľ�������GAS���ܹ���
           GMM������RAU���̲�����������
           Ŀǰ�Ľ������������1�붨ʱ�����ӳٷ���CSҵ�� */
        ulCsServExist = Mm_ComJudgeCsServExist();

        if ((MM_IDLE_NORMAL_SERVICE == g_MmGlobalInfo.ucState) && (MM_CS_SERV_NONE_EXIST != ulCsServExist))
        {
            Mm_TimerStart(MM_TIMER_DELAY_CS_SERVICE_GSM);
        }
        else
        {
            Mm_ComCheckDelayMmConn( MM_TRUE );
            Mm_ComCheckDelayDetach();
        }
    }
}



VOS_VOID Mm_Cell_S17_E19(VOS_VOID *pMsg)
{
    GMMMM_COMBINED_RAU_REJECTED_STRU           *pstCombinedRauRjct;
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8   enCsUpdateStatus;


    if ( MM_FALSE == Mm_RcvGmmCombinedRauRejected(pMsg) )
    {
        return;
    }

    pstCombinedRauRjct = (GMMMM_COMBINED_RAU_REJECTED_STRU*)pMsg;

    /* ��ʾMM���ڽ�������ע�� */
    g_MmGlobalInfo.ucIsComBined = VOS_TRUE;

    NAS_MM_ComProcPsRandomAccessFailCnt(pstCombinedRauRjct->enCause,pstCombinedRauRjct->ulRauAttCounter);

    switch(pstCombinedRauRjct->enCause)
    {
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
    case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW:
        Mm_ComSaveProcAndCauseVal(
                                  MM_COMB_RAU_PROC,
                                  (VOS_UINT8)pstCombinedRauRjct->enCause);            /* ��¼���̺�ԭ��ֵ                         */
        g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;                           /* ���÷���״̬                             */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E19:INFO: MmServiceState is MM_NO_IMSI");


        Mm_ComToNoImsiHandle();                                                 /* ���ý�NO IMSI�Ĺ�������                  */

        Mm_ComSetMmState(MM_IDLE_NO_IMSI);

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E19:NORMAL: STATUS is MM_IDLE_NO_IMSI");
        break;
    case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN:
        g_MmGlobalInfo.ucLikeB = MM_TRUE;                                       /* ����������Bģʽ��ȫ����                  */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E19:INFO: MmLikeB is MM_TRUE");
        if ( MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState )
        {
            if ( VOS_FALSE == NAS_MML_IsCsLaiChanged() )
            {
                Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E19:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
                NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
            }
            else
            {
                g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;           /* ����LU����                               */
                Mm_ComLuOnly();                                                 /* LU REQ                                   */
            }
        }
        else
        {
            enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();
            if ((VOS_FALSE == NAS_MML_IsCsLaiChanged())
                && (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus))
            {                                                                   /* ���LAI����,����״̬ΪU1�ĳ���           */
                if (MM_ATT_NEED == g_MmGlobalInfo.ucAttFlg)
                {
                    g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_IMSI_ATTACH;     /* ����LU����                               */
                    Mm_ComLuOnly();                                             /* LU REQ                                   */
                }
                else
                {
                    Mm_ComNasInfoSav(
                                     MM_STATUS_ATTACHED,
                                     NAS_MML_GetSimCsSecurityCksn()
                                     );
                    g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;        /* ���÷���״̬                             */
                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E19:INFO: MmServiceState is MM_NORMAL_SERVICE");


                    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                                MM_MMC_LU_RESULT_SUCCESS,
                                                NAS_MML_REG_FAIL_CAUSE_NULL);                    /* ��MMC����MMCMM_LU_RESULT_IND             */
                    NAS_MM_SndGmmLuResultInd(MMGMM_LU_SUCCESS,
                                             NAS_MML_REG_FAIL_CAUSE_NULL);                    /* ��MMC����MMCMM_LU_RESULT_IND             */
                    Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E19:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
                    NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                }
            }
            else
            {
                g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;           /* ����LU����                               */
                Mm_ComLuOnly();                                                 /* LU REQ                                   */
            }
        }
        break;
    case NAS_MML_REG_FAIL_CAUSE_MS_ID_NOT_DERIVED:
        Mm_ComSaveProcAndCauseVal(
                                  MM_COMB_RAU_PROC,
                                  (VOS_UINT8)pstCombinedRauRjct->enCause);        /* ��¼���̺�ԭ��ֵ                         */
        g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;                    /* ���÷���״̬                             */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E19:INFO: MmServiceState is MM_NORMAL_SERVICE");
        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* ��¼ǰ״̬                               */
        Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E19:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");
        Mm_ComNasInfoSav(
                        MM_STATUS_ATTACHED,
                        NAS_MML_GetSimCsSecurityCksn()
                        );                                                      /* ����MM��Ϣ                               */
        break;
    case NAS_MML_REG_FAIL_CAUSE_IMPLICIT_DETACHED:
        Mm_ComSaveProcAndCauseVal(
                                  MM_COMB_RAU_PROC,
                                  (VOS_UINT8)pstCombinedRauRjct->enCause);        /* ��¼���̺�ԭ��ֵ                         */
        g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;                   /* ���÷���״̬                             */


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E19:INFO: MmServiceState is MM_LIMITED_SERVICE");
        Mm_ComNasInfoSav(
                        MM_STATUS_DETACHED,
                        NAS_MML_GetSimCsSecurityCksn()
                        );                                                      /* ����MM��Ϣ                               */
        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* ��¼ǰ״̬                               */
        Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E19:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
        break;
    case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
        Mm_ComSaveProcAndCauseVal(
                                  MM_COMB_RAU_PROC,
                                  (VOS_UINT8)pstCombinedRauRjct->enCause);        /* ��¼���̺�ԭ��ֵ                         */
        Mm_ComRejectCause11(MM_RAU);                                            /* ����ԭ��ֵΪ#11�Ĵ���                    */
        g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = MM_CONST_NUM_0;
        break;
    case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
        Mm_ComSaveProcAndCauseVal(
                                  MM_COMB_RAU_PROC,
                                  (VOS_UINT8)pstCombinedRauRjct->enCause);        /* ��¼���̺�ԭ��ֵ                         */
        Mm_ComRejectCause13(MM_RAU);                                            /* ����ԭ��ֵΪ#13�Ĵ���                    */
        g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = MM_CONST_NUM_0;
        break;
    case NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED:
        Mm_ComSetMmState(MM_IDLE_LOCATION_UPDATE_NEEDED);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E19:NORMAL: STATUS is MM_IDLE_LOCATION_UPDATE_NEEDED");
        Mm_ComSaveProcAndCauseVal(
                                  MM_COMB_RAU_PROC,
                                  (VOS_UINT8)pstCombinedRauRjct->enCause);        /* ��¼���̺�ԭ��ֵ                         */
        break;
    default:
        if (pstCombinedRauRjct->ulRauAttCounter == 0x0)
        {
            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                            MM_MMC_LU_RESULT_FAILURE,
                            pstCombinedRauRjct->enCause);
        }
        if ( pstCombinedRauRjct->ulRauAttCounter < 5)
        {
            enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();
            if ( (VOS_FALSE == NAS_MML_IsCsLaiChanged())
              && (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus))
            {                                                                   /* ���LAI����,����״̬ΪU1�ĳ���           */
                Mm_ComSaveProcAndCauseVal(
                                          MM_COMB_RAU_PROC,
                                          (VOS_UINT8)pstCombinedRauRjct->enCause);/* ��¼���̺�ԭ��ֵ                         */
                g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;            /* ���÷���״̬                             */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E19:INFO: MmServiceState is MM_NORMAL_SERVICE");
                Mm_ComNasInfoSav(
                                MM_STATUS_ATTACHED,
                                NAS_MML_GetSimCsSecurityCksn()
                                );                                              /* ����MM��Ϣ                               */
                g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;             /* ��¼ǰ״̬                               */
                Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E19:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");
            }
            else
            {
                Mm_ComSaveProcAndCauseVal(
                                          MM_COMB_RAU_PROC,
                                          (VOS_UINT8)pstCombinedRauRjct->enCause);    /* ��¼���̺�ԭ��ֵ                         */
                g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;      /* ���÷���״̬                             */


                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E19:INFO: MmServiceState is MM_ATTEMPTING_TO_UPDATE");

                NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED);
                g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;             /* ��¼ǰ״̬                               */
                Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);

                Mm_ComNasInfoSav(
                                MM_STATUS_DETACHED,
                                MM_CKSN_INVALID
                                );                                              /* ����MM��Ϣ                               */

                Mm_ComDelLai();                                                 /* ɾ��LAI                                  */

                g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                    ~MM_MS_ID_TMSI_PRESENT;
                NAS_MML_InitUeIdTmsiInvalid();
                /* Modified by h00313353 for iteration 9, 2015-2-4, begin */
                if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
                {
                    Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);
                    Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFKC_ID);               /* ����SIM������״̬                        */
                }
                else
                {
                    Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);
                    Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKEYS_ID);            /* ����SIM������״̬                        */
                }
                /* Modified by h00313353 for iteration 9, 2015-2-4, end */


                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E19:NORMAL: STATUS is MM_IDLE_ATTEMPTING_TO_UPDATE");
            }
        }
        else if(NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE_REG_MAX_TIMES != pstCombinedRauRjct->enCause)
        {
            Mm_ComSaveProcAndCauseVal(
                                      MM_COMB_RAU_PROC,
                                      (VOS_UINT8)pstCombinedRauRjct->enCause);    /* ��¼���̺�ԭ��ֵ                         */
            g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;          /* ���÷���״̬                             */


            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E19:INFO: MmServiceState is MM_ATTEMPTING_TO_UPDATE");

            NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED);
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                 /* ��¼ǰ״̬                               */
            Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);

            Mm_ComNasInfoSav(
                            MM_STATUS_DETACHED,
                            MM_CKSN_INVALID
                            );                                                  /* ����MM��Ϣ                               */
            Mm_ComDelLai();                                                     /* ɾ��LAI                                  */
            g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                ~MM_MS_ID_TMSI_PRESENT;
            NAS_MML_InitUeIdTmsiInvalid();

            /* Modified by h00313353 for iteration 9, 2015-2-4, begin */
            if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
            {
                Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);
                Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFKC_ID);               /* ����SIM������״̬                        */
            }
            else
            {
                Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);
                Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKEYS_ID);            /* ����SIM������״̬                        */
            }
            /* Modified by h00313353 for iteration 9, 2015-2-4, end */


            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E19:NORMAL: STATUS is  MM_IDLE_ATTEMPTING_TO_UPDATE");

            /**************************************************************
            The MM sublayer shall act as in network operation mode II or III
            (depending whether a PCCCH is present) as long as the combined
            GMM procedures are not successful and no new RA is entered. The
            new MM state is MM IDLE. 3gpp 24.008 4.7.3.2.3.2
            ***************************************************************/
            g_MmGlobalInfo.ucLikeNetmode2 = MM_TRUE;
            g_MmGlobalInfo.ucLikeB        = MM_TRUE;

            /*PS����ʧ�ܺ�CS���Ե�������һ��λ�ø���A32D10820==>*/
            Mm_ComProcCauseClear();
            g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;
            Mm_ComLuOnly();
            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                        MM_MMC_LU_RESULT_FAILURE,
                                        pstCombinedRauRjct->enCause);
            return;
        }
        else
        {
            NAS_MM_ResumeMmStateToPreState_LocationUpdatingPending();

            g_MmGlobalInfo.ucPreState = LOCATION_UPDATING_PENDING;
        }
        break;
    }


    /* ֪ͨMM��״̬Ϊ401�� */
    if ( NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE_REG_MAX_TIMES == pstCombinedRauRjct->enCause )
    {
        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                    MM_MMC_LU_RESULT_FAILURE,
                                    NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE);
    }
    else
    {
        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                    MM_MMC_LU_RESULT_FAILURE,
                                    pstCombinedRauRjct->enCause);
    }

    NAS_MM_UpdateEquPlmnInfo(pstCombinedRauRjct->enCause);

    g_MmGlobalInfo.ucProc    = MM_NULL_PROC;
    Mm_ComCheckDelayMmConn( MM_TRUE );

    g_MmGlobalInfo.usCauseVal = NAS_MML_REG_FAIL_CAUSE_NULL;

    Mm_ComCheckDelayDetach();
}




VOS_VOID Mm_Cell_S18_E5(VOS_VOID *pMsg)
{


    if (g_MmGlobalInfo.ucNtMod != g_MmGlobalInfo.ucNewNtMod)
    {
        /* ��״̬������ģʽ�仯����Lu��ֱ�����ϲ�ظ�Detach�ɹ� */
        g_MmGlobalInfo.ucNtMod = g_MmGlobalInfo.ucNewNtMod;                     /* ��������ģʽ                             */
        g_MmGlobalInfo.ucMmServiceState = MM_DETACHED;                          /* ���÷���״̬                             */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S18_E5:INFO: MmServiceState is MM_DETACHED");

        Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                         NAS_MML_GetSimCsSecurityCksn());                 /* ����MM��Ϣ                               */

        /* �жϵȴ���־�Ƿ���ڣ������������MMCGMM_DETACH CNF */
        if (MM_WAIT_CS_DETACH== (g_MmGlobalInfo.stDetachInfo.enDetachType
                     & MM_WAIT_CS_DETACH))
        {
            NAS_MM_SndMmcDetachCnf(MMC_MM_NO_IMSI);
            /* ����ȴ���־ */
            g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_NULL_DETACH;
        }

        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                    MM_MMC_LU_RESULT_FAILURE,
                                    NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);

        Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S18_E5:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
    }


    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                MM_MMC_LU_RESULT_FAILURE,
                                NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE);

    NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                             NAS_MML_REG_FAIL_CAUSE_NULL);
    /* �ظ�MMCMM_ATTACH_CNF�Ĳ���,����ȴ�ATTACH�����־λ */
    if (MM_WAIT_CS_ATTACH == (g_MmGlobalInfo.stAttachInfo.enAttachType
                            & MM_WAIT_CS_ATTACH))
    {
        NAS_MM_SndMmcAttachCnf();
    }
    g_MmGlobalInfo.stAttachInfo.enAttachType = MM_WAIT_NULL_ATTACH;

    return;
}

VOS_VOID Mm_Cell_S18_E10(VOS_VOID *pMsg)
{
    if (MM_FALSE == Mm_RcvGmmImsiDetechComplete(pMsg))
    {
        return;
    }

    Mm_TimerStop(MM_TIMER_T3218);                                               /* ͣT3218                                  */
    Mm_ComDelRandRes();                                                         /* ɾ��RAND��RES                            */

    NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);

    Mm_ComNasInfoSav(
                    MM_STATUS_DETACHED,
                    NAS_MML_GetSimCsSecurityCksn());

    /* �жϵȴ���־�Ƿ���ڣ������������MMCGMM_DETACH CNF */
    if (MM_WAIT_CS_DETACH== (g_MmGlobalInfo.stDetachInfo.enDetachType
                 & MM_WAIT_CS_DETACH))
    {
        NAS_MM_SndMmcDetachCnf(MMC_MM_LIMITED_SERVICE);
        /* ����ȴ���־ */
        g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_NULL_DETACH;
    }

    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                MM_MMC_LU_RESULT_FAILURE,
                                NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);

    g_MmGlobalInfo.ucPowerOnFlg = MM_TRUE;

    if (MM_IDLE_LOCATION_UPDATE_NEEDED != g_MmGlobalInfo.ucState)
    {
        Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
    }


    NAS_EventReport(WUEPS_PID_MM, NAS_OM_EVENT_IMSI_DETACH_IND,
                    VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S18_E10:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
}


VOS_VOID Mm_Cell_S18_E12(VOS_VOID *pMsg)
{

    if (MM_FALSE == Mm_RcvGmmGprsDetechCmpl(pMsg))
    {
        return;
    }

    NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);

    Mm_TimerStop(MM_TIMER_T3218);                                               /* ͣT3218                                  */
    Mm_ComDelRandRes();                                                         /* ɾ��RAND��RES                            */
    Mm_ComNasInfoSav(
                    MM_STATUS_DETACHED,
                    NAS_MML_GetSimCsSecurityCksn());
    if (MM_DETACH_CS_POWEROFF == g_MmGlobalInfo.ucDetachType)
    {                                                                           /* �ػ��ĳ���                               */
        Mm_SndMmcPowerOffCnf();
        Mm_ComSetMmState(MM_STATE_NULL);

        g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S18_E12:NORMAL: STATUS is MM_STATE_NULL");
    }
    else
    {
        /* �жϵȴ���־�Ƿ���ڣ������������MMCGMM_DETACH CNF */
        if (MM_WAIT_CS_DETACH== (g_MmGlobalInfo.stDetachInfo.enDetachType
                     & MM_WAIT_CS_DETACH))
        {
            NAS_MM_SndMmcDetachCnf(MMC_MM_LIMITED_SERVICE);
            /* ����ȴ���־ */
            g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_NULL_DETACH;
        }

        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                    MM_MMC_LU_RESULT_FAILURE,
                                    NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);

        if (MM_IDLE_LOCATION_UPDATE_NEEDED != g_MmGlobalInfo.ucState)
        {
            Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
        }
        g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S18_E12:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
    }

    NAS_EventReport(WUEPS_PID_MM, NAS_OM_EVENT_IMSI_DETACH_IND,
                    VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    g_MmGlobalInfo.ucPowerOnFlg = MM_TRUE;

}
VOS_VOID Mm_Cell_S9_E48(
                    VOS_VOID     *pMsg                                          /* ��ǰ�������Ϣ                           */
                    )
{
    /* Modified by h00313353 for iteration 9, 2015-2-6, begin */
    USIMM_AUTHENTICATION_CNF_STRU     *pstUsimAuthCnf = VOS_NULL_PTR;
    /* Modified by h00313353 for iteration 9, 2015-2-6, end */

    pstUsimAuthCnf = (USIMM_AUTHENTICATION_CNF_STRU *)pMsg;

    /* ��ǰ���ڵȴ�����Ϣ,���� */
    /* Modified by h00313353 for iteration 9, 2015-2-9, begin */
    NAS_MM_LogAuthInfo((VOS_UINT8)(pstUsimAuthCnf->stCmdResult.ulSendPara), g_MmGlobalInfo.AuthenCtrlInfo.ucOpId);

    if ((VOS_UINT8)(pstUsimAuthCnf->stCmdResult.ulSendPara) != g_MmGlobalInfo.AuthenCtrlInfo.ucOpId)
    /* Modified by h00313353 for iteration 9, 2015-2-9, end */
    {
        return;
    }

    if ((USIMM_3G_AUTH != pstUsimAuthCnf->enAuthType )
     && (USIMM_2G_AUTH != pstUsimAuthCnf->enAuthType ))
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_Cell_S9_E48:ERROR: authentication type is not expected!");

        return;
    }

    /* SIM �� || USIM ������Ȩ�����в����� AUTN */
    if ((NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
        || (MM_IE_AUTN_PRESENT != g_MmMsgAuthReq.ucAutnFlg))
    {
        MM_RcvSimAuthCnf(pMsg);
        return;

    }

    if (MM_TRUE == Mm_RcvAgntUsimAuthenticationCnf(pMsg))
    {                                                                           /* ���ճɹ�                                 */
        Mm_ComAuthenRcvUsimCnf();                                               /* ���ü�Ȩ������������ */
    }
    else
    {                                                                           /* ����ʧ��                                 */
    }
    return;                                                                     /* ����                                     */
}

/*******************************************************************************
  MODULE   : Mm_Cell_S9_E55
  FUNCTION : ��WAIT FOR OUTGOING MM CONNECTION״̬��
             �յ�T3214_EXPIRED�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��      03-12-22  �°�����
     2.
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E55(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{

    Mm_ComT3214orT3216Expired();                                                /* ����T3214����T3216����Ĵ���             */
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S9_E55:INFO: RECEIVE MM T3214 EXPIRED");
    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S9_E56
  FUNCTION : ��WAIT FOR OUTGOING MM CONNECTION״̬��
             �յ�T3216_EXPIRED�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��      03-12-22  �°�����
     2.
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E56(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{

    Mm_ComT3214orT3216Expired();                                                /* ����T3214����T3216����Ĵ���             */
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S9_E56:INFO: RECEIVE MM T3216 EXPIRED");
    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S9_E57
  FUNCTION : ��WAIT FOR OUTGOING MM CONNECTION״̬��
             �յ�T3218_EXPIRED�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��      03-12-22  �°�����
     2.
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E57(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{

    Mm_ComT3218Expired();                                                       /* T3218����Ĵ���                          */
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S9_E57:INFO: RECEIVE MM T3218 EXPIRED");
    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S9_E59
  FUNCTION : ��WAIT FOR OUTGOING MM CONNECTION״̬��
             �յ�T3230_EXPIRED�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��      03-12-22  �°�����
     2.
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E59(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{

    Mm_T3230Expire();                                                           /* T3230����Ĵ���                          */
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S9_E59:INFO: RECEIVE MM T3230 EXPIRED");
    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S11_E60
  FUNCTION : ��WAIT FOR NETWORK COMMAND״̬��
             �յ�T3240_EXPIRED�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��      03-12-22  �°�����
     2.
*******************************************************************************/
VOS_VOID Mm_Cell_S11_E60(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{

    Mm_T3240Expire();                                                           /* T3230����Ĵ���                          */
    return;
}

VOS_VOID Mm_Cell_S0_E61(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{

}
VOS_VOID Mm_Cell_S1_E61(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
}
VOS_VOID Mm_Cell_S12_E61(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
}
VOS_VOID Mm_Cell_S13_E61(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
}

/*******************************************************************************
  MODULE   : NAS_MM_ProcConnCtrlInfo_WaitForNetworkCommand
  FUNCTION : ��WAIT FOR NETWORK COMMAND״̬���յ�setup��Ϣ������л���
  INPUT    : VOS_UINT8 *pucCMMsg
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
  1.����      15-6-15    �°�����

*******************************************************************************/
VOS_VOID NAS_MM_ProcConnCtrlInfo_WaitForNetworkCommand(VOS_UINT8 *pucCMMsg)
{
    if (MM_CC_MSG_SETUP == (pucCMMsg[MM_CC_MSG_TYPE_POS] & 0x3f))
    {
        if (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg)
        {
            Mm_SndCcRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId,
                                NAS_MMCM_REL_CAUSE_CM_SRV_REJ_CONGESTION);

            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg = MM_FALSE;
        }
    }
}


VOS_VOID Mm_Cell_S11_E50(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
    VOS_UINT8            ucTI = 0;                                              /* CC��Ϣ�е�TI                             */
    RRMM_DATA_IND_STRU  *pRrDataInd = (RRMM_DATA_IND_STRU *)pRcvMsg;            /* ��ϢRRMM_DATA_IND�Ľṹ��ָ��            */
    VOS_UINT8           *pucCMMsg = VOS_NULL_PTR;                               /* ָ������ת��                             */
    VOS_UINT8           *pucBakCMMsg = VOS_NULL_PTR;

    pucCMMsg = (VOS_UINT8 *)MM_MEM_ALLOC(
                           VOS_MEMPOOL_INDEX_MM,
                           pRrDataInd->RcvNasMsg.ulNasMsgSize,
                           WUEPS_MEM_NO_WAIT);                                  /* �����ڴ�                                 */
    if(VOS_NULL_PTR == pucCMMsg)
    {                                                                           /* �ڴ�����ʧ��                             */

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_Cell_S11_E50:ERROR: MALLOC ERROR!");
        return;                                                                 /* ����                                     */
    }
    pucBakCMMsg = pucCMMsg;
    Mm_TimerStop( MM_TIMER_T3240 );                                             /* ͣTIMER3240                              */

    PS_MEM_SET(pucCMMsg, 0,
        sizeof(VOS_UINT8) * pRrDataInd->RcvNasMsg.ulNasMsgSize);                /* ��ʼ���ڴ�                               */

    PS_MEM_CPY (pucCMMsg, &(pRrDataInd->RcvNasMsg.aucNasMsg[0]),
        pRrDataInd->RcvNasMsg.ulNasMsgSize);                                    /* �õ���Ϣ����                             */

    ucTI = (VOS_UINT8)(((pucCMMsg[0] & 0xf0) >> 4));                           /* �õ�CC��Ϣ�е�TI                         */

    if (((MM_CONST_NUM_7 == ucTI) || (MM_CONST_NUM_15 == ucTI)))
    {                                                                           /* TIO = 111                                */
        NAS_MM_ProcConnCtrlInfo_WaitForNetworkCommand(pucCMMsg);
        Mm_SndCcEstInd (ucTI, pRrDataInd->RcvNasMsg.ulNasMsgSize, pucCMMsg);    /* ��CC����MMCC_EST_IND                     */
        Mm_ComCheckDelayMmConn(MM_FALSE);
    }

    /*lint -e701*/
    if ((MM_CONST_NUM_7 > ucTI))
    {                                                                           /* ���ཨ����MM����                         */
        NAS_MM_ProcConnCtrlInfo_WaitForNetworkCommand(pucCMMsg);
        Mm_SndCcEstInd(ucTI, pRrDataInd->RcvNasMsg.ulNasMsgSize, pucCMMsg );    /* ��CC����MMCC_EST_IND                     */
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0] =
            (VOS_UINT8)(0x01 << ucTI);                                          /* �����Ѿ����ڵ�MM���ӵı�־λ             */
        Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);                                    /* ֪ͨMMC��CS���ҵ���Ѿ�����              */
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_EXIST);
        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* ��¼Ǩ��֮ǰ��״̬                       */
        Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S11_E50:NORMAL: STATUS is MM_CONNECTION_ACTIVE");
        Mm_ComCheckDelayMmConn(MM_FALSE);

    }
    else if (((MM_CONST_NUM_7 < ucTI) && (MM_CONST_NUM_15 > ucTI))
        && (MMC_MM_NORMAL_SERVICE == g_MmGlobalInfo.ucMmServiceState))
    {                                                                           /* CC������MM����                           */
        NAS_MM_ProcConnCtrlInfo_WaitForNetworkCommand(pucCMMsg);
        Mm_SndCcEstInd(ucTI, pRrDataInd->RcvNasMsg.ulNasMsgSize, pucCMMsg);     /* ��CC����MMCC_EST_IND                     */
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1] =
            (VOS_UINT8)(0x01 << (ucTI - 8));                                    /* �����Ѿ����ڵ�MM���ӵı�־λ             */
        Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);                                    /* ֪ͨMMC��CS���ҵ���Ѿ�����              */
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_EXIST);
        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* ��¼Ǩ��֮ǰ��״̬                       */
        Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S11_E50:NORMAL: STATUS is MM_CONNECTION_ACTIVE");
        Mm_ComCheckDelayMmConn(MM_FALSE);
    }
    else
    {

    }

    /*lint +e701*/
    MM_MEM_FREE(VOS_MEMPOOL_INDEX_NAS, pucBakCMMsg);                            /* �ͷ��������Ϣ                           */

    NAS_MM_UpdateCsServiceConnStatusFlg();

    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S14_E40
  FUNCTION : ��WAIT FOR REESTABLISH(WAIT FOR EST_CNF)״̬��
             �յ�RRMM_DATA_IND(CM SERVICE ACCEPT)�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��      04-01-06  �°�����
*******************************************************************************/
VOS_VOID Mm_Cell_S14_E40(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
    VOS_UINT8   i = 0;                                                          /* ѭ����������                             */
    /*lint -e701*/
    Mm_TimerStop(MM_TIMER_T3230);                                               /* ͣTIMER3230                              */
    for (i = 0; i < MM_CONST_NUM_7; i++)
    {                                                                           /* �ؽ���MM����                             */
        if (MM_CONST_NUM_0 !=
        (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0]
            & (0x01 << i)))
        {                                                                       /* ��TI��MM�������ڵȴ��ؽ�                 */
            Mm_SndCcReestCnf( i, MMCC_REEST_SUCCESS);                           /* ֪ͨCC,MM�������ڽ�                      */
        }
        if (MM_CONST_NUM_0 !=
            (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]
            & (0x01 << i)))
        {                                                                       /* ��TI��MM�������ڵȴ��ؽ�                 */
            Mm_SndCcReestCnf((i + 8), MMCC_REEST_SUCCESS);                      /* ֪ͨCC,MM�������ڽ�                      */
        }
    }
    /*lint +e701*/
    g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                         /* ��¼Ǩ��֮ǰ��״̬                       */
    Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S14_E40:NORMAL: STATUS is MM_CONNECTION_ACTIVE");
    Mm_ComCheckDelayMmConn( MM_FALSE );                                         /* ����Ƿ��б�������Ҫ������MM����         */

#if (FEATURE_ON == FEATURE_ECALL)
    /* ����eCall��ʱ��������ʶ */
    NAS_MM_RecordEcallTimerStartNeededFlag();
#endif

    return;
}
VOS_VOID Mm_Cell_S0_E3(
                    VOS_VOID     *pMsg                                          /* ��ǰ�������Ϣ                           */
                    )
{
    if (MM_TRUE == Mm_RcvMmcPlmnSrchIni(pMsg))
    {
        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* ����ucPreState                           */
        Mm_ComSetMmState(MM_IDLE_PLMN_SEARCH);

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S0_E3:NORMAL: STATUS is MM_IDLE_PLMN_SEARCH");
    }
    else
    {
    }
    return;                                                                     /* ����                                     */
}
VOS_VOID Mm_Cell_S3_E65(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
    MM_MSG_CM_SVC_REQ_STRU      CmSvcReq;                                       /* Ҫ���͵�CM SERVICE REQ��Ϣ               */
    VOS_UINT16                  usMsgSize = 0;                                  /* ��Ϣ����,���ֽ�Ϊ��λ                    */
    VOS_UINT8                  *pucCmSvcReq = 0;                                /* Ҫ���͵�CM SERVICE REQ��Ϣָ��           */

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList = VOS_NULL_PTR;
#endif

    if (MM_FALSE == Mm_RcvSsEstReq(pRcvMsg))
    {                                                                           /* ��Ϣ�����ʧ��                         */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        /* ��ǰС������ҵ�������򲻴��� */
        if (VOS_TRUE == NAS_MML_GetCsRestrictNormalServiceFlg())
        {
            Mm_SndSsRelInd(g_MmSsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);

            return;
        }

#if (FEATURE_ON == FEATURE_LTE)
        /* �����ǰΪL��ģ��ֱ�ӻظ�ssʧ�� */
        pstPrioRatList = NAS_MML_GetMsPrioRatList();
        if (VOS_TRUE == NAS_MML_IsLteOnlyMode(pstPrioRatList))
        {
            Mm_SndSsRelInd(g_MmSsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_NOT_SUPPORT_CS_CALL_S1_MODE_ONLY);
            return;
        }

        if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
        {
            NAS_MM_RcvSsEstReq_CSFB();

            return;
        }
#endif

        g_MmGlobalInfo.ucStaOfRcvXXEstReq = g_MmGlobalInfo.ucState;             /* ��¼�յ���������ʱ��״̬                 */

        if ((MM_CONST_NUM_8 > g_MmSsEstReq.ulTi)
            || (MM_CONST_NUM_14 < g_MmSsEstReq.ulTi))
        {
            /* TI���Ϸ� */

            Mm_SndSsRelInd(g_MmSsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);
        }
        else
        {                                                                       /* TI�Ϸ�                                   */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg
                = MM_TRUE;
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                                                RcvXXEstReq.ulTransactionId
                = g_MmSsEstReq.ulTi;
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulCallType
                = 0;
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulCallPri
                = 0;
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucRat = NAS_MML_GetCurrNetRatType();

            Mm_ComFillInCMSncReq(MM_IE_CM_SVC_TYPE_SS_ACT, MM_FALSE, &CmSvcReq);/* ���CM SERVICE REQUEST�ṹ��             */
            pucCmSvcReq = Mm_ComMsgCmSvcReqOfRrEstReq( &CmSvcReq, &usMsgSize ); /* ���CM SERVICE REQUEST ��Ϣ              */
            if (VOS_NULL_PTR == pucCmSvcReq)
            {                                                                   /* ��Ϣ����ʧ��                             */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S3_E65:WARNING: MAKE MSG CM SERVICE REQUEST ERROR!");
                return;                                                         /* ����                                     */
            }
            else
            {                                                                   /* ��Ϣ�����ɹ�                             */
                Mm_SndRrEstReq(RRC_EST_CAUSE_ORIGIN_HIGH_PRIORITY_SIGNAL,
                   MM_FALSE, usMsgSize, pucCmSvcReq);                           /* ������Ϣ                                 */
                MM_MEM_FREE(VOS_MEMPOOL_INDEX_NAS, pucCmSvcReq);                /* �ͷ�CM SERVICE REQUEST ��Ϣ�ṹ��        */
            }
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI =
                (VOS_UINT8)g_MmSsEstReq.ulTi;                                   /* ��¼���ڽ�����MM���ӵ�TI                 */
            g_MmGlobalInfo.ucMMConnEstingPD = MM_IE_PD_NON_CALL_RLT_SS_MSG;     /* ��¼���ڽ�����MM���ӵ�PD                 */
            Mm_TimerStart(MM_TIMER_PROTECT_SIGNALLING);
            Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);                                /* ֪ͨMMC��CS���ҵ���Ѿ�����              */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_ESTING);
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                 /* ��¼Ǩ��֮ǰ��״̬                       */
            Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_MM_CONNECTION);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S3_E65:NORMAL: STATUS is WAIT_FOR_RR_CONNECTION_MM_CONNECTION");
        }

        NAS_MM_UpdateCsServiceConnStatusFlg();

        NAS_MM_UpdateCsServiceBufferStatusFlg();
    }

    return;
}


VOS_VOID Mm_Cell_S4_E65(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{
    NAS_MML_MISCELLANEOUS_CFG_INFO_STRU   *pstMiscellaneousCfgInfo = VOS_NULL_PTR;

    pstMiscellaneousCfgInfo               = NAS_MML_GetMiscellaneousCfgInfo();

    if ( MM_FALSE == Mm_RcvSsEstReq(pRcvMsg) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        /* ��ǰС������ҵ�������򲻴��� */
        if (VOS_TRUE == NAS_MML_GetCsRestrictNormalServiceFlg())
        {
            Mm_SndSsRelInd(g_MmSsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);

            return;
        }

#if (FEATURE_ON == FEATURE_LTE)

        /* �����ǰפ��LTE,��ֱ�ӻظ�SSʧ�� */
        if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
        {        

            /* CS����Ч���򲻴�����ҵ�� */
            if (VOS_FALSE  == NAS_MML_GetSimCsRegStatus())
            {
                Mm_SndSsRelInd(g_MmSsEstReq.ulTi,
                               NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_SIM_INVALID);

                return;
            }
            
            /* �����ǰPS ONLYʱ֧��CSҵ��NVδ�����SSʧ�� */
            if ( (NAS_MML_MS_MODE_PS_ONLY == NAS_MML_GetMsMode())
              && (NAS_MMC_NV_ITEM_DEACTIVE == pstMiscellaneousCfgInfo->ucPsOnlyCsServiceSupportFlg) )
            { 
                 Mm_SndSsRelInd(g_MmSsEstReq.ulTi,
                               NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);
                
                 return;
            }
            
            /* ��LIMIT SRVICE״̬�ſ�SSҵ���CSFB���� */
            if (MM_IDLE_LIMITED_SERVICE == Mm_GetState())
            {
                NAS_MM_RcvSsEstReq_CSFB();

                return;
            }            

            
            /* LTE��UE��null��no imsi��wait for attach״̬�޷�����ssҵ�� */
            Mm_SndSsRelInd(g_MmSsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_NOT_SUPPORT_CS_CALL_S1_MODE_ONLY);

            return;
        }


        
#endif
        if (NAS_MMC_NV_ITEM_DEACTIVE == pstMiscellaneousCfgInfo->ucPsOnlyCsServiceSupportFlg)
        {
            Mm_SndSsRelInd(g_MmSsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);
        }
        else
        {
            /*״̬��Ϊlimited service���߷�����ΪPS ONLY*/
            if ((NAS_MML_MS_MODE_PS_ONLY != NAS_MML_GetMsMode())
             || (MM_IDLE_LIMITED_SERVICE != g_MmGlobalInfo.ucState))
            {
                /* UE��null��no imsi��wait for attach״̬�޷�����ssҵ�� */
                Mm_SndSsRelInd(g_MmSsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);
            }
            else
            {
                NAS_MML_SetCsAttachAllowFlg(VOS_TRUE);
                /*����÷������󲢽���CSע��*/
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg
                    = MM_TRUE;
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                                                    RcvXXEstReq.ulTransactionId
                    = g_MmSsEstReq.ulTi;
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulCallType
                    = 0;
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulCallPri
                    = 0;
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucRat = NAS_MML_GetCurrNetRatType();
                if ((MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod)
                 && (MM_FALSE == g_MmGlobalInfo.ucLikeB))
                {
                    NAS_MM_SndGmmRegisterInit();                                        /* ֪ͨGMM����ע��                          */
                }
                else
                {
                    g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;           /* ����LU����                               */
                    g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = 0;
                    Mm_ComLuOnly();                                                 /* LU REQ                                   */
                }
            }

        }
    }

    NAS_MM_UpdateCsServiceConnStatusFlg();

    NAS_MM_UpdateCsServiceBufferStatusFlg();

    return;
}
VOS_VOID Mm_Cell_S10_E65(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
    MM_MSG_CM_SVC_REQ_STRU          CmSvcReq;                                   /* CM service request�ṹ��                 */
    VOS_UINT8                       ucRst;

    if ( MM_FALSE == Mm_RcvSsEstReq(pRcvMsg) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        /* ��ǰС������ҵ�������򲻴��� */
        if (VOS_TRUE == NAS_MML_GetCsRestrictNormalServiceFlg())
        {
            Mm_SndSsRelInd(g_MmSsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);

            return;
        }
        /*lint -e701*/
        ucRst = Mm_ComJudgeLimitSvc();
        if ( ( MM_CONST_NUM_8 > g_MmSsEstReq.ulTi )
            || ( MM_CONST_NUM_14 < g_MmSsEstReq.ulTi )
            || ( MM_TRUE == ucRst ) )
        {                                                                       /* TI���Ϸ����������޷���״̬               */
            Mm_SndSsRelInd(g_MmSsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);
        }
        else if ( MM_CONST_NUM_0 !=
            ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1] &
            ( 0x01 << ( g_MmSsEstReq.ulTi - 8 ) ) ) )
        {                                                                       /* Ҫ������MM�����Ѿ�����                 */
            Mm_SndSsEstCnf( g_MmSsEstReq.ulTi, MMSS_EST_SUCCESS );              /* ֪ͨSS��MM���ӽ����ɹ�                   */
        }
        else
        {                                                                       /* TI�Ϸ�                                   */
            Mm_ComFillInCMSncReq(MM_IE_CM_SVC_TYPE_SS_ACT, MM_FALSE, &CmSvcReq);/* ���CM SERVICE REQUEST�ṹ��             */
            Mm_ComMsgCmSvcReqSnd( &CmSvcReq );                                  /* �����෢�ͽ���MM���ӵ�����               */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                                                    RcvXXEstReq.ulTransactionId
                = g_MmSsEstReq.ulTi;                                           /* ��¼�ؽ�MM���ӵ�TI */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI =
                (VOS_UINT8)g_MmSsEstReq.ulTi;                                       /* ��¼���ڽ�����MM���ӵ�TI                 */
            g_MmGlobalInfo.ucMMConnEstingPD = MM_IE_PD_NON_CALL_RLT_SS_MSG;     /* ��¼���ڽ�����MM���ӵ�PD                 */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucRat = NAS_MML_GetCurrNetRatType();

            Mm_TimerStart(MM_TIMER_T3230);                                      /* ����TIMER3230                            */
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                 /* ��¼Ǩ��֮ǰ��״̬                       */
            Mm_ComSetMmState(WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S10_E65:NORMAL: STATUS is WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION");
        }
        /*lint +e701*/
    }

    return;
}


VOS_VOID Mm_Cell_S11_E65(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList = VOS_NULL_PTR;
#endif

    if ( MM_FALSE == Mm_RcvSsEstReq(pRcvMsg) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S11_E65:WARNING: MMSS_EST_REQ check fail.");
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        /* ��ǰС������ҵ�������򲻴��� */
        if (VOS_TRUE == NAS_MML_GetCsRestrictNormalServiceFlg())
        {
            Mm_SndSsRelInd(g_MmSsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);

            return;
        }

#if (FEATURE_ON == FEATURE_LTE)
        /* �����ǰΪL��ģ��ֱ�ӻظ�ssʧ�� */
        pstPrioRatList = NAS_MML_GetMsPrioRatList();
        if ( VOS_TRUE == NAS_MML_IsLteOnlyMode(pstPrioRatList) )
        {
            Mm_SndSsRelInd(g_MmSsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_NOT_SUPPORT_CS_CALL_S1_MODE_ONLY);
            return;
        }

        /* �����ǰפ��LTE,��ֱ�ӻظ�SSʧ�� */
        /* L����LOCATION_UPDATING_PENDING״̬�յ�ss����mm�軺�� */
        if ((NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
         && (MM_IDLE_PLMN_SEARCH != g_MmGlobalInfo.ucState)
         && (LOCATION_UPDATING_PENDING != g_MmGlobalInfo.ucState))
        {
            Mm_SndSsRelInd(g_MmSsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_UE_INVALID_STATE);

            return;
        }
#endif

        if (MM_TRUE ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg)
        {                                                                       /* �Ѿ�����һ��������MM���ӽ�������         */
            Mm_SndSsRelInd(g_MmSsEstReq.ulTi,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST);
        }

        /* ����ҵ���ͻ�Ƿ����� */
        if (VOS_FALSE == Mm_IsMultiSrvCollisionAllow(MM_CONN_CTRL_SS))
        {
            Mm_SndSsRelInd(g_MmSsEstReq.ulTi,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_SERVICE_CONGESTION);

            return;
        }

        if (MM_IDLE_PLMN_SEARCH == g_MmGlobalInfo.ucState)
        {
            Mm_SndSsRelInd(g_MmSsEstReq.ulTi,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_SEARCHING_NETWORK);
            return;
        }

        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg
            = MM_TRUE;

        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId
            = g_MmSsEstReq.ulTi;

        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulCallType
            = 0;
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulCallPri
            = 0;
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucRat = NAS_MML_GetCurrNetRatType();


    }

    return;
}
VOS_VOID Mm_Cell_S3_E62(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
    MM_MSG_CM_SVC_REQ_STRU      CmSvcReq;                                       /* Ҫ���͵�CM SERVICE REQ��Ϣ               */
    VOS_UINT16                  usMsgSize = 0;                                  /* ��Ϣ����,���ֽ�Ϊ��λ                    */
    VOS_UINT8                  *pucCmSvcReq = 0;                                /* Ҫ���͵�CM SERVICE REQ��Ϣָ��           */


    if ( MM_FALSE == Mm_RcvSmsEstReq(pRcvMsg) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        /* ��ǰС������ҵ�������򲻴��� */
        if (VOS_TRUE == NAS_MML_GetCsRestrictNormalServiceFlg())
        {
            /* ֪ͨSMS����ʧ�� */
            Mm_SndSmsRelInd(g_MmSmsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);
            return;
        }

#if (FEATURE_ON == FEATURE_LTE)

        /* �����ǰפ��LTE,��ֱ�ӻظ�SMSʧ�� */
        if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
        {
            Mm_SndSmsRelInd(g_MmSmsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_UE_INVALID_STATE);/* ֪ͨSMS����ʧ��                          */

            return;
        }
#endif

        g_MmGlobalInfo.ucStaOfRcvXXEstReq = g_MmGlobalInfo.ucState;             /* ��¼�յ���������ʱ��״̬                 */
        if ( ( MM_CONST_NUM_8 > g_MmSmsEstReq.ulTi )
            || ( MM_CONST_NUM_14 < g_MmSmsEstReq.ulTi ) )
        {                                                                       /* TI���Ϸ�                                 */
            Mm_SndSmsRelInd( g_MmSmsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);/* ֪ͨSMS����ʧ��                          */
        }
        else
        {                                                                       /* TI�Ϸ�                                   */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg
                = MM_TRUE;

            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                                                    RcvXXEstReq.ulTransactionId
                = g_MmSmsEstReq.ulTi;
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulCallType
                = 0;
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulCallPri
                = 0;
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucRat = NAS_MML_GetCurrNetRatType();


            Mm_ComFillInCMSncReq(MM_IE_CM_SVC_TYPE_SMS, MM_FALSE, &CmSvcReq);   /* ���CM SERVICE REQUEST�ṹ��             */
            pucCmSvcReq = Mm_ComMsgCmSvcReqOfRrEstReq( &CmSvcReq, &usMsgSize ); /* ���CM SERVICE REQUEST ��Ϣ              */
            if ( VOS_NULL_PTR == pucCmSvcReq )
            {                                                                   /* ��Ϣ����ʧ��                             */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S3_E62:WARNING: MAKE MSG CM SERVICE REQUEST ERROR!");
                return;                                                         /* ����                                     */
            }
            else
            {                                                                   /* ��Ϣ�����ɹ�                             */
                Mm_SndRrEstReq( RRC_EST_CAUSE_ORIGIN_LOW_PRIORITY_SIGNAL,
                   MM_FALSE,
                   usMsgSize, pucCmSvcReq );                                    /* ������Ϣ                                 */
                MM_MEM_FREE(VOS_MEMPOOL_INDEX_NAS, pucCmSvcReq );               /* �ͷ�CM SERVICE REQUEST ��Ϣ�ṹ��        */
            }
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI =
                (VOS_UINT8)g_MmSmsEstReq.ulTi;                                  /* ��¼���ڽ�����MM���ӵ�TI                 */
            g_MmGlobalInfo.ucMMConnEstingPD = MM_IE_PD_SMS_MSG;                 /* ��¼���ڽ�����MM���ӵ�PD                 */
            Mm_TimerStart(MM_TIMER_PROTECT_SIGNALLING);
            Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);                                /* ֪ͨMMC��CS���ҵ���Ѿ�����              */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_ESTING);
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                 /* ��¼Ǩ��֮ǰ��״̬                       */
            Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_MM_CONNECTION);
            /*A32D11456==>*/
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S3_E62:NORMAL: STATUS is WAIT_FOR_RR_CONNECTION_MM_CONNECTION");
            /*<==A32D11456*/
        }
    }

    NAS_MM_UpdateCsServiceBufferStatusFlg();

    NAS_MM_UpdateCsServiceConnStatusFlg();

    return;
}


VOS_VOID NAS_MM_ProcSmsEstReq_WaitForOutgoingMmConnection(VOS_VOID)
{
    MM_MSG_CM_SVC_REQ_STRU                     CmSvcReq;                            /* Ҫ���͵�CM SERVICE REQ��Ϣ               */
    VOS_UINT16                                 usMsgSize = 0;                        /* ��Ϣ����,���ֽ�Ϊ��λ                    */
    VOS_UINT8                                 *pucCmSvcReq = 0;
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8  enCsUpdateStatus;

    enCsUpdateStatus                      = NAS_MML_GetCsUpdateStatus();

    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg
        = MM_TRUE;
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulTransactionId
        = g_MmSmsEstReq.ulTi;
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulCallType
        = 0;
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulCallPri
        = 0;
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucRat
        = NAS_MML_GetCurrNetRatType();

    if ((VOS_FALSE                               == NAS_MML_IsCsLaiChanged())
     || (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED  != enCsUpdateStatus))
    {
        NAS_MML_SetCsAttachAllowFlg(VOS_TRUE);

        if ((MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod)
            && (MM_FALSE == g_MmGlobalInfo.ucLikeB))
        {
            NAS_MM_SndGmmRegisterInit();                                /* ֪ͨGMM����ע��                          */
        }
        else
        {
            g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;   /* ����LU����                               */
            g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = 0;
            Mm_ComLuOnly();                                         /* LU REQ                                   */
        }
    }
    else
    {
        Mm_ComFillInCMSncReq(MM_IE_CM_SVC_TYPE_SMS, MM_FALSE, &CmSvcReq); /* ���CM SERVICE REQUEST�ṹ��             */

        pucCmSvcReq = Mm_ComMsgCmSvcReqOfRrEstReq(&CmSvcReq, &usMsgSize); /* ���CM SERVICE REQUEST ��Ϣ              */

        if (VOS_NULL_PTR == pucCmSvcReq)
        {                                                           /* ��Ϣ����ʧ��                             */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S4_E62:WARNING: MAKE MSG CM SERVICE REQUEST ERROR!");
            return;                                                 /* ����                                     */
        }
        else
        {                                                           /* ��Ϣ�����ɹ�                             */
            Mm_SndRrEstReq( RRC_EST_CAUSE_ORIGIN_LOW_PRIORITY_SIGNAL,
                            MM_FALSE,
                            usMsgSize, pucCmSvcReq );                                /* ������Ϣ                                 */
            MM_MEM_FREE(VOS_MEMPOOL_INDEX_NAS, pucCmSvcReq);        /* �ͷ�CM SERVICE REQUEST ��Ϣ�ṹ��        */
        }

        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI
            = (VOS_UINT8)g_MmSmsEstReq.ulTi;                        /* ��¼���ڽ�����MM���ӵ�TI                 */
        g_MmGlobalInfo.ucMMConnEstingPD = MM_IE_PD_SMS_MSG;         /* ��¼���ڽ�����MM���ӵ�PD                 */
        Mm_TimerStart(MM_TIMER_PROTECT_SIGNALLING);
        Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);                        /* ֪ͨMMC��CS���ҵ���Ѿ�����              */
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_ESTING);
        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;         /* ��¼Ǩ��֮ǰ��״̬                       */
        Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_MM_CONNECTION);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S4_E62:NORMAL: STATUS is WAIT_FOR_RR_CONNECTION_MM_CONNECTION");
    }
}

VOS_VOID Mm_Cell_S4_E62(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
    NAS_MML_MISCELLANEOUS_CFG_INFO_STRU       *pstMiscellaneousCfgInfo = VOS_NULL_PTR;

    VOS_UINT8                                  ucSimCsRegStatus;

    pstMiscellaneousCfgInfo               = NAS_MML_GetMiscellaneousCfgInfo();

    if ( MM_FALSE == Mm_RcvSmsEstReq(pRcvMsg) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        /* ��ǰС������ҵ�������򲻴��� */
        if (VOS_TRUE == NAS_MML_GetCsRestrictNormalServiceFlg())
        {
            /* ֪ͨSMS����ʧ�� */
            Mm_SndSmsRelInd(g_MmSmsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);

            return;
        }

        /* ��MM_IDLE_NO_IMSI״̬ʱ�յ�����ҵ������ֱ�ӻظ�CS_SIM_INVALID,
           ����״̬һ�����յ�ϵͳ��Ϣ��δע��ʱ������,��ʱ�޷��ṩCS������Ҫ�ز� */
        if (MM_IDLE_NO_IMSI == g_MmGlobalInfo.ucState)
        {
            Mm_SndSmsRelInd(g_MmSmsEstReq.ulTi,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_SIM_INVALID);    /* ֪ͨCC����ʧ��                           */

            return;
        }

#if (FEATURE_ON == FEATURE_LTE)

        /* �����ǰפ��LTE,��ֱ�ӻظ�SMSʧ�� */
        if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
        {
            Mm_SndSmsRelInd(g_MmSmsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_UE_INVALID_STATE);/* ֪ͨSMS����ʧ��                          */

            return;
        }
#endif
        /* ���no rf���Ȼ���ҵ������֪ͨmmc�������� */
        ucSimCsRegStatus = NAS_MML_GetSimCsRegStatus();

        if ((VOS_FALSE == NAS_MML_GetRfAvailFlg())
         && (MM_IDLE_NO_CELL_AVAILABLE == g_MmGlobalInfo.ucState)
         && (VOS_TRUE == ucSimCsRegStatus))
        {
            NAS_MM_UpdateConnCtrlInfo(MM_CONN_CTRL_SMS);
            Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);
            return;
        }

        if (NAS_MMC_NV_ITEM_DEACTIVE == pstMiscellaneousCfgInfo->ucPsOnlyCsServiceSupportFlg)
        {
            Mm_SndSmsRelInd(g_MmSmsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);
        }
        else
        {
            /*״̬��Ϊlimited service���߷�����ΪPS ONLY*/
            if ((NAS_MML_MS_MODE_PS_ONLY != NAS_MML_GetMsMode())
             || (MM_IDLE_LIMITED_SERVICE != g_MmGlobalInfo.ucState))
            {
                /* UE��null��no cell available��no imsi��wait for attach��WAIT FOR RR CONNECTION (IMSI DETACH)��IMSI DETACH INITIATED
                   ״̬�޷�����smsҵ�� */
                Mm_SndSmsRelInd(g_MmSmsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);
            }
            else
            {
                g_MmGlobalInfo.ucStaOfRcvXXEstReq = g_MmGlobalInfo.ucState;         /* ��¼�յ���������ʱ��״̬                 */

                if ((MM_CONST_NUM_8 > g_MmSmsEstReq.ulTi)
                    || (MM_CONST_NUM_14 < g_MmSmsEstReq.ulTi))
                {                                                                   /* TI���Ϸ�                                 */
                    Mm_SndSmsRelInd(g_MmSmsEstReq.ulTi,
                                    NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);                /* ֪ͨSMS����ʧ��                          */
                }
                else
                {
                    NAS_MM_ProcSmsEstReq_WaitForOutgoingMmConnection();
                }
            }

        }
    }


    NAS_MM_UpdateCsServiceConnStatusFlg();

    NAS_MM_UpdateCsServiceBufferStatusFlg();

    return;
}
VOS_VOID Mm_Cell_S10_E62(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
    MM_MSG_CM_SVC_REQ_STRU              CmSvcReq;                               /* CM service request�ṹ��                 */
    VOS_UINT8                           ucRst = MM_FALSE;
    if ( MM_FALSE == Mm_RcvSmsEstReq(pRcvMsg) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        /* ucRst = Mm_ComJudgeLimitSvc(); */
        if (MM_NO_IMSI == g_MmGlobalInfo.ucMmServiceState)
        {                                                                       /* �����޷���                               */
            ucRst = MM_TRUE;                                                    /* ���������޷���                           */
        }

        if ((NAS_MML_MS_MODE_PS_ONLY != NAS_MML_GetMsMode())
         && ((MM_LIMITED_SERVICE == g_MmGlobalInfo.ucMmServiceState)
          || ( MM_ATTEMPTING_TO_UPDATE == g_MmGlobalInfo.ucMmServiceState )))
        {
            ucRst = MM_TRUE;                                                 /* ���������޷���                           */
        }
        /*lint -e701*/
        if ( ( MM_CONST_NUM_8 > g_MmSmsEstReq.ulTi )
            || ( MM_CONST_NUM_14 < g_MmSmsEstReq.ulTi )
            || ( MM_TRUE == ucRst ) )
        {                                                                       /* TI���Ϸ����������޷���״̬               */
            Mm_SndSmsRelInd( g_MmSmsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);/* ֪ͨSMS����ʧ��                          */
        }
        else if (MM_CONST_NUM_0 !=
            (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1] &
            (0x01 << (g_MmSmsEstReq.ulTi - 8))))
        {                                                                       /* Ҫ������MM�����Ѿ�����                 */
            Mm_SndSmsEstCnf( g_MmSmsEstReq.ulTi );                              /* ֪ͨSMS��MM���ӽ����ɹ�                  */
        }
        else
        {                                                                       /* TI�Ϸ�                                   */
            Mm_ComFillInCMSncReq(MM_IE_CM_SVC_TYPE_SMS, MM_FALSE, &CmSvcReq);   /* ���CM SERVICE REQUEST�ṹ��             */
            Mm_ComMsgCmSvcReqSnd( &CmSvcReq );                                  /* �����෢�ͽ���MM���ӵ�����               */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                                                    RcvXXEstReq.ulTransactionId
                = g_MmSmsEstReq.ulTi;                                           /* ��¼�ؽ�MM���ӵ�TI */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI =
                (VOS_UINT8)g_MmSmsEstReq.ulTi;                                  /* ��¼���ڽ�����MM���ӵ�TI                 */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucRat = NAS_MML_GetCurrNetRatType();
            g_MmGlobalInfo.ucMMConnEstingPD = MM_IE_PD_SMS_MSG;                 /* ��¼���ڽ�����MM���ӵ�PD                 */
            Mm_TimerStart(MM_TIMER_T3230);                                      /* ����TIMER3230                            */
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                 /* ��¼Ǩ��֮ǰ��״̬                       */
            Mm_ComSetMmState(WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S10_E62:NORMAL: STATUS is WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION");
        }
        /*lint +e701*/
    }

    return;
}


VOS_VOID Mm_Cell_S11_E62(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{

    if ( MM_FALSE == Mm_RcvSmsEstReq(pRcvMsg) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S11_E62:WARNING: MMSMS_EST_REQ check fail.");
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        /* ��ǰС������ҵ�������򲻴��� */
        if (VOS_TRUE == NAS_MML_GetCsRestrictNormalServiceFlg())
        {
            /* ֪ͨSMS����ʧ�� */
            Mm_SndSmsRelInd(g_MmSmsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);

            return;
        }

#if   (FEATURE_ON == FEATURE_LTE)
        if ( NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
        {
            if (MM_TRUE ==
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg)
            {                                                                       /* �Ѿ�����һ��������MM���ӽ�������         */
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg = MM_FALSE;
                Mm_SndSmsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                    RcvXXEstReq.ulTransactionId, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST);
            }

            Mm_SndSmsRelInd(g_MmSmsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_UE_INVALID_STATE);

            return;
        }
#endif

        if (MM_TRUE ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg)
        {                                                                       /* �Ѿ�����һ��������MM���ӽ�������         */
            Mm_SndSmsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                RcvXXEstReq.ulTransactionId, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST);
        }

        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg
            = MM_TRUE;

        NAS_MML_SetCsServiceBufferStatusFlg(VOS_TRUE);

        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulTransactionId
            = g_MmSmsEstReq.ulTi;
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulCallType
            = 0;
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulCallPri
            = 0;
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucRat = NAS_MML_GetCurrNetRatType();

        if (MM_IDLE_PLMN_SEARCH == g_MmGlobalInfo.ucState)
        {
            Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);
        }

    }


    return;
}


VOS_VOID Mm_Cell_S27_E68(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
    MM_MSG_MM_STATUS_STRU          MsgMmStatus;                                 /* MM STATUS ��Ϣ�ṹ��                     */

    if ( MM_FALSE == Mm_RcvCcPromptRej( pRcvMsg ) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        Mm_TimerStop(MM_TIMER_PROTECT_CCBS);
        Mm_TimerStop(MM_TIMER_T3240);
        MsgMmStatus.MmIeRjctCause.ucRejCause = (VOS_UINT8)(g_MmCcPromptRej.ulRefuseCause);
        Mm_ComMsgMmStatusSnd( &MsgMmStatus );

        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* ��¼Ǩ��֮ǰ��״̬                       */
        if ( MM_FALSE == Mm_ComMmConnExist( ) )
        {                                                                       /* û�д��ڵ�MM���� */
            g_MmGlobalInfo.ucStaAfterWaitForNwkCmd = g_MmGlobalInfo.
                ucStaOfRcvXXEstReq;                                             /* ������е�״̬                           */
            Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );    /* MM��������                               */
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* ��¼Ǩ��֮ǰ��״̬                       */
            Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S27_E68:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
            Mm_TimerStart(MM_TIMER_T3240);                                      /* ����TIMER3240                            */
        }
        else
        {                                                                       /* �д��ڵ�MM���� */
            Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
            Mm_ComCheckDelayMmConn(VOS_FALSE);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S27_E68:NORMAL: STATUS is MM_CONNECTION_ACTIVE");
        }
    }

    return;

}

/*******************************************************************************
  MODULE   : Mm_Cell_S9_E47
  FUNCTION : ��WAIT FOR OUTGOING MM CONNECTION״̬���յ�
                RRMM_DATA_IND(CM SERVICE PROMPT)�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��      04-03-08    �°�����
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E47(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
    MM_MSG_MM_STATUS_STRU          MsgMmStatus;                                 /* MM STATUS ��Ϣ�ṹ��                     */

    if (MM_LIMITED_SERVICE != g_MmGlobalInfo.ucMmServiceState)
    {
        Mm_TimerStop(MM_TIMER_T3212);                                           /* ͣT3212                                  */
    }
    MsgMmStatus.MmIeRjctCause.ucRejCause =
        NAS_MML_REG_FAIL_CAUSE_MSG_TYPE_NOT_COMPATIBLE;                                   /* Service option not supported             */
    Mm_ComMsgMmStatusSnd( &MsgMmStatus );                                       /* ��䲢���� MM STATUS ��Ϣ                */

    return;
}
VOS_VOID Mm_Cell_S10_E47(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
    MM_MSG_MM_STATUS_STRU          MsgMmStatus;                                 /* MM STATUS ��Ϣ�ṹ��                     */
    VOS_UINT8                      aucClassmark2[4];


    PS_MEM_SET(aucClassmark2, 0x00, sizeof(aucClassmark2));

    MM_Fill_IE_ClassMark2(aucClassmark2);

    if ( MM_CONST_NUM_0 == ( aucClassmark2[3] & 0x04 ) )
    {                                                                           /* ��֧��CCBS                               */
        MsgMmStatus.MmIeRjctCause.ucRejCause =
            NAS_MML_REG_FAIL_CAUSE_MSG_NONEXIST_NOTIMPLEMENTE;                            /* Msg type non-existent or not implemented */
        Mm_ComMsgMmStatusSnd( &MsgMmStatus );                                   /* ��䲢���� MM STATUS ��Ϣ                */
    }
    else
    {                                                                           /* ֧��CCBS                                 */
        Mm_SndCcPromptInd();                                                    /* ��CC����MMCC_PROMPT_IND                  */
        g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;                   /* ��¼Ǩ��֮ǰ��״̬                       */
        Mm_ComSetMmState(PROCESS_CM_SERVICE_PROMPT);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S10_E47:NORMAL: STATUS is PROCESS_CM_SERVICE_PROMPT");
        Mm_TimerStart(MM_TIMER_PROTECT_CCBS);
    }

    return;
}
VOS_VOID Mm_Cell_S27_E27(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
    MMCC_DATA_REQ_STRU      *pMmCcDataReq;
    pMmCcDataReq = (MMCC_DATA_REQ_STRU*)pRcvMsg;

    if ( MM_FALSE == Mm_RcvCcDataReq(pRcvMsg) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        /*lint -e701*/
        if ( ( MM_CONST_NUM_7 > pMmCcDataReq->ulTransactionId)
           && ( MM_CONST_NUM_0 ==
           ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0]
           & ( 0x01 << pMmCcDataReq->ulTransactionId ) ) ) )
        {                                                                       /* ����Ϣ�е�TIС��7�����ڲ���TIO !=111     */
        }
        else if(((MM_CONST_NUM_7  < pMmCcDataReq->ulTransactionId)
            &&(MM_CONST_NUM_15 > pMmCcDataReq->ulTransactionId))
            && (MM_CONST_NUM_0 ==
            (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]
            & (0x01 << (pMmCcDataReq->ulTransactionId - 8)))))
        {                                                                       /* ����Ϣ�е�TI����7�����ڲ���TIO !=111     */
            Mm_TimerStop(MM_TIMER_PROTECT_CCBS);
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1] |=
                (VOS_UINT8)( 0x01 << ( pMmCcDataReq->ulTransactionId - 8 ) );   /* ���ø�TI����                             */
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* ��¼Ǩ��֮ǰ��״̬                       */
            Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S27_E27:NORMAL: STATUS is MM_CONNECTION_ACTIVE");
        }
        else
        {

        }
        Mm_SndRrDataReq(pMmCcDataReq->SendCcMsg.ulCcMsgSize,
                        &pMmCcDataReq->SendCcMsg.aucCcMsg[0],
                        RRC_NAS_MSG_PRIORTY_HIGH);                              /* ��CC����Ϣ������ȥ                       */

        /*lint +e701*/
    }

    return;

}

/*******************************************************************************
  MODULE   : Mm_Cell_S9_E69
  FUNCTION : ��WAIT FOR OUTGOING MM CONNECTION״̬��
             �յ�RRMM_DATA_IND( SS Message)�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��      04-03-11    �°�����
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E69(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
    VOS_UINT8                ucTI = 0;                                          /* CC��Ϣ�е�TI                             */
    RRMM_DATA_IND_STRU      *pRrDataInd = (RRMM_DATA_IND_STRU *)pRcvMsg;        /* ��ϢRRMM_DATA_IND�Ľṹ��ָ��            */
    VOS_UINT8               *pucCMMsg = VOS_NULL_PTR;                                                   /* ָ������ת��                             */
    VOS_UINT8               *pucBakCMMsg = VOS_NULL_PTR;

    if ( MM_LIMITED_SERVICE != g_MmGlobalInfo.ucMmServiceState )
    {
        Mm_TimerStop( MM_TIMER_T3212 );                                         /* ͣT3212                                  */
    }
    pucCMMsg = (VOS_UINT8 *)MM_MEM_ALLOC(
                           VOS_MEMPOOL_INDEX_MM,
                           pRrDataInd->RcvNasMsg.ulNasMsgSize,
                           WUEPS_MEM_NO_WAIT);                                  /* �����ڴ�                                 */
    if( VOS_NULL_PTR == pucCMMsg )
    {                                                                           /* �ڴ�����ʧ��                             */

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_Cell_S9_E69:ERROR: MALLOC ERROR!");
        return;                                                                 /* ����                                     */
    }
    pucBakCMMsg = pucCMMsg;
    PS_MEM_SET(pucCMMsg, 0, pRrDataInd->RcvNasMsg.ulNasMsgSize );              /* ��ʼ���ڴ�                               */
    PS_MEM_CPY (pucCMMsg, & ( pRrDataInd->RcvNasMsg.aucNasMsg[0] ),
        pRrDataInd->RcvNasMsg.ulNasMsgSize );                                   /* �õ���Ϣ����                             */
    ucTI = ( VOS_UINT8 )( ( ( pucCMMsg[0] & 0xf0 ) >> 4 ) );                        /* �õ�SS��Ϣ�е�TI                         */
    if ( MM_CONST_NUM_7 > ucTI )
    {                                                                           /* ���ཨ����MM����                         */
        /*lint -e701*/
        if ( MM_CONST_NUM_0 != (
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[0]
            & ( 0x01 << ucTI ) ) )
        {                                                                       /* �����Ӵ���                               */
            Mm_SndSsDataInd (
                (VOS_UINT32 )ucTI,
                pRrDataInd->RcvNasMsg.ulNasMsgSize,
                pucCMMsg );                                                     /* ��SS����MMSS_DATA_IND                    */
        }
        else
        {                                                                       /* �����Ӳ�����                             */
            Mm_SndSsEstInd ( ucTI, pRrDataInd->RcvNasMsg.ulNasMsgSize,
            pucCMMsg );                                                         /* ��SS����MMSS_EST_IND                     */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[0] |=
                ( VOS_UINT8 )( 0x01 << ucTI );                                      /* �����Ѿ����ڵ�MM���ӵı�־λ             */

            /* Ŀǰ������״̬����øú���
                WAIT_FOR_OUTGOING_MM_CONNECTION
                WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION
                MM_CONNECTION_ACTIVE
                ��������״̬���ֲ��䡣*/
            if ( g_MmGlobalInfo.ucState == WAIT_FOR_OUTGOING_MM_CONNECTION )
            {
                g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;                          /* ��¼Ǩ��֮ǰ��״̬                       */
                Mm_ComSetMmState(WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E69:NORMAL: STATUS is WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION");
            }


        }
        /*lint +e701*/
    }
    else if ( ( MM_CONST_NUM_7 < ucTI ) && ( MM_CONST_NUM_15 > ucTI ) )
    {                                                                           /* SS������MM����                           */
        /*lint -e701*/
        if ( MM_CONST_NUM_0 != (
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1]
            & ( 0x01 << ( ucTI - 8 ) ) ) )
        {                                                                       /* �����Ӵ���                               */
            Mm_SndSsDataInd ( ucTI, pRrDataInd->RcvNasMsg.ulNasMsgSize,
                pucCMMsg );                                                     /* ��SS����MMSS_DATA_IND                    */
        }
        else
        {                                                                       /* �����Ӳ�����                             */
            Mm_SndSsEstInd ( ucTI, pRrDataInd->RcvNasMsg.ulNasMsgSize,
            pucCMMsg );                                                         /* ��SS����MMSS_EST_IND                     */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1] |=
                ( VOS_UINT8 )( 0x01 << ( ucTI - 8 ) );                              /* �����Ѿ����ڵ�MM���ӵı�־λ             */
            Mm_TimerStop( MM_TIMER_T3230 );                                     /* ͣT3230                                  */
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* ��¼Ǩ��֮ǰ��״̬                       */
            Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E69:NORMAL: STATUS is MM_CONNECTION_ACTIVE");
            Mm_ComCheckDelayMmConn( MM_FALSE );
        }
        /*lint +e701*/
    }
    else
    {

    }
    MM_MEM_FREE(VOS_MEMPOOL_INDEX_NAS, pucBakCMMsg );                                /* �ͷ��������Ϣ                           */

    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S9_E70
  FUNCTION : ��WAIT FOR OUTGOING MM CONNECTION״̬��
             �յ�RRMM_DATA_IND( SMS Message)�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��      04-03-11    �°�����
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E70(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
    VOS_UINT8                ucTI = 0;                                          /* SMS��Ϣ�е�TI                            */
    RRMM_DATA_IND_STRU      *pRrDataInd = (RRMM_DATA_IND_STRU *)pRcvMsg;        /* ��ϢRRMM_DATA_IND�Ľṹ��ָ��            */
    VOS_UINT8               *pucCMMsg = VOS_NULL_PTR;                           /* ָ������ת��                             */
    VOS_UINT8               *pucBakCMMsg = VOS_NULL_PTR;

    if ( MM_LIMITED_SERVICE != g_MmGlobalInfo.ucMmServiceState )
    {
        Mm_TimerStop( MM_TIMER_T3212 );                                         /* ͣT3212                                  */
    }
    pucCMMsg = (VOS_UINT8 *)MM_MEM_ALLOC(
                           VOS_MEMPOOL_INDEX_MM,
                           pRrDataInd->RcvNasMsg.ulNasMsgSize,
                           WUEPS_MEM_NO_WAIT);                                  /* �����ڴ�                                 */
    if( VOS_NULL_PTR == pucCMMsg )
    {                                                                           /* �ڴ�����ʧ��                             */

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_Cell_S9_E70:ERROR: MALLOC ERROR!");
        return;                                                                 /* ����                                     */
    }
    pucBakCMMsg = pucCMMsg;
    PS_MEM_SET(pucCMMsg, 0, pRrDataInd->RcvNasMsg.ulNasMsgSize );              /* ��ʼ���ڴ�                               */
    PS_MEM_CPY (pucCMMsg, & ( pRrDataInd->RcvNasMsg.aucNasMsg[0] ),
        pRrDataInd->RcvNasMsg.ulNasMsgSize );                                   /* �õ���Ϣ����                             */
    ucTI = ( VOS_UINT8 )( ( ( pucCMMsg[0] & 0xf0 ) >> 4 ) );                        /* �õ�SMS��Ϣ�е�TI                        */
    if ( MM_CONST_NUM_7 > ucTI )
    {                                                                           /* ���ཨ����MM����                         */
        /*lint -e701*/
        if ( MM_CONST_NUM_0 != (
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[0]
            & ( 0x01 << ucTI ) ) )
        {                                                                       /* �����Ӵ���                               */
            Mm_SndSmsDataInd(
                (VOS_UINT32 )ucTI,
                pRrDataInd->RcvNasMsg.ulNasMsgSize,
                pucCMMsg );                                                     /* ��SMS����MMSMS_DATA_IND                  */
        }
        else
        {                                                                       /* �����Ӳ�����                             */
            Mm_SndSmsEstInd( ucTI, pRrDataInd->RcvNasMsg.ulNasMsgSize,
            pucCMMsg );                                                         /* ��SMS����MMSMS_EST_IND                   */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[0] |=
                ( VOS_UINT8 )( 0x01 << ucTI );                                      /* �����Ѿ����ڵ�MM���ӵı�־λ             */

            /* Ŀǰ������״̬����øú���
                WAIT_FOR_OUTGOING_MM_CONNECTION
                WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION
                MM_CONNECTION_ACTIVE
                ��������״̬���ֲ��䡣*/
            if ( g_MmGlobalInfo.ucState == WAIT_FOR_OUTGOING_MM_CONNECTION )
            {
                g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;                          /* ��¼Ǩ��֮ǰ��״̬                       */
                Mm_ComSetMmState(WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E70:NORMAL: STATUS is WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION");
            }


        }
        /*lint +e701*/
    }
    else if ( ( MM_CONST_NUM_7 < ucTI ) && ( MM_CONST_NUM_15 > ucTI ) )
    {                                                                           /* SMS������MM����                          */
        /*lint -e701*/
        if ( MM_CONST_NUM_0 != (
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1]
            & ( 0x01 << ( ucTI - 8 ) ) ) )
        {                                                                       /* �����Ӵ���                               */
            Mm_SndSmsDataInd( ucTI, pRrDataInd->RcvNasMsg.ulNasMsgSize,
                pucCMMsg );                                                     /* ��SMS����MMSMS_DATA_IND                  */
        }
        else
        {                                                                       /* �����Ӳ�����                             */
            Mm_SndSmsEstInd( ucTI, pRrDataInd->RcvNasMsg.ulNasMsgSize,
            pucCMMsg );                                                         /* ��SMS����MMSMS_EST_IND                   */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1] |=
                ( VOS_UINT8 )( 0x01 << ( ucTI - 8 ) );                              /* �����Ѿ����ڵ�MM���ӵı�־λ             */
            Mm_TimerStop( MM_TIMER_T3230 );                                     /* ͣT3230                                  */
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* ��¼Ǩ��֮ǰ��״̬                       */
            Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E70:NORMAL: STATUS is MM_CONNECTION_ACTIVE");
            Mm_ComCheckDelayMmConn( MM_FALSE );
        }
        /*lint +e701*/
    }
    else
    {

    }
    MM_MEM_FREE(VOS_MEMPOOL_INDEX_NAS, pucBakCMMsg);                            /* �ͷ��������Ϣ                           */

    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S11_E69
  FUNCTION : ��WAIT_FOR_NETWORK_COMMAND ״̬��
             �յ�RRMM_DATA_IND( SS Message)�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��      04-03-11  �°�����

     2.��    ��   : 2011��7��14��
       ��    ��   : zhoujun 40661
       �޸�����   : ����MML_CTX�е�ҵ�����״̬
*******************************************************************************/
VOS_VOID Mm_Cell_S11_E69(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{

    VOS_UINT8   ucTI = 0;                                                           /* SS��Ϣ�е�TI                             */
    RRMM_DATA_IND_STRU *pRrDataInd = ( RRMM_DATA_IND_STRU *) pRcvMsg;           /* ��ϢRRMM_DATA_IND�Ľṹ��ָ��            */
    VOS_UINT8   *pucCMMsg = VOS_NULL_PTR;                                                   /* ָ������ת��                             */
    VOS_UINT8   *pucBakCMMsg = VOS_NULL_PTR;

    Mm_TimerStop( MM_TIMER_T3240 );                                             /* ͣTIMER3240                              */
    pucCMMsg = (VOS_UINT8 *)MM_MEM_ALLOC(
                           VOS_MEMPOOL_INDEX_MM,
                           pRrDataInd->RcvNasMsg.ulNasMsgSize,
                           WUEPS_MEM_NO_WAIT);                                  /* �����ڴ�                                 */
    if( VOS_NULL_PTR == pucCMMsg )
    {                                                                           /* �ڴ�����ʧ��                             */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S11_E69:WARNING: MALLOC ERROR!");
        return;                                                                 /* ����                                     */
    }
    pucBakCMMsg = pucCMMsg;
    PS_MEM_SET(pucCMMsg, 0, pRrDataInd->RcvNasMsg.ulNasMsgSize );              /* ��ʼ���ڴ�                               */
    PS_MEM_CPY (pucCMMsg, & ( pRrDataInd->RcvNasMsg.aucNasMsg[0] ),
        pRrDataInd->RcvNasMsg.ulNasMsgSize );                                   /* �õ���Ϣ����                             */
    /*lint -e701*/
    ucTI = ( VOS_UINT8 )( ( ( pucCMMsg[0] & 0xf0 ) >> 4 ) );                        /* �õ�SS��Ϣ�е�TI                         */
    if ( MM_CONST_NUM_7 > ucTI )
    {                                                                           /* ���ཨ����MM����                         */
        Mm_SndSsEstInd ( ucTI, pRrDataInd->RcvNasMsg.ulNasMsgSize, pucCMMsg );  /* ��SS����MMSS_EST_IND                     */
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[0] |=
        ( VOS_UINT8 )( 0x01 << ucTI );                                              /* �����Ѿ����ڵ�MM���ӵı�־λ             */
        g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;                   /* ��¼Ǩ��֮ǰ��״̬                       */
        Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S11_E69:NORMAL: STATUS is MM_CONNECTION_ACTIVE");
        Mm_ComCheckDelayMmConn( MM_FALSE );

    }
    else if ( ( MM_CONST_NUM_7 < ucTI ) && ( MM_CONST_NUM_15 > ucTI ) )
    {                                                                           /* SS������MM����                           */
        Mm_SndSsEstInd ( ucTI, pRrDataInd->RcvNasMsg.ulNasMsgSize, pucCMMsg );  /* ��SS����MMSS_EST_IND                     */
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1] |=
            ( VOS_UINT8 )( 0x01 << ( ucTI - 8 ) );                                  /* �����Ѿ����ڵ�MM���ӵı�־λ             */
        g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;                   /* ��¼Ǩ��֮ǰ��״̬                       */
        Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S11_E69:NORMAL: STATUS is MM_CONNECTION_ACTIVE");
        Mm_ComCheckDelayMmConn( MM_FALSE );
    }
    else
    {
    }
    /*lint +e701*/
    MM_MEM_FREE(VOS_MEMPOOL_INDEX_NAS, pucBakCMMsg);                                /* �ͷ��������Ϣ                           */

    NAS_MM_UpdateCsServiceConnStatusFlg();

    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S11_E70
  FUNCTION : ��WAIT_FOR_NETWORK_COMMAND ״̬��
             �յ�RRMM_DATA_IND( SMS Message)�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��      04-03-11  �°�����

     2.��    ��   : 2011��7��14��
       ��    ��   : zhoujun 40661
       �޸�����   : ����MML_CTX�е�ҵ�����״̬
*******************************************************************************/
VOS_VOID Mm_Cell_S11_E70(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{

    VOS_UINT8   ucTI = 0;                                                           /* SMS��Ϣ�е�TI                            */
    RRMM_DATA_IND_STRU *pRrDataInd = ( RRMM_DATA_IND_STRU *) pRcvMsg;           /* ��ϢRRMM_DATA_IND�Ľṹ��ָ��            */
    VOS_UINT8   *pucCMMsg = VOS_NULL_PTR;                                       /* ָ������ת��                             */
    VOS_UINT8   *pucBakCMMsg = VOS_NULL_PTR;

    Mm_TimerStop( MM_TIMER_T3240 );                                             /* ͣTIMER3240                              */
    pucCMMsg = (VOS_UINT8 *)MM_MEM_ALLOC(
                           VOS_MEMPOOL_INDEX_MM,
                           pRrDataInd->RcvNasMsg.ulNasMsgSize,
                           WUEPS_MEM_NO_WAIT);                                  /* �����ڴ�                                 */
    if( VOS_NULL_PTR == pucCMMsg )
    {                                                                           /* �ڴ�����ʧ��                             */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S11_E70:WARNING: MALLOC ERROR!");
        return;                                                                 /* ����                                     */
    }
    pucBakCMMsg = pucCMMsg;
    PS_MEM_SET(pucCMMsg, 0, pRrDataInd->RcvNasMsg.ulNasMsgSize );              /* ��ʼ���ڴ�                               */
    PS_MEM_CPY (pucCMMsg, & ( pRrDataInd->RcvNasMsg.aucNasMsg[0] ),
        pRrDataInd->RcvNasMsg.ulNasMsgSize );                                   /* �õ���Ϣ����                             */
    ucTI = ( VOS_UINT8 )( ( ( pucCMMsg[0] & 0xf0 ) >> 4 ) );                        /* �õ�SMS��Ϣ�е�TI                        */
    if ( MM_CONST_NUM_7 > ucTI )
    {                                                                           /* ���ཨ����MM����                         */
        Mm_SndSmsEstInd( ucTI, pRrDataInd->RcvNasMsg.ulNasMsgSize,
        pucCMMsg );                                                             /* ��SMS����MMSMS_EST_IND                   */

        /*lint -e701*/
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[0] |=
            ( VOS_UINT8 )( 0x01 << ucTI );                                          /* �����Ѿ����ڵ�MM���ӵı�־λ             */
        /*lint +e701*/
        g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;                   /* ��¼Ǩ��֮ǰ��״̬                       */
        Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S11_E70:NORMAL: STATUS is MM_CONNECTION_ACTIVE");
        Mm_ComCheckDelayMmConn( MM_FALSE );
    }
    else if ( ( MM_CONST_NUM_7 < ucTI ) && ( MM_CONST_NUM_15 > ucTI ) )
    {                                                                           /* SMS������MM����                          */
        Mm_SndSmsEstInd( ucTI, pRrDataInd->RcvNasMsg.ulNasMsgSize,
        pucCMMsg );                                                             /* ��SMS����MMSMS_EST_IND                   */

        /*lint -e701*/
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1] |=
            ( VOS_UINT8 )( 0x01 << ( ucTI - 8 ) );                                  /* �����Ѿ����ڵ�MM���ӵı�־λ             */
        /*lint +e701*/

        g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;                   /* ��¼Ǩ��֮ǰ��״̬                       */
        Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S11_E70:NORMAL: STATUS is MM_CONNECTION_ACTIVE");
        Mm_ComCheckDelayMmConn( MM_FALSE );
    }
    else
    {
    }
    MM_MEM_FREE(VOS_MEMPOOL_INDEX_NAS, pucBakCMMsg);                            /* �ͷ��������Ϣ                           */

    NAS_MM_UpdateCsServiceConnStatusFlg();


    return;
}

VOS_VOID Mm_Cell_S10_E67(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{
    MMSS_DATA_REQ_STRU      *pMmSsDataReq;
    pMmSsDataReq = ( MMSS_DATA_REQ_STRU* )pRcvMsg;

    if ( MM_FALSE == Mm_RcvSsDataReq(pRcvMsg) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        /*lint -e701*/
        if ( ( ( MM_CONST_NUM_7 > pMmSsDataReq->ulTi )
            && ( MM_CONST_NUM_0 !=
            ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[0]
            & ( 0x01 << pMmSsDataReq->ulTi ) ) ) )
            || ( ( MM_CONST_NUM_7 < pMmSsDataReq->ulTi )
            && ( MM_CONST_NUM_0 !=
            ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1]
            & ( 0x01 << ( pMmSsDataReq->ulTi - 8 ) ) ) ) ) )
        {                                                                       /* ��TI��MM���Ӵ���                         */
            Mm_SndRrDataReq( pMmSsDataReq->SsMsg.ulSsMsgSize,
                &pMmSsDataReq->SsMsg.aucSsMsg[0],
                RRC_NAS_MSG_PRIORTY_HIGH);                                      /* ��SS����Ϣ������ȥ                       */
        }
        else
        {                                                                       /* ��TI��MM���Ӳ�����                       */
            Mm_SndSsRelInd( pMmSsDataReq->ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);                               /* ֪ͨSS����ʧ��                           */
        }

        /*lint +e701*/
    }

    return;
}
VOS_VOID Mm_Cell_S10_E64(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{
    MMSMS_DATA_REQ_STRU      *pMmSmsDataReq;
    pMmSmsDataReq = ( MMSMS_DATA_REQ_STRU* )pRcvMsg;

    if ( MM_FALSE == Mm_RcvSmsDataReq(pRcvMsg) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        /*lint -e701*/
        if ( ( ( MM_CONST_NUM_7 > pMmSmsDataReq->ulTi )
            && ( MM_CONST_NUM_0 !=
            ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[0]
            & ( 0x01 << pMmSmsDataReq->ulTi ) ) ) )
            || ( ( MM_CONST_NUM_7 < pMmSmsDataReq->ulTi )
            && ( MM_CONST_NUM_0 !=
            ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1]
            & ( 0x01 << ( pMmSmsDataReq->ulTi - 8 ) ) ) ) ) )
        {                                                                       /* ��TI��MM���Ӵ���                         */
            Mm_SndRrDataReq( pMmSmsDataReq->SmsMsg.ulNasMsgSize,
                &pMmSmsDataReq->SmsMsg.aucNasMsg[0],
                RRC_NAS_MSG_PRIORTY_LOW);                                       /* ��SMS����Ϣ������ȥ                      */
        }
        else
        {                                                                       /* ��TI��MM���Ӳ�����                       */
            Mm_SndSmsRelInd(pMmSmsDataReq->ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);/* ֪ͨSMS����ʧ��                          */
        }

        /*lint +e701*/
    }

    return;
}
VOS_VOID Mm_Cell_S9_E25(
    VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
)
{
    if ( MM_FALSE == Mm_RcvCcRelReq( pRcvMsg ) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        if ( ( MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg )
          && ( ( ( MMCC_RELEASE_SPECIFIC == g_MmCcRelReq.ulReleaseType )
              && ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                                                RcvXXEstReq.ulTransactionId
            == g_MmCcRelReq.ulTransactionId ) )
            || ( MMCC_RELEASE_ALL == g_MmCcRelReq.ulReleaseType ) ) )
        {                                                                       /* Ҫ���ͷŵ�MM�����Ǳ������       */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg = MM_FALSE;                                                     /* ���ò����ڻ����MM���� */
        }
        else
        {
            /* ���ֵ���ᱨ��ȥ����ΪCC�ڷ�MMCC_REL_REQʱ������ʱCC���CALL��MNCC_REL_IND,MNCC_REL_CNF,MNCC_REJ_IND
               ����Ǳ��У�setup���ʧ�ܣ�ring��û����ȥ��������CEND�ϱ� */
            Mm_SndCcRelInd( g_MmCcRelReq.ulTransactionId, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_REL_REQ);/* ֪ͨCCָ���ͷŵ�MM���Ӳ�����             */
        }

        NAS_MM_UpdateCsServiceBufferStatusFlg();

     }

    return;
}


VOS_VOID Mm_Cell_S12_E25(VOS_VOID  *pRcvMsg)
{
    if ( MM_FALSE == Mm_RcvCcRelReq( pRcvMsg ) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
    }
    else
    {
        if ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI ==
                g_MmCcRelReq.ulTransactionId )
        {
            /* ��ֹ��MM���ӽ��������ڽ�����,������뼼����ͬ����rel req */
            if (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucRat == NAS_MML_GetCurrNetRatType())
            {
                Mm_SndRrRelReq(RRC_CELL_UNBARRED);
                g_MmGlobalInfo.bWaitingEstCnf = VOS_FALSE;
                g_MmGlobalInfo.ucStaAfterWaitForNwkCmd = g_MmGlobalInfo.ucStaOfRcvXXEstReq;
                Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
                Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL);
                NAS_NORMAL_LOG(WUEPS_PID_MM, "Mm_Cell_S12_E26:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
                Mm_TimerStart(MM_TIMER_T3240);
            }
            else
            {
                Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);
            }

            Mm_TimerStop( MM_TIMER_PROTECT_SIGNALLING );

            /* ���MM���ȫ�ֱ��� */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI  = NO_MM_CONN_ESTING;
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg = MM_FALSE;
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;

        }
        else
        {
            if ((MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg)
             && (g_MmCcRelReq.ulTransactionId ==
                     g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId))
            {
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg = MM_FALSE;
                Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);
                NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
            }
        }

#if (FEATURE_ON == FEATURE_LTE)
        if (VOS_TRUE == NAS_MML_IsCsfbServiceStatusExist())
        {
            NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

            NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);
        }
#endif

        NAS_MM_UpdateCsServiceBufferStatusFlg();
    }

    return;
}




VOS_VOID Mm_Cell_S1_E63(VOS_VOID    *pRcvMsg)
{
    if (MM_FALSE == Mm_RcvSmsRelReq(pRcvMsg))
    {
    }
    else
    {
        /*�������SMS����SS�Ļ��棬��Ҫ���*/
        if ( (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg)
          && (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulTransactionId == g_MmSmsRelReq.ulTi) )
        {
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg = MM_FALSE;
        }

        NAS_MM_UpdateCsServiceBufferStatusFlg();
    }
}
VOS_VOID Mm_Cell_S32_E63(
    VOS_VOID                           *pRcvMsg
)
{
    if (WAIT_FOR_OUTGOING_MM_CONNECTION == g_MmGlobalInfo.ucSuspendPreState)
    {
        Mm_Cell_S32_DataTransfer(pRcvMsg);
        return;
    }

    if (MM_FALSE == Mm_RcvSmsRelReq(pRcvMsg))
    {
    }
    else
    {
        /*�������SMS����SS�Ļ��棬��Ҫ���*/
        if ( (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg)
          && (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulTransactionId == g_MmSmsRelReq.ulTi) )
        {
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg = MM_FALSE;
        }

        NAS_MM_SndRrMmServiceAbortNotify(WUEPS_PID_WRR);
        NAS_MM_SndRrMmServiceAbortNotify(UEPS_PID_GAS);

        NAS_MM_UpdateCsServiceBufferStatusFlg();
    }
}





/*******************************************************************************
  MODULE   : Mm_Cell_S10_E63
  FUNCTION : ��MM CONNECTION ACTIVE״̬���յ�MMSMS_REL_REQ�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��      04-03-24  �°�����

     2.��    ��   : 2011��7��14��
       ��    ��   : zhoujun 40661
       �޸�����   : ����MML_CTX�е�ҵ�����״̬
*******************************************************************************/
VOS_VOID Mm_Cell_S10_E63(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{
    if ( MM_FALSE == Mm_RcvSmsRelReq(pRcvMsg) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        /*lint -e701*/
        if ( ( MM_CONST_NUM_7 > g_MmSmsRelReq.ulTi ) &&
            ( MM_CONST_NUM_0 !=
            ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[0]
            & ( 0x01 << g_MmSmsRelReq.ulTi ) ) ) )
        {                                                                       /* TIС��7���Ҹ�MM���Ӵ���                  */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[0] &=
                ~(VOS_UINT8)( 0x01 << g_MmSmsRelReq.ulTi );                         /* ����ñ�־λ                             */
        }
        if ( ( MM_CONST_NUM_7 < g_MmSmsRelReq.ulTi ) &&
            ( MM_CONST_NUM_15 > g_MmSmsRelReq.ulTi ) &&
            ( MM_CONST_NUM_0 !=
            ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1]
            & ( 0x01 << ( g_MmSmsRelReq.ulTi - 8 ) ) ) ) )
        {                                                                       /* TIС��7���Ҹ�MM���Ӵ���                  */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1] &=
                ~(VOS_UINT8)( 0x01 << ( g_MmSmsRelReq.ulTi - 8 ) );                 /* ����ñ�־λ                             */
        }
        /*lint +e701*/
        if ( ( MM_CONST_NUM_0 ==
          g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0] )
          && ( MM_CONST_NUM_0 ==
          g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1] )
          && ( MM_CONST_NUM_0 ==
          g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[0] )
          && ( MM_CONST_NUM_0 ==
          g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1] )
          && ( MM_CONST_NUM_0 ==
          g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[0] )
          && ( MM_CONST_NUM_0 ==
          g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1]) )
        {                                                                       /* û��MM���Ӵ���                           */
            g_MmGlobalInfo.ucStaAfterWaitForNwkCmd =
                g_MmGlobalInfo.ucStaOfRcvXXEstReq;                              /* ������е�״̬                           */
            Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );    /* MM��������                               */
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* ��¼Ǩ��֮ǰ��״̬                       */
            Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S10_E63:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
            Mm_TimerStart(MM_TIMER_T3240);                                      /* ����TIMER3240                            */
        }
    }

    NAS_MM_UpdateCsServiceConnStatusFlg();

    return;
}

VOS_VOID Mm_Cell_S12_E63(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
    if ( MM_FALSE == Mm_RcvSmsRelReq(pRcvMsg) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S12_E63:WARNING:  CHECK PRIMITIVE ERROR!");
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        if ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI ==
            g_MmSmsRelReq.ulTi )
        {
            if (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucRat == NAS_MML_GetCurrNetRatType())
            {
                /* ��ֹ��MM���ӽ��������ڽ�����             */
                Mm_SndRrRelReq(RRC_CELL_UNBARRED);

                g_MmGlobalInfo.ucStaAfterWaitForNwkCmd =
                    g_MmGlobalInfo.ucStaOfRcvXXEstReq;                              /* ���ص����յ�����MM��������ʱ��״̬       */
                Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
                Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );    /* MM��������                               */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S12_E63:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
                Mm_TimerStart(MM_TIMER_T3240);                                      /* ����TIMER3240                            */
            }
            else
            {
                Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);
            }

            Mm_TimerStop( MM_TIMER_PROTECT_SIGNALLING );
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI =
                NO_MM_CONN_ESTING;                                              /* ������ڽ�����MM���ӵı�־               */

            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg = MM_FALSE;
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* ��¼Ǩ��֮ǰ��״̬                       */
        }
        else
        {
            if ( ( MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                                                          .RcvXXEstReq.ucFlg )
             && ( g_MmSsAbortReq.ulTransactionId ==
             g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.
                                                            ulTransactionId ) )
            {
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                                                 .RcvXXEstReq.ucFlg = MM_FALSE;
            }
        }

        NAS_MM_UpdateCsServiceBufferStatusFlg();
    }

    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S16_E63
  FUNCTION : ��WAIT FOR ADDITIONAL OUTGOING MM CONNECTION״̬���յ�MMSMS_REL_REQ�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��    2005.03.28  �°�����

     2.��    ��   : 2011��7��14��
       ��    ��   : zhoujun 40661
       �޸�����   : ����MML_CTX�е�ҵ�����״̬
*******************************************************************************/
VOS_VOID Mm_Cell_S16_E63(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
    if ( MM_FALSE == Mm_RcvSmsRelReq(pRcvMsg) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        /*lint -e701*/
        if ( ( MM_CONST_NUM_7 > g_MmSmsRelReq.ulTi ) &&
            ( MM_CONST_NUM_0 !=
            ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[0]
            & ( 0x01 << g_MmSmsRelReq.ulTi ) ) ) )
        {                                                                       /* TIС��7���Ҹ�MM���Ӵ���                  */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[0] &=
                ~(VOS_UINT8)( 0x01 << g_MmSmsRelReq.ulTi );                     /* ����ñ�־λ                             */
        }
        if ( ( MM_CONST_NUM_7 < g_MmSmsRelReq.ulTi ) &&
            ( MM_CONST_NUM_15 > g_MmSmsRelReq.ulTi ) &&
            ( MM_CONST_NUM_0 !=
            ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1]
            & ( 0x01 << ( g_MmSmsRelReq.ulTi - 8 ) ) ) ) )
        {                                                                       /* TIС��7���Ҹ�MM���Ӵ���                  */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1] &=
                ~(VOS_UINT8)( 0x01 << ( g_MmSmsRelReq.ulTi - 8 ) );             /* ����ñ�־λ                             */
        }
        /*lint +e701*/
        if ( ( MM_TRUE ==
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                                                    RcvXXEstReq.ucFlg )
                && ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                RcvXXEstReq.ulTransactionId == g_MmSmsRelReq.ulTi ) )
        {
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg
                = MM_FALSE;                                                     /* ���ò����ڻ����MM���� */
        }
        if ( ( MM_CONST_NUM_0 ==
          g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0] )
          && ( MM_CONST_NUM_0 ==
          g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1] )
          && ( MM_CONST_NUM_0 ==
          g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[0] )
          && ( MM_CONST_NUM_0 ==
          g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1] )
          && ( MM_CONST_NUM_0 ==
          g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[0] )
          && ( MM_CONST_NUM_0 ==
          g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1]) )
        {                                                                       /* û��MM���Ӵ���                           */
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* ��¼Ǩ��֮ǰ��״̬                       */
            Mm_ComSetMmState(WAIT_FOR_OUTGOING_MM_CONNECTION);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S16_E63:NORMAL: STATUS is WAIT_FOR_OUTGOING_MM_CONNECTION");
        }
    }

    NAS_MM_UpdateCsServiceConnStatusFlg();

    NAS_MM_UpdateCsServiceBufferStatusFlg();

    return;
}


VOS_VOID Mm_Cell_S3_E49(
    VOS_VOID                           *pRcvMsg
)
{
    g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;

    Mm_ComSetMmState(MM_IDLE_PLMN_SEARCH);

    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S3_E49:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");

    return;
}


VOS_VOID Mm_Cell_S11_E49(
    VOS_VOID                           *pRcvMsg
)
{

    Mm_SndRrRelReq(RRC_CELL_UNBARRED);                                      /* ��RRC����RRMM_REL_REQ(CS��)              */

    Mm_TimerStop(MM_TIMER_T3240);
    Mm_TimerStop(MM_TIMER_T3218);
    Mm_ComDelRandRes();

    if ( (MM_LU_PROC == g_MmGlobalInfo.ucProc)
      && (NAS_MML_REG_FAIL_CAUSE_NULL == g_MmGlobalInfo.usCauseVal) )
    {
        NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);

        if (MM_DETACH_NEED_DELAY == g_MmGlobalInfo.ucDetachType)
        {
            Mm_TimerStop(MM_TIMER_PROTECT_DETACH);
            g_MmGlobalInfo.ucDetachType = MM_DETACH_TYPE_BUTT;
            Mm_Cell_S3_E23(VOS_NULL_PTR);
        }

        Mm_ComProcCauseClear();
    }
    else if ( (MM_MM_CONN_PROC == g_MmGlobalInfo.ucProc)
           && (NAS_MML_REG_FAIL_CAUSE_NULL == g_MmGlobalInfo.usCauseVal) )
    {
        Mm_ComProcCauseClear();
    }
    else
    {
        Mm_ComProcCauseProcess();
    }

    Mm_TimerStart(MM_TIMER_WAIT_CONNECT_REL);

    g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;

    Mm_ComSetMmState(MM_IDLE_PLMN_SEARCH);

    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S11_E49:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");

    return;
}
VOS_VOID Mm_Cell_S9_E49(
    VOS_VOID                           *pRcvMsg
)
{

    Mm_SndRrRelReq(RRC_CELL_UNBARRED);                                      /* ��RRC����RRMM_REL_REQ(CS��)              */

    Mm_TimerStop(MM_TIMER_T3230);

    Mm_ComDelRandRes();

    g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;

    Mm_ComSetMmState(MM_IDLE_PLMN_SEARCH);

    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E49:NORMAL: STATUS is WAIT FOR OUTGOING MM CONNECTION");

    return;
}
VOS_VOID Mm_Cell_S10_E49(
    VOS_VOID                           *pRcvMsg
)
{

    Mm_SndRrRelReq(RRC_CELL_UNBARRED);                                      /* ��RRC����RRMM_REL_REQ(CS��)              */

    Mm_ComDelRandRes();

    g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;

    Mm_ComSetMmState(MM_IDLE_PLMN_SEARCH);

    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S10_E49:NORMAL: STATUS is MM CONNECTION ACTIVE");

    return;
}
VOS_VOID Mm_Cell_S12_E49(
    VOS_VOID                           *pRcvMsg
)
{

    Mm_SndRrRelReq(RRC_CELL_UNBARRED);                                      /* ��RRC����RRMM_REL_REQ(CS��)              */

    Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);

    Mm_ComDelRandRes();

    g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;

    Mm_ComSetMmState(MM_IDLE_PLMN_SEARCH);

    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S12_E49:NORMAL: STATUS is WAIT FOR RR CONNECTION");

    return;
}
VOS_VOID Mm_Cell_S22_E49(
    VOS_VOID                           *pRcvMsg
)
{
    /* ��RRC����RRMM_REL_REQ(CS��) */
    Mm_SndRrRelReq(RRC_CELL_UNBARRED);

    Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);

    Mm_TimerStart(MM_TIMER_WAIT_CONNECT_REL);

    g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;

    Mm_ComSetMmState(MM_IDLE_PLMN_SEARCH);

    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S22_E49:NORMAL: STATUS is WAIT_FOR_RR_CONNECTION_LOCATION_UPDATING");

    return;
}
VOS_VOID Mm_Cell_S23_E49(
    VOS_VOID                           *pRcvMsg
)
{
    /* ��RRC����RRMM_REL_REQ(CS��) */
    Mm_SndRrRelReq(RRC_CELL_UNBARRED);

    Mm_TimerStop(MM_TIMER_T3211);

    Mm_TimerStart(MM_TIMER_WAIT_CONNECT_REL);


    /* �ظ�MMCMM_ATTACH_CNF�Ĳ���,����ȴ�ATTACH�����־λ */
    if (MM_WAIT_CS_ATTACH == (g_MmGlobalInfo.stAttachInfo.enAttachType
                            & MM_WAIT_CS_ATTACH))
    {
        NAS_MM_SndMmcAttachCnf();
    }
    g_MmGlobalInfo.stAttachInfo.enAttachType = MM_WAIT_NULL_ATTACH;

    NAS_MM_ClearAuthInfo();

    g_MmSubLyrShare.MmShare.ucCsIntegrityProtect  = NAS_MML_RRC_INTEGRITY_PROTECT_DEACTIVE;

    g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;

    /* ��Ϊ����LAUʧ�� */
    NAS_MM_LocationUpdateAttemptCounter(NAS_MML_REG_FAIL_CAUSE_RR_CONN_ABORT);         /* ����RAU attempt counter�Ĵ���            */

    g_MmGlobalInfo.LuInfo.ucRetryFlg = MM_FALSE;


    g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;

    Mm_ComSetMmState(MM_IDLE_PLMN_SEARCH);

    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S23_E49:NORMAL: STATUS is LOCATION_UPDATING_INITIATED");

    return;
}
VOS_VOID Mm_Cell_S24_E49(
    VOS_VOID                           *pRcvMsg
)
{
    /* ��RRC����RRMM_REL_REQ(CS��) */
    Mm_SndRrRelReq(RRC_CELL_UNBARRED);

    Mm_TimerStop(MM_TIMER_T3240);
    Mm_TimerStop(MM_TIMER_T3218);

    Mm_ComDelRandRes();
    Mm_ComProcCauseProcess();

    Mm_TimerStart(MM_TIMER_WAIT_CONNECT_REL);

    g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;

    Mm_ComSetMmState(MM_IDLE_PLMN_SEARCH);

    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S24_E49:NORMAL: STATUS is LOCATION_UPDATE_REJECTED");

    return;
}
VOS_VOID Mm_Cell_S25_E49(
    VOS_VOID                           *pRcvMsg
)
{
    if (MM_DETACH_CS_POWEROFF == g_MmGlobalInfo.ucDetachType)
    {
        return;
    }

    /* ��RRC����RRMM_REL_REQ(CS��) */
    Mm_SndRrRelReq(RRC_CELL_UNBARRED);

    Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);

    Mm_TimerStop(MM_TIMER_PROTECT_DETACH);

    /* �жϵȴ���־�Ƿ���ڣ������������MMCMM_DETACH CNF */
    if (MM_WAIT_CS_DETACH== (g_MmGlobalInfo.stDetachInfo.enDetachType
                 & MM_WAIT_CS_DETACH))
    {
        NAS_MM_SndMmcDetachCnf(MM_DETACHED);

        /* ����ȴ���־ */
        g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_NULL_DETACH;
    }

    Mm_TimerStart(MM_TIMER_WAIT_CONNECT_REL);

    g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;

    Mm_ComSetMmState(MM_IDLE_PLMN_SEARCH);

    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S25_E49:NORMAL: STATUS is WAIT_FOR_RR_CONNECTION_IMSI_DETACH");

    return;
}


VOS_VOID Mm_Cell_S26_E49(
    VOS_VOID                           *pRcvMsg
)
{
    if (MM_DETACH_CS_POWEROFF == g_MmGlobalInfo.ucDetachType)
    {
        return;
    }

    /* ��RRC����RRMM_REL_REQ(CS��) */
    Mm_SndRrRelReq(RRC_CELL_UNBARRED);

    Mm_TimerStop(MM_TIMER_T3220);

    Mm_TimerStop(MM_TIMER_PROTECT_DETACH);

    Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                     NAS_MML_GetSimCsSecurityCksn());

    /* �жϵȴ���־�Ƿ���ڣ������������MMCMM_DETACH CNF */
    if (MM_WAIT_CS_DETACH== (g_MmGlobalInfo.stDetachInfo.enDetachType
                 & MM_WAIT_CS_DETACH))
    {
        NAS_MM_SndMmcDetachCnf(MM_DETACHED);
        /* ����ȴ���־ */
        g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_NULL_DETACH;
    }

    g_MmGlobalInfo.ucPowerOnFlg = MM_TRUE;

    NAS_EventReport(WUEPS_PID_MM, NAS_OM_EVENT_IMSI_DETACH_IND,
                    VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    Mm_TimerStart(MM_TIMER_WAIT_CONNECT_REL);

    g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;

    Mm_ComSetMmState(MM_IDLE_PLMN_SEARCH);

    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S26_E49:NORMAL: STATUS is IMSI_DETACH_INITIATED");

    return;
}
VOS_VOID Mm_Cell_S27_E87(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
    MMCC_DATA_REQ_STRU *pstMsg;
    VOS_UINT8                           ucTi;

    pstMsg = (MMCC_DATA_REQ_STRU *)pRcvMsg;

    ucTi = (VOS_UINT8)pstMsg->ulTransactionId;
    /*lint -e701*/
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]  =
    (VOS_UINT8)( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]
               | (0x01 << (ucTi - 0x08)) );
    /*lint +e701*/
    Mm_TimerStop(MM_TIMER_PROTECT_CCBS);
    Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
    Mm_SndRrDataReq(pstMsg->SendCcMsg.ulCcMsgSize,
                            &pstMsg->SendCcMsg.aucCcMsg[0],
                            RRC_NAS_MSG_PRIORTY_HIGH);

    Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);
    NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_ESTING);

    Mm_ComCheckDelayMmConn(VOS_FALSE);

    NAS_MM_UpdateCsServiceConnStatusFlg();
}
VOS_VOID Mm_Cell_S3_E88(
    VOS_VOID                           *pRcvMsg
)
{
    MMCMM_W_AC_INFO_CHANGE_IND_STRU  *pstAcInfoChangeInd = VOS_NULL_PTR;

    pstAcInfoChangeInd = (MMCMM_W_AC_INFO_CHANGE_IND_STRU*)pRcvMsg;

    /* ��ǰС����Ϊע�����ޣ���ҪǨ��MM״̬ */
    if (NAS_MML_RESTRICTION_UNBAR_TO_BAR == pstAcInfoChangeInd->enCsRestrictRegisterChange)
    {
        g_MmGlobalInfo.ucMmServiceState = NAS_MM_GetLauUptNeededCsSrvStatus();
        Mm_ComSetMmState(MM_IDLE_LOCATION_UPDATE_NEEDED);

    }
}
VOS_VOID Mm_Cell_S6_E88(
    VOS_VOID                           *pRcvMsg
)
{
    MMCMM_W_AC_INFO_CHANGE_IND_STRU    *pstAcInfoChangeInd = VOS_NULL_PTR;

    pstAcInfoChangeInd  = (MMCMM_W_AC_INFO_CHANGE_IND_STRU*)pRcvMsg;

    /* ��ǰС����CSע�����ޱ�Ϊ������ */
    if (NAS_MML_RESTRICTION_BAR_TO_UNBAR == pstAcInfoChangeInd->enCsRestrictRegisterChange)
    {
        /* �û����ò�֧��CS */
        if (VOS_FALSE == NAS_MML_GetCsAttachAllowFlg())
        {
            Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
            return;
        }

        /* ��ǰ�����ڽ�ֹ�б��� */
        if ((MMCMM_NO_FORBIDDEN != g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg)
         && (MMCMM_FORBIDDEN_PLMN_FOR_GPRS != g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg))
        {
            g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;               /* ���÷���״̬                             */
            Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
            return;
        }

        if (VOS_TRUE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNtMod))
        {
            /* ����PSע������ */
            if (VOS_TRUE == NAS_MML_GetPsRestrictRegisterFlg())
            {                                                                   /* RACΪ0�ĳ���                             */
                NAS_MM_ProcCsAcChgRegisterNetModeII();
            }
            /* ����GPRS��֧�ֻ�GPRS��ֹ */
            else if ((MM_UNSUPPORT_GPRS == g_MmGlobalInfo.usRac)
             || (MMCMM_FORBIDDEN_PLMN_FOR_GPRS == g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg))
            {
                NAS_MM_SetLikeBFlg();
                NAS_MM_ProcCsAcChgRegisterNetModeII();
            }
            else
            {
            }
        }
        else
        {
            NAS_MM_ProcCsAcChgRegisterNetModeII();
        }
    }
}
VOS_VOID Mm_Cell_S9_E88(
    VOS_VOID                           *pRcvMsg
)
{
    MMCMM_W_AC_INFO_CHANGE_IND_STRU            *pstAcInfoChangeInd = VOS_NULL_PTR;

    pstAcInfoChangeInd  = (MMCMM_W_AC_INFO_CHANGE_IND_STRU*)pRcvMsg;

    /* �����ǰCSע���Ϊ���ޣ���Ҫ�������ý���ǰ״̬ */
    if (NAS_MML_RESTRICTION_UNBAR_TO_BAR == pstAcInfoChangeInd->enCsRestrictRegisterChange)
    {
        if (MM_IDLE_NO_IMSI != g_MmGlobalInfo.ucStaOfRcvXXEstReq)
        {
            g_MmGlobalInfo.ucStaOfRcvXXEstReq       = MM_IDLE_LOCATION_UPDATE_NEEDED;
            g_MmGlobalInfo.ucStaAfterWaitForNwkCmd  = MM_IDLE_LOCATION_UPDATE_NEEDED;
        }
    }

    /* �����ǰCSע���Ϊ�����ޣ���Ҫ�������ý���ǰ״̬ */
    if (NAS_MML_RESTRICTION_BAR_TO_UNBAR == pstAcInfoChangeInd->enCsRestrictRegisterChange)
    {
        NAS_MM_UpdateMmStateCsRegRestrictBarToUnbar();
    }

    if (VOS_TRUE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNtMod))
    {
        /* ����ģʽI���ֻ�ģʽA��PSע������ޱ�Ϊ������ */
        if ((NAS_MML_RESTRICTION_BAR_TO_UNBAR == pstAcInfoChangeInd->enPsRestrictRegisterChange)
         && (MM_TRUE == g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg ))
        {
            g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg = MM_FALSE;
        }
    }

}

#if (FEATURE_ON == FEATURE_LTE)
VOS_VOID Mm_Cell_S3_E89(
    VOS_VOID                           *pRcvMsg
)
{
    VOS_UINT8                           ucPsRestrictionFlg;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrNetRatType;
    VOS_UINT32                          ulT3412ExpNeedRegFlg;

    enCurrNetRatType     = NAS_MML_GetCurrNetRatType();
    ulT3412ExpNeedRegFlg = NAS_MM_IsT3412ExpiredNeedRegist(NAS_MML_GetLteCsServiceCfg(),
                           NAS_MML_GetTinType(), NAS_MML_GetT3412Status());
    ucPsRestrictionFlg   = NAS_MML_GetPsRestrictRegisterFlg();

    /* 3GPP 24.008��4.4.1  Location updating procedure�½��������£�
        The normal location updating procedure shall also be started if the MS is
        configured to use CS fallback and SMS over SGs, or SMS over SGs only,
        and the TIN indicates "RAT-related TMSI",
        - when the periodic tracking area update timer T3412 expires and the
        network operates in network operation mode II or III
    */
    if ((VOS_FALSE == ulT3412ExpNeedRegFlg)
     || (NAS_MML_NET_RAT_TYPE_LTE == enCurrNetRatType))
    {
        return;
    }

    /* ����ģʽI�£����GMM�Ѿ�ע��������ڽ���ע�ᣬ���账�� */
    if ((VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
     && (MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod))
    {
        if (VOS_TRUE == NAS_GMM_IsRegisteredOrRegistering())
        {
            return;
        }
    }

    /* 3GPP 24.008��4.4.1  Location updating procedure�½��������£�
       The normal location updating procedure shall also be started if the MS is
       configured to use CS fallback and SMS over SGs, or SMS over SGs only,
       and the TIN indicates "RAT-related TMSI",
       - when the periodic tracking area update timer T3412 expires and the
       network operates in network operation mode II or III
    */
    if ((VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
     && (MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod)
     && (VOS_FALSE == ucPsRestrictionFlg))
    {
        return;
    }

    g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_PERIODIC_UPDATING;
    Mm_ComLuOnly();

    return;

}


VOS_VOID Mm_Cell_S5_E89(
    VOS_VOID                           *pRcvMsg
)
{
    VOS_UINT8                           ucPsRestrictionFlg;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrNetRatType;
    VOS_UINT32                          ulT3412ExpNeedRegFlg;

    enCurrNetRatType     = NAS_MML_GetCurrNetRatType();
    ulT3412ExpNeedRegFlg = NAS_MM_IsT3412ExpiredNeedRegist(NAS_MML_GetLteCsServiceCfg(),
                           NAS_MML_GetTinType(), NAS_MML_GetT3412Status());
    ucPsRestrictionFlg   = NAS_MML_GetPsRestrictRegisterFlg();

    /* 3GPP 24.008��4.4.1  Location updating procedure�½��������£�
        The normal location updating procedure shall also be started if the MS is
        configured to use CS fallback and SMS over SGs, or SMS over SGs only,
        and the TIN indicates "RAT-related TMSI",
        - when the periodic tracking area update timer T3412 expires and the
        network operates in network operation mode II or III
    */
    if ((VOS_FALSE == ulT3412ExpNeedRegFlg)
     || (NAS_MML_NET_RAT_TYPE_LTE == enCurrNetRatType))
    {
        return;
    }

    if ((VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
     && (MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod)
     && (VOS_FALSE == ucPsRestrictionFlg))
    {
        return;
    }

    g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_PERIODIC_UPDATING;
    Mm_ComLuOnly();
    return;
}

#endif

VOS_VOID Mm_Cell_S1_E65(VOS_VOID *pRcvMsg)
{
    VOS_UINT8                           ucSimCsRegStatus;

    if ( MM_FALSE == Mm_RcvSsEstReq(pRcvMsg) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        /* ��ǰС������ҵ�������򲻴��� */
        if (VOS_TRUE == NAS_MML_GetCsRestrictNormalServiceFlg())
        {
            Mm_SndSsRelInd(g_MmSsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);

            return;
        }

#if (FEATURE_ON == FEATURE_LTE)
        /* �����ǰפ��LTE,��ֱ�ӻظ�SSʧ�� */
        if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
        {
            Mm_SndSsRelInd(g_MmSsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_NOT_SUPPORT_CS_CALL_S1_MODE_ONLY);

            return;
        }
#endif
        /* �����ǰno rf����Ҫ����ҵ������֪ͨmmc�������� */
        ucSimCsRegStatus = NAS_MML_GetSimCsRegStatus();

        if ((VOS_FALSE == NAS_MML_GetRfAvailFlg())
         && (VOS_TRUE == ucSimCsRegStatus))
        {
            NAS_MM_UpdateConnCtrlInfo(MM_CONN_CTRL_SS);
            Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);
            return;
        }

        Mm_SndSsRelInd(g_MmSsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_OUT_OF_COVERAGE);
    }

    return;
}
VOS_VOID Mm_Cell_S25_E65(VOS_VOID  *pRcvMsg)
{

    if ( MM_FALSE == Mm_RcvSsEstReq(pRcvMsg) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
    }
    else
    {
        Mm_SndSsRelInd(g_MmSsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);
    }

    return;
}


/*lint -restore */

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */
