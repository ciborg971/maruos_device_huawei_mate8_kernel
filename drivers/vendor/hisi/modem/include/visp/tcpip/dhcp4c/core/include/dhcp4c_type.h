/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              dhcp4c_type.h
*
*  Project Code: VISP1.5
*   Module Name: DHCP client Module
*  Date Created: 2004-05-19
*        Author: tangcongfeng(36956)
*   Description: ������DHCP�����õ����ݽṹ
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2004-05-19 tangcongfeng(36956)     Creat the first version.
*  2006-05-10  lu yao(60000758)       Ϊ֧��ARM CPU�ֽڶ������ԣ��޸Ľṹ��
*
*******************************************************************************/

#ifndef _DHCP4C_TYPE_H_
#define _DHCP4C_TYPE_H_



#ifdef  __cplusplus
extern "C"{
#endif

/* Header of DHCP packet */
typedef struct tagDHCP4C_PACKET_HEAD
{
    UCHAR               ucOp;                /* Message opcode/type */
    UCHAR               ucHtype;             /* Hardware addr type  */
    UCHAR               ucHlen;              /* Hardware addr length */
    UCHAR               ucHops;              /* Number of relay agent hops from client */
    ULONG               ulXid;               /* Transaction ID */
    USHORT              usSecs;              /* Seconds since clien t started looking */
    USHORT              usFlags;             /* Flag bits */
    ULONG               ulCiaddr;            /* Client address (if already in use) */
    ULONG               ulYiaddr;            /* 'your' (client) address */
    ULONG               ulSiaddr;            /* address of next server to use in DHCP */
    ULONG               ulGiaddr;            /* DHCP relay agent address */
    UCHAR               pucChaddr [DHCP4C_CHADDR_LEN];   /* Client hardware address */
    UCHAR               pcSname [DHCP4C_SNAME_LEN];      /* Optional server host name */
    UCHAR               pcFile [DHCP4C_FILE_LEN];        /* Boot filename */
} DHCP4C_PACKET_HEAD_S;



/*dhcp���������ṹDHCP4C_PACKET_S*/
typedef struct tagDHCP4C_PACKET
{
    DHCP4C_PACKET_HEAD_S * pstHead; /*DHCP����ͷ*/
    UCHAR *pucOptions; /* DHCP ѡ��*/
}DHCP4C_PACKET_S;

/* ��Ž���������Ϣ�ṹ */
typedef struct tagDHCP4C_PACKETINFO
{

    ULONG       ulXid;            /* Transaction ID */
    ULONG       ulCiaddr;         /* Client address (if already in use) */
    ULONG       ulYiaddr;         /* 'your' (client) address */
    ULONG       ulSiaddr;         /* address of next server to use in DHCP */
    ULONG       ulGiaddr;         /* DHCP relay agent address */
    UCHAR       pucChaddr [DHCP4C_CHADDR_LEN];         /* Client hardware address */
    ULONG       ulOptionOverload;                       /* options overload option */
    ULONG       ulMsgType;                              /* message type */
    ULONG       ulServerId;                             /* server identifier */
    ULONG       ulSubnetMask;                           /* subnet mask  */
    ULONG       ulRouter[DHCP4C_ROUTER_NUM];            /* router address */
    ULONG       ulDNSAddr[DHCP4C_DNSIP_NUM];            /* dns sever address */
    CHAR        pcDomain[DHCP4C_DOMAINNAME_SIZE];       /* domain name */
    ULONG       ulLeaseTime;                            /* address lease time */
    ULONG       ulRenewalTime;                          /* renewal time value */
    ULONG       ulRebingdingTime;                       /* Rebinding time value */
    UCHAR       ucOptionExistFlg[DHCP4C_MAX_OPTIONCODE]; /*��־ѡ����� */
    UCHAR       ucPadding;
}DHCP4C_PACKETINFO_S;

/* SESSION ���ƿ� */
typedef struct tagDHCP4C_SESSION
{
    DLL_NODE_S          stDLLNode; /* list node pointer,must be in first  position in this struct */
    ULONG               ulXID;              /* Transaction ID */
    ULONG               ulInterfaceIndexID; /* Interface Index ID */
    ULONG               ulInterfaceIPAddr;  /* interface address  */
    ULONG               ulInterfaceSubnetMask;    /* the interface's subnetmask  */
    ULONG               ulGatewayIPAddr[DHCP4C_ROUTER_NUM];      /* the Gatewey address */
    ULONG               ulDNSIPAddr[DHCP4C_DNSIP_NUM];           /* the Domain Nane Server's address */
    CHAR                pcDomainName[DHCP4C_DOMAINNAME_SIZE];   /* the Domain Name */
    ULONG               ulServerIdentifier;                      /* the DHCP server identifier */
    UCHAR               pucChaddr [DHCP4C_CHADDR_LEN];           /* client hardware address */
    ULONG               ulLeaseTime;      /* address lease time */
    ULONG               ulRenewTime;      /* renewal time value  */
    ULONG               ulRebindTime;     /* rebinding time value */
    ULONG               ulFSMState;       /* FSM state */
    ULONG               ulArpReqTimerID;         /* ARP REQ timer ID */
    ULONG               ulDiscoverTimerID;       /* Discover timer ID */
    ULONG               ulRequestTimerID;        /* Request timer ID */
    ULONG               ulRenewTimerID;          /* Renew timer ID */
    ULONG               ulRebindTimerID;         /* rebinding timer ID */
    ULONG               ulLeaseTimerID;          /* Lease timer ID */
    ULONG               ulLeaseTimeSince1970;    /* lease time in seconde since 1970/1/1 00:00:00*/
    ULONG               ulDebugFlag;             /* ���Կ��� */
    UCHAR               *pucSendBuf;             /* ����DHCP���Ļ��� */
    UCHAR               *pucOptionItem;          /* �û�����DHCPѡ���� */
    ULONG               ulMsgType;               /* message type */
    ULONG               ulSendBufLen;            /* DHCP ���ĳ��� */
    ULONG               ulMaxReSent;             /* ��¼�����ط����� */
    LONG                lSocketId;               /* SOCKET id */
    ULONG               ulRenewInterfaceFlag;    /* ��ʶ����״̬: DHCP4C_ISRENEWING, DHCP4C_RENEW_TIMOUT, DHCP4C_ISRELEASEING_BAK */                                                 
    ULONG               ulSmooth;                /* 1��δƽ����0���Ѿ�ƽ��*/
    UCHAR               aucSeverMac[MACADDRLEN];  /* Sever��physical��ַ */
    UCHAR               ucReserved[2];
    ULONG               ulCfgCheckTimerID;       /* �û����ü�� timer ID */
    UCHAR               *pucRecvBuf;             /*�������DHCP���Ļ��� */
    ULONG               ulRecvLen;               /*���յ�DHCP���ĳ���*/
    ULONG               ulCfgCheckResult;        /*�����û����ü����*/
    ULONG               ulOutIfIndex;            /* ��LoopBack�ӿ���ʹ��DHCPʱָ���ĳ��ӿ�,����֧��DHCP over IPSEC ����,
                                                    0:��ʾû��ָ�����ӿ�, ��0��ʾָ���ĳ��ӿ�����.������DHCP���ֶζ�Ϊ0,
                                                    ֻ����ָ�����ӿ�ʹ��LoopBack�ӿڵ�DHCPʱ���ֶβŷ�0. */
    DHCP4CSTATISTIC_S   stDhcp4cStatistic;       /* DHCP����ͳ�� */
}DHCP4C_SESSION_S;


typedef struct tagDHCP4C_DEBUGINFO
{
    DLL_NODE_S      stDLLNode;  /* list node pointer,must be in first  position in this struct */
    ULONG ulIfIndex;            /*Interface Index*/
    ULONG ulDebugFlag;          /* Debug flag */
}DHCP4C_DEBUGINFO_S;

/*Added by l60006581 for DHCP4C config, 2006-04-28 */
typedef struct tagDHCP4C_CONFIGINFO
{
    DLL_NODE_S      stDLLNode;  /* list node pointer,must be in first  position in this struct */
    ULONG  ulIfIndex;           /* Interface Index */
    ULONG  ulConfigFlag;        /* Config flag */
    ULONG  ulCiaddr;            /* Ciaddr option,������ */
    ULONG  ulCIDLen;            /* the length of configuration CID */
    ULONG  ulVSILen;            /* the length of configuration VSI */
    UCHAR  ucCID[DHCP4C_MAXCIDLEN];           /* CID option */
    UCHAR  ucVSI[DHCP4C_MAXVSILEN];           /* VSI option */
    ULONG ulDHCPDefaultIP;     /* Default address*/
    ULONG ulDHCPDefaultSubMask; /* Default sub mask */
    /* Added by y171195(z171897) 2010-11-03 for DHCP Vlan Scanning Begin */
    ULONG ulEnable;
    ULONG ulDelayTime;
    /* Added by y171195(z171897) 2010-11-03 for DHCP Vlan Scanning End */
}DHCP4C_CONFIGINFO_S;


#define     DLLNODE(x)      ((DHCP4C_SESSION_S *)(x))
#define     DLLNODEDEBUG(x)    ((DHCP4C_DEBUGINFO_S *)(x))
#define     DLLNODECONFIG(x)   ((DHCP4C_CONFIGINFO_S *)(x)) /*Added by l60006581 for DHCP4C config, 2006-04-28 */

/* �����ӿڵ�DHCP���ڽڵ� */
typedef struct tagDHCP4C_LEASE_NODE
{
    DLL_NODE_S stDLLNode;  /* list node pointer, must be in first position in this struct */
    DHCP4C_LEASE_S stLease; /* DHCP4C ���ڼ�¼ */
}DHCP4C_LEASE_NODE_S;

#pragma    pack( 1 )

typedef struct  tagDHCP_ETHERHDR
{
    UCHAR                   ucHdrDstMacAddr[6];     /*Ŀ��physical��ַ*/
    UCHAR                   ucHdrSrcMacAddr[6];     /*Դphysical��ַ  */
    USHORT                  usHdrType;              /*Э������   */
}DHCP_ETHERHDR_S;

#if (VOS_ARM == VOS_HARDWARE_PLATFORM)
#pragma pack(0)
#else
#pragma pack()
#endif


#ifdef  __cplusplus
}
#endif  /* end of __cplusplus */

#endif  /* end of _DHCP4C_TYPE_H_ */


