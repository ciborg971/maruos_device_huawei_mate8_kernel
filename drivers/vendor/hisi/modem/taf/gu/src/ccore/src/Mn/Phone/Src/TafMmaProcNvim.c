
/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
/* Deleted by h00313353 for iteration 9, 2015-2-13, begin */

/* Deleted by h00313353 for iteration 9, 2015-2-13, end */
#include "pscfg.h"
#if (FEATURE_LTE == FEATURE_ON)
#include "msp_nvim.h"
#endif
#include "ScInterface.h"
#include "NasNvInterface.h"
#include "TafNvInterface.h"
#include "TafMmaCtx.h"
#include "TafAppMma.h"
#include "MmaAppLocal.h"
#include "GasNvInterface.h"

/* Add by l00305157 for Service_State_Optimize_PhaseII, 2015-02-11, begin */
#include "TafLog.h"
/* Add by l00305157 for Service_State_Optimize_PhaseII, 2015-02-11, end */

#if ( FEATURE_ON == FEATURE_LTE )
#include "LPsNvInterface.h"
#include "LNvCommon.h"
#endif

#if (FEATURE_ON == FEATURE_IMS)
#include "ImsaNvInterface.h"
#endif

#include "NasMntn.h"
#include "TafLog.h"
/* Added by y00322978 for CDMA Iteration 17, 2015-7-8, begin */
#include "TafMmaMntn.h"
#include "TafMmaComFunc.h"
/* Added by y00322978 for CDMA Iteration 17, 2015-7-8, end */

#include "NasUsimmApi.h"



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_MMA_PROC_NVIM_C

/*****************************************************************************
  2 ȫ�ֱ���
*****************************************************************************/
extern NAS_MMA_NEW_ADD_GLABAL_VARIABLE_FOR_PC_REPLAY_ST g_MmaNewValue;
extern MMA_DEACT_SIM_WHEN_POWEROFF_ENUM_UINT8           g_ucMmaDeactSimWhenPoweroff;
extern TAF_MMA_GLOBAL_VALUE_ST                          gstMmaValue;
extern VOS_UINT8                                        g_ucMmaOmConnectFlg;                           /* �Ƿ�����PC��������, VOS_TRUE: ������; VOS_FALSE: δ����.                                                                                   Ĭ��δ���� */
extern VOS_UINT8                                        g_ucMmaOmPcRecurEnableFlg;                     /* ��ǰPC�����Ƿ�ʹ����NAS��PC�ط���Ϣ�ķ���, VOS_TRUE: ʹ��; VOS_FASLE: δʹ��
                                                                                   Ĭ��ʹ��PC�ط� */
extern VOS_UINT32                                       g_ucUsimHotOutFlag;
extern VOS_UINT32                                       g_ucUsimHotInFlag;
extern MMA_UE_FORB_BAND_ST                              gstMmaForbBand;
extern ENUM_SYSTEM_APP_CONFIG_TYPE_U16                  g_usMmaAppConfigSupportType;
extern VOS_UINT8                                        g_aucMmaImei[TAF_PH_IMEI_LEN-1];


/*****************************************************************************
  3 �궨��
*****************************************************************************/

/*lint -save -e958 */

VOS_VOID TAF_MMA_ReadUeSupporttedGuBandNvim(VOS_VOID)
{
    /* �޸�Ӳ��Ƶ�εĶ�ȡΪ32λ��ʽ */
    VOS_UINT32                          aulSptBand[3];
    TAF_MMA_UE_SUPPORT_FREQ_BAND_STRU   stUeBand;
    TAF_MMA_USER_BAND_SET_UN            uUserSetBand;
    VOS_UINT32                          ulDataLen;
    TAF_MMA_UE_BAND_CAPA_ST            *pstUeBandCap = VOS_NULL_PTR;

    ulDataLen = 0;

    /*��ȡ UE֧�ֵ� Band */
    PS_MEM_SET(&stUeBand,0x00,sizeof(stUeBand));
    PS_MEM_SET(&uUserSetBand,0x00,sizeof(uUserSetBand));


    PS_MEM_SET(aulSptBand, 0x00, sizeof(aulSptBand));

    (VOS_VOID)NV_GetLength(en_NV_Item_WG_RF_MAIN_BAND, &ulDataLen);

    if (NV_OK != NV_Read(en_NV_Item_WG_RF_MAIN_BAND,aulSptBand,ulDataLen))
    {
        /*��ӡδ�ɹ���ʼ��ֵ��ԭֵ����*/
        MMA_WARNINGLOG("MMA_InitMeInfo():Read en_NV_Item_WG_RF_MAIN_BAND Failed!");
    }
    else
    {
        pstUeBandCap = TAF_MMA_GetUeSupportBandAddr();

        stUeBand.unWcdmaBand.ulBand = aulSptBand[0];
        pstUeBandCap->unWRFSptBand.ulBand = aulSptBand[0];
        MMA_SwitchUESupportBand2UserSetBand(stUeBand,&uUserSetBand);
        pstUeBandCap->ulUeWSptBand = uUserSetBand.ulPrefBand;

        PS_MEM_SET(&stUeBand,0x00,sizeof(stUeBand));
        PS_MEM_SET(&uUserSetBand,0x00,sizeof(uUserSetBand));
        /*V9R1 NV���ݽṹ��չΪ32λ */
        stUeBand.unGsmBand.ulBand = aulSptBand[2];
        pstUeBandCap->unGRFSptBand.ulBand = aulSptBand[2];
        /*V9R1 NV���ݽṹ��չΪ32λ */
        MMA_SwitchUESupportBand2UserSetBand(stUeBand,&uUserSetBand);
        pstUeBandCap->ulUeGSptBand = uUserSetBand.ulPrefBand;

        pstUeBandCap->ulAllUeBand = (pstUeBandCap->ulUeGSptBand | pstUeBandCap->ulUeWSptBand);
    }

    return;
}
VOS_VOID TAF_MMA_ReadForbBandNvim(VOS_VOID)
{
    VOS_UINT32                          ulLen;
    NAS_MMA_NVIM_FORBAND_STRU           stForband;
    VOS_UINT8                           ucOffSet;


    ulLen = 0;
    PS_MEM_SET(&stForband, 0x00, sizeof(stForband));

    (VOS_VOID)NV_GetLength(en_NV_Item_Forbidden_Band, &ulLen);

    if (ulLen > MMA_FORB_BAND_NV_MAX_SIZE)
    {
        return;
    }

    PS_MEM_SET(&stForband, 0, ulLen);

    if (NV_OK != NV_Read(en_NV_Item_Forbidden_Band,&stForband, ulLen))
    {
        MMA_WARNINGLOG("MMA_GetForbBandFromNV():WARNING: en_NV_Item_Forbbiden_Band Error");
        return;
    }

    /*
    gstMmaForbBand������NV�е�ֵ��һ�£���Ҫ�������ֽڽ���ת��
    VOS_UINT8    ucActiveFlag  - NV���1���ֽ�
    VOS_UINT8    ucForbStatus  - NV���2���ֽ�
    TAF_UINT32   ulBandLow     - NV���3-6���ֽ�
    TAF_UINT32   ulBandHigh    - NV���7-10���ֽ�
    */
    ucOffSet = 0;
    /*lint -e961*/
    gstMmaForbBand.ucActiveFlag = stForband.aucForband[ucOffSet++];
    /*lint +e961*/

    if (NV_ITEM_DEACTIVE == gstMmaForbBand.ucActiveFlag)
    {
        return;
    }
    /*lint -e961*/
    gstMmaForbBand.ucForbStatus = stForband.aucForband[ucOffSet++];
    /*lint +e961*/

    PS_MEM_CPY(&(gstMmaForbBand.stForbBand.ulBandLow),stForband.aucForband+ucOffSet,
                                sizeof(gstMmaForbBand.stForbBand.ulBandLow));

    ucOffSet += sizeof(gstMmaForbBand.stForbBand.ulBandLow);

    PS_MEM_CPY(&(gstMmaForbBand.stForbBand.ulBandHigh),stForband.aucForband+ucOffSet,
                                sizeof(gstMmaForbBand.stForbBand.ulBandHigh));


    if ( (0 != gstMmaForbBand.stForbBand.ulBandHigh)
      || (TAF_PH_BAND_ANY != gstMmaForbBand.stForbBand.ulBandLow))
    {
        gstMmaForbBand.ulForbBand = gstMmaForbBand.stForbBand.ulBandHigh |
            (gstMmaForbBand.stForbBand.ulBandLow & ~TAF_PH_BAND_NEED_CHANGE_TO_64BIT);
    }
    else
    {
        gstMmaForbBand.ulForbBand = gstMmaForbBand.stForbBand.ulBandLow;
    }

    /* �ݴ��� */
    if (TAF_PH_BAND_ANY == gstMmaForbBand.ulForbBand)
    {
        gstMmaForbBand.ulForbBand = 0;
    }

    return;
}


#if (FEATURE_ON == FEATURE_LTE)
VOS_VOID TAF_MMA_ReadNvimUeSupporttedLteBand(VOS_VOID)
{
    TAF_USER_SET_PREF_BAND64                   *pstUeSupportLteBand = VOS_NULL_PTR;

    VOS_UINT32                                  ulRslt;
    LRRC_NV_UE_EUTRA_CAP_STRU                  *pstUECapability     = VOS_NULL_PTR;
    RRC_UE_CAP_RF_PARA_STRU                    *pstRfPara           = VOS_NULL_PTR;
    VOS_UINT32                                  i;
    VOS_UINT8                                   ucBandNo;

    pstUeSupportLteBand = TAF_MMA_GetUeSupportLteBandAddr();

    PS_MEM_SET(pstUeSupportLteBand, 0X0, sizeof(TAF_USER_SET_PREF_BAND64));



    pstUECapability =(LRRC_NV_UE_EUTRA_CAP_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMA,
                            sizeof(LRRC_NV_UE_EUTRA_CAP_STRU));

    if(VOS_NULL_PTR == pstUECapability)
    {
        MN_ERR_LOG("TAF_MMA_ReadNvimUeSupporttedLteBand():PS_MEM_ALLOC failed!");
        return ;
    }

    PS_MEM_SET(pstUECapability, 0x00, sizeof(LRRC_NV_UE_EUTRA_CAP_STRU));


    /* LTE NV��� */
    ulRslt = NVM_Read(EN_NV_ID_UE_CAPABILITY, pstUECapability, sizeof(LRRC_NV_UE_EUTRA_CAP_STRU));


    if ( (NV_OK != ulRslt)
      || (NVIM_EUTRA_MAX_SUPPORT_BANDS_NUM < pstUECapability->stRfPara.usCnt) )
    {
        /* ��NVʧ��,��ӡδ�ɹ���ʼ��ֵ��Ĭ�ϸ�ֵΪ֧������Ƶ�� */
        MN_ERR_LOG("TAF_MMA_ReadNvimUeSupporttedLteBand():read en_NV_Item_EUTRA_CAPA_COMM_INFO error");
        pstUeSupportLteBand->ulBandHigh = MN_MMA_LTE_HIGH_BAND_ALL;
        pstUeSupportLteBand->ulBandLow  = MN_MMA_LTE_LOW_BAND_ALL;

        PS_MEM_FREE(WUEPS_PID_MMA, pstUECapability);

        return;
    }

    /* ��ȡNV�е�Ƶ����Ϣ:
       ulBandLow�����bit��Ӧband1�����bit��Ӧband32
       ulBandHigh�����bit��Ӧband33�����bit��Ӧband64 */
    pstRfPara = &(pstUECapability->stRfPara);

    for ( i = 0; i < pstRfPara->usCnt; i++ )
    {
        ucBandNo = (pstRfPara->astSuppEutraBandList[i]).ucEutraBand;

        /* NV�е�Ƶ����ϢָʾΪ��32,����Ӧband1��band32*/
        if ( ucBandNo <= (NVIM_EUTRA_MAX_SUPPORT_BANDS_NUM / 2) )
        {
            /*lint -e701*/
            pstUeSupportLteBand->ulBandLow  |= (VOS_UINT32)( 0x00000001 << (ucBandNo - 1) );
            /*lint +e701*/

        }

        /* NV�е�Ƶ����ϢָʾΪ��32,����Ӧband33��band64 */
        else if ( ucBandNo <= NVIM_EUTRA_MAX_SUPPORT_BANDS_NUM  )
        {
            /*lint -e961 -e701*/
            pstUeSupportLteBand->ulBandHigh |= (VOS_UINT32)( 0x00000001 << (ucBandNo - 32 - 1) );
            /*lint +e961 +e701*/
        }
        else
        {
            /* band���쳣 */
            MN_ERR_LOG("TAF_MMA_ReadNvimUeSupporttedLteBand():LTE BAND NO IS BIG THAN 64, error");
        }
    }

    PS_MEM_FREE(WUEPS_PID_MMA, pstUECapability);

    return;
}
VOS_VOID TAF_MMA_ReadUserSetLteBands(VOS_VOID)
{
    TAF_MMA_SYSCFG_USER_SET_BAND_STRU  *pstUserSetBand = VOS_NULL_PTR;

    pstUserSetBand = TAF_MMA_GetSyscfgUserSetBandAddr();

    /* ���û����õ�LTEƵ�� NV�� */
    if (NV_OK != NV_Read(en_NV_Item_USER_SET_LTEBANDS,
                         &(pstUserSetBand->stUserSetLteBand), sizeof(TAF_USER_SET_PREF_BAND64)))
    {
        /* ��NVʧ��,��ӡδ�ɹ���ʼ��ֵ��Ĭ�ϸ�ֵΪ֧������Ƶ�� */
        pstUserSetBand->stUserSetLteBand.ulBandLow  = MN_MMA_LTE_LOW_BAND_ANY;
        pstUserSetBand->stUserSetLteBand.ulBandHigh = MN_MMA_LTE_HIGH_BAND_ANY;
    }

    return;
}


#endif


VOS_VOID  TAF_MMA_ReadFreqBandNvim(VOS_VOID)
{
    TAF_MMA_SYSCFG_USER_SET_BAND_STRU  *pstUserSetBand = VOS_NULL_PTR;
    NVIM_UE_SUPPORT_FREQ_BAND_STRU      stUserSetFreqBand;

    PS_MEM_SET(&stUserSetFreqBand, 0x00, sizeof(stUserSetFreqBand));

    pstUserSetBand = TAF_MMA_GetSyscfgUserSetBandAddr();

    if (NV_OK != NV_Read(en_NV_Item_Support_Freqbands,
                         &stUserSetFreqBand, sizeof(NVIM_UE_SUPPORT_FREQ_BAND_STRU)))
    {
        /* ��ӡδ�ɹ���ʼ��ֵ��ԭֵ���� */
        MN_WARN_LOG("TAF_MMA_ReadFreqBandNvim():Read Support_Freqbands Failed!");

        return;
    }

    pstUserSetBand->uUserSetUeFormatGuBand.unWcdmaBand.ulBand = stUserSetFreqBand.ulWcdmaBand;
    pstUserSetBand->uUserSetUeFormatGuBand.unGsmBand.ulBand   = stUserSetFreqBand.ulGsmBand;

    PS_MEM_SET(pstUserSetBand->uUserSetUeFormatGuBand.aucReserved1,
               0,
               sizeof(pstUserSetBand->uUserSetUeFormatGuBand.aucReserved1));
    PS_MEM_SET(pstUserSetBand->uUserSetUeFormatGuBand.aucReserved2,
               0,
               sizeof(pstUserSetBand->uUserSetUeFormatGuBand.aucReserved2));

    return;
}
VOS_VOID TAF_MMA_ReadUserSettedBandNvim(VOS_VOID)
{
    TAF_MMA_SYSCFG_USER_SET_BAND_STRU  *pstUserSetBand = VOS_NULL_PTR;

    pstUserSetBand = TAF_MMA_GetSyscfgUserSetBandAddr();

    /* ��ȡ�û����õ�GUƵ�� */
    if (NV_OK != NV_Read(en_NV_Item_User_Set_Freqbands,
                         &(pstUserSetBand->stOrigUserSetGuBand),
                         sizeof(TAF_USER_SET_PREF_BAND64)))
    {
        /*��ӡδ�ɹ���ʼ��ֵ��ԭֵ����*/
        pstUserSetBand->uUserSetGuBand.ulPrefBand      = TAF_PH_BAND_ANY;
        pstUserSetBand->stOrigUserSetGuBand.ulBandHigh = 0;
        pstUserSetBand->stOrigUserSetGuBand.ulBandLow  = TAF_PH_BAND_ANY;
        MMA_WARNINGLOG("TAF_MMA_ReadUserSettedBandNvim():Read UserSet_Freqbands Failed!");
    }
    else
    {
        if ( (0 != pstUserSetBand->stOrigUserSetGuBand.ulBandHigh )
          || ( TAF_PH_BAND_ANY != pstUserSetBand->stOrigUserSetGuBand.ulBandLow) )
        {
            pstUserSetBand->uUserSetGuBand.ulPrefBand = pstUserSetBand->stOrigUserSetGuBand.ulBandHigh |
                                        (pstUserSetBand->stOrigUserSetGuBand.ulBandLow & ~TAF_PH_BAND_NEED_CHANGE_TO_64BIT);
            /* ������ЧƵ�� */
            pstUserSetBand->uUserSetGuBand.ulPrefBand &= (TAF_MMA_GetUeSupportBandAddr()->ulAllUeBand);
        }
        else
        {
            /* ��ǰƵ��ΪTAF_PH_BAND_ANYʱ����ֵΪ����֧�ֵ�����Ƶ�� */
            pstUserSetBand->uUserSetGuBand.ulPrefBand = TAF_MMA_GetUeSupportBandAddr()->ulAllUeBand;
        }
    }

    MN_INFO_LOG1("TAF_MMA_ReadUserSettedBandNvim():Support_Freqbands:",(VOS_INT32)pstUserSetBand->uUserSetGuBand.ulPrefBand);


    return;
}



VOS_VOID  TAF_MMA_UpdateBandCapa(VOS_VOID)
{
    TAF_MMA_GetUeSupportBandAddr()->ulUeWSptBand &= ~(gstMmaForbBand.ulForbBand);
    TAF_MMA_GetUeSupportBandAddr()->ulUeGSptBand &= ~(gstMmaForbBand.ulForbBand);
    TAF_MMA_GetUeSupportBandAddr()->ulAllUeBand = (TAF_MMA_GetUeSupportBandAddr()->ulUeGSptBand \
                                                 | TAF_MMA_GetUeSupportBandAddr()->ulUeWSptBand);


    return;
}


VOS_VOID  TAF_MMA_UpdateUserSetFreqBand(VOS_VOID)
{
    TAF_USER_SET_PREF_BAND64            stUserSetBandAny;  /*64λԭʼƵ��*/
    TAF_MMA_SYSCFG_USER_SET_BAND_STRU  *pstUserSetBand = VOS_NULL_PTR;

    pstUserSetBand = TAF_MMA_GetSyscfgUserSetBandAddr();

    stUserSetBandAny.ulBandHigh = 0;
    stUserSetBandAny.ulBandLow = TAF_PH_BAND_ANY;

    /* �����û�����Ƶ�ε�NVΪ3fffffff */
    if (MMA_SUCCESS != MMA_WriteValue2Nvim(en_NV_Item_User_Set_Freqbands,
                                           &stUserSetBandAny,
                                           sizeof(stUserSetBandAny)))
    {
        MMA_WARNINGLOG("MMA_UpdateBandNvRefForbBand():WARNING:NVIM_Write en_NV_Item_User_Set_Freqbands failed");
    }

    /* ��ǰƵ��ΪTAF_PH_BAND_ANYʱ����ֵΪ����֧�ֵ�����Ƶ�� */
    /* д��en_NV_Item_User_Set_Freqbands֮��ֱ�Ӹ���ȫ�ֱ������������������¶���NV */
    pstUserSetBand->uUserSetGuBand.ulPrefBand = TAF_MMA_GetUeSupportBandAddr()->ulAllUeBand;

    return;
}


VOS_VOID  TAF_MMA_UpdateSupportFreqBand(
    TAF_MMA_UE_SUPPORT_FREQ_BAND_STRU  *pstOrigFreqBand
)
{
    TAF_MMA_SYSCFG_USER_SET_BAND_STRU  *pstUserSetBand = VOS_NULL_PTR;

    pstUserSetBand = TAF_MMA_GetSyscfgUserSetBandAddr();

    /* ����Ƶ��NV */
    if (MMA_SUCCESS != MMA_WriteValue2Nvim(en_NV_Item_Support_Freqbands,
                                           pstOrigFreqBand,
                                           sizeof(pstOrigFreqBand->unWcdmaBand)+sizeof(pstOrigFreqBand->unGsmBand)))
    {
        MMA_WARNINGLOG("MMA_UpdateBandNvRefForbBand():WARNING:NVIM_Write en_NV_Item_Support_Freqbands failed");
    }

    /* д��en_NV_Item_Support_Freqbands֮��ֱ�Ӹ���ȫ�ֱ������������������¶���NV */
    PS_MEM_CPY(&(pstUserSetBand->uUserSetUeFormatGuBand),
                pstOrigFreqBand,
                sizeof(TAF_MMA_UE_SUPPORT_FREQ_BAND_STRU));
    return;
}


VOS_VOID MMA_UpdateBandNvRefForbBand(VOS_VOID)
{
    TAF_MMA_UE_SUPPORT_FREQ_BAND_STRU    stOrigFreqBand;
    TAF_MMA_USER_BAND_SET_UN             uOrigFreqBand;
    TAF_MMA_SYSCFG_USER_SET_BAND_STRU   *pstUserSetBand = VOS_NULL_PTR;

    pstUserSetBand = TAF_MMA_GetSyscfgUserSetBandAddr();


    PS_MEM_SET(&uOrigFreqBand, 0, sizeof(TAF_MMA_USER_BAND_SET_UN));

    PS_MEM_SET(&stOrigFreqBand, 0x00, sizeof(stOrigFreqBand));

    stOrigFreqBand  = pstUserSetBand->uUserSetUeFormatGuBand;

    /*����ǰϵͳ���õ�Ƶ��ת��Ϊ�û����õĸ�ʽ*/
    MMA_SwitchUESupportBand2UserSetBand(stOrigFreqBand,&uOrigFreqBand);

    /* ��ǰϵͳ���õ�Ƶ����ulForbBand�Ƿ��н��� */
    if (0 != (uOrigFreqBand.ulPrefBand & gstMmaForbBand.ulForbBand))
    {
        /*���˵���ǰ��ֹ��Ƶ��*/
        uOrigFreqBand.ulPrefBand &= ~(gstMmaForbBand.ulForbBand);

        MMA_SwitchUserSetBand2UESupportBand(uOrigFreqBand, &stOrigFreqBand);

        /* дNV:en_NV_Item_User_Set_Freqbands,����ȫ�ֱ��� */
        TAF_MMA_UpdateUserSetFreqBand();

        /* дNV:en_NV_Item_Support_Freqbands,����ȫ�ֱ��� */
        TAF_MMA_UpdateSupportFreqBand(&stOrigFreqBand);
    }

}
/*****************************************************************************
 �� �� ��  : MMA_UpdateForbBandStatusToNV
 ��������  : ��ForbBand��NV��״̬����ΪVOS_TRUE
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��4��23��
    ��    ��   : likelai
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID MMA_UpdateForbBandStatusToNV(VOS_VOID)
{
    VOS_UINT32                           ulRslt;

    gstMmaForbBand.ucForbStatus = VOS_TRUE;

    ulRslt = MMA_WriteValue2Nvim(en_NV_Item_Forbidden_Band,
                   &gstMmaForbBand,
                   sizeof(gstMmaForbBand.ucActiveFlag)+sizeof(gstMmaForbBand.ucForbStatus));

    if (MMA_SUCCESS != ulRslt)
    {
        MMA_WARNINGLOG("MMA_UpdateForbBandStatusToNV():WARNING:NVIM_Write en_NV_Item_Forbbiden_Band failed");
    }

    return;
}


VOS_VOID TAF_MMA_UpdateUeAllowedBandRange(VOS_VOID)
{
    /* Ƶ����ص�NV����:
    1.��en_NV_Item_WG_RF_MAIN_BAND
    2.��en_NV_Item_Forbidden_Band
    3.��en_NV_Item_EUTRA_CAPA_COMM_INFO
    4.��en_NV_Item_Support_Freqbands
    5.дen_NV_Item_User_Set_Freqbands��
      ͬʱ����gstMmaValue.stLastSyscfgSet.stUserSetBand.uUserSetGuBand.ulPrefBand
    6.дen_NV_Item_Support_Freqbands
      ͬʱ����gstMmaValue.stLastSyscfgSet.stUserSetBand.uUserSetUeFormatGuBand
    7.дen_NV_Item_Forbidden_Band
    8.��en_NV_Item_USER_SET_LTEBANDS
    */

    /* en_NV_Item_WG_RF_MAIN_BAND */
    /*��ȡӲ��֧�ֵ�Ƶ�η�Χ*/
    TAF_MMA_ReadUeSupporttedGuBandNvim();

    /* en_NV_Item_Forbidden_Band */
    /*��ȡ��ֹƵ�ε�״̬�ͷ�Χ*/
    TAF_MMA_ReadForbBandNvim();

#if (FEATURE_ON == FEATURE_LTE)
    /* en_NV_Item_EUTRA_CAPA_COMM_INFO */
    /* ��ȡ���֧�ֵ�LTE��Ƶ�η�Χ */
    TAF_MMA_ReadNvimUeSupporttedLteBand();

    /* en_NV_Item_USER_SET_LTEBANDS */
    /* ��ȡ�û����õ�LTE��Ƶ�η�Χ */
    TAF_MMA_ReadUserSetLteBands();
#endif

    /* en_NV_Item_Support_Freqbands */
    TAF_MMA_ReadFreqBandNvim();

    /* ��ȡen_NV_Item_User_Set_Freqbands*/
    TAF_MMA_ReadUserSettedBandNvim();

    if (NV_ITEM_ACTIVE == gstMmaForbBand.ucActiveFlag)
    {
        /* ����gstMmaBandCapa */
        TAF_MMA_UpdateBandCapa();
    }


    return;
}
VOS_VOID TAF_MMA_ReadPlmnSelectionModeNvim(VOS_VOID)
{
    NAS_NVIM_SELPLMN_MODE_STRU          stPlmnSelMode;
    VOS_UINT32                          ulLength;

    ulLength = 0;

    (VOS_VOID)NV_GetLength(en_NV_Item_SelPlmn_Mode, &ulLength);
    if (ulLength > sizeof(NAS_NVIM_SELPLMN_MODE_STRU))
    {
        return;
    }


    stPlmnSelMode.usSelPlmnMode = NAS_MSCC_PIF_PLMN_SEL_MODE_AUTO;

    if (NV_OK != NV_Read(en_NV_Item_SelPlmn_Mode, &stPlmnSelMode, ulLength))
    {
        MMA_ERRORLOG("TAF_MMA_ReadPlmnSelectionModeNvim(): Read NV Fail");
        return;
    }

    if ((stPlmnSelMode.usSelPlmnMode != NAS_MSCC_PIF_PLMN_SEL_MODE_AUTO)
     && (stPlmnSelMode.usSelPlmnMode != NAS_MSCC_PIF_PLMN_SEL_MODE_MANUAL))
    {
        MMA_ERRORLOG("TAF_MMA_ReadPlmnSelectionModeNvim(): ucPlmnSelMode is invalid");
        return;
    }


    TAF_MMA_SetPlmnSelectionMode((VOS_UINT8)stPlmnSelMode.usSelPlmnMode);

    return;
}
VOS_VOID TAF_MMA_ReadRatPrioListNvim(VOS_VOID)
{
    TAF_MMA_RAT_ORDER_STRU             *pstRatPrioList = VOS_NULL_PTR;

    /* ���뼼��ƽ������δʹ�ܣ����뼼����NV��en_NV_Item_RAT_PRIO_LIST��ȡ */
    if (VOS_TRUE != TAF_MMA_GetRatBalancingEnableFlg())
    {
        /* ��ȡ��ǰ�Ľ���ģʽ���ȼ� */
        pstRatPrioList = TAF_MMA_GetRatPrioListAddr();
        TAF_MMA_ReadNvimRatPrioList(pstRatPrioList);
        PS_MEM_CPY(&(gstMmaValue.pg_StatusContext->stRatPrioList),
                   pstRatPrioList, sizeof(TAF_MMA_RAT_ORDER_STRU));

        TAF_SDC_SetMsPrioRatList((TAF_SDC_RAT_PRIO_STRU *)pstRatPrioList);
    }
    /* ���뼼��ƽ������ʹ�ܣ��յ���״̬���ҿ���λʱ���ٴ�4F36�ļ���ȡ */
    else
    {
        MMA_NORMAILLOG("TAF_MMA_InitRatPrioList(): WAIT FOR READING 4F36.");
    }

    return;
}
VOS_VOID TAF_MMA_ReadMsClassNvim(VOS_VOID)
{
    NAS_NVIM_MS_CLASS_STRU              stMsClass;
    VOS_UINT32                          ulLength;
    TAF_MMA_LAST_SETTED_SYSCFG_SET_STRU                    *pstLastSyscfgSet = VOS_NULL_PTR;

    PS_MEM_SET(&stMsClass, 0x00, sizeof(NAS_NVIM_MS_CLASS_STRU));
    pstLastSyscfgSet = TAF_MMA_GetLastSyscfgSetAddr();
    ulLength = 0;

    (VOS_VOID)NV_GetLength(en_NV_Item_MMA_MsClass, &ulLength);
    if (NV_OK != NV_Read(en_NV_Item_MMA_MsClass,
                         &stMsClass,
                         ulLength))
    {
        /* Modified by h00313353 for Iteration 13, 2015-4-9, begin */
        pstLastSyscfgSet->enSrvDomain = TAF_MMA_SERVICE_DOMAIN_CS_PS;
    }
    else
    {
        pstLastSyscfgSet->enSrvDomain = stMsClass.ucMsClass;
    }

    MMA_ChangeSrv2Class(pstLastSyscfgSet->enSrvDomain, &gstMmaValue.stSetMsClass.MsClassType);
    /* Modified by h00313353 for Iteration 13, 2015-4-9, end */

    gstMmaValue.stSetMsClass.NewMsClassType             = gstMmaValue.stSetMsClass.MsClassType;
    /*ͬ���ò���λ��STA��ģ���е�ֵ*/
    gstMmaValue.pg_StatusContext->ucModeService         = gstMmaValue.stSetMsClass.MsClassType;
    return;
}
VOS_VOID TAF_MMA_ReadRoamCapaNvim(VOS_VOID)
{
    VOS_UINT32                          ulLength;
    NAS_NVIM_ROAM_CFG_INFO_STRU         stRoamFeature;
    TAF_MMA_LAST_SETTED_SYSCFG_SET_STRU                    *pstLastSyscfgSet = VOS_NULL_PTR;

    PS_MEM_SET(&stRoamFeature, 0x00, sizeof(stRoamFeature));
    pstLastSyscfgSet = TAF_MMA_GetLastSyscfgSetAddr();
    ulLength = 0;

    (VOS_VOID)NV_GetLength(en_NV_Item_Roam_Capa, &ulLength);

    if ( NV_OK != NV_Read(en_NV_Item_Roam_Capa,
                          &stRoamFeature,
                          ulLength))
    {
        MMA_WARNINGLOG("TAF_MMA_ReadRoamCapaNvim():Read en_NV_Item_Roam_Capa Failed!");
        stRoamFeature.ucRoamFeatureFlg = NAS_MSCC_PIF_ROAM_FEATURE_OFF;
        stRoamFeature.ucRoamCapability = NAS_MSCC_PIF_ROAM_NATION_OFF_INTERNATION_OFF;
    }
    else
    {
        if (stRoamFeature.ucRoamFeatureFlg >= NAS_MSCC_PIF_ROAM_FEATURE_BUTT)
        {
            stRoamFeature.ucRoamFeatureFlg = NAS_MSCC_PIF_ROAM_FEATURE_OFF;
        }
        if (stRoamFeature.ucRoamCapability >= NAS_MSCC_PIF_ROAM_BUTT)
        {
            stRoamFeature.ucRoamCapability = NAS_MSCC_PIF_ROAM_NATION_OFF_INTERNATION_OFF;
        }
    }

    gstMmaValue.ucRoamFeatureStatus = stRoamFeature.ucRoamFeatureFlg;
    /* Modified by h00313353 for Iteration 13, 2015-4-15, begin */
    pstLastSyscfgSet->enRoam        = stRoamFeature.ucRoamCapability;
    /* Modified by h00313353 for Iteration 13, 2015-4-15, end */
    return;
}


VOS_VOID TAF_MMA_ReadRoamingBrokerInfoNvim(VOS_VOID)
{
    NAS_MMA_NVIM_ROAMING_BROKER_STRU    stRoamingBroker;
    VOS_UINT32                          ulLength;

    ulLength = 0;

    PS_MEM_SET(&stRoamingBroker, 0, sizeof(NAS_MMA_NVIM_ROAMING_BROKER_STRU));
    (VOS_VOID)NV_GetLength(en_NV_Item_Roaming_Broker, &ulLength);

    if (NV_OK != NV_Read(en_NV_Item_Roaming_Broker, &stRoamingBroker, ulLength))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMA, "TAF_MMA_ReadRoamingBrokerInfoNvim: Read NV Fail ");
        gstMmaValue.ucRoamBrokerSwitch = VOS_FALSE;
    }
    else
    {
        gstMmaValue.ucRoamBrokerSwitch = (stRoamingBroker.aucRoamingBroker)[0];

        /* ���NV�е�ֵ��Ч��������RoamBroker���ܹر� */
        if ( (VOS_FALSE != (stRoamingBroker.aucRoamingBroker)[0]) && (VOS_TRUE != (stRoamingBroker.aucRoamingBroker)[0]) )
        {
            gstMmaValue.ucRoamBrokerSwitch = VOS_FALSE;
        }
    }

    return;
}
VOS_VOID TAF_MMA_ReadReportPlmnSupportFlgNvim(VOS_VOID)
{
    TAF_MMA_NVIM_REPORT_PLMN_SUPPORT_FLG_STRU   stReportPlmn;
    VOS_UINT32                                  ulLength;


    PS_MEM_SET(&stReportPlmn, 0x00, sizeof(stReportPlmn));
    ulLength = 0;

    /* �Ȼ�ȡNV�ĳ��� */
    (VOS_VOID)NV_GetLength(en_NV_Item_REPORT_PLMN_SUPPORT_FLAG, &ulLength);

    if (ulLength > sizeof(TAF_MMA_NVIM_REPORT_PLMN_SUPPORT_FLG_STRU))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMA,"TAF_MMA_ReadNvimReportPlmnSupportFlg():WARNING: en_NV_Item_REPORT_PLMN_SUPPORT_FLAG length Error");
        gstMmaValue.ucReportPlmnFlg = VOS_FALSE;
        return;
    }

    if (NV_OK != NV_Read (en_NV_Item_REPORT_PLMN_SUPPORT_FLAG, &stReportPlmn, ulLength))
    {
        gstMmaValue.ucReportPlmnFlg = VOS_FALSE;
        return;
    }

    if ((VOS_TRUE  != stReportPlmn.ucNvimActiveFlg)
     && (VOS_FALSE != stReportPlmn.ucNvimActiveFlg))
    {
        gstMmaValue.ucReportPlmnFlg = VOS_FALSE;
        return;
    }

    /* ��NVֵ��ֵ��ȫ�ֱ��� */
    gstMmaValue.ucReportPlmnFlg = stReportPlmn.ucNvimActiveFlg;

    return;
}
VOS_VOID TAF_MMA_ReadAccessModeNvim(VOS_VOID)
{
    VOS_UINT32                          ulLength;
    NAS_MMA_NVIM_ACCESS_MODE_STRU       stAccessMode;
    TAF_MMA_LAST_SETTED_SYSCFG_SET_STRU                    *pstLastSyscfgSet = VOS_NULL_PTR;

    PS_MEM_SET(&stAccessMode, 0x00, sizeof(NAS_MMA_NVIM_ACCESS_MODE_STRU));
    pstLastSyscfgSet = TAF_MMA_GetLastSyscfgSetAddr();
    ulLength = 0;

    (VOS_VOID)NV_GetLength(en_NV_Item_MMA_AccessMode, &ulLength);
    if (ulLength > sizeof(NAS_MMA_NVIM_ACCESS_MODE_STRU))
    {
        return;
    }

    if (NV_OK != NV_Read(en_NV_Item_MMA_AccessMode ,
                         &stAccessMode,
                         ulLength))

    {
        MN_WARN_LOG("TAF_MMA_ReadAccessModeNvim:Read:NV_Read runs failed");
        return ;
    }
    pstLastSyscfgSet->enPrioRat = (stAccessMode.aucAccessMode)[1];
    return;
}


VOS_VOID TAF_MMA_ReadFollowonOpenSpeedFlagNvim(VOS_VOID)
{
    VOS_UINT32                              ulLength;
    NAS_NVIM_FOLLOWON_OPENSPEED_FLAG_STRU   stQuickStartFlg;

    PS_MEM_SET(&stQuickStartFlg, 0x00, sizeof(NAS_NVIM_FOLLOWON_OPENSPEED_FLAG_STRU));
    ulLength = sizeof(NAS_NVIM_FOLLOWON_OPENSPEED_FLAG_STRU);

    if (NV_OK != NV_Read(en_NV_Item_FollowOn_OpenSpeed_Flag,
                          (VOS_VOID*)(&(stQuickStartFlg.ulQuickStartSta)),
                          ulLength))
    {
       gstMmaValue.ulQuickStartFlg = MMA_QUICK_START_DISABLE;

       return;
    }

    gstMmaValue.ulQuickStartFlg = stQuickStartFlg.ulQuickStartSta;
    return;
}


VOS_VOID TAF_MMA_ReadRfAutoTestFlagNvim(VOS_VOID)
{
    VOS_UINT32                          ulDataLen;
    VOS_UINT32                          ulAutoSwitchOnFlg;

    ulAutoSwitchOnFlg   = MMA_RF_AUTO_TEST_DISABLE;
    ulDataLen           = sizeof(VOS_UINT16);

    if (NV_OK != NV_Read(en_NV_Item_RF_Auto_Test_Flag,
                          (VOS_VOID*)(&(ulAutoSwitchOnFlg)),
                           ulDataLen))
    {
       TAF_MMA_SetAutoSwitchOnFlg(MMA_RF_AUTO_TEST_ENABLE);

       return;
    }

    TAF_MMA_SetAutoSwitchOnFlg(ulAutoSwitchOnFlg);

#if 0
#ifdef NAS_STUB
    TAF_MMA_SetAutoSwitchOnFlg(MMA_RF_AUTO_TEST_DISABLE);
#endif
#endif

    return;
}


VOS_VOID TAF_MMA_ReadEFustServiceCfgNvim(VOS_VOID)
{
    VOS_UINT32                          ulDataLen;

    ulDataLen = sizeof(MMA_EFUST_SERVICE_CFG_STRU);

    if (NV_OK != NV_Read(en_NV_Item_EFust_Service_Cfg,
                          (VOS_VOID*)(&(gstMmaValue.stEfustServiceCfg)),
                           ulDataLen))
    {
         /*��ӡδ�ɹ���ʼ��ֵ��ԭֵ����*/
        MMA_WARNINGLOG("TAF_MMA_ReadEFustServiceCfgNvim():Read EFust_Service_Cfg Failed!");
    }

    if (NV_ITEM_DEACTIVE == gstMmaValue.stEfustServiceCfg.ucEnableFlag)
    {
        gstMmaValue.stEfustServiceCfg.ucForbidSndMsg = 0;
        gstMmaValue.stEfustServiceCfg.ucForbidReg2GNetWork = 0;
    }

    return;
}

/* TAF_MMA_ReadDisplaySpnFlagNvim*/



VOS_VOID TAF_MMA_ReadNotDisplayLocalNetworkNameNvim(VOS_VOID)
{
    VOS_UINT32                                              ulLength;
    TAF_MMA_NOT_DISPLAY_LOCAL_NETWORKNAME_NVIM_STRU         stNotDisplayLocalNetworkNameStru;

    ulLength = 0;

    PS_MEM_SET(&stNotDisplayLocalNetworkNameStru, 0x00, sizeof(TAF_MMA_NOT_DISPLAY_LOCAL_NETWORKNAME_NVIM_STRU));
    (VOS_VOID)NV_GetLength(en_NV_Item_NotDisplayLocalNetworkName, &ulLength);

    /* ��NV�л�ȡ�û����õ��Ƿ���ʾ���ص�ȫ����Ӫ����Ϣ��־ */
    if (NV_OK == NV_Read(en_NV_Item_NotDisplayLocalNetworkName,
                         &stNotDisplayLocalNetworkNameStru,
                         ulLength))
    {
       gstMmaValue.ucNotDisplayLocalNetworkNameFlg = stNotDisplayLocalNetworkNameStru.ucNotDisplayLocalNetworkNameFlg;
    }


    return;
}
VOS_VOID TAF_MMA_ReadSystemAppCofigNvim(VOS_VOID)
{
    VOS_UINT32                          ulLength;
    NAS_NVIM_SYSTEM_APP_CONFIG_STRU     stSysAppConfig;

    ulLength = 0;
    PS_MEM_SET(&stSysAppConfig, 0x00, sizeof(NAS_NVIM_SYSTEM_APP_CONFIG_STRU));

    /* ��ȡen_NV_Item_System_APP_Config����ȡ�Խӵ��ϲ�Ӧ�� */
    (VOS_VOID)NV_GetLength(en_NV_Item_System_APP_Config, &ulLength);

    if (NV_OK != NV_Read(en_NV_Item_System_APP_Config,
                         &stSysAppConfig, ulLength))
    {
        stSysAppConfig.usSysAppConfigType = SYSTEM_APP_MP;
        MMA_WARNINGLOG("TAF_MMA_ReadSystemAppCofigNvim():Read en_NV_Item_System_APP_Config Failed!");
    }

    if ( SYSTEM_APP_ANDROID < stSysAppConfig.usSysAppConfigType)
    {
        g_usMmaAppConfigSupportType = SYSTEM_APP_MP;
        MMA_WARNINGLOG("TAF_MMA_ReadSystemAppCofigNvim():en_NV_Item_System_APP_Config error!");
    }
    else
    {
        g_usMmaAppConfigSupportType = stSysAppConfig.usSysAppConfigType;
    }


    return;
}
VOS_VOID TAF_MMA_ReadImeiNvim(VOS_VOID)
{
    TAF_PH_MEINFO_STRU                 *pstMeInfo = VOS_NULL_PTR;
    VOS_UINT8                           aucBuf[TAF_PH_IMEI_LEN + 1];
    VOS_UINT8                           ucCheckData;
    VOS_UINT32                          ulDataLen;
    VOS_UINT32                          i;
    MODEM_ID_ENUM_UINT16                enModemId;

    ulDataLen   = TAF_PH_IMEI_LEN;
    ucCheckData = 0;
    pstMeInfo   = &(gstMmaValue.stMeInfo);
    PS_MEM_SET(aucBuf, 0x00, sizeof(aucBuf));

    /* ��PID��ȡMODEMID */
    enModemId = VOS_GetModemIDFromPid(WUEPS_PID_MMA);

    /* ����SC�ӿڶ�ȡIMEI���� */
    (VOS_VOID)SC_PERS_NvRead(enModemId, en_NV_Item_IMEI, aucBuf, NV_ITEM_IMEI_SIZE);

    for (i = 0; i < (TAF_PH_IMEI_LEN-2); i += 2)
    {
        ucCheckData += aucBuf[i]
                      +((aucBuf[i+1] + aucBuf[i+1])/10)
                      +((aucBuf[i+1] + aucBuf[i+1])%10);
    }

    ucCheckData = (10 - (ucCheckData%10))%10;

    MMA_ImeiBcd2Ascii((VOS_UINT8)ulDataLen, aucBuf, (pstMeInfo->ImeisV.aucImei));

    (pstMeInfo->ImeisV.aucImei)[TAF_PH_IMEI_LEN-2] = (VOS_UINT8)(ucCheckData + 0x30);
    (pstMeInfo->ImeisV.aucImei)[TAF_PH_IMEI_LEN-1] = 0;

    PS_MEM_CPY(g_MmaNewValue.aucImeiBcd, aucBuf, ulDataLen);

    PS_MEM_CPY(g_aucMmaImei, pstMeInfo->ImeisV.aucImei, TAF_PH_IMEI_LEN - 1);

    return;
}


VOS_VOID TAF_MMA_ReadFmridNvim(VOS_VOID)
{
    VOS_UINT32                          ulDataLen;
    TAF_PH_MEINFO_STRU                 *pstMeInfo = VOS_NULL_PTR;

    pstMeInfo = &(gstMmaValue.stMeInfo);
    ulDataLen = TAF_MAX_MFR_ID_LEN + 1;

    /*��ȡ��������*/
    if (NV_OK != NV_Read(en_NV_Item_FMRID,
                         pstMeInfo->FmrId.aucMfrId,
                         ulDataLen))
    {
        /*��ӡδ�ɹ���ʼ��ֵ��ԭֵ����*/
        MMA_WARNINGLOG("TAF_MMA_ReadFmridNvim():Read FMRID Failed!");
    }


    return;
}



VOS_VOID TAF_MMA_ReadProductNameNvim(VOS_VOID)
{
    VOS_UINT32                          ulDataLen;
    TAF_PH_MEINFO_STRU                 *pstMeInfo = VOS_NULL_PTR;

    pstMeInfo = &(gstMmaValue.stMeInfo);
    ulDataLen = TAF_PH_PRODUCT_NAME_LEN + 1;

    /*��ȡ��Ʒ����*/
    if (NV_OK != NV_Read(en_NV_Item_ProductName,
                         pstMeInfo->ProductName.aucProductName,
                         ulDataLen))
    {
        /*��ӡδ�ɹ���ʼ��ֵ��ԭֵ����*/
       MMA_WARNINGLOG("TAF_MMA_ReadProductNameNvim():Read ProductName Failed!");
    }


    return;
}


VOS_VOID TAF_MMA_ReadAttEnsCustomNvim(VOS_VOID)
{
    NVIM_ATT_ENS_CTRL_STRU              stNvAttEns;


    PS_MEM_SET(&stNvAttEns, 0x00, sizeof(stNvAttEns));

    /* ��NV��en_NV_Item_Att_Ens_Ctrl_Paraʧ�� */
    if (NV_OK != NV_Read(en_NV_Item_Att_Ens_Ctrl_Para,
                         &stNvAttEns,
                         sizeof(NVIM_ATT_ENS_CTRL_STRU)))
    {
        MMA_ERRORLOG("TAF_MMA_ReadATTCustomNvim(): Read NV Fail");
        return;
    }

    /* ������ѡ��˵����Ʊ�ʶ */
    if (VOS_TRUE == stNvAttEns.ucNetSelMenuFlg)
    {
        TAF_MMA_SetNetworkSelectionMenuEnableFlg(VOS_TRUE);
    }

    /* �ý��뼼��ƽ����Ʊ�ʶ */
    if (VOS_TRUE == stNvAttEns.ucRatBalancingFlg)
    {
        TAF_MMA_SetRatBalancingEnableFlg(VOS_TRUE);
    }

    return;
}


#if (FEATURE_ON == FEATURE_LTE)
VOS_UINT32  TAF_MMA_ReadLastTinInfoNvim(
    NAS_NVIM_TIN_INFO_STRU             *pstTinInfo
)
{
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulLength;

    (VOS_VOID)NV_GetLength(en_NV_Item_TIN_INFO, &ulLength);

    ulResult = NV_Read(en_NV_Item_TIN_INFO, pstTinInfo, sizeof(NAS_NVIM_TIN_INFO_STRU));

    if (NV_OK != ulResult)
    {
        return MMA_FAILURE;
    }

    return MMA_SUCCESS;
}

#endif

/*VOS_VOID TAF_MMA_ReadUeSupporttedCPHSFlagNvim(VOS_VOID)*/

VOS_VOID TAF_MMA_ReadDeactUsimWhenPoweroffNvim(VOS_VOID)
{
    TAF_NVIM_DEACT_SIM_WHEN_POWEROFF_STRU                   stNvDeactSimWhenPoweroff;

    PS_MEM_SET(&stNvDeactSimWhenPoweroff, 0, sizeof(TAF_NVIM_DEACT_SIM_WHEN_POWEROFF_STRU));

    if (NV_OK != NV_Read(en_NV_Item_DEACT_USIM_WHEN_POWEROFF,
                         &stNvDeactSimWhenPoweroff,
                         sizeof(TAF_NVIM_DEACT_SIM_WHEN_POWEROFF_STRU)))
    {
        /* ��ȡNV��ʧ�ܣ�Ĭ�ϸ����Թر� */
        g_ucMmaDeactSimWhenPoweroff = MMA_DEACT_SIM_WHEN_POWEROFF_DISABLE;

        return;
    }

    /* NV��ȡ�ɹ�����ֵΪ1�������Դ򿪣�������Ϊ���Թر� */
    if (VOS_TRUE == stNvDeactSimWhenPoweroff.ucEnableFlag)
    {
        g_ucMmaDeactSimWhenPoweroff = MMA_DEACT_SIM_WHEN_POWEROFF_ENABLE;
    }
    else
    {
        g_ucMmaDeactSimWhenPoweroff = MMA_DEACT_SIM_WHEN_POWEROFF_DISABLE;
    }

    return;
}

/* TAF_MMA_ReadAlphanumericNameByPlmnIdNvim*/

VOS_VOID  TAF_MMA_ReadPsStartNvim( VOS_VOID )
{
    NAS_MMA_NVIM_AUTO_START_STRU        stNvAutoStart;

    stNvAutoStart.ulAutoStart   = NAS_MMA_AUTOMATIC_START;

    if ( NV_OK != NV_Read(en_NV_Item_PS_START,
                          &stNvAutoStart,
                          sizeof(stNvAutoStart) ))
    {
        (VOS_VOID)vos_printf("read auto start nv fail\r\n");
    }

    if ((stNvAutoStart.ulAutoStart) > NAS_MMA_MANUAL_START)
    {
        TAF_MMA_SetAutoInitPsFlg(VOS_TRUE);
        return;
    }

    if (NAS_MMA_MANUAL_START == stNvAutoStart.ulAutoStart)
    {
        TAF_MMA_SetAutoInitPsFlg(VOS_FALSE);
    }
    else
    {
        TAF_MMA_SetAutoInitPsFlg(VOS_TRUE);
    }

    return;
}
VOS_VOID  TAF_MMA_ReadCardLockStatusNvim( VOS_VOID )
{
    TAF_CUSTOM_CARDLOCK_STATUS_STRU     stCardLockStatus;
    VOS_UINT32                          ulResult;

    PS_MEM_SET(&stCardLockStatus, 0x00, sizeof(stCardLockStatus));

    ulResult = NV_Read(en_NV_Item_CardlockStatus,
                       &stCardLockStatus,
                       (VOS_UINT32)(sizeof(stCardLockStatus)));

    if (NV_OK != ulResult)
    {
        MN_WARN_LOG("TAF_MMA_ReadCardLockStatusNvim:WARNING:  read sim lock status fail");
    }

    g_MmaNewValue.stCardLockStatus = stCardLockStatus;

    return;
}


VOS_VOID  TAF_MMA_ReadSimLockMaxTimesNvim( VOS_VOID )
{
    TAF_CUSTOM_SIM_LOCK_MAX_TIMES_STRU  stSimLockMaxTimes;
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulLength;

    PS_MEM_SET(&stSimLockMaxTimes, 0x00, sizeof(stSimLockMaxTimes));
    ulLength = 0;

    /* �Ȼ�ȡNV�ĳ��� */
    (VOS_VOID)NV_GetLength(en_NV_Item_CustomizeSimLockMaxTimes, &ulLength);

    if (ulLength > sizeof(TAF_CUSTOM_SIM_LOCK_MAX_TIMES_STRU))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMA,"TAF_MMA_ReadNvimCustomizeSimLockMaxTimes():WARNING: en_NV_Item_CustomizeSimLockMaxTimes length Error");
        g_MmaNewValue.stSimLockMaxTimes.ulStatus = VOS_FALSE;
        g_MmaNewValue.stSimLockMaxTimes.ulLockMaxTimes = TAF_PH_CARDLOCK_DEFAULT_MAXTIME;
        return;
    }

    ulResult = NV_Read(en_NV_Item_CustomizeSimLockMaxTimes,
                               &stSimLockMaxTimes,
                               sizeof(stSimLockMaxTimes));

    if (NV_OK != ulResult)
    {
        g_MmaNewValue.stSimLockMaxTimes.ulStatus        = VOS_FALSE;
        g_MmaNewValue.stSimLockMaxTimes.ulLockMaxTimes  = TAF_PH_CARDLOCK_DEFAULT_MAXTIME;
    }
    else
    {
        if (VOS_FALSE == stSimLockMaxTimes.ulStatus)
        {
            g_MmaNewValue.stSimLockMaxTimes.ulLockMaxTimes = TAF_PH_CARDLOCK_DEFAULT_MAXTIME;
        }
        else
        {
            g_MmaNewValue.stSimLockMaxTimes = stSimLockMaxTimes;
        }
    }

    return;
}
VOS_VOID  TAF_MMA_ReadSimLockPlmnNvim( VOS_VOID )
{
    TAF_CUSTOM_SIM_LOCK_PLMN_INFO_STRU          stSimLockPlmnInfo;
    VOS_UINT32                                  ulResult;

    PS_MEM_SET(&stSimLockPlmnInfo, 0x00, sizeof(stSimLockPlmnInfo));

    ulResult = NV_Read(en_NV_Item_CustomizeSimLockPlmnInfo,
                       &stSimLockPlmnInfo,
                       sizeof(stSimLockPlmnInfo));
    if (NV_OK != ulResult)
    {
        g_MmaNewValue.stSimLockPlmnInfo.ulStatus = VOS_FALSE;
        PS_MEM_SET(g_MmaNewValue.stSimLockPlmnInfo.astSimLockPlmnRange, (VOS_CHAR)0xaa,
                       sizeof(g_MmaNewValue.stSimLockPlmnInfo.astSimLockPlmnRange));
    }
    else
    {
        g_MmaNewValue.stSimLockPlmnInfo = stSimLockPlmnInfo;
    }

    return;
}


VOS_UINT32  TAF_MMA_ReadLastImsiNvim(
    NAS_MMC_NVIM_LAST_IMSI_STRU        *pstLastImsi
)
{
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulLength;

    ulLength = 0;

    (VOS_VOID)NV_GetLength(en_NV_Item_Last_Imsi, &ulLength);

    ulResult = NV_Read(en_NV_Item_Last_Imsi, pstLastImsi, ulLength);

    if (NV_OK != ulResult)
    {
        return MMA_FAILURE;
    }

    return MMA_SUCCESS;
}


VOS_VOID TAF_MMA_ReadSimPersonalisationPwdNvim( VOS_VOID )
{
    VOS_UINT8                           aucPwd[TAF_PH_ME_PERSONALISATION_PWD_LEN_MAX +1];
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulLength;

    ulLength = 0;

    PS_MEM_SET(aucPwd, 0x00, sizeof(aucPwd));
    (VOS_VOID)NV_GetLength(en_NV_Item_Sim_Personalisation_Pwd, &ulLength);

    ulResult = NV_Read(en_NV_Item_Sim_Personalisation_Pwd,
                     aucPwd,
                     ulLength);

    if (NV_OK != ulResult)
    {
        return;
    }

    PS_MEM_CPY(g_MmaNewValue.aucPwd, aucPwd, TAF_PH_ME_PERSONALISATION_PWD_LEN_MAX);

    return;
}




VOS_VOID TAF_MMA_ReadLcCtrlNvim( VOS_VOID )
{
    TAF_SDC_LC_CONFIG_PARA_STRU        *pstLcConfigInfo = VOS_NULL_PTR;
    TAF_NV_LC_CTRL_PARA_STRU            stLcCtrlInfo;
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulLength;

    ulLength        = 0;
    pstLcConfigInfo = TAF_SDC_GetLcConfigPara();

    PS_MEM_SET(&stLcCtrlInfo, 0x00, sizeof(TAF_NV_LC_CTRL_PARA_STRU));

    (VOS_VOID)NV_GetLength(en_NV_Item_LC_Ctrl_PARA, &ulLength);

    ulResult = NV_Read(en_NV_Item_LC_Ctrl_PARA,
                       &stLcCtrlInfo,
                       ulLength);

    if (NV_OK != ulResult)
    {
        return;
    }

    /* NV �����쳣���,��������쳣�����޸ĵ�ǰLCֵ */
    if ( (VOS_TRUE                      != stLcCtrlInfo.ucLCEnableFlg)
      && (VOS_FALSE                     != stLcCtrlInfo.ucLCEnableFlg) )
    {
        return;
    }

    if ( (TAF_NVIM_LC_RAT_COMBINED_GUL  != stLcCtrlInfo.enRatCombined)
      && (TAF_NVIM_LC_RAT_COMBINED_CL   != stLcCtrlInfo.enRatCombined)
      && (TAF_NVIM_LC_RAT_COMBINED_BUTT != stLcCtrlInfo.enRatCombined))
    {
        return;
    }

    if ( (TAF_NVIM_LC_INDEPENT_WORK     != stLcCtrlInfo.enLCWorkCfg)
      && (TAF_NVIM_LC_INTER_WORK        != stLcCtrlInfo.enLCWorkCfg)
      && (TAF_NVIM_LC_WORK_CFG_BUTT     != stLcCtrlInfo.enLCWorkCfg) )
    {
        return;
    }

    pstLcConfigInfo->ucLCEnableFlg = stLcCtrlInfo.ucLCEnableFlg;
    pstLcConfigInfo->enRatCombined = stLcCtrlInfo.enRatCombined;
    pstLcConfigInfo->enLCWorkCfg   = stLcCtrlInfo.enLCWorkCfg;

    return;
}



VOS_VOID TAF_MMA_WritePlmnSelectionModeNvim(VOS_UINT8 ucReselMode)
{
    NAS_NVIM_SELPLMN_MODE_STRU          stPlmnSelMode;
    VOS_UINT32                          ulNvLength;

    ulNvLength                  = 0;
    stPlmnSelMode.usSelPlmnMode = ucReselMode;

    (VOS_VOID)NV_GetLength(en_NV_Item_SelPlmn_Mode, &ulNvLength);

    if (NV_OK != NV_Write(en_NV_Item_SelPlmn_Mode,
                      &stPlmnSelMode,
                      ulNvLength))
    {
        MN_WARN_LOG("TAF_MMA_WritePlmnSelectionModeNvim:WARNING:  read en_NV_Item_SelPlmn_Mode fail");
    }

    return;
}
VOS_VOID TAF_MMA_UpdateUeBandNvim()
{
    TAF_USER_SET_PREF_BAND64            stOrigUserSetGuBand;
    VOS_UINT32                          ulBand;
    TAF_MMA_USER_BAND_SET_UN            uUserSetBand;
    TAF_MMA_UE_SUPPORT_FREQ_BAND_STRU   stSetBand;
    TAF_MMA_UE_SUPPORT_FREQ_BAND_STRU   stUeOrigSupportFreqBand;
    TAF_MMA_USER_BAND_SET_UN            uUeOrigSupportFreqBand;

    PS_MEM_SET(&stOrigUserSetGuBand, 0x00, sizeof(stOrigUserSetGuBand));
    PS_MEM_SET(&ulBand, 0x00, sizeof(ulBand));
    PS_MEM_SET(&uUserSetBand, 0x00, sizeof(uUserSetBand));
    PS_MEM_SET(&stSetBand, 0x00, sizeof(stSetBand));
    PS_MEM_SET(&stUeOrigSupportFreqBand, 0x00, sizeof(stUeOrigSupportFreqBand));
    PS_MEM_SET(&uUeOrigSupportFreqBand, 0x00, sizeof(uUeOrigSupportFreqBand));


    /* ��NV8265��stOrigUserSetGuBand�� */
    TAF_MMA_ReadUserSettedBandNvim();

    MN_MMA_Convert64BitBandTo32Bit(&(TAF_MMA_GetLastSyscfgSetAddr()->stUserSetBand.stOrigUserSetGuBand),
                                   &ulBand);

    MN_MMA_ConvertGUFrequencyBand(&ulBand);
    uUserSetBand.ulPrefBand = ulBand;

    /* ��NV8229��stUeOrigSupportFreqBand�� */
    TAF_MMA_ReadFreqBandNvim();

    /*����ǰϵͳ���õ�Ƶ��ת��Ϊ�û����õĸ�ʽ*/
    MMA_SwitchUESupportBand2UserSetBand(TAF_MMA_GetLastSyscfgSetAddr()->stUserSetBand.uUserSetUeFormatGuBand,
                                        &uUeOrigSupportFreqBand);

    /* ����û�����Ƶ�Ρ���ƵƵ�ν�����NV 8229ֵ��ͬ����ֱ�ӷ��ز���ҪдNV */
    if (uUserSetBand.ulPrefBand != uUeOrigSupportFreqBand.ulPrefBand)
    {
        MMA_SwitchUserSetBand2UESupportBand(uUserSetBand, &stSetBand);

        /* дNV:en_NV_Item_Support_Freqbands,����ȫ�ֱ��� */
        TAF_MMA_UpdateSupportFreqBand(&stSetBand);
    }

    /*��ForbBandNV����,����Ƶ�μ��� ����NV��*/
    if (NV_ITEM_ACTIVE == gstMmaForbBand.ucActiveFlag)
    {
        if (VOS_FALSE == gstMmaForbBand.ucForbStatus)
        {
            /*���ݽ�ֹƵ�ε���Ϣ����FreqBandNV��UsersetBandNV*/
            MMA_UpdateBandNvRefForbBand();

            /*���½�ֹƵ�ε�StatusΪTRUE 1*/
            MMA_UpdateForbBandStatusToNV();
        }
    }

    return;
}



#if (FEATURE_ON == FEATURE_LTE)


VOS_VOID TAF_MMA_UpdateUserSetLteBands()
{
    TAF_USER_SET_PREF_BAND64           *pstUeSupportLteBand = VOS_NULL_PTR;
    TAF_USER_SET_PREF_BAND64           *pstUserSetLteBand   = VOS_NULL_PTR;    
    TAF_USER_SET_PREF_BAND64            stDestUserSetLteBand;
    
    pstUeSupportLteBand = TAF_MMA_GetUeSupportLteBandAddr();
    pstUserSetLteBand   = TAF_MMA_GetUserSetLteBandAddr();

    /* �û����õ�NVȡ9017��NV:D22C�е���֧�ֵ�Ƶ�ν��� */
    stDestUserSetLteBand.ulBandLow  = (pstUeSupportLteBand->ulBandLow)  & (pstUserSetLteBand->ulBandLow);
    stDestUserSetLteBand.ulBandHigh = (pstUeSupportLteBand->ulBandHigh) & (pstUserSetLteBand->ulBandHigh);

    TAF_MMA_UpdateLteBandToNvim(&stDestUserSetLteBand, pstUserSetLteBand);
    
    return;
}

#endif

/* Added by y00307564 for CDMA 1X Iteration 6, 2014-12-29, begin */
/*****************************************************************************
 �� �� ��  : TAF_MMA_ReadCFreqLockNvim
 ��������  : ��ȡ1X/EVDO����Ƶ��Ϣ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��27��
    ��    ��   : y00307564
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_MMA_ReadCFreqLockNvim(VOS_VOID)
{
    VOS_UINT32                          ulResult;
    TAF_MMA_CFREQ_LOCK_SET_PARA_STRU   *pstTafMmaCFreqLockPara;

    pstTafMmaCFreqLockPara = TAF_MMA_GetCFreqLockSetPara();

    ulResult = NV_Read(en_NV_Item_CFreqLock_CFG,
                       pstTafMmaCFreqLockPara,
                       sizeof(TAF_NVIM_CFREQ_LOCK_CFG_STRU));

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-8, begin */
    TAF_MMA_LogReadNVInfo(en_NV_Item_CFreqLock_CFG,
                          sizeof(TAF_NVIM_CFREQ_LOCK_CFG_STRU),
                          WUEPS_PID_MMA,
                          (VOS_UINT8 *)pstTafMmaCFreqLockPara);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-8, end */

    if (NV_OK != ulResult)
    {
        /* ��ȡNVʧ�ܣ�������Ƶ���� */
        PS_MEM_SET(pstTafMmaCFreqLockPara, 0x0, sizeof(TAF_NVIM_CFREQ_LOCK_CFG_STRU));
        pstTafMmaCFreqLockPara->enFreqLockMode = TAF_MMA_CFREQ_LOCK_MODE_OFF;
    }

    return;
}
/* Added by y00307564 for CDMA 1X Iteration 6, 2014-12-29, end */


VOS_VOID TAF_MMA_ReadCcpuResetRecordNvim(VOS_VOID)
{
    VOS_UINT32                          ulLength;
    TAF_NVIM_CCPU_RESET_RECORD_STRU     stCcpuResetRecord;

    ulLength = 0;
    PS_MEM_SET(&stCcpuResetRecord, 0x00, sizeof(TAF_NVIM_CCPU_RESET_RECORD_STRU));

    (VOS_VOID)NV_GetLength(en_NV_Item_Ccpu_Reset_Record, &ulLength);
    if (ulLength > sizeof(TAF_NVIM_CCPU_RESET_RECORD_STRU))
    {
        return;
    }

    /* NV��ȡʧ�ܣ���Ĭ��ֵ���� */
    if (NV_OK != NV_Read(en_NV_Item_Ccpu_Reset_Record, &stCcpuResetRecord, ulLength))
    {
        MMA_WARNINGLOG("TAF_MMA_ReadCcpuResetRecordNvim():WARNING:NV Read failed.");

        return;
    }

    if (VOS_TRUE == stCcpuResetRecord.ucCcpuResetFlag)
    {
        NAS_TRACE_HIGH("Ccpu Reseting! ");

        TAF_MMA_SetCcpuResetFlag(VOS_TRUE);
    }

    if (0 == stCcpuResetRecord.ucReserved1)
    {
        TAF_MMA_SetTestRoamFlag(VOS_FALSE);
    }
    else
    {
        TAF_MMA_SetTestRoamFlag(VOS_TRUE);

        if (0 != stCcpuResetRecord.ucReserved2)
        {
            TAF_MMA_SetWaitExtTimerLen(stCcpuResetRecord.ucReserved2);
        }
    }


    return;
}
VOS_VOID TAF_MMA_ReadGetGeoCfgInfoNvim(VOS_VOID)
{
    TAF_MMA_GET_GEO_CTX_STRU                               *pstGetGeoCtx = VOS_NULL_PTR;
    NAS_NVIM_GET_GEO_CFG_INFO_STRU                          stGetGeoCfgInfo;
    VOS_UINT32                                              ulLength;

    ulLength     = 0;
    pstGetGeoCtx = TAF_MMA_GetGeoCtxAddr();
    PS_MEM_SET(&stGetGeoCfgInfo, 0x00, sizeof(NAS_NVIM_GET_GEO_CFG_INFO_STRU));

    (VOS_VOID)NV_GetLength(en_NV_Item_Get_Geo_Cfg_Info, &ulLength);

    if (ulLength > sizeof(NAS_NVIM_GET_GEO_CFG_INFO_STRU))
    {
        return;
    }

    /* ��ȡ��ȡ������������Ϣ��NV */
    if (NV_OK != NV_Read(en_NV_Item_Get_Geo_Cfg_Info, &stGetGeoCfgInfo, ulLength))
    {
        return;
    }

    /* ����ù��ܹرգ��򶼰�Ĭ��ֵ���� */
    if (VOS_TRUE != stGetGeoCfgInfo.ucActiveFlag)
    {
        return;
    }

    /* AUSTIN C10���⿨�򲻿���GET GEO����:CSSû��ʵ��DSDS,����ռRF�����µײ�RF�쳣 */
    if (VOS_TRUE == USIMM_VsimIsActive())
    {
        pstGetGeoCtx->stGetGeoNvCfg.ucCfgGetGeoFlag = VOS_FALSE;
        MMA_WARNINGLOG("TAF_MMA_ReadGetGeoCfgInfoNvim: Is virtual sim!");
        
        return;
    }

    pstGetGeoCtx->stGetGeoNvCfg.ucCfgGetGeoFlag = VOS_TRUE;

    /* ���NV���õ�ʱ��Ϊ0����Ĭ��ֵ���� */
    /* NV���õĻ�ȡ�����붨ʱ��ʱ����λ���룬ȫ�ֱ�����Ļ�ȡ�����붨ʱ��ʱ����λ�Ǻ��� */
    if (0 != stGetGeoCfgInfo.ucGetGeoTimerlen)
    {
        /* ��ת���ɺ���󣬴���ȫ�ֱ��� */
        pstGetGeoCtx->stGetGeoNvCfg.ulGetGeoTimerLen = stGetGeoCfgInfo.ucGetGeoTimerlen * NAS_SDC_ONE_THOUSAND_MILLISECOND;
    }

    /* ���NV���õ�ʱ��Ϊ0����Ĭ��ֵ���� */
    /* NV���õĹ�������Чʱ����λ�Ƿ��ӣ�ȫ�ֱ�����Ĺ�������Чʱ����λ���� */
    if (0 != stGetGeoCfgInfo.ulGeoEffectiveTimeLen)
    {
        /* ����ת������󣬴���ȫ�ֱ��� */
        pstGetGeoCtx->stGetGeoNvCfg.ulGeoEffectiveTimeLen = stGetGeoCfgInfo.ulGeoEffectiveTimeLen * NAS_MML_SIXTY_SECOND;
    }

    return;
}


#if (FEATURE_IMS == FEATURE_ON)
VOS_UINT32 TAF_MMA_UpdataVoiceDomainNv(
    VOS_UINT32                          ulVoiceDomain
)
{
    VOS_UINT32                          ulLength;
    LNAS_LMM_NV_VOICE_DOMAIN_STRU       stVoiceDomain;

    /* �Ȼ�ȡNV�ĳ��� */
    ulLength = 0;
    NV_GetLength(EN_NV_ID_UE_VOICE_DOMAIN, &ulLength);

    if (ulLength > sizeof(LNAS_LMM_NV_VOICE_DOMAIN_STRU))
    {
        return VOS_FALSE;
    }

    /* ��NV��EN_NV_ID_UE_VOICE_DOMAIN��ʧ�ܣ�ֱ�ӷ��� */
    if (NV_OK != NV_Read(EN_NV_ID_UE_VOICE_DOMAIN,
                         &stVoiceDomain, ulLength))
    {
        return VOS_FALSE;
    }

    stVoiceDomain.enVoicDomain  = (NAS_LMM_VOICE_DOMAIN_ENUM_UINT32)ulVoiceDomain;

    if (NV_OK != NV_Write(EN_NV_ID_UE_VOICE_DOMAIN,
                          &stVoiceDomain, ulLength))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_UpdateLteImsSupportNv(
    VOS_UINT8                           ucFlag
)
{
    VOS_UINT32                          ulLength;
    IMSA_NV_IMS_RAT_SUPPORT_STRU        stImsSupport;

    /* �Ȼ�ȡNV�ĳ��� */
    ulLength = 0;
    NV_GetLength(EN_NV_ID_IMS_RAT_SUPPORT, &ulLength);

    if (ulLength > sizeof(IMSA_NV_IMS_RAT_SUPPORT_STRU))
    {
        return VOS_FALSE;
    }

    /* ��NV��EN_NV_ID_IMS_RAT_SUPPORT��ʧ�ܣ�ֱ�ӷ��� */
    if (NV_OK != NV_Read(EN_NV_ID_IMS_RAT_SUPPORT,
                         &stImsSupport, ulLength))
    {
        return VOS_FALSE;
    }

    stImsSupport.ucLteImsSupportFlag    = ucFlag;
    stImsSupport.ucLteEmsSupportFlag    = ucFlag;

    if (NV_OK != NV_Write(EN_NV_ID_IMS_RAT_SUPPORT,
                          &stImsSupport, ulLength))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

#endif


VOS_VOID TAF_MMA_ReadPlatformRatCap(VOS_VOID)
{
    TAF_SDC_PLATFORM_RAT_CAP_STRU                          *pstPlatformRatCap = VOS_NULL_PTR;
    VOS_UINT32                                              i;
    VOS_UINT32                                              j;
    PLATAFORM_RAT_CAPABILITY_STRU                           stNvPlatformRatCap;
    TAF_SDC_PLATFORM_RAT_TYPE_ENUM_UINT8                    enTafSdcPlatformRat;

    pstPlatformRatCap = TAF_SDC_GetPlatformRatCap();

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    /* ��ʼ��ΪCDMA 1X + GSM ONLY */
    pstPlatformRatCap->ucRatNum      = 2;
    pstPlatformRatCap->aenRatList[0] = TAF_SDC_PLATFORM_RAT_1X;
    pstPlatformRatCap->aenRatList[1] = TAF_SDC_PLATFORM_RAT_GSM;
    for (i = 2; i < TAF_SDC_PLATFORM_MAX_RAT_NUM; i++)
    {
        pstPlatformRatCap->aenRatList[i] = TAF_SDC_PLATFORM_RAT_BUTT;
    }
#else
    /* ��ʼ��ΪGSM ONLY */
    pstPlatformRatCap->ucRatNum      = 1;
    pstPlatformRatCap->aenRatList[0] = TAF_SDC_PLATFORM_RAT_GSM;
    for (i = 1; i < TAF_SDC_PLATFORM_MAX_RAT_NUM; i++)
    {
        pstPlatformRatCap->aenRatList[i] = TAF_SDC_PLATFORM_RAT_BUTT;
    }
#endif

    /* ��ȡNV, �����ȡʧ�ܣ�ֱ�ӷ��أ�Ĭ��ֵ����Ϊ��֧��GSM */
    PS_MEM_SET(&stNvPlatformRatCap, 0x0, sizeof(stNvPlatformRatCap));
    if (NV_OK != NV_Read(en_NV_Item_Platform_RAT_CAP,
                         &stNvPlatformRatCap, sizeof(PLATAFORM_RAT_CAPABILITY_STRU)))
    {
        TAF_ERROR_LOG(WUEPS_PID_MMC, "TAF_MMA_ReadPlatformRatCap():ERROR: read en_NV_Item_PLATFORM_RAT_CAP Error");

        return;
    }

    if (stNvPlatformRatCap.usRatNum >= PLATFORM_MAX_RAT_NUM)
    {
        stNvPlatformRatCap.usRatNum = PLATFORM_MAX_RAT_NUM;
    }

    /* ��Ч�Լ�飺��Ч��ֱ�ӷ��أ�Ĭ��ֵ����Ϊ��֧��GSM */
    if (VOS_FALSE == TAF_SDC_IsPlatformRatCapNvimValid(&stNvPlatformRatCap))
    {
        TAF_ERROR_LOG(WUEPS_PID_MMC, "TAF_MMA_ReadPlatformRatCap():ERROR: en_NV_Item_PLATFORM_RAT_CAP Invalid");

        return;
    }

    j = 0;

    /* ��ȡ�ɹ�����NV�ж�ȡֵ��ֵ��pstPlatformRatCap */
    for (i = 0; i < stNvPlatformRatCap.usRatNum; i++)
    {
        enTafSdcPlatformRat = TAF_SDC_ConvertNvPlatformRatToTafType(stNvPlatformRatCap.aenRatList[i]);
        if (TAF_SDC_PLATFORM_RAT_BUTT != enTafSdcPlatformRat)
        {
            pstPlatformRatCap->aenRatList[j] = enTafSdcPlatformRat;
            j ++;
        }
    }

    /* ����д�NV�л�ȡƽ̨֧�ֽ��뼼������Ҫ����֧�ֵĸ��������򲻸��£���Ȼ���ճ�ʼֵ1 */
    if (j > 0)
    {
        pstPlatformRatCap->ucRatNum      = (VOS_UINT8)j;
    }

    return;
}

/* Added by l00305157 for Service_State_Optimize_PhaseII, 2015-02-11, begin */
/*****************************************************************************
 �� �� ��  : TAF_MMA_ReadDelayReportServiceStatusCfgNvim
 ��������  : ��NV�л�ȡ���ݵ�����ʾ�Ż���������Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��11��
    ��    ��   : l00305157
    �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�
*****************************************************************************/
VOS_VOID TAF_MMA_ReadDelayReportServiceStatusCfgNvim(VOS_VOID)
{
    TAF_MMA_NVIM_DELAY_REPORT_SERVICE_STATUS_STRU                 stDelayReportServiceStatusCfg;

    PS_MEM_SET(&stDelayReportServiceStatusCfg, 0x00, sizeof(TAF_MMA_NVIM_DELAY_REPORT_SERVICE_STATUS_STRU));

    TAF_MMA_SetDelayReportServiceStatusFlg(VOS_FALSE);
    TAF_MMA_SetDelayReportServiceStatusTimerLen(0);

    if (NV_OK != NV_Read(en_NV_Item_DELAY_REPORT_SERVICE_STATUS_CFG,
                        (VOS_VOID *)&stDelayReportServiceStatusCfg, 
                        sizeof(TAF_MMA_NVIM_DELAY_REPORT_SERVICE_STATUS_STRU)))
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,"TAF_MMA_ReadDelayReportServiceStatusCfgNvim: return error");
        return;
    }

    if (VOS_TRUE == stDelayReportServiceStatusCfg.ucEnable)
    {
        TAF_MMA_SetDelayReportServiceStatusFlg(VOS_TRUE);
        TAF_MMA_SetDelayReportServiceStatusTimerLen(stDelayReportServiceStatusCfg.ulRptSrvStaDelayTimerValue*NAS_SDC_ONE_THOUSAND_MILLISECOND);
        return;
    }
    return;
}
/* Added by l00305157 for Service_State_Optimize_PhaseII, 2015-02-11, begin */
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/* Added by y00322978 for CDMA 1X Iteration 17, 2015-8-22, begin */
/*****************************************************************************
 �� �� ��  : TAF_MMA_ReadEsnFromNvim
 ��������  : ��ά�ɲ��ȡnv�ϱ� esn��Ϣ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��22��
    ��    ��   : y00322978
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_ReadEsnFromNvim( VOS_VOID )
{
    VOS_INT32                           lIndex;
    TAF_SDC_SYS_INFO_STRU              *pstSysInfo = VOS_NULL_PTR;
    NV_PESN_STRU                        stPesn;

    pstSysInfo = TAF_SDC_GetSysInfo();

    if (NV_OK != NV_Read(en_NV_Item_PESN, &stPesn, sizeof(NV_PESN_STRU)))
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_ReadEsnAndMeidNvim:Read Nvim Failed");
        return;
    }

    if (VOS_FALSE == TAF_MMA_IsPesnValid(&stPesn))
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_ReadEsnAndMeidNvim: read Nvim succ, but nvim is invalid");
        return;
    }

    TAF_MMA_LogReadNVInfo(en_NV_Item_PESN,
                          sizeof(NV_PESN_STRU),
                          WUEPS_PID_MMA,
                          (VOS_UINT8 *)&stPesn);

    /* Read from high to low */
    for (lIndex = (PESN_NV_DATA_LEN - 1); lIndex >= 0; lIndex--)
    {
        /* Update the current value */
        pstSysInfo->ulEsn <<= sizeof(stPesn.aucPEsn[0]) * 8;

        /* Add lower bits */
        pstSysInfo->ulEsn |= stPesn.aucPEsn[lIndex];
    }
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_ReadMeidFromNvim
 ��������  : ��ά�ɲ��ȡnv�ϱ� meid��Ϣ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��22��
    ��    ��   : y00322978
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_ReadMeidFromNvim( VOS_VOID )
{
    TAF_SDC_SYS_INFO_STRU              *pstSysInfo = VOS_NULL_PTR;
    NV_MEID_STRU                        stMeid;

    pstSysInfo = TAF_SDC_GetSysInfo();

    if (NV_OK != NV_Read(en_NV_Item_MEID, &stMeid, sizeof(NV_MEID_STRU)))
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_ReadEsnAndMeidNvim:Read Nvim Failed");
        return;
    }

    if (VOS_FALSE == TAF_MMA_IsMeidValid(&stMeid))
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_ReadEsnAndMeidNvim: read Nvim succ, but nvim is invalid");
        return;
    }

    TAF_MMA_LogReadNVInfo(en_NV_Item_MEID,
                          sizeof(NV_MEID_STRU),
                          WUEPS_PID_MMA,
                          (VOS_UINT8 *)&stMeid);

    PS_MEM_CPY(pstSysInfo->aucMeId, stMeid.aucMeID, MEID_NV_DATA_LEN_NEW);
}

/* Added by y00322978 for CDMA 1X Iteration 17, 2015-8-22, end */
#endif

/*****************************************************************************
 �� �� ��  : TAF_MMA_ReadNonnormalRegStatusMergeCfgNvim
 ��������  : ��NV��ȡ�����������ϱ�ע��״̬�ı�����
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��28��
    ��    ��   : z00359541
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_ReadNonnormalRegStatusMergeCfgNvim( VOS_VOID )
{
    TAF_SDC_NONNORMAL_REG_STATUS_MERGE_CFG_STRU            *pstNonnormalRegStatusMergeCfg = VOS_NULL_PTR;
    TAF_NVIM_NONNORMAL_REG_STATUS_MERGE_CFG_STRU            stNonnormalRegStatusMergeCfg;

    pstNonnormalRegStatusMergeCfg = TAF_SDC_GetNonnormalRegStatusMergeCfg();

    PS_MEM_SET(&stNonnormalRegStatusMergeCfg, 0X00, sizeof(TAF_NVIM_NONNORMAL_REG_STATUS_MERGE_CFG_STRU));

    /* ���Կ�����Ч */
    if (VOS_TRUE  == NAS_USIMMAPI_IsTestCard())
    {
        TAF_NORMAL_LOG(WUEPS_PID_MMC, "TAF_MMA_ReadNonnormalRegStatusMergeCfgNvim():Test SIM, Config Invalid");
        return;
    }

    if (NV_OK != NV_Read(en_NV_Item_NONNORMAL_REG_STATUS_MERGE_CFG, &stNonnormalRegStatusMergeCfg, sizeof(TAF_NVIM_NONNORMAL_REG_STATUS_MERGE_CFG_STRU)))
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_ReadNonnormalRegStatusMergeCfgNvim:Read Nvim Failed");
        return;
    }

    TAF_MMA_LogReadNVInfo(en_NV_Item_NONNORMAL_REG_STATUS_MERGE_CFG,
                          sizeof(TAF_NVIM_NONNORMAL_REG_STATUS_MERGE_CFG_STRU),
                          WUEPS_PID_MMA,
                          (VOS_UINT8 *)&stNonnormalRegStatusMergeCfg);

    if (VOS_FALSE == stNonnormalRegStatusMergeCfg.ucMergeFlg)
    {
        pstNonnormalRegStatusMergeCfg->ucMergeFlg = VOS_FALSE;
        
        TAF_NORMAL_LOG(WUEPS_PID_MMC, "TAF_MMA_ReadNonnormalRegStatusMergeCfgNvim():ucMergeFlg = false");
        return;
    }

    pstNonnormalRegStatusMergeCfg->ucMergeFlg = VOS_TRUE;
    TAF_NORMAL_LOG(WUEPS_PID_MMC, "TAF_MMA_ReadNonnormalRegStatusMergeCfgNvim():ucMergeFlg = true");

    return;
}

/*lint -restore */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



