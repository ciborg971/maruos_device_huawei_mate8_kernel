/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : NasGmmProcLResult.c
  �� �� ��   : ����
  ��    ��   : zhoujun /40661
  ��������   : 2011��03��14��
  ����޸�   :
  ��������   : GMM�յ�Lģע�����Ĵ���
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2010��11��12��
    ��    ��   : zhoujun /40661
    �޸�����   : �����ļ�

******************************************************************************/
/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "product_config.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "MmcLmmInterface.h"
#include "PsTypeDef.h"
#include "GmmExt.h"
#include "NasMmSublayerDef.h"
#include "NasGmmProcLResult.h"
#include "NasMmcSndLmm.h"
#endif
#include "GmmInc.h"
#include "NasGmmSndOm.h"
#include "GmmCasGlobal.h"

#define    THIS_FILE_ID        PS_FILE_ID_GMM_PROC_LRESULT_C


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -save -e958 */

#if   (FEATURE_ON == FEATURE_LTE)
VOS_VOID NAS_GMM_RcvLmmAttachRegFailOtherCause(
    VOS_UINT32                          ulAttemptCount
)
{
    /*  3GPP TS 24.301 V9.5.0 (2010-12) 5.5.1.2.6��д��:

        d)  ATTACH REJECT, other EMM cause values than those treated
            in subclause 5.5.1.2.5
            Upon reception of the EMM cause #19, "ESM failure",
            the UE may set the attach attempt counter to 5.
            Upon reception of the EMM causes #95, #96, #97, #99 and #111
            the UE should set the attach attempt counter to 5.
            The UE shall proceed as described below.

        If A/Gb mode or Iu mode is supported by the UE,
        the UE shall in addition handle the GMM parameters GMM state,
        GPRS update status, P-TMSI, P-TMSI signature, RAI and GPRS
        ciphering key sequence number as specified in 3GPP TS 24.008 [13]
        for the abnormal case when a normal attach procedure fails
        and the attach attempt counter is equal to 5.
    */
    if (5 <= ulAttemptCount)
    {

        /*set the GPRS update status to GU2 NOT UPDATED*/
        NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_NOT_UPDATED);

        /*delete P-TMSI, P-TMSI signature, RAI and GPRS ciphering key sequence number */
        Gmm_DelPsLocInfoUpdateUsim();


        /*Ǩ��GMM_DEREGISTERED_NORMAL_SERVICE;*/
        Gmm_ComStaChg(GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH);
    }

    return;
}
VOS_VOID NAS_GMM_RcvLmmTauRegFailOtherCause(
    VOS_UINT32                                              ulAttemptCount,
    MMC_LMM_TAI_IN_LIST_FLAG_ENUM_UINT8                     enTaiInListFlag,
    MMC_LMM_EPS_UPDATE_STATUS_ENUM_UINT8                    enEmmUpStat
)
{
    if (VOS_TRUE == NAS_GMM_IsNeedUpdatePsUpdateStatus(ulAttemptCount,
                                       enTaiInListFlag, enEmmUpStat))
    {
        /* GPRS update status GU2 NOT UPDATED */
        NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_NOT_UPDATED);
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

        /* GMM state GMM_REGISTERED_ATTEMPTING_TO_UPDATE*/
        Gmm_ComStaChg(GMM_REGISTERED_ATTEMPTING_TO_UPDATE);
    }

    if (5 <= ulAttemptCount)
    {
        /* GMM state GMM_REGISTERED_ATTEMPTING_TO_UPDATE*/
        Gmm_ComStaChg(GMM_REGISTERED_ATTEMPTING_TO_UPDATE);

        /*GPRS update status GU2 NOT UPDATED*/
        NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_NOT_UPDATED);


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


        /*reset routing area updating attempt counter*/
        g_GmmRauCtrl.ucRauAttmptCnt                     = 0;
    }

    return;
}
VOS_VOID NAS_GMM_RcvLmmAttachRegFailCause42SevereNetworkFailure(
    VOS_UINT32                          ulAttemptCount
)
{
    if (NAS_MML_3GPP_REL_R11 > NAS_MML_GetLte3gppRelVersion())
    {
        NAS_GMM_RcvLmmAttachRegFailOtherCause(ulAttemptCount);
        return;
    }

    /* set the GPRS update status to GU2 NOT UPDATED*/
    NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_NOT_UPDATED);

    /* delete P-TMSI, P-TMSI signature, RAI and GPRS ciphering key sequence number */
    Gmm_DelPsLocInfoUpdateUsim();

    /* Ǩ��GMM-DEREGISTERED.LIMITSERVICE*/
    Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);
    return;
}
VOS_VOID NAS_GMM_RcvLmmTauRegFailCause42SevereNetworkFailure(
    VOS_UINT32                                              ulAttemptCount,
    MMC_LMM_TAI_IN_LIST_FLAG_ENUM_UINT8                     enTaiInListFlag,
    MMC_LMM_EPS_UPDATE_STATUS_ENUM_UINT8                    enEmmUpStat
)
{
    if (NAS_MML_3GPP_REL_R11 > NAS_MML_GetLte3gppRelVersion())
    {
        NAS_GMM_RcvLmmTauRegFailOtherCause(ulAttemptCount, enTaiInListFlag, enEmmUpStat);
        return;
    }

    /* set the GPRS update status to GU2 NOT UPDATED*/
    NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_NOT_UPDATED);

    /* delete P-TMSI, P-TMSI signature, RAI and GPRS ciphering key sequence number */
    Gmm_DelPsLocInfoUpdateUsim();

    /* Ǩ��GMM-DEREGISTERED.LIMITSERVICE*/
    Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);
    return;
}



VOS_VOID NAS_GMM_RcvLmmAttachCause_Handling(
    NAS_LMM_CN_CAUSE_ENUM_UINT8         enCnCause,
    VOS_UINT32                          ulAttemptCount
)
{
    NAS_MML_MS_3GPP_REL_STRU                               *pstMs3GppRel = VOS_NULL_PTR;
    NAS_LMM_CN_CAUSE_ENUM_UINT8                             enTmpCause;

    pstMs3GppRel = NAS_MML_GetMs3GppRel();
    enTmpCause   = enCnCause;

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
        case NAS_EMM_CAUSE_EPS_SERV_NOT_ALLOW:
        case NAS_EMM_CAUSE_EPS_SERV_AND_NON_EPS_SERV_NOT_ALLOW:
            NAS_GMM_ProcLmmRejCause3();

            break;

        case NAS_EMM_CAUSE_PLMN_NOT_ALLOW:
        case NAS_EMM_CAUSE_TA_NOT_ALLOW:
        case NAS_EMM_CAUSE_ROAM_NOT_ALLOW:
        case NAS_EMM_CAUSE_NO_SUITABL_CELL:
        case NAS_EMM_CAUSE_EPS_SERV_NOT_ALLOW_IN_PLMN:


            /*set the GPRS update status to GU3 ROAMING NOT ALLOWED*/
            NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_ROUTING_AREA_NOT_ALLOWED);

            /*delete P-TMSI, P-TMSI signature, RAI and GPRS ciphering key sequence number */
            Gmm_DelPsLocInfoUpdateUsim();


            /*Ǩ��GMM-DEREGISTERED.LIMITSERVICE;*/
            Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);

            /*reset the GPRS attach attempt counter*/
            g_GmmAttachCtrl.ucAttachAttmptCnt               = 0;

            break;

        /* 4.7.3.1.4	GPRS attach not accepted by the network */
        case NAS_EMM_CAUSE_NOT_AUTHORIZED_FOR_THIS_CSG:

            /*set the GPRS update status to GU3 ROAMING NOT ALLOWED*/
            NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_ROUTING_AREA_NOT_ALLOWED);

            /*Ǩ��GMM-DEREGISTERED.LIMITSERVICE;*/
            Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);


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

            /*reset the GPRS attach attempt counter*/
            g_GmmAttachCtrl.ucAttachAttmptCnt               = 0;


            break;

        case NAS_EMM_CAUSE_SERVER_NETWORK_FAILURE:
            NAS_GMM_RcvLmmAttachRegFailCause42SevereNetworkFailure(ulAttemptCount);
            break;

        /* OTHERSԭ��ֵ���� */
        default:
            NAS_GMM_RcvLmmAttachRegFailOtherCause(ulAttemptCount);
            break;
    }

    return ;

}
VOS_VOID NAS_GMM_RcvLmmTauCause_Handling(
    NAS_LMM_CN_CAUSE_ENUM_UINT8                             enCnCause,
    VOS_UINT32                                              ulAttemptCount,
    MMC_LMM_TAI_IN_LIST_FLAG_ENUM_UINT8                     enTaiInListFlag,
    MMC_LMM_EPS_UPDATE_STATUS_ENUM_UINT8                    enEmmUpStat
)
{
    NAS_MML_MS_3GPP_REL_STRU                               *pstMs3GppRel = VOS_NULL_PTR;
    NAS_LMM_CN_CAUSE_ENUM_UINT8                             enTmpCause;

    pstMs3GppRel = NAS_MML_GetMs3GppRel();
    enTmpCause   = enCnCause;

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
        case NAS_EMM_CAUSE_EPS_SERV_NOT_ALLOW:
        case NAS_EMM_CAUSE_EPS_SERV_AND_NON_EPS_SERV_NOT_ALLOW:
            NAS_GMM_ProcLmmRejCause3();
            break;

        case NAS_EMM_CAUSE_MS_ID_CANNOT_BE_DERIVED_BY_NW:
            /* GMM state GMM_DEREGISTERED_NORMAL_SERVICE*/
            Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);

            /*GPRS update status GU2 NOT UPDATED,*/
            NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_NOT_UPDATED);

            /*delete P-TMSI, P-TMSI signature, RAI and GPRS ciphering key sequence number */
            Gmm_DelPsLocInfoUpdateUsim();

            break;

        case NAS_EMM_CAUSE_EPS_IMPLICITLY_DETACHED:
        case NAS_EMM_CAUSE_NO_EPS_BEARER_CONTEXT_ACTIVATED:

            /* GMM state GMM_DEREGISTERED_NORMAL_SERVICE*/
            Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);

            break;

        case NAS_EMM_CAUSE_PLMN_NOT_ALLOW:
        case NAS_EMM_CAUSE_TA_NOT_ALLOW:
        case NAS_EMM_CAUSE_EPS_SERV_NOT_ALLOW_IN_PLMN:

            /* GMM state GMM_REGISTERED_LIMITED_SERVICE*/
            Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);

            /*GPRS update status GU3 ROAMING NOT ALLOWED*/
            NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_ROUTING_AREA_NOT_ALLOWED);

            /*delete P-TMSI, P-TMSI signature, RAI and GPRS ciphering key sequence number */
            Gmm_DelPsLocInfoUpdateUsim();

            /*reset routing area updating attempt counter*/
            g_GmmRauCtrl.ucRauAttmptCnt                     = 0;

            break;

        case NAS_EMM_CAUSE_ROAM_NOT_ALLOW:
        case NAS_EMM_CAUSE_NO_SUITABL_CELL:
        case NAS_EMM_CAUSE_NOT_AUTHORIZED_FOR_THIS_CSG:

            /* GMM state GMM_REGISTERED_LIMITED_SERVICE*/
            Gmm_ComStaChg(GMM_REGISTERED_LIMITED_SERVICE);

            /*GPRS update status GU3 ROAMING NOT ALLOWED*/
            NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_ROUTING_AREA_NOT_ALLOWED);


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


            /*reset routing area updating attempt counter*/
            g_GmmRauCtrl.ucRauAttmptCnt                     = 0;

            /* �ο�24.008 4.7.5.2.4,#13,#15Ӧ�÷���combined rau with IMSI attach */
            if (NAS_EMM_CAUSE_NOT_AUTHORIZED_FOR_THIS_CSG != enCnCause)
            {
                g_MmSubLyrShare.GmmShare.ucGsAssociationFlg = VOS_FALSE;
            }
            break;

        case NAS_EMM_CAUSE_SERVER_NETWORK_FAILURE:
            NAS_GMM_RcvLmmTauRegFailCause42SevereNetworkFailure(ulAttemptCount, enTaiInListFlag, enEmmUpStat );
            break;

        default :
            NAS_GMM_RcvLmmTauRegFailOtherCause(ulAttemptCount, enTaiInListFlag, enEmmUpStat);
            break;

        }


        return ;
}
VOS_VOID  NAS_GMM_RcvLmmNwInitDetachIndCause_Handling(
    NAS_LMM_CN_CAUSE_ENUM_UINT8         enCnCause
)
{
    switch (enCnCause)
    {
        case NAS_EMM_CAUSE_IMSI_UNKNOWN_IN_HSS:
            break;
        case NAS_EMM_CAUSE_ILLEGAL_UE:
        case NAS_EMM_CAUSE_ILLEGAL_ME:
        case NAS_EMM_CAUSE_EPS_SERV_NOT_ALLOW:
        case NAS_EMM_CAUSE_EPS_SERV_AND_NON_EPS_SERV_NOT_ALLOW:
            NAS_GMM_ProcLmmRejCause3();
            break;

        case NAS_EMM_CAUSE_PLMN_NOT_ALLOW:

            /*set the GPRS update status to GU3 ROAMING NOT ALLOWED*/
            NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_ROUTING_AREA_NOT_ALLOWED);

            /*delete P-TMSI, P-TMSI signature, RAI and GPRS ciphering key sequence number */
            Gmm_DelPsLocInfoUpdateUsim();


            /*Ǩ��GMM-DEREGISTERED.LIMITSERVICE;*/
            Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);

            /*reset the GPRS attach attempt counter*/
            g_GmmAttachCtrl.ucAttachAttmptCnt               = 0;

            break;

        case NAS_EMM_CAUSE_TA_NOT_ALLOW:
        case NAS_EMM_CAUSE_ROAM_NOT_ALLOW:
        case NAS_EMM_CAUSE_NO_SUITABL_CELL:

            /*reset the GPRS attach attempt counter*/
            g_GmmAttachCtrl.ucAttachAttmptCnt               = 0;


            /*set the GPRS update status to GU3 ROAMING NOT ALLOWED*/
            NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_ROUTING_AREA_NOT_ALLOWED);

            /*delete P-TMSI, P-TMSI signature, RAI and GPRS ciphering key sequence number */
            Gmm_DelPsLocInfoUpdateUsim();


            /*Ǩ��GMM-DEREGISTERED.LIMITED-SERVIC*/
            Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);

            break;

        case NAS_EMM_CAUSE_EPS_SERV_NOT_ALLOW_IN_PLMN:


            /*set the GPRS update status to GU3 ROAMING NOT ALLOWED*/
            NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_ROUTING_AREA_NOT_ALLOWED);

            /*delete P-TMSI, P-TMSI signature, RAI and GPRS ciphering key sequence number */
            Gmm_DelPsLocInfoUpdateUsim();


            /*reset the GPRS attach attempt counter*/
            g_GmmAttachCtrl.ucAttachAttmptCnt               = 0;


            /*Ǩ��GMM_DEREGISTERED_LIMITED_SERVICE*/
            Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);

            break;
        /*case NAS_MML_REG_FAIL_CAUSE_NOT_AUTHORIZED_FOR_THIS_CSG:*/
        case NAS_EMM_CAUSE_NOT_AUTHORIZED_FOR_THIS_CSG:
            /*reset the GPRS attach attempt counter*/
            g_GmmAttachCtrl.ucAttachAttmptCnt               = 0;

            /*set the GPRS update status to GU3 ROAMING NOT ALLOWED*/
            NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_ROUTING_AREA_NOT_ALLOWED);


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


            /*Ǩ��GMM_DEREGISTERED_LIMITED_SERVICE*/
            Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);

            break;

     default:

            /*set the GPRS update status to GU2 NOT UPDATED*/
            NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_NOT_UPDATED);

            /*delete P-TMSI, P-TMSI signature, RAI and GPRS ciphering key sequence number */
            Gmm_DelPsLocInfoUpdateUsim();


            /*Ǩ��GMM_DEREGISTERED_NORMAL_SERVICE*/
            Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);

         break;
    }

    return ;
}


VOS_VOID  NAS_GMM_RcvLmmServiceCause_Handling(
    NAS_LMM_CN_CAUSE_ENUM_UINT8         enCnCause
)
{
    NAS_MML_MS_3GPP_REL_STRU                               *pstMs3GppRel = VOS_NULL_PTR;
    NAS_LMM_CN_CAUSE_ENUM_UINT8                             enTmpCause;

    pstMs3GppRel = NAS_MML_GetMs3GppRel();
    enTmpCause   = enCnCause;

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

        if (NAS_EMM_CAUSE_NO_EPS_BEARER_CONTEXT_ACTIVATED == enTmpCause)
        {
            enTmpCause = NAS_EMM_CAUSE_EPS_IMPLICITLY_DETACHED;
        }
    }

    switch ( enTmpCause )
    {
        case NAS_EMM_CAUSE_ILLEGAL_UE:
        case NAS_EMM_CAUSE_ILLEGAL_ME:
        case NAS_EMM_CAUSE_EPS_SERV_NOT_ALLOW:
            NAS_GMM_ProcLmmRejCause3();

            break;

        case NAS_EMM_CAUSE_EPS_SERV_AND_NON_EPS_SERV_NOT_ALLOW:
            if (NAS_MML_GetLte3gppRelVersion() >= NAS_MML_3GPP_REL_R11)
            {
                NAS_GMM_ProcLmmRejCause3();
            }
            break;

        case NAS_EMM_CAUSE_PLMN_NOT_ALLOW:
        case NAS_EMM_CAUSE_TA_NOT_ALLOW:


            /*set the GPRS update status to GU3 ROAMING NOT ALLOWED*/
            NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_ROUTING_AREA_NOT_ALLOWED);

            /*delete P-TMSI, P-TMSI signature, RAI and GPRS ciphering key sequence number */
            Gmm_DelPsLocInfoUpdateUsim();

            /*GMM state is GMM_DEREGISTERED_LIMITED_SERVICE*/
            Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);

            break;

        case NAS_EMM_CAUSE_MS_ID_CANNOT_BE_DERIVED_BY_NW:


            /*set the GPRS update status to GU2 NOT UPDATED*/
            NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_NOT_UPDATED);
            /*delete P-TMSI, P-TMSI signature, RAI and GPRS ciphering key sequence number */
            Gmm_DelPsLocInfoUpdateUsim();

            /*enter the state GMM_DEREGISTERED_NORMAL_SERVICE*/
            Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);

            break;

        case NAS_EMM_CAUSE_EPS_IMPLICITLY_DETACHED:

            /*change to state GMM-DEREGISTERED.NORMAL-SERVICE*/
            Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);

            break;

        case NAS_EMM_CAUSE_ROAM_NOT_ALLOW:
        case NAS_EMM_CAUSE_NO_SUITABL_CELL:
        case NAS_EMM_CAUSE_NOT_AUTHORIZED_FOR_THIS_CSG:

           /*set the GPRS update status to GU3 ROAMING NOT ALLOWED */
           NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_ROUTING_AREA_NOT_ALLOWED);


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



           /*change to state GMM-REGISTERED.LIMITED-SERVICE.*/
           Gmm_ComStaChg(GMM_REGISTERED_LIMITED_SERVICE);

           break;

        case NAS_EMM_CAUSE_SERVER_NETWORK_FAILURE:
            if (NAS_MML_GetLte3gppRelVersion() >= NAS_MML_3GPP_REL_R11)
            {
                /* set the GPRS update status to GU2 NOT UPDATED*/
                NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_NOT_UPDATED);

                /* delete P-TMSI, P-TMSI signature, RAI and GPRS ciphering key sequence number */
                Gmm_DelPsLocInfoUpdateUsim();

                /* Ǩ��GMM-DEREGISTERED.LIMITSERVICE*/
                Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);
            }
            break;

       default:
           break;

    }

    return ;
}
VOS_VOID  NAS_GMM_RcvLmmAttachResult(
    VOS_VOID                           *pstMsg
)
{
    MMCGMM_LMM_ATTACH_IND_STRU         *pstLmmAttachMsg;
    NAS_LMM_CN_CAUSE_ENUM_UINT8         enCnCause;
    VOS_UINT32                          ulAttemptCount;

    enCnCause      = NAS_EMM_CAUSE_BUTT;
    ulAttemptCount = 0x0;

    pstLmmAttachMsg = (MMCGMM_LMM_ATTACH_IND_STRU *)pstMsg;

    if (VOS_TRUE == pstLmmAttachMsg->bitOpCnCause)
    {
        enCnCause = pstLmmAttachMsg->ucCnCause;
    }

    if (VOS_TRUE == pstLmmAttachMsg->bitOpAtmpCnt)
    {
        ulAttemptCount = pstLmmAttachMsg->ulAttemptCount;
    }

    if (MMC_LMM_ATT_RSLT_SUCCESS == pstLmmAttachMsg->ulAttachRslt)
    {
        /* Ǩ��GMM-REGISTERED.NO-CELL-AVAILABLE*/



        /* ���µ�ǰGMM��״̬ΪATTACHED,������Lģ������ʱ�л���Wģ����RAU
           �ᵼ�¼�Ȩʧ�� */
        Gmm_ComStaChg(GMM_REGISTERED_NO_CELL_AVAILABLE);

        /* ����GCFҪ��,��L������ע��ɹ�����GU��Ӧ�÷���COMBINED RAU
           ע��: ����23.060,��SGs�ӿڽ���ʱ,��Ҫɾ��Gs�ӿ�,�˴���ʵ�ֺ�Э�鲻һ�� */

        if (VOS_TRUE == pstLmmAttachMsg->bitOpCnRslt)
        {
            g_MmSubLyrShare.GmmShare.ucGsAssociationFlg = VOS_FALSE;

            if (MMC_LMM_ATT_TYPE_COMBINED_EPS_IMSI == pstLmmAttachMsg->ulReqType)
            {
                g_MmSubLyrShare.GmmShare.ucGsAssociationFlg = VOS_TRUE;
            }
        }
        

        /* 4.7.2.1.2 Handling of READY timer in the MS in Iu mode and S1 mode
           The READY timer is not applicable for Iu mode and S1 mode.
           Upon completion of a successful GPRS attach or routing area updating
           procedure in Iu mode, the MS may stop the READY timer, if running.
           Upon completion of a successful EPS attach or tracking area updating
           procedure, the MS may stop the READY timer, if running. */
        Gmm_TimerStop(GMM_TIMER_T3314);
        gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_STANDBY;

          g_GmmAttachCtrl.ucAttachAttmptCnt = 0;

#if ( VOS_WIN32 == VOS_OS_VER )
        NAS_GMM_SndTinTypeToMmc(NAS_MML_TIN_TYPE_GUTI);
#endif
    }
    else if (MMC_LMM_ATT_RSLT_ACCESS_BAR == pstLmmAttachMsg->ulAttachRslt)
    {
        /*Ǩ��GMM-DEREGISTERED.ATTACH-NEEDED*/
        Gmm_ComStaChg(GMM_DEREGISTERED_ATTACH_NEEDED);
    }
    else if (MMC_LMM_ATT_RSLT_CN_REJ == pstLmmAttachMsg->ulAttachRslt)
    {
        NAS_GMM_RcvLmmAttachCause_Handling(enCnCause, ulAttemptCount);
    }

    else if ( (MMC_LMM_ATT_RSLT_TIMER_EXP ==  pstLmmAttachMsg->ulAttachRslt)
           || (MMC_LMM_ATT_RSLT_FAILURE == pstLmmAttachMsg->ulAttachRslt) )

    {
        if (5 <= ulAttemptCount)
        {
            /*set the GPRS update status to GU2 NOT UPDATED*/
            NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_NOT_UPDATED);

            Gmm_DelPsLocInfoUpdateUsim();

            /*Ǩ��GMM_DEREGISTERED_NORMAL_SERVICE;*/
            Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);
        }
    }
    else if ( MMC_LMM_ATT_RSLT_AUTH_REJ ==  pstLmmAttachMsg->ulAttachRslt)
    {
        NAS_GMM_RcvLmmAuthResult(pstMsg);
    }
    else if ( (MMC_LMM_ATT_RSLT_FORBID_PLMN           ==  pstLmmAttachMsg->ulAttachRslt)
           || (MMC_LMM_ATT_RSLT_FORBID_TA_FOR_RPOS    ==  pstLmmAttachMsg->ulAttachRslt)
           || (MMC_LMM_ATT_RSLT_FORBID_PLMN_FOR_GPRS  ==  pstLmmAttachMsg->ulAttachRslt)
           || (MMC_LMM_ATT_RSLT_FORBID_TA_FOR_ROAMING ==  pstLmmAttachMsg->ulAttachRslt) )
    {
        /* GMM��DEREGISTER״̬�����ʱǨ�Ƶ�GMM_DEREGISTERED_LIMITED_SERVICE */
        if ( VOS_TRUE == NAS_GMM_IsDeregisterState(g_GmmGlobalCtrl.ucState) )
        {
            Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);
        }
        else
        {
            Gmm_ComStaChg(GMM_REGISTERED_LIMITED_SERVICE);
        }
    }
    else if ((MMC_LMM_ATT_RSLT_PS_ATT_NOT_ALLOW == pstLmmAttachMsg->ulAttachRslt)
          || (MMC_LMM_ATT_RSLT_MO_DETACH_FAILURE == pstLmmAttachMsg->ulAttachRslt)
          || (MMC_LMM_ATT_RSLT_MT_DETACH_FAILURE == pstLmmAttachMsg->ulAttachRslt)
          || (MMC_LMM_ATT_RSLT_T3402_RUNNING == pstLmmAttachMsg->ulAttachRslt)
          || (MMC_LMM_ATT_RSLT_ESM_FAILURE == pstLmmAttachMsg->ulAttachRslt))
    {
        Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);
    }
    else
    {
    }


    /* �жϵȴ���־�Ƿ���ڣ������������MMCGMM_ATTACH CNF,��ֹAT��һֱ��CGATT�������� */
    if (GMM_WAIT_PS_ATTACH == (g_GmmGlobalCtrl.stAttachInfo.enAttachType
                             & GMM_WAIT_PS_ATTACH))
    {
        NAS_GMM_SndMmcAttachCnf();

        /* ���Attach cnf�ظ���־ */
        g_GmmGlobalCtrl.stAttachInfo.enAttachType = GMM_WAIT_NULL_ATTACH;
    }

    return ;
}


VOS_UINT32 NAS_GMM_IsNeedUpdatePsUpdateStatus(
    VOS_UINT32                                              ulAttemptCount,
    MMC_LMM_TAI_IN_LIST_FLAG_ENUM_UINT8                     enTaiInListFlag,
    MMC_LMM_EPS_UPDATE_STATUS_ENUM_UINT8                    enEmmUpStat
)
{
    NAS_MML_TIN_TYPE_ENUM_UINT8         enTinType;

    /* 24301Э��:
       If the tracking area updating attempt counter is less than 5,
       and the TAI of the current serving cell is not included in the TAI list
       or the EPS update status is different to EU1 UPDATED:
       If A/Gb mode or Iu mode is supported by the UE, the UE shall in addition
       handle the GPRS update status as specified in 3GPP TS 24.008 [13]
       for the abnormal case when a normal or periodic routing area updating
       procedure fails and the routing area updating attempt counter is less
       than 5 and the GPRS update status is different from GU1 UPDATED.
       24008Э��:
       If the routing area updating attempt counter is less than 5, and the
       stored RAI is different to the RAI of the current serving cell or the
       GPRS update status is different to GU1 UPDATED:
       the MS shall start timer T3311, shall set the GPRS update status to GU2
       NOT UPDATED and changes state to GMM-REGISTERED.ATTEMPTING-TO-UPDATE. */
    enTinType = NAS_MML_GetTinType();

    if ((ulAttemptCount != 0)
     && (ulAttemptCount < GMM_ATTACH_RAU_ATTEMPT_MAX_CNT)
     && ((MMC_LMM_TAI_NOT_IN_TAI_LIST == enTaiInListFlag)
     || (MMC_LMM_EPS_UPDATE_STATUS_UPDATED != enEmmUpStat)
     || (NAS_MML_TIN_TYPE_PTMSI == enTinType)))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

VOS_VOID NAS_GMM_RcvLmmTauResult(
    VOS_VOID                           *pstMsg

)
{
    MMCGMM_LMM_TAU_RESULT_IND_STRU                         *pstLmmTauMsg;
    NAS_LMM_CN_CAUSE_ENUM_UINT8                             enCnCause;
    VOS_UINT32                                              ulAttemptCount;

    MMC_LMM_TAI_IN_LIST_FLAG_ENUM_UINT8                     enTaiInListFlag;
    MMC_LMM_EPS_UPDATE_STATUS_ENUM_UINT8                    enEmmUpStat;

    enCnCause       = NAS_EMM_CAUSE_BUTT;
    ulAttemptCount  = 0x0;
    enTaiInListFlag = MMC_LMM_TAI_IN_LIST_FLAG_BUTT;
    enEmmUpStat     = MMC_LMM_EPS_UPDATE_STATUS_BUTT;

    pstLmmTauMsg = (MMCMM_LMM_TAU_RESULT_IND_STRU *)pstMsg;


    if (VOS_TRUE == pstLmmTauMsg->bitOpCnCause)
    {
        enCnCause = pstLmmTauMsg->ucCnCause;
    }

    if (VOS_TRUE == pstLmmTauMsg->bitOpAtmpCnt)
    {
        ulAttemptCount = pstLmmTauMsg->ulAttemptCount;
    }

    if (VOS_TRUE == pstLmmTauMsg->bitOpTaiInListFlag)
    {
        enTaiInListFlag = pstLmmTauMsg->enTaiInListFlag;
    }

    if (VOS_TRUE == pstLmmTauMsg->bitOpEpsUpdateStuts)
    {
        enEmmUpStat = pstLmmTauMsg->enEmmUpStat;
    }

    if (MMC_LMM_TAU_RSLT_SUCCESS == pstLmmTauMsg->ulTauRst)
    {
        /*Ǩ��GMM-REGISTERED.NO-CELL-AVAILABLE;*/

        Gmm_ComStaChg(GMM_REGISTERED_NO_CELL_AVAILABLE);

        /* ����GCFҪ��,��L������ע��ɹ�����GU��Ӧ�÷���COMBINED RAU
           ע��: ����23.060,��SGs�ӿڽ���ʱ,��Ҫɾ��Gs�ӿ�,�˴���ʵ�ֺ�Э�鲻һ�� */

        if (VOS_TRUE == pstLmmTauMsg->bitOpCnRst)
        {
            g_MmSubLyrShare.GmmShare.ucGsAssociationFlg = VOS_FALSE;

            if ( (MMC_LMM_COMBINED_TA_LA_UPDATING  == pstLmmTauMsg->ulReqType)
              || (MMC_LMM_COMBINED_TA_LA_WITH_IMSI == pstLmmTauMsg->ulReqType)
              || (MMC_LMM_CS_PS_PERIODIC_UPDATING  == pstLmmTauMsg->ulReqType) )
            {
                g_MmSubLyrShare.GmmShare.ucGsAssociationFlg = VOS_TRUE;
            }
        }
        

        /* 4.7.2.1.2 Handling of READY timer in the MS in Iu mode and S1 mode
           The READY timer is not applicable for Iu mode and S1 mode.
           Upon completion of a successful GPRS attach or routing area updating
           procedure in Iu mode, the MS may stop the READY timer, if running.
           Upon completion of a successful EPS attach or tracking area updating
           procedure, the MS may stop the READY timer, if running. */
        Gmm_TimerStop(GMM_TIMER_T3314);
        gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_STANDBY;
    }
    else if (MMC_LMM_TAU_RSLT_ACCESS_BARED == pstLmmTauMsg->ulTauRst)
    {
        /* Ǩ��GMM_REGISTERED_UPDATE_NEEDED; */
        Gmm_ComStaChg(GMM_REGISTERED_UPDATE_NEEDED);
    }
    else if (MMC_LMM_TAU_RSLT_CN_REJ == pstLmmTauMsg->ulTauRst)
    {
        NAS_GMM_RcvLmmTauCause_Handling(enCnCause, ulAttemptCount, enTaiInListFlag, enEmmUpStat);
    }

    else if ( (MMC_LMM_TAU_RSLT_TIMER_EXP ==  pstLmmTauMsg->ulTauRst)
           || (MMC_LMM_TAU_RSLT_FAILURE == pstLmmTauMsg->ulTauRst) )

    {
        if (5 <= ulAttemptCount)
        {
            /*GPRS update status GU2 NOT UPDATED*/
            NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_NOT_UPDATED);

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

            /* GMM state GMM_REGISTERED_ATTEMPTING_TO_UPDATE*/
            Gmm_ComStaChg(GMM_REGISTERED_ATTEMPTING_TO_UPDATE);

            /*routing area updating attempt counter*/
            g_GmmRauCtrl.ucRauAttmptCnt = 0;
        }
        else
        {
            if (VOS_TRUE == NAS_GMM_IsNeedUpdatePsUpdateStatus(ulAttemptCount,
                                               enTaiInListFlag, enEmmUpStat))
            {
                /* GPRS update status GU2 NOT UPDATED */
                NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_NOT_UPDATED);

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

                /* GMM state GMM_REGISTERED_ATTEMPTING_TO_UPDATE*/
                Gmm_ComStaChg(GMM_REGISTERED_ATTEMPTING_TO_UPDATE);
            }
        }
    }
    else if ( MMC_LMM_TAU_RSLT_AUTH_REJ ==  pstLmmTauMsg->ulTauRst)
    {
        NAS_GMM_RcvLmmAuthResult(pstMsg);
    }

    else if ( (MMC_LMM_TAU_RSLT_FORBID_PLMN           ==  pstLmmTauMsg->ulTauRst)
           || (MMC_LMM_TAU_RSLT_FORBID_TA_FOR_RPOS    == pstLmmTauMsg->ulTauRst)
           || (MMC_LMM_TAU_RSLT_FORBID_PLMN_FOR_GPRS  == pstLmmTauMsg->ulTauRst)
           || (MMC_LMM_TAU_RSLT_FORBID_TA_FOR_ROAMING == pstLmmTauMsg->ulTauRst) )
    {
        Gmm_ComStaChg(GMM_REGISTERED_LIMITED_SERVICE);
    }
    else if ((MMC_LMM_TAU_RSLT_MO_DETACH_FAILURE == pstLmmTauMsg->ulTauRst)
          || (MMC_LMM_TAU_RSLT_MT_DETACH_FAILURE == pstLmmTauMsg->ulTauRst)
          || (MMC_LMM_TAU_RSLT_T3402_RUNNING == pstLmmTauMsg->ulTauRst))
    {
        Gmm_ComStaChg(GMM_REGISTERED_LIMITED_SERVICE);
    }
    else
    {
    }

    return ;
}


VOS_VOID  NAS_GMM_RcvLmmMtDetachInd(
    struct MsgCB                       *pstMsg
)
{
    MMCGMM_LMM_MT_DETACH_IND_STRU      *pstLmmDetachMsg;
    NAS_LMM_CN_CAUSE_ENUM_UINT8         enCnCause;

    enCnCause       = NAS_EMM_CAUSE_BUTT;

    pstLmmDetachMsg = (MMCGMM_LMM_MT_DETACH_IND_STRU *)pstMsg;

    if (VOS_TRUE == pstLmmDetachMsg->bitOpCnCause)
    {
        enCnCause = pstLmmDetachMsg->ucCnCause;
    }

    /* ���bitOpCnReqTypeָʾ��Я�������·���Detach����,��ӡ�쳣�󷵻� */
    if (0 == pstLmmDetachMsg->bitOpCnReqType)
    {
        /* �쳣��ӡ */
        NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_RcvLmmMtDetachInd: Detach type is not exist.");

        return;
    }

    /* ���������·���Detach���ͷֱ��� */
    switch (pstLmmDetachMsg->ulCnReqType)
    {
        case MMC_LMM_MT_DET_REATTACH_NOT_REQUIRED:

            /* ��������Я����ԭ��ֵ���� */
            NAS_GMM_RcvLmmNwInitDetachIndCause_Handling(enCnCause);

            break;

        case MMC_LMM_MT_DET_REATTACH_REQUIRED:

            /* ״̬Ǩ��GMM_DEREGISTERED_NO_CELL_AVAILABLE */
            g_GmmGlobalCtrl.ucState = GMM_DEREGISTERED_NO_CELL_AVAILABLE;

            NAS_GMM_LogGmmStateInfo(g_GmmGlobalCtrl.ucState);

            break;

        case MMC_LMM_MT_DET_IMSI:

            /* ������ */

            break;

        default:

            /* �쳣��ӡ */
            NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_RcvLmmMtDetachInd: Detach type requested by cn is unexpected.");

            break;
    }

    return ;
}


VOS_VOID NAS_GMM_RcvLmmMoDetachInd(
    struct MsgCB                       *pstMsg
)
{
    MMCGMM_LMM_MO_DETACH_IND_STRU      *pstLmmDetachMsg = VOS_NULL_PTR;

    pstLmmDetachMsg = (MMCGMM_LMM_MO_DETACH_IND_STRU *)pstMsg;

    switch (pstLmmDetachMsg->ulDetachRslt)
    {
        case  MMC_LMM_DETACH_RSLT_SUCCESS:

            if (GMM_TRUE == g_GmmAttachCtrl.ucSmCnfFlg)
            {
                Gmm_SndSmEstablishCnf(GMM_SM_EST_FAILURE, GMM_SM_CAUSE_PS_DETACH);
            }

            g_GmmAttachCtrl.ucSmCnfFlg    = GMM_FALSE;
            g_GmmGlobalCtrl.ucFollowOnFlg = GMM_FALSE;
            NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);

            Gmm_ComStaChg(GMM_DEREGISTERED_NO_CELL_AVAILABLE);

            break;

        case MMC_LMM_DETACH_RSLT_AUTH_REJ:

            NAS_GMM_RcvLmmAuthResult(pstMsg);

            break;

        default:

            /* �쳣��ӡ */
            NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_RcvLmmMoDetachInd: Detach result by cn is unexpected.");

            break;
    }

    return;
}



VOS_VOID NAS_GMM_RcvLmmLocalDetachInd(
    struct MsgCB                       *pstMsg
)
{
    MMCGMM_LMM_LOCAL_DETACH_IND_STRU   *pstLmmDetachInd = VOS_NULL_PTR;

    pstLmmDetachInd = (MMCGMM_LMM_LOCAL_DETACH_IND_STRU *)pstMsg;

    /* local detach op��ر� */
    if ( VOS_FALSE == pstLmmDetachInd->bitOpLocDetType)
    {
        /* �쳣��ӡ */
        NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_RcvLmmLocalDetachInd: Invalid local detach type!");

        return;
    }

    switch (pstLmmDetachInd->ulLocDetType)
    {
        /* If A/Gb mode or Iu mode is supported by the UE, the UE shall in addition
           handle the GMM parameters GMM state, GPRS update status, P-TMSI, P-TMSI
           signature, RAI, and GPRS ciphering key sequence number as specified in
           3GPP TS 24.008 [13] for the case when a paging for GPRS services using
           IMSI is received.*/
        case  MMC_LMM_L_LOCAL_DETACH_IMSI_PAGING:

            /* ����״̬��ΪGU2  */
            NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_NOT_UPDATED);

            Gmm_DelPsLocInfoUpdateUsim();

            /* ����״̬�Ĺ������� */
            Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);

            break;

        case  MMC_LMM_L_LOCAL_DETACH_OTHERS:

            /* ����״̬�Ĺ������� */
            Gmm_ComStaChg(GMM_DEREGISTERED_NO_CELL_AVAILABLE);

            break;

        default:

            /* �쳣��ӡ */
            NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_RcvLmmLocalDetachInd: Unexpected local detach type!");

            break;
    }

    return;
}




VOS_VOID NAS_GMM_RcvLmmTimerInfoNotify_RegNmlServ(VOS_VOID)
{

    /* 3GPP 24.008��4.7.5.2.1 :when the MS is configured to use CS fallback and SMS over SGs,
       or SMS over SGs only, the TIN indicates "RAT-related TMSI" and the periodic tracking
       area update timer T3412 expires;
    */

    if (MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState)
    {
        g_GmmRauCtrl.ucPeriodicRauFlg = GMM_TRUE;
        if (VOS_TRUE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg)
        {
            g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_COMBINED;
			/* reference to 24.008 4.7.5.2.1 Combined routing area updating procedure initiation
			   when the MS which is configured to use CS fallback and
			   SMS over SGs, or SMS over SGs only, enters a GERAN or
			   UTRAN cell and the E-UTRAN deactivate ISR timer T3423 has expired */
            NAS_GMM_SndRoutingAreaUpdateReq(GMM_COMBINED_RALA_UPDATING);
        }
        else
        {
            g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_WITH_IMSI_ATTACH;
            NAS_GMM_SndRoutingAreaUpdateReq(GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);
        }
        return;
    }

    /* CS������attach */
    if (VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
    {
        g_GmmRauCtrl.ucPeriodicRauFlg = GMM_TRUE;
        g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_WITH_IMSI_ATTACH;
        NAS_GMM_SndRoutingAreaUpdateReq(GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);
    }

    return;
}
VOS_VOID NAS_GMM_RcvLmmTimerInfoNotify_RegLimitServ(VOS_VOID)
{
    if ((GMM_TRUE == g_GmmGlobalCtrl.SysInfo.ucSysValidFlg)
     && (GMM_FALSE == g_GmmGlobalCtrl.ucCvrgAreaLostFlg))
    {
        if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
         && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
        {
            NAS_GMM_SndMmLuInitiation(GMMMM_T3412OrT3423_EXPIRED);
        }
    }
    else
    {
    }
    return;

}
VOS_VOID NAS_GMM_RcvLmmTimerStateNotify(
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulT3412ExpNeedRegFlg;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrNetRatType;
    VOS_UINT32                          ulIsAbleCombineRauFlg;

    ulIsAbleCombineRauFlg = NAS_GMM_IsAbleCombinedRau_TimerStatusChg();
    enCurrNetRatType      = NAS_MML_GetCurrNetRatType();
    ulT3412ExpNeedRegFlg  = NAS_GMM_IsT3412ExpiredNeedRegist(NAS_MML_GetLteCsServiceCfg(),
                                          NAS_MML_GetTinType(), NAS_MML_GetT3412Status());

    /* �յ�L T3412��ʱ��Ϣ */
    if ((NAS_MML_NET_RAT_TYPE_LTE != enCurrNetRatType)
     && (VOS_TRUE == ulT3412ExpNeedRegFlg)
     && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
    {
        switch (g_GmmGlobalCtrl.ucState)
        {
            case GMM_REGISTERED_LIMITED_SERVICE:
            case GMM_REGISTERED_NO_CELL_AVAILABLE:
                NAS_GMM_RcvLmmTimerInfoNotify_RegLimitServ();
                break;

            case GMM_REGISTERED_NORMAL_SERVICE:
            case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:
                if (VOS_TRUE == ulIsAbleCombineRauFlg)
                {
                    NAS_GMM_RcvLmmTimerInfoNotify_RegNmlServ();
                }
                break;

            default :
                NAS_INFO_LOG(WUEPS_PID_GMM, "NAS_GMM_RcvLmmTimerInfoNotify: Invalid state");
                break;
        }
    }

    return;
}
VOS_VOID NAS_GMM_RcvMmcEmergencyNumList(
    struct MsgCB                                           *pRcvMsg
)
{
    MMCGMM_EMERGENCY_NUM_LIST_IND_STRU                     *pstMsg = VOS_NULL_PTR;
    NAS_MML_EMERGENCY_NUM_LIST_STRU                         stEmergencyList;

    pstMsg = (MMCGMM_EMERGENCY_NUM_LIST_IND_STRU *)pRcvMsg;
    PS_MEM_SET(&stEmergencyList, 0, sizeof(NAS_MML_EMERGENCY_NUM_LIST_STRU));

    /* if EMC list is existence, update EMC list and send EMC list to CC */
    if (VOS_TRUE == pstMsg->ucOpEmcNumList)
    {
        if (pstMsg->ucEmergencyNumAmount > MMC_GMM_EMERGENCY_NUM_LIST_MAX_RECORDS)
        {
            stEmergencyList.ucEmergencyNumber = MMC_GMM_EMERGENCY_NUM_LIST_MAX_RECORDS;
        }
        else
        {
            stEmergencyList.ucEmergencyNumber = pstMsg->ucEmergencyNumAmount;
        }

        /* get PLMN MCC */
        stEmergencyList.ulMcc  = NAS_MML_GetCurrCampPlmnId()->ulMcc;

        PS_MEM_CPY((VOS_UINT8 *)&(stEmergencyList.aucEmergencyList[0]),
                   (VOS_UINT8 *)&(pstMsg->astEmergencyNumList[0]),
                   sizeof(LMM_MMC_EMERGENCY_NUM_STRU) * (stEmergencyList.ucEmergencyNumber));

        /* update EMC list to MML data base */
        NAS_MML_SetEmergencyNumList(&stEmergencyList);

        /* send EMC list to CC */
        Gmm_SndCcEmergencyNumberList(&stEmergencyList);
    }
}
VOS_VOID  NAS_GMM_RcvLmmServiceResult(
    VOS_VOID                           *pstMsg

)
{

    MMCGMM_LMM_SERVICE_RESULT_IND_STRU *pstLmmServiceRsltMsg;
    NAS_LMM_CN_CAUSE_ENUM_UINT8         enCnCause;

    enCnCause       = NAS_EMM_CAUSE_BUTT;

    pstLmmServiceRsltMsg = (MMCGMM_LMM_SERVICE_RESULT_IND_STRU *)pstMsg;

    if (VOS_TRUE == pstLmmServiceRsltMsg->bitOpCnCause)
    {
        enCnCause = pstLmmServiceRsltMsg->ucCnCause;
    }

    if (MMC_LMM_SERVICE_RSLT_CN_REJ == pstLmmServiceRsltMsg->ulServiceRst)
    {
        NAS_GMM_RcvLmmServiceCause_Handling(enCnCause);
    }
    else if (MMC_LMM_SERVICE_RSLT_ACCESS_BARED == pstLmmServiceRsltMsg->ulServiceRst)
    {
        Gmm_ComStaChg(GMM_REGISTERED_UPDATE_NEEDED);
    }
    else if ( MMC_LMM_SERVICE_RSLT_AUTH_REJ ==  pstLmmServiceRsltMsg->ulServiceRst)
    {
        NAS_GMM_RcvLmmAuthResult(pstMsg);
    }
    else
    {

    }

    return ;
}


VOS_VOID  NAS_GMM_RcvLmmAuthResult(
    VOS_VOID                           *pstMsg
)
{
    /*set the GPRS update status to GU3 ROAMING NOT ALLOWED*/
    NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_PLMN_NOT_ALLOWED);

    /* ����PS����Ч*/
    NAS_MML_SetSimPsRegStatus(VOS_FALSE);

    /*delete P-TMSI, P-TMSI signature, RAI and GPRS ciphering key sequence number */
    Gmm_DelPsLocInfoUpdateUsim();

    /*Ǩ��GMM-DEREGISTERED.NOIMSI;*/
    Gmm_ComStaChg(GMM_DEREGISTERED_NO_IMSI);

    /* ���UEID�е�IMSI��־λ */
    NAS_GMM_ClearIMSIOfUeID();

    return ;
}
VOS_UINT32  NAS_GMM_MapPtmsiFromGUTI( VOS_VOID )
{
     /*GUTI STRUC
     23.003  2.8.2.1.2
     E UTRAN <M-TMSI> maps as follows:
     -   6 bits of the E UTRAN <M-TMSI> starting at bit 29 and down to bit 24 are mapped into bit 29 and down to bit 24 of the GERAN/UTRAN <P TMSI>;
     -   16 bits of the E UTRAN <M-TMSI> starting at bit 15 and down to bit 0 are mapped into bit 15 and down to bit 0 of the GERAN/UTRAN <P TMSI>;
     E UTRAN <MME Code> maps to GERAN/UTRAN <RAC> and is also copied into the 8 most significant bits of the NRI field within the P TMSI;

    ��23.003  2.8.2.0
    P TMSI shall be of 32 bits length where the two topmost bits are reserved and always set to 11. */

    /*
    -----------------------------------------------------------------------------
    | oct10  | oct 9  | oct8   |   oct7     | oct 6       | oct5        |  oct4       |   oct3      |oct2        | oct1          |
    -----------------------------------------------------------------------------
    |        MCC  |     MNC     |  MMEGI | MMEGI  |  MMEC  |  MTMSI   |  MTMSI  | MTMSI  | MTMSI     |
    -----------------------------------------------------------------------------
    |                                        |                                   |\                |\  |           /                /                                /
    |                                        |                                   |     \           |   \            /                /                                /
    |                                        |                                   |         \       |   |  \        /                /                                /
    |                                        |                                   |              \  |   |     \     /                /                                /
    |                                        |                                   |                  \   |           \                  /                               /
    |                                        |                                   |                 |   \            /\                /                               /
    |                                        |                                   |                 |   |   \      /      \           /                               /
    |                                        |                                   |                 |   |        \  /         \       /                               /
    |                                        |                                   |                 |   |          \/             \   /                               /
    ----------------------------------------------------------------------------
    |      MCC    |    MNC     |   LAC     |   LAC      |    RAC    |  PTMSI   |  PTMSI   | PTMSI  | PTMSI     |
    -----------------------------------------------------------------------------
    | oct10  | oct 9  | oct8   |   oct7     | oct 6       |  oct5       |   oct4      |   oct3       | oct2      |  oct1         |
     -----------------------------------------------------------------------------
     LAI,RAI,PTMSI STRUC
    */

    NAS_LMM_INFO_STRU                   stLmmInfo;
    NAS_LMM_GUTI_STRU                  *pstGutiInfo = VOS_NULL_PTR;
    VOS_UINT8                           aucPtmsi[NAS_MML_MAX_PTMSI_LEN];


    /* �����ӿں���Nas_GetLteInfo��ȡL�����е�GUTI */
    pstGutiInfo                         = &(stLmmInfo.u.stGuti);

    if ( VOS_FALSE ==  NAS_GMM_GetLteGutiValid())
    {
        return VOS_ERR;
    }


    /* GUTI��Чֱ�ӷ���VOS_ERR */
    if ( VOS_TRUE != NAS_GMM_GetLteInfo( NAS_LMM_GUTI, &stLmmInfo ) )
    {
        return VOS_ERR;
    }

    aucPtmsi[0]                         = ( pstGutiInfo->stMTmsi.ucMTmsi & 0x3f ) | 0xc0 ;
    aucPtmsi[1]                         = pstGutiInfo->stMmeCode.ucMmeCode;
    aucPtmsi[2]                         = pstGutiInfo->stMTmsi.ucMTmsiCnt2;
    aucPtmsi[3]                         = pstGutiInfo->stMTmsi.ucMTmsiCnt3;

    /* ��PTMSI������ȫ�ֱ�����ȥ */
    PS_MEM_CPY(NAS_GMM_GetMappedPtmsiAddr(), aucPtmsi, NAS_MML_MAX_PTMSI_LEN);


    return VOS_OK;
}
VOS_UINT32  NAS_GMM_MapRaiFromGUTI( VOS_VOID )
{
    /*23.003  2.8.2.1.2
    E UTRAN <MCC> maps to GERAN/UTRAN <MCC>
    E UTRAN <MNC> maps to GERAN/UTRAN <MNC>
    E UTRAN <MME Group ID> maps to GERAN/UTRAN <LAC>
    E UTRAN <MME Code> maps to GERAN/UTRAN <RAC> and is also copied into the 8 most significant bits of the NRI field within the P TMSI;
    */
    /*GUTI STRUC
       -----------------------------------------------------------------------------
       | oct10  | oct 9  | oct8   |   oct7     | oct 6       | oct5        |  oct4       |   oct3      |oct2        | oct1
       -----------------------------------------------------------------------------
       |        MCC  |     MNC     |  MMEGI | MMEGI  |  MMEC  |  MTMSI   |  MTMSI  | MTMSI  | MTMSI
       -----------------------------------------------------------------------------
       |                                        |                                   |\                |\  |           |                |
       |                                        |                                   |     \           |   \            |                |
       |                                        |                                   |         \       |   |  \        |                |
       |                                        |                                   |              \  |   |     \    |                 |
       |                                        |                                   |                  \   |           \                 |
       |                                        |                                   |                 |   \            | \              |
       |                                        |                                   |                 |   |     \     |     \          |
       |                                        |                                   |                 |   |        \   |         \     |
       |                                        |                                   |                 |  |          \  |            \  |
       -----------------------------------------------------------------------------
       |      MCC    |    MNC     |   LAC     |   LAC      |    RAC     |  PTMSI  |  PTMSI   | PTMSI  | PTMSI
       -----------------------------------------------------------------------------
       | oct10  | oct 9  | oct8   |   oct7     | oct 6       |  oct5       |   oct4      |   oct3       | oct2      |  oct1
        -----------------------------------------------------------------------------
        LAI,RAI,PTMSI STRUC
       */

    NAS_LMM_INFO_STRU                   stLmmInfo;
    NAS_LMM_GUTI_STRU                  *pstGutiInfo = VOS_NULL_PTR;
    GMM_RAI_STRU                        stRai;

    if ( VOS_FALSE ==  NAS_GMM_GetLteGutiValid())
    {
        return VOS_ERR;
    }


    /* �����ӿں���Nas_GetLteInfo��ȡL�����е�GUTI */
    /* GUTI��Чֱ�ӷ���VOS_ERR */
    if ( VOS_TRUE != NAS_GMM_GetLteInfo( NAS_LMM_GUTI, &stLmmInfo ) )
    {
        return VOS_ERR;
    }

    pstGutiInfo                         = &(stLmmInfo.u.stGuti);

    /* ��ȡPLMN��Ϣ */
    NAS_GMM_ConvertLmmPlmnToGmmPlmnId( &(pstGutiInfo->stPlmnId), &(stRai.Lai.PlmnId) );

    /* ��ȡLAC��Ϣ */
    stRai.Lai.aucLac[0]                 = pstGutiInfo->stMmeGroupId.ucGroupId;
    stRai.Lai.aucLac[1]                 = pstGutiInfo->stMmeGroupId.ucGroupIdCnt;

    /* ��ȡRAC��Ϣ */
    stRai.ucRac                         = pstGutiInfo->stMmeCode.ucMmeCode;

    /* raiд��ȫ�ֱ��� */
    NAS_GMM_SetMappedRai(stRai);
    return VOS_OK;
}



VOS_UINT32  NAS_GMM_MapLaiFromGUTI( VOS_VOID )
{
    /*23.003  2.8.2.1.2
    E UTRAN <MCC> maps to GERAN/UTRAN <MCC>
    E UTRAN <MNC> maps to GERAN/UTRAN <MNC>
    E UTRAN <MME Group ID> maps to GERAN/UTRAN <LAC>
    E UTRAN <MME Code> maps to GERAN/UTRAN <RAC> and is also copied into the 8 most significant bits of the NRI field within the P TMSI;
    */

    /*GUTI STRUC
       -----------------------------------------------------------------------------
       | oct10  | oct 9  | oct8   |   oct7     | oct 6       | oct5        |  oct4       |   oct3      |oct2        | oct1
       -----------------------------------------------------------------------------
       |        MCC  |     MNC     |  MMEGI | MMEGI  |  MMEC  |  MTMSI   |  MTMSI  | MTMSI  | MTMSI
       -----------------------------------------------------------------------------
       |                                        |                                   |\                |\  |           |                |
       |                                        |                                   |     \           |   \            |                |
       |                                        |                                   |         \       |   |  \        |                |
       |                                        |                                   |              \  |   |     \    |                 |
       |                                        |                                   |                  \   |           \                 |
       |                                        |                                   |                 |   \            | \              |
       |                                        |                                   |                 |   |     \     |     \          |
       |                                        |                                   |                 |   |        \   |         \     |
       |                                        |                                   |                 |  |          \  |            \  |
       -----------------------------------------------------------------------------
       |      MCC    |    MNC     |   LAC     |   LAC      |    RAC     |  PTMSI  |  PTMSI   | PTMSI  | PTMSI
       -----------------------------------------------------------------------------
       | oct10  | oct 9  | oct8   |   oct7     | oct 6       |  oct5       |   oct4      |   oct3       | oct2      |  oct1
        -----------------------------------------------------------------------------
        LAI,RAI,PTMSI STRUC
       */

    NAS_LMM_INFO_STRU                   stLmmInfo;
    NAS_LMM_GUTI_STRU                  *pstGutiInfo = VOS_NULL_PTR;
    GMM_LAI_STRU                        stLai;

    if ( VOS_FALSE ==  NAS_GMM_GetLteGutiValid())
    {
        return VOS_ERR;
    }

    /* �����ӿں���Nas_GetLteInfo��ȡL�����е�GUTI */
    /* GUTI��Чֱ�ӷ���VOS_ERR */
    if ( VOS_TRUE != NAS_GMM_GetLteInfo( NAS_LMM_GUTI, &stLmmInfo ) )
    {
        return VOS_ERR;
    }

    pstGutiInfo                         = &(stLmmInfo.u.stGuti);

    /* ��ȡPLMN��Ϣ */
    NAS_GMM_ConvertLmmPlmnToGmmPlmnId( &(pstGutiInfo->stPlmnId), &(stLai.PlmnId) );

    /* ��ȡLAC��Ϣ */
    stLai.aucLac[0]                     = pstGutiInfo->stMmeGroupId.ucGroupId;
    stLai.aucLac[1]                     = pstGutiInfo->stMmeGroupId.ucGroupIdCnt;


    /* Laiд��ȫ�ֱ��� */
    NAS_GMM_SetMappedLai(stLai);

    return VOS_OK;
}
VOS_UINT32  NAS_GMM_MapPtmsiSignFromGUTIAndNasToken( VOS_VOID )
{
    /* 23.003  2.8.2.1.2
    E UTRAN <M-TMSI> maps as follows:
    -   6 bits of the E UTRAN <M-TMSI> starting at bit 29 and down to bit 24 are mapped into bit 29 and down to bit 24 of the GERAN/UTRAN <P TMSI>;
    -   16 bits of the E UTRAN <M-TMSI> starting at bit 15 and down to bit 0 are mapped into bit 15 and down to bit 0 of the GERAN/UTRAN <P TMSI>;
    -   and the remaining 8 bits of the E UTRAN <M-TMSI> are mapped into the 8 MBS bits of the <P-TMSI signature> field.
    The remaining 2 octets of the <P-TMSI signature> shall be filled according to subclause 9.1.1 in 3GPP TS.33.401 [89].
    ��33.401  9.1.1
    The x bits available in the P-TMSI signature field (at minimum 16 bits) shall be filled with the truncated NAS-token, which is defined as the x least significant bits of the NAS-token.*/

    NAS_LMM_INFO_STRU                   stLmmInfo;
    VOS_UINT8                          *pucPtmsiSignature = VOS_NULL_PTR;
    VOS_UINT8                          *pucNasToken       = VOS_NULL_PTR;
    NAS_LMM_GUTI_STRU                  *pstGutiInfo       = VOS_NULL_PTR;

    pucPtmsiSignature                   = NAS_GMM_GetMappedPtmsiSignAddr();
    pucNasToken                         = NAS_GMM_GetNasTokenAddr();

    if ( VOS_FALSE ==  NAS_GMM_GetLteGutiValid())
    {
        return VOS_ERR;
    }

    /* �����ӿں���Nas_GetLteInfo��ȡL�����е�GUTI */
    /* GUTI��Чֱ�ӷ���VOS_ERR */
    if ( VOS_TRUE != NAS_GMM_GetLteInfo( NAS_LMM_GUTI, &stLmmInfo ) )
    {
        return VOS_ERR;
    }

    pstGutiInfo                         = &(stLmmInfo.u.stGuti);

    pucPtmsiSignature[0]                = pstGutiInfo->stMTmsi.ucMTmsiCnt1;
    pucPtmsiSignature[1]                = pucNasToken[NAS_GMM_LMM_TOKEN_LEN-2];
    pucPtmsiSignature[2]                = pucNasToken[NAS_GMM_LMM_TOKEN_LEN-1];

    return VOS_OK;
}


VOS_UINT32 NAS_GMM_IsGutiInfoValid( VOS_VOID )
{
    NAS_LMM_INFO_STRU                   stLmmInfo;

    if ( VOS_FALSE ==  NAS_GMM_GetLteGutiValid())
    {
        return VOS_FALSE;
    }

    /* �����ӿں���Nas_GetLteInfo��ȡL�����е�GUTI */
    /* GUTI��Чֱ�ӷ���VOS_FALSE */
    if ( VOS_TRUE != NAS_GMM_GetLteInfo( NAS_LMM_GUTI, &stLmmInfo ) )
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}



VOS_VOID NAS_GMM_GetGUSecContextFromEpsSecContextInHandOver(
    struct MsgCB                       *pstMsg
)
{
    LMM_GMM_HO_SECU_INFO_CNF_STRU      *pstHandOverMsg  = VOS_NULL_PTR;
    VOS_UINT8                          *pucNasToken     = VOS_NULL_PTR;
    VOS_UINT8                          *pucDestBuffer   = VOS_NULL_PTR;
    VOS_VOID                           *pucSrcBuffer    = VOS_NULL_PTR;

    VOS_UINT8                           ucCksn;
    VOS_UINT32                          ulCount;

    ulCount                             = 0;
    pstHandOverMsg                      = ( LMM_GMM_HO_SECU_INFO_CNF_STRU * )pstMsg;
    pucNasToken                         = NAS_GMM_GetNasTokenAddr();

    /*LMMδ����ӳ���UMTS��ȫ������,�뽫NAS TOKEN�ó�0��GPRSCKSN�ó���Чֵ����24008:4.7.3.1.1
    If a current EPS security does not exist, the MS shall set the truncated NAS token included in the P-TMSI signature to all zeros
    and the GPRS ciphering key sequence number to "No key is available"
    */
    if ( ( LMM_GMM_SECU_INFO_RSLT_FAIL      == pstHandOverMsg->enRslt )
      || ( 0 == pstHandOverMsg->bitOpSecuCntxt ) )
    {
        /* GUTI��Ч���һ�ȡGUTI�ɹ�ʱ����NAS TOKEN�ó�0��GPRS CKSN�ó���Чֵ
           �����ʹ�ñ��صģ�����LTEӳ�� */
        if (VOS_TRUE == NAS_GMM_IsGutiInfoValid())
        {
            PS_MEM_SET( pucNasToken, 0, LMM_GMM_NAS_TOKEN_LEN );
            NAS_MML_SetSimPsSecurityCksn(NAS_MML_CKSN_INVALID);
        }

        return;
    }

    /* ��LMM��ȡaucCk��Ϣ */
    pucDestBuffer                   = NAS_MML_GetSimPsSecurityUmtsCk();
    pucSrcBuffer                    = pstHandOverMsg->stHoUmtsSecuCntxt.aucUmtsCk;
    ulCount                         = LMM_GMM_CK_LEN;
    PS_MEM_CPY(pucDestBuffer, pucSrcBuffer, ulCount);

    /* ��LMM��ȡaucIk��Ϣ */
    pucDestBuffer                   = NAS_MML_GetSimPsSecurityUmtsIk();
    pucSrcBuffer                    = pstHandOverMsg->stHoUmtsSecuCntxt.aucUmtsIk;
    ulCount                         = LMM_GMM_IK_LEN;
    PS_MEM_CPY(pucDestBuffer, pucSrcBuffer, ulCount);

    /* ��LMM��ȡucCksn��Ϣ */
    ucCksn                          = (VOS_UINT8) pstHandOverMsg->stHoUmtsSecuCntxt.KSI;
    NAS_MML_SetSimPsSecurityCksn(ucCksn);


    /*����CK,IK��C3�㷨����Kc*/
    NAS_MML_SecContext3GTO2G(NAS_MML_GetSimPsSecurityUmtsIk(),
                             NAS_MML_GetSimPsSecurityUmtsCk(),
                             NAS_MML_GetSimPsSecurityGsmKc());

    /*��UMTSSecurityContext��CK,IK,KSI,Kc,GprsCKSN���浽USIM;����CK,IK,Kcֵ��SIM�� */
    if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
    {/* 3G USIM */
        /* Modified by h00313353 for iteration 9, 2015-2-4, begin */
        Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKEYSPS_ID);      /* ����SIM�е�CKSN,Ck,IK*/
        Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKCGPRS_ID);      /* ����SIM�е�GSM CKSN,Kc*/
    }
    else
    {/* 2G SIM */
        Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFKCGPRS_ID);   /* ����SIM�е�GSM CKSN,Kc*/
        /* Modified by h00313353 for iteration 9, 2015-2-4, end */
    }

    return;
}
VOS_VOID NAS_GMM_GetGUSecContextFromEpsSecContextInReselect(
    struct MsgCB                       *pstMsg
)
{
    LMM_GMM_RESEL_SECU_INFO_CNF_STRU   *pstReselMsg     = VOS_NULL_PTR;
    VOS_UINT8                          *pucNasToken     = VOS_NULL_PTR;
    VOS_UINT8                          *pucDestBuffer   = VOS_NULL_PTR;
    VOS_VOID                           *pucSrcBuffer    = VOS_NULL_PTR;

    VOS_UINT8                           ucCksn;
    VOS_UINT32                          ulCount;

    ulCount                             = 0;
    pstReselMsg                         = ( LMM_GMM_RESEL_SECU_INFO_CNF_STRU * )pstMsg;
    pucNasToken                         = NAS_GMM_GetNasTokenAddr();

    /*LMMδ����ӳ���UMTS��ȫ������,�뽫NAS TOKEN�ó�0��GPRSCKSN�ó���Чֵ����24008:4.7.3.1.1
    If a current EPS security does not exist, the MS shall set the truncated NAS token included in the P-TMSI signature to all zeros
    and the GPRS ciphering key sequence number to "No key is available"
    */
    if ( ( LMM_GMM_SECU_INFO_RSLT_FAIL      == pstReselMsg->enRslt )
      || ( 0 == pstReselMsg->bitOpSecuInfo ) )
    {
        /* GUTI��Ч���һ�ȡGUTI�ɹ�ʱ����NAS TOKEN�ó�0��GPRS CKSN�ó���Чֵ
           �����ʹ�ñ��صģ�����LTEӳ�� */
        if (VOS_TRUE == NAS_GMM_IsGutiInfoValid())
        {
            PS_MEM_SET( pucNasToken, 0, LMM_GMM_NAS_TOKEN_LEN );
            NAS_MML_SetSimPsSecurityCksn(NAS_MML_CKSN_INVALID);
        }

        return;
    }

    /* ��LMM��ȡaucCk��Ϣ */
    pucDestBuffer                   = NAS_MML_GetSimPsSecurityUmtsCk();
    pucSrcBuffer                    = pstReselMsg->stReselSecuInfo.stUmtsSecuContext.aucUmtsCk;
    ulCount                         = LMM_GMM_CK_LEN;
    PS_MEM_CPY(pucDestBuffer, pucSrcBuffer, ulCount);

    /* ��LMM��ȡaucIk��Ϣ */
    pucDestBuffer                   = NAS_MML_GetSimPsSecurityUmtsIk();
    pucSrcBuffer                    = pstReselMsg->stReselSecuInfo.stUmtsSecuContext.aucUmtsIk;
    ulCount                         = LMM_GMM_IK_LEN;
    PS_MEM_CPY(pucDestBuffer, pucSrcBuffer, ulCount);

    /* ��LMM��ȡucCksn��Ϣ */
    ucCksn                          = (VOS_UINT8) pstReselMsg->stReselSecuInfo.stUmtsSecuContext.KSI;
    NAS_MML_SetSimPsSecurityCksn(ucCksn);

    /* ��LMM��ȡaucNasToken��Ϣ */
    pucDestBuffer                   = NAS_GMM_GetNasTokenAddr();
    pucSrcBuffer                    = pstReselMsg->stReselSecuInfo.aucNasToken;
    ulCount                         = LMM_GMM_NAS_TOKEN_LEN;
    PS_MEM_CPY(pucDestBuffer, pucSrcBuffer, ulCount);

    /*����CK,IK��C3�㷨����Kc*/
    NAS_MML_SecContext3GTO2G(NAS_MML_GetSimPsSecurityUmtsIk(),
                             NAS_MML_GetSimPsSecurityUmtsCk(),
                             NAS_MML_GetSimPsSecurityGsmKc());

    /*��UMTSSecurityContext��CK,IK,KSI,Kc,GprsCKSN���浽USIM;����CK,IK,Kcֵ��SIM�� */
    if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
    {/* 3G USIM */
        /* Modified by h00313353 for iteration 9, 2015-2-4, begin */
        Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKEYSPS_ID);        /* ����SIM�е�CKSN,Ck,IK*/
        Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKCGPRS_ID);   /* ����SIM�е�GSM CKSN,Kc*/
    }
    else
    {/* 2G SIM */
        Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFKCGPRS_ID);   /* ����SIM�е�GSM CKSN,Kc*/
        /* Modified by h00313353 for iteration 9, 2015-2-4, end */
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_GetPtmsiInfo
 ��������  : ��ȡGU��PTMSI��ֵ
 �������  : ��
 �������  : pstPtmsi:GU PTMSI��ֵ
 �� �� ֵ  : VOS_OK:��ǰPTMSI������Ч
              VOS_ERR:��ǰPTMSI������Ч
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��5��23��
    ��    ��   : zhoujun /40661
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_GMM_GetPtmsiInfo(
    NAS_GUMM_PTMSI_STRU                 *pstPtmsi
)
{
    VOS_UINT8                           *pucSrcBuffer  = VOS_NULL_PTR;
    VOS_UINT32                           ulCount;
    VOS_UINT32                           i;

    /* ��ȡGUNAS���PTMSI��Ϣ */
    pucSrcBuffer                = NAS_MML_GetUeIdPtmsi();
    ulCount                     = NAS_MML_MAX_PTMSI_LEN;
    PS_MEM_CPY( pstPtmsi->aucPtmsi, pucSrcBuffer, ulCount );

    for ( i = 0 ; i < ulCount ; i++ )
    {
        if ( GMM_PTMSI_INVALID != pstPtmsi->aucPtmsi[i] )
        {
            break;
        }
    }

    /* PTMSIֵȫΪ0xFF */
    if ( i >= ulCount )
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_GetPtmsiSignature
 ��������  : ��ȡGU��PTMSI Signature��ֵ
 �������  : ��
 �������  : pstPtmsi:GU PTMSI��ֵ
 �� �� ֵ  : VOS_OK:��ǰPTMSI Signature������Ч
              VOS_ERR:��ǰPTMSI Signature������Ч
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��5��23��
    ��    ��   : zhoujun /40661
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_GMM_GetPtmsiSignature(
    NAS_GUMM_PTMSI_SIGNATURE_STRU       *pstPtmsiSignature
)
{
    VOS_UINT8                           *pucSrcBuffer  = VOS_NULL_PTR;
    VOS_UINT32                           ulCount;
    VOS_UINT32                           i;

    pucSrcBuffer                = NAS_MML_GetUeIdPtmsiSignature();
    ulCount                     = NAS_MML_MAX_PTMSI_SIGNATURE_LEN;
    PS_MEM_CPY( pstPtmsiSignature->aucPtmsiSign, pucSrcBuffer, ulCount );

    for ( i = 0 ; i < ulCount ; i++ )
    {
        if ( GMM_PTMSI_SIGNATURE_INVALID != pstPtmsiSignature->aucPtmsiSign[i] )
        {
            break;
        }
    }

    /* PTMSIֵȫΪ0xFF */
    if ( i >= ulCount )
    {
        return VOS_ERR;
    }

    return VOS_OK;
}
MMC_LMM_RESULT_ID_ENUM_UINT32  Nas_GetGuInfo(
    NAS_GUMM_INFO_TYPE_ENUM_UINT32      ulInfoType,
    NAS_GUMM_INFO_STRU                 *pstGuInfo
)
{
    /* ����������Դ��ַ,Ŀ�ĵ�ַ�Լ��������ֽڳ��� */
    VOS_UINT32                           ulRet;

    ulRet                               = VOS_OK;

    PS_MEM_SET( pstGuInfo, 0, sizeof( NAS_GUMM_INFO_STRU ) );

    switch (ulInfoType)
    {
        case NAS_GUMM_PTMSI:
            /* ��ȡGUNAS���PTMSI��Ϣ */
            ulRet = NAS_GMM_GetPtmsiInfo(&(pstGuInfo->u.stPtmsi));
            break;

        case NAS_GUMM_PTMSI_SIGNATURE:
            /* ��ȡGUNAS���PTMSI_SIGNATURE��Ϣ */
            ulRet = NAS_GMM_GetPtmsiSignature(&(pstGuInfo->u.stPtmsiSignature));
            break;

        case NAS_GUMM_LAI:
            /* pstGuInfo->u.stLai = ȫ�ֱ���.stLai;*/
            /* ��ȡGUNAS���LAI��Ϣ */
            ulRet = NAS_GMM_GetLaiInfo( &(pstGuInfo->u.stLai) );
            break;

        case NAS_GUMM_RAI:
            /* ��ȡGUNAS���RAI��Ϣ */
            ulRet = NAS_GMM_GetRaiInfo( &(pstGuInfo->u.stRAI));
            break;

        case NAS_GUMM_UMTS_SECU_PARA:
            /* ��GU NAS������ȫ������LMM */
            ulRet = NAS_GMM_GetGuSecuInfo( &(pstGuInfo->u.stSecuContext) );
            break;

        case NAS_GUMM_TMSI_STATUS:
            /* ��GU NAS��ȡTMSI��Ч����Ϣ */
            NAS_GMM_GetTmsiStatusInfo( &(pstGuInfo->u.ulTmsiStatus) );
            break;

        default:
            break;
    }

    if ( VOS_OK != ulRet )
    {
        return MMC_LMM_FAIL;
    }

    return MMC_LMM_SUCC;
}


VOS_UINT32  NAS_GMM_GetLaiInfo(
    MMC_LMM_LAI_STRU                    *pstLai
)
{
    /* ��ȡGUNAS���LAI��Ϣ */
    NAS_MML_PLMN_ID_STRU                stGUNasPlmn;
    NAS_MML_LAI_STRU                   *pstCsSuccLai = VOS_NULL_PTR;

    pstCsSuccLai    = NAS_MML_GetCsLastSuccLai( );

    PS_MEM_SET( &stGUNasPlmn, 0, sizeof( NAS_MML_PLMN_ID_STRU ) );

    /* ���ж�LAI�Ƿ���Ч, */
    if ( ( NAS_MML_LAC_LOW_BYTE_INVALID == pstCsSuccLai->aucLac[0])
      && ( NAS_MML_LAC_HIGH_BYTE_INVALID == pstCsSuccLai->aucLac[1]))
    {
        return VOS_ERR;
    }

    /* ��MM��PLMN idת��ΪLMM��ʽ��PLMN id */
    NAS_MML_ConvertNasPlmnToLMMFormat(&(pstLai->stPlmnId), &(pstCsSuccLai->stPlmnId));

    /* ���LACֵ */
    pstLai->stLac.ucLac                  = pstCsSuccLai->aucLac[0];
    pstLai->stLac.ucLacCnt               = pstCsSuccLai->aucLac[1];

    return VOS_OK;
}



VOS_UINT32  NAS_GMM_GetRaiInfo(
    MMC_LMM_RAI_STRU                   *pstRai
)
{
    NAS_MML_RAI_STRU                   *pstRaiInfo = VOS_NULL_PTR;

    /* ��ȡGUNAS���LAI��Ϣ */
    NAS_MML_PLMN_ID_STRU                stGUNasPlmn;

    PS_MEM_SET( &stGUNasPlmn, 0, sizeof( NAS_MML_PLMN_ID_STRU ) );

    pstRaiInfo  = NAS_MML_GetPsLastSuccRai();

    /* ���ж�LAI�Ƿ���Ч, */
    if ( ( NAS_MML_LAC_LOW_BYTE_INVALID == pstRaiInfo->stLai.aucLac[0])
      && ( NAS_MML_LAC_HIGH_BYTE_INVALID == pstRaiInfo->stLai.aucLac[1]))
    {
        return VOS_ERR;
    }

    /* ��GMM��PLMN idת��ΪLMM��ʽ��PLMN id */
    NAS_MML_ConvertNasPlmnToLMMFormat(&(pstRai->stLai.stPlmnId), &(pstRaiInfo->stLai.stPlmnId));

    /* ���LACֵ */
    pstRai->stLai.stLac.ucLac                  = pstRaiInfo->stLai.aucLac[0];
    pstRai->stLai.stLac.ucLacCnt               = pstRaiInfo->stLai.aucLac[1];


    /* ��ȡRAC��ֵ */
    pstRai->ucRac   = pstRaiInfo->ucRac;

    return VOS_OK;
}
VOS_VOID  NAS_GMM_GetTmsiStatusInfo(
    MMC_LMM_TMSI_STATUS_TYPE_ENUM_UINT32 *ulTmsiStatus
)
{
    VOS_UINT8                           ucMsIdFlg;

    ucMsIdFlg                           = NAS_MM_GetMsIdFlg();

    /* TMSI�Ƿ�����Լ�� */
    if ( MM_MS_ID_TMSI_PRESENT == ( MM_MS_ID_TMSI_PRESENT & ucMsIdFlg ) )
    {
        *ulTmsiStatus               = MMC_LMM_TMSI_STATUS_VALID;
        return ;
    }

    *ulTmsiStatus                       = MMC_LMM_TMSI_STATUS_INVALID;

    return ;
}



VOS_UINT32  NAS_GMM_GetGuSecuInfo(
    NAS_GUMM_UMTS_CONTEXT_STRU         *pstSecuContext
)
{
    /* ����������Դ��ַ,Ŀ�ĵ�ַ�Լ��������ֽڳ��� */
    VOS_UINT8                          *pucDestBuffer = VOS_NULL_PTR;
    VOS_UINT8                          *pucSrcBuffer  = VOS_NULL_PTR;
    VOS_UINT32                          ulCount;
    VOS_UINT32                          i;

    ulCount                             = 0;
    PS_MEM_SET( pstSecuContext, 0, sizeof( NAS_GUMM_UMTS_CONTEXT_STRU ) );

    /* ��ȡGUNAS���ucKSI��Ϣ */
    pstSecuContext->ucKSI               = NAS_MML_GetSimPsSecurityCksn();
    if ( NAS_MML_CKSN_INVALID == pstSecuContext->ucKSI )
    {
        return VOS_ERR;
    }

    /* ��ȡGUNAS���aucCK��Ϣ */
    pucDestBuffer                       = pstSecuContext->aucCK;
    pucSrcBuffer                        = NAS_MML_GetSimPsSecurityUmtsCk();
    ulCount                             = LMM_GMM_CK_LEN;
    PS_MEM_CPY( pucDestBuffer, pucSrcBuffer, ulCount );
    for ( i = 0 ; i < LMM_GMM_CK_LEN ; i++ )
    {
        if ( pucDestBuffer[i]  != GMM_CK_INVALID )
        {
            break;
        }
    }
    if ( i >= LMM_GMM_CK_LEN )
    {
        return VOS_ERR;
    }


    /* ��ȡGUNAS���aucIK��Ϣ */
    pucDestBuffer                       = (VOS_UINT8*)pstSecuContext->aucIK;
    pucSrcBuffer                        = NAS_MML_GetSimPsSecurityUmtsIk();
    ulCount                             = LMM_GMM_IK_LEN;
    PS_MEM_CPY( pucDestBuffer, pucSrcBuffer, ulCount );
    for ( i = 0 ; i < LMM_GMM_IK_LEN ; i++ )
    {
        if ( pucDestBuffer[i]  != GMM_IK_INVALID )
        {
            break;
        }
    }
    if ( i >= LMM_GMM_IK_LEN )
    {
        return VOS_ERR;
    }

    return VOS_OK;
}



VOS_VOID NAS_GMM_ConvertLmmPlmnToGmmPlmnId(
    MMC_LMM_PLMN_ID_STRU                *pstLmmPlmn,
    GMM_PLMN_ID_STRU                    *pstGmmPlmn
)
{
    /* ��LMM�Ĺ��Һ�ת��ΪGMM�Ĺ��Һ���ʽ */
    pstGmmPlmn->aucMccDigit[0]          = (pstLmmPlmn->aucPlmnId[0]) & 0x0F;
    pstGmmPlmn->aucMccDigit[1]          = (pstLmmPlmn->aucPlmnId[0]) >> 4;
    pstGmmPlmn->aucMccDigit[2]          = (pstLmmPlmn->aucPlmnId[1]) & 0x0F;

    /* ��LMM�������ת��ΪGMM���������ʽ */
    pstGmmPlmn->aucMncDigit[0]          = (pstLmmPlmn->aucPlmnId[2]) & 0x0F;
    pstGmmPlmn->aucMncDigit[1]          = (pstLmmPlmn->aucPlmnId[2]) >> 4;
    pstGmmPlmn->aucMncDigit[2]          = (pstLmmPlmn->aucPlmnId[1]) >> 4;

    /* �ж�����ŵ�λ������ֵ */
    pstGmmPlmn->ucMncCnt                = 3;

    if ( 0x0F == pstGmmPlmn->aucMncDigit[2] )
    {
        pstGmmPlmn->ucMncCnt            = 2;
    }

    return ;
}
VOS_VOID  NAS_GMM_ProcLmmRejCause3( VOS_VOID )
{
    /*3GPP TS 24.301 V9.5.0 (2010-12) 5.5.1.2.5
   #3  (Illegal UE); or
   #6  (Illegal ME);
       The UE shall set the EPS update status to EU3 ROAMING NOT
       ALLOWED (and shall store it according to subclause 5.1.3.3)
       and shall delete any GUTI, last visited registered TAI and eKSI.
       The UE shall consider the USIM as invalid for EPS services
       and non-EPS services until switching off or the UICC containing
       the USIM is removed. Additionally, the UE shall delete the list
       of equivalent PLMNs and enter state EMM-DEREGISTERED.

       If A/Gb mode or Iu mode is supported by the UE, the UE shall
       in addition handle the MM parameters update status, TMSI,
       LAI and ciphering key sequence number, and the GMM parameters
       GMM state, GPRS update status, P-TMSI, P-TMSI signature,
       RAI and GPRS ciphering key sequence number as specified
       in 3GPP TS 24.008 [13] for the case when the normal
       attach procedure is rejected with the GMM cause with the same value.
    */

    /* 3GPP TS 24.301 V9.5.0 (2010-12) 5.5.3.2.5
 #3  (Illegal UE);
 #6   Illegal ME); or
 #8  (EPS services and non-EPS services not allowed);
         The UE shall set the EPS update status to EU3 ROAMING
         NOT ALLOWED (and shall store it according to subclause 5.1.3.3)
         and shall delete any GUTI, last visited registered TAI, TAI Listand eKSI.
         The UE shall consider the USIM as invalid for EPS
         and non-EPS services until switching off or the
         UICC containing the USIM is removed. Additionally,
         the UE shall delete the list of equivalent PLMNs
         and shall enter the state EMM-DEREGISTERED.
         If A/Gb mode or Iu mode is supported by the UE,
         the UE shall handle the MM parameters update status, TMSI,
         LAI and ciphering key sequence number, and the GMM parameters
         GMM state, GPRS update status, P-TMSI, P-TMSI signature,
         RAI and GPRS ciphering key sequence number as specified
         in 3GPP TS 24.008 [13] for the case when the combined routing area
         updating procedure is rejected with the GMM cause with the same value.
     */

    /*set the GPRS update status to GU3 ROAMING NOT ALLOWED*/
    NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_PLMN_NOT_ALLOWED);

    /* ����GMM�Ŀ���Ч */
    NAS_MML_SetSimPsRegStatus(VOS_FALSE);

    /*delete P-TMSI, P-TMSI signature, RAI and GPRS ciphering key sequence number */
    Gmm_DelPsLocInfoUpdateUsim();

    /*Ǩ��GMM-DEREGISTERED.NOIMSI;*/
    Gmm_ComStaChg(GMM_DEREGISTERED_NO_IMSI);


    /* �����ر�־ */
    NAS_GMM_ClearIMSIOfUeID();
}
VOS_VOID NAS_GMM_LogGutiInfo(
    NAS_LMM_GUTI_STRU                  *pstGuti
)
{
    NAS_GMM_LOG_GUTI_INFO_STRU         *pstGutiMsg = VOS_NULL_PTR;

    pstGutiMsg = (NAS_GMM_LOG_GUTI_INFO_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMC,
                             sizeof(NAS_GMM_LOG_GUTI_INFO_STRU));
    if ( VOS_NULL_PTR == pstGutiMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_LogGutiInfo:ERROR:Alloc Mem Fail.");
        return;
    }

    pstGutiMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstGutiMsg->stMsgHeader.ulSenderPid     = PS_PID_MM;
    pstGutiMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_GMM;
    pstGutiMsg->stMsgHeader.ulLength        = sizeof(pstGutiMsg->stGutiMsg) + 4;
    pstGutiMsg->stMsgHeader.ulMsgName       = NAS_GMM_LOG_GUTI_INFO_IND;

    PS_MEM_CPY(&(pstGutiMsg->stGutiMsg), pstGuti, sizeof(NAS_LMM_GUTI_STRU));

    DIAG_TraceReport(pstGutiMsg);

    PS_MEM_FREE(WUEPS_PID_GMM, pstGutiMsg);

    return;
}
/*lint -restore */

#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

