
/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "MtcDebug.h"
#include "MtcComm.h"
#include "MtaMtcInterface.h"
#include "MtcRfLcdIntrusion.h"
#include "MtcCalcFreq.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e958*/

#define    THIS_FILE_ID        PS_FILE_ID_MTC_RF_LCD_INTRUSION_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/

VOS_VOID MTC_SndMtaMipiClkInfoInd(VOS_UINT16  usMipiClk)
{
    VOS_UINT16                          ulLenth;
    MTC_MTA_MIPICLK_INFO_IND_STRU      *pstMipiClkInd = VOS_NULL_PTR;

    ulLenth = sizeof(MTC_MTA_MIPICLK_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    /* ������Ϣ�ռ� */
    pstMipiClkInd = (MTC_MTA_MIPICLK_INFO_IND_STRU*)PS_ALLOC_MSG(UEPS_PID_MTC, ulLenth);

    if (VOS_NULL_PTR == pstMipiClkInd)
    {
        MTC_ERROR_LOG("MTC_SndMtaMipiClkInfoInd: Alloc msg fail!");
        MTC_DEBUG_RF_LCD_ALLOC_MSG_ERR();
        return;
    }

    /* ����Ϣ�ռ� */
    PS_MEM_SET((VOS_UINT8*)pstMipiClkInd + VOS_MSG_HEAD_LENGTH, 0x0, ulLenth);

    /* �����Ϣ */
    pstMipiClkInd->stMsgHeader.ulReceiverPid = MTC_GetMipiClkRcvPid();          /* �������ļ���ȡ����Pid */
    pstMipiClkInd->stMsgHeader.ulMsgName     = ID_MTC_MTA_MIPICLK_INFO_IND;
    pstMipiClkInd->usMipiCLk                 = usMipiClk;

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTC, pstMipiClkInd))
    {
        MTC_DEBUG_RF_LCD_SND_MIPICLK_IND_ERR();
        MTC_ERROR_LOG("MTC_SndMtaMipiClkInfoInd: Snd Msg err. Rec Pid ");
        return;
    }

    MTC_DEBUG_RF_LCD_SND_MIPICLK_IND_OK();

    return;
}
VOS_UINT16 MTC_GetInterBitMap(
    VOS_UINT32                          ulFreq
)
{
    VOS_UINT32                          ulMIpiClkIndex;
    VOS_UINT32                          ulFreqIndex;
    VOS_UINT16                          usWidth;
    VOS_UINT16                          usInterBitMap;
    MTC_RF_LCD_INTRUSION_CTX_STRU      *pstRfLcdIntrCtx;

    pstRfLcdIntrCtx                     = MTC_GetRfLcdIntrusionCtxAddr();
    usWidth                             = pstRfLcdIntrCtx->usFreqWidth / 2;
    usInterBitMap                       = 0;

    for (ulMIpiClkIndex = 0; ulMIpiClkIndex < pstRfLcdIntrCtx->ucAvailFreqListNum; ulMIpiClkIndex++)
    {
        for (ulFreqIndex = 0; ulFreqIndex < pstRfLcdIntrCtx->astRfLcdFreqList[ulMIpiClkIndex].ulAvailNum; ulFreqIndex++)
        {
            if ((ulFreq >= pstRfLcdIntrCtx->astRfLcdFreqList[ulMIpiClkIndex].aulFreq[ulFreqIndex] - usWidth)
             && (ulFreq <= pstRfLcdIntrCtx->astRfLcdFreqList[ulMIpiClkIndex].aulFreq[ulFreqIndex] + usWidth))
            {
                usInterBitMap |= (VOS_UINT16)MTC_SET_BIT(ulMIpiClkIndex);
                break;
            }
        }
    }

    return usInterBitMap;
}


VOS_VOID MTC_VerdictModemBitMapPri(
    MTC_MODEM_MIPI_CLK_PRI_STRU        *pstMomdemPri
)
{
    MTC_MODEM_MIPICLK_BITMAP_STRU      *pstModem0 = VOS_NULL_PTR;
    MTC_MODEM_MIPICLK_BITMAP_STRU      *pstModem1 = VOS_NULL_PTR;

    pstModem0 = MTC_GetRfCellInfoAddr(MODEM_ID_0);
#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    pstModem1 = MTC_GetRfCellInfoAddr(MODEM_ID_1);
#else
    pstModem1 = pstModem0;
#endif

    /* Modem0�Ѿ���CS���ӣ�����modem0��modem1��û��cs���� */
    if ((PS_TRUE == pstModem0->enCsExistFlag)
     || (PS_FALSE == pstModem1->enCsExistFlag))
    {
        pstMomdemPri->usPriScellMipiClkBitMap   = pstModem0->usScellBitMap;
        pstMomdemPri->usPriHoppingMipiClkBitMap = pstModem0->usHoppingBitMap;
        pstMomdemPri->usPriNcellMipiClkBitMap   = pstModem0->usNcellBitMap;
        pstMomdemPri->usSecScellMipiClkBitMap   = pstModem1->usScellBitMap;
        pstMomdemPri->usSecHoppingMipiClkBitMap = pstModem1->usHoppingBitMap;
        pstMomdemPri->usSecNcellMipiClkBitMap   = pstModem1->usNcellBitMap;

        return;
    }

    /* Modem1�Ѿ���CS���� */
    pstMomdemPri->usPriScellMipiClkBitMap   = pstModem1->usScellBitMap;
    pstMomdemPri->usPriHoppingMipiClkBitMap = pstModem1->usHoppingBitMap;
    pstMomdemPri->usPriNcellMipiClkBitMap   = pstModem1->usNcellBitMap;
    pstMomdemPri->usSecScellMipiClkBitMap   = pstModem0->usScellBitMap;
    pstMomdemPri->usSecHoppingMipiClkBitMap = pstModem0->usHoppingBitMap;
    pstMomdemPri->usSecNcellMipiClkBitMap   = pstModem0->usNcellBitMap;

    return;
}


VOS_UINT16 MTC_ProcScellClkBitMap(
    VOS_UINT32                          ulScellFreq
)
{
    VOS_UINT16                          usScellClkBitMap;
    VOS_UINT16                          usInterBitMap;

    usScellClkBitMap = MTC_GetMipiClkBitMap();

    usInterBitMap = MTC_GetInterBitMap(ulScellFreq);

    usScellClkBitMap &= ~usInterBitMap;

    return usScellClkBitMap;
}


VOS_UINT16 MTC_ProcHoppingClkBitMap(
    MTC_RF_FREQ_LIST_STRU              *pstFreq
)
{
    VOS_UINT32                          ulIndex;
    VOS_UINT16                          usInterBitMap;
    VOS_UINT16                          usHoppingllClk;

    usHoppingllClk = MTC_GetMipiClkBitMap();

    for (ulIndex = 0; ulIndex < pstFreq->ulFreqNum; ulIndex ++)
    {
        usInterBitMap = MTC_GetInterBitMap(pstFreq->ausFreq[ulIndex]);

        if ((usHoppingllClk & (~usInterBitMap)) == 0)
        {
            return usHoppingllClk;
        }

        usHoppingllClk &= ~usInterBitMap;
    }

    return usHoppingllClk;
}


VOS_UINT16 MTC_ProcNcellClkBitMap(
    MTC_RF_FREQ_LIST_STRU              *pstFreq
)
{
    VOS_UINT16                          usNcellClk;
    VOS_UINT16                          usInterBitMap;
    VOS_UINT32                          ulIndex;
    VOS_UINT8                           ucNum;
    VOS_UINT16                          usMin;
    MTC_RF_LCD_INTRUSION_CTX_STRU      *pstMtcRfLcdCtx;
    VOS_UINT16                          ausCount[MTC_RF_LCD_MIPICLK_MAX_NUM];

    usNcellClk      = MTC_GetMipiClkBitMap();
    pstMtcRfLcdCtx  = MTC_GetRfLcdIntrusionCtxAddr();
    usMin           = 0xFFFF;
    PS_MEM_SET(ausCount, 0, sizeof(ausCount));

    /* ����Ƶ��Ӱ��λͼ */
    for (ulIndex = 0; ulIndex < pstFreq->ulFreqNum; ulIndex++)
    {
        usInterBitMap = MTC_GetInterBitMap(pstFreq->ausFreq[ulIndex]);

        for (ucNum = 0; ucNum < pstMtcRfLcdCtx->ucAvailFreqListNum; ucNum++)
        {
            ausCount[ucNum] += ((usInterBitMap >> ucNum) & 0x0001);
        }
    }

    /* ͳ�Ƹ�LCD MipiClkӰ��Ȩ�� */
    for (ucNum = 0; ucNum < pstMtcRfLcdCtx->ucAvailFreqListNum; ucNum++)
    {
        if (ausCount[ucNum] < usMin)
        {
            usMin = ausCount[ucNum];
        }
    }

    /* ɸѡ���λͼ */
    for (ucNum = 0; ucNum < pstMtcRfLcdCtx->ucAvailFreqListNum; ucNum++)
    {
        if (ausCount[ucNum] > usMin)
        {
            usNcellClk &= ~((VOS_UINT16)MTC_SET_BIT(ucNum));
        }
    }

    return usNcellClk;
}
VOS_UINT16 MTC_ProcLcdMipiClkBitMap(
    MTC_MODEM_MIPI_CLK_PRI_STRU        *pstMomdemPri
)
{
    /* ���ȼ�˳��
       usPriScellMipiClkBitMap;
       usPriHoppingMipiClkBitMap;
       usPriNcellMipiClkBitMap;
       usSecScellMipiClkBitMap;
       usSecHoppingMipiClkBitMap;
       usSecNcellMipiClkBitMap;
    */

    VOS_UINT16                          usMipiClk;

    usMipiClk = pstMomdemPri->usPriScellMipiClkBitMap;

    if ((pstMomdemPri->usSecScellMipiClkBitMap & usMipiClk) == 0)
    {
        return usMipiClk;
    }
    usMipiClk &= pstMomdemPri->usSecScellMipiClkBitMap;

    if ((pstMomdemPri->usPriHoppingMipiClkBitMap & usMipiClk) == 0)
    {
        return usMipiClk;
    }
    usMipiClk &= pstMomdemPri->usPriHoppingMipiClkBitMap;

    if ((pstMomdemPri->usSecHoppingMipiClkBitMap & usMipiClk) == 0)
    {
        return usMipiClk;
    }
    usMipiClk &= pstMomdemPri->usSecHoppingMipiClkBitMap;

    if ((pstMomdemPri->usPriNcellMipiClkBitMap & usMipiClk) == 0)
    {
        return usMipiClk;
    }
    usMipiClk &= pstMomdemPri->usPriNcellMipiClkBitMap;

    if ((pstMomdemPri->usSecNcellMipiClkBitMap & usMipiClk) == 0)
    {
        return usMipiClk;
    }
    usMipiClk &= pstMomdemPri->usSecNcellMipiClkBitMap;


    return usMipiClk;
}


VOS_VOID MTC_RcvRrcUsingFreqInd(VOS_VOID *pMsg)
{
    RRC_MTC_USING_FREQ_IND_STRU        *pstFreqInfo     = VOS_NULL_PTR;
    MTC_MODEM_MIPICLK_BITMAP_STRU      *pstScellInfo    = VOS_NULL_PTR;
    MTC_MSG_BUF_STRU                   *pstBufAddr = VOS_NULL_PTR;
    MTC_MODEM_FREQ_LIST_STRU            stModemFreq;
    MTC_MODEM_MIPI_CLK_PRI_STRU         stMomdemPri;
    VOS_UINT16                          usMipiClk;
    MODEM_ID_ENUM_UINT16                enModemId;
    MTC_CFG_ENUM_UINT8                  enNotchCfg;

    pstFreqInfo     = (RRC_MTC_USING_FREQ_IND_STRU *)pMsg;

    enNotchCfg      = MTC_GetNotchCfg();
    enModemId       = VOS_GetModemIDFromPid(pstFreqInfo->stMsgHeader.ulSenderPid);
    pstBufAddr      = MTC_GetBufAddr(enModemId);
    if ( (MTC_CFG_ENABLE == enNotchCfg)
      && (MODEM_ID_0 == enModemId) )                                            /* ֻ��modem0�ϲ�֧��TL */
    {
        if (PS_FALSE == MTC_IsNeedBufModem0Msg(pstFreqInfo->stMsgHeader.ulSenderPid))
        {
            /* ����������б��������TL Band��Ϣ */
            MTC_ResetNCellBandInfo(MODEM_ID_0);

            /* ���ݵ�ǰ����ģʽ�ϱ�����С����������Ϣ�������Band��Ϣ */
            MTC_GetTLBandInfoFromUsingFreq(pstFreqInfo);

            /* ִ��Notch�þ� */
            MTC_ProcNotchStrategy();

            pstBufAddr->stBufUsingFreqInfoMsg.enExitBufMsgFlag = PS_FALSE;
        }
        else
        {
            PS_MEM_SET(&pstBufAddr->stBufUsingFreqInfoMsg, 0x0, sizeof(MTC_USING_FREQ_MSG_BUF_STRU));
            PS_MEM_CPY(&pstBufAddr->stBufUsingFreqInfoMsg.stUsingFreqInfoMsg, pstFreqInfo, sizeof(RRC_MTC_USING_FREQ_IND_STRU));
            pstBufAddr->stBufUsingFreqInfoMsg.enExitBufMsgFlag = PS_TRUE;

            /* ��ȡ��ά�ɲ� */
            MTC_DEBUG_TraceNotchInfo();

            /* �����Ҫ���棬���������ߣ��ȵ�ģʽ��ȷ������������� */
            return;
        }
    }

    if (MTC_CFG_DISABLE == MTC_GetRfLcdIntrusionCfg())
    {
        return;
    }

    PS_MEM_SET(&stModemFreq, 0, sizeof(MTC_MODEM_FREQ_LIST_STRU));
    PS_MEM_SET(&stMomdemPri, 0, sizeof(MTC_MODEM_MIPI_CLK_PRI_STRU));

    /* Ĭ�ϸ���modem�ķ���С����Ϣ */
#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    if (I1_UEPS_PID_GAS == pstFreqInfo->stMsgHeader.ulSenderPid)
    {
        pstScellInfo = MTC_GetRfCellInfoAddr(MODEM_ID_1);
    }
    else
#endif
    {
        pstScellInfo = MTC_GetRfCellInfoAddr(MODEM_ID_0);
    }

    /* ���·�����Ϣ */
    pstScellInfo->enCsExistFlag = pstFreqInfo->enCsExistFlag;
    pstScellInfo->enPsExistFlag = pstFreqInfo->enPsExistFlag;

    /* ��¼��ά�ɲ���Ϣ */
    MTC_DEBUG_SAVE_RF_USING_CS_PS_INFO(pstScellInfo->enCsExistFlag,
                                       pstScellInfo->enPsExistFlag);

    /* ��ȡ�����������ͺ�Ƶ��ת��ΪƵ�� */
    MTC_CalcRfDlFreq(pstFreqInfo, &stModemFreq);

    /* ɸѡ����С��λͼ */
    pstScellInfo->usScellBitMap         = MTC_ProcScellClkBitMap(stModemFreq.ulScellFreq);

    /* ɸѡ��Ƶλͼ */
    pstScellInfo->usHoppingBitMap       = MTC_ProcHoppingClkBitMap(&stModemFreq.stGsmHoppingFreq);

    /* ɸѡ����λͼ */
    pstScellInfo->usNcellBitMap         = MTC_ProcNcellClkBitMap(&stModemFreq.stNcellFreq);

    /* ���ݸ�modem��ǰ��ҵ��������ȼ� */
    MTC_VerdictModemBitMapPri(&stMomdemPri);

    /* ��¼��ά�ɲ���Ϣ */
    MTC_DEBUG_COPY_MODEM_MIPICLK(stMomdemPri);

    /* ɸѡ���λͼ */
    usMipiClk = MTC_ProcLcdMipiClkBitMap(&stMomdemPri);

    /* �ϱ�LCD MipiClkλͼ��MTA */
    MTC_SndMtaMipiClkInfoInd(usMipiClk);

    MTC_DEBUG_TraceRfUsingFreqListInfo();

    return ;
}

/*lint +e958*/

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* end of MtcRfLcdIntrusion.c */


