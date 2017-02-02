/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              3ah_type.h
*
*  Project Code: VISPV100R007
*   Module Name: ETH OAM 3AH  
*  Date Created: 2008-2-28
*        Author: LY(57500)
*   Description: 3AHģ�����ݽṹ����
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*-------------------------------------------------------------------------------
*  2008-2-28  LY(57500)     Create the first version.
*
*******************************************************************************/
#ifndef _3AH_TYPE_H_
#define _3AH_TYPE_H_

#ifdef __cplusplus
extern "C"{
#endif

/* ���ر������·�¼����� */
typedef struct tagLinkEventInfo
{
    ULONG ulEventType;          /* �¼�����             */
    ULONG ulEventStamp;         /* ��¼�����¼���ʱ��� */

    DULONG_S stDulErrWindows;
    DULONG_S stDulErrThreshold;
    DULONG_S stDulErrValue;
    DULONG_S stDulErrRunTotal;

    ULONG ulEventRunTotal;      /* OAM��λ����������·�¼����� */    
}OAM3AH_LINKEVENT_INFO_S;

/* ��·�¼��������ݽṹ */
typedef struct tagLinkEvent
{
    ULONG ulEventEnable;        /* �¼���ʹ�ܱ�־λ                                 */
    ULONG ulEventTimerId;       /* ��·�¼���ʱ��ID,��ǰֻ�д�֡�¼�/��֡���¼�ʹ�� */
    ULONG ulCount;              /* Ŀǰ����֡��������¼��ǰ����                     */

    VOID (*pfTimerFunc)(ULONG ulIfIndex);   /* ��ʱ���ص�����ָ��,��ǰֻ�д�֡�¼�/��֡���¼�ʹ��   */
    DULONG_S stDulErrCnt;       /* �洢�ӵײ��ȡ�Ĵ�֡��,��ǰֻ�д�֡�¼�/��֡���¼�ʹ��           */
    DULONG_S stdulEventWindow;        /* �洢�û����õĴ���ֵ;�����¼��Ĵ�����Ҫ����ת��,�ʲ���ֱ�ӱ��浽stLinkEventInfo��  */
    /* �û����õ���·�¼����޲���ֱ�ӱ����������stLinkEventInfo��,������� */
    
    OAM3AH_LINKEVENT_INFO_S stLinkEventInfo;
}OAM3AH_LINKEVENT_S;

/* ����TLV���ݽṹ,����ǿ��һ�ֽڶ��� */
#pragma pack(1)

/* 3AH OAMPDU HEAD -- 15�ֽ� */
typedef struct tagOamPduHead
{
    UCHAR   ucDstMacAddr[MACADDRLEN];   /* ��Э��ಥMAC: 01-80-C2-00-00-02 */
    UCHAR   ucSrcMacAddr[MACADDRLEN];   /* ԴMAC                            */

    USHORT  usType;                     /* ��Э������: 8809                 */

    UCHAR   ucSubType;                  /* OAMPDU������                     */
}OAMPDU_HEAD_S;

/* ��VLANͷ��3AH���� */
typedef  struct  tagOamVlanPduHead
{
    UCHAR   ucDstMacAddr[MACADDRLEN];   /* ��Э��ಥMAC: 01-80-C2-00-00-02 */
    UCHAR   ucSrcMacAddr[MACADDRLEN];   /* ԴMAC                            */
    USHORT  usTPID ;                    /* 802.1q Protype 8100 */
    USHORT  usTCI ;                     /*user User_priority CFI VLANID */
    USHORT  usType;                     /* ��Э������: 8809                 */
    UCHAR   ucSubType;                  /* OAMPDU������                     */
}OAMPDU_VLAN_HEAD_S;


/* ������������¼�TLV���� */
typedef struct tagOam3ahEventSymPrd
{
    UCHAR       ucEventType;                /* �¼�����,0x01                    */
    UCHAR       ucEventLen;                 /* �¼�����,0x28                    */
    USHORT      usEventStamp;               /* ��¼�¼�������ʱ���,��λ100ms   */

    DULONG_S    stDulErrWindows;            /* �¼�����                         */
    DULONG_S    stDulErrThreshold;          /* �¼�����                         */
    DULONG_S    stDulErrSymbols;            /* �����ڴ��������                 */
    DULONG_S    stDulErrRunTotal;           /* OAM��λ������������            */

    ULONG       ulEventRunTotal;            /* OAM��λ��������TLV�¼�����     */
}OAM3AH_EVENT_SYMPRD_S;

/* ��֡�¼�TLV */
typedef struct tagOam3ahEventFrame
{
    UCHAR       ucEventType;                /* �¼�����,0x02                    */
    UCHAR       ucEventLen;                 /* �¼�����,0x1A                    */
    USHORT      usEventStamp;               /* ��¼�¼�������ʱ���,��λ100ms   */

    USHORT      usErrWindows;               /* �¼�����                         */
    ULONG       ulErrThreshold;             /* �¼�����                         */
    ULONG       ulErrFrames;                /* �����ڴ�֡��                     */
    DULONG_S    stDulErrRunTotal;           /* OAM��λ���֡����                */

    ULONG       ulEventRunTotal;            /* OAM��λ��������TLV�¼�����     */
}OAM3AH_EVENT_FRAME_S;

/* ��֡�����¼�TLV���� */
typedef struct tagOam3ahEventFrmPrd
{
    UCHAR       ucEventType;                /* �¼�����,0x03                    */
    UCHAR       ucEventLen;                 /* �¼�����,0x1C                    */
    USHORT      usEventStamp;               /* ��¼�¼�������ʱ���,��λ100ms   */

    ULONG       ulErrWindows;               /* �¼�����                         */
    ULONG       ulErrThreshold;             /* �¼�����                         */
    ULONG       ulErrFrames;                /* �����ڴ�֡��                     */
    DULONG_S    stDulErrRunTotal;           /* OAM��λ��֡����                  */

    ULONG       ulEventRunTotal;            /* OAM��λ��������TLV�¼�����     */
}OAM3AH_EVENT_FRMPRD_S;

/* ��֡���¼�TLV���� */
typedef struct tagOam3ahEventFrmSecSum
{
    UCHAR       ucEventType;                /* �¼�����,0x04                    */
    UCHAR       ucEventLen;                 /* �¼�����,0x12                    */
    USHORT      usEventStamp;               /* ��¼�¼�������ʱ���,��λ100ms   */

    USHORT      usErrWindows;               /* �¼�����                         */
    USHORT      usErrThreshold;             /* �¼�����                         */
    USHORT      usErrSecSum;                /* �����ڴ�֡����                   */
    ULONG       ulErrRunTotal;              /* OAM��λ�ܴ�֡����                */

    ULONG       ulEventRunTotal;            /* OAM��λ��������TLV�¼�����     */
}OAM3AH_EVENT_FRMSECSUM_S;

#if (VOS_ARM == VOS_HARDWARE_PLATFORM)
#pragma pack(0)
#else
#pragma pack()
#endif


/* 3AH OAMPDU flags�ֶζ��� */
typedef union unOamPduFlags_U
{
    struct tagOamPduFlags
    {
#if (VRP_BIG_ENDIAN == VRP_YES)
        USHORT  usReserved:9;       /* 15:7 Reserved                            */
        USHORT  usRmtDscvrStatus:2; /* 6:5  Remote Stable & Remote Evaluating   */
        USHORT  uslclDscvrStatus:2; /* 4:3  Local Stable & Local Evaluating    */
        USHORT  usCriticalEvent:1;  /* 2    Critical Event                      */
        USHORT  usDyingGasp:1;      /* 1    unrecoverable condition             */
        USHORT  usLinkFalut:1;      /* 0    PHY detect Link Fault               */
#else
        USHORT  usLinkFalut:1;      /* 0    PHY detect Link Fault               */
        USHORT  usDyingGasp:1;      /* 1    unrecoverable condition             */
        USHORT  usCriticalEvent:1;  /* 2    Critical Event                      */
        USHORT  uslclDscvrStatus:2; /* 4:3  Local Stable & Local Evaluating    */
        USHORT  usRmtDscvrStatus:2; /* 6:5  Remote Stable & Remote Evaluating   */
        USHORT  usReserved:9;       /* 15:7 Reserved                            */
#endif
    }s;
    
    USHORT  usFlags;
}OAMPDU_FLAGS_U;

/* 3AH OAMPDU configuration�ֶζ���   */
typedef union tagOamPduConfig_U
{
    struct tagOamPduConfig
    {
#if (VRP_BIG_ENDIAN == VRP_YES)        
        UCHAR ucDetectInterval:3;   /* Э�鱣��,��չ������ʶ̽������                    */
        UCHAR ucVarRetrieval:1;     /* Variable Retrieval: 1=Support;0=Not Support      */
        UCHAR ucLinkEvent:1;        /* Link Events: 1=Support;0=Not Support             */
        UCHAR ucOamLbSupport:1;     /* Remote Loopback Support: 1=Support;0=Not Support */
        UCHAR ucUniSupport:1;       /* Unidirectional Support: 1=Support;,0=Not Support */
        UCHAR ucOamMode:1;          /* ����OAM Mode: 1=Active;0=Passive                 */
#else
        UCHAR ucOamMode:1;          /* ����OAM Mode: 1=Active;0=Passive                 */
        UCHAR ucUniSupport:1;       /* Unidirectional Support: 1=Support;,0=Not Support */
        UCHAR ucOamLbSupport:1;     /* Remote Loopback Support: 1=Support;0=Not Support */
        UCHAR ucLinkEvent:1;        /* Link Events: 1=Support;0=Not Support             */
        UCHAR ucVarRetrieval:1;     /* Variable Retrieval: 1=Support;0=Not Support      */
        UCHAR ucDetectInterval:3;   /* Э�鱣��,��չ������ʶ̽������                    */
#endif
    }s;

    UCHAR ucConfig;
}OAMPDU_CONFIG_U;

/* 3AH OAMPDU state �ֶζ��� */
typedef union tagOamPduState_U
{
    struct tagOamPduState
    {
#if (VRP_BIG_ENDIAN == VRP_YES)        
        UCHAR ucRsv:5;          /* 7:3 Reserved                 */
        UCHAR ucMuxAction:1;    /* 2   Multiplexer Action       */
        UCHAR ucParserAction:2; /* 1:0 Parser Action            */
#else
        UCHAR ucParserAction:2; /* 1:0 Parser Action            */
        UCHAR ucMuxAction:1;    /* 2   Multiplexer Action       */
        UCHAR ucRsv:5;          /* 7:3 Reserved                 */
#endif
    }s;

    UCHAR ucState;
}OAMPDU_STATE_U;

#pragma pack(1)
/* OAMPDU IFNO TLV�ṹ���� */
typedef struct tagOamPduInfoTlv
{
    UCHAR   ucInfoType;                 /* ��Ϣ����                         */
    UCHAR   ucInfoLen;                  /* ��Ϣ����,0x10                    */
    UCHAR   ucOamVersion;               /* OAM�汾��                        */
    USHORT  usRevision;                 /* Info TLV�޶��汾��               */
    OAMPDU_STATE_U  unState;            /* OAM״̬��Ϣ                      */
    OAMPDU_CONFIG_U unOamCfg;           /* OAM������Ϣ                      */
    USHORT  usOamPduCfg;                /* OAMPDU������Ϣ:���OAMPDU�ߴ�    */
    UCHAR   aucOUI[OAMPDU_OUI_LENGTH];  /* ����Ψһ��ʶ                     */
    ULONG   ulVendorInfo;               /* ���������̲�Ʒ�ı�ʶ,δʹ��    */
}OAMPDU_INFO_TLV_S;

/* Organization Specific Information Tlv */
typedef struct tagOamPduOrgSpecTlv
{
    UCHAR ucInfoType; /* ��Ϣ����: 0xFE OAM3AH_ORG_SPEC_INFORMATION */
    UCHAR ucInfoLen;  /* ��Ϣ���� */
    UCHAR aucOUI[OAMPDU_OUI_LENGTH]; /* ����Ψһ��ʶ */
    UCHAR ucBoardType; /* ��ǰ������ǰ�������/����״̬: 0xAB��ʶ���ð�;0xBA��ʾ���ð� */
}OAMPDU_ORGSPEC_TLV_S;

#if (VOS_ARM == VOS_HARDWARE_PLATFORM)
#pragma pack(0)
#else
#pragma pack()
#endif

typedef struct tagOamPduOrgSpecInfo
{
    ULONG ulLclBoardState; /* ����������״̬;0-����Զ�ͨ��;1-��Զ�ͨ�汾�����ð�״̬;2-��Զ�ͨ�汾�˱��ð�״̬ */
    OAMPDU_ORGSPEC_TLV_S stLclOrgSpecTlv;
    OAMPDU_ORGSPEC_TLV_S stRmtOrgSpecTlv;
}OAM3AH_ORGSPEC_INFO_S;

/* 3AH���ƿ� */
typedef struct tagOam3ahPortInfo
{
    DLL_NODE_S  stNode;             /* ���ڹ���˫������             */

    ULONG   ulIfIndex;              /* �ӿ�����                     */
    ULONG   ul3ahEnable;            /* �ӿ�ʹ�ܱ��                 */
    ULONG   ulDetectIntervar;       /* ̽������,msΪ��λ            */
    ULONG   ulFsmState;             /* �ӿ�3AH״̬��״̬            */
    USHORT  usDscvrProcessStatue;   /* ���ػ�Զ˷����Ƿ����       */
    UCHAR   aucPeerMacAddr[MACADDRLEN];  /* �Զ�physical��ַ              */
    USHORT  usLbTestMode;           /* ���ز���ģʽ,0=VISP�������ģʽ;1=NP���ز���ģʽ */

    OAMPDU_FLAGS_U unFlags;         /* OAMPDU flag�ֶ�              */
    OAMPDU_INFO_TLV_S stLclInfoTlv; /* ����INFO TLV������Ϣ         */
    OAMPDU_INFO_TLV_S stRmtInfoTlv; /* �Զ�INFO TLV������Ϣ         */
    ULONG   ulPduCnt;               /* ÿ����෢��OAMPDU����,��ʼֵΪ10    */

    ULONG   ulPduTimerId;           /* ���ڷ��Ͷ�ʱ��ID             */
    ULONG   ulLostLinkTimerId;      /* �Զ���·��ʧ̽�ⶨʱ��ID     */
    
    /* ������� */
    ULONG   ulLbTimerId;            /* ���س�ʱ��ʱ��ID             */    
    ULONG   ulLbCtrlPduRetryTimes;  /* ���ؿ��Ʊ������Դ���         */
    
    /* �¼����Ϲ�������ֶ� */
    ULONG   ulFaultEnable;          /* ����ͨ��ʹ��״̬,�ӵ�0λ����2λ�ֱ��ʾ��·����/��������/�����¼� */
    ULONG   ulLclFault;             /* ���ع��ϱ�ʶ,ͬ��˵��        */
    ULONG   ulRmtFault;             /* �Զ˹��ϱ�ʶ,ͬ��˵��        */
    
    USHORT  usLclSeqNum;            /* ������·�¼����к�           */
    USHORT  usRmtSeqNum;            /* �Զ���·�¼����к�           */
    
    /* 0: Errored Symbol Period Event           */
    /* 1: Errored Frame Event                   */
    /* 2: Errored Frame Period Event            */
    /* 3: Errored Frame Seconds Summary Event   */
    OAM3AH_LINKEVENT_S stLinkEvent[OAM3AH_LINKEVENT_NUM];

    OAM3AH_PDUSTAT_S stStatistic;  /* 3AH OAMPDU ͳ����Ϣ          */
    ULONG   ulDebugSwitch;         /* 3ah���Կ���                  */

    OAM3AH_ORGSPEC_INFO_S stOrgSpecInfo;  
    ULONG   ulHasNpUpdate;         /* ��¼�Ƿ��Ѿ�������np�Ự�·� */  
    ULONG   ulNegTimeCnt;          /* �״�Э�̲�������澯��ʱ */    
}OAM3AH_PORTINFO_S;


#define     DLLOAM3AHPORTINFO(x)      ((OAM3AH_PORTINFO_S *)(x)) 


/* ״̬��Ǩ�Ƶ����ݽṹ���� */
typedef struct tagOam3ahFsmTran
{
    ULONG ulStartState;        /* ��ʼ״̬,ö��ֵ,�μ���ض��� */
    ULONG ulTranCondition;     /* �����¼�,ö��ֵ,�μ���ض��� */
    ULONG ulEndState;          /* ��ֹ״̬,ö��ֵ,�μ���ض��� */
}OAM3AH_FSMTRAN_S;

/* Shell��Coreע��Ļص������� */
typedef struct tagOam3ahShellCallbackSet
{
    /* ������Ϣ������� */
    VOID (*pfOAM_3AH_DebugOutString) (CHAR * szStr);
}OAM3AH_SHELL_CALLBACK_SET_S;

/* �ײ�֪ͨ�����¼������ṹ */
typedef struct tagOam3ahLinkEvtParam
{
    DULONG_S    stdulWindows;
    DULONG_S    stdulThreshold;
    DULONG_S    stdulErrorNum;
    DULONG_S    stdulErrRunTotal;
}OAM3AH_LINKEVT_PARAM_S;

#ifdef __cplusplus
}
#endif      /* end of __cplusplus   */

#endif      /* end of _3AH_TYPE_H_  */

