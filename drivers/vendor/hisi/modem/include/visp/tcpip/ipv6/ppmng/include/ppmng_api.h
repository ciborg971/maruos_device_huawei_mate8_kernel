
/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ppmng_api.h
*
*  Project Code: VISPV1R7
*   Module Name: PPMNG  
*  Date Created: 2008-3-9
*        Author: wangbin(62223)
*   Description: ppmngģ������ṩ��ͷ�ļ�
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*-------------------------------------------------------------------------------
*  2008-3-8 wangbin(62223)     Create the first version.
*
*******************************************************************************/
#ifndef _PPMNG_API_H_
#define _PPMNG_API_H_

#ifdef __cplusplus
extern "C"{
#endif

/* wangjiaq modify for mccp headfile include */
/* Stack (PP) will do the processing*/
#define PP_NO_PROCESS_NEEDED_BY_INTER_FUNCTION              1 

/* Packet has Error, Stack will Destroy the Packet */
#define PP_RET_ERROR                                        2

/* Intermediate Processing will continue processing and will own the packet and if needed will destroy it */
#define PP_PROCESS_BY_INTER_FUNCTION                        3 

/* Packet has been administratively prohibited (for eg: by ACL) */
#define PP_SEND_ICMP_ERROR                                  4
/* Packet has been processed by Qos Input */
#define PP_PROCESS_BY_INTER_FUNCTION_QOSINPUT                       5

#ifndef IPPROTO_DONE
#define IPPROTO_DONE    257 /* ��־��չͷ���ϲ�Э�鴦����� */
#endif

#define PP_INPUT_TYPE                   0x01
#define PP_OUTPUT_TYPE                  0x02
#define PP_IO_TYPE                       0x04
#define PP_IFOUTPUT_TYPE                0x08
#define PP_QOSOUTPUT_TYPE               0x10

#define PR_ATOMIC       0x01        /* ֻ������������Ϣ    exchange atomic messages only */
#define PR_ADDR         0x02        /* ��Ϣ�а�����ַ      addresses given with messages */

typedef enum tagPPMNG_ERROR
{
    PP6_OK = 0,
    PP6_ERR,
    PP6_NOT_REGISTER,               /* 2  PPMNG���δע�� */
    PP6_ERR_HOSTNODE,               /* 3  IPV6����ģʽ */
    PP6_HOOK_NULL,                  /* 4  ���Ӻ���ΪNULL */
    PP6_INPUT_PARA_NULL,            /* 5  �������ΪNULL */
    PP6_FLOW_STAT_MAX_NUM,          /* 6  �ﵽ���֧�ֱ���ͳ������*/
    PP6_FLOW_NO_RECORD,             /* 7  ͨ��Э��źͶ˿ں�û���ҵ���Ӧ�ı���ͳ�Ƽ�¼*/
}PPMNG_ERROR_E;

/* IPV6���Ĳ���Ƭ��־,
  HERT2.8��IPV6 PATH MTU ���ܻ�ʹ��,������API�ж���һ��,ע��ú궨�������ppmng_pub.h�е�IPV6_PKT_DONTFRAG���屣��һ�� */
#define IPV6_PKT_DONTFRAG           0x00000200

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


#ifndef _ICMP6_ERRSTAT_S 
#define _ICMP6_ERRSTAT_S

/* generate ICMP6 error packet statistics */
typedef struct tagICMP6_ERRSTAT 
{
    ULONG ulIcp6errs_dst_unreach_noroute;
    ULONG ulIcp6errs_dst_unreach_admin;
    ULONG ulIcp6errs_dst_unreach_beyondscope;
    ULONG ulIcp6errs_dst_unreach_addr;
    ULONG ulIcp6errs_dst_unreach_noport;
    ULONG ulIcp6errs_dst_unreach_ingress_egress_plcy;
    ULONG ulIcp6errs_dst_unreach_reject_route;
    ULONG ulIcp6errs_packet_too_big;
    ULONG ulIcp6errs_time_exceed_transit;
    ULONG ulIcp6errs_time_exceed_reassembly;
    ULONG ulIcp6errs_paramprob_header;
    ULONG ulIcp6errs_paramprob_nextheader;
    ULONG ulIcp6errs_paramprob_option;
    ULONG ulIcp6errs_redirect; /* we regard redirect as an error here */
    ULONG ulIcp6errs_unknown;
}ICMP6_ERRSTAT_S;
#endif


#ifndef _ICMP6STAT_S 
#define _ICMP6STAT_S

/* ICMP6 packet statistics */
typedef struct tagICMP6STAT 
{
    /* statistics related to icmp6 packets generated */
    ULONG ulIcp6s_error;            /* no of calls to icmp6_error */
    ULONG ulIcp6s_canterror;        /* no error 'cuz old was icmp */
    ULONG ulIcp6s_toofreq;          /* no error 'cuz rate limitation */
    ULONG ulIcp6s_intoofreq;        /* no error 'cuz rate limitation */
    ULONG ulIcp6s_outhist[256];

    /* statistics related to input message processed */
    ULONG ulIcp6s_badcode;          /* icmp6_code out of range */
    ULONG ulIcp6s_tooshort;         /* packet < sizeof(struct icmp6_hdr) */
    ULONG ulIcp6s_checksum;         /* bad checksum */
    ULONG ulIcp6s_badlen;           /* calculated bound mismatch */

    ULONG ulIcp6s_reflect;
    ULONG ulIcp6s_inhist[256];    
    ULONG ulIcp6s_nd_toomanyopt;    /* too many ND options */
    
    ICMP6_ERRSTAT_S stIcp6s_outerrhist;
    ICMP6_ERRSTAT_S stIcp6s_inerrhist;

    ULONG ulIcp6s_pmtuchg;           /* path MTU changes */
    ULONG ulIcp6s_nd_badopt;         /* bad ND options */
    ULONG ulIcp6s_badns;             /* bad neighbor solicitation */
    ULONG ulIcp6s_badna;             /* bad neighbor advertisement */
    ULONG ulIcp6s_badrs;             /* bad router advertisement */
    ULONG ulIcp6s_badra;             /* bad router advertisement */

    /* Added by Saravanya for ND Host */
    ULONG ulIcp6s_badredirect;       /* bad Redirect received */

    ULONG  ulIcps_totaloutput;       /* Sent total */
    ULONG  ulIcps_totalinput;        /* Recvd total */
    ULONG  ulIcps_inunknowninfo;     /* Recvd unknown info type */
    ULONG  ulIcps_inunknownerror;    /* Recvd unknown error type */
    ULONG  ulIcp6s_inhopexpired;     /* Recvd hop expired */
    ULONG  ulIcp6s_reassexpired;     /* Recvd reassemble expired */
}ICMP6STAT_S;
#endif 
typedef struct tagIP6ICMP6Stats 
{
    IP6STAT_S stIP6Stats;
    ICMP6STAT_S stICMP6Stats;
} IP6_ICMP6_STATS_S;


/* Intermediate Processing. */
typedef ULONG (*IP6_PP_Register) (MBUF_S *pstMBuf);

/* ���Ӻ����ķ���ֵ */
typedef enum enumHookRetValue
{
    HOOK_RET_STACK_CONTINUE_PROC,   /* ���Ӻ������ظ�ֵʱЭ��ջ����������,��Ҫ���Ӻ��������޸�ԭ�б��� */
    HOOK_RET_STACK_DROP_PAKET,      /* ���Ӻ������ظ�ֵʱЭ��ջ�������� */
    
    HOOK_RET_END,                   
}HOOK_RET_VALUE_E;

/* ��Ʒ������ֻ�ܷ�������ֵ:
   HOOK_RET_STACK_CONTINUE_PROC: ���Ӻ������ظ�ֵʱЭ��ջ����������,��Ҫ���Ӻ��������޸�ԭ�б���;
   HOOK_RET_STACK_DROP_PAKET: ���Ӻ������ظ�ֵʱЭ��ջ��������;
*/
typedef struct tagTCPIP_IP6_PROC_ICMP6_PKT_HOOK
{
    ULONG (*pfTCPIPIp6ProcSndIcmp6PktHook) (MBUF_S *pstMBuf);
    ULONG (*pfTCPIPIp6ProcRcvIcmp6PktHook) (MBUF_S *pstMBuf);
}TCPIP_IP6_PROC_ICMP6_PKT_HOOK_S;

/*Added by wangtong207740, MRP IPv6ѡ·����, 2012/11/21 */
typedef enum enumIP6RetSrcRt
{
    IP6_GO_WITH_SCRRT, /*���ƷԴ·�ɳɹ�*/
    IP6_DROP_PKT,      /*���ƷԴ·�ɲ��ɹ�����Ҫ��������*/     
    IP6_GO_PASS,       /*���ƷԴ·�ɲ��ɹ���������ԭ�в�·�ɱ�����*/                   
}RET_IP6_SRC_RT_E;

typedef struct tagIP6SrcRtSearch
{
    IN6ADDR_S ulNextHopIPAddr;  /* ��һ����ַ, ������ */
    ULONG ulOutIfIndex;  /* ���ӿ�, ����������ӿ� */
} IP6_SRC_RT_SEARCH_S;


typedef ULONG (*gpfIP6TCPIPSrcRtSearch)(IN6ADDR_S ulSrcIPAddr, IN6ADDR_S ulDstIPAddr, IP6_SRC_RT_SEARCH_S *pstOutput);

extern gpfIP6TCPIPSrcRtSearch g_pfIp6SrcRtSearch;

/* End of Added by wangtong207740, 2012/11/21 */

typedef struct tagSrcRt6Packet
{
    IN6ADDR_S ulSrcIPAddr; /* ���ĵ�Դ��ַ,������     */
    IN6ADDR_S ulDstIPAddr; /* ���ĵ�Ŀ�ĵ�ַ,������   */
    ULONG ulVrfIndex;
} SRC_RT6_PKT_S;
typedef ULONG (*TCPIP_SRC_RT6_SEARCH_FUN)(SRC_RT6_PKT_S *pstPktInfo, IP6_SRC_RT_SEARCH_S *pstOutput);
extern TCPIP_SRC_RT6_SEARCH_FUN g_pfIp6SrcRtSearchByVrf;

typedef ULONG (*pfTCPIPNeedLookupNdHook)(MBUF_S* pstMbuf);
extern pfTCPIPNeedLookupNdHook g_pfIP6NeedLookupNd;

typedef enum enumIP6NeedLookUpND
{
    IP6_NO_NEED_LOOK_UP_ND,   /*����Ҫ����ND*/
    IP6_NEED_LOOK_UP_ND,      /*��Ҫ����ND*/     
}IP6_NEED_LOOK_UP_E;

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


/* ��������/��ȡ������Ϣ�Ľṹ */
typedef struct tagIP6_PKTINFO {
    IN6ADDR_S   ipi6_stAddr;      /* src/dst IPv6 address */
    ULONG       ipi6_ulIfindex;   /* send/recv interface index */
}IP6_PKTINFO_S;

typedef struct tagIP6_NHINFO {
    SOCKADDR_IN6_S stip6po_nhi_nexthop;
} IP6_NHINFO;

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

typedef struct tagIP6_ROUTE {
    UCHAR  ip6r_ucnxt;        /* next header */
    UCHAR  ip6r_uclen;        /* length in units of 8 octets, exclude first 8 octets */
    UCHAR  ip6r_uctype;       /* routing type */
    UCHAR  ip6r_ucsegleft;    /* segments left */

    /* followed by routing type specific data */
}IP6_ROUTE_S;

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
    LONG    (*pr_pfCtlOutput)(LONG, ULONG, LONG, LONG, MBUF_S **);
    /* user-protocol hook */

    /* user request: see list below */
    LONG    (*pr_pfUsrReq)(ULONG, LONG, VOID *, VOID *, VOID *);

    /* utility hooks */
    VOID   (*pr_pfInit)(VOID);       /* initialization hook */
    VOID   (*pr_pfFastTimO)(VOID);   /* fast timeout (200ms) */
    VOID   (*pr_pfSlowTimO)(VOID);   /* slow timeout (500ms) */
    VOID   (*pr_pfDrain)(VOID);      /* flush any excess space possible */

    /* sysctl for protocol */
    LONG    (*pr_pfSysCtl)(LONG *,ULONG,VOID *,ULONG *,VOID *,ULONG);

} IP6_PP_PROTOSW_S;

typedef struct tagTCPIP_PP6_PKTTYPE_KEY
{
    USHORT  usPort;      /*���˶˿ں�,���봫��������*/
    UCHAR   ucPro;       /*Э���*/
    UCHAR   ucPad[33];   /*�����ֶ�*/
}TCPIP_PP6_PKTTYPE_STAT_KEY_S;/*IPv6 ��ͳ�� key*/ 

typedef struct tagTCPIP_PP6_PKTTYPE_STAT
{
    ULONG  ulSndPkt;     /*���ͱ���ͳ��*/
    ULONG  ulRcvPkt;     /*���ձ���ͳ��*/
    ULONG  ulSndErrPkt;  /*���ʹ���ı���ͳ��*/
    ULONG  ulReserve[8]; /*Ԥ���ֶ�*/
}TCPIP_PP6_PKTTYPE_STAT_S;/*PP6���� ����ͳ��*/

typedef struct tagTCPIP_PP6_PKT_STAT
{
    TCPIP_PP6_PKTTYPE_STAT_KEY_S  stPktType;
    TCPIP_PP6_PKTTYPE_STAT_S      stFlowStat;
    struct tagTCPIP_PP6_PKT_STAT *pstNext;
}TCPIP_PP6_PKT_STAT_S;


typedef ULONG (*IP6_SEND_PKT_HOOK)(struct tagMBuf *pstMbuf);


extern ULONG TCPIP_IP6_RegProcessIcmp6PktHook(TCPIP_IP6_PROC_ICMP6_PKT_HOOK_S *pfHookFunc);

/*******************************************************************************
*    Func Name: TCPIP_ClrPP6ICMP6Stat
*  Description: ���PP6/ICMP6ͳ����Ϣ
*        Input: VOID
*       Output: VOID
*       Return: VOS_ERR
*               VOS_OK
*               PP6_NOT_REGISTER
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-3-9  wanggbin(62223)        Creat the first version.
*
*******************************************************************************/

extern ULONG TCPIP_ClrPP6ICMP6Stat(VOID);

/*******************************************************************************
*    Func Name: TCPIP_GetPP6ICMP6Stat
*  Description: ��ȡPP6/ICMP6ͳ����Ϣ
*        Input: 
*       Output: IP6_ICMP6_STATS_S :pstIp6Icmp6Stats
*       Return: VOS_ERR
*               VOS_OK
*               PP6_NOT_REGISTER
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-3-9  wanggbin(62223)        Creat the first version.
*
*******************************************************************************/

extern ULONG TCPIP_GetPP6ICMP6Stat(IP6_ICMP6_STATS_S *pstIp6Icmp6Stats);

/*******************************************************************************
*    Func Name: TCPIP_SetPP6Redirect
*  Description: ʹ��/ȥʹ�ܷ����ض����Ĺ���
*        Input: ULONG ulRedirectFlag
*       Output: VOID
*       Return: VOS_ERR
*               VOS_OK
*               PP6_NOT_REGISTER
*               PP6_ERR_HOSTNODE
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-3-9  wanggbin(62223)        Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_SetPP6Redirect (ULONG ulRedirectFlag);

/*******************************************************************************
*    Func Name: TCPIP_SetPP6DebugFlag
*  Description: ����PP6���ض�����
*        Input: ULONG ulDebugFlag
                ULONG ulErrpktDebugFlag
*       Output: VOID
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-3-9  wanggbin(62223)        Creat the first version.
*
*******************************************************************************/
extern VOID TCPIP_SetPP6DebugFlag(ULONG ulDebugFlag , ULONG ulErrpktDebugFlag);

/*******************************************************************************
*    Func Name: TCPIP_IP_PP6_Intermediate_Hook_Register
*  Description: �û�ע��IP6���м䴦���Ӻ�����
*        Input: ULONG: ulType
                ULONG ulPriority
                IP6_PP_Register pfIpFwHookFunc
*       Output: VOID
*       Return: VOS_ERR
*               VOS_OK
*               PP6_NOT_REGISTER
*               PP6_ERR_PARA
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-3-9  wanggbin(62223)        Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_IP_PP6_Intermediate_Hook_Register(ULONG ulType,ULONG ulPriority, IP6_PP_Register pfIpFwHookFunc);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncIP6SrcRtSearch
* Date Created: 2012-11-21
*       Author: wangtong207740
*  Description: 
*        Input: gpfIP6TCPIPSrcRtSearch pfHookFunc:
*       Output: VOS_OK-ע�ṳ�Ӻ����ɹ�
*               VOS_ERR-ע�ṳ�Ӻ���ʧ��
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-11-21   wangtong207740          Create
*
*******************************************************************************/
extern  ULONG TCPIP_RegFuncIP6SrcRtSearch(gpfIP6TCPIPSrcRtSearch pfHookFunc);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncIP6SrcRtSearchByVrf
* Date Created: 2013-12-06
*       Author: likaikun213099
*  Description: ע�����ԴIP����·�ɹ���
*        Input: TCPIP_SRC_RT6_SEARCH_FUN pfHookFunc:��Ʒע�����ԴIP����·�ɹ��Ӻ���
*       Output: 
*       Return: VOS_OK-ע�ṳ�Ӻ����ɹ�
*               VOS_ERR-ע�ṳ�Ӻ���ʧ��
*      Caution: �������ע��,���TCPIP_RegFuncIP6SrcRtSearch����VRF����֧��
*               ���ӷ���ֵ:
*               IP6_GO_WITH_SCRRT, ���ƷԴ·�ɳɹ�
*               IP6_DROP_PKT,      ��ƷԴ·�ɲ��ɹ�����Ҫ������
*               IP6_GO_PASS,       ��ƷԴ·�ɲ��ɹ���������ԭ�в�·�ɱ���
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-12-06   likaikun213099          Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncIP6SrcRtSearchByVrf(TCPIP_SRC_RT6_SEARCH_FUN pfHookFunc);

/********************************************************************************
 * Prototype     : ULONG IP6_PP_Output (MBUF_S *pstMBuf,
 *                                    IP6_PKTOPTS_S *pstOpt, ROUTE6_S *pstRo,
 *                                    LONG lFlags, IP6_MOPTIONS_S *pstMo)
 * Description   : Local Packet Output Processing.
 * Input(s)      : pstMBuf -
 *                pstOpt -
 *                pstRo -
 *                lFlags -
 *                pstMo -
 * Output(s)     : None
 * Return        : 0/1
 *-------------------------------------------------------------------------------
 * History
 * Date(yyyy-mm-dd)     Author        Modification
 *  2002-08-21         heqiangc        Created
 *  2003-06-20         Arun H S        Modify
  * 2008-09-01  liangjicheng             IPv6 Modify szPrompt size 40->64
 ********************************************************************************/
extern ULONG IP6_PP_Output (MBUF_S *pstMBuf, IP6_PKTOPTS_S *pstOpt, ULONG ulZoneId, LONG lFlags, IP6_MOPTIONS_S *pstMo);

/********************************************************************************
 * Prototype     : ULONG  IP6_PP_PM_Protocol_Register (LONG lPID,
 *                                                  IP6_PP_PROTOSW_S *pstinfo)
 * Description   : Protocol Registration Function
 * Input(s)      :
 *                 lPID -
 *                 pstProtocolInfo -
 * Output(s)     : N/A
 * Return        : TRUE/FALSE
 *-------------------------------------------------------------------------------
 * History
 * Date(yyyy-mm-dd)     Author        Modification
 *  2003-06-10           Arun          Created
 ********************************************************************************/
extern ULONG IP6_PP_PM_Protocol_Register (LONG lPID, IP6_PP_PROTOSW_S *pstProtocolInfo);

/*******************************************************************************
*    Func Name: TCPIP_PP6Output
* Date Created: 2014-02-28
*       Author: likaikun213099
*  Description: ����IPv6����
*        Input: MBUF_S* pstMBuf:���ģ���Ҫ����DOPRA MBUF��������ȡDOPRA��MBUF�ڴ���װ���ķ���
*       Output: �ɹ���VOS_OK
*               ʧ�ܣ�VOS_ERR
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-02-28   likaikun213099          Create
*
*******************************************************************************/
extern ULONG TCPIP_PP6Output(MBUF_S* pstMBuf);


extern ULONG TCPIP_PP6_PktTypeStat_Register(TCPIP_PP6_PKTTYPE_STAT_KEY_S  *pKey);


extern ULONG TCPIP_PP6_PktTypeStat_UnRegister(TCPIP_PP6_PKTTYPE_STAT_KEY_S  *pKey);


extern ULONG TCPIP_GetPP6PktTypeStat(TCPIP_PP6_PKTTYPE_STAT_KEY_S  *pKey, 
                                         TCPIP_PP6_PKTTYPE_STAT_S *pstFlowStat);


extern ULONG TCPIP_ClrPP6PktTypeStat(TCPIP_PP6_PKTTYPE_STAT_KEY_S  *pKey);


extern ULONG TCPIP_ClrPP6PktStatAll(VOID);


extern ULONG TCPIP_ShowPP6PktTypeStat(VOID);


extern ULONG TCPIP_RegLookupNdHook(pfTCPIPNeedLookupNdHook pfHookFunc);


#ifdef __cplusplus
}
#endif      /* end of _cplusplus        */

#endif      /* end of _PPMNG_API_H_    */

