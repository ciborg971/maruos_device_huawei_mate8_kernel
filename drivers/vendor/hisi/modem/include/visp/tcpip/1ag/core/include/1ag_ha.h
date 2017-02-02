/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              1ag_ha.h
*  Project Code: VISPV100R007
*   Module Name: 1AG  
*  Date Created: 2008-3-3
*        Author: yebo(62007)
*   Description: 1AGģ��HA����
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2008-3-3  yebo(62007)         Create the first version.
*
*******************************************************************************/
#ifndef _1AG_HA_H
#define _1AG_HA_H

#ifdef  __cplusplus
    extern "C"{
#endif

/*��������*/
enum eOam1agOperate
{
    OAM_1AG_CREATE,
    OAM_1AG_DELETE,
    OAM_1AG_UPDATE
};

/*oam1ag ������Ϣ������*/
enum eOam1agBakType
{
    OAM_1AG_GLOBAL = 0x1000,
    OAM_1AG_MDINFO = 0x2000,
    OAM_1AG_MAINFO = 0x3000,
    OAM_1AG_MEPINFO = 0x4000,
    OAM_1AG_RMEPINFO = 0x5000,
    OAM_1AG_COMPATILE = 0x6000,
    /* Add for V2R3C06, by shuxieliu00176784, at 2011-10-04. �޸�ԭ��:  ����ȫ��Э��汾 */
    OAM_1AG_VERSION = 0x7000    
};

/*TLV ����*/
enum eOam1agTlvType
{
    OAM_1AG_HAMDNAME,
    OAM_1AG_HAMANAME,
    OAM_1AG_HARMEPTLV,
    OAM_1AG_HAMEP1AGVERSIONTLV,
    OAM_1AG_HAMEPVLANFLAGTLV,
    OAM_1AG_HARMEPTLV2,
    OAM_1AG_HAMEPLOSSDETECTTLV,
    OAM_Y1731_HAMAAISENABLETLV,
     
};

/* 1AG ��������Ϣ����ͷ */
typedef struct tagOAM1AG_HEAD_BAK
{
    USHORT usBakType;
    USHORT usBakLen;
}OAM1AG_HEAD_BAK_S;

/*MD����TLV��MD���ֳ��ȿɱ�*/
typedef struct tagOAM1AG_MDTLV_BAK
{
    USHORT usType;   /*��������*/
    USHORT usLength;  /*���ĳ���*/
    UCHAR  szMDName[OAM_1AG_MAX_MDNAME_LEN + 1]; /*MD����*/
}OAM1AG_MDTLV_BAK_S;

/*MA����TLV��MD���ֳ��ȿɱ�*/
typedef struct tagOAM1AG_MATLV_BAK
{
    USHORT usType;   /*��������*/
    USHORT usLength;  /*���ĳ���*/
    UCHAR  szMAName[OAM_1AG_MAX_MANAME_LEN + 1]; /*MA����*/
}OAM1AG_MATLV_BAK_S;


/*���ݱ������ȼ�,����������*/
typedef struct tagOAM1AG_PKTGLOBAL_BAK
{
    ULONG ulPktType;   /*��������*/
    UCHAR ucPktPriority;  /*�������ȼ�*/
    UCHAR ucRes[3];
}OAM1AG_PKTGLOBAL_BAK_S;

/*����1agЭ�������ȫ������TLV*/
typedef struct tagOAM1AG_COMPATIBLE_BAK
{
    ULONG ulCompatible;/*�����Կ���*/
}OAM1AG_COMPATIBLE_BAK_S;

/*����MD,����������*/
typedef struct tagOAM1AG_MD_BAK
{
    UCHAR ucMdLevel;    /*MD����*/
    UCHAR ucRes[3];
}OAM1AG_MD_BAK_S;

/*����MA,����������*/
typedef struct tagOAM1AG_MA_BAK
{
    USHORT usVlanId ;    /*MA������VLAN IDֵ*/
    UCHAR  ucCcmInterval;/*CCM���ͼ��*/
    UCHAR  ucCompatibleFlag;/*���ݱ��,0-Ϊ��׼ģʽ,1-��ͨģʽ*/
    UCHAR  ucMaVlanPri;      /*����MA��VLAN���ȼ�*/
    UCHAR  ucRes[3];
}OAM1AG_MA_BAK_S;

typedef struct tagOAMY1731_MAAISENABLETLV_BAK
{
    USHORT usType;                /*TLV����*/
    USHORT usLength;              /*TLV����*/
    UCHAR  ucAisEnable;           /* �Ƿ�ʹ��AIS���ܱ�� */
    UCHAR  ucRes[3];              /*�����ֶ�*/
}OAMY1731_MAAISENABLETLV_BAK_S;

/* MA TLV�����ֶ� ���������� */
typedef struct tagOAM1AG_MATLV_DATA
{
    UCHAR  ucMaAisEnable;         /* ����MA��AISʹ�ܱ�� */
    UCHAR  ucPadding[3];          /* �����ֶ� */
}OAM1AG_MATLV_DATA_S;

/*����MEP,����������*/
typedef struct tagOAM1AG_MEP_BAK
{ 
    ULONG  ulIfIndex;      /*�����ӿ�����*/
    USHORT usMepId;        /*MEP ID*/
    UCHAR  ucCcSendEnable; /*�Ƿ�ʹ��CCM���͹��ܱ��*/
    UCHAR  ucRes[1];
}OAM1AG_MEP_BAK_S;

/* MEP 1AG �汾��Ϣ����TLV */
typedef struct tagOAM1AG_MEP1AGVERSIONTLV_BAK
{
    USHORT usType;                /*TLV����*/
    USHORT usLength;              /*TLV����*/
    UCHAR  uc1agVersion;          /*1AG�汾��Ϣ*/
    UCHAR  ucRes[3];              /*�����ֶ�*/
}OAM1AG_MEP1AGVERSIONTLV_BAK_S;

/* MEP VLAN FLAG����TLV */
typedef struct tagOAM1AG_MEPVLANFLAGTLV_BAK
{
    USHORT usType;                /*TLV����*/
    USHORT usLength;              /*TLV����*/
    UCHAR  ucVlanFlag;            /*1AG VLAN FLAG*/
    UCHAR  ucRes[3];              /*�����ֶ�*/
}OAM1AG_MEPVLANFLAGTLV_BAK_S;

/* MEP Loss Detect TLV�����ֶ� */
typedef struct tagOAM1AG_MEPLOSSDETECTTLV_BAK
{
    USHORT usType;                /*TLV����*/
    USHORT usLength;              /*TLV����*/
    USHORT usLossDetectTimer;     /*ccm lost detect timer*/
    UCHAR  ucRes[2];              /*�����ֶ�*/
}OAM1AG_MEPLOSSDETECTTLV_BAK_S;

/* MEP TLV�����ֶ� */
typedef struct tagOAM1AG_MEPTLV_DATA
{
    UCHAR  uc1agVersion;          /*1AG�汾��Ϣ*/
    UCHAR  ucVlanFlag;            /*1AG VLAN FLAG*/
    USHORT usLostDetect;          /*Loss���ʱ��*/
}OAM1AG_MEPTLV_DATA_S;


/*����RMEP,����������*/
typedef struct tagOAM1AG_RMEP_BAK
{
    ULONG  ulIfIndex;         /*RMEP���ӿ�����*/
    USHORT usRmepId;          /*RMEP IDֵ*/
    USHORT usRMepOutTimerSet; /*Rmep����CCM�ĳ�ʱ����ֵ*/
    UCHAR  ucRemoteIfFlag;    /*Զ�˽ӿ�״̬���,ͬʱҲ�Ǹ澯���*/
    UCHAR  ucCcLost;          /*ccm LOST�澯���*/
    UCHAR  aucMacAddress[OAM_1AG_MACADDR_LEN];  /*RMEP physical��ַ*/
    UCHAR  ucCcmInterval;     /*�Զ˷��ͼ��*/
    UCHAR  ucRes[3];          /*����*/
}OAM1AG_RMEP_BAK_S;

/* ����RMEP�Ķ���̬��־,MD Level��־,�Ƿ��·���NP��־,�Լ���ʱʱ����ϻ�ʱ��ı���,��Щ�ֶ���֯��һ��TLV�� */
typedef struct tagOAM1AG_RMEPTLV_BAK
{
    USHORT usType;                /*TLV����*/
    USHORT usLength;              /*TLV����*/
    UCHAR  ucRMepStatic;          /*0��ʾ��̬���ɵ�RMEP ��1��ʾ��̬������RMEP*/
    UCHAR  ucMdLevelFlag;         /*MD ����,1-���ڱ�����,0-���ڱ�����*/ 
    UCHAR  ucDownloadNp;          /*��1Ϊ��RMEP�·���NP,�����͸���RMEPʱ����ʹ�����屸�ݹ�����ֵ,
                                    ɾ��RMEPʱ,����ͨ��ԭ��ɾ�����������̽����Ƿ��·�NPɾ���Ķ���*/    
    UCHAR  ucRes;                 /*����*/
    ULONG  ulRMepOldTimerSet;     /*Rmep��ʱ���ϻ�����ֵ*/
    ULONG  ulRMepOldTimerCount;   /*Rmep�ϻ�����ֵ*/    
    USHORT usRMepOutTimerCount;   /*Rmep����CCM�ĳ�ʱ����ֵ*/
    USHORT usRes;                 /*Rmep����CCM�ĳ�ʱ����ֵ�Ѿ��ڻ����������н����˱���,��������Ͳ�������*/
}OAM1AG_RMEPTLV_BAK_S;

/* ����rmep��Ϣ����tlv */
typedef struct tagOAM1AG_RMEPTLV2_BAK
{
    USHORT usType;                /*TLV����*/
    USHORT usLength;              /*TLV����*/
    UCHAR  ucVlanFlag;            /*�յ�CCM�����Ƿ����VLAN��� 0-����VLAN��1-��VLAN */
    UCHAR  ucMdLevel;             /*����remp MD����(�Զ�),��̬RMEP��û���յ�CCM֮ǰ����Ϊ����ʱ���ڵ�MD���� */  
    UCHAR  ucRmepCheck;           /*δ�յ�CCMǰ�Ƿ���NP�·�RMEP����ʹNP���Խ�����ͨ�Լ��*/
    UCHAR  ucRdiFlag;             /*��¼�Ƿ����յ�����RDI��CCM,�յ���MA�ڵĽ���RDI����Ҫ����*/
    ULONG  ulRes;                 /* ���� */
}OAM1AG_RMEPTLV2_BAK_S;

/* �����յ���RMEP��ر�����Ϣ.��TLV���ݹ�����RMEP��Ϣͳһ��¼�ڸýṹ��,�ýṹ�е��ֶβ�һ��������OAM1AG_RMEPTLV_BAK_S
   �ṹ���ݹ������ֶ�. Ҳ�������ɺ���������TLV�ֶα��ݹ�����RMEP�����Ϣ.
*/
typedef struct OAM1AG_RMEPTLV_DATA
{
    UCHAR  ucRMepStatic;          /*0��ʾ��̬���ɵ�RMEP ��1��ʾ��̬������RMEP*/
    UCHAR  ucMdLevelFlag;         /*MD ����,1-���ڱ�����,0-���ڱ�����*/ 
    UCHAR  ucDownloadNp;          /*��1Ϊ��RMEP�·���NP*/    
    UCHAR  ucVlanFlag;            /*�յ�CCM�����Ƿ����VLAN��� 0-����VLAN��1-��VLAN */
    ULONG  ulRMepOldTimerSet;     /*Rmep��ʱ���ϻ�����ֵ*/
    ULONG  ulRMepOldTimerCount;   /*Rmep�ϻ�����ֵ*/    
    USHORT usRMepOutTimerCount;   /*Rmep����CCM�ĳ�ʱ����ֵ*/
    UCHAR  ucMdLevel;             /*����remp MD����(�Զ�),��̬RMEP��û���յ�CCM֮ǰ����Ϊ����ʱ���ڵ�MD���� */  
    UCHAR  ucRmepCheck;           /*δ�յ�CCMǰ�Ƿ���NP�·�RMEP����ʹNP���Խ�����ͨ�Լ��*/
    UCHAR  ucRdiFlag;             /*��¼�Ƿ����յ�����RDI��CCM,�յ���MA�ڵĽ���RDI����Ҫ����*/
    UCHAR  ucRes[3];
}OAM1AG_RMEPTLV_DATA_S;

/* Add for V2R3C06, by shuxieliu00176784, at 2011-10-04. �޸�ԭ��: ����ȫ��Э��汾 */
typedef struct tagOAM1AG_VERSION_BAK
{
    ULONG ulGlobalVersion;/* ȫ��Э��汾 */
}OAM1AG_VERSION_BAK_S;


/* ���౸������Ϣ���ͺͳ�����ռ�Ŀռ��С */
#define OAM1AG_HEADBAK_LEN sizeof(OAM1AG_HEAD_BAK_S)

/* OAM1AG HA����HA������ͷ */
#define SET_OAM1AG_HA_HEAD(pucData, ucHAMid, ucBakOperation, usBakMsgLen)\
{\
    HAMSGHEADER_S* pstHaHdr = (HAMSGHEADER_S *)(pucData);\
    pstHaHdr->usMsgLen = usBakMsgLen;\
    pstHaHdr->ucModID = (UCHAR)ucHAMid;\
    pstHaHdr->ucOperation = (UCHAR)ucBakOperation;\
}

/* ��������Ϣ����,��������Ϣ���� */
#define SET_OAM1AG_HA_CHILDHEAD(pucBaseHead,ulHeadOffset,usType,usBakLen)\
{\
    OAM1AG_HEAD_BAK_S *pHeadBak = NULL;\
    pHeadBak = (OAM1AG_HEAD_BAK_S *)((UCHAR *)pucBaseHead + ulHeadOffset);\
    pHeadBak->usBakType = usType;\
    pHeadBak->usBakLen = usBakLen;\
}

/* ����MD/MA TLV���� ,����MD/MA TLV��Ϣ����,����ND/MA TLV��ֵ*/
#define SET_OAM1AG_HA_MDMATLV(pucBase,ulBaseOffet,aucMdName,usMdNameLen,aucMaName,usMaNameLen)\
{\
    OAM1AG_MDTLV_BAK_S  *pMdTlvInfo = NULL;\
    OAM1AG_MATLV_BAK_S  *pMaTlvInfo = NULL;\
    pMdTlvInfo = (OAM1AG_MDTLV_BAK_S *)((UCHAR *)pucBase + ulBaseOffet);\
    pMdTlvInfo->usType = OAM_1AG_HAMDNAME;\
    pMdTlvInfo->usLength = usMdNameLen + OAM1AG_HEADBAK_LEN;\
    (VOID)TCPIP_Mem_Copy(pMdTlvInfo->szMDName, OAM_1AG_MAX_MDNAME_LEN + 1, aucMdName,usMdNameLen);\
    pMaTlvInfo = (OAM1AG_MATLV_BAK_S *)((UCHAR *)pMdTlvInfo + pMdTlvInfo->usLength);\
    pMaTlvInfo->usType = OAM_1AG_HAMANAME;\
    pMaTlvInfo->usLength = usMaNameLen + OAM1AG_HEADBAK_LEN;\
    (VOID)TCPIP_Mem_Copy(pMaTlvInfo->szMAName, OAM_1AG_MAX_MANAME_LEN + 1, aucMaName,usMaNameLen);\
}                   

ULONG OAM_1AG_HA_BatchBackup(VOID);
ULONG OAM_1AG_HA_Smooth(VOID);
ULONG OAM_1AG_HA_Clean(VOID);
VOID  OAM_1AG_HA_RealBackup(UCHAR ucOperatorCode,USHORT usType,VOID *pData);
ULONG OAM_1AG_HA_OutputMsg(UCHAR * pucData, ULONG  ulDataLen);
ULONG OAM_1AG_HA_Input(UCHAR *pucData, ULONG ulDataLen);
ULONG OAM_1AG_HA_Restore(UCHAR * pucData, ULONG ulDataLen,UCHAR ucOperatorCode);
ULONG OAM_1AG_HA_RestoreInfo(UCHAR ucOperatorCode,USHORT usType,VOID *pData,VOID *pMdName,VOID *pMaName,
                                       VOID *pstTlvData);
ULONG OAM_1AG_HA_UpdateInfo(USHORT usType,UCHAR *pucMdName,UCHAR *pucMaName,VOID *pData,
                                 VOID *pstTlvData);
ULONG OAM_1AG_HA_CreateDynamicRmep(ULONG ulIfIndex, UCHAR *pucMacAddr, UCHAR * pszMdName, UCHAR * pszMaName,
                         USHORT usRmepId, VOID *pBaseData, VOID *pstTlvData);
ULONG OAM_1AG_HA_GlobalData(VOID);
ULONG OAM_1AG_HA_Batch1agInfo(USHORT usType);
ULONG OAM_1AG_HA_CfgPack(UCHAR *pucData,USHORT usBakTotalLen,USHORT usMsgOffset,
                         USHORT usType,VOID *pucNode,USHORT *pusBakNodeLen);
ULONG OAM_1AG_GetFirstNode(USHORT usType,ULONG *pulIndex,VOID *pNode, ULONG ulNodeBuffSize);
ULONG OAM_1AG_GetNextNode(USHORT usType,ULONG ulIndex,ULONG *pulNextIndex,VOID *pNode, ULONG ulNodeBufSize);
VOID  OAM_1AG_HA_DbgInfoOutput(UCHAR ucOperatorCode,USHORT usType,ULONG ulCmd);
ULONG OAM_1AG_HA_DebugOutPut(UCHAR *pucData, ULONG ulMsgLen, ULONG ulCmd);
ULONG OAM_1AG_SetHaVerboseDebug (ULONG ulFlag);
ULONG OAM_1AG_GetHaVerboseDebug (ULONG *pulFlag);
ULONG OAM_1AG_HA_CompatibleData(VOID);
/* Add for V2R3C06, by shuxieliu00176784, at 2011-10-04. �޸�ԭ��: ����ȫ��Э��汾*/
ULONG OAM_1AG_HA_VersionData(VOID);

#ifdef  __cplusplus
}
#endif

#endif

