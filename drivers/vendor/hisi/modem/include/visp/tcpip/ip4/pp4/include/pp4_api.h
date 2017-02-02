
#ifndef __PP4_API_H__
#define __PP4_API_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/* address family  */
#ifndef AF_INET
#define AF_INET         2               /* internetwork: UDP, TCP, etc. */
#endif


/* protocol number */
#ifndef IPPROTO_MAX
#define IPPROTO_MAX     256
#endif

#ifndef IPPROTO_RAW
#define IPPROTO_RAW     255     /* raw IP packet */
#endif

#ifndef IPPROTO_IP
#define IPPROTO_IP      0       /* ����IP  dummy for IP */
#endif
#ifndef IPPROTO_ICMP
#define IPPROTO_ICMP    1       /* ���Ʊ���Э��  control message protocol */
#endif
#ifndef IPPROTO_IGMP
#define IPPROTO_IGMP    2       /* �����Э��  group mgmt protocol */
#endif
#ifndef IPPROTO_GGP
#define IPPROTO_GGP     3       /* ·��^2Э���(������)  gateway^2 (deprecated) */
#endif
#ifndef IPPROTO_IPIP            /* IPЭ��֮�ϵ�IP  ip over ip protocol */
#define IPPROTO_IPIP    4
#endif
#ifndef IPPROTO_TCP
#define IPPROTO_TCP     6       /* �������Э��  tcp */
#endif
#ifndef IPPROTO_EGP
#define IPPROTO_EGP     8       /* �ⲿ·��Э��  exterior gateway protocol */
#endif
#ifndef IPPROTO_PUP
#define IPPROTO_PUP     12      /* pup */
#endif
#ifndef IPPROTO_UDP
#define IPPROTO_UDP     17      /* user datagram protocol */
#endif
#ifndef IPPROTO_IDP
#define IPPROTO_IDP     22      /* xns idp */
#endif
#ifndef IPPROTO_TP
#define IPPROTO_TP      29      /* tp-4 w/ class negotiation */
#endif
#ifndef IPPROTO_IPV6
#define IPPROTO_IPV6    41      /* IPv6 in IP */
#endif
#ifndef IPPROTO_GRE
#define IPPROTO_GRE     47      /* Generic Route Encapsulation Protocol */
#endif
#ifndef IPPROTO_ESP
#define IPPROTO_ESP     50      /* Ip Sec */
#endif
#ifndef IPPROTO_AH 
#define IPPROTO_AH      51      /* Ip Sec */
#endif
#ifndef IPPROTO_EON
#define IPPROTO_EON     80      /* ISO cnlp */
#endif
#ifndef IPPROTO_ENCAP
#define IPPROTO_ENCAP   98      /* encapsulation header */
#endif
#ifndef IPPROTO_PIM             /* PIM */
#define IPPROTO_PIM     103
#endif
#ifndef IPPROTO_VRRP
#define IPPROTO_VRRP    112     /*  VRRP */
#endif
#ifndef IPPROTO_ISIS
#define IPPROTO_ISIS    124     /* ISIS over IPv4 */ /* Added by Leon on 20040210 for isis on ipv6 tunnel */
#endif

#ifndef IPPROTO_RAWSCTP
#define IPPROTO_RAWSCTP     132        /* SCTP protocol */
#endif

#ifndef IP_VERSION
#define IP_VERSION  4
#endif

#define PP4_INPUT_NORMAL        0
#define PP4_INPUT_DISTRIBUTE    1

/* pp4�����붨�壬Ų��pp4_core.h */
/* return value for methods in pp4 Cfg interface  */
#define IP_PP4_CFG_OK        VOS_OK
#define IP_PP4_CFG_GEN_ERR   VOS_ERR
#define IP_PP4_CFG_PARA_ERR  2
#define IP_PP4_CFG_IOREQ_ERR 3
#define IP_PP4_CFG_NULL_INT      4   /* ָ���Ľӿ�ָ��Ϊ�գ������ڽӿ�������Ч������Ӧ�ӿ� */
#define IP_PP4_CFG_NULL_POINTER  5   /* �����ָ��Ϊ�� */
#define IP_PP4_CFG_ERR_HOOKTYPE  6   /* �����HOOK�������ʹ��� */
#define IP_PP4_CFG_HA_IS_SMOOTHING 7  /*HA����ƽ��������ֶ���������*/
#define IP_PP4_CFG_NULL_HEAD       8  /*����ͷ���Ϊ��*/
#define IP_PP4_CFG_MEMMALLOC_FAIL  9  /*�ڴ����ʧ��*/
#define IP_PP4_CFG_UNREGISTER_FAIL  10 /*��̬��ע��ʧ��*/
#define IP_PP4_CFG_ALREADY_REGISTERED  11 /* �����Ѿ�ע�� */
#define IP_PP4_CFG_NULLIPCTLBLOCK      12 /* IP���ƿ�Ϊ�� */
#define IP_PP4_ERR_IS_L2PORT           13 /* �����Ŀ��ӿ��Ƕ���˿� */

/* intermediate process not processed the packet. 
 * Stack (PP) will do the processing
 */
#define IP_PP4_NOT_PROCESSED_BY_INTERMEDIATE              0 
/* intermediate found the packet has Error, Stack will Destroy the Packet */
#define IP_PP4_INTER_PROCESS_ERROR                        1
/* Intermediate Processing will continue processing and will own the packet
 * PP do not need to process the packet any more
 */
#define IP_PP4_PROCESSED_BY_INTERMEDIATE                  2 

/* ip pakcet hooks type */
#define IP_PP4_HOOK_INPUT_ALL_PKT                   0x01
#define IP_PP4_HOOK_INPUT_LOCAL_PKT                 0x02
#define IP_PP4_HOOK_FORWARD_PKT                     0x04
#define IP_PP4_HOOK_OUTPUT_LOCAL_PKT                0x08
#define IP_PP4_HOOK_OUTPUT_ALL_PKT                  0x10
/* Add for BC3D03018*/
#define IP_PP4_HOOK_REASS_PKT                       0x20

/* ��MBUF��TAG�������ã���ʾ��IP���ĵ�Ŀ�ص�ַ�Ǳ���ĳ���ӿڵĵ�ַ */
#define IP_PKT_ISOURS           0x00000001

/* ��MBUF��TAG�������ã���ʾ�Ǳ�������ӿڵĹ㲥���� */
#define IP_PKT_IIFBRAODCAST     0x00000002

/* ��MBUF��TAG�������ã���ʾ�Ǳ�������ӿڵĹ㲥���� */
#define IP_PKT_OIFBRAODCAST     0x00000004

/* ��MBUF��TAG�������ã���ʾ�Ǳ������͵�IP���� */
#define IP_PKT_OURSENDPKT       0x00000008

/* ��MBUF��TAG�������ã���ʾ��ת����IP���� */
#define IP_PKT_FORWARDPKT       0x00000010

/* ��MBUF��TAG�������ã���ʾ�Ǹñ�����̫���Ĺ㲥���� */
#define IP_PKT_ETHBCAST         0x00000020

/*added by zhaobiao for resolve wether source route opt is set*/
#define IP_PKT_SRCROUTE         0x80000000

/* ��־����Ϊ�鲥����·��ת��,��Ҫ�����ӿڵĺϷ��� */
#define IP_PKT_MCAST_PR         0x40000000

#define IPOPT_EOL           0       /* ѡ���б���� end of option list */
#define IPOPT_NOP           1       /* �޲��� no operation */
#define IPOPT_RR            7       /* ��¼���ľ���·�� record packet route */
#define IPOPT_TS            68      /* ʱ��� timestamp */
#define IPOPT_SECURITY      130     /* �ṩs,c,h,tcc  provide s,c,h,tcc */
#define IPOPT_LSRR          131     /* ����Դվѡ·  loose source route */
#define IPOPT_SATID         136     /* satnet id */
#define IPOPT_SSRR          137     /* �ϸ�Դվѡ· strict source route */
#define IPOPT_ROUTE_ALERT   148     /* ����·�߸澯����ֵΪ����ֱ�ӷ��� route alert, if value is 0, then delivertoup */
#define IPOPT_UNKOWN        0x80000000 /*��ʶ���ѡ����*/

/* IPѡ���Ӧ����״̬�궨�� */
#define IPOPT_PS_ON 1
#define IPOPT_PS_OFF 0
/* IPѡ��ĳ�ʼֵ(ȱʡֵ)�궨�� */
#define IPOPT_PS_DEFAULT 0xFFFFFFFF

/* IP�㱨�Ĺ����������ö�ٶ��� */
typedef enum tagIP_DEBUG_FILTER
{
    IP_DEBUG_FILTER_IFINDEX = 0,      /* �ӿ����� */
    IP_DEBUG_FILTER_SRCIP,            /* ԴIP */
    IP_DEBUG_FILTER_DSTIP,            /* Ŀ��IP */
    IP_DEBUG_FILTER_PROTO,            /* Э��� */
    IP_DEBUG_FILTER_SRCPORT,          /* Դ�˿� */
    IP_DEBUG_FILTER_DSTPORT,          /* Ŀ�Ķ˿� */
    IP_DEBUG_FILTER_MAX               /* end */
}IP_DEBUG_FILTER_E;

/* IP�㱨�Ĺ���������غ궨�� */
#define IP_DEBUG_FILTER_FLAG_NOR 1    /* ����ͨ���Ĺ��� */
#define IP_DEBUG_FILTER_FLAG_VBS 2    /* ����ϸ���Ĺ��� */

/* ע��ԴIP·�ɺ�,���ķ��ͷ�ʽ�궨�� */
#define IP_GO_WITH_SRCROUTE      0    /* ��Դ·�ɷ��ͱ��� */
#define IP_DROP_PACKET           1    /* �������� */
#define IP_GO_PASS               2    /* ��ԭ�з�ʽ���ͱ��� */

typedef ULONG (*IP_PP4_INTERMEDIATE_HOOK_FUNC)(struct tagMBuf *pstMBuf);

/* ��IP���ͷ�Ƭ֮ǰ��ȡ������IP����, ��ȡ����IP�����ײ������ֶζ���ʹ����������д��ϣ����Ѽ���У���
   ���˵��:
   pstMbuf: IP����
   ����ֵ˵��:
   0  ���Ӻ����Ѵ������ͷ��˱���
   1  ���Ӻ���δ�����ģ���VISP�������� */
typedef ULONG (*IP4_SEND_WHOLE_PKT_HOOK)(struct tagMBuf *pstMbuf);

typedef struct tagIP
{
#if VRP_LITTLE_ENDIAN == VRP_YES
    UCHAR   ip_chHLen:4;        /* header length */
    UCHAR   ip_chVer: 4;         /* version */
#else
    UCHAR  ip_chVer:  4;         /* version */
    UCHAR  ip_chHLen: 4;        /* header length */
#endif
    UCHAR   ip_chTOS;           /* type of service */
    USHORT  ip_usLen;           /* total length */
#define ip_sLen ip_usLen
    USHORT  ip_usId;            /* identification */
    USHORT  ip_usOff;           /* fragment offset field */
#define ip_sOff ip_usOff
#define IP_DF 0x4000            /* dont fragment flag */
#define IP_MF 0x2000            /* more fragments flag */
#define IP_OFFMASK 0x1fff       /* mask for fragmenting bits */
    UCHAR   ip_chTTL;           /* time to live */
    UCHAR   ip_chPr;            /* protocol */
    USHORT  ip_usSum;           /* checksum */
    struct  tagINADDR ip_stSrc;
    struct  tagINADDR ip_stDst; /* source and dest address */
}IP_S;

typedef struct  tagIPIFSTAT
{   /* generic interface information */
    ULONG   ifi_ulMetric;    /* routing metric (external only) */
    ULONG   ifi_ulLoad;      /* load on in this interface */
    /* volatile statistics */
    ULONG   ifi_ulIPackets;  /* packets received on interface */
    ULONG   ifi_ulOPackets;  /* packets sent on interface */
    ULONG   ifi_ulIBytes;    /* total number of octets received */
    ULONG   ifi_ulOBytes;    /* total number of octets sent */
    ULONG   ifi_ulIMcasts;   /* packets received via multicast */
    ULONG   ifi_ulOMcasts;   /* packets sent via multicast */
    ULONG   ifi_ulIDropPkts; /* drop packets received on interface */
    ULONG   ifi_ulIDropBytes;/* drop bytes received on interface */
    ULONG   ifi_ulODropPkts; /* drop packets sent on interface */
    ULONG   ifi_ulODropBytes;/* dorp bytes sent on interface */
    ULONG   ipi_ulHookProcessed;    /* processed by hook */
    ULONG   ipi_ulHookNotProcessed; /* not processed by hook */
    ULONG   ipi_ulHookBcastProcessed;   /* b-cast packets processed by hook */
    ULONG   ipi_ulHookBcastNotProcessed;/* b-cast packets not processed by hook */
    ULONG   ipi_ulHookMcastProcessed;   /* m-cast packets processed by hook */
    ULONG   ipi_ulHookMcastNotProcessed;/* m-cast packets not processed by hook */
    ULONG   ipi_ulPpiProcessed;         /* processed by ppi output */
    ULONG   ipi_ulPpiNotProcessed;      /* not processed by ppi output */
    ULONG   ipi_ulPpiBcastProcessed;    /* b-cast packets processed by ppi output */
    ULONG   ipi_ulPpiBcastNotProcessed; /* b-cast packets not processed by ppi output */
    ULONG   ipi_ulPpiMcastProcessed;    /* m-cast packets processed by ppi output */
    ULONG   ipi_ulPpiMcastNotProcessed; /* m-cast packets not processed by ppi output */
}IPIFSTAT_S;

typedef struct  tagIPIFSTAT_LIST
{
    ULONG      ulIfIndex;
    IPIFSTAT_S stIpIfStat;
}IPIFSTAT_LIST_S;



/*****************************************************************
* global ip statictics struct Ų��pp4_pub.h
*****************************************************************/
typedef struct tagIPSTAT
{
    ULONG   ips_ulTotal;         /* total packets received */
    ULONG   ips_ulBadVers;       /* ip version != 4 */
    ULONG   ips_ulBadSum;        /* checksum bad */
    ULONG   ips_ulBadHLen;       /* ip header length < data size */
    ULONG   ips_ulBadLen;        /* ip length < ip header length */
    ULONG   ips_ulTooShort;      /* packet too short */
    ULONG   ips_ulTooSmall;      /* not enough data */
    ULONG   ips_ulTTLExceed;     /* ttl exceed, add by heqiangc on 2001-11-01 */
    ULONG   ips_ulBadOptions;    /* error in option processing */
    ULONG   ips_ulCantForward;   /* packets rcvd for unreachable dest */
    ULONG   ips_ulForward;       /* packets forwarded */
    ULONG   ips_ulNoProto;       /* unknown or unsupported protocol */
    ULONG   ips_ulInDiscards;    /* packets discarded because resource limit */
    ULONG   ips_ulDelivered;     /* datagrams delivered to upper level*/
    ULONG   ips_ulLocalOut;      /* total ip packets generated here */
    ULONG   ips_ulODropped;      /* lost packets due to nobufs, etc. */
    ULONG   ips_ulNoRoute;       /* packets discarded due to no route */
    ULONG   ips_ulFragments;     /* fragments received */
    ULONG   ips_ulReassembled;   /* total packets reassembled ok */
    ULONG   ips_ulFragDropped;   /* frags dropped (dups, out of space) */
    ULONG   ips_ulFragTimeout;   /* fragments timed out */
    ULONG   ips_ulFragmented;    /* datagrams sucessfully fragmented */
    ULONG   ips_ulCantFrag;      /* don't fragment flag was set, etc. */
    ULONG   ips_ulOFragments;    /* output fragments created */
    ULONG   ips_ulRedirectSent;  /* packets forwarded on same net */
    ULONG   ips_ulRawOut;        /* total raw ip packets generated */
    ULONG   ips_ulDistSockSent;  /* distributed socket send package */
}IPSTAT_S;

typedef struct tagSrcRtSearch
{
    ULONG ulNextHopIPAddr;  /* ��һ����ַ, ������ */
    ULONG ulOutIfIndex;  /* ���ӿ�, ����������ӿ� */
} SRC_RT_SEARCH_S;


typedef ULONG (*gpfTCPIPSrcRtSearch)(ULONG ulSrcIPAddr, ULONG ulDstIPAddr, SRC_RT_SEARCH_S *pstOutput);

typedef struct tagSrcRtPacket
{
    ULONG ulSrcIPAddr; /* ���ĵ�Դ��ַ,������     */
    ULONG ulDstIPAddr; /* ���ĵ�Ŀ�ĵ�ַ,������   */
    ULONG ulVrfIndex;
} SRC_RT_PKT_S;
typedef ULONG (*TCPIP_SRC_RT_SEARCH_FUN)( SRC_RT_PKT_S *pstPktInfo, SRC_RT_SEARCH_S *pstOutput);


extern ULONG TCPIP_ClrIpStatByIf(ULONG ulIfIndex);

extern ULONG TCPIP_ClrIpStatics (VOID);

extern ULONG TCPIP_GetDefaultTTL(VOID);

extern ULONG TCPIP_GetIpStatByIf(ULONG ulIfIndex, IPIFSTAT_S * pstIpStat);

extern ULONG TCPIP_GetIpStatics (IPSTAT_S* pstIpStat);

extern ULONG TCPIP_GetPP4DebugFlag(ULONG *pulDebugFlag, ULONG *pulDebugIpAcl, ULONG *pulDebugIpIfAcl,
    ULONG *pulDebugIpIfOpt, ULONG *pulDebugIpErr, ULONG *pulDebugPacketVerbose);

extern ULONG TCPIP_IpOutput (MBUF_S* pstMBuf);

extern ULONG TCPIP_IP_IF_Output(MBUF_S *pstMbuf);

extern ULONG TCPIP_IP_PP4_Intermediate_Hook_Register(ULONG ulType, ULONG ulPriority, 
    IP_PP4_INTERMEDIATE_HOOK_FUNC pfIpFwHookFunc);

extern ULONG TCPIP_IP_PP4_Intermediate_Hook_UnRegister(ULONG ulType, 
    IP_PP4_INTERMEDIATE_HOOK_FUNC pfIpFwHookFunc);

extern ULONG TCPIP_SetDefaultTTL(ULONG ulTtl);

extern ULONG TCPIP_SetIcmpHostUnreach (ULONG ulIfIndex, ULONG ulFlag);

extern ULONG TCPIP_SetIcmpRedirects(ULONG ulIfIndex, ULONG ulFlag);

extern ULONG TCPIP_SetPP4DebugFlag(ULONG ulIpDebugNo, ULONG ulDebugAcl, ULONG ulDebugIfAcl, 
    ULONG ulDebugIfOpt, ULONG ulDebugIpErr, ULONG ulDebugIpVerbose);

extern VOID TCPIP_ShowPP4Statistic(VOID);

extern VOID TCPIP_ShowPP4StatisticByInterface(CHAR *pName);

extern ULONG TCPIP_SetForwardFlag(ULONG ulFlag);

extern ULONG TCPIP_GetForwardFlag(ULONG *pulFlag);

extern ULONG TCPIP_GetIpId(USHORT *pusIpId);

extern VOID TCPIP_IncreaseIpId(VOID);
extern ULONG TCPIP_ShowPP4DebugFlag( VOID );
/*******************************************************************************
*    Func Name: TCPIP_RegFuncIpSendWholePktHook
*  Description: ע�ṳ�Ӻ���, ��IP���ͷ�Ƭ֮ǰ��ȡ������IP����
*        Input: IP4_SEND_WHOLE_PKT_HOOK pfHook: ���Ӻ���ָ��
*       Output: 
*       Return: VOS_OK   �ɹ�
*               VOS_ERR  ���Ӻ���ָ��Ϊ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-10-24  wujie(61195)     Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncIpSendWholePktHook(IP4_SEND_WHOLE_PKT_HOOK pfHook);

/*******************************************************************************
*    Func Name: TCPIP_SetIpOptAttackGuardSwitch
* Date Created: 2009-09-15
*       Author: wuhailan103194
*  Description: �������IPѡ������п��ơ�����IPѡ����Ŀ���
*               ���ش򿪺󽫲���֧�ִ�IPѡ��ı��Ĵ���
*        Input: ULONG ulSwitch:����,0 �ر�, 1 ��, Ĭ�Ϲر�
*       Output: 
*       Return: VOS_OK:�ɹ� ��������ʧ��
*      Caution: ���ӿ���TCPIP_SetIpOptPermitSwitch�ӿڲ�����ͬʱʹ�ã��������
*               ȫ��ѡ����ñ��ӿڣ����õ���ѡ�����TCPIP_SetIpOptPermitSwitch
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-09-15   wuhailan103194          Create
*
*******************************************************************************/
extern ULONG TCPIP_SetIpOptAttackGuardSwitch(ULONG ulSwitch);

/*******************************************************************************
*    Func Name: TCPIP_GetIpOptAttackGuardSwitch
* Date Created: 2009-09-22
*       Author: wuhailan103194
*  Description: ��ȡ���IPѡ������п��ơ�����IPѡ����Ŀ���
*        Input: 
*       Output: ULONG *pulSwitch:���صĿ���ֵ
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-09-22   wuhailan103194          Create
*
*******************************************************************************/
extern ULONG TCPIP_GetIpOptAttackGuardSwitch(ULONG *pulSwitch);

/*******************************************************************************
*    Func Name: TCPIP_SetIpOptPermitSwitch
* Date Created: 2011-03-28
*       Author: mafeng59090
*  Description: ����ָ��ѡ���Ƿ�������,ȱʡ��������ѡ��
*        Input: ULONG ulOption:ѡ��ֵ��ĿǰVISP֧�����õ�ѡ������:
* IPOPT_RR            7        ��¼���ľ���·�� 
* IPOPT_TS            68       ʱ��� 
* IPOPT_SECURITY      130      �ṩs,c,h,tcc 
* IPOPT_LSRR          131      ����Դվѡ· 
* IPOPT_SATID         136      satnet id 
* IPOPT_SSRR          137      �ϸ�Դվѡ· 
* IPOPT_ROUTE_ALERT   148      ����·�߸澯 
* IPOPT_UNKOWN        0x80000000 ��ʶ��ѡ���
*               ULONG ulSwitch:1 ֧���������ѡ��,0 ����������ѡ��ı���
*       Output: 
*       Return: �ɹ�/ʧ��
*      Caution: ���ӿ���TCPIP_SetIpOptAttackGuardSwitch�ӿڲ�����ͬʱʹ�ã�
*               ������õ���ѡ��Ŀ��ص��ñ��ӿڣ��������ȫ���Ľӿ������
*               TCPIP_SetIpOptAttackGuardSwitch�ӿ�
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-03-28   mafeng59090             Create
*
*******************************************************************************/
extern ULONG TCPIP_SetIpOptPermitSwitch(ULONG ulOption, ULONG ulSwitch);

/*******************************************************************************
*    Func Name: TCPIP_GetIpOptPermitSwitch
* Date Created: 2011-03-28
*       Author: mafeng59090
*  Description: ��ȡָ��ѡ���VISP��������
*        Input: ULONG ulOption:ѡ��ֵ��ĿǰVISP֧�����õ�ѡ������:
* IPOPT_RR            7        ��¼���ľ���·�� 
* IPOPT_TS            68       ʱ��� 
* IPOPT_SECURITY      130      �ṩs,c,h,tcc 
* IPOPT_LSRR          131      ����Դվѡ· 
* IPOPT_SATID         136      satnet id 
* IPOPT_SSRR          137      �ϸ�Դվѡ· 
* IPOPT_ROUTE_ALERT   148      ����·�߸澯 
* IPOPT_UNKOWN        0x80000000 ��ʶ��ѡ���
*               ULONG *pulSwitch:����ֵ��1 ����0 ������
*       Output: pulSwitch
*       Return: �ɹ�/ʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-03-28   mafeng59090             Create
*
*******************************************************************************/
extern ULONG TCPIP_GetIpOptPermitSwitch(ULONG ulOption, ULONG *pulSwitch);


extern ULONG TCPIP_SetIpDebugFilter(ULONG ulSetYes, ULONG ulIfIndex, CHAR *szSrcIp, CHAR *szDstIp,
    ULONG ulProtocol, ULONG ulSrcPort, ULONG ulDstPort);


extern ULONG TCPIP_GetIpDebugFilter(ULONG *pulDebugFlag, ULONG *pulDebugFilter);


extern VOID TCPIP_ShowIpDebugFilter(VOID);


extern ULONG TCPIP_RegFuncSrcRtSearch(gpfTCPIPSrcRtSearch pfHookFunc);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncSrcRtSearchByVrf
* Date Created: 2013-12-06
*       Author: likaikun213099
*  Description: ע�����ԴIP����·�ɹ���
*        Input: TCPIP_SRC_RT_SEARCH_FUN pfHookFunc:��Ʒע�����ԴIP����·�ɹ��Ӻ���
*       Output: 
*       Return: IP_GO_WITH_SRCROUTE     ��Դ·�ɷ��ͱ���
*               IP_DROP_PACKET          ��������
*               IP_GO_PASS              ��ԭ�з�ʽ���ͱ���
*      Caution: �������ע��,���TCPIP_RegFuncSrcRtSearch����VRF����֧��
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-12-06   likaikun213099          Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncSrcRtSearchByVrf(TCPIP_SRC_RT_SEARCH_FUN pfHookFunc);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncIpSendPktNoFibSearchHook
* Date Created: 2014-03-12
*       Author: qinyun62011
*  Description: ע��IP���͹��Ӻ������˹�����·�ɲ�ѯ֮ǰ����
*        Input: IP4_SEND_WHOLE_PKT_HOOK pfHook:
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-12   qinyun62011             Create for (Distribute socket)�ֲ�ʽsocket�ü�
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncIpSendPktNoFibSearchHook(IP4_SEND_WHOLE_PKT_HOOK pfHook);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __PP4_API_H__ */

