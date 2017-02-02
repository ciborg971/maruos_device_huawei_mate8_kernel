/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              tcpip_adapter.h
*
*  Project Code: VISPV100R005
*   Module Name: PUBILC
*  Date Created: 2004-3-8
*        Author: zhang hong yan(19316)
*   Description: VISP�Ŀɲü�����ͷ�ļ�,��Ҫ���û�ʹ�ã�VISP�ڲ����벢��������ͷ�ļ�.
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  -----------------------------------------------------------------------------
*  2004-03-08  zhang hong yan(19316)  Creat the first version.
*  2006-04-27  wang xin(03278)     ���ݱ�̹淶�����ļ����й淶������
*  2008-03-03  liangjicheng        BC3D01254 ɾ��RTPģ��
*******************************************************************************/
/*
  ˵����
      1.����Ʒ������û��Dopra������ƣ��뽫��TCPIP_COMP_INITIAL����ΪVRP_YES�����򣬽��䶨��ΪVRP_NO��
      2.����ƷҪӦ��ģ��X���򽫺�TCPIP_COMP_REGISTER_X����ΪVRP_YES�����򣬽��䶨��ΪVRP_NO��
      3.����Ʒ��TCPIP_COMP_REGISTRE_X����ΪVRP_YES����һ��Ҫ��MakeFile�ļ��м����ģ��X��Lib������ӡ�
*/

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _TCPIP_ADAPTER_H_
#define _TCPIP_ADAPTER_H_

/*If Dopra1.5B100 or above used, define this macro VRP_NO; Otherwise make it VRP_YES.*/
#define TCPIP_COMP_INITIAL               VRP_YES

/*Macro ONLY for this file.To determine if the component should be registered.*/
#define TCPIP_COMP_REGISTER_IPSEC6       VRP_YES   /*IPSEC6*/
#define TCPIP_COMP_REGISTER_ETH          VRP_NO   /*ETHARP*/
#define TCPIP_COMP_REGISTER_PPP          VRP_NO   /*PPP*/
#define TCPIP_COMP_REGISTER_IPV6         VRP_YES    /*IPv6*/
#define TCPIP_COMP_REGISTER_PING         VRP_NO   /*PING*/
#define TCPIP_COMP_REGISTER_DNSC         VRP_YES   /*Dns Client*/
#define TCPIP_COMP_REGISTER_DHCP4C       VRP_NO    /*Dhcp4 Client. no eth,no DHCP4c.*/
#define TCPIP_COMP_REGISTER_ACL4         VRP_YES   /*ACL4*/
#define TCPIP_COMP_REGISTER_ACL6         VRP_YES   /*ACL6*/
#define TCPIP_COMP_REGISTER_ACLFW        VRP_NO   /*ACLFW*/
#define TCPIP_COMP_REGISTER_TRACEROUTE   VRP_NO   /*TraceRout*/
#define TCPIP_COMP_REGISTER_IPHC         VRP_NO    /*IPHC*/
#define TCPIP_COMP_REGISTER_PPPOECLIENT  VRP_NO    /*PPPoE Client*/
#define TCPIP_COMP_REGISTER_MP           VRP_NO    /*Multilink Protocol*/
#define TCPIP_COMP_REGISTER_PPPMUX       VRP_NO    /*PPPMUX*/
#define TCPIP_COMP_REGISTER_TCP4         VRP_YES   /*Tcp4*/
#define TCPIP_COMP_REGISTER_UDP4         VRP_YES   /*Udp4*/
#define TCPIP_COMP_REGISTER_TRUNK        VRP_NO   /*Trunk*/
#define TCPIP_COMP_REGISTER_POES         VRP_NO    /*POES*/
#define TCPIP_COMP_REGISTER_DHCP4R       VRP_NO    /*Dhcp4 Relay.*/
#define TCPIP_COMP_REGISTER_IPSEC        VRP_YES    /*IPSEC*/
#define TCPIP_COMP_REGISTER_IKEV1        VRP_YES    /*IKEV1*/
#define TCPIP_COMP_REGISTER_IKEV2        VRP_YES    /*IKEV2*/
#define TCPIP_COMP_REGISTER_DHCP6C       VRP_NO    /* DHCP6Client,�����ע��DHCP6C,��ͬʱע��IPV6,������Ч */
#define TCPIP_COMP_REGISTER_DHCP6R       VRP_NO    /* DHCP6Relay, �����ע��DHCP6R,��ͬʱע��IPV6,������Ч */
#define TCPIP_COMP_REGISTER_BFD          VRP_NO   /* BFD�ü��� */
#define TCPIP_COMP_REGISTER_OSICP        VRP_NO    /* OSICP�ü��� */
#define TCPIP_COMP_REGISTER_OAM3AH       VRP_NO    /* 3AH�ü��� */
#define TCPIP_COMP_REGISTER_OAM1AG       VRP_NO    /* 1AG�ü��� */
#define TCPIP_COMP_REGISTER_IGMP         VRP_NO    /* IGMP�ü���*/
#define TCPIP_COMP_REGISTER_PTP          VRP_NO    /* PTP(1588v2)Э��ü��� */
#define TCPIP_COMP_REGISTER_VLAN         VRP_NO    /* VLAN�ü���*/
#define TCPIP_COMP_REGISTER_IPOA         VRP_NO
#define TCPIP_COMP_REGISTER_VLINK        VRP_NO
#define TCPIP_COMP_REGISTER_DCLBASE      VRP_NO
#define TCPIP_COMP_REGISTER_RIP          VRP_NO   /*RIP�ɲü�*/
#define TCPIP_COMP_REGISTER_OSPF         VRP_NO   /*OSPF�ɲü�*/
#define TCPIP_COMP_REGISTER_BFDEXT       VRP_NO
#define TCPIP_COMP_REGISTER_RTP          VRP_NO
#define TCPIP_COMP_REGISTER_L2IF         VRP_NO   /* L2IF�ü���*/
#define TCPIP_COMP_REGISTER_MSTP         VRP_NO   /* MSTP�ü���*/
#define TCPIP_COMP_REGISTER_VRRP         VRP_NO   /* VRRP�ü���*/
#define TCPIP_COMP_REGISTER_VRF          VRP_NO   /* VRF�ü���*/
#define TCPIP_COMP_REGISTER_EAP          VRP_NO   /* EAP�ü��� */
#define TCPIP_COMP_REGISTER_SYNCE        VRP_NO   /* SyncE�ü��� */
#define TCPIP_COMP_REGISTER_ARPGUARD     VRP_NO  /* ARP����ƭ�ü��� */
#define TCPIP_COMP_REGISTER_LLDP         VRP_NO  /* LLDP�ü��� */
#define TCPIP_COMP_REGISTER_TWAMP        VRP_NO   /* TWAMP component registeration */
#define TCPIP_COMP_REGISTER_POLICYRT     VRP_NO  /* source policy route registration */
#define TCPIP_COMP_REGISTER_NSR          VRP_NO   /* NSR���Բü��� */
#define TCPIP_COMP_REGISTER_VRF6         VRP_NO   /* VRF6*/

#endif /*_TCPIP_ADAPTER_H_*/

#ifdef __cplusplus
}
#endif

