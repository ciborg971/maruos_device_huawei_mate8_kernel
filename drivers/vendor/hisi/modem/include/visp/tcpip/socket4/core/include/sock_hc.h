/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              sock_hc.h
*
*  Project Code: VISP1.5
*   Module Name: Socket4  
*  Date Created: 2006-4-29
*        Author: l(48769)
*   Description: socket head cache header file 
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2006-04-27   l(48769)        ���ݱ�̹淶�����ļ����й淶������
*
*******************************************************************************/
#ifndef    _SOCK_HC_H_
#define    _SOCK_HC_H_

#ifdef    __cplusplus
extern "C"{
#endif

#ifndef _UDP6_PUBLIC_H
#include "common/ipos/ipv6/udp6_public.h"
#endif

/********************************MACROs define here********************************/
#define HC_NOT_INIT  0     /*Head Cache���û�г�ʼ��*/
#define HC_CREATE    1     /*�ѳ�ʼ�������Ǳ����ײ���û�н���*/
#define HC_OK        2     /*�ѳ�ʼ���������ײ��ѽ���*/

#define HC_MAX_HEADCACHE   256

#define HC_HASHTABLELENTH  256
#define HC_HASHTABLEMASK   HC_HASHTABLELENTH - 1

/* ipv6 128 bits addr transform to 32 bits for uniform hash index with ipv4 */
#define IN6ADDR_TO_INADDR(IN6ADDR) \
    (((IN6ADDR).s6_addr32[0])^((IN6ADDR).s6_addr32[1])^ \
     ((IN6ADDR).s6_addr32[2])^((IN6ADDR).s6_addr32[3]))


#define IP6HEAD_UDP6HEAD_LEN    48  /* 40(basic ipv6 head length) + 8 */
#define IP6HEAD_LEN             40  /* 40(basic ipv6 head length) */

/* use these struct for cal IPv6 Cksum -- see headcahce6_senddata function */
typedef struct stPreudoIP6Hdr
{
    struct 
    {
        USHORT  ph_slen;
        UCHAR   ph_zero[1];
        UCHAR   ph_nxt;
    } ph;
    IN6ADDR_S ip6_stSrc;                /* source address */
    IN6ADDR_S ip6_stDst;                /* destination address */
}PSEUDO_IP6_S;

typedef struct tagIp6Udp6Hdr
{
    PSEUDO_IP6_S stIp6;    
    UDP6HDR_S stUdp6;
}IP6_UDP6_HDR_S;

/******************************************************************************/
#define HeadCache_HashIndex(usPort, ulIpAddr) (((usPort) & (HC_HASHTABLEMASK)) | \
                                                           ((ulIpAddr) & (HC_HASHTABLEMASK)))
#define ADDCARRY(x)  (x > 65535L ? x -= 65535L : x)

#define REDUCE \
{ \
    unLUtil.l = lSum;\
    lSum = unLUtil.s[0] + unLUtil.s[1]; \
    ADDCARRY(lSum); \
}

#define HeadCache_DebugInfo(ucFunc, szBuf)    SOCK_ERROR_TRACE(ucFunc,ERR_LEVEL_INFO,szBuf)
#define HeadCache_DebugWarning(ucFunc, szBuf) SOCK_ERROR_TRACE(ucFunc, ERR_LEVEL_WARNING,szBuf)
#define HeadCache_DebugError(ucFunc, szBuf)   SOCK_ERROR_TRACE(ucFunc, ERR_LEVEL_ERROR,szBuf)

/*****************************structures define here**********************************/

typedef struct tag_HEADCACHEINFO
{
    DLL_S stDllHashTable [HC_HASHTABLELENTH];/* Head Cache���HASH��*/
    DLL_S stHeadCacheInfoDll;/*ָ��Head Cache����DLL����*/
    ULONG ulTotalNum;/*��������Ŀ*/
    /* ULONG ulUpdatedNum; �����������ͱ��ĵĽ����Ŀ  */
    /*ULONG ulInitalNum;�Ѿ���ʼ������û�н���ͷ���Ľ����  */
    /*ULONG ulRawNum;û�г�ʼ���Ľ����  */
}HEADCACHEINFO_S;

/*function*/
HEADCACHE_ENTRY_S* HeadCache_GetNext(HEADCACHE_ENTRY_S* pstEntry);
VOID *HeadCache_GetNextEntry(VOID *pCur,VOID **ppNext);
HEADCACHE_ENTRY_S *HeadCache_HashLookUp(SOCKET_S *pSocket, ULONG ulDstIp, USHORT usDstPort);
ULONG HeadCache_GetLinkStatus(IFNET_S *pstIfNet, ULONG *pulStatus);

/*extern functions declare here*/
extern ULONG TCPIP_IC_SendMsg(ULONG ulMId, ULONG ulInfoId, char * pBuf);
extern ULONG TCPIP_DrvDataSendDirect(ULONG dwIfIndex,  IOVEC_S *msg_pIov, \
                                                             SHORT    msg_nIovLen, VOID *pHeadBuf, ULONG ulHlen);
extern USHORT Ip_Fast_Cksum(USHORT *pusWord);

extern LONG HeadCache_SendData(SOCKET_S *pSocket,  const UIO_S *pUio, UINTPTR *pulEntryAddr);
extern LONG HeadCache6_SendData(SOCKET_S *pSocket,  UIO_S *pUio, UINTPTR *pulEntryAddr);

extern USHORT HeadCache_Cksum(LONG lHeadLenth, LONG nLen, VOID *pHead, const UIO_S *pUio);

#ifdef    __cplusplus
}
#endif    /* end of __cplusplus */

#endif    /* end of _SOCK_HC_H_ */

