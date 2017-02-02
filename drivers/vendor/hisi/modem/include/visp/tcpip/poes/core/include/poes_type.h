/*******************************************************************************
*
*                Copyright 2007, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              poes_type.h
*
* Project Code: VISPV100R006C02
*  Module Name: POES
* Date Created: 2007-07-18
*       Author: lijing(52889)
*  Description: POESģ������ݽṹ����
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2007-07-18   lijing(52889)           Create
*
*******************************************************************************/

#ifndef  _POES_TYPE_H_
#define  _POES_TYPE_H_

#ifdef __cplusplus
extern "C" {
#endif

/* PPPoE�����ײ���������̫�ײ� */
typedef struct tagPoesEtherPppoe
{
    UCHAR  szDestMacAddr[POES_MAC_LEN]; /* Ŀ��mac */
    UCHAR  szSourMacAddr[POES_MAC_LEN]; /* Դmac */
    USHORT usProType;   /* Э��� */
    UCHAR  ucVerType;   /* PPPoE���ĵ�ver��type */
    UCHAR  ucCode;      /* PPPoE���ĵ�code */
    USHORT usSesId;     /* PPPoE���ĵ�session id */
    USHORT usLength;    /* PPPoE���ĵı��ĸ��ز��ֳ��� */
} POES_ETHPOE_S;

/* �Զ�MAC���ƿ� */
typedef struct tagPoesHisMac
{
    DLL_NODE_S stDLLNode;   /* ˫����ڵ� */
    UCHAR      aucHisMacAddr[POES_MAC_LEN]; /* �Զ�physical��ַ */
    USHORT     usSessionNum;/* ��Զ�physical��ַ����Session����Ŀ */
} POES_HIS_MAC_S;

/* Session���ƿ� */
typedef struct tagPoesSb
{
    struct tagPoesCb *pstPoesCb;    /* PPPoE���ƿ�ָ�� */
    POES_HIS_MAC_S *pstHisMac;      /* �Զ�physical��ַ���ƿ�ָ�� */
    IFNET_S *pstEthIf;      /* ��Ӧ��̫���ӿ�IFNETָ�� */
    IFNET_S *pstVAIf;       /* ��ӦVA��ͨ����IFNETָ�� */
    USHORT usSessionId;     /* ��Session��ID */
    UCHAR  ucSesState;      /* ��SessionЭ��״̬ */
    UCHAR  ucTimeCounter;   /* PADI״̬Session�����ʱ������ */
    ULONG  ulInPackets;     /* �յ��İ��� */
    ULONG  ulInOctets;      /* �յ����ֽ��� */
    ULONG  ulInDiscards;    /* ����ʱ�����İ��� */
    ULONG  ulOutPackets;    /* ���͵İ��� */
    ULONG  ulOutOctets;     /* ���͵��ֽ��� */
    ULONG  ulOutDiscards;   /* ����ʱ�����İ��� */
}POES_SB_S;

/* Session�ڵ� */
typedef struct tagPoesSessionNode
{
    POES_SB_S *pstSession;/* ��ӦSession���ƿ�ָ�� */
    USHORT     usPrev;/* ǰһ��Session�ڵ� */
    USHORT     usNext;/* ��һ��Session�ڵ� */
} POES_SESSION_NODE_S;

/* POES���ƿ� */
typedef struct tagPoesCb
{
    DLL_NODE_S           stDLLNode; /* ���ƿ�����ڵ� */
    ULONG                ulEthIfIndex; /* ��Ӧ����̫�ӿڽӿ����� */
    ULONG                ulVTIfIndex; /* ����̫�ӿڶ�Ӧ��VT�ӿ����� */
    UCHAR                aucOurMacAddr[POES_MAC_LEN]; /* ���ӿڵ�physical��ַ */
    UCHAR                ucPadding[2]; /* ����ֶ� */
    UCHAR                szServiceName[POES_SERVICENAME_MAX_LEN]; /* Service Name */
    ULONG                ulNewSessionCount; /* ����ͳ��Session�������� */
    ULONG                ulCurrentEstablishRate; /* ����Session�������� */
    ULONG                ulBurstEstablishRate; /* ���Session�������� */
    ULONG                ulPadiFaliedCount; /* PADI״̬��ʱ���� */
    POES_SESSION_NODE_S *pstSesNodeArray;   /* session�ڵ�����ָ�� */
    USHORT               usSesNodeArrayLen; /* ��ǰSession�ڵ����鳤�� */
    USHORT               usSessionNum; /* ���ӿ��Ͻ���Session��Ŀ*/
    USHORT               usSessFreeIndex; /* ����Session�ڵ��������� */
    USHORT               usFirstPadiSessIndex; /* PADI״̬session����ͷ�ڵ��������� */
    POES_DEBUG_INFO_S    stDebugInfo; /* debug���� */
} POES_CB_S;

/* POESģ����Ϣ */
typedef struct tagPoesModInfo
{
    ULONG ulMID_POES;
    ULONG ulQUE_POES;
    ULONG ulPoesCb_WaitListID;
} POES_MOD_INFO_S;

/* POES���Shell��Coreע��Ļص������� */
typedef struct tagPoesShellCallbackSet
{
    VOID (*pfPOES_DebugOutString)(CHAR * szStr);

    ULONG (*pfPOES_CreateQueue)(ULONG ulQueID, ULONG ulGetCntPerTimes,
                                ULONG (*pfPOES_QueDealPacketFunc)(MBUF_S *),
                                ULONG (*pfPOES_QueIsDropThisPacketFunc)(MBUF_S *, ULONG, CHAR *),
                                ULONG ulMaxLen);

    ULONG (*pfPOES_DeleteQue)(ULONG ulQueID);

    ULONG (*pfPOES_ActiveQueue)(ULONG ulQueID);

    ULONG (*pfPOES_DeActiveQueue)(ULONG ulQueID);

    ULONG (*pfPOES_EnQueue)(MBUF_S *);

    ULONG (*pfPOES_DropQueue)(MBUF_S *);

    VOID (*pfPOES_FreePacketInQueue)(ULONG ulQueID, ULONG ulCmd, CHAR * pData);
} POES_SHELL_CALLBACK_SET_S;

#ifdef __cplusplus
}
#endif

#endif

