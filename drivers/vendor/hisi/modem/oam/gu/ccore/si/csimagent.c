/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : csimagent.c
  �� �� ��   : ����
  ��    ��   :
  ��������   :
  ����޸�   :
  ��������   :
  �����б�   :
  �޸���ʷ   :

  1.��    ��   :
    ��    ��   :
    �޸�����   :
******************************************************************************/
#include "product_config.h"

#if (FEATURE_ON == FEATURE_UE_UICC_MULTI_APP_SUPPORT)

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "usimmglobal.h"
#include "csimagent.h"
#include "CbpaPsInterface.h"
#include "AtCsimagent.h"
#include "TafNvInterface.h"
#include "msp_diag_comm.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_CSIMAGENT_C

TAF_NV_LC_CTRL_PARA_STRU                g_stLCEnableFlag;

#if (FEATURE_ON == FEATURE_CL_INTERWORK)
/*****************************************************************************
  2 ������������
*****************************************************************************/
CSIMA_CBP_STATUS_IND_MSG_STRU           g_stCBPCardStatus;
CSIMA_EVENTLIST_RESEND_ENUM_UINT32      g_enEventListReSendFlag = CSIMA_EVENTLIST_RESEND_INIT;
CSIMA_CARDINFO_STRU                     g_stCpbCardInfo;

/*****************************************************************************
�� �� ��  : CSIMA_CardStatusInd
��������  : CSIMAģ����״��յ���״̬��Ϣ
�������  : ��
�������  : ��
�� �� ֵ  : ��
History     :
1.��    ��  : 2015��03��18��
  ��    ��  : zhuli
  �޸�����  : Create
*****************************************************************************/

VOS_VOID CSIMA_CCB_SetCardType(CSIMA_CBP_CARD_TYPE_ENUM_UINT16 enCardType)
{
    g_stCBPCardStatus.usCardType = enCardType;

    return;
}

/*****************************************************************************
�� �� ��  : CSIMA_CardStatusInd
��������  : CSIMAģ����״��յ���״̬��Ϣ
�������  : ��
�������  : ��
�� �� ֵ  : ��
History     :
1.��    ��  : 2015��03��18��
  ��    ��  : zhuli
  �޸�����  : Create
*****************************************************************************/

VOS_VOID CSIMA_CCB_AddCardType(CSIMA_CBP_CARD_TYPE_ENUM_UINT16 enCardType)
{
    g_stCBPCardStatus.usCardType |= enCardType;

    return;
}

/*****************************************************************************
�� �� ��  : CSIMA_CardStatusInd
��������  : CSIMAģ����״��յ���״̬��Ϣ
�������  : ��
�������  : ��
�� �� ֵ  : ��
History     :
1.��    ��  : 2015��03��18��
  ��    ��  : zhuli
  �޸�����  : Create
*****************************************************************************/

VOS_UINT16 CSIMA_CCB_GetCardType(VOS_VOID)
{
    return g_stCBPCardStatus.usCardType;
}

/*****************************************************************************
�� �� ��  : CSIMA_CardStatusInd
��������  : CSIMAģ����״��յ���״̬��Ϣ
�������  : ��
�������  : ��
�� �� ֵ  : ��
History     :
1.��    ��  : 2015��03��18��
  ��    ��  : zhuli
  �޸�����  : Create
*****************************************************************************/

VOS_VOID CSIMA_CCB_SetCardStatus(CSIMA_CBP_CARD_STATUS_ENUM_UINT16 enCardStatus)
{
    g_stCBPCardStatus.enStatus = enCardStatus;

    return;
}

/*****************************************************************************
�� �� ��  : CSIMA_CardStatusInd
��������  : CSIMAģ����״��յ���״̬��Ϣ
�������  : ��
�������  : ��
�� �� ֵ  : ��
History     :
1.��    ��  : 2015��03��18��
  ��    ��  : zhuli
  �޸�����  : Create
*****************************************************************************/

CSIMA_CBP_CARD_STATUS_ENUM_UINT16 CSIMA_CCB_GetCardStatus(VOS_VOID)
{
    return g_stCBPCardStatus.enStatus;
}

/*****************************************************************************
�� �� ��  : CSIMA_CCB_GetCSIMChannel
��������  : CSIMAģ����״��յ���״̬��Ϣ
�������  : ��
�������  : ��
�� �� ֵ  : ��
History     :
1.��    ��  : 2015��03��18��
  ��    ��  : zhuli
  �޸�����  : Create
*****************************************************************************/

VOS_UINT8 CSIMA_CCB_GetCSIMChannel(VOS_VOID)
{
    return g_stCBPCardStatus.ucCSIMChanNum;
}

/*****************************************************************************
�� �� ��  : CSIMA_CardStatusInd
��������  : CSIMAģ����״��յ���״̬��Ϣ
�������  : ��
�������  : ��
�� �� ֵ  : ��
History     :
1.��    ��  : 2015��03��18��
  ��    ��  : zhuli
  �޸�����  : Create
*****************************************************************************/
VOS_VOID CSIMA_CCB_ClearCardInfo(VOS_VOID)
{
    /* lint -e534 */
    VOS_MemSet(&g_stCBPCardStatus, 0, sizeof(g_stCBPCardStatus));
    /* lint +e534 */

    g_stCBPCardStatus.enIPCMsgId    = CSIMA_CBP_UICC_STATUS_IND_MSG;
    g_stCBPCardStatus.ucCSIMChanNum = CSIMA_CARD_CHANEL_NULL;
    g_stCBPCardStatus.ucUSIMChanNum = CSIMA_CARD_CHANEL_NULL;
    g_stCBPCardStatus.ucISIMChanNum = CSIMA_CARD_CHANEL_NULL;

    CSIMA_CCB_SetCardStatus(CSIMA_CBP_CARD_STATUS_BUTT);
    CSIMA_CCB_SetCardType(CSIMA_CBP_UNKNOWN_CARD);

    VOS_MemSet(g_stCBPCardStatus.aucCSIMAID, (VOS_CHAR)VOS_NULL_BYTE, USIMM_AID_LEN_MAX);
    VOS_MemSet(g_stCBPCardStatus.aucUSIMAID, (VOS_CHAR)VOS_NULL_BYTE, USIMM_AID_LEN_MAX);
    VOS_MemSet(g_stCBPCardStatus.aucISIMAID, (VOS_CHAR)VOS_NULL_BYTE, USIMM_AID_LEN_MAX);

    return;
}


/*****************************************************************************
�� �� ��  : CSIMA_SendTerminalResponse
��������  : CSIMAģ�鷢��TERMINAL RESPONSE����
�������  : ucLen:TERMINAL RESPONSE���ݳ���
            pucRsp:TERMINAL RESPONSE��������
�������  : ��
�� �� ֵ  : ��
History     :
1.��    ��  : 2013��12��19��
  ��    ��  : h00300778
  �޸�����  : Create
*****************************************************************************/
VOS_UINT32 CSIMA_SendTerminalResponse(VOS_UINT8 ucLen, VOS_UINT8 *pucRsp)
{
    USIMM_TERMINALRESPONSE_REQ_STRU    *pstMsg;

    /* ����Ϊ�˱���ԭ�ȴ����߼����䣬������Ϣ��PID����ʹ��STK��PID��ͨ��͸��������������˭�·���TR���� */
    pstMsg = (USIMM_TERMINALRESPONSE_REQ_STRU *)VOS_AllocMsg(MAPS_STK_PID,
                                                            (sizeof(USIMM_TERMINALRESPONSE_REQ_STRU)-VOS_MSG_HEAD_LENGTH)+ucLen);

    if (VOS_NULL_PTR == pstMsg)
    {
        CSIMA_WARNING_LOG("CSIMA_SendTerminalResponse: VOS_AllocMsg is Failed");/*��ӡ����*/

        return VOS_ERR; /*���غ���������Ϣ*/
    }

    /* �����Ϣ���� */
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_USIM;
    pstMsg->stMsgHeader.enMsgName       = USIMM_STKTERMINALRSP_REQ;
    pstMsg->stMsgHeader.enAppType       = USIMM_GUTL_APP;
    pstMsg->stMsgHeader.ulSendPara      = USIMM_TR_TYPE_CBP;
    pstMsg->ucDataLen                   = ucLen;

    VOS_MemCpy(pstMsg->aucContent, pucRsp, ucLen);

    return VOS_SendMsg(MAPS_STK_PID, pstMsg);
}


VOS_UINT32 CSIMA_SendTPDUReqMsg(
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    USIMM_SENDPARA_ENUM_UINT32          enSendPara,
    USIMM_TPDU_DATA_STRU               *pstTpduData
)
{
    USIMM_SENDTPDUDATA_REQ_STRU         *pstMsg;

    if (VOS_NULL_PTR == pstTpduData)
    {
        CSIMA_WARNING_LOG("SI_PIH_SendTPDUReq: Input Para is incorrect.");/*��ӡ����*/

        return VOS_ERR;
    }

    /* �����ڴ� */
    pstMsg = (USIMM_SENDTPDUDATA_REQ_STRU *)VOS_AllocMsg(WUEPS_PID_CSIMA,
                                                    (sizeof(USIMM_SENDTPDUDATA_REQ_STRU) - VOS_MSG_HEAD_LENGTH));

    if (VOS_NULL_PTR == pstMsg)
    {
        CSIMA_WARNING_LOG("SI_PIH_SendTPDUReq: VOS_AllocMsg is Failed");/*��ӡ����*/

        return VOS_ERR; /*���غ���������Ϣ*/
    }

    /* �����Ϣ���� */
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_USIM;
    pstMsg->stMsgHeader.enMsgName       = USIMM_SENDTPDUDATA_REQ;
    pstMsg->stMsgHeader.enAppType       = enAppType;
    pstMsg->stMsgHeader.ulSendPara      = enSendPara;

    VOS_MemCpy(&pstMsg->stTPDUData, pstTpduData, sizeof(USIMM_TPDU_DATA_STRU));

    VOS_MemSet(&pstMsg->stFilePath, 0, sizeof(USIMM_FILEPATH_INFO_STRU));

    return VOS_SendMsg(WUEPS_PID_CSIMA, pstMsg);
}

/*****************************************************************************
�� �� ��  : CSIMA_SendInitCardReqMsg
��������  : PIHģ��SIM����ʼ����Ϣ���ͺ���
�������  : enMsgName:��ʼ����Ϣ����
�������  : ��
�� �� ֵ  : VOS_OK/VOS_ERR
���ú���  :
��������  :
�޶���¼  :
1.��    ��  : 2015��02��06��
  ��    ��  : H00300778
  �޸�����  : �½�����
*****************************************************************************/
VOS_UINT32 CSIMA_SendInitCardReqMsg(USIMM_CMDTYPE_REQ_ENUM_UINT32 enMsgName)
{
    USIMM_ACTIVECARD_REQ_STRU          *pstMsg;

    pstMsg = (USIMM_ACTIVECARD_REQ_STRU *)VOS_AllocMsg(WUEPS_PID_CSIMA, sizeof(USIMM_ACTIVECARD_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        CSIMA_WARNING_LOG("SI_PIH_SendInitCardReqMsg:AllocMsg Failed.");

        return VOS_ERR;
    }

    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_USIM;
    pstMsg->stMsgHeader.enMsgName       = enMsgName;
    pstMsg->stMsgHeader.enAppType       = USIMM_GUTL_APP;
    pstMsg->stMsgHeader.ulSendPara      = VOS_NULL;

    return VOS_SendMsg(WUEPS_PID_CSIMA, pstMsg);
}

/*****************************************************************************
�� �� ��  : SI_PIH_SendActiveCardReqMsg
��������  : PIHģ��SIM����ʼ����Ϣ���ͺ���
�������  : enMsgName:��ʼ����Ϣ����
�������  : ��
�� �� ֵ  : VOS_OK/VOS_ERR
���ú���  :
��������  :
�޶���¼  :
1.��    ��  : 2015��02��06��
  ��    ��  : H00300778
  �޸�����  : �½�����
*****************************************************************************/
VOS_UINT32 CSIMA_SendActiveCardReqMsg(VOS_VOID)
{
    NAS_NVIM_FOLLOWON_OPENSPEED_FLAG_STRU                   stUSIMMOpenSpeed;
    VOS_UINT32                                              ulUsimmOpenSpeed;

    if(NV_OK != NV_Read(en_NV_Item_FollowOn_OpenSpeed_Flag, &stUSIMMOpenSpeed, sizeof(NAS_NVIM_FOLLOWON_OPENSPEED_FLAG_STRU)))
    {
        ulUsimmOpenSpeed = USIMM_OPENSPEEDDISABLE;
    }
    else
    {
        ulUsimmOpenSpeed = stUSIMMOpenSpeed.ulQuickStartSta;
    }

    if (USIMM_OPENSPEEDENABLE == ulUsimmOpenSpeed)
    {
        return VOS_ERR;
    }


    if (VOS_ERR == CSIMA_SendInitCardReqMsg(USIMM_ACTIVECARD_REQ))
    {
        CSIMA_WARNING_LOG("CSIMA_SendActiveCardReqMsg:Send Msg Failed.");

        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_UINT32  CSIMA_UiccResAccRspMsg(USIMM_RACCESS_CNF_STRU  *pstMsg)
{
    VOS_UINT32                          ulResult;
    CSIMA_CBP_RESACC_RSP_MSG_STRU      *pstResAccRsp;
    VOS_UINT32                          ulMemLen;
    VOS_UINT8                           ucSW1 = pstMsg->ucSW1;
    VOS_UINT8                           ucSW2 = pstMsg->ucSW2;

    if (pstMsg->usLen >= CSIMA_CBP_MSG_DATA_RSV)
    {
        ulMemLen = sizeof(CSIMA_CBP_RESACC_RSP_MSG_STRU) + pstMsg->usLen - CSIMA_CBP_MSG_DATA_RSV;
    }
    else
    {
        ulMemLen = sizeof(CSIMA_CBP_RESACC_RSP_MSG_STRU);
    }

    pstResAccRsp = (CSIMA_CBP_RESACC_RSP_MSG_STRU *)VOS_MemAlloc(WUEPS_PID_CSIMA, DYNAMIC_MEM_PT,
                                               ulMemLen);

    if (VOS_NULL_PTR == pstResAccRsp)
    {
        CSIMA_ERROR_LOG("CSIMA_UiccResAccRspMsg: Alloc mem fail!");
        return VOS_ERR;
    }

    /*lint -e534*/
    VOS_MemSet(pstResAccRsp, 0, ulMemLen);
    /*lint +e534*/

    pstResAccRsp->enIPCMsgId = CSIMA_CBP_UICC_RESACC_RSP_MSG;

    if (VOS_OK != pstMsg->stCmdResult.ulResult)
    {
        pstResAccRsp->usSWStatus = UIM_ERR_TIMEOUT;
        pstResAccRsp->usDataLen  = 0;
    }
    else
    {
        /* CBP���·�fetch�����˵����ظ�0x91XX��ʱ����Ҫת����0x9000 */
        if (0x91 == pstMsg->ucSW1)
        {
            ucSW1 = 0x90;
            ucSW2 = 0;
        }

        pstResAccRsp->usSWStatus = ucSW1;
        pstResAccRsp->usSWStatus = (VOS_UINT16)(pstResAccRsp->usSWStatus << 8) + ucSW2;

        pstResAccRsp->usDataLen  =  pstMsg->usLen;

        if (0 != pstResAccRsp->usDataLen)
        {
            /*lint -e534*/
            VOS_MemCpy(pstResAccRsp->aucData, pstMsg->aucContent, pstMsg->usLen);
            /*lint +e534*/
        }
    }

    /* ����CBPCAģ��ӿڽ����ݷ���ȥ */
    ulResult = CBPCA_SndDataToCbpca(WUEPS_PID_CSIMA,
                                    CSIMA_CBPCA_DATA_REQ,
                                    (VOS_UINT8 *)pstResAccRsp,
                                    ulMemLen);

    if (VOS_OK != ulResult)
    {
        CSIMA_ERROR_LOG("CSIMA_UiccResAccRspMsg: send RESACC RSP fail");
    }

    /*lint -e534*/
    VOS_MemFree(WUEPS_PID_CSIMA, pstResAccRsp);
    /*lint +e534*/

    return ulResult;
}


VOS_UINT32  CSIMA_UiccRtpduMsg(VOS_UINT32     ulResult,
                                         VOS_UINT8      ucSW1,
                                         VOS_UINT8      ucSW2,
                                         VOS_UINT8      ucDataLen,
                                         VOS_UINT8      *pucData)
{
    VOS_UINT32                          ulRslt;
    CSIMA_CBP_RTPDU_MSG_STRU           *pstRtpdu;
    VOS_UINT32                          ulMemLen;
    VOS_UINT8                           ucTmpSW1 = ucSW1;
    VOS_UINT8                           ucTmpSW2 = ucSW2;

    if (ucDataLen >= CSIMA_CBP_MSG_DATA_RSV)
    {
        ulMemLen = sizeof(CSIMA_CBP_RTPDU_MSG_STRU) + ucDataLen - CSIMA_CBP_MSG_DATA_RSV;
    }
    else
    {
        ulMemLen = sizeof(CSIMA_CBP_RTPDU_MSG_STRU);
    }

    pstRtpdu = (CSIMA_CBP_RTPDU_MSG_STRU *)VOS_MemAlloc(WUEPS_PID_CSIMA, DYNAMIC_MEM_PT,
                                               ulMemLen);

    if (VOS_NULL_PTR == pstRtpdu)
    {
        CSIMA_ERROR_LOG("CSIMA_UiccRtpduMsg: Alloc mem fail!");
        return VOS_ERR;
    }

    /*lint -e534*/
    VOS_MemSet(pstRtpdu, 0, ulMemLen);
    /*lint +e534*/

    pstRtpdu->enIPCMsgId = CSIMA_CBP_UICC_RTPDU_MSG;

    if (VOS_OK != ulResult)
    {
        pstRtpdu->usSWStatus = UIM_ERR_TIMEOUT;
        pstRtpdu->usDataLen  = 0;
    }
    else
    {
        /* CBP���·�fetch�����˵����ظ�0x91XX��ʱ����Ҫת����0x9000 */
        if (0x91 == ucSW1)
        {
            ucTmpSW1 = 0x90;
            ucTmpSW2 = 0;
        }

        pstRtpdu->usSWStatus = ucTmpSW1;
        pstRtpdu->usSWStatus = (VOS_UINT16)(pstRtpdu->usSWStatus << 8) + ucTmpSW2;

        pstRtpdu->usDataLen = ucDataLen;

        if (0 != ucDataLen)
        {
            /*lint -e534*/
            VOS_MemCpy(pstRtpdu->aucData, pucData, ucDataLen);
            /*lint +e534*/
        }
    }

    /* ����CBPCAģ��ӿڽ����ݷ���ȥ */
    ulRslt = CBPCA_SndDataToCbpca(WUEPS_PID_CSIMA,
                                    CSIMA_CBPCA_DATA_REQ,
                                    (VOS_UINT8 *)pstRtpdu,
                                    ulMemLen);

    if (VOS_OK != ulRslt)
    {
        CSIMA_ERROR_LOG("CSIMA_UiccRtpduMsg: send RTPDU fail");
    }

    /*lint -e534*/
    VOS_MemFree(WUEPS_PID_CSIMA, pstRtpdu);
    /*lint +e534*/

    if (CSIMA_EVENTLIST_NEED_RESEND == g_enEventListReSendFlag)
    {
        g_enEventListReSendFlag = CSIMA_EVENTLIST_RESENT;
        SI_STK_CbpSetupEventListCmdSnd();
    }

    return ulRslt;
}


VOS_UINT32 CSIMA_CBP_HandshakeReqMsg(VOS_VOID)
{
    VOS_UINT32                          ulRslt;
    CSIMA_CBP_UICC_MSGID_ENUM_UINT32    enIPCMsgId;

    enIPCMsgId = CSIMA_CBP_UICC_HANDSHAKE_MSG;

    /* ����CBPCAģ��ӿڽ����ݷ���ȥ */
    ulRslt = CBPCA_SndDataToCbpca(WUEPS_PID_CSIMA,
                                  CSIMA_CBPCA_DATA_REQ,
                                  (VOS_UINT8 *)&enIPCMsgId,
                                  sizeof(enIPCMsgId));

    if (VOS_OK != ulRslt)
    {
        CSIMA_ERROR_LOG("CSIMA_CBP_HandshakeReqMsg: send Data fail");
    }


    return ulRslt;
}
VOS_UINT32  CSIMA_UiccResAccReqMsg(CSIMA_CBP_RESACC_REQ_MSG_STRU *pstMsg)
{
    VOS_UINT32                          ulResult;
    CSIMA_CBP_RESACC_RSP_MSG_STRU       stResAccRsp;
    USIMM_RACCESS_REQ_STRU             *pstReqMsg;
    VOS_UINT8                          *pucFilePath;
    VOS_UINT8                           i;


    /* lint -e534 */
    (VOS_VOID)VOS_MemSet(&stResAccRsp, 0, sizeof(stResAccRsp));
    /* lint +e534 */

    stResAccRsp.enIPCMsgId = CSIMA_CBP_UICC_RESACC_RSP_MSG;

    ulResult = USIMM_VsimIsActive();

    if ((0 != pstMsg->usPathLen % 2) || (VOS_TRUE == ulResult))
    {
        /* ��CBP�ظ�����ִ�д��� */
        stResAccRsp.usSWStatus = UIM_ERR_TIMEOUT;

        /* ����CBPCAģ��ӿڽ����ݷ���ȥ */
        ulResult = CBPCA_SndDataToCbpca(WUEPS_PID_CSIMA,
                                        CSIMA_CBPCA_DATA_REQ,
                                        (VOS_UINT8 *)&stResAccRsp,
                                        sizeof(stResAccRsp));
        return ulResult;
    }

    pstReqMsg = (USIMM_RACCESS_REQ_STRU *)VOS_AllocMsg(WUEPS_PID_CSIMA,
                                                       sizeof(USIMM_RACCESS_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstReqMsg)
    {
        CSIMA_ERROR_LOG("CSIMA_UiccResAccReqMsg: VOS_AllocMsg is Failed");

        /* ��CBP�ظ�����ִ�д��� */
        stResAccRsp.usSWStatus = UIM_ERR_TIMEOUT;

        /* ����CBPCAģ��ӿڽ����ݷ���ȥ */
        ulResult = CBPCA_SndDataToCbpca(WUEPS_PID_CSIMA,
                                        CSIMA_CBPCA_DATA_REQ,
                                        (VOS_UINT8 *)&stResAccRsp,
                                        sizeof(stResAccRsp));
        return VOS_ERR;
    }

    /* �����Ϣ���� */
    pstReqMsg->stMsgHeader.ulReceiverPid= WUEPS_PID_USIM;
    pstReqMsg->stMsgHeader.enMsgName    = USIMM_RACCESS_REQ;
    pstReqMsg->stMsgHeader.enAppType    = USIMM_GUTL_APP;
    pstReqMsg->stMsgHeader.ulSendPara   = VOS_NULL;
    pstReqMsg->enCmdType                = pstMsg->ucCmd;
    pstReqMsg->usEfId                   = pstMsg->usFileId;
    pstReqMsg->ucP1                     = pstMsg->ucP1;
    pstReqMsg->ucP2                     = pstMsg->ucP2;
    pstReqMsg->ucP3                     = pstMsg->ucP3;
    pstReqMsg->usPathLen                = VOS_NULL;

    /* ����������� */
    if (0 != pstMsg->ucLen)
    {
        /* lint -e534 */
        (VOS_VOID)VOS_MemCpy(pstReqMsg->aucContent, pstMsg->aucData, pstMsg->ucLen);
        /* lint +e534 */
    }

    if (pstMsg->usPathLen > 2)
    {
        pstReqMsg->usPathLen = (pstMsg->usPathLen - 2) /((VOS_UINT16)(sizeof(VOS_UINT16))); /* ��ȥ���ֽڵ��ļ�ID */
    }

    pucFilePath = &(pstMsg->aucData[pstMsg->ucLen]);

    /* ���·����Ϣ */
    for (i = 0; i < pstReqMsg->usPathLen; i++)
    {
        pstReqMsg->ausPath[i] = ((pucFilePath[i*2] << 0x08) & 0xFF00) + pucFilePath[(i*2)+1];
    }

    ulResult = VOS_SendMsg(WUEPS_PID_CSIMA, pstReqMsg);

    if (VOS_OK != ulResult)
    {
        /* ��CBP�ظ�����ִ�д��� */
        stResAccRsp.usSWStatus = UIM_ERR_TIMEOUT;

        /* ����CBPCAģ��ӿڽ����ݷ���ȥ */
        ulResult = CBPCA_SndDataToCbpca(WUEPS_PID_CSIMA,
                                        CSIMA_CBPCA_DATA_REQ,
                                        (VOS_UINT8 *)&stResAccRsp,
                                        sizeof(stResAccRsp));
    }

    return ulResult;
}


VOS_UINT32  CSIMA_GetUiccAidAndChanNum(
    USIMM_AID_TYPE_ENUM_UINT32      enAidType,
    VOS_UINT8                      *pucAid,
    VOS_UINT8                      *pucChanNum
)
{
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulAIDLen = 0;
    VOS_UINT8                           ucChannelNum;

    ulResult = USIMM_GetAid(enAidType, &ulAIDLen, pucAid);

    if (VOS_OK != ulResult)
    {
        USIMM_ERROR_LOG("CSIMA_GetUiccAidAndChanNum: USIMM_GetAid Fail");

        return VOS_ERR;
    }

    ucChannelNum = USIMM_CCB_GetAppChNO(enAidType);

    if (VOS_NULL_BYTE == ucChannelNum)
    {
        USIMM_ERROR_LOG("CSIMA_GetUiccAidAndChanNum: USIMM_CCB_GetAppChNO Fail");

        return VOS_ERR;
    }

    *pucChanNum = ucChannelNum;

    return ulResult;
}



VOS_UINT32 CSIMA_CBPEnvelopeSend(CSIMA_CBP_CTPDU_MSG_STRU *pstCtpduMsg)
{
    VOS_UINT32                          ulResult;
    CSIMA_CBP_RTPDU_MSG_STRU            stRtpdu;

    /*lint -e534*/
    VOS_MemSet(&stRtpdu, VOS_NULL, sizeof(stRtpdu));
    /*lint +e534*/

    stRtpdu.enIPCMsgId = CSIMA_CBP_UICC_RTPDU_MSG;

    if ((SI_STK_ENVELOPE_EVENTDOWN == pstCtpduMsg->aucData[0])
        && (TAF_NVIM_LC_RAT_COMBINED_CL != g_stLCEnableFlag.enRatCombined))
    {
       /* ��CBP�ظ�����ִ�гɹ� */
       stRtpdu.usSWStatus = 0x9000;

       /* ����CBPCAģ��ӿڽ����ݷ���ȥ */
       ulResult = CBPCA_SndDataToCbpca(WUEPS_PID_CSIMA,
                                       CSIMA_CBPCA_DATA_REQ,
                                       (VOS_UINT8 *)&stRtpdu,
                                       sizeof(stRtpdu));
        return ulResult;
    }

    pstCtpduMsg->ucChanNum = 0;

    ulResult = CSIMA_SendTPDUOnChan(pstCtpduMsg);

    if (USIMM_API_SUCCESS != ulResult)
    {
        CSIMA_WARNING_LOG("CSIMA_CBPEnvelopeSend: CSIMA_SendTPDUOnBaseChan is Fail");
    }

    return ulResult;
}


VOS_UINT32 CSIMA_SendTPDUOnChan(CSIMA_CBP_CTPDU_MSG_STRU *pstCtpduMsg)
{
    CSIMA_CBP_RTPDU_MSG_STRU            stRtpdu;
    VOS_UINT32                          ulResult;
    USIMM_TPDU_DATA_STRU                stTPDU;
    VOS_UINT8                           ucChanNum;

    /* lint -e534 */
    (VOS_VOID)VOS_MemSet(&stRtpdu, VOS_NULL, sizeof(stRtpdu));

    (VOS_VOID)VOS_MemSet(&stTPDU, VOS_NULL, sizeof(stTPDU));
    /* lint +e534 */

    stRtpdu.enIPCMsgId = CSIMA_CBP_UICC_RTPDU_MSG;

    /* ��ȡCSIM��AID��ͨ���� */
    ucChanNum = CSIMA_CCB_GetCSIMChannel();

    /* ������� */
    if ((CSIMA_CARD_CHANEL_NULL == ucChanNum)
        ||(ucChanNum != pstCtpduMsg->ucChanNum)
        ||(pstCtpduMsg->usDataLen > USIMM_TPDU_DATA_LEN_MAX))
    {
       /* ��CBP�ظ�����ִ�д��� */
       stRtpdu.usSWStatus = UIM_ERR_TIMEOUT;

       /* ����CBPCAģ��ӿڽ����ݷ���ȥ */
       ulResult = CBPCA_SndDataToCbpca(WUEPS_PID_CSIMA,
                                       CSIMA_CBPCA_DATA_REQ,
                                       (VOS_UINT8 *)&stRtpdu,
                                       sizeof(stRtpdu));

        return ulResult;
    }

    /*lint -e534*/
    VOS_MemCpy(stTPDU.aucTPDUHead, pstCtpduMsg->aucCTPDUHdr, USIMM_TPDU_HEAD_LEN);
    /*lint +e534*/

    stTPDU.usDataLen = pstCtpduMsg->usDataLen;

    (VOS_VOID)VOS_MemCpy(stTPDU.aucData, pstCtpduMsg->aucData, pstCtpduMsg->usDataLen);

    if (0 == pstCtpduMsg->ucChanNum)
    {
        ulResult = CSIMA_SendTPDUReqMsg(USIMM_UNLIMIT_AUTO, USIMM_CL_SENDPARA, &stTPDU);
    }
    else
    {
        ulResult = CSIMA_SendTPDUReqMsg(USIMM_CDMA_APP, USIMM_CGLA_SENDPARA, &stTPDU);
    }

    if (VOS_OK != ulResult)
    {
        /* ��CBP�ظ�����ִ�д��� */
        stRtpdu.usSWStatus = UIM_ERR_TIMEOUT;

        /* ����CBPCAģ��ӿڽ����ݷ���ȥ */
        ulResult = CBPCA_SndDataToCbpca(WUEPS_PID_CSIMA,
                                        CSIMA_CBPCA_DATA_REQ,
                                        (VOS_UINT8 *)&stRtpdu,
                                        sizeof(stRtpdu));
    }

    return ulResult;
}


VOS_UINT32  CSIMA_UiccCtpduMsg(CSIMA_CBP_CTPDU_MSG_STRU *pstCtpduMsg)
{
    VOS_UINT32                          ulResult;

    /* EVENLOP����ͨ������ͨ���·� */
    if (CMD_INS_ENVELOPE == pstCtpduMsg->aucCTPDUHdr[INS])
    {
        ulResult = CSIMA_CBPEnvelopeSend(pstCtpduMsg);
    }
    /********* ��ENVELOP����ͨ��CGLA����TPDU�·���ȥ *********/
    else
    {
        ulResult = CSIMA_SendTPDUOnChan(pstCtpduMsg);
    }

    return ulResult;
}


VOS_UINT32 CSIMA_CBP_TerminalResponseMsgProc(CSIMA_CBP_TERMINALRESPONSE_MSG_STRU *pstMsg)
{
    VOS_UINT32                          ulRslt;

    /* �޿�ʱֱ�ӷ���USIMMģ�鴦�� */
    if (USIMM_CARD_NOCARD == g_stCpbCardInfo.enPhyType)
    {
        ulRslt = CSIMA_SendTerminalResponse((VOS_UINT8)pstMsg->usDataLen, pstMsg->aucData);
    }
    /* �п�ʱֱ�ӷ���STKģ�鴦����Ϊ��Ҫ���ͷ�STK��������ж�̬������ڴ� */
    else
    {
        ulRslt = SI_STK_CLSndTrMsg(pstMsg->usDataLen, pstMsg->aucData);
    }

    return ulRslt;
}


VOS_UINT32  CSIMA_CBPCADataIndProc(CBPCA_DATA_IND_MSG_STRU *pstMsg)
{
    VOS_UINT32                          *pulMsgId;
    VOS_UINT32                          ulResult = VOS_ERR;
    CSIMA_CBP_TERMINALRESPONSE_MSG_STRU *pstTR;

    pulMsgId = (VOS_UINT32 *)pstMsg->aucData;

    if (CSIMA_CBP_UICC_TERMINALRESPONSE_MSG == *pulMsgId)
    {
        pstTR = (CSIMA_CBP_TERMINALRESPONSE_MSG_STRU *)(pstMsg->aucData);

        /* �����ݷ��͵�STK��USIMMģ�鴦�� */
        ulResult = CSIMA_CBP_TerminalResponseMsgProc(pstTR);

        return ulResult;
    }

    if (CSIMA_CBP_UICC_RST_REQ_MSG == *pulMsgId)
    {
        /* ��CBP�����²�������RESET���� */
        if (TAF_NVIM_LC_RAT_COMBINED_CL != g_stLCEnableFlag.enRatCombined)
        {
            return VOS_OK;
        }

        /* ��RESET����USIMMģ�鴦�� */
        ulResult = CSIMA_SendActiveCardReqMsg();

        return ulResult;
    }

    if (CSIMA_CBP_UICC_CTPDU_MSG == *pulMsgId)
    {
        /* CBP����csimӦ�� */
        ulResult = CSIMA_UiccCtpduMsg((CSIMA_CBP_CTPDU_MSG_STRU *)(pstMsg->aucData));

        return ulResult;
    }

    if (CSIMA_CBP_UICC_RESACC_REQ_MSG == *pulMsgId)
    {
        /* CBP����usimӦ�� */
        ulResult = CSIMA_UiccResAccReqMsg((CSIMA_CBP_RESACC_REQ_MSG_STRU *)(pstMsg->aucData));

        return ulResult;
    }

    /* ���ִ��� */
    if (CSIMA_CBP_UICC_HANDSHAKE_MSG == *pulMsgId)
    {
        ulResult = CSIMA_CBP_HandshakeReqMsg();

        return ulResult;
    }

    /* ��¼���� */

    return ulResult;
}
VOS_UINT32  CSIMA_CBPCAMsgProc(CSIMA_CBP_MSG_STRU *pstMsg)
{
    VOS_UINT32                          ulResult;

    switch (pstMsg->ulIPCMsgId)
    {
        case CBPCA_CSIMA_DATA_IND:
            ulResult = CSIMA_CBPCADataIndProc((CBPCA_DATA_IND_MSG_STRU *)pstMsg);
            break;
        default:
            ulResult = VOS_ERR;
            break;
    }

    return ulResult;
}


VOS_UINT32  CSIMA_UsimMsgProc(CSIMA_CBP_MSG_STRU *pstMsg)
{
    VOS_UINT32                          ulResult;
    USIMM_STKENVELOPE_CNF_STRU          *pstEnvelopCnf;
    USIMM_SENDTPDUDATA_CNF_STRU         *pstSendTpduCnf;

    switch (pstMsg->ulIPCMsgId)
    {
        case USIMM_RACCESS_CNF:
            ulResult = CSIMA_UiccResAccRspMsg((USIMM_RACCESS_CNF_STRU *)pstMsg);
            break;

        case USIMM_STKENVELOPE_CNF:
            pstEnvelopCnf = (USIMM_STKENVELOPE_CNF_STRU *)pstMsg;

            ulResult = CSIMA_UiccRtpduMsg(pstEnvelopCnf->stCmdResult.ulResult,
                                          pstEnvelopCnf->ucSW1,
                                          pstEnvelopCnf->ucSW2,
                                          pstEnvelopCnf->ucDataLen,
                                          pstEnvelopCnf->aucData);
            break;

        /* ���¿�֮���ȫ�ֱ������ */
        case USIMM_ACTIVECARD_CNF:
            ulResult = CSIMA_Init();
            break;

        case USIMM_SENDTPDUDATA_CNF:
            pstSendTpduCnf = (USIMM_SENDTPDUDATA_CNF_STRU *)pstMsg;

            ulResult = CSIMA_UiccRtpduMsg(pstSendTpduCnf->stCmdResult.ulResult,
                                            pstSendTpduCnf->stRspData.ucSW1,
                                            pstSendTpduCnf->stRspData.ucSW2,
                                            (VOS_UINT8)pstSendTpduCnf->stRspData.ulDataLen,
                                            pstSendTpduCnf->stRspData.aucRspData);
             break;

        case USIMM_STKTERMINALRSP_CNF:
            ulResult = CSIMA_UiccRtpduMsg(((USIMM_STKTERMINALRSP_CNF_STRU *)pstMsg)->stCmdResult.ulResult,
                                          ((USIMM_STKTERMINALRSP_CNF_STRU *)pstMsg)->ucSW1,
                                          ((USIMM_STKTERMINALRSP_CNF_STRU *)pstMsg)->ucSW2,
                                          VOS_NULL,
                                          VOS_NULL_PTR);
            break;

        default:
            /* ��ӡ���� */
            ulResult = VOS_ERR;
            break;
    }

    return ulResult;
}


VOS_VOID CSIMA_CBPResetInd(CSIMA_CBPCA_MODEM_RESET_ENUM_UINT32 enModemReset)
{
    CSIMA_CBPCA_MODEM_RESET_IND_MSG_STRU    *pstResetInd;

    pstResetInd = (CSIMA_CBPCA_MODEM_RESET_IND_MSG_STRU *)VOS_AllocMsg(WUEPS_PID_CSIMA,
                                                                       sizeof(CSIMA_CBPCA_MODEM_RESET_IND_MSG_STRU));

    if (VOS_NULL_PTR == pstResetInd)
    {
        CSIMA_ERROR_LOG("CSIMA_CBPResetInd: Alloc msg fail!");

        return;
    }

    /* �����Ϣ���� */
    pstResetInd->ulReceiverPid      = WUEPS_PID_CBPCA;
    pstResetInd->enMsgType          = CSIMA_CBPCA_MODEM_RESET_IND;
    pstResetInd->enModemReset       = enModemReset;

    if (VOS_OK != VOS_SendMsg(WUEPS_PID_CSIMA, pstResetInd))
    {
        CSIMA_ERROR_LOG("CSIMA_CBPResetInd: Send msg fail!");

        return;
    }

    return;
}
VOS_UINT32  CSIMA_ATResetIndProc(AT_CSIMA_RESET_STATUS_IND_MSG_STRU *pstMsg)
{
    VOS_UINT32                          ulResult;

    /* �յ�CBP��λָʾ��Ҫ͸����CBPCA */
    CSIMA_CBPResetInd(pstMsg->enVIAModemStatus);

    /* ��λ�ɹ���CBP�ϱ���״̬ */
    if (CBP_MODEM_RESET_SUCC == pstMsg->enVIAModemStatus)
    {
        /* δ�ϱ�����״̬�Ļ������PIH�ϱ��˿�״̬���ϱ� */
        if (CSIMA_CBP_CARD_STATUS_BUTT == CSIMA_CCB_GetCardStatus())
        {
            CSIMA_INFO_LOG("CSIMA_ATResetIndProc: have no card status Ind");

            return VOS_OK;
        }

        /* ����CBPCAģ��ӿڽ����ݷ���ȥ */
        ulResult = CBPCA_SndDataToCbpca(WUEPS_PID_CSIMA,
                                    CSIMA_CBPCA_DATA_REQ,
                                    (VOS_UINT8 *)&g_stCBPCardStatus,
                                    sizeof(g_stCBPCardStatus));

        return ulResult;
    }

    return VOS_OK;
}


VOS_UINT32  CSIMA_ATMsgProc(CSIMA_CBP_MSG_STRU *pstMsg)
{
    VOS_UINT32                          ulResult = VOS_ERR;

    switch (pstMsg->ulIPCMsgId)
    {
        case AT_CSIMA_RESET_IND_MSG:
            ulResult = CSIMA_ATResetIndProc((AT_CSIMA_RESET_STATUS_IND_MSG_STRU *)pstMsg);
            break;

        default:
            ulResult = VOS_ERR;
            break;
    }

    return ulResult;
}


VOS_UINT32  CSIMA_ProactiveIndProc(CSIMA_STK_PROACTIVE_CMD_MSG_STRU *pstMsg)
{
    VOS_UINT32                          ulResult;
    CSIMA_CBP_PROACTIVE_CMD_MSG_STRU    stProactiveCmd;

    /*lint -e534*/
    VOS_MemSet(&stProactiveCmd, 0, sizeof(stProactiveCmd));
    /*lint +e534*/

    stProactiveCmd.enIPCMsgId = CSIMA_CBP_UICC_PROACTIVE_CMD_MSG;
    stProactiveCmd.usDataLen  = (VOS_UINT16)pstMsg->ulLen;

    if (0 != stProactiveCmd.usDataLen)
    {
        /*lint -e534*/
        VOS_MemCpy(stProactiveCmd.aucData, pstMsg->aucProactiveCmd, stProactiveCmd.usDataLen);
        /*lint +e534*/
    }

    ulResult = CBPCA_SndDataToCbpca(WUEPS_PID_CSIMA,
                                    CSIMA_CBPCA_DATA_REQ,
                                    (VOS_UINT8 *)&stProactiveCmd,
                                    (sizeof(CSIMA_CBP_PROACTIVE_CMD_MSG_STRU) - STK_PROACTIVE_DATA_LEN + stProactiveCmd.usDataLen));

    return ulResult;
}


VOS_UINT32  CSIMA_STKMsgProc(CSIMA_CBP_MSG_STRU *pstMsg)
{
    VOS_UINT32                          ulResult = VOS_ERR;

    switch (pstMsg->ulIPCMsgId)
    {
        case CSIMA_CBP_UICC_PROACTIVE_CMD_MSG:
            /* ��������ֱ�ӱ���CBPCAģ�� */
            ulResult = CSIMA_ProactiveIndProc((CSIMA_STK_PROACTIVE_CMD_MSG_STRU *)pstMsg);
            break;

        default:
            ulResult = VOS_ERR;
            break;
    }

    return ulResult;
}


/*****************************************************************************
�� �� ��  : CSIMA_CardStatusMsgSend
��������  : CSIMAģ���ϱ���״̬��CBP
�������  : enCardStatus:��״̬
            enCardType:������
�������  : ��
�� �� ֵ  : ��
History     :
1.��    ��  : 2014��01��16��
  ��    ��  : zhuli
  �޸�����  : Create
*****************************************************************************/

VOS_VOID CSIMA_CardStatusMsgSend(CSIMA_CBP_CARD_STATUS_ENUM_UINT16 enCardStatus)
{
    VOS_UINT32                          ulResult;

    CSIMA_CCB_SetCardStatus(enCardStatus);

    /* ����CBPCAģ��ӿڽ����ݷ���ȥ */
    ulResult = CBPCA_SndDataToCbpca(WUEPS_PID_CSIMA,
                                    CSIMA_CBPCA_DATA_REQ,
                                    (VOS_UINT8 *)&g_stCBPCardStatus,
                                    sizeof(g_stCBPCardStatus));

    if (VOS_OK != ulResult)
    {
        CSIMA_ERROR_LOG("CSIMA_CardStatusMsgSend: Send Msg To CBPCA fail");
    }

    if (CSIMA_CBP_CARD_READY == enCardStatus)
    {
        g_enEventListReSendFlag = CSIMA_EVENTLIST_NEED_RESEND;
    }

    return;
}

/*****************************************************************************
�� �� ��  : CSIMA_CardStatusInd
��������  : CSIMAģ����״��յ���״̬��Ϣ
�������  : ��
�������  : ��
�� �� ֵ  : ��
History     :
1.��    ��  : 2015��03��18��
  ��    ��  : zhuli
  �޸�����  : Create
*****************************************************************************/
VOS_VOID CSIMA_UpdateUICCCardInfo(VOS_VOID)
{
    VOS_UINT32                  ulResult;
    VOS_UINT32                  usCardType;

    CSIMA_CCB_SetCardType(CSIMA_CBP_UICC_CARD);

    ulResult = CSIMA_GetUiccAidAndChanNum(USIMM_AID_TYPE_CSIM,
                                          g_stCBPCardStatus.aucCSIMAID,
                                          &g_stCBPCardStatus.ucCSIMChanNum);

    /* �����CSIM��Ӧ�� */
    if (VOS_OK == ulResult)
    {
        CSIMA_CCB_AddCardType(CSIMA_CBP_CSIM_CARD);
    }

    /* �õ�USIMӦ��*/
    ulResult = CSIMA_GetUiccAidAndChanNum(USIMM_AID_TYPE_USIM,
                                          g_stCBPCardStatus.aucUSIMAID,
                                          &g_stCBPCardStatus.ucUSIMChanNum);

    /* ���û��USIM��Ӧ�� */
    if (VOS_OK == ulResult)
    {
        CSIMA_CCB_AddCardType(CSIMA_CBP_USIM_CARD);
    }

    ulResult = CSIMA_GetUiccAidAndChanNum(USIMM_AID_TYPE_ISIM,
                                          g_stCBPCardStatus.aucISIMAID,
                                          &g_stCBPCardStatus.ucISIMChanNum);

    /* ���û��ISIM��Ӧ�� */
    if (VOS_OK == ulResult)
    {
        CSIMA_CCB_AddCardType(CSIMA_CBP_ISIM_CARD);
    }

    usCardType = CSIMA_CCB_GetCardType();

    if (VOS_NULL == (usCardType&((VOS_UINT32)CSIMA_CBP_CSIM_CARD|(VOS_UINT32)CSIMA_CBP_USIM_CARD)))
    {
        CSIMA_CCB_SetCardType(CSIMA_CBP_UNKNOWN_CARD);
    }

    return;
}

/*****************************************************************************
�� �� ��  : CSIMA_CardStatusInd
��������  : CSIMAģ����״��յ���״̬��Ϣ
�������  : ��
�������  : ��
�� �� ֵ  : ��
History     :
1.��    ��  : 2015��03��18��
  ��    ��  : zhuli
  �޸�����  : Create
*****************************************************************************/
VOS_VOID CSIMA_UpdateICCCardInfo(VOS_VOID)
{
    VOS_UINT32                      ulResult;
    USIMM_CARD_SERVIC_ENUM_UINT32   enCardStatus;

    CSIMA_CCB_SetCardType(CSIMA_CBP_CARD_NONE);

    ulResult = USIMM_GetCardType(USIMM_CARD_UIM, &enCardStatus);

    if ((USIMM_API_SUCCESS != ulResult)||(USIMM_CARD_SERVIC_ABSENT == enCardStatus))
    {
        CSIMA_CCB_SetCardType(CSIMA_CBP_UNKNOWN_CARD);
    }
    else
    {
        CSIMA_CCB_SetCardType(CSIMA_CBP_UIM_CARD);
    }

    return;
}

/*****************************************************************************
�� �� ��  : CSIMA_CardStatusInd
��������  : CSIMAģ����״��յ���״̬��Ϣ
�������  : ��
�������  : ��
�� �� ֵ  : ��
History     :
1.��    ��  : 2015��03��18��
  ��    ��  : zhuli
  �޸�����  : Create
*****************************************************************************/
VOS_VOID CSIMA_UpdateCardInfo(USIMM_PHYCARD_TYPE_ENUM_UINT32 enCardType)
{
    if (USIMM_PHYCARD_TYPE_ICC == enCardType)
    {
        CSIMA_UpdateICCCardInfo();
    }
    else if (USIMM_PHYCARD_TYPE_UICC == enCardType)
    {
        CSIMA_UpdateUICCCardInfo();
    }
    else
    {
        CSIMA_CCB_ClearCardInfo();
    }

    return;
}

/*****************************************************************************
�� �� ��  : CSIMA_CardStatusInd
��������  : CSIMAģ����״��յ���״̬��Ϣ
�������  : pstMsg:��״̬��Ϣ
�������  : ��
�� �� ֵ  : ��
History     :
1.��    ��  : 2014��01��16��
  ��    ��  : zhuli
  �޸�����  : Create
*****************************************************************************/
VOS_VOID CSIMA_CardStatusInd(USIMM_CARDSTATUS_IND_STRU *pstMsg)
{
    if (USIMM_PHYCARD_TYPE_NOCARD == pstMsg->enPhyCardType)    /*����*/
    {
        CSIMA_CCB_ClearCardInfo();

        CSIMA_CardStatusMsgSend(CSIMA_CBP_CARD_NOT_READY);
    }
    /*ֻ����У��ɹ�PIN֮��Ż��ϱ����״̬*/
    else if (USIMM_CARD_SERVIC_AVAILABLE == pstMsg->stCsimUimInfo.enCardService)
    {
        CSIMA_UpdateCardInfo(pstMsg->enPhyCardType);

        CSIMA_CardStatusMsgSend(CSIMA_CBP_CARD_READY);
    }
    else if (USIMM_CARD_SERVIC_AVAILABLE != pstMsg->stUsimSimInfo.enCardService)      /*PIN�ֿ���*/
    {
        CSIMA_UpdateCardInfo(pstMsg->enPhyCardType);

        CSIMA_CardStatusMsgSend(CSIMA_CBP_CARD_BOOTUP);
    }
    else    /*����״̬����*/
    {
        CSIMA_ERROR_LOG("CSIMA_CardStatusInd: Receive Card status");
    }

    return;
}


VOS_UINT32  CSIMA_PIHMsgProc(USIMM_CARDSTATUS_IND_STRU *pstMsg)
{
    if (USIMM_CARDSTATUS_IND != pstMsg->ulMsgName)
    {
        /* ��¼����Ŀǰֻ����PIHģ�鷢�����Ŀ�״̬��Ϣ */
        return VOS_ERR;
    }

    CSIMA_CardStatusInd(pstMsg);

    g_stCpbCardInfo.enPhyType   = pstMsg->enPhyCardType;

    return VOS_OK;
}
VOS_VOID CSIMA_PidMsgProc(CSIMA_CBP_MSG_STRU *pstMsg)
{
    VOS_UINT32                          ulResult = VOS_ERR;

    if (VOS_TRUE != g_stLCEnableFlag.ucLCEnableFlg)
    {
        CSIMA_WARNING_LOG("CSIMA_PidMsgProc:feature LC is disable");

        return;
    }

    switch (pstMsg->ulSenderPid)
    {
        case WUEPS_PID_AT:
            ulResult = CSIMA_ATMsgProc(pstMsg);
            break;

        case WUEPS_PID_USIM:
            ulResult = CSIMA_UsimMsgProc(pstMsg);
            break;

        case MAPS_STK_PID:
            ulResult = CSIMA_STKMsgProc(pstMsg);
            break;

        case MAPS_PIH_PID:
            ulResult = CSIMA_PIHMsgProc((USIMM_CARDSTATUS_IND_STRU *)pstMsg);
            break;

        case WUEPS_PID_CBPCA:
            ulResult = CSIMA_CBPCAMsgProc(pstMsg);
            break;

        default:
            CSIMA_WARNING_LOG("CSIMA_PidMsgProc:Default Unknow PID Msg");
            break;
    }

    if (VOS_OK != ulResult)
    {
        /* ��¼���� */
        CSIMA_ERROR_LOG("CSIMA_PidMsgProc:FAIL to proc msg");
    }

    return;
}
VOS_UINT32 CSIMA_Init(VOS_VOID)
{
    VOS_UINT32                          ulResult;

    /* ��PIHģ��ע�Ῠ״̬�ϱ�PID */
    ulResult = PIH_RegUsimCardStatusIndMsg(WUEPS_PID_CSIMA);

    if (VOS_OK != ulResult)
    {
        CSIMA_ERROR_LOG("CSIMA_Init: REG card status Ind fail");
        return VOS_ERR;
    }

    /* ģ��ȫ�ֱ�����ʼ�� */
    CSIMA_CCB_ClearCardInfo();

    if (NV_OK != NV_Read(en_NV_Item_LC_Ctrl_PARA, &g_stLCEnableFlag, sizeof(TAF_NV_LC_CTRL_PARA_STRU)))
    {
        g_stLCEnableFlag.ucLCEnableFlg = VOS_FALSE;
        g_stLCEnableFlag.enRatCombined = TAF_NVIM_LC_RAT_COMBINED_GUL;
    }

    return VOS_OK;
}


VOS_UINT32 CSIMA_PidInit(enum VOS_INIT_PHASE_DEFINE ip)
{
    switch( ip )
    {
        case VOS_IP_INITIAL:
            return CSIMA_Init();

        default:
            break;
    }

    return VOS_OK;
}
#endif /* FEATURE_ON == FEATURE_CL_INTERWORK */

VOS_UINT32 CSIMA_FidInit(enum VOS_INIT_PHASE_DEFINE ip)
{
#if (FEATURE_ON == FEATURE_CL_INTERWORK)
    VOS_UINT32      ulRslt;

    switch (ip)
    {
        case VOS_IP_LOAD_CONFIG:
        {
            ulRslt = VOS_RegisterPIDInfo(WUEPS_PID_CSIMA,
                                        (Init_Fun_Type)CSIMA_PidInit,
                                        (Msg_Fun_Type)CSIMA_PidMsgProc);
            if (VOS_OK != ulRslt)
            {
                return VOS_ERR;
            }

            /* ע���������ȼ� */
            ulRslt = VOS_RegisterMsgTaskPrio(WUEPS_FID_CSIMA, VOS_PRIORITY_M5);

            if (VOS_OK != ulRslt)
            {
                return VOS_ERR;
            }

            break;
        }
        default:
            break;
    }
#endif /* FEATURE_ON == FEATURE_CL_INTERWORK */

    return VOS_OK;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#else

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "csimagent.h"
#include "CbpaPsInterface.h"
#include "AtCsimagent.h"
#include "TafNvInterface.h"
#include "msp_diag_comm.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_CSIMAGENT_C

TAF_NV_LC_CTRL_PARA_STRU                g_stLCEnableFlag;

/* Add by H00300778 for MultiAppSync Begin 2015-05-12 */
VOS_BOOL                                g_bNeedCardStatus = VOS_FALSE;

/* Add by H00300778 for MultiAppSync End 2015-05-12 */

#if (FEATURE_ON == FEATURE_CL_INTERWORK)
/*****************************************************************************
  2 ������������
*****************************************************************************/
CSIMA_CBP_STATUS_IND_MSG_STRU           g_stCBPCardStatus;
CSIMA_EVENTLIST_RESEND_ENUM_UINT32      g_enEventListReSendFlag = CSIMA_EVENTLIST_RESEND_INIT;
CSIMA_CARDINFO_STRU                     g_stCpbCardInfo;

/*****************************************************************************
�� �� ��  : CSIMA_SendTerminalResponse
��������  : CSIMAģ�鷢��TERMINAL RESPONSE����
�������  : ucLen:TERMINAL RESPONSE���ݳ���
            pucRsp:TERMINAL RESPONSE��������
�������  : ��
�� �� ֵ  : ��
History     :
1.��    ��  : 2013��12��19��
  ��    ��  : h00300778
  �޸�����  : Create
*****************************************************************************/
VOS_UINT32 CSIMA_SendTerminalResponse(VOS_UINT8 ucLen, VOS_UINT8 *pucRsp)
{
    USIMM_TERMINALRESPONSE_REQ_STRU    *pstMsg;

    /* ����Ϊ�˱���ԭ�ȴ����߼����䣬������Ϣ��PID����ʹ��STK��PID��ͨ��͸��������������˭�·���TR���� */
    pstMsg = (USIMM_TERMINALRESPONSE_REQ_STRU *)VOS_AllocMsg(MAPS_STK_PID,
                                                            (sizeof(USIMM_TERMINALRESPONSE_REQ_STRU)-VOS_MSG_HEAD_LENGTH)+ucLen);

    if (VOS_NULL_PTR == pstMsg)
    {
        CSIMA_WARNING_LOG("CSIMA_SendTerminalResponse: VOS_AllocMsg is Failed");/*��ӡ����*/

        return VOS_ERR; /*���غ���������Ϣ*/
    }

    /* �����Ϣ���� */
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_USIM;
    pstMsg->stMsgHeader.enMsgName       = USIMM_STKTERMINALRSP_REQ;
    pstMsg->stMsgHeader.enAppType       = USIMM_GUTL_APP;
    pstMsg->stMsgHeader.ulSendPara      = USIMM_TR_TYPE_CBP;
    pstMsg->ucDataLen                   = ucLen;

    VOS_MemCpy(pstMsg->aucContent, pucRsp, ucLen);

    return VOS_SendMsg(MAPS_STK_PID, pstMsg);
}

/*****************************************************************************
�� �� ��  : CSIMA_SendOpenChannelReqMsg
��������  : CSIMAģ��SIM�߼�ͨ��������Ϣ���ͺ���
�������  : ulAIDLen:AID����
            pucADFName:AID����
�������  : ��
�� �� ֵ  : VOS_OK/VOS_ERR
���ú���  :
��������  :
�޶���¼  :
1.��    ��  : 2015��01��31��
  ��    ��  : H00300778
  �޸�����  : �½�����
*****************************************************************************/
VOS_UINT32 CSIMA_SendOpenChannelReqMsg(VOS_UINT32 ulAIDLen, VOS_UINT8 *pucADFName)
{
    USIMM_OPENCHANNEL_REQ_STRU         *pstMsg;

    if (ulAIDLen > (2 * USIMM_AID_LEN_MAX))
    {
        return VOS_ERR;
    }

    pstMsg = (USIMM_OPENCHANNEL_REQ_STRU *)VOS_AllocMsg(WUEPS_PID_CSIMA,
                                                        sizeof(USIMM_OPENCHANNEL_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        CSIMA_WARNING_LOG("CSIMA_SendOpenChannelReqMsg: VOS_AllocMsg is Failed");

        return VOS_ERR;
    }

    VOS_MemSet(&pstMsg->stChannelInfo, 0, sizeof(USIMM_CHANNEL_INFO_STRU));

    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_USIM;
    pstMsg->stMsgHeader.enMsgName       = USIMM_OPENCHANNEL_REQ;
    pstMsg->stMsgHeader.enAppType       = USIMM_GUTL_APP;
    pstMsg->stMsgHeader.ulSendPara      = VOS_NULL;

    pstMsg->stChannelInfo.ulAIDLen      = ulAIDLen;

    VOS_MemCpy(pstMsg->stChannelInfo.aucADFName, pucADFName, ulAIDLen);

    return VOS_SendMsg(WUEPS_PID_CSIMA, pstMsg);
}



VOS_UINT32 CSIMA_SendTPDUReqMsg(
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    USIMM_SENDPARA_ENUM_UINT32          enSendPara,
    USIMM_TPDU_DATA_STRU               *pstTpduData
)
{
    USIMM_SENDTPDUDATA_REQ_STRU         *pstMsg;

    if (VOS_NULL_PTR == pstTpduData)
    {
        CSIMA_WARNING_LOG("SI_PIH_SendTPDUReq: Input Para is incorrect.");/*��ӡ����*/

        return VOS_ERR;
    }

    /* �����ڴ� */
    pstMsg = (USIMM_SENDTPDUDATA_REQ_STRU *)VOS_AllocMsg(WUEPS_PID_CSIMA,
                                                    (sizeof(USIMM_SENDTPDUDATA_REQ_STRU) - VOS_MSG_HEAD_LENGTH));

    if (VOS_NULL_PTR == pstMsg)
    {
        CSIMA_WARNING_LOG("SI_PIH_SendTPDUReq: VOS_AllocMsg is Failed");/*��ӡ����*/

        return VOS_ERR; /*���غ���������Ϣ*/
    }

    /* �����Ϣ���� */
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_USIM;
    pstMsg->stMsgHeader.enMsgName       = USIMM_SENDTPDUDATA_REQ;
    pstMsg->stMsgHeader.enAppType       = enAppType;
    pstMsg->stMsgHeader.ulSendPara      = enSendPara;

    VOS_MemCpy(&pstMsg->stTPDUData, pstTpduData, sizeof(USIMM_TPDU_DATA_STRU));

    VOS_MemSet(&pstMsg->stFilePath, 0, sizeof(USIMM_FILEPATH_INFO_STRU));

    return VOS_SendMsg(WUEPS_PID_CSIMA, pstMsg);
}

/*****************************************************************************
�� �� ��  : CSIMA_SendInitCardReqMsg
��������  : PIHģ��SIM����ʼ����Ϣ���ͺ���
�������  : enMsgName:��ʼ����Ϣ����
�������  : ��
�� �� ֵ  : VOS_OK/VOS_ERR
���ú���  :
��������  :
�޶���¼  :
1.��    ��  : 2015��02��06��
  ��    ��  : H00300778
  �޸�����  : �½�����
*****************************************************************************/
VOS_UINT32 CSIMA_SendInitCardReqMsg(USIMM_CMDTYPE_REQ_ENUM_UINT32 enMsgName)
{
    USIMM_ACTIVECARD_REQ_STRU          *pstMsg;

    pstMsg = (USIMM_ACTIVECARD_REQ_STRU *)VOS_AllocMsg(WUEPS_PID_CSIMA, sizeof(USIMM_ACTIVECARD_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        CSIMA_WARNING_LOG("SI_PIH_SendInitCardReqMsg:AllocMsg Failed.");

        return VOS_ERR;
    }

    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_USIM;
    pstMsg->stMsgHeader.enMsgName       = enMsgName;
    pstMsg->stMsgHeader.enAppType       = USIMM_GUTL_APP;
    pstMsg->stMsgHeader.ulSendPara      = VOS_NULL;

    return VOS_SendMsg(WUEPS_PID_CSIMA, pstMsg);
}

/*****************************************************************************
�� �� ��  : SI_PIH_SendActiveCardReqMsg
��������  : PIHģ��SIM����ʼ����Ϣ���ͺ���
�������  : enMsgName:��ʼ����Ϣ����
�������  : ��
�� �� ֵ  : VOS_OK/VOS_ERR
���ú���  :
��������  :
�޶���¼  :
1.��    ��  : 2015��02��06��
  ��    ��  : H00300778
  �޸�����  : �½�����
*****************************************************************************/
VOS_UINT32 CSIMA_SendActiveCardReqMsg(VOS_VOID)
{
    NAS_NVIM_FOLLOWON_OPENSPEED_FLAG_STRU                   stUSIMMOpenSpeed;
    VOS_UINT32                                              ulUsimmOpenSpeed;

    if(NV_OK != NV_Read(en_NV_Item_FollowOn_OpenSpeed_Flag, &stUSIMMOpenSpeed, sizeof(NAS_NVIM_FOLLOWON_OPENSPEED_FLAG_STRU)))
    {
        ulUsimmOpenSpeed = USIMM_OPENSPEEDDISABLE;
    }
    else
    {
        ulUsimmOpenSpeed = stUSIMMOpenSpeed.ulQuickStartSta;
    }

    if (USIMM_OPENSPEEDENABLE == ulUsimmOpenSpeed)
    {
        return VOS_ERR;
    }


    if (VOS_ERR == CSIMA_SendInitCardReqMsg(USIMM_ACTIVECARD_REQ))
    {
        CSIMA_WARNING_LOG("CSIMA_SendActiveCardReqMsg:Send Msg Failed.");

        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
�� �� ��  : CSIMA_DataHook
��������  : ���ݹ��Ӻ���
�������  : ulLength:���ݳ���
           pucData:��������
�������  : ��
�� �� ֵ  : ��
���ú���  : ��
��������  :
�޶���¼  :
1. ��    ��   : 2015��05��13��
   ��    ��   : H00300778
   �޸�����   : Creat
*****************************************************************************/
VOS_VOID CSIMA_DataHook(
    VOS_UINT32                          ulLength,
    VOS_UINT8                          *pucData)
{
    MsgBlock                           *pMsg;

    pMsg = (MsgBlock*)VOS_AllocMsg(WUEPS_PID_CSIMA, ulLength);

    if (VOS_NULL_PTR == pMsg)
    {
        USIMM_WARNING_LOG("CSIMA_DataHook:WARNING:alloc msg failed\n");

        return;
    }

    pMsg->ulReceiverPid   = WUEPS_PID_CSIMA;

    pMsg->ulLength        = ulLength;

    VOS_MemCpy(pMsg->aucValue, pucData, ulLength);

    DIAG_TraceReport((VOS_VOID *)(pMsg));

    VOS_FreeMsg(WUEPS_PID_CSIMA, pMsg);

    return;
}


VOS_UINT32  CSIMA_UiccResAccRspMsg(USIMM_RACCESS_CNF_STRU  *pstMsg)
{
    VOS_UINT32                          ulResult;
    CSIMA_CBP_RESACC_RSP_MSG_STRU      *pstResAccRsp;
    VOS_UINT32                          ulMemLen;
    VOS_UINT8                           ucSW1 = pstMsg->ucSW1;
    VOS_UINT8                           ucSW2 = pstMsg->ucSW2;

    if (pstMsg->usLen >= CSIMA_CBP_MSG_DATA_RSV)
    {
        ulMemLen = sizeof(CSIMA_CBP_RESACC_RSP_MSG_STRU) + pstMsg->usLen - CSIMA_CBP_MSG_DATA_RSV;
    }
    else
    {
        ulMemLen = sizeof(CSIMA_CBP_RESACC_RSP_MSG_STRU);
    }

    pstResAccRsp = (CSIMA_CBP_RESACC_RSP_MSG_STRU *)VOS_MemAlloc(WUEPS_PID_CSIMA, DYNAMIC_MEM_PT,
                                               ulMemLen);

    if (VOS_NULL_PTR == pstResAccRsp)
    {
        CSIMA_ERROR_LOG("CSIMA_UiccResAccRspMsg: Alloc mem fail!");
        return VOS_ERR;
    }

    /*lint -e534*/
    VOS_MemSet(pstResAccRsp, 0, ulMemLen);
    /*lint +e534*/

    pstResAccRsp->enIPCMsgId = CSIMA_CBP_UICC_RESACC_RSP_MSG;

    if (VOS_OK != pstMsg->stCmdResult.ulResult)
    {
        pstResAccRsp->usSWStatus = UIM_ERR_TIMEOUT;
        pstResAccRsp->usDataLen  = 0;
    }
    else
    {
        /* CBP���·�fetch�����˵����ظ�0x91XX��ʱ����Ҫת����0x9000 */
        if (0x91 == pstMsg->ucSW1)
        {
            ucSW1 = 0x90;
            ucSW2 = 0;
        }

        pstResAccRsp->usSWStatus = ucSW1;
        pstResAccRsp->usSWStatus = (VOS_UINT16)(pstResAccRsp->usSWStatus << 8) + ucSW2;

        pstResAccRsp->usDataLen  =  pstMsg->usLen;

        if (0 != pstResAccRsp->usDataLen)
        {
            /*lint -e534*/
            VOS_MemCpy(pstResAccRsp->aucData, pstMsg->aucContent, pstMsg->usLen);
            /*lint +e534*/
        }
    }

    /* ����CBPCAģ��ӿڽ����ݷ���ȥ */
    ulResult = CBPCA_SndDataToCbpca(WUEPS_PID_CSIMA,
                                    CSIMA_CBPCA_DATA_REQ,
                                    (VOS_UINT8 *)pstResAccRsp,
                                    ulMemLen);

    if (VOS_OK != ulResult)
    {
        CSIMA_ERROR_LOG("CSIMA_UiccResAccRspMsg: send RESACC RSP fail");
    }

    /*lint -e534*/
    VOS_MemFree(WUEPS_PID_CSIMA, pstResAccRsp);
    /*lint +e534*/

    return ulResult;
}


VOS_UINT32  CSIMA_UiccRtpduMsg(VOS_UINT32     ulResult,
                                         VOS_UINT8      ucSW1,
                                         VOS_UINT8      ucSW2,
                                         VOS_UINT8      ucDataLen,
                                         VOS_UINT8      *pucData)
{
    VOS_UINT32                          ulRslt;
    CSIMA_CBP_RTPDU_MSG_STRU           *pstRtpdu;
    VOS_UINT32                          ulMemLen;
    VOS_UINT8                           ucTmpSW1 = ucSW1;
    VOS_UINT8                           ucTmpSW2 = ucSW2;

    if (ucDataLen >= CSIMA_CBP_MSG_DATA_RSV)
    {
        ulMemLen = sizeof(CSIMA_CBP_RTPDU_MSG_STRU) + ucDataLen - CSIMA_CBP_MSG_DATA_RSV;
    }
    else
    {
        ulMemLen = sizeof(CSIMA_CBP_RTPDU_MSG_STRU);
    }

    pstRtpdu = (CSIMA_CBP_RTPDU_MSG_STRU *)VOS_MemAlloc(WUEPS_PID_CSIMA, DYNAMIC_MEM_PT,
                                               ulMemLen);

    if (VOS_NULL_PTR == pstRtpdu)
    {
        CSIMA_ERROR_LOG("CSIMA_UiccRtpduMsg: Alloc mem fail!");
        return VOS_ERR;
    }

    /*lint -e534*/
    VOS_MemSet(pstRtpdu, 0, ulMemLen);
    /*lint +e534*/

    pstRtpdu->enIPCMsgId = CSIMA_CBP_UICC_RTPDU_MSG;

    if (VOS_OK != ulResult)
    {
        pstRtpdu->usSWStatus = UIM_ERR_TIMEOUT;
        pstRtpdu->usDataLen  = 0;
    }
    else
    {
        /* CBP���·�fetch�����˵����ظ�0x91XX��ʱ����Ҫת����0x9000 */
        if (0x91 == ucSW1)
        {
            ucTmpSW1 = 0x90;
            ucTmpSW2 = 0;
        }

        pstRtpdu->usSWStatus = ucTmpSW1;
        pstRtpdu->usSWStatus = (VOS_UINT16)(pstRtpdu->usSWStatus << 8) + ucTmpSW2;

        pstRtpdu->usDataLen = ucDataLen;

        if (0 != ucDataLen)
        {
            /*lint -e534*/
            VOS_MemCpy(pstRtpdu->aucData, pucData, ucDataLen);
            /*lint +e534*/
        }
    }

    /* ����CBPCAģ��ӿڽ����ݷ���ȥ */
    ulRslt = CBPCA_SndDataToCbpca(WUEPS_PID_CSIMA,
                                    CSIMA_CBPCA_DATA_REQ,
                                    (VOS_UINT8 *)pstRtpdu,
                                    ulMemLen);

    if (VOS_OK != ulRslt)
    {
        CSIMA_ERROR_LOG("CSIMA_UiccRtpduMsg: send RTPDU fail");
    }

    /*lint -e534*/
    VOS_MemFree(WUEPS_PID_CSIMA, pstRtpdu);
    /*lint +e534*/

    if (CSIMA_EVENTLIST_NEED_RESEND == g_enEventListReSendFlag)
    {
        g_enEventListReSendFlag = CSIMA_EVENTLIST_RESENT;
        SI_STK_CbpSetupEventListCmdSnd();
    }

    return ulRslt;
}


VOS_UINT32 CSIMA_CBP_HandshakeReqMsg(VOS_VOID)
{
    VOS_UINT32                          ulRslt;
    CSIMA_CBP_UICC_MSGID_ENUM_UINT32    enIPCMsgId;

    enIPCMsgId = CSIMA_CBP_UICC_HANDSHAKE_MSG;

    /* ����CBPCAģ��ӿڽ����ݷ���ȥ */
    ulRslt = CBPCA_SndDataToCbpca(WUEPS_PID_CSIMA,
                                  CSIMA_CBPCA_DATA_REQ,
                                  (VOS_UINT8 *)&enIPCMsgId,
                                  sizeof(enIPCMsgId));

    if (VOS_OK != ulRslt)
    {
        CSIMA_ERROR_LOG("CSIMA_CBP_HandshakeReqMsg: send Data fail");
    }


    return ulRslt;
}
VOS_UINT32  CSIMA_UiccResAccReqMsg(CSIMA_CBP_RESACC_REQ_MSG_STRU *pstMsg)
{
    VOS_UINT32                          ulResult;
    CSIMA_CBP_RESACC_RSP_MSG_STRU       stResAccRsp;
    USIMM_RACCESS_REQ_STRU             *pstReqMsg;
    VOS_UINT8                          *pucFilePath;
    VOS_UINT8                           i;

    /* lint -e534 */
    (VOS_VOID)VOS_MemSet(&stResAccRsp, 0, sizeof(stResAccRsp));
    /* lint +e534 */

    stResAccRsp.enIPCMsgId = CSIMA_CBP_UICC_RESACC_RSP_MSG;

    ulResult = USIMM_VsimIsActive();

    if ((0 != pstMsg->usPathLen % 2) || (VOS_TRUE == ulResult))
    {
        /* ��CBP�ظ�����ִ�д��� */
        stResAccRsp.usSWStatus = UIM_ERR_TIMEOUT;

        /* ����CBPCAģ��ӿڽ����ݷ���ȥ */
        ulResult = CBPCA_SndDataToCbpca(WUEPS_PID_CSIMA,
                                        CSIMA_CBPCA_DATA_REQ,
                                        (VOS_UINT8 *)&stResAccRsp,
                                        sizeof(stResAccRsp));
        return ulResult;
    }

    pstReqMsg = (USIMM_RACCESS_REQ_STRU *)VOS_AllocMsg(WUEPS_PID_CSIMA,
                                                       sizeof(USIMM_RACCESS_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstReqMsg)
    {
        CSIMA_ERROR_LOG("CSIMA_UiccResAccReqMsg: VOS_AllocMsg is Failed");

        /* ��CBP�ظ�����ִ�д��� */
        stResAccRsp.usSWStatus = UIM_ERR_TIMEOUT;

        /* ����CBPCAģ��ӿڽ����ݷ���ȥ */
        /*lint -e534*/
        (VOS_VOID)CBPCA_SndDataToCbpca(WUEPS_PID_CSIMA,
                             CSIMA_CBPCA_DATA_REQ,
                             (VOS_UINT8 *)&stResAccRsp,
                             sizeof(stResAccRsp));
        /*lint +e534*/

        return VOS_ERR;
    }

    /* �����Ϣ���� */
    pstReqMsg->stMsgHeader.ulReceiverPid= WUEPS_PID_USIM;
    pstReqMsg->stMsgHeader.enMsgName    = USIMM_RACCESS_REQ;
    pstReqMsg->stMsgHeader.enAppType    = USIMM_GUTL_APP;
    pstReqMsg->stMsgHeader.ulSendPara   = VOS_NULL;
    pstReqMsg->enCmdType                = pstMsg->ucCmd;
    pstReqMsg->usEfId                   = pstMsg->usFileId;
    pstReqMsg->ucP1                     = pstMsg->ucP1;
    pstReqMsg->ucP2                     = pstMsg->ucP2;
    pstReqMsg->ucP3                     = pstMsg->ucP3;
    pstReqMsg->usPathLen                = VOS_NULL;

    /* ����������� */
    if (0 != pstMsg->ucLen)
    {
        /*lint -e534*/
        (VOS_VOID)VOS_MemCpy(pstReqMsg->aucContent, pstMsg->aucData, pstMsg->ucLen);
        /*lint +e534*/
    }

    if (pstMsg->usPathLen > 2)
    {
        pstReqMsg->usPathLen = (pstMsg->usPathLen - 2) /((VOS_UINT16)(sizeof(VOS_UINT16))); /* ��ȥ���ֽڵ��ļ�ID */
    }

    pucFilePath = &(pstMsg->aucData[pstMsg->ucLen]);

    /* ���·����Ϣ */
    for (i = 0; i < pstReqMsg->usPathLen; i++)
    {
        pstReqMsg->ausPath[i] = ((pucFilePath[i*2] << 0x08) & 0xFF00) + pucFilePath[(i*2)+1];
    }

    ulResult = VOS_SendMsg(WUEPS_PID_CSIMA, pstReqMsg);

    if (VOS_OK != ulResult)
    {
        /* ��CBP�ظ�����ִ�д��� */
        stResAccRsp.usSWStatus = UIM_ERR_TIMEOUT;

        /* ����CBPCAģ��ӿڽ����ݷ���ȥ */
        ulResult = CBPCA_SndDataToCbpca(WUEPS_PID_CSIMA,
                                        CSIMA_CBPCA_DATA_REQ,
                                        (VOS_UINT8 *)&stResAccRsp,
                                        sizeof(stResAccRsp));
    }

    return ulResult;
}


VOS_UINT32  CSIMA_GetUiccAidAndChanNum(USIMM_AID_TYPE_ENUM_UINT32 enAidType,
                                                      VOS_UINT8 *pucAid, VOS_UINT8 *pucChanNum)
{
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulAIDLen = 0;

    ulResult = USIMM_GetAid(enAidType, &ulAIDLen, pucAid);

    if (VOS_OK != ulResult)
    {
        return ulResult;
    }

    ulResult = USIMM_GetUiccChanNumByAid(pucAid, ulAIDLen, pucChanNum);

    return ulResult;
}



VOS_UINT32 CSIMA_CBPEnvelopeSend(CSIMA_CBP_CTPDU_MSG_STRU *pstCtpduMsg)
{
    VOS_UINT32                          ulResult;
    CSIMA_CBP_RTPDU_MSG_STRU            stRtpdu;

    /*lint -e534*/
    VOS_MemSet(&stRtpdu, VOS_NULL, sizeof(stRtpdu));
    /*lint +e534*/

    stRtpdu.enIPCMsgId = CSIMA_CBP_UICC_RTPDU_MSG;

    if ((SI_STK_ENVELOPE_EVENTDOWN == pstCtpduMsg->aucData[0])
        && (TAF_NVIM_LC_RAT_COMBINED_CL != g_stLCEnableFlag.enRatCombined))
    {
       /* ��CBP�ظ�����ִ�гɹ� */
       stRtpdu.usSWStatus = 0x9000;

       /* ����CBPCAģ��ӿڽ����ݷ���ȥ */
       ulResult = CBPCA_SndDataToCbpca(WUEPS_PID_CSIMA,
                                       CSIMA_CBPCA_DATA_REQ,
                                       (VOS_UINT8 *)&stRtpdu,
                                       sizeof(stRtpdu));
        return ulResult;
    }

    ulResult = CSIMA_SendTPDUOnBaseChan(pstCtpduMsg);

    if (USIMM_API_SUCCESS != ulResult)
    {
        CSIMA_WARNING_LOG("CSIMA_CBPEnvelopeSend: CSIMA_SendTPDUOnBaseChan is Fail");
    }

    return ulResult;
}


VOS_UINT32 CSIMA_SendTPDUOnBaseChan(CSIMA_CBP_CTPDU_MSG_STRU *pstCtpduMsg)
{
    CSIMA_CBP_RTPDU_MSG_STRU            stRtpdu;
    VOS_UINT32                          ulResult;
    USIMM_TPDU_DATA_STRU                stTPDU;

    /*lint -e534*/
    VOS_MemSet(&stRtpdu, VOS_NULL, sizeof(stRtpdu));

    VOS_MemSet(&stTPDU, VOS_NULL, sizeof(stTPDU));
    /*lint +e534*/

    stRtpdu.enIPCMsgId = CSIMA_CBP_UICC_RTPDU_MSG;

    /* ������� */
    if ((g_stCBPCardStatus.ucCSIMChanNum != pstCtpduMsg->ucChanNum)
        ||(pstCtpduMsg->usDataLen > USIMM_TPDU_DATA_LEN_MAX))
    {
       /* ��CBP�ظ�����ִ�д��� */
       stRtpdu.usSWStatus = UIM_ERR_TIMEOUT;

       /* ����CBPCAģ��ӿڽ����ݷ���ȥ */
       ulResult = CBPCA_SndDataToCbpca(WUEPS_PID_CSIMA,
                                       CSIMA_CBPCA_DATA_REQ,
                                       (VOS_UINT8 *)&stRtpdu,
                                       sizeof(stRtpdu));

        return ulResult;
    }

    /*lint -e534*/
    (VOS_VOID)VOS_MemCpy(stTPDU.aucTPDUHead, pstCtpduMsg->aucCTPDUHdr, USIMM_TPDU_HEAD_LEN);
    /*lint +e534*/

    stTPDU.usDataLen = pstCtpduMsg->usDataLen;

    (VOS_VOID)VOS_MemCpy(stTPDU.aucData, pstCtpduMsg->aucData, pstCtpduMsg->usDataLen);

    ulResult = CSIMA_SendTPDUReqMsg(USIMM_UNLIMIT_AUTO, USIMM_CL_SENDPARA, &stTPDU);

    if (VOS_OK != ulResult)
    {
        /* ��CBP�ظ�����ִ�д��� */
        stRtpdu.usSWStatus = UIM_ERR_TIMEOUT;

        /* ����CBPCAģ��ӿڽ����ݷ���ȥ */
        ulResult = CBPCA_SndDataToCbpca(WUEPS_PID_CSIMA,
                                        CSIMA_CBPCA_DATA_REQ,
                                        (VOS_UINT8 *)&stRtpdu,
                                        sizeof(stRtpdu));
    }

    return ulResult;
}

VOS_UINT32 CSIMA_SendTPDUOnLogicChan(CSIMA_CBP_CTPDU_MSG_STRU *pstCtpduMsg)
{
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulSessionID;
    CSIMA_CBP_RTPDU_MSG_STRU            stRtpdu;
    VOS_UINT8                           ucChanNum;
    VOS_UINT8                           aucAid[USIMM_AID_LEN_MAX];
    USIMM_TPDU_DATA_STRU                stTPDU;

    /*lint -e534*/
    VOS_MemSet(&stRtpdu, 0, sizeof(stRtpdu));
    /*lint +e534*/

    stRtpdu.enIPCMsgId = CSIMA_CBP_UICC_RTPDU_MSG;

    /* ��ȡCSIM��AID��ͨ���� */
    ulResult = CSIMA_GetUiccAidAndChanNum(USIMM_AID_TYPE_CSIM, aucAid, &ucChanNum);

    if (VOS_OK != ulResult)
    {
        /* ��CBP�ظ�����ִ�д��� */
        stRtpdu.usSWStatus = UIM_ERR_TIMEOUT;

        /* ����CBPCAģ��ӿڽ����ݷ���ȥ */
        ulResult = CBPCA_SndDataToCbpca(WUEPS_PID_CSIMA,
                                        CSIMA_CBPCA_DATA_REQ,
                                        (VOS_UINT8 *)&stRtpdu,
                                        sizeof(stRtpdu));

        return ulResult;
    }

    /* ������� */
    if (ucChanNum != pstCtpduMsg->ucChanNum)
    {
       /* ��CBP�ظ�����ִ�д��� */
       stRtpdu.usSWStatus = UIM_ERR_TIMEOUT;

       /* ����CBPCAģ��ӿڽ����ݷ���ȥ */
       ulResult = CBPCA_SndDataToCbpca(WUEPS_PID_CSIMA,
                                       CSIMA_CBPCA_DATA_REQ,
                                       (VOS_UINT8 *)&stRtpdu,
                                       sizeof(stRtpdu));


        return ulResult;
    }

    /* ͨ��ͨ���Ż�ȡsessionID */
    USIMM_ChanNumToSessionId(pstCtpduMsg->ucChanNum, &ulSessionID);

    /*lint -e534*/
    VOS_MemCpy(stTPDU.aucTPDUHead, pstCtpduMsg->aucCTPDUHdr, USIMM_TPDU_HEAD_LEN);

    stTPDU.usDataLen = pstCtpduMsg->usDataLen;

    VOS_MemCpy(stTPDU.aucData, pstCtpduMsg->aucData, pstCtpduMsg->usDataLen);
    /*lint +e534*/

    ulResult = CSIMA_SendTPDUReqMsg(ulSessionID, USIMM_CGLA_SENDPARA, &stTPDU);

    if (VOS_OK != ulResult)
    {
        /* ��CBP�ظ�����ִ�д��� */
        stRtpdu.usSWStatus = UIM_ERR_TIMEOUT;

        /* ����CBPCAģ��ӿڽ����ݷ���ȥ */
        ulResult = CBPCA_SndDataToCbpca(WUEPS_PID_CSIMA,
                                        CSIMA_CBPCA_DATA_REQ,
                                        (VOS_UINT8 *)&stRtpdu,
                                        sizeof(stRtpdu));

    }

    return ulResult;
}
VOS_UINT32  CSIMA_UiccCtpduMsg(CSIMA_CBP_CTPDU_MSG_STRU *pstCtpduMsg)
{
    VOS_UINT32                          ulResult;

    /* EVENLOP����ͨ������ͨ���·� */
    if (CMD_INS_ENVELOPE == pstCtpduMsg->aucCTPDUHdr[INS])
    {
        ulResult = CSIMA_CBPEnvelopeSend(pstCtpduMsg);
    }
    /********* ��ENVELOP����ͨ��CGLA����TPDU�·���ȥ *********/
    else if (0 == g_stCBPCardStatus.ucCSIMChanNum)
    {
        ulResult = CSIMA_SendTPDUOnBaseChan(pstCtpduMsg);
    }
    else
    {
        ulResult = CSIMA_SendTPDUOnLogicChan(pstCtpduMsg);
    }

    return ulResult;
}


VOS_UINT32 CSIMA_CBP_TerminalResponseMsgProc(CSIMA_CBP_TERMINALRESPONSE_MSG_STRU *pstMsg)
{
    VOS_UINT32                          ulRslt;

    /* �޿�ʱֱ�ӷ���USIMMģ�鴦�� */
    if (USIMM_CARD_NOCARD == g_stCpbCardInfo.enCardType)
    {
        ulRslt = CSIMA_SendTerminalResponse((VOS_UINT8)pstMsg->usDataLen, pstMsg->aucData);
    }
    /* �п�ʱֱ�ӷ���STKģ�鴦����Ϊ��Ҫ���ͷ�STK��������ж�̬������ڴ� */
    else
    {
        ulRslt = SI_STK_CLSndTrMsg(pstMsg->usDataLen, pstMsg->aucData);
    }

    return ulRslt;
}


VOS_UINT32  CSIMA_CBPCADataIndProc(CBPCA_DATA_IND_MSG_STRU *pstMsg)
{
    VOS_UINT32                          *pulMsgId;
    VOS_UINT32                          ulResult = VOS_ERR;
    CSIMA_CBP_TERMINALRESPONSE_MSG_STRU *pstTR;

    pulMsgId = (VOS_UINT32 *)pstMsg->aucData;

    if (CSIMA_CBP_UICC_TERMINALRESPONSE_MSG == *pulMsgId)
    {
        pstTR = (CSIMA_CBP_TERMINALRESPONSE_MSG_STRU *)(pstMsg->aucData);

        /* �����ݷ��͵�STK��USIMMģ�鴦�� */
        ulResult = CSIMA_CBP_TerminalResponseMsgProc(pstTR);

        return ulResult;
    }

    if (CSIMA_CBP_UICC_RST_REQ_MSG == *pulMsgId)
    {
        /* ��CBP�����²�������RESET���� */
        if (TAF_NVIM_LC_RAT_COMBINED_CL != g_stLCEnableFlag.enRatCombined)
        {
            return VOS_OK;
        }

        /* ��RESET����USIMMģ�鴦�� */
        ulResult = CSIMA_SendActiveCardReqMsg();

        return ulResult;
    }

    if (CSIMA_CBP_UICC_CTPDU_MSG == *pulMsgId)
    {
        /* CBP����csimӦ�� */
        ulResult = CSIMA_UiccCtpduMsg((CSIMA_CBP_CTPDU_MSG_STRU *)(pstMsg->aucData));

        return ulResult;
    }

    if (CSIMA_CBP_UICC_RESACC_REQ_MSG == *pulMsgId)
    {
        /* CBP����usimӦ�� */
        ulResult = CSIMA_UiccResAccReqMsg((CSIMA_CBP_RESACC_REQ_MSG_STRU *)(pstMsg->aucData));

        return ulResult;
    }

    /* ���ִ��� */
    if (CSIMA_CBP_UICC_HANDSHAKE_MSG == *pulMsgId)
    {
        ulResult = CSIMA_CBP_HandshakeReqMsg();

        return ulResult;
    }

    /* ��¼���� */

    return ulResult;
}
VOS_UINT32  CSIMA_CBPCAMsgProc(CSIMA_CBP_MSG_STRU *pstMsg)
{
    VOS_UINT32                          ulResult;

    switch (pstMsg->ulIPCMsgId)
    {
        case CBPCA_CSIMA_DATA_IND:
            ulResult = CSIMA_CBPCADataIndProc((CBPCA_DATA_IND_MSG_STRU *)pstMsg);
            break;
        default:
            ulResult = VOS_ERR;
            break;
    }

    return ulResult;
}


VOS_UINT32  CSIMA_OpenChanCnfProc(USIMM_OPENCHANNEL_CNF_STRU *pstMsg)
{
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulChanNum;
    VOS_UINT16                          usCardType = 0;

    /* ��ͨ��ʧ�ܣ��ϱ���״̬������ */
    if (VOS_OK != pstMsg->stCmdResult.ulResult)
    {
        CSIMA_CardStatusMsgSend((VOS_UINT16)CSIMA_CBP_CARD_NOT_READY, ((VOS_UINT16)CSIMA_CBP_USIM_CARD |(VOS_UINT16)CSIMA_CBP_UICC_CARD));

        return VOS_ERR;
    }

    /* ����sessionID��ȡͨ���� */
    USIMM_SessionIdToChanNum(pstMsg->ulSessionID, &ulChanNum);

    /* ͨ���ŷǷ� */
    if (USIMM_CHANNEL_INVALID_NUM == ulChanNum)
    {
        /* �ϱ���״̬������(�ϱ�UICC����ֻ��USIMӦ�ã�VIA������ʿ�) */
        CSIMA_CardStatusMsgSend((VOS_UINT16)CSIMA_CBP_CARD_READY, ((VOS_UINT16)CSIMA_CBP_USIM_CARD |(VOS_UINT16)CSIMA_CBP_UICC_CARD));

        return VOS_ERR;
    }

    ulResult = CSIMA_GetUiccAidAndChanNum(USIMM_AID_TYPE_CSIM,
                                          g_stCBPCardStatus.aucCSIMAID,
                                          &g_stCBPCardStatus.ucCSIMChanNum);

    /* ���û��CSIM��Ӧ�� */
    if (VOS_OK != ulResult)
    {
        /* �ϱ���״̬������(�ϱ�UICC����ֻ��USIMӦ�ã�VIA������ʿ�) */
        CSIMA_CardStatusMsgSend((VOS_UINT16)CSIMA_CBP_CARD_READY, ((VOS_UINT16)CSIMA_CBP_USIM_CARD |(VOS_UINT16)CSIMA_CBP_UICC_CARD));

        return VOS_ERR;
    }

    /* �õ�USIMӦ��*/
    ulResult = CSIMA_GetUiccAidAndChanNum(USIMM_AID_TYPE_USIM,
                                          g_stCBPCardStatus.aucUSIMAID,
                                          &g_stCBPCardStatus.ucUSIMChanNum);

    /* ���û��USIM��Ӧ�� */
    if (VOS_OK != ulResult)
    {
        /* �ϱ���״̬������(�ϱ�UICC����ֻ��USIMӦ�ã�VIA������ʿ�) */
        CSIMA_CardStatusMsgSend((VOS_UINT16)CSIMA_CBP_CARD_NOT_READY, (VOS_UINT16)CSIMA_CBP_UNKNOWN_CARD);

        return VOS_ERR;
    }

    usCardType = ((VOS_UINT16)CSIMA_CBP_UICC_CARD | (VOS_UINT16)CSIMA_CBP_USIM_CARD| (VOS_UINT16)CSIMA_CBP_CSIM_CARD);

    ulResult = CSIMA_GetUiccAidAndChanNum(USIMM_AID_TYPE_ISIM,
                                          g_stCBPCardStatus.aucISIMAID,
                                          &g_stCBPCardStatus.ucISIMChanNum);

    /* ���û��ISIM��Ӧ�� */
    if (VOS_OK != ulResult)
    {
        /* ISIM�����õĻ���0xff���� */
        /*lint -e534*/
        VOS_MemSet(g_stCBPCardStatus.aucISIMAID, (VOS_CHAR)VOS_NULL_BYTE, sizeof(g_stCBPCardStatus.aucISIMAID));
        /*lint +e534*/

        g_stCBPCardStatus.ucISIMChanNum = CSIMA_CARD_CHANEL_NULL;
    }
    else
    {
        usCardType = usCardType | CSIMA_CBP_ISIM_CARD;
    }

    /* ����CBPCAģ��ӿڽ����ݷ���ȥ */
    CSIMA_CardStatusMsgSend((VOS_UINT16)CSIMA_CBP_CARD_READY, usCardType);

    return VOS_OK;
}

/*****************************************************************************
�� �� ��  : CSIMA_SendTPDUCnfMsg
��������  : ����USIMģ�鷵�ص�TPDU���
�������  : pstMsg -- ָ��TPDU�������ݽṹ
�������  : ��
�� �� ֵ  : VOS_OK/VOS_ERR
History     :
1.��    ��  : 2014��01��16��
  ��    ��  : zhuli
  �޸�����  : Create
*****************************************************************************/
VOS_UINT32 CSIMA_SendTPDUCnfMsg(USIMM_SENDTPDUDATA_CNF_STRU *pstMsg)
{
    VOS_UINT32              ulResult = VOS_OK;

    if (CSIMA_CBP_CARD_STATUS_BUTT == g_stCBPCardStatus.enStatus)   /*��һ���ϱ�*/
    {
        if(pstMsg->stRspData.aucInputCmd[INS] != CMD_INS_SELECT)
        {
            CSIMA_WARNING_LOG("CSIMA_SendTPDUCnfMsg: The TPDU Cnf is Error");

            return VOS_ERR;
        }

        if((VOS_OK == pstMsg->stCmdResult.ulResult)
            &&(((0x90 == pstMsg->stRspData.ucSW1)
                &&(0x00 == pstMsg->stRspData.ucSW2))
                ||(0x91 == pstMsg->stRspData.ucSW1)))
        {
            if(USIMM_SIM_CLA == pstMsg->stRspData.aucInputCmd[CLA])
            {
                g_stCBPCardStatus.ucCSIMChanNum = 0;

                CSIMA_CardStatusMsgSend(CSIMA_CBP_CARD_READY, CSIMA_CBP_UIM_CARD);
            }
            else
            {
                g_stCBPCardStatus.ucCSIMChanNum = (pstMsg->stRspData.aucInputCmd[CLA]&0x1F);

                CSIMA_CardStatusMsgSend(CSIMA_CBP_CARD_READY, ((VOS_UINT16)CSIMA_CBP_CSIM_CARD|(VOS_UINT16)CSIMA_CBP_UICC_CARD));
            }
        }
        else
        {
            CSIMA_CardStatusMsgSend(CSIMA_CBP_CARD_NOT_READY, CSIMA_CBP_UNKNOWN_CARD);
        }
    }
    else
    {
        CSIMA_NORMAL_LOG("CSIMA_SendTPDUCnfMsg: The TPDU Cnf send to CBP");

        ulResult = CSIMA_UiccRtpduMsg(pstMsg->stCmdResult.ulResult,
                                      pstMsg->stRspData.ucSW1,
                                      pstMsg->stRspData.ucSW2,
                                      (VOS_UINT8)pstMsg->stRspData.ulDataLen,
                                      pstMsg->stRspData.aucRspData);
    }

    return ulResult;
}
VOS_UINT32  CSIMA_UsimMsgProc(CSIMA_CBP_MSG_STRU *pstMsg)
{
    VOS_UINT32                          ulResult;
    USIMM_STKENVELOPE_CNF_STRU          *pstEnvelopCnf;
    USIMM_SENDTPDUDATA_CNF_STRU         *pstSendTpduCnf;

    switch (pstMsg->ulIPCMsgId)
    {
        case USIMM_RACCESS_CNF:
            ulResult = CSIMA_UiccResAccRspMsg((USIMM_RACCESS_CNF_STRU *)pstMsg);
            break;

        case USIMM_OPENCHANNEL_CNF:
            ulResult = CSIMA_OpenChanCnfProc((USIMM_OPENCHANNEL_CNF_STRU *)pstMsg);
            break;

        case USIMM_STKENVELOPE_CNF:
            pstEnvelopCnf = (USIMM_STKENVELOPE_CNF_STRU *)pstMsg;

            ulResult = CSIMA_UiccRtpduMsg(pstEnvelopCnf->stCmdResult.ulResult,
                                          pstEnvelopCnf->ucSW1,
                                          pstEnvelopCnf->ucSW2,
                                          pstEnvelopCnf->ucDataLen,
                                          pstEnvelopCnf->aucData);
            break;

        /* ���¿�֮���ȫ�ֱ������ */
        case USIMM_ACTIVECARD_CNF:
            ulResult = CSIMA_Init();
            break;

        case USIMM_SENDTPDUDATA_CNF:
            pstSendTpduCnf = (USIMM_SENDTPDUDATA_CNF_STRU *)pstMsg;

            if (USIMM_CL_SENDPARA == pstSendTpduCnf->stCmdResult.ulSendPara)
            {
                ulResult = CSIMA_SendTPDUCnfMsg(pstSendTpduCnf);
            }
            else
            {
                ulResult = CSIMA_UiccRtpduMsg(pstSendTpduCnf->stCmdResult.ulResult,
                                              pstSendTpduCnf->stRspData.ucSW1,
                                              pstSendTpduCnf->stRspData.ucSW2,
                                              (VOS_UINT8)pstSendTpduCnf->stRspData.ulDataLen,
                                              pstSendTpduCnf->stRspData.aucRspData);
            }
            break;

        case USIMM_STKTERMINALRSP_CNF:
            ulResult = CSIMA_UiccRtpduMsg(((USIMM_STKTERMINALRSP_CNF_STRU *)pstMsg)->stCmdResult.ulResult,
                                          ((USIMM_STKTERMINALRSP_CNF_STRU *)pstMsg)->ucSW1,
                                          ((USIMM_STKTERMINALRSP_CNF_STRU *)pstMsg)->ucSW2,
                                          VOS_NULL,
                                          VOS_NULL_PTR);
            break;

        default:
            /* ��ӡ���� */
            ulResult = VOS_ERR;
            break;
    }

    return ulResult;
}


VOS_VOID CSIMA_CBPResetInd(CSIMA_CBPCA_MODEM_RESET_ENUM_UINT32 enModemReset)
{
    CSIMA_CBPCA_MODEM_RESET_IND_MSG_STRU    *pstResetInd;

    pstResetInd = (CSIMA_CBPCA_MODEM_RESET_IND_MSG_STRU *)VOS_AllocMsg(WUEPS_PID_CSIMA,
                                                                       sizeof(CSIMA_CBPCA_MODEM_RESET_IND_MSG_STRU));

    if (VOS_NULL_PTR == pstResetInd)
    {
        CSIMA_ERROR_LOG("CSIMA_CBPResetInd: Alloc msg fail!");

        return;
    }

    /* �����Ϣ���� */
    pstResetInd->ulReceiverPid      = WUEPS_PID_CBPCA;
    pstResetInd->enMsgType          = CSIMA_CBPCA_MODEM_RESET_IND;
    pstResetInd->enModemReset       = enModemReset;

    if (VOS_OK != VOS_SendMsg(WUEPS_PID_CSIMA, pstResetInd))
    {
        CSIMA_ERROR_LOG("CSIMA_CBPResetInd: Send msg fail!");

        return;
    }

    return;
}
VOS_UINT32  CSIMA_ATResetIndProc(AT_CSIMA_RESET_STATUS_IND_MSG_STRU *pstMsg)
{
    VOS_UINT32                          ulResult;

    /* �յ�CBP��λָʾ��Ҫ͸����CBPCA */
    CSIMA_CBPResetInd(pstMsg->enVIAModemStatus);

    /* Add by H00300778 for MultiAppSync Begin 2015-05-12 */
    g_bNeedCardStatus = VOS_TRUE;
    /* Add by H00300778 for MultiAppSync End 2015-05-12 */

    /* ��λ�ɹ���CBP�ϱ���״̬ */
    if (CBP_MODEM_RESET_SUCC == pstMsg->enVIAModemStatus)
    {
        /* δ�ϱ�����״̬�Ļ������PIH�ϱ��˿�״̬���ϱ� */
        if (CSIMA_CBP_CARD_STATUS_BUTT == g_stCBPCardStatus.enStatus)
        {
            CSIMA_INFO_LOG("CSIMA_ATResetIndProc: have no card status Ind");

            /* Add by H00300778 for MultiAppSync Begin 2015-05-12 */
            CSIMA_CardStatusMsgSend(CSIMA_CBP_CARD_NOT_READY, CSIMA_CBP_UNKNOWN_CARD);
            /* Add by H00300778 for MultiAppSync End 2015-05-12 */

            return VOS_OK;
        }

        /* ����CBPCAģ��ӿڽ����ݷ���ȥ */
        ulResult = CBPCA_SndDataToCbpca(WUEPS_PID_CSIMA,
                                    CSIMA_CBPCA_DATA_REQ,
                                    (VOS_UINT8 *)&g_stCBPCardStatus,
                                    sizeof(g_stCBPCardStatus));

        return ulResult;
    }

    return VOS_OK;
}


VOS_UINT32  CSIMA_ATMsgProc(CSIMA_CBP_MSG_STRU *pstMsg)
{
    VOS_UINT32                          ulResult = VOS_ERR;

    switch (pstMsg->ulIPCMsgId)
    {
        case AT_CSIMA_RESET_IND_MSG:
            ulResult = CSIMA_ATResetIndProc((AT_CSIMA_RESET_STATUS_IND_MSG_STRU *)pstMsg);
            break;

        default:
            ulResult = VOS_ERR;
            break;
    }

    return ulResult;
}


VOS_UINT32  CSIMA_ProactiveIndProc(CSIMA_STK_PROACTIVE_CMD_MSG_STRU *pstMsg)
{
    VOS_UINT32                          ulResult;
    CSIMA_CBP_PROACTIVE_CMD_MSG_STRU    stProactiveCmd;

    /*lint -e534*/
    VOS_MemSet(&stProactiveCmd, 0, sizeof(stProactiveCmd));
    /*lint +e534*/

    stProactiveCmd.enIPCMsgId = CSIMA_CBP_UICC_PROACTIVE_CMD_MSG;
    stProactiveCmd.usDataLen  = (VOS_UINT16)pstMsg->ulLen;

    if (0 != stProactiveCmd.usDataLen)
    {
        /*lint -e534*/
        VOS_MemCpy(stProactiveCmd.aucData, pstMsg->aucProactiveCmd, stProactiveCmd.usDataLen);
        /*lint +e534*/
    }

    ulResult = CBPCA_SndDataToCbpca(WUEPS_PID_CSIMA,
                                    CSIMA_CBPCA_DATA_REQ,
                                    (VOS_UINT8 *)&stProactiveCmd,
                                    (sizeof(CSIMA_CBP_PROACTIVE_CMD_MSG_STRU) - STK_PROACTIVE_DATA_LEN + stProactiveCmd.usDataLen));

    return ulResult;
}


VOS_UINT32  CSIMA_STKMsgProc(CSIMA_CBP_MSG_STRU *pstMsg)
{
    VOS_UINT32                          ulResult = VOS_ERR;

    switch (pstMsg->ulIPCMsgId)
    {
        case CSIMA_CBP_UICC_PROACTIVE_CMD_MSG:
            /* ��������ֱ�ӱ���CBPCAģ�� */
            ulResult = CSIMA_ProactiveIndProc((CSIMA_STK_PROACTIVE_CMD_MSG_STRU *)pstMsg);
            break;

        default:
            ulResult = VOS_ERR;
            break;
    }

    return ulResult;
}

/*****************************************************************************
�� �� ��  : CSIMA_OpenCSIMOnLogicChannel
��������  : CSIMAģ���CSIM���߼�ͨ��
�������  : ulAIDLen -- CSIM AID����
            pucAID -- CSIM AID
�������  : ��
�� �� ֵ  : ��
History     :
1.��    ��  : 2014��01��16��
  ��    ��  : zhuli
  �޸�����  : Create
*****************************************************************************/

VOS_VOID CSIMA_OpenCSIMOnLogicChannel(VOS_UINT32 ulAIDLen, VOS_UINT8 *pucAID)
{
    VOS_UINT32                          ulResult;

    if (g_stCBPCardStatus.ucCSIMChanNum != CSIMA_CARD_CHANEL_NULL)  /*֮ǰ��ͨ��*/
    {
        CSIMA_CardStatusMsgSend(CSIMA_CBP_CARD_READY, g_stCBPCardStatus.usCardType);
    }
    else
    {
        /* ����USIM API���߼�ͨ�� */
        ulResult = CSIMA_SendOpenChannelReqMsg(ulAIDLen, pucAID);

        if (USIMM_API_SUCCESS != ulResult)
        {
            /* �ϱ���״̬������ */
            CSIMA_CardStatusMsgSend(CSIMA_CBP_CARD_NOT_READY, CSIMA_CBP_UNKNOWN_CARD);
        }
    }

    return;
}

/*****************************************************************************
�� �� ��  : CSIMA_OpenCSIMOnBaseChannel
��������  : CSIMAģ���CSIM�Ļ����߼�ͨ��
�������  : ulAIDLen -- CSIM AID����
            pucAID -- CSIM AID
�������  : ��
�� �� ֵ  : ��
History     :
1.��    ��  : 2014��01��16��
  ��    ��  : zhuli
  �޸�����  : Create
*****************************************************************************/

VOS_VOID CSIMA_OpenCSIMOnBaseChannel(VOS_UINT32 ulAIDLen, VOS_UINT8 *pucAID)
{
    VOS_UINT32                          ulResult;
    USIMM_TPDU_DATA_STRU                stTPDU;

    /*����Э���·�TPDU����*/
    stTPDU.aucTPDUHead[CLA] = 0x00;
    stTPDU.aucTPDUHead[INS] = 0xA4;
    stTPDU.aucTPDUHead[P1]  = 0x04;
    stTPDU.aucTPDUHead[P2]  = 0x04;
    stTPDU.aucTPDUHead[P3]  = (VOS_UINT8)ulAIDLen;
    stTPDU.usDataLen        = (VOS_UINT16)ulAIDLen;

    (VOS_VOID)VOS_MemCpy(stTPDU.aucData, pucAID, stTPDU.aucTPDUHead[P3]);

    /* ���� API���·����� */
    ulResult = CSIMA_SendTPDUReqMsg(USIMM_UNLIMIT_AUTO, USIMM_CL_SENDPARA, &stTPDU);

    if (VOS_OK != ulResult)
    {
        /* �ϱ���״̬������ */
        CSIMA_CardStatusMsgSend(CSIMA_CBP_CARD_NOT_READY, CSIMA_CBP_UNKNOWN_CARD);
    }

    return;
}

/*****************************************************************************
�� �� ��  : CSIMA_SelectDFCdma
��������  : CSIMAģ���UIM��DF
�������  : ��
�������  : ��
�� �� ֵ  : ��
History     :
1.��    ��  : 2014��01��16��
  ��    ��  : zhuli
  �޸�����  : Create
*****************************************************************************/

VOS_VOID CSIMA_SelectDFCdma(VOS_VOID)
{
    VOS_UINT32                          ulResult;
    USIMM_TPDU_DATA_STRU                stTPDU;
    VOS_UINT8                           aucData[2] = {0x7F, 0x25};

    /*����Э����д����*/
    stTPDU.aucTPDUHead[CLA]= USIMM_SIM_CLA;
    stTPDU.aucTPDUHead[INS]= CMD_INS_SELECT;
    stTPDU.aucTPDUHead[P1] = 0x00;
    stTPDU.aucTPDUHead[P2] = 0x00;
    stTPDU.aucTPDUHead[P3] = sizeof(aucData);

    (VOS_VOID)VOS_MemCpy(stTPDU.aucData, aucData, sizeof(aucData));

    stTPDU.usDataLen = sizeof(aucData);

    /* ����USIM API���·����� */
    ulResult = CSIMA_SendTPDUReqMsg(USIMM_UNLIMIT_AUTO, USIMM_CL_SENDPARA, &stTPDU);

    if (VOS_OK != ulResult)
    {
        /* �ϱ���״̬������ */
        CSIMA_CardStatusMsgSend(CSIMA_CBP_CARD_NOT_READY, CSIMA_CBP_UNKNOWN_CARD);
    }

    return;
}

/*****************************************************************************
�� �� ��  : CSIMA_CardStatusMsgSend
��������  : CSIMAģ���ϱ���״̬��CBP
�������  : enCardStatus:��״̬
            enCardType:������
�������  : ��
�� �� ֵ  : ��
History     :
1.��    ��  : 2014��01��16��
  ��    ��  : zhuli
  �޸�����  : Create
*****************************************************************************/

VOS_VOID CSIMA_CardStatusMsgSend(
    CSIMA_CBP_CARD_STATUS_ENUM_UINT16   enCardStatus,
    CSIMA_CBP_CARD_TYPE_ENUM_UINT16     enCardType)
{
    VOS_UINT32                          ulResult;

    g_stCBPCardStatus.enStatus      = enCardStatus;

    g_stCBPCardStatus.usCardType    = enCardType;

    /* Add by H00300778 for MultiAppSync Begin 2015-05-12 */
    if ((TAF_NVIM_LC_RAT_COMBINED_CL != g_stLCEnableFlag.enRatCombined)
     && (VOS_FALSE == g_bNeedCardStatus))
    {
        CSIMA_ERROR_LOG("CSIMA_CardStatusMsgSend: GUL Mode and No AT Command");

        return;
    }
    /* Add by H00300778 for MultiAppSync End 2015-05-12 */

    /* ����CBPCAģ��ӿڽ����ݷ���ȥ */
    ulResult = CBPCA_SndDataToCbpca(WUEPS_PID_CSIMA,
                                    CSIMA_CBPCA_DATA_REQ,
                                    (VOS_UINT8 *)&g_stCBPCardStatus,
                                    sizeof(g_stCBPCardStatus));

    if (VOS_OK != ulResult)
    {
        CSIMA_ERROR_LOG("CSIMA_CardStatusMsgSend: Send Msg To CBPCA fail");
    }

    if (CSIMA_CBP_CARD_READY == enCardStatus)
    {
        g_enEventListReSendFlag = CSIMA_EVENTLIST_NEED_RESEND;
    }

    /* Add by H00300778 for MultiAppSync Begin 2015-05-12 */
    if (CSIMA_CBP_CARD_NOT_READY == enCardStatus)
    {
        (VOS_VOID)CSIMA_Init();
    }

    CSIMA_DataHook(sizeof(g_stCBPCardStatus), (VOS_UINT8 *)(&g_stCBPCardStatus));
    /* Add by H00300778 for MultiAppSync End 2015-05-12 */

    return;
}

/*****************************************************************************
�� �� ��  : CSIMA_FirstCardStatusInd
��������  : CSIMAģ���״��յ���״̬��Ϣ
�������  : pstMsg:��״̬��Ϣ
�������  : ��
�� �� ֵ  : ��
History     :
1.��    ��  : 2014��01��16��
  ��    ��  : zhuli
  �޸�����  : Create
*****************************************************************************/
VOS_VOID CSIMA_FirstCardStatusInd(USIMM_CARDSTATUS_IND_STRU *pstMsg)
{
    VOS_UINT32                          ulCSIMExistFlag;
    VOS_UINT8                           aucCsimAid[USIMM_AID_LEN_MAX];
    VOS_UINT32                          ulAidLen;
    VOS_UINT32                          ulATRLen = 0;
    /* Add by H00300778 for MultiAppSync Begin 2015-05-12 */
    VOS_UINT8                           aucATRData[SI_ATR_MAX_LEN] = {0};
    SCI_ATRINFO_S                       stSCIATRInfo;
    VOS_INT32                           lResult = VOS_OK;
    /* Add by H00300778 for MultiAppSync End 2015-05-12 */

    ulCSIMExistFlag = USIMM_GetAid(USIMM_AID_TYPE_CSIM, &ulAidLen, aucCsimAid);

    if (USIMM_CARD_NOCARD == pstMsg->stUsimSimInfo.enCardType)    /*�����޿������ǵ�CSIM������UIM*/
    {
        /* Add by H00300778 for MultiAppSync Begin 2015-05-12 */
        lResult = (VOS_INT32)mdrv_sci_get_atr((VOS_ULONG*)&ulATRLen, aucATRData, &stSCIATRInfo);

        if ((VOS_OK != lResult)||(ulATRLen > SI_ATR_MAX_LEN))
        {
            /* �ϱ���״̬������ */
            CSIMA_CardStatusMsgSend(CSIMA_CBP_CARD_NOT_READY, ((VOS_UINT16)CSIMA_CBP_UICC_CARD|(VOS_UINT16)CSIMA_CBP_USIM_CARD));

            return;
        }
        /* Add by H00300778 for MultiAppSync End 2015-05-12 */

        if (VOS_OK == ulCSIMExistFlag)  /*CSIM���ڣ��ڻ���ͨ����Ӧ��*/
        {
            CSIMA_OpenCSIMOnBaseChannel(ulAidLen, aucCsimAid);
        }
        else                            /*CSIM�����ڣ����԰���UIMѡ��*/
        {
            CSIMA_SelectDFCdma();
        }
    }
    else if (USIMM_CARD_USIM == pstMsg->stUsimSimInfo.enCardType) /*������UICC�����ǵ�USIM*/
    {
        if (VOS_OK == ulCSIMExistFlag)  /*CSIM���ڣ����߼�ͨ����Ӧ��*/
        {
            if (USIMM_CARD_SERVIC_AVAILABLE != pstMsg->stUsimSimInfo.enCardService)
            {
                /* �ϱ���״̬��ʼ���� */
                CSIMA_CardStatusMsgSend(CSIMA_CBP_CARD_BOOTUP, ((VOS_UINT16)CSIMA_CBP_UICC_CARD|(VOS_UINT16)CSIMA_CBP_USIM_CARD|(VOS_UINT16)CSIMA_CBP_CSIM_CARD));
            }
            else
            {
                CSIMA_OpenCSIMOnLogicChannel(ulAidLen, aucCsimAid);
            }
        }
        else                            /*CSIM�����ڣ��ϱ��޿�*/
        {
            /* �ϱ���״̬������(�ϱ�UICC����ֻ��USIMӦ�ã�VIA������ʿ�) */
            CSIMA_CardStatusMsgSend(CSIMA_CBP_CARD_NOT_READY, ((VOS_UINT16)CSIMA_CBP_UICC_CARD|(VOS_UINT16)CSIMA_CBP_USIM_CARD));
        }
    }
    else if (USIMM_CARD_SIM == pstMsg->stUsimSimInfo.enCardType)  /*SIM����Ӧ���ǹ��ʿ�����GUL��ʼ�����ϱ��޿�*/
    {
        /* �ϱ���״̬������ */
        CSIMA_CardStatusMsgSend(CSIMA_CBP_CARD_NOT_READY, CSIMA_CBP_SIM_CARD);
    }
    else                                            /*����������*/
    {
        /* �ϱ���״̬������ */
        CSIMA_CardStatusMsgSend(CSIMA_CBP_CARD_NOT_READY, CSIMA_CBP_UNKNOWN_CARD);
    }

    return;
}

/*****************************************************************************
�� �� ��  : CSIMA_CardStatusInd
��������  : CSIMAģ����״��յ���״̬��Ϣ
�������  : pstMsg:��״̬��Ϣ
�������  : ��
�� �� ֵ  : ��
History     :
1.��    ��  : 2014��01��16��
  ��    ��  : zhuli
  �޸�����  : Create
*****************************************************************************/
VOS_VOID CSIMA_CardStatusInd(USIMM_CARDSTATUS_IND_STRU *pstMsg)
{
    VOS_UINT32                          ulCSIMExistFlag;
    VOS_UINT8                           aucCsimAid[USIMM_AID_LEN_MAX];
    VOS_UINT32                          ulAidLen;

    /*ֻ����USIMУ��ɹ�PIN֮��Ż��ϱ����״̬*/
    if ((CSIMA_CBP_CARD_BOOTUP == g_stCBPCardStatus.enStatus)&&(USIMM_CARD_SERVIC_AVAILABLE == pstMsg->stUsimSimInfo.enCardService))
    {
        ulCSIMExistFlag = USIMM_GetAid(USIMM_AID_TYPE_CSIM, &ulAidLen, aucCsimAid);

        if(VOS_OK == ulCSIMExistFlag)
        {
            CSIMA_OpenCSIMOnLogicChannel(ulAidLen, aucCsimAid);
        }
        else
        {
            CSIMA_CardStatusMsgSend(CSIMA_CBP_CARD_NOT_READY, g_stCBPCardStatus.usCardType);
        }
    }
    else
    {
        if (USIMM_CARD_NOCARD == pstMsg->stUsimSimInfo.enCardType)    /*����*/
        {
            CSIMA_CardStatusMsgSend(CSIMA_CBP_CARD_NOT_READY, CSIMA_CBP_UNKNOWN_CARD);
        }
        else if (USIMM_CARD_SERVIC_AVAILABLE != pstMsg->stUsimSimInfo.enCardService)      /*PIN�ֿ���*/
        {
            CSIMA_CardStatusMsgSend(CSIMA_CBP_CARD_BOOTUP, g_stCBPCardStatus.usCardType);
        }
        else    /*����״̬����*/
        {
            CSIMA_ERROR_LOG("CSIMA_CardStatusInd: Receive Card status");
        }
    }

    return;
}


VOS_UINT32  CSIMA_PIHMsgProc(USIMM_CARDSTATUS_IND_STRU *pstMsg)
{
    if (USIMM_CARDSTATUS_IND != pstMsg->ulMsgName)
    {
        /* ��¼����Ŀǰֻ����PIHģ�鷢�����Ŀ�״̬��Ϣ */
        return VOS_ERR;
    }

    /* Add by H00300778 for MultiAppSync Begin 2015-05-12 */
    CSIMA_DataHook(sizeof(g_stCBPCardStatus), (VOS_UINT8 *)(&g_stCBPCardStatus));
    /* Add by H00300778 for MultiAppSync End 2015-05-12 */

    if (CSIMA_CBP_CARD_STATUS_BUTT == g_stCBPCardStatus.enStatus)   /*��һ���ϱ�*/
    {
        CSIMA_FirstCardStatusInd(pstMsg);
    }
    else
    {
        CSIMA_CardStatusInd(pstMsg);
    }

    /* ���濨��Ϣ����USIM��Ϊ׼ */
    g_stCpbCardInfo.enPhyType   = pstMsg->enPhyCardType;
    g_stCpbCardInfo.enCardType  = pstMsg->stUsimSimInfo.enCardType;
    g_stCpbCardInfo.enSvcStatus = pstMsg->stUsimSimInfo.enCardService;

    return VOS_OK;
}
VOS_VOID CSIMA_PidMsgProc(CSIMA_CBP_MSG_STRU *pstMsg)
{
    VOS_UINT32                          ulResult = VOS_ERR;

    /*�����CL���ܹرղ���Ҫ���������Ϣ*/
    if (VOS_TRUE != g_stLCEnableFlag.ucLCEnableFlg)
    {
        CSIMA_WARNING_LOG("CSIMA_PidMsgProc:feature LC is disable");

        return;
    }

    switch (pstMsg->ulSenderPid)
    {
        case WUEPS_PID_AT:
            ulResult = CSIMA_ATMsgProc(pstMsg);
            break;

        case WUEPS_PID_USIM:
            ulResult = CSIMA_UsimMsgProc(pstMsg);
            break;

        case MAPS_STK_PID:
            ulResult = CSIMA_STKMsgProc(pstMsg);
            break;

        case MAPS_PIH_PID:
            ulResult = CSIMA_PIHMsgProc((USIMM_CARDSTATUS_IND_STRU *)pstMsg);
            break;

        case WUEPS_PID_CBPCA:
            ulResult = CSIMA_CBPCAMsgProc(pstMsg);
            break;

        default:
            CSIMA_WARNING_LOG("CSIMA_PidMsgProc:Default Unknow PID Msg");
            break;
    }

    if (VOS_OK != ulResult)
    {
        /* ��¼���� */
        CSIMA_ERROR_LOG("CSIMA_PidMsgProc:FAIL to proc msg");
    }

    return;
}



VOS_UINT32 CSIMA_Init(VOS_VOID)
{
    /* ģ��ȫ�ֱ�����ʼ�� */
    /*lint -e534*/
    VOS_MemSet(&g_stCBPCardStatus, 0, sizeof(g_stCBPCardStatus));
    /*lint +e534*/

    g_stCBPCardStatus.enIPCMsgId    = CSIMA_CBP_UICC_STATUS_IND_MSG;
    g_stCBPCardStatus.enStatus      = CSIMA_CBP_CARD_STATUS_BUTT;
    g_stCBPCardStatus.ucCSIMChanNum = CSIMA_CARD_CHANEL_NULL;
    g_stCBPCardStatus.ucUSIMChanNum = CSIMA_CARD_CHANEL_NULL;
    g_stCBPCardStatus.ucISIMChanNum = CSIMA_CARD_CHANEL_NULL;

    if (NV_OK != NV_Read(en_NV_Item_LC_Ctrl_PARA, &g_stLCEnableFlag, sizeof(TAF_NV_LC_CTRL_PARA_STRU)))
    {
        g_stLCEnableFlag.ucLCEnableFlg = VOS_FALSE;
        g_stLCEnableFlag.enRatCombined = TAF_NVIM_LC_RAT_COMBINED_GUL;
    }

    return VOS_OK;
}
VOS_UINT32 CSIMA_PidInit(enum VOS_INIT_PHASE_DEFINE ip)
{
    switch( ip )
    {
        case VOS_IP_INITIAL:
            return CSIMA_Init();

        /* Add by H00300778 for MultiAppSync Begin 2015-05-12 */
        case VOS_IP_RESTART:
            /* ��PIHģ��ע�Ῠ״̬�ϱ�PID */
            if (VOS_OK != PIH_RegUsimCardStatusIndMsg(WUEPS_PID_CSIMA))
            {
                CSIMA_ERROR_LOG("CSIMA_PidInit: REG card status Ind fail");
                return VOS_ERR;
            }
            break;
        /* Add by H00300778 for MultiAppSync End 2015-05-12 */

        default:
            break;
    }

    return VOS_OK;
}
#endif /* FEATURE_ON == FEATURE_CL_INTERWORK */


VOS_UINT32 CSIMA_FidInit(enum VOS_INIT_PHASE_DEFINE ip)
{
#if (FEATURE_ON == FEATURE_CL_INTERWORK)
    VOS_UINT32      ulRslt;

    switch (ip)
    {
        case VOS_IP_LOAD_CONFIG:
        {
            ulRslt = VOS_RegisterPIDInfo(WUEPS_PID_CSIMA,
                                        (Init_Fun_Type)CSIMA_PidInit,
                                        (Msg_Fun_Type)CSIMA_PidMsgProc);
            if (VOS_OK != ulRslt)
            {
                return VOS_ERR;
            }

            /* ע���������ȼ� */
            ulRslt = VOS_RegisterMsgTaskPrio(WUEPS_FID_CSIMA, VOS_PRIORITY_M5);

            if (VOS_OK != ulRslt)
            {
                return VOS_ERR;
            }

            break;
        }
        default:
            break;
    }
#endif /* FEATURE_ON == FEATURE_CL_INTERWORK */

    return VOS_OK;
}


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* endof #if (FEATURE_ON == FEATURE_UE_UICC_MULTI_APP_SUPPORT) */
