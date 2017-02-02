

#ifndef __CDS_SOFT_FILTER_H__
#define __CDS_SOFT_FILTER_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "TcpIpTypeDef.h"

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 �궨��
*****************************************************************************/

/*IPSec*/
#define IPSEC_NAT_TRAVERSAL_UDP_PORT          (4500)
/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
  4 ö�ٶ���
*****************************************************************************/


/*****************************************************************************
   5 STRUCT����
*****************************************************************************/

/*****************************************************************************
 �ṹ��    : CDS_IP_DATA_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CDS�����IPV4�ؼ���Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                       ucNextHdr;                  /*Э���*/
    VOS_UINT8                       ucServiceType;              /*��������*/
    VOS_UINT8                       ucIpSegType;                /*��Ƭ������Ϣ*/
    VOS_UINT8                       ucTrafficClass;             /*����������*/

    VOS_UINT32                      ulIpIdentity;               /*IP����ID*/


    VOS_UINT32                      ulHdrLen;
    VOS_UINT32                      ulFlowLable;

    VOS_UINT32                      ulAhSpi;                    /*AH SPI*/
    VOS_UINT32                      ulEspSpi;                   /*ESP SPI*/
    VOS_UINT16                      usSrcPort;                  /*Դ�˿ں�*/
    VOS_UINT16                      usDestPort;                 /*Ŀ�Ķ˿ں�*/

    IPV4_ADDR_UN                    unIpv4SrcAddr;              /*ԴIPv4��ַ*/
    IPV4_ADDR_UN                    unIpv4DestAddr;             /*Ŀ��IPv4��ַ*/

    IPV6_ADDR_UN                    unIpv6SrcAddr;              /*ԴIPv6��ַ*/
    IPV6_ADDR_UN                    unIpv6DestAddr;             /*Ŀ��IPv6��ַ*/
    VOS_UINT8                       ucIpVersion;                /*IP�汾��*/
    VOS_UINT8                       aucRsv[3];

}CDS_IP_DATA_INFO_STRU;


/*****************************************************************************
  6 UNION����
*****************************************************************************/


/*****************************************************************************
  7 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  8 ��������
*****************************************************************************/
extern VOS_VOID     CDS_DecodeIpv6Packet(const TTF_MEM_ST *pstIpPkt, CDS_IP_DATA_INFO_STRU *pstIpv6Info);
extern VOS_UINT32   CDS_IpSoftFilter(TTF_MEM_ST *pstIpPkt, VOS_UINT16 *pusResult, const CDS_ENTITY_STRU *pstCdsEntity);
extern VOS_UINT32   CDS_Ipv6ExtHdr(VOS_UINT8 ucNextHdr);
extern VOS_UINT32   CDS_Ipv6AddrEqual(const IPV6_ADDR_UN *a1, const IPV6_ADDR_UN *a2);
extern VOS_VOID     CDS_DecodeIpv4Packet(const TTF_MEM_ST *pstIpPkt, CDS_IP_DATA_INFO_STRU *pstIpInfo);
extern VOS_VOID     CDS_DecodeIpv6Packet(const TTF_MEM_ST * pstIpPkt, CDS_IP_DATA_INFO_STRU * pstIpInfo);
extern VOS_UINT32   CDS_IsIpv4FragInfoEq(const CDS_IP_DATA_INFO_STRU *pstSrc,const CDS_IP_DATA_INFO_STRU *pstTarget);
extern VOS_UINT32   CDS_IsIpv6FragInfoEq(const CDS_IP_DATA_INFO_STRU *pstSrc,const CDS_IP_DATA_INFO_STRU *pstTarget);




/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif

