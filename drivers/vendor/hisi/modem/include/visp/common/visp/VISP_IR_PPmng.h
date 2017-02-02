/*************************************************************************
 *
 *              Copyright 2006, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 *
 *-----------------------------------------------------------------------*
 *
 *                         VISP_IR_PPmng.H
 *
 *  Project Code: VISP1.6
 *   Module Name: PPMNG
 *  Date Created: 2006/11/16
 *        Author: liuyong 57500
 *   Description: ���ͷ�ļ������Ǵ�VISP PPmng��صĸ���ͷ�ļ���ȡIR��Ҫ�ĺ�ͽṹ���ɣ�
 *                �ں���������ά��ʱ����Ҫ��עͬVISP����ͬ��!
 *
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME            DESCRIPTION
 *
 ************************************************************************/
#ifndef _VISP_IR_PPMNG_H_
#define _VISP_IR_PPMNG_H_

#ifdef  __cplusplus
extern "C"{
#endif
/********************* IR Need Add but VISP has not **********/
#define IP6_PKOPTS_CLEAR      -1

/********************   from ppmng_proto_mgnt.h  **********************/
/* ��IPV6Э�鿪�ر������չ��15��,ԭ�й��Ϊ10��,����5�� */
#define PP_MAX_PROTO_TABLE          15

#ifndef IPPROTO_HOPOPTS
#define IPPROTO_HOPOPTS    0        /* ����ѡ��ͷ  Hop-by-hop option header */
#endif
#ifndef IPPROTO_ICMP
#define    IPPROTO_ICMP    1        /* ���Ʊ���Э�� control message protocol */
#endif
#ifndef IPPROTO_IGMP
#define    IPPROTO_IGMP    2        /* �����Э�� group mgmt protocol */
#endif
#ifndef IPPROTO_GGP
#define    IPPROTO_GGP        3     /* ·�� gateway^2 (deprecated) */
#endif
#ifndef IPPROTO_IPIP                /* IPЭ���ϵ�IP ip over ip protocol */
#define IPPROTO_IPIP    4
#endif
#ifndef IPPROTO_TCP
#define    IPPROTO_TCP        6       /* ���ƴ���Э�� tcp */
#endif
#ifndef IPPROTO_EGP
#define    IPPROTO_EGP        8       /* �ⲿ·��Э�� exterior gateway protocol */
#endif
#ifndef IPPROTO_PUP
#define    IPPROTO_PUP        12        /* pup */
#endif
#ifndef IPPROTO_UDP
#define    IPPROTO_UDP        17         /* user datagram protocol */
#endif
#ifndef IPPROTO_IDP
#define    IPPROTO_IDP        22        /* xns idp */
#endif
#ifndef IPPROTO_TP
#define    IPPROTO_TP        29         /* tp-4�ȼ�Э�� tp-4 w/ class negotiation */
#endif
#ifndef IPPROTO_IPV6
#define IPPROTO_IPV6        41           /* Э��汾��6 IPv6 in IPv6 */
#endif
#ifndef IPPROTO_ROUTING
#define IPPROTO_ROUTING    43   /* ѡ· IPv6 Routing header */
#endif
#ifndef IPPROTO_FRAGMENT
#define IPPROTO_FRAGMENT    44    /* IPv6 Fragmentation header */
#endif
#ifndef IPPROTO_GRE
#define    IPPROTO_GRE        47        /* ����·�ɷ�װЭ�� Generic Route Encapsulation Protocol */
#endif
#ifndef IPPROTO_ESP
#define IPPROTO_ESP     50       /* IP���� Ip Sec */
#endif
#ifndef IPPROTO_AH
#define IPPROTO_AH      51       /* IP���� Ip Sec */
#endif
#ifndef IPPROTO_ICMPV6
#define IPPROTO_ICMPV6        58    /* ���Ʊ���Э�� ICMP6 */
#endif
#ifndef IPPROTO_NONE
#define IPPROTO_NONE        59    /* IP����һ�� IPv6 No next header */
#endif
#ifndef IPPROTO_DSTOPTS
#define IPPROTO_DSTOPTS    60    /* IPĿ�ĵ�ַ IPv6 Destination header */
#endif
#ifndef IPPROTO_EON
#define    IPPROTO_EON        80        /* ISO cnlp */
#endif

 /* Modified by Rajesh for defect id BYAD11538 */
#ifndef   IPPROTO_OSPF
#define    IPPROTO_OSPF        89        /* ISO cnlp */
#endif


#ifndef IPPROTO_ENCAP
#define    IPPROTO_ENCAP    98        /* encapsulation header */
#endif

#ifndef IPPROTO_VRRP
#define    IPPROTO_VRRP    112        /*  VRRP */
#endif


#ifndef IPPROTO_MAX
#define    IPPROTO_MAX        256
#endif

#ifndef IPPROTO_DONE
#define IPPROTO_DONE    257 /* ��־��չͷ���ϲ�Э�鴦����� */
#endif

#ifndef SLOWTIMEOUT
#define SLOWTIMEOUT         500
#endif

#ifndef FASTTIMEOUT
#define FASTTIMEOUT         200
#endif

#ifndef IPPROTO_RAW
#define    IPPROTO_RAW        255        /* raw IP packet */
#endif

#ifndef SOCK_RAW
#define SOCK_RAW        3               /* raw-protocol interface */
#endif


#ifndef IPPROTO_ISIS             /* Added by Leon on 20040210 for isis on ipv6 tunnel */
#define IPPROTO_ISIS    124
#endif

/*********************** from vos_id.h ***********************/
#define IPV6_PMTU_CHNL_ID     80

/********************** from ppmng_pub.h  ****************/
#define EUNREACH                 31

#define SYSTRC_IPV6_PPMNG_BASE      00

#define IP6_PPMNG_CORE ((SYSTRC_IPV6_PPMNG_BASE << 8) + 022)
#define IP6_PP_CKSUM ((SYSTRC_IPV6_PPMNG_BASE << 8) + 32)
#define IP6_PPMNG_CONTROL ((SYSTRC_IPV6_PPMNG_BASE << 8) + 011)
#define IP6_PPMNG_DISTRIBUTE ((SYSTRC_IPV6_PPMNG_BASE << 8) + 015)
#define IP6_PPMNG_EXTENSION ((SYSTRC_IPV6_PPMNG_BASE << 8) + 012)
#define IP6_PPMNG_FORWARD ((SYSTRC_IPV6_PPMNG_BASE << 8) + 013)
#define IP6_PPMNG_HDRUTILS ((SYSTRC_IPV6_PPMNG_BASE << 8) + 014)
#define IP6_PPMNG_INIT ((SYSTRC_IPV6_PPMNG_BASE << 8) + 19)
#define IP6_PPMNG_INPUT ((SYSTRC_IPV6_PPMNG_BASE << 8) + 010)
#define IP6_PPMNG_INTERMEDIATE ((SYSTRC_IPV6_PPMNG_BASE << 8) + 016)
#define IP6_PPMNG_OUTPUT ((SYSTRC_IPV6_PPMNG_BASE << 8) + 18)
#define IP6_PPMNG_PROTOMGNT ((SYSTRC_IPV6_PPMNG_BASE << 8) + 017)
#define IP6_PPMNG_PPMNG ((SYSTRC_IPV6_PPMNG_BASE << 8) + 020)
#define IP6_PPMNG_FAC ((SYSTRC_IPV6_PPMNG_BASE << 8) + 021)
#define IP6_PPMNG_HA ((SYSTRC_IPV6_PPMNG_BASE << 8) + 35)


/* IPv6 Stack Enable/Disable. */
#define IP6_PP_DISABLED         0
#define IP6_PP_ENABLED          1

#ifndef EUNREACH
#define EUNREACH 31  /* defect id : 5997 */
#endif

#define IP6_DEFAULT_HOPLIMIT    255;  /* �������ͱ���ʱȱʡ��Hop Limit�ĺ� */
#define IP6_DEFAULT_FLOWLABEL   0;   /* �������ͱ���ʱȱʡ��Flow Label�ĺ� */

#define IP6_MIN_MTU         1280    /* �ӿ��Ͽ����õ���СMTU */
/*#define IP6_MAX_MTU         1500    */ /* �ӿ��Ͽ����õ����MTU, should be 65534 according to RFC */

/* �ڲ�ʹ��JumboPayloadѡ��ʱ,IPv6���ĸ��ص���󳤶� */
#define IPV6_MAXPACKET      65535

/* �ӿ���ȱʡ��IPv6 MTU��ֵ, Ŀǰ���нӿ���ȱʡMTU����ͬ�� */
#define IP6_DEFAULT_MTU     1500

/* ת������ʱӦ��ȥ��Hop Limit��ֵ */
#define IPV6_HLIMDEC        1

/* ����ĺ����ڵ��ú���IP6_Outputʱ���ò���lFlag */
/* Different Values for the lFlags used in IP6_PP_Output () */
#define IPV6_UNSPECSRC              0x00000001   /* ��ʾ�����ı���Դ��ַΪ0 */
#define IPV6_DADPACKET              0x00000002   /* ��ʾ������������DAD���ı��� */

#define IPV6_USEMINMTU              0x00000004
#define IPV6_DONT_FRAG              0x00001000

#define IPV6_NEXTHOP_SPECIFIED      0x00000010
#define IPV6_INTERMEDIATE_PKT       0x00000020

/* User Application has either directed use of kernel default
 * hop limit for outgoing unicast packets
 */
#define IPV6_USEDEFAULT_HOPLIMIT    0x00000040
/* END: Different Values for the lFlags used in IP6_PP_Output () */

/* �����鲥���ĵ�ȱʡHOP LIMITֵ */
#define IP6_DEFAULT_MULTICAST_TTL     255

/* �鲥ѡ��ṹIP6_MOPTIONS_S��im6o_multicast_loop��ȱʡֵ */
#define IP6_DEFAULT_MULTICAST_LOOP      1

/* ����ĺ������ж�һ��ͷ�����Ƿ�Ϊ��չͷ(����IPPROTO_NONE) */
#define IP6_ISEXTENSIONHEADER(proto) \
    ( (proto == IPPROTO_HOPOPTS) || (proto == IPPROTO_ROUTING) || \
      (proto == IPPROTO_FRAGMENT) || (proto == IPPROTO_DSTOPTS) || \
      (proto == IPPROTO_NONE) )

/* ���ڲ�����չͷ�ĺ� */
#define IP6_EXTHDR_GET(m, val, type, off, len, mid, ret) \
{ \
    MBUF_MAKE_MEMORY_CONTINUOUS( (m), (off)+(len), (mid), (ret) ); \
    if ( (ret) == 0 ) \
    { \
        (val) = (type)(MBUF_MTOD(m, UCHAR *) + off); \
    } \
}

/*
   �����չͷ�ĳ���,֧������,Ŀ�ĵغ�·��������չͷ
 */
#define IP6_GET_HDRLEN( phdr ) \
(NULL == (phdr) ? 0 : (((IP6_EXT_S *) (phdr))->ip6e_uclen + 1) << 3)

/*
   ����ĺ����ڽ���չͷ���ݿ���������MBUF��, ����ʱӦ���մӺ�ǰ��˳�����
   �������£�
phdr  : ��չͷ���ݵ�ָ��
type  : �����չͷ������
pmbuf : ����MBUF��ָ��
off   : MBUF��ǰ��ʣ��ռ�ĳ���
nxt   : ��һ����չͷ������
pdata : ����������ָ��MBUF�������չͷ��ָ��

˵��:�����Ŀǰ֧��������չͷ, Ŀ�ĵ���չͷ��·����չͷ
 */
#define ADD_EXTHDR(phdr, type, pmbuf, off, nxt, pdata, datatype)\
{\
    if (phdr) \
    {\
        off -= (((IP6_EXT_S *)phdr)->ip6e_uclen + 1) << 3; \
        pdata = (datatype) (MBUF_MTOD((pmbuf), UCHAR *) + off); \
        (VOID)TCPIP_Mem_Copy(pdata,(((IP6_EXT_S *)phdr)->ip6e_uclen + 1)<<3,phdr, (((IP6_EXT_S *)phdr)->ip6e_uclen + 1)<<3); \
        ((IP6_EXT_S *)pdata)->ip6e_ucnxt = nxt; \
        nxt = type; \
    }\
}

/* Copy IP6 Address from the Structure to the ULONG */
#define PP_COPY_IP6ADDR_STRUCT_TO_ARRAY(dst,src)\
{\
    dst[0] = (src)->s6_addr32[0];\
    dst[1] = (src)->s6_addr32[1];\
    dst[2] = (src)->s6_addr32[2];\
    dst[3] = (src)->s6_addr32[3];\
}

/* Copy IP6 Address from the ULONG to the Structure */
#define PP_COPY_IP6ADDR_ARRAY_TO_STRUCT(dst,src)\
{\
    (dst)->s6_addr32[0] = src[0];\
    (dst)->s6_addr32[1] = src[1];\
    (dst)->s6_addr32[2] = src[2];\
    (dst)->s6_addr32[3] = src[3];\
}


/************************************************************************************/
/* Start Of IP��MBUF�е�TAG�����IP���ĵı�ʾ */

/* ��MBUF��TAG�������ã���ʾ�Ǳ������͵�IP���� */
#define IP6_PKT_OURSENDPKT          0x00000001

/* ��MBUF��TAG�������ã���ʾ��ת����IP���� */
#define IP6_PKT_FORWARDPKT          0x00000002

/* ��MBUF��TAG�������ã���ʾ��IP���ĵ�Ŀ�ص�ַ�Ǳ���ĳ���ӿڵĵ�ַ */
#define IP6_PKT_ISOURS              0x00000004

/* ��ʾ��������DAD���� */
#define IP6_PKT_ISDADPKT            0x00000008

/* ��ʾ�����ĵ�Դ��ַ��0  */
#define IP6_PKT_UNSPECSRC           0x00000010

#define IPV6_PKT_USEMINMTU          0x00000100

#define IPV6_PKT_DONTFRAG           0x00000200

/*
    Defect Id: BYAD03474
    Description: ICMP error not generated when the pkt size is greater than path mtu on v6 side
*/
#define IPV6_PKT_ISINTERMEDIATE     0x00000400 /* BYAD04518 */

/*
 * Defect id : BYAD02397 Reason: Processing of extension headers in main board also Modified by Arun H S on 08 Oct 2003
 * These flags added for FE functionality and for further processing in main board.
 * these flags indicates till which header or ext hdr the packet is been processed
 */
#define IP6_PKT_HDR_BASE            0x00001000
#define IP6_PKT_HDR_EXT_HBH         0x00002000
#define IP6_PKT_HDR_EXT_FRAG        0x00004000
#define IP6_PKT_HDR_EXT_DST         0x00008000
#define IP6_PKT_HDR_EXT_ROUTE       0x00010000
#define IP6_PKT_HDR_EXT_IPV6        0x00020000 /* For the next hdr field, not the base */
#define IP6_PKT_HDR_EXT_UL          0x00040000
/* FIB Notify */
#define PP_FORWARD_FIB_NOTIFY       0x00080000

/*modified by pei gangqiang for VRP_MODULE_QOS_NEST_POLICY_II*/
#define IP6_PKT_HDR_EXT_TCP            0x00100000
#define IP6_PKT_HDR_EXT_UDP            0x00200000
#define IP6_PKT_HDR_EXT_ICMPV6         0x00400000
/*VRP_MODULE_QOS_NEST_POLICY_II modified end*/

/* End of IP��MBUF�е�TAG�����IP���ĵı�ʾ */
/*************************************************************************************/

/* ����ĺ������ж�һ�������Ƿ���DAD���� */
#define IP6_ISDADPACKET(pstMBuf) \
    (((MBUF_IP6_PACKET_INFO_S *)MBUF_GET_TAG_NETWORK_IP6_PTR(pstMBuf))->ulIpPktType & IP6_PKT_ISDADPKT)

/*
����ĺ������ͷ�һ��MBUF��,
ĿǰMBUF��û����Ӧ�ĺ�,MBUF_Destroyֻ�ͷ�һ��MBUF,�Ժ�Ӧ�������ӵ�MBUFģ����
*/
#define IP6_FREE_MBUF_CHAIN(pstMBuf) \
{ \
    MBUF_S *pTmpMBuf = pstMBuf; \
    \
    while (NULL != pTmpMBuf) \
    { \
        pstMBuf = MBUF_GET_PTR_NEXT_MBUF(pTmpMBuf); \
        MBUF_Destroy(pTmpMBuf); \
        pTmpMBuf = pstMBuf; \
    } \
}

/* Protocol Management related Data Structures */
struct tagIP6_PROTOSW;

typedef struct  tag6DOMAIN
{
    int     dom_nFamily;            /* AF_INET6 */
    char    *dom_pName;

    void    (*dom_pfInit) (void);    /* initialize domain data structures */

    int     (*dom_pfExternalize) (MBUF_S *);   /* externalize access rights */
    int     (*dom_pfDispose) (MBUF_S *);       /* dispose of internalized rights */

    struct tagIP6_PROTOSW   *dom_pProtoSw, *dom_pNextProtoSw;
    struct tag6DOMAIN    *dom_pNext;

    int     (*dom_pfRtAttach) (void **, int);/* initialize routing table */

    int     dom_nRtOffset;          /* an arg to rtattach, in bits */
    int     dom_nMaxRtKey;          /* for routing layer */

}IP6_PP_DOMAIN_S;

typedef struct tagIP6_PROTOSW
{
    LONG   pr_sType;                       /* socket type used for */
    struct tag6DOMAIN *pr_pDomain;         /* domain protocol a member of */
    SHORT  pr_sProtocol;                   /* protocol number */
    SHORT  pr_sFlags;                      /* see below */

    /* protocol-protocol hooks */
    /* input to protocol (from below) */
    ULONG  (*pr_pfInput)(MBUF_S **pRcvSeg, ULONG *, ULONG);

    /* output to protocol (from above) */
    LONG   (*pr_pfOutput)(MBUF_S *,VOID *,VOID*,ULONG,VOID*);

    /* control input (from below) */
    VOID   (*pr_pfCtlInput)(LONG,VOID *,VOID *);

    /* control output (from above) */

    LONG    (*pr_pfCtlOutput)(LONG, UINTPTR, LONG, LONG, MBUF_S **);
    /* user-protocol hook */

    /* user request: see list below */
    LONG    (*pr_pfUsrReq)(UINTPTR, LONG, VOID *, VOID *, VOID *);

    /* utility hooks */
    VOID   (*pr_pfInit)();       /* initialization hook */
    VOID   (*pr_pfFastTimO)();   /* fast timeout (200ms) */
    VOID   (*pr_pfSlowTimO)();   /* slow timeout (500ms) */
    VOID   (*pr_pfDrain)();      /* flush any excess space possible */

    /* sysctl for protocol */
    LONG    (*pr_pfSysCtl)(LONG *,ULONG,VOID *,ULONG *,VOID *,ULONG);

} IP6_PP_PROTOSW_S;

typedef enum tagProtoSWField
{
    IP6_PP_SOCK_TYPE = 1,
    IP6_PP_DOMAIN,
    IP6_PP_PROTOCOL_NUMBER,
    IP6_PP_FLAGS,
    IP6_PP_INPUT_FN,
    IP6_PP_OUTPUT_FN,
    IP6_PP_CTL_INPUT_FN,
    IP6_PP_CTL_OUTPUT_FN,
    IP6_PP_USR_REQUEST_FN,
    IP6_PP_INIT_FN,
    IP6_PP_FASTTIMEO_FN,
    IP6_PP_SLOWTIMEO_FN,
    IP6_PP_DRAIN_FN,
    IP6_PP_SYSCTL_FN
}IP6_PP_PROTOCOLFIELD;

/* Modified by Rajesh for Product support Defect id BYAD11615 */

typedef enum tagProduct
{
    IP6_PRODUCT_GSR =1,
    IP6_PRODUCT_PPI
}IP6_PRODUCT;

#define IP6_PRODUCT_GSR_REG          0x00000001
/*added by huweihua for a28d00455 2005_05_05*/
#define VRP_MODULE_IPV6_REG          0x00000002
#define VRP_MODULE_IPV6_TUNNEL_REG          0x00000004
/*ended*/

/* NE5000 macro remove */
#define IP6_PRODUCT_PPI_REG          0x00000002

#define IPV6_INTF_STAT_GET         1
#define IPV6_INTF_STAT_CLEAR       2
#define IPV6_GLOBAL_STAT_GET    3
#define IPV6_GLOBAL_STAT_CLEAR 4

/* Basic Header Data Structures. */
/* IPv6 address���ݽṹ
   �ýṹ������IPv6��ַ�����ݡ�
   ������IPv6��ַ128bit�ľ������ݣ����ù�����������Ե�ַ�ֶεĲ��� */
#ifndef _IN6ADDR_S
#define _IN6ADDR_S
typedef   struct    tagIN6Addr
{
    union
    {
        UCHAR     u6_ucaddr[16];
        USHORT    u6_usaddr[8];
        ULONG     u6_uladdr[4];
    } u6_addr;    /* 128-bit IP6 address */
} IN6ADDR_S;
#endif

/* Ϊ�����÷��㣬�������º궨��*/
#define s6_addr      u6_addr.u6_ucaddr
#define s6_addr8     u6_addr.u6_ucaddr
#define s6_addr16    u6_addr.u6_usaddr
#define s6_addr32    u6_addr.u6_uladdr

#ifndef _IP6_S
#define _IP6_S
typedef struct tagIP6_S {

    union {
        struct ip6_hdrctl {

            ULONG ul_ip6_tclass_flow;   /* 4 bits unused, 8 bits traffic class and 20 bits of flow-ID */
            USHORT us_ip6_plen;         /* 16 bits payload length */
            UCHAR uc_ip6_nxt;           /* 8 bits next header */
            UCHAR uc_ip6_hlim;          /* 8 bits hop limit */

        } ip6_un1;

        struct ip6_hdrctl1 {

#if (VRP_LITTLE_ENDIAN == VRP_YES)
            /* LITTLE_ENDIAN */
            UCHAR uc_ip6_unused:4;      /* 4 bits traffic class */
            UCHAR uc_ip6_ver:4;         /* 4 bits version */
#else
            /* BIG_ENDIAN */
            UCHAR uc_ip6_ver:4;     /* 4 bits version */
            UCHAR uc_ip6_unused:4;      /* 4 bits traffic class */
#endif
/*modified end*/
        } ip6_un2;

    } ip6_ctlun;

    IN6ADDR_S ip6_stSrc;                /* source address */
    IN6ADDR_S ip6_stDst;                /* destination address */

} IP6_S;
#endif


#define ip6_ucVer           ip6_ctlun.ip6_un2.uc_ip6_ver
#define ip6_ulFlow          ip6_ctlun.ip6_un1.ul_ip6_tclass_flow
#define ip6_usPLen          ip6_ctlun.ip6_un1.us_ip6_plen
#define ip6_ucNxtHdr        ip6_ctlun.ip6_un1.uc_ip6_nxt
#define ip6_ucHLim          ip6_ctlun.ip6_un1.uc_ip6_hlim

#define IP6_FLOWINFO_MASK       VOS_HTONL(0x0fffffff)  /* flow info (28 bits) */
#define IP6_FLOWLABEL_MASK      VOS_HTONL(0x000fffff)  /* flow label (20 bits) */

#define IPV6_VERSION        0x06         /* the macro used to set or get the flow label */

#if (VRP_LITTLE_ENDIAN == VRP_YES)
/* LITTLE_ENDIAN */
#define IPV6_VERSION_MASK   0xf0
#else
/* BIG_ENDIAN */
#define IPV6_VERSION_MASK   0x0f

#endif

/* Get different fields from the first four bytes in IPv6 Header, Input ULONG variable is network byte order*/
#define IPV6_HDR_GET_FLOWLABEL(ip6_ulFlow)    (VOS_NTOHL(ip6_ulFlow) & 0x000fffff)

#define IPV6_HDR_GET_TRAFFICCLASS(ip6_ulFlow)    ((VOS_NTOHL(ip6_ulFlow) & 0x0ff00000)>> 20)

#define IPV6_HDR_GET_VERSION(ip6_ulFlow)    ((VOS_NTOHL(ip6_ulFlow) & 0xf0000000)>> 28)

/* Put different fields in the first four bytes in IPv6 Header */
#define IPV6_HDR_PUT_FLOWLABEL(pip6_ulFlow, ip6_Value)\
{                                               \
    ULONG * pulFlow = (ULONG *)(pip6_ulFlow);       \
    *pulFlow = VOS_HTONL((VOS_NTOHL(*pulFlow) & 0xfff00000) | ((ULONG)ip6_Value)); \
}

#define IPV6_HDR_PUT_TRAFFICCLASS(pip6_ulFlow, ip6_Value)\
{                                               \
    ULONG * pulFlow = (ULONG *)(pip6_ulFlow);       \
    *pulFlow = VOS_HTONL((VOS_NTOHL(*pulFlow) & 0xf00fffff) | (((ULONG)ip6_Value) << 20)); \
}

#define IPV6_HDR_PUT_VERSION(pip6_ulFlow, ip6_Value)\
{                                               \
    ULONG * pulFlow = (ULONG *)(pip6_ulFlow);       \
    *pulFlow = VOS_HTONL((VOS_NTOHL(*pulFlow) & 0x0fffffff) | (((ULONG)ip6_Value) << 28)); \
}


#define IPV6_RECVTCLASS     29 /* bool; recv traffic class values */

#define IPV6_DONTFRAG       30

#ifndef _SOCKADDR_IN6_S
#define _SOCKADDR_IN6_S
typedef struct tagSOCKADDR_IN6 {
    UCHAR       ucSin6_len;         /* length of this struct(sa_family_t)*/
    UCHAR       ucSin6_family;      /* AF_INET6 (sa_family_t) */
    USHORT      usSin6_port;        /* Transport layer port # (in_port_t)*/
    ULONG       ulSin6_flowinfo;    /* IP6 flow information */
    IN6ADDR_S   stSin6_addr;        /* IP6 address */
    ULONG       ulSin6_scope_id;    /* scope zone index */
}SOCKADDR_IN6_S;
#endif

/* Extension Header Data Structures. */
/*
��Ϊ�ṹIP6_EXT_S���Ȳ���4�ı���,������Ҫ����1���ֽڽ��ж���.
���¸��ṹ�������ͬ.
*/
#pragma    pack( 1 )
typedef struct tagIP6_EXT{
    UCHAR   ip6e_ucnxt;   /* next header */
    UCHAR   ip6e_uclen;   /* header length */
}IP6_EXT_S;
#if (VOS_ARM == VOS_HARDWARE_PLATFORM)
#pragma pack(0)
#else
#pragma pack()
#endif

#pragma    pack( 1 )
typedef struct tagIP6_HBH {
    UCHAR   ip6h_ucnxt;   /* next header */
    UCHAR   ip6h_uclen;   /* header length in units of 8 octets, exclude first 8 octets */
}IP6_HBH_S;
#if (VOS_ARM == VOS_HARDWARE_PLATFORM)
#pragma pack(0)
#else
#pragma pack()
#endif

#pragma    pack( 1 )

typedef struct tagIP6_DEST {
    UCHAR   ip6d_ucnxt;   /* next header */
    UCHAR   ip6d_uclen;   /* header length in units of 8 octets, exclude first 8 octets */
}IP6_DEST_S;

#if (VOS_ARM == VOS_HARDWARE_PLATFORM)
#pragma pack(0)
#else
#pragma pack()
#endif

#pragma    pack( 1 )

typedef struct tagIP6_OPT {
    UCHAR ip6o_uctype;    /* option type */
    UCHAR ip6o_uclen;     /* option data length, in octets */
}IP6_OPT_S;

#if (VOS_ARM == VOS_HARDWARE_PLATFORM)
#pragma pack(0)
#else
#pragma pack()
#endif


typedef struct tagIP6_ROUTE {
    UCHAR  ip6r_ucnxt;        /* next header */
    UCHAR  ip6r_uclen;        /* length in units of 8 octets, exclude first 8 octets */
    UCHAR  ip6r_uctype;       /* routing type */
    UCHAR  ip6r_ucsegleft;    /* segments left */

    /* followed by routing type specific data */
}IP6_ROUTE_S;

typedef struct tagIP6_ROUTE_TYPE0 {
    UCHAR  ip6r0_ucnxt;       /* next header */
    UCHAR  ip6r0_uclen;       /* length in units of 8 octets, exclude first 8 octets */
    UCHAR  ip6r0_uctype;      /* always zero */
    UCHAR  ip6r0_ucsegleft;   /* segments left */
    ULONG  ip6r0_ulreserved;  /* reserved field */

    /* followed by up to 127 struct in6_addr */
}IP6_ROUTE_TYPE0_S;

/* 0��·����չͷ��type���ֵ */
#define IPV6_RTHDR_TYPE_0       0

/* Fragment Header */
typedef struct tagIP6_FRAG {
    UCHAR  ip6f_ucnxt;        /* next header */
    UCHAR  ip6f_ucreserved;   /* reserved field */
    USHORT ip6f_usofflg;      /* offset, reserved, and flag */
    ULONG  ip6f_ulident;      /* identification */
}IP6_FRAG_S;

/*
 * Fragment Group Structure.
 * Linked List For the given source addr, dest addr and identification in the Reassembly Queue.
 */
typedef struct tagIP6FRAG {
    ULONG ip6f_ulHead;
    USHORT ip6f_usLen;
    UCHAR ip6f_ucNxt;
    UCHAR ip6f_ucHlim;
    /* must not override the above members during reassembling */
    struct tagIP6FRAG *ip6f_pstNext;
    struct tagIP6FRAG *ip6f_pstPrev;
    MBUF_S *ip6f_pstMBuf;
    ULONG ip6f_ulOff;    /* offset in ip6f_pstMBuf to next header */
    ULONG ip6f_ulFragLen;  /* fragmentable part length */
    ULONG ip6f_ulFragOff;  /* fragment offset */
    USHORT ip6f_usMff;  /* more fragment bit in frag off */
    UCHAR  ucPadding[2];
}IP6FRAG_S;

/* Reassembly Queue. */
typedef struct tagIP6REASSQUEUE {
    ULONG ip6q_ulHead;
    USHORT ip6q_usLen;
    UCHAR ip6q_ucNxt;   /* ip6f_nxt in first fragment */
    UCHAR ip6q_ucHlim;
    IP6FRAG_S *ip6q_pstfNext;
    IP6FRAG_S *ip6q_pstfPrev;
    ULONG ip6q_ulId;
    USHORT ip6q_usTTL;
    UCHAR ucPadding[2];
    IN6ADDR_S ip6q_stSrc, ip6q_stDst;
    struct tagIP6REASSQUEUE *ip6q_pstqNext;
    struct tagIP6REASSQUEUE *ip6q_pstqPrev;
    LONG ip6q_lUnFragLen; /* len of unfragmentable part */
}IP6REASSQUEUE_S;

#if (VRP_BIG_ENDIAN == VRP_YES)
/* BIG_ENDIAN */
#define IP6F_OFF_MASK       0xfff8  /* mask out offset from _offlg */
#define IP6F_RESERVED_MASK  0x0006  /* reserved bits in ip6f_offlg */
#define IP6F_MORE_FRAG      0x0001  /* more-fragments flag */
#else
/* LITTLE_ENDIAN */
#define IP6F_OFF_MASK       0xf8ff  /* mask out offset from _offlg */
#define IP6F_RESERVED_MASK  0x0600  /* reserved bits in ip6f_offlg */
#define IP6F_MORE_FRAG      0x0100  /* more-fragments flag */
#endif

typedef struct tagIP6_EXTHDRS_S {
    IP6_S       *ip6e_pstip6;      /* IPv6ͷ��ָ�� */
    IP6_HBH_S   *ip6e_psthbh;      /* ������չͷ��ָ�� */
    IP6_DEST_S  *ip6e_pstdest1;    /* ·����չͷ֮ǰ��Ŀ�ĵ���չͷָ�� */
    IP6_ROUTE_S *ip6e_pstrthdr;    /* ·����չͷ��ָ�� */
    IP6_DEST_S  *ip6e_pstdest2;    /* ·����չͷ֮���Ŀ�ĵ���չͷָ�� */
}IP6_EXTHDRS_S;

/* END: Extension Header Data Structures. */


/* ��������/��ȡ������Ϣ�Ľṹ */
typedef struct tagIP6_PKTINFO {
    IN6ADDR_S   ipi6_stAddr;      /* src/dst IPv6 address */
    ULONG       ipi6_ulIfindex;   /* send/recv interface index */
}IP6_PKTINFO_S;

typedef struct tagIP6_NHINFO {
    SOCKADDR_IN6_S stip6po_nhi_nexthop;
} IP6_NHINFO;

#define ip6po_nexthop       ip6po_pstNHinfo->stip6po_nhi_nexthop.stSin6_addr


/* �������÷��ͱ��ĵ�ѡ��Ľṹ */
typedef struct tagIP6_PKTOPTS_S {
    /* Hoplimit for outgoing packets */
    LONG ip6po_lHlim;

    /* traffic class */
    LONG ip6po_lTclass;

    /* added by mayun for ipv6 precedence 2004-03-10 */
    UCHAR ip6po_ucTos;
    UCHAR ucPadding[3];
    /* Outgoing IF/address information */
    IP6_PKTINFO_S *ip6po_pstPktinfo;

    /* Next-hop address information, not support now */
    IP6_NHINFO *ip6po_pstNHinfo;

    /* Hop-by-Hop options header */
    IP6_HBH_S *ip6po_psthbh;

    /* Destination options header (before a routing header) */
    IP6_DEST_S *ip6po_pstdest1;

    /* Routing header related info. */
    IP6_ROUTE_S *ip6po_pstroute;

    /* Destination options header (after a routing header) */
    IP6_DEST_S *ip6po_pstdest2;

    /* flags, not used now */
    ULONG ip6po_ulFlags;

    /* ��־���ṹ��ָ��ָ����ڴ��Ƿ���Ҫ�ͷ� */
    /*
     * members dynamically allocated -
     * this value will be 1 if the memory of the particular pkt option (or all) needs to be freed
     */
    ULONG ip6po_ulNeedFree;
    
    ULONG ip6po_ulFlowID;
}IP6_PKTOPTS_S;


typedef struct tagIP6_RECVPKTOPTS{
    MBUF_S *pstHead;       /* head of mbuf chain of this struct */

    MBUF_S *pstHlim;       /* received hop limit */
    MBUF_S *pstPktinfo;    /* packet information of rcv packet */
    MBUF_S *psthbh;        /* HbH options header of rcv packet */
    MBUF_S *pstdest1;      /* Dest opt header of rcv packet */
    MBUF_S *pstdest2;      /* Dest opt header (after rthdr) of rcv packet */
    MBUF_S *pstrthdr;      /* Routing header of rcv packet */
}IP6_RECVPKTOPTS_S;

typedef struct tagIp6multi {
    IN6ADDR_S stIP6Addrr;                /* IP6 multicast address */
    ULONG ulIfIndex;
} IP6Multi;

/* Multi-cast membership entry.  One for each group/ifp that a PCB belongs to. */
typedef struct tagIp6multimship {
    IP6Multi stIP6maddr;                    /* Multicast address pointer */
    struct tagIp6multimship *pstNext, *pstPrev;  /* multicast options chain */
}IP6_MultiMembership;

/* ���������鲥����ѡ��ĺ� */
typedef struct tagIP6_MOPTIONS_S
{
    ULONG   im6o_ulIndexIf;         /* ifp for outgoing multicasts */
    UCHAR   im6o_ucMulticast_hlim;    /* hoplimit for outgoing multicasts */
    UCHAR   im6o_ucMulticast_loop;    /* 1 >= hear sends if a member */
    UCHAR   ucPadding[2];
    IP6_MultiMembership *pstMultiMemberships;
    /* ������鲥��ȸ���Ĳ������Ժ����� */
}IP6_MOPTIONS_S;

/* Argument structure for IPV6_JOIN_GROUP and IPV6_LEAVE_GROUP. */
/* ��������ѡ�� IP_ADD_MEMBERSHIP and IP_DROP_MEMBERSHIP�Ĳ��� */
typedef struct tagIP6_Mreq {
    IN6ADDR_S stIp6multiaddr;       /* IP multicast address of group */
    ULONG ulIfIndex;                /* local address of interface */
}IP6_PP_MREQ_S;

/* END: Control Options Data Structures. */

/* IPv6 Statistics */

#define IP6_PP_INCREMENT       0
#define IP6_PP_DECREMENT       1

/* IPv6����ͳ����Ϣ�Ľṹ */
typedef struct tagIP6STAT
{
    ULONG   ip6s_ulTotalReceived;   /* total packets received */
    ULONG   ip6s_ulTooShort;        /* packet too short */
    ULONG   ip6s_ulTooSmall;        /* not enough data */
    ULONG   ip6s_ulHopLimitExceed;  /* hop limit exceed */
    ULONG   ip6s_ulBadHeader;       /* error in header processing */
    ULONG   ip6s_ulBadOption;       /* error in option processing */
    ULONG   ip6s_ulFragments;       /* fragments received */
    ULONG   ip6s_ulReassembled;     /* total packets reassembled ok */
    ULONG   ip6s_ulFragDropped;     /* frags dropped (dups, out of space) */
    ULONG   ip6s_ulFragTimeout;     /* fragments timed out */
    ULONG   ip6s_ulOFailedFragments; /* Fragments Failed to Sent Out. */
    ULONG   ip6s_ulNoProto;         /* unknown or unsupported protocol */
    ULONG   ip6s_ulDelivered;       /* datagrams delivered to upper level*/
    ULONG   ip6s_ulLocalOut;        /* total ipv6 packets generated */
    ULONG   ip6s_ulForward;         /* packets forwarded */
    ULONG   ip6s_ulNoRoute;         /* packets discarded due to no route */
    ULONG   ip6s_ulTooBig;          /* packets discarded due to bigger than mtu*/
    ULONG   ip6s_ulFragmented;      /* datagrams sucessfully fragmented */
    ULONG   ip6s_ulOFragments;      /* output fragments created */
    ULONG   ip6s_ulInMulticasts;    /* multicast packets received */
    ULONG   ip6s_ulNotMember;       /* donot join this multicast group */
    ULONG   ip6s_ulOutMulticasts;   /* multicast packets sent */
    ULONG   ip6s_ulDstAddrErr;      /* error in incoming dest addr (invalid and unsupported) */

/* TODO: Where will this happen ??? - this is a MIB requirement */
    ULONG   ip6s_ulInDiscards;      /* Input Dgms which had no pbms, but were discarded due to lack of buffer space */
    ULONG   ip6s_ulOutDiscards;     /* Output Dgms which had no pbms, but were discarded due to lack of buffer space */
}IP6STAT_S;

typedef enum tageIP6_STATISTICS
{
       IP6_TOTALRECEIVED = 1,   /* total packets received */
       IP6_TOOSHORT,            /* packet too short */
       IP6_TOOSMALL,            /* not enough data */
       IP6_HOPLIMITEXCEED,      /* hop limit exceed */
       IP6_BADHEADER,           /* error in header processing */
       IP6_BADOPTION,           /* error in option processing */
       IP6_FRAGMENTS,           /* fragments received */
       IP6_REASSEMBLED,         /* total packets reassembled ok */
       IP6_FRAGDROPPED,         /* frags dropped (dups, out of space) */
       IP6_FRAGTIMEOUT,         /* fragments timed out */
       IP6_FAILEDFRAGMENTS,     /* Fragments Failed to Sent Out. */
       IP6_NOPROTO,             /* unknown or unsupported protocol */
       IP6_DELIVERED,           /* datagrams delivered to upper level*/
       IP6_LOCALOUT,            /* total ipv6 packets generated */
       IP6_FORWARD,             /* packets forwarded */
       IP6_NOROUTE,             /* packets discarded due to no route */
       IP6_TOOBIG,              /* packets discarded due to bigger than mtu*/
       IP6_FRAGMENTED,          /* datagrams sucessfully fragmented */
       IP6_OFRAGMENTS,          /* output fragments created */
       IP6_INMULTICASTS,        /* multicast packets received */
       IP6_NOTMEMBER,           /* donot join this multicast group */
       IP6_OUTMULTICASTS,       /* multicast packets sent */
       IP6_DSTADDRERR,          /* error in incoming dest addr (invalid and unsupported) */

/* TODO: Where will this happen ??? - this is a MIB requirement */
       IP6_INDISCARDS,          /* Input Dgms which had no pbms, but were discarded due to lack of buffer space */
       IP6_OUTDISCARDS          /* Output Dgms which had no pbms, but were discarded due to lack of buffer space */
}IP6_PP_STATISTICS;

/* END: IPv6 Statistics */

/* Intermediate Processing. */
typedef ULONG (*IP6_PP_Register) (MBUF_S *pstMBuf);
/* END: Intermediate Processing. */
typedef ULONG (*IP6_PP_Register_Notify) (ULONG ulRoutingFlag);

#define IP6_PP_MAX_NOTIFY_REGISTER 10

/*
 * Defect Id: BYAD08299
 * Description: Add Log Info for the PPMNG part as IPv4
 */
typedef enum tageIP6_ICINFO
{
    IP6_REASFULL = 0,
    IP6_REASPAFULL,
    IP6_IC_RPCCALLFAIL  /* added by chenxia for SWFD06092, 2005/02/25 */
} IP6_PP_ICINFO;


 /* Begin : Defect ID: BYAD011817,     Modifier:Rajesh,   Date:2004/9/15
     Reason   : Component issues*/
 typedef struct tagSocket_CALLBACKUP_SET_S
{
    ULONG (*pfIP6_PP_SH_RegisterCliChangeNotify)(ULONG (* pfIP6_PP_NotifyCliChange)(ULONG ulCliState));

}Socket_CALLBACKUP_SET_S;

#ifdef  __cplusplus
}
#endif  /* end of __cplusplus */

#endif  /* end of _VISP_IR_PPMNG_H_ */

