/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              vlink_api.h
*
*  Project Code: node
*   Module Name:   
*  Date Created: 2008-08-01
*        Author: wangbin (62223)
*   Description: 
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-08-01   wangbin (62223)         Create
*
*******************************************************************************/
#ifndef _VLINK_API_H_
#define _VLINK_API_H_

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

typedef enum tagVLINK_ERR_E
{
    VLINK_OK,                         /* 0 */
    VLINK_ERR = MID_COMP_VLINK + 1,   /* 1 ����������ָ��δ��ʼ��*/
    VLINK_ERR_NULL_POINTER,           /* 2 ����ָ��Ϊ�� */
    VLINK_ERR_NO_INDEX_NODE,          /* 3 û��Vlink�ڵ� */
    VLINK_ERR_GET_ENTRY_END,          /* 4 ��ѯ����*/
    VLINK_ERR_WAITLIST,               /* 5 WaitList�쳣*/
    VLINK_ERR_INTERFACE,              /* 6 ����Ľӿ�����*/
    VLINK_ERR_CFG_TYPE,               /* 7 �������������*/
    VLINK_ROUTE_NOTIFY_DISABLE,       /* 8 vlink ·��֪ͨģʽû������*/
    VLINK_ERR_ADDR,                   /* 9  ����ĵ�ַ*/
    VLINK_ERR_VRF,                    /* 10 ��ȡVRF���� */
    VLINK_ERR_MAX                     /*   ���������ֵ*/
}VLINK_ERR_E;

#define VLINK_FILTER_ALL  0x00000000
#define VLINK_FILTER_WITH_DESTMAST  0x00000001
#define VLINK_FILTER_WITH_IFINDEX   0x00000002
#define VLINK_FILTER_WITH_VRFINDEX  0x00000004
typedef struct tagVLINK_ENTRY_FILTER
{
    ULONG ulFiltFlag;   /* vlink·�ɹ���flag*/
    ULONG ulDestAddr;   /* Ŀ�ĵ�ַ*/
    ULONG ulMaskLen;    /* Ŀ������*/
    ULONG ulIfIndex;    /* ���ӿ�����*/
    ULONG ulVrfIndex;   /* vrf����*/
}VLINK_ENTRY_FILTER_S;

typedef struct tagVLINK_ROUTE_INFO
{
    ULONG ulDestAddr;   /* Ŀ�ĵ�ַ*/
    ULONG ulMaskLen;    /* Ŀ������*/
    ULONG ulIfIndex;    /* ���ӿ�����*/
    ULONG ulNextHop;    /* ��һ����ַ*/
    ULONG ulVrfIndex;   /* vrf����*/
    ULONG ulVlinkIndex; /* vlink����:0 ����Чֵ ����������Чֵ*/
    ULONG ulLastUpdTime;/* ���һ�θ���ʱ�䣬���������һֱû�и��£���ʾ��ʼ����ʱ�� */
}VLINK_ROUTE_INFO_S;


typedef struct tagVlink6CfgRt
{
    ULONG ulOperType;        /*
                               #define RTM_CREATE  0x01:����·��
                               #define RTM_DEL     0x02:ɾ��·��
                             */
    ULONG ulIfIndex;         /* ·�ɳ��ӿ����� : �Ƿ���IPC�ӿ����û���֤ */
    UCHAR aucDestAddr[16];   /* 16�ֽ��Ա���˳������˳����*/
} VLINK6_CFG_RT_S; /*IPv6 �Զ�·�����ýṹ*/

ULONG TCPIP_OpenVlinkRtTable(UINTPTR *pulWaitListHandle,VLINK_ENTRY_FILTER_S *pstFilter);
ULONG TCPIP_GetVlinkRtEntry(UINTPTR ulEntryWaitList, VLINK_ROUTE_INFO_S *pstVlinkRtInfo);
ULONG TCPIP_CloseVlinkRtTable( UINTPTR ulWaitListHandle );

VOID TCPIP_ShowVlinkRoute();
VOID TCPIP_ShowVlink6Route();
ULONG TCPIP_SetVlinkDbgFlg(ULONG ulFlag);
ULONG TCPIP_GetVlinkDbgFlg(ULONG *pulFlg);
VOID TCPIP_ShowVlinkDbgFlg();
VOID TCPIP_ShowIPCVlinkCount();

/*******************************************************************************
*    Func Name: TCPIP_CfgVlink6Rt
* Date Created: 2013-04-12
*       Author: luogaowei 61496
*  Description: ����ND�������IPC �ӿ����� 128λ������·��
*        Input: VLINK6_CFG_RT_S *pstRt6Info: �����·����Ϣ
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-04-12   luogaowei 61496        create 
*******************************************************************************/
ULONG TCPIP_CfgVlink6Rt(VLINK6_CFG_RT_S *pstRt6Info);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _VLINK_API_H_ */


