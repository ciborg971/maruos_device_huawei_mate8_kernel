

#ifndef _BFD_HA_H_
#define _BFD_HA_H_

#ifdef  __cplusplus
extern  "C"{
#endif

/* BFD HA������Ϣ���� */
/* ע��: ��������˱������ͣ�����Ҫͬ���޸� pszBfdBakTypeStr�ַ���  */
typedef enum tagBFD_HA_MSG_TYPE
{
    BFD_MSGTYPE_UNKNOW,            /* 0  ����ı�����Ϣ���� */
    BFD_SESSION_UP_BAK,            /* 1  �ỰUP���ݿ� */
    BFD_SESSION_CREATE_BAK,        /* 2  �û������Ự���ƿ�*/
    BFD_SESSION_DEL_BAK,           /* 3  �û�����ɾ���Ự���ƿ�*/
    BFD_SESSION_CFG_UPDATE_BAK,    /* 4  �û����ø��»Ự���� */
    BFD_SESSION_BATCH_BAK,         /* 5  �������ݻỰ�� */

    BFD_SESSION_DIG_DOWN_BAK,      /* 6  �û����ƻỰdown */
    BFD_SET_FUNC_ENABLE_BAK,       /* 7  ����ʹ��BFD���� */
    BFD_SESSION_SET_WTR_TIME_BAK,  /* 8  ���ûỰdown�Ժ��ط�����ʱ��*/
    BFD_SESSION_SET_APPS_FLAG,     /* 9  ����Ӧ����*/

    BFD_SESSION_SET_SING_APPS_BAK, /* 10 ���õ���Ӧ����*/
    BFD_SESSION_DEL_SING_APPS_BAK, /* 11 ɾ������Ӧ����*/
    BFD_REC_ASY_PACKET_BAK,        /* 12 ������(�첽ģʽ)�Ự�����ı��� */
    BFD_REC_DEMAND_BAK,            /* 13 ������(��ѯģʽ)�Ự�����ı��� */
    BFD_UNDO_SHUTDOWN_BAK,         /* 14 �û����ƻỰundo shutdown */

    BFD_ADAPT_MULTIHOP_PORT,       /* 15 ȫ�ֿ��ر���: �Ƿ���������Ự�Զ�����UDPĿ�Ķ˿ں� */
    BFD_NEW_MULTIHOP_PORT,         /* 16 ���ݶ����Ự�ı���Ŀ�Ķ˿ں� */
    
    BFD_SESSION_BAK_TOS,           /* 17 ����bfd�Ựtosֵ */
    BFD_CREATE_VRF_SESSION_BAK,    /* 18 ��ʵ�����û�����BFD�Ự */
    BFD_DELETE_VRF_SESSION_BAK,    /* 19 ��ʵ�����û�ɾ��BFD�Ự */
    BFD_UPDATE_VRF_SESSION_CFG_BAK,/* 20 �û����ø��»Ự���� */
    BFD_DIG_DOWN_VRF_SESSION_BAK,  /* 21 �û����ƻỰdown */
    BFD_SETAPPS_VRF_SESSION_FLAG,  /* 22 ����Ӧ���� */
    BFD_SETSINGAPPS_VRF_SESSION_BAK, /* 23 ���õ���Ӧ���� */
    BFD_DELSINGAPPS_VRF_SESSION_BAK, /* 24 ɾ������Ӧ���� */
    BFD_VRF_REC_ASY_PACKET_BAK,      /* 25 ������(�첽ģʽ)�Ự�����ı��� */
    BFD_VRF_REC_DEMAND_BAK,          /* 26 ������(��ѯģʽ)�Ự�����ı��� */
    BFD_VRF_UNDO_SHUTDOWN_BAK,       /* 27 �û����ƻỰundo shutdown */
    BFD_VRF_NEW_MULTIHOP_PORT_BAK,   /* 28 ���ݶ����Ự�ı���Ŀ�Ķ˿ں� */
    BFD_SESSION_NAME_BAK,            /* 29 ����BFD���� */
    BFD_SESSION_DESC_BAK,            /* 30 ����BFD���� */
    BFD_SESSION_BFDPROTOCOL_BAK,     /* 31 ���ݴ���BFD�Ự��Э������ */
    BFD_SESSION_REMOTEMRI_BAK,       /* 32 ���ݶԶ�RequiredMinRxIntervalֵ */  
    BFD_SESSION_REMOTE_DEMANDMODE_BAK,       /* 32 ���ݶԶ�DemandModeֵ */  

    BFD_MSGTYPE_MAX,               /*  ������������ [ע��]: ��������˱������ͣ�����Ҫͬ���޸� pszBfdBakTypeStr�ַ��� */
} BFD_HA_MSG_TYPE;

/* Begin of HA UPGRADE modification, 2010 December to 2011 January */
/* ����Ϣ��VISPV1R6C02��VISPV1R6C05�汾����, ��Ҫ�����������⴦�� */
#define BFD_CREATE_VPN_SESSION_BAK  17

typedef struct tagBFD_CREATE_VPN_SESSION_BAK
{
    USHORT  usType;                /* ������Ϣ������ */
    USHORT  usLen;                 /* ������Ϣ����ܳ��� */
    ULONG   ulSessId;              /* �ỰID */
    ULONG   ulDstIP;               /* Ŀ�ĵ�ַ(������) */
    ULONG   ulSrcIP;               /* Դ��ַ(������) */
    ULONG   ulOutIfIndex;          /* ���ӿ� */
    ULONG   ulVrfIndex;            /* �Ự������VPN*/
}BFD_CREATE_VPN_SESSION_BAK_S;
/* End of HA UPGRADE modification, 2010 December to 2011 January */

typedef struct tagBFD_PACKET_HEAD_BAK
{
    USHORT usType;           /* ������Ϣ������ */
    USHORT usLen;            /* ������Ϣ����ܳ��� */
    ULONG ulSessionID;       /* ���ÿ������ĻỰ���� */
    ULONG ulExtend;          /* ��չ�ֶ� */
} BFD_PACKET_HEAD_BAK_S;

/* BFD����ǿ�Ʋ������ݽṹ */
typedef struct tagBFD_PACKET_BAK
{
#if ( VRP_BIG_ENDIAN == VRP_YES )
    UCHAR   bVers                   : 3 ;       /* BFD�İ汾��Ϣ */
    UCHAR   bDiagnostic             : 5 ;       /* BFD�������Ϣ */
#else
    UCHAR   bDiagnostic             : 5 ;       /* BFD�������Ϣ */
    UCHAR   bVers                   : 3 ;       /* BFD�İ汾��Ϣ */
#endif
#if ( VRP_BIG_ENDIAN == VRP_YES )
    UCHAR   bState                  : 2 ;       /* BFD��״̬��Ϣ */
    UCHAR   bPollFlag               : 1 ;       /* BFD����ѯ��־ */
    UCHAR   bFinalFlag              : 1 ;       /* BFD����ѯ��Ӧ��־ */
    UCHAR   bControlPlanFlag        : 1 ;       /* BFD�Ϳ���ƽ�湲��ı�־ */
    UCHAR   bAuthenticationFlag     : 1 ;       /* BFD����֤��־ */
    UCHAR   bDemandModeFlag         : 1 ;       /* BFD�Ĳ�ѯ��ʽ��־ */
    UCHAR   bReserved               : 1 ;       /* BFD�ı���λ */ 
#else
    UCHAR   bReserved               : 1 ;       /* BFD�ı���λ */ 
    UCHAR   bDemandModeFlag         : 1 ;       /* BFD�Ĳ�ѯ��ʽ��־ */
    UCHAR   bAuthenticationFlag     : 1 ;       /* BFD����֤��־ */
    UCHAR   bControlPlanFlag        : 1 ;       /* BFD�Ϳ���ƽ�湲��ı�־ */
    UCHAR   bFinalFlag              : 1 ;       /* BFD����ѯ��Ӧ��־ */
    UCHAR   bPollFlag               : 1 ;       /* BFD����ѯ��־ */
    UCHAR   bState                  : 2 ;       /* BFD��״̬��Ϣ */
#endif
    UCHAR   ucDetectMult                ;       /* BFD�ļ�ⱶ�� */ 
    UCHAR   ucPacketLength              ;       /* BFD�ı��ĳ��� */ 
    ULONG   ulLocalDiscriminitor        ;       /* BFD�ı��ر�ʶ�� */
    ULONG   ulRemoteDiscriminitor       ;       /* BFD�ĶԶ˱�ʶ�� */
    ULONG   ulDesiredMinTxInterval      ;       /* BFD�����ķ��ͼ�� */ 
    ULONG   ulRequiredMinRxInterval     ;       /* BFD�ı��ؽ������� */ 
    ULONG   ulRequiredMinEchoRxInterval ;       /* BFD�������ܵķ��ͼ�� */ 
} BFD_PACKET_BAK_S;


typedef struct tagBFD_REC_PACKET_BAK
{
    USHORT usType;           /* ������Ϣ������ */
    USHORT usLen;            /* ������Ϣ����ܳ��� */
    ULONG ulSessionID;       /* ���ÿ������Ľӿ����� */
    BFD_PACKET_BAK_S stPacket;   /* �յ��ı����ֶ� */
} BFD_REC_PACKET_BAK_S;

typedef struct tagBFD_VRF_REC_PACKET_BAK
{
    USHORT usType;           /* ������Ϣ������ */
    USHORT usLen;            /* ������Ϣ����ܳ��� */
    ULONG  ulSessionID;       /* ���ÿ������Ľӿ����� */
    ULONG  ulVrfIndex;
    BFD_PACKET_BAK_S stPacket;   /* �յ��ı����ֶ� */
} BFD_VRF_REC_PACKET_BAK_S;

/* �Ự���²������ݽṹ */
typedef struct tagBFD_SESSION_PARA_BAK
{
    ULONG ulDetectMode;      /* �Ự���ģʽ:1��ѯģʽ;2�첽ģʽ */
    ULONG ulMinTxInterval;   /* ms,��С����ʱ������10~1000ms */
    ULONG ulMinRxInterval;   /* ms,��С����ʱ������10~1000ms */
    ULONG ulDetectMult;      /* ��ⱶ����3~50 */
}BFD_SESSION_PARA_BAK_S;

typedef struct tagBFD_CFG_PACKET_HEAD_BAK
{
    USHORT usType;                    /* ������Ϣ������ */
    USHORT usLen;                     /* ������Ϣ����ܳ��� */
    ULONG ulSessionID;                /* ���ÿ������Ľӿ����� */
    BFD_SESSION_PARA_BAK_S stSessionPara; /* �Ự���� */
} BFD_CFG_PACKET_HEAD_BAK_S;

typedef struct tagBFD_VRF_CFG_PACKET_HEAD_BAK
{
    USHORT usType;                    /* ������Ϣ������ */
    USHORT usLen;                     /* ������Ϣ����ܳ��� */
    ULONG  ulSessionID;               /* ���ÿ������Ľӿ����� */
    ULONG  ulVrfIndex;                /* VRF���� */
    BFD_SESSION_PARA_BAK_S stSessionPara; /* �Ự���� */
} BFD_VRF_CFG_PACKET_HEAD_BAK_S;


/* ����bfd�Ự��tos */
typedef struct tagBFD_SESSION_TOS_BAK
{
    USHORT usType;                    /* ������Ϣ������ */
    USHORT usLen;                     /* ������Ϣ����ܳ��� */
    ULONG  ulSessionID;               /* ���ÿ�������BFD�ỰID */
    UCHAR  ucTos;                     /* bfd�Ựtos */
    UCHAR  Padding[3];
    ULONG  ulVrfIndex;             
}BFD_SESSION_TOS_BAK_S;

/* ����bfd�Ự��Э�����ͣ�1:RFCЭ�� 0:�ݰ�04*/
typedef struct tagBFD_SESSION_BFDPROTOCOL_BAK
{
    USHORT usType;                    /* ������Ϣ������ */
    USHORT usLen;                     /* ������Ϣ����ܳ��� */
    ULONG  ulSessionID;               /* ���ÿ�������BFD�ỰID */
    ULONG  ulVrfIndex;                /* VRF���� */
    ULONG  ulBfdProtocol;             /* bfd�ỰЭ������ */
}BFD_SESSION_BFDPROTOCOL_BAK_S;

/* ����bfd�Ự��Э�����ͣ�1:RFCЭ�� 0:�ݰ�04*/
typedef struct tagBFD_SESSION_REMOTEMRI_BAK
{
    USHORT usType;                    /* ������Ϣ������ */
    USHORT usLen;                     /* ������Ϣ����ܳ��� */
    ULONG  ulSessionID;               /* ���ÿ�������BFD�ỰID */
    ULONG  ulVrfIndex;                /* VRF���� */
    ULONG  ulRemoteMinRxInterval;     /* �Զ˵�RequiredMinRxIntervalֵ */
}BFD_SESSION_REMOTEMRI_BAK_S;

/* ����bfd�Ự�Զ˵�DemandModeֵ*/
typedef struct tagBFD_SESSION_REMOTE_DEMANDMODE_BAK
{
    USHORT usType;                    /* ������Ϣ������ */
    USHORT usLen;                     /* ������Ϣ����ܳ��� */
    ULONG  ulSessionID;               /* ���ÿ�������BFD�ỰID */
    ULONG  ulVrfIndex;                /* VRF���� */
    USHORT usRemoteDemandMode;        /* �Զ˵�DemandModeֵ */
    USHORT usReserved;                /* ���ֽڶ��룬�������� */
}BFD_SESSION_REMOTE_DEMANDMODE_BAK_S;

typedef struct tagBFD_CREATE_SESSION_BAK
{
    USHORT  usType;                /* ������Ϣ������ */
    USHORT  usLen;                 /* ������Ϣ����ܳ��� */
    ULONG   ulSessId;              /* �ỰID */
    ULONG   ulDstIP;               /* Ŀ�ĵ�ַ(������) */
    ULONG   ulSrcIP;               /* Դ��ַ(������) */
    ULONG   ulOutIfIndex;          /* ���ӿ� */
}BFD_CREATE_SESSION_BAK_S;

typedef struct tagBFD_CREATE_VRF_SESSION_BAK
{
    USHORT  usType;                /* ������Ϣ������ */
    USHORT  usLen;                 /* ������Ϣ����ܳ��� */
    ULONG   ulSessId;              /* �ỰID */
    ULONG   pulDstIP[4];               /* Ŀ�ĵ�ַ(������) */
    ULONG   pulSrcIP[4];               /* Դ��ַ(������) */
    ULONG   ulOutIfIndex;          /* ���ӿ� */
    ULONG   ulIpVer;
    ULONG   ulVrfIndex;            /* �Ự������VPN*/
}BFD_CREATE_VRF_SESSION_BAK_S;

typedef struct tagBFD_DELETE_VRF_SESSION_BAK
{
    USHORT  usType;                /* ������Ϣ������ */
    USHORT  usLen;                 /* ������Ϣ����ܳ��� */
    ULONG   ulSessId;              /* �ỰID */
    ULONG   ulVrfIndex;            /* �Ự������VPN*/
}BFD_DELETE_VRF_SESSION_BAK_S;

typedef struct tagBFD_SESSION_CFG_HA_BAK
{
    ULONG   ulBfdType                             ;              /* BFD�󶨵����� */
    ULONG   ulPeerAddrType                        ;              /* BFD�󶨵ĵ�ַ���� */
    ULONG   ulSrcAddr[4]                          ;              /* IPv4��IPv6��ַ,������ */
    ULONG   ulPeerAddr[4]                         ;              /* IPv4��IPv6��ַ,������ */
    ULONG   ulIfIndex                             ;              /* BFDָ���ĳ��ӿ����� */
    ULONG   ulVrfIndex                            ;              /* BFD's Vpn index*/
    ULONG   ulVlanId                              ;              /* BFDָ����VlanId��������̫���ӿ�ʱ�û���ѡ�� */
    BOOL_T  bDemand                               ;
    BOOL_T  bEcho                                 ;
    ULONG   ulDemandTimerInterval                 ;              /* BFD��ѯģʽ�¶�ʱ��ѯ�ļ�� */ 
    ULONG   ulDetectMult                          ;              /* BFD�ı��ؼ�ⱶ�� */ 
    ULONG   ulMinTxInterval                       ;              /* BFD�����ķ��ͼ�� */ 
    ULONG   ulMinRxInterval                       ;              /* BFD�ı��ؽ������� */ 
    ULONG   ulMinEchoTxInterval                   ;              /* BFD�Ự���ػ������ܵĽ�������(��֧��Echo,��ֵ����Ϊ0) */ 
    ULONG   ulMinEchoRxInterval                   ;              /* BFD�������ܵķ��ͼ��(��֧��Echo,��ֵ����Ϊ0)*/ 
    ULONG   ulWtrTimeInterval                     ;              /* Time for wtr. millisecond */
    USHORT  usAuthMode                            ;              /* BFD����֤��ʽ */ 
    UCHAR   ucAuthKeyId                           ;              /* BFD���õ���֤KeyId */ 
    UCHAR   ucAuthPwd[BFD_LEN_MAX_SIMPLE_PWD + 1] ;              /* BFD���õ���֤pwd */
}BFD_SESSION_CFG_HA_BAK_S;

/* �Ựʵ�ʵ�������Ϣ size 13*4�ֽ�*/
typedef struct tagBFD_SESS_RUN_ENTRY_BAK
{
    ULONG   ulLocalDiscr              ;              /* BFD�ı��ر�ʶ�� */
    ULONG   ulRemoteDiscr             ;              /* BFD�ĶԶ˱�ʶ�� */
    USHORT  usUdpSrcPort              ;              /* UDP��Դ�˿ں� */
    USHORT  usUdpDstPort              ;              /* UDP��Ŀ�Ķ˿ں� */
    USHORT  usDetectMode              ;              /* BFD�ļ��ģʽ */
    USHORT  usIsMultiHop              ;              /* BFD�Ự�Ƿ���mulit-hop */ 
    ULONG   ulActTxInterval           ;              /* BFDʵ�ʵķ��ͼ�� */ 
    ULONG   ulActRxInterval           ;              /* BFD��ʵ�ʽ������� */ 
    ULONG   ulDetectTime              ;              /* BFD��ʵ�ʼ��ʱ�� */
    ULONG   ulActEchoTxInterval       ;              /* BFD�Ự���ػ������ܵ�ʵ�ʷ������� */ 
    ULONG   ulActEchoRxInterval       ;              /* BFD�������ܵ�ʵ�ʽ��ռ�� */ 
    ULONG   ulRcvAuthSeq              ;              /* ���յ����к� */
    ULONG   ulXmitAuthSeq             ;              /* ���͵����кŶ���MD5��SHA1 */
    BOOL_T  bAuthSeqKnown             ;              /* ���յ����к��Ƿ��֪ */
    BOOL_T  bPollFlag                 ;              /* �Ƿ�����ѯ���� */
    USHORT  usLocalDiag               ;              /* ��������ֶ� */
    USHORT  usSessState               ;              /* �Ự�ĵ�ǰ״̬ */
} BFD_SESS_RUN_ENTRY_BAK_S;

typedef struct tagBFD_SESSION_BAK
{
    USHORT  usType;                               /* ������Ϣ������ */
    USHORT  usLen;                                /* ������Ϣ����ܳ��� */
    ULONG   ulSessId;                             /* �ỰID */
    ULONG   ulAppId;                              /* Ӧ�ù������ */
    BFD_SESSION_CFG_HA_BAK_S  stSessCfgEntry;     /* �Ự���ÿ� */
    BFD_SESS_RUN_ENTRY_BAK_S  stSessRunEntry;    /* BFDʵ�ʵ���Ϣ */
}BFD_SESSION_BAK_S;

/* SESSION Down��Ϣ�ı��� */
typedef struct tagBFD_DIG_DOWN_BAK
{
    USHORT usType;           /* ������Ϣ������ */
    USHORT usLen;            /* ������Ϣ����ܳ��� */
    ULONG  ulSessionID;      /* ���ÿ������ĻỰ���� */
    ULONG  ulVrfIndex;       /* VRF���� */
    ULONG  ulDigDown;        /* Session down������ */
}BFD_DIG_DOWN_BAK_S;

/* SESSION Ӧ������Ϣ�ı��� */
typedef struct tagBFD_APPGROUP_BAK
{
    USHORT usType;           /* ������Ϣ������ */
    USHORT usLen;            /* ������Ϣ����ܳ��� */
    ULONG  ulSessionID;      /* ���ÿ������ĻỰ���� */
    ULONG  ulVrfIndex;       /* VRF���� */
    ULONG  ulAppGroup;       /* Session Ӧ������Ϣ */
}BFD_APPGROUP_BAK_S;

typedef struct tagBFD_SETSINGAPPS_BAK
{
    USHORT usType;           /* ������Ϣ������ */
    USHORT usLen;            /* ������Ϣ����ܳ��� */
    ULONG  ulSessionID;      /* ���ÿ������ĻỰ���� */
    ULONG  ulVrfIndex;       /* VRF���� */
    ULONG  ulAppID;
} BFD_SETSINGAPPS_BAK_S;

typedef struct tagBFD_MULTIHOP_PORT_BAK
{
    USHORT usType;           /* ������Ϣ������ */
    USHORT usLen;            /* ������Ϣ����ܳ��� */
    ULONG  ulSessionID;      /* ���ÿ������ĻỰ���� */
    ULONG  ulVrfIndex;       /* VRF���� */
    ULONG  ulPort;           /* ����UDP�˿ں� */
} BFD_MULTIHOP_PORT_BAK_S;

typedef struct tagBFD_SESSION_NAME_BAK
{
    USHORT usType;           /* ������Ϣ������ */
    USHORT usLen;            /* ������Ϣ����ܳ��� */
    ULONG  ulSessionID;      /* ���ÿ������ĻỰ���� */
    ULONG  ulVrfIndex;       /* VRF���� */
    UCHAR  szCfgName[BFD_MAX_SESS_NAME_LEN + 1];
} BFD_SESSION_NAME_S;

typedef struct tagBFD_SESSION_DESC_BAK
{
    USHORT usType;           /* ������Ϣ������ */
    USHORT usLen;            /* ������Ϣ����ܳ��� */
    ULONG  ulSessionID;      /* ���ÿ������ĻỰ���� */
    ULONG  ulVrfIndex;       /* VRF���� */
    UCHAR  szSessionDes[BFD_MAX_DESC_NAME_LEN + 1];
} BFD_SESSION_DESC_S;

#define BFD_HA_PACKET_COPY(PACKET_TO, PACKET_FROM)\
{\
    PACKET_TO.bVers = PACKET_FROM.bVers;\
    PACKET_TO.bDiagnostic = PACKET_FROM.bDiagnostic;\
    PACKET_TO.bState = PACKET_FROM.bState;\
    PACKET_TO.bPollFlag = PACKET_FROM.bPollFlag;\
    PACKET_TO.bFinalFlag = PACKET_FROM.bFinalFlag;\
    PACKET_TO.bControlPlanFlag = PACKET_FROM.bControlPlanFlag;\
    PACKET_TO.bAuthenticationFlag = PACKET_FROM.bAuthenticationFlag;\
    PACKET_TO.bDemandModeFlag = PACKET_FROM.bDemandModeFlag;\
    PACKET_TO.bReserved = PACKET_FROM.bReserved;\
    PACKET_TO.ucDetectMult = PACKET_FROM.ucDetectMult;\
    PACKET_TO.ucPacketLength = PACKET_FROM.ucPacketLength;\
    PACKET_TO.ulLocalDiscriminitor = PACKET_FROM.ulLocalDiscriminitor;\
    PACKET_TO.ulRemoteDiscriminitor = PACKET_FROM.ulRemoteDiscriminitor;\
    PACKET_TO.ulDesiredMinTxInterval = PACKET_FROM.ulDesiredMinTxInterval;\
    PACKET_TO.ulRequiredMinRxInterval = PACKET_FROM.ulRequiredMinRxInterval;\
    PACKET_TO.ulRequiredMinEchoRxInterval = PACKET_FROM.ulRequiredMinEchoRxInterval;\
}

#define BFD_HA_SESSION_PARA_COPY(SESSION_TO, SESSION_FROM)\
{\
    SESSION_TO.ulDetectMode = SESSION_FROM.ulDetectMode;\
    SESSION_TO.ulMinTxInterval = SESSION_FROM.ulMinTxInterval;\
    SESSION_TO.ulMinRxInterval = SESSION_FROM.ulMinRxInterval;\
    SESSION_TO.ulDetectMult = SESSION_FROM.ulDetectMult;\
}

#define BFD_HA_SESS_RUN_ENTRY_COPY(ENTRY_TO, ENTRY_FROM)\
{\
    ENTRY_TO.ulLocalDiscr = ENTRY_FROM.ulLocalDiscr;\
    ENTRY_TO.ulRemoteDiscr = ENTRY_FROM.ulRemoteDiscr;\
    ENTRY_TO.usUdpSrcPort = ENTRY_FROM.usUdpSrcPort;\
    ENTRY_TO.usUdpDstPort = ENTRY_FROM.usUdpDstPort;\
    ENTRY_TO.usDetectMode = ENTRY_FROM.usDetectMode;\
    ENTRY_TO.usIsMultiHop = ENTRY_FROM.usIsMultiHop;\
    ENTRY_TO.ulActTxInterval = ENTRY_FROM.ulActTxInterval;\
    ENTRY_TO.ulActRxInterval = ENTRY_FROM.ulActRxInterval;\
    ENTRY_TO.ulDetectTime = ENTRY_FROM.ulDetectTime;\
    ENTRY_TO.ulActEchoTxInterval = ENTRY_FROM.ulActEchoTxInterval;\
    ENTRY_TO.ulActEchoRxInterval = ENTRY_FROM.ulActEchoRxInterval;\
    ENTRY_TO.ulRcvAuthSeq = ENTRY_FROM.ulRcvAuthSeq;\
    ENTRY_TO.ulXmitAuthSeq = ENTRY_FROM.ulXmitAuthSeq;\
    ENTRY_TO.bAuthSeqKnown = ENTRY_FROM.bAuthSeqKnown;\
    ENTRY_TO.bPollFlag = ENTRY_FROM.bPollFlag;\
    ENTRY_TO.usLocalDiag = ENTRY_FROM.usLocalDiag;\
    ENTRY_TO.usSessState = ENTRY_FROM.usSessState;\
}


/* ��ֵBFD�Ự��Ϣ */
#define HA_SESSION_CFG_HA_PACK(stSESSION_CFG_TO, stSESSION_CFG_FROM) \
{\
    stSESSION_CFG_TO.ulBfdType = stSESSION_CFG_FROM.ulBfdType;\
    stSESSION_CFG_TO.ulPeerAddrType = stSESSION_CFG_FROM.ulPeerAddrType;\
    (VOID)TCPIP_Mem_Copy(stSESSION_CFG_TO.ulSrcAddr, sizeof(ULONG) * 4, stSESSION_CFG_FROM.ulSrcAddr, sizeof(ULONG) * 4);\
    (VOID)TCPIP_Mem_Copy(stSESSION_CFG_TO.ulPeerAddr, sizeof(ULONG) * 4, stSESSION_CFG_FROM.ulPeerAddr, sizeof(ULONG) * 4);\
    stSESSION_CFG_TO.ulIfIndex = stSESSION_CFG_FROM.ulIfIndex;\
    stSESSION_CFG_TO.ulVrfIndex = stSESSION_CFG_FROM.ulVrfIndex;\
    stSESSION_CFG_TO.ulVlanId = stSESSION_CFG_FROM.ulVlanId;\
    stSESSION_CFG_TO.bDemand = stSESSION_CFG_FROM.bDemand;\
    stSESSION_CFG_TO.bEcho = stSESSION_CFG_FROM.bEcho;\
    stSESSION_CFG_TO.ulDemandTimerInterval = stSESSION_CFG_FROM.ulDemandTimerInterval;\
    stSESSION_CFG_TO.ulDetectMult = stSESSION_CFG_FROM.ulDetectMult;\
    stSESSION_CFG_TO.ulMinTxInterval = stSESSION_CFG_FROM.ulMinTxInterval;\
    stSESSION_CFG_TO.ulMinRxInterval = stSESSION_CFG_FROM.ulMinRxInterval;\
    stSESSION_CFG_TO.ulMinEchoTxInterval = stSESSION_CFG_FROM.ulMinEchoTxInterval;\
    stSESSION_CFG_TO.ulMinEchoRxInterval = stSESSION_CFG_FROM.ulMinEchoRxInterval;\
    stSESSION_CFG_TO.ulWtrTimeInterval = stSESSION_CFG_FROM.ulWtrTimeInterval;\
    stSESSION_CFG_TO.usAuthMode = stSESSION_CFG_FROM.usAuthMode;\
    stSESSION_CFG_TO.ucAuthKeyId = stSESSION_CFG_FROM.ucAuthKeyId;\
    (VOID)TCPIP_Mem_Copy(stSESSION_CFG_TO.ucAuthPwd, BFD_LEN_MAX_SIMPLE_PWD + 1, stSESSION_CFG_FROM.ucAuthPwd, BFD_LEN_MAX_SIMPLE_PWD + 1);\
}

ULONG BFD_HA_BatchBackup(VOID);
ULONG BFD_HA_BuildOnePacket(USHORT usType, ULONG ulSessionId, VOID * pucData, VOID *pucInBuf, USHORT usInBufLen);
ULONG BFD_HA_BuildSendOnePacket(USHORT usType, ULONG ulSessionId, VOID * pucData, USHORT usInBufLen);
ULONG BFD_HA_BatchBackupSendPacket (UCHAR * pucData, USHORT usDataLen, ULONG ulCount);
ULONG BFD_HA_SendPacket(UCHAR * pucData, USHORT usDataLen);
ULONG BFD_HA_Input(UCHAR * pucBuf, ULONG ulMsgLen);
ULONG BFD_HA_CopyTOSession(BFD_SESSION_BAK_S *pstBfdSessionBak);
ULONG BFD_HA_Smooth(VOID);
ULONG BFD_HA_SmoothOneSession(BFD_SESS_ENTRY_S *pstSession);
ULONG BFD_HA_CanSendPacket(VOID);
ULONG BFD_HA_CannotCfg(VOID);
ULONG BFD_HA_GetDbgSwitch(VOID);
VOID BFD_HA_Register();
VOID BFD_HA_DebugOutPut(UCHAR *pBuf, ULONG ulMsgLen, ULONG ulCmd);
ULONG BFD_HA_SetBfdVerboseDbg(ULONG ulDbg);
ULONG BFD_HA_GetBfdVerboseDbg(ULONG *pulDbg);
ULONG BFD_HA_Clean(VOID);

#ifdef  __cplusplus
}
#endif

#endif

