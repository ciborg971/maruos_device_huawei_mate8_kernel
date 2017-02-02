/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              sfib4_api.h
*
*  Project Code: VISPV100R007
*   Module Name:
*  Date Created: 2008-04-08
*        Author: zengshaoyang62531
*   Description:
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-04-08   zengshaoyang62531       Create
*
*******************************************************************************/
#ifndef _SFIB4_API_H_
#define _SFIB4_API_H_

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

#define FIB4_OK                     VOS_OK
#define FIB4_ERR                    VOS_ERR
#define FIB4_ERR_NOT_ENOUGH_MEM    (VOS_ERR + 1)
#define FIB4_ERR_Q_WRITE           (VOS_ERR + 2)
#define FIB4_ERR_EV_WRITE          (VOS_ERR + 3)
#define FIB4_ERR_RTMSG_INVALID     (VOS_ERR + 4)
#define FIB_ERR_NEXTHOP_OUTIF      (VOS_ERR + 5)      /* ���·��ʱ����ָ����һ�����߳��ӿ� */
#define FIB_ERR_NEXTHOP_INVALID    (VOS_ERR + 6)      /* ��Ч����һ����ַ */
#define FIB_ERR_DESTADDR_INVALID   (VOS_ERR + 7)      /* ��Ч��Ŀ�ĵ�ַ */
#define FIB_ERR_OUTIF_WANTED       (VOS_ERR + 8)      /* ��ָ�����ӿ� (��ָ������һ����ַ�Ǳ�����ַʱ) */
#define FIB_ERR_POLICY_CANNTSET    (VOS_ERR + 9)      /* ��ǰ·�ɲ��Բ�֧�ָı� */
#define FIB_ERR_POLICY_INVALID     (VOS_ERR + 10)     /* ָ����·�ɲ��Բ�֧�� */
#define FIB_ERR_NULL_POINTER       (VOS_ERR + 11)     /* ����ָ��Ϊ�� */
#define FIB_ERR_PRIORITY_INVALID   (VOS_ERR + 12)     /* ·�����ȼ��Ƿ� */
#define FIB_ERR_MASKLEN_INVALID    (VOS_ERR + 13)     /* ���볤�ȷǷ� */
#define FIB_ERR_INVALID_WLHANDLE   (VOS_ERR + 14)     /* ��Ч��Waitlist��� */
#define FIB_NOT_FIND_ROUTE         (VOS_ERR + 15)     /* Added by jiangtao for deleting route item but not find */
#define FIB_HA_IS_SMOOTHING        (VOS_ERR + 16)
#define FIB_ERR_NEXTHOP_WANTED     (VOS_ERR + 17)
#define FIB_ERR_NEXTHOP_OWN        (VOS_ERR + 18)
#define FIB_ERR_DESTADDR_INVALID_2 (VOS_ERR + 19)     /* ��Ч��Ŀ�ĵ�ַ */
#define FIB_ERR_DESTADDR_INVALID_3 (VOS_ERR + 20)     /* ��Ч��Ŀ�ĵ�ַ */
#define FIB_ERR_NEXTHOP_INVALID_2  (VOS_ERR + 21)     /* ��Ч����һ����ַ */
#define FIB_ERR_NEXTHOP_INVALID_3  (VOS_ERR + 22)     /* ��Ч����һ����ַ */
#define FIB_ERR_ROUTEITEM_EXCEED   (VOS_ERR + 23)     /* RIB��ռ䳬�� */
#define FIB_ERR_MSGSEND_FAIL       (VOS_ERR + 24)     /* ��Ϣ����ʧ�� */
#define FIB_ERR_RTMSG_NULL         (VOS_ERR + 25)     /* rtmsg is null */
#define FIB_ERR_RT_NULL            (VOS_ERR + 26)     /* router entry is null */
#define FIB_ERR_DELETE_RT          (VOS_ERR + 27)     /* fail to delete router entry */
#define FIB_ERR_CLEAR_ZONE         (VOS_ERR + 28)     /* fail to clear zone */
#define FIB_ERR_MSG_TYPE           (VOS_ERR + 29)     /* the message type is wrong */
#define FIB_ERR_WAITLIST_GET       (VOS_ERR + 30)     /* fail to get waitlist */
#define FIB_ERR_INVALID_INTERFACE  (VOS_ERR + 31)     /*��Ч�ĳ��ӿڣ���inlookback�ӿ� */
#define FIB_ERR_COMP_NULL          (VOS_ERR + 32)     /* fib4���Ϊ�� */
#define FIB_ERR_MALLOC_FAIL        (VOS_ERR + 33)     /* malloc fail*/
#define FIB_ERR_SCAN_FAIL          (VOS_ERR + 34)     /* ����SFIB4ʧ��*/
#define FIB_ERR_INVALID_FLAG       (VOS_ERR + 35)     /* ���ֵ��Ч */
#define FIB_ERR_INVALID_IPCTL      (VOS_ERR + 36)     /* IP���ƿ���Ч */
#define FIB_ERR_INVALID_IFTYPE     (VOS_ERR + 37)     /* ��Ч�Ľӿ����� */
#define FIB_ERR_INVALID_INSTANCE   (VOS_ERR + 38)     /* ��Ч��ʵ����*/
#define FIB_ERR_INVALID_RTNUM      (VOS_ERR + 39)     /* ��Ч��·������*/
#define FIB_ERR_IS_L2PORT          (VOS_ERR + 40)     /* �����Ŀ��ӿ��Ƕ���˿� */
/* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
#define FIB_ERR_GET_VRFINDEX       (VOS_ERR + 41)     /* ��ȡVRFʵ����ʧ��*/
#define FIB_ERR_IF_NOT_IN_VRF      (VOS_ERR + 42)     /* ���ӿڲ���ָ����VRF��*/
#define FIB_ERR_VRF_NOT_INIT       (VOS_ERR + 43)     /* VRFδ��ʼ��*/
/* End: VISP1.7C03 VRF qinyun , 2009-01-20 */

#define FIB_ERR_OPERA              (VOS_ERR + 44)
#define FIB_ERR_ROUTE_TYPE         (VOS_ERR + 45)

#define FIB_ERR_RM_TYPE            (VOS_ERR + 46)     /*�û�Ԥ����·��ģʽ��ΪSRM�������˲���VISP RIB�Ľӿ�*/
                                                      /*ֱ�ӷ��ش���(��Ϊ��ǰ��ΪSRMʱ����û�г�ʼ��RIB��Դ��)*/

#define RIB4_ERR_VRFID_OUT_BOUND   (VOS_ERR + 47)     /* ��ȡ��VRFʵ���ų���RIB������·��ά��*/
#define RIB4_ERR_NO_USE_ENTRY      (VOS_ERR + 48)     /* û�п��õ���һ��·�ɽڵ�*/
/* ������������ӵ�FIB_ERROR_CODE_E�� */

#define  TCPIP_RIB4_MAX_VRFNAME_LENGTH   31      /*��TCPIP_MAX_VRFNAME_LENGTH����һ��*/

typedef struct tagTCPIP_RIB_RT4_ENTRY
{
    ULONG  ulRtDestAddr;         /* Ŀ�ĵ�ַ�������� */
    ULONG  ulRtDestPrefLen;      /* ���볤�� */
    ULONG  ulRtNextHopAddr;      /* ��һ���������� */
    ULONG  ulRtIfIndex;          /* ���ӿ����� */
    ULONG  ulRtFlags;            /* ·�ɱ�� */
    ULONG  ulRtPri;              /* ·�����ȼ� */
    ULONG  ulRtProto;            /* ·��Э������ */
    ULONG  ulRtUse;              /* �Ƿ���Ч */
    ULONG  ulPmtu;               /* Path mtu for the route. a00900892, 30-01-2014 */
    CHAR   szVrfName[TCPIP_RIB4_MAX_VRFNAME_LENGTH + 1];        /* VRF���� */
} TCPIP_RIB_RT4_ENTRY_S;


/* ZENGSHAOYANG:·��ģ��Ĵ����붼�ú궨������ʾ���ұȽϷ�ɢ�������������Ӽ�ά��
����һ��ö�٣��������101��ʼ��� */
typedef enum tagFIB_ERROR_CODE
{
    FIB4_GET_END = VOS_ERR + 100  ,    /* ���ĩβ�� */
    FIB4_GET_FAIL                 ,    /* ��ȡ����ʧ�� */
    FIB4_GET_FAIL_BY_VRF          ,    /* ͨ��VRF��ȡ����ʧ�� */
    FIB4_GET_FAIL_CLOSE           ,    /* �ر�waitlistʧ�� */
    FIB4_GET_FAIL_OPEN            ,    /* ��waitlistʧ��*/
    FIB4_GET_RT_FAIL_CLOSE        ,    /* ��ȡ����ʧ�ܣ�ֱ�ӹر�waitlist*/
    FIB4_GET_ERR_CLOSE_VRF        ,    /* ָ��VRF��ѯʱ���ر�waitlistʧ�� */
    FIB4_GET_FAIL_CLOSE_VRF       ,    /* ָ��VRF��ѯʱ��GET����ʧ�ܣ��ҹر�waitlistʧ�� */
    FIB4_GET_VRF_NET_FAIL_CLOSE   ,    /* ָ��VRF+���β�ѯ,�ر�waitlistʧ�� */
    FIB4_GET_FAIL_VRF_NET_CLOSE   ,    /* ָ��VRF+���β�ѯ,��ȡ����ʧ���ҹر�waitlistʧ�� */
    FIB4_GET_FAIL_CLOSE_NETIP     ,    /* ָ�����β�ѯʱ�ر�waitlistʧ�� */
    FIB4_GET_FAIL_OPEN_NETIP      ,    /* ָ�����β�ѯʱ��waitlistʧ�� */
    FIB_ERR_VRF_NAMELONG               /* VRF���ֳ��ȴ���31*/
}FIB_ERROR_CODE_E;

#define FIB4_STATIC_ADDR_ADD       1
#define FIB4_STATIC_ADDR_DEL       0



#define FIB4_RTMSG_ADD             1    /* ���·�� */
#define FIB4_RTMSG_DEL             2    /* ɾ��·�� */
#define FIB4_RTMSG_CLEAR           3    /* ���·�� */
#define FIB4_RTMSG_REFRESH         4    /* ˢ��·�� */
/* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
#define FIB4_RTMSG_CLEARSPEC       5    /* ���ָ��·�� */
/* End: VISP1.7C03 VRF qinyun , 2009-01-20 */


#define FIB_RTNUM_LOW_LEVEL       1000
#define FIB_RTNUM_HIGH_LEVEL      100000

/* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
#define FIB_IPV4RM_INSTANCE       1
#define FIB_IPV6RM_INSTANCE       2

#define FIB_RM_TYPE_IPV4          1
#define FIB_RM_TYPE_IPV6          2
/* End: VISP1.7C03 VRF qinyun , 2009-01-20 */

#define FIB_RTWARN_INIT           0
#define FIB_RTWARN_OUTPUT         1
#define FIB_RTWARN_CANCEL         2
/*END of Add*/

typedef enum tagRouteStrategy
{
    RS_ONE_BY_ONE = 0,    /* 0 ���ɷֵ�����ѭ��ʽ */
    RS_NEWEST_FIRST,      /* 1 ����·����Ч */
    RS_OLDEST_FIRST,      /* 2 ����·����Ч */
    RS_PRI_BASED,         /* 3 �ӿ����ȼ������Ч */
    RS_BFCR,              /* 4 ��Ԫ�鱨�������� */
    RS_RTPRI,             /* 5 ·�����ȼ� */
    RS_BFCR_DSCP,         /* 6 ��Ԫ���DSCP ���������� */
    /* End of Added by likaikun00213099, 2014/6/6 */
    RS_END
}ROUTE_STRATEGY_E;

typedef enum tagFibNpMode
{
    FIB_NP_DOWNALL = 0, /*�·�ȫ��·����NP*/
    FIB_NP_DOWNBEST,    /*�·�����·����NP*/
    FIB_NP_END
}FIBNPMODE_E;

typedef enum tagUpdateFibNpMode
{
    UPDATE_FIB_ADDTHENDEL,   /*���·����ӣ����·�ɾ��*/
    UPDATE_FIB_DELTHENADD    /*���·�ɾ�������·�����*/
}UPDATEFIBNPMODE_E;

#ifndef MAX_IF_NAME_LENGTH
#define MAX_IF_NAME_LENGTH  47   /* �ӿ������� */
#endif

/* One of the data stores maintained by FIB6Agent subsystem. Acts as an unit of external data
interface to be used by FIB6Agent to receive FIB entries from RM. This is defined by RM */
typedef struct tagRTMSG4
{
    USHORT  usType;             /* RTMSG_DEL, RTMSG_ADD, RTMSG_DELETE_ZONE */
    USHORT  usZoneID;           /* zone ID */
    ULONG   ulDestination;
    ULONG   ulNexthop;
    ULONG   ulLocalAddress;
    ULONG   ulIfIndex;          /* index of outgoing interface */
    ULONG   ulATIndex;          /* virtual link index */
    ULONG   ulSlot;
    ULONG   ulFlags;            /* RTF_GATEWAY, RTF_HOST, ...*/
    UCHAR   ucDestPrefixLength;
    UCHAR   ucLocalPrefixLength;
    USHORT  usRTPri;            /* route priority */
    ULONG   ulProto;
    /*END Add*/

    UCHAR   ucIfName[MAX_IF_NAME_LENGTH + 1];
    /*END of Add*/

    /* BEGIN: a00900892, 30-01-2014, Path mtu for the route */
    ULONG  ulPmtu;
    /* END: a00900892, 30-01-2014, Path mtu for the route */
    ULONG   ulLocalIfIndex;
    /*End of Add*/
} RTMSG4_S;

/*  One of the data stores maintained by FIB4Container subsystem. It contains route entry
    with various fields as specified below. This structure is used to store external information in
    FIB Table. This can be used in radix node or any other data store based on
    implementation specifics. (to support multi algorithm). */
typedef struct tagTCPIP_RT4_ENTRY
{
     ULONG  ulRt_Dest;
     ULONG  ulRt_Dest_PrefLen;
     ULONG  ulRt_Nexthop;
     ULONG  ulRt_Flags;         /* route flags -RTF_GATEWAY, RTF_HOST */
     ULONG  ulRt_IfIndex;       /* index of outgoing interface */
     ULONG  ulRt_ATIndex;       /* index of virtual link between rt_stLclAddr */
     ULONG  ulRt_Slot;          /* slot num of outgoing interface */
     ULONG  ulRt_Use;           /* metrics to consider */
     ULONG  ulRt_State;
     ULONG  ulRt_Proto;
     ULONG  ulRt_TimeStamp;
     ULONG  ulCacheEntryIndex;  /* used to access corr. cache entry */
     ULONG  ulRt_Loc;           /* local address */
     ULONG  ulRt_Loc_PrefLen;   /* local address mask lenth */
     ULONG  ulRTPri;            /* route priority */
     ULONG  ulPmtu;             /* Path mtu for the route, a00900892, 30-01-2014 */
} TCPIP_RT4_ENTRY_S;
/* ---------------------------------------SGSN·��ά������--------------------------------------------- */
#define SFIB4_VRF_MAX_VRFNAME_LENGTH    31

#define FIB4_SEARCH_ALL                0x00    /*��ѯ����VRFȫ��·�� */

#define FIB4_SEARCH_BY_VRF             0x01    /*ָ��VRF��ѯ[��ѯָ��VRF�е�ȫ��·��]*/

#define FIB4_SEARCH_BY_NETIP           0x02    /*ָ�����β�ѯ[��ѯȫ��VRF�е�ָ��·��]*/

#define FIB4_SEARCH_BY_VRF_AND_NETIP   (FIB4_SEARCH_BY_VRF | FIB4_SEARCH_BY_NETIP)    /*ָ��VRF+���β�ѯ[��ѯָ��VRF�е�ָ��·��]*/


typedef struct tagTCPIP_RIB_FILTER_API
{
    ULONG  ulRtDestAddr;         /* Ŀ�ĵ�ַ�������� */
    ULONG  ulRtDestPrefLen;      /* ���볤�� */
    ULONG  ulRtNextHopAddr;      /* ��һ���������� */
    ULONG  ulRtIfIndex;          /* ���ӿ����� */
    CHAR   szVrfName[TCPIP_RIB4_MAX_VRFNAME_LENGTH + 1]; /* VRF���� */
}TCPIP_RIB_FILTER_API_S;

/* ��������:
1.����������Ϊ��ʱ����ѯȫ��VRF�µ�ȫ��·�ɣ�
�������������������Ϊ��
2.ָ��VRF��ѯ[��ѯָ��VRF�е�ȫ��·��],ulFilterType=FIB4_SEARCH_BY_VRF
3.ָ�����β�ѯ[��ѯȫ��VRF�е�ָ��·��],ulFilterType=FIB4_SEARCH_BY_NETIP
4.ָ��VRF+���β�ѯ[��ѯָ��VRF�е�ָ��·��],ulFilterType=FIB4_SEARCH_BY_VRF_AND_NETIP
*/
typedef struct tagFIB4_FILTER_COND_API
{
    CHAR  szVrfName[SFIB4_VRF_MAX_VRFNAME_LENGTH + 1]; /*VPN ����*/
    ULONG ulDstIp;                                     /*Ŀ�ĵ�ַ*/
    ULONG ulDstMask;                                   /*���볤��,���û���д���볤�ȣ�����24*/
    ULONG ulFilterType;                                /*�������������ṹ��ͷ����˵��*/
}FIB4_FILTER_COND_API_S;

typedef struct tagTCPIP_RT4_ENTRY_BY_VRF
{
     ULONG  ulRt_Dest;
     ULONG  ulRt_Dest_PrefLen;
     ULONG  ulRt_Nexthop;
     ULONG  ulRt_Flags;         /* route flags -RTF_GATEWAY, RTF_HOST */
     ULONG  ulRt_IfIndex;       /* index of outgoing interface */
     ULONG  ulRt_ATIndex;       /* index of virtual link between rt_stLclAddr */
     ULONG  ulRt_Slot;          /* slot num of outgoing interface */
     ULONG  ulRt_Use;           /* metrics to consider */
     ULONG  ulRt_State;
     ULONG  ulRt_Proto;
     ULONG  ulRt_TimeStamp;
     ULONG  ulCacheEntryIndex;  /* used to access corr. cache entry */
     ULONG  ulRt_Loc;           /* local address */
     ULONG  ulRt_Loc_PrefLen;   /* local address mask lenth */
     ULONG  ulRTPri;            /* route priority */
     ULONG  ulVrfIndex;         /* VRF Index*/
     ULONG  ulPmtu;             /* Path mtu for the route. a00900892, 30-01-2014 */
} TCPIP_RT4_ENTRY_BY_VRF_S;

/*  One of the data stores maintained by FIB6Agent for providing search interface
    to external modules */
typedef struct tagTCPIP_ROUTE4
{
     USHORT        usZoneID;       /* zone ID */
     UCHAR         ucTos;          /* 8bit IP�ײ�TOS�ֶΣ������DSCPֵ����Ҫת��ΪTOS��ʽ��ֻ����ƽ��·�ɲ���ΪRS_BFCR_DSCP�������壬����ƽ��·�ɲ�����TOSֵ��������*/
     UCHAR         ucPadding_1[1];
     /*End of Modified by likaikun00213099, 2014/6/6 */
     ULONG         ulDestination;
     ULONG         ulNexthop;
     ULONG         ulLocalAddress;
     ULONG         ulIfIndex;  /* index of outgoing interface */
     ULONG         ulATIndex;  /* virtual link index */
     ULONG         ulSlot;
     ULONG         ulFlags;    /* RTF_GATEWAY, RTF_HOST, ...*/
     UCHAR         ucDestPrefixLength;
     UCHAR         ucLocalPrefixLength;
     USHORT        usRTPri;    /* route priority */
     ULONG         ulSrcIPAddr;
     ULONG         ulDstIPAddr;
     ULONG         ulProtocol;
     USHORT        usSrcPort;
     USHORT        usDstPort;

     /* ���ù���OSPƽ̨�������������ֶ� */
     ULONG         ulVrfIndex;    /*Vrf index*/
     ULONG         ulL3VPNXcIndex;/*��ѯ��ƷFIB,�����������ģ��Ѹò���������Ʒ����Ʒ���ݸ���Ϣ��ȡ��Tunnel ID*/
} TCPIP_ROUTE4_S;

/* w60006501��ӣ���Ԫ��·�ɲ�ѯʹ�õĽṹ�壬��¼���ĵ���Ԫ����Ϣ */
/* �����ݽṹ��Ϊ��PTN��Ʒ����FIBʹ��, ������Ʒ����Ӧ�ø����ݽṹ */
typedef struct tagPacketInfo
{
    ULONG  ulSrcIPAddr;     /* FIB��ѯ���ʱ ������ */
    ULONG  ulDstIPAddr;     /* FIB��ѯ���ʱ ������ */
    ULONG  ulProtocol;      /* FIB��ѯ���ʱ ������ */
    USHORT usSrcPort;       /* FIB��ѯ���ʱ ������ */
    USHORT usDstPort;       /* FIB��ѯ���ʱ ������ */
    UCHAR  ucTos;          /* 8bit IP�ײ�TOS�ֶΣ������DSCPֵ����Ҫת��ΪTOS��ʽ��ֻ����ƽ��·�ɲ���ΪRS_BFCR_DSCP�������壬����ƽ��·�ɲ�����TOSֵ��������*/
    UCHAR  ucPadding_1[3];
    /*End of Add by likaikun00213099, 2014/6/6 */
}PACKETINFO_S;

/*  One of the data stores maintained by FIB6Agent for providing search interface
    to external modules */
/* �����ݽṹ��Ϊ��PTN��Ʒ����FIBʹ��, ������Ʒ����Ӧ�ø����ݽṹ */
typedef struct tagROUTE4
{
     USHORT        usZoneID;       /* zone ID */
     UCHAR         ucPadding_1[2];
     ULONG         ulDestination;
     ULONG         ulNexthop;
     ULONG         ulLocalAddress;
     ULONG         ulIfIndex;  /* index of outgoing interface */
     ULONG         ulATIndex;  /* virtual link index */
     ULONG         ulSlot;
     ULONG         ulFlags;    /* RTF_GATEWAY, RTF_HOST, ...*/
     UCHAR         ucDestPrefixLength;
     UCHAR         ucLocalPrefixLength;
     USHORT        usRTPri;    /* route priority */

     ULONG          ulVrfIndex;   /* Vrf index,�ڸð汾,����usZoneID�ֶ�һ��,����R6C05�汾��Ʒ���õ����ֶ� */
     ULONG         ulL3VPNXcIndex;/* ��ѯ��ƷFIB,�����������ģ��Ѹò���������Ʒ����Ʒ���ݸ���Ϣ��ȡ��Tunnel ID */
     /* End: VISP Support multi-instance project */

     /* Begin: a00900892, 30-01-2014, Path mtu for the route */
     ULONG ulPmtu;
     /* End: a00900892, 30-01-2014, Path mtu for the route */

     PACKETINFO_S *pstPacketInfo;
} ROUTE4_S;

/* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
typedef struct tagTCPIP_RM_CFGSTATIC_S
{
    ULONG Oper;              /*1����  0:ɾ��*/
    ULONG ulIpAddress;
    ULONG ulMaskLen;
    ULONG ulGateway;
    UCHAR szIfName[MAX_IF_NAME_LENGTH + 1];
    ULONG ulRTPri;
    UCHAR szVrfName[SFIB4_VRF_MAX_VRFNAME_LENGTH + 1];
    ULONG ulPmtu;           /* Path MTU support for static route. a00900892, 30-01-2014*/
}TCPIP_RM_CFGSTATIC_S;
typedef struct tagFIB4_IFNEXTHOP_S
{
    ULONG ulIfIndex;
    ULONG ulNextHop;
    CHAR szVrfName[SFIB4_VRF_MAX_VRFNAME_LENGTH + 1]; /*vrf��*/
}FIB4_IFNEXTHOP_S;

typedef struct tagFIB4_EXACT_ROUTE_S
{
    ULONG ulDstIpAddr;
    ULONG ulMaskLen;
    ULONG ulIfIndex;
    ULONG ulNextHop;
    CHAR szVrfName[SFIB4_VRF_MAX_VRFNAME_LENGTH + 1]; /*vrf��*/
}FIB4_EXACT_ROUTE_S;

/*��������*/
typedef struct tagFIB4_FILTER_S
{
  CHAR szVrfName[SFIB4_VRF_MAX_VRFNAME_LENGTH + 1]; /*VPN ����*/
} FIB4_FILTER_S;

/*typedef VOID (*NotifyVlinkProcess_HOOK)(ULONG ulIfIndex,ULONG ulPeerAddr,ULONG ulCmd);*/
typedef VOID (*NotifyVlinkProcess_HOOK)(ULONG ulVrfIndex,ULONG ulIfIndex,ULONG ulPeerAddr,ULONG ulCmd);
/* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
typedef ULONG (*GetPriByIfindex_HOOK)(ULONG ulIfindex, ULONG* pulPri);

/* �����ݽṹֻ��PTN���ⳡ��ʹ�� */
typedef ULONG (*TCPIP_SEARCH_VPN_FIB_FUN)(ROUTE4_S* pstRoute);


/*******************************************************************************
*    Func Name: TCPIP_CloseFibTable
*  Description: unregister waillist object for doubly linked list of route
*        Input: ULONG ulWaitlist:waitlist handle
*       Output:
*       Return: �ɹ�����VOS_OK,ʧ�ܷ��ش�����(��sfib4_api.h)
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   zengshaoyang62531       Create
*
*******************************************************************************/
extern ULONG TCPIP_CloseFibTable(UINTPTR ulWaitlist);
/*******************************************************************************
*    Func Name: TCPIP_DisableRtByIfNextHop
*  Description: ͨ�����ӿ�������next-hopȥʹ��·��
*        Input: ULONG ulIfIndex:���ӿ�����
*               ULONG ulNextHop:next-hop��ַ
*       Output:
*       Return: �ɹ�����VOS_OK,ʧ�ܷ��ش�����(��sfib4_api.h)
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-04-08   zengshaoyang62531       Create
*
*******************************************************************************/
extern ULONG TCPIP_DisableRtByIfNextHop (ULONG ulIfIndex, ULONG ulNextHop);
/*******************************************************************************
*    Func Name: TCPIP_EnableRtByIfNextHop
*  Description: ͨ�����ӿ�������next-hopʹ��·��
*        Input: ULONG ulIfIndex:���ӿ�����
*               ULONG ulNextHop:next-hop��ַ
*       Output:
*       Return: �ɹ�����VOS_OK,ʧ�ܷ��ش�����(��sfib4_api.h)
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-04-08   zengshaoyang62531       Create
*
*******************************************************************************/
extern ULONG TCPIP_EnableRtByIfNextHop (ULONG ulIfIndex, ULONG ulNextHop);
/*******************************************************************************
*    Func Name: TCPIP_ExactDisableRt
*  Description: ��ȷ��ȥʹ��·��
*        Input: ULONG ulDstIpAddr:Ŀ�ĵ�ַ
*               ULONG ulMaskLen:���볤��
*               ULONG ulNextHop:next-hop��ַ
*               ULONG ulIfIndex:���ӿ�����
*       Output:
*       Return: VOS_OK:�ɹ���ʧ�ܷ��ش�����(��sfib4_api.h)
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   zengshaoyang62531       Create
*
*******************************************************************************/
extern ULONG TCPIP_ExactDisableRt (ULONG ulDstIpAddr, ULONG ulMaskLen, ULONG ulNextHop, ULONG ulIfIndex);
/*******************************************************************************
*    Func Name: TCPIP_ExactEnableRt
*  Description: ��ȷ��ʹ��·��
*        Input: ULONG ulDstIpAddr:Ŀ�ĵ�ַ
*               ULONG ulMaskLen:���볤��
*               ULONG ulNextHop:next-hop��ַ
*               ULONG ulIfIndex:���ӿ�����
*       Output:
*       Return: VOS_OK:�ɹ���ʧ�ܷ��ش�����(��sfib4_api.h)
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   zengshaoyang62531       Create
*
*******************************************************************************/
extern ULONG TCPIP_ExactEnableRt (ULONG ulDstIpAddr, ULONG ulMaskLen, ULONG ulNextHop, ULONG ulIfIndex);
/*******************************************************************************
*    Func Name: TCPIP_GetFibEntry
*  Description: Fetches bulk of FIB entries, protected using waitlist
*        Input: ULONG ulWaitlist:waitlist handle
*               ULONG ulRtNumWanted:number of wanted entrys
*               TCPIP_RT4_ENTRY_S *pstRtEntry:point to route entry table
*               ULONG *pulRtNumReturn:number of get entrys
*       Output:
*       Return: �ɹ�����FIB4_OK,ʧ�ܷ��ش�����(��sfib4_api.h)
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   zengshaoyang62531       Create
*
*******************************************************************************/
extern ULONG TCPIP_GetFibEntry(UINTPTR ulWaitlist,ULONG ulRtNumWanted,
    TCPIP_RT4_ENTRY_S *pstRtEntry,ULONG *pulRtNumReturn);

/*******************************************************************************
*    Func Name: TCPIP_GetOutIfindexByDstIP
*  Description: ����Ŀ�ĵ�ַ���ҳ��ӿ�����
*        Input: ULONG ulDIP:  32λ�����ֽ���ĵ�ֵַ
*               ULONG *pulOutIfIndex:���ӿ�ָ��
*       Output:
*       Return: �ɹ�����FIB4_OK,ʧ�ܷ��ش�����(��sfib4_api.h)
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   zengshaoyang62531       Create
*
*******************************************************************************/
extern ULONG TCPIP_GetOutIfindexByDstIP(ULONG ulDIP, ULONG *pulOutIfIndex);
/*******************************************************************************
*    Func Name: TCPIP_GetRouteCount
*  Description: ��ȡ·����Ŀ
*        Input:
*       Output: ULONG *pulNum:��ȡ��·����Ŀ
*       Return: FIB4_ERR
*               FIB4_OK
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   zengshaoyang62531       Create
*
*******************************************************************************/
extern ULONG TCPIP_GetRouteCount (ULONG *pulNum);
/*******************************************************************************
*    Func Name: TCPIP_GetSFIBDebug
*  Description: Get fib debug switch
*        Input:
*       Output: ULONG *pulDbg: sfib debug switch value
*       Return: FIB4_OK
*               FIB4_ERR
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-04-08   zengshaoyang62531       Create
*
*******************************************************************************/
extern ULONG TCPIP_GetSFIBDebug(ULONG *pulDbg);
/*******************************************************************************
*    Func Name: TCPIP_GetSfibHADbg
*  Description: HA���Կ��ػ�ȡ����
*        Input:
*       Output: ULONG *pulDbg:��ȡ�ĵ��Կ���ֵ
*       Return: VOS_OK:�ɹ�
*               VOS_ERR:ʧ��
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   zengshaoyang62531       Create
*
*******************************************************************************/
extern ULONG TCPIP_GetSfibHADbg(ULONG *pulDbg);
/*******************************************************************************
*    Func Name: TCPIP_LookupFIB
*  Description: Searches for the given destination address in the FIB table
*               and fills with the route information if found
*        Input: TCPIP_ROUTE4_S *pstRoute4:Pointer to route entry memory, containing
*                   the destination address, and zoneid
*       Output:  if success,contain search result
*       Return: �ɹ�����FIB4_OK,ʧ�ܷ��ش�����(��sfib4_api.h)
*      Caution: ��ע������ֽ���
*               ULONG ulDestination:    Ŀ�ĵ�ַ    ������
*               ULONG ulNexthop:        ��һ����ַ  ������
*               ULONG ulSrcIPAddr:      ԴIP        ������
*               ULONG ulDstIPAddr:      Ŀ��IP      ������
*               ULONG ulProtocol:       Э���      ������
*               ULONG usSrcPort:        Դ�˿�      ������
*               ULONG usDstPort:        Ŀ�Ķ˿�    ������
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   zengshaoyang62531       Create
*
*******************************************************************************/
extern ULONG TCPIP_LookupFIB(TCPIP_ROUTE4_S *pstRoute4);
/*******************************************************************************
*    Func Name: TCPIP_OpenFibTable
*  Description: register waillist object for doubly linked list of route
*        Input:
*       Output: ULONG *pulWaitlist:waitlist handle
*       Return: �ɹ�����VOS_OK,ʧ�ܷ��ش�����(��sfib4_api.h)
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   zengshaoyang62531       Create
*
*******************************************************************************/
extern ULONG TCPIP_OpenFibTable(UINTPTR *pulWaitlist);
/*******************************************************************************
*    Func Name: TCPIP_PPI_DownloadStaticRtByNextHop
*  Description: ������̬·�ɻ�DHCP·�ɣ��ѷ���Ҫ����·���NP
*        Input: ULONG ulIfIndex:���ӿ�����
*               ULONG ulNextHop:·����һ����ַ��������
*               ULONG ulVlinkIndex:Ҫˢ��·�ɵ�vlink����
*       Output:
*       Return: VOS_OK:�ɹ���ʧ�ܷ��ش�����(��sfib4_api.h)
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   zengshaoyang62531       Create
*
*******************************************************************************/
extern ULONG TCPIP_PPI_DownloadStaticRtByNextHop(ULONG ulIfIndex, ULONG ulNextHop, ULONG ulVlinkIndex);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncGetPriByIfindexHook
*  Description: ע��ͨ���ӿڻ�ȡ�ӿ����ȼ��Ĺ��Ӻ���
*        Input: GetPriByIfindex_HOOK_FUNC pfHookFunc:��ע���ͨ���ӿڻ�ȡ�ӿ����ȼ��Ĺ��Ӻ���
*       Output:
*       Return: FIB4_OK:�ɹ�
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   zengshaoyang62531       Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncGetPriByIfindexHook(GetPriByIfindex_HOOK pfHookFunc);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncNotifyVlinkProcessHook
*  Description: ע��֪ͨvlink����Ĺ��Ӻ���
*        Input: NotifyVlinkProcess_HOOK_FUNC pfHookFunc:��ע���֪ͨvlink����Ĺ��Ӻ���
*       Output:
*       Return: FIB4_OK:�ɹ�
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   zengshaoyang62531       Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncNotifyVlinkProcessHook(NotifyVlinkProcess_HOOK pfHookFunc);
/*******************************************************************************
*    Func Name: TCPIP_RequestFIB
*  Description: This method is used by FIBAgent for adding/deleteing routes
*        Input: RTMSG4_S* pstMsg:·�������ݽṹ���ṩ���û�ʹ��
*       Output:
*       Return: VOS_OK:�ɹ���������������(��sfib4_api.h)
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   zengshaoyang62531       Create
*
*******************************************************************************/
extern ULONG TCPIP_RequestFIB (RTMSG4_S* pstMsg);
/*******************************************************************************
*    Func Name: TCPIP_RouteAdd
*  Description: ��Ӿ�̬·��
*        Input: ULONG ulIpAddress:Ŀ�ĵ�ַ(������)
*               ULONG ulMaskLen:��ַ����
*               ULONG ulGateway:���ص�ַ(������,0��ʾδָ��)
*               ULONG ulIfIndex:���ӿ�����
*               ULONG ulRTPri:·�����ȼ�
*       Output:
*       Return: VOS_OK���ɹ�,ʧ�ܷ��ش�����(��sfib4_api.h)
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-04-08   zengshaoyang62531       Create
*
*******************************************************************************/
extern ULONG TCPIP_RouteAdd(ULONG ulIpAddress, ULONG ulMaskLen, ULONG ulGateway,ULONG ulIfIndex,ULONG ulRTPri);
/*******************************************************************************
*    Func Name: TCPIP_RouteDel
*  Description: ɾ����̬·��
*        Input: ULONG ulIpAddress:Ŀ�ĵ�ַ
*               ULONG ulMaskLen:���볤��
*               ULONG ulGateway:next-hop��ַ
*               ULONG ulIfIndex:���ӿ�����
*       Output:
*       Return: VOS_OK:�ɹ���ʧ�ܷ��ش�����(��sfib4_api.h)
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-04-08   zengshaoyang62531       Create
*
*******************************************************************************/
extern ULONG TCPIP_RouteDel(ULONG ulIpAddress, ULONG ulMaskLen,ULONG ulGateway, ULONG ulIfIndex);
/*******************************************************************************
*    Func Name: TCPIP_SetRoutePolicy
*  Description: ��Ԥ����ѡ·����Ϊ������Ԫ�����ڽӿ����ȼ�������£���Э��ջ��
*               ��֮��ָ��ѡ·������������֮���л�������ʵʱ��Ч��
*               �������Ϊ�·�����·�����ܶ�̬�л�
*        Input: ULONG ulPolicy:ʹ��ѡ·���Ե������֣�0Ϊʹ�ܰ����ӿ����ȼ�ѡ·��
*               1Ϊʹ����Ԫ��·�ɸ��ɷֵ�ѡ·��
*       Output:
*       Return: �ɹ�����VOS_OK,ʧ�ܷ��ش�����(��sfib4_api.h)
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   zengshaoyang62531       Create
*
*******************************************************************************/
extern ULONG TCPIP_SetRoutePolicy(ULONG ulPolicy);
/*******************************************************************************
*    Func Name: TCPIP_SetSFIBDebug
*  Description: set sfib debug switch.
*        Input: ULONG ulDbg:0 --- off,1 --- on
*       Output:
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-04-08   zengshaoyang62531       Create
*
*******************************************************************************/
extern VOID TCPIP_SetSFIBDebug(ULONG ulDbg);
/*******************************************************************************
*    Func Name: TCPIP_SetSfibHADbg
*  Description: HA���Կ������ú���
*        Input: ULONG ulDbg:���õĵ��Կ���ֵ
*       Output:
*       Return: VOS_OK:�ɹ�
*               VOS_ERR:ʧ��
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   zengshaoyang62531       Create
*
*******************************************************************************/
extern ULONG TCPIP_SetSfibHADbg(ULONG ulDbg);


extern ULONG TCPIP_SetWarningRouteNum(ULONG ulInstance, ULONG ulRouteNum);


extern ULONG TCPIP_GetWarningRouteNum(ULONG ulInstance, ULONG *pulRouteNum);
/*END of Add*/

extern VOID TCPIP_ShowWarningRouteNum(ULONG ulInstance);
/*******************************************************************************
*    Func Name: TCPIP_DisableRtByIfNextHopByVrf
* Date Created: 2009-02-02
*       Author: qinyun
*  Description: ͨ�����ӿ�������next-hopȥʹ��·��
*        Input: ULONG ulIfIndex:���ӿ�����
*               ULONG ulNextHop:next-hop��ַ
*       Output:
*       Return: �ɹ�����VOS_OK,ʧ�ܷ��ش�����(��sfib4_api.h)
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-02   qinyun                  Create
*
*******************************************************************************/
extern ULONG TCPIP_DisableRtByIfNextHopByVrf (FIB4_IFNEXTHOP_S *pstInfo);
/*******************************************************************************
*    Func Name: TCPIP_ExactDisableRtByVrf
* Date Created: 2009-02-02
*       Author: qinyun
*  Description: ��ȷ��ȥʹ��·��
*        Input: ULONG ulDstIpAddr:Ŀ�ĵ�ַ
*               ULONG ulMaskLen:���볤��
*               ULONG ulNextHop:next-hop��ַ
*               ULONG ulIfIndex:���ӿ�����
*       Output:
*       Return: VOS_OK:�ɹ���ʧ�ܷ��ش�����(��sfib4_api.h)
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-02   qinyun                  Create
*
*******************************************************************************/
extern ULONG TCPIP_ExactDisableRtByVrf  (FIB4_EXACT_ROUTE_S *pstInfo);
/*******************************************************************************
*    Func Name: TCPIP_ExactEnableRtByVrf
* Date Created: 2009-02-02
*       Author: qinyun
*  Description: ��ȷ��ʹ��·��
*        Input: ULONG ulDstIpAddr:Ŀ�ĵ�ַ
*               ULONG ulMaskLen:���볤��
*               ULONG ulNextHop:next-hop��ַ
*               ULONG ulIfIndex:���ӿ�����
*       Output:
*       Return: VOS_OK:�ɹ���ʧ�ܷ��ش�����(��sfib4_api.h)
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-02   qinyun                  Create
*
*******************************************************************************/
extern ULONG TCPIP_ExactEnableRtByVrf (FIB4_EXACT_ROUTE_S *pstInfo);
/*******************************************************************************
*    Func Name: TCPIP_OpenFibTableByVrf
* Date Created: 2009-02-02
*       Author: qinyun
*  Description: register waillist object for doubly linked list of route
*        Input:
*       Output: ULONG *pulWaitlist:waitlist handle
*       Return: �ɹ�����VOS_OK,ʧ�ܷ��ش�����(��sfib4_api.h)
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-02   qinyun                  Create
*
*******************************************************************************/
ULONG TCPIP_OpenFibTableByVrf(UINTPTR *pulWaitlist, FIB4_FILTER_S *pstFileter) ;
/*******************************************************************************
*    Func Name: TCPIP_GetRouteCount
* Date Created: 2009-02-02
*       Author: qinyun
*  Description: ��ȡ·����Ŀ
*        Input:
*       Output: ULONG *pulNum:��ȡ��·����Ŀ
*       Return: FIB4_ERR
*               FIB4_OK
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-02   qinyun                  Create
*
*******************************************************************************/
ULONG TCPIP_GetRouteCountByVrf (ULONG *pulNum,CHAR *pszVrfName);

/*******************************************************************************
*    Func Name: TCPIP_EnableRtByIfNextHopByVrf
* Date Created: 2009-02-02
*       Author: qinyun
*  Description: ͨ�����ӿ�������next-hopʹ��·��
*        Input: ULONG ulIfIndex:���ӿ�����
*               ULONG ulNextHop:next-hop��ַ
*       Output:
*       Return: �ɹ�����VOS_OK,ʧ�ܷ��ش�����(��sfib4_api.h)
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-02   qinyun                  Create
*
*******************************************************************************/
extern ULONG TCPIP_EnableRtByIfNextHopByVrf (FIB4_IFNEXTHOP_S *pstInfo);

/* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
/*******************************************************************************
*    Func Name: TCPIP_SetRouteByVrf
*  Description: ��Ӿ�̬·��
*        Input: TCPIP_RM_CFGSTATIC_S *pstRmIn:·����Ϣ�ṹ��
*       Output:
*       Return: VOS_OK���ɹ�,ʧ�ܷ��ش�����(��sfib4_api.h)
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-02   qinyun                  Create
*
*******************************************************************************/
extern ULONG TCPIP_SetRouteByVrf(TCPIP_RM_CFGSTATIC_S *pstRmIn);
/*******************************************************************************
*    Func Name: TCPIP_GetFibEntryByVrf
*  Description: Fetches bulk of FIB entries, protected using waitlist
*        Input: ULONG ulWaitlist:waitlist handle
*               CHAR *pszVrfName:VRF Name
*               ULONG ulRtNumWanted:number of wanted entrys
*               TCPIP_RT4_ENTRY_S *pstRtEntry:point to route entry table
*               ULONG *pulRtNumReturn:number of get entrys
*       Output:
*       Return: �ɹ�����FIB4_OK,ʧ�ܷ��ش�����(��sfib4_api.h)
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-02   qinyun                  Create
*
*******************************************************************************/
extern ULONG TCPIP_GetFibEntryByVrf(UINTPTR ulWaitlist,CHAR *pszVrfName,
                ULONG ulRtNumWanted, TCPIP_RT4_ENTRY_S *pstRtEntry,ULONG *pulRtNumReturn);
/*******************************************************************************
*    Func Name: TCPIP_SetRoutePolicyByVrf
* Date Created: 2009-02-02
*       Author: qinyun
*  Description: ��Ԥ����ѡ·����Ϊ������Ԫ�����ڽӿ����ȼ�������£���Э��ջ��
*               ��֮��ָ��ѡ·������������֮���л�������ʵʱ��Ч��
*               �������Ϊ�·�����·�����ܶ�̬�л�
*        Input: ULONG ulPolicy:ʹ��ѡ·���Ե������֣�0Ϊʹ�ܰ����ӿ����ȼ�ѡ·��
*               1Ϊʹ����Ԫ��·�ɸ��ɷֵ�ѡ·��
*       Output:
*       Return: �ɹ�����VOS_OK,ʧ�ܷ��ش�����(��sfib4_api.h)
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-02   qinyun                  Create
*
*******************************************************************************/
extern ULONG TCPIP_SetRoutePolicyByVrf(CHAR *pszVrfName,ULONG ulPolicy);
/*******************************************************************************
*    Func Name: TCPIP_GetOutIfindexByDstIPByVrf
* Date Created: 2009-02-02
*       Author: qinyun
*  Description: ����Ŀ�ĵ�ַ���ҳ��ӿ�����
*        Input: ULONG ulDIP:  32λ�����ֽ���ĵ�ֵַ
*               CHAR *szVrfName:VRFʵ����
*       Output: ULONG *pulOutIfIndex:���ӿ�ָ��
*       Return: �ɹ�����FIB4_OK,ʧ�ܷ��ش�����(��sfib4_api.h)
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-02   qinyun                  Create
*
*******************************************************************************/
extern ULONG TCPIP_GetOutIfindexByDstIPByVrf(ULONG ulDIP, CHAR *szVrfName, ULONG *pulOutIfIndex);
/*******************************************************************************
*    Func Name: TCPIP_PPI_DownloadStaticRtByNextHop
* Date Created: 2009-02-02
*       Author: qinyun
*  Description: ������̬·�ɻ�DHCP·�ɣ��ѷ���Ҫ����·���NP
*        Input: ULONG ulIfIndex:���ӿ�����
*               ULONG ulNextHop:·����һ����ַ��������
*               ULONG ulVlinkIndex:Ҫˢ��·�ɵ�vlink����
*       Output:
*       Return: VOS_OK:�ɹ���ʧ�ܷ��ش�����(��sfib4_api.h)
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-02   qinyun                  Create
*
*******************************************************************************/
extern ULONG TCPIP_PPI_DownloadStaticRtByNextHopByVrf(ULONG ulVrfIndex, ULONG ulIfIndex,
                                                                    ULONG ulNextHop, ULONG ulVlinkIndex);

extern ULONG TCPIP_SetWarningRouteNumByVrf(ULONG ulType,ULONG ulRouteNum,CHAR *szVrfName);

extern ULONG TCPIP_GetWarningRouteNumByVrf(ULONG ulType,ULONG *pulRouteNum,CHAR *szVrfName);
/* End: VISP1.7C03 VRF qinyun , 2009-01-20 */

/*******************************************************************************
*    Func Name: TCPIP_GetRoutePolicyByVrf
* Date Created: 2009-04-08
*       Author: zengshaoyang62531
*  Description: ����VRF��ȡƽ��·�ɵ�ѡ·����
*        Input: CHAR *pszVrfName:VRF����
*       Output: ULONG *pulPolicy:ƽ��·��ѡ·����
*       Return:
*      Caution: �貹������
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-08   zengshaoyang62531       Create
*
*******************************************************************************/
extern ULONG TCPIP_GetRoutePolicyByVrf(CHAR *pszVrfName,ULONG *pulPolicy);

/*******************************************************************************
*    Func Name: TCPIP_GetRoutePolicy
* Date Created: 2009-04-08
*       Author: zengshaoyang62531
*  Description: ��ȡƽ��·�ɵ�ѡ·����
*        Input:
*       Output: ULONG *pulPolicy:ƽ��·�ɵ�ѡ·����
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-08   zengshaoyang62531       Create
*
*******************************************************************************/
extern ULONG TCPIP_GetRoutePolicy(ULONG *pulPolicy);

/*******************************************************************************
*    Func Name: TCPIP_OpenFibTableByFilter
* Date Created: 2010-11-02
*       Author: zengshaoyang62531
*  Description: ���ݹ���������·�ɱ�ľ��
*        Input: FIB4_FILTER_COND_API_S *pstFilter:��������,�ο�FIB4_FILTER_COND_API_S�ṹ��˵��
*       Output: ULONG *pulHandle:���صľ��
*       Return:
*      Caution: ����������Ϊ��ʱ����ѯȫ��VRF�µ�ȫ��·��
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-11-02   zengshaoyang62531       Create
*
*******************************************************************************/
extern ULONG TCPIP_OpenFibTableByFilter(UINTPTR *pulHandle, FIB4_FILTER_COND_API_S *pstFilter);

/*******************************************************************************
*    Func Name: TCPIP_GetNextFibEntry
* Date Created: 2010-11-02
*       Author: zengshaoyang62531
*  Description: �����û�ָ�������������ظ��û�һ��·�ɱ���
*        Input: ULONG ulHandle:·�ɾ����
*       Output: TCPIP_RT4_ENTRY_BY_VRF_S *pstRtEntry:���ص�·�ɱ���
*       Return: VOS_OK�ɹ���FIB4_GET_END,·�ɱ����ѯ����;����������
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-11-02   zengshaoyang62531       Create
*
*******************************************************************************/
extern ULONG TCPIP_GetNextFibEntry(UINTPTR ulHandle, TCPIP_RT4_ENTRY_BY_VRF_S* pstRtEntry);

/*******************************************************************************
*    Func Name: TCPIP_CloseFibTableByFilter
* Date Created: 2010-11-02
*       Author: zengshaoyang62531
*  Description: �ر�·�ɾ�����ͷ������Դ
*        Input: ULONG ulHandle:·�ɾ��
*       Output: 
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-11-02   zengshaoyang62531       Create
*
*******************************************************************************/
extern ULONG TCPIP_CloseFibTableByFilter(UINTPTR ulHandle);

/*******************************************************************************
*    Func Name: TCPIP_Reg_VpnFib
* Date Created: 2008-4-28
*       Author: zhangchunyu(62474)
*  Description: ע���Ʒ��ѯFIB�ӿ�
*        Input: TCPIP_SEARCH_VPN_FIB_FUN pfSearchFib: ��Ʒ��ѯFIB����
*       Output:
*       Return: FIB4_OK/FIB4_ERR    �ɹ�/ʧ��
*      Caution: �ýӿ�ֻ��PTN��Ʒ���ⳡ������
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-4-28    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_Reg_VpnFib(TCPIP_SEARCH_VPN_FIB_FUN pfSearchFib);

/*******************************************************************************
*    Func Name: TCPIP_Search_VispFIB
* Date Created: 2008-5-6
*       Author: zhangchunyu(62474)
*  Description: �˺����ṩ��OSPʹ�ã�Ϊ��֧������VPN,FIB��ΪVISP FIB �Ͳ�ƷFIB,
*               OSPʹ��VISP FIB,��Ʒʹ���Լ���FIB.VISP�ڲ���ѯFIBͨ������
*               IP_FIB_AllocValid��ѯ���ڸú������ж��Ƿ�ע���ƷFIB���ע���ƷFIB,
*               ��OSP�ж��Ƿ���OSP�Ľӿڣ������OSP�Ľӿ����ѯVISP FIB,�����ѯ��ƷFIB
*        Input: ROUTE4_S* pstRoute:
*       Output:
*       Return: 0/��0  �ɹ�/ʧ��
*      Caution: �ýӿ�ֻ��PTN��Ʒ���ⳡ������
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-5-6    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_Search_VispFIB (ROUTE4_S* pstRoute);

/*******************************************************************************
*    Func Name: TCPIP_OpenRib4Table
* Date Created: 2011-08-12
*       Author: zhangliangzhi00187023
*  Description:  ͨ�������VRF���ƣ���ȡ��ѯ�����
*        Input:  CHAR * pszVrfName  : ����VRF������
*       Output: ULONG *pulWaitlist : �������
*       Return: RIB4_OK,RIB4_ERR_GET_VRFINDEX,RIB4_ERR_NULL_POINTER,
*                     RIB4_ERR_VRFID_OUT_BOUND,RIB4_ERR_MALLOC_FAIL
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-08-12   zhangliangzhi00187023                 Create
*
*******************************************************************************/
ULONG TCPIP_OpenRib4Table(UINTPTR *pulWaitlist, CHAR *pszVrfName);

/******************************************************************************
*
*    Func Name: TCPIP_GetRib4Entry
* Date Created: 2011-08-12
*       Author: zhangliangzhi00187023
*  Description:  ͨ����ѯ�������ȡ��һ���ڵ㡣
*       Input:  ULONG ulWaitlist  : ��ѯ���
*       Output:  TCPIP_RIB_RT4_ENTRY_S *pstRtEntry : ��ѯ��������һ���ڵ�
*       Return: RIB4_OK,RIB4_ERR_NULL_INPUT,RIB4_ERR_GET_VRFINDEX,RIB4_ERR_NO_USE_ENTRY
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-08-12   zhangliangzhi00187023                 Create
*
*******************************************************************************/
ULONG TCPIP_GetRib4Entry(UINTPTR ulWaitlist, TCPIP_RIB_RT4_ENTRY_S *pstRtEntry);

/*******************************************************************************
*    Func Name: TCPIP_CloseRib4Table
* Date Created: 2011-08-12
*       Author: zhangliangzhi00187023
*  Description:  �ر� ��ѯ�����
*        Input:  ULONG ulWaitlist: ��ѯ���
*       Output: 
*       Return: RIB4_OK,RIB4_ERR_HANDLE
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-08-12   zhangliangzhi00187023                 Create
*
*******************************************************************************/
ULONG TCPIP_CloseRib4Table(UINTPTR ulWaitlist);

/*******************************************************************************
*    Func Name: TCPIP_ShowRib4ByVrfName
* Date Created: 2011-08-12
*       Author: zhangliangzhi00187023
*  Description: ��ʾIPv4 RIB·�ɱ�����Ϣ��
*        Input: CHAR *pszVrfName: VRF������
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-08-12   zhangliangzhi00187023                 Create
*
*******************************************************************************/
VOID TCPIP_ShowRib4ByVrfName(CHAR *pszVrfName);


ULONG TCPIP_OpenRibTableByFilter(UINTPTR *pulHandle,TCPIP_RIB_FILTER_API_S *pstFilter);


ULONG TCPIP_GetRib4EntryByFilter(UINTPTR ulHandle, TCPIP_RIB_RT4_ENTRY_S *pstRtEntry);


ULONG TCPIP_CloseRibTableByFilter(UINTPTR ulHandle);

/*******************************************************************************
*    Func Name: TCPIP_NotifyIfPriChange
* Date Created: 2012-12-14
*       Author: c00902193
*  Description: This function is notify VISP about priority change on given input
*               IfIndex. If the interface is not find with given ulIfIndex (or)
*               the link protocol of the interface is not PPP, MP and Ethernet,
*               it will return error. This function in turn trigger the balance
*               routing selection process, if the earlier route selection has done
*               based on the interface priority.
*        Input:
*               ULONG ulIfIndex:Interface Index
*       Output: None
*       Return: Success or error code.
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-12-17   chandra (c00902193)         Create
*
*******************************************************************************/
ULONG TCPIP_NotifyIfPriChange(ULONG ulIfIndex);

/*******************************************************************************
*    Func Name: TCPIP_GetBalTable
* Date Created: 2013-09-12
*       Author: qinyun62011
*  Description: ָ����ȷĿ�ĵ�ַ�������ѯƽ��·����Ϣ
*        Input: pstFilter:������������ǰ��֧��VRF������Ŀ�ĵ�ַ�����볤�ȡ�
*               ��һ�������ӿ�������·��FLAG�ֶΡ�����VRF������Ŀ�ĵ�ַ��
*               ���볤��Ϊ�����ƥ��������
*                 pulNumofTable: ����pstEntryTable�ĸ���
*       Output: pstEntryTable: ƽ��·����Ϣ(RTMSG4_S�ṹ������)
*                 pulNumofTable: ��ȡ����·�ɸ���
*       Return: FIB4_OK          �ɹ�
*               ����             ʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-09-12   qinyun62011           Create
*******************************************************************************/
ULONG TCPIP_GetBalTable(RTMSG4_S *pstFilter,RTMSG4_S *pstEntryTable, ULONG *pulNumofTable);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _SFIB4_API_H_ */

