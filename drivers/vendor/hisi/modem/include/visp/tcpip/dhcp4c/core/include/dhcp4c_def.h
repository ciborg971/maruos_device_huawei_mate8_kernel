/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              dhcp4c_def.h
*
*  Project Code: VISP1.5
*   Module Name: DHCP client Module
*  Date Created: 2004-05-19
*        Author: tangcongfeng(36956)
*   Description: ������DHCPģ�����õĺ�
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2004-05-19 tangcongfeng(36956)      Creat the first version.
*
*******************************************************************************/

#ifndef _DHCP4C_DEF_H_
#define _DHCP4C_DEF_H_


#ifdef  __cplusplus
extern "C"{
#endif


#define DHCP4C_SNAME_LEN    64
#define DHCP4C_FILE_LEN     128
#define DHCP4C_CHADDR_LEN   16


/* FSM UP/DOWN ״̬*/
#define DHCP4C_FSM_UP   0
#define DHCP4C_FSM_DOWN 1

#define DHCP4C_BOUND    0
#define DHCP4C_UNBOUND  1

#define DHCP4C_SESSION_SMOOTHED   0
#define DHCP4C_SESSION_UNSMOOTHED 1

/* FSM �¼����� */
#define DHCP4C_FSM_EV_IPCNFLCT          1
#define DHCP4C_FSM_EV_IFPHYCHANGE       2
#define DHCP4C_FSM_EV_START             3
#define DHCP4C_FSM_EV_RENEW             4
#define DHCP4C_FSM_EV_RELEASE           5
#define DHCP4C_FSM_EV_STOP              6
#define DHCP4C_FSM_EV_IFDELETE          7

/* �¼� λ */
#define EV_DHCP4C_CMD   ((ULONG)1)
#define EV_DHCP4C_CNTRL ((ULONG)1<<1)


/* Add by l60006581 for A82D01698, 2006-05-27 */
#define DHCP4C_INTERFAC_LOW    0    /* ͨ��DHCP��ȡ�ĵ�ַ���ȼ����ڽӿ�ԭ�еĵ�ַ���ȼ� */
#define DHCP4C_INTERFAC_HIG    1    /* ͨ��DHCP��ȡ�ĵ�ַ���ȼ����ڽӿ�ԭ�еĵ�ַ���ȼ� */

#define DHCP4C_MAX_RESENT      4

#define DHCP4C_HEAD_LEN        236

/* DHCP��Ϣ���� */
#define DHCP4C_BOOTREQUEST    1
#define DHCP4C_BOOTREPLY      2

/* ��̫��Ӳ������ */
#define DHCP4C_HARDTYPE_ETH   1

/* RFC3456 DHCP over IPSEC�涨DHCPʹ�õ�Ӳ������ */
#define DHCP4C_HARDTYPE_DHCP_OVER_IPSEC   31

/* ��̫��Ӳ����ַ���� */
#define DHCP4C_HARDLEN_ETH    6

/* �㲥��־ */
#define DHCP4C_BROADCAST_FLAGS 0x8000

/* ������־ */
#define DHCP4C_UNICAST_FLAGS      0

#define DHCP4C_MAGIC_COOKIE   "\143\202\123\143" /* 8���ơ�����ʱ�����ĸ��ֽڵ��ڴ��ϵĴ洢ֵΪ0x63,0x82,0x053,0x63 */
#define MAGIC_COOKIE_LEN      4


/* DHCP�� Option�� overload ��־λ */
#define DHCP4C_OVERLOAD_FILE_FLAG   1
#define DHCP4C_OVERLOAD_SNAME_FLAG  2

/* ѡ��������Ϊ255 */
#define DHCP4C_MAX_OPTIONCODE       255
#define DHCP_OPTIONMAXLEN           512      /*DHCP ѡ����󳤶�*/

/* ��ѡ����DHCP������״̬ */
#define DHCP4C_OPTION_MUSTNOT        0
#define DHCP4C_OPTION_MUST           1
#define DHCP4C_OPTION_MAY            2
#define DHCP4C_OPTION_CONDITIONAL    3


/* UDP���ݰ����ͻ�������С */
#define DHCP4C_UDPBUF_MAXLEN         2048

#define DHCP4C_SERVER_PORT           0x43            /* dhcp server port */
#define DHCP4C_CLIENT_PORT           0x44            /* dhcp client port */

/* ��ǿDHCP Client������. */
#define  DHCP4C_MAXHDR_LEN   80     /* ����DHCP Client����MBUFʱԤ�����ײ����� */
#define  DHCP4C_UDPIPHDR_LEN      28   /* DHCP Client���ĵ�UDP, IP���ײ����� */
#define  DHCP4C_TTL   255           /* DHCP Client���ĵ�TTLֵ  */
#define  DHCP4C_TOS   0             /* DHCP Client���ĵ�TOSֵ  */

/* �ط���ʱ��ʱ�ӳ�ֵ */
#define DHCP4C_TIMER_INITAL    4000
/* Discover������������Ӧʱ�����¿�ʼDiscover���ķ��͵ļ�����ο�Windows����Ϊ5���� */
#define DHCP4C_TIMER_INTERVAL    5*60*1000


#define DHCP4C_TIMER_LOOP      1
#define DHCP4C_TIMER_NOLOOP    0

/* ARPREQUEST ����0.5�뷢��һ�μ��IP�Ƿ��ͻ*/
#define DHCP4C_ARPECHO_TIMEOUT_VALUE        500

/*�û�����5s ��鶨ʱ��*/
#define DHCP4C_CFGCHECK_TIMEOUT_VALUE        5000

/*Added by lufeng for DHCP4C config, 2006-04-28 */
/* �������־���� */
#define DHCP4C_CONFIGCIADDR  0x01
#define DHCP4C_CONFIGCID     0x02
#define DHCP4C_CONFIGVSI     0x04
#define DHCP4C_CONFIGDEFAULTIP 0x08
/* Added by y171195(z171897) 2010-11-03 for DHCP Vlan Scanning Begin */
#define DHCP4C_CONFIGVLANSCANNING 0x10
/* Added by y171195(z171897) 2010-11-03 for DHCP Vlan Scanning End */

/* �㲥��ַ */
#define DHCP4C_BROADCAST_IPADDR        0xffffffffL
#define DHCP4C_MAC_LEN                 6

#if (VRP_OS_WINDOWS == VRP_YES)
#define DHCP4C_DEFAULT_FILE_LEASE      "c:/lease.bak"
#endif

#define DHCP4C_DELETE_DNSIP  1
#define DHCP4C_ADD_DNSIP     0


#define DHCP4C_ISRENEWING    0x01 /* renewing interface flag */
#define DHCP4C_RENEW_TIMOUT  0x02 /* renew timer time out */

#define VOS_TIMER_DEL_ON_TIMEOUTMSG  4

#define DHCP4C_MAX_SESSION   64 /* ���session ��*/

/* DHCP4Cģ��ʹ�õ�SIDͳһ�ڴ˶��� */

#define SID_COMP_DHCP4C_DLL_S             1  /* DLL_S */
#define SID_COMP_DHCP4C_SESSION_S         2  /* DHCP4C_SESSION_S */
#define SID_COMP_DHCP4C_CONFIGINFO_S      3  /* DHCP4C_CONFIGINFO_S */
#define SID_COMP_DHCP4C_SNDBUF            4  /* DHCP4C�Ự���Ļ��� */
#define SID_COMP_DHCP4C_DEBUGINFO_S       5  /* DHCP4C_DEBUGINFO_S */
#define SID_COMP_DHCP4C_VIRTUAL_S         6  /* DHCP4C��ӿ���������Ϣ */
#define SID_COMP_DHCP4C_LEASE_S           7  /* DHCP4C���ڽڵ�DHCP4C_LEASE_NODE_S */

/* end of SID */

#ifndef MACADDRLEN
#define MACADDRLEN                6
#endif

#define DHCP_ETHERTYPE_IP         0x0800  /* IPЭ�鱨�� */

#ifdef  __cplusplus
}
#endif  /* end of __cplusplus */

#endif  /* end of _DHCP4C_DEF_H_ */


