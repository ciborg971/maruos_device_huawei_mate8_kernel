/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              pp4_pub.h
*
*  Project Code: VISP1.5
*   Module Name: PP4  
*  Date Created: 2002-06-18
*        Author: chenshuanglong(28510)
*   Description: PP4�����ṩ�ĺꡢ���ݽṹ����
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2002-06-18   chenshuanglong(28510)   Create
*  2006-05-11   luyao(60000758)         Ϊ֧��ARM CPU�ֽڶ������ԣ��޸Ľṹ��
*  2006-11-01   zhoutong(43740)         �淶������
*
*******************************************************************************/


#ifdef  __cplusplus
extern  "C"{
#endif

#ifndef _PP4_PUB_H_
#define _PP4_PUB_H_

#include"tcpip/ip4/pp4/include/pp4_api.h"

#define PR_SLOWHZ   2       /* 500ms��ʱ��        2 slow timeouts per second */
#define PR_FASTHZ   5       /* 200ms��ʱ��        5 fast timeouts per second */


/*
 * �˿ں� < IPPORT_RESERVED �����ظ����ȼ��Ľ���ʹ��
 * Local port number conventions:
 * Ports < IPPORT_RESERVED are reserved for
 * privileged processes (e.g. root).
 *
 * �˿ں� > IPPORT_RESERVED �Ĺ�������ʹ��
 * Ports > IPPORT_USERRESERVED are reserved
 * for servers, not necessarily privileged.
 */


/*
 *�������µ�IANA(2006-05-31), ������ʱ�˿ںŵ� l60006581   
 *extend temporary port's range by l60006581 for lastly 'iana', 2006-05-31 
 */ 
extern USHORT g_usIpPortReservedStart;
extern USHORT g_usIpPortReservedEnd;
#define IPPORT_TRRTDEFAULT   30000

#ifndef IPPROTO_LEG_DHCP
#define IPPROTO_LEG_DHCP 0xffffffff
#endif



/* socket�϶ಥ�鳬��256��ʱ��256���������ڴ� */
#define EX_MULTILEN     256

#ifndef MACADDRLEN
#define MACADDRLEN       6       /*physical��ַ����*/
#endif

/*
 * usrreq�Ĳ�����(*protosw[].pr_usrreq)(up, req, m, nam, opt) ;
 * The arguments to usrreq are:
 *  (*protosw[].pr_usrreq)(up, req, m, nam, opt);

 * ����up��socketָ��,req����Щ����֮һ
 * where up is a (struct socket *), req is one of these requests,
 
 * m�Ǳ�����Ϣ�Ŀ�ѡmbuf��
 * m is a optional mbuf chain containing a message,
 
 * nam�Ǳ����ַ�Ŀ�ѡmbuf��
 * nam is an optional mbuf chain containing an address,

 * opt��socketoptָ��,���߿�ָ��
 * and opt is a pointer to a socketopt structure or nil.

 * ��Э��ֻ������mbuf��
 * The protocol is responsible for disposal of the mbuf chain m,

 * ���������ṩnam��optʹ�õĿռ�
 * the caller is responsible for any space held by nam and opt.

 * ��usrrep���ط���, ���贫��һ��UNIX��������ϲ��������
 * A non-zero return from usrreq gives an
 * UNIX error number which should be passed to higher level software.
 */
 
#define PRU_ATTACH          0   /* ����Э��             attach protocol to up */
#define PRU_DETACH          1   /* ��Э�����           detach protocol from up */
#define PRU_BIND            2   /* Ϊsocket�󶨵�ַ     bind socket to address */
#define PRU_LISTEN          3   /* ��������             listen for connection */
#define PRU_CONNECT         4   /* �����Զ˵�����       establish connection to peer */
#define PRU_ACCEPT          5   /* ���ܶԶ˵�����       accept connection from peer */
#define PRU_DISCONNECT      6   /* ȡ���Զ˵�����       disconnect from peer */
#define PRU_SHUTDOWN        7   /* ���ٷ�������         won't send any more data */
#define PRU_RCVD            8   /* ��������             have taken data; more room now */
#define PRU_SEND            9   /* ��������             send this data */
#define PRU_ABORT           10  /* ��ֹ[���ٶϿ�,����]  abort (fast DISCONNECT, DETATCH) */
#define PRU_CONTROL         11  /* Э�����             control operations on protocol */
#define PRU_SENSE           12  /* ����״̬��m          return status into m */
#define PRU_RCVOOB          13  /* ��ȡband����         retrieve out of band data */
#define PRU_SENDOOB         14  /* ����band����         send out of band data */
#define PRU_SOCKADDR        15  /* ��ȡsocket��ַ       fetch socket's address */
#define PRU_PEERADDR        16  /* ��ȡ�Զ˵�ַ         fetch peer's address */
#define PRU_CONNECT2        17  /* ��������socket       connect two sockets */

/* ��Э���ڲ�ʹ��   begin for protocols internal use */
#define PRU_FASTTIMO        18  /* 200ms ��ʱ    200ms timeout */
#define PRU_SLOWTIMO        19  /* 500ms ��ʱ    500ms timeout */
#define PRU_PROTORCV        20  /* �²����      receive from below */
#define PRU_PROTOSEND       21  /* �²�ַ�      send to below */

#define PRU_NREQ            21
#define PRU_UNBIND          22  /* ���socket�ͽӿڵİ   unbind socket to interface */

/*
 * ctlinput routine�Ĳ�����: (*protosw[].pr_ctlinput)(cmd, sa, arg);
 * The arguments to the ctlinput routine are
 *  (*protosw[].pr_ctlinput)(cmd, sa, arg);
 
 * ����cmd����������֮һ:  sa��sockaddrָ��
 * where cmd is one of the commands below, sa is a pointer to a sockaddr,

 * arg����Э������ʹ�õ�һ��caddr_t��ѡ����
 * and arg is an optional caddr_t argument used within a protocol family.
 */
 
#define PRC_IFDOWN              0   /* �ӿ�ת��             interface transition */
#define PRC_ROUTEDEAD           1   /* ѡ����·��           select new route if possible ??? */
#define PRC_QUENCH2             3   /* DECӵ��ָʾλ        DEC congestion bit says slow down */
#define PRC_QUENCH              4   /* Դվ������           some one said to slow down */
#define PRC_MSGSIZE             5   /* ���Ĺ���,ǿ�ƶ���    message size forced drop */
#define PRC_HOSTDEAD            6   /* ��������Ӧ           host appears to be down */
#define PRC_HOSTUNREACH         7   /* ���Ƽ�(��ʹ��PRC_UNREACH_HOST)   deprecated (use PRC_UNREACH_HOST) */
#define PRC_UNREACH_NET         8   /* ������·��           no route to network */
#define PRC_UNREACH_HOST        9   /* ������·��           no route to host */
#define PRC_UNREACH_PROTOCOL    10  /* Ŀ�Ķ˻ظ�����Э��   dst says bad protocol */
#define PRC_UNREACH_PORT        11  /* ����˿ں�           bad port # */

/* was  PRC_UNREACH_NEEDFRAG    12     (use PRC_MSGSIZE) */
#define PRC_UNREACH_SRCFAIL     13  /* Դ·��ʧ��           source route failed */
#define PRC_REDIRECT_NET        14  /* ����·���ض���       net routing redirect */
#define PRC_REDIRECT_HOST       15  /* ����·���ض���       host routing redirect */
#define PRC_REDIRECT_TOSNET     16  /* �Է������ͺ������ض���  redirect for type of service & net */
#define PRC_REDIRECT_TOSHOST    17  /* �Է������ͺ������ض���  direct for tos & host */
#define PRC_TIMXCEED_INTRANS    18  /* �����ڼ����ݱ�����     packet lifetime expired in transit */
#define PRC_TIMXCEED_REASS      19  /* reass q���ݱ�����      lifetime expired on reass q */
#define PRC_PARAMPROB           20  /* ͷ������             header incorrect */

/* Start: RFC4443 compliance changes */ 
#define PRC_BEYOND_SCOPE          21 /* ����������          Beyond scope */ 
#define PRC_INGRESS_EGRESS_POLICY 22 /* ���/���ڹ������   ingress/egress policy filter */ 
#define PRC_REJECT_ROUTE          23 /* �ܾ�·�����ó�dst   reject route configured to dst */ 
/* End: RFC4443 compliance changes */ 
 
#define PRC_NCMDS               24

#define PRC_IS_REDIRECT(cmd)    \
    ((cmd) >= PRC_REDIRECT_NET && (cmd) <= PRC_REDIRECT_TOSHOST)

/* control code */
#define PRCO_GETOPT 0
#define PRCO_SETOPT 1
#define PRCO_NCMDS  2



/*
 * pr_flagsʹ�õ�ֵ:
 * Values for pr_flags.

 * PR_ADDR ��ҪPR_ATOMIC
 * PR_ADDR requires PR_ATOMIC;

 * PR_ADDR �� PR_CONNREQUIRED ���໥������
 * PR_ADDR and PR_CONNREQUIRED are mutually exclusive.
 */
 
#define PR_ATOMIC       0x01        /* ֻ������������Ϣ    exchange atomic messages only */
#define PR_ADDR         0x02        /* ��Ϣ�а�����ַ      addresses given with messages */
#define PR_CONNREQUIRED 0x04        /* Э��Ҫ������        connection required by protocol */
#define PR_WANTRCVD     0x08        /* ��ҪPRU_RCVD����    want PRU_RCVD calls */
#define PR_RIGHTS       0x10        /*                     passes capabilities */


/*
 * Internet ʵ�ֲ���
 * Internet implementation parameters.
 */
#define MAXTTL      255     /* �����ʱ��(��)        maximum time to live (seconds) */
#define IP_DEFTTL   255     /* Ĭ��TTL��64��Ϊ255,     default ttl changed from 64 to 255, by heqiangc for D13166, 2001-11-24 */
#define IP_FRAGTTL  60      /* ��Ƭ���ĵ������ʱ��  time to live for frags, slowhz */
#define IP_TTLDEC   1       /* ת��ʱ�ļ�ȥֵ          subtracted when forwarding */

/* Added by Yiyu for MPLS Ping/Traceroute. 2004/08/23 */
#define IP_SENDBY_LSPV_FEC  SO_SENDBY_LSPV_FEC

/*
 * ��ѡ���ȱʡֵ������ֵ
 * Defaults and limits for options
 */
#define IP_DEFAULT_MULTICAST_TTL  1 /* ȱʡ���ƶಥ����Ϊ1��                      normally limit m'casts to 1 hop  */
#define IP_DEFAULT_MULTICAST_LOOP 1 /* ������Ա����                               normally hear sends if a member  */
#define IP_MAX_MEMBERSHIPS        4096  /* ÿ��socket���뱣����һ��one mbuf��     per socket; must fit in one mbuf */

#define IP_MAX_SOURCE       16    /* ��socket��,ÿ�������Դ������Ϊ16    the source number of per multi-group in socket limits to 16*/

#define IP_MSS              576     /* ȱʡ�����γ�    default maximum segment size */


#define IP_RAWOUTPUT        0x2     /* ����raw ipͷ     raw ip header exists */


#define EUNREACH            31
/* FIB */
#define IP_FIB_BLACKHOLE    1
#define IP_ENETUNREACH      2
#define IP_FIB_REJECT2      3
#define IP_LOCAL_FORWARDING    (0)    /* ��ʾ�ñ����߱���ת�� */
#define MPLS_L3VPN_FORWARDING (4)     /* ��ʾ������VPN ���ģ������ת�� */
/* End: VISP Support multi-instance project */

/************************************************************************************/
#define   DISP_HEAD               VRP_YES 
#define   DISP_NONE               VRP_NO

#define IPVLAN_VLANID_MASK  0xfff
#define IPGETPRECEDENCE(pIp) ((pIp->ip_chTOS>>5)&0x07)

#define IPID_UPDATECOUNT     0x400
/* End of Added by wangbin, 2015/10/24 */

/*
 * ����ѡ���,Internet ͷ�ṹ
 * Structure of an internet header, naked of options.

 * ����Ҫ��ip_len��ip_off��short�͵�,������u_short
 * We declare ip_len and ip_off to be short, rather than u_short

 * ��Ϊ�޷����͵ıȽ��� , ���׳���
 * pragmatically since otherwise unsigned comparisons can result
 * against negative integers quite easily, and fail in subtle ways.
 */
struct  tagINADDR;

/* IP_S�Ѿ�Ų��pp4_api.h */

/*IPSTAT_S�Ѿ�Ų��pp4_api.h*/


typedef struct tagIpGlobalMibStat{
    ULONG ulInReceives;
    ULONG ulInHdrErrors;
    ULONG ulInAddrErrors;
    ULONG ulForwDatagrams;
    ULONG ulInUnknownProtos;
    ULONG ulInDiscards;
    ULONG ulInDelivers;
    ULONG ulOutRequests;
    ULONG ulOutDiscards;
    ULONG ulOutNoRoutes;
    ULONG ulReasmTimeout;
    ULONG ulReasmReqds;
    ULONG ulReasmOKs;
    ULONG ulReasmFails;
    ULONG ulFragOKs;
    ULONG ulFragFails;
    ULONG ulFragCreates;
    ULONG ulRoutingdiscards;
}IP_PP4_GLOBALMIB_STAT_S;


/*---------------------------------------------------------------*/
/* for IP and TCP reassemble                                     */
/*---------------------------------------------------------------*/
struct tagQUEUE;
typedef struct tagQUEUE
{
    struct tagQUEUE    *pNext;
    struct tagQUEUE    *pPrev;
}QUEUE_S;


/**********************************************************************
* ip multicast source list struct used by socket
**********************************************************************/
typedef struct tagIPMREQ_SOURCELIST
{
    ULONG ulSourceAddr;                               /* ���յ��Ķಥ���ݰ��еĵ�ַ   address that is in the multicast packet recieved*/
    struct tagIPMREQ_SOURCELIST * pstNextSourceAddr;  /* ָ����һ��Դ��ַ               point to next source address*/
}IPMREQ_SOURCELIST_S;
/*
 * Argument structure for IP_ADD_MEMBERSHIP and IP_DROP_MEMBERSHIP.
 */
typedef struct tagIPMREQ
{
    struct  tagINADDR imr_stMultiAddr;              /* ���IP �ಥ��ַ     IP multicast address of group */
    ULONG   imr_ulIndexIf;                          /* �ӿڵı��ص�ַ      local address of interface */
    ULONG   imr_ulFilterMode;                       /* �ಥ�����ģʽ,ֻ����IGMP_REPORT_MODE_IN �� IGMP_REPORT_MODE_EX
                                                     * multicast group filter mode, only be IGMP_REPORT_MODE_IN or IGMP_REPORT_MODE_EX*/
    ULONG   imr_ulSourceCount;                      /* ��socket�еĶ���Դ��Ŀ the number of source on the multi-group in socket*/
    struct  tagIPMREQ_SOURCELIST * pstSourcelist;   /* Դ��ַ����ָ��    point to source address list*/
}IPMREQ_S, *PIPMREQ_S;

/**********************************************************************
* ip multicast option struct
**********************************************************************/
struct tagIPMREQ;
typedef struct tagIPMOPTIONS
{
    ULONG   imo_ulIndexIf;      /* �ⷢ�Ķಥifp        ifp for outgoing multicasts */
    UCHAR   imo_bTTL;           /* �ⷢ�ĶಥTTL        TTL for outgoing multicasts */
    UCHAR   imo_bLoop;          /* 1 =>����г�Ա�յ�   1 => hear sends if a member       */
    USHORT  imo_usVIF;          /* outgoing vif no             */

    USHORT  imo_usNumMemberships;       /* socket��Ա�� no. memberships this socket */
    UCHAR   ucPadding_1[2];
    struct  tagIPMREQ *imo_pMembership_a; /* modifed structure imo_pMembership_a by mayun for D13667 2002-01-10 */
    USHORT  imo_usMaxMemberships;
    UCHAR   ucPadding_2[2]; 
}IPMOPTIONS_S, *PIPMOPTIONS_S;

extern LONG     nMaxLinkHdr;            /* ������·��ͷ             largest link-level header */
extern LONG     nMaxProtoHdr;           /* ����Э��ͷ               largest protocol header */
extern LONG     g_lMaxHdr;              /* ������·��Э��ͷ         largest link+protocol header */

/*****************************************************************************
 * �ⲿ�ӿڶ���. ��Щ�ӿڿ��Ա�����ģ��ֱ�ӵ���, ����ʹ������еĽӿڷ���
 * extern interface definition. these interface can be called by other module*
 * directly. also can use component interface method.                        *
 *****************************************************************************/
struct tagROUTE;

/* ������ӿ�, ʹ����VISP��ģ����ֱ�ӵ���, Ϊ���ּ�����,�����Ǳ���������
 * interface for packet process, for modules not in VISP to call directly */
/*  these are kept here for compatibility                                  */

extern ULONG IP_Input(struct tagMBuf * pstMBuf);
extern ULONG IP_IF_Output( struct tagMBuf *pstMBuf, ULONG ulPmtu );
extern ULONG IP_Output(struct tagMBuf *pstMBuf, struct tagMBuf *pstMOpt, struct tagROUTE *pstRo, 
                       LONG lFlags, struct tagIPMOPTIONS *pstIpMo );
extern ULONG IP_Output_ForInternal(struct tagMBuf *pstMBuf, struct tagMBuf *pstMOpt, struct tagROUTE *pstRo, 
                                   LONG lFlags, struct tagIPMOPTIONS *pstIpMo );
extern MBUF_S *IP_SrcRoute();
extern VOID IP_StrIpOptions(register struct tagMBuf *, struct tagMBuf *);
extern USHORT IN_Cksum(struct tagMBuf *pstMBuf, LONG lLen);
extern USHORT Ip_Fast_Cksum(USHORT * pusWord);
/* �ಥ  multicast */
extern LONG IP_SetMOptions(LONG lOptName, struct tagIPMOPTIONS **ppstIpMopP, struct tagMBuf *pstMBuf);
extern LONG IP_GetMOptions(LONG lOptName, struct tagIPMOPTIONS *pstIpMo, struct tagMBuf **ppstMBufP);
extern void IP_FreeMOptions(struct tagIPMOPTIONS *pstIpMo);

extern VOID IP_PP4_DebugACLFilter(MBUF_S *pMBuf, ULONG *pulMatch);

extern USHORT IP_Get_IpId(VOID);


#endif  /* _PP4_PUB_H_  */

#ifdef  __cplusplus
}
#endif

