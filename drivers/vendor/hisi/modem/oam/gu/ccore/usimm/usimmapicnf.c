

#include "UsimmApi.h"
#include "UsimPsInterface.h"
#include "usimmbase.h"
#include "usimmglobal.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_USIMM_APICNF_C
/*lint +e767*/

#if (FEATURE_ON == FEATURE_UE_UICC_MULTI_APP_SUPPORT)


VOS_VOID USIMM_MaxRecordNumCnf(
    USIMM_QUERYFILE_REQ_STRU           *pstNewMsg,
    VOS_UINT32                          ulErrorCode,
    USIMM_FILECNF_INFO_STRU            *pstCnfInfo
)
{
    USIMM_QUERYFILE_CNF_STRU           *pstUsimMsg;

    pstUsimMsg = (USIMM_QUERYFILE_CNF_STRU*)VOS_AllocMsg(WUEPS_PID_USIM,
                                                         sizeof(USIMM_QUERYFILE_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstUsimMsg)
    {
        USIMM_ERROR_LOG("USIMM_MaxRecordNumCnf: VOS_AllocMsg is Failed");

        return;
    }

    pstUsimMsg->stCmdResult.ulReceiverPid       = pstNewMsg->stMsgHeader.ulSenderPid;
    pstUsimMsg->stCmdResult.ulErrorCode         = ulErrorCode;
    pstUsimMsg->stCmdResult.enMsgName           = USIMM_QUERYFILE_CNF;
    pstUsimMsg->ucRecordNum                     = pstCnfInfo->ucRecordNum;
    pstUsimMsg->ucRecordLen                     = pstCnfInfo->ucRecordLen;
    pstUsimMsg->enFileStatus                    = (USIMM_EFSTATUS_ENUM_UINT8)pstCnfInfo->ulFileStatus;
    pstUsimMsg->enFileRWFlag                    = (VOS_UINT8)pstCnfInfo->ulFileReadUpdateFlag;

    if (ulErrorCode != USIMM_SW_OK)
    {
        pstUsimMsg->stCmdResult.ulResult  = VOS_ERR;
    }
    else
    {
        pstUsimMsg->stCmdResult.ulResult  = VOS_OK;
    }

    /*lint -e534*/
    VOS_MemCpy(&pstUsimMsg->stFilePath, &pstNewMsg->stFilePath, sizeof(pstNewMsg->stFilePath));
    /*lint +e534*/

    (VOS_VOID)VOS_SendMsg(WUEPS_PID_USIM, pstUsimMsg);

    return;
}


VOS_VOID USIMM_PinHandleCnf(
    USIMM_PINHANDLE_REQ_STRU           *pstReqMsg,
    VOS_UINT32                          ulResult,
    USIMM_PIN_INFO_STRU                *pstPINinfo)
{
    USIMM_PINHANDLE_CNF_STRU           *pstUsimMsg;

    pstUsimMsg = (USIMM_PINHANDLE_CNF_STRU *)VOS_AllocMsg(WUEPS_PID_USIM, sizeof(USIMM_PINHANDLE_CNF_STRU)-VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstUsimMsg)
    {
        USIMM_ERROR_LOG("USIMM_PinHandleCnf: VOS_AllocMsg is Failed");

        return;
    }

    pstUsimMsg->stCmdResult.ulReceiverPid                   = pstReqMsg->stMsgHeader.ulSenderPid;
    pstUsimMsg->stCmdResult.enMsgName                       = USIMM_PINHANDLE_CNF;
    pstUsimMsg->stCmdResult.ulResult                        = ulResult;
    pstUsimMsg->stCmdResult.ulErrorCode                     = ulResult;
    pstUsimMsg->stCmdResult.enApptype                       = pstReqMsg->stMsgHeader.enAppType;
    pstUsimMsg->stCmdResult.ulSendPara                      = pstReqMsg->stMsgHeader.ulSendPara;
    pstUsimMsg->enCmdType                                   = pstReqMsg->enCmdType;
    pstUsimMsg->enPinType                                   = pstReqMsg->enPINType;

    /*lint -e534*/
    VOS_MemCpy(&pstUsimMsg->stPinInfo, pstPINinfo, sizeof(USIMM_PIN_INFO_STRU));
    /*lint +e534*/

    (VOS_VOID)VOS_SendMsg(WUEPS_PID_USIM, pstUsimMsg);

    return;
}


VOS_VOID USIMM_SetFileCnf(
    USIMM_UPDATEFILE_REQ_STRU           *pstUpdateMsg,
    VOS_UINT32                          ulErrorCode,
    USIMM_SETCNF_INFO_STRU              *pstCnfInfo)
{
    USIMM_UPDATEFILE_CNF_STRU          *pstUsimMsg;
    VOS_UINT32                          ulResult;

    pstUsimMsg = (USIMM_UPDATEFILE_CNF_STRU*)VOS_AllocMsg(WUEPS_PID_USIM, sizeof(USIMM_UPDATEFILE_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstUsimMsg)
    {
        return;
    }

    if (ulErrorCode != USIMM_SW_OK)
    {
        ulResult = VOS_ERR;
    }
    else
    {
        ulResult = VOS_OK;
    }

    pstUsimMsg->stCmdResult.enMsgName       = USIMM_UPDATEFILE_CNF;
    pstUsimMsg->stCmdResult.ulReceiverPid   = pstUpdateMsg->stMsgHeader.ulSenderPid;
    pstUsimMsg->stCmdResult.ulResult        = ulResult;
    pstUsimMsg->stCmdResult.ulErrorCode     = ulErrorCode;
    pstUsimMsg->stCmdResult.ulSendPara      = pstUpdateMsg->stMsgHeader.ulSendPara;
    pstUsimMsg->stCmdResult.enApptype       = pstUpdateMsg->stMsgHeader.enAppType;
    pstUsimMsg->usEFLen                     = pstCnfInfo->usEFLen;
    pstUsimMsg->ucRecordNum                 = pstCnfInfo->ucRecordNum;

    /*lint -e534*/
    VOS_MemCpy(&pstUsimMsg->stFilePath, &pstUpdateMsg->stFilePath, sizeof(pstUpdateMsg->stFilePath));
    /*lint +e534*/

    (VOS_VOID)VOS_SendMsg(WUEPS_PID_USIM, pstUsimMsg);

    return;
}


VOS_VOID USIMM_GetFileCnf(
    USIMM_READFILE_REQ_STRU            *pstReadMsg,
    VOS_UINT32                          ulErrorCode,
    USIMM_GETCNF_INFO_STRU             *pstCnfInfo)
{
    USIMM_READFILE_CNF_STRU            *pstUsimMsg;
    VOS_UINT32                          ulResult;

    pstUsimMsg = (USIMM_READFILE_CNF_STRU*)VOS_AllocMsg(WUEPS_PID_USIM, (sizeof(USIMM_READFILE_CNF_STRU) - VOS_MSG_HEAD_LENGTH) + pstCnfInfo->usDataLen);

    if(VOS_NULL_PTR == pstUsimMsg)
    {
        USIMM_ERROR_LOG("USIMM_GetFileCnf: VOS_AllocMsg is Failed");

        return;
    }

    if (ulErrorCode != USIMM_SW_OK)
    {
        ulResult = VOS_ERR;
    }
    else
    {
        ulResult = VOS_OK;
    }

    pstUsimMsg->stCmdResult.enMsgName       = USIMM_READFILE_CNF;
    pstUsimMsg->stCmdResult.ulErrorCode     = ulErrorCode;
    pstUsimMsg->stCmdResult.ulResult        = ulResult;
    pstUsimMsg->stCmdResult.ulReceiverPid   = pstReadMsg->stMsgHeader.ulSenderPid;
    pstUsimMsg->stCmdResult.ulSendPara      = pstReadMsg->stMsgHeader.ulSendPara;
    pstUsimMsg->stCmdResult.enApptype       = pstReadMsg->stMsgHeader.enAppType;

    /*lint -e534*/
    VOS_MemCpy(&pstUsimMsg->stFilePath, &pstReadMsg->stFilePath, sizeof(USIMM_FILEPATH_INFO_STRU));
    /*lint +e534*/

    if (USIMM_SW_OK == ulErrorCode)
    {
        pstUsimMsg->ucRecordNum = pstCnfInfo->ucRecordNum;
        pstUsimMsg->usEfLen     = pstCnfInfo->usEfLen;
        pstUsimMsg->ucTotalNum  = pstCnfInfo->ucTotalNum;

        /*lint -e534*/
        VOS_MemCpy(pstUsimMsg->aucEf, pstCnfInfo->pucEf, pstCnfInfo->usDataLen);
        /*lint +e534*/
    }
    else
    {
        pstUsimMsg->ucRecordNum = 0;
        pstUsimMsg->usEfLen     = 0;
        pstUsimMsg->ucTotalNum  = 0;
    }

    (VOS_VOID)VOS_SendMsg(WUEPS_PID_USIM, pstUsimMsg);

    return;
}


VOS_VOID USIMM_ResetCnf(
    VOS_UINT32                          ulReceiverPid,
    USIMM_REFRESH_TYPE_ENUM_UINT32      enRefreshType,
    VOS_UINT32                          ulResult,
    VOS_UINT16                          usSATLen)
{
    USIMM_STKREFRESH_CNF_STRU              *pstUsimMsg;

    pstUsimMsg = (USIMM_STKREFRESH_CNF_STRU *)VOS_AllocMsg(WUEPS_PID_USIM,
                                                       sizeof(USIMM_STKREFRESH_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstUsimMsg)
    {
        USIMM_ERROR_LOG("USIMM_ResetCnf: VOS_AllocMsg is Failed");

        return;
    }

    pstUsimMsg->stCmdResult.ulReceiverPid                   = ulReceiverPid;
    pstUsimMsg->stCmdResult.enMsgName                       = USIMM_STKREFRESH_CNF;
    pstUsimMsg->stCmdResult.ulResult                        = ulResult;
    pstUsimMsg->stCmdResult.ulErrorCode                     = ulResult;
    pstUsimMsg->enRefreshType                               = enRefreshType;
    pstUsimMsg->ulSatLen                                    = usSATLen;

    (VOS_VOID)VOS_SendMsg(WUEPS_PID_USIM, pstUsimMsg);

    return;
}


VOS_VOID USIMM_TelecomAuthCnf(
    USIMM_AUTHENTICATION_REQ_STRU      *pstMsg,
    USIMM_TELECOM_AUTH_INFO_STRU       *pstCnfInfo)
{
    USIMM_AUTHENTICATION_CNF_STRU      *pstCnfMsg;

    /* ������Ϣ�ڴ�  */
    pstCnfMsg = (USIMM_AUTHENTICATION_CNF_STRU *)VOS_AllocMsg(WUEPS_PID_USIM, sizeof(USIMM_AUTHENTICATION_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstCnfMsg)
    {
        USIMM_ERROR_LOG("USIMM_TelecomAuthCnf: VOS_AllocMsg is Failed");

        return;
    }

    /*lint -e534*/
    VOS_MemSet((VOS_UINT8*)pstCnfMsg + VOS_MSG_HEAD_LENGTH, 0, sizeof(USIMM_AUTHENTICATION_CNF_STRU) - VOS_MSG_HEAD_LENGTH);
    /*lint +e534*/

    pstCnfMsg->stCmdResult.ulReceiverPid= pstMsg->stMsgHeader.ulSenderPid;
    pstCnfMsg->stCmdResult.enMsgName    = USIMM_AUTHENTICATION_CNF;
    pstCnfMsg->stCmdResult.enApptype    = USIMM_GUTL_APP;

    /* ������ֵ����Ȩ����������� */
    pstCnfMsg->stCmdResult.ulResult     = VOS_OK;
    pstCnfMsg->stCmdResult.ulErrorCode  = VOS_OK;

    pstCnfMsg->stCmdResult.ulSendPara   = pstMsg->stMsgHeader.ulSendPara;
    pstCnfMsg->enAuthType               = pstMsg->enAuthType;

     /* ��Ȩ��� */
    pstCnfMsg->enResult                 = pstCnfInfo->enResult;

    if ((VOS_NULL_PTR != pstCnfInfo->pucIK)
        && (sizeof(pstCnfMsg->uCnfData.stTELECnf.aucIK) > pstCnfInfo->pucIK[0]))
    {
        /*lint -e534*/
        VOS_MemCpy(pstCnfMsg->uCnfData.stTELECnf.aucIK, pstCnfInfo->pucIK, pstCnfInfo->pucIK[0] + 1);
        /*lint +e534*/
    }

    if ((VOS_NULL_PTR != pstCnfInfo->pucCK)
        && (sizeof(pstCnfMsg->uCnfData.stTELECnf.aucCK) > pstCnfInfo->pucCK[0]))
    {
        /*lint -e534*/
        VOS_MemCpy(pstCnfMsg->uCnfData.stTELECnf.aucCK, pstCnfInfo->pucCK, pstCnfInfo->pucCK[0] + 1);
        /*lint +e534*/
    }

    if ((VOS_NULL_PTR != pstCnfInfo->pucGsmKC)
        && (sizeof(pstCnfMsg->uCnfData.stTELECnf.aucGsmKc) > pstCnfInfo->pucGsmKC[0]))
    {
        /*lint -e534*/
        VOS_MemCpy(pstCnfMsg->uCnfData.stTELECnf.aucGsmKc, pstCnfInfo->pucGsmKC, pstCnfInfo->pucGsmKC[0] + 1);
        /*lint +e534*/
    }

    if ((VOS_NULL_PTR != pstCnfInfo->pucAuts)
        && (sizeof(pstCnfMsg->uCnfData.stTELECnf.aucAuts) > pstCnfInfo->pucAuts[0]))
    {
        /*lint -e534*/
        VOS_MemCpy(pstCnfMsg->uCnfData.stTELECnf.aucAuts, pstCnfInfo->pucAuts, pstCnfInfo->pucAuts[0] + 1);
        /*lint +e534*/
    }

    if ((VOS_NULL_PTR != pstCnfInfo->pucAuthRes)
        && (sizeof(pstCnfMsg->uCnfData.stTELECnf.aucAuthRes) > pstCnfInfo->pucAuthRes[0]))
    {
        /*lint -e534*/
        VOS_MemCpy(pstCnfMsg->uCnfData.stTELECnf.aucAuthRes, pstCnfInfo->pucAuthRes, pstCnfInfo->pucAuthRes[0] + 1);
        /*lint +e534*/
    }

    /* �ظ���Ϣ */
    (VOS_VOID)VOS_SendMsg(WUEPS_PID_USIM, pstCnfMsg);

    return;
}


VOS_VOID USIMM_ImsAuthCnf(
    USIMM_AUTHENTICATION_REQ_STRU       *pstMsg,
    USIMM_IMS_AUTH_INFO_STRU            *pstCnfInfo)
{
    USIMM_AUTHENTICATION_CNF_STRU      *pstCnfMsg;
    VOS_UINT32                          ulNafLen = 0;

    /* ��ȡNAF���ݵĳ��� */
    if (VOS_NULL_PTR != pstCnfInfo->pucKs_ext_NAF)
    {
        ulNafLen = pstCnfInfo->pucKs_ext_NAF[0];
    }

    /* ������Ϣ�ڴ�  */
    pstCnfMsg = (USIMM_AUTHENTICATION_CNF_STRU *)VOS_AllocMsg(WUEPS_PID_USIM,
                                                              sizeof(USIMM_AUTHENTICATION_CNF_STRU) + ulNafLen - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstCnfMsg)
    {
        USIMM_ERROR_LOG("USIMM_ImsAuthCnf: VOS_AllocMsg is Failed");

        return;
    }

    /*lint -e534*/
    VOS_MemSet((VOS_UINT8*)pstCnfMsg + VOS_MSG_HEAD_LENGTH,
                0,
                sizeof(USIMM_AUTHENTICATION_CNF_STRU) + ulNafLen - VOS_MSG_HEAD_LENGTH);
    /*lint +e534*/

    pstCnfMsg->stCmdResult.ulReceiverPid = pstMsg->stMsgHeader.ulSenderPid;
    pstCnfMsg->stCmdResult.enMsgName     = USIMM_AUTHENTICATION_CNF;
    pstCnfMsg->stCmdResult.enApptype     = USIMM_IMS_APP;

    /* ������ֵ����Ȩ����������� */
    pstCnfMsg->stCmdResult.ulResult      = VOS_OK;
    pstCnfMsg->stCmdResult.ulErrorCode   = VOS_OK;

    pstCnfMsg->stCmdResult.ulSendPara    = pstMsg->stMsgHeader.ulSendPara;
    pstCnfMsg->enAuthType                = pstMsg->enAuthType;

     /* ��Ȩ��� */
    pstCnfMsg->enResult                  = pstCnfInfo->enResult;

    if ((VOS_NULL_PTR != pstCnfInfo->pucIK)
        && (sizeof(pstCnfMsg->uCnfData.stTELECnf.aucIK) > pstCnfInfo->pucIK[0]))
    {
        /*lint -e534*/
        VOS_MemCpy(pstCnfMsg->uCnfData.stIMSCnf.aucIK, pstCnfInfo->pucIK, pstCnfInfo->pucIK[0] + 1);
        /*lint +e534*/
    }

    if ((VOS_NULL_PTR != pstCnfInfo->pucCK)
        && (sizeof(pstCnfMsg->uCnfData.stTELECnf.aucCK) > pstCnfInfo->pucCK[0]))
    {
        /*lint -e534*/
        VOS_MemCpy(pstCnfMsg->uCnfData.stIMSCnf.aucCK, pstCnfInfo->pucCK, pstCnfInfo->pucCK[0] + 1);
        /*lint +e534*/
    }

    if ((VOS_NULL_PTR != pstCnfInfo->pucAuts)
        && (sizeof(pstCnfMsg->uCnfData.stTELECnf.aucAuts) > pstCnfInfo->pucAuts[0]))
    {
        /*lint -e534*/
        VOS_MemCpy(pstCnfMsg->uCnfData.stIMSCnf.aucAuts, pstCnfInfo->pucAuts, pstCnfInfo->pucAuts[0] + 1);
        /*lint +e534*/
    }

    if ((VOS_NULL_PTR != pstCnfInfo->pucAutsRes)
        && (sizeof(pstCnfMsg->uCnfData.stTELECnf.aucAuthRes) > pstCnfInfo->pucAutsRes[0]))
    {
        /*lint -e534*/
        VOS_MemCpy(pstCnfMsg->uCnfData.stIMSCnf.aucAuthRes, pstCnfInfo->pucAutsRes, pstCnfInfo->pucAutsRes[0] + 1);
        /*lint +e534*/
    }

    if (VOS_NULL_PTR != pstCnfInfo->pucKs_ext_NAF)
    {
        /*lint -e534*/
        VOS_MemCpy(pstCnfMsg->uCnfData.stIMSCnf.aucKs_ext_NAF, pstCnfInfo->pucKs_ext_NAF, pstCnfInfo->pucKs_ext_NAF[0] + 1);
        /*lint +e534*/
    }

    if (VOS_NULL_PTR != pstCnfInfo->pucResponse)
    {
        /*lint -e534*/
        VOS_MemCpy(pstCnfMsg->uCnfData.stIMSCnf.aucResponse, pstCnfInfo->pucResponse, pstCnfInfo->pucResponse[0] + 1);
        /*lint +e534*/
    }

    if (VOS_NULL_PTR != pstCnfInfo->pucSessionKey)
    {
        /*lint -e534*/
        VOS_MemCpy(pstCnfMsg->uCnfData.stIMSCnf.aucSessionKey, pstCnfInfo->pucSessionKey, pstCnfInfo->pucSessionKey[0] + 1);
        /*lint +e534*/
    }

    /* �ظ���Ϣ */
    (VOS_VOID)VOS_SendMsg(WUEPS_PID_USIM, pstCnfMsg);

    return;
}
VOS_VOID USIMM_RestrictedAccessCnf(
    USIMM_RACCESS_REQ_STRU             *pstReqMsg,
    VOS_UINT32                          ulResult,
    USIMM_RACCESSCNF_INFO_STRU         *pstCnfInfo)
{
    USIMM_RACCESS_CNF_STRU  *pstUsimMsg;

    pstUsimMsg = (USIMM_RACCESS_CNF_STRU *)VOS_AllocMsg(WUEPS_PID_USIM, sizeof(USIMM_RACCESS_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstUsimMsg)
    {
        USIMM_ERROR_LOG("USIMM_RestrictedAccessCnf: VOS_AllocMsg is Failed");

        return;
    }

    pstUsimMsg->stCmdResult.ulReceiverPid                   = pstReqMsg->stMsgHeader.ulSenderPid;
    pstUsimMsg->stCmdResult.enMsgName                       = USIMM_RACCESS_CNF;
    pstUsimMsg->stCmdResult.ulResult                        = ulResult;
    pstUsimMsg->stCmdResult.ulErrorCode                     = pstCnfInfo->ulErrorCode;
    pstUsimMsg->stCmdResult.enApptype                       = pstReqMsg->stMsgHeader.enAppType;
    pstUsimMsg->stCmdResult.ulSendPara                      = pstReqMsg->stMsgHeader.ulSendPara;
    pstUsimMsg->ucSW1                                       = pstCnfInfo->ucSW1;
    pstUsimMsg->ucSW2                                       = pstCnfInfo->ucSW2;
    pstUsimMsg->usLen                                       = 0;

    /*lint -e534*/
    VOS_MemSet(pstUsimMsg->aucContent, 0, sizeof(pstUsimMsg->aucContent));
    /*lint +e534*/

    if((USIMM_API_SUCCESS == ulResult)&&(VOS_NULL_PTR != pstCnfInfo->pContent))
    {
        pstUsimMsg->usLen = pstCnfInfo->ucLen;

        /*lint -e534*/
        VOS_MemCpy(pstUsimMsg->aucContent, pstCnfInfo->pContent, pstCnfInfo->ucLen);
        /*lint +e534*/
    }

    (VOS_VOID)VOS_SendMsg(WUEPS_PID_USIM, pstUsimMsg);

    return;
}
VOS_VOID USIMM_TerminalResponseCnf(
    VOS_UINT32                          ulReceiverPid,
    VOS_UINT32                          ulErrorCode,
    VOS_UINT32                          ulSendPara,
    VOS_UINT8                           ucSW1,
    VOS_UINT8                           ucSW2)
{
    USIMM_STKTERMINALRSP_CNF_STRU  *pstUsimMsg;

    pstUsimMsg = (USIMM_STKTERMINALRSP_CNF_STRU *)VOS_AllocMsg(WUEPS_PID_USIM, sizeof(USIMM_STKTERMINALRSP_CNF_STRU)-VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstUsimMsg)
    {
        USIMM_ERROR_LOG("USIMM_TerminalResponseCnf: VOS_AllocMsg is Failed");

        return;
    }

    pstUsimMsg->stCmdResult.ulReceiverPid   = ulReceiverPid;
    pstUsimMsg->stCmdResult.enMsgName       = USIMM_STKTERMINALRSP_CNF;
    pstUsimMsg->stCmdResult.ulErrorCode     = ulErrorCode;
    pstUsimMsg->stCmdResult.ulSendPara      = ulSendPara;
    pstUsimMsg->ucSW1                       = ucSW1;
    pstUsimMsg->ucSW2                       = ucSW2;

    if(ulErrorCode != USIMM_SW_OK)
    {
        pstUsimMsg->stCmdResult.ulResult = VOS_ERR;
    }
    else
    {
        pstUsimMsg->stCmdResult.ulResult = VOS_OK;
    }

    (VOS_VOID)VOS_SendMsg(WUEPS_PID_USIM, pstUsimMsg);

    return;
}


VOS_VOID USIMM_EnvelopeCnf(
    VOS_UINT32                          ulReceiverPid,
    VOS_UINT32                          ulSendPara,
    VOS_UINT32                          ulErrorCode,
    USIMM_ENVELOPECNF_INFO_STRU        *pstCnfInfo)
{
    USIMM_STKENVELOPE_CNF_STRU  *pstUsimMsg;

    pstUsimMsg = (USIMM_STKENVELOPE_CNF_STRU *)VOS_AllocMsg(WUEPS_PID_USIM, sizeof(USIMM_STKENVELOPE_CNF_STRU)-VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstUsimMsg)
    {
        USIMM_ERROR_LOG("USIMM_EnvelopeCnf: VOS_AllocMsg is Failed");

        return;
    }

    pstUsimMsg->stCmdResult.ulReceiverPid                   = ulReceiverPid;
    pstUsimMsg->stCmdResult.enMsgName                       = USIMM_STKENVELOPE_CNF;
    pstUsimMsg->stCmdResult.ulErrorCode                     = ulErrorCode;
    pstUsimMsg->stCmdResult.ulSendPara                      = ulSendPara;
    pstUsimMsg->ucDataType                                  = pstCnfInfo->ucDataType;
    pstUsimMsg->ucSW1                                       = pstCnfInfo->ucSW1;
    pstUsimMsg->ucSW2                                       = pstCnfInfo->ucSW2;

    if (ulErrorCode != USIMM_SW_OK)
    {
        pstUsimMsg->stCmdResult.ulResult                    = VOS_ERR;
    }
    else
    {
        pstUsimMsg->stCmdResult.ulResult                    = VOS_OK;
    }

    /* ����SMS PP DOWNLOAD������������Ҫ�ظ������࣬��Ҫ�ϱ���TAF */
    if (pstCnfInfo->ulDataLen > VOS_NULL)
    {
        /*lint -e534*/
        VOS_MemCpy(pstUsimMsg->aucData, pstCnfInfo->pucData, pstCnfInfo->ulDataLen);
        /*lint +e534*/

        pstUsimMsg->ucDataLen = (VOS_UINT8)pstCnfInfo->ulDataLen;
    }
    else
    {
        pstUsimMsg->ucDataLen = 0;
    }

    (VOS_VOID)VOS_SendMsg(WUEPS_PID_USIM, pstUsimMsg);

    return;
}
VOS_VOID USIMM_SingleCmdCnf(
    VOS_UINT32                      ulReceiverPid,
    VOS_UINT32                      ulMsgName,
    VOS_UINT32                      ulSendPara,
    VOS_UINT32                      ulResult,
    USIMM_CARDAPP_ENUM_UINT32       enApptype)
{
    USIMM_SINGLECMD_CNF_STRU            *pstUsimMsg;

    pstUsimMsg = (USIMM_SINGLECMD_CNF_STRU *)VOS_AllocMsg(WUEPS_PID_USIM,
                                                         (sizeof(USIMM_SINGLECMD_CNF_STRU) - VOS_MSG_HEAD_LENGTH));

    if (VOS_NULL_PTR == pstUsimMsg)
    {
        USIMM_ERROR_LOG("USIMM_SingleCmdCnf: VOS_AllocMsg is Failed");

        return;
    }
    /*lint -e534*/
    VOS_MemSet(pstUsimMsg,0,sizeof(USIMM_SINGLECMD_CNF_STRU));
    /*lint +e534*/

    pstUsimMsg->stCmdResult.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstUsimMsg->stCmdResult.ulSenderPid         = WUEPS_PID_USIM;
    pstUsimMsg->stCmdResult.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstUsimMsg->stCmdResult.ulReceiverPid       = ulReceiverPid;
    pstUsimMsg->stCmdResult.ulLength            = sizeof(USIMM_SINGLECMD_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    pstUsimMsg->stCmdResult.enMsgName           = ulMsgName;
    pstUsimMsg->stCmdResult.ulResult            = ulResult;
    pstUsimMsg->stCmdResult.ulErrorCode         = ulResult;
    pstUsimMsg->stCmdResult.enApptype           = enApptype;
    pstUsimMsg->stCmdResult.ulSendPara          = ulSendPara;

    (VOS_VOID)VOS_SendMsg(WUEPS_PID_USIM, pstUsimMsg);

    return;
}


VOS_VOID USIMM_FDNCnf(
    USIMM_CMDHEADER_REQ_STRU           *pstMsgHeader,
    VOS_UINT32                          ulResult
)
{
    USIMM_FDNPROCESS_CNF_STRU          *pstUsimMsg;

    pstUsimMsg = (USIMM_FDNPROCESS_CNF_STRU *)VOS_AllocMsg(WUEPS_PID_USIM,
                                                          sizeof(USIMM_FDNPROCESS_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstUsimMsg)
    {
        USIMM_ERROR_LOG("USIMM_FDNCnf: VOS_AllocMsg is Failed");

        return;
    }

    pstUsimMsg->stCmdResult.ulReceiverPid   = pstMsgHeader->ulSenderPid;
    pstUsimMsg->stCmdResult.enMsgName       = USIMM_FBDNPROCESS_CNF;
    pstUsimMsg->stCmdResult.ulResult        = ulResult;
    pstUsimMsg->stCmdResult.ulErrorCode     = ulResult;
    pstUsimMsg->stCmdResult.enApptype       = pstMsgHeader->enAppType;
    pstUsimMsg->stCmdResult.ulSendPara      = pstMsgHeader->ulSendPara;
    pstUsimMsg->enFDNState                  = USIMM_CCB_GetAppFDN(pstMsgHeader->enAppType);

    (VOS_VOID)VOS_SendMsg(WUEPS_PID_USIM, pstUsimMsg);

    return;
}


VOS_VOID USIMM_SetSPBFileCnf(
    USIMM_SETMUTILFILE_REQ_STRU         *pstReqMsg,
    VOS_UINT32                          ulErrorCode)
{
    USIMM_SETMUTILFILE_CNF_STRU *pstUsimMsg = VOS_NULL_PTR;
    VOS_UINT32                  i;

    pstUsimMsg = (USIMM_SETMUTILFILE_CNF_STRU *)VOS_AllocMsg(WUEPS_PID_USIM,
                                                sizeof(USIMM_SETMUTILFILE_CNF_STRU)-VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstUsimMsg)
    {
        USIMM_ERROR_LOG("USIMM_SetSPBFileCnf: VOS_AllocMsg is Failed");

        return;
    }

    if(ulErrorCode != USIMM_SW_OK)
    {
        pstUsimMsg->stCmdResult.ulResult = VOS_ERR;
    }
    else
    {
        pstUsimMsg->stCmdResult.ulResult = VOS_OK;
    }

    pstUsimMsg->stCmdResult.ulReceiverPid   = pstReqMsg->stMsgHeader.ulSenderPid;
    pstUsimMsg->stCmdResult.enMsgName       = USIMM_SETMUTILFILE_CNF;
    pstUsimMsg->stCmdResult.ulErrorCode     = ulErrorCode;
    pstUsimMsg->stCmdResult.enApptype       = pstReqMsg->stMsgHeader.enAppType;

    pstUsimMsg->ucFileNum                   = (VOS_UINT8)pstReqMsg->ulFileCount;

    if (VOS_OK == pstUsimMsg->stCmdResult.ulResult)
    {
        for (i = 0; i < pstReqMsg->ulFileCount; i++)
        {
            if (USIMM_EF_FILE != USIMM_GetFileIDFromStr(&(pstReqMsg->stFileData[i].stFilePath),
                                                                    &(pstUsimMsg->ausEfId[i])))
            {
                break;
            }

            pstUsimMsg->aucRecordNum[i] = pstReqMsg->stFileData[i].ucRecordNum;
            pstUsimMsg->ausEfLen[i]     = pstReqMsg->stFileData[i].usDataLen;
        }
    }

    (VOS_VOID)VOS_SendMsg(WUEPS_PID_USIM, pstUsimMsg);

    return;
}


VOS_VOID USIMM_SearchHandleCnf(
    USIMM_SEARCHFILE_REQ_STRU           *pstMsg,
    VOS_UINT32                          ulErrorCode,
    USIMM_SEARCHCNF_INFO_STRU           *pstCnfInfo)
{
    USIMM_SEARCHFILE_CNF_STRU     *pUsimMsg;

    pUsimMsg = (USIMM_SEARCHFILE_CNF_STRU *)VOS_AllocMsg(WUEPS_PID_USIM,
                            (sizeof(USIMM_SEARCHFILE_CNF_STRU) - VOS_MSG_HEAD_LENGTH) + pstCnfInfo->ulLen);

    if (VOS_NULL_PTR == pUsimMsg)
    {
        USIMM_ERROR_LOG("USIMM_SearchHandleCnf: VOS_AllocMsg is Failed");

        return;
    }

    pUsimMsg->stCmdResult.ulReceiverPid = pstMsg->stMsgHeader.ulSenderPid;
    pUsimMsg->stCmdResult.enMsgName     = USIMM_SEARCHFILE_CNF;
    pUsimMsg->stCmdResult.ulErrorCode   = ulErrorCode;
    pUsimMsg->usTotalRecNum             = pstCnfInfo->usTotalRecNum;
    pUsimMsg->usDataLen                 = 0;

    if (USIMM_SW_OK == ulErrorCode)
    {
        pUsimMsg->stCmdResult.ulResult  = VOS_OK;
    }
    else
    {
        pUsimMsg->stCmdResult.ulResult  = ulErrorCode;
    }

    /*lint -e534*/
    VOS_MemCpy(&pUsimMsg->stFilePath, &pstMsg->stFilePath, sizeof(pstMsg->stFilePath));
    /*lint +e534*/

    if ((VOS_NULL_PTR != pstCnfInfo->pucData) && (pstCnfInfo->ulLen <= 255))
    {
        /*lint -e534 */
        VOS_MemCpy(pUsimMsg->aucData, pstCnfInfo->pucData, pstCnfInfo->ulLen);
        /*lint +e534 */

        pUsimMsg->usDataLen = (VOS_UINT8)pstCnfInfo->ulLen;
    }

    (VOS_VOID)VOS_SendMsg(WUEPS_PID_USIM, pUsimMsg);

    return;
}


VOS_VOID USIMM_CardStatusInd(
    VOS_UINT32                          ulReceiverPid)
{
    USIMM_CARDSTATUS_IND_STRU          *pstUsimMsg;

    pstUsimMsg = (USIMM_CARDSTATUS_IND_STRU *)VOS_AllocMsg(WUEPS_PID_USIM, sizeof(USIMM_CARDSTATUS_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstUsimMsg )
    {
        USIMM_ERROR_LOG("USIMM_CardStatusInd: VOS_AllocMsg is Failed");

        return;
    }

    pstUsimMsg->ulReceiverPid = ulReceiverPid;
    pstUsimMsg->ulMsgName     = USIMM_CARDSTATUS_IND;     /* ������Ϣ���� */
    pstUsimMsg->enPhyCardType = USIMM_CCB_GetCardType();

    pstUsimMsg->stUsimSimInfo.enCardService                 = USIMM_CCB_GetAppService(USIMM_GUTL_APP);
    pstUsimMsg->stUsimSimInfo.enCardType                    = USIMM_COMM_CardAppToType(USIMM_GUTL_APP);
    pstUsimMsg->stCsimUimInfo.enCardService                 = USIMM_CCB_GetAppService(USIMM_CDMA_APP);
    pstUsimMsg->stCsimUimInfo.enCardType                    = USIMM_COMM_CardAppToType(USIMM_CDMA_APP);
    pstUsimMsg->stIsimInfo.enCardService                    = USIMM_CCB_GetAppService(USIMM_IMS_APP);
    pstUsimMsg->stIsimInfo.enCardType                       = USIMM_COMM_CardAppToType(USIMM_IMS_APP);

    (VOS_VOID)VOS_SendMsg(pstUsimMsg->ulSenderPid, pstUsimMsg);

    /*��״̬�����п�����������(���ﱣ����ԭ�д����߼�һ��)*/
    if(USIMM_CARD_SERVIC_AVAILABLE != USIMM_CCB_GetAppService(USIMM_GUTL_APP))
    {
        USIMM_SaveLogFile();
    }

    g_stUSIMMLogData.enLogState = USIMM_NO_NEED_LOG;/*�ϱ���״̬�Ͳ���Ҫ��¼log*/

    return;
}

/*****************************************************************************
�� �� ��  : USIMM_CardTimeOutEventInd
��������  : ����ʱ�¼���ʱ����״̬�ϱ�
�������  : ��
�������  : ��
�� �� ֵ  : VOS_ERR
           VOS_OK
�޶���¼  :
1. ��    ��   : 2015��5��15��
   ��    ��   : zhuli
   �޸�����   : Creat
*****************************************************************************/
VOS_VOID USIMM_CardTimeOutEventInd(VOS_VOID)
{
    USIMM_CARDTIMEOUT_IND_STRU          *pstUsimMsg;

    if ((VOS_TRUE == USIMM_GetTimeOutFlag())
        &&(VOS_TRUE == g_stUsimmFeatureCfg.unCfg.stFeatureCfg.ulTimerOutInd))
    {
        pstUsimMsg = (USIMM_CARDTIMEOUT_IND_STRU *)VOS_AllocMsg(WUEPS_PID_USIM,
                                        sizeof(USIMM_CARDTIMEOUT_IND_STRU) - VOS_MSG_HEAD_LENGTH);

        if (VOS_NULL_PTR == pstUsimMsg)
        {
            USIMM_ERROR_LOG("USIMM_CardTimeOutEventInd: VOS_AllocMsg is Failed");

            return;
        }

        pstUsimMsg->stIndHdr.ulReceiverPid = MAPS_PIH_PID;
        pstUsimMsg->stIndHdr.enMsgName     = USIMM_CARDTIMEOUT_IND;     /* ������Ϣ���� */

        (VOS_VOID)VOS_SendMsg(WUEPS_PID_USIM, pstUsimMsg);

        return;
    }

    USIMM_SetTimeOutFlag(VOS_FALSE);

    return;
}

/*2�׶ο���ʹ��*/

VOS_VOID USIMM_SatDataInd(
    VOS_UINT8                           ucCmdType,
    VOS_UINT16                          usDataLen,
    VOS_UINT8                           *pucData)
{
    USIMM_STKDATA_IND_STRU             *pstUsimMsg;

    pstUsimMsg = (USIMM_STKDATA_IND_STRU *)VOS_AllocMsg(WUEPS_PID_USIM, sizeof(USIMM_STKDATA_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstUsimMsg)
    {
        return;
    }

    pstUsimMsg->stIndHdr.ulReceiverPid  = MAPS_STK_PID;
    pstUsimMsg->stIndHdr.enMsgName      = USIMM_STKDATA_IND;
    pstUsimMsg->usLen                   = usDataLen;
    pstUsimMsg->ucCmdType               = ucCmdType;

    /*lint -e534*/
    VOS_MemCpy(pstUsimMsg->aucContent, pucData, usDataLen);
    /*lint +e534*/

    (VOS_VOID)VOS_SendMsg(WUEPS_PID_USIM, pstUsimMsg);

    return;
}

#if (FEATURE_VSIM == FEATURE_ON)

VOS_VOID USIMM_VsimReDhNegotiateInd(VOS_VOID)
{
    USIMM_VSIM_RDH_IND_STRU         *pstMsg;

    pstMsg = (USIMM_VSIM_RDH_IND_STRU *)VOS_AllocMsg(WUEPS_PID_USIM,
                                    sizeof(USIMM_VSIM_RDH_IND_STRU)-VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    pstMsg->stIndHdr.ulReceiverPid = MAPS_PIH_PID;
    pstMsg->stIndHdr.enMsgName     = USIMM_VSIM_RDH_IND;

    (VOS_VOID)VOS_SendMsg(WUEPS_PID_USIM, pstMsg);

    return;
}
#endif

VOS_VOID USIMM_EccNumberInd(
    VOS_UINT8                           ucEccType,
    VOS_UINT16                          usEfLen,
    VOS_UINT8                           ucRecordNum,
    VOS_UINT8                           *pucData)
{

    USIMM_ECCNUMBER_IND_STRU        *pstUsimMsg;

    pstUsimMsg = (USIMM_ECCNUMBER_IND_STRU *)VOS_AllocMsg(WUEPS_PID_USIM,
                            (sizeof(USIMM_ECCNUMBER_IND_STRU)-VOS_MSG_HEAD_LENGTH)+usEfLen);

    if (VOS_NULL_PTR == pstUsimMsg)
    {
        return;
    }

    pstUsimMsg->stIndHdr.ulReceiverPid  = MAPS_PB_PID;                                           /*��дPB��PID*/
    pstUsimMsg->stIndHdr.enMsgName      = USIMM_ECCNUMBER_IND;
    pstUsimMsg->ucEccType               = ucEccType;
    pstUsimMsg->ucRecordNum             = ucRecordNum;
    pstUsimMsg->usFileSize              = usEfLen;

    if(0 != usEfLen)
    {
        /*lint -e534*/
        VOS_MemCpy(pstUsimMsg->ucContent, pucData, usEfLen);
        /*lint +e534*/
    }

    (VOS_VOID)VOS_SendMsg(WUEPS_PID_USIM, pstUsimMsg);

    return;
}

/*****************************************************************************
�� �� ��  :USIMM_XeccNumberInd
��������  :�������к����ϱ�
�������  :usEfLen:�ļ�����
           pucData��������
�������  :��
�� �� ֵ  :��
�޶���¼  :
1. ��    ��   : 2015��06��11��
   ��    ��   : h00300778
   �޸�����   : Creat
*****************************************************************************/
VOS_VOID USIMM_XeccNumberInd(
    VOS_UINT16                          usEfLen,
    VOS_UINT8                          *pucData)
{

    USIMM_XECCNUMBER_IND_STRU        *pstUsimMsg;

    pstUsimMsg = (USIMM_XECCNUMBER_IND_STRU *)VOS_AllocMsg(WUEPS_PID_USIM,
                                                           (sizeof(USIMM_XECCNUMBER_IND_STRU)-VOS_MSG_HEAD_LENGTH)+usEfLen);

    if (VOS_NULL_PTR == pstUsimMsg)
    {
        return;
    }

    pstUsimMsg->stIndHdr.ulReceiverPid  = MAPS_PB_PID;                                           /*��дPB��PID*/
    pstUsimMsg->stIndHdr.enMsgName      = USIMM_XECCNUMBER_IND;
    pstUsimMsg->usFileSize              = usEfLen;

    if (0 != usEfLen)
    {
        /*lint -e534*/
        VOS_MemCpy(pstUsimMsg->ucContent, pucData, usEfLen);
        /*lint +e534*/
    }

    (VOS_VOID)VOS_SendMsg(WUEPS_PID_USIM, pstUsimMsg);

    return;
}
VOS_VOID USIMM_OpenChannelCnf(
    VOS_UINT32                          ulReceiverPid,
    VOS_UINT32                          ulSendPara,
    VOS_UINT32                          ulResult,
    VOS_UINT32                          ulErrCode,
    VOS_UINT8                           ucChannelNo)
{
    USIMM_OPENCHANNEL_CNF_STRU      *pstUsimMsg = VOS_NULL_PTR;

    pstUsimMsg = (USIMM_OPENCHANNEL_CNF_STRU *)VOS_AllocMsg(WUEPS_PID_USIM,
                                                            sizeof(USIMM_OPENCHANNEL_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstUsimMsg)
    {
        USIMM_ERROR_LOG("USIMM_OpenChannelCnf: VOS_AllocMsg is Failed");

        return;
    }

    pstUsimMsg->stCmdResult.ulReceiverPid       = ulReceiverPid;
    pstUsimMsg->stCmdResult.enMsgName           = USIMM_OPENCHANNEL_CNF;
    pstUsimMsg->stCmdResult.ulResult            = ulResult;
    pstUsimMsg->stCmdResult.ulErrorCode         = ulErrCode;
    pstUsimMsg->stCmdResult.ulSendPara          = ulSendPara;

    if (VOS_OK == ulResult)
    {
        pstUsimMsg->ulSessionID                 = VOS_NULL;
        pstUsimMsg->stCmdResult.enApptype       = USIMM_CCB_GetAppTypeByCH(ucChannelNo);
        pstUsimMsg->ucChannelID                 = ucChannelNo;
    }
    else
    {
        pstUsimMsg->ulSessionID                 = 0;
        pstUsimMsg->stCmdResult.enApptype       = 0;
        pstUsimMsg->ucChannelID                 = 0;
    }

    (VOS_VOID)VOS_SendMsg(WUEPS_PID_USIM, pstUsimMsg);

    return;
}


VOS_VOID USIMM_CloseChannelCnf(
    VOS_UINT32                          ulReceiverPid,
    VOS_UINT32                          ulSendPara,
    VOS_UINT32                          ulResult,
    VOS_UINT32                          ulErrCode)
{
    USIMM_CLOSECHANNEL_CNF_STRU        *pstUsimMsg = VOS_NULL_PTR;

    pstUsimMsg = (USIMM_CLOSECHANNEL_CNF_STRU *)VOS_AllocMsg(WUEPS_PID_USIM,
                                                             sizeof(USIMM_CLOSECHANNEL_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstUsimMsg)
    {
        USIMM_ERROR_LOG("USIMM_CloseChannelCnf: VOS_AllocMsg is Failed");

        return;
    }

    pstUsimMsg->stCmdResult.ulReceiverPid                   = ulReceiverPid;
    pstUsimMsg->stCmdResult.enMsgName                       = USIMM_CLOSECHANNEL_CNF;
    pstUsimMsg->stCmdResult.ulResult                        = ulResult;
    pstUsimMsg->stCmdResult.ulErrorCode                     = ulErrCode;
    pstUsimMsg->stCmdResult.ulSendPara                      = ulSendPara;

    (VOS_VOID)VOS_SendMsg(WUEPS_PID_USIM, pstUsimMsg);

    return;
}

/*****************************************************************************
�� �� ��  :USIMM_SendTPDUCnf
��������  :Send TPDU��Ϣ�ظ�
�������  :ulReceiverPid:������ϢPID
           ulResult:�������
           ulErrCode:������
           pstDataCnf:Send TPDU��Ϣ�ظ�����
�������  :��
�� �� ֵ  :��

�޶���¼  :
1. ��    ��   : 2014��1��15��
   ��    ��   : zhuli
   �޸�����   : Creat
*****************************************************************************/
VOS_VOID USIMM_SendTPDUCnf(
    VOS_UINT32                          ulReceiverPid,
    VOS_UINT32                          ulSendPara,
    VOS_UINT32                          ulResult,
    USIMM_SENDTPDU_CNFINFO_STRU        *pstDataCnf,
    USIMM_CURFILEINFO_ST               *pstCurFile)
{
    USIMM_SENDTPDUDATA_CNF_STRU        *pstUsimMsg = VOS_NULL_PTR;
    VOS_UINT8                           aucPath[USIMM_MAX_PATH_LEN*2];
    VOS_UINT32                          ulPathLen;
    VOS_UINT32                          i;

    pstUsimMsg = (USIMM_SENDTPDUDATA_CNF_STRU *)VOS_AllocMsg(WUEPS_PID_USIM,
                                               sizeof(USIMM_SENDTPDUDATA_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstUsimMsg)
    {
        USIMM_ERROR_LOG("USIMM_AccessChannelCnf: VOS_AllocMsg is Failed");

        return;
    }

    pstUsimMsg->stCmdResult.ulReceiverPid           =   ulReceiverPid;
    pstUsimMsg->stCmdResult.enMsgName               =   USIMM_SENDTPDUDATA_CNF;
    pstUsimMsg->stCmdResult.ulResult                =   ulResult;
    pstUsimMsg->stCmdResult.ulErrorCode             =   ulResult;
    pstUsimMsg->stCmdResult.ulSendPara              =   ulSendPara;

    pstUsimMsg->stRspData.ucSW1                     =   pstDataCnf->ucSw1;
    pstUsimMsg->stRspData.ucSW2                     =   pstDataCnf->ucSw2;
    pstUsimMsg->stRspData.ulDataLen                 =   pstDataCnf->usDataLen;

    if (VOS_NULL != pstDataCnf->usDataLen)
    {
        /*lint -e534*/
        VOS_MemCpy(pstUsimMsg->stRspData.aucRspData, pstDataCnf->pucData, pstDataCnf->usDataLen);
        /*lint +e534*/
    }

    if (VOS_NULL_PTR != pstDataCnf->pucTPDUHead)
    {
        /*lint -e534*/
        VOS_MemCpy(pstUsimMsg->stRspData.aucInputCmd, pstDataCnf->pucTPDUHead, USIMM_TPDU_HEAD_LEN);
        /*lint +e534*/
    }

    if ((VOS_NULL_PTR != pstCurFile)&&(VOS_NULL != pstCurFile->usFilePathLen))
    {
        for (i = 0; i < pstCurFile->usFilePathLen; i++)
        {
            aucPath[i*2] = (VOS_UINT8)((pstCurFile->ausFilePath[i]>>0x08)&0x00FF);

            aucPath[(i*2)+1] = (VOS_UINT8)(pstCurFile->ausFilePath[i]&0x00FF);
        }

        ulPathLen = (VOS_UINT8)(pstCurFile->usFilePathLen * sizeof(VOS_UINT16));

        USIMM_ChangePathToAsciiString(aucPath,
                                      (VOS_UINT8)ulPathLen,
                                      &(pstUsimMsg->stFilePath));
    }

    (VOS_VOID)VOS_SendMsg(WUEPS_PID_USIM, pstUsimMsg);

    return;

}

/*****************************************************************************
�� �� ��  :USIMM_SendTPDUCnf
��������  :Send TPDU��Ϣ�ظ�
�������  :ulReceiverPid:������ϢPID
           ulResult:�������
           ulErrCode:������
           pstDataCnf:Send TPDU��Ϣ�ظ�����
�������  :��
�� �� ֵ  :��

�޶���¼  :
1. ��    ��   : 2014��1��15��
   ��    ��   : zhuli
   �޸�����   : Creat
*****************************************************************************/
VOS_VOID USIMM_CdmaAuthCnf(
    USIMM_AUTHENTICATION_REQ_STRU      *pstMsg,
    USIMM_CDMA_AUTH_INFO_STRU          *pstCnfInfo)
{
    USIMM_AUTHENTICATION_CNF_STRU      *pstCnfMsg;

    /* ������Ϣ�ڴ�  */
    pstCnfMsg = (USIMM_AUTHENTICATION_CNF_STRU *)VOS_AllocMsg(WUEPS_PID_USIM, sizeof(USIMM_AUTHENTICATION_CNF_STRU)-VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstCnfMsg)
    {
        USIMM_ERROR_LOG("USIMM_CdmaAuthCnf: VOS_AllocMsg is Failed");

        return;
    }

    /*lint -e534*/
    VOS_MemSet((VOS_UINT8*)pstCnfMsg + VOS_MSG_HEAD_LENGTH, 0, pstCnfMsg->stCmdResult.ulLength);
    /*lint +e534*/

    pstCnfMsg->stCmdResult.ulReceiverPid= pstMsg->stMsgHeader.ulSenderPid;
    pstCnfMsg->stCmdResult.enMsgName    = USIMM_AUTHENTICATION_CNF;
    pstCnfMsg->stCmdResult.enApptype    = USIMM_CDMA_APP;

    /* ������ֵ����Ȩ����������� */
    pstCnfMsg->stCmdResult.ulResult     = VOS_OK;
    pstCnfMsg->stCmdResult.ulErrorCode  = VOS_OK;

    pstCnfMsg->stCmdResult.ulSendPara   = pstMsg->stMsgHeader.ulSendPara;
    pstCnfMsg->enAuthType               = pstMsg->enAuthType;

     /* ��Ȩ��� */
    pstCnfMsg->enResult                 = pstCnfInfo->enResult;

    if (USIMM_RUNCAVE_AUTH == pstMsg->enAuthType)
    {
        if (VOS_NULL_PTR != pstCnfInfo->pucAuthr)
        {
            /*lint -e534*/
            VOS_MemCpy(pstCnfMsg->uCnfData.stRunCaveCnf.aucAuthr, pstCnfInfo->pucAuthr, sizeof(pstCnfMsg->uCnfData.stRunCaveCnf.aucAuthr));
            /*lint +e534*/
        }
    }

    if ((USIMM_3G_AUTH == pstMsg->enAuthType)
     || (USIMM_EAP_AUTH == pstMsg->enAuthType))
    {
        if (VOS_NULL_PTR != pstCnfInfo->pucIK)
        {
            pstCnfMsg->uCnfData.stTELECnf.aucIK[0] = USIMM_AUTH_IK_LEN;

            /*lint -e534*/
            VOS_MemCpy(&pstCnfMsg->uCnfData.stTELECnf.aucIK[1], pstCnfInfo->pucIK, pstCnfMsg->uCnfData.stTELECnf.aucIK[0]);
            /*lint +e534*/
        }

        if (VOS_NULL_PTR != pstCnfInfo->pucCK)
        {
            pstCnfMsg->uCnfData.stTELECnf.aucCK[0] = USIMM_AUTH_CK_LEN;

            /*lint -e534*/
            VOS_MemCpy(&pstCnfMsg->uCnfData.stTELECnf.aucCK[1], pstCnfInfo->pucCK, pstCnfMsg->uCnfData.stTELECnf.aucCK[0]);
            /*lint +e534*/
        }

        if (VOS_NULL_PTR != pstCnfInfo->pucAuthRes)
        {
            if (pstCnfInfo->pucAuthRes[0] >= USIMM_AUTH_RESSPACELEN)
            {
                pstCnfMsg->uCnfData.stTELECnf.aucAuthRes[0] = USIMM_AUTH_RESSPACELEN -1;
            }
            else
            {
                pstCnfMsg->uCnfData.stTELECnf.aucAuthRes[0] = pstCnfInfo->pucAuthRes[0];
            }

            /*lint -e534*/
            VOS_MemCpy(&pstCnfMsg->uCnfData.stTELECnf.aucAuthRes[1], pstCnfInfo->pucAuthRes + 1, pstCnfMsg->uCnfData.stTELECnf.aucAuthRes[0]);
            /*lint +e534*/
        }

        if (VOS_NULL_PTR != pstCnfInfo->pucAuts)
        {
            pstCnfMsg->uCnfData.stTELECnf.aucAuts[0] = USIMM_AUTH_AUTHSPACELEN - 1;

            /*lint -e534*/
            VOS_MemCpy(&pstCnfMsg->uCnfData.stTELECnf.aucAuts[1], pstCnfInfo->pucAuts, pstCnfMsg->uCnfData.stTELECnf.aucAuts[0]);
            /*lint +e534*/
        }
    }

    /* �ظ���Ϣ */
    (VOS_VOID)VOS_SendMsg(WUEPS_PID_USIM, pstCnfMsg);

    return;
}

/*****************************************************************************
�� �� ��  :USIMM_SendTPDUCnf
��������  :Send TPDU��Ϣ�ظ�
�������  :ulReceiverPid:������ϢPID
           ulResult:�������
           ulErrCode:������
           pstDataCnf:Send TPDU��Ϣ�ظ�����
�������  :��
�� �� ֵ  :��

�޶���¼  :
1. ��    ��   : 2014��1��15��
   ��    ��   : zhuli
   �޸�����   : Creat
*****************************************************************************/
VOS_VOID USIMM_BSChallengeCnf(
    USIMM_CMDHEADER_REQ_STRU           *pstReqMsg,
    VOS_UINT32                          ulResult,
    VOS_UINT32                          ulErrCode,
    VOS_UINT32                          ulDataLen,
    VOS_UINT8                          *pucRandBs)
{
    USIMM_BSCHALLENGE_CNF_STRU       *pstUsimMsg;

    pstUsimMsg = (USIMM_BSCHALLENGE_CNF_STRU *)VOS_AllocMsg(WUEPS_PID_USIM,
                                                            ulDataLen + sizeof(USIMM_BSCHALLENGE_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstUsimMsg)
    {
        USIMM_ERROR_LOG("USIMM_BSChallengeCnf: VOS_AllocMsg is Failed");

        return;
    }

    pstUsimMsg->stCmdResult.ulReceiverPid                   = pstReqMsg->ulSenderPid;
    pstUsimMsg->stCmdResult.enApptype                       = pstReqMsg->enAppType;
    pstUsimMsg->stCmdResult.ulSendPara                      = pstReqMsg->ulSendPara;
    pstUsimMsg->stCmdResult.enMsgName                       = USIMM_BSCHALLENGE_CNF;
    pstUsimMsg->stCmdResult.ulResult                        = ulResult;
    pstUsimMsg->stCmdResult.ulErrorCode                     = ulErrCode;
    pstUsimMsg->ulDataLen                                   = ulDataLen;

    if (VOS_NULL_PTR != pucRandBs)
    {
        /*lint -e534*/
        VOS_MemCpy(pstUsimMsg->aucData, pucRandBs, ulDataLen);
        /*lint +e534*/
    }

    (VOS_VOID)VOS_SendMsg(WUEPS_PID_USIM, pstUsimMsg);

    return;
}

/*****************************************************************************
�� �� ��  :USIMM_GenerateKeyVpmCnf
��������  :Send TPDU��Ϣ�ظ�
�������  :ulReceiverPid:������ϢPID
           ulResult:�������
           ulErrCode:������
           pstDataCnf:Send TPDU��Ϣ�ظ�����
�������  :��
�� �� ֵ  :��

�޶���¼  :
1. ��    ��   : 2014��1��15��
   ��    ��   : zhuli
   �޸�����   : Creat
*****************************************************************************/
VOS_VOID USIMM_GenerateKeyVpmCnf(
    USIMM_GENERATE_KEYVPM_REQ_STRU     *pstReqMsg,
    VOS_UINT32                          ulResult,
    VOS_UINT32                          ulErrCode,
    VOS_UINT32                          ulVpmLen,
    VOS_UINT8                          *pucVpm,
    VOS_UINT8                          *pucKey)
{
    USIMM_GENERATE_KEYVPM_CNF_STRU     *pstUsimMsg;

    pstUsimMsg = (USIMM_GENERATE_KEYVPM_CNF_STRU *)VOS_AllocMsg(WUEPS_PID_USIM,
                                                                ulVpmLen + sizeof(USIMM_GENERATE_KEYVPM_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstUsimMsg)
    {
        USIMM_ERROR_LOG("USIMM_GenerateKeyVpmCnf: VOS_AllocMsg is Failed");

        return;
    }

    pstUsimMsg->stCmdResult.ulReceiverPid                   = pstReqMsg->stMsgHeader.ulSenderPid;
    pstUsimMsg->stCmdResult.enApptype                       = pstReqMsg->stMsgHeader.enAppType;
    pstUsimMsg->stCmdResult.ulSendPara                      = pstReqMsg->stMsgHeader.ulSendPara;
    pstUsimMsg->stCmdResult.enMsgName                       = USIMM_GENERATE_KEYVPM_CNF;
    pstUsimMsg->stCmdResult.ulResult                        = ulResult;
    pstUsimMsg->stCmdResult.ulErrorCode                     = ulErrCode;

    /*lint -e534*/
    VOS_MemCpy(pstUsimMsg->aucKey, pucKey, sizeof(pstUsimMsg->aucKey));
    /*lint +e534*/

    if (0 != ulVpmLen)
    {
        /*lint -e534*/
        VOS_MemCpy(pstUsimMsg->aucVPM, pucVpm, ulVpmLen);
        /*lint +e534*/

        pstUsimMsg->ulVPMLen = ulVpmLen;
    }

    (VOS_VOID)VOS_SendMsg(WUEPS_PID_USIM, pstUsimMsg);

    return;
}

/*****************************************************************************
�� �� ��  :USIMM_CdmaSepcAuthCnf
��������  :Spec Auth��Ϣ�ظ�
�������  :pstReqMsg:������ϢPID
           enAuthType:��Ȩ����
           ulErrCode:������
           uAuthCnf: ��Ϣ�ظ�����
�������  :��
�� �� ֵ  :��

�޶���¼  :
1. ��    ��   : 2014��1��15��
   ��    ��   : zhuli
   �޸�����   : Creat
*****************************************************************************/
VOS_VOID USIMM_CdmaSepcAuthCnf(
    USIMM_CMDHEADER_REQ_STRU           *pstReqMsg,
    VOS_UINT32                          ulErrCode,
    USIMM_CDMASPEC_AUTHTYPE_ENUM_UINT32 enAuthType,
    USIMM_CDMASPECAUTH_DATA_UNION      *puAuthCnf)
{
    USIMM_CDMASPECAUTH_CNF_STRU         *pstUsimMsg;

    pstUsimMsg = (USIMM_CDMASPECAUTH_CNF_STRU *)VOS_AllocMsg(WUEPS_PID_USIM,
                                                         sizeof(USIMM_CDMASPECAUTH_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstUsimMsg)
    {
        USIMM_ERROR_LOG("USIMM_CdmaSepcAuthCnf: VOS_AllocMsg is Failed");

        return;
    }

    pstUsimMsg->stCmdResult.ulReceiverPid   = pstReqMsg->ulSenderPid;
    pstUsimMsg->stCmdResult.enApptype       = pstReqMsg->enAppType;
    pstUsimMsg->stCmdResult.ulSendPara      = pstReqMsg->ulSendPara;
    pstUsimMsg->stCmdResult.enMsgName       = USIMM_CDMASPECAUTH_CNF;
    pstUsimMsg->stCmdResult.ulErrorCode     = ulErrCode;

    if (VOS_OK == ulErrCode)
    {
        pstUsimMsg->stCmdResult.ulResult    = VOS_OK;
    }
    else
    {
        pstUsimMsg->stCmdResult.ulResult    = VOS_ERR;
    }

    pstUsimMsg->enAuthType                  = enAuthType;

    if (VOS_NULL_PTR != puAuthCnf)
    {
        (VOS_VOID)VOS_MemCpy(&pstUsimMsg->uAuthCnf,
                                puAuthCnf,
                                sizeof(USIMM_CDMASPECAUTH_DATA_UNION));
    }
    else
    {
        (VOS_VOID)VOS_MemSet(&pstUsimMsg->uAuthCnf,
                                0,
                                sizeof(USIMM_CDMASPECAUTH_DATA_UNION));
    }

    (VOS_VOID)VOS_SendMsg(WUEPS_PID_USIM, pstUsimMsg);

    return;
}


#else



VOS_VOID USIMM_MaxRecordNumCnf(USIMM_QUERYFILE_REQ_STRU  *pstNewMsg,
                                            VOS_UINT32                  ulErrorCode,
                                           USIMM_FILECNF_INFO_STRU      *pstCnfInfo)
{
    USIMM_QUERYFILE_CNF_STRU           *pstUsimMsg;

    pstUsimMsg = (USIMM_QUERYFILE_CNF_STRU*)VOS_AllocMsg(WUEPS_PID_USIM,
                                                         sizeof(USIMM_QUERYFILE_CNF_STRU)-VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstUsimMsg)
    {
        USIMM_ERROR_LOG("USIMM_MaxRecordNumCnf: VOS_AllocMsg is Failed");

        return;
    }

    pstUsimMsg->stCmdResult.ulReceiverPid       = pstNewMsg->stMsgHeader.ulSenderPid;
    pstUsimMsg->stCmdResult.ulErrorCode         = ulErrorCode;
    pstUsimMsg->stCmdResult.enMsgName           = USIMM_QUERYFILE_CNF;
    pstUsimMsg->ucRecordNum                     = pstCnfInfo->ucRecordNum;
    pstUsimMsg->ucRecordLen                     = pstCnfInfo->ucRecordLen;
    pstUsimMsg->enFileStatus                    = (USIMM_EFSTATUS_ENUM_UINT8)pstCnfInfo->ulFileStatus;
    pstUsimMsg->enFileRWFlag                    = (VOS_UINT8)pstCnfInfo->ulFileReadUpdateFlag;

    if (ulErrorCode != USIMM_SW_OK)
    {
        pstUsimMsg->stCmdResult.ulResult  = VOS_ERR;
    }
    else
    {
        pstUsimMsg->stCmdResult.ulResult  = VOS_OK;
    }

    /*lint -e534*/
    VOS_MemCpy(&pstUsimMsg->stFilePath, &pstNewMsg->stFilePath, sizeof(pstNewMsg->stFilePath));
    /*lint +e534*/

    (VOS_VOID)VOS_SendMsg(WUEPS_PID_USIM, pstUsimMsg);

    return;
}


VOS_VOID USIMM_PinHandleCnf(
    USIMM_PINHANDLE_REQ_STRU           *pstReqMsg,
    VOS_UINT32                          ulResult,
    USIMM_PIN_INFO_STRU                *pstPINinfo)
{
    USIMM_PINHANDLE_CNF_STRU           *pstUsimMsg;

    pstUsimMsg = (USIMM_PINHANDLE_CNF_STRU *)VOS_AllocMsg(WUEPS_PID_USIM, sizeof(USIMM_PINHANDLE_CNF_STRU)-VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstUsimMsg)
    {
        USIMM_ERROR_LOG("USIMM_PinHandleCnf: VOS_AllocMsg is Failed");

        return;
    }

    pstUsimMsg->stCmdResult.ulReceiverPid                   = pstReqMsg->stMsgHeader.ulSenderPid;
    pstUsimMsg->stCmdResult.enMsgName                       = USIMM_PINHANDLE_CNF;
    pstUsimMsg->stCmdResult.ulResult                        = ulResult;
    pstUsimMsg->stCmdResult.ulErrorCode                     = ulResult;
    pstUsimMsg->stCmdResult.enApptype                       = pstReqMsg->stMsgHeader.enAppType;
    pstUsimMsg->stCmdResult.ulSendPara                      = pstReqMsg->stMsgHeader.ulSendPara;
    pstUsimMsg->enCmdType                                   = pstReqMsg->enCmdType;
    pstUsimMsg->enPinType                                   = pstReqMsg->enPINType;

    /*lint -e534*/
    VOS_MemCpy(&pstUsimMsg->stPinInfo, pstPINinfo, sizeof(USIMM_PIN_INFO_STRU));
    /*lint +e534*/

    (VOS_VOID)VOS_SendMsg(WUEPS_PID_USIM, pstUsimMsg);

    return;
}


VOS_VOID USIMM_SetFileCnf(USIMM_UPDATEFILE_REQ_STRU  *pstNewMsg,
                                VOS_UINT32                   ulErrorCode,
                                USIMM_SETCNF_INFO_STRU      *pstCnfInfo)
{
    USIMM_UPDATEFILE_CNF_STRU          *pstUsimMsg;
    VOS_UINT32                          ulResult;

    if (ulErrorCode != USIMM_SW_OK)
    {
        ulResult = VOS_ERR;
    }
    else
    {
        ulResult = VOS_OK;
    }

    pstUsimMsg = (USIMM_UPDATEFILE_CNF_STRU*)VOS_AllocMsg(WUEPS_PID_USIM, sizeof(USIMM_UPDATEFILE_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstUsimMsg)
    {
        return;
    }

    pstUsimMsg->stCmdResult.enMsgName       = USIMM_UPDATEFILE_CNF;
    pstUsimMsg->stCmdResult.ulReceiverPid   = pstNewMsg->stMsgHeader.ulSenderPid;
    pstUsimMsg->stCmdResult.ulResult        = ulResult;
    pstUsimMsg->stCmdResult.ulErrorCode     = ulErrorCode;
    pstUsimMsg->stCmdResult.ulSendPara      = pstNewMsg->stMsgHeader.ulSendPara;
    pstUsimMsg->stCmdResult.enApptype       = pstNewMsg->stMsgHeader.enAppType;
    pstUsimMsg->usEFLen                     = pstCnfInfo->usEFLen;
    pstUsimMsg->ucRecordNum                 = pstCnfInfo->ucRecordNum;

    /*lint -e534*/
    VOS_MemCpy(&pstUsimMsg->stFilePath, &pstNewMsg->stFilePath, sizeof(pstNewMsg->stFilePath));
    /*lint +e534*/

    (VOS_VOID)VOS_SendMsg(WUEPS_PID_USIM, pstUsimMsg);

    return;
}


VOS_VOID USIMM_GetFileCnf(
    USIMM_READFILE_REQ_STRU            *pstNewMsg,
    VOS_UINT32                          ulErrorCode,
    USIMM_GETCNF_INFO_STRU             *pstCnfInfo
)
{
    USIMM_READFILE_CNF_STRU            *pstUsimMsg;
    VOS_UINT32                          ulResult;

    if (ulErrorCode != USIMM_SW_OK)
    {
        ulResult = VOS_ERR;
    }
    else
    {
        ulResult = VOS_OK;
    }

    pstUsimMsg = (USIMM_READFILE_CNF_STRU*)VOS_AllocMsg(WUEPS_PID_USIM, (sizeof(USIMM_READFILE_CNF_STRU) - VOS_MSG_HEAD_LENGTH) + pstCnfInfo->usDataLen);

    if(VOS_NULL_PTR == pstUsimMsg)
    {
        USIMM_ERROR_LOG("USIMM_GetFileCnf: VOS_AllocMsg is Failed");

        return;
    }

    pstUsimMsg->stCmdResult.enMsgName       = USIMM_READFILE_CNF;
    pstUsimMsg->stCmdResult.ulErrorCode     = ulErrorCode;
    pstUsimMsg->stCmdResult.ulResult        = ulResult;
    pstUsimMsg->stCmdResult.ulReceiverPid   = pstNewMsg->stMsgHeader.ulSenderPid;
    pstUsimMsg->stCmdResult.ulSendPara      = pstNewMsg->stMsgHeader.ulSendPara;
    pstUsimMsg->stCmdResult.enApptype       = pstNewMsg->stMsgHeader.enAppType;

    /*lint -e534*/
    VOS_MemCpy(&pstUsimMsg->stFilePath, &pstNewMsg->stFilePath, sizeof(USIMM_FILEPATH_INFO_STRU));
    /*lint +e534*/

    if (USIMM_SW_OK == ulErrorCode)
    {
        pstUsimMsg->ucRecordNum = pstCnfInfo->ucRecordNum;
        pstUsimMsg->usEfLen     = pstCnfInfo->usEfLen;
        pstUsimMsg->ucTotalNum  = pstCnfInfo->ucTotalNum;

        /*lint -e534*/
        VOS_MemCpy(pstUsimMsg->aucEf, pstCnfInfo->pucEf, pstCnfInfo->usDataLen);
        /*lint +e534*/
    }
    else
    {
        pstUsimMsg->ucRecordNum = 0;
        pstUsimMsg->usEfLen     = 0;
        pstUsimMsg->ucTotalNum  = 0;
    }

    (VOS_VOID)VOS_SendMsg(WUEPS_PID_USIM, pstUsimMsg);

    return;
}


VOS_VOID USIMM_ResetCnf(
    VOS_UINT32                          ulReceiverPid,
    USIMM_REFRESH_TYPE_ENUM_UINT32      enRefreshType,
    VOS_UINT32                          ulResult,
    VOS_UINT16                          usSATLen)
{
    USIMM_STKREFRESH_CNF_STRU              *pstUsimMsg;

    pstUsimMsg = (USIMM_STKREFRESH_CNF_STRU *)VOS_AllocMsg(WUEPS_PID_USIM,
                                                       sizeof(USIMM_STKREFRESH_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstUsimMsg)
    {
        USIMM_ERROR_LOG("USIMM_ResetCnf: VOS_AllocMsg is Failed");

        return;
    }

    pstUsimMsg->stCmdResult.ulReceiverPid                   = ulReceiverPid;
    pstUsimMsg->stCmdResult.enMsgName                       = USIMM_STKREFRESH_CNF;
    pstUsimMsg->stCmdResult.ulResult                        = ulResult;
    pstUsimMsg->stCmdResult.ulErrorCode                     = ulResult;
    pstUsimMsg->enRefreshType                               = enRefreshType;
    pstUsimMsg->ulSatLen                                    = usSATLen;

    (VOS_VOID)VOS_SendMsg(WUEPS_PID_USIM, pstUsimMsg);

    return;
}


VOS_VOID USIMM_TelecomAuthCnf(
    USIMM_AUTH_REQ_STRU                *pstMsg,
    USIMM_TELECOM_AUTH_INFO_STRU       *pstCnfInfo)
{
    USIMM_AUTHENTICATION_CNF_STRU      *pstCnfMsg;

    /* ������Ϣ�ڴ�  */
    pstCnfMsg = (USIMM_AUTHENTICATION_CNF_STRU *)VOS_AllocMsg(WUEPS_PID_USIM, sizeof(USIMM_AUTHENTICATION_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstCnfMsg)
    {
        USIMM_ERROR_LOG("USIMM_TelecomAuthCnf: VOS_AllocMsg is Failed");

        return;
    }

    /*lint -e534*/
    VOS_MemSet((VOS_UINT8*)pstCnfMsg + VOS_MSG_HEAD_LENGTH, 0, sizeof(USIMM_AUTHENTICATION_CNF_STRU) - VOS_MSG_HEAD_LENGTH);
    /*lint +e534*/

    pstCnfMsg->stCmdResult.ulReceiverPid= pstMsg->ulSenderPid;
    pstCnfMsg->stCmdResult.enMsgName    = USIMM_AUTHENTICATION_CNF;
    pstCnfMsg->stCmdResult.enApptype    = USIMM_GUTL_APP;

    /* ������ֵ����Ȩ����������� */
    pstCnfMsg->stCmdResult.ulResult     = VOS_OK;
    pstCnfMsg->stCmdResult.ulErrorCode  = VOS_OK;

    pstCnfMsg->stCmdResult.ulSendPara   = pstMsg->ulOpId;
    pstCnfMsg->enAuthType               = pstMsg->enAuthType;

     /* ��Ȩ��� */
    pstCnfMsg->enResult                 = pstCnfInfo->enResult;

    if ((VOS_NULL_PTR != pstCnfInfo->pucIK)
        && (sizeof(pstCnfMsg->uCnfData.stTELECnf.aucIK) > pstCnfInfo->pucIK[0]))
    {
        /*lint -e534*/
        VOS_MemCpy(pstCnfMsg->uCnfData.stTELECnf.aucIK, pstCnfInfo->pucIK, pstCnfInfo->pucIK[0] + 1);
        /*lint +e534*/
    }

    if ((VOS_NULL_PTR != pstCnfInfo->pucCK)
        && (sizeof(pstCnfMsg->uCnfData.stTELECnf.aucCK) > pstCnfInfo->pucCK[0]))
    {
        /*lint -e534*/
        VOS_MemCpy(pstCnfMsg->uCnfData.stTELECnf.aucCK, pstCnfInfo->pucCK, pstCnfInfo->pucCK[0] + 1);
        /*lint +e534*/
    }

    if ((VOS_NULL_PTR != pstCnfInfo->pucGsmKC)
        && (sizeof(pstCnfMsg->uCnfData.stTELECnf.aucGsmKc) > pstCnfInfo->pucGsmKC[0]))
    {
        /*lint -e534*/
        VOS_MemCpy(pstCnfMsg->uCnfData.stTELECnf.aucGsmKc, pstCnfInfo->pucGsmKC, pstCnfInfo->pucGsmKC[0] + 1);
        /*lint +e534*/
    }

    if ((VOS_NULL_PTR != pstCnfInfo->pucAuts)
        && (sizeof(pstCnfMsg->uCnfData.stTELECnf.aucAuts) > pstCnfInfo->pucAuts[0]))
    {
        /*lint -e534*/
        VOS_MemCpy(pstCnfMsg->uCnfData.stTELECnf.aucAuts, pstCnfInfo->pucAuts, pstCnfInfo->pucAuts[0] + 1);
        /*lint +e534*/
    }

    if ((VOS_NULL_PTR != pstCnfInfo->pucAuthRes)
        && (sizeof(pstCnfMsg->uCnfData.stTELECnf.aucAuthRes) > pstCnfInfo->pucAuthRes[0]))
    {
        /*lint -e534*/
        VOS_MemCpy(pstCnfMsg->uCnfData.stTELECnf.aucAuthRes, pstCnfInfo->pucAuthRes, pstCnfInfo->pucAuthRes[0] + 1);
        /*lint +e534*/
    }

    /* �ظ���Ϣ */
    (VOS_VOID)VOS_SendMsg(WUEPS_PID_USIM, pstCnfMsg);

    return;
}


VOS_VOID USIMM_ImsAuthCnf(USIMM_AUTH_REQ_STRU *pstMsg, USIMM_IMS_AUTH_INFO_STRU *pstCnfInfo)
{
    USIMM_AUTHENTICATION_CNF_STRU      *pstCnfMsg;
    VOS_UINT32                          ulNafLen = 0;

    /* ��ȡNAF���ݵĳ��� */
    if (VOS_NULL_PTR != pstCnfInfo->pucKs_ext_NAF)
    {
        ulNafLen = pstCnfInfo->pucKs_ext_NAF[0];
    }

    /* ������Ϣ�ڴ�  */
    pstCnfMsg = (USIMM_AUTHENTICATION_CNF_STRU *)VOS_AllocMsg(WUEPS_PID_USIM, sizeof(USIMM_AUTHENTICATION_CNF_STRU)+ulNafLen-VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstCnfMsg)
    {
        USIMM_ERROR_LOG("USIMM_ImsAuthCnf: VOS_AllocMsg is Failed");

        return;
    }

    /*lint -e534*/
    VOS_MemSet((VOS_UINT8*)pstCnfMsg + VOS_MSG_HEAD_LENGTH, 0, sizeof(USIMM_AUTHENTICATION_CNF_STRU)+ulNafLen-VOS_MSG_HEAD_LENGTH);
    /*lint +e534*/

    pstCnfMsg->stCmdResult.ulReceiverPid= pstMsg->ulSenderPid;
    pstCnfMsg->stCmdResult.enMsgName    = USIMM_AUTHENTICATION_CNF;
    pstCnfMsg->stCmdResult.enApptype    = USIMM_IMS_APP;

    /* ������ֵ����Ȩ����������� */
    pstCnfMsg->stCmdResult.ulResult     = VOS_OK;
    pstCnfMsg->stCmdResult.ulErrorCode  = VOS_OK;

    pstCnfMsg->stCmdResult.ulSendPara   = pstMsg->ulOpId;
    pstCnfMsg->enAuthType               = pstMsg->enAuthType;

     /* ��Ȩ��� */
    pstCnfMsg->enResult                 = pstCnfInfo->enResult;

    if ((VOS_NULL_PTR != pstCnfInfo->pucIK)
        && (sizeof(pstCnfMsg->uCnfData.stTELECnf.aucIK) > pstCnfInfo->pucIK[0]))
    {
        /*lint -e534*/
        VOS_MemCpy(pstCnfMsg->uCnfData.stIMSCnf.aucIK, pstCnfInfo->pucIK, pstCnfInfo->pucIK[0] + 1);
        /*lint +e534*/
    }

    if ((VOS_NULL_PTR != pstCnfInfo->pucCK)
        && (sizeof(pstCnfMsg->uCnfData.stTELECnf.aucCK) > pstCnfInfo->pucCK[0]))
    {
        /*lint -e534*/
        VOS_MemCpy(pstCnfMsg->uCnfData.stIMSCnf.aucCK, pstCnfInfo->pucCK, pstCnfInfo->pucCK[0] + 1);
        /*lint +e534*/
    }

    if ((VOS_NULL_PTR != pstCnfInfo->pucAuts)
        && (sizeof(pstCnfMsg->uCnfData.stTELECnf.aucAuts) > pstCnfInfo->pucAuts[0]))
    {
        /*lint -e534*/
        VOS_MemCpy(pstCnfMsg->uCnfData.stIMSCnf.aucAuts, pstCnfInfo->pucAuts, pstCnfInfo->pucAuts[0] + 1);
        /*lint +e534*/
    }

    if ((VOS_NULL_PTR != pstCnfInfo->pucAutsRes)
        && (sizeof(pstCnfMsg->uCnfData.stTELECnf.aucAuthRes) > pstCnfInfo->pucAutsRes[0]))
    {
        /*lint -e534*/
        VOS_MemCpy(pstCnfMsg->uCnfData.stIMSCnf.aucAuthRes, pstCnfInfo->pucAutsRes, pstCnfInfo->pucAutsRes[0] + 1);
        /*lint +e534*/
    }

    if (VOS_NULL_PTR != pstCnfInfo->pucKs_ext_NAF)
    {
        /*lint -e534*/
        VOS_MemCpy(pstCnfMsg->uCnfData.stIMSCnf.aucKs_ext_NAF, pstCnfInfo->pucKs_ext_NAF, pstCnfInfo->pucKs_ext_NAF[0] + 1);
        /*lint +e534*/
    }

    /* �ظ���Ϣ */
    (VOS_VOID)VOS_SendMsg(WUEPS_PID_USIM, pstCnfMsg);

    return;
}
VOS_VOID USIMM_RestrictedAccessCnf(
    USIMM_RACCESS_REQ_STRU             *pstReqMsg,
    VOS_UINT32                          ulResult,
    USIMM_RACCESSCNF_INFO_STRU         *pstCnfInfo)
{
    USIMM_RACCESS_CNF_STRU  *pstUsimMsg;

    pstUsimMsg = (USIMM_RACCESS_CNF_STRU *)VOS_AllocMsg(WUEPS_PID_USIM, sizeof(USIMM_RACCESS_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstUsimMsg)
    {
        USIMM_ERROR_LOG("USIMM_RestrictedAccessCnf: VOS_AllocMsg is Failed");

        return;
    }

    pstUsimMsg->stCmdResult.ulReceiverPid                   = pstReqMsg->stMsgHeader.ulSenderPid;
    pstUsimMsg->stCmdResult.enMsgName                       = USIMM_RACCESS_CNF;
    pstUsimMsg->stCmdResult.ulResult                        = ulResult;
    pstUsimMsg->stCmdResult.ulErrorCode                     = pstCnfInfo->ulErrorCode;
    pstUsimMsg->stCmdResult.enApptype                       = pstReqMsg->stMsgHeader.enAppType;
    pstUsimMsg->stCmdResult.ulSendPara                      = pstReqMsg->stMsgHeader.ulSendPara;
    pstUsimMsg->ucSW1                                       = pstCnfInfo->ucSW1;
    pstUsimMsg->ucSW2                                       = pstCnfInfo->ucSW2;
    pstUsimMsg->usLen                                       = 0;

    if((USIMM_API_SUCCESS == ulResult)&&(VOS_NULL_PTR != pstCnfInfo->pContent))
    {
        pstUsimMsg->usLen = pstCnfInfo->ucLen;

        /*lint -e534*/
        VOS_MemCpy(pstUsimMsg->aucContent, pstCnfInfo->pContent, pstCnfInfo->ucLen);
        /*lint +e534*/
    }

    (VOS_VOID)VOS_SendMsg(WUEPS_PID_USIM, pstUsimMsg);

    return;
}
VOS_VOID USIMM_TerminalResponseCnf(
    VOS_UINT32                          ulReceiverPid,
    VOS_UINT32                          ulErrorCode,
    VOS_UINT32                          ulSendPara,
    VOS_UINT8                           ucSW1,
    VOS_UINT8                           ucSW2)
{
    USIMM_STKTERMINALRSP_CNF_STRU  *pstUsimMsg;

    pstUsimMsg = (USIMM_STKTERMINALRSP_CNF_STRU *)VOS_AllocMsg(WUEPS_PID_USIM, sizeof(USIMM_STKTERMINALRSP_CNF_STRU)-VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstUsimMsg)
    {
        USIMM_ERROR_LOG("USIMM_TerminalResponseCnf: VOS_AllocMsg is Failed");

        return;
    }

    pstUsimMsg->stCmdResult.ulReceiverPid   = ulReceiverPid;
    pstUsimMsg->stCmdResult.enMsgName       = USIMM_STKTERMINALRSP_CNF;
    pstUsimMsg->stCmdResult.ulErrorCode     = ulErrorCode;
    pstUsimMsg->stCmdResult.ulSendPara      = ulSendPara;
    pstUsimMsg->ucSW1                       = ucSW1;
    pstUsimMsg->ucSW2                       = ucSW2;

    if(ulErrorCode != USIMM_SW_OK)
    {
        pstUsimMsg->stCmdResult.ulResult = VOS_ERR;
    }
    else
    {
        pstUsimMsg->stCmdResult.ulResult = VOS_OK;
    }

    (VOS_VOID)VOS_SendMsg(WUEPS_PID_USIM, pstUsimMsg);

    return;
}


VOS_VOID USIMM_EnvelopeCnf(
    VOS_UINT32                          ulReceiverPid,
    VOS_UINT32                          ulSendPara,
    VOS_UINT32                          ulErrorCode,
    USIMM_ENVELOPECNF_INFO_STRU        *pstCnfInfo)
{
    USIMM_STKENVELOPE_CNF_STRU  *pstUsimMsg;

    pstUsimMsg = (USIMM_STKENVELOPE_CNF_STRU *)VOS_AllocMsg(WUEPS_PID_USIM, sizeof(USIMM_STKENVELOPE_CNF_STRU)-VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstUsimMsg)
    {
        USIMM_ERROR_LOG("USIMM_EnvelopeCnf: VOS_AllocMsg is Failed");

        return;
    }

    pstUsimMsg->stCmdResult.ulReceiverPid                   = ulReceiverPid;
    pstUsimMsg->stCmdResult.enMsgName                       = USIMM_STKENVELOPE_CNF;
    pstUsimMsg->stCmdResult.ulErrorCode                     = ulErrorCode;
    pstUsimMsg->stCmdResult.ulSendPara                      = ulSendPara;
    pstUsimMsg->ucDataType                                  = pstCnfInfo->ucDataType;
    pstUsimMsg->ucSW1                                       = pstCnfInfo->ucSW1;
    pstUsimMsg->ucSW2                                       = pstCnfInfo->ucSW2;

    if (ulErrorCode != USIMM_SW_OK)
    {
        pstUsimMsg->stCmdResult.ulResult                    = VOS_ERR;
    }
    else
    {
        pstUsimMsg->stCmdResult.ulResult                    = VOS_OK;
    }

    /* ����SMS PP DOWNLOAD������������Ҫ�ظ������࣬��Ҫ�ϱ���TAF */
    if (pstCnfInfo->ulDataLen > VOS_NULL)
    {
        /*lint -e534*/
        VOS_MemCpy(pstUsimMsg->aucData, pstCnfInfo->pucData, pstCnfInfo->ulDataLen);
        /*lint +e534*/

        pstUsimMsg->ucDataLen = (VOS_UINT8)pstCnfInfo->ulDataLen;
    }
    else
    {
        pstUsimMsg->ucDataLen = 0;
    }

    (VOS_VOID)VOS_SendMsg(WUEPS_PID_USIM, pstUsimMsg);

    return;
}
VOS_VOID USIMM_SingleCmdCnf(
    VOS_UINT32                      ulReceiverPid,
    VOS_UINT32                      ulMsgName,
    VOS_UINT32                      ulSendPara,
    VOS_UINT32                      ulResult,
    USIMM_CARDAPP_ENUM_UINT32       enApptype)
{
    USIMM_SINGLECMD_CNF_STRU            *pstUsimMsg;

    pstUsimMsg = (USIMM_SINGLECMD_CNF_STRU *)VOS_AllocMsg(WUEPS_PID_USIM,
                                                         (sizeof(USIMM_SINGLECMD_CNF_STRU) - VOS_MSG_HEAD_LENGTH));

    if (VOS_NULL_PTR == pstUsimMsg)
    {
        USIMM_ERROR_LOG("USIMM_SingleCmdCnf: VOS_AllocMsg is Failed");

        return;
    }

    pstUsimMsg->stCmdResult.ulReceiverPid   = ulReceiverPid;
    pstUsimMsg->stCmdResult.enMsgName       = ulMsgName;
    pstUsimMsg->stCmdResult.ulResult        = ulResult;
    pstUsimMsg->stCmdResult.ulErrorCode     = ulResult;
    pstUsimMsg->stCmdResult.enApptype       = enApptype;
    pstUsimMsg->stCmdResult.ulSendPara      = ulSendPara;

    (VOS_VOID)VOS_SendMsg(WUEPS_PID_USIM, pstUsimMsg);

    return;
}


VOS_VOID USIMM_FDNCnf(
    VOS_UINT32                          ulReceiverPid,
    VOS_UINT32                          ulResult,
    VOS_UINT32                          ulErrCode,
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    VOS_UINT32                          ulSendPara,
    VOS_UINT32                          ulFDNState)
{
    USIMM_FDNPROCESS_CNF_STRU          *pstUsimMsg;

    pstUsimMsg = (USIMM_FDNPROCESS_CNF_STRU *)VOS_AllocMsg(WUEPS_PID_USIM,
                                                          sizeof(USIMM_FDNPROCESS_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstUsimMsg)
    {
        USIMM_ERROR_LOG("USIMM_FDNCnf: VOS_AllocMsg is Failed");

        return;
    }

    pstUsimMsg->stCmdResult.ulReceiverPid   = ulReceiverPid;
    pstUsimMsg->stCmdResult.enMsgName       = USIMM_FBDNPROCESS_CNF;
    pstUsimMsg->stCmdResult.ulResult        = ulResult;
    pstUsimMsg->stCmdResult.ulErrorCode     = ulErrCode;
    pstUsimMsg->stCmdResult.enApptype       = enAppType;
    pstUsimMsg->stCmdResult.ulSendPara      = ulSendPara;
    pstUsimMsg->enFDNState                  = ulFDNState;

    (VOS_VOID)VOS_SendMsg(WUEPS_PID_USIM, pstUsimMsg);

    return;
}


VOS_VOID USIMM_SetSPBFileCnf(USIMM_SETMUTILFILE_REQ_STRU    *pstReqMsg,
                                      VOS_UINT32                     ulErrorCode)
{
    USIMM_SETMUTILFILE_CNF_STRU *pstUsimMsg = VOS_NULL_PTR;
    VOS_UINT32                  i;

    pstUsimMsg = (USIMM_SETMUTILFILE_CNF_STRU *)VOS_AllocMsg(WUEPS_PID_USIM,
                                                sizeof(USIMM_SETMUTILFILE_CNF_STRU)-VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstUsimMsg)
    {
        USIMM_ERROR_LOG("USIMM_SetSPBFileCnf: VOS_AllocMsg is Failed");

        return;
    }

    if(ulErrorCode != USIMM_SW_OK)
    {
        pstUsimMsg->stCmdResult.ulResult = VOS_ERR;
    }
    else
    {
        pstUsimMsg->stCmdResult.ulResult = VOS_OK;
    }

    pstUsimMsg->stCmdResult.ulReceiverPid   = pstReqMsg->stMsgHeader.ulSenderPid;
    pstUsimMsg->stCmdResult.enMsgName       = USIMM_SETMUTILFILE_CNF;
    pstUsimMsg->stCmdResult.ulErrorCode     = ulErrorCode;
    pstUsimMsg->stCmdResult.enApptype       = pstReqMsg->stMsgHeader.enAppType;

    pstUsimMsg->ucFileNum                   = (VOS_UINT8)pstReqMsg->ulFileCount;

    if (VOS_OK == pstUsimMsg->stCmdResult.ulResult)
    {
        for(i = 0; i < pstReqMsg->ulFileCount; i++)
        {
            pstUsimMsg->ausEfId[i]      = pstReqMsg->stFileData[i].usFileID;
            pstUsimMsg->aucRecordNum[i] = pstReqMsg->stFileData[i].ucRecordNum;
            pstUsimMsg->ausEfLen[i]     = pstReqMsg->stFileData[i].usDataLen;
        }
    }

    (VOS_VOID)VOS_SendMsg(WUEPS_PID_USIM, pstUsimMsg);

    return;
}


VOS_VOID USIMM_SearchHandleCnf(USIMM_SEARCHFILE_REQ_STRU   *pstMsg,
                                         VOS_UINT32                   ulErrorCode,
                                         USIMM_SEARCHCNF_INFO_STRU    *pstCnfInfo)
{
    USIMM_SEARCHFILE_CNF_STRU     *pUsimMsg;

    pUsimMsg = (USIMM_SEARCHFILE_CNF_STRU *)VOS_AllocMsg(WUEPS_PID_USIM,
                            (sizeof(USIMM_SEARCHFILE_CNF_STRU) - VOS_MSG_HEAD_LENGTH) + pstCnfInfo->ulLen);

    if (VOS_NULL_PTR == pUsimMsg)
    {
        USIMM_ERROR_LOG("USIMM_SearchHandleCnf: VOS_AllocMsg is Failed");

        return;
    }

    pUsimMsg->stCmdResult.ulReceiverPid = pstMsg->stMsgHeader.ulSenderPid;
    pUsimMsg->stCmdResult.enMsgName     = USIMM_SEARCHFILE_CNF;
    pUsimMsg->stCmdResult.ulErrorCode   = ulErrorCode;
    pUsimMsg->usTotalRecNum             = pstCnfInfo->usTotalRecNum;
    pUsimMsg->usDataLen                 = 0;

    if (USIMM_SW_OK == ulErrorCode)
    {
        pUsimMsg->stCmdResult.ulResult  = VOS_OK;
    }
    else
    {
        pUsimMsg->stCmdResult.ulResult  = ulErrorCode;
    }

    /*lint -e534*/
    VOS_MemCpy(&pUsimMsg->stFilePath, &pstMsg->stFilePath, sizeof(pstMsg->stFilePath));
    /*lint +e534*/

    if ((VOS_NULL_PTR != pstCnfInfo->pucData) && (pstCnfInfo->ulLen <= 255))
    {
        VOS_MemCpy(pUsimMsg->aucData, pstCnfInfo->pucData, pstCnfInfo->ulLen);

        pUsimMsg->usDataLen = (VOS_UINT8)pstCnfInfo->ulLen;
    }

    (VOS_VOID)VOS_SendMsg(WUEPS_PID_USIM, pUsimMsg);

    return;
}

/*****************************************************************************
�� �� ��  : USIMM_GetPhyCardType
��������  : �жϿ����������ͣ�ICC��UICC��
�������  : ��
�������  : ��
�� �� ֵ  : USIMM_PHYCARD_TYPE_ENUM_UINT32����
���ú���  :
��������  :
�޶���¼  :
1.��    ��  : 2015��02��07��
  ��    ��  : H00300778
  �޸�����  : �½�����
*****************************************************************************/
USIMM_PHYCARD_TYPE_ENUM_UINT32 USIMM_GetPhyCardType(VOS_VOID)
{
    USIMM_PHYCARD_TYPE_ENUM_UINT32      enPhyCardType;

#if (FEATURE_UE_MODE_CDMA == FEATURE_ON)
    if ((USIMM_CARD_CSIM == gastUSIMMCardAppInfo[USIMM_UICC_CDMA].enCardType)
     || (USIMM_CARD_USIM == gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardType)
     || (USIMM_OPENSPEEDENABLE == gulUSIMMOpenSpeed))
    {
        enPhyCardType = USIMM_PHYCARD_TYPE_UICC;
    }
    else if ((USIMM_CARD_UIM == gastUSIMMCardAppInfo[USIMM_UICC_CDMA].enCardType)
          || (USIMM_CARD_SIM == gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardType))
    {
        enPhyCardType = USIMM_PHYCARD_TYPE_ICC;
    }
    else
    {
        enPhyCardType = USIMM_PHYCARD_TYPE_NOCARD;
    }
#else
    if ((USIMM_CARD_USIM == gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardType)
        || (USIMM_OPENSPEEDENABLE == gulUSIMMOpenSpeed))
    {
        enPhyCardType = USIMM_PHYCARD_TYPE_UICC;
    }
    else if (USIMM_CARD_SIM == gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardType)
    {
        enPhyCardType = USIMM_PHYCARD_TYPE_ICC;
    }
    else
    {
        enPhyCardType = USIMM_PHYCARD_TYPE_NOCARD;
    }
#endif

    return enPhyCardType;
}


VOS_VOID USIMM_CardStatusInd(VOS_UINT32 ulReceiverPid)
{
    USIMM_CARDSTATUS_IND_STRU          *pstUsimMsg;

    pstUsimMsg = (USIMM_CARDSTATUS_IND_STRU *)VOS_AllocMsg(WUEPS_PID_USIM, sizeof(USIMM_CARDSTATUS_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstUsimMsg )
    {
        USIMM_ERROR_LOG("USIMM_CardStatusInd: VOS_AllocMsg is Failed");

        return;
    }

    pstUsimMsg->ulReceiverPid = ulReceiverPid;
    pstUsimMsg->ulMsgName     = USIMM_CARDSTATUS_IND;     /* ������Ϣ���� */
    pstUsimMsg->enPhyCardType = USIMM_GetPhyCardType();
    pstUsimMsg->stUsimSimInfo.enCardService                 = gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardService;
    pstUsimMsg->stUsimSimInfo.enCardType                    = gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardType;
#if (FEATURE_UE_MODE_CDMA == FEATURE_ON)
    pstUsimMsg->stCsimUimInfo.enCardService                 = gastUSIMMCardAppInfo[USIMM_UICC_CDMA].enCardService;
    pstUsimMsg->stCsimUimInfo.enCardType                    = gastUSIMMCardAppInfo[USIMM_UICC_CDMA].enCardType;
#else
    pstUsimMsg->stCsimUimInfo.enCardService                 = USIMM_CARD_SERVIC_ABSENT;
    pstUsimMsg->stCsimUimInfo.enCardType                    = USIMM_CARD_NOCARD;
#endif
    pstUsimMsg->stIsimInfo.enCardService                    = gastUSIMMCardAppInfo[USIMM_UICC_ISIM].enCardService;
    pstUsimMsg->stIsimInfo.enCardType                       = gastUSIMMCardAppInfo[USIMM_UICC_ISIM].enCardType;

    (VOS_VOID)VOS_SendMsg(pstUsimMsg->ulSenderPid, pstUsimMsg);

    /*��״̬�����п�����������(���ﱣ����ԭ�д����߼�һ��)*/
    if(USIMM_CARD_SERVIC_AVAILABLE != gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardService)
    {
        USIMM_SaveLogFile();
    }

    g_stUSIMMLogData.enLogState = USIMM_NO_NEED_LOG;/*�ϱ���״̬�Ͳ���Ҫ��¼log*/

    return;
}

/*2�׶ο���ʹ��*/

VOS_VOID USIMM_SatDataInd(VOS_UINT8   ucCmdType,
                                    VOS_UINT16 usDataLen,
                                    VOS_UINT8 *pucData)
{
    USIMM_STKDATA_IND_STRU             *pstUsimMsg;

    pstUsimMsg = (USIMM_STKDATA_IND_STRU *)VOS_AllocMsg(WUEPS_PID_USIM, sizeof(USIMM_STKDATA_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstUsimMsg)
    {
        return;
    }

    pstUsimMsg->stIndHdr.ulReceiverPid  = MAPS_STK_PID;
    pstUsimMsg->stIndHdr.enMsgName      = USIMM_STKDATA_IND;
    pstUsimMsg->usLen                   = usDataLen;
    pstUsimMsg->ucCmdType               = ucCmdType;

    /*lint -e534*/
    VOS_MemCpy(pstUsimMsg->aucContent, pucData, usDataLen);
    /*lint +e534*/

    (VOS_VOID)VOS_SendMsg(WUEPS_PID_USIM, pstUsimMsg);

    return;
}

#if (FEATURE_VSIM == FEATURE_ON)

VOS_VOID USIMM_VsimReDhNegotiateInd(VOS_VOID)
{
    USIMM_VSIM_RDH_IND_STRU         *pstMsg;

    pstMsg = (USIMM_VSIM_RDH_IND_STRU *)VOS_AllocMsg(WUEPS_PID_USIM,
                                    sizeof(USIMM_VSIM_RDH_IND_STRU)-VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    pstMsg->stIndHdr.ulReceiverPid = MAPS_PIH_PID;
    pstMsg->stIndHdr.enMsgName     = USIMM_VSIM_RDH_IND;

    (VOS_VOID)VOS_SendMsg(WUEPS_PID_USIM, pstMsg);

    return;
}
#endif

VOS_VOID USIMM_EccNumberInd(VOS_UINT8 ucEccType,
                                        VOS_UINT16 usEfLen,
                                        VOS_UINT8 ucRecordNum,
                                        VOS_UINT8 *pucData)
{

    USIMM_ECCNUMBER_IND_STRU        *pstUsimMsg;

    pstUsimMsg = (USIMM_ECCNUMBER_IND_STRU *)VOS_AllocMsg(WUEPS_PID_USIM,
                            (sizeof(USIMM_ECCNUMBER_IND_STRU)-VOS_MSG_HEAD_LENGTH)+usEfLen);

    if (VOS_NULL_PTR == pstUsimMsg)
    {
        return;
    }

    pstUsimMsg->stIndHdr.ulReceiverPid  = MAPS_PB_PID;                                           /*��дPB��PID*/
    pstUsimMsg->stIndHdr.enMsgName      = USIMM_ECCNUMBER_IND;
    pstUsimMsg->ucEccType               = ucEccType;
    pstUsimMsg->ucRecordNum             = ucRecordNum;
    pstUsimMsg->usFileSize              = usEfLen;

    if(0 != usEfLen)
    {
        /*lint -e534*/
        VOS_MemCpy(pstUsimMsg->ucContent, pucData, usEfLen);
        /*lint +e534*/
    }

    (VOS_VOID)VOS_SendMsg(WUEPS_PID_USIM, pstUsimMsg);

    return;
}
VOS_VOID USIMM_OpenChannelCnf(
    VOS_UINT32                          ulReceiverPid,
    VOS_UINT32                          ulSendPara,
    VOS_UINT32                          ulResult,
    VOS_UINT32                          ulErrCode,
    VOS_UINT32                          ulSessionId,
    VOS_UINT8                           ucChannelId)
{
    USIMM_OPENCHANNEL_CNF_STRU      *pstUsimMsg = VOS_NULL_PTR;

    pstUsimMsg = (USIMM_OPENCHANNEL_CNF_STRU *)VOS_AllocMsg(WUEPS_PID_USIM,
                                                            sizeof(USIMM_OPENCHANNEL_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstUsimMsg)
    {
        USIMM_ERROR_LOG("USIMM_OpenChannelCnf: VOS_AllocMsg is Failed");

        return;
    }

    pstUsimMsg->stCmdResult.ulReceiverPid                   = ulReceiverPid;
    pstUsimMsg->stCmdResult.enMsgName                       = USIMM_OPENCHANNEL_CNF;
    pstUsimMsg->stCmdResult.ulResult                        = ulResult;
    pstUsimMsg->stCmdResult.ulErrorCode                     = ulErrCode;
    pstUsimMsg->stCmdResult.ulSendPara                      = ulSendPara;
    pstUsimMsg->ulSessionID                                 = ulSessionId;
    pstUsimMsg->ucChannelID                                 = ucChannelId;

    (VOS_VOID)VOS_SendMsg(WUEPS_PID_USIM, pstUsimMsg);

    return;
}


VOS_VOID USIMM_CloseChannelCnf(
    VOS_UINT32                          ulReceiverPid,
    VOS_UINT32                          ulSendPara,
    VOS_UINT32                          ulResult,
    VOS_UINT32                          ulErrCode)
{
    USIMM_CLOSECHANNEL_CNF_STRU        *pstUsimMsg = VOS_NULL_PTR;

    pstUsimMsg = (USIMM_CLOSECHANNEL_CNF_STRU *)VOS_AllocMsg(WUEPS_PID_USIM,
                                                             sizeof(USIMM_CLOSECHANNEL_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstUsimMsg)
    {
        USIMM_ERROR_LOG("USIMM_CloseChannelCnf: VOS_AllocMsg is Failed");

        return;
    }

    pstUsimMsg->stCmdResult.ulReceiverPid                   = ulReceiverPid;
    pstUsimMsg->stCmdResult.enMsgName                       = USIMM_CLOSECHANNEL_CNF;
    pstUsimMsg->stCmdResult.ulResult                        = ulResult;
    pstUsimMsg->stCmdResult.ulErrorCode                     = ulErrCode;
    pstUsimMsg->stCmdResult.ulSendPara                      = ulSendPara;

    (VOS_VOID)VOS_SendMsg(WUEPS_PID_USIM, pstUsimMsg);

    return;
}

/*****************************************************************************
�� �� ��  :USIMM_SendTPDUCnf
��������  :Send TPDU��Ϣ�ظ�
�������  :ulReceiverPid:������ϢPID
           ulResult:�������
           ulErrCode:������
           pstDataCnf:Send TPDU��Ϣ�ظ�����
�������  :��
�� �� ֵ  :��

�޶���¼  :
1. ��    ��   : 2014��1��15��
   ��    ��   : zhuli
   �޸�����   : Creat
*****************************************************************************/
VOS_VOID USIMM_SendTPDUCnf(VOS_UINT32                       ulReceiverPid,
                                        VOS_UINT32                      ulSendPara,
                                        VOS_UINT32                      ulResult,
                                        VOS_UINT32                      ulErrCode,
                                        USIMM_SENDTPDU_CNFINFO_STRU     *pstDataCnf,
                                        USIMM_FILEPATH_INFO_STRU        *pstFilePath)
{
    USIMM_SENDTPDUDATA_CNF_STRU    *pstUsimMsg = VOS_NULL_PTR;

    pstUsimMsg = (USIMM_SENDTPDUDATA_CNF_STRU *)VOS_AllocMsg(WUEPS_PID_USIM,
                                               sizeof(USIMM_SENDTPDUDATA_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstUsimMsg)
    {
        USIMM_ERROR_LOG("USIMM_AccessChannelCnf: VOS_AllocMsg is Failed");

        return;
    }

    pstUsimMsg->stCmdResult.ulReceiverPid           =   ulReceiverPid;
    pstUsimMsg->stCmdResult.enMsgName               =   USIMM_SENDTPDUDATA_CNF;
    pstUsimMsg->stCmdResult.ulResult                =   ulResult;
    pstUsimMsg->stCmdResult.ulErrorCode             =   ulErrCode;
    pstUsimMsg->stCmdResult.ulSendPara              =   ulSendPara;

    pstUsimMsg->stRspData.ucSW1                     =   pstDataCnf->ucSw1;
    pstUsimMsg->stRspData.ucSW2                     =   pstDataCnf->ucSw2;
    pstUsimMsg->stRspData.ulDataLen                 =   pstDataCnf->usDataLen;

    if (VOS_NULL != pstDataCnf->usDataLen)
    {
        /*lint -e534*/
        VOS_MemCpy(pstUsimMsg->stRspData.aucRspData, pstDataCnf->pucData, pstDataCnf->usDataLen);
        /*lint +e534*/
    }

    if (VOS_NULL_PTR != pstDataCnf->pucTPDUHead)
    {
        /*lint -e534*/
        VOS_MemCpy(pstUsimMsg->stRspData.aucInputCmd, pstDataCnf->pucTPDUHead, USIMM_TPDU_HEAD_LEN);
        /*lint +e534*/
    }

    if (VOS_NULL_PTR != pstFilePath)
    {
        /*lint -e534*/
        VOS_MemCpy(&pstUsimMsg->stFilePath, pstFilePath, sizeof(USIMM_FILEPATH_INFO_STRU));
        /*lint +e534*/
    }

    (VOS_VOID)VOS_SendMsg(WUEPS_PID_USIM, pstUsimMsg);

    return;

}

#if (FEATURE_UE_MODE_CDMA == FEATURE_ON)
/*****************************************************************************
�� �� ��  :USIMM_SendTPDUCnf
��������  :Send TPDU��Ϣ�ظ�
�������  :ulReceiverPid:������ϢPID
           ulResult:�������
           ulErrCode:������
           pstDataCnf:Send TPDU��Ϣ�ظ�����
�������  :��
�� �� ֵ  :��

�޶���¼  :
1. ��    ��   : 2014��1��15��
   ��    ��   : zhuli
   �޸�����   : Creat
*****************************************************************************/
VOS_VOID USIMM_CdmaAuthCnf(
    USIMM_AUTH_REQ_STRU                *pstMsg,
    USIMM_CDMA_AUTH_INFO_STRU          *pstCnfInfo)
{
    USIMM_AUTHENTICATION_CNF_STRU      *pstCnfMsg;

    /* ������Ϣ�ڴ�  */
    pstCnfMsg = (USIMM_AUTHENTICATION_CNF_STRU *)VOS_AllocMsg(WUEPS_PID_USIM, sizeof(USIMM_AUTHENTICATION_CNF_STRU)-VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstCnfMsg)
    {
        USIMM_ERROR_LOG("USIMM_CdmaAuthCnf: VOS_AllocMsg is Failed");

        return;
    }

    /*lint -e534*/
    VOS_MemSet((VOS_UINT8*)pstCnfMsg + VOS_MSG_HEAD_LENGTH, 0, pstCnfMsg->stCmdResult.ulLength);
    /*lint +e534*/

    pstCnfMsg->stCmdResult.ulReceiverPid= pstMsg->ulSenderPid;
    pstCnfMsg->stCmdResult.enMsgName    = USIMM_AUTHENTICATION_CNF;
    pstCnfMsg->stCmdResult.enApptype    = USIMM_CDMA_APP;

    /* ������ֵ����Ȩ����������� */
    pstCnfMsg->stCmdResult.ulResult     = VOS_OK;
    pstCnfMsg->stCmdResult.ulErrorCode  = VOS_OK;

    pstCnfMsg->stCmdResult.ulSendPara   = pstMsg->ulOpId;
    pstCnfMsg->enAuthType               = pstMsg->enAuthType;

     /* ��Ȩ��� */
    pstCnfMsg->enResult                 = pstCnfInfo->enResult;

    if (USIMM_RUNCAVE_AUTH == pstMsg->enAuthType)
    {
        if (VOS_NULL_PTR != pstCnfInfo->pucAuthr)
        {
            /*lint -e534*/
            VOS_MemCpy(pstCnfMsg->uCnfData.stRunCaveCnf.aucAuthr, pstCnfInfo->pucAuthr, sizeof(pstCnfMsg->uCnfData.stRunCaveCnf.aucAuthr));
            /*lint +e534*/
        }
    }

    if (USIMM_3G_AUTH == pstMsg->enAuthType)
    {
        if (VOS_NULL_PTR != pstCnfInfo->pucIK)
        {
            pstCnfMsg->uCnfData.stTELECnf.aucIK[0] = USIMM_AUTH_IK_LEN;

            /*lint -e534*/
            VOS_MemCpy(&pstCnfMsg->uCnfData.stTELECnf.aucIK[1], pstCnfInfo->pucIK, pstCnfMsg->uCnfData.stTELECnf.aucIK[0]);
            /*lint +e534*/
        }

        if (VOS_NULL_PTR != pstCnfInfo->pucCK)
        {
            pstCnfMsg->uCnfData.stTELECnf.aucCK[0] = USIMM_AUTH_CK_LEN;

            /*lint -e534*/
            VOS_MemCpy(&pstCnfMsg->uCnfData.stTELECnf.aucCK[1], pstCnfInfo->pucCK, pstCnfMsg->uCnfData.stTELECnf.aucCK[0]);
            /*lint +e534*/
        }

        if (VOS_NULL_PTR != pstCnfInfo->pucAuthRes)
        {
            if (pstCnfInfo->pucAuthRes[0] >= USIMM_AUTH_RESSPACELEN)
            {
                pstCnfMsg->uCnfData.stTELECnf.aucAuthRes[0] = USIMM_AUTH_RESSPACELEN -1;
            }
            else
            {
                pstCnfMsg->uCnfData.stTELECnf.aucAuthRes[0] = pstCnfInfo->pucAuthRes[0];
            }

            /*lint -e534*/
            VOS_MemCpy(&pstCnfMsg->uCnfData.stTELECnf.aucAuthRes[1], pstCnfInfo->pucAuthRes, pstCnfMsg->uCnfData.stTELECnf.aucAuthRes[0]);
            /*lint +e534*/
        }

        if (VOS_NULL_PTR != pstCnfInfo->pucAuts)
        {
            pstCnfMsg->uCnfData.stTELECnf.aucAuts[0] = USIMM_AUTH_AUTHSPACELEN - 1;

            /*lint -e534*/
            VOS_MemCpy(&pstCnfMsg->uCnfData.stTELECnf.aucAuts[1], pstCnfInfo->pucAuts, pstCnfMsg->uCnfData.stTELECnf.aucAuts[0]);
            /*lint +e534*/
        }
    }

    /* �ظ���Ϣ */
    (VOS_VOID)VOS_SendMsg(WUEPS_PID_USIM, pstCnfMsg);

    return;
}

/*****************************************************************************
�� �� ��  :USIMM_SendTPDUCnf
��������  :Send TPDU��Ϣ�ظ�
�������  :ulReceiverPid:������ϢPID
           ulResult:�������
           ulErrCode:������
           pstDataCnf:Send TPDU��Ϣ�ظ�����
�������  :��
�� �� ֵ  :��

�޶���¼  :
1. ��    ��   : 2014��1��15��
   ��    ��   : zhuli
   �޸�����   : Creat
*****************************************************************************/
VOS_VOID USIMM_BSChallengeCnf(
    USIMM_CMDHEADER_REQ_STRU           *pstReqMsg,
    VOS_UINT32                          ulResult,
    VOS_UINT32                          ulErrCode,
    VOS_UINT32                          ulDataLen,
    VOS_UINT8                          *pucRandBs)
{
    USIMM_BSCHALLENGE_CNF_STRU       *pstUsimMsg;

    pstUsimMsg = (USIMM_BSCHALLENGE_CNF_STRU *)VOS_AllocMsg(WUEPS_PID_USIM,
                                                            ulDataLen + sizeof(USIMM_BSCHALLENGE_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstUsimMsg)
    {
        USIMM_ERROR_LOG("USIMM_BSChallengeCnf: VOS_AllocMsg is Failed");

        return;
    }

    pstUsimMsg->stCmdResult.ulReceiverPid                   = pstReqMsg->ulSenderPid;
    pstUsimMsg->stCmdResult.enApptype                       = pstReqMsg->enAppType;
    pstUsimMsg->stCmdResult.ulSendPara                      = pstReqMsg->ulSendPara;
    pstUsimMsg->stCmdResult.enMsgName                       = USIMM_BSCHALLENGE_CNF;
    pstUsimMsg->stCmdResult.ulResult                        = ulResult;
    pstUsimMsg->stCmdResult.ulErrorCode                     = ulErrCode;
    pstUsimMsg->ulDataLen                                   = ulDataLen;

    if (VOS_NULL_PTR != pucRandBs)
    {
        /*lint -e534*/
        VOS_MemCpy(pstUsimMsg->aucData, pucRandBs, ulDataLen);
        /*lint +e534*/
    }

    (VOS_VOID)VOS_SendMsg(WUEPS_PID_USIM, pstUsimMsg);

    return;
}

/*****************************************************************************
�� �� ��  :USIMM_SendTPDUCnf
��������  :Send TPDU��Ϣ�ظ�
�������  :ulReceiverPid:������ϢPID
           ulResult:�������
           ulErrCode:������
           pstDataCnf:Send TPDU��Ϣ�ظ�����
�������  :��
�� �� ֵ  :��

�޶���¼  :
1. ��    ��   : 2014��1��15��
   ��    ��   : zhuli
   �޸�����   : Creat
*****************************************************************************/
VOS_VOID USIMM_GenerateKeyVpmCnf(
    USIMM_GENERATE_KEYVPM_REQ_STRU     *pstReqMsg,
    VOS_UINT32                          ulResult,
    VOS_UINT32                          ulErrCode,
    VOS_UINT32                          ulVpmLen,
    VOS_UINT8                          *pucVpm,
    VOS_UINT8                          *pucKey)
{
    USIMM_GENERATE_KEYVPM_CNF_STRU     *pstUsimMsg;

    pstUsimMsg = (USIMM_GENERATE_KEYVPM_CNF_STRU *)VOS_AllocMsg(WUEPS_PID_USIM,
                                                                ulVpmLen + sizeof(USIMM_GENERATE_KEYVPM_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstUsimMsg)
    {
        USIMM_ERROR_LOG("USIMM_GenerateKeyVpmCnf: VOS_AllocMsg is Failed");

        return;
    }

    pstUsimMsg->stCmdResult.ulReceiverPid                   = pstReqMsg->stMsgHeader.ulSenderPid;
    pstUsimMsg->stCmdResult.enApptype                       = pstReqMsg->stMsgHeader.enAppType;
    pstUsimMsg->stCmdResult.ulSendPara                      = pstReqMsg->stMsgHeader.ulSendPara;
    pstUsimMsg->stCmdResult.enMsgName                       = USIMM_GENERATE_KEYVPM_CNF;
    pstUsimMsg->stCmdResult.ulResult                        = ulResult;
    pstUsimMsg->stCmdResult.ulErrorCode                     = ulErrCode;

    /*lint -e534*/
    VOS_MemCpy(pstUsimMsg->aucKey, pucKey, sizeof(pstUsimMsg->aucKey));
    /*lint +e534*/

    if (0 != ulVpmLen)
    {
        /*lint -e534*/
        VOS_MemCpy(pstUsimMsg->aucVPM, pucVpm, ulVpmLen);
        /*lint +e534*/

        pstUsimMsg->ulVPMLen = ulVpmLen;
    }

    (VOS_VOID)VOS_SendMsg(WUEPS_PID_USIM, pstUsimMsg);

    return;
}

#endif /*#if (FEATURE_UE_MODE_CDMA == FEATURE_ON)*/

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

