/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              1ag_typ.h
*
*  Project Code: VISPV100R007
*   Module Name: 1AG  
*  Date Created: 2008-2-29
*        Author: yebo(62007)
*   Description: ����1AGö�ٱ������ṹ������
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2008-2-29   yebo(62007)      Create the first version.
*
*******************************************************************************/
#ifndef _1AG_TYP_H
#define _1AG_TYP_H

#ifdef  __cplusplus
        extern "C"{
#endif

/*-------------------------------�ṹ�����Ͷ���Begin------------------------------
---------------------------------------------------------------------------------*/
#pragma    pack(1)
/* VLAN��ǩ�ṹ�嶨�� */
typedef struct  tagOAM1AGVLANTAG
{
#if VRP_LITTLE_ENDIAN == VRP_YES
    USHORT  usVlanId   :12;                           /* VLanID */
    USHORT  usCfi      :1;                            /* 0��ʾphysical��ַ�Ǿ����ʽ��1��ʾphysical��ַ���Ǿ����ʽ��Ĭ����0 */
    USHORT  usPriority :3;                            /* �������ȼ� */
#else
    USHORT  usPriority :3;                            /* �������ȼ� */
    USHORT  usCfi      :1;                            /* 0��ʾphysical��ַ�Ǿ����ʽ��1��ʾphysical��ַ���Ǿ����ʽ��Ĭ����0 */
    USHORT  usVlanId   :12;                           /* VLanID */
#endif
}OAM1AG_VLANTAG_S;

/* Added begin for ֧�ֽ��ղ���VLANͷ��1AG����2009-05-14 */
/*OAM 1AG ����VLAN��SNAP��̫ͷ*/
typedef struct  tagOAM1AGNOVLANSNAPETHDR
{
    UCHAR   ucHdrDstMacAddr[OAM_1AG_MACADDR_LEN];     /*Ŀ��physical��ַ   */
    UCHAR   ucHdrSrcMacAddr[OAM_1AG_MACADDR_LEN];     /*Դphysical��ַ     */
    USHORT             usLen;                         /*��̫��������  */
    UCHAR              ucDSAP;                        /* destination service access point*/
    UCHAR              ucSSAP;                        /* source service access point */
    UCHAR              ucCtrl;                        /* control domain */
    UCHAR              ucORI[3];                              
    USHORT             usType;
}OAM1AG_NOVLAN_ETSNAPHDR_S;

/*OAM 1AG ����VLAN����̫ͷ*/
typedef struct tagOAM1AGNOVLANETHERHDR  
{
    UCHAR   ucHdrDstMacAddr[OAM_1AG_MACADDR_LEN];     /*Ŀ��physical��ַ   */
    UCHAR   ucHdrSrcMacAddr[OAM_1AG_MACADDR_LEN];     /*Դphysical��ַ     */
    USHORT  usType;                                   /* ��̫���� */
}OAM1AG_NOVLAN_ETHERHDR_S;
/* Added end for ֧�ֽ��ղ���VLANͷ��1AG����2009-05-14 */

/*OAM 1AG ��VLAN��SNAP��̫ͷ*/
typedef struct  tagOAM1AGSNAPETHDR
{
    UCHAR   ucHdrDstMacAddr[OAM_1AG_MACADDR_LEN];     /*Ŀ��physical��ַ   */
    UCHAR   ucHdrSrcMacAddr[OAM_1AG_MACADDR_LEN];     /*Դphysical��ַ     */
    USHORT  usVlanEthtype;                            /*0x8100*/
    OAM1AG_VLANTAG_S   stVlanTag;                     /* vlan��ǩ */
    USHORT             usLen;                         /*��̫��������  */
    UCHAR              ucDSAP;                        /* destination service access point*/
    UCHAR              ucSSAP;                        /* source service access point */
    UCHAR              ucCtrl;                        /* control domain */
    UCHAR              ucORI[3];                              
    USHORT             usType;
}OAM1AG_ETSNAPHDR_S;

/*OAM 1AG ��VLAN����̫ͷ*/
typedef struct tagOAM1AGETHERHDR
{
    UCHAR   ucHdrDstMacAddr[OAM_1AG_MACADDR_LEN];     /*Ŀ��physical��ַ   */
    UCHAR   ucHdrSrcMacAddr[OAM_1AG_MACADDR_LEN];     /*Դphysical��ַ     */
    USHORT  usVlanEthtype;                            /*0x8100*/
    OAM1AG_VLANTAG_S    stVlanTag;                    /* vlan��ǩ */
    USHORT  usType;                                   /* ��̫���� */
}OAM1AG_ETHERHDR_S;

/*����1agͷ��*/
typedef struct tagOam1agPubHead
{
#if VRP_LITTLE_ENDIAN == VRP_YES
    UCHAR ucVersion:5;                                /*MD�ļ���*/
    UCHAR ucMdLevel:3;                                /*�汾��*/
#else
    UCHAR ucMdLevel:3;
    UCHAR ucVersion:5;
#endif
    UCHAR ucOpcode;                                   /*CFM����֡����*/
    UCHAR ucFlag;                                     /*���*/
    UCHAR ucFirstTlvOffset;                           /*��һ��TLV��ƫ����*/
}OAM_1AG_PUBHEAD_S;

#if (VOS_ARM == VOS_HARDWARE_PLATFORM)
#pragma pack(0)
#else
#pragma pack()
#endif


/*MDȫ������ṹ*/
typedef struct tagOAM_1AG_MDCHAIN
{
    VOID *pstMdInfo;                                  /*ָ��Md���ƿ�,��ʼ��Ϊ��*/
}OAM_1AG_MDCHAIN_S;

/*MAȫ������ṹ*/
typedef struct tagOAM_1AG_MACHAIN
{
    struct tagOAM_1AG_MACHAIN *pstNext;               /*ָ����һ��MA*/
    VOID *pstMaInfo;                                  /*ָ��Ma���ƿ�,��ʼ��Ϊ��*/
}OAM_1AG_MACHAIN_S;

/*MEPȫ������ṹ*/
typedef struct tagOAM_1AG_MEPCHAIN
{
    DLL_NODE_S stDllNode;                             /*���ڳ�ʱ��ʱ���ķ���*/
    VOID *pstMepInfo;                                 /*ָ��Mep���ƿ�,��ʼ��Ϊ��*/
}OAM_1AG_MEPCHAIN_S;

/*RMEPȫ������ṹ*/
typedef struct tagOAM_1AG_RMEPCHAIN
{
    DLL_NODE_S stDllNode;                             /*���ڳ�ʱ��ʱ���ķ���*/
    VOID *pstRmepInfo;                                /*ָ��Rmep���ƿ�,��ʼ��Ϊ��*/
}OAM_1AG_RMEPCHAIN_S;

/*AIS MA ����ṹ*/
typedef struct tagOAM_Y1731_AISMACHAIN
{
    DLL_NODE_S stDllNode;                             /*���ڳ�ʱ��ʱ���ķ���*/
    VOID *pstAISMaInfo;                                /*ָ��MA ���ƿ�,��ʼ��Ϊ��*/
}OAM_Y1731_AISMACHAIN_S;

/*MD���ݽṹ*/
typedef struct tagOAM_1AG_MD
{
    DLL_S stMaDllList;                                /*MD��MA����*/
    UCHAR ucMdLevel;                                  /*MD����*/
    UCHAR ucMdNameType;                               /*MD��������,Ŀǰֻ֧���ַ�����ʽ*/
    UCHAR ucRes[2];    
    UCHAR szMDName[OAM_1AG_MAX_MDNAME_LEN + 1];       /*MD����,�Ϊ43�ֽ�*/
    ULONG ulMdIndex;                                  /*����MD����*/
    ULONG ulMdNameHash;                               /*MD����Hashֵ*/
}OAM_1AG_MD_S;

/*MA���ݽṹ*/
typedef struct tagOAM_1AG_MA
{
    DLL_NODE_S stDllNode;                           /*MD�½ڵ�*/
    DLL_S  stMepDllList;                            /*MA��MEP����*/
    DLL_S  stRmepDllList;                           /*MA��RMEP����*/
    USHORT usVlanId ;                               /*MA������VLAN IDֵ*/
    UCHAR  ucMaNameType;                            /*ma��������,Ŀǰֻ֧����ʽ*/
    UCHAR  ucCcmInterval;                           /*CCM���ͼ��*/
    UCHAR  szMaName[OAM_1AG_MAX_MANAME_LEN + 1];    /*ma���֣���󳤶�Ϊ43*/
    UCHAR  ucCompatibleFlag;                        /*���ݱ��,0-Ϊ��׼ģʽ,1-��ͨģʽ*/
    UCHAR  ucRdiFlag;                               /*MA ��RDI���,ͬʱҲ��RDI�澯�Ƿ���ʧ�ı��*/
    USHORT usRcvRdiCount;                           /*���յ���RDI����,˵����Զ���п��ܲ����˹��� */
    USHORT usSndRdiCount;                           /*���˵�RDI����,����ֵΪ0ʱ˵������û��MEP��������*/
    UCHAR  ucMaVlanPri;                             /*����MA��VLAN���ȼ�*/
    UCHAR  ucRes;
    ULONG  ulMdIndex;                               /*����MD����*/
    ULONG  ulMaIndex;                               /*����MA����*/
    ULONG  ulMaHashIndex;                           /*MA����*/
    UCHAR  ucAisEnable;                            /* AISʹ�ܿ���*/
    UCHAR  ucAisWarningFlag;                                /* AIS�澯��ʶ*/
    UCHAR  ucAisInterval;                         /*  AIS �������� */
    UCHAR  ucAisRes[1];    
    USHORT usAisOutTimerSet;                        /*AIS�澯��ʱ����ֵ*/
    USHORT usAisOutTimerCount;                      /*AIS�澯��ʱ����ֵ*/
}OAM_1AG_MA_S;

/* MEP���ݽṹ */
typedef struct tagOAM_1AG_MEP
{
    DLL_NODE_S stDllNode;                           /*MA��˫������ڵ�*/
    ULONG  ulMaIndex;                               /*����MA����*/
    ULONG  ulMepIndex;                              /*����MEP����*/
    ULONG  ulIfIndex;                               /*�����ӿ�����*/
    USHORT usMepId;                                 /*MEP ID*/
    UCHAR  ucCcSendEnable;                          /*�Ƿ�ʹ��CCM���͹��ܱ��*/    
    UCHAR  ucPad1;                                  /* ���1�ֽ� */
    USHORT usMepOutTimerSet;                        /*mep��ʱ����CCM����ֵ*/
    USHORT usMepOutTimerCount;                      /*mep��ʱ����CCm����ֵ*/
    UCHAR  ucLevel;                                 /*MEP����,ͬ����MD����,�����ж�*/


    UCHAR  ucMultiFlag;                             /* ��־ɾ������MEPʱ�Ƿ���Ҫ�·��˳��ಥ������ */
                                                    
    UCHAR  uc1agVersion;                            /* ��MEPʹ�õ�1AG�汾��,0:Draft7�汾;1:��׼�汾;2:Y1731�汾 */
    UCHAR  ucVlanFlag;                              /*��MEP�·��͵ı����Ƿ��VLANͷ��־.
                                                      0:��ʾ����Ҫ��VLANͷ,1��ʾ��Ҫ��VLAN*/
    OAM_1AG_STAT_S stMepStat;                       /*MEPͳ����Ϣ*/
    USHORT usLossDetectTimer;                       /*����MEP��Loss���ʱ��*/                                                  
    UCHAR  ucPadding[2];                            /*padding*/
    MEP_PM_INFO_S stPMCheckDLM;
    MEP_PM_INFO_S stPMCheckSLM;
    MEP_PM_INFO_S stPMCheckDDM; 
}OAM_1AG_MEP_S;

/* RMEP���ܼ�����Ϣ */
typedef struct tagRMEP_PM_INFO
{
    USHORT usMepId;
    USHORT usPMEnableFlag;
}RMEP_PM_INFO_S;

/* RMEP���ݽṹ */
typedef struct tagOAM_1AG_RMEP
{
    DLL_NODE_S stDllNode; 
    ULONG  ulMaIndex;                               /*����MA��������*/
    ULONG  ulRmepIndex;                             /*RMEP��������*/
    ULONG  ulIfIndex;                               /*RMEP���ӿ�����*/
    ULONG  ulRMepOldTimerSet;                       /*Rmep��ʱ���ϻ�CCM����ֵ*/
    ULONG  ulRMepOldTimerCount;                     /*rmep�ϻ�CCm����ֵ*/
    USHORT usRmepId;                                /*RMEP IDֵ*/
    USHORT usRMepOutTimerSet;                       /*Rmep��ʱ����CCM����ֵ*/
    USHORT usRMepOutTimerCount;                     /*Rmep��ʱ����CCm����ֵ*/
    UCHAR  ucRemoteIfFlag;                          /*Զ�˽ӿ�״̬���,ͬʱҲ�Ǹ澯���*/
    UCHAR  ucCcLost;                                /*ccm LOST�澯���*/
    UCHAR  ucRdiFlag;                               /*��¼�Ƿ����յ�����RDI��CCM,�յ���MA�ڵĽ���RDI����Ҫ����*/
    UCHAR  ucMdLevelFlag;                           /*MD ����,1-���ڱ�����,0-���ڱ�����*/ 
    UCHAR  ucRMepStatic;                            /*0��ʾ��̬���ɵ�RMEP ��1��ʾ��̬������RMEP*/
    UCHAR  ucCcmInterval;                           /*�Զ�CCM���͸���*/
    UCHAR  aucMacAddress[OAM_1AG_MACADDR_LEN];      /*RMEP physical��ַ*/
    UCHAR  ucDownloadNp;                            /*��1Ϊ��RMEP�·���NP*/
    UCHAR  ucVlanFlag;                              /*�յ�CCM�����Ƿ����VLAN��� 0-����VLAN��1-��VLAN */
    UCHAR  ucMdLevel;                               /*����remp MD����(�Զ�),��̬RMEP��û���յ�CCM֮ǰ����Ϊ����ʱ���ڵ�MD���� */
    UCHAR  ucRmepCheck;                             /*δ�յ�CCMǰ�Ƿ���NP�·�RMEP����ʹNP���Խ�����ͨ�Լ��*/
    UCHAR  ucPadding[2];                            /*Padding*/
    ULONG  ulSequence;                              /*���к�*/
    RMEP_PM_INFO_S  stPMCheckDLM;                       /*˫��֡��ʧ���ʹ�ܱ��*/
    RMEP_PM_INFO_S  stPMCheckSLM;                       /*����֡��ʧ���ʹ�ܱ��*/
    RMEP_PM_INFO_S  stPMCheckDDM;                       /*˫����ʱ���ʹ�ܱ��*/

    OAM_1AG_RMEP_STAT_S stRMepStat;                              /* �յ���ccm����ͳ�� */
}OAM_1AG_RMEP_S;
/*---------------------------------------------------------------------------------------
---------------------------------------CCM_Struct_Begin----------------------------------*/
#pragma    pack(1)
/*��ͨCCM��TLV�ṹ*/
typedef struct tagOAM_1AG_INTERFACETLV
{
    UCHAR  ucType;                                  /*��TLV�ֶε�����*/
    USHORT usLength;                                /*TLV�ֶ���Valueֵ�ĳ���*/
    UCHAR  ucValue;                                 /*TLV�ֶ��е�Valueֵ*/
}OAM_1AG_INTERFACETLV_S;

/*CCM���ĵ�ģ��*/
typedef struct tagOAM_1AG_CCM_TEMPLET
{
#if VRP_LITTLE_ENDIAN == VRP_YES
    UCHAR ucVersion:5;                              /*MD�ļ���*/
    UCHAR ucMdLevel:3;                              /*�汾��*/
#else
    UCHAR ucMdLevel:3;
    UCHAR ucVersion:5;
#endif
    UCHAR ucOpcode;                                 /*CFM����֡����*/
#if VRP_LITTLE_ENDIAN == VRP_YES
    UCHAR ucInterval:3;                             /*CCM���ͼ��*/
    UCHAR ucReserve:4;
    UCHAR ucRdi:1;                                  /*RDIλ*/
#else
    UCHAR ucRdi:1;
    UCHAR ucReserve:4;
    UCHAR ucInterval:3;
#endif
    UCHAR ucTlvOffset;                              /*����ͷ����һ��TLV�ֶε�ƫ����*/
    ULONG ulSequence;                               /*���ĵ����к�*/
    USHORT usMepId;                                 /*MEP��ʶ*/
    UCHAR ucMdMaInfo[OAM_1AG_MAX_MDMAINFO_LEN];     /*����MD��MA�����͡����Ⱥ�����*/
}OAM_1AG_CCM_TEMPLET_S;

/*��װ�˶���ͷ���CCM����*/
typedef struct tagOAM_1AG_CCM_Packet
{
    
    OAM1AG_ETHERHDR_S      stEtherHeader;           /*��̫ͷ*/
    OAM_1AG_CCM_TEMPLET_S  stCcmTemplet;            /*���ĵ�ģ��*/
    OAM_1AG_INTERFACETLV_S stInterfaceTlv;          /*CCM���ĵĵ�һ��TLV*/
}OAM_1AG_CCM_PACKET_S;

typedef struct tagOAM_1AG_CCM_UPDATE_INFO
{
    UCHAR  ucVlanFlag;          /* �Զ˷��͵�CCM����Я��VLAN tag */
    UCHAR  ucMdLevel;           /* �Զ˷��͵�CCM���ĵ�MD ���� */
    UCHAR  ucPadding[2];
}OAM_1AG_CCM_UPDATE_INFO_S;

typedef struct tagOAM_Y1731_AIS_Packet
{
#if VRP_LITTLE_ENDIAN == VRP_YES
    UCHAR ucVersion:5;                                /*MD�ļ���*/
    UCHAR ucMdLevel:3;                                /*�汾��*/
#else
    UCHAR ucMdLevel:3;
    UCHAR ucVersion:5;
#endif
    UCHAR ucOpcode;                                   /*CFM����֡����*/
#if VRP_LITTLE_ENDIAN == VRP_YES
    UCHAR ucInterval:3;                                     /*AIS ��������*/
    UCHAR ucReserve:5;                                
#else
    UCHAR ucReserve:5;                                    
    UCHAR ucInterval:3;                                     /*AIS ��������*/
#endif
    UCHAR ucFirstTlvOffset;                           /*��һ��TLV��ƫ����*/  
    UCHAR  ucEndTlv;                                    /*��βTLV*/
}OAM_Y1731_AIS_PACKET_S;

#if (VOS_ARM == VOS_HARDWARE_PLATFORM)
#pragma pack(0)
#else
#pragma pack()
#endif


/*---------------------------------------CCM_Struct_End-----------------------------------
------------------------------------------------------------------------------------------*/
/*OAM 1AG mode Info*/
typedef struct tagOAM_1AG_MOD_INFO
{
    ULONG ulMID_Oam1ag;
    ULONG ulNpModel;  /*������NPģʽ*/
    ULONG ulDefaultVersion;  /* 1AGĬ��Э��汾*/
}OAM_1AG_MOD_INFO_S;

/*OAM1AG���Shell��Coreע��Ļص�������*/
typedef struct tagOam1agShellCallback
{
    VOID (*pfOAM_1AG_DebugInfo)(CHAR * szStr);
}OAM_1AG_SHELL_CALLBACK_S;

#pragma    pack(1)

/* 1AG-CFM-2007 LTM Egress TLV ��ʽ  */
typedef struct tagOAM_1AG_LTM_EGRESS_TLV
{
    UCHAR  ucType;                               /* ���� */
    USHORT usLength;                             /* ���� */
    UCHAR  aucEgressIdentifier[OAM_1AG_EGRESSID_SIZE];   /* ���ӿڱ�ʶ�� */
}OAM_1AG_LTM_EGRESS_TLV_S;

/* 1AG-CFM-2007 LTR Egress TLV ��ʽ  */
typedef struct tagOAM_1AG_LTR_EGRESS_TLV
{
    UCHAR  ucType;                                 /* ���� */
    USHORT usLength;                               /* ���� */
    UCHAR  aucLastEgressId[OAM_1AG_EGRESSID_SIZE]; /* ��һ�����ӿڱ�ʶ�� */
    UCHAR  aucNextEgressId[OAM_1AG_EGRESSID_SIZE]; /* ���س��ӿڱ�ʶ�� */    
}OAM_1AG_LTR_EGRESS_TLV_S;

/* ������˿���Ϣ��TLV */
typedef struct tagOAM_1AG_REPLYINGRESSTLV
{
    UCHAR ucType;                                /* ���� */
    USHORT usLength;                             /* ���� */
    UCHAR ucIngressAction;                       /* ��ӿڶ��� */ 
    UCHAR aucIngressMac[OAM_1AG_MACADDR_LEN];    /* ��ӿ�physical��ַ */
    UCHAR ucIngressPortIDLength;                 /* ��ӿڶ˿�ID���� */
    UCHAR ucIngressPortIDSubtype;                /* ��ӿڶ˿�ID������ */
    UCHAR aucIngressPortID[OAM_1AG_PORTID_SIZE]; /* ��ӿڶ˿�ID */
}OAM_1AG_REPLYINGRESSTLV_S;

/* �������˿���Ϣ��TLV */
typedef struct tagOAM_1AG_REPLYEGRESSTLV
{
    UCHAR ucType;                                /* ���� */
    USHORT usLength;                             /* ���� */
    UCHAR ucEgressAction;                        /* ���ӿڶ��� */
    UCHAR aucEgressMac[OAM_1AG_MACADDR_LEN];     /* ���ӿ�physical��ַ */
    UCHAR ucEgressPortIDLength;                  /* ���ӿڶ˿�ID���� */
    UCHAR ucEgressPortIDSubtype;                 /* ���ӿڶ˿�ID������ */
    UCHAR aucEgressPortID[OAM_1AG_PORTID_SIZE];  /* ���ӿڶ˿�ID */
}OAM_1AG_REPLYEGRESSTLV_S;

/* Y1731��˿���Ϣ��TLV */
typedef struct tagOAM_1AG_Y1731REPLYINGRESSTLV
{
    UCHAR ucType;                                /* ���� */
    USHORT usLength;                             /* ���� */
    UCHAR ucIngressAction;                       /* ��ӿڶ��� */ 
    UCHAR aucIngressMac[OAM_1AG_MACADDR_LEN];    /* ��ӿ�physical��ַ */
}OAM_1AG_Y1731REPLYINGRESSTLV_S;

/* Y1731���˿���Ϣ��TLV */
typedef struct tagOAM_1AG_Y1731REPLYEGRESSTLV
{
    UCHAR ucType;                                /* ���� */
    USHORT usLength;                             /* ���� */
    UCHAR ucEgressAction;                        /* ���ӿڶ��� */
    UCHAR aucEgressMac[OAM_1AG_MACADDR_LEN];     /* ���ӿ�physical��ַ */
}OAM_1AG_Y1731REPLYEGRESSTLV_S;


/* ���յ���LTR����Ϣ */
typedef struct tagOAM_1AG_LTR_RECV
{
    DLL_NODE_S stLtrNode;                           /* LTR�ڵ� */
    ULONG ulLTRSendId;                              /* LTR��ʶ�� */
    UCHAR aucDmac[OAM_1AG_MACADDR_LEN];             /* Ŀ�ĵ�ַ */
    UCHAR aucSmac[OAM_1AG_MACADDR_LEN];             /* Դ��ַ */
    UCHAR aucLastEgressId[OAM_1AG_EGRESSID_SIZE];   /* ��һ�����ӿڱ�ʶ�� */
    UCHAR aucNextEgressId[OAM_1AG_EGRESSID_SIZE];   /* ���س��ӿڱ�ʶ�� */
    UCHAR ucReplyTtl;                               /* �ظ�TTL */
    UCHAR ucReplyAction;                            /* �ظ����� */
    UCHAR ucFwdYes;                                 /* �Ƿ�ת�� */
    UCHAR ucIsMep;                                  /* �Ƿ�MEP */
    OAM_1AG_REPLYINGRESSTLV_S stReplyIngressTlv;    /* �ظ���ӿ�TLV*/
    OAM_1AG_REPLYEGRESSTLV_S stReplyEgressTlv;      /* �ظ����ӿ�TLV*/
}OAM_1AG_LTR_RECV_S;

/* Draft7Э���׼LTR���� */
typedef struct tagOAM_1AG_LTR_DRAFT7
{
#if VRP_LITTLE_ENDIAN == VRP_YES
    UCHAR ucVersion    :5;                         /* 1AG�汾 */  
    UCHAR ucLevel      :3;                         /* MD���� */
#else
    UCHAR ucLevel      :3;                         /* MD���� */
    UCHAR ucVersion    :5;                         /* 1AG�汾 */
#endif 
    UCHAR ucOpCode;                                /* ������ */
#if VRP_LITTLE_ENDIAN == VRP_YES
    UCHAR ucReserve    :6;   
    UCHAR ucIsMep      :1;                         /* �Ƿ�MEP */
    UCHAR ucFwdYes     :1;                         /* �Ƿ�ת�� */
#else
    UCHAR ucFwdYes     :1;                         /* �Ƿ�ת�� */
    UCHAR ucIsMep      :1;                         /* �Ƿ�MEP */
    UCHAR ucReserve    :6;   
#endif
    UCHAR ucFirstTlvOffset;                        /* ��һ��TLVƫ���� */
    ULONG ulLTRSendId;                             /* LTR��ʶ�� */
    UCHAR aucLastEgressId[OAM_1AG_EGRESSID_SIZE];  /* ��һ�����ӿڱ�ʶ�� */
    UCHAR aucNextEgressId[OAM_1AG_EGRESSID_SIZE];  /* ���س��ӿڱ�ʶ�� */
    UCHAR ucReplyTtl;                              /* �ظ�TTL */
    UCHAR ucReplyAction;                           /* �ظ����� */
    UCHAR aucReserve[6];
    OAM_1AG_REPLYINGRESSTLV_S stReplyIngressTlv;   /* �ظ���ӿ�TLV*/
    OAM_1AG_REPLYEGRESSTLV_S stReplyEgressTlv;     /* �ظ����ӿ�TLV*/
    UCHAR ucEndTlv;                                /* ����TLV */
}OAM_1AG_LTR_DRAFT7_S;

/* 1AG-CFM-2007Э���׼LTR���� */
typedef struct tagOAM_1AG_LTR_STD
{
#if VRP_LITTLE_ENDIAN == VRP_YES
    UCHAR ucVersion    :5;                         /* 1AG�汾 */  
    UCHAR ucLevel      :3;                         /* MD���� */
#else
    UCHAR ucLevel      :3;                         /* MD���� */
    UCHAR ucVersion    :5;                         /* 1AG�汾 */
#endif 
    UCHAR ucOpCode;                                /* ������ */
#if VRP_LITTLE_ENDIAN == VRP_YES
    UCHAR ucReserve    :5;   
    UCHAR ucIsMep      :1;                         /* �Ƿ�MEP */
    UCHAR ucFwdYes     :1;                         /* �Ƿ�ת�� */
    UCHAR ucUseFDBonly :1;
#else
    UCHAR ucUseFDBonly :1;
    UCHAR ucFwdYes     :1;                         /* �Ƿ�ת�� */
    UCHAR ucIsMep      :1;                         /* �Ƿ�MEP */
    UCHAR ucReserve    :5;   
#endif
    UCHAR ucFirstTlvOffset;                        /* ��һ��TLVƫ���� */
    ULONG ulLTRSendId;                             /* LTR��ʶ�� */
    UCHAR ucReplyTtl;                              /* �ظ�TTL */
    UCHAR ucReplyAction;                           /* �ظ����� */
}OAM_1AG_LTR_STD_S;

/* ��ͨ��ʽLTR���� */
typedef struct tagOAM_1AG_LTR_VRP
{
#if VRP_LITTLE_ENDIAN == VRP_YES
    UCHAR ucVersion    :5;                          /* 1AG�汾 */  
    UCHAR ucLevel      :3;                          /* MD���� */
#else
    UCHAR ucLevel      :3;                          /* MD���� */
    UCHAR ucVersion    :5;                          /* 1AG�汾 */
#endif    
    UCHAR ucOpCode;                                 /* ������ */
#if VRP_LITTLE_ENDIAN == VRP_YES
    UCHAR ucReserve    :6;   
    UCHAR ucIsMep      :1;                          /* �Ƿ�MEP */
    UCHAR ucFwdYes     :1;                          /* �Ƿ�ת�� */
#else
    UCHAR ucFwdYes     :1;                          /* �Ƿ�ת�� */
    UCHAR ucIsMep      :1;                          /* �Ƿ�MEP */
    UCHAR ucReserve    :6;   
#endif     

    UCHAR ucFirstTlvOffset;                         /* ��һ��TLVƫ���� */
    ULONG ulLTRSendId;                              /* LTR��ʶ�� */
    UCHAR aucLastEgressId[OAM_1AG_EGRESSID_SIZE];   /* ��һ�����ӿڱ�ʶ�� */
    UCHAR aucNextEgressId[OAM_1AG_EGRESSID_SIZE];   /* ���س��ӿڱ�ʶ�� */
    UCHAR ucReplyTtl;                               /* �ظ�TTL */
    UCHAR ucReplyAction;                            /* �ظ����� */
    UCHAR aucReserve[6];
    OAM_1AG_REPLYINGRESSTLV_S stReplyIngressTlv;    /* �ظ���ӿ�TLV*/
    OAM_1AG_REPLYEGRESSTLV_S stReplyEgressTlv;      /* �ظ����ӿ�TLV*/

    ULONG ulLspToken;                               /* ��0 */
    USHORT usVsiIndex;                              /* ��0xFFFF */
    UCHAR ucLtrPwFlag;                              /* ��0 */
    UCHAR ucBroadcastFlag;                          /* ��0 */
    UCHAR ucEndTlv;                                 /* ����TLV */
    UCHAR aucReserve2[3];
}OAM_1AG_LTR_VRP_S;

/* Draft7Э���׼LTM���� */
typedef struct tagOAM_1AG_LTM_DRAFT7
{
#if VRP_LITTLE_ENDIAN == VRP_YES
    UCHAR ucVersion    :5;                              /* 1AG�汾 */  
    UCHAR ucLevel      :3;                              /* MD���� */
#else
    UCHAR ucLevel      :3;                              /* MD���� */
    UCHAR ucVersion    :5;                              /* 1AG�汾 */
#endif
    UCHAR ucOpCode;                                     /* ������ */
    UCHAR ucFlag;                                       /* ��־ */
    UCHAR ucFirstTlvOffset;                             /* ��һ��TLVƫ���� */
    ULONG ulLTMSendId;                                  /* LTM��ʶ�� */
    UCHAR aucEgressIdentifier[OAM_1AG_EGRESSID_SIZE];   /* ���ӿڱ�ʶ�� */
    UCHAR ucTtl;                                        /* TTL,Ĭ��64 */
    UCHAR aucOriginalMac[OAM_1AG_MACADDR_LEN];          /* ����LTM��Դ��ַ */
    UCHAR aucTargetMac[OAM_1AG_MACADDR_LEN];            /* LTM��Ŀ�ĵ�ַ */
    UCHAR aucReserve[3];                                /* ֻ��Ϊ��ʵ�ֵķ��㣬Ҳ��Υ��Э�� */
    UCHAR ucEndTlv;                                     /* ����TLV */
}OAM_1AG_LTM_DRAFT7_S;

/* 1AG-CFM-2007��׼Э��LTM���� */
typedef struct tagOAM_1AG_LTM_STD
{
#if VRP_LITTLE_ENDIAN == VRP_YES
    UCHAR ucVersion    :5;                              /* 1AG�汾 */  
    UCHAR ucLevel      :3;                              /* MD���� */
#else
    UCHAR ucLevel      :3;                              /* MD���� */
    UCHAR ucVersion    :5;                              /* 1AG�汾 */
#endif
    UCHAR ucOpCode;                                     /* ������ */
#if VRP_LITTLE_ENDIAN == VRP_YES
    UCHAR ucReserve    :7;   
    UCHAR ucUseFDBonly :1;
#else
    UCHAR ucUseFDBonly :1;
    UCHAR ucReserve    :7;   
#endif

    UCHAR ucFirstTlvOffset;                             /* ��һ��TLVƫ���� */
    ULONG ulLTMSendId;                                  /* LTM��ʶ�� */
    UCHAR ucTtl;                                        /* TTL,Ĭ��64 */
    UCHAR aucOriginalMac[OAM_1AG_MACADDR_LEN];          /* ����LTM��Դ��ַ */
    UCHAR aucTargetMac[OAM_1AG_MACADDR_LEN];            /* LTM��Ŀ�ĵ�ַ */
}OAM_1AG_LTM_STD_S;

/* ��ͨ��ʽLTM���� */
typedef struct tagOAM_1AG_LTM_VRP
{
#if VRP_LITTLE_ENDIAN == VRP_YES
    UCHAR ucVersion    :5;                              /* 1AG�汾 */  
    UCHAR ucLevel      :3;                              /* MD���� */
#else
    UCHAR ucLevel      :3;                              /* MD���� */
    UCHAR ucVersion    :5;                              /* 1AG�汾 */
#endif    

    UCHAR ucOpCode;                                     /* ������ */
    UCHAR ucFlag;                                       /* ��־ */
    UCHAR ucFirstTlvOffset;                             /* ��һ��TLVƫ���� */
    ULONG ulLTMSendId;                                  /* LTM��ʶ�� */
    UCHAR aucEgressIdentifier[OAM_1AG_EGRESSID_SIZE];   /* ���ӿڱ�ʶ�� */
    UCHAR ucTtl;                                        /* TTL,Ĭ��64 */
    UCHAR aucOriginalMac[OAM_1AG_MACADDR_LEN];          /* ����LTM��Դ��ַ */
    UCHAR aucTargetMac[OAM_1AG_MACADDR_LEN];            /* LTM��Ŀ�ĵ�ַ */
    UCHAR aucReserve[3];
    ULONG ulLspToken;                                   /* ��0 */
    USHORT usVsiIndex;                                  /* ��0xFFFF */
    USHORT usLtrPwFlag;                                 /* ��0 */
    UCHAR ucBroadcastFlag;                              /* ��0 */
    UCHAR ucEndTlv;                                     /* ����TLV */
    UCHAR aucReserve2[13];
}OAM_1AG_LTM_VRP_S;

#if (VOS_ARM == VOS_HARDWARE_PLATFORM)
#pragma pack(0)
#else
#pragma pack()
#endif


/* �ѷ��͵�LTM����Ϣ */
typedef struct tagOAM_1AG_LTM_SENDOUTDATA
{
    DLL_S stLtrList;                         /* LTR���� */ 
    ULONG ulLTMSendId;                       /* LTM���ͱ�ʶ */
    ULONG ulExecID;                          /* �û�ID */
    ULONG ulSendTime;                        /* ����ʱ��� */
    ULONG ulTimeOut;                         /* ��ʱʱ�䣬��λ�� */
    ULONG ulTtl;                             /* ����Ŀ��MP��������� */
    ULONG ulReadResult;                      /* �ɶ�ȡ��־������Ϊ1����ʾ���Դ�ӡ֮���LTR��������Ӧ�����ȴ� */
    UCHAR aucTargetMac[OAM_1AG_MACADDR_LEN]; /* Ŀ��physical��ַ */
    UCHAR aucReserve[2];
}OAM_1AG_LTM_SENDOUTDATA_S;
/* ����LT����������Ĳ��� */
typedef struct tagOAM_1AG_LT_PARA
{
    UCHAR aucTargetMac[OAM_1AG_MACADDR_LEN];    /* Ŀ��MP��physical��ַ */
    UCHAR aucSourceMac[OAM_1AG_MACADDR_LEN];    /* ����MP��physical��ַ */
    ULONG ulExecID;                             /* �û�ID */
    ULONG ulIfIndex;                            /* ���ӿ� */
    ULONG ulMepIndex;                           /* ����LTM��MEP��ͳ����Ϣ�����ڴ�MEP */
    ULONG ulLTMSendId;                          /* LTM���ͱ�ʶ */
    ULONG ulTtl;                                /* ����Ŀ��MP��������� */
    ULONG ulTimeOut;                            /* ��ʱʱ�䣬��λ�� */
    USHORT usVlanId;                            /* VLanID */
    UCHAR ucLevel;                              /* MD���� */
    UCHAR ucFreeLtmIndex;                       /* ȫ��LTM�����п��нڵ����� */
}OAM_1AG_LT_PARA_S;
/* ���յ���LTM��Ϣ */
typedef struct tagOAM_1AG_LTM_RECV
{
    UCHAR aucDmac[OAM_1AG_MACADDR_LEN];                /* Ŀ�ĵ�ַ */
    UCHAR aucSmac[OAM_1AG_MACADDR_LEN];                /* Դ��ַ */
    USHORT usVlanId;                                   /* VLanID */
    USHORT usEthType;                                  /* ��̫�������� */
    UCHAR ucPriority;                                  /* �������ȼ� */
    UCHAR ucVersion;                                   /* 1AG�汾 */  
    UCHAR ucLevel;                                     /* MD���� */
    UCHAR ucOpCode;                                    /* ������ */
    UCHAR ucFlag;                                      /* ��־ */
    UCHAR ucTtl;                                       /* TTL,Ĭ��64 */
    UCHAR aucRes[2];                                   /* �����ֶ� */
    ULONG ulLTMSendId;                                 /* LTM��ʶ�� */
    UCHAR aucEgressIdentifier[OAM_1AG_EGRESSID_SIZE];  /* ���ӿڱ�ʶ�� */
    UCHAR aucOriginalMac[OAM_1AG_MACADDR_LEN];         /* ����LTM��Դ��ַ */
    UCHAR aucTargetMac[OAM_1AG_MACADDR_LEN];           /* LTM��Ŀ�ĵ�ַ */
}OAM_1AG_LTM_RECV_S;

/* Ҫ���͵�LTR����Ϣ */
typedef struct tagOAM_1AG_LTR_SEND
{
    DLL_NODE_S stLtrNode;       /* LTR�ڵ� */
    MBUF_S *pstMbuf;            /* Ҫ���͵�MBUF */
    ULONG ulIfIndex;            /* ���ӿ����� */
}OAM_1AG_LTR_SEND_S;

/* DCDataTLV Value */
typedef struct tagOAM_1AG_DCDataTLV_Value
{
    ULONG   ulCPTimeHigh;   /*�ϲ������ĸ����ֽڵ�ʱ���*/
    ULONG   ulCPTimeLow;    /*�ϲ������ĵ����ֽڵ�ʱ���*/
    ULONG   ulNPTimeHigh;   /*NP�����ĸ����ֽڵ�ʱ���*/
    ULONG   ulNPTimeLow;    /*NP�����ĸ����ֽڵ�ʱ���*/
}OAM_1AG_VRPDATATLV_VALUE_S;
#pragma pack(1)

/*��ͨData TLV�������Ͷ���*/
typedef struct tagOAM_1AG_VRPDataTLV
{
    UCHAR   ucType;                     /*TLV���ͳ�Ա*/
    USHORT  usLength;                   /*TLV���ȳ�Ա*/
    UCHAR   reserve;                    /*����*/
    OAM_1AG_VRPDATATLV_VALUE_S stValue; /*TLVֵ��Ա*/
}OAM_1AG_VRPDATATLV_S;

/*��׼��ʽTLV*/
typedef struct tagOAM_1AG_DataTLV
{
    UCHAR   ucType;                     /*TLV���ͳ�Ա*/
    USHORT  usLength;                   /*TLV���ȳ�Ա*/
    ULONG   ulValueHigh;                /*TLVֵ��Ա*/
    ULONG   ulValueLow;
}OAM_1AG_DATATLV_S;
/*��׼LB����ͷ��ʽ*/
typedef struct tagOAM_1AG_STDLBPACKET
{
#if VRP_LITTLE_ENDIAN == VRP_YES
    UCHAR   ucVersion    :5;       /* 1AG�汾 */  
    UCHAR   ucLevel      :3;       /* MD���� */
#else
    UCHAR   ucLevel      :3;       /* MD���� */
    UCHAR   ucVersion    :5;       /* 1AG�汾 */
#endif    
    UCHAR   ucOpCode;              /* ������ */
    UCHAR   ucFlag;                /*��־�ض�*/
    UCHAR   ucTLVOffset;           /*��һ��TLV�ڱ����е�ƫ��*/
    ULONG   ulSequence;            /*���ĵ����к�*/
    OAM_1AG_DATATLV_S  stdatatlv;  /*����TLV����*/
}OAM_1AG_STDLBPACKET_S;


/*��ͨLB���ĸ�ʽ*/
typedef struct tagOAM_1AG_VRPLBPACKET
{
#if VRP_LITTLE_ENDIAN == VRP_YES
    UCHAR   ucVersion    :5;    /* 1AG�汾 */  
    UCHAR   ucLevel      :3;    /* MD���� */
#else
    UCHAR   ucLevel      :3;    /* MD���� */
    UCHAR   ucVersion    :5;    /* 1AG�汾 */
#endif    
    UCHAR   ucOpCode;           /* ������ */
    UCHAR   ucFlag;             /*��־�ض�*/
    UCHAR   ucTLVOffset;        /*��һ��TLV�ڱ����е�ƫ��*/
    ULONG   ulSequence;         /*���ĵ����к�*/
    USHORT  usvsiIndex;
    UCHAR   ucFromPwlag;
    UCHAR   ucReserve[3];       /*����*/
    OAM_1AG_VRPDATATLV_S    stSendLBMTLV;
    OAM_1AG_VRPDATATLV_S    stRecvLBMTLV;
    OAM_1AG_VRPDATATLV_S    stSendLBRTLV;
    OAM_1AG_VRPDATATLV_S    stRecvLBRTLV;
    UCHAR   ucEndTLV;           /*End TLV*/
}OAM_1AG_VRPLBPACKET_S;

#if (VOS_ARM == VOS_HARDWARE_PLATFORM)
#pragma pack(0)
#else
#pragma pack()
#endif


/*LBR��������еĽڵ����ݽṹ����*/
typedef struct tagLbrQUE_Node
{
    DLL_NODE_S node;         /*����ڵ�*/    
    ULONG   ulLbrRecvtime;   /*����LBR����ʱ��*/
    MBUF_S  *pstLbrpacket;   /*LBR����*/
    ULONG   ulLbrSequence;   /*LBR�������*/
}LBRQUE_NODE_S;

/*LB ������̴���LB���Թ��̵Ĳ��Բ������緢�ͱ��ĸ���*/
typedef struct tagMacPingParam
{
    UCHAR   ucDestMacAddr[OAM_1AG_MACADDR_LEN];     /*Ŀ���ַ*/
    UCHAR   ucSrcMacAddr[OAM_1AG_MACADDR_LEN];      /* Դ��ַ */
    ULONG   ulIfIndex;                              /*���ӿ�*/
    ULONG   ulPackets;                              /*���ʹ���*/
    ULONG   ulPacketSize;                           /*���Ĵ�С����������̫ͷ*/
    ULONG   ulTimeout;                              /*��ʱʱ��*/
    ULONG   ulPeriod;                               /*���ͼ��*/
    ULONG   ulMaIndex;                              /*MA����*/
    ULONG   ulLocalMepIndex;                        /* ����ά��������*/
    USHORT  usRmepId;                               /* RMEP ID */
    UCHAR   ucVlanPri;                              /* ����1AG Ping���ĵ�VLAN���ȼ�,ȡֵ��Χ[0,7]�Լ�0xFF.
                                                       0xFF��ʾ����Э��ջĬ�Ϲ�����дVLAN���ȼ�,�����MA������VLAN���ȼ�
                                                       ��ʹ�ø�MA��VLAN���ȼ�,����ʹ��ȫ��VLAN���ȼ�. */
    UCHAR   ucReserve;                              /* pad */
    /*--------------------------------------------------------------------*\
    |*   ͳ������Ϣ                                                       *|
    \*--------------------------------------------------------------------*/
    ULONG     ulTransmitted;                       /*�ѷ��ʹ���*/
    ULONG     ulReceived;                          /*�ѽ��մ���*/
    ULONG     ulTmin;                              /*��С����ʱ��*/
    ULONG     ulTmax;                              /*�������ʱ��*/
    ULONG     ulTsum;                              /*�ܵ�����ʱ��*/
}MACPINGPARAM_S;

/* LB ������� */
typedef struct tagOAM_1AG_LBSEQ_NODE
{
    DLL_NODE_S    node;           /* ����ڵ� */
    ULONG       ulSequence;       /* ��� */
}OAM_1AG_LBSEQ_NODE_S;

/* NP��Ϣ */
typedef struct tagOAM_1AG_NPNOTIFYPARA
{
    ULONG ulIfIndex;                            /*�ӿ�����*/
    UCHAR szMdName[OAM_1AG_MAX_MDNAME_LEN + 1]; /*MD����*/
    UCHAR szMaName[OAM_1AG_MAX_MANAME_LEN + 1]; /*MA����*/
    USHORT usRmepId;                             /*MEPIDֵ*/
    UCHAR ucRes[2];
    ULONG ulType;                               /*�澯����*/
}OAM_1AG_NPNOTIFYPARA_S;

/*---------------------------------------------------------------------------------
--------------------------------�ṹ�����Ͷ���End---------------------------------*/
/*-------------------------------ö�����Ͷ���Begin------------------------------
---------------------------------------------------------------------------------*/
enum eOAM1AGTYPE
{
    OAM1AG_CCM = 1,/*ccm����*/
    OAM1AG_LBR = 2,/*LBR����*/
    OAM1AG_LBM = 3,/*LBM����*/
    OAM1AG_LTR = 4,/*LTR����*/
    OAM1AG_LTM = 5, /*LTM����*/
    OAM1AG_AIS =  33  /*AIS����*/
};

/* Ŀ��physical��ַ������ */
enum e1AGMacAddrtype
{
    OAM_1AG_MULTICAST,
    OAM_1AG_UNICAST,
    OAM_1AG_ZERO,
    OAM_1AG_NULLPARA,
    OAM_1AG_BROADCAST
};

/* VISP֧�ֵ�����ģʽ */
enum e1AGNpMode
{
    OAM_1AG_NONP,   /*���ģʽ*/
    OAM_1AG_HALFNP, /*��NPģʽ*/
    OAM_1AG_FULLNP, /*ȫNPģʽ*/
};

/* MD���ָ�ʽ */
enum eMDNAMETYPE
{
    OAM_1AG_MDNAMETYPE_NO_MD_NAME_PRESENT = 1,      /* No Maintenance Domain Name present */
    OAM_1AG_MDNAMETYPE_STRING = 2,                  /* Domain Name based string */
    OAM_1AG_MDNAMETYPE_MACADDR_ADD_2BYTEINT = 3,    /* physical address + 2-octet integer */
    OAM_1AG_MDNAMETYPE_CHARACTER_STRING = 4,        /* Character string ,ĿǰMD����ֻ֧�����ָ�ʽ*/
    OAM_1AG_MDNAMETYPE_MAX
};

/* MA���ָ�ʽ */
enum eMANAMETYPE
{
    OAM_1AG_MANAMETYPE_PRIMARY_VID = 1,         /* Primary VID */
    OAM_1AG_MANAMETYPE_CHARACTER_STRING = 2,    /* Character string,ĿǰMA����ֻ֧�����ָ�ʽ */
    OAM_1AG_MANAMETYPE_2OCTET_INTEGER = 3,      /* 2-octet integer */
    OAM_1AG_MANAMETYPE_RFC2685_VPN_ID = 4,      /* RFC 2685 VPN ID */
    OAM_1AG_MANAMETYPE_MAX
};

/* Mep��ʱ����CCMֵ */
enum eMEPOUTTIME
{
    /*OAM_1AG_CCINTERVAL_100ms��ͨ��(ulInterval / 20)����õ�.��ΪMEP��20ms����һ�Σ�����Ҫ����20*/
    /*OAM_1AG_CCINTERVAL_1s��ͨ��(ulInterval / 20) / 10 ����õ�.��ΪMEP��10�βŵݼ�������Ҫ����10*/
    /*OAM_1AG_CCINTERVAL_10s���ϵ�ͨ��(ulInterval / 20) / 100 ����õ�.��ΪMEP��100�βŵݼ�������Ҫ����100*/
    OAM_1AG_10SSNDTIMEOUT   = 5, 
    OAM_1AG_1MINSNDTIMEOUT  = 30,
    OAM_1AG_10MINSNDTIMEOUT = 300
};

/*Rmep��ʱ���ֵ*/
enum eRMEPOUTTIME
{
    /* OAM_1AG_CCINTERVAL_3ms��OAM_1AG_CCINTERVAL_10ms�ļ����VISP��֧��RMEP̽��,������ǰû�д��������ּ���ĳ�ʱʱ��
       ����ֵ,��һֱΪ0��������NPģʽ��VISP�ǻ�ά��������̽������RMEP��ģ����Ծͻ����RMEP��ʾ��Ϣ��׼�������ּ����
       RMEP�������Ƿ�ʱ����ʾΪ��ʱ.��ȫNPģʽ��VISP�ǲ�������RMEP��ⶨʱ����,����Ϊ��ȫNPģʽ��Ҳ����ȷ��ʾ,��������
       �����RMEP�ĳ�ʱ����ֵ�趨Ϊһ����0ֵ1.*/
    OAM_1AG_3MS_10MSTIMEOUT = 1,
    /*OAM_1AG_CCINTERVAL_100ms��ͨ��(ulInterval / 50) * 3.5 ����õ�*/
    /*OAM_1AG_CCINTERVAL_1s��ͨ��((ulInterval / 50) / 10) * 3.5 ����õ�.*/
    /*OAM_1AG_CCINTERVAL_10s���ϵ�ͨ��((ulInterval / 50) / 100) * 3.5 ����õ�.*/
    OAM_1AG_10STIMEOUT   = 7,
    OAM_1AG_1MINTIMEOUT  = 42,
    OAM_1AG_10MINTIMEOUT = 420
};

/* Mep��ʱ����CCMֵ */
enum eAISOUTTIME
{
    /* ��ʱ������Ϊ500ms */
    OAM_Y1731_1STIMEOUT   = 7, 
    OAM_Y1731_1MINTIMEOUT  = 42
};

/* TLV ���� */
enum e1AGTLVType
{
    OAM_1AG_END_TLV                     = 0,    /* End TLV */
    OAM_1AG_SENDER_ID_TLV               = 1,    /* Sender ID TLV */
    OAM_1AG_PORT_STATUS_TLV             = 2,    /* Port Status TLV */
    OAM_1AG_INTERFACE_STATUS_TLV_DRAFT7 = 3,    /* Interface Status TLV */
    OAM_1AG_DATA_TLV_DRAFT7             = 4,    /* Data TLV */
    OAM_1AG_REPLY_INGRESS_TLV           = 5,    /* Reply Ingress TLV */
    OAM_1AG_REPLY_EGRESS_TLV            = 6,    /* Reply Egress TLV */    
    OAM_1AG_ORGANIZATION_SPECIFIC_TLV   = 31    /* Organization-Specific TLV */
};

/* ��׼Э��TLV ���� */
enum e1AGTLVSTDType
{    
    OAM_1AG_DATA_TLV_STD                = 3,    /* Data TLV */
    OAM_1AG_INTERFACE_STATUS_TLV_STD    = 4,    /* Interface Status TLV */
    OAM_1AG_LTM_EGRESS_TLV              = 7,    /* Reply Egress TLV */
    OAM_1AG_LTR_EGRESS_TLV              = 8,    /* Reply Egress TLV */
};


/* Ingress TLV ACTION */
enum eOAM1AG_INGRESS_TLV_ACTION
{
    OAM_1AG_INGRESS_OK = 1,     /* The target data frame would be passed through to the MAC Relay
                                    Entity. */
    OAM_1AG_INGRESS_DOWN = 2,   /* The Bridge Port��s MAC_Operational parameter is false. */
    OAM_1AG_INGRESS_BLOCKED = 3,/* The target data frame would not be forwarded if received on this
                                    Port due to active topology enforcement */
    OAM_1AG_INGRESS_VID = 4,    /* The ingress port is not in the member set of the LTM��s VID, and
                                    ingress filtering is enabled, so the target data frame would be filtered
                                    by ingress filtering */
    OAM_1AG_INGRESS_MAX
};

/* Egress TLV ACTION */
enum eOAM1AG_EGRESS_TLV_ACTION
{
    OAM_1AG_EGRESS_OK = 1,      /* The targeted data frame would be forwarded. */
    OAM_1AG_EGRESS_DOWN = 2,    /* The Egress Port can be identified, but that
                                    Bridge Port��s MAC_Operational parameter is false. */
    OAM_1AG_EGRESS_BLOCKED = 3, /* The Egress Port can be identified, but the data
                                    frame would not pass through the Egress Port
                                    due to active topology management (8.6.1), i.e.
                                    the Bridge Port is not in the Forwarding state. */
    OAM_1AG_EGRESS_VID = 4,     /* The Egress Port can be identified, but the
                                    Bridge Port is not in the LTM��s VID��s member
                                    set, so would be filtered by egress filtering */
    OAM_1AG_EGRESS_MAX
};

/* LTR Reply Action */
enum eOAM1AG_LTR_REPLY_ACTION
{
    OAM_1AG_RLY_HIT = 1,    /* The LTM reached an MP whose physical address matches the target physical address. */
    OAM_1AG_RLY_FDB = 2,    /* The Egress Port was determined by consulting the Filtering Database */
    OAM_1AG_RLY_MPDB = 3,   /* The Egress Port was determined by consulting the MIP CCM Database */
    OAM_1AG_RLY_MAX
};


/*-------------------------------ö�����Ͷ���end------------------------------
---------------------------------------------------------------------------------*/
#ifdef __cplusplus
    }
#endif  /* end of __cplusplus */

#endif

