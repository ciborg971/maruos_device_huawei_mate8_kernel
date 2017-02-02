

#ifndef _PPP_CORE_TYPE_H_
#define _PPP_CORE_TYPE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "tcpip/ppp/include/ppp_api.h"



/* PPP���ƿ� */
typedef struct tagPppInfo
{
    ULONG bIsAsync: 1,        /* �Ƿ����첽��, ��LCP���ж��Ƿ�Э��ACCMAP */
          bSynAsyConvert: 1,  /* �����첽�ڣ�����ȷ���Ƿ���PPP����ͬ/�첽����ת�� */
          bLoopBacked: 1,     /* �ӿ��Ƿ������Ի� */
          bLowerIsUp: 1, 

          bIsDialer:1,       /* �Ƿ񲦺ſ� */
          bIsCallIn:1,       /* �Ƿ��Ǻ���,�����ж��Ƿ�callback */
          bIsCallBackUser:1, /* �Ƿ���callback�û�,��֤ʱ��AAA��� */

          bMpChannelType:2, /* MPͨ������
                                0(PPP_MP_NONE):����MP
                                1(PPP_MP_SUBCHANNEL):MP��ͨ��
                                2(PPP_MP_FATHER):MP��ͨ��
                                3(PPP_MP_TEMPLATE):MPģ��
                             */

          bPppInterleave:1,  /*�Ƿ�����LFI*/

          bRunningPoeClient:1, /* ������PPP Info�ṹ�Ƿ�����PPPoE Client*/

          bLqmStatus:1, /* ����LQM��·״̬ */
          bReserved: 20;     /* ����,�Ժ�ʹ�� */

    ULONG ulRemoteAccm;      /* �Զ�ACCM������ */
    ULONG ulLocalAccm;       /* ����ACCM������ */

    ULONG ulIfIndex;         /* ��Ӧ��IFNET���� */
    ULONG ulVLinkIndex;      /* ������VLink���� */

    ULONG ulGetAddrTmerId;

    ULONG ulRouteIfIndex;    /* ·�ɿɼ��ӿڵ�IFNET���� */

    /* ����PPPЭ����ƿ������ָ�� */
    DLL_NODE_S  stPppInfoLink; 

    ULONG usPhase;           /* PPP��ǰ����Э�̽׶�,����Ϊ����ֵ:
                                 PPP_PHASE_DEAD
                                 PPP_PHASE_ESTABLISH
                                 PPP_PHASE_AUTHENTICATE
                                 PPP_PHASE_CBCP
                                 PPP_PHASE_NETWORK
                                 PPP_PHASE_TERMINATE
                              */

    ULONG ulResetTimerId;    /* Э��ʧ�ܺ�,����reset��ʱ��,��ʱ������Э��.
                                 ������L2TP tunnel��PPPOE����ӿڻ�DDR�����,
                                 ��֪ͨIFNET��ֱ�Ӷϵ�
                              */


    ULONG ulPpiFailed;      /* PPI�·�ʧ�ܱ�־λ */
    ULONG ulFatherIfIndex;  /* ����PPI(MP)�ظ��·�ʱ�ҵ�Ҫ�·��ĸ��ӿ� */
    

    /* ������Ϣ */
    PPPCONFIGINFO_S *pstConfigInfo;      /* ��ǰ�ӿ����û������������Ϣ,
                                            ֻ�����ÿɼ��ӿ���Ч
                                          */
                              
    PPPCONFIGINFO_S *pstUsedConfigInfo;  /* ��ǰ�ӿ�����Э�̵�������Ϣ,
                                            �Ǵӵ�ǰ�ӿڻ������ӿڵ�pstConfigInfo��������
                                          */

    /* ��Э��ָ�� */
    VOID *pstLcpInfo;        /* LCP  ���ƿ�ָ�� */
    VOID *pstPapInfo;        /* PAP  ���ƿ�ָ�� */
    VOID *pstChapInfo;       /* CHAP ���ƿ�ָ�� */
    VOID *pstIpcpInfo;       /* IPCP ���ƿ�ָ�� */
    
    VOID *pstLqmInfo;        /* LQM  ���ƿ�ָ�� */

    VOID *pstIp6cpInfo;       /* IPv6CP ���ƿ�ָ�� */ 

    ULONG ulIP6LinkStatus;          /* �����ӿڵ�IPv6 DOWN��UP״̬ */
    UCHAR ucInterfaceID[8];         /* �ӿ�ID */
    UCHAR ucInterfaceIDAuto[8];     /* �ӿ�ID */
    ULONG ulFirstGetInterfaceID;    /* ��һ�λ�ȡ�ӿ�ID�ı�־ */
    ULONG ulInterfaceIDType; 

    VOID *pstMpInfo;         /* MP���ƿ�ָ��
                                 ����MP��ͨ��(virtual access)����MP���ƿ�ָ��
                                 ����MP��ͨ�����Ǹ�ͨ����IFNET����
                                 ����MPģ��(virtual template��BRI/PRI),��
                                 virtual access����ָ��
                              */
    VOID *pstMuxcpInfo;      /* PPPMUXCP ���ƿ�ָ�� */

    struct tagPppStatistic stStatisticInfo; /* ͳ����Ϣ�������Ʒ���Ϣ��Mibͳ����Ϣ */

    struct tagPppDebugInfo stPppDebugInfo;  /* �ӿڵ�debug������Ϣ */

    USHORT usMtu;

    /* ��¼�����������PPP�澯 */
    USHORT usWarningRecord;

    UCHAR ucAuthServer;        
    UCHAR ucAuthClient;
    UCHAR ucPadding_2[2];
    CHAR  szLoginUsrName[PPP_MAXUSERNAMELEN + 1]; /* �Զ�������֤ʱʹ�õ��û��� */
    CHAR  szCallBackDialString[PPP_MAXCALLBACKDIALERSTRINGLEN + 1];
    /*yinyuanbin add 2003-02-12 for aaa authencation*/
    CHAR  szCalledNumber[PPP_CALLINGNUM_LEN + 1];
    CHAR  szCallingNumber[PPP_CALLEDNUM_LEN + 1];
    /*end*/
    ULONG ulUserId;

    struct tagIPHC_COMPRESSION_CONTEXT *pCompContext;
    LONG  lCCompany;                        /* Э�̽������ */

    struct tagSLCompress *pVJContext;

    struct tagPPPMUX_CONTEXT_STRUCT* pstMuxContext; /* PPPMUX������ָ�� */
    /* End of addition */
    ULONG ulIsIsFlag;     /* �Ƿ�ʹ���շ�ISIS���ģ�Ϊ1ʹ�ܣ�0ȥʹ�� */
    VOID *pstOsicpInfo;   /* Osicp ���ƿ�ָ�� */
    UCHAR ucPPPType;
    UCHAR ucBakflag ;    /* PPP init��� */

    UCHAR ucCurrentMode;  /* ��ǰPPP�ӿ�ģʽ, 0-����ģʽ,1-����ģʽ(����ģʽ�²��շ�����) */
    UCHAR ucRestoreFlag;  /* ����ģʽ��,�ָ��ɹ�ʧ�ܱ��, 0-�ָ��ɹ�, 1-�ָ�ʧ�� */
    UCHAR ucNpHandleLcpEcho; /* NP�Ƿ���PPP LCP Echo, 0-VISP����, 1-NP���� */
    UCHAR ucPadding_3[3];
    
    ULONG ulNegTimeCnt;         /* ָ��ʱ����Э�̲�ͨ������ */
    ULONG ulNcpResendTimerId;   /* NCP��ʱ����һ��CR���ĵĶ�ʱ��ID */
} PPPINFO_S;

/* PPP���Ͷ��� */
typedef enum tagPPPTPYE
{
    PPPTYPE_PPP = 0, /*��ͨPPP*/
    PPPTYPE_PPPOE,
    PPPTYPE_PPPOEOA,
    PPPTYPE_PPPOA,

    PPPTYPE_MAX
}PPPTYPE_ENUM;

/* Multilink User����ڵ� */
typedef struct tagPppMultilinkUser
{
    struct tagPppMultilinkUser *pNext;        /* ����ָ�� */
    CHAR cUserName[PPP_MAXUSERNAMELEN + 2];   /* �û��� */
    CHAR c_IntfName[200 + 2];                 /* virtual template�ӿ��� */
} PPPMULTILINKUSER_S;


/* ״̬��ģ�����ݽṹ���� */
typedef struct tagPppFsm
{
    CHAR *  pProtocolInfo;         /* ��Э����ƿ�ָ�� */
    CHAR *  pPppInfo;              /* PPP���ƿ�ָ�� */
    ULONG   ulTimeOutTime;         /* config request/terminate request���ĵĳ�ʱʱ�� */
    ULONG   ulTimeOutID;           /* config request���ĵĶ�ʱ�� */
    ULONG   ulEchoTimeOutTime;     /* LCP Echo request���ĵĳ�ʱʱ�� */
    ULONG   ulEchoTimeoutID;       /* LCP Echo request���ĵĶ�ʱ�� */

    ULONG   ulResetTimerId;        /* NCP reset��ʱ�� */

    ULONG   ulIPCPResetTimerId;

    struct tagPppFsmCallbacks *pstCallBacks;  /* �ص������� */

    ULONG   ulNeedNego;

    USHORT  usProtocol;            /* ��Э���PPPЭ��� */
    SHORT   sRetransmits;          /* config request/terminate request�����ش����� */
    USHORT  usNakloops;            /* Nak�Է�ͬһ��ѡ��Ĵ��� */
    UCHAR   ucState;               /* Э��״̬ */
    UCHAR   ucPktId;               /* ��Э�鵱ǰ���ĵ�ID */
    UCHAR   ucEchoId;              /* LCP Echo request���ĵ�ID */
    UCHAR   ucEchoTimes;           /* PPP echo̽����� */
    USHORT  usDownReason;          /* ��¼������(down��close�¼�)���µ�PPPЭ��downԭ�� */
} PPPFSM_S;

typedef struct tagPppFsmCallbacks
{
    /* ������Э�̱��Ĵ��� */
    VOID  (*resetci)(PPPFSM_S *);   /* ����������Ϣ����Э�̳�ʼֵ */
    USHORT (*cilen)(PPPFSM_S *);    /* ��Ҫ���͵�request���ĳ��� */

    VOID  (*addci)(PPPFSM_S *, UCHAR *);          /* ��֯Э�̱��� */

    USHORT (*ackci)(PPPFSM_S *, UCHAR *, ULONG);  /* ����Է���ack���� */

    USHORT (*nakci)(PPPFSM_S *, UCHAR *, ULONG);  /* ����Է���nak���� */

    USHORT (*rejci)(PPPFSM_S *, UCHAR *, ULONG);  /* ����Է���reject���� */

    UCHAR (*reqci)(PPPFSM_S *, UCHAR *, ULONG *); /* ����Է���request���� */

    USHORT (*extcode)(PPPFSM_S *, UCHAR, UCHAR, UCHAR *, UCHAR *, ULONG); /* ����Э�����еı��ģ���protocol reject�� */
                                  
    /* �¼���Э��ת������ֹ״̬ */
    VOID (*up)(PPPFSM_S *);         /* Э��up */

    ULONG (*upcheck)(PPPFSM_S *);   /* Э��up���Э�̽��������ȷ�Լ��  */     

    VOID (*down)(PPPFSM_S *);       /* Э����ʱdown,����Ҫ����Э��.
                                       ��finished��������:����PPPOE��DDR�ȵ������
                                       ����֪ͨ�²�����· */
    VOID (*finished)(PPPFSM_S *);   /* Э�������֪ͨ�ײ�:�����·.����LCP,ֻҪ����
                                       PPPOE��DDR�ȵ����,�������reset��ʱ��,
                                       ��ʱ����������Э�� */
    VOID (*starting)(PPPFSM_S *);   /* tls(This-Layer-Started)�����У�֪ͨ�²�:��׼
                                       ����������Э��,�����,�뷢һ��up�¼�.
                                       Э����������û�о���涨,���Բ�ʵ��*/

    VOID (*timerout)(VOID *);       /* PPP��Э��״̬��FSM��ʱ������ */

    VOID (*ncpreset)(VOID *);       /* PPP��Э��״̬�������ش���ʱ������ */

    /* ��Э����Ϣ */
    CHAR proto_name[8];             /* ��Э���� */
} PPPFSMCALLBACK_S;


typedef struct tagMP_USER_INFO
{
    DLL_NODE_S stDLLNode;                 /* ˫����ڵ� */
    ULONG ulVirtualTemplateNum;           /* ��Ӧ��ģ��� */
    UCHAR ucUserName[MP_USERNAME_LEN + 2];/* �û��� */
    UCHAR ucPadding[2]; 
    DLL_S *pulIfIndexList;
} MP_USER_INFO_S;/*�û���-��ģ���Ӧ��ṹ*/

typedef struct tagMPGROUP_LIST_INFO
{
    DLL_NODE_S stDLLNode;   /* ˫����ڵ� */
    UCHAR ucMpGroupName[IF_MAX_INTERFACE_NAME_LEN+1];/* �û��� */
    DLL_S *pulSubLinkList;
} MPGROUP_LIST_INFO_S;

/**�����ģ��id*******/
typedef struct tagPPP_ModInfo
{
    ULONG ulMID_PPP;
    ULONG ulMID_IFNET;
    ULONG ulMID_STAC;
    ULONG ulMID_STAC_HASH;
    ULONG ulMID_VJCOMP;
    
    ULONG ulSID_PPP_PACKET_S;
    ULONG ulSID_PPP_CB_S;
    ULONG ulSID_PPP_L2TPOPTION_S;
    ULONG ulSID_PPP_L2TPPARA_S;
    ULONG ulSID_PPP_BUILDRUN;
    ULONG ulSID_STAC_BUFFER_S;
    ULONG ulSID_STAC_HASHNODE_S;
    ULONG ulSID_STAC_MINLIST_S;
    ULONG ulSID_STAC_PACKET_S;
    ULONG ulSID_PPP_ASY_S;
    ULONG ulSID_PPP_SYN_S;
    ULONG ulSID_MBUF_S;
    
    ULONG ulQUE_PPP_ASY;
    ULONG ulQUE_IP_INPUT;
    ULONG ulQUE_IPV6_INPUT;
    ULONG ulQUE_MPLS_INPUT;
    ULONG ulQUE_IPX;
    ULONG ulQUE_ISIS_INPUT;
    ULONG ulQUE_PPP_STAC;
    ULONG ulQUE_PPP_MP;
    ULONG ulQUE_PPP_NEGO;
    ULONG ulQUE_PPPMUX_INPUT;

    /*Ԥ���ò���*/
    ULONG ulPPP_DEF_NEED_PAP;/* PPP��·�Ƿ���ҪPAP��֤ */
    ULONG ulPPP_DEF_NEED_CHAP;/* PPP��·�Ƿ���ҪCHAP��֤ */
    ULONG ulPPP_DEF_NEED_LOOPNEGO;/*��һ��Э�̲��ɹ��Ժ��Ƿ�ȴ�һ��ʱ������ѭ��Э��*/
    ULONG ulPPP_DEF_NEGO_TIMEOUT;/* һ��Э�̳�ʱʱ�� */
    ULONG ulPPP_DEFAULT_KEEPALIVE;/* ��·��Э�̺�̽����·״̬ */
    ULONG ulPPP_DEFMRU;/*Э��ʱȱʡMRU*/
    ULONG ulPPP_DEFAULT_ACCM;/*ȱʡͬ�첽ת���ַ��������п����ֶ�ת��(0xffffffff) */
    ULONG ulPPP_DEF_NEED_NCP;/*����ȱʡ�Ƿ���ҪNCPЭ��*/
    ULONG ulPPP_DEF_NEED_LCP;/* Liqiang ʵ�����ܹ������Ʒ������---����ȱʡ�Ƿ���ҪLCPЭ�� 2003-12-17 */
    ULONG ulPPP_DEF_NEED_OSICP; /*����ȱʡ�Ƿ���ҪOSICPЭ��*/
    ULONG ulPPP_DEF_CONFREQS;/*Config Request���ش�����*/
    ULONG ulPPP_DEF_MAX_CTLNUM;/*���PPP���ƿ���Ŀ*/
    ULONG ulNeedAsyQue;/*�Ƿ���Ҫ�����첽���Ķ���*/
    ULONG ulTcpSpace;       /* TCP��ʽ���CIDֵ */
    ULONG ulNonTcpSpace;    /* ��TCP��ʽ���CIDֵ */
    ULONG ulRtpCompression; /* Э��(Enhanced) RTP Compression��ѡ��Э������ */
    ULONG ulCompressType;   /* ����ѹ����������*/
    ULONG ulIphcNpSwitch;   /* �Ƿ�֧��NP��IPHC����*/
    ULONG ulUnidirction;    /* �Ƿ�֧�ֵ����� */
    /* End of addition for IPHC,2005/09/19*/
    /*Add by z2474 for BC3D00352 2008-09-20*/
    ULONG ulChapCheckUser;  /* Chap Client���Ƿ�У���û��� */
    ULONG ulGlobalTimer;
    ULONG ulIphcSubOptAdapt;
}PPP_MOD_INFO_S;

/**************shell ��coreע��Ļص�������************************************/
typedef ULONG (* PPP_QueDealPacketFunc)(MBUF_S *);                    /* ������ĺ��� */
typedef ULONG (* PPP_QueIsDropThisPacketFunc)(MBUF_S *,ULONG,CHAR*); /* �Ƿ��� */

typedef struct tagPPP_SHELL_CALLBACK_SET
{
    ULONG (*pfCLI_EnableCommand)( CHAR *  szCmdModeName, CHAR * szCmdKey );
    ULONG (*pfCLI_DisableCommand)( CHAR *  szCmdModeName, CHAR * szCmdKey );
    
    ULONG (*pfQue_AddQueLen)(ULONG ulQueID,ULONG ulLen);
    VOID (*pfQue_FreePacketInQueueForRequest)(ULONG ulQueID,ULONG ulCmd,CHAR* pData);
    ULONG (*pfQue_GetQueLen)(ULONG ulQueID);
    ULONG (*pfQue_SetQueLen)(ULONG ulQueID,ULONG ulMaxLen);

    ULONG (*pfQue_RegisterQue)(ULONG ulQueID, ULONG ulGetCntPerTimes, PPP_QueDealPacketFunc pfDealPkt, PPP_QueIsDropThisPacketFunc pfIsDropThisPkt, ULONG ulMaxLen);
    ULONG (*pfQue_ActiveQue)(ULONG ulQueID);
    ULONG (*pfQue_DeActiveQue)(ULONG ulQueID);
    ULONG (*pfQue_EnQueue)(MBUF_S* pMBuf);
    ULONG (*pfPPP_EnDropQue)(MBUF_S *pMBuf);
        
    ULONG (*pfPPP_NotifyIpcpDown)(ULONG ulIfIndex);
    ULONG (*pfPPP_BuildRun)(CHAR* szSectionName, CHAR** pszBuildRunInfo);
    
    VOID (*pfPPP_Shell_AuthRequest)(ULONG ulIfnetIndex, PPPAUTHMSG_S * pMsg);
    ULONG (*pfPPP_GetPeerIPAddress)(ULONG ulUserID, 
                                                                          ULONG ulIfnetIndex, 
                                                                                 PPP_GetPeerCallBack_PF pfGetPeerCallBack);
    VOID (*pfPPP_FreeAddr)(ULONG ulUserID, ULONG ulIfnetIndex, ULONG ulPeerIPAddress);
    ULONG (*pfPPP_Shel_Chap_GetUserPsw)(PPPAUTHMSG_S *pstMsg);

    VOID (*pfPPP_ShowDebugInfo)( CHAR *szString, ULONG ulLen );

}PPP_SHELL_CALLBACK_SET_S;

/********��ʱ����ؽṹ��������************/
typedef struct tagPppChainNode
{
    LONG lPrev; /*ǰ������*/
    LONG lNext; /*��������*/
}PPPCHAINNODE_S;

/*��ʱ���ص�����ָ��*/
typedef void (* PppTimeoutCall)( VOID * );

typedef struct tagPppTimerNode
{
    PPPCHAINNODE_S  stNode;
    ULONG           stEndTimeHigh;
    ULONG           stEndTimeLow;
    ULONG           ulTimerId;
    VOID            *pArg;
    PppTimeoutCall  stCallBack;
}PPPTIMERNODE_S;


/*****************************VLINK��ؽṹ����***********************************/
typedef struct  tagPppIFConfig
{
    USHORT  usIfDelay;
    USHORT  usIfReliability;
    USHORT  usIfLoad;
    UCHAR   ucPadding[2]; 
    ULONG   ulIfBandwidth;
    ULONG   ulIfBaudrate;
    ULONG   ulIfMtu;
    /*add sunyu for bandwidth,delay command*/
    ULONG   ulConfIfDelay;
    ULONG   ulConfIfBandwidth;
    /*end add sunyu for bandwidth,delay command*/

    ULONG   ulData;
} PPPIFCONFIG_S;

typedef struct tagPppIfMsgentry
{
    ULONG  ulIntfIndex;             /*�ӿ�Ψһ����ֵ*/
    ULONG  ulVlinkIndex;            /*����·����ֵ���ӿ��¼�ʱ��Ϊ0*/
    USHORT  usSlot;                 /*�ӿ����ڲۺţ� new in 3.0 */
    USHORT  usMsgType;              /*�����涨��*/
    USHORT  usIfState;              /*�ӿ�״̬*/
    USHORT  usIfFlags;              /* �ӿڱ�־*/        
    CHAR    cIfName[IF_MAX_INTERFACE_NAME_LEN + 1];    /*�ӿ�����*/
    USHORT  usIfType;                               /*�ӿ�����*/
    UCHAR ucPadding_1[2]; 
    PPPIFCONFIG_S      stIfData;                    /*�ӿڲ���*/
    SOCKADDR_S  stPeerAddr;         /*�Զ˵�ַ����������·ʱ�����жԶ˵�ַ*/
    ULONG ulMacAddrLen;
    UCHAR ucMacAddr[IF_MAX_MAC_LEN + 1];
    UCHAR ucPadding_2;
    /*added by roy to support vpn at 20031019*/
    ULONG ulVrfIndex;
    /*end added by roy to support vpn at 20031019*/    

}PPPIFMSGENTRY_S;

typedef struct tagPppIfMsgentry PPP_VLINKSTATUS_S;


typedef ULONG (*PPP_NotifySubMod_FuncPtr)(IFNET_S *pstIf, ULONG ulCmd, CHAR *pPara);

typedef struct tagPPPSUBMODCALLBACK
{
    PPP_NotifySubMod_FuncPtr pfPPP_NotifyMp;
}PPP_SUBMOD_CALLBACK_S;


#ifdef __cplusplus
}
#endif

#endif /* end of _PPP_TYPE_H_ */

