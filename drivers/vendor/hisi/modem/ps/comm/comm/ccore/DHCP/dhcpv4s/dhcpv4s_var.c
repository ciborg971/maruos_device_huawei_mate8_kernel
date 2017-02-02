#include "dhcp_inc.h"
/* add by w00316385 start */
#include "dhcpc_def.h"
/* add by w00316385 end */
#include "dhcpv4s_def.h"
#include "dhcpv4s_type.h"
#include "dhcpv4s_var.h"
#include "dhcpv4s_fun.h"
#include "dhcpv4s_dbgcmd.h"


/*MAIN*/
ULONG g_ulDhcpServerTaskId = 0;

MC_QUE_ID g_pDHCPSRcvDhcpMsgQueId = NULL;      /* ��������PF-DPE ��DHCP ��Ϣ���ն���ID */
ULONG *g_ulDhcpStatisc = NULL;

/*TIMER*/
ULONG  g_ulDhcpsTimerQueId = 0;    /* ��ʱ����Ϣ���� */
ULONG  g_ulDhcpsInnerQueId = 0;

ULONG  g_ulLeaseCircleTimerID = 0;
ULONG  g_ulStateCircleTimerID = 0;

/* BEGIN: Modified by jixiaoming at 2011-05-04 */
DHCPS_TIMER_LINKLIST_S** g_ppstStateTimerList = NULL;                           /* ״̬��ʱ������ָ������ */
DHCPS_TIMER_LINKLIST_S** g_ppstLeaseTimerList = NULL;                          /* ��Լ��ʱ������ָ������ */
/* END: Modified by jixiaoming at 2011-05-04 */
DHCPS_TIMER_LINKLIST_S*  g_pstLeaseTimer = NULL;
DHCPS_TIMER_LINKLIST_S*  g_pstStateTimer = NULL;

ULONG g_ulLeaseTimerCount = 0;         /* ��׼��ʱ���� */
ULONG g_ulStateTimerCount = 0;         /* ��׼��ʱ���� */

ULONG  g_ulCurrentStateNode;              /*  ��ǰ�����state �ڵ� */
ULONG  g_ulCurrentLeaseNode;              /*  ��ǰ�����lease �ڵ� */

UCHAR *g_pucDHCPSRecvMsgBuff = NULL;


/*CFG*/
ULONG g_ulDhcpServerSwitch = 0;
DHCPS_EXPIRED_REC_S *g_pstExpiredInfor = NULL;              /*dhcp server expired ��Ϣ */

DHCPS_ANALYZEDPACKET_S g_stAnalyzPacket;

DHCPS_MSG_BUFFLIST_HEAD *g_pstDHCPMsgBuffList = NULL;


/*PROC*/
DHCPS_LEASE_S *g_pstDhcpSLease = NULL;   /* g_pstDhcpSLease[0]��ʹ�� */
DHCPS_CFG_OPTION_S *g_pstOption = NULL;

UCHAR g_aucMsg2Event[9] = {0xff,
                                          DHCPS_MSG_RECIVE_DISCOVER,
                                          0xff,
                                          DHCPS_MSG_RECIVE_REQUEST,
                                          DHCPS_MSG_RECIVE_DECLINE,
                                          0xff,
                                          DHCPS_MSG_RELAY_SERVER_NAK,
                                          DHCPS_MSG_RECIVE_RELEASE,
                                          DHCPS_MSG_RECIVE_INFORM};

UCHAR g_aucMsgUSM2Event[DHCPS_USM_MSG_END] = {0xff, 0xff, 0xff,
                                                                              DHCPS_MSG_USM_ADDRESS_SUCCESS,
                                                                              DHCPS_MSG_USM_ADDRESS_FAILURE,
                                                                              DHCPS_MSG_USM_DEACTIVE};


const UCHAR g_ucDhcpOptionParseType[79]={
    DHCP_OPTION_BYTEPARSE,    /*0 Pad Option*/
    DHCP_OPTION_LONG,    /*1 Subnet Mask*/
    DHCP_OPTION_LONG,    /*2 Time Offset*/
    DHCP_OPTION_IP_ADDRESS,    /*3 Router Option*/
    DHCP_OPTION_IP_ADDRESS,    /*4 Time Server Option*/
    DHCP_OPTION_IP_ADDRESS,    /* 5 Name Server Option*/
    DHCP_OPTION_IP_ADDRESS,    /*6 Domain Name Server Option*/
    DHCP_OPTION_IP_ADDRESS,    /*7 Log Server Option*/
    DHCP_OPTION_IP_ADDRESS,    /*8 Cookie Server Option*/
    DHCP_OPTION_IP_ADDRESS,    /*9 LPR Server Option*/
    DHCP_OPTION_IP_ADDRESS,    /* 10 Impress Server Option*/
    DHCP_OPTION_IP_ADDRESS,    /*11 Resource Location Server Option*/
    DHCP_OPTION_BYTEPARSE,    /*12 Host Name Option*/
    DHCP_OPTION_SHORT,    /*13 Boot File Size Option*/
    DHCP_OPTION_BYTEPARSE,    /*14 Merit Dump File*/
    DHCP_OPTION_BYTEPARSE,    /*15 Domain Name*/
    DHCP_OPTION_IP_ADDRESS,    /*16 Swap Server*/
    DHCP_OPTION_BYTEPARSE,    /*17 Root Path*/
    DHCP_OPTION_BYTEPARSE,    /*18 Extensions Path*/
    DHCP_OPTION_BYTE,    /*19 IP Forwarding Enable/Disable Option*/
    DHCP_OPTION_BYTE,    /*20 Non-Local Source Routing Enable/Disable Option*/
    DHCP_OPTION_LONGPARSE,    /*21 Policy Filter Option*/
    DHCP_OPTION_SHORT,    /*22 Maximum Datagram Reassembly Size*/
    DHCP_OPTION_BYTE,    /*23 Default IP Time-to-live*/
    DHCP_OPTION_LONG,    /*24 Path MTU Aging Timeout Option*/
    DHCP_OPTION_SHORTPARSE,    /*25 Path MTU Plateau Table Option*/
    DHCP_OPTION_SHORT,    /*26 Interface MTU Option*/
    DHCP_OPTION_BYTE,    /*27 All Subnets are Local Option*/
    DHCP_OPTION_IP_ADDRESS,    /*28 Broadcast Address Option*/
    DHCP_OPTION_BYTE,    /*29 Perform Mask Discovery Option*/
    DHCP_OPTION_BYTE,    /*30 Mask Supplier Option*/
    DHCP_OPTION_BYTE,    /*Perform Router Discovery Option*/
    DHCP_OPTION_IP_ADDRESS,    /*Router Solicitation Address Option*/
    DHCP_OPTION_IP_ADDRESS,    /*Static Route Option*/
    DHCP_OPTION_BYTE,    /*Trailer Encapsulation Option*/
    DHCP_OPTION_LONG,    /*35 ARP Cache Timeout Option*/
    DHCP_OPTION_BYTE,    /*Ethernet Encapsulation Option*/
    DHCP_OPTION_BYTE,    /*TCP Default TTL Option*/
    DHCP_OPTION_LONG,    /*TCP Keepalive Interval Option*/
    DHCP_OPTION_BYTE,    /*TCP Keepalive Garbage Option*/
    DHCP_OPTION_BYTEPARSE,    /*40 Network Information Service Domain Option*/
    DHCP_OPTION_IP_ADDRESS,    /*Network Information Servers Option*/
    DHCP_OPTION_IP_ADDRESS,    /*Network Time Protocol Servers Option*/
    DHCP_OPTION_BYTEPARSE,    /*Vendor Specific Information*/
    DHCP_OPTION_IP_ADDRESS,    /*NetBIOS over TCP/IP Name Server Option*/
    DHCP_OPTION_IP_ADDRESS,    /*45 NetBIOS over TCP/IP Datagram Distribution Server Option*/
    DHCP_OPTION_BYTE,    /*NetBIOS over TCP/IP Node Type Option*/
    DHCP_OPTION_BYTEPARSE,    /*NetBIOS over TCP/IP Scope Option*/
    DHCP_OPTION_IP_ADDRESS,    /*X Window System Font Server Option*/
    DHCP_OPTION_IP_ADDRESS,    /*X Window System Display Manager Option*/
    DHCP_OPTION_IP_ADDRESS,    /*50 Requested IP Address*/
    DHCP_OPTION_LONGPARSE,    /*IP Address Lease Time*/
    DHCP_OPTION_BYTE,    /*Option Overload*/
    DHCP_OPTION_BYTE,    /*DHCP Message Type*/
    DHCP_OPTION_IP_ADDRESS,    /*Server Identifier*/
    DHCP_OPTION_BYTEPARSE,    /*55 Parameter Request List*/
    DHCP_OPTION_BYTEPARSE,    /*Message*/
    DHCP_OPTION_SHORT,    /*Maximum DHCP Message Size*/
    DHCP_OPTION_LONG,    /*Renewal (T1) Time Value*/
    DHCP_OPTION_LONG,    /*Rebinding (T2) Time Value*/
    DHCP_OPTION_BYTEPARSE,    /*60 Vendor class identifier*/
    DHCP_OPTION_BYTEPARSE,    /*Client-identifier*/
    DHCP_OPTION_NOTSUPPORT,    /*��֧�ֵ�Option*/
    DHCP_OPTION_NOTSUPPORT,    /*��֧�ֵ�Option*/
    DHCP_OPTION_BYTEPARSE,    /*Network Information Service+ Domain Option*/
    DHCP_OPTION_IP_ADDRESS,    /*65 Network Information Service+ Servers Option*/
    DHCP_OPTION_BYTEPARSE,    /*TFTP server name*/
    DHCP_OPTION_BYTEPARSE,    /*Bootfile name*/
    DHCP_OPTION_IP_ADDRESS,    /*Mobile IP Home Agent option*/
    DHCP_OPTION_IP_ADDRESS,    /*Simple Mail Transport Protocol (SMTP) Server Option*/
    DHCP_OPTION_IP_ADDRESS,    /*70 Post Office Protocol (POP3) Server Option*/
    DHCP_OPTION_IP_ADDRESS,    /*Network News Transport Protocol (NNTP) Server Option*/
    DHCP_OPTION_IP_ADDRESS,    /*Default World Wide Web (WWW) Server Option*/
    DHCP_OPTION_IP_ADDRESS,    /*Default Finger Server Option*/
    DHCP_OPTION_IP_ADDRESS,    /*Default Internet Relay Chat (IRC) Server Option*/
    DHCP_OPTION_IP_ADDRESS,    /*75 StreetTalk Server Option*/
    DHCP_OPTION_IP_ADDRESS,    /*StreetTalk Directory Assistance (STDA) Server Option*/
    DHCP_OPTION_NOTSUPPORT,    /*��֧�ֵ�Option*/
    DHCP_OPTION_NOTSUPPORT,    /*78 ��֧�ֵ�Option*/
    /*�������� static ������δ��ֵ�ı����Զ���ʼ��Ϊ 0��
    ���Ժ���ľͲ���ʼ���� */
    };                    /*option������Ԫ*/

/* Added start by dongmingzhou 42828 at 2008-11-27 UGW9811V900R001C01 for ADDRESS SUBSYSTEM */

/*DHCPS״̬����ȫ�����ݽṹ*/
DHCPS_STATE_MACHINE_NODE  g_stDHCPSStateMachine[DHCPS_STATE_MAX + 1];

/*DHCPS��Ϣͳ����Ϣ��ȫ�����ݽṹ*/
DHCPS_STATE_MESSAGE_NODE  g_stDHCPSMsgNode[DHCPS_MSG_MAX];

/*DHCPS��USM�����Ϣ����ID*/
ULONG g_ulDHCPSUSMQueId    = 0;


/*��������*/
ULONG g_aulDHCPSDbgCnt[DHCPS_MAX_FAILURE_COUNTER];

/* Added end by dongmingzhou 42828 at 2008-11-27 UGW9811V900R001C01 for ADDRESS SUBSYSTEM */

/*����ʹ�õı���*/
ULONG g_ulDHCPSIpnum = 0; /*����ʹ��*/

STUB_SDB_CONTEXT_S g_stStubSdbContext = {0};

/* Modified start by dongmingzhou 42828 at 2009-02-18 UGWV9R1C1 for ��ַ���� */
ULONG g_ulUdpsStub = 0;
ULONG g_ulUsmStub = 0;
/* Modified end by dongmingzhou 42828 at 2009-02-18 UGWV9R1C1 for ��ַ���� */

ULONG g_ulDhcpsDebug = 0;

/*״̬���������ַ���ע����󲻵ó���40*/
UCHAR g_DHCPStateMachineDescrip[DHCPS_STATE_MAX][30] =
{
    "DHCPS_IDEL",
    "DHCPS_REQUESTIP",
    "DHCPS_OFFERED",
    "DHCPS_COMMITED",
    "DHCPS_RELAY",
};

/*��Ϣ��������ַ���ע����󲻵ó���50*/
/*lint -e785*/
UCHAR g_DHCPMsgNodeDescrip[DHCPS_MSG_MAX][50] =
{
    "DHCPS_RECIVE_DISCOVER",
    "DHCPS_RECIVE_REQUEST",
    "DHCPS_RECIVE_DECLINE",
    "DHCPS_RECIVE_RELEASE",
    "DHCPS_RECIVE_INFORM",
    "DHCPS_USM_ADDRESS_SUCCESS",
    "DHCPS_USM_ADDRESS_FAILURE",
    "DHCPS_USM_DEACTIVE",
    "DHCPS_TIMER",
    "DHCPS_RECIVE_NAK",
};
/*lint +e785*/

UCHAR g_DHCPStatiscDescrip[DHCPS_MAX_STATISC][50] =
{
    "DHCPS_RECEIVE_USM :" ,
    "DHCPS_RECEIVE_DPE :",
    "DHCPS_SEND_USM_APPLY :",
    "DHCPS_SEND_USM_RELEASE :",
    "DHCPS_SEND_MSG_OFFER :",
    "DHCPS_SEND_MSG_ACK :",
    "DHCPS_SEND_MSG_NAK :",
    "DHCPS_SEND_MSG_TOTAL :",
    "DHCPS_SEND_MSG_SUCC :",
    "DHCPS_STATISC_END :",
};

/* BEGIN: Modified by jixiaoming at 2011-03-02 */
VOS_SIZE_T  g_UEtoPGW_ulDHCPV4DiscoveryNumAddr =  VOS_NULL_PTR; /*����ͳ��PGW���յ�UEʼ����DHCPV4 Discovery��Ϣ����*/
VOS_SIZE_T  g_UEtoPGW_ulDHCPV4RequestNumAddr =  VOS_NULL_PTR;   /*����ͳ��PGW���յ�UEʼ����DHCPV4 Request��Ϣ����*/
VOS_SIZE_T  g_UEtoPGW_ulDHCPV4DeclineNumAddr =  VOS_NULL_PTR;   /*����ͳ��PGW���յ�UEʼ����DHCPV4 Decline��Ϣ����*/
VOS_SIZE_T  g_UEtoPGW_ulDHCPV4ReleaseNumAddr =  VOS_NULL_PTR;   /*����ͳ��PGW���յ�UEʼ����DHCPV4 Releases��Ϣ����*/
VOS_SIZE_T  g_UEtoPGW_ulDHCPV4InformNumAddr =  VOS_NULL_PTR;    /*����ͳ��PGW���յ�UEʼ����DHCPV4 Inform��Ϣ����*/
VOS_SIZE_T  g_PGWtoUE_ulDHCPV4OfferNumAddr =  VOS_NULL_PTR;     /*����ͳ��PGW���͸�UE��DHCPV4 Offer��Ϣ����*/
VOS_SIZE_T  g_PGWtoUE_ulDHCPV4AckNumAddr =  VOS_NULL_PTR;       /*����ͳ��PGW���͸�UE��DHCPV4 Ack��Ϣ����*/
VOS_SIZE_T  g_PGWtoUE_ulDHCPV4NakNumAddr =  VOS_NULL_PTR;       /*����ͳ��PGW���͸�UE��DHCPV4 Nak��Ϣ����*/


VOS_SIZE_T  g_UEtoSGW_ulDHCPV4DiscoveryNumAddr =  VOS_NULL_PTR;     /*����ͳ��SGW���յ�UEʼ����DHCPV4 Discovery��Ϣ����*/
VOS_SIZE_T  g_UEtoSGW_ulDHCPV4RequestNumAddr =  VOS_NULL_PTR;       /*����ͳ��SGW���յ�UEʼ����DHCPV4 Request��Ϣ����*/
VOS_SIZE_T  g_UEtoSGW_ulDHCPV4DeclineNumAddr =  VOS_NULL_PTR;       /*����ͳ��SGW���յ�UEʼ����DHCPV4 Decline��Ϣ����*/
VOS_SIZE_T  g_UEtoSGW_ulDHCPV4ReleaseNumAddr =  VOS_NULL_PTR;       /*����ͳ��SGW���յ�UEʼ����DHCPV4 Releases��Ϣ����*/
VOS_SIZE_T  g_UEtoSGW_ulDHCPV4InformNumAddr =  VOS_NULL_PTR;        /*����ͳ��SGW���յ�UEʼ����DHCPV4 Inform��Ϣ����*/
VOS_SIZE_T  g_SGWtoUE_ulDHCPV4OfferNumAddr =  VOS_NULL_PTR;         /*����ͳ��SGW���͸�UE��DHCPV4 Offer��Ϣ����*/
VOS_SIZE_T  g_SGWtoUE_ulDHCPV4AckNumAddr =  VOS_NULL_PTR;           /*����ͳ��SGW���͸�UE��DHCPV4 Ack��Ϣ����*/
VOS_SIZE_T  g_SGWtoUE_ulDHCPV4NakNumAddr =  VOS_NULL_PTR;           /*����ͳ��SGW���͸�UE��DHCPV4 Nak��Ϣ����*/
/* END: Modified by jixiaoming at 2011-03-02 */

ULONG g_ulGreProType = 0;

/* BEGIN: Added by zhangjinquan at 2011-10-06 for log optimize */
/**********DHCPV4S��־ע��id*******************/
ULONG g_ulDhcpv4sLogRecordRegId = 0;
/* END: Added by zhangjinquan at 2011-10-06 for log optimize */

