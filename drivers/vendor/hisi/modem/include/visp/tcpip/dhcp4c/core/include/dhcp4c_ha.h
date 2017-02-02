

#ifndef _DHCP4C_HA_H_
#define _DHCP4C_HA_H_

#ifdef  __cplusplus
extern  "C"{
#endif

#define DHCP4C_BOUND_BAK                   32    /* DHCP�Ự���ƿ鱸�� */
#define DHCP4C_UNBOUND_BAK                 33    /* ȥ��DHCP�Ự */
#define DHCP4C_FSM_IFDOWN_BAK              34    /* ��UP��DHCP�Ự���ƿ鱸�� */

#define DHCP4C_ENABLE_DHCP_FLAG_BAK        40    /*  ʹ��DHCP��õ�ַ���� */
#define DHCP4C_DISABLE_DHCP_FLAG_BAK       41    /*  ȥʹ��DHCP��õ�ַ���� */
#define DHCP4C_ISRENEW_BAK                 42    /*  ���»�ýӿڵ�DHCP��ַ */
#define DHCP4C_ISRELEASEING_BAK            0x08  /*  �ͷŽӿڵ�DHCP��ַ���� */

#define DHCP4C_CFG_ITEM_BAK                50    /*  DHCP���ÿ�ı��� */
#define DHCP4C_CFG_CIADDR_BAK              51    /*  DHCP��CIADDR�����ı��� */
#define DHCP4C_OPTION_DEL_BAK              52    /*  ɾ������ */

#define DHCP4C_OPTION_VSI_BAK              43    /* VIS�ı���ͷ����� */
#define DHCP4C_OPTION_CLIENTID_BAK         61    /* CID���ݵ�ͷ����� */

#define DHCP4C_IFNET_DOWN_BAK              70    /* �ӿ�down�¼��ı��� */
#define DHCP4C_IFNET_DELETE_BAK            71    /*�ӿ�ɾ���ı���*/

/*added by luogaowei 2007-7-26*/
#define DHCP4C_CFG_DEFAULTIP_SET_BAK       80    /* ����DHCPĬ�ϵ�ַ */
#define DHCP4C_CFG_DEFAULTIP_DEL_BAK       81    /* ɾ��DHCPĬ�ϵ�ַ */

#define DHCP4C_CONFIG_LIST                 1     /*  �������� */
#define DHCP4C_SESSION_LIST                2     /*  �Ự���� */

#define DHCP4C_BAK_VIRTUAL                 0x80

#define DHCP4C_BAK_GLOBALCFG               0x81  /* ȫ��������Ϣ���ݲ���,ha����ͷ�����ֶ� */

enum enumDHCP4CNEWBAKMsgType  /*�µ�DHCP HAͷ��Ϣ����,ռ�����ֽ�*/
{
    DHCP4C_NEWBAK_VIRTUAL_INFO = 0X0100,/*VISPV1R7�����ı���������ֵ��0X0100��ʼ,ǰ���ֵԤ����VISPV1R6*/
    DHCP4C_DNS_BAK_INFO_CODE = 0X0101,
    DHCP4C_GATEWAYIP_BAK_INFO_CODE = 0x0102,
    DHCP4C_DOMAIN_BAK_INFO_CODE = 0x0103,
    
    DHCP4C_GLOBALCFG_BAK = 0x0200,     /* dhcp4cȫ��������Ϣ����             */
    DHCP4C_GLOBALCFG_BAK_TOS,          /* ��tlv��tosֵ����                   */
    DHCP4C_GLOBALCFG_BAK_IGNOREOPTION, /* ��TLV���Ƿ����50/55/57ѡ����    */
    DHCP4C_GLOBALCFG_BAK_END,          /* ����Ҫ�ڴ�ǰ���ȫ��������Ϣtlv    */

    DHCP4C_ENABLERMT_OUTIF_BAK = 0x0300,    /* ָ�����ӿ�ʹ��DHCPʱ���ݳ��ӿ���Ϣ */
};

#ifndef DHCP4C_HA_CAL_CFG_SIZE
#define DHCP4C_HA_CAL_CFG_SIZE(ulCIDLen, ulVSILen) \
             (ulCIDLen + ulVSILen + ((4 - (ulCIDLen + ulVSILen) % 4))%4)
#endif

/* ʹ��DHCPʱ��Ҫ���ݵ���Ϣ */
typedef struct tagDHCP4C_ENABLEPARA
{
    ULONG  ulFlag;         /* DHCPʹ�ܱ�־ */
    ULONG  ulOutIfIndex;   /* DHCPʹ��ʱָ���ĳ��ӿ����� */
}DHCP4C_ENABLEPARA_S;

typedef struct tagDHCP4C_PACKET_HEAD_BAK
{
    USHORT usType;                 /* ������Ϣ������ */
    USHORT usLen;                  /* ������Ϣ����ܳ��� */
    ULONG  ulIfIndex;              /* ���ÿ������Ľӿ����� */
    ULONG  ulExtend;               /*  ��չ�ֶ�*/
}DHCP4C_PACKET_HEAD_BAK_S;

typedef struct tagDHCP4C_FSM_IFDOWN_BAK
{
    USHORT usType;                         /* ������Ϣ������ */
    USHORT usLen;                          /* ������Ϣ����ܳ��� */
    ULONG  ulIfIndex;                      /* ���ÿ������Ľӿ����� */
    ULONG  ulInterfaceIPAddr;              /* interface address  */
    ULONG  ulLeaseTimeSince1970;           /* lease time in seconde since 1970/1/1 00:00:00*/
    UCHAR  pucChaddr [DHCP4C_CHADDR_LEN];  /* Ӳ����ַ */
}DHCP4C_FSM_IFDOWN_BAK_S;

typedef struct tagDHCP4C_UP_HEAD_BAK
{
    USHORT  usType;              /* ������Ϣ������ */
    USHORT  usLen;              /* ������Ϣ����ܳ��� */
    ULONG   ulXID;              /* Transaction ID */
    ULONG   ulInterfaceIndexID; /* Interface Index ID */
    ULONG   ulInterfaceIPAddr;  /* interface address  */
    ULONG   ulInterfaceSubnetMask;    /* the interface's subnetmask  */
    ULONG   ulGatewayIPAddr[DHCP4C_ROUTER_NUM];      /* the Gatewey address */
    ULONG   ulDNSIPAddr[DHCP4C_DNSIP_NUM];/* the Domain Nane Server's address */
    CHAR    pcDomainName[DHCP4C_DOMAINNAME_SIZE];   /* the Domain Name */
    ULONG   ulServerIdentifier;                      /* the DHCP server identifier */
    UCHAR   pucChaddr [DHCP4C_CHADDR_LEN];           /* client hardware address */
    ULONG   ulLeaseTime;      /* address lease time */
    ULONG   ulRenewTime;      /* renewal time value  */
    ULONG   ulRebindTime;     /* rebinding time value */
    ULONG   ulFSMState;       /* FSM state */    
}DHCP4C_UP_HEAD_BAK_S;

typedef struct tagDHCP4C_CFG_NODE_BAK
{
    USHORT  usType;              /* ������Ϣ������ */
    USHORT  usLen;              /* ������Ϣ����ܳ��� */
    ULONG    ulIfIndex;           /* ���ÿ������Ľӿ����� */
    ULONG    ulConfigFlag;        /* ���õı�� */
    ULONG    ulCiaddr;            /* ���õ�Ciaddr ֵ */
    ULONG    ulCIDLen;            /* ���õ�CIDֵ���� */  
    ULONG    ulVSILen;            /* ���õ�VSIֵ���� */
    ULONG ulDHCPDefaultIP;     /* Default address*/
    ULONG ulDHCPDefaultSubMask; /* Default sub mask */
}DHCP4C_CFG_NODE_BAK_S;


typedef struct tagDHCP4C_HA_HEAD_BAK
{
    USHORT usType;                         
    USHORT usLen;                          
}DHCP4C_HA_HEAD_BAK_S;

typedef struct tagDHCP4C_HA_VIRTUAL_INFO_BAK
{
    ULONG ulIfIndex;                         
    ULONG ulDHCPClientIP;
    ULONG ulDHCPClientIPMask;
    ULONG ulFlag;    
}DHCP4C_HA_VIRTUAL_INFO_S;

typedef struct tagDHCP4C_DNSTLV_BAK
{
    USHORT usType;
    USHORT usLen;
    ULONG aulDNSIP[DHCP4C_DNSIP_NUM];  
}DHCP4C_DNSTLV_BAK_S;

typedef struct tagDHCP4C_GATEWAYIPTLV_BAK
{
    USHORT usType;
    USHORT usLen;
    ULONG aulGatewayIP[DHCP4C_ROUTER_NUM];
}DHCP4C_GATEWAYIPTLV_BAK_S;

typedef struct tagDHCP4C_DOMAINTLV_BAK
{
    USHORT usType;
    USHORT usLen;
    UCHAR ucDomainName[DHCP4C_DOMAINNAME_SIZE];
}DHCP4C_DOMAINTLV_BAK_S;

typedef struct tagDHCP4C_TLV_HEAD_BAK
{
    USHORT usType;
    USHORT usLen;
}DHCP4C_TLV_HEAD_BAK_S;

typedef struct tagDHCP4C_TOSTLV_BAK
{
    DHCP4C_TLV_HEAD_BAK_S stTlvHdr;
    UCHAR  ucTos;
    UCHAR  ucPad[3];
}DHCP4C_TOSTLV_BAK_S;

typedef struct tagDHCP4C_IGNOREOPTION_BAK
{
    DHCP4C_TLV_HEAD_BAK_S stTlvHdr;
    ULONG  ulIgnoreOption;
}DHCP4C_IGNOREOPTION_BAK_S;

/* ����HA���ĵ�ͷ(�ⲿ����) */
#define HA_DHCP4C_BAK_SESS_SET(pstUpSession, pstSession)\
{\
    pstUpSession->ulXID = pstSession->ulXID;\
    pstUpSession->ulInterfaceIndexID = pstSession->ulInterfaceIndexID;\
    pstUpSession->ulInterfaceIPAddr = pstSession->ulInterfaceIPAddr;\
    pstUpSession->ulInterfaceSubnetMask = pstSession->ulInterfaceSubnetMask;\
    (VOID)TCPIP_Mem_Copy(pstUpSession->ulGatewayIPAddr, DHCP4C_ROUTER_NUM * sizeof(ULONG), pstSession->ulGatewayIPAddr, DHCP4C_ROUTER_NUM * sizeof(ULONG));\
    (VOID)TCPIP_Mem_Copy(pstUpSession->ulDNSIPAddr, DHCP4C_DNSIP_NUM * sizeof(ULONG), pstSession->ulDNSIPAddr, DHCP4C_DNSIP_NUM * sizeof(ULONG));\
    (VOID)TCPIP_Mem_Copy(pstUpSession->pcDomainName, DHCP4C_DOMAINNAME_SIZE, pstSession->pcDomainName, DHCP4C_DOMAINNAME_SIZE);\
    pstUpSession->ulServerIdentifier = pstSession->ulServerIdentifier;\
    (VOID)TCPIP_Mem_Copy(pstUpSession->pucChaddr, DHCP4C_CHADDR_LEN, pstSession->pucChaddr, DHCP4C_CHADDR_LEN);\
    pstUpSession->ulLeaseTime = pstSession->ulLeaseTime;\
    pstUpSession->ulRenewTime = pstSession->ulRenewTime;\
    pstUpSession->ulRebindTime = pstSession->ulRebindTime;\
    pstUpSession->ulFSMState = pstSession->ulFSMState;\
}

ULONG DHCP4C_HA_VirtualCfgInput(UCHAR *pucBuf, USHORT usDataLen);
ULONG DHCP4C_HA_SendVirtualInfo(IFNET_S *pstIf);
ULONG DHCP4C_HA_BuildOnePacket(USHORT usType, ULONG ulIfIndex, UCHAR *pucData, UCHAR *pucInBuf, USHORT usInBufLen);
ULONG DHCP4C_HA_SendPacket(UCHAR * pucData, USHORT usDataLen);
VOID DHCP4C_HA_ReleaseDhcpFlag(ULONG ulIndex, ULONG usFlag);
ULONG DHCP4C_HA_BatchBackup();
ULONG DHCP4C_HA_Input(UCHAR *pucInBuf, USHORT usDataLen);
ULONG DHCP4C_HA_Smooth();
ULONG DHCP4C_HA_BuildSendOnePacket(USHORT usType, ULONG ulIfIndex, UCHAR * pucData, USHORT usInBufLen);
ULONG TCPIP_HA_SetDhcpDbg(ULONG ulDbg);
ULONG DHCP4C_HA_CheckEnableDhcp(ULONG ulIfIndex);
ULONG DHCP4C_HA_GetDhcpDbg(ULONG *pulDbg);
VOID *DHCP4C_GetNext(VOID *pCur,VOID **ppNext);
ULONG DHCP4C_OpenEntry (UINTPTR *pulWaitListHandle, ULONG ulWaitId);
ULONG DHCP4C_GetEntry (UINTPTR ulEntryWaitList, UCHAR *ucData, ULONG ulDataSize, ULONG ulType);
ULONG DHCP4C_CloseObject (UINTPTR ulWaitListHandle);
DHCP4C_SESSION_S *DHCP4C_HA_CreateAtSlave (ULONG ulIfIndex);
ULONG DHCP4C_HA_CreateSocketAtSlave (VOID);
ULONG DHCP4C_HA_GetDhcp4cVerboseDbg (ULONG *pulDbg);
ULONG DHCP4C_HA_SetDhcp4cVerboseDbg(ULONG ulDbg);
VOID DHCP4C_HA_DebugOutPut(UCHAR *pBuf,ULONG ulMsgLen,ULONG ulCmd);
ULONG DHCP4C_HA_Clean(VOID);
ULONG DHCP4C_HA_GlobalCfg_BackUp(ULONG ulBakType);
ULONG DHCP4C_HA_GlobalCfg_Input(UCHAR *pucData, ULONG ulDataLen);

#ifdef  __cplusplus
}
#endif

#endif

