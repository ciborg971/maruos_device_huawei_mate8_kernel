/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              pp4_input.h
*
*  Project Code: VISP1.5
*   Module Name: PP4  
*  Date Created: 2002-06-18
*        Author: chenshuanglong(28510)
*   Description: pp4_input.cͷ�ļ�
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2002-06-18   chenshuanglong(28510)   Create
*  2006-11-01   zhoutong(43740)         �淶������
*
*******************************************************************************/


#ifdef  __cplusplus
extern  "C"{
#endif

#ifndef _PP4_INPUT_H_
#define _PP4_INPUT_H_

#ifndef MIN
#define MIN(a, b)       ((a)>(b) ? (b):(a)) 
#endif

/*
 * Definitions for internet protocol version 4.
 * Per RFC 791, September 1981.
 */
#define IP_VERSION  4

/*
 * IP packet process parameters
 */
/* flags passed to ip_output as last parameter */
#define IP_SENDDATAIF       SO_SENDDATAIF   /* special output interface */
#define IP_ROUTETOIF        SO_DONTROUTE    /* bypass routing tables */
#define IP_ALLOWBROADCAST   SO_BROADCAST    /* can send broadcast packets */
/* added by mayun for rsvp 2002-12-17 */
#define IP_SENDBY_IF_NEXTHOP SO_SENDBY_IF_NEXTHOP /* specify output interface and nexthop */
/* end of mayun for rsvp */
/* added by mayun for gsr 2003-05-08 */
#define IP_SENDDATAPORT     SO_SENDDATAPORT /*ָ���˿ڷ���*/
/*end of mayun for gsr */
/* Added by Usha */
#define IP_NATPT_NEXTHOP    0x00020000 /* this flag conflicts with SO_SETKEEPALIVE, not a good idea. */
/* end of add by Usha */

#define IP_SENDDATAIF_DONTSETTTL      SO_SENDDATAIF_DONTSETTTL   /* special output interface,but not set TTL*/
#define IP_SENDDATAIF_WITHROUTE       SO_SENDDATAIF_WITHROUTE

/*
 * Definitions for IP type of service (ip_tos)
 */
#define IPTOS_LOWDELAY      0x10
#define IPTOS_THROUGHPUT    0x08
#define IPTOS_RELIABILITY   0x04

/*
 * Definitions for IP precedence (also in ip_tos) (hopefully unused)
 */
#define IPTOS_PREC_NETCONTROL       0xe0
#define IPTOS_PREC_INTERNETCONTROL  0xc0
#define IPTOS_PREC_CRITIC_ECP       0xa0
#define IPTOS_PREC_FLASHOVERRIDE    0x80
#define IPTOS_PREC_FLASH            0x60
#define IPTOS_PREC_IMMEDIATE        0x40
#define IPTOS_PREC_PRIORITY         0x20
#define IPTOS_PREC_ROUTINE          0x00

/*
 * Definitions for options.
 */
/* flag bits for ipt_flg */
#define IPOPT_TS_TSONLY     0       /* timestamps only */
#define IPOPT_TS_TSANDADDR  1       /* timestamps and addresses */
#define IPOPT_TS_PRESPEC    3       /* specified modules only */

/* bits for security (not byte swapped) */
#define IPOPT_SECUR_UNCLASS 0x0000
#define IPOPT_SECUR_CONFID  0xf135
#define IPOPT_SECUR_EFTO    0x789a
#define IPOPT_SECUR_MMMM    0xbc4d
#define IPOPT_SECUR_RESTR   0xaf13
#define IPOPT_SECUR_SECRET  0xd788
#define IPOPT_SECUR_TOPSECRET   0x6bc5

#define IPOPT_COPIED(o)     ((o)&0x80)    /* ���� */
#define IPOPT_CLASS(o)      ((o)&0x60)    /* �ȼ� */
#define IPOPT_NUMBER(o)     ((o)&0x1f)    /* ���� */

#define IPOPT_CONTROL       0x00    /* ���� */
#define IPOPT_RESERVED1     0x20    /* ����1 */
#define IPOPT_DEBMEAS       0x40    /*  */
#define IPOPT_RESERVED2     0x60    /* ����2 */

#define IPOPT_RR_PS            2       /* IPOPT_RRѡ���Ӧ���ر�־λ */
#define IPOPT_TS_PS            4       /* IPOPT_TSѡ���Ӧ���ر�־λ */
#define IPOPT_SECURITY_PS      8       /* IPOPT_SECURITYѡ���Ӧ���ر�־λ */
#define IPOPT_LSRR_PS          16      /* IPOPT_LSRRѡ���Ӧ���ر�־λ */
#define IPOPT_SATID_PS         32      /* IPOPT_SATIDѡ���Ӧ���ر�־λ */
#define IPOPT_SSRR_PS          64      /* IPOPT_SSRRѡ���Ӧ���ر�־λ */
#define IPOPT_ROUTE_ALERT_PS   128     /* IPOPT_ROUTE_ALERTѡ���Ӧ���ر�־λ */
#define IPOPT_UNKOWN_PS    0x80000000  /*��ʶ���ѡ��ر��*/

/*
 * ѡ��ƫ���� Offsets to fields in options other than EOL and NOP.
 */
#define IPOPT_OPTVAL        0       /* ѡ��ID option ID */
#define IPOPT_OLEN          1       /* ѡ��� option length */
#define IPOPT_OFFSET        2       /* ƫ���� offset within option */
#define IPOPT_MINOFF        4       /* ��Сֵ min value of above */
#define IPOPT_MAXOFF        40      /* ���ֵ max value of above .mayun. 20010809 */

#define MAX_IPOPTLEN        40

#define IP_FORWARDING       1       /* forward IP packets not for us */
/* #define IP_SENDREDIRECTS    1   */   /* redirect process on */ 

#define IP_NOTSENDREDIRECTS     1   /* redirect process on */
#define IP_SENDREDIRECTS        0   /* redirect process on */
#define IP_NOTSENDHOSTUNREACH   1   /*add by zhangyaping for host_unreach*/
#define IP_SENDHOSTUNREACH      0   /*add by zhangyaping for host_unreach*/

#define LAND_NO_CFG_SWITCH      0   /* No need to check for land attack. */
#define LAND_PRE_CFG_SWITCH     1   /* Need to check land attack due to pre configuration of land attack switch. */
#define LAND_ATK_CFG_SWITCH     2   /* Need to check land attack due to IP attack switch configuration set. */

/* PP4ģ������� */
enum enumPp4ErrorNum
{
    IP_ERR_OK,
    IP_ERR_UNKNOWN,
    IP_ERR_INVALID_PTR,
    IP_ERR_ETMEXCEED,
    IP_ERR_EUNREACH,
    IP_ERR_VPNROUTING,
};

#define IP_MAXPACKET        65535   /* maximum packet size */

#define IP_MAX_FRAGS        1000    /* ·������IP���������IP��Ƭ�������Ŀ */
#define IP_MAX_REASSQ_NUM   400     /* ·������IP������е������Ŀ */

/* IP������·�����ڲ�ѭ������Ĵ�����������ֵ������IP���� */
#define IP_PKT_MAX_LOOPTIMES    20

#ifndef IP_MULTI_QUERY_IP
#define IP_MULTI_QUERY_IP   0xe0000001 /* ����ಥ��ѯ���ĵ�Ŀ�ĵ�ַ������IGMPЭ�� */
#endif

#ifndef IP_MULTI_VRRP_IP
#define IP_MULTI_VRRP_IP    0xe0000012 /* ����VRRP���ĵ�Ŀ�ĵ�ַ������VRRPЭ�� */
#endif

/*
 * Time stamp option structure.
 */
typedef struct  tagIPTIMESTAMP
{
    UCHAR   ipt_chCode;     /* IPOPT_TS */
    UCHAR   ipt_chLen;      /* size of structure (variable) */
    UCHAR   ipt_chPtr;      /* index of current entry */
#if VRP_LITTLE_ENDIAN == VRP_YES
    UCHAR   ipt_chFlg:4;    /* flags, see below */
    UCHAR   ipt_chOflw:4;   /* overflow counter */
#else
    UCHAR   ipt_chOflw:4;   /* overflow counter */
    UCHAR   ipt_chFlg:4;    /* flags, see below */
#endif
    union tagIPTTIMESTAMP
    {
        ULONG   ipt_time[1];
        struct  tagIPTTA
        {
            struct tagINADDR ipt_stAddr;
            ULONG  ipt_nlTime;
        } ipt_stTa[1];
    } ipt_unTimeStamp;
}IPTIMESTAMP_S;

/*
 * Ip header, when holding a fragment.
 *
 * Note: ipf_next must be at same offset as ipq_pNext of IPREASSQUEUE_S
 */
typedef struct  tagIPASFRAG
{
#if VRP_LITTLE_ENDIAN == VRP_YES
    UCHAR   ip_chHLen:4;        /* header length */
    UCHAR   ip_chVer:4;         /* version */
#else
    UCHAR   ip_chVer:4;         /* version */
    UCHAR   ip_chHLen:4;        /* header length */
#endif
    UCHAR   ipf_chMff;          /* XXX overlays ip_tos: use low bit to avoid destroying tos; copied from (ip_off&IP_MF)*/
    USHORT  ip_sLen;            /* total length */
    USHORT  ip_usId;            /* identification */
    USHORT  ip_sOff;            /* offset */
    MBUF_S  *ipf_pMBuf;
#ifdef TCPIP_NOVRP_64BIT
    UINTPTR   ip_pReserved;           /* reserved */
#endif
    struct  tagIPASFRAG  *ipf_pNext;  /* next fragment */
    struct  tagIPASFRAG  *ipf_pPrev;  /* previous fragment */
}IPASFRAG_S;

/*
 * Ip reassembly queue structure.  Each fragment
 * being reassembled is attached to one of these structures.
 * They are timed out after ipq_ttl drops to 0, and may also
 * be reclaimed if memory becomes tight.
 */
typedef struct tagIPREASSQUEUE
{
    struct tagIPREASSQUEUE *pNext;  /* next reass headers*/
    struct tagIPREASSQUEUE *pPrev;  /* previous reass headers */
    UCHAR  ipq_chTTL;               /* time for reass q to live */
    UCHAR  ipq_chPr;                /* protocol of this fragment */
    USHORT ipq_usId;                /* sequence id for reassembly */
#ifdef TCPIP_NOVRP_64BIT
    UCHAR  ip_chReserved[4];        /* reserved */
#endif    
    struct tagIPASFRAG *ipq_pNext;  /* next fragments */
    struct tagIPASFRAG *ipq_pPrev;  /* previous fragments */
    struct tagINADDR ipq_stSrc;     /* source address */
    struct tagINADDR ipq_stDst;     /* destenation address*/
    UCHAR  ipq_chFirstFragTTL;      /* time for reass q to live */
    UCHAR  ucPadding[3]; 
    ULONG  ulVrfIndex;              /* ��IP��������VRF��vrfindex, added by yuyong&mayun 2002/10/30 for address overlap*/
    /* MBUF_S    *ipq_pMBuf;*/
}IPREASSQUEUE_S;

/*·�ɻ���ṹ*/
typedef struct tagIPROUTECACHE_S
{
    ULONG  ulIPAddr;               /*����Ŀ�ĵ�ַ*/
    ULONG  ulNextHop;              /*����ת������һ��*/
    ULONG  ulOutIfIndex;           /*���ĳ��ӿ�����*/
    ULONG  ulATIndex;              /*����vlink����*/
    ULONG  ulRcvInIndex;           /*������ӿ�����*/
    ULONG ulPmtu;                 /* Added by a00900892, PMTU for static routes*/
}IPROUTECACHE_S;

extern IPSTAT_S    stIpStat;            /* ȫ��IPͳ����Ϣ */
extern UCHAR       *ucDebugInfo[];      /* ������Ϣ */
extern ULONG       g_ulIpPktLoopTimes;  /* IP����ѭ������Ĵ�����������ֵ���� */
extern USHORT      g_usIpId;              /* ip packet ctr, for ids */
extern ULONG           g_ulIpDoRandomId;
extern IPREASSQUEUE_S  g_stIpReassQueue;/* ip reass. queue */
extern IPROUTECACHE_S  g_ulIpRouteCache ; /*·�ɻ���*/
extern ULONG      g_ulIPMissCnt   ;  /*·�ɻ�������ʧ�ܵļ���*/

/* IP���Ĵ����� */
extern ULONG IP_ProcessByBoard(MBUF_S *pstMBuf, IFNET_S *pstIfNet, IPIFNET_S *pstIpCtl);
extern ULONG  IP_DeliverToUp( MBUF_S *pstMBuf );
extern ULONG IP_Distribute(MBUF_S *pstMBuf);
extern VOID  IP_FillMBufQoSTag(MBUF_S * pstMBuf);
extern VOID  IP_FreeF( IPREASSQUEUE_S *pstIpQ);
extern ULONG IP_PP4_InitPktProcParams();
extern VOID  IP_Link_DropPacket(MBUF_S * pstMBuf);
extern ULONG IP_IsLocalAddressByFIB(INADDR_S* pstDst,  MBUF_S* pstMbuf);
extern ULONG IP_Attack_PermitCheckProc(MBUF_S *pstMBuf, ULONG ulType);

#endif  /* _PP4_INPUT_H_  */

#ifdef  __cplusplus
}
#endif

