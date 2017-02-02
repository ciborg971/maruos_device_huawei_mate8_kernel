/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              tcpip_optim.h
*
*  Project Code: VISP V1R6C02
*   Module Name: OPTIM
*  Date Created: 2008-04-17
*        Author: mafeng(59090)
*   Description: �����Ż�����궨���뺯������
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-04-17   mafeng(59090)           Create
*
*******************************************************************************/

#ifndef _TCPIP_OPTIM_H_
#define _TCPIP_OPTIM_H_


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/*struct id,�������ڴ�ʱʹ��*/
#define SID_PUBLIC_OPTIM_S 1


/* �������������(���ջ�������ͻ����) */
#define CACHE_HASHLEN 256

/* ��ʱ������ 10s */
#define OPTIM_TIMECYCLE 10000
#define OPTIM_DEF_ENTRYNUM 32

#define OPTIM_EN_STATUS 1
#define OPTIM_DIS_STATUS 0

#define OPTIM_DEBUG_ON 1
#define OPTIM_DEBUG_OFF 0

#define OPTIM_MBUF_OURRCV 0x0001

/* BFD���ĵĶ˿ں� */
#define OPTIM_BFD_DPORT 3784
#define OPTIM_BFD_SPORT 4784

/* IKE�Ķ˿ں� */
#define OPTIM_IKE_PACK_UDPPORT 500
#define OPTIM_IKE_NAT_PACK_UDPPORT 4500

/* TTLֵ,ת�����Ľ����ж� */
#define OPTIM_IP_TTLDEC 1

/* DHCP CLIENT PORT */
#define OPTIM_DHCP4C_CLIENT_PORT 0x44

enum tagOPTProcRet
{
    OPTIM_GOTO_VISP = VOS_OK, /* �Ż�����ʧ��,����VISP������������ */
    OPTIM_GOTO_END,           /* ���ı��ͷ�(���Ӻ�������ʧ�ܻ�VLAN����ʧ��),���Ĵ������̽��� */
    OPTIM_GOTO_OPTIM,         /* �����Ż�����ɹ�,���Ĵ������̽��� */
};

#define CACHE_HASHMASK (CACHE_HASHLEN - 1)

/* �жϵ�ǰ�Ƿ�ʹ�������Ż� */
#define OPTIM_IS_DISENABLE_STATUS (OPTIM_DIS_STATUS == g_ulOptimEnable)
#define OPTIM_IS_ENABLE_STATUS (OPTIM_EN_STATUS == g_ulOptimEnable)

/* ����������ݽṹ */
typedef struct tagOptimCache
{
    struct tagOptimCache *pstNextNode;
    
    /* 1, host receive, 2, forward, 3, host send */
    UCHAR ucCacheType; /* SEND/RECEIVE/FORWARD */

    /* 17:udp,6:tcp,0:rawip,17:iwf */
    UCHAR ucPktType;   /* UDP/TCP/RAWIP/IWF */
    UCHAR ucNPFlag;    /* NP flag */
    UCHAR ucTmFlag;    /* time �ϻ���־*/

    LONG  iFd;            /* visp rcv/send skt id  */
    ULONG ulOutIfIndex;   /* snd ifnet index */
    ULONG ulVLINKIndex;   /* vlink index */
    ULONG ulNextHop;      /* next hop,network seq */
    
    ULONG   ulDstIp;     /* dst ip,network seq    */
    ULONG   ulSrcIp;     /* src ip,network seq    */
    USHORT  usDstPort;   /* dst port,network seq  */
    USHORT  usSrcPort;   /* src port,network seq  */
    UCHAR   ucProtocol;  /* rip protocol          */
    UCHAR   ucPad;

    USHORT  usHeadLen;   /* ת������ʱ�ı���ͷ���� */
    UCHAR pucPktHead[48];
}OPTIM_CACHE_S;

/* IP��������Ԫ�����Ϣnetwork seq */
typedef struct tagOptimIpInfo
{
    ULONG ulSIP;    /* Դ��ַ */            
    ULONG ulDIP;    /* Ŀ�ĵ�ַ */ 
    USHORT usSP;    /* Դ�˿ں� */            
    USHORT usDP;    /* Ŀ�Ķ˿ں� */            
    UCHAR ucPID;    /* Э��� */
    UCHAR ucPadding[3];
}OPTIM_IPINFO_S;

/* �Ż�ʹ��״̬��־1:ʹ�� 0:ȥʹ�� */
extern ULONG g_ulOptimEnable;

/* ���Կ���״̬ */
extern ULONG g_ulOptimDebug;

/* �����ˢ�¶�ʱ��ID */
extern ULONG g_ulOptimTimerID;

/* �û�ʹ���Ż�ʱָ���Ļ���������� */
extern ULONG g_ulOptEntrySum;

/* ��ǰ���û����������� */
extern ULONG g_ulOptEntryUsable;

/*�����Ż������ϻ���ʱ����ʱʱ��(���ڲ�����ʹ��)*/
extern ULONG g_ulOptTimeOutValue;

extern TCPIP_OPTIMSTAT_S g_pstOptStatInfo;
extern OPTIM_CACHE_S *g_pstOptEntryHead;
extern OPTIM_CACHE_S *g_pstOptEntryUsable;

/* ���ͻ���� */
extern OPTIM_CACHE_S *g_pstOptSndEntry[CACHE_HASHLEN];

/* ���ջ���� */
extern OPTIM_CACHE_S *g_pstOptRcvEntry[CACHE_HASHLEN];

extern OPTIM_INTERMEDIATE_HOOK_FUNC g_pfOptimIntermediateHook;

/*Added by qinyun62011, (Distribute socket)�ֲ�ʽsocket�ü��������Ż�����ϣ�������ģ���е��ù�ϵ�ĺ�������ȫ�ֹ��ӵķ�ʽ�ṩ, 2014/3/7 */
typedef struct tagTCPIP_OPTIM_HOOK
{
    ULONG (*pfOPTIM_AllocEntryForIWF)(MBUF_S *pstMbuf, LONG nIpHLen);
    VOID (*pfOPTIM_AllocEntryForUDP)(IP_S *pstIP, LONG iFd);
    VOID (*pfOPTIM_DelEntryBySocket)(ULONG ulEntryType, LONG iFd);
    ULONG (*pfOPTIM_SndUDP)(MBUF_S *pstMbuf, MBUF_S *pMAddr, USHORT usSPort);
}TCPIP_OPTIM_HOOK_S;
extern TCPIP_OPTIM_HOOK_S g_stOptimHook;
/* End of Added by qinyun62011, 2014/3/7 */

/* ������Ԫ����ϢHASH��������� */
#define OPTIM_HASHINDEX(ulSIP, usSP, ulDIP, usDP, ucPID, HashIndex) \
{\
    ULONG ulTemp = (ulSIP) ^ (usSP) ^ ((ulDIP)>>1)  ^((usDP)>>1)^(ucPID);\
    ulTemp ^= (ulTemp >> 20) ^ (ulTemp >> 12) ^ (ulTemp >> 7) ^ (ulTemp >> 4);\
    (HashIndex) = (ulTemp & CACHE_HASHMASK);\
}

/* ���������뵽������� */
#define OPTIM_ENTRY_INSERT(g_pstCache, ulHashIndex, pstEntry) \
{\
    (pstEntry)->pstNextNode = (g_pstCache)[(ulHashIndex)];\
    (g_pstCache)[(ulHashIndex)] = (pstEntry);\
}

/* ����ipͷ��ttl��У��� */
/* ulCheck = (pstIp)->ip_usSum;����ΪulCheck = (ULONG)((pstIp)->ip_usSum);�Ա�֤����һ�� */
/* (pstIp)->ip_usSum = ulCheck + ((ulCheck >= 0xFFFF)?1:0)�ұ����(USHORT)�Ա�֤����һ�� */
#define OPTIM_FAST_CKSUM(pstIp)\
{\
    ULONG ulCheck;\
    ulCheck = (ULONG)((pstIp)->ip_usSum);\
    ulCheck += VOS_HTONS(0x0100);\
    (pstIp)->ip_usSum = (USHORT)(ulCheck + ((ulCheck >= 0xFFFF)?1:0));\
    --(pstIp)->ip_chTTL;\
}

/* ������Ԫ����Ϣƥ�仺�����(����ΪOPTIM_CACHE_S��OPTIM_IPINFO_S����ָ��) */
#define OPTIM_PKT_MATCH_CACHE_RCV(pstEntry, pstIpInfo, ulRet)\
{\
    if (((pstEntry)->ulSrcIp==(pstIpInfo)->ulSIP)&&((pstEntry)->ulDstIp==(pstIpInfo)->ulDIP)\
        &&((pstEntry)->usSrcPort==(pstIpInfo)->usSP)&&((pstEntry)->usDstPort==(pstIpInfo)->usDP)\
        &&((pstEntry)->ucProtocol==(pstIpInfo)->ucPID))\
    {\
        (ulRet) = VOS_OK;\
    }\
}

/* ������Ԫ����Ϣƥ�仺�����(����ΪOPTIM_CACHE_S��OPTIM_IPINFO_S����ָ��) */
#define OPTIM_PKT_MATCH_CACHE_SND(pstEntry, pstIpInfo, ulRet)\
{\
    if (((pstEntry)->ulDstIp==(pstIpInfo)->ulDIP)\
        &&((pstEntry)->usSrcPort==(pstIpInfo)->usSP)&&((pstEntry)->usDstPort==(pstIpInfo)->usDP)\
        &&((pstEntry)->ucProtocol==(pstIpInfo)->ucPID))\
    {\
        (ulRet) = VOS_OK;\
    }\
}


/* ����mbuf��Ϣ���»������(OPTIM_CACHE_S��MBUF_IP_PACKET_INFO_S���ݽṹ) */
#define OPTIM_MtoE(pstEntry, pstMInfo)\
{\
    (pstEntry)->ulSrcIp    = (pstMInfo)->ulSourceIpAddress;\
    (pstEntry)->usSrcPort  = (pstMInfo)->usSourcePortOrIcmpType;\
    (pstEntry)->ulDstIp    = (pstMInfo)->ulDestinationIpAddress;\
    (pstEntry)->usDstPort  = (pstMInfo)->usDestinationPortOrIcmpCode;\
    (pstEntry)->ucProtocol = (pstMInfo)->ucProtocolId;\
    (pstEntry)->ulNextHop  = (pstMInfo)->ulNextHopIpAddress;\
}

/* ����mbuf��Ϣ������Ԫ����Ϣ(OPTIM_IPINFO_S��MBUF_IP_PACKET_INFO_S���ݽṹ) */
#define OPTIM_MtoO(pstOptIp, pstMInfo)\
{\
    (pstOptIp)->ulSIP = (pstMInfo)->ulSourceIpAddress;\
    (pstOptIp)->usSP  = (pstMInfo)->usSourcePortOrIcmpType;\
    (pstOptIp)->ulDIP = (pstMInfo)->ulDestinationIpAddress;\
    (pstOptIp)->usDP  = (pstMInfo)->usDestinationPortOrIcmpCode;\
    (pstOptIp)->ucPID = (pstMInfo)->ucProtocolId;\
}

/* ����Entry��Ϣ������Ԫ����Ϣ(OPTIM_IPINFO_S��OPTIM_CACHE_S���ݽṹ) */
#define OPTIM_EtoO(pstOptIp, pstEntry)\
{\
    (pstOptIp)->ulSIP = (pstEntry)->ulSrcIp;\
    (pstOptIp)->usSP  = (pstEntry)->usSrcPort;\
    (pstOptIp)->ulDIP = (pstEntry)->ulDstIp;\
    (pstOptIp)->usDP  = (pstEntry)->usDstPort;\
    (pstOptIp)->ucPID = (pstEntry)->ucProtocol;\
}


/* ���ݱ�����ӿ����͸����Ż�ͳ����Ϣ */
#define OPTIM_UPDATESTAT_BY_INIFTYPE(ulInIfType, g_stOptStatInfo)\
{\
    if ((PORT_ETHERNET == (ulInIfType))||(PORT_ETH_TRUNK == (ulInIfType)))\
    {\
        (g_stOptStatInfo).ulEthRcv++;\
    }\
    else\
    {\
        (g_stOptStatInfo).ulNoEthRcv++;\
    }\
}

/* ���ݱ��ĳ��ӿ����͸����Ż�ͳ����Ϣ */
#define OPTIM_UPDATESTAT_BY_OUTIFTYPE(ulOutIfType, g_stOptStatInfo)\
{\
    if ((PORT_ETHERNET == (ulOutIfType))||(PORT_ETH_TRUNK == (ulOutIfType)))\
    {\
        (g_stOptStatInfo).ulEthSnd++;\
    }\
    else\
    {\
        (g_stOptStatInfo).ulNoEthSnd++;\
    }\
}

/* ���ݱ���Э�����͸����Ż�ͳ����Ϣ */
#define OPTIM_UPDATESTAT_BY_SNDPKTTYPE(ucPktType, g_stOptStatInfo)\
{\
    if (IPPROTO_UDP == (ucPktType))\
    {\
        (g_stOptStatInfo).ulIWFSnd++;\
    }\
    else\
    {\
        if (IPPROTO_TCP == (ucPktType))\
        {\
            (g_stOptStatInfo).ulTcpSnd++;\
        }\
        else\
        {\
            (g_stOptStatInfo).ulRipSnd++;\
        }\
    }\
}

/* ��װ������Ϣɾ������ */
#define OPTIM_DEBUG_OUTPUT(str)\
{\
    (VOID)TCPIP_IC_SendMsg(0, 0, str);\
}


extern VOID  OPTIM_AllocEntryForETH(MBUF_S *pstMbuf, IFNET_S *pstIfnet);
extern VOID  OPTIM_AllocEntryForIP(MBUF_S *pstMbuf, IFNET_S *pstIfnet);
extern ULONG OPTIM_AllocEntryForIWF(MBUF_S *pstMbuf, LONG nIpHLen);
extern ULONG OPTIM_AllocEntryForPPI(MBUF_S *pstMbuf, IFNET_S *pstIfnet);
extern VOID  OPTIM_AllocEntryForNoUDP(IP_S *pstIP);
extern VOID  OPTIM_AllocEntryForUDP(IP_S *pstIP, LONG iFd);

extern ULONG OPTIM_CreateEntry(ULONG ulSum);
extern VOID  OPTIM_DelAllEntry(VOID);
extern ULONG OPTIM_ETHUpdateEntry(OPTIM_CACHE_S **ppstEntry, ULONG ulIfIndex);
extern VOID  OPTIM_DelEntryByEth(ULONG ulIfIndex);
extern ULONG OPTIM_SocketUpdateEntry(OPTIM_CACHE_S **ppstEntry, LONG iFd);
extern VOID  OPTIM_DelEntryBySocket(ULONG ulEntryType, LONG iFd);
extern VOID  OPTIM_DestroyEntry(VOID);

extern OPTIM_CACHE_S *OPTIM_MallocEntry(VOID);
extern OPTIM_CACHE_S *OPTIM_Rcv_MatchEntry(ULONG ulIndex, OPTIM_IPINFO_S *pstOptInfo);
extern OPTIM_CACHE_S *OPTIM_Snd_MatchEntry(ULONG ulIndex, OPTIM_IPINFO_S *pstOptInfo);


extern VOID  OPTIM_GetIPInfo(IP_S *pstIp, OPTIM_IPINFO_S *pstOptInfo);
extern ULONG OPTIM_GetRTMODE(VOID);
extern ULONG OPTIM_GetSKMODE(VOID);
extern ULONG OPTIM_PreP_IP(MBUF_S *pstMbuf);
extern ULONG OPTIM_PreP_ETH(MBUF_S *pstMbuf);
extern ULONG OPTIM_Rcv(MBUF_S *pstMbuf, IFNET_S *pstIfnet);
extern VOID  OPTIM_FreeEntry(OPTIM_CACHE_S * pstEntry);
extern ULONG OPTIM_SndIP(MBUF_S *pstMbuf, LONG lHLen);
extern ULONG OPTIM_SndUDP(MBUF_S *pstMbuf, MBUF_S *pMAddr, USHORT usSPort);
extern VOID  OPTIM_TimerUpdateEntry(OPTIM_CACHE_S **ppstEntry);
extern VOID  OPTIM_Timer(VOID *pTemp);
extern LONG OPTIM_EntryDbgInfo(OPTIM_CACHE_S *pstEntry, CHAR *pszDbgInfo, LONG lBufLen, LONG nLen);

extern ULONG OPTIM_DoNothing(MBUF_S *pstMbuf);
extern ULONG TCPIP_AddVlanHead(MBUF_S *pMBuf, ULONG ulVlanHead);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* end of _TCPIP_OPTIM_H_ */

