/*******************************************************************************
*
*
*                Copyright 2011, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              dhcp6r_typ.h
*
*  Project Code: VISP V2R3C06
*   Module Name: DHCP6R  
*  Date Created: 2011-7-15
*        Author: PBQ(RT24429)
*   Description: DHCP6Rģ������ݽṹ����
*
*-------------------------------------------------------------------------------
*  Modification  History
*  DATE          NAME             DESCRIPTION    
*-------------------------------------------------------------------------------
*  2011-7-27     PBQ(RT24429)     Create the first version.
*
*******************************************************************************/

#ifndef _DHCP6R_TYP_H_
#define _DHCP6R_TYP_H_

#ifdef __cplusplus
    extern "C"{
#endif  /* end of __cplusplus */

/* IPv6 socketͨ�ýṹ */
typedef struct tagSockaddr_Storage
{
    UCHAR               ss_ucLen;
    UCHAR               ss_ucFamily;
    UCHAR               aucFill[126];
}SOCKADDR_STORAGE_S;

/* relayʹ�����ÿ��ƿ� */
typedef struct tagDHCP6RCfgNode
{
    DLL_NODE_S          stDLLNode;
    ULONG               ulIfIndex;       /* ���ýӿ�����,���Ϊȫ�����ã���indexΪ0 */
    ULONG               ulEnableStatus;  /* ʹ��״̬ 0-δʹ�� 1-ʹ�� */
    ULONG               ulServerNum;     /* �ӿ���server��ַ��Ŀ */       
    DHCP6R_SERVERNODE_S astServer[DHCP6R_SERVERLIST_MAX_NUM]; /* server��ַ�ṹ���� */
}DHCP6R_CFG_NODE_S;

/*ȫ�ֿ��ƿ�*/
typedef struct tagDHCP6RCfgHead
{
    DLL_S               stCfgList;       /* �ӿ��������� */
    ULONG               ulEnableCount;   /* ʹ�ܼ��� */
    UCHAR               ucCfgMode;       /* Relayʹ��ģʽ��ȫ��ģʽ(1),�ӿ�ģʽ(0) */
    UCHAR               ucFwdMode;       /* �м̷�ʽ,��ʼֵ0-�ֵ���ʽ��1-�㲥��ʽ */
    USHORT              usMaxHops;       /* ���RELAY����,Ĭ��ֵΪ32 */
    DHCP6R_STATINFO_S   stStatistics;    /* ͳ����Ϣ */ 
}DHCP6R_CFG_HEAD_S;

typedef struct tagDHCP6RDbgEntry
{
    DLL_S               stDebugList;     /* Debug�������� */
    ULONG               ulGlobalDebug;   /* ȫ�ֵ��Կ��� */ 
    USHORT              usDbgPktLen;     /* ���ĵ�����Ϣ������� */ 
}DHCP6R_DBG_S;

/* �ӿڵ��Կ��ؿ��ƿ� */
typedef struct tagDHCP6RDebug
{
    DLL_NODE_S          stDLLNode;
    ULONG               ulIfIndex;    
    ULONG               ulDebug;
}DHCP6R_DEBUG_NODE_S; 

/* ����Դ(Ŀ��)��ַ�ͳ�(��)�ӿ����� */
typedef struct in6_pktinfo
{
    IN6ADDR_S           stIp6Addr;       /* src/dst IPv6 address */
    ULONG               ulIfIndex;       /* send/recv interface index */
}IN6_PKTINFO_S;

#pragma pack(1)
/* DHCPv6 relay����ͷ */
typedef struct tgDHCP6R_HEADER
{
    UCHAR               ucMsgType;
    UCHAR               ucHopCnt;
    IN6ADDR_S           stLinkAddr;
    IN6ADDR_S           stPeerAddr;
}DHCP6R_HEADER_S;

/* Begin: Add by pengbinquan for 2011080012, ��Ϊ�������������Ϣ��ӡ��ϸ���� */
/* Relay-Forward��Relay-Reply����֮�����������ͷ�������� */
typedef struct tagPublicHeader
{
    ULONG               ulMsgType  :8;   /* ����ǰ8λΪ�������� */
    ULONG               ulTranID   :24;  /* ���ĺ�24λΪTranID */
}DHCP6R_PUBLIC_HEADER_S;
/* End: Add by pengbinquan for 2011080012, 2011-08-24 */
#if (VOS_ARM == VOS_HARDWARE_PLATFORM)
#pragma pack(0)
#else
#pragma pack()
#endif

/* ͨ��ѡ��ṹ */
typedef struct tagDHCP6ROptBuf
{
    USHORT              usOptCode;
    USHORT              usOptLen;
    CHAR               *pOptData;
}DHCP6R_OPTBUF_S;

/* InterfaceIDѡ��ṹ */
typedef struct tagDHCP6RInterfaceID
{
    USHORT              usOptCode;
    USHORT              usOptLen;
#pragma pack(1)
    struct packed_data
    {
        UCHAR           ucInterfaceType; /* �ӿ����� */
        UCHAR           ucReserved;
        USHORT          usInterfaceNum;  /* �ӿڱ�� */
    }OptData;
#if (VOS_ARM == VOS_HARDWARE_PLATFORM)
#pragma pack(0)
#else
#pragma pack()
#endif

}DHCP6R_INTERFACEID_S;

/* Relay ����ѡ��ṹ */
typedef struct tagDHCP6ROptInfo
{
    DHCP6R_OPTBUF_S     stRelayMsgOpt;   /* �м̱���ѡ�� */
    DHCP6R_OPTBUF_S     stIfIdOpt;       /* �ӿ�IDѡ�� */
}DHCP6R_OPTINFO_S; 

/* Shell��Coreע��Ļص������� */
typedef struct tagDHCP6RShellCallbackSet
{
    ULONG (*pfDHCP6R_DebugOutString)(CHAR * szStr); /* ������Ϣ������� */
}DHCP6R_SHELL_CALLBACK_SET_S;

#ifdef __cplusplus
}
#endif  /* end of __cplusplus */

#endif  /* end of _DHCP6R_TYP_H_ */

