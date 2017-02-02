/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              etharp_ha.h
*
*  Project Code: VISPV100R006
*   Module Name: HA
*  Date Created: 2006-12-04
*        Author: xiehuaguo
*   Description: ��̫���ݴ���ͷ�ļ�
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2006-12-04  xiehuaguo        Create
*
*******************************************************************************/

#ifndef _ETHARP_HA_H_
#define _ETHARP_HA_H_

#ifdef  __cplusplus
extern "C"{
#endif


/* ��̫������Ϣͷ */
typedef struct tag_ETH_BAK
{
    ULONG    ulMsgType; /* ��Ϣ���� */
    ULONG    ulArpItems;   /* ARP��ݵĸ���*/
} ETH_BAK_S ;

typedef struct tag_ARP_BAK_UPGRADE
{
    ULONG     ulIfIndex;        /* �ӿ����� */
    ULONG     ulIpAddr;         /* ��ַ */
    ULONG     ulRtExpire;       /* ��ʱʱ�� */
    UCHAR     szMac[MACADDRLEN];/* physical��ַ */
    UCHAR     ucFlags;          /* ARP���*/
    UCHAR     ucSourceType;      /*��̬ARP����Դ:��ѧϰ���û����á����ú����ѧϰ����*/
    ULONG     ulVrfIndex;       /* ʵ������ */    
    USHORT    usVID;            /* VLAN ID */
    USHORT    usReserved;       /* ���� */ 
}ARP_BAK_UPGRADE_S;

#define ETHARP_BAK_STATIC_BASE(from, to )\
{\
    (to)->ulIpAddr   =  (from)->ulIpAddr ;\
    (to)->ucFlags    =  (from)->ucFlags ;\
    (to)->ulIfIndex  =  (from)->ulIfIndex;\
    (to)->ulVrfIndex  =  (from)->ulVrfIndex;\
    (to)->usVID      =  (from)->usVID;\
    (VOID)TCPIP_Mem_Copy((to)->szMac,MACADDRLEN,(from)->szMac,MACADDRLEN);\
}

/* ������ձ��ݶ�̬ARP�ָ���*/
#define ETHARP_BAK_DYNAMIC_BASE(from, to )\
{ \
    (to)->ulIfIndex   =  (from)->ulIfIndex ;\
    (to)->ulIpAddr    =  (from)->ulIpAddr ;\
    (to)->ucFlags     =  (from)->ucFlags ;\
    (to)->ulRtExpire  =  (from)->ulRtExpire ;\
    (to)->ulVrfIndex  =  (from)->ulVrfIndex;\
    (to)->usVID       =  (from)->usVID;\
    (to)->ucSourceType = (from)->ucSourceType;\
    (VOID)TCPIP_Mem_Copy((to)->szMac,MACADDRLEN,(from)->szMac,MACADDRLEN);\
}

/* End: VISP Support multi-instance project */

/* ��̫������Ϣ���ݽṹ */
typedef struct tag_ETH_BAK_CFG_S
{
    ULONG     ulIfIndex;        /* �ӿ����� */
    USHORT    usIsARPproxy;     /* ARP������ */
    USHORT    usDhcpflag ;      /* �ӿ��Ƿ�ʹ��DHCP��� */  
    UCHAR     ucBakEthMac [MACADDRLEN];/* �ӿ�MAC */  
    UCHAR     ucEnableSpecArpPrxy; /* ����ARP������ */
    UCHAR     ucVlanflag;   /* �ӿ�VLANʹ�ܱ�� */

}ETH_BAK_CFG_S;


/* ��̫������Ϣ���� */
enum enumEthBAKMsgType
{
    ETH_BAK_ARP = 1,
    ETH_BAK_CONFIG,
    ETH_BAK_ARP_ADD,
    ETH_BAK_ARP_DELETE,
    ETH_BAK_ARP_UPDATE,
    ETH_BAK_GLOBAL,
    ETH_BAK_TLV,
    ETH_BAK_VLANID,
    ETH_BAK_ARP_ADD_VRF,
    ETH_BAK_ARP_DELETE_VRF,
    ETH_BAK_ARP_UPDATE_VRF,
    /* End: VISP Support multi-instance project */
    ETH_BAK_DARP_USERADD,
    ETH_BAK_SARP_CONFLICT,
    ETH_BAK_ARPTIME, /* BC3D01640 �û����԰�ETH�ӿ����ö�̬ARP������ϻ���ʱʱ�� ���ݴ��� */
    ETH_BAK_SUBVLAN,
    ETH_BAK_ISISFLAG,
    ETH_BAK_ARPGUARD,
    ETH_BAK_ARPCAPTURE,
};

enum enumEthBAKSubMsgType
{
    ETH_BAK_FREEARPMAXTIMES,
    ETH_BAK_FREEARPMAXNUM,
    ETH_BAK_ARPSTRICTLEARNSWITCH,
    ETH_BAK_ARPUNICASTCOUNT,
    ETH_BAK_ARPEXPIREOFFSET,
};

/*ETHARPģ��HA������Ϣͷ*/
typedef struct tagETHARP_HA_HEAD
{
    USHORT usEthOprType;  /* ETHARP������Ϣ����  */
    USHORT usEthOprLen;   /* ETHARP������Ϣ����  */
}ETHARP_HA_HEAD_S;

/* ��̫������ϢTLV */
typedef struct tag_ETH_BAK_GLOBAL_TLV
{
    USHORT    usTlvType;   /* TLV��Ϣ���� */
    USHORT    usTlvLen;    /* TLV����*/
} ETH_BAK_GLOBAL_TLV_S ;

typedef struct tag_ETH_BAK_VLANID_S
{
    ULONG     ulMsgType;        /*��Ϣ����*/
    ULONG     ulLen;            /*���ĳ���*/
    ULONG     ulIfIndex;        /* �ӿ����� */
    ULONG     ulVlanID;         /* �ӿ�VLAN ID*/
}ETH_BAK_VLANID_S;
 
/* BC3D01640 �û����԰�ETH�ӿ����ö�̬ARP������ϻ���ʱʱ�� ���ݴ��� */
typedef struct tag_ETH_BAK_ARPTIME_S
{
    ULONG     ulMsgType;        /*��Ϣ����*/
    ULONG     ulLen;            /*���ĳ���*/
    ULONG     ulIfIndex;        /* �ӿ����� */
    ULONG     ulArpExpireTime;  /* �ӿ�arpʱ�� */
}ETH_BAK_ARPTIME_S;

typedef struct tag_ETH_BAK_ISISFLAG_S
{
    ULONG     ulMsgType;        /*��Ϣ����*/
    ULONG     ulLen;            /*���ĳ���*/
    ULONG     ulIfIndex;        /* �ӿ����� */
    ULONG     ulISISFlag;       /* ISISʹ�ܱ�� */
}ETH_BAK_ISISFLAG_S;

typedef struct tag_ETH_BAK_DARPUSERADD_S
{
    ULONG      ulMsgType;        /* ��Ϣ���� */
    ULONG      ulLen;            /* ���ĳ��� */
    ULONG      ulIpAddr;         /* ��ַ */
    ULONG      ulIfIndex;        /* �ӿ����� */
    UCHAR      ucDArpUserAddflag; /* ��̬ARP�û���ӱ�� */
    UCHAR      ucPadding[3];
}ETH_BAK_DARPUSERADD_S;

typedef struct tag_ETH_BAK_SARPCONFLICT_S
{
    ULONG      ulMsgType;               /* ��Ϣ���� */
    ULONG      ulLen;                   /* ���ĳ��� */
    ULONG      ulIpAddr;                /* ��ַ */
    ULONG      ulVrfId;                 /* ʵ���� */
    UCHAR      ucSArpConflictFlag;      /* ��̬ARP�Ͷ�̬ARP��ͻ��� */
    UCHAR      ucPadding[3];
}ETH_BAK_SARPCONFLICT_S;

typedef struct tag_ETH_SUB_HEAD_BAK
{
    ULONG    ulMsgType; /* ��Ϣ���� */
    ULONG    ulLength;   /* ���ݱ��ĵ��ܳ���*/
} ETH_SUB_HEAD_BAK_S ;

typedef struct tag_ETH_BAK_ARPCAPTURE_S
{
    ULONG     ulMsgType;        /*��Ϣ����*/
    ULONG     ulLen;            /*���ĳ���*/
    ULONG     ulIfIndex;        /* �ӿ����� */
    ULONG     ulRcvCaptureQueLen;  /* ���ն��г��� */
    ULONG     ulSndCaptureQueLen;  /* ���Ͷ��г��� */
}ETH_BAK_ARPCAPTURE_S;

#define ETH_REALTIME_BAK         0
#define ETH_BATCH_BAK            1

/*ÿ�������ݵ�ARP����*/
#define  ETH_BAK_MAX_ITEM        20  

/*��̫������Ϣ�ײ�����*/
#define  ETH_BAK_HEAD_LEN       (sizeof(ETH_BAK_S) + sizeof(HAMSGHEADER_S))

/*��������������ֻ�����巢�͵�ʱ����ã����ԣ�����������˱���Vrf��Ϣ*/
/* ���ݾ�̬ARP*/
#define ETHARP_BAK_STATIC_ARP(from, to )\
{\
    (to)->ulIpAddr   =  (from)->ulRtIpAddr ;\
    (to)->ucFlags    =  (UCHAR)((from)->ulFlags) ;\
    (to)->ulIfIndex  =  (from)->ulRtIfIndex;\
    (to)->ulVrfIndex  =  (from)->ulVrfIndex;\
    (to)->usVID      =  (from)->usVID;\
    (VOID)TCPIP_Mem_Copy((to)->szMac,MACADDRLEN,(from)->ucMacAddr,MACADDRLEN);\
}

/* ���ݶ�̬ARP*/
#define ETHARP_BAK_DYNAMIC_ARP(from, to )\
{ \
    (to)->ulIfIndex   =  (from)->ulRtIfIndex ;\
    (to)->ulIpAddr    =  (from)->ulRtIpAddr ;\
    (to)->ucFlags     =  (UCHAR)((from)->ulFlags) ;\
    (to)->ulRtExpire  =  (from)->ulRtExpire ;\
    (to)->ulVrfIndex  =  (from)->ulVrfIndex;\
    (to)->usVID       =  (from)->usVID;\
    (to)->ucSourceType = (from)->ucSourceType;\
    (VOID)TCPIP_Mem_Copy((to)->szMac,MACADDRLEN,(from)->ucMacAddr,MACADDRLEN);\
}
/* End: VISP Support multi-instance project */


/* ����������Ϣ */
#define ETHARP_BAK_SND_CFG_INFO(from, to )\
{ \
    (to)->ulIfIndex     =  ((from)->pMtSoftIf)->if_ulIfIndex ;\
    (to)->usIsARPproxy  = (USHORT)((from)->bIsARPproxy) ;\
    (to)->ucEnableSpecArpPrxy    = (UCHAR)((from)->bEnableSpecArpPrxy) ;\
    (to)->ucVlanflag    =  (UCHAR)((from)->ulVlanFlag) ;\
    (VOID)TCPIP_Mem_Copy((to)->ucBakEthMac,MACADDRLEN,(from)->ucEthernetHeader,MACADDRLEN);\
}

/* �ָ�������Ϣ */
#define ETHARP_BAK_RCV_CFG_INFO(from, to )\
{ \
    (to)->bIsARPproxy  = (BOOL_T)((from)->usIsARPproxy) ;\
    (to)->bEnableSpecArpPrxy = (BOOL_T)((from)->ucEnableSpecArpPrxy);\
    (to)->ulVlanFlag   = (ULONG)(from)->ucVlanflag;\
    (VOID)TCPIP_Mem_Copy((to)->ucBakEthMac,MACADDRLEN,(from)->ucBakEthMac,MACADDRLEN);\
}

#define  ETH_SUB_BAK_HEAD_LEN       (sizeof(ETH_SUB_HEAD_BAK_S) + sizeof(HAMSGHEADER_S))

/*����VLAN ID �ı�����Ϣ*/
#define ETHARP_BAK_SND_VLANID_INFO(from, to )\
{ \
    (to)->ulIfIndex     =  ((from)->pMtSoftIf)->if_ulIfIndex ;\
    (to)->ulVlanID      =  (from)->ulVlanId ;\
}

enum enumEthHaRetrunCode
{
    ETH_HA_OK,
    ETH_HA_ERR,                          /* 1 ʧ�� */
    ETH_HA_MALLOC_FAIL,                  /* 2 �����ڴ�ʧ�� */
    ETH_HA_NEED_DELAY,                   /* 3 ��Ҫ��ʱ */
    ETH_HA_WRITEHAQUE_FAIL,              /* 4 дHA����ʧ�� */ 
};


extern VOID *ETHARP_GetNextMt(VOID *pCur,VOID **ppNext);
extern ULONG ETHARP_OpenMtEntry (UINTPTR *pulWaitListHandle);
extern ULONG ETHARP_GetMtEntry (UINTPTR ulEntryWaitList, ETHARP_MTSOFTC_S **ppstMtSoftC);
extern ULONG ETHARP_CloseMtObject ( UINTPTR ulWaitListHandle);

extern ULONG ETHARP_HA_BatchBackup ();
extern ULONG ETHARP_HA_Input(UCHAR * pBuf, ULONG ulMsgLen);
extern ULONG ETHARP_HA_Smooth ();
extern ULONG ETHARP_HA_GetEthDbg (ULONG *pulDbg);
extern ULONG TCPIP_HA_SetEthDbg (ULONG ulDbg);
extern VOID ETHARP_HA_DebugOutPut(UCHAR *pBuf,ULONG ulMsgLen,ULONG ulCmd);
extern ULONG ETHARP_HA_GetVerboseDbg (ULONG *pulDbg);
extern ULONG ETHARP_HA_SetVerboseDbg (ULONG ulDbg);

extern ULONG ETHARP_SetDhcpflag (ULONG ulIfindex , ULONG ulflag);
extern ULONG ETHARP_HA_SendArpMsg (ULONG ulCmd ,ETHARP_ARPRTENTRY_S *pNode);
extern ULONG ETHARP_HA_SendCfgMsg (ETHARP_MTSOFTC_S    *pstMt);
extern ULONG ETHARP_HA_Clean();
extern VOID ETHARP_HA_NEW_Send_GlobalVar(ULONG ulSubType);
extern VOID ETHARP_HA_NEW_BatchGlobalVar(VOID);
extern ULONG ETHARP_HA_NEW_GlobalVarInput(UCHAR *pBuf, ULONG ulMsgLen);
ULONG  ETHARP_HA_SendVlanIDMsg (ULONG ulIfIndex , ULONG ulVlanTag);
extern ULONG  ETHARP_HA_SendRealTypeMsg (UCHAR * pstNeedBakData, ULONG ulBakLen, ULONG ulType);
extern ULONG ETHARP_HA_BuildOneTLV(UCHAR *pucBuf, UCHAR * pstNeedBakData, ULONG ulType, ULONG *pulLen);
extern ULONG ETHARP_HA_BuildBatchType(UCHAR **pucData, UCHAR *pucNeedbackData,UCHAR **pHaHead, 
                               UCHAR **pHaTail, ULONG ulType, ULONG *pulTlvNum, ULONG *pulTotalNum);

extern ULONG ETHARP_HA_BatchArpTLV();
extern ULONG ETHARP_HA_BatchEthTLV();

extern VOID ETHARP_HA_RestorDArpFlag(ETH_BAK_DARPUSERADD_S * pstBakDArp);
extern VOID ETHARP_HA_RestoreSArpConflict(ETH_BAK_SARPCONFLICT_S *pstBakSArp);
extern ULONG ETHARP_HA_BuildHeaderAndSend(UCHAR *pHaBufHead, UCHAR *pHaData);
extern VOID ETHARP_SArpConflictSmooth(VOID);
extern ULONG ETHARP_HA_SetISISFlag(ULONG ulIfIndex,ULONG ulISISFlag);

#ifdef  __cplusplus
}
#endif
#endif

