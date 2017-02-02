/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              dhcp4c_api.h
*
*  Project Code: VISPV1R7
*   Module Name: dhcpc
*  Date Created: 2008-03-07
*        Author: wuhailan
*   Description: dhcpc�û�API�ӿ��ļ�
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-03-07   wuhailan                Create
*
*******************************************************************************/
#ifndef _DHCP4C_API_H_
#define _DHCP4C_API_H_


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#ifndef DNS_DOMAIN_LIST_NAME_LENGTH
#define DNS_DOMAIN_LIST_NAME_LENGTH 20
#endif

#define DHCP4C_DOMAINNAME_SIZE DNS_DOMAIN_LIST_NAME_LENGTH
#define DHCP4C_DNSIP_NUM       6 /* dns server ��ַ���� */
#define DHCP4C_ROUTER_NUM      8 /* router list number */

#define DHCP4C_MINCIDLEN       2
#define DHCP4C_MAXCIDLEN       256
#define DHCP4C_MINVSILEN       1
#define DHCP4C_MAXVSILEN       256

/* DHCP���ݰ���option��ѡ�����,������ʱ������ */
#define DHCP4C_OPTION_PAD                                 0
#define DHCP4C_OPTION_END                                 255
#define DHCP4C_OPTION_CLIENTID                            61
#define DHCP4C_OPTION_SERVERID                            54
#define DHCP4C_OPTION_SUBNET_MASK                         1
#define DHCP4C_OPTION_ROUTER                              3
#define DHCP4C_OPTION_DNS                                 6
#define DHCP4C_OPTION_DOMAIN_NAME                         15
#define DHCP4C_OPTION_REQUESTED_IP                        50
#define DHCP4C_OPTION_OVERLOAD                            52
#define DHCP4C_OPTION_MESSAGE_TYPE                        53
#define DHCP4C_OPTION_LEASE_TIME                          51
#define DHCP4C_OPTION_RENEWAL_TIME                        58
#define DHCP4C_OPTION_REBINDING_TIME                      59
#define DHCP4C_OPTION_PARAMETEREQLIST                     55
#define DHCP4C_OPTION_MAXMSG_SIZE                         57
#define DHCP4C_OPTION_VSI                                 43

/* Added by likaikun00213099 2014-02-11 for DHCP client packet check */
#define DHCP4C_FSM_MAX               11
/* End of Added by likaikun00213099 2014-02-11 for DHCP client packet check */

/* FSM ״̬*/
#define DHCP4C_FSM_IFDOWN         0
#define DHCP4C_FSM_INIT           1
#define DHCP4C_FSM_INIT_REBOOT    2
#define DHCP4C_FSM_REBOOTING      3
#define DHCP4C_FSM_SELECTING      4
#define DHCP4C_FSM_REQUESTING     5
#define DHCP4C_FSM_BOUND          6
#define DHCP4C_FSM_REBINDING      7
#define DHCP4C_FSM_RENEWING       8
#define DHCP4C_FSM_HALFBOUND      9
#define DHCP4C_FSM_WAIT_CONFCHECK   10  /*�û����ü��״̬*/

/*dhcp���ݰ�������*/
#define DHCP4C_DHCPDISCOVER          1
#define DHCP4C_DHCPOFFER             2
#define DHCP4C_DHCPREQUEST           3
#define DHCP4C_DHCPDECLINE           4
#define DHCP4C_DHCPACK               5
#define DHCP4C_DHCPNAK               6
#define DHCP4C_DHCPRELEASE           7
#define DHCP4C_DHCPINFORM            8


/* DEBUG �꿪�ض��� */
#define DHCP4C_DEBUG_FLAG_PACKET        0x01
#define DHCP4C_DEBUG_FLAG_EVENT         0x02
#define DHCP4C_DEBUG_FLAG_ERROR         0x04
#define DHCP4C_DEBUG_FLAG_ALL           0x07

#define DHCP4C_CHADDR_LEN   16

#ifndef IF_MAX_INTERFACE_NAME_LEN
#define IF_MAX_INTERFACE_NAME_LEN 47       /* ���ӿ������� */
#endif

/* ����/ˢ��DHCP���ڼ�¼ */
#define DHCP4C_ADD_LEASE  0
/* ɾ��DHCP���ڼ�¼ */
#define DHCP4C_DEL_LEASE  1

#define DHCP4C_PKTHOOK_SUCCESS_MODIFY       0
#define DHCP4C_PKTHOOK_NOT_MODIFY           1
#define DHCP4C_PKTHOOK_FAIL_MODIFY          2

/* Added by y171195(z171897) 2010-11-03 for DHCP Vlan Scanning Begin */
/* ȥʹ��DHCP VLAN Scaning���� */
#define DHCP4C_VLAN_SCANNING_DISABLE        0
/* ʹ��DHCP VLAN Scaning���� */
#define DHCP4C_VLAN_SCANNING_ENABLE         1
/* DHCP VLAN Scaning�����ӳ�ʱ�����ֵ1h=3600*1000ms */
#define DHCP4C_VLAN_SCANNING_MAX_DELAYTIME  3600000
/* Added by y171195(z171897) 2010-11-03 for DHCP Vlan Scanning End */

typedef struct tagDhcp4cStatistic
{
    /* Э��ͳ����Ϣ  ����*/
    ULONG ulInDhcpOffer;        /* DHCP4C_DHCPOFFER 2 */
    ULONG ulInDhcpAck;          /* DHCP4C_DHCPACK 5 */
    ULONG ulInDhcpNak;          /* DHCP4C_DHCPNAK 6 */
    ULONG ulInDhcpInform;       /* DHCP4C_DHCPINFORM 8 */
    ULONG ulInErr;              /* DHCP4C ����ͳ��*/

    /* Э��ͳ����Ϣ  ����*/
    ULONG ulOutDhcpDiscover;    /* DHCP4C_DHCPDISCOVER 1 */
    ULONG ulOutDhcpReqest;      /* DHCP4C_DHCPREQUEST 3 */
    ULONG ulOutDhcpDecline;     /* DHCP4C_DHCPDECLINE 4 */
    ULONG ulOutDhcpRelease;     /* DHCP4C_DHCPRELEASE 7 */
} DHCP4CSTATISTIC_S;

typedef struct tagDHCP4C_FSM_SELECT
{
    ULONG ulPacketLen;
    UCHAR  *pOfferPacket;     /* ѡ���Server��Offer����*/
}DHCP4C_FSM_SELECT_S;

typedef struct tagDHCP4C_PROC_HOOK
{
    UCHAR *pucUdpBuf;   /* ��ű��ĵĻ�����ָ�� */
    ULONG ulRecvLen;    /* ���յı��ĳ��� */
    USHORT usVlanInfo;  /* vlan��Ϣ */
    USHORT usRes;       /* �����ֶ� */
}DHCP4C_PROC_HOOK_S;

typedef struct tagDHCP4C_DISPLAYINFO
{
    ULONG            ulIfIndex;               /* �ӿ�����*/
    ULONG            ulIpAddr;                /* ��ַ */
    ULONG            ulInterfaceSubnetMask;   /* �������� */
    CHAR             szDnsSuffix[DHCP4C_DOMAINNAME_SIZE];   /* domain name */
    ULONG            ulDNSIPAddr[DHCP4C_DNSIP_NUM];          /* ���ֽ�����������ַ */
    ULONG            ulGatewayIPAddr[DHCP4C_ROUTER_NUM];     /* ���ص�ַ */
    ULONG            ulLeaseTime;                            /* address lease time */
    ULONG            ulOutIfIndex;            /* ʹ��DHCPʱָ���ĳ��ӿ�����, 0��ʾû��ָ�����ӿ� */
}DHCP4C_DISPLAYINFO_S;

/*DHCP4c ���õ���Ϣ����Ҫ�ǹ��ⲿ�ӿڻ�ȡDHCP ����Ϣ*/
typedef struct tagDHCP4C_OPTIONINFO
{
    ULONG  ulCiaddr;                          /* Ciaddr option */
    ULONG  ulCIDLen;                          /* the length of configuration CID */
    ULONG  ulVSILen;                          /* the length of configuration VSI */
    UCHAR  ucCID[DHCP4C_MAXCIDLEN];           /* CID option */
    UCHAR  ucVSI[DHCP4C_MAXVSILEN];           /* VSI option */
}DHCP4C_OPTIONINFO_S;

/* �����ӿڵ�DHCP�����ļ����ݶ��� */
typedef struct tagDHCP4C_LEASE
{
    CHAR  if_szIfName[IF_MAX_INTERFACE_NAME_LEN+1]; /*�ӿ������ؼ��ֶ�*/
    UCHAR pucChaddr[DHCP4C_CHADDR_LEN];   /* physical��ַ */
    UCHAR ucEnableFlag;      /* DHCPʹ�ܱ�־ */
    UCHAR ucPriority;        /* ��ַ���ȼ� */
    UCHAR ucPadding[2];
    ULONG ulInterfaceIPAddr; /* �ӿڵ�ַ�������� */
    ULONG ulSecond1970;      /* ���ڽ���ʱ����1970/1/1-00:00:00����������*/
}DHCP4C_LEASE_S;

/* DHCP4Cͳ����Ϣ */
typedef struct tagDHCP4C_Statistic
{
    /* Э��ͳ����Ϣ  ����*/
    ULONG ulInDhcpOffer;        /* DHCP4C_DHCPOFFER     */
    ULONG ulInDhcpAck;          /* DHCP4C_DHCPACK       */
    ULONG ulInDhcpNak;          /* DHCP4C_DHCPNAK       */
    ULONG ulInErr;              /* DHCP4C ����ͳ��      */

    /* Э��ͳ����Ϣ  ����*/
    ULONG ulOutDhcpDiscover;    /* DHCP4C_DHCPDISCOVER  */
    ULONG ulOutDhcpReqest;      /* DHCP4C_DHCPREQUEST   */
    ULONG ulOutDhcpDecline;     /* DHCP4C_DHCPDECLINE   */
    ULONG ulOutDhcpRelease;     /* DHCP4C_DHCPRELEASE   */
} DHCP4C_STATISTIC_S;

/*DHCP4cģ�������*/
enum tagDHCP_ErrCode
{
    DHCP4C_SUCCESS = 0,
    DHCP4C_FAILURE,

    DHCP4C_CONFIGERR_INDEX,     /*2 ��Ч�Ľӿ�����(�޶�Ӧ�ӿ�) */
    DHCP4C_CONFIGERR_MEMORY,    /*3 �ڴ����ʧ��(�ڴ治��) */
    DHCP4C_CONFIGERR_LEN,       /*4 ������ȴ���  */
    DHCP4C_CONFIGERR_VAL,       /*5 ������ֵ����    */
    DHCP4C_CONFIGERR_CODE,      /*6 ������code����  */
    DHCP4C_CONFIGERR_INTER,     /*7 ָ���Ľӿ����ʹ��� */
    DHCP4C_CONFIGERR_DBGTYPE,   /*8 ָ����Debug���ʹ��� */
    DHCP4C_CONFIGERR_DISABLE,   /*9 ָ���Ľӿ�û��ʹ��DHCP */

    DHCP4C_WRONGFLAG_PPP,       /*10 ��PPP��ʹ��DHCP, û��ʹ��DHCP��ַ�����ȼ����ڽӿڵ�ַ���ȼ��ı�־ */
    DHCP4C_REQFLAG_WRONG,       /*11 ʹ��DHCP�ı�־λ���� */
    DHCP4C_REENABLEFLAG_WRONG,  /*12 �ظ�ʹ��DHCP��־λ����,ֻ����ʹ��ͬ���ı�־λʹ��DHCP */

    DHCP4C_HA_IS_SMOOTHING,     /*13 HA����ƽ��������ֶ���������ʱ���û��������ӿڣ��򷵻ش˴����� */
    DHCP4C_CONFIGERR_SUBTRUNK,  /*14 TRUNK�ӽӿڽ��в���*/
    DHCP4C_CONFIGERR_CFGDHCPIP, /*15 ����DHCP ��ַʧ��*/
    DHCP4C_CONFIGERR_WRITEQUE,  /*16 д����ʧ��*/
    DHCP4C_PARA_ERR,            /*17 ��������*/
    DHCP4C_STOP_FAILURE,        /*18 dhcp4c_stop failure        */
    DHCP4C_AM4_CFG_ERR,         /*19 IP_AM4_CfgProcIpAddrDhcp return err  */
    DHCP4C_ALREADY_ENABLE_DHCP, /*20 �Ѿ�ʹ����DHCP*/
    DHCP4C_CONFIGERR_IPIFNET,   /*21 �ӿڻ�ȡ������ȷ��IP���ƿ�*/
    DHCP4C_CONFIGERR_NULLPOINTER,/*22����ָ��Ϊ��*/
    DHCP4C_CONFIGERR_DBGNO,     /*23 ָ����debug����ֵ����ȷ*/
    DHCP4C_INVALID_IPADDRESS,   /*24 ���صĵ�ַ��Ч*/
    DHCP4C_CONFIGNODE_NOTEXIST, /*25 �����ڴ����ý��*/

    DHCP4C_API_COM_NULL,        /*26 dhcp4c���Ϊ��*/
    DHCP4C_API_PARA_WRONG,      /*27 �����������*/
    DHCP4C_API_GET_INFO_FAIL,   /*28 ��ȡ��ʾ��Ϣʧ��*/
    DHCP4C_NOT_3D_MODE,         /*29 ����ά�ӿ�ģʽ*/
    DHCP4C_NULLPOINTER,         /*30 ����ָ��Ϊ��*/
    DHCP4C_IP_ADDR_WRONG,       /*31 ��ַ�Ƿ�*/
    DHCP4C_VIRTUAL_IFNET,       /*32 �Ǳ���ӿ�*/
    DHCP4C_TASKRAP_NULL_IFNET,  /*33 ������ռ���½ӿ�Ϊ��*/
    DHCP4C_WRITE_LEASE_NULL,    /*34 дDHCP�����ļ��Ĺ��Ӻ���Ϊ��*/
    DHCP4C_READ_LEASE_NULL,     /*35 ��DHCP�����ļ��Ĺ��Ӻ���Ϊ��*/
    DHCP4C_INT_NOTL3ETH,        /*36 ����˿ڲ�֧��Dhcp*/
    DHCP4C_ISVLANIF,            /*37 �ӿ���VLANIF */
    /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
    DHCP4C_VRF_NOT_SUPPORT,     /*38 �ýӿ����ڵ�VRFʵ����֧��DHCP*/
    /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
    DHCP4C_REG_UNREG_FAIL,      /*39 DHCPע���ȥע��ʧ��*/
    DHCP4C_CONFIGERR_LOOPBACKIF_INDEX,  /* 40 ֧��DHCP OVER IPSECʱ,ʹ��DHCPʱ�����LoopBack�ӿ������������Ϸ� */
    DHCP4C_CONFIGERR_NOT_LOOPBACK,      /* 41 ֧��DHCP OVER IPSECʱ,ʹ��DHCPʱ�����LoopBack�ӿ�������������LoopBack���� */
    DHCP4C_CONFIGERR_OUTIF_INDEX,       /* 42 ֧��DHCP OVER IPSECʱ,ʹ��DHCPʱ����ĳ��ӿ������������Ϸ� */
    DHCP4C_VIRTUAL_OUTIFNET,            /* 43 ֧��DHCP OVER IPSECʱ,ʹ��DHCPʱ����ĳ��ӿ��������Ϸ�,���Ǳ���ӿ� */
    DHCP4C_OUTIFNET_NOTL3ETH,           /* 44 ֧��DHCP OVER IPSECʱ,ʹ��DHCPʱ����ĳ��ӿ��������Ϸ�,��������ӿ� */
    DHCP4C_OUTIFNET_ISVLANIF,           /* 45 ֧��DHCP OVER IPSECʱ,ʹ��DHCPʱ����ĳ��ӿ��������Ϸ�,��VLAN�ӿ� */
    DHCP4C_CONFIGERR_SUBTRUNK_OUTIFNET, /* 46 ֧��DHCP OVER IPSECʱ,ʹ��DHCPʱ����ĳ��ӿ��������Ϸ�,��TRUNK��Ա�ӿ� */
    DHCP4C_CONFIGERR_INTER_OUTIFNET,    /* 47 ֧��DHCP OVER IPSECʱ,ʹ��DHCPʱ����ĳ��ӿ��������Ϸ�,����ETH,TRUNK�ӿ� */
    DHCP4C_CONFIGERR_VLANSCANNING_NOTENABLE,/* 48 ȥʹ��DHCP VLAN Scaning����ʱ,DHCP VLAN Scaning����δʹ�� */
    DHCP4C_CONFIGERR_VLANSCANNING_DELAYTIME_OVERFLOW,/* 49 ʹ��DHCP VLAN Scaning����ʱ,������ʱʱ�䳬���趨�����ֵ(1h) */
    DHCP4C_CONFIGERR_IP_ALREADY,  /* 50 ���/ɾ��IP�ظ����� */
    DHCP4C_ERR_MAX
};

/*Modified by zhongyu206043, �޸Ĳ���Ϊ�ṹ��DHCP4C_PROC_HOOK_S  for S.DHCP.1.1, 2012/8/18 */
typedef ULONG (*TCPIP_PROCDHCP_HOOK_FUNC)(DHCP4C_PROC_HOOK_S *pInfo);
/*End of Modified by zhongyu206043, 2012/8/18 */

/* ע���ȡDHCP��Ϣ���Ӻ��� */
typedef ULONG ( * GET_DHCP_CLIENT_IP_HOOK_FUN) ( ULONG ulIfIndex,
                                                        ULONG ulDHCPClientIP,
                                                        ULONG ulDHCPClientIPMask,
                                                        ULONG aulDNSIP[DHCP4C_DNSIP_NUM],
                                                        ULONG aulGatewayIP[DHCP4C_ROUTER_NUM],
                                                        CHAR pcDomainName[DHCP4C_DOMAINNAME_SIZE],
                                                        ULONG ulFlag
                                                        );

/* ע���ȡDHCP Server IP��Ϣ���Ӻ��� */
typedef ULONG (* GET_DHCP_SERVER_IP_HOOK_FUN) (ULONG ulIfIndex,
                                                      ULONG ulDHCPServerIP,
                                                      ULONG ulFlag
                                                     );

/* ע�����DHCPѡ��Ӻ��� */
typedef ULONG (*gpfDHCPADDOPTION_HOOK_FUNC)(ULONG ulIfIndex ,ULONG ulMessageType,
                                            ULONG ulFSMState,ULONG  ulMaxLen,
                                            UCHAR *pucOptionItem,ULONG *pulLen);
/* ��ȡDHCP�����ļ��Ĺ��Ӻ���ԭ��
   DHCP4C_LEASE_S **ppstLease: �����߷��صĴ�����ڼ�¼���ڴ��׵�ַָ��, �ڴ��ɵ���������, VISP�ͷ�
   ULONG *pulLeaseNum: �����߷��ص����ڼ�¼���� */
typedef ULONG (*LEASE_READ_HOOK)(DHCP4C_LEASE_S **ppstLease, ULONG *pulLeaseNum);

/* дDHCP�����ļ��Ĺ��Ӻ���ԭ��
   ULONG ulDelFlag: Ϊ0��ʾд���¼, ������ڽӿ�����ͬ�ļ�¼���串��; Ϊ1��ʾɾ���ӿ�����ͬ�ļ�¼
   DHCP4C_LEASE_S *pstLease: ���ڼ�¼ָ��, ָ����ڴ���VISP�������ͷ� */
typedef ULONG (*LEASE_WRITE_HOOK)(ULONG ulDelFlag, DHCP4C_LEASE_S *pstLease);

/*VISP�������ü��ص�����ע�ṳ��
����Ʒ�ڸ����ü��ص�����������ʵ�����ü������첽���ü���֪ͨ)*/
typedef ULONG (*TCPIP_PROCDHCP_CONF_CHECK_HOOK_FUNC) (
                                                        UCHAR *pucUdpBuf,
                                                        ULONG ulRecvLen,
                                                        ULONG ulIfIndex,
                                                        ULONG ulCorrelator);
/*���ü��ע������ṹ*/
typedef struct tagDHCP4C_CONF_CHECK_HOOK
{
    ULONG ulIfIndex;    /*��Ҫ�����ü��Ľӿ�*/
    ULONG ulCorrelator; /*���ü�������,VISP���ò�Ʒ���ü��ص�����ʱ������Ʒ�ġ�*/
    ULONG ulCheckResult;    /*��Ʒ���������ý����VISP����DHCPDECLINE�����н��ý����Ϊѡ�����DHCP��������*/
    TCPIP_PROCDHCP_CONF_CHECK_HOOK_FUNC pfCfgCheckHookFunc; /*���ü�⺯��*/
    struct tagDHCP4C_CONF_CHECK_HOOK *pstNext;
}DHCP4C_CONF_CHECK_HOOK_S;


/* ���������Ӻ�������ԴIP���� */
typedef struct tagTCPIP_PROCDHCP_UNICAST_HOOK_FUNC
{
    ULONG (*pfTCPIP_ProcdhcpcUnicastOut)(ULONG ulIfIndex,
                                ULONG *pulDhcpServerAddr,
                                   ULONG *pulDhcpSrcAddr,
                                        UCHAR *pucUdpBuf,
                                        ULONG ulSendLen);

    ULONG (*pfTCPIP_ProcdhcpcUnicastIn)(ULONG ulIfIndex,
                                       UCHAR *pucUdpBuf,
                                       ULONG ulRecvLen);
}TCPIP_PROCDHCP_UNICAST_HOOK_FUNC;

/* Added by y171195(z171897) 2010-11-03 for DHCP Vlan Scanning Begin */
/* DHCP offer����vlan��Ϣ����֪ͨ�ص�����ԭ��
*  ULONG ulIfIndex: �ӿ�����
*  USHORT usVlanInfo: VLAN��Ϣ,����tag,���ȼ�,VLANID.(������)
*/
typedef VOID (*DHCP_VLAN_NOTIFY_HOOK)(ULONG ulIfIndex, USHORT usVlanInfo);
/* Added by y171195(z171897) 2010-11-03 for DHCP Vlan Scanning End */

/* Added by likaikun00213099 2014-02-11 for DHCP client packet check */
typedef struct tagDHCP4C_PROC_VALID_HOOK
{
    UCHAR *pucUdpBuf;   /* DHCP���ģ���UDP�ײ� */
    ULONG ulRecvLen;    /* ���ĳ��� */
    ULONG ulMsgType;    /* ��������(��ǰ�汾��֧��Offer��ACK)
                            #define DHCP4C_DHCPDISCOVER          1
                            #define DHCP4C_DHCPOFFER             2
                            #define DHCP4C_DHCPREQUEST           3
                            #define DHCP4C_DHCPDECLINE           4
                            #define DHCP4C_DHCPACK               5
                            #define DHCP4C_DHCPNAK               6
                            #define DHCP4C_DHCPRELEASE           7
                            #define DHCP4C_DHCPINFORM            8*/
    USHORT usVlanInfo;  /* vlan ��Ϣ*/
    USHORT usRes;       /* �����ֶ� */
}DHCP4C_PROC_VALID_HOOK_S;
typedef ULONG (*TCPIP_PROC_VALID_DHCP_HOOK_FUNC)(DHCP4C_PROC_VALID_HOOK_S *pInfo);
/* End of Added by likaikun00213099 2014-02-11 for DHCP client packet check */

/*******************************************************************************
*    Func Name: TCPIP_GetDhcp4cStatics
* Date Created: 2012-08-17
*       Author: zhongyu206043
*  Description: ��ȡDHCP��Э��ͳ����Ϣ��
*        Input: ULONG ulIfIndex:
*               DHCP4CSTATISTIC_S * pstStat:����DHCP�Ľӿ�����
*       Output: pstStat��ָ��ṹ��DHCP4CSTATISTIC_S
*                        ��ָ�롣����ָ����ڴ����û�����������ͷš�
*       Return: VOS_OK           �ɹ�
*               ����             ʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-08-17   zhongyu206043           Create for S.DHCP.1.1
*
*******************************************************************************/
extern ULONG TCPIP_GetDhcp4cStatics(ULONG ulIfIndex,DHCP4CSTATISTIC_S * pstStat);

/*******************************************************************************
*    Func Name: TCPIP_DhcpcDoFsmSelecting
* Date Created: 2012-08-17
*       Author: zhongyu206043
*  Description: ����DHCP Clientģ�����Selecting״̬����
*               ֻ�е�DHCPģ�鴦��Selectingʱ����ʹ�á�
*        Input: DHCP4C_FSM_SELECT_S *pstOfferInfo:��ѡ���DHCP Server��Offer����
*       Output: 
*       Return: VOS_OK           �ɹ�
*               ����             ʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-08-17   zhongyu206043           Create for S.DHCP.1.1
*
*******************************************************************************/
extern ULONG TCPIP_DhcpcDoFsmSelecting(DHCP4C_FSM_SELECT_S *pstOfferInfo);



extern ULONG TCPIP_DhcpRmtClient(ULONG ulLoopbackIfIndex, ULONG ulOutIfIndex);
/*******************************************************************************
*    Func Name: TCPIP_DhcpClient
*  Description: ʹ��/ȥʹ��DHCP Client
*        Input: ULONG ulIfIndex:�ӿ�����
*               ULONG ulSetYes:ʹ�ܱ��  0-ȥʹ��;  1-ʹ��NodeB����DHCP; 2-ʹ����ͨDHCP
*       Output: 
*       Return: �ɹ�:VOS_OK;  ����:����ʧ��
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-07   wuhailan                Create
*
*******************************************************************************/
extern ULONG TCPIP_DhcpClient(ULONG ulIfIndex, ULONG ulSetYes);
/*******************************************************************************
*    Func Name: TCPIP_ReleaseDhcp
*  Description: �ͷ�DHCPC��ַ��Ϣ
*        Input: ULONG ulIfIndex:�ӿ�����,��Ϊ���ͷ�����ʹ��DHCP���õ�ַ�Ľӿڵĵ�ַ
*       Output: ��
*       Return: �ɹ�����DHCP4C_SUCCESS,��������ʧ��
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   wuhailan                Create
*
*******************************************************************************/
extern ULONG TCPIP_ReleaseDhcp(ULONG ulIfIndex);
/*******************************************************************************
*    Func Name: TCPIP_RenewDhcp
*  Description: ���͸���ĳ�ӿ����ڵ���Ϣ
*        Input: ULONG ulIfIndex-�ӿ�����ֵ,��Ϊ���������ʹ��DHCP���õ�ַ�Ľӿڵĵ�ַ
*       Output: ��
*       Return: �ɹ�����DHCP4C_SUCCESS,��������ʧ��
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   wuhailan                Create
*
*******************************************************************************/
extern ULONG TCPIP_RenewDhcp(ULONG ulIfIndex);

/*******************************************************************************
*    Func Name: TCPIP_SetDhcpcCiaddr
*  Description: ����Ciaddrֵ��Ϣ:
*               ulCiaddrΪ0 ʱ�������Ӧ��pConfigNode�ڵ�
*               ulCiaddr��Ϊ0ʱ�����Ӷ�Ӧ��pConfigNode�ڵ㣬���� ulCiaddr��ֵ
*               ulCiaddrΪ������,�û��ڴ���ʱ��Ҫ��һ���������������ת��
*        Input: ULONG ulIfIndex:�ӿ�����
*               ULONG ulCiaddr:Ҫ���õ�Ciaddrֵ
*       Output: ��
*       Return: �ɹ�����DHCP4C_SUCCESS,��������ʧ��
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   wuhailan                Create
*
*******************************************************************************/
extern ULONG TCPIP_SetDhcpcCiaddr(ULONG ulIfIndex, ULONG ulCiaddr);

/*******************************************************************************
*    Func Name: TCPIP_AddDhcpcOptionsInfo
*  Description: ����Client ID���VSI���60ѡ��ֵ
*        Input: ULONG ulIfIndex: �ӿ�����ֵ��
*               UCHAR ucCode:    �����CODE��
*                                Ŀǰֻ֧��������   43----VSIѡ��
*                                                   61----CIDѡ��
*               UCHAR ucLen:     ����ĳ�����
*               UCHAR *pucValue: �����ֵ��
*       Output: ��
*       Return: �ɹ�����DHCP4C_SUCCESS,��������ʧ��
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   wuhailan                Create
*
*******************************************************************************/
extern ULONG TCPIP_AddDhcpcOptionsInfo(ULONG ulIfIndex, UCHAR ucCode, UCHAR ucLen, UCHAR *pucValue);
/*******************************************************************************
*    Func Name: TCPIP_GetDhcpcOptionsInfo
*  Description: ��ȡ DHCP��������Ϣ����Ҫ����Ciaddr,VSI,CID.
*        Input: ULONG ulIfIndex: �ӿ�����
*               DHCP4C_OPTIONINFO_S *pstDhcpOptions: ��ȡ��Ϣָ��
*       Output: ��
*       Return: �ɹ�����DHCP4C_SUCCESS,��������ʧ��
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   wuhailan                Create
*
*******************************************************************************/
extern ULONG TCPIP_GetDhcpcOptionsInfo(ULONG ulIfIndex, DHCP4C_OPTIONINFO_S *pstDhcpOptions);
/*******************************************************************************
*    Func Name: TCPIP_ShowDhcpcOptionsInfo
*  Description: ��ʾDHCPC��ѡ����Ϣ
*        Input: CHAR *pstIfName:�ӿ�����
*       Output: ��
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-05-14   wuhailan                Create
*
*******************************************************************************/
extern VOID TCPIP_ShowDhcpcOptionsInfo(CHAR *pstIfName);

/*******************************************************************************
*    Func Name: TCPIP_GetDhcpcInfo
*  Description: ��ȡDHCP��Լ�����Ϣ
*        Input: ULONG ulIfIndex:�ӿ�����
*               DHCP4C_DISPLAYINFO_S *pstDhcp4cInfo:DHCP��Լ�����Ϣָ��
*       Output: ��
*       Return: VOS_OK�ɹ�,��������ʧ��
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   wuhailan                Create
*
*******************************************************************************/
extern ULONG TCPIP_GetDhcpcInfo(ULONG ulIfIndex, DHCP4C_DISPLAYINFO_S *pstDhcp4cInfo);
/*******************************************************************************
*    Func Name: TCPIP_ShowDhcpcInfo
*  Description: ��ʾָ���ӿ�DHCP Client��Լ��Ϣ
*        Input: CHAR *pstIfName:�ӿ�����
*       Output: ��
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   wuhailan                Create
*
*******************************************************************************/
extern VOID TCPIP_ShowDhcpcInfo(CHAR *pstIfName);

/*******************************************************************************
*    Func Name: TCPIP_SetDhcpcHADbg
*  Description: ���õ��Կ��صĽӿں���
*        Input: ULONG ulDbg:���õĵ��Կ���ֵ
*       Output: ��
*       Return: VOS_OK�ɹ�;VOS_ERRʧ��
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   wuhailan                Create
*
*******************************************************************************/
extern ULONG TCPIP_SetDhcpcHADbg(ULONG ulDbg);
/*******************************************************************************
*    Func Name: TCPIP_GetDhcpcHADbg
*  Description: ��ȡ���Կ��صĽӿں���
*        Input: ��
*       Output: ULONG *pulDbg:��ȡ�ĵ��Կ���ֵ
*       Return: VOS_OK�ɹ�;VOS_ERRʧ��
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   wuhailan                Create
*
*******************************************************************************/
extern ULONG TCPIP_GetDhcpcHADbg(ULONG *pulDbg);

/*******************************************************************************
*    Func Name: TCPIP_SetDhcpcDebug
*  Description: ���ýӿ�dhcp���õ��Կ��أ�ĳ���͵ĵ���
*                ���ز���ȫ�ֵĻ��Ǿֲ��ģ�ֻҪʹ���˸����͵�����Ϣ�ͻ����
*        Input: ULONG ulIfIndex:�ӿ�����ֵΪ������нӿ���Ч
*               ULONG ulSetYes:Ϊ��򿪵��Կ���,Ϊ0�رյ��Կ���
*               ULONG ulDHCP4CDebugType:���Կ�������,����ֵ����
*               DHCP4C_DEBUG_FLAG_PACKET        0x01
*               DHCP4C_DEBUG_FLAG_EVENT         0x02
*               DHCP4C_DEBUG_FLAG_ERROR         0x04
*               DHCP4C_DEBUG_FLAG_ALL           0x07
*       Output:
*       Return: �ɹ�����DHCP4C_SUCCESS,��������ʧ��
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   wuhailan                Create
*
*******************************************************************************/
extern ULONG TCPIP_SetDhcpcDebug(ULONG ulIfIndex, ULONG ulSetYes, ULONG ulDHCP4CDebugType);
/*******************************************************************************
*    Func Name: TCPIP_ShowDhcpcDebug
*  Description: ��ʾDHCPC�ĵ��Կ�����Ϣ.ע:������HA����
*        Input: VOID
*       Output: ��
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-05-14   wuhailan                Create
*
*******************************************************************************/
extern VOID TCPIP_ShowDhcpcDebug(VOID);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncProcDhcpcPacketHook
*  Description: DHCP4C���մ���Ĺ��Ӻ���ע��ӿ�
*        Input: TCPIP_PRODHCP_HOOK_FUNC pfHookFuc:�ṩ���û�ע���DHCP4C���մ���ĺ���ָ��
*       Output: ��
*       Return: VOS_OK�ɹ�,��������ʧ��
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   wuhailan                Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncProcDhcpcPacketHook(TCPIP_PROCDHCP_HOOK_FUNC pfHookFuc);

/*******************************************************************************
*    Func Name: TCPIP_SetDhcpcDefaultAddr
*  Description: ����DHCP��Ĭ�ϵ�ַ����������
*        Input: ULONG ulIfIndex: �ӿ�������
*               ULONG ulIpAddr: ����ӵĵ�ַ��������
*               ULONG ulSubnetMask: ����ӵĵ�ַ���������루������
*       Output: ��
*       Return: �ɹ�����DHCP4C_SUCCESS,��������ʧ��
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   wuhailan                Create
*
*******************************************************************************/
extern ULONG TCPIP_SetDhcpcDefaultAddr(ULONG ulIfIndex, ULONG ulIpAddr, ULONG ulSubnetMask);
/*******************************************************************************
*    Func Name: TCPIP_DelDhcpcDefaultAddr
*  Description: ���DHCP��Ĭ�ϵ�ַ����������
*        Input: ULONG ulIfIndex: �ӿ�������
*       Output: 
*       Return: �ɹ�����DHCP4C_SUCCESS,��������ʧ��
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   wuhailan                Create
*
*******************************************************************************/
extern ULONG TCPIP_DelDhcpcDefaultAddr(ULONG ulIfIndex);
/*******************************************************************************
*    Func Name: TCPIP_GetDhcpcDefaultAddr
*  Description: ��ȡDHCP��Ĭ�ϵ�ַ����������
*        Input: ULONG ulIfIndex: �ӿ�����
*       Output: ULONG *pulIpAddr: Ĭ�ϵ�ַ��������
*               ULONG *pulSubnetMask: Ĭ���������루������
*       Return: �ɹ�����DHCP4C_SUCCESS,��������ʧ��
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   wuhailan                Create
*
*******************************************************************************/
extern ULONG TCPIP_GetDhcpcDefaultAddr(ULONG ulIfIndex, ULONG *pulIpAddr,ULONG *pulSubnetMask);
/*******************************************************************************
*    Func Name: TCPIP_ShowDhcpcDefaultAddr
*  Description: ��ʾDHCP��Ĭ�ϵ�ַ����������
*        Input: CHAR *pstIfName:�ӿ�����
*       Output: ��
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-04-24   wuhailan                Create
*
*******************************************************************************/
extern VOID TCPIP_ShowDhcpcDefaultAddr(CHAR *pstIfName);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncGetDhcpcIP
*  Description: ע��DHCP Client��Ϣ�ϱ����Ӵ�����
*        Input: GET_DHCP_CLIENT_IP_HOOK_FUN pfGetDHCPClientIP
*
*       Output: 
*       Return: VOS_ERR
                VOS_OK
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-12   wangbin(62223)           Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncGetDhcpcIP (GET_DHCP_CLIENT_IP_HOOK_FUN pfGetDHCPClientIP);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncGetDhcpsIP
* Date Created: 2009-02-05
*       Author: mafeng(59090)
*  Description: ע��DHCP Server IP��Ϣ�ϱ����Ӵ�����
*        Input: GET_DHCP_SERVER_IP_HOOK_FUN pfGetDHCPServerIP:
*       Output: 
*       Return: DHCP4C_FAILURE
*               DHCP4C_SUCCESS
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-05   mafeng(59090)           Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncGetDhcpsIP (GET_DHCP_SERVER_IP_HOOK_FUN pfGetDHCPServerIP);

/*******************************************************************************
*    Func Name: TCPIP_SetDhcpcIP
*  Description: DHCP Client��ȡ��Ϣ���������·�
*        Input: ULONG ulIfIndex,
                ULONG ulDHCPClientIP
*               ULONG ulDHCPClientIPMask,
                ULONG aulDNSIP[DHCP4C_DNSIP_NUM],
                ULONG aulGatewayIP[DHCP4C_ROUTER_NUM]
                CHAR pcDomainName[DHCP4C_DOMAINNAME_SIZE],
                ULONG ulFlag
*       Output: 
*       Return: DHCP4C_HA_IS_SMOOTHING:ϵͳ����ƽ�����ֶ������׶�
                DHCP4C_NOT_3D_MODE:         ����άģʽ��
                DHCP4C_API_COM_NULL:        ���Ϊ��
                DHCP4C_PARA_ERR:            ��������
                DHCP4C_CONFIGERR_INDEX:     ��Ч�ӿ�����
                DHCP4C_CONFIGERR_CFGDHCPIP: ����DHCP ��ַʧ��
                DHCP4C_CONFIGERR_INDEX:     �ӿ�������Ч
                DHCP4C_SUCCESS:             ����ɹ�
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-12   wangbin(62223)           Create
*
*******************************************************************************/
extern ULONG TCPIP_SetDhcpcIP(ULONG ulIfIndex,
                                          ULONG ulDHCPClientIP,
                                          ULONG ulDHCPClientIPMask,
                                          ULONG aulDNSIP[DHCP4C_DNSIP_NUM],
                                          ULONG aulGatewayIP[DHCP4C_ROUTER_NUM],
                                          CHAR pcDomainName[DHCP4C_DOMAINNAME_SIZE],
                                          ULONG ulFlag
                                          );

extern ULONG TCPIP_RegFuncDhcpcAddOptionHook(gpfDHCPADDOPTION_HOOK_FUNC pfHookFunc);

/*******************************************************************************
*    Func Name: TCPIP_SetDhcpcTos
*  Description: ����DHCP4Cģ���tosֵ
*        Input: UCHAR ucTos: ���õ�tosֵ��ֵ����Ч
*       Output:
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-8-19    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_SetDhcpcTos(UCHAR ucTos);
/*******************************************************************************
*    Func Name: TCPIP_GetDhcpcTos
*  Description: ��ȡdhcp4cģ�����õ�tosֵ
*        Input: UCHAR *pucTos: �����ȡ��tosֵ
*       Output:
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-8-19    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_GetDhcpcTos(UCHAR *pucTos);
/*******************************************************************************
*    Func Name: TCPIP_SetDhcpcIgnoreOption
*  Description: �����Ƿ���Խ���server���͵�Я��50/55/57ѡ��ı���
*        Input: ULONG ulSetYes: Ҫ���õ�ֵ;0/1
*       Output:
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-8-20    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_SetDhcpcIgnoreOption(ULONG ulSetYes);
/*******************************************************************************
*    Func Name: TCPIP_GetDhcpcIgnoreOption
*  Description: ��ȡ����50/55/57ѡ����ֵ
*        Input: ULONG *pulSetYes: ���������ֵ
*       Output:
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-8-20    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_GetDhcpcIgnoreOption(ULONG *pulSetYes);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncDhcpLeaseHook
*  Description: ע��DHCP�����ļ���д����
*        Input: LEASE_WRITE_HOOK pfWriteHook: дDHCP�����ļ��Ĺ��Ӻ���
*               LEASE_READ_HOOK pfReadHook: ��ȡDHCP�����ļ��Ĺ��Ӻ���
*       Output: 
*       Return: DHCP4C_SUCCESS
*               DHCP4C_WRITE_LEASE_NULL
*               DHCP4C_READ_LEASE_NULL
*      Caution: �����ڳ�ʼ��VISPЭ��ջ֮ǰע�ᣬ���������Ӻ�������ͬʱע��
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-17  wujie(61195)     Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncDhcpLeaseHook(LEASE_WRITE_HOOK pfWriteHook, LEASE_READ_HOOK pfReadHook);


extern ULONG TCPIP_RegFuncProcDhcpcConfCheckHook(ULONG ulIfIndex,
                                    TCPIP_PROCDHCP_CONF_CHECK_HOOK_FUNC pfCfgCheckHook);


ULONG TCPIP_UnRegFuncProcDhcpcConfCheckHook(ULONG ulIfIndex);


extern ULONG TCPIP_SetDhcpcUserCheckResult(ULONG ulIfIndex, ULONG ulCorrelator, ULONG ulCheckResult);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncProcDhcpcUnicastHook
* Date Created: 2009-09-09
*       Author: xujun57575
*  Description: �ṩ��Ʒע��DHCPC���Ĵ���Ĺ���
*        Input: TCPIP_PROCDHCP_UNICAST_HOOK_FUNC pfProcDhcpcHookFunc:
*       Output:
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-09-09   xujun57575              Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncProcDhcpcUnicastHook(TCPIP_PROCDHCP_UNICAST_HOOK_FUNC *pfProcDhcpcHookFunc);

/*******************************************************************************
*    Func Name: TCPIP_GetDhcpcSessionIfIndexByPkt
* Date Created: 2009-11-28
*       Author: mafeng(59090)
*  Description: ����DHCPClient���Ļ�ȡDHCPC�Ự�Ľӿ�����ֵ(ֻ��DHCPServer
*               ���͵�����վ���͵�DHCPC���Ľ��д���,�Ǳ���վ���Ĳ������ط�0)
*        Input: UCHAR *pucPktBuf:������DHCPClient����,ΪDHCPC�����ַ����׵�ַ
*               ULONG usPktLen:DHCPClient���ĵĳ��ȣ�����Ӧ����240
*       Output: ULONG *pulIfIndex:��DHCPC���Ķ�Ӧ��ʹ��DHCPC���ܵĽӿ�����ֵ
*                                 Ҫ������ǿ�ָ��
*       Return: 0(VOS_OK)�ñ���Ϊ����վ(Э��ջ)�ı���
*               ��0(������)�ñ��Ĳ��Ǳ���վ(Э��ջ)�ı���
*      Caution: ���ط�0��˵���ñ��Ĳ��Ǳ���վ�ı��ģ�����0��ʾ�ñ����Ǳ���վ��
*               DHCPC���ģ������ڰѴӸ�DHCPC���Ļ�ȡ���ĵ�ַ���õ��ӿ�ǰ��Ҫ
*               �ж�һ�½ӿڵĽӿ�����ֵ�Ƿ����API���صĽӿ�����ֵ��ȣ����
*               ������������õ��ӿ��ϡ�
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-11-28   mafeng(59090)           Create
*
*******************************************************************************/
extern ULONG TCPIP_GetDhcpcSessionIfIndexByPkt(UCHAR *pucPktBuf, ULONG usPktLen, ULONG *pulIfIndex);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncDHCPVlanNotifyHook
* Date Created: 2010-11-03
*       Author: y171195(z171897)
*  Description: DHCP VLAN Scaning������,�ṩ��Ʒע��֪ͨOFFER������Я����VLAN��Ϣ�Ĺ���
*        Input: DHCP_VLAN_NOTIFY_HOOK pfDhcpVlanNotifyHook:��Ʒ�ṩ�Ĵ���OFFER����
*               ��Я����VLAN��Ϣ�ĺ���
*       Output: 
*       Return: VOS_OK: �ɹ�
*               ����: ʧ��
*      Caution: 1.�ù��Ӻ���֧�ֶ�̬ע��ͽ�ע��,���Բ�Ʒ������Э��ջ����֮�����
*                 ���øýӿ�ע��ͽ�ע��.
*               2.�ûص����Ӻ����в���ʹ�ò�Ʒ���ź�����������ܻ��VISP���ź�������������
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                          DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-11-03   y171195(z171897)              Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncDHCPVlanNotifyHook(DHCP_VLAN_NOTIFY_HOOK pfDhcpVlanNotifyHook);

/*******************************************************************************
*    Func Name: TCPIP_SetDHCPVlanScanning
* Date Created: 2010-11-03
*       Author: y171195(z171897)
*  Description: ʹ��/ȥʹ��DHCP VLAN Scaning����
*        Input: ulIfIndex: �ӿ�����
*               ulEnable: ʹ�ܱ��: 1:ʹ��; 0:ȥʹ��
*               ulDelayTime: Discovery�����ش���ʱ�ӳ�ʱ��,��λ����,ȡֵ��Χ[0,3600*1000]
*       Output: 
*       Return: VOS_OK: �ɹ�
*               ����: ʧ��
*      Caution:
*      1.DHCP Vlan Scanning����Ҫ���Ʒ�����ڽӿ���ʹ��DHCP֮ǰ��ʹ��DHCP Vlan Scanning����,
*        ����DHCP Vlan Scanning���ܿ����޷�����������
*      2.DHCP Vlan Scanning����ָ������ʱʱ�����Ч�Ժ������ɲ�Ʒ���б�֤��
*        Ҫ���Ʒָ������ʱʱ��Ҫ�㹻��Ʒ��DHCP discovery���Ľ���VLAN Scanning���ʹ���
*        ��Ҫ���Ʒָ�����ӳ�ʱ��Ҫ��֤Э��ջ�ش���discovery������VLAN Scanning���ʹ�����ɺ󷢳���
*      3.DHCP Vlan Scanning����Ҫ���Ʒ��������̫�ӿ���ʹ��VLAN���ܡ����Ҳ�������ֻ����ĳһ�ض�VLAN�ı���.
*      4.DHCP VLAN Scaning���ܲ�֧��HA����.
*      5.ֻ����̫�ӿ�֧��DHCP VLAN Scaning����.
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                          DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-11-03   y171195(z171897)              Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_SetDHCPVlanScanning(ULONG ulIfIndex, ULONG ulEnable, ULONG ulDelayTime);

/*******************************************************************************
*    Func Name: TCPIP_GetDHCPVlanScanning
* Date Created: 2010-11-03
*       Author: y171195(z171897)
*  Description: ʹ��/ȥʹ��DHCP VLAN Scaning����״̬��ѯ
*        Input: ulIfIndex: �ӿ�����
*       Output: pulEnable: ʹ�ܱ��: 1:ʹ��; 0:ȥʹ��
*               pulDelayTime: Discovery�����ش���ʱ�ӳ�ʱ��,��λ����,ȡֵ��Χ[0,3600*1000]
*       Return: VOS_OK: �ɹ�
*               ����: ʧ��
*      Caution:
*      1.DHCP Vlan Scanning����Ҫ���Ʒ�����ڽӿ���ʹ��DHCP֮ǰ��ʹ��DHCP Vlan Scanning����,
*        ����DHCP Vlan Scanning���ܿ����޷�����������
*      2.DHCP Vlan Scanning����ָ������ʱʱ�����Ч�Ժ������ɲ�Ʒ���б�֤��
*        Ҫ���Ʒָ������ʱʱ��Ҫ�㹻��Ʒ��DHCP discovery���Ľ���VLAN Scanning���ʹ���
*        ��Ҫ���Ʒָ�����ӳ�ʱ��Ҫ��֤Э��ջ�ش���discovery������VLAN Scanning���ʹ�����ɺ󷢳���
*      3.DHCP Vlan Scanning����Ҫ���Ʒ��������̫�ӿ���ʹ��VLAN���ܡ����Ҳ�������ֻ����ĳһ�ض�VLAN�ı���.
*      4.DHCP VLAN Scaning���ܲ�֧��HA����.
*      5.ֻ����̫�ӿ�֧��DHCP VLAN Scaning����.
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                          DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-11-03   y171195(z171897)              Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_GetDHCPVlanScanning(ULONG ulIfIndex, ULONG *pulEnable, ULONG *pulDelayTime);


extern ULONG TCPIP_GetDhcp4cStatistic(DHCP4C_STATISTIC_S * pstStat);


extern ULONG TCPIP_ClrDhcp4cStatistic(VOID);


extern VOID TCPIP_ShowDhcp4cStat(VOID);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncProcDhcpcValidPacketHook
* Date Created: 2014-02-11
*       Author: likaikun213099
*  Description: �û�ע��У��DHCP���ĵĹ��Ӻ���
*        Input: TCPIP_PROC_VALID_DHCP_HOOK_FUNC pfHookFuc:���Ӻ���
*       Output: NONE
*       Return: �ɹ���VOS_OK
*               ʧ�ܣ�VOS_ERR
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-02-11   likaikun213099          Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncProcDhcpcValidPacketHook (TCPIP_PROC_VALID_DHCP_HOOK_FUNC pfHookFuc);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* _DHCP4C_API_H_ */

