
#ifndef  _SOCK_COM_H
#define  _SOCK_COM_H

#ifdef   __cplusplus
extern   "C"{
#endif

#ifndef _UTLDLL_H_
#include "vos/vospubh/utldll.h"
#endif
#include "tcpip/ifnet/include/ifnet_api.h"
#ifndef _IF_IIFNET_INC_H_
#include "tcpip/ifnet/include/iifnet_inc.h"
#endif
#ifndef _IP6_PUB_H_
#include "ipv6/ppmng/core/include/ppmng_pub.h"
#endif

#include "tcpip/tcp4/include/tcp_api.h"
#include "tcpip/udp4/include/udp_api.h"
#include "tcpip/rawip4/include/rawip_api.h"
#include "common/ipos/ipv6/tcp6_public.h"
#include "vos/vospubh/utlsll.h"

struct tagPROTOSW;
struct tagTCB;

#ifndef TYPEDEF_TASK_T
#define TYPEDEF_TASK_T
typedef ULONG    task_t;
#endif

/* socket   state */
#define    SS_NOFDREF           0x001    /* û���κ��ļ���ο�  no file table ref any more */
#define    SS_ISCONNECTED       0x002    /* ��һ������������socket  socket connected to a peer */
#define    SS_ISCONNECTING      0x004    /* ������������ӵĹ�����  in process of connecting to peer */
#define    SS_ISDISCONNECTING   0x008    /* �ڶϿ����ӵĹ�����  in process of disconnecting */
#define    SS_CANTSENDMORE      0x010    /* �����ٷ��͸��������  can't send more data to peer */
#define    SS_CANTRCVMORE       0x020    /* �����ڽ��ո��������  can't receive more data from peer */
#define    SS_RCVATMARK         0x040    /* ��OOB���ݴ����ڽ��ջ������ʼλ�� */

#define    SS_PRIV              0x080    /* �㲥��Ȩ  privileged for broadcast, raw... */
#define    SS_NBIO              0x100    /* û������ѡ��  non-blocking ops */
#define    SS_ASYNC             0x200    /* �첽����/���֪ͨ  async i/o notify */
#define    SS_ISCONFIRMING      0x400    /* ����������������  deciding to accept connection req */
#define    SS_CONNECT           0x800

#define    SS_BLOCKING          0x1000    /* there is one task blocking on this socket*/
                                          /* used in global socket*/
#define    SS_RECALL            0x2000    /* set socket to call back */
#define    SS_SENDDATAIF        0X20000
#define    SS_WOULDWAKEUP       0X40000
#define    SS_ASYNWAKEUP        0x80000   /* asynsocket to wake up peerclose message */

#define    SS_BACK              0x4000    /* set socket to backup */ /* added by mayun for socket ha */

#define    SS_CHILDSOCK    0x8000     /* To indicate whether the socket is a child socket */

/*    sockbuf     state */
#define    SB_LOCK              0x01    /* lock on data queue */
#define    SB_WANT              0x02    /* someone is waiting to lock */
#define    SB_WAIT              0x04    /* someone is waiting for data/space */
#define    SB_SEL               0x08    /* someone is selecting */
#define    SB_ASYNC             0x10    /* ASYNC I/O, need signals */
#define    SB_NOTIFY            (SB_WAIT|SB_SEL|SB_ASYNC)
#define    SB_NOINTR            0x40    /* operations not interruptible */
#define    SB_SELOOB            0x80
#define    SB_LOCKWAIT          0x100
#define    SB_BLOCKING          0x1000   /* there has been a task blocking on this sb */

#define    SCM_RIGHTS           0x01

/* user close  state */
#define    SS_USERCLOSECALLED     0x01  /* �û��Ѿ����ù�CLOSE */
#define    SS_PEERCLOSENOTIFIED   0x02  /* SOCKET�Ѿ��ϱ���PEERCLOSE */
/* Add End */

/*************************************************************************/
/* Ϊ����Ϣ����ע���������Ӧ��                                          */
/*************************************************************************/
/*����ģ������*/
#define MODULE_SOCKET       "SOCKET"


/* �澯��Ϣ */
#define SOCK_DEBUG_GEN      1
#define SOCK_LOG_GEN        2
#define SOCK_TRAP_GEN       3

extern ULONG g_ulTcp_Syn_Use_Config_TOS;

typedef struct tagCMSGHDR
{
    SHORT        cmsg_nLen;     /* data byte count, including hdr */
    SHORT        cmsg_sLevel;   /* originating protocol */
    SHORT        cmsg_sType;    /* protocol-specific type */
    CHAR         cmsg_cData[2];
}CMSGHDR_S;
#define        L_CMSGHDR_S        sizeof(CMSGHDR_S)

#define    CMSG_DATA(cmsg)        ((UCHAR *)((cmsg) + 1))

typedef struct tagSELINFO
{
    task_t      si_tTaskId;   /* ����ȴ����Socket�Ľ���ID������selectʹ�ã�*/
    SHORT       si_sFlags;    /* ���ж������ѡ�и�SB�������־λ������ΪSI_COLL������selectʹ�ã�*/
    UCHAR       ucPadding[2];
}SELINFO_S;
#define        L_SELINFO_S        sizeof(SELINFO_S)


typedef struct tagSENDDATAIF
{
    ULONG           ulIfIndex;
    ULONG           ulSrcAddr;
}SENDDATAIF_S;
#define         L_SENDDATAIF_S  sizeof(SENDDATAIF_S)

/* added for setting keepalive time value and count by mayun 2001-07-19 */
typedef struct tagKEEPALIVESET
{
    USHORT usKeepintvl;       /* second */
    USHORT usKeepcount;       /* keepintvl's count */
}KEEPALIVESET_S;
#define         L_KEEPALIVE_S   sizeof(KEEPALIVESET_S)
/* end of mayun 2001-07-19 */

/*
 * added by mayun for socket muti_instance 2002-12-17
 */
typedef struct tagSENDBY_IF_NEXTHOP
{
    ULONG           ulOutIfIndex;
    ULONG           ulNextHopAddr;     /* must be net-order */
}SENDBY_IF_NEXTHOP_S;
#define         L_SENDBY_IF_NEXTHOP_S  sizeof(SENDBY_IF_NEXTHOP_S)
/* end of mayun */

#define         L_SNDBYDSTMAC_S  sizeof(SNDBYDSTMAC_S)
#define         MAXMACLEN        8
typedef struct tagSNDBYDSTMAC
{
    UCHAR           ucDstMac[MAXMACLEN];
    ULONG           ulMacLen;
}SNDBYDSTMAC_S;

typedef struct  tagASYNSOCKET
{
    ULONG           ulQueueID;
    ULONG           ulPointer;
    task_t          ulWakeTaskID;
}ASYNSOCKET_S;
#define L_ASYNSOCKET_S sizeof(struct tagASYNSOCKET)

typedef struct  tagRECALLSOCKET
{
    ULONG (*so_pfCallBack)( CHAR *, VOID *ulValue );
    CHAR  *pszDataBuf;
    ULONG ulBufLen;
    ULONG ulUserData;  /* the data user set and will be return at ulValue */
}RECALLSOCKET_S;

#define L_RECALLSOCKET_S sizeof(RECALLSOCKET_S)

typedef union tagAsyncsock_un
{
    ASYNSOCKET_S    so_unstAsynSocket; /* this is set by the application, to wakeup application */
    RECALLSOCKET_S  so_unstCallBack;
}ASYNSOCKINFO_UN;
#define L_SO_UNASYNSOCK sizeof(ASYNSOCKINFO_UN)


#define HC_SEND_SUCCESS     0              /*���ͳɹ�*/
#define HC_NEED_UPDATE      1              /*�����ײ���Ҫupdate*/
#define HC_NOT_SUPPORT      2              /*��֧��ʹ��Head Cache����*/
#define HC_SEND_FAIL        3              /*����ʧ��*/
#define HC_IR_SUCCESS       4              /* IR�����ͻ���״̬OK */

/* ָ��socket��ȡTCP/UDP/RAWIPͳ���ֶζ��� */
typedef union unPerSocketStat_U
{
    TCP4PERSTAT_S   stPerTCP4Stat;          /* ����socket id task id�� ��Ԫ��ͳ��TCP4 */
    UDP4PERSTAT_S   stPerUDP4Stat;          /* ����socket id task id�� ��Ԫ��ͳ��UDP4 */
    RAWIP4PERSTAT_S stPerRAWIP4Stat;        /* ����socket id task id�� ��Ԫ��ͳ��RAWIP4 */
    TCP6PERCONNSTAT_S stPerTCP6Stat;        /* ����socket id task id�� ��Ԫ��ͳ��TCP6 */
}PERSOCKETSTAT_U;

/*struct tagPROTOSW;*/ /* by zhangyilong 27499 �ظ�������ȥ�� */
typedef struct tagSOCKET
{
    SHORT               so_sType;           /* generic type, see socket.h */
    SHORT               so_sLinger;         /* time to linger while closing */
    ULONG               so_sOptions;        /* from socket call, see socket.h
                                             changed by yuyong&mayun 2002/10/30 for address overlap*/
    ULONG               so_sState;          /* internal state flags SS_*, below */
    VOID                (*so_pfSignal)();
    CHAR                *so_pPcb;           /* protocol control block */
    struct tagPROTOSW   *so_pProto;         /* protocol handle */
    struct tagSOCKET    *so_pHead;          /* back pointer to accept socket */
    struct tagSOCKET    *so_pQ0;            /* queue of partial connections */
    struct tagSOCKET    *so_pQ;             /* queue of incoming connections */
    SHORT               so_sQ0Len;          /* partials on so_q0 */
    SHORT               so_sQLen;           /* number of connections on so_q */
    SHORT               so_sQLimit;         /* max number queued connections */
    SHORT               so_sTimeO;          /* connection timeout */
    SHORT               so_sError;          /* error affecting connection */
    UCHAR               ucUsrCloseFlag;     /* 1����������û��Ƿ����CLOSE,2����������Ƿ��ϱ���PEERCLOSE */
    /* Addend end */
    UCHAR               ucPadding_1[1];
    task_t              so_tTaskId;         /* pgid for signals */
    ULONG               so_ulOobMark;       /* chars to oob mark */
    
    /* Added for setting keepidle time value by likaikun 2014-01-13 */
    ULONG               ulKeepIdle;
    /* End of likaikun */
    
    /* added for setting keepalive time value and count by mayun 2001-07-19 */
    KEEPALIVESET_S      so_stKeepalive;
    /* end of mayun */

    SENDDATAIF_S        so_stSendDataIf;
    /*
     * added by mayun for socket muti_instance 2002-12-17
     */
    SENDBY_IF_NEXTHOP_S so_stSendby_If_NextHop;

    SNDBYDSTMAC_S       so_stSndbyDstMac;

    ULONG               ulSrcAddr;      /* �����ֽ��� */

    struct tagSOCKBUF
    {
        LONG        sb_ulCC;        /* actual chars in buffer */
        LONG        sb_ulHiWat;     /* max actual CHAR count */

        LONG        sb_ulLoWat;     /* low water mark */
        MBUF_S      *sb_pMb;        /* the mbuf chain */

        /*One mbuf pointer added by zhangfeng for D14729, 2002,04,19*/
        MBUF_S      *sb_pLastMbuf;  /*refer to the mbuf node next to never*/
        /*End of addition to improve search efficiency, 2002,04,19*/

        SELINFO_S   sb_stSel;       /* process selecting read/write */
        SHORT       sb_sFlags;      /* flags, see below */
        SHORT       sb_sTimeO;      /* timeout for read/write */
        ULONG       sb_ulIfIndex;   /* contain the ifnet inext of the latest sended or received datagram */
        /* we set read , connect, accept sleep in so_stRcv.sb_tTaskId,
        * and write,close in so_stSnd.sb_tTaskId */
        task_t      sb_tTaskId;     /* the task who sleep to read,write,connect,accept */

        /* Added for SOCKET HA */
        ULONG       sb_ulAddOrSubLen;     /* Save the length to be added or subtract from the socket buffer by ha */
        UCHAR       sb_ucIsInBackupQueue; /* Indicate whether this socket buf is backup queue */
        UCHAR       ucPadding_1[3];
    } so_stRcv, so_stSnd;

    SHORT so_sRefCnt;   /* the number of tasks to share this socket */
    UCHAR ucPadding_2[2];

    /* added for mpls vpn */
    ULONG           ulVrfIndex;
    ULONG           ulVrfIndex_Rcvd;

    /* mayun for zoneid */
    ULONG           ulZoneId;

    ASYNSOCKINFO_UN so_unAsynSock;

    LONG             so_iFd;            /* the file descriptor of this socket */
    struct tagTCB   *so_pTcb;           /* the tcb which this socket socket is in
                                         It is to falloc a fd in SO_IsConnected() for new socket(which is create by SO_NewConn ) */
#define so_stAsynSocket    so_unAsynSock.so_unstAsynSocket
#define so_stCallBack      so_unAsynSock.so_unstCallBack

    /* add for Socketdebug ,only use in UDP or RawIP for full drop .mayun. */
    ULONG so_ulDropPackets;

    /*��IPV4 UDP, RAW IP���ͱ���ʱ����Ŀ�ĵ�ַ�������ظ�����mbuf����*/
    VOID *so_pAddr;

    VOID *pstHeadCacheInfo;/*ָ��Head Cache����Ϣ�ṹ*/
    struct tagSOCKET *pstHeadCacheSocketNext;/*ָ����һ��ʹ��Head Cache��socket*/

    /* Added for SOCKET HA */
    ULONG so_ulBackupTimeStamp; /* Indicate the time when socket chain's backup msg of this
                                 * socket is put into socket backup queue.
                                 */
    UCHAR so_ucIsInBackupQueue; /* Indicate whether backup msg of socket modification
                                 * or socket chain is in socket backup queue
                                 */
    UCHAR ucPadding;        /* �����ֶ�,δʹ�� */
    /* Added by y171195(z171897) 2010-11-03 for DHCP Vlan Scanning Begin */
    USHORT usRcvVlanInfo;   /* ����vlan tag��Ϣ,������ */
    /* Added by y171195(z171897) 2010-11-03 for DHCP Vlan Scanning End */

    SENDDATAIF_S so_stTrrtOutIfIndex;    /*trrt����ʱָ���ĳ��ӿ�*/

    PERSOCKETSTAT_U unSocketStat;        /* ָ��socket��ȡTCP/UDP/RAWIPͳ���ֶ� */
}SOCKET_S;
#define L_SOCKET_S        sizeof(SOCKET_S)

typedef struct tagSOCKBUF     SOCKBUF_S;
#define L_SOCKBUF_S       sizeof(SOCKBUF_S)



typedef struct tagFILEOPS
{
    LONG   (*fo_pfRead)();
    LONG   (*fo_pfWrite)();
    LONG   (*fo_pfIoctl)();
    LONG   (*fo_pfSelect)();
    LONG   (*fo_pfClose)();
}FILEOPS_S;
#define        L_FILEOPS_S        sizeof(FILEOPS_S)

typedef struct tagFILE
{
    UCHAR    f_ucState;
    UCHAR    f_ucFlags;
    UCHAR    f_ucType;
    UCHAR    ucPadding;
    FILEOPS_S    *f_pOps;
    SOCKET_S    *f_pData;
}FILE_S;
#define        L_FILE_S    sizeof(FILE_S)

/*task control block*/
typedef struct tagTCB
{
    struct tagTCB   *tcb_pNext;
    task_t           tcb_tTaskId;    /* the task prossess this tcb */
    FILE_S          *tcb_pFile;     /* the files in this tcb */
    LONG            tcb_sMinVldIdx; /* the minimum valid file index */
                                    /* every time, we use the minimum valid
                                     *file index in this tcb, to optimize the
                                     *select function */
    LONG            tcb_sFileNum;   /* the number of files in tcb_pFile */
    LONG            tcp_sBusyFileNum;
    /*Begin BC3D01829 liangjicheng 2009-08-04*/
    LONG            tcb_usMaxSockId;
    /*End BC3D01829 liangjicheng 2009-08-04*/
}TCB_S;
#define L_TCB_S        sizeof(TCB_S)

/* Head Cache���ṹ*/

typedef struct tag_HeadCache
{
    DLL_NODE_S stHeadCacheNodeLink;   /* Head Cache���˳������*/
    DLL_NODE_S stHeadCacheHashLink;   /* hash��ͻ�������*/
    SOCKET_S   *pSocket;              /* ָ����Ӧ��socket�ṹ*/
    ULONG      ulFlag;                /* Head Cache��־������Head Cache��״̬�������������ĺ궨��*/
    ULONG      ulSrcIP;               /* Դ��ַ*/
    ULONG      ulDstIp;               /* Ŀ�ĵ�ַ*/
    IN6ADDR_S  stSrcIP6;              /* IPv6 Դ��ַ   */
    IN6ADDR_S  stDstIP6;              /* IPv6 Ŀ�ĵ�ַ */
    ULONG      ulIpPro;               /* Э���*/
    ULONG      ulIfIndex;             /* ���ӿ�����*/
    ULONG      ulNextHop;             /* ��һ���ĵ�ַ*/
    IN6ADDR_S stNextHop6;             /* IPv6 ��һ����ַ */
    USHORT     usSrcPort;             /* ���ض˿ں�*/
    USHORT     usDstPort;             /* Զ�˶˿ں�*/
    UCHAR      *pucBlock;             /* ָ������ı����ײ��ڴ�*/
    UCHAR      *pucHead;              /* �����ײ���(UDP�ײ�)+IP�ײ�+��·���ײ�*/
    ULONG      ulHeadLen;             /* �����ײ�����*/
    ULONG      ulNormalSendTotal;     /* ͳ�����������̱����� */
    ULONG      ulHCSendTotal;         /* ͳ�������ͳɹ��������������������̱�������*/
} HEADCACHE_ENTRY_S;

/* ������ͷ��󳤶� */
#define HC_MAX_HDR   64
/*���¶���Ϊ����VISP�ڲ�Դ�ļ�ͬʱ����sock_pub.h��tcpip_sock.h���ֳ�ͻ���ض���*/
/* Ϊ�˽�����������Ŀ����ļ�ʱ���˽ṹ���ͻ������һ�������:VISP_TEST
   Ĭ������²�����˱���꣬�Բ�Ʒ������Ӱ�� */
#ifndef VISP_TEST
typedef struct tagTCPIP_HEADCACHE_ENTRY
{
    ULONG      ulFlag;                /* Head Cache��־������Head Cache��״̬�������������ĺ궨��*/
    ULONG      ulSrcIP;               /* Դ��ַ*/
    ULONG      ulDstIp;               /* Ŀ�ĵ�ַ*/
    IN6ADDR_S  stSrcIP6;              /* IPv6 Դ��ַ   */
    IN6ADDR_S  stDstIP6;              /* IPv6 Ŀ�ĵ�ַ */
    ULONG      ulIpPro;               /* Э���*/
    ULONG      ulIfIndex;             /* ���ӿ�����*/
    ULONG      ulNextHop;             /* ��һ���ĵ�ַ*/
    IN6ADDR_S stNextHop6;             /* IPv6 ��һ����ַ */
    USHORT     usSrcPort;             /* ���ض˿ں�*/
    USHORT     usDstPort;             /* Զ�˶˿ں�*/
    UCHAR      aucHead[HC_MAX_HDR];   /* �����ײ���(UDP�ײ�)+IP�ײ�+��·���ײ�*/
    ULONG      ulHeadLen;             /* �����ײ�����*/
    ULONG      ulNormalSendTotal;     /* ͳ�����������̱����� */
    ULONG      ulHCSendTotal;         /* ͳ�������ͳɹ��������������������̱�������*/
}TCPIP_HEADCACHE_ENTRY_S;
#endif
typedef ULONG (*HEADCACHE_VLANCHECK_HOOK_FUNC)(IFNET_S *pIf);


typedef struct tagIP_SOCK_SH_CALLBACUP_SET_S
{
    VOID (*pfDebugToIC) ( ULONG ulInfoID, CHAR *szString );
    ULONG (*pfVOS_Que_Create)(CHAR *pQueName,ULONG ulQueDepth,ULONG ulFlags,ULONG *pulRetQueID);
    ULONG (*pfVOS_Que_GetName)(ULONG ulQueID, CHAR *pQueName);
    ULONG (*pfVOS_Que_Write)(ULONG ulQueID,UINTPTR *ulMsg,ULONG ulFlag, ULONG ulTimeOutInmillsec);
    ULONG (*pfVOS_Que_Read)(ULONG ulQueID,UINTPTR *ulRetMsg,ULONG ulFlag, ULONG ulTimeOutInmillsec);
    ULONG (*pfSOCK_SH_Que_GetMsgNum)(ULONG ulQueID, ULONG *pulRetMsgNum);
    ULONG (*pfSOCK_SH_Que_GetMaxNum)(ULONG ulQueID, ULONG *pulRetMaxNum);
    ULONG (*pfVOS_Ev_Write)(ULONG ulTaskID,ULONG ulEvents);
    ULONG (*pfVOS_Ev_Read)(ULONG ulEvents, ULONG *pulRetEvents,ULONG ulFlags, ULONG ulTimeOutInmillsec);
    ULONG (*pfGetHostName)(CHAR* pchName, LONG iLen);
}IP_SOCK_SH_CALLBACUP_SET_S;

typedef struct tagSOCK_MOD_INFO_S
{
    ULONG ulModID;
    ULONG ulSubModID;
    ULONG ulSKT_MAX_SOCK_N;
    ULONG ulHC_ENTRY_MAINTYPE;
    ULONG ulSKT_GLOBAL_SOCKET_EN;
    ULONG ulHC_IR_Enable_flag;
}SOCK_MOD_INFO_S;

typedef struct tagNewFreePort
{
    SLL_NODE_S stNode;      /* ȫ������ڵ� */
    USHORT     usPort;      /* ģ��ID */
    USHORT     usReserve;   /* ���� */
}NEW_FREE_PORT_S;

VOID SOCK_Init_RecentlyFreePortList();
ULONG SOCK_Add_NewFreePort(USHORT usPort);
ULONG SOCK_Search_FreePort(USHORT usPort, ULONG ulDelFlag);

extern SLL_S g_sllRecentlyFreePortList;
extern ULONG g_ulRandomPortEnhance;
extern USHORT g_usRandomPortStart;
#ifdef    __cplusplus
}
#endif    /* end of __cplusplus */

#endif
