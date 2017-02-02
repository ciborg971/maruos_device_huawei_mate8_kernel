


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "NasEmmSecuInclude.h"
#include    "NasLmmPubMPrint.h"
#include    "NasEmmTauSerInclude.h"
#include    "NasEmmAttDetInclude.h"

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASEMMSECUSMC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASEMMSECUSMC_C
/*lint +e767*/


/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/
VOS_UINT8                           g_aucEia0Kasme[NAS_LMM_SECU_AUTH_KEY_ASME_LEN] = {
        0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x66,
        0x19,0x84,0x05,0x14,0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x66,
        0x66,0x66,0x66,0x66,};

/*****************************************************************************
  3 Function
*****************************************************************************/


VOS_VOID  NAS_EMM_DeriveNewNasKey(      VOS_UINT8  *pucKasme,
                                        VOS_UINT8   ucEca,
                                        VOS_UINT8   ucEia)
{
    VOS_UINT32                          ulRslt = NAS_EMM_SECU_FAIL;

    NAS_EMM_SECU_LOG_INFO("NAS_EMM_DeriveNewNasKey entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_DeriveNewNasKey_ENUM,LNAS_ENTRY);

    /*����NasCk*/
    ulRslt = NAS_EMM_ComputeNasKey(     pucKasme,
                                        NAS_EMM_GetSecuTempNasCkAddr(),
                                        NAS_EMM_SECU_CIPHER_KEY,
                                        ucEca);
    if(NAS_EMM_SECU_FAIL == ulRslt)
    {
        NAS_EMM_SECU_LOG_ERR("NAS_EMM_DeriveNewNasKey:Compute NasCK Err.");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_DeriveNewNasKey_ENUM,LNAS_FUNCTION_LABEL1);
    }

    /*����NasIk*/
    ulRslt = NAS_EMM_ComputeNasKey(     pucKasme,
                                        NAS_EMM_GetSecuTempNasIkAddr(),
                                        NAS_EMM_SECU_INTEGRITY_KEY,
                                        ucEia);
    if(NAS_EMM_SECU_FAIL == ulRslt)
    {
        NAS_EMM_SECU_LOG_ERR("NAS_EMM_DeriveNewNasKey:Compute NasIK Err.");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_DeriveNewNasKey_ENUM,LNAS_FUNCTION_LABEL2);
    }

    return;
}


VOS_UINT32  NAS_EMM_ComputeNasKey(  VOS_UINT8  *pucKasme,
                                    VOS_UINT8  *pNasK,
                                    NAS_EMM_SECU_NAS_KEY_TYPE_ENUM_UINT8 enNasKeyType,
                                    VOS_UINT8   enProtAlgoType)
{
    VOS_UINT8                       aucAlgParam[NAS_EMM_SECU_MAX_ALG_PARAM_LEN];
    VOS_UINT8                       aucKeyParam[NAS_LMM_SECU_AUTH_KEY_ASME_LEN];
    VOS_UINT32                      ulIndex = 0;
    VOS_UINT32                      ulRslt = NAS_EMM_SECU_FAIL;

    NAS_EMM_SECU_LOG_INFO("NAS_EMM_ComputeNasKey entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_ComputeNasKey_ENUM,LNAS_ENTRY);


    if(VOS_NULL_PTR == pucKasme)
    {
        NAS_EMM_SECU_LOG_ERR("NAS_EMM_ComputeNasKey:-> pucKasme is null.");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_ComputeNasKey_ENUM,LNAS_NULL_PTR);
        return NAS_EMM_SECU_FAIL;
    }

    /* ����KDF�㷨��Ҫ�Ĳ��� */

    /*encode FC*/
    aucAlgParam[ulIndex++]          = NAS_EMM_SECU_ALG_PARAM_NAS_KEY_FC;

    if (NAS_EMM_SECU_CIPHER_KEY == enNasKeyType)
    {
        /* encode distinguisher */
        aucAlgParam[ulIndex++]      = NAS_EMM_SECU_ALG_PARAM_CK_DISTINGUISHER;

        aucAlgParam[ulIndex++]      = NAS_EMM_SECU_ALG_PARAM_KASME_PRE_LEN;
        aucAlgParam[ulIndex++]      = NAS_EMM_SECU_ALG_PARAM_DISTINGUISHER_LEN;

        /* encode algorithm identity */
        aucAlgParam[ulIndex++] = enProtAlgoType;

        aucAlgParam[ulIndex++]     = NAS_EMM_SECU_ALG_PARAM_KASME_PRE_LEN;
        aucAlgParam[ulIndex++]     = NAS_EMM_SECU_ALG_PARAM_IDENTITY_LEN;
    }
    else
    {
        /* encode distinguisher */
        aucAlgParam[ulIndex++]     = NAS_EMM_SECU_ALG_PARAM_IK_DISTINGUISHER;

        aucAlgParam[ulIndex++]     = NAS_EMM_SECU_ALG_PARAM_KASME_PRE_LEN;
        aucAlgParam[ulIndex++]     = NAS_EMM_SECU_ALG_PARAM_DISTINGUISHER_LEN;

        /* encode algorithm identity */
        aucAlgParam[ulIndex++] = enProtAlgoType;

        aucAlgParam[ulIndex++]     = NAS_EMM_SECU_ALG_PARAM_KASME_PRE_LEN;
        aucAlgParam[ulIndex++]     = NAS_EMM_SECU_ALG_PARAM_IDENTITY_LEN;
    }

    ulRslt = NAS_EMM_KDF_HmacSha256(aucAlgParam,ulIndex,pucKasme,aucKeyParam);

    if (NAS_EMM_SECU_SUCC == ulRslt)
    {
        PS_GetLeastSignBitsByTrunc(aucKeyParam,pNasK);
        return NAS_EMM_SECU_SUCC;
    }
    else
    {
        NAS_EMM_SECU_LOG_ERR("NAS_EMM_ComputeNasKey->PS_KDF_HmacSha256 run Fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_ComputeNasKey_ENUM,LNAS_FAIL);
        return NAS_EMM_SECU_FAIL;
    }
}


/*lint -e960*/
/*lint -e961*/
VOS_VOID  NAS_EMM_UpdateCurSecuCntxt(VOS_VOID)
{
    NAS_EMM_SECU_LOG_INFO("NAS_EMM_UpdateCurSecuCntxt enterd.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_UpdateCurSecuCntxt_ENUM,LNAS_ENTRY);

    /*�� new mapped secu cntxt����Ϊ��ǰ��ȫ������*/
    if(NAS_EMM_SMC_UPDATE_NEW_MAPPED == NAS_EMM_GetSmcType())
    {
        NAS_EMM_SetSecuCurKSIasme(NAS_LMM_NKSI_NO_KEY_IS_AVAILABLE);
        NAS_EMM_SetSecuCurKSIsgsn(NAS_EMM_GetSecuNewMappedKSIsgsn());
        NAS_LMM_MEM_CPY(                NAS_EMM_GetSecuCurKasmeAddr(),
                                        NAS_EMM_GetSecuNewMappedKasmeAddr(),
                                        NAS_LMM_SECU_AUTH_KEY_ASME_LEN);


        /* ��� new mapped security context */
        /* NAS_EMM_ClearNewMappedSecuCntxt(); */
    }
    /*�� new native secu cntxt����Ϊ��ǰ��ȫ������*/
    else if(NAS_EMM_SMC_UPDATE_NEW_NATIVE == NAS_EMM_GetSmcType())
    {
        NAS_EMM_SetSecuCurKSIsgsn(NAS_LMM_NKSI_NO_KEY_IS_AVAILABLE);
        NAS_EMM_SetSecuCurKSIasme(NAS_EMM_GetSecuNewNativeKSIasme());
        NAS_LMM_MEM_CPY(                NAS_EMM_GetSecuCurKasmeAddr(),
                                        NAS_EMM_GetSecuNewNativeKasmeAddr(),
                                        NAS_LMM_SECU_AUTH_KEY_ASME_LEN);
        /*��� new native security context*/
        NAS_EMM_ClearNewNativeSecuCntxt();

        /*��� new mapped security context*/
        NAS_EMM_ClearNewMappedSecuCntxt();

    }
    /*�� non-current native secu cntxt����Ϊ��ǰ��ȫ������*/
    else
    {
        NAS_EMM_SetSecuCurKSIsgsn(NAS_LMM_NKSI_NO_KEY_IS_AVAILABLE);
        NAS_EMM_SetSecuCurKSIasme(NAS_EMM_GetSecuNonCurNativeKSIasme());
        NAS_LMM_MEM_CPY(                NAS_EMM_GetSecuCurKasmeAddr(),
                                        NAS_EMM_GetSecuNonCurNativeKasmeAddr(),
                                        NAS_LMM_SECU_AUTH_KEY_ASME_LEN);
        /*��� non-current native security context*/
        NAS_EMM_ClearNonCurNativeSecuCntxt();
    }


    NAS_EMM_SECU_LOG2_INFO("NAS_EMM_UpdateCurSecuCntxt: CurKSIasme = , CurKSIsgsn = .",
                        NAS_EMM_GetSecuCurKSIasme(),
                        NAS_EMM_GetSecuCurKSIsgsn());
    TLPS_PRINT2LAYER_INFO2(NAS_EMM_UpdateCurSecuCntxt_ENUM,LNAS_FUNCTION_LABEL1,
                        NAS_EMM_GetSecuCurKSIasme(),
                        NAS_EMM_GetSecuCurKSIsgsn());


   return;
}


VOS_UINT32 NAS_EMM_Eia0SmcVerifyKsi
(
    VOS_UINT8                           ucKsi
)
{
    VOS_UINT8                           ucKsiValue = NAS_EMM_NULL;
    VOS_UINT8                           ucKsiType  = NAS_EMM_NULL;

    NAS_EMM_SECU_LOG_INFO("NAS_EMM_Eia0SmcVerifyKsi enter.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_Eia0SmcVerifyKsi_ENUM,LNAS_ENTRY);

    /* ��ȡ KSI���ͺ� KSI ��ֵ*/
    ucKsiValue  = ucKsi & NAS_EMM_LOW_3_BITS_F;
    ucKsiType   = ucKsi>>NAS_EMM_SECU_KSI_TYPE_BIT_POS;
    if(NAS_LMM_NKSI_NO_KEY_IS_AVAILABLE == ucKsiValue)
    {
        NAS_EMM_SECU_LOG_ERR("NAS_EMM_Eia0SmcVerifyKsi:KSI is NO_KEY.");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_Eia0SmcVerifyKsi_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_EMM_SECU_FAIL;
    }

    /* Ϊ�˼��ݲ�ͬ���磬ʵ�п���ϳ�ԭ���ݲ��ж�KSI�Ƿ�Ϊ0 */
    if(0 != ucKsiValue)
    {
        NAS_EMM_SECU_LOG_ERR("NAS_EMM_Eia0SmcVerifyKsi:KSI is not zero.");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_Eia0SmcVerifyKsi_ENUM,LNAS_FUNCTION_LABEL2);
    }

    /* Ϊ�˼��ݲ�ͬ���磬ʵ�п���ϳ�ԭ���ݲ��ж��Ƿ�ΪNATIVE */
    if (NAS_EMM_SECU_KSI_TYPE_NATIVE != ucKsiType)
    {
        NAS_EMM_SECU_LOG_ERR("NAS_EMM_Eia0SmcVerifyKsi:KSI type is not native.");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_Eia0SmcVerifyKsi_ENUM,LNAS_FUNCTION_LABEL3);
    }

    NAS_EMM_SetSmcType(NAS_EMM_SMC_UPDATE_CUR);

    return  NAS_EMM_SECU_SUCC;
}
VOS_UINT32 NAS_EMM_NotEia0SmcVerifyKsi
(
    VOS_UINT8                           ucSqn,
    VOS_UINT8                           ucKsi
)
{
    VOS_UINT8                               ucKsiType;
    VOS_UINT8                               ucKsiValue;
    VOS_UINT32                              ulRslt;

    NAS_EMM_SECU_LOG_INFO("NAS_EMM_NotEia0SmcVerifyKsi enter.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_NotEia0SmcVerifyKsi_ENUM,LNAS_ENTRY);

    /* ��ȡ KSI���ͺ� KSI ��ֵ*/
    ucKsiType   = ucKsi>>NAS_EMM_SECU_KSI_TYPE_BIT_POS;
    ucKsiValue  = ucKsi&NAS_EMM_LOW_3_BITS_F;
    if(NAS_LMM_NKSI_NO_KEY_IS_AVAILABLE == ucKsiValue)
    {
        NAS_EMM_SECU_LOG_ERR("NAS_EMM_NotEia0SmcVerifyKsi:KSI is NO_KEY.");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_NotEia0SmcVerifyKsi_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_EMM_SECU_FAIL;
    }

    /* ���SMCЯ����KSIΪ native ����*/
    if(NAS_EMM_SECU_KSI_TYPE_NATIVE == ucKsiType)
    {
        NAS_EMM_SECU_LOG_NORM("NAS_EMM_NotEia0SmcVerifyKsi:KSI is Native.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_NotEia0SmcVerifyKsi_ENUM,LNAS_FUNCTION_LABEL2);
        ulRslt = NAS_EMM_SmcVerifyNativeKsi(ucKsiValue);
    }
    else/* ���SMCЯ����KSIΪ Mapped ����*/
    {
        NAS_EMM_SECU_LOG_NORM("NAS_EMM_NotEia0SmcVerifyKsi:KSI is Mapped.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_NotEia0SmcVerifyKsi_ENUM,LNAS_FUNCTION_LABEL3);
        ulRslt = NAS_EMM_SmcVerifyMappedKsi(ucSqn, ucKsiValue);
    }

    return ulRslt;
}
VOS_UINT32  NAS_EMM_SmcVerifyNativeKsi( VOS_UINT8 ucKsiValue)
{
    NAS_EMM_SECU_LOG1_INFO("NAS_EMM_SmcVerifyNativeKsi: ucKsiValue = ", ucKsiValue);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_SmcVerifyNativeKsi_ENUM,LNAS_FUNCTION_LABEL1,ucKsiValue);
    if(NAS_EMM_GetSecuNewNativeKSIasme() == ucKsiValue)
    {
        NAS_EMM_SetSmcType(NAS_EMM_SMC_UPDATE_NEW_NATIVE);
    }
    else if (NAS_EMM_GetSecuCurKSIasme() == ucKsiValue)
    {
        NAS_EMM_SetSmcType(NAS_EMM_SMC_UPDATE_CUR);
    }
    else if(NAS_EMM_GetSecuNonCurNativeKSIasme() == ucKsiValue)
    {
        NAS_EMM_SetSmcType(NAS_EMM_SMC_UPDATE_NON_CUR_NATIVE);
    }
    else
    {
        NAS_EMM_SECU_LOG_NORM("NAS_EMM_SmcVerifyNativeKsi: NAS_EMM_SECU_FAIL");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_SmcVerifyNativeKsi_ENUM,LNAS_FUNCTION_LABEL2);
        return  NAS_EMM_SECU_FAIL;
    }

    return  NAS_EMM_SECU_SUCC;
}


VOS_UINT32  NAS_EMM_SmcVerifyMappedKsi
(
    VOS_UINT8                           ucSqn,
    VOS_UINT8                           ucKsiValue
)
{
    /* ���SQN�պ�Ϊ0��GU��ѡ��Lʱ����TAU��Ϣ��current��ȫ�����ĵ�KSI��mapped cksn��ȣ�
       ����SMC��Ϣ�е�KSI���ڴ˶��ߣ�������ʹ��new mapped����˴�����Ϊ�˹��
       �����·�SMC��ϢʱUE�޷�����ʹ�����ף�������������ʱ����ʹ��new mapped */
    if(    (0 == ucSqn)
        && (NAS_EMM_GetSecuNewMappedKSIsgsn() == NAS_EMM_GetSecuCurKSIsgsn())
        && (NAS_EMM_GetSecuNewMappedKSIsgsn() == ucKsiValue)   )
    {
        NAS_EMM_SECU_LOG_NORM("NAS_EMM_SmcVerifyMappedKsi: Update New mapped security context.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_SmcVerifyMappedKsi_ENUM,LNAS_FUNCTION_LABEL1);
        NAS_EMM_SetSmcType(NAS_EMM_SMC_UPDATE_NEW_MAPPED);
        return NAS_EMM_SECU_SUCC;
    }

    /* ����������������������� */
    if (NAS_EMM_GetSecuCurKSIsgsn() == ucKsiValue)
    {
        NAS_EMM_SECU_LOG_NORM("NAS_EMM_SmcVerifyMappedKsi: Update current mapped security context.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_SmcVerifyMappedKsi_ENUM,LNAS_FUNCTION_LABEL2);
        NAS_EMM_SetSmcType(NAS_EMM_SMC_UPDATE_CUR);
    }
    else if(NAS_EMM_GetSecuNewMappedKSIsgsn() == ucKsiValue)
    {
        NAS_EMM_SetSmcType(NAS_EMM_SMC_UPDATE_NEW_MAPPED);
    }
    else
    {
        NAS_EMM_SECU_LOG_NORM("NAS_EMM_SmcVerifyMappedKsi:NAS_EMM_SECU_FAIL.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_SmcVerifyMappedKsi_ENUM,LNAS_FUNCTION_LABEL3);
        return  NAS_EMM_SECU_FAIL;
    }

    return  NAS_EMM_SECU_SUCC;
}
VOS_UINT32 NAS_EMM_Eia0SmcVerifyAlg( VOS_UINT8 ucSelEca, VOS_UINT8 ucSelEia)
{
    if (NAS_EMM_SECU_ALG_EEA0 != ucSelEca)
    {
        NAS_EMM_SndOmLogSecuVerifyFail(NAS_LMM_OM_LOG_SECU_FAIL_TYPE_NON_EIA0,
                                       ucSelEca);
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_Eia0SmcVerifyAlg_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_EMM_SECU_FAIL;
    }

    return NAS_EMM_IsAlgUeSupported(ucSelEca, ucSelEia);
}


VOS_UINT32 NAS_EMM_IsAlgUeSupported( VOS_UINT8 ucSelEca, VOS_UINT8 ucSelEia)
{
    NAS_MM_UE_NET_CAP_STRU             *pstUeNetCap = NAS_EMM_NULL_PTR;
    VOS_UINT8                           ucEEA;
    VOS_UINT8                           ucEIA;

    NAS_EMM_SECU_LOG_INFO("NAS_EMM_IsAlgUeSupported entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_IsAlgUeSupported_ENUM,LNAS_ENTRY);

    /*��ȡUE_NET_CAP*/
    pstUeNetCap = NAS_LMM_GetEmmInfoSecuParaUeNetCapAddr();

    /*��������Ա������߼����㷨��UE��֧��*/
    ucEEA = pstUeNetCap->aucUeNetCap[NAS_EMM_UE_NET_CAP_EEA_POS];
    ucEIA = pstUeNetCap->aucUeNetCap[NAS_EMM_UE_NET_CAP_EIA_POS];

    /*lint -e701*/
    if((NAS_EMM_BIT_NO_SLCT == ((ucEIA << ucSelEia)& NAS_EMM_SECU_HIGHEST_BIT))
      ||(NAS_EMM_BIT_NO_SLCT == ((ucEEA << ucSelEca)& NAS_EMM_SECU_HIGHEST_BIT)))

    {
        return NAS_EMM_SECU_FAIL;
    }
    /*lint +e701*/

    return NAS_EMM_SECU_SUCC;
}

CIPHER_ALGORITHM_E NAS_EMM_GetIntegrityAlg( VOS_UINT8 ucSelEia)
{

    NAS_EMM_SECU_LOG_INFO("NAS_EMM_GetIntegrityAlg entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_GetIntegrityAlg_ENUM,LNAS_ENTRY);

    switch(ucSelEia)
    {
        case    NAS_EMM_SECU_ALG_EIA0:
            return CIPHER_ALG_NULL;

        case    NAS_EMM_SECU_ALG_EIA1:
            return CIPHER_ALG_SNOW3G;

        case    NAS_EMM_SECU_ALG_EIA2:
            return CIPHER_ALG_AES_128;

        case    NAS_EMM_SECU_ALG_EIA3:
            return CIPHER_ALG_ZUC;

        default:
            NAS_EMM_SECU_LOG_INFO("NAS_EMM_GetIntegrityAlg entered: ucSelEia err");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_GetIntegrityAlg_ENUM,LNAS_ERROR);
            return CIPHER_ALG_BUTTOM;

    }
}

CIPHER_ALGORITHM_E NAS_EMM_GetSecurityAlg( VOS_UINT8 ucSelEca)
{

    NAS_EMM_SECU_LOG_INFO("NAS_EMM_GetSecurityAlg entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_GetSecurityAlg_ENUM,LNAS_ENTRY);

    switch(ucSelEca)
    {
        case    NAS_EMM_SECU_ALG_EEA0:

            return CIPHER_ALG_NULL;

        case    NAS_EMM_SECU_ALG_EEA1:
            return CIPHER_ALG_SNOW3G;

        case    NAS_EMM_SECU_ALG_EEA2:
            return CIPHER_ALG_AES_128;

        case    NAS_EMM_SECU_ALG_EEA3:
            return CIPHER_ALG_ZUC;

        default:
            NAS_EMM_SECU_LOG_INFO("NAS_EMM_GetSecurityAlg entered: ucSelEca err");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_GetSecurityAlg_ENUM,LNAS_ERROR);
            return CIPHER_ALG_BUTTOM;

    }
}



VOS_UINT32  NAS_EMM_SmcVerifyUeSecuCap(
                        const NAS_LMM_UE_SECURITY_CAP_STRU    *pstUeSecuCap )
{
    NAS_MM_UE_NET_CAP_STRU             *pstLocalUeNetCap = VOS_NULL_PTR;
    NAS_MM_MS_NET_CAP_STRU             *pstLocalMsNetCap = VOS_NULL_PTR;
    NAS_LMM_UE_SECURITY_CAP_STRU        stLocalUeSecuCap = {0};

    NAS_EMM_SECU_LOG_INFO("NAS_EMM_SmcVerifyUeSecuCap entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SmcVerifyUeSecuCap_ENUM,LNAS_ENTRY);

    if(NAS_EMM_SMC_CLOSE== g_ulUeSecuCapMatch)
    {
        NAS_EMM_SECU_LOG_INFO("NAS_EMM_SmcVerifyUeSecuCap: g_ulUeSecuCapMatch = NAS_EMM_SMC_CLOSE");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_SmcVerifyUeSecuCap_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_EMM_SECU_SUCC;
    }

    /* ��ȡ UE ���ص� UE_NET_CAP�� MS_NET_CAP*/
    pstLocalUeNetCap = NAS_LMM_GetEmmInfoSecuParaUeNetCapAddr();
    pstLocalMsNetCap = NAS_LMM_GetEmmInfoMsNetCapAddr();


    /* ����Ƕ�ģģʽ*/
    if (NAS_EMM_SUCC == NAS_EMM_CheckMutiModeSupport())
    {
        /*stLocalUeSecuCap.ucUeSeuCapLen = pstLocalUeNetCap->ucUeNetCapLen + 1;*/
        stLocalUeSecuCap.ucEEA = pstLocalUeNetCap->aucUeNetCap[NAS_EMM_UE_NET_CAP_EEA_POS];
        stLocalUeSecuCap.ucEIA = pstLocalUeNetCap->aucUeNetCap[NAS_EMM_UE_NET_CAP_EIA_POS];
        stLocalUeSecuCap.ucUEA = pstLocalUeNetCap->aucUeNetCap[NAS_EMM_UE_NET_CAP_UEA_POS];
        stLocalUeSecuCap.ucUIA = (pstLocalUeNetCap->aucUeNetCap[NAS_EMM_UE_NET_CAP_UIA_POS])&NAS_EMM_7_BITS_F;
        stLocalUeSecuCap.ucGEA = ((pstLocalMsNetCap->aucMsNetCap[0]&NAS_EMM_HIGHES_BIT)
                                  >>NAS_LMM_MOVEMENT_1_BITS);
        stLocalUeSecuCap.ucGEA |= ((pstLocalMsNetCap->aucMsNetCap[1]&NAS_EMM_6_BITS_F)
                                  >>NAS_LMM_MOVEMENT_1_BITS);

        /* �Ƚ�SMCЯ��Я����UE_SECURITY_CAP��UE���ص�UE_SECURITY_CAP��ֻ�Ƚ�����,���ٱȽϳ���*/    /*lint -e420 -e831*/
        /*lint -e420 -e831*/
        if(NAS_EMM_SECU_MEM_CMP_EQUAL != NAS_LMM_MEM_CMP(  (VOS_VOID*)&(stLocalUeSecuCap.ucEEA),
                                                            (VOS_VOID*)&(pstUeSecuCap->ucEEA),
                                                            NAS_EMM_SMC_MAX_UE_SECU_CAP_LEN ))
        /*lint +e420 +e831*/
        {
            NAS_EMM_SECU_LOG_ERR("NAS_EMM_SmcVerifyUeSecuCap: UE_SECU_CAP_NOT_MATCH.");
            TLPS_PRINT2LAYER_ERROR(NAS_EMM_SmcVerifyUeSecuCap_ENUM,LNAS_FUNCTION_LABEL2);
            return NAS_EMM_SECU_FAIL;
        }
    }
    /* Lģ��ģģʽ:ֻ��֤EEA,EIA�Ƿ���UE����ƥ�䣬������UEA,UIA*/
    else
    {
        stLocalUeSecuCap.ucUeSeuCapLen = pstLocalUeNetCap->ucUeNetCapLen;
        stLocalUeSecuCap.ucEEA = pstLocalUeNetCap->aucUeNetCap[NAS_EMM_UE_NET_CAP_EEA_POS];
        stLocalUeSecuCap.ucEIA = pstLocalUeNetCap->aucUeNetCap[NAS_EMM_UE_NET_CAP_EIA_POS];
        stLocalUeSecuCap.ucUEA = pstLocalUeNetCap->aucUeNetCap[NAS_EMM_UE_NET_CAP_UEA_POS];
        stLocalUeSecuCap.ucUIA = (pstLocalUeNetCap->aucUeNetCap[NAS_EMM_UE_NET_CAP_UIA_POS])&NAS_EMM_7_BITS_F;

        /* �Ƚ�SMCЯ����EEA,EIA��UE���ص�EEA,EIA*/
        if((pstUeSecuCap->ucEEA != stLocalUeSecuCap.ucEEA)
         ||(pstUeSecuCap->ucEIA != stLocalUeSecuCap.ucEIA))
        {
            NAS_EMM_SECU_LOG_ERR("NAS_EMM_SmcVerifyUeSecuCap: EEA or EIA NOT MATCH.");
            TLPS_PRINT2LAYER_ERROR(NAS_EMM_SmcVerifyUeSecuCap_ENUM,LNAS_FUNCTION_LABEL3);
            return NAS_EMM_SECU_FAIL;
        }

    }

    return NAS_EMM_SECU_SUCC;
}


VOS_UINT32  NAS_EMM_SmcVerifyNonceUE(
                                        const NAS_EMM_SECU_SMC_STRU *pstSmcStru )
{
    NAS_EMM_SECU_LOG_INFO("NAS_EMM_SmcVerifyNonceUE entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SmcVerifyNonceUE_ENUM,LNAS_ENTRY);

    /* ȷ��regplayed NonceUE�� NonceMME��Ԫ�������*/
    if((NAS_EMM_BIT_NO_SLCT == pstSmcStru->bitNonceUe)
     ||(NAS_EMM_BIT_NO_SLCT == pstSmcStru->bitNonceMme))
    {
        return NAS_EMM_SECU_FAIL;
    }

    /* ��UE���ص� NonceUE�Ƚϣ����ؽ��*/
    if(NAS_EMM_SECU_MEM_CMP_EQUAL != NAS_LMM_MEM_CMP(pstSmcStru->aucNonceUe,
                                                    NAS_EMM_GetSecuNonceUEAddr(),
                                                    NAS_EMM_SECU_NONCE_UE_LEN))
    {
        return NAS_EMM_SECU_FAIL;
    }

    return NAS_EMM_SECU_SUCC;

}


VOS_UINT32  NAS_EMM_DecodeSmcMsg(
                                        LRRC_LNAS_MSG_STRU      *pstCnSmcMsg,
                                        NAS_EMM_SECU_SMC_STRU   *pstSecurModeCtrl)/*lint -e662 -e661 -e831 -e416 -e415*/

{
    VOS_UINT32                          ulIndex             = NAS_EMM_NULL;
    VOS_UINT32                          ulMsgSize           = NAS_EMM_NULL;
    VOS_UINT8                          *pucSmcMsg           = VOS_NULL_PTR;
    VOS_UINT32                          ulTempMsgSize       = 0;
    VOS_UINT8                           ucReplayeUeSecuCapLen = 0;

    NAS_EMM_SECU_LOG_INFO( "NAS_EMM_DecodeCnSecurModeCtrlMsgNasMsg is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_DecodeSmcMsg_ENUM,LNAS_ENTRY);

    /* �жϿտ���ϢSMC���������Ƿ���ȷ*/
    /* ֻ��������̳��ȣ�
       ������Ϣ��󳤶ȵ�������ڱ�֤��Ԫ������ȷ������£����ڶ���Ĵ����ֽڲ��迼��*/
    ulMsgSize  = pstCnSmcMsg->ulNasMsgSize;
    if(NAS_EMM_SMC_MIN_LEN > ulMsgSize)
    {
        NAS_EMM_SndOmLogSecuVerifyFail(NAS_LMM_OM_LOG_SECU_FAIL_TYPE_DECODE_FAIL,
                                       1);
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_DecodeSmcMsg_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_EMM_SECU_FAIL;
    }

    /*��ȡSMC��Ϣ����*/
    pucSmcMsg = pstCnSmcMsg->aucNasMsg;

    /* ��ȡ��ѡIE*/
    ulIndex = NAS_EMM_SECU_PLAIN_MSG_POS;

    /*Protolcal Disciriminator and security header type*/
    pstSecurModeCtrl->ucPdSt = pucSmcMsg[ulIndex];
    ulIndex++;

    /*Message Type*/
    pstSecurModeCtrl->ucMt = pucSmcMsg[ulIndex];
    ulIndex++;

    /*selected NAS security algorithm*/
    pstSecurModeCtrl->ucSelAlgrthm = pucSmcMsg[ulIndex];
    ulIndex++;

    /*Key Set Identifier*/
    pstSecurModeCtrl->ucKSI = pucSmcMsg[ulIndex]& NAS_EMM_LOW_HALF_BYTE_F;
    ulIndex++;

    /*replayed UE security capability*/
    ucReplayeUeSecuCapLen = pucSmcMsg[ulIndex];
    ulIndex++;

    /*replayed UE secutity capability len:[2,5]*/
    if((NAS_EMM_SMC_MIN_UE_SECU_CAP_LEN > ucReplayeUeSecuCapLen)
     ||(NAS_EMM_SMC_MAX_UE_SECU_CAP_LEN < ucReplayeUeSecuCapLen))
    {
        NAS_EMM_SndOmLogSecuVerifyFail(NAS_LMM_OM_LOG_SECU_FAIL_TYPE_DECODE_FAIL,
                                       2);
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_DecodeSmcMsg_ENUM,LNAS_FUNCTION_LABEL2);
        return NAS_EMM_SECU_FAIL;
    }

    /*���ʣ�������ĳ����Ƿ�����Ҫ��*/
    if((ulIndex + ucReplayeUeSecuCapLen) > ulMsgSize)
    {
        NAS_EMM_SndOmLogSecuVerifyFail(NAS_LMM_OM_LOG_SECU_FAIL_TYPE_DECODE_FAIL,
                                       3);
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_DecodeSmcMsg_ENUM,LNAS_FUNCTION_LABEL3);
        return NAS_EMM_SECU_FAIL;
    }

    pstSecurModeCtrl->stUeSecuCap.ucUeSeuCapLen = ucReplayeUeSecuCapLen;
    NAS_LMM_MEM_CPY(                &(pstSecurModeCtrl->stUeSecuCap.ucEEA),
                                    &(pucSmcMsg[ulIndex]),
                                     ucReplayeUeSecuCapLen);
    ulIndex += ucReplayeUeSecuCapLen;

    /* ���spareλΪ0 */
    pstSecurModeCtrl->stUeSecuCap.ucUIA &= NAS_EMM_7_BITS_F;
    pstSecurModeCtrl->stUeSecuCap.ucGEA &= NAS_EMM_7_BITS_F;
    /*��ѡ��Ԫ������ɺ�ʣ�������ĳ���*/
    ulTempMsgSize =  ulMsgSize -  ulIndex;
    if(0 == ulTempMsgSize)
    {
        NAS_EMM_SECU_LOG_INFO("NAS_EMM_DecodeSmcMsg: decode complete.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_DecodeSmcMsg_ENUM,LNAS_FUNCTION_LABEL4);
        return NAS_EMM_SECU_SUCC;
    }

    /*��ȡ��ѡ��Ԫ*/
    /*IMEISV request*/
    if(NAS_EMM_SMC_IMEISV_REQ_IEI == (pucSmcMsg[ulIndex]&NAS_EMM_HIGH_HALF_BYTE_F))
    {
        NAS_EMM_SECU_LOG_INFO("NAS_EMM_DecodeSmcMsg: IMEISV request IE.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_DecodeSmcMsg_ENUM,LNAS_FUNCTION_LABEL5);
        pstSecurModeCtrl->bitImeisvReq = NAS_EMM_BIT_SLCT;
        pstSecurModeCtrl->ucImeisvRsq = pucSmcMsg[ulIndex];
        ulIndex++;
        ulTempMsgSize = ulMsgSize -  ulIndex;
    }

    /*�ж����ʣ������Ϊ0����������*/
    if(0 == ulTempMsgSize)
    {
        NAS_EMM_SECU_LOG_INFO("NAS_EMM_DecodeSmcMsg: decode complete.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_DecodeSmcMsg_ENUM,LNAS_FUNCTION_LABEL6);
        return NAS_EMM_SECU_SUCC;
    }

    /*replayed NonceUE*/
    if(NAS_EMM_SMC_NONCE_UE_IEI == pucSmcMsg[ulIndex])
    {
        ulIndex++;
        if((ulIndex + NAS_EMM_SECU_NONCE_UE_LEN) <= ulMsgSize)
        {
            NAS_EMM_SECU_LOG_INFO("NAS_EMM_DecodeSmcMsg: replayed Nonce IE.");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_DecodeSmcMsg_ENUM,LNAS_FUNCTION_LABEL7);
            pstSecurModeCtrl->bitNonceUe = NAS_EMM_BIT_SLCT;
            NAS_LMM_MEM_CPY(             pstSecurModeCtrl->aucNonceUe,
                                        (pucSmcMsg + ulIndex),
                                        NAS_EMM_SECU_NONCE_UE_LEN);
            ulIndex += NAS_EMM_SECU_NONCE_UE_LEN;
            ulTempMsgSize = ulMsgSize -  ulIndex;

             /*�ж����ʣ������Ϊ0����������*/
            if(0 == ulTempMsgSize)
            {
                NAS_EMM_SECU_LOG_INFO("NAS_EMM_DecodeSmcMsg: decode complete.");
                TLPS_PRINT2LAYER_INFO(NAS_EMM_DecodeSmcMsg_ENUM,LNAS_FUNCTION_LABEL8);
                return NAS_EMM_SECU_SUCC;
            }
        }
        else
        {
            NAS_EMM_SndOmLogSecuVerifyFail(NAS_LMM_OM_LOG_SECU_FAIL_TYPE_DECODE_FAIL,
                                           4);
            TLPS_PRINT2LAYER_ERROR(NAS_EMM_DecodeSmcMsg_ENUM,LNAS_FUNCTION_LABEL9);
            return NAS_EMM_SECU_FAIL;
        }
    }

    /*NonceMME*/
    if(NAS_EMM_SMC_NONCE_MME_IEI == pucSmcMsg[ulIndex])
    {
        ulIndex++;
        if((ulIndex + NAS_EMM_SECU_NONCE_MME_LEN) <= ulMsgSize)
        {
            NAS_EMM_SECU_LOG_INFO("NAS_EMM_DecodeSmcMsg: NonceMME IE.");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_DecodeSmcMsg_ENUM,LNAS_FUNCTION_LABEL10);
            pstSecurModeCtrl->bitNonceMme = NAS_EMM_BIT_SLCT;
            NAS_LMM_MEM_CPY(             pstSecurModeCtrl->aucNonceMme,
                                       (pucSmcMsg + ulIndex),
                                        NAS_EMM_SECU_NONCE_MME_LEN);
        }
        else
        {
            NAS_EMM_SndOmLogSecuVerifyFail(NAS_LMM_OM_LOG_SECU_FAIL_TYPE_DECODE_FAIL,
                                           5);
            TLPS_PRINT2LAYER_ERROR(NAS_EMM_DecodeSmcMsg_ENUM,LNAS_FUNCTION_LABEL11);
            return NAS_EMM_SECU_FAIL;
        }
    }

    return NAS_EMM_SECU_SUCC;

}/*lint +e662 +e661 +e831 +e416 +e415*/


VOS_UINT32  NAS_EMM_NotEia0SmcVerifyParam
(
    const NAS_EMM_SECU_SMC_STRU              *pstSmcStru,
    VOS_UINT8                           ucSqn
)
{
    VOS_UINT32                          ulRslt      = NAS_EMM_SECU_FAIL;
    VOS_UINT8                           ucSmcEia    = NAS_EMM_NULL;
    VOS_UINT8                           ucSmcEca    = NAS_EMM_NULL;

    /*lint -e415 -e416*/
    ulRslt = NAS_EMM_NotEia0SmcVerifyKsi(ucSqn, pstSmcStru->ucKSI);
    /*lint +e415 +e416*/

    if(NAS_EMM_SECU_FAIL == ulRslt)
    {
        NAS_EMM_SecuSendSmcRej(NAS_EMM_SMC_REJ_UNSPECIFIED);
        NAS_EMM_SndOmLogSecuVerifyFail(NAS_LMM_OM_LOG_SECU_FAIL_TYPE_KSI_MISMATCH,
                                       ucSqn);
        TLPS_PRINT2LAYER_INFO(NAS_EMM_NotEia0SmcVerifyParam_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_EMM_SECU_FAIL;
    }

    /*����㷨*/
    ucSmcEia =  pstSmcStru->ucSelAlgrthm & NAS_EMM_LOW_3_BITS_F;
    ucSmcEca =  (pstSmcStru->ucSelAlgrthm >>4) & NAS_EMM_LOW_3_BITS_F;
    ulRslt = NAS_EMM_IsAlgUeSupported(ucSmcEca, ucSmcEia);
    if(NAS_EMM_SECU_FAIL == ulRslt)
    {
        NAS_EMM_SecuSendSmcRej(NAS_EMM_SMC_REJ_UNSPECIFIED);
        NAS_EMM_SndOmLogSecuVerifyFail(NAS_LMM_OM_LOG_SECU_FAIL_TYPE_ALG_NOT_SUPPORT,
                                       0);
        TLPS_PRINT2LAYER_INFO(NAS_EMM_NotEia0SmcVerifyParam_ENUM,LNAS_FUNCTION_LABEL2);
        return NAS_EMM_SECU_FAIL;
    }

    /*���SMCЯ����replayed UE_SECURITY_CAP�Ƿ���UE����ά������ͬ*/
    ulRslt = NAS_EMM_SmcVerifyUeSecuCap(&(pstSmcStru->stUeSecuCap));
    if(NAS_EMM_SECU_FAIL == ulRslt)
    {
        NAS_EMM_SecuSendSmcRej(NAS_EMM_SMC_REJ_SECU_CAP_MISMATCH);
        /* coverity[unchecked_value] */
        NAS_EMM_SndOmLogSecuVerifyFail(NAS_LMM_OM_LOG_SECU_FAIL_TYPE_UE_CAP_MISMATCH,
                                       NAS_EMM_CheckMutiModeSupport());
        TLPS_PRINT2LAYER_INFO(NAS_EMM_NotEia0SmcVerifyParam_ENUM,LNAS_FUNCTION_LABEL3);
        return NAS_EMM_SECU_FAIL;
    }

    /*���SMCЯ����KSIΪnew mapped ksi������Ҫ��֤replaye NonceUE*/
    if(NAS_EMM_SMC_UPDATE_NEW_MAPPED == NAS_EMM_GetSmcType())
    {
        ulRslt = NAS_EMM_SmcVerifyNonceUE(pstSmcStru);
        if(NAS_EMM_SECU_FAIL == ulRslt)
        {
            NAS_EMM_SecuSendSmcRej(NAS_EMM_SMC_REJ_UNSPECIFIED);
            NAS_EMM_SndOmLogSecuVerifyFail(NAS_LMM_OM_LOG_SECU_FAIL_TYPE_NONCE_MISMATCH,
                                           0);
            TLPS_PRINT2LAYER_INFO(NAS_EMM_NotEia0SmcVerifyParam_ENUM,LNAS_FUNCTION_LABEL4);
            return NAS_EMM_SECU_FAIL;
        }
    }

    return NAS_EMM_SECU_SUCC;
}


VOS_UINT32  NAS_EMM_Eia0SmcVerifyParam
(
    const NAS_EMM_SECU_SMC_STRU              *pstSmcStru
)
{
    VOS_UINT32                          ulRslt      = NAS_EMM_SECU_FAIL;
    VOS_UINT8                           ucSmcEia    = NAS_EMM_NULL;
    VOS_UINT8                           ucSmcEca    = NAS_EMM_NULL;

    /*lint -e415 -e416*/
    ulRslt = NAS_EMM_Eia0SmcVerifyKsi(pstSmcStru->ucKSI);
    /*lint +e415 +e416*/

    if(NAS_EMM_SECU_FAIL == ulRslt)
    {
        NAS_EMM_SecuSendSmcRej(NAS_EMM_SMC_REJ_UNSPECIFIED);
        NAS_EMM_SndOmLogSecuVerifyFail(NAS_LMM_OM_LOG_SECU_FAIL_TYPE_KSI_MISMATCH,
                                       (pstSmcStru->ucKSI) & NAS_EMM_LOW_3_BITS_F);
        TLPS_PRINT2LAYER_INFO(NAS_EMM_Eia0SmcVerifyParam_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_EMM_SECU_FAIL;
    }

    /*����㷨*/
    ucSmcEia =  pstSmcStru->ucSelAlgrthm & NAS_EMM_LOW_3_BITS_F;
    ucSmcEca =  (pstSmcStru->ucSelAlgrthm >>4) & NAS_EMM_LOW_3_BITS_F;
    ulRslt = NAS_EMM_Eia0SmcVerifyAlg(ucSmcEca, ucSmcEia);
    if(NAS_EMM_SECU_FAIL == ulRslt)
    {
        NAS_EMM_SecuSendSmcRej(NAS_EMM_SMC_REJ_UNSPECIFIED);
        NAS_EMM_SndOmLogSecuVerifyFail(NAS_LMM_OM_LOG_SECU_FAIL_TYPE_ALG_NOT_SUPPORT,
                                       0);
        TLPS_PRINT2LAYER_INFO(NAS_EMM_Eia0SmcVerifyParam_ENUM,LNAS_FUNCTION_LABEL2);
        return NAS_EMM_SECU_FAIL;
    }

    /*���SMCЯ����replayed UE_SECURITY_CAP�Ƿ���UE����ά������ͬ*/
    ulRslt = NAS_EMM_SmcVerifyUeSecuCap(&(pstSmcStru->stUeSecuCap));
    if(NAS_EMM_SECU_FAIL == ulRslt)
    {
        NAS_EMM_SecuSendSmcRej(NAS_EMM_SMC_REJ_SECU_CAP_MISMATCH);
        /* coverity[unchecked_value] */
        NAS_EMM_SndOmLogSecuVerifyFail(NAS_LMM_OM_LOG_SECU_FAIL_TYPE_UE_CAP_MISMATCH,
                                       NAS_EMM_CheckMutiModeSupport());
        TLPS_PRINT2LAYER_INFO(NAS_EMM_Eia0SmcVerifyParam_ENUM,LNAS_FUNCTION_LABEL3);
        return NAS_EMM_SECU_FAIL;
    }

    /* Ϊ�˼��ݲ�ͬ���磬ʵ�п���ϳ�ԭ���ݲ��ж��Ƿ��н������ػ���
       ���ڽ����������� */

    return NAS_EMM_SECU_SUCC;
}


VOS_UINT32  NAS_EMM_SmcVerifyParam( LRRC_LNAS_MSG_STRU  *pstSmcMsg )
{
    VOS_UINT8                           ucSmcEia = 0;
    VOS_UINT32                          ulRslt = NAS_EMM_SECU_FAIL;
    NAS_EMM_SECU_SMC_STRU              *pstSmcStru = VOS_NULL_PTR;

    NAS_EMM_SECU_LOG_INFO("NAS_EMM_SmcVerifyParam enterd.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SmcVerifyParam_ENUM,LNAS_ENTRY);

    /*SMC��Ϣ����*/
    pstSmcStru = (NAS_EMM_SECU_SMC_STRU *)NAS_EMM_GetSecuBufSpace();
    NAS_LMM_MEM_SET(pstSmcStru, 0, sizeof(NAS_EMM_SECU_SMC_STRU));
    ulRslt = NAS_EMM_DecodeSmcMsg(pstSmcMsg, pstSmcStru);
    if(NAS_EMM_SECU_FAIL == ulRslt)
    {
        NAS_EMM_SecuSendSmcRej(NAS_EMM_SMC_REJ_UNSPECIFIED);
        NAS_EMM_SECU_LOG_NORM("NAS_EMM_SmcVerifyParam:decode ERR.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_SmcVerifyParam_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_EMM_SECU_FAIL;
    }

    /*���KSI*/
    NAS_EMM_SECU_LOG1_INFO("NAS_EMM_SmcVerifyParam:pstSmcStru->ucKSI = ", pstSmcStru->ucKSI );
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_SmcVerifyParam_ENUM,LNAS_FUNCTION_LABEL2,pstSmcStru->ucKSI);

    ucSmcEia =  pstSmcStru->ucSelAlgrthm & NAS_EMM_LOW_3_BITS_F;

    if (NAS_EMM_SECU_ALG_EIA0 == ucSmcEia)
    {
        /* mod by yanglei 00307272 for KEY_INFO_REPORT,2015-08-13,begin */
        ulRslt = NAS_EMM_Eia0SmcVerifyParam(      pstSmcStru);
        if(NAS_EMM_SECU_FAIL == ulRslt)
        {
            NAS_EMM_SndOmLogEpsSecContextInfo();
        }
        return ulRslt;
        /* mod by yanglei 00307272 for KEY_INFO_REPORT,2015-08-13,end */
    }
    else
    {
        /* mod by yanglei 00307272 for KEY_INFO_REPORT,2015-08-13,begin */
        /*lint -e416 -e415*/
        ulRslt = NAS_EMM_NotEia0SmcVerifyParam(   pstSmcStru,
                                                pstSmcMsg->aucNasMsg[NAS_EMM_SECU_MSG_SN_POS]);
        /*lint +e416 +e415*/
        if(NAS_EMM_SECU_FAIL == ulRslt)
        {
            NAS_EMM_SndOmLogEpsSecContextInfo();
        }
        return ulRslt;
        /* mod by yanglei 00307272 for KEY_INFO_REPORT,2015-08-13,end */

    }
}


VOS_VOID  NAS_EMM_SecuGetNonceMmeInSmc( VOS_VOID )
{
    NAS_EMM_SECU_SMC_STRU              *pstSmcStru = VOS_NULL_PTR;

    NAS_EMM_SECU_LOG_INFO("NAS_EMM_SecuGetNonceMmeInSmc enterd.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SecuGetNonceMmeInSmc_ENUM,LNAS_ENTRY);

    /* �ӽ�������Ϣ�ṹ�л�ȡ NONCEmme*/
    pstSmcStru = (NAS_EMM_SECU_SMC_STRU *)NAS_EMM_GetSecuBufSpace();
    NAS_LMM_MEM_CPY(                     NAS_EMM_GetSecuNonceMMEAddr(),
                                        pstSmcStru->aucNonceMme,
                                        NAS_EMM_SECU_NONCE_MME_LEN);
    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_Eia0SmcIntCheckPara
 Description     : ����EIA0ʱ����NAS CK��NAS IK
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2012-10-18  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_Eia0SmcIntCheckPara
(
    LRRC_LNAS_MSG_STRU                 *pstSmcMsg,
    NAS_EMM_PROT_PARAM_STRU            *pstUnProtParam
)
{
    VOS_UINT8                          *pucKasme        = VOS_NULL_PTR;
    VOS_UINT8                           ucSmcEia        = NAS_EMM_NULL;
    VOS_UINT8                           ucSmcEca        = NAS_EMM_NULL;
    VOS_UINT32                          ulDlForUnprot   = NAS_EMM_NULL;
    VOS_UINT8                           ucKsiValue      = NAS_EMM_NULL;
    VOS_UINT32                          ulRslt          = NAS_EMM_SECU_FAIL;


    /* ����SMCЯ����KSI�����ͣ���ȡ��ȫ������*/
    /*lint -e416 -e415*/
    ucKsiValue =  pstSmcMsg->aucNasMsg[NAS_EMM_SECU_SMC_KSI_POSE] & NAS_EMM_LOW_3_BITS_F;
    /*lint +e416 +e415*/
    if (ucKsiValue == NAS_EMM_GetSecuCurKSIasme())
    {
        pucKasme = NAS_EMM_GetSecuCurKasmeAddr();
    }
    else
    {
        pucKasme = NAS_EMM_GetEia0Kasme();
    }

    /*��ȡSMCЯ�����㷨*/
    /*lint -e416 -e415*/
    ucSmcEia =  pstSmcMsg->aucNasMsg[NAS_EMM_SECU_SMC_ALG_POSE] & NAS_EMM_LOW_3_BITS_F;
    ucSmcEca = (pstSmcMsg->aucNasMsg[NAS_EMM_SECU_SMC_ALG_POSE]>>4) & NAS_EMM_LOW_3_BITS_F;
    /*lint +e416 +e415*/

    /*�����µ� NasCK,NasIK*/
    NAS_EMM_DeriveNewNasKey(pucKasme,ucSmcEca,ucSmcEia);

    (VOS_VOID)ulRslt;

    /*SMC��Ϣ�����Լ����Ҫʹ�������ɵ� NasCK,NasIK���滻Register�е���Կ*/
    /*NasIK*/
    (VOS_VOID)NAS_EMM_SecuSetKeyByKeyIndex(  NAS_EMM_GetSecuTempNasIkAddr(),
                                        NAS_EMM_SECU_INTEGRITY_KEY);
    /*NasCK*/
    (VOS_VOID)NAS_EMM_SecuSetKeyByKeyIndex(  NAS_EMM_GetSecuTempNasCkAddr(),
                                        NAS_EMM_SECU_CIPHER_KEY);

    /*��װSMC��Ϣ�����Լ����Ҫ�Ĳ���*/
    pstUnProtParam->ulNasCount          = ulDlForUnprot;
    pstUnProtParam->ucSecuALg           = ucSmcEia;
    pstUnProtParam->pucMsg              = pstSmcMsg->aucNasMsg;
    pstUnProtParam->pulMsgSize          = &(pstSmcMsg->ulNasMsgSize);

    return;
}
VOS_VOID  NAS_EMM_NotEia0SmcIntCheckPara(
                                        LRRC_LNAS_MSG_STRU      *pstSmcMsg,
                                        NAS_EMM_PROT_PARAM_STRU *pstUnProtParam)
{
    VOS_UINT8                          *pucKasme = VOS_NULL_PTR;
    VOS_UINT8                           ucSmcEia = 0;
    VOS_UINT8                           ucSmcEca = 0;
    VOS_UINT32                          ulDlForUnprot = 0;
    VOS_UINT32                          ulRslt = NAS_EMM_SECU_FAIL;

    /* ����SMCЯ����KSI�����ͣ���ȡ��ȫ������*/
    switch (NAS_EMM_GetSmcType())
    {
        case NAS_EMM_SMC_UPDATE_CUR:
            /*lint -e415 -e416*/
            ulDlForUnprot = NAS_EMM_CompDlNasCount(NAS_EMM_GetSecuDlNasCount(),
                                pstSmcMsg->aucNasMsg[NAS_EMM_SECU_MSG_SN_POS]);
            /*lint +e415 +e416*/
            pucKasme = NAS_EMM_GetSecuCurKasmeAddr();
            break;

        case NAS_EMM_SMC_UPDATE_NEW_MAPPED:
            /*lint -e415 -e416*/
            ulDlForUnprot = pstSmcMsg->aucNasMsg[NAS_EMM_SECU_MSG_SN_POS];
            /*lint +e415 +e416*/

            pucKasme = NAS_EMM_GetSecuNewMappedKasmeAddr();

            /*��ȡSMC��ϢЯ���� NONCEmme*/
            NAS_EMM_SecuGetNonceMmeInSmc();

            /*���� new mapped security context�е� Kasme*/
            ulRslt = NAS_EMM_DeriveKasmeFromUmtsIdle(pucKasme);
            if(NAS_EMM_SECU_FAIL == ulRslt)
            {
                NAS_EMM_SECU_LOG_ERR("NAS_EMM_DeriveKasmeFromUmtsIdle ERR.");
                TLPS_PRINT2LAYER_ERROR(NAS_EMM_NotEia0SmcIntCheckPara_ENUM,LNAS_FUNCTION_LABEL1);
            }
            break;

        case NAS_EMM_SMC_UPDATE_NEW_NATIVE:
            /* �˴�ȡ�����·���SMC��Ϣ�е�Sqn��NasCount�ĸ�3�ֽڹ̶�ȡ0�����ʵ�ֵ�Ŀ����
            ��ֹ�ռ�Ȩ��ɺ����ʧ�����ղ�������ĵ�1��SMC��Ϣ�����೬ʱ���ٷ�SMC���̿��ܽ�
            Sqn��1����UEһֱ��NasCount=0���޷��Ᵽ���ɹ����������жϷ�ת���߼����ڣ���ֹ��
            �������ղ���UE���͵�SMC CMP��Ϣ���ط�ʱ����Sqn=0����UE����Ϊ��ת����һֱ�޷���
            �����ɹ������ʵ�ָպ��ܼ��������������                                     */
            /*lint -e415 -e416*/
            ulDlForUnprot = pstSmcMsg->aucNasMsg[NAS_EMM_SECU_MSG_SN_POS];
            /*lint +e415 +e416*/
            pucKasme = NAS_EMM_GetSecuNewNativeKasmeAddr();
            break;

        case NAS_EMM_SMC_UPDATE_NON_CUR_NATIVE:
            /*lint -e416 -e415*/
            ulDlForUnprot = NAS_EMM_CompDlNasCount(
                                NAS_EMM_GetSecuNonCurDlNasCount(),
                                pstSmcMsg->aucNasMsg[NAS_EMM_SECU_MSG_SN_POS]);
            /*lint +e416 +e415*/
            pucKasme = NAS_EMM_GetSecuNonCurNativeKasmeAddr();
            break;

        default:
            NAS_EMM_SECU_LOG_ERR("NAS_EMM_NotEia0SmcIntCheckPara:SmcType ERR.");
            TLPS_PRINT2LAYER_ERROR(NAS_EMM_NotEia0SmcIntCheckPara_ENUM,LNAS_FUNCTION_LABEL2);
            return;
    }

    /*��ȡSMCЯ�����㷨*/
    /*lint -e416 -e415*/
    ucSmcEia =  pstSmcMsg->aucNasMsg[NAS_EMM_SECU_SMC_ALG_POSE] & NAS_EMM_LOW_3_BITS_F;
    ucSmcEca = (pstSmcMsg->aucNasMsg[NAS_EMM_SECU_SMC_ALG_POSE]>>4) & NAS_EMM_LOW_3_BITS_F;
    /*lint +e416 +e415*/

    /*�����µ� NasCK,NasIK*/
    NAS_EMM_DeriveNewNasKey(pucKasme,ucSmcEca,ucSmcEia);

    (VOS_VOID)ulRslt;

    /*SMC��Ϣ�����Լ����Ҫʹ�������ɵ� NasCK,NasIK���滻Register�е���Կ*/
    /*NasIK*/
    (VOS_VOID)NAS_EMM_SecuSetKeyByKeyIndex(  NAS_EMM_GetSecuTempNasIkAddr(),
                                        NAS_EMM_SECU_INTEGRITY_KEY);
    /*NasCK*/
    (VOS_VOID)NAS_EMM_SecuSetKeyByKeyIndex(  NAS_EMM_GetSecuTempNasCkAddr(),
                                        NAS_EMM_SECU_CIPHER_KEY);

    /*��װSMC��Ϣ�����Լ����Ҫ�Ĳ���*/
    pstUnProtParam->ulNasCount          = ulDlForUnprot;
    pstUnProtParam->ucSecuALg           = ucSmcEia;
    pstUnProtParam->pucMsg              = pstSmcMsg->aucNasMsg;
    pstUnProtParam->pulMsgSize          = &(pstSmcMsg->ulNasMsgSize);

    return;
}



VOS_UINT32  NAS_EMM_SmcIntCheck( LRRC_LNAS_MSG_STRU  *pstSmcMsg )
{
    VOS_UINT32                          ulRslt          = NAS_EMM_SECU_FAIL;
    NAS_EMM_PROT_PARAM_STRU             stUnProtParam   = {0};
    VOS_UINT8                           ucSmcEia        = NAS_EMM_NULL;

    /*����SMCЯ���Ĳ����������µ� NasCK,NasIK,����SMC�����Լ��Ĳ���*/
    /*lint -e416 -e415*/
    ucSmcEia =  pstSmcMsg->aucNasMsg[NAS_EMM_SECU_SMC_ALG_POSE] & NAS_EMM_LOW_3_BITS_F;
    /*lint +e416 +e415*/
    if (NAS_EMM_SECU_ALG_EIA0 == ucSmcEia)
    {
        NAS_EMM_Eia0SmcIntCheckPara(pstSmcMsg, &stUnProtParam);
    }
    else
    {

        NAS_EMM_NotEia0SmcIntCheckPara(pstSmcMsg, &stUnProtParam);
    }

    /*�����Լ��*/
    /* coverity[var_deref_model] */
    ulRslt = NAS_EMM_SecuIntCheck(&stUnProtParam);
    if(NAS_EMM_SECU_FAIL == ulRslt)
    {
        NAS_EMM_SECU_LOG_NORM("NAS_EMM_SmcIntCheck: SMC Int Check Fail.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_SmcIntCheck_ENUM,LNAS_FUNCTION_LABEL1);

        /*���ΰ�ȫ����ʧ�ܣ��µ�NasCK��NasIKû����Ч����ԭRegister�е���Կ*/
        /*NasIK*/
        (VOS_VOID) NAS_EMM_SecuSetKeyByKeyIndex(  NAS_EMM_GetSecuCurNasIkAddr(),
                                            NAS_EMM_SECU_INTEGRITY_KEY);
        /*NasCK*/
        (VOS_VOID) NAS_EMM_SecuSetKeyByKeyIndex(  NAS_EMM_GetSecuCurNasCkAddr(),
                                            NAS_EMM_SECU_CIPHER_KEY);
        /* mod by yanglei 00307272 for KEY_INFO_REPORT2,2015-08-13,begin */
        NAS_EMM_SndOmLogEpsSecContextInfo();
        /* mod by yanglei 00307272 for KEY_INFO_REPORT2,2015-08-13,end */
        /* �����Լ��ʧ��,ʹ�û�ԭ�����Կ��smc rej�տڽ��м��� */
        NAS_EMM_SecuSendSmcRej(NAS_EMM_SMC_REJ_UNSPECIFIED);
        return NAS_EMM_SECU_FAIL;
    }

    /*�����Լ��ͨ��������ܱ���DL_NASCOUNT*/
    /* Mod by yanglei 00307272 for DL_NAS_COUNT_OPTIMIZE, 2015-08-27, Begin */
    /* �����countֵ���ڱ���countֵ���߼����countֵΪ0�Ÿ��� */
    if((stUnProtParam.ulNasCount > NAS_EMM_GetSecuDlNasCount())
        ||(stUnProtParam.ulNasCount == 0))
    {
        NAS_EMM_GetSecuDlNasCount() = stUnProtParam.ulNasCount;
    }
    /* Mod by yanglei 00307272 for DL_NAS_COUNT_OPTIMIZE, 2015-08-27, End */

    return NAS_EMM_SECU_SUCC;
}
VOS_VOID  NAS_EMM_SendSecuParamToRrc( VOS_VOID )
{
    LRRC_LNAS_INFO_STRU                   stNasInfo;

    NAS_EMM_SECU_LOG_INFO("NAS_EMM_SendSecuParamToRrc entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SendSecuParamToRrc_ENUM,LNAS_ENTRY);

    /*����ڴ�*/
    NAS_LMM_MEM_SET(&stNasInfo, 0, sizeof(LRRC_LNAS_INFO_STRU));

    /*��䰲ȫ����: Kasme + UL_NasCount*/
    stNasInfo.bitOpSecurityKey = NAS_EMM_BIT_SLCT;
    NAS_LMM_MEM_CPY(                     stNasInfo.stSecurityKey.aucKasme,
                                        NAS_EMM_GetSecuCurKasmeAddr(),
                                        NAS_LMM_SECU_AUTH_KEY_ASME_LEN);
    stNasInfo.stSecurityKey.ulNasCount = NAS_EMM_GetSecuUlNasCount();

    /*����RRC_MM_INFO_CHANGE_REQ��Ϣ��RRC*/
    NAS_EMM_SendInfoChangeReqMsg(&stNasInfo);

    return;

}
VOS_VOID    NAS_EMM_SecuSendSmcCmp(
                        NAS_EMM_IMEISV_REQUEST_INFO_ENUM_UINT8  enIfImeisvReq)
{
    VOS_UINT32                           ulPos                   = 0;
    NAS_EMM_MRRC_DATA_REQ_STRU          *pIntraMsg              = VOS_NULL_PTR;
    NAS_EMM_PUB_INFO_STRU               *pstEmmInfo             = VOS_NULL_PTR;
    VOS_UINT32                          uldataReqMsgLenNoHeader;

    NAS_EMM_SECU_LOG_INFO("NAS_EMM_SecuSendSmcCmp is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SecuSendSmcCmp_ENUM,LNAS_ENTRY);

    /*������Ϣ�ڴ�*/
    pIntraMsg = (VOS_VOID *)NAS_LMM_MEM_ALLOC(NAS_EMM_INTRA_MSG_MAX_SIZE);
    if (NAS_EMM_NULL_PTR == pIntraMsg)
    {
        return;
    }

    /*����SMC COMPLETE��Ϣ*/
    pIntraMsg->stNasMsg.aucNasMsg[ulPos++]     = EMM_CN_MSG_PD_EMM;
    pIntraMsg->stNasMsg.aucNasMsg[ulPos++]     = NAS_EMM_CN_MT_SMC_CMP;

    if(NAS_EMM_IMEISV_REQUEST == enIfImeisvReq)
    {
        pIntraMsg->stNasMsg.aucNasMsg[ulPos++] = NAS_EMM_SECU_IMEISV_IEI;

        /* ��� IMEISV*/
        pstEmmInfo = NAS_LMM_GetEmmInfoAddr();
        /*lint -e419*/
        NAS_LMM_MEM_CPY((VOS_VOID *)&pIntraMsg->stNasMsg.aucNasMsg[ulPos],
                                        pstEmmInfo->stMmUeId.aucImeisv,
                                        NAS_MM_MAX_UEID_BUF_SIZE);
        /*lint +e419*/

        ulPos += NAS_MM_MAX_UEID_BUF_SIZE;
    }

    /*�����ϢID*/
    pIntraMsg->ulMsgId = ID_NAS_LMM_INTRA_MRRC_DATA_REQ;
    pIntraMsg->enEstCaue = LRRC_LNAS_EST_CAUSE_MO_SIGNALLING;
    pIntraMsg->enCallType = LRRC_LNAS_CALL_TYPE_ORIGINATING_SIGNALLING;
    pIntraMsg->enDataCnf = LRRC_LMM_DATA_CNF_NEED;

    /*����ڲ���Ϣ����*/
    pIntraMsg->enEmmMsgType = NAS_EMM_MSG_SMC_COMPL;

    /*�����Ϣ����*/
    pIntraMsg->stNasMsg.ulNasMsgSize = ulPos;

    /*���㲻������Ϣͷ����Ϣ����*/
    uldataReqMsgLenNoHeader =
        NAS_EMM_COUNT_INTRA_MSG_NO_HEADER_LEN(pIntraMsg->stNasMsg.ulNasMsgSize);

    /*�����Ϣͷ*/
    NAS_EMM_SET_SECU_INTRA_MSG_HEADER(pIntraMsg, uldataReqMsgLenNoHeader);

    /*�տ���Ϣ�ϱ� SECU_MODE_COMPLETE*/
    NAS_LMM_SendOmtAirMsg( NAS_EMM_OMT_AIR_MSG_UP,
                          NAS_EMM_SECU_CMP,
                          (NAS_MSG_STRU*)&(pIntraMsg->stNasMsg));

    /*�ؼ��¼��ϱ� SECU_MODE_COMPLETE*/
    NAS_LMM_SendOmtKeyEvent(EMM_OMT_KE_SECU_CMP);

    /* ��MRRC����SMC COMPLETE��Ϣ */
    NAS_EMM_SndUplinkNasMsg(pIntraMsg);

    NAS_LMM_MEM_FREE(pIntraMsg);

    return;
}
VOS_VOID NAS_EMM_SecuSendSmcRej(NAS_EMM_SMC_REJ_CAUSE_ENUM_UINT8 enCause)
{
    VOS_UINT32                          ulPos               = 0;
    NAS_EMM_MRRC_DATA_REQ_STRU         *pIntraMsg           = VOS_NULL;
    VOS_UINT32                          uldataReqMsgLenNoHeader;


    NAS_EMM_SECU_LOG_INFO("NAS_EMM_SecuSendSmcRej is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SecuSendSmcRej_ENUM,LNAS_ENTRY);

    /* ������Ϣ�ڴ� */
    pIntraMsg = (VOS_VOID *)NAS_LMM_MEM_ALLOC(
                                        NAS_EMM_INTRA_MSG_MAX_SIZE);

    /* �ж�����������ʧ���˳� */
    if (NAS_EMM_NULL_PTR == pIntraMsg)
    {
      return;
    }

    /*����SMC Reject ��Ϣ*/
    pIntraMsg->stNasMsg.aucNasMsg[ulPos++] = EMM_CN_MSG_PD_EMM;
    pIntraMsg->stNasMsg.aucNasMsg[ulPos++] = NAS_EMM_CN_MT_SMC_REJ;

    /* ��� EMM CAUSE*/
    pIntraMsg->stNasMsg.aucNasMsg[ulPos++] = enCause;

    /* �����ϢID */
    pIntraMsg->ulMsgId                  = ID_NAS_LMM_INTRA_MRRC_DATA_REQ;
    pIntraMsg->enEstCaue                = LRRC_LNAS_EST_CAUSE_MO_SIGNALLING;
    pIntraMsg->enCallType               = LRRC_LNAS_CALL_TYPE_ORIGINATING_SIGNALLING;
    pIntraMsg->enDataCnf                = LRRC_LMM_DATA_CNF_NEED;
    pIntraMsg->enEmmMsgType             = NAS_EMM_MAS_SMC_REJ;

    /* �����Ϣ���� */
    pIntraMsg->stNasMsg.ulNasMsgSize = ulPos;

    /*���㲻������Ϣͷ����Ϣ����*/
    uldataReqMsgLenNoHeader =
            NAS_EMM_COUNT_INTRA_MSG_NO_HEADER_LEN(pIntraMsg->stNasMsg.ulNasMsgSize);

    /*�����Ϣͷ*/
    NAS_EMM_SET_SECU_INTRA_MSG_HEADER(pIntraMsg, uldataReqMsgLenNoHeader);

    /*�տ���Ϣ�ϱ� SECU_MODE_REJ*/
    NAS_LMM_SendOmtAirMsg( NAS_EMM_OMT_AIR_MSG_UP,
                          NAS_EMM_SECU_REJ,
                          (NAS_MSG_STRU*)&(pIntraMsg->stNasMsg));

    /*�ؼ��¼��ϱ� SECU_MODE_REJ*/
    NAS_LMM_SendOmtKeyEvent(         EMM_OMT_KE_SECU_REJ);

    /*��MRRC����SMC Reject��Ϣ*/
    NAS_EMM_SndUplinkNasMsg(pIntraMsg);

    NAS_LMM_MEM_FREE(pIntraMsg);

    return;
}
NAS_EMM_IMEISV_REQUEST_INFO_ENUM_UINT8  NAS_EMM_IsImeisvReq( VOS_VOID)
{
    NAS_EMM_SECU_SMC_STRU              *pstSmcStru = VOS_NULL_PTR;

    NAS_EMM_SECU_LOG_INFO("NAS_EMM_IsImeisvReq enterd.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_IsImeisvReq_ENUM,LNAS_ENTRY);
    pstSmcStru = (NAS_EMM_SECU_SMC_STRU *)NAS_EMM_GetSecuBufSpace();

    if((NAS_EMM_BIT_SLCT == pstSmcStru->bitImeisvReq)
     &&(NAS_EMM_SMC_IMEISV_REQ == pstSmcStru->ucImeisvRsq))
    {
        return NAS_EMM_IMEISV_REQUEST;
    }
    else
    {
        return NAS_EMM_IMEISV_NOT_REQUEST;
    }

}


VOS_VOID  NAS_EMM_SmcSucc( const LRRC_LNAS_MSG_STRU    *pstSmcMsg )
{
    NAS_EMM_IMEISV_REQUEST_INFO_ENUM_UINT8  enIfImeisvReq   = NAS_EMM_IMEISV_REQUEST_INFO_BUTT;
    VOS_UINT8                               ucSmcEia        = 0;
    VOS_UINT8                               ucKsiValue      = 0;

    NAS_EMM_SECU_LOG_INFO("NAS_EMM_SmcSucc enterd.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SmcSucc_ENUM,LNAS_ENTRY);

    if((NAS_EMM_SMC_UPDATE_NEW_MAPPED == NAS_EMM_GetSmcType())
     ||(NAS_EMM_SMC_UPDATE_NEW_NATIVE == NAS_EMM_GetSmcType()))
    {
        /*DL_NASCOUNT��UP_NASCOUNT ����*/
        NAS_EMM_GetSecuDlNasCount() = 0;
        NAS_EMM_GetSecuUlNasCount() = 0;

        /*����������*/
        NAS_EMM_UpdateCurSecuCntxt();
    }
    else if(NAS_EMM_SMC_UPDATE_NON_CUR_NATIVE == NAS_EMM_GetSmcType())
    {
        /*Dl_NasCount��SMC�����Լ��ɹ�ʱ���Ѿ���ԭ���˴����ش���*/
        /*Ul_NasCount��ԭΪnon-current security context�е�Ul_NasCount*/
        NAS_EMM_SetSecuUlNasCount(NAS_EMM_GetSecuNonCurUlNasCount());

        /*����KSIasme��Kasme*/
        NAS_EMM_UpdateCurSecuCntxt();
    }
    else
    {
        /*ɾ�� new mapped security context*/
        NAS_EMM_ClearNewMappedSecuCntxt();
    }

    /* ���������EIA0������Ҫ��ֵKSI��KASME������������NAS COUNTΪ0,
       ɾ��������NV�еİ�ȫ������ */
    /*lint -e416 -e415*/
    ucSmcEia    = pstSmcMsg->aucNasMsg[NAS_EMM_SECU_SMC_ALG_POSE-NAS_EMM_SECU_PLAIN_MSG_POS] & NAS_EMM_LOW_3_BITS_F;
    ucKsiValue  = pstSmcMsg->aucNasMsg[NAS_EMM_SECU_SMC_KSI_POSE-NAS_EMM_SECU_PLAIN_MSG_POS] & NAS_EMM_LOW_3_BITS_F;
    /*lint +e416 +e415*/
    if (NAS_EMM_SECU_ALG_EIA0 == ucSmcEia)
    {
        if (ucKsiValue != NAS_EMM_GetSecuCurKSIasme())
        {
            NAS_LMM_MEM_CPY(    NAS_EMM_GetSecuCurKasmeAddr(),
                                NAS_EMM_GetEia0Kasme(),
                                NAS_LMM_SECU_AUTH_KEY_ASME_LEN);
        }

        NAS_EMM_SetSecuCurKSIsgsn(NAS_LMM_NKSI_NO_KEY_IS_AVAILABLE);
        NAS_EMM_SetSecuCurKSIasme(ucKsiValue);

        /*DL_NASCOUNT��UP_NASCOUNT ����*/
        NAS_EMM_GetSecuDlNasCount() = 0;
        NAS_EMM_GetSecuUlNasCount() = 0;

        /* ɾ��������NV�еİ�ȫ������ */
        NAS_LMM_WriteEpsSecuContext(NAS_NV_ITEM_DELETE);

        /* ֪ͨEMM EIA0�㷨���� */
        NAS_EMM_SendIntraEia0ActNotify();
    }

    /*����NasCK,NasIK*/
    NAS_LMM_MEM_CPY(                     NAS_EMM_GetSecuCurNasCkAddr(),
                                        NAS_EMM_GetSecuTempNasCkAddr(),
                                        NAS_LMM_SECU_NAS_KEY_LEN);
    NAS_LMM_MEM_CPY(                     NAS_EMM_GetSecuCurNasIkAddr(),
                                        NAS_EMM_GetSecuTempNasIkAddr(),
                                        NAS_LMM_SECU_NAS_KEY_LEN);

    /*�����㷨*/
    NAS_EMM_GetSecuAlg() = pstSmcMsg->aucNasMsg[NAS_EMM_PLAIN_SMC_ALG_POSE];

    /*����RRC_MM_INFO_CHNG_REQ��Ϣ*/
    NAS_EMM_SendSecuParamToRrc();

    /*����SECU_MODE_COMPLETE��Ϣ*/
    enIfImeisvReq = NAS_EMM_IsImeisvReq();
    NAS_EMM_SecuSendSmcCmp(enIfImeisvReq);
    /* ������ǰ��ȫ������ */
    NAS_EMM_SndOmLogEpsSecContextInfo();

    return;
}



/*lint -e416*/
/*lint -e415*/
/*lint -e831*/

VOS_UINT32  NAS_EMM_SmcCommProcess(LRRC_LNAS_MSG_STRU  *pstSmcMsg)/*lint -e416 -e415*/
{
    VOS_UINT32                          ulRslt = NAS_EMM_SECU_FAIL;
    VOS_UINT8                           ucSmcEia = NAS_EMM_NULL;

    NAS_EMM_SECU_LOG_INFO("NAS_EMM_SmcCommProcess enterd.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SmcCommProcess_ENUM,LNAS_ENTRY);

    /*�����Ϣ����*/
    if(NAS_EMM_CN_MT_SMC_CMD != pstSmcMsg->aucNasMsg[NAS_EMM_SECU_SMC_MT_POSE])
    {
        NAS_EMM_SECU_LOG_ERR("NAS_EMM_SmcCommProcess:SMC MT ERR.");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_SmcCommProcess_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_EMM_SECU_FAIL;
    }

    /*SMC��Ϣ�ϱ�*/
    NAS_LMM_SendOmtAirMsg(               NAS_EMM_OMT_AIR_MSG_DOWN,
                                        NAS_EMM_SECU_CMD,
                         (NAS_MSG_STRU*)pstSmcMsg);

    /*�ؼ��¼��ϱ� SECU_MODE_CMD*/
    NAS_LMM_SendOmtKeyEvent(EMM_OMT_KE_SECU_CMD);

    /*ֹͣT3416,ɾ�� RAND�� RES*/
    NAS_LMM_StopPtlTimer(                TI_NAS_EMM_PTL_T3416);
    NAS_EMM_SecuClearRandRes();


#if (VOS_OS_VER != VOS_WIN32)
    ucSmcEia =  pstSmcMsg->aucNasMsg[NAS_EMM_SECU_SMC_ALG_POSE] & NAS_EMM_LOW_3_BITS_F;

    /* �����EIA0�����ж��Ƿ��������ʹ��EIA0������ */
    if (NAS_EMM_SECU_ALG_EIA0 == ucSmcEia)
    {
        /* ��� (�Ȳ��ǽ���ע�������Ҳ��������������)������ģʽ�Ҳ��ǽ�����)��������ʹ��EIA0 */
        if(NAS_EMM_YES != NAS_EMM_IsRegStatusEmcRegingOrContainEmcBear())
        {
            NAS_EMM_SECU_LOG_NORM("NAS_EMM_SmcCommProcess:Rejected! it's not allowed to use EIA0.");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_SmcCommProcess_ENUM,LNAS_FUNCTION_LABEL2);
            NAS_EMM_SecuSendSmcRej(NAS_EMM_SMC_REJ_UNSPECIFIED);
            return NAS_EMM_SECU_FAIL;
        }
    }
#endif


    /*SMCЯ���Ĳ������:���ȶԿտ���Ϣ���룬Ȼ���SMC��ϢЯ���Ĳ������м���
      ����:KSI, �㷨, replayed UE_NET_CAP, replayed NONCEue,��������*/
    ulRslt = NAS_EMM_SmcVerifyParam(pstSmcMsg);
    if(NAS_EMM_SECU_FAIL == ulRslt)
    {
        return NAS_EMM_SECU_FAIL;
    }

    /*��SMC��Ϣ���������Լ��*/
    ulRslt = NAS_EMM_SmcIntCheck(pstSmcMsg);
    if(NAS_EMM_SECU_FAIL == ulRslt)
    {
        return NAS_EMM_SECU_FAIL;
    }

    /*SMC��Ϣ��֤�ɹ��Ĵ���*/
    /*NAS_EMM_SmcSucc(pstSmcMsg);*/

    return NAS_EMM_SECU_SUCC;
}
/*lint +e831*/
/*lint +e415*/
/*lint +e416*/



VOS_VOID NAS_EMM_HandleLrrcMsgSndFailForHandOver(
                                        NAS_EMM_MRRC_MGMT_DATA_STRU  *pEmmMrrcMgmtData,
                                        VOS_UINT32 *pulIsDelBuff)
{
    NAS_LMM_MAIN_STATE_ENUM_UINT16       enMainState;

    /* �ӵ�ǰ״̬���л�ȡ״̬ */
    enMainState                         = NAS_LMM_GetEmmCurFsmMS();

    if (EMM_MS_TAU_INIT == enMainState)
    {
        /*ֹͣT3430��ʱ��*/
        NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_TAU_T3430);

        /*ֹͣT3440��ʱ��*/
        NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_T3440);

        #if (FEATURE_ON == FEATURE_DSDS)
        /*����end notify��Ϣ��RRC��֪ͨRRC�ͷ���Դ*/
        NAS_EMM_TAU_SendRrcDsdsEndNotify();
        #endif
        /* ������:����TAU�Լ�COMM����DATA REQ����ʧ�ܴ��� */
        NAS_LMM_AddTauCounter(NAS_LMM_OM_PCE_TIMES_TYPE_DATA_CNF_FAIL);

        /* �������TAU����ԭ�� */
        NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_SND_MSG_FAIL);
    }
    else if (EMM_MS_SER_INIT == enMainState)
    {
        /* ������: ����Ser Comm����DATA REQ����ʧ�ܴ��� */
        NAS_LMM_AddSerCounter(NAS_LMM_OM_PCE_TIMES_TYPE_DATA_CNF_FAIL);
        /*  ��Ҫ����Ӧ�Ļ�����Ϣ��ulHoWaitSysInfoFlag����Ϊtrue */
        pEmmMrrcMgmtData->ulHoWaitSysInfoFlag = VOS_TRUE;
        *pulIsDelBuff = VOS_FALSE;
    }
    else
    {

    }

}


VOS_UINT32 NAS_EMM_SndCommonProcedureMsgFailProc(VOS_VOID* pMsg,VOS_UINT32 *pulIsDelBuff)
{
    LRRC_LMM_DATA_CNF_STRU              *pstRrcMmDataCnf = VOS_NULL_PTR;
    NAS_LMM_MAIN_STATE_ENUM_UINT16       enMainState;
    NAS_LMM_SUB_STATE_ENUM_UINT16        enSubState;
    NAS_EMM_MRRC_MGMT_DATA_STRU         *pEmmMrrcMgmtData = NAS_EMM_NULL_PTR;

    *pulIsDelBuff = VOS_TRUE;

    /*add by lifuxin for Lnas est process re-construct start*/
    NAS_LMM_EstingOrReleasingProcessTimerHandle();

    switch(NAS_EMM_CUR_MAIN_STAT)
    {
        case    EMM_MS_AUTH_INIT:

            NAS_LMM_IfEmmHasBeenPushedThenPop();
            NAS_EMM_PUBU_LOG_INFO(" NAS_EMM_SndCommonProcedureMsgFailProc enter");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_SndCommonProcedureMsgFailProc_ENUM,LNAS_FUNCTION_LABEL1);
            break;

        default:
            NAS_EMM_PUBU_LOG_INFO(" NAS_EMM_SndCommonProcedureMsgFailProc enter");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_SndCommonProcedureMsgFailProc_ENUM,LNAS_FUNCTION_LABEL2);
            break;
    }


    /* �ӵ�ǰ״̬���л�ȡ״̬ */
    enMainState                         = NAS_LMM_GetEmmCurFsmMS();
    enSubState                          = NAS_LMM_GetEmmCurFsmSS();

    pstRrcMmDataCnf = (LRRC_LMM_DATA_CNF_STRU*) pMsg;

    pEmmMrrcMgmtData = NAS_EMM_FindMsgInDataReqBuffer(pstRrcMmDataCnf->ulOpId);

    if (NAS_EMM_NULL_PTR == pEmmMrrcMgmtData)
    {
        return NAS_EMM_FAIL;
    }

    switch (pstRrcMmDataCnf->enSendRslt)
    {
        case LRRC_LMM_SEND_RSLT_FAILURE_HO:
            NAS_EMM_HandleLrrcMsgSndFailForHandOver(pEmmMrrcMgmtData, pulIsDelBuff);

            break;
        case LRRC_LMM_SEND_RSLT_FAILURE_TXN:
        case LRRC_LMM_SEND_RSLT_FAILURE_RLF:
            if (EMM_MS_REG_INIT == enMainState)
            {
                /* ������: ͳ��attach Comm����DATA REQ����ʧ�ܴ��� */
                NAS_LMM_AddAttachCounter(NAS_LMM_OM_PCE_TIMES_TYPE_DATA_CNF_FAIL);
                /* ����ATTACH���� */
                NAS_EMM_RestartAttProcedural();
            }
            else if (EMM_MS_DEREG_INIT == enMainState)
            {
                NAS_LMM_StopStateTimer(     TI_NAS_EMM_T3421);

                #if (FEATURE_ON == FEATURE_DSDS)
                /*����end notify��Ϣ��RRC��֪ͨRRC�ͷ���Դ*/
                NAS_LMM_SendRrcDsdsEndNotify(LRRC_LNAS_SESSION_TYPE_PS_DETACH);
                #endif

                /*����DETACH REQUEST��Ϣ*/
                NAS_EMM_SendDetachReqMo();
            }
            else if ((EMM_MS_REG == enMainState)
                       && (EMM_SS_REG_IMSI_DETACH_WATI_CN_DETACH_CNF == enSubState))
            {
                NAS_LMM_StopStateTimer(     TI_NAS_EMM_T3421);

                #if (FEATURE_ON == FEATURE_DSDS)
                /*����end notify��Ϣ��RRC��֪ͨRRC�ͷ���Դ*/
                NAS_LMM_SendRrcDsdsEndNotify(LRRC_LNAS_SESSION_TYPE_PS_DETACH);
                #endif


                /* ����IMSI DETACH���� */
                NAS_EMM_SendImsiDetachReqMo();
            }
            else if (EMM_MS_TAU_INIT == enMainState)
            {
                /*ֹͣT3430��ʱ��*/
                NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_TAU_T3430);

                #if (FEATURE_ON == FEATURE_DSDS)
                /*����end notify��Ϣ��RRC��֪ͨRRC�ͷ���Դ*/
                NAS_EMM_TAU_SendRrcDsdsEndNotify();
                #endif

                /*ֹͣT3440��ʱ��*/
                NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_T3440);
                /* ������:����TAU COMM����DATA REQ����ʧ�ܴ��� */
                NAS_LMM_AddTauCounter(NAS_LMM_OM_PCE_TIMES_TYPE_DATA_CNF_FAIL);

                /* �������TAU����ԭ�� */
                NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_SND_MSG_FAIL);
            }
            else if (EMM_MS_SER_INIT == enMainState)
            {
                /* ������: ����Ser Comm����DATA REQ����ʧ�ܴ��� */
                NAS_LMM_AddSerCounter(NAS_LMM_OM_PCE_TIMES_TYPE_DATA_CNF_FAIL);
                NAS_EMM_RestartSerProcedural();
            }
            else
            {

            }

            break;

        default:
            break;
        }

    return NAS_EMM_SUCC;

}
/*lint +e961*/
/*lint +e960*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

