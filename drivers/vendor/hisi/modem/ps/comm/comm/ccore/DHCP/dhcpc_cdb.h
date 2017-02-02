
#ifndef __DHCPC_CDB_H__
#define __DHCPC_CDB_H__

#ifdef   __WIN32_PLATFORM__
#pragma pack(push, 1)
#endif

#define DHCP_SERVER_GROUP_MAX_NUM   1000

/*congjing DHCPC*//*****************************/
#define DHCP_PRISRV_TIMER_ON    1   /* ��ʱ������ */
#define DHCP_PRISRV_TIMER_DOWN  0   /* ��ʱ���ر� */
#define DHCP_PRISRV_TEST_ON     1   /* ���÷�����̽��� */
#define DHCP_PRISRV_TEST_DOWN   0   /* ���÷�����̽��ر� */

/* BEGIN: Added by jixiaoming at 2011-09-27 for  CR20101222007 */
#define DHCP_NO_ALARM                      0               /* DHCP û�з�����·�ϸ澯 */
#define DHCP_ALARMED                       1               /* DHCP �Ѿ�������·�ϸ澯 */
/* END: Added by jixiaoming at 2011-09-27 for  CR20101222007 */

#define DHCP_SEVER_NORMAL                         0 /*������״̬����*/
#define DHCP_SEVER_ABNORMAL                       1 /*����������Ӧ*/      
#define DHCP_SEVER_TRY                            2 /*������̽�⿪��*/
#define DHCP_SEVER_GROUP_IS_IPV6                  1 /*dhcp����������*/
#define DHCP_SEVER_GROUP_IS_IPV4                  2 /*dhcp����������*/
#define DHCP_SEVER_RETRANSMIT_NUM_NORMAL          1 /*�������������Ϣ����*/
#define DHCP_SEVER_RETRANSMIT_NUM_INI             0 /*�������������Ϣ��ʼ����*/
#define DHCP_SEVER_INVALID_IP                              0 /*��Чip*/
#define DHCPC_V_INTERFACE_NAME_MAX_LEN  19

/* ����DHCP����V�ӿڸ��� */
typedef struct
{
    UCHAR       aucIfName[DHCPC_V_INTERFACE_NAME_MAX_LEN+1];     /* V�ӿ����� */
    ULONG       ulPeerIp;       /* �Զ�IP��ַ */
    UCHAR       aulPeerIPv6[40];       /*�Զ�IPv6��ַ */
    ULONG       ulMsgType;       /* ��Ϣ���� */
    ULONG       ulPeerIpTypeOp;       /* �Զ˵�ַ����ѡ�� */
}VOS_PACKED DHCPC_IFTRC_V_FILTER; 

#define VOS_ERR_GTPC_ERR_BASE    20000
#define VOS_ERR_GTPC_ERR_LOGIC_INTERFACE             (VOS_ERR_GTPC_ERR_BASE+31)    /* �߼��ӿ����벻�Ϸ����߽ӿڲ����� */
#define VOS_ERR_GTPC_ERR_PEER_IP                     (VOS_ERR_GTPC_ERR_BASE+33)    /* �Զ�IP���� */


#define LAP_DHCP_SERVER_GROUP_NAME_MAX_LENGTH    32
#define LAP_VPN_INSTANCE_NAME_MAX_LENGTH         31

typedef struct tagLAPDHCPCFG
{
     ULONG aulPrimaryServerIp[4];        /*  ����������IP ��ַ*/
     ULONG aulSecondaryServerIp[4];        /*  ����������IP ��ַ*/
     ULONG ulVpnIndex;                /*  DHCP ��������������VPN ʵ������*/  
     UCHAR aucDhcpServerGrpName[LAP_DHCP_SERVER_GROUP_NAME_MAX_LENGTH + 1];        /*  DHCP������������� */
     UCHAR  ucLeaseTime;            /* ��ַ���� */
     USHORT usDhcpServerGrpIndex;    /* DHCP���������index */
    /* BEGIN: Added by jixiaoming at 2011-09-27 for  CR20101222007 */
     UCHAR aucVpnName[LAP_VPN_INSTANCE_NAME_MAX_LENGTH+1]; /*  DHCP ��������������VPN ʵ������*/ 
    /* END: Added by jixiaoming at 2011-09-27 for  CR20101222007 */
     UCHAR ucIsDHCPv6;             /* �Ƿ�DHPCv6���: 1--��ipv6 ,2 -- ��ipv4 ��0--Ĭ��group*/
     UCHAR ucRetransmitNum;        /* ���õ�����ط���������Χ0-5��Ĭ��3 */
     UCHAR ucRetransmitTimeOut;    /* ���õ��ط��������Χ1-10��Ĭ��3 */
     UCHAR ucReserve;              /* �����ֶ� */
}LAP_DHCP_CFG_S;

#ifdef   __WIN32_PLATFORM__
#pragma pack(pop, 1)
#endif

#endif /* end of __DHCPC_CDB_H__ */
