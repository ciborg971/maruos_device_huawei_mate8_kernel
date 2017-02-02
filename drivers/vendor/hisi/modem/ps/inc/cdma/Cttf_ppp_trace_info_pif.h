/******************************************************************************

                  ��Ȩ���� (C), 2013-2023, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : Cttf_ppp_trace_info_pif.h
  �� �� ��   : ����
  ��    ��   : d00314740
  ��������   : 2015��06��19��
  ����޸�   :
  ��������   :
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��06��19��
    ��    ��   : d00314740
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __CTTF_PPP_TRACE_INFO_PIF_H__
#define __CTTF_PPP_TRACE_INFO_PIF_H__


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/*****************************************************************************
 ö����    : PS_DATA_FLOW_TYPE_ENUM
 Э����  :
 ASN.1���� :
 �ṹ˵��  : Data flow type
*****************************************************************************/
enum PS_DATA_FLOW_TYPE_ENUM
{
    PS_DATA_FLOW_TYPE_PPP_FRAME     = 0,
    PS_DATA_FLOW_TYPE_IPV4_PACKET,
    PS_DATA_FLOW_TYPE_IPV6_PACKET,
    PS_DATA_FLOW_TYPE_BUTT
};
typedef VOS_UINT8 PS_DATA_FLOW_TYPE_ENUM_UINT8;

/*****************************************************************************
 ö����    : HIGH_LAYER_PROTOCOL_TYPE_ENUM
 Э����  :
 ASN.1���� :
 �ṹ˵��  : High layer protocol type, ����EVDOЭ��high layer����
*****************************************************************************/
enum HIGH_LAYER_PROTOCOL_TYPE_ENUM
{
    HIGH_LAYER_TCP_TYPE                 = 0,
    HIGH_LAYER_UDP_TYPE,
    HIGH_LAYER_ICMP_TYPE,
    HIGH_LAYER_ICMPV6_TYPE,
    HIGH_LAYER_IPV4_OTHER_PROTOCOL_TYPE,
    HIGH_LAYER_IPV6_OTHER_PROTOCOL_TYPE,
    HIGH_LAYER_PROTOCOL_TYPE_BUTT
};
typedef VOS_UINT8 HIGH_LAYER_PROTOCOL_TYPE_ENUM_UINT8;

/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/
/*****************************************************************************
 �ṹ��    : PS_DATA_HTTP_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����ϸ���壬��������ʺ�ӵ���´򲻿���ҳ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucReserve1[4];
} PS_DATA_HTTP_INFO_STRU;

/*****************************************************************************
 �ṹ��    : PS_DATA_DNS_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����ϸ���壬��������ʺ�ӵ���´򲻿���ҳ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucReserve1[4];
    /* flag����: ���� or Ӧ�� */
} PS_DATA_DNS_INFO_STRU;

/*****************************************************************************
 �ṹ��    : PS_DATA_TCP_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : TCP_TYPE����չ��Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usIpId;   /* ip header identification */
    VOS_UINT16                          usDataLen;  /* ip packet byte len */
    VOS_UINT16                          usSrcPort;
    VOS_UINT16                          usDstPort;
    VOS_UINT32                          ulAckSeq;
    PS_BOOL_ENUM_UINT8                  enIncludeHttp;
    VOS_UINT8                           aucReserve1[3];
    PS_DATA_HTTP_INFO_STRU              stHttp;
} PS_DATA_TCP_INFO_STRU;

/*****************************************************************************
 �ṹ��    : PS_DATA_UDP_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : UDP_TYPE����չ��Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usIpId;   /* ip header identification */
    VOS_UINT16                          usDataLen;  /* ip packet byte len */
    VOS_UINT16                          usSrcPort;
    VOS_UINT16                          usDstPort;
    PS_BOOL_ENUM_UINT8                  enIncludeDns;
    VOS_UINT8                           aucReserve1[3];
    PS_DATA_DNS_INFO_STRU               stDns;
} PS_DATA_UDP_INFO_STRU;

/*****************************************************************************
 �ṹ��    : PS_DATA_ICMPV4_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ICMPV4_TYPE����չ��Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usIpId;     /* ip header identification */
    VOS_UINT16                          usDataLen;  /* ip packet byte len */
    VOS_UINT8                           ucType;     /* icmp header type */
    VOS_UINT8                           aucReserve1[3];
    VOS_UINT16                          usIcmpId;   /* icmp header identification */
    VOS_UINT16                          usIcmpSn;   /* icmp header sequence number */
} PS_DATA_ICMPV4_INFO_STRU;

/*****************************************************************************
 �ṹ��    : PS_DATA_ICMPV6_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ICMPV6_TYPE����չ��Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usDataLen;  /* ip packet byte len */
    VOS_UINT8                           ucType;   /* icmp header type */
    VOS_UINT8                           aucReserve1[1];
} PS_DATA_ICMPV6_INFO_STRU;

/*****************************************************************************
 �ṹ��    : PS_DATA_IPV4_OTHER_PROTOCOL_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : IPV4�������͵���չ��Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usIpId;   /* ip header identification */
    VOS_UINT16                          usDataLen;  /* ip packet byte len */
} PS_DATA_IPV4_OTHER_PROTOCOL_INFO_STRU;

/*****************************************************************************
 �ṹ��    : PS_DATA_IPV6_OTHER_PROTOCOL_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : IPV6�������͵���չ��Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usDataLen;  /* ip packet byte len */
    VOS_UINT8                           aucReserve1[2];
} PS_DATA_IPV6_OTHER_PROTOCOL_INFO_STRU;

/*****************************************************************************
 �ṹ��    : PS_DATA_HIGH_LAYER_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �ϲ��������ݵ���ϸ��Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                  ulChoice;

#define PS_DATA_HIGH_LAYER_TCP_TYPE                    (6)
#define PS_DATA_HIGH_LAYER_UDP_TYPE                    (17)
#define PS_DATA_HIGH_LAYER_ICMP_TYPE                   (1)
#define PS_DATA_HIGH_LAYER_ICMPV6_TYPE                 (58)
#define PS_DATA_HIGH_LAYER_IPV4_OTHER_PROTOCOL_TYPE    (254)
#define PS_DATA_HIGH_LAYER_IPV6_OTHER_PROTOCOL_TYPE    (255)

    union
    {
         PS_DATA_TCP_INFO_STRU                  stTcpInfo;
         PS_DATA_UDP_INFO_STRU                  stUdpInfo;
         PS_DATA_ICMPV4_INFO_STRU               stIcmpv4Info;
         PS_DATA_ICMPV6_INFO_STRU               stIcmpv6Info;
         PS_DATA_IPV4_OTHER_PROTOCOL_INFO_STRU  stIpv4OtherTypeInfo;
         PS_DATA_IPV6_OTHER_PROTOCOL_INFO_STRU  stIpv6OtherTypeInfo;
    } u;
} PS_DATA_HIGH_LAYER_INFO_STRU;

/*****************************************************************************
 �ṹ��    : PS_DATA_EXT_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �ϲ��������ݵ���չ��Ϣ
*****************************************************************************/
typedef struct
{
    PS_DATA_FLOW_TYPE_ENUM_UINT8        enDataType;         /* Ϊ���㹤�߽��н�����ͬʱ��EVDOЭ��Խ� */
    VOS_UINT8                           ucPri;              /* ���ȼ� */
    VOS_UINT8                           aucReserve1[2];
    VOS_UINT32                          ulBirthTime;        /* ������ʼtick */
    PS_DATA_HIGH_LAYER_INFO_STRU        stHighLayerInfo;    /* ������PPP֡������IP���ģ�����������ṹ��Ϣ */
    VOS_UINT8                           aucUserDef[4];      /* �û��Զ�����չ�ռ� */
    VOS_UINT16                          usStartSN;
    VOS_UINT16                          usEndSN;
} PS_DATA_EXT_INFO_STRU;

/*****************************************************************************
  8 UNION����
*****************************************************************************/



/*****************************************************************************
  9 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/




#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of Cttf_ppp_trace_info_pif.h */






