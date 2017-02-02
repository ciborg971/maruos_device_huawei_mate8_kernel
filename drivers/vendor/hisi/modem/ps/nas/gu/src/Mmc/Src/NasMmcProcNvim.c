
/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "NasMmlCtx.h"
#include "NasMmcCtx.h"
#include "NasMmcProcNvim.h"
#include "NasComm.h"
/* Deleted by h00313353 for iteration 9, 2015-2-13, begin */

/* Deleted by h00313353 for iteration 9, 2015-2-13, end */
#include "NasMmlLib.h"
#include "NasMmcProcUsim.h"
#include "pscfg.h"
#include "NasMmcSndOm.h"
#include "NasUsimmApi.h"
#if (FEATURE_LTE == FEATURE_ON)
#include "msp_nvim.h"
#include "LNvCommon.h"
#include "LNasNvInterface.h"
#include "LPsNvInterface.h"
#include "ImsaNvInterface.h"

#include "NasMmcSndLmm.h"
#endif

#include "ScInterface.h"
#include "NasNvInterface.h"
#include "TafNvInterface.h"


/* DSDSʹ��NV��TTF��ȡ */
#include "TtfNvInterface.h"
#include "WasNvInterface.h"

#include "NasMmcComFunc.h"

/* Added by c00318887 for file refresh��Ҫ����������, 2015-4-28, begin */
#include "SysNvId.h"
/* Added by c00318887 for file refresh��Ҫ����������, 2015-4-28, end */

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_MMC_PROC_NIVM_C

/*****************************************************************************
  2 ȫ�ֱ���
*****************************************************************************/

/*****************************************************************************
  3 �궨��
*****************************************************************************/

/*lint -save -e958 */

VOS_VOID NAS_MMC_ReadCsOnlyDataServiceSupportNvim( VOS_VOID )
{
    NAS_MML_CS_ONLY_DATA_SERVICE_SUPPORT_FLG_STRU           stCsOnlyDataServiceSupportFlg;
    NAS_MML_MISCELLANEOUS_CFG_INFO_STRU                    *pstMiscellaneousCfgInfo = VOS_NULL_PTR;

    pstMiscellaneousCfgInfo = NAS_MML_GetMiscellaneousCfgInfo();

    PS_MEM_SET(&stCsOnlyDataServiceSupportFlg, 0, sizeof(stCsOnlyDataServiceSupportFlg));
    if (NV_OK != NV_Read(en_NV_Item_CS_ONLY_DATA_SERVICE_SUPPORT_FLG,
                         &stCsOnlyDataServiceSupportFlg,
                         sizeof(stCsOnlyDataServiceSupportFlg)))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC,
           "NAS_MMC_ReadCsOnlyDataServiceSupportNvim():WARNING: en_NV_Item_CS_ONLY_DATA_SERVICE_SUPPORT_FLG Error");

        return;
    }


    if (NAS_MMC_NV_ITEM_ACTIVE != stCsOnlyDataServiceSupportFlg.ucActiveFlg)
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC,
           "NAS_MMC_ReadCsOnlyDataServiceSupportNvim(): NV deactive.");
        return;
    }

    if (0 != stCsOnlyDataServiceSupportFlg.ucCsOnlyDataServiceSupportFlg)
    {
        stCsOnlyDataServiceSupportFlg.ucCsOnlyDataServiceSupportFlg = VOS_TRUE;
    }

    pstMiscellaneousCfgInfo->ucCsOnlyDataServiceSupportFlg
             = stCsOnlyDataServiceSupportFlg.ucCsOnlyDataServiceSupportFlg;

    return;

}


VOS_VOID NAS_MMC_ReadLteDisabledUseLteInfoFlagNvim(VOS_VOID)
{
    NAS_MMC_LTE_DISABLED_USE_LTE_INFO_FLAG_STRU             stLDisabledUseLInfoFlag;
    VOS_UINT32                                              ulLength;

    ulLength                = 0;
    PS_MEM_SET(&stLDisabledUseLInfoFlag, 0, sizeof(stLDisabledUseLInfoFlag));

    /* �Ȼ�ȡNV�ĳ��� */
    (VOS_VOID)NV_GetLength(en_NV_Item_LTE_DISABLED_USE_LTE_INFO_FLAG, &ulLength);

    if (ulLength > sizeof(NAS_MMC_LTE_DISABLED_USE_LTE_INFO_FLAG_STRU))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadLteDisabledUseLteInfoFlagNvim(): nv length Error");
        return;
    }

    if (NV_OK != NV_Read(en_NV_Item_LTE_DISABLED_USE_LTE_INFO_FLAG,
                         &stLDisabledUseLInfoFlag, ulLength))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC,
           "NAS_MMC_ReadLteDisabledUseLteInfoFlagNvim():WARNING: NV read Error");

        return;
    }

    /* ���Կ�nv��Ĭ�Ͽ���*/
    if ((VOS_TRUE == NAS_USIMMAPI_IsTestCard())
     || (VOS_TRUE == stLDisabledUseLInfoFlag.ucLDisabledRauUseLInfoFlag))
    {
        NAS_MML_SetLteDisabledRauUseLteInfoFlag(VOS_TRUE);
    }

    return;
}



VOS_VOID NAS_MMC_ReadWgRfMainBandNvim( VOS_VOID )
{
    NAS_NVIM_WG_RF_MAIN_BAND_STRU       stRfMainBand;
    VOS_UINT32                          ulDataLen;

    ulDataLen = 0;

    PS_MEM_SET(&stRfMainBand, 0x00, sizeof(stRfMainBand));

    (VOS_VOID)NV_GetLength(en_NV_Item_WG_RF_MAIN_BAND, &ulDataLen);

    if (NV_OK != NV_Read(en_NV_Item_WG_RF_MAIN_BAND, &stRfMainBand, ulDataLen))
    {
        /*��ӡδ�ɹ���ʼ��ֵ��ԭֵ����*/
        NAS_ERROR_LOG(WUEPS_PID_MMC,
                     "NAS_MMC_ReadWgRfMainBandNvim():Read en_NV_Item_WG_RF_MAIN_BAND Failed!");
        return;
    }

    NAS_MML_SetGsmBandCapability(stRfMainBand.ulGband);

    return;
}



VOS_VOID NAS_MMC_ReadLauRejTrigPlmnSearchNvim( VOS_VOID )
{
    NAS_NVIM_LAU_REJ_TRIG_PLMN_SEARCH_CFG_STRU              stLauRejCfg;
    VOS_UINT32                                              ulLength;
    NAS_MML_LAU_REJ_TRIG_PLMN_SEARCH_STRU                  *pstLauRejCfg    = VOS_NULL_PTR;

    ulLength        = 0;
    pstLauRejCfg    = NAS_MML_GetLauRejTrigPlmnSearchCfg();

    PS_MEM_SET(&stLauRejCfg, 0, sizeof(NAS_NVIM_LAU_REJ_TRIG_PLMN_SEARCH_CFG_STRU));

    (VOS_VOID)NV_GetLength(en_NV_Item_LAU_REJ_TRIG_PLMN_SEARCH, &ulLength);
    if (ulLength > sizeof(NAS_NVIM_LAU_REJ_TRIG_PLMN_SEARCH_CFG_STRU))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC,
                     "NAS_MMC_ReadLauRejTrigPlmnSearchNvim():en_NV_Item_LAU_REJ_TRIG_PLMN_SEARCH Length Error");
        return;
    }


    if (NV_OK != NV_Read(en_NV_Item_LAU_REJ_TRIG_PLMN_SEARCH,
                         &stLauRejCfg, ulLength))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC,
                     "NAS_MMC_ReadLauRejTrigPlmnSearchNvim():en_NV_Item_LAU_REJ_TRIG_PLMN_SEARCH Error");

        return;
    }


    /* NV��ֵ��ȫ�ֱ����� */
    if (stLauRejCfg.ucCmSrvTrigPlmnSearchCauseNum   > NAS_NVIM_MAX_LAU_REJ_TRIG_PLMN_SEARCH_CAUSE_NUM)
    {
        stLauRejCfg.ucCmSrvTrigPlmnSearchCauseNum   = NAS_NVIM_MAX_LAU_REJ_TRIG_PLMN_SEARCH_CAUSE_NUM;
    }

    pstLauRejCfg->ucCmSrvExistTrigPlmnSearch        = stLauRejCfg.ucCmSrvExistTrigPlmnSearch;
    pstLauRejCfg->ucCmSrvTrigPlmnSearchCauseNum     = stLauRejCfg.ucCmSrvTrigPlmnSearchCauseNum;
    PS_MEM_CPY(pstLauRejCfg->aucCmSrvTrigPlmnSearchCause, stLauRejCfg.aucCmSrvTrigPlmnSearchCause, stLauRejCfg.ucCmSrvTrigPlmnSearchCauseNum);

    return;

}
VOS_VOID NAS_MMC_ReadLauRejNeedNoRetryWhenCmSrvExistNvim( VOS_VOID )
{
    NAS_MML_LAU_REJ_NORETRY_WHEN_CM_SRV_EXIST_CFG_STRU     *pstLauRejCfg = VOS_NULL_PTR;
    NAS_NVIM_LAU_REJ_NORETRY_WHEN_CM_SRV_EXIST_CFG_STRU     stLauRejCfg;
    VOS_UINT32                                              ulLength;
    VOS_UINT32                                              i;

    ulLength        = 0;
    i               = 0;

    PS_MEM_SET(&stLauRejCfg, 0, sizeof(NAS_NVIM_LAU_REJ_NORETRY_WHEN_CM_SRV_EXIST_CFG_STRU));

    (VOS_VOID)NV_GetLength(en_NV_Item_LAU_REJ_NORETRY_WHEN_CM_SRV_EXIST, &ulLength);
    if (ulLength > sizeof(NAS_NVIM_LAU_REJ_NORETRY_WHEN_CM_SRV_EXIST_CFG_STRU))
    {
        return;
    }

    pstLauRejCfg = NAS_MML_GetLauRejNoRetryWhenCmSrvExistCfgInfo();

    if (NV_OK != NV_Read(en_NV_Item_LAU_REJ_NORETRY_WHEN_CM_SRV_EXIST,
                         &stLauRejCfg, ulLength))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC,
                     "NAS_MMC_ReadLauRejNeedRetryWhenCmSrvExist():en_NV_Item_LAU_REJ_NORETRY_WHEN_CM_SRV_EXIST Error");

        return;
    }

    pstLauRejCfg->ucLauRejCauseNum  = stLauRejCfg.ucLauRejCauseNum;
    pstLauRejCfg->ucLauRejTimes     = stLauRejCfg.ucLauRejTimes;

    if (pstLauRejCfg->ucLauRejCauseNum > NAS_NVIM_MAX_REJECT_NO_RETRY_CAUSE_NUM)
    {
        pstLauRejCfg->ucLauRejCauseNum = NAS_NVIM_MAX_REJECT_NO_RETRY_CAUSE_NUM;
    }

    for (i = 0; i < pstLauRejCfg->ucLauRejCauseNum; i++)
    {
        pstLauRejCfg->aucLauRejCause[i] = stLauRejCfg.aucLauRejCause[i];
    }

    return;

}



VOS_VOID NAS_MMC_ReadRoamingRejectNoRetryFlgNvim( VOS_VOID )
{
    NAS_MML_ROAMINGREJECT_NORETYR_CFG_STRU                 *pstNoRetryCfg = VOS_NULL_PTR;
    NAS_NVIM_ROAMINGREJECT_NORETYR_CFG_STRU                 stRoamingRejectNoRetryCfg;
    VOS_UINT32                                              ulLength;
    VOS_UINT32                                              i;

    ulLength        = 0;
    i               = 0;

    PS_MEM_SET(&stRoamingRejectNoRetryCfg, 0, sizeof(NAS_NVIM_ROAMINGREJECT_NORETYR_CFG_STRU));

    (VOS_VOID)NV_GetLength(en_NV_Item_ROAMING_REJECT_NORETRY_CFG, &ulLength);
    if (ulLength > sizeof(NAS_NVIM_ROAMINGREJECT_NORETYR_CFG_STRU))
    {
        return;
    }

    pstNoRetryCfg = NAS_MML_GetRoamingRejectNoRetryCfg();

    if (NV_OK != NV_Read(en_NV_Item_ROAMING_REJECT_NORETRY_CFG,
                         &stRoamingRejectNoRetryCfg, ulLength))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC,
                     "NAS_MMC_ReadRoamingRejectNoRetryFlgNvim():en_NV_Item_ROAMING_REJECT_NORETRY_CFG Error");

        return;
    }

    pstNoRetryCfg->ucNoRetryRejectCauseNum = stRoamingRejectNoRetryCfg.ucNoRetryRejectCauseNum;

    if (pstNoRetryCfg->ucNoRetryRejectCauseNum > NAS_MML_MAX_ROAMING_REJECT_NO_RETRY_CAUSE_NUM)
    {
        pstNoRetryCfg->ucNoRetryRejectCauseNum = NAS_MML_MAX_ROAMING_REJECT_NO_RETRY_CAUSE_NUM;
    }

    for (i = 0; i < pstNoRetryCfg->ucNoRetryRejectCauseNum; i++)
    {
        pstNoRetryCfg->aucNoRetryRejectCause[i] = stRoamingRejectNoRetryCfg.aucNoRetryRejectCause[i];
    }

    return;

}

VOS_VOID NAS_MMC_ReadImeisvNvim( VOS_VOID )
{
    VOS_UINT8                           aucImeisv[NV_ITEM_IMEI_SIZE];
    VOS_UINT8                           i;
    NAS_MML_MS_CAPACILITY_INFO_STRU    *pstMsCapability = VOS_NULL_PTR;
    VOS_UINT8                           aucImeiSvn[4];

    MODEM_ID_ENUM_UINT16                enModemId;


    PS_MEM_SET(aucImeisv, 0x00, sizeof(aucImeisv));

    pstMsCapability = NAS_MML_GetMsCapability();

    /* ��PID��ȡMODEMID */
    enModemId = VOS_GetModemIDFromPid(WUEPS_PID_MMC);

    NAS_TRACE_HIGH("SC_PERS_NvRead begin");

    /* ����SC�ӿڶ�ȡIMEI���� */
    (VOS_VOID)SC_PERS_NvRead(enModemId, en_NV_Item_IMEI, aucImeisv, NV_ITEM_IMEI_SIZE);

    NAS_TRACE_HIGH("SC_PERS_NvRead end");

    for (i = 0; i < NV_ITEM_IMEI_SIZE; i++)
    {
        pstMsCapability->aucImeisv[i] = aucImeisv[i];
    }

    /* ��Ҫ����������ֽ���Ϊ0 */
    pstMsCapability->aucImeisv[NV_ITEM_IMEI_SIZE-2] = 0;
    pstMsCapability->aucImeisv[NV_ITEM_IMEI_SIZE-1] = 0;



    PS_MEM_SET(aucImeiSvn, 0x00, sizeof(aucImeiSvn));

    /* ���ȡIMEISV������ */
    if (NV_OK != NV_Read(en_NV_Item_Imei_Svn,
                    aucImeiSvn, sizeof(aucImeiSvn)))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadImeisvNvim:Read Nvim Failed");
        return;

    }

    /* NV����Ч,����� */
    if (VOS_TRUE == aucImeiSvn[0])
    {
         pstMsCapability->aucImeisv[NV_ITEM_IMEI_SIZE-2] = aucImeiSvn[1];
         pstMsCapability->aucImeisv[NV_ITEM_IMEI_SIZE-1] = aucImeiSvn[2];
    }

    return;
}
VOS_VOID NAS_MMC_ReadSupported3GppReleaseNvim(VOS_VOID)
{
    NAS_MML_MS_3GPP_REL_STRU           *pstMs3GppRel = VOS_NULL_PTR;
    NAS_MMC_NVIM_MSCR_VERSION_STRU      stMscrVersion;
    NAS_MMC_NVIM_SGSNR_VERSION_STRU     stSgsnrVersion;
    VOS_UINT32                          ulLength;

    NAS_MMC_NVIM_SUPPORT_3GPP_RELEASE_STRU  stSupported3GppRelease;

    ulLength                                          = 0;


    stSupported3GppRelease.aucSupported3GppRelease[0] = NAS_MML_3GPP_REL_R4 + 1;
    stSupported3GppRelease.aucSupported3GppRelease[1] = NAS_MML_3GPP_REL_R6 + 1;

    stMscrVersion.ucStatus          = NAS_MMC_NV_ITEM_DEACTIVE;
    stMscrVersion.ucUeMscrVersion   = 0;

    stSgsnrVersion.ucStatus         = NAS_MMC_NV_ITEM_DEACTIVE;
    stSgsnrVersion.ucUeSgsnrVersion = 0;

    pstMs3GppRel = NAS_MML_GetMs3GppRel();

    /* ��ȡ֧�ֵ�Э��ջ�汾 */
    if(NV_OK != NV_Read (en_NV_Item_NAS_Supported_3GPP_Release,
                         &stSupported3GppRelease, NAS_MMC_NVIM_SUPPORTED_3GPP_RELEASE_SIZE))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadSupported3GppReleaseNvim(): en_NV_Item_Supported_3GPP_Release Error");
        return;
    }

    /* NV�ֲ�������NV�м�¼ֵ����:
    1��R4�汾��
    2��R5�汾��
    3��R6�汾��Ĭ��ֵ����
    4��R7�汾��
    */

    pstMs3GppRel->enMsGsmRel   = stSupported3GppRelease.aucSupported3GppRelease[0] - 1;
    pstMs3GppRel->enMsWcdmaRel = stSupported3GppRelease.aucSupported3GppRelease[1] - 1;
    (VOS_VOID)NV_GetLength(en_NV_Item_UE_MSCR_VERSION, &ulLength);
    /* ��ȡMSC�İ汾 */
    if (NV_OK != NV_Read (en_NV_Item_UE_MSCR_VERSION, &stMscrVersion, ulLength))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadSupported3GppReleaseNvim():WARNING: NV_Read en_NV_Item_UE_MSCR_VERSION Error");
        return;
    }

    if (NAS_MMC_NV_ITEM_ACTIVE == stMscrVersion.ucStatus)
    {
        pstMs3GppRel->enMsMscRel = stMscrVersion.ucUeMscrVersion;
    }


    /* ��ȡSGSN�İ汾 */
    if (NV_OK != NV_Read (en_NV_Item_UE_SGSNR_VERSION, &stSgsnrVersion, sizeof(stSgsnrVersion)))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadSupported3GppReleaseNvim():WARNING: NV_Read en_NV_Item_UE_SGSNR_VERSION Error");
        return;
    }

    if(NAS_MMC_NV_ITEM_ACTIVE == stSgsnrVersion.ucStatus)
    {
        pstMs3GppRel->enMsSgsnRel = stSgsnrVersion.ucUeSgsnrVersion;
    }

    return;
}
VOS_VOID NAS_MMC_ReadClassMark1Nvim(VOS_VOID)
{
    VOS_UINT8                           ucClassmark1;
    NAS_MML_MS_CAPACILITY_INFO_STRU    *pstMsCapability = VOS_NULL_PTR;


    ucClassmark1 = NAS_MML_DEFAULT_CLASSMARK1_VALUE;

    pstMsCapability = NAS_MML_GetMsCapability();

    if (NV_OK != NV_Read (en_NV_Item_Gsm_Classmark1,
                          &ucClassmark1, sizeof(VOS_UINT8)))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC,  "NAS_MMC_ReadClassMark1Nvim(): NV_Read Classmark1 Error");
        return;
    }

    pstMsCapability->ucClassmark1 = ucClassmark1;
    return;
}


VOS_VOID NAS_MMC_ReadClassMark2Nvim(VOS_VOID)
{
    VOS_UINT8                           aucClassmark2[NAS_MML_CLASSMARK2_LEN];
    NAS_MML_MS_CAPACILITY_INFO_STRU    *pstMsCapability = VOS_NULL_PTR;


    PS_MEM_SET(aucClassmark2, 0x00, NAS_MML_CLASSMARK2_LEN);

    pstMsCapability = NAS_MML_GetMsCapability();

    if (NV_OK != NV_Read (en_NV_Item_Gsm_Classmark2,
                          aucClassmark2, NAS_MML_CLASSMARK2_LEN))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadClassMark2Nvim():NV_Read Classmark2 Error");
        return;
    }

    PS_MEM_CPY(pstMsCapability->aucClassmark2, aucClassmark2, NAS_MML_CLASSMARK2_LEN);

    return;
}


VOS_VOID NAS_MMC_UpdateNetworkCapabilityGeaValue(VOS_VOID)
{
    NAS_MMC_NVIM_GPRS_GEA_ALG_CTRL_STRU stGeaSupportCtrl;
    VOS_UINT8                           ucGeaSupportCtrl;
    NAS_MML_MS_CAPACILITY_INFO_STRU    *pstMsCapability = VOS_NULL_PTR;
    VOS_UINT32                          ulLength;

    ulLength = 0;

    stGeaSupportCtrl.ucStatus         = NAS_MMC_NV_ITEM_DEACTIVE;
    stGeaSupportCtrl.ucGeaSupportCtrl = 0;

    pstMsCapability = NAS_MML_GetMsCapability();

    (VOS_VOID)NV_GetLength(en_NV_Item_GEA_SUPPORT_CTRL, &ulLength);
    if (ulLength > sizeof(stGeaSupportCtrl))
    {
        return;
    }

    if (NV_OK != NV_Read(en_NV_Item_GEA_SUPPORT_CTRL, &stGeaSupportCtrl, ulLength))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC,
                      "NAS_MMC_UpdateNetworkCapabilityGeaValue():NV_Read en_NV_Item_GEA_SUPPORT_CTRL Error");

        return;
    }

    if (NAS_MMC_NV_ITEM_ACTIVE == stGeaSupportCtrl.ucStatus)
    {
        ucGeaSupportCtrl = stGeaSupportCtrl.ucGeaSupportCtrl;

        /* ��ʼ��ΪGEA1-GEA7����֧�� */
        pstMsCapability->stMsNetworkCapability.aucNetworkCapability[0] &= ~NAS_MMC_GPRS_GEA1_VALUE;
        pstMsCapability->stMsNetworkCapability.aucNetworkCapability[1] &= ~( NAS_MMC_GPRS_GEA2_VALUE
                                                                          | NAS_MMC_GPRS_GEA3_VALUE
                                                                          | NAS_MMC_GPRS_GEA4_VALUE
                                                                          | NAS_MMC_GPRS_GEA5_VALUE
                                                                          | NAS_MMC_GPRS_GEA6_VALUE
                                                                          | NAS_MMC_GPRS_GEA7_VALUE);

        /*  GEA1: ��һ���ֽڵ����λ */
        if (NAS_MMC_GPRS_GEA1_SUPPORT == (ucGeaSupportCtrl & NAS_MMC_GPRS_GEA1_SUPPORT))
        {
            pstMsCapability->stMsNetworkCapability.aucNetworkCapability[0] |= NAS_MMC_GPRS_GEA1_VALUE;
        }

        /*  GEA2: �ڶ����ֽڵ�����ڶ���bit */
        if (NAS_MMC_GPRS_GEA2_SUPPORT == (ucGeaSupportCtrl & NAS_MMC_GPRS_GEA2_SUPPORT))
        {
            pstMsCapability->stMsNetworkCapability.aucNetworkCapability[1] |= NAS_MMC_GPRS_GEA2_VALUE;
        }

        /* GEA3: �ڶ����ֽڵ����������bit */
        if (NAS_MMC_GPRS_GEA3_SUPPORT == (ucGeaSupportCtrl & NAS_MMC_GPRS_GEA3_SUPPORT))
        {
            pstMsCapability->stMsNetworkCapability.aucNetworkCapability[1] |= NAS_MMC_GPRS_GEA3_VALUE;
        }

        /* GEA4: �ڶ����ֽڵ�������ĸ�bit */
        if (NAS_MMC_GPRS_GEA4_SUPPORT == (ucGeaSupportCtrl & NAS_MMC_GPRS_GEA4_SUPPORT))
        {
            pstMsCapability->stMsNetworkCapability.aucNetworkCapability[1] |= NAS_MMC_GPRS_GEA4_VALUE;
        }

        /* GEA5: �ڶ����ֽڵ���������bit */
        if (NAS_MMC_GPRS_GEA5_SUPPORT == (ucGeaSupportCtrl & NAS_MMC_GPRS_GEA5_SUPPORT))
        {
            pstMsCapability->stMsNetworkCapability.aucNetworkCapability[1] |= NAS_MMC_GPRS_GEA5_VALUE;
        }

        /* GEA6: �ڶ����ֽڵ����������bit */
        if (NAS_MMC_GPRS_GEA6_SUPPORT == (ucGeaSupportCtrl & NAS_MMC_GPRS_GEA6_SUPPORT))
        {
            pstMsCapability->stMsNetworkCapability.aucNetworkCapability[1] |= NAS_MMC_GPRS_GEA6_VALUE;
        }

        /* GEA7: �ڶ����ֽڵ�������߸�bit */
        if (NAS_MMC_GPRS_GEA7_SUPPORT == (ucGeaSupportCtrl & NAS_MMC_GPRS_GEA7_SUPPORT))
        {
            pstMsCapability->stMsNetworkCapability.aucNetworkCapability[1] |= NAS_MMC_GPRS_GEA7_VALUE;
        }
    }

    return;
}



VOS_VOID NAS_MMC_ReadNetworkCapabilityNvim(VOS_VOID)
{
    NAS_MMC_NVIM_NETWORK_CAPABILITY_STRU                    stNetworkCap;/*network capability*/

    VOS_UINT32                          ulLen;
    NAS_MML_MS_CAPACILITY_INFO_STRU    *pstMsCapability = VOS_NULL_PTR;


    ulLen = 0;
    PS_MEM_SET(&stNetworkCap, 0x00, sizeof(NAS_MMC_NVIM_NETWORK_CAPABILITY_STRU));

    pstMsCapability = NAS_MML_GetMsCapability();
    (VOS_VOID)NV_GetLength(en_NV_Item_NetworkCapability, &ulLen);

    if (ulLen > (NAS_MML_MAX_NETWORK_CAPABILITY_LEN + 1))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadNetworkCapabilityNvim():WARNING: en_NV_Item_NetworkCapability length Error");
        return;
    }
    else
    {
        if(NV_OK != NV_Read (en_NV_Item_NetworkCapability, &stNetworkCap, ulLen))
        {
            NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadNetworkCapabilityNvim():en_NV_Item_NetworkCapability Error");
            return;
        }
    }

    /* nv��aucNetworkCapability[0]��ĳ���ΪnetworkCapbility���� + networkCapbilityֵ*/
    pstMsCapability->stMsNetworkCapability.ucNetworkCapabilityLen = stNetworkCap.aucNetworkCapability[0];

    if (pstMsCapability->stMsNetworkCapability.ucNetworkCapabilityLen > NAS_MML_MAX_NETWORK_CAPABILITY_LEN)
    {
        pstMsCapability->stMsNetworkCapability.ucNetworkCapabilityLen = NAS_MML_MAX_NETWORK_CAPABILITY_LEN;
    }

    /* ������������ */
    PS_MEM_CPY(&pstMsCapability->stMsNetworkCapability.aucNetworkCapability[0],
               &(stNetworkCap.aucNetworkCapability[1]),
               pstMsCapability->stMsNetworkCapability.ucNetworkCapabilityLen);

    /* ����en_NV_Item_GEA_SUPPORT_CTRL����network capability��GEA��ֵ */
    NAS_MMC_UpdateNetworkCapabilityGeaValue();
    return;
}


VOS_VOID NAS_MMC_ReadUcs2CustomizationNvim(VOS_VOID)
{
    NAS_MML_MS_CAPACILITY_INFO_STRU                        *pstMsCapability = VOS_NULL_PTR;
    VOS_UINT32                                              ulDataLen;
    VOS_UINT32                                              ulResult;
    NAS_MMC_NVIM_UCS2_CUSTOMIZATION_STRU                    stUcs2Customization;

    ulDataLen       = 0;
    pstMsCapability = NAS_MML_GetMsCapability();

    stUcs2Customization.usUcs2Customization = NAS_MMC_UCS2_NO_PREFER;

    (VOS_VOID)NV_GetLength(en_NV_Item_UCS2_Customization, &ulDataLen);
    if (ulDataLen > sizeof(stUcs2Customization))
    {
        return;
    }

    ulResult = NV_Read(en_NV_Item_UCS2_Customization, &stUcs2Customization, ulDataLen);

    /* ��ȡʧ�ܣ�Ĭ�� the ME has no preference between the use of the default alphabet and the use of UCS2 */
    if ( NV_OK != ulResult )
    {
        stUcs2Customization.usUcs2Customization = NAS_MMC_UCS2_NO_PREFER;
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadUcs2CustomizationNvim():en_NV_Item_UCS2_Customization Error");
    }

    /* ����classmark2�е�UCS2����,����ms network capability�е�UCS2������ */
    if (NAS_MMC_UCS2_NO_PREFER == stUcs2Customization.usUcs2Customization)
    {
        pstMsCapability->aucClassmark2[3] |= 0x10;
        pstMsCapability->stMsNetworkCapability.aucNetworkCapability[0] |= 0x10;
    }
    else
    {
        pstMsCapability->aucClassmark2[3] &= 0xef;
        pstMsCapability->stMsNetworkCapability.aucNetworkCapability[0] &= 0xef;
    }

    return;
}



VOS_VOID NAS_MMC_ReadCloseSmsCapabilityConfigNvim(VOS_VOID)
{
    NAS_MML_MS_CAPACILITY_INFO_STRU                        *pstMsCapability = VOS_NULL_PTR;
    VOS_UINT32                                              ulLength;
    NAS_NVIM_CLOSE_SMS_CAPABILITY_CFG_STRU                  stCloseSmsCapabilityCfg;
    VOS_UINT32                                              ulRet;

    ulLength        = 0;

    pstMsCapability = NAS_MML_GetMsCapability();

    /* �Ȼ�ȡNV�ĳ��� */
    (VOS_VOID)NV_GetLength(en_NV_Item_Close_SMS_Capability_Config, &ulLength);

    if (ulLength > sizeof(NAS_NVIM_CLOSE_SMS_CAPABILITY_CFG_STRU))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadCloseSmsCapabilityConfigNvim():en_NV_Item_Close_SMS_Capability_Config length Error");
        return;
    }

    ulRet = NV_Read(en_NV_Item_Close_SMS_Capability_Config,
                   &stCloseSmsCapabilityCfg,
                    ulLength);

    /* ��ȡ�رն��Ŷ���NVʧ��,Ĭ�ϲ��رն��Ź��� */
    if (NV_OK != ulRet)
    {
        stCloseSmsCapabilityCfg.ucActFlg = VOS_FALSE;

        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadCloseSmsCapabilityConfigNvim():en_NV_Item_CLOSE_SMS_Capability_Config Failed");
    }

    /* ����ms network capability�е�CS/PS�Ķ���֧������,����class mark2�е�PS�������� */
    if (VOS_TRUE == stCloseSmsCapabilityCfg.ucActFlg)
    {
        pstMsCapability->stMsNetworkCapability.aucNetworkCapability[0] &= 0x9f;
        pstMsCapability->aucClassmark2[2] &= 0xf7;
    }
    else
    {
        pstMsCapability->stMsNetworkCapability.aucNetworkCapability[0] |= 0x60;
        pstMsCapability->aucClassmark2[2] |= 0x08;
    }

    return;
}


#if (FEATURE_ON == FEATURE_LTE)

VOS_VOID NAS_MMC_ReadLteRoamConfigNvim(VOS_VOID)
{
    NAS_MMC_NVIM_LTE_INTERNATIONAL_ROAM_CFG_STRU            stLteRoamNvCfg;
    VOS_UINT32                                              ulLength;
    VOS_UINT32                                              aulRoamEnabledMccList[5];


    ulLength = 0;

    PS_MEM_SET(&stLteRoamNvCfg,       0x00, sizeof(NAS_MMC_NVIM_LTE_INTERNATIONAL_ROAM_CFG_STRU));
    PS_MEM_SET(aulRoamEnabledMccList, 0x00, sizeof(aulRoamEnabledMccList));

    /* �Ȼ�ȡNV�ĳ��� */
    (VOS_VOID)NV_GetLength(en_NV_Item_Lte_Internation_Roam_Config, &ulLength);

    if (ulLength > sizeof(NAS_MMC_NVIM_LTE_INTERNATIONAL_ROAM_CFG_STRU))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadLteRoamConfigNvim():WARNING: en_NV_Item_Lte_Internation_Roam_Config length Error");
        return;
    }

    if ( NV_OK != NV_Read(en_NV_Item_Lte_Internation_Roam_Config,
                          &stLteRoamNvCfg,
                           ulLength))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadLteRoamConfigNvim(): en_NV_Item_Lte_Internation_Roam_Config Error");
        return;
    }

    PS_MEM_CPY(aulRoamEnabledMccList, stLteRoamNvCfg.aucRoamEnabledMccList, sizeof(aulRoamEnabledMccList));

    /* ���õ�ǰLTE���������Ƿ����� */
    NAS_MML_SetLteRoamAllowedFlg(stLteRoamNvCfg.ucLteRoamAllowedFlg);

    /* ��������LTE���εĹ����� */
    NAS_MML_SetRoamEnabledMccList(aulRoamEnabledMccList);

    return;
}


VOS_VOID NAS_MMC_ReadLNasReleaseNvim(VOS_VOID)
{
    LNAS_LMM_NV_NAS_RELEASE_STRU        stNvNasRelease;
    VOS_UINT32                          ulLength;
    NAS_MML_MS_3GPP_REL_STRU           *pstMs3GppRel = VOS_NULL_PTR;

    ulLength     = 0;
    pstMs3GppRel = NAS_MML_GetMs3GppRel();

    pstMs3GppRel->enLteNasRelease = NAS_MML_3GPP_REL_R9;

    /* ��ȡNV EN_NV_ID_NAS_RELEASE ���� */
    (VOS_VOID)NV_GetLength(EN_NV_ID_NAS_RELEASE, &ulLength);

    if (ulLength > sizeof(LNAS_LMM_NV_NAS_RELEASE_STRU))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadLNasReleaseNvim():WARNING: EN_NV_ID_NAS_RELEASE length Error");
        return;
    }

    /* ��NVʧ�� */
    if (NV_OK != NV_Read(EN_NV_ID_NAS_RELEASE,
                         &stNvNasRelease, ulLength))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC,
                      "NAS_MMC_ReadLNasReleaseNvim(): EN_NV_ID_NAS_RELEASE Error");
        return;
    }

    if (VOS_TRUE == stNvNasRelease.bitOpReleaseName)
    {
        if (0x00000b00 <= stNvNasRelease.ulReleaseName)
        {
            pstMs3GppRel->enLteNasRelease = NAS_MML_3GPP_REL_R11;
            return;
        }

        if (0x00000a00 <= stNvNasRelease.ulReleaseName)
        {
            pstMs3GppRel->enLteNasRelease = NAS_MML_3GPP_REL_R10;
            return;
        }
    }


    return;
}

#endif


VOS_VOID NAS_MMC_ReadRPLMNConfigNvim(VOS_VOID)
{
    NAS_MMC_NVIM_ROAM_SEARCH_RPLMN_CFG_STRU            stRoamPlmnSearchNvCfg;
    VOS_UINT32                                         ulLength = 0;

    PS_MEM_SET(&stRoamPlmnSearchNvCfg, 0x00, sizeof(NAS_MMC_NVIM_ROAM_SEARCH_RPLMN_CFG_STRU));

    /* �Ȼ�ȡNV�ĳ��� */
    (VOS_VOID)NV_GetLength(en_NV_Item_Roam_Search_Rplmn_Config, &ulLength);

    if (ulLength > sizeof(NAS_MMC_NVIM_ROAM_SEARCH_RPLMN_CFG_STRU))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadLteRoamConfigNvim():WARNING: en_NV_Item_Roam_Search_Rplmn_Config length Error");
        return;
    }

    if ( NV_OK != NV_Read(en_NV_Item_Roam_Search_Rplmn_Config,
                          &stRoamPlmnSearchNvCfg,
                           ulLength))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadLteRoamConfigNvim(): en_NV_Item_Roam_Search_Rplmn_Config Error");
        return;
    }

    /*������������RPLMN��ʶ*/
    NAS_MML_SetRoamRplmnSearchFlg(stRoamPlmnSearchNvCfg.ucRoamRplmnflg);
    /*�������Mcc�б�*/
    NAS_MML_SetNationalMCCList(stRoamPlmnSearchNvCfg.aucRoamEnabledMccList);

    return;
}
VOS_VOID NAS_MMC_ReadSBMCustomDualIMSIConfigNvim(VOS_VOID)
{
    /* en_NV_Item_SBM_CUSTOM_DUAL_IMSI-->en_NV_Item_SBM_CUSTOM_DUAL_IMSI_NEW
       NVIM_SBM_CUSTOM_DUAL_IMSI_STRU -->NVIM_SBM_CUSTOM_DUAL_IMSI_STRU_NEW */
    NVIM_SBM_CUSTOM_DUAL_IMSI_STRU_NEW                      stSBMDualimsiNvCfg;
    VOS_UINT32                                              ulLength;
    ulLength = 0;

    PS_MEM_SET(&stSBMDualimsiNvCfg, 0x00, sizeof(NVIM_SBM_CUSTOM_DUAL_IMSI_STRU_NEW));

    /* �Ȼ�ȡNV�ĳ��� */
    (VOS_VOID)NV_GetLength(en_NV_Item_SBM_CUSTOM_DUAL_IMSI_NEW, &ulLength);

    if (ulLength > sizeof(NVIM_SBM_CUSTOM_DUAL_IMSI_STRU_NEW))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadSBMCustomDualIMSIConfigNvim():WARNING: en_NV_Item_SBM_CUSTOM_DUAL_IMSI_NEW length Error");
        return;
    }

    if ( NV_OK != NV_Read(en_NV_Item_SBM_CUSTOM_DUAL_IMSI_NEW,
                          &stSBMDualimsiNvCfg,
                           ulLength))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadSBMCustomDualIMSIConfigNvim(): en_NV_Item_SBM_CUSTOM_DUAL_IMSI_NEW Error");
        return;
    }

    /*�����������ƿ���*/
    NAS_MML_SetDisableLTEOnBandFlg(stSBMDualimsiNvCfg.ucSbmCustomDualImsiFlg);

    return;
}




VOS_VOID NAS_MMC_ReadDailRejectConfigNvim(VOS_VOID)
{
    NAS_MMC_NVIM_DAIL_REJECT_CFG_STRU   stDellRejectCfg;
    VOS_UINT32                          ulLength;


    stDellRejectCfg.ucEnableFlg = VOS_FALSE;


    ulLength = 0;

    /* �Ȼ�ȡNV�ĳ��� */
    (VOS_VOID)NV_GetLength(en_NV_Item_Dail_Reject_Config, &ulLength);

    if (ulLength > sizeof(NAS_MMC_NVIM_DAIL_REJECT_CFG_STRU))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadDailRejectConfigNvim():WARNING: en_NV_Item_Dail_Reject_Config length Error");
        return;
    }

    if ( NV_OK != NV_Read(en_NV_Item_Dail_Reject_Config,
                          &stDellRejectCfg,
                          ulLength))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadDellRejectConfigNvim(): en_NV_Item_Dell_Reject_Config Error");
        return;
    }

    /* ���õ�ǰ���ű����Ƿ���� */
    NAS_MML_SetDailRejectCfg(stDellRejectCfg.ucEnableFlg);

    return;
}



VOS_VOID  NAS_MMC_ReadMsModeNvim( VOS_VOID )
{
    NAS_NVIM_MS_CLASS_STRU              stMsClass;
    VOS_UINT32                          ulLength;

    ulLength        = 0;

    PS_MEM_SET(&stMsClass, 0x00, sizeof(NAS_NVIM_MS_CLASS_STRU));
    stMsClass.ucMsClass = NAS_MML_MS_MODE_BUTT;

    (VOS_VOID)NV_GetLength(en_NV_Item_MMA_MsClass, &ulLength);
    if (ulLength > sizeof(NAS_NVIM_MS_CLASS_STRU))
    {
        return;
    }

    if (NV_OK != NV_Read(en_NV_Item_MMA_MsClass, &stMsClass, ulLength))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadMsModeNvim():en_NV_Item_MMA_MsClass NV Read Fail!");
        return;
    }

    /* NV�е�ȡֵ����( 0��ֻ֧��CS���ֻ���1��NV_MS_CLASS_CG��ֻ֧��PS���ֻ���
       2��NV_MS_CLASS_A��֧��CS/PS���ֻ���Ĭ��ֵ��)��MML�еĲ�һ�£���Ҫת��*/

    if ((NV_MS_MODE_CS_ONLY == stMsClass.ucMsClass)
    ||  (NV_MS_MODE_ANY == stMsClass.ucMsClass))
    {
        NAS_MML_SetMsMode(NAS_MML_MS_MODE_CS_ONLY);
    }

    else if (NV_MS_MODE_PS_ONLY == stMsClass.ucMsClass)
    {
        NAS_MML_SetMsMode(NAS_MML_MS_MODE_PS_ONLY);
    }
    else if (NV_MS_MODE_CS_PS == stMsClass.ucMsClass)
    {
        NAS_MML_SetMsMode(NAS_MML_MS_MODE_PS_CS);
    }
    else
    {
    }

    return;
}
VOS_VOID NAS_MMC_ReadUserSetBandNvim(VOS_VOID)
{
    NVIM_UE_SUPPORT_FREQ_BAND_STRU                          stUserSetFreqBand;
    NAS_MML_MS_BAND_INFO_STRU                              *pstUserSetBand = VOS_NULL_PTR;
    LTE_BAND_STRU                                           stLteBand;


    PS_MEM_SET(&stUserSetFreqBand, 0x00, sizeof(stUserSetFreqBand));
    PS_MEM_SET(&stLteBand,         0x00, sizeof(stLteBand));

    pstUserSetBand = NAS_MML_GetMsSupportBand();

    /* ���û����õ�GUƵ�� NV�� */
    if (NV_OK != NV_Read(en_NV_Item_Support_Freqbands,
                         &stUserSetFreqBand, sizeof(NVIM_UE_SUPPORT_FREQ_BAND_STRU)))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadUserSetBandNvim():en_NV_Item_Support_Freqbands Error");
        return;
    }

    pstUserSetBand->unGsmBand.ulBand   = stUserSetFreqBand.ulGsmBand;
    pstUserSetBand->unWcdmaBand.ulBand = stUserSetFreqBand.ulWcdmaBand;

    /* ���û����õ�LTEƵ�� NV�� */
    if (NV_OK != NV_Read(en_NV_Item_USER_SET_LTEBANDS,
                         &stLteBand, sizeof(LTE_BAND_STRU)))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadUserSetBandNvim():en_NV_Item_USER_SET_LTEBANDS Error");
        return;
    }

    pstUserSetBand->stLteBand = stLteBand;

    return;
}


VOS_VOID NAS_MMC_ReadUseSingleRplmnFlagNvim(VOS_VOID)
{
    NAS_MMC_NVIM_USE_SINGLE_RPLMN_STRU  stUseSingleRplmnFlag;
    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRplmnCfgInfo = VOS_NULL_PTR;
    VOS_UINT32                          ulLength;

    ulLength        = 0;


    stUseSingleRplmnFlag.usUseSingleRplmnFlag = NAS_MMC_NV_ITEM_ACTIVE;

    pstRplmnCfgInfo = NAS_MML_GetRplmnCfg();

    (VOS_VOID)NV_GetLength(en_NV_Item_Use_Single_Rplmn_When_Area_Lost, &ulLength);
    if (ulLength > sizeof(stUseSingleRplmnFlag))
    {
        return;
    }

    if (NV_OK != NV_Read(en_NV_Item_Use_Single_Rplmn_When_Area_Lost,
                         &stUseSingleRplmnFlag, ulLength))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC,
                     "NAS_MMC_ReadUseSingleRplmnFlagNvim():en_NV_Item_Use_Single_Rplmn_When_Area_Lost Error");

        return;
    }

    if ((stUseSingleRplmnFlag.usUseSingleRplmnFlag != NAS_MMC_NV_ITEM_DEACTIVE)
     && (stUseSingleRplmnFlag.usUseSingleRplmnFlag != NAS_MMC_NV_ITEM_ACTIVE))
    {
        return;
    }

    /* usUseSingleRplmnFlagΪ0��WCDMA��GSM�洢����ע���RPLMN */
    if (NAS_MMC_NV_ITEM_DEACTIVE == stUseSingleRplmnFlag.usUseSingleRplmnFlag)
    {
        /* ֧��˫RPLMN */
        pstRplmnCfgInfo->ucMultiRATRplmnFlg = VOS_TRUE;
    }
    else
    {
        pstRplmnCfgInfo->ucMultiRATRplmnFlg = VOS_FALSE;
    }


    return;
}


VOS_VOID NAS_MMC_ReadRplmnWithRatNvim(VOS_VOID)
{
    NAS_NVIM_RPLMN_WITH_RAT_STRU        stRplmn;
    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRplmnCfgInfo = VOS_NULL_PTR;
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstRatPrioList = VOS_NULL_PTR;

    pstRatPrioList           = NAS_MML_GetMsPrioRatList();


    stRplmn.stGRplmn.ulMcc          = NAS_MML_INVALID_MCC;
    stRplmn.stGRplmn.ulMnc          = NAS_MML_INVALID_MNC;
    stRplmn.stWRplmn.ulMcc          = NAS_MML_INVALID_MCC;
    stRplmn.stWRplmn.ulMnc          = NAS_MML_INVALID_MNC;
    stRplmn.ucLastRplmnRat          = NAS_MML_NET_RAT_TYPE_BUTT;
    stRplmn.ucLastRplmnRatEnableFlg = VOS_FALSE;

    pstRplmnCfgInfo   = NAS_MML_GetRplmnCfg();

    if(NV_OK != NV_Read (en_NV_Item_RPlmnWithRat, &stRplmn, sizeof(NAS_NVIM_RPLMN_WITH_RAT_STRU)))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadRplmnWithRatNvim(): en_NV_Item_RPlmnWithRat Error");
        return;
    }

    if ((stRplmn.ucLastRplmnRatEnableFlg != NAS_MMC_NV_ITEM_DEACTIVE)
     && (stRplmn.ucLastRplmnRatEnableFlg != NAS_MMC_NV_ITEM_ACTIVE))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadRplmnWithRatNvim(): NV parameter Error");
        return;
    }

    pstRplmnCfgInfo->ucLastRplmnRatFlg = stRplmn.ucLastRplmnRatEnableFlg;

    /* �����״�������ֵΪĬ�ϵ�0XFF,��ʱ��Ҫ����Ĭ�ϵ�SYSCFGEX�Ľ������ȼ�ȡ
       ������ȼ� */
    if ((NAS_MML_NET_RAT_TYPE_INVALID == stRplmn.ucLastRplmnRat)
     || (NAS_MML_NET_RAT_TYPE_BUTT    == stRplmn.ucLastRplmnRat))
    {
        pstRplmnCfgInfo->enLastRplmnRat = pstRatPrioList->aucRatPrio[0];
    }
    else
    {
        pstRplmnCfgInfo->enLastRplmnRat    = stRplmn.ucLastRplmnRat;
    }

    PS_MEM_CPY(&pstRplmnCfgInfo->stGRplmnInNV, &stRplmn.stGRplmn, sizeof(NAS_MML_PLMN_ID_STRU));
    PS_MEM_CPY(&pstRplmnCfgInfo->stWRplmnInNV, &stRplmn.stWRplmn, sizeof(NAS_MML_PLMN_ID_STRU));


    return;
}



VOS_VOID NAS_MMC_ReadNvimLastRplmnRat(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8    *penNvimLastRplmnRat
)
{
    NAS_NVIM_RPLMN_WITH_RAT_STRU        stRplmn;

    stRplmn.stGRplmn.ulMcc          = NAS_MML_INVALID_MCC;
    stRplmn.stGRplmn.ulMnc          = NAS_MML_INVALID_MNC;
    stRplmn.stWRplmn.ulMcc          = NAS_MML_INVALID_MCC;
    stRplmn.stWRplmn.ulMnc          = NAS_MML_INVALID_MNC;
    stRplmn.ucLastRplmnRat          = NAS_MML_NET_RAT_TYPE_BUTT;
    stRplmn.ucLastRplmnRatEnableFlg = VOS_FALSE;

    if(NV_OK != NV_Read (en_NV_Item_RPlmnWithRat, &stRplmn, sizeof(NAS_NVIM_RPLMN_WITH_RAT_STRU)))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadNvimLastRplmnRat(): en_NV_Item_RPlmnWithRat Error");
        return;
    }

    if ((stRplmn.ucLastRplmnRatEnableFlg != NAS_MMC_NV_ITEM_DEACTIVE)
     && (stRplmn.ucLastRplmnRatEnableFlg != NAS_MMC_NV_ITEM_ACTIVE))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadNvimLastRplmnRat(): NV parameter Error");
        return;
    }

    *penNvimLastRplmnRat = stRplmn.ucLastRplmnRat;

    return;
}




VOS_VOID NAS_MMC_WriteRplmnWithRatNvim(VOS_VOID)
{
    NAS_NVIM_RPLMN_WITH_RAT_STRU        stRplmn;
    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRplmnCfgInfo = VOS_NULL_PTR;

    pstRplmnCfgInfo = NAS_MML_GetRplmnCfg();

    stRplmn.ucLastRplmnRat          = pstRplmnCfgInfo->enLastRplmnRat;
    stRplmn.stGRplmn.ulMcc          = pstRplmnCfgInfo->stGRplmnInNV.ulMcc;
    stRplmn.stGRplmn.ulMnc          = pstRplmnCfgInfo->stGRplmnInNV.ulMnc;
    stRplmn.stWRplmn.ulMcc          = pstRplmnCfgInfo->stWRplmnInNV.ulMcc;
    stRplmn.stWRplmn.ulMnc          = pstRplmnCfgInfo->stWRplmnInNV.ulMnc;
    stRplmn.ucLastRplmnRatEnableFlg = pstRplmnCfgInfo->ucLastRplmnRatFlg;

    if(NV_OK != NV_Write(en_NV_Item_RPlmnWithRat, &stRplmn, sizeof(NAS_NVIM_RPLMN_WITH_RAT_STRU)))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_WriteRplmnWithRatNvim(): en_NV_Item_RPlmnWithRat Error");
    }

    return;
}


#if   (FEATURE_ON == FEATURE_LTE)


VOS_VOID NAS_MMC_ReadTinInfoNvim( VOS_VOID )
{
    NAS_NVIM_TIN_INFO_STRU          stTinInfo;

    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRplmnCfgInfo = VOS_NULL_PTR;


    PS_MEM_SET(&stTinInfo, 0x00, sizeof(stTinInfo));

    pstRplmnCfgInfo = NAS_MML_GetRplmnCfg();

    if ( NV_OK != NV_Read(en_NV_Item_TIN_INFO,
                          &stTinInfo,
                          sizeof(stTinInfo) ))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadTinInfoNvim(): en_NV_Item_TIN_INFO Error");

        return;
    }

    PS_MEM_CPY(pstRplmnCfgInfo->aucLastImsi, stTinInfo.aucImsi, sizeof(pstRplmnCfgInfo->aucLastImsi));
    pstRplmnCfgInfo->enTinType = (NAS_MML_TIN_TYPE_ENUM_UINT8)stTinInfo.ucTinType;

    /* ���ƽ̨��֧��LTE����Ҫ��Tin type�����쳣���� */
    if (VOS_FALSE == NAS_MML_IsPlatformSupportLte())
    {
        if ((NAS_MML_TIN_TYPE_GUTI == pstRplmnCfgInfo->enTinType)
         || (NAS_MML_TIN_TYPE_RAT_RELATED_TMSI == pstRplmnCfgInfo->enTinType))
        {
            pstRplmnCfgInfo->enTinType = NAS_MML_TIN_TYPE_INVALID;
        }
    }

    return;

}
VOS_VOID  NAS_MMC_WriteTinInfoNvim(
    NAS_MML_TIN_TYPE_ENUM_UINT8         enTinType,
    VOS_UINT8                          *pucImsi
)
{
    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRplmnCfgInfo = VOS_NULL_PTR;

    NAS_NVIM_TIN_INFO_STRU              stTinInfo;

    pstRplmnCfgInfo = NAS_MML_GetRplmnCfg();

    /*
        The following EMM parameter shall be stored in a non-volatile memory in the
        ME together with the IMSI from the USIM:
        -   TIN.
        This EMM parameter can only be used if the IMSI from the USIM matches the
        IMSI stored in the non-volatile memory of the ME; else the UE shall delete
        the EMM parameter.
    */

    /* �ȸ���MML�Ĳ��� */
    pstRplmnCfgInfo->enTinType  = enTinType;
    PS_MEM_CPY(pstRplmnCfgInfo->aucLastImsi, pucImsi, sizeof(pstRplmnCfgInfo->aucLastImsi));

    /* �ٸ���NVIM�еĲ��� */
    stTinInfo.ucTinType        = pstRplmnCfgInfo->enTinType;
    PS_MEM_CPY(stTinInfo.aucImsi, pstRplmnCfgInfo->aucLastImsi, sizeof(stTinInfo.aucImsi));
    PS_MEM_SET(stTinInfo.aucReserve, 0, sizeof(stTinInfo.aucReserve));

    /* ������NVIM�� */
    if (NV_OK != NV_Write (en_NV_Item_TIN_INFO,
                           &stTinInfo,
                           sizeof(stTinInfo)))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_WriteTinInfoNvim:Write NV Failed");
    }
}


VOS_VOID NAS_MMC_ReadLteCsServiceConfigNvim(VOS_VOID)
{
    NAS_NVIM_LTE_CS_SERVICE_CFG_STRU                        stLteCsServiceCfg;
    VOS_UINT32                                              ulLength;

    ulLength        = 0;


    PS_MEM_SET(&stLteCsServiceCfg, 0x00, sizeof(NAS_NVIM_LTE_CS_SERVICE_CFG_STRU));
    (VOS_VOID)NV_GetLength(en_NV_Item_Lte_Cs_Service_Config, &ulLength);
    if (ulLength > sizeof(stLteCsServiceCfg))
    {
        return;
    }
    if ( NV_OK != NV_Read(en_NV_Item_Lte_Cs_Service_Config,
                          &stLteCsServiceCfg,
                          ulLength ))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadLteCsServiceConfigNvim(): en_NV_Item_Lte_Cs_Service_Config Error");
        return;
    }

    /* ���NV����ֵ��Ч�������MML�е�ȫ�ֱ��� */
    if ((NAS_MMC_NV_ITEM_ACTIVE == stLteCsServiceCfg.ucNvimActiveFlg)
     && (stLteCsServiceCfg.ucLteCsServiceCfg < NAS_MML_LTE_SUPPORT_BUTT))
    {
        /* ���õ�ǰLTE��CSҵ������������NV��� */
        NAS_MML_SetLteCsServiceCfg(stLteCsServiceCfg.ucLteCsServiceCfg);

#if (VOS_WIN32 == VOS_OS_VER)
        NAS_MML_SetLteCsServiceCfg(NAS_MML_LTE_SUPPORT_CSFB_AND_SMS_OVER_SGS);
#endif

        return;
    }

    /* NV��Чʱ����Ϊ  */
    NAS_MML_SetLteCsServiceCfg(NAS_MML_LTE_SUPPORT_BUTT);

#if (VOS_WIN32 == VOS_OS_VER)
        NAS_MML_SetLteCsServiceCfg(NAS_MML_LTE_SUPPORT_CSFB_AND_SMS_OVER_SGS);
#endif


    return;
}





VOS_VOID NAS_MMC_ReadHoWaitSysinfoTimeLenNvim(VOS_VOID)
{
    NAS_MMC_NVIM_HO_WAIT_SYSINFO_TIMER_CFG_STRU             stHoTimerCfg;


    PS_MEM_SET(&stHoTimerCfg, 0x00, sizeof(stHoTimerCfg));

    /* ��NVʧ�� */
    if (NV_OK != NV_Read(en_NV_Item_Ho_Wait_Sysinfo_Timer_Config,
                         &stHoTimerCfg, sizeof(NAS_MMC_NVIM_HO_WAIT_SYSINFO_TIMER_CFG_STRU)))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC,
                      "NAS_MMC_ReadHoWaitSysinfoTimeLenNvim(): en_NV_Item_HO_WAIT_SYSINFO_TIMER_Config Error");
        return;
    }

    /* en_NV_Item_HO_WAIT_SYSINFO_TIMER_Configδʹ�ܣ������õ�ϵͳ��Ϣʱ��ΪĬ��ֵ1s */
    if ( NAS_MMC_NV_ITEM_DEACTIVE == stHoTimerCfg.ucNvimActiveFlg )
    {
        NAS_MML_SetHoWaitSysinfoTimerLen(NAS_MML_HO_WAIT_SYS_INFO_DEFAULT_LEN_VALUE);
        return;
    }

    /* en_NV_Item_HO_WAIT_SYSINFO_TIMER_Config���õ�ϵͳ��Ϣʱ��Ϊ0�������ΪĬ��ֵ1s */
    if ( 0 == stHoTimerCfg.ucWaitSysinfoTimeLen )
    {
        NAS_MML_SetHoWaitSysinfoTimerLen(NAS_MML_HO_WAIT_SYS_INFO_DEFAULT_LEN_VALUE);
        return;
    }

    /* ����MMLȫ�ֱ����е�HO��ϵͳ��Ϣ��ֵ */
    NAS_MML_SetHoWaitSysinfoTimerLen(stHoTimerCfg.ucWaitSysinfoTimeLen * NAS_MML_ONE_THOUSAND_MILLISECOND);

    return;
}
#endif

VOS_VOID NAS_MMC_ReadCsfbEmgCallLaiChgLauFirstNvim(VOS_VOID)
{
    NAS_MMC_NVIM_CSFB_EMG_CALL_LAI_CHG_LAU_FIRST_CFG_STRU   stCsfbEmgCallLauFirstCfg;
    VOS_UINT32                                              ulLength;


    PS_MEM_SET(&stCsfbEmgCallLauFirstCfg, 0x00, sizeof(NAS_MMC_NVIM_CSFB_EMG_CALL_LAI_CHG_LAU_FIRST_CFG_STRU));

    ulLength = 0;

    /* �Ȼ�ȡNV�ĳ��� */
    (VOS_VOID)NV_GetLength(en_NV_Item_Csfb_Emg_Call_LaiChg_Lau_First_CFG, &ulLength);

    if (ulLength > sizeof(NAS_MMC_NVIM_CSFB_EMG_CALL_LAI_CHG_LAU_FIRST_CFG_STRU))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadCsfbEmgCallLaiChgLauFirstNvim():WARNING: en_NV_Item_Csfb_Emergency_Call_LaiChg_Lau_First_CFG length Error");
        return;
    }

    /* ��NVʧ�� */
    if (NV_OK != NV_Read(en_NV_Item_Csfb_Emg_Call_LaiChg_Lau_First_CFG,
                         &stCsfbEmgCallLauFirstCfg, ulLength))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC,
                      "NAS_MMC_ReadCsfbEmgCallLaiChgLauFirstNvim(): en_NV_Item_Csfb_Emergency_Call_LaiChg_Lau_First_CFG Error");
        return;
    }

    if (VOS_TRUE == stCsfbEmgCallLauFirstCfg.ucCsfbEmgCallLaiChgLauFirstFlg)
    {
        NAS_MML_SetCsfbEmgCallLaiChgLauFirstFlg(stCsfbEmgCallLauFirstCfg.ucCsfbEmgCallLaiChgLauFirstFlg);
    }

    return;
}





VOS_VOID NAS_MMC_ReadEHPlmnSupportNvim(VOS_VOID)
{
    NAS_MMC_NVIM_EHPLMN_SUPPORT_FLG_STRU                    stEHPlmnSupportFlg;
    NAS_MML_HPLMN_CFG_INFO_STRU                            *pstHplmnCfgInfo = VOS_NULL_PTR;
    VOS_UINT32                                              ulLength;

    ulLength        = 0;

    stEHPlmnSupportFlg.usEHPlmnSupportFlg = VOS_FALSE;

    pstHplmnCfgInfo = NAS_MML_GetHplmnCfg();

    (VOS_VOID)NV_GetLength(en_NV_Item_Standard_EHplmn_Support_Flg, &ulLength);
    if (ulLength > sizeof(stEHPlmnSupportFlg))
    {
        return;
    }

    if (NV_OK != NV_Read(en_NV_Item_Standard_EHplmn_Support_Flg,
                         &stEHPlmnSupportFlg, ulLength))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC,
                      "NAS_MMC_ReadEHPlmnSupportNvim(): en_NV_Item_Standard_EHplmn_Support_Flg Error");
        return;
    }

    if ((NAS_MMC_NV_ITEM_ACTIVE != stEHPlmnSupportFlg.usEHPlmnSupportFlg)
     && (NAS_MMC_NV_ITEM_DEACTIVE != stEHPlmnSupportFlg.usEHPlmnSupportFlg))
    {
        return;
    }

    pstHplmnCfgInfo->ucEhplmnSupportFlg = (VOS_UINT8)stEHPlmnSupportFlg.usEHPlmnSupportFlg;

    return;
}


VOS_VOID NAS_MMC_ReadActingHPlmnSupportNvim(VOS_VOID)
{
    NVIM_ACTING_HPLMN_SUPPORT_FLAG_STRU                     stActingHPlmnSupport;
    VOS_UINT32                                              ulLength;


    PS_MEM_SET(&stActingHPlmnSupport, 0x00, sizeof(NVIM_ACTING_HPLMN_SUPPORT_FLAG_STRU));
    ulLength = 0;

    /* �Ȼ�ȡNV�ĳ��� */
    (VOS_VOID)NV_GetLength(en_NV_Item_ACTING_PLMN_SUPPORT_FLAG, &ulLength);

    if (ulLength > sizeof(NVIM_ACTING_HPLMN_SUPPORT_FLAG_STRU))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadActingHPlmnSupportNvim():WARNING: en_NV_Item_ACTING_PLMN_SUPPORT_FLAG length Error");
        return;
    }

    /* ��ȡACTING-HPLMN����NV */
    if (NV_OK != NV_Read(en_NV_Item_ACTING_PLMN_SUPPORT_FLAG,
                         &stActingHPlmnSupport, sizeof(NVIM_ACTING_HPLMN_SUPPORT_FLAG_STRU)))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC,
                      "NAS_MMC_ReadActingHPlmnSupportNvim(): en_NV_Item_ACTING_PLMN_SUPPORT_FLAG Error");
        return;
    }

    if (NAS_MMC_NV_ITEM_ACTIVE == stActingHPlmnSupport.ucNvimActiveFlg)
    {
        /* ��ֵACTING-HPLMN���Ʊ�־ */
        NAS_MML_SetActingHplmnSupportFlg(VOS_TRUE);
    }

    return;
}



VOS_VOID NAS_MMC_ReadSearchHPlmnFlgAutoModeNvim(VOS_VOID)
{
    NAS_MMC_NVIM_AUTO_SEARCH_HPLMN_FLG_STRU                 stHplmnSearchFlg;
    NAS_MML_HPLMN_CFG_INFO_STRU                            *pstHplmnCfgInfo = VOS_NULL_PTR;
    VOS_UINT32                                              ulLength;

    ulLength        = 0;

    stHplmnSearchFlg.usAutoSearchHplmnFlg  = 0;

    pstHplmnCfgInfo = NAS_MML_GetHplmnCfg();

    (VOS_VOID)NV_GetLength(en_NV_Item_SrchHplmnFlg_StartOrAreaLostInAutoMode, &ulLength);
    if (ulLength > sizeof(stHplmnSearchFlg))
    {
        return;
    }

    if (NV_OK != NV_Read(en_NV_Item_SrchHplmnFlg_StartOrAreaLostInAutoMode,
                         &stHplmnSearchFlg, ulLength))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC,
                      "NAS_MMC_ReadSearchHPlmnFlgAutoModeNvim():en_NV_Item_SrchHplmnFlg_StartOrAreaLostInAutoMode Error");
        return;
    }

    if (stHplmnSearchFlg.usAutoSearchHplmnFlg >= NAS_MML_SEARCH_HPLMN_FLG_TYPE_BUTT )
    {
        return;
    }

    pstHplmnCfgInfo->enAutoSearchHplmnFlg = (VOS_UINT8)stHplmnSearchFlg.usAutoSearchHplmnFlg;
    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ReadAddEhplmnWhenSrchHplmnFlgNvim
 ��������  : ��NV�л�ȡNV��: en_NV_Item_SrchHplmnFlg_StartOrAreaLostInAutoMode
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :

  1.��    ��   : 2015��9��30��
    ��    ��   : c00318887
    �޸�����   : �½�����
*****************************************************************************/

VOS_VOID NAS_MMC_ReadAddEhplmnWhenSrchHplmnNvim(VOS_VOID)
{
    NAS_NVIM_ADD_EHPLMN_WHEN_SRCH_HPLMN_CFG_STRU            stAddEhplmnWhenSrchHplmnFlag;
    NAS_MML_HPLMN_CFG_INFO_STRU                            *pstHplmnCfgInfo = VOS_NULL_PTR;
    VOS_UINT32                                              ulLength;

    ulLength                                                = 0;

    stAddEhplmnWhenSrchHplmnFlag.ucActiveFlag               = VOS_FALSE;

    pstHplmnCfgInfo                                         = NAS_MML_GetHplmnCfg();

    (VOS_VOID)NV_GetLength(en_NV_Item_Add_EHPLMN_WHEN_SRCH_HPLMN_CFG, &ulLength);
    if (ulLength > sizeof(stAddEhplmnWhenSrchHplmnFlag))
    {
        return;
    }

    if (NV_OK != NV_Read(en_NV_Item_Add_EHPLMN_WHEN_SRCH_HPLMN_CFG,
                         &stAddEhplmnWhenSrchHplmnFlag, ulLength))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC,
                      "NAS_MMC_ReadAddEhplmnWhenSrchHplmnNvim():en_NV_Item_Add_EHPLMN_WHEN_SRCH_HPLMN_CFG Error");
        return;
    }

    if ((NAS_MMC_NV_ITEM_ACTIVE   != stAddEhplmnWhenSrchHplmnFlag.ucActiveFlag)
     && (NAS_MMC_NV_ITEM_DEACTIVE != stAddEhplmnWhenSrchHplmnFlag.ucActiveFlag))
    {
        return;
    }

    pstHplmnCfgInfo->ucAddEhplmnWhenSrchHplmnFlg            = stAddEhplmnWhenSrchHplmnFlag.ucActiveFlag;

    return;
}



VOS_VOID NAS_MMC_ReadSearchHPlmnFlgManualModeNvim(VOS_VOID)
{
    NAS_MMC_NVIM_MANUAL_SEARCH_HPLMN_FLG_STRU               stManualSearchHplmnFlg;
    NAS_MML_HPLMN_CFG_INFO_STRU                            *pstHplmnCfgInfo = VOS_NULL_PTR;
    VOS_UINT32                                              ulLength;

    ulLength        = 0;


    stManualSearchHplmnFlg.usManualSearchHplmnFlg = VOS_TRUE;

    pstHplmnCfgInfo = NAS_MML_GetHplmnCfg();

    (VOS_VOID)NV_GetLength(en_NV_Item_SrchHplmnFlg_StartInManualMode, &ulLength);
    if (ulLength > sizeof(stManualSearchHplmnFlg))
    {
        return;
    }

    if (NV_OK != NV_Read(en_NV_Item_SrchHplmnFlg_StartInManualMode,
                         &(stManualSearchHplmnFlg), ulLength))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadSearchHPlmnFlgManualModeNvim():en_NV_Item_SrchHplmnFlg_StartInManualMode Error");
        return;
    }

    if ((NAS_MMC_NV_ITEM_ACTIVE != stManualSearchHplmnFlg.usManualSearchHplmnFlg)
     && (NAS_MMC_NV_ITEM_DEACTIVE != stManualSearchHplmnFlg.usManualSearchHplmnFlg))
    {
        return;
    }

    pstHplmnCfgInfo->ucManualSearchHplmnFlg = (VOS_UINT8)stManualSearchHplmnFlg.usManualSearchHplmnFlg;

    return;
}


VOS_VOID NAS_MMC_ReadSearchHplmnFlgPowerOnNvim(VOS_VOID)
{
    NAS_MMC_NVIM_HPLMN_SEARCH_POWERON_STRU                  stHplmnSearchPowerOn;
    NAS_MML_HPLMN_CFG_INFO_STRU                            *pstHplmnCfgInfo = VOS_NULL_PTR;
    VOS_UINT32                                              ulLength;

    ulLength        = 0;


    stHplmnSearchPowerOn.ucHplmnSearchPowerOn = VOS_FALSE;

    pstHplmnCfgInfo = NAS_MML_GetHplmnCfg();

    (VOS_VOID)NV_GetLength(en_NV_Item_SearchHplmnAtPowerOn, &ulLength);
    if (ulLength > sizeof(stHplmnSearchPowerOn))
    {
        return;
    }

    if (NV_OK != NV_Read(en_NV_Item_SearchHplmnAtPowerOn, &stHplmnSearchPowerOn, ulLength))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadSearchHplmnFlgPowerOnNvim():en_NV_Item_SearchHplmnAtPowerOn Error");
        return;
    }

    if ((NAS_MMC_NV_ITEM_ACTIVE != stHplmnSearchPowerOn.ucHplmnSearchPowerOn)
     && (NAS_MMC_NV_ITEM_DEACTIVE != stHplmnSearchPowerOn.ucHplmnSearchPowerOn))
    {
        return;
    }

    pstHplmnCfgInfo->ucHplmnSearchPowerOn = stHplmnSearchPowerOn.ucHplmnSearchPowerOn;

    return;
}



VOS_VOID NAS_MMC_ReadEnhancedHPlmnSearchFlagNvim(VOS_VOID)
{
    NAS_MML_BG_SEARCH_CFG_INFO_STRU                        *pstBgSearchCfg = VOS_NULL_PTR;
    NAS_MMC_NVIM_ENHANCED_HPLMN_SRCH_FLG_STRU               stEnhancedHplmnSrchFlg;
    VOS_UINT32                                              ulLength;

    ulLength        = 0;


    stEnhancedHplmnSrchFlg.usEnhancedHplmnSrchFlg = VOS_FALSE;

    pstBgSearchCfg = NAS_MML_GetBgSearchCfg();
    (VOS_VOID)NV_GetLength(en_NV_Item_Enhanced_Hplmn_Srch_Flg, &ulLength);
    if (ulLength > sizeof(stEnhancedHplmnSrchFlg))
    {
        return;
    }
    if (NV_OK != NV_Read(en_NV_Item_Enhanced_Hplmn_Srch_Flg, &stEnhancedHplmnSrchFlg, ulLength))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC,"NAS_MMC_ReadEnhancedHPlmnSearchFlagNvim(): en_NV_Item_Enhanced_Hplmn_Srch_Flg Error");
        return;
    }

    if ((NAS_MMC_NV_ITEM_ACTIVE != stEnhancedHplmnSrchFlg.usEnhancedHplmnSrchFlg)
     && (NAS_MMC_NV_ITEM_DEACTIVE != stEnhancedHplmnSrchFlg.usEnhancedHplmnSrchFlg))
    {
        return;
    }

    pstBgSearchCfg->ucEnhancedHplmnSrchFlg = (VOS_UINT8)stEnhancedHplmnSrchFlg.usEnhancedHplmnSrchFlg;

    return;
}


VOS_VOID NAS_MMC_ReadSpecialRoamFlgNvim(VOS_VOID)
{
    NAS_MMC_NVIM_SPECIAL_ROAM_STRU      stSpecialRoam;
    NAS_MML_BG_SEARCH_CFG_INFO_STRU    *pstBgSearchCfg = VOS_NULL_PTR;
    VOS_UINT32                          ulLength;

    ulLength        = 0;


    stSpecialRoam.ucStatus         = NAS_MMC_NV_ITEM_DEACTIVE;
    stSpecialRoam.ucSpecialRoamFlg = VOS_FALSE;

    pstBgSearchCfg = NAS_MML_GetBgSearchCfg();
    (VOS_VOID)NV_GetLength(en_NV_Item_Special_Roam_Flag, &ulLength);
    if (ulLength > sizeof(stSpecialRoam))
    {
        return;
    }
    if (NV_OK != NV_Read (en_NV_Item_Special_Roam_Flag, &stSpecialRoam, ulLength))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadSpecialRoamFlgNvim():en_NV_Item_Special_Roam_Flag Error");
        return;
    }

    if (NAS_MMC_NV_ITEM_ACTIVE == stSpecialRoam.ucStatus)
    {
        pstBgSearchCfg->ucSpecialRoamFlg = stSpecialRoam.ucSpecialRoamFlg;
    }

    return;
}



VOS_VOID NAS_MMC_ReadNetworkNameNvim( VOS_VOID )
{
    NAS_MMC_NVIM_OPERATOR_NAME_INFO_STRU                    stNvimOperatorName;
    NAS_MML_OPERATOR_NAME_INFO_STRU                        *pstOperatorName;

    pstOperatorName = NAS_MML_GetOperatorNameInfo();

    if(NV_OK != NV_Read (en_NV_Item_Network_Name_From_MM_Info, &stNvimOperatorName, sizeof(stNvimOperatorName)))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadNetworkNameNvim:WARNING: Read NV Item Fail.");
        return;
    }

    pstOperatorName->stOperatorPlmnId.ulMcc = stNvimOperatorName.stOperatorPlmnId.ulMcc;
    pstOperatorName->stOperatorPlmnId.ulMnc = stNvimOperatorName.stOperatorPlmnId.ulMnc;
    PS_MEM_CPY(pstOperatorName->aucOperatorNameLong, stNvimOperatorName.aucOperatorNameLong, NAS_NVIM_MAX_OPER_LONG_NAME_LEN);
    PS_MEM_CPY(pstOperatorName->aucOperatorNameShort, stNvimOperatorName.aucOperatorNameShort, NAS_NVIM_MAX_OPER_SHORT_NAME_LEN);

}


VOS_UINT32 NAS_MMC_IsInNvEplmnList(
    NVIM_PLMN_VALUE_STRU               *pstPlmnId,
    VOS_UINT8                           ucPlmnNum,
    NVIM_PLMN_VALUE_STRU               *pstPlmnIdList
)
{
    VOS_UINT32                          i;

    for ( i = 0 ; i < ucPlmnNum ; i++ )
    {
        if ( (pstPlmnId->ucMcc[0] == pstPlmnIdList[i].ucMcc[0])
          && (pstPlmnId->ucMcc[1] == pstPlmnIdList[i].ucMcc[1])
          && (pstPlmnId->ucMcc[2] == pstPlmnIdList[i].ucMcc[2])
          && (pstPlmnId->ucMnc[0] == pstPlmnIdList[i].ucMnc[0])
          && (pstPlmnId->ucMnc[1] == pstPlmnIdList[i].ucMnc[1])
          && (pstPlmnId->ucMnc[2] == pstPlmnIdList[i].ucMnc[2]) )
        {
            return VOS_TRUE;
        }
    }
    return VOS_FALSE;
}




VOS_VOID NAS_MMC_ConvertMmlPlmnIdToNvimEquPlmn(
    NAS_MML_PLMN_ID_STRU               *pstMmlPlmnId,
    NVIM_PLMN_VALUE_STRU               *pstNvimPlmnId
)
{
    /* ת��MCC */
    pstNvimPlmnId->ucMcc[0] = (VOS_UINT8)(pstMmlPlmnId->ulMcc & NAS_MML_OCTET_LOW_FOUR_BITS);

    pstNvimPlmnId->ucMcc[1] = (VOS_UINT8)((pstMmlPlmnId->ulMcc >> 8) & NAS_MML_OCTET_LOW_FOUR_BITS);

    pstNvimPlmnId->ucMcc[2] = (VOS_UINT8)((pstMmlPlmnId->ulMcc >> 16) & NAS_MML_OCTET_LOW_FOUR_BITS);

    /* ת��MNC */
    pstNvimPlmnId->ucMnc[0] = (VOS_UINT8)(pstMmlPlmnId->ulMnc & NAS_MML_OCTET_LOW_FOUR_BITS);

    pstNvimPlmnId->ucMnc[1] = (VOS_UINT8)((pstMmlPlmnId->ulMnc >> 8) & NAS_MML_OCTET_LOW_FOUR_BITS);

    pstNvimPlmnId->ucMnc[2] = (VOS_UINT8)((pstMmlPlmnId->ulMnc >> 16) & NAS_MML_OCTET_LOW_FOUR_BITS);

}


VOS_VOID NAS_MMC_ConvertMmlEquListToNvimEquPlmnList(
    NAS_MML_EQUPLMN_INFO_STRU          *pstMmlEPlmnList,
    NVIM_EQUIVALENT_PLMN_LIST_STRU     *pstNvimEPlmnList
)
{
    VOS_UINT8                           i;

    pstNvimEPlmnList->ucCount = pstMmlEPlmnList->ucEquPlmnNum;

    if (pstNvimEPlmnList->ucCount > NVIM_MAX_EPLMN_NUM)
    {
        pstNvimEPlmnList->ucCount = NVIM_MAX_EPLMN_NUM;
    }

    for (i = 0; i < pstNvimEPlmnList->ucCount; i++)
    {
        NAS_MMC_ConvertMmlPlmnIdToNvimEquPlmn(&(pstMmlEPlmnList->astEquPlmnAddr[i]),
                                              &(pstNvimEPlmnList->struPlmnList[i]));

    }

    return;
}


VOS_UINT32 NAS_MMC_IsNvimEPlmnListEqual(
    NVIM_EQUIVALENT_PLMN_LIST_STRU     *pstNvimEPlmnList1,
    NVIM_EQUIVALENT_PLMN_LIST_STRU     *pstNvimEPlmnList2
)
{
    VOS_UINT32                          i;

    if (pstNvimEPlmnList1->ucCount != pstNvimEPlmnList2->ucCount)
    {
        return VOS_FALSE;
    }

    /* Eplmn��������0,��Rplmn��ͬʱ��EplmnList����ͬ */
    if (pstNvimEPlmnList1->ucCount > 0)
    {
        if (VOS_FALSE == NAS_MMC_IsInNvEplmnList(&(pstNvimEPlmnList1->struPlmnList[0]),
											     1,
                                                 pstNvimEPlmnList2->struPlmnList))
        {
            return VOS_FALSE;
        }
    }
    else
    {
        return VOS_TRUE;
    }

    /* ����Eplmnû�н������������ظ����ݣ���Ҫ�Ա�2���б����ȷ����ͬ */
    for ( i = 1 ; i < pstNvimEPlmnList1->ucCount ; i++ )
    {
        if (VOS_FALSE == NAS_MMC_IsInNvEplmnList(&(pstNvimEPlmnList1->struPlmnList[i]),
											     pstNvimEPlmnList2->ucCount,
                                                 pstNvimEPlmnList2->struPlmnList))
        {
            return VOS_FALSE;
        }
    }

    for ( i = 1 ; i < pstNvimEPlmnList2->ucCount ; i++ )
    {
        if (VOS_FALSE == NAS_MMC_IsInNvEplmnList(&(pstNvimEPlmnList2->struPlmnList[i]),
                                                 pstNvimEPlmnList1->ucCount,
                                                 pstNvimEPlmnList1->struPlmnList))
        {
            return VOS_FALSE;
        }
    }

    return VOS_TRUE;
}


VOS_VOID NAS_MMC_DeleteEPlmnList( VOS_VOID )
{
    NAS_MML_EQUPLMN_INFO_STRU          *pstEPlmnList    = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU               *pstCurrPlmnId = VOS_NULL_PTR;

    pstEPlmnList   = NAS_MML_GetEquPlmnList();

    /* ɾ��Eplmn */
    NAS_MML_InitEquPlmnInfo(pstEPlmnList);

    /* ����NV��Eplmn */
    NAS_MMC_WriteEplmnNvim();

    /*����ǰ�������Eplmn�б�*/
    pstCurrPlmnId = NAS_MML_GetCurrCampPlmnId();

    pstEPlmnList->astEquPlmnAddr[0].ulMcc = pstCurrPlmnId->ulMcc;
    pstEPlmnList->astEquPlmnAddr[0].ulMnc = pstCurrPlmnId->ulMnc;

    pstEPlmnList->ucEquPlmnNum = 1;

    return;
}
VOS_VOID NAS_MMC_WriteEplmnNvim(VOS_VOID)
{
    VOS_UINT32                          ulUpdateNvFlag;
    NVIM_EQUIVALENT_PLMN_LIST_STRU     *pstNewNvEquPlmnList = VOS_NULL_PTR;
    NVIM_EQUIVALENT_PLMN_LIST_STRU     *pstOldNvEquPlmnList = VOS_NULL_PTR;


    ulUpdateNvFlag  = VOS_FALSE;

    pstNewNvEquPlmnList = (NVIM_EQUIVALENT_PLMN_LIST_STRU*)PS_MEM_ALLOC(
                                                      WUEPS_PID_MMC,
                                                      sizeof(NVIM_EQUIVALENT_PLMN_LIST_STRU));

    if (VOS_NULL_PTR == pstNewNvEquPlmnList)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_WriteEplmnNvim:ERROR: Memory Alloc Error");
        return;
    }

    pstOldNvEquPlmnList = (NVIM_EQUIVALENT_PLMN_LIST_STRU*)PS_MEM_ALLOC(
                                                        WUEPS_PID_MMC,
                                                        sizeof (NVIM_EQUIVALENT_PLMN_LIST_STRU));

    if (VOS_NULL_PTR == pstOldNvEquPlmnList)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_WriteEplmnNvim:ERROR: Memory Alloc Error");
        PS_MEM_FREE(WUEPS_PID_MMC, pstNewNvEquPlmnList);
        return;
    }

    PS_MEM_SET(pstNewNvEquPlmnList, 0, sizeof(NVIM_EQUIVALENT_PLMN_LIST_STRU));
    PS_MEM_SET(pstOldNvEquPlmnList, 0, sizeof(NVIM_EQUIVALENT_PLMN_LIST_STRU));

    NAS_MMC_ConvertMmlEquListToNvimEquPlmnList(NAS_MML_GetEquPlmnList(),
                                               pstNewNvEquPlmnList);

    /* ��ȡNV��EPLMN��Ϣ */
    if ( NV_OK == NV_Read(en_NV_Item_EquivalentPlmn,
                         pstOldNvEquPlmnList, sizeof(NVIM_EQUIVALENT_PLMN_LIST_STRU)) )
    {
        if (VOS_FALSE == NAS_MMC_IsNvimEPlmnListEqual(pstNewNvEquPlmnList,
                                                      pstOldNvEquPlmnList))
        {
            ulUpdateNvFlag = VOS_TRUE;
        }
    }
    else
    {
        /* ��ȡ NV ʧ�ܣ���Ҫ���� EPLMN */
        ulUpdateNvFlag = VOS_TRUE;
    }

    if ( VOS_TRUE == ulUpdateNvFlag )
    {
        if (NV_OK != NV_Write(en_NV_Item_EquivalentPlmn,
                              pstNewNvEquPlmnList,
                              sizeof(NVIM_EQUIVALENT_PLMN_LIST_STRU)))
        {
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_WriteEplmnNvim:WARNING: en_NV_Item_EquivalentPlmn Error");
        }
    }

    PS_MEM_FREE(WUEPS_PID_MMC, pstNewNvEquPlmnList);
    PS_MEM_FREE(WUEPS_PID_MMC, pstOldNvEquPlmnList);


}
VOS_VOID NAS_MMC_ReadHplmnFirstSearchPeriodNvim(VOS_VOID)
{
    NAS_NVIM_HPLMN_FIRST_TIMER_STRU stFirstHplmnTime;
    NAS_MML_BG_SEARCH_CFG_INFO_STRU    *pstBgSearchCfg = VOS_NULL_PTR;

    pstBgSearchCfg = NAS_MML_GetBgSearchCfg();

    /* ��ʼĬ��Ϊ2���� */
    stFirstHplmnTime.ucHplmnTimerLen = 2;
    if (NV_OK != NV_Read (en_NV_Item_HPlmnFirstTimer, &(stFirstHplmnTime.ucHplmnTimerLen), sizeof(VOS_UINT8)))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadHplmnFirstSearchPeriodNvim():WARNING: en_NV_Item_HPlmnFirstTimer Error");
        return;
    }

    /* NV�������Է����������,ʵ����������ʱ��ʱ��Ҫ��ms������ */
    pstBgSearchCfg->ulFirstStartHplmnTimerLen = (stFirstHplmnTime.ucHplmnTimerLen) * NAS_MML_SIXTY_SECOND * NAS_MML_ONE_THOUSAND_MILLISECOND;

    return;
}


VOS_VOID NAS_MMC_ReadDefaultHplmnSrchPeriodNvim(VOS_VOID)
{
    NAS_MMC_NVIM_DEFAULT_MAX_HPLMN_PERIOD_STRU   stDefaultHplmnSrchPeri;
    NAS_MML_BG_SEARCH_CFG_INFO_STRU             *pstBgSearchCfg = VOS_NULL_PTR;


    stDefaultHplmnSrchPeri.ucDefaultMaxHplmnPeriFlg = NAS_MMC_NV_ITEM_DEACTIVE;
    stDefaultHplmnSrchPeri.ucDefaultMaxHplmnTim     = 0;

    pstBgSearchCfg = NAS_MML_GetBgSearchCfg();

    if (NV_OK != NV_Read(en_NV_Item_Default_Max_Hplmn_Srch_Peri,
                         &stDefaultHplmnSrchPeri,
                         sizeof(NAS_MMC_NVIM_DEFAULT_MAX_HPLMN_PERIOD_STRU)))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC,
                      "NAS_MMC_ReadDefaultHplmnSrchPeriodNvim(): en_NV_Item_Default_Hplmn_Srch_Peri Error");
        return;
    }

    if (NAS_MMC_NV_ITEM_ACTIVE == stDefaultHplmnSrchPeri.ucDefaultMaxHplmnPeriFlg)
    {
        pstBgSearchCfg->stDefaultMaxHplmnTimerPeriod.ucNvimActiveFlg      = stDefaultHplmnSrchPeri.ucDefaultMaxHplmnPeriFlg;

        /* NVIM�����Է����������,������ʱ����Ҫ��ms������ */
        pstBgSearchCfg->stDefaultMaxHplmnTimerPeriod.ulDefaultMaxHplmnLen = stDefaultHplmnSrchPeri.ucDefaultMaxHplmnTim * NAS_MML_SIXTY_SECOND * NAS_MML_ONE_THOUSAND_MILLISECOND;
    }

    return;
}

/* Added by c00318887 for file refresh��Ҫ����������, 2015-4-28, begin */
/*****************************************************************************
 �� �� ��  : NAS_MMC_ReadHighPrioPlmnRefreshTriggerBGSearchFlagNvim
 ��������  : ��ȡen_NV_Item_HIGH_PRIO_PLMN_REFRESH_TRIGGER_BG_SEARCH_CFG nv������
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��04��28��
    ��    ��   : c00318887
    �޸�����   : for file refresh ����
*****************************************************************************/
VOS_VOID NAS_MMC_ReadHighPrioPlmnRefreshTriggerBGSearchFlagNvim(VOS_VOID)
{
    NAS_MMC_NVIM_HIGH_PRIO_PLMN_REFRESH_TRIGGER_BG_SEARCH_STRU  stHighPrioPlmnRefreshTriggerBGSearchCfg;
    VOS_UINT32                                                  ulLength;

    ulLength = 0;
    PS_MEM_SET(&stHighPrioPlmnRefreshTriggerBGSearchCfg, 0x0, sizeof(NAS_MMC_NVIM_HIGH_PRIO_PLMN_REFRESH_TRIGGER_BG_SEARCH_STRU));

    /* �Ȼ�ȡNV�ĳ��� */
    (VOS_VOID)NV_GetLength(en_NV_Item_HIGH_PRIO_PLMN_REFRESH_TRIGGER_BG_SEARCH_CFG, &ulLength);

    if (ulLength > sizeof(NAS_MMC_NVIM_HIGH_PRIO_PLMN_REFRESH_TRIGGER_BG_SEARCH_STRU))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC,
                      "NAS_MMC_ReadHighPrioPlmnRefreshTriggerBGSearchFlagNvim(): en_NV_Item_HIGH_PRIO_PLMN_REFRESH_TRIGGER_BG_SEARCH_CFG length Error");
        return;
    }


    if (NV_OK != NV_Read (en_NV_Item_HIGH_PRIO_PLMN_REFRESH_TRIGGER_BG_SEARCH_CFG, &stHighPrioPlmnRefreshTriggerBGSearchCfg, sizeof(NAS_MMC_NVIM_HIGH_PRIO_PLMN_REFRESH_TRIGGER_BG_SEARCH_STRU)))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC,
                      "NAS_MMC_ReadHighPrioPlmnRefreshTriggerBGSearchFlagNvim():WARNING: en_NV_Item_HIGH_PRIO_PLMN_REFRESH_TRIGGER_BG_SEARCH_CFG Error");
        return;
    }

    if (NAS_MMC_NV_ITEM_ACTIVE == stHighPrioPlmnRefreshTriggerBGSearchCfg.ucTriggerBGSearchFlag)
    {
        NAS_MML_SetHighPrioPlmnRefreshTriggerBGSearchFlag(stHighPrioPlmnRefreshTriggerBGSearchCfg.ucTriggerBGSearchFlag);

        /* NVIM���������������,������ʱ����Ҫ��ms������ */
        if (0 == stHighPrioPlmnRefreshTriggerBGSearchCfg.usSearchDelayLen)
        {
            stHighPrioPlmnRefreshTriggerBGSearchCfg.usSearchDelayLen = NV_ITEM_HIGH_PRIO_PLMN_REFRESH_TRIGGER_BG_SEARCH_DEFAULT_DELAY_LEN;
        }

        NAS_MML_SetHighPrioPlmnRefreshTriggerBGSearchDelayLen(stHighPrioPlmnRefreshTriggerBGSearchCfg.usSearchDelayLen * 1000);
    }

    return;
}

/* Added by c00318887 for file refresh��Ҫ����������, 2015-4-28, end */

VOS_VOID NAS_MMC_ReadSrchHplmnTtimerValueNvim(VOS_VOID)
{
    NAS_MMC_NVIM_SEARCH_HPLMN_TIMER_STRU stSrchHplmnTimer;
    NAS_MML_BG_SEARCH_CFG_INFO_STRU     *pstBgSearchCfg = VOS_NULL_PTR;


    stSrchHplmnTimer.ucStatus              = NAS_MMC_NV_ITEM_DEACTIVE;
    stSrchHplmnTimer.usSrchHplmnTimerValue = 0;

    pstBgSearchCfg = NAS_MML_GetBgSearchCfg();

    if (NV_OK != NV_Read (en_NV_Item_SearchHplmnTtimerValue, &stSrchHplmnTimer, sizeof(NAS_MMC_NVIM_SEARCH_HPLMN_TIMER_STRU)))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC,
                      "NAS_MMC_ReadSrchHplmnTtimerValueNvim():WARNING: en_NV_Item_SearchHplmnTtimerValue Error");
        return;
    }

    if (NAS_MMC_NV_ITEM_ACTIVE == stSrchHplmnTimer.ucStatus)
    {
        pstBgSearchCfg->stNonFirstHplmnTimerPeriod.ucNvimActiveFlg         = stSrchHplmnTimer.ucStatus;
        pstBgSearchCfg->stNonFirstHplmnTimerPeriod.ulNonFirstHplmnTimerLen = stSrchHplmnTimer.usSrchHplmnTimerValue * NAS_MML_SIXTY_SECOND * NAS_MML_ONE_THOUSAND_MILLISECOND;
    }

    return;
}


VOS_VOID NAS_MMC_ReadWhiteOpeLockPlmnInfoNvim( VOS_VOID )
{
    NAS_MMC_NVIM_OPER_LOCK_WHITEPLMN_STRU stOperLockPlmnList;
    NAS_MML_PLMN_LOCK_CFG_INFO_STRU      *pstPlmnLockCfgInfo = VOS_NULL_PTR;


    stOperLockPlmnList.ulWhitePlmnLockNum = 0;

    pstPlmnLockCfgInfo = NAS_MML_GetPlmnLockCfg();

    if (NV_OK != NV_Read (en_NV_Item_OPERLOCK_PLMN_INFO_WHITE, &stOperLockPlmnList, sizeof(NAS_MMC_NVIM_OPER_LOCK_WHITEPLMN_STRU)))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadWhiteOpeLockPlmnInfoNvim:Read NV Failed");
        return;
    }

    if (0 != stOperLockPlmnList.ulWhitePlmnLockNum)
    {
        /* ��������Ч */
        pstPlmnLockCfgInfo->ucWhitePlmnLockNum = (VOS_UINT8)stOperLockPlmnList.ulWhitePlmnLockNum;

        if (stOperLockPlmnList.ulWhitePlmnLockNum > NAS_MML_MAX_WHITE_LOCK_PLMN_NUM)
        {
            pstPlmnLockCfgInfo->ucWhitePlmnLockNum = NAS_MML_MAX_WHITE_LOCK_PLMN_NUM;
        }

        PS_MEM_CPY(pstPlmnLockCfgInfo->astWhitePlmnId,
                   stOperLockPlmnList.astWhitePlmnId,
                   (sizeof(NAS_MML_PLMN_ID_STRU) * NAS_MML_MAX_WHITE_LOCK_PLMN_NUM));
    }

    return;
}
VOS_VOID NAS_MMC_ReadBlackOperLockPlmnInfoNvim( VOS_VOID )
{
    NAS_MMC_NVIM_OPER_LOCK_BLACKPLMN_STRU stOperLockPlmnList;
    NAS_MML_PLMN_LOCK_CFG_INFO_STRU      *pstPlmnLockCfgInfo = VOS_NULL_PTR;


    stOperLockPlmnList.ulBlackPlmnLockNum = 0;


    PS_MEM_SET(&stOperLockPlmnList, 0x00, sizeof(stOperLockPlmnList));

    pstPlmnLockCfgInfo = NAS_MML_GetPlmnLockCfg();

    if (NV_OK != NV_Read (en_NV_Item_OperLock_Plmn_Info, &stOperLockPlmnList, sizeof(NAS_MMC_NVIM_OPER_LOCK_BLACKPLMN_STRU)))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadBlackOperLockPlmnInfoNvim:Read NV Failed");
        return;
    }

    pstPlmnLockCfgInfo->ucBlackPlmnLockNum = (VOS_UINT8)stOperLockPlmnList.ulBlackPlmnLockNum;

    if ( stOperLockPlmnList.ulBlackPlmnLockNum > NAS_MML_MAX_BLACK_LOCK_PLMN_NUM )
    {
        pstPlmnLockCfgInfo->ucBlackPlmnLockNum = NAS_MML_MAX_BLACK_LOCK_PLMN_NUM;
    }

    PS_MEM_CPY(pstPlmnLockCfgInfo->astBlackPlmnId,
               stOperLockPlmnList.astBlackPlmnId,
               (sizeof(NAS_MML_PLMN_ID_STRU) * NAS_MML_MAX_BLACK_LOCK_PLMN_NUM));

    return;
}


VOS_UINT32 NAS_MMC_IsRatForbiddenListNvimParaRangeValid(
    NAS_MMC_NVIM_RAT_FORBIDDEN_LIST_STRU *pstParaValue
)
{
    if (NAS_MMC_NVIM_RAT_FORBIDDEN_LIST_SWITCH_BUTT <= pstParaValue->enSwitchFlag)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_IsRatForbiddenListNvimValid:The para enSwitchFlag is invalid");
        return VOS_FALSE;
    }

    /* ������飬���NV���õ�SIM����Ŀ����NVIM_MAX_IMSI_FORBIDDEN_LIST_NUM������Ϊ���õ�NV�����Ƿ���ֱ�ӷ��أ�*/
    if ( NAS_NVIM_MAX_IMSI_FORBIDDEN_LIST_NUM < pstParaValue->ucImsiListNum )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_IsRatForbiddenListNvimValid:The para ucImsiListNum is invalid");
        return VOS_FALSE;
    }

    /* ������飬���NV���õĽ�ֹRAT��Ŀ����2������Ϊ���õ�NV�����Ƿ���ֱ�ӷ��� */
    if ( NAS_NVIM_MAX_SUPPORTED_FORBIDDEN_RAT_NUM < pstParaValue->ucForbidRatNum )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_IsRatForbiddenListNvimValid:The para ucForbidRatNum is invalid");
        return VOS_FALSE;
    }

    return VOS_TRUE;
}



VOS_UINT8 NAS_MMC_IsRatForbiddenListNvimValid(
    NAS_MMC_NVIM_RAT_FORBIDDEN_LIST_STRU *pstParaValue
)
{
    VOS_UINT32                          i;

    i = 0;

    if ( VOS_FALSE == NAS_MMC_IsRatForbiddenListNvimParaRangeValid(pstParaValue) )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_IsRatForbiddenListNvimValid:The para is invalid");
        return VOS_FALSE;
    }

    /* �����ֹ������ʽ�б��а���GSM���򷵻�VOS_FALSE */
    for (i = 0; i < pstParaValue->ucForbidRatNum; i++)
    {
        if (NAS_MMC_NVIM_PLATFORM_SUPPORT_RAT_GERAN == pstParaValue->aenForbidRatList[i])
        {
            NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_IsRatForbiddenListNvimValid:The para aenForbidRatList is invalid");
            return VOS_FALSE;
        }
    }

    /* �����ֹ���뼼������ĿΪ0��Ҳ��Ϊ��������ȷ�� */
    if (NAS_NVIM_FORBIDDEN_RAT_NUM_0 == pstParaValue->ucForbidRatNum)
    {
        return VOS_TRUE;
    }

    /* ֻ����������ϣ���LTE��LTE+UTRAN */
    if ((NAS_NVIM_FORBIDDEN_RAT_NUM_1             == pstParaValue->ucForbidRatNum)
     && (NAS_MMC_NVIM_PLATFORM_SUPPORT_RAT_EUTRAN == pstParaValue->aenForbidRatList[0]))
    {
        return VOS_TRUE;
    }

    if ((NAS_NVIM_FORBIDDEN_RAT_NUM_2 == pstParaValue->ucForbidRatNum))
    {
        if ((NAS_MMC_NVIM_PLATFORM_SUPPORT_RAT_UTRAN  == pstParaValue->aenForbidRatList[0])
         && (NAS_MMC_NVIM_PLATFORM_SUPPORT_RAT_EUTRAN == pstParaValue->aenForbidRatList[1]))
        {
            return VOS_TRUE;
        }

        if ((NAS_MMC_NVIM_PLATFORM_SUPPORT_RAT_EUTRAN == pstParaValue->aenForbidRatList[0])
         && (NAS_MMC_NVIM_PLATFORM_SUPPORT_RAT_UTRAN  == pstParaValue->aenForbidRatList[1]))
        {
            return VOS_TRUE;
        }

        if ((NAS_MMC_NVIM_PLATFORM_SUPPORT_RAT_EUTRAN == pstParaValue->aenForbidRatList[0])
         && (NAS_MMC_NVIM_PLATFORM_SUPPORT_RAT_EUTRAN == pstParaValue->aenForbidRatList[1]))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;

}
VOS_UINT32 NAS_MMC_ConvertNvimRatToMmlType(
    NAS_MMC_NVIM_PLATFORM_SUPPORT_RAT_ENUM_UINT8            enNvRatType,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                        *penMmlRatType
)
{
    switch(enNvRatType)
    {
        case NAS_MMC_NVIM_PLATFORM_SUPPORT_RAT_GERAN:
            *penMmlRatType = NAS_MML_NET_RAT_TYPE_GSM;
            break;

        case NAS_MMC_NVIM_PLATFORM_SUPPORT_RAT_UTRAN:
            *penMmlRatType = NAS_MML_NET_RAT_TYPE_WCDMA;
            break;

        case NAS_MMC_NVIM_PLATFORM_SUPPORT_RAT_EUTRAN:
            *penMmlRatType = NAS_MML_NET_RAT_TYPE_LTE;
            break;

        default:
            *penMmlRatType = NAS_MML_NET_RAT_TYPE_BUTT;
            return VOS_FALSE;
    }

    return VOS_TRUE;
}


VOS_VOID NAS_MMC_ReadRatForbiddenListConfigNvim( VOS_VOID )
{
    VOS_UINT32                                              i;
    NAS_MML_SIM_FORMAT_PLMN_ID                              stSimPlmn;
    NAS_MML_PLMN_ID_STRU                                    stPlmn;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enMmlRatType;

    NAS_MMC_NVIM_RAT_FORBIDDEN_LIST_STRU                    stRatForbiddenListCfgNvim;
    NAS_MML_RAT_FORBIDDEN_LIST_STRU                        *pstRatForbiddenList = VOS_NULL_PTR;

    PS_MEM_SET(&stRatForbiddenListCfgNvim, 0x00, sizeof(stRatForbiddenListCfgNvim));
    PS_MEM_SET(&stSimPlmn, 0x00, sizeof(stSimPlmn));
    PS_MEM_SET(&stPlmn, 0x00, sizeof(stPlmn));

    enMmlRatType = NAS_MML_NET_RAT_TYPE_BUTT;

    pstRatForbiddenList = NAS_MML_GetRatForbiddenListCfg();

    if (NV_OK != NV_Read(en_NV_Item_Rat_Forbidden_List_Config, &stRatForbiddenListCfgNvim, sizeof(NAS_MMC_NVIM_RAT_FORBIDDEN_LIST_STRU)))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadRatForbiddenListAccordImsiConfigNvim:Read NV Failed");
        return;
    }

    /* ͳһ��������� */
    if (VOS_FALSE == NAS_MMC_IsRatForbiddenListNvimValid(&stRatForbiddenListCfgNvim))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadRatForbiddenListAccordImsiConfigNvim:The paras of nvim is invalid");
        return;

    }
    /* ��NV�еĲ������浽MML */
    pstRatForbiddenList->enSwitchFlag   = stRatForbiddenListCfgNvim.enSwitchFlag;

    /* �����ֹRAT��Ϣ */
    pstRatForbiddenList->ucForbidRatNum = 0;
    for (i = 0; i < stRatForbiddenListCfgNvim.ucForbidRatNum; i++)
    {
        if (VOS_TRUE == NAS_MMC_ConvertNvimRatToMmlType(stRatForbiddenListCfgNvim.aenForbidRatList[i], &enMmlRatType))
        {
            pstRatForbiddenList->aenForbidRatList[pstRatForbiddenList->ucForbidRatNum] = enMmlRatType;
            pstRatForbiddenList->ucForbidRatNum++;
        }
    }

    pstRatForbiddenList->ucImsiListNum  = 0;

    /* ��USIM�б����PLMN��Ϣת��Ϊ�ڴ��е���Ϣ */
    for ( i = 0; i < stRatForbiddenListCfgNvim.ucImsiListNum; i++ )
    {
        PS_MEM_CPY(stSimPlmn.aucSimPlmn, stRatForbiddenListCfgNvim.astImsiList[i].aucSimPlmn, NAS_MML_SIM_PLMN_ID_LEN);
        NAS_MMC_ConvertSimPlmnToNasPLMN(&stSimPlmn, &stPlmn);

        if (VOS_TRUE == NAS_MML_IsPlmnIdValid(&stPlmn))
        {
            pstRatForbiddenList->astImsiList[pstRatForbiddenList->ucImsiListNum].ulMcc = stPlmn.ulMcc;
            pstRatForbiddenList->astImsiList[pstRatForbiddenList->ucImsiListNum].ulMnc = stPlmn.ulMnc;
            pstRatForbiddenList->ucImsiListNum++;
        }
    }

    return;
}



VOS_VOID NAS_MMC_ReadDisabledRatPlmnInfoNvim( VOS_VOID )
{
    NAS_MMC_NVIM_DISABLED_RAT_PLMN_INFO_STRU                stDisabledRatPlmnList;

    NAS_MML_DISABLED_RAT_PLMN_CFG_INFO_STRU                *pstDisabledRatPlmnCfgInfo;
    VOS_UINT32                                              i;


    PS_MEM_SET(&stDisabledRatPlmnList, 0x00, sizeof(stDisabledRatPlmnList));

    pstDisabledRatPlmnCfgInfo = NAS_MML_GetDisabledRatPlmnInfo();

    if (NV_OK != NV_Read (en_NV_Item_Disabled_Rat_Plmn_Info, &stDisabledRatPlmnList, sizeof(NAS_MMC_NVIM_DISABLED_RAT_PLMN_INFO_STRU)))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadDisabledRatPlmnInfoNvim:Read NV Failed");
        return;
    }

    pstDisabledRatPlmnCfgInfo->ulDisabledRatPlmnNum = (VOS_UINT8)stDisabledRatPlmnList.ulDisabledRatPlmnNum;

    if (stDisabledRatPlmnList.ulDisabledRatPlmnNum > NAS_MML_NVIM_MAX_DISABLED_RAT_PLMN_NUM)
    {
        pstDisabledRatPlmnCfgInfo->ulDisabledRatPlmnNum = NAS_MML_NVIM_MAX_DISABLED_RAT_PLMN_NUM;
    }

    for (i = 0; i < pstDisabledRatPlmnCfgInfo->ulDisabledRatPlmnNum; i++)
    {
        pstDisabledRatPlmnCfgInfo->astDisabledRatPlmnId[i].stPlmnWithRat.stPlmnId.ulMcc = stDisabledRatPlmnList.astDisabledRatPlmnId[i].ulMcc;
        pstDisabledRatPlmnCfgInfo->astDisabledRatPlmnId[i].stPlmnWithRat.stPlmnId.ulMnc = stDisabledRatPlmnList.astDisabledRatPlmnId[i].ulMnc;
        pstDisabledRatPlmnCfgInfo->astDisabledRatPlmnId[i].stPlmnWithRat.enRat          = stDisabledRatPlmnList.astDisabledRatPlmnId[i].enRat;

        pstDisabledRatPlmnCfgInfo->astDisabledRatPlmnId[i].ulPlmnDisabledForbiddenSlice   = NAS_MML_MAX_TIME_SLICE;

        pstDisabledRatPlmnCfgInfo->astDisabledRatPlmnId[i].ulPlmnDisabledBeginSlice     = 0;
    }

    return;
}


VOS_VOID NAS_MMC_ReadUserCfgExtEhplmnInfoNvim( VOS_VOID )
{
    VOS_UINT32                                              i;
    VOS_UINT32                                              j;
    VOS_UINT32                                              ulNvimEhplmnNum;
    NAS_MML_SIM_FORMAT_PLMN_ID                              stSimPlmn;
    NAS_MML_PLMN_ID_STRU                                    stPlmn;
    NAS_MMC_NVIM_USER_CFG_EXT_EHPLMN_INFO_STRU              stNvimCfgExtEhplmnInfo;
    NAS_MML_USER_CFG_EXT_EHPLMN_INFO_STRU                  *pstUserCfgExtEhplmnInfo;

    PS_MEM_SET(&stNvimCfgExtEhplmnInfo, 0x00, sizeof(stNvimCfgExtEhplmnInfo));

    pstUserCfgExtEhplmnInfo = NAS_MML_GetUserCfgExtEhplmnInfo();
    /*ѭ��������ʼ��*/
    ulNvimEhplmnNum = 0;

    if ( NV_OK != NV_Read( en_NV_Item_User_Cfg_Ext_Ehplmn_Info,
                            &stNvimCfgExtEhplmnInfo, sizeof(NAS_MMC_NVIM_USER_CFG_EXT_EHPLMN_INFO_STRU)) )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadUserCfgEhplmnInfoNvim:Read NV Failed");
        return;
    }

    ulNvimEhplmnNum = stNvimCfgExtEhplmnInfo.ulNvimEhplmnNum;
    pstUserCfgExtEhplmnInfo->ulUserCfgEhplmnNum = ulNvimEhplmnNum;
    if ( ulNvimEhplmnNum > NAS_MML_MAX_USER_CFG_EXT_EHPLMN_NUM )
    {
        ulNvimEhplmnNum = NAS_MML_MAX_USER_CFG_EXT_EHPLMN_NUM;
    }

    /* ��NV�е�PLMN LIST��Ϣ���浽MML��ȫ�ֱ�����ȥ */

    for (j = 0; j < ulNvimEhplmnNum; j++)
    {
        /* ��ʼ���ڴ��д��PLMN�����б���� */
        pstUserCfgExtEhplmnInfo->astUserCfgEhplmnInfo[j].ucImsiPlmnListNum = 0;

        /* ��ֹ����Խ�� */
        if (stNvimCfgExtEhplmnInfo.astNvimEhplmnInfo[j].ucImsiPlmnListNum > NAS_MMC_MAX_USER_CFG_IMSI_PLMN_NUM)
        {
            stNvimCfgExtEhplmnInfo.astNvimEhplmnInfo[j].ucImsiPlmnListNum = NAS_MMC_MAX_USER_CFG_IMSI_PLMN_NUM;
        }

        for ( i = 0; i < stNvimCfgExtEhplmnInfo.astNvimEhplmnInfo[j].ucImsiPlmnListNum; i++ )
        {
            PS_MEM_CPY(stSimPlmn.aucSimPlmn, stNvimCfgExtEhplmnInfo.astNvimEhplmnInfo[j].astImsiPlmnList[i].aucSimPlmn, NAS_MML_SIM_PLMN_ID_LEN);
            NAS_MMC_ConvertSimPlmnToNasPLMN(&stSimPlmn, &stPlmn);

            if (VOS_TRUE == NAS_MML_IsPlmnIdValid(&stPlmn))
            {
                pstUserCfgExtEhplmnInfo->astUserCfgEhplmnInfo[j].astImsiPlmnList[pstUserCfgExtEhplmnInfo->astUserCfgEhplmnInfo[j].ucImsiPlmnListNum] = stPlmn;
                pstUserCfgExtEhplmnInfo->astUserCfgEhplmnInfo[j].ucImsiPlmnListNum++;
            }
        }

        /* ��NV�е�EHplmn��Ϣ���浽MML��ȫ�ֱ�����ȥ */

        /* ��ʼ���ڴ��д��PLMN�����б���� */
        pstUserCfgExtEhplmnInfo->astUserCfgEhplmnInfo[j].ucEhplmnListNum = 0;

        /* ��ֹ����Խ�� */
        if ( stNvimCfgExtEhplmnInfo.astNvimEhplmnInfo[j].ucEhplmnListNum > NAS_MMC_MAX_USER_CFG_EHPLMN_NUM )
        {
            stNvimCfgExtEhplmnInfo.astNvimEhplmnInfo[j].ucEhplmnListNum = NAS_MMC_MAX_USER_CFG_EHPLMN_NUM;
        }

        for ( i = 0; i < stNvimCfgExtEhplmnInfo.astNvimEhplmnInfo[j].ucEhplmnListNum; i++ )
        {
            PS_MEM_CPY(stSimPlmn.aucSimPlmn, stNvimCfgExtEhplmnInfo.astNvimEhplmnInfo[j].astEhPlmnList[i].aucSimPlmn, NAS_MML_SIM_PLMN_ID_LEN);
            NAS_MMC_ConvertSimPlmnToNasPLMN(&stSimPlmn, &stPlmn);

            if (VOS_TRUE == NAS_MML_IsPlmnIdValid(&stPlmn))
            {
                pstUserCfgExtEhplmnInfo->astUserCfgEhplmnInfo[j].astEhPlmnList[pstUserCfgExtEhplmnInfo->astUserCfgEhplmnInfo[j].ucEhplmnListNum] = stPlmn;
                pstUserCfgExtEhplmnInfo->astUserCfgEhplmnInfo[j].ucEhplmnListNum++;
            }
        }
    }

    return;
}


VOS_VOID NAS_MMC_ReadAvailableTimerInfoNvim( VOS_VOID  )
{
    NAS_MML_AVAIL_TIMER_CFG_STRU       *pstAvailTimerCfg = VOS_NULL_PTR;
    NAS_MMC_NVIM_AVAIL_TIMER_CFG_STRU   stNvimAvailTimerCfg;


    PS_MEM_SET(&stNvimAvailTimerCfg, 0x00, sizeof(stNvimAvailTimerCfg));

    pstAvailTimerCfg = NAS_MML_GetAvailTimerCfg();

    if (NV_OK != NV_Read (en_NV_Item_SEARCH_TIMER_INFO, &stNvimAvailTimerCfg, sizeof(stNvimAvailTimerCfg)))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadAvailableTimerInfoNvim:Read NV Failed");
        return;
    }

    pstAvailTimerCfg->ulFirstSearchTimeCount = stNvimAvailTimerCfg.ulFirstSearchTimeCount;
    pstAvailTimerCfg->ulFirstSearchTimeLen   = stNvimAvailTimerCfg.ulFirstSearchTimeLen;
    pstAvailTimerCfg->ulDeepSearchTimeCount  = stNvimAvailTimerCfg.ulDeepSearchTimeCount;
    pstAvailTimerCfg->ulDeepSearchTimeLen    = stNvimAvailTimerCfg.ulDeepSearchTimeLen;
    return;
}


VOS_VOID NAS_MMC_ReadStandardSTKSteeringOfRoamingFlgNvim(VOS_VOID)
{
    NAS_MMC_NVIM_STK_STEERING_OF_ROAMING_SUPPORT_FLG_STRU   stStkSteeringOfRoamingSupportFlg;
    VOS_UINT32                                              ulLength;

    ulLength = 0;

    (VOS_VOID)NV_GetLength(en_NV_Item_Standard_STK_SteeringOfRoaming_Support_Flg, &ulLength);
    stStkSteeringOfRoamingSupportFlg.usStkSteeringOfRoamingSupportFlg = VOS_TRUE;

    if (NV_OK != NV_Read(en_NV_Item_Standard_STK_SteeringOfRoaming_Support_Flg,
                         &stStkSteeringOfRoamingSupportFlg,
                         ulLength))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadStandardSTKSteeringOfRoamingFlgNvim():WARNING: en_NV_Item_Standard_STK_SteeringOfRoaming_Support_Flg Error");
        return;
    }

    if ((NAS_MMC_NV_ITEM_ACTIVE !=  stStkSteeringOfRoamingSupportFlg.usStkSteeringOfRoamingSupportFlg)
     && (NAS_MMC_NV_ITEM_DEACTIVE !=  stStkSteeringOfRoamingSupportFlg.usStkSteeringOfRoamingSupportFlg))
    {
        return;
    }

    NAS_MML_SetStkSteeringOfRoamingSupportFlg((VOS_UINT8) stStkSteeringOfRoamingSupportFlg.usStkSteeringOfRoamingSupportFlg);

    return;
}


VOS_VOID NAS_MMC_ReadCsRejSearchSupportFlagNvim(VOS_VOID)
{
    NAS_MMC_NVIM_CS_REJ_SEARCH_SUPPORT_STRU  stCsRejSearchSupportFlg;
    VOS_UINT32                               ulLength;

    ulLength        = 0;


    stCsRejSearchSupportFlg.ucStatus                = NAS_MMC_NV_ITEM_DEACTIVE;
    stCsRejSearchSupportFlg.ucCsRejSearchSupportFlg = VOS_FALSE;

    (VOS_VOID)NV_GetLength(en_NV_Item_SteeringofRoaming_SUPPORT_CTRL, &ulLength);
    if (ulLength > sizeof(stCsRejSearchSupportFlg))
    {
        return;
    }

    if (NV_OK != NV_Read (en_NV_Item_SteeringofRoaming_SUPPORT_CTRL,
                          &stCsRejSearchSupportFlg, ulLength))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadCsRejSearchSupportFlagNvim():WARNING: NV_Read en_NV_Item_SteeringofRoaming_SUPPORT_CTRL Error");
        return;
    }

    if(NAS_MMC_NV_ITEM_ACTIVE == stCsRejSearchSupportFlg.ucStatus)
    {
        NAS_MML_SetCsRejSearchSupportFlg(stCsRejSearchSupportFlg.ucCsRejSearchSupportFlg);
    }

    return;
}


VOS_VOID NAS_MMC_ReadAutoAttachNvim(VOS_VOID)
{
    NAS_NVIM_AUTOATTACH_STRU            stAutoattachFlag;
    VOS_UINT32                          ulLength;

    ulLength        = 0;


    stAutoattachFlag.usAutoattachFlag= VOS_TRUE;

    (VOS_VOID)NV_GetLength(en_NV_Item_Autoattach, &ulLength);
    if (ulLength > sizeof(stAutoattachFlag))
    {
        return;
    }

    if(NV_OK != NV_Read (en_NV_Item_Autoattach, &stAutoattachFlag, ulLength))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadAutoAttachNvim():WARNING: en_NV_Item_Autoattach Error");
        return;
    }

    NAS_MML_SetPsAutoAttachFlg((VOS_UINT8)stAutoattachFlag.usAutoattachFlag);
    return;
}


VOS_VOID NAS_MMC_ReadPlmnSelectionModeNvim(VOS_VOID)
{
    NAS_NVIM_SELPLMN_MODE_STRU                          stPlmnSelMode;


    stPlmnSelMode.usSelPlmnMode = NAS_MMC_PLMN_SELECTION_MODE_BUTT;

    if (NV_OK != NV_Read (en_NV_Item_SelPlmn_Mode, &stPlmnSelMode.usSelPlmnMode, sizeof(stPlmnSelMode.usSelPlmnMode)))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadPlmnSelectionModeNvim():WARNING: en_NV_Item_SelPlmn_Mode Error");
        return;
    }

    if ((stPlmnSelMode.usSelPlmnMode != NAS_MMC_PLMN_SELECTION_MODE_AUTO)
     && (stPlmnSelMode.usSelPlmnMode != NAS_MMC_PLMN_SELECTION_MODE_MANUAL))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadPlmnSelectionModeNvim():NV parameter invalid");
        return;
    }

    NAS_MMC_SetPlmnSelectionMode((NAS_MMC_PLMN_SELECTION_MODE_ENUM_UINT8)(stPlmnSelMode.usSelPlmnMode));

    return;
}
VOS_VOID NAS_MMC_WritePlmnSelectionModeNvim(VOS_VOID)
{
    NAS_NVIM_SELPLMN_MODE_STRU          stPlmnSelMode;
    VOS_UINT32                          ulNvLength;

    ulNvLength = 0;
    stPlmnSelMode.usSelPlmnMode = NAS_MMC_GetPlmnSelectionMode();

    (VOS_VOID)NV_GetLength(en_NV_Item_SelPlmn_Mode, &ulNvLength);
    if (NV_OK != NV_Write(en_NV_Item_SelPlmn_Mode,
                      &stPlmnSelMode,
                      ulNvLength))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_WritePlmnSelectionModeNvim():en_NV_Item_SelPlmn_Mode Error");
    }

    return;
}


VOS_VOID NAS_MMC_ReadEquivalentPlmnNvim(VOS_VOID)
{

    NVIM_EQUIVALENT_PLMN_LIST_STRU      stEquivPlmn;
    VOS_UINT32                          i;
    NAS_MML_NETWORK_INFO_STRU          *pstNetWorkInfo = VOS_NULL_PTR;
    VOS_UINT32                          ulEquPlmnNum;


    PS_MEM_SET(&stEquivPlmn, 0x00, sizeof(stEquivPlmn));

    pstNetWorkInfo = NAS_MML_GetNetworkInfo();

    if (NV_OK != NV_Read (en_NV_Item_EquivalentPlmn, &stEquivPlmn, sizeof(NVIM_EQUIVALENT_PLMN_LIST_STRU)))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadEquivalentPlmnNvim():WARNING: en_NV_Item_EquivalentPlmn Error");
        return;
    }

    if ( NVIM_MAX_EPLMN_NUM < stEquivPlmn.ucCount)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadEquivalentPlmnNvim():ERROR: EquivalentPlmn Num ERROR.");
        stEquivPlmn.ucCount = NVIM_MAX_EPLMN_NUM;
    }

    ulEquPlmnNum = stEquivPlmn.ucCount;

    if (ulEquPlmnNum > NAS_MML_MAX_EQUPLMN_NUM)
    {
        ulEquPlmnNum = NAS_MML_MAX_EQUPLMN_NUM;
    }

    for (i = 0; i < ulEquPlmnNum; i++)
    {
        pstNetWorkInfo->stEquPlmnInfo.astEquPlmnAddr[i].ulMcc =
                            (stEquivPlmn.struPlmnList[i].ucMcc[0]
                            | ((VOS_UINT32)stEquivPlmn.struPlmnList[i].ucMcc[1] << 8)
                            | ((VOS_UINT32)stEquivPlmn.struPlmnList[i].ucMcc[2] << 16));

        pstNetWorkInfo->stEquPlmnInfo.astEquPlmnAddr[i].ulMnc =
                           (stEquivPlmn.struPlmnList[i].ucMnc[0]
                           | ((VOS_UINT32)stEquivPlmn.struPlmnList[i].ucMnc[1] << 8)
                           | ((VOS_UINT32)stEquivPlmn.struPlmnList[i].ucMnc[2] << 16));
    }

    /* ��EPLMN�б���ɾ����Ч������ */
    ulEquPlmnNum = NAS_MML_DelInvalidPlmnFromList(ulEquPlmnNum, pstNetWorkInfo->stEquPlmnInfo.astEquPlmnAddr);
    pstNetWorkInfo->stEquPlmnInfo.ucEquPlmnNum = (VOS_UINT8)ulEquPlmnNum;

    return;
}
VOS_VOID NAS_MMC_ReadMaxForbRoamLaNvim(VOS_VOID)
{
    NAS_MMC_NVIM_MAX_FORB_ROAM_LA_STRU   stMaxForbRoamLa;
    NAS_MML_MISCELLANEOUS_CFG_INFO_STRU *pstMiscellaneousCfgInfo = VOS_NULL_PTR;


    stMaxForbRoamLa.ucMaxForbRoamLaFlg = NAS_MMC_NV_ITEM_DEACTIVE;
    stMaxForbRoamLa.ucMaxForbRoamLaNum = 0;

    pstMiscellaneousCfgInfo = NAS_MML_GetMiscellaneousCfgInfo();

    if (NV_OK != NV_Read(en_NV_Item_Max_Forb_Roam_La,
                         &stMaxForbRoamLa, sizeof(NAS_MMC_NVIM_MAX_FORB_ROAM_LA_STRU)))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC,
                        "NAS_MMC_ReadMaxForbRoamLaNvim():WARNING: en_NV_Item_Max_Forb_Roam_La Error");
        return;
    }

    if (NAS_MMC_NV_ITEM_ACTIVE == stMaxForbRoamLa.ucMaxForbRoamLaFlg)
    {
        pstMiscellaneousCfgInfo->ucMaxForbRoamLaFlg = stMaxForbRoamLa.ucMaxForbRoamLaFlg;
        pstMiscellaneousCfgInfo->ucMaxForbRoamLaNum = stMaxForbRoamLa.ucMaxForbRoamLaNum;
    }

    return;
}


VOS_VOID NAS_MMC_ReadGsmForbidAccessInfoNvim(VOS_VOID)
{
    NAS_MMC_NVIM_EFUST_SERVICE_CFG_STRU  stEfustServiceCfg;
    NAS_MML_MISCELLANEOUS_CFG_INFO_STRU *pstMiscellaneousCfgInfo = VOS_NULL_PTR;


    PS_MEM_SET(&stEfustServiceCfg, 0x00, sizeof(NAS_MMC_NVIM_EFUST_SERVICE_CFG_STRU));

    pstMiscellaneousCfgInfo = NAS_MML_GetMiscellaneousCfgInfo();

    if (NV_OK != NV_Read(en_NV_Item_EFust_Service_Cfg,
                         &stEfustServiceCfg, sizeof(NAS_MMC_NVIM_EFUST_SERVICE_CFG_STRU)))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC,
                        "NAS_MMC_ReadGsmForbidAccessInfoNvim:WARNING: en_NV_Item_EFust_Service_Cfg Error");
        return;
    }

    if (NAS_MMC_NV_ITEM_ACTIVE == stEfustServiceCfg.ucStatus)
    {
        pstMiscellaneousCfgInfo->ucNvGsmForbidFlg = stEfustServiceCfg.ucForbidReg2GNetWork;
    }

    return;
}


VOS_VOID NAS_MMC_ReadRoamBrokerRegisterFailCntNvim(VOS_VOID)
{
    NAS_MMC_NVIM_REG_FAIL_CNT_STRU       stRegisterFailCnt;
    NAS_MML_MISCELLANEOUS_CFG_INFO_STRU *pstMiscellaneousCfgInfo = VOS_NULL_PTR;


    stRegisterFailCnt.ucNvActiveFlag = VOS_FALSE;
    stRegisterFailCnt.ucRegFailCnt   = 0;

    pstMiscellaneousCfgInfo = NAS_MML_GetMiscellaneousCfgInfo();

    if (NV_OK != NV_Read(en_NV_Item_Register_Fail_Cnt,
                         &stRegisterFailCnt, sizeof(NAS_MMC_NVIM_REG_FAIL_CNT_STRU)))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadRoamBrokerRegisterFailCntNvim():WARNING: en_Nv_Item_Register_Fail_Cnt Error");
        return;
    }

    pstMiscellaneousCfgInfo->ucRoamBrokerRegisterFailCnt = NAS_MML_MAX_CS_REG_FAIL_CNT;

    if ((VOS_TRUE == stRegisterFailCnt.ucNvActiveFlag)
     && (stRegisterFailCnt.ucRegFailCnt < NAS_MML_MAX_CS_REG_FAIL_CNT))
    {
        pstMiscellaneousCfgInfo->ucRoamBrokerRegisterFailCnt = stRegisterFailCnt.ucRegFailCnt;

        pstMiscellaneousCfgInfo->ucRoamBrokerActiveFlag      = VOS_TRUE;
    }


    return;
}


VOS_VOID NAS_MMC_ReadPsLociNvim(VOS_VOID)
{
    NAS_NVIM_PS_LOCI_SIM_FILES_STRU stPsLocInfo;


    PS_MEM_SET(&stPsLocInfo, 0x00, sizeof(stPsLocInfo));

    if (NV_OK != NV_Read(en_NV_Item_Ps_Loci,
                         &stPsLocInfo, NAS_NVIM_PS_LOCI_SIM_FILE_LEN))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadPsLociNvim():WARNING: en_NV_Item_Ps_Loci Error");

        return;
    }

    /* ����PTMSI������ */
    NAS_MMC_UpdatePtmsiFormPsLociFile(stPsLocInfo.aucPsLocInfo);

    /* ����PTMSI SIGNATURE������ */
    NAS_MMC_UpdatePtmsiSignatureFormPsLociFile(stPsLocInfo.aucPsLocInfo);

    /* ����RAI������ */
    NAS_MMC_UpdateRaiFormPsLociFile(stPsLocInfo.aucPsLocInfo);

    NAS_MML_UpdateSimPsLociFileContent(stPsLocInfo.aucPsLocInfo);

    /* ����GPRS��״̬ */
    if (stPsLocInfo.aucPsLocInfo[NAS_MML_PS_LOCI_SIM_FILE_LEN - 1] > NAS_MML_ROUTING_UPDATE_STATUS_ROUTING_AREA_NOT_ALLOWED )
    {
        stPsLocInfo.aucPsLocInfo[NAS_MML_PS_LOCI_SIM_FILE_LEN - 1] = NAS_MML_ROUTING_UPDATE_STATUS_ROUTING_AREA_NOT_ALLOWED;
    }
    NAS_MML_SetPsUpdateStatus(stPsLocInfo.aucPsLocInfo[NAS_MML_PS_LOCI_SIM_FILE_LEN - 1]);

    return;
}
VOS_VOID NAS_MMC_WritePsLociNvim(
    VOS_UINT8                          *pstPsLocInfo,
    VOS_UINT32                          ulSize
)
{
    VOS_UINT32                          i;
    NAS_MML_SIM_MS_IDENTITY_STRU       *pstMsIdentity = VOS_NULL_PTR;

    pstMsIdentity       = NAS_MML_GetSimMsIdentity();

    /* �Ƿ�PS LOC��Ϣ�򳤶� */
    if ((VOS_NULL_PTR == pstPsLocInfo)
     || (0 ==ulSize)
     || (ulSize > NAS_MML_PS_LOCI_SIM_FILE_LEN))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_WritePsLociNvim:ERROR: Invalid PS loc info!");

        return;
    }

    if (NV_OK != NV_Write(en_NV_Item_Ps_Loci, pstPsLocInfo, ulSize))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_WritePsLociNvim:ERROR: NV_Write Error");

        return;
    }

    /* ����PTMSI��������Ч */
    for (i = 0; i < NAS_MML_MAX_PTMSI_LEN; i++)
    {
        pstMsIdentity->aucPtmsi[i]  = pstPsLocInfo[i];
    }

    /* ����PTMSI SIGNATURE��������Ч */
    for (i = 0; i < NAS_MML_MAX_PTMSI_SIGNATURE_LEN; i++)
    {
        pstMsIdentity->aucPtmsiSignature[i] = pstPsLocInfo[i + NAS_MML_PTMSI_SIGNATRUE_POS_EFPSLOCI_FILE];
    }

    /* ����RAI������ */
    NAS_MMC_UpdateRaiFormPsLociFile(pstPsLocInfo);

    /* ����GPRS��״̬ */
    NAS_MML_SetPsUpdateStatus(pstPsLocInfo[NAS_MML_PS_LOCI_SIM_FILE_LEN - 1]);

    return;
}
VOS_VOID NAS_MMC_ReadRoamCfgInfoNvim(VOS_VOID)
{
    NAS_NVIM_ROAM_CFG_INFO_STRU         stRoamFeature;
    NAS_MML_ROAM_CFG_INFO_STRU         *pstRoamCfgInfo = VOS_NULL_PTR;
    VOS_UINT32                          ulNvLenght;


    stRoamFeature.ucRoamFeatureFlg = NAS_MMC_NV_ITEM_DEACTIVE;
    stRoamFeature.ucRoamCapability = NAS_MML_ROAM_BUTT;
    ulNvLenght                     = 0;

    pstRoamCfgInfo = NAS_MML_GetRoamCfg();

    (VOS_VOID)NV_GetLength(en_NV_Item_Roam_Capa, &ulNvLenght);
    if (NV_OK != NV_Read(en_NV_Item_Roam_Capa,
                         &stRoamFeature, ulNvLenght))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC,
           "NAS_MMC_ReadRoamFeatureNvim():WARNING: en_NV_Item_Roam_Capa Error");

        return;
    }

    if ((NAS_MMC_NV_ITEM_ACTIVE == stRoamFeature.ucRoamFeatureFlg)
     && (stRoamFeature.ucRoamCapability < NAS_MML_ROAM_BUTT))
    {
        pstRoamCfgInfo->ucRoamFeatureFlg = stRoamFeature.ucRoamFeatureFlg;
        pstRoamCfgInfo->enRoamCapability = stRoamFeature.ucRoamCapability;
    }

    return;
}


VOS_VOID NAS_MMC_ReadDtSingleDomainPlmnSearchNvim(VOS_VOID)
{
    NAS_MMC_NVIM_SINGLE_DOMAIN_FAIL_CNT_STRU                stSingleDomainFailCnt;
    NAS_MML_MISCELLANEOUS_CFG_INFO_STRU                    *pstMiscellaneousCfgInfo = VOS_NULL_PTR;
    VOS_UINT32                                              ulLength;

    ulLength = 0;


    stSingleDomainFailCnt.ucSingleDomainFailPlmnSrchFlag = NAS_MMC_NV_ITEM_DEACTIVE;

    pstMiscellaneousCfgInfo = NAS_MML_GetMiscellaneousCfgInfo();

    (VOS_VOID)NV_GetLength(en_NV_Item_SINGLE_DOMAIN_FAIL_SRCH_PLMN_CNT, &ulLength);
    if (NV_OK != NV_Read(en_NV_Item_SINGLE_DOMAIN_FAIL_SRCH_PLMN_CNT,
                         &stSingleDomainFailCnt.ucSingleDomainFailPlmnSrchFlag, ulLength))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC,
           "NAS_MMC_ReadDtSingleDomainPlmnSearchNvim():WARNING: en_NV_Item_SINGLE_DOMAIN_FAIL_SRCH_PLMN_CNT Error");

        return;
    }


    if ((NAS_MMC_NV_ITEM_ACTIVE != stSingleDomainFailCnt.ucSingleDomainFailPlmnSrchFlag)
     && (NAS_MMC_NV_ITEM_DEACTIVE != stSingleDomainFailCnt.ucSingleDomainFailPlmnSrchFlag))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC,
           "NAS_MMC_ReadDtSingleDomainPlmnSearchNvim():WARNING: NV parameter Error");
        return;
    }

    pstMiscellaneousCfgInfo->ucSingleDomainFailPlmnSrchFlag
             = stSingleDomainFailCnt.ucSingleDomainFailPlmnSrchFlag;

}

VOS_VOID  NAS_MMC_ReadLastImsiNvim( VOS_VOID )
{

    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRplmnCfg;
    NAS_MMC_NVIM_LAST_IMSI_STRU         stLastImsi;
    VOS_UINT32                          ulLength;

    ulLength = 0;


    PS_MEM_SET(&stLastImsi, 0x00, sizeof(NAS_MMC_NVIM_LAST_IMSI_STRU));

    pstRplmnCfg = NAS_MML_GetRplmnCfg();

    (VOS_VOID)NV_GetLength(en_NV_Item_Last_Imsi, &ulLength);

    /* ������NVIM��,NVIM�б��ֵĵ�һλ����Чλ���ڶ�λ�Ժ����IMSI���� */
    if (NV_OK != NV_Read(en_NV_Item_Last_Imsi,
                    &stLastImsi, ulLength))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC,
            "NAS_MMC_ReadLastImsiNvim(): WARNING: en_NV_Item_Last_Imsi Error");

        return;
    }

    PS_MEM_CPY(pstRplmnCfg->aucLastImsi,stLastImsi.aucImsi,NAS_MML_MAX_IMSI_LEN);


    return;
}

VOS_VOID NAS_MMC_UpdateLastImsi( VOS_VOID )
{

    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRplmnCfgInfo = VOS_NULL_PTR;
    VOS_UINT8                           aucLastImsi[NAS_MML_MAX_IMSI_LEN];
    NAS_MMC_NVIM_LAST_IMSI_STRU         stLastImsi;
    VOS_UINT32                          ulLength;

    ulLength = 0;
    pstRplmnCfgInfo = NAS_MML_GetRplmnCfg();

    PS_MEM_SET(aucLastImsi, 0x00, NAS_MML_MAX_IMSI_LEN);
    PS_MEM_SET(&stLastImsi, 0x00, sizeof(NAS_MMC_NVIM_LAST_IMSI_STRU));

    if ( USIMM_API_SUCCESS != USIMM_GetCardIMSI(aucLastImsi) )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_UpdateLastImsi:Get Imsi Failed");
        return;
    }

    PS_MEM_CPY(pstRplmnCfgInfo->aucLastImsi, aucLastImsi, sizeof(aucLastImsi));
    PS_MEM_CPY(stLastImsi.aucImsi, aucLastImsi, sizeof(aucLastImsi));

    (VOS_VOID)NV_GetLength(en_NV_Item_Last_Imsi, &ulLength);

    /* ������NVIM��,NVIM�б��ֵĵ�һλ����Чλ���ڶ�λ�Ժ����IMSI���� */
    if (NV_OK != NV_Write (en_NV_Item_Last_Imsi,
                           &stLastImsi,
                           ulLength))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_UpdateLastImsi:Write NV Failed");
    }

}


VOS_VOID NAS_MMC_ReaducWcdmaPriorityGsmNvim(VOS_VOID)
{
    NAS_MMC_NVIM_WCDMA_PRIORITY_GSM_FLG_STRU                stWcdmaPriorityGsm;
    NAS_MML_MISCELLANEOUS_CFG_INFO_STRU                    *pstMiscellaneousCfgInfo = VOS_NULL_PTR;
    VOS_UINT32                                              ulLength;

    ulLength = 0;

    stWcdmaPriorityGsm.ucWcdmaPriorityGsmFlg = NAS_MMC_NV_ITEM_DEACTIVE;

    pstMiscellaneousCfgInfo = NAS_MML_GetMiscellaneousCfgInfo();

    /* Ĭ������Ϊ������ */
    pstMiscellaneousCfgInfo->ucWcdmaPriorityGsmFlg             = NAS_MMC_NV_ITEM_DEACTIVE;
    pstMiscellaneousCfgInfo->ucSortAvailalePlmnListRatPrioFlg  = NAS_MMC_NV_ITEM_DEACTIVE;

    (VOS_VOID)NV_GetLength(en_NV_Item_NVIM_WCDMA_PRIORITY_GSM_SUPPORT_FLG, &ulLength);
    if (NV_OK != NV_Read(en_NV_Item_NVIM_WCDMA_PRIORITY_GSM_SUPPORT_FLG,
                         &stWcdmaPriorityGsm, ulLength))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC,
           "NAS_MMC_ReadDtSingleDomainPlmnSearchNvim():WARNING: en_NV_Item_NVIM_WCDMA_PRIORITY_GSM_SUPPORT_FLG Error");

        return;
    }

    if (NAS_MMC_NV_ITEM_ACTIVE == stWcdmaPriorityGsm.ucWcdmaPriorityGsmFlg)
    {
        pstMiscellaneousCfgInfo->ucWcdmaPriorityGsmFlg = stWcdmaPriorityGsm.ucWcdmaPriorityGsmFlg;
    }

    if (NAS_MMC_NV_ITEM_ACTIVE == stWcdmaPriorityGsm.ucSortAvailalePlmnListRatPrioFlg)
    {
        pstMiscellaneousCfgInfo->ucSortAvailalePlmnListRatPrioFlg = stWcdmaPriorityGsm.ucSortAvailalePlmnListRatPrioFlg;
    }

    return;
}
VOS_VOID NAS_MMC_ReadPsOnlyCsServiceSupportNvim(VOS_VOID)
{
    NAS_NVIM_PS_ONLY_CS_SERVICE_SUPPORT_FLG_STRU            stPsOnlyCsServiceSupportFlg;
    NAS_MML_MISCELLANEOUS_CFG_INFO_STRU                    *pstMiscellaneousCfgInfo = VOS_NULL_PTR;
    VOS_UINT32                                              ulLength;

    ulLength = 0;


    stPsOnlyCsServiceSupportFlg.ucPsOnlyCsServiceSupportFlg = NAS_MMC_NV_ITEM_DEACTIVE;

    pstMiscellaneousCfgInfo = NAS_MML_GetMiscellaneousCfgInfo();

    (VOS_VOID)NV_GetLength(en_NV_Item_NVIM_PS_ONLY_CS_SERVICE_SUPPORT_FLG, &ulLength);
    if (ulLength > sizeof(stPsOnlyCsServiceSupportFlg))
    {
        return;
    }

    if (NV_OK != NV_Read(en_NV_Item_NVIM_PS_ONLY_CS_SERVICE_SUPPORT_FLG,
                         &stPsOnlyCsServiceSupportFlg, ulLength))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC,
           "NAS_MMC_ReadDtSingleDomainPlmnSearchNvim():WARNING: en_NV_Item_SINGLE_DOMAIN_FAIL_SRCH_PLMN_CNT Error");

        return;
    }


    if ((NAS_MMC_NV_ITEM_ACTIVE != stPsOnlyCsServiceSupportFlg.ucPsOnlyCsServiceSupportFlg)
     && (NAS_MMC_NV_ITEM_DEACTIVE != stPsOnlyCsServiceSupportFlg.ucPsOnlyCsServiceSupportFlg))
    {
        pstMiscellaneousCfgInfo->ucPsOnlyCsServiceSupportFlg = NAS_MMC_NV_ITEM_DEACTIVE;
        NAS_WARNING_LOG(WUEPS_PID_MMC,
           "NAS_MMC_ReaducWcdmaPriorityGsmNvim():WARNING: NV parameter Error");
        return;
    }

    pstMiscellaneousCfgInfo->ucPsOnlyCsServiceSupportFlg
             = stPsOnlyCsServiceSupportFlg.ucPsOnlyCsServiceSupportFlg;

}


VOS_VOID NAS_MMC_ReadAPPConfigSupportNvim(VOS_VOID)
{
    NAS_MML_MISCELLANEOUS_CFG_INFO_STRU                    *pstMiscellaneousCfgInfo = VOS_NULL_PTR;
    NAS_NVIM_SYSTEM_APP_CONFIG_STRU                     stSysAppConfig;
    VOS_UINT32                                              ulLength;

    ulLength = 0;
    stSysAppConfig.usSysAppConfigType = SYSTEM_APP_BUTT;

    pstMiscellaneousCfgInfo = NAS_MML_GetMiscellaneousCfgInfo();

    (VOS_VOID)NV_GetLength(en_NV_Item_System_APP_Config, &ulLength);
    if (ulLength > sizeof(stSysAppConfig))
    {
        return;
    }
    if (NV_OK != NV_Read(en_NV_Item_System_APP_Config,
                         &stSysAppConfig, ulLength))
    {
        pstMiscellaneousCfgInfo->usAppConfigSupportFlg  = SYSTEM_APP_MP;
        NAS_WARNING_LOG(WUEPS_PID_MMC,
           "NAS_MMC_ReadAPPConfigSupportNvim():WARNING: read en_NV_Item_System_APP_Config Error");

        return;
    }


    if ( SYSTEM_APP_ANDROID < stSysAppConfig.usSysAppConfigType )
    {
        pstMiscellaneousCfgInfo->usAppConfigSupportFlg  = SYSTEM_APP_MP;
        NAS_WARNING_LOG(WUEPS_PID_MMC,
           "NAS_MMC_ReadAPPConfigSupportNvim():WARNING: en_NV_Item_System_APP_Config error");

    }
    else
    {
        pstMiscellaneousCfgInfo->usAppConfigSupportFlg = stSysAppConfig.usSysAppConfigType ;
    }
    return;
}



VOS_VOID NAS_MMC_ReadAisRoamingNvim( VOS_VOID  )
{
    NAS_MMC_NVIM_AIS_ROAMING_CFG_STRU   stNvimAisRoamingCfg;
    NAS_MML_AIS_ROAMING_CFG_STRU       *pstAisRoamingCfg;


    PS_MEM_SET(&stNvimAisRoamingCfg, 0x00, sizeof(stNvimAisRoamingCfg));

    pstAisRoamingCfg = NAS_MML_GetAisRoamingCfg();

    if (NV_OK != NV_Read(en_NV_Item_NVIM_AIS_ROAMING_CFG,
                         &stNvimAisRoamingCfg, sizeof(stNvimAisRoamingCfg)))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC,
           "NAS_MMC_ReadAisRoamingNvim():WARNING: read en_NV_Item_NVIM_AIS_ROAMING_CFG Error");

        return;
    }

    pstAisRoamingCfg->ucEnableFlg            = stNvimAisRoamingCfg.ucEnableFlg;
    pstAisRoamingCfg->enHighPrioRatType      = stNvimAisRoamingCfg.ucHighPrioRatType;
    pstAisRoamingCfg->stHighPrioPlmnId.ulMcc = stNvimAisRoamingCfg.stHighPrioPlmnId.ulMcc;
    pstAisRoamingCfg->stHighPrioPlmnId.ulMnc = stNvimAisRoamingCfg.stHighPrioPlmnId.ulMnc;
    pstAisRoamingCfg->stSimHPlmnId.ulMcc     = stNvimAisRoamingCfg.stSimHPlmnId.ulMcc;
    pstAisRoamingCfg->stSimHPlmnId.ulMnc     = stNvimAisRoamingCfg.stSimHPlmnId.ulMnc;
}


VOS_VOID NAS_MMC_ReadUserAutoReselCfgNvim(VOS_VOID)
{
    NAS_MMC_NVIM_USER_AUTO_RESEL_CFG_STRU    stUserAutoReselCfg;
    VOS_UINT32                               ulLength;

    ulLength = 0;


    PS_MEM_SET(&stUserAutoReselCfg, 0x00, sizeof(NAS_MMC_NVIM_USER_AUTO_RESEL_CFG_STRU));

    (VOS_VOID)NV_GetLength(en_NV_Item_User_Auto_Resel_Switch, &ulLength);


    if (NV_OK != NV_Read(en_NV_Item_User_Auto_Resel_Switch,
                         &stUserAutoReselCfg, ulLength))
    {
        stUserAutoReselCfg.ucAutoReselActiveFlg  = VOS_FALSE;
        NAS_WARNING_LOG(WUEPS_PID_MMC,
           "NAS_MMC_ReadUserAutoReselCfgNvim():WARNING: read en_NV_Item_User_Auto_Resel_Switch Error");

    }

    if (stUserAutoReselCfg.ucAutoReselActiveFlg == VOS_TRUE)
    {
        NAS_MML_SetUserAutoReselActiveFlg(VOS_TRUE);
    }
    else
    {
        NAS_MML_SetUserAutoReselActiveFlg(VOS_FALSE);
    }

    return;

}


VOS_VOID NAS_MMC_ReadScanCtrlNvim(VOS_VOID)
{
    NVIM_SCAN_CTRL_STRU                 stNvScanCtrl;
    VOS_UINT32                          ulLength;

    ulLength = 0;


    (VOS_VOID)NV_GetLength(en_NV_Item_Scan_Ctrl_Para, &ulLength);
    if (ulLength > sizeof(stNvScanCtrl))
    {
        return;
    }

    PS_MEM_SET(&stNvScanCtrl, 0x00, sizeof(NVIM_SCAN_CTRL_STRU));

    /* ��NV��en_NV_Item_Scan_Ctrl_Para��ʧ�ܣ�ֱ�ӷ��� */
    if (NV_OK != NV_Read(en_NV_Item_Scan_Ctrl_Para,
                         &stNvScanCtrl, ulLength))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC,
           "NAS_MMC_ReadScanCtrlNvim():WARNING: read en_NV_Item_Scan_Ctrl_Para Error");

        return;
    }

    /* δ���ֱ�ӷ��� */
    if (NAS_MMC_NV_ITEM_ACTIVE != stNvScanCtrl.ucNvimActiveFlg)
    {
        return;
    }

    /* ���������Ѽ�������������Ʊ�ʶΪVOS_TRUE */
    NAS_MML_SetScanCtrlEnableFlg(VOS_TRUE);

    return;
}



VOS_VOID NAS_MMC_ReadHPlmnSearchRegardLessMccNvim(VOS_VOID)
{
    NAS_MMC_NVIM_HPLMN_SEARCH_REGARDLESS_MCC_SUPPORT_STRU   stHplmnSearchRegardlessMcc;


    PS_MEM_SET(&stHplmnSearchRegardlessMcc, 0x00, sizeof(stHplmnSearchRegardlessMcc));

    /* ��ȡNV */
    if (NV_OK != NV_Read(en_NV_Item_HPLMN_SEARCH_REGARDLESS_MCC_SUPPORT,
                         &stHplmnSearchRegardlessMcc, sizeof(NAS_MMC_NVIM_HPLMN_SEARCH_REGARDLESS_MCC_SUPPORT_STRU)))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC,
                      "NAS_MMC_ReadHPlmnSearchRegardLessMccNvim(): en_NV_Item_HPLMN_SEARCH_REGARDLESS_MCC_SUPPORT Error");
        return;
    }

    /*  ��Ч�Լ�� */
    if (NAS_MMC_NV_ITEM_ACTIVE != stHplmnSearchRegardlessMcc.ucNvimActiveFlg)
    {
        return;
    }

    if (stHplmnSearchRegardlessMcc.ucCustomMccNum > NAS_MML_BG_SEARCH_REGARDLESS_MCC_NUMBER)
    {
        return;
    }

    /* ��ֵ��ȫ�ֱ��� */
    NAS_MML_SetBgSearchRegardlessMccList(stHplmnSearchRegardlessMcc.aulCustommMccList, stHplmnSearchRegardlessMcc.ucCustomMccNum);

    return;
}
VOS_UINT32 NAS_MMC_ConvertNivmActionToMmlType(
    NAS_MMC_NVIM_SINGLE_DOMAIN_REG_FAIL_ACTION_ENUM_UINT8   enNvAction,
    NAS_MML_SINGLE_DOMAIN_REG_FAIL_ACTION_ENUM_UINT8       *penMmlAction
)
{
    switch(enNvAction)
    {
        case NAS_MMC_NVIM_SINGLE_DOMAIN_REG_FAIL_ACTION_PLMN_SELECTION:
            *penMmlAction = NAS_MML_SINGLE_DOMAIN_REG_FAIL_ACTION_PLMN_SELECTION;
            break;

        case NAS_MMC_NVIM_SINGLE_DOMAIN_REG_FAIL_ACTION_NORMAL_CAMP_ON:
            *penMmlAction = NAS_MML_SINGLE_DOMAIN_REG_FAIL_ACTION_NORMAL_CAMP_ON;
            break;

        case NAS_MMC_NVIM_SINGLE_DOMAIN_REG_FAIL_ACTION_OPTIONAL_PLMN_SELECTION:
            *penMmlAction = NAS_MML_SINGLE_DOMAIN_REG_FAIL_ACTION_OPTIONAL_PLMN_SELECTION;
            break;

        case NAS_MMC_NVIM_SINGLE_DOMAIN_REG_FAIL_ACTION_LIMITED_CAMP_ON:
            *penMmlAction = NAS_MML_SINGLE_DOMAIN_REG_FAIL_ACTION_LIMITED_CAMP_ON;
            break;

        case NAS_MMC_NVIM_SINGLE_DOMAIN_ROAMING_REG_FAIL_ACTION_PLMN_SELECTION:
            *penMmlAction = NAS_MML_SINGLE_DOMAIN_ROAMING_REG_FAIL_ACTION_PLMN_SELECTION;
            break;

        default:
            *penMmlAction = NAS_MML_SINGLE_DOMAIN_REG_FAIL_ACTION_BUTT;
            return VOS_FALSE;
    }

    return VOS_TRUE;
}


VOS_VOID NAS_MMC_ReadPrioHplmnActCfgNvim(VOS_VOID)
{
    NAS_MMC_NVIM_PRIO_HPLMNACT_CFG_STRU    stHplmnActCfg;
    NAS_MML_PRIO_HPLMNACT_CFG_STRU        *pstPrioHplmnActCfg = VOS_NULL_PTR;


    PS_MEM_SET(&stHplmnActCfg, 0x00, sizeof(stHplmnActCfg));

    pstPrioHplmnActCfg = NAS_MML_GetPrioHplmnActCfg();

    if (NV_OK != NV_Read(en_NV_Item_PRIO_HPLMNACT_CFG,
                        &stHplmnActCfg, sizeof(NAS_MMC_NVIM_PRIO_HPLMNACT_CFG_STRU)))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC,
           "NAS_MMC_ReadPrioHplmnActCfgNvim(): read en_NV_Item_PRIO_HPLMNACT_CFG fail");

        return;
    }

    /* ��ȡ�ö����Ƿ񼤻� */
    if (NAS_MMC_NV_ITEM_ACTIVE == stHplmnActCfg.ucStatus)
    {
        pstPrioHplmnActCfg->ucActiveFlg = VOS_TRUE;
    }
    else
    {
        pstPrioHplmnActCfg->ucActiveFlg = VOS_FALSE;
    }

    /* ��ȡ���Ƶ����ȵ�HPLMNAct,ֻ���ǲ�Ʒ֧�ֵĽ��뼼�� */
#if (FEATURE_ON == FEATURE_LTE)

    pstPrioHplmnActCfg->usPrioHplmnAct = (stHplmnActCfg.usPrioHplmnAct & NAS_MML_SIM_UE_SUPPORT_RAT_SUPPORT_LTE);

#else
    pstPrioHplmnActCfg->usPrioHplmnAct = (stHplmnActCfg.usPrioHplmnAct & NAS_MML_SIM_UE_SUPPORT_RAT);

#endif

    return;
}


VOS_UINT32 NAS_MMC_ConvertNivmRegCauseToMmlType(
    NAS_MMC_NVIM_REG_FAIL_CAUSE_ENUM_UINT16                 enNvCause,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                     *penMmlCause
)
{
    switch (enNvCause)
    {
        case NAS_MMC_NVIM_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN:
            *penMmlCause = NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN;
            break;

        case NAS_MMC_NVIM_REG_FAIL_CAUSE_TIMER_TIMEOUT:
            *penMmlCause = NAS_MML_REG_FAIL_CAUSE_TIMER_TIMEOUT;
            break;

        default:
            *penMmlCause = NAS_MML_REG_FAIL_CAUSE_BUTT;
            return VOS_FALSE;
    }

    return VOS_TRUE;
}



VOS_VOID NAS_MMC_ReadSingleDomainFailActionListNvim(VOS_VOID)
{
    NAS_MMC_NVIM_SINGLE_DOMAIN_FAIL_ACTION_LIST_STRU    stSingleDomainFailAction;
    NAS_MML_SINGLE_DOMAIN_FAIL_ACTION_LIST_CTX_STRU    *pstSingleDomainFailActionCtx = VOS_NULL_PTR;
    VOS_UINT32                                          i;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                  enRegCause;
    NAS_MML_SINGLE_DOMAIN_REG_FAIL_ACTION_ENUM_UINT8    enAction;


    PS_MEM_SET(&stSingleDomainFailAction, 0x00, sizeof(stSingleDomainFailAction));

    /* ��ȡNV */
    if (NV_OK != NV_Read(en_NV_Item_SINGLE_DOMAIN_FAIL_ACTION_LIST,
                         &stSingleDomainFailAction, sizeof(NAS_MMC_NVIM_SINGLE_DOMAIN_FAIL_ACTION_LIST_STRU)))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadSingleDomainFailActionListNvim(): en_NV_Item_SINGLE_DOMAIN_FAIL_ACTION_LIST Error");
        return;
    }

    /* ��Ч�Լ�� */
    if (NAS_MMC_NV_ITEM_ACTIVE != stSingleDomainFailAction.ucActiveFlag)
    {
        return;
    }

    /* �����Ƿ� */
    if (stSingleDomainFailAction.ucCount > NAS_MML_SINGLE_DOMAIN_FAIL_ACTION_MAX_LIST)
    {
        return;
    }

    pstSingleDomainFailActionCtx = NAS_MML_GetSingleDomainFailActionCtx();

    pstSingleDomainFailActionCtx->ucActiveFlag = VOS_TRUE;

    /* ��NV���ֵ���浽ȫ�ֱ�������Ҫ��NV�ж��Ƶ�ACTIONֵת��ΪMMC�����ACTIONֵ */
    for (i = 0; i < stSingleDomainFailAction.ucCount; i++)
    {
        if (NAS_MMC_NVIM_REG_DOMAIN_CS == stSingleDomainFailAction.astSingleDomainFailActionList[i].enDomain)
        {
            pstSingleDomainFailActionCtx->astSingleDomainFailActionList[pstSingleDomainFailActionCtx->ucCount].enDomain
                = NAS_MML_REG_DOMAIN_CS;
        }
        else if (NAS_MMC_NVIM_REG_DOMAIN_PS == stSingleDomainFailAction.astSingleDomainFailActionList[i].enDomain)
        {
            pstSingleDomainFailActionCtx->astSingleDomainFailActionList[pstSingleDomainFailActionCtx->ucCount].enDomain
                = NAS_MML_REG_DOMAIN_PS;
        }
        else
        {
            continue;
        }

        if (VOS_FALSE == NAS_MMC_ConvertNivmRegCauseToMmlType(stSingleDomainFailAction.astSingleDomainFailActionList[i].enRegCause, &enRegCause))
        {
            continue;
        }

        if (VOS_FALSE == NAS_MMC_ConvertNivmActionToMmlType(stSingleDomainFailAction.astSingleDomainFailActionList[i].enAction, &enAction))
        {
            continue;
        }


        pstSingleDomainFailActionCtx->astSingleDomainFailActionList[pstSingleDomainFailActionCtx->ucCount].enRegCause
            = enRegCause;

        pstSingleDomainFailActionCtx->astSingleDomainFailActionList[pstSingleDomainFailActionCtx->ucCount].enAction
            = enAction;

        pstSingleDomainFailActionCtx->ucCount++;
    }

    return;
}


VOS_VOID NAS_MMC_ReadRegFailNetWorkFailureCustomFlagNvim(VOS_VOID)
{
    NAS_MMC_NVIM_REG_FAIL_NETWORK_FAILURE_CUSTOM_FLG_STRU   stCsRegFailNetFailureCustom;
    VOS_UINT32                                              ulLength;


    PS_MEM_SET(&stCsRegFailNetFailureCustom, 0x00, sizeof(NAS_MMC_NVIM_REG_FAIL_NETWORK_FAILURE_CUSTOM_FLG_STRU));

    ulLength = 0;

    /* �Ȼ�ȡNV�ĳ��� */
    (VOS_VOID)NV_GetLength(en_NV_Item_CS_FAIL_NETWORK_FAILURE_PLMN_SEARCH_FLAG, &ulLength);

    if (ulLength > sizeof(NAS_MMC_NVIM_REG_FAIL_NETWORK_FAILURE_CUSTOM_FLG_STRU))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadRegFailNetWorkFailureCustomFlagNvim():WARNING: en_NV_Item_CS_FAIL_NETWORK_FAILURE_PLMN_SEARCH_FLAG length Error");
        return;
    }

    /* ��ȡNV */
    if (NV_OK != NV_Read(en_NV_Item_CS_FAIL_NETWORK_FAILURE_PLMN_SEARCH_FLAG,
                         &stCsRegFailNetFailureCustom, ulLength))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadRegFailNetWorkFailureCustomFlagNvim(): en_NV_Item_CS_FAIL_NETWORK_FAILURE_PLMN_SEARCH_FLAG Error");
        return;
    }

    /* NV��Ч�Լ�� */
    if (NAS_MMC_NV_ITEM_ACTIVE != stCsRegFailNetFailureCustom.ucNvimActiveFlg)
    {
        return;
    }

    /* ��ֵ��ȫ�ֱ��� */
    NAS_MML_SetRegFailNetWorkFailureCustomFlag(VOS_TRUE);

    return;
}


VOS_VOID NAS_MMC_ReadPlmnExactlyCompareNvim(VOS_VOID)
{
    NAS_MMC_NVIM_PLMN_EXACTLY_COMPARE_FLAG_STRU             stPlmnExactlyCompara;
    VOS_UINT32                                              ulLength;


    PS_MEM_SET(&stPlmnExactlyCompara, 0x00, sizeof(NAS_MMC_NVIM_PLMN_EXACTLY_COMPARE_FLAG_STRU));

    ulLength = 0;

    /* �Ȼ�ȡNV�ĳ��� */
    (VOS_VOID)NV_GetLength(en_NV_Item_PLMN_EXACTLY_COMPARE_FLG, &ulLength);

    if (ulLength > sizeof(NAS_MMC_NVIM_PLMN_EXACTLY_COMPARE_FLAG_STRU))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadPlmnExactlyCompareNvim():WARNING: en_NV_Item_PLMN_EXACTLY_COMPARE_FLG length Error");
        return;
    }

    /* ��ȡNV */
    if (NV_OK != NV_Read (en_NV_Item_PLMN_EXACTLY_COMPARE_FLG, &stPlmnExactlyCompara, ulLength))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadPlmnExactlyCompareNvim(): en_NV_Item_PLMN_EXACTLY_COMPARE_FLG Error");
        return;
    }

    /* NV��Ч�Լ�� */
    if (VOS_TRUE == stPlmnExactlyCompara.ucPlmnExactlyCompareFlag)
    {
        /* ��ֵ��ȫ�ֱ��� */
        NAS_MML_SetPlmnExactlyComparaFlg(stPlmnExactlyCompara.ucPlmnExactlyCompareFlag);
    }

    return;
}

VOS_VOID NAS_MMC_ReadCustomizeServiceNvim(VOS_VOID)
{
    NAS_NVIM_CUSTOMIZE_SERVICE_STRU                         stCustomServ;
    VOS_UINT32                                              ulLength;


    ulLength = 0;

    PS_MEM_SET(&stCustomServ, (VOS_CHAR)0x0, sizeof(NAS_NVIM_CUSTOMIZE_SERVICE_STRU));

    /* �Ȼ�ȡNV�ĳ��� */
    (VOS_VOID)NV_GetLength(en_NV_Item_CustomizeService, &ulLength);

    if (ulLength > sizeof(NAS_NVIM_CUSTOMIZE_SERVICE_STRU))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadCustomizeServiceNvim():WARNING: en_NV_Item_CustomizeService length Error");
        return;
    }

    /* ��ȡen_NV_Item_CustomizeService NV */
    if (NV_OK != NV_Read (en_NV_Item_CustomizeService, &stCustomServ, ulLength))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadCustomizeServiceNvim(): en_NV_Item_CustomizeService Error");
        return;
    }

    if (NAS_MMC_NV_ITEM_DEACTIVE == stCustomServ.ulStatus)
    {
        NAS_MML_SetSupportCsServiceFLg(VOS_FALSE);
    }

    if ((NAS_MMC_NV_ITEM_ACTIVE == stCustomServ.ulStatus)
     && (VOS_FALSE == stCustomServ.ulCustomizeService))
    {
        NAS_MML_SetSupportCsServiceFLg(VOS_FALSE);
    }

    return;

}




VOS_VOID NAS_MMC_ReadHplmnRegisterCtrlNvim(VOS_VOID)
{
    NAS_MMC_NVIM_HPLMN_REGISTER_CTRL_FLAG_STRU              stHplmnRegisterCtrlFlg;
    VOS_UINT32                                              ulLength;


    PS_MEM_SET(&stHplmnRegisterCtrlFlg, 0x00, sizeof(NAS_MMC_NVIM_HPLMN_REGISTER_CTRL_FLAG_STRU));

    ulLength = 0;

    /* �Ȼ�ȡNV�ĳ��� */
    (VOS_VOID)NV_GetLength(en_NV_Item_Hplmn_Register_Ctrl_Flg, &ulLength);

    if (ulLength > sizeof(stHplmnRegisterCtrlFlg))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadHplmnRegisterCtrlNvim():WARNING: en_NV_Item_Hplmn_Register_Ctrl_Flg length Error");
        return;
    }

    /* ��ȡNV */
    if (NV_OK != NV_Read (en_NV_Item_Hplmn_Register_Ctrl_Flg, &stHplmnRegisterCtrlFlg, ulLength))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadHplmnRegisterCtrlNvim(): en_NV_Item_Hplmn_Register_Ctrl_Flg Error");
        return;
    }

    /* NV��Ч�Լ�� */
    if (VOS_TRUE == stHplmnRegisterCtrlFlg.ucHplmnRegisterCtrlFlg)
    {
        /* ��ֵ��ȫ�ֱ��� */
        NAS_MML_SetHplmnRegisterCtrlFlg(stHplmnRegisterCtrlFlg.ucHplmnRegisterCtrlFlg);
    }

    return;
}


VOS_VOID NAS_MMC_ReadH3gCtrlNvim(VOS_VOID)
{
    NAS_MMC_NVIM_H3G_CTRL_FLAG_STRU     stH3gCtrlFlg;
    VOS_UINT32                          ulLength;

    PS_MEM_SET(&stH3gCtrlFlg, 0x00, sizeof(NAS_MMC_NVIM_H3G_CTRL_FLAG_STRU));

    ulLength = 0;

    /* �Ȼ�ȡNV�ĳ��� */
    (VOS_VOID)NV_GetLength(en_NV_Item_H3g_Customization, &ulLength);

    if (ulLength > sizeof(stH3gCtrlFlg))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadH3gCtrlNvim():WARNING: en_NV_Item_H3g_Customization length Error");
        return;
    }

    /* ��ȡNV */
    if (NV_OK != NV_Read (en_NV_Item_H3g_Customization, &stH3gCtrlFlg, ulLength))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadH3gCtrlNvim(): en_NV_Item_H3g_Customization Error");
        return;
    }

    /* ��ֵ��ȫ�ֱ��� */
    NAS_MML_SetH3gCtrlFlg(stH3gCtrlFlg.ucH3gCtrlFlg);

    return;
}

VOS_VOID NAS_MMC_ReadCellSignReportCfgNvim( VOS_VOID )
{

    NAS_MMC_MAINTAIN_CTX_STRU                              *pstMaintainInfo = VOS_NULL_PTR;
    NAS_NVIM_CELL_SIGN_REPORT_CFG_STRU                      stCellSignReportCfg;
    VOS_UINT32                                              ulLength;

    pstMaintainInfo = NAS_MMC_GetMaintainInfo();
    PS_MEM_SET(&stCellSignReportCfg, (VOS_CHAR)0x0, sizeof(stCellSignReportCfg));


    ulLength = 0;

    /* �Ȼ�ȡNV�ĳ��� */
    (VOS_VOID)NV_GetLength(en_NV_Item_CELL_SIGN_REPORT_CFG, &ulLength);

    if (ulLength > sizeof(NAS_NVIM_CELL_SIGN_REPORT_CFG_STRU))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadCellSignReportCfgNvim():WARNING: en_NV_Item_CELL_SIGN_REPORT_CFG length Error");
        return;
    }

    if(NV_OK != NV_Read(en_NV_Item_CELL_SIGN_REPORT_CFG,
                        &stCellSignReportCfg,
                        ulLength))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadCellSignReportCfgNvim:read en_NV_Item_CELL_SIGN_REPORT_CFG failed");
        return;
    }

    /* ��ȡnv�����źŸı��������ã�����ʱ��֪ͨ����� */
    pstMaintainInfo->ucSignThreshold = stCellSignReportCfg.ucSignThreshold;

    if (stCellSignReportCfg.ucSignThreshold > NAS_MMC_MAX_SIGN_THRESHOLD)
    {
        pstMaintainInfo->ucSignThreshold = 0;
    }

    /* ��ȡnv�����źŸı���ʱ�䣬����ʱ��֪ͨ����� */
    pstMaintainInfo->ucMinRptTimerInterval = stCellSignReportCfg.ucMinRptTimerInterval;

    if (stCellSignReportCfg.ucMinRptTimerInterval > NAS_MMC_MAX_SIGN_TIMERINTERVAL)
    {
        pstMaintainInfo->ucMinRptTimerInterval = 0;
    }

    return;
}
VOS_VOID NAS_MMC_WriteCellSignReportCfgNvim(VOS_UINT8 ucSignThreshold,VOS_UINT8 ucMinRptTimerInterval)
{
    NAS_NVIM_CELL_SIGN_REPORT_CFG_STRU  stCellSignReportCfg;
    VOS_UINT32                          ulLength;

    PS_MEM_SET(&stCellSignReportCfg, 0x0, sizeof(stCellSignReportCfg));
    ulLength = 0;

    stCellSignReportCfg.ucSignThreshold       = ucSignThreshold;
    stCellSignReportCfg.ucMinRptTimerInterval = ucMinRptTimerInterval;

    (VOS_VOID)NV_GetLength(en_NV_Item_CELL_SIGN_REPORT_CFG, &ulLength);
    if (NV_OK != NV_Write(en_NV_Item_CELL_SIGN_REPORT_CFG,
                          &stCellSignReportCfg,
                          ulLength))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_WriteCellSignReportCfgNvim():en_NV_Item_CELL_SIGN_REPORT_CFG Error");
    }

    return;
}


VOS_VOID NAS_MMC_ReadPlatformRatCapNvim( VOS_VOID )
{
    NAS_MML_PLATFORM_RAT_CAP_STRU              *pstPlatformRatCap = VOS_NULL_PTR;
    PLATAFORM_RAT_CAPABILITY_STRU               stNvPlatformRatCap;
    NAS_MML_PLATFORM_RAT_TYPE_ENUM_UINT8        enNasPlatformRatCap;
    VOS_UINT32                                  ulLength;
    VOS_UINT8                                   ucIndex;
    VOS_UINT32                                  i;

    ulLength = 0;
    pstPlatformRatCap = NAS_MML_GetPlatformRatCap();
    PS_MEM_SET(&stNvPlatformRatCap, (VOS_CHAR)0x0, sizeof(stNvPlatformRatCap));

    /* ��ʼ��ΪGSM ONLY */
    pstPlatformRatCap->ucRatNum      = NAS_MML_MIN_PLATFORM_RAT_NUM;
    pstPlatformRatCap->aenRatPrio[0] = NAS_MML_PLATFORM_RAT_TYPE_GSM;

    /* �Ȼ�ȡNV�ĳ��� */
    ulLength = 0;
    (VOS_VOID)NV_GetLength(en_NV_Item_Platform_RAT_CAP, &ulLength);

    if (ulLength > sizeof(PLATAFORM_RAT_CAPABILITY_STRU))
    {
        NAS_MMC_SndOmPlatformRatCap();

        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadPlatformRatCapNvim():WARNING: en_NV_Item_PLATFORM_RAT_CAP length Error");

        NAS_TRACE_HIGH("en_NV_Item_PLATFORM_RAT_CAP length Error, ulLength = %d", ulLength);
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_READ_PLATFORM_RAT_CAP_NVIM_FAILURE);

        return;
    }

    /* ��NV��en_NV_Item_PLATFORM_RAT_CAP��ʧ�ܣ�ֱ�ӷ��� */
    if (NV_OK != NV_Read(en_NV_Item_Platform_RAT_CAP,
                         &stNvPlatformRatCap, sizeof(PLATAFORM_RAT_CAPABILITY_STRU)))
    {
        NAS_MMC_SndOmPlatformRatCap();

        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadPlatformRatCapNvim():WARNING: read en_NV_Item_PLATFORM_RAT_CAP Error");

        NAS_TRACE_HIGH("read en_NV_Item_PLATFORM_RAT_CAP Error");
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_READ_PLATFORM_RAT_CAP_NVIM_FAILURE);

        return;
    }

    /* ��Ч�Լ�飺��Ч��ֱ�ӷ��� */
    if (VOS_FALSE == NAS_MMC_IsPlatformRatCapNvimValid(&stNvPlatformRatCap))
    {
        NAS_MMC_SndOmPlatformRatCap();

        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadPlatformRatCapNvim():WARNING: en_NV_Item_PLATFORM_RAT_CAP Invalid");

        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_READ_PLATFORM_RAT_CAP_NVIM_FAILURE);

        return;
    }

    /* ��ֵ��ȫ�ֱ��� */
    ucIndex = 0;
    for (i = 0; i < stNvPlatformRatCap.usRatNum; i++)
    {
        if (VOS_TRUE == NAS_MMC_ConvertNvimTypePlatformRatCapToNasType((stNvPlatformRatCap.aenRatList[i]),
                                                                        &enNasPlatformRatCap))
        {
            pstPlatformRatCap->aenRatPrio[ucIndex] = enNasPlatformRatCap;
            ucIndex++;
        }
    }

    if (ucIndex > 0)
    {
        pstPlatformRatCap->ucRatNum = ucIndex;
    }

    /* ��ά�ɲ⣬��ӡLOG */
    NAS_MMC_SndOmPlatformRatCap();

    NAS_TRACE_HIGH("read en_NV_Item_PLATFORM_RAT_CAP correct, RatNum = %d, aenRatList[0]= %d, aenRatList[1]= %d, aenRatList[2]= %d, aenRatList[3]= %d, aenRatList[4]= %d,aenRatList[5]= %d, aenRatList[6]= %d",
                    stNvPlatformRatCap.usRatNum, stNvPlatformRatCap.aenRatList[0], stNvPlatformRatCap.aenRatList[1], stNvPlatformRatCap.aenRatList[2], stNvPlatformRatCap.aenRatList[3], stNvPlatformRatCap.aenRatList[4], stNvPlatformRatCap.aenRatList[5], stNvPlatformRatCap.aenRatList[6]);

    return;

}


VOS_UINT32 NAS_MMC_IsPlatformRatCapNvimValid(
    PLATAFORM_RAT_CAPABILITY_STRU              *pstNvPlatformRatCap
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          j;

    /* ���ƽ̨֧�ֵĽ��뼼������Ϊ0��������Ч */
    if ((0 == pstNvPlatformRatCap->usRatNum)
      ||( pstNvPlatformRatCap->usRatNum > PLATFORM_MAX_RAT_NUM))
    {
        NAS_TRACE_HIGH("en_NV_Item_PLATFORM_RAT_CAP RatNum Invalid, RatNum = %d", pstNvPlatformRatCap->usRatNum);

        return VOS_FALSE;
    }

    for (i = 0; i < pstNvPlatformRatCap->usRatNum; i++)
    {
        /* ���ƽ̨֧�ֵĽ��뼼�����ظ���������Ч  */
        for (j = i + 1 ; j < pstNvPlatformRatCap->usRatNum; j++ )
        {
            if (pstNvPlatformRatCap->aenRatList[i] == pstNvPlatformRatCap->aenRatList[j])
            {
                NAS_TRACE_HIGH("en_NV_Item_PLATFORM_RAT_CAP Rat duplicate, RatNum = %d, aenRatList[%d] = aenRatList[%d] = %d", pstNvPlatformRatCap->usRatNum, i, j, pstNvPlatformRatCap->aenRatList[i]);

                return VOS_FALSE;
            }
        }

        /* ���ƽ̨֧�ֵĽ��뼼����Ч��������Ч */
        if (PLATFORM_RAT_BUTT <= pstNvPlatformRatCap->aenRatList[i])
        {
            NAS_TRACE_HIGH("en_NV_Item_PLATFORM_RAT_CAP Rat invalid, aenRatList[%d] = %d", i, pstNvPlatformRatCap->aenRatList[i]);

            return VOS_FALSE;
        }
    }

    return VOS_TRUE;

}
VOS_UINT32 NAS_MMC_ConvertNvimTypePlatformRatCapToNasType(
    PLATFORM_RAT_TYPE_ENUM_UINT16                       enNvPlatformRatCap,
    NAS_MML_PLATFORM_RAT_TYPE_ENUM_UINT8               *penNasPlatformRatCap
)
{
    VOS_UINT32                          ulRslt;
    ulRslt  = VOS_FALSE;

    switch (enNvPlatformRatCap)
    {
        case PLATFORM_RAT_GSM:
            *penNasPlatformRatCap = NAS_MML_PLATFORM_RAT_TYPE_GSM;
            ulRslt                = VOS_TRUE;
            break;

        case PLATFORM_RAT_WCDMA:
            *penNasPlatformRatCap = NAS_MML_PLATFORM_RAT_TYPE_WCDMA;
            ulRslt                = VOS_TRUE;
            break;

#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
        case PLATFORM_RAT_TDS:
            *penNasPlatformRatCap = NAS_MML_PLATFORM_RAT_TYPE_TD_SCDMA;
            ulRslt                = VOS_TRUE;
            break;
#endif

#if   (FEATURE_ON == FEATURE_LTE)
        case PLATFORM_RAT_LTE:
            *penNasPlatformRatCap = NAS_MML_PLATFORM_RAT_TYPE_LTE;
            ulRslt                = VOS_TRUE;
            break;
#endif
        default:
            ulRslt                = VOS_FALSE;
            break;
    }
    return ulRslt;

}


#if  (FEATURE_ON == FEATURE_LTE)

VOS_VOID NAS_MMC_ReadEnableLteTimerLenNvim(VOS_VOID)
{
    NAS_MMC_NVIM_ENABLE_LTE_TIMER_LEN_STRU                  stEnableLteTimerLen;
    VOS_UINT32                                              ulLength;

    PS_MEM_SET(&stEnableLteTimerLen, 0x00, sizeof(stEnableLteTimerLen));
    ulLength = 0;

    /* �Ȼ�ȡNV�ĳ��� */
    (VOS_VOID)NV_GetLength(en_NV_Item_Enable_Lte_Timer_Len, &ulLength);

    if (ulLength > sizeof(NAS_MMC_NVIM_ENABLE_LTE_TIMER_LEN_STRU))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadEnableLteTimerLenNvim(): en_NV_Item_Enable_Lte_Timer_Len length Error");
        return;
    }

    /* ��NVʧ�� */
    if (NV_OK != NV_Read(en_NV_Item_Enable_Lte_Timer_Len,
                         &stEnableLteTimerLen, ulLength))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC,
                      "NAS_MMC_ReadEnableLteTimerLenNvim(): en_NV_Item_Enable_Lte_Timer_Len error");
        return;
    }

    /* nv���������enable lte��ʱ��ʱ��Ϊ0�������ΪĬ��ֵ5���� */
    if (VOS_TRUE == stEnableLteTimerLen.ucNvimActiveFlag)
    {
        if (0 == stEnableLteTimerLen.ucCsfbEmgCallEnableLteTimerLen)
        {
            NAS_MML_SetCsfbEmgCallEnableLteTimerLen(NAS_MML_ENABLE_LTE_TIMER_DEFAULT_LEN);
        }
        else
        {
            /* ����MMLȫ�ֱ����е�enable lte��ʱ��ʱ��,nv�λ�Ƿ��ӣ�����ʱ����λ�Ǻ��� */
            NAS_MML_SetCsfbEmgCallEnableLteTimerLen(stEnableLteTimerLen.ucCsfbEmgCallEnableLteTimerLen * NAS_MML_SIXTY_SECOND
                                         * NAS_MML_ONE_THOUSAND_MILLISECOND);
        }

        if (0 == stEnableLteTimerLen.ucCsPsMode1EnableLteTimerLen)
        {
            NAS_MML_SetCsPsMode13GPPEnableLteTimerLen(NAS_MML_ENABLE_LTE_TIMER_DEFAULT_LEN);
        }
        else
        {
            NAS_MML_SetCsPsMode13GPPEnableLteTimerLen(stEnableLteTimerLen.ucCsPsMode1EnableLteTimerLen * NAS_MML_SIXTY_SECOND
                                         * NAS_MML_ONE_THOUSAND_MILLISECOND);
        }

        if (NAS_MML_VOICE_NOT_PREFER_DISABLED_PLMN_MAX_INVALID_PERIOD == stEnableLteTimerLen.ucLteVoiceNotAvailPlmnForbiddenPeriod)
        {
            NAS_MML_SetVoiceNotAvailPlmnForbiddenPeriod(NAS_MML_MAX_TIME_SLICE);
        }
        else
        {
            NAS_MML_SetVoiceNotAvailPlmnForbiddenPeriod(stEnableLteTimerLen.ucLteVoiceNotAvailPlmnForbiddenPeriod * NAS_MML_SIXTY_SECOND * NAS_MML_ONE_THOUSAND_MILLISECOND);
        }
    }

    return;
}


VOS_VOID NAS_MMC_ReadCsfbRauFollowOnFlgNvim(VOS_VOID)
{
    NAS_MMC_CSFB_RAU_FOLLOW_ON_FLAG_STRU                    stCsfbRauFollowOnFlg;
    VOS_UINT32                                              ulLength;

    ulLength = 0;
    PS_MEM_SET(&stCsfbRauFollowOnFlg, 0x00, sizeof(stCsfbRauFollowOnFlg));

    /* �Ȼ�ȡNV�ĳ��� */
    (VOS_VOID)NV_GetLength(en_NV_Item_CSFB_RAU_FOLLOW_ON_FLAG, &ulLength);

    if (ulLength > sizeof(NAS_MMC_CSFB_RAU_FOLLOW_ON_FLAG_STRU))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadCsfbRauFollowOnFlgNvim(): en_NV_Item_CSFB_RAU_FOLLOW_ON_FLAG length Error");
        return;
    }

    /* ��NVʧ�� */
    if (NV_OK != NV_Read(en_NV_Item_CSFB_RAU_FOLLOW_ON_FLAG,
                         &stCsfbRauFollowOnFlg, ulLength))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadCsfbRauFollowOnFlgNvim(): en_NV_Item_CSFB_RAU_FOLLOW_ON_FLAG error");
        return;
    }

    if (VOS_TRUE == stCsfbRauFollowOnFlg.ucIsRauNeedFollowOnCsfbMtFlg)
    {
         NAS_MML_SetIsRauNeedFollowOnCsfbMtFlg(VOS_TRUE);
    }

    if (VOS_TRUE == stCsfbRauFollowOnFlg.ucIsRauNeedFollowOnCsfbMoFlg)
    {
         NAS_MML_SetIsRauNeedFollowOnCsfbMoFlg(VOS_TRUE);
    }

    return;
}


VOS_VOID NAS_MMC_ReadLteCustomMccInfoNvim(VOS_VOID)
{
    LTE_CUSTOM_MCC_INFO_STRU            stLteCustomMccInfo;
    VOS_UINT32                          ulLength;

    ulLength = 0;
    PS_MEM_SET(&stLteCustomMccInfo, 0x00, sizeof(stLteCustomMccInfo));

    /* �Ȼ�ȡNV�ĳ��� */
    (VOS_VOID)NV_GetLength(EN_NV_ID_LTE_CUSTOM_MCC_INFO, &ulLength);

    if (ulLength > sizeof(LTE_CUSTOM_MCC_INFO_STRU))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadLteCustomMccInfoNvim(): EN_NV_ID_LTE_CUSTOM_MCC_INFO length Error");
        return;
    }

    /* ��NVʧ�� */
    if (NV_OK != NV_Read(EN_NV_ID_LTE_CUSTOM_MCC_INFO,
                         &stLteCustomMccInfo, ulLength))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadLteCustomMccInfoNvim(): EN_NV_ID_LTE_CUSTOM_MCC_INFO error");
        return;
    }

    if (VOS_TRUE == stLteCustomMccInfo.ucSwitchFlag)
    {
         NAS_MML_SetIsDelFddBandSwitchOnFlg(VOS_TRUE);
    }

    return;
}


#endif


VOS_VOID NAS_MMC_ReadSvlteSupportFlagNvim(VOS_VOID)
{
#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    SVLTE_SUPPORT_FLAG_STRU             stSvlteSupportFlag;
    VOS_UINT32                          ulLength;

    ulLength = 0;
    PS_MEM_SET(&stSvlteSupportFlag, 0x00, sizeof(stSvlteSupportFlag));

    /* �Ȼ�ȡNV�ĳ��� */
    (VOS_VOID)NV_GetLength(en_NV_Item_SVLTE_FLAG, &ulLength);

    if (ulLength > sizeof(SVLTE_SUPPORT_FLAG_STRU))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadSvlteSupportFlagNvim(): en_NV_Item_SVLTE_FLAG length Error");
        return;
    }

    /* ��NVʧ�� */
    if (NV_OK != NV_Read(en_NV_Item_SVLTE_FLAG,
                         &stSvlteSupportFlag, ulLength))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadSvlteSupportFlagNvim(): en_NV_Item_SVLTE_FLAG error");
        return;
    }

    if (VOS_TRUE == stSvlteSupportFlag.ucSvlteSupportFlag)
    {
         NAS_MML_SetSvlteSupportFlag(VOS_TRUE);
    }
#endif

    return;
}




VOS_VOID NAS_MMC_ReadPsTransferCfgNvim(VOS_VOID)
{
#if (FEATURE_ON == FEATURE_MULTI_MODEM)

    MTC_NV_PS_TRANSFER_CFG_STRU         stPsTransferCfg;
    VOS_UINT32                          ulLength;

    ulLength = 0;

    PS_MEM_SET(&stPsTransferCfg, 0x00, sizeof(stPsTransferCfg));

    /* �Ȼ�ȡNV�ĳ��� */
    (VOS_VOID)NV_GetLength(en_NV_Item_PS_TRANSFER_CFG, &ulLength);

    if (ulLength > sizeof(MTC_NV_PS_TRANSFER_CFG_STRU))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadPsTransferCfgNvim(): en_NV_Item_PS_TRANSFER_CFG length Error");
        return;
    }

    /* ��NVʧ�� */
    if (NV_OK != NV_Read(en_NV_Item_PS_TRANSFER_CFG,
                         &stPsTransferCfg, ulLength))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadPsTransferCfgNvim(): en_NV_Item_PS_TRANSFER_CFG error");
        return;
    }

    if (MTC_PS_TRANSFER_OFF_AREA == stPsTransferCfg.enSolutionCfg)
    {
         NAS_MML_SetPsTransferOffAreaModeFlag(VOS_TRUE);
    }

#endif

    return;
}




VOS_VOID NAS_MMC_ReadDsdaPlmnSearchEnhancedCfgNvim(VOS_VOID)
{
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    NV_DSDA_PLMN_SEARCH_ENHANCED_CFG_STRU                   stDsdaPlmnSearchEnhancedCfg;
    VOS_UINT32                                              ulLength;

    ulLength = 0;
    PS_MEM_SET(&stDsdaPlmnSearchEnhancedCfg, 0x00, sizeof(stDsdaPlmnSearchEnhancedCfg));

    /* �Ȼ�ȡNV�ĳ��� */
    (VOS_VOID)NV_GetLength(en_NV_Item_DSDA_PLMN_SEARCH_ENHANCED_CFG, &ulLength);

    if (ulLength > sizeof(NV_DSDA_PLMN_SEARCH_ENHANCED_CFG_STRU))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadDsdaPlmnSearchEnhancedCfgNvim(): en_NV_Item_DSDA_PLMN_SEARCH_ENHANCED_CFG length Error");
        return;
    }

    /* ��NVʧ�� */
    if (NV_OK != NV_Read(en_NV_Item_DSDA_PLMN_SEARCH_ENHANCED_CFG,
                         &stDsdaPlmnSearchEnhancedCfg, ulLength))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadDsdaPlmnSearchEnhancedCfgNvim(): en_NV_Item_DSDA_PLMN_SEARCH_ENHANCED_CFG error");
        return;
    }

    if (NAS_MMC_UTRAN_SKIP_W_PLMNSEARCH_MASK == (stDsdaPlmnSearchEnhancedCfg.usSolutionMask & NAS_MMC_UTRAN_SKIP_W_PLMNSEARCH_MASK))
    {
         NAS_MMC_SetUtranSkipWPlmnSearchFlag(VOS_TRUE);
    }

    if (NAS_MMC_SUPPORT_NCELL_SEARCH_MASK == (stDsdaPlmnSearchEnhancedCfg.usSolutionMask & NAS_MMC_SUPPORT_NCELL_SEARCH_MASK))
    {
        NAS_MMC_SetNcellSearchFlag(VOS_TRUE);
        NAS_MMC_SetNcellSearchFirstTimerLen(stDsdaPlmnSearchEnhancedCfg.ucSolution2NcellQuickSearchTimer);
        NAS_MMC_SetNcellSearchSecondTimerLen(stDsdaPlmnSearchEnhancedCfg.ucSolution2NcellQuickSearchTimer2);
    }

#endif

    return;
}



VOS_VOID NAS_MMC_ReadRoamPlmnSelectionSortCfgNvim(VOS_VOID)
{
    NAS_MMC_NVIM_ROAM_PLMN_SELECTION_SORT_CFG_STRU          stNvRoamSortCfg;
    VOS_UINT32                                              ulLength;


    PS_MEM_SET(&stNvRoamSortCfg, 0, sizeof(NAS_MMC_NVIM_ROAM_PLMN_SELECTION_SORT_CFG_STRU));
    ulLength    = 0;

    /* ���������sim��������Ҫ֧�������Ż������������������ */
    if (VOS_TRUE == USIMM_VsimIsActive())
    {
        NAS_MMC_SetRoamPlmnSelectionSortActiveFlg(VOS_FALSE);
    
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadRoamPlmnSelectionSortCfgNvim: Is virtual sim!");
        return;
    }

    /* �Ȼ�ȡNV�ĳ��� */
    (VOS_VOID)NV_GetLength(en_NV_Item_Roam_Plmn_Selection_Sort_Cfg, &ulLength);

    if (ulLength > sizeof(NAS_MMC_NVIM_ROAM_PLMN_SELECTION_SORT_CFG_STRU))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadRoamPlmnSelectionSortCfgNvim(): en_NV_Item_Roam_Plmn_Selection_Sort_Cfg length Error");
        return;
    }

    /* ��NVʧ�� */
    if (NV_OK != NV_Read(en_NV_Item_Roam_Plmn_Selection_Sort_Cfg,
                         &stNvRoamSortCfg, ulLength))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadRoamPlmnSelectionSortCfgNvim(): en_NV_Item_Roam_Plmn_Selection_Sort_Cfg error");
        return;
    }

    NAS_MMC_SetRoamPlmnSelectionSortActiveFlg(VOS_FALSE);

    if (VOS_TRUE == stNvRoamSortCfg.ucRoamPlmnSelectionSortFlg)
    {
        NAS_MMC_SetRoamPlmnSelectionSortActiveFlg(VOS_TRUE);
    }

    return;
}
VOS_VOID NAS_MMC_ReadHistorySearchCfgNvim(VOS_VOID)
{
    NAS_MMC_NVIM_HISTORY_SEARCH_CFG_STRU                    stHistoryCfg;
    VOS_UINT32                                              ulLength;
    NAS_MMC_HISTORY_SEARCH_INFO_STRU                       *pstHistoryInfo  = VOS_NULL_PTR;

    pstHistoryInfo  = NAS_MMC_GetHistorySearchInfo();

    ulLength = 0;
    PS_MEM_SET(&stHistoryCfg, 0x00, sizeof(stHistoryCfg));

    /* �Ȼ�ȡNV�ĳ��� */
    (VOS_VOID)NV_GetLength(en_NV_Item_History_Search_Cfg, &ulLength);

    if (ulLength > sizeof(NAS_MMC_NVIM_HISTORY_SEARCH_CFG_STRU))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadHistorySearchCfgNvim(): en_NV_Item_History_Timer_Len_Cfg length Error");
        return;
    }

    /* ��NVʧ�� */
    if (NV_OK != NV_Read(en_NV_Item_History_Search_Cfg,
                         &stHistoryCfg, ulLength))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadHistorySearchCfgNvim(): en_NV_Item_History_Timer_Len_Cfg error");
        return;
    }

    /* NV�ر�ʱ��ʱ����Ч,������history�� */
    if ( (VOS_FALSE == stHistoryCfg.ucActiveFlg)
      || (0 == stHistoryCfg.ulFirstTimerLen)
      || (0 == stHistoryCfg.ulSecondTimerLen) )
    {
         pstHistoryInfo->ucActiveFlg    = VOS_FALSE;

         return;
    }

    /* NV��ʱ���ѵ�һ�׶�ʱ���͵ڶ��׶�ʱ�����µ�ȫ�ֱ��� */
    pstHistoryInfo->ucActiveFlg         = VOS_TRUE;
    pstHistoryInfo->ulFirstTimerLen     = stHistoryCfg.ulFirstTimerLen;
    pstHistoryInfo->ulSecondTimerLen    = stHistoryCfg.ulSecondTimerLen;

    return;
}


VOS_VOID NAS_MMC_ReadGetGeoCfgInfoNvim(VOS_VOID)
{
    NAS_NVIM_GET_GEO_CFG_INFO_STRU                          stGetGeoCfgInfo;
    VOS_UINT32                                              ulLength;
    VOS_UINT32                                              i;
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstGetGeoRatList  = VOS_NULL_PTR;

    pstGetGeoRatList  = NAS_MML_GetGeoPrioRatList();

    ulLength = 0;
    PS_MEM_SET(&stGetGeoCfgInfo, 0x00, sizeof(NAS_NVIM_GET_GEO_CFG_INFO_STRU));

    /* �Ȼ�ȡNV�ĳ��� */
    (VOS_VOID)NV_GetLength(en_NV_Item_Get_Geo_Cfg_Info, &ulLength);

    if (ulLength > sizeof(NAS_NVIM_GET_GEO_CFG_INFO_STRU))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadGetGeoCfgInfoNvim(): en_NV_Item_Get_Geo_Cfg_Info length Error");
        return;
    }

    /* ��NVʧ�� */
    if (NV_OK != NV_Read(en_NV_Item_Get_Geo_Cfg_Info, &stGetGeoCfgInfo, ulLength))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadGetGeoCfgInfoNvim(): en_NV_Item_Get_Geo_Cfg_Info error");
        return;
    }

    /* NV��δ��ʱ�����뼼����Ч */
    if (VOS_FALSE == stGetGeoCfgInfo.ucActiveFlag)
    {
        return;
    }

    /* ���������������������� */
    if (NAS_MML_MAX_RAT_NUM < stGetGeoCfgInfo.stGetGeoPrioRatList.ucRatOrderNum)
    {
        stGetGeoCfgInfo.stGetGeoPrioRatList.ucRatOrderNum   = NAS_MML_MAX_RAT_NUM;
    }

    for (i = 0; i < stGetGeoCfgInfo.stGetGeoPrioRatList.ucRatOrderNum; i++)
    {
        pstGetGeoRatList->aucRatPrio[i]  = stGetGeoCfgInfo.stGetGeoPrioRatList.aucRatOrder[i];
    }

    pstGetGeoRatList->ucRatNum  = stGetGeoCfgInfo.stGetGeoPrioRatList.ucRatOrderNum;

    return;
}


VOS_VOID  NAS_MMC_ReadIsrSupportNvim( VOS_VOID )
{
    VOS_UINT32                          ulLen;
    NAS_NVIM_ISR_CFG_STRU               stIsrCfg;

    ulLen = 0;

    PS_MEM_SET(&stIsrCfg, 0x00, sizeof(stIsrCfg));
    (VOS_VOID)NV_GetLength(en_NV_Item_NasIsrSupport, &ulLen);

    /* ��NV��en_NV_Item_NasIsrSupport��ʧ�ܣ�ֱ�ӷ��� */
    if (NV_OK != NV_Read(en_NV_Item_NasIsrSupport,
                         &stIsrCfg, ulLen))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadIsrSupportNvim():WARNING: read en_NV_Item_NasIsrSupport Error");

        return;
    }

    if ( VOS_TRUE == stIsrCfg.ucIsrSupport)
    {
        NAS_MML_SetIsrSupportFlg(VOS_TRUE);
    }
    else
    {
        NAS_MML_SetIsrSupportFlg(VOS_FALSE);
    }

}
VOS_VOID NAS_MMC_ReadRefreshRplmnWhenEplmnInvalidCfgNvim(VOS_VOID)
{
    NAS_NVIM_REFRESH_RPLMN_WHEN_EPLMN_INVALID_CFG_STRU      stRefreshRplmnCfg;
    VOS_UINT32                                              ulLength;

    ulLength = 0;
    PS_MEM_SET(&stRefreshRplmnCfg, 0x00, sizeof(stRefreshRplmnCfg));

    /* USIM��ʱ��ɾ������Ĭ��ֵ���� */
    if (VOS_TRUE == NAS_USIMMAPI_IsTestCard())
    {
        return ;
    }

    /* �Ȼ�ȡNV�ĳ��� */
    (VOS_VOID)NV_GetLength(en_NV_Item_REFRESH_RPLMN_WHEN_EPLMN_INVALID_CFG, &ulLength);

    if (ulLength > sizeof(NAS_NVIM_REFRESH_RPLMN_WHEN_EPLMN_INVALID_CFG_STRU))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadRefreshRplmnWhenEplmnInvalidCfgNvim(): en_NV_Item_REFRESH_RPLMN_WHEN_EPLMN_INVALID_CFG length Error");
        return;
    }

    /* ��NVʧ�� */
    if (NV_OK != NV_Read(en_NV_Item_REFRESH_RPLMN_WHEN_EPLMN_INVALID_CFG,
                         &stRefreshRplmnCfg, ulLength))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadRefreshRplmnWhenEplmnInvalidCfgNvim(): en_NV_Item_REFRESH_RPLMN_WHEN_EPLMN_INVALID_CFG error");
        return;
    }    

    /* ����Ҫɾ��RPLMN�����ã�����Ĭ����Ҫɾ��RPLMN */
    if (VOS_FALSE == stRefreshRplmnCfg.ucDeleteRplmnFlg)
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "DeleteRplmnWhenEplmnInvalidFlg IS FALSE");
        NAS_MML_SetDeleteRplmnWhenEplmnInvalidFlg(VOS_FALSE);
        
        return;
    }

    NAS_NORMAL_LOG(WUEPS_PID_MMC, "DeleteRplmnWhenEplmnInvalidFlg IS TRUE");

    NAS_MML_SetDeleteRplmnWhenEplmnInvalidFlg(VOS_TRUE);
    
    return;
}


#if (FEATURE_ON == FEATURE_PTM)

VOS_VOID NAS_MMC_ReadErrlogCtrlInfoNvim(VOS_VOID)
{
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulLength;
    NV_ID_ERR_LOG_CTRL_INFO_STRU        stErrorLogCtrlInfo;

    ulLength = 0;
    PS_MEM_SET(&stErrorLogCtrlInfo, 0x00, sizeof(NV_ID_ERR_LOG_CTRL_INFO_STRU));
    (VOS_VOID)NV_GetLength(en_NV_Item_ErrLogCtrlInfo, &ulLength);

    ulResult = NV_Read(en_NV_Item_ErrLogCtrlInfo,
                       &stErrorLogCtrlInfo,
                       ulLength);

    if (ulResult == NV_OK)
    {
        NAS_MML_SetErrlogCtrlFlag(stErrorLogCtrlInfo.ucAlmStatus);
        NAS_MML_SetErrlogAlmLevel(stErrorLogCtrlInfo.ucAlmLevel);
    }
    else
    {
        NAS_MML_SetErrlogCtrlFlag(VOS_FALSE);
        NAS_MML_SetErrlogAlmLevel(NAS_ERR_LOG_CTRL_LEVEL_CRITICAL);
    }

    return;
}


VOS_VOID NAS_MMC_ReadErrlogNwSrchRecordcfgNvim(VOS_VOID)
{
    VOS_UINT32                              ulResult;
    VOS_UINT32                              ulLength;
    NAS_NVIM_NW_SEARCH_CHR_RECORD_CFG_STRU  stRecordCfg;

    ulLength = 0;
    PS_MEM_SET(&stRecordCfg, 0x00, sizeof(NAS_NVIM_NW_SEARCH_CHR_RECORD_CFG_STRU));
    (VOS_VOID)NV_GetLength(en_NV_Item_Nw_Search_Chr_Record_Cfg, &ulLength);

    if (ulLength > sizeof(NAS_NVIM_NW_SEARCH_CHR_RECORD_CFG_STRU))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadErrlogNwSrchRecordcfgNvim():WARNING: en_NV_Item_Nw_Search_Chr_Record_Cfg length Error");

        return;
    }

    ulResult = NV_Read(en_NV_Item_Nw_Search_Chr_Record_Cfg,
                       &stRecordCfg,
                       ulLength);

    if (ulResult != NV_OK)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadErrlogNwSrchRecordcfgNvim():WARNING: read en_NV_Item_Nw_Search_Chr_Record_Cfg Error");

        NAS_MML_SetErrLogNwSrchCfgActiveFlag(VOS_FALSE);
        NAS_MML_SetErrLogNwSrchCfgRecordNum(0);

        return;
    }

    NAS_MML_SetErrLogNwSrchCfgActiveFlag(stRecordCfg.ucActiveFlag);
    NAS_MML_SetErrLogNwSrchCfgRecordNum(stRecordCfg.ulRecordNum);

    /* ���Կ����򲻿����ù��� */
    if (VOS_TRUE == NAS_USIMMAPI_IsTestCard())
    {
        NAS_MML_SetErrLogNwSrchCfgActiveFlag(VOS_FALSE);
    }

    return;
}


#endif
VOS_VOID NAS_MMC_ReadAccBarPlmnSearchNvim(VOS_VOID)
{
    VOS_UINT32                                              ulLen;
    NAS_MMC_NVIM_ACC_BAR_PLMN_SEARCH_FLG_STRU               stAccBarPlmnSearchFlg;

    ulLen = 0;

    PS_MEM_SET(&stAccBarPlmnSearchFlg, 0x00, sizeof(NAS_MMC_NVIM_ACC_BAR_PLMN_SEARCH_FLG_STRU));
    (VOS_VOID)NV_GetLength(en_NV_Item_ACC_BAR_PLMN_SEARCH_FLG, &ulLen);

    /* ��NV��en_NV_Item_ACC_BAR_PLMN_SEARCH_FLG��ʧ�ܣ�ֱ�ӷ��� */
    if (NV_OK != NV_Read(en_NV_Item_ACC_BAR_PLMN_SEARCH_FLG,
                         &stAccBarPlmnSearchFlg, ulLen))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadAccBarPlmnSearchNvim():WARNING: read en_NV_Item_ACC_BAR_PLMN_SEARCH_FLG Error");

        return;
    }

    /* ��ֵ��ȫ�ֱ��� */
    if ( VOS_TRUE == stAccBarPlmnSearchFlg.ucAccBarPlmnSearchFlg)
    {
        NAS_MML_SetSupportAccBarPlmnSearchFlg(VOS_TRUE);
    }
    else
    {
        NAS_MML_SetSupportAccBarPlmnSearchFlg(VOS_FALSE);
    }

    return;
}



VOS_VOID NAS_MMC_ReadUserCfgOPlmnInfoNvim(VOS_VOID)
{
    VOS_UINT32                                              ulLen;
    VOS_UINT32                                              ulStep;
    VOS_UINT32                                              ulNvOplmnAvail;
    NAS_MML_PLMN_ID_STRU                                    stPlmn;
    NAS_MML_SIM_FORMAT_PLMN_ID                              stSimPlmn;
    NAS_MMC_NVIM_USER_CFG_OPLMN_EXTEND_STRU                *pstNvimCfgOPlmnInfo = VOS_NULL_PTR;
    NAS_MML_USER_CFG_OPLMN_INFO_STRU                       *pstUserCfgOPlmnInfo = VOS_NULL_PTR;

    ulLen = 0;
    PS_MEM_SET(&stPlmn, 0x00, sizeof(NAS_MML_PLMN_ID_STRU));
    PS_MEM_SET(&stSimPlmn, 0x00, sizeof(NAS_MML_SIM_FORMAT_PLMN_ID));

    pstNvimCfgOPlmnInfo = (NAS_MMC_NVIM_USER_CFG_OPLMN_EXTEND_STRU*)PS_MEM_ALLOC(
                                                      WUEPS_PID_MMC,
                                                      sizeof(NAS_MMC_NVIM_USER_CFG_OPLMN_EXTEND_STRU));
    if (VOS_NULL_PTR == pstNvimCfgOPlmnInfo)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadUserCfgOPlmnInfoNvim():ERROR: Memory Alloc Error");
        return;
    }

    PS_MEM_SET(pstNvimCfgOPlmnInfo, 0x00, sizeof(NAS_MMC_NVIM_USER_CFG_OPLMN_EXTEND_STRU));

    (VOS_VOID)NV_GetLength(en_NV_Item_USER_CFG_OPLMN_EXTEND_LIST, &ulLen);

    pstUserCfgOPlmnInfo = NAS_MML_GetUserCfgOPlmnInfo();

    /* ��NV��en_NV_Item_USER_CFG_OPLMN_EXTEND_LIST��ʧ�ܣ�ֱ�ӷ��� */
    if (NV_OK != NV_Read(en_NV_Item_USER_CFG_OPLMN_EXTEND_LIST,
                         pstNvimCfgOPlmnInfo, ulLen))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadUserCfgOPlmnInfoNvim():WARNING: read en_NV_Item_USER_CFG_OPLMN_EXTEND_LIST Error");
        PS_MEM_FREE(WUEPS_PID_MMC, pstNvimCfgOPlmnInfo);
        return;
    }

    /* ȷ��ucActiveFlgֵ��Ч��ΪVOS_TRUE��VOS_FALSE */
    if (VOS_TRUE != pstNvimCfgOPlmnInfo->ucActiveFlg)
    {
         pstNvimCfgOPlmnInfo->ucActiveFlg = VOS_FALSE;
    }

    /* ȷ��ucImsiCheckFlgֵ��Ч��ΪVOS_TRUE��VOS_FALSE */
    if (VOS_FALSE != pstNvimCfgOPlmnInfo->ucImsiCheckFlg)
    {
         pstNvimCfgOPlmnInfo->ucImsiCheckFlg = VOS_TRUE;
    }

    /* ��NV�е�PLMN LIST��Ϣ���浽MML��ȫ�ֱ�����ȥ */
    pstUserCfgOPlmnInfo->ucActiveFlg       = pstNvimCfgOPlmnInfo->ucActiveFlg;
    pstUserCfgOPlmnInfo->ucImsiCheckFlg    = pstNvimCfgOPlmnInfo->ucImsiCheckFlg;
    PS_MEM_CPY(pstUserCfgOPlmnInfo->aucVersion, pstNvimCfgOPlmnInfo->aucVersion, sizeof(pstUserCfgOPlmnInfo->aucVersion));

    /* ��NV�е�OPLMN���浽�ڴ���,��Ҫ��ֹ����Խ�� */
    if ( pstNvimCfgOPlmnInfo->usOplmnListNum > NAS_MML_MAX_USER_CFG_OPLMN_NUM )
    {
        pstNvimCfgOPlmnInfo->usOplmnListNum = NAS_MML_MAX_USER_CFG_OPLMN_NUM;
    }
    pstUserCfgOPlmnInfo->usOplmnListNum = pstNvimCfgOPlmnInfo->usOplmnListNum;

    /* ��NV�б����IMSI��Ϣת��Ϊ�ڴ��е���Ϣ,��Ҫ��ֹ����Խ�� */
    if ( pstNvimCfgOPlmnInfo->ucImsiPlmnListNum > NAS_MML_MAX_USER_OPLMN_IMSI_NUM )
    {
        pstNvimCfgOPlmnInfo->ucImsiPlmnListNum = NAS_MML_MAX_USER_OPLMN_IMSI_NUM;
    }

    pstUserCfgOPlmnInfo->ucImsiPlmnListNum = 0;
    for ( ulStep = 0; ulStep < pstNvimCfgOPlmnInfo->ucImsiPlmnListNum; ulStep++ )
    {
        PS_MEM_CPY(stSimPlmn.aucSimPlmn, pstNvimCfgOPlmnInfo->astImsiPlmnList[ulStep].aucSimPlmn, NAS_MML_SIM_PLMN_ID_LEN);
        NAS_MMC_ConvertSimPlmnToNasPLMN(&stSimPlmn, &stPlmn);

        if (VOS_TRUE == NAS_MML_IsPlmnIdValid(&stPlmn))
        {
            pstUserCfgOPlmnInfo->astImsiPlmnList[pstUserCfgOPlmnInfo->ucImsiPlmnListNum] = stPlmn;
            pstUserCfgOPlmnInfo->ucImsiPlmnListNum++;
        }
    }

    /* ����û����õ�OPLMN��Ч����Ҫ��NV�е�OPLMN�б��浽MMLȫ�ֱ����� */
    ulNvOplmnAvail = NAS_MML_IsNvimOplmnAvail();

    if (VOS_TRUE == ulNvOplmnAvail)
    {
        /* ʹ��NV�е�OPLMN�ļ�����MML�б��濨�ļ�OPLMN��Ϣ��ȫ�ֱ��� */
        NAS_MMC_UpdateOPlmnInfoFromNvim(pstNvimCfgOPlmnInfo->aucOPlmnList, pstNvimCfgOPlmnInfo->usOplmnListNum);
    }

    PS_MEM_FREE(WUEPS_PID_MMC, pstNvimCfgOPlmnInfo);
    return;
}


 VOS_VOID  NAS_MMC_ReadDplmnNplmnInfoNvim(VOS_VOID)
{
    VOS_UINT32                                              ulLen;
    NAS_MML_PLMN_ID_STRU                                    stHplmnId;
    VOS_UINT8                                               ucHplmnType;
    VOS_UINT8                                              *pucImsi         = VOS_NULL_PTR;
    NAS_MMC_NVIM_CFG_DPLMN_NPLMN_INFO_STRU                 *pstNvimCfgDPlmnNPlmnInfo = VOS_NULL_PTR;
    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU                      *pstDPlmnNPlmnCfgInfo = VOS_NULL_PTR;
    NAS_MMC_NVIM_CFG_DPLMN_NPLMN_FLAG_STRU                 *pstNvimCfgDPlmnNPlmnFlag = VOS_NULL_PTR;

    ulLen = 0;
    /* ȡ���ֻ�����IMSI����Ϣ */
    pucImsi     = NAS_MML_GetSimImsi();

    /* �ӵ�ǰ��IMSI��ȡ��home plmn */
    stHplmnId  = NAS_MML_GetImsiHomePlmn(pucImsi);

    pstNvimCfgDPlmnNPlmnFlag = (NAS_MMC_NVIM_CFG_DPLMN_NPLMN_FLAG_STRU*)PS_MEM_ALLOC(
                                                      WUEPS_PID_MMC,
                                                      sizeof(NAS_MMC_NVIM_CFG_DPLMN_NPLMN_FLAG_STRU));
    if (VOS_NULL_PTR == pstNvimCfgDPlmnNPlmnFlag)
    {
        return;
    }

    pstNvimCfgDPlmnNPlmnInfo = (NAS_MMC_NVIM_CFG_DPLMN_NPLMN_INFO_STRU*)PS_MEM_ALLOC(
                                                      WUEPS_PID_MMC,
                                                      sizeof(NAS_MMC_NVIM_CFG_DPLMN_NPLMN_INFO_STRU));
    if (VOS_NULL_PTR == pstNvimCfgDPlmnNPlmnInfo)
    {
        PS_MEM_FREE(WUEPS_PID_MMC, pstNvimCfgDPlmnNPlmnFlag);
        return;
    }

    pstDPlmnNPlmnCfgInfo = NAS_MMC_GetDPlmnNPlmnCfgInfo();

    PS_MEM_SET(pstNvimCfgDPlmnNPlmnFlag, 0x00, sizeof(NAS_MMC_NVIM_CFG_DPLMN_NPLMN_FLAG_STRU));

    (VOS_VOID)NV_GetLength(en_NV_Item_Cfg_Dplmn_Nplmn_Flag, &ulLen);

    if (ulLen > sizeof(NAS_MMC_NVIM_CFG_DPLMN_NPLMN_FLAG_STRU))
    {
        PS_MEM_FREE(WUEPS_PID_MMC, pstNvimCfgDPlmnNPlmnFlag);
        PS_MEM_FREE(WUEPS_PID_MMC, pstNvimCfgDPlmnNPlmnInfo);
        return;
    }

    if (NV_OK != NV_Read(en_NV_Item_Cfg_Dplmn_Nplmn_Flag, pstNvimCfgDPlmnNPlmnFlag, ulLen))
    {
        PS_MEM_FREE(WUEPS_PID_MMC, pstNvimCfgDPlmnNPlmnFlag);
        PS_MEM_FREE(WUEPS_PID_MMC, pstNvimCfgDPlmnNPlmnInfo);
        return;
    }

    if (VOS_TRUE == pstNvimCfgDPlmnNPlmnFlag->usCfgDplmnNplmnFlag)
    {
        pstDPlmnNPlmnCfgInfo->ucActiveFlg = VOS_TRUE;
    }
    else
    {
        PS_MEM_FREE(WUEPS_PID_MMC, pstNvimCfgDPlmnNPlmnFlag);
        PS_MEM_FREE(WUEPS_PID_MMC, pstNvimCfgDPlmnNPlmnInfo);
        return;
    }

    pstDPlmnNPlmnCfgInfo->ucCMCCHplmnNum = 0;
    pstDPlmnNPlmnCfgInfo->ucUNICOMHplmnNum = 0;
    pstDPlmnNPlmnCfgInfo->ucCTHplmnNum = 0;

    NAS_MMC_UpdateDPlmnNPlmnFlagInfo(pstNvimCfgDPlmnNPlmnFlag);

    PS_MEM_SET(pstNvimCfgDPlmnNPlmnInfo, 0x00, sizeof(NAS_MMC_NVIM_CFG_DPLMN_NPLMN_INFO_STRU));

    ucHplmnType = NAS_MMC_JudegeHplmnType(&stHplmnId);

    /* Modified by c00318887 for DPlmn���ݺ����Ƚ���HPLMN, 2015-5-28, begin */
    if (NAS_MMC_HPLMN_TYPE_CMCC == ucHplmnType)
    {
        (VOS_VOID)NV_GetLength(en_NV_Item_CMCC_Cfg_Dplmn_Nplmn_Info, &ulLen);

        if (ulLen > sizeof(NAS_MMC_NVIM_CFG_DPLMN_NPLMN_INFO_STRU))
        {
            PS_MEM_FREE(WUEPS_PID_MMC, pstNvimCfgDPlmnNPlmnFlag);
            PS_MEM_FREE(WUEPS_PID_MMC, pstNvimCfgDPlmnNPlmnInfo);
            return;
        }

        /* ��NV��en_NV_Item_CMCC_Cfg_Dplmn_Nplmn_Info��ʧ�ܣ�ֱ�ӷ��� */
        if (NV_OK != NV_Read(en_NV_Item_CMCC_Cfg_Dplmn_Nplmn_Info,
                             pstNvimCfgDPlmnNPlmnInfo, ulLen))
        {
            PS_MEM_FREE(WUEPS_PID_MMC, pstNvimCfgDPlmnNPlmnFlag);
            PS_MEM_FREE(WUEPS_PID_MMC, pstNvimCfgDPlmnNPlmnInfo);
            return;
        }
    }
    else if (NAS_MMC_HPLMN_TYPE_UNICOM == ucHplmnType)
    {
        (VOS_VOID)NV_GetLength(en_NV_Item_UNICOM_Cfg_Dplmn_Nplmn_Info, &ulLen);

        if (ulLen > sizeof(NAS_MMC_NVIM_CFG_DPLMN_NPLMN_INFO_STRU))
        {
            PS_MEM_FREE(WUEPS_PID_MMC, pstNvimCfgDPlmnNPlmnFlag);
            PS_MEM_FREE(WUEPS_PID_MMC, pstNvimCfgDPlmnNPlmnInfo);
            return;
        }

        /* ��NV��en_NV_Item_UNICOM_Cfg_Dplmn_Nplmn_Info��ʧ�ܣ�ֱ�ӷ��� */
        if (NV_OK != NV_Read(en_NV_Item_UNICOM_Cfg_Dplmn_Nplmn_Info,
                             pstNvimCfgDPlmnNPlmnInfo, ulLen))
        {
            PS_MEM_FREE(WUEPS_PID_MMC, pstNvimCfgDPlmnNPlmnFlag);
            PS_MEM_FREE(WUEPS_PID_MMC, pstNvimCfgDPlmnNPlmnInfo);
            return;
        }
    }
    else if (NAS_MMC_HPLMN_TYPE_CT == ucHplmnType)
    {
        (VOS_VOID)NV_GetLength(en_NV_Item_CT_Cfg_Dplmn_Nplmn_Info, &ulLen);

        if (ulLen > sizeof(NAS_MMC_NVIM_CFG_DPLMN_NPLMN_INFO_STRU))
        {
            PS_MEM_FREE(WUEPS_PID_MMC, pstNvimCfgDPlmnNPlmnFlag);
            PS_MEM_FREE(WUEPS_PID_MMC, pstNvimCfgDPlmnNPlmnInfo);
            return;
        }

        /* ��NV��en_NV_Item_CT_Cfg_Dplmn_Nplmn��ʧ�ܣ�ֱ�ӷ��� */
        if (NV_OK != NV_Read(en_NV_Item_CT_Cfg_Dplmn_Nplmn_Info,
                             pstNvimCfgDPlmnNPlmnInfo, ulLen))
        {
            PS_MEM_FREE(WUEPS_PID_MMC, pstNvimCfgDPlmnNPlmnFlag);
            PS_MEM_FREE(WUEPS_PID_MMC, pstNvimCfgDPlmnNPlmnInfo);
            return;
        }
    }
    else
    {
        pstDPlmnNPlmnCfgInfo->ucActiveFlg = VOS_FALSE;
        PS_MEM_FREE(WUEPS_PID_MMC, pstNvimCfgDPlmnNPlmnFlag);
        PS_MEM_FREE(WUEPS_PID_MMC, pstNvimCfgDPlmnNPlmnInfo);
        return;
    }
    /* Modified by c00318887 for DPlmn���ݺ����Ƚ���HPLMN, 2015-5-28, end */

    pstDPlmnNPlmnCfgInfo->usDplmnListNum = 0;
    pstDPlmnNPlmnCfgInfo->usNplmnListNum = 0;

    NAS_MMC_UpdateDplmnNplmnInfo(pstNvimCfgDPlmnNPlmnInfo);

    PS_MEM_FREE(WUEPS_PID_MMC, pstNvimCfgDPlmnNPlmnFlag);
    PS_MEM_FREE(WUEPS_PID_MMC, pstNvimCfgDPlmnNPlmnInfo);
    return;
}
VOS_VOID NAS_MMC_WriteDplmnNplmnToNvim(VOS_VOID)
{
    VOS_UINT32                                              ulLen;
    VOS_UINT32                                              ulStep;
    NAS_MML_PLMN_ID_STRU                                    stUserPlmn;
    NAS_MML_SIM_FORMAT_PLMN_ID                              stNvimPlmn;
    NAS_MML_PLMN_ID_STRU                                    stHplmnId;
    VOS_UINT8                                               ucHplmnType;
    VOS_UINT8                                              *pucImsi = VOS_NULL_PTR;
    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU                      *pstDPlmnNPlmnCfgInfo = VOS_NULL_PTR;
    NAS_MMC_NVIM_CFG_DPLMN_NPLMN_INFO_STRU                 *pstNvimCfgDPlmnNPlmnInfo = VOS_NULL_PTR;

    PS_MEM_SET(&stHplmnId, 0, sizeof(stHplmnId));
    PS_MEM_SET(&stNvimPlmn, 0, sizeof(stNvimPlmn));
    PS_MEM_SET(&stUserPlmn, 0, sizeof(stUserPlmn));
    ulLen       = 0;
    ulStep      = 0;
    ucHplmnType = 0;

    /* ȡ���ֻ�����IMSI����Ϣ */
    pucImsi    = NAS_MML_GetSimImsi();

    /* �ӵ�ǰ��IMSI��ȡ��home plmn */
    stHplmnId  = NAS_MML_GetImsiHomePlmn(pucImsi);

    pstDPlmnNPlmnCfgInfo = NAS_MMC_GetDPlmnNPlmnCfgInfo();

    if (VOS_TRUE != pstDPlmnNPlmnCfgInfo->ucActiveFlg)
    {
        return;
    }

    pstNvimCfgDPlmnNPlmnInfo = (NAS_MMC_NVIM_CFG_DPLMN_NPLMN_INFO_STRU*)PS_MEM_ALLOC(
                                   WUEPS_PID_MMC,
                                   sizeof(NAS_MMC_NVIM_CFG_DPLMN_NPLMN_INFO_STRU));

    if (VOS_NULL_PTR == pstNvimCfgDPlmnNPlmnInfo)
    {
        return;
    }

    PS_MEM_SET(pstNvimCfgDPlmnNPlmnInfo, 0x00, sizeof(NAS_MMC_NVIM_CFG_DPLMN_NPLMN_INFO_STRU));

    if ( pstDPlmnNPlmnCfgInfo->usDplmnListNum > NAS_MMC_MAX_CFG_DPLMN_NUM )
    {
        pstDPlmnNPlmnCfgInfo->usDplmnListNum = NAS_MMC_MAX_CFG_DPLMN_NUM;
    }

    pstNvimCfgDPlmnNPlmnInfo->usDplmnListNum = pstDPlmnNPlmnCfgInfo->usDplmnListNum;

    for ( ulStep = 0; ulStep < pstDPlmnNPlmnCfgInfo->usDplmnListNum; ulStep++ )
    {
        stNvimPlmn.aucSimPlmn[0] = 0;
        stNvimPlmn.aucSimPlmn[1] = 0;
        stNvimPlmn.aucSimPlmn[2] = 0;
        stUserPlmn.ulMcc = pstDPlmnNPlmnCfgInfo->astDPlmnList[ulStep].stSimPlmnWithRat.stPlmnId.ulMcc;
        stUserPlmn.ulMnc = pstDPlmnNPlmnCfgInfo->astDPlmnList[ulStep].stSimPlmnWithRat.stPlmnId.ulMnc;

        NAS_MMC_ConvertNasPlmnToSimFormat(&stUserPlmn, &stNvimPlmn);

        /* Modified by c00318887 for DPlmn���ݺ����Ƚ���HPLMN, 2015-5-20, begin */

        pstNvimCfgDPlmnNPlmnInfo->aucDPlmnList[(ulStep * NAS_MMC_DPLMN_NPLMN_NV_INFO_LEN)]     = stNvimPlmn.aucSimPlmn[0];
        pstNvimCfgDPlmnNPlmnInfo->aucDPlmnList[(ulStep * NAS_MMC_DPLMN_NPLMN_NV_INFO_LEN) + 1] = stNvimPlmn.aucSimPlmn[1];
        pstNvimCfgDPlmnNPlmnInfo->aucDPlmnList[(ulStep * NAS_MMC_DPLMN_NPLMN_NV_INFO_LEN) + 2] = stNvimPlmn.aucSimPlmn[2];
        pstNvimCfgDPlmnNPlmnInfo->aucDPlmnList[(ulStep * NAS_MMC_DPLMN_NPLMN_NV_INFO_LEN) + 3] = (VOS_UINT8)((pstDPlmnNPlmnCfgInfo->astDPlmnList[ulStep].stSimPlmnWithRat.usSimRat) >> NAS_MML_OCTET_MOVE_EIGHT_BITS);
        pstNvimCfgDPlmnNPlmnInfo->aucDPlmnList[(ulStep * NAS_MMC_DPLMN_NPLMN_NV_INFO_LEN) + 4] = (VOS_UINT8)((pstDPlmnNPlmnCfgInfo->astDPlmnList[ulStep].stSimPlmnWithRat.usSimRat) & (0x00FF));

        /* ����ע������Ϣ */
        pstNvimCfgDPlmnNPlmnInfo->aucDPlmnList[(ulStep * NAS_MMC_DPLMN_NPLMN_NV_INFO_LEN) + 5] = pstDPlmnNPlmnCfgInfo->astDPlmnList[ulStep].enRegDomain;

        /* ����������Ϣ */
        pstNvimCfgDPlmnNPlmnInfo->aucDPlmnList[(ulStep * NAS_MMC_DPLMN_NPLMN_NV_INFO_LEN) + NAS_MMC_DPLMN_NPLMN_NV_PRESETING_FLAG_INDEX] = pstDPlmnNPlmnCfgInfo->astDPlmnList[ulStep].enType;

        /* Modified by c00318887 for DPlmn���ݺ����Ƚ���HPLMN, 2015-5-20, end */

    }

    if ( pstDPlmnNPlmnCfgInfo->usNplmnListNum > NAS_MMC_MAX_CFG_NPLMN_NUM )
    {
        pstDPlmnNPlmnCfgInfo->usNplmnListNum = NAS_MMC_MAX_CFG_NPLMN_NUM;
    }

    pstNvimCfgDPlmnNPlmnInfo->usNplmnListNum = pstDPlmnNPlmnCfgInfo->usNplmnListNum;

    for ( ulStep = 0; ulStep < pstDPlmnNPlmnCfgInfo->usNplmnListNum; ulStep++ )
    {
        stNvimPlmn.aucSimPlmn[0]= 0;
        stNvimPlmn.aucSimPlmn[1]= 0;
        stNvimPlmn.aucSimPlmn[2]= 0;
        stUserPlmn.ulMcc        = pstDPlmnNPlmnCfgInfo->astNPlmnList[ulStep].stSimPlmnWithRat.stPlmnId.ulMcc;
        stUserPlmn.ulMnc        = pstDPlmnNPlmnCfgInfo->astNPlmnList[ulStep].stSimPlmnWithRat.stPlmnId.ulMnc;

        NAS_MMC_ConvertNasPlmnToSimFormat(&stUserPlmn, &stNvimPlmn);

        /* Modified by c00318887 for DPlmn���ݺ����Ƚ���HPLMN, 2015-5-20, begin */
        pstNvimCfgDPlmnNPlmnInfo->aucNPlmnList[(ulStep * NAS_MMC_DPLMN_NPLMN_NV_INFO_LEN)]     = stNvimPlmn.aucSimPlmn[0];
        pstNvimCfgDPlmnNPlmnInfo->aucNPlmnList[(ulStep * NAS_MMC_DPLMN_NPLMN_NV_INFO_LEN) + 1] = stNvimPlmn.aucSimPlmn[1];
        pstNvimCfgDPlmnNPlmnInfo->aucNPlmnList[(ulStep * NAS_MMC_DPLMN_NPLMN_NV_INFO_LEN) + 2] = stNvimPlmn.aucSimPlmn[2];
        pstNvimCfgDPlmnNPlmnInfo->aucNPlmnList[(ulStep * NAS_MMC_DPLMN_NPLMN_NV_INFO_LEN) + 3] = (VOS_UINT8)((pstDPlmnNPlmnCfgInfo->astNPlmnList[ulStep].stSimPlmnWithRat.usSimRat) >> NAS_MML_OCTET_MOVE_EIGHT_BITS);
        pstNvimCfgDPlmnNPlmnInfo->aucNPlmnList[(ulStep * NAS_MMC_DPLMN_NPLMN_NV_INFO_LEN) + 4] = (VOS_UINT8)((pstDPlmnNPlmnCfgInfo->astNPlmnList[ulStep].stSimPlmnWithRat.usSimRat) & (0x00FF));

        /* ����ע������Ϣ */
        pstNvimCfgDPlmnNPlmnInfo->aucNPlmnList[(ulStep * NAS_MMC_DPLMN_NPLMN_NV_INFO_LEN) + 5] = pstDPlmnNPlmnCfgInfo->astNPlmnList[ulStep].enRegDomain;

        /* ����������Ϣ */
        pstNvimCfgDPlmnNPlmnInfo->aucNPlmnList[(ulStep * NAS_MMC_DPLMN_NPLMN_NV_INFO_LEN) + NAS_MMC_DPLMN_NPLMN_NV_PRESETING_FLAG_INDEX] = pstDPlmnNPlmnCfgInfo->astNPlmnList[ulStep].enType;

    /* Modified by c00318887 for DPlmn���ݺ����Ƚ���HPLMN, 2015-5-20, end */

    }

    ucHplmnType = NAS_MMC_JudegeHplmnType(&stHplmnId);

    /* Modified by c00318887 for DPlmn���ݺ����Ƚ���HPLMN, 2015-5-28, begin */
    if (NAS_MMC_HPLMN_TYPE_CMCC == ucHplmnType)
    {
        (VOS_VOID)NV_GetLength(en_NV_Item_CMCC_Cfg_Dplmn_Nplmn_Info, &ulLen);

        /* дNV��en_NV_Item_CMCC_Cfg_Dplmn_Nplmn��ʧ�ܣ�ֱ�ӷ��� */
        if (NV_OK != NV_Write(en_NV_Item_CMCC_Cfg_Dplmn_Nplmn_Info,
                              pstNvimCfgDPlmnNPlmnInfo, ulLen))
        {
            PS_MEM_FREE(WUEPS_PID_MMC, pstNvimCfgDPlmnNPlmnInfo);
            return;
        }
    }

    if (NAS_MMC_HPLMN_TYPE_UNICOM == ucHplmnType)
    {
        (VOS_VOID)NV_GetLength(en_NV_Item_UNICOM_Cfg_Dplmn_Nplmn_Info, &ulLen);
        /* дNV��en_NV_Item_UNICOM_Cfg_Dplmn_Nplmn��ʧ�ܣ�ֱ�ӷ��� */
        if (NV_OK != NV_Write(en_NV_Item_UNICOM_Cfg_Dplmn_Nplmn_Info,
                              pstNvimCfgDPlmnNPlmnInfo, ulLen))
        {
            PS_MEM_FREE(WUEPS_PID_MMC, pstNvimCfgDPlmnNPlmnInfo);
            return;
        }
    }

    if (NAS_MMC_HPLMN_TYPE_CT == ucHplmnType)
    {
        (VOS_VOID)NV_GetLength(en_NV_Item_CT_Cfg_Dplmn_Nplmn_Info, &ulLen);
        /* дNV��en_NV_Item_CT_Cfg_Dplmn_Nplmn��ʧ�ܣ�ֱ�ӷ��� */
        if (NV_OK != NV_Write(en_NV_Item_CT_Cfg_Dplmn_Nplmn_Info,
                              pstNvimCfgDPlmnNPlmnInfo, ulLen))
        {
            PS_MEM_FREE(WUEPS_PID_MMC, pstNvimCfgDPlmnNPlmnInfo);
            return;
        }
    }
    /* Modified by c00318887 for DPlmn���ݺ����Ƚ���HPLMN, 2015-5-28, end */

    PS_MEM_FREE(WUEPS_PID_MMC, pstNvimCfgDPlmnNPlmnInfo);
    return;

}
NAS_MMC_HPLMN_TYPE_ENUM_UINT8 NAS_MMC_JudegeHplmnType(
    NAS_MML_PLMN_ID_STRU               *pstHplmnId
)
{
    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU                      *pstDPlmnNPlmnCfgInfo = VOS_NULL_PTR;
    VOS_UINT32                          i;

    pstDPlmnNPlmnCfgInfo = NAS_MMC_GetDPlmnNPlmnCfgInfo();

    for (i = 0; i < pstDPlmnNPlmnCfgInfo->ucCMCCHplmnNum; i++)
    {
        if (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(&pstDPlmnNPlmnCfgInfo->astCMCCHplmnList[i], pstHplmnId))
        {
            return NAS_MMC_HPLMN_TYPE_CMCC;
        }
    }

    for (i = 0; i < pstDPlmnNPlmnCfgInfo->ucUNICOMHplmnNum; i++)
    {
        if (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(&pstDPlmnNPlmnCfgInfo->astUNICOMHplmnList[i], pstHplmnId))
        {
            return NAS_MMC_HPLMN_TYPE_UNICOM;
        }
    }

    for (i = 0; i < pstDPlmnNPlmnCfgInfo->ucCTHplmnNum; i++)
    {
        if (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(&pstDPlmnNPlmnCfgInfo->astCTHplmnList[i], pstHplmnId))
        {
            return NAS_MMC_HPLMN_TYPE_CT;
        }
    }

    return NAS_MMC_HPLMN_TYPE_BUTT;
}


#if (FEATURE_ON == FEATURE_DSDS)

VOS_VOID NAS_MMC_ReadModemRfShareCfgNvim(VOS_VOID)
{
    NV_MODEM_RF_SHARE_CFG_EX_STRU          stNvimRfShareCfgExInfo;
    VOS_UINT32                             ProfileId;

    PS_MEM_SET(&stNvimRfShareCfgExInfo, 0x00, sizeof(NV_MODEM_RF_SHARE_CFG_EX_STRU));

    /* ��NV��en_NV_Item_USER_CFG_OPLMN_EXTEND_LIST��ʧ�ܣ�ֱ�ӷ��� */
    if (NV_OK != NV_Read(en_NV_MODEM_RF_SHARE_EX_CFG,
                         &stNvimRfShareCfgExInfo, sizeof(NV_MODEM_RF_SHARE_CFG_EX_STRU)))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadModemRfShareCfgNvim():WARNING: read en_NV_MODEM_RF_SHARE_EX_CFG Error");

        return;
    }

    ProfileId = stNvimRfShareCfgExInfo.ulProfileTypeId;
    if(ProfileId > 7)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadModemRfShareCfgNvim():WARNING: get ProfileId Error");
        return;
    }

    if ( (VOS_TRUE  != stNvimRfShareCfgExInfo.astNvModemRfShareCfg[ProfileId].usSupportFlag)
      && (VOS_FALSE != stNvimRfShareCfgExInfo.astNvModemRfShareCfg[ProfileId].usSupportFlag) )
    {
        /* NV�����쳣���� */
        stNvimRfShareCfgExInfo.astNvModemRfShareCfg[ProfileId].usSupportFlag = VOS_FALSE;
    }

    NAS_MML_SetDsdsRfShareFlg(stNvimRfShareCfgExInfo.astNvModemRfShareCfg[ProfileId].usSupportFlag);

    return;
}

VOS_VOID NAS_MMC_ReadDsdsEndSessionDelayNvim(VOS_VOID)
{
    NAS_MMC_NVIM_DSDS_END_SESSION_DELAY_STRU                stNvimDsdsEndSessionDelay;
    NAS_MML_DSDS_END_SESSION_DELAY_STRU                     stDsdsEndSesssionDelay;

    PS_MEM_SET(&stNvimDsdsEndSessionDelay, 0x00, sizeof(NAS_MMC_NVIM_DSDS_END_SESSION_DELAY_STRU));
    PS_MEM_SET(&stDsdsEndSesssionDelay, 0x00, sizeof(NAS_MML_DSDS_END_SESSION_DELAY_STRU));

    /* ��NV��en_NV_Item_DSDS_END_SESSION_DELAY��ʧ�ܣ�ֱ�ӷ��� */
    if (NV_OK != NV_Read(en_NV_Item_DSDS_END_SESSION_DELAY,
                         &stNvimDsdsEndSessionDelay, sizeof(NAS_MMC_NVIM_DSDS_END_SESSION_DELAY_STRU)))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC,
            "NAS_MMC_ReadDsdsEndSessionDelayNvim():WARNING: read en_NV_Item_DSDS_END_SESSION_DELAY Error");

        return;
    }

    if (stNvimDsdsEndSessionDelay.ulCsRegEndSessionDelayTime > NAS_MML_CS_REG_END_SESSION_MAX_DELAY_TIME)
    {
        stDsdsEndSesssionDelay.ulCsRegEndSessionDelayTime = NAS_MML_CS_REG_END_SESSION_MAX_DELAY_TIME;
    }
    else
    {
        stDsdsEndSesssionDelay.ulCsRegEndSessionDelayTime = stNvimDsdsEndSessionDelay.ulCsRegEndSessionDelayTime;
    }

    if (stNvimDsdsEndSessionDelay.ulPsRegEndSessionDelayTime > NAS_MML_PS_REG_END_SESSION_MAX_DELAY_TIME)
    {
        stDsdsEndSesssionDelay.ulPsRegEndSessionDelayTime = NAS_MML_PS_REG_END_SESSION_MAX_DELAY_TIME;
    }
    else
    {
        stDsdsEndSesssionDelay.ulPsRegEndSessionDelayTime = stNvimDsdsEndSessionDelay.ulPsRegEndSessionDelayTime;
    }

    NAS_MML_SetDsdsEndSessionDelay(&stDsdsEndSesssionDelay);

    return;
}

#endif
VOS_VOID  NAS_MMC_ReadUmtsCodecTypeNvim(VOS_VOID)
{
    MN_CALL_UMTS_CODEC_TYPE_STRU        stNvimCodecType;
    NAS_MML_CALL_UMTS_CODEC_TYPE_STRU   stCodecType;

    PS_MEM_SET(&stNvimCodecType, 0x00, sizeof(stNvimCodecType));
    PS_MEM_SET(&stCodecType, 0x00, sizeof(stCodecType));

    if ( NV_OK != NV_Read(en_NV_Item_UMTS_CODEC_TYPE,
                          &stNvimCodecType,
                          sizeof(stNvimCodecType)))
    {
        return;
    }

    stCodecType.ucCnt = stNvimCodecType.ucCnt;
    PS_MEM_CPY(stCodecType.aucUmtsCodec, stNvimCodecType.aucUmtsCodec, sizeof(stCodecType.aucUmtsCodec));

    NAS_MML_CALL_SetCallUmtsCodecType(&stCodecType);
}


VOS_VOID  NAS_MMC_ReadMedCodecTypeNvim(VOS_VOID)
{
    MN_CALL_NIMV_ITEM_CODEC_TYPE_STRU   stNvimCodecType;
    NAS_MML_CALL_GSM_CODEC_TYPE_STRU    stCodecType;

    PS_MEM_SET(&stNvimCodecType, 0x00, sizeof(stNvimCodecType));
    PS_MEM_SET(&stCodecType, 0x00, sizeof(stCodecType));

    if ( NV_OK != NV_Read(en_NV_Item_MED_CODEC_TYPE,
                          &stNvimCodecType,
                          sizeof(stNvimCodecType)))
    {
        return;
    }

    stCodecType.ucCodecTypeNum = stNvimCodecType.ucCodecTypeNum;
    PS_MEM_CPY(stCodecType.aucCodecType, stNvimCodecType.aucCodecType, sizeof(stNvimCodecType.aucCodecType));

    NAS_MML_CALL_SetCallGsmCodecType(&stCodecType);
}


VOS_VOID NAS_MMC_ReadImsVoiceMMEnableNvim(VOS_VOID)
{
    NAS_MMC_IMS_VOICE_MOBILE_MANAGEMENT stImsVoiceMM;
    VOS_UINT32                          ulLength;

    ulLength = 0;

    (VOS_VOID)NV_GetLength(en_NV_Item_IMS_VOICE_MOBILE_MANAGEMENT, &ulLength);
    if (ulLength > sizeof(stImsVoiceMM))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadImsVoiceMMEnableNvim():WARNING: NvGetLength too long");
        return;
    }

    if (NV_OK != NV_Read(en_NV_Item_IMS_VOICE_MOBILE_MANAGEMENT,
                         &stImsVoiceMM, ulLength))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadImsVoiceMMEnableNvim():WARNING: read en_NV_Item_IMS_VOICE_MOBILE_MANAGEMENT Error");
        return;
    }

    if (VOS_TRUE  == stImsVoiceMM.ucImsVoiceInterSysLauEnable)
    {
        NAS_MML_SetImsVoiceInterSysLauEnableFlg(VOS_TRUE);
    }
    else
    {
        NAS_MML_SetImsVoiceInterSysLauEnableFlg(VOS_FALSE);
    }

    if (VOS_TRUE  == stImsVoiceMM.ucImsVoiceMMEnable)
    {
        NAS_MML_SetImsVoiceMMEnableFlg(VOS_TRUE);
    }
    else
    {
        NAS_MML_SetImsVoiceMMEnableFlg(VOS_FALSE);
    }

    return;
}


VOS_VOID NAS_MMC_ReadLcCtrlParaNvim(VOS_VOID)
{
    TAF_NV_LC_CTRL_PARA_STRU            stLcCtrlPara;

    PS_MEM_SET(&stLcCtrlPara, 0, sizeof(stLcCtrlPara));

    /* ��NVʧ�� */
    if (NV_OK != NV_Read(en_NV_Item_LC_Ctrl_PARA,
                         &stLcCtrlPara,
                         sizeof(stLcCtrlPara)))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadLcCtrlParaNvim(): en_NV_Item_LC_Ctrl_PARA error");
        return;
    }

    if (VOS_TRUE == stLcCtrlPara.ucLCEnableFlg)
    {
        NAS_MML_SetLcEnableFlg(VOS_TRUE);
    }
    else
    {
        NAS_MML_SetLcEnableFlg(VOS_FALSE);
    }

    return;
}
VOS_VOID NAS_MMC_ReadIgnoreAuthRejFlgNvim(VOS_VOID)
{
    VOS_UINT32                                              ulLen;
    NAS_MMC_NVIM_IGNORE_AUTH_REJ_CFG_STRU                   stIgnoreAuthRejInfo;

    ulLen = 0;
    PS_MEM_SET(&stIgnoreAuthRejInfo, 0x00, sizeof(NAS_MMC_NVIM_IGNORE_AUTH_REJ_CFG_STRU));
    (VOS_VOID)NV_GetLength(en_NV_Item_Ignore_Auth_Rej_CFG, &ulLen);

    stIgnoreAuthRejInfo.ucIgnoreAuthRejFlg = VOS_FALSE;
    stIgnoreAuthRejInfo.ucMaxAuthRejNo = 0;
    /* ��NV��en_NV_Item_Remove_Auth_Rej_CFG��ʧ�ܣ�ֱ�ӷ��� */
    if (NV_OK != NV_Read(en_NV_Item_Ignore_Auth_Rej_CFG,
                         &stIgnoreAuthRejInfo, ulLen))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadIgnoreAuthRejFlgNvim():WARNING: read en_NV_Item_Remove_Auth_Rej_CFG Error");

        return;
    }

    if (VOS_TRUE == NAS_USIMMAPI_IsTestCard())
    {
        NAS_MML_SetIgnoreAuthRejFlg(VOS_FALSE);
        return;
    }

    /* ��ֵ��ȫ�ֱ��� */
    if ( VOS_TRUE == stIgnoreAuthRejInfo.ucIgnoreAuthRejFlg)
    {
        NAS_MML_SetIgnoreAuthRejFlg(VOS_TRUE);
    }
    else
    {
        NAS_MML_SetIgnoreAuthRejFlg(VOS_FALSE);
    }

    NAS_MML_SetMaxAuthRejNo((stIgnoreAuthRejInfo.ucMaxAuthRejNo));

    return;
}



VOS_VOID NAS_MMC_ReadHighPrioRatHplmnTimerCfgNvim( VOS_VOID  )
{
    NAS_MML_HIGH_PRIO_RAT_HPLMN_TIMER_CFG_STRU       *pstHighRatHplmnTimerCfg = VOS_NULL_PTR;
    NAS_MMC_NVIM_HIGH_PRIO_RAT_HPLMN_TIMER_CFG_STRU   stHighRatHplmnTimerCfg;

    PS_MEM_SET(&stHighRatHplmnTimerCfg, 0x00, sizeof(stHighRatHplmnTimerCfg));

    pstHighRatHplmnTimerCfg = NAS_MML_GetHighPrioRatHplmnTimerCfg();

    if (NV_OK != NV_Read (en_NV_Item_HIGH_PRIO_RAT_HPLMN_TIMER_CFG, &stHighRatHplmnTimerCfg, sizeof(stHighRatHplmnTimerCfg)))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadHighPrioRatHplmnTimerCfgNvim:Read NV Failed");
        return;
    }

    pstHighRatHplmnTimerCfg->ucActiveFLg = VOS_FALSE;

    if (VOS_TRUE == stHighRatHplmnTimerCfg.ucActiveFLg)
    {
        pstHighRatHplmnTimerCfg->ucActiveFLg                = VOS_TRUE;
        pstHighRatHplmnTimerCfg->ucTdThreshold              = stHighRatHplmnTimerCfg.ucTdThreshold;
        pstHighRatHplmnTimerCfg->ulFirstSearchTimeLen       = stHighRatHplmnTimerCfg.ulFirstSearchTimeLen;
        pstHighRatHplmnTimerCfg->ulNonFirstSearchTimeLen    = stHighRatHplmnTimerCfg.ulNonFirstSearchTimeLen;
        pstHighRatHplmnTimerCfg->ulFirstSearchTimeCount     = stHighRatHplmnTimerCfg.ulFirstSearchTimeCount;
        pstHighRatHplmnTimerCfg->ulRetrySearchTimeLen       = stHighRatHplmnTimerCfg.ulRetrySearchTimeLen;
    }

    return;
}

#if  (FEATURE_ON == FEATURE_LTE)

VOS_VOID NAS_MMC_ReadUltraFlashCsfbSupportFlgNvim(VOS_VOID)
{
    NAS_MMC_NVIM_ULTRA_FLASH_CSFB_SUPPORT_FLG_STRU          stUltraFlashCsfbSupport;

    PS_MEM_SET(&stUltraFlashCsfbSupport, 0x00, sizeof(NAS_MMC_NVIM_ULTRA_FLASH_CSFB_SUPPORT_FLG_STRU));

    /* ��NV��en_NV_Item_Ultra_Flash_Csfb_Support_Flg��ʧ�ܣ�ֱ�ӷ��� */
    if (NV_OK != NV_Read(en_NV_Item_Ultra_Flash_Csfb_Support_Flg,
                         &stUltraFlashCsfbSupport,
                         sizeof(NAS_MMC_NVIM_ULTRA_FLASH_CSFB_SUPPORT_FLG_STRU)))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadIgnoreAuthRejFlgNvim():WARNING: read en_NV_Item_Remove_Auth_Rej_CFG Error");

        return;
    }

    /* ��ֵ��ȫ�ֱ��� */
    if ( VOS_TRUE == stUltraFlashCsfbSupport.ucUltraFlashCsfbSupportFLg)
    {
        NAS_MML_SetUltraFlashCsfbSupportFlg(VOS_TRUE);
    }
    else
    {
        NAS_MML_SetUltraFlashCsfbSupportFlg(VOS_FALSE);
    }

    return;
}


VOS_VOID NAS_MMC_ReadSrvccSupportFlgNvim(VOS_VOID)
{
    IMS_NV_IMS_CAP_STRU                 stImsCap;
    VOS_UINT8                           ucSrvccFlg;
    NAS_MML_MS_CAPACILITY_INFO_STRU    *pstMsCapability = VOS_NULL_PTR;

    pstMsCapability = NAS_MML_GetMsCapability();

    PS_MEM_SET(&stImsCap, 0x00, sizeof(IMS_NV_IMS_CAP_STRU));

    /* ��NV��EN_NV_ID_IMS_CAPABILITY��ʧ�ܣ�ֱ�ӷ��� */
    if (NV_OK != NV_Read(EN_NV_ID_IMS_CAPABILITY,
                         &stImsCap,
                         sizeof(IMS_NV_IMS_CAP_STRU)))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadSrvccSupportFlgNvim():WARNING: read EN_NV_ID_IMS_CAPABILITY Error");

        return;
    }

    /* active/hold/alerting/pre alterting��һ��״̬֧��SRVCC���͸����籨֧��SRVCC */
    ucSrvccFlg  = (stImsCap.ucSrvccOnImsSupportFlag || stImsCap.ucSrvccMidCallOnImsSupportFlag
                || stImsCap.ucSrvccAlertingOnImsSupportFlag || stImsCap.ucSrvccPreAlertingOnImsSupportFlag);

    /* ��ֵ��ȫ�ֱ�����aucNetworkCapability��srvcc��bitλ���ڵ�λ�òο�3GPP 24008 */
    if ( VOS_TRUE == ucSrvccFlg)
    {
        NAS_MML_SetSupportSrvccFlg(VOS_TRUE);
        pstMsCapability->stMsNetworkCapability.aucNetworkCapability[2] |= 0x08;
    }
    else
    {
        NAS_MML_SetSupportSrvccFlg(VOS_FALSE);
        pstMsCapability->stMsNetworkCapability.aucNetworkCapability[2] &= 0xf7;
    }

    return;
}


#endif
VOS_VOID NAS_MMC_Read3GPP2UplmnNotPrefFlgNvim(VOS_VOID)
{
    NAS_MMC_NVIM_3GPP2_UPLMN_NOT_PREF_STRU                  st3GPP2UplmnNotPref;

    PS_MEM_SET(&st3GPP2UplmnNotPref, 0x00, sizeof(NAS_MMC_NVIM_3GPP2_UPLMN_NOT_PREF_STRU));

    /* ��NV��en_NV_Item_3GPP2_Uplmn_Not_Pref_Flg��ʧ�ܣ�ֱ�ӷ��� */
    if (NV_OK != NV_Read(en_NV_Item_3GPP2_Uplmn_Not_Pref_Flg,
                         &st3GPP2UplmnNotPref,
                         sizeof(NAS_MMC_NVIM_3GPP2_UPLMN_NOT_PREF_STRU)))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_Read3GPP2UplmnNotPrefFlgNvim():WARNING: read en_NV_Item_3GPP2_Uplmn_Not_Pref_Flg Error");

        return;
    }

    /* ��ֵ��ȫ�ֱ��� */
    if (VOS_TRUE == st3GPP2UplmnNotPref.uc3GPP2UplmnNotPrefFlg)
    {
        NAS_MML_Set3GPP2UplmnNotPrefFlg(VOS_TRUE);
    }
    else
    {
        NAS_MML_Set3GPP2UplmnNotPrefFlg(VOS_FALSE);
    }

    return;
}


VOS_VOID NAS_MMC_ReadDamCfgNvim(VOS_VOID)
{
    PS_NV_DAM_CONFIG_PARA_STRU                  stDamCfgInfo;
    VOS_UINT32                                  ulLength;
    VOS_UINT8                                   i;
    NAS_MML_DAM_PLMN_INFO_CONFIG_STRU          *pstDamPlmnInfoCfg = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU                        stGUNasPlmn;
    MMC_LMM_PLMN_ID_STRU                        stLMMPlmn;

    PS_MEM_SET(&stDamCfgInfo, 0x00, sizeof(stDamCfgInfo));
    PS_MEM_SET(&stGUNasPlmn, 0x00, sizeof(stGUNasPlmn));
    PS_MEM_SET(&stLMMPlmn, 0x00, sizeof(stLMMPlmn));
    ulLength              = 0;
    pstDamPlmnInfoCfg     = NAS_MML_GetDamPlmnInfoCfg();

    /* �Ȼ�ȡNV�ĳ��� */
    (VOS_VOID)NV_GetLength(EN_NV_ID_DAM_CONFIG_PARA, &ulLength);

    if (ulLength > sizeof(PS_NV_DAM_CONFIG_PARA_STRU))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadDamCfgNvim(): nv length Error");
        return;
    }

    /* ��NVʧ�� */
    if (NV_OK != NV_Read(EN_NV_ID_DAM_CONFIG_PARA,
                         &stDamCfgInfo, ulLength))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadDamCfgNvim(): read nv error");
        return;
    }

    /* ��ȡenable lte�Ƿ���Ҫ�������� */
    if (VOS_TRUE == stDamCfgInfo.ucEnableLteTrigPlmnSearchFlag)
    {
        NAS_MML_SetEnableLteTrigPlmnSearchFlag(stDamCfgInfo.ucEnableLteTrigPlmnSearchFlag);
    }

    if (stDamCfgInfo.stDamConfigPlmnPara.stDamPlmnList.ulPlmnNum > NAS_MML_SUPPORT_DAM_MAX_PLMN_NUM)
    {
        stDamCfgInfo.stDamConfigPlmnPara.stDamPlmnList.ulPlmnNum = NAS_MML_SUPPORT_DAM_MAX_PLMN_NUM;
    }

    if (stDamCfgInfo.stDamConfigPlmnPara.stImsiPlmnList.ulPlmnNum  > NAS_MML_SUPPORT_DAM_MAX_PLMN_NUM)
    {
        stDamCfgInfo.stDamConfigPlmnPara.stImsiPlmnList.ulPlmnNum = NAS_MML_SUPPORT_DAM_MAX_PLMN_NUM;
    }

    pstDamPlmnInfoCfg->stDamPlmnList.ucPlmnNum = (VOS_UINT8)stDamCfgInfo.stDamConfigPlmnPara.stDamPlmnList.ulPlmnNum;

    for (i = 0; i < stDamCfgInfo.stDamConfigPlmnPara.stDamPlmnList.ulPlmnNum; i++)
    {
        stLMMPlmn.aucPlmnId[0] = stDamCfgInfo.stDamConfigPlmnPara.stDamPlmnList.astPlmnId[i].aucPlmnId[0];
        stLMMPlmn.aucPlmnId[1] = stDamCfgInfo.stDamConfigPlmnPara.stDamPlmnList.astPlmnId[i].aucPlmnId[1];
        stLMMPlmn.aucPlmnId[2] = stDamCfgInfo.stDamConfigPlmnPara.stDamPlmnList.astPlmnId[i].aucPlmnId[2];

        NAS_MMC_ConvertLmmPlmnToGUNasFormat(&stLMMPlmn, &stGUNasPlmn);

        if (VOS_TRUE == NAS_MML_IsPlmnIdValid(&stGUNasPlmn))
        {
            pstDamPlmnInfoCfg->stDamPlmnList.astPlmnId[i].ulMcc = stGUNasPlmn.ulMcc;
            pstDamPlmnInfoCfg->stDamPlmnList.astPlmnId[i].ulMnc = stGUNasPlmn.ulMnc;
        }
    }

    pstDamPlmnInfoCfg->stImsiPlmnList.ucPlmnNum = (VOS_UINT8)stDamCfgInfo.stDamConfigPlmnPara.stImsiPlmnList.ulPlmnNum;

    for (i = 0; i < stDamCfgInfo.stDamConfigPlmnPara.stImsiPlmnList.ulPlmnNum; i++)
    {
        stLMMPlmn.aucPlmnId[0] = stDamCfgInfo.stDamConfigPlmnPara.stImsiPlmnList.astPlmnId[i].aucPlmnId[0];
        stLMMPlmn.aucPlmnId[1] = stDamCfgInfo.stDamConfigPlmnPara.stImsiPlmnList.astPlmnId[i].aucPlmnId[1];
        stLMMPlmn.aucPlmnId[2] = stDamCfgInfo.stDamConfigPlmnPara.stImsiPlmnList.astPlmnId[i].aucPlmnId[2];

        NAS_MMC_ConvertLmmPlmnToGUNasFormat(&stLMMPlmn, &stGUNasPlmn);

        if (VOS_TRUE == NAS_MML_IsPlmnIdValid(&stGUNasPlmn))
        {
            pstDamPlmnInfoCfg->stImsiPlmnList.astPlmnId[i].ulMcc = stGUNasPlmn.ulMcc;
            pstDamPlmnInfoCfg->stImsiPlmnList.astPlmnId[i].ulMnc = stGUNasPlmn.ulMnc;
        }
    }

    /* ��ȡ��DAM����disable lte���Ƿ���Ҫ��DAM��������ֹ���뼼�������б��� */
    if (VOS_TRUE == stDamCfgInfo.ucAddDamPlmnInDisablePlmnWithRatListFlag)
    {
        NAS_MML_SetAddDamPlmnInDisablePlmnWithRatListFlag(VOS_TRUE);
    }

    return;
}





VOS_VOID NAS_MMC_ReadSyscfgTriPlmnSrchCfgNvim(VOS_VOID)
{
    NAS_MMC_NVIM_SYSCFG_TRIGGER_PLMN_SEARCH_CFG_STRU        stSyscfgTriPlmnSrchCfg;
    VOS_UINT32                                              ulLength;

    ulLength = 0;
    PS_MEM_SET(&stSyscfgTriPlmnSrchCfg, 0x00, sizeof(NAS_MMC_NVIM_SYSCFG_TRIGGER_PLMN_SEARCH_CFG_STRU));

    /* �Ȼ�ȡNV�ĳ��� */
    (VOS_VOID)NV_GetLength(en_NV_Item_Syscfg_Trigger_Plmn_Search_Cfg, &ulLength);

    if (ulLength > sizeof(NAS_MMC_NVIM_SYSCFG_TRIGGER_PLMN_SEARCH_CFG_STRU))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadSyscfgTriPlmnSrchCfgNvim(): en_NV_Item_Syscfg_Trigger_Plmn_Search_Cfg length Error");
        return;
    }

    /* ��NVʧ�� */
    if (NV_OK != NV_Read(en_NV_Item_Syscfg_Trigger_Plmn_Search_Cfg,
                         &stSyscfgTriPlmnSrchCfg, ulLength))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadSyscfgTriPlmnSrchCfgNvim(): en_NV_Item_Syscfg_Trigger_Plmn_Search_Cfg error");
        return;
    }

    if (VOS_TRUE == stSyscfgTriPlmnSrchCfg.ucHighPrioRatPlmnSrchFlg)
    {
        NAS_MML_SetSyscfgTriHighRatSrchFlg(VOS_TRUE);
    }
    else
    {
        NAS_MML_SetSyscfgTriHighRatSrchFlg(VOS_FALSE);
    }

    return;
}


VOS_VOID  NAS_MMC_ReadChangeNwCauseCfgNvim(VOS_VOID)
{
    NAS_MMC_NVIM_CHANGE_NW_CAUSE_CFG_STRU                   stNvConfigCause;
    VOS_UINT32                                              ulRslt;

    PS_MEM_SET(&stNvConfigCause, 0x00, sizeof(NAS_MMC_NVIM_CHANGE_NW_CAUSE_CFG_STRU));

    ulRslt = NV_Read(en_NV_Item_ChangeNWCause_CFG,
                     (VOS_VOID *)&stNvConfigCause,
                     sizeof(NAS_MMC_NVIM_CHANGE_NW_CAUSE_CFG_STRU));

    if (NV_OK == ulRslt)
    {
        if (NAS_MMC_NVIM_MAX_CAUSE_NUM < stNvConfigCause.ucCsRegCauseNum)
        {
            NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadChangeNwCauseCfgNvim(): config NV para ucCsRegCauseNum err.");
            return;
        }

        if (NAS_MMC_NVIM_MAX_CAUSE_NUM < stNvConfigCause.ucPsRegCauseNum)
        {
            NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadChangeNwCauseCfgNvim(): config NV para ucPsRegCauseNum err.");
            return;
        }

        if (NAS_MMC_NVIM_MAX_CAUSE_NUM < stNvConfigCause.ucDetachCauseNum)
        {
            NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadChangeNwCauseCfgNvim(): config NV para ucDetachCauseNum err.");
            return;
        }

        if (NAS_MMC_NVIM_MAX_CAUSE_NUM < stNvConfigCause.ucPsSerRejCauseNum)
        {
            NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadChangeNwCauseCfgNvim(): config NV para ucPsSerRejCauseNum err.");
            return;
        }

        if (NAS_MMC_NVIM_MAX_CAUSE_NUM < stNvConfigCause.ucMmAbortCauseNum)
        {
            NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadChangeNwCauseCfgNvim(): config NV para ucMmAbortCauseNum err.");
            return;
        }

        if (NAS_MMC_NVIM_MAX_CAUSE_NUM < stNvConfigCause.ucCmSerRejCauseNum)
        {
            NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadChangeNwCauseCfgNvim(): config NV para ucCmSerRejCauseNum err.");
            return;
        }
    }
    else
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadChangeNwCauseCfgNvim(): config NV err.");

        PS_MEM_SET(&stNvConfigCause, 0x00, sizeof(NAS_MMC_NVIM_CHANGE_NW_CAUSE_CFG_STRU));
    }

    /* ����NV������Ϣ */
    NAS_MML_SetChangeNWCauseCfg(&stNvConfigCause);
}
VOS_VOID NAS_MMC_ReadRelPsSignalConCfgNvim(VOS_VOID)
{
    NAS_MMC_NVIM_REL_PS_SIGNAL_CON_CFG_STRU                 stRelPsSigConCfg;

    PS_MEM_SET(&stRelPsSigConCfg, 0x00, sizeof(NAS_MMC_NVIM_REL_PS_SIGNAL_CON_CFG_STRU));

    if(NV_OK != NV_Read(en_NV_Item_REL_PS_SIGNAL_CON_CFG,
                        (VOS_VOID *)&stRelPsSigConCfg,
                        sizeof(NAS_MMC_NVIM_REL_PS_SIGNAL_CON_CFG_STRU)))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC,
                     "NAS_MMC_ReadRelPsSignalConCfgNvim():en_NV_Item_REL_PS_SIGNAL_CON_CFG Error");
        return;
    }

    if(VOS_TRUE == stRelPsSigConCfg.ucRelPsSignalConFlg)
    {
        NAS_MML_SetRelPsSigConFlg(VOS_TRUE);
        NAS_MML_SetRelPsSigConCfg_T3340TimerLen(stRelPsSigConCfg.ulT3340Len);;
    }

    if (VOS_FALSE == stRelPsSigConCfg.ucPdpExistNotStartT3340Flag)
    {
        NAS_MML_SetPdpExistNotStartT3340Flag(stRelPsSigConCfg.ucPdpExistNotStartT3340Flag);
    }


}

#if  (FEATURE_ON == FEATURE_LTE)
VOS_VOID NAS_MMC_ReadLteRejCause14CfgNvim(VOS_VOID)
{
    NAS_MMC_NVIM_LTE_REJ_CAUSE_14_CFG_STRU    stLteRejCause14Cfg;

    PS_MEM_SET(&stLteRejCause14Cfg, 0x00, sizeof(NAS_MMC_NVIM_LTE_REJ_CAUSE_14_CFG_STRU));

    if (NV_OK != NV_Read(en_NV_Item_LTE_REJ_CAUSE_14_CFG,
                         (VOS_VOID *)&stLteRejCause14Cfg,
                         sizeof(NAS_MMC_NVIM_LTE_REJ_CAUSE_14_CFG_STRU)))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC,
                     "NAS_MMC_ReadLteRejCause14CfgNvim():en_NV_Item_LTE_REJ_CAUSE_14_CFG Error");
        return;
    }

    /* һ���Բ��Կ�������δ���� */
    if (   (VOS_TRUE  == NAS_USIMMAPI_IsTestCard())
        || (VOS_FALSE == stLteRejCause14Cfg.ucLteRejCause14Flg))
    {
        NAS_MML_SetLteRejCause14Flg(VOS_FALSE);
        return;
    }

    NAS_MML_SetLteRejCause14Flg(VOS_TRUE);
    NAS_MML_SetLteRejCause14EnableLteTimerLen(stLteRejCause14Cfg.usLteRejCause14EnableLteTimerLen * NAS_MML_SIXTY_SECOND
                                 * NAS_MML_ONE_THOUSAND_MILLISECOND);
}
#endif

#if  (FEATURE_ON == FEATURE_IMS)
VOS_VOID NAS_MMC_ReadImsRatSupportNvim(VOS_VOID)
{
    VOS_UINT32                                  ulLength;
    IMSA_NV_IMS_RAT_SUPPORT_STRU                stImsSupport;

    /* IMS����ֻ����FEATURE_IMS��ʱ�����п�������Ϊ���� */
    /* �Ȼ�ȡNV�ĳ��� */
    ulLength = 0;
    NV_GetLength(EN_NV_ID_IMS_RAT_SUPPORT, &ulLength);

    if (ulLength > sizeof(IMSA_NV_IMS_RAT_SUPPORT_STRU))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadImsRatSupportNvim():WARNING: EN_NV_ID_IMS_RAT_SUPPORT length Error");

        return;
    }

    /* ��NV��EN_NV_ID_IMS_RAT_SUPPORT��ʧ�ܣ�ֱ�ӷ��� */
    if (NV_OK != NV_Read(EN_NV_ID_IMS_RAT_SUPPORT,
                         &stImsSupport, ulLength))
    {

        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadImsRatSupportNvim():WARNING: read EN_NV_ID_IMS_RAT_SUPPORT Error");

        return;
    }

    /* ��ֵ��ȫ�ֱ����� */
    NAS_MML_SetLteImsSupportFlg(stImsSupport.ucLteImsSupportFlag);

    return;
}


VOS_VOID NAS_MMC_ReadImsCapNvim(VOS_VOID)
{
    VOS_UINT32                                  ulLength;
    IMS_NV_IMS_CAP_STRU                         stImsCapa;

    /* �Ȼ�ȡNV�ĳ��� */
    ulLength = 0;
    NV_GetLength(EN_NV_ID_IMS_CAPABILITY, &ulLength);

    if (ulLength > sizeof(IMS_NV_IMS_CAP_STRU))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadImsCapNvim():WARNING: EN_NV_ID_IMS_CAPABILITY length Error");

        return;
    }

    /* ��NV��EN_NV_ID_IMS_CAPABILITY��ʧ�ܣ�ֱ�ӷ��� */
    if (NV_OK != NV_Read(EN_NV_ID_IMS_CAPABILITY,
                         &stImsCapa, ulLength))
    {

        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadImsCapNvim():WARNING: read EN_NV_ID_IMS_CAPABILITY Error");

        return;
    }

    /* ��ֵ��ȫ�ֱ����� */
    NAS_MML_SetVoiceCallOnImsSupportFlag(stImsCapa.ucVoiceCallOnImsSupportFlag);
    NAS_MML_SetVideoCallOnImsSupportFlag(stImsCapa.ucVideoCallOnImsSupportFlag);
    NAS_MML_SetSmsOnImsSupportFlag(stImsCapa.ucSmsOnImsSupportFlag);

    return;
}
VOS_VOID NAS_MMC_ReadUssdOnImsNvim(VOS_VOID)
{
    VOS_UINT32                                  ulLength;
    TAF_NV_IMS_USSD_SUPPORT_STRU                stUssdFlg;

    /* �Ȼ�ȡNV�ĳ��� */
    ulLength = 0;
    NV_GetLength(en_NV_Item_IMS_USSD_SUPPORT_FLG, &ulLength);

    if (ulLength > sizeof(TAF_NV_IMS_USSD_SUPPORT_STRU))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC,
                      "NAS_MMC_ReadUssdOnImsNvim():WARNING: en_NV_Item_IMS_USSD_SUPPORT_FLG length Error");

        return;
    }

    /* ��NV��en_NV_Item_IMS_USSD_SUPPORT_FLG��ʧ�ܣ�ֱ�ӷ��� */
    if (NV_OK != NV_Read(en_NV_Item_IMS_USSD_SUPPORT_FLG,
                         &stUssdFlg, ulLength))
    {

        NAS_ERROR_LOG(WUEPS_PID_MMC,
                      "NAS_MMC_ReadUssdOnImsNvim():WARNING: read en_NV_Item_IMS_USSD_SUPPORT_FLG Error");

        return;
    }

    /* NV������USSD֧��������Ϣ */
    NAS_MML_SetUssdOnImsSupportFlag(stUssdFlg.ucUssdOnImsSupportFlag);

    return;
}

#endif
VOS_VOID NAS_MMC_ReadDsdsActiveModemModeNvim(VOS_VOID)
{
    TAF_NV_DSDS_ACTIVE_MODEM_MODE_STRU  stMode;

    PS_MEM_SET(&stMode, 0x00, sizeof(TAF_NV_DSDS_ACTIVE_MODEM_MODE_STRU));

    if (NV_OK != NV_Read(en_NV_Item_DSDS_Active_Modem_Mode,
                        (VOS_VOID *)&stMode,
                        sizeof(TAF_NV_DSDS_ACTIVE_MODEM_MODE_STRU)))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC,
                     "NAS_MMC_ReadDsdsActiveModemModeNvim():en_NV_Item_DSDS_Active_Modem_Mode Error");
        return;
    }

    if (TAF_NV_ACTIVE_MULTI_MODEM == stMode.enActiveModem)
    {
        NAS_MML_SetDsdsMultiModemModeFlg(VOS_TRUE);

        return;
    }

    NAS_MML_SetDsdsMultiModemModeFlg(VOS_FALSE);

    return;
}




VOS_VOID NAS_MMC_ReadCsmoSupportedCfgNvim(VOS_VOID)
{
    NAS_MMC_NVIM_CSMO_SUPPORTED_CFG_STRU  stNvimCfgCsmoInfo;

    PS_MEM_SET(&stNvimCfgCsmoInfo, 0x00, sizeof(stNvimCfgCsmoInfo));

    if (NV_OK != NV_Read(en_NV_Item_Csmo_Supported_Cfg_Info,
                        (VOS_VOID *)&stNvimCfgCsmoInfo,
                        sizeof(NAS_MMC_NVIM_CSMO_SUPPORTED_CFG_STRU)))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC,
                     "NAS_MMC_ReadCsmoSupportedCfgNvim():en_NV_Item_Csmo_Supported_Cfg_Info Error");
        return;
    }

    if (VOS_TRUE == stNvimCfgCsmoInfo.ucCsmoSupportedFlg)
    {
        NAS_MML_SetCsmoSupportedFlg(VOS_TRUE);

        return;
    }

    NAS_MML_SetCsmoSupportedFlg(VOS_FALSE);

    return;
}


VOS_VOID NAS_MMC_ReadT3212TimerCfgNvim(VOS_VOID)
{
    NAS_MML_T3212_TIMER_INFO_CONFIG_STRU                   *pstT3212Info        = VOS_NULL_PTR;
    NAS_MMC_NVIM_T3212_TIMER_CFG_STRU                       stNvimCfgT3212Info;

    pstT3212Info = NAS_MML_GetT3212TimerInfo();
    PS_MEM_SET(&stNvimCfgT3212Info, 0x00, sizeof(stNvimCfgT3212Info));

    if (NV_OK != NV_Read(en_NV_Item_T3212_Timer_Cfg_Info,
                        (VOS_VOID *)&stNvimCfgT3212Info,
                        sizeof(NAS_MMC_NVIM_T3212_TIMER_CFG_STRU)))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC,
                     "NAS_MMC_ReadT3212TimerCfgNvim():en_NV_Item_Csmo_Supported_Cfg_Info Error");
        return;
    }

    pstT3212Info->ulT3212NvActiveFlg = VOS_FALSE;

    /* ��NV���õ��쳣ֵ���м��ݴ���, ����T3212ʱ��Ϊ0�����޸�ΪĬ��6���� */
    if (0 == stNvimCfgT3212Info.ulT3212Phase1TimeLen)
    {
        stNvimCfgT3212Info.ulT3212Phase1TimeLen = NAS_MML_T3212_DEFAULT_UNIT_LEN;
    }

    /* ��NV���õ��쳣ֵ���м��ݴ���, ����T3212ʱ��Ϊ0�����޸�ΪĬ��6���� */
    if (0 == stNvimCfgT3212Info.ulT3212Phase2TimeLen)
    {
        stNvimCfgT3212Info.ulT3212Phase2TimeLen = NAS_MML_T3212_DEFAULT_UNIT_LEN;
    }

    /* NV���õ�T3212���ʱ��������18Сʱ */
    if (stNvimCfgT3212Info.ulT3212Phase1TimeLen >= NAS_MML_T3212_CFG_MAX_VALUE)
    {
        stNvimCfgT3212Info.ulT3212Phase1TimeLen = NAS_MML_T3212_CFG_MAX_VALUE;
    }

    /* NV���õ�T3212���ʱ��������18Сʱ */
    if (stNvimCfgT3212Info.ulT3212Phase2TimeLen >= NAS_MML_T3212_CFG_MAX_VALUE)
    {
        stNvimCfgT3212Info.ulT3212Phase2TimeLen = NAS_MML_T3212_CFG_MAX_VALUE;
    }

    if (VOS_TRUE == stNvimCfgT3212Info.ulNvActiveFlg)
    {
        pstT3212Info->ulT3212NvActiveFlg = VOS_TRUE;
    }

    pstT3212Info->ulT3212StartSceneCtrlBitMask  = stNvimCfgT3212Info.ulT3212StartSceneCtrlBitMask;
    pstT3212Info->ulT3212Phase1TimeLen          = stNvimCfgT3212Info.ulT3212Phase1TimeLen * NAS_MML_ONE_THOUSAND_MILLISECOND;
    pstT3212Info->ulT3212Phase1Count            = stNvimCfgT3212Info.ulT3212Phase1Count;
    pstT3212Info->ulT3212Phase2TimeLen          = stNvimCfgT3212Info.ulT3212Phase2TimeLen * NAS_MML_ONE_THOUSAND_MILLISECOND;
    pstT3212Info->ulT3212Phase2Count            = stNvimCfgT3212Info.ulT3212Phase2Count;

    return;
}



VOS_VOID NAS_MMC_ReadRoamDisplayCfgNvim(VOS_VOID)
{
    NAS_MMC_NVIM_ROAM_DISPLAY_CFG_STRU          stNvimRoamDisplayCfg;;

    PS_MEM_SET(&stNvimRoamDisplayCfg, 0x00, sizeof(stNvimRoamDisplayCfg));

    if (NV_OK != NV_Read(en_NV_Item_Roam_Display_Cfg,
                        (VOS_VOID *)&stNvimRoamDisplayCfg,
                        sizeof(NAS_MMC_NVIM_ROAM_DISPLAY_CFG_STRU)))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC,
                     "NAS_MMC_ReadRoamDisplayCfgNvim():en_NV_Item_Roam_Display_Cfg Error");
        return;
    }

    if (VOS_TRUE == stNvimRoamDisplayCfg.ucHplmnInEplmnDisplayHomeFlg)
    {
        NAS_MML_SetHplmnInEplmnDisplayHomeFlg(VOS_TRUE);

        return;
    }

    NAS_MML_SetHplmnInEplmnDisplayHomeFlg(VOS_FALSE);

    return;
}

#if (FEATURE_ON == FEATURE_LTE)

VOS_VOID NAS_MMC_ReadLteOos2GPrefPlmnSelCfgNvim(VOS_VOID)
{
    VOS_UINT32                                              i;
    NAS_MML_SIM_FORMAT_PLMN_ID                              stSimPlmn;
    NAS_MML_PLMN_ID_STRU                                    stPlmn;
    NAS_MMC_NVIM_LTE_OOS_2G_PREF_PLMN_SEL_CFG_STRU          stLteOosPlmnSelCfgNvim;
    NAS_MML_LTE_OOS_2G_PREF_PLMN_SEL_CFG_STRU              *pstLteOosPlmnSelCfg = VOS_NULL_PTR;

    PS_MEM_SET(&stLteOosPlmnSelCfgNvim, 0x00, sizeof(NAS_MMC_NVIM_LTE_OOS_2G_PREF_PLMN_SEL_CFG_STRU));
    PS_MEM_SET(&stSimPlmn, 0x00, sizeof(stSimPlmn));
    PS_MEM_SET(&stPlmn, 0x00, sizeof(stPlmn));

    pstLteOosPlmnSelCfg = NAS_MML_GetLteOos2GPrefPlmnSelCfg();
    pstLteOosPlmnSelCfg->ucImsiListNum  = 0;

    if (NV_OK != NV_Read(en_NV_Item_LTE_OOS_2G_PREF_PLMN_SEL_CFG, &stLteOosPlmnSelCfgNvim, sizeof(NAS_MMC_NVIM_LTE_OOS_2G_PREF_PLMN_SEL_CFG_STRU)))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadLteOos2GPrefPlmnSelCfgNvim:Read NV Failed");
        return;
    }

    /* ��������,�������ֵ�������ֵ���� */
    if (NAS_NVIM_LTE_OOS_2G_PREF_PLMN_SEL_MAX_IMSI_LIST_NUM < stLteOosPlmnSelCfgNvim.ucImsiListNum)
    {
        stLteOosPlmnSelCfgNvim.ucImsiListNum = NAS_NVIM_LTE_OOS_2G_PREF_PLMN_SEL_MAX_IMSI_LIST_NUM;
    }

    /* ��USIM�б����PLMN��Ϣת��Ϊ�ڴ��е���Ϣ */
    for ( i = 0; i < stLteOosPlmnSelCfgNvim.ucImsiListNum; i++ )
    {
        PS_MEM_CPY(stSimPlmn.aucSimPlmn, stLteOosPlmnSelCfgNvim.astImsiList[i].aucSimPlmn, NAS_MML_SIM_PLMN_ID_LEN);
        NAS_MMC_ConvertSimPlmnToNasPLMN(&stSimPlmn, &stPlmn);

        if (VOS_TRUE == NAS_MML_IsPlmnIdValid(&stPlmn))
        {
            pstLteOosPlmnSelCfg->astImsiList[pstLteOosPlmnSelCfg->ucImsiListNum].ulMcc = stPlmn.ulMcc;
            pstLteOosPlmnSelCfg->astImsiList[pstLteOosPlmnSelCfg->ucImsiListNum].ulMnc = stPlmn.ulMnc;
            pstLteOosPlmnSelCfg->ucImsiListNum++;
        }
    }
}
#endif


VOS_VOID NAS_MMC_ReadPsRegFailMaxTimesTrigLauOnceFlgNvim(VOS_VOID)
{
    NAS_NVIM_PS_REG_FAIL_MAX_TIMES_TRIG_LAU_ONCE_CFG_STRU stPsRegFailMaxTimesTrigLauOnce;
    VOS_UINT32                                            ulLength;

    ulLength = 0;
    NV_GetLength(en_NV_Item_PS_REG_FAIL_MAX_TIMES_TRIG_LAU_ONCE_CFG, &ulLength);

    if (ulLength > sizeof(NAS_NVIM_PS_REG_FAIL_MAX_TIMES_TRIG_LAU_ONCE_CFG_STRU))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadPsRegFailMaxTimesTrigLauOnceFlgNvim():WARNING: en_NV_Item_PS_REG_FAIL_MAX_TIMES_TRIG_LAU_ONCE_CFG length Error");

        return;
    }

    PS_MEM_SET(&stPsRegFailMaxTimesTrigLauOnce, 0x00, sizeof(NAS_NVIM_PS_REG_FAIL_MAX_TIMES_TRIG_LAU_ONCE_CFG_STRU));

    if (NV_OK != NV_Read(en_NV_Item_PS_REG_FAIL_MAX_TIMES_TRIG_LAU_ONCE_CFG,
                        (VOS_VOID *)&stPsRegFailMaxTimesTrigLauOnce,
                        sizeof(NAS_NVIM_PS_REG_FAIL_MAX_TIMES_TRIG_LAU_ONCE_CFG_STRU)))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC,
                  "NAS_MMC_ReadPsRegFailMaxTimesTrigLauOnceFlgNvim():en_NV_Item_PS_REG_FAIL_MAX_TIMES_TRIG_LAU_ONCE_CFG Error");
    }

    if (VOS_TRUE == stPsRegFailMaxTimesTrigLauOnce.ucPsRegFailMaxTimesTrigLauOnceFlg)
    {
        NAS_MML_SetPsRegFailMaxTimesTrigLauOnceFlg(VOS_TRUE);

        return;
    }

    NAS_MML_SetPsRegFailMaxTimesTrigLauOnceFlg(VOS_FALSE);

    return;
}


VOS_VOID NAS_MMC_ReadKeepSrchHplmnEvenRejByCause13Nvim(VOS_VOID)
{
    NAS_NVIM_KEEP_SRCH_HPLMN_EVEN_REJ_BY_CAUSE_13_CFG_STRU  stKeepSrchHplmnEvenRejByCause13;
    VOS_UINT32                                              ulLength;

    ulLength = 0;
    NV_GetLength(en_NV_Item_KEEP_SRCH_HPLMN_EVEN_REJ_BY_CAUSE_13_CFG, &ulLength);

    if (ulLength > sizeof(NAS_NVIM_KEEP_SRCH_HPLMN_EVEN_REJ_BY_CAUSE_13_CFG_STRU))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadKeepSrchHplmnEvenRejByCause13Nvim():WARNING: en_NV_Item_KEEP_SRCH_HPLMN_EVEN_REJ_BY_CAUSE_13_CFG length Error");

        return;
    }

    PS_MEM_SET(&stKeepSrchHplmnEvenRejByCause13, 0x00, sizeof(stKeepSrchHplmnEvenRejByCause13));

    if (NV_OK != NV_Read(en_NV_Item_KEEP_SRCH_HPLMN_EVEN_REJ_BY_CAUSE_13_CFG,
                        (VOS_VOID *)&stKeepSrchHplmnEvenRejByCause13,
                        sizeof(NAS_NVIM_KEEP_SRCH_HPLMN_EVEN_REJ_BY_CAUSE_13_CFG_STRU)))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC,
                  "NAS_MMC_ReadKeepSrchHplmnEvenRejByCause13Nvim():en_NV_Item_KEEP_SRCH_HPLMN_EVEN_REJ_BY_CAUSE_13_CFG Error");
    }

    if (VOS_TRUE == stKeepSrchHplmnEvenRejByCause13.ucKeepSrchHplmnEvenRejByCause13Flg)
    {
        NAS_MML_SetKeepSrchHplmnEvenRejByCause13Flg(VOS_TRUE);

        return;
    }

    NAS_MML_SetKeepSrchHplmnEvenRejByCause13Flg(VOS_FALSE);

    return;
}


VOS_VOID NAS_MMC_ReadEpsRejByCause14InVplmnAllowPsRegFlgNvim(VOS_VOID)
{
    NAS_NVIM_EPS_REJ_BY_CAUSE_14_IN_VPLMN_ALLOW_PS_REG_CFG_STRU stEpsRejByCause14InVplmnAllowPsRegCfg;
    VOS_UINT32                                                  ulLength;

    ulLength = 0;
    NV_GetLength(en_NV_Item_EPS_REJ_BY_CAUSE_14_IN_VPLMN_Allow_PS_REG_CFG, &ulLength);

    if (ulLength > sizeof(NAS_NVIM_EPS_REJ_BY_CAUSE_14_IN_VPLMN_ALLOW_PS_REG_CFG_STRU))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadEpsRejByCause14InVplmnAllowPsRegFlgNvim():WARNING: en_NV_Item_EPS_REJ_BY_CAUSE_14_IN_VPLMN_Allow_PS_REG_CFG length Error");

        return;
    }

    PS_MEM_SET(&stEpsRejByCause14InVplmnAllowPsRegCfg,
                0x00,
                sizeof(NAS_NVIM_EPS_REJ_BY_CAUSE_14_IN_VPLMN_ALLOW_PS_REG_CFG_STRU));

    if (NV_OK != NV_Read(en_NV_Item_EPS_REJ_BY_CAUSE_14_IN_VPLMN_Allow_PS_REG_CFG,
                        (VOS_VOID *)&stEpsRejByCause14InVplmnAllowPsRegCfg,
                        sizeof(NAS_NVIM_EPS_REJ_BY_CAUSE_14_IN_VPLMN_ALLOW_PS_REG_CFG_STRU)))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC,
                  "NAS_MMC_ReadEpsRejByCause14InVplmnAllowPsRegFlgNvim():en_NV_Item_EPS_REJ_BY_CAUSE_14_IN_VPLMN_Allow_PS_REG_CFG Error");
        return;
    }

    if (VOS_TRUE == stEpsRejByCause14InVplmnAllowPsRegCfg.ucEpsRejByCause14InVplmnAllowPsRegFlg)
    {
        NAS_MML_SetEpsRejByCause14InVplmnAllowPsRegFlg(VOS_TRUE);

        return;
    }

    NAS_MML_SetEpsRejByCause14InVplmnAllowPsRegFlg(VOS_FALSE);

    return;
}


VOS_VOID NAS_MMC_ReadCarryEplmnWhenSrchRplmnCfgNvim(VOS_VOID)
{
    NAS_NVIM_CARRY_EPLMN_WHEN_SRCH_RPLMN_CFG_STRU           stCarryEplmnWhenSrchRplmnCfg;
    NAS_MML_CARRY_EPLMN_WHEN_SRCH_RPLMN_CFG_STRU           *pstCarryEplmnWhenSrchRplmnCfg;
    VOS_UINT32                                              ulLength;

    ulLength = 0;
    NV_GetLength(en_NV_Item_CARRY_EPLMN_WHEN_SRCH_RPLMN_CFG, &ulLength);

    if (ulLength > sizeof(NAS_NVIM_CARRY_EPLMN_WHEN_SRCH_RPLMN_CFG_STRU))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadCarryEplmnWhenSrchRplmnCfgNvim():WARNING: en_NV_Item_CARRY_EPLMN_WHEN_SRCH_RPLMN_CFG length Error");

        return;
    }

    PS_MEM_SET(&stCarryEplmnWhenSrchRplmnCfg,
                0x00,
                sizeof(NAS_NVIM_CARRY_EPLMN_WHEN_SRCH_RPLMN_CFG_STRU));

    pstCarryEplmnWhenSrchRplmnCfg = NAS_MML_GetCarryEplmnWhenSrchRplmnCfg();

    if (NV_OK != NV_Read(en_NV_Item_CARRY_EPLMN_WHEN_SRCH_RPLMN_CFG,
                        (VOS_VOID *)&stCarryEplmnWhenSrchRplmnCfg,
                        sizeof(NAS_NVIM_CARRY_EPLMN_WHEN_SRCH_RPLMN_CFG_STRU)))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC,
                  "NAS_MMC_ReadCarryEplmnWhenSrchRplmnCfgNvim():en_NV_Item_CARRY_EPLMN_WHEN_SRCH_RPLMN_CFG Error");
    }

    if (NAS_MMC_NVIM_CARRY_EPLMN_SWITCH_BUTT > stCarryEplmnWhenSrchRplmnCfg.enSwitchFlag)
    {
        pstCarryEplmnWhenSrchRplmnCfg->enSwitchFlag = stCarryEplmnWhenSrchRplmnCfg.enSwitchFlag;
    }
    else
    {
        pstCarryEplmnWhenSrchRplmnCfg->enSwitchFlag = NAS_MMC_NVIM_CARRY_EPLMN_SWITCH_OFF;
    }

    if (VOS_TRUE == stCarryEplmnWhenSrchRplmnCfg.ucCarryEplmnSceneSwitchOn)
    {
        pstCarryEplmnWhenSrchRplmnCfg->ucCarryEplmnSceneSwitchOn = VOS_TRUE;
    }

    if (VOS_TRUE == stCarryEplmnWhenSrchRplmnCfg.ucCarryEplmnSceneAreaLost)
    {
        pstCarryEplmnWhenSrchRplmnCfg->ucCarryEplmnSceneAreaLost = VOS_TRUE;
    }

    if (VOS_TRUE == stCarryEplmnWhenSrchRplmnCfg.ucCarryEplmnSceneAvailableTimerExpired)
    {
        pstCarryEplmnWhenSrchRplmnCfg->ucCarryEplmnSceneAvailableTimerExpired = VOS_TRUE;
    }

    if (VOS_TRUE == stCarryEplmnWhenSrchRplmnCfg.ucCarryEplmnSceneCSFBServiceRej)
    {
        pstCarryEplmnWhenSrchRplmnCfg->ucCarryEplmnSceneCSFBServiceRej = VOS_TRUE;
    }

    if (VOS_TRUE == stCarryEplmnWhenSrchRplmnCfg.ucCarryEplmnSceneDisableLte)
    {
        pstCarryEplmnWhenSrchRplmnCfg->ucCarryEplmnSceneDisableLte = VOS_TRUE;
    }

    if (VOS_TRUE == stCarryEplmnWhenSrchRplmnCfg.ucCarryEplmnSceneEnableLte)
    {
        pstCarryEplmnWhenSrchRplmnCfg->ucCarryEplmnSceneEnableLte = VOS_TRUE;
    }

    if (VOS_TRUE == stCarryEplmnWhenSrchRplmnCfg.ucCarryEplmnSceneSysCfgSet)
    {
        pstCarryEplmnWhenSrchRplmnCfg->ucCarryEplmnSceneSysCfgSet = VOS_TRUE;
    }

    return;
}




VOS_VOID NAS_MMC_ReadProtectMtCsfbPagingProcedureLenNvim(VOS_VOID)
{
    NAS_MMC_NVIM_PROTECT_MT_CSFB_PAGING_PROCEDURE_LEN_STRU  stNvimProtectMtCsfbPagingProcedureLen;;

    PS_MEM_SET(&stNvimProtectMtCsfbPagingProcedureLen, 0x00, sizeof(stNvimProtectMtCsfbPagingProcedureLen));

    if (NV_OK != NV_Read(en_NV_Item_Protect_Mt_Csfb_Paging_Procedure_Len,
                        (VOS_VOID *)&stNvimProtectMtCsfbPagingProcedureLen,
                        sizeof(NAS_MMC_NVIM_PROTECT_MT_CSFB_PAGING_PROCEDURE_LEN_STRU)))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC,
                     "NAS_MMC_ReadProtectMtCsfbPagingProcedureLenNvim():en_NV_Item_Protect_Mt_Csfb_Paging_Procedure_Len Error");
        return;
    }

    if (stNvimProtectMtCsfbPagingProcedureLen.usMtCsfbPagingProcedureLen < NAS_MML_PROTECT_MT_CSFB_PAGING_PROCEDURE_MIN_LEN)
    {
        NAS_MML_SetProtectMtCsfbPagingProcedureLen(NAS_MML_PROTECT_MT_CSFB_PAGING_PROCEDURE_MIN_LEN);

        return;
    }

    if (stNvimProtectMtCsfbPagingProcedureLen.usMtCsfbPagingProcedureLen > NAS_MML_PROTECT_MT_CSFB_PAGING_PROCEDURE_MAX_LEN)
    {
        NAS_MML_SetProtectMtCsfbPagingProcedureLen(NAS_MML_PROTECT_MT_CSFB_PAGING_PROCEDURE_MAX_LEN);

        return;
    }

    NAS_MML_SetProtectMtCsfbPagingProcedureLen(stNvimProtectMtCsfbPagingProcedureLen.usMtCsfbPagingProcedureLen);

    return;
}


VOS_VOID NAS_MMC_ReadLowPrioAnycellsearchLteCfgNvim(VOS_VOID)
{
    NAS_NVIM_LOW_PRIO_ANYCELL_SEARCH_LTE_FLG_STRU           stNvimLowPrioAnycellsearchLteCfg;

    PS_MEM_SET(&stNvimLowPrioAnycellsearchLteCfg, 0x00, sizeof(NAS_NVIM_LOW_PRIO_ANYCELL_SEARCH_LTE_FLG_STRU));

    if (NV_OK != NV_Read(en_NV_Item_Low_Prio_Anycell_Search_Lte_Cfg,
                        (VOS_VOID *)&stNvimLowPrioAnycellsearchLteCfg,
                        sizeof(NAS_NVIM_LOW_PRIO_ANYCELL_SEARCH_LTE_FLG_STRU)))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC,
                     "NAS_MMC_ReadLowPrioAnycellsearchLteCfgNvim():en_NV_Item_Low_Prio_Anycell_Search_Lte_Cfg Error");
        return;
    }

    if (VOS_TRUE == stNvimLowPrioAnycellsearchLteCfg.ucLowPrioAnycellSearchLteFlg)
    {
        NAS_MML_SetLowPrioAnycellSearchLteFlg(VOS_TRUE);

        return;
    }

    NAS_MML_SetLowPrioAnycellSearchLteFlg(VOS_FALSE);

    return;
}
/* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-8-26, begin */
/*****************************************************************************
 �� �� ��  : NAS_MMC_ReadPlmnSearchPhaseOneTotalTimerCfgNvim
 ��������  : ��ȡen_NV_Item_Plmn_Search_Phase_One_Total_Time_CFG
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��26��
    ��    ��   : c00318887
    �޸�����   : �½�
*****************************************************************************/
VOS_VOID NAS_MMC_ReadPlmnSearchPhaseOneTotalTimerCfgNvim(VOS_VOID)
{
    NAS_NVIM_PLMN_SEARCH_PHASE_ONE_TOTAL_TIMER_CFG_STRU     stPhaseOneTotalTimerCfg;
    VOS_UINT32                                              ulLength;
    NAS_MML_PLMN_SEARCH_PHASE_ONE_TOTAL_TIMER_CFG_STRU     *pstPhaseOneTotalTimerInfo  = VOS_NULL_PTR;

    pstPhaseOneTotalTimerInfo  = NAS_MML_GetPlmnSearchPhaseOneTotalTimerCfg();

    ulLength = 0;
    PS_MEM_SET(&stPhaseOneTotalTimerCfg, 0x00, sizeof(stPhaseOneTotalTimerCfg));

    /* �Ȼ�ȡNV�ĳ��� */
    (VOS_VOID)NV_GetLength(en_NV_Item_Plmn_Search_Phase_One_Total_Timer_CFG, &ulLength);

    if (ulLength > sizeof(NAS_NVIM_PLMN_SEARCH_PHASE_ONE_TOTAL_TIMER_CFG_STRU))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadPlmnSearchPhaseOneTotalTimerCfgNvim(): en_NV_Item_Plmn_Search_Phase_One_Total_Timer_CFG length Error");
        return;
    }

    /* ��NVʧ�� */
    if (NV_OK != NV_Read(en_NV_Item_Plmn_Search_Phase_One_Total_Timer_CFG,
                         &stPhaseOneTotalTimerCfg, ulLength))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadPlmnSearchPhaseOneTotalTimerCfgNvim(): en_NV_Item_Plmn_Search_Phase_One_Total_Timer_CFG error");
        return;
    }

    /* NV�ر�ʱ��ʱ����Ч,����ʱ����Ƶ�һ�׶����� */
    if ( (VOS_FALSE == stPhaseOneTotalTimerCfg.ucActiveFlag)
      || (0 == stPhaseOneTotalTimerCfg.ulTotalTimeLen) )
    {
         pstPhaseOneTotalTimerInfo->ucActiveFlag       = VOS_FALSE;

         return;
    }

    /* NV��ʱ���ѵ�һ�׶�ʱ�����µ�ȫ�ֱ��� */
    pstPhaseOneTotalTimerInfo->ucActiveFlag            = VOS_TRUE;
    pstPhaseOneTotalTimerInfo->ulTotalTimeLen          = stPhaseOneTotalTimerCfg.ulTotalTimeLen;

    return;
}

/* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-8-26, end */


/* Added by z00359541 for CS REG FAIL FORB LA, 2015-9-23, begin */
/*****************************************************************************
 �� �� ��  : NAS_MMC_ReadCsRegFailForbLaTimeCfgNvim
 ��������  : ��ȡen_NV_Item_CS_REG_FAIL_CAUSE_FORB_LA_TIME_CFG ����
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��23��
    ��    ��   : z00359541
    �޸�����   : �½�
*****************************************************************************/
VOS_VOID NAS_MMC_ReadCsRegFailForbLaTimeCfgNvim(VOS_VOID)
{
    NAS_MML_FORB_LA_WITH_VALID_PERIOD_CFG_INFO_LIST_STRU   *pstForbLaWithValidPeriodCfg = VOS_NULL_PTR;
    VOS_UINT32                                              i;
    NAS_MMC_NVIM_CUSTOMIZED_FORB_LA_CFG_STRU         stCustomizedForbLaCfg;

    PS_MEM_SET(&stCustomizedForbLaCfg, 0x00, sizeof(stCustomizedForbLaCfg));

    pstForbLaWithValidPeriodCfg = NAS_MML_GetForbLaWithValidPeriodCfg();

    /* ���Կ�����Ч */
    if (VOS_TRUE  == NAS_USIMMAPI_IsTestCard())
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadCsRegFailForbLaTimeCfgNvim():Test SIM, Forb La List Invalid");
        return;
    }
    
    if (NV_OK != NV_Read(en_NV_Item_CS_REG_FAIL_FORB_LA_TIME_CFG, &stCustomizedForbLaCfg,
                          sizeof(NAS_MMC_NVIM_CUSTOMIZED_FORB_LA_CFG_STRU)))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadCsRegFailForbLaTimeCfgNvim():Read NV Failed");
        return;
    }   

    if (stCustomizedForbLaCfg.usRegFailCauseNum > NAS_MML_NVIM_MAX_REG_FAIL_CAUSE_NUM)
    {
        NAS_WARNING_LOG1(WUEPS_PID_MMC, "NAS_MMC_ReadCsRegFailForbLaTimeCfgNvim(): Forb La Num read from NV exceeds max", stCustomizedForbLaCfg.usRegFailCauseNum);
        stCustomizedForbLaCfg.usRegFailCauseNum = NAS_MML_NVIM_MAX_REG_FAIL_CAUSE_NUM;
    }

    pstForbLaWithValidPeriodCfg->ulSupportForbLaWithValidPeriodNum = stCustomizedForbLaCfg.usRegFailCauseNum;

    for (i = 0; i < pstForbLaWithValidPeriodCfg->ulSupportForbLaWithValidPeriodNum; i++)
    {
        pstForbLaWithValidPeriodCfg->astForbLaWithValidPeriodCfgList[i].usRegFailCause              = stCustomizedForbLaCfg.ausRegFailCauseList[i];
        pstForbLaWithValidPeriodCfg->astForbLaWithValidPeriodCfgList[i].usForbLaValidPeriodLen      = stCustomizedForbLaCfg.usForbLaTimeLen;
        pstForbLaWithValidPeriodCfg->astForbLaWithValidPeriodCfgList[i].usPunishTimeLen               = stCustomizedForbLaCfg.usPunishTimeLen;
    }

    return;
}
/* Added by z00359541 for CS REG FAIL FORB LA, 2015-9-23, end */


/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


