
#include "vos_Id.h"
#include "usimmbase.h"
#include "usimmapdu.h"
#include "usimmdl.h"
#include "NvIdList.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID PS_FILE_ID_USIMM_CUIM_C
/*lint +e767*/

#if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_OFF == FEATURE_UE_UICC_MULTI_APP_SUPPORT))

USIMM_CARD_VERSION_TYPE_UINT8   g_enCardVersionType;

/*��ǰADF��Ϣ*/
USIMM_ADF_INFO_STRU             g_stCSIMADFInfo;

VOS_UINT8                       g_aucCUIMCstInfo[USIMM_EF_CST_MAX_LEN] = {0};   /*����洢CST�ļ��Ŀռ�*/

VOS_UINT8                       g_ucCSIMESTInfo;

VOS_UINT8                       g_ucStoreEsMeidResult;


VOS_VOID UICC_InitCsimGlobal(VOS_VOID)
{
    gstUSIMMBaseInfo.ucCLA        = USIMM_USIM_CLA;

    gastUSIMMCardAppInfo[USIMM_UICC_CDMA].enCardType    = USIMM_CARD_CSIM;

    gastUSIMMCardAppInfo[USIMM_UICC_CDMA].enStateChange = USIMM_CARD_STATE_CHANGED; /*��Ҫ�ϱ���״̬*/

    /*lint -e534*/
    VOS_MemSet(&g_stCSIMADFInfo, 0, sizeof(g_stCSIMADFInfo));
    /*lint +e534*/

    return ;
}
VOS_VOID UICC_InitUimGlobal(VOS_VOID)
{
    /*lint -e534*/
    VOS_MemSet(&g_stCSIMADFInfo, 0, sizeof(g_stCSIMADFInfo));
    /*lint +e534*/

    gstUSIMMBaseInfo.ucCLA                              = USIMM_SIM_CLA;

    gastUSIMMCardAppInfo[USIMM_UICC_CDMA].enCardType    = USIMM_CARD_UIM;

    gastUSIMMCardAppInfo[USIMM_UICC_CDMA].enStateChange = USIMM_CARD_STATE_CHANGED; /*��Ҫ�ϱ���״̬*/

    /* SIM ��֧�ֹ��� */
    gstUSIMMBaseInfo.enSupportPath                      = USIMM_NOTSUPPORT_PATH;

    gstUSIMMBaseInfo.enSupportSFI                       = USIMM_NOTSUPPORT_SFI;

    gstUSIMMBaseInfo.enSupportChannel                   = USIMM_NOTSUPPORT_CHANNEL;

    return ;
}


VOS_VOID UICC_InitUICCGlobal(VOS_VOID)
{
    UICC_InitCsimGlobal();

    (VOS_VOID)USIMM_InitUsimGlobal();

    gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardType    = USIMM_CARD_USIM;  /*ѡ���ļ�������Ҫʹ�����״̬*/

    g_enCardVersionType = USIMM_CARD_UICC_TYPE;

    return;
}
VOS_VOID UICC_InitICCGlobal(VOS_VOID)
{
    UICC_InitUimGlobal();

    (VOS_VOID)USIMM_InitSimGlobal();

    gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardType    = USIMM_CARD_SIM;  /*ѡ���ļ�������Ҫʹ�����״̬*/

    g_enCardVersionType = USIMM_CARD_ICC_TYPE;

    return;
}
VOS_VOID UICC_SaveDFPinInfo(USIMM_ADF_INFO_STRU *pstADFInfo)
{
    /*lint -e534*/
    VOS_MemCpy(&pstADFInfo->stPINInfo, &gstUSIMMCurFileInfo.stDFInfo.stPINInfo, sizeof(USIMM_PIN_INFO_STRU));
    /*lint +e534*/

    pstADFInfo->ucPIN1RefNum = gstUSIMMCurFileInfo.stDFInfo.ucPIN1RefNum;

    pstADFInfo->ucPIN2RefNum = gstUSIMMCurFileInfo.stDFInfo.ucPIN2RefNum;

    return;
}


VOS_UINT32 UICC_InitDecodeEFDIR(VOS_VOID)
{
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulAidLen;
    VOS_UINT32                          i;
    VOS_UINT8                          *pucdata;
    VOS_UINT8                           aucUsimRidAppCode[USIMM_RID_LEN + USIMM_APP_CODE_LEN] = {0xA0,0x00,0x00,0x00,0x87,0x10,0x02};
    VOS_UINT8                           aucCsimRidAppCode[USIMM_RID_LEN + USIMM_APP_CODE_LEN] = {0xA0,0x00,0x00,0x03,0x43,0x10,0x02};
    VOS_UINT16                          ausPath[] = {MF, EFDIR};

    ulResult = USIMM_SelectFile(USIMM_UMTS_APP, USIMM_NEED_FCP, ARRAYSIZE(ausPath), ausPath);

    if(VOS_OK != ulResult)/*ѡ���ļ�*/
    {
        USIMM_ERROR_LOG("USIMM_DecodeEFDIR: EFDIR could not Found");/*��ӡ����*/

        return VOS_ERR;
    }

    pucdata = (VOS_UINT8 *)VOS_MemAlloc(WUEPS_PID_USIM,DYNAMIC_MEM_PT,gstUSIMMCurFileInfo.stEFInfo.usFileLen);

    if(VOS_NULL_PTR == pucdata)   /*�жϽ��*/
    {
        USIMM_ERROR_LOG("USIMM_DecodeEFDIR: VOS_MemAlloc Error");/*��ӡ����*/

        return VOS_ERR;
    }

    if(USIMM_EFSTRUCTURE_FIXED == gstUSIMMCurFileInfo.stEFInfo.enFileType)
    {
        if (USIMM_SW_OK != USIMM_ReadLFFile(&gstUSIMMCurFileInfo.stEFInfo, USIMM_READ_ALLRECORD, pucdata))      /*��ȡ��¼����*/
        {
            USIMM_INFO_LOG("USIMM_DecodeEFDIR: USIMM_ReadLFFile Error");

            /*lint -e534*/
            VOS_MemFree(WUEPS_PID_USIM, pucdata);
            /*lint +e534*/

            return VOS_ERR;
        }
    }
    else
    {
        USIMM_ERROR_LOG("USIMM_DecodeEFDIR: EFDIR File Type Error");/*��ӡ����*/

        /*lint -e534*/
        VOS_MemFree(WUEPS_PID_USIM, pucdata);
        /*lint +e534*/

        return VOS_ERR;                                              /*����102.221 13.1 �ڲ�֧�ֶ����Ƹ�ʽ�ļ�*/
    }

    ulResult = VOS_ERR;

    for(i=0; i<gstUSIMMCurFileInfo.stEFInfo.usFileLen; i+=gstUSIMMCurFileInfo.stEFInfo.ucRecordLen)
    {
        if ( (APP_TMP_TAG != pucdata[i + APP_TMP_TAG_OFFSET])
          || (APP_IND_TAG != pucdata[i + APP_IND_TAG_OFFSET]))    /*�ж����ݺϷ���*/
        {
            USIMM_WARNING_LOG("USIMM_DecodeEFDIR: EFDIR Content not Right");/*��ӡ����*/

            continue;
        }

        ulAidLen = (pucdata[i + APP_AID_LEN_OFFSET] > USIMM_AID_LEN_MAX)?USIMM_AID_LEN_MAX:pucdata[i + APP_AID_LEN_OFFSET];

        /* ֻҪƥ�䵽A0000000871002����Ϊ�ҵ���USIM��AID */
        if (VOS_OK == VOS_MemCmp(pucdata + i + APP_AID_VALUE_OFFSET, aucUsimRidAppCode, sizeof(aucUsimRidAppCode)))
        {
            g_astAidInfo[USIMM_AID_TYPE_USIM].ulAIDLen = ulAidLen;

            /*lint -e534*/
            VOS_MemCpy(g_astAidInfo[USIMM_AID_TYPE_USIM].aucAID, pucdata + i + APP_AID_VALUE_OFFSET, ulAidLen);    /*���������Ϣ*/
            /*lint +e534*/

            ulResult = VOS_OK;
        }

        /* ֻҪƥ�䵽A0000003431002����Ϊ�ҵ���CSIM��AID */
        if (VOS_OK == VOS_MemCmp(pucdata + i + APP_AID_VALUE_OFFSET, aucCsimRidAppCode, sizeof(aucCsimRidAppCode)))
        {
            g_astAidInfo[USIMM_AID_TYPE_CSIM].ulAIDLen = ulAidLen;

            /*lint -e534*/
            VOS_MemCpy(g_astAidInfo[USIMM_AID_TYPE_CSIM].aucAID, pucdata + i + APP_AID_VALUE_OFFSET, ulAidLen);    /*���������Ϣ*/
            /*lint +e534*/

            ulResult = VOS_OK;
        }
    }

    /*lint -e534*/
    VOS_MemFree(WUEPS_PID_USIM, pucdata);
    /*lint +e534*/

    return ulResult;
}
VOS_UINT32 UICC_InitCommResetStep(VOS_VOID)
{
    VOS_UINT32              ulResult;

    USIMM_InitGlobalVarOnReset();

    ulResult = USIMM_InitCardTypeByATR();   /*��ȡATR�жϿ�״̬*/

    if(VOS_OK != ulResult)     /*��ʼ����һ������*/
    {
        USIMM_ERROR_LOG("UICC_InitCommResetStep: USIMM_InitCardTypeByATR Error");   /*��ӡ����*/

        return VOS_ERR;
    }

    USIMM_NORMAL_LOG("UICC_InitCommResetStep: USIMM_InitCardTypeByATR is Finished");

    return VOS_OK ;
}
VOS_VOID UICC_GetTerminalProfile(USIMM_STK_CFG_STRU *pstProfileContent)
{
    VOS_UINT32                          ulResult;
    VOS_UINT8                           aucUsimProfile[]=STK_USIM_PROFILE_DEFAULT;
    VOS_UINT8                           aucSimProfile[]= STK_SIM_PROFILE_DEFAULT;

    /*��ȡNV���жϵ�ǰ��SAT״̬*/
    ulResult = NV_Read(en_NV_Item_TerminalProfile_Set, pstProfileContent, sizeof(USIMM_STK_CFG_STRU));

    if(NV_OK == ulResult)/*��ȡʧ�ܰ���Ĭ���·�*/
    {
        return;
    }

    USIMM_WARNING_LOG("UICC_GetTerminalProfile: NV_Read Failed");

    if (USIMM_CARD_CSIM == gastUSIMMCardAppInfo[USIMM_UICC_CDMA].enCardType)
    {
        /*lint -e534*/
        VOS_MemCpy(pstProfileContent->stUsimProfile.aucProfile, aucUsimProfile, sizeof(aucUsimProfile));
        /*lint +e534*/

        pstProfileContent->stUsimProfile.ucProfileLen = sizeof(aucUsimProfile);
    }
    else
    {
        /*lint -e534*/
        VOS_MemCpy(pstProfileContent->stSimProfile.aucProfile, aucSimProfile, sizeof(aucSimProfile));
        /*lint +e534*/

        pstProfileContent->stSimProfile.ucProfileLen = sizeof(aucSimProfile);
    }

    return;
}


/*****************************************************************************
�� �� ��  :UICC_TerminalProfileDownload
��������  :���ն����������·�
�������  :��
�������  :��
�� �� ֵ  :VOS_ERR
           VOS_OK

���ú���  :USIMM_GetTerminalProfile
        USIMM_TermimalProfile_APDU
        USIMM_CheckSW
*****************************************************************************/
VOS_UINT32 UICC_TerminalProfileDownload(VOS_VOID)
{
    USIMM_STK_CFG_STRU                  stProfileContent;
    VOS_UINT32                          ulResult;

    UICC_GetTerminalProfile(&stProfileContent);

    if (USIMM_CARD_CSIM == gastUSIMMCardAppInfo[USIMM_UICC_CDMA].enCardType)
    {
        USIMM_INFO_LOG("UICC_TerminalProfileDownload: Send usim Terminal");

        ulResult = USIMM_TermimalProfile_APDU(stProfileContent.stUsimProfile.ucProfileLen,
                                             stProfileContent.stUsimProfile.aucProfile);
    }
    else
    {
        USIMM_INFO_LOG("UICC_TerminalProfileDownload: Send sim Terminal");

        ulResult = USIMM_TermimalProfile_APDU(stProfileContent.stSimProfile.ucProfileLen,
                                             stProfileContent.stSimProfile.aucProfile);
    }

    if (VOS_OK != ulResult)
    {
        g_stUSIMMInitInfo.stUSIMMInfo.enTPDownloadStatus = USIMM_PROFILE_DOWNLOAD_FAIL;

        USIMM_ERROR_LOG("UICC_TerminalProfileDownload: USIMM_TermimalProfile_APDU Error");

        return USIMM_INIT_RESET;
    }

    return USIMM_INIT_OK;
}


VOS_UINT32 UICC_InitCommCSIMStep(VOS_VOID)
{
    VOS_UINT32          ulResult;

    ulResult = USIMM_InsertNoNeedPinFileToPool();

    if (VOS_OK != ulResult)
    {
        USIMM_WARNING_LOG("UICC_InitCommCSIMStep: USIMM_InsertNoNeedPinFileToPool Error");   /*��ӡ����*/

        return VOS_ERR;
    }

    ulResult = UICC_TerminalProfileDownload();

    if (VOS_OK != ulResult)
    {
        USIMM_WARNING_LOG("UICC_InitCommCSIMStep: UICC_TerminalProfileDownload Error");   /*��ӡ����*/
    }

    /* ����AIDѡ��3GӦ�� */
    ulResult = UICC_InitDecodeEFDIR();

    /* �������EFDIR�ɹ���˵����USIM������ATR���ݽ����ĵڶ��� */
    if (VOS_OK == ulResult)
    {
        USIMM_DecodeATRSecondStep();
    }

    if (VOS_OK != ulResult)
    {
        USIMM_WARNING_LOG("UICC_InitCommCSIMStep: UICC_InitDecodeEFDIR Error");   /*��ӡ����*/

        return VOS_ERR;
    }

    return VOS_OK;
}
VOS_UINT32 UICC_InitCommUIMStep(VOS_VOID)
{
    VOS_UINT32                          ulResult;

    USIMM_INFO_LOG("UICC_InitCommUIMStep: This Card is Sim Card");

    ulResult = USIMM_InsertNoNeedPinFileToPool();

    if (VOS_OK != ulResult)
    {
        USIMM_WARNING_LOG("UICC_InitCommUIMStep: USIMM_InsertNoNeedPinFileToPool is Failed");     /*��ӡ����*/

        return VOS_ERR;
    }

    return VOS_OK;
}
VOS_UINT32 UICC_InitCommStep(VOS_VOID)
{
    VOS_UINT32              ulResult;

    if(VOS_OK != UICC_InitCommResetStep())     /*��ʼ����һ������*/
    {
        USIMM_ERROR_LOG("UICC_InitCommStep: UICC_InitCommResetStep Error");   /*��ӡ����*/

        return VOS_ERR;
    }

    UICC_InitUICCGlobal();

    ulResult = UICC_InitCommCSIMStep();

    if (VOS_OK != ulResult)
    {
        if (VOS_OK != UICC_InitCommResetStep())
        {
            USIMM_ERROR_LOG("UICC_InitCommStep: UICC_InitCommResetStep again Error");   /*��ӡ����*/

            return VOS_ERR;
        }

        UICC_InitICCGlobal();

        ulResult = UICC_InitCommUIMStep();
    }

    if (VOS_OK != ulResult)
    {
        USIMM_InitGlobalVarOnReset();

        gastUSIMMCardAppInfo[USIMM_UICC_CDMA].enCardType    = USIMM_CARD_UIM;   /*��״̬�㲥��ʱ����Ҫ�ܹ�����CDMA*/
    }

    gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardType    = USIMM_CARD_NOCARD;  /* �ָ�ȫ�ֱ������� */

    return ulResult;
}
VOS_UINT32 UICC_SelectCSIMADF(VOS_VOID)
{
    VOS_UINT32                          ulResult;
    USIMM_APDU_ST                       stApduInfo = {0};

    stApduInfo.aucAPDU[P1] = USIMM_SELECT_BY_DF_NAME;
    stApduInfo.aucAPDU[P2] = USIMM_SELECT_RETURN_FCP_TEMPLATE;
    stApduInfo.aucAPDU[P3] = (VOS_UINT8)g_stCSIMADFInfo.ulAIDLen;

    /*lint -e534*/
    VOS_MemCpy(stApduInfo.aucSendBuf, g_stCSIMADFInfo.aucAID, (VOS_UINT8)g_stCSIMADFInfo.ulAIDLen);
    /*lint +e534*/

    ulResult = USIMM_ReselectFileAPDU(&stApduInfo);

    if(VOS_OK == ulResult) /*�ж�AIDѡ����*/
    {
        USIMM_ClearCurEFInfo(&gstUSIMMCurFileInfo);/*ѡ��DF�ļ����ϴ�ѡ�е�EF�ļ���Ϊ��Чֵ*/

        ulResult = USIMM_DecodeDFFcp(USIMM_CARD_CSIM, &stApduInfo, &gstUSIMMCurFileInfo);
    }
    else
    {
        USIMM_ERROR_LOG("USIMM_SelectUiccADF: Select File Error");/*��ӡ����*/

        ulResult = VOS_ERR;
    }

    if(VOS_OK == ulResult)
    {
        gstUSIMMCurFileInfo.usCurDFID   = ADF;

        g_stCSIMADFInfo.ucCharaByte     = gstUSIMMCurFileInfo.stDFInfo.ucCharaByte;

        g_stCSIMADFInfo.ucSupCmd        = gstUSIMMCurFileInfo.stDFInfo.ucSupCmd;
    }

    return ulResult;
}
VOS_UINT32 UICC_InitCUIMTFileContent(VOS_UINT16 usFileID, USIMM_U8_LVDATA_STRU *pstFileData)
{
    USIMM_GET_COMM_FILE_STRU    stFileInfo;
    USIMM_GETCNF_INFO_STRU      stCnfInfo;
    VOS_UINT32                  ulResult;
    VOS_UINT16                  ausFilePath[3];

    if (EFUNDERDF != USIMM_FILE_TYPE(usFileID))
    {
        USIMM_ERROR_LOG("UICC_InitCUIMTFile: File is not a EF");

        return VOS_ERR;
    }

    /*lint -e534*/
    VOS_MemSet(&stFileInfo, 0, sizeof(USIMM_GET_COMM_FILE_STRU));

    VOS_MemSet(&stCnfInfo, 0, sizeof(USIMM_GETCNF_INFO_STRU));
    /*lint +e534*/

    ausFilePath[0] = MF;
    ausFilePath[2] = usFileID;

    if (USIMM_CARD_CSIM == gastUSIMMCardAppInfo[USIMM_UICC_CDMA].enCardType)
    {
        ausFilePath[1]          = ADF;

        stFileInfo.enAppType    = USIMM_UNLIMIT_APP;
    }
    else
    {
        ausFilePath[1]          = DFCDMA;

        stFileInfo.enAppType    = USIMM_UNLIMIT_APP;
    }

    stFileInfo.ulPathLen    = 3;    /*�̶�MF/DF/EF��·������*/
    stFileInfo.pusFilePath  = ausFilePath;

    ulResult = USIMM_GetCdmaFileFromCard(&stFileInfo, &stCnfInfo);

    if (VOS_OK != ulResult)
    {
        USIMM_ERROR_LOG("UICC_InitCUIMTFile: USIMM_GetCdmaFileFromCard is failed");

        return VOS_ERR;
    }

    pstFileData->pucData    = stCnfInfo.pucEf;

    pstFileData->ulDataLen  = stCnfInfo.usEfLen;

    return VOS_OK ;
}
VOS_VOID UICC_InitCUIMTFile(VOS_UINT16 usFileID)
{
    USIMM_U8_LVDATA_STRU                stContent;
    VOS_UINT32                          ulResult;

    stContent.ulDataLen = 0;
    stContent.pucData   = VOS_NULL_PTR;

    ulResult = UICC_InitCUIMTFileContent(usFileID, &stContent);

    if (VOS_ERR != ulResult)
    {
        /*lint -e534*/
        VOS_MemFree(WUEPS_PID_USIM, stContent.pucData);
        /*lint +e534*/
    }

    if (VOS_NULL_PTR != stContent.pucData)
    {
        /*lint -e534*/
        VOS_MemFree(WUEPS_PID_USIM, stContent.pucData);
        /*lint +e534*/
    }

    return;
}


VOS_VOID UICC_InitCUIMEccFile(VOS_VOID)
{
    USIMM_U8_LVDATA_STRU            stContent;

    if (VOS_OK != UICC_InitCUIMTFileContent(EF_CUIM_ECC, &stContent))
    {
        return ;
    }

    /*�ϱ���ǰ��Ecc��������,����SIM ����ʽ����,�������Դ�*/
    /*USIMM_EccNumberInd(ECC_SIM, (VOS_UINT16)stContent.ulDataLen, VOS_NULL, stContent.pucData);*/

    /*lint -e534*/
    VOS_MemFree(WUEPS_PID_USIM, stContent.pucData);
    /*lint +e534*/

    return;
}


VOS_VOID UICC_InitCUIMCstFile(VOS_VOID)
{
    USIMM_U8_LVDATA_STRU                stContent;
    VOS_UINT32                          ulSaveLen;

    if (VOS_OK != UICC_InitCUIMTFileContent(EF_CUIM_CST, &stContent))
    {
        return ;
    }

    if (sizeof(g_aucCUIMCstInfo) > stContent.ulDataLen)
    {
        ulSaveLen = stContent.ulDataLen;
    }
    else
    {
        ulSaveLen = sizeof(g_aucCUIMCstInfo);
    }

    /*lint -e534*/
    VOS_MemCpy(g_aucCUIMCstInfo, stContent.pucData, ulSaveLen);

    VOS_MemFree(WUEPS_PID_USIM, stContent.pucData);
    /*lint +e534*/

    return;
}


VOS_VOID UICC_InitCSIMEstFile(VOS_VOID)
{
    USIMM_U8_LVDATA_STRU               stContent;

    if (VOS_OK != UICC_InitCUIMTFileContent(EF_CSIM_EST, &stContent))
    {
        return ;
    }

    g_ucCSIMESTInfo = stContent.pucData[0];

    if ((g_ucCSIMESTInfo &0x01) == 0x00)
    {
        gstUSIMMBaseInfo.enFDNStatus = USIMM_FDNSTATUS_OFF;
    }
    else
    {
        gstUSIMMBaseInfo.enFDNStatus = USIMM_FDNSTATUS_ON;
    }

    /*lint -e534*/
    VOS_MemFree(WUEPS_PID_USIM, stContent.pucData);
    /*lint +e534*/

    return;
}


VOS_UINT32 UICC_InitCUIMEsnMeid(VOS_VOID)
{
    VOS_UINT32              ulResult;
    NV_ESN_MEID_STRU        stNVData;

    /*lint -e534*/
    VOS_MemSet(&stNVData, 0, sizeof(NV_ESN_MEID_STRU));
    /*lint +e534*/

    ulResult = NV_Read(en_NV_Item_ESN_MEID, &stNVData, sizeof(NV_ESN_MEID_STRU));

    if (NV_OK != ulResult)
    {
        USIMM_ERROR_LOG("UICC_InitCUIMEsnMeid: NV_Read en_NV_Item_ESN_MEID Failed");

        //stNVData.enEsnMeIDFlag  = ESN_ME_ENABLE_FLAG;

        //stNVData.aucEsn[0]      = 7;

        return VOS_ERR;
    }

    /* ���ܹر� */
    if (ESN_MEID_DISABLE == stNVData.enEsnMeIDFlag)
    {
        return VOS_OK;
    }

    if (ESN_ME_ENABLE_FLAG == stNVData.enEsnMeIDFlag)
    {
        ulResult = USIMM_StoreESNMEID_APDU(UICC_STORE_ESN_P1, stNVData.aucEsn, &gstUSIMMAPDU);
    }
    else if (MEID_ME_ENABLE_FLAG == stNVData.enEsnMeIDFlag)
    {
        ulResult = USIMM_StoreESNMEID_APDU(UICC_STORE_MEID_P1, stNVData.aucMeID, &gstUSIMMAPDU);
    }
    else
    {
        USIMM_ERROR_LOG("UICC_InitCUIMEsnMeid: NV_Read en_NV_Item_ESN_MEID Flag error");

        ulResult = VOS_ERR;
    }

    if (VOS_OK == ulResult)
    {
        g_ucStoreEsMeidResult = gstUSIMMAPDU.aucRecvBuf[0];
    }
    else
    {
        USIMM_ERROR_LOG("UICC_InitCUIMEsnMeid: Command Send error");

        g_ucStoreEsMeidResult = VOS_NULL;
    }

    return ulResult;
}
VOS_UINT32 UICC_GetPUKRemainTime(VOS_UINT8 ucPINNo, USIMM_ADF_INFO_STRU *pstADFInfo)
{
    VOS_UINT32 ulResult;
    VOS_UINT8  ucRemain;

    ulResult = USIMM_UnblockPIN_APDU(ucPINNo, VOS_NULL_PTR,VOS_NULL_PTR);

    if(VOS_OK != ulResult)/*�жϽ��*/
    {
        USIMM_ERROR_LOG("USIMM_GetPUKRemainTime: USIMM_UnblockPIN_APDU Error");

        return VOS_ERR;
    }

    if(0x63 == gstUSIMMAPDU.ucSW1)
    {
        ucRemain = gstUSIMMAPDU.ucSW2&0x0F;
    }
    else
    {
        ucRemain = 0;
    }

    if(pstADFInfo->ucPIN1RefNum == ucPINNo)
    {
        pstADFInfo->stPINInfo.ucPuk1RemainTime = ucRemain;
    }
    else if(pstADFInfo->ucPIN2RefNum == ucPINNo)
    {
        pstADFInfo->stPINInfo.ucPuk2RemainTime = ucRemain;
    }
    else
    {
        return VOS_ERR;
    }

    return VOS_OK;
}
VOS_UINT32 UICC_GetPINRemainTime(VOS_UINT8 ucPINNo, USIMM_ADF_INFO_STRU *pstADFInfo)
{
    VOS_UINT32  ulResult;
    VOS_UINT8   ucRemain;

    ulResult = USIMM_PINVerify_APDU(CMD_INS_VERIFY,ucPINNo, VOS_NULL_PTR);

    if(VOS_OK != ulResult)/*�жϽ��*/
    {
        USIMM_ERROR_LOG("USIMM_GetPINRemainTime: USIMM_PINVerify_APDU Error");

        return VOS_ERR;
    }

    if(0x63 == gstUSIMMAPDU.ucSW1)
    {
        ucRemain = gstUSIMMAPDU.ucSW2&0x0F;
    }
    else
    {
        ucRemain = 0;
    }

    if(pstADFInfo->ucPIN1RefNum == ucPINNo)
    {
        pstADFInfo->stPINInfo.ucPin1RemainTime = ucRemain;
    }
    else if(pstADFInfo->ucPIN2RefNum == ucPINNo)
    {
        pstADFInfo->stPINInfo.ucPin2RemainTime = ucRemain;
    }
    else
    {
        return VOS_ERR;
    }

    return VOS_OK;
}
VOS_UINT32 UICC_InitPINRemainTime(USIMM_ADF_INFO_STRU *pstADFInfo)
{
    VOS_UINT32 ulResult;

    /*��ʼ��PIN1ʣ�����*/
    if ((pstADFInfo->ucPIN1RefNum >= 0x01)&&(pstADFInfo->ucPIN1RefNum <= 0x08))
    {
        USIMM_INFO_LOG("UICC_InitPINRemainTime: Get PIN 1");

        ulResult = UICC_GetPINRemainTime(pstADFInfo->ucPIN1RefNum, pstADFInfo);

        if(VOS_OK != ulResult)
        {
            USIMM_ERROR_LOG("UICC_InitPINRemainTime: Get PIN 1 Times error");

            return VOS_ERR;
        }
    }

    /*��ʼ��PIN2ʣ�����*/
    if ((pstADFInfo->ucPIN2RefNum >= 0x81)&&(pstADFInfo->ucPIN2RefNum <= 0x88))
    {
        USIMM_INFO_LOG("UICC_InitPINRemainTime: Get PIN 2");

        ulResult = UICC_GetPINRemainTime(pstADFInfo->ucPIN2RefNum, pstADFInfo);

        if(VOS_OK != ulResult)
        {
            USIMM_ERROR_LOG("UICC_InitPINRemainTime: Get PIN 2 Times error");

            return VOS_ERR;
        }
    }

    /*��ʼ��PUK1ʣ�����*/
    if ((pstADFInfo->ucPIN1RefNum >= 0x01)&&(pstADFInfo->ucPIN1RefNum <= 0x08))
    {
        USIMM_INFO_LOG("UICC_InitPINRemainTime: Get PUK 1");

        ulResult = UICC_GetPUKRemainTime(pstADFInfo->ucPIN1RefNum, pstADFInfo);

        if(VOS_OK != ulResult)
        {
            USIMM_ERROR_LOG("UICC_InitPINRemainTime: Get PUK 1 Times error");

            return VOS_ERR;
        }
    }

    /*��ʼ��PUK2ʣ���ʱ*/
    if ((pstADFInfo->ucPIN2RefNum >= 0x81)&&(pstADFInfo->ucPIN2RefNum <= 0x88))
    {
        USIMM_INFO_LOG("UICC_InitPINRemainTime: Get PUK 2");

        ulResult = UICC_GetPUKRemainTime(pstADFInfo->ucPIN2RefNum, pstADFInfo);

        if(VOS_OK != ulResult)
        {
            USIMM_ERROR_LOG("UICC_InitPINRemainTime: Get PUK 2 Times error");

            return VOS_ERR;
        }
    }

    return VOS_OK;
}


VOS_UINT32 UICC_InitCardAppPINInfo(USIMM_CARD_VERSION_TYPE_UINT8 enCardVersionType, USIMM_ADF_INFO_STRU *pstADFInfo)
{
    VOS_UINT32 ulResult;

    UICC_SaveDFPinInfo(pstADFInfo);

    if(USIMM_CARD_UICC_TYPE == enCardVersionType)
    {
        ulResult = UICC_InitPINRemainTime(pstADFInfo);  /*��ʼ��PINʣ�����*/

        if(VOS_OK != ulResult)
        {
            return VOS_ERR;
        }
    }

    if((USIMM_PIN_ENABLED == pstADFInfo->stPINInfo.enPin2Enable)
        &&(0 != pstADFInfo->stPINInfo.ucPin2RemainTime))
    {
        pstADFInfo->enPin2Verified = USIMM_PIN_NEED;
    }

    if((USIMM_PIN_ENABLED == pstADFInfo->stPINInfo.enPin1Enable)
        &&(0 != pstADFInfo->stPINInfo.ucPin1RemainTime))
    {
        pstADFInfo->enPin1Verified = USIMM_PIN_NEED;
    }

    return VOS_OK;
}
VOS_VOID UICC_AdjudgeAppState(USIMM_CARD_APP_INFO_ST *pstAppState, USIMM_ADF_INFO_STRU *pstADFInfo)
{
    USIMM_CARD_SERVIC_ENUM_UINT32 enProCardService;

    enProCardService = pstAppState->enCardService;    /*���浱ǰ�Ŀ�״̬*/

    /*�ж�����״̬*/
    if (0 == pstADFInfo->stPINInfo.ucPin1RemainTime)    /*PIN1ʣ��0��*/
    {
        USIMM_NORMAL_LOG("UICC_AdjudgeAppState: The PIN of the Card is Block");

        pstADFInfo->enPin1Verified  = USIMM_PUK_NEED;
    }

    if (0 == pstADFInfo->stPINInfo.ucPin2RemainTime)    /*PIN2ʣ��0��*/
    {
        USIMM_NORMAL_LOG("UICC_AdjudgeAppState: The PIN2 of the Card is Block");

        pstADFInfo->enPin2Verified  = USIMM_PUK_NEED;
    }

    if(0 == pstADFInfo->stPINInfo.ucPuk1RemainTime)    /*PUK1ʣ��0��*/
    {
        USIMM_WARNING_LOG("UICC_AdjudgeAppState: The Card PUK is Block, Card Could Not Used");

        pstADFInfo->enPin1Verified  = USIMM_PUK_BLOCK;
    }

    /*��������״̬�жϿ�״̬*/
    if(USIMM_PUK_BLOCK == pstADFInfo->enPin1Verified)/*�ж�PUK BLOCK״̬*/
    {
        USIMM_NORMAL_LOG("UICC_AdjudgeAppState: PUK is Block");

        gstUSIMMBaseInfo.enCurPINType   = USIMM_PUK;

        pstAppState->enCardService   = USIMM_CARD_SERVIC_UNAVAILABLE;
    }
    else if(USIMM_PUK_NEED == pstADFInfo->enPin1Verified)/*�ж�PUK״̬*/
    {
        USIMM_NORMAL_LOG("UICC_AdjudgeAppState: The Card Need the PUK Password");

        if (USIMM_POOL_AVAILABLE == gstUSIMMPOOL.enPoolStatus)
        {
            gstUSIMMPOOL.enPoolStatus = USIMM_POOL_NEED_PASSWORD;
        }

        gstUSIMMBaseInfo.enCurPINType = USIMM_PUK;

        pstAppState->enCardService = USIMM_CARD_SERVIC_SIM_PUK;
    }
    else if(USIMM_PIN_NEED == pstADFInfo->enPin1Verified) /*���жϵ�ǰPIN1״̬*/
    {
        USIMM_NORMAL_LOG("UICC_AdjudgeAppState: The Card Need the PIN Password");

        if (USIMM_POOL_AVAILABLE == gstUSIMMPOOL.enPoolStatus)
        {
            gstUSIMMPOOL.enPoolStatus = USIMM_POOL_NEED_PASSWORD;
        }

        gstUSIMMBaseInfo.enCurPINType = USIMM_PIN;

        pstAppState->enCardService = USIMM_CARD_SERVIC_SIM_PIN;
    }
    else if(USIMM_PUK_NEED == pstADFInfo->enPin2Verified)   /*���ж�PUK2״̬*/
    {
        USIMM_NORMAL_LOG("UICC_AdjudgeAppState: The Card Need the PUK2 Password");

        gstUSIMMBaseInfo.enCurPINType = USIMM_PUK2;

        pstAppState->enCardService = USIMM_CARD_SERVIC_AVAILABLE;
    }
    else  /*���ж�PIN2״̬*/                                                                                  /*���Ĭ����ҪPIN2*/
    {
        USIMM_NORMAL_LOG("UICC_AdjudgeAppState: The Card Need the PIN2 Password");

        gstUSIMMBaseInfo.enCurPINType = USIMM_PIN2;

        pstAppState->enCardService = USIMM_CARD_SERVIC_AVAILABLE;
    }

    if(enProCardService != pstAppState->enCardService )
    {
        USIMM_NORMAL_LOG("UICC_AdjudgeAppState: The Card State is Changed, Need Report the Card State");

        pstAppState->enStateChange = USIMM_CARD_STATE_CHANGED;
    }

    return ;
}
VOS_UINT32 UICC_InitCSIMNeedPINStep(VOS_VOID)
{
    VOS_UINT16  aucFileList[] = {EF_CUIM_USGIND, EF_CUIM_SP, EF_CUIM_IMSIM, EF_CUIM_IMSIT, EF_CUIM_ACCOLC, EF_CUIM_PRL, EF_CUIM_EPRL, EF_CUIM_MAXPRL, EF_CUIM_TMSI};
    VOS_UINT32  i;

    /*Read EF AD*/
    UICC_InitCUIMTFile(EF_CUIM_AD);

    /*Save EF CST*/
    UICC_InitCUIMCstFile();

    /*Read EF EST*/
    UICC_InitCSIMEstFile();

    UICC_CsimFDNCheck();

    /*Read UIMID*/
    UICC_InitCUIMTFile(EF_CUIM_RUIMID);

    /*ESM MEID Management*/
    if (VOS_OK != UICC_InitCUIMEsnMeid())
    {
        USIMM_ERROR_LOG("UICC_InitCSIMNeedPINStep: UICC_InitCUIMEsnMeid Failed ");

        return VOS_ERR;
    }

    /*Read USGING, SP, IMSI_M, IMSI_T, ACCOLC, PRL, EPRL, MAXPRL*/
    for(i=0; i<ARRAYSIZE(aucFileList); i++)
    {
        UICC_InitCUIMTFile(aucFileList[i]);
    }

    /*Status*/
    /*lint -e534*/
    USIMM_Status_APDU(USIMM_STATUS_CURAPP_INITIALIZED, USIMM_STATUS_NO_DATA_RETURNED, 0x00);
    /*lint +e534*/

    return VOS_OK;
}
VOS_UINT32 UICC_InitCSIM(VOS_VOID)
{
    if (VOS_NULL == g_astAidInfo[USIMM_AID_TYPE_CSIM].ulAIDLen)
    {
        return VOS_ERR;
    }

    g_stCSIMADFInfo.ulAIDLen = g_astAidInfo[USIMM_AID_TYPE_CSIM].ulAIDLen;

    /*lint -e534*/
    VOS_MemCpy(g_stCSIMADFInfo.aucAID, g_astAidInfo[USIMM_AID_TYPE_CSIM].aucAID, g_astAidInfo[USIMM_AID_TYPE_CSIM].ulAIDLen);
    /*lint +e534*/

    if (VOS_OK != UICC_SelectCSIMADF())
    {
        USIMM_ERROR_LOG("UICC_InitCSIM: UICC_SelectCSIMADF failed");

        return VOS_ERR;
    }

    if (VOS_OK != UICC_InitCardAppPINInfo(g_enCardVersionType, &g_stCSIMADFInfo))
    {
        USIMM_ERROR_LOG("UICC_InitCSIM: UICC_InitCardAppPINInfo failed");

        return VOS_ERR;
    }

    UICC_AdjudgeAppState(&gastUSIMMCardAppInfo[USIMM_UICC_CDMA] , &g_stCSIMADFInfo);

    /*Read ECC*/
    UICC_InitCUIMEccFile();

    if (((0 != g_stCSIMADFInfo.stPINInfo.ucPin1RemainTime)
        &&(USIMM_PIN_ENABLED !=  g_stCSIMADFInfo.stPINInfo.enPin1Enable)))
    {
        if ( VOS_OK != UICC_InitCSIMNeedPINStep())
        {
            USIMM_ERROR_LOG("UICC_InitCSIM: UICC_InitCSIMNeedPINStep failed");

            return VOS_ERR;
        }
    }

    return VOS_OK;
}
VOS_VOID UICC_UIMFdnRequest(USIMM_FDNSTATUS_ENUM_UINT32 *pulFdnStatus)
{
    VOS_UINT16                          ausPath[] = {MF, DFCDMA, EFADN};
    VOS_UINT32                          ulResult;

    /* ��FDN״̬��SST�ļ���δallocated and activated,FDNδ���� */
    if (PS_USIM_SERVICE_NOT_AVAILIABLE == USIMM_IsServiceAvailable(UIM_SVR_FDN))
    {
        *pulFdnStatus = USIMM_FDNSTATUS_OFF;

        return;
    }

    /* ��ADN״̬��SST�ļ���δallocated and activated,FDN���� */
    if (PS_USIM_SERVICE_NOT_AVAILIABLE == USIMM_IsServiceAvailable(UIM_SVR_ADN))
    {
        *pulFdnStatus = USIMM_FDNSTATUS_ON;

        return;
    }

    /* ADN�ļ�������,FDN���� */
    ulResult = USIMM_SelectFile(USIMM_GSM_APP, USIMM_NEED_FCP, ARRAYSIZE(ausPath), ausPath);

    if (VOS_OK != ulResult)
    {
        *pulFdnStatus = USIMM_FDNSTATUS_ON;
    }
    else
    {
        /* ADN�ļ���Ч,FDN���� */
        if (USIMM_EFSTATUS_DEACTIVE == gstUSIMMCurFileInfo.stEFInfo.enFileStatus)
        {
            *pulFdnStatus = USIMM_FDNSTATUS_ON;
        }
        /* ADN�ļ���Ч,FDNδ���� */
        else
        {
            *pulFdnStatus = USIMM_FDNSTATUS_OFF;
        }
    }

    return;
}

VOS_VOID UICC_UimFDNProcedure(VOS_VOID)
{
    VOS_UINT16                          ausFileList[] = {EF_CUIM_IMSIM, EF_CUIM_IMSIT, EF_CUIM_TMSI};
    VOS_UINT16                          ausPath[] = {MF, DFCDMA, 0x0};
    VOS_UINT32                          ulResult;
    VOS_UINT32                          i;

    UICC_UIMFdnRequest(&gstUSIMMBaseInfo.enFDNStatus);

    for (i=0; i<ARRAYSIZE(ausFileList); i++)
    {
        /*Selct IMSI_M, IMSI_T, TMSI*/
        ausPath[2] = ausFileList[i];

        ulResult = USIMM_SelectCdmaFile(USIMM_NEED_FCP, ARRAYSIZE(ausPath), ausPath);

        if (VOS_OK != ulResult)
        {
            USIMM_ERROR_LOG("UICC_UimFDNProcedure: One Mandory file is absent");

            continue;
        }

        if (USIMM_EFSTATUS_DEACTIVE == gstUSIMMCurFileInfo.stEFInfo.enFileStatus)
        {
            ulResult = USIMM_ActivateFile_APDU();         /*change File Status*/
        }

        if (VOS_OK != ulResult)
        {
            USIMM_ERROR_LOG("UICC_UimFDNProcedure: USIMM_ActivateFile_APDU is failed");
        }
    }

    return;
}



VOS_VOID UICC_CsimFDNCheck(VOS_VOID)
{
    VOS_UINT16                          ausFileList[] = {EF_CUIM_IMSIM, EF_CUIM_IMSIT, EF_CUIM_TMSI};
    VOS_UINT16                          ausPath[] = {MF, ADF, 0x0};
    VOS_UINT32                          ulResult;
    VOS_UINT32                          i;

    for (i=0; i<ARRAYSIZE(ausFileList); i++)
    {
        /*Selct IMSI_M, IMSI_T, TMSI*/
        ausPath[2] = ausFileList[i];

        ulResult = USIMM_SelectCdmaFile(USIMM_NEED_FCP, ARRAYSIZE(ausPath), ausPath);

        if (VOS_OK != ulResult)
        {
            USIMM_ERROR_LOG("UICC_CsimFDNCheck: One Mandory file is absent");

            continue;
        }

        if (USIMM_EFSTATUS_DEACTIVE == gstUSIMMCurFileInfo.stEFInfo.enFileStatus)
        {
            USIMM_ERROR_LOG("UICC_UimFDNProcedure: One file is deactive");
        }
    }

    return ;
}

VOS_UINT32 UICC_InitUIMNeedPINStep(VOS_VOID)
{
    VOS_UINT16  aucFileList[] = {EF_CUIM_USGIND, EF_CUIM_SP, EF_CUIM_IMSIM, EF_CUIM_IMSIT, EF_CUIM_ACCOLC, EF_CUIM_PRL, EF_CUIM_EPRL, EF_CUIM_TMSI};
    VOS_UINT32  i;

    if (USIMM_INIT_OK != UICC_TerminalProfileDownload())
    {
        USIMM_WARNING_LOG("UICC_InitUIMNeedPINStep: Terminal Profile download error");
    }

    UICC_UimFDNProcedure();

    /*Read EF AD*/
    UICC_InitCUIMTFile(EF_CUIM_AD);

    /*Read EF CST*/
    UICC_InitCUIMCstFile();

    /*Read EF Revision*/
    UICC_InitCUIMTFile(EF_UIM_REVISION);

    /*ESN MEID Management*/
    if (VOS_OK != UICC_InitCUIMEsnMeid())
    {
        USIMM_ERROR_LOG("UICC_InitUIMNeedPINStep: UICC_InitCUIMEsnMeid Failed ");

        return VOS_ERR;
    }

    /*Read EF USGING, SP, IMSI_M, IMSI_T, ACCOLC, PRL, EPRL, TMSI*/
    for(i=0; i<ARRAYSIZE(aucFileList); i++)
    {
        UICC_InitCUIMTFile(aucFileList[i]);
    }

    return VOS_OK;
}
VOS_UINT32 UICC_InitUIM(VOS_VOID)
{
    VOS_UINT32                          ulResult;
    VOS_INT32                           lVoltageSwitchRst;
    VOS_UINT16                          ausPath[] = {MF, DFCDMA};

    ulResult = USIMM_SelectCdmaFile(USIMM_NEED_FCP, ARRAYSIZE(ausPath), ausPath);

    if (VOS_OK != ulResult)
    {
        USIMM_WARNING_LOG("UICC_InitUIM: Select SIM Card DFGSM is Failed");     /*��ӡ����*/

        return VOS_ERR;
    }

    if (0x10 == (gstUSIMMCurFileInfo.stDFInfo.ucCharaByte & 0x70)) /*SIM�������ļ������ֽ��л���ѹ*/
    {
        USIMM_NORMAL_LOG("UICC_InitUIM: SIM Card Need Change the Voltage.");

        g_stUSIMMInitInfo.stUSIMMInfo.ucVoltageSwitchFlag = VOS_TRUE;

        /*����λʧ�ܰ����޿�����*/
        if (VOS_OK != USIMM_DLResetCard(USIMM_CHANGE_VCC, &lVoltageSwitchRst))
        {
            USIMM_ERROR_LOG("UICC_InitUIM:SIM Card Change the Voltage Failed.");

            return VOS_ERR;      /*����Ҫ�������жϴ���*/
        }

        if (USIMM_SCI_NONEED_CHANGEVCC != lVoltageSwitchRst)
        {
            USIMM_ClearCurFileInfo();

            ulResult = USIMM_SelectCdmaFile(USIMM_NEED_FCP, ARRAYSIZE(ausPath), ausPath);

            /* ��ѹ�л�����ѡ��һ��DF */
            if (VOS_OK != ulResult)
            {
                USIMM_ERROR_LOG("UICC_InitUIM: Select DF again is Failed");

                return VOS_ERR;      /*����Ҫ�������жϴ���*/
            }
        }
    }

    if (VOS_OK != UICC_InitCardAppPINInfo(g_enCardVersionType, &g_stCSIMADFInfo))
    {
        return VOS_ERR;
    }

    UICC_AdjudgeAppState(&gastUSIMMCardAppInfo[USIMM_UICC_CDMA] , &g_stCSIMADFInfo);

    /*Read RUIMID*/
    UICC_InitCUIMTFile(EF_CUIM_RUIMID);

    /*Read ECC*/
    UICC_InitCUIMEccFile();

    if (((0 != g_stCSIMADFInfo.stPINInfo.ucPin1RemainTime)
        &&(USIMM_PIN_ENABLED !=  g_stCSIMADFInfo.stPINInfo.enPin1Enable)))
    {
        if ( VOS_OK != UICC_InitUIMNeedPINStep())
        {
            return VOS_ERR;
        }
    }

    return VOS_OK;
}


VOS_UINT32 UICC_InitCardHandle(USIMM_MsgBlock *pMsg)
{
    VOS_UINT32          ulResult;

    ulResult = UICC_InitCommStep();

    if (VOS_OK != ulResult)
    {
        g_enCardVersionType = USIMM_CARD_NON_TYPE;

        return VOS_ERR;
    }

    if (USIMM_CARD_UICC_TYPE == g_enCardVersionType)
    {
        ulResult = UICC_InitCSIM();
    }
    else
    {
        ulResult = UICC_InitUIM();
    }

    if (VOS_OK != ulResult)
    {
        ulResult = USIMM_InitCard(pMsg);
    }

    return ulResult;
}


VOS_UINT32 USIMM_SelectCdmaFile(USIMM_FILE_NEED_FCP_ENUM_UINT32     enEfFcpFlag,
                                        VOS_UINT32                          ulPathLen,
                                        VOS_UINT16                         *pusFilePath)
{
    USIMM_SELECT_PARA_STUR              stSelectPara;
    USIMM_U16_LVDATA_STRU               stFileAllPath = {0};
    VOS_UINT32                          ulResult;
    VOS_UINT16                          usCurPathLen;

    if (USIMM_CARD_CSIM == gastUSIMMCardAppInfo[USIMM_UICC_CDMA].enCardType)
    {
        stSelectPara.enCardType = USIMM_CARD_USIM;
    }
    else
    {
        stSelectPara.enCardType = USIMM_CARD_SIM;
    }

    stSelectPara.enEfFcpFlag    = enEfFcpFlag;
    stSelectPara.enFileApp      = USIMM_UNLIMIT_APP;

    stFileAllPath.ulDataLen     = ulPathLen;
    stFileAllPath.pusData       = pusFilePath;

    /* ѡ���ļ��Ѿ��ǵ�ǰ�ļ����˳������سɹ� */
    ulResult = USIMM_CardFilePathCMP(stFileAllPath.ulDataLen, stFileAllPath.pusData,
                    gstUSIMMCurFileInfo.usFilePathLen, gstUSIMMCurFileInfo.ausFilePath);

    if (VOS_OK == ulResult)
    {
        if (USIMM_IS_DF_FILE(stFileAllPath.pusData[stFileAllPath.ulDataLen-1])
            || (0 != gstUSIMMCurFileInfo.stEFInfo.usFileLen)
            || (USIMM_NO_NEED_FCP == enEfFcpFlag))
        {
            USIMM_INFO_LOG("USIMM_SelectCdmaFile: Selected file is current file.");

            return USIMM_SW_OK;
        }
    }

    /* ͨ��ȫ·��ѡ���ļ� */
    ulResult = USIMM_SelectFileWithPath(&stSelectPara, &stFileAllPath, &gstUSIMMCurFileInfo, &usCurPathLen);

    if (VOS_NULL == usCurPathLen)
    {
        USIMM_ClearCurFileInfo();
    }
    else
    {
        stFileAllPath.ulDataLen = usCurPathLen;

        /* ����·�� */
        USIMM_UpdateFilePath(&stSelectPara, &stFileAllPath, &gstUSIMMCurFileInfo);
    }

    return ulResult;

}
VOS_UINT32 USIMM_SetCdmaFileHandle(USIMM_MsgBlock *pMsg, USIMM_UPDATEFILE_REQ_STRU *pstNewMsg)
{
    USIMM_SETFILE_REQ_STRU                 *pstSetFileMsg;
    VOS_UINT32                              ulResult;
    USIMM_EFFCP_ST                          stEFFcp;
    USIMM_SETCNF_INFO_STRU                  stCnfInfo;
    VOS_UINT16                              ausFileAllPath[USIMM_MAX_PATH_LEN]  = {MF, 0x0};

    pstSetFileMsg = (USIMM_SETFILE_REQ_STRU*)pMsg;

    /*lint -e534*/
    VOS_MemSet(&stCnfInfo, 0, sizeof(stCnfInfo));
    /*lint +e534*/

    stCnfInfo.ucRecordNum  = pstSetFileMsg->ucRecordNum;
    stCnfInfo.usEFLen      = pstSetFileMsg->usDataLen;
    stCnfInfo.usEfid       = pstSetFileMsg->usFileID;

    if (USIMM_CARD_UIM == gastUSIMMCardAppInfo[USIMM_UICC_CDMA].enCardType)
    {
        ausFileAllPath[1] = DFCDMA;
    }
    else
    {
        ausFileAllPath[1] = ADF;
    }

    ausFileAllPath[2] = pstSetFileMsg->usFileID;

    ulResult = USIMM_SelectCdmaFile(USIMM_NEED_FCP, 3, ausFileAllPath);

    if(USIMM_SW_OK != ulResult)/*�ж�ѡ����*/
    {
        USIMM_WARNING_LOG("USIMM_SetCdmaFileHandle: Select File is Failed");

        USIMM_SetFileCnf(pstNewMsg, ulResult, &stCnfInfo);

        return ulResult;
    }

    /*lint -e534*/
    VOS_MemCpy(&stEFFcp, &(gstUSIMMCurFileInfo.stEFInfo), sizeof(stEFFcp));
    /*lint +e534*/

    ulResult = USIMM_CheckSetFilePara(&stEFFcp, pstSetFileMsg->ucRecordNum, pstSetFileMsg->usDataLen);

    if(USIMM_SW_OK != ulResult)/*�ж�ѡ����*/
    {
        USIMM_WARNING_LOG("USIMM_SetCdmaFileHandle: USIMM_CheckSetFilePara is Failed");

        USIMM_SetFileCnf(pstNewMsg, ulResult, &stCnfInfo);

        return ulResult;
    }

    /* �����ļ����͸����ļ� */
    ulResult = USIMM_UpdateFile(stEFFcp.enFileType, pstSetFileMsg->ucRecordNum, pstSetFileMsg->usDataLen, pstSetFileMsg->aucContent);

    if(USIMM_SW_OK != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_SetCdmaFileHandle: Update File Content is Failed");

        USIMM_SetFileCnf(pstNewMsg, ulResult, &stCnfInfo);

        return ulResult;
    }

    USIMM_SetFileCnf(pstNewMsg, ulResult, &stCnfInfo);

    return VOS_OK;
}
VOS_UINT32 USIMM_GetCdmaFileFromCard(USIMM_GET_COMM_FILE_STRU *pstFileInfo, USIMM_GETCNF_INFO_STRU *pstCnfInfo)
{
    VOS_UINT32                          ulResult;

    pstCnfInfo->pucEf = VOS_NULL_PTR;

    ulResult = USIMM_SelectCdmaFile(USIMM_NEED_FCP, pstFileInfo->ulPathLen, pstFileInfo->pusFilePath);

    if(VOS_OK != ulResult) /*�ļ�ѡ��ʧ��*/
    {
        USIMM_ERROR_LOG("USIMM_GetCdmaFileFromCard: Select File is Failed");

        return ulResult;
    }

    /* ��ȡҪ�����ļ�������stCnfInfo�ṹ����usEfLen, usDataLen, ucRecordNum, ucTotalNum��ֵ */
    ulResult = USIMM_GetReadFilePara(pstFileInfo->ucRecordNum, &gstUSIMMCurFileInfo.stEFInfo, pstCnfInfo);

    /* ��ȡ���ļ�����ʧ�� */
    if(VOS_OK != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_GetCdmaFileFromCard: Get file para Failed");

        return ulResult;
    }

    pstCnfInfo->pucEf = (VOS_UINT8 *)VOS_MemAlloc(WUEPS_PID_USIM, DYNAMIC_MEM_PT, pstCnfInfo->usDataLen);

    if(VOS_NULL_PTR == pstCnfInfo->pucEf)/*��鷵��ֵ*/
    {
        USIMM_ERROR_LOG("USIMM_GetCdmaFileFromCard: VOS_MemAlloc is Error");

        return USIMM_SW_ERR;
    }

    ulResult = USIMM_ReadFile(&gstUSIMMCurFileInfo.stEFInfo, pstCnfInfo->ucRecordNum, pstCnfInfo->usDataLen, pstCnfInfo->pucEf);

    if(VOS_OK != ulResult)
    {
        /*lint -e534*/
        VOS_MemFree(WUEPS_PID_USIM, pstCnfInfo->pucEf);
        /*lint +e534*/

        pstCnfInfo->pucEf = VOS_NULL_PTR;
    }

    return ulResult;
}


VOS_UINT32 USIMM_GetCdmaFileHandle(USIMM_MsgBlock *pstMsg, USIMM_CMDHEADER_REQ_STRU *pstReqMsg)
{
    USIMM_GET_COMM_FILE_STRU            stFileInfo;
    USIMM_GETCNF_INFO_STRU              stCnfInfo;
    VOS_UINT16                          ausFileAllPath[USIMM_MAX_PATH_LEN] = {MF, 0x0};
    USIMM_GETFILE_REQ_STRU             *pstOldMsg;
    USIMM_READFILE_REQ_STRU            *pstNewMsg;
    VOS_UINT32                          ulResult;

    pstOldMsg = (USIMM_GETFILE_REQ_STRU*)pstMsg;
    pstNewMsg = (USIMM_READFILE_REQ_STRU *)pstReqMsg;

    /*lint -e534*/
    VOS_MemSet(&stCnfInfo, 0, sizeof(stCnfInfo));
    /*lint +e534*/

    stCnfInfo.ucRecordNum      = pstOldMsg->ucRecordNum;
    stCnfInfo.usEfId           = pstOldMsg->usFileID;

    if (USIMM_CARD_CSIM == gastUSIMMCardAppInfo[USIMM_UICC_CDMA].enCardType)
    {
        ausFileAllPath[1]      = ADF;
    }
    else
    {
        ausFileAllPath[1]      = DFCDMA;
    }

    ausFileAllPath[2]      = pstOldMsg->usFileID;

    stFileInfo.ulPathLen   = 3;                             /*MF+DF+EF*/
    stFileInfo.pusFilePath = ausFileAllPath;
    stFileInfo.ucRecordNum = pstOldMsg->ucRecordNum;

    ulResult = USIMM_GetCdmaFileFromCard(&stFileInfo, &stCnfInfo);

    USIMM_GetFileCnf(pstNewMsg, ulResult, &stCnfInfo);

    if (VOS_NULL_PTR != stCnfInfo.pucEf)
    {
        /*lint -e534*/
        VOS_MemFree(WUEPS_PID_USIM, stCnfInfo.pucEf);
        /*lint +e534*/
    }

    return VOS_OK;
}
VOS_UINT32 USIMM_BSChallengeHandle(USIMM_CMDHEADER_REQ_STRU *pstMsg)
{
    VOS_UINT32                          ulResult;
    USIMM_BSCHALLENGE_REQ_STRU         *pstReqMsg;
    VOS_UINT16                          ausPath[] = {MF, DFCDMA};

    if (VOS_OK != USIMM_CdmaParaCheckSimple())/*�жϽ��*/
    {
        USIMM_ERROR_LOG("USIMM_BSChallengeHandle: USIMM_CdmaParaCheckSimple Error");

        USIMM_BSChallengeCnf(pstMsg, VOS_ERR, VOS_ERR, VOS_NULL, VOS_NULL_PTR);

        return VOS_ERR;
    }

    if (USIMM_CARD_UIM == gastUSIMMCardAppInfo[USIMM_UICC_CDMA].enCardType)
    {
        ausPath[1] = DFCDMA;

        ulResult = USIMM_SelectCdmaFile(USIMM_NEED_FCP, ARRAYSIZE(ausPath), ausPath);
    }
    else
    {
        ausPath[1] = ADF;

        ulResult = USIMM_SelectCdmaFile(USIMM_NEED_FCP, ARRAYSIZE(ausPath), ausPath);
    }

    if (VOS_OK != ulResult)/*�жϽ��*/
    {
        USIMM_ERROR_LOG("USIMM_BSChallengeHandle: Select ADFCSIM or DFCDMA Error");

        USIMM_BSChallengeCnf(pstMsg, VOS_ERR, ulResult, VOS_NULL, VOS_NULL_PTR);

        return VOS_ERR;
    }

    pstReqMsg = (USIMM_BSCHALLENGE_REQ_STRU *)pstMsg;

    ulResult = USIMM_BSChallengeAPDU(pstReqMsg->aucData, &gstUSIMMAPDU);

    if (VOS_OK != ulResult)/*��鷢�ͽ��*/
    {
        USIMM_ERROR_LOG("USIMM_BSChallengeHandle: Send APDU Command is Failed");

        USIMM_BSChallengeCnf(pstMsg, VOS_ERR, USIMM_SW_SENDCMD_ERROR, VOS_NULL, VOS_NULL_PTR);

        return VOS_ERR;
    }

    ulResult = USIMM_CheckSW(&gstUSIMMAPDU);

    USIMM_BSChallengeCnf(pstMsg, ulResult, ulResult, gstUSIMMAPDU.ulRecDataLen, gstUSIMMAPDU.aucRecvBuf);

    if (USIMM_SW_OK != ulResult)
    {
        USIMM_WARNING_LOG("USIMM_BSChallengeHandle: The Command Result is Error");

        ulResult = VOS_ERR;
    }

    return ulResult;
}
VOS_UINT32 USIMM_ManageSsdHandle(USIMM_CMDHEADER_REQ_STRU *pMsg)
{
    VOS_UINT32                          ulResult;
    USIMM_MANAGESSD_REQ_STRU           *pstMsg;
    VOS_UINT8                           ucDataLen;
    VOS_UINT8                           aucData[USIMM_CDMA_RANDSSD_LEN + USIMM_ESN_MEID_LEN + 1];
    VOS_UINT16                          ausPath[] = {MF, DFCDMA};

    pstMsg = (USIMM_MANAGESSD_REQ_STRU *)pMsg;

    if (pstMsg->stSsdData.enCmdType >= USIMM_MANAGESSD_BUTT)
    {
        USIMM_ERROR_LOG("USIMM_ManageSsdHandle: Input Para is wrong");

        USIMM_SingleCmdCnf(pMsg->ulSenderPid,
                           USIMM_MANAGESSD_CNF,
                           pMsg->ulSendPara,
                           VOS_ERR,
                           pMsg->enAppType);

        return VOS_ERR;
    }

    if (VOS_OK != USIMM_CdmaParaCheckSimple())/*�жϽ��*/
    {
        USIMM_ERROR_LOG("USIMM_ManageSsdHandle: USIMM_CdmaParaCheckSimple Error");

        USIMM_SingleCmdCnf(pMsg->ulSenderPid,
                           USIMM_MANAGESSD_CNF,
                           pMsg->ulSendPara,
                           VOS_ERR,
                           pMsg->enAppType);

        return VOS_ERR;
    }

    if (USIMM_CARD_UIM == gastUSIMMCardAppInfo[USIMM_UICC_CDMA].enCardType)
    {
        ausPath[1] = DFCDMA;

        ulResult = USIMM_SelectCdmaFile(USIMM_NEED_FCP, ARRAYSIZE(ausPath), ausPath);
    }
    else
    {
        ausPath[1] = ADF;

        ulResult = USIMM_SelectCdmaFile(USIMM_NEED_FCP, ARRAYSIZE(ausPath), ausPath);
    }

    if (VOS_OK != ulResult)/*�жϽ��*/
    {
        USIMM_ERROR_LOG("USIMM_ManageSsdHandle: Select ADFCSIM or DFCDMA Error");

        USIMM_SingleCmdCnf(pMsg->ulSenderPid,
                           USIMM_MANAGESSD_CNF,
                           pMsg->ulSendPara,
                           ulResult,
                           pMsg->enAppType);

        return VOS_ERR;
    }

    if (USIMM_MANAGESSD_UPDATE == pstMsg->stSsdData.enCmdType)
    {
        /*lint -e534*/
        VOS_MemCpy(aucData,
                    pstMsg->stSsdData.uSSDData.stUpdateSSD.aucRandSSD,
                    USIMM_CDMA_RANDSSD_LEN);
        /*lint +e534*/

        aucData[USIMM_CDMA_RANDSSD_LEN] = pstMsg->stSsdData.uSSDData.stUpdateSSD.ucProcessCtrl;

        /*lint -e534*/
        VOS_MemCpy(aucData + USIMM_CDMA_RANDSSD_LEN + 1,
                   pstMsg->stSsdData.uSSDData.stUpdateSSD.aucESN,
                   USIMM_ESN_MEID_LEN);
        /*lint +e534*/

        ucDataLen = USIMM_CDMA_RANDSSD_LEN + USIMM_ESN_MEID_LEN + 1;
    }
    else
    {
        /*lint -e534*/
        VOS_MemCpy(aucData,
                    pstMsg->stSsdData.uSSDData.stConfirmSSD.aucAuthBS,
                    USIMM_CDMA_AUTHBS_LEN);
        /*lint +e534*/

        ucDataLen = USIMM_CDMA_AUTHBS_LEN;
    }

    if (USIMM_CARD_UIM == gastUSIMMCardAppInfo[USIMM_UICC_CDMA].enCardType)
    {
        if (USIMM_MANAGESSD_UPDATE == pstMsg->stSsdData.enCmdType)
        {
            ulResult = USIMM_UpdateSsdAPDU(ucDataLen, aucData, &gstUSIMMAPDU);
        }
        else
        {
            ulResult = USIMM_ConfirmSsdAPDU(ucDataLen, aucData, &gstUSIMMAPDU);
        }
    }
    else
    {
        ulResult = USIMM_ManageSsdAPDU((VOS_UINT8)pstMsg->stSsdData.enCmdType, ucDataLen, aucData, &gstUSIMMAPDU);
    }

    if (VOS_OK != ulResult)/*��鷢�ͽ��*/
    {
        USIMM_ERROR_LOG("USIMM_ManageSsdHandle: Send APDU Command is Failed");

        USIMM_SingleCmdCnf(pMsg->ulSenderPid,
                           USIMM_MANAGESSD_CNF,
                           pMsg->ulSendPara,
                           USIMM_SW_SENDCMD_ERROR,
                           pMsg->enAppType);

        return VOS_ERR;
    }

    ulResult = USIMM_CheckSW(&gstUSIMMAPDU);

    USIMM_SingleCmdCnf(pMsg->ulSenderPid,
                       USIMM_MANAGESSD_CNF,
                       pMsg->ulSendPara,
                       ulResult,
                       pMsg->enAppType);

    if (USIMM_SW_OK != ulResult)
    {
        USIMM_WARNING_LOG("USIMM_ManageSsdHandle: The Command Result is Error");

        ulResult = VOS_ERR;
    }

    return ulResult;
}
VOS_UINT32 USIMM_GenerateKeyVpmHandle(USIMM_CMDHEADER_REQ_STRU *pMsg)
{
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulVpmLen;
    USIMM_GENERATE_KEYVPM_REQ_STRU     *pstMsg;
    VOS_UINT8                           aucData[2];
    VOS_UINT16                          ausPath[] = {MF, DFCDMA};

    pstMsg = (USIMM_GENERATE_KEYVPM_REQ_STRU *)pMsg;

    if (VOS_OK != USIMM_CdmaParaCheckSimple())/*�жϽ��*/
    {
        USIMM_ERROR_LOG("USIMM_GenerateKeyVpmHandle: USIMM_CdmaParaCheckSimple Error");

        USIMM_GenerateKeyVpmCnf(pstMsg, VOS_ERR, VOS_ERR, VOS_NULL, VOS_NULL_PTR, VOS_NULL_PTR);

        return VOS_ERR;
    }

    if (USIMM_CARD_UIM == gastUSIMMCardAppInfo[USIMM_UICC_CDMA].enCardType)
    {
        ausPath[1] = DFCDMA;

        ulResult = USIMM_SelectCdmaFile(USIMM_NEED_FCP, ARRAYSIZE(ausPath), ausPath);
    }
    else
    {
        ausPath[1] = ADF;

        ulResult = USIMM_SelectCdmaFile(USIMM_NEED_FCP, ARRAYSIZE(ausPath), ausPath);
    }

    if (VOS_OK != ulResult)/*�жϽ��*/
    {
        USIMM_ERROR_LOG("USIMM_GenerateKeyVpmHandle: Select ADFCSIM or DFCDMA Error");

        USIMM_GenerateKeyVpmCnf(pstMsg, VOS_ERR, ulResult, VOS_NULL, VOS_NULL_PTR, VOS_NULL_PTR);

        return VOS_ERR;
    }

    aucData[0] = pstMsg->ucFirstOctet;
    aucData[1] = pstMsg->ucLastOctet;

    ulResult = USIMM_GenerateKeyVpmAPDU(sizeof(aucData), aucData, &gstUSIMMAPDU);

    if (VOS_OK != ulResult)/*��鷢�ͽ��*/
    {
        USIMM_ERROR_LOG("USIMM_GenerateKeyVpmHandle: Send APDU Command is Failed");

        USIMM_GenerateKeyVpmCnf(pstMsg, VOS_ERR, USIMM_SW_SENDCMD_ERROR, VOS_NULL, VOS_NULL_PTR, VOS_NULL_PTR);

        return VOS_ERR;
    }

    ulResult = USIMM_CheckSW(&gstUSIMMAPDU);

    ulVpmLen = (gstUSIMMAPDU.ulRecDataLen > 8)?(gstUSIMMAPDU.ulRecDataLen - 8):VOS_NULL;

    USIMM_GenerateKeyVpmCnf(pstMsg, ulResult, ulResult, ulVpmLen, gstUSIMMAPDU.aucRecvBuf + 8, gstUSIMMAPDU.aucRecvBuf);

    if (USIMM_SW_OK != ulResult)
    {
        USIMM_WARNING_LOG("USIMM_GenerateKeyVpmHandle: The Command Result is Error");

        ulResult = VOS_ERR;
    }

    return ulResult;
}
VOS_UINT32 USIMM_CdmaAuthHandle(USIMM_AUTH_REQ_STRU *pstMsg)
{
    USIMM_CDMA_AUTH_INFO_STRU           stCnfInfo;
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulOffset = 1;
    VOS_UINT16                          ausPath[] = {MF, DFCDMA};
    VOS_UINT8                           ucP1;
    VOS_UINT8                           ucP2;

    /*lint -e534*/
    VOS_MemSet(&stCnfInfo, 0, sizeof(stCnfInfo));
    /*lint +e534*/

    if ((USIMM_CARD_UIM != gastUSIMMCardAppInfo[USIMM_UICC_CDMA].enCardType)
        && (USIMM_CARD_CSIM != gastUSIMMCardAppInfo[USIMM_UICC_CDMA].enCardType))
    {
        USIMM_ERROR_LOG("USIMM_CdmaAuthHandle: incorrect card type.");

        stCnfInfo.enResult = USIMM_AUTH_CDMA_OTHER_FAILURE;

        USIMM_CdmaAuthCnf(pstMsg, &stCnfInfo);

        return VOS_ERR;
    }

    /* ������Ⲣȷ����Ȩ���ݲ��� */
    if (USIMM_CARD_UIM == gastUSIMMCardAppInfo[USIMM_UICC_CDMA].enCardType)
    {
        ausPath[1] = DFCDMA;

        ulResult = USIMM_SelectCdmaFile(USIMM_NEED_FCP, ARRAYSIZE(ausPath), ausPath);

        if (USIMM_3G_AUTH == pstMsg->enAuthType)
        {
            ucP1 = 0x01;
            ucP2 = 0x00;
        }
        else
        {
            ucP1 = 0x00;
            ucP2 = 0x00;
        }
    }
    else
    {
        ausPath[1] = ADF;

        ulResult = USIMM_SelectCdmaFile(USIMM_NEED_FCP, ARRAYSIZE(ausPath), ausPath);

        if (USIMM_3G_AUTH == pstMsg->enAuthType)
        {
            ucP1 = 0x00;
            ucP2 = 0x81;
        }
        else
        {
            ucP1 = 0x00;
            ucP2 = 0x80;
        }
    }

    if (VOS_OK != ulResult)/*�жϽ��*/
    {
        USIMM_ERROR_LOG("USIMM_CdmaAuthHandle: Select ADFCSIM or DFCDMA Error");

        stCnfInfo.enResult = USIMM_AUTH_CDMA_OTHER_FAILURE;

        USIMM_CdmaAuthCnf(pstMsg, &stCnfInfo);

        return VOS_ERR;
    }

    ulResult = USIMM_Authentication_APDU(ucP1, ucP2, pstMsg->aucData, pstMsg->ulDataLen);

    if(VOS_OK != ulResult)/*�жϼ�Ȩ���ͽ��*/
    {
        USIMM_ERROR_LOG("USIMM_CdmaAuthHandle: Send USIM Authentication APDU Error");

        stCnfInfo.enResult = USIMM_AUTH_CDMA_OTHER_FAILURE;

        USIMM_CdmaAuthCnf(pstMsg, &stCnfInfo);

        return VOS_ERR;
    }

    ulResult = USIMM_CheckSW(&gstUSIMMAPDU);

    if (USIMM_SW_CDMA_AUTN_ERROR == ulResult)
    {
        USIMM_WARNING_LOG("USIMM_CdmaAuthHandle: SIM Check SW Error");

        stCnfInfo.enResult = USIMM_AUTH_MAC_FAILURE;

        USIMM_CdmaAuthCnf(pstMsg, &stCnfInfo);

        return VOS_ERR;
    }

    if (USIMM_SW_OK != ulResult)
    {
        stCnfInfo.enResult = USIMM_AUTH_CDMA_OTHER_FAILURE;

        USIMM_CdmaAuthCnf(pstMsg, &stCnfInfo);

        return VOS_ERR;
    }

    if (USIMM_RUNCAVE_AUTH == pstMsg->enAuthType)
    {
        stCnfInfo.pucAuthr = gstUSIMMAPDU.aucRecvBuf;

        USIMM_INFO_LOG("USIMM_CdmaAuthHandle: Run Cave Authentication right");

        stCnfInfo.enResult = USIMM_AUTH_CDMA_SUCCESS;

        USIMM_CdmaAuthCnf(pstMsg, &stCnfInfo);

        return VOS_OK;
    }

    /* 3G ��Ȩ�ɹ� */
    if (USIMM_AUTH_SUCCESS_TAG == gstUSIMMAPDU.aucRecvBuf[0])
    {
        stCnfInfo.enResult  = USIMM_AUTH_CDMA_SUCCESS;

        stCnfInfo.pucCK     = gstUSIMMAPDU.aucRecvBuf + ulOffset; /* ָ��CK */
        ulOffset            += 16;/* ָ��IK */

        stCnfInfo.pucIK     = gstUSIMMAPDU.aucRecvBuf + ulOffset;
        ulOffset            += 16;/* ָ��Res */

        stCnfInfo.pucAuthRes= gstUSIMMAPDU.aucRecvBuf + ulOffset;

        USIMM_INFO_LOG("USIMM_CdmaAuthHandle: USIM 3G Authenctication AKA Right");
    }
    else if (USIMM_AUTH_SYNC_FAIL_TAG == gstUSIMMAPDU.aucRecvBuf[0]) /* 3G��ͬ�� */
    {
        stCnfInfo.enResult  = USIMM_AUTH_SYNC_FAILURE;

        stCnfInfo.pucAuts   = gstUSIMMAPDU.aucRecvBuf + ulOffset;

        USIMM_WARNING_LOG("USIMM_CdmaAuthHandle: USIM 3G Authentication AKA Synchronization Failure");
    }
    else                                                                /*�������ݴ���*/
    {
        USIMM_ERROR_LOG("USIMM_CdmaAuthHandle: USIM Authentication Response Data Error");

        stCnfInfo.enResult = USIMM_AUTH_CDMA_OTHER_FAILURE;
    }

    USIMM_CdmaAuthCnf(pstMsg, &stCnfInfo);

    return VOS_OK ;
}
VOS_UINT32 USIMM_IsUIMServiceAvailable(UICC_SERVICES_TYPE_ENUM_UINT32 enService)
{
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucBitNo;

    if ((USIMM_CARD_UIM != gastUSIMMCardAppInfo[USIMM_UICC_CDMA].enCardType)
        || (USIMM_CARD_SERVIC_AVAILABLE != gastUSIMMCardAppInfo[USIMM_UICC_CDMA].enCardService))
    {
        USIMM_WARNING_LOG("USIMM_IsUIMServiceAvailable: The Card Type is Wrong");

        return PS_USIM_SERVICE_NOT_AVAILIABLE;
    }

    ucBitNo = (VOS_UINT8)((enService - ISIM_SVR_BUTT) + 1);

    /* ��ȡ�����Bit��Ϣ */
    ulResult = USIMM_GetBitFromBuf(g_aucCUIMCstInfo, ucBitNo, sizeof(g_aucCUIMCstInfo));

    /* SIM�����ж�ACTIVEλ */
    if (PS_USIM_SERVICE_AVAILIABLE == ulResult)
    {
        ulResult = USIMM_GetBitFromBuf(g_aucCUIMCstInfo, (ucBitNo+1), sizeof(g_aucCUIMCstInfo));
    }

    if(USIMM_BITNOFOUNE == ulResult)
    {
        USIMM_WARNING_LOG("USIMM_IsUIMServiceAvailable: The Service is Out of File");

        return PS_USIM_SERVICE_NOT_AVAILIABLE;
    }

    return ulResult;
}


VOS_UINT32 USIMM_IsCSIMServiceAvailable(UICC_SERVICES_TYPE_ENUM_UINT32 enService)
{
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucBitNo;

    if ((USIMM_CARD_CSIM != gastUSIMMCardAppInfo[USIMM_UICC_CDMA].enCardType)
        || (USIMM_CARD_SERVIC_AVAILABLE != gastUSIMMCardAppInfo[USIMM_UICC_CDMA].enCardService))
    {
        USIMM_WARNING_LOG("USIMM_IsCSIMServiceAvailable: The Card Type is Wrong");

        return PS_USIM_SERVICE_NOT_AVAILIABLE;
    }

    ucBitNo = (VOS_UINT8)((enService - UIM_SVR_BUTT) + 1);

    /* ��ȡ�����Bit��Ϣ */
    ulResult = USIMM_GetBitFromBuf(g_aucCUIMCstInfo, ucBitNo, sizeof(g_aucCUIMCstInfo));

    if(USIMM_BITNOFOUNE == ulResult)
    {
        USIMM_WARNING_LOG("USIMM_IsCSIMServiceAvailable: The Service is Out of File");

        return PS_USIM_SERVICE_NOT_AVAILIABLE;
    }

    return ulResult;

}

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

