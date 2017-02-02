


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/

#include "CDS.h"
#include "CdsUlProc.h"
#include "CdsIpfCtrl.h"
#include "CdsMsgProc.h"
#include "FcFlowCtrlMana.h"
#include "QosFcRabStatus.h"
#include "CdsImsProc.h"
#include "CdsDebug.h"
#if (CDS_FEATURE_ON == CDS_FEATURE_BASTET)
#include "CdsBastetProc.h"
#endif

/*lint -e767*/
/*lint -e524*/
/*lint -e653*/

#define    THIS_FILE_ID        PS_FILE_ID_CDS_MSG_PROC_C
/*lint +e524*/
/*lint +e653*/
/*lint +e767*/

/*****************************************************************************
  2 �ⲿ��������
*****************************************************************************/

/******************************************************************************
   3 ˽�ж���
******************************************************************************/

/******************************************************************************
   4 ȫ�ֱ�������
******************************************************************************/
VOS_UINT32      g_astUlIpfBidToNdisType[] = {
                        CDS_ADS_IP_PACKET_TYPE_DHCP_SERVERV4,
                        CDS_ADS_IP_PACKET_TYPE_ND_SERVERDHCPV6,
                        CDS_ADS_IP_PACKET_TYPE_BUTT,
                        CDS_ADS_IP_PACKET_TYPE_ICMPV6,
                        CDS_ADS_IP_PACKET_TYPE_LINK_FE80,
                        CDS_ADS_IP_PACKET_TYPE_LINK_FF,
                        CDS_ADS_IP_PACKET_TYPE_BUTT};

/*��BID���IP������.ע������Խ��*/
#define  CDS_UL_GET_IPPKT_TYPE_BY_BID(UlIpfBid)    \
                       (g_astUlIpfBidToNdisType[(UlIpfBid) - CDS_UL_IPF_BEARER_ID_DHCPV4])


/******************************************************************************
   5 ����ʵ��
******************************************************************************/




/*lint -e524*/
/*lint -e653*/

VOS_VOID CDS_UlDataIndToAds(TTF_MEM_ST *pstIpPkt)
{
    CDS_ADS_DATA_IND_STRU                *pstDataInd;
    VOS_UINT32                            ulMsgLen;
    IPF_RESULT_STRU                      *pstIpfRlst;
    VOS_UINT16                            usIpfResult;

    if (VOS_NULL_PTR == pstIpPkt)
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"CDS_UlDataIndToAds : Input Para Error.");
        CDS_PRINT_ERROR(CDS_UlDataIndToAds_ENUM,CDS_PRINT_PARA_INPUT_ERR);
        return;
    }

    /*������Ϣ�ڴ�*/
    ulMsgLen = sizeof(CDS_ADS_DATA_IND_STRU) + (pstIpPkt->usUsed - 4);
    pstDataInd = CDS_ALLOC_MSG_WITH_HDR(ulMsgLen);
    if (VOS_NULL_PTR == pstDataInd)
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_UlDataIndToAds : Alloc Msg Fail. Size=.",ulMsgLen);
        CDS_PRINT_ERROR1(CDS_UlDataIndToAds_ENUM,CDS_PRINT_MEM_ALLOC_FAIL,ulMsgLen);
        TTF_MemFree(UEPS_PID_CDS,pstIpPkt);
        return;
    }

    /*��д��Ϣ����*/
    CDS_CFG_MSG_HDR(pstDataInd,ACPU_PID_ADS_UL);
    pstDataInd->enMsgId     = ID_CDS_ADS_IP_PACKET_IND;

    /*��дModemId/RabId/Len*/
    pstDataInd->usLen       = pstIpPkt->usUsed;
    pstDataInd->enModemId   = CDS_UL_GET_MODEMID_FROM_TTF(pstIpPkt);
    pstDataInd->ucRabId     = CDS_UL_GET_RABID_FROM_TTF(pstIpPkt);

    /*����IPF�����BEEARID����д����*/
    usIpfResult = CDS_UL_GET_IPF_RESULT_FORM_TTF(pstIpPkt);
    pstIpfRlst = (IPF_RESULT_STRU *)(&usIpfResult);
    if ((CDS_UL_IPF_BEARER_ID_DHCPV4 <= pstIpfRlst->usBearedId)
         &&(CDS_UL_IPF_BEARER_ID_LL_FF >= pstIpfRlst->usBearedId))
    {
        pstDataInd->enIpPacketType = (VOS_UINT8)CDS_UL_GET_IPPKT_TYPE_BY_BID(pstIpfRlst->usBearedId);
    }
    else
    {
        pstDataInd->enIpPacketType = CDS_ADS_IP_PACKET_TYPE_BUTT;
    }

    /*���ݿ������ͷ�Դ�ڴ�*/
    PS_MEM_CPY(pstDataInd->aucData,pstIpPkt->pData,pstIpPkt->usUsed);
    TTF_MemFree(UEPS_PID_CDS,pstIpPkt);

    /*������Ϣ*/
    CDS_SEND_MSG(pstDataInd);

    CDS_INFO_LOG1(UEPS_PID_CDS,"CDS_UlDataIndToAds: Send Data Succ.Type ",pstIpfRlst->usBearedId);
    CDS_PRINT_INFO1(CDS_UlDataIndToAds_ENUM,CDS_PRINT_SENT_DATA_TO_ADS_INFO,pstIpfRlst->usBearedId);

    return;
}




VOS_UINT32  CDS_GetRanMode(VOS_VOID)
{
    CDS_ENTITY_STRU         *pstCdsEntity;

    /*���CDS��Ӧʵ����Ϣ*/
    pstCdsEntity = CDS_GetCdsEntity(MODEM_ID_0);
    if (VOS_NULL_PTR == pstCdsEntity)
    {
        return MMC_CDS_MODE_BUTT;
    }

    /*����CDSʵ���ģʽ��Ϣ*/
    return pstCdsEntity->enRanMode;
}


VOS_VOID CDS_ChangeRanModeToNULL(CDS_ENTITY_STRU *pstCdsEntity)
{

    CDS_ASSERT(VOS_NULL_PTR != pstCdsEntity);

    CDS_INFO_LOG2(UEPS_PID_CDS,"Enter CDS_ChangeRanModeToNULL.ModemId, PreRanMode :",pstCdsEntity->usModemId,pstCdsEntity->enRanMode);
    CDS_PRINT_INFO2(CDS_ChangeRanModeToNULL_ENUM,LL2_PTR_NULL,pstCdsEntity->usModemId,pstCdsEntity->enRanMode);

    /* ���ؽ���NULLģʽ���� */
    if (MODEM_ID_0 == pstCdsEntity->usModemId)
    {
        Fc_SwitchToNull();
    }

    /*���ý���ģʽ*/
    pstCdsEntity->enRanMode = MMC_CDS_MODE_NULL;

    /*���Service Request��־*/
    pstCdsEntity->ulServiceReqFlg = PS_FALSE;

    /*����GU SR��־*/
    CDS_CLR_GU_ALL_RAB_SR_FLG(pstCdsEntity);

    /*����10ms�����Զ�ʱ��*/
    if (PS_SUCC != CDS_StartTimer(pstCdsEntity,CDS_TMR_ID_DL_10MS_PERIODIC_TMR))
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"CDS_ChangeRanModeToNULL:Start Tmr Fail.");
        CDS_PRINT_ERROR(CDS_ChangeRanModeToNULL_ENUM, CDS_PRINT_START_TIMER_FAIL);
        return;
    }

    CDS_SET_VOICEPREFER_ACT_FLAG(pstCdsEntity,PS_FALSE);
    CDS_ERROR_LOG(UEPS_PID_CDS,"Leave CDS_ChangeRanModeToNULL Succ.");
    CDS_PRINT_ERROR(CDS_ChangeRanModeToNULL_ENUM, CDS_PRINT_PROC_INFO);

    return;
}
VOS_VOID CDS_ChangeRanModeToLTE(CDS_ENTITY_STRU *pstCdsEntity)
{

    CDS_ASSERT(VOS_NULL_PTR != pstCdsEntity);

    CDS_INFO_LOG2(UEPS_PID_CDS,"Enter CDS_ChangeRanModeToLTE. ModemId,PreRanMode :",pstCdsEntity->usModemId,pstCdsEntity->enRanMode);
    CDS_PRINT_INFO2(CDS_ChangeRanModeToLTE_ENUM,CDS_PRINT_PROC_INFO,pstCdsEntity->usModemId,pstCdsEntity->enRanMode);

    if (MODEM_ID_0 == pstCdsEntity->usModemId)
    {
        if (PS_FALSE == pstCdsEntity->ulTestModeFlg)
        {
            Fc_SwitchToLte();
        }
        else
        {
            /* ���ؽ��뻷��ģʽ���� */
            Fc_SwitchToNull();
        }
    }

    /*���ý���ģʽ*/
    pstCdsEntity->enRanMode = MMC_CDS_MODE_LTE;

    /*���Service Request��־*/
    pstCdsEntity->ulServiceReqFlg = PS_FALSE;

    /*����GU SR��־*/
    CDS_CLR_GU_ALL_RAB_SR_FLG(pstCdsEntity);

    /*ֹͣNULL����10ms�����Զ�ʱ��*/
    CDS_StopTimer(pstCdsEntity,CDS_TMR_ID_DL_10MS_PERIODIC_TMR);

    /*�������л�������*/
    CDS_SendUlBuffData(pstCdsEntity);

    CDS_SET_VOICEPREFER_ACT_FLAG(pstCdsEntity,PS_FALSE);

    CDS_ERROR_LOG(UEPS_PID_CDS,"Leave CDS_ChangeRanModeToLTE Succ.");
    CDS_PRINT_ERROR(CDS_ChangeRanModeToLTE_ENUM, CDS_PRINT_PROC_INFO);

    return;
}


VOS_VOID CDS_ChangeRanModeToGU(CDS_ENTITY_STRU *pstCdsEntity)
{

    CDS_ASSERT(VOS_NULL_PTR != pstCdsEntity);

    CDS_INFO_LOG2(UEPS_PID_CDS,"Enter CDS_ChangeRanModeToGU. ModemId,PreRanMode :",pstCdsEntity->usModemId,pstCdsEntity->enRanMode);
    CDS_PRINT_INFO2(CDS_ChangeRanModeToGU_ENUM,CDS_PRINT_PROC_INFO,pstCdsEntity->usModemId,pstCdsEntity->enRanMode);

    if (MODEM_ID_0 == pstCdsEntity->usModemId)
    {
        if (PS_FALSE == pstCdsEntity->ulTestModeFlg)
        {
            Fc_SwitchToGu();
        }
        else
        {
            /* ���ؽ��뻷��ģʽ���� */
            Fc_SwitchToNull();
        }
    }

    /*���ý���ģʽ*/
    pstCdsEntity->enRanMode = MMC_CDS_MODE_GU;

    /*���Service Request��־*/
    pstCdsEntity->ulServiceReqFlg = PS_FALSE;

    /*�����л��淢�͵�RABM*/
    CDS_SendUlBuffDataToRabm(pstCdsEntity,CDS_NAS_ALL_BEARER_ID);

    /*����GU SR��־*/
    CDS_CLR_GU_ALL_RAB_SR_FLG(pstCdsEntity);

    /*ֹͣNULL����10ms�����Զ�ʱ��*/
    CDS_StopTimer(pstCdsEntity,CDS_TMR_ID_DL_10MS_PERIODIC_TMR);

    CDS_SET_VOICEPREFER_ACT_FLAG(pstCdsEntity,PS_FALSE);

    CDS_ERROR_LOG(UEPS_PID_CDS,"Leave CDS_ChangeRanModeToGU Succ.");
    CDS_PRINT_ERROR(CDS_ChangeRanModeToGU_ENUM, CDS_PRINT_PROC_INFO);

    return;
}



VOS_VOID CDS_MMC_MsgProc(MsgBlock  *pstMsg)
{
    MMC_CDS_MODE_CHANGE_IND_STRU        *pstModeChangeInd;
    CDS_ENTITY_STRU                     *pstCdsEntity;
    VOS_UINT16                           usModemId;

    /*�����Ч���ж�*/
    if (VOS_NULL_PTR == pstMsg)
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"CDS_MMC_MsgProc : Input NULL Para.");
        CDS_PRINT_ERROR(CDS_MMC_MsgProc_ENUM,CDS_PRINT_PARA_INPUT_ERR);
        return;
    }

    /*Proc Msg*/
    pstModeChangeInd = (MMC_CDS_MODE_CHANGE_IND_STRU *)((VOS_UINT32)pstMsg);

    /*����Pid���ModemId,����ModemId���Cdsʵ��ָ��*/
    usModemId = VOS_GetModemIDFromPid(pstModeChangeInd->ulSenderPid);
    pstCdsEntity = CDS_GetCdsEntity(usModemId);
    if (VOS_NULL_PTR == pstCdsEntity)
    {
        CDS_ERROR_LOG2(UEPS_PID_CDS,
                       "CDS_MMC_MsgProc : CDS_GetCdsEntity Fail.SenderPid,ModemId",
                       pstModeChangeInd->ulSenderPid,
                       usModemId);
        CDS_PRINT_ERROR2(CDS_MMC_MsgProc_ENUM,CDS_PRINT_GET_ENTITY_FAIL,pstModeChangeInd->ulSenderPid,
                       usModemId);
        return;
    }

    switch(pstModeChangeInd->enMode)
    {
    case MMC_CDS_MODE_NULL:
        CDS_ChangeRanModeToNULL(pstCdsEntity);
        break;

    case MMC_CDS_MODE_GU:
        CDS_ChangeRanModeToGU(pstCdsEntity);
        break;

    case MMC_CDS_MODE_LTE:
        CDS_ChangeRanModeToLTE(pstCdsEntity);
        break;

    default:
        CDS_ERROR_LOG2(UEPS_PID_CDS,
                       "CDS_MMC_MsgProc:Change Ran Mode Error.ModemId,RanMode:",
                       pstCdsEntity->usModemId,
                       pstModeChangeInd->enMode);
        CDS_PRINT_ERROR2(CDS_MMC_MsgProc_ENUM,CDS_PRINT_GET_ACCESS_MODE_FAIL, pstCdsEntity->usModemId,
                       pstModeChangeInd->enMode);
        break;
    }

    return;
}
VOS_VOID CDS_NdStartFilterMsgProc(const MsgBlock  *pstMsg)
{
    NDCLIENT_CDS_START_FILTER_REQ_STRU   *pstReqMsg;
    CDS_NDCLIENT_START_FILTER_CNF_STRU   *pstCnfMsg;
    VOS_UINT32                            ulMsgLen;

    /*����ж�*/
    if (VOS_NULL_PTR == pstMsg)
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"CDS_NdStartFilterMsgProc : Input Para Error.");
        CDS_PRINT_ERROR(CDS_NdStartFilterMsgProc_ENUM,CDS_PRINT_PARA_INPUT_ERR);
        return;
    }

    pstReqMsg = (NDCLIENT_CDS_START_FILTER_REQ_STRU *)((VOS_UINT32)pstMsg);
    if (pstReqMsg->enModemId >= CDS_MAX_MODEM_NUM)
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_NdStartFilterMsgProc : ModemId Error. ModemID.",pstReqMsg->enModemId);
        CDS_PRINT_ERROR1(CDS_NdStartFilterMsgProc_ENUM,CDS_PRINT_MODEM_ID_ERR,pstReqMsg->enModemId);
        return;
    }

    ulMsgLen = sizeof(CDS_NDCLIENT_START_FILTER_CNF_STRU);
    pstCnfMsg = CDS_ALLOC_MSG_WITH_HDR(ulMsgLen);
    if (VOS_NULL_PTR == pstCnfMsg)
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_NdStartFilterMsgProc : Alloc Msg Fail. Size .",ulMsgLen);
        CDS_PRINT_ERROR1(CDS_NdStartFilterMsgProc_ENUM,CDS_PRINT_MEM_ALLOC_FAIL,ulMsgLen);
        return;
    }

    /*��д��Ϣ����*/
    CDS_CFG_MSG_HDR(pstCnfMsg,UEPS_PID_NDCLIENT);
    pstCnfMsg->ulMsgId = ID_CDS_NDCLIENT_START_FILTER_CNF;

    /*����ModemId*/
    pstCnfMsg->enModemId = pstReqMsg->enModemId;
    pstCnfMsg->enRslt    = CDS_EnableDlIPFFilter(pstReqMsg->enModemId);

    /*������Ϣ*/
    CDS_SEND_MSG(pstCnfMsg);

    CDS_INFO_LOG(UEPS_PID_CDS,"CDS_NdStartFilterMsgProc: Send Cnf Msg Succ.");
    CDS_PRINT_ERROR(CDS_NdStartFilterMsgProc_ENUM,CDS_PRINT_PROC_INFO);

    return;
}



VOS_VOID CDS_NdStopFilterMsgProc(const MsgBlock  *pstMsg)
{
    NDCLIENT_CDS_STOP_FILTER_REQ_STRU    *pstReqMsg;
    CDS_NDCLIENT_STOP_FILTER_CNF_STRU    *pstCnfMsg;
    VOS_UINT32                            ulMsgLen;

    /*����ж�*/
    if (VOS_NULL_PTR == pstMsg)
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"CDS_NdStopFilterMsgProc : Input Para Error.");
        CDS_PRINT_ERROR(CDS_NdStopFilterMsgProc_ENUM,CDS_PRINT_PARA_INPUT_ERR);
        return;
    }

    pstReqMsg = (NDCLIENT_CDS_STOP_FILTER_REQ_STRU *)((VOS_UINT32)pstMsg);
    if (pstReqMsg->enModemId >= CDS_MAX_MODEM_NUM)
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_NdStopFilterMsgProc : ModemId Error. ModemID.",pstReqMsg->enModemId);
        CDS_PRINT_ERROR1(CDS_NdStopFilterMsgProc_ENUM,CDS_PRINT_MODEM_ID_ERR,pstReqMsg->enModemId);
        return;
    }

    ulMsgLen = sizeof(CDS_NDCLIENT_STOP_FILTER_CNF_STRU);
    pstCnfMsg = CDS_ALLOC_MSG_WITH_HDR(ulMsgLen);
    if (VOS_NULL_PTR == pstCnfMsg)
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_NdStopFilterMsgProc : Alloc Msg Fail. Size .",ulMsgLen);
        CDS_PRINT_ERROR1(CDS_NdStopFilterMsgProc_ENUM,CDS_PRINT_MEM_ALLOC_FAIL,ulMsgLen);
        return;
    }

    /*��д��Ϣ����*/
    CDS_CFG_MSG_HDR(pstCnfMsg,UEPS_PID_NDCLIENT);
    pstCnfMsg->ulMsgId = ID_CDS_NDCLIENT_STOP_FILTER_CNF;

    /*����ModemId*/
    pstCnfMsg->enModemId = pstReqMsg->enModemId;
    pstCnfMsg->enRslt    = CDS_DisableDlIPFFilter(pstReqMsg->enModemId);

    /*������Ϣ*/
    CDS_SEND_MSG(pstCnfMsg);

    CDS_INFO_LOG(UEPS_PID_CDS,"CDS_NdStopFilterMsgProc: Send Cnf Msg Succ.");

    CDS_PRINT_ERROR(CDS_NdStopFilterMsgProc_ENUM,CDS_PRINT_PROC_INFO);

    return;

}


VOS_VOID CDS_NdDataReqMsgProc(MsgBlock  *pstMsg)
{
    NDCLIENT_CDS_DATA_REQ_STRU      *pstDataReq;
    CDS_ENTITY_STRU                 *pstCdsEntity;
    TTF_MEM_ST                      *pstNdPkt;

    /*����ж�*/
    if (VOS_NULL_PTR == pstMsg)
    {
        CDS_INFO_LOG(UEPS_PID_CDS,"CDS_NdDataReqMsgProc: Input Para Error.");
        CDS_PRINT_ERROR(CDS_NdDataReqMsgProc_ENUM,CDS_PRINT_PARA_INPUT_ERR);
        return;
    }

    pstDataReq = (NDCLIENT_CDS_DATA_REQ_STRU *)((VOS_UINT32)pstMsg);

    /*��Ϣ������Ч�ж�*/
    if (VOS_NULL_PTR == pstDataReq->pstIpPacket)
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"CDS_NdDataReqMsgProc: Packet Pointer NULL.");
        CDS_PRINT_ERROR(CDS_NdDataReqMsgProc_ENUM,LL2_PTR_NULL);
        return;
    }

    if ((CDS_NAS_MIN_BEARER_ID > pstDataReq->ucRabId)
         || (CDS_NAS_MAX_BEARER_ID < pstDataReq->ucRabId))
    {
        TTF_MemFree(UEPS_PID_CDS,pstDataReq->pstIpPacket);
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_NdDataReqMsgProc: Rab Id Error.",pstDataReq->ucRabId);
        CDS_PRINT_ERROR1(CDS_NdDataReqMsgProc_ENUM,CDS_PRINT_RAB_ID_ERR,pstDataReq->ucRabId);
        return;
    }

    CDS_DBG_UL_RECV_ND_PKT_NUM(1);

    /*����ModemId��ȡCDSʵ��*/
    pstCdsEntity = CDS_GetCdsEntity(pstDataReq->enModemId);
    if (VOS_NULL_PTR == pstCdsEntity)
    {
        TTF_MemFree(UEPS_PID_CDS,pstDataReq->pstIpPacket);
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_NdDataReqMsgProc: CDS_GetCdsEntity Error.",pstDataReq->enModemId);
        CDS_PRINT_ERROR1(CDS_NdDataReqMsgProc_ENUM,CDS_PRINT_GET_ENTITY_FAIL,pstDataReq->enModemId);
        return;
    }

    /*�������Ϣ���浽TTF,������RabId����Ϊ���˵Ľ��*/
    pstNdPkt = pstDataReq->pstIpPacket;
    CDS_UL_SAVE_IPFRSLT_MODEMID_RABID_TO_TTF(pstNdPkt,
                                             pstDataReq->ucRabId,
                                             pstDataReq->enModemId,
                                             pstDataReq->ucRabId);

    /*Added by l00304941 for LTE PDU Report, 2015-03-16*/
    CDS_DBG_UL_REC_IP_PKT_INFO(pstNdPkt);
    CDS_DBB_NDCLIENT_DATA_REQ_HOOK(pstNdPkt);

    /*���ýӿڽ����ݷ��͵��տ�*/
    CDS_UlDispatchDataByRanMode(pstCdsEntity,pstNdPkt);
    return;
}


VOS_VOID CDS_NDCLIENT_MsgProc(MsgBlock  *pstMsg)
{
    /*����ж�*/
    if (VOS_NULL_PTR == pstMsg)
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"CDS_NDCLIENT_MsgProc : Input NULL Para.");
        CDS_PRINT_ERROR(CDS_NDCLIENT_MsgProc_ENUM,CDS_PRINT_PARA_INPUT_ERR);
        return;
    }

    switch(TTF_GET_MSG_NAME(pstMsg))
    {
    case ID_NDCLIENT_CDS_START_FILTER_REQ:
        /*�������й���*/
        CDS_NdStartFilterMsgProc(pstMsg);
        break;

    case ID_NDCLIENT_CDS_STOP_FILTER_REQ:
        /*�ر����й���*/
        CDS_NdStopFilterMsgProc(pstMsg);
        break;

    case ID_NDCLIENT_CDS_DATA_REQ:
        /*ת�����ݵ��տ�*/
        CDS_NdDataReqMsgProc(pstMsg);
        break;

    default:
        CDS_INFO_LOG1(UEPS_PID_CDS,"CDS_NDCLIENT_MsgProc: Msg Id Error.MsgID=",TTF_GET_MSG_NAME(pstMsg));
        CDS_PRINT_INFO1(CDS_NDCLIENT_MsgProc_ENUM,CDS_PRINT_GET_MSG_ID_FAIL,TTF_GET_MSG_NAME(pstMsg));
        break;

    }

    return;
}


VOS_VOID CDS_RabmSerivceRequestNotify(VOS_UINT8 ucRabId, CDS_ENTITY_STRU *pstCdsEntity)
{
    CDS_RABM_SERVICE_IND_STRU   *pstIndMsg;
    VOS_UINT32                   ulMsgLen;

    /*����ж�*/
    if (VOS_NULL_PTR == pstCdsEntity)
    {
        CDS_INFO_LOG(UEPS_PID_CDS,"CDS_RabmSerivceRequestNotify Input Para Error.");
        CDS_PRINT_ERROR(CDS_RabmSerivceRequestNotify_ENUM,CDS_PRINT_PARA_INPUT_ERR);
        return ;
    }

    if ((CDS_NAS_MIN_BEARER_ID > ucRabId) || (CDS_NAS_MAX_BEARER_ID < ucRabId))
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_RabmSerivceRequestNotify: Rab Id Error.",ucRabId);
        CDS_PRINT_ERROR1(CDS_RabmSerivceRequestNotify_ENUM,CDS_PRINT_RAB_ID_ERR,ucRabId);
        return;
    }

    /*�Ѿ�������ֱ�ӷ���*/
    if (PS_TRUE == CDS_GET_GU_RAB_SR_FLG(pstCdsEntity,ucRabId))
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_RabmSerivceRequestNotify: Has Trigger SR..",ucRabId);
        CDS_PRINT_ERROR1(CDS_RabmSerivceRequestNotify_ENUM,CDS_PRINT_TRIGGER_SR_ALREADY,ucRabId);
        return;
    }

    CDS_INFO_LOG2(UEPS_PID_CDS,"Enter CDS_RabmSerivceRequestNotify.ModemId,RabId",pstCdsEntity->usModemId,ucRabId);
    CDS_PRINT_INFO2(CDS_RabmSerivceRequestNotify_ENUM,CDS_PRINT_PROC_INFO,pstCdsEntity->usModemId,ucRabId);

    ulMsgLen = sizeof(CDS_RABM_SERVICE_IND_STRU);
    pstIndMsg = CDS_ALLOC_MSG_WITH_HDR(ulMsgLen);
    if (VOS_NULL_PTR == pstIndMsg)
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_RabmSerivceRequestNotify : Alloc Msg Fail. Size .",ulMsgLen);
        CDS_PRINT_ERROR1(CDS_RabmSerivceRequestNotify_ENUM,CDS_PRINT_MEM_ALLOC_FAIL,ulMsgLen);
        return;
    }

    /*��д��Ϣ����*/
    if (MODEM_ID_0 == pstCdsEntity->usModemId)
    {
        CDS_CFG_MSG_HDR(pstIndMsg,I0_WUEPS_PID_RABM);
    }
    else
    {
        CDS_CFG_MSG_HDR(pstIndMsg,I1_WUEPS_PID_RABM);
    }

    pstIndMsg->enMsgId = ID_CDS_RABM_SERVICE_IND;
    pstIndMsg->ucRabId = ucRabId;

    /*������Ϣ*/
    CDS_SEND_MSG(pstIndMsg);

    /*����SR��־*/
    CDS_SET_GU_RAB_SR_FLG(pstCdsEntity,ucRabId);

    CDS_INFO_LOG(UEPS_PID_CDS,"Leave CDS_RabmSerivceRequestNotify: Send Service Ind Msg Succ.");
    CDS_PRINT_INFO(CDS_RabmSerivceRequestNotify_ENUM,CDS_PRINT_PROC_INFO);

    return;

}
VOS_VOID CDS_RabmSendBuffIndMsgProc(const MsgBlock  *pstMsg)
{
    VOS_UINT16                           usModemId;
    CDS_ENTITY_STRU                     *pstCdsEntity;
    CDS_RABM_SEND_BUFF_DATA_IND_STRU    *pstIndMsg;

    CDS_INFO_LOG(UEPS_PID_CDS,"Enter CDS_RabmSendBuffIndMsgProc.");

    CDS_PRINT_INFO(CDS_RabmSendBuffIndMsgProc_ENUM,CDS_PRINT_PROC_INFO);

    /*����ж�*/
    if (VOS_NULL_PTR == pstMsg)
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"CDS_RabmSendBuffIndMsgProc : Input NULL Para.");
        CDS_PRINT_ERROR(CDS_RabmSendBuffIndMsgProc_ENUM,LL2_PTR_NULL);
        return;
    }

    /*����Pid���ModemId,����ModemId���Cdsʵ��ָ��*/
    usModemId = VOS_GetModemIDFromPid(pstMsg->ulSenderPid);
    pstCdsEntity = CDS_GetCdsEntity(usModemId);
    if (VOS_NULL_PTR == pstCdsEntity)
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_RabmSendBuffIndMsgProc : Get CDS Enttiy Fail.",usModemId);
        CDS_PRINT_ERROR1(CDS_RabmSendBuffIndMsgProc_ENUM,CDS_PRINT_GET_ENTITY_FAIL,usModemId);
        return;
    }

    pstIndMsg = (CDS_RABM_SEND_BUFF_DATA_IND_STRU *)((VOS_UINT32)pstMsg);

    /*RABID�ж�*/
    if ((CDS_NAS_MIN_BEARER_ID > pstIndMsg->ucRabId)
         || (CDS_NAS_MAX_BEARER_ID < pstIndMsg->ucRabId))
    {
        CDS_ERROR_LOG2(UEPS_PID_CDS,"CDS_RabmSendBuffIndMsgProc : Rab Id Error.ModemId,RbId",usModemId,pstIndMsg->ucRabId);
        CDS_PRINT_ERROR2(CDS_RabmSendBuffIndMsgProc_ENUM,CDS_PRINT_RAB_ID_ERR,usModemId,pstIndMsg->ucRabId);
        return;
    }

    /*���RAB SR��־*/
    /*lint -e701*/
    CDS_CLR_GU_RAB_SR_FLG(pstCdsEntity,pstIndMsg->ucRabId);
    /*lint +e701*/

    /*�����л��淢�͵�RABM*/
    CDS_SendUlBuffDataToRabm(pstCdsEntity,pstIndMsg->ucRabId);

    CDS_INFO_LOG1(UEPS_PID_CDS,"Leave CDS_RabmSendBuffIndMsgProc. ModemId:",usModemId);
    CDS_PRINT_INFO1(CDS_RabmSendBuffIndMsgProc_ENUM,CDS_PRINT_PROC_INFO,usModemId);

    return;
}


VOS_VOID CDS_RabmFreeBuffIndMsgProc(const MsgBlock  *pstMsg)
{
    VOS_UINT16                           usModemId;
    CDS_ENTITY_STRU                     *pstCdsEntity;
    CDS_RABM_FREE_BUFF_DATA_IND_STRU    *pstIndMsg;

    CDS_INFO_LOG(UEPS_PID_CDS,"Enter CDS_RabmFreeBuffIndMsgProc.");
    CDS_PRINT_INFO(CDS_RabmFreeBuffIndMsgProc_ENUM,CDS_PRINT_PROC_INFO);

    /*����ж�*/
    if (VOS_NULL_PTR == pstMsg)
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"CDS_RabmFreeBuffIndMsgProc : Input Null Para.");
        CDS_PRINT_ERROR(CDS_RabmFreeBuffIndMsgProc_ENUM,LL2_PTR_NULL);
        return;
    }

    /*����Pid���ModemId,����ModemId���Cdsʵ��ָ��*/
    usModemId = VOS_GetModemIDFromPid(pstMsg->ulSenderPid);
    pstCdsEntity = CDS_GetCdsEntity(usModemId);
    if (VOS_NULL_PTR == pstCdsEntity)
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_RabmFreeBuffIndMsgProc : Get CDS Entity Fail.",usModemId);
        CDS_PRINT_ERROR1(CDS_RabmFreeBuffIndMsgProc_ENUM,CDS_PRINT_GET_ENTITY_FAIL,usModemId);
        return;
    }

    pstIndMsg = (CDS_RABM_FREE_BUFF_DATA_IND_STRU *)((VOS_UINT32)pstMsg);

    /*RABID�ж�*/
    if ((CDS_NAS_MIN_BEARER_ID > pstIndMsg->ucRabId)
         || (CDS_NAS_MAX_BEARER_ID < pstIndMsg->ucRabId))
    {
        CDS_ERROR_LOG2(UEPS_PID_CDS,"CDS_RabmFreeBuffIndMsgProc : Rab Id Error.ModemId,RabId",usModemId,pstIndMsg->ucRabId);
        CDS_PRINT_ERROR2(CDS_RabmFreeBuffIndMsgProc_ENUM,CDS_PRINT_RAB_ID_ERR,usModemId,pstIndMsg->ucRabId);
        return;
    }

    /*���ָ��RABID SR��־*/
    /*lint -e701*/
    CDS_CLR_GU_RAB_SR_FLG(pstCdsEntity,pstIndMsg->ucRabId);
    /*lint +e701*/

    /*���ָ��RABID���л���*/
    CDS_UlGUClearBuffData(pstCdsEntity,pstIndMsg->ucRabId);

    CDS_INFO_LOG1(UEPS_PID_CDS,"Leave CDS_RabmFreeBuffIndMsgProc.ModemID:",usModemId);

    CDS_PRINT_INFO1(CDS_RabmFreeBuffIndMsgProc_ENUM,CDS_PRINT_PROC_INFO,usModemId);

    return;
}
VOS_VOID CDS_ProcRabmVoicePreferActIndMsg(const MsgBlock  *pstMsg)
{
    VOS_UINT16                          usModemId;
    CDS_ENTITY_STRU                    *pstCdsEntity;
    RABM_CDS_VOICEPREFER_ACT_IND_STRU  *pstIndMsg;

    CDS_INFO_LOG(UEPS_PID_CDS,"Enter CDS_ProcRabmVoicePreferActIndMsg.");
    CDS_PRINT_INFO(CDS_ProcRabmVoicePreferActIndMsg_ENUM,CDS_PRINT_PROC_INFO);

    /*����ж�*/
    if (VOS_NULL_PTR == pstMsg)
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"CDS_ProcRabmVoicePreferActIndMsg : Input Null Para.");
        CDS_PRINT_ERROR(CDS_ProcRabmVoicePreferActIndMsg_ENUM,LL2_PTR_NULL);
        return;
    }

    /*����Pid���ModemId,����ModemId���Cdsʵ��ָ��*/
    usModemId = VOS_GetModemIDFromPid(pstMsg->ulSenderPid);
    pstCdsEntity = CDS_GetCdsEntity(usModemId);
    if (VOS_NULL_PTR == pstCdsEntity)
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_ProcRabmVoicePreferActIndMsg : Get CDS Entity Fail.",usModemId);
        CDS_PRINT_ERROR1(CDS_ProcRabmVoicePreferActIndMsg_ENUM,CDS_PRINT_GET_ENTITY_FAIL,usModemId);
        return;
    }

    pstIndMsg = (RABM_CDS_VOICEPREFER_ACT_IND_STRU *)((VOS_UINT32)pstMsg);


    /* ����VoicePrefer�����־*/
    CDS_SET_VOICEPREFER_ACT_FLAG(pstCdsEntity,pstIndMsg->ulVoicePreferActInd);

    CDS_INFO_LOG1(UEPS_PID_CDS,"Leave CDS_ProcRabmVoicePreferActIndMsg.ModemID:",usModemId);
    CDS_PRINT_INFO1(CDS_ProcRabmVoicePreferActIndMsg_ENUM,CDS_PRINT_PROC_INFO,usModemId);

    return;
}
VOS_VOID CDS_RABM_MsgProc(const MsgBlock  *pstMsg)
{
    /*����ж�*/
    if (VOS_NULL_PTR == pstMsg)
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"CDS_RABM_MsgProc : Input Para Null.");
        CDS_PRINT_ERROR(CDS_RABM_MsgProc_ENUM,CDS_PRINT_PARA_INPUT_ERR);
        return;
    }

    switch(TTF_GET_MSG_NAME(pstMsg))
    {
    case ID_RABM_CDS_FREE_BUFF_DATA_IND:
        CDS_RabmFreeBuffIndMsgProc(pstMsg);
        break;

    case ID_RABM_CDS_SEND_BUFF_DATA_IND:
        CDS_RabmSendBuffIndMsgProc(pstMsg);
        break;

    case ID_QOS_FC_RABM_RAB_CREATE_IND:
        QosFc_RabCreate(pstMsg);
        break;

    case ID_QOS_FC_RABM_RAB_RELEASE_IND:
        QosFc_RabRelease(pstMsg);
        break;

    case ID_RABM_CDS_VOICEPREFER_ACT_IND:
        CDS_ProcRabmVoicePreferActIndMsg(pstMsg);
        break;

    default:
        CDS_INFO_LOG1(UEPS_PID_CDS,"CDS_RABM_MsgProc : Recv Rabm Msg Id Error.",TTF_GET_MSG_NAME(pstMsg));
        CDS_PRINT_INFO1(CDS_RABM_MsgProc_ENUM,CDS_PRINT_GET_MSG_ID_FAIL,TTF_GET_MSG_NAME(pstMsg));
        break;
    }

    return;
}
VOS_VOID CDS_TmrMsgProc(const MsgBlock  *pstMsg)
{
    REL_TIMER_MSG         *pstTmrMsg;

    if (VOS_NULL_PTR == pstMsg)
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"CDS_TmrMsgProc : Input Para Error.");
        CDS_PRINT_ERROR(CDS_TmrMsgProc_ENUM,CDS_PRINT_PARA_INPUT_ERR);
        return;
    }

    pstTmrMsg = (REL_TIMER_MSG *)((VOS_UINT32)pstMsg);

    switch(pstTmrMsg->ulName)
    {
    case CDS_TMR_ID_DL_10MS_PERIODIC_TMR:
        CDS_Dl10msPeridicTmrTimeoutProc(pstTmrMsg);
        break;

    case CDS_TMR_ID_FC_CHECK_TMR:
        /* ����״̬check */
        QosFc_FlowCtrl();
        break;

    case CDS_TMR_ID_LB_MODE_B_TMR:
        CDS_LoopBackModeBTimeoutProc(pstTmrMsg);
        break;

    case CDS_TMR_ID_ADQ_EMPTY_PROCTECT:
        CDS_AdqEmptyProctectTimeOutProc();
        break;

    case CDS_TMR_ID_UL_DATA_PROCTECT:
        CDS_UlDataProtectTmrTimeoutProc(pstTmrMsg);
        break;

    default:
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_TmrMsgProc : Tmr Msg Name Error.",pstTmrMsg->ulName);
        break;
    }
    return;
}

/*****************************************************************************
 �� �� ��  : CDS_DhcpDataReqMsgProc
 ��������  : ����DHCP���͵�����������Ϣ��CDS��RS����������ת����������
 �������  :
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ  :
    1.��    ��   : 2015��06��10��
      ��    ��   : l00304941
      �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CDS_DhcpDataReqMsgProc(MsgBlock  *pstMsg)
{
    DHCP_CDS_DATA_REQ_STRU          *pstDataReq;
    CDS_ENTITY_STRU                 *pstCdsEntity;
    TTF_MEM_ST                      *pstDhcpPkt;

    /*����ж�*/
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    pstDataReq = (DHCP_CDS_DATA_REQ_STRU *)((VOS_UINT32)pstMsg);

    /*��Ϣ������Ч�ж�*/
    if (VOS_NULL_PTR == pstDataReq->pstIpPacket)
    {
        return;
    }

    if ((CDS_NAS_MIN_BEARER_ID > pstDataReq->ucRabId)
         || (CDS_NAS_MAX_BEARER_ID < pstDataReq->ucRabId))
    {
        TTF_MemFree(UEPS_PID_CDS,pstDataReq->pstIpPacket);
        return;
    }

    CDS_DBG_UL_RECV_DHCP_PKT_NUM(1);

    /*����ModemId��ȡCDSʵ��*/
    pstCdsEntity = CDS_GetCdsEntity(pstDataReq->enModemId);
    if (VOS_NULL_PTR == pstCdsEntity)
    {
        TTF_MemFree(UEPS_PID_CDS,pstDataReq->pstIpPacket);
        return;
    }

    /*�������Ϣ���浽TTF,������RabId����Ϊ���˵Ľ��*/
    pstDhcpPkt = pstDataReq->pstIpPacket;
    CDS_UL_SAVE_IPFRSLT_MODEMID_RABID_TO_TTF(pstDhcpPkt,
                                             pstDataReq->ucRabId,
                                             pstDataReq->enModemId,
                                             pstDataReq->ucRabId);

    /*Added by l00304941 for LTE PDU Report, 2015-03-16*/
    CDS_DBG_UL_REC_IP_PKT_INFO(pstDhcpPkt);
    CDS_DBG_DHCP_DATA_REQ_HOOK(pstDhcpPkt);

    /*���ýӿڽ����ݷ��͵��տ�*/
    CDS_UlDispatchDataByRanMode(pstCdsEntity,pstDhcpPkt);
    return;
}

/*****************************************************************************
 �� �� ��  : CDS_DhcpStartFilterMsgProc
 ��������  : ����DHCP���͵��������й�����Ϣ
 �������  :
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ  :
    1.��    ��   : 2015��06��10��
      ��    ��   : l00304941
      �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CDS_DhcpStartFilterMsgProc(MsgBlock  *pstMsg)
{
    DHCP_CDS_START_FILTER_REQ_STRU       *pstReqMsg;
    CDS_DHCP_START_FILTER_CNF_STRU       *pstCnfMsg;
    VOS_UINT32                            ulMsgLen;

    /*����ж�*/
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    pstReqMsg = (DHCP_CDS_START_FILTER_REQ_STRU *)((VOS_UINT32)pstMsg);
    if (pstReqMsg->enModemId >= CDS_MAX_MODEM_NUM)
    {
        return;
    }

    ulMsgLen = sizeof(CDS_DHCP_START_FILTER_CNF_STRU);
    pstCnfMsg = CDS_ALLOC_MSG_WITH_HDR(ulMsgLen);
    if (VOS_NULL_PTR == pstCnfMsg)
    {
        return;
    }

    /*��д��Ϣ����*/
    CDS_CFG_MSG_HDR(pstCnfMsg,UEPS_PID_DHCP);
    pstCnfMsg->enMsgId = ID_CDS_DHCP_START_FILTER_CNF;

    /*����ModemId*/
    pstCnfMsg->enModemId = pstReqMsg->enModemId;
    pstCnfMsg->enRslt    = CDS_EnableDlIPFFilter(pstReqMsg->enModemId);

    /*������Ϣ*/
    CDS_SEND_MSG(pstCnfMsg);


    return;
}


/*****************************************************************************
 �� �� ��  : CDS_DhcpStopFilterMsgProc
 ��������  : ����DHCP���͵�ֹͣ���й�����Ϣ
 �������  :
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ  :
    1.��    ��   : 2015��06��10��
      ��    ��   : l00304941
      �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CDS_DhcpStopFilterMsgProc(MsgBlock  *pstMsg)
{
    DHCP_CDS_STOP_FILTER_REQ_STRU        *pstReqMsg;
    CDS_DHCP_STOP_FILTER_CNF_STRU        *pstCnfMsg;
    VOS_UINT32                            ulMsgLen;

    /*����ж�*/
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    pstReqMsg = (DHCP_CDS_STOP_FILTER_REQ_STRU *)((VOS_UINT32)pstMsg);
    if (pstReqMsg->enModemId >= CDS_MAX_MODEM_NUM)
    {
        return;
    }

    ulMsgLen = sizeof(CDS_DHCP_STOP_FILTER_CNF_STRU);
    pstCnfMsg = CDS_ALLOC_MSG_WITH_HDR(ulMsgLen);
    if (VOS_NULL_PTR == pstCnfMsg)
    {
        return;
    }

    /*��д��Ϣ����*/
    CDS_CFG_MSG_HDR(pstCnfMsg,UEPS_PID_DHCP);
    pstCnfMsg->enMsgId = ID_CDS_DHCP_STOP_FILTER_CNF;

    /*����ModemId*/
    pstCnfMsg->enModemId = pstReqMsg->enModemId;
    pstCnfMsg->enRslt    = CDS_DisableDlIPFFilter(pstReqMsg->enModemId);

    /*������Ϣ*/
    CDS_SEND_MSG(pstCnfMsg);


    return;

}

/*****************************************************************************
 �� �� ��  : CDS_DHCP_MsgProc
 ��������  : �����յ���DHCP��Ϣ
 �������  : const MsgBlock  *pstMsg
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ  :
    1.��    ��   : 2015��06��10��
      ��    ��   : l00304941
      �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CDS_DHCP_MsgProc(MsgBlock  *pstMsg)
{
    /*����ж�*/
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    switch(TTF_GET_MSG_NAME(pstMsg))
    {
    case ID_DHCP_CDS_DATA_REQ:
        CDS_DhcpDataReqMsgProc(pstMsg);
        break;

    case ID_DHCP_CDS_START_FILTER_REQ:
        CDS_DhcpStartFilterMsgProc(pstMsg);
        break;

    case ID_DHCP_CDS_STOP_FILTER_REQ:
        CDS_DhcpStopFilterMsgProc(pstMsg);
        break;

    default:
        break;
    }
    return;
}


#if (CDS_FEATURE_ON == CDS_FEATURE_LTE)
VOS_VOID CDS_ERabmSerivceRequestNotify(VOS_UINT8 ucEpsbId)
{
    CDS_ERABM_SERVICE_NOTIFY_STRU   *pstNotifyMsg;
    VOS_UINT32                       ulMsgLen;

    /*����ж�*/
    if ((CDS_NAS_MIN_BEARER_ID > ucEpsbId) || (CDS_NAS_MAX_BEARER_ID < ucEpsbId))
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_ERabmSerivceRequestNotify: EpsbId Error.",ucEpsbId);
        CDS_PRINT_ERROR1(CDS_ERabmSerivceRequestNotify_ENUM,CDS_PRINT_EPSB_ID_ERR,ucEpsbId);
        return;
    }

    CDS_INFO_LOG1(UEPS_PID_CDS,"Enter CDS_ERabmSerivceRequestNotify.EpsbId:",ucEpsbId);
    CDS_PRINT_INFO1(CDS_ERabmSerivceRequestNotify_ENUM,CDS_PRINT_PROC_INFO,ucEpsbId);

    ulMsgLen = sizeof(CDS_ERABM_SERVICE_NOTIFY_STRU);
    pstNotifyMsg = CDS_ALLOC_MSG_WITH_HDR(ulMsgLen);
    if (VOS_NULL_PTR == pstNotifyMsg)
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_ERabmSerivceRequestNotify : Alloc Msg Fail. Size .",ulMsgLen);
        CDS_PRINT_ERROR1(CDS_ERabmSerivceRequestNotify_ENUM,CDS_PRINT_MEM_ALLOC_FAIL,ulMsgLen);
       return;
    }

    /*��д��Ϣ����*/
    CDS_CFG_MSG_HDR(pstNotifyMsg,PS_PID_RABM);
    pstNotifyMsg->ulMsgId = ID_CDS_ERABM_SERVICE_NOTIFY;

    /* lihong00150010 emergency tau&service begin */
    pstNotifyMsg->ucRabId = ucEpsbId;
    /* lihong00150010 emergency tau&service end */

    /*������Ϣ*/
    CDS_SEND_MSG(pstNotifyMsg);

    CDS_INFO_LOG(UEPS_PID_CDS,"Leave CDS_ERabmSerivceRequestNotify: Send Service Ind Msg Succ.");
    CDS_PRINT_INFO(CDS_ERabmSerivceRequestNotify_ENUM,CDS_PRINT_PROC_INFO);

    return;


}
VOS_VOID CDS_ERabmSendBuffIndMsgProc(MsgBlock  *pstMsg)
{
    ERABM_CDS_SEND_BUFF_DATA_IND_STRU    *pstSendBufInd;
    CDS_ENTITY_STRU                      *pstCdsEntity;

    /*����ж�*/
    if (VOS_NULL_PTR == pstMsg)
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"CDS_ERabmSendBuffIndMsgProc : Input Null Para.");
        CDS_PRINT_ERROR(CDS_ERabmSendBuffIndMsgProc_ENUM,CDS_PRINT_PARA_INPUT_ERR);
        return;
    }

    pstSendBufInd = (ERABM_CDS_SEND_BUFF_DATA_IND_STRU*)((VOS_UINT32)pstMsg);

    CDS_INFO_LOG1(UEPS_PID_CDS,
                  "CDS_ERabmSendBuffIndMsgProc: Send Data Allowed Type .",
                  pstSendBufInd->enSndBuffDataAllowedType);
    CDS_PRINT_INFO1(CDS_ERabmSendBuffIndMsgProc_ENUM,CDS_PRINT_PROC_INFO,pstSendBufInd->enSndBuffDataAllowedType);

    /*����ModemId���CDSʵ��ָ�룬LNASĬ�ϲ�����Modem0*/
    pstCdsEntity = CDS_GetCdsEntity(MODEM_ID_0);
    if (VOS_NULL_PTR == pstCdsEntity)
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"CDS_ERabmSendBuffIndMsgProc : Get CDS Entity Fail.");
        CDS_PRINT_ERROR(CDS_ERabmSendBuffIndMsgProc_ENUM,CDS_PRINT_GET_ENTITY_FAIL);
        return;
    }

    /*���Service Request��־*/
    pstCdsEntity->ulServiceReqFlg = PS_FALSE;

    /*�������л�������*/
    CDS_SendUlBuffData(pstCdsEntity);

    return;
}


VOS_VOID CDS_ERabmFreeBuffIndMsgProc(const MsgBlock  *pstMsg)
{
    CDS_ENTITY_STRU                      *pstCdsEntity;

    /*����ж�*/
    if (VOS_NULL_PTR == pstMsg)
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"CDS_ERabmFreeBuffIndMsgProc : Input Null Para");
        CDS_PRINT_ERROR(CDS_ERabmFreeBuffIndMsgProc_ENUM,CDS_PRINT_PARA_INPUT_ERR);
        return;
    }

    CDS_INFO_LOG(UEPS_PID_CDS,"Enter CDS_ERabmFreeBuffIndMsgProc");
    CDS_PRINT_INFO(CDS_ERabmFreeBuffIndMsgProc_ENUM,CDS_PRINT_PROC_INFO);

    /*����ModemId���CDSʵ��ָ�룬LNASĬ�ϲ�����Modem0*/
    pstCdsEntity = CDS_GetCdsEntity(MODEM_ID_0);
    if (VOS_NULL_PTR == pstCdsEntity)
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"CDS_ERabmFreeBuffIndMsgProc : Get CDS Entity Fail.");
        CDS_PRINT_ERROR(CDS_ERabmFreeBuffIndMsgProc_ENUM,CDS_PRINT_GET_ENTITY_FAIL);
        return;
    }

    /*���Service Request��־*/
    pstCdsEntity->ulServiceReqFlg = PS_FALSE;

    /*������л�������*/
    CDS_ClearUlBuffData(pstCdsEntity);

    return;
}


VOS_VOID CDS_ERABM_MsgProc(MsgBlock  *pstMsg)
{
    /*����ж�*/
    if (VOS_NULL_PTR == pstMsg)
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"CDS_ERABM_MsgProc : Input Para Error.");
        CDS_PRINT_ERROR(CDS_ERABM_MsgProc_ENUM,CDS_PRINT_PARA_INPUT_ERR);
        return;
    }

    switch(TTF_GET_MSG_NAME(pstMsg))
    {
    case ID_ERABM_CDS_FREE_BUFF_DATA_IND:
        CDS_ERabmFreeBuffIndMsgProc(pstMsg);
        break;

    case ID_ERABM_CDS_SEND_BUFF_DATA_IND:
        CDS_ERabmSendBuffIndMsgProc(pstMsg);
        break;

    case ID_QOS_FC_ERABM_RAB_CREATE_IND:
        QosFc_RabCreate(pstMsg);
        break;

    case ID_QOS_FC_ERABM_RAB_RELEASE_IND:
        QosFc_RabRelease(pstMsg);
        break;

    default:
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_ERABM_MsgProc : Recv Erabm Msg Id Error.",TTF_GET_MSG_NAME(pstMsg));
        CDS_PRINT_ERROR1(CDS_ERABM_MsgProc_ENUM,CDS_PRINT_GET_MSG_ID_FAIL,TTF_GET_MSG_NAME(pstMsg));
        break;
    }

    return;
}
CDS_TEST_MODE_ENUM_UINT32 CDS_GetTestMode(VOS_VOID)
{
    CDS_ENTITY_STRU         *pstCdsEntity;

    /*����ModemId���CDSʵ��ָ�룬LBĬ�ϲ�����Modem0*/
    pstCdsEntity = CDS_GetCdsEntity(MODEM_ID_0);
    if (VOS_NULL_PTR == pstCdsEntity)
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"CDS_GetTestMode : Get CDS Entity Fail.");
        CDS_PRINT_ERROR(CDS_GetTestMode_ENUM,CDS_PRINT_GET_ENTITY_FAIL);
        return CDS_TEST_MODE_BUTT;
    }

    /*����CDSʵ��Ļ���ģʽ*/
    if (PS_TRUE == pstCdsEntity->ulTestModeFlg)
    {
        return CDS_TEST_MODE_ACTIVATED;
    }
    else
    {
        return CDS_TEST_MODE_DEACTIVATED;
    }
}


VOS_VOID CDS_ActLookBackMsgProc(const MsgBlock  *pstMsg)
{
    CDS_ENTITY_STRU         *pstCdsEntity;

    /*�����Ч���ж�*/
    if (VOS_NULL_PTR == pstMsg)
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"CDS_ActLookBackMsgProc : Input Para Error.");
        CDS_PRINT_ERROR(CDS_ActLookBackMsgProc_ENUM,CDS_PRINT_PARA_INPUT_ERR);
        return;
    }

    CDS_INFO_LOG(UEPS_PID_CDS,"Enter CDS_ActLookBackMsgProc");
    CDS_PRINT_INFO(CDS_ActLookBackMsgProc_ENUM,CDS_PRINT_ENTER_FUC_INFO);

    /*����ModemId���CDSʵ��ָ�룬LBĬ�ϲ�����Modem0*/
    pstCdsEntity = CDS_GetCdsEntity(MODEM_ID_0);
    if (VOS_NULL_PTR == pstCdsEntity)
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"CDS_ActLookBackMsgProc : Get CDS Entity Fail.");
        CDS_PRINT_ERROR(CDS_ActLookBackMsgProc_ENUM,CDS_PRINT_GET_ENTITY_FAIL);
        return ;
    }

    /* ���ؽ��뻷��ģʽ���� */
    Fc_SwitchToNull();

    /*���û���ģʽ��־λΪPS_TRUE*/
    pstCdsEntity->ulTestModeFlg = PS_TRUE;
    pstCdsEntity->ulLoopBackState = CDS_LB_STATE_ACTIVE;

    /*���Service Request��־*/
    pstCdsEntity->ulServiceReqFlg = PS_FALSE;

    /*������л���*/
    CDS_ClearUlBuffData(pstCdsEntity);

    /*��ջ��ض���*/
    CDS_ClearLoopBackQue(pstCdsEntity);

    CDS_INFO_LOG(UEPS_PID_CDS,"Leave CDS_ActLookBackMsgProc");
    CDS_PRINT_INFO(CDS_ActLookBackMsgProc_ENUM,CDS_PRINT_LEAVE_FUC_INFO);

    return;
}
VOS_VOID CDS_DeactLookBackMsgProc(const MsgBlock  *pstMsg)
{
    CDS_ENTITY_STRU         *pstCdsEntity;

    /*�����Ч���ж�*/
    if (VOS_NULL_PTR == pstMsg)
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"CDS_DeactLookBackMsgProc : Input Para Error.");
        CDS_PRINT_ERROR(CDS_DeactLookBackMsgProc_ENUM,CDS_PRINT_PARA_INPUT_ERR);
        return;
    }

    CDS_INFO_LOG(UEPS_PID_CDS,"Enter CDS_DeactLookBackMsgProc");

    CDS_PRINT_INFO(CDS_DeactLookBackMsgProc_ENUM,CDS_PRINT_ENTER_FUC_INFO);

    /*����ModemId���CDSʵ��ָ�룬LBĬ�ϲ�����Modem0*/
    pstCdsEntity = CDS_GetCdsEntity(MODEM_ID_0);
    if (VOS_NULL_PTR == pstCdsEntity)
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"CDS_DeactLookBackMsgProc : Get CDS Entity Fail.");
        CDS_PRINT_ERROR(CDS_DeactLookBackMsgProc_ENUM,CDS_PRINT_GET_ENTITY_FAIL);
        return ;
    }

    /* �����˳�����ģʽ���� */
    if (MMC_CDS_MODE_LTE == pstCdsEntity->enRanMode)
    {
        Fc_SwitchToLte();
    }
    else if (MMC_CDS_MODE_GU == pstCdsEntity->enRanMode)
    {
        Fc_SwitchToGu();
    }
    else
    {
        /* ������ */
    }

    /*���û���ģʽ��־λΪPS_FALSE*/
    pstCdsEntity->ulTestModeFlg = PS_FALSE;
    pstCdsEntity->ulLoopBackState = CDS_LB_STATE_DEACTIVE;

    /*���Service Request��־*/
    pstCdsEntity->ulServiceReqFlg = PS_FALSE;

    /*������л���*/
    CDS_ClearUlBuffData(pstCdsEntity);

    /*��ջ��ض���*/
    CDS_ClearLoopBackQue(pstCdsEntity);

    CDS_INFO_LOG(UEPS_PID_CDS,"Leave CDS_DeactLookBackMsgProc");

    CDS_PRINT_INFO(CDS_DeactLookBackMsgProc_ENUM,CDS_PRINT_LEAVE_FUC_INFO);

    return;
}


VOS_VOID CDS_StartLBTestLoopMsgProc(const MsgBlock  *pstMsg)
{
    ETC_CDS_START_TEST_LOOP_NOTIFY_STRU  *pstStartTLMsg;
    CDS_ENTITY_STRU                      *pstCdsEntity;

    /*�����Ч���ж�*/
    CDS_ASSERT(VOS_NULL_PTR != pstMsg);

    CDS_INFO_LOG(UEPS_PID_CDS,"Enter CDS_StartLBTestLoopMsgProc");

    CDS_PRINT_INFO(CDS_StartLBTestLoopMsgProc_ENUM,CDS_PRINT_ENTER_FUC_INFO);

    /*����ModemId���CDSʵ��ָ�룬LBĬ�ϲ�����Modem0*/
    pstCdsEntity = CDS_GetCdsEntity(MODEM_ID_0);
    if (VOS_NULL_PTR == pstCdsEntity)
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_StartLBTestLoopMsgProc : Get CDS_GetCdsEntity Fail.ModemId:",MODEM_ID_0);
        CDS_PRINT_ERROR1(CDS_StartLBTestLoopMsgProc_ENUM,CDS_PRINT_GET_ENTITY_FAIL,MODEM_ID_0);
        return ;
    }

    pstStartTLMsg = (ETC_CDS_START_TEST_LOOP_NOTIFY_STRU*)((VOS_VOID*)pstMsg);

    CDS_INFO_LOG2(UEPS_PID_CDS,"CDS_StartLBTestLoopMsgProc : LB Mode,Timer Len.",pstStartTLMsg->ulLBMode,pstStartTLMsg->ulLBModeBTmrLen);

    CDS_PRINT_INFO2(CDS_StartLBTestLoopMsgProc_ENUM,CDS_PRINT_PROC_INFO,pstStartTLMsg->ulLBMode,pstStartTLMsg->ulLBModeBTmrLen);

    /*���ֻ���ģʽ��Ϣ*/
    if (CDS_ETC_LB_MODE_B == pstStartTLMsg->ulLBMode)
    {
        pstCdsEntity->ulLoopBackMode = CDS_LB_MODE_B;
        if (0 != pstStartTLMsg->ulLBModeBTmrLen)
        {
            CDS_SET_TMR_LEN(pstCdsEntity,
                            CDS_TMR_ID_LB_MODE_B_TMR,
                            pstStartTLMsg->ulLBModeBTmrLen * 1000);
        }
        else
        {
            /*��ʱ��ʱ��Ϊ0����10ms����*/
            CDS_SET_TMR_LEN(pstCdsEntity,
                            CDS_TMR_ID_LB_MODE_B_TMR,
                            CDS_TMR_LEN);
        }
    }
    else
    {
        pstCdsEntity->ulLoopBackMode = CDS_LB_MODE_A;
        CDS_SET_TMR_LEN(pstCdsEntity,CDS_TMR_ID_LB_MODE_B_TMR,0);
    }

    /*���Service Request��־*/
    pstCdsEntity->ulServiceReqFlg = PS_FALSE;
    pstCdsEntity->ulLoopBackState = CDS_LB_STATE_START;

    /*��ջ��ض���*/
    CDS_ClearLoopBackQue(pstCdsEntity);

    CDS_INFO_LOG(UEPS_PID_CDS,"Leave CDS_StartLBTestLoopMsgProc");
     CDS_PRINT_INFO(CDS_StartLBTestLoopMsgProc_ENUM,CDS_PRINT_LEAVE_FUC_INFO);

    return;
}


VOS_VOID CDS_StopLBTestLoopMsgProc(const MsgBlock  *pstMsg)
{
    CDS_ENTITY_STRU                      *pstCdsEntity;

    /*�����Ч���ж�*/
    if (VOS_NULL_PTR == pstMsg)
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"CDS_StopLBTestLoopMsgProc : Input Para Error.");
        CDS_PRINT_ERROR(CDS_StopLBTestLoopMsgProc_ENUM,CDS_PRINT_PARA_INPUT_ERR);
        return;
    }

    CDS_INFO_LOG(UEPS_PID_CDS,"Enter CDS_StopLBTestLoopMsgProc");
    CDS_PRINT_INFO(CDS_StopLBTestLoopMsgProc_ENUM,CDS_PRINT_ENTER_FUC_INFO);

    /*����ModemId���CDSʵ��ָ�룬LBĬ�ϲ�����Modem0*/
    pstCdsEntity = CDS_GetCdsEntity(MODEM_ID_0);
    if (VOS_NULL_PTR == pstCdsEntity)
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_StartLBTestLoopMsgProc : Get CDS_GetCdsEntity Fail.ModemId:",MODEM_ID_0);
        CDS_PRINT_ERROR1(CDS_StopLBTestLoopMsgProc_ENUM,CDS_PRINT_GET_ENTITY_FAIL,MODEM_ID_0);
        return ;
    }

    /*���LB��Ӧ��Ϣ*/
    pstCdsEntity->ulLoopBackMode = CDS_LB_MODE_BUTT;
    CDS_SET_TMR_LEN(pstCdsEntity,CDS_TMR_ID_LB_MODE_B_TMR,0);

    /*���Service Request��־*/
    pstCdsEntity->ulServiceReqFlg = PS_FALSE;
    pstCdsEntity->ulLoopBackState = CDS_LB_STATE_STOP;

    /*��ջ��ض���*/
    CDS_ClearLoopBackQue(pstCdsEntity);

    CDS_INFO_LOG(UEPS_PID_CDS,"Enter CDS_StopLBTestLoopMsgProc");
    CDS_PRINT_INFO(CDS_StopLBTestLoopMsgProc_ENUM,CDS_PRINT_LEAVE_FUC_INFO);
    return;
}
VOS_VOID CDS_ETC_MsgProc(const MsgBlock  *pstMsg)
{
    /*����ж�*/
    if (VOS_NULL_PTR == pstMsg)
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"CDS_ETC_MsgProc : Input Para Error.");
        CDS_PRINT_ERROR(CDS_ETC_MsgProc_ENUM,CDS_PRINT_PARA_INPUT_ERR);
        return;
    }

    switch(TTF_GET_MSG_NAME(pstMsg))
    {
    case ID_ETC_CDS_ACT_TEST_MODE_NOTIFY:
        CDS_ActLookBackMsgProc(pstMsg);
        break;

    case ID_ETC_CDS_DEACT_TEST_MODE_NOTIFY:
        CDS_DeactLookBackMsgProc(pstMsg);
        break;

    case ID_ETC_CDS_START_TEST_LOOP_NOTIFY:
        CDS_StartLBTestLoopMsgProc(pstMsg);
        break;

    case ID_ETC_CDS_STOP_TEST_LOOP_NOTIFY:
        CDS_StopLBTestLoopMsgProc(pstMsg);
        break;

    default:
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_ETC_MsgProc : Recv ETC Msg Id Error.",TTF_GET_MSG_NAME(pstMsg));
        CDS_PRINT_ERROR1(CDS_ETC_MsgProc_ENUM,CDS_PRINT_GET_MSG_ID_FAIL,TTF_GET_MSG_NAME(pstMsg));
        break;
    }

    return;
}

#endif

#if (CDS_FEATURE_ON == CDS_FEATURE_CDMA)
/*****************************************************************************
 �� �� ��  : CDS_APSServiceRequestNotify
 ��������  : CDS֪ͨAPS����SERVICE REQUEST
 �������  : VOS_UINT8 ucRabId
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ  :
    1.��    ��   : 2014��10��25��
      ��    ��   : l00304941
      �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CDS_APSServiceRequestNotify(CDS_ENTITY_STRU *pstCdsEntity, VOS_UINT8 ucRabId)
{
    CDS_APS_CDATA_SERVICE_IND_STRU                *pstNotifyMsg;
    VOS_UINT32                                     ulMsgLen;

    /*����ж�*/
    if (VOS_NULL_PTR == pstCdsEntity)
    {
        CDS_INFO_LOG(UEPS_PID_CDS,"CDS_APSServiceRequestNotify Input Para Error.");
        CDS_PRINT_ERROR(CDS_APSServiceRequestNotify_ENUM,CDS_PRINT_PARA_INPUT_ERR);
        return ;
    }

    if ((CDS_NAS_MIN_BEARER_ID > ucRabId) || (CDS_NAS_MAX_BEARER_ID < ucRabId))
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_APSServiceRequestNotify: ucRabId Error.",ucRabId);
        CDS_PRINT_ERROR1(CDS_APSServiceRequestNotify_ENUM,CDS_PRINT_RAB_ID_ERR,ucRabId);
        return;
    }

    /*�Ѿ�������ֱ�ӷ���*/
    if (PS_TRUE == CDS_GET_CDMA_RAB_SR_FLG(pstCdsEntity,ucRabId))
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_APSServiceRequestNotify: Has Trigger SR..",ucRabId);
        CDS_PRINT_ERROR1(CDS_APSServiceRequestNotify_ENUM,CDS_PRINT_TRIGGER_SR_ALREADY,ucRabId);
        return;
    }

    CDS_INFO_LOG2(UEPS_PID_CDS,"Enter CDS_APSServiceRequestNotify.ModemId,RabId",pstCdsEntity->usModemId,ucRabId);
    CDS_PRINT_INFO2(CDS_APSServiceRequestNotify_ENUM, CDS_PRINT_ENTER_FUC_INFO,pstCdsEntity->usModemId,ucRabId);


    ulMsgLen = sizeof(CDS_APS_CDATA_SERVICE_IND_STRU);
    pstNotifyMsg = CDS_ALLOC_MSG_WITH_HDR(ulMsgLen);
    if (VOS_NULL_PTR == pstNotifyMsg)
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_APSServiceRequestNotify : Alloc Msg Fail. Size .",ulMsgLen);
        CDS_PRINT_ERROR1(CDS_APSServiceRequestNotify_ENUM,CDS_PRINT_MEM_ALLOC_FAIL,ulMsgLen);
        return;
    }

    /*��д��Ϣ����*/
    CDS_CFG_MSG_HDR(pstNotifyMsg,WUEPS_PID_TAF);
    pstNotifyMsg->enMsgId = ID_CDS_APS_CDATA_SERVICE_IND;
    pstNotifyMsg->ucRabId = ucRabId;

    /*������Ϣ*/
    CDS_SEND_MSG(pstNotifyMsg);

    /*����SR��־*/
    CDS_SET_CDMA_RAB_SR_FLG(pstCdsEntity,ucRabId);

    CDS_INFO_LOG(UEPS_PID_CDS,"Leave CDS_APSServiceRequestNotify: Send Service Ind Msg Succ.");
    CDS_PRINT_INFO(CDS_APSServiceRequestNotify_ENUM,CDS_PRINT_PROC_INFO);
    return;

}

/*****************************************************************************
 �� �� ��  : CDS_APSSendBuffIndMsgProc
 ��������  : ����APS ���ͻ���������Ϣ
 �������  : MsgBlock  *pstMsg
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ  :
    1.��    ��   : 2014��10��25��
      ��    ��   : l00304941
      �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CDS_APSSendBuffIndMsgProc(MsgBlock  *pstMsg)
{
    APS_CDS_CDATA_SEND_BUFF_DATA_IND_STRU         *pstSendBufInd;
    CDS_ENTITY_STRU                               *pstCdsEntity;
    VOS_UINT16                                     enModemId;

    /*����ж�*/
    if (VOS_NULL_PTR == pstMsg)
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"CDS_APSSendBuffIndMsgProc : Input Null Para.");
        CDS_PRINT_ERROR(CDS_APSSendBuffIndMsgProc_ENUM,CDS_PRINT_PARA_INPUT_ERR);
        return;
    }

    CDS_INFO_LOG(UEPS_PID_CDS,"Enter CDS_APSSendBuffIndMsgProc");
    CDS_PRINT_INFO(CDS_APSSendBuffIndMsgProc_ENUM,CDS_PRINT_ENTER_FUC_INFO);

    pstSendBufInd = (APS_CDS_CDATA_SEND_BUFF_DATA_IND_STRU*)((VOS_UINT32)pstMsg);

    /* ����Pid ���ModemId, ����ModemId ���CDSʵ��ָ��*/
    enModemId = VOS_GetModemIDFromPid(pstSendBufInd->ulSenderPid);
    pstCdsEntity = CDS_GetCdsEntity(enModemId);
    if (VOS_NULL_PTR == pstCdsEntity)
    {
        CDS_ERROR_LOG2(UEPS_PID_CDS,"CDS_APSSendBuffIndMsgProc : Get CDS Entity Fail.SenderPid,ModemId",
                       pstSendBufInd->ulSenderPid,
                       enModemId);
        CDS_PRINT_ERROR2(CDS_APSSendBuffIndMsgProc_ENUM,CDS_PRINT_GET_ENTITY_FAIL,pstSendBufInd->ulSenderPid,
                       enModemId);
        return;
    }

    /*RABID�ж�*/
    if ((CDS_NAS_MIN_BEARER_ID > pstSendBufInd->ucRabId) || (CDS_NAS_MAX_BEARER_ID < pstSendBufInd->ucRabId))
    {
        CDS_ERROR_LOG2(UEPS_PID_CDS,"CDS_APSSendBuffIndMsgProc : Rab Id Error.ModemId,RabId",enModemId,pstSendBufInd->ucRabId);
        CDS_PRINT_ERROR2(CDS_APSSendBuffIndMsgProc_ENUM,CDS_PRINT_RAB_ID_ERR,enModemId,pstSendBufInd->ucRabId);
        return;
    }

    /*���ָ��RAB SR��־*/
    CDS_CLR_CDMA_RAB_SR_FLG(pstCdsEntity,pstSendBufInd->ucRabId);

    /*����ָ��RAB ���л���*/
    CDS_CDMASendUlBuffData(pstCdsEntity,pstSendBufInd->ucRabId);

    CDS_INFO_LOG1(UEPS_PID_CDS,"Leave CDS_APSSendBuffIndMsgProc. ModemId:",enModemId);
    CDS_PRINT_INFO1(CDS_APSSendBuffIndMsgProc_ENUM,CDS_PRINT_LEAVE_FUC_INFO,enModemId);

    return;
}

/*****************************************************************************
 �� �� ��  : CDS_APSFreeBuffIndMsgProcs
 ��������  : ����APS��ջ���������Ϣ
 �������  : MsgBlock  *pstMsg
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ  :
    1.��    ��   : 2014��10��25��
      ��    ��   : l00304941
      �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CDS_APSFreeBuffIndMsgProc(const MsgBlock  *pstMsg)
{
    APS_CDS_CDATA_FREE_BUFF_DATA_IND_STRU          *pstFreeBufInd;
    CDS_ENTITY_STRU                                *pstCdsEntity;
    VOS_UINT16                                      enModemId;

    /*����ж�*/
    if (VOS_NULL_PTR == pstMsg)
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"CDS_APSFreeBuffIndMsgProc : Input Null Para.");
        CDS_PRINT_ERROR(CDS_APSFreeBuffIndMsgProc_ENUM,CDS_PRINT_PARA_INPUT_ERR);
        return;
    }

    CDS_INFO_LOG(UEPS_PID_CDS,"Enter CDS_APSFreeBuffIndMsgProc");
    CDS_PRINT_INFO(CDS_APSFreeBuffIndMsgProc_ENUM,CDS_PRINT_ENTER_FUC_INFO);

    pstFreeBufInd = (APS_CDS_CDATA_FREE_BUFF_DATA_IND_STRU *)((VOS_UINT32)pstMsg);

    /* ����Pid ���ModemId, ����ModemId ���CDSʵ��ָ��*/
    enModemId = VOS_GetModemIDFromPid(pstFreeBufInd->ulSenderPid);
    pstCdsEntity = CDS_GetCdsEntity(enModemId);
    if (VOS_NULL_PTR == pstCdsEntity)
    {
        CDS_ERROR_LOG2(UEPS_PID_CDS,"CDS_APSFreeBuffIndMsgProc : Get CDS Entity Fail.SenderPid,ModemId",
                       pstFreeBufInd->ulSenderPid,
                       enModemId);
        CDS_PRINT_ERROR2(CDS_APSFreeBuffIndMsgProc_ENUM,CDS_PRINT_GET_ENTITY_FAIL,pstFreeBufInd->ulSenderPid,
                       enModemId);
        return;
    }

    /*RABID�ж�*/
    if ((CDS_NAS_MIN_BEARER_ID > pstFreeBufInd->ucRabId) || (CDS_NAS_MAX_BEARER_ID < pstFreeBufInd->ucRabId))
    {
        CDS_ERROR_LOG2(UEPS_PID_CDS,"CDS_APSFreeBuffIndMsgProc : Rab Id Error.ModemId,RabId",enModemId,pstFreeBufInd->ucRabId);
        CDS_PRINT_ERROR2(CDS_APSFreeBuffIndMsgProc_ENUM,CDS_PRINT_RAB_ID_ERR,enModemId,pstFreeBufInd->ucRabId);
        return;
    }

    /*���ָ��RAB SR��־*/
    CDS_CLR_CDMA_RAB_SR_FLG(pstCdsEntity,pstFreeBufInd->ucRabId);

    /*���ָ��RAB ���л�������*/
    CDS_UlGUClearBuffData(pstCdsEntity,pstFreeBufInd->ucRabId);

    CDS_INFO_LOG1(UEPS_PID_CDS,"Leave CDS_APSFreeBuffIndMsgProc. ModemId:",enModemId);

    CDS_PRINT_INFO1(CDS_APSFreeBuffIndMsgProc_ENUM,CDS_PRINT_LEAVE_FUC_INFO,enModemId);

    return;
}

/*****************************************************************************
 �� �� ��  : CDS_ChangeRanModeToCDMA
 ��������  : ����ǰ����ģʽ�л���CDMA
 �������  : MsgBlock  *pstMsgS
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ  :
    1.��    ��   : 2014��10��25��
      ��    ��   : l00304941
      �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CDS_ChangeRanModeToCDMA(CDS_ENTITY_STRU *pstCdsEntity,APS_CDS_MODE_ENUM_UINT32 enMode)
{
    APS_CDS_MODE_ENUM_UINT32               PreRanMode;

    /*����ж�*/
    if (VOS_NULL_PTR == pstCdsEntity)
    {
        CDS_INFO_LOG(UEPS_PID_CDS,"CDS_ChangeRanModeToCDMA Input Para Error.");
        CDS_PRINT_ERROR(CDS_ChangeRanModeToCDMA_ENUM,CDS_PRINT_PARA_INPUT_ERR);
        return ;
    }

    CDS_INFO_LOG2(UEPS_PID_CDS,"Enter CDS_ChangeRanModeToCDMA. ModemId,PreRanMode :",pstCdsEntity->usModemId,pstCdsEntity->enRanMode);
    CDS_PRINT_INFO2(CDS_ChangeRanModeToCDMA_ENUM,CDS_PRINT_ENTER_FUC_INFO,pstCdsEntity->usModemId,pstCdsEntity->enRanMode);

    PreRanMode = pstCdsEntity->enRanMode;
    pstCdsEntity->enRanMode = enMode;

    /*���Service Request��־*/
    pstCdsEntity->ulServiceReqFlg = PS_FALSE;

    /*����CDMA RAB SR��־*/
    CDS_CLR_CDMA_ALL_RAB_SR_FLG(pstCdsEntity);

    /*ֹͣNULL����10ms�����Զ�ʱ��*/
    CDS_StopTimer(pstCdsEntity,CDS_TMR_ID_DL_10MS_PERIODIC_TMR);

    /*�������г��ص����л�������*/
    CDS_CDMASendUlBuffData(pstCdsEntity,CDS_NAS_ALL_BEARER_ID);

    CDS_INFO_LOG(UEPS_PID_CDS,"Leave CDS_ChangeRanModeToCDMA Succ.");
    CDS_PRINT_INFO(CDS_ChangeRanModeToCDMA_ENUM,CDS_PRINT_LEAVE_FUC_INFO);

    return;
}

/*****************************************************************************
 �� �� ��  : CDS_APS_ChangeRanModeMsgProc
 ��������  : �����յ��Ľ���ģʽ�����Ϣ
 �������  :
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ  :
    1.��    ��   : 2014�� 11�� 05��
      ��    ��   : l00304941
      �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CDS_APS_ChangeRanModeMsgProc(MsgBlock  *pstMsg)
{
    APS_CDS_MODE_CHANGE_IND_STRU        *pstModeChangeInd;
    CDS_ENTITY_STRU                     *pstCdsEntity;
    VOS_UINT16                           usModemId;

    /*�����Ч���ж�*/
    if (VOS_NULL_PTR == pstMsg)
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"CDS_ChangeRanModeMsgProc : Input NULL Para.");
        CDS_PRINT_ERROR(CDS_APS_ChangeRanModeMsgProc_ENUM,CDS_PRINT_PARA_INPUT_ERR);
        return;
    }

    /*Proc Msg*/
    pstModeChangeInd = (APS_CDS_MODE_CHANGE_IND_STRU *)((VOS_UINT32)pstMsg);

    /*����Pid���ModemId,����ModemId���Cdsʵ��ָ��*/
    usModemId = VOS_GetModemIDFromPid(pstModeChangeInd->ulSenderPid);
    pstCdsEntity = CDS_GetCdsEntity(usModemId);
    if (VOS_NULL_PTR == pstCdsEntity)
    {
        CDS_ERROR_LOG2(UEPS_PID_CDS,
                       "CDS_ChangeRanModeMsgProc : CDS_GetCdsEntity Fail.SenderPid,ModemId",
                       pstModeChangeInd->ulSenderPid,
                       usModemId);
        CDS_PRINT_ERROR2(CDS_APS_ChangeRanModeMsgProc_ENUM,CDS_PRINT_GET_ENTITY_FAIL,pstModeChangeInd->ulSenderPid,
                       usModemId);
        return;
    }

    switch(pstModeChangeInd->enMode)
    {
    case APS_CDS_MODE_NULL:
        CDS_ChangeRanModeToNULL(pstCdsEntity);
        break;

    case APS_CDS_MODE_GU:
        CDS_ChangeRanModeToGU(pstCdsEntity);
        break;

    case APS_CDS_MODE_LTE:
        CDS_ChangeRanModeToLTE(pstCdsEntity);
        break;

    case APS_CDS_MODE_1X:
    case APS_CDS_MODE_EVDO:
        CDS_ChangeRanModeToCDMA(pstCdsEntity,pstModeChangeInd->enMode);
        break;

    default:
        CDS_ERROR_LOG2(UEPS_PID_CDS,"CDS_ChangeRanModeMsgProc:Change Ran Mode Error.ModemId,RanMode:",
                       pstCdsEntity->usModemId,
                       pstModeChangeInd->enMode);
        CDS_PRINT_ERROR2(CDS_APS_ChangeRanModeMsgProc_ENUM,CDS_PRINT_GET_ACCESS_MODE_FAIL, pstCdsEntity->usModemId,
                       pstModeChangeInd->enMode);
        break;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : CDS_APS_MsgProc
 ��������  : �����յ���APS��Ϣ
 �������  : MsgBlock  *pstMsg
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ  :
    1.��    ��   : 2014��10��25��
      ��    ��   : l00304941
      �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CDS_APS_MsgProc(MsgBlock  *pstMsg)
{
    APS_CDS_CDATA_SEND_BUFF_DATA_IND_STRU         *pstSendBufInd;

    /*����ж�*/
    if (VOS_NULL_PTR == pstMsg)
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"CDS_APS_MsgProc : Input Para Error.");
        CDS_PRINT_ERROR(CDS_APS_MsgProc_ENUM,CDS_PRINT_PARA_INPUT_ERR);
        return;
    }

    pstSendBufInd = (APS_CDS_CDATA_SEND_BUFF_DATA_IND_STRU*)((VOS_UINT32)pstMsg);

    switch(pstSendBufInd->enMsgId)
    {
    case ID_APS_CDS_CDATA_SEND_BUFF_DATA_IND:
        CDS_APSSendBuffIndMsgProc(pstMsg);
        break;

    case ID_APS_CDS_CDATA_FREE_BUFF_DATA_IND:
        CDS_APSFreeBuffIndMsgProc(pstMsg);
        break;

    case ID_APS_CDS_MODE_CHANGE_IND:
        CDS_APS_ChangeRanModeMsgProc(pstMsg);
        break;

    default:
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_APS_MsgProc : Recv APS Msg Id Error.",TTF_GET_MSG_NAME(pstMsg));
        CDS_PRINT_ERROR1(CDS_APS_MsgProc_ENUM,CDS_PRINT_GET_MSG_ID_FAIL,TTF_GET_MSG_NAME(pstMsg));
        break;
    }

    return;
}

#endif

/*****************************************************************************
 �� �� ��  : CDS_UMTS_TrigEvenTresMsgProc
 ��������  : ��ȡ��Ϣ�����е�ulDlTrigEventThres
 �������  :
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ  :
    1.��    ��   : 2012��6��14��
      ��    ��   : t148005
      �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CDS_UMTS_TrigEvenTresMsgProc(const MsgBlock  *pstMsg)
{
    (VOS_VOID)pstMsg;
    return;
}

/*****************************************************************************
 �� �� ��  : CDS_UMTS_TrigEvenTresMsgProc
 ��������  : FcACore��Ϣ������
 �������  :
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ  :
    1.��    ��   : 2012��6��14��
      ��    ��   : t148005
      �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CDS_FcACore_MsgProc(const MsgBlock  *pstMsg)
{
    if (VOS_NULL_PTR == pstMsg)
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"CDS_FcA_MsgProc : Input Para Error.");
        CDS_PRINT_ERROR(CDS_FcACore_MsgProc_ENUM,CDS_PRINT_PARA_INPUT_ERR);
        return;
    }

    switch(TTF_GET_MSG_NAME(pstMsg))
    {
    case ID_FC_CDS_DL_THRES_CHG_IND:
        /*lint -e522*/
        CDS_UMTS_TrigEvenTresMsgProc(pstMsg);
        /*lint +e522*/
        break;

    default:
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_FcA_MsgProc : Recv FcACore Msg Id Error.",TTF_GET_MSG_NAME(pstMsg));
        CDS_PRINT_ERROR1(CDS_FcACore_MsgProc_ENUM,CDS_PRINT_GET_MSG_ID_FAIL,TTF_GET_MSG_NAME(pstMsg));
        break;
    }

    return;
}



VOS_VOID CDS_RecvMsgProc(MsgBlock  *pstMsg)
{
    if (VOS_NULL_PTR == pstMsg)
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"CDS_RecvMsgProc : Input Para NULL.");
        CDS_PRINT_ERROR(CDS_RecvMsgProc_ENUM,CDS_PRINT_PARA_INPUT_ERR);
        return;
    }

    switch(TTF_GET_MSG_SENDER_PID(pstMsg))
    {
    case I0_WUEPS_PID_MMC:
    case I1_WUEPS_PID_MMC:
    case I2_WUEPS_PID_MMC:
        CDS_MSG_HOOK(pstMsg);
        CDS_MMC_MsgProc(pstMsg);
        break;

    case UEPS_PID_NDCLIENT:
        CDS_MSG_HOOK(pstMsg);
        CDS_NDCLIENT_MsgProc(pstMsg);
        break;

    case I0_WUEPS_PID_RABM:
    case I1_WUEPS_PID_RABM:
    case I2_WUEPS_PID_RABM:
        CDS_MSG_HOOK(pstMsg);
        CDS_RABM_MsgProc(pstMsg);
        break;

    case DOPRA_PID_TIMER:
        CDS_TmrMsgProc(pstMsg);
        break;

    case ACPU_PID_FC:
        CDS_FcACore_MsgProc(pstMsg);
        break;

    case PS_PID_IMSA:
        CDS_MSG_HOOK(pstMsg);
        CDS_IMSA_MsgProc(pstMsg);
        break;

#if (CDS_FEATURE_ON == CDS_FEATURE_BASTET)
    case UEPS_PID_BASTET:
        CDS_MSG_HOOK(pstMsg);
        CDS_BST_MsgProc(pstMsg);
        break;
#endif

#if (CDS_FEATURE_ON == CDS_FEATURE_LTE)
    case PS_PID_RABM:
        CDS_MSG_HOOK(pstMsg);
        CDS_ERABM_MsgProc(pstMsg);
        break;

    case PS_PID_TC:
        CDS_MSG_HOOK(pstMsg);
        CDS_ETC_MsgProc(pstMsg);
        break;
#endif

#if (CDS_FEATURE_ON == CDS_FEATURE_CDMA)
    case I0_WUEPS_PID_TAF:
    case I1_WUEPS_PID_TAF:
    case I2_WUEPS_PID_TAF:
        CDS_MSG_HOOK(pstMsg);
        CDS_APS_MsgProc(pstMsg);
        break;
#endif

    case UEPS_PID_DHCP:
        CDS_MSG_HOOK(pstMsg);
        CDS_DHCP_MsgProc(pstMsg);
        break;

    default:
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_RecvMsgProc : CDS Msg Proc Error : Unkown Sender.",TTF_GET_MSG_SENDER_PID(pstMsg));
        CDS_PRINT_ERROR1(CDS_RecvMsgProc_ENUM,CDS_PRINT_GET_MSG_SENDER_ERR,TTF_GET_MSG_SENDER_PID(pstMsg));
        break;
    }

    return;
}
/*lint +e653*/
/*lint +e767*/



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



