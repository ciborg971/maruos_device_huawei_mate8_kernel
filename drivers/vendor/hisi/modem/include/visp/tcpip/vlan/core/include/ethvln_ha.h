
#ifndef _ETHVLN_HA_H_
#define _ETHVLN_HA_H_

#ifdef  __cplusplus
extern "C"{
#endif

/* ��̫VLAN������Ϣͷ�ṹ */
typedef struct tagEthVlanHaHead
{
    USHORT  usBakType;          /* ETH VLAN������Ϣ����  */
    USHORT  usBakLen;           /* ETH VLAN������Ϣ����  */
}ETHVLAN_HA_HEAD_S;


/* ��̫VLAN�������� */
typedef struct tagEthVlanHaData
{
    ULONG   ulIfIndex;         /* �ӽӿ����� */
    USHORT  usMinVid;          /* VLAN ID��Сֵ */
    USHORT  usMaxVid;          /* VLAN ID���ֵ */
    USHORT  usEncapType ;      /* ��װ��ʽ */
    UCHAR   ucpadd[2];
}ETHVLAN_HA_DATA_S;


#define ETHVLAN_HA_BATCH         0x1
#define ETHVLAN_HA_REALTIME      0x2

#define SET_ETHVLAN_HA_HEAD(pstEthVlanBakHdr, ulBakType, ulBakLen)\
{\
    (pstEthVlanBakHdr)->usBakType = (USHORT)(ulBakType);\
    (pstEthVlanBakHdr)->usBakLen  = (USHORT)(ulBakLen);\
}


#define ETHVLAN_VID_CONVERT_HADATA(pstVidNode, pstEthVlanData) \
{ \
    (pstEthVlanData)->ulIfIndex   = (pstVidNode)->ulSubIfIndex; \
    (pstEthVlanData)->usMinVid    = (pstVidNode)->usVID; \
    (pstEthVlanData)->usMaxVid    = (pstVidNode)->usVID; \
    (pstEthVlanData)->usEncapType = (pstVidNode)->encapType; \
}


#define ETHVLAN_HA_ADD  1
#define ETHVLAN_HA_DEL  2


extern ULONG ETHVLAN_HA_BatchBackup(VOID);
extern ULONG ETHVLAN_HA_RealTimeBackup(ULONG ulBakType, VOID* pData);
extern ULONG ETHVLAN_HA_BuildOnePkt(UCHAR* pucData, ULONG ulOffset, ULONG ulBufTotalLen,
                                     VOID *pstVoid, ULONG *pulMsgAddLen, USHORT usType);
extern ULONG ETHVLAN_HA_CntBakLen(ULONG ulBakType, ULONG *pulBakLen);
extern ULONG EHTVLAN_HA_OpenWaitList(UINTPTR *pulWaitListHandle);
extern ULONG EHTVLAN_HA_CloseWtLstObject(UINTPTR ulWaitListHandle);
extern ULONG EHTVLAN_HA_GetWtLstEntry(UINTPTR ulWaitListHandle, ETHVLAN_VID_NODE_S *pstVidNode);
extern VOID *EHTVLAN_HA_GetWtLstNext(VOID *pCur,VOID **ppNext);
extern ULONG ETHVLAN_HA_Input(UCHAR *pucBuf, ULONG ulMsgLen);
extern ULONG ETHVLAN_HA_OutputMsg(UCHAR *pucData, ULONG ulMsgLen);
extern VOID  ETHVLAN_HA_VerboseOutput(UCHAR *pBuf, ULONG ulMsgLen, ULONG ulCmd);
extern ULONG ETHVLAN_HA_Smooth(VOID);
extern ULONG ETHVLAN_HA_Clean(VOID);



#ifdef __cplusplus
}
#endif

#endif

