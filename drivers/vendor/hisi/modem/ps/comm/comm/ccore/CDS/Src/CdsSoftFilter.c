


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "CDS.h"
#include "CdsSoftFilter.h"
#include "CdsIpfCtrl.h"
#include "CdsDebug.h"

/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_CDS_SOFT_FILTER_C
/*lint +e767*/

/*****************************************************************************
  2 �ⲿ��������
*****************************************************************************/

extern VOS_UINT32 CDS_IpFragmentProc( VOS_UINT8              *pucEpsbID,
                                             TTF_MEM_ST             *pstIpPkt,
                                             const IPF_RESULT_STRU  *pstIpfRslt,
                                             const CDS_ENTITY_STRU  *pstCdsEntity);

/******************************************************************************
   3 ˽�ж���
******************************************************************************/


/******************************************************************************
   4 ȫ�ֱ�������
******************************************************************************/


/******************************************************************************
   5 ����ʵ��
******************************************************************************/


VOS_UINT32 CDS_IsIpv4FragInfoEq(const CDS_IP_DATA_INFO_STRU *pstSrc,
                                      const CDS_IP_DATA_INFO_STRU *pstTarget)
{
    CDS_ASSERT_RTN(VOS_NULL_PTR != pstSrc, PS_FALSE);
    CDS_ASSERT_RTN(VOS_NULL_PTR != pstTarget, PS_FALSE);

    if (IP_VERSION_V4 != pstSrc->ucIpVersion)
    {
        return PS_FALSE;
    }

    if (pstSrc->ulIpIdentity != pstTarget->ulIpIdentity)
    {
        return PS_FALSE;
    }

    if (pstSrc->unIpv4SrcAddr.ulIpAddr != pstTarget->unIpv4SrcAddr.ulIpAddr)
    {
        return PS_FALSE;
    }

    if (pstSrc->unIpv4DestAddr.ulIpAddr != pstTarget->unIpv4DestAddr.ulIpAddr)
    {
        return PS_FALSE;
    }

    return PS_TRUE;
}


VOS_UINT32 CDS_IsIpv6FragInfoEq(const CDS_IP_DATA_INFO_STRU *pstSrc,
                                      const CDS_IP_DATA_INFO_STRU *pstTarget)
{
    CDS_ASSERT_RTN(VOS_NULL_PTR != pstSrc, PS_FALSE);
    CDS_ASSERT_RTN(VOS_NULL_PTR != pstTarget, PS_FALSE);

    if (IP_VERSION_V6 != pstSrc->ucIpVersion)
    {
        return PS_FALSE;
    }

    if (pstSrc->ulIpIdentity != pstTarget->ulIpIdentity)
    {
        return PS_FALSE;
    }

    if (PS_FALSE == CDS_Ipv6AddrEqual(&(pstSrc->unIpv6DestAddr),&(pstTarget->unIpv6DestAddr)))
    {
        return PS_FALSE;
    }

    if (PS_FALSE == CDS_Ipv6AddrEqual(&(pstSrc->unIpv6SrcAddr),&(pstTarget->unIpv6SrcAddr)))
    {
        return PS_FALSE;
    }

    return PS_TRUE;
}


VOS_UINT32 CDS_Ipv4MaskedAddrCmp(const IPV4_ADDR_UN *a1, const IPV4_ADDR_UN *m, const IPV4_ADDR_UN *a2)
{
    return (!!((a1->ulIpAddr ^ a2->ulIpAddr) & m->ulIpAddr));
}


VOS_UINT32 CDS_IPFragmentType(VOS_UINT16 usMF, VOS_UINT16 usFragOffset)
{

    if (usMF)
    {
        if (0 == usFragOffset)
        {
            return CDS_UL_IPF_IPSEG_TYPE_FRAGMENT_HEAD;
        }
        else
        {
            return CDS_UL_IPF_IPSEG_TYPE_FRAGMENT_MID;
        }
    }
    else
    {
        if (0 == usFragOffset)
        {
            return CDS_UL_IPF_IPSEG_TYPE_NO_FRAGMENT;
        }
        else
        {
            return CDS_UL_IPF_IPSEG_TYPE_FRAGMENT_TAIL;
        }
    }

}


VOS_VOID CDS_DecodeIPSecHdr(const TTF_MEM_ST *pstIpPkt, CDS_IP_DATA_INFO_STRU *pstIpInfo)
{
    AH_HDR_STRU     *pstAhHdr;
    VOS_UINT32       ulAhHdrLen;
    ESP_HDR_STRU    *pstEspHdr;

    /*AH*/
    /*������AH���п��ܼ�������ESP*/
    if (IPV4_PROTOCOL_AUTH == pstIpInfo->ucNextHdr)
    {
        pstAhHdr = (AH_HDR_STRU *)((VOS_UINT32)(pstIpPkt->pData + pstIpInfo->ulHdrLen));
        pstIpInfo->ulAhSpi = IP_NTOHL(pstAhHdr->ulSPI);
        if (IPV4_PROTOCOL_ESP != pstAhHdr->ucNextHdr)
        {
            return;
        }

        /*��������ESP*/
        pstIpInfo->ucNextHdr = pstAhHdr->ucNextHdr;
        ulAhHdrLen = (pstAhHdr->ucHdrLen + 2) << 2;
        pstIpInfo->ulHdrLen = pstIpInfo->ulHdrLen + ulAhHdrLen;
    }

    /*ESP*/
    if (IPV4_PROTOCOL_ESP == pstIpInfo->ucNextHdr)
    {
        pstEspHdr = (ESP_HDR_STRU *)((VOS_UINT32)(pstIpPkt->pData + pstIpInfo->ulHdrLen));
        pstIpInfo->ulEspSpi = IP_NTOHL(pstEspHdr->ulSPI);
    }

    return ;
}


VOS_VOID CDS_DecodeTransportLayer(const TTF_MEM_ST *pstIpPkt, CDS_IP_DATA_INFO_STRU *pstIpInfo)
{

    UDP_HDR_STRU        *pstUdpHdr;
    TCP_HDR_STRU        *pstTcpHdr;
    ESP_HDR_STRU        *pstEspHdr;

    if (IPV4_PROTOCOL_UDP == pstIpInfo->ucNextHdr)
    {
        /*����UDPͷ*/
        pstUdpHdr = (UDP_HDR_STRU *)((VOS_UINT32)(pstIpPkt->pData + pstIpInfo->ulHdrLen));
        pstIpInfo->usSrcPort  = IP_NTOHS(pstUdpHdr->usSrcPort);
        pstIpInfo->usDestPort = IP_NTOHS(pstUdpHdr->usDstPort);

        if (IPSEC_NAT_TRAVERSAL_UDP_PORT == pstIpInfo->usDestPort)
        {
            /*����IPSEC NAT-Tģʽ�µ�SPIֵ*//*ƫ�Ƶ�UDPͷ��*/
            pstEspHdr = (ESP_HDR_STRU *)((VOS_UINT32)(pstUdpHdr + 1));
            pstIpInfo->ulEspSpi = IP_NTOHL(pstEspHdr->ulSPI);
            return;
        }
    }
    else if (IPV4_PROTOCOL_TCP == pstIpInfo->ucNextHdr)
    {
        /*����TCPͷ*/
        pstTcpHdr = (TCP_HDR_STRU *)((VOS_UINT32)(pstIpPkt->pData + pstIpInfo->ulHdrLen));
        pstIpInfo->usSrcPort  = IP_NTOHS(pstTcpHdr->usSrcPort);
        pstIpInfo->usDestPort = IP_NTOHS(pstTcpHdr->usDstPort);
    }
    else
    {
        /*nothing for pc-lint*/
    }

    return ;
}


VOS_VOID CDS_DecodeIpv4Hdr(const TTF_MEM_ST *pstIpPkt, CDS_IP_DATA_INFO_STRU *pstIpInfo)
{
    IPV4_HDR_STRU      *pstIpv4Hdr;
    VOS_UINT16          usMoreFragFlg;
    VOS_UINT16          usFragOffset;

    /*����IPͷ����Ϣ*/
    pstIpv4Hdr = (IPV4_HDR_STRU *)((VOS_UINT32)(pstIpPkt->pData));
    pstIpInfo->ucNextHdr      = pstIpv4Hdr->ucProtocol;
    pstIpInfo->ucServiceType  = pstIpv4Hdr->ucServiceType;
    pstIpInfo->ulHdrLen       = pstIpv4Hdr->ucIpHdrLen << 2;
    pstIpInfo->unIpv4SrcAddr.ulIpAddr  = pstIpv4Hdr->unSrcAddr.ulIpAddr;
    pstIpInfo->unIpv4DestAddr.ulIpAddr = pstIpv4Hdr->unDestAddr.ulIpAddr;
    pstIpInfo->ulIpIdentity   = IP_NTOHS(pstIpv4Hdr->usIdentification);
    pstIpInfo->ucIpVersion    = IP_VERSION_V4;

    /*��Ƭ����*/
    usFragOffset  = IP_NTOHS(pstIpv4Hdr->usOffset) & IPV4_OFFSET_MASK;
    usMoreFragFlg = !!(IP_NTOHS(pstIpv4Hdr->usOffset) & IPV4_MF_MASK);

    pstIpInfo->ucIpSegType = (VOS_UINT8)CDS_IPFragmentType(usMoreFragFlg, usFragOffset);

    return ;
}



VOS_UINT32 CDS_IsIPSecPacket(VOS_UINT8 ucProtocol)
{
    return (VOS_UINT32)((IPV4_PROTOCOL_AUTH == ucProtocol) || (IPV4_PROTOCOL_ESP == ucProtocol));
}


VOS_VOID CDS_DecodeIpv4Packet(const TTF_MEM_ST *pstIpPkt, CDS_IP_DATA_INFO_STRU *pstIpInfo)
{

    /*����IPv4ͷ*/
    CDS_DecodeIpv4Hdr(pstIpPkt,pstIpInfo);

    /*IP�м��Ƭ��β��Ƭ, ���ٽ��������Э��*/
    if ((CDS_UL_IPF_IPSEG_TYPE_FRAGMENT_MID == pstIpInfo->ucIpSegType)
        || (CDS_UL_IPF_IPSEG_TYPE_FRAGMENT_TAIL == pstIpInfo->ucIpSegType))
    {
        return ;
    }

    /*IPSec���ݰ���ֻ����SPI���������ٽ���*/
    if (PS_TRUE == CDS_IsIPSecPacket(pstIpInfo->ucNextHdr))
    {
        CDS_DecodeIPSecHdr(pstIpPkt,pstIpInfo);
        return ;
    }

    CDS_DecodeTransportLayer(pstIpPkt,pstIpInfo);

    return ;
}
VOS_UINT32 CDS_Ipv6AddrEqual(const IPV6_ADDR_UN *a1, const IPV6_ADDR_UN *a2)
{
    return (0 == ( (a1->aulIpAddr[0] ^ a2->aulIpAddr[0]) |
                    (a1->aulIpAddr[1] ^ a2->aulIpAddr[1]) |
                    (a1->aulIpAddr[2] ^ a2->aulIpAddr[2]) |
                    (a1->aulIpAddr[3] ^ a2->aulIpAddr[3])));
}


VOS_UINT32 CDS_Ipv6MaskedAddrCmp(const IPV6_ADDR_UN *a1, const IPV6_ADDR_UN *m, const IPV6_ADDR_UN *a2)
{

    return (!!(((a1->aulIpAddr[0] ^ a2->aulIpAddr[0]) & m->aulIpAddr[0])
                    | ((a1->aulIpAddr[1] ^ a2->aulIpAddr[1]) & m->aulIpAddr[1])
                    | ((a1->aulIpAddr[2] ^ a2->aulIpAddr[2]) & m->aulIpAddr[2])
                    | ((a1->aulIpAddr[3] ^ a2->aulIpAddr[3]) & m->aulIpAddr[3])));

}


VOS_UINT32 CDS_Ipv6ExtHdr(VOS_UINT8 ucNextHdr)
{
    return (VOS_UINT32)((IPV6_NEXTHDR_HOP == ucNextHdr)
            || (IPV6_NEXTHDR_ROUTING  == ucNextHdr)
            || (IPV6_NEXTHDR_FRAGMENT == ucNextHdr)
            || (IPV6_NEXTHDR_ESP == ucNextHdr)
            || (IPV6_NEXTHDR_AUTH == ucNextHdr)
            || (IPV6_NEXTHDR_NONE == ucNextHdr)
            || (IPV6_NEXTHDR_DEST == ucNextHdr));
}


VOS_VOID CDS_DecodeIpv6Hdr(const TTF_MEM_ST *pstIpPkt, CDS_IP_DATA_INFO_STRU *pstIpInfo)
{
    IPV6_HDR_STRU       *pstIpv6Hdr;

    /*��IPͷ�л�ȡ������Ϣ*/
    pstIpv6Hdr = (IPV6_HDR_STRU *)((VOS_UINT32)pstIpPkt->pData);
    pstIpInfo->ucTrafficClass = IPV6_TRAFFIC_CLASS(pstIpv6Hdr);
    pstIpInfo->ulFlowLable    = IPV6_FLOW_LABLE(pstIpv6Hdr);
    pstIpInfo->ucNextHdr      = pstIpv6Hdr->ucNextHdr;
    pstIpInfo->ulHdrLen       = IPV6_HDR_LEN;
    pstIpInfo->ucIpVersion    = IP_VERSION_V6;
    PS_MEM_CPY(&(pstIpInfo->unIpv6SrcAddr),&(pstIpv6Hdr->unSrcAddr),IPV6_ADDR_LEN);
    PS_MEM_CPY(&(pstIpInfo->unIpv6DestAddr),&(pstIpv6Hdr->unDstAddr),IPV6_ADDR_LEN);
    return ;
}
VOS_VOID CDS_DecodeIpv6ExtHdr(const TTF_MEM_ST *pstIpPkt, CDS_IP_DATA_INFO_STRU *pstIpInfo)
{
    VOS_UINT8              ucNextHdr;
    IPV6_FRAGMENT_HDR     *pstFragHdr;
    IPV6_OPTION_HDR       *pstOptHdr;
    VOS_UINT16             usMF;
    VOS_UINT16             usFragOffset;
    VOS_UINT32             ulOptLen;
    VOS_UINT32             ulHdrLen;
    IPV6_HDR_STRU         *pstIpv6Hdr;
    AH_HDR_STRU           *pstAhHdr;
    ESP_HDR_STRU          *pstEspHdr;

    /*���IPv6ͷ�е���Ϣ*/
    pstIpv6Hdr = (IPV6_HDR_STRU *)((VOS_UINT32)(pstIpPkt->pData));
    ucNextHdr  = pstIpv6Hdr->ucNextHdr;
    ulHdrLen   = sizeof(IPV6_HDR_STRU);

    /*����������չͷ*/
    while (CDS_Ipv6ExtHdr(ucNextHdr))
    {
        if (IPV6_NEXTHDR_NONE == ucNextHdr)
        {
            break;
        }
        else if (IPV6_NEXTHDR_ESP == ucNextHdr)
        {
            pstEspHdr = (ESP_HDR_STRU *)((VOS_UINT32)(pstIpPkt->pData + ulHdrLen));
            pstIpInfo->ulEspSpi = IP_NTOHL(pstEspHdr->ulSPI);
            break;
        }
        else if (IPV6_NEXTHDR_AUTH == ucNextHdr)
        {
            pstAhHdr = (AH_HDR_STRU *)((VOS_UINT32)(pstIpPkt->pData + ulHdrLen));
            pstIpInfo->ulAhSpi = IP_NTOHL(pstAhHdr->ulSPI);
            /*�����ΪESP�����ٶ�ȡ����������չͷ*/
            if (IPV6_NEXTHDR_ESP != pstAhHdr->ucNextHdr)
            {
                break;
            }

            /*NextHdrΪESP�����������ֶ�*/
            ucNextHdr = pstAhHdr->ucNextHdr;
            ulOptLen  = (pstAhHdr->ucHdrLen + 2) << 2;
            ulHdrLen  = ulHdrLen + ulOptLen;

        }
        else if (IPV6_NEXTHDR_FRAGMENT == ucNextHdr)
        {
            pstFragHdr = (IPV6_FRAGMENT_HDR *)((VOS_UINT32)(pstIpPkt->pData + ulHdrLen));

            /*get ip segments offset by MF and fragment offset*/
            usMF         = IP_NTOHS(pstFragHdr->usFragOffset) & IPV6_MF_MASK;
            usFragOffset = IP_NTOHS(pstFragHdr->usFragOffset) & IPV6_OFFSET_MASK;
            pstIpInfo->ucIpSegType  = (VOS_UINT8)CDS_IPFragmentType(usMF,usFragOffset);
            pstIpInfo->ulIpIdentity = IP_NTOHL(pstFragHdr->ulIdentification);

            ucNextHdr  = pstFragHdr->ucNextHdr;
            ulOptLen   = sizeof(IPV6_FRAGMENT_HDR);
            ulHdrLen   = ulHdrLen + ulOptLen;
            /*��ͷ��Ƭ�����ټ�����ͷ*/
            if (CDS_UL_IPF_IPSEG_TYPE_FRAGMENT_HEAD != pstIpInfo->ucIpSegType)
            {
                break;
            }
        }
        else
        {
            pstOptHdr = (IPV6_OPTION_HDR*)((VOS_UINT32)(pstIpPkt->pData + ulHdrLen));
            ucNextHdr = pstOptHdr->ucNextHdr;
            ulOptLen  = IPV6_OPTION_LEN(pstOptHdr);
            ulHdrLen  = ulHdrLen + ulOptLen;
        }

    }

    /*����NextHdr��HdrLen*/
    pstIpInfo->ucNextHdr = ucNextHdr;
    pstIpInfo->ulHdrLen  = ulHdrLen;

    return;
}
VOS_VOID CDS_DecodeIpv6Packet(const TTF_MEM_ST *pstIpPkt, CDS_IP_DATA_INFO_STRU *pstIpInfo)
{

    /*����IPv4ͷ*/
    CDS_DecodeIpv6Hdr(pstIpPkt,pstIpInfo);

    /*������չͷ��������չͷ.����IP�ֶΡ�AH��ESP��*/
    if (PS_TRUE == CDS_Ipv6ExtHdr(pstIpInfo->ucNextHdr))
    {
        CDS_DecodeIpv6ExtHdr(pstIpPkt,pstIpInfo);
    }

    /*IP�м��Ƭ��β��Ƭ, ���ٽ��������Э��*/
    if ((CDS_UL_IPF_IPSEG_TYPE_FRAGMENT_MID == pstIpInfo->ucIpSegType)
        || (CDS_UL_IPF_IPSEG_TYPE_FRAGMENT_TAIL == pstIpInfo->ucIpSegType))
    {
        return ;
    }

    CDS_DecodeTransportLayer(pstIpPkt,pstIpInfo);

    return ;
}
VOS_UINT32 CDS_MatchIpv4SrcAddr(IPV4_ADDR_UN  unSrcAddr, const CDS_SOFTFILTER_INFO_STRU *pstSoftFilter)
{

    /*û�������ù�����������Ĭ��ƥ��ɹ�*/
    if (PS_TRUE != pstSoftFilter->bitOpLcIpv4AddrAndMask)
    {
        return PS_SUCC;
    }

    if (0 == CDS_Ipv4MaskedAddrCmp(&unSrcAddr,
                                    &(pstSoftFilter->unLocalIpv4Mask),
                                    &(pstSoftFilter->unLocalIpv4Addr)))
    {
        return PS_SUCC;
    }
    else
    {
        return PS_FAIL;
    }

}
VOS_UINT32 CDS_MatchIpv4DestAddr(IPV4_ADDR_UN unDestAddr, const CDS_SOFTFILTER_INFO_STRU *pstSoftFilter)
{

    /*û�������ù�����������Ĭ��ƥ��ɹ�*/
    if (PS_TRUE != pstSoftFilter->bitOpRmtIpv4AddrAndMask)
    {
        return PS_SUCC;
    }

    if (0 == CDS_Ipv4MaskedAddrCmp(&unDestAddr,
                                   &(pstSoftFilter->unRmtIpv4Mask),
                                   &(pstSoftFilter->unRmtIpv4Addr)))
    {
        return PS_SUCC;
    }
    else
    {
        return PS_FAIL;
    }

}
VOS_UINT32 CDS_MatchServiceType(VOS_UINT8  ucServiceType, const CDS_SOFTFILTER_INFO_STRU *pstSoftFilter)
{

    if (PS_TRUE != pstSoftFilter->bitOpTypeOfService)
    {
        return PS_SUCC;
    }

    if ((ucServiceType & pstSoftFilter->ucTypeOfServiceMask)
         == (pstSoftFilter->ucTypeOfService & pstSoftFilter->ucTypeOfServiceMask))
    {
        return PS_SUCC;
    }

    return PS_FAIL;
}



VOS_UINT32 CDS_MatchIpv6SrcAddr(const IPV6_ADDR_UN  *pstSrcAddr, const CDS_SOFTFILTER_INFO_STRU *pstSoftFilter)
{
    if (PS_TRUE != pstSoftFilter->bitOpLcIpv6AddrAndMask)
    {
        return PS_SUCC;
    }

    if(0 == CDS_Ipv6MaskedAddrCmp(pstSrcAddr,
                                 &(pstSoftFilter->unLocalIpv6Mask),
                                 &(pstSoftFilter->unLocalIpv6Addr)))
    {
        return PS_SUCC;
    }


    return PS_FAIL;
}


VOS_UINT32 CDS_MatchIpv6DestAddr(const IPV6_ADDR_UN *pstDestAddr, const CDS_SOFTFILTER_INFO_STRU *pstSoftFilter)
{

    if (PS_TRUE != pstSoftFilter->bitOpRmtIpv6AddrAndMask)
    {
        return PS_SUCC;
    }

    if(0 == CDS_Ipv6MaskedAddrCmp(pstDestAddr,
                                 &(pstSoftFilter->unRmtIpv6Mask),
                                 &(pstSoftFilter->unRmtIpv6Addr)))
    {
        return PS_SUCC;
    }

    return PS_FAIL;
}


VOS_UINT32 CDS_MatchIpv6FlowLable(VOS_UINT32   ulFlowLabel, const CDS_SOFTFILTER_INFO_STRU *pstSoftFilter)
{
    if (PS_TRUE != pstSoftFilter->bitOpFlowLabelType)
    {
        return PS_SUCC;
    }

    if ((ulFlowLabel & IPV6_FLOW_LABLE_MASK)
          == (pstSoftFilter->ulFlowLabelType & IPV6_FLOW_LABLE_MASK))
    {
        return PS_SUCC;
    }
    else
    {
        return PS_FAIL;
    }
}


VOS_UINT32 CDS_MatchIpProtocol(VOS_UINT8 ucProtocol, const CDS_SOFTFILTER_INFO_STRU *pstSoftFilter)
{
    if (PS_TRUE != pstSoftFilter->bitOpProtocolId)
    {
        return PS_SUCC;
    }

    if (ucProtocol == pstSoftFilter->ucProtocolId)
    {
        return PS_SUCC;
    }
    else
    {
        return PS_FAIL;
    }
}


VOS_UINT32 CDS_MatchIPSecSPI(const CDS_IP_DATA_INFO_STRU *pstIpInfo, const CDS_SOFTFILTER_INFO_STRU *pstSoftFilter)
{
    if (PS_TRUE != pstSoftFilter->bitOpSecuParaIndex)
    {
        return PS_SUCC;
    }

    /*�ȱȽ�AH SPI*/
    if (pstIpInfo->ulAhSpi == pstSoftFilter->ulSecuParaIndex)
    {
        return PS_SUCC;
    }

    /*�ٱȽ�ESP SPI*/
    if (pstIpInfo->ulEspSpi == pstSoftFilter->ulSecuParaIndex)
    {
        return PS_SUCC;
    }

    return PS_FAIL;
}


VOS_UINT32 CDS_MatchSrcPort(VOS_UINT16 usSrcPort, const CDS_SOFTFILTER_INFO_STRU *pstSoftFilter)
{
    /*��Դ�˿�*/
    if (PS_TRUE == pstSoftFilter->bitOpSingleLocalPort)
    {
        if (usSrcPort == pstSoftFilter->usSingleLcPort)
        {
            return PS_SUCC;
        }
        else
        {
            return PS_FAIL;
        }
    }

    /*��Դ�˿�*/
    if (PS_TRUE == pstSoftFilter->bitOpLocalPortRange)
    {
        if ((usSrcPort >= pstSoftFilter->usLcPortLowLimit)
             && (usSrcPort <= pstSoftFilter->usLcPortHighLimit))
        {
            return PS_SUCC;
        }
        else
        {
            return PS_FAIL;
        }
    }

    return PS_SUCC;
}


VOS_UINT32 CDS_MatchDestPort(VOS_UINT16 usDestPort, const CDS_SOFTFILTER_INFO_STRU *pstSoftFilter)
{
    /*��Ŀ�Ķ˿�*/
    if (PS_TRUE == pstSoftFilter->bitOpSingleRemotePort)
    {
        if (usDestPort == pstSoftFilter->usSingleRmtPort)
        {
            return PS_SUCC;
        }
        else
        {
            return PS_FAIL;
        }
    }

    /*��Ŀ�Ķ˿�*/
    if (PS_TRUE == pstSoftFilter->bitOpRemotePortRange)
    {
        if ((usDestPort >= pstSoftFilter->usRmtPortLowLimit)
             && (usDestPort <= pstSoftFilter->usRmtPortHighLimit))
        {
            return PS_SUCC;
        }
        else
        {
            return PS_FAIL;
        }
    }

    return PS_SUCC;
}


VOS_UINT32 CDS_MatchIpv4SoftFilter(const CDS_IP_DATA_INFO_STRU *pstIpInfo, const CDS_SOFTFILTER_INFO_STRU *pstSoftFilter)
{
    /*ƥ��ԴIPv4��ַ*/
    if (PS_SUCC != CDS_MatchIpv4SrcAddr(pstIpInfo->unIpv4SrcAddr, pstSoftFilter))
    {
        return PS_FAIL;
    }

    /*ƥ��Ŀ��IPv4��ַ*/
    if (PS_SUCC != CDS_MatchIpv4DestAddr(pstIpInfo->unIpv4DestAddr, pstSoftFilter))
    {
        return PS_FAIL;
    }

    /*ƥ��SPI*/
    if (PS_SUCC != CDS_MatchIPSecSPI(pstIpInfo, pstSoftFilter))
    {
        return PS_FAIL;
    }

    /*ƥ��Э���*/
    if (PS_SUCC != CDS_MatchIpProtocol(pstIpInfo->ucNextHdr, pstSoftFilter))
    {
        return PS_FAIL;
    }

    /*ƥ��Service Type*/
    if (PS_SUCC != CDS_MatchServiceType(pstIpInfo->ucServiceType, pstSoftFilter))
    {
        return PS_FAIL;
    }

    /*ƥ��Դ�˿ں�*/
    if (PS_SUCC != CDS_MatchSrcPort(pstIpInfo->usSrcPort, pstSoftFilter))
    {
        return PS_FAIL;
    }

    /*ƥ��Ŀ�Ķ˿ں�*/
    if (PS_SUCC != CDS_MatchDestPort(pstIpInfo->usDestPort, pstSoftFilter))
    {
        return PS_FAIL;
    }

    return PS_SUCC;
}
VOS_UINT32 CDS_MatchIpv6SoftFilter(const CDS_IP_DATA_INFO_STRU *pstIpInfo, const CDS_SOFTFILTER_INFO_STRU *pstSoftFilter)
{
    /*ƥ��ԴIPv6��ַ*/
    if (PS_SUCC != CDS_MatchIpv6SrcAddr(&(pstIpInfo->unIpv6SrcAddr), pstSoftFilter))
    {
        return PS_FAIL;
    }

    /*ƥ��Ŀ��IPv6��ַ*/
    if (PS_SUCC != CDS_MatchIpv6DestAddr(&(pstIpInfo->unIpv6DestAddr), pstSoftFilter))
    {
        return PS_FAIL;
    }

    /*ƥ��SPI*/
    if (PS_SUCC != CDS_MatchIPSecSPI(pstIpInfo, pstSoftFilter))
    {
        return PS_FAIL;
    }

    /*ƥ��FlowLable*/
    if (PS_SUCC != CDS_MatchIpv6FlowLable(pstIpInfo->ulFlowLable, pstSoftFilter))
    {
        return PS_FAIL;
    }

    /*ƥ��NextHdr*/
    if (PS_SUCC != CDS_MatchIpProtocol(pstIpInfo->ucNextHdr, pstSoftFilter))
    {
        return PS_FAIL;
    }

    /*ƥ��Service Type*/
    if (PS_SUCC != CDS_MatchServiceType(pstIpInfo->ucTrafficClass, pstSoftFilter))
    {
        return PS_FAIL;
    }

    /*ƥ��Դ�˿ں�*/
    if (PS_SUCC != CDS_MatchSrcPort(pstIpInfo->usSrcPort, pstSoftFilter))
    {
        return PS_FAIL;
    }

    /*ƥ��Ŀ�Ķ˿ں�*/
    if (PS_SUCC != CDS_MatchDestPort(pstIpInfo->usDestPort, pstSoftFilter))
    {
        return PS_FAIL;
    }

    return PS_SUCC;
}


VOS_UINT32 CDS_Ipv4PktSoftFilter(const TTF_MEM_ST *pstIpPkt, IPF_RESULT_STRU *pstIpfResult, const CDS_ENTITY_STRU *pstCdsEntity)
{
    CDS_IP_DATA_INFO_STRU           stIpInfo        = {0};
    CDS_SOFTFILTER_INFO_STRU       *pstSoftFilter   = VOS_NULL_PTR;
    VOS_UINT32                      ulCnt;

    /*����IPv4���ݰ�*/
    CDS_DecodeIpv4Packet(pstIpPkt,&stIpInfo);

    /*�������������*/
    for (ulCnt = 0; ulCnt < pstCdsEntity->ulUlSoftFilterNum; ulCnt ++)
    {
        pstSoftFilter = (CDS_SOFTFILTER_INFO_STRU *)(&(pstCdsEntity->astUlSoftFilter[ulCnt]));

        /*�����ΪIPv4����ִ����һ��������*/
        if (CDS_SOFTFILTER_TYPE_IPV4 != pstSoftFilter->enFilterType)
        {
            continue;
        }

        /*ƥ��IPv4 TFT������*/
        if (PS_SUCC == CDS_MatchIpv4SoftFilter(&stIpInfo, pstSoftFilter))
        {
            break;
        }
    }

    /*ƥ�������ʧ��*/
    if ((VOS_NULL_PTR == pstSoftFilter) || (ulCnt == pstCdsEntity->ulUlSoftFilterNum))
    {
        return PS_FAIL;
    }

    /*������˽��*/
    pstIpfResult->usBearedId  = pstSoftFilter->ucRabId;
    pstIpfResult->usIpSegInfo = stIpInfo.ucIpSegType;
    pstIpfResult->usIpType    = IPF_IPTYPE_V4;
    return PS_SUCC;
}



VOS_UINT32 CDS_Ipv6PktSoftFilter(const TTF_MEM_ST *pstIpPkt, IPF_RESULT_STRU *pstIpfResult,const CDS_ENTITY_STRU *pstCdsEntity)
{

    CDS_IP_DATA_INFO_STRU           stIpInfo      = {0};
    CDS_SOFTFILTER_INFO_STRU       *pstSoftFilter = VOS_NULL_PTR;
    VOS_UINT32                      ulCnt;

    /*����IPv6���ݰ�*/
    CDS_DecodeIpv6Packet(pstIpPkt,&stIpInfo);

    /*�����������������*/
    for (ulCnt = 0; ulCnt < pstCdsEntity->ulUlSoftFilterNum; ulCnt ++)
    {
        pstSoftFilter = (CDS_SOFTFILTER_INFO_STRU *)(&(pstCdsEntity->astUlSoftFilter[ulCnt]));

        /*�����ΪIPv6����ִ����һ��������*/
        if (CDS_SOFTFILTER_TYPE_IPV6 != pstSoftFilter->enFilterType)
        {
            continue;
        }

        /*ƥ��IPv6 TFT������*/
        if (PS_SUCC == CDS_MatchIpv6SoftFilter(&stIpInfo, pstSoftFilter))
        {
            break;
        }
    }

    /*ƥ�������ʧ��*/
    if ((VOS_NULL_PTR == pstSoftFilter) || (ulCnt == pstCdsEntity->ulUlSoftFilterNum))
    {
        return PS_FAIL;
    }

    /*������˽��*/
    pstIpfResult->usBearedId  = pstSoftFilter->ucRabId;
    pstIpfResult->usIpSegInfo = stIpInfo.ucIpSegType;
    pstIpfResult->usIpType    = IPF_IPTYPE_V6;

    return PS_SUCC;

}



VOS_UINT32 CDS_IpSoftFilter(TTF_MEM_ST *pstIpPkt, VOS_UINT16 *pusResult, const CDS_ENTITY_STRU *pstCdsEntity)
{
    VOS_UINT32           ulResult;
    IPF_RESULT_STRU     *pstIpfResult;
    VOS_UINT8            ucIpfragRabId;

    CDS_ASSERT_RTN(VOS_NULL_PTR != pstIpPkt, PS_FAIL);
    CDS_ASSERT_RTN(VOS_NULL_PTR != pusResult, PS_FAIL);
    CDS_ASSERT_RTN(VOS_NULL_PTR != pstCdsEntity, PS_FAIL);

    CDS_DBG_UL_SOFT_FILTER_PKT_NUM(1);

    pstIpfResult = (IPF_RESULT_STRU *)((VOS_UINT32)pusResult);
    if (IP_VERSION_V4 == IP_GET_VERSION(pstIpPkt->pData))
    {
        /*IPv4*/
        ulResult = CDS_Ipv4PktSoftFilter(pstIpPkt, pstIpfResult, pstCdsEntity);
        CDS_DBG_UL_SOFT_FILTER_IPV4_PKT_NUM(1);
    }
    else
    {
        /*IPv6*/
        ulResult = CDS_Ipv6PktSoftFilter(pstIpPkt, pstIpfResult, pstCdsEntity);
        CDS_DBG_UL_SOFT_FILTER_IPV6_PKT_NUM(1);
    }

    if (PS_SUCC != ulResult)
    {
        CDS_DBG_UL_SOFT_FILTER_FAIL_NUM(1);
        return PS_FAIL;
    }

    /*IP��Ƭ��.���ٻ�ƥ��һ��ȱʡ����*/
    if (CDS_UL_IPF_IPSEG_TYPE_NO_FRAGMENT != pstIpfResult->usIpSegInfo)
    {
        CDS_DBG_UL_SOFT_FILTER_IPSEG_PKT_NUM(1);
        if (PS_SUCC == CDS_IpFragmentProc(&ucIpfragRabId, pstIpPkt,pstIpfResult,pstCdsEntity))
        {
            /*����RabId*/
            pstIpfResult->usBearedId = ucIpfragRabId;
            CDS_DBG_UL_SOFT_FILTER_IPSEG_SUCC_NUM(1);
        }
        else
        {
            CDS_DBG_UL_SOFT_FILTER_IPSEG_FAIL_NUM(1);
        }
    }

    return PS_SUCC;
}


VOS_UINT32  CDS_SetUlSoftFilter(const CDS_SOFTFILTER_INFO_STRU *pstUlFilterInfo, VOS_UINT32 ulFilterNum)
{

    CDS_ENTITY_STRU                *pstCdsEntity;
    VOS_INT32                       lLock;

    /*����ж�*/
    if (VOS_NULL_PTR == pstUlFilterInfo)
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"CDS_SetUlSoftFilter : Input Para Error.");
        CDS_PRINT_ERROR(CDS_SetUlSoftFilter_ENUM,CDS_PRINT_PARA_INPUT_ERR);
        return PS_FAIL;
    }

    if (ulFilterNum >= CDS_MAX_SOFT_FILTER_NUM)
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_SetUlSoftFilter : ulFitler Num Error.",ulFilterNum);
        CDS_PRINT_ERROR1(CDS_SetUlSoftFilter_ENUM,CDS_PRINT_FILTER_NUM_ERR,ulFilterNum);
        return PS_FAIL;
    }

    pstCdsEntity = CDS_GetCdsEntity(MODEM_ID_0);
    if (VOS_NULL_PTR == pstCdsEntity)
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"CDS_SetUlSoftFilter : Get CDS Entity Fail.");
        CDS_PRINT_ERROR(CDS_SetUlSoftFilter_ENUM,CDS_PRINT_GET_ENTITY_FAIL);
        return PS_FAIL;
    }

    lLock = VOS_SplIMP();
    pstCdsEntity->ulUlSoftFilterNum = ulFilterNum;
    PS_MEM_CPY(pstCdsEntity->astUlSoftFilter,
               pstUlFilterInfo,
               ulFilterNum * sizeof(CDS_SOFTFILTER_INFO_STRU));

    VOS_Splx(lLock);

    return PS_SUCC;

}



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

