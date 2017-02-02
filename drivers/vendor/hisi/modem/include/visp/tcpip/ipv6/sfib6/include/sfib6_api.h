
/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              sfib6_api.h
*
*  Project Code: VISPV1R7
*   Module Name:   
*  Date Created: 2008-3-9
*        Author: wangbin(62223)
*   Description: SFIB6ģ������ṩ��ͷ�ļ�
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*-------------------------------------------------------------------------------
*  2008-3-8 wangbin(62223)     Create the first version.
*
*******************************************************************************/
#ifndef _SFIB6_API_H_
#define _SFIB6_API_H_

#ifdef __cplusplus
extern "C"{
#endif

#define FIB6_OK                 VOS_OK
#define FIB6_ERR                VOS_ERR
#define SFIB6_GENERAL_ERR       VOS_ERR + 1
#define SFIB6_NOT_FIND_ROUTE    VOS_ERR + 2
#define SFIB6_ERR_SCAN_FAIL     VOS_ERR + 3
#define FIB6_NOT_REGISTER       VOS_ERR + 4
#define FIB6_MALLOC_FAIL        VOS_ERR + 5
#define FIB6_GET_RTENTRY_ERR    VOS_ERR + 6
#define FIB6_IS_L2PORT          VOS_ERR + 7 /*�����Ŀ��ӿ��Ƕ���˿�*/
#define FIB6_ERR_RM_TYPE        VOS_ERR + 8 /*RTMģʽ��*/
#define FIB6_ERR_DEST_ADDR      VOS_ERR + 9 /*Ŀ�ĵ�ַ�Ƿ�*/
#define FIB6_ERR_IF_NULL        VOS_ERR + 10/*�ӿ�Ϊ��*/
#define FIB6_ERR_IF_TYPE        VOS_ERR + 11/*�ӿ����ʹ���*/
#define FIB6_ERR_NULL_PARAM     VOS_ERR + 12/*���ָ��Ϊ��*/
#define FIB6_ERR_NETRT_PREFIX   VOS_ERR + 13/*����·��ǰ׺��Ч*/
#define FIB6_ERR_NETRT_NEXTHOP_INVALID    VOS_ERR + 14/*��һ������Ϊָ���ӿ�Global��ַ*/
#define FIB6_ERR_NETRT_DESTADDR_INVALID   VOS_ERR + 15/*Ŀ�ĵ�ַ����һ����ǰ׺����������*/
#define FIB6_ERR_NETRT_EXIST              VOS_ERR + 16/*����·���Ѿ�����*/
#define FIB6_ERR_NETRT_NOT_EXIST          VOS_ERR + 17/*����·�ɲ�����*/
#define FIB6_ERR_NETRT_GET_IF_INFO        VOS_ERR + 18/*��ȡ����·�ɳ��ӿ���Ϣ����*/
#define FIB6_ERR_NETRT_IF_TYPE_INVALID    VOS_ERR + 19/*����·�ɳ��ӿ�������Ч*/
#define FIB6_ERR_GET_IPV6VTABLE           VOS_ERR + 20/*��ȡIPv6������*/
#define FIB6_ERR_RIB_FULL                 VOS_ERR + 21/*RIB6������*/
#define FIB6_ERR_DESTADDR_NOT_GLOBAL      VOS_ERR + 22/*Ŀ�ĵ�ַ����Global��ַ����*/
#define FIB6_ERR_PREFIXLEN_INVALID        VOS_ERR + 23/*��ַǰ׺���ȷǷ�*/
#define FIB6_ERR_PRIORITY_INVALID         VOS_ERR + 24/*���ȼ��Ƿ�*/
#define FIB6_ERR_NEXTHOP_OR_INTF_INVALID  VOS_ERR + 25/*��һ������ӿ���Ч*/
#define FIB6_ERR_NEXTHOP_IS_OWN_GLOBAL    VOS_ERR + 26/*��һ���Ǳ���Global��ַ*/
#define FIB6_ERR_BEST_SEARCH_FAIL         VOS_ERR + 27/*��ѯָ��Ŀ�ĵ�ַ��·��ʧ��*/
#define FIB6_ERR_INVALID_FLAG             VOS_ERR + 28/*����ı�־*/
#define FIB6_ERR_INVALID_WLHANDLE         VOS_ERR + 29/* ��Ч��Waitlist��� */
#define RIB6_ERR_NO_USE_ENTRY             VOS_ERR + 30/* û�п��õ���һ��·�ɽڵ�*/
#define FIB6_ERR_NULL_POINTER    VOS_ERR + 31
#define FIB6_GET_FAIL_CLOSE      VOS_ERR + 32
#define FIB6_SEARCH_NO_FILTER    VOS_ERR + 33
#define FIB6_ERR_GET_VRFINDEX    VOS_ERR + 34
#define FIB6_GET_FAIL_OPEN          VOS_ERR + 35
#define FIB6_GET_RT_FAIL_CLOSE   VOS_ERR + 36
#define FIB6_GET_FAIL                      VOS_ERR + 37
#define FIB6_GET_END                       VOS_ERR + 38
#define FIB6_GET_ERR_CLOSE_VRF   VOS_ERR + 39
#define FIB6_GET_FAIL_CLOSE_VRF  VOS_ERR + 40
#define FIB6_GET_FAIL_BY_VRF       VOS_ERR + 41
#define FIB6_GET_FAIL_CLOSE_NETIP  VOS_ERR + 42
#define FIB6_GET_FAIL_OPEN_NETIP   VOS_ERR + 43
#define FIB6_GET_VRF_NET_FAIL_CLOSE  VOS_ERR + 44
#define FIB6_GET_FAIL_VRF_NET_CLOSE   VOS_ERR + 45
#define FIB6_ERR_WAITLIST_GET VOS_ERR + 46
/* Begin:VISP V3R2C10 VRF chandra , 2014-03-18 */
#define FIB6_ERR_VRF_NOT_INIT VOS_ERR + 47
#define FIB6_ERR_INVALID_INTERFACE VOS_ERR + 48
#define FIB6_ERR_IF_NOT_IN_VRF VOS_ERR + 49
/* End:VISP V3R2C10 VRF chandra , 2014-03-18 */

#define FIB6_RTMSG_ADD             1
#define FIB6_RTMSG_DEL             2
#define FIB6_RTMSG_CLEAR           3
#define FIB6_RTMSG_REFRESH         4    /* added for defect 7034; Guru, 1-03-04 */
#define FIB6_RTMSG_STACK_ADD       5

#define FIB6_OLDRTMSG6             6    /* added for defect 7034; Guru, 1-03-04 */
#define FIB6_NEWRTMSG6             7    /* added for defect 7034; Guru, 1-03-04 */



#define FIB6_STATICRT_MIN_PRIORITY      1
#define FIB6_STATICRT_MAX_PRIORITY      255

/* Added by hanna55555, VISPV1R8C03 for net route, 2009/12/16 */
#define FIB6_NETRT_MIN_PREFIX      1
#define FIB6_NETRT_MAX_PREFIX      127
/*End of Added by hanna55555, 2009/12/16 */

/*added by limin00188004, 2011/8/12   ���ⵥ��:C06������ */
#define  TCPIP_RIB6_MAX_VRFNAME_LENGTH   31      /*��TCPIP_MAX_VRFNAME_LENGTH����һ��*/

#define FIB6_SEARCH_ALL                0x00    /*��ѯ����VRFȫ��·�� */

#define FIB6_SEARCH_BY_VRF6             0x01    /*ָ��VRF��ѯ[��ѯָ��VRF�е�ȫ��·��]*/

#define FIB6_SEARCH_BY_NETIP           0x02    /*ָ�����β�ѯ[��ѯȫ��VRF�е�ָ��·��]*/

#define FIB6_SEARCH_BY_VRF_AND_NETIP   (FIB6_SEARCH_BY_VRF6 | FIB6_SEARCH_BY_NETIP)    /*ָ��VRF+���β�ѯ[��ѯָ��VRF�е�ָ��·��]*/

typedef struct tagTCPIP_RIB_RT6_ENTRY
{
    ULONG  ulRtDestAddr[4];                             /* Ŀ�ĵ�ַ */
    ULONG  ulRtDestPrefLen;                             /* ���볤�� */
    ULONG  ulRtNextHopAddr[4];                          /* ��һ�� */
    ULONG  ulRtIfIndex;                                 /* ���ӿ����� */
    ULONG  ulRtFlags;                                   /* ·�ɱ�� */
    ULONG  ulRtPri;                                     /* ·�����ȼ� */
    ULONG  ulRtProto;                                   /* ·��Э������ */
    ULONG  ulRtUse;                                     /* �Ƿ���Ч */
    CHAR   szVrfName[TCPIP_RIB6_MAX_VRFNAME_LENGTH + 1];     /* VRF���� */
} TCPIP_RIB_RT6_ENTRY_S;
/*End of Modified by limin00188004, 2011/8/12   ���ⵥ��:C06������ */


/*֧��ͨ��Ԥ���õķ�ʽ����·��ѡ·����*/
typedef enum tagRoute6Strategy
{
    RS6_ONE_BY_ONE = 0,    /* 0 ���ɷֵ�����ѭ��ʽ */
    RS6_NEWEST_FIRST,      /* 1 ����·����Ч */
    RS6_OLDEST_FIRST,      /* 2 ����·����Ч */
    RS6_PRI_BASED,         /* 3 �ӿ����ȼ������Ч */
    RS6_BFCR,              /* 4 ��Ԫ�鱨�������� */
    RS6_RTPRI,             /* 5 ·�����ȼ� */
    RS6_END
}ROUTE6_STRATEGY_E;

/*֧��ͨ��Ԥ���õķ�ʽ����·���·�NP��ģʽ*/
typedef enum tagFib6NpMode
{
    FIB6_NP_DOWNALL = 0, /*�·�ȫ��·����NP*/
    FIB6_NP_DOWNBEST,    /*�·�����·����NP*/
    FIB6_NP_END
}FIB6NPMODE_E;

/*֧��ͨ��Ԥ���õķ�ʽ����NP·�ɸ���ģʽ*/
typedef enum tagUpdateFib6NpMode
{
    UPDATE_FIB6_ADDTHENDEL,   /*���·����ӣ����·�ɾ��*/
    UPDATE_FIB6_DELTHENADD    /*���·�ɾ�������·�����*/
}UPDATEFIB6NPMODE_E;

/* ��IPv6��������ȡ����Ϣ */
typedef struct tagPacket6Info 
{
    ULONG ulSrcAddr[4];            /* ԴIPv6��ַ */            
    ULONG ulDstAddr[4];            /* Ŀ��IPv6��ַ */ 
    USHORT usSrcPort;            /* Դ�˿ں� or ICMPv6 Type*/            
    USHORT usDstPort;            /* Ŀ�Ķ˿ں� or ICMPv6 Code*/            
    UCHAR ucProto;               /* Э��ŷ�Χ���ֵ */
    UCHAR ucReserve[3];         /*�����ֶ�*/
} PACKET6INFO_S;

/*  One of the data stores maintained by FIB6Agent for providing search interface
    to external modules */
/* �����ݽṹ��Ϊ��MCCP��Ʒ����FIBʹ��, ������Ʒ����Ӧ�ø����ݽṹ */
typedef struct tagROUTE6
{
    USHORT usZoneID;            /* vrf id */
    UCHAR  ucPadding_1[2];
    ULONG  aulDestination[4];
    ULONG  aulNexthop[4];
    ULONG  aulLocalAddress[4];        
    ULONG  ulIfIndex;           /* index of outgoing interface */
    ULONG  ulATIndex;           /* virtual link index */
    ULONG  ulSlot;
    ULONG  ulFlags;             /* RTF_GATEWAY, RTF_HOST, ...*/
    UCHAR  ucDestPrefixLength;
    UCHAR  ucLocalPrefixLength;
    UCHAR  ucPadding_2[2];
    ULONG  ulLabel;             /* Inner label */ 
    /* >=1 - > indicates MPLS tunnel, 0 - indicates normal forwarding  
       V6 stack will decide MPLS forwarding/normal forwarding based on this */
    ULONG  ulToken;  
/* Guru: End of addition for 6PE implementation 26th Mar'04 */
    /* Added by hanna55555, VISPV1R8C03, 2009/11/30 */
    ULONG ulRtPri;            /* route priority */
    /*End of Added by hanna55555, 2009/11/30 */
    PACKET6INFO_S *pstPacket6Info;
} ROUTE6_S;

typedef struct tagTCPIP_RTMSG6
{
    USHORT  usType;
    USHORT  usZoneID;
    ULONG   aulDestination[4];
    ULONG   aulNexthop[4];
    ULONG   aulLocalAddress[4];        
    ULONG   ulIfIndex;          /* index of outgoing interface */
    ULONG   ulATIndex;          /* virtual link index */
    ULONG   ulSlot;
    ULONG   ulFlags; 
    /* Added by hanna55555, VISPV1R8C03, 2009/12/7 */
    ULONG   ulRTPri;            /* route priority */
    /*End of Added by hanna55555, 2009/12/7 */
    UCHAR   ucDestPrefixLength;
    UCHAR   ucLocalPrefixLength;
    USHORT  ucReserved1;
} TCPIP_RTMSG6_S;

typedef struct tagTCPIP_RT6_ENTRY
{
    ULONG  aulRt_Dest[4];  
    ULONG  ulRt_Dest_PrefLen;
    ULONG  aulRt_Nexthop[4];
    ULONG  ulRt_Flags;        
    ULONG  ulRt_IfIndex;       /* index of outgoing interface */
    ULONG  ulRt_ATIndex;       /* index of virtual link between rt_stLclAddr */
    ULONG  ulRt_Slot;          /* slot num of outgoing interface */
    /* Added by hanna55555, VISPV1R8C03, 2009/12/7 */
    ULONG  ulRTPri;            /* route priority */
    /*End of Added by hanna55555, 2009/12/7 */
    ULONG  ulRt_Proto;
} TCPIP_RT6_ENTRY_S;

typedef struct tagTCPIP_ROUTE6
{
    ULONG  aulDestination[4];
    ULONG  aulNexthop[4];
    ULONG  aulLocalAddress[4];        
    ULONG  ulIfIndex;           /* index of outgoing interface */
    ULONG  ulATIndex;           /* virtual link index */
    ULONG  ulSlot;
    ULONG  ulFlags;             /* RTF_GATEWAY, RTF_HOST, ...*/
    /* Added by hanna55555, VISPV1R8C03, 2009/12/7 */
    ULONG  ulRTPri;            /* route priority */
    /*End of Added by hanna55555, 2009/12/7 */
    UCHAR  ucDestPrefixLength;
    UCHAR  ucLocalPrefixLength;
    USHORT usZoneID;            /* zone ID */
    ULONG ulSrcAddr[4];            /* ԴIPv6��ַ */            
    ULONG ulDstAddr[4];            /* Ŀ��IPv6��ַ */ 
    USHORT usSrcPort;            /* Դ�˿ں� or ICMPv6 Type*/            
    USHORT usDstPort;            /* Ŀ�Ķ˿ں� or ICMPv6 Code*/            
    UCHAR ucProto;               /* Э��ŷ�Χ���ֵ */
    UCHAR ucReserve[3];         /*�����ֶ�*/
} TCPIP_ROUTE6_S;

#ifndef _VRP_IN6ADDR_S
#define _VRP_IN6ADDR_S
typedef   struct    tagVRPIN6Addr
{
    union
    {
        UCHAR   u6_ucaddr[16];
        USHORT  u6_usaddr[8];
        ULONG   u6_uladdr[4];
    } vrp_u6_addr;    /* 128-bit IP6 address */
}VRP_IN6ADDR_S;
#endif

/* Added by hanna55555, VISPV1R8C03, 2009/12/1 */
typedef struct tagTCPIP_RT6
{
    VRP_IN6ADDR_S stIn6Addr;          /*Ŀ�ĵ�ַ*/
    ULONG ulPreLen;                   /*���볤��,0~128*/
    VRP_IN6ADDR_S stGateway;          /*���ص�ַ*/
    ULONG ulIfIndex;                  /*���ӿ�����*/
    ULONG ulRTPri;                    /*·�����ȼ�,1~255*/
}TCPIP_RT6_S;

typedef struct tagTCPIP_CFG_RT_BYNH
{
    ULONG ulIfIndex;                  /*���ӿ�����*/
    VRP_IN6ADDR_S stGateway;          /*���ص�ַ*/
}TCPIP_CFG_RT_BYNH_S;

typedef struct tagTCPIP_CFG_RT_EXACT
{
    VRP_IN6ADDR_S stIn6Addr;          /*Ŀ�ĵ�ַ*/
    ULONG ulMaskLen;                  /*���볤��,0~128*/
    VRP_IN6ADDR_S stGateway;          /*���ص�ַ*/
    ULONG ulIfIndex;                  /*���ӿ�����*/
}TCPIP_CFG_RT_EXACT_S;

typedef struct tagTCPIP_NET_RT6
{
    VRP_IN6ADDR_S stIn6Addr;             /*Ŀ�ĵ�ַ*/
    ULONG ulPreLen;                      /*���볤��,1~127*/
    VRP_IN6ADDR_S stGateway;             /*���ص�ַ*/
    ULONG ulIfIndex;                     /*���ӿ�����*/
}TCPIP_NET_RT6_S;



typedef struct tagSFIB_AM6_MSG
{
    ULONG ulIfnetIndex;     /*�ӿ�����*/
    ULONG ulMsgType;        /*��ַ���ɾ����Ϣ 0-����,1-ɾ��*/
    ULONG ulLogAddr[LEN_4]; /*��ַ*/
    ULONG ulSubMaskLen;     /*��ַǰ׺*/
    /* Begin:VISP V3R2C10 VRF chandra , 2014-03-18 */
    ULONG  ulInstanceID;
    /* End: VISP V3R2C10 VRF chandra , 2014-03-18 */    
}SFIB_AM6_MSG_S;

/* Begin:VISP V3R2C10 VRF chandra , 2014-03-18 */
#define FIB6_STATIC_ADDR_ADD       1
#define FIB6_STATIC_ADDR_DEL       0

#define SFIB6_VRF_MAX_VRFNAME_LENGTH    31

typedef struct tagTCPIP_RM6_CFGSTATIC_S
{
    ULONG Oper; /* 1 is Add, 0 is delete */
    VRP_IN6ADDR_S stIn6Addr;  
    ULONG ulPreLen; 
    VRP_IN6ADDR_S stGateway;   
    UCHAR szIfName[MAX_IF_NAME_LENGTH + 1];   
    ULONG ulRTPri; 
    UCHAR szVrfName[SFIB6_VRF_MAX_VRFNAME_LENGTH + 1];    
}TCPIP_RM6_CFGSTATIC_S;

typedef struct tagTCPIP_NET_RT6_WITH_VRF
{
    ULONG ulOper; /* 1- Add and 0 - Delete */
    VRP_IN6ADDR_S stIn6Addr;             /*Ŀ�ĵ�ַ*/
    ULONG ulPreLen;                      /*���볤��,1~127*/
    VRP_IN6ADDR_S stGateway;             /*���ص�ַ*/
    ULONG ulIfIndex;                     /*���ӿ�����*/
    UCHAR szVrfName[SFIB6_VRF_MAX_VRFNAME_LENGTH + 1];     
}TCPIP_NET_RT6_WITH_VRF_S;
/* End:VISP V3R2C10 VRF chandra , 2014-03-18 */

/*added by Abhishek Mishraa for VRF6 related APIs*/
typedef struct tagFIB6_FILTER_COND_API
{
    CHAR  szVrfName[TCPIP_RIB6_MAX_VRFNAME_LENGTH + 1]; /*VPN ����*/
    ULONG ulRtDestAddr[4];                                     /*Ŀ�ĵ�ַ*/
    ULONG ulDstMask;                                   /*���볤��,���û���д���볤�ȣ�����128*/
    ULONG ulFilterType;                               /*FIB6_SEARCH_ALL--�޹���������ѯ
                                                                   FIB6_SEARCH_BY_VRF6--ָ��VRF6��ѯ
                                                                   FIB6_SEARCH_BY_NETIP--ָ�����β�ѯ
                                                                   FIB6_SEARCH_BY_VRF6_AND_NETIP--ָ��VRF6+���β�ѯ*/

}FIB6_FILTER_COND_API_S;


typedef struct tagTCPIP_RT6_ENTRY_BY_VRF
{
     ULONG  ulRt_Dest[4];
     ULONG  ulRt_Dest_PrefLen;
     ULONG  ulRt_Nexthop[4];
     ULONG  ulRt_Flags;         /* route flags -RTF_GATEWAY, RTF_HOST */
     ULONG  ulRt_IfIndex;       /* index of outgoing interface */
     ULONG  ulRt_ATIndex;       /* index of virtual link between rt_stLclAddr */
     ULONG  ulRt_Slot;          /* slot num of outgoing interface */
     ULONG  ulRt_Use;           /* metrics to consider */
     ULONG  ulRt_State;
     ULONG  ulRt_Proto;
     ULONG  ulRt_TimeStamp;
     ULONG  ulCacheEntryIndex;  /* used to access corr. cache entry */
     ULONG  ulRTPri;            /* route priority */
     ULONG  ulVrfIndex;         /* VRF Index*/
} TCPIP_RT6_ENTRY_BY_VRF_S;

/*End of addion for VRF6 related APIs  by Abhishek Mishraa */

typedef ULONG ( *IPV6_SHELL_RM_CALLBACK_FUNC_PTR)(SFIB_AM6_MSG_S *pstIn6Addr);
/*End of Added by hanna55555, 2009/12/1 */

typedef ULONG (*TCPIP_SEARCH_VPN_FIB6_FUN)(ROUTE6_S* pstRoute6);

/*******************************************************************************
*    Func Name: TCPIP_SetSFIB6Debug
*  Description: Set debug switch
*        Input: ULONG ulDbg: 0 - OFF; Other value - ON. 
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
extern ULONG TCPIP_SetSFIB6Debug(ULONG ulDbg);

/*******************************************************************************
*    Func Name: TCPIP_GetSFIB6Debug
*  Description: get sfib6 debug switch
*        Input: ULONG *pulDbg: 
*       Output: VOID
*       Return: FIB6_ERR
*               FIB6_OK
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-3-9  wanggbin(62223)        Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_GetSFIB6Debug(ULONG *pulDbg);

/*******************************************************************************
*    Func Name: TCPIP_RequestFIB6
*  Description: Adds, Updates, Deletes or Clears the FIB table depending 
*               on the input message type
*        Input: TCPIP_RTMSG6_S * pstRtMsg: ·����Ϣָ��
*       Output: 
*       Return: FIB6_OK,FIB6_ERR,FIB6_NOT_REGISTER
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-3-9  wanggbin(62223)        Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_RequestFIB6(TCPIP_RTMSG6_S * pstRtMsg);

/*******************************************************************************
*    Func Name: TCPIP_OpenFib6Table
*  Description: register waillist object for doubly linked list of route
*        Input: ULONG *pulWaitListHandle: waitlist handle
*               USHORT usZoneID: zone id
*       Output: 
*       Return: FIB6_OK,FIB6_ERR,FIB6_NOT_REGISTER
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-3-9  wanggbin(62223)        Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_OpenFib6Table (UINTPTR *pulWaitListHandle);

/*******************************************************************************
*    Func Name: TCPIP_CloseFib6Table
*  Description: unregister waillist object for doubly linked list of route
*        Input: ULONG ulWaitlist: waitlist handle
*       Output: VOID
*       Return: FIB6_OK
*               FIB6_ERR
*               FIB6_NOT_REGISTER
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-3-9  wanggbin(62223)        Creat the first version.
*
*******************************************************************************/
extern ULONG  TCPIP_CloseFib6Table(UINTPTR ulWaitlist);

/*******************************************************************************
*    Func Name: TCPIP_GetFib6Entry
*  Description: Fetches bulk of FIB entries, protected  using waitlist
*        Input: 
*               ULONG ulWaitlist    : waitlist handle
*               ULONG ulRtNumWanted  : number of wanted entrys
*       Output: TCPIP_RT6_ENTRY_S *pstRtEntry : point to route entry table
                ULONG *pulRtNumReturn: number of get entrys
*               
*       Return: FIB6_ERR
*               FIB6_OK
*               FIB6_RT_END
*               FIB6_ERR_SCAN
*               FIB6_MALLOC_FAIL
*               FIB6_GET_RTENTRY_ERR
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-3-9  wanggbin(62223)        Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_GetFib6Entry(UINTPTR ulWaitlist,ULONG ulRtNumWanted,
                                                            TCPIP_RT6_ENTRY_S *pstRtEntry,ULONG *pulRtNumReturn);

/*******************************************************************************
*    Func Name: TCPIP_GetRoute6Count
*  Description: Returns total number of routes in corresponding FIB table
*        Input: 
*       Output: ULONG *pulNum :number of routes
*       Return: FIB6_OK
*               FIB6_ERR
*               FIB6_NOT_REGISTER
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-3-9  wanggbin(62223)        Creat the first version.
*
*******************************************************************************/

extern ULONG TCPIP_GetRoute6Count (ULONG *pulNum);

/*******************************************************************************
*    Func Name: TCPIP_LookupFIB6
*  Description: Searches for the given destination address in the FIB table 
*               and fills with the route information if found
*        Input: TCPIP_ROUTE6_S* pstRoute6  : Pointer to route entry memory, containing
*                                      the destination address, and zoneid
*               BOOL_T bEnableRouteBal: A flag indicate whether to use route balancing or not
*       Output: 
*       Return: FIB6_OK,FIB6_ERR,FIB6_NOT_REGISTER
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-3-9  wanggbin(62223)        Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_LookupFIB6(TCPIP_ROUTE6_S *pstRoute4, BOOL_T bEnableRouteBal);

/*******************************************************************************
*    Func Name: TCPIP_ShowFIB6
* Date Created: 2009-08-20
*       Author: mafeng(59090)
*  Description: ��ʾIPv6 FIB·�ɱ�����Ϣ
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-08-20   mafeng(59090)           Create
*
*******************************************************************************/
extern VOID TCPIP_ShowFIB6(VOID);

/*******************************************************************************
*    Func Name: TCPIP_ShowRIB6
* Date Created: 2009-08-20
*       Author: mafeng(59090)
*  Description: ��ʾIPv6 RIB·�ɱ�����Ϣ
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-08-20   mafeng(59090)           Create
*
*******************************************************************************/
extern VOID TCPIP_ShowRIB6(VOID);

/*******************************************************************************
*    Func Name: TCPIP_Route6Add
* Date Created: 2009-12-07
*       Author: hanna55555
*  Description: ����IPv6��̬·��.
*        Input: TCPIP_RT6_S *pstStaticRouter:��̬·��������Ϣ
*       Output: 
*       Return: �ɹ�����FIB6_OK
*               ʧ�ܷ��ش�����
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-07   hanna55555              Create
*
*******************************************************************************/
ULONG TCPIP_Route6Add(TCPIP_RT6_S *pstStaticRouter);

/* Begin:VISP V3R2C10 VRF chandra , 2014-03-18 */
/*******************************************************************************
*    Func Name: TCPIP_SetRoute6ByVrf
* Date Created: 2014-03-26
*       Author: C00902193
*  Description: Function to create/delete static route with VRF for ipv6.
*        Input: TCPIP_RM6_CFGSTATIC_S *pstStaticRoute: Details to create the entry.
*       Output:
*       Return: success - FIB6_OK
*                   fail - error
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-26   C00902193              Create
*
*******************************************************************************/   
ULONG TCPIP_SetRoute6ByVrf(TCPIP_RM6_CFGSTATIC_S *pstStaticRoute);
/* End:VISP V3R2C10 VRF chandra , 2014-03-18 */

/*******************************************************************************
*    Func Name: TCPIP_Route6Del
* Date Created: 2009-12-07
*       Author: hanna55555
*  Description: ɾ��IPv6��̬·��.
*        Input: TCPIP_RT6_S *pstStaticRouter:��̬·��ɾ����Ϣ
*       Output: 
*       Return: �ɹ�����FIB6_OK
*               ʧ�ܷ��ش�����
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-07   hanna55555              Create
*
*******************************************************************************/
ULONG TCPIP_Route6Del(TCPIP_RT6_S *pstStaticRouter);

/*******************************************************************************
*    Func Name: TCPIP_DisableRt6ByIfNextHop
* Date Created: 2009-12-07
*       Author: hanna55555
*  Description: ����ָ���ĳ��ӿڡ���һ��ȥʹ��·��.
*        Input: TCPIP_CFG_RT_BYNH_S  *pstRtMsg:·����Ϣ
*       Output: 
*       Return: �ɹ�����FIB6_OK
*               ʧ�ܷ��ش�����
*      Caution: ֻ����SRM��ʽ������ʹ��.
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-07   hanna55555              Create
*
*******************************************************************************/
ULONG TCPIP_DisableRt6ByIfNextHop (TCPIP_CFG_RT_BYNH_S  *pstRtMsg);

/*******************************************************************************
*    Func Name: TCPIP_EnableRt6ByIfNextHop
* Date Created: 2009-12-07
*       Author: hanna55555
*  Description: ����ָ���ĳ��ӿڡ���һ��ʹ��·��.
*        Input: TCPIP_CFG_RT_BYNH_S  *pstRtMsg:·����Ϣ
*       Output: 
*       Return: �ɹ�����FIB6_OK
*               ʧ�ܷ��ش�����
*      Caution: ֻ����SRM��ʽ������ʹ��.
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-07   hanna55555              Create
*
*******************************************************************************/
ULONG TCPIP_EnableRt6ByIfNextHop (TCPIP_CFG_RT_BYNH_S  *pstRtMsg);

/*******************************************************************************
*    Func Name: TCPIP_ExactDisableRt6
* Date Created: 2009-12-07
*       Author: hanna55555
*  Description: ����ָ����Ŀ�ĵ�ַ�����볤�ȡ����ӿڡ���һ��ȥʹ��·��.
*        Input: TCPIP_CFG_RT_EXACT_S  *pstRtMsg:·����Ϣ
*       Output: 
*       Return: �ɹ�����FIB6_OK
*               ʧ�ܷ��ش�����
*      Caution: ֻ����SRM��ʽ������ʹ��.
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-07   hanna55555              Create
*
*******************************************************************************/
ULONG TCPIP_ExactDisableRt6 (TCPIP_CFG_RT_EXACT_S  *pstRtMsg);

/*******************************************************************************
*    Func Name: TCPIP_ExactEnableRt6
* Date Created: 2009-12-07
*       Author: hanna55555
*  Description: ����ָ����Ŀ�ĵ�ַ�����볤�ȡ����ӿڡ���һ��ʹ��·��.
*        Input: TCPIP_CFG_RT_EXACT_S  *pstRtMsg:·����Ϣ
*       Output: 
*       Return: �ɹ�����FIB6_OK
*               ʧ�ܷ��ش�����
*      Caution: ֻ����SRM��ʽ������ʹ��.
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-07   hanna55555              Create
*
*******************************************************************************/
ULONG TCPIP_ExactEnableRt6 (TCPIP_CFG_RT_EXACT_S  *pstRtMsg);

/*******************************************************************************
*    Func Name: TCPIP_SetHost6RouteReserved
* Date Created: 2009-12-07
*       Author: hanna55555
*  Description: ���ýӿ�DWONʱ,�Ƿ���IPv6����·�ɵı��.
*        Input: ULONG ulIfIndex:�ӿ�����;
*               ULONG ulFlag:��������·�ɵı��,1:����,0:������;
*       Output: 
*       Return: �ɹ�����FIB6_OK
*               ʧ�ܷ��ش�����
*      Caution: ֻ����ETH��Trunk��Ӧ�Ľӿ�.
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-07   hanna55555              Create
*
*******************************************************************************/
ULONG TCPIP_SetHost6RouteReserved(ULONG ulIfIndex, ULONG ulFlag);

/*******************************************************************************
*    Func Name: TCPIP_GetHost6RouteReserved
* Date Created: 2009-12-07
*       Author: hanna55555
*  Description: ��ȡ�Ƿ���IPv6����·�ɵı��.
*        Input: ULONG ulIfIndex:�ӿ�����;
*               ULONG *pulFlag:����·�ɱ������;
*       Output: 
*       Return: �ɹ�����FIB6_OK
*               ʧ�ܷ��ش�����
*      Caution: ֻ����ETH��Trunk��Ӧ�Ľӿ�.
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-07   hanna55555              Create
*
*******************************************************************************/
ULONG TCPIP_GetHost6RouteReserved(ULONG ulIfIndex, ULONG *pulFlag);

/*******************************************************************************
*    Func Name: TCPIP_ShowHost6RouteReserved
* Date Created: 2009-12-07
*       Author: hanna55555
*  Description: ��ʾ�Ƿ���IPv6����·�ɵı��.
*        Input: CHAR *pIfName:�ӿ���;
*       Output: 
*       Return: 
*      Caution: ֻ����ETH��Trunk��Ӧ�Ľӿ�.
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-07   hanna55555              Create
*
*******************************************************************************/
VOID TCPIP_ShowHost6RouteReserved(CHAR *pIfName);

/*******************************************************************************
*    Func Name: TCPIP_NetRoute6Add
* Date Created: 2009-12-07
*       Author: hanna55555
*  Description: ������ģʽ��,����IPv6����·��.
*        Input: TCPIP_NET_RT6_S *pstNetRouter:����·����Ϣ;
*       Output: 
*       Return: �ɹ�����FIB6_OK
*               ʧ�ܷ��ش�����
*      Caution: ��������ģʽ��ʹ��,�ɲ�Ʒ���б�֤.
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-07   hanna55555              Create
*
*******************************************************************************/
ULONG TCPIP_NetRoute6Add(TCPIP_NET_RT6_S *pstNetRouter);

/*******************************************************************************
*    Func Name: TCPIP_NetRoute6Del
* Date Created: 2009-12-07
*       Author: hanna55555
*  Description: ������ģʽ��,ɾ��IPv6����·��.
*        Input: TCPIP_NET_RT6_S *pstNetRouter:����·����Ϣ;
*       Output: 
*       Return: �ɹ�����FIB6_OK
*               ʧ�ܷ��ش�����
*      Caution: ��������ģʽ��ʹ��,�ɲ�Ʒ���б�֤.
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-07   hanna55555              Create
*
*******************************************************************************/
ULONG TCPIP_NetRoute6Del(TCPIP_NET_RT6_S *pstNetRouter);

/*******************************************************************************
*    Func Name: TCPIP_SetNetRoute6ByVrf
* Date Created: 2014-03-26
*       Author: Chandra
*  Description: Function to create/delete Net route with VRF for ipv6.
*        Input: TCPIP_NET_RT6_WITH_VRF_S *pstNetRouter: Details to create the entry.
*       Output:
*       Return: success - FIB6_OK
*                   fail - error
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                              DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-04-23   Chandra 00902193              Create
*
*********************************************************************************/
ULONG TCPIP_SetNetRoute6ByVrf(TCPIP_NET_RT6_WITH_VRF_S *pstNetRouter);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncUpdateIntfAddr6Hook
* Date Created: 2009-12-07
*       Author: hanna55555
*  Description: ע��IPv6�ӿڵ�ַ�仯֪ͨ·�ɹ���ģ��Ĺ���.
*        Input: IPV6_SHELL_RM_CALLBACK_FUNC_PTR pfHookFunc:��ַ�仯֪ͨ������
*       Output: 
*       Return: �ɹ�����FIB6_OK
*               ʧ�ܷ��ش�����
*      Caution: ֻ���ڹ����綨��RM��ʽ������ʹ��.
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-07   hanna55555              Create for VISPV1R8C03
*
*******************************************************************************/
ULONG TCPIP_RegFuncUpdateIntfAddr6Hook(IPV6_SHELL_RM_CALLBACK_FUNC_PTR pfHookFunc);

/*******************************************************************************
*    Func Name: TCPIP_OpenRib6Table
* Date Created: 2011-08-12
*       Author: limin00188004
*  Description:  ͨ�������VRF���ƣ���ȡ��ѯ�����
*        Input:  CHAR * pszVrfName  : ����VRF������
*       Output: ULONG *pulWaitlist : �������
*       Return: RIB6_OK,RIB6_ERR_NULL_POINTER,RIB6_ERR_MALLOC_FAIL
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-08-12   limin00188004                 Create
*
*******************************************************************************/
ULONG TCPIP_OpenRib6Table(UINTPTR *pulWaitlist, CHAR *pszVrfName);

/******************************************************************************
*
*    Func Name: TCPIP_GetRib6Entry
* Date Created: 2011-08-12
*       Author: limin00188004
*  Description:  ͨ����ѯ�������ȡ��һ���ڵ㡣
*       Input:  ULONG ulWaitlist  : ��ѯ���
*       Output:  TCPIP_RIB_RT6_ENTRY_S *pstRtEntry : ��ѯ��������һ���ڵ�
*       Return: RIB6_OK,RIB6_ERR_NULL_INPUT,RIB6_ERR_NO_USE_ENTRY
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-08-12   limin00188004                 Create
*
*******************************************************************************/
ULONG TCPIP_GetRib6Entry(UINTPTR ulWaitlist, TCPIP_RIB_RT6_ENTRY_S *pstRtEntry);

/*******************************************************************************
*    Func Name: TCPIP_CloseRib6Table
* Date Created: 2011-08-12
*       Author: limin00188004
*  Description:  �ر� ��ѯ�����
*        Input:  ULONG ulWaitlist: ��ѯ���
*       Output: 
*       Return: RIB6_OK,RIB6_ERR_HANDLE
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-08-12   limin00188004                 Create
*
*******************************************************************************/
ULONG TCPIP_CloseRib6Table(UINTPTR ulWaitlist);

/*******************************************************************************
*    Func Name: TCPIP_ShowRib6ByVrfName
* Date Created: 2011-08-12
*       Author: limin00188004
*  Description: ��ʾIPv6 RIB·�ɱ�����Ϣ��
*        Input: CHAR *pszVrfName: VRF������
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-08-12   limin00188004                 Create
*
*******************************************************************************/
VOID TCPIP_ShowRib6ByVrfName(CHAR *pszVrfName);

/*******************************************************************************
*    Func Name: TCPIP_OpenFib6TableByFilter
* Date Created: 2013-10-10
*       Author: a00900872
*  Description: According to the filter criteria to open a handle to the routing table
*        Input: FIB6_FILTER_COND_API_S *pstFilter:Filter conditions, refer to the structure described FIB6_FILTER_COND_API_S
*       Output: ULONG *pulHandle:Returned handle
*       Return:
*      Caution:When the filter is empty, the entire query all VRF routing
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-10-10  a00900872       Create
*
*******************************************************************************/
ULONG TCPIP_OpenFib6TableByFilter(UINTPTR *pulHandle, FIB6_FILTER_COND_API_S *pstFilter);

/*******************************************************************************
*    Func Name: TCPIP_GetNextFib6Entry
* Date Created: 2013-10-10
*       Author: a00900872
*  Description:According to user-specified criteria, to return to the user a routing table entry
*        Input: ULONG ulHandle: Handle
*       Output: TCPIP_RT4_ENTRY_BY_VRF_S *pstRtEntry:Return routing table entry
*       Return: VOS_OK,Error Code��FIB4_GET_END, routing table entry end of the query; other error codes
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-10-10  a00900872       Create
*
*******************************************************************************/
ULONG TCPIP_GetNextFib6Entry(UINTPTR ulHandle, TCPIP_RT6_ENTRY_BY_VRF_S* pstRtEntry);

/*******************************************************************************
*    Func Name: TCPIP_CloseFib6TableByFilter
* Date Created: 2013-10-10
*       Author: a00900872
*  Description:Close routing handles, freeing resources
*        Input: ULONG ulHandle:Handle
*       Output: 
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-10-10  a00900872       Create
*
*******************************************************************************/
ULONG TCPIP_CloseFib6TableByFilter(UINTPTR ulHandle);

/*******************************************************************************
*    Func Name: TCPIP_ShowFIB6ByVrf
*  Description: ��ʾָ��VRF6��FIB����
*       Output: 
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-10-25  wangjiaqi        Create the first version.
*
*******************************************************************************/
VOID TCPIP_ShowFIB6ByVrf(CHAR *pszVrfName);
/*******************************************************************************
*    Func Name: TCPIP_Reg_VpnFib6
* Date Created: 2013-12-05
*       Author: likaikun213099
*  Description: ע���Ʒ��ѯFIB6�ӿ�
*        Input: TCPIP_SEARCH_VPN_FIB6_FUN pfSearchFib6:���Ӻ���
*       Output: 
*       Return: �ɹ���VOS_OK
*               ʧ�ܣ�VOS_ERR
*      Caution: ��Ҫ��Э��ջ��ʼ��֮ǰע��
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-12-05   likaikun213099          Create
*
*******************************************************************************/
ULONG TCPIP_Reg_VpnFib6(TCPIP_SEARCH_VPN_FIB6_FUN pfSearchFib6);

#ifdef __cplusplus
}
#endif      /* end of _cplusplus        */

#endif      /* end of _SFIB6_API_H_    */


