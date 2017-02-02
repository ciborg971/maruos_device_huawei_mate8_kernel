
/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "ScInterface.h"
#include "ScComm.h"
#include "ScCtx.h"
#include "ScFactory.h"
#include "TafDrvAgent.h"
#include "omnvinterface.h"
#include "NVIM_Interface.h"

#ifdef __cplusplus
  #if __cplusplus
  extern "C"{
  #endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_SC_FACTORY_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ��������
*****************************************************************************/


SC_ERROR_CODE_ENUM_UINT32 SC_FAC_RsaDecrypt(
    VOS_UINT8                          *pucCipherData,
    VOS_UINT32                          ulCipherLen,
    VOS_UINT8                          *pucRawData,
    VOS_UINT32                         *pulLen
)
{
    VOS_UINT32                          ulResult;

    /* �ж��Ƿ�ͨ�����߼�Ȩ */
    if (SC_AUTH_STATUS_UNDO == SC_CTX_GetFacAuthStatus())
    {
        SC_ERROR_LOG("SC_FAC_RsaDecrypt: SC_CTX_GetFacAuthStatus is not done.");

        return SC_ERROR_CODE_IDENTIFY_FAIL;
    }

    ulResult = SC_COMM_RsaDecrypt(pucCipherData, ulCipherLen, pucRawData, pulLen);

    SC_INFO1_LOG("SC_FAC_RsaDecrypt: The Result is:", ulResult);

    return ulResult;

}
SC_ERROR_CODE_ENUM_UINT32 SC_FAC_RsaEncrypt(
    VOS_UINT8                          *pucRawData,
    VOS_UINT32                          ulLen,
    VOS_UINT8                          *pucCipherData,
    VOS_UINT32                         *pulCipherLen
)
{
    VOS_UINT32                          ulResult;

    /* �ж��Ƿ�ͨ�����߼�Ȩ */
    if (SC_AUTH_STATUS_UNDO == SC_CTX_GetFacAuthStatus())
    {
        SC_ERROR_LOG("SC_FAC_RsaEncrypt: SC_CTX_GetFacAuthStatus is not done.");

        return SC_ERROR_CODE_IDENTIFY_FAIL;
    }

    ulResult = SC_COMM_RsaEncrypt(pucRawData, ulLen, pucCipherData, pulCipherLen);

    SC_INFO1_LOG("SC_FAC_RsaEncrypt: The Result is", ulResult);

    return ulResult;
}
SC_ERROR_CODE_ENUM_UINT32 SC_FAC_SetFacAuthPubKey(SC_SET_FAC_AUTH_PUB_KEY_STRU *pstSetFacAuthPubKey)
{
    VOS_UINT32                          ulResult;
    VOS_INT                             lResult;
    VOS_UINT8                           aucSsk[SC_KEY_LEN];
    VOS_UINT8                           aucHash[SC_HASH_LEN];
    VOS_INT                             lHashLen;
    VOS_INT                             lCipherLen;
    VOS_UINT8                           aucCipherData[SC_SIGNATURE_LEN];
    VOS_UINT32                          ulKeyLen;

    /* �Ƶ�SSK��Կ */
    ulKeyLen = SC_KEY_LEN;

    ulResult = SC_COMM_GenerateKey(SC_SSK_STRING, SC_SSK_STRLEN, aucSsk, ulKeyLen);

    if (SC_ERROR_CODE_NO_ERROR != ulResult)
    {
        SC_ERROR1_LOG("SC_FAC_SetFacAuthPubKey: SC_COMM_GenerateKey SSK is Failed.", ulResult);

        return ulResult;
    }

    /* ��MD5�㷨������AK��ժҪ */
    lHashLen = SC_HASH_LEN;

    lResult = mdrv_crypto_hash((VOS_CHAR*)pstSetFacAuthPubKey->aucAuthPubKey,
                          SC_AUTH_PUB_KEY_LEN,
                          CRYPTO_ALGORITHM_SHA256,
                          (VOS_CHAR*)aucHash,
                          &lHashLen);

    /* ���DRV���㷵�صĽ������OK����DRV���������HASH����16�ֽ� */
    if ((VOS_OK != lResult) || (SC_HASH_LEN != lHashLen))
    {
        SC_ERROR2_LOG("SC_FAC_SetFacAuthPubKey: mdrv_crypto_hash is Failed.", lResult, lHashLen);
        /* ����HASH����ʧ�� */
        return SC_ERROR_CODE_GENERATE_HASH_FAIL;
    }

    /* ��AES_ECB�㷨�������ժҪ */
    lCipherLen = SC_SIGNATURE_LEN;

    lResult = mdrv_crypto_enc((VOS_CHAR*)aucHash,
                             lHashLen,
                             CRYPTO_ENCRYPT_ALGORITHM_AES_ECB,
                             (VOS_CHAR*)aucSsk,
                             (VOS_INT)ulKeyLen,
                             (VOS_CHAR*)aucCipherData,
                             &lCipherLen);

    /* ���DRV���㷵�صĽ������OK���������ļ���ժҪ����16�ֽ� */
    if ((VOS_OK != lResult) || (SC_SIGNATURE_LEN != lCipherLen))
    {
        SC_ERROR2_LOG("SC_FAC_SetFacAuthPubKey: mdrv_crypto_enc is Failed.", lResult, lCipherLen);
        /* ����AES_ECB����ʧ�� */
        return SC_ERROR_CODE_AES_ECB_ENCRYPT_FAIL;
    }

    /* ��AT��������ļ���ժҪ�����õ���ժҪ���жԱ� */
    if (VOS_OK != VOS_MemCmp(aucCipherData,
                             pstSetFacAuthPubKey->aucSignature,
                             SC_SIGNATURE_LEN))
    {
        SC_ERROR_LOG("SC_FAC_SetFacAuthPubKey: signature compare is Failed.");
        /* ����ժҪǩ����֤ʧ�� */
        return SC_ERROR_CODE_VERIFY_PUB_KEY_SIGNATURE_FAIL;
    }

    /* ��AK����д��AKFile.bin�ļ��� */
    ulResult = SC_COMM_WriteSecretFile(SC_SECRET_FILE_TYPE_AK,
                                       pstSetFacAuthPubKey->aucAuthPubKey,
                                       SC_AUTH_PUB_KEY_LEN);

    SC_INFO1_LOG("SC_FAC_SetFacAuthPubKey: The Result is:", ulResult);

    return ulResult;
}



SC_ERROR_CODE_ENUM_UINT32 SC_FAC_WriteHUK(
    VOS_UINT8                          *pucHuk,
    VOS_UINT32                          ulLen
)
{
    VOS_INT                             lResult;

    /* ������� */
    if ((SC_HUK_LEN != ulLen) || (VOS_NULL_PTR == pucHuk))
    {
        SC_ERROR_LOG("SC_FAC_WriteHUK: Para is wrong.");

        return SC_ERROR_CODE_WRITE_HUK_FAIL;
    }

    /* ͨ������ӿ�д��HUK */
    lResult = mdrv_efuse_write_huk((VOS_CHAR*)pucHuk, (VOS_UINT)ulLen);

    if (VOS_OK != lResult)
    {
        SC_ERROR1_LOG("SC_FAC_WriteHUK: mdrv_efuse_write_huk is failed.", lResult);
        /* ����HUKд��ʧ�� */
        return SC_ERROR_CODE_WRITE_HUK_FAIL;
    }

    /* ���ز����ɹ� */
    return SC_ERROR_CODE_NO_ERROR;
}


SC_ERROR_CODE_ENUM_UINT32 SC_FAC_WriteIMEI(
    MODEM_ID_ENUM_UINT16                enModemID,
    VOS_UINT8                          *pucCipherData,
    VOS_UINT32                          ulCipherLen
)
{
    VOS_UINT32                          ulResult;

    /* �жϼ�Ȩ�Ƿ�ͨ�� */
    if (SC_AUTH_STATUS_DONE != SC_CTX_GetFacAuthStatus())
    {
        SC_ERROR_LOG("SC_FAC_WriteIMEI: SC_CTX_GetFacAuthStatus is not done.");

        return SC_ERROR_CODE_IDENTIFY_FAIL;
    }

    /* ������� */
    if ((SC_RSA_ENCRYPT_LEN != ulCipherLen) || (VOS_NULL_PTR == pucCipherData))
    {
        SC_ERROR_LOG("SC_FAC_WriteIMEI: Para is wrong.");

        return SC_ERROR_CODE_PARA_FAIL;
    }

    /* ����Flash ������ǩ�� */
    SC_INFO1_LOG("#info:SC_FAC_WriteIMEI: modem id is: .", enModemID);
    if (MODEM_ID_0 == enModemID)
    {
        ulResult = SC_COMM_WriteSecretFile(SC_SECRET_FILE_TYPE_IMEI_I0,
                                           pucCipherData,
                                           ulCipherLen);
    }
#if  ( FEATURE_MULTI_MODEM == FEATURE_ON )
    else if (MODEM_ID_1 == enModemID)
    {
        ulResult = SC_COMM_WriteSecretFile(SC_SECRET_FILE_TYPE_IMEI_I1,
                                           pucCipherData,
                                           ulCipherLen);
    }
#if (3 == MULTI_MODEM_NUMBER)
    else if (MODEM_ID_2 == enModemID)
    {
        ulResult = SC_COMM_WriteSecretFile(SC_SECRET_FILE_TYPE_IMEI_I2,
                                           pucCipherData,
                                           ulCipherLen);
    }
#endif
#endif
    else
    {
        SC_ERROR_LOG("SC_FAC_WriteIMEI: modem id  error.");
        return SC_ERROR_CODE_MODEM_ID_FAIL;
    }

    if (SC_ERROR_CODE_NO_ERROR != ulResult)
    {
        SC_ERROR1_LOG("SC_FAC_WriteIMEI: write IMEI is failed.", ulResult);

        /* ����IMEIд��ʧ�� */
        return SC_ERROR_CODE_WRITE_FILE_IMEI_FAIL;
    }

    /* ���ز����ɹ� */
    return SC_ERROR_CODE_NO_ERROR;
}
SC_ERROR_CODE_ENUM_UINT32 SC_FAC_StartIdentify(SC_IDENTIFY_START_RESPONSE_STRU *pstIdentifyStartRsp)
{
    VOS_UINT32                          ulResult;
    VOS_INT                             lResult;
    VOS_INT                             lIdentifyStartRspLen;
    SC_AK_FILE_STRU                    *pstAKFile;

    /* �����Ȩ״̬ȫ�ֱ��� */
    SC_CTX_SetFacAuthStatus(SC_AUTH_STATUS_UNDO);

    /* ���÷�����߼�Ȩ��־ΪVOS_FALSE */
    SC_CTX_SetIdentifyStartFlg(VOS_FALSE);

    /* ����һ��32λ������������浽ȫ�ֱ��� */
    if (VOS_OK != mdrv_crypto_gen_rand((VOS_CHAR*)SC_CTX_GetFacRandDataAddr(),
                               SC_RAND_DATA_LEN))
    {
        SC_ERROR_LOG("SC_FAC_StartIdentify: mdrv_crypto_gen_rand is failed.");

        return SC_ERROR_CODE_GET_RAND_NUMBER_FAIL;
    }

    pstAKFile = (SC_AK_FILE_STRU*)VOS_MemAlloc(CCPU_PID_PAM_OM,
                                               DYNAMIC_MEM_PT,
                                               sizeof(SC_AK_FILE_STRU));

    if (VOS_NULL_PTR == pstAKFile)
    {
        SC_ERROR_LOG("SC_FAC_StartIdentify: VOS_MemAlloc is failed.");
        /* �����ڴ�����ʧ�� */
        return SC_ERROR_CODE_ALLOC_MEM_FAIL;
    }

    /* ��ȡAK-FILE������ǩ��У�� */
    ulResult = SC_COMM_ReadSCFileAndCmpSign(SC_SECRET_FILE_TYPE_AK,
                                            pstAKFile->aucAuthPubKey,
                                            sizeof(SC_AK_FILE_STRU));

    if (SC_ERROR_CODE_NO_ERROR != ulResult)
    {
        /*lint -e534*/
        VOS_MemFree(CCPU_PID_PAM_OM, pstAKFile);
        /*lint +e534*/

        SC_ERROR1_LOG("SC_FAC_StartIdentify: SC_COMM_ReadSCFileAndCmpSign is failed.", ulResult);

        return ulResult;
    }

    /* �����������RSA���� */
    lIdentifyStartRspLen = SC_RSA_ENCRYPT_LEN;

    lResult = mdrv_crypto_enc_rsa((VOS_CHAR*)SC_CTX_GetFacRandDataAddr(),
                                SC_RAND_DATA_LEN,
                                (VOS_CHAR*)pstAKFile->aucAuthPubKey,
                                SC_AUTH_PUB_KEY_LEN,
                                (VOS_CHAR*)pstIdentifyStartRsp->aucIdentifyStartRsp,
                                &lIdentifyStartRspLen);

    if ((VOS_OK != lResult) || (SC_RSA_ENCRYPT_LEN != lIdentifyStartRspLen))
    {
        /*lint -e534*/
        VOS_MemFree(CCPU_PID_PAM_OM, pstAKFile);
        /*lint +e534*/

        SC_ERROR2_LOG("SC_FAC_StartIdentify: mdrv_crypto_enc_rsa is failed.", lResult, lIdentifyStartRspLen);

        return SC_ERROR_CODE_RSA_ENCRYPT_FAIL;
    }

    /*lint -e534*/
    VOS_MemFree(CCPU_PID_PAM_OM, pstAKFile);
    /*lint +e534*/

    /* ���÷�����߼�Ȩ��־ΪVOS_TRUE */
    SC_CTX_SetIdentifyStartFlg(VOS_TRUE);

    return SC_ERROR_CODE_NO_ERROR;
}
SC_ERROR_CODE_ENUM_UINT32 SC_FAC_EndIdentify(SC_IDENTIFY_END_REQUEST_STRU *pstIdentifyEndReq)
{
    VOS_UINT32                          ulResult;
    VOS_INT                             lResult;
    VOS_UINT8                           aucRandData[SC_RAND_DATA_LEN];
    VOS_UINT8                           aucOldRandData[SC_RAND_DATA_LEN];
    VOS_INT                             lRandDataLen;
    SC_AK_FILE_STRU                    *pstAKFile;

    if ( VOS_TRUE != SC_CTX_GetIdentifyStartFlg())
    {
        SC_ERROR_LOG("SC_FAC_EndIdentify: Identify hasn't start!");
        return SC_ERROR_CODE_IDENTIFY_FAIL;
    }

    /*lint -e534*/
    VOS_MemCpy(aucOldRandData, SC_CTX_GetFacRandDataAddr(), SC_RAND_DATA_LEN);

    VOS_MemSet(SC_CTX_GetFacRandDataAddr(), 0, SC_RAND_DATA_LEN);
    /*lint +e534*/

    pstAKFile = (SC_AK_FILE_STRU*)VOS_MemAlloc(CCPU_PID_PAM_OM,
                                               DYNAMIC_MEM_PT,
                                               sizeof(SC_AK_FILE_STRU));

    if (VOS_NULL_PTR == pstAKFile)
    {
        SC_ERROR_LOG("SC_FAC_EndIdentify: VOS_MemAlloc is failed.");
        /* �����ڴ�����ʧ�� */
        return SC_ERROR_CODE_ALLOC_MEM_FAIL;
    }

    /* ��ȡAK-FILE������ǩ��У�� */
    ulResult = SC_COMM_ReadSCFileAndCmpSign(SC_SECRET_FILE_TYPE_AK,
                                            pstAKFile->aucAuthPubKey,
                                            sizeof(SC_AK_FILE_STRU));

    if (SC_ERROR_CODE_NO_ERROR != ulResult)
    {
        /*lint -e534*/
        VOS_MemFree(CCPU_PID_PAM_OM, pstAKFile);
        /*lint +e534*/

        SC_ERROR1_LOG("SC_FAC_EndIdentify: SC_COMM_ReadSCFileAndCmpSign is failed.", ulResult);

        return ulResult;
    }

    /* ����������Ľ���RSA���� */
    lRandDataLen = SC_RAND_DATA_LEN;

    lResult = mdrv_crypto_dec_rsa((VOS_CHAR*)pstIdentifyEndReq->aucIdentifyEndReq,
                                 sizeof(SC_IDENTIFY_END_REQUEST_STRU),
                                 (VOS_CHAR*)pstAKFile->aucAuthPubKey,
                                 sizeof(pstAKFile->aucAuthPubKey),
                                 (VOS_CHAR*)aucRandData, &lRandDataLen);

    if ((VOS_OK != lResult) || (SC_RAND_DATA_LEN != lRandDataLen))
    {
        /*lint -e534*/
        VOS_MemFree(CCPU_PID_PAM_OM, pstAKFile);
        /*lint +e534*/

        SC_ERROR2_LOG("SC_FAC_EndIdentify: mdrv_crypto_dec_rsa is failed.", lResult, lRandDataLen);

        return SC_ERROR_CODE_RSA_DECRYPT_FAIL;
    }

    /* ��SC_StartIdentify���ɵ���������бȶ� */
    if (VOS_OK != VOS_MemCmp(aucRandData, aucOldRandData, SC_RAND_DATA_LEN))
    {
        /*lint -e534*/
        VOS_MemFree(CCPU_PID_PAM_OM, pstAKFile);
        /*lint +e534*/

        SC_ERROR_LOG("SC_FAC_EndIdentify: VOS_MemCmp RandData is failed.");

        return SC_ERROR_CODE_IDENTIFY_FAIL;
    }

    /* ���¼�Ȩ״̬Ϊͨ�� */
    SC_CTX_SetFacAuthStatus(SC_AUTH_STATUS_DONE);

    /* ���÷�����߼�Ȩ��־ΪVOS_FALSE */
    SC_CTX_SetIdentifyStartFlg(VOS_FALSE);

    /*lint -e534*/
    VOS_MemFree(CCPU_PID_PAM_OM, pstAKFile);
    /*lint +e534*/

    return SC_ERROR_CODE_NO_ERROR;
}



SC_ERROR_CODE_ENUM_UINT32 SC_FAC_SetPortAttrib(SC_SET_PORT_ATTRIBUTE_STRU *pstSetPortAttrib)
{
    VOS_UINT32                          ulResult;
    VOS_INT                             lResult;
    VOS_INT                             lDKPwdDataLen;
    VOS_UINT8                           aucDKPwd[SC_PERS_PWD_LEN];
    SC_AK_FILE_STRU                    *pstAKFile;
    SC_DK_FILE_STRU                     stDKFileContent;
    VOS_UINT8                           ucLoop;

    /* �жϼ�Ȩ�Ƿ�ͨ�� */
    if (SC_AUTH_STATUS_DONE != SC_CTX_GetFacAuthStatus())
    {
        SC_ERROR_LOG("SC_FAC_SetPortAttrib: SC_CTX_GetFacAuthStatus is not done.");

        return SC_ERROR_CODE_IDENTIFY_FAIL;
    }

    /* ����AK�ļ����ڴ� */
    pstAKFile = (SC_AK_FILE_STRU*)VOS_MemAlloc(CCPU_PID_PAM_OM,
                                               DYNAMIC_MEM_PT,
                                               sizeof(SC_AK_FILE_STRU));

    if (VOS_NULL_PTR == pstAKFile)
    {
        SC_ERROR_LOG("SC_FAC_SetPortAttrib: VOS_MemAlloc is failed.");
        /* �����ڴ�����ʧ�� */
        return SC_ERROR_CODE_ALLOC_MEM_FAIL;
    }

    /* ��ȡAK-FILE������ǩ��У�� */
    ulResult = SC_COMM_ReadSCFileAndCmpSign(SC_SECRET_FILE_TYPE_AK,
                                            pstAKFile->aucAuthPubKey,
                                            sizeof(SC_AK_FILE_STRU));

    if (SC_ERROR_CODE_NO_ERROR != ulResult)
    {
        /*lint -e534*/
        VOS_MemFree(CCPU_PID_PAM_OM, pstAKFile);
        /*lint +e534*/

        SC_ERROR1_LOG("SC_FAC_SetPortAttrib: SC_COMM_ReadSCFileAndCmpSign is failed.", ulResult);

        return ulResult;
    }

    /* ����������Ľ���RSA���� */
    lDKPwdDataLen = SC_PERS_PWD_LEN;

    lResult = mdrv_crypto_dec_rsa((VOS_CHAR*)pstSetPortAttrib->aucRsaPwd,
                                 sizeof(pstSetPortAttrib->aucRsaPwd),
                                 (VOS_CHAR*)pstAKFile->aucAuthPubKey,
                                 sizeof(pstAKFile->aucAuthPubKey),
                                 (VOS_CHAR*)aucDKPwd, &lDKPwdDataLen);

    if ((VOS_OK != lResult) || (SC_PERS_PWD_LEN != lDKPwdDataLen))
    {
        /*lint -e534*/
        VOS_MemFree(CCPU_PID_PAM_OM, pstAKFile);
        /*lint +e534*/

        return SC_ERROR_CODE_RSA_DECRYPT_FAIL;
    }

    /* �жϽ��ܺ��DK���������Ƿ�Ϊ��ֵΪ"0"~"9"������ */
    for (ucLoop = 0; ucLoop < SC_PERS_PWD_LEN; ucLoop++)
    {
        if (0x09 < aucDKPwd[ucLoop])
        {
            /*lint -e534*/
            VOS_MemFree(CCPU_PID_PAM_OM, pstAKFile);
            /*lint +e534*/

            SC_ERROR_LOG("SC_FAC_SetPortAttrib: aucDKPwd is incorrect!");

            return SC_ERROR_CODE_OTHER_ERROR;
        }
    }

    /* ����DK���� */
    ulResult = SC_COMM_GenerateCryptoPwd(SC_CRYPTO_PASSWORD_TYPE_DK,
                                         aucDKPwd,
                                         SC_PERS_PWD_LEN,
                                         stDKFileContent.aucDKCryptoPwd,
                                         SC_CRYPTO_PWD_LEN);

    if (SC_ERROR_CODE_NO_ERROR != ulResult)
    {
        /*lint -e534*/
        VOS_MemFree(CCPU_PID_PAM_OM, pstAKFile);
        /*lint +e534*/

        SC_ERROR1_LOG("SC_FAC_SetPortAttrib: SC_COMM_GenerateCryptoPwd is failed.", ulResult);

        return ulResult;
    }

    /* ����DKFile.bin�ļ� */
    stDKFileContent.enPortStatus = pstSetPortAttrib->enStatus;

    ulResult = SC_COMM_WriteSecretFile(SC_SECRET_FILE_TYPE_DK,
                                       (VOS_UINT8*)&stDKFileContent,
                                       sizeof(SC_DK_FILE_STRU));

    SC_INFO1_LOG("SC_FAC_SetPortAttrib: The result is:", ulResult);

    /*lint -e534*/
    VOS_MemFree(CCPU_PID_PAM_OM, pstAKFile);
    /*lint +e534*/

    return ulResult;
}


SC_ERROR_CODE_ENUM_UINT32 SC_FAC_GetPortAttrib(
    SC_PORT_STATUS_ENUM_UINT32         *penStatus
)
{
    SC_DK_FILE_STRU                     stDKFile;
    VOS_UINT32                          ulResult;

    /* ��HUKδд�룬��Чʱ����Ĭ��HSIC��OM�ڴ� */
    if (VOS_FALSE == mdrv_efuse_check_huk_valid())
    {
        *penStatus = SC_PORT_STATUS_ON;
        return SC_ERROR_CODE_NO_ERROR;
    }

    /* ��ȡDK-FILE��У��ǩ�� */
    ulResult = SC_COMM_ReadSCFileAndCmpSign(SC_SECRET_FILE_TYPE_DK,
                                            (VOS_UINT8*)&stDKFile,
                                            sizeof(SC_DK_FILE_STRU));

    if (SC_ERROR_CODE_NO_ERROR != ulResult)
    {
        SC_ERROR1_LOG("SC_FAC_GetPortAttrib: SC_COMM_ReadSCFileAndCmpSign is failed.", ulResult);

        return ulResult;
    }

    /* ���ض˿�״̬ */
    *penStatus = stDKFile.enPortStatus;

    return SC_ERROR_CODE_NO_ERROR;
}
SC_ERROR_CODE_ENUM_UINT32 SC_FAC_VerifyPortPassword(
    VOS_UINT8                          *pucPwd,
    VOS_UINT8                           ucLen
)
{
    VOS_UINT32                          ulResult;
    VOS_INT32                           lResult;
    VOS_UINT8                           aucCryptoPwd[SC_CRYPTO_PWD_LEN];
    SC_DK_FILE_STRU                     stDKFile;

    ulResult = SC_ERROR_CODE_BUTT;

    /* ��HUKδд�룬��Чʱ����Ĭ������У��ͨ�� */
    if (VOS_FALSE == mdrv_efuse_check_huk_valid())
    {
        return SC_ERROR_CODE_NO_ERROR;
    }

    /* ������� */
    if ((VOS_NULL_PTR == pucPwd) || (SC_CRYPTO_PWD_LEN != ucLen))
    {
        return ulResult;
    }

    /* ��ȡDK-FILE������У�� */
    ulResult = SC_COMM_ReadSCFileAndCmpSign(SC_SECRET_FILE_TYPE_DK,
                                            (VOS_UINT8*)&stDKFile,
                                            sizeof(SC_DK_FILE_STRU));

    if (SC_ERROR_CODE_NO_ERROR != ulResult)
    {
        SC_ERROR1_LOG("SC_FAC_VerifyPortPassword: SC_COMM_ReadSCFileAndCmpSign is failed.", ulResult);

        return ulResult;
    }

    /* ����DK���� */
    ulResult = SC_COMM_GenerateCryptoPwd(SC_CRYPTO_PASSWORD_TYPE_DK,
                                         pucPwd, ucLen, aucCryptoPwd,
                                         SC_CRYPTO_PWD_LEN);

    if (SC_ERROR_CODE_NO_ERROR != ulResult)
    {
        SC_ERROR1_LOG("SC_FAC_VerifyPortPassword: SC_COMM_GenerateCryptoPwd is failed.", ulResult);

        return ulResult;
    }

    /* �ȶ�DK���� */
    lResult = VOS_MemCmp(aucCryptoPwd, stDKFile.aucDKCryptoPwd, SC_CRYPTO_PWD_LEN);
    if (VOS_OK != lResult)
    {
        SC_ERROR_LOG("SC_FAC_VerifyPortPassword: VOS_MemCmp DK is failed.");

        return SC_ERROR_CODE_DK_INCORRECT;
    }

    return SC_ERROR_CODE_NO_ERROR;
}

#if (FEATURE_ON == FEATURE_VSIM)
SC_ERROR_CODE_ENUM_UINT32 SC_FAC_SetDhKey(
    MODEM_ID_ENUM_UINT16                enModemID,
    SC_DH_KEY_TYPE_ENUM_UINT32          enKeyType,
    VOS_UINT32                          ulKeyLen,
    VOS_UINT8                          *pucKey
)
{
    VOS_UINT32                          ulResult;
    NVIM_VSIM_HVSDH_NV_STRU             stDhNv;

    /* �жϼ�Ȩ�Ƿ�ͨ�� */
    if (SC_AUTH_STATUS_DONE != SC_CTX_GetFacAuthStatus())
    {
        SC_ERROR_LOG("SC_FAC_SetDhKey: SC_CTX_GetFacAuthStatus is not done.");

        return SC_ERROR_CODE_IDENTIFY_NOT_FINISH;
    }

    /* ��NV���ж�����Կ��Ϣ */
    ulResult = NV_ReadEx(enModemID, en_NV_Item_VSIM_HVSDH_INFO, &stDhNv, sizeof(stDhNv));
    if (NV_OK != ulResult)
    {
        SC_ERROR_LOG("SC_FAC_SetDhKey: NV_Read fail.");
        return SC_ERROR_CODE_NV_READ_FAIL;
    }

    if (SC_DH_KEY_SERVER_PUBLIC_KEY == enKeyType)
    {
        /*lint -e534*/
        VOS_MemCpy(stDhNv.stSPublicKey.aucKey, pucKey, ulKeyLen);
        /*lint +e534*/
        stDhNv.stSPublicKey.ulKeyLen = ulKeyLen;
    }
    else if (SC_DH_KEY_MODEM_PUBLIC_KEY == enKeyType)
    {
        /*lint -e534*/
        VOS_MemCpy(stDhNv.stCPublicKey.aucKey, pucKey, ulKeyLen);
        /*lint +e534*/
        stDhNv.stCPublicKey.ulKeyLen = ulKeyLen;
    }
    else
    {
        /*lint -e534*/
        VOS_MemCpy(stDhNv.stCPrivateKey.aucKey, pucKey, ulKeyLen);
        /*lint +e534*/
        stDhNv.stCPrivateKey.ulKeyLen = ulKeyLen;
    }

    /* ����������Կд��NV���� */
    ulResult = NV_WriteEx(enModemID, en_NV_Item_VSIM_HVSDH_INFO, &stDhNv, sizeof(stDhNv));
    if (NV_OK != ulResult)
    {
        SC_ERROR_LOG("SC_FAC_SetDhKey: NV_Write fail.");

        return SC_ERROR_CODE_NV_WRITE_FAIL;
    }

    return SC_ERROR_CODE_NO_ERROR;
}
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

