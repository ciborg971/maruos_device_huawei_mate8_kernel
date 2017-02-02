
/*lint --e{740,958,717}*/

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include  "l4a_fun.h"

#define    THIS_FILE_ID        MSP_FILE_ID_L4A_FUN_C

/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/
VOS_UINT32 g_L4aPrintCtrl = 0;

/*****************************************************************************
  3 Function
*****************************************************************************/

#define L4A_VALID_PID_CHECK(pstReq, pstCnf) do{ \
if((NULL == pstReq) || (NULL == pstCnf) || (pstReq->stCtrl.ulPid != pstCnf->ulOpId))    \
    return ERR_MSP_FAILURE; \
else    \
    return ERR_MSP_SUCCESS; \
}while(0)


VOS_UINT32 l4a_GetValidCidNum(VOS_UINT8 *pData)
{
    VOS_UINT32 i = 0, ulNum = 0;
    
    for(i = 0; i < (APS_L4A_LTE_MAX_CID + 1); i++)
    {
        if(pData[i])
        {
            ulNum++;
        }
    }

    return ulNum;
}

VOS_UINT32 l4a_GetUlValidCidNum(VOS_UINT32 *pData)
{
    VOS_UINT32 i = 0, ulNum = 0;
    
    for(i = 0; i < (APS_L4A_LTE_MAX_CID + 1); i++)
    {
        if(pData[i])
        {
            ulNum++;
        }
    }

    return ulNum;
}


VOS_UINT32 l4a_GetValidCidIndex(VOS_UINT8 *pData, VOS_UINT32 x)
{
    VOS_UINT32 i = 0, ulNum = 0;
    
    for(i = 0; i < (APS_L4A_LTE_MAX_CID + 1); i++)
    {
        if((pData[i]) && (ulNum++ == x))
        {
            break;
        }
    }

    return i;
}

VOS_UINT32 l4a_GetUlValidCidIndex(VOS_UINT32 *pData, VOS_UINT32 x)
{
    VOS_UINT32 i = 0, ulNum = 0;
    
    for(i = 0; i < (APS_L4A_LTE_MAX_CID + 1); i++)
    {
        if((pData[i]) && (ulNum++ == x))
        {
            break;
        }
    }

    return i;
}


VOS_VOID l4a_GetPLMNInfo(L4A_PLMN_ID_STRU * pMspPlmn, APP_PLMN_ID_STRU * pPsPlmn)
{
    if((NULL == pMspPlmn) || (NULL == pPsPlmn))
    {
        return ;
    }

    pMspPlmn->Mcc = ((pPsPlmn->aucPlmnId[0] & 0x0f) << 8)
        | (pPsPlmn->aucPlmnId[0] & 0xf0)
        | (pPsPlmn->aucPlmnId[1] & 0x0f);

    /* ����λȫΪ1ʱ����ʾmncֻ����λ*/
    if(0xf0 == (pPsPlmn->aucPlmnId[1] & 0xf0))
    {
        pMspPlmn->Mnc = ((pPsPlmn->aucPlmnId[2] & 0x0f) << 4)
            | ((pPsPlmn->aucPlmnId[2] & 0xf0) >> 4)
            | 0x0f00;
    }
    else
    {
        pMspPlmn->Mnc = (pPsPlmn->aucPlmnId[2] & 0x0f);
        pMspPlmn->Mnc <<= 8;
        pMspPlmn->Mnc |= (pPsPlmn->aucPlmnId[2] & 0xf0);
        pMspPlmn->Mnc |= ((pPsPlmn->aucPlmnId[1] & 0xf0) >> 4);
    }
    return ;
}

/* RDP�����x��cid�������� */
VOS_UINT32 l4a_FunRDPCidIndexReq(L4A_DATA_MSG_STRU* pData,VOS_UINT32 ulPsReqMsgId,VOS_UINT32 ulPsReqPid, VOS_UINT32 x)
{
    APP_ESM_INQ_PARA_REQ_STRU stReq= {0};
    L4A_ONLY_CID_COMM_REQ_STRU *pstReq = NULL;

    pstReq = (L4A_ONLY_CID_COMM_REQ_STRU*)(pData);

    stReq.ulMsgId = ulPsReqMsgId;
    stReq.ulOpId = pstReq->stCtrl.ulPid;
    stReq.ulCid = l4a_GetValidCidIndex(pstReq->aucCid, x);
    if(stReq.ulCid == (APS_L4A_LTE_MAX_CID + 1))
    {
        return ERR_MSP_FAILURE;
    }
    return  l4aPacket2Ps(ulPsReqPid, &stReq, sizeof(APP_ESM_INQ_PARA_REQ_STRU));
}

VOS_UINT32 l4a_FunPsOnlyCidCommSetReq(L4A_DATA_MSG_STRU* pData,VOS_UINT32 ulPsReqMsgId,VOS_UINT32 ulPsReqPid)
{
    /* ��һ�δ�����ǵ�0��cide */
    return l4a_FunRDPCidIndexReq(pData, ulPsReqMsgId, ulPsReqPid, 0);
}

VOS_UINT32 l4a_FunPsNoCidCommSetCnf(L4A_PS_MSG_STRU* pData,L4A_FW_MSG_FUN_TABLE_STRU* pstTable,VOS_UINT16 usClientId)
{
    L4A_NO_CID_COMM_CNF_STRU stCnf  = {0};
    APP_ESM_PARA_SET_CNF_STRU *pstCnf=NULL;

    if(NULL == pData)
    {
        stCnf.ulErrorCode = ERR_MSP_TIMEOUT;
        return l4aPacket2Aps(&stCnf, sizeof(L4A_NO_CID_COMM_CNF_STRU));
    }

    pstCnf = (APP_ESM_PARA_SET_CNF_STRU *)(pData);

    stCnf.enMsgId = pstTable->ulAtCnfMsgId;
    stCnf.stCtrl.ulPid = pstCnf->ulOpId;
    stCnf.stCtrl.ulClientId = (VOS_UINT32)usClientId;

    stCnf.ulErrorCode = pstCnf->ulSetRslt;
    return l4aPacket2Aps(&stCnf, sizeof(L4A_NO_CID_COMM_CNF_STRU));
}


VOS_UINT32 l4a_PktActivateCnf2Aps(L4A_PS_MSG_STRU* pData,VOS_UINT32 ulAtCnfMsgId,VOS_UINT16 usClientId)
{
    APS_L4A_PDP_ACTIVATE_CNF_STRU stCnf = {0};
    APP_ESM_PDP_SETUP_CNF_STRU* pstCnf  = NULL;

    pstCnf = (APP_ESM_PDP_SETUP_CNF_STRU*)(pData);

    stCnf.enMsgId         = ulAtCnfMsgId;
    stCnf.usClientId      = usClientId;
    stCnf.bitOpEpsQos     = pstCnf->bitOpSdfQos;
    stCnf.bitOpEsmCause   = 1;
    stCnf.bitOpLinkCid    = pstCnf->bitOpLinkCid;
    stCnf.ucCid           = (VOS_UINT8)pstCnf->ulCid;
    stCnf.ulLinkCid       = pstCnf->ulLinkCid;
    stCnf.ulRabId         = pstCnf->ulRabId;
    stCnf.ulEsmCause      = pstCnf->ulRslt;
    stCnf.ulDedicatedBearerFlg = pstCnf->enBearerType;

    (VOS_VOID)VOS_MemCpy(&(stCnf.stIpAddrInfo), &(pstCnf->stPDNAddrInfo), sizeof(APS_L4A_PDP_ADDR_STRU));
    (VOS_VOID)VOS_MemCpy(&(stCnf.stEpsQosInfo), &(pstCnf->stSdfQosInfo), sizeof(APS_L4A_EPS_QOS_STRU));

    if((1 == pstCnf->bitOpDnsPrim) && (APP_ESM_PDN_TYPE_IPV4 == pstCnf->stDnsPrimAddrInfo.ucIpType))
    {
        stCnf.stDnsAddrInfo.bitOpPrimDnsAddr= 1;
        (VOS_VOID)VOS_MemCpy(stCnf.stDnsAddrInfo.aucPrimDnsAddr, pstCnf->stDnsPrimAddrInfo.aucIpV4Addr, APP_MAX_IPV4_ADDR_LEN);
    }

    if((1 == pstCnf->bitOpDnsPrim) && (APP_ESM_PDN_TYPE_IPV6 == pstCnf->stDnsPrimAddrInfo.ucIpType))
    {
        stCnf.stIpv6DnsAddrInfo.bitOpPrimDnsAddr = 1;
        (VOS_VOID)VOS_MemCpy(stCnf.stIpv6DnsAddrInfo.aucPrimDnsAddr, pstCnf->stDnsPrimAddrInfo.aucIpV6Addr, APP_MAX_IPV6_ADDR_LEN);
    }

    if((1 == pstCnf->bitOpDnsSec) && (APP_ESM_PDN_TYPE_IPV4 == pstCnf->stDnsSecAddrInfo.ucIpType))
    {
        stCnf.stDnsAddrInfo.bitOpSecDnsAddr = 1;
        (VOS_VOID)VOS_MemCpy(stCnf.stDnsAddrInfo.aucSecDnsAddr, pstCnf->stDnsSecAddrInfo.aucIpV4Addr, APP_MAX_IPV4_ADDR_LEN);
    }

    if((1 == pstCnf->bitOpDnsSec) && (APP_ESM_PDN_TYPE_IPV6== pstCnf->stDnsSecAddrInfo.ucIpType))
    {
        stCnf.stIpv6DnsAddrInfo.bitOpSecDnsAddr = 1;
        (VOS_VOID)VOS_MemCpy(stCnf.stIpv6DnsAddrInfo.aucSecDnsAddr, pstCnf->stDnsSecAddrInfo.aucIpV6Addr, APP_MAX_IPV6_ADDR_LEN);
    }

    /*stPdpActCnf.tNbnsAddrInfo��ʱ���Բ��ṩ*/

    stCnf.stGateWayAddrInfo.bitOpGateWayAddr= pstCnf->bitOpGateWayAddrInfo;
    (VOS_VOID)VOS_MemCpy(stCnf.stGateWayAddrInfo.aucGateWayAddr, pstCnf->stGateWayAddrInfo.aucIpV4Addr, 4*sizeof(VOS_UINT8));

    stCnf.stPcscfAddrInfo.bitOpPrimPcscfAddr = pstCnf->bitOpPCscfPrim;
    stCnf.stPcscfAddrInfo.bitOpSecPcscfAddr  = pstCnf->bitOpPCscfSec;
    (VOS_VOID)VOS_MemCpy(stCnf.stPcscfAddrInfo.aucPrimPcscfAddr, pstCnf->stPCscfPrimAddrInfo.aucIpV4Addr, 4*sizeof(VOS_UINT8));
    (VOS_VOID)VOS_MemCpy(stCnf.stPcscfAddrInfo.aucSecPcscfAddr, pstCnf->stPCscfSecAddrInfo.aucIpV4Addr, 4*sizeof(VOS_UINT8));

    return l4aPacket2Aps((&stCnf), sizeof(APS_L4A_PDP_ACTIVATE_CNF_STRU));
}

VOS_UINT32 l4a_PktActivateRej2Aps(L4A_PS_MSG_STRU* pData, VOS_UINT32 ulAtCnfMsgId,VOS_UINT16 usClientId)
{
    APS_L4A_PDP_ACTIVATE_REJ_STRU stCnf = {0};
    APP_ESM_PDP_SETUP_CNF_STRU* pstCnf = NULL;

    pstCnf = (APP_ESM_PDP_SETUP_CNF_STRU*)(pData);

    stCnf.enMsgId         = ulAtCnfMsgId;
    stCnf.usClientId      = usClientId;
    stCnf.ucCid           = (VOS_UINT8)pstCnf->ulCid;
    stCnf.ulEsmCause      = pstCnf->ulRslt;

    return l4aPacket2Aps((&stCnf), sizeof(APS_L4A_PDP_ACTIVATE_REJ_STRU));
}

VOS_UINT32 l4a_PktDeactivateCnf2Aps(L4A_PS_MSG_STRU* pData, VOS_UINT32 ulAtCnfMsgId,VOS_UINT16 usClientId)
{
    APS_L4A_PDP_DEACTIVATE_CNF_STRU stCnf = {0};
    APP_ESM_PDP_RELEASE_CNF_STRU* pstCnf = NULL;

    pstCnf = (APP_ESM_PDP_RELEASE_CNF_STRU*)(pData);

    stCnf.enMsgId         = ulAtCnfMsgId;
    stCnf.usClientId      = usClientId;
    stCnf.bitOpLinkCid    = pstCnf->bitOpLinkCid;
    stCnf.ucCid           = (VOS_UINT8)pstCnf->ulCid;
    stCnf.ulLinkCid       = pstCnf->ulLinkCid;
    stCnf.stIpAddrInfo.enPdpType = pstCnf->stPDNAddrInfo.ucIpType;
    (VOS_VOID)VOS_MemCpy(stCnf.stIpAddrInfo.aucIpv4Addr, pstCnf->stPDNAddrInfo.aucIpV4Addr, APP_MAX_IPV4_ADDR_LEN*sizeof(VOS_UINT8));
    (VOS_VOID)VOS_MemCpy(stCnf.stIpAddrInfo.aucIpv6Addr, pstCnf->stPDNAddrInfo.aucIpV6Addr, APP_MAX_IPV6_ADDR_LEN*sizeof(VOS_UINT8));

    return l4aPacket2Aps((&stCnf), sizeof(APS_L4A_PDP_DEACTIVATE_CNF_STRU));
}

VOS_UINT32 l4a_PktDeactivateRej2Aps(L4A_PS_MSG_STRU* pData, VOS_UINT32 ulAtCnfMsgId,VOS_UINT16 usClientId)
{
    APS_L4A_PDP_DEACTIVATE_REJ_STRU stCnf = {0};
    APP_ESM_PDP_RELEASE_CNF_STRU* pstCnf = NULL;

    pstCnf = (APP_ESM_PDP_RELEASE_CNF_STRU*)(pData);

    stCnf.enMsgId         = ulAtCnfMsgId;
    stCnf.usClientId      = usClientId;
    stCnf.bitOpLinkCid    = pstCnf->bitOpLinkCid;
    stCnf.ucCid           = (VOS_UINT8)pstCnf->ulCid;
    stCnf.ulLinkCid       = pstCnf->ulLinkCid;
    stCnf.ulEsmCause      = pstCnf->ulRslt;

    return l4aPacket2Aps((&stCnf), sizeof(APS_L4A_PDP_DEACTIVATE_REJ_STRU));
}



/* ^LWCLASH REQ */
VOS_UINT32 l4a_FunPsLwclashReadReq(L4A_DATA_MSG_STRU* pData,VOS_UINT32 ulPsReqMsgId,VOS_UINT32 ulPsReqPid)
{
    APP_RRC_LWCLASH_REQ_STRU stReq= {0};

    stReq.ulMsgId = ulPsReqMsgId;

    return l4aPacket2Ps(ulPsReqPid, &stReq, sizeof(APP_RRC_LWCLASH_REQ_STRU));
}


/* ^LWCLASH CNF */
VOS_UINT32 l4a_FunPsLwclashReadCnf(L4A_PS_MSG_STRU* pData,L4A_FW_MSG_FUN_TABLE_STRU* pstTable,VOS_UINT16 usClientId)
{
    L4A_READ_LWCLASH_CNF_STRU stCnf  = {0};
    RRC_APP_LWCLASH_CNF_STRU *pstCnf = NULL;

    stCnf.enMsgId = pstTable->ulAtCnfMsgId;
    stCnf.usClientId = usClientId;

    if(NULL == pData)
    {
        stCnf.ulErrorCode = ERR_MSP_TIMEOUT;
        return l4aPacket2At(&stCnf, sizeof(L4A_READ_LWCLASH_CNF_STRU));
    }

    pstCnf = (RRC_APP_LWCLASH_CNF_STRU *)(pData);
    stCnf.ulErrorCode = ERR_MSP_SUCCESS;
    (VOS_VOID)VOS_MemCpy(&stCnf.stLwclashInfo, &pstCnf->stLWClashPara, sizeof(RRC_APP_LWCLASH_PARA_STRU));

    return l4aPacket2At(&stCnf, sizeof(L4A_READ_LWCLASH_CNF_STRU));
}


VOS_UINT32 l4a_FunPsLcacellReadReq(L4A_DATA_MSG_STRU* pData,VOS_UINT32 ulPsReqMsgId,VOS_UINT32 ulPsReqPid)
{
    APP_L2_CA_CELL_INFO_REQ_STRU stReq= {0};
    
    stReq.ulMsgId = ulPsReqMsgId;
    
    return l4aPacket2Ps(ulPsReqPid, &stReq, sizeof(APP_L2_CA_CELL_INFO_REQ_STRU));
}

VOS_UINT32 l4a_FunPsLcacellReadCnf(L4A_PS_MSG_STRU* pData,L4A_FW_MSG_FUN_TABLE_STRU* pstTable,VOS_UINT16 usClientId)
{
    L4A_READ_LCACELL_CNF_STRU stCnf  = {0};
    L2_APP_CA_CELL_INFO_CNF_STRU *pstCnf = NULL;
    
    stCnf.enMsgId = pstTable->ulAtCnfMsgId;
    stCnf.usClientId = usClientId;
    
    if(NULL == pData)
    {
        stCnf.ulErrorCode = ERR_MSP_TIMEOUT;
        return l4aPacket2At(&stCnf, sizeof(L4A_READ_LCACELL_CNF_STRU));
    }

    pstCnf = (L2_APP_CA_CELL_INFO_CNF_STRU *)(pData);
    stCnf.ulErrorCode = ERR_MSP_SUCCESS;
    (VOS_VOID)VOS_MemCpy(stCnf.stLcacellInfo, pstCnf->astCellStatus, sizeof(L4A_CACELL_INFO_STRU)*CA_MAX_CELL_NUM);

    return l4aPacket2At(&stCnf, sizeof(L4A_READ_LCACELL_CNF_STRU));
}



/* ^LWURC */
VOS_UINT32 l4a_FunLwclashInd(L4A_PS_MSG_STRU* pData)
{
    RRC_APP_LWCLASH_IND_STRU *pstLwclashInd=NULL;
    L4A_READ_LWCLASH_IND_STRU stLwclash={0};

    if(L4A_GetRptCmdStatus(L4A_RPT_CMD_LWURC))
    {
        pstLwclashInd = (RRC_APP_LWCLASH_IND_STRU *)(pData);

        L4A_INFO_LOG("state %d, ulfreq %d, ulbw %d, dlfreq %d, dlbw %d, band %d\n",
            pstLwclashInd->stLWClashPara.enState, pstLwclashInd->stLWClashPara.usUlFreq,
            pstLwclashInd->stLWClashPara.usUlBandwidth, pstLwclashInd->stLWClashPara.usDlFreq,
            pstLwclashInd->stLWClashPara.usDlBandwidth, pstLwclashInd->stLWClashPara.usBand);

        (VOS_VOID)VOS_MemCpy(&stLwclash.stLwclashInfo, &pstLwclashInd->stLWClashPara, sizeof(RRC_APP_LWCLASH_PARA_STRU));

        stLwclash.enMsgId = ID_MSG_L4A_LWCLASH_IND;

        return l4aPacket2At(&stLwclash, sizeof(L4A_READ_LWCLASH_IND_STRU));
    }

    return ERR_MSP_SUCCESS;
}

VOS_UINT32 l4a_FunLcacellInd(L4A_PS_MSG_STRU* pData)
{
    L2_APP_CA_CELL_INFO_IND_STRU    *pstLcacellInd=NULL;
    L4A_READ_LCACELL_IND_STRU       stLcacell={0};

    if(L4A_GetRptCmdStatus(L4A_RPT_CMD_LCACELLURC))
    {
        pstLcacellInd = (L2_APP_CA_CELL_INFO_IND_STRU *)(pData);

        (VOS_VOID)VOS_MemCpy(stLcacell.stLcacellInfo, pstLcacellInd->astCellStatus, sizeof(L4A_CACELL_INFO_STRU)*CA_MAX_CELL_NUM);

        stLcacell.enMsgId = ID_MSG_L4A_LCACELL_IND;

        return l4aPacket2At(&stLcacell, sizeof(L4A_READ_LCACELL_IND_STRU));
    }

    return ERR_MSP_SUCCESS;
}


VOS_UINT32 l4a_IsmcoexTimeout(VOS_UINT16 usClientId)
{
    L4A_ISMCOEX_CNF_STRU stCnf = { 0 };

    L4A_INFO_LOG("%s, %d.\n",__FUNCTION__, __LINE__);

    stCnf.enMsgId = ID_MSG_L4A_ISMCOEXSET_CNF;
    stCnf.usClientId = usClientId;
    stCnf.ulErrorCode = ERR_MSP_TIMEOUT;
    return l4aPacket2At(&stCnf, sizeof(stCnf));
}

/* ^ISMCOEX REQ */
VOS_UINT32 l4a_FunLteWifiReq(L4A_DATA_MSG_STRU* pData,VOS_UINT32 ulPsReqMsgId,VOS_UINT32 ulPsReqPid)
{
    L4A_ISMCOEX_REQ_STRU* pstReq = (L4A_ISMCOEX_REQ_STRU*)pData;
    LMSP_LPHY_LTE_WIFI_COEX_SET_REQ_STRU *pstReqToDsp = NULL;
    VOS_UINT32  ulSize, i, ulRet;
    LMSP_LPHY_COEX_PARA_STRU *pstcoex;
    
    ulSize = (sizeof(LMSP_LPHY_LTE_WIFI_COEX_SET_REQ_STRU) - 4 
        + (sizeof(LMSP_LPHY_COEX_PARA_STRU)*L4A_ISMCOEX_BANDWIDTH_NUM));

    pstReqToDsp = VOS_MemAlloc(MSP_L4_L4A_PID, DYNAMIC_MEM_PT, ulSize);
    if(NULL == pstReqToDsp)
    {
        return l4a_IsmcoexTimeout((VOS_UINT16)pstReq->stCtrl.ulClientId);
    }
    
    /* ����ԭ�ﵽDSP */
    pstReqToDsp->enMsgId            = ID_LMSP_LPHY_LTE_WIFI_COEX_SET_REQ;
    pstReqToDsp->usCoexParaNum      = L4A_ISMCOEX_BANDWIDTH_NUM;
    pstReqToDsp->usCoexParaSize     = (sizeof(LMSP_LPHY_COEX_PARA_STRU)*L4A_ISMCOEX_BANDWIDTH_NUM);

    pstcoex = (LMSP_LPHY_COEX_PARA_STRU *)&(pstReqToDsp->aucCoexPara[0]);

    for(i = 0; i < L4A_ISMCOEX_BANDWIDTH_NUM; i++)
    {
        pstcoex->enCoexBWType       = (VOS_UINT16)i;
        pstcoex->enCoexEnableInd    = (VOS_UINT16)pstReq->astCoex[i].ulFlag;
        pstcoex->usTx_begin         = (VOS_UINT16)pstReq->astCoex[i].ulTXBegin;
        pstcoex->usTx_End           = (VOS_UINT16)pstReq->astCoex[i].ulTXEnd;
        pstcoex->sTxPower           = (VOS_INT16)pstReq->astCoex[i].lTXPower;
        pstcoex->usRx_begin         = (VOS_UINT16)pstReq->astCoex[i].ulRXBegin;
        pstcoex->usRx_End           = (VOS_UINT16)pstReq->astCoex[i].ulRXEnd;
        
        pstcoex++;
    }

    ulRet = BSP_MailBox_ComMsgWrite(EN_MAILBOX_SERVICE_LTE_COEX, pstReqToDsp, ulSize, EN_MAILBOX_SLEEP_WAKEUP);
    if(ulRet != VOS_OK)
    {
        L4A_ERROR_LOG("[%s] : l4a send to dsp fail, ulRet %d!!!.\n", __FUNCTION__, ulRet);
        (VOS_VOID)l4a_IsmcoexTimeout((VOS_UINT16)pstReq->stCtrl.ulClientId);
        
        (VOS_VOID)VOS_MemFree(MSP_L4_L4A_PID, pstReqToDsp);

        return ERR_MSP_SUCCESS;
    }
    
    (VOS_VOID)VOS_MemFree(MSP_L4_L4A_PID, pstReqToDsp);

    return ERR_MSP_WAIT_ASYNC;
}


/* ^ISMCOEX CNF */
VOS_UINT32 l4a_FunLteWifiCnf(L4A_PS_MSG_STRU* pData,L4A_FW_MSG_FUN_TABLE_STRU* pstTable,VOS_UINT16 usClientId)
{
    L4A_ISMCOEX_CNF_STRU* pDspCnf = (L4A_ISMCOEX_CNF_STRU*)pData;
    L4A_ISMCOEX_CNF_STRU stCnf = { 0 };

    stCnf.enMsgId = pstTable->ulAtCnfMsgId;
    stCnf.usClientId = usClientId;

    if(NULL == pData)
    {
        L4A_INFO_LOG("%s, %d.\n",__FUNCTION__, __LINE__);

        /* L4A��������AT����ʱ */
        return ERR_MSP_SUCCESS;
    }

    stCnf.ulErrorCode = pDspCnf->ulErrorCode;

    return l4aPacket2At(&stCnf, sizeof(stCnf));
}

/* ^RADVER REQ */
VOS_UINT32 l4a_FunRadverReq(L4A_DATA_MSG_STRU* pData,VOS_UINT32 ulPsReqMsgId,VOS_UINT32 ulPsReqPid)
{
    L4A_SET_RADVER_REQ_STRU* pstReq = (L4A_SET_RADVER_REQ_STRU*)pData;
    APP_LRRC_SET_UE_REL_VERSION_REQ_STRU stReqtoRrc = {0};
    
    stReqtoRrc.ulMsgId= ulPsReqMsgId;
    stReqtoRrc.ulMode     = pstReq->ulMod;
    stReqtoRrc.ulVersion  = pstReq->ulVer;

    return l4aPacket2Ps(ulPsReqPid, &stReqtoRrc, sizeof(APP_LRRC_SET_UE_REL_VERSION_REQ_STRU));
}


/* ^RADVER CNF */
VOS_UINT32 l4a_FunRadverCnf(L4A_PS_MSG_STRU* pData,L4A_FW_MSG_FUN_TABLE_STRU* pstTable,VOS_UINT16 usClientId)
{
    LRRC_APP_SET_UE_REL_VERSION_CNF_STRU* pRrcCnf = (LRRC_APP_SET_UE_REL_VERSION_CNF_STRU*)pData;
    L4A_SET_RADVER_CNF_STRU stCnf = { 0 };

    stCnf.enMsgId = pstTable->ulAtCnfMsgId;
    stCnf.usClientId = usClientId;

    if(NULL == pData)
    {
        L4A_INFO_LOG("%s, %d.\n",__FUNCTION__, __LINE__);

        /* L4A��������AT����ʱ */
        return ERR_MSP_SUCCESS;
    }

    stCnf.ulErrorCode = pRrcCnf->enResult;

    return l4aPacket2At(&stCnf, sizeof(stCnf));
}


/* ^CNMR REQ */
VOS_UINT32 l4a_FunPsCnmrReadReq(L4A_DATA_MSG_STRU* pData,VOS_UINT32 ulPsReqMsgId,VOS_UINT32 ulPsReqPid)
{
    APP_RRC_NMR_REQ_STRU stReq = {0};

    stReq.ulMsgId = ulPsReqMsgId;

    return  l4aPacket2Ps(ulPsReqPid,&stReq, sizeof(APP_RRC_NMR_REQ_STRU));
}


/* ^CNMR CNF */
VOS_UINT32 l4a_FunPsCnmrReadCnf(L4A_PS_MSG_STRU* pData,L4A_FW_MSG_FUN_TABLE_STRU* pstTable,VOS_UINT16 usClientId)
{
    L4A_READ_CNMR_CNF_STRU stCnf = {0};
    RRC_APP_NMR_CNF_STRU *pstCnf = NULL;

    stCnf.enMsgId = pstTable->ulAtCnfMsgId;
    stCnf.usClientId = usClientId;

    if(NULL == pData)
    {
        stCnf.ulErrorCode = ERR_MSP_TIMEOUT;
        return l4aPacket2Aps(&stCnf, sizeof(L4A_READ_CNMR_CNF_STRU));
    }

    pstCnf = (RRC_APP_NMR_CNF_STRU *)(pData);
    stCnf.ulErrorCode = pstCnf->enResult;
    (VOS_VOID)VOS_MemCpy(&(stCnf.stLteCelInfo),&(pstCnf->stLteCelInfo),sizeof(RRC_APP_LTE_CELL_INFO_STRU));

    return l4aPacket2At(&stCnf, sizeof(L4A_READ_CNMR_CNF_STRU));
}


/* ^CERSSI/+CSQ/^ANQUERY REQ */
VOS_UINT32 l4a_FunPsCsqReadReq(L4A_DATA_MSG_STRU* pData,VOS_UINT32 ulPsReqMsgId,VOS_UINT32 ulPsReqPid)
{
    APP_RRC_CSQ_REQ_STRU stReq= {0};
    L4A_CSQ_INFO_REQ_STRU *pstReq=NULL;

    pstReq = (L4A_CSQ_INFO_REQ_STRU *)(pData);

    if( ID_MSG_L4A_CERSSI_REQ == pData->enMsgId)
    {
        stReq.usSwt = EN_L4A_RSSI_IND;
    }
    else if (( ID_MSG_L4A_CSQ_INFO_REQ == pData->enMsgId)||(ID_MSG_L4A_ANQUERY_INFO_REQ == pData->enMsgId)\
        ||( ID_MSG_L4A_CERSSI_INQ_REQ == pData->enMsgId))
    {
        stReq.usSwt = EN_L4A_RSSI_INQ_NOT_IND;
    }

    stReq.ulMsgId = ulPsReqMsgId;
    stReq.usNdb = pstReq->ucnDb;
    stReq.usMs  = pstReq->ucMinRptTimerInterval;

    return  l4aPacket2Ps(ulPsReqPid, &stReq, sizeof(APP_RRC_CSQ_REQ_STRU));
}


/* ^CERSSI/+CSQ/^ANQUERY CNF */
VOS_UINT32 l4a_FunPsCsqReadCnf(L4A_PS_MSG_STRU* pData, L4A_FW_MSG_FUN_TABLE_STRU* pstTable, VOS_UINT16 usClientId)
{
    L4A_CSQ_INFO_CNF_STRU stCnf = {0};
    RRC_APP_CSQ_CNF_STRU *pstCnf= NULL;

    stCnf.enMsgId = pstTable->ulAtCnfMsgId;
    stCnf.usClientId = usClientId;

    if(ID_MSG_L4A_CERSSI_CNF == pstTable->ulAtCnfMsgId)
    {
        return 0;
    }
    
    if(NULL == pData)
    {
        stCnf.ulErrorCode = ERR_MSP_TIMEOUT;
        return l4aPacket2Aps(&stCnf, sizeof(L4A_CSQ_INFO_CNF_STRU));
    }

    pstCnf = (RRC_APP_CSQ_CNF_STRU *)(pData);

    stCnf.ulErrorCode = ERR_MSP_SUCCESS;

    /*Э��ջ�����ֵ��8������*/
    stCnf.sRssi = ((99 == pstCnf->sRssi)?99:pstCnf->sRssi/8);
    stCnf.sRsrp = ((99 == pstCnf->sRsrp)?99:pstCnf->sRsrp/8);
    stCnf.sRsrq = ((99 == pstCnf->sRsrq)?99:pstCnf->sRsrq/8);

    stCnf.lSINR             = pstCnf->lSINR;
    stCnf.stCQI.usRI        = pstCnf->stCQI.usRI;
    stCnf.stCQI.ausCQI[0]   = pstCnf->stCQI.ausCQI[0];
    stCnf.stCQI.ausCQI[1]   = pstCnf->stCQI.ausCQI[1];

    return l4aPacket2At(&stCnf, sizeof(L4A_CSQ_INFO_CNF_STRU));
}


/* ^LCELLINFO=n REQ */
VOS_UINT32 l4a_FunPsCellInfoReadReq(L4A_DATA_MSG_STRU* pData,VOS_UINT32 ulPsReqMsgId,VOS_UINT32 ulPsReqPid)
{
    APP_LRRC_GET_NCELL_INFO_REQ_STRU stReq= {0};
    L4A_READ_CELL_INFO_REQ_STRU *pstReq=NULL;

    pstReq = (L4A_READ_CELL_INFO_REQ_STRU *)(pData);

    stReq.ulMsgId    = ulPsReqMsgId;
    stReq.enCellFlag = pstReq->ulCellFlag;
    return  l4aPacket2Ps(ulPsReqPid, &stReq, sizeof(APP_LRRC_GET_NCELL_INFO_REQ_STRU));
}


/* ^LCELLINFO=n CNF */
VOS_UINT32 l4a_FunPsCellInfoReadCnf(L4A_PS_MSG_STRU* pData,L4A_FW_MSG_FUN_TABLE_STRU* pstTable,VOS_UINT16 usClientId)
{
    L4A_READ_CELL_INFO_CNF_STRU stCnf   = {0};
    LRRC_APP_GET_NCELL_INFO_CNF_STRU *pstCnf=NULL;

    stCnf.enMsgId = pstTable->ulAtCnfMsgId;
    stCnf.usClientId = usClientId;

    if(NULL == pData)
    {
        stCnf.ulErrorCode = ERR_MSP_TIMEOUT;
        return l4aPacket2At(&stCnf, sizeof(L4A_READ_CELL_INFO_CNF_STRU));
    }

    pstCnf = (LRRC_APP_GET_NCELL_INFO_CNF_STRU *)(pData);
    stCnf.ulErrorCode = pstCnf->enResult;
    (VOS_VOID)VOS_MemCpy(&(stCnf.stNcellListInfo), &pstCnf->stNcellListInfo, sizeof(LRRC_APP_NCELL_LIST_INFO_STRU));

    return l4aPacket2At(&stCnf, sizeof(L4A_READ_CELL_INFO_CNF_STRU));
}


/* ^CELLID? REQ */
VOS_UINT32 l4a_FunPsCellIDReadReq(L4A_DATA_MSG_STRU* pData,VOS_UINT32 ulPsReqMsgId,VOS_UINT32 ulPsReqPid)
{
    APP_RRC_CELLID_REQ_STRU stReq= {0};

    stReq.ulMsgId = ulPsReqMsgId;

    return  l4aPacket2Ps(ulPsReqPid,&stReq, sizeof(APP_RRC_CELLID_REQ_STRU));
}


/* ^CELLID? CNF */
VOS_UINT32 l4a_FunPsCellIDReadCnf(L4A_PS_MSG_STRU* pData,L4A_FW_MSG_FUN_TABLE_STRU* pstTable,VOS_UINT16 usClientId)
{
    L4A_READ_CELL_ID_CNF_STRU stCnf = {0};
    RRC_APP_CELLID_CNF_STRU *pstCnf=NULL;
    L4A_PLMN_ID_STRU stPlmn ={0};

    stCnf.enMsgId = pstTable->ulAtCnfMsgId;
    stCnf.usClientId = usClientId;

    if(NULL == pData)
    {
        stCnf.ulErrorCode = ERR_MSP_TIMEOUT;
        return l4aPacket2At(&stCnf, sizeof(L4A_READ_CELL_ID_CNF_STRU));
    }

    pstCnf = (RRC_APP_CELLID_CNF_STRU *)(pData);
    stCnf.ulErrorCode = pstCnf->enResult;

    l4a_GetPLMNInfo(&stPlmn,&pstCnf->stPlmnId);
    stCnf.usMncNum = (0x0f ==((stPlmn.Mnc)>>8))? 2: 3;
    stCnf.usMCC = stPlmn.Mcc;
    stCnf.usMNC = stPlmn.Mnc;
    stCnf.ulCi = pstCnf->ulCi;
    stCnf.usPci = pstCnf->usPci;
    stCnf.usTAC= pstCnf->usTAC;

    return l4aPacket2At(&stCnf, sizeof(L4A_READ_CELL_ID_CNF_STRU));
}


VOS_UINT32 l4a_FunPsFastDormReadReq(L4A_DATA_MSG_STRU* pData,VOS_UINT32 ulPsReqMsgId,VOS_UINT32 ulPsReqPid)
{
    APP_LRRC_FAST_DORM_CFG_NTF_STRU stReq = {0};
    L4A_SET_FAST_DORM_REQ_STRU*     pstReq = NULL;

    pstReq = (L4A_SET_FAST_DORM_REQ_STRU*)(pData);

    stReq.ulMsgId = ulPsReqMsgId;
    stReq.ulFlag        = (VOS_UINT32)pstReq->ulFlag;
    stReq.ulTimerLen    = (VOS_UINT32)pstReq->ulTimerLen;
    return l4aPacket2PsNoCnf(ulPsReqPid,&stReq, sizeof(APP_LRRC_FAST_DORM_CFG_NTF_STRU));
}

VOS_UINT32 l4a_FunPsThresholdReadReq(L4A_DATA_MSG_STRU* pData,VOS_UINT32 ulPsReqMsgId,VOS_UINT32 ulPsReqPid)
{
    L4A_LW_THREASHOLD_CFG_REQ_STRU*    pstReq = NULL;
    APP_LRRC_RESEL_OFFSET_CFG_NTF_STRU stReq = {0};

    pstReq = (L4A_LW_THREASHOLD_CFG_REQ_STRU*)(pData);

    stReq.ulMsgId = ulPsReqMsgId;
    stReq.ulFlag  = pstReq->ulFlag;
    return l4aPacket2PsNoCnf(ulPsReqPid,&stReq, sizeof(APP_LRRC_RESEL_OFFSET_CFG_NTF_STRU));
}

VOS_UINT32 l4a_FunPsL2IdleSetReq(L4A_DATA_MSG_STRU* pData,VOS_UINT32 ulPsReqMsgId,VOS_UINT32 ulPsReqPid)
{
    APP_LRRC_CON_TO_IDLE_NTF_STRU stReq = {0};

    stReq.ulMsgId = ulPsReqMsgId;

    return l4aPacket2PsNoCnf(ulPsReqPid,&stReq, sizeof(APP_LRRC_CON_TO_IDLE_NTF_STRU));
}


/* ^LTECS REQ */
VOS_UINT32 l4a_FunPsLtecsReadReq(L4A_DATA_MSG_STRU* pData,VOS_UINT32 ulPsReqMsgId,VOS_UINT32 ulPsReqPid)
{
    APP_MM_INQ_LTE_CS_REQ_STRU stReq= {0};
    APS_L4A_GET_LTE_CS_REQ_STRU *pstReq = NULL;

    pstReq = (APS_L4A_GET_LTE_CS_REQ_STRU*)(pData);

    stReq.ulMsgId = ulPsReqMsgId;
    stReq.ulOpId  = pstReq->stCtrl.ulPid;

    return  l4aPacket2Ps(ulPsReqPid,&stReq, sizeof(APP_MM_INQ_LTE_CS_REQ_STRU));
}


/* ^LTECS CNF */
VOS_UINT32 l4a_FunPsLtecsReadCnf(L4A_PS_MSG_STRU* pData,L4A_FW_MSG_FUN_TABLE_STRU* pstTable,VOS_UINT16 usClientId)
{
    APS_L4A_GET_LTE_CS_CNF_STRU stCnf = {0};
    APP_MM_INQ_LTE_CS_CNF_STRU *pstCnf=NULL;

    if(NULL == pData)
    {
        stCnf.ulErrorCode = ERR_MSP_TIMEOUT;
        return l4aPacket2Aps(&stCnf, sizeof(APS_L4A_GET_LTE_CS_CNF_STRU));
    }

    pstCnf = (APP_MM_INQ_LTE_CS_CNF_STRU *)(pData);

    stCnf.enMsgId = pstTable->ulAtCnfMsgId;
    stCnf.stCtrl.ulPid = pstCnf->ulOpId;
    stCnf.stCtrl.ulClientId = (VOS_UINT32)usClientId;

    stCnf.ulErrorCode = pstCnf->ulRslt;
    if(ERR_MSP_SUCCESS == stCnf.ulErrorCode)
    {
        stCnf.ucSmsOverSGs = pstCnf->stLtecsInfo.ucSmsOverSGs;
        stCnf.ucSmsOverIMS = pstCnf->stLtecsInfo.ucSmsOverIMS;
        stCnf.ucCSFB = pstCnf->stLtecsInfo.ucCSFB;
        stCnf.ucSrVcc = pstCnf->stLtecsInfo.ucSrVcc;
        stCnf.ucVoLGA = pstCnf->stLtecsInfo.ucVoLGA;
    }

    return l4aPacket2Aps(&stCnf, sizeof(APS_L4A_GET_LTE_CS_CNF_STRU));
}


VOS_UINT32 l4a_FunLtecsChk(L4A_PS_MSG_STRU* pData, L4A_RX_INFO_STRU* pNode)
{
    APS_L4A_GET_LTE_CS_REQ_STRU *pstReq = (APS_L4A_GET_LTE_CS_REQ_STRU*)(pNode->pData);
    APP_MM_INQ_LTE_CS_CNF_STRU *pstCnf = (APP_MM_INQ_LTE_CS_CNF_STRU *)(pData);

    L4A_VALID_PID_CHECK(pstReq, pstCnf);
}


/* +CEMODE REQ */
VOS_UINT32 l4a_FunPsCemodeReadReq(L4A_DATA_MSG_STRU* pData,VOS_UINT32 ulPsReqMsgId,VOS_UINT32 ulPsReqPid)
{
    APP_MM_INQ_UE_MODE_REQ_STRU stReq= {0};
    APS_L4A_GET_CEMODE_REQ_STRU *pstReq;

    pstReq = (APS_L4A_GET_CEMODE_REQ_STRU *)pData;

    stReq.ulMsgId = ulPsReqMsgId;
    stReq.ulOpId  = pstReq->stCtrl.ulPid;

    return  l4aPacket2Ps(ulPsReqPid,&stReq, sizeof(APP_MM_INQ_UE_MODE_REQ_STRU));
}

/* +CEMODE CNF */
VOS_UINT32 l4a_FunPsCemodeReadCnf(L4A_PS_MSG_STRU* pData,L4A_FW_MSG_FUN_TABLE_STRU* pstTable,VOS_UINT16 usClientId)
{
    APS_L4A_GET_CEMODE_CNF_STRU stCnf   = {0};
    APP_MM_INQ_UE_MODE_CNF_STRU *pstCnf=NULL;
    VOS_UINT32 i=0;
    VOS_UINT32 aulMode[NAS_LMM_UE_MODE_BUTT-1] = {3, 0, 1, 2};

    if(NULL == pData)
    {
        stCnf.ulErrorCode = ERR_MSP_TIMEOUT;
        return l4aPacket2Aps(&stCnf, sizeof(APS_L4A_GET_CEMODE_CNF_STRU));
    }

    pstCnf = (APP_MM_INQ_UE_MODE_CNF_STRU *)(pData);

    stCnf.enMsgId = pstTable->ulAtCnfMsgId;
    stCnf.stCtrl.ulPid = pstCnf->ulOpId;
    stCnf.stCtrl.ulClientId = (VOS_UINT32)usClientId;

    stCnf.ulErrorCode = pstCnf->ulRslt;
    if(0 != pstCnf->enCurrentUeMode)
    {
        stCnf.ulCurrentUeMode = aulMode[pstCnf->enCurrentUeMode - 1];   /* ��PS�Ľ��ת��ATЭ��Ķ��� */
    }
    stCnf.ulSupportModeCnt = pstCnf->ulSupportModeCnt;
    for(i=0;i<4;i++)
    {
        stCnf.aulSupportModeList[i] = pstCnf->aenSupportModeList[i];
    }
    return l4aPacket2Aps(&stCnf, sizeof(APS_L4A_GET_CEMODE_CNF_STRU));
}


VOS_UINT32 l4a_FunCemodChk(L4A_PS_MSG_STRU* pData, L4A_RX_INFO_STRU* pNode)
{
    APS_L4A_GET_CEMODE_REQ_STRU *pstReq = (APS_L4A_GET_CEMODE_REQ_STRU*)(pNode->pData);
    APP_MM_INQ_UE_MODE_CNF_STRU *pstCnf = (APP_MM_INQ_UE_MODE_CNF_STRU *)(pData);

    L4A_VALID_PID_CHECK(pstReq, pstCnf);
}


/* +CGANS */
VOS_UINT32 l4a_FunPsCgansSetReq(L4A_DATA_MSG_STRU* pData,VOS_UINT32 ulPsReqMsgId,VOS_UINT32 ulPsReqPid)
{
    APP_ESM_PDP_MANAGER_RSP_STRU stReq= {0};
    APS_L4A_SET_CGANS_REQ_STRU *pstReq = NULL;

    pstReq = (APS_L4A_SET_CGANS_REQ_STRU *)(pData);

    stReq.ulMsgId = ulPsReqMsgId;
    stReq.ulCid = pstReq->ucCid;

    /* ATЭ����PSЭ���෴*/
    stReq.ulSetupRslt = (0 == pstReq->ulResponse) ? 1:0;
    return  l4aPacket2PsNoCnf(ulPsReqPid,&stReq, sizeof(APP_ESM_PDP_MANAGER_RSP_STRU));
}


/* ^NDISDUP/^NDISCONN REQ */
VOS_UINT32 l4a_FunPsNdisconnSetReq(L4A_DATA_MSG_STRU* pData,VOS_UINT32 ulPsReqMsgId,VOS_UINT32 ulPsReqPid)
{
    APP_ESM_NDISCONN_REQ_STRU stReq= {0};
    APS_L4A_SET_NDISCONN_REQ_STRU   *pstReq=NULL;

    pstReq = (APS_L4A_SET_NDISCONN_REQ_STRU *)(pData);

    stReq.ulMsgId               = ulPsReqMsgId;

    stReq.ulCid                 = pstReq->stDialPara.ulCid;

    stReq.bitOpPdnType          = 1;
    stReq.bitOpApn              = 1;  /* ȱʡ�����޹�����CID*/
    stReq.bitOpGwAuth           = 1;

    stReq.bitOpIpv4AddrAlloc    = pstReq->stDialPara.bitOpIpv4AddrAlloc;
    stReq.bitOpPcscfDiscovery   = pstReq->stDialPara.bitOpPcscfDiscovery;
    stReq.bitOpImCnSignalFlg    = pstReq->stDialPara.bitOpImCnSignalFlg;

    stReq.enIpv4AddrAlloc       = pstReq->stDialPara.enIpv4AddrAlloc;
    stReq.enEmergencyInd        = pstReq->stDialPara.enEmergencyInd;
    stReq.enPcscfDiscovery      = pstReq->stDialPara.enPcscfDiscovery;
    stReq.enImCnSignalFlg       = pstReq->stDialPara.enImCnSignalFlg;

    stReq.enPdnType             = pstReq->stDialPara.enPdpType;

    stReq.stApnInfo.ucApnLen = pstReq->stDialPara.ucAPNLen;
    (VOS_VOID)VOS_MemCpy(stReq.stApnInfo.aucApnName, pstReq->stDialPara.aucAPN, APP_MAX_APN_LEN);

    if(0 != pstReq->stDialPara.usAuthType)
    {
       /* USER NAME*/
       stReq.stGwAuthInfo.ucUserNameLen = pstReq->stDialPara.ucUserNameLen;
       (VOS_VOID)VOS_MemCpy(stReq.stGwAuthInfo.aucUserName,pstReq->stDialPara.aucUserName,APP_ESM_MAX_USER_NAME_LEN); /* [false alarm]: ����Fortify���� */

       /* PASSWORD*/
       stReq.stGwAuthInfo.ucPwdLen = pstReq->stDialPara.ucPwdLen;
       (VOS_VOID)VOS_MemCpy(stReq.stGwAuthInfo.aucPwd,pstReq->stDialPara.aucPassword,APP_ESM_MAX_PASSWORD_LEN); /* [false alarm]: ����Fortify���� */

       stReq.stGwAuthInfo.enGwAuthType = (VOS_UINT8)pstReq->stDialPara.usAuthType;
    }

    return  l4aPacket2Ps(ulPsReqPid,&stReq, sizeof(APP_ESM_NDISCONN_REQ_STRU));
}


/* ^NDISDUP/^NDISCONN CNF */
VOS_UINT32 l4a_FunPsNdisconnSetCnf(L4A_PS_MSG_STRU* pData,L4A_FW_MSG_FUN_TABLE_STRU* pstTable,VOS_UINT16 usClientId)
{
    APS_L4A_SET_NDISCONN_CNF_STRU stCnf = {0};
    APP_ESM_NDISCONN_CNF_STRU *pstCnf=NULL;
    L4A_RX_INFO_STRU *pNode = NULL;
    APS_L4A_SET_NDISCONN_REQ_STRU   *pstReq=NULL;
    APP_ESM_PDP_SETUP_CNF_STRU stEsmCnf = {0};

    if(NULL == pData)
    {
        pNode = l4a_GetExeCmdNode(pstTable->ulAtReqMsgId, L4A_REQ_FLAG);
        if(NULL != pNode)
        {
            pstReq = pNode->pData;
            if(NULL != pstReq)
            {
                stCnf.enMsgId     = ID_L4A_APS_PDP_ACTIVATE_REJ;
                stCnf.usClientId  = usClientId;
                stCnf.ucCid       = (VOS_UINT8)pstReq->stDialPara.ulCid;
                stCnf.ulErrorCode = ERR_MSP_TIMEOUT;

                return l4aPacket2Aps(&stCnf, sizeof(APS_L4A_SET_NDISCONN_CNF_STRU));
            }
        }
        
        return ERR_MSP_SUCCESS;
    }

    pstCnf = (APP_ESM_NDISCONN_CNF_STRU *)(pData);

    stEsmCnf.ulCid               = pstCnf->ulCid;
    stEsmCnf.ulRslt              = pstCnf->ulRslt;
    stEsmCnf.enBearerState       = pstCnf->enBearerState;
    stEsmCnf.enBearerType        = pstCnf->enBearerType;
    stEsmCnf.ulRabId             = pstCnf->ulRabId;
    stEsmCnf.bitOpBearerState    = pstCnf->bitOpBearerState    ;
    stEsmCnf.bitOpBearerType     = pstCnf->bitOpBearerType     ;
    stEsmCnf.bitOpPdnAddr        = pstCnf->bitOpPdnAddr        ;
    stEsmCnf.bitOpRabId          = pstCnf->bitOpRabId          ;
    stEsmCnf.bitOpApn            = pstCnf->bitOpApn            ;
    stEsmCnf.bitOpSdfQos         = pstCnf->bitOpSdfQos         ;
    stEsmCnf.bitOpDnsPrim        = pstCnf->bitOpDnsPrim        ;
    stEsmCnf.bitOpDnsSec         = pstCnf->bitOpDnsSec         ;
    stEsmCnf.bitOpPCscfPrim      = pstCnf->bitOpPCscfPrim      ;
    stEsmCnf.bitOpPCscfSec       = pstCnf->bitOpPCscfSec       ;
    stEsmCnf.bitOpGateWayAddrInfo= pstCnf->bitOpGateWayAddrInfo;

    (VOS_VOID)VOS_MemCpy(&stEsmCnf.stPDNAddrInfo        ,&pstCnf->stPDNAddrInfo,      sizeof(APP_ESM_IP_ADDR_STRU));
    (VOS_VOID)VOS_MemCpy(&stEsmCnf.stSubnetMask         ,&pstCnf->stSubnetMask,       sizeof(APP_ESM_IP_ADDR_STRU));       
    (VOS_VOID)VOS_MemCpy(&stEsmCnf.stGateWayAddrInfo    ,&pstCnf->stGateWayAddrInfo,  sizeof(APP_ESM_IP_ADDR_STRU));  
    (VOS_VOID)VOS_MemCpy(&stEsmCnf.stDnsPrimAddrInfo    ,&pstCnf->stDnsPrimAddrInfo,  sizeof(APP_ESM_IP_ADDR_STRU));  
    (VOS_VOID)VOS_MemCpy(&stEsmCnf.stDnsSecAddrInfo     ,&pstCnf->stDnsSecAddrInfo,   sizeof(APP_ESM_IP_ADDR_STRU));   
    (VOS_VOID)VOS_MemCpy(&stEsmCnf.stPCscfPrimAddrInfo  ,&pstCnf->stPCscfPrimAddrInfo,sizeof(APP_ESM_IP_ADDR_STRU));
    (VOS_VOID)VOS_MemCpy(&stEsmCnf.stPCscfSecAddrInfo   ,&pstCnf->stPCscfSecAddrInfo, sizeof(APP_ESM_IP_ADDR_STRU));

    (VOS_VOID)VOS_MemCpy(&stEsmCnf.stApnInfo            ,&pstCnf->stApnInfo,          sizeof(APP_ESM_APN_INFO_STRU));
    (VOS_VOID)VOS_MemCpy(&stEsmCnf.stSdfQosInfo         ,&pstCnf->stSdfQosInfo,       sizeof(APP_ESM_EPS_QOS_INFO_STRU));

    /* �����ֵ��ΪSUCC��bitOpRabId��ΪTRUEʱ������ACTIVATE_REJ��������������ACTIVATE_CNF */
    if((ERR_MSP_SUCCESS != pstCnf->ulRslt) && (0 == pstCnf->bitOpRabId))
    {
        return l4a_PktActivateRej2Aps((L4A_PS_MSG_STRU*)&stEsmCnf, ID_L4A_APS_PDP_ACTIVATE_REJ,usClientId);/*����ʧ�ܣ��ϱ�REJ*/
    }
    else
    {
        return l4a_PktActivateCnf2Aps((L4A_PS_MSG_STRU*)&stEsmCnf, ID_L4A_APS_PDP_ACTIVATE_CNF,usClientId);/*����ɹ����ϱ�CNF*/
    }
}

/* TODO: */
VOS_UINT32 l4a_FunPsPPPDialSetReq(L4A_DATA_MSG_STRU* pData,VOS_UINT32 ulPsReqMsgId,VOS_UINT32 ulPsReqPid)
{
    APP_ESM_PDP_SETUP_REQ_STRU stReq= {0};
    APS_L4A_PPP_DIAL_REQ_STRU *pstReq=NULL;

    pstReq = (APS_L4A_PPP_DIAL_REQ_STRU *)(pData);

    stReq.ulMsgId = ulPsReqMsgId;
    stReq.enSetupType = APP_ESM_PDP_SETUP_TYPE_PPP;
    stReq.ulCid       = pstReq->ulCid;
    (VOS_VOID)VOS_MemCpy(&(stReq.stPppInfo), &(pstReq->stPppInfo), sizeof(APP_ESM_PPP_INFO_STRU));
    return  l4aPacket2Ps(ulPsReqPid,&stReq, sizeof(APP_ESM_PDP_SETUP_REQ_STRU));
}

/* TODO: */
VOS_UINT32 l4a_FunPsPPPDialSetCnf(L4A_PS_MSG_STRU* pData,L4A_FW_MSG_FUN_TABLE_STRU* pstTable,VOS_UINT16 usClientId)
{
    APS_L4A_PPP_DIAL_CNF_STRU stCnf = {0};
    APP_ESM_PDP_SETUP_CNF_STRU *pstCnf=NULL;
    L4A_RX_INFO_STRU *pNode = NULL;
    APS_L4A_PPP_DIAL_REQ_STRU *pstReq=NULL;

    if(NULL == pData)
    {
        pNode = l4a_GetExeCmdNode(pstTable->ulAtReqMsgId, L4A_REQ_FLAG);
        if(NULL != pNode)
        {
            pstReq = pNode->pData;
            if(NULL != pstReq)
            {
                stCnf.enMsgId     = ID_L4A_APS_PDP_ACTIVATE_REJ;
                stCnf.usClientId  = usClientId;
                stCnf.ucCid       = (VOS_UINT8)pstReq->ulCid;
                stCnf.ulErrorCode = ERR_MSP_TIMEOUT;

                return l4aPacket2Aps(&stCnf, sizeof(APS_L4A_PPP_DIAL_CNF_STRU));
            }
        }
        
        return ERR_MSP_SUCCESS;
    }

    pstCnf = (APP_ESM_PDP_SETUP_CNF_STRU *)(pData);
    
    /* �����ֵ��ΪSUCC��bitOpRabId��ΪTRUEʱ������ACTIVATE_REJ��������������ACTIVATE_CNF */
    if((ERR_MSP_SUCCESS != pstCnf->ulRslt) && (0 == pstCnf->bitOpRabId))
    {
        return l4a_PktActivateRej2Aps(pData, ID_L4A_APS_PDP_ACTIVATE_REJ,usClientId);/*����ʧ�ܣ��ϱ�REJ*/
    }
    else
    {
        return l4a_PktActivateCnf2Aps(pData, ID_L4A_APS_PDP_ACTIVATE_CNF,usClientId);/*����ɹ����ϱ�CNF*/
    }
}


/* NDISDUP=1,0/PPP�Ͽ����� */
VOS_UINT32 l4a_FunPsDialEndSetReq(L4A_DATA_MSG_STRU* pData,VOS_UINT32 ulPsReqMsgId,VOS_UINT32 ulPsReqPid)
{
    APP_ESM_PDP_RELEASE_REQ_STRU stReq= {0};
    APS_L4A_PS_CALL_END_REQ_STRU *pstReq=NULL;

    pstReq = (APS_L4A_PS_CALL_END_REQ_STRU *)(pData);

    stReq.ulMsgId = ulPsReqMsgId;
    stReq.ulCid = pstReq->ulCid ;
    return  l4aPacket2Ps(ulPsReqPid,&stReq, sizeof(APP_ESM_PDP_RELEASE_REQ_STRU));
}


/* NDISDUP=1,0/PPP�Ͽ����� */
VOS_UINT32 l4a_FunPsDialEndSetCnf(L4A_PS_MSG_STRU* pData,L4A_FW_MSG_FUN_TABLE_STRU* pstTable,VOS_UINT16 usClientId)
{
    APS_L4A_PS_CALL_END_CNF_STRU stCnf  = {0};
    APP_ESM_PDP_RELEASE_CNF_STRU *pstCnf=NULL;
    L4A_RX_INFO_STRU *pNode = NULL;
    APS_L4A_PS_CALL_END_REQ_STRU *pstReq=NULL;

    if(NULL == pData)
    {
        pNode = l4a_GetExeCmdNode(pstTable->ulAtReqMsgId, L4A_REQ_FLAG);
        if(NULL != pNode)
        {
            pstReq = pNode->pData;
            if(NULL != pstReq)
            {
                stCnf.enMsgId     = ID_L4A_APS_PDP_DEACTIVATE_REJ;
                stCnf.usClientId  = usClientId;
                stCnf.ucCid       = (VOS_UINT8)pstReq->ulCid;
                stCnf.ulErrorCode = ERR_MSP_TIMEOUT;

                return l4aPacket2Aps(&stCnf, sizeof(APS_L4A_PS_CALL_END_CNF_STRU));
            }
        }
        
        return ERR_MSP_SUCCESS;
    }

    pstCnf = (APP_ESM_PDP_RELEASE_CNF_STRU *)(pData);
    if(ERR_MSP_SUCCESS == pstCnf->ulRslt)
    {
        return l4a_PktDeactivateCnf2Aps(pData, ID_L4A_APS_PDP_DEACTIVATE_CNF,usClientId);
    }
    else
    {
        return l4a_PktDeactivateRej2Aps(pData, ID_L4A_APS_PDP_DEACTIVATE_REJ,usClientId);
    }
}


VOS_UINT32 l4a_FunPsAuthDataSetReq(L4A_DATA_MSG_STRU* pData,VOS_UINT32 ulPsReqMsgId,VOS_UINT32 ulPsReqPid)
{
    APP_ESM_SET_GW_AUTH_REQ_STRU stReq= {0};
    APS_L4A_SET_AUTHDATA_REQ_STRU *pstReq=NULL;

    pstReq = (APS_L4A_SET_AUTHDATA_REQ_STRU *)(pData);

    stReq.ulMsgId = ulPsReqMsgId;
    stReq.ulOpId  = pstReq->stCtrl.ulPid;
    stReq.ulCid   = (VOS_UINT32)pstReq->stAuthData.ucCid;

    /* win7ר��AT����*/
    if(0 != pstReq->stAuthData.usAuthType)
    {
        stReq.enSetType = APP_ESM_PARA_SETTING;

        /* USER NAME*/
        stReq.stGwAuthInfo.ucUserNameLen = pstReq->stAuthData.ucUserNameLen;
        (VOS_VOID)VOS_MemCpy(stReq.stGwAuthInfo.aucUserName,pstReq->stAuthData.aucUserName,APP_ESM_MAX_USER_NAME_LEN); /* [false alarm]: ����Fortify���� */

        /* PASSWORD*/
        stReq.stGwAuthInfo.ucPwdLen = pstReq->stAuthData.ucPwdLen;
        (VOS_VOID)VOS_MemCpy(stReq.stGwAuthInfo.aucPwd,pstReq->stAuthData.aucPassword,APP_ESM_MAX_PASSWORD_LEN); /* [false alarm]: ����Fortify���� */

        /* AUTH TYPE */
        stReq.stGwAuthInfo.enGwAuthType = (VOS_UINT8)pstReq->stAuthData.usAuthType;
    }
    else
    {
        stReq.enSetType = APP_ESM_PARA_DELETE;
    }
    return  l4aPacket2Ps(ulPsReqPid,&stReq, sizeof(APP_ESM_SET_GW_AUTH_REQ_STRU));
}


VOS_UINT32 l4a_FunAuthdataChk(L4A_PS_MSG_STRU* pData, L4A_RX_INFO_STRU* pNode)
{
    APS_L4A_SET_AUTHDATA_REQ_STRU *pstReq = (APS_L4A_SET_AUTHDATA_REQ_STRU*)(pNode->pData);
    APP_ESM_PARA_SET_CNF_STRU *pstCnf = (APP_ESM_PARA_SET_CNF_STRU *)(pData);

    L4A_VALID_PID_CHECK(pstReq, pstCnf);
}


/* +CGDCONT REQ */
VOS_UINT32 l4a_FunPsCgdcontSetReq(L4A_DATA_MSG_STRU* pData,VOS_UINT32 ulPsReqMsgId,VOS_UINT32 ulPsReqPid)
{
    APP_ESM_SET_CGDCONT_REQ_STRU stReq= {0};
    APS_L4A_SET_CGDCONT_REQ_STRU *pstReq = NULL;

    pstReq = (APS_L4A_SET_CGDCONT_REQ_STRU*)(pData);

    stReq.ulMsgId = ulPsReqMsgId;
    stReq.ulOpId = pstReq->stCtrl.ulPid;
    stReq.ulCid = pstReq->stCgdcontInfo.ucCid;

    if((pstReq->stCgdcontInfo.bitOpEmergency) && (APS_L4A_PDP_FOR_EMC == pstReq->stCgdcontInfo.enEmergency))
    {
        stReq.enBearCidType = APP_ESM_BEARER_TYPE_EMERGENCY;
    }
    else
    {
        stReq.enBearCidType = APP_ESM_CID_TYPE_DEFAULT;
    }

    if((0 == pstReq->stCgdcontInfo.bitOpPdpType) && (0 == pstReq->stCgdcontInfo.bitOpApn))
    {
        stReq.enSetType = APP_ESM_PARA_DELETE;
        stReq.bitOpIpv4AddrAllocType = 0;
        stReq.enIpv4AddrAllocType = APP_ESM_IPV4_ADDR_ALLOC_TYPE_BUTT;
        stReq.enPdnType = APP_ESM_PDN_TYPE_BUTT;
        stReq.stApnInfo.ucApnLen = 0;
    }
    else
    {
        stReq.enSetType              = APP_ESM_PARA_SETTING;
        stReq.bitOpBearType          = 1;
        stReq.bitOpPdnType           = pstReq->stCgdcontInfo.bitOpPdpType;
        stReq.bitOpApn               = pstReq->stCgdcontInfo.bitOpApn;
        stReq.bitOpIpv4AddrAllocType = pstReq->stCgdcontInfo.bitOpIPV4ADDRALLOC;
#if 1
        stReq.bitOpPcscfDiscovery    = pstReq->stCgdcontInfo.bitOpPcscfDiscovery;
        stReq.bitOpImsCnSignalFlag   = pstReq->stCgdcontInfo.bitOpImCnSignalFlg;
#endif
        stReq.enIpv4AddrAllocType   = pstReq->stCgdcontInfo.ucIPV4ADDRALLOC;
        stReq.enPdnType             = pstReq->stCgdcontInfo.enPdpType;
#if 1
        stReq.enPcscfDiscovery      = pstReq->stCgdcontInfo.enPcscfDiscovery;
        stReq.enImsCnSignalFlag     = pstReq->stCgdcontInfo.enImCnSignalFlg;
#endif
        stReq.stApnInfo.ucApnLen = (VOS_UINT8)VOS_StrLen((VOS_CHAR*)pstReq->stCgdcontInfo.aucApn);
        if(stReq.stApnInfo.ucApnLen > APP_MAX_APN_LEN)
        {
            stReq.stApnInfo.ucApnLen = APP_MAX_APN_LEN;
        }

        (VOS_VOID)VOS_MemCpy((VOS_VOID*)(stReq.stApnInfo.aucApnName),
            (VOS_VOID*)(pstReq->stCgdcontInfo.aucApn), stReq.stApnInfo.ucApnLen);
    }

    return  l4aPacket2Ps(ulPsReqPid,&stReq, sizeof(APP_ESM_SET_CGDCONT_REQ_STRU));
}


/* +CGDCONT CNF */
VOS_UINT32 l4a_FunPsCgdcontSetCnf(L4A_PS_MSG_STRU* pData,L4A_FW_MSG_FUN_TABLE_STRU* pstTable,VOS_UINT16 usClientId)
{
    APS_L4A_SET_CGDCONT_CNF_STRU stCnf  = {0};
    APP_ESM_SET_CGDCONT_CNF_STRU *pstCnf=NULL;


    if(NULL == pData)
    {
        stCnf.ulErrorCode = ERR_MSP_TIMEOUT;

        return l4aPacket2Aps(&stCnf, sizeof(APS_L4A_SET_CGDCONT_CNF_STRU));
    }

    pstCnf = (APP_ESM_SET_CGDCONT_CNF_STRU *)(pData);

    stCnf.enMsgId           = pstTable->ulAtCnfMsgId;
    stCnf.stCtrl.ulPid      = pstCnf->ulOpId;
    stCnf.stCtrl.ulClientId = (VOS_UINT32)usClientId;

    stCnf.ulErrorCode = pstCnf->ulRslt;

    return l4aPacket2Aps(&stCnf, sizeof(APS_L4A_SET_CGDCONT_CNF_STRU));
}


VOS_UINT32 l4a_FunCgdcontChk(L4A_PS_MSG_STRU* pData, L4A_RX_INFO_STRU* pNode)
{
    APS_L4A_SET_CGDCONT_REQ_STRU *pstReq = (APS_L4A_SET_CGDCONT_REQ_STRU*)(pNode->pData);
    APP_ESM_SET_CGDCONT_CNF_STRU *pstCnf = (APP_ESM_SET_CGDCONT_CNF_STRU *)(pData);

    L4A_VALID_PID_CHECK(pstReq, pstCnf);
}


/* +CGDSCONT REQ */
VOS_UINT32 l4a_FunPsCgdscontSetReq(L4A_DATA_MSG_STRU* pData,VOS_UINT32 ulPsReqMsgId,VOS_UINT32 ulPsReqPid)
{
    APP_ESM_SET_BEARER_TYPE_REQ_STRU stReq= {0};
    APS_L4A_SET_CGDSCONT_REQ_STRU*  pstReq = NULL;

    pstReq = (APS_L4A_SET_CGDSCONT_REQ_STRU*)(pData);

    stReq.ulMsgId = ulPsReqMsgId;
    stReq.ulOpId = pstReq->stCtrl.ulPid;
    stReq.ulCid = pstReq->stCgdscontInfo.ucSecondaryCid;

    if(0 == pstReq->stCgdscontInfo.bitOpPrimaryCid)
    {
        stReq.enSetType = APP_ESM_PARA_DELETE;
    }
    else
    {
        stReq.enSetType = APP_ESM_PARA_SETTING;
        stReq.enBearCidType = APP_ESM_CID_TYPE_DEDICATED;
        stReq.bitOpLinkdCid = pstReq->stCgdscontInfo.bitOpPrimaryCid;
        stReq.ulLinkdCid = pstReq->stCgdscontInfo.ucPrimaryCid;
    }
    return  l4aPacket2Ps(ulPsReqPid,&stReq, sizeof(APP_ESM_SET_BEARER_TYPE_REQ_STRU));
}


VOS_UINT32 l4a_FunCgdscontChk(L4A_PS_MSG_STRU* pData, L4A_RX_INFO_STRU* pNode)
{
    APS_L4A_SET_CGDSCONT_REQ_STRU *pstReq = (APS_L4A_SET_CGDSCONT_REQ_STRU*)(pNode->pData);
    APP_ESM_PARA_SET_CNF_STRU *pstCnf = (APP_ESM_PARA_SET_CNF_STRU *)(pData);

    L4A_VALID_PID_CHECK(pstReq, pstCnf);
}


static VOS_VOID l4a_SetPortRange(APS_L4A_PDP_TFT_EXT_STRU * pstL4aTft, APP_ESM_TFT_INFO_STRU * pstEsmTft)
{
    /* ���õĵط���֤�������ָ�벻Ϊ��*/

    /* <destination port range>*/
    if(pstL4aTft->bitOpDestPortRange)
    {
        if(pstL4aTft->usLowDestPort == pstL4aTft->usHighDestPort)
        {
            pstEsmTft->bitOpSingleLocalPort = 1;
            pstEsmTft->bitOpLocalPortRange = 0;
            pstEsmTft->usSingleLcPort = pstL4aTft->usLowDestPort;
        }
        else if(pstL4aTft->usLowDestPort < pstL4aTft->usHighDestPort)
        {
            pstEsmTft->bitOpSingleLocalPort = 0;
            pstEsmTft->bitOpLocalPortRange = 1;

            pstEsmTft->usLcPortLowLimit = pstL4aTft->usLowDestPort;
            pstEsmTft->usLcPortHighLimit = pstL4aTft->usHighDestPort;
        }
        else /* ��Сֵ�������ֵ*/
        {
            pstEsmTft->bitOpSingleLocalPort = 0;
            pstEsmTft->bitOpLocalPortRange = 0;
        }
    }

    /* <source port range>*/
    if(pstL4aTft->bitOpSrcPortRange)
    {
        if(pstL4aTft->usLowSourcePort == pstL4aTft->usHighSourcePort)
        {
            pstEsmTft->bitOpSingleRemotePort = 1;
            pstEsmTft->bitOpRemotePortRange = 0;
            pstEsmTft->usSingleRmtPort = pstL4aTft->usLowSourcePort;
        }
        else if(pstL4aTft->usLowSourcePort < pstL4aTft->usHighSourcePort)
        {
            pstEsmTft->bitOpSingleRemotePort = 0;
            pstEsmTft->bitOpRemotePortRange = 1;

            pstEsmTft->usRmtPortLowLimit = pstL4aTft->usLowSourcePort;
            pstEsmTft->usRmtPortHighLimit = pstL4aTft->usHighSourcePort;
        }
        else
        {
            pstEsmTft->bitOpSingleRemotePort = 0;
            pstEsmTft->bitOpRemotePortRange = 0;
        }
    }

    return ;
}


VOS_VOID l4a_FunSetTftInfo(APP_ESM_SET_TFT_REQ_STRU* pstPsCgtftReq, APS_L4A_SET_CGTFT_REQ_STRU* pstCgtftReq)
{
    if((0 == pstCgtftReq->stTftInfo.bitOpPktFilterId) && (0 == pstCgtftReq->stTftInfo.bitOpPrecedence))
    {
        pstPsCgtftReq->enSetType = APP_ESM_PARA_DELETE;   /* 0:set 1:del*/
    }
    else
    {
        pstPsCgtftReq->enSetType = APP_ESM_PARA_SETTING;   /* 0:set 1:del*/

        /* <packet filter identifier>*/
        pstPsCgtftReq->stAppTftInfo.ucPacketFilterId = pstCgtftReq->stTftInfo.ucPacketFilterId;

        /* <evaluation precedence index>*/
        pstPsCgtftReq->stAppTftInfo.ucPrecedence = pstCgtftReq->stTftInfo.ucPrecedence;

        /* <source address and subnet mask>*/

        if(1 == pstCgtftReq->stTftInfo.bitOpSrcIp)
        {
            if(APP_ESM_PDN_TYPE_IPV4 == pstCgtftReq->stTftInfo.stSourceIpaddr.enPdpType)
            {
                pstPsCgtftReq->stAppTftInfo.bitOpRmtIpv4AddrAndMask = 1;
                
                (VOS_VOID)VOS_MemCpy((VOS_VOID*)(pstPsCgtftReq->stAppTftInfo.aucRmtIpv4Address),
                    (VOS_VOID*)(pstCgtftReq->stTftInfo.stSourceIpaddr.aucIpv4Addr), APP_MAX_IPV4_ADDR_LEN);

                (VOS_VOID)VOS_MemCpy((VOS_VOID*)(pstPsCgtftReq->stAppTftInfo.aucRmtIpv4Mask),
                    (VOS_VOID*)(pstCgtftReq->stTftInfo.stSourceIpMask.aucIpv4Addr), APP_MAX_IPV4_ADDR_LEN);
            }

            if(APP_ESM_PDN_TYPE_IPV6 == pstCgtftReq->stTftInfo.stSourceIpaddr.enPdpType)
            {
                pstPsCgtftReq->stAppTftInfo.bitOpRmtIpv6AddrAndMask = 1;

                (VOS_VOID)VOS_MemCpy((VOS_VOID*)(pstPsCgtftReq->stAppTftInfo.aucRmtIpv6Address),
                    (VOS_VOID*)(pstCgtftReq->stTftInfo.stSourceIpaddr.aucIpv6Addr), APP_MAX_IPV6_ADDR_LEN);

                (VOS_VOID)VOS_MemCpy((VOS_VOID*)(pstPsCgtftReq->stAppTftInfo.aucRmtIpv6Mask),
                    (VOS_VOID*)(pstCgtftReq->stTftInfo.stSourceIpMask.aucIpv6Addr), APP_MAX_IPV6_ADDR_LEN);
            }
        }

        /* <protocol number (ipv4) / next header (ipv6)>*/
        pstPsCgtftReq->stAppTftInfo.bitOpProtocolId = pstCgtftReq->stTftInfo.bitOpProtocolId;
        if(pstPsCgtftReq->stAppTftInfo.bitOpProtocolId)
        {
            pstPsCgtftReq->stAppTftInfo.ucProtocolId = pstCgtftReq->stTftInfo.ucProtocolId;
        }

        /* <destination port range>,<source port range>*/
        l4a_SetPortRange(&(pstCgtftReq->stTftInfo), &(pstPsCgtftReq->stAppTftInfo));

        /* <ipsec security parameter index (spi)>*/
        pstPsCgtftReq->stAppTftInfo.bitOpSecuParaIndex = pstCgtftReq->stTftInfo.bitOpSpi;
        if(pstPsCgtftReq->stAppTftInfo.bitOpSecuParaIndex)
        {
            pstPsCgtftReq->stAppTftInfo.ulSecuParaIndex = pstCgtftReq->stTftInfo.ulSecuParaIndex;
        }

        pstPsCgtftReq->stAppTftInfo.bitOpTypeOfService = pstCgtftReq->stTftInfo.bitOpTosMask;
        pstPsCgtftReq->stAppTftInfo.bitOpFlowLabelType = pstCgtftReq->stTftInfo.bitOpFlowLable;

        /* <type of service (tos) (ipv4) and mask / traffic class (ipv6) and mask>*/
        pstPsCgtftReq->stAppTftInfo.bitOpTypeOfService = pstCgtftReq->stTftInfo.bitOpTosMask;
        if(pstPsCgtftReq->stAppTftInfo.bitOpTypeOfService)
        {
            pstPsCgtftReq->stAppTftInfo.ucTypeOfService = pstCgtftReq->stTftInfo.ucTypeOfService;
            pstPsCgtftReq->stAppTftInfo.ucTypeOfServiceMask = pstCgtftReq->stTftInfo.ucTypeOfServiceMask;
        }

        /* <flow label (ipv6)>*/
        pstPsCgtftReq->stAppTftInfo.bitOpFlowLabelType = pstCgtftReq->stTftInfo.bitOpFlowLable;
        if(pstPsCgtftReq->stAppTftInfo.bitOpFlowLabelType)
        {
            pstPsCgtftReq->stAppTftInfo.ulFlowLabelType = pstCgtftReq->stTftInfo.ulFlowLable;
        }

        /* <direction>  AT��NAS��Э���෴*/
        /* (AT:  0-pre rel 7, 1-uplink,   2-downlink, 3-birectional)*/
        /* (NAS: 0-pre rel 7, 1-downlink, 2-uplink,   3-birectional)*/
        if(1 == pstCgtftReq->stTftInfo.enTftFilterDirection)
        {
            pstPsCgtftReq->stAppTftInfo.enDirection = APP_ESM_TRANSFER_DIRECTION_UPLINK;
        }
        else if(2 == pstCgtftReq->stTftInfo.enTftFilterDirection)
        {
            pstPsCgtftReq->stAppTftInfo.enDirection = APP_ESM_TRANSFER_DIRECTION_DOWNLINK;
        }
        else
        {
            pstPsCgtftReq->stAppTftInfo.enDirection = pstCgtftReq->stTftInfo.enTftFilterDirection;
        }
    }

    return ;
}

/* +CGTFT REQ */
VOS_UINT32 l4a_FunPsCgtftSetReq(L4A_DATA_MSG_STRU* pData,VOS_UINT32 ulPsReqMsgId,VOS_UINT32 ulPsReqPid)
{
    APP_ESM_SET_TFT_REQ_STRU stReq= {0};
    APS_L4A_SET_CGTFT_REQ_STRU *pstReq = NULL;

    pstReq = (APS_L4A_SET_CGTFT_REQ_STRU*)(pData);

    stReq.ulMsgId = ulPsReqMsgId;
    stReq.ulOpId = pstReq->stCtrl.ulPid;
    stReq.ulCid = pstReq->ulCid;

    l4a_FunSetTftInfo(&stReq, pstReq);
    return  l4aPacket2Ps(ulPsReqPid,&stReq, sizeof(APP_ESM_SET_TFT_REQ_STRU));
}


VOS_UINT32 l4a_FunCgtftChk(L4A_PS_MSG_STRU* pData, L4A_RX_INFO_STRU* pNode)
{
    APS_L4A_SET_CGTFT_REQ_STRU *pstReq = (APS_L4A_SET_CGTFT_REQ_STRU*)(pNode->pData);
    APP_ESM_PARA_SET_CNF_STRU *pstCnf = (APP_ESM_PARA_SET_CNF_STRU *)(pData);

    L4A_VALID_PID_CHECK(pstReq, pstCnf);
}


/* +CGACT REQ */
VOS_UINT32 l4a_FunPsCgactSetReq(L4A_DATA_MSG_STRU* pData,VOS_UINT32 ulPsReqMsgId,VOS_UINT32 ulPsReqPid)
{
    APP_ESM_PDP_SETUP_REQ_STRU stPsActReq = {0};
    APP_ESM_PDP_RELEASE_REQ_STRU stPsDeactReq = {0};
    APS_L4A_SET_CGACT_REQ_STRU *pstReq = NULL;
    VOS_UINT32 ret = 0;
    
    pstReq = (APS_L4A_SET_CGACT_REQ_STRU*)(pData);

    if(pstReq->enState == 1)
    {
        stPsActReq.ulMsgId = ID_APP_ESM_PDP_SETUP_REQ;
        stPsActReq.ulCid = l4a_GetUlValidCidIndex(pstReq->aulCid, 0);
        stPsActReq.enSetupType = APP_ESM_PDP_SETUP_TYPE_NORMAL;

        ret = l4aPacket2Ps(ulPsReqPid,&stPsActReq, sizeof(APP_ESM_PDP_SETUP_REQ_STRU));
        if(ERR_MSP_WAIT_ASYNC == ret)
        {
            (VOS_VOID)l4a_AddCmdToListEx(pData, ID_APS_L4A_SET_CGACT_REQ, ID_APP_ESM_PDP_SETUP_CNF);
            return ERR_MSP_SUCCESS;
        }
    }
    else
    {
        stPsDeactReq.ulMsgId = ID_APP_ESM_PDP_RELEASE_REQ;
        stPsDeactReq.ulCid = l4a_GetUlValidCidIndex(pstReq->aulCid, 0);

        ret = l4aPacket2Ps(ulPsReqPid,&stPsDeactReq, sizeof(APP_ESM_PDP_RELEASE_REQ_STRU));
        if(ERR_MSP_WAIT_ASYNC == ret)
        {
            (VOS_VOID)l4a_AddCmdToListEx(pData, ID_APS_L4A_SET_CGACT_REQ, ID_APP_ESM_PDP_RELEASE_CNF);
            return ERR_MSP_SUCCESS;
        }
    }

    return ret;
}


/* +CGACT CNF */
VOS_UINT32 l4a_FunPsCgactSetCnf(L4A_PS_MSG_STRU* pData,L4A_FW_MSG_FUN_TABLE_STRU* pstTable,VOS_UINT16 usClientId)
{
    APP_ESM_PDP_SETUP_CNF_STRU* pstPsActCnf = NULL;
    APP_ESM_PDP_RELEASE_CNF_STRU* pstPsDeactCnf = NULL;
    L4A_RX_INFO_STRU *pNode = NULL;
    APS_L4A_SET_CGACT_REQ_STRU *pstReq = NULL;
    APS_L4A_PDP_ACTIVATE_REJ_STRU stActCnf = {0};
    APS_L4A_PDP_DEACTIVATE_REJ_STRU stDeactCnf = {0};
    VOS_UINT32 ulCid;

    if(NULL == pData)
    {
        pNode = l4a_GetExeCmdNode(pstTable->ulAtReqMsgId, L4A_REQ_FLAG);
        if(NULL != pNode)
        {
            pstReq = pNode->pData;
            if(NULL != pstReq)
            {
                ulCid = l4a_GetUlValidCidIndex(pstReq->aulCid, 0);
                if(pstReq->enState)
                {
                    stActCnf.enMsgId         = ID_L4A_APS_PDP_ACTIVATE_REJ;
                    stActCnf.usClientId      = usClientId;
                    stActCnf.ucCid           = (VOS_UINT8)ulCid;
                    stActCnf.ulEsmCause      = ERR_MSP_TIMEOUT;

                    return l4aPacket2Aps((&stActCnf), sizeof(APS_L4A_PDP_ACTIVATE_REJ_STRU));
                }
                else
                {
                    stDeactCnf.enMsgId         = ID_L4A_APS_PDP_DEACTIVATE_REJ;
                    stDeactCnf.usClientId      = usClientId;
                    stDeactCnf.ucCid           = (VOS_UINT8)usClientId;
                    stDeactCnf.ulEsmCause      = ERR_MSP_TIMEOUT;

                    return l4aPacket2Aps((&stDeactCnf), sizeof(APS_L4A_PDP_DEACTIVATE_REJ_STRU));
                }
            }
        }
        
        return ERR_MSP_SUCCESS;
    }

    if( ID_APP_ESM_PDP_SETUP_CNF == pData->ulMsgId)
    {
        pstPsActCnf = (APP_ESM_PDP_SETUP_CNF_STRU *)(pData);
        
        /* �����ֵ��ΪSUCC��bitOpRabId��ΪTRUEʱ������ACTIVATE_REJ��������������ACTIVATE_CNF */
        if((ERR_MSP_SUCCESS != pstPsActCnf->ulRslt) && (0 == pstPsActCnf->bitOpRabId))
        {
            return l4a_PktActivateRej2Aps(pData, ID_L4A_APS_PDP_ACTIVATE_REJ,usClientId);/*����ʧ�ܣ��ϱ�REJ*/
        }
        else
        {
            return l4a_PktActivateCnf2Aps(pData, ID_L4A_APS_PDP_ACTIVATE_CNF,usClientId);/*����ɹ����ϱ�CNF*/
        }
    }
    else if ( ID_APP_ESM_PDP_RELEASE_CNF == pData->ulMsgId)
    {
        pstPsDeactCnf = (APP_ESM_PDP_RELEASE_CNF_STRU *)(pData);
        if(ERR_MSP_SUCCESS == pstPsDeactCnf->ulRslt)
        {
            return l4a_PktDeactivateCnf2Aps(pData, ID_L4A_APS_PDP_DEACTIVATE_CNF,usClientId);
        }
        else
        {
            return l4a_PktDeactivateRej2Aps(pData, ID_L4A_APS_PDP_DEACTIVATE_REJ,usClientId);
        }
    }
    return ERR_MSP_FAILURE;
}

/* +CGAUTO */
VOS_UINT32 l4a_FunPsCgautoSetReq(L4A_DATA_MSG_STRU* pData,VOS_UINT32 ulPsReqMsgId,VOS_UINT32 ulPsReqPid)
{
    APP_ESM_SET_PDP_MANAGER_TYPE_REQ_STRU stReq= {0};
    APS_L4A_SET_CGAUTO_REQ_STRU *pstReq = NULL;

    pstReq = (APS_L4A_SET_CGAUTO_REQ_STRU*)(pData);

    stReq.ulMsgId = ulPsReqMsgId;
    stReq.ulOpId = pstReq->stCtrl.ulPid;

    stReq.enSetType = APP_ESM_PARA_SETTING;

    if(EN_L4A_AUTO_ANSWER == pstReq->enAnsMode)
    {
        stReq.enAnsMode = APP_ESM_ANSWER_MODE_MANI;  /* �ֶ�Ӧ��*/
    }
    else if(EN_L4A_MANU_ANSWER == pstReq->enAnsMode)
    {
        stReq.enAnsMode = APP_ESM_ANSWER_MODE_AUTO;
        stReq.enAnsType = APP_ESM_ANSWER_ACCEPT;  /* �Զ�Ӧ��*/
    }
    else
    {
        stReq.enAnsMode = APP_ESM_ANSWER_MODE_AUTO;
        stReq.enAnsType = APP_ESM_ANSWER_REJ;   /* �Զ��ܾ�*/
    }
    return  l4aPacket2Ps(ulPsReqPid,&stReq, sizeof(APP_ESM_SET_PDP_MANAGER_TYPE_REQ_STRU));
}


VOS_UINT32 l4a_FunPsCgautoSetCnf(L4A_PS_MSG_STRU* pData,L4A_FW_MSG_FUN_TABLE_STRU* pstTable,VOS_UINT16 usClientId)
{
    APS_L4A_SET_CGAUTO_CNF_STRU stCnf  = {0};
    APP_ESM_SET_PDP_MANAGER_TYPE_CNF_STRU *pstCnf=NULL;

    if(NULL == pData)
    {
        stCnf.ulErrorCode = ERR_MSP_TIMEOUT;
        return l4aPacket2Aps(&stCnf, sizeof(L4A_NO_CID_COMM_CNF_STRU));
    }

    pstCnf = (APP_ESM_SET_PDP_MANAGER_TYPE_CNF_STRU *)(pData);

    stCnf.enMsgId = pstTable->ulAtCnfMsgId;
    stCnf.stCtrl.ulPid = pstCnf->ulOpId;
    stCnf.stCtrl.ulClientId = (VOS_UINT32)usClientId;

    stCnf.ulErrorCode = pstCnf->ulSetRslt;
    return l4aPacket2Aps(&stCnf, sizeof(APS_L4A_SET_CGAUTO_CNF_STRU));
}


VOS_UINT32 l4a_FunCgautoChk(L4A_PS_MSG_STRU* pData, L4A_RX_INFO_STRU* pNode)
{
    APS_L4A_SET_CGAUTO_REQ_STRU *pstReq = (APS_L4A_SET_CGAUTO_REQ_STRU*)(pNode->pData);
    APP_ESM_SET_PDP_MANAGER_TYPE_CNF_STRU *pstCnf = (APP_ESM_SET_PDP_MANAGER_TYPE_CNF_STRU *)(pData);

    L4A_VALID_PID_CHECK(pstReq, pstCnf);
}


VOS_VOID l4a_FunCgcontrdpPkj(APP_ESM_INQ_DYNAMIC_PDP_CONT_CNF_STRU* pstPsPdpContCnf, APS_L4A_PRIM_PDP_DYNAMIC_EXT_STRU *pstPrim)
{
    if(0 == pstPsPdpContCnf->bitOpApn)
    {
        /* ��ʶר�г��أ����ڹ��� */
        pstPrim->bitOpApn = 0;
        return;
    }
    
    pstPrim->ucPrimayCid          = (VOS_UINT8)pstPsPdpContCnf->ulCid;
    pstPrim->bitOpBearerId        = 1;
    pstPrim->bitOpApn             = pstPsPdpContCnf->bitOpApn;
    pstPrim->bitOpIpAddr          = pstPsPdpContCnf->bitOpPdnAddr;
    pstPrim->bitOpSubMask         = pstPsPdpContCnf->bitOpPdnAddr;
    pstPrim->ucBearerId           = (VOS_UINT8)pstPsPdpContCnf->ulEpsbId;
    pstPrim->bitOpDNSPrimAddr     = pstPsPdpContCnf->bitOpDnsPrim;
    pstPrim->bitOpDNSSecAddr      = pstPsPdpContCnf->bitOpDnsSec;
    pstPrim->bitOpPCSCFPrimAddr   = pstPsPdpContCnf->bitOpPCscfPrim;
    pstPrim->bitOpPCSCFSecAddr    = pstPsPdpContCnf->bitOpPCscfSec;
    pstPrim->bitOpGwAddr          = pstPsPdpContCnf->bitOpGateWayAddrInfo;
#if 1
    pstPrim->bitOpImCnSignalFlg   = pstPsPdpContCnf->bitOpImsCnSignalFlag;
    pstPrim->enImCnSignalFlg      = (APS_L4A_IMS_CN_SIG_FLAG_ENUM_UINT8)pstPsPdpContCnf->enImsCnSignalFlag;
#endif
    (VOS_VOID)VOS_MemSet((VOS_VOID*)(pstPrim->aucApn), 0, APS_L4A_MAX_APN_LEN + 1);

    (VOS_VOID)VOS_MemCpy((VOS_VOID*)(pstPrim->aucApn),
        (VOS_VOID*)(pstPsPdpContCnf->stApnInfo.aucApnName), (VOS_UINT32)pstPsPdpContCnf->stApnInfo.ucApnLen);

    (VOS_VOID)VOS_MemCpy((VOS_VOID*)&(pstPrim->stPdpAddr),
        (VOS_VOID*)&(pstPsPdpContCnf->stPDNAddrInfo), sizeof(APP_ESM_IP_ADDR_STRU));

    (VOS_VOID)VOS_MemCpy((VOS_VOID*)&(pstPrim->stSubnetMask),
        (VOS_VOID*)&(pstPsPdpContCnf->stSubnetMask), sizeof(APP_ESM_IP_ADDR_STRU));

    (VOS_VOID)VOS_MemCpy((VOS_VOID*)&(pstPrim->stGWAddr),
        (VOS_VOID*)&(pstPsPdpContCnf->stGateWayAddrInfo), sizeof(APP_ESM_IP_ADDR_STRU));

    (VOS_VOID)VOS_MemCpy((VOS_VOID*)&(pstPrim->stDNSPrimAddr),
        (VOS_VOID*)&(pstPsPdpContCnf->stDnsPrimAddrInfo), sizeof(APP_ESM_IP_ADDR_STRU));

    (VOS_VOID)VOS_MemCpy((VOS_VOID*)&(pstPrim->stDNSSecAddr),
        (VOS_VOID*)&(pstPsPdpContCnf->stDnsSecAddrInfo), sizeof(APP_ESM_IP_ADDR_STRU));

    (VOS_VOID)VOS_MemCpy((VOS_VOID*)&(pstPrim->stPCSCFPrimAddr),
        (VOS_VOID*)&(pstPsPdpContCnf->stPCscfPrimAddrInfo), sizeof(APP_ESM_IP_ADDR_STRU));

    (VOS_VOID)VOS_MemCpy((VOS_VOID*)&(pstPrim->stPCSCFSecAddr),
        (VOS_VOID*)&(pstPsPdpContCnf->stPCscfSecAddrInfo), sizeof(APP_ESM_IP_ADDR_STRU));
}

VOS_UINT32 l4a_FunPsCgcontrdpSetCnf(L4A_PS_MSG_STRU* pData,L4A_FW_MSG_FUN_TABLE_STRU* pstTable,VOS_UINT16 usClientId)
{
    APP_ESM_INQ_DYNAMIC_PDP_CONT_CNF_STRU *pstPsPdpContCnf = NULL;
    APS_L4A_SET_CGCONTRDP_CNF_STRU *pstCnf = NULL;
    VOS_UINT32 ulsize, i, j;
    VOS_UINT32 ret;
    L4A_RX_INFO_STRU *pNode = NULL;
    L4A_ONLY_CID_COMM_REQ_STRU *pstReq = NULL;

    pNode = l4a_GetExeCmdNode(pstTable->ulAtReqMsgId, L4A_REQ_FLAG);
    if((NULL == pNode) || (NULL == pNode->pData) || (NULL == pData))
    {
        L4A_INFO_LOG("%s pNode: %p, pData %p.\n", __FUNCTION__, pNode, pData);

        /* �Ҳ�������ڵ㣬��AT/TAF��ʱ���Ʒ���ERROR */
        return ERR_MSP_SUCCESS;
    }

    pstPsPdpContCnf = (APP_ESM_INQ_DYNAMIC_PDP_CONT_CNF_STRU *)(pData);

    pstReq = (L4A_ONLY_CID_COMM_REQ_STRU *)pNode->pData;

    if(0 == pNode->ulCidNum)
    {
        pNode->ulCidNum = l4a_GetValidCidNum(pstReq->aucCid);
        if(0 == pNode->ulCidNum)
        {
            L4A_INFO_LOG("%s %d failed.\n", __FUNCTION__, __LINE__);
            
            return ERR_MSP_SUCCESS;
        }
        
        L4A_INFO_LOG("%s %d.\n", __FUNCTION__, pNode->ulCidNum);

        ulsize = sizeof(APS_L4A_SET_CGCONTRDP_CNF_STRU) + (pNode->ulCidNum * sizeof(APS_L4A_PRIM_PDP_DYNAMIC_EXT_STRU));

        pstCnf = VOS_MemAlloc(MSP_L4_L4A_PID, DYNAMIC_MEM_PT, ulsize);
        if(NULL == pstCnf)
        {
            /* �����ڴ�ʧ�ܣ���AT/TAF��ʱ���Ʒ���ERROR */
            return ERR_MSP_SUCCESS;
        }
        
        (VOS_VOID)VOS_MemSet((VOS_VOID*)pstCnf, 0, ulsize);

        pNode->pCnfData = pstCnf;

        pstCnf->enMsgId             = pstTable->ulAtCnfMsgId;
        pstCnf->stCtrl.ulPid        = pstPsPdpContCnf->ulOpId;
        pstCnf->stCtrl.ulClientId   = (VOS_UINT32)usClientId;
        pstCnf->ulCidNum            = pNode->ulCidNum;
    }
    else
    {
        if(NULL == pNode->pCnfData)
        {
            L4A_INFO_LOG("%s %d failed.\n", __FUNCTION__, __LINE__);
            
            return ERR_MSP_SUCCESS;
        }
        pstCnf = pNode->pCnfData;
    }

    pstCnf->ulErrorCode = pstPsPdpContCnf->ulRslt;

    /* ����ɹ��ȱ���Ӧ����Ϣ��Ȼ���ж��Ƿ����һ�������cid�����ʧ��ֱ��Ӧ���AT/TAF */
    if(ERR_MSP_SUCCESS == pstCnf->ulErrorCode)
    {
        l4a_FunCgcontrdpPkj(pstPsPdpContCnf, &pstCnf->astPrimParaInfo[pNode->ulCidIndex]);
        
        pNode->ulCidIndex++;
        if(pNode->ulCidIndex != pNode->ulCidNum)
        {
            /* �ٴη������� */
            ret = l4a_FunRDPCidIndexReq((L4A_DATA_MSG_STRU*)pstReq, pstTable->ulPsReqMsgId, pstTable->ulPsReqPid, pNode->ulCidIndex);
            if(ERR_MSP_WAIT_ASYNC == ret)
            {
                L4A_INFO_LOG("%s %d.\n", __FUNCTION__, pNode->ulCidIndex);

                /* �����첽״̬�����õĵط�Ҫ�ж� */
                return ERR_MSP_WAIT_ASYNC;
            }
        }
    }

    for(i = 0, j = 0; i < pNode->ulCidNum; i++)
    {
        if(0 != pstCnf->astPrimParaInfo[i].bitOpApn)
        {
            (VOS_VOID)VOS_MemCpy(&pstCnf->astPrimParaInfo[j++], &pstCnf->astPrimParaInfo[i], sizeof(APS_L4A_PRIM_PDP_DYNAMIC_EXT_STRU));
        }
    }

    pstCnf->ulCidNum = j;

    ulsize = sizeof(APS_L4A_SET_CGCONTRDP_CNF_STRU) + (pNode->ulCidNum * sizeof(APS_L4A_PRIM_PDP_DYNAMIC_EXT_STRU));

    ret = l4aPacket2Aps(pstCnf, ulsize);

    (VOS_VOID)VOS_MemFree(MSP_L4_L4A_PID, pstCnf);

    return ret;
}


VOS_UINT32 l4a_FunCgcontrdpChk(L4A_PS_MSG_STRU* pData, L4A_RX_INFO_STRU* pNode)
{
    APS_L4A_SET_CGCONTRDP_REQ_STRU *pstReq = (APS_L4A_SET_CGCONTRDP_REQ_STRU*)(pNode->pData);
    APP_ESM_INQ_DYNAMIC_PDP_CONT_CNF_STRU *pstCnf = (APP_ESM_INQ_DYNAMIC_PDP_CONT_CNF_STRU *)(pData);

    L4A_VALID_PID_CHECK(pstReq, pstCnf);
}



VOS_UINT32 l4a_FunPsCgscontrdpSetCnf(L4A_PS_MSG_STRU* pData,L4A_FW_MSG_FUN_TABLE_STRU* pstTable,VOS_UINT16 usClientId)
{
    APP_ESM_INQ_DYNAMIC_PDP_CONT_CNF_STRU *pstPsPdpContCnf = NULL;
    APS_L4A_SET_CGSCONTRDP_CNF_STRU *pstCnf = NULL;
    VOS_UINT32 ulsize, i,j;
    VOS_UINT32 ret;
    L4A_RX_INFO_STRU *pNode = NULL;
    L4A_ONLY_CID_COMM_REQ_STRU *pstReq = NULL;
    
    pNode = l4a_GetExeCmdNode(pstTable->ulAtReqMsgId, L4A_REQ_FLAG);
    if((NULL == pNode) || (NULL == pNode->pData) || (NULL == pData))
    {
        L4A_INFO_LOG("%s %d failed.\n", __FUNCTION__, __LINE__);

        /* �Ҳ�������ڵ㣬��AT/TAF��ʱ���Ʒ���ERROR */
        return ERR_MSP_SUCCESS;
    }

    pstPsPdpContCnf = (APP_ESM_INQ_DYNAMIC_PDP_CONT_CNF_STRU *)(pData);
    pstReq = pNode->pData;

    if(0 == pNode->ulCidNum)
    {
        pNode->ulCidNum = l4a_GetValidCidNum(pstReq->aucCid);
        if(0 == pNode->ulCidNum)
        {
            L4A_INFO_LOG("%s %d failed.\n", __FUNCTION__, __LINE__);
            
            return ERR_MSP_SUCCESS;
        }

        L4A_INFO_LOG("%s %d.\n", __FUNCTION__, pNode->ulCidNum);

        ulsize = sizeof(APS_L4A_SET_CGSCONTRDP_CNF_STRU) + (pNode->ulCidNum * sizeof(APS_L4A_SEC_PDP_DYNAMIC_EXT_STRU));

        pstCnf = VOS_MemAlloc(MSP_L4_L4A_PID, DYNAMIC_MEM_PT, ulsize);
        if(NULL == pstCnf)
        {
            /* �����ڴ�ʧ�ܣ���AT/TAF��ʱ���Ʒ���ERROR */
            return ERR_MSP_SUCCESS;
        }

        (VOS_VOID)VOS_MemSet((VOS_VOID*)pstCnf, 0, ulsize);

        pNode->pCnfData = pstCnf;

        pstCnf->enMsgId             = pstTable->ulAtCnfMsgId;
        pstCnf->stCtrl.ulPid        = pstPsPdpContCnf->ulOpId;
        pstCnf->stCtrl.ulClientId   = (VOS_UINT32)usClientId;
        pstCnf->ulCidNum            = pNode->ulCidNum;
    }
    else
    {
        if(NULL == pNode->pCnfData)
        {
            L4A_INFO_LOG("%s %d failed.\n", __FUNCTION__, __LINE__);
            
            return ERR_MSP_SUCCESS;
        }
        pstCnf = pNode->pCnfData;
    }

    pstCnf->ulErrorCode = pstPsPdpContCnf->ulRslt;

    /* ����ɹ��ȱ���Ӧ����Ϣ��Ȼ���ж��Ƿ����һ�������cid�����ʧ��ֱ��Ӧ���AT/TAF */
    if(ERR_MSP_SUCCESS == pstCnf->ulErrorCode)
    {
        if(pstPsPdpContCnf->bitOpLinkCid)   /* ֻ��¼ר�г�����Ϣ */
        {
            pstCnf->astSecParaInfo[pNode->ulCidIndex].ucPrimaryCid  = (VOS_UINT8)pstPsPdpContCnf->ulLinkCid;
            pstCnf->astSecParaInfo[pNode->ulCidIndex].ucCid         = (VOS_UINT8)pstPsPdpContCnf->ulCid;
            pstCnf->astSecParaInfo[pNode->ulCidIndex].ucBearerId    = (VOS_UINT8)pstPsPdpContCnf->ulEpsbId;
        }
        else
        {
            pstCnf->astSecParaInfo[pNode->ulCidIndex].ucPrimaryCid  = 0;
            pstCnf->astSecParaInfo[pNode->ulCidIndex].ucCid         = 0;
            pstCnf->astSecParaInfo[pNode->ulCidIndex].ucBearerId    = 0;
        }

        pNode->ulCidIndex++;
        if(pNode->ulCidIndex != pNode->ulCidNum)
        {
            /* �ٴη������� */
            ret = l4a_FunRDPCidIndexReq((L4A_DATA_MSG_STRU*)pstReq, pstTable->ulPsReqMsgId, pstTable->ulPsReqPid, pNode->ulCidIndex);
            if(ERR_MSP_WAIT_ASYNC == ret)
            {
                L4A_INFO_LOG("%s %d.\n", __FUNCTION__, pNode->ulCidIndex);

                /* �����첽״̬�����õĵط�Ҫ�ж� */
                return ERR_MSP_WAIT_ASYNC;
            }
        }
    }

    for(i = 0, j = 0; i < pNode->ulCidNum; i++)
    {
        /* 5 <= bearerid <= 15���Դ����ж��Ƿ���ר�г��� */
        if(0 != pstCnf->astSecParaInfo[i].ucBearerId)
        {
            (VOS_VOID)VOS_MemCpy(&pstCnf->astSecParaInfo[j++], &pstCnf->astSecParaInfo[i], sizeof(APS_L4A_SEC_PDP_DYNAMIC_EXT_STRU));
        }
    }

    pstCnf->ulCidNum = j;

    ulsize = sizeof(APS_L4A_SET_CGSCONTRDP_CNF_STRU) + (pNode->ulCidNum * sizeof(APS_L4A_SEC_PDP_DYNAMIC_EXT_STRU));

    ret = l4aPacket2Aps(pstCnf, ulsize);

    (VOS_VOID)VOS_MemFree(MSP_L4_L4A_PID, pstCnf);

    return ret;
}


VOS_UINT32 l4a_FunCgscontrdpChk(L4A_PS_MSG_STRU* pData, L4A_RX_INFO_STRU* pNode)
{
    APS_L4A_SET_CGSCONTRDP_REQ_STRU *pstReq = (APS_L4A_SET_CGSCONTRDP_REQ_STRU*)(pNode->pData);
    APP_ESM_INQ_DYNAMIC_PDP_CONT_CNF_STRU *pstCnf = (APP_ESM_INQ_DYNAMIC_PDP_CONT_CNF_STRU *)(pData);

    L4A_VALID_PID_CHECK(pstReq, pstCnf);
}


VOS_VOID l4a_FunCgtftrdpPkj(APP_ESM_INQ_DYNAMIC_TFT_CNF_STRU* pstPsInqTftCnf, APS_L4A_SDF_PF_TFT_STRU *psttft)
{
    VOS_UINT32 j = 0;

    /* ���õĵط���֤pstPsInqTftCnf��pstCgtftCnf��Ϊ��*/

    psttft->ulPfNum= pstPsInqTftCnf->ulPfNum;
    psttft->ulCid = pstPsInqTftCnf->ulCid;
    for(j = 0; j < pstPsInqTftCnf->ulPfNum; j++)
    {
        psttft->astTftInfo[j].bitOpPktFilterId = 1;
        psttft->astTftInfo[j].bitOpPrecedence = 1;
        psttft->astTftInfo[j].bitOpSrcIp = pstPsInqTftCnf->astPfInfo[j].bitOpRmtIpv4AddrAndMask;

        if(pstPsInqTftCnf->astPfInfo[j].bitOpRmtIpv4AddrAndMask)
        {
            psttft->astTftInfo[j].stSourceIpaddr.enPdpType = APS_L4A_PDP_IPV4;
            psttft->astTftInfo[j].stSourceIpMask.enPdpType = APS_L4A_PDP_IPV4;
            (VOS_VOID)VOS_MemCpy((VOS_VOID*)(psttft->astTftInfo[j].stSourceIpaddr.aucIpv4Addr),
            (VOS_VOID*)(pstPsInqTftCnf->astPfInfo[j].aucRmtIpv4Address), APP_MAX_IPV4_ADDR_LEN);

            (VOS_VOID)VOS_MemCpy((VOS_VOID*)(psttft->astTftInfo[j].stSourceIpMask.aucIpv4Addr),
            (VOS_VOID*)(pstPsInqTftCnf->astPfInfo[j].aucRmtIpv4Mask), APP_MAX_IPV4_ADDR_LEN);
        }
        if(pstPsInqTftCnf->astPfInfo[j].bitOpRmtIpv6AddrAndMask)
        {
            psttft->astTftInfo[j].stSourceIpaddr.enPdpType = APS_L4A_PDP_IPV6;
            psttft->astTftInfo[j].stSourceIpMask.enPdpType = APS_L4A_PDP_IPV6;
            (VOS_VOID)VOS_MemCpy((VOS_VOID*)(psttft->astTftInfo[j].stSourceIpaddr.aucIpv6Addr),
            (VOS_VOID*)(pstPsInqTftCnf->astPfInfo[j].aucRmtIpv6Address), APP_MAX_IPV6_ADDR_LEN);

            (VOS_VOID)VOS_MemCpy((VOS_VOID*)(psttft->astTftInfo[j].stSourceIpMask.aucIpv6Addr),
            (VOS_VOID*)(pstPsInqTftCnf->astPfInfo[j].aucRmtIpv6Mask), APP_MAX_IPV6_ADDR_LEN);
        }

        if((pstPsInqTftCnf->astPfInfo[j].bitOpRmtIpv4AddrAndMask)&&(pstPsInqTftCnf->astPfInfo[j].bitOpRmtIpv6AddrAndMask))
        {
            psttft->astTftInfo[j].stSourceIpaddr.enPdpType = APS_L4A_PDP_IPV4V6;
            psttft->astTftInfo[j].stSourceIpMask.enPdpType = APS_L4A_PDP_IPV4V6;
        }

        psttft->astTftInfo[j].bitOpProtocolId = pstPsInqTftCnf->astPfInfo[j].bitOpProtocolId;
        psttft->astTftInfo[j].bitOpSpi = pstPsInqTftCnf->astPfInfo[j].bitOpSecuParaIndex;
        psttft->astTftInfo[j].bitOpTosMask = pstPsInqTftCnf->astPfInfo[j].bitOpTypeOfService;
        psttft->astTftInfo[j].bitOpFlowLable = pstPsInqTftCnf->astPfInfo[j].bitOpFlowLabelType;
        psttft->astTftInfo[j].bitOpDirection = 1;

        psttft->astTftInfo[j].ucPacketFilterId = pstPsInqTftCnf->astPfInfo[j].ucPacketFilterId;
        psttft->astTftInfo[j].ucPrecedence = pstPsInqTftCnf->astPfInfo[j].ucPrecedence;

        psttft->astTftInfo[j].ucProtocolId = pstPsInqTftCnf->astPfInfo[j].ucProtocolId;

        if(pstPsInqTftCnf->astPfInfo[j].bitOpLocalPortRange)
        {
            psttft->astTftInfo[j].bitOpDestPortRange = 1;
            psttft->astTftInfo[j].usLowDestPort =pstPsInqTftCnf->astPfInfo[j].usLcPortLowLimit;
            psttft->astTftInfo[j].usHighDestPort = pstPsInqTftCnf->astPfInfo[j].usLcPortHighLimit;
        }
        else if(pstPsInqTftCnf->astPfInfo[j].bitOpSingleLocalPort)
        {
            psttft->astTftInfo[j].bitOpDestPortRange = 1;
            psttft->astTftInfo[j].usLowDestPort =pstPsInqTftCnf->astPfInfo[j].usSingleLcPort;
            psttft->astTftInfo[j].usHighDestPort = pstPsInqTftCnf->astPfInfo[j].usSingleLcPort;
        }
        else
        {
            psttft->astTftInfo[j].bitOpDestPortRange = 0;
        }

        if(pstPsInqTftCnf->astPfInfo[j].bitOpRemotePortRange)
        {
            psttft->astTftInfo[j].bitOpSrcPortRange = 1;
            psttft->astTftInfo[j].usLowSourcePort = pstPsInqTftCnf->astPfInfo[j].usRmtPortLowLimit;
            psttft->astTftInfo[j].usHighSourcePort = pstPsInqTftCnf->astPfInfo[j].usRmtPortHighLimit;
        }
        else if(pstPsInqTftCnf->astPfInfo[j].bitOpSingleRemotePort)
        {
            psttft->astTftInfo[j].bitOpSrcPortRange = 1;
            psttft->astTftInfo[j].usLowSourcePort = pstPsInqTftCnf->astPfInfo[j].usSingleRmtPort;
            psttft->astTftInfo[j].usHighSourcePort = pstPsInqTftCnf->astPfInfo[j].usSingleRmtPort;
        }
        else
        {
            psttft->astTftInfo[j].bitOpSrcPortRange = 0;
        }

        psttft->astTftInfo[j].ulSecuParaIndex = pstPsInqTftCnf->astPfInfo[j].ulSecuParaIndex;
        psttft->astTftInfo[j].ucTypeOfService = pstPsInqTftCnf->astPfInfo[j].ucTypeOfService;
        psttft->astTftInfo[j].ucTypeOfServiceMask = pstPsInqTftCnf->astPfInfo[j].ucTypeOfServiceMask;
        psttft->astTftInfo[j].ulFlowLable = pstPsInqTftCnf->astPfInfo[j].ulFlowLabelType;

        /* AT��NAS��Э���෴*/
        /* (AT:  0-pre rel 7, 1-uplink,   2-downlink, 3-birectional)*/
        /* (NAS: 0-pre rel 7, 1-downlink, 2-uplink,   3-birectional)*/
        if(APP_ESM_TRANSFER_DIRECTION_UPLINK == pstPsInqTftCnf->astPfInfo[j].enDirection)
        {
            psttft->astTftInfo[j].enTftFilterDirection = 1;
        }
        else if(APP_ESM_TRANSFER_DIRECTION_DOWNLINK == pstPsInqTftCnf->astPfInfo[j].enDirection)
        {
            psttft->astTftInfo[j].enTftFilterDirection = 2;
        }
        else
        {
            psttft->astTftInfo[j].enTftFilterDirection = pstPsInqTftCnf->astPfInfo[j].enDirection;
        }

        psttft->astTftInfo[j].bitOpNwPktFilterId = 1;
        psttft->astTftInfo[j].ucNwPktFilterId = pstPsInqTftCnf->astPfInfo[j].ucNwPacketFilterId;
    }

    return ;
}

VOS_UINT32 l4a_FunPsCgtftrdpSetCnf(L4A_PS_MSG_STRU* pData,L4A_FW_MSG_FUN_TABLE_STRU* pstTable,VOS_UINT16 usClientId)
{
    APS_L4A_SET_CGTFTRDP_CNF_STRU *pstCnf = NULL;
    APP_ESM_INQ_DYNAMIC_TFT_CNF_STRU *pstPsInqTftCnf=NULL;
    VOS_UINT32 ulsize;
    VOS_UINT32 ret;
    L4A_RX_INFO_STRU *pNode = NULL;
    L4A_ONLY_CID_COMM_REQ_STRU *pstReq = NULL;

    pNode = l4a_GetExeCmdNode(pstTable->ulAtReqMsgId, L4A_REQ_FLAG);
    if((NULL == pNode) || (NULL == pNode->pData) || (NULL == pData))
    {
        L4A_INFO_LOG("%s %d failed.\n", __FUNCTION__, __LINE__);

        /* �Ҳ�������ڵ㣬��AT/TAF��ʱ���Ʒ���ERROR */
        return ERR_MSP_SUCCESS;
    }

    pstPsInqTftCnf = (APP_ESM_INQ_DYNAMIC_TFT_CNF_STRU *)(pData);
    pstReq = pNode->pData;

    if(0 == pNode->ulCidNum)
    {
        pNode->ulCidNum = l4a_GetValidCidNum(pstReq->aucCid);
        if(0 == pNode->ulCidNum)
        {
            L4A_INFO_LOG("%s %d failed.\n", __FUNCTION__, __LINE__);

            return ERR_MSP_SUCCESS;
        }
        
        L4A_INFO_LOG("%s %d.\n", __FUNCTION__, pNode->ulCidNum); /* [false alarm]: ����Fortify���� */

        ulsize = sizeof(APS_L4A_SET_CGTFTRDP_CNF_STRU) \
            + (pNode->ulCidNum * sizeof(APS_L4A_SDF_PF_TFT_STRU)); /* [false alarm]: ����Fortify���� */

        pstCnf = VOS_MemAlloc(MSP_L4_L4A_PID, DYNAMIC_MEM_PT, ulsize);
        if(NULL == pstCnf)
        {
            /* �����ڴ�ʧ�ܣ���AT/TAF��ʱ���Ʒ���ERROR */
            return ERR_MSP_SUCCESS;
        }

        pNode->pCnfData = pstCnf;

        pstCnf->enMsgId             = pstTable->ulAtCnfMsgId;
        pstCnf->stCtrl.ulPid        = pstPsInqTftCnf->ulOpId;
        pstCnf->stCtrl.ulClientId   = (VOS_UINT32)usClientId;
        pstCnf->ulCidNum            = pNode->ulCidNum;
    }
    else
    {
        if(NULL == pNode->pCnfData)
        {
            L4A_INFO_LOG("%s %d failed.\n", __FUNCTION__, __LINE__);
            
            return ERR_MSP_SUCCESS;
        }
        pstCnf = pNode->pCnfData;
    }

    pstCnf->ulErrorCode = pstPsInqTftCnf->ulRslt;

    /* ����ɹ��ȱ���Ӧ����Ϣ��Ȼ���ж��Ƿ����һ�������cid�����ʧ��ֱ��Ӧ���AT/TAF */
    if(ERR_MSP_SUCCESS == pstCnf->ulErrorCode)
    {
        l4a_FunCgtftrdpPkj(pstPsInqTftCnf, &pstCnf->astPfTftInfo[pNode->ulCidIndex]);

        pNode->ulCidIndex++;
        if(pNode->ulCidIndex != pNode->ulCidNum)
        {
            /* �ٴη������� */
            ret = l4a_FunRDPCidIndexReq((L4A_DATA_MSG_STRU*)pstReq, pstTable->ulPsReqMsgId, pstTable->ulPsReqPid, pNode->ulCidIndex);
            if(ERR_MSP_WAIT_ASYNC == ret)
            {
                L4A_INFO_LOG("%s %d.\n", __FUNCTION__, pNode->ulCidIndex);

                /* �����첽״̬�����õĵط�Ҫ�ж� */
                return ERR_MSP_WAIT_ASYNC;
            }
        }
    }

    ulsize = sizeof(APS_L4A_SET_CGTFTRDP_CNF_STRU) + (pNode->ulCidNum * sizeof(APS_L4A_SDF_PF_TFT_STRU));
    ret = l4aPacket2Aps(pstCnf, ulsize);

    (VOS_VOID)VOS_MemFree(MSP_L4_L4A_PID, pstCnf);

    return ret;
}


VOS_UINT32 l4a_FunCgtftrdpChk(L4A_PS_MSG_STRU* pData, L4A_RX_INFO_STRU* pNode)
{
    L4A_ONLY_CID_COMM_REQ_STRU *pstReq = (L4A_ONLY_CID_COMM_REQ_STRU*)(pNode->pData);
    APP_ESM_INQ_DYNAMIC_TFT_CNF_STRU *pstCnf = (APP_ESM_INQ_DYNAMIC_TFT_CNF_STRU *)(pData);

    L4A_VALID_PID_CHECK(pstReq, pstCnf);
}


VOS_UINT32 l4a_FunPsCgeqosSetReq(L4A_DATA_MSG_STRU* pData,VOS_UINT32 ulPsReqMsgId,VOS_UINT32 ulPsReqPid)
{
    APP_ESM_SET_EPS_QOS_REQ_STRU stReq= {0};
    APS_L4A_SET_CGEQOS_REQ_STRU *pstReq = NULL;

    pstReq = (APS_L4A_SET_CGEQOS_REQ_STRU*)(pData);

    stReq.ulMsgId = ulPsReqMsgId;
    stReq.ulOpId = pstReq->stCtrl.ulPid;
    stReq.ulCid = pstReq->stCgeqosInfo.ucCid ;

    if(0 == pstReq->stCgeqosInfo.bitOpQCI)
    {
        stReq.enSetType = APP_ESM_PARA_DELETE; /* 0:set, 1:del*/
    }
    else
    {
       stReq.enSetType = APP_ESM_PARA_SETTING; /* 0:set, 1:del*/

       /* Э��ջ��AT����Ӧ */
       stReq.stSdfQosInfo.ucQCI = pstReq->stCgeqosInfo.ucValQCI;
       stReq.stSdfQosInfo.ulDLGMaxRate = pstReq->stCgeqosInfo.ulValDLGBR;
       stReq.stSdfQosInfo.ulULGMaxRate = pstReq->stCgeqosInfo.ulValULGBR;
       stReq.stSdfQosInfo.ulDLMaxRate = pstReq->stCgeqosInfo.ulValDLMBR;
       stReq.stSdfQosInfo.ulULMaxRate = pstReq->stCgeqosInfo.ulValULMBR;
    }

    return  l4aPacket2Ps(ulPsReqPid,&stReq, sizeof(APP_ESM_SET_EPS_QOS_REQ_STRU));
}


VOS_UINT32 l4a_FunCgeqosChk(L4A_PS_MSG_STRU* pData, L4A_RX_INFO_STRU* pNode)
{
    APS_L4A_SET_CGEQOS_REQ_STRU *pstReq = (APS_L4A_SET_CGEQOS_REQ_STRU*)(pNode->pData);
    APP_ESM_PARA_SET_CNF_STRU *pstCnf = (APP_ESM_PARA_SET_CNF_STRU *)(pData);

    L4A_VALID_PID_CHECK(pstReq, pstCnf);
}


VOS_UINT32 l4a_FunPsCgeqosrdpSetCnf(L4A_PS_MSG_STRU* pData,L4A_FW_MSG_FUN_TABLE_STRU* pstTable,VOS_UINT16 usClientId)
{
    APS_L4A_SET_CGEQOSRDP_CNF_STRU *pstCnf    = NULL;
    APP_ESM_INQ_DYNAMIC_EPS_QOS_CNF_STRU *pstEsmCnf=NULL;
    VOS_UINT32 ulsize;
    VOS_UINT32 ret;
    L4A_RX_INFO_STRU *pNode = NULL;
    L4A_ONLY_CID_COMM_REQ_STRU *pstReq = NULL;

    pNode = l4a_GetExeCmdNode(pstTable->ulAtReqMsgId, L4A_REQ_FLAG);
    if((NULL == pNode) || (NULL == pNode->pData) || (NULL == pData))
    {
        L4A_INFO_LOG("%s %d failed.\n", __FUNCTION__, __LINE__);

        /* �Ҳ�������ڵ㣬��AT/TAF��ʱ���Ʒ���ERROR */
        return ERR_MSP_SUCCESS;
    }

    pstEsmCnf = (APP_ESM_INQ_DYNAMIC_EPS_QOS_CNF_STRU *)(pData);
    pstReq = pNode->pData;

    if(0 == pNode->ulCidNum)
    {
        pNode->ulCidNum = l4a_GetValidCidNum(pstReq->aucCid);
        if(0 == pNode->ulCidNum)
        {
            L4A_INFO_LOG("%s %d failed.\n", __FUNCTION__, __LINE__);
            
            return ERR_MSP_SUCCESS;
        }
        
        L4A_INFO_LOG("%s %d.\n", __FUNCTION__, pNode->ulCidNum); /* [false alarm]: ����Fortify���� */

        ulsize = sizeof(APS_L4A_SET_CGEQOSRDP_CNF_STRU) \
            + (pNode->ulCidNum * sizeof(APS_L4A_EPS_QOS_EXT_STRU)); /* [false alarm]: ����Fortify���� */

        pstCnf = VOS_MemAlloc(MSP_L4_L4A_PID, DYNAMIC_MEM_PT, ulsize);
        if(NULL == pstCnf)
        {
            /* �����ڴ�ʧ�ܣ���AT/TAF��ʱ���Ʒ���ERROR */
            return ERR_MSP_SUCCESS;
        }

        pNode->pCnfData = pstCnf;

        pstCnf->enMsgId             = pstTable->ulAtCnfMsgId;
        pstCnf->stCtrl.ulPid        = pstEsmCnf->ulOpId;
        pstCnf->stCtrl.ulClientId   = (VOS_UINT32)usClientId;
        pstCnf->ulCidNum            = pNode->ulCidNum;
    }
    else
    {
        if(NULL == pNode->pCnfData)
        {
            L4A_INFO_LOG("%s %d failed.\n", __FUNCTION__, __LINE__);
            
            return ERR_MSP_SUCCESS;
        }
        pstCnf = pNode->pCnfData;
    }

    pstCnf->ulErrorCode = pstEsmCnf->ulRslt;
    
    /* ����ɹ��ȱ���Ӧ����Ϣ��Ȼ���ж��Ƿ����һ�������cid�����ʧ��ֱ��Ӧ���AT/TAF */
    if(ERR_MSP_SUCCESS == pstCnf->ulErrorCode)
    {
        pstCnf->astEpsQosInfo[pNode->ulCidIndex].ucCid   = (VOS_UINT8)pstEsmCnf->ulCid;
        pstCnf->astEpsQosInfo[pNode->ulCidIndex].ucQCI   = pstEsmCnf->stSdfQosInfo.ucQCI;
        pstCnf->astEpsQosInfo[pNode->ulCidIndex].ulDLGBR = pstEsmCnf->stSdfQosInfo.ulDLGMaxRate;
        pstCnf->astEpsQosInfo[pNode->ulCidIndex].ulULGBR = pstEsmCnf->stSdfQosInfo.ulULGMaxRate;
        pstCnf->astEpsQosInfo[pNode->ulCidIndex].ulDLMBR = pstEsmCnf->stSdfQosInfo.ulDLMaxRate;
        pstCnf->astEpsQosInfo[pNode->ulCidIndex].ulULMBR = pstEsmCnf->stSdfQosInfo.ulULMaxRate;
        pstCnf->astEpsQosInfo[pNode->ulCidIndex].bitOpQCI   = 1;
        pstCnf->astEpsQosInfo[pNode->ulCidIndex].bitOpDLGBR = 1;
        pstCnf->astEpsQosInfo[pNode->ulCidIndex].bitOpULGBR = 1;
        pstCnf->astEpsQosInfo[pNode->ulCidIndex].bitOpDLMBR = 1;
        pstCnf->astEpsQosInfo[pNode->ulCidIndex].bitOpULMBR = 1;

        pNode->ulCidIndex++;
        if(pNode->ulCidIndex != pNode->ulCidNum)
        {
            /* �ٴη������� */
            ret = l4a_FunRDPCidIndexReq((L4A_DATA_MSG_STRU*)pstReq, pstTable->ulPsReqMsgId, pstTable->ulPsReqPid, pNode->ulCidIndex);
            if(ERR_MSP_WAIT_ASYNC == ret)
            {
                L4A_INFO_LOG("%s %d.\n", __FUNCTION__, pNode->ulCidIndex);
                
                /* �����첽״̬�����õĵط�Ҫ�ж� */
                return ERR_MSP_WAIT_ASYNC;
            }
        }
    }

    ulsize = sizeof(APS_L4A_SET_CGEQOSRDP_CNF_STRU) + (pNode->ulCidNum * sizeof(APS_L4A_EPS_QOS_EXT_STRU));

    ret = l4aPacket2Aps(pstCnf, ulsize);

    (VOS_VOID)VOS_MemFree(MSP_L4_L4A_PID, pstCnf);

    return ret;
}


VOS_UINT32 l4a_FunCgeqosrdpChk(L4A_PS_MSG_STRU* pData, L4A_RX_INFO_STRU* pNode)
{
    L4A_ONLY_CID_COMM_REQ_STRU *pstReq = (L4A_ONLY_CID_COMM_REQ_STRU*)(pNode->pData);
    APP_ESM_INQ_DYNAMIC_EPS_QOS_CNF_STRU *pstCnf = (APP_ESM_INQ_DYNAMIC_EPS_QOS_CNF_STRU *)(pData);

    L4A_VALID_PID_CHECK(pstReq, pstCnf);
}


VOS_UINT32 l4a_FunPsCgcmodSetReq(L4A_DATA_MSG_STRU* pData,VOS_UINT32 ulPsReqMsgId,VOS_UINT32 ulPsReqPid)
{
    APP_ESM_INQ_PARA_REQ_STRU stReq= {0};
    APS_L4A_SET_CGCMOD_REQ_STRU *pstReq = NULL;

    pstReq = (APS_L4A_SET_CGCMOD_REQ_STRU*)(pData);

    stReq.ulMsgId = ulPsReqMsgId;
    stReq.ulCid = l4a_GetUlValidCidIndex(pstReq->aulCid, 0);
    if(stReq.ulCid == (APS_L4A_LTE_MAX_CID + 1))
    {
        return ERR_MSP_FAILURE;
    }
    return  l4aPacket2Ps(ulPsReqPid, &stReq, sizeof(APP_ESM_INQ_PARA_REQ_STRU));
}

VOS_UINT32 l4a_PktPdpModifyCnf2Aps(L4A_PS_MSG_STRU* pData, VOS_UINT32 ulAtCnfMsgId,VOS_UINT16 usClientId)
{
    APS_L4A_PDP_MODIFY_CNF_STRU stCnf = {0};
    APP_ESM_PDP_MODIFY_CNF_STRU * pstCnf = NULL;

    pstCnf = (APP_ESM_PDP_MODIFY_CNF_STRU*)(pData);

    stCnf.enMsgId         = ulAtCnfMsgId;
    stCnf.usClientId      = usClientId;
    stCnf.bitOpEpsQos     = pstCnf->bitOpSdfQos;
    stCnf.ucCid           = (VOS_UINT8)pstCnf->ulCid;
    stCnf.ulRabId         = pstCnf->ulRabId;

    (VOS_VOID)VOS_MemCpy(&(stCnf.stEpsQosInfo), &(pstCnf->stSdfQosInfo), sizeof(APP_ESM_EPS_QOS_INFO_STRU));

    return l4aPacket2Aps(&stCnf, sizeof(APS_L4A_PDP_MODIFY_CNF_STRU));
}

VOS_UINT32 l4a_PktPdpModifyRej2Aps(L4A_PS_MSG_STRU* pData, VOS_UINT32 ulAtCnfMsgId,VOS_UINT16 usClientId)
{
    APS_L4A_PDP_MODIFY_REJ_STRU stCnf = {0};
    APP_ESM_PDP_MODIFY_CNF_STRU* pstCnf = NULL;

    pstCnf = (APP_ESM_PDP_MODIFY_CNF_STRU*)(pData);

    stCnf.enMsgId         = ulAtCnfMsgId;
    stCnf.usClientId      = usClientId;
    stCnf.ucCid           = (VOS_UINT8)pstCnf->ulCid;
    stCnf.ulEsmCause      = pstCnf->ulRslt;

    return l4aPacket2Aps(&stCnf, sizeof(APS_L4A_PDP_MODIFY_REJ_STRU));
}

VOS_UINT32 l4a_FunPsCgcmodSetCnf(L4A_PS_MSG_STRU* pData,L4A_FW_MSG_FUN_TABLE_STRU* pstTable,VOS_UINT16 usClientId)
{
    APS_L4A_PDP_MODIFY_REJ_STRU stCnf = {0};
    APP_ESM_PDP_MODIFY_CNF_STRU* pstCnf = NULL;
    L4A_RX_INFO_STRU *pNode = NULL;
    APS_L4A_SET_CGCMOD_REQ_STRU *pstReq = NULL;

    if(NULL == pData)
    {
        pNode = l4a_GetExeCmdNode(pstTable->ulAtReqMsgId, L4A_REQ_FLAG);
        if(NULL != pNode)
        {
            pstReq = pNode->pData;
            if(NULL != pstReq)
            {
                stCnf.enMsgId = ID_L4A_APS_PDP_MODIFY_REJ;
                stCnf.usClientId = usClientId;
                stCnf.ucCid = (VOS_UINT8)l4a_GetUlValidCidIndex(pstReq->aulCid, 0);
                stCnf.ulEsmCause = ERR_MSP_TIMEOUT;
                return l4aPacket2Aps(&stCnf, sizeof(APS_L4A_PDP_MODIFY_REJ_STRU));
            }
        }
        
        return ERR_MSP_SUCCESS;
    }

    pstCnf = (APP_ESM_PDP_MODIFY_CNF_STRU *)(pData);
    if (pstCnf->ulRslt == ERR_MSP_SUCCESS)
    {
        return l4a_PktPdpModifyCnf2Aps(pData, ID_L4A_APS_PDP_MODIFY_CNF,usClientId);
    }
    else
    {
        return l4a_PktPdpModifyRej2Aps(pData, ID_L4A_APS_PDP_MODIFY_REJ,usClientId);
    }
}



VOS_UINT32 l4a_FunPsAbortSetReq(L4A_DATA_MSG_STRU* pData,VOS_UINT32 ulPsReqMsgId,VOS_UINT32 ulPsReqPid)
{
    APP_ESM_PROCEDURE_ABORT_NOTIFY_STRU stReq= {0};
    APS_L4A_ABORT_REQ_STRU* pstReq = (APS_L4A_ABORT_REQ_STRU*)(pData);

    stReq.ulMsgId = ulPsReqMsgId;
    stReq.ulCid   = pstReq->ucCid;

    return l4aPacket2PsNoCnf(ulPsReqPid, &stReq, sizeof(APP_ESM_PROCEDURE_ABORT_NOTIFY_STRU));
}

VOS_UINT32 l4a_FunPsIpv6SetReq(L4A_DATA_MSG_STRU* pData,VOS_UINT32 ulPsReqMsgId,VOS_UINT32 ulPsReqPid)
{
    APP_ESM_IPV6_INFO_NOTIFY_STRU stReq = {0};
    APS_L4A_IPV6_INFO_NOTIFY_IND_STRU*  pstReq = (APS_L4A_IPV6_INFO_NOTIFY_IND_STRU*)(pData);

    /* ���stIpv6InfoNotify����*/
    stReq.ulMsgId         = ulPsReqMsgId;
    stReq.ucEpsbId        = pstReq->ucRabId;
    stReq.ucIpv6PrefixNum = pstReq->ucIpv6PrefixNum;
    (VOS_VOID)VOS_MemCpy(stReq.astIpv6PrefixArray, pstReq->astIpv6PrefixArray, \
        APP_ESM_MAX_IPV6_PREFIX_NUM*sizeof(APP_ESM_IPV6_PREFIX_STRU));

    return l4aPacket2PsNoCnf(ulPsReqPid, &stReq, sizeof(APP_ESM_IPV6_INFO_NOTIFY_STRU));
}


VOS_UINT32 l4a_FunIndCfgSetReq(L4A_DATA_MSG_STRU* pData,VOS_UINT32 ulPsReqMsgId,VOS_UINT32 ulPsReqPid)
{
    L4A_IND_CFG_REQ_STRU *pstReq = (L4A_IND_CFG_REQ_STRU*)(pData);
    VOS_UINT32 i;

    if(pstReq->stIndCfg.curc_bit_valid)
    {
        /* ATת���ַ���ʱ�ǰ�����洢�ģ�L4Aת�������� */
        for(i = 0; i < L4A_CURC_RPT_CFG_MAX_SIZE; i++)
        {
            g_aucL4aCurcRptCfg[i] = pstReq->stIndCfg.aucCurcCfgReq[L4A_CURC_RPT_CFG_MAX_SIZE - 1 - i];
        }
    }

    if(pstReq->stIndCfg.anlevel_bit_valid)
    {
        L4A_INFO_LOG("l4a curc set anlevel\n");
        L4A_SetRptCmdStatus(L4A_RPT_CMD_ANLEVEL, pstReq->stIndCfg.anlevel_bit);
    }

    if(pstReq->stIndCfg.rssi_bit_valid)
    {
        L4A_INFO_LOG("l4a curc set rssi\n");
        L4A_SetRptCmdStatus(L4A_RPT_CMD_RSSI, pstReq->stIndCfg.rssi_bit);
    }

    if(pstReq->stIndCfg.lwurc_bit_valid)
    {
        L4A_INFO_LOG("l4a curc set lwurc\n");
        L4A_SetRptCmdStatus(L4A_RPT_CMD_LWURC, pstReq->stIndCfg.lwurc_bit);
    }

    if(pstReq->stIndCfg.mode_bit_valid)
    {
        L4A_INFO_LOG("l4a curc set mode\n");
        L4A_SetRptCmdStatus(L4A_RPT_CMD_MODE, pstReq->stIndCfg.mode_bit);
    }

    if(pstReq->stIndCfg.cerssi_bit_valid)
    {
        L4A_INFO_LOG("l4a curc set cerssi\n");
        L4A_SetRptCmdStatus(L4A_RPT_CMD_CERSSI, pstReq->stIndCfg.cerssi_bit);
    }
    
    if(pstReq->stIndCfg.lcacell_bit_valid)
    {
        L4A_INFO_LOG("l4a curc set lcacellurc\n");
        L4A_SetRptCmdStatus(L4A_RPT_CMD_LCACELLURC, pstReq->stIndCfg.lcacell_bit);
    }

    return ERR_MSP_SUCCESS;
}


VOS_UINT32 l4a_PktManagerInd2Aps(L4A_PS_MSG_STRU* pData)
{
    APS_L4A_PDP_ACTIVATE_IND_STRU stInd = {0};
    APP_ESM_PDP_MANAGER_IND_STRU* pstInd = NULL;

    stInd.enMsgId  = ID_L4A_APS_PDP_ACTIVATE_IND;

    pstInd = (APP_ESM_PDP_MANAGER_IND_STRU*)(pData);

    stInd.ucCid         = (VOS_UINT8)pstInd->ulCid;
    stInd.ucOpId        = (VOS_UINT8)pstInd->ulOpId;
#if 1
    stInd.bitOpLinkCid  = pstInd->bitOpLinkCid;
    stInd.ulLinkCid     = pstInd->ulLinkCid;
#endif
    return l4aPacket2Aps((VOS_VOID*)(&stInd),sizeof(APS_L4A_PDP_ACTIVATE_IND_STRU));
}

VOS_UINT32 l4a_PktSetupInd2Aps(L4A_PS_MSG_STRU* pData)
{
    APS_L4A_PDP_SETUP_IND_STRU stInd = {0};
    APP_ESM_PDP_SETUP_IND_STRU* pstInd  = NULL;

    pstInd = (APP_ESM_PDP_SETUP_IND_STRU*)(pData);

    stInd.enMsgId              = ID_L4A_APS_PDP_SETUP_IND;
    stInd.bitOpEpsQos          = pstInd->bitOpSdfQos;
    stInd.bitOpEsmCause        = 1;
    stInd.bitOpLinkCid         = pstInd->bitOpLinkCid;
    stInd.ucOpId               = (VOS_UINT8)pstInd->ulOpId;
    stInd.ucCid                = (VOS_UINT8)pstInd->ulCid;
    stInd.ulLinkCid            = pstInd->ulLinkCid;
    stInd.ulRabId              = pstInd->ulRabId;
    stInd.ulEsmCause           = pstInd->ulRslt;
    stInd.ulDedicatedBearerFlg = pstInd->enBearerType;

    (VOS_VOID)VOS_MemCpy(&(stInd.stIpAddrInfo), &(pstInd->stPDNAddrInfo), sizeof(APS_L4A_PDP_ADDR_STRU));
    (VOS_VOID)VOS_MemCpy(&(stInd.stEpsQosInfo), &(pstInd->stSdfQosInfo), sizeof(APS_L4A_EPS_QOS_STRU));

    if((1 == pstInd->bitOpDnsPrim) && (APP_ESM_PDN_TYPE_IPV4 == pstInd->stDnsPrimAddrInfo.ucIpType))
    {
        stInd.stDnsAddrInfo.bitOpPrimDnsAddr= 1;
        (VOS_VOID)VOS_MemCpy(stInd.stDnsAddrInfo.aucPrimDnsAddr, pstInd->stDnsPrimAddrInfo.aucIpV4Addr, APP_MAX_IPV4_ADDR_LEN);
    }

    if((1 == pstInd->bitOpDnsPrim) && (APP_ESM_PDN_TYPE_IPV6 == pstInd->stDnsPrimAddrInfo.ucIpType))
    {
        stInd.stIpv6DnsAddrInfo.bitOpPrimDnsAddr = 1;
        (VOS_VOID)VOS_MemCpy(stInd.stIpv6DnsAddrInfo.aucPrimDnsAddr, pstInd->stDnsPrimAddrInfo.aucIpV6Addr, APP_MAX_IPV6_ADDR_LEN);
    }

    if((1 == pstInd->bitOpDnsSec) && (APP_ESM_PDN_TYPE_IPV4 == pstInd->stDnsSecAddrInfo.ucIpType))
    {
        stInd.stDnsAddrInfo.bitOpSecDnsAddr = 1;
        (VOS_VOID)VOS_MemCpy(stInd.stDnsAddrInfo.aucSecDnsAddr, pstInd->stDnsSecAddrInfo.aucIpV4Addr, APP_MAX_IPV4_ADDR_LEN);
    }

    if((1 == pstInd->bitOpDnsSec) && (APP_ESM_PDN_TYPE_IPV6== pstInd->stDnsSecAddrInfo.ucIpType))
    {
        stInd.stIpv6DnsAddrInfo.bitOpSecDnsAddr = 1;
        (VOS_VOID)VOS_MemCpy(stInd.stIpv6DnsAddrInfo.aucSecDnsAddr, pstInd->stDnsSecAddrInfo.aucIpV6Addr, APP_MAX_IPV6_ADDR_LEN);
    }

    /*stPdpActCnf.tNbnsAddrInfo��ʱ���Բ��ṩ*/

    stInd.stGateWayAddrInfo.bitOpGateWayAddr= pstInd->bitOpGateWayAddrInfo;
    (VOS_VOID)VOS_MemCpy(stInd.stGateWayAddrInfo.aucGateWayAddr, pstInd->stGateWayAddrInfo.aucIpV4Addr, 4*sizeof(VOS_UINT8));

    stInd.stPcscfAddrInfo.bitOpPrimPcscfAddr = pstInd->bitOpPCscfPrim;
    stInd.stPcscfAddrInfo.bitOpSecPcscfAddr  = pstInd->bitOpPCscfSec;
    (VOS_VOID)VOS_MemCpy(stInd.stPcscfAddrInfo.aucPrimPcscfAddr, pstInd->stPCscfPrimAddrInfo.aucIpV4Addr, 4*sizeof(VOS_UINT8));
    (VOS_VOID)VOS_MemCpy(stInd.stPcscfAddrInfo.aucSecPcscfAddr, pstInd->stPCscfSecAddrInfo.aucIpV4Addr, 4*sizeof(VOS_UINT8));

    return l4aPacket2Aps((&stInd), sizeof(APS_L4A_PDP_SETUP_IND_STRU));
}

VOS_UINT32 l4a_PktDeactivateInd2Aps(L4A_PS_MSG_STRU* pData)
{
    APS_L4A_PDP_DEACTIVATE_IND_STRU stInd = {0};
    APP_ESM_PDP_RELEASE_IND_STRU* pstInd = NULL;

    pstInd = (APP_ESM_PDP_RELEASE_CNF_STRU*)(pData);

    stInd.bitOpLinkCid = pstInd->bitOpLinkCid;
    stInd.enMsgId = ID_L4A_APS_PDP_DEACTIVATE_IND;
    stInd.ucCid = (VOS_UINT8)pstInd->ulCid;
    stInd.ucOpId = (VOS_UINT8)pstInd->ulOpId;
    stInd.ulEsmCause = pstInd->ulRslt;
    stInd.ulLinkCid = pstInd->ulLinkCid;
    stInd.stIpAddrInfo.enPdpType = pstInd->stPDNAddrInfo.ucIpType;
    stInd.ulEpsbId = pstInd->ulEpsbId;

    (VOS_VOID)VOS_MemCpy(stInd.stIpAddrInfo.aucIpv4Addr, pstInd->stPDNAddrInfo.aucIpV4Addr, APP_MAX_IPV4_ADDR_LEN*sizeof(VOS_UINT8));
    (VOS_VOID)VOS_MemCpy(stInd.stIpAddrInfo.aucIpv6Addr, pstInd->stPDNAddrInfo.aucIpV6Addr, APP_MAX_IPV6_ADDR_LEN*sizeof(VOS_UINT8));

    return l4aPacket2Aps((VOS_VOID*)(&stInd), sizeof(APS_L4A_PDP_DEACTIVATE_IND_STRU));
}

VOS_UINT32 l4a_PktPdpModifyInd2Aps(L4A_PS_MSG_STRU* pData)
{
    APP_ESM_PDP_MODIFY_IND_STRU * pstInd        = NULL;
    APS_L4A_PDP_MODIFY_IND_STRU stInd = {0};

    pstInd = (APP_ESM_PDP_MODIFY_IND_STRU *)pData;

    stInd.bitOpEpsQos = pstInd->bitOpSdfQos;
    stInd.enMsgId      = ID_L4A_APS_PDP_MODIFY_IND;
    stInd.ucCid    = (VOS_UINT8)pstInd->ulCid;
    stInd.ulRabId      = pstInd->ulRabId;

    stInd.ucOpId       = (VOS_UINT8)pstInd->ulOpId;

    (VOS_VOID)VOS_MemCpy(&(stInd.stEpsQosInfo), &(pstInd->stSdfQosInfo), sizeof(APP_ESM_EPS_QOS_INFO_STRU));
    return l4aPacket2Aps((VOS_VOID*)(&stInd), sizeof(APS_L4A_PDP_MODIFY_IND_STRU));
}


VOS_UINT32 l4a_FunCsqInd(L4A_PS_MSG_STRU* pData)
{
    RRC_APP_CSQ_IND_STRU *pstPsCsqInd = NULL;
    L4A_CSQ_INFO_IND_STRU stCsqInd = {0};
    VOS_UINT32 ret = ERR_MSP_SUCCESS;

    pstPsCsqInd = (RRC_APP_CSQ_IND_STRU *)(pData);

    /*Э��ջ�����ֵ��8������*/
    stCsqInd.sRssi = ((99 == pstPsCsqInd->sRssi)?99:pstPsCsqInd->sRssi/8);
    stCsqInd.sRsrp = ((99 == pstPsCsqInd->sRsrp)?99:pstPsCsqInd->sRsrp/8);
    stCsqInd.sRsrq = ((99 == pstPsCsqInd->sRsrq)?99:pstPsCsqInd->sRsrq/8);

    stCsqInd.lSINR      = pstPsCsqInd->lSINR;
    stCsqInd.stCQI.usRI       = pstPsCsqInd->stCQI.usRI;
    stCsqInd.stCQI.ausCQI[0]   = pstPsCsqInd->stCQI.ausCQI[0];
    stCsqInd.stCQI.ausCQI[1]   = pstPsCsqInd->stCQI.ausCQI[1];

    if(VOS_TRUE == L4A_GetRptCmdStatus(L4A_RPT_CMD_RSSI))
    {
        stCsqInd.enMsgId = ID_MSG_L4A_RSSI_IND;
        ret |= l4aPacket2At(&stCsqInd, sizeof(L4A_CSQ_INFO_IND_STRU));
    }
    if(VOS_TRUE == L4A_GetRptCmdStatus(L4A_RPT_CMD_CERSSI))
    {
        stCsqInd.enMsgId = ID_MSG_L4A_CERSSI_IND;
        ret |= l4aPacket2At(&stCsqInd, sizeof(L4A_CSQ_INFO_IND_STRU));
    }
    if(VOS_TRUE == L4A_GetRptCmdStatus(L4A_RPT_CMD_ANLEVEL))
    {
        stCsqInd.enMsgId = ID_MSG_L4A_ANLEVEL_IND;
        ret |= l4aPacket2At(&stCsqInd, sizeof(L4A_CSQ_INFO_IND_STRU));
    }
    return ret;
}


VOS_UINT32 L4aPktSdfInfo(APS_L4A_SDF_PARA_STRU* pstSdfParaInfo,APP_ESM_SDF_PARA_STRU* pstSdfPara)
{
    VOS_UINT32 i = 0;
    
    if((NULL == pstSdfParaInfo) || (NULL == pstSdfPara))
    {
        return ERR_MSP_FAILURE;
    }

    pstSdfPara->bitOpPdnType             = pstSdfParaInfo->bitOpPdnType;
    pstSdfPara->bitOpApn                 = pstSdfParaInfo->bitOpApn;
    pstSdfPara->bitOpSdfQos              = pstSdfParaInfo->bitOpSdfQos;
    pstSdfPara->bitOpLinkdCId            = pstSdfParaInfo->bitOpLinkdCId;
    pstSdfPara->bitIpv4AddrAllocType     = pstSdfParaInfo->bitIpv4AddrAllocType;
    pstSdfPara->bitOpGwAuthInfo          = pstSdfParaInfo->bitOpGwAuthInfo;
    pstSdfPara->bitOpSpare               = pstSdfParaInfo->bitOpSpare;
#if 1
    pstSdfPara->bitOpPcscfDiscovery      = pstSdfParaInfo->bitOpPcscfDiscovery;
    pstSdfPara->bitOpImsCnSignalFlag     = pstSdfParaInfo->bitOpImsCnSignalFlag;
#endif
    pstSdfPara->enPdnType                = pstSdfParaInfo->enPdnType;
    pstSdfPara->enIpv4AddrAllocType      = pstSdfParaInfo->enIpv4AddrAllocType;
    pstSdfPara->ulCId                    = pstSdfParaInfo->ulCid;
    pstSdfPara->ulLinkdCId               = pstSdfParaInfo->ulLinkdCid;
    pstSdfPara->ulPfNum                  = pstSdfParaInfo->ulPfNum;
#if 0
    pstSdfPara->enBearerCntxtType        = pstSdfParaInfo->enBearerCntxtType;
#else
    pstSdfPara->enPcscfDiscovery         = pstSdfParaInfo->enPcscfDiscovery;
    pstSdfPara->enImsCnSignalFlag        = pstSdfParaInfo->enImsCnSignalFlag;

    if((pstSdfParaInfo->bitOpEmergencyInd) && (APS_L4A_PDP_FOR_EMC == pstSdfParaInfo->enEmergencyInd))
    {
        pstSdfPara->enBearerCntxtType    = APP_ESM_BEARER_TYPE_EMERGENCY;
    }
    else
    {
        pstSdfPara->enBearerCntxtType    = pstSdfParaInfo->enBearerCntxtType;
    }
#endif

    (VOS_VOID)VOS_MemCpy(&(pstSdfPara->stSdfQosInfo), &(pstSdfParaInfo->stSdfQosInfo), sizeof(APP_ESM_EPS_QOS_INFO_STRU));
    pstSdfPara->stApnInfo.ucApnLen       = pstSdfParaInfo->stApnInfo.ucApnLen;
    (VOS_VOID)VOS_MemCpy(pstSdfPara->stApnInfo.aucApnName, pstSdfParaInfo->stApnInfo.aucApnName, APP_MAX_APN_LEN);

    /*(VOS_VOID)VOS_MemCpy(&(pstSdfPara->stGwAuthInfo), &(pstSdfParaInfo->stGwAuthInfo), sizeof(APP_ESM_GW_AUTH_INFO_STRU));ע�⣬��������USERNAME���Ȳ�ͬ���д�ȷ��    */
    pstSdfPara->stGwAuthInfo.enGwAuthType = (VOS_UINT8)pstSdfParaInfo->stGwAuthInfo.enGwAuthType;
    pstSdfPara->stGwAuthInfo.ucAccNumLen  = pstSdfParaInfo->stGwAuthInfo.ucAccNumLen;
    pstSdfPara->stGwAuthInfo.ucPwdLen     = pstSdfParaInfo->stGwAuthInfo.ucPwdLen;
    pstSdfPara->stGwAuthInfo.ucUserNameLen= pstSdfParaInfo->stGwAuthInfo.ucUserNameLen;
    (VOS_VOID)VOS_MemCpy(pstSdfPara->stGwAuthInfo.auAccessNum, pstSdfParaInfo->stGwAuthInfo.auAccessNum, APP_ESM_MAX_ACCESS_NUM_LEN);
    (VOS_VOID)VOS_MemCpy(pstSdfPara->stGwAuthInfo.aucUserName, pstSdfParaInfo->stGwAuthInfo.aucUserName, APP_ESM_MAX_USER_NAME_LEN);
    (VOS_VOID)VOS_MemCpy(pstSdfPara->stGwAuthInfo.aucPwd, pstSdfParaInfo->stGwAuthInfo.aucPwd, APP_ESM_MAX_PASSWORD_LEN);

    for(i = 0; i < pstSdfParaInfo->ulPfNum; i++)
    {
        (VOS_VOID)VOS_MemCpy(pstSdfPara->astCntxtTftInfo + i, pstSdfParaInfo->astCntxtTftInfo + i, sizeof(APP_ESM_TFT_INFO_STRU));
/*
        if((1 == pstSdfParaInfo->astCntxtTftInfo[i].OP_SourceIpAddr) && (1 == pstSdfParaInfo->astCntxtTftInfo[i].OP_SourceIpMask))
        {
            pstSdfPara->astCntxtTftInfo[i].bitOpRmtIpv4AddrAndMask = 1;
        }

        if((1 == pstSdfParaInfo->astCntxtTftInfo[i].OP_SourceIpv6Addr) && (1 == pstSdfParaInfo->astCntxtTftInfo[i].OP_SourceIpv6Mask))
        {
            pstSdfPara->astCntxtTftInfo[i].bitOpRmtIpv6AddrAndMask = 1;
        }

        if((1 == pstSdfParaInfo->astCntxtTftInfo[i].OP_HighDestPort) && (1 == pstSdfParaInfo->astCntxtTftInfo[i].OP_LowDestPort))
        {
            pstSdfPara->astCntxtTftInfo[i].bitOpRemotePortRange = 1;
        }

        if((1 == pstSdfParaInfo->astCntxtTftInfo[i].OP_HighSourcePort) && (1 == pstSdfParaInfo->astCntxtTftInfo[i].OP_LowSourcePort))
        {
            pstSdfPara->astCntxtTftInfo[i].bitOpLocalPortRange = 1;
        }

        pstSdfPara->astCntxtTftInfo[i].bitOpProtocolId          = pstSdfParaInfo->astCntxtTftInfo[i].OP_ProtocolId;
        
        pstSdfPara->astCntxtTftInfo[i].bitOpSecuParaIndex       = pstSdfParaInfo->astCntxtTftInfo[i].OP_ulSecuParaIndex;
        pstSdfPara->astCntxtTftInfo[i].bitOpTypeOfService       = pstSdfParaInfo->astCntxtTftInfo[i].OP_ucTypeOfService;

        pstSdfPara->astCntxtTftInfo[i].ucPacketFilterId         = pstSdfParaInfo->astCntxtTftInfo[i].ucPacketFilterId;
        pstSdfPara->astCntxtTftInfo[i].ucNwPacketFilterId       = pstSdfParaInfo->astCntxtTftInfo[i].ucNwPacketFilterId;
        pstSdfPara->astCntxtTftInfo[i].enDirection              = pstSdfParaInfo->astCntxtTftInfo[i].enDirection;
        pstSdfPara->astCntxtTftInfo[i].ucPrecedence             = pstSdfParaInfo->astCntxtTftInfo[i].ucPrecedence;
        pstSdfPara->astCntxtTftInfo[i].ulSecuParaIndex          = pstSdfParaInfo->astCntxtTftInfo[i].ulSecuParaIndex;

        pstSdfPara->astCntxtTftInfo[i].usLcPortHighLimit        = pstSdfParaInfo->astCntxtTftInfo[i].usHighSourcePort;
        pstSdfPara->astCntxtTftInfo[i].usLcPortLowLimit         = pstSdfParaInfo->astCntxtTftInfo[i].usLowSourcePort;
        
        if(pstSdfParaInfo->astCntxtTftInfo[i].usHighSourcePort == pstSdfParaInfo->astCntxtTftInfo[i].usLowSourcePort)
        {
            pstSdfPara->astCntxtTftInfo[i].bitOpSingleLocalPort = 1;
            pstSdfPara->astCntxtTftInfo[i].usSingleLcPort   = pstSdfParaInfo->astCntxtTftInfo[i].usHighSourcePort;
        }

        pstSdfPara->astCntxtTftInfo[i].usRmtPortHighLimit   = pstSdfParaInfo->astCntxtTftInfo[i].usHighDestPort;
        pstSdfPara->astCntxtTftInfo[i].usRmtPortLowLimit    = pstSdfParaInfo->astCntxtTftInfo[i].usLowDestPort;

        if(pstSdfParaInfo->astCntxtTftInfo[i].usHighDestPort == pstSdfParaInfo->astCntxtTftInfo[i].usLowDestPort)
        {
            pstSdfPara->astCntxtTftInfo[i].bitOpSingleRemotePort = 1;
            pstSdfPara->astCntxtTftInfo[i].usSingleRmtPort = pstSdfParaInfo->astCntxtTftInfo[i].usHighDestPort;
        }

        pstSdfPara->astCntxtTftInfo[i].ucProtocolId             = pstSdfParaInfo->astCntxtTftInfo[i].OP_ProtocolId;
        pstSdfPara->astCntxtTftInfo[i].ucTypeOfService          = pstSdfParaInfo->astCntxtTftInfo[i].ucTypeOfService;
        pstSdfPara->astCntxtTftInfo[i].ucTypeOfServiceMask      = pstSdfParaInfo->astCntxtTftInfo[i].ucTypeOfServiceMask;

        VOS_MemCpy(pstSdfPara->astCntxtTftInfo[i].aucRmtIpv4Address, pstSdfParaInfo->astCntxtTftInfo[i].aucSourceIpAddr + 1, pstSdfParaInfo->astCntxtTftInfo[i].aucSourceIpAddr[0]);
        VOS_MemCpy(pstSdfPara->astCntxtTftInfo[i].aucRmtIpv4Mask, pstSdfParaInfo->astCntxtTftInfo[i].aucSourceIpMask + 1, pstSdfParaInfo->astCntxtTftInfo[i].aucSourceIpMask[0]);
        VOS_MemCpy(pstSdfPara->astCntxtTftInfo[i].aucRmtIpv6Address, pstSdfParaInfo->astCntxtTftInfo[i].aucRmtIpv6Address + 1, pstSdfParaInfo->astCntxtTftInfo[i].aucRmtIpv6Address[0]);
        VOS_MemCpy(pstSdfPara->astCntxtTftInfo[i].aucRmtIpv6Mask, pstSdfParaInfo->astCntxtTftInfo[i].aucRmtIpv6Mask + 1, pstSdfParaInfo->astCntxtTftInfo[i].aucRmtIpv6Mask[0]);

        pstSdfPara->astCntxtTftInfo[i].ulFlowLabelType          = pstSdfParaInfo->astCntxtTftInfo[i].ulFlowLableType;
*/
    }

    return ERR_MSP_SUCCESS;
}

VOS_UINT32 APP_GetSdfPara(VOS_UINT32 *pulSdfNum,APP_ESM_SDF_PARA_STRU *pstSdfPara)
{
    VOS_UINT32 ret = APP_FAILURE;
    VOS_UINT8 ucCid = 0;
    APS_L4A_SDF_PARA_STRU* pstSdfParaInfo = NULL;

    if((NULL == pulSdfNum)||(NULL == pstSdfPara))
    {
        return APP_FAILURE;
    }

    pstSdfParaInfo =
        (APS_L4A_SDF_PARA_STRU*)VOS_MemAlloc(MSP_L4_L4A_PID, DYNAMIC_MEM_PT, sizeof(APS_L4A_SDF_PARA_STRU));

    if(NULL == pstSdfParaInfo)
    {
        return APP_FAILURE;
    }

    (VOS_VOID)VOS_MemSet((VOS_VOID*)pstSdfParaInfo, 0, sizeof(APS_L4A_SDF_PARA_STRU));

    ucCid = (VOS_UINT8)(pstSdfPara->ulCId);
    
    ret = TAF_APS_GetCidSdfParaInfo(ucCid,pstSdfParaInfo);

    if(VOS_ERR == ret)
    {
        ret = APP_FAILURE;
    }
    else
    {
        (VOS_VOID)L4aPktSdfInfo(pstSdfParaInfo,pstSdfPara);

        *pulSdfNum = 1;
        ret        = APP_SUCCESS;
    }

    (VOS_VOID)VOS_MemFree(MSP_L4_L4A_PID, pstSdfParaInfo);

    return ret;
}

VOS_UINT32 APP_GetPdpManageInfo(APP_ESM_PDP_MANAGE_INFO_STRU *pstPdpManageInfo)
{
    VOS_UINT32 ret = APP_FAILURE;

    APS_L4A_PDP_MANAGE_INFO_STRU* pstApsPdpMngInfo = NULL;

    if(NULL == pstPdpManageInfo)
    {
        return APP_FAILURE;
    }
    
    pstApsPdpMngInfo = 
        (APS_L4A_PDP_MANAGE_INFO_STRU*)VOS_MemAlloc(MSP_L4_L4A_PID, DYNAMIC_MEM_PT, sizeof(APS_L4A_PDP_MANAGE_INFO_STRU));

    if(NULL == pstApsPdpMngInfo)
    {
        return APP_FAILURE;
    }
    
    ret = TAF_APS_GetPdpManageInfo(pstApsPdpMngInfo);

    if(VOS_ERR == ret)
    {
        (VOS_VOID)VOS_MemFree(MSP_L4_L4A_PID, pstApsPdpMngInfo);
        return APP_FAILURE;
    }

    pstPdpManageInfo->enMode = (APP_ESM_BEARER_MANAGE_MODE_ENUM_UINT8)pstApsPdpMngInfo->enMode;
    pstPdpManageInfo->enType = (APP_ESM_BEARER_MANAGE_TYPE_ENUM_UINT8)pstApsPdpMngInfo->enType;

    (VOS_VOID)VOS_MemFree(MSP_L4_L4A_PID, pstApsPdpMngInfo);

    return APP_SUCCESS;
}

/*****************************************************************************
 �� �� ��  : APP_GetCidImsSuppFlag
 ��������  : ��ȡCID��Ӧ��IMS����
 �������  : ucCid                      - CID
 �������  : pucImsSuppFlag             - CID֧��IMS����
 �� �� ֵ  : APP_FAILURE                - ����ִ���쳣
             APP_SUCCESS                - ����ִ�гɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��1��
    ��    ��   : z00301431
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 APP_GetCidImsSuppFlag(VOS_UINT8 ucCid ,VOS_UINT8 *pucImsSuppFlag)
{
    if(NULL == pucImsSuppFlag)
    {
        return APP_FAILURE;
    }

    *pucImsSuppFlag = TAF_APS_GetCidImsCfgFlag(ucCid);

    return APP_SUCCESS;
}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



