

#ifndef _PPP_CORE_DEF_H_
#define _PPP_CORE_DEF_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "ppp/include/ppp_api.h"

/*��ַ������,��socket.h�ṩ����ʱ*/
#ifndef AF_INET
#define AF_INET         2               /* internetwork: UDP, TCP, etc. */
#endif

#ifndef AF_INET6
#define AF_INET6        29
#endif
#ifndef AF_IPX
#define AF_IPX          23              /* Novell����Э�� Novell Internet Protocol */
#endif


#ifndef MIN
#define MIN(a, b)       ((a)>(b) ? (b):(a)) 
#endif

/* ��ɢ�궨�� *******************************************************************/
#define TCPIP_PPP_FAC 0

#define PPP_DEBUGSWITCH_ERROR 0xFF

#define PPP_DEF_MAX_CTLNUM 64
#define RTM_CREATE      0x01    /* �ӿڡ�����·����*/
#define RTM_DEL         0x02    /* �ӿڡ�����·ɾ��*/
#define MIB_MAC_LEN 6
#define IFTABLE 1

#define PPP_MAX_NEG_TIME 600            /*�û�ָ��������Э��ʱ��*/
#define PPP_TIMEINIT     (ULONG)~0x0    /* 0xFFFFFFFF,ppp���ƿ��ϼ�ʱ��ʼֵ(��Ч) */
#define PPP_TIMEDONE     (ULONG)~0x1    /* 0xFFFFFFFE,ppp���ƿ��ϼ�ʱΪPPP_TIMEDONE,��ʾ�Ѿ�����澯���� */
#define PPP_INVALID_STATE 0xFFFFFFFF  /* ppp���ƿ�Э����Ч״̬ */
#define PPP_MUXCP_DISABLE   0xFF       /* pppMuxδʹ��Э��״ֵ̬*/
/*******************************************************************************/


/************************* �����йصĺ� (Begin)*****************************/

#define PPP_MAXAUTHFAILTIMES        3

#define PPP_MAXTRANSFAILEDTIMES     5
#define PPP_DEF_MP_FRAGS            4
#define PPP_DEF_MP_BINDS            4

#define PPP_GETCOUNTPERTIME 200   /* һ�ε�����ദ��ı����� */

#define PPP_QUE_REGLEN      1024    /*  ���е�ȱʡע�᳤��  shiyong 2000/10/10  */
#define PPP_MAXQUELEN       1024

#define PPP_ECHOTIMEOUT     10000    /* 10000����   ten seconds in milliseconds */
#define PPP_ECHOSENDTIME    PPP_ECHOTIMEOUT  /* same as echo timeout */

#define PPP_MAXMRU          2000    /* maximum MRU */

#define PPP_DEFMRU          1500    /*ȱʡMRU default MRU */

#define PPP_MINMRU          46      /* minimum MRU */

#define PPP_DEFTIMEOUTTIME  3000L   /* Timeout time in milliseconds */
#define PPP_MAXTIMEOUTTIME  10000L  /* Timeout time in milliseconds */

#define PPP_DEFMAXCONFREQS  5       /* ����CR�����ش�����    Maximum Configure-Request transmissions */

#define PPP_MAXTERMREQS     5       /* ����TR�����ش�����   Maximum Terminate-Request transmissions */
#define PPP_MAXNAKLOOPS     10      /* NAK����������  Maximum number of nak loops */
#define PPP_MAXLOOPSBACK    10      /* ��󻷻ؼ����� Maximum number of loopsback */


#define PPP_MINLOOPSBACK    3       /* ��С���ؼ����� */


#define PPP_AUTH_MAXTRANSMITS  10   /* PAP&&CHAP ��֤����ش����� */

#define PPP_DEF_RESETTIME   30000L

#define PPP_DEFMRRU  1500
#define PPP_MINMRRU  128            /* ��С�����MRRUֵ  No MRUs below this is allowed */


/*����û���*/
#define MP_MAX_USER_NUM        200
#define MAX_HOT_SLOT_USER_NUM  20   /* �Ȳ�ε�����·��û���Ŀ */
/*�û�������*/
#define MP_USERNAME_LEN        PPP_MAXUSERNAMELEN

#define NOAUTH_NODISCR         1    /* ֱ�Ӱ� */
#define DISCR_NOAUTH           2    /* �ն��������� */
#define NODISCR_AUTH           3    /* �û����� */
#define DISCR_AUTH             4    /* �ն����������û����� */

/* Added for HUAWEI-MP-MIB, 2004/06/08 */
#define MPGROUP_BIND            0
#define NOBIND_MP               5
/*������ָ������ͨ��*/
#define NOSUCHSUBCHANNEL        0

#define PPP_DEFAULT_ACCM  0xffffffff  /* ȱʡͬ�첽ת���ַ��������п����ֶ�ת�� */

#define MP_SSNHF_ENABLE              1  /* ʹ��Э��SSNHFѡ�� */
#define MP_SSNHF_DISNABLE            0  /* ȥʹ��Э��SSNHFѡ�� */
#define MC_MHF_ENABLE                1  /* ʹ��Э��MHFѡ�� */
#define MC_MHF_DISNABLE              0  /* ȥʹ��Э��MHFѡ�� */
#define MC_PREFIX_ELISION_ENABLE     1  /* ʹ��Э��Prefix-Elisionѡ�� */
#define MC_PREFIX_ELISION_DISNABLE   0  /* ȥʹ��Э��Prefix-Elisionѡ�� */
#define PREFIX_E_IS_USED             1  /* �õȼ�����ǰ׺ʡ��ӳ���ϵ */
#define PREFIX_E_NO_USED             0  /* �õȼ�������ǰ׺ʡ��ӳ���ϵ */

#define MC_MAX_LSCLASS              16  /* ������ͷ��ʽ֧�ֵ����ȼ��� */
#define MC_DEF_LSCLASS               8  /* ������ͷ��ʽĬ��֧�ֵĵȼ��� */
#define MC_MAX_SSCLASS               4  /* ������ͷ��ʽ֧�ֵ����ȼ��� */
#define MC_LSN_CODE                  2  /* �����и�ʽ��codeֵ */
#define MC_SSN_CODE                  6  /* ������ͷ��ʽ��codeֵ */
#define MC_PREFIXE_MAX_STR           8  /* ǰ׺ʡ���ֶε���󳤶� */
/* End of added */

/*Begin BC3D01936 ͬ��BC3D01705 liangjicheng 2009-08-24*/
/* ��Դ�˲�ʱ��һ�μ������ӿ������û�����ʱ���ܳ�������� */
#define PPP_MAX_VERIFY_IFNUM    128
/*End BC3D01936*/

/************************* �����йصĺ� (End)*****************************/


/************************* �����ù�������Ĭ��ֵ (Begin)*************************/

#define PPP_DEF_NEED_PAP      0x0   /* ȱʡ: ����ҪPAP��֤ */

#define PPP_DEF_NEED_CHAP     0x0   /* ȱʡ: ����ҪCHAP��֤ */

#define PPP_DEF_NEED_LOOPNEGO  0x1   /* ȱʡ: ����Э��*/

/* Liqiang17164  ʵ��CDMA BSC��Ʒ���� 2003-10-25 */
#define PPP_DEF_NEED_NCP       0x1   /* ȱʡ: ����NCPЭ��*/

/* Liqiang ʵ�����ܹ�����Ʒ���� 2003-12-17 */
#define PPP_DEF_NEED_LCP       0x1   /* ȱʡ: ����LCPЭ��*/
#define PPP_DEF_NEED_OSICP     0x1   /* �Ƿ�Э��OSICPֱ���ϱ�UP��Ĭ��Ϊ1��Э�� */
/* ע��: ���LCPЭ�̲�ͨ��, �Ҳ��ϳ���PPP_STATE_REQSENT, ������Timeoutʱ�� *
 *       ϣ���Ժ����ʵ����Э�̹�����������ֳ�ʱ, ���´��Զ����ڳ�ʱʱ��  */
#define PPP_DEF_NEGO_TIMEOUT  6000L  /* ȱʡ: ȱʡTimeoutʱ��(6��) */
#define PPP_MAX_NEGO_TIMEOUT  30000L /* ���Timeoutʱ��(30��) */

#define PPP_DEF_ECHO_TIMEOUT  10000L /* ȱʡ: ȱʡEcho��ʱʱ��(10��) */
#define PPP_DEF_ECHO_SENDTIME PPP_DEF_ECHO_TIMEOUT /* ��Echo��ʱʱ����ͬ */
#define PPP_DEFAULT_KEEPALIVE PPP_DEF_ECHO_TIMEOUT /* ��·��Э���ú���·��̽����·״̬�� */

#define PPP_DEF_CONFREQS      5     /* ȱʡ: 5��  */
#define PPP_MAX_CONFREQS      10    /* ���: 10�� */

#define PPP_DEF_NAKLOOPS      10
#define PPP_MAX_NAKLOOPS      10
#define PPP_MAX_LOOPSBACK     10    /* Maximum number of nak loops */

/*�Ƿ񴴽�PPP�첽���Ķ��У�ȱʡΪ������*/
#define PPP_NEED_ASYQUE    1
#define PPP_NO_ASYQUE      0

/* �Ƿ�Э�������Э�飬Ĭ�϶�Э�� */
#define PPP_NEGO_NPROTO_ALL   0xFFFFFFFF
#define PPP_NEGO_NPROTO_IPCP  0x1
#define PPP_NEGO_NPROTO_OSICP 0x2

/************************* �����ù�������Ĭ��ֵ (End)*************************/


/************************* �¼�ö�ٱ��� (Begin)*****************************/

/* ������ں˱��¼� */
enum enumPPP_EVENT_ShellToCore
{
    PPPISLUP = 0,
    PPPISLDOWN,
    PPPCHGIPADDR,
    PPPADDIPADDR,
    PPPDELIPADDR,
    PPPADDIP6LINKLOCALADDR,  /*����LINKLOCAL��ַ*/
    PPPDELIP6LINKLOCALADDR,  /*ɾ��LINKLOCAL��ַ*/
    PPPCHGIPXADDR,
    PPPADDIPXADDR,
    PPPDELIPXADDR,
    PPPADDIPISIS,
    PPPDELIPISIS,

    PPPISDOWNALL,
    PPPENABLEPPPMUX,  /*ʹ��PPP MUX*/
    PPPDISABLEPPPMUX, /*ȥʹ��PPP MUX*/
    /* End of addition */

    PPPDELIPADDFORINVALID,

    PPPMAX_END
};

/* ״̬���¼� */
enum enumPPP_EVENT_FSM
{
    /* �ⲿ�¼� */
    PPP_EVENT_FSM_UP = 0,
    PPP_EVENT_FSM_DOWN,
    PPP_EVENT_FSM_OPEN,
    PPP_EVENT_FSM_CLOSE,
    /* ��ʱ���¼� */
    PPP_EVENT_FSM_TO_PLUS,
    PPP_EVENT_FSM_TO_SUB,
    /* �����¼� */
    PPP_EVENT_FSM_RCR_PLUS,
    PPP_EVENT_FSM_RCR_SUB,
    PPP_EVENT_FSM_RCA,
    PPP_EVENT_FSM_RCN,
    PPP_EVENT_FSM_RTR,
    PPP_EVENT_FSM_RTA,
    PPP_EVENT_FSM_RUC,
    PPP_EVENT_FSM_RXJ_PLUS,
    PPP_EVENT_FSM_RXJ_SUB,
    PPP_EVENT_FSM_RXR
};

enum emumPPP_ACTION_FSM
{
    PPP_ACTION_FSM_TLU = 1,
    PPP_ACTION_FSM_TLD,
    PPP_ACTION_FSM_TLS,
    PPP_ACTION_FSM_TLF,
    PPP_ACTION_FSM_IRC,
    PPP_ACTION_FSM_ZRC,
    PPP_ACTION_FSM_SCR,
    PPP_ACTION_FSM_SCA_SCN,
    PPP_ACTION_FSM_STR,
    PPP_ACTION_FSM_STA,
    PPP_ACTION_FSM_SCJ,
    PPP_ACTION_FSM_SER,
    PPP_ACTION_FSM_SDR,
    PPP_ACTION_FSM_MAX,
};

/* Э�����ں˱����¼� */
enum enumPPP_EVENT_ProtocolToCore
{
    PPP_EVENT_LCPUP = 0,
    PPP_EVENT_LCPDOWN,
    PPP_EVENT_LCPFINISHED,
    PPP_EVENT_LCPSTARTING,
    PPP_EVENT_IPCPUP,
    PPP_EVENT_IPCPDOWN,
    PPP_EVENT_IPCPFINISHED,
    PPP_EVENT_IPCPSTARTING,

    PPP_EVENT_IPXCPUP,
    PPP_EVENT_IPXCPDOWN,
    PPP_EVENT_IPXCPFINISHED,
    PPP_EVENT_IPXCPSTARTING,

    PPP_EVENT_CCPUP,
    PPP_EVENT_CCPDOWN ,
    PPP_EVENT_CCPFINISHED,
    PPP_EVENT_CCPSTARTING,
    PPP_EVENT_PAPSUCCESS,
    PPP_EVENT_PAPFAILED,
    PPP_EVENT_CHAPSUCCESS,
    PPP_EVENT_CHAPFAILED,
    PPP_EVENT_RECHALLENGE,
    PPP_EVENT_OSICPUP,
    PPP_EVENT_OSICPDOWN,
    PPP_EVENT_OSICPFINISHED,
    PPP_EVENT_OSICPSTARTING,
    PPP_EVENT_MPLSCPUP,
    PPP_EVENT_MPLSCPDOWN,
    PPP_EVENT_MPLSCPFINISHED,
    PPP_EVENT_MPLSCPSTARTING,

    PPP_EVENT_IP6CPUP,
    PPP_EVENT_IP6CPDOWN,
    PPP_EVENT_IP6CPFINISHED,
    PPP_EVENT_IP6CPSTARTING,
    PPP_EVENT_IP6CP_SET_INTERFACE_ID,

    PPP_EVENT_MUXCPUP ,
    PPP_EVENT_MUXCPDOWN ,
    PPP_EVENT_MUXCPFINISHED ,
    PPP_EVENT_MUXCPSTARTING ,
    /* End of addition */

    PPP_EVENT_MAXEVENT
};

/* �ں�����Ǳ����¼� */
enum enumPPP_EVENT_CoreToShell
{
    /* ֧��np xiehuaguo add for support np 2006-05-08 */
    PPP_LCP_UP = 0,
    PPP_LCP_DOWN ,
    PPP_IPCP_UP,
    PPP_IPCP_DOWN,

    PPP_IP6CP_UP,
    PPP_IP6CP_DOWN,
    PPP_IP6CP_GET_LINKLOCAL_ADDR,
    PPP_IP6CP_SET_INTERFACEID,

    PPP_GET_IPADDR,
    PPP_GET_PEERIPADDR,
    PPP_FREE_PEERIPADDR,
    PPP_IPXCP_UP,
    PPP_IPXCP_DOWN,
    PPP_GET_IPXADDR,
    PPP_SET_ACCM,
    PPP_OSICP_UP,
    PPP_OSICP_DOWN,
    PPP_OSICP_ENABLE

    ,PPP_MUXCP_UP,
    PPP_MUXCP_DOWN
    /* End of addition */
};

/* PPP RPC ͨ����Ϣ */
enum enumPPP_IPC_MSG
{
   PPP_HOT_INSERT_SLOT ,
   PPP_HOT_INSERT_POINTER
};

/************************* �¼�ö�ٱ��� (End)*****************************/


/* ������Ϣ�����,�Ժ�Ӧ�滻�� */
#define PPP_LOG_INFO    0
#define PPP_LOG_WARNING 1
#define PPP_LOG_NOTICE  2
#define PPP_LOG_ERROR   3


/**************************** PPP�׶� *********************************/
enum enumPppPhase
{
    PPP_PHASE_DEAD = 0,       /* 0  ��·�����ý׶�   Dead Phase */
    PPP_PHASE_ESTABLISH,      /* 1  ��·�����׶�     Establish Phase */
    PPP_PHASE_AUTHENTICATE,   /* 2  ��֤�׶�         Authenticate Phase */
    PPP_PHASE_CBCP,           /* 3                   Cbcp Phase */
    PPP_PHASE_NETWORK,        /* 4  �����Э��׶�   Network Phase */
    PPP_PHASE_TERMINATE       /* 5  ��·��ֹ�׶�     Terminate Phase */
};

/**************************** PPP�׶� *********************************/
enum ePppPhase
{
    PPP_DEAD_PHASE = 1,       /* 1  ��·�����ý׶�    Dead Phase */
    PPP_ESTABLISH_PHASE,      /* 2  ��·�����׶�      Establish Phase */
    PPP_AUTHENTICATE_PHASE,   /* 3  ��֤�׶�          Authenticate Phase */
    PPP_CBCP_PHASE,           /* 4                    Cbcp Phase */
    PPP_NETWORK_PHASE,        /* 5  �����Э��׶�    Network Phase */
    PPP_TERMINATE_PHASE       /* 6  ��·��ֹ�׶�      Terminate Phase */
};

/* PPPЭ������  PPP Nego Type */
enum ePppNegoType
{
    PPP_NEGO_LCP = 1,    /* 1  PPP��·����Э��   PPP LCP Negotiation */
    PPP_NEGO_NCP         /* 2  PPP�������Э��   PPP IPCP Negotiation */
};


/********************** PPP���ĸ����ֳ��� *****************************/
#define FSM_HDRLEN  4     /* Э���ֽ��� octets for every protocol, code+ID+length*/
#define PPP_HDRLEN  4     /* ��׼pppͷ�ֽ��� octets for standard ppp header ff+03+protocol*/
#define PPP_FCSLEN  2     /* FCS�ֽ��� octets for FCS */

#define PPP_HDRLEN_MIN 1  /* ��СPPP�ײ����� */
/*
|--------- PPP_HDRLEN ----------|--------- FSM_HDRLEN ----------|
0       1       2       3       4       5       6       7       8
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|   ff  |   03  |    protocol   |  code |   ID  |     length    |  data...
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
*/

/* ��Э��ͨ�õ�Э��ѡ��� */
#define PPP_CILEN_VOID      2   /* PPP ci type + ci length */
#define PPP_CILEN_SHORT     4   /* PPP_CILEN_VOID + sizeof(short) */
#define PPP_CILEN_LONG      6   /* PPP_CILEN_VOID + sizeof(long) */

/* ��Э��ͨ�õĻ�ȡЭ��ѡ���(cilen)�� */
#define PPP_LENCIVOID(neg)      (neg ? PPP_CILEN_VOID : 0)
#define PPP_LENCISHORT(neg)     (neg ? PPP_CILEN_SHORT : 0)
#define PPP_LENCILONG(neg)      (neg ? PPP_CILEN_LONG : 0)
/********************** PPP���ĸ����ֳ��� *****************************/


/************************ IPCPģ�� *****************************/
/* ��Э��ѡ��� */
#define PPP_CILEN_COMPRESS  4   /* ѹ��Э��ѡ����С����  min length for compression protocol opt. */
#define PPP_CILEN_VJ        6   /* RFC1332ѹ���㷨ѡ���  length for RFC1332 Van-Jacobson opt. */
#define PPP_CILEN_ADDR      6   /* ���͵���ַѡ��  new-style single address option */
#define PPP_CILEN_ADDRS     10  /* ��ʽż��ַѡ��  old-style dual address option */
/************************ IPCPģ�� *****************************/


/************************ IPXCPģ�� *****************************/
/* ��Э��ѡ��� */
#define PPP_CILEN_NODE      8   /* IPX�ڵ���Ŀѡ���  length for IPX Node Number opt. */
#define PPP_CILEN_ROUTING   4   /* ·��Э��ѡ����С����  min length for routing protocol opt. */
#define PPP_CILEN_ROUTER    3   /* ѹ��Э��ѡ����С����  min length for compression protocol opt. */
/************************ IPXCPģ�� *****************************/


/************************* �������� **********************************/
#define PPP_MP             0x003d
#define PPP_IP             0x0021
#define PPP_OSI            0x0023
#define PPP_IPX            0x002b

#define PPP_IP6                 0x0057
#define PPP_INTERFACELEN        8
#define PPP_MACADDRLEN          6
#define PPP_INTERFACENUMLEN     2
#define PPP_RANDOMLEN           4

#define PPP_IPHC                0x0061      /* IP�ײ�ѹ�� IP header compress */

#define PPP_VJ_COMP             0x002d
#define PPP_VJ_UNCOMP           0x002f
#define PPP_VJ_COMP_OLD         0x0037
#define PPP_COMP                0x00fd          /* ѹ���� compressed packet */

#define PPP_PPPMUX              0x0059          /* PPP��·���� PPP Multiplexing  */

#define PPP_IPXCP               0x802b          /* IPX����ѡ�� IPX Control Protocol */
#define TELEBIT_COMPRESS        0x0002          /* Telebitѹ��  Telebit Compressed IPX */
#define SHIVA_COMPRESS          0x0235          /* Shivaѹ��  Shiva Compressed NCP/IPX */
#define PPP_CCP                 0x80fd          /* ѹ������Э��  Compression Control Protocol */
#define PPP_PAP                 0xc023          /* ��Կ��֤Э��  P***W*** Authentication Protocol */
#define PPP_LQR                 0xc025          /* ��·��������Э��  Link Quality Report protocol */
#define PPP_CHAP                0xc223          /* ��ս���ֱ�����֤Э��  Cryptographic Handshake Auth. Protocol */
#define PPP_BCP                 0x8031          /* ppp���ſ���Э��  ppp bridge control protocol */
#define PPP_BP                  0x0031          /* ppp����Э��  PPP bridge protocol */
#define PPP_SCCP                0x80fd          /* ����·pppѹ������Э�� ppp compress control protocol on single link */
#define PPP_SCP                 0x00fd          /* ����·pppѹ��Э�� ppp compress protocol on single link */
#define PPP_MCCP                0x80fb          /* ����·pppѹ������Э�� ppp compress control protocol on multilink  */
#define PPP_MCP                 0x00fb          /* ����·pppѹ��Э�� PPP compress protocol on multilink */
#define PPP_SECP                0x8053          /* ����·pppenc ����Э�� ppp enc control protocol on single link */
#define PPP_SEP                 0x0053          /* ����·pppenc Э�� PPP enc protocol on single link */
#define PPP_MECP                0x8055          /* ����·pppenc ����Э�� PPP enc control protocol on multilink */
#define PPP_MEP                 0x0055          /* ����·pppenc Э�� PPP enc protocol on multilink */
#define PPP_BACP                0xc02b          /* �������ÿ���Э�� Bandwidth Allocation Control Protocol */
#define PPP_BAP                 0xc02d          /* �������Э�� Bandwidth Control Protocol */
#define PPP_CBCP                0xc029          /* �ؽп���Э�� Callback Control Protocol */
#define PPP_OSI_NPDU            0x0023          /* ����ϵͳ��������Э�����ݵ�ԪЭ�� OSI NPDU(Network Protocol Data Unit) Protocol */
#define PPP_MPLSCP              0x8281          /* ��Э���ǽ�������Э�� MPLS Control Protocol */
#define PPP_MPLS_UNICAST        0x0281          /* ���㴫�䱨�� MPLS unicast packet */
#define PPP_MPLS_MULTICAST      0x0283          /* ��㴫�䱨�� MPLS multicast packet */

/*add by wht06310 for debugsort*/
#define PPP_LCP_ECHO            0xc022

/************************* �������� **********************************/

/* 
 * Significant octet values.
 */
#define PPP_ALLSTATIONS 0xff        /* �㲥��ַ All-Stations broadcast address */
#define PPP_UI          0x03        /* δ�����Ϣ Unnumbered Information */
#define PPP_FLAG        0x7e        /* ������� Flag Sequence */
#define PPP_ESCAPE      0x7d        /* escape�첽���� Asynchronous Contro Escape */
#define PPP_TRANS       0x20        /* �첽͸������ Asynchronous transparency modifier */


/* Ԥ���ı���ͷ��С */
#define PPP_RESERVED_PACKET_HEADER  40
/* ��������ǰ׺ʡ�ԣ�����LCPЭ�̱��ĵĳ��ȿ��ܳ���200�ֽڣ������ӵ�256�ֽ� */
#define PPP_DEFAULT_NEGO_PACKET_LEN 256

/* MPͨ������ */
#define PPP_MP_NONE          0          /* ����MP */
#define PPP_MP_SUBCHANNEL    1          /* MP��ͨ�� */
#define PPP_MP_FATHER        2          /* MP��ͨ�� */
#define PPP_MP_TEMPLATE      3          /* MPģ�� */

#define PPP_MP_DISCR_LOCASSIGN_LEN  6   /* ���ط�����ն��������ų��� */

/* ��֤��Ϣ���� */
#define PPP_AUTH_ACCEPT      0
#define PPP_AUTH_FAILED      1

/* NP��ȡPPP LCP Echo�����Ϣ */
#define PPPISHANDLELCPECHO  0        /* VISP�Ƿ��ͺʹ������ */
#define PPPGETLCPECHOINFO  1         /* ��ȡLCP OPEN״̬��Echo�����Ϣ */

/* ������Ч�Ķ�ʱ��ID�� */
#define PPP_INVALID_TIMERID  0

/* ����NCP��ʱ����һ��CR���Ķ�ʱ����С�����ֵ */
#define PPP_NCP_NEGO_DELAY_MIN 1
#define PPP_NCP_NEGO_DELAY_MAX 6000

/*************************** ���Ķ���д�� (Begin)****************************/
/* �ƶ�ָ�뱨�� */
#define PPP_INCPTR(n, cp)   ((cp) += (n))
#define PPP_DECPTR(n, cp)   ((cp) -= (n))

/*
* Inline versions of get/put char/short/long.
* Pointer is advanced; we assume that both arguments
* are lvalues and will already be in registers.
* ������Ԫ�ؾ�Ϊ����㣬�����Ѿ����ڻ�������
* cp MUST be UCHAR *. cp�����ͱ���ΪUCHAR��
*/

#define PPP_GETCHAR(c, cp) { \
    (c) = *(cp); \
    (cp) ++ ; \
}
#define PPP_PUTCHAR(c, cp) { \
    *(cp) = (UCHAR) (c); \
    (cp) ++ ; \
}

/*modify by wht06310 for compatibility ARMCPU,2006-05-13*/
#ifdef TCPIP_SUPPORT_ARMCPU
#define PPP_GETSHORT(s, cp) { \
#define PPP_GETLONG(l, cp) { \
    (l) = VOS_NTOHL(*((ULONG *)cp)); \
    cp += sizeof(ULONG) ; \
}
#define PPP_PUTLONG(l, cp) { \
    *((ULONG*)cp) = VOS_HTONL(l) ; \
    cp += sizeof(ULONG) ; \
}
#endif
#define PPP_HDRLEN_PF(bNegPfc,usProtocol) \
    (bNegPfc ? ((usProtocol & 0xff00) ? 2:1) : 2)

#define PPP_HDRLEN_ACF(bNegAcfc) (bNegAcfc ? 0:2)

#define PPP_MAKEPF(bPfc, p, t) \
{ \
    if (PPP_LCP == t) \
    { \
        PPP_PUTSHORT(t, p); \
    } \
    else if (bPfc && !(t & 0xff00) ) \
    { \
        PPP_PUTCHAR((UCHAR)t,p); \
    } \
    else \
    { \
        PPP_PUTSHORT(t, p); \
    } \
}
/* End of addition */

/*
 * Ϊ���������ײ�
 * PPP_MAKEHEADER - Add Header fields to a packet.
 */
#define PPP_MAKEHEADER(bPfc,bAcfc,p, t) \
{ \
    if ((PPP_LCP == t) || (!bAcfc)) \
    { \
        PPP_PUTCHAR(PPP_ALLSTATIONS, p); \
        PPP_PUTCHAR(PPP_UI, p); \
    } \
    PPP_MAKEPF(bPfc,p,t); \
}

/* ����ǰ׺ʡ��ӳ����������ݿ��� */
#define PPP_COPYPREFIXE(pstPppInfo, pstDestInfo, pstSrcInfo)\
{\
    if ( NULL == pstDestInfo->pstPrefixE )\
    {\
        pstDestInfo->pstPrefixE = (MC_PREFIXE_S *)TCPIP_Malloc(g_stPPPModInfo.ulMID_PPP | g_stPPPModInfo.ulSID_PPP_CB_S, \
                                                             sizeof(MC_PREFIXE_S)*MC_PREFIXE_MAX_NUM);\
        if ( NULL == pstDestInfo->pstPrefixE )\
        {\
            PPP_Debug_CoreEvent(pstPppInfo, PPP_LOG_ERROR, "Malloc Prefix-Elision CB error!!");\
        }\
    }\
    if ( pstDestInfo->pstPrefixE )\
    {\
        if ( pstSrcInfo->pstPrefixE )\
        {\
            (VOID)TCPIP_Mem_Copy(pstDestInfo->pstPrefixE, sizeof(MC_PREFIXE_S)*MC_PREFIXE_MAX_NUM, pstSrcInfo->pstPrefixE, sizeof(MC_PREFIXE_S)*MC_PREFIXE_MAX_NUM);\
        }\
        else\
        {\
            (VOID)TCPIP_Mem_Set((CHAR *)pstDestInfo->pstPrefixE, 0, sizeof(MC_PREFIXE_S)*MC_PREFIXE_MAX_NUM);\
        }\
    }\
}


/* ������PPP_LCP_OPTION_S��PPPCONFIGINFO_S�ṹ��������ǰ׺ʡ��ӳ���ָ�룬
   �����ڽ������ݿ���ʱ���ܼ򵥵Ľṹ��ֵ��Ҫ��ǰ׺ʡ��ӳ���ָ�������⴦�� */
#define PPP_COPYINFOBYPREFIXE(pstPppInfo, opt, pstDestInfo, pstSrcInfo)\
{\
    if ( opt )\
    {\
        /* ��SrcLcpOption�����ݿ�����DestLcpOption�У���ǰ׺ʡ��ӳ���ָ����ռ4���ֽ��� */\
        (VOID)TCPIP_Mem_Copy(pstDestInfo, sizeof(*pstDestInfo), pstSrcInfo, sizeof(*pstDestInfo)-LEN_4);\
        PPP_COPYPREFIXE(pstPppInfo, pstDestInfo, pstSrcInfo);\
    }\
    else\
    {\
        if ( pstDestInfo->pstPrefixE )\
        {\
            (VOID)TCPIP_Free(pstDestInfo->pstPrefixE);\
            pstDestInfo->pstPrefixE = NULL;\
        }\
        /* ���������ǰ׺ʡ��ӳ������ֱ�ӿ������� */\
        (VOID)TCPIP_Mem_Copy(pstDestInfo, sizeof(*pstDestInfo), pstSrcInfo, sizeof(*pstDestInfo));\
    }\
}
/* End of added */


/*************************** ���Ķ���д�� (End)****************************/


#define PPP_NEED_NEGO      1
#define PPP_NOT_NEED_NEGO  0


/**********************/
/* ״̬��ģ��ĺ궨�� */
/**********************/

/***************************** codeֵ ********************************/
/*
 *  CP (LCP, IPCP, etc.) codes.
 */
#define CONFREQ   1   /* �������� Configuration Request */
#define CONFACK   2   /* Ack���� Configuration Ack */
#define CONFNAK   3   /* Nak���� Configuration Nak */
#define CONFREJ   4   /* �ܾ����� Configuration Reject */
#define TERMREQ   5   /* ��ֹ���� Termination Request */
#define TERMACK   6   /* ACK��ֹ Termination Ack */
#define CODEREJ   7   /* ����ܾ� Code Reject */
#define PROTREJ   8   /* Э��ܾ� Protocol-Reject */
/***************************** codeֵ ********************************/


/****************************** ״̬ *********************************/
/* FSM states */
enum ePppState
{
    PPP_STATE_INITIAL = 0,  /* 0   down��û�д� Down, hasn't been opened */
    PPP_STATE_STARTING,     /* 1   down���Ѿ��� Down, been opened */
    PPP_STATE_CLOSED,       /* 2   up��û�д� Up, hasn't been opened */
    PPP_STATE_STOPPED,      /* 3   open���ȴ�down�¼� Open, waiting for down event */
    PPP_STATE_CLOSING,      /* 4   ��ֹ���ӣ�û�д� Terminating the connection, not open */
    PPP_STATE_STOPPING,     /* 5   ��ֹ���� Terminating, but open */
    PPP_STATE_REQSENT,      /* 6   ����һ���ܾ����� We've sent a Config Request */
    PPP_STATE_ACKRCVD,      /* 7   ����һ��ACK���� We've received a Config Ack */
    PPP_STATE_ACKSENT,      /* 8   ����һ��ACK���� We've sent a Config Ack */
    PPP_STATE_OPENED        /* 9   �������� Connection available */
};

#define PPP_TUNNEL_TYPE_L2TP  3

/*�������û���������PPP*/
#define PPP_USERTYPE_PPP               0x0010
#define PPP_USERTYPE_L2TP              0x0050


/************************ PPP ״̬��״̬ת��ͼ (Begin)***********************/
/*
           | State״̬
           |  0           1        2          3         4         5           6         7         8           9
Events �¼�| Initial   Starting  Closed    Stopped   Closing   Stopping   Req-Sent  Ack-Rcvd  Ack-Sent    Opened
             ״̬       ״̬     ״̬       ״̬      ״̬      ״̬      ״̬        ״̬     ״̬        ״̬
-----------+------------------------------------------------------------------------------------------------------
 Up   �¼�|    2     irc,scr/6     -         -         -         -          -         -         -           -
 Down �¼�|    -         -       0       tls/1       0         1          1         1         1         tld/1
 Open �¼�|  tls/1       1     irc,scr/6     3r        5r        5r         6         7         8           9r
 Close�¼�|    0       tlf/0       2         2         4         4      irc,str/4  irc,str/4   irc,str/4    tld,irc,str/4
          |
  TO+ �¼�|    -         -         -         -      str/4     str/5     scr/6    scr/6     scr/8         -
  TO- �¼�|    -         -         -         -       tlf/2     tlf/3      tlf/3p    tlf/3p    tlf/3p        -
          |
 RCR+ �¼�|    -         -    sta/2   irc,scr,sca/8     4         5        sca/8   sca,tlu/9   sca/8    tld,scr,sca/8
 RCR- �¼�|    -         -    sta/2   irc,scr,scn/6     4         5        scn/6     scn/7     scn/6   tld,scr,scn/6
 RCA  �¼�|    -         -    sta/2     sta/3         4         5        irc/7     scr/6x  irc,tlu/9    tld,scr/6x
 RCN  �¼�|    -         -    sta/2     sta/3         4         5      irc,scr/6   scr/6x  irc,scr/8    tld,scr/6x
          |
 RTR  �¼�|    -         -    sta/2     sta/3        sta/4     sta/5      sta/6     sta/6     sta/6    tld,zrc,sta/5
 RTA  �¼�|    -         -      2         3         tlf/2     tlf/3        6         6         8      tld,scr/6
          |
 RUC  �¼�|    -         -    scj/2     scj/3        scj/4     scj/5      scj/6     scj/7     scj/8       scj/9
 RXJ+ �¼�|    -         -      2         3          4         5          6         6         8           9
 RXJ- �¼�|    -         -     tlf/2     tlf/3         tlf/2     tlf/3       tlf/3     tlf/3     tlf/3       tld,irc,str/5
          |
 RXR  �¼�|    -         -      2         3          4         5          6         7         8      ser/9
*/

/* �¼�(Events)�Ͷ���(Actions)˵��:
   Events                                   Actions

   Up   = lower layer is Up                 tlu = This-Layer-Up
          �²�up                                  ����up
   Down = lower layer is Down               tld = This-Layer-Down
          �²�down                                ����down
   Open = administrative Open               tls = This-Layer-Started
          �����                                ���㿪ʼ
   Close= administrative Close              tlf = This-Layer-Finished
          ����ر�                                �������

   TO+  = Timeout with counter > 0          irc = Initialize-Restart-Count
          count�����㳬ʱ                         ��ʼ�����¿�ʼ
   TO-  = Timeout with counter expired      zrc = Zero-Restart-Count
          count���ڳ�ʱ

   RCR+ = Receive-Configure-Request (Good)  scr = Send-Configure-Request
          ����CR����                              ����CR����
   RCR- = Receive-Configure-Request (Bad)
   RCA  = Receive-Configure-Ack             sca = Send-Configure-Ack
          ��������ACK                             ��������ACK
   RCN  = Receive-Configure-Nak/Rej         scn = Send-Configure-Nak/Rej
          ��������NAK/Rej                         ��������NAK/Rej
   RTR  = Receive-Terminate-Request         str = Send-Terminate-Request
          ��������                                ������ֹ����
   RTA  = Receive-Terminate-Ack             sta = Send-Terminate-Ack
          ������ֹACK                             ������ֹACK

   RUC  = Receive-Unknown-Code              scj = Send-Code-Reject
          ����δ֪����                            ���ͱ���ܾ�
   RXJ+ = Receive-Code-Reject (permitted)
          ���ձ���ܾ�������
       or Receive-Protocol-Reject
       �� ����Э��ܾ�
   RXJ- = Receive-Code-Reject (catastrophic)
       or Receive-Protocol-Reject
   RXR  = Receive-Echo-Request              ser = Send-Echo-Reply
          �����ظ�����                            �����ظ�Ӧ��
       or Receive-Echo-Reply
       �� �����ظ�Ӧ��
       or Receive-Discard-Request
       �� ���ն�������
*/

/* �¼�(Events)�Ͷ���(Actions)�Ĵ���
   �����¼���
   ÿ���¼�һ������,+��-���¼�(��RCR+��RCR-)�ϲ�Ϊһ������,
   ��ΪҪ�ں������жϾ�����+����-�¼�.

   ���ڶ���:
   ÿ������һ����.
*/
/************************ PPP ״̬��״̬ת��ͼ (End)***********************/


/************************ ״̬�������ĺ궨�� (Begin)*************************/

/* tlu(����up This-Layer-Up)����:���ûص�����up */
#define PPP_FSM_tlu(pstFsm) \
{\
    PPP_Debug_FsmAction(pstFsm, (ULONG)PPP_ACTION_FSM_TLU); \
    if((pstFsm->pstCallBacks != NULL) && (pstFsm->pstCallBacks->up)) \
    { \
        (*pstFsm->pstCallBacks->up)(pstFsm); \
    } \
}

/* tld(����down This-Layer-Down)����:���ûص�����down */
#define PPP_FSM_tld(pstFsm) \
{\
    PPP_Debug_FsmAction(pstFsm, (ULONG)PPP_ACTION_FSM_TLD); \
    if((pstFsm->pstCallBacks != NULL)&&(pstFsm->pstCallBacks->down)) \
    { \
        /* ��down */ \
        (*pstFsm->pstCallBacks->down)(pstFsm); \
    } \
}

/* tls(���㿪ʼ This-Layer-Started)����: */
#define PPP_FSM_tls(pstFsm) \
{\
    PPP_Debug_FsmAction(pstFsm, (ULONG)PPP_ACTION_FSM_TLS); \
    if((pstFsm->pstCallBacks != NULL) && (pstFsm->pstCallBacks->starting)) \
    { \
        (*pstFsm->pstCallBacks->starting)(pstFsm); \
    } \
}

/* tlf(������� This-Layer-Finished)����: */
#define PPP_FSM_tlf(pstFsm) \
{\
    PPP_Debug_FsmAction(pstFsm, (ULONG)PPP_ACTION_FSM_TLF); \
    if((pstFsm->pstCallBacks != NULL) && (pstFsm->pstCallBacks->finished)) \
    { \
        (*pstFsm->pstCallBacks->finished)(pstFsm); \
    } \
}

/* irc(��ʼ�������������� Initialize-Restart-Count)����: */
#define PPP_FSM_irc(pstFsm) \
{ \
    /* ת����ʼ�� Retransmits */ \
    PPP_Debug_FsmAction(pstFsm, (ULONG)PPP_ACTION_FSM_IRC); \
    pstFsm->sRetransmits = (SHORT)g_stPPPModInfo.ulPPP_DEF_CONFREQS;/*���Retransmitֵ*/\
    /* TimeOutTime�ص���ʼֵ */ \
    /*pstFsm->ulTimeOutTime = PPP_DEFTIMEOUTTIME; ��ʼֵ */ \
    /*pstFsm->usNakloops = 0; �����ڴ˴����㣬���򲻸����ʱ��Ҳ���ˣ�*/\
    /*����Э�����벻��Ҫ��ѭ����pengjimei2003/07/27*/\
}

/* zrc(���㣭���������� Zero-Restart-Count)����: */
#define PPP_FSM_zrc(pstFsm) \
{ \
    PPP_Debug_FsmAction(pstFsm, (ULONG)PPP_ACTION_FSM_ZRC); \
    pstFsm->sRetransmits = 0; \
}


/* scr(���ͣ����ã����� Send-Configure-Request)����:���ͱ��� */
#define PPP_FSM_scr(pstFsm) \
{ \
    PPP_Debug_FsmAction(pstFsm, (ULONG)PPP_ACTION_FSM_SCR); \
    PPP_FSM_SendConfigReq(pstFsm); \
    pstFsm->ucPktId ++; \
    /* ������ʱ�� */ \
    PPP_FSM_SetRetransmitTimer(pstFsm); \
}

/* sca(Send-Configure-Ack)��scn(Send-Configure-Nak/Rej)����: */
/* ulCode�����˾�����ʲô���� */
#define PPP_FSM_sca_scn(pstFsm, ucCode, ucId, pHead, pPacket, ulLen) \
{ \
    PPP_Debug_FsmAction(pstFsm, (ULONG)PPP_ACTION_FSM_SCA_SCN); \
    PPP_FSM_SendPacket(pstFsm, ucCode, ucId, pHead, pPacket, ulLen); \
}

/* str(���ͣ���ֹ������ Send-Terminate-Request)���� */
#define PPP_FSM_str(pstFsm) \
{ \
    PPP_Debug_FsmAction(pstFsm, (ULONG)PPP_ACTION_FSM_STR); \
    PPP_FSM_SendPacketByCode(pstFsm, TERMREQ, pstFsm->ucPktId); \
    pstFsm->ucPktId ++; \
    /* ������ʱ�� */ \
    PPP_FSM_SetRetransmitTimer(pstFsm); \
}

/* sta(���ͣ���ֹ��Ack Send-Terminate-Ack)���� */
#define PPP_FSM_sta(pstFsm, ucId) \
{ \
    PPP_Debug_FsmAction(pstFsm, (ULONG)PPP_ACTION_FSM_STA); \
    PPP_FSM_SendPacketByCode(pstFsm, TERMACK, ucId); \
}

/* scj(���ͣ����룭�ܾ� Send-Code-Reject)���� */
#define PPP_FSM_scj(pstFsm, pHead, pPacket, ulLen) \
{ \
    PPP_Debug_FsmAction(pstFsm, (ULONG)PPP_ACTION_FSM_SCJ); \
    PPP_FSM_SendPacket(pstFsm, CODEREJ, pstFsm->ucPktId, pHead, pPacket, ulLen); \
}

/* ser(���ͣ����أ�Ӧ�� Send-Echo-Reply)����,ֻ��LCP������������ */
#define PPP_FSM_ser(pstFsm, ucId, pHead, pPacket, ulLen, ulMagicNumber) \
{ \
    UCHAR *pTemp = pPacket; \
    /* �������                                                       \
    |--------FSM Head(bytes) -------|                                 \
        0       1      2       3        4       5       6       7     \
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ \
    |       |       |       |       |       |       |       |       | \
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ \
                                    |                                 \
                                    pPacket                           \
                                    pTemp                             \
    */ \
    PPP_Debug_FsmAction(pstFsm, (ULONG)PPP_ACTION_FSM_SER); \
    PPP_PUTLONG(ulMagicNumber, pTemp); \
    pstFsm->sRetransmits = (SHORT)g_stPPPModInfo.ulPPP_DEF_CONFREQS;\
    /* �������                                                       \
    |--------FSM Head(bytes) -------|                                 \
        0       1      2       3        4       5       6       7     \
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ \
    |       |       |       |       |       Magic  Number           | \
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ \
                                    |                               | \
                                    pPacket                         | \
                                                                 pTemp\
    */                                                                \
   PPP_FSM_SendPacket(pstFsm, ECHOREP, ucId, pHead, pPacket, ulLen); \
}

/************************ ״̬�������ĺ궨�� (End)*************************/


/************************ ��״̬���йص������궨�� (Begin)*************************/

/* �ı�״̬,���ڲ���Ҫ��ʱ����״̬,ɾ����ʱ�� */
/* TO�¼���״̬ת��ͼ */
/*
      | State
      |    0         1         2         3         4         5           6         7         8           9
Events| Initial   Starting  Closed    Stopped   Closing   Stopping   Req-Sent  Ack-Rcvd  Ack-Sent    Opened
------+------------------------------------------------------------------------------------------------------
  TO+ |    -         -         -         -       str/4     str/5      scr/6     scr/6     scr/8         -
  TO- |    -         -         -         -       tlf/2     tlf/3      tlf/3p    tlf/3p    tlf/3p        -
*/
/* ���,Initial��Starting��Closed��Stopped��Opened״̬���ö�ʱ��,��Ҫɾ����ʱ��,
   ����״̬����ԭ���Ķ�ʱ�� */
/* �����ACKRCVD״̬����TO-�¼�����ô��˫������·��ʱʱ������̫��������ģ�Ӧ������negotiate timeʱ�� */
/*��Э���OPEN״̬ת������Ҫ֪ͨ����*/
/*��Э��ת��OPEN״̬���ҷ�Mp��ͨ��������MP��ͨ���ڰ󶨳ɹ�ʱ����*/

/* ɾ���ش���ʱ�� */
#define PPP_FSM_DelRetransmitTimer(pstFsm) \
{ \
    if(pstFsm->ulTimeOutID) \
    { \
        (VOID)PPP_Timer_Delete(pstFsm->ulTimeOutID); \
        pstFsm->ulTimeOutID = 0; \
    } \
}

/* �����ش���ʱ�� */
/* ʹ��ѭ����ʱ������������Ϣ��ʧ����״̬���޷��������� */
#define PPP_FSM_SetRetransmitTimer(pstFsm) \
{ \
    ULONG ulRetValue; \
    PPPINFO_S *pstTempPppInfo = NULL;\
    /* �����ʱ���Ѿ����������ô��� */ \
    if (0 == pstFsm->ulTimeOutID) \
    { \
        if ((NULL != (PPPINFO_S *)pstFsm->pPppInfo) && (NULL != pstFsm->pstCallBacks) && (NULL != pstFsm->pstCallBacks->timerout))\
        {\
            pstTempPppInfo = (PPPINFO_S *)pstFsm->pPppInfo;\
            ulRetValue = PPP_Timer_Create(\
                             pstFsm->ulTimeOutTime, \
                             pstFsm->pstCallBacks->timerout, \
                             (VOID*)(UINTPTR)pstTempPppInfo->ulIfIndex, \
                             &(pstFsm->ulTimeOutID) \
                            ); \
            VOS_DBGASSERT(0 == ulRetValue); \
        }\
    } \
}

#define PPP_FSM_SetRetransmitTimerWithLessDelay(pstFsm) \
{ \
    ULONG ulRetValue; \
    PPPINFO_S *pstPppInfo = NULL;\
    /* �����ʱ���Ѿ����������ô��� */ \
    if (0 == pstFsm->ulTimeOutID) \
    { \
        if ((NULL != (PPPINFO_S *)pstFsm->pPppInfo) && (NULL != pstFsm->pstCallBacks) && (NULL != pstFsm->pstCallBacks->timerout))\
        {\
            pstPppInfo = (PPPINFO_S *)pstFsm->pPppInfo;\
            ulRetValue = PPP_Timer_Create(\
                             pstFsm->ulTimeOutTime - g_ulPPPRestanmitDelay, \
                             pstFsm->pstCallBacks->timerout, \
                             (VOID*)(UINTPTR)pstPppInfo->ulIfIndex, \
                             &(pstFsm->ulTimeOutID) \
                            ); \
            VOS_DBGASSERT(0 == ulRetValue); \
        }\
    } \
}
/* End of addition */

/*����config-request����*/
#define PPP_FSM_reqci(pstFsm, pPacket, ulLen, ucCode) \
{ \
            if(PPP_MAXNAKLOOPS <= pstFsm->usNakloops) \
            {\
                /* ��Ӧ���ѭ�����ﵽ�������Ҫ�򱸷ݸ����ݱ� reaching the max nak loops, backup the packet to build REJ packet if need. */ \
                (VOID)TCPIP_Mem_Copy(szPacketBuf, PPP_DEFAULT_NEGO_PACKET_LEN, pPacket, ulLen); \
            }\
            ucCode = (*pstFsm->pstCallBacks->reqci)(pstFsm, pPacket, &ulLen); /* ����ci���� parse his request ci */ \
            if(CONFNAK == ucCode) \
            { \
                pstFsm->usNakloops ++; \
                if(pstFsm->usNakloops > PPP_MAXNAKLOOPS) \
                { \
                    /* NCCЭ��ʧ��ԭ��ɼ� */ \
                    if (NCC_PPP_ISENABLE) \
                    { \
                        PPPINFO_S *pst_PppInfo = (PPPINFO_S*)(pstFsm->pPppInfo); \
                        if (pst_PppInfo) \
                        { \
                            if (PPP_LCP == pstFsm->usProtocol) \
                            { \
                                NCC_RecordPppLcpDot(LCP_FSM_REQCI_MAXNAKTOREJ, pst_PppInfo->ulIfIndex); \
                            } \
                            else if (PPP_IPCP == pstFsm->usProtocol) \
                            { \
                                NCC_RecordPppIpcpDot(IPCP_FSM_REQCI_MAXNAKTOREJ, pst_PppInfo->ulIfIndex); \
                            } \
                        } \
                    } \
                    /*add by wuhailan for log enhance, 2007-3-21.*/\
                    TCPIP_LOG_FIXLEN(RUN_LOG_VISP_0E88, TCPIP_LOG_LEVEL_ERROR, LOG_TYPE_RUN, \
                          "TCPIP PPP LOG:Rej neg pkt!/nakloops:%d\n", pstFsm->usNakloops, 0, 0, 0);\
                    ulLen = PPP_FSM_RebuildRejPacket(pPacket, (LONG)ulLen, szPacketBuf, (LONG)ulPacketLen); \
                } \
                else\
                {\
            } \
            else \
            { \
                ucCode = CONFACK; \
            } \
        } \
    }\
}

/************************ ��״̬���йص������궨�� (End)*************************/


/************************ ��debug�йصĺ궨�� (Begin)*************************/

/* ����/������ı�־�� */
#define PPP_DEBUG_PACKET_IN       0
#define PPP_DEBUG_PACKET_OUT      1
#define PPP_DEBUG_PACKET_UNCOMPED 2
#define PPP_DEBUG_PACKET_FORCOMP  3
#define PPP_DEBUG_PACKET_VERBOSE_LENTH  64

/* debug�����е�����ֵ */
#define PPP_DEBUG_ERROR       0
#define PPP_DEBUG_EVENT       1
#define PPP_DEBUG_PACKET      2
#define PPP_DEBUG_STATE       3
#define PPP_DEBUG_ALL         4
#define PPP_DEBUG_ACTION      5

#define PPP_DEBUG_VERBOSE     6

/* Ŀ����ϵĵ��Ժ� */
#define PPP_DebugOutString(cDebugBuf, ulLen, pstPppInfo) \
{ \
    g_stPPPShellFun.pfPPP_ShowDebugInfo(cDebugBuf, (ULONG)(ulLen)); \
}

/************************ ��debug�йصĺ궨�� (End)*************************/





/**********************protocol name index*********************/
enum enPppProNameIndex
{
    PPP_PRONAMEINDEX_IP,         /* 0 */
    PPP_PRONAMEINDEX_LCP,        /* 1 */
    PPP_PRONAMEINDEX_PAP,        /* 2 */
    PPP_PRONAMEINDEX_CHAP,       /* 3 */
    PPP_PRONAMEINDEX_IPCP,       /* 4 */
    PPP_PRONAMEINDEX_IPXCP,      /* 5 */
    PPP_PRONAMEINDEX_MP,         /* 6 */
    PPP_PRONAMEINDEX_BCP,        /* 7 */
    PPP_PRONAMEINDEX_BRIDGE,     /* 8 */
    PPP_PRONAMEINDEX_VJComp,     /* 9 */
    PPP_PRONAMEINDEX_VJUnComp,   /* 10 */
    PPP_PRONAMEINDEX_IPX,        /* 11 */
    PPP_PRONAMEINDEX_CCP,        /* 12 */
    PPP_PRONAMEINDEX_MCCP,       /* 13 */
    PPP_PRONAMEINDEX_SCP,        /* 14 */
    PPP_PRONAMEINDEX_MCP,        /* 15 */
    PPP_PRONAMEINDEX_MPLSCP,     /* 16 */
    PPP_PRONAMEINDEX_MPLS_UNICAST,     /* 17 */
    PPP_PRONAMEINDEX_MPLS_MULTICAST,   /* 18 */
    PPP_PRONAMEINDEX_OSICP,      /* 19 */
    PPP_PRONAMEINDEX_OSI_NPDU,   /* 20 */
    PPP_PRONAMEINDEX_CBCP,       /* 21 */
    PPP_PRONAMEINDEX_LQM         /* 22 */
    ,PPP_PRONAMEINDEX_IP6CP,     /* 23 */
    PPP_PRONAMEINDEX_IP6         /* 24 */
    ,PPP_PRONAMEINDEX_PPPMUXCP,  /* 25 */
    PPP_PRONAMEINDEX_PPPMUX      /* 26 */
    /* End of addition */

    ,PPP_PRONAMEINDEX_FULL_HEADER,          /* 27 */
    PPP_PRONAMEINDEX_Compressed_TCP,        /* 28 */
    PPP_PRONAMEINDEX_Compressed_TCP_NODELTA,/* 29 */
    PPP_PRONAMEINDEX_Compressed_NON_TCP,    /* 30 */
    PPP_PRONAMEINDEX_Compressed_UDP_8,      /* 31 */
    PPP_PRONAMEINDEX_Compressed_UDP_16,     /* 32 */
    PPP_PRONAMEINDEX_Compressed_RTP_8,      /* 33 */
    PPP_PRONAMEINDEX_Compressed_RTP_16,     /* 34 */
    PPP_PRONAMEINDEX_CONTEXT_STATE          /* 35 */
    /* End of addition */
};
/********************Э��������  protocol name index*******************/


/************************ ͬ�첽ת���� *************************/
#define PPP_ConvertByteToAsy(ucOctet, pAsyData, ulAsyLen, ulAsynAccm) \
{                                                  \
    if((ucOctet == '\x7e') || (ucOctet == '\x7d')) \
    {                                              \
        /* ����escape���ƶ� add the Escape Control Character */     \
        *pAsyData = '\x7d';                        \
        pAsyData ++;                               \
        ulAsyLen ++;                               \
        ucOctet ^= 0x20;                           \
    }                                              \
    if(ucOctet < 0x20)                             \
    {                                              \
        if ((ulAsynAccm >> (unsigned int)ucOctet) & ((unsigned int)0x1)) \
        {                                          \
            /* �����Ҫ����escape���ƶ� if this character need be mapped, add the Escape Control Character */ \
            *pAsyData = '\x7d';                    \
            pAsyData ++;                           \
            ulAsyLen ++;                           \
            ucOctet ^= 0x20;                       \
        }                                          \
    }                                              \
    /* ����escape���ƶ� add the Escape Control Character */         \
    * pAsyData = ucOctet;                          \
    pAsyData ++;                                   \
    ulAsyLen ++; /* �ʺ�֡���� adjust frame's length */       \
}
/************************ ͬ�첽ת���� *************************/


/* ������������¼��PPP���ƿ� Add by xiaoshouhe31170 2003/10/16 */
#define PPP_FLOW_STAT_OUT(pstPppInfo, ulLen) \
{\
    (pstPppInfo)->stStatisticInfo.ulOutOctets += (ulLen);\
    if((pstPppInfo)->stStatisticInfo.ulOutOctets < (ulLen))\
    {\
        (pstPppInfo)->stStatisticInfo.ulOutGigaWords++;\
    }\
    (pstPppInfo)->stStatisticInfo.ulOutPackets++;\
}

/* ������������¼��PPP���ƿ� Add by xiaoshouhe31170 2003/10/16 */
#define PPP_FLOW_STAT_IN(pstPppInfo, ulLen) \
{\
    (pstPppInfo)->stStatisticInfo.ulInOctets += (ulLen);\
    if((pstPppInfo)->stStatisticInfo.ulInOctets < (ulLen))\
    {\
        (pstPppInfo)->stStatisticInfo.ulInGigaWords++;\
    }\
    (pstPppInfo)->stStatisticInfo.ulInPackets++;\
}


/********************* ��ʱ����صĺ궨�� (Begin)**********************/

#define PPP_CHAIN_TAIL       -1    /* �������±괮�����ĸ�������ı�β */

#define PPP_DEF_GLOBALTIME 1000

#define PppChainDelNode(astBufHead,pstQueueHead,pstNode) \
{\
    if (PPP_CHAIN_TAIL == ((pstNode)->stNode.lPrev))\
    {\
        (pstQueueHead)->lNext =  (pstNode)->stNode.lNext;\
    }\
    else \
    { \
        astBufHead[((pstNode)->stNode.lPrev)].stNode.lNext = (pstNode)->stNode.lNext;\
    } \
    if (PPP_CHAIN_TAIL == ((pstNode)->stNode.lNext))\
    { \
        (pstQueueHead)->lPrev =  (pstNode)->stNode.lPrev;\
    } \
    else \
    { \
        astBufHead[((pstNode)->stNode.lNext)].stNode.lPrev = (pstNode)->stNode.lPrev;\
    } \
    (pstNode)->stNode.lPrev = PPP_CHAIN_TAIL;\
    (pstNode)->stNode.lNext = PPP_CHAIN_TAIL;\
}

#define PppChainAddNode(astBufHead,pstQueueHead,pstNode)\
{\
    (pstNode)->stNode.lPrev = (pstQueueHead)->lPrev;\
    (pstNode)->stNode.lNext = PPP_CHAIN_TAIL;\
    if (PPP_CHAIN_TAIL == ((pstNode)->stNode.lPrev))\
    {\
        (pstQueueHead)->lNext = (pstNode) - (astBufHead);\
    }\
    else\
    {\
        astBufHead[((pstNode)->stNode.lPrev)].stNode.lNext = (pstNode) - (astBufHead);\
    }\
    (pstQueueHead)->lPrev = (pstNode) - (astBufHead);\
}

#define PppChainInsNode(astBufHead,pstQueueHead,pstNode,pstNewNode)\
{\
    (pstNewNode)->stNode.lNext = (pstNode) - (astBufHead);\
    if (PPP_CHAIN_TAIL == ((pstNode)->stNode.lPrev))\
    {\
        (pstNewNode)->stNode.lPrev = PPP_CHAIN_TAIL;\
        (pstQueueHead)->lNext = (pstNewNode) - (astBufHead);\
    }\
    else\
    {\
        (pstNewNode)->stNode.lPrev =  (pstNode)->stNode.lPrev;\
        astBufHead[((pstNode)->stNode.lPrev)].stNode.lNext = (pstNewNode) - (astBufHead);\
    }\
    (pstNode)->stNode.lPrev = (pstNewNode) - (astBufHead);\
}

#define PppChainPrevNode(astBufHead,pstNode,pstPrevNode)\
{\
    if (PPP_CHAIN_TAIL == ((pstNode)->stNode.lPrev))\
    {\
        pstPrevNode = NULL;\
    }\
    else\
    {\
        pstPrevNode = &(astBufHead[((pstNode)->stNode.lPrev)]);\
    }\
}

#define PppChainNextNode(astBufHead,pstNode,pstNextNode)\
{\
    if (PPP_CHAIN_TAIL == ((pstNode)->stNode.lNext))\
    {\
        pstNextNode = NULL;\
    }\
    else\
    {\
        pstNextNode = &(astBufHead[((pstNode)->stNode.lNext)]);\
    }\
}

#define PppChainFirstNode(astBufHead,pstQueueHead,pstFirstNode)\
{\
    if (PPP_CHAIN_TAIL == (pstQueueHead)->lNext)\
    {\
        pstFirstNode = NULL;\
    }\
    else\
    {\
        pstFirstNode = &(astBufHead[((pstQueueHead)->lNext)]);\
    }\
}

#define PppChainEndNode(astBufHead,pstQueueHead,pstEndNode)\
{\
    if (PPP_CHAIN_TAIL == (pstQueueHead)->lPrev)\
    {\
        pstEndNode = NULL;\
    }\
    else\
    {\
        pstEndNode = &(astBufHead[((pstQueueHead)->lPrev)]);\
    }\
}

/********************* ��ʱ����صĺ궨�� (End)**********************/

/* ����������õĲ����ͱ���Э�̻�õĲ�����һ��, ������Э�̻�õĲ�����һ��, ���¼�澯 */
#define PPP_PARA_CMP_RECORD(parameter, stParaRecorder, usWarningRecord)\
if ((pstWantOptions->parameter != pstGotOptions->parameter)\
   || (pstGotOptions->parameter != pstHisOptions->parameter))\
{\
    stParaRecorder.ul_is_different = 1;\
    stParaRecorder.ul_want_value = pstWantOptions->parameter;\
    stParaRecorder.ul_got_value = pstGotOptions->parameter;\
    stParaRecorder.ul_his_value = pstHisOptions->parameter;\
    usWarningRecord |= PPP_IPHC_PARA_DIFF;\
}\

/********************** PPP�澯��صĺ궨��(End) **********************/

#define PPP_COPY_LCPOPTION_TO_PPI(stPpiInfo, pstLcpOption)\
{\
    ULONG i;\
    VOS_DBGASSERT(PPI_MC_PREFIX_MAX_NUM >= MC_PREFIXE_MAX_NUM);\
    VOS_DBGASSERT(PPI_MC_PREFIX_MAX_LEN >= MC_PREFIXE_MAX_STR);\
    (stPpiInfo).neg_discr = (pstLcpOption)->neg_discr;\
    (stPpiInfo).neg_magicnumber = (pstLcpOption)->neg_magicnumber;\
    (stPpiInfo).neg_accompression = (pstLcpOption)->neg_accompression;\
    (stPpiInfo).neg_asyncmap = (pstLcpOption)->neg_asyncmap;\
    (stPpiInfo).neg_mhf = (pstLcpOption)->neg_mhf;\
    (stPpiInfo).neg_mrru = (pstLcpOption)->neg_mrru;\
    (stPpiInfo).neg_mru = (pstLcpOption)->neg_mru;\
    (stPpiInfo).neg_pcompression = (pstLcpOption)->neg_pcompression;\
    (stPpiInfo).neg_prefix = (pstLcpOption)->neg_prefixE;\
    (stPpiInfo).neg_ssnhf = (pstLcpOption)->neg_ssnhf;\
    (stPpiInfo).ulAsyncmap = (pstLcpOption)->asyncmap;\
    (stPpiInfo).usMrru = (pstLcpOption)->mrru;\
    (stPpiInfo).usMru = (pstLcpOption)->mru;\
    (stPpiInfo).ucCode = (pstLcpOption)->ucMhfCode;\
    (stPpiInfo).ucClass = (pstLcpOption)->ucMhfClass;\
    if(((pstLcpOption)->neg_prefixE) && ((pstLcpOption)->pstPrefixE))\
    {\
        for(i = 0; i < (ULONG)MC_PREFIXE_MAX_NUM; i++)\
        {\
            (stPpiInfo).astPrefix[i].ucPrefixValid = (pstLcpOption)->pstPrefixE[i].ucIsUsedFlag;\
            (stPpiInfo).astPrefix[i].ucClass = (pstLcpOption)->pstPrefixE[i].ucClass;\
            (stPpiInfo).astPrefix[i].usPrefixLength = (pstLcpOption)->pstPrefixE[i].ucPrefixELen;\
            (VOID)TCPIP_Mem_Copy((stPpiInfo).astPrefix[i].aucPrefix, PPI_MC_PREFIX_MAX_LEN, \
            (pstLcpOption)->pstPrefixE[i].aucPrefixE, MC_PREFIXE_MAX_STR);\
        }\
    }\
    if((pstLcpOption)->neg_mrru)\
    {\
        (stPpiInfo).ucDiscr_len = (pstLcpOption)->discr_len;\
        (stPpiInfo).ucDiscr_class = (pstLcpOption)->discr_class;\
        (VOID)TCPIP_Mem_Copy((stPpiInfo).discr_addr, PPI_MP_MP_DISCR_MAX_LENGTH,\
                (pstLcpOption)->discr_addr, PPP_MP_DISCR_MAX_LENGTH);\
    }\
    (stPpiInfo).ulMagicnumber = (pstLcpOption)->magicnumber;\
}

#define PPP_EnDropQueue  g_stPPPShellFun.pfPPP_EnDropQue
#define PPP_GetIfByIndex(ulIfIndex) g_pstCoreIFNETFUNTable->pfIF_GetIfByIndex(ulIfIndex)
#define PPP_GetConfigMTU(pIf)    g_pstCoreIFNETFUNTable->pfIF_GetConfigMTU(pIf)
#define PPP_GetIfByFullName(szFull)\
            g_pstCoreIFNETFUNTable->pfIF_GetIfByFullName(szFull)

#define PPP_MP_ISLInput(ulIfIndex, pstMbuf, usProtocol, ulOffset)\
            g_pstPppMpFunTable->pfMP_SonISLInput((ulIfIndex),\
                                                 (pstMbuf), \
                                                 (usProtocol), \
                                                 (ulOffset))

#define PPP_MP_FatherOutput(pstIfnet, pstMbuf, usProtocol)\
            g_pstPppMpFunTable->pfMP_FatherOutput((pstIfnet),\
                                                  (pstMbuf), \
                                                  (usProtocol))

#define PPP_MP_NoPppMultilink(ulIfIndex)\
            g_pstPppMpFunTable->pfMP_NoPppMultilink(ulIfIndex)

#define PPP_MP_GetDiscr(ulIfIndex, pucDiscr_addr, pucClass, pucLength)  \
            g_pstPppMpFunTable->pfMP_GetDiscr(ulIfIndex, pucDiscr_addr, pucClass, pucLength)

#define PPP_MP_IsCfgDiscriminator(ulIfIndex)\
            g_pstPppMpFunTable->pfMP_IsCfgDiscriminator(ulIfIndex)

#define PPP_MP_IsCfgDiscardReq(ulIfIndex) \
            g_pstPppMpFunTable->pfMP_IsCfgDiscardReq(ulIfIndex)

#define PPP_MP_GetGoodSonChannel(ulIfIndex,pulSonIfIndex) \
            g_pstPppMpFunTable->pfMP_GetGoodSonChannel(ulIfIndex,pulSonIfIndex)

#define PPP_MP_GetNeedDownSonChannel(ulIfIndex,ulOurMagicNum,ulHisMagicNum,pulSonIfIndex) \
            g_pstPppMpFunTable->pfMP_GetNeedDownSonChannel(ulIfIndex,ulOurMagicNum,ulHisMagicNum,pulSonIfIndex)
/* End of addition */


#define PPP_MID_PPP     g_stPPPModInfo.ulMID_PPP
#define PPP_SID_ASY_S   g_stPPPModInfo.ulSID_PPP_ASY_S
#define PPP_QUE_MP      (ULONG)g_stPPPModInfo.ulQUE_PPP_MP

#define PPP_QUE_PPPMUX  g_stPPPModInfo.ulQUE_PPPMUX_INPUT

#define PPP_FreePacketInQueForRequest(ulQueID, ulCmd, pData)\
            g_stPPPShellFun.pfQue_FreePacketInQueueForRequest((ulQueID), \
                                                              (ulCmd), \
                                                              (pData))

/********************* PPPģ�����SID��غ�(BEGIN)**********************/
#define SID_COMP_PPP_PACKET_S           ( 1 )
#define SID_COMP_PPP_CB_S               ( 2 )
#define SID_COMP_PPP_L2TPOPTION_S       ( 3 )
#define SID_COMP_PPP_L2TPPARA_S         ( 4 )
#define SID_COMP_PPP_BUILDRUN           ( 5 )
#define SID_COMP_PPP_STAC_BUFFER_S      ( 6 )
#define SID_COMP_PPP_STAC_HASHNODE_S    ( 7 )
#define SID_COMP_PPP_STAC_MINLIST_S     ( 8 )
#define SID_COMP_PPP_STAC_PACKET_S      ( 9 )
#define SID_COMP_PPP_ASY_S              ( 10)
#define SID_COMP_PPP_SYN_S              ( 11)
#define SID_COMP_PPP_MBUF_S             ( 12)
/********************* PPPģ�����SID��غ�(END)**********************/


#define PPI_LCP (PPI_LCPGOTOPTION|PPI_LCPHISOPTION)
#define PPI_IPCP (PPI_IPCPGOTOPTION|PPI_IPCPHISOPTION)
#define PPI_MCP (PPI_MUXCPGOTOPTION|PPI_MUXCPHISOPTION)
#define PPI_MP (PPI_ADD_MLPPP|PPI_DEL_MLPPP)
/* Added by hanna55555, VISPV1R8C01 for ppp-link support ipv6, 2009/3/30 */
#define PPI_IP6CP (PPI_IP6CPGOTOPTION|PPI_IP6CPHISOPTION)
/*End of Added by hanna55555, 2009/3/30 */

#define PPP_LCPECHO_TONP(pstNpLcpEcho, pstFsm) \
{ \
    PPP_LCP_OPTION_S *pstGotOptions; \
    PPP_LCP_OPTION_S *pstHisOptions; \
    UCHAR             *pcTemp; \
    USHORT            usTemp; \
    ULONG             ulMagic; \
    pstGotOptions = &(((PPPLCPINFO_S*)pstFsm->pProtocolInfo)->stGotOptions); \
    pstHisOptions = &(((PPPLCPINFO_S*)pstFsm->pProtocolInfo)->stHisOptions); \
    ulMagic = pstGotOptions->magicnumber; \
    pstNpLcpEcho->ulGotMagicNum = VOS_HTONL(ulMagic); \
    ulMagic = pstHisOptions->magicnumber; \
    pstNpLcpEcho->ulHisMagicNum = VOS_HTONL(ulMagic); \
    pstNpLcpEcho->ulKeepAlive  = VOS_HTONL(pstFsm->ulEchoTimeOutTime / 1000); \
    usTemp = PPP_MAXLOOPSBACK; \
    pstNpLcpEcho->usLoopBackNum = VOS_HTONS(usTemp); \
    pstNpLcpEcho->ucPacketID = pstFsm->ucEchoId; \
    pstNpLcpEcho->ucPppDownNum = (UCHAR)g_stPPPModInfo.ulPPP_DEF_CONFREQS; \
    pstNpLcpEcho->szEchoReq[0] = 0xff; \
    pstNpLcpEcho->szEchoReq[1] = 0x03; \
    pcTemp = (UCHAR *)&pstNpLcpEcho->szEchoReq[2]; \
    usTemp = PPP_LCP; \
    PPP_PUTSHORT(usTemp, pcTemp) \
    pstNpLcpEcho->szEchoReq[4] = ECHOREQ; \
    pstNpLcpEcho->szEchoReq[5] = pstFsm->ucEchoId; \
    pcTemp = (UCHAR *)&pstNpLcpEcho->szEchoReq[6]; \
    usTemp = (LCP_MAGICNUM_LEN + FSM_HDRLEN); \
    PPP_PUTSHORT(usTemp, pcTemp) \
    pcTemp = (UCHAR *)&pstNpLcpEcho->szEchoReq[8]; \
    PPP_PUTLONG(pstGotOptions->magicnumber, pcTemp) \
}

/* �޸����Ӹ�ö�ٶ���ʱ,ע����Ҫ��CHAR *g_stNccPppDownReason[]����Ӧ���޸� */
enum emumPPP_DOWN_DOT
{
    PPP_DOWN_RCR = 1,
    PPP_DOWN_RCA,
    PPP_DOWN_RCN,
    PPP_DOWN_RXJ_SUB_CR,  /* �յ��ܾ�����code reject */
    PPP_DOWN_RXJ_SUB_PR,  /* �յ��ܾ�Э��protocal reject */
    PPP_DOWN_RTR,
    PPP_DOWN_RTA,
    PPP_DOWN_DOT_8,
    PPP_DOWN_DOT_9,
    PPP_DOWN_DOT_10,
    PPP_DOWN_DOT_11,
    PPP_DOWN_DOT_12,
    PPP_DOWN_DOT_13,
    PPP_DOWN_DOT_14,
    PPP_DOWN_DOT_15,
    PPP_DOWN_DOT_16,
    PPP_DOWN_DOT_17,
    PPP_DOWN_DOT_18,
    PPP_DOWN_DOT_19,
    PPP_DOWN_DOT_20,
    PPP_DOWN_DOT_21,
    PPP_DOWN_DOT_22,
    PPP_DOWN_DOT_23,
    PPP_DOWN_DOT_24,
    PPP_DOWN_DOT_25,
    PPP_DOWN_DOT_26,
    PPP_DOWN_DOT_27,
    PPP_DOWN_DOT_28,
    PPP_DOWN_DOT_29,
    PPP_DOWN_DOT_30,
    PPP_DOWN_DOT_31,
    PPP_DOWN_DOT_32,
    PPP_DOWN_DOT_33,
    PPP_DOWN_DOT_34,
    PPP_DOWN_DOT_35,
    PPP_DOWN_DOT_36,
    PPP_DOWN_DOT_37,
    PPP_DOWN_DOT_38,
    PPP_DOWN_DOT_39,
    PPP_DOWN_DOT_40,
    PPP_DOWN_DOT_41,
    PPP_DOWN_DOT_42,
    PPP_DOWN_DOT_43,
    PPP_DOWN_DOT_44,
    PPP_DOWN_DOT_45,
    PPP_DOWN_DOT_46,
    PPP_DOWN_DOT_47,
    PPP_DOWN_DOT_48,
    PPP_DOWN_DOT_49,
    PPP_DOWN_DOT_50,
    PPP_DOWN_DOT_51,
    PPP_DOWN_DOT_52,
    PPP_DOWN_DOT_53,
    PPP_DOWN_DOT_54,
    PPP_DOWN_DOT_55,
    PPP_DOWN_DOT_56,
    PPP_DOWN_DOT_57,
    PPP_DOWN_DOT_58,
    PPP_DOWN_DOT_59,
    PPP_DOWN_DOT_60,
    PPP_DOWN_DOT_61,
    PPP_DOWN_DOT_62,
    PPP_DOWN_DOT_63,
    PPP_DOWN_DOT_64,
    PPP_DOWN_DOT_65,
    PPP_DOWN_DOT_66,/* Added by hanna55555, VISPV1R8C01 for ppp-link support ipv6, 2009/3/20 */
    PPP_DOWN_DOT_67,/* Added by hanna55555, BC3D01643, 2009/6/4 */
    PPP_DOWN_DOT_68,
    PPP_DOWN_DOT_69,
    PPP_DOWN_DOT_70,
    PPP_DOWN_DOT_71,
    PPP_DOWN_DOT_END,
};
/* �޸����Ӹ�ö�ٶ���ʱ,ע����Ҫ��CHAR *g_stNccPppDownReason[]����Ӧ���޸� */

#ifdef __cplusplus
}
#endif

#endif
