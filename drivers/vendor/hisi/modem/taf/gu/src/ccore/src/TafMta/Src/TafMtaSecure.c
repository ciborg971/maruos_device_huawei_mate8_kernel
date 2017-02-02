

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "TafMtaSecure.h"
#include "TafMtaMain.h"
#include "ScInterface.h"
#include "SysNvId.h"
#include "TafNvInterface.h"
#include "NVIM_Interface.h"
#include "TafMtaComm.h"
#include "mdrv.h"
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
#include "omnvinterface.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e958*/

#define    THIS_FILE_ID        PS_FILE_ID_TAF_MTA_SECURE_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/

MTA_AT_RESULT_ENUM_UINT32 TAF_MTA_ConvertScErr(
    SC_ERROR_CODE_ENUM_UINT32           enErrCode
)
{
    switch(enErrCode)
    {
        case SC_ERROR_CODE_NO_ERROR:
            return MTA_AT_RESULT_NO_ERROR;

        case SC_ERROR_CODE_OPEN_FILE_FAIL:
        case SC_ERROR_CODE_READ_FILE_FAIL:
        case SC_ERROR_CODE_WRITE_FILE_FAIL:
        case SC_ERROR_CODE_WRITE_FILE_IMEI_FAIL:
            return MTA_AT_RESULT_DEVICE_SEC_FLASH_ERROR;

        case SC_ERROR_CODE_VERIFY_SIGNATURE_FAIL:
        case SC_ERROR_CODE_VERIFY_PUB_KEY_SIGNATURE_FAIL:
            return MTA_AT_RESULT_DEVICE_SEC_SIGNATURE_FAIL;

        case SC_ERROR_CODE_DK_INCORRECT:
            return MTA_AT_RESULT_DEVICE_SEC_DK_INCORRECT;

        case SC_ERROR_CODE_UNLOCK_KEY_INCORRECT:
            return MTA_AT_RESULT_DEVICE_SEC_UNLOCK_KEY_INCORRECT;

        case SC_ERROR_CODE_RSA_ENCRYPT_FAIL:
            return MTA_AT_RESULT_DEVICE_SEC_RSA_ENCRYPT_FAIL;

        case SC_ERROR_CODE_RSA_DECRYPT_FAIL:
            return MTA_AT_RESULT_DEVICE_SEC_RSA_DECRYPT_FAIL;

        case SC_ERROR_CODE_GET_RAND_NUMBER_FAIL:
            return MTA_AT_RESULT_DEVICE_SEC_GET_RAND_NUMBER_FAIL;

        case SC_ERROR_CODE_IDENTIFY_FAIL:
        case SC_ERROR_CODE_IDENTIFY_NOT_FINISH:
            return MTA_AT_RESULT_DEVICE_SEC_IDENTIFY_FAIL;

        case SC_ERROR_CODE_WRITE_HUK_FAIL:
            return MTA_AT_RESULT_DEVICE_SEC_WRITE_HUK_FAIL;

        case SC_ERROR_CODE_NV_READ_FAIL:
        case SC_ERROR_CODE_NV_WRITE_FAIL:
            return MTA_AT_RESULT_DEVICE_SEC_NV_ERROR;

        case SC_ERROR_CODE_LOCK_CODE_INVALID:
        case SC_ERROR_CODE_CREATE_KEY_FAIL:
        case SC_ERROR_CODE_GENERATE_HASH_FAIL:
        case SC_ERROR_CODE_AES_ECB_ENCRYPT_FAIL:
        case SC_ERROR_CODE_ALLOC_MEM_FAIL:
        case SC_ERROR_CODE_UNLOCK_STATUS_ABNORMAL:
        case SC_ERROR_CODE_BUTT:
        default:
            /* 上述错误以及其他错误，返回OTHER_ERROR */
            return MTA_AT_RESULT_DEVICE_SEC_OTHER_ERROR;
    }
}
VOS_VOID TAF_MTA_RcvAtApSecSetReq( VOS_VOID *pMsg )
{
    AT_MTA_MSG_STRU                    *pstAtMtaReqMsg;
    AT_MTA_APSEC_REQ_STRU              *pstApSecReq;
    MTA_AT_APSEC_CNF_STRU               stApSecCnf;
    VOS_UINT32                          ulResult;

    /* 局部变量初始化 */
    pstAtMtaReqMsg  = (AT_MTA_MSG_STRU*)pMsg;
    pstApSecReq     = (AT_MTA_APSEC_REQ_STRU*)pstAtMtaReqMsg->aucContent;

    /* 调用SC模块提供的安全封包解析函数 */
    ulResult        = SC_APSEC_ParseSecPacket(&pstApSecReq->ulSPLen,
                                              pstApSecReq->aucSecPacket);
    if (VOS_OK == ulResult)
    {
        /* 解析成功，将返回的安全封包发送给AT模块 */
        stApSecCnf.enResult = MTA_AT_RESULT_NO_ERROR;
        stApSecCnf.ulSPLen  = pstApSecReq->ulSPLen;
        PS_MEM_CPY(stApSecCnf.aucSecPacket, pstApSecReq->aucSecPacket, MTA_SEC_PACKET_MAX_LEN);
    }
    else
    {
        /* 解析失败，返回对应的错误码 */
        PS_MEM_SET(&stApSecCnf, 0x00, sizeof(MTA_AT_APSEC_CNF_STRU));
        stApSecCnf.enResult = MTA_AT_RESULT_ERROR;
    }

    /* 返回跨核消息ID_MTA_AT_APSEC_SET_CNF到AT模块 */
    TAF_MTA_SndAtMsg( &pstAtMtaReqMsg->stAppCtrl,
                      ID_MTA_AT_APSEC_SET_CNF,
                      sizeof(MTA_AT_APSEC_CNF_STRU),
                      (VOS_UINT8*)&stApSecCnf );

    return;
}
VOS_VOID TAF_MTA_RcvAtSimlockUnlockSetReq( VOS_VOID *pMsg )
{
    AT_MTA_MSG_STRU                    *pstAtMtaReqMsg;
    AT_MTA_SIMLOCKUNLOCK_REQ_STRU      *pstSimlockUnlockReq;
    MTA_AT_SIMLOCKUNLOCK_CNF_STRU       stSimlockUnlockCnf;
    VOS_UINT32                          ulResult;

    /* 局部变量初始化 */
    pstAtMtaReqMsg          = (AT_MTA_MSG_STRU *)pMsg;
    pstSimlockUnlockReq     = (AT_MTA_SIMLOCKUNLOCK_REQ_STRU *)pstAtMtaReqMsg->aucContent;

    /* 调用SC模块提供的锁网锁卡解锁函数 */
    ulResult        = SC_PERS_SimlockUnlock(pstSimlockUnlockReq->enCategory,
                                            pstSimlockUnlockReq->aucPassword);
    if (VOS_OK == ulResult)
    {
        /* 解锁成功，返回结果给AT模块 */
        stSimlockUnlockCnf.enResult = MTA_AT_RESULT_NO_ERROR;
    }
    else
    {
        /* 解锁失败，返回结果给AT模块 */
        stSimlockUnlockCnf.enResult = MTA_AT_RESULT_ERROR;
    }

    /* 返回跨核消息ID_MTA_AT_APSEC_SET_CNF到AT模块 */
    TAF_MTA_SndAtMsg( &pstAtMtaReqMsg->stAppCtrl,
                      ID_MTA_AT_SIMLOCKUNLOCK_SET_CNF,
                      sizeof(MTA_AT_SIMLOCKUNLOCK_CNF_STRU),
                      (VOS_UINT8*)&stSimlockUnlockCnf );

    return;
}
VOS_VOID TAF_MTA_RcvQryImeiVerifyReq(VOS_VOID *pMsg)
{
    SC_ERROR_CODE_ENUM_UINT32           enScResult;
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulImeiVerify;
    AT_MTA_MSG_STRU                    *pstAtMtaReqMsg = VOS_NULL_PTR;

    pstAtMtaReqMsg = (AT_MTA_MSG_STRU *)pMsg;
    ulImeiVerify = VOS_TRUE;

    /* 由PID获取MODEMID */
    enModemId = VOS_GetModemIDFromPid(UEPS_PID_MTA);

    /* 调用SC接口进行IMEI校验，若函数执行失败，则按照IMEI校验失败处理 */
    enScResult = SC_PERS_VerifyIMEI(enModemId);
    if (SC_ERROR_CODE_NO_ERROR != enScResult)
    {
        ulImeiVerify = VOS_FALSE;
    }

    /* 返回跨核消息ID_MTA_AT_IMEI_VERIFY_QRY_CNF到AT模块 */
    TAF_MTA_SndAtMsg( &pstAtMtaReqMsg->stAppCtrl,
                      ID_MTA_AT_IMEI_VERIFY_QRY_CNF,
                      sizeof(VOS_UINT32),
                      (VOS_UINT8*)&ulImeiVerify );

    return;
}
VOS_VOID TAF_MTA_RcvQryCgsnReq(VOS_VOID *pMsg)
{
    MODEM_ID_ENUM_UINT16                enModemId;
    AT_MTA_MSG_STRU                    *pstAtMtaReqMsg = VOS_NULL_PTR;
    MTA_AT_CGSN_QRY_CNF_STRU            stCgsnCnf;

    /* 初始化 */
    pstAtMtaReqMsg = (AT_MTA_MSG_STRU *)pMsg;
    PS_MEM_SET(&stCgsnCnf, 0x00, sizeof(MTA_AT_CGSN_QRY_CNF_STRU));

    /* 由PID获取MODEMID */
    enModemId = VOS_GetModemIDFromPid(UEPS_PID_MTA);

    /* 调用SC接口读取IMEI号码 */
    (VOS_VOID)SC_PERS_NvRead(enModemId, en_NV_Item_IMEI, stCgsnCnf.aucImei, NV_ITEM_IMEI_SIZE);

    /* 返回跨核消息ID_MTA_AT_IMEI_VERIFY_QRY_CNF到AT模块 */
    TAF_MTA_SndAtMsg( &pstAtMtaReqMsg->stAppCtrl,
                      ID_MTA_AT_CGSN_QRY_CNF,
                      sizeof(MTA_AT_CGSN_QRY_CNF_STRU),
                      (VOS_UINT8*)&stCgsnCnf );

    return;
}


/*lint +e958*/

VOS_VOID TAF_MTA_RcvAtNvwrSecCtrlSetReq( VOS_VOID *pMsg )
{
    AT_MTA_MSG_STRU                    *pstAtMtaReqMsg;
    AT_MTA_NVWRSECCTRL_SET_REQ_STRU    *pstNvwrSecCtrlReq;
    MTA_AT_RESULT_CNF_STRU              stNvwrSecCtrlCnf;
    TAF_NV_NVWR_SEC_CTRL_STRU           stNvwrSecCtrlNV;
    IMEI_STRU                           stImeiSrc;
    IMEI_STRU                           stImeiPara;
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulImeiLen;
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT8                           aucImeiStr[TAF_NVIM_ITEM_IMEI_SIZE + 1];

    /* 局部变量初始化 */
    pstAtMtaReqMsg          = (AT_MTA_MSG_STRU *)pMsg;
    pstNvwrSecCtrlReq       = (AT_MTA_NVWRSECCTRL_SET_REQ_STRU *)pstAtMtaReqMsg->aucContent;

    /* SC提供的RSA封装需要调用者将解密后结果的预期长度传入 */
    ulImeiLen               = MTA_IMEI_LEN;

    PS_MEM_SET(&stNvwrSecCtrlNV, 0x00, sizeof(stNvwrSecCtrlNV));
    PS_MEM_SET(&stNvwrSecCtrlCnf, 0x00, sizeof(stNvwrSecCtrlCnf));
    PS_MEM_SET(&stImeiSrc, 0x00, sizeof(stImeiSrc));
    PS_MEM_SET(&stImeiPara, 0x00, sizeof(stImeiPara));
    PS_MEM_SET(aucImeiStr, 0x00, sizeof(aucImeiStr));

    /* 如果单板没有HUK则不作安全校验 */
    if (VOS_TRUE == mdrv_efuse_check_huk_valid())
    {
        /* 单板已经写入HUK但未下发安全密文则返回失败 */
        if (VOS_TRUE != pstNvwrSecCtrlReq->ucSecStrFlg)
        {
            stNvwrSecCtrlCnf.enResult = MTA_AT_RESULT_DEVICE_SEC_SIGNATURE_FAIL;

            /* 返回跨核消息ID_MTA_AT_APSEC_SET_CNF到AT模块 */
            TAF_MTA_SndAtMsg( &pstAtMtaReqMsg->stAppCtrl,
                              ID_MTA_AT_NVWRSECCTRL_SET_CNF,
                              sizeof(stNvwrSecCtrlCnf),
                              (VOS_UINT8*)&stNvwrSecCtrlCnf );

            return;
        }

        /* 由PID获取MODEMID */
        enModemId = VOS_GetModemIDFromPid(UEPS_PID_MTA);

        /* 调用SC接口读取IMEI号码 */
        ulResult = SC_PERS_NvRead(enModemId, en_NV_Item_IMEI, stImeiSrc.aucImei, TAF_NVIM_ITEM_IMEI_SIZE);

        if (SC_ERROR_CODE_NO_ERROR != ulResult)
        {
            /* 异常，返回结果给AT模块 */
            stNvwrSecCtrlCnf.enResult = TAF_MTA_ConvertScErr(ulResult);

            /* 返回跨核消息ID_MTA_AT_APSEC_SET_CNF到AT模块 */
            TAF_MTA_SndAtMsg( &pstAtMtaReqMsg->stAppCtrl,
                              ID_MTA_AT_NVWRSECCTRL_SET_CNF,
                              sizeof(stNvwrSecCtrlCnf),
                              (VOS_UINT8*)&stNvwrSecCtrlCnf );

            return;
        }

        /* 调用SC模块接口, 对密文进行RSA解密 */
        ulResult = SC_FAC_RsaDecrypt(pstNvwrSecCtrlReq->aucSecString,
                                     AT_RSA_CIPHERTEXT_LEN,
                                     aucImeiStr,
                                     &ulImeiLen);

        if (MTA_IMEI_LEN != ulImeiLen)
        {
            ulResult = SC_ERROR_CODE_RSA_DECRYPT_FAIL;
        }

        if (SC_ERROR_CODE_NO_ERROR != ulResult)
        {
            /* 异常，返回结果给AT模块 */
            stNvwrSecCtrlCnf.enResult = TAF_MTA_ConvertScErr(ulResult);

            /* 返回跨核消息ID_MTA_AT_APSEC_SET_CNF到AT模块 */
            TAF_MTA_SndAtMsg( &pstAtMtaReqMsg->stAppCtrl,
                              ID_MTA_AT_NVWRSECCTRL_SET_CNF,
                              sizeof(stNvwrSecCtrlCnf),
                              (VOS_UINT8*)&stNvwrSecCtrlCnf );

            return;
        }

        /* 数字字符串转换为数字串 */
        if (VOS_OK != TAF_MTA_AcNums2DecNums(aucImeiStr, stImeiPara.aucImei, ulImeiLen))
        {
            stNvwrSecCtrlCnf.enResult = MTA_AT_RESULT_DEVICE_SEC_SIGNATURE_FAIL;

            /* 返回跨核消息ID_MTA_AT_APSEC_SET_CNF到AT模块 */
            TAF_MTA_SndAtMsg( &pstAtMtaReqMsg->stAppCtrl,
                              ID_MTA_AT_NVWRSECCTRL_SET_CNF,
                              sizeof(stNvwrSecCtrlCnf),
                              (VOS_UINT8*)&stNvwrSecCtrlCnf );

            return;
        }

        /* 校验IMEI码 */
        if (0 != PS_MEM_CMP(stImeiPara.aucImei, stImeiSrc.aucImei, ulImeiLen))
        {
            stNvwrSecCtrlCnf.enResult = MTA_AT_RESULT_DEVICE_SEC_SIGNATURE_FAIL;

            /* 返回跨核消息ID_MTA_AT_APSEC_SET_CNF到AT模块 */
            TAF_MTA_SndAtMsg( &pstAtMtaReqMsg->stAppCtrl,
                              ID_MTA_AT_NVWRSECCTRL_SET_CNF,
                              sizeof(stNvwrSecCtrlCnf),
                              (VOS_UINT8*)&stNvwrSecCtrlCnf );

            return;
        }
    }

    /* 修改安全控制NV */
    if (NV_OK == NV_Read(en_NV_Item_NVWR_SEC_CTRL, &stNvwrSecCtrlNV, sizeof(stNvwrSecCtrlNV)))
    {
        stNvwrSecCtrlNV.ucSecType = pstNvwrSecCtrlReq->ucSecType;

        if (NV_OK == NV_Write(en_NV_Item_NVWR_SEC_CTRL, &stNvwrSecCtrlNV, sizeof(stNvwrSecCtrlNV)))
        {
            /* 设置成功 */
            stNvwrSecCtrlCnf.enResult = MTA_AT_RESULT_NO_ERROR;

            /* 返回跨核消息ID_MTA_AT_APSEC_SET_CNF到AT模块 */
            TAF_MTA_SndAtMsg( &pstAtMtaReqMsg->stAppCtrl,
                              ID_MTA_AT_NVWRSECCTRL_SET_CNF,
                              sizeof(stNvwrSecCtrlCnf),
                              (VOS_UINT8*)&stNvwrSecCtrlCnf );

            return;
        }
    }

    /* NV修改失败 */
    stNvwrSecCtrlCnf.enResult = MTA_AT_RESULT_ERROR;

    /* 返回跨核消息ID_MTA_AT_APSEC_SET_CNF到AT模块 */
    TAF_MTA_SndAtMsg( &pstAtMtaReqMsg->stAppCtrl,
                      ID_MTA_AT_NVWRSECCTRL_SET_CNF,
                      sizeof(stNvwrSecCtrlCnf),
                      (VOS_UINT8*)&stNvwrSecCtrlCnf );

    return;
}

/* Added by z00316370 for Nv_Esn_Meid 2015-7-23 begin */
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

#ifdef DMT
VOS_UINT32 CAS_GetpEsnByMeid(VOS_UINT8 *pucMeid, VOS_UINT32 *pulEsn)
{
    *pulEsn = 0x80c16f14;

    return VOS_OK;
}
#endif

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvMeidSetReq
 功能描述  : MTA预处理中处理^MEID设置命令
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月23日
    作    者   : z00316370
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MTA_RcvMeidSetReq(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pstSetReq       = VOS_NULL_PTR;
    AT_MTA_MEID_SET_REQ_STRU           *pstMeidSetReq   = VOS_NULL_PTR;
    MTA_AT_RESULT_CNF_STRU              stMeifSetCnf;
    NV_MEID_STRU                        stMeId;
    NV_PESN_STRU                        stPEsn;
    NV_ESN_MEID_STRU                    stEsnMeId;
    VOS_UINT32                          ulEsn;

    PS_MEM_SET(&stMeId, 0x00, sizeof(NV_MEID_STRU));
    PS_MEM_SET(&stPEsn, 0x00, sizeof(NV_PESN_STRU));
    PS_MEM_SET(&stEsnMeId, 0x00, sizeof(NV_ESN_MEID_STRU));
    PS_MEM_SET(&stMeifSetCnf, 0x00, sizeof(stMeifSetCnf));

    pstSetReq           = (AT_MTA_MSG_STRU *)pMsg;
    pstMeidSetReq       = (AT_MTA_MEID_SET_REQ_STRU *)pstSetReq->aucContent;

    PS_MEM_CPY(stMeId.aucMeID, pstMeidSetReq->aucMeid, AT_MTA_MEID_DATA_LEN * sizeof(VOS_UINT8));

    /* 根据meid计算pesn */
    if (VOS_OK != CAS_GetpEsnByMeid(pstMeidSetReq->aucMeid, &ulEsn))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvMeidSetReq():Cal PESN Fail!");

        stMeifSetCnf.enResult = MTA_AT_RESULT_INCORRECT_PARAMETERS;
        /* 给at回消息 */
        TAF_MTA_SndAtMsg(&pstSetReq->stAppCtrl,
                         ID_MTA_AT_MEID_SET_CNF,
                         sizeof(stMeifSetCnf),
                         (VOS_UINT8*)&stMeifSetCnf );

        return;
    }

    stPEsn.aucPEsn[0] = ((VOS_UINT8)ulEsn & 0xFF);
    stPEsn.aucPEsn[1] = ((VOS_UINT8)(ulEsn>>8) & 0xFF);
    stPEsn.aucPEsn[2] = ((VOS_UINT8)(ulEsn>>16) & 0xFF);
    stPEsn.aucPEsn[3] = ((VOS_UINT8)(ulEsn>>24) & 0xFF);

    if (NV_OK != NV_Write(en_NV_Item_MEID, &stMeId, sizeof(stMeId)))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvMeidSetReq():en_NV_Item_MEID NV Write Fail!");

        stMeifSetCnf.enResult = MTA_AT_RESULT_DEVICE_SEC_NV_ERROR;
        /* 给at回消息 */
        TAF_MTA_SndAtMsg(&pstSetReq->stAppCtrl,
                         ID_MTA_AT_MEID_SET_CNF,
                         sizeof(stMeifSetCnf),
                         (VOS_UINT8*)&stMeifSetCnf );

        return;
    }

    if (NV_OK != NV_Write(en_NV_Item_PESN, &stPEsn, sizeof(stPEsn)))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvMeidSetReq():en_NV_Item_PESN NV Write Fail!");

        stMeifSetCnf.enResult = MTA_AT_RESULT_DEVICE_SEC_NV_ERROR;
        /* 给at回消息 */
        TAF_MTA_SndAtMsg(&pstSetReq->stAppCtrl,
                         ID_MTA_AT_MEID_SET_CNF,
                         sizeof(stMeifSetCnf),
                         (VOS_UINT8*)&stMeifSetCnf );

        return;
    }

    /* 更新老的NV项 */
    stEsnMeId.enEsnMeIDFlag = MEID_ME_ENABLE_FLAG;
    stEsnMeId.aucEsn[0]     = PESN_NV_DATA_LEN;
    PS_MEM_CPY(&(stEsnMeId.aucEsn[1]), stPEsn.aucPEsn, PESN_NV_DATA_LEN);

    stEsnMeId.aucMeID[0]    = MEID_NV_DATA_LEN_NEW;
    PS_MEM_CPY(&(stEsnMeId.aucMeID[1]), stMeId.aucMeID, MEID_NV_DATA_LEN_NEW);

    if (NV_OK != NV_Write(en_NV_Item_ESN_MEID, &stEsnMeId, sizeof(stEsnMeId)))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvMeidSetReq():en_NV_Item_ESN_MEID NV Write Fail!");

        stMeifSetCnf.enResult = MTA_AT_RESULT_DEVICE_SEC_NV_ERROR;
        /* 给at回消息 */
        TAF_MTA_SndAtMsg(&pstSetReq->stAppCtrl,
                         ID_MTA_AT_MEID_SET_CNF,
                         sizeof(stMeifSetCnf),
                         (VOS_UINT8*)&stMeifSetCnf );

        return;
    }

    stMeifSetCnf.enResult = MTA_AT_RESULT_NO_ERROR;

    /* 给at回消息 */
    TAF_MTA_SndAtMsg(&pstSetReq->stAppCtrl,
                     ID_MTA_AT_MEID_SET_CNF,
                     sizeof(stMeifSetCnf),
                     (VOS_UINT8*)&stMeifSetCnf );

    return;
}
/* Added by z00316370 for Nv_Esn_Meid 2015-7-23 end */
#endif



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

