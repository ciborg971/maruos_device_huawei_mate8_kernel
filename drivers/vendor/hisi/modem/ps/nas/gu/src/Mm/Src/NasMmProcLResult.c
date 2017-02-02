/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : NasMmProcLResult.c
  �� �� ��   : ����
  ��    ��   : zhoujun /40661
  ��������   : 2011��03��14��
  ����޸�   :
  ��������   : MM�յ�Lģע�����Ĵ���
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2010��11��12��
    ��    ��   : zhoujun /40661
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/


#include "MM_Inc.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "PsTypeDef.h"
#include  "MmLmmInterface.h"
#include "NasCommDef.h"
#include "MM_Share.h"
#include "NasMmProcLResult.h"
#endif
#include "MM_Ext.h"
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
#define    THIS_FILE_ID        PS_FILE_ID_NAS_MMPROCLRESULT_C

/*lint -save -e958 */

#if   (FEATURE_ON == FEATURE_LTE)
VOS_VOID  NAS_MM_ProcLmmRejCause3( VOS_VOID )
{
    /* MM parameters update status U3 ROAMING NOT ALLOWED*/
    NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_PLMN_NOT_ALLOWED);

    /*delete TMSI, LAI and ciphering key sequence number */
    NAS_MM_DelLaiTmsiCK();

    g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &= ~MM_MS_ID_IMSI_PRESENT;

    /* ���·���״̬ */
    g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;

    /*MM state is MM_IDLE_NO_IMSI*/
    Mm_ComSetMmState(MM_IDLE_NO_IMSI);

    NAS_MML_SetSimCsRegStatus(VOS_FALSE);

}


VOS_VOID  NAS_MM_ProcLmmAttachCause_Handling(
    NAS_LMM_CN_CAUSE_ENUM_UINT8         enRejectCause
)
{
    NAS_MML_MS_3GPP_REL_STRU                               *pstMs3GppRel = VOS_NULL_PTR;
    NAS_LMM_CN_CAUSE_ENUM_UINT8                             enTmpCause;

    pstMs3GppRel = NAS_MML_GetMs3GppRel();
    enTmpCause   = enRejectCause;

    /* ��ǰԭ��ֵ��#35�Ұ汾ΪR10�汾����ԭ��ֵת�����11����Э��3GPP 24.301 */
    if ( (NAS_EMM_CAUSE_REQUESTED_SER_OPTION_NOT_AUTHORIZED_IN_PLMN == enTmpCause)
      && (NAS_MML_3GPP_REL_R9 < pstMs3GppRel->enLteNasRelease) )
    {
        enTmpCause = NAS_EMM_CAUSE_PLMN_NOT_ALLOW;
    }

    switch ( enTmpCause )
    {
        case NAS_EMM_CAUSE_ILLEGAL_UE:
        case NAS_EMM_CAUSE_ILLEGAL_ME:
        case NAS_EMM_CAUSE_EPS_SERV_AND_NON_EPS_SERV_NOT_ALLOW:
            NAS_MM_ProcLmmRejCause3();
            break;

        case NAS_EMM_CAUSE_PLMN_NOT_ALLOW:

            /*handle the MM parameters update status U3 ROAMING NOT ALLOWED*/
            NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_LOCATION_AREA_NOT_ALLOWED);
            /*delete TMSI, LAI and ciphering key sequence numbe*/
            NAS_MM_DelLaiTmsiCK();

            /*reset location update attempt counter*/
            g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = 0;

            /*Ǩ��MM_IDLE_NO_CELL_AVAILABLE*/
            Mm_ComSetMmState(MM_IDLE_NO_CELL_AVAILABLE);

            break;

        default :
            break;
    }

}
VOS_VOID NAS_MM_ProcLmmTauCause_Handling(
    NAS_LMM_CN_CAUSE_ENUM_UINT8         enRejectCause
)
{
    NAS_MML_MS_3GPP_REL_STRU                               *pstMs3GppRel = VOS_NULL_PTR;
    NAS_LMM_CN_CAUSE_ENUM_UINT8                             enTmpCause;

    pstMs3GppRel = NAS_MML_GetMs3GppRel();
    enTmpCause   = enRejectCause;

    /* ��ǰԭ��ֵ��#35�Ұ汾ΪR10�汾����ԭ��ֵת�����11����Э��3GPP 24.301 */
    if ( (NAS_EMM_CAUSE_REQUESTED_SER_OPTION_NOT_AUTHORIZED_IN_PLMN == enTmpCause)
      && (NAS_MML_3GPP_REL_R9 < pstMs3GppRel->enLteNasRelease) )
    {
        enTmpCause = NAS_EMM_CAUSE_PLMN_NOT_ALLOW;
    }

    switch ( enTmpCause )
    {
        case NAS_EMM_CAUSE_ILLEGAL_UE:
        case NAS_EMM_CAUSE_ILLEGAL_ME:
        case NAS_EMM_CAUSE_EPS_SERV_AND_NON_EPS_SERV_NOT_ALLOW:
            NAS_MM_ProcLmmRejCause3();
            break;

        case NAS_EMM_CAUSE_PLMN_NOT_ALLOW:

            /*MM parameters update status U3 ROAMING NOT ALLOWED */
            NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_LOCATION_AREA_NOT_ALLOWED);

            /*delete TMSI, LAI, ciphering key sequence number */
            NAS_MM_DelLaiTmsiCK();

            /*reset the location update attempt counter*/
            g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = 0;

            /*Ǩ��MM_IDLE_NO_CELL_AVAILABLE*/
            Mm_ComSetMmState(MM_IDLE_NO_CELL_AVAILABLE);

            break;

        default :
            break;
    }

}
VOS_VOID  NAS_MM_ProcLmmNwDetachIndCause_Handling(
    NAS_LMM_CN_CAUSE_ENUM_UINT8         enRejectCause
)
{
    switch (enRejectCause)
    {
        /* 3GPP TS 24.301 V9.5.0 (2010-12) 5.5.2.3.2
            #3  (Illegal UE); or
            #6  (Illegal ME);
            The UE shall set the EPS update status to EU3 ROAMING NOT ALLOWED
            (and shall store it according to subclause 5.1.3.3)
            and shall delete any GUTI, last visited registered TAI,
            TAI list and KSI. The UE shall consider the USIM as invalid
            for EPS services until switching off or the UICC containing
            the USIM is removed. The UE shall delete the list of
            equivalent PLMNs and shall enter the state EMM-DEREGISTERED.

            If A/Gb mode or Iu mode is supported by the UE,
            the UE shall handle the MM parameters update status, TMSI,
            LAI and ciphering key sequence number and the GMM parameters
            GMM state, RAI, P-TMSI, P-TMSI signature, GPRS ciphering key
            sequence number and GPRS update status as specified in
            3GPP TS 24.008 [13] for the case when a DETACH REQUEST is
            received with the GMM cause with the same value and with detach
            type set to "re-attach not required". The USIM shall also be
            considered as invalid for non-EPS services until switching off
            or the UICC containing the USIM is removed.

            3GPP TS 24008
            5.5.2.3.2 Network initiated detach procedure completion by the UE
            #3 (Illegal UE); or
            #6 (Illegal ME);
            A GPRS MS operating in MS operation mode A or B shall in addition set the update status to
            U3 ROAMING NOT ALLOWED, shall delete any TMSI, LAI and ciphering key sequence number.
            If the MS is operating in MS operation mode A and an RR connection exists, the MS shall
            abort the RR connection, unless an emergency call is ongoing. The SIM/USIM shall be considered
            as invalid also for non-GPRS services until switching off or the SIM/USIM is removed.
        */

        case NAS_EMM_CAUSE_IMSI_UNKNOWN_IN_HSS:
        case NAS_EMM_CAUSE_ILLEGAL_UE:
        case NAS_EMM_CAUSE_ILLEGAL_ME:
        case NAS_EMM_CAUSE_EPS_SERV_AND_NON_EPS_SERV_NOT_ALLOW:
            NAS_MM_ProcLmmRejCause3();
            break;

        case NAS_EMM_CAUSE_PLMN_NOT_ALLOW:

            /*handle the MM parameters update status U3 ROAMING NOT ALLOWED*/
            NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_LOCATION_AREA_NOT_ALLOWED);

            /*delete TMSI, LAI and ciphering key sequence number*/
            NAS_MM_DelLaiTmsiCK();

            /* ���·���״̬ */
            g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;

            /*MM state is MM_IDLE_NO_CELL_AVAILABLE*/
            Mm_ComSetMmState(MM_IDLE_NO_CELL_AVAILABLE);

            g_MmSubLyrShare.MmShare.ucCsAttachState = MM_STATUS_DETACHED;

            break;

        case NAS_EMM_CAUSE_TA_NOT_ALLOW:
        case NAS_EMM_CAUSE_ROAM_NOT_ALLOW:
        case NAS_EMM_CAUSE_NO_SUITABL_CELL:

            /* ETSI TS 124 301
            5.5.2.3.2 Network initiated detach procedure completion by the UE
            If A/Gb mode or Iu mode is supported by the UE, the UE shall handle the GMM parameters GMM state, RAI,
            P-TMSI, P-TMSI signature, GPRS ciphering key sequence number, GPRS update status and GPRS attach
            attempt counter as specified in 3GPP TS 24.008 [13] for the case when a DETACH REQUEST is received with
            the GMM cause with the same value and with detach type set to "re-attach not required". If the UE is IMSI
            attached for non-EPS services, the UE shall in addition handle the MM parameters update status, TMSI, LAI,
            ciphering key sequence number and location update attempt counter as specified in 3GPP TS 24.008 [13] for the
            case when a DETACH REQUEST is received with the GMM cause with the same value and with detach type set
            to "re-attach not required".

            TS 24008
            4.7.4.2.2   Network initiated GPRS detach procedure completion by the MS
            # 12    (Location area not allowed);
            -   If the MS is IMSI attached, the MS shall set the update status to U3 ROAMING NOT ALLOWED, shall delete
            any TMSI, LAI and ciphering key sequence number and shall reset the location update attempt counter.
            The new MM state is MM IDLE.
            */

            /* ���CSΪ��ע��״̬ */
            if (MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState)
            {
                /* Update Status��ΪNAS_MML_LOCATION_UPDATE_STATUS_LOCATION_AREA_NOT_ALLOWED */
                NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_LOCATION_AREA_NOT_ALLOWED);

                /* ɾ��TMSI, LAI and ciphering key sequence number */
                NAS_MM_DelLaiTmsiCK();

                /* reset location update attempt counter */
                g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = 0;

                /* ���·���״̬ */
                g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;

                /* Ǩ��MM_IDLE_LIMITED_SERVICE */
                Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);

                g_MmSubLyrShare.MmShare.ucCsAttachState = MM_STATUS_DETACHED;
            }
            break;

        case NAS_EMM_CAUSE_EPS_SERV_NOT_ALLOW:
        case NAS_EMM_CAUSE_EPS_SERV_NOT_ALLOW_IN_PLMN:

            /* ETSI TS 124 301
            5.5.2.3.2 Network initiated detach procedure completion by the UE
            #7 (EPS services not allowed);
            A UE operating in CS/PS mode 1 or CS/PS mode 2 of operation is still IMSI attached for non-EPS services in
            the network. The UE operating in CS/PS mode 1 or CS/PS mode 2 of operation shall set the update status to U2
            NOT UPDATED

            #14 (EPS services not allowed in this PLMN)
            A UE operating in CS/PS mode 1 or CS/PS mode 2 of operation is still IMSI attached for non-EPS services and
            shall set the update status to U2 NOT UPDATED.
            */

            /* ���CSΪ��ע��״̬ */
            if (MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState)
            {
                /* Update Status��ΪNAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED */
                NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED);


                /* ɾ��TMSI, LAI CKSN */
                NAS_MM_DelLaiTmsiCK();

                /* ˢ��sim��cs loci 0x6F7E�ļ�����Ӧ���� */
                NAS_MM_WriteLocaInCard();
            }
            break;

        default:

            /* ������ */

            break;
     }

     return;
}


VOS_VOID  NAS_MM_ProcLmmAttachRstInd(
    MMCMM_LMM_ATTACH_IND_STRU          *pstLmmAttachInd
)
{

    NAS_LMM_CN_CAUSE_ENUM_UINT8         enCnCause;

    enCnCause      = NAS_EMM_CAUSE_BUTT;

    if (VOS_TRUE == pstLmmAttachInd->bitOpCnCause)
    {
        enCnCause = pstLmmAttachInd->ucCnCause;
    }

    /* Ǩ��MM_IDLE_NO_CELL_AVAILABLE*/
    Mm_ComSetMmState(MM_IDLE_NO_CELL_AVAILABLE);

    /* PS ONLY ֻҪ����FAIL��� */
    switch (pstLmmAttachInd->ulAttachRslt)
    {
        case MMC_LMM_ATT_RSLT_CN_REJ:
            NAS_MM_ProcLmmAttachCause_Handling(enCnCause);
            break;

        case MMC_LMM_ATT_RSLT_AUTH_REJ:
            NAS_MM_ProcLmmAuthRstInd();
            break;

        case MMC_LMM_ATT_RSLT_SUCCESS:
        case MMC_LMM_ATT_RSLT_ACCESS_BAR:
        case MMC_LMM_ATT_RSLT_TIMER_EXP:
        case MMC_LMM_ATT_RSLT_FORBID_PLMN:
        case MMC_LMM_ATT_RSLT_FORBID_TA_FOR_RPOS:
        case MMC_LMM_ATT_RSLT_FORBID_PLMN_FOR_GPRS:
        case MMC_LMM_ATT_RSLT_FORBID_TA_FOR_ROAMING:
        case MMC_LMM_ATT_RSLT_FAILURE:
        case MMC_LMM_ATT_RSLT_ESM_FAILURE:
        case MMC_LMM_ATT_RSLT_MO_DETACH_FAILURE:
        case MMC_LMM_ATT_RSLT_MT_DETACH_FAILURE:
        case MMC_LMM_ATT_RSLT_T3402_RUNNING:
        case MMC_LMM_ATT_RSLT_PS_ATT_NOT_ALLOW:
            /* ������ */
            break;

        default:

            NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_ProcLmmAttachRstInd: unexpected attach rslt.");
            break;
    }

    return;

}


VOS_VOID  NAS_MM_ProcLmmTauRstInd(
    MMCMM_LMM_TAU_RESULT_IND_STRU      *pstTauInd
)
{
    /* # 3(Illegal MS),
    # 6(Illegal ME),
    If the MS is IMSI attached, the MS shall in addition set the update status
    to U3 ROAMING NOT ALLOWED, shall delete any TMSI, LAI and ciphering key
    sequence number. If the MS is operating in MS operation mode A and an RR
    connection exists, the MS shall abort the RR connection, unless an
    emergency call is ongoing. The SIM/USIM shall be considered as invalid
    also for non-GPRS services until switching off or the SIM/USIM is removed.
    */

    /* # 11(PLMN not allowed),
       # 12(Location area not allowed),
       # 13(Roaming not allowed in this location area),
       # 14(GPRS services not allowed in this PLMN),
       # 15((No Suitable Cells In Location Area)

       If no RR connection exists, the MS shall perform the following additional
       actions immediately. If the MS is operating in MS operation mode A and an
       RR connection exists, the MS shall perform these actions when the RR
       connection is subsequently released:
       -   If the MS is IMSI attached, the MS shall set the update status to
       U3 ROAMING NOT ALLOWED, shall delete any TMSI, LAI and ciphering key
       sequence number and shall reset the location update attempt counter.
       The new MM state is MM IDLE.
   */


    NAS_LMM_CN_CAUSE_ENUM_UINT8         enCnCause;

    enCnCause      = NAS_EMM_CAUSE_BUTT;

    if (VOS_TRUE == pstTauInd->bitOpCnCause)
    {
        enCnCause = pstTauInd->ucCnCause;
    }

    /*Ǩ��MM_IDLE_NO_CELL_AVAILABLE;*/
    Mm_ComSetMmState(MM_IDLE_NO_CELL_AVAILABLE);

    switch (pstTauInd->ulTauRst)
    {
        case MMC_LMM_TAU_RSLT_CN_REJ:
            NAS_MM_ProcLmmTauCause_Handling(enCnCause);
            break;

        case MMC_LMM_TAU_RSLT_AUTH_REJ:
            NAS_MM_ProcLmmAuthRstInd();
            break;

        case MMC_LMM_TAU_RSLT_SUCCESS:
        case MMC_LMM_TAU_RSLT_ACCESS_BARED:
        case MMC_LMM_TAU_RSLT_TIMER_EXP:
        case MMC_LMM_TAU_RSLT_FORBID_PLMN:
        case MMC_LMM_TAU_RSLT_FORBID_TA_FOR_RPOS:
        case MMC_LMM_TAU_RSLT_FORBID_TA_FOR_ROAMING:
        case MMC_LMM_TAU_RSLT_FORBID_PLMN_FOR_GPRS:
        case MMC_LMM_TAU_RSLT_FAILURE:
        case MMC_LMM_TAU_RSLT_MO_DETACH_FAILURE:
        case MMC_LMM_TAU_RSLT_MT_DETACH_FAILURE:
        case MMC_LMM_TAU_RSLT_T3402_RUNNING:
            /* ������ */
            break;

        default:

            NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_ProcLmmTauRstInd: unexpected attach rslt.");
            break;
    }

}


VOS_VOID  NAS_MM_ProcLmmServiceRstInd(
    MMCMM_LMM_SERVICE_RESULT_IND_STRU  *pstLmmServiceInd
)
{
    NAS_LMM_CN_CAUSE_ENUM_UINT8         enCnCause;
    NAS_MML_MS_3GPP_REL_STRU                               *pstMs3GppRel = VOS_NULL_PTR;

    pstMs3GppRel = NAS_MML_GetMs3GppRel();

    enCnCause      = NAS_EMM_CAUSE_BUTT;

    if (MMC_LMM_SERVICE_RSLT_CN_REJ == pstLmmServiceInd->ulServiceRst)
    {
        if (VOS_TRUE == pstLmmServiceInd->bitOpCnCause)
        {
            enCnCause = pstLmmServiceInd->ucCnCause;
        }

        /* ��ǰԭ��ֵ��#35�Ұ汾ΪR10�汾����ԭ��ֵת�����11����Э��3GPP 24.301 */
        if ( (NAS_EMM_CAUSE_REQUESTED_SER_OPTION_NOT_AUTHORIZED_IN_PLMN == enCnCause)
          && (NAS_MML_3GPP_REL_R9 < pstMs3GppRel->enLteNasRelease) )
        {
            enCnCause = NAS_EMM_CAUSE_PLMN_NOT_ALLOW;
        }

        switch (enCnCause)
        {

            /*3GPP TS 24.301 V9.5.0 (2010-12) 5.6.1.5
                #3   (Illegal UE); or
                #6   (Illegal ME);
                The UE shall set the EPS update status to EU3 ROAMING NOT ALLOWED
                (and shall store it according to subclause 5.1.3.3) and shall delete any GUTI,
                last visited registered TAI, TAI list and eKSI. The UE shall consider the USIM
                as invalid for EPS services until switching off or the UICC containing the USIM
                is removed. The UE shall enter the state EMM-DEREGISTERED.

                If A/Gb mode or Iu mode is supported by the UE, the UE shall handle the GMM parameters
                GMM state, GPRS update status, P-TMSI, P-TMSI signature, RAI and GPRS ciphering key sequence number
                and the MM parameters update status, TMSI, LAI and ciphering key sequence number as
                specified in 3GPP TS 24.008 [13] for the case when the service request procedure
                is rejected with the GMM cause with the same value. The USIM shall be considered
                as invalid also for non-EPS services until switching off or the UICC
                containing the USIM is removed.
            */
            case NAS_EMM_CAUSE_ILLEGAL_UE:
            case NAS_EMM_CAUSE_ILLEGAL_ME:
                NAS_MM_ProcLmmRejCause3();
                break;

            case NAS_EMM_CAUSE_EPS_SERV_AND_NON_EPS_SERV_NOT_ALLOW:
                if (NAS_MML_GetLte3gppRelVersion() >= NAS_MML_3GPP_REL_R11)
                {
                    NAS_MM_ProcLmmRejCause3();
                }
                break;

            case NAS_EMM_CAUSE_PLMN_NOT_ALLOW:

                /*set  the MM parameters update statu  U3 ROAMING NOT ALLOWED*/
                NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_LOCATION_AREA_NOT_ALLOWED);

                /*delete TMSI, LAI, ciphering key sequence number*/
                NAS_MM_DelLaiTmsiCK();

                /*24301 set the location update attempt counter*/
                g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = 0;

                /* ���·���״̬ */
                g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;

                /*Ǩ�� MM_IDLE_NO_CELL_AVAILABLE*/
                Mm_ComSetMmState(MM_IDLE_NO_CELL_AVAILABLE);

                break;

            case NAS_EMM_CAUSE_CS_DOMAIN_NOT_AVAILABLE:
                if (NAS_MML_GetLte3gppRelVersion() >= NAS_MML_3GPP_REL_R11)
                {
                    /* Update Status��ΪNAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED */
                    NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED);

                    /* ɾ��TMSI, LAI CKSN */
                    NAS_MM_DelLaiTmsiCK();

                    /* Ǩ��MM_IDLE_NO_CELL_AVAILABLE */
                    Mm_ComSetMmState(MM_IDLE_NO_CELL_AVAILABLE);
                }
                break;

           default:
               break;

        }
    }

    /* ���յ�SERVICE REJʱ������״̬Ǩ�� */

    else if (MMC_LMM_SERVICE_RSLT_AUTH_REJ == pstLmmServiceInd->ulServiceRst)
    {
        NAS_MM_ProcLmmAuthRstInd();
    }
    else
    {
    }

}


VOS_VOID  NAS_MM_ProcLmmAuthRstInd(VOS_VOID)
{
    /*handle the MM parameters update status U3 ROAMING NOT ALLOWED*/
    NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_PLMN_NOT_ALLOWED);

    /*delete TMSI, LAI and ciphering key sequence numbe*/
    NAS_MM_DelLaiTmsiCK();

    g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &= ~MM_MS_ID_IMSI_PRESENT;

    /* ���·���״̬ */
    g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;

    /*Ǩ��MM_IDLE_NO_IMSI*/
    Mm_ComSetMmState(MM_IDLE_NO_IMSI);

    NAS_MML_SetSimCsRegStatus(VOS_FALSE);
}
VOS_VOID  NAS_MM_ConvertLmmPlmnToNasPLMN(
    VOS_UINT8                          *pucLmmPlmn,
    NAS_MML_PLMN_ID_STRU               *pstNasPlmn
)
{
    VOS_UINT32                          ulTempData;
    NAS_MML_PLMN_ID_STRU                stPlmn;

    /*
       PLMN BCD ���� ��ʽ

       MCC digit 2,  MCC digit 1, ----OCTET 1
       MNC digit 3,  MCC digit 3, ----OCTET 2
       MNC digit 2,  MNC digit 1, ----OCTET 3
    */

    ulTempData = NAS_MML_OCTET_LOW_FOUR_BITS & pucLmmPlmn[0];
    stPlmn.ulMcc = ulTempData;
    ulTempData = (NAS_MML_OCTET_HIGH_FOUR_BITS & pucLmmPlmn[0]) >> NAS_MML_OCTET_MOVE_FOUR_BITS;
    stPlmn.ulMcc |= ulTempData << NAS_MML_OCTET_MOVE_EIGHT_BITS;

    ulTempData = NAS_MML_OCTET_LOW_FOUR_BITS & pucLmmPlmn[1];
    stPlmn.ulMcc |= ulTempData << NAS_MML_OCTET_MOVE_SIXTEEN_BITS;
    ulTempData = (NAS_MML_OCTET_HIGH_FOUR_BITS & pucLmmPlmn[1]) >> NAS_MML_OCTET_MOVE_FOUR_BITS;

    stPlmn.ulMnc = ulTempData << NAS_MML_OCTET_MOVE_SIXTEEN_BITS;
    ulTempData = NAS_MML_OCTET_LOW_FOUR_BITS & pucLmmPlmn[2];
    stPlmn.ulMnc |= ulTempData;
    ulTempData = (NAS_MML_OCTET_HIGH_FOUR_BITS & pucLmmPlmn[2]) >> NAS_MML_OCTET_MOVE_FOUR_BITS;
    stPlmn.ulMnc |= ulTempData << NAS_MML_OCTET_MOVE_EIGHT_BITS;

    *pstNasPlmn = stPlmn;

    return;
}


VOS_VOID NAS_MM_ProcLmmRejOtherCause(
    VOS_UINT32                          ulAttemptCounter,
    VOS_UINT32                          ulLmmBitOpAtmpCnt
)
{
    /* ETSI TS 124 301 R11
    5.5.3.3.6 Abnormal cases in the UE

    -   If the tracking area updating attempt counter is less than 5,
    the UE shall set the update status to U2 NOT UPDATED,
    but shall not delete any LAI, TMSI, ciphering key sequence number and list of equivalent PLMNs;
    or
    -   if the tracking area updating attempt counter is equal to 5,
    the UE shall delete any LAI, TMSI, ciphering key sequence number and list of equivalent PLMNs
    and set the update status to U2 NOT UPDATED.

    A UE operating in CS/PS mode 1 of operation shall select GERAN or UTRAN radio access technology
    and proceed with appropriate MM or GMM specific procedures.
    */

    /* ���Դ�����Ч������Ϊ����פ��*/
    if ( VOS_FALSE == ulLmmBitOpAtmpCnt)
    {
        /* ���·���״̬ */
        g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;

        /* Ǩ��MM_IDLE_LIMITED_SERVICE */
        Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);

        return;
    }

    if (ulAttemptCounter < MM_EMM_MAX_ATTEMPT_COUNTER)
    {

        /* Update Status��ΪNAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED */
        NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED);

        /* Ǩ��MM_IDLE_ATTEMPTING_TO_UPDATE:�´�����attach������tauʱ��LMM��֪ͨMM��MM��Ǩ��LOCATION_UPDATING_PENDING */
        Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);
    }
    else
    {
        /* Update Status��ΪNAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED */
        NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED);

        /* ɾ��TMSI, LAI CKSN */
        NAS_MM_DelLaiTmsiCK();

        /* ���·���״̬ */
        g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;

        /* Ǩ��MM_IDLE_ATTEMPTING_TO_UPDATE */
        Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);

        NAS_MM_ProcBufferedCsfbService();
    }

    return;
}


VOS_VOID  NAS_MM_ProcLmmCombinedAttachCause(
    NAS_LMM_CN_CAUSE_ENUM_UINT8         enRejectCause,
    VOS_UINT32                          ulAttemptCounter,
    VOS_UINT32                          ulLmmBitOpAtmpCnt
)
{
    NAS_MML_MS_3GPP_REL_STRU                               *pstMs3GppRel = VOS_NULL_PTR;
    NAS_LMM_CN_CAUSE_ENUM_UINT8                             enTmpCause;

    pstMs3GppRel = NAS_MML_GetMs3GppRel();
    enTmpCause   = enRejectCause;

    /* ��ǰԭ��ֵ��#35�Ұ汾ΪR10�汾����ԭ��ֵת�����11����Э��3GPP 24.301 */
    if ( (NAS_EMM_CAUSE_REQUESTED_SER_OPTION_NOT_AUTHORIZED_IN_PLMN == enTmpCause)
      && (NAS_MML_3GPP_REL_R9 < pstMs3GppRel->enLteNasRelease) )
    {
        enTmpCause = NAS_EMM_CAUSE_PLMN_NOT_ALLOW;
    }

    switch ( enTmpCause )
    {
        case NAS_EMM_CAUSE_ILLEGAL_UE:
        case NAS_EMM_CAUSE_ILLEGAL_ME:
        case NAS_EMM_CAUSE_EPS_SERV_AND_NON_EPS_SERV_NOT_ALLOW:

            /* ETSI TS 124 301
            5.5.1.3.5 Combined attach not accepted by the network
            #3 (Illegal UE);
            #6 (Illegal ME); or
            #8 (EPS services and non-EPS services not allowed);
            If A/Gb mode or Iu mode is supported by the UE, the UE shall in addition handle the MM parameters update
            status, TMSI, LAI and ciphering key sequence number, and the GMM parameters GMM state, GPRS update
            status, P-TMSI, P-TMSI signature, RAI and GPRS ciphering key sequence number as specified in
            3GPP TS 24.008 [13] for the case when the combined attach procedure is rejected with the GMM cause with the
            same value.

            TS 24008
            4.7.3.2.4   Combined GPRS attach not accepted by the network
            # 3     (Illegal MS);
            # 6     (Illegal ME), or
            # 8     (GPRS services and non-GPRS services not allowed);

            The MS shall set the update status to U3 ROAMING NOT ALLOWED, shall delete any TMSI, LAI
            and ciphering key sequence number. The SIM/USIM shall be considered as invalid for GPRS
            and non-GPRS services until switching off or the SIM/USIM is removed.
            */

            /* ����NAS_MM_ProcLmmRejCause3���д��� */
            NAS_MM_ProcLmmRejCause3();
            break;

        case NAS_EMM_CAUSE_EPS_SERV_NOT_ALLOW:
        case NAS_EMM_CAUSE_EPS_SERV_NOT_ALLOW_IN_PLMN:


            /* Update Status��ΪNAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED */
            NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED);

            /* ɾ��TMSI, LAI CKSN */
            NAS_MM_DelLaiTmsiCK();


            break;



        case NAS_EMM_CAUSE_PLMN_NOT_ALLOW:
        case NAS_EMM_CAUSE_TA_NOT_ALLOW:
        case NAS_EMM_CAUSE_ROAM_NOT_ALLOW:
        case NAS_EMM_CAUSE_NO_SUITABL_CELL:

            /* ETSI TS 124 301
            5.5.1.3.5 Combined attach not accepted by the network
            #11 (PLMN not allowed);
            #12 (Tracking area not allowed);
            #13 (Roaming not allowed in this tracking area);
            #15 (No suitable cells in tracking area);
            If A/Gb mode or Iu mode is supported by the UE, the UE shall in addition handle the MM parameters update
            status, TMSI, LAI, ciphering key sequence number and location update attempt counter, and the GMM
            parameters GMM state, GPRS update status, P-TMSI, P-TMSI signature, RAI, GPRS ciphering key sequence
            number and GPRS attach attempt counter as specified in 3GPP TS 24.008 [13] for the case when the combined
            attach procedure is rejected with the GMM cause with the same value and no RR connection exists.

            TS 24008
            4.7.3.2.4   Combined GPRS attach not accepted by the network
            # 11    (PLMN not allowed);
            The MS shall set the update status to U3 ROAMING NOT ALLOWED, reset the location update attempt counter and
            shall delete any TMSI, LAI and ciphering key sequence number. The new MM state is MM IDLE.
            */

            /* Update Status��ΪNAS_MML_LOCATION_UPDATE_STATUS_LOCATION_AREA_NOT_ALLOWED */
            NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_LOCATION_AREA_NOT_ALLOWED);

            /* ɾ��TMSI, LAI and ciphering key sequence number */
            NAS_MM_DelLaiTmsiCK();

            /* reset location update attempt counter */
            g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = 0;

            /* ���·���״̬ */
            g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;

            /* Ǩ��MM_IDLE_LIMITED_SERVICE */
            Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);

            break;

        default :

            NAS_MM_ProcLmmRejOtherCause(ulAttemptCounter, ulLmmBitOpAtmpCnt);

            break;
    }

    return;
}
VOS_VOID  NAS_MM_ProcLmmCombinedTauCause(
    NAS_LMM_CN_CAUSE_ENUM_UINT8         enRejectCause,
    VOS_UINT32                          ulAttemptCounter,
    VOS_UINT32                          ulLmmBitOpAtmpCnt
)
{
    NAS_MML_MS_3GPP_REL_STRU                               *pstMs3GppRel = VOS_NULL_PTR;
    NAS_LMM_CN_CAUSE_ENUM_UINT8                             enTmpCause;

    pstMs3GppRel = NAS_MML_GetMs3GppRel();
    enTmpCause   = enRejectCause;

    /* �汾ΪR10�汾���Ժ�汾����ǰԭ��ֵ��#35��ԭ��ֵת�����#11����Э��3GPP
    24.301 5.5.3.3.5 */
    /* �汾ΪR10�汾���Ժ�汾����ǰԭ��ֵ��#40��ԭ��ֵת�����#10����Э��3GPP
    24.301 5.5.3.3.5 */
    if (NAS_MML_3GPP_REL_R9 < pstMs3GppRel->enLteNasRelease)
    {
        if (NAS_EMM_CAUSE_REQUESTED_SER_OPTION_NOT_AUTHORIZED_IN_PLMN == enTmpCause)
        {
            enTmpCause = NAS_EMM_CAUSE_PLMN_NOT_ALLOW;
        }

    }

    switch ( enTmpCause )
    {
        case NAS_EMM_CAUSE_ILLEGAL_UE:
        case NAS_EMM_CAUSE_ILLEGAL_ME:
        case NAS_EMM_CAUSE_EPS_SERV_AND_NON_EPS_SERV_NOT_ALLOW:

            /* ETSI TS 124 301
            5.5.3.3.5 Combined tracking area updating procedure not accepted by the network
            #3 (Illegal UE);
            #6 (Illegal ME); or
            #8 (EPS services and non-EPS services not allowed);
            If A/Gb mode or Iu mode is supported by the UE, the UE shall handle the MM parameters update status, TMSI,
            LAI and ciphering key sequence number, and the GMM parameters GMM state, GPRS update status, P-TMSI,
            P-TMSI signature, RAI and GPRS ciphering key sequence number as specified in 3GPP TS 24.008 [13] for the
            case when the combined routing area updating procedure is rejected with the GMM cause with the same value.

            TS 24008
            4.7.3.2.4   Combined GPRS attach not accepted by the network
            # 3     (Illegal MS);
            # 6     (Illegal ME), or
            # 8     (GPRS services and non-GPRS services not allowed);

            The MS shall set the GPRS update status to GU3 ROAMING NOT ALLOWED and the update status to U3 ROAMING NOT ALLOWED
            (and shall store it according to subclause 4.1.3.2) and enter the state GMM-DEREGISTERED. Furthermore,
            it shall delete any P-TMSI, P-TMSI signature, TMSI, RAI, LAI, ciphering key sequence number and
            GPRS ciphering key sequence number and shall consider the SIM/USIM as invalid for GPRS and non GPRS services
            until switching off or the SIM/USIM is removed.
            */

            /* ����NAS_MM_ProcLmmRejCause3���д��� */
            NAS_MM_ProcLmmRejCause3();
            break;

        case NAS_EMM_CAUSE_EPS_SERV_NOT_ALLOW:

            /* ETSI TS 124 301
            5.5.3.3.5 Combined tracking area updating procedure not accepted by the network
            #7 (EPS services not allowed);
            A UE in CS/PS mode 1 or CS/PS mode 2 of operation is still IMSI attached for non-EPS services. The UE shall
            set the update status to U2 NOT UPDATED
            */

            /* Update Status��ΪNAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED */
            NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED);

            /* ɾ��TMSI, LAI CKSN */
            NAS_MM_DelLaiTmsiCK();

            /* ˢ��sim��cs loci 0x6F7E�ļ�����Ӧ���� */
            NAS_MM_WriteLocaInCard();

            break;

        case NAS_EMM_CAUSE_MS_ID_CANNOT_BE_DERIVED_BY_NW:
        case NAS_EMM_CAUSE_EPS_IMPLICITLY_DETACHED:
        case NAS_EMM_CAUSE_NO_EPS_BEARER_CONTEXT_ACTIVATED:

            /* ETSI TS 124 301
            5.5.3.3.5 Combined tracking area updating procedure not accepted by the network
            #9 (UE identity cannot be derived by the network);
                The UE shall set the EPS update status to EU2 NOT UPDATED (and shall store it according to subclause 5.1.3.3)
                and shall delete any GUTI, last visited registered TAI, TAI List and eKSI.
                The UE shall delete the list of equivalent PLMNs and enter the state EMM-DEREGISTERED.
                Subsequently, the UE shall automatically initiate the attach procedure.
                If A/Gb mode or Iu mode is supported by the UE, the UE shall in addition handle the GMM parameters GMM state, GPRS update status, P-TMSI, P-TMSI signature, RAI and GPRS ciphering key sequence number
                as specified in 3GPP TS 24.008 [13] for the case when the combined routing area updating procedure is rejected with the GMM cause with the same value.
                A UE in CS/PS mode 1 or CS/PS mode 2 of operation is still IMSI attached for non-EPS services.
                The UE shall set the update status to U2 NOT UPDATED.
            #10 (Implicitly detached);
            #40 (No EPS bearer context activated);
                UE shall delete the list of equivalent PLMNs and deactivate all the EPS bearer contexts locally, if any,
                and shall enter the state EMM-DEREGISTERED.NORMAL-SERVICE. The UE shall then perform the attach procedure.
                If A/Gb mode or Iu mode is supported by the UE, the UE shall in addition handle the GMM state as specified in 3GPP TS 24.008 [13] for the case
                when the combined routing area updating procedure is rejected with the GMM cause value #10 "Implicitly detached".
                A UE in CS/PS mode 1 or CS/PS mode 2 of operation is still IMSI attached for non-EPS services.
                The UE shall set the update status to U2 NOT UPDATED.
            */

            /* Update Status��ΪNAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED */
            NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED);

            /* ɾ��TMSI, LAI CKSN */
            NAS_MM_DelLaiTmsiCK();

            /* ˢ��sim��cs loci 0x6F7E�ļ�����Ӧ���� */
            NAS_MM_WriteLocaInCard();

            break;

        case NAS_EMM_CAUSE_PLMN_NOT_ALLOW:
        case NAS_EMM_CAUSE_TA_NOT_ALLOW:

            /* ETSI TS 124 301
            5.5.3.3.5 Combined tracking area updating procedure not accepted by the network
            #11 (PLMN not allowed);
            #12 (Tracking area not allowed);
            If A/Gb mode or Iu mode is supported by the UE, the UE shall handle the MM parameters update status, TMSI,
            LAI, ciphering key sequence number and the location update attempt counter, and the GMM parameters GMM
            state, GPRS update status, P-TMSI, P-TMSI signature, RAI, GPRS ciphering key sequence number and routing
            area updating attempt counter as specified in 3GPP TS 24.008 [13] for the case when the combined routing area
            updating procedure is rejected with the GMM cause with the same value.

            TS 24008
            4.7.5.2.4   Combined routing area updating not accepted by the network
            # 11    (PLMN not allowed);
            The MS shall set the GPRS update status to GU3 ROAMING NOT ALLOWED and the update status to U3 ROAMING NOT ALLOWED
            (and shall store it according to subclause 4.1.3.2) and enter the state GMM-DEREGISTERED. Furthermore,
            it shall delete any P-TMSI, P-TMSI signature, TMSI, RAI, LAI, ciphering key sequence number GPRS ciphering key sequence
            number, and reset the routing area updating attempt counter and the location update attempt counter.
            */

            /* Update Status��ΪNAS_MML_LOCATION_UPDATE_STATUS_LOCATION_AREA_NOT_ALLOWED */
            NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_LOCATION_AREA_NOT_ALLOWED);

            /* ɾ��TMSI, LAI and ciphering key sequence number */
            NAS_MM_DelLaiTmsiCK();

            /* reset location update attempt counter */
            g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = 0;

            /* ���·���״̬ */
            g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;

            /* Ǩ��MM_IDLE_LIMITED_SERVICE */
            Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);

            break;

        case NAS_EMM_CAUSE_ROAM_NOT_ALLOW:
        case NAS_EMM_CAUSE_NO_SUITABL_CELL:

            /* ETSI TS 124 301
            5.5.3.3.5 Combined tracking area updating procedure not accepted by the network
            #13 (Roaming not allowed in this tracking area);
            #15 (No suitable cells in tracking area);
            If A/Gb mode or Iu mode is supported by the UE, the UE shall handle the MM parameters update status and the
            location update attempt counter, and the GMM parameters GMM state, GPRS update status and routing area
            updating attempt counter as specified in 3GPP TS 24.008 [13] for the case when the combined routing area
            updating procedure is rejected with the GMM cause with the same value.

            TS 24008
            4.7.5.2.4   Combined routing area updating not accepted by the network
            # 13    (Roaming not allowed in this location area)
            The MS shall in addition set the update status to U3 ROAMING NOT ALLOWED and shall reset the location update
            attempt counter. The new MM state is MM IDLE.
            */

            /* Update Status��ΪNAS_MML_LOCATION_UPDATE_STATUS_LOCATION_AREA_NOT_ALLOWED */
            NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_LOCATION_AREA_NOT_ALLOWED);

            /* ˢ��sim��cs loci 0x6F7E�ļ�����Ӧ���� */
            NAS_MM_WriteLocaInCard();

            /* reset location update attempt counter */
            g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = 0;

            /* ���·���״̬ */
            g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;

            /* Ǩ��MM_IDLE_LIMITED_SERVICE */
            Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);

            break;


        case NAS_EMM_CAUSE_EPS_SERV_NOT_ALLOW_IN_PLMN:

            /* ETSI TS 124 301
            5.5.3.3.5 Combined tracking area updating procedure not accepted by the network
            #14 (EPS services not allowed in this PLMN);
            The UE operating in CS/PS mode 1 or CS/PS mode 2 of operation is still IMSI attached for non-EPS services
            and shall set the update status to U2 NOT UPDATED.
            */

            /* Update Status��ΪNAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED */
            NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED);

            /* ɾ��TMSI, LAI CKSN */
            NAS_MM_DelLaiTmsiCK();

            /* ˢ��sim��cs loci 0x6F7E�ļ�����Ӧ���� */
            NAS_MM_WriteLocaInCard();

            break;

        default :

            /* ����NAS_MM_ProcLmmRejOtherCause���д��� */
            NAS_MM_ProcLmmRejOtherCause(ulAttemptCounter,ulLmmBitOpAtmpCnt);

            break;
    }

    return;
}


VOS_VOID NAS_MM_ProcLmmEpsOnlySuccCsRejOtherCause(
    VOS_UINT32                          ulAttemptCounter,
    VOS_UINT32                          ulLmmBitOpAtmpCnt
)
{
    /* 24301
    Other  EMM cause values and the case that no EMM cause IE was received are considered as abnormal cases.
    The combined tracking area updating procedure shall be considered as failed for non-EPS services.
    The behaviour of the UE in those cases is specified in subclause 5.5.3.3.6.
    */

    /* ���Դ�����Ч������Ϊ����פ��*/
    if (VOS_FALSE == ulLmmBitOpAtmpCnt)
    {
        /* ���·���״̬ */
        g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;

        /* Ǩ��MM_IDLE_LIMITED_SERVICE */
        Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);

        return;
    }

    if (ulAttemptCounter < MM_EMM_MAX_ATTEMPT_COUNTER )
    {
        if (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == NAS_MML_GetCsUpdateStatus())
        {
            /* ���·���״̬ */
            g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;

            /* Ǩ��MM_IDLE_NORMAL_SERVICE */
            Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
        }
        else
        {
            /* Update Status��ΪNAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED */
            NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED);

            /* ɾ��TMSI, LAI CKSN */
            NAS_MM_DelLaiTmsiCK();


            /* ���·���״̬ */
            g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;


            /* Ǩ��MM_IDLE_ATTEMPTING_TO_UPDATE */
            Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);

            NAS_MM_ProcBufferedCsfbService();
        }
    }
    else
    {
        /* GCF test LTE case 9.2.1.2.3,T3402��ʱ����TAU REQ(combine ta la updating with IMSI attach,
          Я��TMSI status(����ЧTMSI)),�����ϱ���ƥ�䣬����UE��Я��TMSI status */

        /* ���·���״̬ */
        g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;

        /* Ǩ��MM_IDLE_ATTEMPTING_TO_UPDATE */
        Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);

        NAS_MM_ProcBufferedCsfbService();
    }

    return;
}


VOS_VOID NAS_MM_ProcLmmCombinedAttachOnlyEpsSucc(
    MMCMM_LMM_ATTACH_IND_STRU          *pstLmmCombinedAttachInd
)
{
    VOS_UINT32                          ulAttemptCount;

    ulAttemptCount = 0x0;

    /* �����Ϣ��bitOpCnCauseָʾ��Я��ucCnCause,��ӡ�쳣�󷵻� */
    if (VOS_FALSE == pstLmmCombinedAttachInd->bitOpCnCause)
    {
        NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_ProcLmmCombinedAttachOnlyEpsSucc: there is no cn cause.");

        return;
    }

    if ( VOS_TRUE == pstLmmCombinedAttachInd->bitOpAtmpCnt)
    {
        ulAttemptCount = pstLmmCombinedAttachInd->ulAttemptCount;
    }

    /* ���������·���Detach���ͷֱ��� */
    switch (pstLmmCombinedAttachInd->ucCnCause)
    {
        case NAS_EMM_CAUSE_IMSI_UNKNOWN_IN_HSS:

            /* ETSI TS 124 301:
               5.5.1.3.4.3 Combined attach successful for EPS services only
               #2 (IMSI unknown in HSS)
               The UE shall set the update status to U3 ROAMING NOT ALLOWED and shall delete any TMSI, LAI and ciphering key sequence number.
               The UE shall enter state EMM-REGISTERED.NORMAL-SERVICE. The new MM state is MM IDLE.
               The USIM shall be considered as invalid for non-EPS services until switching off or the UICC containing the USIM is removed.
            */

            /* Update Status��ΪNAS_MML_LOCATION_UPDATE_STATUS_PLMN_NOT_ALLOWED */
            NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_PLMN_NOT_ALLOWED);

            /* ɾ��TMSI, LAI and ciphering key sequence number */
            NAS_MM_DelLaiTmsiCK();

            g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &= ~MM_MS_ID_IMSI_PRESENT;

            /* ���·���״̬ */
            g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;

            /* ״̬��ΪMM_IDLE_NO_IMSI */
            Mm_ComSetMmState(MM_IDLE_NO_IMSI);

            /* ����CS����Ч */
            NAS_MML_SetSimCsRegStatus(VOS_FALSE);

            break;

        case NAS_EMM_CAUSE_MSC_TEMPORARILY_NOT_REACHABLE:
        case NAS_EMM_CAUSE_NETWORKFAILURE:
        case NAS_EMM_CAUSE_CONGESTION:
            if (ulAttemptCount < MM_EMM_MAX_ATTEMPT_COUNTER )
            {
                if (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == NAS_MML_GetCsUpdateStatus())
                {
                    /* ���·���״̬ */
                    g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;

                    /* Ǩ��MM_IDLE_NORMAL_SERVICE */
                    Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
                }
                else
                {
                    /* Update Status��ΪNAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED */
                    NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED);

                    /* ɾ��TMSI, LAI CKSN */
                    NAS_MM_DelLaiTmsiCK();


                    /* ���·���״̬ */
                    g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;


                    /* Ǩ��MM_IDLE_ATTEMPTING_TO_UPDATE */
                    Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);

                    NAS_MM_ProcBufferedCsfbService();
                }
            }
            else
            {

                /* GCF test LTE case 9.2.1.2.3,T3402��ʱ����TAU REQ(combine ta la updating with IMSI attach,
                  Я��TMSI status(����ЧTMSI)),�����ϱ���ƥ�䣬����UE��Я��TMSI status */


                /* ���·���״̬ */
                g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;

                /* Ǩ��MM_IDLE_ATTEMPTING_TO_UPDATE */
                Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);

                NAS_MM_ProcBufferedCsfbService();
            }
            break;

        case NAS_EMM_CAUSE_CS_DOMAIN_NOT_AVAILABLE:

            /* ETSI TS 124 301:
               5.5.1.3.4.3 Combined attach successful for EPS services only
               #18 (CS domain not available)
               The UE shall set the update status to U2 NOT UPDATED.
            */

            /* Update Status��ΪNAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED */
            NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED);

            /* ɾ��TMSI, LAI CKSN */
            NAS_MM_DelLaiTmsiCK();

            /* ˢ��sim��cs loci 0x6F7E�ļ�����Ӧ���� */
            NAS_MM_WriteLocaInCard();

            /* ���·���״̬ */
            g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;

            /* ״̬��ΪMM_IDLE_NO_CELL_AVAILABLE */
            Mm_ComSetMmState(MM_IDLE_NO_CELL_AVAILABLE);

            break;

        default:

            NAS_MM_ProcLmmEpsOnlySuccCsRejOtherCause(ulAttemptCount, pstLmmCombinedAttachInd->bitOpAtmpCnt);

            break;
    }

    return;
}
VOS_VOID NAS_MM_ProcLmmCombinedAttachSucc(
    MMCMM_LMM_ATTACH_IND_STRU          *pstLmmCombinedAttachInd
)
{
    NAS_MML_LAI_STRU                   *pstCsSuccLai = VOS_NULL_PTR;
    VOS_UINT8                          *pucTmsi      = VOS_NULL_PTR;

    pstCsSuccLai    = NAS_MML_GetCsLastSuccLai();
    pucTmsi         = NAS_MML_GetUeIdTmsi();

    /* ETSI TS 124 301:
    5.5.1.3.4.2 Combined attach successful
    The UE, receiving an ATTACH ACCEPT message, stores the received location area identification, stops timer T3410,
    resets the location update attempt counter and sets the update status to U1 UPDATED. If the message contains an IMSI,
    the UE is not allocated any TMSI, and shall delete any TMSI accordingly. If the message contains a TMSI, the UE shall
    use this TMSI as the new temporary identity. The UE shall delete its old TMSI and shall store the new TMSI. If neither
    a TMSI nor an IMSI has been included by the network in the ATTACH ACCEPT message, the old TMSI, if any
    available, shall be kept.
    */

    /* ����CS�����һ��ע��ɹ���LAI��Ϣ */
    if (VOS_TRUE == pstLmmCombinedAttachInd->bitOpLai)
    {
        /* ���浽MML�ϴγɹ�LAIȫ�ֱ����� */
        NAS_MM_ConvertLmmPlmnToNasPLMN(pstLmmCombinedAttachInd->stLai.stPlmnId.aucPlmnId, &(pstCsSuccLai->stPlmnId));

        pstCsSuccLai->aucLac[0] = pstLmmCombinedAttachInd->stLai.stLac.ucLac;
        pstCsSuccLai->aucLac[1] = pstLmmCombinedAttachInd->stLai.stLac.ucLacCnt;

        pstCsSuccLai->ucRac = NAS_MML_RAC_INVALID;


    }

    /* resets the location update attempt counter and sets the update status to U1 UPDATED */
    g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = 0;
    NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_UPDATED);

    /* ��ATTACH ACCEPT��Ϣ�з������µ�TMSI����ˢ��TMSI,������IMSI����ɾ��TMSI */
    if (VOS_TRUE == pstLmmCombinedAttachInd->bitOpMsIdentity)
    {
        /*
        8   7   6   5             4           3   2   1
        Length of mobile identity contents                           octet 1

        Identity digit 1   | odd/even indic | Type of identity       octet 2
        Identity digit p+1 | Identity digit p                        octet 3*

        Type of identity (octet 2)
        Bits
        3 2 1
        0 0 1   IMSI
        0 1 0   IMEI
        0 1 1   IMEISV
        1 0 0   TMSI/P-TMSI/M-TMSI
        1 0 1   TMGI and optional MBMS Session Identity
        0 0 0   No Identity (note 1)

        If the mobile identity is the TMSI/P-TMSI/M-TMSI then bits 5 to 8 of octet 3 are coded as "1111"
        and bit 8 of octet4 is the most significant bit and bit 1 of the last octet the least significant bit.
        The coding of the TMSI/P-TMSI is left open for each administration.
        */

        if (MM_IE_MI_ID_TYPE_IMSI == (pstLmmCombinedAttachInd->stMsIdentity.aucMsIdentity[1] & 0x7))
        {
            /* ����TMSI��Ч */
            g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &= ~MM_MS_ID_TMSI_PRESENT;
            NAS_MML_InitUeIdTmsiInvalid();
        }
        else if (MM_IE_MI_ID_TYPE_TMSI == (pstLmmCombinedAttachInd->stMsIdentity.aucMsIdentity[1] & 0x7))
        {
            /* ����TMSI */
            g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg |= MM_MS_ID_TMSI_PRESENT;

            pucTmsi[0] = pstLmmCombinedAttachInd->stMsIdentity.aucMsIdentity[2];
            pucTmsi[1] = pstLmmCombinedAttachInd->stMsIdentity.aucMsIdentity[3];
            pucTmsi[2] = pstLmmCombinedAttachInd->stMsIdentity.aucMsIdentity[4];
            pucTmsi[3] = pstLmmCombinedAttachInd->stMsIdentity.aucMsIdentity[5];

            g_MmGlobalInfo.MsCsInfo.stPlmnId.ulMcc = pstCsSuccLai->stPlmnId.ulMcc;
            g_MmGlobalInfo.MsCsInfo.stPlmnId.ulMnc = pstCsSuccLai->stPlmnId.ulMnc;
        }
        else
        {
        }
    }

    /* ˢ��sim��cs loci 0x6F7E�ļ�����Ӧ���� */
    NAS_MM_WriteLocaInCard();

    /* ����CS����ע��ȫ�ֱ��� */
    g_MmSubLyrShare.MmShare.ucCsAttachState = MM_STATUS_ATTACHED;

    /* ����Power on����ΪFalse */
    g_MmGlobalInfo.ucPowerOnFlg = MM_FALSE;

    /* ���·���״̬ */
    g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;

    /* Ǩ��״̬��MM_IDLE_NORMAL_SERVICE */
    Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);

    /* ����MM��CC���� */

    NAS_MM_ProcBufferedCsfbService();


    return;
}
VOS_VOID NAS_MM_ProcLmmCombinedAttachFail(
    MMCMM_LMM_ATTACH_IND_STRU          *pstLmmCombinedAttachInd
)
{
    NAS_LMM_CN_CAUSE_ENUM_UINT8         enCnCause;
    VOS_UINT32                          ulAttemptCount;

    enCnCause      = NAS_EMM_CAUSE_BUTT;
    ulAttemptCount = 0x0;

    if (VOS_TRUE == pstLmmCombinedAttachInd->bitOpCnCause)
    {
        if ((VOS_FALSE == pstLmmCombinedAttachInd->bitOpCnRslt)
         || (MMC_LMM_ATT_CN_RSLT_EPS_ONLY != pstLmmCombinedAttachInd->ulCnRslt))
        {
            enCnCause = pstLmmCombinedAttachInd->ucCnCause;
        }
    }

    if ( VOS_TRUE == pstLmmCombinedAttachInd->bitOpAtmpCnt)
    {
        ulAttemptCount = pstLmmCombinedAttachInd->ulAttemptCount;
    }

    switch (pstLmmCombinedAttachInd->ulAttachRslt)
    {
        /* ������ȷ�ܾ� */
        case MMC_LMM_ATT_RSLT_CN_REJ:
            NAS_MM_ProcLmmCombinedAttachCause(enCnCause, ulAttemptCount, pstLmmCombinedAttachInd->bitOpAtmpCnt);
            break;

        /* ��Ȩ���� */
        case MMC_LMM_ATT_RSLT_AUTH_REJ:
            NAS_MM_ProcLmmAuthRstInd();
            break;

        /* ���뱻 Barred */
        case MMC_LMM_ATT_RSLT_ACCESS_BAR:

            /* ���·���״̬ */
            g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;

            /* ״̬Ǩ�Ƶ�MM_IDLE_LOCATION_UPDATE_NEEDED */
            Mm_ComSetMmState(MM_IDLE_LOCATION_UPDATE_NEEDED);

            NAS_MM_ProcBufferedCsfbService();

            break;

        /* ��������Ӧ */
        case MMC_LMM_ATT_RSLT_TIMER_EXP:

            NAS_MM_ProcLmmRejOtherCause(ulAttemptCount,pstLmmCombinedAttachInd->bitOpAtmpCnt);
            break;


        /* ��ֹ��Ϣ������ATTACH */
        case MMC_LMM_ATT_RSLT_FORBID_PLMN:
        case MMC_LMM_ATT_RSLT_FORBID_TA_FOR_RPOS:
        case MMC_LMM_ATT_RSLT_FORBID_PLMN_FOR_GPRS:
        case MMC_LMM_ATT_RSLT_FORBID_TA_FOR_ROAMING:
        case MMC_LMM_ATT_RSLT_PS_ATT_NOT_ALLOW:
        case MMC_LMM_ATT_RSLT_ESM_FAILURE:
        case MMC_LMM_ATT_RSLT_MO_DETACH_FAILURE:
        case MMC_LMM_ATT_RSLT_MT_DETACH_FAILURE:
        case MMC_LMM_ATT_RSLT_T3402_RUNNING:

            /* ���·���״̬ */
            g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;

            /* ״̬Ǩ�Ƶ�MM_IDLE_LIMITED_SERVICE */
            Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);

            break;

        /* ����ATTACHδָ��ԭ���ʧ�� */
        case MMC_LMM_ATT_RSLT_FAILURE:

            NAS_MM_ProcLmmRejOtherCause(ulAttemptCount,pstLmmCombinedAttachInd->bitOpAtmpCnt);

            break;

        default:

            /* �쳣��ӡ */
            NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_ProcLmmCombinedAttachFail: unexpected attach rslt.");
            break;
    }



    return;
}
VOS_VOID NAS_MM_ProcLmmCombinedTauOnlyEpsSucc(
    MMCMM_LMM_TAU_RESULT_IND_STRU      *pstCombinedTauInd
)
{
    VOS_UINT32                          ulAttemptCount;

    ulAttemptCount = 0x0;

    /* �ú���ֻ��ulTauRstΪ�ɹ��ŵ���,�����Ϣ��bitOpCnCauseָʾ��Я��ucCnCause,ulTauRstΪcnrej,��˴�ӡ�쳣�󷵻� */
    if (VOS_FALSE == pstCombinedTauInd->bitOpCnCause)
    {
        NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_ProcLmmCombinedTauOnlyEpsSucc: there is no cn cause.");

        return;
    }

    if ( VOS_TRUE == pstCombinedTauInd->bitOpAtmpCnt)
    {
        ulAttemptCount = pstCombinedTauInd->ulAttemptCount;
    }

    /* ���������·���Detach���ͷֱ��� */
    switch (pstCombinedTauInd->ucCnCause)
    {
        case NAS_EMM_CAUSE_IMSI_UNKNOWN_IN_HSS:

            /*ETSI TS 124 301:
            5.5.3.3.4.3 Combined tracking area updating successful for EPS services only
            #2 (IMSI unknown in HSS)
            The UE shall stop T3430 if still running and shall reset the tracking area updating attempt counter. The UE
            shall set the update status to U3 ROAMING NOT ALLOWED and shall delete any TMSI, LAI and ciphering
            key sequence number. The UE shall enter state EMM-REGISTERED.NORMAL-SERVICE. The new MM
            state is MM IDLE. The USIM shall be considered as invalid for non-EPS services until switching off or the
            UICC containing the USIM is removed.
            */

            /* Update Status��ΪNAS_MML_LOCATION_UPDATE_STATUS_PLMN_NOT_ALLOWED */
            NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_PLMN_NOT_ALLOWED);

            /* ɾ��TMSI, LAI and ciphering key sequence number */
            NAS_MM_DelLaiTmsiCK();

            g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &= ~MM_MS_ID_IMSI_PRESENT;

            /* ���·���״̬ */
            g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;

            /* ״̬��ΪMM_IDLE_NO_IMSI */
            Mm_ComSetMmState(MM_IDLE_NO_IMSI);

            /* ����CS����Ч */
            NAS_MML_SetSimCsRegStatus(VOS_FALSE);

            break;

        case NAS_EMM_CAUSE_MSC_TEMPORARILY_NOT_REACHABLE:
        case NAS_EMM_CAUSE_NETWORKFAILURE:
        case NAS_EMM_CAUSE_CONGESTION:
            if (ulAttemptCount < MM_EMM_MAX_ATTEMPT_COUNTER )
            {
                if (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == NAS_MML_GetCsUpdateStatus())
                {
                    /* ���·���״̬ */
                    g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;

                    /* Ǩ��MM_IDLE_NORMAL_SERVICE */
                    Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
                }
                else
                {
                    /* Update Status��ΪNAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED */
                    NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED);

                    /* ɾ��TMSI, LAI CKSN */
                    NAS_MM_DelLaiTmsiCK();


                    /* ���·���״̬ */
                    g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;


                    /* Ǩ��MM_IDLE_ATTEMPTING_TO_UPDATE */
                    Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);

                    NAS_MM_ProcBufferedCsfbService();
                }
            }
            else
            {

                /* GCF test LTE case 9.2.1.2.3,T3402��ʱ����TAU REQ(combine ta la updating with IMSI attach,
                  Я��TMSI status(����ЧTMSI)),�����ϱ���ƥ�䣬����UE��Я��TMSI status */



                /* ���·���״̬ */
                g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;

                /* Ǩ��MM_IDLE_ATTEMPTING_TO_UPDATE */
                Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);

                NAS_MM_ProcBufferedCsfbService();
            }
            break;

        case NAS_EMM_CAUSE_CS_DOMAIN_NOT_AVAILABLE:

            /*ETSI TS 124 301:
            5.5.3.3.4.3 Combined tracking area updating successful for EPS services only
            #18 (CS domain not available)
            The UE shall set the update status to U2 NOT UPDATED.
            */

            /* Update Status��ΪNAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED */
            NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED);

            /* ɾ��TMSI, LAI CKSN */
            NAS_MM_DelLaiTmsiCK();

            /* ˢ��sim��cs loci 0x6F7E�ļ�����Ӧ���� */
            NAS_MM_WriteLocaInCard();

            /* ���·���״̬ */
            g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;

            /* ״̬��ΪMM_IDLE_NO_CELL_AVAILABLE */
            Mm_ComSetMmState(MM_IDLE_NO_CELL_AVAILABLE);

            break;

        default:

            NAS_MM_ProcLmmEpsOnlySuccCsRejOtherCause(ulAttemptCount, pstCombinedTauInd->bitOpAtmpCnt);

            break;
    }

    return;
}
VOS_VOID NAS_MM_ProcLmmCombinedTauSucc(
    MMCMM_LMM_TAU_RESULT_IND_STRU      *pstCombinedTauInd
)
{
    NAS_MML_LAI_STRU                   *pstCsSuccLai = VOS_NULL_PTR;
    VOS_UINT8                          *pucTmsi      = VOS_NULL_PTR;

    pstCsSuccLai    = NAS_MML_GetCsLastSuccLai();
    pucTmsi         = NAS_MML_GetUeIdTmsi();

    /* ETSI TS 124 301:
    5.5.3.3.4.2 Combined tracking area updating successful
    The UE, receiving a TRACKING AREA UPDATE ACCEPT message, stores the received location area identification,
    resets the location update attempt counter, sets the update status to U1 UPDATED and enters MM state MM IDLE.
    How to handle the old TMSI stored in the UE depends on the mobile identity included in the TRACKING AREA
    UPDATE ACCEPT message.
    - If the TRACKING AREA UPDATE ACCEPT message contains an IMSI, the UE is not allocated any TMSI,
    and shall delete any old TMSI accordingly.
    - If the TRACKING AREA UPDATE ACCEPT message contains a TMSI, the UE shall use this TMSI as new
    temporary identity. The UE shall delete its old TMSI and shall store the new TMSI. In this case, a TRACKING
    AREA UPDATE COMPLETE message is returned to the network to confirm the received TMSI.
    - If neither a TMSI nor an IMSI has been included by the network in the TRACKING AREA UPDATE ACCEPT
    message, the old TMSI, if any is available, shall be kept.
    */

    /* ����CS�����һ��ע��ɹ���LAI��Ϣ */
    if (VOS_TRUE == pstCombinedTauInd->bitOpLai)
    {
        /* ���浽MML�ϴγɹ�LAIȫ�ֱ����� */
        NAS_MM_ConvertLmmPlmnToNasPLMN(pstCombinedTauInd->stLai.stPlmnId.aucPlmnId, &(pstCsSuccLai->stPlmnId));

        pstCsSuccLai->aucLac[0] = pstCombinedTauInd->stLai.stLac.ucLac;
        pstCsSuccLai->aucLac[1] = pstCombinedTauInd->stLai.stLac.ucLacCnt;

        pstCsSuccLai->ucRac = NAS_MML_RAC_INVALID;


    }

    /* resets the location update attempt counter and sets the update status to U1 UPDATED */
    g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = 0;
    NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_UPDATED);

    /* ��ATTACH ACCEPT��Ϣ�з������µ�TMSI����ˢ��TMSI,������IMSI����ɾ��TMSI */
    if (VOS_TRUE == pstCombinedTauInd->bitOpMsIdentity)
    {
        /* �����޸�aucMsIdentity�ĳ���Ϊ9����TLV��ʽ��ΪLV��ʽ */
        /*
        8   7   6   5             4           3   2   1
        Length of mobile identity contents                           octet 1

        Identity digit 1   | odd/even indic | Type of identity       octet 2
        Identity digit p+1 | Identity digit p                        octet 3*

        Type of identity (octet 2)
        Bits
        3 2 1
        0 0 1   IMSI
        0 1 0   IMEI
        0 1 1   IMEISV
        1 0 0   TMSI/P-TMSI/M-TMSI
        1 0 1   TMGI and optional MBMS Session Identity
        0 0 0   No Identity (note 1)

        If the mobile identity is the TMSI/P-TMSI/M-TMSI then bits 5 to 8 of octet 3 are coded as "1111"
        and bit 8 of octet4 is the most significant bit and bit 1 of the last octet the least significant bit.
        The coding of the TMSI/P-TMSI is left open for each administration.
        */

        if (MM_IE_MI_ID_TYPE_IMSI == (pstCombinedTauInd->stMsIdentity.aucMsIdentity[1] & 0x7))
        {
            /* ����TMSI��Ч */
            g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &= ~MM_MS_ID_TMSI_PRESENT;
            NAS_MML_InitUeIdTmsiInvalid();
        }
        else if (MM_IE_MI_ID_TYPE_TMSI == (pstCombinedTauInd->stMsIdentity.aucMsIdentity[1] & 0x7))
        {
            /* ����TMSI */
            g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg |= MM_MS_ID_TMSI_PRESENT;

            pucTmsi[0] = pstCombinedTauInd->stMsIdentity.aucMsIdentity[2];
            pucTmsi[1] = pstCombinedTauInd->stMsIdentity.aucMsIdentity[3];
            pucTmsi[2] = pstCombinedTauInd->stMsIdentity.aucMsIdentity[4];
            pucTmsi[3] = pstCombinedTauInd->stMsIdentity.aucMsIdentity[5];

            g_MmGlobalInfo.MsCsInfo.stPlmnId.ulMcc = pstCsSuccLai->stPlmnId.ulMcc;
            g_MmGlobalInfo.MsCsInfo.stPlmnId.ulMnc = pstCsSuccLai->stPlmnId.ulMnc;
        }
        else
        {
        }
    }

    /* ˢ��sim��cs loci 0x6F7E�ļ�����Ӧ���� */
    NAS_MM_WriteLocaInCard();

    /* ����CS����ע��ȫ�ֱ��� */
    g_MmSubLyrShare.MmShare.ucCsAttachState = MM_STATUS_ATTACHED;

    /* ����Power on����ΪFalse */
    g_MmGlobalInfo.ucPowerOnFlg = MM_FALSE;

    /* ���·���״̬ */
    g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;

    /* Ǩ��״̬��MM_IDLE_NORMAL_SERVICE */
    Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);


    NAS_MM_ProcBufferedCsfbService();


    return;
}
VOS_VOID NAS_MM_ProcLmmCombinedTauFail(
    MMCMM_LMM_TAU_RESULT_IND_STRU      *pstCombinedTauInd
)
{
    NAS_LMM_CN_CAUSE_ENUM_UINT8         enCnCause;
    VOS_UINT32                          ulAttemptCounter;

    enCnCause        = NAS_EMM_CAUSE_BUTT;
    ulAttemptCounter = 0x0;

    if (VOS_TRUE == pstCombinedTauInd->bitOpCnCause)
    {
        if ((VOS_FALSE == pstCombinedTauInd->bitOpCnRst)
         || ((MMC_LMM_TA_UPDATED != pstCombinedTauInd->ulCnRst)
          && (MMC_LMM_TA_UPDATED_ISR_ACTIVATED != pstCombinedTauInd->ulCnRst)))
        {
            enCnCause = pstCombinedTauInd->ucCnCause;
        }
    }

    if (VOS_TRUE == pstCombinedTauInd->bitOpAtmpCnt)
    {
        ulAttemptCounter = pstCombinedTauInd->ulAttemptCount;
    }

    switch (pstCombinedTauInd->ulTauRst)
    {
        /* ������ȷ�ܾ� */
        case MMC_LMM_TAU_RSLT_CN_REJ:

            NAS_MM_ProcLmmCombinedTauCause(enCnCause, ulAttemptCounter, pstCombinedTauInd->bitOpAtmpCnt);
            break;

        /* ��Ȩ���� */
        case MMC_LMM_TAU_RSLT_AUTH_REJ:

            NAS_MM_ProcLmmAuthRstInd();
            break;

        /* ���뱻 Barred */
        case MMC_LMM_TAU_RSLT_ACCESS_BARED:

            /* ���·���״̬ */
            g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;

            /* ״̬Ǩ�Ƶ�MM_IDLE_LOCATION_UPDATE_NEEDED */
            Mm_ComSetMmState(MM_IDLE_LOCATION_UPDATE_NEEDED);

            NAS_MM_ProcBufferedCsfbService();

            break;

        /* ��������Ӧ */
        case MMC_LMM_TAU_RSLT_TIMER_EXP:

            NAS_MM_ProcLmmRejOtherCause(ulAttemptCounter,pstCombinedTauInd->bitOpAtmpCnt);

            break;

        /* ��ֹ��Ϣ������ATTACH */
        case MMC_LMM_TAU_RSLT_FORBID_PLMN:
        case MMC_LMM_TAU_RSLT_FORBID_TA_FOR_RPOS:
        case MMC_LMM_TAU_RSLT_FORBID_PLMN_FOR_GPRS:
        case MMC_LMM_TAU_RSLT_FORBID_TA_FOR_ROAMING:
        case MMC_LMM_TAU_RSLT_MO_DETACH_FAILURE:
        case MMC_LMM_TAU_RSLT_MT_DETACH_FAILURE:
        case MMC_LMM_TAU_RSLT_T3402_RUNNING:

            /* ���·���״̬ */
            g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;

            /* ״̬Ǩ�Ƶ�MM_IDLE_LIMITED_SERVICE */
            Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);

            break;

        /* ����ATTACHδָ��ԭ���ʧ�� */
        case MMC_LMM_TAU_RSLT_FAILURE:

            NAS_MM_ProcLmmRejOtherCause(ulAttemptCounter,pstCombinedTauInd->bitOpAtmpCnt);

            break;

        default:

            /* �쳣��ӡ */
            NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_ProcLmmCombinedTauFail: unexpected attach rslt.");
            break;
    }

    return;
}
VOS_VOID NAS_MM_ProcLmmCombinedTauInd(
    MMCMM_LMM_TAU_RESULT_IND_STRU      *pstCombinedTauInd
)
{
    /* ���bitOpCnRsltָʾ��Я��������Ӧ�Ľ��ulCnRslt, ��ʾ�����������
       1)����TAU������ܾ�����ʧ��
       2)��ǰ���յ�ϵͳ��Ϣ����Ҫ����TAU���߲��ܷ���TAU,LMMֱ�ӻظ���TAU��� */
    if (VOS_FALSE == pstCombinedTauInd->bitOpCnRst)
    {
        if (MMC_LMM_TAU_RSLT_SUCCESS == pstCombinedTauInd->ulTauRst)
        {
            /* ���·���״̬ */
            g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;

            /* Ǩ��״̬��MM_IDLE_NORMAL_SERVICE */
            Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);

            /* L���յ�ϵͳ��Ϣ������ע������,�����̳ɹ�ʱ��Ҫ����MM��CC���� */

            NAS_MM_ProcBufferedCsfbService();

        }
        else
        {
            /* ����TAUʧ�� */
            NAS_MM_ProcLmmCombinedTauFail(pstCombinedTauInd);
        }

        return;
    }



    /* ���������TAU��EPS�ɹ� */
    if ((MMC_LMM_TA_UPDATED == pstCombinedTauInd->ulCnRst)
     || (MMC_LMM_TA_UPDATED_ISR_ACTIVATED == pstCombinedTauInd->ulCnRst))
    {
        /* ���TauRsltΪ�ɹ� */
        if (MMC_LMM_TAU_RSLT_SUCCESS == pstCombinedTauInd->ulTauRst)
        {
            /* ������tau eps only�ɹ���cs���ܴ�ԭ��ֵ����������������mm״̬ */
            if (MMC_LMM_CS_PS_PERIODIC_UPDATING != pstCombinedTauInd->ulReqType)
            {
                /* ����EPS�ɹ���������Я����causeΪ#2��#18��#16��#17��#22 */
                NAS_MM_ProcLmmCombinedTauOnlyEpsSucc(pstCombinedTauInd);
            }
        }
        else
        {
            /* ������Ӧ�Ľ��������ԭ�������ԭ��,��ʱ��������ע��ʧ�ܴ��� */
            NAS_MM_ProcLmmCombinedTauFail(pstCombinedTauInd);
        }
    }
    else if ((MMC_LMM_COMBINED_TA_LA_UPDATED == pstCombinedTauInd->ulCnRst)
          || (MMC_LMM_COMBINED_TA_LA_UPDATED_ISR_ACTIVATED == pstCombinedTauInd->ulCnRst))
    {
        /* ���������TAU�ɹ� */
        if (MMC_LMM_TAU_RSLT_SUCCESS == pstCombinedTauInd->ulTauRst)
        {
            NAS_MM_ProcLmmCombinedTauSucc(pstCombinedTauInd);
        }
        else
        {
            /* ����TAUʧ�� */
            NAS_MM_ProcLmmCombinedTauFail(pstCombinedTauInd);
        }
    }
    else
    {
        /* �쳣��ӡ */
        NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_ProcLmmCombinedTauInd: request COMBINED_EPS_IMSI tau, unexpected cn rslt.");
    }

    return;
}
VOS_UINT8 NAS_MM_RcvLmmAttachInd(
    struct MsgCB                       *pstMsg
)
{
    MMCMM_LMM_ATTACH_IND_STRU          *pstLmmAttachInd = VOS_NULL_PTR;

    pstLmmAttachInd = (MMCMM_LMM_ATTACH_IND_STRU *)pstMsg;

    /* ����ǵ���EPSע�� */
    if (MMC_LMM_ATT_TYPE_EPS_ONLY == pstLmmAttachInd->ulReqType)
    {
        NAS_MM_ProcLmmAttachRstInd(pstLmmAttachInd);
    }
    else if (MMC_LMM_ATT_TYPE_COMBINED_EPS_IMSI == pstLmmAttachInd->ulReqType)
    {
        /* ���bitOpCnRsltָʾ��Я��������Ӧ�Ľ��ulCnRslt,��ʾ
           1)����Attach������ܾ�����ʧ��
           2)��ǰδע����ҽ��յ�ϵͳ��Ϣ����Ҫ����ע����߲��ܷ���ע��,LMMֱ�ӻظ���Attach��� */
        if (VOS_FALSE == pstLmmAttachInd->bitOpCnRslt)
        {
            NAS_MM_ProcLmmCombinedAttachFail(pstLmmAttachInd);


            /* �ظ�MMCMM_ATTACH_CNF�Ĳ���,����ȴ�ATTACH�����־λ */
            if (MM_WAIT_CS_ATTACH == (g_MmGlobalInfo.stAttachInfo.enAttachType
                                    & MM_WAIT_CS_ATTACH))
            {
                NAS_MM_SndMmcAttachCnf();
            }

            g_MmGlobalInfo.stAttachInfo.enAttachType = MM_WAIT_NULL_ATTACH;

            return MM_EVENT_ID_INVALID;
        }


        /* ���������Ӧ�Ľ��������ע���EPS�ɹ� */
        if (MMC_LMM_ATT_CN_RSLT_EPS_ONLY == pstLmmAttachInd->ulCnRslt)
        {
            /* ���AttachRsltΪ�ɹ� */
            if (MMC_LMM_ATT_RSLT_SUCCESS == pstLmmAttachInd->ulAttachRslt)
            {
                /* ����EPS�ɹ���������Я����causeΪ#2��#18��#16��#17��#22 */
                NAS_MM_ProcLmmCombinedAttachOnlyEpsSucc(pstLmmAttachInd);
            }
            else
            {
                /* ������Ӧ�Ľ��������ԭ�������ԭ��,��ʱ��������ע��ʧ�ܴ��� */
                NAS_MM_ProcLmmCombinedAttachFail(pstLmmAttachInd);
            }
        }
        else if (MMC_LMM_ATT_CN_RSLT_COMBINED_EPS_IMSI == pstLmmAttachInd->ulCnRslt)
        {
            /* ���������Ӧ�Ľ��������ע��ɹ� */
            if (MMC_LMM_ATT_RSLT_SUCCESS == pstLmmAttachInd->ulAttachRslt)
            {
                NAS_MM_ProcLmmCombinedAttachSucc(pstLmmAttachInd);
            }
            else
            {
                /* ������Ӧ�Ľ��������ע��ʧ�� */
                NAS_MM_ProcLmmCombinedAttachFail(pstLmmAttachInd);
            }
        }
        else
        {
            /* �쳣��ӡ */
            NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_RcvLmmAttachInd: request COMBINED_EPS_IMSI attach, unexpected cn rslt.");
        }
    }
    else
    {
        /* �쳣��ӡ */
        NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_RcvLmmAttachInd: unexpected request attach type.");
    }


    /* �ظ�MMCMM_ATTACH_CNF�Ĳ���,����ȴ�ATTACH�����־λ */
    if (MM_WAIT_CS_ATTACH == (g_MmGlobalInfo.stAttachInfo.enAttachType
                            & MM_WAIT_CS_ATTACH))
    {
        NAS_MM_SndMmcAttachCnf();
    }

    g_MmGlobalInfo.stAttachInfo.enAttachType = MM_WAIT_NULL_ATTACH;

    return MM_EVENT_ID_INVALID;
}


VOS_UINT8 NAS_MM_RcvLmmTauInd(
    struct MsgCB                       *pstMsg
)
{
    MMCMM_LMM_TAU_RESULT_IND_STRU      *pstLmmTauInd = VOS_NULL_PTR;

    pstLmmTauInd = (MMCMM_LMM_TAU_RESULT_IND_STRU *)pstMsg;

    switch (pstLmmTauInd->ulReqType)
    {
        case MMC_LMM_TA_UPDATING:
        case MMC_LMM_PS_PERIODIC_UPDATING:

            /* ����EPS���� */
            NAS_MM_ProcLmmTauRstInd(pstLmmTauInd);
            break;

        case MMC_LMM_COMBINED_TA_LA_UPDATING:
        case MMC_LMM_COMBINED_TA_LA_WITH_IMSI:
        case MMC_LMM_CS_PS_PERIODIC_UPDATING:

            /* ����NAS_MM_ProcLmmCombinedTauInd��������TAU */
            NAS_MM_ProcLmmCombinedTauInd(pstLmmTauInd);
            break;

        default:

            /* �쳣��ӡ */
            NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_RcvLmmTauInd: unexpected request tau type.");
            break;
    }

    return MM_EVENT_ID_INVALID;
}
VOS_UINT8 NAS_MM_RcvLmmMTDetachInd(
    struct MsgCB                       *pstMsg
)
{
    MMCMM_LMM_MT_DETACH_IND_STRU       *pstLmmDetachInd = VOS_NULL_PTR;

    pstLmmDetachInd = (MMCMM_LMM_MT_DETACH_IND_STRU *)pstMsg;

    if (MMC_LMM_DETACH_LOCAL == pstLmmDetachInd->ulDetachType)
    {
        /* �������� */
        if (NAS_MML_MS_MODE_PS_CS == NAS_MML_GetMsMode())
        {
            Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
        }
        return MM_EVENT_ID_INVALID;
    }

    /* ���bitOpCnReqTypeָʾ��Я�������·���Detach����,��ӡ�쳣�󷵻� */
    if (VOS_FALSE == pstLmmDetachInd->bitOpCnReqType)
    {
        NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_RcvLmmMTDetachInd: detach type is MMC_LMM_DETACH_MT, but have no cn req type.");

        return MM_EVENT_ID_INVALID;
    }

    /* ���������·���Detach���ͷֱ��� */
    switch (pstLmmDetachInd->ulCnReqType)
    {
        case MMC_LMM_MT_DET_REATTACH_NOT_REQUIRED:

            /* ETSI TS 124 301
            5.5.2.3.2 Network initiated detach procedure completion by the UE
            If the UE is attached for EPS and non-EPS services, then the UE shall set the update status to U2 NOT UPDATED if:
            - the Detach type IE indicates "re-attach required"; or
            - the Detach type IE indicates "re-attach not required" and no EMM cause IE is included.
            */

            if ((MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState)
             && (VOS_FALSE == pstLmmDetachInd->bitOpCnCause))
            {
                /* Update Status��ΪNAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED */
                NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED);

                /* ɾ��TMSI, LAI CKSN */
                NAS_MM_DelLaiTmsiCK();

                /* ˢ��sim��cs loci 0x6F7E�ļ�����Ӧ���� */
                NAS_MM_WriteLocaInCard();
            }

            if (VOS_TRUE == pstLmmDetachInd->bitOpCnCause)
            {
                /* ����NAS_MM_ProcLmmNwDetachIndCause_Handling */
                NAS_MM_ProcLmmNwDetachIndCause_Handling(pstLmmDetachInd->ucCnCause);
            }
            break;

        case MMC_LMM_MT_DET_REATTACH_REQUIRED:

            /* ETSI TS 124 301
            5.5.2.3.2 Network initiated detach procedure completion by the UE
            If the UE is attached for EPS and non-EPS services, then the UE shall set the update status to U2 NOT UPDATED if:
            - the Detach type IE indicates "re-attach required"; or
            - the Detach type IE indicates "re-attach not required" and no EMM cause IE is included.

            If the detach type indicates "IMSI detach" or "re-attach required", then the UE shall ignore the EMM cause IE if
            received.
            */

            if (MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState)
            {
                /* Update Status��ΪNAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED */
                NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED);

                /* ɾ��TMSI, LAI CKSN */
                NAS_MM_DelLaiTmsiCK();

                /* ˢ��sim��cs loci 0x6F7E�ļ�����Ӧ���� */
                NAS_MM_WriteLocaInCard();
            }
            break;

        case MMC_LMM_MT_DET_IMSI:

            /* ETSI TS 124 301
            5.5.2.3.2 Network initiated detach procedure completion by the UE
            When receiving the DETACH REQUEST message and the detach type indicates "IMSI detach", the UE shall not
            deactivate the EPS bearer context(s) including the default EPS bearer context. The UE shall set the MM update status to
            U2 NOT UPDATED. A UE may send a DETACH ACCEPT message to the network, and shall re-attach to non-EPS
            services by performing the combined tracking area updating procedure according to subclause 5.5.3.3, sending a
            TRACKING AREA UPDATE REQUEST message with EPS update type IE indicating "combined TA/LA updating
            with IMSI attach".

            If the detach type indicates "IMSI detach" or "re-attach required", then the UE shall ignore the EMM cause IE if
            received.
            */

            /* Update Status��ΪNAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED */
            NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED);

            /* ɾ��TMSI, LAI CKSN */
            NAS_MM_DelLaiTmsiCK();

            /* ˢ��sim��cs loci 0x6F7E�ļ�����Ӧ���� */
            NAS_MM_WriteLocaInCard();

            /* ����CS��ע��ȫ�ֱ���Ϊδע�� */
            g_MmSubLyrShare.MmShare.ucCsAttachState = MM_STATUS_DETACHED;

            break;

        default:

            /* �쳣��ӡ */
            NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_RcvLmmMTDetachInd: detach type is MMC_LMM_DETACH_MT, unexpected cn req type.");
            break;
    }

    return MM_EVENT_ID_INVALID;
}
VOS_UINT8 NAS_MM_RcvLmmMoDetachInd(
    struct MsgCB                       *pstMsg
)
{
    MMCMM_LMM_MO_DETACH_IND_STRU       *pstLmmDetachInd = VOS_NULL_PTR;

    pstLmmDetachInd = (MMCMM_LMM_MO_DETACH_IND_STRU *)pstMsg;

    switch (pstLmmDetachInd->ulDetachRslt)
    {
        case  MMC_LMM_DETACH_RSLT_SUCCESS:

            /* ����CS��ע��ȫ�ֱ���Ϊδע�� */
            g_MmSubLyrShare.MmShare.ucCsAttachState = MM_STATUS_DETACHED;

            /* ���·���״̬ */
            g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;

            /* Ǩ��״̬��MM_IDLE_NO_CELL_AVAILABLE */
            Mm_ComSetMmState(MM_IDLE_NO_CELL_AVAILABLE);

            break;

        case  MMC_LMM_DETACH_RSLT_AUTH_REJ:

            NAS_MM_ProcLmmAuthRstInd();

            break;

        default:

            /* �쳣��ӡ */
            NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_RcvLmmMoDetachInd: , unexpected detach result!");

            break;
    }

    return MM_EVENT_ID_INVALID;
}


VOS_UINT8 NAS_MM_RcvLmmServiceRsltInd(
    struct MsgCB                       *pstMsg
)
{
    MMCMM_LMM_SERVICE_RESULT_IND_STRU  *pstLmmServiceInd = VOS_NULL_PTR;

    pstLmmServiceInd = (MMCMM_LMM_SERVICE_RESULT_IND_STRU *)pstMsg;

    NAS_MM_RecordErrorLogInfo(NAS_ERR_LOG_BASE_STATE_TRAG_NW_SEARCH_FOR_RCV_LMM_SRV_RST,
                              pstLmmServiceInd->ulServiceRst);


    NAS_MM_ProcLmmServiceRstInd(pstLmmServiceInd);

    return MM_EVENT_ID_INVALID;

}


VOS_UINT8 NAS_MM_RcvLmmSysInfoInd(
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           aucTimerId[3];

    VOS_UINT32                          ulEmergencyCallFlg;
    MMC_MM_LTE_SYS_INFO_IND_STRU       *pstLmmSysInfo = VOS_NULL_PTR;
    ulEmergencyCallFlg = MM_CS_SERV_NONE_EXIST;



    g_MmGlobalInfo.ucLikeB = MM_FALSE;

    g_MmGlobalInfo.enPreRatType = NAS_MML_NET_RAT_TYPE_LTE;

    /* ��L�·���CSFBʱ������δ��GU��ʱ���յ�L��ϵͳ��Ϣ���������CSFB���� */

    pstLmmSysInfo = (MMC_MM_LTE_SYS_INFO_IND_STRU*)pstMsg;

    aucTimerId[0] = MM_TIMER_T3211;
    aucTimerId[1] = MM_TIMER_T3212;
    aucTimerId[2] = MM_TIMER_T3213;


    /* ���С��״̬Ϊnormal,LMM����ᷢ��ע�ᣬֹͣ���еĶ�ʱ��
       ���С��״̬Ϊanycell,LMM���治�ᷢ��ע�ᣬ����ҪͣT3211/T3212/T3213����������ٻص�GU,���ܻ����һ��LAU */
    if (MMC_LMM_CELL_STATUS_NORMAL == pstLmmSysInfo->stLteSysInfo.enCellStatusInd)
    {
        g_MmGlobalInfo.LuInfo.ucT3213AttmptCnt = 0;
        if (VOS_FALSE == NAS_MML_IsPlmnSupportDam(NAS_MML_GetCurrCampPlmnId()))
        {
            /* ֹͣ����CSFB MT������ʱ�������������ʱ�� */
            aucTimerId[0] = MM_TIMER_PROTECT_MT_CSFB_PAGING_PROCEDURE;
            NAS_MM_TimerStopExceptSpecialTimers(1, aucTimerId);
        }
        else
        {
            /* ֹͣ����T3212�����������ʱ�� */
            aucTimerId[0] = MM_TIMER_T3212;
            NAS_MM_TimerStopExceptSpecialTimers(1, aucTimerId);
        }
    }
    else
    {
        NAS_MM_TimerStopExceptSpecialTimers(3, aucTimerId);
    }

    /* ��¼״̬ΪCSFB MT���յ�LTE��ϵͳ��Ϣ */
    NAS_MM_RecordErrorLogInfo(NAS_ERR_LOG_BASE_STATE_LTE_SYS_INFO_RECEIVED,
                              NAS_MML_REG_FAIL_CAUSE_NULL);

    /* PS ONLY��ʾ��֧������ע�� */
    if (VOS_FALSE == NAS_MML_GetCsAttachAllowFlg())
    {
        /* CS��֧�֣�������� */
        Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_NOT_SUPPORT_CS_CALL_S1_MODE_ONLY);

        MM_RelMsgBuf();

        if (VOS_FALSE == NAS_MML_GetSimCsRegStatus())
        {
            g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;

            /* ״̬Ǩ�Ƶ�MM_IDLE_NO_IMSI */
            Mm_ComSetMmState(MM_IDLE_NO_IMSI);

            return MM_EVENT_ID_INVALID;
        }

        g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;

        /* ״̬Ǩ�Ƶ�MM_IDLE_NO_CELL_AVAILABLE */
        Mm_ComSetMmState(MM_IDLE_NO_CELL_AVAILABLE);


        return MM_EVENT_ID_INVALID;
    }

    if (MM_IDLE_PLMN_SEARCH == g_MmGlobalInfo.ucState)
    {
        /* ���֧��CSFB �����ǽ�������*/
        ulEmergencyCallFlg = Mm_ComJudgeCsServExist();

        if ((NAS_MML_LTE_SUPPORT_CSFB_AND_SMS_OVER_SGS == NAS_MML_GetLteCsServiceCfg())
         || (MM_CS_SERV_EMERGENCY_CALL_EXIST == ulEmergencyCallFlg))
        {
            /* �����CC SS�Ļ��� */
            if ( MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg )
            {
                Mm_SndSmsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulTransactionId,
                                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_OUT_OF_COVERAGE);

                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg = MM_FALSE;
            }

            NAS_MM_UpdateCsServiceBufferStatusFlg();

            NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

            NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

            NAS_MML_SetRelCauseCsfbHighPrioFlg(VOS_FALSE);

            /* ������ǽ������У�����csfb���̣�����ע�� */
            if ((MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucEstingCallTypeFlg)
             && (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg))
            {
                NAS_MM_RcvCcEstReq_CSFB();
            }
            else
            {
                /* IDLE PLMN SERACH״̬�յ�LMM��ϵͳ��Ϣ���ϴ�����ָʾCSFB֧�֣����λ�δ����ע�ᣬ�ظ�CS����ʱ�޷��� */
                Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_OUT_OF_COVERAGE);
            }
        }
        else
        {
            /* IDLE PLMN SERACH״̬�յ�LMM��ϵͳ��Ϣ������ָʾCSFB��֧�� */
            Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_NOT_SUPPORT_CS_CALL_S1_MODE_ONLY);
        }

        MM_RelMsgBuf();

        if (VOS_FALSE == NAS_MML_GetSimCsRegStatus())
        {
            /* ״̬Ǩ�Ƶ�MM_IDLE_NO_IMSI */
            Mm_ComSetMmState(MM_IDLE_NO_IMSI);
            return MM_EVENT_ID_INVALID;
        }

        /* ״̬Ǩ�Ƶ�LOCATION_UPDATING_PENDING,�ȴ�LMM��ע���� */
        Mm_ComSetMmState(LOCATION_UPDATING_PENDING);
    }

    return MM_EVENT_ID_INVALID;

}


VOS_UINT8 NAS_MM_RcvLmmCombinedStartNotifyReq(
    VOS_VOID                           *pstMsg
)
{
    LMM_MM_COMBINED_START_NOTIFY_REQ_STRU                   *pstCombinedNotifyReqMsg;

    pstCombinedNotifyReqMsg = (LMM_MM_COMBINED_START_NOTIFY_REQ_STRU *)pstMsg;

    if ((MM_LMM_COMBINED_ATTACH == pstCombinedNotifyReqMsg->enCombinedType)
     || (MM_LMM_COMBINED_TAU == pstCombinedNotifyReqMsg->enCombinedType))
    {
        /* MM�յ���״̬תΪMM LOCATION UPDATING PENDING */
        Mm_ComSetMmState(LOCATION_UPDATING_PENDING);
    }

    if (MM_LMM_COMBINED_DETACH == pstCombinedNotifyReqMsg->enCombinedType)
    {
        /* MM�յ���״̬תΪMM IMSI DETACH PENDING */
        Mm_ComSetMmState(IMSI_DETACH_PENDING);

    }

    return MM_EVENT_ID_INVALID;
}


VOS_UINT8 NAS_MM_RcvLmmCsfbServiceEndInd(
    VOS_VOID                           *pstMsg
)
{
    NAS_MML_CSFB_SERVICE_STATUS_ENUM_UINT8                  enCsfbServiceStatus;
    LMM_MM_CSFB_SERVICE_END_IND_STRU                       *pstCsfbEndInd   = VOS_NULL_PTR;
    NAS_MMCM_REL_CAUSE_ENUM_UINT32                          enRelCause;

    enCsfbServiceStatus  = NAS_MML_GetCsfbServiceStatus();
    pstCsfbEndInd        = (LMM_MM_CSFB_SERVICE_END_IND_STRU *)pstMsg;
    enRelCause           = NAS_MM_ConvertCsfbSrvRsltToMmCcRelCause(pstCsfbEndInd);

    NAS_MM_RecordErrorLogInfo(NAS_ERR_LOG_BASE_STATE_END_IND_RECEIVED,
                              enRelCause);

#if (FEATURE_ON == FEATURE_PTM)
    /* ��¼CSFB MT�쳣 */
    NAS_MM_CsfbMtFailRecord();
#endif

    /* ��ϵͳ�ػ�LTE������ΪCSFB���̽��� */
    NAS_MM_EndCsfbFlow(enCsfbServiceStatus, enRelCause);

    return MM_EVENT_ID_INVALID;
}


VOS_UINT8 NAS_MM_RcvLmmCsPagingInd(
    VOS_VOID                           *pstMsg
)
{
    LMM_MM_CSFB_SERVICE_PAGING_IND_STRU *pstCsfbPaingIndMsg = VOS_NULL_PTR;

    pstCsfbPaingIndMsg = (LMM_MM_CSFB_SERVICE_PAGING_IND_STRU *)pstMsg;

    /* IMS�绰ʱ������cs���paging ind */
    if (VOS_TRUE   == NAS_MML_GetImsCallFlg())
    {
        return MM_EVENT_ID_INVALID;
    }

    if (LMM_MM_PAGING_IND_UE_ID_TMSI == pstCsfbPaingIndMsg->enPagingUeId)
    {
        g_MmGlobalInfo.ucPagingRecordTypeId = MM_TMSI_PAGING;
    }
    else if (LMM_MM_PAGING_IND_UE_ID_S_TMSI == pstCsfbPaingIndMsg->enPagingUeId)
    {
        g_MmGlobalInfo.ucPagingRecordTypeId = MM_STMSI_PAGING;
    }
    else
    {
        g_MmGlobalInfo.ucPagingRecordTypeId = MM_IMSI_PAGING;
    }


    NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_MT_EXIST);

    NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_MT_EXIST);

    /* ��L����CSFB���̿�ʼ����,CSFB�Ƿ���Է�����ж���LMM���������������,
       L��ظ�LMM_MM_CSFB_SERVICE_END_IND */
    NAS_MM_SndLmmCsfbServiceStartNotify();

    Mm_TimerStart(MM_TIMER_PROTECT_MT_CSFB_PAGING_PROCEDURE);

    NAS_MML_SetCsfbMtPagingTimerStatus(NAS_MML_MT_CSFB_PAGING_TIMER_RUNNING);

    NAS_MM_ClearErrorLogInfo();

    NAS_MM_RecordErrorLogInfo(NAS_ERR_LOG_BASE_STATE_LMM_CS_PAGING_RECEIVED,
                              NAS_MML_REG_FAIL_CAUSE_NULL);


   return MM_EVENT_ID_INVALID;
}






VOS_UINT8 NAS_MM_RcvLmmHoSecuInfoCnf(
    VOS_VOID                           *pstMsg
)
{
    LMM_MM_HO_SECU_INFO_CNF_STRU       *pstHoSecuInfo   = VOS_NULL_PTR;
    VOS_UINT8                          *pucDestBuffer   = VOS_NULL_PTR;
    VOS_VOID                           *pucSrcBuffer    = VOS_NULL_PTR;
    VOS_UINT32                          ulCount;
    VOS_UINT8                           ucCksn;

    pstHoSecuInfo = (LMM_MM_HO_SECU_INFO_CNF_STRU *)pstMsg;

    /* ֹͣ��ʱ�� */
    Mm_TimerStop(MM_TIMER_WAIT_GET_HO_SECU_INFO_CNF);

    /* ��ȡLMM�İ�ȫ������ʧ��ʱ����Ȼʹ��ԭ���İ�ȫ������ */
    if (MM_LMM_SECU_INFO_RSLT_SUCC != pstHoSecuInfo->enRslt)
    {
        if ((NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
         && (MM_INTER_RAT_CHANGE      == g_MmGlobalInfo.ucState))
        {
            /* ��MMC�ظ�����rsp */
            NAS_MM_SndMmcSuspendRsp();
        }

        return MM_EVENT_ID_INVALID;
    }

    /* ��LMM��ȡaucCk��Ϣ */
    pucDestBuffer                   = NAS_MML_GetSimCsSecurityUmtsCk();
    pucSrcBuffer                    = pstHoSecuInfo->stHoSecuCntxt.aucCk;
    ulCount                         = MM_LMM_CK_LEN;
    PS_MEM_CPY(pucDestBuffer, pucSrcBuffer, ulCount);

    /* ��LMM��ȡaucIk��Ϣ */
    pucDestBuffer                   = NAS_MML_GetSimCsSecurityUmtsIk();
    pucSrcBuffer                    = pstHoSecuInfo->stHoSecuCntxt.aucIk;
    ulCount                         = MM_LMM_IK_LEN;
    PS_MEM_CPY(pucDestBuffer, pucSrcBuffer, ulCount);

    /* ��LMM��ȡucCksn��Ϣ */
    ucCksn                          = (VOS_UINT8) pstHoSecuInfo->stHoSecuCntxt.ulKSI;
    NAS_MML_SetSimCsSecurityCksn(ucCksn);

    /*����CK,IK��C3�㷨����Kc*/
    NAS_MML_SecContext3GTO2G(NAS_MML_GetSimCsSecurityUmtsIk(),
                             NAS_MML_GetSimCsSecurityUmtsCk(),
                             NAS_MML_GetSimCsSecurityGsmKc());

    if ((NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
     && (MM_INTER_RAT_CHANGE      == g_MmGlobalInfo.ucState))
    {
        /* ��MMC�ظ�����rsp */
        NAS_MM_SndMmcSuspendRsp();
    }

    return MM_EVENT_ID_INVALID;
}





VOS_VOID NAS_MM_ProcBufferedCsfbService(VOS_VOID)
{
    /* ����MM��CC���� */
    if ((VOS_FALSE == NAS_MML_IsCsfbServiceStatusExist())
     && (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg))
    {
        NAS_MM_RcvCcEstReq_CSFB();
    }

    /* ����MM��SS���� */
    if ((VOS_FALSE == NAS_MML_IsCsfbServiceStatusExist())
     && (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg))
    {
        NAS_MM_RcvSsEstReq_CSFB();
    }

    return ;
}


/*lint -restore */


#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

