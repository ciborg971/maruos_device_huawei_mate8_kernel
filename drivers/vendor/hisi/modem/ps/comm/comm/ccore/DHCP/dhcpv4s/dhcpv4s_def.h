
/************************************************************************
 *                                                                      *
 *                             DHCPS_DEF.H                               *
 *                                                                      *
 *  Project Code:       DHCP                                            *
 *  Create Date:        2002/04/10                                      *
 *  Author:                                                             *
 *  Modify Date:                                                        *
 *  Document:  ��DHCP��������ϸ���˵���顷                             *
 *             ��DHCP��������Ҫ���˵���顷                             *
 *  Function:                                                           *
 *  Others:                                                             *
 *----------------------------------------------------------------------*
 *                                                                      *
 *             Copyright 2000 - 2002 HuaWei Tech, Inc.                  *
 *                      ALL RIGHTS RESERVED                             *
 *                                                                      *
 ***********************************************************************/
#ifndef _DHCPV4S_DEF_H_
#define _DHCPV4S_DEF_H_

#define PPP_IP 0x0021
#define PPP_IP6 0x0057
#define PPP_VSNP 0x005b

/*��������ʹ�õĺ�*/
#define DHCPS_DFT_QUEUE_LENGTH 128
#define DHCPS_MAX_SHARE_QUE_ATTACH_NUM 100
#define DHCPS_FLOWCONTROL_MAX 20

#define DHCPS_QUEUE_LENGTH 1024

#define DHCPS_RECV_MSG_MAXLEN 2048  /* ������Ϣ��󳤶� */

#define DHCPS_MAX_LEASE_TIMER_LEN  (31 * 24 * 60)          /* ��λ:��. */
#define DHCPS_TIMER_LEN_UNLIMITED   0XFFFFFFFF

/* BEGIN: Added by jixiaoming at 2011-05-04 */
 /* 
  * dhcps ״̬��STATE Timer Ҫ��ʱ���ʱ����ĿǰȡOFFERED״̬��ʱ��ʱ��(��λ:��) .
  */
#define DHCPS_MAX_STATE_TIMER_LEN (5 * 60)

#define DHCPS_STATE_TIMER_PACE 500            /* ״̬��ʱ���Ĳ���(����) */
#define DHCPS_LEASE_TIMER_PACE (500 * 60)       /* ��Լ��ʱ���Ĳ���(����) */

/* STATEʱ��۵Ĳ�λ��  */
#define DHCPS_MAX_STATE_TIMER_LINKLIST (5000 * 2 + 1)

/* LEASEʱ��۵Ĳ�λ�� */
#define DHCPS_MAX_LEASE_TIMER_LINKLIST (65535 * 2 + 1)

/* ��׼��ʱ�ۼӻ��������ֵ */
#define DHCPS_STATE_TMR_TIME_OVERFLOW (0xFFFFFFFF-(0xFFFFFFFF%(DHCPS_MAX_STATE_TIMER_LINKLIST)))
#define DHCPS_LEASE_TMR_TIME_OVERFLOW (0xFFFFFFFF-(0xFFFFFFFF%(DHCPS_MAX_LEASE_TIMER_LINKLIST)))
/* END: Added by jixiaoming at 2011-05-04 */

#define DHCPS_MAX_STATISC 10 /*200*/

#define DHCPS_UDPBUF_MAXLEN                2048

/*dhcp���ݰ��а�ͷ(����option����)�ĳ����ܺ�*/
#define  DHCPS_HEAD_LEN            236

#define DHCPS_OPTION_MAXLEN                 576

/*DHCP HEAD*/
#define DHCPS_BOOTREQUEST    1
#define DHCPS_BOOTREPLY      2

#define DHCPS_ETHERNET    0x01         /*MAC����ΪETHERNET*/
#define DHCPS_MAC_LEN            6

#define   DHCP_SERVER_PORT   67 
#define   DHCP_CLIENT_PORT   68
#define   DHCP_RELAY_PORT    DHCP_SERVER_PORT

/*=======================DCHP_OPTION ���ֵĺ궨��=================*/

#define DHCPS_OPTIONDATA_LEN       64

#define DHCP_BROADCAST_BIT  0x8000

/*dhcp���ݰ���option������ǰ���cookie��־*/
#define  DHCPS_OPTIONS_COOKIE  "\143\202\123\143" 
/* ������8���Ʊ�ʾ��ʵ���ϼ���ʮ�����Ƶ� 0X63825363 */

/* ϵͳ��ȱʡ��Լʱ��1�죬ת��Ϊ��λ�����ֵ */
#define DHCP_DEFAULT_LEASE_TIME_SECONDS     86400

/* DHCP�� Option�� overload ��־λ */
#define DHCP_OVERLOAD_FILE_FLAG         1
#define DHCP_OVERLOAD_SNAME_FLAG        2

/*dhcp���ݰ�������*/ 
#define DHCP_DHCPDISCOVER       1
#define DHCP_DHCPOFFER      2
#define DHCP_DHCPREQUEST        3
#define DHCP_DHCPDECLINE        4
#define DHCP_DHCPACK            5
#define DHCP_DHCPNAK            6
#define DHCP_DHCPRELEASE        7
#define DHCP_DHCPINFORM         8


/*dhcp���ݰ���option��ѡ�����*/
#define DHCP_OPTION_PAD                             0
#define DHCP_OPTION_SUBNET_MASK                     1
#define DHCP_OPTION_END                             255
#define DHCP_OPTION_LEASE_TIME                      51
#define DHCP_OPTION_REQUESTED_IP                    50
#define DHCP_OPTION_OVERLOAD                        52
#define DHCP_OPTION_MESSAGE_TYPE                    53
#define DHCP_OPTION_SERVERID                        54
#define DHCP_OPTION_MAXMESSAGE_SIZE                 57
#define DHCP_OPTION_RENEWAL_TIME                           58
#define DHCP_OPTION_REBIND_TIME                            59

#define DHCP_OPTION_PARAMETER_REQUEST_LIST                 55
#define DHCP_OPTION_RAPID_COMMIT                 80


/*�û��Զ���Option������*/
#define DHCP_OPTIONFORMAT_ASCII                     1
#define DHCP_OPTIONFORMAT_HEX                       2 
#define DHCP_OPTIONFORMAT_IP                        3 
#define DHCP_OPTIONFORMAT_NULL                      0 

/*����ѡ�������:
��֧�ֵġ����ֽڽ�����˫�ֽڽ��������ֽڽ���*/
#define DHCP_OPTION_NOTSUPPORT      0
#define DHCP_OPTION_BYTEPARSE       1
#define DHCP_OPTION_SHORTPARSE      2
#define DHCP_OPTION_LONGPARSE       3
#define DHCP_OPTION_SHORT            4    /*RFC ��ָ��ֻ��2���ֽ�*/
#define DHCP_OPTION_BYTE             5
#define DHCP_OPTION_LONG             6
#define DHCP_OPTION_IP_ADDRESS       7

  
/* RFC����� DHCP ��С�����ݰ��ĳ���(����DHCPͷ��Option)*/
#define DHCP_MIN_LEN                576


/*״̬����Ҫ, �Ƿ�Ҫ����??*/
/* DHCP��Լ״̬���� */  
#define DHCP_LEASE_AVAILABLE                1
#define DHCP_LEASE_OFFERED                  2
#define DHCP_LEASE_COMMITED                 4
#define DHCP_LEASE_CONFLICT_DELAYSECONDS    3600


/* Added start by dongmingzhou 42828 at 2008-12-01 UGW9811V900R001C01 for ADDRESS SUBSYSTEM */
#define DHCPS_TIMER_LENGTH_WAITUSM                         20
#define DHCPS_TIMER_LENGTH_WAITREAUESTMSG           300
#define DHCPS_TIMER_LENGTH_WAITLEASE                      0xFFFFFFFF
/* Added end by dongmingzhou 42828 at 2008-12-01 UGW9811V900R001C01 for ADDRESS SUBSYSTEM */


/*��USM֮��Ķ��г���*/
#define DHCPS_INTERNAL_MSG_QUE_LEN          1024

#define DHCPS_INNER_EVENT   1
#define DHCPS_PF_EV         (1<<2)
#define DHCPS_USM_EV         (1<<3)


/* Added start by zhangxiujuan00108044 at 2008-12-22 UGW9811V900R001C01 for ADDRESS SUBSYSTEM */
/*DHCPS��USM֮����¼�λ*/
#define  DHCPS_EV_BASE        1                            /* ������Ϣ�¼�λ����ַ */
#define  DHCPS_USM_EV        DHCPS_EV_BASE         /* dhcps�յ�USMģ����Ϣ���¼�  */

/*Ӧ�÷���USM����*/
/*DHCPS��USM����IP��ַ���¼�λ*/
#define USM_DHCPS_REQ_EVENTBIT  (1 << 5)
/* Added end by zhangxiujuan00108044 at 2008-12-22 UGW9811V900R001C01 for ADDRESS SUBSYSTEM */

/*DHCPS��Լʹ�ñ�־*/
#define DHCPS_LEASE_NOTUSED       0
#define DHCPS_LEASE_USED             1

/*----------------------------------*/
#define IP_HEADER_LENGTH 20
#define UDP_HEADER_LENGTH 8





/*FSM���õĺ�  */

#define DHCPS_FSM_CHECKMSG(P1,P2,U1)                \
    /*����ж�*/                                                 \
    if( ((P1) == NULL) || ((P2) == NULL) )                           \
    {                                                                            \
        VOS_Assert(0);                                                   \
        DHCPS_InternalBranchCounter((U1));                    \
        return VOS_ERR;                                                  \
    }                                                                             \

#define DHCPS_FSM_GETLEASE(P1,P2,P3,U1)        \
    /*ȡ��Լָ��*/                                      \
    (P1) = (P2)->pstLease;                                          \
    if( (P1) == NULL )                                                 \
    {                                                                      \
        VOS_Assert(0);                                             \
        (P3)->ulResult = DHCPS_STATE_CHANGE_ERR;      \
        DHCPS_InternalBranchCounter((U1));                \
        return VOS_ERR;                                              \
    }                                                                         \

#define DHCPS_FSM_CHECKLEASEUSED(P1,P2,U1)       \
    /*�ж���Լ��ʹ�ñ�־*/                       \
    if( (P1)->ucUsed != DHCPS_LEASE_USED)                     \
    {                                                                            \
    (P1) = (P2)->pstAnalyzedPacket;                                    \
    if(NULL == (P1))                                                          \
    {                                                                             \
        VOS_Assert(0);                                                    \
        (P3)->ulResult = DHCPS_STATE_CHANGE_ERR;           \
        DHCPS_InternalBranchCounter((U1));                    \
        return VOS_ERR;                                                 \
    }
#define DHCPS_FSM_CHECKRESULT(ulRet,P1,U1)     \
    /*�жϺ����ķ���ֵ*/                        \
    if((ulRet) != VOS_OK)                                            \
    {                                                                       \
        VOS_Assert(0);                                              \
        (P1)->ulResult = DHCPS_STATE_CHANGE_ERR;      \
        DHCPS_InternalBranchCounter((U1));                \
        return VOS_ERR;                                              \
    }                                                                         \

#define DHCPS_CHECKLEASEPOINT(P1,U1)                  \
    /*����ж�*/                                                         \
    if( NULL == (P1))                                                               \
    {                                                                                    \
        VOS_DBGASSERT(0);                                                   \
        DHCPS_InternalBranchCounter((U1));                                \
        return VOS_ERR;                                                            \
    }                                                                                       \

#define DHCPS_CHECKLEASEUSED(P1,U1)       \
    /*�ж���Լ��ʹ�ñ�־*/                       \
    if( (P1)->ucUsed != DHCPS_LEASE_USED)                     \
    {                                                                            \
        VOS_Assert(0);                                                   \
        DHCPS_InternalBranchCounter((U1));                    \
        return VOS_ERR;                                                 \
    }                                                                            \

/* Added start by dongmingzhou 42828 at 2009-04-21 UGWV9R1C1 for ���� */
/*ֹͣ ����*/
/*0          0         */
/*0          1         */
/*1          0         */
/*1          1         */
#define DHCPS_HA_LEASETIME_INVALID          0    
#define DHCPS_HA_LEASETIME_START            1    
#define DHCPS_HA_LEASETIME_STOP             2    
#define DHCPS_HA_LEASETIME_STOPSTART        3    
/* Added end by dongmingzhou 42828 at 2009-04-21 UGWV9R1C1 for ���� */


#define DHCPS_IPADDR_INVALID(IPADDR) ((0 == IPADDR) || (VOS_NULL_DWORD == IPADDR))

#define DHCPS_NTOH_IPV6_ADDR(StIpv6Addr)   \
    (StIpv6Addr).s6_addr16[0] = VOS_HTONS((StIpv6Addr).s6_addr16[0]);\
    (StIpv6Addr).s6_addr16[1] = VOS_HTONS((StIpv6Addr).s6_addr16[1]);\
    (StIpv6Addr).s6_addr16[2] = VOS_HTONS((StIpv6Addr).s6_addr16[2]);\
    (StIpv6Addr).s6_addr16[3] = VOS_HTONS((StIpv6Addr).s6_addr16[3]);\
    (StIpv6Addr).s6_addr16[4] = VOS_HTONS((StIpv6Addr).s6_addr16[4]);\
    (StIpv6Addr).s6_addr16[5] = VOS_HTONS((StIpv6Addr).s6_addr16[5]);\
    (StIpv6Addr).s6_addr16[6] = VOS_HTONS((StIpv6Addr).s6_addr16[6]);\
    (StIpv6Addr).s6_addr16[7] = VOS_HTONS((StIpv6Addr).s6_addr16[7]);

#endif
