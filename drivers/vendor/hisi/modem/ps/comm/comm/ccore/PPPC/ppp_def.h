/************************************************************************
*                                                                      *
*                             ppp_def.h                                *
*                                                                      *
*  Project Code:       VRP3.0                                          *
*  Create Date:        2000/03/27                                      *
*  Author:             Deng Yi Ou                                      *
*  Modify Date:                                                        *
*  Document:                                                           *
*  Function:           PPPģ��˽�к궨��                               *
*  Others:                                                             *
*----------------------------------------------------------------------*
*                                                                      *
*  Copyright 2000-2002 VRP3.0 Team Beijing Institute HuaWei Tech, Inc. *
*                      ALL RIGHTS RESERVED                             *
*                                                                      *
*----------------------------------------------------------------------*
*                                                                      *
*   ����ļ�������PPPģ�����е�˽�к궨��                              *
*                                                                      *
************************************************************************/

#ifndef      _PPP_DEF_H_
#define      _PPP_DEF_H_

#ifdef      __cplusplus
extern "C" {
#endif      /* end of __cplusplus */

/*��ַ������,��socket.h�ṩ����ʱ*/
#ifndef AF_INET
 #define AF_INET 2                      /* internetwork: UDP, TCP, etc. */
#endif

#ifndef AF_IPX
 #define AF_IPX 23                      /* Novell Internet Protocol */
#endif

#ifndef VOS_OutPrintf
#define VOS_OutPrintf       vos_printf
#endif


#define VRP_YES                         (1)
#define VRP_NO                          (0)
/* #define PPPC_ST */

#define VRP_MODULE_LINK_PPP_EAP                 (VRP_NO)
#define VRP_MODULE_STAC                         (VRP_NO)
#define VRP_MODULE_LINK_PPP_CCP                 (VRP_NO)

#define PPP_Malloc(memsize) VOS_MemAlloc(MSPS_PID_PPPC, DYNAMIC_MEM_PT, memsize)
#define PPP_Free(Addr)      VOS_MemFree(MSPS_PID_PPPC, Addr)
#define PPP_MemSet(pBuffer, ucData, Count)     VOS_MemSet(pBuffer, ucData, Count)

#define L2TP_MAX_USER_NUM 20000  /* L2TP�û��� */

#define PPP_MAX_USER_NUM 10
#define PPP_MAX_IMSISEG_NUM 100         /*IMSI��Ȩ�Ŷθ���*/

#define LOCAL_ALLOCATE_IP 0              /* ���ص�ַ���� */
#define RADIUS_ALLOCATE_IP 1            /* Radius���� */

#define PPP_LCP_NEGO_PACKET_MAX_LEN 200

#define PPP_STACK_ERR 0XFF

#define PPP_CB_STATE_FREE 0
#define PPP_CB_STATE_USED 1

#define PPP_FLOWCONTROL_MAX 1

#define PPP_PERF_ADD 0
#define PPP_PERF_SUB 1
#define IPV6_ADD   0
#define IPV6_SUB   1

#define PDSN_DOMAINNAME_LEN 64
#ifndef IPV6_ADDR_LEN
#define IPV6_ADDR_LEN 8         /*IPV6��ַ����(ushort����)*/
#endif
#define IPV6_ADDR_LEN_INTER 4   /* ipv6��ַ�ӿ�id����(ushort����)*/



#define LCP_VERSION_CAPABILITI_C9_IPCP_NAK_HANDLING    0x40   /* ֧��C9 (ipcp-nak-handling) */


#ifdef    __PRODUCT_TYPE_PDSN80
#define PPP_MAX_CCP_USER_NUM g_ulPppCcpMaxUserNum

/* Modified start by liutao 38563 at 2004-09-29 V800R002 for PPPѹ����ֲ */
#define PPP_MAX_VJ_USER_NUM 5000   /*g_ulPppVjMaxUserNum*/
/* Modified end by liutao 38563 at 2004-09-29 V800R002 for PPPѹ����ֲ */


#endif

#define PPP_INDEX_MASK 0xfffff
#define PPP_COMPRESS_2D_MASK 0x20000000
#define PPP_COMPRESS_2F_MASK 0x40000000
#define PPP_ASYN_MASK 0x80000000

#define M_PPPCOMPRESS_VJ_FLAG 0x01
#define M_PPPCOMPRESS_MPPC_FLAG 0x02
#define M_PPPCOMPRESS_STAC_FLAG 0x04
#define PPP_RECODE_USERFULL 2

enum PPPC_TIMEOUT_MSG_TYPE_ENUM
{
    PPPC_CHAP_CHALLENGE_RESEND_TIMER        = 0,            /* CHAP Challenge�ش���ʱ�� */
    PPPC_CHAP_RESPONSE_RESEND_TIMER         = 1,            /* CHAP Response�ش���ʱ�� */
    PPPC_EAP_SEND_AAA_AUTH_REQ_TIMER        = 2,            /* EAP���ͼ�Ȩ����ʱ��ʱ�� */
    PPPC_EAP_SEND_EAP_REQ_TIMER             = 3,            /* EAP����EAP������Ϣ */
    PPPC_LCP_SEND_ECHO_REQ_TIMER            = 4,            /* LCP����Echo Req��ʱ�� */
    PPPC_PAP_WAIT_FOR_REQ_TIMER             = 5,            /* PAP�ȴ��Զ˷�����֤����ʱ�� */
    PPPC_PAP_SEND_AUTH_REQ_TIMER            = 6,            /* PAP���õȴ���֤��ʱ��ʱ�� */
    PPPC_NEGO_TIMEOUT_TIMER                 = 7,            /* Э�̹��̳���2������ֹЭ�̣���ֹPPP״̬��������ѭ�� */
    PPPC_CCP_TIMEOUT_TIMER                  = 8,            /* CCP��ʱ��ʱ�� */
    PPPC_FSM_RETRANSMIT_TIMER               = 9,            /* FSM�ش���ʱ�� */
    PPPC_HRPD_PA_AGENT_RLP_RSP_TIMER        = 10,           /* PA�ش���ʱ�� */
    PPPC_AWAKE_SELF_REACH_MAX_PROC_TIMER    = 11,           /* ����������ﵽ����ʱ�˳�PPPC�����ڻ����Լ� */
    PPPC_HDLC_FRM_OUTPUT_SPACE_ALLOC_FAIL   = 12,           /* HDLC�����װĿ�Ŀռ�ʧ�ܶ�ʱ������ */

    PPPC_TIMER_BUFF
};
typedef VOS_UINT32 CTTF_1X_FMAC_STATISTIC_MUX1_FCH_ENUM_UINT32;


/** ****************************************************************************
 * Name        : PPPC_RAT_MODE_ENUM_UINT8
 *
 * Description :
 *******************************************************************************/
enum PPPC_RAT_MODE_ENUM
{
    PPPC_RAT_MODE_1X               = 0x00,
    PPPC_RAT_MODE_HRPD             = 0x01,
    PPPC_RAT_MODE_EHRPD            = 0x02,
    PPPC_RAT_MODE_BUTT             = 0x03
};
typedef VOS_UINT8 PPPC_RAT_MODE_ENUM_UINT8;


enum enumPppSoftPara
{
    M_SPM_L2TP_IMSI_FORMAT =    534,/* ����ο���L2TP���������Ϣ��Я����IMSI��Ϣ��ʽ,ֵΪ0ʱ����Ϣ��Я����10λ,ֵΪ1ʱ��ȫ�� */

    M_SPM_PPPCOMPRESS_LIMIT = 536,

    M_SPM_PPPVJ_LIMIT = 537,

    M_SPM_PDSN_MATCH_CONSTRUCTDOMAIN = 562, /* �û����в�Я������Ϣʱ�Ƿ���Ҫƥ�䵽PDSN������,���ֵΪ0ʱ,��ƥ�乹����;����,ƥ�� */
    M_SPM_PDSN_CHAPRESPONSE_USERNAME = 567,  /* Chap Response��Ϣ���Ƿ��������û�����,���ֵΪ0ʱ,��������;����,������ */
    M_SPM_PDSN_IPCP_IPADDR = 571, /* AP8D06991:IPCPЭ�̽׶�PDSN���͵�Request��Ϣ��Я����IP��ַ, �����Ϊ1ʱ��2.2.2.2, Ϊ0ʱ��RP�߼��ڵ�ַ */
    M_SPM_PPPCOMPRESS_FLAG = 577,


    M_SPM_LCP_TRANSFER = 585,
    M_SPM_AUTH_TRANSFER = 586,
    M_SPM_IPCP_TRANSFER = 587,
};

/*********** ��Ϣ��������**************/
enum enumTrace
{
    PPP_TRC_LCP_CONFREQ = 1,
    PPP_TRC_LCP_CONFACK,
    PPP_TRC_LCP_CONFNAK,
    PPP_TRC_LCP_CONFREJ,
    PPP_TRC_LCP_TERMREQ,
    PPP_TRC_LCP_TERMACK,
    PPP_TRC_LCP_CODEREJ,
    PPP_TRC_LCP_PROTREJ,
    PPP_TRC_IPCP_CONFREQ, /*0x9*/
    PPP_TRC_IPCP_CONFACK,
    PPP_TRC_IPCP_CONFNAK,
    PPP_TRC_IPCP_CONFREJ,
    PPP_TRC_IPCP_TERMREQ,
    PPP_TRC_IPCP_TERMACK,
    PPP_TRC_IPCP_CODEREJ,
    PPP_TRC_IPCP_PROTREJ,
    PPP_TRC_PAP_AUTHREQ, /*0x11*/
    PPP_TRC_PAP_AUTHACK,
    PPP_TRC_PAP_AUTHNAK,
    PPP_TRC_CHAP_CHALLENGE,
    PPP_TRC_CHAP_RESPONSE,
    PPP_TRC_CHAP_SUCCSSS,
    PPP_TRC_CHAP_FAILURE,
    PPP_TRC_SCP_CONFREQ, /*0x18*/
    PPP_TRC_SCP_CONFACK,
    PPP_TRC_SCP_CONFNAK,
    PPP_TRC_SCP_CONFREJ,
    PPP_TRC_SCP_TERMREQ,
    PPP_TRC_SCP_TERMACK,
    PPP_TRC_SCP_CODEREJ,
    PPP_TRC_SCP_PROTREJ,
    PPP_TRC_SCP_RESETREQ,
    PPP_TRC_SCP_RESETACK,
    PPP_TRC_LCP_ECHOREQ,
    PPP_TRC_LCP_ECHOREP,

    PPP_TRC_LCP_INDENTI,
    PPP_TRC_LCP_DISCREQ, /* 0x25*/
    PPP_TRC_IPV6CP_CONFREQ, /*0x26*/
    PPP_TRC_IPV6CP_CONFACK,
    PPP_TRC_IPV6CP_CONFNAK,
    PPP_TRC_IPV6CP_CONFREJ,
    PPP_TRC_IPV6CP_TERMREQ,
    PPP_TRC_IPV6CP_TERMACK,
    PPP_TRC_IPV6CP_CODEREJ,
    PPP_TRC_IPV6CP_PROTREJ,/*0X2D*/
    PPP_TRC_LCP_VERSION_CAP,

    PPP_TRC_EAP_REQUEST,  /* 0X2F */
    PPP_TRC_EAP_RESPONSE,
    PPP_TRC_EAP_SUCCSSS,
    PPP_TRC_EAP_FAILURE,

    PPP_TRC_VSNCP_CONFREQ, /*0x33*/
    PPP_TRC_VSNCP_CONFACK,
    PPP_TRC_VSNCP_CONFNAK,
    PPP_TRC_VSNCP_CONFREJ,
    PPP_TRC_VSNCP_TERMREQ,
    PPP_TRC_VSNCP_TERMACK,
    PPP_TRC_VSNCP_CODEREJ,
    PPP_TRC_VSNCP_PROTREJ,
    PPP_TRC_INVALIDPACKET
};

/*PPPģ���ڴ���MIPAgentҵ������У�
ͬFA���н���ʱ�����ļ����ؼ�״̬ */
 #define PPP_MIPAGENT_NULL 0
 #define PPP_MIPAGENT_WAITFA 1
 #define PPP_MIPAGENT_FAOK 2

 #define PPP_MIPAGENT_LICCHECK 3  /*Add by z60016360 at 2007-05-25 for BYHD14247*/
/*����MIPAgentʹ��״̬*/
 #define PPP_MIPAGENT_ENABLE 1
 #define PPP_MIPAGENT_DISABLE 0

/*���屾�ػ���AAA�����ú�*/
 #define PPP_MIPAGENT_LOCALCONF 0
 #define PPP_MIPAGENT_AAACONF 1

/*����(����mipagent�û�)pppģ����faģ�鷢��mipע��ʱ��
    �ȴ�Ӧ���ʱ����(10��)*/
 #define PPP_FA_MIPAGENT_TIMEINTVL 15

 #define RM_MAX_APN_NUM MAX_APN_NUM
 #define MAX_APN_NUM 3000


/*�����û�ģʽ:�ս�ģʽ��������ģʽ*/
#define PPP_USERMODE_TERMI 0
#define PPP_USERMODE_RELAY 1

/*����ppp�ͻ���ģʽ*/
#define PPP_CLIENT_TRUE 1
#define PPP_CLIENT_FALSE 0

/*�����Ƿ���Э�̱�־*/
#define PPP_RENEGOTIATE_TRUE 1
#define PPP_RENEGOTIATE_FALSE 0


 #define PPP_USERLOG_MIPATOSIP 0      /*mipagent�û�����ʧ�ܣ������sip�û�*/
 #define PPP_USERLOG_MIP 1                 /*mip�û�����*/
 #define PPP_USERLOG_MIPAGENT 2      /*mipagent�û�����*/


#define   PPPCFG_AUTHMODE_DEFAULT 1

#define   PPPCFG_AUTHMODE_NONE 0
#define   PPPCFG_AUTHMODE_NEGO 2
#define   PPPCFG_HOSTNAME_DEFAULT_PDSN "pdsn"
#define   PPPCFG_MRU_DEFAULT 1500
#define   PPPCFG_TIMEOUT_DEFAULT 1
#define   PPPCFG_AUTHOPTION_DEFAULT 0/* Added by LHT04029 at 2006-06-16 R2C02B025 for BYHD10294 */

/* added by gxf 20030215 */
/************************* �¼�λ *****************************/
#define PPP_NEGO_EVENTBIT 0x0001
#define PPP_AAA_EVENTBIT 0x0002
#define PPP_DHCP_EVENTBIT 0x0004
#define PPP_CCP_EVENTBIT 0x0008 /*WGGSN_B03_L2TP_PPPC_COMP*/
#define PPP_GSPC_MSG_EVENTBIT 0x0010 /* Added by liutao 38563 at 2004-09-21 V800R002 for ��ֲ */

#define PPP_COMPRESS_MSG_EVENTBIT 0x0200

 #define PPP_A11_NOTIFY_PPP_EVENTBIT 0x0020 /*A11֪ͨPPPC up��down�¼�*/
 #define PPP_LICENSE_EVENTBIT 0x0100   /*0x0020���¼�λ��PPPMģ��ռ����*/

#define PPP_LAP_NOTIFY_PPP_EVENTBIT 0x0040 /*LAP2֪ͨPPPC ����IP��ַ*/
#define PPP_L2TP_NOTIFY_PPP_EVENTBIT 0x0080 /*GTPC֪ͨPPPC up��down�¼�*/
#define PPP_INNERMSG_NOTIFY_PPP_EVENTBIT 0x0100
#define DIAM_AUTH_PPP_EVENT 0x0400

/*#define PPP_FA_EVENTBIT     0x0020 *//*����5λ��û������20λ��
                                       ��Ҫ�ǿ��ǵ�������ǰ���������*/

#define PPP_FA_EVENTBIT (1 << 21)     /*�궨��, PPP����FA��Ϣʱ���¼�λ*/
#define PPPC_SPUA_EV (1 << 22)

#define PPP_PCRFC_EVENTBIT (1 << 23 )  /*ppp����PCRFC��Ϣʱ���¼�λ*/

#define PPPC_MIPLIC_EV (1 << 23)  /* Add by z60016360 at 2007-05-25 V800R005C02B010 for BYHD14247 */


/************************* ��ַ���䷽ʽ *****************************/


/************************* �����йصĺ� *****************************/
#define PPP_MAXAUTHFAILTIMES 3
#define PPP_MAXTRANSFAILEDTIMES 5
#define PPP_MAX_CALLBACK_INFO_LEN 20
#define PPP_DEF_MP_FRAGS 4
#define PPP_DEF_MP_BINDS 4

#define PPP_GETCOUNTPERTIME 200   /* һ�ε�����ദ��ı����� */
#define PPP_QUE_REGLEN 75    /*  ���е�ȱʡע�᳤��  shiyong 2000/10/10  */

#define PPP_ECHOTIMEOUT 10000 /* ten seconds in milliseconds */
#define PPP_ECHOSENDTIME PPP_ECHOTIMEOUT /* same as echo timeout */

#define PPP_MAXMRU 2000    /* maximum MRU */
#define PPP_DEFMRU 1500    /* default MRU */
#define PPP_MINMRU 64      /* minimum MRU */

#define PPP_DEFTIMEOUTTIME 1000L   /* Timeout time in milliseconds */
#define PPP_MAXTIMEOUTTIME 10000L  /* Timeout time in milliseconds */

#define PPP_DEFMAXCONFREQS 15     /* Maximum Configure-Request transmissions */

#define PPP_MAXTERMREQS 5      /* Maximum Terminate-Request transmissions */
#define PPP_MAXNAKLOOPS 10      /* Maximum number of nak loops */
#define PPP_MAXLOOPSBACK 10      /* Maximum number of nak loops */
#define PPP_DEF_RESETTIME 30000L

#define PPP_DEFMRRU 1500
#define PPP_MINMRRU 128         /* No MRUs below this is allowed */

#ifndef PPP_MAXUSERNAMELEN
#define PPP_MAXUSERNAMELEN 128    /*32*/
#endif
#define PPP_MAXUSERPWDLEN 128

/*����û���*/
#define MP_MAX_USER_NUM 50
#define MAX_HOT_SLOT_USER_NUM 20  /*�Ȳ�ε�����·��û���Ŀ*/
/*�û�������*/
#define MP_USERNAME_LEN 32

/*add by huzhiyong for new development 2002/01/21 */
#define NOAUTH_NODISCR 1
#define DISCR_NOAUTH 2
#define NODISCR_AUTH 3
#define DISCR_AUTH 4

#define PPP_MAXCALLBACKDIALERSTRINGLEN 64

/* modified by gxf for GGSN80 20030213 */
/* Added start by liutao 38563 at 2004-09-24 V800R002 for PPPѹ����ֲ */
#define PPPCOMP_PKTID_NOT_INC 0x01   /* ������idֵ */
#define PPPCOMP_PKTID_INC 0x02  /* ����idֵ */
#define PPPCOMP_MPPC 1
#define PPPCOMP_LZS0 2
#define PPPCOMP_LZS1 3
/* Added end by liutao 38563 at 2004-09-24 V800R002 for PPPѹ����ֲ */
#define PPP_DEFAULT_ACCM 0x0  /* ȱʡͬ�첽ת���ַ��������п����ֶ�ת�� */
/* Added start by liujianhui 61463 at 2008-03-31 PDSN V9R7 Demo for ��ֲ */

#define CALL_FROMID_LENTH  20

#ifdef __PRODUCT_TYPE_PDSN80
typedef enum
{
    LICE_LIMIT_ITEM_USER_NUM = 0,
    LICE_LIMIT_ITEM_MIP_NUM  = 1,
    LICE_LIMIT_ITEM_PPS_NUM  = 2,
    LICE_LIMIT_ITEM_COMPRESS = 3,
    LICE_LIMIT_ITEM_TRACK  = 4,
    LICE_LIMIT_ITEM_LISTEN = 5,

    /* LICE_LIMIT_ITEM_BSN					= 6,*//*license����BSN��Դ Added by liuxiaojie 60004253 at 2006-05-16 V800R005C01B010 for License */
    /* Added start by wufang 60019246 at 2007-04-16 PDSN9660V800R5C02 for License */
    LICE_LIMIT_ITEM_EVDO_NUM = 6,
    LICE_LIMIT_ITEM_EVDO_A10_NUM = 7,
    /* Added end by wufang 60019246 at 2007-04-16 PDSN9660V800R5C02 for License */
    /* Modified start by wufang 60019246 at 2007-04-16 PDSN9660V800R5C02 for License */
    LICE_LIMIT_ITEM_MIPAGENT = 8,               /*license����MIP Agent���� Added by liuxiaojie 60004253 at 2006-05-16 V800R005C01B010 for License */

    LICE_LIMIT_ITEM_IPSec = 9,
    LICE_LIMIT_ITEM_LMT = 10,
    /* Modified end by wufang 60019246 at 2007-04-16 PDSN9660V800R5C02 for License */
    /*LICE_LIMIT_ITEM_BUTT*/ /* <=M_LIC_MAX_LIMIT_ITEM_NUM */
} E_LIC_LIMIT_ITEM_TYPE;
#endif
/* Added end by liujianhui 61463 at 2008-03-31 PDSN V9R7 Demo for ��ֲ */
/************************* �����йصĺ� *****************************/

/************************* �¼�ö�ٱ��� *****************************/
/* ������ں˱��¼� */
enum enumPPP_EVENT_ShellToCore
{
    PPPISLUP = 0,
    PPPISLDOWN,
    PPPISLRENEGO,
    PPPCHGIPADDR,
    PPPADDIPADDR,
    PPPDELIPADDR,
    PPPCHGIPXADDR,
    PPPADDIPXADDR,
    PPPDELIPXADDR,
    PPPADDIPISIS,
    PPPDELIPISIS,
    PPPSTCEND        /* added by gxf 200300306   end flag of enumPPP_EVENT_ShellToCore */
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
    PPP_EVENT_FSM_RXR,

    PPP_EVENT_FSM_BUTT
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
    PPP_EVENT_IPCPFINISHED,  /*6*/
    PPP_EVENT_IPCPSTARTING,
    PPP_EVENT_IPV6CPUP,
    PPP_EVENT_IPV6CPDOWN,
    PPP_EVENT_IPV6CPFINISHED,
    PPP_EVENT_IPV6CPSTARTING,   /*11*/
    PPP_EVENT_CCPUP,
    PPP_EVENT_CCPDOWN,
    PPP_EVENT_CCPFINISHED,
    PPP_EVENT_CCPSTARTING,
    PPP_EVENT_PAPSUCCESS,     /*16*/
    PPP_EVENT_PAPFAILED,
    PPP_EVENT_CHAPSUCCESS,
    PPP_EVENT_CHAPFAILED,
    PPP_EVENT_RECHALLENGE,
    PPP_EVENT_OSICPUP,       /*21*/
    PPP_EVENT_OSICPDOWN,
    PPP_EVENT_OSICPFINISHED,
    PPP_EVENT_OSICPSTARTING,
    PPP_EVENT_MPLSCPUP,
    PPP_EVENT_MPLSCPDOWN,
    PPP_EVENT_MPLSCPFINISHED,
    PPP_EVENT_MPLSCPSTARTING,
    PPP_EVENT_EAPFAILED,
    PPP_EVENT_EAPSUCCESS,
    PPP_EVENT_EAPREAUTH,     /*31*/
    PPP_EVENT_VSNCPUP,
    PPP_EVENT_VSNCPDOWN,
    PPP_EVENT_VSNCPFINISHED,
    PPP_EVENT_VSNCPSTARTING,

    PPP_EVENT_MAXEVENT
};

/* �ں�����Ǳ����¼� */
enum enumPPP_EVENT_CoreToShell
{
    PPP_LCP_UP = 0,    /* added by gxf 20030217 */
    PPP_LCP_DOWN,
    PPP_IPCP_UP,
    PPP_IPCP_DOWN,
    PPP_IPV6CP_UP,
    PPP_IPV6CP_DOWN,
    PPP_CCP_UP,
    PPP_CCP_DOWN,
    PPP_GET_IPADDR,
    PPP_GET_PEERIPADDR,
    PPP_FREE_PEERIPADDR,
    PPP_IPXCP_UP,
    PPP_IPXCP_DOWN,
    PPP_GET_IPXADDR,
    PPP_SET_ACCM,
    PPP_OSICP_UP,
    PPP_OSICP_DOWN,
    PPP_OSICP_ENABLE,
    PPP_SDBNOTIFY_LICCHECK,
    PPP_VSNCP_UP,
    PPP_VSNCP_DOWN,
    PPP_EVENT_CTSEND    /* added by gxf 200300306   end flag of enumPPP_EVENT_CoreToShell */
};

/* added by gxf for GGSN80 20030212 */


/* PPP RPC ͨ����Ϣ */
enum enumPPP_IPC_MSG
{
    PPP_HOT_INSERT_SLOT,
    PPP_HOT_INSERT_POINTER
};

/************************* �¼�ö�ٱ��� *****************************/

/* ������Ϣ�����,�Ժ�Ӧ�滻�� */
#define PPP_LOG_INFO 0
#define PPP_LOG_WARNING 1
#define PPP_LOG_NOTICE 2
#define PPP_LOG_ERROR 3

/**************************** PPP�׶� *********************************/
enum enumPppPhase
{
    PPP_PHASE_DEAD = 0,       /* 0   Dead Phase */
    PPP_PHASE_ESTABLISH,      /* 1   Establish Phase */
    PPP_PHASE_AUTHENTICATE,   /* 2   Authenticate Phase */
    PPP_PHASE_CBCP,           /* 3   Cbcp Phase */
    PPP_PHASE_NETWORK,        /* 4   Network Phase */
    PPP_PHASE_TERMINATE       /* 5   Terminate Phase */
};

/**************************** PPP�׶� *********************************/

/********************** PPP���ĸ����ֳ��� *****************************/
#define FSM_HDRLEN 4
#define PPP_HDRLEN 4   /* octets for standard ppp header */
#define PPP_FCSLEN 2   /* octets for FCS */


#define PPP_HDR_CODE_LEN 1

/*
 |--------- PPP_HDRLEN ----------|--------- FSM_HDRLEN ----------|
    0       1       2       3       4       5       6       7
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 |   ff  |   03  |    protocol   |  code |   ID  |     length    |  data...
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */

/* ��Э��ͨ�õ�Э��ѡ��� */
#define PPP_CILEN_VOID 2
#define PPP_CILEN_SHORT 4   /* PPP_CILEN_VOID + sizeof(short) */
#define PPP_CILEN_LONG 6   /* PPP_CILEN_VOID + sizeof(long) */

/* ��Э��ͨ�õĻ�ȡЭ��ѡ���(cilen)�� */
#define PPP_LENCIVOID(neg) (neg ? PPP_CILEN_VOID : 0)
#define PPP_LENCISHORT(neg) (neg ? PPP_CILEN_SHORT : 0)
#define PPP_LENCILONG(neg) (neg ? PPP_CILEN_LONG : 0)

/********************** PPP���ĸ����ֳ��� *****************************/

/************************ IPCPģ�� *****************************/
/* ��Э��ѡ��� */
#define PPP_CILEN_COMPRESS 4   /* min length for compression protocol opt. */
#define PPP_CILEN_VJ 6   /* length for RFC1332 Van-Jacobson opt. */
#define PPP_CILEN_ADDR 6   /* new-style single address option */
#define PPP_CILEN_ADDRS 10   /* old-style dual address option */
/************************ IPCPģ�� *****************************/

/************************ IPXCPģ�� *****************************/
/* ��Э��ѡ��� */
#define PPP_CILEN_NODE 8   /* length for IPX Node Number opt. */
#define PPP_CILEN_ROUTING 4   /* min length for routing protocol opt. */
#define PPP_CILEN_ROUTER 3   /* min length for compression protocol opt. */
/************************ IPXCPģ�� *****************************/

/************************* �������� **********************************/
#ifndef PPP_MP
#define PPP_MP 0x003d
#endif
#ifndef PPP_IP
#define PPP_IP 0x0021
#endif
#ifndef PPP_IP6
#define PPP_IP6 0x0057
#endif
#ifndef PPP_OSI
#define PPP_OSI 0x0023
#endif
#ifndef PPP_IPX
#define PPP_IPX 0x002b
#endif

#ifndef _lint
#if (VRP_MODULE_IP_MPLS_SOFTFW == VRP_YES)
 #define PPP_MPLS 0x0281
 #define PPP_MPLS_MCAST 0x0282
#endif
#endif
#define PPP_LCP_DEACTIVE 0xFFFF      /* ���ⶨ�壬Ϊ����������Э�� */
#define PPP_IPCP_DEACTIVE 0xFFFE     /* ���ⶨ�壬Ϊ����������Э�� */
#define PPP_IPV6CP_DEACTIVE 0xFFFD   /* ���ⶨ�壬Ϊ����������Э�� */
#define PPP_VJ_COMP 0x002d
#define PPP_VJ_UNCOMP 0x002f
#define PPP_VJ_COMP_OLD 0x0037
#define PPP_COMP 0x00fd      /* compressed packet */
#define PPP_IPCP 0x8021      /* IP Control Protocol */
#define PPP_VSNCP  0x805B
#define PPP_IPV6CP 0x8057      /* IPv6 Control Protocol */
#define PPP_IPXCP 0x802b      /* IPX Control Protocol */
#define TELEBIT_COMPRESS 0x0002      /* Telebit Compressed IPX */
#define SHIVA_COMPRESS 0x0235      /* Shiva Compressed NCP/IPX */
#define PPP_CCP 0x80fd      /* Compression Control Protocol */
#define PPP_LCP 0xc021      /* Link Control Protocol */
#define PPP_PAP 0xc023      /* Password Authentication Protocol */
#define PPP_LQR 0xc025      /* Link Quality Report protocol */
#define PPP_CHAP 0xc223      /* Cryptographic Handshake Auth. Protocol */
#define PPP_EAP 0xc227      /* Extensible Auth. Protocol  */
#define PPP_BCP 0x8031      /* ppp bridge control protocol */
#define PPP_BP 0x0031     /* PPP bridge protocol*/
#define PPP_SCCP 0x80fd      /* ppp compress control protocol on single link*/
#define PPP_SCP 0x00fd      /* ppp compress protocol on single link */
#define PPP_MCCP 0x80fb      /* ppp compress control protocol on multilink  */
#define PPP_MCP 0x00fb      /* PPP compress protocol on multilink */
#define PPP_SECP 0x8053      /* ppp encrypt control protocol on single link */
#define PPP_SEP 0x0053      /* PPP encrypt protocol on single link */
#define PPP_MECP 0x8055      /* PPP encrypt control protocol on multilink */
#define PPP_MEP 0x0055      /* PPP encrypt protocol on multilink */
#define PPP_BACP 0xc02b      /* Bandwidth Allocation Control Protocol */
#define PPP_BAP 0xc02d      /* Bandwidth Control Protocol */
#define PPP_CBCP 0xc029      /* Callback Control Protocol */
#define PPP_OSICP 0x8023      /* OSI Control Protocol */
#define PPP_OSI_NPDU 0x0023      /* OSI NPDU(Network Protocol Data Unit) Protocol */
#define PPP_MPLSCP 0x8281      /* MPLS Control Protocol */
#define PPP_MPLS_UNICAST 0x0281      /* MPLS unicast packet */
#define PPP_MPLS_MULTICAST 0x0283      /* MPLS multicast packet */
/************************* �������� **********************************/

/*
 * Significant octet values.
 */
#define PPP_ALLSTATIONS 0xff    /* All-Stations broadcast address */
#define PPP_UI 0x03        /* Unnumbered Information */
#define PPP_FLAG 0x7e        /* Flag Sequence */
#define PPP_ESCAPE 0x7d        /* Asynchronous Control Escape */
#define PPP_TRANS 0x20        /* Asynchronous transparency modifier */

/* Ԥ���ı���ͷ��С */
#define PPP_RESERVED_PACKET_HEADER 40
#define PPP_DEFAULT_NEGO_PACKET_LEN 3000

#ifndef _lint
/* MPͨ������ */
#if (VRP_MODULE_LINK_PPP_MP == VRP_YES)
 #define PPP_MP_NONE 0                  /* ����MP */
 #define PPP_MP_SUBCHANNEL 1            /* MP��ͨ�� */
 #define PPP_MP_FATHER 2                /* MP��ͨ�� */
 #define PPP_MP_TEMPLATE 3              /* MPģ�� */
#endif
#endif

/*************************** ���Ķ���д�� ****************************/
/* �ƶ�ָ�뱨�� */
#define PPP_INCPTR(n, cp) ((cp) += (n))
#define PPP_DECPTR(n, cp) ((cp) -= (n))

/*
 * Inline versions of get/put char/short/long.
 * Pointer is advanced; we assume that both arguments
 * are lvalues and will already be in registers.
 * cp MUST be UCHAR *.
 */

#define PPP_GETCHAR(c, cp) { \
        (c) = *(cp); \
        (cp)++; \
    }
#define PPP_PUTCHAR(c, cp) { \
        *(cp) = (UCHAR) (c); \
        (cp)++; \
    }

/*
 #define PPP_GETSHORT(s, cp) { \
    (s) = (USHORT)(*(cp) << 8); \
    (cp) ++ ; \
    (s) |= (USHORT)(*(cp)); \
    (cp) ++ ; \
}

 #define PPP_PUTSHORT(s, cp) { \
 *(cp) = (UCHAR) ((s) >> 8); \
    (cp) ++ ; \
 *(cp) = (UCHAR) (s); \
    (cp) ++ ; \
}
 */
#define PPP_GETSHORT(s, cp) { \
        USHORT usTemp = 0; \
        VOS_MemCpy((void *)&usTemp, (void *)cp, sizeof(USHORT)); \
        (s)   = VOS_NTOHS(usTemp); \
        (cp) += 2; \
    }

#define PPP_PUTSHORT(s, cp) { \
        USHORT usTemp = VOS_HTONS(s); \
        VOS_MemCpy((void *)cp, (void *)&usTemp, sizeof(USHORT)); \
        (cp) += 2; \
    }

#define PPP_GETLONG(l, cp) { \
        ULONG ulTemp = 0; \
        VOS_MemCpy((void *)&ulTemp, (void *)cp, sizeof(ULONG)); \
        (l) = VOS_NTOHL(ulTemp); \
        cp += 4; \
    }
#define PPP_PUTLONG(l, cp) { \
        ULONG ulTemp = VOS_HTONL(l); \
        VOS_MemCpy((void *)cp, (void *)&ulTemp, sizeof(ULONG)); \
        cp += 4; \
    }

/* add by luofang ��ƽ̨ */
#define PPP_GETADDR(l, cp) { \
    VOS_MemCpy((void *)&l, (void *)cp, sizeof(ULONG));\
    cp += 4 ; \
}
#define PPP_PUTADDR(l, cp) { \
    VOS_MemCpy((void *)cp, (void *)&l, sizeof(ULONG));\
    cp += 4 ; \
}
/* end add by luofang ��ƽ̨ */



#define PPP_GETCHARPTR(c, cp, len) { \
        VOS_MemCpy((void *)c, (void *)cp, len); \
        cp += len; \
    }
#define PPP_PUTCHARPTR(auc, cp, len) { \
        VOS_MemCpy((void *)cp, (void *)auc, len); \
        cp += len; \
    }

/*
 * PPP_MAKEHEADER - Add Header fields to a packet.
 */
#define PPP_MAKEHEADER(p, t) \
    { \
        PPP_PUTCHAR(PPP_ALLSTATIONS, p); \
        PPP_PUTCHAR(PPP_UI, p); \
        PPP_PUTSHORT(t, p); \
    }

/*************************** ���Ķ���д�� ****************************/

/*
������֧��PPP�Ľӿ�ģ����ע��ӿ����
����������Ҫע��������֧��PPP�Ľӿ��£�
����ṩһ����ͳһ������֧��PPP��ģ����ע
�����
ppp multilink max-bind���ʹ������ꡣ
�������ֻע����VTģ���¡�
 */
#define PPP_InstallInterfaceCmd(szCmdDefine, \
                                ulCmdLevel, \
                                NewCmdDesVec, \
                                ExtendCmdElementVec, \
                                InteractiveProc, \
                                ulTimeOutFlag) \
    { \
        /* ��ͬ�첽������ע������*/ \
        (VOID)CLI_InstallCmd(CLI_CMD_TEMPLET_IF_SERIAL, \
                             szCmdDefine, \
                             ulCmdLevel, \
                             NewCmdDesVec, \
                             ExtendCmdElementVec, \
                             InteractiveProc, \
                             ulTimeOutFlag); \
        /* ���첽������ע������*/ \
        (VOID)CLI_InstallCmd(CLI_CMD_TEMPLET_IF_ASYNC, \
                             szCmdDefine, \
                             ulCmdLevel, \
                             NewCmdDesVec, \
                             ExtendCmdElementVec, \
                             InteractiveProc, \
                             ulTimeOutFlag); \
        /* ���첽������ע������*/ \
        (VOID)CLI_InstallCmd(CLI_CMD_TEMPLET_IF_DIALER, \
                             szCmdDefine, \
                             ulCmdLevel, \
                             NewCmdDesVec, \
                             ExtendCmdElementVec, \
                             InteractiveProc, \
                             ulTimeOutFlag); \
        /* ���첽������ע������*/ \
        (VOID)CLI_InstallCmd(CLI_CMD_TEMPLET_IF_BRI, \
                             szCmdDefine, \
                             ulCmdLevel, \
                             NewCmdDesVec, \
                             ExtendCmdElementVec, \
                             InteractiveProc, \
                             ulTimeOutFlag); \
        /* ���첽������ע������*/ \
        (VOID)CLI_InstallCmd(CLI_CMD_TEMPLET_VIRTUAL_TEMPLATE, \
                             szCmdDefine, \
                             ulCmdLevel, \
                             NewCmdDesVec, \
                             ExtendCmdElementVec, \
                             InteractiveProc, \
                             ulTimeOutFlag); \
        /* ��POS����ע������*/ \
        (VOID)CLI_InstallCmd(CLI_CMD_TEMPLET_IF_POS, \
                             szCmdDefine, \
                             ulCmdLevel, \
                             NewCmdDesVec, \
                             ExtendCmdElementVec, \
                             InteractiveProc, \
                             ulTimeOutFlag); \
        /* ��AUX����ע������*/ \
        (VOID)CLI_InstallCmd(CLI_CMD_TEMPLET_IF_AUX, \
                             szCmdDefine, \
                             ulCmdLevel, \
                             NewCmdDesVec, \
                             ExtendCmdElementVec, \
                             InteractiveProc, \
                             ulTimeOutFlag); \
    }

/**********************/
/* ״̬��ģ��ĺ궨�� */
/**********************/

/***************************** codeֵ ********************************/

/*
 *  CP (LCP, IPCP, etc.) codes.
 */
#define VEDRSPEC 0  /* Vendor Specific*/
#define CONFREQ 1   /* Configuration Request */
#define CONFACK 2   /* Configuration Ack */
#define CONFNAK 3   /* Configuration Nak */
#define CONFREJ 4   /* Configuration Reject */
#define TERMREQ 5   /* Termination Request */
#define TERMACK 6   /* Termination Ack */
#define CODEREJ 7   /* Code Reject */
#define PROTREJ 8   /* Protocol-Reject */
/***************************** codeֵ ********************************/
#define VENDORSPECIFIC_INDICTE 2  /* Vendor Specific �汾/����ָʾ����*/
#define VENDORSPECIFIC_RESPONSE 3  /* Vendor Specific �汾/������Ӧ����*/

typedef enum
{
    PDSN_PPP_IPTYE_IPV4 = 1,
    PDSN_PPP_IPTYE_IPV6    ,
    PDSN_PPP_IPTYE_ALL,        /*ͬʱ֧��ipv4 ipv6��ַЭ�̣��Ǽ�Ȩ��aaa��С��ʱĬ�϶�֧��*/
    PDSN_PPP_IPTYE_CMIPV4 = 4,
    PDSN_PPP_IPTYE_PMIPV4 = 0X10
} PDSN_PPP_IPTYE;


/****************************** ״̬ *********************************/
/* FSM states */
enum ePppState
{
    PPP_STATE_INITIAL = 0,  /* 0   Down, hasn't been opened */
    PPP_STATE_STARTING,     /* 1   Down, been opened */
    PPP_STATE_CLOSED,       /* 2   Up, hasn't been opened */
    PPP_STATE_STOPPED,      /* 3   Open, waiting for down event */
    PPP_STATE_CLOSING,      /* 4   Terminating the connection, not open */
    PPP_STATE_STOPPING,     /* 5   Terminating, but open */
    PPP_STATE_REQSENT,      /* 6   We've sent a Config Request */
    PPP_STATE_ACKRCVD,      /* 7   We've received a Config Ack */
    PPP_STATE_ACKSENT,      /* 8   We've sent a Config Ack */
    PPP_STATE_OPENED,       /* 9   Connection available */

    PPP_STATE_BUTT
};


/* �¼�(Events)�Ͷ���(Actions)�Ĵ���
   �����¼���
   ÿ���¼�һ������,+��-���¼�(��RCR+��RCR-)�ϲ�Ϊһ������,
   ��ΪҪ�ں������жϾ�����+����-�¼�.

   ���ڶ���:
   ÿ������һ����.
 */

/************************ PPP ״̬��״̬ת��ͼ ***********************/

/************************ ״̬�������ĺ궨�� *************************/

/* tlu(This-Layer-Up)����:���ûص�����up */
#define PPP_FSM_tlu(pstFsm) \
    {\
        if (pstFsm->pstCallBacks->up) \
        { \
            (*pstFsm->pstCallBacks->up)(pstFsm); \
        } \
    }

/* tld(This-Layer-Down)����:���ûص�����down */
#define PPP_FSM_tld(pstFsm) \
    {\
        if (pstFsm->pstCallBacks->down) \
        { \
            /* ��down */ \
            (*pstFsm->pstCallBacks->down)(pstFsm); \
        } \
    }

/* tls(This-Layer-Started)����: */
#define PPP_FSM_tls(pstFsm) \
    {\
    if (pstFsm->pstCallBacks->starting) \
    { \
        (*pstFsm->pstCallBacks->starting)(pstFsm); \
    } \
    }

/* tlf(This-Layer-Finished)����: */
#define PPP_FSM_tlf(pstFsm) \
    {\
        if (pstFsm->pstCallBacks->finished) \
        { \
            (*pstFsm->pstCallBacks->finished)(pstFsm); \
        } \
    }

/* irc(Initialize-Restart-Count)����: */
#define PPP_FSM_irc(pstFsm) \
    { \
        /* ��ʼ��Retransmits */ \
        pstFsm->sRetransmits = PPP_DEFMAXCONFREQS;/* ���Retransmitֵ */ \
        /* TimeOutTime�ص���ʼֵ */ \
        /*pstFsm->ulTimeOutTime = PPP_DEFTIMEOUTTIME ; ��ʼֵ */ \
        /* ��ʼ��usNakloops */ \
        pstFsm->usNakloops = 0; \
    }

/* zrc(Zero-Restart-Count)����: */
#define PPP_FSM_zrc(pstFsm) \
    { \
        pstFsm->sRetransmits = 0; \
    }

/* scr(Send-Configure-Request)����:���ͱ��� */
#define PPP_FSM_scr(pstFsm) \
    { \
        PPP_FSM_SendConfigReq(pstFsm); \
        pstFsm->ucPktId++; \
        /* ������ʱ�� */ \
        PPP_FSM_SetRetransmitTimer(pstFsm); \
    }

/* sca(Send-Configure-Ack)��scn(Send-Configure-Nak/Rej)����: */
/* ulCode�����˾�����ʲô���� */
#define PPP_FSM_sca_scn(pstFsm, ucCode, ucId, pHead, pPacket, ulLen) \
    { \
        PPP_FSM_SendPacket(pstFsm, ucCode, ucId, pHead, pPacket, ulLen); \
    }

/* str(Send-Terminate-Request)���� */
#define PPP_FSM_str(pstFsm) \
    { \
        PPP_FSM_SendPacketByCode(pstFsm, TERMREQ, pstFsm->ucPktId); \
        pstFsm->ucPktId++; \
        /* ������ʱ�� */ \
        PPP_FSM_SetRetransmitTimer(pstFsm); \
    }

/* sta(Send-Terminate-Ack)���� */
#define PPP_FSM_sta(pstFsm, ucId) \
    { \
        PPP_FSM_SendPacketByCode(pstFsm, TERMACK, ucId); \
    }

/* scj(Send-Code-Reject)���� */
#define PPP_FSM_scj(pstFsm, pHead, pPacket, ulLen) \
    { \
        PPP_FSM_SendPacket(pstFsm, CODEREJ, pstFsm->ucPktId, pHead, pPacket, ulLen); \
    }

/* ser(Send-Echo-Reply)����,ֻ��LCP������������ */
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
     */       \
    PPP_PUTLONG(ulMagicNumber, pTemp); \
    pstFsm->sRetransmits = PPP_DEFMAXCONFREQS; \
    /* �������                                                       \
     |--------FSM Head(bytes) -------|                                 \
        0       1      2       3        4       5       6       7     \
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ \
     |       |       |       |       |       Magic  Number           | \
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ \
     |                               | \
                                    pPacket                         | \
                                                                 pTemp\
     */ \
    PPP_FSM_SendPacket(pstFsm, ECHOREP, ucId, pHead, pPacket, ulLen); \
    }

/************************ ״̬�������ĺ궨�� *************************/

/************************ ��״̬���йص������궨�� *************************/
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
#define PPP_FSM_ChangeState(pstFsm, ucNewState) \
    { \
        PPP_Debug_FsmStateChange(pstFsm, ucNewState); \
        pstFsm->ucState = ucNewState; \
        switch (ucNewState) \
        { \
        case PPP_STATE_INITIAL: \
        case PPP_STATE_STARTING: \
        case PPP_STATE_CLOSED: \
        case PPP_STATE_STOPPED: \
        case PPP_STATE_OPENED: \
            PPP_FSM_DelRetransmitTimer(pstFsm); \
            break; \
        case PPP_STATE_CLOSING: \
        case PPP_STATE_STOPPING: \
        case PPP_STATE_REQSENT: \
        case PPP_STATE_ACKRCVD: \
        case PPP_STATE_ACKSENT: \
        default: \
            break; \
            } \
            }

/* ɾ���ش���ʱ�� */
#define PPP_FSM_DelRetransmitTimer(pstFsm) \
    { \
        if (PPP_VSNCP == pstFsm->usProtocol) \
        { \
            (VOID)PPP_VSNCP_FSM_DelRetransmitTimer(pstFsm); \
        } \
        else \
        {  \
            if (pstFsm->ulTimeOutID) \
            { \
                (VOID)VOS_StopRelTimer(&(pstFsm->ulTimeOutID)); \
                pstFsm->ulTimeOutID = 0; \
            } \
        } \
    }


#define PPP_FSM_reqci(pstFsm, pPacket, ulLen, ucCode) \
    { \
        if (pstFsm->pstCallBacks->reqci) \
        { \
            ucCode = (*pstFsm->pstCallBacks->reqci)(pstFsm, pPacket, &ulLen); \
            if (ucCode == CONFNAK) \
            { \
                pstFsm->usNakloops++; \
                if (pstFsm->usNakloops > PPP_MAXNAKLOOPS) \
                { \
                    ucCode = CONFREJ;/* NAK����̫��,��ΪREJ */  \
                } \
            } \
            else \
            { \
                pstFsm->usNakloops = 0; \
            } \
        } \
        else \
        { \
            if (ulLen) \
            { \
                ucCode = CONFREJ;/* �ܾ����в��� */  \
            } \
            else \
            { \
                ucCode = CONFACK; \
            } \
        } \
    } \
    /************************ ��״̬���йص������궨�� *************************/

/************************ ��debug�йصĺ궨�� *************************/
/* ����/������ı�־�� */
#define PPP_DEBUG_PACKET_IN 0
#define PPP_DEBUG_PACKET_OUT 1

/* debug�����е�����ֵ */
#define PPP_DEBUG_ERROR 0
#define PPP_DEBUG_EVENT 1
#define PPP_DEBUG_PACKET 2
#define PPP_DEBUG_STATE 3

/* Ŀ����ϵĵ��Ժ� */
 #define PPP_DebugOutString(cDebugBuf, ulLen, pstPppInfo) \
{ \
    /* added by hyj 20030310 */ \
    UCHAR ucTemp[1024]; \
    PPP_MemSet((void *)ucTemp, 0, 1024); \
    if (ulLen > 1023) \
    { \
        /*lint -e420*/ \
        VOS_MemCpy(ucTemp, cDebugBuf, 1023); \
        /*lint +e420*/ \
    } \
    else \
    { \
        VOS_MemCpy(ucTemp, cDebugBuf, (ULONG)ulLen); \
    } \
    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,"%s" ,(CHAR *)ucTemp); \
 \
}


/************************ ��debug�йصĺ궨�� *************************/

 /*PPPģ����Դ�ӡ����*/
#define PPP_LOG_LEVEL     0
#define PPP_DEBUG_INFO    LOG_LEVEL_INFO
#define PPP_DEBUG_LOG     LOG_LEVEL_WARNING



#ifndef __WIN32_PLATFORM__
#define PPP_DebugOut(ulMid,ulCtrlLevel, fmt, ...)                      \
{                                                                    \
    if (ulCtrlLevel == LOG_LEVEL_INFO)                                \
    {                                                                \
        vos_printf("\r\n PPP_DEBUG_LEVEL--LOG_LEVEL_INFO: ");            \
    }                                                                \
    else                                                             \
    {                                                                \
        vos_printf("\r\n PPP_DEBUG_LEVEL--LOG_LEVEL_WARNING: ");         \
    }                                                                \
    vos_printf(fmt);                                                     \
}
#else
#define PPP_DebugOut(ulMid,ulCtrlLevel, fmt, ...)                      \
{                                                                    \
    /*��ʽ����ʹ��PS_LOGά��*/  \
    /*PS_LOG(MSPS_PID_PPPC, 0, ulCtrlLevel, fmt);*/                  \
    /*���Դ�����ʱʹ��VOS_printfά��*/  \
    if (ulCtrlLevel == LOG_LEVEL_INFO)                                \
    {                                                                \
        vos_printf("\r\n PPP_DEBUG_LEVEL--LOG_LEVEL_INFO: ");        \
    }                                                                \
    else                                                             \
    {                                                                \
        vos_printf("\r\n PPP_DEBUG_LEVEL--LOG_LEVEL_WARNING: ");     \
    }                                                                \
    vos_printf(fmt);                                                 \
}
#endif



/************************ ��������ʾ��Ϣ ************************/
enum ePppCmdInfo
{
    PPP_NOENCAP_ERROR = 0,
    PPP_NOTHISINTERF_ERROR
};

/************************ ��������ʾ��Ϣ ************************/

/************************ ͬ�첽ת���� *************************/
#define PPP_ConvertByteToAsy(ucOctet, pAsyData, ulAsyLen, ulAsynAccm) \
    {                                                  \
        if ((ucOctet == '\x7e') || (ucOctet == '\x7d')) \
        {                                              \
            /* add the Escape Control Character */ \
            *pAsyData = '\x7d';                        \
            pAsyData++;                               \
            ulAsyLen++;                               \
            ucOctet ^= 0x20;                           \
        }                                              \
        if (ucOctet < 0x20)                             \
        {                                              \
            if ((ulAsynAccm >> (unsigned int)ucOctet) & ((unsigned int)0x1)) \
            {                                          \
                /* if this character need be mapped, add the Escape Control Character */ \
                *pAsyData = '\x7d';                    \
                pAsyData++;                           \
                ulAsyLen++;                           \
                ucOctet ^= 0x20;                       \
            }                                          \
        }                                              \
        /* add the Escape Control Character */ \
        *pAsyData = ucOctet;                          \
        pAsyData++;                                   \
        ulAsyLen++; /* adjust frame's length */ \
    }

/************************ ��ȡPPPC���ƿ�ָ��� *************************/
#define GETPPPINFOPTRBYRP(pstPppInfo, ulRPIndex) \
    {                                                \
        if (((ulRPIndex) <= PPP_MAX_USER_NUM) && (PPP_CB_STATE_USED == g_astPppPool[ulRPIndex].usState)) \
        { \
            pstPppInfo = &g_astPppPool[ulRPIndex];        \
        } \
        else \
        { \
            pstPppInfo = VOS_NULL_PTR; \
        } \
    }

/* Begin Added by hyj for B02 */

/* ����(�ָ�)ʧ�ܱ�־ */
#define PPP_BKP_FAIL 1
#define PPP_BKP_SUCCESS 0

/* ��ʱ���ݸı��� */
#define PPP_BKPROUTINECHANGED 1
#define PPP_BKPROUTINONECHANGED 0

/* ��̬���ӱ�� */
#define PPP_STATE_FAIL 0
#define PPP_STATE_NEGOING 1
#define PPP_STATE_SUCCESS 2


/* �յ�PPPC���ƿ��� */
#define PPP_BKP_USEING 1
#define PPP_BKP_FREE 0

/* ����������� */
#define PPP_DOMAIN_LOCKED 1
#define PPP_DOMAIN_UNLOCK 0

/* ���ٽ������ */
#define PPP_TRACE_IN 0
#define PPP_TRACE_OUT 1

/* BEGIN: Added by longsirui 41291, 2008/4/8   ���ⵥ��:AX4D01982 */
#define PPP_TRACE_LNS_IN 2
#define PPP_TRACE_LNS_OUT 3
/* END:   Added by longsirui 41291, 2008/4/8 */

/* ���ݵ���ʹ�õ�����һЩ�궨�� */

/* Modifiedstart by zhangxiujuan 60016360 at 2006-09-21 V800R005C01B010 for BYHD11709 */
#ifdef  __PRODUCT_TYPE_PDSN80
 #define PPP_BKP_INFO_MAX 5
#else
 #define PPP_BKP_INFO_MAX 10                    /* ÿ����෢��10�����ƿ���Ϣ */
#endif
/* Modified  end by zhangxiujuan 60016360 at 2006-09-21 V800R005C01B010 for BYHD11709 */

#define PPP_BKP_MALLOC_RETRY_NUM 10          /* ��������ʱ�ڴ����볢�Դ��� */
#define PPP_BKP_SEND_RETRY_NUM 3           /* ��������ʱ��Ϣ�ط����Դ��� */
#define PPP_BKP_SLEEP_TIME 200         /* ���ݵ���ʱ�����л�ʱ�� */
#define PPP_BKP_DATA_FLAG 0xFFFFFFFF  /* �����־λ */
#define PPP_INDEX_NULL 0xFFFFFFFF  /* ��Ч���ƿ����� */


/******* ����IMSI���������Ϣ***********/
#define DEBUGBYIMSI() \
    { \
        LONG ulImsiCmp; \
        if (g_stPppDebugInfo.bDebug_Imsi) \
        { \
            ulImsiCmp = VOS_MemCmp(&g_stPppDebugImsi, &(pstPppInfo->stIMSI), sizeof(IMSI_S)); \
            if (ulImsiCmp) \
            { \
                return; \
            } \
        } \
    }


/* End Added by hyj for B02 */

/*****************************************
            ������Ժ�
*****************************************/
#define PPP_UT VOS_ERR
#define PPP_ST VOS_ERR

#ifndef  __WIN32_PLATFORM__
 #define PPP_TRACE(args...) \
            PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, ##args)
#else
 #define PPP_TRACE
#endif

#define PPP_TASK_NAME "PPPT"
#define LAP2_TASK_NAME "LAP"
#define LAP2_USER_TYPE_GTP 0
#define LAP2_USER_TYPE_PPP 1

#define SECTION_NAME_LEN 80 /*�˺궨��Ӧ��ɾ�������ڲ�֪���������Ǹ��궨��*/


/* Added start by zhudaoming 62333 at 2007-12-06 GGSN9811V9R7C01B02 for L2TP/PPP V9��ֲ */
/*lapͷ�ļ���GTPCͷ�ļ��г�ͻ���������¶����ˣ���Ҫȷ��һ�£�ɾ�����еĺ궨��*/
#define LAP2_EV_IPC_MSG 0X00020000
#define LAP2_EV_TIMER 0X00010000
#define SC_ADDR_REQ_MSG 0X00040000
#define SC_ADDR_RLS_MSG 0X00080000
#define DHCP_ADDR_MSG 0x00100000
/*AM-USM��AM-LAP2֮�佻����Ϣ����Ϣ��������*/
/*AM-USM��AM-LAP2֮�佻����Ϣ����Ϣ��������*/
/* Deleted start by zhudaoming 62333 at 2008-01-28 V9R7C01B02 for L2TP/PPP V9R7��ֲ */
/* Deleted end by zhudaoming 62333 at 2008-01-28 V9R7C01B02 for L2TP/PPP V9R7��ֲ */

/* Modified start by zhudaoming 62333 at 2007-12-05 GGSN9811V9R7C01B02 for L2TP/PPP V9��ֲ */
/*::PPP moudle*/
#define SID_PPP_PACKET_S 0x235
#define SID_PPP_CB_S 0x236
#define SID_PPP_BUILDRUN 0x237
#define SID_PPP_L2TPOPTION_S 0x238
#define SID_PPP_L2TPPARA_S 0x239
#define SID_PPP_AAAPRIM_S 0x240
#define SID_PPP_ASY_S 0x241
#define SID_PPP_SYN_S 0x242
#define SID_PPP_DHCP_S 0x243
#define SID_PPP_CBLCP_S 0x244
#define SID_PPP_CBIPCP_S 0x245
#define SID_PPP_BKP_S 0x246
#define SID_PPP_CBPAP_S 0x247
#define SID_PPP_CBCHAP_S 0x248
#define SID_PPP_CBCONFIG_S 0x249
#define SID_PPP_USERINFO_S 0x250
#define SID_PPP_RENEGO_S 0x251
#define SID_PPP_CCP_S 0x252
#define SID_PPP_MSID_S 0x253
/* Modified end by zhudaoming 62333 at 2007-12-05 GGSN9811V9R7C01B02 for L2TP/PPP V9��ֲ */

#define LAP_IPV4 0
#define LAP_IPV6 1
/* Added end by zhudaoming 62333 at 2007-12-06 GGSN9811V9R7C01B02 for L2TP/PPP V9��ֲ */
#define  AM_PPP_RADIUS_PRI 1
#define PPP_USR_NUMBER_INCR 1
#define PPP_USR_NUMBER_DECR 2

/* BEGIN: Added by longsirui 41291, 2008/1/24   ���ⵥ��:GGSN9811V9R7C02 for L2TP/PPP V9��ֲ */
#define FSU_TID_PPPC MID_PPPC
#define FSU_DBGMSG_LEN 1800
#define PPP_MAX_STATISC 600   /*500-599�����PCCʹ��*/
#define PPP_IPV6_MAX_STATISC 300
#define PPP_HSGW_MAX_STATISC 300   /*500-599�����PCCʹ��*/

#define AM_PPPC_MAX_SC_NUM 16
/* END:   Added by longsirui 41291, 2008/1/24 */

#define PPP_SOFT_INVALID(g_ulSoftPara)     ((g_ulSoftPara != 0) && (g_ulSoftPara != 1))

#define M_CFG_STATICIP_ROUTE_DISABLE    3   /* ��̬��ַ�������·�·�� */

#define M_CFG_DEFAULT_IPROUTEFLAG       0   /* Ĭ���Ƿ��·�·�� */
#define M_CFG_STATICIP_ROUTEDISABLE     1   /* ���·�·�� */

#define PPP_GETHDLCADDR(pstHdlcCB ,ulindex) \
    if(ulindex <= PPP_MAX_USER_NUM) \
    { \
        pstHdlcCB = &g_astHdlcPool[ulindex]; \
    } \
    else \
    { \
        pstHdlcCB = VOS_NULL_PTR; \
    }

#define PPP_GETLCPADDR(pstLcpCB ,ulindex) \
    if(ulindex <= PPP_MAX_USER_NUM) \
    { \
        pstLcpCB = &g_astPppLcpPool[ulindex]; \
    } \
    else \
    { \
        pstLcpCB = VOS_NULL_PTR; \
    }

#define PPP_GETIPCPADDR(pstIpcpCB, ulindex) \
    if(ulindex <= PPP_MAX_USER_NUM) \
    { \
        pstIpcpCB = &g_astPppIpcpPool[ulindex]; \
    } \
    else \
    { \
        pstIpcpCB = VOS_NULL_PTR; \
    }

#define PPP_GETPAPADDR(pstPapCB ,ulindex) \
    if(ulindex <= PPP_MAX_USER_NUM) \
    { \
        pstPapCB = &g_astPppPapPool[ulindex]; \
    } \
    else \
    { \
        pstPapCB = VOS_NULL_PTR; \
    }

#if VRP_MODULE_LINK_PPP_EAP == VOS_YES
#define PPP_GETEAPADDR(pstEapCB ,ulindex) \
    if((ulindex <= PPP_MAX_USER_NUM) && (0 == g_astPppEapPool[ulindex].ucUsed)) \
    { \
        pstEapCB = &g_astPppEapPool[ulindex]; \
    } \
    else \
    { \
        pstEapCB = VOS_NULL_PTR; \
    }
#endif

#define PPP_GETCHAPADDR(pstChapCB ,ulindex) \
    if(ulindex <= PPP_MAX_USER_NUM) \
    { \
        pstChapCB = &g_astPppChapPool[ulindex]; \
    } \
    else \
    { \
        pstChapCB = VOS_NULL_PTR; \
    }


#define PPP_GETCCPADDR(pstCcpCB ,ulindex) \
    if(ulindex <= PPP_MAX_USER_NUM) \
    { \
        pstCcpCB = &g_astPppCcpPool[ulindex]; \
    } \
    else \
    { \
        pstCcpCB = VOS_NULL_PTR; \
    }

#define PPP_GETCONFIGADDR(pstCcpCB ,ulindex) \
    if(ulindex <= PPP_MAX_USER_NUM) \
    { \
        pstCcpCB = &g_astPppConfifPool[ulindex]; \
    } \
    else \
    { \
        pstCcpCB = VOS_NULL_PTR; \
    }

#define PPP_GETIPV6CPADDR(pstIpv6cpCB ,ulindex) \
if((ulindex <= PPP_MAX_USER_NUM) && (0 == g_astPppIpv6cpPool[ulindex].ucUsedFlag)) \
{ \
    pstIpv6cpCB = &g_astPppIpv6cpPool[ulindex]; \
} \
else \
{ \
    pstIpv6cpCB = VOS_NULL_PTR; \
}
#define  PPP_USERTYPE_NOCMIP_NOAAA(pstLcpInfo,pstPppInfo) \
    ((PPPCFG_AUTHMODE_DEFAULT == g_stPppCfgInfo.ucAuthmod)\
    && (0 == pstLcpInfo->stGotOptions.neg_upap)\
    && (0 == pstLcpInfo->stGotOptions.neg_chap)\
    && (PPP_USERTYPE_MIP != pstPppInfo->bIPTech))

/* CMIPЭ�̳�SIP */
#define  PPP_USERTYPE_MIP_RENEGO_TYPECHANGE(pstPppInfo,pstIpcpInfo)\
    ((PPP_USERTYPE_MIP == pstPppInfo->bIPTech)\
    && (1 == pstIpcpInfo->stHisOptions.neg_addr))

/* ����PPP����ԭ��ֵ */
#define PPP_SET_REL_CODE(pstPppInfo, RelCode) \
    if (AM_RELCODE_UNKNOWN == (pstPppInfo)->ucPppRleaseCode) \
    { (pstPppInfo)->ucPppRleaseCode = (RelCode); }



#define PPP_RMI_MAX_NUM_PER_SPU  4   /*������Ҫʹ��ƽ̨�ṩ�ĺ�MAX_CPU_NUM*/

#define PPP_CPU_0_ON_SPU 0
#define PPP_CPU_1_ON_SPU 1
#define PPP_CPU_3_ON_SPU 3


enum
{
    PPP_USERSTAT_VJ,
    PPP_USERSTAT_MPPC,
    PPP_USERSTAT_ZLS0,
    PPP_USERSTAT_ZLS1
};

#define PPP_SUBCOUNT(x) (((x) > 0) ? ((x)--) : NULL)

typedef struct
{
    VOS_UINT32    ulMainDNSServer;     /* ��DNS������ */
    VOS_UINT32    ulBackupDNSServer;   /* ��DNS������ */
    VOS_UINT32    stMainDNSServerIpv6[4];    /* ����IPv6 DNS������ */
    VOS_UINT32    stBackupDNSServerIpv6[4];    /* ����IPv6 DNS������ */
    VOS_UINT16    usApnIndex ;         /* APN����   */
    UCHAR         ucDNSSelectMode;     /* 0 �����������ȣ� 1 Radiusָ������ */
    UCHAR         ucDNSSelectModev6;
}VOS_PACKED   DOMAINDNS_S;



#ifdef      __cplusplus
}
#endif      /* end of __cplusplus */

#endif      /* end of _PPP_DEF_H_ */
