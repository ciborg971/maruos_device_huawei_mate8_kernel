


#ifndef        _TCP_API_H
#define        _TCP_API_H

#ifdef    __cplusplus
extern    "C"{
#endif

/*[Debug Flag]*/
#define TCP_DEBUG_PACKET    0x01
#define TCP_DEBUG_TRANSA    0x10 
/* Extend debug function for MD5 option, 2002,09,25, zhangfeng */
#define TCP_DEBUG_MD5       0x0100

#define TCP_DEBUG_OFF   0
#define TCP_DEBUG_ON    1

/*TCPģ�������*/
enum tagTCP_ErrCode
{
    TCP_FILTOK = VOS_OK,
    TCP_FAILURE,

    TCP_FILTNOTFOUND,      /* 2 û�ҵ�Ҫɾ���Ĺ���       */
    TCP_FILTNONE,          /* 3 ������Ѿ��������       */
    TCP_FILTTOOMUCH,       /* 4 �������                 */
    TCP_FILTINUSE,         /* 5 ָ���Ĺ����Ѿ������ù��� */
    TCP_FILTADD,           /* 6 �����һ������           */
    TCP_COMP_NULL,         /* 7 TCP���δע��            */
    TCP_PARA_ERR,          /* 8 ���������Χ�Ƿ�         */
    TCP_PARATYPE_ERR,      /* 9 ��������ͷǷ�           */
    TCP_INPUT_NULL_POINT,  /* 10 �����ָ�� */
    TCP_ERR_NULL_INPCB,    /* 11 INPCBָ��Ϊ�� */
    TCP_ERR_NULL_SOCKET,   /* 12 ��ȡSOCKET���ƿ�ָ��Ϊ�� */
    TCP_ERR_NULL_TCPCB,    /* 13 ��ȡTCPCP�ṹָ��Ϊ�� */
    TCP_ERR_GETSTAT_INPCB,     /* 14 ������Ԫ���ȡINPCBʧ�� */
    TCP_ERR_GETSTAT_SOCKETCB,  /* 15 ������Ԫ���ȡSOCKETCBʧ�� */
    TCP_ERR_GETSTAT_TCPCB,     /* 16 ������Ԫ���ȡTCPCBʧ�� */

    TCP_NETINFO_FINISH,        /* 17 TCPNetInfo ��ѯ���� */
    TCP_GETINPCB_WRONG,        /* 18 ��ȡ�õ���INPCBΪ�� */

    /*Added by wangtong207740, ����socket id ��ȡ��Ӧ��tcp����ͳ��, 2012/9/5 */
    TCP_NOT_GLOBAL_SOCKET,      /* 19 ��֧�ַ�ȫ��SOCKET���� */
    /* End of Added by wangtong207740, 2012/9/5 */

    TCP_ERR_MAX,
};

enum tagTCP_StateCode
{
    TCPSTATE_CLOSED        = 0,   /* closed */
    TCPSTATE_LISTEN        = 1,   /* listening for connection */
    TCPSTATE_SYN_SENT      = 2,   /* active, have sent syn */
    TCPSTATE_SYN_RECEIVED  = 3,   /* have send and received syn */
    TCPSTATE_ESTABLISHED   = 4,   /* established */
    TCPSTATE_CLOSE_WAIT    = 5,   /* rcvd fin, waiting for close */
    TCPSTATE_FIN_WAIT_1    = 6,   /* have closed, sent fin */
    TCPSTATE_CLOSING       = 7,   /* closed xchd FIN; await FIN ACK */
    TCPSTATE_LAST_ACK      = 8,   /* had fin and close; await FIN ACK */
    TCPSTATE_FIN_WAIT_2    = 9,   /* have closed, fin is acked */
    TCPSTATE_TIME_WAIT     = 10,  /* in 2*msl quiet wait after close */
};

/*set/get SYN/FIN/WIN*/
#define TCP_FUNSPEC_CHGKEEPVAL          0
#define TCP_FUNSPEC_CHGKEEPFINTIME      1
#define TCP_FUNSPEC_WINSIZE             2
#define TCP_FUNSPEC_ESTABLISHED         3


/* TCPͳ�ƽṹ */
typedef struct tagTCPSTAT
{
    ULONG    ulAccepts;
    ULONG    ulClosed;
    ULONG    ulConnAttempt;
    ULONG    ulConnDrops;
    ULONG    ulConnects;
    ULONG    ulDelayedAck;
    ULONG    ulDrops;
    ULONG    ulKeepDrops;
    ULONG    ulKeepProbe;
    ULONG    ulKeepTimeOut;
    ULONG    ulPAWSDrop;
    ULONG    ulPCBCacheMiss;

    /* Added by LQZ, Mar-26 97. */
    ULONG    ulPersistDrops;

    ULONG    ulPersistTimeOut;
    ULONG    ulPredictionAck;
    ULONG    ulPredictionData;
    ULONG    ulRcvAckByte;
    ULONG    ulRcvAckPacket;
    ULONG    ulRcvAckTooMuch;
    ULONG    ulRcvDupAck;
    ULONG    ulRcvAfterClose;
    ULONG    ulRcvBadOff;
    ULONG    ulRcvBadSum;
    ULONG    ulRcvByte;
    ULONG    ulRcvDupByte;
    ULONG    ulRcvDupPacket;
    ULONG    ulRcvPacketAfterWnd;
    ULONG    ulRcvByteAfterWnd;
    ULONG    ulRcvPartDupByte;
    ULONG    ulRcvPartDupPacket;
    ULONG    ulRcvOutOrderPacket;
    ULONG    ulRcvOutOrderByte;
    ULONG    ulRcvShort;
    ULONG    ulRcvTotal;
    ULONG    ulRcvPacket;
    ULONG    ulRcvWndProbe;
    ULONG    ulRcvWndUpdate;
    ULONG    ulRexmtTimeOut;
    ULONG    ulRTTUpdated;
    ULONG    ulSegsTimed;
    ULONG    ulSndByte;
    ULONG    ulSndControl;
    ULONG    ulSndPacket;
    ULONG    ulSndProbe;
    ULONG    ulSndRexmtByte;
    ULONG    ulSndAcks;
    ULONG    ulSndRexmtPacket;
    ULONG    ulSndTotal;
    ULONG    ulSndErr;   /* Added for dist_sock by likaikun00213099 */

    ULONG    ulSndRST;   /* Added for MIB-II */

    ULONG    ulSndUrgent;
    ULONG    ulSndWndUpdate;
    ULONG    ulTimeOutDrop;

    /* added by mayun to distinguish con_estab timer and keepalive timer */
    ULONG    ulKeepAliveTimeOut;  /*·�������ʱ����ʱ����*/
    ULONG    ulKeepAliveDrops;    /*����̽��ʧ�ܶ������Ӵ���*/

    /* TCP with MD5 authentication, zhangfeng, 2002,07,20 */
    ULONG    ulMd5Permit;
    ULONG    ulMd5Deny;
    ULONG    ulMd5Output;
    /* TCP with MD5 authentication, zhangfeng, 2002,07,20 */

    /* Added for tcp ha */
    ULONG ulSeqRcvNxtRevised; /* Times that seqRcvNxt has been revised */

    /* Added for notification failure */
    ULONG    ulNotifyReadFailed;
    ULONG    ulNotifyWriteFailed;
    ULONG    ulNotifyPeerCloseFailed;
    ULONG    ulNotifyKeepLiveDownFailed;
    ULONG    ulNotifyConnectFailed;

    /* Added by fengjing209023 cookieά�� */
    ULONG    ulCookieRcvdSyn;       /* cookie��ʱ�յ���SYN������ */
    ULONG    ulCookieRspdSynAck;    /* cookie��ʱ�ص�SYNACK������ */
    ULONG    ulCookieRcvdAck;       /* cookie��ʱ�յ���ACK������ */
    ULONG    ulCookiePassedAck;     /* cookie��ʱУ��ɹ���ACK������ */
    ULONG    ulCookieTimoAck;       /* cookie��ʱУ��ʧ�ܵ�ACK������(��ʱ) */
    ULONG    ulCookieBadMssAck;     /* cookie��ʱУ��ʧ�ܵ�ACK������(MSS��������) */
    ULONG    ulCookieOtherPkt;      /* cookie��ʱ����socket�յ����������� */
    ULONG    ulUsrCookieOnWhenTIMO; /* cookie��ʱ�յ���ACK���ĳ�ʱ�����ǲ�ƷCOOKIE���� */
    /* Add end */
    
    ULONG    ulRecvMemDrop;        /* �ڴ治�㶪���ı����� */
} TCPSTAT_S;

/* ����socket id,task id����Ԫ���ȡͳ����Ϣ����������ݽṹ */
typedef struct tagTCP4CONN_S
{
    ULONG    ulVrfIndex;    /* VRF����*/
    ULONG    ulLAddr;       /* ���˵�ַ(������) */
    ULONG    ulFAddr;       /* �Զ˵�ַ(������) */
    ULONG    ulLPort;       /* ���˶˿ں� */
    ULONG    ulFPort;       /* �Զ˶˿ں� */
    ULONG    ulSocketID ; /*��socket idָ��ʱ����socket����ͳ����Ϣ��*/
    /* ��������Ԫ�飬����ΪTCPDORP��INPCB����ɾ��������ڸ������ȻҪ��socketid��ȡ */
    ULONG    ulTaskID;      /* ����ID */
}TCP4CONN_S;

/* ����socket id task id ����Ԫ���TCPͳ�ƽṹ */
typedef struct tagTCP4PERSTAT
{
    TCP4CONN_S stTcp4Conn; /* ʵ�ʻ�ȡ��socket id task id ����Ԫ��*/    
    
    ULONG    ulAccepts;
    ULONG    ulConnAttempt;
    ULONG    ulConnDrops;
    ULONG    ulConnects;
    ULONG    ulDelayedAck;
    ULONG    ulDrops;
    ULONG    ulKeepDrops;
    ULONG    ulKeepProbe;
    ULONG    ulKeepTimeOut;
    ULONG    ulPAWSDrop;

    ULONG    ulPersistDrops;
    ULONG    ulPersistTimeOut;
    ULONG    ulPredictionAck;
    ULONG    ulPredictionData;
    ULONG    ulRcvAckByte;
    ULONG    ulRcvAckPacket;
    ULONG    ulRcvAckTooMuch;
    ULONG    ulRcvDupAck;
    ULONG    ulRcvAfterClose;
    ULONG    ulRcvByte;
    ULONG    ulRcvDupByte;
    ULONG    ulRcvDupPacket;
    ULONG    ulRcvPacketAfterWnd;
    ULONG    ulRcvByteAfterWnd;
    ULONG    ulRcvPartDupByte;
    ULONG    ulRcvPartDupPacket;
    ULONG    ulRcvOutOrderPacket;
    ULONG    ulRcvOutOrderByte;
    ULONG    ulRcvTotal;
    ULONG    ulRcvPacket;
    ULONG    ulRcvWndProbe;
    ULONG    ulRcvWndUpdate;
    ULONG    ulRexmtTimeOut;
    ULONG    ulRTTUpdated;
    ULONG    ulSegsTimed;
    ULONG    ulSndByte;
    ULONG    ulSndControl;
    ULONG    ulSndPacket;
    ULONG    ulSndProbe;
    ULONG    ulSndRexmtByte;
    ULONG    ulSndAcks;
    ULONG    ulSndRexmtPacket;
    ULONG    ulSndTotal;
    ULONG    ulSndErr;   /* Added for dist_sock by likaikun00213099 */

    ULONG    ulSndRST;   /* Added for MIB-II */
    ULONG    ulSndSYN;   /* Added for Qos Info */
    ULONG    ulSndFIN;   /* Added for Qos Info */

    ULONG    ulSndUrgent;
    ULONG    ulSndWndUpdate;
    ULONG    ulTimeOutDrop;

    ULONG    ulKeepAliveTimeOut;  /*·�������ʱ����ʱ����*/
    ULONG    ulKeepAliveDrops;    /*����̽��ʧ�ܶ������Ӵ���*/

    ULONG    ulMd5Permit;
    ULONG    ulMd5Deny;
    ULONG    ulMd5Output;

    /*socket ��������Ϣ*/
    ULONG    ulSndHiWat ; /*���ͻ�������ˮλ*/
    ULONG    ulRcvHiWat ; /*���ջ�������ˮλ*/
    ULONG    ulSndCC ; /*���ͻ�������ʵ������ */
    ULONG    ulRcbCC ; /*���ջ�������ʵ������ */

    ULONG    ulSubSOTimeODrops;      /* number of subsocket droped because of timeout */
    ULONG    ulSubSoBacklogDrops;    /* number of subsocket droped because of exceeding backlog */  
} TCP4PERSTAT_S;

typedef struct tagTcpSockInfo
{
    ULONG    ulLocalAddr;          /*���˵�ַ ����˳��*/
    ULONG    ulPeerAddr;           /*�Զ˵�ַ ����˳��*/
    USHORT   usLocalPort;          /*���˶˿ں� ����˳��*/
    USHORT   ulPeerPort;           /*�Զ˶˿ں� ����˳��*/

    ULONG    so_sOptions;            /*socketѡ��*/
    ULONG    so_sState;              /*tcp ״̬*/

    SHORT    so_sLinger;             /*Linger ֵ */
    SHORT    so_sQ0Len;         /* δ��������Ӹ���*/
    SHORT    so_sQLen;          /* �Ѿ����Ӹ��� */
    SHORT    so_sQLimit;        /* tcp ������Ӹ��� */

    ULONG    ulDelayedAck;        /*�ӳٷ��͵�ACK��������*/
    ULONG    ulRcvAckByte;        /*���յ��ֽ���*/
    ULONG    ulRcvAckPacket;      /*�յ���ACK��������*/
    ULONG    ulRcvAfterClose;     /*�رպ���յı��ĸ���*/    
    ULONG    ulRcvPacketAfterWnd; /*�������ڽ��մ�������*/
    ULONG    ulRcvPartDupPacket;  /*�����ظ���������*/
    ULONG    ulRcvOutOrderPacket; /*������������*/
    ULONG    ulRcvTotal;          /*�ܼ��յ�������*/
    ULONG    ulRcvPacket;         /*��˳�򵽴ﱨ������*/
    ULONG    ulRexmtTimeOut;      /*�ش���ʱ����ʱ����*/
    ULONG    ulSndByte;           /*���͵ı����ֽ���*/
    ULONG    ulSndPacket;         /*���͵����ݱ���*/
    ULONG    ulSndAcks;           /*����ACK������*/
    ULONG    ulSndRexmtPacket;    /*�����ط�����*/
} TCP_SOCK_INFO_S;



#define TCP_MAXFILTNUM      5

typedef struct tagTCPFILT
{
    ULONG   ulTaskId;        /* ����û����õĹ��������е�����ID   */
    ULONG   ulSockId;        /* ����û����õĹ��������е��׽ӿں� */
}TCPFILT_S;

typedef struct tagTCPDBUGFILTRD
{       
    TCPFILT_S stTCPDbugFilt[TCP_MAXFILTNUM];
    ULONG          ulFiltCnt;       /* ��ǰ���������ĸ��� */
}TCPDBUGFILTRD_S;


typedef ULONG   TCP_SEQ;

/* TCPͷ���ݽṹ */
typedef struct tagTCPHDR
{
    USHORT  usSrcPort;
    USHORT  usDstPort;
    TCP_SEQ                 seqSeqNumber;
    TCP_SEQ                 seqAckNumber;
#if VRP_LITTLE_ENDIAN == VRP_YES
    UCHAR   ucX2:4,
                    ucOffset:4;
#else
    UCHAR   ucOffset:4, /* warning:nonstandard extension used : bit field types other than LONG. */
                    ucX2:4;     /* warning:nonstandard extension used : bit field types other than LONG. */
#endif
    UCHAR   ucFlags;
    USHORT      usWnd;
    USHORT      usCheckSum;
    USHORT      usUrgentPoint;
} TCPHDR_S;

typedef struct tagTCPIP_TCPNETINFO_S
{
    ULONG   ulTaskId;       /* ����ID     */
    ULONG   ulSrcIp;        /* �����ֽ��� */
    ULONG   ulDstIp;        /* �����ֽ��� */
    USHORT  usSrcPort;
    USHORT  usDestPort;
    USHORT  usState;
    USHORT  usRes;
    /*Added by limin00188004, ��ȡ����״̬ʱ���socket���󶨵�VRF����, 2012/9/28   ���ⵥ��:S.VRF.02.01 */
    ULONG   ulVrfIndex;
    /* End of Added by limin00188004, 2012/9/28   ���ⵥ��:S.VRF.02.01 */
}TCPIP_TCPNETINFO_S;

/* COOKIE��Կ, 136���ֽڳ��� */  
typedef ULONG ( *gpfTCPIPGetCookieSecret)(ULONG* pulCookieValue, ULONG ulBytesNum); 

/* ��ȡ��ƷCOOKIE���ع��ӣ�����1��ʾ��Ʒ�򿪣�0��ʾ��Ʒ�ر�*/
typedef ULONG ( *gpfTCPIPGetUsrCookieSwitch)(ULONG* pulCookieSwitch);

/* Begin: Added by a00900892 for TCP MD5 Authentication notification */
/* Structure used as input parameter for hook function to notify TCP MD5
   configuration. */
typedef struct tagTCP4MD5CFGNOTIFY 
{
    ULONG ulTaskId;         /* vos task id */ 
    ULONG ulVrfIndex;       /* vrf index */ 
    ULONG ulSocketId;       /* socket id */ 
    ULONG ulLocalAddr;      /* The end of the address: host order */ 
    ULONG ulRemoteAddr;     /* Peer address: host order */ 
    USHORT usLocalPort;     /* local port: host order */ 
    USHORT usRemotePort;    /* peer port: host order */ 
    ULONG ulOper;           /* Add: 1 or Del: 0 */ 
} TCP4MD5CFGNOTIFY_S;
/* Structure used as input parameter for hook function to notify TCP MD5
   authentication result. */
typedef struct tagTCPMD5AUTHRESULT 
{
    ULONG ulTaskId;         /* vos task id */ 
    ULONG ulVrfIndex;       /* vrf index */ 
    ULONG ulSocketId;       /* socket id */ 
    ULONG ulLocalAddr;      /* The end of the address: host order */ 
    ULONG ulRemoteAddr;     /* Peer address: host order */ 
    USHORT usLocalPort;     /* local port: host order */ 
    USHORT usRemotePort;    /* peer port: host order */ 
    ULONG ulResult;         /* permit: 1 or deny: 0 */ 
} TCP4MD5AUTHRESULTNOTIFY_S; 
/* Function pointer to hold the pointer to hook function for notifying TCP MD5
   configuration. */
typedef ULONG ( *gpfTCPIPMd5CfgNotifyHook)(TCP4MD5CFGNOTIFY_S* pstCfgPara);
/* Function pointer to hold the pointer to hook function for notifying TCP MD5
   authentication result. */
typedef ULONG ( *gpfTCPIPMd5AuthNotifyHook)(TCP4MD5AUTHRESULTNOTIFY_S* pstAuthResult);
/* End: Added by a00900892 for TCP MD5 Authentication notification */

VOID TCPIP_ShowTcpStatistic(VOID);

VOID TCPIP_ShowTCPCB(VOID *pAddress);

VOID TCPIP_ShowTCP(VOID);

ULONG TCPIP_GetTCPStat(TCPSTAT_S *pstTCPStat);

VOID TCPIP_ClrTCPStat(VOID);

VOID TCPIP_NoDebugTCPAll(VOID);

VOID TCPIP_DebugTCPAll(VOID);

LONG TCPIP_SetTCPDbgFilter(ULONG ulFlag, ULONG ulDbgFilterId, ULONG ulTaskId, ULONG ulSockId);

ULONG TCPIP_SetTCPRespondQuench(ULONG ulSetYes);

VOID TCPIP_GetTCPParam(ULONG ulType, ULONG * pulValue);

ULONG TCPIP_SetTCPParam(ULONG ulType, ULONG ulValue);

VOID TCPIP_GetTCPDbgFilter(ULONG *pulDebugFlag, TCPDBUGFILTRD_S *pstPacketFilter, TCPDBUGFILTRD_S *pstEventFilter);

/*******************************************************************************
*    Func Name: TCPIP_GetTCPDbgFilterWithMd5
* Date Created: 2009-12-2
*       Author: zhangchunyu(62474)
*  Description: ��ȡTCP4 DEBUG��ʶ�͹������ֵ,����MD5������Ϣ
*        Input: ULONG *pulDebugFlag:����TCP Debug��ʶ
*               TCPDBUGFILTRD_S *pstPacketFilter:���ص�TCP���Ĺ���ֵ
*               TCPDBUGFILTRD_S *pstEventFilter:���ص�TCP״̬����ֵ
*               TCPDBUGFILTRD_S *pstMD5Filter:���������˵�MD5
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-12-2    zhangchunyu(62474)     Create the first version.
*
*******************************************************************************/
VOID TCPIP_GetTCPDbgFilterWithMd5(ULONG *pulDebugFlag, 
                                  TCPDBUGFILTRD_S *pstPacketFilter,
                                  TCPDBUGFILTRD_S *pstEventFilter,
                                  TCPDBUGFILTRD_S *pstMD5Filter);

typedef ULONG (*TCPINPUT_HOOK_FUNC)( MBUF_S* pMbuf );
ULONG TCPIP_RegFuncTCPInputHook( TCPINPUT_HOOK_FUNC pfFuncHook );
extern TCPINPUT_HOOK_FUNC g_TCP_Input_HookFunc;

#define TCP_NOT_PROCESSED_BY_INTERMEDIATE              0 
/* intermediate found the packet has Error, Stack will Destroy the Packet */
#define TCP_INTER_PROCESS_ERROR                        1
/* Intermediate Processing will continue processing and will own the packet
 * PP do not need to process the packet any more */
#define TCP_PROCESSED_BY_INTERMEDIATE                  2


extern ULONG TCPIP_GetPerTcp4ConnStats(TCP4CONN_S *pstConnInfo, TCP4PERSTAT_S *pstRetStats);


extern ULONG TCPIP_ResetPerTcp4ConnStats(TCP4CONN_S *pstConnInfo);


extern ULONG TCPIP_OpenTcpNetInfo(UINTPTR *pulWaitlist);


extern ULONG TCPIP_GetTcpNetInfo(UINTPTR ulWaitlist, TCPIP_TCPNETINFO_S *pstNetInfo);


extern ULONG TCPIP_CloseTcpNetInfo(UINTPTR ulWaitlist);

/*******************************************************************************
*    Func Name: TCPIP_GetTcpInfo
* Date Created: 2012-09-05
*       Author: wangtong207740
*  Description: 
*        Input: ULONG ulSocketId:
*               TCP_SOCK_INFO_S *pstTcpInfo:
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-09-05   wangtong207740          Create
*
*******************************************************************************/
ULONG TCPIP_GetTcpInfo(ULONG ulSocketId, TCP_SOCK_INFO_S *pstTcpInfo);


ULONG TCPIP_RegTcpCookieSecret(gpfTCPIPGetCookieSecret  pfGetCookieHook);

ULONG  TCPIP_RegGetUsrCookieSwitch(gpfTCPIPGetUsrCookieSwitch pfGetUserCookieSwitch);
/* Begin: Added by a00900892 for TCP MD5 Authentication notification */
/*******************************************************************************
*    Func Name: TCPIP_RegTcp4Md5CfgNotifyHook
* Date Created: 2014-7-17
*       Author: a00900892
*  Description: API to register a callback function to provide notification for TCP MD5 configurations
*        Input: pfCfgNotify: registered callback function 
*       Return: VOS_OK, VOS_ERR
*      Caution: If the input parameter pfCfgNotify is NULL, hook will be
*               unregistered.
*------------------------------------------------------------------------------
*  Modification History
*  DATE          NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-7-17   a00900892                Create
*
*******************************************************************************/
ULONG TCPIP_RegTcp4Md5CfgNotifyHook(gpfTCPIPMd5CfgNotifyHook pfCfgNotify);
/*******************************************************************************
*    Func Name: TCPIP_RegTcpMd5AuthNotifyHook
* Date Created: 2014-7-17
*       Author: a00900892
*  Description: API to register a callback function to provide notification for TCP MD5 Authentication results
*        Input: pfAuthNotify: registered callback function 
*       Return: VOS_OK, VOS_ERR
*      Caution: If the input parameter pfCfgNotify is NULL, hook will be
*               unregistered.
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-7-17   a00900892                Create
*
*******************************************************************************/
ULONG  TCPIP_RegTcp4Md5AuthNotifyHook(gpfTCPIPMd5AuthNotifyHook pfAuthNotify);
/* End: Added by a00900892 for TCP MD5 Authentication notification */
#ifdef    __cplusplus
}
#endif    /* end of __cplusplus */

#endif

