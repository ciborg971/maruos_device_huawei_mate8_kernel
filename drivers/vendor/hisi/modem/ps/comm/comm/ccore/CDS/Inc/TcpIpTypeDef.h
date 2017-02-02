

#ifndef __TCP_IP_TYPE_DEF_H__
#define __TCP_IP_TYPE_DEF_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  #pragma pack(*)    �����ֽڶ��뷽ʽ
*****************************************************************************/

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include "vos.h"


#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#pragma warning(disable:4200)
#endif

/*****************************************************************************
  2 macro
*****************************************************************************/
/*Ehternet Max MTU*/
#define ETH_MAX_MTU                 (1500)

/* Define IP Version */
#define IP_VERSION_V4               (4)
#define IP_VERSION_V6               (6)

/* Define IPV4/IPV6 Address Length */
#ifndef IPV4_ADDR_LEN
#define IPV4_ADDR_LEN               (4)
#endif

#ifndef IPV6_ADDR_LEN
#define IPV6_ADDR_LEN               (16)
#endif

/*IPv4��IPv6ͷ����*/
#define IPV4_HDR_LEN                (20)
#define IPV6_HDR_LEN                (40)

/* IPv4 flags. network byte order*/
#define IPV4_MF_MASK                (0x2000)      /* Flag: "More Fragments" */
#define IPV4_DF_MASK                (0x4000)      /* Flag: "Don't Fragment" */
#define IPV4_OFFSET_MASK            (0x1FFF)      /* Fragment Offset part */

/*IPv6 Fragment Flg*/
#define IPV6_MF_MASK                (0x0001)        /*Flag : More Fragments*/
#define IPV6_OFFSET_MASK            (0xFFF8)        /*Fragment Offset part*/
#define IPV6_FLOW_LABLE_MASK        (0x000FFFFFUL)  /* FlowLable Mask, FlowLabel length is  20bit*/

/* Protocol field of IPv4 header. */
#define IPV4_PROTOCOL_ICMP          (1)         /* IP����Э����ICMP */
#define IPV4_PROTOCOL_TCP           (6)         /* IP����Э����TCP  */
#define IPV4_PROTOCOL_UDP           (17)        /* IP����Э����UDP  */
#define IPV4_PROTOCOL_ESP           (50)        /* IPSec ESP */
#define IPV4_PROTOCOL_AUTH          (51)        /* IPSec AH */


/* Nextheader fields of IPV6 header. reference linux ipv6 implement. */
#define IPV6_NEXTHDR_HOP            (0)       /*Hop-by-hop option header*/
#define IPV6_NEXTHDR_TCP            (6)       /*TCP segment*/
#define IPV6_NEXTHDR_UDP            (17)      /*UDP message*/
#define IPV6_NEXTHDR_IPV6           (41)      /*IPv6 in IPv6*/
#define IPV6_NEXTHDR_ROUTING        (43)      /*Routing header*/
#define IPV6_NEXTHDR_FRAGMENT       (44)      /*Fragmentation/reassembly header*/
#define IPV6_NEXTHDR_ESP            (50)      /*Encapsulating security payload*/
#define IPV6_NEXTHDR_AUTH           (51)      /*Auhtentication header*/
#define IPV6_NEXTHDR_ICMP           (58)      /*ICMP for IPv6*/
#define IPV6_NEXTHDR_NONE           (59)      /*No next header*/
#define IPV6_NEXTHDR_DEST           (60)      /*Destination options header*/
#define IPV6_NEXTHDR_MOBILITY       (135)     /*Mobility header*/
#define IPV6_NEXTHDR_MAX            (255)

/*Get IP Version*/
#define IP_GET_VERSION(pucIpPkt)                ((pucIpPkt)[0] >> 4)

/*Get IPv6 Traffic Class*/
#define IPV6_TRAFFIC_CLASS(pstIpv6Hdr)          ((((pstIpv6Hdr)->ucPriority) << 4) | ((((pstIpv6Hdr)->aucFlowLabel[0]) & 0xF0) >> 4))

/*Get IPv6 Flow Lable*/
#define IPV6_FLOW_LABLE(pstIpv6Hdr)             (VOS_UINT32)(((((pstIpv6Hdr)->aucFlowLabel[0]) & 0x0F) << 16) \
                                                            | (((pstIpv6Hdr)->aucFlowLabel[1]) << 8) \
                                                            | (((pstIpv6Hdr)->aucFlowLabel[2])))

/* Get Ipv6 Option Len */
#define IPV6_OPTION_LEN(pstOptHdr)              (((pstOptHdr)->ucHdrLen + 1) << 3)


/*define transfer between network byte order and host byte order*/
#if (VOS_BYTE_ORDER == VOS_BIG_ENDIAN)
#define IP_NTOHL(x)    (x)
#define IP_HTONL(x)    (x)
#define IP_NTOHS(x)    (x)
#define IP_HTONS(x)    (x)
#else
#define IP_NTOHL(x)    ((((x) & 0x000000ff) << 24) | \
             (((x) & 0x0000ff00) <<  8) | \
             (((x) & 0x00ff0000) >>  8) | \
             (((x) & 0xff000000) >> 24))

#define IP_HTONL(x)    ((((x) & 0x000000ff) << 24) | \
             (((x) & 0x0000ff00) <<  8) | \
             (((x) & 0x00ff0000) >>  8) | \
             (((x) & 0xff000000) >> 24))

#define IP_NTOHS(x)    ((((x) & 0x00ff) << 8) | \
             (((x) & 0xff00) >> 8))

#define IP_HTONS(x)    ((((x) & 0x00ff) << 8) | \
             (((x) & 0xff00) >> 8))

#endif  /* _BYTE_ORDER==_LITTLE_ENDIAN */

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
  4 Enum
*****************************************************************************/


/*****************************************************************************
 �ṹ��    : ICMPV4_TYPE_ENUM
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ICMPv4ͷ�����Ͷ���
*****************************************************************************/
enum ICMPV4_TYPE_ENUM
{
    ICMPV4_TYPE_ECHOREPLY            = 0,           /* Ping Reply*/
    ICMPV4_TYPE_DEST_UNREACH         = 3,           /* Destination Unreachable*/
    ICMPV4_TYPE_SRC_QUENCH           = 4,           /* Source Quench */
    ICMPV4_TYPE_REDIRECT             = 5,           /* Redirect (change route) */
    ICMPV4_TYPE_ECHO                 = 8,           /* Ping Request */
    ICMPV4_TYPE_TIME_EXCEEDED        = 11,          /* Time Exceeded */
    ICMPV4_TYPE_PARA_PROBLEM         = 12,          /* Parameter Problem */
    ICMPV4_TYPE_TIMESTAMP            = 13,          /* Timestamp Request */
    ICMPV4_TYPE_TIMESTAMPREPLY       = 14,          /* Timestamp Reply */
    ICMPV4_TYPE_INFO_REQUEST         = 15,          /* Information Request */
    ICMPV4_TYPE_INFO_REPLY           = 16,          /* Information Reply */
    ICMPV4_TYPE_ADDRESS              = 17,          /* Address Mask Request */
    ICMPV4_TYPE_ADDRESS_REPLY        = 18,          /* Address Mask Reply */

    ICMPV4_TYPE_BUTT
};


/*****************************************************************************
 �ṹ��    : ICMPV6_TYPE_ENUM
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ICMPv6ͷ�����Ͷ���
*****************************************************************************/
enum ICMPV6_TYPE_ENUM
{
    ICMPV6_TYPE_ECHOREQUEST          = 128,
    ICMPV6_TYPE_ECHOREPLY            = 129,
    ICMPV6_TYPE_RS                   = 133,
    ICMPV6_TYPE_RA                   = 134,
    ICMPV6_TYPE_NS                   = 135,
    ICMPV6_TYPE_NA                   = 136,
    ICMPV6_TYPE_REDIRECT             = 137,
    ICMPV6_TYPE_BUTT
};

/*****************************************************************************
 �ṹ��    : TCP_OPTION_ITEM_KIND_ENUM
 Э����  : ����TCPѡ���е�����
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
enum TCP_OPTION_ITEM_KIND_ENUM
{
    TCP_OPTION_ITEM_KIND_EOL        = 0,                     /*End of Option List*/
    TCP_OPTION_ITEM_KIND_NOP        = 1,                     /*No Operation*/
    TCP_OPTION_ITEM_KIND_MSS        = 2,                     /*MSS*/
    TCP_OPTION_ITEM_KIND_WINSCALE   = 3,                     /*Window Scale shitf count*/
    TCP_OPTION_ITEM_KIND_SACKPER    = 4,                     /*SACK Permitted*/
    TCP_OPTION_ITEM_KIND_SACK       = 5,                     /*SACK*/
    TCP_OPTION_ITEM_KIND_TIMESTAMP  = 8,                     /*ʱ���*/
    TCP_OPTION_ITEM_KIND_BUTT       = 254
};

/*****************************************************************************
 �ṹ��    : TCP_HDR_FLAG_ENUM
 Э����  : ����TCPͷ�еı�־λ
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
enum TCP_HDR_FLAG_ENUM
{
    TCP_HDR_FLG_FIN  = 0x1,
    TCP_HDR_FLG_SYN  = 0x2,
    TCP_HDR_FLG_RST  = 0x4,
    TCP_HDR_FLG_PSH  = 0x8,
    TCP_HDR_FLG_ACK  = 0x10,
    TCP_HDR_FLG_URG  = 0x20,
    TCP_HDR_FLG_REV  = 0x40
};


/*****************************************************************************
  5 STRUCT
*****************************************************************************/


#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(1)
#else
#pragma pack(push, 1)
#endif

/*****************************************************************************
 �ṹ��    : IPV4_ADDR_UN
 Э����  :
 ASN.1���� :
 �ṹ˵��  : IPV4��ַ
*****************************************************************************/
typedef union
{
    VOS_UINT8    aucIPAddr[4];
    VOS_UINT32   ulIpAddr;
} IPV4_ADDR_UN;

/*****************************************************************************
�ṹ��    : IPV6_ADDR_UN
Э����  :
ASN.1���� :
�ṹ˵��  : IPV6��ַ
*****************************************************************************/
typedef union
{
    VOS_UINT8    aucIPAddr[16];
    VOS_UINT16   ausIpAddr[8];
    VOS_UINT32   aulIpAddr[4];
} IPV6_ADDR_UN;

/*****************************************************************************
 �ṹ��    : IPV4_HDR_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : IPV4�̶�ͷ.��little-endian����.
*****************************************************************************/
typedef struct
{
    VOS_UINT8    ucIpHdrLen:4;                 /* header length */
    VOS_UINT8    ucIpVer:4;                    /* version */

    VOS_UINT8    ucServiceType;                /* type of service */
    VOS_UINT16   usTotalLen;                   /* total length */
    VOS_UINT16   usIdentification;             /* identification */
    VOS_UINT16   usOffset;                     /* fragment offset field */

    VOS_UINT8    ucTTL;                        /* time to live*/
    VOS_UINT8    ucProtocol;                   /* protocol */
    VOS_UINT16   usCheckSum;                   /* checksum */
    IPV4_ADDR_UN unSrcAddr;                    /* source address */
    IPV4_ADDR_UN unDestAddr;                   /* dest address */
}IPV4_HDR_STRU;


/*****************************************************************************
 �ṹ��    : IPV6_HDR_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : IPV6�̶�ͷ.��little-endian����.
*****************************************************************************/
typedef struct
{
    VOS_UINT8     ucPriority :4;               /*priority*/
    VOS_UINT8     ucIpVersion:4;               /*ip version, to be 6*/
    VOS_UINT8     aucFlowLabel[3];             /*flow lable, low 20bit*/

    VOS_UINT16    usPayloadLen;                /*not include ipv6 fixed hdr len 40bytes*/
    VOS_UINT8     ucNextHdr;                   /*for l4 protocol or ext hdr*/
    VOS_UINT8     ucHopLimit;
    IPV6_ADDR_UN  unSrcAddr;
    IPV6_ADDR_UN  unDstAddr;

}IPV6_HDR_STRU;

/*****************************************************************************
 �ṹ��    : IPV6_FRAGMENT_HDR
 Э����  :
 ASN.1���� :
 �ṹ˵��  : IPV6��Ƭͷ
*****************************************************************************/
typedef struct
{
    VOS_UINT8       ucNextHdr;
    VOS_UINT8       ucReserved;
    VOS_UINT16      usFragOffset;
    VOS_UINT32      ulIdentification;
}IPV6_FRAGMENT_HDR;


/*****************************************************************************
 �ṹ��    : IPV6_OPTION_HDR
 Э����  :
 ASN.1���� :
 �ṹ˵��  : IPV6 ѡ��ͷ.����TLV��ʽ.
*****************************************************************************/
typedef struct
{
    VOS_UINT8       ucNextHdr;
    VOS_UINT8       ucHdrLen;
}IPV6_OPTION_HDR;


/*****************************************************************************
 �ṹ��    : TCP_HDR_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����TCP�̶�ͷ.��little-endian����.
*****************************************************************************/
typedef struct
{
    VOS_UINT16    usSrcPort;
    VOS_UINT16    usDstPort;
    VOS_UINT32    ulSeqNum;
    VOS_UINT32    ulAck;
    VOS_UINT8     bitRec    : 4;
    VOS_UINT8     bitHdrLen : 4;
    VOS_UINT8     ucFlag;
    VOS_UINT16    usWinSize;
    VOS_UINT16    usCheckSum;
    VOS_UINT16    usUrgentOffset;
}TCP_HDR_STRU;

/*****************************************************************************
 �ṹ��    : TCP_FAKE_HDR_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �������У���ʱ�õ���TCPα�ײ�. ��little-endian����.
*****************************************************************************/
typedef struct
{
    VOS_UINT8             aucRec0[8];                             /*ȫ��Ϊ0��Ӱ��CRC���㣬Ϊ��ͬIPͷ��С������ͬ*/
    VOS_UINT32            ulSrcIP;                                /*ԴIP��ַ*/
    VOS_UINT32            ulDstIP;                                /*Ŀ��IP��ַ*/
    VOS_UINT8             ucAll0;                                 /*ȫ��Ϊ0*/
    VOS_UINT8             ucProtocol;                             /*IP�ײ���Э���ֶ�*/
    VOS_UINT16            usLength;
}TCP_FAKE_HDR_STRU;

/*****************************************************************************
 �ṹ��    : TCP_OPTION_ITEM_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����TCPͷOptionѡ��ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8             ucKind;
    VOS_UINT8             ucLen;
    VOS_UINT8             aucValue[126];
}TCP_OPTION_ITEM_STRU;


/*****************************************************************************
 �ṹ��    : UDP_HDR_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����UDPͷ.��little-endian����.
*****************************************************************************/
typedef struct
{
    VOS_UINT16      usSrcPort;
    VOS_UINT16      usDstPort;
    VOS_UINT16      usLen;
    VOS_UINT16      usCheckSum;
}UDP_HDR_STRU;

/*****************************************************************************
 �ṹ��    : ICMP_HDR_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����ICMPͷ.��little-endian����.
*****************************************************************************/
typedef struct
{
    VOS_UINT8       ucType;
    VOS_UINT8       ucCode;
    VOS_UINT16      usCheckSum;
}ICMP_HDR_STRU;

/*****************************************************************************
 �ṹ��    : AH_HDR_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����IPSec AHͷ.��little-endian����.
*****************************************************************************/
typedef struct
{
    VOS_UINT8       ucNextHdr;
    VOS_UINT8       ucHdrLen;
    VOS_UINT16      usRes;

    VOS_UINT32      ulSPI;
    VOS_UINT32      ulSn;                   /* Sequence number */
    VOS_UINT8       auth_data[0];           /* Variable len but >=4. Mind the 64 bit alignment! */
}AH_HDR_STRU;


/*****************************************************************************
 �ṹ��    : ESP_HDR_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����IPSec ESPͷ.��little-endian����.
*****************************************************************************/
typedef struct
{
    VOS_UINT32      ulSPI;
    VOS_UINT32      ulSn;                   /* Sequence number */
    VOS_UINT8       enc_data[0];            /* Variable len but >=8. Mind the 64 bit alignment! */
}ESP_HDR_STRU;



#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/



/*****************************************************************************
  9 OTHERS
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

#endif /* end of TcpIpTypeDef.h */
