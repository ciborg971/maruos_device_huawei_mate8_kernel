/*******************************************************************************
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              sfib_sh_rm.h
*
* Project Code: VISPV100R005
*  Module Name: SFIB4
* Date Created: 2004-07-07
*       Author: Zhang Hongyan
*  Description: ʵ�ּ�·�ɹ���ĺ��������ݽṹ�Ķ���
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2004-07-07   Zhang Hongyan           Create
*  2006-03-30   Jiangtao                Adjust for D00646
*  2006-04-21   Jiangtao                Adjust for D00859
*  2006-05-11   luyao(60000758)         Ϊ֧��ARM CPU�ֽڶ������ԣ��޸Ľṹ��
*
*******************************************************************************/

#ifdef    __cplusplus
extern    "C"{
#endif

#ifndef _SFIB_RM_H
#define _SFIB_RM_H

#include "tcpip/ifnet/include/if_def.h"

typedef struct tagSFIB_RT_ENTRY
{
    ULONG  ulRt_Dest;               /* destination address */
    ULONG  ulRt_Dest_PrefLen;       /* len of mask */
    ULONG  ulRt_Nexthop;            /* next hop address */
    ULONG  ulRt_Flags;              /* route flags -RTF_GATEWAY, RTF_HOST */ 
    ULONG  ulRt_IfIndex;            /* index of outgoing interface */
    ULONG  ulRt_ATIndex;            /* index of virtual link between ulRt_Loc_IfIndex */
    ULONG  ulRt_Slot;               /* slot num of outgoing interface */
    ULONG  ulRt_Loc;                /* local address */
    ULONG  ulRt_Loc_PrefLen;        /* local address mask */
    ULONG  ulRt_Loc_IfIndex;        /* index of local interface */
    /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
    ULONG  ulVrfIndex;
    /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
    USHORT usRt_Proto;              /* route type, eg: SFIB_ROUTE_INTER_NET */
    BOOL_T bUse;                    /* used flag,0 δʹ��,1 ʹ�� */
    USHORT usRef;                   /* reference number */
    USHORT usRTPri;                 /* route priority */
    UCHAR  ucUserNextHopFlag;       /* ���þ�̬·��ʱ�Ƿ�ָ��next-hop,0��ָ����1ָ�� */
    UCHAR  ucUserOutIfFlag;         /* ���þ�̬·��ʱ�Ƿ�ָ�����ӿ�,0��ָ����1ָ�� */
    UCHAR  ucPadding[2];
    CHAR   szRt_OutIfName[MAX_IF_NAME_LENGTH + 1];  /* name of out interface */
    ULONG  ulPmtu;                   /* Path mtu for the route, a00900892, 30-01-2014 */
} SFIB_RT_ENTRY_S;


/******************************************************
                                       SFIB��AM4�Ľӿ���Ϣ
******************************************************/
#define SFIB_AM4_NEW_ADDRESS 0
#define SFIB_AM4_DEL_ADDRESS 1

typedef struct tagSFIB_AM4_MSG
{
    ULONG  ulIfnetIndex;    /* IFNET index of bound physical interface */
    ULONG  ulMsgType;       /* address added or deleted */
    ULONG  ulLogAddr;       /* address */
    ULONG  ulSubMask;       /* Address mask */
    ULONG  ulAddressType;   /* Interface address Type */
    /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
    ULONG  ulInstanceID;
    /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
} SFIB_AM4_MSG_S;


/******************************************************
                                       SFIB��IFNET��VLINK�ӿ���Ϣ
******************************************************/
#define SFIB_VLINK_NEW 0
#define SFIB_VLINK_DEL 1

typedef struct tagSFIB_VLINK_IFNETMSG
{
    ULONG ulIfnetIndex;     /* Ifnet Index of the phy Interface */
    ULONG ulVlinkIndex;     /* Vlink Index is Zero for Phy Msg  */
    ULONG ulPeerAddr;       /* Peer Address of Vlink            */    
    ULONG ulMsgType;        /* Message Type                     */   
    /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
    ULONG ulVrfIndex;       /* VRF ID                           */   
    /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
} SFIB_VLINK_IFNETMSG_S;

/*Ϊ����tips���ӵĽṹ����*/
typedef struct tagIfAddrms
{
    ULONG      ulIntfIndex;
    USHORT     usMsgType;
    UCHAR      ucPadding[2]; 
    ULONG      ulIpFlag;
    SOCKADDR_S sLocalAddr;
    SOCKADDR_S sNetMask;
    SOCKADDR_S sPrimaryAddr;
} IFADDRMS_S;

#define RM_USR_DSCP_LEN 19

typedef struct tagDefaultRt
{
    ULONG ulActionType; /*���û�ɾ����0-delete��1-create*/
    ULONG ulRtPri;/*·�����ȼ���Ĭ��Ϊ1��ȡֵ0-255*/
    ULONG ulDestAddr;/*Ŀ�ĵ�ַ*/
    ULONG ulIfIndex; /*���ӿ�*/
    ULONG ulMask;/*���룬ȡֵ1-32*/
    ULONG ulNextHopAddr;/*��һ�������ص�ַ*/
    /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
    ULONG ulVrfIndex;
    /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
} DEFAULTRT_S;
/*END Add*/ 

/* VRF�������ܴ�pstRtEntryTmp��ȡ������������ */
#define COPY_ONE_ROUTE_TO_USER(pstRtEntry,pstRtEntryTmp,ulIndex)    \
    (pstRtEntry)->ulRt_Dest = (pstRtEntryTmp)->ulRt_Dest;\
    (pstRtEntry)->ulRt_Dest_PrefLen = (pstRtEntryTmp)->ulRt_Dest_PrefLen;\
    (pstRtEntry)->ulRt_Nexthop = (pstRtEntryTmp)->ulRt_Nexthop;\
    (pstRtEntry)->ulRt_Flags = (pstRtEntryTmp)->ulRt_Flags;\
    (pstRtEntry)->ulRt_IfIndex = (pstRtEntryTmp)->ulRt_IfIndex;\
    (pstRtEntry)->ulRt_ATIndex = (pstRtEntryTmp)->ulRt_ATIndex;\
    (pstRtEntry)->ulRt_Slot = (pstRtEntryTmp)->ulRt_Slot;\
    (pstRtEntry)->ulRt_Use = (pstRtEntryTmp)->ulRt_Use;\
    (pstRtEntry)->ulRt_State = (pstRtEntryTmp)->ulRt_State;\
    (pstRtEntry)->ulRt_Proto = (pstRtEntryTmp)->ulRt_Proto;\
    (pstRtEntry)->ulRt_TimeStamp = (pstRtEntryTmp)->ulRt_TimeStamp;\
    (pstRtEntry)->ulCacheEntryIndex = (pstRtEntryTmp)->ulCacheEntryIndex;\
    (pstRtEntry)->ulRt_Loc = (pstRtEntryTmp)->ulRt_Loc;\
    (pstRtEntry)->ulRt_Loc_PrefLen = (pstRtEntryTmp)->ulRt_Loc_PrefLen;\
    (pstRtEntry)->ulRTPri = (pstRtEntryTmp)->ulRTPri;\
    (pstRtEntry)->ulVrfIndex = (ulIndex);\
    (pstRtEntry)->ulPmtu = (pstRtEntryTmp)->ulPmtu; /* Path mtu for the route. a00900892, 30-01-2014 */\


/* ��ָ������������������ȫ��VRF�в���ȫ��·�� */
#define FIB4_SEARCH_NO_FILTER          0x04   

typedef struct tagFIB4_FILTER_KEY
{
    ULONG ulVrfIndex;                                  /*VRF����*/
    UINTPTR ulWaitlist;                            /*VRF��Ӧ��waitlist*/
    ULONG ulFilterType;                                /*��������*/
}FIB4_FILTER_KEY_S;

ULONG IP4_RIB_OpenRib4Table (UINTPTR *pulHandle, CHAR * pszVrfName);
ULONG IP4_RIB_CloseObject_RIB (UINTPTR ulHandle);
ULONG IP4_RIB_GetRib4Entry (UINTPTR ulHandle, SFIB_RT_ENTRY_S *pstRIBData);

ULONG IP4_RIB_GetRib4EntryByFilter (UINTPTR ulHandle, SFIB_RT_ENTRY_S *pstRIBData);

ULONG SFIB_Update_InterfaceAddress(SFIB_AM4_MSG_S *pMsg, IFADDRMS_S * pstIPMsg);
ULONG SFIB_RM_Mask2Len(ULONG ulSubnetMask, ULONG *pulMaskLen);

/* route type */
#define SFIB_ROUTE_STATIC              1
#define SFIB_ROUTE_DHCP                2
#define SFIB_ROUTE_INTER_NET           3
#define SFIB_ROUTE_INTER_HOST          4
#define SFIB_ROUTE_LOOPBACK            5
#define SFIB_ROUTE_VLINK               6
#define SFIB_ROUTE_SUBNET_BROCST       7

#define SFIB_DEF_SRM_VLINK             1
#define SFIB_DEF_RIB_MAXNUM            64
#define SFIB_CFG_RIB_MAXNUM            1024

#define SFIB_LOOPBACK_ADDRESS          (0x7f000001)

#define SFIB_ERR_MAX_ROUTE             VOS_ERR + 1
#define SFIB_ERR_ROUTE_CANNOT_REPALCE  VOS_ERR + 2
#define SFIB_ERR_ROUTE_CANNOT_DEL      VOS_ERR + 3
#define SFIB_ERR_VRF_NOT_ENABLE        VOS_ERR + 4

#define SFIB_ADDR_TYPE_PRIMARY         1
#define SFIB_ADDR_TYPE_BORROW          2

#define SID_RT4_ENTRY_S 1

/* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
VOID   SFIB_InterfaceUp(ULONG ulZoneId,ULONG ulIfIndex);
VOID   SFIB_InterfaceDown(ULONG ulZoneId,ULONG ulIfIndex);
VOID   SFIB_AddInterfaceAddress(ULONG ulZoneId,ULONG ulIpAddress, ULONG ulMaskLen, ULONG ulIfIndex);
VOID   SFIB_DelInterfaceAddress(ULONG ulZoneId,ULONG ulIpAddress, ULONG ulMaskLen, ULONG ulIfIndex);
VOID   SFIB_RM_NewRoute(ULONG ulZoneId,SFIB_RT_ENTRY_S **ppstRtEntry);
VOID   SFIB_RM_GetNextRoute(ULONG ulZoneId,SFIB_RT_ENTRY_S **ppstRtEntry);
ULONG  SFIB_AddDefaultRouteByDhcpc(ULONG ulZoneId,ULONG ulGateway);
ULONG  SFIB_DelDefaultRouteByDhcpc(ULONG ulZoneId,ULONG ulGateWay);
ULONG  SFIB_AddRoute(ULONG ulZoneId,ULONG ulIpAddress, ULONG ulMaskLen, ULONG ulGateway, ULONG ulIfIndex, ULONG ulRTPri, ULONG Pmtu);
ULONG  SFIB_DelRoute(ULONG ulZoneId,ULONG ulIpAddress, ULONG ulMaskLen,ULONG ulGateway, ULONG ulIfIndex);
BOOL_T SFIB_RM_AddrIsOwn(ULONG ulZoneId,ULONG ulIpAddr);
BOOL_T SFIB_RM_DstAddrIsSame(ULONG ulZoneId,ULONG ulDstAddr, ULONG ulMaskLen, ULONG ulIfIndex);
ULONG  SFIB_RM_DelSameStaticRoute(ULONG ulZoneId,ULONG ulIpAddr, ULONG ulMaskLen);
ULONG  SFIB_RM_AddSameStaticRoute(ULONG ulZoneId,ULONG ulIpAddr, ULONG ulMaskLen);
ULONG SFIB_DisableRtByIfNextHop(ULONG ulZoneId,ULONG ulIfIndex, ULONG ulNextHop);
ULONG SFIB_EnableRtByIfNextHop(ULONG ulZoneId,ULONG ulIfIndex, ULONG ulNextHop);
ULONG SFIB_ExactDisableRt(ULONG ulZoneId,ULONG ulDstIpAddr, ULONG ulMaskLen, ULONG ulNextHop, ULONG ulIfIndex);
ULONG SFIB_ExactEnableRt(ULONG ulZoneId,ULONG ulDstIpAddr, ULONG ulMaskLen, ULONG ulNextHop, ULONG ulIfIndex);
ULONG SFIB_PPI_DownloadStaticRtByNextHop(ULONG ulZoneId,ULONG ulIfIndex, 
                                         ULONG ulNextHop, 
                                         ULONG ulVlinkIndex);
/* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
BOOL_T SFIB_RM_IfIsLinkUp(ULONG ulIfIndex);
VOID   SFIB_RM_FreeRoute(SFIB_RT_ENTRY_S *pstRtEntry);
extern ULONG TCPIP_IC_SendMsg(ULONG ulMid, ULONG ulInfoId, char *pBuf);
VOID   SFIB_RM_GetRtByNexthop(ULONG ulIpAddr, SFIB_RT_ENTRY_S* pstRt);
VOID   SFIB_RM_GetRtByIfIdx(ULONG ulIfIndex, SFIB_RT_ENTRY_S* pstRtEntry);
ULONG  SFIB_VLINK_AddRoute(ULONG ulPeerAddr, ULONG ulIfnetIndex, ULONG ulVlinkIndex);
ULONG  SFIB_VLINK_DelRoute(ULONG ulPeerAddr, ULONG ulIfnetIndex, ULONG ulVlinkIndex);

ULONG SFIB_ProcessDefaultRTAdd(SFIB_RT_ENTRY_S *pstInputRtEntry);
ULONG SFIB_ProcessDefaultRTDel(SFIB_RT_ENTRY_S *pstInputRtEntry);

extern ULONG SFIB_SetWarningRouteNum(ULONG ulInstance, ULONG ulRouteNum);
extern ULONG SFIB_SetWarningRouteNumByVrf(ULONG ulType,ULONG ulRouteNum,CHAR *pszVrfName);
ULONG SFIB_RM_RtTblInit(ULONG ulZoneId);
VOID SFIB_RM_RtTblClr(ULONG ulZoneId);

BOOL_T SFIB_RM_ExistSameRoute(ULONG ulZoneId,ULONG ulDstAddr, ULONG ulMaskLen, ULONG ulIfIndex);

#endif  /* #ifndef _SFIB_RM_H */

#ifdef    __cplusplus
}
#endif

