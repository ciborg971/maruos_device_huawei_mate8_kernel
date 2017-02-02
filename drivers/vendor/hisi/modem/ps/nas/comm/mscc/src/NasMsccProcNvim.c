

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "PsCommonDef.h"
#include "NasMsccProcNvim.h"
#if (FEATURE_ON == FEATURE_IMS)
#include "ImsaNvInterface.h"
#include "LPsNvInterface.h"
#include "LNvCommon.h"
#endif
#include "NVIM_Interface.h"
#include "NasNvInterface.h"

#include "NasMntn.h"
#include "NasMsccTimerMgmt.h"
#include "NasMsccComFunc.h"


#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_NAS_MSCC_PROC_NVIM_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ��������
*****************************************************************************/


VOS_VOID NAS_MSCC_ReadNvim(VOS_VOID)
{
    /* INit the Platform RAT cap structure */
    NAS_MSCC_ReadPlatformRatCapNvim();

    /* Init the IMS Config Parameter Structure */
    NAS_MSCC_ReadImsCfgInfoNvim();

    /* Read the NV System Acquire Info */
    NAS_MSCC_ReadMmssNvimInfo();
}
VOS_VOID NAS_MSCC_ReadImsCfgInfoNvim(VOS_VOID)
{
    /* Read NVIM to update the IMS RAT support */
    NAS_MSCC_ReadImsRatSupportNvim();

    /* Init the Voice domain */
    NAS_MSCC_ReadVoiceDomainNvim();

    /* Init the Ims Voice Cap Timer Len */
    NAS_MSCC_ReadWaitImsVoiceCapTimerLenNvim();
}
VOS_VOID NAS_MSCC_ReadImsRatSupportNvim(VOS_VOID)
{
#if (FEATURE_ON == FEATURE_IMS)
    VOS_UINT32                          ulLength;
    IMSA_NV_IMS_RAT_SUPPORT_STRU        stImsSupport;
#endif

    NAS_MSCC_IMS_CONFIG_PARA_STRU      *pstImsCfgInfo;

    pstImsCfgInfo = NAS_MSCC_GetImsCfgInfo();

    /* IMS��ر�ʱ��Ĭ�ϳ�ʼ��Ϊ��֧��IMS */
    PS_MEM_SET(&(pstImsCfgInfo->stImsRatSupport), 0, sizeof(NAS_MSCC_IMS_RAT_SUPPORT_STRU));

    pstImsCfgInfo->stImsRatSupport.ucGsmImsSupportFlag   = VOS_FALSE;
    pstImsCfgInfo->stImsRatSupport.ucUtranImsSupportFlag = VOS_FALSE;
    pstImsCfgInfo->stImsRatSupport.ucLteImsSupportFlag   = VOS_FALSE;
    pstImsCfgInfo->stImsRatSupport.ucGsmEmsSupportFlag   = VOS_FALSE;
    pstImsCfgInfo->stImsRatSupport.ucUtranEmsSupportFlag = VOS_FALSE;
    pstImsCfgInfo->stImsRatSupport.ucLteEmsSupportFlag   = VOS_FALSE;

    /* IMS����ֻ����FEATURE_IMS��ʱ�����п�������Ϊ���� */
#if (FEATURE_ON == FEATURE_IMS)
    /* �Ȼ�ȡNV�ĳ��� */
    ulLength = 0;
    NV_GetLength(EN_NV_ID_IMS_RAT_SUPPORT, &ulLength);

    if (ulLength > sizeof(IMSA_NV_IMS_RAT_SUPPORT_STRU))
    {
        NAS_TRACE_HIGH("NAS_MSCC_ReadImsRatSupportNvim(): EN_NV_ID_IMS_RAT_SUPPORT length Error");

        return;
    }

    /* ��NV��EN_NV_ID_IMS_RAT_SUPPORT��ʧ�ܣ�ֱ�ӷ��� */
    if (NV_OK != NV_Read(EN_NV_ID_IMS_RAT_SUPPORT, &stImsSupport, ulLength))
    {

        NAS_TRACE_HIGH("NAS_MSCC_ReadImsRatSupportNvim(): read EN_NV_ID_IMS_RAT_SUPPORT Error");

        return;
    }

    /* ��ֵ��ȫ�ֱ����� */
    pstImsCfgInfo->stImsRatSupport.ucGsmImsSupportFlag   = stImsSupport.ucGsmEmsSupportFlag;
    pstImsCfgInfo->stImsRatSupport.ucUtranImsSupportFlag = stImsSupport.ucUtranImsSupportFlag;
    pstImsCfgInfo->stImsRatSupport.ucLteImsSupportFlag   = stImsSupport.ucLteImsSupportFlag;
    pstImsCfgInfo->stImsRatSupport.ucGsmEmsSupportFlag   = stImsSupport.ucGsmEmsSupportFlag;
    pstImsCfgInfo->stImsRatSupport.ucUtranEmsSupportFlag = stImsSupport.ucUtranEmsSupportFlag;
    pstImsCfgInfo->stImsRatSupport.ucLteEmsSupportFlag   = stImsSupport.ucLteEmsSupportFlag;
#endif

    return;
}
VOS_VOID NAS_MSCC_ReadVoiceDomainNvim(VOS_VOID)
{
#if (FEATURE_ON == FEATURE_IMS)
    VOS_UINT32                          ulLength;
    LNAS_LMM_NV_VOICE_DOMAIN_STRU       stVoiceDomain;
#endif

    NAS_MSCC_IMS_CONFIG_PARA_STRU      *pstImsCfgInfo;

    pstImsCfgInfo = NAS_MSCC_GetImsCfgInfo();

    /* NV�ر�ʱ��Ĭ�ϳ�ʼ��ΪCS ONLY */
    pstImsCfgInfo->enVoiceDomain = NAS_MSCC_VOICE_DOMAIN_CS_ONLY;

#if (FEATURE_ON == FEATURE_IMS)
    pstImsCfgInfo->enVoiceDomain = NAS_MSCC_VOICE_DOMAIN_IMS_PS_PREFERRED;

    /* �Ȼ�ȡNV�ĳ��� */
    ulLength = 0;
    NV_GetLength(EN_NV_ID_UE_VOICE_DOMAIN, &ulLength);

    if (ulLength > sizeof(LNAS_LMM_NV_VOICE_DOMAIN_STRU))
    {
        NAS_TRACE_HIGH("NAS_MSCC_ReadVoiceDomainNvim(): EN_NV_ID_UE_VOICE_DOMAIN length Error");

        return;
    }

    /* ��NV��EN_NV_ID_UE_VOICE_DOMAIN��ʧ�ܣ�ֱ�ӷ��� */
    if (NV_OK != NV_Read(EN_NV_ID_UE_VOICE_DOMAIN,
                         &stVoiceDomain, ulLength))
    {

        NAS_TRACE_HIGH("NAS_MSCC_ReadVoiceDomainNvim(): read EN_NV_ID_UE_VOICE_DOMAIN Error");

        return;
    }

    /* NV������ȡֵ�Ϸ�ʱ����ֵ��ȫ�ֱ����� */
    if ( (VOS_TRUE                              == stVoiceDomain.bitOpVoicDomain)
      && (NAS_LMM_VOICE_DOMAIN_IMS_PS_PREFERRED >= stVoiceDomain.enVoicDomain) )
    {
        pstImsCfgInfo->enVoiceDomain = stVoiceDomain.enVoicDomain;
    }
#endif

    return;
}


VOS_VOID NAS_MSCC_ReadWaitImsVoiceCapTimerLenNvim(VOS_VOID)
{
#if (FEATURE_ON == FEATURE_IMS)
    NAS_NVIM_WAIT_IMS_VOICE_AVAIL_TIMER_LEN_STRU            stImsVoiceAvailTimerLen;
    VOS_UINT32                                              ulLength;
#endif
    NAS_MSCC_IMS_CONFIG_PARA_STRU                          *pstImsCfgInfo;

    pstImsCfgInfo = NAS_MSCC_GetImsCfgInfo();

    pstImsCfgInfo->ulWaitImsVoiceAvailTimerLen = TI_NAS_MSCC_WAIT_IMSA_IMS_VOICE_AVAIL_IND_LEN;

#if (FEATURE_ON == FEATURE_IMS)
    ulLength = 0;

    /* �Ȼ�ȡNV�ĳ��� */
    NV_GetLength(en_NV_Item_WAIT_IMS_VOICE_AVAIL_Timer_Len, &ulLength);

    if (ulLength > sizeof(NAS_NVIM_WAIT_IMS_VOICE_AVAIL_TIMER_LEN_STRU))
    {
        NAS_TRACE_HIGH("NAS_MSCC_ReadWaitImsVoiceCapTimerLenNvim(): en_NV_Item_WAIT_IMS_VOICE_AVAIL_Timer_Len length Error");
        return;
    }

    /* ��NVʧ�� */
    if (NV_OK != NV_Read(en_NV_Item_WAIT_IMS_VOICE_AVAIL_Timer_Len,
                         &stImsVoiceAvailTimerLen,
                         ulLength))
    {
        NAS_TRACE_HIGH("NAS_MSCC_ReadWaitImsVoiceCapTimerLenNvim(): en_NV_Item_WAIT_IMS_VOICE_AVAIL_Timer_Len error");
        return;
    }

    if (VOS_TRUE == stImsVoiceAvailTimerLen.ucNvimActiveFlag)
    {
        /* NV�ĳ���Ϊ0ʹ��Ĭ��ʱ��,NV�ĵ�λΪS,��Ҫת��Ϊ���� */
        if (0 == stImsVoiceAvailTimerLen.ucWaitImsVoiceAvailTimerLen)
        {
            pstImsCfgInfo->ulWaitImsVoiceAvailTimerLen = TI_NAS_MSCC_WAIT_IMSA_IMS_VOICE_AVAIL_IND_LEN;
        }
        else
        {
            pstImsCfgInfo->ulWaitImsVoiceAvailTimerLen = stImsVoiceAvailTimerLen.ucWaitImsVoiceAvailTimerLen * NAS_MSCC_THOUSAND_MILLISECOND_UNIT;
        }
    }
#endif

    return;
}

VOS_VOID NAS_MSCC_ReadPlatformRatCapNvim(VOS_VOID)
{
    VOS_UINT32                          i;
    VOS_UINT32                          j;
    PLATAFORM_RAT_CAPABILITY_STRU       stNvPlatformRatCap;
    VOS_RATMODE_ENUM_UINT32             enNasMsccPlatformRat;
    NAS_MSCC_PLATFORM_RAT_CAP_STRU     *pstPlatformRatCap;

    pstPlatformRatCap = NAS_MSCC_GetPlatformRatCap();

    /* Initialize the Platform RAT cap structure to contain only GSM */
    pstPlatformRatCap->ucRatNum      = 1;
    pstPlatformRatCap->aenRatList[0] = VOS_RATMODE_GSM;
    for (i = 1; i < VOS_RATMODE_BUTT; i++)
    {
        pstPlatformRatCap->aenRatList[i] = VOS_RATMODE_BUTT;
    }

    /* MemSet the stNvPlatformRatCap local structure to zero. Read NV 9203 to get the platform RAT capability supported*/
    PS_MEM_SET(&stNvPlatformRatCap, 0x0, sizeof(stNvPlatformRatCap));
    if (NV_OK != NV_Read(en_NV_Item_Platform_RAT_CAP,
                         &stNvPlatformRatCap,
                         sizeof(PLATAFORM_RAT_CAPABILITY_STRU)))
    {
        NAS_TRACE_HIGH("NAS_MSCC_ReadPlatformRatCapNvim():ERROR: read en_NV_Item_PLATFORM_RAT_CAP Error");

        return;
    }

    /* If the Number of RAT read from NVIM is greater than maximum, set the Number of Rat to the max value */
    if (stNvPlatformRatCap.usRatNum >= PLATFORM_MAX_RAT_NUM)
    {
        NAS_TRACE_HIGH("NAS_MSCC_ReadPlatformRatCapNvim():ERROR: en_NV_Item_PLATFORM_RAT_CAP Invalid: Number of Platforms greater than MAX");

        return;
    }

    /* Check if the NVIM data is valid */
    if (VOS_FALSE == NAS_MSCC_IsPlatformRatCapNvimValid(&stNvPlatformRatCap))
    {
        NAS_TRACE_HIGH("NAS_MSCC_ReadPlatformRatCapNvim():ERROR: en_NV_Item_PLATFORM_RAT_CAP Invalid");

        return;
    }

    j = 0;

    /* Read the NVIM data and convert the NVIM format to MSCC Enum format. Skip the BUTT plarform types */
    for (i = 0; i < stNvPlatformRatCap.usRatNum; i++)
    {
        enNasMsccPlatformRat = NAS_MSCC_ConvertNvPlatformRatToMsccType(stNvPlatformRatCap.aenRatList[i]);
        if (VOS_RATMODE_BUTT != enNasMsccPlatformRat)
        {
            pstPlatformRatCap->aenRatList[j] = enNasMsccPlatformRat;
            j ++;
        }
    }

    /* If atleast one entry is copied into the pstPlatformRatCap, update the number of RATs to the number read. */
    if (j > 0)
    {
        pstPlatformRatCap->ucRatNum      = (VOS_UINT8)j;
    }

    return;
}




VOS_VOID NAS_MSCC_ReadMmssNvimInfo(VOS_VOID)
{
    /* Read the MSCC Location Info From NVIM */
    NAS_MSCC_ReadLastLocationInfoNvim();

    /* Read the CL System Acquire Cfg NVIM */
    NAS_MSCC_ReadMmssSystemAcquireCfgNvim();
}



VOS_VOID NAS_MSCC_ReadMmssSystemAcquireCfgNvim(VOS_VOID)
{
    NAS_NVIM_MMSS_SYSTEM_ACQUIRE_CFG_STRU                   stNvimMmssSystemAcquireCfg;
    NAS_MSCC_MMSS_SYSACQ_CFG_STRU                          *pstMmssSysAcqCfgInfo = VOS_NULL_PTR;

    PS_MEM_SET(&stNvimMmssSystemAcquireCfg, 0x0, sizeof(NAS_NVIM_MMSS_SYSTEM_ACQUIRE_CFG_STRU));

    /* Get the MMSS Sys acq Cfg Info global variable address */
    pstMmssSysAcqCfgInfo = NAS_MSCC_GetMmssSysAcqCfgInfoAddr();

    if (NV_OK != NV_Read(en_Nv_Item_Mmss_System_Acquire_Cfg,
                     &stNvimMmssSystemAcquireCfg,
                     sizeof(NAS_NVIM_MMSS_SYSTEM_ACQUIRE_CFG_STRU)))
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_ReadCLSystemAcquireCfgNvim: NV Read Failed!");

        return;
    }

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-8, begin */
    NAS_MSCC_LogReadNVInfo(en_Nv_Item_Mmss_System_Acquire_Cfg,
                           sizeof(NAS_NVIM_MMSS_SYSTEM_ACQUIRE_CFG_STRU),
                           UEPS_PID_MSCC,
                           (VOS_UINT8 *)&stNvimMmssSystemAcquireCfg);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-8, end */

    /* Log the MMSS System acquire Cfg */
    NAS_MSCC_MNTN_LogNvimMmssCfgInfo(&stNvimMmssSystemAcquireCfg);

    /* Read the Search LTE on HSD Sync Ind Control Flag from NVIM */
    /* Read the NV Value if the NV value is true or False */
    if ((stNvimMmssSystemAcquireCfg.ucReAcqLteOnHrpdSyncIndFlag == VOS_TRUE)
      ||(stNvimMmssSystemAcquireCfg.ucReAcqLteOnHrpdSyncIndFlag == VOS_FALSE))
    {
        pstMmssSysAcqCfgInfo->ucReAcqLteOnHrpdSyncIndFlag = stNvimMmssSystemAcquireCfg.ucReAcqLteOnHrpdSyncIndFlag;

    }
    /* If the NV Value is neither true nor false, then use the default value of true */
    else
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_ReadMsccSearchLteOnHrpdSyncIndSwitch: Invalid Value!");

        /* Initialize to FALSE */
        pstMmssSysAcqCfgInfo->ucReAcqLteOnHrpdSyncIndFlag = VOS_FALSE;
    }

    /* Read the CDMA 1x Preferred flag from NVIM */
    /* Read the NV Value if the NV value is true or False */
    if ((stNvimMmssSystemAcquireCfg.ucIs1xLocInfoPrefThanLte == VOS_TRUE)
      ||(stNvimMmssSystemAcquireCfg.ucIs1xLocInfoPrefThanLte == VOS_FALSE))
    {
        pstMmssSysAcqCfgInfo->ucIs1xLocInfoPrefThanLte = stNvimMmssSystemAcquireCfg.ucIs1xLocInfoPrefThanLte;

    }
    /* If the NV Value is neither true nor false, then use the default value of true */
    else
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_ReadCdma1xLocationInfoPreferredFlag: Invalid Value!");

        /* Initialize the flag to contain CDMA 1x preferred */
        pstMmssSysAcqCfgInfo->ucIs1xLocInfoPrefThanLte = VOS_TRUE;

    }

    /* Save the Sys Acq timer Cfg from NVIM */
    NAS_MSCC_SaveSysAcqTimerCfg(&(stNvimMmssSystemAcquireCfg.stMmssSysAcqTimerCfg),
                                &(pstMmssSysAcqCfgInfo->stSysAcqTimerCfg));

    return;
}

VOS_VOID NAS_MSCC_ReadLastLocationInfoNvim(VOS_VOID)
{
    NAS_NVIM_MMSS_LAST_LOCATION_INFO_STRU                   stNvimMmssLocationInfo;
    NAS_MSCC_MMSS_LOCATION_INFO_STRU                       *pstMmssLocationInfo = VOS_NULL_PTR;

    PS_MEM_SET(&stNvimMmssLocationInfo, 0x0, sizeof(NAS_NVIM_MMSS_LAST_LOCATION_INFO_STRU));

    /* Get the MMSS Location Info Global variable address */
    pstMmssLocationInfo = NAS_MSCC_GetMmssLastLocationInfoAddr();

    /* Read the NV Item */
    if (NV_OK != NV_Read(en_Nv_Item_MmssLastLocationInfo,
                         &stNvimMmssLocationInfo,
                         sizeof(NAS_NVIM_MMSS_LAST_LOCATION_INFO_STRU)))
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_ReadLastLocationInfoNvim: Read NV Failed!");

        return;
    }

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-8, begin */
    NAS_MSCC_LogReadNVInfo(en_Nv_Item_MmssLastLocationInfo,
                           sizeof(NAS_NVIM_MMSS_LAST_LOCATION_INFO_STRU),
                           UEPS_PID_MSCC,
                           (VOS_UINT8 *)&stNvimMmssLocationInfo);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-8, end */

    /* Log the MMSS Last Location Info */
    NAS_MSCC_MNTN_LogNvimMmssLastLocInfo(&stNvimMmssLocationInfo);

    /* If the MMSS Location Info valid flag is not TRUE, use the default values written in the previous step */
    if (VOS_TRUE != stNvimMmssLocationInfo.ucIsLocInfoUsedInSwitchOn)

    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_ReadLastLocationInfoNvim: Location Info NVIM Flag is not active!");

        return;
    }
    /* Read the NVIM Values if the Valid flag is TRUE */
    else
    {

        if (NAS_NVIM_LC_RAT_COMBINED_GUL == stNvimMmssLocationInfo.enSysAcqMode)
        {
            /* Set the System Acquire Mode as GUL in System Acquire Ctrl global variable and return*/
            pstMmssLocationInfo->enSysAcqMode = NAS_MSCC_LC_RAT_COMBINED_GUL;

            /* Set the location info as valid */
            pstMmssLocationInfo->ucIsLocInfoUsedInSwitchOn = VOS_TRUE;
        }
        /* Update the global values to the NV values if Sys Acq Mode is CL */
        else if (NAS_NVIM_LC_RAT_COMBINED_CL == stNvimMmssLocationInfo.enSysAcqMode)
        {
            /* Set the System Acquire Mode as CL */
            pstMmssLocationInfo->enSysAcqMode = NAS_MSCC_LC_RAT_COMBINED_CL;

            /* Update the global values to the NV values */
            pstMmssLocationInfo->ucCdma1xActiveFlag         = stNvimMmssLocationInfo.ucIs1xLocInfoValid;
            pstMmssLocationInfo->ucLteActiveFlag            = stNvimMmssLocationInfo.ucIsLteLocInfoValid;

            /* Update the 1x location info */
            pstMmssLocationInfo->st1xLocationInfo.ulMcc = stNvimMmssLocationInfo.st1xLocInfo.ulMcc;
            pstMmssLocationInfo->st1xLocationInfo.ulMnc = stNvimMmssLocationInfo.st1xLocInfo.ulMnc;
            pstMmssLocationInfo->st1xLocationInfo.usSid = stNvimMmssLocationInfo.st1xLocInfo.usSid;
            pstMmssLocationInfo->st1xLocationInfo.usNid = stNvimMmssLocationInfo.st1xLocInfo.usNid;

            pstMmssLocationInfo->st1xLocationInfo.en1xPrioClass = stNvimMmssLocationInfo.st1xLocInfo.en1xPrioClass;
            pstMmssLocationInfo->st1xLocationInfo.enAIPrioClass = stNvimMmssLocationInfo.st1xLocInfo.enAIPrioClass;

            /* Update the LTE location info */
            pstMmssLocationInfo->stLteLocationInfo.ulMcc = stNvimMmssLocationInfo.st3gppLocInfo.ulMcc;
            pstMmssLocationInfo->stLteLocationInfo.ulMnc = stNvimMmssLocationInfo.st3gppLocInfo.ulMnc;

            pstMmssLocationInfo->stLteLocationInfo.enPrioClass = stNvimMmssLocationInfo.st3gppLocInfo.enPrioClass;

            /* Set the location info as valid */
            pstMmssLocationInfo->ucIsLocInfoUsedInSwitchOn = VOS_TRUE;

        }
        /* Make error log if System Acquire mode is invalid */
        else
        {
            NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_ReadLastLocationInfoNvim: System acquire mode is invalid!");
        }
    }

    return;
}




VOS_VOID NAS_MSCC_WriteMmssLocationInfoNvim(
    NAS_MSCC_MMSS_LOCATION_INFO_STRU                       *pstMmssLocationInfo
)
{
    NAS_NVIM_MMSS_LAST_LOCATION_INFO_STRU    stNvimMmssLocationInfo;

    PS_MEM_SET(&stNvimMmssLocationInfo, 0x0, sizeof(NAS_NVIM_MMSS_LAST_LOCATION_INFO_STRU));

    /* Construct the NVIM MMSS Location info */
    if (NAS_MSCC_LC_RAT_COMBINED_CL == pstMmssLocationInfo->enSysAcqMode)
    {
        stNvimMmssLocationInfo.enSysAcqMode = NAS_NVIM_LC_RAT_COMBINED_CL;
    }
    else
    {
        stNvimMmssLocationInfo.enSysAcqMode = NAS_NVIM_LC_RAT_COMBINED_GUL;
    }

    stNvimMmssLocationInfo.ucIs1xLocInfoValid  = pstMmssLocationInfo->ucCdma1xActiveFlag;
    stNvimMmssLocationInfo.ucIsLteLocInfoValid = pstMmssLocationInfo->ucLteActiveFlag;

    /* Update the 1x Location Info */
    stNvimMmssLocationInfo.st1xLocInfo.ulMcc   = pstMmssLocationInfo->st1xLocationInfo.ulMcc;
    stNvimMmssLocationInfo.st1xLocInfo.ulMnc   = pstMmssLocationInfo->st1xLocationInfo.ulMnc;
    stNvimMmssLocationInfo.st1xLocInfo.usSid   = pstMmssLocationInfo->st1xLocationInfo.usSid;
    stNvimMmssLocationInfo.st1xLocInfo.usNid   = pstMmssLocationInfo->st1xLocationInfo.usNid;
    stNvimMmssLocationInfo.st1xLocInfo.en1xPrioClass = pstMmssLocationInfo->st1xLocationInfo.en1xPrioClass;
    stNvimMmssLocationInfo.st1xLocInfo.enAIPrioClass = pstMmssLocationInfo->st1xLocationInfo.enAIPrioClass;

    /* Update the LTE Location Info */
    stNvimMmssLocationInfo.st3gppLocInfo.ulMcc  = pstMmssLocationInfo->stLteLocationInfo.ulMcc;
    stNvimMmssLocationInfo.st3gppLocInfo.ulMnc  = pstMmssLocationInfo->stLteLocationInfo.ulMnc;
    stNvimMmssLocationInfo.st3gppLocInfo.enPrioClass = pstMmssLocationInfo->stLteLocationInfo.enPrioClass;

    /* Set the NVIM location info as valid */
    stNvimMmssLocationInfo.ucIsLocInfoUsedInSwitchOn = VOS_TRUE;

    if (NV_OK != NV_Write(en_Nv_Item_MmssLastLocationInfo,
                         &stNvimMmssLocationInfo, sizeof(NAS_NVIM_MMSS_LAST_LOCATION_INFO_STRU)))
    {
        /* Make Error log is NV Write Fails */
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_WriteMmssLocationInfoNvim:Write Nvim Failed");

        return;
    }

    return;
}



VOS_UINT8 NAS_MSCC_ReadMlplMsplNvim(
    NAS_MSCC_NVIM_MLPL_MSPL_STRU                            *pstNvimMlplMspl
)
{
    if (NV_OK != NV_Read(en_NV_Item_MLPL_MSPL_FILE, pstNvimMlplMspl,
                                            sizeof(NAS_MSCC_NVIM_MLPL_MSPL_STRU)))
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_ReadAndParseMlplMsplNvim:ERROR: Read Nvim Failed");

        return VOS_FALSE;
    }

    return VOS_TRUE;
}



#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



