

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "product_config.h"
#include "cbpacommagent.h"
#include "csimagent.h"
#include "mdrv.h"
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
#define    THIS_FILE_ID        PS_FILE_ID_CBPACOMMAGENT_C

#if (FEATURE_ON == FEATURE_CL_INTERWORK)
/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
/* CBPCA ���������� */
CBPCA_CTX_STRU                          g_stCbpcaCtx;

/* CBPCA ��ά�ɲ�ͳ�� */
CBPCA_STATISTIC_STRU                    g_stCbpcaStatic = {0};

/* CPBCA��ӡ��ά�ɲ���ƿ��� */
VOS_UINT8                               g_ucCbpcaDbgFlag = VOS_FALSE;

/* HDLC֡�е�MsgId��CBPCA��Ҫת������PID֮���ӳ���ϵ�� */
CBPCA_PID_MSGID_MAP_TABLE_STRU          g_astCbpcaPidMsgIdMapTbl[] =
{
    /* CBPCA��Ҫת������PID */    /* HDLC֡�е�MsgId */    /* �����ֽ� */    /* CBPCA���͵���ӦPID��ʹ�õ�enMsgType */
    /* Add by H00300778 for MultiAppSync Begin 2015-05-12 */
    { I0_WUEPS_PID_CSIMA,            0x0000,              0x0,               CBPCA_CSIMA_DATA_IND          },/* ��һ�е�λ�ò����Ա䶯 */
    /* Add by H00300778 for MultiAppSync End 2015-05-12 */
    { WUEPS_PID_CMMCA,               0x0001,              0x0,               CBPCA_CMMCA_DATA_IND          }

};

VOS_INT  CBPCA_UartRcvCBFunc(UART_CONSUMER_ID uPortNo, VOS_UINT8 *pucData, VOS_UINT32 ulLength);

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/

VOS_VOID CBPCA_SetDebugSwitch(VOS_UINT8 ucFlag)
{
    g_ucCbpcaDbgFlag = ucFlag;

    return;
}


VOS_VOID CBPCA_ResetStatisticInfo(VOS_VOID)
{
    /*lint -e534*/
    VOS_MemSet(&g_stCbpcaStatic, 0, sizeof(g_stCbpcaStatic));
    /*lint +e534*/
    return;
}


VOS_VOID CBPCA_ShowCtrlAndStatisticInfo(VOS_VOID)
{
    /*lint -e534*/
    vos_printf("\r\n\r\n********************CBPCA ������������Ϣ************************\r\n");
    vos_printf("g_stCbpcaCtx.usExpectRcvIndex                                  %d\r\n", g_stCbpcaCtx.usExpectRcvIndex);
    vos_printf("g_stCbpcaCtx.usExpectSndIndex                                  %d\r\n", g_stCbpcaCtx.usExpectSndIndex);
    vos_printf("g_stCbpcaCtx.enCBPStatus(0:NOT READY 1:READY)                  %d\r\n", g_stCbpcaCtx.enCBPStatus);
    vos_printf("g_stCbpcaCtx.stDecapCtrlCtx.ulLength(DECAP�����е����ݳ���)    %d\r\n", g_stCbpcaCtx.stDecapCtrlCtx.ulLength);

    vos_printf("\r\n********************CBPCA ��ά�ɲ�ͳ����Ϣ************************\r\n");
    vos_printf("HDLC���װ:���װ�ɹ�����ͳ��                                 %d\r\n", g_stCbpcaStatic.ulHdlcDecapSucc);
    vos_printf("������ûص���������uPortNo�������ͳ��                       %d\r\n", g_stCbpcaStatic.ulUartCBWrongPortNo);
    vos_printf("������ûص������������ָ��Ϊ�մ���ͳ��                      %d\r\n", g_stCbpcaStatic.ulUartCBNullPtr);
    vos_printf("������ûص�����������ڳ���Ϊ0����ͳ��                       %d\r\n", g_stCbpcaStatic.ulUartCBLenIsZero);
    vos_printf("������ûص���������CBP״̬ΪNOT READY����ͳ��                %d\r\n", g_stCbpcaStatic.ulUartCBCBPNotReady);
    vos_printf("HDLC���װ:FCS�������ͳ��                                    %d\r\n", g_stCbpcaStatic.ulHdlcDecapFCSError);
    vos_printf("HDLC���װ:�쳣֡����������ͳ��                               %d\r\n", g_stCbpcaStatic.ulHdlcDecapDiscard);
    vos_printf("HDLC���װ:�����������ͳ��                                   %d\r\n", g_stCbpcaStatic.ulHdlcDecapBuffFull);
    vos_printf("HDLC���װ:��δ������ͳ��                                   %d\r\n", g_stCbpcaStatic.ulHdlcDecapParaError);
    vos_printf("HDLC���װ:�����Index����ͳ��                                %d\r\n", g_stCbpcaStatic.ulHdlcDecapInvalidIndex);
    vos_printf("HDLC���װ:���װ������ݳ���<=6��������Data����쳣ͳ��      %d\r\n", g_stCbpcaStatic.ulHdlcDecapNoDataField);
    vos_printf("HDLC���װ:���װ��LENGTH��<=2���쳣ͳ��                    %d\r\n", g_stCbpcaStatic.ulHdlcDecapLengthAbnormal);
    vos_printf("HDLC���װ:Length��ʵ�����ݳ���ҪС���쳣ͳ��                 %d\r\n", g_stCbpcaStatic.ulHdlcDecapLengthIsLess);
    vos_printf("HDLC���װ:Length��ʵ�����ݳ���Ҫ����쳣ͳ��                 %d\r\n", g_stCbpcaStatic.ulHdlcDecapLengthIsMore);
    vos_printf("HDLC���װ:�����MsgId����ͳ��                                %d\r\n", g_stCbpcaStatic.ulHdlcDecapInvalidMsgId);
    vos_printf("HDLC���װ:��Ч֡����ͳ��                                     %d\r\n", g_stCbpcaStatic.ulHdlcDecapInvalidFrame);
    vos_printf("���õ���ӿ�mdrv_dualmodem_send���ͳɹ�����ͳ��                     %d\r\n", g_stCbpcaStatic.ulSendToUartSucc);
    vos_printf("CBPδ���������·���CBP��֡����������ͳ��                      %d\r\n", g_stCbpcaStatic.ulCBPNotReadyDiscardFrame);
    vos_printf("����CBP�����ݣ������Ҳ���MsgId��Ӧ��PID������������ͳ��       %d\r\n", g_stCbpcaStatic.ulHdlcEncapInvalidPID);
    vos_printf("HDLC��װʧ�ܴ���ͳ��                                          %d\r\n", g_stCbpcaStatic.ulHdlcEncapFail);
    vos_printf("���õ���ӿ�mdrv_dualmodem_send����ʧ�ܴ���ͳ��                     %d\r\n", g_stCbpcaStatic.ulSendToUartFail);

    vos_printf("\r\n\r\n");
    /*lint +e534*/
    return;

}


VOS_VOID CBPCA_UartDataHook(VOS_UINT32 ulLength, VOS_UINT8 *pucData)
{
    MsgBlock                           *pstMsg;

    pstMsg = (MsgBlock*)VOS_AllocMsg(WUEPS_PID_CBPCA, ulLength);

    if (VOS_NULL_PTR == pstMsg)
    {
        CBPA_ERROR_LOG("CBPCA_UartDataHook:WARNING:alloc msg failed\n");

        return;
    }

    pstMsg->ulReceiverPid   = WUEPS_PID_CBPCA;

    pstMsg->ulLength        = ulLength;

    /*lint -e534*/
    VOS_MemCpy(pstMsg->aucValue, pucData, ulLength);
    /*lint +e534*/

    DIAG_TraceReport((VOS_VOID *)(pstMsg));

    /*lint -e534*/
    VOS_FreeMsg(WUEPS_PID_CBPCA, pstMsg);
    /*lint +e534*/

    return;
}


CBPCA_CTX_STRU* CBPCA_GetCtxAddr(VOS_VOID)
{
    return &(g_stCbpcaCtx);
}


VOS_VOID CBPCA_RestoreIndex(VOS_VOID)
{
    CBPCA_CTX_STRU                     *pstCbpcaCtx;
    VOS_INT32                           lLockKey;

    /* ��ȡCBPCA CTX��ָ�� */
    pstCbpcaCtx = CBPCA_GetCtxAddr();

    /* ���ж� */
    lLockKey = VOS_SplIMP();

    /* Index���� */
    pstCbpcaCtx->usExpectRcvIndex = 0;
    pstCbpcaCtx->usExpectSndIndex = 0;

    /* ���ж� */
    VOS_Splx(lLockKey);

    return;
}


VOS_VOID CBPCA_IncreaseIndex(VOS_UINT16 *pusIndex)
{
    VOS_INT32                           lLockKey;

    /* ���ж� */
    lLockKey = VOS_SplIMP();

    /* Index�ۼ� */
    if (*pusIndex < CBPCA_MAX_INDEX)
    {
        (*pusIndex)++;
    }
    else
    {
        *pusIndex = 0;
    }

    /* ���ж� */
    VOS_Splx(lLockKey);

    return;
}
VOS_UINT32 CBPCA_FindMatchPidByMsgId(
    VOS_UINT16                          usMsgId,
    VOS_UINT32                         *pulPid,
    CBPCA_MSG_TYPE_ENUM_UINT32         *penMsgType)
{
    VOS_UINT8       ucLoop;
    VOS_UINT8       ucTblElementCnt;

    ucTblElementCnt = (VOS_UINT8)(sizeof(g_astCbpcaPidMsgIdMapTbl) / sizeof(CBPCA_PID_MSGID_MAP_TABLE_STRU));

    for (ucLoop = 0; ucLoop < ucTblElementCnt; ucLoop++)
    {
        if (usMsgId == g_astCbpcaPidMsgIdMapTbl[ucLoop].usMsgId)
        {
            *pulPid     = g_astCbpcaPidMsgIdMapTbl[ucLoop].ulPid;
            *penMsgType = g_astCbpcaPidMsgIdMapTbl[ucLoop].enMsgType;
            return VOS_OK;
        }
    }

    return VOS_ERR;
}


VOS_UINT32 CBPCA_FindMatchMsgIdByPid(VOS_UINT32 ulPid, VOS_UINT16 *pusMsgId)
{
    VOS_UINT8       ucLoop;
    VOS_UINT8       ucTblElementCnt;

    ucTblElementCnt = (VOS_UINT8)(sizeof(g_astCbpcaPidMsgIdMapTbl) / sizeof(CBPCA_PID_MSGID_MAP_TABLE_STRU));

    for (ucLoop = 0; ucLoop < ucTblElementCnt; ucLoop++)
    {
        if (ulPid == g_astCbpcaPidMsgIdMapTbl[ucLoop].ulPid)
        {
            *pusMsgId = g_astCbpcaPidMsgIdMapTbl[ucLoop].usMsgId;
            return VOS_OK;
        }
    }

    return VOS_ERR;
}


VOS_UINT32 CBPCA_SndDataToCbpca(
    VOS_UINT32                          ulSndPid,
    CBPCA_MSG_TYPE_ENUM_UINT32          enMsgType,
    VOS_UINT8                          *pucData,
    VOS_UINT32                          ulLength)
{
    CBPCA_DATA_REQ_MSG_STRU            *pstMsg;
    VOS_UINT32                          ulMsgLen;
    VOS_UINT8                          *pucTmpptr;

    if ((VOS_NULL == ulLength) || (VOS_NULL_PTR == pucData))
    {
        CBPA_ERROR_LOG("CBPCA_SndDataToCbpca: para error!");
        return VOS_ERR;
    }

    /* ������Ϣ���ȣ���������Ϣͷ������ҪԤ����ǰ6���ֽڣ�������дHDLC֡�ж�Index��Length��MsgId��
        �������Լ���һ���ڴ濽����������ݷ���Ч�� */
    ulMsgLen = ((sizeof(CBPCA_DATA_REQ_MSG_STRU) - CBPCA_MSG_DATA_RSV_LEN)
                + CBPCA_RCV_UPPER_DATA_RSV_LEN + ulLength) - VOS_MSG_HEAD_LENGTH;

    pstMsg = (CBPCA_DATA_REQ_MSG_STRU *)VOS_AllocMsg(ulSndPid, ulMsgLen);
    if (VOS_NULL_PTR == pstMsg)
    {
        CBPA_ERROR1_LOG("CBPCA_SndDataToCbpca: Alloc msg fail!", (VOS_INT32)enMsgType);
        return VOS_ERR;
    }

    /* �����Ϣ���� */
    pstMsg->ulReceiverPid      = WUEPS_PID_CBPCA;
    pstMsg->enMsgType          = enMsgType;
    pstMsg->ulDataLen          = ulLength;

    /* �����������ݣ�����pucTmpptrָ��ת����Ϊ�˹��PCLINT������ָ������澯 */
    pucTmpptr = (VOS_UINT8 *)(((VOS_UINT32)pstMsg->aucData) + CBPCA_RCV_UPPER_DATA_RSV_LEN);
    /*lint -e534*/
    VOS_MemCpy(pucTmpptr, pucData, ulLength);
    /*lint +e534*/

    if (VOS_OK != VOS_SendMsg(ulSndPid, pstMsg))
    {
        CBPA_ERROR1_LOG("CBPCA_SndDataToCbpca: Send msg fail!", (VOS_INT32)enMsgType);
        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_VOID CBPCA_DataReqProc(CBPCA_DATA_REQ_MSG_STRU *pMsg)
{
    CBPCA_CTX_STRU                     *pCbpcaCtx;
    VOS_UINT8                          *pucData;
    VOS_UINT8                          *pucTmpPtr;
    VOS_UINT16                          usHdlcLength;      /* HDLC֡��Length���ֵ */
    VOS_UINT16                          usMsgId;
    VOS_UINT16                          usEncapLen;

    /* HDLC֡�ĸ�ʽ����:
    | 0x7E || Index(Low byte) | Index(High byte) | Length(Low byte) | Length(High byte) | MsgId(Low byte) | MsgId(High byte) |
    |           ... Data(Low byte) | Data(High byte) ...            |   FCS(High byte)  |  FCS(Low byte)  | 0x7E |
    */

    pCbpcaCtx = CBPCA_GetCtxAddr();

    /* ���ж�CBP Modem״̬�Ƿ�ready */
    if (CBP_MODEM_STATUS_READY != pCbpcaCtx->enCBPStatus)
    {
        /* ��ǰCBPδready������VIA�������ƣ���ǰ�������ݷ��ͣ�����ֱ�Ӷ�������¼��ά�ɲ� */
        CBPCA_STATISTIC_INC(CBPCA_STATISTIC_CBP_NOT_READY_DISCARD_FRAME);

        return;
    }

    /* pMsg->aucData�Ѿ�Ԥ����ǰ6���ֽڣ��������HDLC֡��Index��Length��MsgId������һ���ڲ⿽������ߴ���Ч�� */
    pucData = pMsg->aucData;

    /* ���Index */
    *pucData       = (VOS_UINT8)(pCbpcaCtx->usExpectSndIndex & 0xFF);
    *(pucData + 1) = (VOS_UINT8)((pCbpcaCtx->usExpectSndIndex >> 8) & 0xFF);

    /* ���Length(LengthΪMsgId��Data��ĳ��Ⱥ�) */
    pucData += sizeof(VOS_UINT16);
    usHdlcLength = (VOS_UINT16)(pMsg->ulDataLen + sizeof(usMsgId));
    *pucData       = (VOS_UINT8)(usHdlcLength & 0xFF);
    *(pucData + 1) = (VOS_UINT8)((usHdlcLength >> 8) & 0xFF);

    /* ����ulSenderPid��ȡ��Ӧ��MsgId */
    if (VOS_OK != CBPCA_FindMatchMsgIdByPid(pMsg->ulSenderPid, &usMsgId))
    {
        /* ��¼��ά�ɲ⣬������ֱ�Ӷ��� */
        CBPCA_STATISTIC_INC(CBPCA_STATISTIC_CANNOT_FIND_MATCH_MSGID);

        CBPA_ERROR_LOG("CBPCA_DataReqProc: Abnormal Msg ID.");

        return;
    }

    /* ���MsgId������pTmpPtr��ָ��ת������Ϊ�˹��PCLINT������ָ������澯 */
    pucData += sizeof(VOS_UINT16);
    pucTmpPtr        = (VOS_UINT8 *)((VOS_UINT32)pucData);
    *pucTmpPtr       = (VOS_UINT8)(usMsgId & 0xFF);         /* [false alarm]:��Ϣ���죬����ʵ�ʳ�������ռ䣬�˴�û��������� */
    *(pucTmpPtr + 1) = (VOS_UINT8)((usMsgId >> 8) & 0xFF);  /* [false alarm]:��Ϣ���죬����ʵ�ʳ�������ռ䣬�˴�û��������� */

    /* ִ��HDLC��װ */
    if (VOS_OK != Om_HdlcEncap(pMsg->aucData,
                               (VOS_UINT16)(CBPCA_RCV_UPPER_DATA_RSV_LEN + pMsg->ulDataLen),
                               pCbpcaCtx->stEncapCtrlCtx.pucEncapBuff,
                               (VOS_UINT16)(pCbpcaCtx->stEncapCtrlCtx.ulEncapBuffSize),
                               &usEncapLen))
    {
        /* HDLC��װʧ�ܣ���¼��ά�ɲ� */
        CBPCA_STATISTIC_INC(CBPCA_STATISTIC_HDLC_ENCAP_FAIL);

        CBPA_ERROR_LOG("CBPCA_DataReqProc: Om_HdlcEncap Fail!");

        return;
    }

    /* ���õ���UART���ͽӿڷ������� */
    if (VOS_OK != mdrv_dualmodem_send(CBP_UART_PORT_ID, pCbpcaCtx->stEncapCtrlCtx.pucEncapBuff, (VOS_UINT32)usEncapLen))
    {
        /* ����ӿڷ���ʧ�ܣ���¼��ά�ɲ� */
        CBPCA_STATISTIC_INC(CBPCA_STATISTIC_HDLC_ENCAP_SEND_FAIL);

        CBPA_ERROR_LOG("CBPCA_DataReqProc: mdrv_dualmodem_send Fail!");

        return;
    }

    /* ��ά�ɲ��ӡ */
    /*lint -e40*/
    CBPA_DEBUG_TRACE(pCbpcaCtx->stEncapCtrlCtx.pucEncapBuff, usEncapLen);
    /*lint +e40*/

    /* ��¼��ά�ɲ� */
    CBPCA_STATISTIC_INC(CBPCA_STATISTIC_HDLC_ENCAP_SEND_SUCC);

    /* �ۼӷ���Index */
    CBPCA_IncreaseIndex(&(pCbpcaCtx->usExpectSndIndex));

    /* ִ�й������� */
    CBPCA_UartDataHook((VOS_UINT32)usEncapLen, pCbpcaCtx->stEncapCtrlCtx.pucEncapBuff);

    return;
}


VOS_VOID CBPCA_CSIMAModemResetIndProc(CSIMA_CBPCA_MODEM_RESET_IND_MSG_STRU *pMsg)
{
    CBPCA_CTX_STRU                     *pCbpcaCtx;
    VOS_INT32                           iResult;

    pCbpcaCtx = CBPCA_GetCtxAddr();

    if (CSIMA_CBPCA_MODEM_RESET_START == pMsg->enModemReset)
    {
        /* ��CBP Ready��־��Ϊ"NOT READY" */
        pCbpcaCtx->enCBPStatus = CBP_MODEM_STATUS_NOT_READY;

    }
    else if (CSIMA_CBPCA_MODEM_RESET_SUCC == pMsg->enModemReset)
    {
        /*ͨ��AT�����жϵ�ǰ��ƴƬ�����PID��AP��ֻ֤����ȷ��Modem�����·�������*/
        if (g_astCbpcaPidMsgIdMapTbl[0].ulPid != pMsg->ulSenderPid)
        {
            g_astCbpcaPidMsgIdMapTbl[0].ulPid = pMsg->ulSenderPid;
        }

        if (0 != mdrv_dual_modem_init())
        {
            CBPA_WARNING_LOG("CBPCA_CSIMAModemResetIndProc: uart_test_bsp_dual_modem_init fail!");
        }

        CBPA_ERROR_LOG("CBPCA_CSIMAModemResetIndProc after uart_test_bsp_dual_modem_init");

        iResult = mdrv_dualmodem_register_rcvhook(CBP_UART_PORT_ID, (pUARTRecv)CBPCA_UartRcvCBFunc);

        if (VOS_OK != iResult)
        {
            CBPA_ERROR1_LOG("CBPCA_Init: Reg callback function fail!", iResult);
            return;
        }

        CBPA_ERROR_LOG("CBPCA_CSIMAModemResetIndProc after register CBPCA_UartRcvCBFunc");

        /* ���HDLC��װ�Ļ������� */
        /*lint -e534*/
        VOS_MemSet(pCbpcaCtx->stEncapCtrlCtx.pucEncapBuff, 0, pCbpcaCtx->stEncapCtrlCtx.ulEncapBuffSize);

        /* ���HDLC���װ�Ļ������� */
        VOS_MemSet(pCbpcaCtx->stDecapCtrlCtx.pucDecapBuff, 0, pCbpcaCtx->stDecapCtrlCtx.ulDecapBuffSize);
        /*lint +e534*/
        Om_HdlcInit(&pCbpcaCtx->stDecapCtrlCtx);

        /* ����HDLC���ա�����Index������ */
        CBPCA_RestoreIndex();

        /* ��CBP Ready��־��Ϊ"READY" */
        pCbpcaCtx->enCBPStatus = CBP_MODEM_STATUS_READY;

        CBPA_ERROR_LOG("CBPCA_CSIMAModemResetIndProc after enCBPStatus = CBP_MODEM_STATUS_READY");
    }
    else if (CSIMA_CBPCA_MODEM_RESET_FAIL == pMsg->enModemReset)
    {
        /* VIA Modem��λʧ�ܣ���ǰ�����κδ��� */
        CBPA_WARNING_LOG("CBPCA_CSIMAModemResetIndProc: VIA Reset fail!");
    }
    else
    {
        CBPA_WARNING_LOG("CBPCA_CSIMAModemResetIndProc: Abnormal enModemReset!");
    }

    return;
}
VOS_VOID CBPCA_CSIMAMsgProc(MsgBlock *pMsg)
{
    CBPCA_MSG_HDR_STRU                 *pstDataReq;

    pstDataReq = (CBPCA_MSG_HDR_STRU *)pMsg;

    switch (pstDataReq->enMsgType)
    {
         case CSIMA_CBPCA_DATA_REQ:
            CBPCA_DataReqProc((CBPCA_DATA_REQ_MSG_STRU *)pMsg);
            break;

         case CSIMA_CBPCA_MODEM_RESET_IND:
            CBPCA_CSIMAModemResetIndProc((CSIMA_CBPCA_MODEM_RESET_IND_MSG_STRU *)pMsg);
            break;

         default:
            CBPA_WARNING_LOG("CBPCA_CSIMAMsgProc: Abnormal Msg ID.");
            break;
    }

    return;
}


VOS_VOID CBPCA_CMMCAMsgProc(MsgBlock *pMsg)
{
    CBPCA_MSG_HDR_STRU                 *pstDataReq;

    pstDataReq = (CBPCA_MSG_HDR_STRU *)pMsg;

    switch (pstDataReq->enMsgType)
    {
         case CMMCA_CBPCA_DATA_REQ:
            CBPCA_DataReqProc((CBPCA_DATA_REQ_MSG_STRU *)pMsg);
            break;

         default:
            CBPA_WARNING_LOG("CBPCA_CMMCAMsgProc: Abnormal Msg ID.");
            break;
    }

    return;
}



VOS_VOID CBPCA_PidMsgProc(MsgBlock *pMsg)
{
    switch (pMsg->ulSenderPid)
    {
        /* Add by H00300778 for MultiAppSync Begin 2015-05-12 */
        case I0_WUEPS_PID_CSIMA:
        case I1_WUEPS_PID_CSIMA:
        /* Add by H00300778 for MultiAppSync End 2015-05-12 */
            CBPCA_CSIMAMsgProc(pMsg);
            break;

        case WUEPS_PID_CMMCA:
            CBPCA_CMMCAMsgProc(pMsg);
            break;

        default:
            CBPA_WARNING_LOG("CBPCA_PidMsgProc: Abnormal PID.");
            break;
    }

    return;
}


VOS_VOID CBPCA_TransferDataToUpperLayer(
    VOS_UINT32                          ulRcvPid,
    CBPCA_MSG_TYPE_ENUM_UINT32          enMsgType,
    VOS_UINT8                          *pucData,
    VOS_UINT32                          ulLength)
{
    CBPCA_DATA_IND_MSG_STRU            *pstMsg;
    VOS_UINT32                          ulMsgLen;
    VOS_UINT8                          *pucTmpPtr;

    /* ������Ϣ���ȣ���������Ϣͷ */
    if (ulLength > CBPCA_MSG_DATA_RSV_LEN)
    {
        ulMsgLen = ((sizeof(CBPCA_DATA_IND_MSG_STRU) - CBPCA_MSG_DATA_RSV_LEN) + ulLength) - VOS_MSG_HEAD_LENGTH;
    }
    else
    {
        ulMsgLen = sizeof(CBPCA_DATA_IND_MSG_STRU) - VOS_MSG_HEAD_LENGTH;
    }

    pstMsg = (CBPCA_DATA_IND_MSG_STRU *)VOS_AllocMsg(WUEPS_PID_CBPCA, ulMsgLen);
    if (VOS_NULL_PTR == pstMsg)
    {
        CBPA_ERROR1_LOG("CBPCA_TransferDataToUpperLayer: Alloc msg fail!", (VOS_INT32)enMsgType);
        return;
    }

    /* �����Ϣ���� */
    pstMsg->ulReceiverPid      = ulRcvPid;
    pstMsg->enMsgType          = enMsgType;
    pstMsg->ulDataLen          = ulLength;

    if (0 != ulLength)
    {
        /* ������������ */
        pucTmpPtr = (VOS_UINT8 *)((VOS_UINT32)(pstMsg->aucData));
        /*lint -e534*/
        VOS_MemCpy(pucTmpPtr, pucData, ulLength);
        /*lint +e534*/
    }
    if (VOS_OK != VOS_SendMsg(WUEPS_PID_CBPCA, pstMsg))
    {
        CBPA_ERROR1_LOG("CBPCA_TransferDataToUpperLayer: Send msg fail!", (VOS_INT32)enMsgType);
    }

    return;
}
VOS_VOID CBPCA_DecreaseIndex(VOS_UINT16 *pusIndex)
{
    VOS_INT32                           lLockKey;

    /* ���ж� */
    lLockKey = VOS_SplIMP();

    /* Index��һ */
    if (*pusIndex > 0)
    {
        (*pusIndex)--;
    }
    else
    {
        *pusIndex = CBPCA_MAX_INDEX;
    }

    /* ���ж� */
    VOS_Splx(lLockKey);

    return;
}
VOS_VOID CBPCA_DispatchReceivedData(VOS_UINT8 *pucData, VOS_UINT32 ulInfoLength)
{
    VOS_UINT16                          usIndex  = 0;
    VOS_UINT16                          usLength = 0;          /* ��¼HDLC֡��length�ֶε�ֵ */
    VOS_UINT16                          usRawDataLength = 0;   /* ��¼HDLC֡��Data��ĳ��� */
    VOS_UINT16                          usMsgId  = 0;
    VOS_UINT32                          ulRcvPid;
    CBPCA_MSG_TYPE_ENUM_UINT32          enMsgType;
    CBPCA_CTX_STRU                     *pCbpcaCtx;
    VOS_UINT32                          i = 0;

    /* ���յ�������������ʽ����
    | Index(Low byte) | Index(High byte) | Length(Low byte) | Length(High byte) | MsgId(Low byte) | MsgId(High byte) |
    |           ... Data ...             |
    */

    /* �ж�ulLength�Ϸ��� */
    if (VOS_NULL == ulInfoLength)
    {
        CBPA_ERROR_LOG("CBPCA_DispatchReceivedData: ulInfoLength is 0!");
        return;
    }

    if (ulInfoLength <= CBPCA_RCV_UPPER_DATA_RSV_LEN)
    {
        /* ��¼��ά�ɲ���Ϣ */
        CBPCA_STATISTIC_INC(CBPCA_STATISTIC_HDLC_DECAP_NO_DATA_FIELD);

        CBPA_ERROR_LOG("CBPCA_DispatchReceivedData: ulInfoLength <= 6!");
        return;
    }

    /* ��ȡCBPCA����������ָ�� */
    pCbpcaCtx = CBPCA_GetCtxAddr();

    /* �ж�Index�Ƿ���Ԥ�ڵ�index��� */
    /*lint -e534*/
    VOS_MemCpy((VOS_VOID *)&usIndex, (VOS_VOID *)pucData, sizeof(VOS_UINT16));
    /*lint +e534*/
    if (pCbpcaCtx->usExpectRcvIndex != usIndex)
    {
        /* ��¼��ά�ɲ���Ϣ����ǰ�Ȳ�ʵ���ط���Index����Ҳ�������� */
        CBPCA_STATISTIC_INC(CBPCA_STATISTIC_HDLC_DECAP_INVALID_INDEX);
        if (0xffff == usIndex)
        {
            CBPCA_DecreaseIndex(&(CBPCA_GetCtxAddr()->usExpectRcvIndex));
        }
        else if(pCbpcaCtx->usExpectRcvIndex > usIndex)
        {
            /* ��ӡ�����¼����INDEX��Ϣ */
            /*lint -e534*/
            vos_printf("CBPCA_DispatchReceivedData:ExpectRcvIndex>usIndex,index is 0x%x,pCbpcaCtx->usExpectRcvIndex is 0x%x\n",usIndex,pCbpcaCtx->usExpectRcvIndex);
            /*lint +e534*/
            pCbpcaCtx->usExpectRcvIndex = usIndex;
        }
        else
        {
            /* ��ӡ�����¼����INDEX��Ϣ */
            /*lint -e534*/
            vos_printf("CBPCA_DispatchReceivedData: index is 0x%x,pCbpcaCtx->usExpectRcvIndex is 0x%x\n",usIndex,pCbpcaCtx->usExpectRcvIndex);
            /*lint +e534*/
            for(i=0;i<ulInfoLength;i++)
            {
                /*lint -e534*/
                vos_printf("pucData[%d]: 0x%x\n",i,pucData[i]);
                /*lint +e534*/
            }
            mdrv_om_system_error(CBPCA_VIAMSG_INDEX_ERROR,THIS_FILE_ID, __LINE__, 0, 0);
            pCbpcaCtx->usExpectRcvIndex = usIndex;
        }
    }

    /* LengthΪMsgId��Data�򳤶�֮�ͣ��ж���Ϸ��� */
    pucData += sizeof(VOS_UINT16);
    /*lint -e534*/
    (VOS_VOID)VOS_MemCpy((VOS_VOID *)&usLength, (VOS_VOID *)pucData, sizeof(VOS_UINT16));
    /*lint +e534*/

    if (usLength <= sizeof(usMsgId))
    {
        /* ��¼��ά�ɲ���Ϣ */
        CBPCA_STATISTIC_INC(CBPCA_STATISTIC_HDLC_DECAP_LENGTH_ABNORMAL);

        CBPA_ERROR_LOG("CBPCA_DispatchReceivedData: usLength <= 2!");
        return;
    }

    if (usLength != (ulInfoLength - sizeof(usIndex) - sizeof(usLength)))
    {
        /* ��usLengthС��ʵ�ʳ��ȣ�����usLengthΪ׼��������ʵ�ʳ���Ϊ׼ */
        if (usLength < (ulInfoLength - sizeof(usIndex) - sizeof(usLength)))
        {
            /* ��¼��ά�ɲ���Ϣ */
            CBPCA_STATISTIC_INC(CBPCA_STATISTIC_HDLC_DECAP_LENGTH_IS_LESS);

            usRawDataLength = usLength - sizeof(usMsgId);
        }
        else
        {
            /* ��¼��ά�ɲ���Ϣ */
            CBPCA_STATISTIC_INC(CBPCA_STATISTIC_HDLC_DECAP_LENGTH_IS_MORE);

            usRawDataLength = (VOS_UINT16)(ulInfoLength - sizeof(usIndex) - sizeof(usLength) - sizeof(usMsgId));
        }
    }
    else
    {
        usRawDataLength = usLength - sizeof(usMsgId);
    }

    /* ����MsgId�ҵ���Ҫת������PID */
    pucData += sizeof(VOS_UINT16);
    /*lint -e534*/
    VOS_MemCpy((VOS_VOID *)&usMsgId, (VOS_VOID *)pucData, sizeof(VOS_UINT16));
    /*lint +e534*/
    if (VOS_OK != CBPCA_FindMatchPidByMsgId(usMsgId, &ulRcvPid, &enMsgType))
    {
        /* ��¼��ά�ɲ���Ϣ����������֡ */
        CBPCA_STATISTIC_INC(CBPCA_STATISTIC_HDLC_DECAP_INVALID_MSGID);

        return;
    }

    /* ��ָ��ָ��Data�� */
    pucData += sizeof(VOS_UINT16);

    /* ������ת����Ŀ��PID */
    CBPCA_TransferDataToUpperLayer(ulRcvPid, enMsgType, pucData, usRawDataLength);

    /* ��ά�ɲ���Ϣͳ�� */
    CBPCA_STATISTIC_INC(CBPCA_STATISTIC_HDLC_DECAP_SUCC);

    return;
}
VOS_INT  CBPCA_UartRcvCBFunc(UART_CONSUMER_ID uPortNo, VOS_UINT8 *pucData, VOS_UINT32 ulLength)
{
    VOS_UINT32                          ulLoop;
    OM_HDLC_STRU                       *pstDecapCtrlCtx;
    OM_HDLC_RESULT_ENUM_UINT32          enDecapResult;
    VOS_INT                             iResult = VOS_ERROR;

    /* �ж�ucPortNo�Ϸ��� */
    if (CBP_UART_PORT_ID != uPortNo)
    {
        /* ��ά�ɲ�ͳ�� */
        CBPCA_STATISTIC_INC(CBPCA_STATISTIC_UART_CALLBACK_WRONG_PORTNO);

        CBPA_ERROR_LOG("CBPCA_UartRcvCBFunc: ucPortNo != CBP_UART_PORT_ID!");
        return VOS_ERROR;
    }

    /* pData�Ϸ��Լ�� */
    if (VOS_NULL_PTR == pucData)
    {
        /* ��ά�ɲ�ͳ�� */
        CBPCA_STATISTIC_INC(CBPCA_STATISTIC_UART_CALLBACK_NULL_PTR);

        CBPA_ERROR_LOG("CBPCA_UartRcvCBFunc: pucData is VOS_NULL_PTR!");
        return VOS_ERROR;
    }

    /* uslength�Ϸ��Լ�� */
    if (VOS_NULL == ulLength)
    {
        /* ��ά�ɲ�ͳ�� */
        CBPCA_STATISTIC_INC(CBPCA_STATISTIC_UART_CALLBACK_LEN_IS_ZERO);

        CBPA_ERROR_LOG("CBPCA_UartRcvCBFunc: ulLength is 0!");
        return VOS_ERROR;
    }

    /* �ж�CBP�Ƿ�ready */
    if (CBP_MODEM_STATUS_READY != CBPCA_GetCtxAddr()->enCBPStatus)
    {
        /* ��ά�ɲ�ͳ�� */
        CBPCA_STATISTIC_INC(CBPCA_STATISTIC_UART_CALLBACK_CBP_NOT_READY);

        CBPA_ERROR_LOG("CBPCA_UartRcvCBFunc: CBP is not ready!");
        return VOS_ERROR;
    }

    /* ִ�й������� */
    CBPCA_UartDataHook(ulLength, pucData);

    pstDecapCtrlCtx = &(CBPCA_GetCtxAddr()->stDecapCtrlCtx);

    /* ִ�н��װ���� */
    for (ulLoop = 0; ulLoop < ulLength; ulLoop++)
    {
        enDecapResult = Om_HdlcDecap(pstDecapCtrlCtx, pucData[ulLoop]);

        switch (enDecapResult)
        {
            case HDLC_SUCC:
                /*lint -e40*/
                CBPA_DEBUG_TRACE(pstDecapCtrlCtx->pucDecapBuff, pstDecapCtrlCtx->ulInfoLen);
                /*lint +e40*/

                /* ������һ������HDLC֡��ִ��ת������ */
                CBPCA_DispatchReceivedData(pstDecapCtrlCtx->pucDecapBuff, pstDecapCtrlCtx->ulInfoLen);

                /* ��HDLC�����ṹ��ԭ */
                Om_HdlcInit(pstDecapCtrlCtx);

                /* �ۼӽ���Index */
                CBPCA_IncreaseIndex(&(CBPCA_GetCtxAddr()->usExpectRcvIndex));

                iResult = VOS_OK;
                break;

            case HDLC_NOT_HDLC_FRAME:
                /*����������֡, ����HDLC���װ*/
                iResult = VOS_OK;
                break;

            case HDLC_FCS_ERROR:
                /* FCSУ��ʧ�ܣ����п�ά�ɲ�ͳ�� */
                CBPCA_STATISTIC_INC(CBPCA_STATISTIC_HDLC_DECAP_FCS_ERR);

                /* �ۼӽ���Index */
                CBPCA_IncreaseIndex(&(CBPCA_GetCtxAddr()->usExpectRcvIndex));

                iResult = VOS_ERROR;
                break;

            case HDLC_FRAME_DISCARD:
                /* �쳣֡�����п�ά�ɲ�ͳ�� */
                CBPCA_STATISTIC_INC(CBPCA_STATISTIC_HDLC_DECAP_DISCARD);

                /* �ۼӽ���Index */
                CBPCA_IncreaseIndex(&(CBPCA_GetCtxAddr()->usExpectRcvIndex));

                iResult = VOS_ERROR;
                break;

            case HDLC_BUFF_FULL:
                /* �������棬���п�ά�ɲ�ͳ�� */
                CBPCA_STATISTIC_INC(CBPCA_STATISTIC_HDLC_DECAP_BUFF_FULL);

                /* �ۼӽ���Index */
                CBPCA_IncreaseIndex(&(CBPCA_GetCtxAddr()->usExpectRcvIndex));

                iResult = VOS_ERROR;
                break;
            case HDLC_PARA_ERROR:
                /* ��δ��󣬽��п�ά�ɲ�ͳ�� */
                CBPCA_STATISTIC_INC(CBPCA_STATISTIC_HDLC_DECAP_PARA_ERROR);

                /* �ۼӽ���Index */
                CBPCA_IncreaseIndex(&(CBPCA_GetCtxAddr()->usExpectRcvIndex));

                iResult = VOS_ERROR;
                break;

            default:
                /* �������󣬽��п�ά�ɲ�ͳ�� */
                CBPCA_STATISTIC_INC(CBPCA_STATISTIC_HDLC_DECAP_INVALID_FRAME);

                /* �ۼӽ���Index */
                CBPCA_IncreaseIndex(&(CBPCA_GetCtxAddr()->usExpectRcvIndex));

                iResult = VOS_ERROR;
                break;
        }
    }

    return iResult;
}


VOS_UINT32 CBPCA_Init(VOS_VOID)
{
    CBPCA_CTX_STRU                     *pstCbpcaCtx;
/*    VOS_INT                             iResult;*/
    /* Add by H00300778 for MultiAppSync Begin 2015-05-12 */
    TAF_NV_LC_CTRL_PARA_STRU            stModem0LcCtrl = {0};
    TAF_NV_LC_CTRL_PARA_STRU            stModem1LcCtrl = {0};
    VOS_UINT32                          ulResult0;
    VOS_UINT32                          ulResult1;

    /* ��ȡCBPCA CTX��ָ�� */
    pstCbpcaCtx = CBPCA_GetCtxAddr();

    /* ��CBPCA CTX��������� */
    /*lint -e534*/
    VOS_MemSet(pstCbpcaCtx, 0, sizeof(CBPCA_CTX_STRU));
    /*lint +e534*/

    /* �ж�˫��L+C����NV�Ƿ�������δ����������ִ�г�ʼ������ */
    ulResult0 = NV_ReadEx(MODEM_ID_0, en_NV_Item_LC_Ctrl_PARA, &stModem0LcCtrl, sizeof(TAF_NV_LC_CTRL_PARA_STRU));

    ulResult1 = NV_ReadEx(MODEM_ID_1, en_NV_Item_LC_Ctrl_PARA, &stModem1LcCtrl, sizeof(TAF_NV_LC_CTRL_PARA_STRU));

    /*�����ȡȫ��ʧ�ܲ��˳�������������ĳ������*/
    if ((NV_OK != ulResult0)
     && (NV_OK != ulResult1))
    {
        CBPA_ERROR_LOG("CBPCA_Init: NV en_NV_Item_LC_Ctrl_PARA read fail!");
        return VOS_OK;
    }

    /*ȫ��ͨ��Ʒ����������Ҫ�򿪣����Ű汾ֻ��Ҫ������*/
    if ((VOS_TRUE != stModem0LcCtrl.ucLCEnableFlg)
     && (VOS_TRUE != stModem1LcCtrl.ucLCEnableFlg))
    {
        CBPA_NORMAL_LOG("CBPCA_Init: NV en_NV_Item_LC_Ctrl_PARA is off!");
        return VOS_OK;
    }

    /* ���������CL���ܣ�˵�������ڸ������棬����Ĭ�������� */
    if ((VOS_TRUE                     == stModem0LcCtrl.ucLCEnableFlg)
     && (TAF_NVIM_LC_RAT_COMBINED_GUL == stModem0LcCtrl.enRatCombined)
     && (VOS_TRUE                     == stModem1LcCtrl.ucLCEnableFlg)
     && (TAF_NVIM_LC_RAT_COMBINED_CL  == stModem1LcCtrl.enRatCombined))
    {
        g_astCbpcaPidMsgIdMapTbl[0].ulPid = I1_WUEPS_PID_CSIMA;
    }
    /* Add by H00300778 for MultiAppSync End 2015-05-12 */

    /* ��������HDLC��װ�Ļ��� */
    pstCbpcaCtx->stEncapCtrlCtx.pucEncapBuff = (VOS_UINT8 *)VOS_MemAlloc(WUEPS_PID_CBPCA, STATIC_MEM_PT, CBPCA_HDLC_BUFFER_SIZE);

    if (VOS_NULL_PTR == pstCbpcaCtx->stEncapCtrlCtx.pucEncapBuff)
    {
        CBPA_ERROR_LOG("CBPCA_Init: Alloc Encapsulate buffer fail!");
        return VOS_ERR;
    }

    /* HDLC��װ���泤�ȸ�ֵ */
    pstCbpcaCtx->stEncapCtrlCtx.ulEncapBuffSize = CBPCA_HDLC_BUFFER_SIZE;

    /* ��������HDLC���װ�Ļ��� */
    pstCbpcaCtx->stDecapCtrlCtx.pucDecapBuff = (VOS_UINT8 *)VOS_MemAlloc(WUEPS_PID_CBPCA, STATIC_MEM_PT, CBPCA_HDLC_BUFFER_SIZE);
    if (VOS_NULL_PTR == pstCbpcaCtx->stDecapCtrlCtx.pucDecapBuff)
    {
        CBPA_ERROR_LOG("CBPCA_Init: Alloc Decapsulate buffer fail!");

        /*lint -e534*/
        VOS_MemFree(WUEPS_PID_CBPCA, pstCbpcaCtx->stEncapCtrlCtx.pucEncapBuff);
        /*lint +e534*/
        return VOS_ERR;
    }

    /* HDLC���װ���泤�ȸ�ֵ */
    pstCbpcaCtx->stDecapCtrlCtx.ulDecapBuffSize = CBPCA_HDLC_BUFFER_SIZE;

    /* ��ʼ��HDLC���װ���������� */
    Om_HdlcInit(&pstCbpcaCtx->stDecapCtrlCtx);

    /* ��ʼ���շ�HDLC֡��Index����Ϊ0 */
    CBPCA_RestoreIndex();

    /* ��ʼ��CBP�Ƿ�ready��ȫ�ֱ�Ǳ���Ϊ"NOT READY" */
    pstCbpcaCtx->enCBPStatus = CBP_MODEM_STATUS_NOT_READY;

    return VOS_OK;
}


VOS_UINT32 CBPCA_PidInit(enum VOS_INIT_PHASE_DEFINE ip)
{
    switch (ip)
    {
        case VOS_IP_INITIAL:
            return CBPCA_Init();

        default:
            break;
    }

    return VOS_OK;
}
#endif /* FEATURE_ON == FEATURE_CL_INTERWORK */

VOS_UINT32 CBPCA_FidInit(enum VOS_INIT_PHASE_DEFINE ip)
{
#if (FEATURE_ON == FEATURE_CL_INTERWORK)
    VOS_UINT32      ulRslt;

    switch (ip)
    {
        case VOS_IP_LOAD_CONFIG:
        {
            ulRslt = VOS_RegisterPIDInfo(WUEPS_PID_CBPCA,
                                        (Init_Fun_Type)CBPCA_PidInit,
                                        (Msg_Fun_Type)CBPCA_PidMsgProc);
            if (VOS_OK != ulRslt)
            {
                return VOS_ERR;
            }

            /* ע���������ȼ� */
            ulRslt = VOS_RegisterMsgTaskPrio(WUEPS_FID_CBPCA, VOS_PRIORITY_P1);

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

