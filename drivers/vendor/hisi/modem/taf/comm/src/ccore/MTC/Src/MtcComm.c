
/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "MtcComm.h"
#include "MtcCtx.h"
#include "MtcIntrusion.h"
#include "MtcMmaInterface.h"
#include "MtcDebug.h"
#include "TafMtcInterface.h"

#include "MtcPsTransfer.h"
#include "CmmcaMtcInterface.h"
#include "MtcRfLcdIntrusion.h"

#include "ImsaMtcInterface.h"
#include "TafMtcApi.h"
#include "MtcMrma.h"
#include  "NVIM_Interface.h"
#include "MtcCalcFreq.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e958*/

#define    THIS_FILE_ID        PS_FILE_ID_MTC_COMM_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ��������
*****************************************************************************/

PS_BOOL_ENUM_UINT8 MTC_GetIntrusionActionEnableFlag(VOS_VOID)
{
    MTC_CFG_ENUM_UINT8                  enIntrusionCfg;
    MTC_CFG_ENUM_UINT8                  enNotchCfg;
    MTC_CFG_ENUM_UINT8                  enNarrowBandDcsCfg;
    MTC_CFG_ENUM_UINT8                  enTlRfCtrlCfg;

    enIntrusionCfg      = MTC_GetIntrusionCfg();
    enNotchCfg          = MTC_GetNotchCfg();
    enNarrowBandDcsCfg  = MTC_GetNarrowBandDcsCfg();
    enTlRfCtrlCfg   = MTC_GetTlRfCtrlCfg();

    if ((MTC_CFG_ENABLE == enIntrusionCfg)
     || (MTC_CFG_ENABLE == enNotchCfg)
     || (MTC_CFG_ENABLE == enNarrowBandDcsCfg)
     || (MTC_CFG_ENABLE == enTlRfCtrlCfg))
    {
        return PS_TRUE;
    }

    return PS_FALSE;
}


VOS_UINT32 MTC_GetOtherModemId(
    MODEM_ID_ENUM_UINT16                enModemId,
    MODEM_ID_ENUM_UINT16               *penOtherModemId
)
{

    if (MODEM_ID_0 == enModemId)
    {
        *penOtherModemId = MODEM_ID_1;
    }
    else if (MODEM_ID_1 == enModemId)
    {
        *penOtherModemId = MODEM_ID_0;
    }
    else
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

VOS_VOID MTC_ProcModem0BufMsg(VOS_VOID)
{
    MTC_MSG_BUF_STRU                       *pstBufAddr     = VOS_NULL_PTR;
    RRC_MTC_INTRUSION_BAND_INFO_IND_STRU   *pstBandInfoMsg      = VOS_NULL_PTR;
    RRC_MTC_USING_FREQ_IND_STRU            *pstUsingFreqInfoMsg = VOS_NULL_PTR;

    /* ���Band��Ϣ�������е�TL Band��Ϣ */
    MTC_ResetNCellBandInfo(MODEM_ID_0);
    MTC_ResetModemCurBandInfo(MODEM_ID_0);

    pstBufAddr          = MTC_GetBufAddr(MODEM_ID_0);
    pstBandInfoMsg      = &(pstBufAddr->stBufBandInfoMsg.stIntrusionBandInfoMsg);
    pstUsingFreqInfoMsg = &(pstBufAddr->stBufUsingFreqInfoMsg.stUsingFreqInfoMsg);

    if (PS_TRUE == pstBufAddr->stBufBandInfoMsg.enExitBufMsgFlag)
    {
        if (PS_TRUE == MTC_IsNeedPopModem0BufMsg(pstBandInfoMsg->stMsgHeader.ulSenderPid))
        {
            /* �建���־ */
            pstBufAddr->stBufBandInfoMsg.enExitBufMsgFlag = PS_FALSE;

            MTC_RcvIntrusionBandInfoInd((VOS_VOID*)pstBandInfoMsg);
        }
    }

    if (PS_TRUE == pstBufAddr->stBufUsingFreqInfoMsg.enExitBufMsgFlag)
    {
        if (PS_TRUE == MTC_IsNeedPopModem0BufMsg(pstUsingFreqInfoMsg->stMsgHeader.ulSenderPid))
        {
            /* �建���־ */
            pstBufAddr->stBufUsingFreqInfoMsg.enExitBufMsgFlag = PS_FALSE;

            MTC_RcvRrcUsingFreqInd((VOS_VOID*)pstUsingFreqInfoMsg);
        }
    }

    return;
}
VOS_VOID MTC_RcvMmaRatModeInd(VOS_VOID *pMsg)
{
    MMA_MTC_RAT_MODE_IND_STRU              *pstRatMode          = VOS_NULL_PTR;
    VOS_UINT32                              ulPid;
    MODEM_ID_ENUM_UINT16                    enModemId;
    MTC_RATMODE_ENUM_UINT8                  enOldRatMode;

    pstRatMode  = (MMA_MTC_RAT_MODE_IND_STRU *)pMsg;
    ulPid       = pstRatMode->stMsgHeader.ulSenderPid;

    /* ���� Pid��ȡmodem ID */
    enModemId   = VOS_GetModemIDFromPid(ulPid);
    if (enModemId >= MODEM_ID_BUTT)
    {
        MTC_ERROR_LOG("MTC_RcvMmaRatModeInd: Modem ID Err.");
        return ;
    }

    enOldRatMode = MTC_GetModemRatMode(enModemId);
    /* ����ģʽ�仯 */
    if (enOldRatMode != pstRatMode->enRatMode)
    {
        /* ����Modem�Ľ���ģʽ */
        MTC_SetModemRatMode(enModemId, pstRatMode->enRatMode);

        /* ģʽ�仯ִ��notch�þ� */
        if (MODEM_ID_0 == enModemId)
        {
            MTC_ProcModem0BufMsg();
        }
    }

    return;
}


VOS_VOID MTC_RcvMmaCurrCampPlmnInfoInd(VOS_VOID *pMsg)
{
    VOS_UINT32                                  ulPid;
    MODEM_ID_ENUM_UINT16                        enModemId;
    MODEM_ID_ENUM_UINT16                        enOtherModemId;
    MMA_MTC_CURR_CAMP_PLMN_INFO_IND_STRU       *pstCurrCampPlmnInfo = VOS_NULL_PTR;
    MTC_MODEM_NETWORK_INFO_STRU                *pstNetworkInfo      = VOS_NULL_PTR;
    MTC_GSM_CELLINFO_EX_STRU                   *pstGsmCellInfoEx    = VOS_NULL_PTR;
    MTC_OPERATOR_CUST_SOLUTION_ENUM_UINT8       enOperatorCustSolution;
    MTC_RATMODE_ENUM_UINT8                      enOldRatMode;

    pstCurrCampPlmnInfo = (MMA_MTC_CURR_CAMP_PLMN_INFO_IND_STRU *)pMsg;
    ulPid               = pstCurrCampPlmnInfo->stMsgHeader.ulSenderPid;

    /* ���� Pid��ȡmodem ID */
    enModemId           = VOS_GetModemIDFromPid(ulPid);
    enOtherModemId      = MODEM_ID_BUTT;

    if (enModemId >= MODEM_ID_BUTT)
    {
        MTC_ERROR_LOG("MTC_RcvMmaCurrCampPlmnInfoInd: Modem ID Err.");
        return ;
    }

    /* ����Modemϵͳ��Ϣ�е�Modem������Ϣ */
    pstNetworkInfo      = MTC_GetModemNetworkInfoAddr(enModemId);
    pstNetworkInfo->stPlmnId                            = pstCurrCampPlmnInfo->stPlmnId;
    pstNetworkInfo->stPsDomainInfo.ucPsSupportFlg       = pstCurrCampPlmnInfo->ucPsSupportFlg;
    pstNetworkInfo->stPsDomainInfo.ucPsAttachAllowFlg   = pstCurrCampPlmnInfo->ucPsAttachAllowFlag;
    pstNetworkInfo->ucIsForbiddenPlmnFlag               = pstCurrCampPlmnInfo->ucIsForbiddenPlmnFlag;

    enOldRatMode = MTC_GetModemRatMode(enModemId);
    if (enOldRatMode != pstCurrCampPlmnInfo->enRatMode)
    {
        MTC_SetModemRatMode(enModemId, pstCurrCampPlmnInfo->enRatMode);

        /* ģʽ�仯ִ��notch�þ� */
        if (MODEM_ID_0 == enModemId)
        {
            MTC_ProcModem0BufMsg();
        }
    }

    if (MTC_RATMODE_GSM != pstCurrCampPlmnInfo->enRatMode)
    {
        /* ģʽ�л�Ϊ��GSMģʽ��Ҫ���GSMС����չ��Ϣ */
        pstGsmCellInfoEx = MTC_GetModemGsmCellInfoEx(enModemId);
        PS_MEM_SET(pstGsmCellInfoEx, 0, sizeof(MTC_GSM_CELLINFO_EX_STRU));
    }

    if (MODEM_ID_2 == enModemId)
    {
        /* ��ǰModem2û��������󣬽�����ȫ�ֱ��� */
        return;
    }

    /* ��ȡ��ǰ��Ӫ�̵Ķ��Ʒ��� */
    enOperatorCustSolution = MTC_GetOperatorCustSolution();

    /* ������֪ͨ��һ��Modem��ǰ��PLMN ID */
    if (VOS_OK == MTC_GetOtherModemId(enModemId, &enOtherModemId))
    {
        /* ֪ͨmodem0��mmc modem1��פ����Ϣ��UTRAN ����T/W��״̬�У�
            �����жϸ�����PLMN����������й����ģ�����W������*/
        MTC_SndMmaOtherModemInfoNotify(enOtherModemId,
                                       &pstCurrCampPlmnInfo->stPlmnId,
                                       VOS_NULL_PTR);
    }

    /* PS��Ǩ�Ʋ��Կ���ʱ�������� */
    if (MTC_PS_TRANSFER_NONE == MTC_GetPsTransferCfg())
    {
        return;
    }

    /* ����Modem0���͵�פ��plmn��Ϣ */
    if (MODEM_ID_0 == enModemId)
    {
        switch (enOperatorCustSolution)
        {
            case MTC_OPERATOR_CUST_CMCC_SVLTE:
                MTC_ProcCurrCampPlmnInfoForSvlte();
                break;
            case MTC_OPERATOR_CUST_CT_LC:
                MTC_ProcCurrCampPlmnInfoForLC();
                break;
            default:
                break;
        }
    }

    return;
}



VOS_VOID MTC_RcvMmaEplmnInfoInd(VOS_VOID *pMsg)
{
    VOS_UINT32                                              ulPid;
    MODEM_ID_ENUM_UINT16                                    enModemId;
    MODEM_ID_ENUM_UINT16                                    enOtherModemId;
    MMA_MTC_EPLMN_INFO_IND_STRU                            *pstEplmnInfo = VOS_NULL_PTR;

    pstEplmnInfo    = (MMA_MTC_EPLMN_INFO_IND_STRU *)pMsg;
    ulPid           = pstEplmnInfo->stMsgHeader.ulSenderPid;

    /* ���� Pid��ȡmodem ID */
    enModemId       = VOS_GetModemIDFromPid(ulPid);
    enOtherModemId  = MODEM_ID_BUTT;

    if (enModemId >= MODEM_ID_BUTT)
    {
        MTC_ERROR_LOG("MTC_RcvMmaEplmnInfoInd: Modem ID Err.");
        return ;
    }

    if (MODEM_ID_2 == enModemId)
    {
        /* Modem2û��EPLMN�������� */
        return;
    }

    /* ֻ����PS��Ǩ�Ʋ���ʹ��ʱ��ִ�к������� */
    if (MTC_PS_TRANSFER_NONE == MTC_GetPsTransferCfg())
    {
        return;
    }

    /* ֻ������SVLTE��������Ҫͬ������Modem�ĵ�ЧPLMN */
    if (MTC_OPERATOR_CUST_CMCC_SVLTE == MTC_GetOperatorCustSolution())
    {
        if (VOS_OK == MTC_GetOtherModemId(enModemId, &enOtherModemId))
        {
            MTC_SndMmaOtherModemInfoNotify(enOtherModemId, VOS_NULL_PTR, &pstEplmnInfo->stEplmnInfo);
        }
    }

    return;
}


VOS_VOID MTC_RcvRrcNcellInfoInd(VOS_VOID * pMsg)
{
    MODEM_ID_ENUM_UINT16                                    enModemId;
    MODEM_ID_ENUM_UINT16                                    enOtherModemId;
    RRC_MTC_NCELL_INFO_IND_STRU                            *pstNcellInfoInd;
    MTC_MMA_TDS_NCELL_INFO_STRU                             stTdsNcellInfo;
    MTC_MMA_LTE_NCELL_INFO_STRU                             stLteNcellInfo;

    pstNcellInfoInd = (RRC_MTC_NCELL_INFO_IND_STRU*)pMsg;
    enModemId       = VOS_GetModemIDFromPid(pstNcellInfoInd->stMsgHeader.ulSenderPid);
    enOtherModemId  = MODEM_ID_BUTT;

    PS_MEM_SET(&stTdsNcellInfo, 0x00, sizeof(stTdsNcellInfo));
    PS_MEM_SET(&stLteNcellInfo, 0x00, sizeof(stLteNcellInfo));

    if (enModemId >= MODEM_ID_BUTT)
    {
        MTC_ERROR1_LOG("MTC_RcvRrcNcellInfoInd: Err ModemId ", enModemId);
        return;
    }

    if (MODEM_ID_2 == enModemId)
    {
        /* Modem2û��NCELL INFO�Ĵ������� */
        return;
    }

    /* ֻ����PS��Ǩ�Ʋ���ʹ��ʱ��ִ�к������� */
    if (MTC_PS_TRANSFER_NONE == MTC_GetPsTransferCfg())
    {
        return;
    }

    /* ֻ������SVLTE��������Ҫ���� */
    if (MTC_OPERATOR_CUST_CMCC_SVLTE == MTC_GetOperatorCustSolution())
    {
        if (VOS_OK == MTC_GetOtherModemId(enModemId, &enOtherModemId))
        {
            stTdsNcellInfo.ucTdsArfcnNum = pstNcellInfoInd->stTdsNCellInfo.ucTdsArfcnNum;
            PS_MEM_CPY(stTdsNcellInfo.ausTdsArfcnList, pstNcellInfoInd->stTdsNCellInfo.ausTdsArfcnList,
                       sizeof(stTdsNcellInfo.ausTdsArfcnList));
            stLteNcellInfo.ucLteArfcnNum = pstNcellInfoInd->stLteNCellInfo.ucLteArfcnNum;
            /* Modified by w00316404 for R11 Update LTE Arf, 2015-07-20, begin */
            PS_MEM_CPY(stLteNcellInfo.aulLteArfcnList, pstNcellInfoInd->stLteNCellInfo.aulLteArfcnList,
                       sizeof(stLteNcellInfo.aulLteArfcnList));
            /* Modified by w00316404 for R11 Update LTE Arf, 2015-07-20, end */
            MTC_SndMmaNcellInfoInd(enOtherModemId, &stTdsNcellInfo, &stLteNcellInfo);
        }
    }

    return;
}


VOS_VOID MTC_RcvMmaRegStatusInd(VOS_VOID *pMsg)
{
    VOS_UINT32                          ulPid;
    MODEM_ID_ENUM_UINT16                enModemId;
    MMA_MTC_REG_STATUS_IND_STRU        *pstRegStatusInd = VOS_NULL_PTR;

    pstRegStatusInd = (MMA_MTC_REG_STATUS_IND_STRU *)pMsg;
    ulPid           = pstRegStatusInd->stMsgHeader.ulSenderPid;

    /* ���� Pid��ȡmodem ID */
    enModemId       = VOS_GetModemIDFromPid(ulPid);
    if (enModemId >= MODEM_ID_BUTT)
    {
        MTC_ERROR_LOG("MTC_RcvMmaRegStatusInd: Modem ID Err.");
        return ;
    }

    /* ���¿��Ƿ���Ч��ʶ */
    MTC_SetModemUsimValidFlag(enModemId, pstRegStatusInd->ucIsUsimValidFlg);
    return;
}
VOS_VOID MTC_SndMmaOtherModemDplmnNplmnInfoNotify(
    MODEM_ID_ENUM_UINT16                enModemId,
    MODEM_ID_ENUM_UINT16                enOtherModemId
)
{
    VOS_UINT32                                              ulMsgLenth;
    VOS_UINT32                                              ulNvLen;
    VOS_UINT32                                              ulReceivePid;
    MTC_MMA_OTHER_MODEM_DPLMN_NPLMN_INFO_NOTIFY_STRU       *pstOtherModemDplmnNplmnInfoNotify = VOS_NULL_PTR;
    NAS_MMC_NVIM_CFG_DPLMN_NPLMN_INFO_STRU                 *pstNvimCfgDPlmnNPlmnInfo = VOS_NULL_PTR;
    NAS_MMC_NVIM_CFG_DPLMN_NPLMN_FLAG_STRU                  stNvimCfgDPlmnNPlmnFlag;

    PS_MEM_SET(&stNvimCfgDPlmnNPlmnFlag, 0, sizeof(stNvimCfgDPlmnNPlmnFlag));
    ulMsgLenth = 0;
    ulNvLen    = 0;
    ulMsgLenth = sizeof(MTC_MMA_OTHER_MODEM_DPLMN_NPLMN_INFO_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH;

    if (MODEM_ID_0 == enOtherModemId)
    {
        ulReceivePid = I0_WUEPS_PID_MMA;
    }
    else if (MODEM_ID_1 == enOtherModemId)
    {
        ulReceivePid = I1_WUEPS_PID_MMA;
    }
    else
    {
        MTC_ERROR_LOG("MTC_SndMmaOtherModemDplmnNplmnInfoNotify: Error Modem Id!");
        return;
    }

    /* ������Ϣ�ռ� */
    pstOtherModemDplmnNplmnInfoNotify = (MTC_MMA_OTHER_MODEM_DPLMN_NPLMN_INFO_NOTIFY_STRU*)PS_ALLOC_MSG(UEPS_PID_MTC, ulMsgLenth);

    if (VOS_NULL_PTR == pstOtherModemDplmnNplmnInfoNotify)
    {
        MTC_ERROR_LOG("MTC_SndMmaOtherModemDplmnNplmnInfoNotify: Alloc msg fail!");
        return;
    }

    /* ����Ϣ�ռ� */
    PS_MEM_SET((VOS_UINT8*)pstOtherModemDplmnNplmnInfoNotify + VOS_MSG_HEAD_LENGTH, 0, ulMsgLenth);

    pstNvimCfgDPlmnNPlmnInfo = (NAS_MMC_NVIM_CFG_DPLMN_NPLMN_INFO_STRU*)PS_MEM_ALLOC(
                                                      UEPS_PID_MTC,
                                                      sizeof(NAS_MMC_NVIM_CFG_DPLMN_NPLMN_INFO_STRU));
    if (VOS_NULL_PTR == pstNvimCfgDPlmnNPlmnInfo)
    {
        PS_FREE_MSG(UEPS_PID_MTC, pstOtherModemDplmnNplmnInfoNotify);
        return;
    }

    NV_GetLength(en_NV_Item_Cfg_Dplmn_Nplmn_Flag, &ulNvLen);

    if (ulNvLen > sizeof(NAS_MMC_NVIM_CFG_DPLMN_NPLMN_FLAG_STRU))
    {
        PS_MEM_FREE(UEPS_PID_MTC, pstNvimCfgDPlmnNPlmnInfo);
        PS_FREE_MSG(UEPS_PID_MTC, pstOtherModemDplmnNplmnInfoNotify);
        return;
    }

    /* ��ȡ��modem��nv�� */
    if (NV_OK != NV_ReadEx(enModemId, en_NV_Item_Cfg_Dplmn_Nplmn_Flag, &stNvimCfgDPlmnNPlmnFlag, ulNvLen))
    {
        PS_MEM_FREE(UEPS_PID_MTC, pstNvimCfgDPlmnNPlmnInfo);
        PS_FREE_MSG(UEPS_PID_MTC, pstOtherModemDplmnNplmnInfoNotify);
        return;
    }

    PS_MEM_SET(pstNvimCfgDPlmnNPlmnInfo, 0x00, sizeof(NAS_MMC_NVIM_CFG_DPLMN_NPLMN_INFO_STRU));

    /* �����Ϣ */
    pstOtherModemDplmnNplmnInfoNotify->stMsgHeader.ulReceiverPid   = ulReceivePid;
    pstOtherModemDplmnNplmnInfoNotify->stMsgHeader.ulMsgName       = ID_MTC_MMA_OTHER_MODEM_DPLMN_NPLMN_INFO_NOTIFY;

    /* dplmn��nplmn֧��nv��رգ��������ȡ�ƶ���ͨ���ŵ�dplmn��nplmn��Ϣ,����֪ͨ */
    if (VOS_FALSE == stNvimCfgDPlmnNPlmnFlag.usCfgDplmnNplmnFlag)
    {
        PS_MEM_FREE(UEPS_PID_MTC, pstNvimCfgDPlmnNPlmnInfo);
        PS_FREE_MSG(UEPS_PID_MTC, pstOtherModemDplmnNplmnInfoNotify);
        return;
    }

    /* Modified by c00318887 for DPlmn���ݺ����Ƚ���HPLMN, 2015-5-28, end */
    NV_GetLength(en_NV_Item_CMCC_Cfg_Dplmn_Nplmn_Info, &ulNvLen);

    if (ulNvLen > sizeof(NAS_MMC_NVIM_CFG_DPLMN_NPLMN_INFO_STRU))
    {
        PS_MEM_FREE(UEPS_PID_MTC, pstNvimCfgDPlmnNPlmnInfo);
        PS_FREE_MSG(UEPS_PID_MTC, pstOtherModemDplmnNplmnInfoNotify);
        return;
    }

    /* ��NV��en_NV_Item_CMCC_Cfg_Dplmn_Nplmn */
    if (NV_OK == NV_ReadEx(enModemId, en_NV_Item_CMCC_Cfg_Dplmn_Nplmn_Info,
                         pstNvimCfgDPlmnNPlmnInfo, ulNvLen))
    {
        PS_MEM_CPY(&pstOtherModemDplmnNplmnInfoNotify->stCmccDplmnNplmnInfo,
            pstNvimCfgDPlmnNPlmnInfo, sizeof(pstOtherModemDplmnNplmnInfoNotify->stCmccDplmnNplmnInfo));
    }

    NV_GetLength(en_NV_Item_UNICOM_Cfg_Dplmn_Nplmn_Info, &ulNvLen);

    if (ulNvLen > sizeof(NAS_MMC_NVIM_CFG_DPLMN_NPLMN_INFO_STRU))
    {
        PS_MEM_FREE(UEPS_PID_MTC, pstNvimCfgDPlmnNPlmnInfo);
        PS_FREE_MSG(UEPS_PID_MTC, pstOtherModemDplmnNplmnInfoNotify);
        return;
    }

    /* ��NV��en_NV_Item_UNICOM_Cfg_Dplmn_Nplmn*/
    if (NV_OK == NV_ReadEx(enModemId, en_NV_Item_UNICOM_Cfg_Dplmn_Nplmn_Info,
                         pstNvimCfgDPlmnNPlmnInfo, ulNvLen))
    {
        PS_MEM_CPY(&pstOtherModemDplmnNplmnInfoNotify->stUnicomDplmnNplmnInfo,
            pstNvimCfgDPlmnNPlmnInfo, sizeof(pstOtherModemDplmnNplmnInfoNotify->stUnicomDplmnNplmnInfo));
    }

    NV_GetLength(en_NV_Item_CT_Cfg_Dplmn_Nplmn_Info, &ulNvLen);

    if (ulNvLen > sizeof(NAS_MMC_NVIM_CFG_DPLMN_NPLMN_INFO_STRU))
    {
        PS_MEM_FREE(UEPS_PID_MTC, pstNvimCfgDPlmnNPlmnInfo);
        PS_FREE_MSG(UEPS_PID_MTC, pstOtherModemDplmnNplmnInfoNotify);
        return;
    }

    /* ��NV��en_NV_Item_CT_Cfg_Dplmn_Nplmn*/
    if (NV_OK == NV_ReadEx(enModemId, en_NV_Item_CT_Cfg_Dplmn_Nplmn_Info,
                         pstNvimCfgDPlmnNPlmnInfo, ulNvLen))
    {
        PS_MEM_CPY(&pstOtherModemDplmnNplmnInfoNotify->stCtDplmnNplmnInfo,
            pstNvimCfgDPlmnNPlmnInfo, sizeof(pstOtherModemDplmnNplmnInfoNotify->stCtDplmnNplmnInfo));
    }
    /* Modified by c00318887 for DPlmn���ݺ����Ƚ���HPLMN, 2015-5-28, end */


    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTC, pstOtherModemDplmnNplmnInfoNotify))
    {
        MTC_ERROR1_LOG("MTC_SndMmaOtherModemDplmnNplmnInfoNotify: Snd Msg err. Rec Pid ", I0_WUEPS_PID_MMA);
        PS_MEM_FREE(UEPS_PID_MTC, pstNvimCfgDPlmnNPlmnInfo);
        return;
    }

    PS_MEM_FREE(UEPS_PID_MTC, pstNvimCfgDPlmnNPlmnInfo);
    return;
}
VOS_VOID MTC_RcvMmaPowerStateInd(VOS_VOID *pMsg)
{
    VOS_UINT32                          ulPid;
    MODEM_ID_ENUM_UINT16                enModemId;
    MMA_MTC_POWER_STATE_IND_STRU       *pstPowerState = VOS_NULL_PTR;
    MTC_CFG_ENUM_UINT8                  enIntrusionCfg;
    MTC_CFG_ENUM_UINT8                  enNotchCfg;

    MTC_CFG_ENUM_UINT8                  enNarrowDcsCfg;
    MTC_CFG_ENUM_UINT8                  enTlRfCtrlCfg;
    MTC_MODEM_MIPI_CLK_PRI_STRU         stMomdemPri;
    VOS_UINT16                          usMipiClk;

    MODEM_ID_ENUM_UINT16                enOtherModemId;

    MTC_PS_TRANSFER_CTX_STRU           *pstPsTransferCtx = VOS_NULL_PTR;

    MTC_MODEM_POWER_STATE_ENUM_UINT8    enPowerState;

    pstPsTransferCtx = MTC_GetPsTransferCtxAddr();

    pstPowerState   = (MMA_MTC_POWER_STATE_IND_STRU *)pMsg;
    ulPid           = pstPowerState->stMsgHeader.ulSenderPid;
    PS_MEM_SET(&stMomdemPri, 0, sizeof(MTC_MODEM_MIPI_CLK_PRI_STRU));

    /* ���� Pid��ȡmodem ID */
    enModemId       = VOS_GetModemIDFromPid(ulPid);
    if (enModemId >= MODEM_ID_BUTT)
    {
        MTC_ERROR_LOG("MTC_RcvMmaPowerStateInd: Modem ID Err.");
        return ;
    }


    if (MTC_MODEM_POWER_ON == pstPowerState->enPowerState)
    {
        if (MODEM_ID_2 != enModemId)
        {
            /* ����ǿ�����Ϣ��������㷢�����ø��ſ���ָʾ */
            if (PS_TRUE == MTC_GetIntrusionActionEnableFlag())
            {
                MTC_SndIntrusionActionSetReq(enModemId, PS_TRUE);
            }

            (VOS_VOID)MTC_GetOtherModemId(enModemId, &enOtherModemId);
            MTC_SndMmaOtherModemDplmnNplmnInfoNotify(enModemId,enOtherModemId);
        }
    }
    else
    {
        /* �յ��ػ�ָʾʱ��Ҫ����Modem��Ϣ */
        MTC_ResetModemInfo(enModemId);

        if (MODEM_ID_2 != enModemId)
        {
            /* �յ��ػ�״ָ̬ʾ����Ҫ����Ӧmodem������RfCellInfo�������¼���bitmap�ϱ���MTA */
            if (MTC_CFG_DISABLE != MTC_GetRfLcdIntrusionCfg())
            {
                MTC_InitRfCellInfo(enModemId);

                /* ���ݸ�modem��ǰ��ҵ��������ȼ� */
                MTC_VerdictModemBitMapPri(&stMomdemPri);

                /* ɸѡ���λͼ */
                usMipiClk = MTC_ProcLcdMipiClkBitMap(&stMomdemPri);

                /* �ϱ�LCD MipiClkλͼ��MTA */
                MTC_SndMtaMipiClkInfoInd(usMipiClk);
            }

            /* �ػ�ʱ����PSTRANSFER���ϱ�״ֵ̬ */
            if (MODEM_ID_0 == enModemId)
            {
                pstPsTransferCtx->enReportCause     = MTC_PS_TRANSFER_CAUSE_BUTT;
                pstPsTransferCtx->enRrcCause        = MTC_PS_TRANSFER_CAUSE_BUTT;
            }
        }
    }

    /* Modified by zwx247453 for K3V3 3 modem TAS, 2015-07-20, Begin */
    /* ��ȡ��ά�ɲ���Ϣ */
    MTC_DEBUG_TraceAllModemConnStateInfo();

    enPowerState = MTC_GetModemPowerState(enModemId);

    /* ���ػ�״̬�����仯 */
    if (pstPowerState->enPowerState != enPowerState)
    {
        /* ���±��ؿ��ػ�״̬ */
        MTC_SetModemPowerState(enModemId, pstPowerState->enPowerState);

        /* ����RCM */
        MTC_SndRcmModemStateInd();
    }
    /* Modified by zwx247453 for K3V3 3 modem TAS, 2015-07-20, End */

    /*Modem2 ��ʱ��������ſ������*/
    if (MODEM_ID_2 != enModemId)
    {
        /* �жϸ��ſ����Ƿ�ʹ�� */
        enIntrusionCfg = MTC_GetIntrusionCfg();
        if (MTC_CFG_ENABLE == enIntrusionCfg)
        {
            /* ���ſ���ʹ�ܣ����ö�ӦModem�Ŀ��ػ�״̬�仯������ */
            MTC_IntrusionModemPowerStateChange(enModemId, pstPowerState->enPowerState);
        }



        /* �ж�Notch�þ��Ƿ�ʹ�� */
        enNotchCfg = MTC_GetNotchCfg();
        if (MTC_CFG_ENABLE == enNotchCfg)
        {
            /* Notch�þ�����ʹ�ܣ�ִ��Notch�þ� */
            MTC_ProcNotchStrategy();
        }

        /* �ж�Narrow band dcs�þ��Ƿ�ʹ�� */
        enNarrowDcsCfg = MTC_GetNarrowBandDcsCfg();
        if (MTC_CFG_ENABLE == enNarrowDcsCfg)
        {
            /* ִ��Narrow band dcs�þ� */
            MTC_ProcNarrowDcsStrategy();
        }

        /* ���ݿ��ػ�״̬����TL��Ƶ�����з��� */
        enTlRfCtrlCfg = MTC_GetTlRfCtrlCfg();
        if (MTC_CFG_ENABLE == enTlRfCtrlCfg)
        {
            MTC_ProcB39B32Intrusion();
        }

        MTC_ProcRseStrategy();
    }

    /* ����ǰMTC�������ϱ���SDT */
    MTC_DEBUG_TraceCtxInfo();

    if (MODEM_ID_1 == enModemId)
    {
        /* VOLTE Rank1����: Modem1�Ŀ��ػ�״̬�仯Ҫ֪ͨ��IMSA */
        MTC_SndImsaModem1InfoInd();
    }

    /* ��ά�ɲ��¼���ػ�״̬�ϱ����� */
    MTC_DEBUG_RcvPowerStateInd(enModemId, pstPowerState->enPowerState);

    return;
}
VOS_VOID MTC_RcvTafCsSrvInfoInd(VOS_VOID *pMsg)
{
    VOS_UINT32                          ulPid;
    MODEM_ID_ENUM_UINT16                enModemId;
    TAF_MTC_CS_SERVICE_INFO_IND_STRU   *pstCsSrvInfo = VOS_NULL_PTR;
    MTC_CS_SERVICE_STATE_ENUM_UINT8     enCsSrvStateOld;
    MTC_CS_SERVICE_STATE_ENUM_UINT8     enCsSrvStateNew;
    MTC_CFG_ENUM_UINT8                  enIntrusionCfg;

    pstCsSrvInfo    = (TAF_MTC_CS_SERVICE_INFO_IND_STRU *)pMsg;
    ulPid           = pstCsSrvInfo->stMsgHeader.ulSenderPid;
    enIntrusionCfg  = MTC_GetIntrusionCfg();

    /* ���� Pid��ȡmodem ID */
    enModemId       = VOS_GetModemIDFromPid(ulPid);
    if (enModemId >= MODEM_ID_BUTT)
    {
        MTC_ERROR_LOG("MTC_RcvMmaPowerStateInd: Modem ID Err.");
        return;
    }

    /* �Ȼ�ȡԭCS�����״̬ */
    enCsSrvStateOld = MTC_GetModemCsSrvExistFlg(enModemId);

    /* ����modem ��Ϣ��CS��ҵ��״̬ */
    MTC_SetModemCallSrvExistFlg(enModemId, pstCsSrvInfo->ucCallSrvExistFlg);
    MTC_SetModemSmsSrvExistFlg(enModemId, pstCsSrvInfo->ucSmsSrvExistFlg);
    MTC_SetModemSsSrvExistFlg(enModemId, pstCsSrvInfo->ucSsSrvExistFlg);

    /* �ڻ�ȡ��ǰCS�����״̬ */
    enCsSrvStateNew = MTC_GetModemCsSrvExistFlg(enModemId);

    /* ��ά�ɲ���Ϣ��¼ */
    MTC_DEBUG_RcvCsSrvInfoInd(enModemId);

    /* ���Modem1��CS�����״̬�����仯���Ҹ��ſ������Կ���������Ҫ�������ſ��Ʋþ� */
    if ( (MODEM_ID_1 == enModemId)
      && (enCsSrvStateNew != enCsSrvStateOld)
      && (MTC_CFG_ENABLE == enIntrusionCfg) )
    {
        MTC_ProcIntrusionStrategy();
    }

    return;
}


VOS_VOID MTC_SndMmaOtherModemInfoNotify(
    MODEM_ID_ENUM_UINT16                enModemId,
    MTC_MMA_PLMN_ID_STRU               *pstCurrCampPlmnId,
    MTC_MMA_EPLMN_INFO_STRU            *pstEplmnInfo
)
{
    VOS_UINT32                                  ulLenth;
    VOS_UINT32                                  ulReceivePid;
    MTC_MMA_OTHER_MODEM_INFO_NOTIFY_STRU       *pstOtherModemInfoNotify = VOS_NULL_PTR;

    ulLenth = sizeof(MTC_MMA_OTHER_MODEM_INFO_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH;

    if (MODEM_ID_0 == enModemId)
    {
        ulReceivePid = I0_WUEPS_PID_MMA;
    }
    else if (MODEM_ID_1 == enModemId)
    {
        ulReceivePid = I1_WUEPS_PID_MMA;
    }
    else
    {
        MTC_ERROR_LOG("MTC_SndMmaOtherModemInfoNotify: Error Modem Id!");
        return;
    }

    /* ������Ϣ�ռ� */
    pstOtherModemInfoNotify = (MTC_MMA_OTHER_MODEM_INFO_NOTIFY_STRU*)PS_ALLOC_MSG(UEPS_PID_MTC, ulLenth);

    if (VOS_NULL_PTR == pstOtherModemInfoNotify)
    {
        MTC_ERROR_LOG("MTC_SndMmaOtherModemInfoNotify: Alloc msg fail!");
        return;
    }

    /* ����Ϣ�ռ� */
    PS_MEM_SET((VOS_UINT8*)pstOtherModemInfoNotify + VOS_MSG_HEAD_LENGTH, 0, ulLenth);

    /* �����Ϣ */
    pstOtherModemInfoNotify->stMsgHeader.ulReceiverPid   = ulReceivePid;
    pstOtherModemInfoNotify->stMsgHeader.ulMsgName       = ID_MTC_MMA_OTHER_MODEM_INFO_NOTIFY;

    if (VOS_NULL_PTR != pstCurrCampPlmnId)
    {
        pstOtherModemInfoNotify->stCurrCampPlmnId.ulMcc = pstCurrCampPlmnId->ulMcc;
        pstOtherModemInfoNotify->stCurrCampPlmnId.ulMnc = pstCurrCampPlmnId->ulMnc;
        pstOtherModemInfoNotify->bitOpCurrCampPlmnId    = VOS_TRUE;
    }

    if (VOS_NULL_PTR != pstEplmnInfo)
    {
        pstOtherModemInfoNotify->bitOpEplmnInfo           = VOS_TRUE;
        pstOtherModemInfoNotify->stEplmnInfo.ucEquPlmnNum = pstEplmnInfo->ucEquPlmnNum;
        PS_MEM_CPY(pstOtherModemInfoNotify->stEplmnInfo.astEquPlmnAddr, pstEplmnInfo->astEquPlmnAddr,
                   sizeof(pstOtherModemInfoNotify->stEplmnInfo.astEquPlmnAddr));
    }

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTC, pstOtherModemInfoNotify))
    {
        MTC_ERROR1_LOG("MTC_SndMmaOtherModemInfoNotify: Snd Msg err. Rec Pid ", I0_WUEPS_PID_MMA);
        return;
    }

    return;
}


VOS_VOID MTC_SndMmaNcellInfoInd(
    MODEM_ID_ENUM_UINT16                enModemId,
    MTC_MMA_TDS_NCELL_INFO_STRU        *pstTddNcellInfo,
    MTC_MMA_LTE_NCELL_INFO_STRU        *pstLteNcellInfo
)
{
    VOS_UINT32                          ulLenth;
    MTC_MMA_NCELL_INFO_IND_STRU        *pstNcellInfoInd = VOS_NULL_PTR;
    VOS_UINT32                          ulReceivePid;

    ulLenth = sizeof(MTC_MMA_NCELL_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    if (MODEM_ID_0 == enModemId)
    {
        ulReceivePid = I0_WUEPS_PID_MMA;
    }
    else if (MODEM_ID_1 == enModemId)
    {
        ulReceivePid = I1_WUEPS_PID_MMA;
    }
    else
    {
        MTC_ERROR_LOG("MTC_SndMmaNcellInfoInd: Error Modem Id!");
        return;
    }

    /* ������Ϣ�ռ� */
    pstNcellInfoInd = (MTC_MMA_NCELL_INFO_IND_STRU*)PS_ALLOC_MSG(UEPS_PID_MTC, ulLenth);

    if (VOS_NULL_PTR == pstNcellInfoInd)
    {
        MTC_ERROR_LOG("MTC_SndMmaNcellInfoInd: Alloc msg fail!");
        return;
    }

    /* ����Ϣ�ռ� */
    PS_MEM_SET((VOS_UINT8*)pstNcellInfoInd + VOS_MSG_HEAD_LENGTH, 0, ulLenth);

    /* �����Ϣ */
    pstNcellInfoInd->stMsgHeader.ulReceiverPid   = ulReceivePid;
    pstNcellInfoInd->stMsgHeader.ulMsgName       = ID_MTC_MMA_NCELL_INFO_IND;

    if (VOS_NULL_PTR != pstTddNcellInfo)
    {
        PS_MEM_CPY(&pstNcellInfoInd->stTdsNcellInfo,
                    pstTddNcellInfo,
                    sizeof(pstNcellInfoInd->stTdsNcellInfo));
    }

    if (VOS_NULL_PTR != pstLteNcellInfo)
    {
        PS_MEM_CPY(&pstNcellInfoInd->stLteNcellInfo,
                    pstLteNcellInfo,
                    sizeof(pstNcellInfoInd->stLteNcellInfo));
    }

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTC, pstNcellInfoInd))
    {
        MTC_ERROR_LOG("MTC_SndMmaNcellInfoInd: Snd Msg err.");
        return;
    }

    return;
}



VOS_VOID MTC_TransCdmaPlmnId(
    VOS_UINT32                          ulSrcPlmnId,
    MTC_MMA_PLMN_ID_STRU               *pstDetPlmnId
)
{
    /* CDMA��PLMN ID��ʽ0x0024005F */
    /* MCC 0x00000402 */
    pstDetPlmnId->ulMcc = 0;
    pstDetPlmnId->ulMcc += (ulSrcPlmnId & 0x00F00000) >> 20;
    pstDetPlmnId->ulMcc += (ulSrcPlmnId & 0x000F0000) >> 8;
    pstDetPlmnId->ulMcc += (ulSrcPlmnId & 0x0000F000) << 4;

    /* MNC 0x000F0500 */
    pstDetPlmnId->ulMnc = 0;
    pstDetPlmnId->ulMnc += (ulSrcPlmnId & 0x00000F00) >> 8;
    pstDetPlmnId->ulMnc += (ulSrcPlmnId & 0x000000F0) << 4;
    pstDetPlmnId->ulMnc += (ulSrcPlmnId & 0x0000000F) << 16;

    return;
}
VOS_UINT32 MTC_IsContainPlmnId(
    MTC_MMA_PLMN_ID_STRU               *pstPlmnId,
    VOS_UINT32                          ulPlmnNum,
    MTC_MMA_PLMN_ID_STRU               *pastSrcPlmnId
)
{
    VOS_UINT32                          ulLoop;

    for (ulLoop = 0; ulLoop < ulPlmnNum; ulLoop++)
    {
        if ( (pstPlmnId->ulMcc == pastSrcPlmnId[ulLoop].ulMcc)
          && (pstPlmnId->ulMnc == pastSrcPlmnId[ulLoop].ulMnc) )
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


VOS_UINT32 MTC_GetEplmnFromOtherRatInfoInd(
    MTC_MMA_EPLMN_INFO_STRU            *pstEplmnInfo,
    CMMCA_OTHER_RAT_INFO_IND_STRU      *pstOtherRatInfoInd
)
{
    VOS_UINT16                          usLoop1;
    VOS_UINT8                           ucLoop2;

    if (pstOtherRatInfoInd->usEarfcnListSize > CMMCA_MAX_ARFCN_NUM)
    {
        MTC_ERROR_LOG("MTC_GetEplmnFromOtherRatInfoInd: usEarfcnListSize too big!");
        return VOS_ERR;
    }

    pstEplmnInfo->ucEquPlmnNum = 0;

    for (usLoop1 = 0; usLoop1 < pstOtherRatInfoInd->usEarfcnListSize; usLoop1++)
    {
        if (pstOtherRatInfoInd->astOtherRatInfo[usLoop1].ucNumPlmn > CMMCA_MAX_EUTRA_NEIGHBOR_PLMN_NUM)
        {
            MTC_ERROR2_LOG("MTC_GetEplmnFromOtherRatInfoInd: ucNumPlmn too big! ",
                           usLoop1,
                           pstOtherRatInfoInd->astOtherRatInfo[usLoop1].ucNumPlmn);
            return VOS_ERR;
        }

        for (ucLoop2 = 0; ucLoop2 < pstOtherRatInfoInd->astOtherRatInfo[usLoop1].ucNumPlmn; ucLoop2++)
        {
            MTC_TransCdmaPlmnId(pstOtherRatInfoInd->astOtherRatInfo[usLoop1].aulPlmnId[ucLoop2],
                                &pstEplmnInfo->astEquPlmnAddr[pstEplmnInfo->ucEquPlmnNum]);

            /* ����ظ�PLNM ID */
            if (VOS_FALSE == MTC_IsContainPlmnId(&pstEplmnInfo->astEquPlmnAddr[pstEplmnInfo->ucEquPlmnNum],
                                                 pstEplmnInfo->ucEquPlmnNum,
                                                 pstEplmnInfo->astEquPlmnAddr))
            {
                pstEplmnInfo->ucEquPlmnNum++;
            }

            if (pstEplmnInfo->ucEquPlmnNum >= MTC_MMA_MAX_EQUPLMN_NUM)
            {
                return VOS_OK;
            }
        }
    }

    return VOS_OK;
}
VOS_UINT32 MTC_GetLteNcellInfoFromOtherRatInfoInd(
    MTC_MMA_LTE_NCELL_INFO_STRU        *pstLteNcellInfo,
    CMMCA_OTHER_RAT_INFO_IND_STRU      *pstOtherRatInfoInd
)
{
    VOS_UINT16                          usLoop;

    if (pstOtherRatInfoInd->usEarfcnListSize > CMMCA_MAX_ARFCN_NUM)
    {
        return VOS_ERR;
    }

    pstLteNcellInfo->ucLteArfcnNum = 0;

    for (usLoop = 0; usLoop < pstOtherRatInfoInd->usEarfcnListSize; usLoop++)
    {
        pstLteNcellInfo->ucLteArfcnNum++;
        /* Modified by w00316404 for R11 Update LTE Arf, 2015-07-20, begin */
        pstLteNcellInfo->aulLteArfcnList[usLoop] = pstOtherRatInfoInd->astOtherRatInfo[usLoop].ulEarfcn;
        /* Modified by w00316404 for R11 Update LTE Arf, 2015-07-20, end */
        if (pstLteNcellInfo->ucLteArfcnNum >= MTC_MMA_LTE_ARFCN_MAX_NUM)
        {
            return VOS_OK;
        }
    }

    return VOS_OK;
}


VOS_VOID MTC_RcvCmmcaOtherRatInfoInd(VOS_VOID* pMsg)
{
    CMMCA_MTC_OTHER_RAT_INFO_IND_STRU  *pstOtherRatInfoInd = VOS_NULL_PTR;
    MTC_MMA_EPLMN_INFO_STRU             stEplmnInfo;
    MTC_MMA_LTE_NCELL_INFO_STRU         stLteNcellInfo;

    PS_MEM_SET(&stEplmnInfo, 0, sizeof(MTC_MMA_EPLMN_INFO_STRU));
    PS_MEM_SET(&stLteNcellInfo, 0, sizeof(MTC_MMA_LTE_NCELL_INFO_STRU));

    pstOtherRatInfoInd = (CMMCA_MTC_OTHER_RAT_INFO_IND_STRU *)pMsg;

    /* PS��Ǩ�Ʋ��Կ���ʱ�������� */
    if (MTC_PS_TRANSFER_NONE == MTC_GetPsTransferCfg())
    {
        return;
    }

    /* �й�����C+L���Ʒ���ִ�к������� */
    if (MTC_OPERATOR_CUST_CT_LC != MTC_GetOperatorCustSolution())
    {
        return;
    }

    /* ��LTE���뼼�����账�� */
    if (CMMCA_MMC_RAT_ID_EUTRAN != pstOtherRatInfoInd->stOtherRatInfo.enRatId)
    {
        return;
    }

    /* ֪ͨMMA��ЧPLMN */
    if (VOS_OK == MTC_GetEplmnFromOtherRatInfoInd(&stEplmnInfo, &(pstOtherRatInfoInd->stOtherRatInfo)))
    {
        MTC_SndMmaOtherModemInfoNotify(MODEM_ID_0, VOS_NULL_PTR, &stEplmnInfo);
    }

    /* ֪ͨMMA LTEƵ����Ϣ */
    if (VOS_OK == MTC_GetLteNcellInfoFromOtherRatInfoInd(&stLteNcellInfo, &(pstOtherRatInfoInd->stOtherRatInfo)))
    {
        MTC_SndMmaNcellInfoInd(MODEM_ID_0, VOS_NULL_PTR, &stLteNcellInfo);
    }

    return;
}

/* Modified by zwx247453 for K3V3 3 modem TAS, 2015-07-20, begin */

VOS_VOID MTC_ProcSetCdmaExtModemConnStateInfo(VOS_VOID* pMsg)
{
    TAF_PS_MSG_STRU                    *pstMsg         = VOS_NULL_PTR;
    TAF_MTC_CDMA_STATE_IND_STRU        *pstCmdStateInd = VOS_NULL_PTR;
    TAF_MTC_CDMA_STATE_INFO_STRU       *pstCdmaState   = VOS_NULL_PTR;
    VOS_UINT32                          ulSndMsgFlag;

    ulSndMsgFlag    = VOS_FALSE;
    pstMsg          = (TAF_PS_MSG_STRU *)pMsg;
    pstCmdStateInd  = (TAF_MTC_CDMA_STATE_IND_STRU *)pstMsg->aucContent;
    pstCdmaState    = (TAF_MTC_CDMA_STATE_INFO_STRU *)&pstCmdStateInd->stCdmaState;

    /* ��ȡ��ά�ɲ���Ϣ */
    MTC_DEBUG_TraceAllModemConnStateInfo();

    /* �����ⲿcdma modem״̬��Ϣ */
    /* �ж�CS״̬�Ƿ�仯 */
    if (pstCdmaState->enCsConnSt != MTC_GetOutSideCsConnStateInfo(MTC_OUTSIDE_MODEM_CDMA))
    {
        ulSndMsgFlag = VOS_TRUE;
        MTC_SetOutSideCsConnStateInfo(MTC_OUTSIDE_MODEM_CDMA, pstCdmaState->enCsConnSt);
    }

    /* �ж�PS״̬�Ƿ�仯 */
    if (pstCdmaState->enPsConnSt != MTC_GetOutSidePsConnStateInfo(MTC_OUTSIDE_MODEM_CDMA))
    {
        ulSndMsgFlag = VOS_TRUE;
        MTC_SetOutSidePsConnStateInfo(MTC_OUTSIDE_MODEM_CDMA, pstCdmaState->enPsConnSt);
    }

    /* �жϿ��ػ�״̬�Ƿ�仯 */
    if (pstCdmaState->enPowerState != MTC_GetOutSideModemPowerState(MTC_OUTSIDE_MODEM_CDMA))
    {
        ulSndMsgFlag = VOS_TRUE;
        MTC_SetOutSideModemPowerState(MTC_OUTSIDE_MODEM_CDMA, pstCdmaState->enPowerState);
    }

    /* �жϿ�״̬�Ƿ�仯 */
    if (pstCdmaState->enUsimmState != MTC_GetOutSideModemUsimmState(MTC_OUTSIDE_MODEM_CDMA))
    {
        ulSndMsgFlag = VOS_TRUE;
        MTC_SetOutSideModemUsimmState(MTC_OUTSIDE_MODEM_CDMA, pstCdmaState->enUsimmState);
    }

    /* ״̬�Ƿ��б仯���仯�ͷ�����Ϣ֪ͨRCM */
    if (VOS_TRUE == ulSndMsgFlag)
    {
        /* ������Ϣ֪ͨRCM */
        MTC_SndRcmModemStateInd();
    }

    return;
}
/* Modified by zwx247453 for K3V3 3 modem TAS, 2015-07-20, end */

VOS_VOID MTC_ProcModemServiceConnStateInd(VOS_VOID *pMsg)
{
    TAF_PS_MSG_STRU                    *pstMsg              = VOS_NULL_PTR;
    TAF_MTC_MODEM_CONN_STATUS_IND_STRU *pstModemStateInd    = VOS_NULL_PTR;
    TAF_MTC_SRV_CONN_STATE_INFO_STRU   *pstModemState       = VOS_NULL_PTR;
    VOS_UINT32                          ulSndMsgFlag;
    VOS_UINT32                          ulPid;
    MODEM_ID_ENUM_UINT16                enModemId;
    TAF_MTC_SRV_CONN_STATE_ENUM_UINT8   enOldsConnState;
    TAF_MTC_SRV_CONN_STATE_ENUM_UINT8   enCurrsConnState;
    MTC_CFG_ENUM_UINT8                  enTlRfCtrlCfg;

    /* ��ȡ��ά�ɲ���Ϣ */
    MTC_DEBUG_TraceAllModemConnStateInfo();

    ulSndMsgFlag        = VOS_FALSE;
    pstMsg              = (TAF_PS_MSG_STRU *)pMsg;
    pstModemStateInd    = (TAF_MTC_MODEM_CONN_STATUS_IND_STRU *)pstMsg->aucContent;
    pstModemState       = (TAF_MTC_SRV_CONN_STATE_INFO_STRU *)&pstModemStateInd->stModemConnStateInfo;
    ulPid               = pstModemStateInd->stCtrl.ulModuleId;
    enOldsConnState     = TAF_MTC_SRV_NO_EXIST;
    enCurrsConnState    = TAF_MTC_SRV_NO_EXIST;

    /* ���� Pid��ȡmodem ID */
    enModemId           = VOS_GetModemIDFromPid(ulPid);
    if (enModemId >= MODEM_ID_BUTT)
    {
        MTC_ERROR_LOG("MTC_ProcModemServiceConnStateInd: Modem ID Err.");
        return ;
    }

    /* ���������ļ� */
    /* CS״̬ */
    if (VOS_TRUE == pstModemState->bitOpCsSrv)
    {
        if (PS_TRUE == MTC_IsNeedSndTasCsInfo2Rcm(enModemId, pstModemState->enCsSrvConnState, MTC_CS_TYPE_GU))
        {
            ulSndMsgFlag        = VOS_TRUE;
        }

        /* �ñ�� */
        MTC_SetCsTypeInfo(enModemId, MTC_CS_TYPE_GU, pstModemState->enCsSrvConnState);
    }

    /* PS״̬ */
    enOldsConnState = MTC_GetPsSrvState(enModemId);
    if (VOS_TRUE == pstModemState->bitOpPsSrv)
    {
        MTC_SetActualPsTypeInfo(enModemId, MTC_PS_TYPE_GU, pstModemState->enPsSrvConnState);
        if (MTC_RATMODE_GSM != MTC_GetModemRatMode(enModemId))
        {
            MTC_SetPsTypeInfo(enModemId, MTC_PS_TYPE_GU, pstModemState->enPsSrvConnState);
        }
        /* GSMҪ��һֱ�ϱ�PS������ */
        else
        {
            MTC_SetPsTypeInfo(enModemId, MTC_PS_TYPE_GU, TAF_MTC_SRV_NO_EXIST);
        }
    }

    /* EPS״̬ */
    if (VOS_TRUE == pstModemState->bitOpEpsSrv)
    {
        MTC_SetPsTypeInfo(enModemId, MTC_PS_TYPE_LTE, pstModemState->enEpsSrvConnState);
        MTC_SetActualPsTypeInfo(enModemId, MTC_PS_TYPE_LTE, pstModemState->enEpsSrvConnState);
    }

    enCurrsConnState = MTC_GetPsSrvState(enModemId);
    if (enCurrsConnState != enOldsConnState)
    {
        ulSndMsgFlag = VOS_TRUE;
    }

    /* ״̬�Ƿ��б仯���仯�ͷ�����Ϣ֪ͨRCM */
    if (VOS_TRUE == ulSndMsgFlag)
    {
        /* ������Ϣ֪ͨRCM */
        MTC_SndRcmModemStateInd();
    }

    /* Modified by zwx247453 for K3V3 3 modem TAS, 2015-07-20, Begin */
    /* ��׷��� */
    enTlRfCtrlCfg = MTC_GetTlRfCtrlCfg();
    if ((MTC_CFG_ENABLE == enTlRfCtrlCfg)
        && (MODEM_ID_2 != enModemId))
    {
        MTC_ProcB39B32Intrusion();
    }
    /* Modified by zwx247453 for K3V3 3 modem TAS, 2015-07-20, End */
    return;
}


VOS_VOID MTC_ProcUsimmStateInd(VOS_VOID *pMsg)
{
    TAF_PS_MSG_STRU                        *pstMsg              = VOS_NULL_PTR;
    TAF_MTC_USIMM_STATUS_IND_STRU          *pstUsimmStateInd    = VOS_NULL_PTR;
    VOS_UINT32                              ulPid;
    MODEM_ID_ENUM_UINT16                    enModemId;
    TAF_MTC_USIMM_CARD_SERVIC_ENUM_UINT16   enUsimmState;


    /* ��ȡ��ά�ɲ���Ϣ */
    MTC_DEBUG_TraceAllModemConnStateInfo();

    pstMsg              = (TAF_PS_MSG_STRU *)pMsg;
    pstUsimmStateInd    = (TAF_MTC_USIMM_STATUS_IND_STRU *)pstMsg->aucContent;
    ulPid               = pstUsimmStateInd->stCtrl.ulModuleId;

    /* ���� Pid��ȡmodem ID */
    enModemId           = VOS_GetModemIDFromPid(ulPid);
    if (enModemId >= MODEM_ID_BUTT)
    {
        MTC_ERROR_LOG("MTC_ProcUsimmStateInd: Modem Id Err.");
        return ;
    }

    enUsimmState       = MTC_GetUsimmStateInfo(enModemId);

    /* �жϿ�״̬�Ƿ�仯 */
    if (pstUsimmStateInd->enUsimmState == enUsimmState)
    {
        return;
    }

    MTC_SetUsimmStateInfo(enModemId, pstUsimmStateInd->enUsimmState);

    /* ������Ϣ֪ͨRCM */
    MTC_SndRcmModemStateInd();

    return;
}

/*****************************************************************************
 �� �� ��  : MTC_RcvTcStatusInfo
 ��������  : MTCģ��֪ͨRCMģ��TC���ز���״̬
 �������  : MsgBlock* pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��6��
    ��    ��   : wx270776
    �޸�����   : �����º���
  2.��    ��   : 2015��7��20��
    ��    ��   : zwx247453
    �޸�����   : 3 modem TAS
*****************************************************************************/
VOS_VOID MTC_RcvTcStatusInfo(
    VOS_VOID                           *pMsg
)
{
    /* Modified by zwx247453 for K3V3 3 modem TAS, 2015-07-20, begin */
    MTC_RCM_TC_STATUS_NOTIFY_STRU      *pstTcStatus  = VOS_NULL_PTR;
    NAS_MTC_TC_STATUS_INFO_IND_STRU    *pstNasMtcMsg = VOS_NULL_PTR;
    MODEM_ID_ENUM_UINT16                enModemId;
    MTC_NAS_TC_STATUS_ENUM_UINT16       enCurTcStat;

    pstNasMtcMsg                      = (NAS_MTC_TC_STATUS_INFO_IND_STRU*)pMsg;
    enModemId                         = VOS_GetModemIDFromPid(pstNasMtcMsg->ulSenderPid);

    if ( enModemId >= MODEM_ID_BUTT )
    {
        MTC_ERROR_LOG("MTC_RcvTcStatusInfo: Modem ID Error!");
        return ;
    }

    enCurTcStat                       = (MTC_NAS_TC_STATUS_ENUM_UINT16)MTC_GetCurrentTcStatus(enModemId);
    /* Modified by zwx247453 for K3V3 3 modem TAS, 2015-07-20, end */

    /* ����յ��ظ��Ļ���״̬��ֱ�ӷ��� */
    if( enCurTcStat == pstNasMtcMsg->enTcStatus )
    {
        return;
    }

    /* ������Ϣ�� */
    pstTcStatus = (MTC_RCM_TC_STATUS_NOTIFY_STRU *)MTC_ALLOC_MSG_WITH_HDR(sizeof(MTC_RCM_TC_STATUS_NOTIFY_STRU));
    if (VOS_NULL_PTR == pstTcStatus)
    {
        MTC_ERROR_LOG("MTC_RcvTcStatusInfo: Alloc Msg Fail!");
        return;
    }

    /* �����Ϣ���� */
    PS_MEM_SET( MTC_GET_MSG_ENTITY(pstTcStatus), 0, MTC_GET_MSG_LENGTH(pstTcStatus) );

    /* �����Ϣͷ */
    MTC_CFG_RCM_MSG_HDR(&pstTcStatus->stMsgHeader, ID_MTC_RCM_TC_STATUS_NOTIFY);

    /* �����Ϣ���� */
    pstTcStatus->enModemId            = enModemId;
    pstTcStatus->enRatMode            = MTC_ConvertRcmRatMode(pstNasMtcMsg->enRatMode);
    pstTcStatus->enTcStatus           = pstNasMtcMsg->enTcStatus;

    /* ��ȫ�ֱ����м�¼����״̬ */
    MTC_SetCurrentTcStatus(enModemId, pstTcStatus->enTcStatus);

    /* ������Ϣ */
    MTC_SEND_MSG(pstTcStatus);

    return;
}

/* Deleted by zwx247453 for K3V3 3 modem TAS, 2015-07-20 */

/*****************************************************************************
 �� �� ��  : MTC_ConvertRcmRatMode
 ��������  : ��NAS��MTC�Ľ��뼼��ת��ΪMTC��RCM����ʽ
 �������  : MTC_NAS_RAT_MODE_ENUM_UINT16   enMtcNasRatMode
 �������  : ��
 �� �� ֵ  : MTC_RCM_RAT_MODE_ENUM_UINT16   enMtcRcmRatMode
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��22��
    ��    ��   : wx270776
    �޸�����   : �����ɺ���
*****************************************************************************/
MTC_RCM_RAT_MODE_ENUM_UINT16 MTC_ConvertRcmRatMode(
    MTC_NAS_RAT_MODE_ENUM_UINT16        enMtcNasRatMode
)
{
    MTC_RCM_RAT_MODE_ENUM_UINT16        enMtcRcmRatMode;

    switch(enMtcNasRatMode)
    {
    case MTC_NAS_RAT_MODE_GSM:
        enMtcRcmRatMode = MTC_RCM_RAT_MODE_GSM;
        break;

    case MTC_NAS_RAT_MODE_WCDMA:
        enMtcRcmRatMode = MTC_RCM_RAT_MODE_WCDMA;
        break;

    case MTC_NAS_RAT_MODE_TDSCDMA:
        enMtcRcmRatMode = MTC_RCM_RAT_MODE_TDSCDMA;
        break;

    case MTC_NAS_RAT_MODE_LTE:
        enMtcRcmRatMode = MTC_RCM_RAT_MODE_LTE;
        break;

    case MTC_NAS_RAT_MODE_CDMA:
        enMtcRcmRatMode = MTC_RCM_RAT_MODE_CDMA;
        break;

    default:
        enMtcRcmRatMode = MTC_RCM_RAT_MODE_BUTT;
        break;
    }

    return enMtcRcmRatMode;
}


#if (FEATURE_ON == FEATURE_IMS)
/* Modified by zwx247453 for K3V3 3 modem TAS, 2015-07-20, begin */

VOS_VOID MTC_ProcImsaSrvConnStateInfo(VOS_VOID* pMsg)
{

    IMSA_MTC_SRV_CONN_STATUS_NOTIFY_STRU   *pstImsaStatus;
    VOS_UINT32                              ulSndRcmFlag;
    MODEM_ID_ENUM_UINT16                    enModemId;
    MTC_CFG_ENUM_UINT8                      enTlRfCtrlCfg;
    TAF_MTC_SRV_CONN_STATE_ENUM_UINT8       enCsSrvConnState;

    ulSndRcmFlag    = VOS_FALSE;
    pstImsaStatus   = (IMSA_MTC_SRV_CONN_STATUS_NOTIFY_STRU *)pMsg;
    enModemId       = VOS_GetModemIDFromPid(pstImsaStatus->ulSenderPid);

    if (enModemId >= MODEM_ID_BUTT)
    {
        MTC_ERROR_LOG("MTC_ProcImsaSrvConnStateInfo: Modem ID Error!");
        return ;
    }

    if ( IMSA_SRV_CONN_STATUS_IS_EXIST == pstImsaStatus->enIsImsSrvExist)
    {
        enCsSrvConnState = TAF_MTC_SRV_EXIST;
    }
    else
    {
        enCsSrvConnState = TAF_MTC_SRV_NO_EXIST;
    }

    if (PS_TRUE == MTC_IsNeedSndTasCsInfo2Rcm(enModemId, enCsSrvConnState, MTC_CS_TYPE_IMS))
    {
        ulSndRcmFlag    = VOS_TRUE;
    }

    /* ����IMS��� */
    MTC_SetCsTypeInfo(enModemId, MTC_CS_TYPE_IMS, enCsSrvConnState);

    if (VOS_TRUE == ulSndRcmFlag)
    {
        /* ������Ϣ֪ͨRCM */
        MTC_SndRcmModemStateInd();
    }

    /* ��׷��� */
    enTlRfCtrlCfg = MTC_GetTlRfCtrlCfg();
    if ((MTC_CFG_ENABLE == enTlRfCtrlCfg)
        && (MODEM_ID_2 != enModemId))
    {
        MTC_ProcB39B32Intrusion();
    }

    return;

}
/* Modified by zwx247453 for K3V3 3 modem TAS, 2015-07-20, end */
#endif
VOS_VOID MTC_RcvGsmCellInfoExInd(VOS_VOID *pMsg)
{
    RRC_MTC_GSM_CELL_INFO_EX_IND_STRU  *pstGsmCellInfoExInd = VOS_NULL_PTR;
    MTC_GSM_CELLINFO_EX_STRU           *pstGsmCellInfoEx    = VOS_NULL_PTR;
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulPid;

    pstGsmCellInfoExInd = (RRC_MTC_GSM_CELL_INFO_EX_IND_STRU *)pMsg;
    ulPid               = pstGsmCellInfoExInd->stMsgHeader.ulSenderPid;

    /* ���� Pid��ȡmodem ID */
    enModemId       = VOS_GetModemIDFromPid(ulPid);
    if (enModemId >= MODEM_ID_BUTT)
    {
        MTC_ERROR_LOG("MTC_RcvGsmCellInfoExInd: Modem ID Err.");
        return ;
    }

    pstGsmCellInfoEx = MTC_GetModemGsmCellInfoEx(enModemId);
    pstGsmCellInfoEx->ulValidFlg        = VOS_TRUE;
    pstGsmCellInfoEx->stPlmnId.ulMcc    = pstGsmCellInfoExInd->stGsmCellInfoEx.stPlmnId.ulMcc;
    pstGsmCellInfoEx->stPlmnId.ulMnc    = pstGsmCellInfoExInd->stGsmCellInfoEx.stPlmnId.ulMnc;
    pstGsmCellInfoEx->usLac             = pstGsmCellInfoExInd->stGsmCellInfoEx.usLac;
    pstGsmCellInfoEx->usCellId          = pstGsmCellInfoExInd->stGsmCellInfoEx.usCellId;

    return;
}
VOS_VOID MTC_RcvMtaGsmCellInfoQryReq(VOS_VOID *pMsg)
{
    MTA_MTC_RESERVE_STRU               *pstReqMsg           = VOS_NULL_PTR;
    VOS_UINT32                          ulLenth;
    MTC_MTA_GSM_CELLINFO_QRY_CNF_STRU  *pstCnfMsg           = VOS_NULL_PTR;
    MTC_GSM_CELLINFO_EX_STRU           *pstGsmCellInfoEx    = VOS_NULL_PTR;

    pstReqMsg = (MTA_MTC_RESERVE_STRU *)pMsg;

    /* ������Modem0 MTAģ��Ĳ�ѯ���� */
    if (UEPS_PID_MTA != pstReqMsg->stMsgHeader.ulSenderPid)
    {
        return;
    }

    ulLenth = sizeof(MTC_MTA_GSM_CELLINFO_QRY_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    /* ������Ϣ�ռ� */
    pstCnfMsg = (MTC_MTA_GSM_CELLINFO_QRY_CNF_STRU *)PS_ALLOC_MSG(UEPS_PID_MTC, ulLenth);

    if (VOS_NULL_PTR == pstCnfMsg)
    {
        MTC_ERROR_LOG("MTC_RcvMtaGsmCellInfoQryReq: Alloc msg fail!");
        return;
    }

    /* ����Ϣ�ռ� */
    PS_MEM_SET((VOS_UINT8*)pstCnfMsg + VOS_MSG_HEAD_LENGTH, 0, ulLenth);

    /* �����Ϣ */
    pstCnfMsg->stMsgHeader.ulReceiverPid    = UEPS_PID_MTA;
    pstCnfMsg->stMsgHeader.ulMsgName        = ID_MTC_MTA_GSM_CELLINFO_QRY_CNF;

    pstGsmCellInfoEx = MTC_GetModemGsmCellInfoEx(MODEM_ID_1);

    pstCnfMsg->enResult                     = MTA_MTC_RESULT_NO_ERROR;
    pstCnfMsg->stCellInfoEx.ulValidFlg      = pstGsmCellInfoEx->ulValidFlg;
    pstCnfMsg->stCellInfoEx.stPlmnId        = pstGsmCellInfoEx->stPlmnId;
    pstCnfMsg->stCellInfoEx.usLac           = pstGsmCellInfoEx->usLac;
    pstCnfMsg->stCellInfoEx.usCellId        = pstGsmCellInfoEx->usCellId;

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTC, pstCnfMsg))
    {
        MTC_ERROR_LOG("MTC_RcvMtaGsmCellInfoQryReq: Snd Msg err.");
        return;
    }

    return;
}
VOS_VOID MTC_RcvMmaImsaStateInd(VOS_VOID *pMsg)
{
    VOS_UINT32                          ulPid;
    MMA_MTC_IMSA_STATE_IND_STRU        *pstImsaStateInd = VOS_NULL_PTR;
    MODEM_ID_ENUM_UINT16                enModemId;

    pstImsaStateInd = (MMA_MTC_IMSA_STATE_IND_STRU *)pMsg;
    ulPid           = pstImsaStateInd->stMsgHeader.ulSenderPid;

    /* ���� Pid��ȡmodem ID */
    enModemId       = VOS_GetModemIDFromPid(ulPid);
    if (enModemId >= MODEM_ID_BUTT)
    {
        MTC_ERROR_LOG("MTC_RcvMmaPowerStateInd: Modem ID Err.");
        return ;
    }

    /* ����IMSA���ػ�״̬ */
    MTC_SetModemImsaState(enModemId, pstImsaStateInd->enPowerState);

    if (MTC_MODEM_POWER_ON == pstImsaStateInd->enPowerState)
    {
        /* ����ǿ�����Ϣ����Ҫ����һ��Modem�Ŀ���״̬֪ͨ��IMSA */
        MTC_SndImsaModem1InfoInd();
    }

    return;
}

/* Added by w00316404 for NEXT B26 Project, 2015-6-17, begin */
/*****************************************************************************
 �� �� ��  : MTC_RcvMmaImsVoiceCapInd
 ��������  : MTCģ�����MMAģ��֪ͨ��IMS��������״̬��Ϣ
 �������  : MsgBlock* pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��06��17��
    ��    ��   : w00316404
    �޸�����   : ��������
*****************************************************************************/
VOS_VOID MTC_RcvMmaImsVoiceCapInd(VOS_VOID *pMsg)
{
    MMA_MTC_IMS_VOICE_CAP_IND_STRU     *pstImsVoiceCap  = VOS_NULL_PTR;
    VOS_UINT32                          ulPid;
    MODEM_ID_ENUM_UINT16                enModemId;
    MTC_MODEM_IMS_VOICE_CAP_ENUM_UINT8  enImsVoiceCap;

    pstImsVoiceCap  = (MMA_MTC_IMS_VOICE_CAP_IND_STRU *)pMsg;
    ulPid           = pstImsVoiceCap->stMsgHeader.ulSenderPid;

    /* ����Pid��ȡmodem ID */
    enModemId   = VOS_GetModemIDFromPid(ulPid);
    if (MODEM_ID_0 != enModemId)
    {
        MTC_ERROR_LOG("MTC_RcvMmaImsVoiceCapInd: Modem ID is not MODEM_ID_0.");
        return ;
    }

    /* ��ȡ��ǰIMS��������״̬ */
    enImsVoiceCap = MTC_GetModemImsVoiceCap(enModemId);

    /* IMS��������״̬�����仯ʱ������IMS��������״̬�����͵�RCM */
    if (pstImsVoiceCap->enImsVoiceCap != enImsVoiceCap)
    {
        /* ����IMS��������״̬ */
        MTC_SetModemImsVoiceCap(enModemId, pstImsVoiceCap->enImsVoiceCap);

        MTC_SndRcmModemImsVoiceCapInd();
    }

    return;
}
/* Added by w00316404 for NEXT B26 Project, 2015-6-17, end */

VOS_VOID MTC_ProcBeginSessionInd(VOS_VOID *pMsg)
{
    TAF_PS_MSG_STRU                    *pstMsg              = VOS_NULL_PTR;
    MTC_BEGIN_SESSION_IND_STRU         *pstBeginSessionInd  = VOS_NULL_PTR;
    VOS_UINT32                          ulPid;
    VOS_UINT32                          ulSendMsg2RcmFlag;
    MODEM_ID_ENUM_UINT16                enModemId;
    TAF_MTC_SRV_CONN_STATE_ENUM_UINT8   enCsSrvStatus;
    MTC_SESSION_TYPE_ENUM_UINT8         enSessionType;

    /* ��ȡ��ά�ɲ���Ϣ */
    MTC_DEBUG_TraceAllModemConnStateInfo();

    pstMsg              = (TAF_PS_MSG_STRU *)pMsg;
    pstBeginSessionInd  = (MTC_BEGIN_SESSION_IND_STRU *)pstMsg->aucContent;
    ulPid               = pstBeginSessionInd->stCtrl.ulModuleId;
    ulSendMsg2RcmFlag   = VOS_FALSE;

    /* ���� Pid��ȡmodem ID */
    enModemId           = VOS_GetModemIDFromPid(ulPid);
    if (enModemId >= MODEM_ID_BUTT)
    {
        MTC_ERROR_LOG("MTC_ProcBeginSessionInd: Modem Id Err.");
        return;
    }

    enSessionType       = pstBeginSessionInd->enSessionType;

    /* �ж��Ƿ���CS��Ϣ�ϱ� */
    if(enSessionType >= MTC_SESSION_TYPE_CS_BUTT)
    {
        return;
    }

    /* ��֮ǰû���ϱ���������Ҫ֪ͨRCM */
    enCsSrvStatus = MTC_GetCsSrvState(enModemId);
    if ( (PS_FALSE == MTC_IsCsSessionInfoExit(enModemId))
      && (TAF_MTC_SRV_NO_EXIST == enCsSrvStatus))
    {
        ulSendMsg2RcmFlag = VOS_TRUE;
    }

    /* ��Session ���� */
    MTC_SetCsSessionInfo(enModemId, enSessionType);

    /* ������Ϣ֪ͨRCM */
    if (VOS_TRUE == ulSendMsg2RcmFlag)
    {
        MTC_SndRcmModemStateInd();
    }

    return;
}


VOS_VOID MTC_ProcEndSessionInd(VOS_VOID *pMsg)
{
    TAF_PS_MSG_STRU                    *pstMsg              = VOS_NULL_PTR;
    MTC_END_SESSION_IND_STRU           *pstEndSessionInd    = VOS_NULL_PTR;
    VOS_UINT32                          ulPid;
    VOS_UINT32                          ulSessionValue;
    MODEM_ID_ENUM_UINT16                enModemId;
    MTC_SESSION_TYPE_ENUM_UINT8         enSessionType;
    TAF_MTC_SRV_CONN_STATE_ENUM_UINT8   enCsSrvStatus;

    /* ��ȡ��ά�ɲ���Ϣ */
    MTC_DEBUG_TraceAllModemConnStateInfo();

    pstMsg              = (TAF_PS_MSG_STRU *)pMsg;
    pstEndSessionInd    = (MTC_END_SESSION_IND_STRU *)pstMsg->aucContent;
    ulPid               = pstEndSessionInd->stCtrl.ulModuleId;
    ulSessionValue      = 0;

    /* ���� Pid��ȡmodem ID */
    enModemId           = VOS_GetModemIDFromPid(ulPid);
    if (enModemId >= MODEM_ID_BUTT)
    {
        MTC_ERROR_LOG("MTC_ProcBeginSessionInd: Modem Id Err.");
        return;
    }

    enSessionType       = pstEndSessionInd->enSessionType;

    /* �ж��Ƿ���CS��Ϣ�ϱ� */
    if(enSessionType >= MTC_SESSION_TYPE_CS_BUTT)
    {
        return;
    }

    /* �ж��Ƿ��RCM�ϱ� */
    ulSessionValue  = ~(MTC_SET_BIT(enSessionType));
    enCsSrvStatus   = MTC_GetCsSrvState(enModemId);
    if ( (MTC_NO_SESSION_INFO   == (MTC_GetCsSessionInfo(enModemId) & ulSessionValue))
      && (TAF_MTC_SRV_NO_EXIST  == enCsSrvStatus) )
    {
        /* ���session��¼ */
        MTC_ClearCsSessionInfo(enModemId, enSessionType);

        /* ������Ϣ֪ͨRCM */
        MTC_SndRcmModemStateInd();

        return ;
    }

    /* ���session��¼ */
    MTC_ClearCsSessionInfo(enModemId, enSessionType);

    return;
}
PS_BOOL_ENUM_UINT8 MTC_IsNeedSndTasCsInfo2Rcm(
    MODEM_ID_ENUM_UINT16                enModemId,
    TAF_MTC_SRV_CONN_STATE_ENUM_UINT8   enCsSrvConnState,
    MTC_CS_TYPE_ENUM_UINT8              enCsType
)
{
    PS_BOOL_ENUM_UINT8                  enSndFlag;
    PS_BOOL_ENUM_UINT8                  enCsSessionExit;
    TAF_MTC_SRV_CONN_STATE_ENUM_UINT8   enCsSrvStatus;
    VOS_UINT8                           ucCsTypeInfo;
    VOS_UINT8                           ucCsTypeValue;


    enCsSessionExit     = MTC_IsCsSessionInfoExit(enModemId);
    enCsSrvStatus       = MTC_GetCsSrvState(enModemId);
    enSndFlag           = PS_FALSE;

    switch(enCsType)
    {
        case MTC_CS_TYPE_GU:
            ucCsTypeValue = MTC_SET_BIT(MTC_CS_TYPE_GU);
            break;

        case MTC_CS_TYPE_IMS:
            ucCsTypeValue = MTC_SET_BIT(MTC_CS_TYPE_IMS);
            break;

        case MTC_CS_TYPE_CDMA:
        default:
            return PS_FALSE;
    }

    /* ��״̬ΪCS���� */
    if (TAF_MTC_SRV_EXIST == enCsSrvConnState)
    {
        /* CS״̬�Ƿ��Ǵ��޵��� */
        if ( (PS_FALSE              == enCsSessionExit)
          && (TAF_MTC_SRV_NO_EXIST  == enCsSrvStatus) )
        {
            enSndFlag = PS_TRUE;
        }
        else
        {
            enSndFlag = PS_FALSE;
        }
    }
    else /* ��״̬ΪCS������ */
    {
        /* ֮ǰ��CS ������Ϣ */
        ucCsTypeInfo    = MTC_GetCsTypeInfo(enModemId);

        /* ���֮ǰΨһ���ڵ�ǰ���͵�CS,����е��ޣ���Ҫ֪ͨRCM */
        if ( (ucCsTypeValue == ucCsTypeInfo)
          && (PS_FALSE == enCsSessionExit))
        {
            enSndFlag = PS_TRUE;
        }
        else
        {
            enSndFlag = PS_FALSE;
        }
    }

    return enSndFlag;
}
PS_BOOL_ENUM_UINT8 MTC_IsNeedBufModem0Msg(VOS_UINT32 ulSendPid)
{
    MTC_RATMODE_ENUM_UINT8                  enRatMode;

    enRatMode = MTC_GetModemRatMode(MODEM_ID_0);

    if ( (MTC_RATMODE_GSM == enRatMode)
      && (I0_UEPS_PID_GAS == ulSendPid))
    {
        return PS_FALSE;
    }

    if ( (MTC_RATMODE_WCDMA == enRatMode)
      && (WUEPS_PID_WRR == ulSendPid) )
    {
        return PS_FALSE;
    }

    if ( (MTC_RATMODE_LTE == enRatMode)
      && (PS_PID_ERRC == ulSendPid) )
    {
        return PS_FALSE;
    }

    if ( (MTC_RATMODE_TDS == enRatMode)
      && (TPS_PID_RRC == ulSendPid) )
    {
        return PS_FALSE;
    }

    return PS_TRUE;
}


PS_BOOL_ENUM_UINT8 MTC_IsNeedPopModem0BufMsg(VOS_UINT32 ulSendPid)
{
    MTC_RATMODE_ENUM_UINT8                  enRatMode;

    enRatMode = MTC_GetModemRatMode(MODEM_ID_0);

    if ( (MTC_RATMODE_GSM == enRatMode)
      && (I0_UEPS_PID_GAS == ulSendPid))
    {
        return PS_TRUE;
    }

    if ( (MTC_RATMODE_WCDMA == enRatMode)
      && (WUEPS_PID_WRR == ulSendPid) )
    {
        return PS_TRUE;
    }

    if ( (MTC_RATMODE_LTE == enRatMode)
      && (PS_PID_ERRC == ulSendPid) )
    {
        return PS_TRUE;
    }

    if ( (MTC_RATMODE_TDS == enRatMode)
      && (TPS_PID_RRC == ulSendPid) )
    {
        return PS_TRUE;
    }

    return PS_FALSE;
}


/*lint +e958*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

