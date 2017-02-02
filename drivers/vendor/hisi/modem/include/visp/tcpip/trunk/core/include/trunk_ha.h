/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              trunk_ha.h
*
*  Project Code: VISPV1R6
*   Module Name: Trunk  
*  Date Created: 2006-12-6
*        Author: LY(57500)
*   Description: trunk HAͷ�ļ���������ص����ݽṹ���ꡢö���Լ�����������ģ�麯��������
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*-------------------------------------------------------------------------------
*  2006-12-6   LY(57500)        Create the first version.
*
*******************************************************************************/
#ifndef _TRUNK_HA_H
#define _TRUNK_HA_H

#ifdef  __cplusplus
extern  "C" {
#endif

/************ HA���ݽṹ�ͺ� **************/

/* ����HA��ͷ�Ĳ������� */
#define TRUNK_HA_BATCH              0x00          
#define TRUNK_HA_REALTIME           0x01

#define TRUNK_INFO_BAK_TYPE         0x0001  /* Trunk��Ϣ����*/
#define TRUNK_PORT_NEGO_BAK_TYPE    0x0002  /* �˿���Ϣ���� */
#define TRUNK_PORT_NONEGO_BAK_TYPE  0x0003  /* �˿���Ϣ���� */
#define TRUNK_GCFG_BAK_TYPE         0x0004  /* ȫ��������Ϣ */

/*#define TRUNK_REALTIME_BAK_TYPE  0x0003*/
/* ʵʱ������Ϣ����, ע����Ҫͬ���޸�g_aulRtPackLen �� g_aszRtBackDbgInfo */
enum enTrunkRealBackUpType
{
    TRUNK_REALTIME_TRUNK_CREATE = 0x0100,
    TRUNK_REALTIME_PORT_ADD,
    TRUNK_REALTIME_PORT_REMOVE,
    TRUNK_REALTIME_PORT_UP,
    TRUNK_REALTIME_PORT_DOWN,
    TRUNK_REALTIME_SET_PERIOD,
    TRUNK_REALTIME_SET_LACP,
    TRUNK_REALTIME_NEWREFPORT,      /* �ο��˿������仯 */
    TRUNK_REALTIME_HE_CHNGPERIOD,   /* �Զ�����ģʽ�仯 */
    TRUNK_REALTIME_TRUNK_BFDMODE,   /* ����trunk���Ա�˿������õ���bfd�Ự����Ч��ʽ */
    TRUNK_BAK_DYNMAC_INDEX,         /* ���Ӷ�̬��ȡtrunk mac����,Ϊ֧��������̬��ȡmacһ��,������������,����ʵʱ���ݺ���������,��ʹ�ô˱������� */
    TRUNK_BAK_NEGOUTTIME,           /* �����״�Э�̲�ͨ������澯֪ͨ��ʱ�� */
    TRUNK_BAK_PORTMAC,              /* trunk��Ա�˿�mac���� BC3D02043 ETH/TRUNK MAC����һ��ʱ��ʵ����Ҫ���� */
    TRUNK_BAK_SYS_PRI,              /* ʵʱ����ϵͳ���ȼ� */
    TRUNK_BAK_PORT_PRI,             /* ���ݶ˿����ȼ� */
    TRUNK_BAK_BACKUPMODE,           /* ���ݶ˿ڱ���ģʽ */
    TRUNK_BAK_MASTERPORT,           /* ����1:1ģʽ���˿� */
    TRUNK_BAK_RECOVERMODE,          /* ���ݶ˿ڻָ�ģʽ */
    TRUNK_BAK_ACTIVENUM,            /* ����M:Nģʽ����˿� */
    TRUNK_BAK_PASSIVEMODE,          /* ����������״̬ */
    TRUNK_BAK_SYS_PRI_BYID = 0x0114, /* ����Trunk��ϵͳ���ȼ� */
    TRUNK_BAK_PRODUCT_POLICY,       /* ����Trunk�Ĳ�Ʒ���Ʋ��� */
    /* ��ע�⡿: ���������ʵʱ��������, ��Ҫͬ���޸�g_aulRtPackLen �� g_aszRtBackDbgInfo */  
};

/* ���ݳ�����Ϣ��� */
#define TRUNK_HA_DBG_CLOSE      0
#define TRUNK_HA_DBG_OPEN       1

#define TKHA_DEBUG_INFO_LEN     256

/* ������Ϣ����� */
extern TRUNK_SHELL_CALLBACK_SET_S g_stTrunkShellApi;
#define TRUNK_HA_DEBUG(stErr) TCPIP_DebugOutput(stErr)

/* add by lijing for V1R6C02ά����ǿ��Ŀ */
/* LACPЭ����Ϣ�� */
typedef struct tagLacpNegoBak
{
    /* ������Ϣ */
    ULONG ulDefaulted;             /* �˿��Ƿ�Ϊdefaulted�˿� */
    UCHAR ucActorAdminState;       /* ���˶˿ڹ���״ֵ̬ */
    UCHAR ucActorOperState;        /* ���˶˿�����״ֵ̬ */
    USHORT usActorAdminKey;        /* ���˶˿ڹ���Key */
    USHORT usActorOperKey;         /* ���˶˿�����Key */
    USHORT usActorPortPri;         /* ���˶˿����ȼ� */
    USHORT usActorPortIndex;       /* ���˶˿ں� */

    /* �Զ���Ϣ */
    UCHAR ucPartnerAdminState;     /* �Զ˶˿ڹ���״ֵ̬ */
    UCHAR ucPartnerOperState;      /* �Զ˶˿�����״ֵ̬ */
    USHORT usPartnerAdminKey;      /* �Զ˶˿ڹ���KEY */
    USHORT usPartnerOperKey;       /* �Զ˶˿�����Key */
    USHORT usPartnerAdminPortPri;  /* �Զ˶˿ڹ������ȼ� */
    USHORT usPartnerOperPortPri;   /* �Զ˶˿��������ȼ� */
    USHORT usPartnerAdminPortIndex; /* �Զ˶˿ڹ���˿ں� */
    USHORT usPartnerOperPortIndex;  /* �Զ˶˿������˿ں� */
    USHORT usPartnerAdminSysPri;   /* �Զ�ϵͳ�������ȼ� */
    USHORT usPartnerOperSysPri;    /* �Զ�ϵͳ�������ȼ� */
    UCHAR ucPartnerAdminSysMac[TRUNK_MACADDR_LEN]; /* �Զ�ϵͳ����physical��ַ */
    UCHAR ucPartnerOperSysMac[TRUNK_MACADDR_LEN];  /* �Զ�ϵͳ����physical��ַ */
}LACP_NEGO_BAK_S;


/* �˿ڱ�����Ϣ LACPЭ����Ϣ�� 64�ֽ�*/
typedef struct tagTrunkPortNegoBak
{
    ULONG ulTrunkId;        /* Trunk ID��0��31��        */
    ULONG ulIfIndex;        /* ��Ա�˿ڵĽӿ�����       */
    ULONG ulLacpStatus;             /* �˿�״̬             */
    UCHAR ucOldMacAddress[TRUNK_MACADDR_LEN];       /* ��Ա�˿ڼ���Trunkǰ��physical��ַ */
    UCHAR ucReserved[2];            /* �����ֶ�                     */
    LACP_NEGO_BAK_S stLacpNegoBak;      /* ���ݵ�Э����Ϣ��             */
}TRUNK_PORT_NEGO_BAK_S;

/* �˿ڱ�����Ϣ NOLACPЭ����Ϣ�� 20�ֽ�*/
typedef struct tagTrunkPortNoNegoBak
{
    ULONG ulTrunkId;        /* Trunk ID��0��31��    */
    ULONG ulIfIndex;        /* �˿ڵĽӿ�����       */
    ULONG ulLacpStatus;             /* �˿�״̬             */
    UCHAR ucOldMacAddress[TRUNK_MACADDR_LEN];       /* ��Ա�˿ڼ���Trunkǰ��physical��ַ */
    UCHAR ucReserved[2];            /* �����ֶ�                     */
}TRUNK_PORT_NONEGO_BAK_S;

/* Trunk������Ϣ 24�ֽ� */
typedef struct tagTrunkInfoBak
{
    ULONG ulTrunkId;        /* Trunk ID��0��31��    */
    ULONG ulIfIndex;        /* Trunk�ӿ�����        */
    ULONG ulEnableLacp;     /* �Ƿ�ʹ��LACP��Ĭ��Ϊʹ�� */
    ULONG ulRefIfIndex;     /* �ο��˿ڵĽӿ�����   */
    UCHAR ucMacAddress[TRUNK_MACADDR_LEN];  /* Trunk�ӿ�physical��ַ     */
    UCHAR ucBfdTrunkMode;             /* trunk���Ա�˿��Ͻ�������bfd�Ự����Чģʽ,Ĭ��trunk���� */   
    UCHAR ucPadding[1];
}TRUNK_INFO_BAK_S;

/* ȫ��������Ϣ 8�ֽ� */
typedef struct tagTrunkGCfgBak
{
    UCHAR   g_ucSysMacAddress[TRUNK_MACADDR_LEN];   /* Trunk�ӿ�physical��ַ     */
    USHORT  g_usSysPri;             /* ��¼Trunkģ���ϵͳ���ȼ�����LACPЭ��ʹ�� */ 
}TRUNK_GCFG_BAK_S;

/* TRUNK������Ϣͷ 4 �ֽ� */
typedef struct tagTrunk_HEAD_BAK
{
    USHORT usType;          /* ������Ϣ������       */
    USHORT usLen;           /* ������Ϣ�鳤��       */
} TRUNK_HEAD_BAK_S;

/* HA ͷ���� + Trunk HA ͷ���� */
#define TKHA_HDR_LEN (sizeof(HAMSGHEADER_S)+sizeof(TRUNK_HEAD_BAK_S))


typedef struct tagTrunkPortAddBak
{
    ULONG ulIfIndex;
    ULONG ulTrunkId;
    USHORT usPri;
    USHORT usPadding;
}TRUNK_PORTADD_BAK_S;

typedef struct tagTrunkSetLacpBak
{
    ULONG ulIfIndex;
    ULONG ulValue;
}TRUNK_SETLACP_BAK_S;

typedef struct tagTrunkSetPeriodBak
{
    ULONG ulIfIndex;
    ULONG ulPeriod;
}TRUNK_SETPERIOD_BAK_S;

typedef struct tagTrunkNewRefPortBak
{
    ULONG ulTrunkId;
    ULONG ulNewRefIndex;
}TRUNK_NEWREFPORT_BAK_S;

/* �Զ˸ı�����ģʽʵʱ������Ϣ�ṹ */
typedef struct tagTrunkHeChngPeriodBak
{
    ULONG ulIfIndex; /* �˿����� */
    UCHAR ucPartnerOperState;
    UCHAR ucReserved[3];
}TRUNK_HECHNGPERIOD_BAK_S;

/* ����trunk�Ͻ�������bfd�Ự����Чģʽ */
typedef struct tagBfdTrunkModeBak
{
    ULONG ulIfIndex; /* trunk���� */
    UCHAR ucBfdTrunkMode;
    UCHAR ucReserved[3];
}TRUNK_BFDMODE_BAK_S;

/* ����trunk��̬��ȡphysical��ַ����µĽӿ�����,�Ա�֤����һ�� */
typedef struct tagTrunkDynMacIndex
{
    ULONG  ulTrunkId;
    ULONG  ulMacPortIndex;
    UCHAR  ucMacAddress[TRUNK_MACADDR_LEN];  /* Trunk�ӿ�physical��ַ     */
    UCHAR  ucPadding[2];
}TRUNK_DYNMAC_INDEX;

/* trunk ��Ա�˿�physical��ַ���� */
typedef struct tagTrunkPortMac
{
    ULONG  ulTrunkId;
    ULONG  ulPortIndex;
    UCHAR  ucBakMacAddress[TRUNK_MACADDR_LEN];       /* �����Ա�˿ڵ�ʵ��physical��ַ */
    UCHAR  Padding[2];    
}TRUNK_PORTMAC_S;

/* ���ݶ˿����ȼ� */
typedef struct tagTrunkPortPri
{
    ULONG  ulPortIndex;
    ULONG  ulPortPri;
}TRUNK_PORT_PRI_S;

typedef struct tagTrunkBackupModeBak
{
    ULONG ulTrunkId;
    ULONG ulMode;
}TRUNK_BACKUPMODE_BAK_S;

typedef struct tagTrunkMasterPortBak
{
    ULONG ulTrunkId;
    ULONG ulMasterIfIndex;
}TRUNK_MASTERPORT_BAK_S;

typedef struct tagTrunkRecoverModeBak
{
    ULONG ulTrunkId;
    ULONG ulMode;
}TRUNK_RECOVERMODE_BAK_S;

typedef struct tagTrunkActiveNumBak
{
    ULONG ulTrunkId;
    ULONG ulActiveNum;
}TRUNK_ACTIVENUM_BAK_S;

typedef struct tagTrunkPassiveBak
{
    ULONG ulTrunkId;
    ULONG ulPassive;
}TRUNK_PASSIVE_BAK_S;

typedef struct tagTrunkSysPriByIdBak
{
    ULONG ulTrunkId;
    USHORT usSysPri;
    USHORT usPadding;
}TRUNK_SYSPRI_BYID_BAK_S;

/* Add by shuxieliu00176784/baiweiqiang00177000, at 2011-06-29. �޸�ԭ��: ��Ʒ���Ʋ��Ա���  */
typedef struct tagTrunkProductPolicyBak
{
    ULONG ulTrunkId;
    ULONG ulProductPolicy;
}TRUNK_PRODUCT_POLICY_BAK_S;


/* ����TRUNK HA ������������� */
enum tagTrunkHAErr
{
    PACK_TRUNK_OK =  VOS_OK,
    PACK_TRUNK_ERR = VOS_ERR,
    PACKET_TOO_LONG,
    TRUNK_NEED_PACK,
    TRUNK_NO_NEED_PACK   
};

/* ����HA���ĵ�ͷ(�ⲿ����) */
#define HA_HEAD_TRUNK_SET(pucData, ucBakOperation, usBakMsgLen)\
{\
    HAMSGHEADER_S* pstHaHdr = NULL;\
    pstHaHdr = (HAMSGHEADER_S *)(pucData);\
    pstHaHdr->usMsgLen = (USHORT)usBakMsgLen;\
    pstHaHdr->ulSeq = 0;\
    pstHaHdr->ucModID = (UCHAR)HA_MID_TRUNK;\
    pstHaHdr->ucOperation = (UCHAR)ucBakOperation;\
}

/* ����TRUNK HA�ڲ����ĵ�ͷ*/
#define HA_TRUNK_HEAD_BAK_SET(pstTrunkHeadBak, usBakType, usBakLen)\
{\
    (pstTrunkHeadBak)->usType = (USHORT)(usBakType);\
    (pstTrunkHeadBak)->usLen = (USHORT)(usBakLen);\
}

/* add by lijing for V1R6C02ά����ǿ��Ŀ */
/* ����Trunk LacpЭ����Ϣ*/
#define HA_TRUNK_LACP_NEGO_BAK_SET(stLacpNegoTo, stLacpNegoFrom)\
{\
    stLacpNegoTo.ulDefaulted = stLacpNegoFrom.ulDefaulted;\
    stLacpNegoTo.ucActorAdminState = stLacpNegoFrom.ucActorAdminState;\
    stLacpNegoTo.ucActorOperState = stLacpNegoFrom.ucActorOperState;\
    stLacpNegoTo.usActorAdminKey = stLacpNegoFrom.usActorAdminKey;\
    stLacpNegoTo.usActorOperKey = stLacpNegoFrom.usActorOperKey;\
    stLacpNegoTo.usActorPortPri = stLacpNegoFrom.usActorPortPri;\
    stLacpNegoTo.usActorPortIndex = stLacpNegoFrom.usActorPortIndex;\
    stLacpNegoTo.ucPartnerAdminState = stLacpNegoFrom.ucPartnerAdminState;\
    stLacpNegoTo.ucPartnerOperState = stLacpNegoFrom.ucPartnerOperState;\
    stLacpNegoTo.usPartnerAdminKey = stLacpNegoFrom.usPartnerAdminKey;\
    stLacpNegoTo.usPartnerOperKey = stLacpNegoFrom.usPartnerOperKey;\
    stLacpNegoTo.usPartnerAdminPortPri = stLacpNegoFrom.usPartnerAdminPortPri;\
    stLacpNegoTo.usPartnerOperPortPri = stLacpNegoFrom.usPartnerOperPortPri;\
    stLacpNegoTo.usPartnerAdminPortIndex = stLacpNegoFrom.usPartnerAdminPortIndex;\
    stLacpNegoTo.usPartnerOperPortIndex = stLacpNegoFrom.usPartnerOperPortIndex;\
    stLacpNegoTo.usPartnerAdminSysPri = stLacpNegoFrom.usPartnerAdminSysPri;\
    stLacpNegoTo.usPartnerOperSysPri = stLacpNegoFrom.usPartnerOperSysPri;\
    (VOID)TCPIP_Mem_Copy(stLacpNegoTo.ucPartnerAdminSysMac,TRUNK_MACADDR_LEN,stLacpNegoFrom.ucPartnerAdminSysMac, TRUNK_MACADDR_LEN);\
    (VOID)TCPIP_Mem_Copy(stLacpNegoTo.ucPartnerOperSysMac,TRUNK_MACADDR_LEN,stLacpNegoFrom.ucPartnerOperSysMac, TRUNK_MACADDR_LEN);\
}

#ifdef    __cplusplus
}
#endif      /* end of __cplusplus */

#endif      /* end of _TRUNK_HA_H */
