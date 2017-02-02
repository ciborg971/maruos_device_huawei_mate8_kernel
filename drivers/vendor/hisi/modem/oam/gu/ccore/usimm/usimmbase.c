
#include "vos_Id.h"
#include "usimmbase.h"
#include "usimmapdu.h"
#include "usimmdl.h"
#include "siappstk.h"
#include "NvIdList.h"
#include "usimmt1dl.h"
#include "usimmglobal.h"
#include "usimminit.h"
#include "siapppih.h"
#include "errorlog.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID PS_FILE_ID_USIMM_BASE_C
/*lint +e767*/

#if (FEATURE_ON == FEATURE_UE_UICC_MULTI_APP_SUPPORT)


VOS_UINT32 USIMM_RefreshHandle(
    USIMM_CMDHEADER_REQ_STRU            *pMsg)
{
    USIMM_STKREFRESH_REQ_STRU          *pstMsg;
    USIMM_CARDAPP_ENUM_UINT32           enAppType;
    VOS_UINT8                           ucChannelNo;

    pstMsg = (USIMM_STKREFRESH_REQ_STRU*)pMsg;

    if (USIMM_RESET == pstMsg->enRefreshType)
    {
        USIMM_INFO_LOG("USIMM_RefreshHandle: The Card Need Cold Reset.");

        if (USIMM_PHYCARD_TYPE_UICC == USIMM_CCB_GetCardType())
        {
            for (enAppType = 0; enAppType < USIMM_CARDAPP_BUTT; enAppType++)
            {
                ucChannelNo = USIMM_CCB_GetAppChNO(enAppType);

                if (VOS_NULL_BYTE != ucChannelNo)
                {
                    (VOS_VOID)USIMM_SendStatusApdu(ucChannelNo,
                                                   USIMM_STATUS_TERMINATION_CURAPP,
                                                   USIMM_STATUS_DF_NAME_RETURNED,
                                                   VOS_NULL_BYTE);
                }
            }
        }

        USIMM_ResetGlobalVar();

        (VOS_VOID)USIMM_COMM_InitCard(VOS_NULL_PTR);

        USIMM_RefreshInd(USIMM_CCB_GetMainAppType(),pstMsg);
    }
    else
    {
        (VOS_VOID)USIMM_RefreshNoReset(pstMsg);

        USIMM_SendRefreshTR(pstMsg, COMMAND_PERFORMED_SUCCESSFULLY);
    }

    USIMM_ResetCnf(pstMsg->stMsgHeader.ulSenderPid, pstMsg->enRefreshType, VOS_OK, gstUSIMMBaseInfo.usSATLen); /*�ظ��������*/

    return VOS_OK;
}
VOS_VOID USIMM_SAT_Fetch(
    VOS_UINT16                          usLen)
{
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulOffset;
    VOS_UINT8                           ucCmdType;
    VOS_UINT8                           ucP3;
    VOS_UINT8                           aucData[USIMM_EF_IMSI_LEN];
    USIMM_POOL_ONERECORD_ST             stRecord;
    USIMM_DEF_FILEID_ENUM_UINT32        enDefFileId;
    USIMM_APDU_HEAD_STRU                stApduHead;
    USIMM_APDU_RSP_STRU                 stRspData;

    /*lint -e534*/
    VOS_MemSet(&stRecord, 0 , sizeof(USIMM_POOL_ONERECORD_ST));
    /*lint +e534*/

    if (USIMM_SAT_STATE_NEEDRESPONSE == gstUSIMMBaseInfo.enSATState)
    {
        USIMM_ERROR_LOG("USIMM_SAT_Fetch: The Last Data Need Response");

        return;
    }

    if (usLen >  0x100)
    {
        gstUSIMMBaseInfo.usSATLen   = 0;

        gstUSIMMBaseInfo.enSATState = USIMM_SAT_STATE_NODATA;

        USIMM_ERROR_LOG("USIMM_SAT_Fetch: The Data Len is Error");

        return;
    }
    else
    {
        ucP3 = (VOS_UINT8)usLen;
    }

    /*lint   -e534 */
    VOS_MemSet(&stApduHead, 0, sizeof(stApduHead));
    /*lint   +e534 */

    stApduHead.ucINS = CMD_INS_FETCH;
    stApduHead.ucP3  = ucP3;

    ulResult = USIMM_SendAPDUHandle(USIMM_APDUCMD_COMMON,
                                    &stApduHead,
                                    VOS_NULL_PTR,
                                    &stRspData);

    if (USIMM_SW_OK != ulResult)/*�жϽ��*/
    {
        USIMM_ERROR_LOG("USIMM_SAT_Fetch: Send APUD Command is Failed");    /*��ӡ����*/

        gstUSIMMBaseInfo.enSATState = USIMM_SAT_STATE_NODATA;

        gstUSIMMBaseInfo.usSATLen   = 0;

        return;
    }

    /*��ѯ��ǰ��������������*/
    ulResult = USIMM_FindTagInSMPTLV(stRspData.aucRsp, USIMM_SATCMD_TAG, usLen);

    if (USIMM_TAGNOTFOUND == ulResult)/*�жϽ��*/
    {
        USIMM_WARNING_LOG("USIMM_SAT_Fetch: The Command Type Tag is Not Founded in the SAT Data ");  /*��ӡ����*/

        gstUSIMMBaseInfo.enSATState = USIMM_SAT_STATE_NODATA;

        gstUSIMMBaseInfo.usSATLen   = 0;

        return;
    }

    ulOffset = USIMM_FindTagInSMPTLV(&stRspData.aucRsp[ulResult + 1], USIMM_CMDDETAIL_TAG,
                                    stRspData.aucRsp[ulResult]);

    if (USIMM_TAGNOTFOUND == ulOffset)/*�жϽ��*/
    {
        USIMM_WARNING_LOG("USIMM_SAT_Fetch: The Command Detail Tag is Not Founded in the SAT Data");    /*��ӡ����*/

        gstUSIMMBaseInfo.enSATState = USIMM_SAT_STATE_NODATA;

        gstUSIMMBaseInfo.usSATLen   = 0;

        return;
    }

    ulOffset += ulResult;

    ucCmdType = stRspData.aucRsp[ulOffset + 3];

    USIMM_INFO_LOG("USIMM_SAT_Fetch: IND SAT Command, Wait Terminal Response");

    gstUSIMMBaseInfo.enSATState = USIMM_SAT_STATE_NEEDRESPONSE;

    USIMM_SatDataInd(ucCmdType, usLen, stRspData.aucRsp); /*�ϱ��������������*/

    gstUSIMMBaseInfo.usSATLen = 0;

    /* ����UICC����ȥ��7F20�µ�IMSI ֻ��ICC���Ź���7F20�µ�IMSI */
    enDefFileId   =   ((USIMM_PHYCARD_TYPE_ICC == USIMM_CCB_GetCardType())?USIMM_GSM_EFIMSI_ID:USIMM_USIM_EFIMSI_ID);

    /* �����0x01 Refresh���������ϱ������ܿ���IMSI�����������Ҫ�����ڴ� */
    if ((USIMM_CARD_SERVIC_AVAILABLE == USIMM_CCB_GetAppService(USIMM_GUTL_APP))
     && (0x01 == ucCmdType))
    {
        if (VOS_OK == USIMM_PoolDelOneFile(EFIMSI, USIMM_GUTL_APP))
        {
            /* ��IMSI */
            if (VOS_OK != USIMM_GetTFByDefFID(USIMM_GUTL_APP,
                                                enDefFileId,
                                                USIMM_READ_ALL_FILE_CONTENT,
                                                aucData))
            {
                USIMM_ERROR_LOG("USIMM_SAT_Fetch: Fail to Read IMSI");

                return;
            }
            stRecord.usEFId     = EFIMSI;
            stRecord.usLen      = USIMM_EF_IMSI_LEN;
            stRecord.enAppType  = USIMM_GUTL_APP;
            stRecord.enFileType = USIMM_EFSTRUCTURE_TRANSPARENT;
            stRecord.pucContent = aucData;

            (VOS_VOID)USIMM_PoolInsertOneFile(&stRecord);
        }
        else
        {
            USIMM_ERROR_LOG("USIMM_SAT_Fetch: Can not find IMSI in Pool");

            return;
        }
    }

    return;
}
VOS_UINT32 USIMM_SAT_Envelope(
    USIMM_CMDHEADER_REQ_STRU            *pMsg)
{
    VOS_UINT32                          ulResult;
    USIMM_STKENVELOPE_REQ_STRU          *pstMsg;
    USIMM_ENVELOPECNF_INFO_STRU         stCnfInfo;
    USIMM_APDU_HEAD_STRU                stApduHead;
    USIMM_U8_LVDATA_STRU                stApduData;
    USIMM_APDU_RSP_STRU                 stRspData;

    /*lint   -e534 */
    VOS_MemSet(&stCnfInfo, 0, sizeof(stCnfInfo));
    /*lint   +e534 */

    pstMsg = (USIMM_STKENVELOPE_REQ_STRU*)pMsg;

    if (VOS_OK != USIMM_ApiParaCheck())
    {
        USIMM_WARNING_LOG("USIMM_SAT_Envelope: USIMM_ApiParaCheck is Failed"); /*��ӡ����*/

        USIMM_EnvelopeCnf(pstMsg->stMsgHeader.ulSenderPid, pstMsg->stMsgHeader.ulSendPara, USIMM_SW_ERR, &stCnfInfo);

        return VOS_ERR;
    }

    stCnfInfo.ucDataType = pstMsg->aucContent[0];

    /*lint  -e534 */
    VOS_MemSet(&stApduHead, 0, sizeof(stApduHead));
    /*lint  +e534 */

    stApduHead.ucINS = CMD_INS_ENVELOPE;

    stApduData.ulDataLen = pstMsg->ucDataLen;
    stApduData.pucData   = pstMsg->aucContent;

    ulResult = USIMM_SendAPDUHandle(USIMM_APDUCMD_COMMON,
                                    &stApduHead,
                                    &stApduData,
                                    &stRspData);  /*������������*/

    stCnfInfo.ucSW1 = stRspData.ucSW1;

    stCnfInfo.ucSW2 = stRspData.ucSW2;

    if (VOS_OK != ulResult)/*�����*/
    {
        USIMM_ERROR_LOG("USIMM_SAT_Envelope: Send APDU Command is Failed");

        USIMM_EnvelopeCnf(pstMsg->stMsgHeader.ulSenderPid, pstMsg->stMsgHeader.ulSendPara, USIMM_SW_SENDCMD_ERROR, &stCnfInfo);

        return VOS_ERR;
    }

    /* ���ENVELOPE�����WARNING */
    if ((0x62 == stRspData.ucApduSW1)||(0x63 == stRspData.ucApduSW1)||(0x9E == stRspData.ucApduSW1))
    {
        stCnfInfo.ucSW1 = stRspData.ucApduSW1;

        stCnfInfo.ucSW2 = stRspData.ucApduSW2;

        if ((USIMM_ENVELOPE_PPDOWN == pstMsg->aucContent[0])
           || (USIMM_ENVELOPE_CBDOWN == pstMsg->aucContent[0]))
        {
            ulResult = USIMM_SW_DOWNLOAD_ERROR;
        }
    }

    stCnfInfo.ulDataLen = stRspData.usRspLen;

    stCnfInfo.pucData   = stRspData.aucRsp;

    USIMM_EnvelopeCnf(pstMsg->stMsgHeader.ulSenderPid, pstMsg->stMsgHeader.ulSendPara, ulResult, &stCnfInfo);

    if (USIMM_SW_OK != ulResult) /*��Ҫ���ؾ���ԭ����ʱ���ش���*/
    {
        USIMM_WARNING_LOG("USIMM_SAT_Envelope: Send APDU Command Result is Failed");

        ulResult = VOS_ERR;
    }

    return ulResult;
}
VOS_UINT32 USIMM_SAT_TerminalResopnse(
    USIMM_CMDHEADER_REQ_STRU            *pMsg)
{
    VOS_UINT32                          ulResult;
    USIMM_TERMINALRESPONSE_REQ_STRU    *pstMsg;
    USIMM_APDU_HEAD_STRU                stApduHead;
    USIMM_U8_LVDATA_STRU                stApduData;
    USIMM_APDU_RSP_STRU                 stRspData;
    USIMM_SAT_STATE_ENUM_UINT32         enSatState;

    pstMsg = (USIMM_TERMINALRESPONSE_REQ_STRU*)pMsg;

    if (VOS_FALSE == USIMM_IsCLEnable())
    {
        if (VOS_OK != USIMM_ApiParaCheck())
        {
            USIMM_WARNING_LOG("USIMM_SAT_TerminalResopnse: USIMM_ApiParaCheck is Failed"); /*��ӡ����*/

            USIMM_TerminalResponseCnf(pstMsg->stMsgHeader.ulSenderPid, USIMM_SW_ERR, pstMsg->stMsgHeader.ulSendPara, 0, 0);

            return VOS_ERR;
        }
    }

    /*lint  -e534 */
    VOS_MemSet(&stApduHead, 0, sizeof(stApduHead));
    /*lint  +e534 */

    stApduHead.ucINS = CMD_INS_TERMINAL_RESPONSE;

    stApduData.ulDataLen = pstMsg->ucDataLen;
    stApduData.pucData   = pstMsg->aucContent;

    enSatState = gstUSIMMBaseInfo.enSATState;
    gstUSIMMBaseInfo.enSATState = USIMM_SAT_STATE_NODATA;

    ulResult = USIMM_SendAPDUHandle(USIMM_APDUCMD_COMMON,
                                    &stApduHead,
                                    &stApduData,
                                    &stRspData);  /*������������*/

    if (VOS_OK != ulResult)/*��鷢�ͽ��*/
    {
        gstUSIMMBaseInfo.enSATState = enSatState;

        USIMM_ERROR_LOG("USIMM_SAT_TerminalResopnse: Send APDU Command is Failed");

        USIMM_TerminalResponseCnf(pstMsg->stMsgHeader.ulSenderPid, USIMM_SW_SENDCMD_ERROR, pstMsg->stMsgHeader.ulSendPara, 0, 0);

        return VOS_ERR;
    }

    USIMM_TerminalResponseCnf(pstMsg->stMsgHeader.ulSenderPid, ulResult, pstMsg->stMsgHeader.ulSendPara, stRspData.ucSW1, stRspData.ucSW2);

    return ulResult;
}
VOS_UINT32  USIMM_PinStatusCheck(
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    USIMM_PIN_CMD_TYPE_ENUM_UINT32      enCmdType,
    USIMM_PIN_TYPE_ENUM_UINT32          enPINType,
    VOS_UINT32                         *pulResult
)
{
    VOS_UINT32                          ulResult;
    USIMM_APP_PIN_INFO_STRU            *pstPin1Info;
    USIMM_APP_PIN_INFO_STRU            *pstPin2Info;

    pstPin1Info = USIMM_CCB_GetPIN1InfoByApp(enAppType);
    pstPin2Info = USIMM_CCB_GetPIN2InfoByApp(enAppType);

    if ((VOS_NULL_PTR == pstPin1Info)
    ||  (VOS_NULL_PTR == pstPin2Info))
    {
        USIMM_ERROR_LOG("USIMM_PinStatusCheck: pstPin1Info is Null Ptr");
        return VOS_ERR;
    }

    switch (enCmdType)
    {
        case USIMM_PINCMD_ENABLE:
            if (USIMM_PIN == enPINType)
            {
                if (USIMM_PUK_NEED == pstPin1Info->enPinVerified)
                {
                    ulResult = VOS_FALSE;
                    *pulResult = USIMM_SIM_PUK_REQUIRED;
                }
                else if (USIMM_PIN_DISABLED == pstPin1Info->enPinEnable)
                {
                    ulResult = VOS_TRUE;
                }
                else
                {
                    ulResult = VOS_FALSE;
                    *pulResult = USIMM_SIM_FAILURE;
                }
            }
            else if (USIMM_PIN2 == enPINType)
            {
                if (USIMM_PUK_NEED == pstPin2Info->enPinVerified)
                {
                    ulResult = VOS_FALSE;
                    *pulResult = USIMM_SIM_PUK2_REQUIRED;
                }
                else if (USIMM_PIN_DISABLED == pstPin2Info->enPinEnable)
                {
                    ulResult = VOS_TRUE;
                }
                else
                {
                    ulResult = VOS_FALSE;
                    *pulResult = USIMM_SIM_FAILURE;
                }
            }
            else
            {
                *pulResult = USIMM_OPERATION_NOT_ALLOW;
                ulResult = VOS_FALSE;
            }
            break;

        case USIMM_PINCMD_VERIFY:
            if (USIMM_PIN == enPINType)
            {
                if (USIMM_PUK_NEED == pstPin1Info->enPinVerified)
                {
                    ulResult = VOS_FALSE;
                    *pulResult = USIMM_SIM_PUK_REQUIRED;
                }
                else if ((USIMM_PIN_DISABLED == pstPin1Info->enPinEnable)
                    ||(USIMM_PIN_NONEED == pstPin1Info->enPinVerified))
                {
                    ulResult = VOS_FALSE;
                    *pulResult = USIMM_OPERATION_NOT_ALLOW;
                }
                else
                {
                    ulResult = VOS_TRUE;
                }
            }
            else if (USIMM_PIN2 == enPINType)
            {
                if (USIMM_PUK_NEED == pstPin2Info->enPinVerified)
                {
                    ulResult = VOS_FALSE;
                    *pulResult = USIMM_SIM_PUK2_REQUIRED;
                }
                else if ((USIMM_PIN_DISABLED == pstPin2Info->enPinEnable)
                    ||(USIMM_PIN_NONEED == pstPin2Info->enPinVerified))
                {
                    ulResult = VOS_FALSE;
                    *pulResult = USIMM_OPERATION_NOT_ALLOW;
                }
                else
                {
                    ulResult = VOS_TRUE;
                }
            }
            else
            {
                *pulResult = USIMM_OPERATION_NOT_ALLOW;
                ulResult = VOS_FALSE;
            }
            break;

        case USIMM_PINCMD_DISABLE:
            if (USIMM_PIN == enPINType)
            {
                if (USIMM_PUK_NEED == pstPin1Info->enPinVerified)
                {
                    ulResult = VOS_FALSE;
                    *pulResult = USIMM_SIM_PUK_REQUIRED;
                }
                else if (USIMM_PIN_ENABLED == pstPin1Info->enPinEnable)
                {
                    ulResult = VOS_TRUE;
                }
                else
                {
                    ulResult = VOS_FALSE;
                    *pulResult = USIMM_SIM_FAILURE;
                }
            }
            else if (USIMM_PIN2 == enPINType)
            {
                if (USIMM_PUK_NEED == pstPin2Info->enPinVerified)
                {
                    ulResult = VOS_FALSE;
                    *pulResult = USIMM_SIM_PUK2_REQUIRED;
                }
                else if (USIMM_PIN_ENABLED == pstPin2Info->enPinEnable)
                {
                    ulResult = VOS_TRUE;
                }
                else
                {
                    ulResult = VOS_FALSE;
                    *pulResult = USIMM_SIM_FAILURE;
                }
            }
            else
            {
                *pulResult = USIMM_OPERATION_NOT_ALLOW;
                ulResult = VOS_FALSE;
            }
            break;
        case USIMM_PINCMD_UNBLOCK:
            if (VOS_TRUE == USIMM_CheckSupportAP())
            {
                ulResult = VOS_TRUE;
            }
            else
            {
                if (USIMM_PIN == enPINType)
                {
                    if (USIMM_PUK_NEED == pstPin1Info->enPinVerified)
                    {
                        ulResult = VOS_TRUE;
                    }
                    else
                    {
                        ulResult = VOS_FALSE;
                        *pulResult = USIMM_OPERATION_NOT_ALLOW;
                    }
                }
                else if (USIMM_PIN2 == enPINType)
                {
                    if (USIMM_PUK_NEED == pstPin2Info->enPinVerified)
                    {
                        ulResult = VOS_TRUE;
                    }
                    else
                    {
                        ulResult = VOS_FALSE;
                        *pulResult = USIMM_OPERATION_NOT_ALLOW;
                    }
                }
                else
                {
                    ulResult = VOS_FALSE;
                    *pulResult = USIMM_OPERATION_NOT_ALLOW;
                }
            }
            break;

        case USIMM_PINCMD_CHANGE:
            if (USIMM_PIN == enPINType)
            {
                if (USIMM_PUK_NEED == pstPin1Info->enPinVerified)
                {
                    ulResult = VOS_FALSE;
                    *pulResult = USIMM_SIM_PUK_REQUIRED;
                }
                else if (USIMM_PIN_ENABLED == pstPin1Info->enPinEnable)
                {
                    ulResult = VOS_TRUE;
                }
                else
                {
                    ulResult = VOS_FALSE;
                    *pulResult = USIMM_SIM_FAILURE;
                }
            }
            else if (USIMM_PIN2 == enPINType)
            {
                if (USIMM_PUK_NEED == pstPin2Info->enPinVerified)
                {
                    ulResult = VOS_FALSE;
                    *pulResult = USIMM_SIM_PUK2_REQUIRED;
                }
                else if (USIMM_PIN_ENABLED == pstPin2Info->enPinEnable)
                {
                    ulResult = VOS_TRUE;
                }
                else
                {
                    ulResult = VOS_FALSE;
                    *pulResult = USIMM_SIM_FAILURE;
                }
            }
            else
            {
                ulResult = VOS_FALSE;
                *pulResult = USIMM_SIM_FAILURE;
            }
            break;
        default:
            *pulResult = USIMM_OPERATION_NOT_ALLOW;
            ulResult = VOS_FALSE;
            break;
    }

    return ulResult;
}

/*****************************************************************************
�� �� ��  : USIMM_PinPreProcHandle
��������  : USIMMģ��PIN��������ϢԤ����
�������  : pstMsg : PIN��������Ϣ
�������  : pstMsg : PIN��������Ϣ
�� �� ֵ  : ��
History     :
1.��    ��  : 2015��01��30��
  ��    ��  : h00300778
  �޸�����  : Create
*****************************************************************************/
VOS_UINT32 USIMM_PinPreProcHandle(
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    USIMM_PINHANDLE_REQ_STRU           *pstMsg
)
{
    VOS_UINT32                          ulResult = VOS_OK;
    VOS_UINT32                          ulServiceStatus;

    /* �����δָʾPIN��������ͣ����ݵ�ǰPIN��״̬�Ͳ�������ת������ */
    if (USIMM_SIM_NON == pstMsg->enPINType)
    {
        ulResult = USIMM_HandlePINType(enAppType, (VOS_UINT8)(pstMsg->enCmdType), &pstMsg->enPINType);
    }

    if (USIMM_PUK == pstMsg->enPINType)
    {
        pstMsg->enPINType = USIMM_PIN;
    }
    else if ( USIMM_PUK2 == pstMsg->enPINType )
    {
        pstMsg->enPINType = USIMM_PIN2;
    }
    else if ((USIMM_PHYCARD_TYPE_ICC== USIMM_CCB_GetCardType())
            &&(USIMM_PIN            == pstMsg->enPINType)
            &&(USIMM_PINCMD_DISABLE == pstMsg->enCmdType))
    {
        if (USIMM_GUTL_APP == enAppType)
        {
            ulServiceStatus = USIMM_IsServiceAvailable(SIM_SVR_CHV1);
        }
        else if (USIMM_CDMA_APP == enAppType)
        {
            ulServiceStatus = USIMM_IsServiceAvailable(UIM_SVR_CHV_DISABLE);
        }
        else
        {
            ulServiceStatus = PS_USIM_SERVICE_NOT_AVAILIABLE;
        }

        if (PS_USIM_SERVICE_NOT_AVAILIABLE == ulServiceStatus)
        {
            return VOS_ERR;
        }
    }
    else
    {
        /*do nothing*/
    }

    return ulResult;
}

/*****************************************************************************
�� �� ��  : USIMM_PinHandleCardStatusCheck
��������  : USIMMģ��PIN��������ǰ��״̬��鴦����
�������  : ��
�������  : ��
�� �� ֵ  : VOS_OK/VOS_ERR
History     :
1.��    ��  : 2015��02��11��
  ��    ��  : h00300778
  �޸�����  : Create
*****************************************************************************/
VOS_UINT32 USIMM_PinHandleCardStatusCheck(
    USIMM_CARDAPP_ENUM_UINT32           enAppType)
{
    VOS_UINT32                          ulUsimmOpenSpeed;

    if (USIMM_PHYCARD_TYPE_NOCARD == USIMM_CCB_GetCardType())
    {
        USIMM_WARNING_LOG("USIMM_PinHandleCardStatusCheck: The Card is not exsit.");

        return USIMM_API_NOTAVAILABLE;
    }

    if (USIMM_CARDAPP_BUTT <= enAppType)
    {
        USIMM_WARNING_LOG("USIMM_PinHandleCardStatusCheck: The App Type is incorrect.");

        return USIMM_API_NOTAVAILABLE;
    }

    ulUsimmOpenSpeed = USIMM_CCB_GetUsimOpenSpeed();

    if ((USIMM_CCB_GetAppService(enAppType) <= USIMM_CARD_SERVIC_UNAVAILABLE)
     || (USIMM_OPENSPEEDENABLE == ulUsimmOpenSpeed)) /*��״̬���*/
    {
        USIMM_WARNING_LOG("USIMM_PinHandleCardStatusCheck: The Card Status is Wrong");

        return USIMM_API_NOTAVAILABLE;
    }

    if (VOS_TRUE == USIMM_VsimIsActive())    /*vSIM���ܴ�*/
    {
        USIMM_WARNING_LOG("USIMM_PinHandleCardStatusCheck: The vSIM is Open");

        return USIMM_API_NOTAVAILABLE;
    }

    return VOS_OK;
}


VOS_VOID USIMM_BuildPrePinInfo(
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    USIMM_PIN_INFO_STRU                *pstPINInfo
)
{
    USIMM_APP_PIN_INFO_STRU            *pstPin1Info;
    USIMM_APP_PIN_INFO_STRU            *pstPin2Info;

    if (VOS_NULL_PTR == pstPINInfo)
    {
        return;
    }

    pstPin1Info = USIMM_CCB_GetPIN1InfoByApp(enAppType);
    pstPin2Info = USIMM_CCB_GetPIN2InfoByApp(enAppType);

    if ((VOS_NULL_PTR == pstPin1Info)
    ||  (VOS_NULL_PTR == pstPin2Info))
    {
        USIMM_ERROR_LOG("USIMM_BuildPrePinInfo: pstPin1Info is Null Ptr");
        return;
    }

    pstPINInfo->ucPin1RemainTime = pstPin1Info->ucPinRemainTime;        /* PIN1��ʣ����� */
    pstPINInfo->ucPin2RemainTime = pstPin2Info->ucPinRemainTime;        /* PIN2��ʣ����� */
    pstPINInfo->ucPuk1RemainTime = pstPin1Info->ucPukRemainTime;        /* PUK1��ʣ����� */
    pstPINInfo->ucPuk2RemainTime = pstPin2Info->ucPukRemainTime;        /* PUK2��ʣ����� */
    pstPINInfo->enPin1Enable     = pstPin1Info->enPinEnable;            /* PIN1����״̬ */
    pstPINInfo->enPin2Enable     = pstPin2Info->enPinEnable;            /* PIN2����״̬ */

    return;
}


VOS_UINT32 USIMM_PINHandle(
    USIMM_CMDHEADER_REQ_STRU            *pMsg)
{
    USIMM_FILEPATH_INFO_STRU            stFilePath;
    VOS_UINT32                          ulResult      = VOS_ERR;
    USIMM_CARDAPP_ENUM_UINT32           enAppType;
    USIMM_PIN_INFO_STRU                 stCnfPinInfo;
    USIMM_PINHANDLE_REQ_STRU           *pstMsg;
    USIMM_APP_PIN_INFO_STRU            *pstPinInfo;

    enAppType = USIMM_CCB_GetMainAppType();

    pstMsg = (USIMM_PINHANDLE_REQ_STRU *)pMsg;

    if (VOS_OK != USIMM_PinHandleCardStatusCheck(enAppType))
    {
        USIMM_ERROR_LOG("USIMM_PINHandle: USIMM_PinHandleCardStatusCheck Failed");

        /*lint -e534*/
        VOS_MemSet(&stCnfPinInfo, 0, sizeof(stCnfPinInfo));
        /*lint +e534*/

        USIMM_PinHandleCnf(pstMsg, VOS_ERR, &stCnfPinInfo);

        return VOS_ERR;
    }

    ulResult = USIMM_PinPreProcHandle(enAppType, pstMsg);

    if (VOS_OK != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_PINHandle: USIMM_PinPreProcHandle Failed");

        USIMM_BuildPrePinInfo(enAppType, &stCnfPinInfo);

        USIMM_PinHandleCnf(pstMsg, VOS_ERR, &stCnfPinInfo);

        return VOS_ERR;
    }

    if (USIMM_PHYCARD_TYPE_UICC == USIMM_CCB_GetCardType())
    {
        /* ѡ��ǰ��Ӧ�õ�APP */
        /*lint -e534*/
        VOS_MemCpy(stFilePath.acPath, USIMM_ADF_STR, VOS_StrLen(USIMM_ADF_STR) + 1);
        /*lint +e534*/
        stFilePath.ulPathLen          =  VOS_StrLen(USIMM_ADF_STR);

        ulResult = USIMM_SelectFile(enAppType, USIMM_NEED_FCP, &stFilePath);
    }
    else
    {
        if (USIMM_GUTL_APP == enAppType)
        {
            /* ѡ��DFGSM */
            ulResult = USIMM_SelectFileByDefFileId(USIMM_UNLIMIT_AUTO, USIMM_NEED_FCP, USIMM_GSM_ID);
        }
        else
        {
            /* ѡ��DFCDMA */
            ulResult = USIMM_SelectFileByDefFileId(USIMM_UNLIMIT_AUTO, USIMM_NEED_FCP, USIMM_CDMA_ID);
        }
    }

    if (ulResult != VOS_OK)/*����ļ���ѡ�н��*/
    {
        USIMM_ERROR_LOG("USIMM_PINHandle: Select Current DF is Failed");

        USIMM_BuildPrePinInfo(enAppType, &stCnfPinInfo);

        USIMM_PinHandleCnf(pstMsg, VOS_ERR, &stCnfPinInfo);

        if (USIMM_SW_SENDCMD_ERROR == ulResult)
        {
            /* ��Ҫ�ϱ���״̬ */
            USIMM_CCB_SetAppService(enAppType,     USIMM_CARD_SERVIC_ABSENT);
            USIMM_CCB_SetAppStateChange(enAppType, USIMM_CARD_STATE_CHANGED);
        }

        return VOS_ERR;
    }

    if (VOS_TRUE != USIMM_PinStatusCheck(enAppType, pstMsg->enCmdType, pstMsg->enPINType, &ulResult))
    {
        USIMM_BuildPrePinInfo(enAppType, &stCnfPinInfo);

        USIMM_PinHandleCnf(pstMsg, ulResult, &stCnfPinInfo);

        return VOS_ERR;
    }

    switch(pstMsg->enCmdType)
    {
        case USIMM_PINCMD_DISABLE:   /*���ȥ�������֤PIN��ͬһ��������*/
        case USIMM_PINCMD_ENABLE:
        case USIMM_PINCMD_VERIFY:
            ulResult = USIMM_PINVerify(enAppType, pstMsg->enPINType, (VOS_UINT8)pstMsg->enCmdType, pstMsg->aucOldPIN);

            /*lint  -e534 */
            VOS_MemCpy(pstMsg->aucNewPIN, pstMsg->aucOldPIN, USIMM_PINNUMBER_LEN);
            /*lint  +e534 */
            break;

        case USIMM_PINCMD_CHANGE:           /*����PIN����*/
            ulResult = USIMM_ChangePIN(enAppType, pstMsg->enPINType, pstMsg->aucOldPIN, pstMsg->aucNewPIN);
            break;

        case USIMM_PINCMD_UNBLOCK:          /*����PIN����*/
            ulResult = USIMM_UnblockPIN(enAppType, pstMsg->enPINType, pstMsg->aucOldPIN, pstMsg->aucNewPIN);
            break;

        default:
            USIMM_WARNING_LOG("USIMM_PINHandle: The CMD Type is Error");
            ulResult = VOS_ERR;
            break;
    }

    if (USIMM_PIN == pstMsg->enPINType)    /*����PIN�����Ľ��*/
    {
        pstPinInfo = USIMM_CCB_GetPIN1InfoByApp(enAppType);

        if (VOS_NULL_PTR == pstPinInfo)
        {
            USIMM_ERROR_LOG("USIMM_PINHandle: pstPin1Info is Null Ptr");
            return VOS_ERR;
        }

        if (VOS_OK == ulResult)
        {
            /* ��¼�ɹ�У�顢ȥ����򼤻���PIN1�� */
            /*lint -e534 */
            VOS_MemCpy(pstPinInfo->aucPin, pstMsg->aucNewPIN, USIMM_PINNUMBER_LEN);
            /*lint +e534 */

            pstPinInfo->ucPINLen = USIMM_PINNUMBER_LEN;

            /* �����ҪPIN��Ĳ��� */
            if (VOS_OK != USIMM_COMM_InitPINApp())
            {
                USIMM_ERROR_LOG("USIMM_PINHandle:USIMM_InitThirdSteps is Failed");

                USIMM_BuildPrePinInfo(enAppType, &stCnfPinInfo);

                USIMM_PinHandleCnf(pstMsg, ulResult, &stCnfPinInfo);

                return VOS_ERR;
            }
        }
        else
        {
            /*lint  -e534 */
            VOS_MemSet(pstPinInfo->aucPin, 0, USIMM_PINNUMBER_LEN);
            /*lint  +e534 */

            pstPinInfo->ucPINLen = 0;
        }
    }

    USIMM_BuildPrePinInfo(enAppType, &stCnfPinInfo);

    USIMM_PinHandleCnf(pstMsg, ulResult, &stCnfPinInfo);

    return VOS_OK;
}
VOS_UINT32 USIMM_CheckChangeCardByICCID(VOS_VOID)
{
    VOS_UINT32                      ulResult;
    VOS_UINT8                       aucOldIccid[20];
    VOS_UINT8                       aucNewIccid[20];


    ulResult = USIMM_PoolReadOneFile(EFICCID, USIMM_READ_ALL_FILE_CONTENT, aucOldIccid, USIMM_UNLIMIT_AUTO);

    if (VOS_OK != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_ProtectReset: USIMM_PoolReadOneFile EFICCID Error");

        return USIMM_COMM_INIT_NORMAL_FAIL;
    }

    /* ��ICCID */
    ulResult = USIMM_GetTFByDefFID(USIMM_UNLIMIT_AUTO,
                                    USIMM_ICCID_ID,
                                    USIMM_READ_ALL_FILE_CONTENT,
                                    aucNewIccid);

    if (VOS_OK != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_ProtectReset: Select EFICCID Error");

        return USIMM_COMM_INIT_NORMAL_FAIL;
    }

    /*lint -e534*/
    if (VOS_OK != VOS_MemCmp(aucOldIccid, aucNewIccid, USIMM_CCB_GetCurEFInfo(USIMM_UNLIMIT_AUTO)->usFileLen))
    {
        USIMM_ERROR_LOG("USIMM_ProtectReset: Not the same ICCID");
    /*lint +e534*/

        return USIMM_COMM_INIT_FATAL_FAIL;
    }

    return USIMM_COMM_INIT_SUCC;
}

/*****************************************************************************
�� �� ��  :USIMM_IccProtectFirstStep
��������  :ICC�������Ը�λ��һ��
�������  :��
�������  :��
�� �� ֵ  :USIMM_INIT_FAIL_CONTINUE/USIMM_INIT_OK

�޶���¼  :
1. ��    ��   : 2015��4��10��
   ��    ��   : h00300778
   �޸�����   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_IccProtectFirstStep(VOS_VOID)
{
    VOS_UINT32                          ulResult;
    VOS_INT32                           lResult;
    VOS_INT32                           lVoltageSwitchRst = USIMM_SCI_NONEED_CHANGEVCC;
    USIMM_FILEPATH_INFO_STRU            stFilePath;
    USIMM_CARDAPP_ENUM_UINT32           enAppType;

    /* ��λ�� */
    if (VOS_OK != mdrv_sci_deact())
    {
        USIMM_ERROR_LOG("USIMM_IccProtectFirstStep: Deactive Card Error");

        return USIMM_COMM_INIT_NORMAL_FAIL;
    }

    ulResult = USIMM_DLResetCard(USIMM_RESET_CARD, &lResult);

    if (VOS_OK != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_IccProtectFirstStep: USIMM_DLResetCard Error");

        return USIMM_COMM_INIT_NORMAL_FAIL;
    }

    enAppType   = USIMM_CCB_GetMainAppType();

    if (USIMM_GUTL_APP == enAppType)
    {
        /*lint -e534*/
        VOS_MemCpy(stFilePath.acPath, USIMM_GSM_STR, VOS_StrLen(USIMM_GSM_STR) + 1);
        /*lint +e534*/
        stFilePath.ulPathLen          =  VOS_StrLen(USIMM_GSM_STR);

        ulResult = USIMM_SelectFile(USIMM_UNLIMIT_AUTO, USIMM_NEED_FCP, &stFilePath);
    }
    else
    {
        /*lint -e534*/
        VOS_MemCpy(stFilePath.acPath, USIMM_CDMA_STR, VOS_StrLen(USIMM_CDMA_STR) + 1);
        /*lint +e534*/
        stFilePath.ulPathLen          =  VOS_StrLen(USIMM_CDMA_STR);

        ulResult = USIMM_SelectFile(USIMM_UNLIMIT_AUTO, USIMM_NEED_FCP, &stFilePath);
    }

    if (VOS_OK != ulResult)
    {
        USIMM_WARNING_LOG("USIMM_IccProtectFirstStep: Select DFGSM/DFCDMA is Failed");     /*��ӡ����*/

        return USIMM_COMM_INIT_NORMAL_FAIL;
    }

    USIMM_SaveDFPinInfo();

    if (0x10 == (USIMM_CCB_GetCurDFInfo(USIMM_UNLIMIT_AUTO)->ucCharaByte & 0x70)) /*SIM�������ļ������ֽ��л���ѹ*/
    {
        USIMM_NORMAL_LOG("USIMM_IccProtectFirstStep: SIM Card Need Change the Voltage.");

        g_stUSIMMInitInfo.stUSIMMInfo.ucVoltageSwitchFlag = VOS_TRUE;

        /*����λʧ�ܰ����޿�����*/
        if (VOS_OK != USIMM_DLResetCard(USIMM_CHANGE_VCC, &lVoltageSwitchRst))
        {
            USIMM_ERROR_LOG("USIMM_Select2GApp:SIM Card Change the Voltage Failed.");

            return USIMM_COMM_INIT_NORMAL_FAIL;      /*����Ҫ�������жϴ���*/
        }

        /* ��ѹδ�л�ֱ�ӷ��� */
        if (USIMM_SCI_NONEED_CHANGEVCC == lVoltageSwitchRst)
        {
            return USIMM_COMM_INIT_NORMAL_FAIL;
        }

        /* ��ѹ�л�����ѡ��һ��DFGSM��DFCDMA */
        ulResult = USIMM_SelectFile(USIMM_UNLIMIT_AUTO, USIMM_NEED_FCP, &stFilePath);

        if (VOS_OK != ulResult)
        {
            USIMM_ERROR_LOG("USIMM_IccProtectFirstStep: Select DFGSM/DFCDMA is Failed");

            return USIMM_COMM_INIT_NORMAL_FAIL;      /*����Ҫ�������жϴ���*/
        }
    }

    return USIMM_COMM_INIT_SUCC;
}

/*****************************************************************************
�� �� ��  :USIMM_IccProtectAutoVerifyPin
��������  :ICC�������Ը�λ�Զ���֤PIN�����
�������  :��
�������  :��
�� �� ֵ  :USIMM_INIT_OK

�޶���¼  :
1. ��    ��   : 2015��4��10��
   ��    ��   : h00300778
   �޸�����   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_IccProtectAutoVerifyPin(VOS_VOID)
{
    USIMM_CARDAPP_ENUM_UINT32           enMainAppType;

    enMainAppType = USIMM_CCB_GetMainAppType();

    (VOS_VOID)USIMM_COMM_AutoVerifyPIN(0);

    if (USIMM_INITSTEPS_SUCCESS == USIMM_COMM_InitAppState(0))
    {
        if (USIMM_CARD_STATE_CHANGED == USIMM_CCB_GetAppStateChange(enMainAppType))
        {
            return USIMM_COMM_INIT_FATAL_FAIL;
        }
    }

    return USIMM_COMM_INIT_SUCC;
}

/*****************************************************************************
�� �� ��  :USIMM_IccProtectProfileDownloadStep
��������  :ICC�������Ը�λ��������PROFILE����
�������  :��
�������  :��
�� �� ֵ  :USIMM_INIT_OK

�޶���¼  :
1. ��    ��   : 2015��4��10��
   ��    ��   : h00300778
   �޸�����   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_IccProtectProfileDownloadStep(VOS_VOID)
{
    USIMM_CARDAPP_ENUM_UINT32           enAppType;
    USIMM_INITAPPLIST_FUNC             *pFuncTbl;

    enAppType       = USIMM_CCB_GetMainAppType();

    /* ��ICC�ĳ�ʼ�����в��ҿ����ϵ�֮��PROFILE DOWNLOAD�Ƿ�ɹ�������ɹ���Ҫ�ٴ��·� */
    pFuncTbl        = USIMM_GetInitFunsByAppType(enAppType, USIMM_ICC_InitTerminalProfile);

    if (USIMM_FUNC_AVAILABLE == pFuncTbl->enStatus)
    {
        (VOS_VOID)USIMM_ICC_InitTerminalProfile(0);
    }

    return USIMM_COMM_INIT_SUCC;
}


/*****************************************************************************
�� �� ��  :USIMM_IccProtectFdnBdnStep
��������  :ICC�������Ը�λ���FDNBDN����
�������  :��
�������  :��
�� �� ֵ  :USIMM_INIT_OK

�޶���¼  :
1. ��    ��   : 2015��4��10��
   ��    ��   : h00300778
   �޸�����   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_IccProtectFdnBdnStep(VOS_VOID)
{

    USIMM_CARDAPP_ENUM_UINT32           enAppType;
    USIMM_INITAPPLIST_FUNC             *pInitFunc = VOS_NULL_PTR;

    enAppType   = USIMM_CCB_GetMainAppType();

    if (USIMM_GUTL_APP == enAppType)
    {
        pInitFunc = USIMM_GetInitFunsByAppType(USIMM_GUTL_APP, USIMM_ICC_InitSimFBDN);

        if (USIMM_FUNC_AVAILABLE == pInitFunc->enStatus)
        {
            (VOS_VOID)USIMM_ICC_InitSimFBDN(0);
        }
    }
    else
    {
        pInitFunc = USIMM_GetInitFunsByAppType(USIMM_CDMA_APP, USIMM_ICC_InitUimFdnBdn);

        if (USIMM_FUNC_AVAILABLE == pInitFunc->enStatus)
        {
            (VOS_VOID)USIMM_ICC_InitUimFdnBdn(0);
        }
    }

    return USIMM_COMM_INIT_SUCC;
}

/*****************************************************************************
�� �� ��  :USIMM_UiccProtectFirstStep
��������  :UICC�������Ը�λ��һ��
�������  :��
�������  :��
�� �� ֵ  :USIMM_INIT_FAIL_CONTINUE/USIMM_INIT_OK

�޶���¼  :
1. ��    ��   : 2015��3��7��
   ��    ��   : h00300778
   �޸�����   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_UiccProtectFirstStep(VOS_VOID)
{
    VOS_UINT32                          ulResult;
    VOS_INT32                           lResult;

    /* ��λ�� */
    if (VOS_OK != mdrv_sci_deact())
    {
        USIMM_ERROR_LOG("USIMM_UiccProtectFirstStep: Deactive Card Error");

        return USIMM_COMM_INIT_NORMAL_FAIL;
    }

    ulResult = USIMM_DLResetCard(USIMM_RESET_CARD, &lResult);

    if (VOS_OK != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_UiccProtectFirstStep: USIMM_DLResetCard Error");

        return USIMM_COMM_INIT_NORMAL_FAIL;
    }

    ulResult = USIMM_SelectFileByDefFileId(USIMM_UNLIMIT_AUTO, USIMM_NEED_FCP, USIMM_MF_ID);

    if (ulResult != VOS_OK)
    {
        USIMM_ERROR_LOG("USIMM_UiccProtectFirstStep: Select MF is Failed");

        return USIMM_COMM_INIT_NORMAL_FAIL;
    }

    ulResult = USIMM_UsimVoltageSwitch(USIMM_CCB_GetCurDFInfo(USIMM_UNLIMIT_AUTO)->ucCharaByte,
                                       &g_stUSIMMInitInfo.stUSIMMInfo.ucVoltageSwitchFlag);

    if (ulResult != VOS_OK)
    {
        USIMM_ERROR_LOG("USIMM_UiccProtectFirstStep: Select MF is Failed");

        return USIMM_COMM_INIT_NORMAL_FAIL;
    }

    USIMM_UsimTerminalCapability();

    return USIMM_COMM_INIT_SUCC;
}

/*****************************************************************************
�� �� ��  :USIMM_UiccProtectProfileDownloadStep
��������  :UICC�������Ը�λ��������PROFILE����
�������  :��
�������  :��
�� �� ֵ  :USIMM_INIT_OK

�޶���¼  :
1. ��    ��   : 2015��4��7��
   ��    ��   : h00300778
   �޸�����   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_UiccProtectProfileDownloadStep(VOS_VOID)
{
    VOS_UINT32                          i;
    USIMM_COMM_CARD_INIT_FUNC           *pInitFunc;

    pInitFunc            =            USIMM_INIT_GetUiccCommInitFunc();
    /* ��UICC�ĳ�ʼ�����в��ҿ����ϵ�֮��PROFILE DOWNLOAD�Ƿ�ɹ���
    ����ɹ���Ҫ�ٴ��·� */
    for (i = 0; i < USIMM_INIT_GetUiccCommInitFuncNum(); i++)
    {
        if ((USIMM_UICC_ProfileDownload == pInitFunc[i].pProcFun)
         && (USIMM_FUNC_AVAILABLE == pInitFunc[i].enStatus))
        {
            (VOS_VOID)USIMM_UICC_ProfileDownload();

            break;
        }
    }

    return USIMM_COMM_INIT_SUCC;
}

/*****************************************************************************
�� �� ��  :USIMM_UiccProtectResumeAppStep
��������  :UICC�������Ը�λ���´��߼�ͨ������ʼ������APP�Ĺ���
�������  :��
�������  :��
�� �� ֵ  :USIMM_INIT_OK

�޶���¼  :
1. ��    ��   : 2015��3��7��
   ��    ��   : h00300778
   �޸�����   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_UiccProtectResumeAppStep(VOS_VOID)
{
    VOS_UINT32                          ulRslt = VOS_OK;
    USIMM_CARDAPP_ENUM_UINT32           enMainAppType;

    /* �Ƚ���Ӧ��ͨ���ϵ�APP�ָ�����Ӧ��ֻ��CDMA��GUTL */
    enMainAppType = USIMM_CCB_GetMainAppType();

    if (USIMM_GUTL_APP == enMainAppType)
    {
        ulRslt = USIMM_UICC_InitUsimADF(0);
    }
    else
    {
        ulRslt = USIMM_UICC_InitCsimADF(0);
    }

    if (USIMM_INITSTEPS_SUCCESS != ulRslt)
    {
        return USIMM_COMM_INIT_NORMAL_FAIL;
    }

    ulRslt = USIMM_UICC_InitPINTime(0);

    if (USIMM_INITSTEPS_SUCCESS != ulRslt)
    {
        return USIMM_COMM_INIT_NORMAL_FAIL;
    }

    (VOS_VOID)USIMM_COMM_AutoVerifyPIN(0);

    if (USIMM_INITSTEPS_SUCCESS == USIMM_COMM_InitAppState(0))
    {
        if (USIMM_CARD_STATE_CHANGED == USIMM_CCB_GetAppStateChange(enMainAppType))
        {
            return USIMM_COMM_INIT_FATAL_FAIL;
        }
    }

    return USIMM_UiccProtectReactiveChannels();
}
/*****************************************************************************
�� �� ��  :USIMM_UiccProtectResumeAppStep
��������  :UICC�������Ը�λ���´��߼�ͨ������ʼ������APP�Ĺ���
�������  :��
�������  :��
�� �� ֵ  :USIMM_INIT_OK

�޶���¼  :
1. ��    ��   : 2015��3��7��
   ��    ��   : h00300778
   �޸�����   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_UiccProtectReactiveChannels(VOS_VOID)
{
    USIMM_UICC_ADF_INFO_STRU           *pstCurAidInfo           = VOS_NULL_PTR;
    USIMM_AID_INFO_STRU                *pstAIDInfo              = VOS_NULL_PTR;
    USIMM_APDU_RSP_STRU                 stApduRsp;
    USIMM_CARDAPP_ENUM_UINT32           enChannelAppType        = USIMM_UNLIMIT_APP_BUTT;
    VOS_UINT32                          ulRslt                  = VOS_OK;
    VOS_UINT8                           ucInvalidChannelNum     = 0;
    VOS_UINT8                           i                       = 0;
    VOS_UINT8                           ucChannelNo             = 0;
    VOS_UINT8                           ucMaxValidChannelNo     = 0;
    VOS_UINT8                           aucInvalidChannel[20]   = {0};


    (VOS_VOID)VOS_MemSet(&stApduRsp, 0, sizeof(USIMM_APDU_RSP_STRU));

    /* �õ������Ч��CHANNEL NUM */
    for (i = USIMM_CHANNEL_NUMBER_MAX - 1; i >= 1; i--)
    {
        if (USIMM_UNLIMIT_APP_BUTT != USIMM_CCB_GetAppTypeByCH(i))
        {
            ucMaxValidChannelNo = i;
            break;
        }
    }

    /* �ж��ǲ��ǵ�ǰ��channel��Ч�������Ч��Ҫopen channel  */
    for (i = 1; i <= ucMaxValidChannelNo; i++)
    {
        if (VOS_OK != USIMM_SendOpenChannelApdu(&ucChannelNo))
        {
            return USIMM_COMM_INIT_NORMAL_FAIL;
        }

        enChannelAppType =  USIMM_CCB_GetAppTypeByCH(ucChannelNo);

        if (USIMM_UNLIMIT_APP_BUTT <= enChannelAppType)
        {
            aucInvalidChannel[ucInvalidChannelNum] = ucChannelNo;
            ucInvalidChannelNum++;
        }
        else if (USIMM_GUTL_APP == enChannelAppType)
        {
            ulRslt = USIMM_UICC_InitUsimADF(ucChannelNo);
        }
        else if (USIMM_CDMA_APP == enChannelAppType)
        {
            ulRslt = USIMM_UICC_InitCsimADF(ucChannelNo);
        }
        else if (USIMM_IMS_APP  == enChannelAppType)
        {
            ulRslt = USIMM_UICC_InitIsimADF(ucChannelNo);
        }
        else
        {
            /* �õ���ǰchannel��AID */
            pstCurAidInfo = USIMM_CCB_GetAdfInfoByCH(ucChannelNo);

            if (VOS_NULL_PTR == pstCurAidInfo)
            {
                USIMM_ERROR_LOG("USIMM_UiccProtectReactiveChannels :pstCurAidInfo is VOS_NULL_PTR ");
                continue;
            }

            /* Select Aid */
            (VOS_VOID)USIMM_SelectAIDFile(ucChannelNo,
                                          USIMM_SELECT_ACTIVATE_AID,
                                          (USIMM_AID_INFO_STRU *)pstAIDInfo,
                                          &stApduRsp);
        }

        if (VOS_OK != ulRslt)
        {
            return USIMM_COMM_INIT_NORMAL_FAIL;
        }
    }

    /* �رն����Channel */
    for (i = 0; i < ucInvalidChannelNum; i++)
    {
        if (USIMM_SW_OK != USIMM_SendCloseChannelApdu(aucInvalidChannel[i]))
        {
            USIMM_ERROR_LOG("USIMM_UiccProtectReactiveChannels:USIMM_SendCloseChannelApdu ERR");
        }
    }

    return USIMM_COMM_INIT_SUCC;
}


PUSIMPROTECTPROC g_astIccProtectResetFuncTbl[] =
{
    USIMM_IccProtectFirstStep,
    USIMM_CheckChangeCardByICCID,
    USIMM_IccProtectAutoVerifyPin,
    USIMM_IccProtectProfileDownloadStep,
    USIMM_IccProtectFdnBdnStep,
};
/*****************************************************************************
�� �� ��  :USIMM_IccProtectResetProc
��������  :ICC�������Ը�λ������
�������  :enCardType:������
�������  :��
�� �� ֵ  :USIMM_INIT_OK/USIMM_INIT_FATAL_EXIT/USIMM_INIT_FAIL_CONTINUE

�޶���¼  :
1. ��    ��   : 2015��4��7��
   ��    ��   : h00300778
   �޸�����   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_IccProtectResetProc(VOS_VOID)
{
    VOS_UINT32                          ulRslt;
    VOS_UINT32                          i;

    for (i = 0; i < ARRAYSIZE(g_astIccProtectResetFuncTbl); i++)
    {
        ulRslt = g_astIccProtectResetFuncTbl[i]();

        if (USIMM_COMM_INIT_SUCC != ulRslt)
        {
            break;
        }
    }

    return ulRslt;
}

PUSIMPROTECTPROC g_astUiccProtectResetFuncTbl[] =
{
    USIMM_UiccProtectFirstStep,
    USIMM_CheckChangeCardByICCID,
    USIMM_UiccProtectProfileDownloadStep,
    USIMM_UiccProtectResumeAppStep,
};

/*****************************************************************************
�� �� ��  :USIMM_UiccProtectResetProc
��������  :UICC�������Ը�λ������
�������  :enCardType:������
�������  :��
�� �� ֵ  :USIMM_INIT_OK/USIMM_INIT_FATAL_EXIT/USIMM_INIT_FAIL_CONTINUE

�޶���¼  :
1. ��    ��   : 2015��4��7��
   ��    ��   : h00300778
   �޸�����   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_UiccProtectResetProc(VOS_VOID)
{
    VOS_UINT32                          ulRslt;
    VOS_UINT32                          i;

    for (i = 0; i < ARRAYSIZE(g_astUiccProtectResetFuncTbl); i++)
    {
        ulRslt = g_astUiccProtectResetFuncTbl[i]();

        if (USIMM_COMM_INIT_SUCC != ulRslt)
        {
            break;
        }
    }

    return ulRslt;
}

/*****************************************************************************
�� �� ��  :USIMM_ProtectResetProc
��������  :�������Ը�λ������
�������  :enCardType:������
�������  :��
�� �� ֵ  :USIMM_INIT_OK/USIMM_INIT_FATAL_EXIT/USIMM_INIT_FAIL_CONTINUE

�޶���¼  :
1. ��    ��   : 2015��4��7��
   ��    ��   : h00300778
   �޸�����   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_ProtectResetProc(
    USIMM_PHYCARD_TYPE_ENUM_UINT32      enCardType)
{
    VOS_UINT32                          ulRslt;

    if (USIMM_PHYCARD_TYPE_UICC == enCardType)
    {
        ulRslt = USIMM_UiccProtectResetProc();
    }
    else
    {
        ulRslt = USIMM_IccProtectResetProc();
    }

    return ulRslt;
}


VOS_UINT32 USIMM_ProtectReset(
    USIMM_CMDHEADER_REQ_STRU            *pstMsg)
{
    VOS_UINT32                          ulResult = VOS_ERR;
    VOS_UINT32                          i;
    USIMM_PHYCARD_TYPE_ENUM_UINT32      enCardType;

    /* ���ٿ���ģʽ */
    if (USIMM_OPENSPEEDENABLE == USIMM_CCB_GetUsimOpenSpeed())/*��״̬���*/
    {
        USIMM_SingleCmdCnf(pstMsg->ulSenderPid,
                           USIMM_PROTECTRESET_CNF,
                           pstMsg->ulSendPara,
                           VOS_ERR,
                           pstMsg->enAppType);

        return VOS_OK;
    }

    /* vSIM���ܴ� */
    if (VOS_TRUE == USIMM_VsimIsActive())
    {
        USIMM_SingleCmdCnf(pstMsg->ulSenderPid,
                           USIMM_PROTECTRESET_CNF,
                           pstMsg->ulSendPara,
                           VOS_ERR,
                           pstMsg->enAppType);

        return VOS_OK;
    }

    /* ��ǰ�Ѿ��޿�����²��������Ը�λ��ֱ�ӻظ�ʧ�� */
    if (VOS_FALSE == USIMM_CCB_IsCardExist())
    {
        USIMM_SingleCmdCnf(pstMsg->ulSenderPid,
                           USIMM_PROTECTRESET_CNF,
                           pstMsg->ulSendPara,
                           VOS_ERR,
                           pstMsg->enAppType);

        return VOS_OK;
    }

    USIMM_NORMAL_LOG("USIMM_ProtectReset: Protect Reset Start");

    /* ���汣���Ը�λ֮ǰ�Ŀ�״̬ */
    enCardType = USIMM_CCB_GetCardType();

    /*�ϱ�SDT*/
    USIMM_ReportEvent(USIMM_PROTECT_RESET);

    for (i = 0; i < USIMM_PROTECT_MAX_NUM; i++)
    {
#if (VOS_OS_VER != VOS_WIN32)       /* PC Stub */
        HPA_USIMLowPowerLock(WUEPS_PID_USIM);
#endif
        (VOS_VOID)VOS_TaskDelay((i*100));

#if (VOS_OS_VER != VOS_WIN32)       /* PC Stub */
        HPA_USIMLowPowerUnLock(WUEPS_PID_USIM);
#endif

        USIMM_ClearCurFileInfo(USIMM_GUTL_APP);
        USIMM_ClearCurFileInfo(USIMM_IMS_APP);
        USIMM_ClearCurFileInfo(USIMM_CDMA_APP);

        USIMM_T1InitGlobalVar();

        ulResult = USIMM_ProtectResetProc(enCardType);

        /* �����Ը�λ�ɹ�������쳣�����˳������Ը�λ���� */
        if ((USIMM_COMM_INIT_SUCC == ulResult)
         || (USIMM_COMM_INIT_FATAL_FAIL == ulResult))
        {
            break;
        }
    }

    if (VOS_OK != ulResult)
    {
        (VOS_VOID)USIMM_DeactiveRealCard((USIMM_MsgBlock *)pstMsg);
#if (FEATURE_ON == FEATURE_PTM)
        USIMM_RecordCardErrorLog(USIMM_MNTN_STATE_POLLING_FAIL, USIMM_MNTN_ERROR_LEVEL_CRITICAL);
#endif
    }

    USIMM_SingleCmdCnf(pstMsg->ulSenderPid, USIMM_PROTECTRESET_CNF, pstMsg->ulSendPara, ulResult, pstMsg->enAppType);

    USIMM_NORMAL_LOG("USIMM_ProtectReset: Protect Reset End");

    return VOS_OK;
}

#if (FEATURE_ON == FEATURE_PTM)
VOS_VOID USIMM_CardErrorLogReport(VOS_VOID)
{
    OM_ERR_LOG_REPORT_CNF_STRU                *pstCnfMsg;

    if (OM_APP_STATUS_CLOSE == g_stErrLogCtrlInfo.ucAlmStatus)
    {
        return;
    }

    /* ������Ϣ�ڴ�  */
    pstCnfMsg = (OM_ERR_LOG_REPORT_CNF_STRU*)VOS_AllocMsg(WUEPS_PID_USIM, sizeof(OM_ERR_LOG_REPORT_CNF_STRU)
                                                                          - VOS_MSG_HEAD_LENGTH
                                                                          - 4
                                                                          + sizeof(g_stCardErrorLog));
    if (VOS_NULL_PTR == pstCnfMsg)
    {
        USIMM_ERROR_LOG("USIMM_CardErrorLogReport: VOS_AllocMsg is Failed");

        return;
    }

    /* ���cnf��Ϣ */
    pstCnfMsg->ulReceiverPid    = MSP_PID_DIAG_APP_AGENT;
    pstCnfMsg->ulMsgName        = ID_OM_ERR_LOG_REPORT_CNF;
    pstCnfMsg->ulMsgType        = OM_ERR_LOG_MSG_ERR_REPORT;
    pstCnfMsg->ulRptlen         = sizeof(g_stCardErrorLog);

    /*lint -e419 -e534 */
    VOS_MemCpy(pstCnfMsg->aucContent, &g_stCardErrorLog, sizeof(g_stCardErrorLog));
    /*lint +e419 +e534 */

    /* �ظ���Ϣ */
    (VOS_VOID)VOS_SendMsg(pstCnfMsg->ulSenderPid, pstCnfMsg);

    return;
}
VOS_VOID USIMM_RecordCardErrorLog(
    USIMM_MNTN_STATE_ERROR_REASON_ENUM_UINT32                   enErrorReason,
    USIMM_MNTN_ERROR_LEVEL_ENUM_UINT16                          enAlmLevel)
{
    VOS_INT32       lResult;
    VOS_UINT32      ulLength;

    g_stCardErrorLog.stHeader.ulMsgModuleId = OM_ERR_LOG_MOUDLE_ID_USIMM;

#if defined (INSTANCE_1)
    g_stCardErrorLog.stHeader.usModemId = MODEM_ID_1; /* ��ʶ�������� */
#elif defined (INSTANCE_2)
    g_stCardErrorLog.stHeader.usModemId = MODEM_ID_2;
#else
    g_stCardErrorLog.stHeader.usModemId = MODEM_ID_0;
#endif

    g_stCardErrorLog.stHeader.usAlmId = 1;
    g_stCardErrorLog.stHeader.usAlmLevel = enAlmLevel;
    g_stCardErrorLog.stHeader.usAlmType = 0;        /* 0����ͨ�Ÿ澯 */
    g_stCardErrorLog.stHeader.usAlmLowSlice = OM_GetSlice();
    g_stCardErrorLog.stHeader.usAlmHighSlice = 0;   /* ��ʱ���ã�Ĭ����0 */

    g_stCardErrorLog.enStateErrorReason = enErrorReason;

    /* ���õ���ӿڻ�ȡ������� */
    lResult = mdrv_sci_read_recordlog((VOS_UINT8 *)&g_stCardErrorLog.stSCIRecordInfo,
                                  &ulLength, sizeof(g_stCardErrorLog.stSCIRecordInfo));

    if (VOS_OK != lResult)
    {
        USIMM_ERROR_LOG("USIMM_RecordCardErrorLog: DRV API RETURN ERR");
    }

    g_stCardErrorLog.stHeader.ulAlmLength = sizeof(VOS_UINT32) + sizeof(SCI_RECORD_INFO_S) + sizeof(g_stCardErrorLog.aulRsv);

    return;
}
#endif



VOS_UINT32 USIMM_StatusHandle(
    USIMM_CMDHEADER_REQ_STRU            *pMsg)
{
    VOS_UINT32                          ulResult = VOS_ERR;
    USIMM_STATUSCMD_REQ_STRU           *pstMsg;

    pstMsg = (USIMM_STATUSCMD_REQ_STRU *)pMsg;

    if (VOS_OK != USIMM_ApiParaCheck())
    {
        USIMM_SingleCmdCnf(pMsg->ulSenderPid,
                           USIMM_STATUSCMD_CNF,
                           pMsg->ulSendPara,
                           ulResult,
                           pMsg->enAppType);

        return ulResult;
    }

    if (pstMsg->enNeedFcp == USIMM_POLL_NEED_FCP)
    {
        ulResult = USIMM_STATUSProc();
    }
    else
    {
        ulResult = USIMM_SendStatusApdu(USIMM_APDU_BASECHANNEL,
                                        USIMM_STATUS_NO_INDICATION,
                                        USIMM_STATUS_NO_DATA_RETURNED,
                                        VOS_NULL);

        if (VOS_OK != ulResult)
        {
            /* ICCIDƥ��͵�STATUS������ICCID��ƥ�䣬���������Ը�λ���� */
            if (USIMM_COMM_INIT_SUCC != USIMM_CheckChangeCardByICCID())
            {
                ulResult = USIMM_SW_SENDCMD_ERROR;
            }
            else
            {
                ulResult = USIMM_SW_OK;
            }
        }
    }

    USIMM_SingleCmdCnf(pMsg->ulSenderPid,
                       USIMM_STATUSCMD_CNF,
                       pMsg->ulSendPara,
                       ulResult,
                       pMsg->enAppType);

    return ulResult;
}
VOS_UINT32 USIMM_UpdateFile(
    USIMM_EF_TYPE_ENUM_UINT32           enEFFileType,
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    VOS_UINT8                           ucRecordNum,
    VOS_UINT16                          usDataLen,
    VOS_UINT8                          *pucData)
{
    VOS_UINT32                              ulResult;
    VOS_UINT8                               ucChannelID;

    ucChannelID = USIMM_CCB_GetAppChNO(enAppType);

    if (VOS_NULL_BYTE == ucChannelID)
    {
        USIMM_ERROR_LOG("USIMM_UpdateFile:USIMM_CCB_GetAppChNO error");

        return USIMM_SW_ERR;
    }

    switch (enEFFileType)
    {
        case USIMM_EFSTRUCTURE_TRANSPARENT:

            /*���¶������ļ�*/
            ulResult = USIMM_SendUpdateBinaryApdu(ucChannelID, usDataLen, pucData);
            break;

        case USIMM_EFSTRUCTURE_FIXED:

            /*���¼�¼�ļ�*/
            ulResult = USIMM_SendUpdateRecordApdu(ucChannelID,
                                                  USIMM_RECORD_ABSOLTE,
                                                  ucRecordNum,
                                                  pucData,
                                                  (VOS_UINT8)usDataLen);
            break;

        case USIMM_EFSTRUCTURE_CYCLE:

            /*����ѭ���ļ�*/
            ulResult = USIMM_SendUpdateRecordApdu(ucChannelID,
                                                   USIMM_RECORD_PREVIOUS,
                                                   VOS_NULL,
                                                   pucData,
                                                   (VOS_UINT8)usDataLen);
            break;

        default:
            USIMM_WARNING_LOG("USIMM_SetFileHandle: The File Type is Not Support");
            ulResult = USIMM_SW_FILETYPE_ERROR;
            break ;
    }

    return ulResult;
}
VOS_UINT32 USIMM_SelectFile
(
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    USIMM_FILE_NEED_FCP_ENUM_UINT32     enEfFcpFlag,
    USIMM_FILEPATH_INFO_STRU           *pstFilePath
)
{
    VOS_UINT16                          ausFilePath[USIMM_MAX_PATH_LEN] = {0};
    VOS_UINT32                          ulPathLen = 0;
    VOS_UINT32                          ulResult;
    VOS_UINT16                          usIsDF;
    VOS_UINT16                          usCurPathLen;
    USIMM_SELECT_PARA_STUR              stSelectPara;
    USIMM_U16_LVDATA_STRU               stFilePath;
    VOS_UINT16                          usFileLen;

    /* ������� */
    if (VOS_NULL_PTR == pstFilePath)
    {
        USIMM_ERROR_LOG("USIMM_SelectFile:Input Parameter error.");

        return USIMM_SW_ERR;
    }

    if (USIMM_PHYCARD_TYPE_NOCARD == USIMM_CCB_GetCardType())
    {
        USIMM_ERROR_LOG("USIMM_SelectFile:PHY Card Type error.");

        return USIMM_SW_OTHER_ERROR;
    }

    if (VOS_NULL_BYTE == USIMM_CCB_GetAppChNO(enAppType))
    {
        USIMM_ERROR_LOG("USIMM_SelectFile:App Type Service is absent.");

        return USIMM_SW_OTHER_ERROR;
    }

    /*lint -e732*/
    ulResult = VOS_MemCmp((VOS_CHAR *)USIMM_MF_STR,
                          (VOS_CHAR *)pstFilePath->acPath,
                          VOS_StrLen(USIMM_MF_STR));
    /*lint -e732*/

    if (VOS_OK != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_SelectFile: No MF.");

        return USIMM_SW_OTHER_ERROR;
    }

    if (VOS_OK != USIMM_StrToFilePath(pstFilePath, ausFilePath, &ulPathLen))
    {
        USIMM_ERROR_LOG("USIMM_SelectFile:USIMM_StrToFilePath error.");

        return USIMM_SW_OTHER_ERROR;
    }

    /* ѡ���ļ��Ѿ��ǵ�ǰ�ļ����˳������سɹ� */
    ulResult = USIMM_CardFilePathCMP(ulPathLen,
                                     ausFilePath,
                                     USIMM_CCB_GetCurFileInfo(enAppType)->usFilePathLen,
                                     USIMM_CCB_GetCurFileInfo(enAppType)->ausFilePath);

    if (VOS_OK == ulResult)
    {
        usIsDF    = USIMM_IS_DF_FILE(ausFilePath[ulPathLen - 1]);

        usFileLen = USIMM_CCB_GetCurEFInfo(enAppType)->usFileLen;

        if ((VOS_TRUE           == usIsDF)
         || (0                  != usFileLen)
         || (USIMM_NO_NEED_FCP  == enEfFcpFlag))
        {
            USIMM_INFO_LOG("USIMM_SelectFile: Selected file is current file.");

            return USIMM_SW_OK;
        }
    }

    stSelectPara.enCardType     = USIMM_CCB_GetCardType();
    stSelectPara.enEfFcpFlag    = enEfFcpFlag;
    stSelectPara.enAppType      = enAppType;

    stFilePath.pusData          = ausFilePath;
    stFilePath.ulDataLen        = ulPathLen;

    /* ͨ��ȫ·��ѡ���ļ� */
    ulResult = USIMM_SelectFileWithPath(&stSelectPara,
                                        &stFilePath,
                                        USIMM_CCB_GetCurFileInfo(enAppType),
                                        &usCurPathLen);

    if (VOS_NULL == usCurPathLen)
    {
        USIMM_ClearCurFileInfo(enAppType);
    }
    else
    {
        stFilePath.ulDataLen = usCurPathLen;

        /* ����·�� */
        USIMM_UpdateFilePath(&stSelectPara, &stFilePath, USIMM_CCB_GetCurFileInfo(enAppType));
    }

    return ulResult;
}


VOS_UINT32 USIMM_CheckSetFilePara(
    USIMM_EFFCP_ST                      *pstCurEFFcp,
    VOS_UINT8                           ucRecordNum,
    VOS_UINT16                          usDataLen)
{
    VOS_UINT32                          ulResult = USIMM_SW_OK;

    switch (pstCurEFFcp->enFileType)
    {
        case USIMM_EFSTRUCTURE_TRANSPARENT:
            /*�����������Ƿ����*/
            if (pstCurEFFcp->usFileLen < usDataLen)
            {
                USIMM_ERROR_LOG("USIMM_CheckSetFilePara: The Length of Data is too Large to the File");

                ulResult = USIMM_SW_OUTOF_RANGE;
            }

            break;

        case USIMM_EFSTRUCTURE_FIXED:
            /*�����µļ�¼���Ƿ�Խ��*/
            if (pstCurEFFcp->ucRecordNum < ucRecordNum)
            {
                USIMM_ERROR_LOG("USIMM_CheckSetFilePara: The Record Index of Data is Out of File Range");

                ulResult = USIMM_SW_OUTOF_RANGE;
            }

            break;

        case USIMM_EFSTRUCTURE_CYCLE:
            ulResult = USIMM_SW_OK;
            break;

        default:
            USIMM_WARNING_LOG("USIMM_CheckSetFilePara: The File Type is Not Support");
            ulResult = USIMM_SW_CMD_ERROR;
            break;
    }

    return ulResult;
}


VOS_UINT32 USIMM_SetIsimFileHandle(
    USIMM_UPDATEFILE_REQ_STRU           *pstUpdateMsg,
    VOS_UINT16                          usEFID)
{
    VOS_UINT32                          ulResult = VOS_OK;
    USIMM_DEF_FILEID_ENUM_UINT32        enIsimFileId;
    USIMM_DEF_FILEID_ENUM_UINT32        enUsimFileId;
    VOS_CHAR                           *pcPathStr;
    USIMM_UPDATEFILE_REQ_STRU           stUpdateMsg;

    /*lint -e419 -e534 */
    VOS_MemCpy((VOS_UINT8 *)&stUpdateMsg, (VOS_UINT8 *)pstUpdateMsg, sizeof(stUpdateMsg));
    /*lint +e419 +e534 */

    /* ��ǰISIM�����񲻿��� */
    if (USIMM_CARD_SERVIC_AVAILABLE != USIMM_CCB_GetAppService(USIMM_IMS_APP))
    {
        USIMM_WARNING_LOG("USIMM_SetIsimFileHandle: ISIM app unavailable");

        return USIMM_SW_ERR;
    }

    /* �鿴��ǰ�Ƿ���USIMģ��ISIM */
    if (VOS_TRUE == USIMM_CCB_GetUsimSimulateIsimStatus())
    {
        if (VOS_OK != USIMM_ChangePathToDefFileID(stUpdateMsg.stMsgHeader.enAppType,
                                                  stUpdateMsg.stFilePath.ulPathLen,
                                                  stUpdateMsg.stFilePath.acPath,
                                                  &enIsimFileId))
        {
            /* �ļ����ɸ��� */
            USIMM_WARNING_LOG("USIMM_ChangePathToDefFileID: ISIM file can't find.");

            return USIMM_SW_NOFILE_FOUND;
        }

        /* ����ISIM�ļ�ID���Ҷ�Ӧ��USIM�ļ�ID �Ҳ�����Ӧ��USIM�ļ�ID����Ϊ�ļ����ɸ��� */
        enUsimFileId = USIMM_IsimEFIDToUsimEFID(enIsimFileId);

        /* �Ҳ�����Ӧ��USIM�ļ�ID */
        if (VOS_NULL_WORD == enUsimFileId)
        {
            /* �ļ����ɸ��� */
            USIMM_WARNING_LOG("USIMM_SetIsimFileHandle: ISIM file can't write.");

            return USIMM_SW_NOFILE_FOUND;
        }

        if (VOS_OK != USIMM_ChangeDefFileToPath(enUsimFileId, &pcPathStr))
        {
            /* �ļ����ɸ��� */
            USIMM_WARNING_LOG("USIMM_SetIsimFileHandle: USIMM_ChangeDefFileToPath fail");

            return USIMM_SW_NOFILE_FOUND;
        }

        stUpdateMsg.stFilePath.ulPathLen = VOS_StrLen(pcPathStr);

        /*lint -e534*/
        VOS_MemCpy(stUpdateMsg.stFilePath.acPath, pcPathStr, stUpdateMsg.stFilePath.ulPathLen + 1);
        /*lint +e534*/

        if (USIMM_EF_FILE != USIMM_GetFileIDFromStr(&(stUpdateMsg.stFilePath), &usEFID))
        {
            /* �ļ����ɸ��� */
            USIMM_WARNING_LOG("USIMM_SetIsimFileHandle: USIMM_GetEFileIDFromStr fail");

            return USIMM_SW_NOFILE_FOUND;
        }

        /* ��USIM�ļ�id�����ļ� */
        stUpdateMsg.stMsgHeader.enAppType = USIMM_GUTL_APP;
    }

    /* ����USIM�ӿڸ���USIM�ļ� */
    ulResult = USIMM_SetFileCommHandle(&stUpdateMsg, usEFID);

    return ulResult;
}


VOS_UINT32 USIMM_SetRealFile(
    USIMM_UPDATEFILE_REQ_STRU           *pstUpdateMsg,
    VOS_UINT16                          usEFID)
{
    VOS_UINT32                          ulResult;
    USIMM_SETCNF_INFO_STRU              stCnfInfo;

    /*lint  -e534 */
    VOS_MemSet(&stCnfInfo, 0, sizeof(stCnfInfo));
    /*lint  +e534 */

    stCnfInfo.ucRecordNum  = pstUpdateMsg->ucRecordNum;
    stCnfInfo.usEFLen      = pstUpdateMsg->usDataLen;
    stCnfInfo.usEfid       = usEFID;

    /* ִ��ISIM�����ļ� */
    if (USIMM_IMS_APP == pstUpdateMsg->stMsgHeader.enAppType)
    {
        ulResult = USIMM_SetIsimFileHandle(pstUpdateMsg, usEFID);
    }
    else
    {
        ulResult = USIMM_SetFileCommHandle(pstUpdateMsg, usEFID);
    }

    USIMM_SetFileCnf(pstUpdateMsg, ulResult, &stCnfInfo); /*�ظ����½��*/

    return ulResult;
}


VOS_UINT32 USIMM_GetFileFromCard(
    USIMM_GET_COMM_FILE_STRU           *pstFileInfo,
    USIMM_GETCNF_INFO_STRU             *pstCnfInfo)
{
    VOS_UINT32                          ulResult;

    ulResult = USIMM_SelectFile(pstFileInfo->enAppType,
                                USIMM_NEED_FCP,
                                &pstFileInfo->stFilePath);

    if (VOS_OK != ulResult) /*�ļ�ѡ��ʧ��*/
    {
        USIMM_ERROR_LOG("USIMM_GetFileFromCard: Select File is Failed");

        return ulResult;
    }

    /* ��ȡҪ�����ļ�������stCnfInfo�ṹ����usEfLen, usDataLen, ucRecordNum, ucTotalNum��ֵ */
    ulResult = USIMM_GetReadFilePara(pstFileInfo->ucRecordNum,
                                     USIMM_CCB_GetCurEFInfo(pstFileInfo->enAppType),
                                     pstCnfInfo);

    /* ��ȡ���ļ�����ʧ�� */
    if (VOS_OK != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_GetFileFromCard: Get file para Failed");

        return ulResult;
    }

    /*�ⲿ����Ҫ��ոò��������������ε���*/
    if (VOS_NULL_PTR == pstCnfInfo->pucEf)
    {
        pstCnfInfo->pucEf = (VOS_UINT8 *)VOS_MemAlloc(WUEPS_PID_USIM, DYNAMIC_MEM_PT, pstCnfInfo->usDataLen);
    }

    if (VOS_NULL_PTR == pstCnfInfo->pucEf)/*��鷵��ֵ*/
    {
        USIMM_ERROR_LOG("USIMM_GetFileFromCard: VOS_MemAlloc is Error");

        return USIMM_SW_ERR;
    }

    ulResult = USIMM_ReadFile(pstFileInfo->enAppType,
                              USIMM_CCB_GetCurEFInfo(pstFileInfo->enAppType),
                              pstCnfInfo);

    return ulResult;
}
VOS_UINT32 USIMM_GetFileCommHandle(
    USIMM_READFILE_REQ_STRU            *pstReadMsg,
    USIMM_GETCNF_INFO_STRU             *pstCnfInfo,
    VOS_UINT16                          usEFID
)
{
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulFileNum;
    USIMM_GET_COMM_FILE_STRU            stFileInfo;
    USIMM_GETCNF_INFO_STRU              stCnfInfo;
    USIMM_READFILE_REQ_STRU             stReadMsg;

    /*lint -e534*/
    VOS_MemSet(&stCnfInfo, 0, sizeof(stCnfInfo));
    VOS_MemSet(&stFileInfo, 0, sizeof(stFileInfo));
    VOS_MemCpy((VOS_UINT8*)&stReadMsg, (VOS_UINT8*)pstReadMsg, sizeof(stReadMsg));
    /*lint +e534*/

    if (VOS_TRUE == pstReadMsg->bNeedReadCache)
    {
        if (USIMM_SW_OK == USIMM_PoolFindFile(usEFID, &ulFileNum, pstReadMsg->stMsgHeader.enAppType))
        {
            USIMM_INFO_LOG("USIMM_GetFileCommHandle: Get File Success from Usimm Pool");

            pstCnfInfo->pucEf = (VOS_UINT8 *)VOS_MemAlloc(WUEPS_PID_USIM,
                                                          DYNAMIC_MEM_PT,
                                                          USIMM_CCB_GetPoolFileByIndex(ulFileNum)->usLen);

            if (VOS_NULL_PTR == pstCnfInfo->pucEf)/*��鷵��ֵ*/
            {
                USIMM_ERROR_LOG("USIMM_GetFileCommHandle: VOS_MemAlloc is Error");

                return USIMM_SW_ERR;
            }

            /*lint -e534*/
            VOS_MemCpy(pstCnfInfo->pucEf,
                       USIMM_CCB_GetPoolFileByIndex(ulFileNum)->pucContent,
                       USIMM_CCB_GetPoolFileByIndex(ulFileNum)->usLen);
            /*lint +e534*/

            pstCnfInfo->usDataLen    = USIMM_CCB_GetPoolFileByIndex(ulFileNum)->usLen;
            pstCnfInfo->usEfLen      = USIMM_CCB_GetPoolFileByIndex(ulFileNum)->usLen;

            return USIMM_SW_OK;
        }
    }

    stFileInfo.enAppType   = pstReadMsg->stMsgHeader.enAppType;
    stFileInfo.ucRecordNum = pstReadMsg->ucRecordNum;

    /*lint -e534*/
    VOS_MemCpy(&stFileInfo.stFilePath, &(pstReadMsg->stFilePath), sizeof(pstReadMsg->stFilePath));
    /*lint +e534*/

    ulResult = USIMM_GetFileFromCard(&stFileInfo, &stCnfInfo);

    /*����ļ����ش�����Ҫ����һ��*/
    if ((USIMM_SW_FILETYPE_ERROR    == ulResult)
      ||(USIMM_SW_NOFILE_FOUND      == ulResult)
      ||(USIMM_SW_NOFILE_SELECT     == ulResult))
    {
        USIMM_ClearCurEFInfo(USIMM_CCB_GetCurFileInfo(pstReadMsg->stMsgHeader.enAppType));

        ulResult = USIMM_GetFileFromCard(&stFileInfo, &stCnfInfo);
    }

    /* �����������ֵ */
    /*lint -e534*/
    VOS_MemCpy(pstCnfInfo, &stCnfInfo, sizeof(stCnfInfo));
    /*lint +e534*/

    return ulResult;
}
VOS_UINT32 USIMM_GetIsimIMPI(
    USIMM_GETCNF_INFO_STRU              *pstCnfInfo)
{
    VOS_UINT8                           aucAsciiImsi[USIMM_EF_IMSI_LEN*2];
    VOS_UINT32                          ulAsciiImsiLen;
    VOS_UINT8                           aucAsciiMCC[4];
    VOS_UINT8                           aucAsciiMNC[4];
    VOS_UINT32                          ulResult;
    VOS_UINT8                           aucStr[] = "@ims.mnc000.mcc000.3gppnetwork.org";
    VOS_UINT32                          ulStrLen;
    VOS_UINT32                          ulFileLen;

    ulResult = USIMM_ImsiBcd2Ascii(aucAsciiImsi);

    if (USIMM_SW_OK != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_GetIsimIMPI: decode imsi fail.");

        return USIMM_SW_ERR;
    }

    USIMM_GetAsciiMCCAndMNC(aucAsciiImsi, aucAsciiMCC, aucAsciiMNC);

    /* ��Э��23.003 13.3��ʾ������imsi���� */
    /* �ļ����ݸ�ʽΪ"<IMSI>@ims.mnc<MNC>.mcc<MCC>.3gppnetwork.org" */
    ulStrLen = VOS_StrLen((VOS_CHAR *)aucStr);
    ulAsciiImsiLen = VOS_StrLen((VOS_CHAR *)aucAsciiImsi);

    /* ǰ2���ֽ�ΪTL�ֶ� */
    ulFileLen = 2 + ulStrLen + ulAsciiImsiLen;

    pstCnfInfo->pucEf = (VOS_UINT8 *)VOS_MemAlloc(WUEPS_PID_USIM, DYNAMIC_MEM_PT, ulFileLen);

    if (VOS_NULL_PTR == pstCnfInfo->pucEf)
    {
        USIMM_ERROR_LOG("USIMM_GetIsimIMPI:VOS_MemAlloc is Error");

        return USIMM_SW_ERR;
    }

    /* copy mnc */
    /*lint  -e534 */
    VOS_MemCpy(aucStr + 8, aucAsciiMNC, USIMM_MNC_MCC_FIG_NUM);
    /*lint +e534*/

    /* copy mcc */
    /*lint -e534*/
    VOS_MemCpy(aucStr + 15, aucAsciiMCC, USIMM_MNC_MCC_FIG_NUM);
    /*lint  +e534 */

    pstCnfInfo->pucEf[0] = USIMM_ISIM_FILE_TAG;
    pstCnfInfo->pucEf[1] = (VOS_UINT8)(ulFileLen - 2);

    /* copy imsi */
    /*lint -e534 */
    VOS_MemCpy(&(pstCnfInfo->pucEf[2]), aucAsciiImsi, ulAsciiImsiLen);

    VOS_MemCpy(&(pstCnfInfo->pucEf[2]) + ulAsciiImsiLen, aucStr, ulStrLen);
    /*lint +e534 */

    pstCnfInfo->usEfLen   = (VOS_UINT16)ulFileLen;

    pstCnfInfo->usDataLen = (VOS_UINT16)ulFileLen;

    return USIMM_SW_OK;
}


VOS_UINT32 USIMM_GetIsimIMPU(
    USIMM_GETCNF_INFO_STRU              *pstCnfInfo)
{
    VOS_UINT8                           aucAsciiImsi[USIMM_EF_IMSI_LEN*2] = {0};
    VOS_UINT32                          ulAsciiImsiLen;
    VOS_UINT8                           aucAsciiMCC[4];
    VOS_UINT8                           aucAsciiMNC[4];
    VOS_UINT32                          ulResult;
    VOS_UINT8                           aucStr1[] = "sip:";
    VOS_UINT32                          ulStr1Len;
    VOS_UINT8                           aucStr2[] = "@ims.mnc000.mcc000.3gppnetwork.org";
    VOS_UINT32                          ulStr2Len;
    VOS_UINT32                          ulFileLen;

    ulResult = USIMM_ImsiBcd2Ascii(aucAsciiImsi);

    if (USIMM_SW_OK != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_GetIsimIMPI: decode imsi fail.");

        return USIMM_SW_ERR;
    }

    USIMM_GetAsciiMCCAndMNC(aucAsciiImsi, aucAsciiMCC, aucAsciiMNC);

    /* ��Э��23.003 13.4B��ʾ�������ļ����� */
    /* �ļ���ʽΪ"sip : <IMSI>@ims.mnc<MNC>.mcc<MCC>.3gppnetwork.org"*/
    ulStr1Len = VOS_StrLen((VOS_CHAR *)aucStr1);
    ulStr2Len = VOS_StrLen((VOS_CHAR *)aucStr2);
    ulAsciiImsiLen = VOS_StrLen((VOS_CHAR *)aucAsciiImsi);

    /* ǰ2���ֽ�ΪTL�ֶ� */
    ulFileLen = 2 + ulStr1Len + ulAsciiImsiLen + ulStr2Len;

    pstCnfInfo->pucEf = (VOS_UINT8 *)VOS_MemAlloc(WUEPS_PID_USIM, DYNAMIC_MEM_PT, ulFileLen);

    if (VOS_NULL_PTR == pstCnfInfo->pucEf)
    {
        USIMM_ERROR_LOG("USIMM_GetIsimIMPU:VOS_MemAlloc is Error");

        return USIMM_SW_ERR;
    }

    /* copy mnc */
    /*lint  -e534 */
    VOS_MemCpy(aucStr2 + 8, aucAsciiMNC, USIMM_MNC_MCC_FIG_NUM);
    /*lint +e534*/

    /* copy mcc */
    /*lint -e534*/
    VOS_MemCpy(aucStr2 + 15, aucAsciiMCC, USIMM_MNC_MCC_FIG_NUM);
    /*lint  +e534 */

    pstCnfInfo->pucEf[0] = USIMM_ISIM_FILE_TAG;
    pstCnfInfo->pucEf[1] = (VOS_UINT8)(ulFileLen - 2);

    /*lint  -e534 */
    VOS_MemCpy(&(pstCnfInfo->pucEf[2]), aucStr1, ulStr1Len);

    VOS_MemCpy(&(pstCnfInfo->pucEf[2]) + ulStr1Len, aucAsciiImsi, ulAsciiImsiLen);

    VOS_MemCpy(&(pstCnfInfo->pucEf[2]) + ulStr1Len + ulAsciiImsiLen, aucStr2, ulStr2Len);
    /*lint +e534 */

    pstCnfInfo->usEfLen = (VOS_UINT16)ulFileLen;

    pstCnfInfo->usDataLen = (VOS_UINT16)ulFileLen;

    return USIMM_SW_OK;
}
VOS_UINT32 USIMM_GetIsimDOMAIN(
    USIMM_GETCNF_INFO_STRU              *pstCnfInfo)
{
    VOS_UINT8                           aucAsciiImsi[USIMM_EF_IMSI_LEN*2] = {0};
    VOS_UINT8                           aucAsciiMCC[4] = {0};
    VOS_UINT8                           aucAsciiMNC[4] = {0};
    VOS_UINT32                          ulResult;
    VOS_UINT8                           aucStr[] = "ims.mnc000.mcc000.3gppnetwork.org";
    VOS_UINT32                          ulFileLen;

    ulResult = USIMM_ImsiBcd2Ascii(aucAsciiImsi);

    if (USIMM_SW_OK != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_GetIsimIMPI: decode imsi fail.");

        return USIMM_SW_ERR;
    }

    USIMM_GetAsciiMCCAndMNC(aucAsciiImsi, aucAsciiMCC, aucAsciiMNC);

    /* ��Э��23.003 13.2��ʾ�������ļ����� */
    /* �ļ���ʽΪ"ims.mnc<MNC>.mcc<MCC>.3gppnetwork.org" */
    /* ǰ2���ֽ�ΪTL�ֶ� */
    ulFileLen = 2 + VOS_StrLen((VOS_CHAR *)aucStr);

    pstCnfInfo->pucEf = (VOS_UINT8 *)VOS_MemAlloc(WUEPS_PID_USIM, DYNAMIC_MEM_PT, ulFileLen);

    if (VOS_NULL_PTR == pstCnfInfo->pucEf)
    {
        USIMM_ERROR_LOG("USIMM_GetIsimDOMAIN:VOS_MemAlloc is Error");

        return USIMM_SW_ERR;
    }

    /* copy mnc */
    /*lint  -e534 */
    VOS_MemCpy((aucStr + 7), aucAsciiMNC, USIMM_MNC_MCC_FIG_NUM);
    /*lint +e534*/

    /* copy mcc */
    /*lint -e534*/
    VOS_MemCpy((aucStr + 14), aucAsciiMCC, USIMM_MNC_MCC_FIG_NUM);
    /*lint  +e534 */

    pstCnfInfo->pucEf[0] = USIMM_ISIM_FILE_TAG;
    pstCnfInfo->pucEf[1] = (VOS_UINT8)(ulFileLen - 2);

    /*lint  -e534 */
    VOS_MemCpy(&(pstCnfInfo->pucEf[2]), (VOS_UINT8 *)aucStr, ulFileLen);
    /*lint  +e534 */

    pstCnfInfo->usEfLen = (VOS_UINT16)ulFileLen;

    pstCnfInfo->usDataLen = (VOS_UINT16)ulFileLen;

    return USIMM_SW_OK;
}
VOS_UINT32 USIMM_GetIsimIST(
    USIMM_GETCNF_INFO_STRU              *pstCnfInfo)
{
    VOS_UINT32                          i;
    VOS_UINT32                          j;
    VOS_UINT8                           ucSVRContent = 0;
    VOS_UINT16                          usFileLen;
    /*lint -e656*/
    VOS_UINT8                           aucSVRBit[ISIM_SVR_BUTT - USIM_SVR_BUTT];
    /*lint +e656*/
    VOS_UINT32                          ulArrayIndex;

    /*lint -e656*/
    usFileLen = ((ISIM_SVR_BUTT - USIM_SVR_BUTT) + USIMM_BIT_NUM_IN_BYTE - 1) / USIMM_BIT_NUM_IN_BYTE;
    /*lint +e656*/

    for (i = ISIM_SVR_PCSCF_ADDR; i < ISIM_SVR_BUTT; i++)
    {
        /* ���ýӿڻ�ȡ����λ״̬ */
        aucSVRBit[i - ISIM_SVR_PCSCF_ADDR] = (VOS_UINT8)USIMM_IsISIMServiceAvailable(i);
    }

    pstCnfInfo->pucEf = (VOS_UINT8 *)VOS_MemAlloc(WUEPS_PID_USIM, DYNAMIC_MEM_PT, usFileLen);

    if (VOS_NULL_PTR == pstCnfInfo->pucEf)
    {
        USIMM_ERROR_LOG("USIMM_GetIsimIST:VOS_MemAlloc is Error");

        return USIMM_SW_ERR;
    }

    for (i = 0; i < usFileLen; i++)
    {
        ucSVRContent = 0;

        for (j = 0; j < USIMM_BIT_NUM_IN_BYTE; j++)
        {
            ulArrayIndex = (i*USIMM_BIT_NUM_IN_BYTE + j);

            /*lint -e656 -e701*/
            if (ulArrayIndex < (ISIM_SVR_BUTT - USIM_SVR_BUTT))
            {
                ucSVRContent = (VOS_UINT8)(ucSVRContent | ((aucSVRBit[ulArrayIndex] & 0x1) << j));
            }
            /*lint +e656 +e701*/
        }

        pstCnfInfo->pucEf[i] = ucSVRContent;
    }

    pstCnfInfo->usEfLen = usFileLen;

    pstCnfInfo->usDataLen = usFileLen;

    return USIMM_SW_OK;
}
VOS_UINT32 USIMM_GetIsimFileHandle(
    USIMM_READFILE_REQ_STRU            *pstReadMsg,
    USIMM_GETCNF_INFO_STRU             *pstCnfInfo,
    VOS_UINT16                          usEFID)
{
    VOS_UINT32                          ulResult = VOS_OK;
    USIMM_DEF_FILEID_ENUM_UINT32        enIsimFileId;
    USIMM_DEF_FILEID_ENUM_UINT32        enUsimFileId;
    VOS_CHAR                           *pcPathStr;
    USIMM_READFILE_REQ_STRU             stReadMsg;

    /*lint -e419 -e534 */
    VOS_MemCpy((VOS_UINT8 *)&stReadMsg, (VOS_UINT8 *)pstReadMsg, sizeof(stReadMsg));
    /*lint +e419 +e534 */

    /* ��ǰISIM�����񲻿��� */
    if (USIMM_CARD_SERVIC_AVAILABLE != USIMM_CCB_GetAppService(USIMM_IMS_APP))
    {
        USIMM_WARNING_LOG("USIMM_GetIsimFileHandle: ISIM app unavailable");

        return USIMM_SW_ERR;
    }

    /* �鿴��ǰ�Ƿ���USIMģ��ISIM */
    if (VOS_TRUE == USIMM_CCB_GetUsimSimulateIsimStatus())
    {
        if (EFISIMIMPI == usEFID)
        {
            return USIMM_GetIsimIMPI(pstCnfInfo);
        }

        if (EFISIMDOMAIN == usEFID)
        {
            return USIMM_GetIsimDOMAIN(pstCnfInfo);
        }

        if (EFISIMIMPU == usEFID)
        {
            return USIMM_GetIsimIMPU(pstCnfInfo);
        }

        if (EFISIMIST == usEFID)
        {
            return USIMM_GetIsimIST(pstCnfInfo);
        }

        if (VOS_OK != USIMM_ChangePathToDefFileID(stReadMsg.stMsgHeader.enAppType,
                                                  stReadMsg.stFilePath.ulPathLen,
                                                  stReadMsg.stFilePath.acPath,
                                                  &enIsimFileId))
        {
            /* �ļ����ɸ��� */
            USIMM_WARNING_LOG("USIMM_ChangePathToDefFileID: ISIM file can't find.");

            return USIMM_SW_NOFILE_FOUND;
        }

        /* �����ļ�����ISIM�ļ�ID���Ҷ�Ӧ��USIM�ļ�ID �Ҳ�����Ӧ��USIM�ļ�ID����Ϊ�ļ����ɶ�ȡ */
        enUsimFileId = USIMM_IsimEFIDToUsimEFID(enIsimFileId);

        /* �Ҳ�����Ӧ��USIM�ļ�ID */
        if (VOS_NULL_WORD == enUsimFileId)
        {
            /* �ļ����ɶ�ȡ */
            USIMM_WARNING_LOG("USIMM_GetIsimFileHandle: ISIM file can't read");

            return USIMM_SW_NOFILE_FOUND;
        }

        if (VOS_OK != USIMM_ChangeDefFileToPath(enUsimFileId, &pcPathStr))
        {
            USIMM_WARNING_LOG("USIMM_GetIsimFileHandle: USIMM_ChangeDefFileToPath fail");

            return USIMM_SW_NOFILE_FOUND;
        }

        stReadMsg.stFilePath.ulPathLen = VOS_StrLen(pcPathStr);

        /*lint -e534*/
        VOS_MemCpy(stReadMsg.stFilePath.acPath, pcPathStr, stReadMsg.stFilePath.ulPathLen + 1);
        /*lint +e534*/

        if (USIMM_EF_FILE != USIMM_GetFileIDFromStr(&(stReadMsg.stFilePath), &usEFID))
        {
            USIMM_WARNING_LOG("USIMM_GetIsimFileHandle: USIMM_GetEFileIDFromStr fail");

            return USIMM_SW_NOFILE_FOUND;
        }

        stReadMsg.stMsgHeader.enAppType = USIMM_GUTL_APP;
    }

    /* ����USIM�ӿڶ�ȡUSIM�ļ� */
    ulResult = USIMM_GetFileCommHandle(&stReadMsg, pstCnfInfo, usEFID);

    return ulResult;

}
VOS_UINT32 USIMM_GetRealFile(
    USIMM_READFILE_REQ_STRU             *pstReadMsg,
    VOS_UINT16                          usEFID)
{
    VOS_UINT32                          ulResult;
    USIMM_GETCNF_INFO_STRU              stCnfInfo;

    /*lint -e534*/
    VOS_MemSet(&stCnfInfo, 0, sizeof(stCnfInfo));
    /*lint +e534*/

    if (USIMM_IMS_APP == pstReadMsg->stMsgHeader.enAppType)
    {
        ulResult = USIMM_GetIsimFileHandle(pstReadMsg, &stCnfInfo, usEFID);
    }
    else
    {
        ulResult = USIMM_GetFileCommHandle(pstReadMsg, &stCnfInfo, usEFID);
    }

    stCnfInfo.usEfId           = usEFID;

    USIMM_GetFileCnf(pstReadMsg, ulResult, &stCnfInfo);

    if (VOS_NULL_PTR != stCnfInfo.pucEf)
    {
        /*lint -e534*/
        VOS_MemFree(WUEPS_PID_USIM, stCnfInfo.pucEf);
        /*lint +e534*/
    }

    return ulResult;
}


VOS_UINT32 USIMM_RAccessPathHandle(
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    VOS_UINT16                          usFileID,
    VOS_UINT8                           ucPathLen,
    VOS_UINT16                         *pusPath,
    USIMM_RESTRIC_CMD_ENUM_UINT32       ulCmdType)
{
    VOS_UINT16                          ausFilePath[USIMM_MAX_PATH_LEN];
    VOS_UINT32                          ulResult;
    USIMM_FILEPATH_INFO_STRU            stFilePath;
    VOS_UINT32                          i;
    VOS_UINT8                           aucPath[USIMM_MAX_PATH_LEN*2];

    if ((ucPathLen + 1) > USIMM_MAX_PATH_LEN)
    {
        USIMM_ERROR_LOG("USIMM_RAccessPathHandle: The File Path Len is error");

        return USIMM_SW_ERR;
    }

    /* GET RESPONSE��������ļ���Ϣ��ȷ���ļ���������ѡ�� */
    if (USIMM_GET_RESPONSE == ulCmdType)
    {
        USIMM_ClearCurFileInfo(enAppType);
    }

    /* AT����������а��ļ�·����������ƴ���ļ�·����ѡ���ļ���
       ���û���ļ�·����ֱ�Ӱ��ļ�IDѡ�ļ� */
    if (0 != ucPathLen)
    {
        /* �����ļ�·�� */
        /*lint  -e534 */
        VOS_MemCpy(ausFilePath, pusPath, ucPathLen*sizeof(VOS_UINT16));
        /*lint  +e534 */
    }

    /* �����ļ�ID */
    ausFilePath[ucPathLen] = usFileID;
    ucPathLen++;

    for (i = 0; i < ucPathLen; i++)
    {
        aucPath[i*2] = (VOS_UINT8)((ausFilePath[i]>>0x08)&0x00FF);

        aucPath[(i*2)+1] = (VOS_UINT8)(ausFilePath[i]&0x00FF);
    }

    /* ��·��ѡ���ļ���·��������Ҫ��1�����ļ�ID���� */
    USIMM_ChangePathToAsciiString(aucPath,
                                  (VOS_UINT8)(ucPathLen*sizeof(VOS_UINT16)),
                                 &stFilePath);

    ulResult = USIMM_SelectFile(enAppType, USIMM_NEED_FCP, &stFilePath);

    return ulResult;
}
VOS_UINT32 USIMM_AccessCmdHandle(
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    USIMM_RESTRIC_CMD_ENUM_UINT32       enCmdType,
    USIMM_APDU_HEAD_STRU               *pstApduHead,
    USIMM_U8_LVDATA_STRU               *pstApduData,
    VOS_UINT32                         *pulNeedCopy
)
{
    USIMM_APDU_RSP_STRU                 stRspData;
    VOS_UINT32                          ulResult = USIMM_SW_OK;

    pstApduHead->ucChannel      = USIMM_CCB_GetAppChNO(enAppType);

    switch (enCmdType)
    {
        case USIMM_READ_BINARY:
            pstApduHead->ucINS  = CMD_INS_READ_BINARY;
            *pulNeedCopy        = VOS_YES;                  /* ��������Ҫ���� */
            ulResult            = USIMM_SendAPDUHandle(USIMM_APDUCMD_COMMON,
                                                        pstApduHead,
                                                        VOS_NULL_PTR,
                                                        &stRspData);
            break;

        case USIMM_READ_RECORD:
            pstApduHead->ucINS  = CMD_INS_READ_RECORD;
            *pulNeedCopy        = VOS_YES;                  /* ��������Ҫ���� */
            ulResult            = USIMM_SendAPDUHandle(USIMM_APDUCMD_COMMON,
                                                        pstApduHead,
                                                        VOS_NULL_PTR,
                                                        &stRspData);
            break;

        case USIMM_UPDATE_BINARY:
            pstApduHead->ucINS  = CMD_INS_UPDATE_BINARY;
            ulResult            = USIMM_SendAPDUHandle(USIMM_APDUCMD_COMMON,
                                                        pstApduHead,
                                                        pstApduData,
                                                        &stRspData);
            break;

        case USIMM_UPDATE_RECORD:
            pstApduHead->ucINS  = CMD_INS_UPDATE_RECORD;
            ulResult            = USIMM_SendAPDUHandle(USIMM_APDUCMD_COMMON,
                                                        pstApduHead,
                                                        pstApduData,
                                                        &stRspData);
            break;

        case USIMM_STATUS:
            pstApduHead->ucINS  = CMD_INS_STATUS;
            *pulNeedCopy        = VOS_YES;                                                          /*��������Ҫ����*/
            ulResult            = USIMM_SendAPDUHandle(USIMM_APDUCMD_COMMON,
                                                        pstApduHead,
                                                        VOS_NULL_PTR,
                                                        &stRspData);
            break;

        case USIMM_AUTHENTICATION:
            pstApduHead->ucINS  = CMD_INS_AUTHENTICATE;
            *pulNeedCopy        = VOS_YES;
            ulResult            = USIMM_SendAPDUHandle(USIMM_APDUCMD_COMMON,
                                                        pstApduHead,
                                                        pstApduData,
                                                        &stRspData);
            break;

        case USIMM_GET_RESPONSE:
            *pulNeedCopy        = VOS_YES;
            break;

        default:
            ulResult            =  USIMM_SW_SENDCMD_ERROR;
            break;
    }

    return ulResult;
}
VOS_UINT32 USIMM_RAccessHandle(
    USIMM_CMDHEADER_REQ_STRU            *pMsg)
{
    VOS_UINT32                          ulResult            = VOS_OK;
    VOS_UINT32                          ulNeedCopy          = VOS_NO;
    USIMM_RACCESS_REQ_STRU             *pstMsg;
    VOS_UINT8                           ucLen               = 0;
    VOS_UINT8                          *pucContent          = VOS_NULL_PTR;
    NAS_NVIM_SYSTEM_APP_CONFIG_STRU     stSystemAppConfig;
    USIMM_RACCESSCNF_INFO_STRU          stCnfInfo           = {0};
    USIMM_APDU_HEAD_STRU                stApduHead;
    USIMM_U8_LVDATA_STRU                stApduData;

    pstMsg = (USIMM_RACCESS_REQ_STRU *)pMsg;

    if (VOS_OK != USIMM_ApiParaCheck())
    {
        USIMM_RestrictedAccessCnf(pstMsg, VOS_ERR, &stCnfInfo);

        return VOS_ERR;
    }

    stApduHead.ucP1         = pstMsg->ucP1;
    stApduHead.ucP2         = pstMsg->ucP2;
    stApduHead.ucP3         = pstMsg->ucP3;

    stApduData.ulDataLen    = pstMsg->ucP3;
    stApduData.pucData      = pstMsg->aucContent;

    /* �������⿨�����ſ���envelop�������ִ��status�ͻ����֮ǰѡ�е��ļ�δѡ��,
    ״̬�ַ���USIMM_SW_NOFILE_SELECT����ʱ���֮ǰѡ�е��ļ�·��������ѡ���ļ��������ļ���
    ����������������Ҫѭ����ִ��һ�ξ��˳� */

    /*�����ǰ�����ݷ��أ���ô��Ҫ��ձ������ݵ�ȫ�ֱ���*/
    /*lint  -e534 */
    VOS_MemSet(&gstUSIMMAPDU, 0, sizeof(gstUSIMMAPDU));
    /*lint  +e534 */

    if (VOS_NULL_WORD != pstMsg->usEfId)
    {
        ulResult = USIMM_RAccessPathHandle(pstMsg->stMsgHeader.enAppType,
                                           pstMsg->usEfId,
                                           (VOS_UINT8)pstMsg->usPathLen,
                                           pstMsg->ausPath,
                                           pstMsg->enCmdType);
    }

    if (USIMM_SW_OK != ulResult)/*�ж�ѡ����*/
    {
        stCnfInfo.ulErrorCode = ulResult;

        stCnfInfo.ucSW1 = gstUSIMMAPDU.ucSW1;

        stCnfInfo.ucSW2 = gstUSIMMAPDU.ucSW2;

        USIMM_RestrictedAccessCnf(pstMsg,
                                  VOS_OK,
                                  &stCnfInfo);

        return VOS_OK;
    }

    ulResult = USIMM_AccessCmdHandle(pstMsg->stMsgHeader.enAppType,
                                     pstMsg->enCmdType,
                                    &stApduHead,
                                    &stApduData,
                                    &ulNeedCopy);

    if (USIMM_SW_SENDCMD_ERROR == ulResult)/*��鷢�ͽ��*/
    {
        USIMM_ERROR_LOG("USIMM_RAccessHandle: Send Command APDU is Failed");

        stCnfInfo.ulErrorCode = USIMM_SW_SENDCMD_ERROR;

        USIMM_RestrictedAccessCnf(pstMsg, VOS_ERR, &stCnfInfo);

        return VOS_ERR;
    }

    if (USIMM_SW_OK != ulResult)/*�����*/
    {
        USIMM_WARNING_LOG("USIMM_RAccessHandle: The Command Result is Failed");

        ucLen = 0;

        ulNeedCopy = VOS_NO;
    }

    /* ���MP��ANDROID��GET RESPONSE�����P3�����Ĳ��� */
    if (VOS_OK != NV_Read(en_NV_Item_System_APP_Config, &stSystemAppConfig, sizeof(NAS_NVIM_SYSTEM_APP_CONFIG_STRU)))
    {
        stSystemAppConfig.usSysAppConfigType = SYSTEM_APP_MP;
    }

    if (VOS_YES == ulNeedCopy) /*�����ݿ���*/
    {
        ucLen       = (VOS_UINT8)gstUSIMMAPDU.ulRecDataLen;

        pucContent  = &gstUSIMMAPDU.aucRecvBuf[0];

        /* �ڷ�ANDROID�ϣ�����P3����ָ���ĳ��ȡ���ANDROID�Ϸ���ʵ�ʳ��� */
        if ((USIMM_GET_RESPONSE == pstMsg->enCmdType)
            && (SYSTEM_APP_ANDROID != stSystemAppConfig.usSysAppConfigType))
        {
            ucLen = (ucLen > pstMsg->ucP3)?pstMsg->ucP3:ucLen;
        }
    }

    stCnfInfo.ulErrorCode = ulResult;

    stCnfInfo.ucSW1 = gstUSIMMAPDU.ucSW1;

    stCnfInfo.ucSW2 = gstUSIMMAPDU.ucSW2;

    stCnfInfo.ucLen = ucLen;

    stCnfInfo.pContent = pucContent;

    USIMM_RestrictedAccessCnf(pstMsg, VOS_OK, &stCnfInfo);

    return VOS_OK;
}
VOS_UINT32  USIMM_SearchHandle(
    USIMM_SEARCHFILE_REQ_STRU           *pstSearchMsg,
    VOS_UINT16                          usEFID)
{
    VOS_UINT32                          ulResult;
    USIMM_SEARCHCNF_INFO_STRU           stCnfInfo;
    USIMM_APDU_HEAD_STRU                stApduHead;
    USIMM_APDU_RSP_STRU                 stRspData;
    USIMM_U8_LVDATA_STRU                stApduData;
    VOS_UINT8                           ucChannelNo;

    ucChannelNo = USIMM_CCB_GetAppChNO(pstSearchMsg->stMsgHeader.enAppType);

    if (VOS_NULL_BYTE == ucChannelNo)
    {
        USIMM_WARNING_LOG("USIMM_SearchHandle: USIMM_CCB_GetAppChNO Fail");

        return USIMM_SW_ERR;
    }

    /*lint -e534*/
    VOS_MemSet(&stCnfInfo, 0, sizeof(stCnfInfo));
    /*lint +e534*/

    stApduHead.ucChannel    = ucChannelNo;
    stApduHead.ucINS        = CMD_INS_SEARCH_RECORD;

    stCnfInfo.usEfid        = usEFID;

    ulResult = USIMM_SelectFile(pstSearchMsg->stMsgHeader.enAppType,
                                USIMM_NEED_FCP,
                                &(pstSearchMsg->stFilePath)); /*���ö�Ӧ��API*/

    if (VOS_OK != ulResult)
    {
#if (VOS_WIN32 == VOS_OS_VER)
        USIMM_SearchHandleCnf(pstSearchMsg, USIMM_SW_NOFILE_FOUND, &stCnfInfo);
#else
        USIMM_SearchHandleCnf(pstSearchMsg, ulResult, &stCnfInfo);
#endif
        return ulResult;
    }

    if (USIMM_PHYCARD_TYPE_UICC == USIMM_CCB_GetCardType())
    {
        stApduHead.ucP1         = 0x01;
        stApduHead.ucP2         = 0x04;
    }
    else
    {
        stApduHead.ucP1         = 0x00;
        stApduHead.ucP2         = 0x10;
    }

    stApduHead.ucP3         = (VOS_UINT8)(pstSearchMsg->ulDataLen);
    stApduData.ulDataLen    = pstSearchMsg->ulDataLen;
    stApduData.pucData      = pstSearchMsg->aucData;

    ulResult = USIMM_SendAPDUHandle(USIMM_APDUCMD_COMMON,
                                    &stApduHead,
                                    &stApduData,
                                    &stRspData);

    if (VOS_OK != ulResult)
    {
        USIMM_SearchHandleCnf(pstSearchMsg, ulResult, &stCnfInfo);

        return ulResult;
    }

    stCnfInfo.pucData = stRspData.aucRsp;

    stCnfInfo.ulLen   = stRspData.usRspLen;

    stCnfInfo.usTotalRecNum = USIMM_CCB_GetCurEFInfo(pstSearchMsg->stMsgHeader.enAppType)->ucRecordNum; ;

    USIMM_SearchHandleCnf(pstSearchMsg, ulResult, &stCnfInfo);

    return VOS_OK;
}
VOS_UINT32 USIMM_PBInitStatusIndHandle(
    USIMM_CMDHEADER_REQ_STRU            *pMsg)
{
    USIMM_PBINIT_STATUS_IND_STRU       *pstMsg;

    if (VOS_TRUE == USIMM_VsimIsActive())    /*vSIM���ܴ�*/
    {
        USIMM_WARNING_LOG("USIMM_PBInitStatusInd: The vSIM is Open");

        return VOS_OK;
    }

    pstMsg = (USIMM_PBINIT_STATUS_IND_STRU *)pMsg;

    gstUSIMMBaseInfo.stPBInfo.enPBInitStatus = pstMsg->enPBInitStatus;

    /*�绰����ʼ����ɣ����Ա�������*/
    if (USIMM_PB_IDLE == pstMsg->enPBInitStatus)
    {
        USIMM_SaveLogFile();
    }

    return VOS_OK;
}


VOS_UINT32 USIMM_SIMAuthHandle(
    USIMM_AUTHENTICATION_REQ_STRU       *pstMsg)
{
    USIMM_TELECOM_AUTH_INFO_STRU        stCnfInfo;
    USIMM_U8_DATA_STRU                  stData;
    USIMM_APDU_RSP_STRU                 stRspData;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           aucGsmRes[USIMM_2G_AUTH_SRES_LEN + 1];
    VOS_UINT8                           aucGsmKc[USIMM_2G_AUTH_KC_LEN + 1];

    /*lint  -e534 */
    VOS_MemSet(&stCnfInfo,  0, sizeof(stCnfInfo));
    VOS_MemSet(&stData,     0, sizeof(USIMM_U8_DATA_STRU));
    VOS_MemSet(&stRspData,  0, sizeof(USIMM_APDU_RSP_STRU));
    /*lint  +e534 */

    if (USIMM_CARD_SERVIC_ABSENT == USIMM_CCB_GetAppService(USIMM_GUTL_APP))
    {
        USIMM_ERROR_LOG("USIMM_SIMAuthHandle: SIM is disable.");

        stCnfInfo.enResult = USIMM_AUTH_GSM_OTHER_FAILURE;

        USIMM_TelecomAuthCnf(pstMsg, &stCnfInfo);

        return VOS_ERR;
    }

    /* ����Ȩ�����Ƿ���ȷ */
    if (USIMM_2G_AUTH != pstMsg->enAuthType)
    {
        USIMM_ERROR_LOG("USIMM_SIMAuthHandle: enAuthType is incorrcet.");

        stCnfInfo.enResult = USIMM_AUTH_GSM_OTHER_FAILURE;

        USIMM_TelecomAuthCnf(pstMsg, &stCnfInfo);

        return VOS_ERR;
    }

    if (VOS_OK != USIMM_AuthenticationDataFillDataProc(pstMsg, &stData))
    {
        stCnfInfo.enResult = USIMM_AUTH_UMTS_OTHER_FAILURE;

        USIMM_TelecomAuthCnf(pstMsg, &stCnfInfo);

        return VOS_ERR;
    }

    ulResult = USIMM_SelectFileByDefFileId(USIMM_GUTL_APP, USIMM_NEED_FCP, USIMM_GSM_ID);

    if (VOS_OK != ulResult)/*�жϽ��*/
    {
        USIMM_ERROR_LOG("USIMM_USIMAuthHandle: Select ADF Error");

        stCnfInfo.enResult = USIMM_AUTH_GSM_OTHER_FAILURE;

        USIMM_TelecomAuthCnf(pstMsg, &stCnfInfo);

        return VOS_ERR;
    }

    /* GSM��Ȩֻ�·�RAND�����ݣ�û�г�����Ϣ */
    ulResult = USIMM_SendAuthenticationApdu(pstMsg->stMsgHeader.enAppType,
                                            0x0,
                                            USIMM_SIM_2G_AUTH_MODE,
                                            stData.ucDataLen - 1,
                                            stData.aucData + 1,
                                            &stRspData);

    if (VOS_OK != ulResult)
    {
        stCnfInfo.enResult = USIMM_AUTH_GSM_OTHER_FAILURE;

        USIMM_TelecomAuthCnf(pstMsg, &stCnfInfo);

        return VOS_ERR;
    }

    /* SIM����Ȩ��������û�г����ֶΣ���Ҫ��� */
    aucGsmRes[0] = USIMM_2G_AUTH_SRES_LEN;
    /*lint  -e534 */
    VOS_MemCpy(&aucGsmRes[1], &stRspData.aucRsp[0], USIMM_2G_AUTH_SRES_LEN);
    /*lint  +e534 */

    aucGsmKc[0]  = USIMM_2G_AUTH_KC_LEN;
    /*lint  -e534 */
    VOS_MemCpy(&aucGsmKc[1], &stRspData.aucRsp[USIMM_2G_AUTH_SRES_LEN], USIMM_2G_AUTH_KC_LEN);
    /*lint  +e534 */

    stCnfInfo.pucGsmKC   = aucGsmKc;
    stCnfInfo.pucAuthRes = aucGsmRes;

    USIMM_INFO_LOG("USIMM_SIMAuthHandle: SIM Authentication Right");

    stCnfInfo.enResult = USIMM_AUTH_GSM_SUCCESS;

    USIMM_TelecomAuthCnf(pstMsg, &stCnfInfo);

    return VOS_OK;

}


VOS_UINT32 USIMM_USIMAuthHandle(
    USIMM_AUTHENTICATION_REQ_STRU       *pstMsg)
{
    USIMM_TELECOM_AUTH_INFO_STRU        stCnfInfo;
    USIMM_U8_DATA_STRU                  stData;
    USIMM_APDU_RSP_STRU                 stRspData;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucMode;
    VOS_UINT32                          ulOffset = 1;

    /*lint  -e534 */
    VOS_MemSet(&stCnfInfo,  0, sizeof(stCnfInfo));
    VOS_MemSet(&stData,     0, sizeof(USIMM_U8_DATA_STRU));
    VOS_MemSet(&stRspData,  0, sizeof(USIMM_APDU_RSP_STRU));
    /*lint  +e534 */

    if (USIMM_CARD_SERVIC_ABSENT == USIMM_CCB_GetAppService(USIMM_GUTL_APP))
    {
        USIMM_ERROR_LOG("USIMM_USIMAuthHandle: SIM is disable.");

        stCnfInfo.enResult = USIMM_AUTH_UMTS_OTHER_FAILURE;

        USIMM_TelecomAuthCnf(pstMsg, &stCnfInfo);

        return VOS_ERR;
    }

    /* ������Ⲣȷ����Ȩ���ݲ��� */
    if (USIMM_2G_AUTH == pstMsg->enAuthType)
    {
        ucMode = USIMM_USIM_2G_AUTH_MODE;
    }
    else if (USIMM_3G_AUTH == pstMsg->enAuthType)
    {
        ucMode = USIMM_USIM_3G_AUTH_MODE;
    }
    else
    {
        USIMM_ERROR_LOG("USIMM_USIMAuthHandle: enAuthType is incorrect.");

        stCnfInfo.enResult = USIMM_AUTH_UMTS_OTHER_FAILURE;

        USIMM_TelecomAuthCnf(pstMsg, &stCnfInfo);

        return VOS_ERR;
    }

    if (VOS_OK != USIMM_AuthenticationDataFillDataProc(pstMsg, &stData))
    {
        stCnfInfo.enResult = USIMM_AUTH_UMTS_OTHER_FAILURE;

        USIMM_TelecomAuthCnf(pstMsg, &stCnfInfo);

        return VOS_ERR;
    }

    ulResult = USIMM_SelectFileByDefFileId(USIMM_GUTL_APP, USIMM_NEED_FCP, USIMM_USIM_ID);

    if (VOS_OK != ulResult)/*�жϽ��*/
    {
        USIMM_ERROR_LOG("USIMM_USIMAuthHandle: Select ADF Error");

        stCnfInfo.enResult = USIMM_AUTH_UMTS_OTHER_FAILURE;

        USIMM_TelecomAuthCnf(pstMsg, &stCnfInfo);

        return VOS_ERR;
    }

    ulResult = USIMM_SendAuthenticationApdu(pstMsg->stMsgHeader.enAppType,
                                            0x0,
                                            ucMode,
                                            stData.ucDataLen,
                                            stData.aucData,
                                            &stRspData);

    if (USIMM_SW_AUTN_ERROR == ulResult)
    {
        USIMM_WARNING_LOG("USIMM_USIMAuthHandle: SIM Check SW Error");

        stCnfInfo.enResult = USIMM_AUTH_MAC_FAILURE;

        USIMM_TelecomAuthCnf(pstMsg, &stCnfInfo);

        return VOS_ERR;
    }

    if (VOS_OK != ulResult)
    {
        stCnfInfo.enResult = USIMM_AUTH_UMTS_OTHER_FAILURE;

        USIMM_TelecomAuthCnf(pstMsg, &stCnfInfo);

        return VOS_ERR;
    }

    /* ��ǰUSIM����GSM��Ȩ */
    if (USIMM_2G_AUTH == pstMsg->enAuthType)
    {
        stCnfInfo.pucAuthRes = &stRspData.aucRsp[0];

        stCnfInfo.pucGsmKC   = &stRspData.aucRsp[USIMM_2G_AUTH_SRES_LEN + 1];

        USIMM_INFO_LOG("USIMM_USIMAuthHandle: USIM GSM Authentication right");

        stCnfInfo.enResult = USIMM_AUTH_GSM_SUCCESS;

        USIMM_TelecomAuthCnf(pstMsg, &stCnfInfo);

        return VOS_OK;
    }

    /* 3G ��Ȩ�ɹ� */
    if (USIMM_AUTH_SUCCESS_TAG == stRspData.aucRsp[0])
    {
        stCnfInfo.enResult  = USIMM_AUTH_UMTS_SUCCESS;

        stCnfInfo.pucAuthRes = &stRspData.aucRsp[ulOffset]; /*ָ��Res*/

        ulOffset            += stRspData.aucRsp[ulOffset] + 1; /*ָ��CK*/

        stCnfInfo.pucCK     = &stRspData.aucRsp[ulOffset];

        ulOffset            += stRspData.aucRsp[ulOffset] + 1; /*ָ��IK*/

        stCnfInfo.pucIK     = &stRspData.aucRsp[ulOffset];

        ulOffset            += stRspData.aucRsp[ulOffset] + 1; /*ָ�������ܵ�Kc*/

        if (ulOffset < stRspData.ucSW2)
        {
            stCnfInfo.pucGsmKC = &stRspData.aucRsp[ulOffset];

            USIMM_INFO_LOG("USIMM_USIMAuthHandle: USIM 3G Authentication have the KC Data");
        }

        USIMM_INFO_LOG("USIMM_USIMAuthHandle: USIM 3G Authenctication Right");
    }
    else if (USIMM_AUTH_SYNC_FAIL_TAG == stRspData.aucRsp[0]) /* 3G��ͬ�� */
    {
        stCnfInfo.enResult  = USIMM_AUTH_SYNC_FAILURE;

        stCnfInfo.pucAuts   = &stRspData.aucRsp[1];

        USIMM_WARNING_LOG("USIMM_USIMAuthHandle: USIM 3G Authentication Need ReSynchronization");
    }
    else                                                                /*�������ݴ���*/
    {
        USIMM_ERROR_LOG("USIMM_USIMAuthHandle: USIM Authentication Response Data Error");

        stCnfInfo.enResult = USIMM_AUTH_UMTS_OTHER_FAILURE;
    }

    USIMM_TelecomAuthCnf(pstMsg, &stCnfInfo);

    return VOS_OK;
}

/*****************************************************************************
�� �� ��  : USIMM_IsimAuthenticationProc
��������  : ISIM����Ȩ����
�������  : pstMsg:��Ȩ��Ϣ
�������  : ��
�� �� ֵ  : VOS_OK/VOS_ERR
���ú���  :
�޶���¼  :
1. ��    ��   : 2015��04��08��
   ��    ��   : H00300778
   �޸�����   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_IsimAuthenticationProc(
    USIMM_AUTHENTICATION_REQ_STRU       *pstMsg)
{
    USIMM_IMS_AUTH_INFO_STRU            stCnfInfo;
    USIMM_U8_DATA_STRU                  stData;
    USIMM_APDU_RSP_STRU                 stRspData;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucMode;

    /*lint -e534*/
    VOS_MemSet(&stCnfInfo,  0, sizeof(USIMM_IMS_AUTH_INFO_STRU));
    VOS_MemSet(&stData,     0, sizeof(USIMM_U8_DATA_STRU));
    VOS_MemSet(&stRspData,  0, sizeof(USIMM_APDU_RSP_STRU));
    /*lint +e534*/

    if (USIMM_CARD_SERVIC_ABSENT == USIMM_CCB_GetAppService(USIMM_IMS_APP))
    {
        USIMM_ERROR_LOG("USIMM_IsimAuthenticationProc: ISIM is disable.");

        stCnfInfo.enResult = USIMM_AUTH_IMS_OTHER_FAILURE;

        USIMM_ImsAuthCnf(pstMsg, &stCnfInfo);

        return VOS_ERR;
    }

    if (VOS_OK != USIMM_AuthenticationDataFillDataProc(pstMsg, &stData))
    {
        stCnfInfo.enResult = USIMM_AUTH_UMTS_OTHER_FAILURE;

        USIMM_ImsAuthCnf(pstMsg, &stCnfInfo);

        return VOS_ERR;
    }

    ulResult = USIMM_SelectFileByDefFileId(USIMM_IMS_APP, USIMM_NEED_FCP, USIMM_ISIM_ID);

    if (VOS_OK != ulResult)/*�жϽ��*/
    {
        USIMM_ERROR_LOG("USIMM_IsimAuthenticationProc: Select ADF Error");

        stCnfInfo.enResult = USIMM_AUTH_IMS_OTHER_FAILURE;

        USIMM_ImsAuthCnf(pstMsg, &stCnfInfo);

        return VOS_ERR;
    }

    if (USIMM_IMS_AUTH == pstMsg->enAuthType)
    {
        ucMode = USIMM_ISIM_AKA_AUTH_MODE;
    }
    else if ((USIMM_GBA_AUTH == pstMsg->enAuthType) || (USIMM_NAF_AUTH == pstMsg->enAuthType))
    {
        ucMode = USIMM_ISIM_GBA_NAF_AUTH_MODE;
    }
    else
    {
        ucMode = USIMM_ISIM_HTTP_AUTH_MODE;
    }

    ulResult = USIMM_SendAuthenticationApdu(pstMsg->stMsgHeader.enAppType,
                                            0x0,
                                            ucMode,
                                            stData.ucDataLen,
                                            stData.aucData,
                                            &stRspData);

    if (USIMM_SW_AUTN_ERROR == ulResult)
    {
        USIMM_WARNING_LOG("USIMM_IsimAuthenticationProc: SIM Check SW Error");

        stCnfInfo.enResult = USIMM_AUTH_MAC_FAILURE;

        USIMM_ImsAuthCnf(pstMsg, &stCnfInfo);

        return VOS_ERR;
    }

    if (VOS_OK != ulResult)
    {
        stCnfInfo.enResult = USIMM_AUTH_IMS_OTHER_FAILURE;

        USIMM_ImsAuthCnf(pstMsg, &stCnfInfo);

        return VOS_ERR;
    }

    if (USIMM_IMS_AUTH == pstMsg->enAuthType)
    {
        USIMM_IsimAkaAuthRspProc(pstMsg, &stRspData);
    }
    else if (USIMM_GBA_AUTH == pstMsg->enAuthType)
    {
        USIMM_IsimGbaAuthRspProc(pstMsg, &stRspData);
    }
    else if (USIMM_NAF_AUTH == pstMsg->enAuthType)
    {
        USIMM_IsimNafAuthRspProc(pstMsg, &stRspData);
    }
    else
    {
        USIMM_IsimHttpAuthRspProc(pstMsg, &stRspData);
    }

    return VOS_OK;
}

/*****************************************************************************
�� �� ��  : USIMM_IsimAkaAuthRspProc
��������  : ISIM��AKA��Ȩ����
�������  : pstMsg:��Ȩ��Ϣ
            ptRspData:��Ȩ��Ӧ����
�������  : ��
�� �� ֵ  : VOS_OK/VOS_ERR
���ú���  :
�޶���¼  :
1. ��    ��   : 2015��04��08��
   ��    ��   : H00300778
   �޸�����   : Creat
*****************************************************************************/
VOS_VOID USIMM_IsimAkaAuthRspProc(
    USIMM_AUTHENTICATION_REQ_STRU      *pstMsg,
    USIMM_APDU_RSP_STRU                *pstRspData)
{
    USIMM_IMS_AUTH_INFO_STRU            stCnfInfo;
    VOS_UINT32                          ulOffset = 1;

    /*lint -e534*/
    VOS_MemSet(&stCnfInfo,  0, sizeof(USIMM_IMS_AUTH_INFO_STRU));
    /*lint +e534*/

    if (USIMM_AUTH_SUCCESS_TAG == pstRspData->aucRsp[0])
    {
        stCnfInfo.pucAutsRes    = &pstRspData->aucRsp[ulOffset];/*ָ��Res*/

        ulOffset                += pstRspData->aucRsp[ulOffset] + 1;/*ָ��CK*/

        stCnfInfo.pucCK         = &pstRspData->aucRsp[ulOffset];

        ulOffset                += pstRspData->aucRsp[ulOffset] + 1;/*ָ��IK*/

        stCnfInfo.pucIK         = &pstRspData->aucRsp[ulOffset];

        stCnfInfo.enResult      = USIMM_AUTH_IMS_SUCCESS;
    }
    else if (USIMM_AUTH_SYNC_FAIL_TAG == pstRspData->aucRsp[0])
    {
        stCnfInfo.pucAuts  =  &pstRspData->aucRsp[ulOffset];

        stCnfInfo.enResult = USIMM_AUTH_SYNC_FAILURE;
    }
    else
    {
        stCnfInfo.enResult = USIMM_AUTH_IMS_OTHER_FAILURE;
    }

    USIMM_ImsAuthCnf(pstMsg, &stCnfInfo);

    return;
}

/*****************************************************************************
�� �� ��  : USIMM_IsimHttpAuthRspProc
��������  : ISIM��HTTP��Ȩ����
�������  : pstMsg:��Ȩ��Ϣ
            ptRspData:��Ȩ��Ӧ����
�������  : ��
�� �� ֵ  : ��
���ú���  :
�޶���¼  :
1. ��    ��   : 2015��04��08��
   ��    ��   : H00300778
   �޸�����   : Creat
*****************************************************************************/
VOS_VOID USIMM_IsimHttpAuthRspProc(
    USIMM_AUTHENTICATION_REQ_STRU      *pstMsg,
    USIMM_APDU_RSP_STRU                *pstRspData)
{
    USIMM_IMS_AUTH_INFO_STRU            stCnfInfo;
    VOS_UINT32                          ulOffset = 1;

    /*lint -e534*/
    VOS_MemSet(&stCnfInfo,  0, sizeof(USIMM_IMS_AUTH_INFO_STRU));
    /*lint +e534*/

    if (USIMM_AUTH_SUCCESS_TAG == pstRspData->aucRsp[0])
    {
        stCnfInfo.pucResponse   = &pstRspData->aucRsp[ulOffset];     /* ָ��Response */

        ulOffset                += pstRspData->aucRsp[ulOffset] + 1; /* ָ��SessionKey */

        stCnfInfo.pucSessionKey = &pstRspData->aucRsp[ulOffset];

        stCnfInfo.enResult      = USIMM_AUTH_IMS_SUCCESS;
    }
    else
    {
        stCnfInfo.enResult = USIMM_AUTH_IMS_OTHER_FAILURE;
    }

    USIMM_ImsAuthCnf(pstMsg, &stCnfInfo);

    return;
}

/*****************************************************************************
�� �� ��  : USIMM_IsimGbaAuthRspProc
��������  : ISIM��GBA��Ȩ����
�������  : pstMsg:��Ȩ��Ϣ
            ptRspData:��Ȩ��Ӧ����
�������  : ��
�� �� ֵ  : ��
���ú���  :
�޶���¼  :
1. ��    ��   : 2015��04��08��
   ��    ��   : H00300778
   �޸�����   : Creat
*****************************************************************************/
VOS_VOID USIMM_IsimGbaAuthRspProc(
    USIMM_AUTHENTICATION_REQ_STRU      *pstMsg,
    USIMM_APDU_RSP_STRU                *pstRspData)
{
    USIMM_IMS_AUTH_INFO_STRU            stCnfInfo;
    VOS_UINT32                          ulOffset = 1;

    /*lint -e534*/
    VOS_MemSet(&stCnfInfo,  0, sizeof(USIMM_IMS_AUTH_INFO_STRU));
    /*lint +e534*/

    if (USIMM_AUTH_SUCCESS_TAG == pstRspData->aucRsp[0])
    {
        stCnfInfo.pucAutsRes    = &pstRspData->aucRsp[ulOffset];/*ָ��Res*/

        stCnfInfo.enResult      = USIMM_AUTH_IMS_SUCCESS;
    }
    else if (USIMM_AUTH_SYNC_FAIL_TAG == pstRspData->aucRsp[0])
    {
        stCnfInfo.pucAuts  =  &pstRspData->aucRsp[ulOffset];

        stCnfInfo.enResult = USIMM_AUTH_SYNC_FAILURE;
    }
    else
    {
        stCnfInfo.enResult = USIMM_AUTH_IMS_OTHER_FAILURE;
    }

    USIMM_ImsAuthCnf(pstMsg, &stCnfInfo);

    return;
}

/*****************************************************************************
�� �� ��  : USIMM_IsimNafAuthRspProc
��������  : ISIM��NAF��Ȩ����
�������  : pstMsg:��Ȩ��Ϣ
            ptRspData:��Ȩ��Ӧ����
�������  : ��
�� �� ֵ  : ��
���ú���  :
�޶���¼  :
1. ��    ��   : 2015��04��08��
   ��    ��   : H00300778
   �޸�����   : Creat
*****************************************************************************/
VOS_VOID USIMM_IsimNafAuthRspProc(
    USIMM_AUTHENTICATION_REQ_STRU      *pstMsg,
    USIMM_APDU_RSP_STRU                *pstRspData)
{
    USIMM_IMS_AUTH_INFO_STRU            stCnfInfo;
    VOS_UINT32                          ulOffset = 1;

    /*lint -e534*/
    VOS_MemSet(&stCnfInfo,  0, sizeof(USIMM_IMS_AUTH_INFO_STRU));
    /*lint +e534*/

    if (USIMM_AUTH_SUCCESS_TAG == pstRspData->aucRsp[0])
    {
        stCnfInfo.pucKs_ext_NAF = &pstRspData->aucRsp[ulOffset];/*ָ��Res*/

        stCnfInfo.enResult      = USIMM_AUTH_IMS_SUCCESS;
    }
    else
    {
        stCnfInfo.enResult      = USIMM_AUTH_IMS_OTHER_FAILURE;
    }

    USIMM_ImsAuthCnf(pstMsg, &stCnfInfo);

    return;
}
VOS_UINT32 USIMM_ISIMAuthParaCheck(
    USIMM_AUTHENTICATION_REQ_STRU       *pstMsg,
    VOS_UINT8                           *pucMode)
{
    VOS_UINT32                          ulIMSSVR;

    /* ����AKA��Ȩ��ISIM��USIM��ͬ����USIMģ��IMS�������ֱ���·���Ȩ��
    �����ж�95�ŷ���λ��������Ȩ��Ҫ�ж� */
    if (USIMM_IMS_AUTH == pstMsg->enAuthType)
    {
        *pucMode = USIMM_USIM_3G_AUTH_MODE;

        return VOS_OK;
    }

    /* ����USIM����ӿڣ��ж�USIM���Ƿ�֧��IMS */
    ulIMSSVR = USIMM_IsUSIMServiceAvailable(USIM_SVR_ACCESS_IMS);

    if (PS_USIM_SERVICE_AVAILIABLE != ulIMSSVR)
    {
        return VOS_ERR;
    }

    if ((USIMM_GBA_AUTH == pstMsg->enAuthType) || (USIMM_NAF_AUTH == pstMsg->enAuthType))
    {
        *pucMode = USIMM_USIM_GBA_AUTH_MODE;

        return VOS_OK;
    }

    return VOS_ERR;
}
VOS_UINT32 USIMM_ISIMAuthHandle(
    USIMM_AUTHENTICATION_REQ_STRU       *pstMsg)
{
    USIMM_IMS_AUTH_INFO_STRU            stCnfInfo;
    USIMM_U8_DATA_STRU                  stData;
    USIMM_APDU_RSP_STRU                 stRspData;
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulOffset = 1;
    VOS_UINT8                           ucMode;

    /*lint  -e534 */
    VOS_MemSet(&stCnfInfo,  0, sizeof(USIMM_IMS_AUTH_INFO_STRU));
    VOS_MemSet(&stData,     0, sizeof(USIMM_U8_DATA_STRU));
    VOS_MemSet(&stRspData,  0, sizeof(USIMM_APDU_RSP_STRU));
    /*lint  +e534 */

    if (USIMM_CARD_SERVIC_ABSENT == USIMM_CCB_GetAppService(USIMM_IMS_APP))
    {
        USIMM_ERROR_LOG("USIMM_ISIMAuthHandle: ISIM is disable.");

        stCnfInfo.enResult = USIMM_AUTH_IMS_OTHER_FAILURE;

        USIMM_ImsAuthCnf(pstMsg, &stCnfInfo);

        return VOS_ERR;
    }

    /* ������Ⲣȷ����Ȩ���ݲ��� */
    if (VOS_OK != USIMM_ISIMAuthParaCheck(pstMsg, &ucMode))
    {
        USIMM_ERROR_LOG("USIMM_ISIMAuthHandle: enAuthType is wrong.");

        stCnfInfo.enResult = USIMM_AUTH_IMS_OTHER_FAILURE;

        USIMM_ImsAuthCnf(pstMsg, &stCnfInfo);

        return VOS_ERR;
    }

    if (VOS_OK != USIMM_AuthenticationDataFillDataProc(pstMsg, &stData))
    {
        stCnfInfo.enResult = USIMM_AUTH_UMTS_OTHER_FAILURE;

        USIMM_ImsAuthCnf(pstMsg, &stCnfInfo);

        return VOS_ERR;
    }

    ulResult = USIMM_SelectFileByDefFileId(USIMM_GUTL_APP, USIMM_NEED_FCP, USIMM_USIM_ID);

    if (VOS_OK != ulResult)/*�жϼ�Ȩ���ͽ��*/
    {
        USIMM_ERROR_LOG("USIMM_ISIMAuthHandle: Select USIM ADF Error");

        stCnfInfo.enResult = USIMM_AUTH_IMS_OTHER_FAILURE;

        USIMM_ImsAuthCnf(pstMsg, &stCnfInfo);

        return VOS_ERR;
    }

    /* ������ͨ��USIM����ģ��ISIM�ļ�Ȩ��APP���ͻ���Ҫ��GUTL */
    ulResult = USIMM_SendAuthenticationApdu(USIMM_GUTL_APP,
                                            0x0,
                                            ucMode,
                                            stData.ucDataLen,
                                            stData.aucData,
                                            &stRspData);

    if (USIMM_SW_AUTN_ERROR == ulResult)
    {
        USIMM_WARNING_LOG("USIMM_ISIMAuthHandle: SIM Check SW Error");

        stCnfInfo.enResult = USIMM_AUTH_MAC_FAILURE;

        USIMM_ImsAuthCnf(pstMsg, &stCnfInfo);

        return VOS_ERR;
    }

    if (VOS_OK != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_ISIMAuthHandle: Send USIM Authentication APDU Error");
        stCnfInfo.enResult = USIMM_AUTH_IMS_OTHER_FAILURE;

        USIMM_ImsAuthCnf(pstMsg, &stCnfInfo);

        return VOS_ERR;
    }

    /* ��Ȩ�ɹ� */
    if (USIMM_AUTH_SUCCESS_TAG == stRspData.aucRsp[0])
    {
        if (USIMM_IMS_AUTH == pstMsg->enAuthType)
        {
            stCnfInfo.pucAutsRes    = &stRspData.aucRsp[ulOffset]; /*ָ��Res*/

            ulOffset                += stRspData.aucRsp[ulOffset] + 1; /*ָ��CK*/

            stCnfInfo.pucCK         = &stRspData.aucRsp[ulOffset];

            ulOffset                += stRspData.aucRsp[ulOffset] + 1; /*ָ��IK*/

            stCnfInfo.pucIK         = &stRspData.aucRsp[ulOffset];
        }
        else if (USIMM_GBA_AUTH == pstMsg->enAuthType)
        {
            stCnfInfo.pucAutsRes    = &stRspData.aucRsp[ulOffset];
        }
        else
        {
            stCnfInfo.pucKs_ext_NAF = &stRspData.aucRsp[ulOffset];
        }

        stCnfInfo.enResult  = USIMM_AUTH_IMS_SUCCESS;

        USIMM_ImsAuthCnf(pstMsg, &stCnfInfo);

        return VOS_OK;
    }

    /* ͬ��ʧ�� */
    if (USIMM_AUTH_SYNC_FAIL_TAG == stRspData.aucRsp[0])
    {
        if ((USIMM_IMS_AUTH == pstMsg->enAuthType) || (USIMM_GBA_AUTH == pstMsg->enAuthType))
        {
            stCnfInfo.pucAuts  = &stRspData.aucRsp[ulOffset];

            stCnfInfo.enResult = USIMM_AUTH_SYNC_FAILURE;

            USIMM_ImsAuthCnf(pstMsg, &stCnfInfo);

            return VOS_ERR;
        }
    }

    stCnfInfo.enResult  = USIMM_AUTH_IMS_OTHER_FAILURE;

    USIMM_ImsAuthCnf(pstMsg, &stCnfInfo);

    return VOS_ERR;
}

/*****************************************************************************
�� �� ��  :USIMM_AuthenticationDataFillDataProc
��������  :ʵ�������⿨��Ȩ�·��ͽ���ظ���
�������  :Э��ջ�·�����Ϣ����
�������  :�õ��ļ�Ȩ����
�� �� ֵ  :VOS_ERR
           VOS_OK

�޶���¼  :
1. ��    ��   : 2015��3��7��
   ��    ��   : h00300778
   �޸�����   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_AuthenticationDataFillDataProc(
    USIMM_AUTHENTICATION_REQ_STRU      *pstMsg,
    USIMM_U8_DATA_STRU                 *pstData)
{
    VOS_UINT32                          ulOffset;
    VOS_UINT32                          ulRslt;

    switch (pstMsg->enAuthType)
    {
        /* �������ݲ���LV��ʽ������ÿ���ֶζ���ҪԤ��һ���ֽڴ�ų��ȣ�������˵����ͬ */
        case USIMM_3G_AUTH:

            if (USIMM_GUTL_APP == pstMsg->stMsgHeader.enAppType)
            {
                /* GUTL���ͼ�Ȩ���ݳ��Ⱦ���RAND�ĳ��Ⱥ�AUTN���ȼ�2 */
                pstData->ucDataLen      = pstMsg->uAuth.st3GAuth.stRand.ucDataLen\
                                        + pstMsg->uAuth.st3GAuth.stAutn.ucDataLen\
                                        + 2;

                /* ���RAND�ĳ��� */
                pstData->aucData[0]     = pstMsg->uAuth.st3GAuth.stRand.ucDataLen;

                /* ����RAND������ */
                /*lint -e534*/
                VOS_MemCpy(pstData->aucData + 1, pstMsg->uAuth.st3GAuth.stRand.aucData, pstData->aucData[0]);
                /*lint +e534*/

                /* ��¼����ƫ���� */
                ulOffset = pstData->aucData[0] + 1;

                /* ���AUTN�ĳ��� */
                pstData->aucData[ulOffset] = pstMsg->uAuth.st3GAuth.stAutn.ucDataLen;

                /* ����AUTN������ */
                /*lint -e534*/
                VOS_MemCpy(pstData->aucData + ulOffset + 1, pstMsg->uAuth.st3GAuth.stAutn.aucData, pstData->aucData[ulOffset]);
                /*lint +e534*/
            }
            else
            {
                /* CDMA��3G��ȨAUTN����Ҫ�����ȣ�RAND����Ҫ������ֻҪ��1 */
                pstData->ucDataLen      = pstMsg->uAuth.st3GAuth.stRand.ucDataLen\
                                        + pstMsg->uAuth.st3GAuth.stAutn.ucDataLen + 1;

                /* ����RAND������ */
                /*lint -e534*/
                VOS_MemCpy(pstData->aucData, pstMsg->uAuth.st3GAuth.stRand.aucData, pstMsg->uAuth.st3GAuth.stRand.ucDataLen);
                /*lint +e534*/

                /* ��¼����ƫ���� */
                ulOffset = pstMsg->uAuth.st3GAuth.stRand.ucDataLen;

                /* ���AUTN�ĳ��� */
                pstData->aucData[ulOffset] = pstMsg->uAuth.st3GAuth.stAutn.ucDataLen;

                /* ����AUTN������ */
                /*lint -e534*/
                VOS_MemCpy(pstData->aucData + ulOffset + 1,
                           pstMsg->uAuth.st3GAuth.stAutn.aucData,
                           pstMsg->uAuth.st3GAuth.stAutn.ucDataLen);
                /*lint +e534*/
            }

            ulRslt = VOS_OK;

            break;

        case USIMM_2G_AUTH:
            /* 2G��Ȩ���ݳ��Ⱦ���RAND�ĳ��ȼ�1 */
            pstData->ucDataLen          = pstMsg->uAuth.st2GAuth.stRand.ucDataLen + 1;

            /* ���RAND������Ϣ */
            pstData->aucData[0]         = pstMsg->uAuth.st2GAuth.stRand.ucDataLen;

            /* ����RAND���� */
            /*lint -e534*/
            VOS_MemCpy(pstData->aucData + 1, pstMsg->uAuth.st2GAuth.stRand.aucData, pstData->aucData[0]);
            /*lint +e534*/

            ulRslt = VOS_OK;

            break;

        case USIMM_IMS_AUTH:
            /* IMS��Ȩ���ݳ��Ⱦ���RAND�ĳ��Ⱥ�AUTN���ȼ�2 */
            pstData->ucDataLen          = pstMsg->uAuth.stImsAuth.stRand.ucDataLen\
                                        + pstMsg->uAuth.stImsAuth.stAutn.ucDataLen\
                                        + 2;

            /* ���RAND������Ϣ */
            pstData->aucData[0] = pstMsg->uAuth.stImsAuth.stRand.ucDataLen;

            /* ����RAND���� */
            /*lint -e534*/
            VOS_MemCpy(pstData->aucData + 1, pstMsg->uAuth.stImsAuth.stRand.aucData, pstData->aucData[0]);
            /*lint +e534*/

            /* ��¼����ƫ���� */
            ulOffset = pstData->aucData[0] + 1;

            /* ���AUTN�ĳ��� */
            pstData->aucData[ulOffset] = pstMsg->uAuth.stImsAuth.stAutn.ucDataLen;

            /* ����AUTN������ */
            /*lint -e534*/
            VOS_MemCpy(pstData->aucData + ulOffset + 1, pstMsg->uAuth.stImsAuth.stAutn.aucData, pstData->aucData[ulOffset]);
            /*lint +e534*/

            ulRslt = VOS_OK;

            break;

        case USIMM_HTTP_AUTH:
            /* HTTP��Ȩ���ݳ��Ⱦ���REALM�ĳ��Ⱥ�NONCE���Ⱥ�CNONCE���ȼ�3 */
            pstData->ucDataLen          = pstMsg->uAuth.stHttpAuth.stRealm.ucDataLen
                                        + pstMsg->uAuth.stHttpAuth.stNonce.ucDataLen
                                        + pstMsg->uAuth.stHttpAuth.stCnonce.ucDataLen
                                        + 3;

            /* ���REALM������Ϣ */
            pstData->aucData[0] = pstMsg->uAuth.stHttpAuth.stRealm.ucDataLen;

            /* ����REALM���� */
            /*lint -e534*/
            VOS_MemCpy(pstData->aucData + 1, pstMsg->uAuth.stHttpAuth.stRealm.aucData, pstData->aucData[0]);
            /*lint +e534*/

            /* ��¼����ƫ���� */
            ulOffset = pstData->aucData[0] + 1;

            /* ���NONCE������Ϣ */
            pstData->aucData[ulOffset] = pstMsg->uAuth.stHttpAuth.stNonce.ucDataLen;

            /* ����NONCE���� */
            /*lint -e534*/
            VOS_MemCpy(pstData->aucData + ulOffset + 1, pstMsg->uAuth.stHttpAuth.stNonce.aucData, pstData->aucData[ulOffset]);
            /*lint +e534*/

            /* ��¼����ƫ���� */
            ulOffset += pstData->aucData[ulOffset] + 1;

            /* ���NONCE������Ϣ */
            pstData->aucData[ulOffset]  = pstMsg->uAuth.stHttpAuth.stCnonce.ucDataLen;

            /* ����NONCE���� */
            /*lint -e534*/
            VOS_MemCpy(pstData->aucData + ulOffset + 1, pstMsg->uAuth.stHttpAuth.stCnonce.aucData, pstData->aucData[ulOffset]);
            /*lint +e534*/

            ulRslt = VOS_OK;

            break;

        case USIMM_GBA_AUTH:
            /* ����GBA��Ȩ��ʽ��ͷ������Ҫ������һ��tag�ֶΣ�����Ҫ��3 */
            pstData->ucDataLen          = pstMsg->uAuth.stGbaAuth.stRand.ucDataLen\
                                        + pstMsg->uAuth.stGbaAuth.stAutn.ucDataLen\
                                        + 3;

            /* ���GBA��Ȩ��TAG */
            pstData->aucData[0]         = USIMM_GBA_AUTH_TAG;

            /* ���RAND������Ϣ */
            pstData->aucData[1]         = pstMsg->uAuth.stGbaAuth.stRand.ucDataLen;

            /* ����RAND���� */
            /*lint -e534*/
            VOS_MemCpy(pstData->aucData + 2, pstMsg->uAuth.stGbaAuth.stRand.aucData, pstData->aucData[1]);
            /*lint +e534*/

            /* ��¼����ƫ���� */
            ulOffset = pstData->aucData[1] + 2;

            /* ���AUTN�ĳ��� */
            pstData->aucData[ulOffset] = pstMsg->uAuth.stGbaAuth.stAutn.ucDataLen;

            /* ����AUTN���� */
            /*lint -e534*/
            VOS_MemCpy(pstData->aucData + ulOffset + 1, pstMsg->uAuth.stGbaAuth.stAutn.aucData, pstData->aucData[ulOffset]);
            /*lint +e534*/

            ulRslt = VOS_OK;

            break;

        case USIMM_NAF_AUTH:

            /* ����NAF��Ȩ��ʽ��ͷ������Ҫ������һ��tag�ֶΣ�����Ҫ��3 */
            pstData->ucDataLen          = pstMsg->uAuth.stNafAuth.stNafID.ucDataLen\
                                        + pstMsg->uAuth.stNafAuth.stImpi.ucDataLen\
                                        + 3;
            /* ���NAF��Ȩ��TAG */
            pstData->aucData[0]         = USIMM_NAF_AUTH_TAG;

            /* ���NAFID������Ϣ */
            pstData->aucData[1]         = pstMsg->uAuth.stNafAuth.stNafID.ucDataLen;

            /* ����NAFID���� */
            /*lint -e534*/
            VOS_MemCpy(pstData->aucData + 2, pstMsg->uAuth.stNafAuth.stNafID.aucData, pstData->aucData[1]);
            /*lint +e534*/

            /* ��¼����ƫ���� */
            ulOffset = pstData->aucData[1] + 2;

            /* ���IMPI�ĳ��� */
            pstData->aucData[ulOffset]= pstMsg->uAuth.stNafAuth.stImpi.ucDataLen;

            /* ����IMPI���� */
            /*lint -e534*/
            VOS_MemCpy(pstData->aucData + ulOffset + 1, pstMsg->uAuth.stNafAuth.stImpi.aucData, pstData->aucData[ulOffset]);
            /*lint +e534*/

            ulRslt = VOS_OK;

            break;

        case USIMM_RUNCAVE_AUTH:
            /* ����RUN CAVE��Ȩ��ʽ���ݳ��ȹ̶���17 */
            pstData->ucDataLen          = USIMM_AUTH_RUNCAVE_LEN;

            pstData->aucData[0]         = pstMsg->uAuth.stRunCaveAuth.ucRandType;

            /* RAND��������ʱ�����ݳ�����4 */
            if (USIMM_RUNCAVE_RAND == pstData->aucData[0])
            {
                /*lint -e534*/
                VOS_MemCpy(pstData->aucData + 1, pstMsg->uAuth.stRunCaveAuth.aucRand, USIMM_RUNCAVE_RAND_LEN);
                /*lint +e534*/
            }
            /* RANDU��������ʱ�����ݳ�����3����һ�ֽڿ��Ź̶���0 */
            else
            {
                pstData->aucData[1]   = 0;

                /*lint -e534*/
                VOS_MemCpy(pstData->aucData + 2, pstMsg->uAuth.stRunCaveAuth.aucRand, USIMM_RUNCAVE_RAND_LEN - 1);
                /*lint +e534*/
            }

            pstData->aucData[5] = pstMsg->uAuth.stRunCaveAuth.ucDigLen;

            pstData->aucData[9] = pstMsg->uAuth.stRunCaveAuth.ucProcessCtrl;

            /*lint -e534*/
            VOS_MemCpy(pstData->aucData + 6, pstMsg->uAuth.stRunCaveAuth.aucDigits, USIMM_RUNCAVE_DIGLEN);

            VOS_MemCpy(pstData->aucData + 10, pstMsg->uAuth.stRunCaveAuth.aucEsn, USIMM_ESN_MEID_LEN);
            /*lint +e534*/

            ulRslt = VOS_OK;

            break;

        case USIMM_EAP_AUTH:

            /*lint -e534*/
            VOS_MemCpy(pstData->aucData, pstMsg->uAuth.stEapAuth.stRand.aucData, pstMsg->uAuth.stEapAuth.stRand.ucDataLen);
            /*lint +e534*/

            pstData->ucDataLen = pstMsg->uAuth.stEapAuth.stRand.ucDataLen;

            pstData->aucData[pstData->ucDataLen] = pstMsg->uAuth.stEapAuth.stAutn.ucDataLen;

            pstData->ucDataLen++;

            /*lint -e534*/
            VOS_MemCpy(pstData->aucData + pstData->ucDataLen,
                       pstMsg->uAuth.stEapAuth.stAutn.aucData,
                       pstMsg->uAuth.stEapAuth.stAutn.ucDataLen);
            /*lint +e534*/

            pstData->ucDataLen += pstMsg->uAuth.stEapAuth.stAutn.ucDataLen;

            ulRslt = VOS_OK;

            break;

        default:

            ulRslt = VOS_ERR;
            break;
    }

    return ulRslt;
}


/*****************************************************************************
�� �� ��  :USIMM_GutlAuthenticationProc
��������  :ʵ�������⿨��Ȩ�·��ͽ���ظ���
�������  :Э��ջ�·�����Ϣ����
�������  :��
�� �� ֵ  :VOS_ERR
           VOS_OK

�޶���¼  :
1. ��    ��   : 2015��3��7��
   ��    ��   : h00300778
   �޸�����   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_GutlAuthenticationProc(
    USIMM_AUTHENTICATION_REQ_STRU       *pstMsg)
{
    VOS_UINT32                          ulRslt;
    USIMM_PHYCARD_TYPE_ENUM_UINT32      enCardType;

    enCardType = USIMM_CCB_GetCardType();

    if (USIMM_PHYCARD_TYPE_UICC == enCardType)
    {
        ulRslt = USIMM_USIMAuthHandle(pstMsg);
    }
    else
    {
        ulRslt = USIMM_SIMAuthHandle(pstMsg);
    }

    return ulRslt;
}


/*****************************************************************************
�� �� ��  :USIMM_ImsAuthenticationProc
��������  :ISIM APP���ͼ�Ȩ����
�������  :pMsg:API���·���Ϣ����
�������  :��
�� �� ֵ  :VOS_ERR/VOS_OK

�޶���¼  :
1. ��    ��   : 2015��4��9��
   ��    ��   : H00300778
   �޸�����   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_ImsAuthenticationProc(
    USIMM_AUTHENTICATION_REQ_STRU       *pstMsg)
{
    VOS_UINT32                          ulRslt;

    if (VOS_TRUE == USIMM_CCB_GetUsimSimulateIsimStatus())
    {
        ulRslt = USIMM_ISIMAuthHandle(pstMsg);
    }
    else
    {
        ulRslt = USIMM_IsimAuthenticationProc(pstMsg);
    }

    return ulRslt;
}


VOS_UINT32 USIMM_CdmaAuthHandle(
    USIMM_AUTHENTICATION_REQ_STRU       *pstMsg)
{
    USIMM_CDMA_AUTH_INFO_STRU           stCnfInfo;
    USIMM_U8_DATA_STRU                  stData;
    USIMM_APDU_RSP_STRU                 stRspData;
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulOffset = 1;
    USIMM_PHYCARD_TYPE_ENUM_UINT32      enCardType;
    VOS_UINT8                           ucP1;
    VOS_UINT8                           ucP2;


    /*lint -e534*/
    VOS_MemSet(&stCnfInfo,  0, sizeof(USIMM_CDMA_AUTH_INFO_STRU));
    VOS_MemSet(&stData,     0, sizeof(USIMM_U8_DATA_STRU));
    VOS_MemSet(&stRspData,  0, sizeof(USIMM_APDU_RSP_STRU));
    /*lint +e534*/

    if (USIMM_CARD_SERVIC_ABSENT == USIMM_CCB_GetAppService(USIMM_CDMA_APP))
    {
        USIMM_ERROR_LOG("USIMM_CdmaAuthHandle: incorrect card type.");

        stCnfInfo.enResult = USIMM_AUTH_CDMA_OTHER_FAILURE;

        USIMM_CdmaAuthCnf(pstMsg, &stCnfInfo);

        return VOS_ERR;
    }

    if (VOS_OK != USIMM_AuthenticationDataFillDataProc(pstMsg, &stData))
    {
        stCnfInfo.enResult = USIMM_AUTH_CDMA_OTHER_FAILURE;

        USIMM_CdmaAuthCnf(pstMsg, &stCnfInfo);

        return VOS_ERR;
    }

    /* ������Ⲣȷ����Ȩ���ݲ��� */
    enCardType = USIMM_CCB_GetCardType();

    if (USIMM_PHYCARD_TYPE_ICC == enCardType)
    {
        ulResult = USIMM_SelectFileByDefFileId(USIMM_CDMA_APP, USIMM_NEED_FCP, USIMM_CDMA_ID);

        if (USIMM_3G_AUTH == pstMsg->enAuthType)
        {
            ucP1 = 0x01;
            ucP2 = 0x00;
        }
        else if (USIMM_EAP_AUTH == pstMsg->enAuthType)
        {
            ucP1 = 0x02;
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
        ulResult = USIMM_SelectFileByDefFileId(USIMM_CDMA_APP, USIMM_NEED_FCP, USIMM_CSIM_ID);

        if (USIMM_3G_AUTH == pstMsg->enAuthType)
        {
            ucP1 = 0x00;
            ucP2 = 0x81;
        }
        else if (USIMM_EAP_AUTH == pstMsg->enAuthType)
        {
            ucP1 = 0x00;
            ucP2 = 0x82;
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

    ulResult = USIMM_SendAuthenticationApdu(pstMsg->stMsgHeader.enAppType,
                                            ucP1,
                                            ucP2,
                                            stData.ucDataLen,
                                            stData.aucData,
                                            &stRspData);

    if (USIMM_SW_CDMA_AUTN_ERROR == ulResult)
    {
        USIMM_WARNING_LOG("USIMM_CdmaAuthHandle: SIM Check SW Error");

        stCnfInfo.enResult = USIMM_AUTH_MAC_FAILURE;

        USIMM_CdmaAuthCnf(pstMsg, &stCnfInfo);

        return VOS_ERR;
    }

    if (VOS_OK != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_CdmaAuthHandle: Send USIM Authentication APDU Error");

        stCnfInfo.enResult = USIMM_AUTH_CDMA_OTHER_FAILURE;

        USIMM_CdmaAuthCnf(pstMsg, &stCnfInfo);

        return VOS_ERR;
    }

    if (USIMM_RUNCAVE_AUTH == pstMsg->enAuthType)
    {
        stCnfInfo.pucAuthr = stRspData.aucRsp;

        USIMM_INFO_LOG("USIMM_CdmaAuthHandle: Run Cave Authentication right");

        stCnfInfo.enResult = USIMM_AUTH_CDMA_SUCCESS;

        USIMM_CdmaAuthCnf(pstMsg, &stCnfInfo);

        return VOS_OK;
    }

    /* EAP��Ȩ */
    if (USIMM_EAP_AUTH == pstMsg->enAuthType)
    {
        if (1 == stRspData.aucRsp[0])
        {
            stCnfInfo.enResult  = USIMM_AUTH_SYNC_FAILURE;

            stCnfInfo.pucAuts   = stRspData.aucRsp + ulOffset;

            USIMM_WARNING_LOG("USIMM_CdmaAuthHandle: EAP Authentication Synchronization Failure");
        }
        else if (0 == stRspData.aucRsp[0])
        {
            stCnfInfo.enResult  = USIMM_AUTH_CDMA_SUCCESS;

            stCnfInfo.pucCK     = stRspData.aucRsp + ulOffset;
            ulOffset            += USIMM_AUTH_CK_LEN;   /* ָ��IK */

            stCnfInfo.pucIK     = stRspData.aucRsp + ulOffset;
            ulOffset            += USIMM_AUTH_IK_LEN;   /* ָ��Res */

            stCnfInfo.pucAuthRes = stRspData.aucRsp + ulOffset;

            USIMM_INFO_LOG("USIMM_CdmaAuthHandle: EAP Authenctication AKA Right");
        }
        else                                            /* �������ݴ��� */
        {
            USIMM_ERROR_LOG("USIMM_CdmaAuthHandle: EAP Authentication Response Data Error");

            stCnfInfo.enResult = USIMM_AUTH_CDMA_OTHER_FAILURE;
        }

        USIMM_CdmaAuthCnf(pstMsg, &stCnfInfo);

        return VOS_OK;
    }

    /* 3G ��Ȩ�ɹ� */
    if (USIMM_AUTH_SUCCESS_TAG == stRspData.aucRsp[0])
    {
        stCnfInfo.enResult   = USIMM_AUTH_CDMA_SUCCESS;

        stCnfInfo.pucCK      = stRspData.aucRsp + ulOffset; /* ָ��CK */
        ulOffset             += USIMM_AUTH_CK_LEN;/* ָ��IK */

        stCnfInfo.pucIK      = stRspData.aucRsp + ulOffset;
        ulOffset             += USIMM_AUTH_IK_LEN;/* ָ��Res */

        stCnfInfo.pucAuthRes = stRspData.aucRsp + ulOffset;

        USIMM_INFO_LOG("USIMM_CdmaAuthHandle: USIM 3G Authenctication AKA Right");
    }
    else if (USIMM_AUTH_SYNC_FAIL_TAG == stRspData.aucRsp[0]) /* 3G��ͬ�� */
    {
        stCnfInfo.enResult  = USIMM_AUTH_SYNC_FAILURE;

        stCnfInfo.pucAuts   = stRspData.aucRsp + ulOffset;

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



VOS_UINT32 USIMM_AuthenticationHandle(
    USIMM_CMDHEADER_REQ_STRU            *pMsg)
{
    USIMM_AUTHENTICATION_REQ_STRU      *pstMsg;
    VOS_UINT32                          ulResult;

    pstMsg  = (USIMM_AUTHENTICATION_REQ_STRU *)pMsg;

#if (FEATURE_VSIM == FEATURE_ON)
    if (VOS_TRUE == USIMM_VsimIsActive())    /*vSIM is Active*/
    {
        return USIMM_VirtualAuthenticationProc(pstMsg);
    }
#endif

    /*Ӳ������*/
    if (USIMM_GUTL_APP == pstMsg->stMsgHeader.enAppType)
    {
        ulResult = USIMM_GutlAuthenticationProc(pstMsg);
    }
    else if (USIMM_IMS_APP == pstMsg->stMsgHeader.enAppType)
    {
        ulResult =  USIMM_ImsAuthenticationProc(pstMsg);
    }
    else if (USIMM_CDMA_APP == pstMsg->stMsgHeader.enAppType)
    {
        ulResult =  USIMM_CdmaAuthHandle(pstMsg);
    }
    else
    {
        USIMM_ERROR_LOG("USIMM_AuthenticationHandle: enAppType is incorrect.");

        return VOS_ERR;
    }

    USIMM_CheckTimeOutError();

    return ulResult;
}


VOS_UINT32 USIMM_3Gpp2FDNHandle(
    USIMM_FDNPROCESS_REQ_STRU           *pstMsg)
{
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulUimSvr;
    VOS_UINT32                          ulCsimSvr;

    if (USIMM_CARD_SERVIC_AVAILABLE != USIMM_CCB_GetAppService(USIMM_CDMA_APP))
    {
        USIMM_ERROR_LOG("USIMM_3Gpp2FDNHandle: The App Status is Wrong");

        return VOS_ERR;
    }

    /* �жϵ�ǰȫ�ֱ�����FDN״̬�� */
    if (pstMsg->enHandleType == USIMM_CCB_GetAppFDN(USIMM_CDMA_APP))
    {
        USIMM_NORMAL_LOG("USIMM_3Gpp2FDNHandle: The FDN Status is Same");

        return VOS_OK;
    }

    ulUimSvr    = USIMM_IsServiceAvailable(UIM_SVR_FDN);
    ulCsimSvr   = USIMM_IsServiceAvailable(CSIM_SVR_FDN);

    if ((PS_USIM_SERVICE_NOT_AVAILIABLE == ulUimSvr)
        && (PS_USIM_SERVICE_NOT_AVAILIABLE == ulCsimSvr))
    {
        USIMM_ERROR_LOG("USIMM_3Gpp2FDNHandle: The Card SVR is Wrong");

        return VOS_ERR;
    }

    if (USIMM_PHYCARD_TYPE_UICC == USIMM_CCB_GetCardType())
    {
        /*����ADF����������*/
        ulResult = USIMM_SelectFileByDefFileId(USIMM_CDMA_APP, USIMM_NEED_FCP, USIMM_CSIM_ID);
    }
    else
    {
        /*����ADF����������*/
        ulResult = USIMM_SelectFileByDefFileId(USIMM_CDMA_APP, USIMM_NEED_FCP, USIMM_CDMA_ID);
    }

    if (ulResult != VOS_OK)/*�жϽ��*/
    {
        USIMM_ERROR_LOG("USIMM_3Gpp2FDNHandle: The USIMM_SelectFile is Wrong");

        return VOS_ERR;
    }

    ulResult = USIMM_PINVerify(USIMM_CDMA_APP, USIMM_PIN2, USIMM_PINCMD_VERIFY, pstMsg->aucPIN);

    if (ulResult != VOS_OK)/*�жϽ��*/
    {
        USIMM_ERROR_LOG("USIMM_3Gpp2FDNHandle: The USIMM_PINVerify is Wrong");

        return ulResult;
    }

    if (USIMM_PHYCARD_TYPE_UICC == USIMM_CCB_GetCardType())
    {
        if (USIMM_FDN_ACTIVE == pstMsg->enHandleType)
        {
            ulResult = USIMM_UICCFDNEnable(USIMM_CDMA_APP);
        }
        else if (USIMM_FDN_DEACTIVE == pstMsg->enHandleType)
        {
            ulResult = USIMM_UICCFDNDisable(USIMM_CDMA_APP);
        }
        else
        {
            /*��ǰֻ֧��FDN������BDN�Ĳ������ش���*/
            ulResult = VOS_ERR;
        }
    }
    else
    {
        if (USIMM_FDN_ACTIVE == pstMsg->enHandleType)
        {
            ulResult = USIMM_ICCFDNEnable(USIMM_CDMA_APP);
        }
        else if (USIMM_FDN_DEACTIVE == pstMsg->enHandleType)
        {
            ulResult = USIMM_ICCFDNDisable(USIMM_CDMA_APP);
        }
        else
        {
            /*��ǰֻ֧��FDN������BDN�Ĳ������ش���*/
            ulResult = VOS_ERR;
        }
    }

    /* �ϱ�FDN״̬��� */
    if (VOS_OK == ulResult)
    {
        USIMM_CCB_SetAppFDN(USIMM_CDMA_APP, pstMsg->enHandleType);
    }

    return ulResult;
}


VOS_UINT32 USIMM_3GppFDNHandle(
    USIMM_FDNPROCESS_REQ_STRU           *pstMsg)
{
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulSimSvr;
    VOS_UINT32                          ulUsimSvr;

    if (USIMM_CARD_SERVIC_AVAILABLE != USIMM_CCB_GetAppService(USIMM_GUTL_APP))
    {
        USIMM_ERROR_LOG("USIMM_3GppFDNHandle: The App Status is Wrong");

        return VOS_ERR;
    }

    ulSimSvr    = USIMM_IsServiceAvailable(SIM_SVR_FDN);
    ulUsimSvr   = USIMM_IsServiceAvailable(USIM_SVR_FDN);

    if ((PS_USIM_SERVICE_NOT_AVAILIABLE == ulSimSvr)
        && (PS_USIM_SERVICE_NOT_AVAILIABLE == ulUsimSvr))
    {
        USIMM_ERROR_LOG("USIMM_3GppFDNHandle: The Card SVR is Close");

        return VOS_ERR;
    }

    /* �жϵ�ǰȫ�ֱ�����FDN״̬�� */
    if (pstMsg->enHandleType == USIMM_CCB_GetAppFDN(USIMM_GUTL_APP))
    {
        USIMM_NORMAL_LOG("USIMM_3GppFDNHandle: The Status is Same");

        return VOS_OK;
    }

    if (USIMM_PHYCARD_TYPE_UICC == USIMM_CCB_GetCardType())
    {
        /*����ADF����������*/
        ulResult = USIMM_SelectFileByDefFileId(USIMM_GUTL_APP, USIMM_NEED_FCP, USIMM_USIM_ID);
    }
    else
    {
        /*����DF����������*/
        ulResult = USIMM_SelectFileByDefFileId(USIMM_GUTL_APP, USIMM_NEED_FCP, USIMM_GSM_ID);
    }

    if (USIMM_SW_OK != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_3GppFDNHandle: Select Card ADF Fail");

        return VOS_ERR;
    }

    ulResult = USIMM_PINVerify(USIMM_GUTL_APP, USIMM_PIN2, USIMM_PINCMD_VERIFY, pstMsg->aucPIN);

    if (ulResult != VOS_OK)/*�жϽ��*/
    {
        USIMM_ERROR_LOG("USIMM_3GppFDNHandle: USIMM_PINVerify Fail");

        return ulResult;
    }

    if (USIMM_PHYCARD_TYPE_UICC == USIMM_CCB_GetCardType())
    {
        if (USIMM_FDN_ACTIVE == pstMsg->enHandleType)
        {
            ulResult = USIMM_UICCFDNEnable(USIMM_GUTL_APP);
        }
        else if (USIMM_FDN_DEACTIVE == pstMsg->enHandleType)
        {
            ulResult = USIMM_UICCFDNDisable(USIMM_GUTL_APP);
        }
        else
        {
            /*��ǰֻ֧��FDN������BDN�Ĳ������ش���*/
            ulResult = VOS_ERR;
        }
    }
    else
    {
        if (USIMM_FDN_ACTIVE == pstMsg->enHandleType)
        {
            ulResult = USIMM_ICCFDNEnable(USIMM_GUTL_APP);
        }
        else if (USIMM_FDN_DEACTIVE == pstMsg->enHandleType)
        {
            ulResult = USIMM_ICCFDNDisable(USIMM_GUTL_APP);
        }
        else
        {
            /*��ǰֻ֧��FDN������BDN�Ĳ������ش���*/
            ulResult = VOS_ERR;
        }
    }

    /* �ϱ�FDN״̬��� */
    if (VOS_OK == ulResult)
    {
       USIMM_CCB_SetAppFDN(USIMM_GUTL_APP, pstMsg->enHandleType);

        /* ΪNAS ECALL ������ʱ�����ӣ�V8R1�޸Ļ��� */
        if (USIMM_PHYCARD_TYPE_UICC == USIMM_CCB_GetCardType())
        {
            USIMM_FDNEstChgInd();
        }
    }

    return ulResult;
}


VOS_UINT32 USIMM_FDNHandle(
    USIMM_CMDHEADER_REQ_STRU            *pMsg)
{
    VOS_UINT32                          ulResult;
    USIMM_FDNPROCESS_REQ_STRU          *pstMsg;

    pstMsg = (USIMM_FDNPROCESS_REQ_STRU *)pMsg;

    if (USIMM_API_SUCCESS != USIMM_ApiParaCheck())
    {
        USIMM_WARNING_LOG("USIMM_FDNHandle: USIMM_ApiParaCheck is Failed"); /*��ӡ����*/

        USIMM_FDNCnf(&pstMsg->stMsgHeader, VOS_ERR);

        return VOS_ERR; /*���غ���������Ϣ*/
    }

    if (USIMM_GUTL_APP == pstMsg->stMsgHeader.enAppType)
    {
        ulResult = USIMM_3GppFDNHandle(pstMsg);
    }
    else if (USIMM_CDMA_APP == pstMsg->stMsgHeader.enAppType)
    {
        ulResult = USIMM_3Gpp2FDNHandle(pstMsg);
    }
    else
    {
        USIMM_ERROR_LOG("USIMM_FDNHandle: AppType is Wrong"); /*��ӡ����*/

        ulResult = VOS_ERR;
    }

    USIMM_FDNCnf(&pstMsg->stMsgHeader, ulResult);

    return ulResult;
}
VOS_UINT32 USIMM_DeactiveRealCard(
    USIMM_MsgBlock                      *pMsg)
{
    VOS_UINT32                          ulErrlogNumber;
    OAM_MNTN_SIM_CARD_LOST_EVENT_STRU   stSimCardLost;

    USIMM_NORMAL_LOG("USIMM_DeactiveRealCard: Deactive Card");

    if (USIMM_OPENSPEEDENABLE == USIMM_CCB_GetUsimOpenSpeed())/*��״̬���*/
    {
        USIMM_WARNING_LOG("USIMM_DeactiveCardReq: The Card Status is Wrong");

        return VOS_ERR;
    }

    /* ��Ϊ˫��˫�����Ը�16λ��¼pid,��16λ��¼ԭ����id */
    ulErrlogNumber = pMsg->ulSenderPid;
    ulErrlogNumber <<= 16;
    ulErrlogNumber |= MNTN_OAM_SIM_CARD_LOST_EVENT;

    /* ��Errorlog�ļ��м�¼SIM�������¼� */
    if (VOS_OK != MNTN_RecordErrorLog(ulErrlogNumber,
                                      (void *)&stSimCardLost,
                                      sizeof(OAM_MNTN_SIM_CARD_LOST_EVENT_STRU)))
    {
        USIMM_WARNING_LOG("USIMM_DeactiveRealCard: Fail to record  SIM card lost event in Errorlog file");
    }

    OM_RecordInfoStart(VOS_EXC_DUMP_MEM_NUM_1, WUEPS_PID_USIM, WUEPS_PID_USIM, USIMMDL_DRV_USIMMSCI_DEACT);

    if (VOS_OK != mdrv_sci_deact())
    {
        USIMM_ERROR_LOG("USIMM_DeactiveRealCard: Deactive Card Error");
    }

    OM_RecordInfoEnd(VOS_EXC_DUMP_MEM_NUM_1);

    USIMM_ResetGlobalVarWithCard();

    USIMM_ExcLogDataSave((VOS_UINT8 *)&pMsg->ulSenderPid, sizeof(VOS_UINT32));

    USIMM_SaveExcLogFile();

    return VOS_OK;
}
VOS_UINT32 USIMM_DeactiveCardHandle(
    USIMM_CMDHEADER_REQ_STRU            *pMsg)
{
#if (FEATURE_VSIM == FEATURE_ON)
    if (VOS_TRUE == USIMM_VsimIsActive())    /*vSIM is Active*/
    {
        return USIMM_DeactiveVsim((USIMM_MsgBlock*)pMsg);
    }
#endif

    /*Ӳ������*/
    return USIMM_DeactiveRealCard((USIMM_MsgBlock*)pMsg);
}


VOS_UINT32 USIMM_CardInOutHandle(
    USIMM_CMDHEADER_REQ_STRU            *pMsg)
{
    USIMM_CARD_INOUT_IND_STRU           *pstMsg;
    USIMM_HOTINOUT_IND_STRU             *pstUsimMsg;

    pstMsg = (USIMM_CARD_INOUT_IND_STRU *)pMsg;

    pstUsimMsg = (USIMM_HOTINOUT_IND_STRU *)VOS_AllocMsg(WUEPS_PID_USIM,
                                                       sizeof(USIMM_HOTINOUT_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstUsimMsg)
    {
        USIMM_ERROR_LOG("USIMM_CardInOutHandle: VOS_AllocMsg is Failed");

        return VOS_ERR;
    }

    pstUsimMsg->stIndHdr.enMsgName      = USIMM_HOTINOUT_IND;
    pstUsimMsg->stIndHdr.ulReceiverPid  = WUEPS_PID_MMA;
    pstUsimMsg->ulCardInOutStatus       = pstMsg->ulCardInOutStatus;

    (VOS_VOID)VOS_SendMsg(WUEPS_PID_USIM, pstUsimMsg);

    if (USIMM_CARDSTATUS_IND_PLUGOUT == pstMsg->ulCardInOutStatus)  /*����ȥ����ӿ�ʵ�ֿ�״̬�ϱ��ͱ����Ը�λֹͣ*/
    {
        (VOS_VOID)USIMM_DeactiveRealCard((USIMM_MsgBlock *)pMsg);
    }

    return VOS_OK;
}
VOS_UINT32 USIMM_InitCardHandle(
    USIMM_CMDHEADER_REQ_STRU            *pMsg)
{
    VOS_UINT32                      ulResult;

    ulResult = VOS_ERR;

    if (USIMM_PHYCARD_TYPE_NOCARD == USIMM_CCB_GetCardType())
    {
#if (FEATURE_VSIM == FEATURE_ON)
        if (VOS_FALSE == USIMM_VsimIsActive())    /*vSIM Close*/
        {
            ulResult =  USIMM_COMM_InitCard((USIMM_MsgBlock*)pMsg);
        }
        else
        {
            ulResult =  USIMM_InitVsimCard((USIMM_MsgBlock*)pMsg);
        }
#else
        ulResult = USIMM_COMM_InitCard((USIMM_MsgBlock *)pMsg);
#endif  /*(FEATURE_VSIM == FEATURE_ON)*/
    }

    if (WUEPS_PID_USIM != pMsg->ulSenderPid)  /*�ⲿModule���͵ĳ�ʼ��*/
    {
        USIMM_SingleCmdCnf(pMsg->ulSenderPid, USIMM_ACTIVECARD_CNF, pMsg->ulSendPara, ulResult, pMsg->enAppType);
    }

#if (FEATURE_ON == FEATURE_PTM)
    if (VOS_OK == ulResult)
    {
        USIMM_RecordCardErrorLog(USIMM_MNTN_STATE_OK, USIMM_MNTN_ERROR_LEVEL_INFO);
    }
    else
    {
        USIMM_RecordCardErrorLog(USIMM_MNTN_STATE_INIT_FAIL, USIMM_MNTN_ERROR_LEVEL_MAJOR);
    }
#endif  /*(FEATURE_ON == FEATURE_PTM)*/

    return ulResult;
}
VOS_UINT32 USIMM_OpenChannelHandle(
    USIMM_CMDHEADER_REQ_STRU            *pMsg)
{
    USIMM_OPENCHANNEL_REQ_STRU          *pstMsg;
    USIMM_AID_INFO_STRU                 stAIDInfo;
    VOS_UINT32                          ulResult;
    USIMM_APDU_RSP_STRU                 stApduRsp;
    VOS_UINT8                           ucChannelNo;

    pstMsg = (USIMM_OPENCHANNEL_REQ_STRU *)pMsg;

    ulResult = USIMM_ApiParaCheck();

    if (USIMM_API_SUCCESS != ulResult)
    {
        USIMM_WARNING_LOG("USIMM_OpenChannelHandle: USIMM_ApiParaCheck is Failed");/*��ӡ����*/

        USIMM_OpenChannelCnf(pstMsg->stMsgHeader.ulSenderPid,
                             pstMsg->stMsgHeader.ulSendPara,
                             TAF_ERR_SIM_FAIL,
                             VOS_ERR,
                             VOS_NULL_BYTE);

        return ulResult; /*���غ���������Ϣ*/
    }

    if ((VOS_TRUE == g_stUsimmFeatureCfg.unCfg.stFeatureCfg.ulAidLenCheckFlg)
       && (pstMsg->stChannelInfo.ulAIDLen < USIMM_AID_LEN_MIN))
    {
        USIMM_ERROR_LOG("USIMM_OpenChannelHandle: the length of AID is error");

        USIMM_OpenChannelCnf(pstMsg->stMsgHeader.ulSenderPid,
                             pstMsg->stMsgHeader.ulSendPara,
                             TAF_ERR_ERROR,
                             VOS_ERR,
                             VOS_NULL_BYTE);

        return VOS_ERR;
    }

    if (VOS_TRUE == USIMM_SearchAllAID(pstMsg->stChannelInfo.ulAIDLen,
                                       pstMsg->stChannelInfo.aucADFName,
                                       &ucChannelNo))
    {
        USIMM_OpenChannelCnf(pstMsg->stMsgHeader.ulSenderPid,
                             pstMsg->stMsgHeader.ulSendPara,
                             TAF_ERR_NO_ERROR,
                             VOS_OK,
                             ucChannelNo);

        return VOS_OK;
    }

    /* һ��ͨ��ʹ����ֻ�����һ��ͨ�������֮ǰû�д򿪣����·�MANAGE CHANNEL�����ͨ�� */
    ulResult = USIMM_OpenChannel(&ucChannelNo);

    if (USIMM_SW_OK != ulResult)
    {
        USIMM_OpenChannelCnf(pstMsg->stMsgHeader.ulSenderPid,
                             pstMsg->stMsgHeader.ulSendPara,
                             TAF_ERR_MISSING_RESOURCE,
                             ulResult,
                             VOS_NULL_BYTE);

        return VOS_ERR;
    }

    if (VOS_NULL == pstMsg->stChannelInfo.ulAIDLen)
    {
        USIMM_OpenChannelCnf(pstMsg->stMsgHeader.ulSenderPid,
                             pstMsg->stMsgHeader.ulSendPara,
                             TAF_ERR_NO_ERROR,
                             VOS_OK,
                             ucChannelNo);

        return VOS_OK;
    }

    stAIDInfo.ulAIDLen  = pstMsg->stChannelInfo.ulAIDLen;

    /*lint  -e534 */
    VOS_MemCpy(stAIDInfo.aucAID,  pstMsg->stChannelInfo.aucADFName, pstMsg->stChannelInfo.ulAIDLen);
    /*lint  +e534 */

    /*NFC����Ҫ��P2=00*/
    if (VOS_TRUE == g_stUsimmFeatureCfg.unCfg.stFeatureCfg.ulP2ActiveAID)
    {
        ulResult = USIMM_SelectAIDFile(ucChannelNo, USIMM_SELECT_ACTIVATE_AID, &stAIDInfo, &stApduRsp);
    }
    else
    {
        ulResult = USIMM_SelectAIDFile(ucChannelNo, USIMM_SELECT_RETURN_FCP_TEMPLATE, &stAIDInfo, &stApduRsp);
    }

    if (USIMM_SW_OK != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_OpenChannelHandle: USIMM_CheckSW failed.");

        (VOS_VOID)USIMM_CloseChannel(ucChannelNo);

        USIMM_OpenChannelCnf(pstMsg->stMsgHeader.ulSenderPid,
                             pstMsg->stMsgHeader.ulSendPara,
                             TAF_ERR_NO_SUCH_ELEMENT,
                             ulResult,
                             VOS_NULL_BYTE);

        return VOS_ERR;
    }

    USIMM_OpenChannelCnf(pstMsg->stMsgHeader.ulSenderPid,
                         pstMsg->stMsgHeader.ulSendPara,
                         TAF_ERR_NO_ERROR,
                         VOS_OK,
                         ucChannelNo);

    return VOS_OK;
}


VOS_UINT32 USIMM_CloseChannelHandle(
    USIMM_CMDHEADER_REQ_STRU            *pMsg)
{
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucChannelId;
    USIMM_CARDAPP_ENUM_UINT32           enAppType;
    USIMM_CLOSECHANNEL_REQ_STRU        *pstMsg;

    pstMsg = (USIMM_CLOSECHANNEL_REQ_STRU *)pMsg;

    ulResult = USIMM_ApiParaCheck();

    if (VOS_OK != ulResult)
    {
        USIMM_WARNING_LOG("USIMM_CloseChannelHandle: USIMM_ApiParaCheck is Failed");/*��ӡ����*/

        USIMM_CloseChannelCnf(pstMsg->stMsgHeader.ulSenderPid,
                              pstMsg->stMsgHeader.ulSendPara,
                              TAF_ERR_SIM_FAIL,
                              VOS_ERR);

        return ulResult; /*���غ���������Ϣ*/
    }

    enAppType = pstMsg->stMsgHeader.enAppType;

    if (USIMM_UNLIMIT_APP_BUTT <= enAppType)
    {
        USIMM_ERROR_LOG("USIMM_CloseChannelHandle: ulSessionID is not correct");

        USIMM_CloseChannelCnf(pstMsg->stMsgHeader.ulSenderPid,
                              pstMsg->stMsgHeader.ulSendPara,
                              TAF_ERR_PARA_ERROR,
                              VOS_ERR);

        return VOS_ERR;
    }

    ucChannelId = USIMM_CCB_GetAppChNO(enAppType);

    if (VOS_NULL_BYTE == ucChannelId)
    {
        USIMM_ERROR_LOG("USIMM_CloseChannelHandle: Channel ID is not correct");

        USIMM_CloseChannelCnf(pstMsg->stMsgHeader.ulSenderPid,
                              pstMsg->stMsgHeader.ulSendPara,
                              TAF_ERR_PARA_ERROR,
                              VOS_ERR);

        return VOS_ERR;
    }

    /* ȥ����ADF �ο�Э��102.221 8.5.3�ڣ���ֹӦ��ʱ���·�status֪ͨUICC��Ȼ��ͨ�����ַ�ʽ����Ӧ�ã�
     1 ��ͨ��������ѡ��һ���µ�Ӧ��
     2 ��ͨ����select��Ӧ�ã�p2��������ֹӦ��
     3 �ر�ͨ��
     �˴���Ϊ�ǹر��߼�ͨ�������ѡ��ʽ3
    */
    (VOS_VOID)USIMM_SendStatusApdu(ucChannelId,
                                    USIMM_STATUS_TERMINATION_CURAPP,
                                    USIMM_STATUS_NO_DATA_RETURNED,
                                    VOS_NULL);

    /* �ر��߼�ͨ�� */
    ulResult = USIMM_CloseChannel(ucChannelId);

    if (VOS_OK != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_CloseChannelHandle: USIMM_CloseChannel failed.");

        USIMM_CloseChannelCnf(pstMsg->stMsgHeader.ulSenderPid,
                              pstMsg->stMsgHeader.ulSendPara,
                              TAF_ERR_ERROR,
                              ulResult);

        return VOS_ERR;
    }

    USIMM_CloseChannelCnf(pstMsg->stMsgHeader.ulSenderPid,
                          pstMsg->stMsgHeader.ulSendPara,
                          TAF_ERR_NO_ERROR,
                          VOS_OK);

    return VOS_OK;
}
VOS_UINT32 USIMM_CardStatusHandle(
    USIMM_CMDHEADER_REQ_STRU            *pstMsg)
{
    USIMM_CARD_STATUS_IND_STRU         *pstCardStatus;
    VOS_UINT32                          ulCardExist;

    pstCardStatus = (USIMM_CARD_STATUS_IND_STRU *)pstMsg;

    ulCardExist = USIMM_CCB_IsCardExist();

    /* ��ǰ���п�������յ����γ���Ϣ */
    if ((USIMM_CARDSTATUS_IND_PLUGOUT == pstCardStatus->ulCardStatus)
       && (VOS_TRUE == ulCardExist))
    {
        return USIMM_DeactiveRealCard((USIMM_MsgBlock *)pstMsg);
    }
    else if ((VOS_TRUE == USIMM_IsCLEnable())&&(USIMM_CARDSTATUS_IND_PLUGOUT == pstCardStatus->ulCardStatus))
    {
        return USIMM_DeactiveRealCard((USIMM_MsgBlock *)pstMsg);
    }
    /* ��ǰ���޿�������յ���������Ϣ */
    else if ((USIMM_CARDSTATUS_IND_PLUGIN == pstCardStatus->ulCardStatus)
       && (VOS_FALSE == ulCardExist))
    {
        return USIMM_ActiveCardReq(WUEPS_PID_USIM);
    }
    else
    {
        return VOS_OK;
    }
}


VOS_UINT32 USIMM_Read_OpenSpeedFile(
    USIMM_READFILE_REQ_STRU             *pstReadMsg,
    VOS_UINT16                          usEFID)
{
    VOS_UINT32                   ulResult;
    VOS_UINT8                    aucContent[250];
    VOS_UINT32                   i;
    USIMM_GETCNF_INFO_STRU       stFileInfo = {0};
    USIMM_OPENSPEED_FILE_TO_NVID ausNVId[]  = {
                                {0x6F62, USIMM_EF6F62Len, en_NV_Item_EF6F62},
                                {0x6F7B, USIMM_EF6F7BLen, en_NV_Item_EF6F7B},
                                {0x6F60, USIMM_EF6F60Len, en_NV_Item_EF6F60},
                                {0x6F61, USIMM_EF6F61Len, en_NV_Item_EF6F61},
                                {0x6F31, USIMM_EF6F31Len, en_NV_Item_EF6F31},
                                {0x6FAD, USIMM_EF6FADLen, en_NV_Item_EF6FAD},
                                {0x6F38, USIMM_EF6F38Len, en_NV_Item_EF6F38},
                                {0x6F7E, USIMM_EF6F7ELen, en_NV_Item_EF6F7E},
                                {0x6F73, USIMM_EF6F73Len, en_NV_Item_EF6F73},
                                {0x6F53, USIMM_EF6F53Len, en_NV_Item_EF6F53},
                                {0x6F07, USIMM_EF6F07Len, en_NV_Item_EF6F07},
                                {0x6F08, USIMM_EF6F08Len, en_NV_Item_EF6F08},
                                {0x6F09, USIMM_EF6F09Len, en_NV_Item_EF6F09},
                                {0x6F20, USIMM_EF6F20Len, en_NV_Item_EF6F20},
                                {0x6F52, USIMM_EF6F52Len, en_NV_Item_EF6F52},
                                {0x4F20, USIMM_EF4F20Len, en_NV_Item_EF4F20},
                                {0x4F52, USIMM_EF4F52Len, en_NV_Item_EF4F52},
                                {0x6FB7, USIMM_EF6FB7Len, en_NV_Item_EF6FB7},
                                {0x6F78, USIMM_EF6F78Len, en_NV_Item_EF6F78},
                                {0x6F5B, USIMM_EF6F5BLen, en_NV_Item_EF6F5B},
                                {0x6F5C, USIMM_EF6F5CLen, en_NV_Item_EF6F5C},
                                {0x6FC4, USIMM_EF6FC4Len, en_NV_Item_EF6FC4},
                                {0x6F74, USIMM_EF6F74Len, en_NV_Item_EF6F74},
                            };

    stFileInfo.usEfId       = usEFID;
    stFileInfo.ucRecordNum  = 0;
    stFileInfo.ucTotalNum   = 0;

    if (USIMM_GUTL_APP != pstReadMsg->stMsgHeader.enAppType)
    {
        USIMM_WARNING_LOG("USIMM_Read_OpenSpeedFile: The AppType is not USIMM_GUTL_APP");

        USIMM_GetFileCnf(pstReadMsg, USIMM_SW_MSGCHECK_ERROR, &stFileInfo);

        return VOS_ERR;
    }

    for (i = 0; i< ARRAYSIZE(ausNVId); i++)
    {
        if (ausNVId[i].usFileId == usEFID)
        {
            break;
        }
    }

    if (i >= ARRAYSIZE(ausNVId))
    {
        USIMM_WARNING_LOG("USIMM_Read_OpenSpeedFile: The File is Not Exist in Flash");

        USIMM_GetFileCnf(pstReadMsg, USIMM_SW_MSGCHECK_ERROR, &stFileInfo);

        return VOS_ERR;
    }

    ulResult = NV_Read(ausNVId[i].enNVId, aucContent, ausNVId[i].usEfLen);

    if (NV_OK != ulResult)
    {
        USIMM_WARNING_LOG("USIMM_Read_OpenSpeedFile: Read NV is Failed");

        USIMM_GetFileCnf(pstReadMsg, USIMM_SW_MSGCHECK_ERROR, &stFileInfo);

        return VOS_ERR;
    }

    stFileInfo.usDataLen    = ausNVId[i].usEfLen;
    stFileInfo.usEfLen      = ausNVId[i].usEfLen;
    stFileInfo.pucEf        = aucContent;

    USIMM_GetFileCnf(pstReadMsg, USIMM_SW_OK, &stFileInfo);

    return VOS_OK;
}


VOS_UINT32 USIMM_ReadFileHandle(
    USIMM_CMDHEADER_REQ_STRU            *pstMsgHeader)
{
    USIMM_READFILE_REQ_STRU            *pstReadMsg;
    VOS_UINT16                          usEFID;
    USIMM_GETCNF_INFO_STRU              stCnfInfo = {0};
    VOS_UINT32                          ulResult;

    pstReadMsg = (USIMM_READFILE_REQ_STRU *)pstMsgHeader;

    if (USIMM_UNLIMIT_APP_BUTT <= pstReadMsg->stMsgHeader.enAppType)
    {
        USIMM_GetFileCnf(pstReadMsg, USIMM_SW_MSGCHECK_ERROR, &stCnfInfo);

        return VOS_ERR;
    }

    if (USIMM_EF_FILE != USIMM_GetFileIDFromStr(&pstReadMsg->stFilePath, &usEFID))
    {
        USIMM_GetFileCnf(pstReadMsg, USIMM_SW_MSGCHECK_ERROR, &stCnfInfo);

        return VOS_ERR;
    }

    if (USIMM_OPENSPEEDENABLE == USIMM_CCB_GetUsimOpenSpeed()) /*���ٿ�������*/
    {
        return USIMM_Read_OpenSpeedFile(pstReadMsg, usEFID);
    }

    if(VOS_OK != USIMM_ApiParaCheckSimple())
    {
        USIMM_GetFileCnf(pstReadMsg, USIMM_SW_MSGCHECK_ERROR, &stCnfInfo);

        return VOS_ERR;
    }

#if (FEATURE_VSIM == FEATURE_ON)
    /* ���⿨״̬�Ѽ��� */
    if (VOS_TRUE == USIMM_VsimIsActive())
    {
        return USIMM_GetVsimFile(pstReadMsg, usEFID);
    }
#endif

    /* Ӳ������ */
    ulResult = USIMM_GetRealFile(pstReadMsg, usEFID);

    USIMM_CheckTimeOutError();

    return ulResult;
}
VOS_UINT32 USIMM_UpdateFileHandle(
    USIMM_CMDHEADER_REQ_STRU            *pstMsgHeader)
{
    USIMM_UPDATEFILE_REQ_STRU          *pstUpdateMsg;
    VOS_UINT16                          usEFID;
    USIMM_SETCNF_INFO_STRU              stCnfInfo = {0};
    VOS_UINT32                          ulResult;

    pstUpdateMsg = (USIMM_UPDATEFILE_REQ_STRU *)pstMsgHeader;

    if (VOS_OK != USIMM_ApiParaCheckSimple())
    {
        USIMM_SetFileCnf(pstUpdateMsg, USIMM_SW_MSGCHECK_ERROR, &stCnfInfo);

        return VOS_ERR;
    }

    if (USIMM_UNLIMIT_APP_BUTT <= pstUpdateMsg->stMsgHeader.enAppType)
    {
        USIMM_SetFileCnf(pstUpdateMsg, USIMM_SW_MSGCHECK_ERROR, &stCnfInfo);

        return VOS_ERR;
    }

    if (USIMM_EF_FILE != USIMM_GetFileIDFromStr(&pstUpdateMsg->stFilePath, &usEFID))
    {
        USIMM_SetFileCnf(pstUpdateMsg, USIMM_SW_MSGCHECK_ERROR, &stCnfInfo);

        return VOS_ERR;
    }

#if (FEATURE_VSIM == FEATURE_ON)
    /* ���⿨���� */
    if (VOS_TRUE == USIMM_VsimIsActive())
    {
        return USIMM_SetVsimFile(pstUpdateMsg, usEFID);
    }
#endif

    /* Ӳ������ */
    ulResult = USIMM_SetRealFile(pstUpdateMsg, usEFID);

    USIMM_CheckTimeOutError();

    return ulResult;
}


VOS_UINT32 USIMM_SetFileCommHandle(
    USIMM_UPDATEFILE_REQ_STRU           *pstUpdateMsg,
    VOS_UINT16                          usEFID)
{
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulFileIndex;
    USIMM_FILE_NEED_FCP_ENUM_UINT32     enFcpFlag;
    USIMM_EFFCP_ST                      stEFFcp;
    USIMM_POOL_ONERECORD_ST             stRecord;

    /*lint -e534*/
    VOS_MemSet(&stEFFcp, 0, sizeof(stEFFcp));
    VOS_MemSet(&stRecord, 0, sizeof(stRecord));
    /*lint +e534*/

    if (VOS_OK == USIMM_PoolFindFile(usEFID, &ulFileIndex, pstUpdateMsg->stMsgHeader.enAppType))
    {
        enFcpFlag          = USIMM_NO_NEED_FCP;
    }
    else
    {
        enFcpFlag          = USIMM_NEED_FCP;
    }

    ulResult = USIMM_SelectFile(pstUpdateMsg->stMsgHeader.enAppType,
                                enFcpFlag,
                                &pstUpdateMsg->stFilePath);

    if (USIMM_SW_OK != ulResult)/*�ж�ѡ����*/
    {
        USIMM_WARNING_LOG("USIMM_SetFileCommHandle: Select File is Failed");

        return ulResult;
    }

    if (USIMM_NO_NEED_FCP == enFcpFlag)
    {
        stEFFcp.enFileType = USIMM_CCB_GetPoolFileByIndex(ulFileIndex)->enFileType;
        stEFFcp.usFileLen  = USIMM_CCB_GetPoolFileByIndex(ulFileIndex)->usLen;
    }
    else
    {
        (VOS_VOID)VOS_MemCpy(&stEFFcp,
                             USIMM_CCB_GetCurEFInfo(pstUpdateMsg->stMsgHeader.enAppType),
                             sizeof(stEFFcp));
    }

    ulResult = USIMM_CheckSetFilePara(&stEFFcp, pstUpdateMsg->ucRecordNum, pstUpdateMsg->usDataLen);

    if (USIMM_SW_OK != ulResult)/*�ж�ѡ����*/
    {
        USIMM_WARNING_LOG("USIMM_SetFileCommHandle: USIMM_CheckSetFilePara is Failed");

        return ulResult;
    }

    /* �����ļ����͸����ļ� */
    ulResult = USIMM_UpdateFile(stEFFcp.enFileType,
                                pstUpdateMsg->stMsgHeader.enAppType,
                                pstUpdateMsg->ucRecordNum,
                                pstUpdateMsg->usDataLen,
                                pstUpdateMsg->aucContent);

    if (USIMM_SW_OK != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_SetFileCommHandle: Update File Content is Failed");

        return ulResult;
    }

    /* ����ļ������ڻ���������Ҫ���� */
    if (VOS_OK != USIMM_PoolUpdateOneFile(pstUpdateMsg->stMsgHeader.enAppType,
                                          usEFID,
                                          stEFFcp.usFileLen,
                                          pstUpdateMsg->aucContent))
    {
        USIMM_ERROR_LOG("USIMM_SetFileCommHandle: Update pool Content is Failed");
    }

    return USIMM_SW_OK;
}


VOS_UINT32 USIMM_QueryFileHandle(
    USIMM_CMDHEADER_REQ_STRU            *pstMsgHeader)
{
    USIMM_QUERYFILE_REQ_STRU    *pstQueryFileReq;
    VOS_UINT16                   usEFID;
    USIMM_FILECNF_INFO_STRU      stCnfInfo = {0};
    VOS_UINT32                   ulResult;
    USIMM_CARDAPP_ENUM_UINT32    enCardApp;
    USIMM_EFFCP_ST              *pstEFFCP  = VOS_NULL_PTR;

    pstQueryFileReq = (USIMM_QUERYFILE_REQ_STRU*)pstMsgHeader;
    enCardApp       = pstQueryFileReq->stMsgHeader.enAppType;

    if (USIMM_API_SUCCESS != USIMM_ApiParaCheck())
    {
        USIMM_MaxRecordNumCnf(pstQueryFileReq, USIMM_SW_MSGCHECK_ERROR, &stCnfInfo);

        return VOS_ERR; /*���غ���������Ϣ*/
    }

    if (USIMM_EF_FILE != USIMM_GetFileIDFromStr(&pstQueryFileReq->stFilePath, &usEFID))
    {
        USIMM_MaxRecordNumCnf(pstQueryFileReq, USIMM_SW_MSGCHECK_ERROR, &stCnfInfo);

        return VOS_ERR;
    }

    ulResult = USIMM_SelectFile(enCardApp,
                                USIMM_NEED_FCP,
                                &pstQueryFileReq->stFilePath);
    /* �ж��ļ���ѡ���� */
    if (VOS_OK != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_QueryFileHandle: The File Not Exist");

        USIMM_MaxRecordNumCnf(pstQueryFileReq, ulResult, &stCnfInfo);

        return VOS_ERR;
    }

    stCnfInfo.usEFId    = usEFID;
    pstEFFCP            = USIMM_CCB_GetCurEFInfo(enCardApp);

    /*�ж��ļ�������*/
    if (USIMM_EFSTRUCTURE_TRANSPARENT == pstEFFCP->enFileType)
    {
        USIMM_ERROR_LOG("USIMM_GetMaxRecordNum: The File Type is Wrong");

        ulResult = USIMM_SW_FILETYPE_ERROR;
    }
    else                    /*���ڼ�¼�ļ���ѭ���ļ�����Ϊ�ɹ�*/
    {
        USIMM_INFO_LOG("USIMM_GetMaxRecordNum: The File Select is OK");

        ulResult                = USIMM_SW_OK;

        stCnfInfo.ucRecordLen   = pstEFFCP->ucRecordLen;

        stCnfInfo.ucRecordNum   = pstEFFCP->ucRecordNum;
    }

    stCnfInfo.ulFileStatus          = pstEFFCP->enFileStatus;

    stCnfInfo.ulFileReadUpdateFlag  = pstEFFCP->enFileReadUpdateFlag;

    USIMM_MaxRecordNumCnf(pstQueryFileReq, ulResult, &stCnfInfo);

    return VOS_OK;
}


VOS_UINT32 USIMM_SearchFileHandle(
    USIMM_CMDHEADER_REQ_STRU            *pstMsgHeader)
{
    USIMM_SEARCHFILE_REQ_STRU          *pstSearchMsg;
    VOS_UINT16                          usEFID;
    USIMM_SEARCHCNF_INFO_STRU           stCnfInfo = {0};

    pstSearchMsg = (USIMM_SEARCHFILE_REQ_STRU *)pstMsgHeader;

    if (VOS_OK != USIMM_ApiParaCheckSimple())
    {
        USIMM_SearchHandleCnf(pstSearchMsg, USIMM_SW_MSGCHECK_ERROR, &stCnfInfo);

        return VOS_ERR;
    }

    if (USIMM_UNLIMIT_APP_BUTT <= pstSearchMsg->stMsgHeader.enAppType)
    {
        USIMM_SearchHandleCnf(pstSearchMsg, USIMM_SW_MSGCHECK_ERROR, &stCnfInfo);

        return VOS_ERR;
    }

    if (USIMM_EF_FILE != USIMM_GetFileIDFromStr(&pstSearchMsg->stFilePath, &usEFID))
    {
        USIMM_SearchHandleCnf(pstSearchMsg, USIMM_SW_MSGCHECK_ERROR, &stCnfInfo);

        return VOS_ERR;
    }

    return USIMM_SearchHandle(pstSearchMsg, usEFID);
}


VOS_UINT32 USIMM_SetSPBFileHandle(
    USIMM_CMDHEADER_REQ_STRU            *pstMsgHeader)
{
    VOS_UINT32                          i;
    USIMM_SETMUTILFILE_REQ_STRU        *pstMsg;
    VOS_UINT32                          ulResult;

    pstMsg = (USIMM_SETMUTILFILE_REQ_STRU *)pstMsgHeader;

    ulResult = USIMM_ApiParaCheck();

    if (USIMM_API_SUCCESS != ulResult)
    {
        USIMM_WARNING_LOG("USIMM_SetSPBFileReq: USIMM_ApiParaCheck is Failed"); /*��ӡ����*/

        USIMM_SetSPBFileCnf(pstMsg, USIMM_SW_MSGCHECK_ERROR);

        return ulResult; /*���غ���������Ϣ*/
    }

    for (i = 0; i < pstMsg->ulFileCount; i++)
    {
        /* ѡ��绰���ļ�, �绰���ļ�Ϊ��¼�ļ�����˲���Ҫ����FCP */
        if (VOS_OK != USIMM_SelectFile(pstMsg->stMsgHeader.enAppType,
                                       USIMM_NO_NEED_FCP,
                                       &(pstMsg->stFileData[i].stFilePath)))
        {
            USIMM_SetSPBFileCnf(pstMsg, USIMM_SW_NOFILE_SELECT);

            return VOS_ERR;
        }

        ulResult = USIMM_UpdateFile(USIMM_EFSTRUCTURE_FIXED,
                                    pstMsg->stMsgHeader.enAppType,
                                    pstMsg->stFileData[i].ucRecordNum,
                                    pstMsg->stFileData[i].usDataLen,
                                    pstMsg->stFileData[i].aucContent);
        if (VOS_OK != ulResult)
        {
            USIMM_SetSPBFileCnf(pstMsg, USIMM_SW_DOWNLOAD_ERROR);

            return VOS_ERR;
        }
    }

    USIMM_SetSPBFileCnf(pstMsg, USIMM_SW_OK);

    return VOS_OK;
}
VOS_UINT32 USIMM_ChannelCmdParaCheck(
    USIMM_SENDTPDUDATA_REQ_STRU         *pstMsg)
{
    /* ���ƶ�Ҫ��Լ�Ȩ����Ҳ�·��������ƶ��汾Ҫ����� */
    if (VOS_TRUE == g_stUsimmFeatureCfg.unCfg.stFeatureCfg.ulAuthCmdCheckFlg)
    {
        /* ��֧��GSM��Ȩ���� : ��SIM gsm��Ȩ��USIM gsm��Ȩ��Э��27.007����cgla����
        SIM gsm��Ȩʱ��P2����Ϊ0���ο�Э��11.11 9.2.16
        USIM gsm��Ȩʱ��P2��������bitΪ0���ο�Э��31.102 7.1.2
        */
        if ((CMD_INS_AUTHENTICATE == pstMsg->stTPDUData.aucTPDUHead[INS])
            &&(0 == (pstMsg->stTPDUData.aucTPDUHead[P2] & 0x07)))
        {
            USIMM_ERROR_LOG("USIMM_ChannelCmdParaCheck: The authenticate operation is forbided.");

            return VOS_ERR;
        }
    }

    /* ���INS�ֽ��Ƿ�Ϊ"6X"����"9X"��������򷵻�ʧ��.�˴������Э���׼��7816-4��ȷ�涨insΪ"6X","9X"�Ƿ� */
    if ((0x60 == (pstMsg->stTPDUData.aucTPDUHead[INS]&0xf0))
        || (0x90 == (pstMsg->stTPDUData.aucTPDUHead[INS]&0xf0)))
    {
        USIMM_ERROR_LOG("USIMM_ChannelCmdParaCheck: The operation is not supportable.");

        return VOS_ERR;
    }

    /* �˴�������ǰ�ڷ�������cgla�����߼�ͨ��ʱ�����·��������� :
       1 ��manage�򿪻�ر�ͨ��
       2 select aid���� P1Ϊ04ָ����select by df name
       3 fetchָ��߼�ͨ���ظ�91XX��Ҫ�ڻ���ͨ����fetch���μ�Э��102.221 7.4.2.1
    */
    if (VOS_TRUE == g_stUsimmFeatureCfg.unCfg.stFeatureCfg.ulCglaInsCheckFlg)
    {
        if ((CMD_INS_MANAGE_CHANNEL == pstMsg->stTPDUData.aucTPDUHead[INS])
            || (CMD_INS_FETCH      == pstMsg->stTPDUData.aucTPDUHead[INS]))
        {
            USIMM_ERROR_LOG("USIMM_ChannelCmdParaCheck: The operation is not supportable.");

            return VOS_ERR;
        }
    }

    if (VOS_TRUE == g_stUsimmFeatureCfg.unCfg.stFeatureCfg.ulCglaSelectCheckFlg)
    {
        if ((CMD_INS_SELECT             == pstMsg->stTPDUData.aucTPDUHead[INS])
            && (USIMM_SELECT_BY_DF_NAME == pstMsg->stTPDUData.aucTPDUHead[P1]))
        {
            USIMM_ERROR_LOG("USIMM_ChannelCmdParaCheck: The operation is not supportable.");

            return VOS_ERR;
        }
    }

    return VOS_OK;
}

/*****************************************************************************
�� �� ��  : USIMM_CheckAIDFcp
��������  : ��ѯ��ǰ�Ƿ�����ϱ�����AID FCP
�������  : pstMsg �������Ϣ����
�������  : pstDataCnf ��������������
�� �� ֵ  : VOS_ERR
           VOS_OK
�޶���¼  :
1. ��    ��   : 2015��3��18��
   ��    ��   : zhuli
   �޸�����   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_CheckAIDFcp(
    USIMM_SENDTPDUDATA_REQ_STRU         *pstMsg,
    USIMM_SENDTPDU_CNFINFO_STRU         *pstDataCnf)
{
    USIMM_UICC_ADF_INFO_STRU           *pstAdfInfo;
    VOS_UINT32                          ulFcpLen;
    VOS_UINT8                          *pucFcp;
    VOS_UINT8                           ucChannelNo;

    if (VOS_FALSE == g_stUsimmFeatureCfg.unCfg.stFeatureCfg.ulAIDFCPSave)
    {
        USIMM_WARNING_LOG("USIMM_CheckAIDFcp: ulAIDFCPSave Close");

        return VOS_ERR;
    }

    ucChannelNo = USIMM_CCB_GetAppChNO(pstMsg->stMsgHeader.enAppType);

    if (VOS_NULL_BYTE == ucChannelNo)
    {
        USIMM_WARNING_LOG("USIMM_CheckAIDFcp: USIMM_CCB_GetAppChNO Fail");

        return VOS_ERR;
    }

    pstAdfInfo = USIMM_CCB_GetAdfInfoByCH(ucChannelNo);

    if (VOS_NULL_PTR == pstAdfInfo)
    {
        USIMM_WARNING_LOG("USIMM_CheckAIDFcp: USIMM_CCB_GetAdfInfoByCH Fail");

        return VOS_ERR;
    }

    USIMM_CCB_GetAIDFcp(ucChannelNo, &ulFcpLen, &pucFcp);

    if (VOS_NULL == ulFcpLen)
    {
        USIMM_WARNING_LOG("USIMM_CheckAIDFcp: USIMM_CCB_GetAdfInfoByCH Fail");

        return VOS_ERR;
    }

    if ((CMD_INS_SELECT == pstMsg->stTPDUData.aucTPDUHead[INS])
        &&(USIMM_SELECT_BY_DF_NAME == pstMsg->stTPDUData.aucTPDUHead[P1]))
    {
        /*lint -e534*/
        if (VOS_OK == VOS_MemCmp(pstMsg->stTPDUData.aucData, pstAdfInfo->aucAID, pstMsg->stTPDUData.aucTPDUHead[P3]))
        /*lint +e534*/
        {
            pstDataCnf->ucSw1       = 0x90;
            pstDataCnf->ucSw2       = 0x00;
            pstDataCnf->usDataLen   = (VOS_UINT16)ulFcpLen;
            pstDataCnf->pucData     = pucFcp;

            return VOS_OK;
        }
    }

    return VOS_ERR;
}

/*****************************************************************************
�� �� ��  : USIMM_SelectTPDUProc
��������  : ���ѡ���ļ��������
�������  : pstMsg �������Ϣ����
�������  : pstRspData �����ص���������
�� �� ֵ  : VOS_ERR
           VOS_OK
�޶���¼  :
1. ��    ��   : 2015��3��18��
   ��    ��   : zhuli
   �޸�����   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_SelectTPDUProc(
    USIMM_SENDTPDUDATA_REQ_STRU        *pstMsg,
    USIMM_APDU_RSP_STRU                *pstRspData
)
{
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulPathLen;
    VOS_UINT16                          ausPath[USIMM_MAX_PATH_LEN];
    USIMM_SELECT_PARA_STUR              stSelectPara;
    USIMM_U16_LVDATA_STRU               stFilePath;
    USIMM_TPDU_HEAD_STRU                stTpduHead;
    USIMM_U8_LVDATA_STRU                stTpduData;
    USIMM_CURFILEINFO_ST               *pstCurFile;

    if ((pstMsg->stTPDUData.aucTPDUHead[P1] == USIMM_SELECT_BY_DF_NAME)
        &&((   (pstMsg->stTPDUData.aucTPDUHead[P2] == USIMM_SELECT_ACTIVATE_AID)
            || (pstMsg->stTPDUData.aucTPDUHead[P2] == USIMM_SELECT_TERMINATION_AID)
            || (pstMsg->stTPDUData.aucTPDUHead[P3] > USIMM_MAX_PATH_LEN*2))))
    {
        USIMM_ERROR_LOG("USIMM_SelectTPDUProc: The Select Para Error");

        return VOS_ERR;
    }

    stTpduHead.ucChannel    = USIMM_CCB_GetAppChNO(pstMsg->stMsgHeader.enAppType);

    if (VOS_NULL_BYTE == stTpduHead.ucChannel)
    {
        USIMM_ERROR_LOG("USIMM_SelectTPDUProc: The Select Channel Error");

        return VOS_ERR;
    }

    USIMM_CCB_ClearAIDFcp(stTpduHead.ucChannel);

    pstCurFile = USIMM_CCB_GetCurFileInfo(pstMsg->stMsgHeader.enAppType);

    if (VOS_NULL_PTR == pstCurFile)
    {
        USIMM_ERROR_LOG("USIMM_SelectTPDUProc: The Select App Error");

        return VOS_ERR;
    }

    stTpduHead.ucCLA        = pstMsg->stTPDUData.aucTPDUHead[CLA];
    stTpduHead.ucINS        = pstMsg->stTPDUData.aucTPDUHead[INS];
    stTpduHead.ucP1         = pstMsg->stTPDUData.aucTPDUHead[P1];
    stTpduHead.ucP2         = pstMsg->stTPDUData.aucTPDUHead[P2];
    stTpduHead.ucP3         = pstMsg->stTPDUData.aucTPDUHead[P3];

    stTpduData.pucData      = pstMsg->stTPDUData.aucData;
    stTpduData.ulDataLen    = pstMsg->stTPDUData.usDataLen;

    ulResult = USIMM_SendTPDUHandle(&stTpduHead, &stTpduData, pstRspData);

    if (USIMM_SW_OK != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_SelectTPDUProc: The USIMM_SendTPDUHandle Error");

        return VOS_OK;
    }

    USIMM_ChangePathToU16(pstMsg->stTPDUData.aucTPDUHead[P3],
                          pstMsg->stTPDUData.aucData,
                          &ulPathLen,
                          ausPath);

    stFilePath.pusData      = ausPath;

    stFilePath.ulDataLen    = ulPathLen;

    /* ����T=1Э������ٸ���response��INS�ж��Ƕ���ҪFCP�ˣ�ֻ�ܿ��Ƿ�����Ӧ���� */
    if (VOS_NULL != pstRspData->usRspLen)
    {
        stSelectPara.enEfFcpFlag = USIMM_NEED_FCP;

        (VOS_VOID)USIMM_DecodeFileFcp(USIMM_CCB_GetCardType(),
                                      &stFilePath,
                                      pstRspData,
                                      pstCurFile);

        /* �����߼�ͨ����GetResponse��� */
        USIMM_CCB_SetResponse(stTpduHead.ucChannel, pstRspData->usRspLen, pstRspData->aucRsp);
    }
    else
    {
        stSelectPara.enEfFcpFlag = USIMM_NO_NEED_FCP;
    }

    USIMM_UpdateFileByRelativePath(&stSelectPara, &stFilePath, pstCurFile);

    return VOS_OK;
}

/*****************************************************************************
�� �� ��  : USIMM_TPDUDataProc
��������  : ��������������
�������  : pstMsg �������Ϣ����
�������  : pstRspData �����ص���������
�� �� ֵ  : VOS_ERR
           VOS_OK
�޶���¼  :
1. ��    ��   : 2015��3��18��
   ��    ��   : zhuli
   �޸�����   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_TPDUDataProc(
    USIMM_SENDTPDUDATA_REQ_STRU        *pstMsg,
    USIMM_APDU_RSP_STRU                *pstRspData
)
{
    VOS_UINT32                  ulResult;
    USIMM_TPDU_HEAD_STRU        stTpduHead;
    USIMM_U8_LVDATA_STRU        stTpduData;

    stTpduHead.ucChannel    = USIMM_CCB_GetAppChNO(pstMsg->stMsgHeader.enAppType);

    if (VOS_NULL_BYTE == stTpduHead.ucChannel)
    {
        USIMM_ERROR_LOG("USIMM_TPDUDataProc: The Select Channel Error");

        return VOS_ERR;
    }

    USIMM_CCB_ClearAIDFcp(stTpduHead.ucChannel);

    stTpduHead.ucCLA        = pstMsg->stTPDUData.aucTPDUHead[CLA];
    stTpduHead.ucINS        = pstMsg->stTPDUData.aucTPDUHead[INS];
    stTpduHead.ucP1         = pstMsg->stTPDUData.aucTPDUHead[P1];
    stTpduHead.ucP2         = pstMsg->stTPDUData.aucTPDUHead[P2];
    stTpduHead.ucP3         = pstMsg->stTPDUData.aucTPDUHead[P3];

    stTpduData.pucData      = pstMsg->stTPDUData.aucData;
    stTpduData.ulDataLen    = pstMsg->stTPDUData.usDataLen;

    ulResult = USIMM_SendTPDUHandle(&stTpduHead, &stTpduData, pstRspData);

    if (USIMM_SW_OK != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_TPDUDataProc: The USIMM_SendTPDUHandle Error");

        return VOS_ERR;
    }

    ulResult = USIMM_CheckSW(stTpduHead.ucINS, pstRspData->ucApduSW1, pstRspData->ucApduSW2);

    /*����Warning������Ѿ��·�Get Response���Ҳ���Ҫ�ϱ�Get Response�����ݣ�
    ����Ҫ�ϱ���SW����Get Response���ݵ�ȫ�ֱ�������Ӧ���·�Get Response����*/
    if ((VOS_TRUE           == g_stUsimmFeatureCfg.unCfg.stFeatureCfg.ulCglaGetRsp)
        &&(USIMM_SW_WARNING == ulResult)
        &&(VOS_FALSE        == g_stUsimmFeatureCfg.unCfg.stFeatureCfg.ulWarningDataInd))
    {
        USIMM_CCB_SetResponse(stTpduHead.ucChannel, 
                                pstRspData->usRspLen, 
                                pstRspData->aucRsp);

        pstRspData->usRspLen = VOS_NULL;
    }

    return VOS_OK;
}

/*****************************************************************************
�� �� ��  : USIMM_GetResponseTPDUProc
��������  : ���GetResponse�������
�������  : pstMsg �������Ϣ����
�������  : pstRspData �����ص���������
�� �� ֵ  : VOS_ERR
            VOS_OK
�޶���¼  :
1. ��    ��   : 2015��3��18��
   ��    ��   : zhuli
   �޸�����   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_GetResponseTPDUProc(
    USIMM_SENDTPDUDATA_REQ_STRU        *pstMsg,
    USIMM_APDU_RSP_STRU                *pstRspData
)
{
    VOS_UINT32                          ulRspLen;
    VOS_UINT8                          *pucRsp;
    VOS_UINT8                           ucChannelNo;

    ucChannelNo = USIMM_CCB_GetAppChNO(pstMsg->stMsgHeader.enAppType);

    if (VOS_NULL_BYTE == ucChannelNo)
    {
        return VOS_ERR;
    }

    USIMM_CCB_ClearAIDFcp(ucChannelNo);

    USIMM_CCB_GetResponse(ucChannelNo, &ulRspLen, &pucRsp);

    /* GetResponseѡ��ӻ������ж�ȡ */
    if (0 != ulRspLen)
    {
        pstRspData->usRspLen =   (VOS_UINT16)ulRspLen;

        pstRspData->ucApduSW1 =   0x90;
        pstRspData->ucApduSW2 =   0x00;
        pstRspData->ucSW1     =   0x90;
        pstRspData->ucSW2     =   0x00;

        /*lint  -e534 */
        VOS_MemCpy(pstRspData->aucRsp, pucRsp, ulRspLen);
        /*lint  +e534 */

        USIMM_CCB_ClearResponse(ucChannelNo);

        return VOS_OK;
    }

    return USIMM_TPDUDataProc(pstMsg, pstRspData);
}
VOS_UINT32 USIMM_SendTPDUDataHandle(
    USIMM_CMDHEADER_REQ_STRU            *pstMsgHeader)
{
    USIMM_SENDTPDUDATA_REQ_STRU        *pstMsg;
    USIMM_CURFILEINFO_ST               *pstCurFile;
    VOS_UINT32                          ulResult;
    USIMM_SENDTPDU_CNFINFO_STRU         stDataCnf;
    USIMM_APDU_RSP_STRU                 stRspData;

    /*lint -e534*/
    VOS_MemSet(&stDataCnf, 0, sizeof(stDataCnf));
    VOS_MemSet(&stRspData, 0, sizeof(stRspData));
    /*lint +e534*/

    pstCurFile = VOS_NULL_PTR;

    ulResult = USIMM_ApiParaCheck();

    if (USIMM_API_SUCCESS != ulResult)
    {
        USIMM_WARNING_LOG("USIMM_SendTPDUDataHandle: The USIMM_ApiParaCheck is Error");

        USIMM_SendTPDUCnf(pstMsgHeader->ulSenderPid, pstMsgHeader->ulSendPara, VOS_ERR, &stDataCnf, pstCurFile);

        return ulResult;
    }

    pstMsg = (USIMM_SENDTPDUDATA_REQ_STRU*)pstMsgHeader;

    if (VOS_OK == USIMM_CheckAIDFcp(pstMsg, &stDataCnf))
    {
        USIMM_SendTPDUCnf(pstMsgHeader->ulSenderPid, pstMsgHeader->ulSendPara, VOS_OK, &stDataCnf, pstCurFile);

        return VOS_OK;
    }

    if (VOS_OK != USIMM_ChannelCmdParaCheck(pstMsg))
    {
        USIMM_ERROR_LOG("USIMM_AccessChannelHandle: The authenticate operation is forbided.");

        USIMM_SendTPDUCnf(pstMsgHeader->ulSenderPid, pstMsgHeader->ulSendPara, VOS_ERR, &stDataCnf, pstCurFile);

        return VOS_ERR;
    }

    if (pstMsg->stFilePath.ulPathLen != VOS_NULL) /*��Ҫ����ѡ��֮ǰ��·��*/
    {
        ulResult = USIMM_SelectFile(pstMsgHeader->enAppType, USIMM_NEED_FCP, &pstMsg->stFilePath);

        if (ulResult != USIMM_SW_OK)
        {
            USIMM_ERROR_LOG("USIMM_GAccessHandle: The USIMM_SelectFile Return Error");
        }
    }

    /*lint -e534*/
    VOS_MemSet(&stDataCnf, 0, sizeof(stDataCnf));
    /*lint +e534*/

    stDataCnf.pucTPDUHead = pstMsg->stTPDUData.aucTPDUHead;

    if (CMD_INS_SELECT == pstMsg->stTPDUData.aucTPDUHead[INS])
    {
        ulResult = USIMM_SelectTPDUProc(pstMsg, &stRspData);
    }
    else if (CMD_INS_GET_RESPONSE == pstMsg->stTPDUData.aucTPDUHead[INS])
    {
        ulResult = USIMM_GetResponseTPDUProc(pstMsg, &stRspData);
    }
    else
    {
        ulResult = USIMM_TPDUDataProc(pstMsg, &stRspData);
    }

    if (VOS_OK == ulResult)
    {
        stDataCnf.ucSw1         = stRspData.ucApduSW1;
        stDataCnf.ucSw2         = stRspData.ucApduSW2;
        stDataCnf.usDataLen     = stRspData.usRspLen;
        stDataCnf.pucData       = stRspData.aucRsp;

        pstCurFile = USIMM_CCB_GetCurFileInfo(pstMsgHeader->enAppType);
    }

    USIMM_SendTPDUCnf(pstMsgHeader->ulSenderPid,
                      pstMsgHeader->ulSendPara,
                      ulResult,
                      &stDataCnf,
                      pstCurFile);

    return ulResult;
}
VOS_UINT32 USIMM_BSChallengeHandle(
    USIMM_CMDHEADER_REQ_STRU            *pstMsg)
{
    VOS_UINT32                          ulResult;
    USIMM_BSCHALLENGE_REQ_STRU         *pstReqMsg;
    USIMM_APDU_RSP_STRU                 stRspData;
    VOS_UINT8                           ucChannelID;

    /*lint -e534*/
    VOS_MemSet(&stRspData,  0, sizeof(USIMM_APDU_RSP_STRU));
    /*lint +e534*/

    if (VOS_OK != USIMM_ApiParaCheck())/*�жϽ��*/
    {
        USIMM_ERROR_LOG("USIMM_BSChallengeHandle: USIMM_CdmaParaCheckSimple Error");

        USIMM_BSChallengeCnf(pstMsg, VOS_ERR, VOS_ERR, VOS_NULL, VOS_NULL_PTR);

        return VOS_ERR;
    }

    ucChannelID = USIMM_CCB_GetAppChNO(pstMsg->enAppType);

    if (VOS_NULL_BYTE == ucChannelID)
    {
        USIMM_ERROR_LOG("USIMM_BSChallengeHandle: USIMM_CCB_GetAppChNO Error");

        USIMM_BSChallengeCnf(pstMsg, VOS_ERR, VOS_ERR, VOS_NULL, VOS_NULL_PTR);

        return VOS_ERR;
    }

    if (USIMM_PHYCARD_TYPE_ICC == USIMM_CCB_GetCardType())
    {
        ulResult = USIMM_SelectFileByDefFileId(USIMM_CDMA_APP, USIMM_NEED_FCP, USIMM_CDMA_ID);
    }
    else
    {
        ulResult = USIMM_SelectFileByDefFileId(USIMM_CDMA_APP, USIMM_NEED_FCP, USIMM_CSIM_ID);
    }

    if (VOS_OK != ulResult)/*�жϽ��*/
    {
        USIMM_ERROR_LOG("USIMM_BSChallengeHandle: Select ADFCSIM or DFCDMA Error");

        USIMM_BSChallengeCnf(pstMsg, VOS_ERR, ulResult, VOS_NULL, VOS_NULL_PTR);

        return VOS_ERR;
    }

    pstReqMsg = (USIMM_BSCHALLENGE_REQ_STRU *)pstMsg;

    ulResult = USIMM_SendBSChallengeApdu(ucChannelID,
                                         USIMM_BS_RANDSEED_MAX,
                                         pstReqMsg->aucData,
                                         &stRspData);

    USIMM_BSChallengeCnf(pstMsg, ulResult, ulResult, stRspData.usRspLen, stRspData.aucRsp);

    if (USIMM_SW_OK != ulResult)
    {
        USIMM_WARNING_LOG("USIMM_BSChallengeHandle: The Command Result is Error");

        ulResult = VOS_ERR;
    }

    return ulResult;
}


VOS_UINT32 USIMM_ManageSsdHandle(
    USIMM_CMDHEADER_REQ_STRU            *pMsg)
{
    VOS_UINT32                          ulResult;
    USIMM_MANAGESSD_REQ_STRU           *pstMsg;
    VOS_UINT8                           ucDataLen;
    VOS_UINT8                           aucData[USIMM_CDMA_RANDSSD_LEN + USIMM_ESN_MEID_LEN + 1];
    VOS_UINT8                           ucChannelID;

    pstMsg = (USIMM_MANAGESSD_REQ_STRU *)pMsg;

    if (pstMsg->stSsdData.enCmdType >= USIMM_MANAGESSD_BUTT)
    {
        USIMM_ERROR_LOG("USIMM_ManageSsdHandle: Input Para is wrong");

        USIMM_SingleCmdCnf(pMsg->ulSenderPid, USIMM_MANAGESSD_CNF, pMsg->ulSendPara, VOS_ERR, pMsg->enAppType);

        return VOS_ERR;
    }

    if (VOS_OK != USIMM_ApiParaCheck())/*�жϽ��*/
    {
        USIMM_ERROR_LOG("USIMM_ManageSsdHandle: USIMM_CdmaParaCheckSimple Error");

        USIMM_SingleCmdCnf(pMsg->ulSenderPid, USIMM_MANAGESSD_CNF, pMsg->ulSendPara, VOS_ERR, pMsg->enAppType);

        return VOS_ERR;
    }

    if (USIMM_PHYCARD_TYPE_ICC == USIMM_CCB_GetCardType())
    {
        ulResult = USIMM_SelectFileByDefFileId(USIMM_CDMA_APP, USIMM_NEED_FCP, USIMM_CDMA_ID);
    }
    else
    {
        ulResult = USIMM_SelectFileByDefFileId(USIMM_CDMA_APP, USIMM_NEED_FCP, USIMM_CSIM_ID);
    }

    if (VOS_OK != ulResult)/*�жϽ��*/
    {
        USIMM_ERROR_LOG("USIMM_ManageSsdHandle: Select ADFCSIM or DFCDMA Error");

        USIMM_SingleCmdCnf(pMsg->ulSenderPid, USIMM_MANAGESSD_CNF, pMsg->ulSendPara, ulResult, pMsg->enAppType);

        return VOS_ERR;
    }

    if (USIMM_MANAGESSD_UPDATE == pstMsg->stSsdData.enCmdType)
    {
        /*lint  -e534 */
        VOS_MemCpy(aucData,
                   pstMsg->stSsdData.uSSDData.stUpdateSSD.aucRandSSD,
                   USIMM_CDMA_RANDSSD_LEN);
        /*lint +e534*/

        aucData[USIMM_CDMA_RANDSSD_LEN] = pstMsg->stSsdData.uSSDData.stUpdateSSD.ucProcessCtrl;

        /*lint  -e534 */
        VOS_MemCpy(aucData + USIMM_CDMA_RANDSSD_LEN + 1,
                   pstMsg->stSsdData.uSSDData.stUpdateSSD.aucESN,
                   USIMM_ESN_MEID_LEN);
        /*lint +e534*/

        ucDataLen = USIMM_CDMA_RANDSSD_LEN + USIMM_ESN_MEID_LEN + 1;
    }
    else
    {
        /*lint  -e534 */
        VOS_MemCpy(aucData,
                   pstMsg->stSsdData.uSSDData.stConfirmSSD.aucAuthBS,
                   USIMM_CDMA_AUTHBS_LEN);
        /*lint +e534*/

        ucDataLen = USIMM_CDMA_AUTHBS_LEN;
    }

    if (USIMM_PHYCARD_TYPE_ICC == USIMM_CCB_GetCardType())
    {
        if (USIMM_MANAGESSD_UPDATE == pstMsg->stSsdData.enCmdType)
        {
            ulResult = USIMM_SendUpdateSsdApdu(ucDataLen, aucData);
        }
        else
        {
            ulResult = USIMM_SendConfirmSsdApdu(ucDataLen, aucData);
        }
    }
    else
    {
        ucChannelID = USIMM_CCB_GetAppChNO(pstMsg->stMsgHeader.enAppType);

        if (VOS_NULL_BYTE == ucChannelID)
        {
            ulResult =  VOS_ERR;
        }
        else
        {
            ulResult = USIMM_SendManageSsdApdu(ucChannelID,
                                           (VOS_UINT8)pstMsg->stSsdData.enCmdType,
                                           ucDataLen,
                                           aucData);
        }
    }

    USIMM_SingleCmdCnf(pMsg->ulSenderPid, USIMM_MANAGESSD_CNF, pMsg->ulSendPara, ulResult, pMsg->enAppType);

    if (USIMM_SW_OK != ulResult)
    {
        USIMM_WARNING_LOG("USIMM_ManageSsdHandle: The Command Result is Error");

        ulResult = VOS_ERR;
    }

    return ulResult;
}


VOS_UINT32 USIMM_GenerateKeyVpmHandle(
    USIMM_CMDHEADER_REQ_STRU            *pMsg)
{
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulVpmLen;
    USIMM_GENERATE_KEYVPM_REQ_STRU     *pstMsg;
    USIMM_APDU_RSP_STRU                 stRspData;
    VOS_UINT8                           aucData[2];
    VOS_UINT8                           ucChannelID;

    /*lint -e534*/
    VOS_MemSet(&stRspData,  0, sizeof(USIMM_APDU_RSP_STRU));
    /*lint +e534*/

    pstMsg = (USIMM_GENERATE_KEYVPM_REQ_STRU *)pMsg;

    if (VOS_OK != USIMM_ApiParaCheck())/*�жϽ��*/
    {
        USIMM_ERROR_LOG("USIMM_GenerateKeyVpmHandle: USIMM_ApiParaCheck Error");

        USIMM_GenerateKeyVpmCnf(pstMsg, VOS_ERR, VOS_ERR, VOS_NULL, VOS_NULL_PTR, VOS_NULL_PTR);

        return VOS_ERR;
    }

    ucChannelID = USIMM_CCB_GetAppChNO(pstMsg->stMsgHeader.enAppType);

    if (VOS_NULL_BYTE == ucChannelID)
    {
        USIMM_ERROR_LOG("USIMM_GenerateKeyVpmHandle: USIMM_CCB_GetAppChNO Error");

        USIMM_GenerateKeyVpmCnf(pstMsg, VOS_ERR, VOS_ERR, VOS_NULL, VOS_NULL_PTR, VOS_NULL_PTR);

        return VOS_ERR;
    }

    if (USIMM_PHYCARD_TYPE_ICC == USIMM_CCB_GetCardType())
    {
        ulResult = USIMM_SelectFileByDefFileId(USIMM_CDMA_APP, USIMM_NEED_FCP, USIMM_CDMA_ID);
    }
    else
    {
        ulResult = USIMM_SelectFileByDefFileId(USIMM_CDMA_APP, USIMM_NEED_FCP, USIMM_CSIM_ID);
    }

    if (VOS_OK != ulResult)/*�жϽ��*/
    {
        USIMM_ERROR_LOG("USIMM_GenerateKeyVpmHandle: Select ADFCSIM or DFCDMA Error");

        USIMM_GenerateKeyVpmCnf(pstMsg, VOS_ERR, ulResult, VOS_NULL, VOS_NULL_PTR, VOS_NULL_PTR);

        return VOS_ERR;
    }

    aucData[0] = pstMsg->ucFirstOctet;
    aucData[1] = pstMsg->ucLastOctet;

    ulResult = USIMM_SendGenerateKeyVpmApdu(ucChannelID, sizeof(aucData), aucData, &stRspData);

    if (USIMM_SW_OK != ulResult)/*��鷢�ͽ��*/
    {
        USIMM_ERROR_LOG("USIMM_GenerateKeyVpmHandle: Send APDU Command is Failed");

        USIMM_GenerateKeyVpmCnf(pstMsg, VOS_ERR, USIMM_SW_SENDCMD_ERROR, VOS_NULL, VOS_NULL_PTR, VOS_NULL_PTR);

        return VOS_ERR;
    }


    ulVpmLen = (stRspData.usRspLen > 8)?(stRspData.usRspLen - 8):VOS_NULL;

    USIMM_GenerateKeyVpmCnf(pstMsg, ulResult, ulResult, ulVpmLen, stRspData.aucRsp + 8, stRspData.aucRsp);

    return ulResult;
}

/*****************************************************************************
�� �� ��  :USIMM_CdmaSpecAuthHandle
��������  :ʵ����CDMA�����Ȩ�Ĳ����ͽ���ķ���
�������  :pMsg:API���·���Ϣ����
�������  :��
�� �� ֵ  :VOS_ERR
           VOS_OK
���ú���  :

�޶���¼  :
1. ��    ��   : 2016��6��14��
   ��    ��   : zhuli
   �޸�����   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_CdmaSpecAuthHandle(
    USIMM_CMDHEADER_REQ_STRU            *pMsg)
{
    USIMM_CDMASPECAUTH_REQ_STRU         *pstMsg;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucChannelID;

    pstMsg = (USIMM_CDMASPECAUTH_REQ_STRU*)pMsg;

    if (VOS_OK != USIMM_ApiParaCheck())/*�жϽ��*/
    {
        USIMM_WARNING_LOG("USIMM_CdmaSpecAuthHandle: USIMM_ApiParaCheck Error");

        USIMM_CdmaSepcAuthCnf(&pstMsg->stMsgHeader,
                            USIMM_SW_ERR,
                            pstMsg->enAuthType,
                            VOS_NULL_PTR);

        return VOS_ERR;
    }

    ucChannelID = USIMM_CCB_GetAppChNO(pMsg->enAppType);

    if (VOS_NULL_BYTE == ucChannelID)
    {
        USIMM_WARNING_LOG("USIMM_CdmaSpecAuthHandle: USIMM_CCB_GetAppChNO Error");

        USIMM_CdmaSepcAuthCnf(&pstMsg->stMsgHeader,
                            USIMM_SW_NOFILE_FOUND,
                            pstMsg->enAuthType,
                            VOS_NULL_PTR);

        return VOS_ERR;
    }

    if (USIMM_PHYCARD_TYPE_ICC == USIMM_CCB_GetCardType())
    {
        ulResult = USIMM_SelectFileByDefFileId(USIMM_CDMA_APP, USIMM_NEED_FCP, USIMM_CDMA_ID);
    }
    else
    {
        ulResult = USIMM_SelectFileByDefFileId(USIMM_CDMA_APP, USIMM_NEED_FCP, USIMM_CSIM_ID);
    }

    if (VOS_OK != ulResult)/*�жϽ��*/
    {
        USIMM_WARNING_LOG("USIMM_CdmaSpecAuthHandle: Select ADFCSIM or DFCDMA Error");

        USIMM_CdmaSepcAuthCnf(&pstMsg->stMsgHeader,
                            USIMM_SW_NOFILE_FOUND,
                            pstMsg->enAuthType,
                            VOS_NULL_PTR);

        return VOS_ERR;
    }

    pstMsg = (USIMM_CDMASPECAUTH_REQ_STRU*)pMsg;

    switch(pstMsg->enAuthType)
    {
        case USIMM_CDMASPEC_COMPUTEIP:
            ulResult = USIMM_CdmaSpecAuthComputeIP(ucChannelID,
                                                &pstMsg->stMsgHeader,
                                                &pstMsg->uAuthData.stComputeIP);
            break;

        case USIMM_CDMASPEC_BCMCS:
            ulResult = USIMM_CdmaSpecAuthBCMCS(ucChannelID,
                                                &pstMsg->stMsgHeader,
                                                &pstMsg->uAuthData.stBCMCS);
            break;

        case USIMM_CDMASPEC_APPAUTH:
            ulResult = USIMM_CdmaSpecAuthApp(ucChannelID,
                                                &pstMsg->stMsgHeader,
                                                &pstMsg->uAuthData.stAppAuth);
            break;

        default:
            ulResult = USIMM_SW_CMD_ERROR;
            USIMM_WARNING_LOG("USIMM_CdmaSpecAuthHandle: Msg AuthType Error");
            break;
    }

    if (VOS_OK != ulResult)
    {
        USIMM_WARNING_LOG("USIMM_CdmaSpecAuthHandle: Prcess the Msg Error");

        USIMM_CdmaSepcAuthCnf(&pstMsg->stMsgHeader,
                            ulResult,
                            pstMsg->enAuthType,
                            VOS_NULL_PTR);
    }

    return ulResult;
}


static USIMMAPP_FUNCLIST_ST gastUSIMMAppFuncList[] =
{
    {USIMM_ACTIVECARD_REQ      , USIMM_InitCardHandle},
    {USIMM_INITCONTINUE_REQ    , USIMM_InitCardOptionalFile},
    {USIMM_PROTECTRESET_REQ    , USIMM_ProtectReset},
    {USIMM_DEACTIVECARD_REQ    , USIMM_DeactiveCardHandle},
    {USIMM_AUTHENTICATION_REQ  , USIMM_AuthenticationHandle},
    {USIMM_PINHANDLE_REQ       , USIMM_PINHandle},
    {USIMM_UPDATEFILE_REQ      , USIMM_UpdateFileHandle},
    {USIMM_READFILE_REQ        , USIMM_ReadFileHandle},
    {USIMM_QUERYFILE_REQ       , USIMM_QueryFileHandle},
    {USIMM_STATUSCMD_REQ       , USIMM_StatusHandle},
    {USIMM_SEARCHFILE_REQ      , USIMM_SearchFileHandle},
    {USIMM_FBDNPROCESS_REQ     , USIMM_FDNHandle},
    {USIMM_OPENCHANNEL_REQ     , USIMM_OpenChannelHandle},
    {USIMM_CLOSECHANNEL_REQ    , USIMM_CloseChannelHandle},
    {USIMM_SENDTPDUDATA_REQ    , USIMM_SendTPDUDataHandle},
    {USIMM_STKTERMINALRSP_REQ  , USIMM_SAT_TerminalResopnse},
    {USIMM_STKENVELOPE_REQ     , USIMM_SAT_Envelope},
    {USIMM_STKREFRESH_REQ      , USIMM_RefreshHandle},
    {USIMM_PBINIT_STATUS_IND   , USIMM_PBInitStatusIndHandle},
    {USIMM_RACCESS_REQ         , USIMM_RAccessHandle},
    {USIMM_SETMUTILFILE_REQ    , USIMM_SetSPBFileHandle},
    {USIMM_CARD_INOUT_IND      , USIMM_CardInOutHandle},
    {USIMM_CARDSTATUS_CB_IND   , USIMM_CardStatusHandle},
    {USIMM_BSCHALLENGE_REQ     , USIMM_BSChallengeHandle},
    {USIMM_GENERATE_KEYVPM_REQ , USIMM_GenerateKeyVpmHandle},
    {USIMM_MAMAGESSD_REQ       , USIMM_ManageSsdHandle},
    {USIMM_CDMASPECAUTH_REQ    , USIMM_CdmaSpecAuthHandle}
};


VOS_VOID USIMM_CardStateChangeProc(VOS_VOID)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulFlag = VOS_FALSE;

    for (i = 0; i < USIMM_CARDAPP_BUTT; i++)
    {
        if (USIMM_CARD_STATE_CHANGED == USIMM_CCB_GetAppStateChange(i))
        {
            USIMM_CCB_SetAppStateChange(i, USIMM_CARD_STATE_NOCHANGE);

            ulFlag = VOS_TRUE;
        }
    }

    if (VOS_TRUE == ulFlag)
    {
        USIMM_CardStatusInd(MAPS_PIH_PID);
    }

    return;
}

#if (FEATURE_ON == FEATURE_PTM)

VOS_VOID USIMM_ErrorLogProc(
    USIMM_CMDHEADER_REQ_STRU            *pMsg)
{
    OM_ERROR_LOG_CTRL_IND_STRU   *pstCrtlInd;

    OM_RecordInfoStart(VOS_EXC_DUMP_MEM_NUM_1,
                        pMsg->ulSenderPid,
                        WUEPS_PID_USIM,
                        pMsg->enMsgName);

    if (ID_OM_ERR_LOG_REPORT_REQ == pMsg->enMsgName)
    {
        USIMM_CardErrorLogReport();

        OM_RecordInfoEnd(VOS_EXC_DUMP_MEM_NUM_1);

        return;
    }

    if (ID_OM_ERR_LOG_CTRL_IND == pMsg->enMsgName)
    {
        pstCrtlInd = (OM_ERROR_LOG_CTRL_IND_STRU *)pMsg;

        g_stErrLogCtrlInfo.ucAlmLevel = pstCrtlInd->ucAlmLevel;
        g_stErrLogCtrlInfo.ucAlmStatus = pstCrtlInd->ucAlmStatus;
    }

    OM_RecordInfoEnd(VOS_EXC_DUMP_MEM_NUM_1);

    return;
}
#endif


VOS_VOID USIMM_ApplicationMsgProc(
    USIMM_CMDHEADER_REQ_STRU            *pMsg)
{
    VOS_UINT32                          ulQueueSize = 0;

    if (pMsg->enMsgName >= (sizeof(gastUSIMMAppFuncList)/sizeof(USIMMAPP_FUNCLIST_ST)))
    {
        (VOS_VOID)LogPrint2("\r\nUSIMM_ApplicationMsgProc:CmdType error!, Msg ID is %d, Send PID is %d\r\n", (VOS_INT)pMsg->enMsgName, (VOS_INT)pMsg->ulSenderPid);
        return;
    }

    OM_RecordInfoStart(VOS_EXC_DUMP_MEM_NUM_1, pMsg->ulSenderPid, WUEPS_PID_USIM, pMsg->enMsgName);

    if (VOS_OK != gastUSIMMAppFuncList[pMsg->enMsgName].pProcFun(pMsg))
    {
        USIMM_WARNING_LOG("USIMM_ApplicationMsgProc: Message Handle Error");
    }

    OM_RecordInfoEnd(VOS_EXC_DUMP_MEM_NUM_1);

    USIMM_CardStateChangeProc();

    /*��ǰ����SAT�������SAT���ܴ�*/
    if (USIMM_SAT_STATE_NEEDFETCH == gstUSIMMBaseInfo.enSATState)
    {
        USIMM_SAT_Fetch(gstUSIMMBaseInfo.usSATLen);
    }

#ifndef OAM_DMT
    /* ��ȡ��ǰFID����Ϣ�ĸ��� */
    ulQueueSize = VOS_GetQueueSizeFromFid(MAPS_USIMM_FID);
#else
    ulQueueSize = VOS_NULL;
#endif
    /*����ʱ��ֹͣ������*/
    if ((VOS_FALSE == USIMM_VsimIsActive())
        &&(USIMM_PB_IDLE == gstUSIMMBaseInfo.stPBInfo.enPBInitStatus)
        &&(USIMM_CLKSTOP_ALLOW == gstUSIMMDrvInfo.enCLKStop)
        &&(VOS_NULL == ulQueueSize))
    {
        USIMM_NORMAL_LOG("USIMM_ApplicationMsgProc:Clock Stop Begin");

        (VOS_VOID)mdrv_sci_stop_tm((SCI_CLK_STOP_TYPE_E)gstUSIMMDrvInfo.enCLKLevel);
    }

    USIMM_CardTimeOutEventInd();

    return;
}
VOS_VOID USIMM_MsgProc(
    USIMM_CMDHEADER_REQ_STRU            *pMsg)
{
    if (VOS_NULL_PTR == pMsg)
    {
        return;
    }

    if (MSP_PID_DIAG_APP_AGENT == pMsg->ulSenderPid)
    {
#if (FEATURE_ON == FEATURE_PTM)
        USIMM_ErrorLogProc(pMsg);
#endif
    }
    else
    {
        USIMM_ApplicationMsgProc(pMsg);
    }

    return;
}


VOS_UINT32 USIMM_FID_Init(enum VOS_INIT_PHASE_DEFINE ip)
{
    VOS_UINT32                              ulResult = VOS_OK;
    USIMM_CMD_DEBUG_MODE_ST                 stDebugInfo;

    switch (ip)
    {
        case VOS_IP_LOAD_CONFIG:    /* USIMM Application PID ע�� */
            ulResult = VOS_RegisterPIDInfo(WUEPS_PID_USIM,
                                           (Init_Fun_Type)VOS_NULL_PTR,
                                           (Msg_Fun_Type)USIMM_MsgProc);
            if (ulResult != VOS_OK)
            {
                return VOS_ERR;
            }

            /* ע��USIM Managerģ���FID */
            ulResult = VOS_RegisterMsgTaskPrio(MAPS_USIMM_FID, MAPS_USIMM_FID_PRIORITY);

            if (ulResult != VOS_OK)
            {
                return VOS_ERR;
            }

            break;

        case VOS_IP_INITIAL:    /* ��ģ���ʼ����� */

            USIMM_ClearGlobalVar();

            if (USIMM_OPENSPEEDENABLE == USIMM_CCB_GetUsimOpenSpeed())
            {
                USIMM_NORMAL_LOG("USIMM_FID_Init: Usimm Open Speed is ON");

                USIMM_InitOpenSpeed();

                ulResult = VOS_OK;
            }
            else
            {
                USIMM_NORMAL_LOG("USIMM_FID_Init: Start Normal Init SIM Step");

                ulResult = NV_Read(en_NV_Item_Usim_Debug_Mode_Set, &stDebugInfo, sizeof(USIMM_CMD_DEBUG_MODE_ST));

                if ((NV_OK ==  ulResult)&&(VOS_TRUE == stDebugInfo.usFlag)) /* �ӳ�ʱ�䲶���ʼ����Ϣ */
                {
                    return VOS_OK;
                }

                USIMM_InitLogFile();

                USIMM_InitExcLogFile();

                USIMM_CardStatusRegCbFuncProc();

#ifndef OAM_DMT
                ulResult = USIMM_ActiveCardReq(WUEPS_PID_USIM);
#endif
            }
            break;

        default:
            break;
    }

    return ulResult;
}

#else


VOS_UINT32 USIMM_RefreshHandle(USIMM_CMDHEADER_REQ_STRU *pMsg)
{
    USIMM_STKREFRESH_REQ_STRU             *pstMsg;
    VOS_UINT8                           aucTemp[] = {0x81,0x03,0x00,0x00,0x00,0x02,0x02,0x82,0x81,0x83,0x01,0x00};
    USIMM_MODE_TYPE_ENUM_UINT8          ucMode;
    USIMM_PIN_INFO_STRU                 stPINInfo;


    pstMsg = (USIMM_STKREFRESH_REQ_STRU*)pMsg;

    USIMM_PoolDelAll();

    if (USIMM_RESET == pstMsg->enRefreshType)
    {
        USIMM_INFO_LOG("USIMM_RefreshHandle: The Card Need Cold Reset.");

        if(USIMM_CARD_USIM == gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardType)
        {
            /*lint -e534*/
            USIMM_Status_APDU(USIMM_STATUS_TERMINATION_CURAPP, USIMM_STATUS_DF_NAME_RETURNED, 0xFF);
            /*lint +e534*/
        }

        USIMM_InitGlobalVarOnPower();

        /*lint -e534*/
        USIMM_InitCard(VOS_NULL_PTR);
        /*lint +e534*/
    }
    else
    {
        if (VOS_OK != USIMM_RefreshAidVerify(pstMsg->ulAidLen, pstMsg->aucAid))
        {
            aucTemp[2]  = (VOS_UINT8)pstMsg->ulCommandNum;
            aucTemp[3]  = (VOS_UINT8)pstMsg->ulCommandType;
            aucTemp[4]  = (VOS_UINT8)pstMsg->enRefreshType;
            aucTemp[11] = COMMAND_DATA_NOT_UNDERSTOOD_BY_TERMINAL;

            /* Ϊ�˹���������̵���������˴���Ҫ��������ִ�н�� */
            /*lint -e534*/
            USIMM_TerminalResponse_APDU(sizeof(aucTemp), aucTemp);
            /*lint +e534*/

            /* �ظ�������� */
            USIMM_ResetCnf(pstMsg->stMsgHeader.ulSenderPid, pstMsg->enRefreshType, VOS_ERR, gstUSIMMBaseInfo.usSATLen);

            return VOS_OK;
        }

        if ((USIMM_CARD_USIM == gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardType)
         && (USIMM_APPLICATION_RESET_3G_ONLY == pstMsg->enRefreshType))
        {
            /*lint -e534*/
            VOS_MemSet(&stPINInfo, 0, sizeof(stPINInfo));

            VOS_MemCpy(&stPINInfo, &gstUSIMMADFInfo.stPINInfo, sizeof(stPINInfo));

            USIMM_Status_APDU(USIMM_STATUS_TERMINATION_CURAPP, USIMM_STATUS_DF_NAME_RETURNED, 0xFF);
            /*lint +e534*/

            USIMM_Reselect3GApp();
            /*lint -e534*/
            VOS_MemCpy(&gstUSIMMADFInfo.stPINInfo, &stPINInfo, sizeof(stPINInfo));
            /*lint +e534*/
        }

        /*lint -e534*/
        USIMM_InsertNoNeedPinFileToPool();
        /*lint +e534*/

        /* ��ʼ��ATT�����ļ����䲻��PIN����� */
        USIMM_AttFileInit();

        if(USIMM_CARD_USIM == gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardType)
        {
            /*lint -e534*/
            USIMM_InsertLPFileToPool();

            USIMM_InitUsimEccFile();
            /*lint +e534*/
        }
        else
        {
            /*lint -e534*/
            USIMM_InsertLPFileToPool();

            USIMM_InitSimEccFile();
            /*lint +e534*/
        }

        /* SIM���£���refresh typeΪ0/2/3����£���Ҫ�·�Terminal Profile��refresh typeΪ1����Ҫ��
            USIM���¶�����Ҫ�·�Terminal Profile */
        if (USIMM_SIM_REFRESH_IS_NEED_TP(pstMsg->enRefreshType))
        {
            ucMode = USIMM_RESET_MODE;
        }
        else
        {
            ucMode = USIMM_REFRESH_MODE;
        }

        if (USIMM_CARD_SERVIC_AVAILABLE == gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardService)
        {
            USIMM_InitNeedPinSteps(ucMode);

            /*lint -e534*/
            USIMM_InitCardOptionalFile(VOS_NULL_PTR);
            /*lint +e534*/
        }

        if(((USIMM_FILE_CHANGE_NOTIFY == pstMsg->enRefreshType)||(USIMM_INITIAL_FILE_CHANGE_NOTIFY == pstMsg->enRefreshType))
            &&(pstMsg->usLen != 0))
        {
            USIMM_RefreshFileRead(pstMsg);
        }

        aucTemp[2]  = (VOS_UINT8)pstMsg->ulCommandNum;
        aucTemp[3]  = (VOS_UINT8)pstMsg->ulCommandType;
        aucTemp[4]  = (VOS_UINT8)pstMsg->enRefreshType;

        /*Ϊ�˹���������̵���������˴���Ҫ��������ִ�н��*/
        /*lint -e534*/
        USIMM_TerminalResponse_APDU(sizeof(aucTemp), aucTemp);
        /*lint +e534*/
    }

    USIMM_ResetCnf(pstMsg->stMsgHeader.ulSenderPid, pstMsg->enRefreshType, VOS_OK, gstUSIMMBaseInfo.usSATLen); /*�ظ��������*/

    USIMM_RefreshInd(pstMsg);

    return VOS_OK;
}


VOS_VOID USIMM_SAT_Fetch(VOS_UINT16 usLen)
{
    USIMM_APP_TYPE_ENUM_UINT32          enAppType;
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulOffset;
    VOS_UINT8                           ucCmdType;
    VOS_UINT8                           ucP3;
    VOS_UINT8                           aucData[USIMM_EF_IMSI_LEN];

    if (USIMM_SAT_STATE_NEEDRESPONSE == gstUSIMMBaseInfo.enSATState)
    {
        USIMM_ERROR_LOG("USIMM_SAT_Fetch: The Last Data Need Response");

        return;
    }

    if(usLen >  0x100)
    {
        gstUSIMMBaseInfo.usSATLen   = 0;

        gstUSIMMBaseInfo.enSATState = USIMM_SAT_STATE_NODATA;

        USIMM_ERROR_LOG("USIMM_SAT_Fetch: The Data Len is Error");

        return;
    }
    else
    {
        ucP3 = (VOS_UINT8)usLen;
    }

    ulResult = USIMM_Fetch_APDU(ucP3);

    if(VOS_OK != ulResult)/*�жϽ��*/
    {
        USIMM_ERROR_LOG("USIMM_SAT_Fetch: Send APUD Command is Failed");    /*��ӡ����*/

        gstUSIMMBaseInfo.enSATState = USIMM_SAT_STATE_NODATA;

        gstUSIMMBaseInfo.usSATLen   = 0;

        return;
    }

    ulResult = USIMM_CheckSW(&gstUSIMMAPDU);

    if(USIMM_SW_OK != ulResult)/*�жϽ��*/
    {
        USIMM_WARNING_LOG("USIMM_SAT_Fetch: The Send APDU Result is Error");/*��ӡ����*/

        gstUSIMMBaseInfo.enSATState = USIMM_SAT_STATE_NODATA;

        gstUSIMMBaseInfo.usSATLen   = 0;

        return;
    }

    /*��ѯ��ǰ��������������*/
    ulResult = USIMM_FindTagInSMPTLV(gstUSIMMAPDU.aucRecvBuf, USIMM_SATCMD_TAG, usLen);

    if(USIMM_TAGNOTFOUND == ulResult)/*�жϽ��*/
    {
        USIMM_WARNING_LOG("USIMM_SAT_Fetch: The Command Type Tag is Not Founded in the SAT Data ");  /*��ӡ����*/

        gstUSIMMBaseInfo.enSATState = USIMM_SAT_STATE_NODATA;

        gstUSIMMBaseInfo.usSATLen   = 0;

        return;
    }

    ulOffset = USIMM_FindTagInSMPTLV(&gstUSIMMAPDU.aucRecvBuf[ulResult+1],USIMM_CMDDETAIL_TAG,
                                    gstUSIMMAPDU.aucRecvBuf[ulResult]);

    if(USIMM_TAGNOTFOUND == ulOffset)/*�жϽ��*/
    {
        USIMM_WARNING_LOG("USIMM_SAT_Fetch: The Command Detail Tag is Not Founded in the SAT Data");    /*��ӡ����*/

        gstUSIMMBaseInfo.enSATState = USIMM_SAT_STATE_NODATA;

        gstUSIMMBaseInfo.usSATLen   = 0;

        return;
    }

    ulOffset += ulResult;

    ucCmdType = gstUSIMMAPDU.aucRecvBuf[ulOffset+3];

    USIMM_INFO_LOG("USIMM_SAT_Fetch: IND SAT Command, Wait Terminal Response");

    gstUSIMMBaseInfo.enSATState = USIMM_SAT_STATE_NEEDRESPONSE;

    USIMM_SatDataInd(ucCmdType, usLen, gstUSIMMAPDU.aucRecvBuf);/*�ϱ��������������*/

    gstUSIMMBaseInfo.usSATLen = 0;

    enAppType   =   ((USIMM_CARD_SIM == gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardType)?USIMM_GSM_APP:USIMM_UMTS_APP);

    /* �����0x01 Refresh���������ϱ������ܿ���IMSI�����������Ҫ�����ڴ� */
    if((0x01 == ucCmdType)&&(USIMM_NONEED == gstUSIMMADFInfo.enPin1Verified))
    {
        if(VOS_OK == USIMM_PoolDelOneFile(EFIMSI, enAppType))
        {
            /* ��IMSI */
            if(VOS_OK != USIMM_GetTFFile(enAppType, EFIMSI, USIMM_READ_ALL_FILE_CONTENT, aucData))
            {
                USIMM_ERROR_LOG("USIMM_SAT_Fetch: Fail to Read IMSI");

                return;
            }

            /*lint -e534*/
            USIMM_PoolInsertOneFile(EFIMSI, USIMM_EF_IMSI_LEN, aucData,
                                          enAppType, USIMM_EFSTRUCTURE_TRANSPARENT);
            /*lint +e534*/
        }
        else
        {
            USIMM_ERROR_LOG("USIMM_SAT_Fetch: Can not find IMSI in Pool");

            return;
        }
    }

    return;
}


VOS_UINT32 USIMM_SAT_Envelope(USIMM_CMDHEADER_REQ_STRU *pMsg)
{
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulSWRslt;
    USIMM_STKENVELOPE_REQ_STRU          *pstMsg;
    USIMM_ENVELOPECNF_INFO_STRU         stCnfInfo;

    /*lint -e534*/
    VOS_MemSet(&stCnfInfo, 0, sizeof(stCnfInfo));
    /*lint +e534*/

    pstMsg = (USIMM_STKENVELOPE_REQ_STRU*)pMsg;

    if (VOS_OK != USIMM_ApiParaCheck())
    {
        USIMM_WARNING_LOG("USIMM_SAT_Envelope: USIMM_ApiParaCheck is Failed");/*��ӡ����*/

        USIMM_EnvelopeCnf(pstMsg->stMsgHeader.ulSenderPid, pstMsg->stMsgHeader.ulSendPara, USIMM_SW_ERR, &stCnfInfo);

        return VOS_ERR;
    }

    stCnfInfo.ucDataType = pstMsg->aucContent[0];

    ulResult = USIMM_Envelope_APDU(pstMsg->ucDataLen, pstMsg->aucContent);  /*������������*/

    stCnfInfo.ucSW1 = gstUSIMMAPDU.ucSW1;

    stCnfInfo.ucSW2 = gstUSIMMAPDU.ucSW2;

    if(VOS_OK != ulResult)/*�����*/
    {
        USIMM_ERROR_LOG("USIMM_SAT_Envelope: Send APDU Command is Failed");

        USIMM_EnvelopeCnf(pstMsg->stMsgHeader.ulSenderPid, pstMsg->stMsgHeader.ulSendPara,USIMM_SW_SENDCMD_ERROR,&stCnfInfo);

        return VOS_ERR;
    }

    ulSWRslt = USIMM_CheckSW(&gstUSIMMAPDU);

    /* ���ENVELOPE�����WARNING */
    if ((0x62 == gstUSIMMAPDU.ucApduSW1)||(0x63 == gstUSIMMAPDU.ucApduSW1)||(0x9E == gstUSIMMAPDU.ucApduSW1))
    {
        stCnfInfo.ucSW1 = gstUSIMMAPDU.ucApduSW1;

        stCnfInfo.ucSW2 = gstUSIMMAPDU.ucApduSW2;

        if ((USIMM_ENVELOPE_PPDOWN == pstMsg->aucContent[0])
           || (USIMM_ENVELOPE_CBDOWN == pstMsg->aucContent[0]))
        {
            ulResult = USIMM_SW_DOWNLOAD_ERROR;
        }
        else
        {
            ulResult = ulSWRslt;    /* ���������������������� */
        }
    }
    else
    {
        ulResult = ulSWRslt;
    }

    stCnfInfo.ulDataLen = gstUSIMMAPDU.ulRecDataLen;

    stCnfInfo.pucData   = gstUSIMMAPDU.aucRecvBuf;

    USIMM_EnvelopeCnf(pstMsg->stMsgHeader.ulSenderPid, pstMsg->stMsgHeader.ulSendPara, ulResult, &stCnfInfo);

    if(USIMM_SW_OK != ulResult) /*��Ҫ���ؾ���ԭ����ʱ���ش���*/
    {
        USIMM_WARNING_LOG("USIMM_SAT_Envelope: Send APDU Command Result is Failed");

        ulResult = VOS_ERR;
    }

    return ulResult;
}


VOS_UINT32 USIMM_SAT_TerminalResopnse(USIMM_CMDHEADER_REQ_STRU *pMsg)
{
    VOS_UINT32                      ulResult;
    USIMM_TERMINALRESPONSE_REQ_STRU *pstMsg;

    pstMsg = (USIMM_TERMINALRESPONSE_REQ_STRU*)pMsg;

    if (VOS_FALSE == USIMM_IsCLEnable())
    {
        if (VOS_OK != USIMM_ApiParaCheck())
        {
            USIMM_WARNING_LOG("USIMM_SAT_TerminalResopnse: USIMM_ApiParaCheck is Failed");/*��ӡ����*/

            USIMM_TerminalResponseCnf(pstMsg->stMsgHeader.ulSenderPid, USIMM_SW_ERR, pstMsg->stMsgHeader.ulSendPara,0,0);

            return VOS_ERR;
        }
    }

    ulResult = USIMM_TerminalResponse_APDU(pstMsg->ucDataLen, pstMsg->aucContent);

    if(VOS_OK != ulResult)/*��鷢�ͽ��*/
    {
        USIMM_ERROR_LOG("USIMM_SAT_TerminalResopnse: Send APDU Command is Failed");

        USIMM_TerminalResponseCnf(pstMsg->stMsgHeader.ulSenderPid, USIMM_SW_SENDCMD_ERROR, pstMsg->stMsgHeader.ulSendPara,0,0);

        return VOS_ERR;
    }

    gstUSIMMBaseInfo.enSATState = USIMM_SAT_STATE_NODATA;

    ulResult = USIMM_CheckSW(&gstUSIMMAPDU);

    USIMM_TerminalResponseCnf(pstMsg->stMsgHeader.ulSenderPid, ulResult, pstMsg->stMsgHeader.ulSendPara, gstUSIMMAPDU.ucSW1,gstUSIMMAPDU.ucSW2);

    if(USIMM_SW_OK != ulResult)
    {
        USIMM_WARNING_LOG("USIMM_SAT_TerminalResopnse: The Command Result is Error");

        ulResult = VOS_ERR;
    }

    return ulResult;
}



VOS_UINT32  USIMM_PinStatusCheck(USIMM_PIN_CMD_TYPE_ENUM_UINT32  enCmdType,
                                           USIMM_PIN_TYPE_ENUM_UINT32      enPINType,
                                           VOS_UINT32                      *pulResult)
{
    VOS_UINT32  ulResult;

    switch (enCmdType)
    {
        case USIMM_PINCMD_ENABLE:
            if(USIMM_PIN == enPINType)
            {
                if(USIMM_PUK_NEED == gstUSIMMADFInfo.enPin1Verified)
                {
                    ulResult = VOS_FALSE;
                    *pulResult = USIMM_SIM_PUK_REQUIRED;
                }
                else if(USIMM_PIN_DISABLED == gstUSIMMADFInfo.stPINInfo.enPin1Enable)
                {
                    ulResult = VOS_TRUE;
                }
                else
                {
                    ulResult = VOS_FALSE;
                    *pulResult = USIMM_SIM_FAILURE;
                }
            }
            else if(USIMM_PIN2 == enPINType)
            {
                if(USIMM_PUK_NEED == gstUSIMMADFInfo.enPin2Verified)
                {
                    ulResult = VOS_FALSE;
                    *pulResult = USIMM_SIM_PUK2_REQUIRED;
                }
                else if(USIMM_PIN_DISABLED == gstUSIMMADFInfo.stPINInfo.enPin2Enable)
                {
                    ulResult = VOS_TRUE;
                }
                else
                {
                    ulResult = VOS_FALSE;
                    *pulResult = USIMM_SIM_FAILURE;
                }
            }
            else
            {
                *pulResult = USIMM_OPERATION_NOT_ALLOW;
                ulResult = VOS_FALSE;
            }
            break;

        case USIMM_PINCMD_VERIFY:
            if(USIMM_PIN == enPINType)
            {
                if(USIMM_PUK_NEED == gstUSIMMADFInfo.enPin1Verified)
                {
                    ulResult = VOS_FALSE;
                    *pulResult = USIMM_SIM_PUK_REQUIRED;
                }
                else if((USIMM_PIN_DISABLED == gstUSIMMADFInfo.stPINInfo.enPin1Enable)
                    ||(USIMM_NONEED == gstUSIMMADFInfo.enPin1Verified))
                {
                    ulResult = VOS_FALSE;
                    *pulResult = USIMM_OPERATION_NOT_ALLOW;
                }
                else
                {
                    ulResult = VOS_TRUE;
                }
            }
            else if(USIMM_PIN2 == enPINType)
            {
                if(USIMM_PUK_NEED == gstUSIMMADFInfo.enPin2Verified)
                {
                    ulResult = VOS_FALSE;
                    *pulResult = USIMM_SIM_PUK2_REQUIRED;
                }
                else if((USIMM_PIN_DISABLED == gstUSIMMADFInfo.stPINInfo.enPin2Enable)
                    ||(USIMM_NONEED == gstUSIMMADFInfo.enPin2Verified))
                {
                    ulResult = VOS_FALSE;
                    *pulResult = USIMM_OPERATION_NOT_ALLOW;
                }
                else
                {
                    ulResult = VOS_TRUE;
                }
            }
            else
            {
                *pulResult = USIMM_OPERATION_NOT_ALLOW;
                ulResult = VOS_FALSE;
            }
            break;

        case USIMM_PINCMD_DISABLE:
            if(USIMM_PIN == enPINType)
            {
                if(USIMM_PUK_NEED == gstUSIMMADFInfo.enPin1Verified)
                {
                    ulResult = VOS_FALSE;
                    *pulResult = USIMM_SIM_PUK_REQUIRED;
                }
                else if(USIMM_PIN_ENABLED == gstUSIMMADFInfo.stPINInfo.enPin1Enable)
                {
                    ulResult = VOS_TRUE;
                }
                else
                {
                    ulResult = VOS_FALSE;
                    *pulResult = USIMM_SIM_FAILURE;
                }
            }
            else if(USIMM_PIN2 == enPINType)
            {
                if(USIMM_PUK_NEED == gstUSIMMADFInfo.enPin2Verified)
                {
                    ulResult = VOS_FALSE;
                    *pulResult = USIMM_SIM_PUK2_REQUIRED;
                }
                else if(USIMM_PIN_ENABLED == gstUSIMMADFInfo.stPINInfo.enPin2Enable)
                {
                    ulResult = VOS_TRUE;
                }
                else
                {
                    ulResult = VOS_FALSE;
                    *pulResult = USIMM_SIM_FAILURE;
                }
            }
            else
            {
                *pulResult = USIMM_OPERATION_NOT_ALLOW;
                ulResult = VOS_FALSE;
            }
            break;
        case USIMM_PINCMD_UNBLOCK:
            if (VOS_TRUE == USIMM_CheckSupportAP())
            {
                ulResult = VOS_TRUE;
            }
            else
            {
                if(USIMM_PIN == enPINType)
                {
                    if(USIMM_PUK_NEED == gstUSIMMADFInfo.enPin1Verified)
                    {
                        ulResult = VOS_TRUE;
                    }
                    else
                    {
                        ulResult = VOS_FALSE;
                        *pulResult = USIMM_OPERATION_NOT_ALLOW;
                    }
                }
                else if(USIMM_PIN2 == enPINType)
                {
                    if(USIMM_PUK_NEED == gstUSIMMADFInfo.enPin2Verified)
                    {
                        ulResult = VOS_TRUE;
                    }
                    else
                    {
                        ulResult = VOS_FALSE;
                        *pulResult = USIMM_OPERATION_NOT_ALLOW;
                    }
                }
                else
                {
                    ulResult = VOS_FALSE;
                    *pulResult = USIMM_OPERATION_NOT_ALLOW;
                }
            }
            break;
        case USIMM_PINCMD_CHANGE:
            if(USIMM_PIN == enPINType)
            {
                if(USIMM_PUK_NEED == gstUSIMMADFInfo.enPin1Verified)
                {
                    ulResult = VOS_FALSE;
                    *pulResult = USIMM_SIM_PUK_REQUIRED;
                }
                else if(USIMM_PIN_ENABLED == gstUSIMMADFInfo.stPINInfo.enPin1Enable)
                {
                    ulResult = VOS_TRUE;
                }
                else
                {
                    ulResult = VOS_FALSE;
                    *pulResult = USIMM_SIM_FAILURE;
                }
            }
            else if(USIMM_PIN2 == enPINType)
            {
                if(USIMM_PUK_NEED == gstUSIMMADFInfo.enPin2Verified)
                {
                    ulResult = VOS_FALSE;
                    *pulResult = USIMM_SIM_PUK2_REQUIRED;
                }
                else if(USIMM_PIN_ENABLED == gstUSIMMADFInfo.stPINInfo.enPin2Enable)
                {
                    ulResult = VOS_TRUE;
                }
                else
                {
                    ulResult = VOS_FALSE;
                    *pulResult = USIMM_SIM_FAILURE;
                }
            }
            else
            {
                ulResult = VOS_FALSE;
                *pulResult = USIMM_SIM_FAILURE;
            }
            break;
        default:
            *pulResult = USIMM_OPERATION_NOT_ALLOW;
            ulResult = VOS_FALSE;
            break;
    }

    return ulResult;
}

/*****************************************************************************
�� �� ��  : USIMM_PinPreProcHandle
��������  : USIMMģ��PIN��������ϢԤ����
�������  : pNewstMsg:�µ�PIN��������Ϣ
�������  : pPreMsg:�ɵ�PIN��������Ϣ
�� �� ֵ  : ��
History     :
1.��    ��  : 2015��01��30��
  ��    ��  : h00300778
  �޸�����  : Create
*****************************************************************************/
VOS_UINT32 USIMM_PinPreProcHandle(
    USIMM_PINHANDLE_REQ_STRU            *pNewstMsg,
    USIMM_PIN_REQ_STRU                  *pPreMsg)
{
    VOS_UINT32                          ulResult = VOS_OK;

    /*lint -e534*/
    VOS_MemCpy(pPreMsg, pNewstMsg, VOS_MSG_HEAD_LENGTH);
    /*lint +e534*/

    pPreMsg->enPINType  = pNewstMsg->enPINType;
    pPreMsg->enCmdType  = pNewstMsg->enCmdType;

    /*lint -e534*/
    VOS_MemCpy(pPreMsg->aucOldPIN, pNewstMsg->aucOldPIN, USIMM_PINNUMBER_LEN);
    VOS_MemCpy(pPreMsg->aucNewPIN, pNewstMsg->aucNewPIN, USIMM_PINNUMBER_LEN);
    /*lint +e534*/

    /* �����δָʾPIN��������ͣ����ݵ�ǰPIN��״̬�Ͳ�������ת������ */
    if (USIMM_SIM_NON == pPreMsg->enPINType)
    {
        ulResult = USIMM_HandlePINType((VOS_UINT8)(pPreMsg->enCmdType), &pPreMsg->enPINType);
    }

    if (USIMM_PUK == pPreMsg->enPINType)
    {
        pPreMsg->enPINType = USIMM_PIN;
    }
    else if ( USIMM_PUK2 == pPreMsg->enPINType )
    {
        pPreMsg->enPINType = USIMM_PIN2;
    }
    else
    {
        /*do nothing*/
    }

    return ulResult;
}

/*****************************************************************************
�� �� ��  : USIMM_PinHandleCardStatusCheck
��������  : USIMMģ��PIN��������ǰ��״̬��鴦����
�������  : ��
�������  : ��
�� �� ֵ  : VOS_OK/VOS_ERR
History     :
1.��    ��  : 2015��02��11��
  ��    ��  : h00300778
  �޸�����  : Create
*****************************************************************************/
VOS_UINT32 USIMM_PinHandleCardStatusCheck(VOS_VOID)
{
    if ((gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardService <= USIMM_CARD_SERVIC_UNAVAILABLE)
     || (USIMM_OPENSPEEDENABLE == gulUSIMMOpenSpeed))/*��״̬���*/
    {
        USIMM_WARNING_LOG("USIMM_PinHandleCardStatusCheck: The Card Status is Wrong");

        return USIMM_API_NOTAVAILABLE;
    }

    if(VOS_TRUE == USIMM_VsimIsActive())    /*vSIM���ܴ�*/
    {
        USIMM_WARNING_LOG("USIMM_PinHandleCardStatusCheck: The vSIM is Open");

        return USIMM_API_NOTAVAILABLE;
    }

    return VOS_OK;
}


VOS_UINT32 USIMM_PINHandle(USIMM_CMDHEADER_REQ_STRU *pMsg)
{
    USIMM_PIN_REQ_STRU                  stMsg;
    VOS_UINT32                          ulResult      = VOS_ERR;
    VOS_UINT16                          ausUsimPath[] = {MF, ADF};
    VOS_UINT16                          ausSimPath[]  = {MF, DFGSM};

    if (VOS_OK != USIMM_PinHandleCardStatusCheck())
    {
        USIMM_ERROR_LOG("USIMM_PINHandle: USIMM_PinHandleCardStatusCheck Failed");

        USIMM_PinHandleCnf((USIMM_PINHANDLE_REQ_STRU *)pMsg, VOS_ERR, &gstUSIMMADFInfo.stPINInfo);

        return VOS_ERR;
    }

    ulResult = USIMM_PinPreProcHandle((USIMM_PINHANDLE_REQ_STRU *)pMsg, &stMsg);

    if (VOS_OK != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_PINHandle: USIMM_PinPreProcHandle Failed");

        USIMM_PinHandleCnf((USIMM_PINHANDLE_REQ_STRU *)pMsg, VOS_ERR, &gstUSIMMADFInfo.stPINInfo);

        return VOS_ERR;
    }

    if (USIMM_CARD_USIM == gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardType)
    {
        /* ����ADF���������� */
        ulResult = USIMM_SelectFile(USIMM_UMTS_APP, USIMM_NEED_FCP, ARRAYSIZE(ausUsimPath), ausUsimPath);
    }
    else
    {
        /* ����DFGSM���������� */
        ulResult = USIMM_SelectFile(USIMM_GSM_APP, USIMM_NEED_FCP, ARRAYSIZE(ausSimPath), ausSimPath);
    }

    if (ulResult != VOS_OK)/*����ļ���ѡ�н��*/
    {
        USIMM_ERROR_LOG("USIMM_PINHandle: Select Current DF is Failed");

        USIMM_PinHandleCnf((USIMM_PINHANDLE_REQ_STRU *)pMsg, VOS_ERR, &gstUSIMMADFInfo.stPINInfo);

        if(USIMM_SW_SENDCMD_ERROR == ulResult)
        {
            gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardType        = USIMM_CARD_NOCARD;
            gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardService     = USIMM_CARD_SERVIC_ABSENT;
            gastUSIMMCardAppInfo[USIMM_UICC_USIM].enStateChange     = USIMM_CARD_STATE_CHANGED; /*��Ҫ�ϱ���״̬*/
        }

        return VOS_ERR;
    }

    if (VOS_TRUE !=  USIMM_PinStatusCheck(stMsg.enCmdType, stMsg.enPINType, &ulResult))
    {
        USIMM_PinHandleCnf((USIMM_PINHANDLE_REQ_STRU *)pMsg, ulResult, &gstUSIMMADFInfo.stPINInfo);

        return VOS_ERR;
    }

    switch(stMsg.enCmdType)
    {
        case USIMM_PINCMD_DISABLE:   /*���ȥ�������֤PIN��ͬһ��������*/
        case USIMM_PINCMD_ENABLE:
        case USIMM_PINCMD_VERIFY:
            ulResult = USIMM_PINVerify(stMsg.enPINType, (VOS_UINT8)stMsg.enCmdType, stMsg.aucOldPIN);
            /*lint -e534*/
            VOS_MemCpy(stMsg.aucNewPIN, stMsg.aucOldPIN, USIMM_PINNUMBER_LEN);
            /*lint +e534*/
            break;

        case USIMM_PINCMD_CHANGE:           /*����PIN����*/
            ulResult = USIMM_ChangePIN(stMsg.enPINType,stMsg.aucOldPIN,stMsg.aucNewPIN);
            break;

        case USIMM_PINCMD_UNBLOCK:          /*����PIN����*/
            ulResult = USIMM_UnblockPIN(stMsg.enPINType, stMsg.aucOldPIN, stMsg.aucNewPIN);
            break;

        default:
            USIMM_WARNING_LOG("USIMM_PINHandle: The CMD Type is Error");
            ulResult = VOS_ERR;
            break;
    }

    (VOS_VOID)USIMM_AdjudgeCardState();    /*�жϵ�ǰ��״̬*/

    if (USIMM_PIN == stMsg.enPINType)    /*����PIN�����Ľ��*/
    {
        if (VOS_OK == ulResult)
        {
            /*lint -e534*/
            VOS_MemCpy(gstUSIMMADFInfo.aucPin1, stMsg.aucNewPIN, USIMM_PINNUMBER_LEN);/*��¼�ɹ�У�顢ȥ����򼤻���PIN1��*/
            /*lint +e534*/

            if (gstUSIMMPOOL.enPoolStatus < USIMM_POOL_AVAILABLE)        /*�����ǰ����ʼ��δ�������Ҫ������ʼ��*/
            {
                USIMM_INFO_LOG("USIMM_PINHandle: The Initialation is Continue, Go Into Secorend Step");

                USIMM_InitNeedPinSteps(USIMM_NORMAL_MODE);

                /* ��ʼ����ѡ�ļ� */
                if (VOS_OK != USIMM_InitThirdSteps())
                {
                    USIMM_ERROR_LOG("USIMM_PINHandle:USIMM_InitThirdSteps is Failed");

                    USIMM_PinHandleCnf((USIMM_PINHANDLE_REQ_STRU *)pMsg, VOS_ERR, &gstUSIMMADFInfo.stPINInfo);

                    return VOS_ERR;
                }
            }

            gstUSIMMPOOL.enPoolStatus = USIMM_POOL_AVAILABLE;

            /*lint -e534*/
            USIMM_SendInitCardMsg(WUEPS_PID_USIM, USIMM_INITCONTINUE_REQ);
            /*lint +e534*/
        }
        else
        {
            /*lint -e534*/
            VOS_MemSet(gstUSIMMADFInfo.aucPin1, 0, USIMM_PINNUMBER_LEN);
            /*lint +e534*/
        }
    }

    USIMM_PinHandleCnf((USIMM_PINHANDLE_REQ_STRU *)pMsg, ulResult, &gstUSIMMADFInfo.stPINInfo);

    return VOS_OK;
}


VOS_UINT32 USIMM_AutoVerifyPIN(USIMM_PIN_ENABLE_STATUS_ENUM_UINT32 enPinEnable,
                                     USIMM_PIN_VERIY_STATUS_ENUM_UINT32  *penPinVerified,
                                     VOS_UINT8                           ucPinRefNum,
                                     VOS_UINT8                           *pucPin)
{
    VOS_UINT32                      ulResult;

    if ((USIMM_PIN_ENABLED == enPinEnable)
     && (USIMM_PIN_NEED == *penPinVerified))
    {
        USIMM_NORMAL_LOG("USIMM_ProtectReset: Need Verify The Pin");

        if (0 == pucPin[0])  /*��ǰPIN����Ч����Ҫ�ϱ���״̬*/
        {
            if (USIMM_POOL_AVAILABLE == gstUSIMMPOOL.enPoolStatus)
            {
                gstUSIMMPOOL.enPoolStatus = USIMM_POOL_NEED_PASSWORD;
            }

            return USIMM_INIT_NEEDPIN;
        }

        /* �ɹ�У���PIN�룬���Զ�У��PIN�� */
        ulResult = USIMM_PINVerify_APDU(USIMM_PINCMD_VERIFY, ucPinRefNum, pucPin);

        if (VOS_OK != ulResult)/*�����*/
        {
            USIMM_ERROR_LOG("USIMM_ProtectReset: USIMM_PINVerify_APDU Error");

            return USIMM_INIT_FAIL;
        }

        ulResult = USIMM_CheckSW(&gstUSIMMAPDU);

        if (USIMM_SW_OK != ulResult) /*��ǰ�������ɹ�*/
        {
            USIMM_ERROR_LOG("USIMM_ProtectReset: Verify PIN1 Error");

            return USIMM_INIT_FAIL;
        }

        *penPinVerified = USIMM_NONEED;
    }

    return USIMM_INIT_OK;
}


VOS_UINT32 USIMM_CheckChangeCardByICCID(VOS_VOID)
{
    VOS_UINT32                      ulResult;
    VOS_UINT8                       aucOldIccid[20];
    VOS_UINT8                       aucNewIccid[20];
    USIMM_APP_TYPE_ENUM_UINT32      enAppType;

    enAppType   =   ((USIMM_CARD_SIM == gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardType)?USIMM_GSM_APP:USIMM_UMTS_APP);

    ulResult = USIMM_PoolReadOneFile(EFICCID, USIMM_READ_ALL_FILE_CONTENT, aucOldIccid, enAppType);

    if(VOS_OK != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_ProtectReset: USIMM_PoolReadOneFile EFICCID Error");

        return VOS_ERR;
    }

    /* ��ICCID */
    ulResult = USIMM_GetTFFile(enAppType, EFICCID, USIMM_READ_ALL_FILE_CONTENT, aucNewIccid);

    if(VOS_OK != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_ProtectReset: Select EFICCID Error");

        return VOS_ERR;
    }

    if(VOS_OK != VOS_MemCmp(aucOldIccid, aucNewIccid,gstUSIMMCurFileInfo.stEFInfo.usFileLen))
    {
        USIMM_ERROR_LOG("USIMM_ProtectReset: Not the same ICCID");

        return VOS_ERR;
    }

    return VOS_OK;
}
VOS_UINT32 USIMM_ProtectFirstStep(VOS_UINT32  ulOldCardType)
{
    VOS_UINT32  ulResult;
    VOS_INT32   lResult;
    VOS_UINT16  usFileID;

    /* ��λ���������λʧ�ܻὫ�����͵�ȫ�ֱ�����Ϊ�޿�����˸�λ�ɹ���Ҫ���ÿ����͵�ȫ�ֱ��� */
    if (VOS_OK != mdrv_sci_deact())
    {
        USIMM_ERROR_LOG("USIMM_ProtectFirstStep: Deactive Card Error");

        return VOS_ERR;
    }

    ulResult = USIMM_DLResetCard(USIMM_RESET_CARD, &lResult);

    if(VOS_OK != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_ProtectFirstStep: USIMM_DLResetCard Error");

        return VOS_ERR;
    }

    /* ���ÿ����͵�ȫ�ֱ��� */
    gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardType = ulOldCardType;

    /* ����SIM��Ҫѡ��GSMӦ�ã����л���ѹ */
    if(USIMM_CARD_SIM == gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardType)
    {
        ulResult = USIMM_Select2GApp();

        if(VOS_OK != ulResult)
        {
            USIMM_ERROR_LOG("USIMM_ProtectFirstStep: USIMM_Select2GApp is Failed");

            return VOS_ERR;
        }
    }

    /* ����USIM��Ҫ����MF fcp�л���ѹ */
    if(USIMM_CARD_USIM == gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardType)
    {
        usFileID = MF;

        ulResult = USIMM_SelectFile(USIMM_UMTS_APP, USIMM_NEED_FCP, 1, &usFileID);

        if(ulResult != VOS_OK)
        {
            USIMM_ERROR_LOG("USIMM_InsertNoNeedPinFileToPool: Select MF is Failed");

            gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardService = USIMM_CARD_SERVIC_UNAVAILABLE;          /*����ǰ������*/

            return VOS_ERR;
        }

        ulResult = USIMM_UsimVoltageSwitch(gstUSIMMCurFileInfo.stDFInfo.ucCharaByte,
                                           &g_stUSIMMInitInfo.stUSIMMInfo.ucVoltageSwitchFlag);

        if(ulResult != VOS_OK)
        {
            USIMM_ERROR_LOG("USIMM_InsertNoNeedPinFileToPool: Select MF is Failed");

            gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardService = USIMM_CARD_SERVIC_UNAVAILABLE;          /*����ǰ������*/

            return VOS_ERR;
        }

        USIMM_UsimTerminalCapability();

    }

    return VOS_OK;
}


VOS_UINT32 USIMM_ProtectSecondStep(VOS_VOID)
{
    if(USIMM_CARD_USIM == gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardType)
    {
        /* �·�profileDownload */
        /*lint -e534*/
        USIMM_UsimProfileDownload();
        /*lint +e534*/

        /* ����UICC */
        if(VOS_ERR == USIMM_SelectUiccADF())
        {
            USIMM_ERROR_LOG("USIMM_ProtectReset: USIMM_SelectUiccADF Error");    /*��ӡ����*/
            return VOS_ERR;
        }
    }

    if(VOS_ERR == USIMM_InitCardPINInfo())    /*��ȡPIN����*/
    {
        USIMM_ERROR_LOG("USIMM_ProtectReset: USIMM_InitCardPINInfo Error");    /*��ӡ����*/
        return VOS_ERR;
    }

    /*lint -e534*/
    USIMM_AdjudgeCardState();
    /*lint +e534*/

    return VOS_OK;
}
VOS_VOID USIMM_ResumeAppChannel(VOS_VOID)
{
    VOS_UINT32      ulAIDLen = 0;
    VOS_UINT8       aucADFName[USIMM_AID_LEN_MAX];
    VOS_UINT32      ulResult;
    VOS_UINT8       ucOldChanNum;
    VOS_UINT8       ucNewChanNum = 0;
    VOS_UINT32      ulSessionId = 0;
    VOS_UINT8       i;
    USIMM_APDU_ST   stApduInfo;

    if(VOS_FALSE == USIMM_IsCLEnable())
    {
        /* ����߼�ͨ����Ϣ�����ǻ���ͨ������ */
        /*lint -e534*/
        VOS_MemSet(&g_astUSIMMChCtrl[1], 0, sizeof(USIMM_CHANNEL_INFO_STRU)*(USIMM_CHANNEL_NUM_MAX - 1));
        /*lint +e534*/

        return;
    }

    /*lint -e534*/
    VOS_MemSet(&stApduInfo, 0, sizeof(stApduInfo));
    /*lint +e534*/

    ulResult = USIMM_GetAid(USIMM_AID_TYPE_CSIM, &ulAIDLen, aucADFName);

    if (VOS_OK == ulResult)
    {
        ulResult = USIMM_GetUiccChanNumByAid(aucADFName, ulAIDLen, &ucOldChanNum);

        if ((VOS_OK != ulResult) || (ucOldChanNum >= USIMM_CHANNEL_NUM_MAX))
        {
            USIMM_ERROR_LOG("USIMM_ResumeAppChannel: USIMM_GetUiccChanNumByAid failed.");

            /* ����߼�ͨ����Ϣ�����ǻ���ͨ������ */
            /*lint -e534*/
            VOS_MemSet(&g_astUSIMMChCtrl[1], 0, sizeof(USIMM_CHANNEL_INFO_STRU)*(USIMM_CHANNEL_NUM_MAX - 1));
            /*lint +e534*/

            return;
        }

        ulSessionId = g_astUSIMMChCtrl[ucOldChanNum].ulSessionId;

        /* ����߼�ͨ����Ϣ�����ǻ���ͨ������ */
        /*lint -e534*/
        VOS_MemSet(&g_astUSIMMChCtrl[1], 0, sizeof(USIMM_CHANNEL_INFO_STRU)*(USIMM_CHANNEL_NUM_MAX - 1));
        /*lint +e534*/

        while (ucOldChanNum > ucNewChanNum)
        {
            /* �·�manage���߼�ͨ��,��ͨ����ʱ���ڻ����߼�ͨ���ϣ����P2����Ϊ0,P3������1����������һ���ֽڵ�channelID */
            if (VOS_OK != USIMM_Manage_Channel_APDU(USIMM_OPEN_CHANNEL, 0, 1))
            {
                USIMM_ERROR_LOG("USIMM_ResumeAppChannel: The USIMM_Manage_Channel_APDU Return Error");

                return;
            }

            ulResult = USIMM_CheckSW(&gstUSIMMAPDU);

            /*�жϼ����*/
            if (USIMM_SW_OK != ulResult)
            {
                USIMM_WARNING_LOG("USIMM_ResumeAppChannel: USIMM_CheckSW Error");

                return;
            }

            ucNewChanNum = gstUSIMMAPDU.aucRecvBuf[0];

            /* ͨ��ID�����Ϸ���Χ */
            if (USIMM_CHANNEL_NUM_MAX <= ucNewChanNum)
            {
                USIMM_ERROR_LOG("USIMM_ResumeAppChannel: Channel ID is not valid.");

                /*lint -e534*/
                USIMM_CloseChannel(ucNewChanNum);
                /*lint +e534*/

                return;
            }
        }

        for (i = 1; i < ucNewChanNum; i++)
        {
            /*lint -e534*/
            USIMM_CloseChannel(i);
            /*lint +e534*/
        }

        stApduInfo.aucAPDU[CLA] = USIMM_USIM_CLA;

        stApduInfo.aucAPDU[P1] = USIMM_SELECT_BY_DF_NAME;
        stApduInfo.aucAPDU[P2] = USIMM_SELECT_RETURN_FCP_TEMPLATE;
        stApduInfo.aucAPDU[P3] = (VOS_UINT8)ulAIDLen;

        /*lint -e534*/
        VOS_MemCpy(stApduInfo.aucSendBuf, aucADFName, ulAIDLen);
        /*lint +e534*/

        /* �·�����AID�������ݵ�Ԫ,cla�ֶ�Ӧ���ڴ򿪵��߼�ͨ���� */
        ulResult = USIMM_SelectFileByChannelID_APDU(ucNewChanNum, &stApduInfo);

        if (VOS_OK != ulResult)
        {
            USIMM_ERROR_LOG("USIMM_ResumeAppChannel: select csim aid failed.");

            /*lint -e534*/
            USIMM_CloseChannel(ucNewChanNum);
            /*lint +e534*/

            return;
        }

        ulResult = USIMM_CheckSW(&stApduInfo);

        if (USIMM_SW_OK != ulResult)
        {
            USIMM_ERROR_LOG("USIMM_ResumeAppChannel: USIMM_CheckSW failed.");

            /*lint -e534*/
            USIMM_CloseChannel(ucNewChanNum);
            /*lint +e534*/

            return;
        }

        g_astUSIMMChCtrl[ucNewChanNum].ulSessionId = ulSessionId;
        g_astUSIMMChCtrl[ucNewChanNum].ulChanNum   = ucNewChanNum;

        /*lint -e534*/
        VOS_MemCpy(g_astUSIMMChCtrl[ucNewChanNum].aucADFName, aucADFName, ulAIDLen);
        /*lint +e534*/

        g_astUSIMMChCtrl[ucNewChanNum].ulAIDLen = ulAIDLen;
    }
    else
    {
        /* ����߼�ͨ����Ϣ�����ǻ���ͨ������ */
        /*lint -e534*/
        VOS_MemSet(&g_astUSIMMChCtrl[1], 0, sizeof(USIMM_CHANNEL_INFO_STRU)*(USIMM_CHANNEL_NUM_MAX - 1));
        /*lint +e534*/
    }

    return;
}

#if(FEATURE_ON == FEATURE_PTM)

VOS_VOID USIMM_CardErrorLogReport(VOS_VOID)
{
    OM_ERR_LOG_REPORT_CNF_STRU                *pstCnfMsg;

    if (OM_APP_STATUS_CLOSE == g_stErrLogCtrlInfo.ucAlmStatus)
    {
        return;
    }

    /* ������Ϣ�ڴ�  */
    pstCnfMsg = (OM_ERR_LOG_REPORT_CNF_STRU*)VOS_AllocMsg(WUEPS_PID_USIM, sizeof(OM_ERR_LOG_REPORT_CNF_STRU)
                                                                          - VOS_MSG_HEAD_LENGTH
                                                                          - 4
                                                                          + sizeof(g_stCardErrorLog));
    if (VOS_NULL_PTR == pstCnfMsg)
    {
        USIMM_ERROR_LOG("USIMM_CardErrorLogReport: VOS_AllocMsg is Failed");

        return;
    }

    /* ���cnf��Ϣ */
    pstCnfMsg->ulReceiverPid    = MSP_PID_DIAG_APP_AGENT;
    pstCnfMsg->ulMsgName        = ID_OM_ERR_LOG_REPORT_CNF;
    pstCnfMsg->ulMsgType        = OM_ERR_LOG_MSG_ERR_REPORT;
    pstCnfMsg->ulRptlen         = sizeof(g_stCardErrorLog);

    /*lint -e419 -e534 */
    VOS_MemCpy(pstCnfMsg->aucContent, &g_stCardErrorLog, sizeof(g_stCardErrorLog));
    /*lint +e419 +e534 */

    /* �ظ���Ϣ */
    (VOS_VOID)VOS_SendMsg(pstCnfMsg->ulSenderPid, pstCnfMsg);

    return;
}
VOS_VOID USIMM_RecordCardErrorLog(
    USIMM_MNTN_STATE_ERROR_REASON_ENUM_UINT32                   enErrorReason,
    USIMM_MNTN_ERROR_LEVEL_ENUM_UINT16                          enAlmLevel)
{
    VOS_INT32       lResult;
    VOS_UINT32      ulLength;

    g_stCardErrorLog.stHeader.ulMsgModuleId = OM_ERR_LOG_MOUDLE_ID_USIMM;

#if defined (INSTANCE_1)
    g_stCardErrorLog.stHeader.usModemId = MODEM_ID_1; /* ��ʶ�������� */
#elif defined (INSTANCE_2)
    g_stCardErrorLog.stHeader.usModemId = MODEM_ID_2;
#else
    g_stCardErrorLog.stHeader.usModemId = MODEM_ID_0;
#endif

    g_stCardErrorLog.stHeader.usAlmId = 1;
    g_stCardErrorLog.stHeader.usAlmLevel = enAlmLevel;
    g_stCardErrorLog.stHeader.usAlmType = 0;        /* 0����ͨ�Ÿ澯 */
    g_stCardErrorLog.stHeader.usAlmLowSlice = OM_GetSlice();
    g_stCardErrorLog.stHeader.usAlmHighSlice = 0;   /* ��ʱ���ã�Ĭ����0 */

    g_stCardErrorLog.enStateErrorReason = enErrorReason;

    /* ���õ���ӿڻ�ȡ������� */
    lResult = mdrv_sci_read_recordlog((VOS_UINT8 *)&g_stCardErrorLog.stSCIRecordInfo,
                                  &ulLength, sizeof(g_stCardErrorLog.stSCIRecordInfo));

    if (VOS_OK != lResult)
    {
        USIMM_ERROR_LOG("USIMM_RecordCardErrorLog: DRV API RETURN ERR");
    }

    g_stCardErrorLog.stHeader.ulAlmLength = sizeof(VOS_UINT32) + sizeof(SCI_RECORD_INFO_S) + sizeof(g_stCardErrorLog.aulRsv);

    return;
}
#endif


VOS_UINT32 USIMM_ProtectReset(USIMM_CMDHEADER_REQ_STRU *pstMsg)
{
    VOS_UINT32                          ulResult = VOS_ERR;
    VOS_UINT32                          i;
    VOS_UINT32                          ulOldCardStatus;
    VOS_UINT32                          ulOldCardType;

    /* ���ٿ���ģʽ */
    if (USIMM_OPENSPEEDENABLE == gulUSIMMOpenSpeed)/*��״̬���*/
    {
        USIMM_SingleCmdCnf(pstMsg->ulSenderPid,
                           USIMM_PROTECTRESET_CNF,
                           pstMsg->ulSendPara,
                           VOS_ERR,
                           pstMsg->enAppType);

        return VOS_OK;
    }

    /* vSIM���ܴ� */
    if (VOS_TRUE == USIMM_VsimIsActive())
    {
        USIMM_SingleCmdCnf(pstMsg->ulSenderPid,
                           USIMM_PROTECTRESET_CNF,
                           pstMsg->ulSendPara,
                           VOS_ERR,
                           pstMsg->enAppType);

        return VOS_OK;
    }

    /* ��ǰ�Ѿ��޿�����²��������Ը�λ��ֱ�ӻظ�ʧ�� */
    if (USIMM_CARD_SERVIC_ABSENT == gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardService)
    {
        USIMM_SingleCmdCnf(pstMsg->ulSenderPid,
                           USIMM_PROTECTRESET_CNF,
                           pstMsg->ulSendPara,
                           VOS_ERR,
                           pstMsg->enAppType);

        return VOS_OK;
    }

    USIMM_NORMAL_LOG("USIMM_ProtectReset: Protect Reset Start");

    /* ���汣���Ը�λ֮ǰ�Ŀ�״̬ */
    ulOldCardStatus = gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardService;
    ulOldCardType   = gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardType;

    /*�ϱ�SDT*/
    USIMM_ReportEvent(USIMM_PROTECT_RESET);

    if((USIMM_CARD_USIM != ulOldCardType) && (USIMM_CARD_SIM != ulOldCardType))
    {
        USIMM_ERROR_LOG("USIMM_ProtectReset: Card type is neither SIM nor USIM");
        USIMM_SingleCmdCnf(pstMsg->ulSenderPid,
                           USIMM_PROTECTRESET_CNF,
                           pstMsg->ulSendPara,
                           VOS_ERR,
                           pstMsg->enAppType);
        return VOS_ERR;
    }

    for(i = 0; i < USIMM_PROTECT_MAX_NUM; i++)
    {
#if (VOS_OS_VER != VOS_WIN32)       /* PC Stub */
        HPA_USIMLowPowerLock(WUEPS_PID_USIM);
#endif
        /*lint -e534*/
        VOS_TaskDelay((i*100));
        /*lint +e534*/

#if (VOS_OS_VER != VOS_WIN32)       /* PC Stub */
    HPA_USIMLowPowerUnLock(WUEPS_PID_USIM);
#endif

        USIMM_ClearCurFileInfo();

        USIMM_T1InitGlobalVar();

        ulResult = USIMM_ProtectFirstStep(ulOldCardType);

        if(VOS_OK != ulResult)
        {
            USIMM_ERROR_LOG("USIMM_ProtectReset: USIMM_ProtectFirstStep is err");    /*��ӡ����*/

            continue;
        }

        ulResult = USIMM_CheckChangeCardByICCID();

        if(VOS_OK != ulResult)
        {
            USIMM_ERROR_LOG("USIMM_ProtectReset: the card has changed!");    /*��ӡ����*/

            break;
        }

        ulResult = USIMM_ProtectSecondStep();

        if(VOS_OK != ulResult)
        {
            USIMM_ERROR_LOG("USIMM_ProtectReset: the USIMM_ProtectSecondStep is Error!");    /*��ӡ����*/

            continue;
        }

        /* �ɹ�У���PIN�룬���Զ�У��PIN�� */
        ulResult = USIMM_AutoVerifyPIN(gstUSIMMADFInfo.stPINInfo.enPin1Enable,
                                       &gstUSIMMADFInfo.enPin1Verified,
                                       gstUSIMMADFInfo.ucPIN1RefNum,
                                       gstUSIMMADFInfo.aucPin1);

        if(USIMM_INIT_FAIL == ulResult)
        {
            USIMM_ERROR_LOG("USIMM_ProtectReset: the USIMM_ProtectSecondStep is Error!");    /*��ӡ����*/

            continue;
        }

        /* δУ��pin�룬��Ҫ�ϱ���״̬ */
        if(USIMM_INIT_NEEDPIN == ulResult)
        {
            ulResult = VOS_OK;

            break;
        }

        if(USIMM_CARD_SIM == gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardType)
        {
            /*lint -e534*/
            USIMM_SimProfileDownload(USIMM_PROTECT_RESET_MODE);
            USIMM_InitSimFDNBDNStatus();
            /*lint +e534*/
        }

        /*lint -e534*/
        USIMM_AdjudgeCardState();
        /*lint +e534*/

        if(USIMM_CARD_SERVIC_AVAILABLE == gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardService)
        {
            gstUSIMMPOOL.enPoolStatus = USIMM_POOL_AVAILABLE;
        }

        break;
    }

    if ((VOS_OK == ulResult) && (ulOldCardStatus == gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardService))
    {
        gastUSIMMCardAppInfo[USIMM_UICC_USIM].enStateChange = USIMM_CARD_STATE_NOCHANGE;

        USIMM_ResumeAppChannel();
    }

    if (VOS_OK != ulResult)
    {
        /*lint -e534*/
        USIMM_DeactiveRealCard((USIMM_MsgBlock *)pstMsg);
        /*lint +e534*/
#if(FEATURE_ON == FEATURE_PTM)
        USIMM_RecordCardErrorLog(USIMM_MNTN_STATE_POLLING_FAIL, USIMM_MNTN_ERROR_LEVEL_CRITICAL);
#endif
    }

    USIMM_SingleCmdCnf(pstMsg->ulSenderPid,
                       USIMM_PROTECTRESET_CNF,
                       pstMsg->ulSendPara,
                       ulResult,
                       pstMsg->enAppType);

    USIMM_NORMAL_LOG("USIMM_ProtectReset: Protect Reset End");

    return VOS_OK;
}


VOS_UINT32 USIMM_StatusHandle(USIMM_CMDHEADER_REQ_STRU *pMsg)
{
    VOS_UINT32                          ulResult = VOS_ERR;
    USIMM_STATUSCMD_REQ_STRU           *pstMsg;

    pstMsg = (USIMM_STATUSCMD_REQ_STRU *)pMsg;

    if (VOS_OK != USIMM_ApiParaCheck())
    {
        USIMM_SingleCmdCnf(pMsg->ulSenderPid,
                           USIMM_STATUSCMD_CNF,
                           pMsg->ulSendPara,
                           ulResult,
                           pMsg->enAppType);

        return ulResult;
    }

    if (pstMsg->enNeedFcp == USIMM_POLL_NEED_FCP)
    {
        ulResult = USIMM_STATUSProc();
    }
    else
    {
        ulResult = USIMM_Status_APDU(USIMM_STATUS_NO_INDICATION, USIMM_STATUS_NO_DATA_RETURNED, 0);

        if (VOS_OK != ulResult)
        {
            ulResult = USIMM_SW_SENDCMD_ERROR;
        }
        else if (VOS_OK != USIMM_CheckSW(&gstUSIMMAPDU))
        {
            if (VOS_OK != USIMM_CheckChangeCardByICCID())
            {
                ulResult = USIMM_SW_ERR;
            }
        }
        else
        {

        }
    }

    USIMM_SingleCmdCnf(pMsg->ulSenderPid,
                       USIMM_STATUSCMD_CNF,
                       pMsg->ulSendPara,
                       ulResult,
                       pMsg->enAppType);

    return ulResult;
}


VOS_UINT32 USIMM_UpdateFile(USIMM_EF_TYPE_ENUM_UINT32  enEFFileType,
                                 VOS_UINT8                   ucRecordNum,
                                 VOS_UINT16                  usDataLen,
                                 VOS_UINT8                   *pucData)
{
    VOS_UINT32                              ulResult;

    switch (enEFFileType)
    {
        case USIMM_EFSTRUCTURE_TRANSPARENT:

            /*���¶������ļ�*/
            ulResult = USIMM_UpdateTFFile(usDataLen, pucData);
            break;

        case USIMM_EFSTRUCTURE_FIXED:

            /*���¼�¼�ļ�*/
            ulResult = USIMM_UpdateLFFile(ucRecordNum, pucData, (VOS_UINT8)usDataLen);
            break;

        case USIMM_EFSTRUCTURE_CYCLE:

            /*����ѭ���ļ�*/
            ulResult = USIMM_UpdateCLFFile(pucData, (VOS_UINT8)usDataLen);
            break;

        default:
            USIMM_WARNING_LOG("USIMM_SetFileHandle: The File Type is Not Support");
            ulResult = USIMM_SW_FILETYPE_ERROR;
            break ;
    }

    return ulResult;
}
VOS_UINT32 USIMM_SelectFile(USIMM_APP_TYPE_ENUM_UINT32         enFileApp,
                                USIMM_FILE_NEED_FCP_ENUM_UINT32     enEfFcpFlag,
                                VOS_UINT32                          ulPathLen,
                                VOS_UINT16                         *pusFilePath)
{
    VOS_UINT32                          ulResult;
    USIMM_SELECT_PARA_STUR              stSelectPara;
    USIMM_U16_LVDATA_STRU               stFilePath;

    if (VOS_NULL_PTR == pusFilePath)
    {
        USIMM_ERROR_LOG("USIMM_SelectFile:Input Parameter error.");

        return USIMM_SW_ERR;
    }

    stSelectPara.enFileApp      = enFileApp;
    stSelectPara.enCardType     = gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardType;
    stSelectPara.enEfFcpFlag    = enEfFcpFlag;

    stFilePath.ulDataLen        = ulPathLen;
    stFilePath.pusData          = pusFilePath;

    /* ѡ���ļ����� */
    ulResult = USIMM_SelectFileHandle(&stSelectPara, &stFilePath);

    if(ulResult != USIMM_SW_OK)
    {
        USIMM_ERROR_LOG("USIMM_SelectFile: Select File with Path Error.");
    }

    return ulResult;
}
VOS_UINT32 USIMM_GetFileAllPath(USIMM_SELECT_PARA_STUR       *pstSelectPara,
                                        USIMM_U16_LVDATA_STRU      *pstFilePathIn,
                                        USIMM_U16_LVDATA_STRU      *pstFilePathOut)
{
    VOS_UINT32                          ulResult = VOS_ERR;
    VOS_UINT32                          ulPathAllLen = 0;
    VOS_UINT16                          ausPathTemp[USIMM_MAX_PATH_LEN] = {0};
    VOS_UINT16                          ausPathAll[USIMM_MAX_PATH_LEN] = {0};
#if 0
    VOS_UINT32                          i;
    VOS_UINT8                           aucTypeTemp[USIMM_MAX_PATH_LEN] = {0};
    VOS_UINT8                           aucTypeOK0[] = {MFTAG};
    VOS_UINT8                           aucTypeOK1[] = {MFTAG, EFUNDERMF};
    VOS_UINT8                           aucTypeOK2[] = {MFTAG, DFUNDERMF};
    VOS_UINT8                           aucTypeOK3[] = {MFTAG, DFUNDERMF, EFUNDERDF};
    VOS_UINT8                           aucTypeOK4[] = {MFTAG, DFUNDERMF, DFUNDERDF};
    VOS_UINT8                           aucTypeOK5[] = {MFTAG, DFUNDERMF, DFUNDERDF, EFUNDERGRANDADF};
#endif

    /* ���ļ�ID��Ϊ·�� */
    if (1 == pstFilePathIn->ulDataLen)
    {
        ulResult = USIMM_GetCardFilePath(pstSelectPara->enFileApp, pstFilePathIn->pusData[0], &ulPathAllLen, ausPathTemp);
    }

    /* ����Ϊ·�� �� ͨ���ļ�ID���·��ʧ�� */
    if (VOS_OK != ulResult)
    {
        /*lint -e534*/
        VOS_MemCpy(ausPathTemp, pstFilePathIn->pusData, (pstFilePathIn->ulDataLen)*sizeof(VOS_UINT16));
        /*lint +e534*/
        ulPathAllLen = pstFilePathIn->ulDataLen;
    }

    /* ȷ��·�����Ǿ���·�� */
    if (MFTAG == USIMM_FILE_TYPE(ausPathTemp[0]))
    {
        /*lint -e534*/
        VOS_MemCpy(ausPathAll, ausPathTemp, ulPathAllLen*sizeof(VOS_UINT16));
        /*lint +e534*/
    }
    else
    {
        ausPathAll[0] = MF;

        /*lint -e534*/
        VOS_MemCpy(&ausPathAll[1], ausPathTemp, ulPathAllLen*sizeof(VOS_UINT16));
        /*lint +e534*/

        ulPathAllLen++;
    }

    /*lint -e534*/
    VOS_MemCpy(pstFilePathOut->pusData, ausPathAll, ulPathAllLen*sizeof(VOS_UINT16));
    /*lint +e534*/

    pstFilePathOut->ulDataLen = ulPathAllLen;

    return VOS_OK;

#if 0
    /* ������·����Ϊ������ʽ */
    for (i = 0; i < ulPathAllLen; i++)
    {
        aucTypeTemp[i] = USIMM_FILE_TYPE(ausPathAll[i]);
    }

    /* ATT�����ý���·���Ϸ��Լ�� */
    if (USIMM_ATT_APP == pstSelectPara->enFileApp)
    {
        ulResult = VOS_OK;
    }
    else
    {
        ulResult = (VOS_UINT32)VOS_MemCmp(aucTypeOK0, aucTypeTemp, ulPathAllLen);
    }

    if (ulResult != VOS_OK)
    {
        ulResult = (VOS_UINT32)VOS_MemCmp(aucTypeOK1, aucTypeTemp, ulPathAllLen);
    }

    if (ulResult != VOS_OK)
    {
        ulResult = (VOS_UINT32)VOS_MemCmp(aucTypeOK2, aucTypeTemp, ulPathAllLen);
    }

    if (ulResult != VOS_OK)
    {
        ulResult = (VOS_UINT32)VOS_MemCmp(aucTypeOK3, aucTypeTemp, ulPathAllLen);
    }

    if (ulResult != VOS_OK)
    {
        ulResult = (VOS_UINT32)VOS_MemCmp(aucTypeOK4, aucTypeTemp, ulPathAllLen);
    }

    if (ulResult != VOS_OK)
    {
        ulResult = (VOS_UINT32)VOS_MemCmp(aucTypeOK5, aucTypeTemp, ulPathAllLen);
    }

    if (VOS_OK == ulResult)
    {
        /* lint -e534 */
        VOS_MemCpy(pstFilePathOut->pusData, ausPathAll, ulPathAllLen*sizeof(VOS_UINT16));
        /* lint +e534 */

        pstFilePathOut->ulDataLen = ulPathAllLen;
    }

    return ulResult;
#endif

}
VOS_UINT32 USIMM_SelectFileHandle(USIMM_SELECT_PARA_STUR        *pstSelectPara,
                                        USIMM_U16_LVDATA_STRU          *pstFilePath)
{
    VOS_UINT16                          ausFileAllPath[USIMM_MAX_PATH_LEN] = {0};
    USIMM_U16_LVDATA_STRU               stFileAllPath = {0};
    VOS_UINT16                          usCurPathLen = 0;
    VOS_UINT32                          ulResult;

    /* ������� */
    if ((VOS_NULL_PTR == pstSelectPara)||(VOS_NULL_PTR == pstFilePath))
    {
        USIMM_ERROR_LOG("USIMM_SelectFileHandle:Input Parameter error.");

        return USIMM_SW_ERR;
    }

    stFileAllPath.pusData = ausFileAllPath;

    /* ��ȡѡ���ļ���ȫ·�� */
    if (VOS_OK != USIMM_GetFileAllPath(pstSelectPara, pstFilePath, &stFileAllPath))
    {
        USIMM_ERROR_LOG("USIMM_SelectFileHandle:Can't find the file.");

        return USIMM_SW_NOFILE_FOUND;
    }

    /* ѡ���ļ��Ѿ��ǵ�ǰ�ļ����˳������سɹ� */
    ulResult = USIMM_CardFilePathCMP(stFileAllPath.ulDataLen, stFileAllPath.pusData,
                    gstUSIMMCurFileInfo.usFilePathLen, gstUSIMMCurFileInfo.ausFilePath);

    if (VOS_OK == ulResult)
    {
        if (USIMM_IS_DF_FILE(stFileAllPath.pusData[stFileAllPath.ulDataLen-1])
            || (0 != gstUSIMMCurFileInfo.stEFInfo.usFileLen)
            || (USIMM_NO_NEED_FCP == pstSelectPara->enEfFcpFlag))
        {
            USIMM_INFO_LOG("USIMM_SelectFileHandle: Selected file is current file.");

            return USIMM_SW_OK;
        }
    }

    /* ͨ��ȫ·��ѡ���ļ� */
    ulResult = USIMM_SelectFileWithPath(pstSelectPara, &stFileAllPath, &gstUSIMMCurFileInfo, &usCurPathLen);

    if (VOS_NULL == usCurPathLen)
    {
        USIMM_ClearCurFileInfo();
    }
    else
    {
        stFileAllPath.ulDataLen = usCurPathLen;

        /* ����·�� */
        USIMM_UpdateFilePath(pstSelectPara, &stFileAllPath, &gstUSIMMCurFileInfo);
    }

    return ulResult;
}
VOS_UINT32 USIMM_CheckSetFilePara(USIMM_EFFCP_ST *pstCurEFFcp, VOS_UINT8 ucRecordNum, VOS_UINT16 usDataLen)
{
    VOS_UINT32                          ulResult = USIMM_SW_OK;

    switch (pstCurEFFcp->enFileType)
    {
        case USIMM_EFSTRUCTURE_TRANSPARENT:
            /*�����������Ƿ����*/
            if(pstCurEFFcp->usFileLen < usDataLen)
            {
                USIMM_ERROR_LOG("USIMM_CheckSetFilePara: The Length of Data is too Large to the File");

                ulResult = USIMM_SW_OUTOF_RANGE;
            }

            break;

        case USIMM_EFSTRUCTURE_FIXED:
            /*�����µļ�¼���Ƿ�Խ��*/
            if(pstCurEFFcp->ucRecordNum < ucRecordNum)
            {
                USIMM_ERROR_LOG("USIMM_CheckSetFilePara: The Record Index of Data is Out of File Range");

                ulResult = USIMM_SW_OUTOF_RANGE;
            }

            break;

        case USIMM_EFSTRUCTURE_CYCLE:
            ulResult = USIMM_SW_OK;
            break;

        default:
            USIMM_WARNING_LOG("USIMM_CheckSetFilePara: The File Type is Not Support");
            ulResult = USIMM_SW_CMD_ERROR;
            break;
    }

    return ulResult;
}


VOS_UINT32 USIMM_SetFileCommHandle(USIMM_SET_COMM_FILE_STRU  *pstSetFileInfo)
{
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulFileIndex;
    USIMM_FILE_NEED_FCP_ENUM_UINT32     enFcpFlag;
    VOS_BOOL                            bParaCheckFlag;
    USIMM_EFFCP_ST                      stEFFcp;

    /*lint -e534*/
    VOS_MemSet(&stEFFcp, 0, sizeof(stEFFcp));
    /*lint +e534*/

    /* ���ж��Ƿ���ȷ���ļ����� */
    if (USIMM_EFSTRUCTURE_NONE == pstSetFileInfo->enEFFileType)
    {
        bParaCheckFlag = VOS_TRUE;

        if (VOS_OK == USIMM_PoolFindFile(pstSetFileInfo->usFileID, &ulFileIndex, pstSetFileInfo->enAppType))
        {
            enFcpFlag                               = USIMM_NO_NEED_FCP;
            stEFFcp.enFileType = gstUSIMMPOOL.astpoolRecord[ulFileIndex].enFileType;
            stEFFcp.usFileLen  = gstUSIMMPOOL.astpoolRecord[ulFileIndex].usLen;
        }
        else
        {
            enFcpFlag                               = USIMM_NEED_FCP;
        }
    }
    else
    {
        stEFFcp.enFileType = pstSetFileInfo->enEFFileType;
        enFcpFlag          = USIMM_NO_NEED_FCP;
        bParaCheckFlag     = VOS_FALSE;
    }

    ulResult = USIMM_SelectFile(pstSetFileInfo->enAppType, enFcpFlag, 1, &pstSetFileInfo->usFileID);

    if(USIMM_SW_OK != ulResult)/*�ж�ѡ����*/
    {
        USIMM_WARNING_LOG("USIMM_SetFileCommHandle: Select File is Failed");

        return ulResult;
    }

    if (USIMM_NEED_FCP == enFcpFlag)
    {
        /*lint -e534*/
        VOS_MemCpy(&stEFFcp, &(gstUSIMMCurFileInfo.stEFInfo), sizeof(stEFFcp));
        /*lint +e534*/
    }

    if (VOS_TRUE == bParaCheckFlag)
    {
        ulResult = USIMM_CheckSetFilePara(&stEFFcp, pstSetFileInfo->ucRecordNum, pstSetFileInfo->usDataLen);

        if(USIMM_SW_OK != ulResult)/*�ж�ѡ����*/
        {
            USIMM_WARNING_LOG("USIMM_SetFileCommHandle: USIMM_CheckSetFilePara is Failed");

            return ulResult;
        }
    }

    /* �����ļ����͸����ļ� */
    ulResult = USIMM_UpdateFile(stEFFcp.enFileType, pstSetFileInfo->ucRecordNum, pstSetFileInfo->usDataLen, pstSetFileInfo->pucData);

    if(USIMM_SW_OK != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_SetFileCommHandle: Update File Content is Failed");

        return ulResult;
    }

    /* ����ļ������ڻ���������Ҫ���� */
    if (USIMM_SW_OK == USIMM_PoolDelOneFile(pstSetFileInfo->usFileID, pstSetFileInfo->enAppType))
    {
        /*lint -e534*/
        USIMM_PoolInsertOneFile(pstSetFileInfo->usFileID, pstSetFileInfo->usDataLen, pstSetFileInfo->pucData,
                                pstSetFileInfo->enAppType, stEFFcp.enFileType);
        /*lint +e534*/
    }

    return USIMM_SW_OK;
}
VOS_UINT32 USIMM_SetUsimFileHandle(USIMM_SETFILE_REQ_STRU *pstMsg)
{
    USIMM_SET_COMM_FILE_STRU            stSetFileInfo = {0};

    stSetFileInfo.enAppType         = pstMsg->enAppType;
    stSetFileInfo.usFileID          = pstMsg->usFileID;
    stSetFileInfo.usDataLen         = pstMsg->usDataLen;
    stSetFileInfo.ucRecordNum       = pstMsg->ucRecordNum;
    stSetFileInfo.pucData           = pstMsg->aucContent;

    return USIMM_SetFileCommHandle(&stSetFileInfo);
}


VOS_UINT32 USIMM_SetPBFileHandle(USIMM_SETFILE_REQ_STRU *pstMsg)
{
    USIMM_SET_COMM_FILE_STRU            stSetFileInfo;

    stSetFileInfo.enAppType         = pstMsg->enAppType;
    stSetFileInfo.usFileID          = pstMsg->usFileID;
    stSetFileInfo.usDataLen         = pstMsg->usDataLen;
    stSetFileInfo.ucRecordNum       = pstMsg->ucRecordNum;
    stSetFileInfo.pucData           = pstMsg->aucContent;

    /* �⼸���绰���ļ�Ϊ�������ļ� */
    if((EFPSC == pstMsg->usFileID) || (EFCC == pstMsg->usFileID) || (EFPUID == pstMsg->usFileID))
    {
        stSetFileInfo.enEFFileType    = USIMM_EFSTRUCTURE_TRANSPARENT;
    }
    else
    {
        stSetFileInfo.enEFFileType    = USIMM_EFSTRUCTURE_FIXED;
    }

    return USIMM_SetFileCommHandle(&stSetFileInfo);
}
VOS_UINT32 USIMM_SetIsimFileHandle(USIMM_SETFILE_REQ_STRU *pstMsg)
{
    USIMM_SET_COMM_FILE_STRU            stSetFileInfo;
    VOS_UINT16                          usFileID = VOS_NULL_WORD;
    VOS_UINT32                          ulResult = VOS_OK;

    /*lint -e534*/
    VOS_MemSet(&stSetFileInfo, 0, sizeof(stSetFileInfo));
    /*lint +e534*/

    /* ��ǰISIM�����񲻿��� */
    if (USIMM_CARD_SERVIC_AVAILABLE != gastUSIMMCardAppInfo[USIMM_UICC_ISIM].enCardService)
    {
        USIMM_WARNING_LOG("USIMM_SetIsimFileHandle: ISIM app unavailable");

        return USIMM_SW_ERR;
    }

    stSetFileInfo.enAppType         = pstMsg->enAppType;
    stSetFileInfo.usFileID          = pstMsg->usFileID;
    stSetFileInfo.usDataLen         = pstMsg->usDataLen;
    stSetFileInfo.ucRecordNum       = pstMsg->ucRecordNum;
    stSetFileInfo.pucData           = pstMsg->aucContent;

    /* ����ISIM�ļ�ID���Ҷ�Ӧ��USIM�ļ�ID �Ҳ�����Ӧ��USIM�ļ�ID����Ϊ�ļ����ɸ��� */
    usFileID = USIMM_IsimEFIDToUsimEFID(stSetFileInfo.usFileID);

    /* �Ҳ�����Ӧ��USIM�ļ�ID */
    if (VOS_NULL_WORD == usFileID)
    {
        /* �ļ����ɸ��� */
        USIMM_WARNING_LOG("USIMM_SetIsimFileHandle: ISIM file can't write.");

        return USIMM_SW_NOFILE_FOUND;
    }

    /* ��USIM�ļ�id�����ļ� */
    stSetFileInfo.usFileID  = usFileID;
    stSetFileInfo.enAppType = USIMM_UMTS_APP;

    /* ����USIM�ӿڸ���USIM�ļ� */
    ulResult = USIMM_SetFileCommHandle(&stSetFileInfo);

    return ulResult;
}


VOS_UINT32 USIMM_SetRealFile(USIMM_MsgBlock *pMsg, USIMM_UPDATEFILE_REQ_STRU *pstNewMsg)
{
    USIMM_SETFILE_REQ_STRU              *pstMsg;
    VOS_UINT32                          ulResult;
    USIMM_SETCNF_INFO_STRU              stCnfInfo;

    /*lint -e534*/
    VOS_MemSet(&stCnfInfo, 0, sizeof(stCnfInfo));
    /*lint +e534*/

    pstMsg = (USIMM_SETFILE_REQ_STRU *)pMsg;

    stCnfInfo.ucRecordNum  = pstMsg->ucRecordNum;
    stCnfInfo.usEFLen      = pstMsg->usDataLen;
    stCnfInfo.usEfid       = pstMsg->usFileID;

    /* ִ��ISIM�����ļ� */
    if (USIMM_ISIM_APP == pstMsg->enAppType)
    {
        ulResult = USIMM_SetIsimFileHandle(pstMsg);
    }
    else if (USIMM_PB_APP == pstMsg->enAppType)
    {
        ulResult = USIMM_SetPBFileHandle(pstMsg);
    }
    else
    {
        ulResult = USIMM_SetUsimFileHandle(pstMsg);
    }

    USIMM_SetFileCnf(pstNewMsg, ulResult, &stCnfInfo);/*�ظ����½��*/

    return VOS_OK;
}


VOS_UINT32 USIMM_SetFileHandle(USIMM_MsgBlock *pMsg, USIMM_UPDATEFILE_REQ_STRU *pstNewMsg)
{
#if (FEATURE_VSIM == FEATURE_ON)
    if(VOS_TRUE == USIMM_VsimIsActive())    /*vSIM is Active*/
    {
        return USIMM_SetVsimFile((USIMM_SETFILE_REQ_STRU *)pMsg, pstNewMsg);
    }
#endif

    /*Ӳ������*/
    return USIMM_SetRealFile(pMsg, pstNewMsg);
}


VOS_UINT32 USIMM_GetFileFromCard(USIMM_GET_COMM_FILE_STRU *pstFileInfo, USIMM_GETCNF_INFO_STRU *pstCnfInfo)
{
    VOS_UINT32                          ulResult;

    ulResult = USIMM_SelectFile(pstFileInfo->enAppType, USIMM_NEED_FCP, pstFileInfo->ulPathLen, pstFileInfo->pusFilePath);

    if(VOS_OK != ulResult) /*�ļ�ѡ��ʧ��*/
    {
        USIMM_ERROR_LOG("USIMM_GetFileFromCard: Select File is Failed");

        return ulResult;
    }

    /* ��ȡҪ�����ļ�������stCnfInfo�ṹ����usEfLen, usDataLen, ucRecordNum, ucTotalNum��ֵ */
    ulResult = USIMM_GetReadFilePara(pstFileInfo->ucRecordNum, &gstUSIMMCurFileInfo.stEFInfo, pstCnfInfo);

    /* ��ȡ���ļ�����ʧ�� */
    if(VOS_OK != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_GetFileFromCard: Get file para Failed");

        return ulResult;
    }

    /*�ⲿ����Ҫ��ոò��������������ε���*/
    if (VOS_NULL_PTR == pstCnfInfo->pucEf)
    {
        pstCnfInfo->pucEf = (VOS_UINT8 *)VOS_MemAlloc(WUEPS_PID_USIM, DYNAMIC_MEM_PT, pstCnfInfo->usDataLen);
    }

    if(VOS_NULL_PTR == pstCnfInfo->pucEf)/*��鷵��ֵ*/
    {
        USIMM_ERROR_LOG("USIMM_GetFileFromCard: VOS_MemAlloc is Error");

        return USIMM_SW_ERR;
    }

    ulResult = USIMM_ReadFile(&gstUSIMMCurFileInfo.stEFInfo, pstCnfInfo->ucRecordNum, pstCnfInfo->usDataLen, pstCnfInfo->pucEf);

    return ulResult;
}
VOS_UINT32 USIMM_GetFileCommHandle(USIMM_GET_COMM_FILE_STRU *pstFileInfo, USIMM_GETCNF_INFO_STRU *pstCnfInfo)
{
    VOS_UINT32                  ulResult;
    VOS_UINT32                  ulFileNum;
    USIMM_GETCNF_INFO_STRU      stCnfInfo;

    /*lint -e534*/
    VOS_MemSet(&stCnfInfo, 0, sizeof(stCnfInfo));
    /*lint +e534*/

    if (USIMM_SW_OK == USIMM_PoolFindFile(*(pstFileInfo->pusFilePath), &ulFileNum, pstFileInfo->enAppType))
    {
        USIMM_INFO_LOG("USIMM_GetFileCommHandle: Get File Success from Usimm Pool");

        pstCnfInfo->pucEf = (VOS_UINT8 *)VOS_MemAlloc(WUEPS_PID_USIM, DYNAMIC_MEM_PT, gstUSIMMPOOL.astpoolRecord[ulFileNum].usLen);

        if(VOS_NULL_PTR == pstCnfInfo->pucEf)/*��鷵��ֵ*/
        {
            USIMM_ERROR_LOG("USIMM_GetFileCommHandle: VOS_MemAlloc is Error");

            return USIMM_SW_ERR;
        }

        /*lint -e534*/
        VOS_MemCpy(pstCnfInfo->pucEf, gstUSIMMPOOL.astpoolRecord[ulFileNum].pucContent, gstUSIMMPOOL.astpoolRecord[ulFileNum].usLen);
        /*lint +e534*/
        pstCnfInfo->usDataLen    = gstUSIMMPOOL.astpoolRecord[ulFileNum].usLen;
        pstCnfInfo->usEfLen      = gstUSIMMPOOL.astpoolRecord[ulFileNum].usLen;

        return USIMM_SW_OK;
    }

    ulResult = USIMM_GetFileFromCard(pstFileInfo, &stCnfInfo);

    /*����ļ����ش�����Ҫ����һ��*/
    if ((USIMM_SW_FILETYPE_ERROR    == ulResult)
      ||(USIMM_SW_NOFILE_FOUND      == ulResult)
      ||(USIMM_SW_NOFILE_SELECT     == ulResult))
    {
        USIMM_ClearCurEFInfo(&gstUSIMMCurFileInfo);

        ulResult = USIMM_GetFileFromCard(pstFileInfo, &stCnfInfo);
    }

    /* �����������ֵ */
    /*lint -e534*/
    VOS_MemCpy(pstCnfInfo, &stCnfInfo, sizeof(stCnfInfo));
    /*lint +e534*/

    return ulResult;
}
VOS_UINT32 USIMM_GetUsimFileHandle(USIMM_GET_COMM_FILE_STRU *pstFileInfo, USIMM_GETCNF_INFO_STRU *pstCnfInfo)
{
    return USIMM_GetFileCommHandle(pstFileInfo, pstCnfInfo);
}


VOS_UINT32 USIMM_GetIsimIMPI(USIMM_GETCNF_INFO_STRU *pstCnfInfo)
{
    VOS_UINT8                           aucAsciiImsi[USIMM_EF_IMSI_LEN*2];
    VOS_UINT32                          ulAsciiImsiLen;
    VOS_UINT8                           aucAsciiMCC[4];
    VOS_UINT8                           aucAsciiMNC[4];
    VOS_UINT32                          ulResult;
    VOS_UINT8                           aucStr[]="@ims.mnc000.mcc000.3gppnetwork.org";
    VOS_UINT32                          ulStrLen;
    VOS_UINT32                          ulFileLen;

    ulResult = USIMM_ImsiBcd2Ascii(aucAsciiImsi);

    if (USIMM_SW_OK != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_GetIsimIMPI: decode imsi fail.");

        return USIMM_SW_ERR;
    }

    USIMM_GetAsciiMCCAndMNC(aucAsciiImsi, aucAsciiMCC, aucAsciiMNC);

    /* ��Э��23.003 13.3��ʾ������imsi���� */
    /* �ļ����ݸ�ʽΪ"<IMSI>@ims.mnc<MNC>.mcc<MCC>.3gppnetwork.org" */
    ulStrLen = VOS_StrLen((VOS_CHAR *)aucStr);
    ulAsciiImsiLen = VOS_StrLen((VOS_CHAR *)aucAsciiImsi);

    /* ǰ2���ֽ�ΪTL�ֶ� */
    ulFileLen = 2 + ulStrLen + ulAsciiImsiLen;

    pstCnfInfo->pucEf = (VOS_UINT8 *)VOS_MemAlloc(WUEPS_PID_USIM, DYNAMIC_MEM_PT, ulFileLen);

    if (VOS_NULL_PTR == pstCnfInfo->pucEf)
    {
        USIMM_ERROR_LOG("USIMM_GetIsimIMPI:VOS_MemAlloc is Error");

        return USIMM_SW_ERR;
    }

    /* copy mnc */
    /*lint -e534*/
    VOS_MemCpy(aucStr+8, aucAsciiMNC, USIMM_MNC_MCC_FIG_NUM);

    /* copy mcc */
    VOS_MemCpy(aucStr+15, aucAsciiMCC, USIMM_MNC_MCC_FIG_NUM);
    /*lint +e534*/

    pstCnfInfo->pucEf[0] = USIMM_ISIM_FILE_TAG;
    pstCnfInfo->pucEf[1] = (VOS_UINT8)(ulFileLen - 2);

    /* copy imsi */
    /*lint -e534*/
    VOS_MemCpy(&(pstCnfInfo->pucEf[2]), aucAsciiImsi, ulAsciiImsiLen);

    VOS_MemCpy(&(pstCnfInfo->pucEf[2])+ulAsciiImsiLen, aucStr, ulStrLen);
    /*lint +e534*/

    pstCnfInfo->usEfLen   = (VOS_UINT16)ulFileLen;

    pstCnfInfo->usDataLen = (VOS_UINT16)ulFileLen;

    return USIMM_SW_OK;
}


VOS_UINT32 USIMM_GetIsimIMPU(USIMM_GETCNF_INFO_STRU *pstCnfInfo)
{
    VOS_UINT8                           aucAsciiImsi[USIMM_EF_IMSI_LEN*2] = {0};
    VOS_UINT32                          ulAsciiImsiLen;
    VOS_UINT8                           aucAsciiMCC[4];
    VOS_UINT8                           aucAsciiMNC[4];
    VOS_UINT32                          ulResult;
    VOS_UINT8                           aucStr1[] = "sip:";
    VOS_UINT32                          ulStr1Len;
    VOS_UINT8                           aucStr2[]="@ims.mnc000.mcc000.3gppnetwork.org";
    VOS_UINT32                          ulStr2Len;
    VOS_UINT32                          ulFileLen;

    ulResult = USIMM_ImsiBcd2Ascii(aucAsciiImsi);

    if (USIMM_SW_OK != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_GetIsimIMPI: decode imsi fail.");

        return USIMM_SW_ERR;
    }

    USIMM_GetAsciiMCCAndMNC(aucAsciiImsi, aucAsciiMCC, aucAsciiMNC);

    /* ��Э��23.003 13.4B��ʾ�������ļ����� */
    /* �ļ���ʽΪ"sip:<IMSI>@ims.mnc<MNC>.mcc<MCC>.3gppnetwork.org"*/
    ulStr1Len = VOS_StrLen((VOS_CHAR *)aucStr1);
    ulStr2Len = VOS_StrLen((VOS_CHAR *)aucStr2);
    ulAsciiImsiLen = VOS_StrLen((VOS_CHAR *)aucAsciiImsi);

    /* ǰ2���ֽ�ΪTL�ֶ� */
    ulFileLen = 2 + ulStr1Len + ulAsciiImsiLen + ulStr2Len;

    pstCnfInfo->pucEf = (VOS_UINT8 *)VOS_MemAlloc(WUEPS_PID_USIM, DYNAMIC_MEM_PT, ulFileLen);

    if (VOS_NULL_PTR == pstCnfInfo->pucEf)
    {
        USIMM_ERROR_LOG("USIMM_GetIsimIMPU:VOS_MemAlloc is Error");

        return USIMM_SW_ERR;
    }

    /* copy mnc */
    /*lint -e534*/
    VOS_MemCpy(aucStr2+8, aucAsciiMNC, USIMM_MNC_MCC_FIG_NUM);

    /* copy mcc */
    VOS_MemCpy(aucStr2+15, aucAsciiMCC, USIMM_MNC_MCC_FIG_NUM);
    /*lint +e534*/

    pstCnfInfo->pucEf[0] = USIMM_ISIM_FILE_TAG;
    pstCnfInfo->pucEf[1] = (VOS_UINT8)(ulFileLen - 2);

    /*lint -e534*/
    VOS_MemCpy(&(pstCnfInfo->pucEf[2]), aucStr1, ulStr1Len);

    VOS_MemCpy(&(pstCnfInfo->pucEf[2]) + ulStr1Len, aucAsciiImsi, ulAsciiImsiLen);

    VOS_MemCpy(&(pstCnfInfo->pucEf[2]) + ulStr1Len + ulAsciiImsiLen, aucStr2, ulStr2Len);
    /*lint +e534*/

    pstCnfInfo->usEfLen = (VOS_UINT16)ulFileLen;

    pstCnfInfo->usDataLen = (VOS_UINT16)ulFileLen;

    return USIMM_SW_OK;
}
VOS_UINT32 USIMM_GetIsimDOMAIN(USIMM_GETCNF_INFO_STRU *pstCnfInfo)
{
    VOS_UINT8                           aucAsciiImsi[USIMM_EF_IMSI_LEN*2] = {0};
    VOS_UINT8                           aucAsciiMCC[4] = {0};
    VOS_UINT8                           aucAsciiMNC[4] = {0};
    VOS_UINT32                          ulResult;
    VOS_UINT8                           aucStr[]="ims.mnc000.mcc000.3gppnetwork.org";
    VOS_UINT32                          ulFileLen;

    ulResult = USIMM_ImsiBcd2Ascii(aucAsciiImsi);

    if (USIMM_SW_OK != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_GetIsimIMPI: decode imsi fail.");

        return USIMM_SW_ERR;
    }

    USIMM_GetAsciiMCCAndMNC(aucAsciiImsi, aucAsciiMCC, aucAsciiMNC);

    /* ��Э��23.003 13.2��ʾ�������ļ����� */
    /* �ļ���ʽΪ"ims.mnc<MNC>.mcc<MCC>.3gppnetwork.org" */
    /* ǰ2���ֽ�ΪTL�ֶ� */
    ulFileLen = 2 + VOS_StrLen((VOS_CHAR *)aucStr);

    pstCnfInfo->pucEf = (VOS_UINT8 *)VOS_MemAlloc(WUEPS_PID_USIM, DYNAMIC_MEM_PT, ulFileLen);

    if (VOS_NULL_PTR == pstCnfInfo->pucEf)
    {
        USIMM_ERROR_LOG("USIMM_GetIsimDOMAIN:VOS_MemAlloc is Error");

        return USIMM_SW_ERR;
    }

    /* copy mnc */
    /*lint -e534*/
    VOS_MemCpy((aucStr+7), aucAsciiMNC, USIMM_MNC_MCC_FIG_NUM);

    /* copy mcc */
    VOS_MemCpy((aucStr+14), aucAsciiMCC, USIMM_MNC_MCC_FIG_NUM);
    /*lint +e534*/

    pstCnfInfo->pucEf[0] = USIMM_ISIM_FILE_TAG;
    pstCnfInfo->pucEf[1] = (VOS_UINT8)(ulFileLen - 2);

    /*lint -e534*/
    VOS_MemCpy(&(pstCnfInfo->pucEf[2]), (VOS_UINT8 *)aucStr, ulFileLen);
    /*lint +e534*/

    pstCnfInfo->usEfLen = (VOS_UINT16)ulFileLen;

    pstCnfInfo->usDataLen = (VOS_UINT16)ulFileLen;

    return USIMM_SW_OK;
}
VOS_UINT32 USIMM_GetIsimIST(USIMM_GETCNF_INFO_STRU *pstCnfInfo)
{
    VOS_UINT32                          i;
    VOS_UINT32                          j;
    VOS_UINT8                           ucSVRContent = 0;
    VOS_UINT16                          usFileLen;
    /*lint -e656*/
    VOS_UINT8                           aucSVRBit[ISIM_SVR_BUTT - USIM_SVR_BUTT];
    /*lint +e656*/
    VOS_UINT32                          ulArrayIndex;

    /*lint -e656*/
    usFileLen = ((ISIM_SVR_BUTT - USIM_SVR_BUTT) + USIMM_BIT_NUM_IN_BYTE - 1) / USIMM_BIT_NUM_IN_BYTE;
    /*lint +e656*/

    for(i = ISIM_SVR_PCSCF_ADDR; i < ISIM_SVR_BUTT; i++)
    {
        /* ���ýӿڻ�ȡ����λ״̬ */
        aucSVRBit[i-ISIM_SVR_PCSCF_ADDR] = (VOS_UINT8)USIMM_IsISIMServiceAvailable(i);
    }

    pstCnfInfo->pucEf = (VOS_UINT8 *)VOS_MemAlloc(WUEPS_PID_USIM, DYNAMIC_MEM_PT, usFileLen);

    if (VOS_NULL_PTR == pstCnfInfo->pucEf)
    {
        USIMM_ERROR_LOG("USIMM_GetIsimIST:VOS_MemAlloc is Error");

        return USIMM_SW_ERR;
    }

    for(i = 0; i < usFileLen; i++)
    {
        ucSVRContent = 0;

        for(j = 0; j < USIMM_BIT_NUM_IN_BYTE; j++)
        {
            ulArrayIndex = (i*USIMM_BIT_NUM_IN_BYTE + j);

            /*lint -e656 -e701*/
            if (ulArrayIndex < (ISIM_SVR_BUTT - USIM_SVR_BUTT))
            {
                ucSVRContent = (VOS_UINT8)(ucSVRContent | ((aucSVRBit[ulArrayIndex] & 0x1) << j));
            }
            /*lint +e656 +e701*/
        }

        pstCnfInfo->pucEf[i] = ucSVRContent;
    }

    pstCnfInfo->usEfLen = usFileLen;

    pstCnfInfo->usDataLen = usFileLen;

    return USIMM_SW_OK;
}
VOS_UINT32 USIMM_GetIsimFileHandle(USIMM_GET_COMM_FILE_STRU *pstFileInfo, USIMM_GETCNF_INFO_STRU *pstCnfInfo)
{
    VOS_UINT16                          usFileID = VOS_NULL_WORD;
    VOS_UINT32                          ulResult = VOS_OK;

    /* ��ǰISIM�����񲻿��� */
    if (USIMM_CARD_SERVIC_AVAILABLE != gastUSIMMCardAppInfo[USIMM_UICC_ISIM].enCardService)
    {
        USIMM_WARNING_LOG("USIMM_GetIsimFileHandle: ISIM app unavailable");

        return USIMM_SW_ERR;
    }

    if (EFISIMIMPI == *pstFileInfo->pusFilePath)
    {
        return USIMM_GetIsimIMPI(pstCnfInfo);
    }

    if (EFISIMDOMAIN == *pstFileInfo->pusFilePath)
    {
        return USIMM_GetIsimDOMAIN(pstCnfInfo);
    }

    if (EFISIMIMPU == *pstFileInfo->pusFilePath)
    {
        return USIMM_GetIsimIMPU(pstCnfInfo);
    }

    if (EFISIMIST == *pstFileInfo->pusFilePath)
    {
        return USIMM_GetIsimIST(pstCnfInfo);
    }

    /* �����ļ�����ISIM�ļ�ID���Ҷ�Ӧ��USIM�ļ�ID �Ҳ�����Ӧ��USIM�ļ�ID����Ϊ�ļ����ɶ�ȡ */
    usFileID = USIMM_IsimEFIDToUsimEFID(*pstFileInfo->pusFilePath);

    /* �Ҳ�����Ӧ��USIM�ļ�ID */
    if (VOS_NULL_WORD == usFileID)
    {
        /* �ļ����ɶ�ȡ */
        USIMM_WARNING_LOG("USIMM_GetIsimFileHandle: ISIM file can't read");

        return USIMM_SW_NOFILE_FOUND;
    }

    /* ��USIM�ļ�id��ȡ�ļ� */
    *pstFileInfo->pusFilePath  = usFileID;
    pstFileInfo->enAppType = USIMM_UMTS_APP;

    /* ����USIM�ӿڶ�ȡUSIM�ļ� */
    ulResult = USIMM_GetFileCommHandle(pstFileInfo, pstCnfInfo);

    return ulResult;

}


VOS_UINT32 USIMM_GetRealFile(USIMM_GETFILE_REQ_STRU* pstOldMsg, USIMM_READFILE_REQ_STRU *pstNewMsg)
{
    VOS_UINT32                          ulResult;
    USIMM_GETCNF_INFO_STRU              stCnfInfo;
    USIMM_GET_COMM_FILE_STRU            stGetFileInfo;

    /*lint -e534*/
    VOS_MemSet(&stCnfInfo, 0, sizeof(stCnfInfo));
    VOS_MemSet(&stGetFileInfo, 0, sizeof(stGetFileInfo));
    /*lint +e534*/

    stGetFileInfo.enAppType     = pstOldMsg->enAppType;
    stGetFileInfo.ucRecordNum   = pstOldMsg->ucRecordNum;
    stGetFileInfo.pusFilePath   = &pstOldMsg->usFileID;
    stGetFileInfo.ulPathLen     = 1;

    if (USIMM_ISIM_APP == pstOldMsg->enAppType)
    {
        ulResult = USIMM_GetIsimFileHandle(&stGetFileInfo, &stCnfInfo);
    }
    else
    {
        ulResult = USIMM_GetUsimFileHandle(&stGetFileInfo, &stCnfInfo);
    }

    stCnfInfo.ucRecordNum      = pstOldMsg->ucRecordNum;
    stCnfInfo.usEfId           = pstOldMsg->usFileID;

    USIMM_GetFileCnf(pstNewMsg, ulResult, &stCnfInfo);

    if(VOS_NULL_PTR != stCnfInfo.pucEf)
    {
        /*lint -e534*/
        VOS_MemFree(WUEPS_PID_USIM, stCnfInfo.pucEf);
        /*lint +e534*/
    }

    return VOS_OK;
}


VOS_UINT32 USIMM_GetFileHandle(USIMM_GETFILE_REQ_STRU* pstOldMsg, USIMM_READFILE_REQ_STRU *pstNewMsg)
{
#if (FEATURE_VSIM == FEATURE_ON)
    if(VOS_TRUE == USIMM_VsimIsActive())    /*vSIM is Active*/
    {
        return USIMM_GetVsimFile(pstOldMsg, pstNewMsg);
    }
#endif

    /*Ӳ������*/
    return USIMM_GetRealFile(pstOldMsg, pstNewMsg);
}

#if (FEATURE_UE_MODE_CDMA == FEATURE_ON)
/*****************************************************************************
�� �� ��  :USIMM_GetCdmaFileMaxRecordNum
��������  :ʵ����CDMA����ȡ�ļ�����¼����ѡ�ļ�����
�������  :usFildId:�ļ�ID
�������  :��
�� �� ֵ  :VOS_ERR
           VOS_OK
�޶���¼  :
1. ��    ��   : 2014��10��17��
   ��    ��   : h00300778
   �޸�����   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_GetCdmaFileMaxRecordNum(VOS_UINT16 usFildId)
{
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulPathLen;
    VOS_UINT16                          ausFileAllPath[USIMM_MAX_PATH_LEN] = {MF, 0x0};

    /* ƴ�ļ�·�� */
    if (USIMM_CARD_CSIM == gastUSIMMCardAppInfo[USIMM_UICC_CDMA].enCardType)
    {
        ausFileAllPath[1]      = ADF;
    }
    else
    {
        ausFileAllPath[1]      = DFCDMA;
    }

    ulPathLen         = 3;
    ausFileAllPath[2] = usFildId;

    ulResult = USIMM_SelectCdmaFile(USIMM_NEED_FCP, ulPathLen, ausFileAllPath);

    /* �ļ�ѡ��ʧ�� */
    if (VOS_OK != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_GetCdmaFileMaxRecordNum: Select File is Failed");

        return ulResult;
    }

    return VOS_OK;
}
#endif


VOS_UINT32 USIMM_GetMaxRecordNum(USIMM_MsgBlock *pMsg, USIMM_QUERYFILE_REQ_STRU *pstNewMsg)
{
    VOS_UINT32                  ulResult;
    USIMM_MAXRECORD_REQ_STRU    *pstOldMsg;
    USIMM_FILECNF_INFO_STRU     stCnfInfo;

    /*lint -e534*/
    VOS_MemSet(&stCnfInfo, 0, sizeof(stCnfInfo));
    /*lint +e534*/

    pstOldMsg = (USIMM_MAXRECORD_REQ_STRU*)pMsg;

    stCnfInfo.usEFId = pstOldMsg->usEfId;

#if (FEATURE_UE_MODE_CDMA == FEATURE_ON)
    if (USIMM_3GPP2_APP == pstOldMsg->enAppType)
    {
        ulResult = USIMM_GetCdmaFileMaxRecordNum(pstOldMsg->usEfId);
    }
    else
#endif
    {
        ulResult = USIMM_SelectFile(pstOldMsg->enAppType, USIMM_NEED_FCP, 1, &pstOldMsg->usEfId);
    }

    if(VOS_OK != ulResult)/*�ж��ļ���ѡ����*/
    {
        USIMM_ERROR_LOG("USIMM_GetMaxRecordNum: The File Not Exist");

        USIMM_MaxRecordNumCnf(pstNewMsg, ulResult, &stCnfInfo);

        return VOS_ERR;
    }

    if(USIMM_EFSTRUCTURE_TRANSPARENT == gstUSIMMCurFileInfo.stEFInfo.enFileType)/*�ж��ļ�������*/
    {
        USIMM_ERROR_LOG("USIMM_GetMaxRecordNum: The File Type is Wrong");

        ulResult = USIMM_SW_FILETYPE_ERROR;
    }
    else                    /*���ڼ�¼�ļ���ѭ���ļ�����Ϊ�ɹ�*/
    {
        USIMM_INFO_LOG("USIMM_GetMaxRecordNum: The File Select is OK");

        ulResult                = USIMM_SW_OK;

        stCnfInfo.ucRecordLen   = gstUSIMMCurFileInfo.stEFInfo.ucRecordLen;

        stCnfInfo.ucRecordNum   = gstUSIMMCurFileInfo.stEFInfo.ucRecordNum;
    }

    stCnfInfo.ulFileStatus          = gstUSIMMCurFileInfo.stEFInfo.enFileStatus;

    stCnfInfo.ulFileReadUpdateFlag  = gstUSIMMCurFileInfo.stEFInfo.enFileReadUpdateFlag;

    USIMM_MaxRecordNumCnf(pstNewMsg, ulResult, &stCnfInfo);

    return ulResult;
}
VOS_UINT32 USIMM_GAccessHandle(USIMM_MsgBlock *pMsg)
{
    VOS_UINT32                          ulResult;
    USIMM_GACCESS_REQ_STRU              *pstMsg;
    USIMM_SENDTPDU_CNFINFO_STRU         stDataCnf;
    VOS_UINT32                          ulPathLen;
    VOS_UINT16                          ausPath[USIMM_MAX_PATH_LEN];
    VOS_UINT8                           aucPath[USIMM_MAX_PATH_LEN*2];
    USIMM_SELECT_PARA_STUR              stSelectPara;
    USIMM_U16_LVDATA_STRU               stFilePath;
    USIMM_FILEPATH_INFO_STRU            stFilePathCnf;
    VOS_UINT32                          i;
    VOS_UINT32                          ulSWResult;
    VOS_UINT16                          usTmpPathLen = 0;

    pstMsg = (USIMM_GACCESS_REQ_STRU*)pMsg;

    /*lint -e534*/
    VOS_MemSet(&stDataCnf, 0, sizeof(stDataCnf));
    /*lint +e534*/

    stDataCnf.pucTPDUHead= pstMsg->aucContent;

    /* TMO����Ҫ+CSIM���� */
    if (VOS_TRUE == g_stUsimmFeatureCfg.unCfg.stFeatureCfg.ulTmo_flg)
    {
        USIMM_SendTPDUCnf(pstMsg->ulSenderPid,
                          pstMsg->ulSendPara,
                          VOS_ERR,
                          USIMM_SW_ERR,
                          &stDataCnf,
                          VOS_NULL_PTR);

        return VOS_ERR;
    }

    if(CMD_INS_SELECT == pstMsg->aucContent[INS])   /* ���ڳ���·����Ӧ��ѡ�з�ʽ��֧�� */
    {
        if( (pstMsg->aucContent[P1] == USIMM_SELECT_BY_DF_NAME)||(pstMsg->aucContent[P3] > USIMM_MAX_PATH_LEN*2) )
        {
            USIMM_ERROR_LOG("USIMM_GAccessHandle: The USIMM_SelectFile Return Error");

            USIMM_SendTPDUCnf(pstMsg->ulSenderPid,
                              pstMsg->ulSendPara,
                              VOS_ERR,
                              USIMM_SW_ERR,
                              &stDataCnf,
                              VOS_NULL_PTR);

            return VOS_ERR;
        }
    }

    if (pstMsg->ulPathLen != 0) /*��Ҫ����ѡ��֮ǰ��·��*/
    {
        ulResult = USIMM_SelectFile(USIMM_UNLIMIT_APP, USIMM_NEED_FCP, pstMsg->ulPathLen, pstMsg->ausPath);

        if(ulResult != VOS_OK)
        {
            USIMM_ERROR_LOG("USIMM_GAccessHandle: The USIMM_SelectFile Return Error");
        }
    }

    /*lint -e534*/
    VOS_MemSet(&gstUSIMMAPDU, 0, sizeof(gstUSIMMAPDU));
    /*lint +e534*/

    if (VOS_OK != USIMM_FormatCsimApdu(pstMsg, &gstUSIMMAPDU))  /*��ϳɱ�׼��ʽ*/
    {
        USIMM_SendTPDUCnf(pstMsg->ulSenderPid,
                          pstMsg->ulSendPara,
                          VOS_ERR,
                          USIMM_SW_ERR,
                          &stDataCnf,
                          VOS_NULL_PTR);

        USIMM_ERROR_LOG("USIMM_GAccessHandle: The USIMM_FormatCsimApdu Return Error");

        /*lint -e534*/
        VOS_MemSet(&gstUSIMMAPDU, 0, sizeof(gstUSIMMAPDU));
        /*lint +e534*/

        return VOS_ERR;
    }

    ulResult = USIMM_DLHandle(&gstUSIMMAPDU); /* ������·�㺯�� */

    if((CMD_INS_SELECT == pstMsg->aucContent[INS])&&(VOS_OK == ulResult)&&(gstUSIMMAPDU.ucSW1 == 0x90))   /*�����µ�ѡ�����ʱ����Ҫ���¸��µ�ǰ��ַ*/
    {
        stSelectPara.enCardType = gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardType;

        stSelectPara.enFileApp  = USIMM_UNLIMIT_APP;

        /* ����T=1Э������ٸ���response��INS�ж��Ƕ���ҪFCP�ˣ�ֻ�ܿ��Ƿ�����Ӧ���� */
        if(VOS_NULL != gstUSIMMAPDU.ulRecDataLen)
        {
            stSelectPara.enEfFcpFlag = USIMM_NEED_FCP;
        }
        else
        {
            stSelectPara.enEfFcpFlag = USIMM_NO_NEED_FCP;
        }

        USIMM_ChangePathToU16(pstMsg->aucContent[P3], &pstMsg->aucContent[P3+1], &ulPathLen, ausPath);

        stFilePath.pusData      = ausPath;

        stFilePath.ulDataLen    = ulPathLen;

        if(VOS_NULL != gstUSIMMAPDU.ulRecDataLen)
        {
            /*lint -e534*/
            USIMM_DecodeFileFcp(gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardType, &stFilePath, &gstUSIMMAPDU, &gstUSIMMCurFileInfo);
            /*lint +e534*/
        }

        USIMM_UpdateFileByRelativePath(&stSelectPara, &stFilePath, &gstUSIMMCurFileInfo);
    }

    stDataCnf.usDataLen = (VOS_UINT16)gstUSIMMAPDU.ulRecDataLen;
    stDataCnf.pucData   = gstUSIMMAPDU.aucRecvBuf;
    stDataCnf.ucSw1     = gstUSIMMAPDU.ucSW1;
    stDataCnf.ucSw2     = gstUSIMMAPDU.ucSW2;

    ulSWResult = USIMM_CheckSW(&gstUSIMMAPDU);

    for (i = 0; i < gstUSIMMCurFileInfo.usFilePathLen; i++)
    {
        aucPath[i*2] = (VOS_UINT8)((gstUSIMMCurFileInfo.ausFilePath[i]>>0x08)&0x00FF);

        aucPath[(i*2)+1] = (VOS_UINT8)(gstUSIMMCurFileInfo.ausFilePath[i]&0x00FF);
    }

    ulPathLen = (VOS_UINT8)(gstUSIMMCurFileInfo.usFilePathLen * sizeof(VOS_UINT16));

    USIMM_ChangePathToAsciiString(aucPath,
                                  (VOS_UINT8)ulPathLen,
                                  stFilePathCnf.acPath,
                                  &usTmpPathLen);

    stFilePathCnf.ulPathLen = usTmpPathLen;

    USIMM_SendTPDUCnf(pstMsg->ulSenderPid,
                      pstMsg->ulSendPara,
                      ulResult,
                      ulSWResult,
                      &stDataCnf,
                      &stFilePathCnf);

    return ulResult;
}


VOS_UINT32 USIMM_RAccessPathHandle(
    VOS_UINT16                          usFileID,
    VOS_UINT16                          usPathLen,
    VOS_UINT16                         *pusPath,
    USIMM_RESTRIC_CMD_ENUM_UINT32       ulCmdType)
{
    VOS_UINT16                          ausFilePath[USIMM_MAX_PATH_LEN];
    VOS_UINT32                          ulResult;

    if((usPathLen+1) > USIMM_MAX_PATH_LEN)
    {
        USIMM_ERROR_LOG("USIMM_RAccessPathHandle: The File Path Len is error");

        return USIMM_SW_ERR;
    }

    /* GET RESPONSE��������ļ���Ϣ��ȷ���ļ���������ѡ�� */
    if (USIMM_GET_RESPONSE == ulCmdType)
    {
        USIMM_ClearCurFileInfo();
    }
#if (FEATURE_OFF == FEATURE_UE_MODE_CDMA)
    /* AT����������а��ļ�·����������ƴ���ļ�·����ѡ���ļ���
       ���û���ļ�·����ֱ�Ӱ��ļ�IDѡ�ļ�*/
    if (0 == usPathLen)
    {
        /* ���ѡ���У��ٰ��绰����Ӧ�ó���ѡ���ļ� */
        ulResult = USIMM_SelectFile(USIMM_UNLIMIT_APP, USIMM_NEED_FCP, 1, &usFileID);

        if ((USIMM_SW_OK != ulResult)&&(USIMM_SW_SENDCMD_ERROR != ulResult))
        {
            ulResult = USIMM_SelectFile(USIMM_PB_APP, USIMM_NEED_FCP, 1, &usFileID);
        }
    }
    else
    {
        /* �����ļ�·�� */
        /*lint -e534*/
        VOS_MemCpy(ausFilePath, pusPath, usPathLen*sizeof(VOS_UINT16));

        /* �����ļ�ID */
        VOS_MemCpy((ausFilePath + usPathLen), &usFileID, sizeof(usFileID));
        /*lint +e534*/

        /* ��·��ѡ���ļ���·��������Ҫ��1�����ļ�ID���� */
        ulResult = USIMM_SelectFile(USIMM_UNLIMIT_APP, USIMM_NEED_FCP, (usPathLen+1), ausFilePath);
    }
#else
    if (0 == usPathLen)
    {
        ulResult = USIMM_SelectCdmaFile(USIMM_NEED_FCP, 1, &usFileID);
    }
    else
    {
        /* �����ļ�·�� */
        /*lint -e534*/
        VOS_MemCpy(ausFilePath, pusPath, usPathLen*sizeof(VOS_UINT16));

        /* �����ļ�ID */
        VOS_MemCpy((ausFilePath + usPathLen), &usFileID, sizeof(usFileID));
        /*lint +e534*/

        /* ��·��ѡ���ļ���·��������Ҫ��1�����ļ�ID���� */
        ulResult = USIMM_SelectCdmaFile(USIMM_NEED_FCP, (usPathLen+1), ausFilePath);
    }
#endif
    return ulResult;
}
VOS_UINT32 USIMM_RAccessHandle(USIMM_CMDHEADER_REQ_STRU *pMsg)
{
    VOS_UINT32                          ulResult   = VOS_OK;
    VOS_UINT16                          usOffset;
    VOS_UINT32                          ulNeedCopy          = VOS_NO;
    USIMM_RACCESS_REQ_STRU             *pstMsg;
    VOS_UINT8                           ucLen               = 0;
    VOS_UINT8                          *pucContent          = VOS_NULL_PTR;
    NAS_NVIM_SYSTEM_APP_CONFIG_STRU     stSystemAppConfig;
    USIMM_RACCESSCNF_INFO_STRU          stCnfInfo           = {0};
    VOS_UINT32                          i = 0;

    pstMsg = (USIMM_RACCESS_REQ_STRU *)pMsg;

    if (VOS_OK != USIMM_ApiParaCheck())
    {
        USIMM_RestrictedAccessCnf(pstMsg, VOS_ERR, &stCnfInfo);

        return VOS_ERR;
    }

    /* �������⿨�����ſ���envelop�������ִ��status�ͻ����֮ǰѡ�е��ļ�δѡ��,
    ״̬�ַ���USIMM_SW_NOFILE_SELECT����ʱ���֮ǰѡ�е��ļ�·��������ѡ���ļ��������ļ���
    ����������������Ҫѭ����ִ��һ�ξ��˳� */
    while(i < 2)
    {

        /*�����ǰ�����ݷ��أ���ô��Ҫ��ձ������ݵ�ȫ�ֱ���*/
        /*lint -e534*/
        VOS_MemSet(&gstUSIMMAPDU, 0, sizeof(gstUSIMMAPDU));
        /*lint +e534*/

        if(VOS_NULL_WORD != pstMsg->usEfId)
        {
            ulResult = USIMM_RAccessPathHandle(pstMsg->usEfId,
                                               pstMsg->usPathLen,
                                               pstMsg->ausPath,
                                               pstMsg->enCmdType);
        }

        if(USIMM_SW_OK != ulResult)/*�ж�ѡ����*/
        {
            stCnfInfo.ulErrorCode = ulResult;

            stCnfInfo.ucSW1 = gstUSIMMAPDU.ucSW1;

            stCnfInfo.ucSW2 = gstUSIMMAPDU.ucSW2;

            USIMM_RestrictedAccessCnf(pstMsg,
                                      VOS_OK,
                                      &stCnfInfo);

            return VOS_OK;
        }

        switch (pstMsg->enCmdType)
        {
            case USIMM_READ_BINARY:
                usOffset   = ((VOS_UINT16)(pstMsg->ucP1<< 8) & 0xFF00) + pstMsg->ucP2;
                ulNeedCopy = VOS_YES;                                                                 /*��������Ҫ����*/
                ulResult   = USIMM_ReadBinary_APDU(usOffset, pstMsg->ucP3);
                break;

            case USIMM_READ_RECORD:
                ulNeedCopy = VOS_YES;                                                                 /*��������Ҫ����*/
                ulResult   = USIMM_ReadRecord_APDU(pstMsg->ucP1, pstMsg->ucP2, pstMsg->ucP3);
                break;

            case USIMM_UPDATE_BINARY:
                usOffset = ((VOS_UINT16)(pstMsg->ucP1 << 8) & 0xFF00) + pstMsg->ucP2;
                ulResult = USIMM_UpdateBinary_APDU(usOffset, pstMsg->ucP3, pstMsg->aucContent);
                break;

            case USIMM_UPDATE_RECORD:
                ulResult = USIMM_UpdateRecord_APDU(pstMsg->ucP1,pstMsg->ucP2,pstMsg->ucP3,pstMsg->aucContent);
                break;

            case USIMM_STATUS:
                ulNeedCopy = VOS_YES;                                                          /*��������Ҫ����*/
                ulResult   = USIMM_Status_APDU(pstMsg->ucP1, pstMsg->ucP2, pstMsg->ucP3);
                break;
            case USIMM_AUTHENTICATION:
                ulNeedCopy = VOS_YES;
                ulResult   = USIMM_Authentication_APDU(0x0, pstMsg->ucP2, pstMsg->aucContent, pstMsg->ucP3);
                break;

            case USIMM_GET_RESPONSE:
                ulNeedCopy = VOS_YES;
                break;

            default:
                ulResult =  USIMM_SW_SENDCMD_ERROR;
                break;
        }

        if (VOS_OK != ulResult)/*��鷢�ͽ��*/
        {
            USIMM_ERROR_LOG("USIMM_RAccessHandle: Send Command APDU is Failed");

            stCnfInfo.ulErrorCode = USIMM_SW_SENDCMD_ERROR;

            USIMM_RestrictedAccessCnf(pstMsg, VOS_ERR, &stCnfInfo);

            return VOS_ERR;
        }

        ulResult = USIMM_CheckSW(&gstUSIMMAPDU);

        if (USIMM_SW_NOFILE_SELECT == ulResult)
        {
            i++;
            USIMM_ClearCurFileInfo();
        }
        else
        {
            break;
        }
    }

    if (USIMM_SW_OK != ulResult)/*�����*/
    {
        USIMM_WARNING_LOG("USIMM_RAccessHandle: The Command Result is Failed");

        ucLen = 0;

        ulNeedCopy = VOS_NO;
    }

    /* ���MP��ANDROID��GET RESPONSE�����P3�����Ĳ��� */
    if (VOS_OK != NV_Read(en_NV_Item_System_APP_Config, &stSystemAppConfig, sizeof(NAS_NVIM_SYSTEM_APP_CONFIG_STRU)))
    {
        stSystemAppConfig.usSysAppConfigType =   SYSTEM_APP_MP;
    }

    if (VOS_YES == ulNeedCopy) /*�����ݿ���*/
    {
        ucLen       = (VOS_UINT8)gstUSIMMAPDU.ulRecDataLen;

        pucContent  = &gstUSIMMAPDU.aucRecvBuf[0];

        /* �ڷ�ANDROID�ϣ�����P3����ָ���ĳ��ȡ���ANDROID�Ϸ���ʵ�ʳ��� */
        if ((USIMM_GET_RESPONSE == pstMsg->enCmdType)
            && (SYSTEM_APP_ANDROID != stSystemAppConfig.usSysAppConfigType))
        {
            ucLen = (ucLen > pstMsg->ucP3)?pstMsg->ucP3:ucLen;
        }
    }

    stCnfInfo.ulErrorCode = ulResult;

    stCnfInfo.ucSW1 = gstUSIMMAPDU.ucSW1;

    stCnfInfo.ucSW2 = gstUSIMMAPDU.ucSW2;

    stCnfInfo.ucLen = ucLen;

    stCnfInfo.pContent = pucContent;

    USIMM_RestrictedAccessCnf(pstMsg, VOS_OK, &stCnfInfo);

    return VOS_OK;
}


VOS_UINT32  USIMM_SearchHandle(USIMM_SEARCH_REQ_STRU *pstOldMsg, USIMM_SEARCHFILE_REQ_STRU *pstNewMsg)
{
    VOS_UINT32                  ulResult;
    USIMM_SEARCHCNF_INFO_STRU   stCnfInfo;

    /*lint -e534*/
    VOS_MemSet(&stCnfInfo, 0, sizeof(stCnfInfo));
    /*lint +e534*/

    stCnfInfo.usEfid = pstOldMsg->usEfId;

    ulResult = USIMM_SelectFile(pstOldMsg->enAppType, USIMM_NEED_FCP, 1, &pstOldMsg->usEfId); /*���ö�Ӧ��API*/

    if (VOS_OK != ulResult)
    {
#if (VOS_WIN32 == VOS_OS_VER)
        USIMM_SearchHandleCnf(pstNewMsg, USIMM_SW_NOFILE_FOUND, &stCnfInfo);
#else
        USIMM_SearchHandleCnf(pstNewMsg, ulResult, &stCnfInfo);
#endif
        return VOS_OK;
    }

    if (USIMM_CARD_USIM == gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardType)
    {
        ulResult = USIMM_Search_APDU(0x01, 0x04, pstOldMsg->ucLen, pstOldMsg->aucContent);
    }
    else
    {
        ulResult = USIMM_Search_APDU(0x00, 0x10, pstOldMsg->ucLen, pstOldMsg->aucContent);
    }

    if (VOS_OK != ulResult)
    {
        USIMM_SearchHandleCnf(pstNewMsg, ulResult, &stCnfInfo);

        return VOS_OK;
    }

    ulResult = USIMM_CheckSW(&gstUSIMMAPDU);/*���ѡ����*/

    stCnfInfo.pucData = gstUSIMMAPDU.aucRecvBuf;

    stCnfInfo.ulLen   = gstUSIMMAPDU.ulRecDataLen;

    stCnfInfo.usTotalRecNum = gstUSIMMCurFileInfo.stEFInfo.ucRecordNum;;

    USIMM_SearchHandleCnf(pstNewMsg, ulResult, &stCnfInfo);

    return VOS_OK;
}


VOS_UINT32 USIMM_PBInitStatusIndHandle(USIMM_CMDHEADER_REQ_STRU *pMsg)
{
    USIMM_PBINIT_STATUS_IND_STRU       *pstMsg;

    if (VOS_TRUE == USIMM_VsimIsActive())    /*vSIM���ܴ�*/
    {
        USIMM_WARNING_LOG("USIMM_PBInitStatusInd: The vSIM is Open");

        return VOS_OK;
    }

    pstMsg = (USIMM_PBINIT_STATUS_IND_STRU *)pMsg;

    gstUSIMMBaseInfo.stPBInfo.enPBInitStatus = pstMsg->enPBInitStatus;

    /*�绰����ʼ����ɣ����Ա�������*/
    if(USIMM_PB_IDLE == pstMsg->enPBInitStatus)
    {
        USIMM_SaveLogFile();
    }

    return VOS_OK;
}


VOS_UINT32 USIMM_SIMAuthHandle(USIMM_AUTH_REQ_STRU *pstMsg)
{
    USIMM_TELECOM_AUTH_INFO_STRU        stCnfInfo;
    VOS_UINT32                          ulResult;
    VOS_UINT16                          ausSimPath[]={MF, DFGSM};
    VOS_UINT8                           aucGsmRes[USIMM_2G_AUTH_SRES_LEN + 1];
    VOS_UINT8                           aucGsmKc[USIMM_2G_AUTH_KC_LEN + 1];

    /*lint -e534*/
    VOS_MemSet(&stCnfInfo, 0, sizeof(stCnfInfo));
    /*lint +e534*/

    if (USIMM_CARD_SIM != gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardType)
    {
        USIMM_ERROR_LOG("USIMM_SIMAuthHandle: SIM is disable.");

        stCnfInfo.enResult = USIMM_AUTH_GSM_OTHER_FAILURE;

        USIMM_TelecomAuthCnf(pstMsg, &stCnfInfo);

        return VOS_ERR;
    }

    /* ����Ȩ�����Ƿ���ȷ */
    if (USIMM_2G_AUTH != pstMsg->enAuthType)
    {
        USIMM_ERROR_LOG("USIMM_SIMAuthHandle: enAuthType is incorrcet.");

        stCnfInfo.enResult = USIMM_AUTH_GSM_OTHER_FAILURE;

        USIMM_TelecomAuthCnf(pstMsg, &stCnfInfo);

        return VOS_ERR;
    }

    ulResult = USIMM_SelectFile(USIMM_GSM_APP, USIMM_NEED_FCP, ARRAYSIZE(ausSimPath), ausSimPath);

    if(VOS_OK != ulResult) /*�жϽ��*/
    {
        USIMM_ERROR_LOG("USIMM_SIMAuthHandle: Select DFGSM Error");

        stCnfInfo.enResult = USIMM_AUTH_GSM_OTHER_FAILURE;

        USIMM_TelecomAuthCnf(pstMsg, &stCnfInfo);

        return VOS_ERR;
    }

    /* SIM���·���Ȩ���ݲ���Ҫ�����ֶ� */
    ulResult = USIMM_Authentication_APDU(0x0, USIMM_SIM_2G_AUTH_MODE, pstMsg->aucData + 1, pstMsg->ulDataLen - 1);

    if (VOS_OK != ulResult) /*�жϼ�Ȩ���ͽ��*/
    {
        USIMM_ERROR_LOG("USIMM_SIMAuthHandle: Send SIM Authentication APDU Error");

        stCnfInfo.enResult = USIMM_AUTH_GSM_OTHER_FAILURE;

        USIMM_TelecomAuthCnf(pstMsg, &stCnfInfo);

        return VOS_ERR;
    }

    ulResult = USIMM_CheckSW(&gstUSIMMAPDU);

    if (USIMM_SW_AUTN_ERROR == ulResult)
    {
        USIMM_WARNING_LOG("USIMM_SIMAuthHandle: SIM Check SW Error");

        stCnfInfo.enResult = USIMM_AUTH_MAC_FAILURE;

        USIMM_TelecomAuthCnf(pstMsg, &stCnfInfo);

        return VOS_ERR;
    }

    if (VOS_OK != ulResult)
    {
        stCnfInfo.enResult = USIMM_AUTH_GSM_OTHER_FAILURE;

        USIMM_TelecomAuthCnf(pstMsg, &stCnfInfo);

        return VOS_ERR;
    }

    /* SIM����Ȩ��������û�г����ֶΣ���Ҫ��� */
    aucGsmRes[0] = USIMM_2G_AUTH_SRES_LEN;
    /*lint -e534*/
    VOS_MemCpy(&aucGsmRes[1], &gstUSIMMAPDU.aucRecvBuf[0], USIMM_2G_AUTH_SRES_LEN);
    /*lint +e534*/

    aucGsmKc[0]  = USIMM_2G_AUTH_KC_LEN;
    /*lint -e534*/
    VOS_MemCpy(&aucGsmKc[1], &gstUSIMMAPDU.aucRecvBuf[USIMM_2G_AUTH_SRES_LEN], USIMM_2G_AUTH_KC_LEN);
    /*lint +e534*/

    stCnfInfo.pucGsmKC   = aucGsmKc;
    stCnfInfo.pucAuthRes = aucGsmRes;

    USIMM_INFO_LOG("USIMM_SIMAuthHandle: SIM Authentication Right");

    stCnfInfo.enResult = USIMM_AUTH_GSM_SUCCESS;

    USIMM_TelecomAuthCnf(pstMsg, &stCnfInfo);

    return VOS_OK;

}
VOS_UINT32 USIMM_USIMAuthHandle(USIMM_AUTH_REQ_STRU *pstMsg)
{
    USIMM_TELECOM_AUTH_INFO_STRU        stCnfInfo;
    VOS_UINT32                          ulResult;
    VOS_UINT16                          ausUsimPath[]={MF, ADF};
    VOS_UINT8                           ucMode;
    VOS_UINT32                          ulOffset = 1;

    /*lint -e534*/
    VOS_MemSet(&stCnfInfo, 0, sizeof(stCnfInfo));
    /*lint +e534*/

    if (USIMM_CARD_USIM != gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardType)
    {
        USIMM_ERROR_LOG("USIMM_USIMAuthHandle: SIM is disable.");

        stCnfInfo.enResult = USIMM_AUTH_UMTS_OTHER_FAILURE;

        USIMM_TelecomAuthCnf(pstMsg, &stCnfInfo);

        return VOS_ERR;
    }

    /* ������Ⲣȷ����Ȩ���ݲ��� */
    if (USIMM_2G_AUTH == pstMsg->enAuthType)
    {
        ucMode = USIMM_USIM_2G_AUTH_MODE;
    }
    else if (USIMM_3G_AUTH == pstMsg->enAuthType)
    {
        ucMode = USIMM_USIM_3G_AUTH_MODE;
    }
    else
    {
        USIMM_ERROR_LOG("USIMM_USIMAuthHandle: enAuthType is incorrect.");

        stCnfInfo.enResult = USIMM_AUTH_UMTS_OTHER_FAILURE;

        USIMM_TelecomAuthCnf(pstMsg, &stCnfInfo);

        return VOS_ERR;
    }

    ulResult = USIMM_SelectFile(USIMM_UMTS_APP, USIMM_NEED_FCP, ARRAYSIZE(ausUsimPath), ausUsimPath);

    if(VOS_OK != ulResult)/*�жϽ��*/
    {
        USIMM_ERROR_LOG("USIMM_USIMAuthHandle: Select ADF Error");

        stCnfInfo.enResult = USIMM_AUTH_UMTS_OTHER_FAILURE;

        USIMM_TelecomAuthCnf(pstMsg, &stCnfInfo);

        return VOS_ERR;
    }

    ulResult = USIMM_Authentication_APDU(0x0, ucMode, pstMsg->aucData, pstMsg->ulDataLen);

    if(VOS_OK != ulResult)/*�жϼ�Ȩ���ͽ��*/
    {
        USIMM_ERROR_LOG("USIMM_USIMAuthHandle: Send USIM Authentication APDU Error");

        stCnfInfo.enResult = USIMM_AUTH_UMTS_OTHER_FAILURE;

        USIMM_TelecomAuthCnf(pstMsg, &stCnfInfo);

        return VOS_ERR;
    }

    ulResult = USIMM_CheckSW(&gstUSIMMAPDU);

    if(USIMM_SW_AUTN_ERROR == ulResult)
    {
        USIMM_WARNING_LOG("USIMM_USIMAuthHandle: SIM Check SW Error");

        stCnfInfo.enResult = USIMM_AUTH_MAC_FAILURE;

        USIMM_TelecomAuthCnf(pstMsg, &stCnfInfo);

        return VOS_ERR;
    }

    if (VOS_OK != ulResult)
    {
        stCnfInfo.enResult = USIMM_AUTH_UMTS_OTHER_FAILURE;

        USIMM_TelecomAuthCnf(pstMsg, &stCnfInfo);

        return VOS_ERR;
    }

    /* ��ǰUSIM����GSM��Ȩ */
    if (USIMM_2G_AUTH == pstMsg->enAuthType)
    {
        stCnfInfo.pucAuthRes = &gstUSIMMAPDU.aucRecvBuf[0];

        stCnfInfo.pucGsmKC   = &gstUSIMMAPDU.aucRecvBuf[USIMM_2G_AUTH_SRES_LEN + 1];

        USIMM_INFO_LOG("USIMM_USIMAuthHandle: USIM GSM Authentication right");

        stCnfInfo.enResult = USIMM_AUTH_GSM_SUCCESS;

        USIMM_TelecomAuthCnf(pstMsg, &stCnfInfo);

        return VOS_OK;
    }

    /* 3G ��Ȩ�ɹ� */
    if (USIMM_AUTH_SUCCESS_TAG == gstUSIMMAPDU.aucRecvBuf[0])
    {
        stCnfInfo.enResult  = USIMM_AUTH_UMTS_SUCCESS;

        stCnfInfo.pucAuthRes= &gstUSIMMAPDU.aucRecvBuf[ulOffset];/*ָ��Res*/

        ulOffset            += gstUSIMMAPDU.aucRecvBuf[ulOffset] + 1;/*ָ��CK*/

        stCnfInfo.pucCK     = &gstUSIMMAPDU.aucRecvBuf[ulOffset];

        ulOffset            += gstUSIMMAPDU.aucRecvBuf[ulOffset] + 1;/*ָ��IK*/

        stCnfInfo.pucIK     = &gstUSIMMAPDU.aucRecvBuf[ulOffset];

        ulOffset            += gstUSIMMAPDU.aucRecvBuf[ulOffset] + 1;/*ָ�������ܵ�Kc*/

        if(ulOffset < gstUSIMMAPDU.ucSW2)
        {
            stCnfInfo.pucGsmKC = &gstUSIMMAPDU.aucRecvBuf[ulOffset];

            USIMM_INFO_LOG("USIMM_USIMAuthHandle: USIM 3G Authentication have the KC Data");
        }

        USIMM_INFO_LOG("USIMM_USIMAuthHandle: USIM 3G Authenctication Right");
    }
    else if (USIMM_AUTH_SYNC_FAIL_TAG == gstUSIMMAPDU.aucRecvBuf[0]) /* 3G��ͬ�� */
    {
        stCnfInfo.enResult  = USIMM_AUTH_SYNC_FAILURE;

        stCnfInfo.pucAuts   = &gstUSIMMAPDU.aucRecvBuf[1];

        USIMM_WARNING_LOG("USIMM_USIMAuthHandle: USIM 3G Authentication Need ReSynchronization");
    }
    else                                                                /*�������ݴ���*/
    {
        USIMM_ERROR_LOG("USIMM_USIMAuthHandle: USIM Authentication Response Data Error");

        stCnfInfo.enResult = USIMM_AUTH_UMTS_OTHER_FAILURE;
    }

    USIMM_TelecomAuthCnf(pstMsg, &stCnfInfo);

    return VOS_OK;
}
VOS_UINT32 USIMM_ISIMAuthParaCheck(USIMM_AUTH_REQ_STRU *pstMsg, VOS_UINT8 *pucMode)
{
    VOS_UINT32                          ulIMSSVR;

    /* ����AKA��Ȩ��ISIM��USIM��ͬ����USIMģ��IMS�������ֱ���·���Ȩ��
    �����ж�95�ŷ���λ��������Ȩ��Ҫ�ж� */
    if (USIMM_IMS_AUTH == pstMsg->enAuthType)
    {
        *pucMode = USIMM_USIM_3G_AUTH_MODE;

        return VOS_OK;
    }

    /* ����USIM����ӿڣ��ж�USIM���Ƿ�֧��IMS */
    ulIMSSVR = USIMM_IsUSIMServiceAvailable(USIM_SVR_ACCESS_IMS);

    if(PS_USIM_SERVICE_AVAILIABLE != ulIMSSVR)
    {
        return VOS_ERR;
    }

    if ((USIMM_GBA_AUTH == pstMsg->enAuthType) || (USIMM_NAF_AUTH == pstMsg->enAuthType))
    {
        *pucMode = USIMM_USIM_GBA_AUTH_MODE;

        return VOS_OK;
    }

    return VOS_ERR;
}
VOS_UINT32 USIMM_ISIMAuthHandle(USIMM_AUTH_REQ_STRU *pstMsg)
{
    USIMM_IMS_AUTH_INFO_STRU            stCnfInfo;
    VOS_UINT32                          ulResult;
    VOS_UINT16                          ausUsimPath[]={MF, ADF};
    VOS_UINT8                           ucMode;
    VOS_UINT32                          ulOffset = 1;

    /*lint -e534*/
    VOS_MemSet(&stCnfInfo, 0, sizeof(stCnfInfo));
    /*lint +e534*/

    if (USIMM_CARD_ISIM != gastUSIMMCardAppInfo[USIMM_UICC_ISIM].enCardType)
    {
        USIMM_ERROR_LOG("USIMM_ISIMAuthHandle: ISIM is disable.");

        stCnfInfo.enResult = USIMM_AUTH_IMS_OTHER_FAILURE;

        USIMM_ImsAuthCnf(pstMsg, &stCnfInfo);

        return VOS_ERR;
    }

    /* ������Ⲣȷ����Ȩ���ݲ��� */
    if (VOS_OK != USIMM_ISIMAuthParaCheck(pstMsg, &ucMode))
    {
        USIMM_ERROR_LOG("USIMM_ISIMAuthHandle: enAuthType is wrong.");

        stCnfInfo.enResult = USIMM_AUTH_IMS_OTHER_FAILURE;

        USIMM_ImsAuthCnf(pstMsg, &stCnfInfo);

        return VOS_ERR;
    }

    ulResult = USIMM_SelectFile(USIMM_UMTS_APP, USIMM_NEED_FCP, ARRAYSIZE(ausUsimPath), ausUsimPath);

    if (VOS_OK != ulResult)/*�жϽ��*/
    {
        USIMM_ERROR_LOG("USIMM_ISIMAuthHandle: Select ADF Error");

        stCnfInfo.enResult = USIMM_AUTH_IMS_OTHER_FAILURE;

        USIMM_ImsAuthCnf(pstMsg, &stCnfInfo);

        return VOS_ERR;
    }

    ulResult = USIMM_Authentication_APDU(0x0, ucMode, pstMsg->aucData, pstMsg->ulDataLen);

    if (VOS_OK != ulResult)/*�жϼ�Ȩ���ͽ��*/
    {
        USIMM_ERROR_LOG("USIMM_ISIMAuthHandle: Send USIM Authentication APDU Error");

        stCnfInfo.enResult = USIMM_AUTH_IMS_OTHER_FAILURE;

        USIMM_ImsAuthCnf(pstMsg, &stCnfInfo);

        return VOS_ERR;
    }

    ulResult = USIMM_CheckSW(&gstUSIMMAPDU);

    if (USIMM_SW_AUTN_ERROR == ulResult)
    {
        USIMM_WARNING_LOG("USIMM_ISIMAuthHandle: SIM Check SW Error");

        stCnfInfo.enResult = USIMM_AUTH_MAC_FAILURE;

        USIMM_ImsAuthCnf(pstMsg, &stCnfInfo);

        return VOS_ERR;
    }

    if (VOS_OK != ulResult)
    {
        stCnfInfo.enResult = USIMM_AUTH_IMS_OTHER_FAILURE;

        USIMM_ImsAuthCnf(pstMsg, &stCnfInfo);

        return VOS_ERR;
    }

    /* ��Ȩ�ɹ� */
    if (USIMM_AUTH_SUCCESS_TAG == gstUSIMMAPDU.aucRecvBuf[0])
    {
        if (USIMM_IMS_AUTH == pstMsg->enAuthType)
        {
            stCnfInfo.pucAutsRes    = &gstUSIMMAPDU.aucRecvBuf[ulOffset];/*ָ��Res*/

            ulOffset                += gstUSIMMAPDU.aucRecvBuf[ulOffset] + 1;/*ָ��CK*/

            stCnfInfo.pucCK         = &gstUSIMMAPDU.aucRecvBuf[ulOffset];

            ulOffset                += gstUSIMMAPDU.aucRecvBuf[ulOffset] + 1;/*ָ��IK*/

            stCnfInfo.pucIK         = &gstUSIMMAPDU.aucRecvBuf[ulOffset];
        }
        else if (USIMM_GBA_AUTH == pstMsg->enAuthType)
        {
            stCnfInfo.pucAutsRes    = &gstUSIMMAPDU.aucRecvBuf[ulOffset];
        }
        else
        {
            stCnfInfo.pucKs_ext_NAF = &gstUSIMMAPDU.aucRecvBuf[ulOffset];
        }

        stCnfInfo.enResult  = USIMM_AUTH_IMS_SUCCESS;

        USIMM_ImsAuthCnf(pstMsg, &stCnfInfo);

        return VOS_OK;
    }

    /* ͬ��ʧ�� */
    if (USIMM_AUTH_SYNC_FAIL_TAG == gstUSIMMAPDU.aucRecvBuf[0])
    {
        if ((USIMM_IMS_AUTH == pstMsg->enAuthType) || (USIMM_GBA_AUTH == pstMsg->enAuthType))
        {
            stCnfInfo.pucAuts  = &gstUSIMMAPDU.aucRecvBuf[ulOffset];

            stCnfInfo.enResult = USIMM_AUTH_SYNC_FAILURE;

            USIMM_ImsAuthCnf(pstMsg, &stCnfInfo);

            return VOS_ERR;
        }
    }

    stCnfInfo.enResult  = USIMM_AUTH_IMS_OTHER_FAILURE;

    USIMM_ImsAuthCnf(pstMsg, &stCnfInfo);

    return VOS_ERR;
}

/*****************************************************************************
�� �� ��  : USIMM_AuthMsgTransferProc
��������  : ������Ϣ�м�Ȩ������䵽ԭ���ļ�Ȩ��Ϣ��
�������  : pstNewMsg:����Ϣ�ṹ
�������  : pstPrvMsg:ԭ����Ϣ�ṹ
�� �� ֵ  : VOS_OK/VOS_ERR
���ú���  :
��������  :
�޶���¼  :
1.��    ��  : 2015��01��30��
  ��    ��  : H00300778
  �޸�����  : �½�����
*****************************************************************************/
VOS_VOID USIMM_AuthMsgTransferFillDataProc(
    USIMM_AUTHENTICATION_REQ_STRU      *pstNewMsg,
    USIMM_AUTH_REQ_STRU                *pstPrvMsg)
{
    VOS_UINT32                          ulOffset;

    switch (pstPrvMsg->enAuthType)
    {
        /* �������ݲ���LV��ʽ������ÿ���ֶζ���ҪԤ��һ���ֽڴ�ų��ȣ�������˵����ͬ */
        case USIMM_3G_AUTH:

            if (USIMM_UMTS_APP == pstPrvMsg->enAppType)
            {
                pstPrvMsg->ulDataLen    = pstNewMsg->uAuth.st3GAuth.stRand.ucDataLen
                                        + pstNewMsg->uAuth.st3GAuth.stAutn.ucDataLen
                                        + 2;


                pstPrvMsg->aucData[0] = pstNewMsg->uAuth.st3GAuth.stRand.ucDataLen;

                /*lint -e534*/
                VOS_MemCpy(pstPrvMsg->aucData + 1, pstNewMsg->uAuth.st3GAuth.stRand.aucData, pstPrvMsg->aucData[0]);
                /*lint +e534*/

                ulOffset = pstPrvMsg->aucData[0] + 1;

                pstPrvMsg->aucData[ulOffset] = pstNewMsg->uAuth.st3GAuth.stAutn.ucDataLen;

                /*lint -e534*/
                VOS_MemCpy(pstPrvMsg->aucData + ulOffset + 1, pstNewMsg->uAuth.st3GAuth.stAutn.aucData, pstPrvMsg->aucData[ulOffset]);
                /*lint +e534*/
            }
            else
            {
                /* CDMA��3G��ȨAUTN����Ҫ�����ȣ�RAND����Ҫ������ֻҪ��1 */
                pstPrvMsg->ulDataLen    = pstNewMsg->uAuth.st3GAuth.stRand.ucDataLen
                                        + pstNewMsg->uAuth.st3GAuth.stAutn.ucDataLen + 1;

                /*lint -e534*/
                VOS_MemCpy(pstPrvMsg->aucData, pstNewMsg->uAuth.st3GAuth.stRand.aucData, pstNewMsg->uAuth.st3GAuth.stRand.ucDataLen);
                /*lint +e534*/

                ulOffset = pstNewMsg->uAuth.st3GAuth.stRand.ucDataLen;

                pstPrvMsg->aucData[ulOffset] = pstNewMsg->uAuth.st3GAuth.stAutn.ucDataLen;

                /*lint -e534*/
                VOS_MemCpy(pstPrvMsg->aucData + ulOffset + 1,
                           pstNewMsg->uAuth.st3GAuth.stAutn.aucData,
                           pstNewMsg->uAuth.st3GAuth.stAutn.ucDataLen);
                /*lint +e534*/
            }


            break;

        case USIMM_2G_AUTH:
            pstPrvMsg->ulDataLen        = pstNewMsg->uAuth.st2GAuth.stRand.ucDataLen + 1;

            pstPrvMsg->aucData[0]       = pstNewMsg->uAuth.st2GAuth.stRand.ucDataLen;

            /*lint -e534*/
            VOS_MemCpy(pstPrvMsg->aucData + 1, pstNewMsg->uAuth.st2GAuth.stRand.aucData, pstPrvMsg->aucData[0]);
            /*lint +e534*/

            break;

        case USIMM_IMS_AUTH:
            pstPrvMsg->ulDataLen        = pstNewMsg->uAuth.stImsAuth.stRand.ucDataLen
                                        + pstNewMsg->uAuth.stImsAuth.stAutn.ucDataLen
                                        + 2;

            pstPrvMsg->aucData[0] = pstNewMsg->uAuth.stImsAuth.stRand.ucDataLen;

            /*lint -e534*/
            VOS_MemCpy(pstPrvMsg->aucData + 1, pstNewMsg->uAuth.stImsAuth.stRand.aucData, pstPrvMsg->aucData[0]);
            /*lint +e534*/

            ulOffset = pstPrvMsg->aucData[0] + 1;

            pstPrvMsg->aucData[ulOffset] = pstNewMsg->uAuth.stImsAuth.stAutn.ucDataLen;

            /*lint -e534*/
            VOS_MemCpy(pstPrvMsg->aucData + ulOffset + 1, pstNewMsg->uAuth.stImsAuth.stAutn.aucData, pstPrvMsg->aucData[ulOffset]);
            /*lint +e534*/
            break;

        case USIMM_HTTP_AUTH:
            pstPrvMsg->ulDataLen        = pstNewMsg->uAuth.stHttpAuth.stRealm.ucDataLen
                                        + pstNewMsg->uAuth.stHttpAuth.stNonce.ucDataLen
                                        + pstNewMsg->uAuth.stHttpAuth.stCnonce.ucDataLen
                                        + 3;

            pstPrvMsg->aucData[0] = pstNewMsg->uAuth.stHttpAuth.stRealm.ucDataLen;

            /*lint -e534*/
            VOS_MemCpy(pstPrvMsg->aucData + 1, pstNewMsg->uAuth.stHttpAuth.stRealm.aucData, pstPrvMsg->aucData[0]);
            /*lint +e534*/

            ulOffset = pstPrvMsg->aucData[0] + 1;

            pstPrvMsg->aucData[ulOffset] = pstNewMsg->uAuth.stHttpAuth.stNonce.ucDataLen;

            /*lint -e534*/
            VOS_MemCpy(pstPrvMsg->aucData + ulOffset + 1, pstNewMsg->uAuth.stHttpAuth.stNonce.aucData, pstPrvMsg->aucData[ulOffset]);
            /*lint +e534*/

            ulOffset += pstPrvMsg->aucData[ulOffset] + 1;

            pstPrvMsg->aucData[ulOffset] = pstNewMsg->uAuth.stHttpAuth.stCnonce.ucDataLen;

            /*lint -e534*/
            VOS_MemCpy(pstPrvMsg->aucData + ulOffset + 1, pstNewMsg->uAuth.stHttpAuth.stCnonce.aucData, pstPrvMsg->aucData[ulOffset]);
            /*lint +e534*/

            break;

        /* ����GBA��Ȩ��ʽ��ͷ������Ҫ������һ��tag�ֶΣ�����Ҫ��3 */
        case USIMM_GBA_AUTH:
            pstPrvMsg->ulDataLen         = pstNewMsg->uAuth.stGbaAuth.stRand.ucDataLen
                                         + pstNewMsg->uAuth.stGbaAuth.stAutn.ucDataLen
                                         + 3;

            pstPrvMsg->aucData[0]        = USIMM_GBA_AUTH_TAG;

            pstPrvMsg->aucData[1]        = pstNewMsg->uAuth.stGbaAuth.stRand.ucDataLen;

            /*lint -e534*/
            VOS_MemCpy(pstPrvMsg->aucData + 2, pstNewMsg->uAuth.stGbaAuth.stRand.aucData, pstPrvMsg->aucData[1]);
            /*lint +e534*/

            ulOffset = pstPrvMsg->aucData[1] + 2;

            pstPrvMsg->aucData[ulOffset] = pstNewMsg->uAuth.stGbaAuth.stAutn.ucDataLen;

            /*lint -e534*/
            VOS_MemCpy(pstPrvMsg->aucData + ulOffset + 1, pstNewMsg->uAuth.stGbaAuth.stAutn.aucData, pstPrvMsg->aucData[ulOffset]);
            /*lint +e534*/
            break;

        /* ����NAF��Ȩ��ʽ��ͷ������Ҫ������һ��tag�ֶΣ�����Ҫ��3 */
        case USIMM_NAF_AUTH:
            pstPrvMsg->ulDataLen        = pstNewMsg->uAuth.stNafAuth.stNafID.ucDataLen
                                        + pstNewMsg->uAuth.stNafAuth.stImpi.ucDataLen
                                        + 3;

            pstPrvMsg->aucData[0]       = USIMM_NAF_AUTH_TAG;

            pstPrvMsg->aucData[1]       = pstNewMsg->uAuth.stNafAuth.stNafID.ucDataLen;

            /*lint -e534*/
            VOS_MemCpy(pstPrvMsg->aucData + 2, pstNewMsg->uAuth.stNafAuth.stNafID.aucData, pstPrvMsg->aucData[1]);
            /*lint +e534*/

            ulOffset = pstPrvMsg->aucData[1] + 2;

            pstPrvMsg->aucData[ulOffset]= pstNewMsg->uAuth.stNafAuth.stImpi.ucDataLen;

            /*lint -e534*/
            VOS_MemCpy(pstPrvMsg->aucData + ulOffset + 1, pstNewMsg->uAuth.stNafAuth.stImpi.aucData, pstPrvMsg->aucData[ulOffset]);
            /*lint +e534*/
            break;

        case USIMM_RUNCAVE_AUTH:

            pstPrvMsg->ulDataLen        = USIMM_AUTH_RUNCAVE_LEN;

            pstPrvMsg->aucData[0]       = pstNewMsg->uAuth.stRunCaveAuth.ucRandType;

            if (USIMM_RUNCAVE_RAND == pstPrvMsg->aucData[0])
            {
                /*lint -e534*/
                VOS_MemCpy(pstPrvMsg->aucData + 1, pstNewMsg->uAuth.stRunCaveAuth.aucRand, USIMM_RUNCAVE_RAND_LEN);
                /*lint +e534*/
            }
            else
            {
                pstPrvMsg->aucData[1]   = 0;

                /*lint -e534*/
                VOS_MemCpy(pstPrvMsg->aucData + 2, pstNewMsg->uAuth.stRunCaveAuth.aucRand, USIMM_RUNCAVE_RAND_LEN - 1);
                /*lint +e534*/
            }

            pstPrvMsg->aucData[5] = pstNewMsg->uAuth.stRunCaveAuth.ucDigLen;

            pstPrvMsg->aucData[9] = pstNewMsg->uAuth.stRunCaveAuth.ucProcessCtrl;

            /*lint -e534*/
            VOS_MemCpy(pstPrvMsg->aucData + 6, pstNewMsg->uAuth.stRunCaveAuth.aucDigits, USIMM_RUNCAVE_DIGLEN);

            VOS_MemCpy(pstPrvMsg->aucData + 10, pstNewMsg->uAuth.stRunCaveAuth.aucEsn, USIMM_ESN_MEID_LEN);
            /*lint +e534*/

            break;

        default:
            break;
    }

    return;
}

/*****************************************************************************
�� �� ��  : USIMM_AuthMsgTransferProc
��������  : ������Ϣת����ԭ���ļ�Ȩ��Ϣ
�������  : pstNewMsg:����Ϣ�ṹ
�������  : pstPrvMsg:ԭ����Ϣ�ṹ
�� �� ֵ  : ��
���ú���  :
��������  :
�޶���¼  :
1.��    ��  : 2015��01��30��
  ��    ��  : H00300778
  �޸�����  : �½�����
*****************************************************************************/
VOS_UINT32 USIMM_AuthMsgTransferProc(
    USIMM_AUTHENTICATION_REQ_STRU      *pstNewMsg,
    USIMM_AUTH_REQ_STRU                *pstPrvMsg)
{
    USIMM_TELECOM_AUTH_INFO_STRU        stTelCnfInfo;
    USIMM_IMS_AUTH_INFO_STRU            stImsCnfInfo;
#if (FEATURE_UE_MODE_CDMA == FEATURE_ON)
    USIMM_CDMA_AUTH_INFO_STRU           stCdmaCnfInfo;
#endif

    /* ����Ȩ���� */
    pstPrvMsg->enAuthType = pstNewMsg->enAuthType;
    pstPrvMsg->ulOpId     = pstNewMsg->stMsgHeader.ulSendPara;

    /* ������Ϣͷ */
    /*lint -e534*/
    VOS_MemCpy(pstPrvMsg, pstNewMsg, VOS_MSG_HEAD_LENGTH);
    /*lint +e534*/

    if (USIMM_API_SUCCESS != USIMM_ApiParaCheckSimple())
    {
        if (USIMM_GUTL_APP == pstNewMsg->stMsgHeader.enAppType)
        {
            /*lint -e534*/
            VOS_MemSet(&stTelCnfInfo, 0, sizeof(USIMM_TELECOM_AUTH_INFO_STRU));
            /*lint +e534*/

            stTelCnfInfo.enResult = USIMM_AUTH_UMTS_OTHER_FAILURE;

            USIMM_TelecomAuthCnf(pstPrvMsg, &stTelCnfInfo);
        }

        if (USIMM_IMS_APP == pstNewMsg->stMsgHeader.enAppType)
        {
            /*lint -e534*/
            VOS_MemSet(&stImsCnfInfo, 0, sizeof(USIMM_TELECOM_AUTH_INFO_STRU));
            /*lint +e534*/

            stImsCnfInfo.enResult = USIMM_AUTH_IMS_OTHER_FAILURE;

            USIMM_ImsAuthCnf(pstPrvMsg, &stImsCnfInfo);
        }
#if (FEATURE_UE_MODE_CDMA == FEATURE_ON)
        if (USIMM_CDMA_APP == pstNewMsg->stMsgHeader.enAppType)
        {
            /*lint -e534*/
            VOS_MemSet(&stCdmaCnfInfo, 0, sizeof(USIMM_CDMA_AUTH_INFO_STRU));
            /*lint +e534*/

            stCdmaCnfInfo.enResult = USIMM_AUTH_CDMA_OTHER_FAILURE;

            USIMM_CdmaAuthCnf(pstPrvMsg, &stCdmaCnfInfo);
        }
#endif

        return VOS_ERR;
    }

    switch (pstNewMsg->stMsgHeader.enAppType)
    {
        /* GUTL����ʱSIM��ת��GSM APP,USIM��ת��UMTS */
        case USIMM_GUTL_APP:
            if (USIMM_CARD_SIM == gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardType)
            {
                pstPrvMsg->enAppType = USIMM_GSM_APP;
            }
            else if (USIMM_CARD_USIM == gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardType)
            {
                pstPrvMsg->enAppType = USIMM_UMTS_APP;
            }
            else
            {
                pstPrvMsg->enAppType = USIMM_APP_BUTT;
            }
            break;

        case USIMM_IMS_APP:

            pstPrvMsg->enAppType = USIMM_ISIM_APP;

            break;
#if (FEATURE_UE_MODE_CDMA == FEATURE_ON)
        case USIMM_CDMA_APP:
            pstPrvMsg->enAppType = USIMM_3GPP2_APP;
            break;
#endif

        default:
            /* ��������� */
            pstPrvMsg->enAppType = USIMM_APP_BUTT;
            break;
    }

    USIMM_AuthMsgTransferFillDataProc(pstNewMsg, pstPrvMsg);

    return VOS_OK;
}


VOS_UINT32 USIMM_AuthenticationHandle(USIMM_CMDHEADER_REQ_STRU *pMsg)
{
    USIMM_AUTH_REQ_STRU                 stMsg;

    /* ����¾���Ϣ��ת�����������Ե�ǰ����״̬������ */
    if (VOS_OK != USIMM_AuthMsgTransferProc((USIMM_AUTHENTICATION_REQ_STRU *)pMsg, &stMsg))
    {
        return VOS_ERR;
    }

#if (FEATURE_VSIM == FEATURE_ON)
    if(VOS_TRUE == USIMM_VsimIsActive())    /*vSIM is Active*/
    {
        if (USIMM_UMTS_APP == stMsg.enAppType)
        {
            return USIMM_AuthenVirtulUsim(&stMsg);
        }
        else if (USIMM_GSM_APP == stMsg.enAppType)
        {
            return USIMM_AuthenVirtulSim(&stMsg);
        }
        else
        {
            return VOS_ERR;
        }
    }
#endif

    /*Ӳ������*/
    if (USIMM_GSM_APP == stMsg.enAppType)
    {
        return USIMM_SIMAuthHandle(&stMsg);
    }

    if (USIMM_UMTS_APP == stMsg.enAppType)
    {
        return USIMM_USIMAuthHandle(&stMsg);
    }

    if (USIMM_ISIM_APP == stMsg.enAppType)
    {
        return USIMM_ISIMAuthHandle(&stMsg);
    }
#if (FEATURE_UE_MODE_CDMA == FEATURE_ON)
    if (USIMM_3GPP2_APP == stMsg.enAppType)
    {
        return USIMM_CdmaAuthHandle(&stMsg);
    }
#endif
    USIMM_ERROR_LOG("USIMM_AuthenticationHandle: enAppType is incorrect.");

    return VOS_ERR;
}
VOS_UINT32 USIMM_FDNHandle(USIMM_CMDHEADER_REQ_STRU *pMsg)
{
    VOS_UINT32                          ulResult;
    USIMM_FDNPROCESS_REQ_STRU          *pstMsg;
    VOS_UINT16                          ausUsimPath[]={MF, ADF};
    VOS_UINT16                          ausSimPath[]={MF, DFGSM};
    VOS_UINT32                          ulSimSvr;
    VOS_UINT32                          ulUsimSvr;

    pstMsg = (USIMM_FDNPROCESS_REQ_STRU *)pMsg;

    if (USIMM_API_SUCCESS != USIMM_ApiParaCheck())
    {
        USIMM_WARNING_LOG("USIMM_FDNHandle: USIMM_ApiParaCheck is Failed");/*��ӡ����*/

        USIMM_FDNCnf(pstMsg->stMsgHeader.ulSenderPid,
                     VOS_ERR,
                     VOS_ERR,
                     pstMsg->stMsgHeader.enAppType,
                     pstMsg->stMsgHeader.ulSendPara,
                     (VOS_UINT32)gstUSIMMBaseInfo.enFDNStatus);

        return VOS_ERR; /*���غ���������Ϣ*/
    }


    ulSimSvr    = USIMM_IsServiceAvailable(SIM_SVR_FDN);
    ulUsimSvr   = USIMM_IsServiceAvailable(USIM_SVR_FDN);

    if ((PS_USIM_SERVICE_NOT_AVAILIABLE == ulSimSvr)
        && (PS_USIM_SERVICE_NOT_AVAILIABLE == ulUsimSvr))
    {
        USIMM_FDNCnf(pstMsg->stMsgHeader.ulSenderPid,
                     VOS_ERR,
                     VOS_ERR,
                     pstMsg->stMsgHeader.enAppType,
                     pstMsg->stMsgHeader.ulSendPara,
                     (VOS_UINT32)gstUSIMMBaseInfo.enFDNStatus);

        return VOS_ERR;
    }

    if (USIMM_CARD_USIM == gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardType)
    {
        /*����ADF����������*/
        ulResult = USIMM_SelectFile(USIMM_UMTS_APP, USIMM_NEED_FCP, ARRAYSIZE(ausUsimPath), ausUsimPath);
    }
    else
    {
        /*����ADF����������*/
        ulResult = USIMM_SelectFile(USIMM_GSM_APP, USIMM_NEED_FCP, ARRAYSIZE(ausSimPath), ausSimPath);
    }

    ulResult = USIMM_PINVerify(USIMM_PIN2, USIMM_PINCMD_VERIFY, pstMsg->aucPIN);

    /*lint -e534*/
    USIMM_AdjudgeCardState();    /*�жϵ�ǰ��״̬*/
    /*lint +e534*/

    if (ulResult != VOS_OK)/*�жϽ��*/
    {
        USIMM_FDNCnf(pstMsg->stMsgHeader.ulSenderPid,
                     ulResult,
                     ulResult,
                     pstMsg->stMsgHeader.enAppType,
                     pstMsg->stMsgHeader.ulSendPara,
                     (VOS_UINT32)gstUSIMMBaseInfo.enFDNStatus);

        return VOS_ERR;
    }

    /* �жϵ�ǰȫ�ֱ�����FDN״̬�� */
    if (pstMsg->enHandleType == gstUSIMMBaseInfo.enFDNStatus)
    {
        USIMM_FDNCnf(pstMsg->stMsgHeader.ulSenderPid,
                     VOS_OK,
                     VOS_OK,
                     pstMsg->stMsgHeader.enAppType,
                     pstMsg->stMsgHeader.ulSendPara,
                     (VOS_UINT32)gstUSIMMBaseInfo.enFDNStatus);

        return VOS_OK;
    }

    if (USIMM_FDN_ACTIVE == pstMsg->enHandleType)
    {
        ulResult = USIMM_FDNEnable();
    }
    else if (USIMM_FDN_DEACTIVE == pstMsg->enHandleType)
    {
        ulResult = USIMM_FDNDisable();
    }
    else
    {
        /*��ǰֻ֧��FDN������BDN�Ĳ������ش���*/
        ulResult = VOS_ERR;
    }

    /* �ϱ�FDN״̬��� */
    if (VOS_OK == ulResult)
    {
        gstUSIMMBaseInfo.enFDNStatus = pstMsg->enHandleType;

        /* ΪNAS ECALL ������ʱ�����ӣ�V8R1�޸Ļ��� */
        if (USIMM_CARD_USIM == gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardType)
        {
            USIMM_FDNEstChgInd();
        }
    }

    /* �ظ�������� */
    USIMM_FDNCnf(pstMsg->stMsgHeader.ulSenderPid,
                 ulResult,
                 ulResult,
                 pstMsg->stMsgHeader.enAppType,
                 pstMsg->stMsgHeader.ulSendPara,
                 (VOS_UINT32)gstUSIMMBaseInfo.enFDNStatus);

    return ulResult;
}
VOS_UINT32 USIMM_DeactiveRealCard(USIMM_MsgBlock *pMsg)
{
    VOS_UINT32                          ulErrlogNumber;
    OAM_MNTN_SIM_CARD_LOST_EVENT_STRU   stSimCardLost;

    USIMM_NORMAL_LOG("USIMM_DeactiveRealCard: Deactive Card");

    if (USIMM_OPENSPEEDENABLE == gulUSIMMOpenSpeed)/*��״̬���*/
    {
        USIMM_WARNING_LOG("USIMM_DeactiveCardReq: The Card Status is Wrong");

        return VOS_ERR;
    }

    /* ��Ϊ˫��˫�����Ը�16λ��¼pid,��16λ��¼ԭ����id */
    ulErrlogNumber = pMsg->ulSenderPid;
    ulErrlogNumber <<= 16;
    ulErrlogNumber |= MNTN_OAM_SIM_CARD_LOST_EVENT;

    /* ��Errorlog�ļ��м�¼SIM�������¼� */
    if (VOS_OK != MNTN_RecordErrorLog(ulErrlogNumber,
                                      (void *)&stSimCardLost,
                                      sizeof(OAM_MNTN_SIM_CARD_LOST_EVENT_STRU)))
    {
        USIMM_WARNING_LOG("USIMM_DeactiveRealCard: Fail to record  SIM card lost event in Errorlog file");
    }

    OM_RecordInfoStart(VOS_EXC_DUMP_MEM_NUM_1, WUEPS_PID_USIM, WUEPS_PID_USIM, USIMMDL_DRV_USIMMSCI_DEACT);

    if(VOS_OK != mdrv_sci_deact())
    {
        USIMM_ERROR_LOG("USIMM_DeactiveRealCard: Deactive Card Error");
    }

    OM_RecordInfoEnd(VOS_EXC_DUMP_MEM_NUM_1);

    USIMM_InitGlobalVarOnReset();

    USIMM_InitGlobalVarOnPower();

    gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardType     = USIMM_CARD_NOCARD;
    gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardService  = USIMM_CARD_SERVIC_ABSENT;

    USIMM_ExcLogDataSave((VOS_UINT8 *)&pMsg->ulSenderPid, sizeof(VOS_UINT32));

    USIMM_SaveExcLogFile();

    return VOS_OK;
}
VOS_UINT32 USIMM_DeactiveCardHandle(USIMM_CMDHEADER_REQ_STRU *pMsg)
{
#if (FEATURE_VSIM == FEATURE_ON)
    if(VOS_TRUE == USIMM_VsimIsActive())    /*vSIM is Active*/
    {
        return USIMM_DeactiveVsim((USIMM_MsgBlock*)pMsg);
    }
#endif

    /*Ӳ������*/
    return USIMM_DeactiveRealCard((USIMM_MsgBlock*)pMsg);
}


VOS_UINT32 USIMM_CardInOutHandle(USIMM_CMDHEADER_REQ_STRU *pMsg)
{
    USIMM_CARD_INOUT_IND_STRU           *pstMsg;
    USIMM_HOTINOUT_IND_STRU             *pstUsimMsg;

    pstMsg = (USIMM_CARD_INOUT_IND_STRU *)pMsg;

    pstUsimMsg = (USIMM_HOTINOUT_IND_STRU *)VOS_AllocMsg(WUEPS_PID_USIM,
                                                       sizeof(USIMM_HOTINOUT_IND_STRU)-VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstUsimMsg)
    {
        USIMM_ERROR_LOG("USIMM_CardInOutHandle: VOS_AllocMsg is Failed");

        return VOS_ERR;
    }

    pstUsimMsg->stIndHdr.enMsgName      = USIMM_HOTINOUT_IND;
    pstUsimMsg->stIndHdr.ulReceiverPid  = WUEPS_PID_MMA;
    pstUsimMsg->ulCardInOutStatus       = pstMsg->ulCardInOutStatus;

    (VOS_VOID)VOS_SendMsg(WUEPS_PID_USIM, pstUsimMsg);

    if (USIMM_CARDSTATUS_IND_PLUGOUT == pstMsg->ulCardInOutStatus)  /*����ȥ����ӿ�ʵ�ֿ�״̬�ϱ��ͱ����Ը�λֹͣ*/
    {
        /*lint -e534*/
        USIMM_DeactiveRealCard((USIMM_MsgBlock *)pMsg);
        /*lint +e534*/
    }

    return VOS_OK;
}
VOS_UINT32 USIMM_InitCardHandle(USIMM_CMDHEADER_REQ_STRU *pMsg)
{
    VOS_UINT32                      ulResult;

#if (FEATURE_UE_MODE_CDMA == FEATURE_ON)
    ulResult = UICC_InitCardHandle((USIMM_MsgBlock*)pMsg);
#else
#if (FEATURE_VSIM == FEATURE_ON)
    if(VOS_FALSE == USIMM_VsimIsActive())    /*vSIM Close*/
    {
        ulResult =  USIMM_InitCard((USIMM_MsgBlock*)pMsg);
    }
    else
    {
        ulResult =  USIMM_InitVsimCard((USIMM_MsgBlock*)pMsg);
    }
#else
    ulResult = USIMM_InitCard((USIMM_MsgBlock *)pMsg);
#endif  /*(FEATURE_VSIM == FEATURE_ON)*/
#endif  /*(FEATURE_UE_MODE_CDMA == FEATURE_ON)*/

    if (WUEPS_PID_USIM != pMsg->ulSenderPid)  /*�ⲿModule���͵ĳ�ʼ��*/
    {
        USIMM_SingleCmdCnf(pMsg->ulSenderPid,
                           USIMM_ACTIVECARD_CNF,
                           pMsg->ulSendPara,
                           ulResult,
                           pMsg->enAppType);
    }

#if(FEATURE_ON == FEATURE_PTM)
    if (VOS_OK == ulResult)
    {
        USIMM_RecordCardErrorLog(USIMM_MNTN_STATE_OK, USIMM_MNTN_ERROR_LEVEL_INFO);
    }
    else
    {
        USIMM_RecordCardErrorLog(USIMM_MNTN_STATE_INIT_FAIL, USIMM_MNTN_ERROR_LEVEL_MAJOR);
    }
#endif  /*(FEATURE_ON == FEATURE_PTM)*/

    return ulResult;
}


VOS_UINT32 USIMM_IsdbAccessHandle(USIMM_MsgBlock *pMsg)
{
    VOS_UINT32                          ulResult;
    USIMM_ISDB_ACCESS_REQ_STRU         *pstMsg;
    USIMM_SENDTPDU_CNFINFO_STRU         stDataCnf;

    pstMsg = (USIMM_ISDB_ACCESS_REQ_STRU *)pMsg;

    /*lint -e534*/
    VOS_MemSet(&stDataCnf, 0, sizeof(stDataCnf));
    /*lint +e534*/

    stDataCnf.pucTPDUHead = pstMsg->aucContent;

    if (VOS_OK != USIMM_FormatIsdbApdu(pstMsg, &gstUSIMMAPDU))  /*��ϳɱ�׼��ʽ*/
    {
        USIMM_SendTPDUCnf(pstMsg->ulSenderPid,
                          pstMsg->ulSendPara,
                          VOS_ERR,
                          USIMM_SW_ERR,
                          &stDataCnf,
                          VOS_NULL_PTR);

        USIMM_ERROR_LOG("USIMM_IsdbAccessHandle: The USIMM_FormatCsimApdu Return Error");

        return VOS_ERR;
    }

    /* �ӻ���ͨ���·�������Ҫ������� */
    if ((USIMM_USIM_CLA == gstUSIMMAPDU.aucAPDU[CLA])
      &&(CMD_INS_SELECT == gstUSIMMAPDU.aucAPDU[INS]))
    {
        USIMM_ClearCurFileInfo();
    }

    ulResult = USIMM_DLHandle(&gstUSIMMAPDU); /* ������·�㺯�� */

    if((0x62 == gstUSIMMAPDU.ucApduSW1)&&(0xF3 == gstUSIMMAPDU.ucApduSW2))
    {
        stDataCnf.ucSw1     =   gstUSIMMAPDU.ucApduSW1;
        stDataCnf.ucSw2     =   gstUSIMMAPDU.ucApduSW2;
        stDataCnf.usDataLen =   VOS_NULL;
        stDataCnf.pucData   =   VOS_NULL_PTR;
    }
    else
    {
        stDataCnf.ucSw1     =   gstUSIMMAPDU.ucSW1;
        stDataCnf.ucSw2     =   gstUSIMMAPDU.ucSW2;
        stDataCnf.usDataLen =   (VOS_UINT16)gstUSIMMAPDU.ulRecDataLen;
        stDataCnf.pucData   =   gstUSIMMAPDU.aucRecvBuf;
    }

    USIMM_SendTPDUCnf(pstMsg->ulSenderPid,
                      pstMsg->ulSendPara,
                      ulResult,
                      ulResult,
                      &stDataCnf,
                      VOS_NULL_PTR);

    return ulResult;
}
VOS_UINT32 USIMM_SearchCHFree(VOS_VOID)
{
    VOS_UINT8                           ucIndex;

    for (ucIndex = 0; ucIndex < USIMM_CHANNEL_NUM_MAX; ucIndex++)
    {
        if (0 == g_astUSIMMChCtrl[ucIndex].ulSessionId)
        {
             return VOS_OK;
        }
    }

    return VOS_ERR;
}


VOS_UINT8 USIMM_SearchCHCtrl(VOS_UINT32 ulSessionId)
{
    VOS_UINT8                          ucIndex;

    for (ucIndex = 0; ucIndex < USIMM_CHANNEL_NUM_MAX; ucIndex++)
    {
        if (ulSessionId == g_astUSIMMChCtrl[ucIndex].ulSessionId)
        {
            return ucIndex;
        }
    }

    return USIMM_CHANNEL_NUM_MAX;
}


VOS_UINT32 USIMM_CloseChannel(VOS_UINT8 ucChannelID)
{
    VOS_UINT32                          ulResult;

    /* �·�manage���߼�ͨ��,��ͨ����ʱ��P2����ΪucChannelID,P3������0,��ʱ�������������� */
    if (VOS_OK != USIMM_Manage_Channel_APDU(USIMM_CLOSE_CHANNEL, ucChannelID, 0))
    {
        USIMM_ERROR_LOG("USIMM_CloseChannel: The USIMM_Manage_Channel_APDU Return Error");

        return VOS_ERR;
    }

    ulResult = USIMM_CheckSW(&gstUSIMMAPDU);

    /*�жϼ����*/
    if (USIMM_SW_OK != ulResult)
    {
        USIMM_WARNING_LOG("USIMM_CloseChannel: USIMM_CheckSW Error");

        return ulResult;
    }

    return VOS_OK;
}



VOS_UINT32 USIMM_OpenChannel(VOS_UINT8 *pucChannelID, VOS_UINT32 *pulSessionId)
{
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucChannelID;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulSessionId;

    /* �·�manage���߼�ͨ��,��ͨ����ʱ���ڻ����߼�ͨ���ϣ����P2����Ϊ0,P3������1����������һ���ֽڵ�channelID */
    if (VOS_OK != USIMM_Manage_Channel_APDU(USIMM_OPEN_CHANNEL, 0, 1))
    {
        USIMM_ERROR_LOG("USIMM_OpenChannel: The USIMM_Manage_Channel_APDU Return Error");

        return VOS_ERR;
    }

    ulResult = USIMM_CheckSW(&gstUSIMMAPDU);

    /*�жϼ����*/
    if (USIMM_SW_OK != ulResult)
    {
        USIMM_WARNING_LOG("USIMM_OpenChannel: USIMM_CheckSW Error");

        return ulResult;
    }

    ucChannelID = gstUSIMMAPDU.aucRecvBuf[0];

    /* ͨ��ID�����Ϸ���Χ */
    if (USIMM_CHANNEL_NUM_MAX <= ucChannelID)
    {
        USIMM_ERROR_LOG("USIMM_OpenChannel: Channel ID is not valid.");

        /*lint -e534*/
        USIMM_CloseChannel(ucChannelID);
        /*lint +e534*/

        return VOS_ERR;
    }

    /* ��ͨ��ID�Ѿ���ʹ�� */
    if (0 != g_astUSIMMChCtrl[ucChannelID].ulSessionId)
    {
        USIMM_ERROR_LOG("USIMM_OpenChannel: This channel is used already.");

        /*lint -e534*/
        USIMM_CloseChannel(ucChannelID);
        /*lint +e534*/

        return VOS_ERR;
    }

    for(ucIndex = 0; ucIndex < VOS_NULL_BYTE; ucIndex++)
    {
        ulSessionId = VOS_Rand(USIMM_SESSION_ID_MAX);

        if(0 != ulSessionId)
        {
            break;
        }
    }

    if(VOS_NULL_BYTE == ucIndex)
    {
        USIMM_ERROR_LOG("USIMM_OpenChannel: make rand err.");

        /*lint -e534*/
        USIMM_CloseChannel(ucChannelID);
        /*lint +e534*/

        return VOS_ERR;
    }

    *pulSessionId = USIMM_SESSION_ID(ulSessionId, ucChannelID);

    *pucChannelID = ucChannelID;

    return VOS_OK;
}


VOS_UINT32 USIMM_OpenChannelHandle(USIMM_CMDHEADER_REQ_STRU *pMsg)
{
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucChannelId = VOS_NULL_BYTE;
    VOS_UINT32                          ulSessionId = VOS_NULL_DWORD;
    USIMM_OPENCHANNEL_REQ_STRU         *pstMsg;
    USIMM_APDU_ST                       stApduInfo = {0};
    VOS_UINT32                          i;
    VOS_UINT32                          ulMemCmpRlst;
    VOS_UINT32                          ulClEnable;

    pstMsg = (USIMM_OPENCHANNEL_REQ_STRU *)pMsg;

    if (VOS_FALSE == USIMM_IsCLEnable())
    {
        ulResult = USIMM_ApiParaCheck();

        if (USIMM_API_SUCCESS != ulResult)
        {
            USIMM_WARNING_LOG("USIMM_OpenChannelHandle: USIMM_ApiParaCheck is Failed");/*��ӡ����*/

            USIMM_OpenChannelCnf(pstMsg->stMsgHeader.ulSenderPid,
                                 pstMsg->stMsgHeader.ulSendPara,
                                 TAF_ERR_SIM_FAIL,
                                 VOS_ERR,
                                 VOS_NULL_DWORD,
                                 VOS_NULL);

            return ulResult; /*���غ���������Ϣ*/
        }
    }

    /* CLģʽ�£�CSIMӦ���Ѿ���ǰ���߼�ͨ������ǰ���践��session-id���� */
    ulMemCmpRlst = (VOS_UINT32)VOS_MemCmp(pstMsg->stChannelInfo.aucADFName, g_astAidInfo[USIMM_AID_TYPE_CSIM].aucAID, g_astAidInfo[USIMM_AID_TYPE_CSIM].ulAIDLen);
    ulClEnable   = USIMM_IsCLEnable();

    if ((pstMsg->stMsgHeader.ulSenderPid == WUEPS_PID_CSIMA)
      && (g_ulCsimSessionId != VOS_NULL_DWORD)
      && (VOS_NULL == ulMemCmpRlst)
      && (VOS_TRUE == ulClEnable))
    {
        USIMM_OpenChannelCnf(pstMsg->stMsgHeader.ulSenderPid,
                             pstMsg->stMsgHeader.ulSendPara,
                             TAF_ERR_NO_ERROR,
                             VOS_OK,
                             g_ulCsimSessionId,
                             VOS_NULL);

        return VOS_OK;
    }

    /* �жϵ�ǰ�Ƿ���ʣ��ͨ�� */
    if (VOS_OK != USIMM_SearchCHFree())
    {
        USIMM_ERROR_LOG("USIMM_OpenChannelHandle: The logic channel is full.");

        USIMM_OpenChannelCnf(pstMsg->stMsgHeader.ulSenderPid,
                             pstMsg->stMsgHeader.ulSendPara,
                             TAF_ERR_MISSING_RESOURCE,
                             VOS_ERR,
                             VOS_NULL_DWORD,
                             VOS_NULL);

        return VOS_ERR;
    }

    /* һ��ͨ��ʹ����ֻ�����һ��ͨ�������֮ǰû�д򿪣����·�MANAGE CHANNEL�����ͨ�� */
    ulResult = USIMM_OpenChannel(&ucChannelId, &ulSessionId);

    if (VOS_OK != ulResult)
    {
        USIMM_OpenChannelCnf(pstMsg->stMsgHeader.ulSenderPid,
                             pstMsg->stMsgHeader.ulSendPara,
                             TAF_ERR_ERROR,
                             ulResult,
                             VOS_NULL_DWORD,
                             VOS_NULL);

        return VOS_ERR;
    }

    if (VOS_TRUE == g_stUsimmFeatureCfg.unCfg.stFeatureCfg.ulAidLenCheckFlg)
    {
        if (pstMsg->stChannelInfo.ulAIDLen < USIMM_AID_LEN_MIN)
        {
            USIMM_ERROR_LOG("USIMM_OpenChannelHandle: the length of AID is error");

            /*lint -e534*/
            USIMM_CloseChannel(ucChannelId);
            /*lint +e534*/

            USIMM_OpenChannelCnf(pstMsg->stMsgHeader.ulSenderPid,
                                 pstMsg->stMsgHeader.ulSendPara,
                                 TAF_ERR_ERROR,
                                 VOS_ERR,
                                 VOS_NULL_DWORD,
                                 VOS_NULL);

            return VOS_ERR;
        }
    }

    stApduInfo.aucAPDU[CLA] = USIMM_USIM_CLA;

    stApduInfo.aucAPDU[P1] = USIMM_SELECT_BY_DF_NAME;

    /* Add by H00300778 for MultiAppSync Begin 2015-05-12 */
    if (VOS_TRUE == g_stUsimmFeatureCfg.unCfg.stFeatureCfg.ulP2ActiveAID)
    {
        stApduInfo.aucAPDU[P2] = USIMM_SELECT_ACTIVATE_AID;
    }
    else
    {
        stApduInfo.aucAPDU[P2] = USIMM_SELECT_RETURN_FCP_TEMPLATE;
    }
    /* Add by H00300778 for MultiAppSync End 2015-05-12 */

    stApduInfo.aucAPDU[P3] = (VOS_UINT8)pstMsg->stChannelInfo.ulAIDLen;

    /*lint -e534*/
    VOS_MemCpy(stApduInfo.aucSendBuf, pstMsg->stChannelInfo.aucADFName, pstMsg->stChannelInfo.ulAIDLen);
    /*lint +e534*/

    for (i = 0; i < 2; i++)
    {
        /* �·�����AID�������ݵ�Ԫ,cla�ֶ�Ӧ���ڴ򿪵��߼�ͨ���� */
        ulResult = USIMM_SelectFileByChannelID_APDU(ucChannelId, &stApduInfo);

        if(VOS_OK != ulResult)
        {
            USIMM_ERROR_LOG("USIMM_OpenChannelHandle: Select ADF Error");

            /*lint -e534*/
            USIMM_CloseChannel(ucChannelId);
            /*lint +e534*/

            USIMM_OpenChannelCnf(pstMsg->stMsgHeader.ulSenderPid,
                                 pstMsg->stMsgHeader.ulSendPara,
                                 TAF_ERR_NO_SUCH_ELEMENT,
                                 ulResult,
                                 VOS_NULL_DWORD,
                                 VOS_NULL);

            return VOS_ERR;
        }

        ulResult = USIMM_CheckSW(&stApduInfo);

        /* ѡ���ļ�ʧ�ܺ���Ҫ��P2������Ϊ0x00,�ٴγ���ѡ���ļ� */
        /* Add by H00300778 for MultiAppSync Begin 2015-05-12 */
        if ((USIMM_SW_OK != ulResult)&&(USIMM_SW_WARNING != ulResult))
        {
            if (USIMM_SELECT_RETURN_FCP_TEMPLATE == stApduInfo.aucAPDU[P2])
            {
                stApduInfo.aucAPDU[P2] = USIMM_SELECT_ACTIVATE_AID;

                USIMM_ERROR_LOG("USIMM_OpenChannelHandle: USIMM_CheckSW set P2 == 0 and try again.");

                continue;
            }
        }
        /* Add by H00300778 for MultiAppSync End 2015-05-12 */

        break;
    }

    /* Add by H00300778 for MultiAppSync Begin 2015-05-12 */
    if ((USIMM_SW_OK != ulResult)&&(USIMM_SW_WARNING != ulResult))
    {
        USIMM_ERROR_LOG("USIMM_OpenChannelHandle: USIMM_CheckSW failed.");

        /*lint -e534*/
        USIMM_CloseChannel(ucChannelId);
        /*lint +e534*/

        USIMM_OpenChannelCnf(pstMsg->stMsgHeader.ulSenderPid,
                             pstMsg->stMsgHeader.ulSendPara,
                             TAF_ERR_NO_SUCH_ELEMENT,
                             ulResult,
                             VOS_NULL_DWORD,
                             VOS_NULL);

        return VOS_ERR;
    }
    /* Add by H00300778 for MultiAppSync End 2015-05-12 */

    /*lint -e534*/
    VOS_MemCpy(&g_astUSIMMChCtrl[ucChannelId], &pstMsg->stChannelInfo, sizeof(USIMM_CHANNEL_INFO_STRU));
    /*lint +e534*/

    if (VOS_TRUE == g_stUsimmFeatureCfg.unCfg.stFeatureCfg.ulAIDFCPSave)
    {
        /*lint -e534*/
        VOS_MemCpy(g_astUSIMMChAIDFCP[ucChannelId].aucADFFcp, stApduInfo.aucRecvBuf, stApduInfo.ulRecDataLen);
        /*lint +e534*/

        g_astUSIMMChAIDFCP[ucChannelId].ulAIDFCPLen = stApduInfo.ulRecDataLen;
    }

    g_astUSIMMChCtrl[ucChannelId].ulSessionId = ulSessionId;
    g_astUSIMMChCtrl[ucChannelId].ulChanNum   = ucChannelId;

    g_astUSIMMChGetRsp[ucChannelId].ulRspLen  = 0;

    USIMM_OpenChannelCnf(pstMsg->stMsgHeader.ulSenderPid,
                         pstMsg->stMsgHeader.ulSendPara,
                         TAF_ERR_NO_ERROR,
                         VOS_OK,
                         ulSessionId,
                         ucChannelId);

    return VOS_OK;
}
VOS_UINT32 USIMM_ChannelCmdParaCheck(VOS_VOID)
{
    /* ���ƶ�Ҫ��Լ�Ȩ����Ҳ�·��������ƶ��汾Ҫ����� */
    if (VOS_TRUE == g_stUsimmFeatureCfg.unCfg.stFeatureCfg.ulAuthCmdCheckFlg)
    {
        /* ��֧��GSM��Ȩ����:��SIM gsm��Ȩ��USIM gsm��Ȩ��Э��27.007����cgla����
        SIM gsm��Ȩʱ��P2����Ϊ0���ο�Э��11.11 9.2.16
        USIM gsm��Ȩʱ��P2��������bitΪ0���ο�Э��31.102 7.1.2
        */
        if ((CMD_INS_AUTHENTICATE == gstUSIMMAPDU.aucAPDU[INS])
            &&(0 == (gstUSIMMAPDU.aucAPDU[P2] & 0x07)))
        {
            USIMM_ERROR_LOG("USIMM_ChannelCmdParaCheck: The authenticate operation is forbided.");

            return VOS_ERR;
        }
    }

    /* ���INS�ֽ��Ƿ�Ϊ"6X"����"9X"��������򷵻�ʧ��.�˴������Э���׼��7816-4��ȷ�涨insΪ"6X","9X"�Ƿ� */
    if ((0x60 == (gstUSIMMAPDU.aucAPDU[INS]&0xf0))
        || (0x90 == (gstUSIMMAPDU.aucAPDU[INS]&0xf0)))
    {
        USIMM_ERROR_LOG("USIMM_ChannelCmdParaCheck: The operation is not supportable.");

        return VOS_ERR;
    }

    /* �˴�������ǰ�ڷ�������cgla�����߼�ͨ��ʱ�����·���������:
       1 ��manage�򿪻�ر�ͨ��
       2 select aid���� P1Ϊ04ָ����select by df name
       3 fetchָ��߼�ͨ���ظ�91XX��Ҫ�ڻ���ͨ����fetch���μ�Э��102.221 7.4.2.1
    */
    if (VOS_TRUE == g_stUsimmFeatureCfg.unCfg.stFeatureCfg.ulCglaInsCheckFlg)
    {
        if((CMD_INS_MANAGE_CHANNEL == gstUSIMMAPDU.aucAPDU[INS])
            || (CMD_INS_FETCH == gstUSIMMAPDU.aucAPDU[INS]))
        {
            USIMM_ERROR_LOG("USIMM_ChannelCmdParaCheck: The operation is not supportable.");

            return VOS_ERR;
        }
    }

    if (VOS_TRUE == g_stUsimmFeatureCfg.unCfg.stFeatureCfg.ulCglaSelectCheckFlg)
    {
        if ((CMD_INS_SELECT == gstUSIMMAPDU.aucAPDU[INS])
            && (USIMM_SELECT_BY_DF_NAME == gstUSIMMAPDU.aucAPDU[P1]))
        {
            USIMM_ERROR_LOG("USIMM_ChannelCmdParaCheck: The operation is not supportable.");

            return VOS_ERR;
        }
    }

    return VOS_OK;
}


VOS_UINT32 USIMM_CloseChannelHandle(USIMM_CMDHEADER_REQ_STRU *pMsg)
{
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucChannelId;
    USIMM_CLOSECHANNEL_REQ_STRU        *pstMsg;

    pstMsg = (USIMM_CLOSECHANNEL_REQ_STRU *)pMsg;

    if (VOS_FALSE == USIMM_IsCLEnable())
    {
        ulResult = USIMM_ApiParaCheck();

        if (VOS_OK != ulResult)
        {
            USIMM_WARNING_LOG("USIMM_CloseChannelHandle: USIMM_ApiParaCheck is Failed");/*��ӡ����*/

            USIMM_CloseChannelCnf(pstMsg->stMsgHeader.ulSenderPid,
                                  pstMsg->stMsgHeader.ulSendPara,
                                  TAF_ERR_SIM_FAIL,
                                  VOS_ERR);

            return ulResult; /*���غ���������Ϣ*/
        }
    }

    ucChannelId = USIMM_SearchCHCtrl(pstMsg->ulSessionID);

    /* ͨ���Ų������ */
    if ((0 == ucChannelId) || (USIMM_CHANNEL_NUM_MAX <= ucChannelId))
    {
        USIMM_ERROR_LOG("USIMM_CloseChannelHandle: ulSessionID is not correct");

        USIMM_CloseChannelCnf(pstMsg->stMsgHeader.ulSenderPid,
                              pstMsg->stMsgHeader.ulSendPara,
                              TAF_ERR_PARA_ERROR,
                              VOS_ERR);

        return VOS_ERR;
    }

    /* ȥ����ADF �ο�Э��102.221 8.5.3�ڣ���ֹӦ��ʱ���·�status֪ͨUICC��Ȼ��ͨ�����ַ�ʽ����Ӧ�ã�
     1 ��ͨ��������ѡ��һ���µ�Ӧ��
     2 ��ͨ����select��Ӧ�ã�p2��������ֹӦ��
     3 �ر�ͨ��
     �˴���Ϊ�ǹر��߼�ͨ�������ѡ��ʽ3
    */
    ulResult = USIMM_StatusByChannelID_APDU(ucChannelId, USIMM_STATUS_TERMINATION_CURAPP, USIMM_STATUS_NO_DATA_RETURNED, 0);

    if(VOS_OK != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_CloseChannelHandle: Terminate ADF Error");

        USIMM_CloseChannelCnf(pstMsg->stMsgHeader.ulSenderPid,
                              pstMsg->stMsgHeader.ulSendPara,
                              TAF_ERR_ERROR,
                              ulResult);

        return VOS_ERR;
    }

    ulResult = USIMM_CheckSW(&gstUSIMMAPDU);

    if (USIMM_SW_OK != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_CloseChannelHandle: USIMM_CheckSW failed.");
    }

    /* �ر��߼�ͨ�� */
    ulResult = USIMM_CloseChannel(ucChannelId);

    if (VOS_OK != ulResult)
    {
        USIMM_CloseChannelCnf(pstMsg->stMsgHeader.ulSenderPid,
                              pstMsg->stMsgHeader.ulSendPara,
                              TAF_ERR_ERROR,
                              ulResult);

        return VOS_ERR;
    }

    /*lint -e534*/
    VOS_MemSet(&g_astUSIMMChCtrl[ucChannelId], 0, sizeof(USIMM_CHANNEL_INFO_STRU));
    /*lint +e534*/

    if (VOS_TRUE == g_stUsimmFeatureCfg.unCfg.stFeatureCfg.ulAIDFCPSave)
    {
        g_astUSIMMChAIDFCP[ucChannelId].ulAIDFCPLen = VOS_NULL;
    }

    USIMM_CloseChannelCnf(pstMsg->stMsgHeader.ulSenderPid,
                          pstMsg->stMsgHeader.ulSendPara,
                          TAF_ERR_NO_ERROR,
                          VOS_OK);

    return VOS_OK;
}
VOS_UINT32 USIMM_OpenChannelForCSIM(VOS_VOID)
{
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucChannelId = VOS_NULL_BYTE;
    VOS_UINT32                          ulSessionId = VOS_NULL_DWORD;
    USIMM_APDU_ST                       stApduInfo = {0};
    VOS_UINT32                          ulCSIMExistFlag;
    VOS_UINT8                           aucCsimAid[USIMM_AID_LEN_MAX];
    VOS_UINT32                          ulCsimAidLen;
    VOS_UINT32                          ulUSIMExistFlag;
    VOS_UINT8                           aucUsimAid[USIMM_AID_LEN_MAX];
    VOS_UINT32                          ulUsimAidLen;

    (VOS_VOID)VOS_MemSet(aucCsimAid, 0, sizeof(aucCsimAid));
    (VOS_VOID)VOS_MemSet(aucUsimAid, 0, sizeof(aucUsimAid));

    /* ��CL��ʽ��Ҫ���߼�ͨ�� */
    if (VOS_FALSE == USIMM_IsCLEnable())
    {
        return VOS_OK;
    }

    ulCSIMExistFlag = USIMM_GetAid(USIMM_AID_TYPE_CSIM, &ulCsimAidLen, aucCsimAid);
    ulUSIMExistFlag = USIMM_GetAid(USIMM_AID_TYPE_USIM, &ulUsimAidLen, aucUsimAid);

    /* ֻ��UICC˫ģ����Ҫ�����߼�ͨ�� */
    if ((VOS_OK != ulCSIMExistFlag)
     || (VOS_OK != ulUSIMExistFlag))
    {
        return VOS_OK;
    }

    /* �жϵ�ǰ�Ƿ���ʣ��ͨ�� */
    if (VOS_OK != USIMM_SearchCHFree())
    {
        USIMM_ERROR_LOG("USIMM_OpenChannelHandle: The logic channel is full.");

        return VOS_ERR;
    }

    /* һ��ͨ��ʹ����ֻ�����һ��ͨ�������֮ǰû�д򿪣����·�MANAGE CHANNEL�����ͨ�� */
    ulResult = USIMM_OpenChannel(&ucChannelId, &ulSessionId);

    if (VOS_OK != ulResult)
    {
        return VOS_ERR;
    }

    if (VOS_TRUE == g_stUsimmFeatureCfg.unCfg.stFeatureCfg.ulAidLenCheckFlg)
    {
        if (ulCsimAidLen < USIMM_AID_LEN_MIN)
        {
            USIMM_ERROR_LOG("USIMM_OpenChannelForCSIM: the length of AID is error");

            (VOS_VOID)USIMM_CloseChannel(ucChannelId);

            return VOS_ERR;
        }
    }

    stApduInfo.aucAPDU[CLA] = USIMM_USIM_CLA;

    stApduInfo.aucAPDU[P1] = USIMM_SELECT_BY_DF_NAME;

    stApduInfo.aucAPDU[P2] = USIMM_SELECT_RETURN_FCP_TEMPLATE;

    stApduInfo.aucAPDU[P3] = (VOS_UINT8)ulCsimAidLen;

    (VOS_VOID)VOS_MemCpy(stApduInfo.aucSendBuf, aucCsimAid, ulCsimAidLen);

    /* �·�����AID�������ݵ�Ԫ,cla�ֶ�Ӧ���ڴ򿪵��߼�ͨ���� */
    ulResult = USIMM_SelectFileByChannelID_APDU(ucChannelId, &stApduInfo);

    if (VOS_OK != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_OpenChannelHandle: Select ADF Error");

        (VOS_VOID)USIMM_CloseChannel(ucChannelId);

        return VOS_ERR;
    }

    ulResult = USIMM_CheckSW(&stApduInfo);

    if ((USIMM_SW_OK != ulResult) && (USIMM_SW_CMD_REMAINTIME != ulResult))
    {
        USIMM_ERROR_LOG("USIMM_OpenChannelHandle: USIMM_CheckSW failed.");

        (VOS_VOID)USIMM_CloseChannel(ucChannelId);

        return VOS_ERR;
    }

    if (VOS_TRUE == g_stUsimmFeatureCfg.unCfg.stFeatureCfg.ulAIDFCPSave)
    {
        (VOS_VOID)VOS_MemCpy(g_astUSIMMChAIDFCP[ucChannelId].aucADFFcp, stApduInfo.aucRecvBuf, stApduInfo.ulRecDataLen);

        g_astUSIMMChAIDFCP[ucChannelId].ulAIDFCPLen = stApduInfo.ulRecDataLen;
    }

    g_astUSIMMChCtrl[ucChannelId].ulSessionId = ulSessionId;
    g_astUSIMMChCtrl[ucChannelId].ulChanNum   = ucChannelId;
    g_astUSIMMChCtrl[ucChannelId].ulAIDLen    = ulCsimAidLen;
    (VOS_VOID)VOS_MemCpy(g_astUSIMMChCtrl[ucChannelId].aucADFName, aucCsimAid, ulCsimAidLen);

    g_astUSIMMChGetRsp[ucChannelId].ulRspLen  = 0;

    g_ulCsimSessionId = ulSessionId;

    return VOS_OK;
}
VOS_UINT32 USIMM_CheckAIDFcp(VOS_UINT32                   ulChannelId,
                                        USIMM_APDU_ST               *pstUsimmApdu,
                                        USIMM_SENDTPDU_CNFINFO_STRU *pstDataCnf)
{
    if (VOS_FALSE == g_stUsimmFeatureCfg.unCfg.stFeatureCfg.ulAIDFCPSave)
    {
        return VOS_ERR;
    }

    if (VOS_NULL == g_astUSIMMChAIDFCP[ulChannelId].ulAIDFCPLen)
    {
        return VOS_ERR;
    }

    if (0xA4 == pstUsimmApdu->aucAPDU[INS])
    {
        if (VOS_OK == VOS_MemCmp(g_astUSIMMChCtrl[ulChannelId].aucADFName,
                                pstUsimmApdu->aucSendBuf,
                                pstUsimmApdu->aucAPDU[P3]))
        {
            pstDataCnf->pucData     = g_astUSIMMChAIDFCP[ulChannelId].aucADFFcp;
            pstDataCnf->ucSw1       = 0x90;
            pstDataCnf->ucSw2       = 0x00;
            pstDataCnf->usDataLen   = (VOS_UINT16)g_astUSIMMChAIDFCP[ulChannelId].ulAIDFCPLen;

            return VOS_OK;
        }
    }

    g_astUSIMMChAIDFCP[ulChannelId].ulAIDFCPLen = VOS_NULL;

    return VOS_ERR;
}


VOS_UINT32 USIMM_AccessChannelHandle(USIMM_MsgBlock *pMsg)
{
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucChannelId;
    USIMM_ACCESS_CHANNEL_REQ_STRU      *pstMsg;
    USIMM_SENDTPDU_CNFINFO_STRU         stDataCnf = {0};

    pstMsg = (USIMM_ACCESS_CHANNEL_REQ_STRU *)pMsg;

    stDataCnf.pucTPDUHead = pstMsg->aucData;

    ucChannelId = USIMM_SearchCHCtrl(pstMsg->ulSessionID);

    /* ͨ���Ų������ */
    if ((0 == ucChannelId) || (USIMM_CHANNEL_NUM_MAX <= ucChannelId))
    {
        USIMM_ERROR_LOG("USIMM_AccessChannelHandle: The channel ID is too big.");

        USIMM_SendTPDUCnf(pstMsg->ulSenderPid,
                          pstMsg->ulSendPara,
                          VOS_ERR,
                          VOS_ERR,
                          &stDataCnf,
                          VOS_NULL_PTR);

        return VOS_ERR;
    }

    /* GetResponseѡ��ӻ������ж�ȡ */
    if ((CMD_INS_GET_RESPONSE == pstMsg->aucData[INS])
        &&(0 != g_astUSIMMChGetRsp[ucChannelId].ulRspLen))
    {
        stDataCnf.usDataLen =   (VOS_UINT16)g_astUSIMMChGetRsp[ucChannelId].ulRspLen;
        stDataCnf.pucData   =   g_astUSIMMChGetRsp[ucChannelId].aucRspContent;
        stDataCnf.ucSw1     =   0x90;
        stDataCnf.ucSw2     =   0x00;

        g_astUSIMMChGetRsp[ucChannelId].ulRspLen = 0;

        USIMM_SendTPDUCnf(pstMsg->ulSenderPid,
                          pstMsg->ulSendPara,
                          VOS_OK,
                          USIMM_SW_OK,
                          &stDataCnf,
                          VOS_NULL_PTR);

        return USIMM_SW_OK;
    }

    g_astUSIMMChGetRsp[ucChannelId].ulRspLen = 0;

    /* ��ϳɱ�׼��ʽ */
    if (VOS_OK != USIMM_FormatStandardApdu(pstMsg->aucData, (VOS_UINT16)pstMsg->ulDataLen, &gstUSIMMAPDU))
    {
        USIMM_ERROR_LOG("USIMM_AccessChannelHandle: The USIMM_FormatStandardApdu Return Error");

        USIMM_SendTPDUCnf(pstMsg->ulSenderPid,
                          pstMsg->ulSendPara,
                          VOS_ERR,
                          VOS_ERR,
                          &stDataCnf,
                          VOS_NULL_PTR);

        return VOS_ERR;
    }

    if (VOS_OK != USIMM_ChannelCmdParaCheck())
    {
        USIMM_ERROR_LOG("USIMM_AccessChannelHandle: The authenticate operation is forbided.");

        USIMM_SendTPDUCnf(pstMsg->ulSenderPid,
                          pstMsg->ulSendPara,
                          VOS_ERR,
                          VOS_ERR,
                          &stDataCnf,
                          VOS_NULL_PTR);

        return VOS_ERR;
    }

    if (VOS_OK == USIMM_CheckAIDFcp(ucChannelId, &gstUSIMMAPDU, &stDataCnf))
    {
        USIMM_SendTPDUCnf(pstMsg->ulSenderPid,
                          pstMsg->ulSendPara,
                          VOS_OK,
                          VOS_OK,
                          &stDataCnf,
                          VOS_NULL_PTR);

        return VOS_OK;
    }

    /* �Ե���bit�������� */
    gstUSIMMAPDU.aucAPDU[CLA] = (gstUSIMMAPDU.aucAPDU[CLA] & 0xFC)|ucChannelId;

    /* ������·�㺯�� */
    ulResult = USIMM_CglaDLHandle(&gstUSIMMAPDU);

    if(VOS_OK != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_AccessChannelHandle: The operation is not supportable.");

        USIMM_SendTPDUCnf(pstMsg->ulSenderPid,
                          pstMsg->ulSendPara,
                          VOS_ERR,
                          ulResult,
                          &stDataCnf,
                          VOS_NULL_PTR);

        return VOS_ERR;
    }

    /* ���緢����Warning��������л��洦�� */
    if ((VOS_TRUE == gstUSIMMDLControl.bSendRep)
        && (USIMM_SW_WARNING == gstUSIMMAPDU.ucResult))
    {
        stDataCnf.ucSw1                     =   gstUSIMMAPDU.ucApduSW1;
        stDataCnf.ucSw2                     =   gstUSIMMAPDU.ucApduSW2;

        if (VOS_TRUE == g_stUsimmFeatureCfg.unCfg.stFeatureCfg.ulWarningDataInd)
        {
            g_astUSIMMChGetRsp[ucChannelId].ulRspLen= 0;
            stDataCnf.usDataLen                     = (VOS_UINT16)gstUSIMMAPDU.ulRecDataLen;
            stDataCnf.pucData                       = gstUSIMMAPDU.aucRecvBuf;
        }
        else
        {
            stDataCnf.usDataLen                         =   0;

            /* �����߼�ͨ����GetResponse��� */
            g_astUSIMMChGetRsp[ucChannelId].ulRspLen    =   gstUSIMMAPDU.ulRecDataLen;

            /*lint -e534*/
            VOS_MemCpy(g_astUSIMMChGetRsp[ucChannelId].aucRspContent,
                        gstUSIMMAPDU.aucRecvBuf,
                        gstUSIMMAPDU.ulRecDataLen);
            /*lint +e534*/
        }
    }
    else
    {
        stDataCnf.usDataLen                 =   (VOS_UINT16)gstUSIMMAPDU.ulRecDataLen;
        stDataCnf.pucData                   =   gstUSIMMAPDU.aucRecvBuf;
        stDataCnf.ucSw1                     =   gstUSIMMAPDU.ucSW1;
        stDataCnf.ucSw2                     =   gstUSIMMAPDU.ucSW2;
    }

    /* �˴�����check sw����Ϊ���߼�ͨ���ϻظ�91XX�������ڻ���ͨ����fetch */
    ulResult = USIMM_CheckSW(&gstUSIMMAPDU);

    /* MANAGE������д�ӡ */
    if(CMD_INS_MANAGE_CHANNEL == gstUSIMMAPDU.aucAPDU[INS])
    {
        USIMM_INFO_LOG("USIMM_AccessChannelHandle: manage command send by cgla.");
    }

    /* check sw���۽���Ƿ�ok������at�ظ�ok��Ϊ�˽�sw����app */
    USIMM_SendTPDUCnf(pstMsg->ulSenderPid,
                      pstMsg->ulSendPara,
                      VOS_OK,
                      ulResult,
                      &stDataCnf,
                      VOS_NULL_PTR);

    return ulResult;
}


VOS_UINT32 USIMM_CardStatusHandle(USIMM_CMDHEADER_REQ_STRU *pstMsg)
{
    USIMM_CARD_STATUS_IND_STRU         *pstCardStatus;

    pstCardStatus = (USIMM_CARD_STATUS_IND_STRU *)pstMsg;

    /* ��ǰ���п�������յ����γ���Ϣ */
    if ((USIMM_CARDSTATUS_IND_PLUGOUT == pstCardStatus->ulCardStatus)
       && (USIMM_CARD_SERVIC_ABSENT != gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardService))
    {
        return USIMM_DeactiveRealCard((USIMM_MsgBlock *)pstMsg);
    }
    else if ((VOS_TRUE == USIMM_IsCLEnable())&&(USIMM_CARDSTATUS_IND_PLUGOUT == pstCardStatus->ulCardStatus))
    {
        return USIMM_DeactiveRealCard((USIMM_MsgBlock *)pstMsg);
    }
    /* ��ǰ���޿�������յ���������Ϣ */
    else if ((USIMM_CARDSTATUS_IND_PLUGIN == pstCardStatus->ulCardStatus)
       && (USIMM_CARD_SERVIC_ABSENT == gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardService))
    {
        return USIMM_ActiveCardReq(WUEPS_PID_USIM);
    }
    else
    {
        return VOS_OK;
    }
}

/*****************************************************************************
�� �� ��  :USIMM_SendTPDUHandle
��������  :����ͨ���·�������Ϣ����
�������  :USIMM_MsgBlock: API�·���Ϣ����
�������  :��
�� �� ֵ  :VOS_ERR
           VOS_OK
�޶���¼  :
1. ��    ��   : 2014��1��15��
   ��    ��   : zhuli
   �޸�����   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_SendTPDUHandle(USIMM_MsgBlock *pMsg)
{
    VOS_UINT32                          ulResult;
    USIMM_SENDTPDU_REQ_STRU             *pstMsg;
    USIMM_SENDTPDU_CNFINFO_STRU         stDataCnf;
    USIMM_APDU_ST                       stUSIMMAPDU;

    pstMsg = (USIMM_SENDTPDU_REQ_STRU *)pMsg;

    /*lint -e534*/
    VOS_MemSet(&stDataCnf, 0, sizeof(stDataCnf));

    VOS_MemSet(&stUSIMMAPDU, 0, sizeof(USIMM_APDU_ST));

    VOS_MemCpy(stUSIMMAPDU.aucAPDU, pstMsg->aucTPDUHead, sizeof(pstMsg->aucTPDUHead));
    /*lint +e534*/

    stDataCnf.pucTPDUHead = pstMsg->aucTPDUHead;

    if (VOS_NULL == pstMsg->ulTPDUDataLen)
    {
        stUSIMMAPDU.ulLcValue = 0;
        stUSIMMAPDU.ulLeValue = stUSIMMAPDU.aucAPDU[P3];
    }
    else
    {
        stUSIMMAPDU.ulLcValue = pstMsg->ulTPDUDataLen;
        stUSIMMAPDU.ulLeValue = 0;

        /*lint -e534*/
        VOS_MemCpy(stUSIMMAPDU.aucSendBuf, pstMsg->aucTPDUData, pstMsg->ulTPDUDataLen);
        /*lint +e534*/
    }

    ulResult = USIMM_CglaDLHandle(&stUSIMMAPDU);

    if(VOS_OK != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_SendTPDUHandle: USIMM_CglaDLHandle Return Failed.");

        USIMM_SendTPDUCnf(pstMsg->ulSenderPid,
                          pstMsg->ulSendPara,
                          VOS_ERR,
                          ulResult,
                          &stDataCnf,
                          VOS_NULL_PTR);

        return VOS_ERR;
    }

    stDataCnf.usDataLen                 =   (VOS_UINT16)stUSIMMAPDU.ulRecDataLen;
    stDataCnf.pucData                   =   stUSIMMAPDU.aucRecvBuf;
    stDataCnf.ucSw1                     =   stUSIMMAPDU.ucSW1;
    stDataCnf.ucSw2                     =   stUSIMMAPDU.ucSW2;

    /* �˴�����check sw����Ϊ���߼�ͨ���ϻظ�91XX�������ڻ���ͨ����fetch */
    ulResult = USIMM_CheckSW(&stUSIMMAPDU);

    if (VOS_OK != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_SendTPDUHandle: USIMM_CglaDLHandle Return Failed.");
    }

    /* check sw���۽���Ƿ�ok������at�ظ�ok��Ϊ�˽�sw����app */
    USIMM_SendTPDUCnf(pstMsg->ulSenderPid,
                      pstMsg->ulSendPara,
                      VOS_OK,
                      ulResult,
                      &stDataCnf,
                      VOS_NULL_PTR);

    return ulResult;
}

/*lint -e732*/

VOS_UINT32 USIMM_ChangeToOldApp(
    VOS_UINT32                          ulSenderPID,
    USIMM_FILEPATH_INFO_STRU           *pstFilePath,
    USIMM_CARDAPP_ENUM_UINT32           enNewAPP,
    VOS_UINT16                          usDFID,
    USIMM_APP_TYPE_ENUM_UINT32         *penOldApp
)
{
    VOS_UINT32                          ulGSMATTResult;
    VOS_UINT32                          ulUSIMATTResult;

    ulUSIMATTResult = VOS_MemCmp(USIMM_ATTUSIM_STR, pstFilePath->acPath, (VOS_UINT32)VOS_StrLen(USIMM_ATTUSIM_STR));

    ulGSMATTResult  = VOS_MemCmp(USIMM_ATTGSM_STR, pstFilePath->acPath, (VOS_UINT32)VOS_StrLen(USIMM_ATTGSM_STR));

    if (MAPS_PB_PID == ulSenderPID)
    {
        *penOldApp = USIMM_PB_APP;
    }
    else if (USIMM_IMS_APP == enNewAPP)
    {
        *penOldApp = USIMM_ISIM_APP;
    }
#if (FEATURE_UE_MODE_CDMA == FEATURE_ON)
    else if (USIMM_CDMA_APP == enNewAPP)
    {
        *penOldApp = USIMM_3GPP2_APP;
    }
#endif
    else if ((VOS_OK == ulUSIMATTResult) || (VOS_OK == ulGSMATTResult))
    {
        *penOldApp = USIMM_ATT_APP;
    }
    else if (DFGSM == usDFID)
    {
        *penOldApp = USIMM_GSM_APP;
    }
    else if ((USIMM_GUTL_APP == enNewAPP)&&(ADF == usDFID))
    {
        *penOldApp = USIMM_UMTS_APP;
    }
    else
    {
        *penOldApp = USIMM_UNLIMIT_APP;
    }

    return VOS_OK;
}
/*lint +e732*/


VOS_UINT32 USIMM_Read_OpenSpeedFile(USIMM_READFILE_REQ_STRU *pstMsg, VOS_UINT16 usFileID)
{
    VOS_UINT32                  ulResult;
    VOS_UINT8                   aucContent[250];
    VOS_UINT32                  i;
    USIMM_GETCNF_INFO_STRU      stFileInfo = {0};
    USIMM_OPENSPEED_FILE_TO_NVID ausNVId[] = {
                                {0x6F62, USIMM_EF6F62Len, en_NV_Item_EF6F62},
                                {0x6F7B, USIMM_EF6F7BLen, en_NV_Item_EF6F7B},
                                {0x6F60, USIMM_EF6F60Len, en_NV_Item_EF6F60},
                                {0x6F61, USIMM_EF6F61Len, en_NV_Item_EF6F61},
                                {0x6F31, USIMM_EF6F31Len, en_NV_Item_EF6F31},
                                {0x6FAD, USIMM_EF6FADLen, en_NV_Item_EF6FAD},
                                {0x6F38, USIMM_EF6F38Len, en_NV_Item_EF6F38},
                                {0x6F7E, USIMM_EF6F7ELen, en_NV_Item_EF6F7E},
                                {0x6F73, USIMM_EF6F73Len, en_NV_Item_EF6F73},
                                {0x6F53, USIMM_EF6F53Len, en_NV_Item_EF6F53},
                                {0x6F07, USIMM_EF6F07Len, en_NV_Item_EF6F07},
                                {0x6F08, USIMM_EF6F08Len, en_NV_Item_EF6F08},
                                {0x6F09, USIMM_EF6F09Len, en_NV_Item_EF6F09},
                                {0x6F20, USIMM_EF6F20Len, en_NV_Item_EF6F20},
                                {0x6F52, USIMM_EF6F52Len, en_NV_Item_EF6F52},
                                {0x4F20, USIMM_EF4F20Len, en_NV_Item_EF4F20},
                                {0x4F52, USIMM_EF4F52Len, en_NV_Item_EF4F52},
                                {0x6FB7, USIMM_EF6FB7Len, en_NV_Item_EF6FB7},
                                {0x6F78, USIMM_EF6F78Len, en_NV_Item_EF6F78},
                                {0x6F5B, USIMM_EF6F5BLen, en_NV_Item_EF6F5B},
                                {0x6F5C, USIMM_EF6F5CLen, en_NV_Item_EF6F5C},
                                {0x6FC4, USIMM_EF6FC4Len, en_NV_Item_EF6FC4},
                                {0x6F74, USIMM_EF6F74Len, en_NV_Item_EF6F74}
                            };

    stFileInfo.usEfId       = usFileID;
    stFileInfo.ucRecordNum  = 0;
    stFileInfo.ucTotalNum   = 0;

    for(i=0; i<ARRAYSIZE(ausNVId); i++)
    {
        if(ausNVId[i].usFileId == usFileID)
        {
            break;
        }
    }

    if(i >=  23)
    {
        USIMM_WARNING_LOG("USIMM_Read_OpenSpeedFile: The File is Not Exist in Flash");

        USIMM_GetFileCnf(pstMsg, USIMM_SW_MSGCHECK_ERROR, &stFileInfo);

        return VOS_ERR;
    }

    ulResult = NV_Read(ausNVId[i].enNVId, aucContent, ausNVId[i].usEfLen);

    if(NV_OK != ulResult)
    {
        USIMM_WARNING_LOG("USIMM_Read_OpenSpeedFile: Read NV is Failed");

        USIMM_GetFileCnf(pstMsg, USIMM_SW_MSGCHECK_ERROR, &stFileInfo);

        return VOS_ERR;
    }

    stFileInfo.usDataLen    = ausNVId[i].usEfLen;
    stFileInfo.usEfLen      = ausNVId[i].usEfLen;
    stFileInfo.pucEf        = aucContent;

    USIMM_GetFileCnf(pstMsg, USIMM_SW_OK, &stFileInfo);

    return VOS_OK;
}


VOS_UINT32 USIMM_ReadFileHandle(USIMM_CMDHEADER_REQ_STRU *pstMsgHeader)
{
    USIMM_READFILE_REQ_STRU     *pstMsg;
    USIMM_GETFILE_REQ_STRU      stOldMsg;
    VOS_UINT16                  usDFID;
    VOS_UINT16                  usSubDF;
    VOS_UINT16                  usEFID;
    VOS_UINT32                  ulResult;
    USIMM_GETCNF_INFO_STRU      stCnfInfo = {0};

    pstMsg = (USIMM_READFILE_REQ_STRU *)pstMsgHeader;

    if (VOS_OK != USIMM_GetFilePathFormStr(&pstMsg->stFilePath, &usDFID, &usSubDF, &usEFID))
    {
        USIMM_GetFileCnf(pstMsg, USIMM_SW_MSGCHECK_ERROR, &stCnfInfo);

        return VOS_ERR;
    }

    if (VOS_OK != USIMM_ChangeToOldApp(pstMsg->stMsgHeader.ulSenderPid,
                                        &pstMsg->stFilePath,
                                        pstMsg->stMsgHeader.enAppType,
                                        usDFID,
                                        &stOldMsg.enAppType))
    {
        USIMM_GetFileCnf(pstMsg, USIMM_SW_MSGCHECK_ERROR, &stCnfInfo);

        return VOS_ERR;
    }

    stOldMsg.ulSendPara = pstMsg->stMsgHeader.ulSendPara;

    stOldMsg.ucRecordNum= pstMsg->ucRecordNum;

    stOldMsg.usFileID   = usEFID;

    if (USIMM_OPENSPEEDENABLE == gulUSIMMOpenSpeed) /*���ٿ�������*/
    {
        ulResult = USIMM_Read_OpenSpeedFile(pstMsg, usEFID);
    }
    else if (VOS_OK != USIMM_ApiParaCheckSimple())
    {
        USIMM_GetFileCnf(pstMsg, USIMM_SW_MSGCHECK_ERROR, &stCnfInfo);

        return VOS_ERR;
    }
    else if ((USIMM_GSM_APP     == stOldMsg.enAppType)
              ||(USIMM_UMTS_APP == stOldMsg.enAppType)
              ||(USIMM_PB_APP   == stOldMsg.enAppType)
              ||(USIMM_ATT_APP  == stOldMsg.enAppType)
              ||(USIMM_ISIM_APP == stOldMsg.enAppType)
              ||(USIMM_UNLIMIT_APP == stOldMsg.enAppType))
    {
        ulResult = USIMM_GetFileHandle(&stOldMsg, pstMsg);
    }
#if (FEATURE_UE_MODE_CDMA == FEATURE_ON)
    else if (USIMM_3GPP2_APP == stOldMsg.enAppType)
    {
        ulResult = USIMM_GetCdmaFileHandle((USIMM_MsgBlock*)&stOldMsg, pstMsg);
    }
#endif
    else
    {
        ulResult = VOS_ERR;
    }

    return ulResult;
}

VOS_UINT32 USIMM_UpdateFileHandle(USIMM_CMDHEADER_REQ_STRU *pstMsgHeader)
{
    USIMM_UPDATEFILE_REQ_STRU          *pstNewMsg;
    USIMM_SETFILE_REQ_STRU             *pstOldMsg;
    VOS_UINT16                          usDFID;
    VOS_UINT16                          usSubDF;
    VOS_UINT16                          usEFID;
    VOS_UINT32                          ulResult;
    USIMM_SETCNF_INFO_STRU              stCnfInfo = {0};

    pstNewMsg = (USIMM_UPDATEFILE_REQ_STRU *)pstMsgHeader;

    if (VOS_OK != USIMM_ApiParaCheckSimple())
    {
        USIMM_SetFileCnf(pstNewMsg, USIMM_SW_MSGCHECK_ERROR, &stCnfInfo);

        return VOS_ERR;
    }

    if (VOS_OK != USIMM_GetFilePathFormStr(&pstNewMsg->stFilePath, &usDFID, &usSubDF, &usEFID))
    {
        USIMM_SetFileCnf(pstNewMsg, USIMM_SW_MSGCHECK_ERROR, &stCnfInfo);

        return VOS_ERR;
    }

    pstOldMsg = (USIMM_SETFILE_REQ_STRU*)VOS_AllocMsg(WUEPS_PID_USIM,
                                                      (sizeof(USIMM_SETFILE_REQ_STRU) - VOS_MSG_HEAD_LENGTH + pstNewMsg->usDataLen));

    if (VOS_NULL_PTR == pstOldMsg)
    {
        return VOS_ERR;
    }

    stCnfInfo.usEfid        = usEFID;
    stCnfInfo.ucRecordNum   = pstNewMsg->ucRecordNum;
    stCnfInfo.usEFLen       = pstNewMsg->usDataLen;

    if (VOS_OK != USIMM_ChangeToOldApp(pstNewMsg->stMsgHeader.ulSenderPid,
                                       &pstNewMsg->stFilePath,
                                       pstNewMsg->stMsgHeader.enAppType,
                                       usDFID,
                                       &pstOldMsg->enAppType))
    {
        USIMM_SetFileCnf(pstNewMsg, USIMM_SW_MSGCHECK_ERROR, &stCnfInfo);

        /*lint -e534*/
        VOS_FreeMsg(WUEPS_PID_USIM, pstOldMsg);
        /*lint +e534*/

        return VOS_ERR;
    }

    pstOldMsg->ulSendPara   = pstNewMsg->stMsgHeader.ulSendPara;
    pstOldMsg->ucRecordNum  = pstNewMsg->ucRecordNum;
    pstOldMsg->usFileID     = usEFID;
    pstOldMsg->usDataLen    = pstNewMsg->usDataLen;
    pstOldMsg->ucRecordNum  = pstNewMsg->ucRecordNum;

    /*lint -e534*/
    VOS_MemCpy(pstOldMsg->aucContent, pstNewMsg->aucContent, pstNewMsg->usDataLen);
    /*lint +e534*/

    if ( (USIMM_GSM_APP     == pstOldMsg->enAppType)
        ||(USIMM_UMTS_APP   == pstOldMsg->enAppType)
        ||(USIMM_PB_APP     == pstOldMsg->enAppType)
        ||(USIMM_ATT_APP    == pstOldMsg->enAppType)
        ||(USIMM_ISIM_APP   == pstOldMsg->enAppType)
        ||(USIMM_UNLIMIT_APP== pstOldMsg->enAppType))
    {
        ulResult = USIMM_SetFileHandle((USIMM_MsgBlock*)pstOldMsg, pstNewMsg);
    }
#if (FEATURE_UE_MODE_CDMA == FEATURE_ON)
    else if (USIMM_3GPP2_APP == pstOldMsg->enAppType)
    {
        ulResult = USIMM_SetCdmaFileHandle((USIMM_MsgBlock*)pstOldMsg, pstNewMsg);
    }
#endif
    else
    {
        USIMM_SetFileCnf(pstNewMsg, USIMM_SW_MSGCHECK_ERROR, &stCnfInfo);

        ulResult = VOS_ERR;
    }

    /*lint -e534*/
    VOS_FreeMsg(WUEPS_PID_USIM, pstOldMsg);
    /*lint +e534*/

    return ulResult;
}



VOS_UINT32 USIMM_QueryFileHandle(USIMM_CMDHEADER_REQ_STRU *pstMsgHeader)
{
    USIMM_QUERYFILE_REQ_STRU    *pstNewMsg;
    VOS_UINT16                  usDFID;
    VOS_UINT16                  usSubDF;
    VOS_UINT16                  usEFID;
    USIMM_MAXRECORD_REQ_STRU    stOldMsg;
    USIMM_FILECNF_INFO_STRU     stCnfInfo = {0};

    pstNewMsg = (USIMM_QUERYFILE_REQ_STRU*)pstMsgHeader;

    if(USIMM_API_SUCCESS != USIMM_ApiParaCheck())
    {
        USIMM_MaxRecordNumCnf(pstNewMsg, USIMM_SW_MSGCHECK_ERROR, &stCnfInfo);

        return VOS_ERR; /*���غ���������Ϣ*/
    }

    if (VOS_OK != USIMM_GetFilePathFormStr(&pstNewMsg->stFilePath, &usDFID, &usSubDF, &usEFID))
    {
        USIMM_MaxRecordNumCnf(pstNewMsg, USIMM_SW_MSGCHECK_ERROR, &stCnfInfo);

        return VOS_ERR;
    }

    if (VOS_OK != USIMM_ChangeToOldApp(pstNewMsg->stMsgHeader.ulSenderPid,
                                        &pstNewMsg->stFilePath,
                                        pstNewMsg->stMsgHeader.enAppType,
                                        usDFID,
                                        &stOldMsg.enAppType))
    {
        USIMM_MaxRecordNumCnf(pstNewMsg, USIMM_SW_MSGCHECK_ERROR, &stCnfInfo);

        return VOS_ERR;
    }

    stOldMsg.usEfId            = usEFID;

    /*lint -e534*/
    USIMM_GetMaxRecordNum((USIMM_MsgBlock*)&stOldMsg, pstNewMsg);
    /*lint +e534*/

    return VOS_OK;
}

VOS_UINT32 USIMM_SearchFileHandle(USIMM_CMDHEADER_REQ_STRU *pstMsgHeader)
{
    USIMM_SEARCHFILE_REQ_STRU   *pstNewMsg;
    USIMM_SEARCH_REQ_STRU       stOldMsg;
    VOS_UINT16                  usDFID;
    VOS_UINT16                  usSubDF;
    VOS_UINT16                  usEFID;
    USIMM_SEARCHCNF_INFO_STRU   stCnfInfo = {0};

    pstNewMsg = (USIMM_SEARCHFILE_REQ_STRU *)pstMsgHeader;

    if (VOS_OK != USIMM_ApiParaCheckSimple())
    {
        USIMM_SearchHandleCnf(pstNewMsg, USIMM_SW_MSGCHECK_ERROR, &stCnfInfo);

        return VOS_ERR;
    }

    if (VOS_OK != USIMM_GetFilePathFormStr(&pstNewMsg->stFilePath, &usDFID, &usSubDF, &usEFID))
    {
        USIMM_SearchHandleCnf(pstNewMsg, USIMM_SW_MSGCHECK_ERROR, &stCnfInfo);

        return VOS_ERR;
    }

    stCnfInfo.usEfid        = usEFID;

    if (VOS_OK != USIMM_ChangeToOldApp(pstNewMsg->stMsgHeader.ulSenderPid,
                                        &pstNewMsg->stFilePath,
                                        pstNewMsg->stMsgHeader.enAppType,
                                        usDFID,
                                        &stOldMsg.enAppType))
    {
        USIMM_SearchHandleCnf(pstNewMsg, USIMM_SW_MSGCHECK_ERROR, &stCnfInfo);

        return VOS_ERR;
    }

    stOldMsg.usEfId       = usEFID;

    stOldMsg.ucLen        = (VOS_UINT8)pstNewMsg->ulDataLen;

    /*lint -e534*/
    VOS_MemCpy(stOldMsg.aucContent, pstNewMsg->aucData, pstNewMsg->ulDataLen);
    /*lint +e534*/

    (VOS_VOID)USIMM_SearchHandle(&stOldMsg, pstNewMsg);

    return VOS_OK;
}


VOS_UINT32 USIMM_SetSPBFileHandle(USIMM_CMDHEADER_REQ_STRU *pstMsgHeader)
{
    VOS_UINT32                  i;
    USIMM_SETMUTILFILE_REQ_STRU *pstMsg;
    VOS_UINT32                  ulResult;

    pstMsg = (USIMM_SETMUTILFILE_REQ_STRU *)pstMsgHeader;

    ulResult = USIMM_ApiParaCheck();

    if(USIMM_API_SUCCESS != ulResult)
    {
        USIMM_WARNING_LOG("USIMM_SetSPBFileReq: USIMM_ApiParaCheck is Failed");/*��ӡ����*/

        USIMM_SetSPBFileCnf(pstMsg, USIMM_SW_MSGCHECK_ERROR);

        return ulResult; /*���غ���������Ϣ*/
    }

    for(i = 0; i < pstMsg->ulFileCount; i++)
    {
        /* ѡ��绰���ļ�, �绰���ļ�Ϊ��¼�ļ�����˲���Ҫ����FCP */
        if (VOS_OK != USIMM_SelectFile(USIMM_PB_APP, USIMM_NO_NEED_FCP, 1, &pstMsg->stFileData[i].usFileID))
        {
            USIMM_SetSPBFileCnf(pstMsg, USIMM_SW_NOFILE_SELECT);

            return VOS_ERR;
        }

        ulResult = USIMM_UpdateFile(USIMM_EFSTRUCTURE_FIXED,
                                    pstMsg->stFileData[i].ucRecordNum,
                                    pstMsg->stFileData[i].usDataLen,
                                    pstMsg->stFileData[i].aucContent);
        if (VOS_OK != ulResult)
        {
            USIMM_SetSPBFileCnf(pstMsg, USIMM_SW_DOWNLOAD_ERROR);

            return VOS_ERR;
        }
    }

    USIMM_SetSPBFileCnf(pstMsg, USIMM_SW_OK);

    return VOS_OK;
}
VOS_UINT32 USIMM_SendTPDUDataHandle(USIMM_CMDHEADER_REQ_STRU *pstMsgHeader)
{
    USIMM_SENDTPDUDATA_REQ_STRU         *pstNewMsg;
    VOS_UINT32                          ulDataLen;
    VOS_UINT32                          ulResult;

    if(VOS_TRUE == USIMM_VsimIsActive())    /*vSIM���ܴ�*/
    {
        USIMM_WARNING_LOG("USIMM_GenericAccessReq: The vSIM is Open");

        return USIMM_API_NOTAVAILABLE;
    }

    pstNewMsg = (USIMM_SENDTPDUDATA_REQ_STRU*)pstMsgHeader;

    ulDataLen = pstNewMsg->stTPDUData.usDataLen + USIMM_TPDU_HEAD_LEN;

    if ((SI_PIH_EVENT_GENERIC_ACCESS_CNF == SI_PIH_EVENT_TYPE(pstNewMsg->stMsgHeader.ulSendPara))
     || (USIMM_CSIM_SENDPARA == pstNewMsg->stMsgHeader.ulSendPara))
    {
        USIMM_GACCESS_REQ_STRU              stCsimMsg = {0};

        stCsimMsg.ulSenderPid = pstMsgHeader->ulSenderPid;
        stCsimMsg.ulSendPara  = pstMsgHeader->ulSendPara;

        (VOS_VOID)USIMM_StrToFilePath(&pstNewMsg->stFilePath, stCsimMsg.ausPath, &stCsimMsg.ulPathLen);

        stCsimMsg.usDataLen = (VOS_UINT16)ulDataLen;

        /*lint -e534*/
        VOS_MemCpy(stCsimMsg.aucContent, pstNewMsg->stTPDUData.aucTPDUHead, USIMM_TPDU_HEAD_LEN);

        VOS_MemCpy(stCsimMsg.aucContent + USIMM_TPDU_HEAD_LEN, pstNewMsg->stTPDUData.aucData, pstNewMsg->stTPDUData.usDataLen);
        /*lint +e534*/

        ulResult = USIMM_GAccessHandle((USIMM_MsgBlock*)&stCsimMsg);
    }
    else if ((SI_PIH_EVENT_ISDB_ACCESS_CNF == SI_PIH_EVENT_TYPE(pstNewMsg->stMsgHeader.ulSendPara))
          || (USIMM_ISDB_SENDPARA == pstNewMsg->stMsgHeader.ulSendPara))
    {
        USIMM_ISDB_ACCESS_REQ_STRU          stIsdbMsg = {0};

        stIsdbMsg.ulSenderPid = pstMsgHeader->ulSenderPid;
        stIsdbMsg.ulSendPara  = pstMsgHeader->ulSendPara;

        stIsdbMsg.usDataLen = (VOS_UINT16)ulDataLen;

        /*lint -e534*/
        VOS_MemCpy(stIsdbMsg.aucContent, pstNewMsg->stTPDUData.aucTPDUHead, USIMM_TPDU_HEAD_LEN);

        VOS_MemCpy(stIsdbMsg.aucContent + USIMM_TPDU_HEAD_LEN, pstNewMsg->stTPDUData.aucData, pstNewMsg->stTPDUData.usDataLen);

        ulResult = USIMM_IsdbAccessHandle((USIMM_MsgBlock*)&stIsdbMsg);
    }
    else if ((SI_PIH_EVENT_CGLA_SET_CNF == SI_PIH_EVENT_TYPE(pstNewMsg->stMsgHeader.ulSendPara))
          || (USIMM_CGLA_SENDPARA == pstNewMsg->stMsgHeader.ulSendPara))
    {
        USIMM_ACCESS_CHANNEL_REQ_STRU       stCglaMsg = {0};

        stCglaMsg.ulSenderPid = pstMsgHeader->ulSenderPid;
        stCglaMsg.ulSendPara  = pstMsgHeader->ulSendPara;

        stCglaMsg.ulSessionID = pstNewMsg->stMsgHeader.enAppType;
        stCglaMsg.ulDataLen   = ulDataLen;

        /*lint -e534*/
        VOS_MemCpy(stCglaMsg.aucData, pstNewMsg->stTPDUData.aucTPDUHead, USIMM_TPDU_HEAD_LEN);

        VOS_MemCpy(stCglaMsg.aucData + USIMM_TPDU_HEAD_LEN, pstNewMsg->stTPDUData.aucData, pstNewMsg->stTPDUData.usDataLen);
        /*lint +e534*/

        ulResult = USIMM_AccessChannelHandle((USIMM_MsgBlock*)&stCglaMsg);
    }
    else
    {
        USIMM_SENDTPDU_REQ_STRU             stTpduMsg = {0};

        stTpduMsg.ulSenderPid = pstMsgHeader->ulSenderPid;
        stTpduMsg.ulSendPara  = pstMsgHeader->ulSendPara;

        stTpduMsg.ulSessionID             = 0;
        stTpduMsg.stFilePath.ulPathLen    = 0;
        stTpduMsg.ulTPDUDataLen           = pstNewMsg->stTPDUData.usDataLen;

        /*lint -e534*/
        VOS_MemCpy(stTpduMsg.aucTPDUHead, pstNewMsg->stTPDUData.aucTPDUHead, USIMM_TPDU_HEAD_LEN);

        VOS_MemCpy(stTpduMsg.aucTPDUData, pstNewMsg->stTPDUData.aucData, pstNewMsg->stTPDUData.usDataLen);
        /*lint +e534*/

        ulResult = USIMM_SendTPDUHandle((USIMM_MsgBlock*)&stTpduMsg);
    }

    return ulResult;
}


static USIMMAPP_FUNCLIST_ST gastUSIMMAppFuncList[] =
{
    {USIMM_ACTIVECARD_REQ      , USIMM_InitCardHandle},
    {USIMM_INITCONTINUE_REQ    , USIMM_InitCardOptionalFile},
    {USIMM_PROTECTRESET_REQ    , USIMM_ProtectReset},
    {USIMM_DEACTIVECARD_REQ    , USIMM_DeactiveCardHandle},
    {USIMM_AUTHENTICATION_REQ  , USIMM_AuthenticationHandle},
    {USIMM_PINHANDLE_REQ       , USIMM_PINHandle},
    {USIMM_UPDATEFILE_REQ      , USIMM_UpdateFileHandle},
    {USIMM_READFILE_REQ        , USIMM_ReadFileHandle},
    {USIMM_QUERYFILE_REQ       , USIMM_QueryFileHandle},
    {USIMM_STATUSCMD_REQ       , USIMM_StatusHandle},
    {USIMM_SEARCHFILE_REQ      , USIMM_SearchFileHandle},
    {USIMM_FBDNPROCESS_REQ     , USIMM_FDNHandle},
    {USIMM_OPENCHANNEL_REQ     , USIMM_OpenChannelHandle},
    {USIMM_CLOSECHANNEL_REQ    , USIMM_CloseChannelHandle},
    {USIMM_SENDTPDUDATA_REQ    , USIMM_SendTPDUDataHandle},
    {USIMM_STKTERMINALRSP_REQ  , USIMM_SAT_TerminalResopnse},
    {USIMM_STKENVELOPE_REQ     , USIMM_SAT_Envelope},
    {USIMM_STKREFRESH_REQ      , USIMM_RefreshHandle},
    {USIMM_PBINIT_STATUS_IND   , USIMM_PBInitStatusIndHandle},
    {USIMM_RACCESS_REQ         , USIMM_RAccessHandle},
    {USIMM_SETMUTILFILE_REQ    , USIMM_SetSPBFileHandle},
    {USIMM_CARD_INOUT_IND      , USIMM_CardInOutHandle},
    {USIMM_CARDSTATUS_CB_IND   , USIMM_CardStatusHandle},
    {USIMM_ACTIVEISIM_REQ      , USIMM_InitIsimHandle},
#if (FEATURE_UE_MODE_CDMA == FEATURE_ON)
    {USIMM_BSCHALLENGE_REQ     , USIMM_BSChallengeHandle},
    {USIMM_GENERATE_KEYVPM_REQ , USIMM_GenerateKeyVpmHandle},
    {USIMM_MAMAGESSD_REQ       , USIMM_ManageSsdHandle},
#endif
};


VOS_VOID USIMM_ISIMStateChangeWithUsim(VOS_VOID)
{
    if (USIMM_CARD_STATE_CHANGED == gastUSIMMCardAppInfo[USIMM_UICC_USIM].enStateChange)
    {
        /*lint -e534*/
        USIMM_InitIsimHandle(VOS_NULL_PTR);
        /*lint +e534*/

        if ((USIMM_CARD_USIM == gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardType)&&(VOS_TRUE == gulUsimSupportIMS))
        {
            gastUSIMMCardAppInfo[USIMM_UICC_ISIM].enCardService = gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardService;
            gastUSIMMCardAppInfo[USIMM_UICC_ISIM].enStateChange = USIMM_CARD_STATE_CHANGED;
        }
    }

    return;
}


VOS_VOID USIMM_CardStateChangeProc(VOS_VOID)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulFlag = VOS_FALSE;

    /* �ж�ISIM��״̬�Ƿ�Ҫ����USIM�仯 */
    USIMM_ISIMStateChangeWithUsim();

    for(i = 0; i < USIMM_UICC_BUTT; i++)
    {
        if (USIMM_CARD_STATE_CHANGED == gastUSIMMCardAppInfo[i].enStateChange)
        {
            gastUSIMMCardAppInfo[i].enStateChange = USIMM_CARD_STATE_NOCHANGE;

            ulFlag = VOS_TRUE;
        }
    }

    if (VOS_TRUE == ulFlag)
    {
        USIMM_CardStatusInd(MAPS_PIH_PID);
    }

    return;
}

#if(FEATURE_ON == FEATURE_PTM)
VOS_VOID USIMM_ErrorLogProc(USIMM_CMDHEADER_REQ_STRU * pMsg)
{
    OM_ERROR_LOG_CTRL_IND_STRU   *pstCrtlInd;

    OM_RecordInfoStart(VOS_EXC_DUMP_MEM_NUM_1, pMsg->ulSenderPid, WUEPS_PID_USIM, pMsg->enMsgName);

    if (ID_OM_ERR_LOG_REPORT_REQ == pMsg->enMsgName)
    {
        USIMM_CardErrorLogReport();

        OM_RecordInfoEnd(VOS_EXC_DUMP_MEM_NUM_1);

        return;
    }

    if (ID_OM_ERR_LOG_CTRL_IND == pMsg->enMsgName)
    {
        pstCrtlInd = (OM_ERROR_LOG_CTRL_IND_STRU *)pMsg;

        g_stErrLogCtrlInfo.ucAlmLevel = pstCrtlInd->ucAlmLevel;
        g_stErrLogCtrlInfo.ucAlmStatus = pstCrtlInd->ucAlmStatus;
    }

    OM_RecordInfoEnd(VOS_EXC_DUMP_MEM_NUM_1);

    return;
}
#endif


VOS_VOID USIMM_ApplicationMsgProc(USIMM_CMDHEADER_REQ_STRU * pMsg)
{
    VOS_UINT32                          ulQueueSize = 0;

    if (pMsg->enMsgName >= (sizeof(gastUSIMMAppFuncList)/sizeof(USIMMAPP_FUNCLIST_ST)))
    {
        /*lint -e534*/
        LogPrint2("\r\nUSIMM_ApplicationMsgProc:CmdType error!, Msg ID is %d, Send PID is %d\r\n", (VOS_INT)pMsg->enMsgName, (VOS_INT)pMsg->ulSenderPid);
        /*lint +e534*/

        return;
    }

    OM_RecordInfoStart(VOS_EXC_DUMP_MEM_NUM_1, pMsg->ulSenderPid, WUEPS_PID_USIM, pMsg->enMsgName);

    if (VOS_OK != gastUSIMMAppFuncList[pMsg->enMsgName].pProcFun(pMsg))
    {
        USIMM_WARNING_LOG("USIMM_ApplicationMsgProc: Message Handle Error");
    }

    OM_RecordInfoEnd(VOS_EXC_DUMP_MEM_NUM_1);

    USIMM_CardStateChangeProc();

    /*��ǰ����SAT�������SAT���ܴ�*/
    if (USIMM_SAT_STATE_NEEDFETCH == gstUSIMMBaseInfo.enSATState)
    {
        USIMM_SAT_Fetch(gstUSIMMBaseInfo.usSATLen);
    }

#ifndef OAM_DMT
    /* ��ȡ��ǰFID����Ϣ�ĸ��� */
    ulQueueSize = VOS_GetQueueSizeFromFid(MAPS_USIMM_FID);
#else
    ulQueueSize = VOS_NULL;
#endif
    /*����ʱ��ֹͣ������*/
    if((VOS_FALSE == USIMM_VsimIsActive())
        &&(USIMM_PB_IDLE == gstUSIMMBaseInfo.stPBInfo.enPBInitStatus)
        &&(USIMM_CLKSTOP_ALLOW == gstUSIMMDrvInfo.enCLKStop)
        && (VOS_NULL == ulQueueSize))
    {
        USIMM_NORMAL_LOG("USIMM_ApplicationMsgProc:Clock Stop Begin");

        /*lint -e534*/
        mdrv_sci_stop_tm((SCI_CLK_STOP_TYPE_E)gstUSIMMDrvInfo.enCLKLevel);
        /*lint +e534*/
    }
}
VOS_VOID USIMM_MsgProc(USIMM_CMDHEADER_REQ_STRU *pMsg)
{
    if (VOS_NULL_PTR == pMsg)
    {
        return;
    }

    if (MSP_PID_DIAG_APP_AGENT == pMsg->ulSenderPid)
    {
#if(FEATURE_ON == FEATURE_PTM)
        USIMM_ErrorLogProc(pMsg);
#endif
    }
    else
    {
        USIMM_ApplicationMsgProc(pMsg);
    }

    return;
}


VOS_UINT32 USIMM_FID_Init(enum VOS_INIT_PHASE_DEFINE ip)
{
    VOS_UINT32                              ulResult = VOS_OK;
    USIMM_CMD_DEBUG_MODE_ST                 stDebugInfo;
    NAS_NVIM_FOLLOWON_OPENSPEED_FLAG_STRU   stUSIMMOpenSpeed;

    switch (ip)
    {
        case VOS_IP_LOAD_CONFIG:    /* USIMM Application PID ע�� */
            ulResult = VOS_RegisterPIDInfo(WUEPS_PID_USIM,
                                           (Init_Fun_Type)VOS_NULL_PTR,
                                           (Msg_Fun_Type)USIMM_MsgProc);
            if (ulResult != VOS_OK)
            {
                return VOS_ERR;
            }

            /* ע��USIM Managerģ���FID */
            ulResult = VOS_RegisterMsgTaskPrio(MAPS_USIMM_FID, MAPS_USIMM_FID_PRIORITY);

            if (ulResult != VOS_OK)
            {
                return VOS_ERR;
            }

            break;

        case VOS_IP_INITIAL:    /* ��ģ���ʼ����� */

            USIMM_InitGlobalVarOnPower();

            /* ��ȡNV�жϿ��ٿ���״̬ */
            if (NV_OK != NV_Read(en_NV_Item_FollowOn_OpenSpeed_Flag, &stUSIMMOpenSpeed, sizeof(NAS_NVIM_FOLLOWON_OPENSPEED_FLAG_STRU)))
            {
                gulUSIMMOpenSpeed = USIMM_OPENSPEEDDISABLE;
            }
            else
            {
                gulUSIMMOpenSpeed = stUSIMMOpenSpeed.ulQuickStartSta;
            }

            if (USIMM_OPENSPEEDENABLE == gulUSIMMOpenSpeed)
            {
                USIMM_NORMAL_LOG("USIMM_FID_Init: Usimm Open Speed is ON");

                USIMM_InitOpenSpeed();

                ulResult = VOS_OK;
            }
            else
            {
                USIMM_NORMAL_LOG("USIMM_FID_Init: Start Normal Init SIM Step");

                ulResult = NV_Read(en_NV_Item_Usim_Debug_Mode_Set, &stDebugInfo, sizeof(USIMM_CMD_DEBUG_MODE_ST));

                if ((NV_OK ==  ulResult)&&(VOS_TRUE == stDebugInfo.usFlag)) /* �ӳ�ʱ�䲶���ʼ����Ϣ */
                {
                    return VOS_OK;
                }

                USIMM_InitLogFile();

                USIMM_InitExcLogFile();

#ifndef OAM_DMT
                ulResult = USIMM_ActiveCardReq(WUEPS_PID_USIM);
#endif

                USIMM_CardStatusRegCbFuncProc();
            }
            break;

        default:
            break;
    }

    return ulResult;
}

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


