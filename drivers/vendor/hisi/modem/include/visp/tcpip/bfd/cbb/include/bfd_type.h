/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              bfd_type.h
*
*  Project Code: VISPV100R006
*   Module Name: BFD
*  Date Created: 2006-12-01
*        Author: Wangchengyang
*   Description: BFD��Ҫ�õ������ݽṹ���Ͷ���ͷ�ļ�
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME                DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2006-12-01      Wangchengyang       Create
*
*******************************************************************************/
#ifndef _BFD_TYPE_H_
#define _BFD_TYPE_H_

#ifdef __cplusplus
extern "C" {
#endif

#define BFD_DEFAULT_GATE_VALUE 501
/*End for BC3D02737*/
/* wangjiaqi modify for ipv6 bfd 20131119 begin */
#define BFD_ACTION_SND          1
#define BFD_ACTION_RCV          2
#define BFD_ACTION_SND_ERR      3
#define BFD_ACTION_RCV_ERR      4
/* wangjiaqi modify for ipv6 bfd end */

/* BFD�ļ��ģʽ */
/* CAUTION: if modify mode define,pls update g_aszDetectMode */
typedef enum tagBFD_DETECT_MODE_E
{
    BFD_DETECT_ASYNC_WECHO      = 0     ,       /* ��ECHO���ܵ��첽ģʽ */
    BFD_DETECT_ASYNC_WOECHO             ,       /* ����ECHO���ܵ��첽ģʽ */
    BFD_DETECT_DEMAND_WECHO             ,       /* ��ECHO���ܵĲ�ѯģʽ */
    BFD_DETECT_DEMAND_WOECHO            ,       /* ����ECHO���ܵĲ�ѯģʽ */
    BFD_DETECT_MODE_MAX                         /* ���ģʽ�������Чֵ */
} BFD_DETECT_MODE_E ;

/* BFD ��֤��ʽ */
typedef enum tagBFD_AUTH_TYPE_E
{
    BFD_AUTH_NONE      = 0            ,       /* ����֤ */
    BFD_AUTH_SIMPLE                   ,       /* ��pwd��֤ */
    BFD_AUTH_MD5                      ,       /* MD5��֤ */
    BFD_AUTH_MMD5                     ,       /* Meticulous MD5��֤ */
    BFD_AUTH_SHA1                     ,       /* SHA1��֤ */
    BFD_AUTH_MSHA1                    ,       /* Meticulous SHA1��֤ */
    BFD_AUTH_MAX                              /* �����Чֵ */
} BFD_AUTH_TYPE_E;

/*Begin BC3D02903 liangjicheng 2010-04-19 */
#define BFD_SESSION_STATE_NORMAL    0
#define BFD_SESSION_STATE_DELETE    1
/*End   BC3D02903 liangjicheng 2010-04-19 */  
/* wangjiaqi modify for ipv6 bfd 20131119 begin */
typedef struct tagBFD_SESS_PKT_STATIC_S
{
    /* Э��ͳ����Ϣ  ����*/
    ULONG ulBfdRcvDown;      /*���յ�DOWN����*/
    ULONG ulBfdRcvInit;      /*���յ�Init����*/
    ULONG ulBfdRcvUp;        /*���յ�Up����*/
    ULONG ulBfdRcvAdminDown; /*���յ�AdminDown����*/
    ULONG ulBfdRcvErr;       /*���յĴ�����*/
    ULONG ulBfdRcvP;         /*���յ�P����*/
    ULONG ulBfdRcvF;         /*���յ�F����*/

    /* Э��ͳ����Ϣ  ����*/
    ULONG ulBfdSndDown;      /*���͵�DOWN����*/
    ULONG ulBfdSndInit;      /*���͵�Init����*/
    ULONG ulBfdSndUp;        /*���͵�Up����*/
    ULONG ulBfdSndAdminDown; /*���͵�AdminDown����*/
    ULONG ulBfdSndErr;       /*���͵Ĵ�����*/    
    ULONG ulBfdSndP;         /*���͵�P����*/
    ULONG ulBfdSndF;         /*���͵�F����*/
}BFD_SESS_PKT_STATIC_S ;
/* wangjiaqi modify for ipv6 bfd end */
/* BFD�Ự�����ñ��� */
typedef struct tagBFD_SESS_CFG_ENTRY_S
{
    ULONG   ulBfdType                             ;      /* BFD�󶨵����� */
    ULONG   ulPeerAddrType                        ;      /* BFD�󶨵ĵ�ַ���� */
    ULONG   ulSrcAddr[4]                          ;      /* IPv4��IPv6��ַ,������ */
    ULONG   ulPeerAddr[4]                         ;      /* IPv4��IPv6��ַ,������ */
    ULONG   ulIfIndex                             ;      /* BFDָ���ĳ��ӿ����� */
    ULONG   ulVrfIndex                            ;      /* BFD's Vpn index*/
    ULONG   ulVlanId                              ;      /* BFDָ����VlanId��������̫���ӿ�ʱ�û���ѡ�� */
    BOOL_T  bDemand                               ;    
    BOOL_T  bEcho                                 ;    
    ULONG   ulDemandTimerInterval                 ;      /* BFD��ѯģʽ�¶�ʱ��ѯ�ļ������δʹ�� */ 
    ULONG   ulDetectMult                          ;      /* BFD�ı��ؼ�ⱶ�� */ 
    ULONG   ulMinTxInterval                       ;      /* BFD�����ķ��ͼ�� */ 
    ULONG   ulMinRxInterval                       ;      /* BFD�ı��ؽ������� */ 
    ULONG   ulMinEchoTxInterval                   ;      /* BFD�Ự���ػ������ܵĽ�������(��֧��Echo,��ֵ����Ϊ0) */ 
    ULONG   ulMinEchoRxInterval                   ;      /* BFD�������ܵķ��ͼ��(��֧��Echo,��ֵ����Ϊ0)*/ 
    ULONG   ulWtrTimeInterval                     ;      /* Time for wtr. millisecond */
    USHORT  usAuthMode                            ;      /* BFD����֤��ʽ */ 
    UCHAR   ucAuthKeyId                           ;      /* BFD���õ���֤KeyId */ 
    UCHAR   ucAuthPwd[BFD_LEN_MAX_SIMPLE_PWD + 1] ;      /* BFD���õ���֤pwd */
    ULONG   ulSentPakcets                         ;      /* ���ͱ��ĸ��� */
    ULONG   ulRcvPackets                          ;      /* ���ձ��ĸ��� */
    ULONG   ulLastSentTime                        ;      /* ����ͱ���ʱ�� */
    ULONG   ulUpToDown                            ;      /* �Ự״̬Up��ΪDown�Ĵ��� */

    /* �Զ��Ѿ�ȷ���˵��շ����, Added by wujie 61195 for A82D25354, 2008/05/12 */
    ULONG   ulAckedCfgTX                          ;
    ULONG   ulAckedCfgRX                          ;
    UCHAR   szCfgName[BFD_MAX_SESS_NAME_LEN + 1];
    UCHAR   szSessionDes[BFD_MAX_DESC_NAME_LEN + 1];
    UCHAR   ucTos                                 ;      /* bfd �Ựtos */
    UCHAR   Padding[3]                            ;
    ULONG   ulRemoteDiscr;
}BFD_SESS_CFG_ENTRY_S ;

/* �Ựʵ�ʵ�������Ϣ size 13*4�ֽ�*/
typedef struct tagBFD_SESS_RUN_ENTRY_S
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
    /*Add for BC3D00792,DR.177 ����Զ�ʵ�ʼ�ⱶ�� */
    ULONG   ulActDetectMult           ;              /* BFD�ĶԶ˼�ⱶ�� */
    ULONG   ulActEchoTxInterval       ;              /* BFD�Ự���ػ������ܵ�ʵ�ʷ������� */ 
    ULONG   ulActEchoRxInterval       ;              /* BFD�������ܵ�ʵ�ʽ��ռ�� */ 
    ULONG   ulRcvAuthSeq              ;              /* ���յ����к� */
    ULONG   ulXmitAuthSeq             ;              /* ���͵����кŶ���MD5��SHA1 */
    BOOL_T  bAuthSeqKnown             ;              /* ���յ����к��Ƿ��֪ */
    BOOL_T  bPollFlag                 ;              /* �Ƿ�����ѯ���� */
    USHORT  usLocalDiag               ;              /* ��������ֶ� */
    USHORT  usSessState               ;              /* �Ự�ĵ�ǰ״̬ */
    USHORT  usRemoteDemandMode        ;              /* �Զ�BFD�Ự�Ƿ�����Ϊ��ѯģʽ��BFD_TRUE:�Զ�����; BFD_FALSE:�Զ�δ���� */
    USHORT  usReserved                ;              /* ���ֽڶ��룬���ֶα������� */
    ULONG   ulRemoteMinRxInterval     ;              /*bfd�Զ������Ľ���ʱ����ֵ*/
    ULONG   ulRemoteMinTxInterval     ;              /*bfd�Զ������ķ���ʱ����ֵ added by luogaowei 2012-10-27*/
} BFD_SESS_RUN_ENTRY_S;

typedef struct tagBFD_SESS_COUNT_ENTRY_S
{
    ULONG   ulPktRcvDrop                        ;      /* �������ĵĸ��� */
    ULONG   ulPktSendErr                        ;      /* ���ͱ���ʧ�ܵĸ���*/
    ULONG   ulSessionStateTime                        ;      /* �Ự��ʼ��ʱ�� */
    ULONG   ulLastDownTime                        ;      /* ���һ��Down��ʱ�� */
} BFD_SESS_COUNT_ENTRY_S;

/* �Ự��Ϣ��ʹ������ṹ��ţ����Ϊ255�� */
typedef struct tagBFD_SESS_ENTRY_S
{
    ULONG   ulSessId                          ;      /* �ỰID */
    ULONG   ulDbgFlag                         ;      /* �Ựdebug���أ���λ����BFD_DEBUG_STATE/BFD_DEBUG_INPUT�� */
    ULONG   ulChangeFlag                      ;      /* �Ự����Ŀ��Ʊ��Ĳ����Ƿ���ı�־λ��1 ��ʾ���ģ�0 ��ʾδ���� */
    ULONG   ulAppId                           ;      /* �ỰӦ�ú�,һ������λ��ʶһ��Ӧ�� */
    ULONG   ulWtrTimerId                      ;      /* WTR��ʱ��ID */
    ULONG   ulTxTimerId                       ;      /* ���ͱ��Ķ�ʱ��ID */
    ULONG   ulDetectOrInitTimerId             ;      /* �ỰUp֮ǰΪInit��ʱ��ʱ�����ỰUp֮��Ϊ̽�ⶨʱ�� */    
    CHAR*   pchPacket                         ;      /* ���Ļ���Buffer��BFD4��BFD6�ṹ��ͬ;������δ������ֱ�ӿ������ͣ������ٹ��챨�� */
    ULONG   ulHAFlag                          ;      /* HA��ǣ�ȡֵBFD_HA_BEFORESMOOTH��BFD_HA_SMOOTHING��BFD_HA_SMOOTHED */
    /* Begin:VISP1.7C03 VRF wangchengyang,2009-02-01 */
    ULONG   ulVrfIndex                        ;      /* VRF����,��Ҫ����ͨ������ĻỰ���ƿ鷴�������ڵ�VRF */
    /* End:VISP1.7C03 VRF wangchengyang,2009-02-01 */
    
    /*Added by wangchengyang-xujun62830-57575, VISPV1R8C01, 2009/4/8 */
    ULONG   ulIpVer                           ;      /* IP�汾��ʶ:0--��ʾ��IPv4 BFD;1--��ʾ��IPv6 BFD */
    /* End of Added by wangchengyang-xujun62830-57575, 2009/4/8 */

    ULONG   ulSentNegoPakcets; /*����ͳ�Ʒ��ͱ��ĸ��������ᱻ��������ǻỰ��ɾ��*/

    BFD_SESS_CFG_ENTRY_S   stSessCfgEntry     ;      /* �Ự��������Ϣ�ı������� */
    BFD_SESS_RUN_ENTRY_S   stSessRunEntry     ;      /* BFDʵ�ʵ���Ϣ */ 
    BFD_SESS_COUNT_ENTRY_S stSessCountEntry;
    ULONG   ulCurrentGRState                  ;      /* ��BFD�Ự��ǰ��GR״̬, ȡֵ��enumBFD_GR_STATE */
    ULONG   ulNotifyTimerId                   ;       /*ָ��ʱ���ڶ���֪ͨһ���Զ�ʱ��*/

    /*Begin BC3D02903 liangjicheng 2010-04-19 */
    ULONG   ulStateFlag                       ;       /*����״̬��Ϣ������ˢ�²���*/
    /*End   BC3D02903 liangjicheng 2010-04-19 */
    ULONG   ulNoPPIDown                       ;       /*������ʶɾ���Ựʱ�Ƿ��·�BFD_PPI_SESSION_DELETE*/
    
    /*Begin BC3D03565 chenlong 2010-10-08 */
    ULONG   ulNoSendDDFlag                    ;       /*ȡֵΪ1��ʾɾ���Ựʱ������Admin Down����,ȡֵΪ0��ʾɾ���Ựʱ����Admin Down����*/
    /*End   BC3D03565 chenlong 2010-10-08 */
    ULONG   ulBfdProtocol;                            /*BFD�����Ự��Э������ BFD_PROTO_DRAFT4:�ݰ�4; BFD_PROTO_STD:��׼RFC*/
    UCHAR   ucPFState;                                /*P���״̬: P_NULL, P_OPEN , F_ACK, P_EXPIRE*/
    UCHAR   ucPSndCount;                              /*P���ķ��ʹ����� ���Ĭ��5��*/
    USHORT  usSessionPosNo;                           /*BFD�Ự�ı�ţ��ȴ������Ⱥ�˳��*/
#if (TCPIP_NSR == VRP_YES) 
    USHORT  usStateResultInSmooth;                    /* ƽ����Ự״̬*/
    UCHAR   ucNSRRcvAdmindown;                        /* nsr�������յ�admin down����*/
    UCHAR   ucNSRCfgAdmindown;                        /* nsr����������admin down*/
    UCHAR   ucNSRPPIFlag;                             /* NSR������PPI�·���־*/
    UCHAR   ucPad[3];
#endif
    /* wangjiaqi modify for ipv6 bfd 20131119 begin */
    BFD_SESS_PKT_STATIC_S stBfdSessPktStatic;
    /* wangjiaqi modify for ipv6 bfd end */  
    
    /* Added by fengjing209023 for S-BFD-MultiSession.CFG.001 ��ΪBFD_ON����Ч������Ĭ�ϲ���Ч */
    ULONG ulMultiHopFlag;       /* ������ϸñ�ǣ����ڶ�����Ҳ����3784������Ĭ��4784 */
    /* Added end */
    AVL3_NODE_S stBfdSessionNode;             /* AVL Node */
} BFD_SESS_ENTRY_S ;

/* BFD�Ŀ��Ʊ��ĸ�ʽ */
typedef struct tagBFD_CONTROL_PACKET_S
{
     BFD_PACKET_S   stMandPkt                      ;      /* ���Ʊ��ĵ�ǿ�Ʋ��� */
     UCHAR   ucAuthType                            ;      /* ��֤���� */
     UCHAR   ucAuthLen                             ;      /* ��֤���ĵĳ��� */
     UCHAR   ucAuthKeyID                           ;      /* ��֤��KeyID */
     UCHAR   ucAuthPwd[BFD_LEN_MAX_SIMPLE_PWD + 1] ;      /* ��֤��pwd */
     ULONG   ulSeqNum                              ;      /* ��֤�����к� */
} BFD_CONTROL_PACKET_S;

/* BFDʹ�ܿ���״̬ */
typedef enum tagBFD_CAPABILITY_E
{
    BFD_CAPABILITY_DISABLED      = 0         ,       /* BFD��ȥʹ�ܣ�Ĭ��Ϊ�� */
    BFD_CAPABILITY_ENABLED                   ,       /* BFD�Ѿ�ʹ�� */
    BFD_CAPABILITY_DISABLE_PROCESSING        ,       /* BFD������ȥʹ���� */
    BFD_CAPABILITY_MAX                       ,       /* BFDʹ�ܱ�������Чֵ */
}BFD_GLOBAL_CAPABILITY_E;

/* BFD License״̬ */
typedef enum tagBFD_LICENSE_E
{
    BFD_LICENSE_DISABLED      = 0         ,       /* BFD License��ȥʹ�� */
    BFD_LICENSE_ENABLED                   ,       /* BFD License�Ѿ�ʹ�� */
    BFD_LICENSE_DISABLING                 ,       /* BFD Licenseȥʹ����*/
    BFD_LICENSE_ENABLING                  ,       /* BFD Licenseʹ����*/
}BFD_GLOBAL_LICENSE_E;

/* BFD��Ϣ���� */
typedef enum tagBFD_MSG_TYPE_E
{
    BFD_ADD_IPADDR,           /* ���ӵ�ַ */
    BFD_DEL_IPADDR,           /* ɾ����ַ */
    BFD_START_POLL,           /* �û�����POLL */
    BFD_SESSION_CREATE,       /* �û������Ự */
    BFD_SESSION_UPDATE,       /* �Ự�������� */
    BFD_SESSION_SHUTDOWN,     /* �û�shutdown*/
    BFD_SESSION_UNDOSHUTDOWN, /* �û�undo shutdown */
    BFD_SESSION_DELETE,       /* ɾ���Ự */
    BFD_TRUNKPORT_ADD,        /* �ӿڼ���trunk */
    BFD_TRUNKPORT_REMOVE,     /* �ӿ��Ƴ�trunk */
    /*Added by wangchengyang-xujun62830-57575 for VISPV1R8C01, 2009/4/29 */
    BFD_GLOBAL_DISABLE,       /* ȫ��ȥʹ�� */
    /* End of Added by wangchengyang-xujun62830-57575, 2009/4/29 */
    /*Added by qinyun62011, �Ż�BFD�ỰID��չ��9215����������, 2013/9/27 */
    BFD_VRF_DELETE,           /* ɾ��VRF */
    /*End of Modified by qinyun62011, 2013/9/29 */
    BFD_LICENSE_SHUTDOWN,     /* BFD License���ܹر� */
    BFD_LICENSE_UNDOSHUTDOWN, /* BFD License���ܴ� */
    /*Added by xujun57575 for VISPV1R8C01, 2010/2/26 */
    BFD_GLOBAL_RESETALL,       /* ȫ�ָ�λ�Ự*/
    /* End of Added by xujun57575, 2010/2/26 */

    /*Begin BC3D02903 liangjicheng 2010-04-19 */
    BFD_EXT_OSPF_RULE_ADD,     /* ���ﶨ�����ִ���Ŀǰ�Ĵ������ָ����������������*/
    BFD_EXT_OSPF_RULE_UPDATE,
    BFD_EXT_OSPF_RULE_DELETE,
    /*End   BC3D02903 liangjicheng 2010-04-19 */
    /* wangjiaqi modify for ipv6 bfd 20131121 begin */
    BFD6_GLOBAL_DISABLE,        /* bfd6ȫ��ȥʹ�� */
    BFD6_VRF_DELETE,           /* ɾ��VRF */
    BFD6_GLOBAL_RESETALL,       /* bfd6ȫ�ָ�λ�Ự*/
    BFD6_LICENSE_SHUTDOWN,       /* BFD6 License���ܹر� */
    BFD6_LICENSE_UNDOSHUTDOWN,   /* BFD6 License���ܴ� */
    /* wangjiaqi modify for ipv6 bfd end */    
    BFD6_ADD_IPADDR,           /* ����IPv6��ַ */
    BFD6_DEL_IPADDR,           /* ɾ��IPv6��ַ */    
    BFD_EXT_REFERSH_ALL_RULE,    /*BFD EXTˢ�����й���*/
    BFD_MSG_MAX
}BFD_MSG_TYPE_E;

/* BFD��Ϣ���ݽṹ */
typedef struct tagBFD_MSG_S
{
   ULONG   ulMsgType       ;   /* ��Ϣ���� */
   ULONG   ulSessionID     ;   /* �ỰID�������û�����POLL */
   ULONG   ulIfIndex       ;   /* �ӿ����������ڵ�ַ��ɾ */
   /* Begin:VISP1.7C03 VRF wangchengyang,2009-02-01,��ΪBFD�Ự��Ҫ�ỰID��Vrf Index��ͬ��ʶ
   * ��д��Ϣ��ʱ����Ϣ���еĲ������ĸ�Ԫ�ص�ULONG������,���ڵ�ַ��VRFIndex��ͬʱ���֣���˸�Ϊ������ */
   union
   {
       ULONG   ulIPAddr    ;   /* ��ַ,���������ڵ�ַ��ɾ */
       UINTPTR ulIP6AddrHandle;
       ULONG   ulVrfIndex  ;   /* VRF���� */
       UINTPTR ulLinkLink  ;   /* ���ڴ������ݵ�ָ�� */
   }unPrivate;
   /* End:VISP1.7C03 VRF wangchengyang,2009-02-01 */
} BFD_MSG_S;

/*Begin BC3D02903 liangjicheng 2010-04-19 */
typedef struct tagBFD_EXT_OSPF_RULE_MSG
{
   ULONG    ulIPVertion;        /*IP�汾��*/
   ULONG    ulMsgType;          /* ��Ϣ���� */
   ULONG    ulProcIndex;
   ULONG    ulIfIndex;        /*�ӿ�����*/
   ULONG    ulInstanceID;     /*�ӿ�ʵ��ID(������OSPFV3����)*/
   ULONG    ulMinTxInterval;
   ULONG    ulMinRxInterval;
   ULONG    ulDetectMult;
} BFD_EXT_OSPF_RULE_MSG;
/*End   BC3D02903 liangjicheng 2010-04-19 */

/* Begin:VISP1.7C03 VRF wangchengyang,2009-02-01 */
/* BFD �Ự��ѯ���*/
typedef struct tagBFD_KEY_S
{
    ULONG ulVrfIndex    ;     /* vrf ���� */
    ULONG ulSessionId   ;     /* �Ự��ʶ */
    ULONG ulIsAllVrf    ;     /* �Ƿ��ѯ����VRF�µĻỰ:1-��,0-���� */
    /*Added by wangchengyang-xujun62830-57575 for VISPV1R8C01, 2009/4/20 */
    ULONG ulIpVer       ;     /* IP�汾��ʶ */
    /* End of Added by wangchengyang-xujun62830-57575, 2009/4/20 */
}BFD_KEY_S;
/* End:VISP1.7C03 VRF wangchengyang,2009-02-01 */

/*Added by wangchengyang-xujun62830-57575 for VISPV1R8C01, 2009/4/14 */
/* BFD6���Ľ�����Ϣ */
typedef struct tagBFD_PKTINFO_S
{
    ULONG  ulDstIP[4];     /* ����Ŀ��IP,������ */
    ULONG  ulSrcIP[4];     /* ����ԴIP,������ */
    ULONG  ulVrfIndex;     /* ���Ľ��ն�Ӧ��VRF */
    ULONG  ulIfIndex;      /* ��ӿ����� */
    USHORT usDstPort;      /* Ŀ�Ķ˿ں�,������ */
    USHORT usTTL;          /* ����Я����TTL */
    ULONG  ulIpVer;        /* IP�汾��ʶ:0--IPv4;1--IPv6 */
    ULONG  ulIsMutiHop;    /* �����Ƿ����*/
}BFD_PKTINFO_S;
/* End of Added by wangchengyang-xujun62830-57575, 2009/4/14 */

typedef struct tagBFD_SESSION_PUB_INFO_S
{
    ULONG ulSessionId; /* �ỰID */
    ULONG ulIpVer;        /* IP�汾��ʶ:0--IPv4;1--IPv6 */
    ULONG ulOutIndex; /* �Ự���ӿ�*/
    ULONG ulAppId;       /* �ỰӦ�ú�,һ������λ��ʶһ��Ӧ�� */
    USHORT usSessState;/* �Ự״̬*/
    USHORT usLocalDiag;/* ��������ֶ� */
}BFD_SESSION_PUB_INFO_S;

/* BFDģ���Ƿ��ܹ����ͱ��ݱ��� ����ԭ�� */
typedef ULONG(*BFD_HA_CAN_SEND_PACKET)(VOID);

/* BFDģ�鷢�ͱ��ݱ��� ����ԭ�� */
typedef ULONG(*BFD_HA_SEND_LIVE_PACKET)(USHORT usType, ULONG ulSessionId, VOID * pucData, USHORT usInBufLen);

/* BFDģ���ȡHA���Կ���״̬ ����ԭ�� */
typedef ULONG(*BFD_HA_GET_DBG_SWITCH)(VOID);

/* BFDģ���ѯ��ǰ�Ƿ��ֹ���� ����ԭ�� */
typedef ULONG(*BFD_HA_CANNOT_CFG)(VOID);

/* BFD HA���Ժ������ ����ԭ�� */
typedef VOID(*BFD_HA_DBG_OUTPUT)(CHAR *pDebugInfo);

/* BFD״̬֪ͨVRRPģ��Ĺ��� */
typedef VOID(*BFD_STATE_NOTIFYVRRP)(ULONG ulNotifyType, ULONG ulSessionID, ULONG ulVrfIndex, 
                    ULONG ulState, ULONG ulDstIP, ULONG ulSrcIP, ULONG ulInIfIndex, ULONG ulAppGroup);

/* BFD״̬֪ͨBFD EXTģ��Ĺ��� */
typedef VOID(*BFD_STATE_NOTIFYEXT)(ULONG ulNotifyType, ULONG ulSessionID, ULONG ulVrfIndex, 
                    ULONG ulDstIP, ULONG ulSrcIP, ULONG ulInIfIndex, ULONG ulNewSessionID);
/*End of Modified by qinyun62011, 2010/9/29 */

typedef ULONG (*BFD_TaskonitorTimeInit)(VOID);

#ifdef __cplusplus
}
#endif

#endif

