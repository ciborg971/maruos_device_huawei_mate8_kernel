



/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "ppp_inc.h"
#include "pppc_ctrl.h"



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define         THIS_FILE_ID            PS_FILE_ID_PPPC_SHEL_C

/* PPPC�����ݶ���ͳ����Ϣ�ṹ�� */
extern PPP_DATA_Q_STAT_STRU             g_stPppcDataQueueStats;

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*lint -save -e958 */

ULONG PPP_USMStartVsncp(UCHAR *pucVsncpMsg, ULONG ulRpIndex)
{
    ULONG ulLen = 0;
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;
    UCHAR *pHead = VOS_NULL_PTR;
    UCHAR *pPacket = VOS_NULL_PTR;

    GETPPPINFOPTRBYRP(pstPppInfo, ulRpIndex);
    if (VOS_NULL_PTR == pstPppInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_774);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                     "\r\n PPP_USMStartVsncp: User %d isn't exist!", ulRpIndex);
        return VOS_ERR;
    }

    ulLen = *((ULONG *)pucVsncpMsg);
    pHead = pucVsncpMsg + sizeof(ULONG);
    pPacket = pucVsncpMsg + sizeof(ULONG) + PPP_RESERVED_PACKET_HEADER;

    PPP_VSNCP_PactketProc(pstPppInfo, pHead, pPacket, ulLen, CONFREQ);
    PPP_DBG_OK_CNT(PPP_PHOK_1472);

    return VOS_OK;
}


ULONG PPP_USMNotifyRelease(PPP_A11MSG_S *pstA11Msg)
{
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;

    GETPPPINFOPTRBYRP(pstPppInfo, pstA11Msg->ulRPIndex);

    PPP_DBG_OK_CNT(PPP_PHOK_1292);
    if (VOS_NULL_PTR != pstPppInfo)
    {
        pstPppInfo->bFailFlag = PPPA11DOWNNOLCPTER;
    }

    (VOID)PPP_Shell_ISLIoCtl(pstA11Msg->ulRPIndex, PPP_ISLDOWN, (CHAR *)&pstA11Msg->ulL2tpType);

    return VOS_OK;
}



VOID PPP_IpcpTimeOutProcForPdn(ULONG ulRpIndex)
{
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;

    GETPPPINFOPTRBYRP(pstPppInfo, ulRpIndex);
    if (VOS_NULL_PTR == pstPppInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_567);
        return;
    }

    if (0 == SOFTPARA_BIT1383)
    {
        A11_ReqNumSubProc(pstPppInfo);
    }

    SNMP_SetFailReason(pstPppInfo, FSM_ALARM_IPCP_MS_NO_RSP);

    return;
}


VOID PPP_UpdatePcfInfo(ULONG ulRpIndex, ULONG ulPcfIp, USHORT usPcfIndex)
{
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;

    GETPPPINFOPTRBYRP(pstPppInfo, ulRpIndex);
    if (pstPppInfo == VOS_NULL_PTR)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_568);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n PPP_UpdatePcfInfo: User %d isn't exist!", ulRpIndex);
        return;
    }

    pstPppInfo->ulPcfIP = ulPcfIp;
    pstPppInfo->usPcfIndex = usPcfIndex;
    PPP_DBG_OK_CNT(PPP_PHOK_1293);

    return;
}

/*****************************************************************************
 �� �� ��  : PPP_StartIPV4CP
 ��������  :
             ���û��PPP���ƿ飬����ʧ��
             �����PPP���ƿ飬û��IPCP���ƿ飬��Ҫ�ж��Ƿ�����Э�̣����򱣴��ַ�����򷵻�ʧ��
             �����IPCP���ƿ飬�򱣴��ַ������IPCPЭ��
             ȡ�����ƿ��л�����Ϣ������IPCP Request ��Ϣ��Ȼ�����յ������е�IPCP Request ��Ϣ

 �������  : ULONG ulRpIdx
             ULONG ulIpAddr
             ULONG ulPriDns
             ULONG ulSecDns
 �������  : ��
 �� �� ֵ  : ULONG
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��30��
    ��    ��   : luofang
    �޸�����   : �����ɺ���

*****************************************************************************/
ULONG PPP_StartIPV4CP(ULONG ulRpIdx, ULONG ulIpAddr, ULONG ulPriDns, ULONG ulSecDns)
{
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;
    PPPIPCPINFO_S *pstIpcpInfo = VOS_NULL_PTR;
    UCHAR *pHead = VOS_NULL_PTR;
    UCHAR *pPacket = VOS_NULL_PTR;
    ULONG ulMsgLen = 0;

    GETPPPINFOPTRBYRP(pstPppInfo, ulRpIdx);
    if (pstPppInfo == VOS_NULL_PTR)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_569);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n PPP_StartIPV4CP: User %d isn't exist!", ulRpIdx);
        return VOS_ERR;
    }

    if (0 != pstPppInfo->ulPeerIPAddr)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_570);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n PPP_StartIPV4CP: User IP is exist!");
        return VOS_ERR;
    }

    /* �����ַ*/
    pstPppInfo->ulPeerIPAddr = ulIpAddr;
    pstPppInfo->ulDNSAddr1 = ulPriDns;
    pstPppInfo->ulDNSAddr2 = ulSecDns;
    pstPppInfo->ucIpCapability |= PDSN_PPP_IPTYE_IPV4;

    /* ��Э�̣�ֱ�ӱ����ַ �˴���Э�̱�ǿ��Ʋ�ס ʹ��Э�̽׶ο��� */
    if ((USHORT)PPP_PHASE_NETWORK != pstPppInfo->usPhase)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1294);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG, "\r\n PPP_StartIPV4CP: Renego!");
        return VOS_OK;
    }

    /* û���ƿ� */
    if (VOS_NULL_PTR == pstPppInfo->pstIpcpInfo)
    {
        /* ���򴴽����ƿ飬����Э�� */
        PPP_GETIPCPADDR(pstPppInfo->pstIpcpInfo, pstPppInfo->ulRPIndex);
        if (VOS_NULL_PTR == pstPppInfo->pstIpcpInfo)
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_571);
            PPP_DebugOut(MID_PPPC,PPP_DEBUG_LOG, " \r\n PPP_StartIPV4CP: malloc ipcp CB fail!");
            return VOS_ERR;
        }
        PPP_MemSet(pstPppInfo->pstIpcpInfo, 0, sizeof(PPPIPCPINFO_S));

        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n PPP_StartIPV4CP: active ipcp negoation !");
    }

    /* �п��ƿ� */
    pstIpcpInfo = (PPPIPCPINFO_S*)pstPppInfo->pstIpcpInfo;

    /* �ж��Ƿ���ҪЭ��VJѹ�� */
    /*lint -e746*/
    if(VOS_OK == PPP_CheckVjLimit())
    /*lint +e746*/
    {
        pstPppInfo->pstConfigInfo->bEnableVJComp = 1;
    }
    else
    {
        pstPppInfo->pstConfigInfo->bEnableVJComp = 0;
    }

    /* ��ʼ��IPCP���ƿ� ȡ��IPCP���ƿ������ݣ��ȷ�Request��Ϣ */
    PPP_IPCP_Init(pstPppInfo, pstPppInfo->ulIPAddr, pstPppInfo->ulPeerIPAddr);
    /* ��IPCP������Ϣ,����IPCP��ʼЭ�� */
    PPP_IPCP_ReceiveEventFromCore(pstPppInfo->pstIpcpInfo, (ULONG)PPP_EVENT_FSM_OPEN, VOS_NULL_PTR );
    PPP_IPCP_ReceiveEventFromCore(pstPppInfo->pstIpcpInfo, (ULONG)PPP_EVENT_FSM_UP, VOS_NULL_PTR );

    /* ��������Ϣ*/
    if (VOS_NULL_PTR != pstIpcpInfo->pucIpv4cpMsg)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1295);
        pHead    = pstIpcpInfo->pucIpv4cpMsg;
        pPacket  = pstIpcpInfo->pucIpv4cpMsg + PPP_RESERVED_PACKET_HEADER;
        ulMsgLen = pstIpcpInfo->ulIpv4cpLen;

        /* �յ��ն˷����ļ�Ȩ���� */
        PPP_IPCP_ReceivePacket(pstPppInfo->pstIpcpInfo, pHead, pPacket, ulMsgLen);
        (VOID)PPP_Free(pstIpcpInfo->pucIpv4cpMsg);
        pstIpcpInfo->pucIpv4cpMsg = VOS_NULL_PTR;
        pstIpcpInfo->ulIpv4cpLen = 0;
    }

    PPP_DBG_OK_CNT(PPP_PHOK_1296);
    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n PPP_StartIPV4CP: Done!");
    return VOS_OK;
}
/*****************************************************************************
 �� �� ��  : PPP_StartIPV6CP
 ��������  :
          ���û��PPP���ƿ飬����ʧ��
          �����PPP���ƿ飬û��IPCP���ƿ飬��Ҫ�ж��Ƿ�����Э�̣����򱣴��ַ�����򷵻�ʧ��
          �����IPCP���ƿ飬�򱣴��ַ������IPCPЭ��
          ȡ�����ƿ��л�����Ϣ������IPCP Request ��Ϣ��Ȼ�����յ������е�IPCP Request ��Ϣ

 �������  : ULONG ulRpIdx
             UCHAR* szIpV6Addr
             UCHAR* szPriDns
             UCHAR* szSecDns
 �������  : ��
 �� �� ֵ  : ULONG
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��30��
    ��    ��   : luofang
    �޸�����   : �����ɺ���

*****************************************************************************/
ULONG PPP_StartIPV6CP(ULONG ulRpIdx, UCHAR* szIpV6Addr, UCHAR* szPriDns, UCHAR* szSecDns)
{
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;
    PPPIPV6CPINFO_S *pstIpV6CpInfo = VOS_NULL_PTR;
    UCHAR *pHead = VOS_NULL_PTR;
    UCHAR *pPacket = VOS_NULL_PTR;
    ULONG ulMsgLen = 0;

    GETPPPINFOPTRBYRP(pstPppInfo, ulRpIdx);
    if (pstPppInfo == VOS_NULL_PTR)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_572);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n PPP_StartIPV6CP: User %d isn't exist!", ulRpIdx);
        return VOS_ERR;
    }

    if (VOS_OK == PPP_ipv6_addr_check(pstPppInfo->usPeerIPv6Addr))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_573);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n PPP_StartIPV6CP: User IP is exist!");
        return VOS_ERR;
    }

    /* �����ַ */
    VOS_MemCpy(pstPppInfo->usPeerIPv6Addr, szIpV6Addr, PDN_IPV6ADDR_LEN);
    pstPppInfo->ucIpCapability |= PDSN_PPP_IPTYE_IPV6;

    /* ��Э�̣�ֱ�ӱ����ַ �˴���Э�̱�ǿ��Ʋ�ס ʹ��Э�̽׶ο��� */
    if ((USHORT)PPP_PHASE_NETWORK != pstPppInfo->usPhase)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1297);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG, "\r\n PPP_StartIPV6CP: Renego!");
        return VOS_OK;
    }

    /* û�п��ƿ� */
    if (VOS_NULL_PTR == pstPppInfo->pstIpV6cpInfo)
    {
        /* ���򴴽����ƿ飬����Э�� */
        PPP_GETIPV6CPADDR(pstPppInfo->pstIpV6cpInfo, pstPppInfo->ulRPIndex);
        if (VOS_NULL_PTR == pstPppInfo->pstIpV6cpInfo)
        {
            PPP_DBG_OK_CNT(PPP_PHOK_1298);
            PPP_DebugOut(MID_PPPC,PPP_DEBUG_LOG, " \r\n PPP_StartIPV6CP: malloc ipcp CB fail!");
            return VOS_ERR;
        }
        PPP_MemSet(pstPppInfo->pstIpV6cpInfo, 0, sizeof(PPPIPV6CPINFO_S));

        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n PPP_StartIPV6CP: IPV6CP CB is VOS_NULL_PTR!");
    }

    pstIpV6CpInfo = (PPPIPV6CPINFO_S*)pstPppInfo->pstIpV6cpInfo;

    /* ��ʼ��IPV6CP���ƿ� ȡ��IPV6CP���ƿ������ݣ��ȷ�Request��Ϣ��Ȼ���յ� */
    PPP_IPV6CP_Init(pstPppInfo, pstPppInfo->usIpv6Addr, pstPppInfo->usPeerIPv6Addr);

    /* ��IPCP������Ϣ,����IPCP��ʼЭ�� */
    PPP_IPV6CP_ReceiveEventFromCore(pstPppInfo->pstIpV6cpInfo, (ULONG)PPP_EVENT_FSM_OPEN, VOS_NULL_PTR );
    PPP_IPV6CP_ReceiveEventFromCore(pstPppInfo->pstIpV6cpInfo, (ULONG)PPP_EVENT_FSM_UP, VOS_NULL_PTR );

    /* ��������Ϣ*/
    if (pstIpV6CpInfo->pucIpv6cpMsg)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1299);
        pHead    = pstIpV6CpInfo->pucIpv6cpMsg;
        pPacket  = pstIpV6CpInfo->pucIpv6cpMsg + PPP_RESERVED_PACKET_HEADER;
        ulMsgLen = pstIpV6CpInfo->ulIpv6cpLen;

        /* �յ��ն˷����ļ�Ȩ���� */
        PPP_IPV6CP_Pactket_Proc(pstPppInfo, pHead, pPacket, ulMsgLen);

        (VOID)PPP_Free(pstIpV6CpInfo->pucIpv6cpMsg);
        pstIpV6CpInfo->pucIpv6cpMsg = VOS_NULL_PTR;
        pstIpV6CpInfo->ulIpv6cpLen = 0;
    }
    PPP_DBG_OK_CNT(PPP_PHOK_1300);

    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n PPP_StartIPV6CP: Done!");
    return VOS_OK;

}

/*****************************************************************************
 �� �� ��  : PPP_StopIPV4CP
 ��������  : PDN֪ͨPPP��ջɾ��IPV4
 �������  : ULONG ulRpIndex
 �������  : ��
 �� �� ֵ  : ULONG
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��12��
    ��    ��   : luofang
    �޸�����   : �����ɺ���

*****************************************************************************/
ULONG PPP_StopIPV4CP(ULONG ulRpIndex)
{
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;
    PPPIPCPINFO_S *pstIpcpInfo = VOS_NULL_PTR ;
    UCHAR *pHead = VOS_NULL_PTR;
    UCHAR *pPacket = VOS_NULL_PTR;
    ULONG ulMsgLen = 0;

    GETPPPINFOPTRBYRP(pstPppInfo, ulRpIndex);
    if (pstPppInfo == VOS_NULL_PTR)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_574);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n PPP_StopIPV4CP: User %d isn't exist!", ulRpIndex);
        return VOS_ERR;
    }
    pstPppInfo->bIpcpNoToPDN= VOS_TRUE;   /* 1ʱ��֪ͨPDN */
    pstIpcpInfo = (PPPIPCPINFO_S *)pstPppInfo->pstIpcpInfo;
    pstPppInfo->ucIpCapability &= ~PDSN_PPP_IPTYE_IPV4;

    /* ����ipcp term��Ϣ���ipv4��· */
    if (PPP_STATE_SUCCESS == pstPppInfo->bPppStateFlg)
    {
        PPP_IPCP_NegotiationDown(pstPppInfo->pstIpcpInfo);
        PPP_DBG_OK_CNT(PPP_PHOK_1301);
    }
    else
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1302);
        if ((VOS_NULL_PTR != pstIpcpInfo)
            && (PPP_STATE_INITIAL == pstIpcpInfo->stFsm.ucState)
            && (VOS_NULL_PTR != pstIpcpInfo->pucIpv4cpMsg))
        {
            PPP_DBG_OK_CNT(PPP_PHOK_1303);
            /* �����INIT״̬��˵�����ڵȴ�PDN�����ַ�����ʧ������Ҫ��LCP Protol Reject */
            pHead    = pstIpcpInfo->pucIpv4cpMsg;
            pPacket  = pstIpcpInfo->pucIpv4cpMsg + PPP_RESERVED_PACKET_HEADER;
            ulMsgLen = pstIpcpInfo->ulIpv4cpLen;

            PPP_Core_ReceiveUnknownProtocol(pstPppInfo, pHead, pPacket, ulMsgLen, PPP_IPCP, CONFREQ);

            (VOID)PPP_Free(pstIpcpInfo->pucIpv4cpMsg);
            pstIpcpInfo->pucIpv4cpMsg = VOS_NULL_PTR;
            pstIpcpInfo->ulIpv4cpLen = 0;
        }
        PPP_Core_IpcpV4FinProc(pstPppInfo);
    }

    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n PPP_StopIPV4CP Done!");
    return VOS_OK;
}
ULONG PPP_ReleaseIPV4CP(ULONG ulRpIndex)
{
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;

    GETPPPINFOPTRBYRP(pstPppInfo, ulRpIndex);
    if (pstPppInfo == VOS_NULL_PTR)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_575);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n PPP_StopIPV4CP: User %d isn't exist!", ulRpIndex);
        return VOS_ERR;
    }
    pstPppInfo->bIpcpNoToPDN= VOS_TRUE;   /* 1ʱ��֪ͨPDN */
    pstPppInfo->ucIpCapability &= ~PDSN_PPP_IPTYE_IPV4;

    PPP_Core_IpcpV4FinProc(pstPppInfo);
    PPP_DBG_OK_CNT(PPP_PHOK_1304);

    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n PPP_StopIPV4CP Done!");
    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : PPP_StopIPV6CP
 ��������  : PDN֪ͨPPP��ջɾ��IPV6
 �������  : ULONG ulRpIndex
 �������  : ��
 �� �� ֵ  : ULONG
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��12��
    ��    ��   : luofang
    �޸�����   : �����ɺ���

*****************************************************************************/
ULONG PPP_StopIPV6CP(ULONG ulRpIndex)
{
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;
    PPPIPV6CPINFO_S *pstIpv6cpInfo = VOS_NULL_PTR ;
    UCHAR *pHead = VOS_NULL_PTR;
    UCHAR *pPacket = VOS_NULL_PTR;
    ULONG ulMsgLen = 0;

    GETPPPINFOPTRBYRP(pstPppInfo, ulRpIndex);
    if (pstPppInfo == VOS_NULL_PTR)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_576);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n PPP_StopIPV6CP: User %d isn't exist!", ulRpIndex);
        return VOS_ERR;
    }

    pstPppInfo->bIpv6cpNoToPDN= VOS_TRUE;   /* 1ʱ��֪ͨPDN */
    pstIpv6cpInfo = (PPPIPV6CPINFO_S *)pstPppInfo->pstIpV6cpInfo;
    pstPppInfo->ucIpCapability &= ~PDSN_PPP_IPTYE_IPV6;

    /*����ֻ��ipv6����open ״̬��ipv6cp term��Ϣ���ipv6��·�� ����ֱ��ɾ��ipv6cp��Դ��*/
    if (PPP_STATE_SUCCESS == pstPppInfo->bPppStateFlgV6)
    {
        PPP_IPV6CP_NegotiationDown(pstPppInfo->pstIpV6cpInfo);
        PPP_DBG_OK_CNT(PPP_PHOK_1305);
    }
    else
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1306);
        if ((VOS_NULL_PTR != pstIpv6cpInfo)
            && (PPP_STATE_INITIAL == pstIpv6cpInfo->stFsm.ucState)
            && (VOS_NULL_PTR != pstIpv6cpInfo->pucIpv6cpMsg))
        {
            PPP_DBG_OK_CNT(PPP_PHOK_1307);
            /* �����INIT״̬��˵�����ڵȴ�PDN�����ַ�����ʧ������Ҫ��LCP Protol Reject */
            pHead    = pstIpv6cpInfo->pucIpv6cpMsg;
            pPacket  = pstIpv6cpInfo->pucIpv6cpMsg + PPP_RESERVED_PACKET_HEADER;
            ulMsgLen = pstIpv6cpInfo->ulIpv6cpLen;

            PPP_Core_ReceiveUnknownProtocol(pstPppInfo, pHead, pPacket, ulMsgLen, PPP_IPV6CP, CONFREQ);

            (VOID)PPP_Free(pstIpv6cpInfo->pucIpv6cpMsg);
            pstIpv6cpInfo->pucIpv6cpMsg = VOS_NULL_PTR;
            pstIpv6cpInfo->ulIpv6cpLen = 0;
        }

        PPP_Core_IpcpV6FinProc(pstPppInfo);
    }

    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n PPP_StopIPV6CP Done!");
    return VOS_OK;
}
ULONG PPP_ReleaseIPV6CP(ULONG ulRpIndex)
{
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;

    GETPPPINFOPTRBYRP(pstPppInfo, ulRpIndex);
    if (pstPppInfo == VOS_NULL_PTR)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_577);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n PPP_StopIPV6CP: User %d isn't exist!", ulRpIndex);
        return VOS_ERR;
    }

    pstPppInfo->bIpv6cpNoToPDN= VOS_TRUE;   /* 1ʱ��֪ͨPDN */
    pstPppInfo->ucIpCapability &= ~PDSN_PPP_IPTYE_IPV6;

    PPP_Core_IpcpV6FinProc(pstPppInfo);
    PPP_DBG_OK_CNT(PPP_PHOK_1308);

    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n PPP_StopIPV6CP Done!");
    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : PPP_NotifyIpv6SendRA
 ��������  : ppp֪ͨipv6����ra��Ϣ
 �������  : ULONG ulRpIndex
 �������  : ��
 �� �� ֵ  : ULONG
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��04��13��
    ��    ��   : luofang
    �޸�����   : �����ɺ���

*****************************************************************************/
ULONG PPP_NotifyIpv6SendRA(ULONG ulRpIndex, UCHAR ucPDNId)
{
    ULONG ulResult = 0;
    ULONG ulPdnIndex = 0;
    SDB_PDSN_RP_CONTEXT_S *pstRpContext = VOS_NULL_PTR;
    PDN_CONTEXT_S *pstPdnContext = VOS_NULL_PTR;

    /*��ȡrp������*/
    ulResult = (ULONG)SDB_GetRpContextByIndex(ulRpIndex, (VOID**)&pstRpContext);
    if ((SDB_SUCCESS != ulResult) || (VOS_NULL_PTR == pstRpContext))
    {
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "\r\n PPP_NotifyIpv6SendRA: User %u isn't exist!", ulRpIndex);
        PPP_DBG_ERR_CNT(PPP_PHERR_578);
        return VOS_ERR;
    }

    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                 "\r\n PPP_NotifyIpv6SendRA: ucPDNId[%u]!", ucPDNId);
    if (VOS_NULL_BYTE == ucPDNId)
    {
        ucPDNId = 0;
    }
    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                 "\r\n PPP_NotifyIpv6SendRA1: ucPDNId[%u]!", ucPDNId);
    if (ucPDNId >= A11_MAX_PDN_NUM)
    {
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "\r\n PPP_NotifyIpv6SendRA: ucPDNId %u isn't valid!", ucPDNId);
        PPP_DBG_ERR_CNT(PPP_PHERR_579);
        return VOS_ERR;
    }

    ulPdnIndex = (ULONG)pstRpContext->ausPdnIndexArray[ucPDNId];

    /*��ȡPDN������*/
    ulResult = (ULONG)SDB_GetPdnContextByIndex(ulPdnIndex, (VOID**)&pstPdnContext);
    if ((SDB_SUCCESS != ulResult) || (VOS_NULL_PTR == pstPdnContext))
    {
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "\r\n PPP_NotifyIpv6SendRA: PDN %u isn't exist!", ulPdnIndex);
        PPP_DBG_ERR_CNT(PPP_PHERR_580);
        return VOS_ERR;
    }

    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                 "\r\n PPP_NotifyIpv6SendRA: ulPdnIndex[%u]bIpV6Used[%u]ulIpv6Timer[%u]!",
                 ulPdnIndex,pstPdnContext->bIpV6Used,pstPdnContext->ulIpv6Timer);

    if (pstPdnContext->bIpV6Used)
    {
        if (0 != pstPdnContext->ulIpv6Timer)
        {
            /* ֹͣIPv6��ʱ�������ٷ���RA��Ϣ */
            ulResult = IPV6_StopTimer(pstPdnContext->ulIpv6Timer);
            if (VOS_OK != ulResult)
            {
                /* ���ӵ�����Ϣ�������˳� */
                PPP_DBG_ERR_CNT(PPP_PHERR_581);
            }
        }

        pstPdnContext->ucIpv6RouteMsgNum = 0;

        /* ֪ͨIPv6����RA��Ϣ */
        ulResult = Ipv6_A11NotifySendRa(pstPdnContext->ulPdnIndex);
        if (VOS_OK != ulResult)
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_582);
            PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                         "\r\n PPP_NotifyIpv6SendRA: Ipv6_A11NotifySendRa fail pdnindex[%u]!",
                         ulResult,pstPdnContext->ulPdnIndex);
            return VOS_ERR;
        }
        PPP_DBG_OK_CNT(PPP_PHOK_1309);
    }

    return VOS_OK;
}


/*****************************************************************************
 �� �� ��  : PPP_SendFakeIPV4CPReqMsg
 ��������  : PDN��ʱ��PPP�ṩ��PDN���÷���Config Req��Ϣ
 �������  : ULONG ulRpIndex
 �������  : ��
 �� �� ֵ  : ULONG
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��13��
    ��    ��   : luofang
    �޸�����   : �����ɺ���

*****************************************************************************/
ULONG PPP_SendFakeIPV4CPReqMsg(ULONG ulRpIndex)
{
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;
    PPPIPCPINFO_S *pstIpcpInfo = VOS_NULL_PTR;
    PPPFSM_S *pstFsm = VOS_NULL_PTR;

    /* ��ȡPPP���ƿ� */
    GETPPPINFOPTRBYRP(pstPppInfo, ulRpIndex);
    if (pstPppInfo == VOS_NULL_PTR)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_583);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n PPP_SendFakeIPV4CPReqMsg: User %d isn't exist!", ulRpIndex);
        return VOS_ERR;
    }

    if (PPP_PHASE_NETWORK != pstPppInfo->usPhase)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_584);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n PPP_SendFakeIPV4CPReqMsg: Wrong phase! usPhase = %u", pstPppInfo->usPhase);
        return VOS_ERR;
    }

    /* ��ȡIPCP���ƿ� */
    pstIpcpInfo = pstPppInfo->pstIpcpInfo;
    if (VOS_NULL_PTR == pstIpcpInfo)
    {
        PPP_GETIPCPADDR(pstIpcpInfo, pstPppInfo->ulRPIndex);
        if (VOS_NULL_PTR == pstIpcpInfo)
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_585);
            /* Malloc Error */
            PPP_Debug_CoreEvent(pstPppInfo, PPP_LOG_ERROR, "PPP_SendFakeIPV4CPReqMsg Malloc IPCP CB Err!!");
            return VOS_ERR;
        }
        pstPppInfo->pstIpcpInfo = pstIpcpInfo;
    }

    PPP_MemSet((void *)pstIpcpInfo, 0, sizeof(PPPIPCPINFO_S));

    /* �ж��Ƿ���ҪЭ��VJѹ�� */
    /*lint -e746*/
    if(VOS_OK == PPP_CheckVjLimit())
    /*lint +e746*/
    {
        pstPppInfo->pstConfigInfo->bEnableVJComp = 1;
    }
    else
    {
        pstPppInfo->pstConfigInfo->bEnableVJComp = 0;
    }

    PPP_IPCP_Init(pstPppInfo, pstPppInfo->ulIPAddr, pstPppInfo->ulPeerIPAddr);

    pstFsm = (PPPFSM_S*)&(pstIpcpInfo->stFsm);
    (*pstFsm->pstCallBacks->resetci)(pstFsm);

    /* ���첢���ͱ��� */
    PPP_FSM_SendConfigReq(pstFsm);

    /* ���IPCP���ƿ� */
    PPP_ClearCB_IPCP(pstIpcpInfo);
    pstPppInfo->pstIpcpInfo = VOS_NULL_PTR;


    PPP_DBG_OK_CNT(PPP_PHOK_1310);
    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n PPP_SendFakeIPV4CPReqMsg Done !");
    return VOS_OK;

}

/*****************************************************************************
 �� �� ��  : PPP_SendFakeIPV6CPReqMsg
 ��������  : PDN��ʱ��PPP�ṩ��PDN���÷���Config Req��Ϣ
 �������  : ULONG ulRpIndex
 �������  : ��
 �� �� ֵ  : ULONG
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��13��
    ��    ��   : luofang
    �޸�����   : �����ɺ���

*****************************************************************************/
ULONG PPP_SendFakeIPV6CPReqMsg(ULONG ulRpIndex)
{
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;
    PPPIPV6CPINFO_S *pstIpV6cpInfo = VOS_NULL_PTR;
    PPPFSM_S *pstFsm = VOS_NULL_PTR;

    /* ��ȡPPP���ƿ� */
    GETPPPINFOPTRBYRP(pstPppInfo, ulRpIndex);
    if (pstPppInfo == VOS_NULL_PTR)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_585);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n PPP_SendFakeIPV6CPReqMsg: User %d isn't exist!", ulRpIndex);
        return VOS_ERR;
    }

    if (PPP_PHASE_NETWORK != pstPppInfo->usPhase)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_586);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n PPP_SendFakeIPV6CPReqMsg: Wrong phase! usPhase = %u", pstPppInfo->usPhase);
        return VOS_ERR;
    }

    /* ��ȡIPV6CP���ƿ� */
    pstIpV6cpInfo = pstPppInfo->pstIpV6cpInfo;
    if (VOS_NULL_PTR == pstIpV6cpInfo)
    {
        PPP_GETIPV6CPADDR(pstIpV6cpInfo, pstPppInfo->ulRPIndex);
        if (VOS_NULL_PTR == pstIpV6cpInfo)
        {
            PPP_DBG_OK_CNT(PPP_PHOK_1311);
            PPP_Debug_CoreEvent(pstPppInfo, PPP_LOG_ERROR, "\r\nPPP_SendFakeIPV6CPReqMsg Malloc IPv6CP CB Err!!");
            return VOS_ERR;
        }
        pstPppInfo->pstIpV6cpInfo = pstIpV6cpInfo;
    }
    PPP_MemSet((void *)pstIpV6cpInfo, 0, sizeof(PPPIPV6CPINFO_S));

    PPP_IPV6CP_Init(pstPppInfo, pstPppInfo->usIpv6Addr, pstPppInfo->usPeerIPv6Addr);

    pstFsm = (PPPFSM_S*)&(pstIpV6cpInfo->stFsm);
    (*pstFsm->pstCallBacks->resetci)(pstFsm);

    /* ���첢���ͱ��� */
    PPP_FSM_SendConfigReq(pstFsm);

    /* ���IPV6CP���ƿ� */
    PPP_ClearCB_IPV6CP(pstIpV6cpInfo);
    pstPppInfo->pstIpV6cpInfo = VOS_NULL_PTR;

    PPP_DBG_OK_CNT(PPP_PHOK_1312);
    PPP_DebugOut(MID_PPPC,PPP_DEBUG_INFO,"\r\n PPP_SendFakeIPV6CPReqMsg Done!");
    return VOS_OK;
}


/*****************************************************************************
 �� �� ��  : PPP_Shell_ReceiveLcpUpFromCore
 ��������  : PPP����յ�LCP_UP�¼�
 �������  : PPPINFO_S *pstPppInfo
 �������  : ��
 �� �� ֵ  : ULONG
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��30��
    ��    ��   : luofang
    �޸�����   : �����ɺ���

*****************************************************************************/
ULONG PPP_Shell_ReceiveLcpUpFromCore(PPPINFO_S *pstPppInfo)
{
    PPPLCPINFO_S *pstLcpInfo = VOS_NULL_PTR;

    if ( VOS_NULL_PTR == pstPppInfo)
    {
        PPP_DebugOut(MID_PPPC,PPP_DEBUG_INFO,"\r\n PPP_Shell_ReceiveLcpUpFromCore Input para null! ");
        return VOS_ERR;
    }

    pstLcpInfo = (PPPLCPINFO_S*)(pstPppInfo->pstLcpInfo);

    if ( VOS_NULL_PTR == pstLcpInfo)
    {
        PPP_DebugOut(MID_PPPC,PPP_DEBUG_INFO,"\r\nPPP_Shell_ReceiveLcpUpFromCore para null");
        return VOS_ERR;
    }

    if (VOS_OK != PPP_SendUserInfo(pstPppInfo, LCP_INFOR))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_587);
        return VOS_ERR;
    }
    PPP_DBG_OK_CNT(PPP_PHOK_1313);

    /* ����ͳ��:LCPЭ�̳ɹ����� */
    PPP_PerfInc(&g_stPppPerfStatistic.ulLcpSuccess, PERF_TYPE_PPPC_LCP_NEGO_SUCC_NUM, pstPppInfo->bEhrpdUser);
    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                  "\r\n [ppp]PPP_Shell_ReceiveLcpUpFromCore: LcpSuccess: %d",
                  g_stPppPerfStatistic.ulLcpSuccess);
    return VOS_OK;
}


/*****************************************************************************
 �� �� ��  : PPP_Shell_ReceiveLcpDownFromCore
 ��������  : PPP����յ�LCP_DOWN�¼�
 �������  : PPPINFO_S *pstPppInfo
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��30��
    ��    ��   : luofang
    �޸�����   : �����ɺ���

*****************************************************************************/
VOID PPP_Shell_ReceiveLcpDownFromCore(PPPINFO_S *pstPppInfo)
{
    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                  "\r\n [ppp]PPP_Shell_ReceiveLcpDownFromCore: Enter pstPppInfo->bFailFlag=%d", pstPppInfo->bFailFlag);

    if (PPPLOWEDOWN != pstPppInfo->bFailFlag)
    {

        PPP_DBG_OK_CNT(PPP_PHOK_1314);

        if (LAPRECYCLE == pstPppInfo->bFailFlag)
        {
            PPP_DBG_OK_CNT(PPP_PHOK_1315);
            PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                          "\r\n [ppp]PPP_Shell_ReceiveLcpDownFromCore: LAPRECYCLE");
            A11_PPP_TermTag(pstPppInfo->ulRPIndex, LAPRECYCLE);
        }
        else if (PPPFADOWN == pstPppInfo->bFailFlag)
        {
            PPP_DBG_OK_CNT(PPP_PHOK_1316);
            PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                          "\r\n [ppp]PPP_Shell_ReceiveLcpDownFromCore: PPPFADOWN");
            A11_PPP_TermTag(pstPppInfo->ulRPIndex, PPPFADOWN);
        }
        else
        {
            PPP_DBG_OK_CNT(PPP_PHOK_1317);
            A11_PPP_TermTag(pstPppInfo->ulRPIndex, PPP_Negotiation_Fail);
        }

        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n [ppp]PPP_Shell_ReceiveLcpDownFromCore: Notify lower release user %u", pstPppInfo->ulRPIndex);
    }

    /* �������һ�� */
    if (PPP_CB_STATE_USED == g_astPppPool[pstPppInfo->ulRPIndex].usState)
    {
        PPP_INNER_COUNTER(PPP_INNER_COUTNER_015);
        PPP_DBG_OK_CNT(PPP_PHOK_1318);
        (VOID)PPP_DeleteCB(pstPppInfo);
    }

    PPP_DebugOut(MID_PPPC,PPP_DEBUG_INFO,"\r\n PPP_Shell_ReceiveLcpDownFromCore Done!");
    return;
}


/*****************************************************************************
 �� �� ��  : PPP_Shell_IpcpUpNoIp
 ��������  : IPCPЭ����ɺ��û�ûЭ��ip
 �������  : PPPINFO_S *pstPppInfo
 �������  : ��
 �� �� ֵ  : ULONG
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��22��
    ��    ��   : luofang
    �޸�����   : �����ɺ���

*****************************************************************************/
ULONG PPP_Shell_IpcpUpNoIp(PPPINFO_S *pstPppInfo)
{
    if(VOS_NULL_PTR == pstPppInfo)
    {
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n PPP_Shell_IpcpUpNoIp Input is null!");
        return VOS_ERR;
    }

    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n [ppp]PPP_Shell_IpcpUpNoIp: Enter pstPppInfo->bIPTech %u pstPppInfo->ulPeerIPAddr %u",
                  pstPppInfo->bIPTech, pstPppInfo->ulPeerIPAddr);

    /* ��CMip�û���ɾ����ջ */

    /*���ipv4��ַ��IPV4�汾����*/
    PPP_DBG_OK_CNT(PPP_PHOK_1319);
    pstPppInfo->ucIpCapability &= ~PDSN_PPP_IPTYE_IPV4;
    PPP_IPCP_NegotiationDown(pstPppInfo->pstIpcpInfo);

    return VOS_OK;
}



/*****************************************************************************
 �� �� ��  : PPP_Shell_IpcpUpNegotiateIp
 ��������  :  PPP�Ĵ���IpcpUpNegotiateIp�¼��ĺ���
 �������  : PPPINFO_S *pstPppInfo
             PPPLCPINFO_S *pstLcpInfo
 �������  : ��
 �� �� ֵ  : ULONG
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��12��
    ��    ��   : luofang
    �޸�����   : �����ɺ���

*****************************************************************************/
ULONG PPP_Shell_IpcpUpNegotiateIp(PPPINFO_S *pstPppInfo, PPPLCPINFO_S *pstLcpInfo)
{

    PPP_DebugOut(MID_PPPC,PPP_DEBUG_INFO, "\r\n [ppp]PPP_Shell_IpcpUpNegotiateIp: Enter pstPppInfo->bIPTech %u pstPppInfo->ulPeerIPAddr %u",
                  pstPppInfo->bIPTech, pstPppInfo->ulPeerIPAddr);

    PPP_INNER_COUNTER(PPP_INNER_COUTNER_018);

    /* �����˼�Ȩ��û�м�Ȩ */
    if (PPP_USERTYPE_NOCMIP_NOAAA(pstLcpInfo,pstPppInfo))
    {
        HSGW_EmsTraceByRpIndex(pstPppInfo->ulRPIndex, HSGW_EMS_MODULE_PPP, EMS_PPP_10);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                      "\r\n [ppp]PPP_Shell_IpcpUpNegotiateIp: is sip no auth: %u",
                      pstPppInfo->ulRPIndex);
        /*����֤����PPPЭ�̳ɹ�*/
        PPP_SNMP_PERF_SET_SUCCESS(pstPppInfo);

        PPP_SET_REL_CODE(pstPppInfo, AM_RELCODE_PPP_IPCP_NEGONAK);
        PPP_LCP_NegotiationDown(pstPppInfo->pstLcpInfo);

        /* ��IPCP�ɹ�֮������֤�û�PDSN��ȥ����û� ����Ự������������1 */
        A11_ReqNumSubProc(pstPppInfo);
        PPP_PerfInc(&g_stPppPerfStatistic.ulIpcpSuccess, PERF_TYPE_PPPC_IPCP_NEGO_SUCC_NUM, pstPppInfo->bEhrpdUser);


        PPP_DBG_ERR_CNT(PPP_PHERR_588);

        PPP_ERROR_COUNTER(PPP_ERROR_COUNTER019);
        return VOS_ERR;
    }
    PPP_DebugOut(MID_PPPC,PPP_DEBUG_INFO,"\r\n PPP_Shell_IpcpUpNegotiateIp Done!");
    return VOS_OK;
}
ULONG PPP_Shell_IpcpSuccessProc(PPPINFO_S *pstPppInfo)
{
    ULONG64 ulNegoTime = 0;
    PDN_PPP_NCP_UP_S stNcpUpInfo = { 0 };
    VOS_UINT32 ulRet;


    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n [ppp]PPP_Shell_IpcpSuccessProc: Enter");
#if 0
    if (VOS_OK != PDN_CheckIsCmipCanRun(pstPppInfo->ulRPIndex, 0))
    {
         PPP_DebugOut(MID_PPPC, PDSN_DBGLVL_INFO,
                   "\r\n [ppp]PPP_Shell_IpcpSuccessProc: dea cmip user for bit1493 is openl !");
        PPP_SET_REL_CODE(pstPppInfo, AM_RELCODE_DEA_CMIP_FOR_BIT1493);
        PPP_LCP_NegotiationDown(pstPppInfo->pstLcpInfo);
        return VOS_ERR;
    }
#endif
    /*lint -e63*/
    stNcpUpInfo.ulIpv4Addr = pstPppInfo->ulPeerIPAddr;
    /*lint +e63*/


    PPP_INNER_COUNTER(PPP_INNER_COUTNER_016);
    /* ɾ��Э�̶�ʱ�� */
    (VOID)PPP_NodeDelete(pstPppInfo->ulRPIndex);


    if (pstPppInfo->bReNego)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1320);
        pstPppInfo->bReNego = 0;
        if (pstPppInfo->pstPppRenegoInfo)
        {
            (VOID)PPP_Free(pstPppInfo->pstPppRenegoInfo);
            pstPppInfo->pstPppRenegoInfo = 0;
        }
    }


    PPP_SNMP_PERF_SET_SUCCESS(pstPppInfo);

    /* ����ͳ��:IPCPЭ�̳ɹ����� */
    PPP_PerfInc(&g_stPppPerfStatistic.ulIpcpSuccess, PERF_TYPE_PPPC_IPCP_NEGO_SUCC_NUM, pstPppInfo->bEhrpdUser);
    PPP_DBG_OK_CNT(PPP_PHOK_1321);

    /* ��̬���ӱ���óɹ� */
    pstPppInfo->bPppStateFlg = PPP_STATE_SUCCESS;

    /* PPP��·�����ɹ� */
    pstPppInfo->bPppSuccess = 1;

    if(0 == pstPppInfo->ulNegoEndTime)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1322);
        pstPppInfo->ulNegoEndTime = VOS_GetTick();
        ulNegoTime = pstPppInfo->ulNegoEndTime - pstPppInfo->ulNegoStartTime;
        (VOID)PerfSetFamPerfCounterByAddress(&(g_stPppPerfStatistic.ulPppNegoTotalTime), PPP_PERF_ADD, (ULONG)ulNegoTime);
        PPP_PerfInc(&g_stPppPerfStatistic.ulPppNegoNum, PERF_TYPE_PPPC_PPP_NEGO_NUM, pstPppInfo->bEhrpdUser);
    }

    /* ��ʱ����,��¼�ı������ */

    if (pstPppInfo->bReNego)
    {
        pstPppInfo->bReNego = 0;
        if (pstPppInfo->pstPppRenegoInfo)
        {
            (VOID)PPP_Free(pstPppInfo->pstPppRenegoInfo);
            pstPppInfo->pstPppRenegoInfo = 0;
        }
    }

    if (VOS_NULL_PTR != pstPppInfo->pstLcpInfo)
    {
        ((PPPLCPINFO_S*)pstPppInfo->pstLcpInfo)->bReqSendAck = VOS_FALSE;
    }

    /* �ͷ�L2TP���ƿ� */
    if (pstPppInfo->pL2tpPara != VOS_NULL_PTR)
    {
        (VOID)PPP_Free(pstPppInfo->pL2tpPara);
        pstPppInfo->pL2tpPara = VOS_NULL_PTR;
    }

    if (VOS_OK != PPP_SendUserInfo(pstPppInfo, IPCP_INFOR))
    {
        PPP_DebugOut(MID_PPPC, PDSN_DBGLVL_INFO,
                   "\r\n [ppp]PPP_Shell_IpcpSuccessProc: PPP_SendUserInfo fail !");
        PPP_SET_REL_CODE(pstPppInfo, AM_RELCODE_PPP_IPCP_NEGONAK);
        PPP_LCP_NegotiationDown(pstPppInfo->pstLcpInfo);
        PPP_ERROR_COUNTER(PPP_ERROR_COUNTER013);
        PPP_DBG_ERR_CNT(PPP_PHERR_590);
        return VOS_ERR;
    }

    ulRet = PPP_StopNegoTimer();
    if (VOS_OK != ulRet)
    {
        PPPC_WARNING_LOG1("stop nego timer fail!\r\n", ulRet);
    }

    /* IPCP�ɹ�ʱ���� */
    PPPC_IsReadyToRespActCmd(pstPppInfo);

    return VOS_OK;
}
ULONG PPP_Shell_ReceiveIpcpUpFromCore(PPPINFO_S *pstPppInfo)
{
    ULONG ulRet = VOS_OK;
    PPPIPCPINFO_S *pstIpcpInfo = VOS_NULL_PTR;
    PPPLCPINFO_S *pstLcpInfo = VOS_NULL_PTR;
    UCHAR ucAnotherDmpu = 0;
    UCHAR ucDmpuId = 0;
    UCHAR ucDpeId = 0;

    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n [ppp]PPP_Shell_ReceiveIpcpUpFromCore: Enter");

    pstIpcpInfo = (PPPIPCPINFO_S *)pstPppInfo->pstIpcpInfo;
    pstLcpInfo = (PPPLCPINFO_S *)pstPppInfo->pstLcpInfo;


    if(pstIpcpInfo->stGotOptions.neg_vj)
    {
        /* ѡ���ӿ����ӿ���DPEID */
        if (MAX_DMPU_ID <= pstPppInfo->ucDmpuId)
        {
            ulRet = (ULONG)PPP_CompSelectDmpuDpe(&ucDmpuId, &ucDpeId);
            if (VOS_OK != ulRet)
            {
                HSGW_EmsTraceByRpIndex(pstPppInfo->ulRPIndex, HSGW_EMS_MODULE_PPP, EMS_PPP_11);
                /* �ӿ�����λ�����û���Ҳ�Ѿ��ﵽ���ޣ������� */
                PPP_DBG_ERR_CNT(PPP_PHERR_591);
                PPP_SET_REL_CODE(pstPppInfo, AM_RELCODE_PPP_IPCP_NEGONAK);
                PPP_LCP_NegotiationDown(pstPppInfo->pstLcpInfo);  /*�ͷ���·*/
                return VOS_ERR;
            }

            ulRet = (ULONG)PPP_CompCheckVjUserNum(&ucDmpuId);
            if(VOS_OK != ulRet)
            {
                PPP_DBG_ERR_CNT(PPP_PHERR_592);
                PPP_SET_REL_CODE(pstPppInfo, AM_RELCODE_PPP_IPCP_NEGONAK);
                PPP_LCP_NegotiationDown(pstPppInfo->pstLcpInfo);  /*�ͷ���·*/
                return VOS_ERR;
            }

            pstPppInfo->ucDmpuId = ucDmpuId;
            pstPppInfo->ucDpeId  = ucDpeId;
        }

        if((VOS_FALSE == pstPppInfo->bVjFlag) && (VOS_TRUE == pstPppInfo->bMppcFlag))
        {
            PPP_DBG_OK_CNT(PPP_PHOK_1323);
        }
        /* END of liushuang*/
        PPP_CompUserNumAdd(pstPppInfo, PPP_USERSTAT_VJ);
        PPP_INNER_COUNTER(PPP_INNER_COUTNER_064);
    }


    /*Э����IP��ַ*/
    ulRet = PPP_Shell_IpcpUpNegotiateIp(pstPppInfo, pstLcpInfo);
    if (VOS_ERR == ulRet)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_593);
        return VOS_ERR;
    }

    PPP_DBG_OK_CNT(PPP_PHOK_1324);
    return PPP_Shell_IpcpSuccessProc(pstPppInfo);
}


/*****************************************************************************
 �� �� ��  : PPP_Shell_IpV6cpUpNoIp
 ��������  : IPV6CPЭ����ɺ��û�û��Э��IP
 �������  : PPPINFO_S *pstPppInfo
 �������  : ��
 �� �� ֵ  : ULONG
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��22��
    ��    ��   : luofang
    �޸�����   : �����ɺ���

*****************************************************************************/
ULONG PPP_Shell_IpV6cpUpNoIp( PPPINFO_S *pstPppInfo )
{

    if(VOS_NULL_PTR == pstPppInfo)
    {
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n PPP_Shell_IpcpUpNoIp Input is null!");
        return VOS_ERR;
    }

    /* IPV6CPЭ��û��Э���û�IP��ֱ��֪ͨPDNɾ����ջ����֧��CMIPV6 */

    /*���ipv6��ַ��IPV6�汾����*/
    PPP_DBG_OK_CNT(PPP_PHOK_1325);
    pstPppInfo->ucIpCapability &= ~PDSN_PPP_IPTYE_IPV6;
    PPP_IPV6CP_NegotiationDown(pstPppInfo->pstIpV6cpInfo);

    return VOS_OK;
}



/*****************************************************************************
 �� �� ��  : PPP_Shell_IpV6cpUpNegotiateIp
 ��������  : ipv6cp�׶�Э����ip��sip����up������
 �������  : PPPINFO_S *pstPppInfo
 �������  : ��
 �� �� ֵ  : ULONG
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��12��
    ��    ��   : luofang
    �޸�����   : �����ɺ���

*****************************************************************************/
ULONG PPP_Shell_IpV6cpUpNegotiateIp( PPPINFO_S *pstPppInfo )
{
    PPPLCPINFO_S *pstLcpInfo = VOS_NULL_PTR;

    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                 "\r\n PPP_Shell_Ipv6cpUpNegotiateIp: ipcp up (negotiate ip) addr:%02x:%02x:%02x:%02x",
                 pstPppInfo->usPeerIPv6Addr[0],pstPppInfo->usPeerIPv6Addr[1],pstPppInfo->usPeerIPv6Addr[2],pstPppInfo->usPeerIPv6Addr[3]);

    pstLcpInfo = (PPPLCPINFO_S*)pstPppInfo->pstLcpInfo;
    if ( VOS_NULL_PTR == pstLcpInfo )
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_594);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n PPP_Shell_IpV6cpUpNegotiateIp: lcp cb is null");
        return VOS_ERR;
    }

    /* �����˼�Ȩ��û�м�Ȩ */
    if (PPP_USERTYPE_NOCMIP_NOAAA(pstLcpInfo,pstPppInfo))
    {
        HSGW_EmsTraceByRpIndex(pstPppInfo->ulRPIndex, HSGW_EMS_MODULE_PPP, EMS_PPP_12);
        PPP_DBG_ERR_CNT(PPP_PHERR_595);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                     "\r\n PPP_Shell_Ipv6cpUpNegotiateIp 2: is sip no auth: %u",
                     pstPppInfo->ulRPIndex);

        PPP_SET_REL_CODE(pstPppInfo, AM_RELCODE_PPP_IPV6CP_NEGONAK);
        PPP_LCP_NegotiationDown(pstPppInfo->pstLcpInfo);
        IPV6_PerfStatistic(IPV6_IPV6CP_SUCC);
        A11_OM_PerfStatisticPCFUnit((ULONG)PERF_TYPE_PCF_PPPC_IPV6CP_NEGO_SUCC_NUM, pstPppInfo->ulPcfIP);
        return VOS_ERR;
    }
    PPP_DebugOut(MID_PPPC,PPP_DEBUG_INFO,"\r\n PPP_Shell_IpV6cpUpNegotiateIp Done!");
    return VOS_OK;
}
ULONG PPP_Shell_IpV6cpSuccessProc( PPPINFO_S *pstPppInfo )
{
    PDN_PPP_NCP_UP_S stNcpUpInfo = { 0 };
    ULONG64 ulNegoTime = 0;

    /* ����ͳ�� */

    /* IPV6CP�ɹ���PPP֪ͨPDN */
    VOS_MemCpy(stNcpUpInfo.aucIpV6Addr, pstPppInfo->usPeerIPv6Addr,PDN_IPV6ADDR_LEN);

    /* ����ͳ��:IPv6CPЭ�̳ɹ����� */
    PPP_DBG_OK_CNT(PPP_PHOK_1326);
    IPV6_PerfStatistic(IPV6_IPV6CP_SUCC);
    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n PPP_Shell_IpV6cpSuccessProc: IPV6_PerfStatistic Success:Enter !");

    A11_OM_PerfStatisticPCFUnit((ULONG)PERF_TYPE_PCF_PPPC_IPV6CP_NEGO_SUCC_NUM, pstPppInfo->ulPcfIP);

    M_SET_NEWPHASE(pstPppInfo, PPP_SNMP_PERF_PHASE_SUCCESS);

    /* PPP��·�����ɹ� */
    pstPppInfo->bPppSuccess = 1;

    /* ɾ��Э�̶�ʱ�� */
    (VOID)PPP_NodeDelete(pstPppInfo->ulRPIndex);

    if(0 == pstPppInfo->ulNegoEndTime)
    {
        pstPppInfo->ulNegoEndTime = VOS_GetTick();
        ulNegoTime = pstPppInfo->ulNegoEndTime - pstPppInfo->ulNegoStartTime;
        (VOID)PerfSetFamPerfCounterByAddress(&(g_stPppPerfStatistic.ulPppNegoTotalTime), PPP_PERF_ADD, (ULONG)ulNegoTime);
        PPP_PerfInc(&g_stPppPerfStatistic.ulPppNegoNum, PERF_TYPE_PPPC_PPP_NEGO_NUM, pstPppInfo->bEhrpdUser);
        PPP_DBG_OK_CNT(PPP_PHOK_1327);
    }

    /* ��̬���ӱ���óɹ� */
    pstPppInfo->bPppStateFlgV6 = PPP_STATE_SUCCESS;

    /* ��ʱ���� */

    if (pstPppInfo->bReNegoV6)
    {
        pstPppInfo->bReNegoV6 = 0;

        /*ipcp���ƿ�Ϊ�ջ���v4��Э�̱����Ч���ͷſ��ƿ�*/
        if (((pstPppInfo->pstPppRenegoInfo)&&(VOS_NULL_PTR == pstPppInfo->pstIpcpInfo))
            || ((pstPppInfo->pstPppRenegoInfo)&&(!pstPppInfo->bReNego)))
        {
            (VOID)PPP_Free(pstPppInfo->pstPppRenegoInfo);
            pstPppInfo->pstPppRenegoInfo = 0;
        }
    }

    if (pstPppInfo->pL2tpPara != VOS_NULL_PTR)
    {
        (VOID)PPP_Free(pstPppInfo->pL2tpPara);
        pstPppInfo->pL2tpPara = VOS_NULL_PTR;
    }

    (VOID)PPP_NotifyIpv6SendRA(pstPppInfo->ulRPIndex, VOS_NULL_BYTE);

    (VOID)PPP_SendUserInfo(pstPppInfo, IPCPV6_INFOR);

    /* IPV6CP�ɹ�ʱ���� */
    PPPC_IsReadyToRespActCmd(pstPppInfo);

    return VOS_OK;
}
ULONG PPP_Shell_ReceiveIpV6cpUpFromCore(  PPPINFO_S *pstPppInfo )
{
    PPPIPV6CPINFO_S* pstIpV6cpInfo = VOS_NULL_PTR;
    ULONG ulRet = VOS_ERR;

    pstIpV6cpInfo = pstPppInfo->pstIpV6cpInfo;
    if ( VOS_NULL_PTR == pstIpV6cpInfo )
    {
        PPP_SET_REL_CODE(pstPppInfo, AM_RELCODE_PPP_IPV6CP_NEGONAK);
        PPP_LCP_NegotiationDown(pstPppInfo->pstLcpInfo);  /*�ͷ���·*/
        PPP_DBG_ERR_CNT(PPP_PHERR_597);
        return VOS_ERR;
    }

    /* δЭ��ipΪCMIP���� */
    if (0 == pstIpV6cpInfo->stHisOptions.neg_addr)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_598);
        (VOID)PPP_Shell_IpV6cpUpNoIp(pstPppInfo);
        return VOS_ERR;
    }

    /*Э����IP��ַ*/
    ulRet = PPP_Shell_IpV6cpUpNegotiateIp(pstPppInfo);
    if (VOS_ERR == ulRet)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_599);
        return VOS_ERR;
    }

    PPP_DBG_OK_CNT(PPP_PHOK_1328);
    return PPP_Shell_IpV6cpSuccessProc(pstPppInfo);
}
ULONG PPP_Shell_ReceiveCcpUpFromCore(PPPINFO_S *pstPppInfo)
{
    ULONG ulResult = 0;
    PPP_CCP_INFO_S* pstCcpInfo = VOS_NULL_PTR;
    UCHAR ucAnotherDmpu = 0;
    UCHAR ucDmpuId = 0;
    UCHAR ucDpeId = 0;

    pstCcpInfo = (PPP_CCP_INFO_S*)pstPppInfo->pstCcpInfo;
    if (VOS_NULL_PTR == pstCcpInfo)
    {
         return VOS_ERR;
    }

    switch(pstCcpInfo->ucPppCompType)
    {
        case PPPCOMP_MPPC:
        {
            /* ѡ���ӿ����ӿ���DPEID */
            if (MAX_DMPU_ID <= pstPppInfo->ucDmpuId)
            {
                ulResult = (ULONG)PPP_CompSelectDmpuDpe(&ucDmpuId, &ucDpeId);
                if (VOS_OK != ulResult)
                {
                    PPP_DBG_ERR_CNT(PPP_PHERR_600);
                    return VOS_ERR;
                }

                ulResult = (ULONG)PPP_CompCheckMppcUserNum(&ucDmpuId);
                if(VOS_OK != ulResult)
                {
                     /* �ӿ�����λ�����û���Ҳ�Ѿ��ﵽ���ޣ�����ֹCCP */
                     PPP_DBG_ERR_CNT(PPP_PHERR_601);
                     return VOS_ERR;
                }

                pstPppInfo->ucDmpuId = ucDmpuId;
                pstPppInfo->ucDpeId  = ucDpeId;
            }

            if((VOS_FALSE == pstPppInfo->bMppcFlag) && (VOS_TRUE == pstPppInfo->bVjFlag))
            {
                PPP_DBG_OK_CNT(PPP_PHOK_1329);
            }
            /* END of liushuang */

            PPP_DBG_OK_CNT(PPP_PHOK_1330);
            PPP_CompUserNumAdd(pstPppInfo, PPP_USERSTAT_MPPC);
            PPP_INNER_COUNTER(PPP_INNER_COUTNER_065);
            break;
        }
        case PPPCOMP_LZS0:
        {
            PPP_DBG_OK_CNT(PPP_PHOK_1331);
            PPP_CompUserNumAdd(pstPppInfo, PPP_USERSTAT_ZLS0);
            break;
        }
        case PPPCOMP_LZS1:
        {
            PPP_DBG_OK_CNT(PPP_PHOK_1332);
            PPP_CompUserNumAdd(pstPppInfo, PPP_USERSTAT_ZLS1);
            break;
        }
        default:
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_602);
            PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                      "\r\n [ppp]PPP_Shell_ReceiveCcpUpFromCore: Unknow compress type %d",
                      pstCcpInfo->ucPppCompType);
            return VOS_ERR;
        }
    }

    if (VOS_OK != PPP_SendUserInfo(pstPppInfo, SCP_INFOR))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_603);
        return VOS_ERR;
    }

    /* ����ͳ�� */
    PPP_PerfInc(&g_stPppPerfStatistic.ulCcpSuccess, PERF_TYPE_PPPC_CCP_NEGO_SUCC, pstPppInfo->bEhrpdUser);


    return VOS_OK;
}


VOID PPP_Shell_ReceiveCcpDownFromCore(PPPINFO_S *pstPppInfo)
{
    A11_PPPC_USR_INFOR_S stUsrinfo = { 0 };

    if (pstPppInfo->bMppcFlag)
    {
        PPP_CompUserNumDel(pstPppInfo, PPP_USERSTAT_MPPC);
        PPP_DBG_OK_CNT(PPP_PHOK_1333);
        PPP_INNER_COUNTER(PPP_INNER_COUTNER_069);
    }
    if (pstPppInfo->bLzs0Flag)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1334);
        PPP_CompUserNumDel(pstPppInfo, PPP_USERSTAT_ZLS0);
    }
    if (pstPppInfo->bLzs1Flag)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1335);
        PPP_CompUserNumDel(pstPppInfo, PPP_USERSTAT_ZLS1);
    }

    stUsrinfo.ucPPPConFlag = 0;

    if (PPPA11DOWNNOLCPTER == pstPppInfo->bFailFlag)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1336);
        stUsrinfo.ucPcfReleaseFlag = VOS_TRUE;
    }
#if 0
    /* ֪ͨA11���������ļ�A10�� */
    (VOID)A11_PPPC_SendUsrInfor(pstPppInfo->ulRPIndex,
                        &stUsrinfo,
                        SCP_INFOR);
#endif

    return;
}

/*****************************************************************************
 �� �� ��  : PPP_Shell_ReceiveFreePeerIpFromCore
 ��������  : ���ں˽����¼��Ľӿں���
 �������  : pstPppInfo:PPP���ƿ�
             ulCmd:������
             pPara:�¼��Ĳ���
 �������  : ��
 �� �� ֵ  : VOS_OK;VOS_ERR
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2000-04-04
    ��    ��   : Deng Yi Ou
    �޸�����   :

*****************************************************************************/
ULONG PPP_Shell_ReceiveEventFromCore(PPPINFO_S *pstPppInfo,
                                     ULONG      ulCmd,
                                     CHAR *     pPara)
{
    SDB_PDSN_RP_CONTEXT_S *pstRpContext = VOS_NULL_PTR;
    PDN_CONTEXT_S *pstPdnContext = VOS_NULL_PTR;
    ULONG ulResult = VOS_OK;
    ULONG ulPdnIndex = 0;

    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
        "\r\n [ppp]PPP_Shell_ReceiveEventFromCore: Enter ulCmd: %d", ulCmd);

    if (!pstPppInfo || (ulCmd >= PPP_EVENT_CTSEND))
    {
        VOS_DBGASSERT(0);
        return VOS_ERR;
    }

    switch (ulCmd)
    {
        case PPP_LCP_UP:
        {
            /* �·�LCP�û���Ϣ*/
            ulResult = PPP_Shell_ReceiveLcpUpFromCore(pstPppInfo);
            break;
        }

        case PPP_LCP_DOWN:
        {
            PPP_Shell_ReceiveLcpDownFromCore(pstPppInfo);
            break;
        }

        case PPP_IPCP_UP:
        {
            ulResult = PPP_Shell_ReceiveIpcpUpFromCore(pstPppInfo);
            break;
        }

        case PPP_IPCP_DOWN:
        {
            /* ��̬���ӱ����ʧ�� */
            pstPppInfo->bPppStateFlg = PPP_STATE_FAIL;

            break;
        }

        case PPP_IPV6CP_UP:
        {
            ulResult = PPP_Shell_ReceiveIpV6cpUpFromCore(pstPppInfo);
            break;
        }

        case PPP_IPV6CP_DOWN:
        {
            /* ��̬���ӱ����ʧ�� */
            pstPppInfo->bPppStateFlgV6 = PPP_STATE_FAIL;


            /*��ȡrp������*/
            ulResult = (ULONG)SDB_GetRpContextByIndex(pstPppInfo->ulRPIndex, (VOID**)&pstRpContext);
            if ((SDB_SUCCESS != ulResult) || (VOS_NULL_PTR == pstRpContext))
            {
                break;
            }

            ulPdnIndex = (ULONG)pstRpContext->ausPdnIndexArray[0];

            /*��ȡPDN������*/
            ulResult = (ULONG)SDB_GetPdnContextByIndex(ulPdnIndex, (VOID**)&pstPdnContext);
            if ((SDB_SUCCESS != ulResult) || (VOS_NULL_PTR == pstPdnContext))
            {
                PPP_DBG_ERR_CNT(PPP_PHERR_604);
                break;
            }

            /* ֹͣIPv6��ʱ�������ٷ���RA��Ϣ */
            ulResult = IPV6_StopTimer(pstPdnContext->ulIpv6Timer);
            if (VOS_OK != ulResult)
            {
               /* ���ӵ�����Ϣ�������˳� */
               PPP_DBG_ERR_CNT(PPP_PHERR_605);
            }
            pstPdnContext->ulIpv6Timer = 0;

            break;
        }
        case PPP_VSNCP_UP:
        {
            ulResult = PPP_Shell_ReceiveVSNCPUpFromCore(pstPppInfo);
            break;
        }
        case PPP_VSNCP_DOWN:
        {
            /* ��̬���ӱ����ʧ�� */
            break;
        }
        case PPP_CCP_UP:
        {
            ulResult = PPP_Shell_ReceiveCcpUpFromCore(pstPppInfo);
            break;
        }
        case PPP_CCP_DOWN:
        {
            PPP_Shell_ReceiveCcpDownFromCore(pstPppInfo);
            break;
        }
        default:
            break;
    }

    return ulResult;
}
/*****************************************************************************
 �� �� ��  : PPP_Shell_GetPacketFromCore
 ��������  : �ں˷��ͱ��ĺ���
 �������  : pstPppInfo:PPP���ƿ�
             pPacket:�ַ�������ʽ���ڵı���
             ulLen:���ĳ���
             usProtocol:PPPЭ���
 �������  : ��
 �� �� ֵ  : VOS_OK;VOS_ERR
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2000-04-04
    ��    ��   : Deng Yi Ou
    �޸�����   :

*****************************************************************************/
ULONG PPP_Shell_GetPacketFromCore(CHAR * pstPppInfo,
                                  UCHAR* pHead,
                                  UCHAR* pPacket,
                                  ULONG  ulLen,
                                  USHORT usProtocol)
{
    PMBUF_S *pMbuf = VOS_NULL_PTR;
    ULONG ulRetCode = 0;

    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n [ppp]PPP_Shell_GetPacketFromCore: Enter");

    if (VOS_NULL_PTR == pstPppInfo)
    {
        VOS_DBGASSERT(0);
        return VOS_ERR;
    }

    ShowCode(pPacket, (USHORT)ulLen);

    /* ������� */
    /*
     |------------- PPP_RESERVED_PACKET_HEADER ----------|
     |                   |--------PPP Head(bytes) -------|
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |       ...         |       |       |       |       |  Data ...
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |                                                   |
    pHead                                               pPacket
     */

    /* ��Ϣ���� */
    PPP_OmMsgTrc(((PPPINFO_S*)pstPppInfo)->ulRPIndex, usProtocol, pPacket, ulLen, PPP_TRACE_OUT,
                 0, &(((PPPINFO_S*)pstPppInfo)->stIMSI), ((PPPINFO_S*)pstPppInfo)->bEhrpdUser);

    /* ����MBUF */
    pMbuf = (PMBUF_S *)PMBUF_GetPMbuf(MID_PPPC, ulLen);
    if (VOS_NULL_PTR == pMbuf)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_606);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                     "\r\n [ppp]PPP_Shell_GetPacketFromCore: PMBUF_GetMbuf is NULL!");
        return VOS_ERR;
    }

    ulRetCode = PMBUF_CopyDataFromBufferToPMBuf(pMbuf,
                                              0,
                                              ulLen,
                                              (UCHAR *)pPacket,
                                              MID_PPPC);
    if (VOS_OK != ulRetCode)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_607);
        (VOID)PMBUF_Destroy(pMbuf);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                     "\r\n [ppp]PPP_Shell_GetPacketFromCore: MBUF_CopyDataFromBufferToMBuf fail!");
        return VOS_ERR;
    }

    /* ����ͳ��:����Э�̱������� */
    PPP_PerfInc(&g_stPppPerfStatistic.ulSendNego, PERF_TYPE_PPPC_SEND_NEGO_PKT_NUM, ((PPPINFO_S*)pstPppInfo)->bEhrpdUser);

#if (FEATURE_ON == FEATURE_HARDWARE_HDLC_ON_CCPU)
    return PPPC_HDLC_HARD_ProcProtocolPacket(((PPPINFO_S *)pstPppInfo)->ulRPIndex, pMbuf, 0, usProtocol);
#else
    return PPP_Shell_SendPacketToISL((PPPINFO_S *)pstPppInfo, pMbuf, usProtocol);
#endif
}


/*****************************************************************************
 �� �� ��  : PPP_Shell_ReceiveNegoPacket
 ��������  : ����Э�̱��ĺ���,
 �������  : pMbuf:����
 �������  : ��
 �� �� ֵ  : VOS_OK;VOS_ERR
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2000-04-04
    ��    ��   : Deng Yi Ou
    �޸�����   :

*****************************************************************************/
ULONG PPP_Shell_ReceiveNegoPacket(PMBUF_S *pMbuf, VOS_UINT8 ucPppId)
{
    ULONG ulLen = 0;
    ULONG ulOffset = 0;
    UCHAR *pHead = VOS_NULL_PTR;
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;
    ULONG enReturn = 0;
    ULONG ulA10Index = 0;
    UCHAR ucLcpTerminateFlg = VOS_FALSE;
    FWD_TO_CTRL_HDR       *pstCtrl      = VOS_NULL_PTR;
    CTTF_PPPC_TRACE_DATA_STRU *pstMntnInfo  = VOS_NULL_PTR;


    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n [ppp]PPP_Shell_ReceiveNegoPacket: Enter");

    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                  "\r\n [ppp]PPP_Shell_ReceiveNegoPacket: ReceiveNego: %d", g_stPppPerfStatistic.ulReceiveNego);

    if (VOS_NULL_PTR == pMbuf)
    {
        VOS_DBGASSERT(pMbuf);

        /* ����ͳ��:��ЧЭ�̱�����*/
        //PPP_PerfInc(g_stPppPerfStatistic.pulReceiveNegoErr, PERF_TYPE_PPPC_RCV_ERR_NEGO_PKT_NUM);

        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                      "\r\n [ppp]PPP_Shell_ReceiveNegoPacket: ReceiveNegoErr: %d", g_stPppPerfStatistic.ulReceiveNegoErr);

        PPP_DBG_ERR_CNT(PPP_PHERR_608);
        return VOS_ERR;
    }

    GETPPPINFOPTRBYRP(pstPppInfo, ucPppId);

    if (VOS_NULL_PTR == pstPppInfo)
    {
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                      "\r\n [ppp]PPP_Shell_ReceiveNegoPacket: ReceiveNegoErr: %d, User %d isn't exist!",
                      g_stPppPerfStatistic.ulReceiveNegoErr, ucPppId);

        PPP_ERROR_COUNTER(PPP_ERROR_COUNTER033);
        PPP_DBG_ERR_CNT(PPP_PHERR_611);
        return VOS_ERR;
    }

    pstPppInfo->bIsAsync = pstPppInfo->bSynAsyConvert;
    if (pstPppInfo->bSynAsyConvert && pstPppInfo->pstLcpInfo)
    {
        ((PPPLCPINFO_S *)pstPppInfo->pstLcpInfo)->stWantOptions.neg_asyncmap  = 1;
        ((PPPLCPINFO_S *)pstPppInfo->pstLcpInfo)->stAllowOptions.neg_asyncmap = 1;
    }

    ulLen = PMBUF_GET_TOTAL_DATA_LENGTH(pMbuf);

    /* ��ά�ɲ� */
    pstMntnInfo = (CTTF_PPPC_TRACE_DATA_STRU *)PPP_Malloc(
                   PPPC_OM_TRANS_DATA_OFFSET_LEN + ulLen);
    if (VOS_NULL_PTR != pstMntnInfo)
    {
        PS_MEM_SET(pstMntnInfo, 0, PPPC_OM_TRANS_DATA_OFFSET_LEN + ulLen);
        pstMntnInfo->ulReceiverCpuId = VOS_LOCAL_CPUID;
        pstMntnInfo->ulReceiverPid   = MSPS_PID_PPPC;
        pstMntnInfo->ulSenderCpuId   = VOS_LOCAL_CPUID;

        if (PPPC_RAT_MODE_1X == PPPC_GetRatMode())
        {
            pstMntnInfo->ulSenderPid     = MSPS_PID_1X_FRLP;
            pstMntnInfo->enMsgId         = ID_CTTF_1X_PPPC_TRACE_DATA_NEGO_DL;
            pstMntnInfo->enRatMode       = PPPC_RAT_MODE_1X;
            /* �յ���PPPЭ�̱�������һ */
            PPPC_1X_IncreaseNegoRcvCnt();
        }
        else
        {
            pstMntnInfo->ulSenderPid     = CTTF_PID_HRPD_FPA;
            pstMntnInfo->enMsgId         = ID_CTTF_HRPD_PPPC_TRACE_DATA_NEGO_DL;
            pstMntnInfo->enRatMode       = PPPC_GetRatMode();
            /* �յ���PPPЭ�̱�������һ */
            PPPC_HRPD_IncreaseNegoRcvCnt();
        }

        pstMntnInfo->ulLength        = ulLen + PPPC_OM_TRANS_DATA_OFFSET_LEN - VOS_MSG_HEAD_LENGTH;
        pstMntnInfo->usVersion       = CTTF_PPPC_TRACE_DATA_VERSION;
        (VOID)PS_MEM_CPY((VOS_UINT8 *)&pstMntnInfo->stDataStats, (VOS_UINT8 *)&g_stPppcDataQueueStats, sizeof(PPP_DATA_Q_STAT_STRU));
        (VOID)PMBUF_CopyDataFromPMBufToBuffer(pMbuf, 0, ulLen, pstMntnInfo->aucValue);

        PPP_MNTN_TRACE_MSG(pstMntnInfo);

        PPP_Free(pstMntnInfo);

        pstMntnInfo = VOS_NULL_PTR;
    }

    if (ulLen > PPP_DEFAULT_NEGO_PACKET_LEN)
    {
        HSGW_EmsTraceByRpIndex(pstPppInfo->ulRPIndex, HSGW_EMS_MODULE_PPP, EMS_PPP_13);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                      "\r\n [ppp]PPP_Shell_ReceiveNegoPacket: ReceiveNegoErr: %d, ulLength %d is too long!",
                      g_stPppPerfStatistic.ulReceiveNegoErr, ulLen);

        PPP_Debug_CoreEvent(pstPppInfo, PPP_LOG_NOTICE, "Receive a too long negotionate packet,drop it!!");
        PPP_DBG_ERR_CNT(PPP_PHERR_612);

        return VOS_OK;
    }

    /* Ԥ������PPP����ͷ�Ŀռ� */
    ulOffset = PPP_RESERVED_PACKET_HEADER;

    /*mode by z0012969 for c05 �����Ż�*/
    pHead = g_ucPppRcvPacketHead;
    if (VOS_NULL_PTR == pHead)
    {
        /* ���������Ϣ */
        PPP_Debug_CoreEvent(pstPppInfo, PPP_LOG_ERROR, "PPP_Shell_ReceiveNegoPacket: get addr Err!!");

        /* �ͷ�MBUF */
        PPP_DBG_ERR_CNT(PPP_PHERR_613);
        return VOS_ERR;
    }
    PPP_MemSet((void *)g_ucPppRcvPacketHead, 0,  PPP_DEFAULT_NEGO_PACKET_LEN+PPP_RESERVED_PACKET_HEADER);

    (VOID)PMBUF_CopyDataFromPMBufToBuffer(pMbuf, 0, ulLen, pHead + ulOffset);

    PPP_CheckIsLcpTerminateMsg(pstPppInfo, pHead + ulOffset, ulLen, &ucLcpTerminateFlg);

    /* �����ں˴��� */
    PPP_Core_ReceivePacketFromShell(pstPppInfo, pHead, pHead + ulOffset, ulLen);

    return VOS_OK;
}

/*****************************************************************************
�� �� ��  : PPP_Shell_ISLIoCtl
��������  : �ӵײ�����¼��Ľӿں���
�������  : USM_LAP2_MSG_S* pstMsg
�������  : pstPppInfo:PPPC���ƿ�ָ��
            ulCmd:������,����Ϊ����ֵ:
                  ISLUP:�ײ�UP
                  ISLDOWN:�ײ�DOWN                                                          ISPCFSWITCH:BS/PCF�л�
                  ISLRENEGO:�ײ���Э��
                  PPPC_L2TPUP:L2TP���͸�PPP��UP�¼�
                  PPPC_L2TPDOWN:L2TP���͸�PPP��DOWN�¼�
            pPara:�¼��Ĳ���,һ�������ΪNULL
                  L2TP��LNS�˱�ISLUPʱ������ԤЭ�̽��
�� �� ֵ  : VOS_OK;VOS_ERR
���ú���  :

��������  :

�޸���ʷ     :
1.��    ��   : 2000��04��04��
  ��    ��   : Deng Yi Ou
  �޸�����   : �����ɺ���
2.��    ��   : 2012��10��22��
  ��    ��   : luofang
  �޸�����   : �����ɺ���

*****************************************************************************/
ULONG PPP_Shell_ISLIoCtl(ULONG ulRPIndex, ULONG ulCmd, char *pPara)
{
    ULONG enReturn    = 0;
    ULONG ulA10Index  = 0;
    ULONG ulReRpIndex = 0;
    SDB_PDSN_RP_CONTEXT_S *pstRpContext = VOS_NULL_PTR;
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;
    PPPIPCPINFO_S* pstIpcpInfo = VOS_NULL_PTR;
    PPPIPV6CPINFO_S* pstIpv6cpInfo = VOS_NULL_PTR;
    PPP_CCP_INFO_S* pstCcpInfo = VOS_NULL_PTR;
    PPPRENOGOINFO stPppRenegoInfo = {0};

    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n [ppp]PPP_Shell_ISLIoCtl: Enter ulRPIndex %u, ulCmd %d", ulRPIndex, ulCmd);

    if (!(ulRPIndex <= PPP_MAX_USER_NUM)
        || (ulCmd >= ISLTUEND))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_615);
        PPP_ERROR_COUNTER(PPP_ERROR_COUNTER005);
        VOS_DBGASSERT(0);
        return VOS_ERR;
    }

    switch (ulCmd)
    {
        case PPP_ISLDOWN:
        {
            PPP_INNER_COUNTER(PPP_INNER_COUTNER_001);
            PPP_DBG_OK_CNT(PPP_PHOK_1337);

            GETPPPINFOPTRBYRP(pstPppInfo, ulRPIndex);

            if (VOS_NULL_PTR != pstPppInfo)
            {
                /* SNMP������: ��������ͳ��ԭ��ֵ: pcf����ȥ�� */
                PPP_SNMP_PERF_SET_FAILREASON_PCF_RELEASE(pstPppInfo, pstPppInfo->pulCurrFsm);

                /* PPPЭ�̹����У��յ�PCF���ͷ����� ��������Ự��������������1 */
                A11_ReqNumSubProc(pstPppInfo);
                PPP_DBG_OK_CNT(PPP_PHOK_1338);

                PPP_Core_ReceiveEventFromShell(pstPppInfo, (ULONG)PPPISLDOWN, VOS_NULL_PTR);
                (VOID)PPP_DeleteCB(pstPppInfo);
                PPP_DBG_OK_CNT(PPP_PHOK_1339);
            }
            else
            {
                PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                        "\r\n [ppp]PPP_Shell_ISLIoCtl: PPPINFO index %d IS NULL!", ulRPIndex);

                return VOS_ERR;
            }
            break;
        }

        case ISPCFSWITCH:
        {
            if (VOS_NULL_PTR == pPara)
            {
                VOS_DBGASSERT(0);
                return VOS_ERR;
            }

            GETPPPINFOPTRBYRP(pstPppInfo, ulRPIndex);
            if (VOS_NULL_PTR != pstPppInfo)
            {
                /* ����RP INDEX */
                VOS_MemCpy(&g_astPppPool[*(ULONG*)pPara], pstPppInfo, sizeof(PPPINFO_S));

                g_astPppPool[*(ULONG*)pPara].ulRPIndex = *(ULONG*)pPara;
                g_astPppPool[ulRPIndex].usState = PPP_CB_STATE_FREE;
            }
            else
            {
                PPP_DBG_ERR_CNT(PPP_PHERR_617);
                PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                            "\r\n [ppp]PPP_Shell_ISLIoCtl: ISPCFSWITCH: PPPINFO IS NULL!");
                return VOS_ERR;
            }
            break;
        }
        case ISLRENEGO:
        {
            /*�ײ��ϱ���PPPЭ�̱�������A10Index����Ҫת����RpIndex��Ϊ�˱��ֽӿ�ͳһ��
            ���ﻹ��ʹ��ulRPIndex��Ϊ��Σ����б����ֵΪ�ײ��������A10Index*/
            PPP_INNER_COUNTER(PPP_INNER_COUTNER_011);
            ulA10Index = ulRPIndex;
#if 0
            enReturn = (ULONG)SDB_GetRpContextByA10Index(ulA10Index,
                                                         (ULONG*)&ulReRpIndex,
                                                         (UCHAR**)&pstRpContext);
            if ((enReturn != SDB_SUCCESS) || (VOS_NULL_PTR == pstRpContext))
            {
                PPP_DBG_ERR_CNT(PPP_PHERR_618);
                PPP_ERROR_COUNTER(PPP_ERROR_COUNTER008);
                return VOS_ERR;
            }
#endif
            PPP_DBG_OK_CNT(PPP_PHOK_1340);

            PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                         "\r\n [ppp]PPP_Shell_ISLIoCtl: NP notify user %u RENEGO", ulReRpIndex);

            GETPPPINFOPTRBYRP(pstPppInfo, ulReRpIndex);
            if (VOS_NULL_PTR != pstPppInfo)
            {
                pstIpcpInfo = (PPPIPCPINFO_S*)pstPppInfo->pstIpcpInfo;
                pstIpv6cpInfo = (PPPIPV6CPINFO_S*)pstPppInfo->pstIpV6cpInfo;
                pstCcpInfo = (PPP_CCP_INFO_S*)pstPppInfo->pstCcpInfo;

                PPP_DBG_OK_CNT(PPP_PHOK_1341);

                PPP_MemSet((VOID*)&stPppRenegoInfo, 0, sizeof(stPppRenegoInfo));

                if ( (pstIpcpInfo&&(PPP_STATE_OPENED == pstIpcpInfo->stFsm.ucState))
                    || ((pstIpv6cpInfo) && (PPP_STATE_OPENED == pstIpv6cpInfo->stFsm.ucState)))
                {
                    PPP_DBG_OK_CNT(PPP_PHOK_1342);

                    if (pstIpcpInfo)
                    {
                        pstPppInfo->bReNego = 1;
                        stPppRenegoInfo.ucIpcpFlag = 1;
                        (VOID)VOS_MemCpy((VOID*)&stPppRenegoInfo.stIpcpOptions, (VOID*)&pstIpcpInfo->stGotOptions,
                        sizeof(PPP_IPCP_OPTION_S));
                    }
                    if (pstIpv6cpInfo)
                    {
                        pstPppInfo->bReNegoV6 = 1;
                        stPppRenegoInfo.ucIpV6cpFlag = 1;
                        (VOID)VOS_MemCpy((VOID*)&stPppRenegoInfo.stIpcpV6Options, (VOID*)&pstIpv6cpInfo->stGotOptions,
                        sizeof(PPP_IPV6CP_OPTION_S));
                    }

                    /* ͨ�ô��������Ƿ�˫ջ�û� */
                    if (pstCcpInfo && (PPP_STATE_OPENED == pstCcpInfo->stFsm.ucState))
                    {
                        stPppRenegoInfo.ucCcpFlag = 1;
                        (VOID)VOS_MemCpy((VOID*)&stPppRenegoInfo.stCcpOptions, (VOID*)&pstCcpInfo->stGotOptions,
                        sizeof(PPP_CCP_options_S));
                    }

                    M_SET_NEWPHASE(pstPppInfo, PPP_SNMP_PERF_PHASE_LCP);
                    //(VOID)PPP_NodeDelete(ulReRpIndex);
                    (VOID)PPP_NodeAdd(ulReRpIndex, 0, PPP_NEGO_LIST_NODE_LCP_START);

                    if (VOS_NULL_PTR == pstPppInfo->pstPppRenegoInfo)
                    {
                        pstPppInfo->pstPppRenegoInfo = (PPPRENOGOINFO *)PPP_Malloc(sizeof(PPPRENOGOINFO));
                        if(VOS_NULL_PTR == pstPppInfo->pstPppRenegoInfo )
                        {
                            PPP_DBG_ERR_CNT(PPP_PHERR_619);
                            VOS_DBGASSERT(0);
                            (VOID)vos_printf("\r\n PPP_Shell_ISLIoCtl PPP_Malloc Failed!~!!");
                            return VOS_ERR;
                        }
                        PPP_MemSet((void*)pstPppInfo->pstPppRenegoInfo, 0, sizeof(PPPRENOGOINFO));
                    }

                    if (VOS_NULL_PTR != pstPppInfo->pstPppRenegoInfo)
                    {
                        (VOID)VOS_MemCpy(pstPppInfo->pstPppRenegoInfo, (VOID*)&stPppRenegoInfo,
                        sizeof(PPPRENOGOINFO));
                    }

                    PPP_DBG_OK_CNT(PPP_PHOK_1343);
                    pstPppInfo->bPpcAAAFlag = 0;

                    PPP_Core_ReceiveEventFromShell(pstPppInfo, PPPISLRENEGO, VOS_NULL_PTR);
                }
            }
            else
            {
                PPP_ERROR_COUNTER(PPP_ERROR_COUNTER009);
                PPP_DBG_ERR_CNT(PPP_PHERR_620);
                PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                             "\r\n [ppp]PPP_Shell_ISLIoCtl: ISLRENEGO: PPPINFO IS VOS_NULL_PTR!");
                return VOS_ERR;
            }
            break;
        }
        default:
            break;
    }

    return VOS_OK;
}

/****************************************************************************
* CREATE DATE  ��2000/04/04                                                 *
* CREATED BY   ��Deng Yi Ou                                                 *
* FUNCTION     ����ײ㷢�ͱ���,���ñ�����ǰ�����Mbuf��Ԥ����PPP����ͷ�ռ� *
* MODIFY DATE  ��modified by gxf for GGSN80 20030218                        *
* INPUT        ��pstPppInfo:PPP���ƿ�                                       *
*                pMbuf:MBUF��ʽ���ڵı���                                   *
*                usProtocol:PPPЭ���                                       *
* OUTPUT       ��                                                           *
* RETURN       ��VOS_OK:�ɹ�;VOS_ERR:ʧ��                                   *
* CALLED BY    ��PPP_Shell_GetPacketFromCore��PPP_Shell_NiOutput��          *
*                MP_Transmit                                                *
****************************************************************************/
ULONG PPP_Shell_SendPacketToISL(PPPINFO_S *pstPppInfo,
                               PMBUF_S *   pMbuf,
                               USHORT     usProtocol)
{
    /* ������� */

    /*
    |--------PPP Head(bytes) -------|
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    |       |       |       |       |  Data ...
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    |
                                  pMbuf->pData
    */
    UCHAR* pBuf = VOS_NULL_PTR;
    ULONG ulResult;
    ULONG ulHeadLen;
    PPPLCPINFO_S* pstLcpInfo = VOS_NULL_PTR;

    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                "\r\n PPP_Shell_SendPacketToISL: enter pstPppInfo=0x%x, pMbuf = 0x%x, usProtocol = 0x%x",
                pstPppInfo, pMbuf, usProtocol);

    if (VOS_NULL_PTR == pMbuf)
    {
        VOS_DBGASSERT(0);
        return VOS_ERR;
    }

    if ((VOS_NULL_PTR == pstPppInfo) || (VOS_NULL_PTR == pstPppInfo->pstLcpInfo))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_621);
        (VOID)PMBUF_Destroy(pMbuf);
        VOS_DBGASSERT(0);
        return VOS_ERR;
    }

    /* ��ñ���ָ�� */
    pBuf = (UCHAR*)PMBUF_MTOD(pMbuf, CHAR *);

    pstLcpInfo = (PPPLCPINFO_S*)(pstPppInfo->pstLcpInfo);

   /* ���ӱ��ĳ��� */
   if ((pstPppInfo->bIsAsync)
       && ((usProtocol == PPP_LCP) || !(pstLcpInfo->stHisOptions.neg_accompression)))
   {
       ulHeadLen = PPP_HDRLEN;
   }
   else
   {
       ulHeadLen = PPP_HDRLEN - 2; /* ȥ��ff03 */
   }

   /*Begin WGGSN_B03_L2TP_PPPC_COMP*/
   /* ��Э����ѹ���Ĵ��� */
   if (((usProtocol == PPP_IP)
        || (usProtocol == PPP_SCP)) && (pstLcpInfo->stHisOptions.neg_pcompression))
   {
       ulHeadLen -= 1;
   }

   /*End WGGSN_B03_L2TP_PPPC_COMP*/

   PMBUF_PREPEND_MEMORY_SPACE(pMbuf, ulHeadLen, MID_PPPC, ulResult);

   if (ulResult == 0)
   {
       /* ok */
       if (pMbuf == VOS_NULL_PTR)
       {
           PPP_DBG_ERR_CNT(PPP_PHERR_622);
           PPP_Debug_CoreEvent(pstPppInfo, PPP_LOG_ERROR, "PPP_Shell_SendPacketToISL: Mbuf is NULL!");
           return VOS_ERR;
       }
   }
   else
   {
       PPP_DBG_ERR_CNT(PPP_PHERR_623);
       /* failed */
       PPP_Debug_CoreEvent(pstPppInfo, PPP_LOG_ERROR, "MBUF_PREPEND_MEMORY_SPACE Err!!");
       (VOID)PMBUF_Destroy(pMbuf);
       return VOS_ERR;
   }

   /* ��ñ���ָ�� */
   pBuf = (UCHAR*)PMBUF_MTOD(pMbuf, CHAR *);

   /* ������� */

   /*
    |--------PPP Head(bytes) -------|
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    |       |       |       |       |  Data ...
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    |
   pMbuf->pData
   pBuf
    */

   /* ��PPP����ͷ */
   /*PPP_MAKEHEADER(pBuf, usProtocol) ;*/
   if (pstPppInfo->bIsAsync
       && ((usProtocol == PPP_LCP) || !(pstLcpInfo->stHisOptions.neg_accompression)))
   {
       PPP_PUTCHAR(PPP_ALLSTATIONS, pBuf);
       PPP_PUTCHAR(PPP_UI, pBuf);
   }

   /*Begin WGGSN_B03_L2TP_PPPC_COMP*/
   /* ��Э����ѹ���Ĵ��� */
   if (((usProtocol == PPP_IP)
        || (usProtocol == PPP_SCP)) && (pstLcpInfo->stHisOptions.neg_pcompression))
   {
       PPP_PUTCHAR(usProtocol, pBuf);
   }
   else
   {
       PPP_PUTSHORT(usProtocol, pBuf);
   }

   /*End WGGSN_B03_L2TP_PPPC_COMP*/


   /* ������� */

   /*
    |--------PPP Head(bytes) -------|
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    |  ff   |   03  |    protocol   |  Data ...
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    |                               |
   pMbuf->pData                    |
                                   pBuf
    */

   /* ͬ/�첽ת�� */
   if (pstPppInfo->bSynAsyConvert)
   {
        /* ����PPPЭ��RFC1661��LCP����ѡ����ACCMѡ�����LCP���Ĳ����첽ӳ�� */
       pMbuf = PPP_SynToAsy(pMbuf,
                (usProtocol == PPP_LCP ? 0x00000000 : pstPppInfo->ulRemoteAccm));
       if (pMbuf == VOS_NULL_PTR)
       {
           PPP_DBG_ERR_CNT(PPP_PHERR_624);
           PPP_Debug_CoreEvent(pstPppInfo, PPP_LOG_ERROR, "Syn To Asy Error!!");
           return VOS_ERR;
       }
   }

   if (1 == pstPppInfo->bPppClient)
   {
       /* ���ͱ��� */
       ulResult = PPPC_ULSendNegoFrame(pMbuf, pstPppInfo->ulRPIndex);

#ifdef PPPC_ST
       ulResult =VOS_OK;
#endif

       if (VOS_ERR == ulResult)
       {
           PPP_DBG_ERR_CNT(PPP_PHERR_625);
           PPP_Debug_CoreEvent(pstPppInfo, PPP_LOG_ERROR, "Send Packet Fail!!");
           return VOS_ERR;
       }
   }
   else
   {
       /* �ͷ�pMbuf */
       PMBUF_Destroy(pMbuf);
       PPP_DBG_ERR_CNT(PPP_PHERR_867);
       PPP_DebugOut((ULONG)MID_PPPC, PPP_DEBUG_LOG,
                    "\r\n PPP_Shell_SendPacketToISL: PPP mode err not client %d", pstPppInfo->bPppClient);
   }

   return VOS_OK;
}


/*****************************************************************************
 �� �� ��  : PPP_Shell_ReceiveAAAResult
 ��������  : PPP�յ�AAA�ظ��ļ�Ȩ��Ϣ
 �������  : AAA_AUTHRSP_S *pstMsg
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��30��
    ��    ��   : luofang
    �޸�����   : �����ɺ���

*****************************************************************************/
VOID PPP_Shell_ReceiveAAAResult(AAA_AUTHRSP_S *pstMsg)
{
#if 0
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;
    PPPLCPINFO_S *pstLcpInfo = VOS_NULL_PTR;
    UCHAR ucValid = 0;
    ULONG ulIndex = 0;
    ULONG ulResult = 0;
    USM_PPP_LINKUP_RESULT_S stMsg ={0};  /* PPP Link up ֪ͨUSM����Ϣ�ṹ�� */
    /*��μ��*/
    if (VOS_NULL_PTR == pstMsg)
    {
        PPP_DebugOut(MID_PPPC,PPP_DEBUG_INFO,"\r\nPPP_Shell_ReceiveAAAResult Input para null!");
        return ;
    }

    ulIndex = pstMsg->ulSDBIndex;
    GETPPPINFOPTRBYRP(pstPppInfo, ulIndex);
    if (VOS_NULL_PTR == pstPppInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_626);
        PPP_ERROR_COUNTER(PPP_ERROR_COUNTER023);
        PPP_DebugOut(MID_PPPC,PPP_DEBUG_INFO, "\r\n PPP_Shell_ReceiveAAAResult: User %d isn't exist!", ulIndex);
        return;
    }

    if (pstMsg->ulMsgType != AAA_PPPC_CREAT_RSP)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_627);
        PPP_ERROR_COUNTER(PPP_ERROR_COUNTER022);
        PPP_Debug_CoreEvent(pstPppInfo, PPP_LOG_ERROR, "PPP ReceiveAAAResult: Msg Type Error!!");
        return;
    }

    ucValid = ((VOS_NULL_PTR == pstPppInfo->pstPapInfo)
          || ((PPPPAPINFO_S*)pstPppInfo->pstPapInfo)->ucServerState != PAP_STATE_WAIT_AAA)
          && ((VOS_NULL_PTR == pstPppInfo->pstChapInfo)
          || ((PPPCHAPINFO_S*)pstPppInfo->pstChapInfo)->ucServerState != CHAP_STATE_WAITING_AAA);
    if (ucValid)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_628);
        PPP_ERROR_COUNTER(PPP_ERROR_COUNTER021);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n PPP_Shell_ReceiveAAAResult: User %d state is wrong.", ulIndex);
        return;
    }

    /*��֤�ɹ�*/
    if (VOS_OK == pstMsg->ucResult)
    {
        /* ���AAA�·�������ͷ� L2TP,��ο�����ȥ���û� */
        ucValid = ((TUNNEL_L2TP != pstMsg->usTunnelType[0]) && (0 != pstMsg->usTunnelType[0]))
                &&(VOS_TRUE == SOFTPARA_BIT1478);
        if(ucValid)
        {
            /* ȥ���û� */
            PPP_DBG_ERR_CNT(PPP_PHERR_629);
            PPP_CHAP_DeleteTimer(pstPppInfo);
            PPP_PAP_DeleteTimer(pstPppInfo);
            PPP_SET_REL_CODE(pstPppInfo, AM_RELCODE_PPP_L2TPTUNLPARA_ERR);
            PPP_LCP_NegotiationDown(pstPppInfo->pstLcpInfo);
            return;
        }

        /*���� PDN_CheckL2tpUser()�����ж�*/
        ulResult = PDN_CheckL2tpUser(pstPppInfo->usCDBIndex,pstMsg);
        /*�����L2TP�û���ֱ��֪ͨUSM*/
        if(VOS_OK == ulResult)
        {
            /* ��䷢��USM����Ϣ�ṹ�� */
            stMsg.pucMsg = (UCHAR *)pstMsg;
            stMsg.ulRpIndex = pstPppInfo->ulRPIndex;
            stMsg.usDomainIndex = pstPppInfo->usCDBIndex;
            stMsg.usVirtualDomainIndex = pstPppInfo->usVirtualDomainIdx;
            VOS_MemCpy(stMsg.aucNAI, pstPppInfo->ucNAI, NAI_NAME_LEN + 1);

            (VOID)USM_NotifyPhaseResultFunc(pstPppInfo->ulRPIndex,
                                          E_USM_MSGTYPE_PPP2USM_SETUP,
                                          (UCHAR *)&stMsg);
            PPP_CHAP_DeleteTimer(pstPppInfo);
            PPP_PAP_DeleteTimer(pstPppInfo);
            return;
        }

    }
    else
    {
        /* AUTHģ�鷵��ʧ��ʱ����������Ự��������������1*/
        switch(pstMsg->ucResult)
        {
            case AAA_AUTH_FAIL:
            {
                SNMP_SetFailReason(pstPppInfo, FSM_ALARM_AUTH_ERROR_ACCOUNT);

                A11_ReqNumSubProc(pstPppInfo);
                PPP_DBG_ERR_CNT(PPP_PHERR_630_AUTH_FAIL);

                break;
            }
            case AAA_AUTH_SRV_ERR:
            {
                SNMP_SetFailReason(pstPppInfo, FSM_ALARM_AUTH_AAA_NO_RSP);

                A11_ReqNumSubProc(pstPppInfo);

                PPP_DBG_ERR_CNT(PPP_PHERR_631);
                break;
            }
            default:
            {
                PPP_DBG_ERR_CNT(PPP_PHERR_632);
                break;
            }
        }
    }

    /*���򣬻ظ���Ȩ��Ϣ.Ȼ����PPP_Core_NetworkPhase������
    ��������֤����Э�̺��������̣���֪ͨUSM*/
    pstLcpInfo = (PPPLCPINFO_S*)pstPppInfo->pstLcpInfo;
    if (VOS_NULL_PTR == pstLcpInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_633);
        PPP_DebugOut(MID_PPPC,PPP_DEBUG_INFO,
                   "\r\n PPP_Shell_ReceiveAAAResult:pstLcpInfo null");
        return;
    }

    /* ��chap\papģ�鴦�� */
    if (pstLcpInfo->stGotOptions.neg_chap)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1344);
        PPP_CHAP_ReceiveAAAResult(pstMsg);
    }
    if (pstLcpInfo->stGotOptions.neg_upap)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1345);
        PPP_PAP_ReceiveAAAResult(pstMsg);
    }

    PPP_DebugOut(MID_PPPC,PPP_DEBUG_INFO,"\r\n PPP_Shell_ReceiveAAAResult success !");
#endif
    return;
}
VOID PPP_SendLcpPreProc(PPPINFO_S* pstPppInfo, A11_PPPC_USR_INFOR_S *pstUsrinfo)
{
    PPPLCPINFO_S *pstLcpInfo = VOS_NULL_PTR;
    pstLcpInfo = (PPPLCPINFO_S*)(pstPppInfo->pstLcpInfo);

    /* �·�Э�̽����A11 */
    pstUsrinfo->usMtu  = pstPppInfo->usMtu;
    pstUsrinfo->ulAccm = (pstPppInfo->ulLocalAccm | pstPppInfo->ulRemoteAccm);
    pstUsrinfo->ulMagicNum = pstLcpInfo->stGotOptions.magicnumber;
    pstUsrinfo->ulRpIndex = pstPppInfo->ulRPIndex;

    /* ͬ���첽��־ */
    pstUsrinfo->ucPPPMode |= (pstPppInfo->bSynAsyConvert ? A11_PPP_FLAG_SYNASY : 0);

    /* �ս�������־ */
    pstUsrinfo->ucPPPMode |= (pstPppInfo->bPppMode ? A11_PPP_FLAG_MODE : 0);

    pstUsrinfo->ucPPPMode |= (pstLcpInfo->stHisOptions.neg_pcompression ? A11_PPP_FLAG_PFC : 0);
    pstUsrinfo->ucPPPMode |= (pstLcpInfo->stHisOptions.neg_accompression ? A11_PPP_FLAG_ACFC : 0);

    return;
}
VOID PPP_SendIpcpPreProc(PPPINFO_S* pstPppInfo, A11_PPPC_USR_INFOR_S *pstUsrinfo)
{
     PPPIPCPINFO_S*  pstIpcpInfo = (PPPIPCPINFO_S*)(pstPppInfo->pstIpcpInfo);
     PPP_CCP_INFO_S* pstCcpInfo  = (PPP_CCP_INFO_S*)(pstPppInfo->pstCcpInfo);

     /*����PPP��Ϣ���û���Ϣ*/
     if ((VOS_NULL_PTR != pstIpcpInfo)
        && (PPP_STATE_OPENED == pstIpcpInfo->stFsm.ucState))
     {
          pstUsrinfo->ulPppFlag |= pstIpcpInfo->stGotOptions.neg_vj ? A11_PPP_FLAG_VJ : 0;
          pstUsrinfo->ucmaxslotindex = pstIpcpInfo->stGotOptions.maxslotindex;
     }

     if ((VOS_NULL_PTR != pstCcpInfo)
        && (PPP_STATE_OPENED == pstCcpInfo->stFsm.ucState))
     {
         switch (pstCcpInfo->ucPppCompType)
         {
             case PPPCOMP_MPPC:
                 pstUsrinfo->ulPppFlag |= A11_PPP_FLAG_MPPC;
                 break;
             case PPPCOMP_LZS0:
                 pstUsrinfo->ulPppFlag |= A11_PPP_FLAG_LZS0;
                 break;
             case PPPCOMP_LZS1:
                 pstUsrinfo->ulPppFlag |= A11_PPP_FLAG_LZS1;
                 break;
             default:
                 break;
         }
     }

     pstUsrinfo->ucPPPConFlag = (UCHAR)((pstUsrinfo->ulPppFlag) & (0xFFFFFFFC));

     if (CRM_BOARD_TYPE_SPUD == g_enPppBoardType)
     {
         if (MAX_DMPU_NUM > pstPppInfo->ucDmpuId)
         {
             pstUsrinfo->ucDmpuId    = pstPppInfo->ucDmpuId + PPP_CPU_2_ON_SPU;  /* �ӿ�ID���߼�IDҪת��Ϊʵ��CPUID */
             pstUsrinfo->ucDmpuDpeId = pstPppInfo->ucDpeId;
         }
     }
     else
     {
        pstUsrinfo->ucDmpuId    = pstPppInfo->ucDmpuId;
        pstUsrinfo->ucDmpuDpeId = pstPppInfo->ucDpeId;
     }
     return;
}

/****************************************************************************
* CREATE DATE  ��2004/01/31                                                 *
* CREATED BY   ��heyajun                                                    *
* FUNCTION     :                                                            *
* MODIFY DATE  ��                                                           *
* INPUT        ��                                                           *
*                                                                           *
*                                                                           *
* OUTPUT       ��                                                           *
* RETURN       ���ɹ�����VOS_OK��ʧ�ܷ���VOS_ERR                            *
* CALLED BY    ��                                                           *
****************************************************************************/
ULONG PPP_SendUserInfo(PPPINFO_S* pstPppInfo, ULONG ulType)
{
    A11_PPPC_USR_INFOR_S stUsrinfo = {0};

    if(LCP_INFOR == ulType)
    {
        PPP_SendLcpPreProc(pstPppInfo, &stUsrinfo);
    }
    else if ((IPCP_INFOR == ulType) || (SCP_INFOR == ulType))
    {
        PPP_SendIpcpPreProc(pstPppInfo, &stUsrinfo);
    }


    return VOS_OK;

}

/*End WGGSN_B03_L2TP_PPPC_COMP*/
/* Added start by liutao 38563 at 2004-09-22 V800R002 for PPPѹ����ֲ */

  /*=======================================================================
   *  ��������:  GTPC_EncapUpdatePdpContextReqV1
   *  �������:  2004/01/28
   *  ��    ��:
   *  ��������:  GTPC�ṩ��PPPCģ���PPP���ķ�װ�ӿ�
   *  �������:  pMbuf        ��װ��PPPЭ����Ϣ��MBUF�ṹָ��
   *  �������:  ��
   *  ��������:  GTPC_SUCCESS            ���ɹ�
   *             GTPC_FAILURE            ��ʧ��
   *  ȫ�ֱ���:  ��
   *  ����˵��:  B03 ��������
   *  ���ú���:  *
   *  ��������:
   *=======================================================================*/
  VOID ShowCode(UCHAR *pucMsg, USHORT usLen)
  {
      UCHAR ucMaxPerLine = 16;
      UCHAR ucCodeCount = 0, ucLine = 1;

      if ((VOS_NULL_PTR == pucMsg) || (usLen == 0))
      {
          return;
      }

      if (VRP_NO == g_ulPppDebugSwitch)
      {
          return;
      }

      (VOID)VOS_OutPrintf("\r\n #######Begin Decode Message#######\r\n");
      (VOID)VOS_OutPrintf("[%u]  ", ucLine++);

      while (usLen > 0)
      {
          (VOID)VOS_OutPrintf("%.2x ", *pucMsg );

          if (0 == (++ucCodeCount % ucMaxPerLine))
          {
              (VOID)VOS_OutPrintf("\r\n");
              if (ucLine < 10)
              {
                  (VOID)VOS_OutPrintf("[%u]  ", ucLine++);
              }
              else
              {
                  (VOID)VOS_OutPrintf("[%u] ", ucLine++);
              }
          }

          usLen--;
          pucMsg++;
      }

      (VOID)VOS_OutPrintf("\r\n#######End Decode Message#######\r\n");

      return;
  }


ULONG PPP_Shell_OutPut(ULONG ulRpindex, PMBUF_S *pstPMBuffNew, USHORT usProtocol)
{
  PPPINFO_S *pstPppInfo = VOS_NULL_PTR;  /*PDSN��ָ��PPP���ƿ��ָ��*/
  ULONG ulResult = 0;

  /* ��ȡPPPC���ƿ�ָ��*/
  GETPPPINFOPTRBYRP(pstPppInfo, ulRpindex);

  if (VOS_NULL_PTR == pstPppInfo)
  {
      PPP_DBG_ERR_CNT(PPP_PHERR_635);
      (VOID)PMBUF_Destroy((PMBUF_S*)pstPMBuffNew);
      return VOS_ERR;
  }

  /* ����PPP��ǵķ��ͺ��� */
  ulResult = PPP_Shell_SendPacketToISL((PPPINFO_S *)pstPppInfo, pstPMBuffNew, (USHORT)usProtocol);
  if (VOS_OK != ulResult)
  {
      PPP_DBG_ERR_CNT(PPP_PHERR_636);
      return VOS_ERR;
  }
  return VOS_OK;
}
ULONG PPP_CM_GetAuthFlag(ULONG ulPdnIndex,UCHAR * pucAuthFlag)
{
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;
    PPPLCPINFO_S *pstLcpInfo = VOS_NULL_PTR;
    PDN_CONTEXT_S *pstPdnContext = VOS_NULL_PTR;

    if (pucAuthFlag == VOS_NULL_PTR)
    {
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\nPPP PPP_CM_GetAuthFlag : input pointer is null");
        return VOS_ERR;
    }

    (VOID)SDB_GetPdnContextByIndex(ulPdnIndex, &pstPdnContext);
    if (VOS_NULL_PTR == pstPdnContext)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_637);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                "\r\nPPP PPP_CM_GetAuthFlag : get pdn context error %d",ulPdnIndex);
        return VOS_ERR;
    }

    GETPPPINFOPTRBYRP(pstPppInfo, pstPdnContext->ulRpIndex);
    if ((!pstPppInfo))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_638);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                 "\r\n PPP_CM_GetAuthFlag: Find RpIndex is wrong, ulRpIndex:%u", ulPdnIndex);
        return VOS_ERR;
    }

    *pucAuthFlag = 0;
    pstLcpInfo = (PPPLCPINFO_S*)pstPppInfo->pstLcpInfo;
    if (VOS_NULL_PTR == pstLcpInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_639);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\nPPP PPP_CM_GetAuthFlag pstLcpInfo is null no auth !");
        return VOS_ERR;
    }

    if (E_PDNTYPE_CMIP == pstPdnContext->ucPdnType)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1346);
        *pucAuthFlag = 1;
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\nPPP PPP_CM_GetAuthFlag : cmip user");
        return VOS_OK;
    }

    if ((1 == pstLcpInfo->stGotOptions.neg_chap) || (1 == pstLcpInfo->stGotOptions.neg_upap))
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1347);
        *pucAuthFlag = 1;
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\nPPP PPP_CM_GetAuthFlag : used chap/pap auth");
    }

    return VOS_OK;
}


VOID PPP_SetSendSTRFlag(ULONG ulRpIndex, ULONG ulAuthSessionState)
{
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;
    ULONG ulRet = 0;

    GETPPPINFOPTRBYRP(pstPppInfo, ulRpIndex);
    if (VOS_NULL_PTR == pstPppInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_640);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n [ppp]PPP_SetSendSTRFlag: pstPppInfo is null!");
        return;
    }

    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                 "\r\n [ppp]PPP_SetSendSTRFlag: ulAuthSessionState[%u] usPeerId[%u]ucAAAType[%u]!",
                 ulAuthSessionState, pstPppInfo->usPeerId, pstPppInfo->ucAAAType);

    if (VOS_TRUE == ulAuthSessionState)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1348);
        if (M_DIAMAUTH_DYNAAA_AAA == pstPppInfo->ucAAAType)
        {
            PPP_DBG_OK_CNT(PPP_PHOK_1349);
            /* ɾ���ϵ�hash */
            ulRet = Diam_AUTHHostRemoveByAAACBIndex(pstPppInfo->usPeerId, pstPppInfo->ulRPIndex);
            if (ulRet != VOS_OK)
            {
                PPP_DebugOut(MID_PPPC, PPP_DEBUG_ERROR,
                             "\r\n [ppp]PPP_SetSendSTRFlag: Diam_AUTHHostRemoveByAAACBIndex fail[%u] usPeerId[%u]ucAAAType[%u]!",
                             ulAuthSessionState, pstPppInfo->usPeerId, pstPppInfo->ucAAAType);
                PPP_DBG_ERR_CNT(PPP_PHERR_641);
            }

        }
        pstPppInfo->usPeerId = VOS_NULL_WORD;
        pstPppInfo->ucAAAType = VOS_NULL_BYTE;

    }

    return;
}
ULONG PPP_GetIPCPNakHandlingFlag(ULONG ulRpIndex)
{
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;

    GETPPPINFOPTRBYRP(pstPppInfo, ulRpIndex);
    if (VOS_NULL_PTR == pstPppInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_642);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "\r\n [ppp]PPP_GetIPCPNakHandlingFlag: pstPppInfo is null!");
        return VOS_FALSE;
    }

    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                 "\r\n [ppp]PPP_GetIPCPNakHandlingFlag: bIPCPNakHandFlag[%u]!",
                 pstPppInfo->bIPCPNakHandFlag);

    return pstPppInfo->bIPCPNakHandFlag;
}



ULONG PPP_GetPeerID(ULONG ulRpIndex, USHORT *pusPeerId)
{
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;

    GETPPPINFOPTRBYRP(pstPppInfo, ulRpIndex);
    if (VOS_NULL_PTR == pstPppInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_643);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "\r\n [ppp]PPP_GetPeerID: pstPppInfo is null!");
        return VOS_ERR;
    }

    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                 "\r\n [ppp]PPP_GetPeerID: usPeerId[%u]!",
                 pstPppInfo->usPeerId);

    *pusPeerId = pstPppInfo->usPeerId;

    return VOS_OK;
}




ULONG PPP_GetAAAType(ULONG ulRpIndex, UCHAR *pucAAAType)
{
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;

    GETPPPINFOPTRBYRP(pstPppInfo, ulRpIndex);
    if (VOS_NULL_PTR == pstPppInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_644);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "\r\n [ppp]PPP_GetAAAType: pstPppInfo is null!");
        return VOS_ERR;
    }

    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                 "\r\n [ppp]PPP_GetAAAType: ucAAAType[%u]!",
                 pstPppInfo->ucAAAType);
    *pucAAAType = pstPppInfo->ucAAAType;
    return VOS_OK;
}


ULONG PPP_UpdatePeerID(ULONG ulRpIndex, USHORT usPeerId, UCHAR ucAAAType)
{
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;
    SDB_PDSN_RP_CONTEXT_S *pstRpContext = VOS_NULL_PTR;
    ULONG ulRet = 0;
    USHORT usOldPeerId = 0;
    UCHAR ucOldAAAType = 0;

    GETPPPINFOPTRBYRP(pstPppInfo, ulRpIndex);
    if (VOS_NULL_PTR == pstPppInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_645);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "\r\n [ppp]PPP_UpdatePeerID: pstPppInfo is null!");
        return VOS_ERR;
    }

    ulRet = (ULONG)SDB_GetRpContextByIndex(pstPppInfo->ulRPIndex, (UCHAR**)&pstRpContext);
    if ((VOS_NULL_PTR == pstRpContext) || (ulRet != VOS_OK))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_646);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "\r\n [ppp]PPP_UpdatePeerID: SDB_GetRpContextByIndex fail[%u] index[%u]!",
                     ulRet, pstPppInfo->ulRPIndex);
        return VOS_ERR;
    }

    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                 "\r\n [ppp]PPP_UpdatePeerID: usPeerId[%u][%u] aaatype[%u]!",
                 pstPppInfo->usPeerId, usPeerId, ucAAAType);

    PPP_DBG_OK_CNT(PPP_PHOK_1350);
    usOldPeerId = pstPppInfo->usPeerId;
    ucOldAAAType = pstPppInfo->ucAAAType;
    pstPppInfo->usPeerId = usPeerId;
    pstPppInfo->ucAAAType = ucAAAType;

    /* ���� */
    if ((USM_STATE_ACTIVE == pstRpContext->ucUsmState)
        && ((pstPppInfo->usPeerId != usOldPeerId)
        || (pstPppInfo->ucAAAType != ucOldAAAType)))
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1351);
    }

    return VOS_OK;
}
ULONG PPP_JudgeIsDynAAAResource(ULONG ulRpIndex, USHORT *pusDynAAAIndex)
{
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;
    ULONG ulRet = 0;

    if (VOS_NULL_PTR == pusDynAAAIndex)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_647);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "\r\n [ppp]PPP_CheckDynAAAResource: pusDynAAAIndex is null!");
        return VOS_ERR;
    }

    GETPPPINFOPTRBYRP(pstPppInfo, ulRpIndex);
    if (VOS_NULL_PTR == pstPppInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_648);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                     "\r\n [ppp]PPP_CheckDynAAAResource: pstPppInfo is null!");
        return VOS_ERR;
    }


    if (M_DIAMAUTH_DYNAAA_AAA == pstPppInfo->ucAAAType)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1352);
        *pusDynAAAIndex = pstPppInfo->usPeerId;
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                     "\r\n [ppp]PPP_CheckDynAAAResource: usPeerId[%u]aaatype[%u]!",
                     pstPppInfo->usPeerId, pstPppInfo->ucAAAType);
        return VOS_OK;
    }
    PPP_DBG_OK_CNT(PPP_PHOK_1353);

    return VOS_ERR;
}



ULONG PPP_GetNowUTCInSec(ULONG ulRpIndex)
{
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;

    GETPPPINFOPTRBYRP(pstPppInfo, ulRpIndex);
    if (VOS_NULL_PTR == pstPppInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_649);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "\r\n [ppp]PPP_GetNowUTCInSec: pstPppInfo is null!ulRpIndex=%u", ulRpIndex);
        return VOS_NULL_DWORD;
    }

    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                 "\r\n [ppp]PPP_GetNowUTCInSec: ulNowUTCInSec[%u]!",
                 pstPppInfo->ulNowUTCInSec);

    return pstPppInfo->ulNowUTCInSec;
}


VOS_UINT64 PPP_GetLocalL2tpCsi(VOID)
{
    return g_ullPppLocalL2tpCsi;
}


VOID PPP_CheckIsLcpTerminateMsg(PPPINFO_S *pstPppInfo, UCHAR *pucPacket, ULONG ulLen, UCHAR *pucLcpTerminateFlg)
{
    UCHAR ucCode = 0;
    ULONG ulOffset = 0;
    USHORT usProtocol = 0;

    if ((VOS_NULL_PTR == pucPacket) || (VOS_NULL_PTR == pstPppInfo))
    {
        return;
    }
#if 0
    if (E_CRM_ACTIVE == CRM_GetSlotPrimaryInfoOfSelfGroup((UCHAR)DVM_SELF_SLOTID))
    {
        return;
    }
#endif

    /* ���Э���,������PPPͷ���� */
    ulOffset = PPP_Core_GetProtocol(pstPppInfo, pucPacket, &usProtocol);
    if ((ulOffset == 0) || (ulLen < ulOffset))
    {
        return;
    }

    /* �ƶ�ָ�� */
    pucPacket += ulOffset;
    ulLen -= ulOffset;

    PPP_GETCHAR(ucCode, pucPacket);

    if (PPP_LCP == usProtocol)
    {
        if ((ulLen > PPP_LCP_NEGO_PACKET_MAX_LEN) || (ulLen < FSM_HDRLEN)
            || ((VOS_NULL_PTR == pstPppInfo->pstLcpInfo)))
        {
            return;
        }
        if (TERMREQ == ucCode)
        {
            *pucLcpTerminateFlg = VOS_TRUE;
        }
    }

    return;
}
ULONG PPP_SlaveBoardDiscardMsMsg(SDB_PDSN_RP_CONTEXT_S *pstRpContext, UCHAR ucSlaveReleaseFlg)
{
#if 0
    if (E_CRM_ACTIVE == CRM_GetSlotPrimaryInfoOfSelfGroup((UCHAR)DVM_SELF_SLOTID))
    {
        return VOS_ERR;
    }
#endif

    if (VOS_NULL_PTR == pstRpContext)
    {
        return VOS_OK;
    }

    /* ���岻��Ҫ������ͷ���Ϣ */
    if (VOS_FALSE == ucSlaveReleaseFlg)
    {
        return VOS_OK;
    }

    pstRpContext->bSlaveReleaseFlg = VOS_TRUE;
    PPP_DBG_ERR_CNT(PPP_PHERR_650_MS_SLAVE_REL);

    return VOS_OK;
}


#define __PPP_L2TP_PROC__

/*****************************************************************************
�� �� ��  : PPP_L2tpMsgProc
��������  : PPPģ���յ�L2TP��Ϣ�Ĵ�����
�������  : PPPC_L2TP_NOTIFY_INFO *pstMsg
           ULONG ulMsgCode
�������  : ��
�� �� ֵ  : VOID
���ú���  :
��������  :

�޸���ʷ      :
1.��    ��   : 2012��12��13��
  ��    ��   :ZHAICHAO
  �޸�����   : �����ɺ���

*****************************************************************************/
VOID PPP_L2tpMsgProc(VOID *pstMsg, ULONG ulMsgCode)
{
#if 0
    ULONG ulRet = VOS_OK;
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;
    PDN_CONTEXT_S *pstPdnContext = VOS_NULL_PTR;
    ULONG ulPdnIndex = 0;

    if ( VOS_NULL_PTR == pstMsg )
    {
         PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n [ppp]PPP_L2tpMsgProc: input para is null!");
         return ;
    }

    /* ����Ѿ����������ж� */
    switch (ulMsgCode)
    {
         case PPP_MSG_CODE_L2TP_UP:
         {
             L2TP_NOTIFY_PPPC_UP_INFO* pstL2tpUpMsg = pstMsg;
             PPP_INNER_COUNTER(PPP_INNER_COUTNER_008);

             PPP_DBG_OK_CNT(PPP_PHOK_1356);

             ulPdnIndex = PDN_PDNGlobalIndexToPDNScIndex(pstL2tpUpMsg->ulPdpindex);

             ulRet = SDB_GetPdnContextByIndex(ulPdnIndex, (UCHAR**)&pstPdnContext);
             if ((VOS_OK != ulRet) || (VOS_NULL_PTR == pstPdnContext))
             {
                 PPP_DBG_ERR_CNT(PPP_PHERR_652);
                 return;
             }

             (VOID)PPP_NodeDelete(pstPdnContext->ulRpIndex);

             GETPPPINFOPTRBYRP(pstPppInfo, pstPdnContext->ulRpIndex);
             if (VOS_NULL_PTR != pstPppInfo)
             {
                 (VOID)PPP_ClearCB(pstPppInfo);
             }

             /* �Ƿ�ɾ��ppp���ƿ� */
             (VOID)PDN_L2tpUp(ulPdnIndex, pstMsg);
             break ;
         }
         case PPP_MSG_CODE_L2TP_DOWN:
         {
             L2TP_NOTIFY_PPPC_DOWN_INFO* pstL2tpDownMsg = pstMsg;
             PPP_INNER_COUNTER(PPP_INNER_COUTNER_009);

             PPP_DBG_OK_CNT(PPP_PHOK_1357);

             ulPdnIndex = PDN_PDNGlobalIndexToPDNScIndex(pstL2tpDownMsg->ulPdpindex);

             ulRet = SDB_GetPdnContextByIndex(ulPdnIndex, (UCHAR**)&pstPdnContext);
             if ((VOS_OK != ulRet) || (VOS_NULL_PTR == pstPdnContext))
             {
                 PPP_DBG_ERR_CNT(PPP_PHERR_653);
                 return ;
             }

             GETPPPINFOPTRBYRP(pstPppInfo, pstPdnContext->ulRpIndex);
             if (VOS_NULL_PTR != pstPppInfo)
             {
                 (VOID)PPP_NodeDelete(pstPdnContext->ulRpIndex);
             }
             else
             {
                 pstL2tpDownMsg->usFailReason = L2TP_DEA_CALL_BY_LNS;
             }

             (VOID)PDN_L2tpDown(ulPdnIndex, pstMsg);
             break ;
         }
         default:
         {
             PPP_DBG_ERR_CNT(PPP_PHERR_654);
             VOS_DBGASSERT(0);
             PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                                  "\r\n PPP_L2tpMsgProc: Proc l2tp msg faild! MsgCode[%d].",
                                  ulMsgCode);
             break;
         }
    }
#endif
    return;
}

 /*****************************************************************************
   �� �� ��  : PPP_Shell_NotifyL2tpUp
   ��������  : PPP֪ͨL2TP����L2tp���
   �������  : ULONG ulIndex
               L2TP_PPPPARA_S *pstPPPPara
   �������  : ��
   �� �� ֵ  : ULONG
   ���ú���  :
   ��������  :

   �޸���ʷ      :
    1.��    ��   : 2012��10��17��
      ��    ��   : luofang
      �޸�����   : �����ɺ���

  *****************************************************************************/
ULONG PPP_Shell_NotifyL2tpUp(ULONG ulIndex, L2TP_PPPPARA_S *pstPPPPara )
{
#if 0
    ULONG         ulResult = 0;
    SDB_RETURNCODE_E   enSdbReturn = SDB_SUCCESS;
    SDB_PDSN_RP_CONTEXT_S *pstContext = VOS_NULL_PTR;

    PPP_DBG_OK_CNT(PPP_PHOK_1358);
    PPP_DebugOut( ( ULONG )MID_PPPC, PPP_DEBUG_INFO, "\r\n PPP_NotifyL2tpUp: Call %lu up in.", ulIndex );

    if (VOS_NULL_PTR == pstPPPPara)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_655);
        PPP_DebugOut( ( ULONG )MID_PPPC, PPP_DEBUG_LOG, "\r\n PPP_NotifyL2tpUp: pstPPPPara is null" );
        return VOS_ERR;
    }

    enSdbReturn = (SDB_RETURNCODE_E)SDB_GetRpContextByIndex(ulIndex, ( UCHAR** )&pstContext );
    if ( ( SDB_SUCCESS != enSdbReturn   )  || ( VOS_NULL_PTR == pstContext  ) )
    {
        /* �������Ĳ����� */
        PPP_DebugOut( ( ULONG )MID_PPPC, PPP_DEBUG_LOG, "\r\n PPP_NotifyL2tpUp The PDP Context dose not exist %lu", enSdbReturn);
        PPP_DBG_ERR_CNT(PPP_PHERR_656);
        return VOS_ERR;
    }

    PPP_L2tpUpPreProc(pstPPPPara, pstContext,ulIndex);

    ulResult = PPP_SendMsgToL2tp(L2TP_MSGCODE_UP,
                                    (UCHAR *)pstPPPPara,
                                    sizeof(L2TP_PPPPARA_S));

    PPP_DebugOut( ( ULONG )MID_PPPC, PPP_DEBUG_INFO, "\r\n PPP_NotifyL2tpUp  exit %lu spu type %lu", ulResult, g_enPppBoardType);

    if (VOS_OK != ulResult)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_657);
        return VOS_ERR ;
    }

    PPP_DBG_OK_CNT(PPP_PHOK_1359);
#endif
    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : PPP_Shell_NotifyL2tpDown
 ��������  : PPPģ��֪ͨL2TPģ��Down
 �������  : ULONG ulRPIndex
 �������  : ��
 �� �� ֵ  : ULONG
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��8��
    ��    ��   : luofang
    �޸�����   : �����ɺ���

*****************************************************************************/
ULONG PPP_Shell_NotifyL2tpDown(PDN_CONTEXT_S *pstPdnContext, UCHAR ucMsgCode)
{
#if 0
    ULONG ulResult = VOS_OK;
    L2TP_DOWNPARA_S stL2tpDown = {0};

    stL2tpDown.ulPdpindex   = PDN_PDNScIndexToPDNGlobalIndex(pstPdnContext->ulPdnIndex);
    stL2tpDown.ulTeidc      = pstPdnContext->ulTeidc;
    stL2tpDown.ulGiifIndex  = pstPdnContext->stL2tp.ulIfIndex;
    stL2tpDown.usLocalTID   = pstPdnContext->stL2tp.usLocalTid;
    stL2tpDown.usLocalSID   = pstPdnContext->stL2tp.usLocalSid;
    stL2tpDown.ucScid       = (UCHAR)PPP_SELF_CMPIDXINSG;

    ulResult = PPP_SendMsgToL2tp(ucMsgCode,
                                    (UCHAR *)&stL2tpDown,
                                    sizeof(L2TP_DOWNPARA_S));

    if ( VOS_OK != ulResult )
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_658);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                    "\r\n [ppp]PPP_Shell_NotifyL2tpDown: PPP_SendMsgToL2tp error %u,%u",
                    ulResult, ucMsgCode);
        return VOS_ERR;
    }
#endif
    return VOS_OK;
}

/*****************************************************************************
�� �� ��  : PPP_L2tpUpPreProc
��������  :  ���������������L2TP����
�������  : L2TP_PPPPARA_S * pstPPPPara
           SDB_GSPU_CONTEXT_S *pstContext
�������  : ��
�� �� ֵ  : VOID
���ú���  :
��������  :

�޸���ʷ      :
1.��    ��   : 2012��10��17��
  ��    ��   : luofang
  �޸�����   : �����ɺ���

*****************************************************************************/
VOID PPP_L2tpUpPreProc(L2TP_PPPPARA_S * pstPPPPara, SDB_PDSN_RP_CONTEXT_S *psRpContext,ULONG ulIndex)
{
#if 0
    UCHAR szTempImsi[M_IMSI_LEN] = {0}; /*Imsi to string*/
    ULONG imsiLen = 0;
    ULONG i = 0;  /*IMSI Lenth*/
    CHAR szCallFromId[CALL_FROMID_LENTH] = {0};
    UCHAR aucMsisdn[A11_MSISDN_LEN] = {0};
    S_CFG_DOMAINNODE *pstDomain = VOS_NULL_PTR;
    UCHAR ucMDNFlag = 0;
    ULONG ulRet = 0;

    if ((VOS_NULL_PTR == pstPPPPara) || (VOS_NULL_PTR == psRpContext))
    {
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\nPPP_L2tpUpPreProc input para is null");
        return;
    }


    ImsiToString(psRpContext->stImsi, szTempImsi);     /*Convert IMSI to string for variable IMSI*/

    ulRet = A11_GetDomainByIndex(psRpContext->usDomainIndex, &pstDomain);
    if (VOS_OK != ulRet)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_659);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG, "\r\nPPP_L2tpUpPreProc Get Domain configure fail!");
        return;
    }

    ucMDNFlag = pstDomain->ucL2tpAttribute;

    if((HSGW_DOMAIN_L2TP_ATTRIBUTE_MDN == ucMDNFlag) && (VOS_TRUE == psRpContext->ucMsisdnFlag)) /* �ж�AAA�Ƿ��·��˸��ֶ� */
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1360);
        A11_BCDToString(psRpContext->szMsisdn, aucMsisdn, 15);
        PTM_StrNCpy(pstPPPPara->stSessionInfo.szDialingNumber, aucMsisdn, L2TP_DIALINGNUM_LEN-1);
    }
    else
    {
        /*ȡIMSI��Ϊ�û����룬18����ο���*/
        if (g_ulSoftPara534 & 0x01)
        {
            PPP_DBG_OK_CNT(PPP_PHOK_1361);
            VOS_MemCpy(pstPPPPara->stSessionInfo.szDialingNumber, szTempImsi,
            VOS_StrLen((CHAR *)szTempImsi));
        }
        else
        {
            imsiLen = VOS_StrLen((CHAR *)szTempImsi);
            if ((imsiLen >= 10) && (imsiLen <= 15))
            {
                for (i = 0; i < 10; i++)
                {
                    szCallFromId[i] = (CHAR)szTempImsi[i + imsiLen - 10];
                }

                szCallFromId[10] = '\0';
                VOS_StrCpy(pstPPPPara->stSessionInfo.szDialingNumber, szCallFromId);
            }
            else
            {
                PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n PPP_L2tpUpPreProc IMSI Length Error: %d \r\n", imsiLen);
            }
        }
    }

    VOS_StrCpy(pstPPPPara->stSessionInfo.szDialedNumber, "8888");

    pstPPPPara->stSessionInfo.bBearTypeUsed = VOS_TRUE;
    pstPPPPara->stSessionInfo.ulBearType = BEARER_TYPE_BOTH;
    pstPPPPara->stSessionInfo.ulFramType = FRAMING_TYPE_BOTH;
    pstPPPPara->stSessionInfo.bPrivateGroupIdUsed = VOS_TRUE;
#endif
    return;
}
VOS_UINT32 PPP_Shell_L2tpProc(ULONG ulRpIdx, L2TP_PPPPARA_S *pstL2tpPara)
{
    PPPLCPINFO_S *pstLcpInfo = VOS_NULL_PTR;
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;  /*PDSN��ָ��PPP���ƿ��ָ��*/

    if (VOS_NULL_PTR == pstL2tpPara)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_660);
        return VOS_ERR;
    }

    /* ��ȡPPPC���ƿ�ָ��*/
    GETPPPINFOPTRBYRP(pstPppInfo, ulRpIdx);
    if (VOS_NULL_PTR == pstPppInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_661);
        return VOS_ERR;
    }

    if (VOS_NULL_PTR == pstPppInfo->pL2tpPara)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_662);
        return VOS_ERR;
    }

    VOS_MemCpy(&(pstL2tpPara->stSessionInfo),
                pstPppInfo->pL2tpPara,
                sizeof(L2TP_SESSIONPARA_S));

    pstL2tpPara->stSessionInfo.bLcpOptionUsed   = VOS_TRUE;
    pstL2tpPara->stSessionInfo.bProxyAuthenUsed = VOS_TRUE;

    /*��l2tp�û�,֪ͨl2tp up*/
    /* ֪ͨL2TP������� */

    pstLcpInfo = (PPPLCPINFO_S*)pstPppInfo->pstLcpInfo;
    if (VOS_NULL_PTR == pstLcpInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_663);
        return VOS_ERR;
    }

    if (pstLcpInfo->stGotOptions.neg_chap)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1362);
        PPP_PerfInc(&g_stPppPerfStatistic.ulChapSuccess, PERF_TYPE_PPPC_CHAP_AUTHEN_SUCC_NUM, pstPppInfo->bEhrpdUser);
    }
    else if (pstLcpInfo->stGotOptions.neg_upap)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1363);
        PPP_PerfInc(&g_stPppPerfStatistic.ulPapSuccess, PERF_TYPE_PPPC_PAP_AUTHEN_SUCC_NUM, pstPppInfo->bEhrpdUser);
    }
    else
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1364);
        PPP_Debug_CoreEvent(pstPppInfo, PPP_LOG_ERROR, "PPP_Shell_L2tpProc: Receive unexpected message!!");
    }


    PPP_SNMP_PERF_SET_SUCCESS(pstPppInfo);

    if (VOS_ERR == PPP_Shell_NotifyL2tpUp(pstPppInfo->ulRPIndex, pstL2tpPara))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_664);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n PPP_Shell_ReceiveAAAResult: PPP_Shell_NotifyL2tpUp failed");
        pstPppInfo->bFailFlag = PPPL2TPDOWN;
        /* PPP_LCP_NegotiationDown(pstPppInfo->pstLcpInfo); */
        return VOS_ERR;
    }

    PPP_DBG_OK_CNT(PPP_PHOK_1365);
    pstPppInfo->bAuthFlag = VOS_TRUE;
    pstPppInfo->bPppSuccess = 1;

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : PPP_SendMsgToL2tp
 ��������  : ������Ϣ��LAC�߳�
 �������  : UCHAR ucMsgCode
             UCHAR* pucMsg
             ULONG ulMsgLen
 �������  : ��
 �� �� ֵ  : ULONG
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��19��
    ��    ��   : luofang
    �޸�����   : �����ɺ���

*****************************************************************************/
ULONG PPP_SendMsgToL2tp(UCHAR ucMsgCode, UCHAR* pucMsg, ULONG ulMsgLen )
{
#if 0
    ULONG ulRet = VOS_OK;

    if (VOS_NULL_PTR == pucMsg)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_665);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n [ppp]PPP_SendMsgToL2tp : Input ptr is null");
        return VOS_ERR;
    }

    if (CRM_BOARD_TYPE_SPUD == g_enPppBoardType)    /*SPUD��*/
    {
        ulRet = PPP_SendRtMsg(PPP_SELF_CSI, g_ullPppLocalL2tpCsi, L2TP_MSG_TYPE_PPPC, ucMsgCode, pucMsg, ulMsgLen);
        if ( VOS_OK != ulRet )
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_666);
            PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG ,
                        "\r\n %s:  PPP_SendMsgToL2tp error, the ret = 0x%lx, msgcode %d. ",
                        (CHAR *)(__FUNCTION__), ulRet, ucMsgCode );
            return VOS_ERR;
        }
    }
    else
    {
        ulRet = PPP_SendURTMsg(g_ullPppLocalL2tpCsi, L2TP_MSG_TYPE_FCM, ucMsgCode, pucMsg, ulMsgLen);
        if (VOS_OK != ulRet)
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_667);
            PPP_DebugOut( MID_PPPC, PPP_DEBUG_LOG,
                        "\r\n PPP_SendMsgToL2tp: Call PPP_SendURTMsg ret %lu msgcode %d.", ulRet, ucMsgCode);
            return VOS_ERR;
        }
    }

    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                "\r\n PPP_SendMsgToL2tp:  send message to lac succ. ");
#endif
    return VOS_OK ;
}


/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
