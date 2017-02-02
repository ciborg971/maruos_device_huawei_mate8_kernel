
#ifndef __DHCPS_H__
#define __DHCPS_H__
/**************************************************************************\
*  Copyright (c) 2000-2002, Huawei Tech. Co., Ltd.
*  All rights reserved.
* 
*  File name:  dhcps.h
*  Project:    Quidway S8016 Dhcp Server
*  Author:     wanghui
*  Version:    V1.0
*  Date:       2001-12-29
*  Description:DHCP SERVER��ͷ�ļ�
*  History:  
*  Others: 
\**************************************************************************/


#define DHCPS_INTERNAL       1     /* ������������DHCP SERVER */
#define DHCPS_EXTERNAL       0     /* ������������DHCP SERVER */ 

#define DHCPS_UNICAST        1
#define DHCPS_BROADCAST      0

typedef struct  tagDhcpServerDiag
{
    ULONG ulDhcpRcvTotal;                       /* DHCP�յ��ı��ĵ����� */
    
    ULONG ulDhcpRcvFromNps;            /* DHCP�յ��Ĵ�NPS�����ı����� */    
    ULONG ulDhcpRcvFromSocket;      /* DHCP�յ��Ĵ�socket�����ı����� */
    
    ULONG ulDhcpSendTotal;          /* DHCP server�����ı������� */
    
    ULONG ulDhcpClientPktDeclineTotal; /* DHCP server�յ���DECLINE������ */
    ULONG ulDhcpClientPktInformTotal;  /* DHCP server�յ���INFORM������ */
    ULONG ulDhcpClientPktDiscoverTotal;/* DHCP server�յ���DISCOVER������ */
    ULONG ulDhcpClientPktRequestTotal; /* DHCP server�յ���REQUEST������ */
    ULONG ulDhcpClientPktReleaseTotal;  /* DHCP server�յ���RELEASE������ */
    ULONG ulDhcpServerPktOfferTotal;   /* DHCP server������OFFER������ */
    ULONG ulDhcpServerPktAckTotal;     /* DHCP server������ACK������ */
    ULONG ulDhcpServerPktNakTotal;     /* DHCP server������NAK������ */

    /* һЩ����ͳ����Ϣ */
    ULONG ulDhcpRcvUnknownTotal;       /* DHCP server�յ���δ֪�������� */
    ULONG ulMemMallocErrNum;           /* ��Ҫ��¼dhcpr.c���ڴ����ʧ�ܵĴ��� */
}DHCPServerDIAG_S;

typedef struct tagSEtherAddr {
    unsigned char AddrByte[6];
} SEtherAddr;


#ifndef SUCCESS
#define SUCCESS                 0
#define FAILURE                  1
#endif

#define  VLAN_MIN_VLANID            2
#define  VLAN_MAX_VLANID            4094

void DHCPS_PrintDebug(CHAR *pcStr );
#define DHCPSOPTION_COUNT 18

#define L2IF_SUCCESS     VOS_OK
#define L2IF_FAILURE     VOS_ERR

#define ETHERNETHARDWARETYPE 1
#define ETHERNETHARDWARELEN  6 

#define DHCP_PKT_BUFF_SIZE 2048 /* ����dhcp���ĵĻ����С */

/*DHCP������"options"�ֶζ�Ӧ�ı�־λ*/
#define DHCPSUBNETMASK_CODE_FLAGBIT  1 
#define DHCPROUTERIP_CODE_FLAGBIT    (1<<1) 
#define DHCPDNSIP_CODE_FLAGBIT       (1<<2)
#define DHCPDOMAINNAME_CODE_FLAGBIT  (1<<3)

#define DHCPNBNS_CODE_FLAGBIT        (1<<4) 
#define DHCPNBDS_CODE_FLAGBIT        (1<<5) 
#define DHCPNBNT_CODE_FLAGBIT        (1<<6) 
#define DHCPNBSCOPE_CODE_FLAGBIT     (1<<7) 

#define DHCPIPLEASETIME_CODE_FLAGBIT (1<<8)  
#define DHCPRENEWTIME_CODE_FLAGBIT   (1<<9)  
#define DHCPREBINDTIME_CODE_FLAGBIT  (1<<10)  

#ifdef   __WIN32_PLATFORM__
#pragma pack(push, 1)
#endif

typedef struct tagLAM_MACIP
{
    ULONG ulIPAddr;
    ULONG ulFwdInfo;
}VOS_PACKED LAM_MACIP;

#ifdef   __WIN32_PLATFORM__
#pragma pack(pop, 1)
#endif

#define DEBUG_HASH   0
#define SMARTBITS_EMU 0

#define DHCP_MAX_VLANID       4094          /* �����õ�VLANIDֵ */ 
#define DHCP_MIN_VLANID       2             /* ��С���õ�vlanidֵ */ 
#define DHCPR_DEFAULTVLAN     1             /*ϵͳĬ�ϵ�vlan�ĳ�ʼֵ*/

#define DHCP_MAX_PORT_NUM 512              /* l3֧�ֵ����˿���Ŀ */

/* ��ϵͳ�еõ���PORT��תΪȫ�ֱ��,���256���˿� */
/*********************************************************************
 * ����ֻ�������ӿ�GE��FE��ÿ���ӿڰ������һ��FE�ӿ����˿�0��15���� *
 * ÿ���ӿڰ������2��GE�ӿ���ÿ���ӿ��˿�0��1��;                    * 
 * �������㷨,16*(SLOTNO-1)+PICNO*2+PORTNO��ÿ����Ķ˿�ͳһ���     *
 *********************************************************************/
#define DHCP_GPORT(stInfo) (32*((stInfo).ucSlotNo-1)+(stInfo).ucPICNo*2+(stInfo).ucPortNo)

#define MAX_DHCP_SERVER_GROUP 20    /* L3֧�ֵ�����DHCP SERVER��ĸ��� */
#define MIN_DHCP_SERVER_GROUP 1
#define MAX_DHCP_SERVER_NUM   2     /* ÿ��SERVER��֧�ֵ�SERVER����Ŀ */

#define _DEBUG_DHCPRELAY 1          /* DHCP RELAY�ĵ��Կ��� */

#define    DHCPS_PORT        67          /* ���ڱ�ʶDHCP SERVER��UDP�˿ں� */
#define    DHCPC_PORT        68          /* ���ڱ�ʶDHCP CLIENT��UDP�˿ں� */

#define CLIENTID_LEN         7
#define ETHERNETHARDWARETYPE 1
#define ETHERNETHARDWARELEN  6 

#define  MAGICCOOKIE         0x63825363 /* �����ֽ���,DHCP OPTION��ʼ���ĸ��ֽ�Ϊħ���֣�����У�� */
#define  ENDOFOPTIONS        0xff       /* DHCP OPTION�Ľ�����ʶ */   

#define DHCPOPTION_COUNT     8         /* DHCP OPTION��L3���ĵ���Ŀ�ĸ���,�����Ҫ���ȷ�� */


#define DHCPSUBNETMASK_CODE  0x01 /* DHCP����"options"�ֶκ���"Subnet mask"ѡ��ı�ʶ�� */
#define DHCPROUTERIP_CODE    0x03 /* DHCP����"options"�ֶκ���"Routet "ѡ��ı�ʶ�� */
#define DHCPDNSIP_CODE       0x06 /*DHCP����"options"�ֶκ���"DNS server "ѡ��ı�ʶ��*/
#define DHCPHOSTNAME_CODE    0x0c /*DHCP����"options"�ֶκ���"Host name"ѡ��ı�ʶ��*/
#define DHCPDOMAINNAME_CODE  0x0f /*DHCP����"options"�ֶκ���"Domain name"ѡ��ı�ʶ��*/
#define DHCPNBNS_CODE        0x2c /*DHCP����"options"�ֶκ���"Netbios name server"ѡ��ı�ʶ��*/
#define DHCPNBDS_CODE        0x2d /*DHCP����"options"�ֶκ���"Netbios data distribute server"ѡ��ı�ʶ��*/
#define DHCPNBNT_CODE        0x2e /*DHCP����"options"�ֶκ���"Netbios node type"ѡ��ı�ʶ��*/
#define DHCPNBSCOPE_CODE     0x2f /*DHCP����"options"�ֶκ���"Netbios scope"ѡ��ı�ʶ��*/
#define DHCPVENDORINFO_CODE  0x29  /*DHCP����"options"�ֶκ���"Vendor specific information"ѡ��ı�ʶ��*/
#define DHCPREQUESTEDIP_CODE 0x32 /* DHCP����"options"�ֶκ���"Requested Ip"ѡ��ı�ʶ�� */
#define DHCPIPLEASETIME_CODE 0x33  /*DHCP����"options"�ֶκ���"Dhcp Ip address lease time"ѡ��ı�ʶ��*/
#define DHCPMESSAGETYPE_CODE 0x35 /* DHCP����"options"�ֶκ���"Dhcp Message Type"ѡ��ı�ʶ�� */
#define DHCPSERVERIP_CODE    0x36 /* DHCP����"options"�ֶκ���"Dhcp Server Ip"ѡ��ı�ʶ�� */
#define DHCPREQPARAM_CODE    0x37 /* DHCP����"options"�ֶκ���"Requested parameter list"ѡ��ı�ʶ�� */
#define DHCPRENEWTIME_CODE   0x3a /* DHCP����"options"�ֶκ���"Renew time"ѡ��ı�ʶ�� */
#define DHCPREBINDTIME_CODE  0x3b /* DHCP����"options"�ֶκ���"Rebind time"ѡ��ı�ʶ�� */
#define DHCPCLIENTID_CODE    0x3d /* DHCP����"options"�ֶκ���"Dhcp client Id"ѡ��ı�ʶ�� */
#define DHCPCLASSID_CODE    0x3c /* DHCP����"options"�ֶκ���"Dhcp class Id"ѡ��ı�ʶ�� */

/*DHCP������"options"�ֶζ�Ӧ�ı�־λ*/
#define DHCPSUBNETMASK_CODE_FLAGBIT  1 
#define DHCPROUTERIP_CODE_FLAGBIT    (1<<1) 
#define DHCPDNSIP_CODE_FLAGBIT       (1<<2)
#define DHCPDOMAINNAME_CODE_FLAGBIT  (1<<3)

#define DHCPNBNS_CODE_FLAGBIT        (1<<4) 
#define DHCPNBDS_CODE_FLAGBIT        (1<<5) 
#define DHCPNBNT_CODE_FLAGBIT        (1<<6) 
#define DHCPNBSCOPE_CODE_FLAGBIT     (1<<7) 

#define DHCPIPLEASETIME_CODE_FLAGBIT (1<<8)  
#define DHCPRENEWTIME_CODE_FLAGBIT   (1<<9)  
#define DHCPREBINDTIME_CODE_FLAGBIT  (1<<10)  

#define DHCPRELEASEPKT_LEN   328

#define DHCP_IPTTL           16


#define MACHDRLEN             14        /* ���ڷ�װ���ĵĶ���ͷ�ĳ��� */              
#define IPHDRLEN             20     /* ���ڷ�װ���ĵ�IPͷ�ĳ��� */  
#define UDPHDRLEN            8      /* ���ڷ�װ���ĵ�UDPͷ�ĳ��� */
#define MIN_DHCP_UDP_LEN     308    /* ����DHCP���ĵ�UDP���ĵ���С���� */
#define MIN_DHCP_LEN         236    /* DHCP����ͷ����С���� */

/*IP���еļ����ϲ�Э������ֵ*/
#define UDP_PROTOTYPE        17
#define TCP_PROTOTYPE        6
#define ICMP_PROTOTYPE       1

#define DHCPFIXEDFIELD_LEN   (ULONG)sizeof(DHCP_S) /* 236bytes */

#define HOP_LIMIT          4    /* DHCP���ĵ��������� */

#define DHCP_PKT_BUFF_SIZE 2048 /* ����dhcp���ĵĻ����С */

#define DHCP_DEBUG_ON      0
#define DHCP_DEBUG_OFF     1

#define DHCP_VLANTAG_TYPE   0x8100
#define IP_DGRAM_TYPE       0x0800           /* ��ʾMAC���װ����IP���� */
#define INBROADCASTIP       0xFFFFFFFF     /* IP�㲥��ַ */

#define DHCP_QUEUELEN    500     /* ��Ϣ���еĳ��� */
#define EV_DHCP_RCV     0x04
#define EV_DHCP_MSG     0x03

/*����,���ڴ򿪶�ʱ��hash�����,Ϊ0ʱ,��hash����������,Ϊ1ʱ����. */
#define TIMEHASH    0           

#define DHCP_DELHASH_TIMESPAN 3600000 /* ��ʱ��ʱ����ʱ����,�Ժ���Ϊ��λ,ÿ1Сʱ����һ�λص�����*/

/*SOCKET��������ȡֵ��Χ�������Сֵ*/
#define MINSOCKVALUE          1
#define MAXSOCKVALUE          3072 

#define DHCP_VLANTAG_SIZE     4


#define DHCP_GET_VLANID(ulFwdInfo) (USHORT)((ulFwdInfo) & 0x0000FFFF)
#define DHCP_GET_PORTNO(ulFwdInfo) (UCHAR)(((ulFwdInfo) >> 16) & 0x0000001F)
#define DHCP_GET_PICNO(ulFwdInfo)  (UCHAR)(((ulFwdInfo) >> 21) & 0x00000003)
#define DHCP_GET_SLOTNO(ulFwdInfo) (UCHAR)(((ulFwdInfo) >> 24) & 0x000000FF)

/*����MBUF_TR_RegisterReceiver��ǿ������ת��*/ 
typedef    VOID (*pfRCV_FUN)(PMBUF_S *,ULONG ); 

/*����ע�ᶨʱ���ص�������ǿ������ת��*/
typedef VOID  (*pfDhcpTimerFunc)(VOID *); 

/* DHCP��Ϣ����: */
enum enDHCPR_MSG
{
   DHCPDISCOVER=1,
   DHCPOFFER,
   DHCPREQUEST,
   DHCPDECLINE,
   DHCPACK,
   DHCPNAK,
   DHCPRELEASE,
   DHCPINFORM
};


typedef struct tagEtherAddr
{
    UCHAR  ucAddrByte[6];
}EtherAddr_S;


typedef struct tagMACHDR
{
    EtherAddr_S stDstMacAddr;    /* Ŀ��MAC��ַ */
    EtherAddr_S stSrcMacAddr;    /* ԴMAC��ַ */
    USHORT      usHdrType;            /* Э������ */
}MACHDR_S;        

typedef struct tagMACHDRWITHTAG
{
    EtherAddr_S stDstMacAddr;    /* Ŀ��MAC��ַ */
    EtherAddr_S stSrcMacAddr;    /* ԴMAC��ַ */
    USHORT      usVlanType;     /* vlan type*/
    USHORT      usVlanId;
    USHORT      usHdrType;         /* Э������ */
}MACHDRWITHTAG_S;        

/* ���µ�ѡ�Ҫ�޸�,ɾ��ĳ������ĳЩ�� */
/**************************************************************************************
*˵��:����DHCP���ĵ�option���ǿ��Ա仯�ģ������û��ı���Я������Ϣ���仯���������ṹ���޷���ʵ��ӳ
*dhcp option�εı��������֮���Զ�������ṹ�壬��Ϊ���ڱ���option�ε�ʱ���¼һЩ����Ȥ����Ϣ���޷�
*��dhcp_s������˳��һһ��Ӧ�ķ�ӳ�����ģ���������֮���Բ���ָ�룬��û���ñ�����ֻ�ǲ����ٵ���Ϊoption
*�������ݣ���Ϊ������������dhcp����ͷ�ģ�ֻ����һЩָ�����������Ȥ��ѡ����dhcp�����еĵ�ַλ�ü��ɡ�
*ʵ������ȫ���Բ��ñ�������¼����Ȥѡ���Ϊ��ǰһֱ����ָ���¼�ķ�ʽ������Ҳ���������ˣ�������Ҫ��ס
*����DHCPOPTION_S��һһ��Ӧ������dhcp�����е�option���������ݣ�����DHCP_S��ͬ��
*ֵ��˵������:ʹ��ָ���кܶ�����ԣ����Լ��ٶ������������������ÿһС�����һ��������
****************************************************************************************/
typedef struct tagDHCPOPTION
{
    ULONG  ulSubnetMask;
    ULONG *pulRouterIp;               /*Ĭ������option:code = 3*/
    UCHAR ucRouterIpLen;
    ULONG *pulDNSIp;                  /*DNS������option:code = 6*/
    UCHAR ucDNSIpLen;
    ULONG  ulMagicCookie;
    UCHAR *pucHostName;               /*������option:code = 12*/    
    ULONG  ulHostNameLen;
    UCHAR *pucDomainName;             /*����option:code = 15*/
    UCHAR ucDomainNameLen;
  /*NetBiosѡ��*/
    ULONG *pulNBNSIp;                 /*Netbios���Ʒ�����option:code = 44*/
    UCHAR ucNBNSIpLen;
    ULONG *pulNBDSIp;                 /*Netbios���ݷַ�������option:code = 45*/
    UCHAR ucNBDSIpLen; 
    UCHAR *pucNBNodeType;             /*Netbios�ڵ�����option:code = 46*/
    UCHAR *pucNBScope;                /*Netbios��Χoption:code = 47*/
    UCHAR ucNBScopeLen;
  /*DHCP option*/
    ULONG *pulReqIp;                  /*�ͻ���Ҫ��IP��ַoption:code = 50*/
    ULONG *pulLeaseTime;              /*IP��ַ����option:code = 51*/
    UCHAR *pucDHCPMsgType;            /*DHCP��Ϣ����option:code = 53*/
    ULONG *pulDHCPServerIp;           /*DHCP������IP��ַoption:code = 54*/
    UCHAR *pucReqParamList;           /*�ͻ�����Ĳ����б�option:code = 55*/
    UCHAR ucReqParamListLen;
    ULONG *pulRenewTime;              /*����ʱ��option:code = 58*/
    ULONG *pulRebindTime;             /*���°�ʱ��option:code = 59*/
    UCHAR *pucClientId;               /*�ͻ���ʶoption:code = 61*/
    ULONG  ulClientIdLen;
  /*Ϊ֧��CM,IDT���趨��ר�ŵĳ���ѡ��*/
    UCHAR *pucVendorOption;           /*�����ض���Ϣoption:code = 43*/
    UCHAR ucVendorOptinLen;
  /*��¼'option'��������λ��*/
    UCHAR *pucEndOfOption;
}DHCPOPTION_S;

typedef struct tagDHCPR_INFOHDR
{
    UCHAR    ucSlotNo;
    UCHAR    ucReserved1:1;    /* ����2BitԤ�� */
    UCHAR    ucPICNo:2;        /* 2BitΪ���俨�� */
    UCHAR    ucPortNo:5;    /* 4BitΪ�˿ں� */
    USHORT   usVlanId;
}DHCPR_INFOHDR_S;

typedef struct tagMAC_HASHDATA
{
    EtherAddr_S stUserMacAddr; /* �û�������MAC��ַ */
    DHCPR_INFOHDR_S stDhcpFwdInfo;  
    /* �洢ʱ�ǰ�4���ֽ�����,���ﲹ2���ֽ�,ʹռ�ÿռ�Ϊ4�ı���. */
    UCHAR ucClrFlag;
    UCHAR RESERVED; 
}MACHASH_S;

typedef struct tagDHCP_SERVER_GROUP
{
     ULONG   ulServerAddr1;
     ULONG   ulServerAddr2;
}DHCP_SERVER_GROUP_S;

typedef struct tagDHCP_UDP_FATEHEAD
{
     ULONG   ulSrcIp;
     ULONG   ulDestIp;
     UCHAR   ucPad;
     UCHAR   ucProtocal;
     SHORT   sUdpLen;
}DHCP_UDP_FATEHEAD_S;

/**Added by zhengzhiguo 2003-03-07 for d18872**/
typedef struct  tagDhcpDiagPort
{
    ULONG ulFwdInfo;
    ULONG ulPacketNum;
}DHCPDIAGPORT_S;
/**End Added**/

typedef struct  tagDhcpDiag
{
    ULONG ulDhcpRcvTotal;                       /* DHCP�յ��ı��ĵ����� */
    
    /*����vlan�յ���DHCP������*/
    ULONG ulDhcpRcvFromVlan[DHCP_MAX_VLANID + 1];        /* ����Ĳ���ΪVlanId */

    /**Added by zhengzhiguo 2003-03-07 for d18872**/
    DHCPDIAGPORT_S stPacketFromPort[DHCP_MAX_PORT_NUM];
    /**End Added**/
    
    ULONG ulDhcpRcvFromNps;            /* DHCP�յ��Ĵ�NPS�����ı����� */    

    ULONG ulDhcpServerPktTotal;     /* DHCP�յ���server�����ı����� */    
    
    
    ULONG ulDhcpSendToServer;          /* DHCP���͵�SERVER�ı����� */
    
    ULONG ulDhcpClientPktTotal;        /* DHCP�յ���CLIENT�������ı������� */
    ULONG ulDhcpClientPktUnicast;      /* DHCP�յ���CLIENT�����ĵ��������� */
    ULONG ulDhcpClientPktBroadcast;    /* DHCP�յ���CLIENT�����Ĺ㲥������ */

    ULONG ulDhcpClientPktDeclineTotal; /* DHCP�յ���DECLINE������ */
    ULONG ulDhcpClientPktInformTotal;  /* DHCP�յ���INFORM������ */
    ULONG ulDhcpClientPktDiscoverTotal;/* DHCP�յ���DISCOVER������ */
    ULONG ulDhcpClientPktRequestTotal; /* DHCP�յ���REQUEST������ */
    ULONG ulDhcpServerPktOfferTotal;   /* DHCP�յ���OFFER������ */
    ULONG ulDhcpServerPktAckTotal;     /* DHCP�յ���ACK������ */
    ULONG ulDhcpServerPktNakTotal;     /* DHCP�յ���NAK������ */

    /* һЩ����ͳ����Ϣ */
    ULONG ulNotDhcpRequestPkt;         /* ���������ĺ����յ��ķ��������� */
    ULONG ulNotDhcpReplyPkt;           /* ��Ӧ�������յ��ķ���Ӧ������ */
    ULONG ulMemMallocErrNum;           /* ��Ҫ��¼dhcpr.c���ڴ����ʧ�ܵĴ��� */
}DHCPDIAG_S;

/*untagged���Զ��壺*/
#define    VMS_TAGGED                0
#define    VMS_UNTAGGED            1

#define MBUF_FLAG_VLAN_SINGLECAST  0x00200000
#define MBUF_TR_DHCPR               0x0000000b

/*�����Ƿ������õ�ö�ٱ���*/
typedef enum tagIPPOOL_LEASE_FLAG
{
    LEASE_ABLE =0,
    LEASE_DISABLE
}IPPOOL_LEASE_FLAG;

/**********************VLAN���ENUM����**********************/
/* VLAN���� */
enum enVlanType
{
    VLAN_TYPE_INVALID = 0,
    VLAN_TYPE_DEFAULT,            /* ȱʡVLAN����        */
    VLAN_TYPE_COMMON,            /* ��ͨVLAN����        */
    VLAN_TYPE_SUPER,            /* super VLAN����   */
    VLAN_TYPE_SUB,                /* sub VLAN����        */
    VLAN_TYPE_PORT                /* �ֲ� VLAN����    */
};

#define L2IF_MAX_VLAN_NUM       4096    /*ϵͳ�������vlan��*/

#define DHCP_SRV_EV_QUIT         0x00000001
#define DHCP_SRV_EV_CLNT         0x00000002



#endif
