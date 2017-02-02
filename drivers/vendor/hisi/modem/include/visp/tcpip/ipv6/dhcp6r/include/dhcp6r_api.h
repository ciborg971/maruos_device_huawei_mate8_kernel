/*******************************************************************************
*
*
*                Copyright 2011, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              dhcp6r_api.h
*
*  Project Code: VISP V2R3C06
*   Module Name: DHCPv6
*  Date Created: 2011-7-19
*        Author: PBQ(RT24429)
*   Description: dhcp6rģ������ṩ��ͷ�ļ�
*
*-------------------------------------------------------------------------------
*  Modification  History
*  DATE          NAME              DESCRIPTION    
*-------------------------------------------------------------------------------
*  2011-7-19     PBQ(RT24429)      Create the first version.
*
*******************************************************************************/

#ifndef _DHCP6R_API_H_
#define _DHCP6R_API_H_

#ifdef __cplusplus
    extern "C"{
#endif  /* end of __cplusplus */

/* ʹ��ȥʹ�� */
#define DHCP6R_DISABLED             0
#define DHCP6R_ENABLED              1

/* �м�ģʽ */
#define DHCP6R_FORWORD_CYCLE        0x0     /* �ֵ���ʽ */
#define DHCP6R_FORWORD_BROADCAST    0x1     /* �㲥��ʽ */

/* ������Ϣ���� */
#define DHCP6R_DEBUG_OFF            0x0     /* �رյ��Կ��� */
#define DHCP6R_DEBUG_PAKCET         0x1     /* Packet������Ϣ���Կ��� */
#define DHCP6R_DEBUG_ERROR          0x2     /* Error���Կ��� */
#define DHCP6R_DEBUG_ALL            0x3     /* ǰ���߶��� */
#define DHCP6R_DEBUG_ALL_DETAIL     0x7     /* ǰ���߶����Ҵ�ӡ������ϸ��Ϣ */

/* �����û��ӿڴ����� */
enum enDHCP6RErrInfo
{
    DHCP6R_OK           = VOS_OK,
    DHCP6R_ERR          = VOS_ERR,
    DHCP6R_ERR_PARAM,                       /*  2  �������Ϸ�                 */
    DHCP6R_ERR_NOMEM,                       /*  3  �ڴ����ʧ��               */
    DHCP6R_ERR_NULL_IF,                     /*  4  �ӿڲ�����                 */
    DHCP6R_ERR_NULL_POINTER,                /*  5  ָ�����Ϊ��               */
    DHCP6R_ERR_NOSUPPORT_IF,                /*  6  �ӿڲ�֧��DHCP6R           */
    DHCP6R_ERR_BORROW_IP_IF,                /*  7  ���õ�ַ�ӿ�               */
    DHCP6R_ERR_TRUNKPORT_IF,                /*  8  TRUNK��Ա�˿ڲ�֧��RELAY   */
    DHCP6R_ERR_MODE_NO_MATCH,               /*  9  ����ӿ�����������ģʽ��ͻ */
    DHCP6R_ERR_SERVERADDR_NO_MATCH,         /*  10 ����ӿ�������Server��ַ���Ͳ�ƥ�� */
    DHCP6R_ERR_NO_CFG,                      /*  11 û�����ÿ��ƿ�             */
    DHCP6R_ERR_SERVER_EXIST,                /*  12 �Ѿ������������ַ         */
    DHCP6R_ERR_SERVER_NOEXIST,              /*  13 û�����������ַ           */
    DHCP6R_ERR_SERVER_INVALID,              /*  14 ���õ�server��ַ�Ƿ�       */
    DHCP6R_ERR_MAX_SERVER,                  /*  15 �ﵽ���SERVER����         */
    DHCP6R_ERR_NOT_REGISTER,                /*  16 DHCP6R ģ��δע��          */
    DHCP6R_ERR_MODE_DIS,                    /*  17 ȥʹ��ģʽ��ʹ��ģʽ��һ�� */
    DHCP6R_ERR_JOIN_MULTI_GROUP,            /*  18 ����ಥ��ʧ��             */
    DHCP6R_ERR_LEAVE_MULTI_GROUP,           /*  19 �˳��ಥ��ʧ��             */
    DHCP6R_ERR_NO_ENABLE_RELAY,             /*  20 δʼ��relay����(ȫ�ֺͽӿ�ģʽ��δʹ��) */
    DHCP6R_ERR_INADDR6_TO_CHAR,             /*  21 ����ַ�ṹת�����ַ���ʧ�� */
    DHCP6R_ERR_GET_IFNAMEBYINDEX,           /*  22 �ɽӿ�������ȡ�ӿ���ʧ��   */
    DHCP6R_ERR_MEMCPY,                      /*  23 �ڴ濽��ʧ��               */
    DHCP6R_ERR_IPV6_DOWN,                   /*  24 �ӿ�δʹ��IPv6Э��         */
    DHCP6R_ERR_IPV6_IF_SCAN,                /*  25 ����ʹ��IPv6�ӿ�ʧ��       */
    DHCP6R_ERR_LINKLOCAL_EXIST,             /*  26 ͬһ��·���ص�ַ��Ӷ��   */
    DHCP6R_ERR_LOCALHOST_ADDR,              /*  27 ��ӵĵ�ַ�Ǳ����ĵ�ַ   */
    DHCP6R_ERR_NO_CFG_DEBUG,                /*  28 û�����ô˽ӿڵ��Կ���     */
    DHCP6R_ERR_NO_CFG_DST_IPADDR,           /*  29 ���ͱ���û������Ŀ�ĵ�ַ   */
    DHCP6R_ERR_ADDR6_TO_STRING,             /*  30 ��IPV6��ַת��Ϊ�ַ���ʧ�� */
    DHCP6R_ERR_ALL_JOIN_MULTI_GROUP,        /*  31 ȫ��ʹ��ʱ�����нӿڼ���ಥ��ʧ�ܡ�
                                                ���нӿ��˳��ಥ��ʧ�ܶ�ȥʹ�ܺ�����
                                                ʹ����Ӱ�죬�������������    */
    DHCP6R_ERR_NO_IN_MULTI_GROUP,           /*  32 û�м���ಥ��             */
    DHCP6R_ERR_MAX,                         /*  ���������ֵ,�Ժ���Ӵ������밴˳����ӵ���ǰ */
};

#define DHCP6R_SERVERLIST_MAX_NUM   8       /* ȫ��ģʽ�����Server��Ŀ���ӿ�ģʽ��ÿ���ӿ����Server��Ŀ */

#ifndef _IN6ADDR_S
#define _IN6ADDR_S
 /* IPv6��ַ�ṹ */
 typedef struct tagIN6Addr
 {
     union
     {
         UCHAR     u6_ucaddr[16];
         USHORT    u6_usaddr[8];
         ULONG     u6_uladdr[4];
     } u6_addr;    /* 128-bit IP6 address */
 }IN6ADDR_S;
#endif
/* Ϊ�����÷��㣬�������º궨��*/
#define s6_addr      u6_addr.u6_ucaddr
#define s6_addr8     u6_addr.u6_ucaddr
#define s6_addr16    u6_addr.u6_usaddr
#define s6_addr32    u6_addr.u6_uladdr

/* ����server��ַ�ṹ */
typedef struct tagDHCP6RServerNode
{
    IN6ADDR_S      stServerAddr;     /*Server ��IPV6��ַ*/
    ULONG          ulIfIndex;        /*Server ��Ӧ�ĳ��ӿ�*/
}DHCP6R_SERVERNODE_S;

/* Relayͳ����Ϣ�ṹ */
typedef struct tagDHCP6RStatInfo
{
    ULONG ulRxServerPkt;                /* Relay�յ���Server�������ı�����      */
    ULONG ulTxServerGlobal;             /* Relay��Server�����͵�Ŀ�ĵ�ַΪȫ�ֵ�
                                           ַ������                             */
    ULONG ulTxServerLinklocal;          /* Relay��Server�����͵�Ŀ�ĵ�ַΪ��·��
                                           �ص�ַ������                         */
    ULONG ulTxServerMulticast;          /* Relay��Server�����͵�Ŀ�ĵ�ַΪ�ಥ��
                                           ַ������                             */
    ULONG ulTxServerPkt;                /* Relay��Server�����͵ı�������        */
                                        
    ULONG ulRxClientPkt;                /* Relay�յ���Client���������ı�����    */ 
    ULONG ulTxClientRelayReplyPkt;      /* Relay���͵�Client����RELAYREPLY������ */
    ULONG ulTxClientAdvertisePkt;       /* Relay���͵�Client����ADVERTISE������ */
    ULONG ulTxClientReconfigurePkt;     /* Relay���͵�Client����RECONFIGURE������ */
    ULONG ulTxClientReplyPkt;           /* Relay���͵�Client����REPLY������     */
    ULONG ulTxClientPkt;                /* Relay���͵�Client���ı�������        */
                                        
    ULONG ulRxClientSolicitPkt;         /* Relay�յ���SOLICIT������             */
    ULONG ulRxClientRequestPkt;         /* Relay�յ���REQUEST������             */
    ULONG ulRxClientConfirmPkt;         /* Relay�յ���CONFIRM������             */
    ULONG ulRxClientRenewPkt;           /* Relay�յ���RENEW������               */
    ULONG ulRxClientRebindPkt;          /* Relay�յ���REBIND������              */
    ULONG ulRxClientReleasePkt;         /* Relay�յ���RELEASE������             */
    ULONG ulRxClientDeclinePkt;         /* Relay�յ���DECLINE������             */
    ULONG ulRxClientInforequestPkt;     /* Relay�յ���INFORMATION_REQUEST������ */
    ULONG ulRxClientRelayforwPkt;       /* Relay�յ���RELAY_FORW������          */    

    ULONG ulRxServerRelayreplyPkt;      /* Relay�յ���RELAY_REPL������          */

    /***********************************************\
     * ���Ľ��ա���������                          *
     * �ֵ�ģʽ�£���������-������ == ���ͱ������� *
     * �㲥ģʽ�£���������-������ <= ���ͱ������� *
    \***********************************************/
    ULONG ulRxAllPkt;                   /* Relay���ձ��������������������ĺͶ���
                                           ����                                 */
    ULONG ulTxAllPkt;                   /* Relay���ͱ����������������ͳɹ���ʧ��
                                           ����                                 */

    /* �������ļ��� */                  
    ULONG ulRxDropPkt;                  /* Relay�����ı������������쳣���ĺ�δ��
                                           ��Server��ַʱ����������             */
    ULONG ulTxFailedPkt;                /* Relay����ʧ�ܵı�������������ȫʧ�ܺ�
                                           �ֽ������Ե�ʧ��                     */                                            
}DHCP6R_STATINFO_S;

/*******************************************************************************
*    Func Name: TCPIP_DHCP6R_Enable
*  Description: ʹ��/ȥʹ��Relay���ܡ�
*        Input: ULONG ulInIfIndex:  ָ����ӿڵĽӿ�������0��Ϊ0��ʾ��ȫ��ģʽ
*                                   ʹ��/ȥʹ��Relay���ܣ���0��ʾ�Խӿ�ģʽ
*                                   ʹ��/ȥʹ��ָ���ӿڵ�Relay���ܡ�
*               ULONG ulEnableFlag: ʹ�ܿ��أ�DHCP6R_DISABLED   ȥʹ��
*                                             DHCP6R_ENABLED    ʹ��
*       Output: ��
*       Return: �ɹ�����DHCP6R_OK,����������ʾʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-07-13   PBQ(RT24429)            Create
*
*******************************************************************************/
extern ULONG TCPIP_DHCP6R_Enable(ULONG ulIfIndex, ULONG ulEnableFlag);

/*******************************************************************************
*    Func Name: TCPIP_DHCP6R_AddServerList
*  Description: ����һ��ServerList����
*        Input: ULONG ulInIfIndex: ָ����ӿڵĽӿ�������0��Ϊ0��ʾ����ȫ��
*                                  ServerList�����0��ʾ����ָ���ӿڵ�
*                                  ServerList���
*               DHCP6R_SERVERNODE_S *pstServerNode: Server��ַ�ṹָ�룬�ṹ����
*                                                   �����ֶ�stServerAddr��
*                                                   ulIfIndex��˵������:
*               stServerAddr: IPV6��ַ���������������ֵ�ַ���ͣ�
*                             1. IPv6ȫ�򵥲���ַ����������һ��Relay�ĵ�ַ��
*                                Ҳ������Server�ĵ�ַ����ʱulIfIndex����Ϊ0��
*                             2. IPv6��·���ص�ַ����������һ��relay�ĵ�ַ������
*                                ��һ��relay��˵��server�ĵ�ַ����ʱulIfIndex��
*                                ��ָ��Ϊ��0;
*                             3. IPv6�ಥ��ַFF02::1:2��FF05::1:3�����ڶಥ��ַ
*                                FF05::1:3��������Server��ͬһ������Relay������
*                                �á���ʱulIfIndex����ָ��Ϊ��0;
*               ulIfIndex: ָ����ַ��Ӧ�ĳ��ӿ���������ָ���ĵ�ַΪȫ�ֵ�����ַ
*                          ʱ��ulIfIndex����Ϊ0����ָ���ĵ�ַΪ��·���ص�ַ�Ͷ�
*                          ����ַʱ��ulIfIndex����ָ��Ϊ��0;
*       Output: ��
*       Return: �ɹ�����DHCP6R_OK,����������ʾʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-07-13   PBQ(RT24429)            Create
*
*******************************************************************************/
extern ULONG TCPIP_DHCP6R_AddServerList(ULONG ulInIfIndex, DHCP6R_SERVERNODE_S *pstServerNode);

/*******************************************************************************
*    Func Name: TCPIP_DHCP6R_DelServerList
*  Description: ɾ��һ��ServerList����
*        Input: ULONG ulInIfIndex: ָ����ӿڵĽӿ�������0��Ϊ0��ʾɾ��ȫ��
*                                  ServerList�����0��ʾɾ��ָ���ӿڵ�
*                                  ServerList���
*               DHCP6R_SERVERNODE_S *pstServerNode: Server��ַ�ṹָ�룬�ṹ����
*                                                   �����ֶ�stServerAddr��
*                                                   ulIfIndex��˵������:
*               stServerAddr: IPV6��ַ���������������ֵ�ַ���ͣ�
*                             1. IPv6ȫ�򵥲���ַ����������һ��Relay�ĵ�ַ��
*                                Ҳ������Server�ĵ�ַ����ʱulIfIndex����Ϊ0��
*                             2. IPv6��·���ص�ַ����������һ��relay�ĵ�ַ������
*                                ��һ��relay��˵��server�ĵ�ַ����ʱulIfIndex��
*                                ��ָ��Ϊ��0;
*                             3. IPv6�ಥ��ַFF02::1:2��FF05::1:3�����ڶಥ��ַ
*                                FF05::1:3��������Server��ͬһ������Relay������
*                                �á���ʱulIfIndex����ָ��Ϊ��0;
*               ulIfIndex: ָ����ַ��Ӧ�ĳ��ӿ���������ָ���ĵ�ַΪȫ�ֵ�����ַ
*                          ʱ��ulIfIndex����Ϊ0����ָ���ĵ�ַΪ��·���ص�ַ�Ͷ�
*                          ����ַʱ��ulIfIndex����ָ��Ϊ��0;
*       Output: ��
*       Return: �ɹ�����DHCP6R_OK,����������ʾʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-07-13   PBQ(RT24429)            Create
*
*******************************************************************************/
extern ULONG TCPIP_DHCP6R_DelServerList(ULONG ulInIfIndex, DHCP6R_SERVERNODE_S *pstServerNode);

/*******************************************************************************
*    Func Name: TCPIP_DHCP6R_DelAllServerList
*  Description: ɾ������ServerList����
*        Input: ULONG ulInIfIndex: ָ����ӿڵĽӿ�������0
*                                  Ϊ0:�ڽӿ�ʹ��ģʽ��:��ʾɾ�����нӿڵ�����
*                                                       ServerList����
*                                      ��ȫ��ʹ��ģʽ��:��ʾɾ��ȫ��serverlist
*                                                       ����
*                                  ��0:��ʾɾ��ָ���ӿڵ�����ServerList���
*       Output: ��
*       Return: �ɹ�����DHCP6R_OK,����������ʾʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-09-28   chenyao/mashouqiang     Create
*
*******************************************************************************/
ULONG TCPIP_DHCP6R_DelAllServerList(ULONG ulInIfIndex);

/*******************************************************************************
*    Func Name: TCPIP_DHCP6R_GetServerList
*  Description: ��ȡServerList�б�
*        Input: ULONG ulInIfIndex: ָ����ӿڵĽӿ�������0��Ϊ0��ʾ��ȡȫ�� 
*                                  ServerList�б���0��ʾ��ȡָ����ӿڵ�
*                                  ServerList�б�
*       Output: DHCP6R_SERVERNODE_S *pstDhcp6rServerList: �����ȡ����ServerList��
*       Return: �ɹ�����DHCP6R_OK,����������ʾʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-07-13   PBQ(RT24429)            Create
*
*******************************************************************************/
extern ULONG TCPIP_DHCP6R_GetServerList(ULONG ulInIfIndex, DHCP6R_SERVERNODE_S *pstDhcp6rServerList);

/*******************************************************************************
*    Func Name: TCPIP_DHCP6R_ShowServerList
*  Description: ��ʾServerList�б�
*        Input: ULONG ulInIfIndex: ָ����ӿڵĽӿ�������0��Ϊ0��ʾ��ʾȫ�� 
*                                  ServerList�б���0��ʾ��ʾָ����ӿڵ�
*                                  ServerList�б�
*       Output: ��
*       Return: �ɹ�����DHCP6R_OK,����������ʾʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-07-13   PBQ(RT24429)            Create
*
*******************************************************************************/
extern ULONG TCPIP_DHCP6R_ShowServerList(ULONG ulInIfIndex);

/*******************************************************************************
*    Func Name: TCPIP_DHCP6R_SetMaxHops
*  Description: ��������м�������
*        Input: ULONG ulHops: ����м�������ȡֵ��Χ��0~255��Ĭ��Ϊ32
*       Output: 
*       Return: �ɹ�����DHCP6R_OK,����������ʾʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-07-13   PBQ(RT24429)            Create
*
*******************************************************************************/
extern ULONG TCPIP_DHCP6R_SetMaxHops(ULONG ulHops);

/*******************************************************************************
*    Func Name: TCPIP_DHCP6R_GetMaxHops
*  Description: ��ȡ����м�������
*        Input: 
*       Output: ULONG *ulHops:�����ȡ���������
*       Return: �ɹ�����DHCP6R_OK,����������ʾʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-07-13   PBQ(RT24429)            Create
*
*******************************************************************************/
extern ULONG TCPIP_DHCP6R_GetMaxHops(ULONG *pulHops);

/*******************************************************************************
*    Func Name: TCPIP_DHCP6R_ShowMaxHops
*  Description: ��ʾ����м�������
*        Input: ��
*       Output: ��
*       Return: �ɹ�����DHCP6R_OK,����������ʾʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-07-13   PBQ(RT24429)            Create
*
*******************************************************************************/
extern ULONG TCPIP_DHCP6R_ShowMaxHops(VOID);

/*******************************************************************************
*    Func Name: TCPIP_DHCP6R_SetDebugSwitch
*  Description: ���� Relay ���Կ���
*        Input: ULONG ulIfIndex: ָ���ӿڵĽӿ�������0��Ϊ0��ʾ����ȫ�ֵ��Կ��� 
*                                ��0��ʾ����ָ���ӿڵĵ��Կ���
*               ULONG ulDebugSwitch: ������Ϣ�ȼ�����: 
*                                   DHCP6R_DEBUG_OFF        ���Կ��عر�
*                                   DHCP6R_DEBUG_PAKCET     ��Packet������Ϣ��
*                                                           �Կ���
*                                   DHCP6R_DEBUG_ERROR      ��Error���Կ���
*                                   DHCP6R_DEBUG_ALL        ��Packet������Ϣ��
*                                                           Error���Կ���
*                                   DHCP6R_DEBUG_ALL_DETAIL ��Packet��ϸ��Ϣ��
*                                                           Error���Կ���
*       Output: ��
*       Return: �ɹ�����DHCP6R_OK,����������ʾʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-07-13   PBQ(RT24429)            Create
*
*******************************************************************************/
extern ULONG TCPIP_DHCP6R_SetDebugSwitch(ULONG ulIfIndex, ULONG ulDebugSwitch);

/*******************************************************************************
*    Func Name: TCPIP_DHCP6R_GetDebugSwitch
*  Description: ��ȡ Relay ���Կ���
*        Input: ULONG ulIfIndex: ָ���ӿڵĽӿ�������0��Ϊ0��ʾ��ȡȫ�� 
*                                Relay ���Կ��أ���0��ʾ��ȡָ���ӿڵ�
*                                Relay ���Կ��ء�
*       Output: ULONG *pulDebugSwitch �����ȡ���ĵ��Կ���
*       Return: �ɹ�����DHCP6R_OK,����������ʾʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-07-13   PBQ(RT24429)            Create
*
*******************************************************************************/
extern ULONG TCPIP_DHCP6R_GetDebugSwitch(ULONG ulIfIndex, ULONG *pulDebugSwitch);

/*******************************************************************************
*    Func Name: TCPIP_DHCP6R_SetDbgPktLen
*  Description: ���õ��Ա����������
*        Input: USHORT usPacketLen: Ĭ�ϳ���ΪDHCP6R_PRINT_LEN_DEFAULT(128),
*                                   ��СֵΪDHCP6R_PRINT_LEN_MIN(34),
*                                   ���ֵΪDHCP6R_PRINT_LEN_MAX(16384),
*                                   ����Ϊ0���ߴ��ڱ���ʵ�ʳ������ӡ����ȫ������
*       Output: ��
*       Return: �ɹ�����DHCP6R_OK,����������ʾʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-08-29   PBQ(RT24429)            Create
*
*******************************************************************************/
extern ULONG TCPIP_DHCP6R_SetDbgPktLen(USHORT usPacketLen);

/*******************************************************************************
*    Func Name: TCPIP_DHCP6R_ShowDebugSwitch
*  Description: ��ʾ Relay ���Կ���
*        Input: ULONG ulIfIndex: ָ���ӿڵĽӿ�������0��Ϊ0��ʾ��ʾȫ�� 
*                                Relay ���Կ��أ���0��ʾ��ʾָ����ӿڵ�
*                                Relay ���Կ��ء�
*       Output: ��
*       Return: �ɹ�����DHCP6R_OK,����������ʾʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-08-29   PBQ(RT24429)            Create
*
*******************************************************************************/
extern ULONG TCPIP_DHCP6R_ShowDebugSwitch(ULONG ulIfIndex);

/*******************************************************************************
*    Func Name: TCPIP_DHCP6R_ShowCfgInfo
*  Description: ��ʾRelay������Ϣ
*        Input: ULONG ulIfIndex: ָ���ӿڵĽӿ�������0��Ϊ0��ʾ��ʾȫ�� 
*                                Relay ������Ϣ����0��ʾ��ʾָ����ӿڵ�
*                                Relay ������Ϣ��
*       Output: ��
*       Return: �ɹ�����DHCP6R_OK,����������ʾʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-08-29   PBQ(RT24429)            Create
*
*******************************************************************************/
extern ULONG TCPIP_DHCP6R_ShowCfgInfo(ULONG ulIfIndex);

/*******************************************************************************
*    Func Name: TCPIP_DHCP6R_GetStatInfo
*  Description: ��ȡRelayͳ����Ϣ
*        Input: ��
*       Output: DHCP6R_STATINFO_S *pstDhcp6rStat: �����ȡ����Relayͳ����Ϣ�ṹ
*       Return: �ɹ�����DHCP6R_OK,����������ʾʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-07-13   PBQ(RT24429)            Create
*
*******************************************************************************/
extern ULONG TCPIP_DHCP6R_GetStatInfo(DHCP6R_STATINFO_S *pstDhcp6rStat);

/*******************************************************************************
*    Func Name: TCPIP_DHCP6R_ClrStatInfo
*  Description: ���Relayͳ����Ϣ
*        Input: ��
*       Output: ��
*       Return: �ɹ�����DHCP6R_OK,����������ʾʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-07-13   PBQ(RT24429)            Create
*
*******************************************************************************/
extern ULONG TCPIP_DHCP6R_ClrStatInfo(VOID);

/*******************************************************************************
*    Func Name: TCPIP_DHCP6R_ShowStatInfo
*  Description: ��ʾRelayͳ����Ϣ
*        Input: ��
*       Output: ��
*       Return: �ɹ�����DHCP6R_OK,����������ʾʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-07-13   PBQ(RT24429)            Create
*
*******************************************************************************/
extern ULONG TCPIP_DHCP6R_ShowStatInfo(VOID);

/*******************************************************************************
*    Func Name: TCPIP_DHCP6R_SetFwdMode
*  Description: �����м�serverģʽ
*        Input: ULONG ulMode: DHCP6R_FORWORD_CYCLE      �ֵ���ʽ
*                             DHCP6R_FORWORD_BROADCAST  �㲥��ʽ
*       Output: ��
*       Return: �ɹ�����DHCP6R_OK,����������ʾʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-07-13   PBQ(RT24429)            Create
*
*******************************************************************************/
extern ULONG TCPIP_DHCP6R_SetFwdMode(ULONG ulMode);

/*******************************************************************************
*    Func Name: TCPIP_DHCP6R_GetFwdMode
*  Description: ��ȡ�м�serverģʽ
*        Input: ��
*       Output: ULONG *pulMode: ��ȡ�����м�serverģʽ
*       Return: �ɹ�����DHCP6R_OK,����������ʾʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-07-13   PBQ(RT24429)            Create
*
*******************************************************************************/
extern ULONG TCPIP_DHCP6R_GetFwdMode(ULONG *pulMode);

/*******************************************************************************
*    Func Name: TCPIP_DHCP6R_ShowFwdMode
*  Description: ��ʾ�м�serverģʽ
*        Input: ��
*       Output: ��
*       Return: �ɹ�����DHCP6R_OK,����������ʾʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-07-13   PBQ(RT24429)            Create
*
*******************************************************************************/
extern ULONG TCPIP_DHCP6R_ShowFwdMode(VOID);

#ifdef __cplusplus
}
#endif  /* end of __cplusplus */

#endif      /* end of _DHCP6R_API_H_ */


