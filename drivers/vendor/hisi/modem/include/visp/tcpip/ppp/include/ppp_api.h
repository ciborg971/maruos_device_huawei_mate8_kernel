
#ifndef _PPP_API_H_
#define _PPP_API_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "ppp/include/mp_api.h"

/**********************************************************************
*                        �����ṩ�Ĵ�����
***********************************************************************/


typedef enum enPppProErrorInfo
{
    PPP_NOENCAP_ERROR = VOS_ERR + 1,    /* 2 */ 
    PPP_WRONGPARA_ERROR,                /* 3 */
    PPP_NOTHISINTERF_ERROR,             /* 4 */
    PPP_DNSIPADDRESS_SAME,              /* 5 */
    PPP_DNSIPADDRESS_INVALID,           /* 6 */
    PPP_DNSIPADDRESS_PRI_IS_INVALID,    /* 7 ��DNS��Ч */
    PPP_DNSIPADDRESS_SEC_IS_INVALID,    /* 8 ��DNS��Ч */
    PPP_DNSIPADDRESS_NOEXIST,           /* 9 */
    PPP_CIPHERPASSWORD_WRONG,           /* 10 */
    PPP_IFNETCB_NOEXIST,                /* 11 */
    PPP_PPPCB_NOEXIST,                  /* 12 */
    PPP_CONFIGINFO_NOEXIST,             /* 13 */
    PPP_CONFIGINFO_NOEXIST_2,           /* 14 */
    PPP_LCPCB_NOEXIST,                  /* 15 */
    PPP_IPCPCB_NOEXIST,                 /* 16 */

    PPP_IPHC_DISABLE,                   /* 17 */
    PPP_IPHC_DISABLE_2,                 /* 18 */
    PPP_IPHC_CONTEXT_NOTEXIST,          /* 19 */
    PPP_IPHC_CONTEXT_NOTEXIST_2,        /* 20 */
     
    PPP_NEGOPHASE_ERR,                  /* 21 negotiate phase error*/
    PPP_NEGOTYPE_ERR,                   /* 22 negotiate protocol error */
    PPP_FSMSTATE_ERR,                   /* 23 protocol fsm state error */
    
    PPP_MUXCPCB_NOEXIST,                /* 24 */
    PPP_MUX_DISABLE,                    /* 25 */
    PPP_MUX_CONTEXT_NOTEXIST,           /* 26 */
    
    PPP_IP6CPCB_NOEXIST,                /* 27 */
    PPP_EXCEED_MAX_CBNUM,               /* 28 */

    PPP_CONFIG_CONFLICT,                /* 29 PPP������ó�ͻ���磬VJ-IPHC��PAP-CHAP */
    PPP_PARA_NULLPOINTER,               /* 30 �������Ϊ��ָ�� */
    PPP_PROTOCOL_INVALID,               /* 31 ��Ч��Э������ */
    PPP_HOSTNAME_INVALID,               /* 32 ��Ч���û���(���̻򳬳�) */
    PPP_HA_IS_SMOOTHING,                /* 33 HA����ƽ��������ֶ����������û������ӿ��򷵻ش˴����� */

    PPP_CONFIG_IFCONFLICT,              /* 34 */
    PPP_IP6CB_NOEXIST,                  /* 35 ��ȡIPv6�Ŀ��ƿ�ʧ�� */
    PPP_WRONGSETPARA_ERROR,             /* 36 �Ƿ����ÿ��ز������� */
    PPP_GETCB_FAIL,                     /* 37 ��ȡPPP���ƿ�ʧ�� */
    PPP_PHYTYPE_ERR,                    /* 38 �������ʹ��� */
    PPP_GETCONFIGINFO_FAIL,             /* 39 ��ȡ������Ϣʧ�� */
    PPP_CIPHERPASSWORD_WRONGLONG,       /* 40 pwd���� */
    PPP_SETONEOPT_FAIL,                 /* 41 ���õ�������״̬ʧ�� */
    PPP_SETGLOBEONEOPT_FAIL,            /* 42 ���õ���ȫ�ֿ���ʧ�� */
    PPP_SETNODEONEOPT_FAIL,             /* 43 ���õ���ȫ�ֽڵ㿪��ʧ�� */
    PPP_UPDATECONFIGINFO,               /* 44 ����������Ϣ */

    PPP_CANOT_SET_OSICP,                /* 45 �ýӿڲ��������Ƿ�Э��OSICP*/
    PPP_OSICPCB_NOEXIST,                /* 46 OSICP ���ƿ鲻����*/

    PPP_COM_NULL,                       /* 47 ������Ϊ�� */
    PPP_VA_NOEXIST,                     /* 48 Dialer����VT�ӿ��µ�VA�ӿڲ����� */
    PPP_NOT_3D_MODE,                    /* 49 �ӿ����÷���άģʽ */
    PPP_PARA_IP_WRONG,                  /* 50 */
    PPP_ERR_PORT_IS_VIRTUAL,            /* 51 �Ǳ���ӿ� */
    PPP_FUNCHOOK_NULL,                  /* 52 ��������Ϊ�� */
    PPP_IS_SHUTDOWN,                    /* 53 PPP�ӿ��Ѿ���shutdown�� */
    PPP_IPCTL_NOTEXIST,                 /* 54 IP���ƿ�Ϊ�� */
    PPP_CFG_MTU_FAIL,                   /* 55 MTU����Խ�� */
    PPP_CONFIGERR_MEMORY,               /* 56 �ڴ����ʧ�� */
    PPPMUX_COM_NULL,                    /* 57 PPPMUX���Ϊ�� */
    PPP_TASKRAP_NULL_IFNET,             /* 58 ������ռ���½ӿڱ�ɾ58 */

    PPP_ERR_NEG_TIME_REACHMAX,          /* 59 �û�ָ����Э��ʱ�䳬����Χ */
    PPP_ERR_CREATE_TIMER_FAIL,          /* 60 ������ʱ��ʧ�� */

    PPP_ERR_NOT_PPP_ITF = 61,           /* 61 �ӿڲ���PPP�ӿ� */

    PPP_LCPFSM_NOTOPEN,                 /* 62 NP�߼���ȡVISP�ڲ�PPP Lcp Echo�����Ϣʱ, LCP״̬��״̬��ΪOPEN״̬ */
    PPP_TIMER_CREATION_FAIL,
    PPP_INVALID_INPUT,

    PPP_ERRCODE_END         /* ����������ֵ������������߽��жϣ��Ժ����Ӵ�����ʱ���붨���ڴ�ֵ֮ǰ */
}PPP_PRO_ERROR_INFO_E;



/**********************************************************************
*                        �����ṩ�ĺ궨��
***********************************************************************/

#define PPP_MAXUSERNAMELEN     72
#define PPP_MAXUSERPWDLEN      20
#define PPP_MAXUSERPWDLENOLD   16

#define PPP_MAXCALLBACKDIALERSTRINGLEN  64
#define PPP_CALLINGNUM_LEN              64
#define PPP_CALLEDNUM_LEN               64

#define PPP_MP_DISCR_MAX_LENGTH         20  /* �ն�����������󳤶� */
#define PPP_MAX_CALLBACK_INFO_LEN       20
#define MC_PREFIXE_MAX_NUM              16  /* ǰ׺ʡ��֧�ֵ����ȼ��� */

/*��ΪTCPIP_GetPPPInfo�����ulType����*/
#define PPP_SELF            0
#define PPP_USEDCONFIG      1
#define PPP_CONFIG          2   
#define PPP_LCP             0xc021          /* Link Control Protocol */
#define PPP_IPCP            0x8021          /* IP Control Protocol */
#define PPP_PPPMUXCP        0x8059          /* PPP Multiplexing Control Protocol */
#define PPP_OSICP           0x8023          /* OSI Control Protocol */
#define PPP_IP6CP           0x8057          /* IPv6 Control Protocol */

/*��ΪTCPIP_SetPppAuthType�����ulType����*/
#define TCPIP_AUTH_NONE 0
#define TCPIP_AUTH_PAP  1
#define TCPIP_AUTH_CHAP 2
#define TCPIP_AUTH_ALL  3

#define PPP_NP_NOT_HANDLE_LCP_ECHO 0
#define PPP_NP_HANDLE_LCP_ECHO 1



#ifndef DHCP4C_DNSIP_NUM
#define DHCP4C_DNSIP_NUM       6 /* dns server ��ַ���� */
#endif

/*�����û�����pwd��֤(CHAP/PAP)*/
#define PPPMAXTUNNELSERVERNUM  5
#define PPP_MAXPERUSERCFGLEN   10

/* Added by hanna55555, VISPV1R8C01 for ppp-link support ipv6, 2009/3/20 */
#define INTERFACE_ID_LEN       8
/*End of Added by hanna55555, 2009/3/20 */


#define PPP_INTERFACEID_INDEX   8

/* Modified by Syed Ajim for BYAD06119 , 2004-01-09 */
#define PPP_IP6_INTERID_ISZERO(InterfaceID) \
( (InterfaceID)[0]== 0x00 && \
   (InterfaceID)[1]== 0x00 && \
   (InterfaceID)[2]== 0x00 && \
   (InterfaceID)[3]== 0x00 && \
   (InterfaceID)[4]== 0x00 && \
   (InterfaceID)[5]== 0x00 && \
   (InterfaceID)[6]== 0x00 && \
   (InterfaceID)[7]== 0x00 )

#define  PPP_IP6_CHECK_LINKLOCAL_ADDR(pstIpv6Addr)  \
   (PPP_IP6_INTERID_ISZERO((UCHAR *)((UCHAR *)pstIpv6Addr + PPP_INTERFACEID_INDEX))) ? VOS_ERR : VOS_OK 

/********************** PPP�澯��صĺ궨�� **********************/
#define PPP_IPHC_PARA_DIFF              0x0001  /* ��Ӧ�澯IDΪWARNING_PPP_IPHC_PARA_DIFF */
#define PPP_IPCONFLICT                  0x0002  /* PPP�ĵ�ַЭ�̳�ͻ�澯 */
#define PPP_LOOPBACK                    0x0004  /* PPP����·���ظ澯 */
#define PPP_MP_ED_DIFF                  0x0008  /* PPP��MP�ն���������һ�¸澯*/
#define PPP_LCP_AUTH_NEGOTIATE_FAILURE  0x0010  /* LCP��֤Э��Э�̲����㵼��Э��ʧ�ܵĸ澯 */
#define PPP_LCP_MP_NOBIND               0x0020  /* LCPЭ��ʱ̽�⵽һ�ΰ󶨵�MP����һ��û�а󶨵�MP��澯 */
#define PPP_MP_SUBLINKLOWLIMIT          0x0040  /* �趨MP���޷�ֵ������·�����澯 */
#define PPP_MP_CFG_DIFF                 0x0080  /* ���˻�Զ���ͨ��PFC/ACFC/MHF/SSNHF/MRU/MRRU/PREFIX��һ�µ���LCP down */
#define PPP_PAP_AUTH_FAILURE            0x0100  /* PAP��֤ʧ�ܣ���ӦWARNING_PPP_AUTH_FAILURE */
#define PPP_CHAP_AUTH_FAILURE           0x0200  /* CHAP��֤ʧ�ܣ���ӦWARNING_PPP_AUTH_FAILURE */
#define PPP_NPINFO_NOCONSISTENT         0x0400  /* VISP�·���NP����Ϣ��NP��Ч����Ϣ��һ�£���ӦWARNING_PPP_NPINFO_NOCONSISTENT */
#define PPP_DOWN_PPI_FAIL               0x0800  /* �·�NPʧ�ܣ���ӦWARNING_PPI_DOWN_PPP_FAIL */
#define PPP_NEG_NOT_PASS                0x1000  /* �涨ʱ����Э�̲�ͨ��ʱ����澯�������ӦWARNING_PPP_NEG_NOT_PASS */

/**********************************************************************
*                        �����ṩ�����ݽṹ����
***********************************************************************/

/*��TCPIP_ReceiveAuthResult�ӿ��е�ulResult�ֶ���д��֤���,�Է��ظ�VISP
  �û�ֻҪ��дPPP_PRIM_ACCEPT��PPP_PRIM_REJECT����*/
typedef enum enPppAuthPrimID
{
    PPP_PRIM_JOIN = 1,
    PPP_PRIM_CHAP,
    PPP_PRIM_ACCT,

    
    PPP_PRIM_LEAVING,
    PPP_PRIM_ACCEPT,
    PPP_PRIM_REJECT,
    PPP_PRIM_BYE,
    PPP_PRIM_CUT,
    
    
    PPP_PRIM_EXECUSERNULL,
    PPP_PRIM_LEAVING_OK
}PPP_AUTH_PRIMID_E;


/*PPP Debug Flag Info*/
typedef struct tagPppDebugInfo
{
    ULONG ulDebug_Verbose_SetNum;/* ����Verbose��Ϣ��ӡ���� */
    ULONG ulDebug_Verbose_Octets;/* ���õ�Verbose��Ϣ��ӡǰN�ֽ��� */
    ULONG ulDebug_Verbose_CountNum; /* Verbose ��Ϣ��ӡ�������� */
    
    UCHAR ucDebug_Lcp_Packet;
    UCHAR ucDebug_Lcp_Event;
    UCHAR ucDebug_Lcp_Error;
    UCHAR ucDebug_Lcp_StateChange;
    UCHAR ucDebug_Lcp_Action;
    UCHAR ucDebug_Lcp_Verbose;

    UCHAR ucDebug_Lcpecho_Packet;
    UCHAR ucDebug_Lcpecho_Event;
    UCHAR ucDebug_Lcpecho_Action;
    
    UCHAR ucDebug_Ipcp_Packet;
    UCHAR ucDebug_Ipcp_Event;
    UCHAR ucDebug_Ipcp_Error;
    UCHAR ucDebug_Ipcp_StateChange;
    UCHAR ucDebug_Ipcp_Action;
    UCHAR ucDebug_Ipcp_Verbose;

    UCHAR ucDebug_Ip6cp_Packet;
    UCHAR ucDebug_Ip6cp_Event;
    UCHAR ucDebug_Ip6cp_Error;
    UCHAR ucDebug_Ip6cp_StateChange;
    UCHAR ucDebug_Ip6cp_Action;
    UCHAR ucDebug_Ip6cp_Verbose;

    UCHAR ucDebug_Pap_Packet;
    UCHAR ucDebug_Pap_Event;
    UCHAR ucDebug_Pap_Error;
    UCHAR ucDebug_Pap_StateChange;
    UCHAR ucDebug_Pap_Verbose;

    UCHAR ucDebug_Chap_Packet;
    UCHAR ucDebug_Chap_Event;
    UCHAR ucDebug_Chap_Error;
    UCHAR ucDebug_Chap_StateChange;
    UCHAR ucDebug_Chap_Verbose;

    UCHAR ucDebug_Osicp_Packet ;
    UCHAR ucDebug_Osicp_Event ;
    UCHAR ucDebug_Osicp_Error ;
    UCHAR ucDebug_Osicp_StateChange ;
    UCHAR ucDebug_Osicp_Action;
    UCHAR ucDebug_Osicp_Verbose;
    UCHAR ucDebug_Osi_Packet ;
    UCHAR ucDebug_Osi_Verbose ;

    UCHAR ucDebug_Ip_Packet;
    UCHAR ucDebug_Ip_Verbose;
    
    /* Added by hanna55555, VISPV1R8C01 for ppp-link support ipv6, 2009/3/18 */
    UCHAR ucDebug_Ip6_Packet; /*��ʾ���е�IPv6����*/
    UCHAR ucDebug_Ip6_Verbose;
    /*End of Added by hanna55555, 2009/3/18 */
    
    UCHAR ucDebug_MP_Event;
    UCHAR ucDebug_MP_Packet;
    UCHAR ucDebug_MP_Error;
    UCHAR ucDebug_MP_Verbose;

    UCHAR ucDebug_VJComp_Packet;
    UCHAR ucDebug_VJComp_Verbose;

    UCHAR ucDebug_Lqm_Packet;
    UCHAR ucDebug_Lqm_Verbose;

    UCHAR ucDebug_Muxcp_Packet ;
    UCHAR ucDebug_Muxcp_Event ;
    UCHAR ucDebug_Muxcp_Error ;
    UCHAR ucDebug_Muxcp_StateChange;
    UCHAR ucDebug_Muxcp_Action;
    UCHAR ucDebug_Muxcp_Verbose;

    UCHAR ucDebug_Pppmux_Packet;
    UCHAR ucDebug_Pppmux_Error;
    UCHAR ucDebug_Pppmux_Verbose;
    UCHAR ucDebug_IPHC_Verbose;/* ���ڴ�ӡIPHCԭʼ������Ϣ */

    UCHAR ucDebug_Core_Event;
    UCHAR ucDebug_Packet_Verbose;/*�������أ�����all�Ŀ���*/
    UCHAR ucDebug_Link_PhaseChange;
}PPPDEBUGINFO_S;


/*PPP Control Block Info*/
typedef struct tagTCPIP_PppInfo
{
    ULONG bIsAsync: 1,        /* �Ƿ����첽��, ��LCP���ж��Ƿ�Э��ACCMAP */
          bSynAsyConvert: 1,  /* �����첽�ڣ�����ȷ���Ƿ���PPP����ͬ/�첽����ת�� */
          bLoopBacked: 1,     /* �ӿ��Ƿ������Ի� */
          bLowerIsUp: 1, 
          bIsDialer:1,       /* �Ƿ񲦺ſ� */
          bIsCallIn:1,       /* �Ƿ��Ǻ���,�����ж��Ƿ�callback */
          bIsCallBackUser:1, /* �Ƿ���callback�û�,��֤ʱ��AAA��� */
          bMpChannelType:2,  /* MPͨ������
                                0(PPP_MP_NONE):����MP
                                1(PPP_MP_SUBCHANNEL):MP��ͨ��
                                2(PPP_MP_FATHER):MP��ͨ��
                                3(PPP_MP_TEMPLATE):MPģ��
                             */
          bPppInterleave:1,    /*�Ƿ�����LFI*/
          bRunningPoeClient:1, /* ������PPP Info�ṹ�Ƿ�����PPPoE Client*/
          bLqmStatus:1,      /* ����LQM��·״̬ */
          bReserved: 20;     /* ����,�Ժ�ʹ�� */

    ULONG ulRemoteAccm;      /* �Զ�ACCM������ */
    ULONG ulLocalAccm;       /* ����ACCM������ */

    ULONG ulIfIndex;         /* ��Ӧ��IFNET���� */
    ULONG ulVLinkIndex;      /* ������VLink���� */
    ULONG ulRouteIfIndex;    /* ·�ɿɼ��ӿڵ�IFNET���� */

    ULONG usPhase;           /* PPP��ǰ����Э�̽׶�,����Ϊ����ֵ:
                                 PPP_PHASE_DEAD
                                 PPP_PHASE_ESTABLISH
                                 PPP_PHASE_AUTHENTICATE
                                 PPP_PHASE_CBCP
                                 PPP_PHASE_NETWORK
                                 PPP_PHASE_TERMINATE
                              */

    struct tagPppDebugInfo stPppDebugInfo;  /* �ӿڵ�debug������Ϣ */

    USHORT usMtu;
    UCHAR  ucPadding_1[2];

    UCHAR ucAuthServer;        
    UCHAR ucAuthClient;
    UCHAR ucPadding_2[2];
    CHAR  szLoginUsrName[PPP_MAXUSERNAMELEN + 1]; /* �Զ�������֤ʱʹ�õ��û��� */
    CHAR  szCallBackDialString[PPP_MAXCALLBACKDIALERSTRINGLEN + 1];
    /*aaa authencation*/
    CHAR  szCalledNumber[PPP_CALLINGNUM_LEN + 1];
    CHAR  szCallingNumber[PPP_CALLEDNUM_LEN + 1];

    ULONG ulUserId;
    ULONG ulIsIsFlag;     /* �Ƿ�ʹ���շ�ISIS���ģ�Ϊ1ʹ�ܣ�0ȥʹ�� */
} TCPIP_PPPINFO_S;

/*PPP AUTH MSG*/
typedef struct tagPppAuthMsg
{
    USHORT usType;      /*PAP or CHAP Auth packet*/
    UCHAR ucPktID;      /*�������*/
    CHAR szUsrName[PPP_MAXUSERNAMELEN + 2];
    UCHAR ucUsrNameLen;
    CHAR szPwd[LEN_256];/*chap��֤ʱΪchallege*/
    UCHAR ucPwdLen;
    CHAR szResponse[LEN_256];/*�����û���ȡpwdʱΪpwd��chap��֤���ʱΪ���ɵ�response*/
    UCHAR ucResponseLen;
}PPPAUTHMSG_S; 

/*PPP LCP Option*/
typedef struct tagPppLcpOption
{
    /* �Ƿ�Э�� */
    ULONG neg_mru: 1,
         neg_asyncmap : 1,
         neg_upap : 1,
         neg_chap : 1,
         neg_magicnumber : 1,
         neg_pcompression : 1,
         neg_accompression : 1,
         neg_lqr : 1,
         neg_mrru : 1,      /* mpЭ��ѡ�����Э�� */
         neg_ssnhf : 1,     /* mpЭ��ѡ���ѡ�vispĬ�ϲ�Э�̣�ʹ�ó���� */
         neg_discr : 1,     /* mpЭ��ѡ���ѡ�vispĬ��Э�̣�classΪ1�����6�ֽڵ�ַ */
         neg_callback : 1,
         neg_mhf : 1,
         neg_prefixE : 1,
         bReserve : 18;

    /* Э�̲���ֵ */
    USHORT  mru;
    USHORT  mrru;
    ULONG   asyncmap;
    ULONG   magicnumber;
    ULONG   numloops;
    UCHAR   chap_mdtype;
    UCHAR   ucPadding[3]; 
    ULONG   lqr_period; /* Reporting period for LQR 1/100ths second */
    UCHAR   discr_len;
    UCHAR   discr_class;
    UCHAR   callbackopr;
    UCHAR   discr_addr[PPP_MP_DISCR_MAX_LENGTH];
    UCHAR   callbackinfo[PPP_MAX_CALLBACK_INFO_LEN];
    UCHAR   callbacklen;

    UCHAR ucPrefixELen;       /* Req������ǰ׺ʡ��ѡ��ĳ��� */
    UCHAR ucMhfCode;          /* MHFѡ����codeֵ */
    UCHAR ucMhfClass;         /* MHFѡ����classֵ */
    UCHAR ucReserve; 
    
    /* Ϊ�˷���ǰ׺ʡ�Ա�Ŀ��������䶨�彫�䶨����ڽṹ�����
       �������ӵĲ�������ڸò���ǰ�棬������������� */
    MC_PREFIXE_S *pstPrefixE; /* ǰ׺ʡ��ӳ����ñ���һ��16��MC_PREFIXE_SԪ�ص����飬�洢ǰ׺ʡ�Թ��� */
} PPP_LCP_OPTION_S;

/*PPP LCP Info*/
typedef struct tagTCPIP_PppLcpInfo
{
    PPP_LCP_OPTION_S stGotOptions;    /* �Ѿ���Է�Э�̳ɹ����ҵ�ѡ�� */
    PPP_LCP_OPTION_S stHisOptions;    /* �Ѿ�����Э�̳ɹ��ĶԷ���ѡ�� */
    PPP_LCP_OPTION_S stWantOptions;   /* ��ϣ����Է�Э�̵��ҵ�ѡ�� */
    PPP_LCP_OPTION_S stAllowOptions;  /* ����Է�����Э�̵��ҵ�ѡ�� */
} TCPIP_PPPLCPINFO_S;

/*PPP IPCP Option*/
typedef struct tagPppIpcpOption
{
    /* �Ƿ�Э�� */
    ULONG neg_addr :         1,   /* Negotiate Address? */
          old_addrs:         1,   /* Use old (IP-Addresses) option? */
          req_addr :         1,   /* Ask peer to send address? */
          neg_vj :           1,   /* Van Jacobson Compression? */
          neg_dnsaddr0 :     1,   /* negotiate Primary DNS server address? */
          req_dnsaddr0 :     1,   /* Ask peer to send DNS server address? */
          neg_nbnsaddr0 :    1,   /* negotiate Primary NBNS server address? */
          req_nbnsaddr0 :    1,   /* Ask peer to send NBNS server address? */
          neg_dnsaddr1 :     1,   /* negotiate Secondary DNS server address? */
          req_dnsaddr1 :     1,   /* Ask peer to send DNS server address? */
          neg_nbnsaddr1 :    1,   /* negotiate Secondary NBNS server address? */
          req_nbnsaddr1 :    1,   /* Ask peer to send NBNS server address? */
          accept_dnsaddr0 :  1,   /* accept peer's value is changed */
          accept_dnsaddr1 :  1,   /* accept peer's value is changed */
          accept_nbnsaddr0 : 1,   /* accept peer's value is changed */
          neg_iphc : 1,           /* IPHC Compression? */
          accept_nbnsaddr1 : 1,   /* accept peer's value is changed */

          breserved: 15;

    USHORT vj_protocol;           /* protocol value to use in VJ option */
    UCHAR maxslotindex, cflag;    /* values for RFC1332 VJ compression neg. */
    ULONG ouraddr, hisaddr;       /* Addresses in HOST BYTE ORDER */
    ULONG dnsaddr0, nbnsaddr0;    /* Primary DNS address and Primary NDNS address (in HOST BYTE ORDER) */
    ULONG dnsaddr1, nbnsaddr1;    /* Secondary DNS and NBNS address (in HOST BYTE ORDER) */  
    
    USHORT iphc_protocol;
    USHORT us_tcp_space;
    USHORT us_non_tcp_space;
    USHORT us_f_max_period;
    USHORT us_f_max_time;
    USHORT us_max_header;

    UCHAR ucRtpCompression;    /* Э��(Enhance) RTP Compression��ѡ������ */
    UCHAR ucCompressType;      /* ����ѹ������ */

    UCHAR ucPadding[2]; 
} PPP_IPCP_OPTION_S ;

/* Modified by hanna55555, VISPV1R8C01 for ppp-link support ipv6, 2009/3/20 */
/*PPP IP6CP Option*/
typedef struct tagPppIp6cpOption
{
    /* �Ƿ�Э�� */
#if (VRP_BIG_ENDIAN == VRP_YES)
    ULONG   neg_interfaceid :  1,   /* Negotiate Address? */
            neg_compprotocol:  1,
            nak_isok        :  1,   /* Use old (IP-Addresses) option? */
            bReserve        :  29;  /* Ϊ���Ժ���չԤ��Э��λ */
#else
    ULONG   bReserve        :  29,  /* Ϊ���Ժ���չԤ��Э��λ */
            nak_isok        :  1,   /* Use old (IP-Addresses) option? */
            neg_compprotocol:  1, 
            neg_interfaceid :  1;   /* Negotiate Address? */
#endif

    UCHAR   my_interface_id[8],his_interface_id[8];
    USHORT  comp_protocol;   /* protocol value to use in compress protocol option */
    UCHAR   ucPadding[2]; 
} PPP_IP6CP_OPTION_S;
/* End of Modified by hanna55555, 2009/3/20 */

/*PPP IPCP Info*/
typedef struct tagTCPIP_PppIpcpInfo
{
    PPP_IPCP_OPTION_S stGotOptions;    /* �Ѿ�Э�̵����ҵ�ѡ�� */
    PPP_IPCP_OPTION_S stHisOptions;    /* �Ѿ�Э�̵��ĶԷ���ѡ�� */
    PPP_IPCP_OPTION_S stWantOptions;   /* ��ϣ����Է�Э�̵��ҵ�ѡ�� */
    PPP_IPCP_OPTION_S stAllowOptions;  /* ������Է�Э�̵��ҵ�ѡ�� */
} TCPIP_PPPIPCPINFO_S ;

/* Added by hanna55555, VISPV1R8C01 for ppp-link support ipv6, 2009/3/20 */
/*PPP IP6CP Info*/
typedef struct tagTCPIP_PppIp6cpInfo
{
    PPP_IP6CP_OPTION_S stGotOptions;    /* �Ѿ�Э�̵����ҵ�ѡ�� */
    PPP_IP6CP_OPTION_S stHisOptions;    /* �Ѿ�Э�̵��ĶԷ���ѡ�� */
    PPP_IP6CP_OPTION_S stWantOptions;   /* ��ϣ����Է�Э�̵��ҵ�ѡ�� */
    PPP_IP6CP_OPTION_S stAllowOptions;  /* ������Է�Э�̵��ҵ�ѡ�� */
} TCPIP_PPPIP6CPINFO_S ;
/*End of Added by hanna55555, 2009/3/20 */

/*PPP PPPMUXCP Option*/
typedef struct tagPppMuxcpOption
{
    /* �Ƿ�Э�� */
    #if (VRP_BIG_ENDIAN == VRP_YES)
    ULONG neg_defaultpid : 1,    /* Negotiate Default Pid */
          bReserve       : 31;   /* Ϊ���Ժ���չԤ��Э��λ */
    #else
    ULONG bReserve       : 31,   /* Ϊ���Ժ���չԤ��Э��λ */
          neg_defaultpid : 1;    /* Negotiate Default Pid */
    #endif
    
    /* Э�̲��� */
    USHORT usDefaultPid;        /* Ĭ��Э��ţ����û���������Ϊ0x0021 */
    USHORT usReserved;          /* Ԥ�� */
} PPP_MUXCP_OPTION_S; 

/*PPP PPPMUXCP Info*/
typedef struct tagTCPIP_PppMuxcpInfo
{
    PPP_MUXCP_OPTION_S stGotOptions;    /* �Ѿ�Э�̵����ҵ�ѡ�� */
    PPP_MUXCP_OPTION_S stHisOptions;    /* �Ѿ�Э�̵��ĶԷ���ѡ�� */
    PPP_MUXCP_OPTION_S stWantOptions;   /* ��ϣ����Է�Э�̵��ҵ�ѡ�� */
    PPP_MUXCP_OPTION_S stAllowOptions;  /* ������Է�Э�̵��ҵ�ѡ�� */
} TCPIP_PPPMUXCPINFO_S ;

/*PPP OSICP Option*/
typedef struct tagPppOsicpOption
{
    /* �Ƿ�Э�� */
    UCHAR neg_Align_NPDU ;

    /* Э�̲���ֵ */
    UCHAR ucAlign_NPDU;
} PPP_OSICP_OPTION_S ;

/*PPP OSICP Info*/
typedef struct tagTCPIP_PppOsicpInfo
{
    PPP_OSICP_OPTION_S stGotOptions;    /* �Ѿ�Э�̵����ҵ�ѡ�� */
    PPP_OSICP_OPTION_S stHisOptions;    /* �Ѿ�Э�̵��ĶԷ���ѡ�� */
    PPP_OSICP_OPTION_S stWantOptions;   /* ��ϣ����Է�Э�̵��ҵ�ѡ�� */
    PPP_OSICP_OPTION_S stAllowOptions;  /* ������Է�Э�̵��ҵ�ѡ�� */
} TCPIP_PPPOSICPINFO_S ;

/* PPPЭ�̽�����ݽṹ */
typedef struct tagPPPNEGORESULT
{
    /* �Ƿ�ʹ�� */
    ULONG  neg_upap          : 1,   /* ��־Э��PAP��֤ */
           neg_chap          : 1,   /* ��־Э��CHAP��֤ */
           neg_pcompression  : 1,   /* ��־Э��PFC */
           neg_accompression : 1,   /* ��־Э��ACFC */
           neg_ssnhf         : 1,   /* ��־Э��SSNHF */
           neg_mhf           : 1,   /* ��־Э��MHF */
           neg_prefixE       : 1,   /* ��־Э��Prefix-Elision */
           neg_iphc          : 1,   /* ��־Э��IPHC */
           neg_vj            : 1,   /* ��־Э��Vjyѹ�� */
           neg_mrru          : 1,   /* ��־Э��mrru */
           neg_discr          :1,   /*��־Э��discr*/
           neg_defaultpid    : 1,   /* ��־Э��PPPMux */
           is_lcp_up         : 1,   /* �Ƿ�LCPЭ�̳ɹ� */
           is_ipcp_up        : 1,   /* �Ƿ�IPCPЭ�̳ɹ�*/
           is_pppmux_up      : 1,   /* �Ƿ�PPPMUXЭ�̳ɹ�*/
           is_osicp_up       : 1,   /*�Ƿ�osicpЭ�̳ɹ�*/
           /* Added by hanna55555, VISPV1R8C01 for ppp-link support ipv6, 2009/3/20 */
           is_ip6cp_up       : 1,   /* �Ƿ�IP6CPЭ�̳ɹ�*/
           breserved         : 15;  /* ���� */
           /*End of Added by hanna55555, 2009/3/20 */

    /* LCP */
    USHORT mru;                  /* Э�̵�mru */
    USHORT mrru;                 /* Э�̵�mrru */
    UCHAR ucMhfCode;             /* MHFѡ��֧�ֳ�����ͷ��ʽ���Ƕ�����ͷ��ʽ */
    UCHAR ucMhfClass;            /* MHFѡ��֧�ֵĵȼ��� */
    UCHAR discr_len;             /*�ն�����������*/
    UCHAR discr_class;           /*�ն�����������*/
    
    /*�ն�������*/
    UCHAR discr_addr[PPP_MP_DISCR_MAX_LENGTH];

    MC_PREFIXE_S astPrefixE[MC_PREFIXE_MAX_NUM]; /* ǰ׺ʡ��ӳ��� */

    /* IPCP */
    ULONG  ouraddr;              /* ���˵�ַ */
    ULONG  hisaddr;              /* �Զ˵�ַ */
    ULONG  iphc_protocol;
    USHORT us_tcp_space;
    USHORT us_non_tcp_space;
    USHORT us_f_max_period;
    USHORT us_f_max_time;
    USHORT us_max_header;
    UCHAR  ucRtpCompression;     /* Э��(Enhance) RTP Compression��ѡ������ */
    UCHAR  ucCompressType;       /* ����ѹ������ */

    /* MUXCP */
    ULONG ulDefaultPid;         /* Э�̵�PID */

    /* OSICP */
    UCHAR our_neg_Align_NPDU;        /*�����Ƿ�Э��NPDU*/
    UCHAR our_ucAlign_NPDU;          /*Э�̵�ֵ*/
    UCHAR his_neg_Align_NPDU;        /*�Զ��Ƿ�Э��NPDU*/
    UCHAR his_ucAlign_NPDU;          /*Э�̵�ֵ*/
    
    /* Added by hanna55555, VISPV1R8C01 for ppp-link support ipv6, 2009/3/20 */
    /* IP6CP */
    UCHAR  my_interface_id[8];   /* ���˽ӿ�ID */
    UCHAR  his_interface_id[8];  /* �Զ˽ӿ�ID */
    /*End of Added by hanna55555, 2009/3/20 */
} PPPNEGORESULT_S;

/*PPP��Э�飬������TCPIP_ShowPPPCfgInfo��ulProtocol��������*/
typedef enum enPppSubProtocol
{
    PPP_SUB_MUXCP,
    PPP_SUB_IPHC,
    PPP_SUB_MC,
    PPP_SUB_PREFIX,
    PPP_SUB_OSICP
}PPP_SUB_PROTOCOL_E;

/* LQM��������ȡ���ֶ���Ϣ */
typedef struct tagTCPIP_LQR_STAT
{
    ULONG ulSaveInPackets; /*���յı�����*/
    ULONG ulSaveInDiscards;/*���պ����ı�����*/
    ULONG ulSaveInErrors;  /*���յ��Ĵ�������*/
    ULONG ulSaveInOctets;  /*���յ����ֽ���*/
    ULONG ulOutPackets;    /*���͵ı�����*/
    ULONG ulOutOctets;     /*���͵��ֽ���*/
} TCPIP_LQR_STAT_S;

/* ͳ����Ϣ */
typedef struct tagPppStatistic
{
    /* �Ʒ���Ϣ */
    ULONG ulInOctets;
    ULONG ulInGigaWords;
    ULONG ulOutOctets;
    ULONG ulOutGigaWords;
    ULONG ulInPackets;
    ULONG ulOutPackets;
    ULONG ulOutBadPkts;       /* ���Ͷ��������� */
    ULONG ulOutBadOctets;     /* ���Ͷ����ֽ��� */
    ULONG ulBadFcsPackets;
    ULONG ulBadAddressPackets;
    ULONG ulBadControlPackets;
    ULONG ulSendDiscReqPackets; /* �ӿ��Ϸ��͵�discard request������ */
    ULONG ulRecvDiscReqPackets; /* �ӿ��Ͻ��յ�discard request������ */
    ULONG ulDownDiscReqPackets; /* �ɹ�down�������ӿڵ�discard request������ */
} PPPSTATISTIC_S;

typedef enum enPppFsmState
{
    PPP_FSM_INITIAL_STATE = 1,  /* 1   Down, hasn't been opened */
    PPP_FSM_STARTING_STATE,     /* 2   Down, been opened */
    PPP_FSM_CLOSED_STATE,       /* 3   Up, hasn't been opened */
    PPP_FSM_STOPPED_STATE,      /* 4   Open, waiting for down event */
    PPP_FSM_CLOSING_STATE,      /* 5   Terminating the connection, not open */
    PPP_FSM_STOPPING_STATE,     /* 6   Terminating, but open */
    PPP_FSM_REQSENT_STATE,      /* 7   We've sent a Config Request */
    PPP_FSM_ACKRCVD_STATE,      /* 8   We've received a Config Ack */
    PPP_FSM_ACKSENT_STATE,      /* 9   We've sent a Config Ack */
    PPP_FSM_OPENED_STATE        /* 10   Connection available */
}PPP_FSM_STATE_E;

/* ������Ϣ */
typedef struct tagPppConfigInfo 
{
    ULONG bCallbackReq    : 1,
          bCallbackAcc    : 1,
          bCallInAuth     : 1,
          bAuthRmtChap    : 1,
          bAuthRmtPap     : 1,
          bEnableVJComp   : 1,
          /*bEnableComp     : 1,*/
          bEnablePComp    : 1,
          bEnableACComp   : 1,
          /* End of addition */
          bSetAsMp        : 1,
          bPapPwdEncrypt  : 1,
          bChapPwdEncrypt : 1,
          bAuthRmtList    : 1,

          bAcceptPeerDNS0      :1,
          bRejectPeerDNS0      :1,
          bAcceptPeerDNS1      :1,
          bRejectPeerDNS1      :1,
  
          bEnableIPHComp  : 1,
          bNegoSubOptions : 1,
          bStacCompress   : 1,   
          
          bPppInterleave  : 1,  /* �Ƿ�ʹ��MP�ķ�Ƭ���湦�� */

          bPppReorderWindow  : 1,
          bMpDiscriminator:1,   /* SWFD10247 2005.06.11  discriminator negotiation,Ĭ��ʹ��,class:1(�����������6�ֽ�), */

          bNegoLCPEnable:  1,   
          bNegoNCPEnable:  1,
          /*End for IPOS D00042*/

          bMc         :1,
          bMcPrefixE  :1,
          bSsnhf      :1,
          bPPPMux     :1,  /* �Ƿ�Э��PPP MUX */
          bNegoDNSEnable   :1, /* ����POECЭ��DNS */
          bLqmNegEnable    :1, /* �Ƿ�Э��LQM */
          bNegoOSICPEnable :1, /* �Ƿ�Э��OSI */
          bReserved   :1;

    ULONG ulNegTimeOut;

    USHORT usMaxMpBindNum;/*������·��*/
    USHORT usMinFragLen; /*MP��ʼ�ֶε���С����, added by pengjimei 2001/09/17*/
    ULONG  ulBindType;/*add by huzhiyong for new development 2002/01/22 */
    ULONG  ulBindVTNum;/*add by huzhiyong for new development 2002/01/22 */
    ULONG  ulEndpointDiscriminator; /*MP�ն�������ֵ*/
    
    USHORT usMaxDelayLFI; /* Add by Chenxia, 2002/10/18, for QoS transplant */
    USHORT usLqmPeriod;   /* LQM ��������ֵ */
    USHORT usUpSublinkLowLimit; /* mp�ӿڳ�Ա�˿�UP���ﵽ��ֵʱ�Ž��������Э�� */
    UCHAR  ucNegoMagicNum;      /* �Ƿ�Э��ħ���ֱ�� */
    UCHAR  ucSelfLoop;          /* �Ƿ������Ի�ģʽ��� */
    UCHAR  ucMpDiscardRequest;  /* MP�ӿ��Ƿ���discard request���� */
    UCHAR  ucDealAcfcPfc;       /* �Ƿ���ܺʹ���ACFC��PFCЭ��ѡ�Ĭ���ǽ��ܵ� */
    UCHAR  ucPadding[2];
    ULONG  ulClosePercentage;   /* �趨�Ĺر���·������ */
    ULONG  ulResumePercentage;  /* �趨������������·������ */
    ULONG  ulPrimDNSIPAddr;     /* �趨��Primary DNS Server��ַ */
    ULONG  ulSndDNSIPAddr;      /* �趨��Secondary DNS Server��ַ */

    UCHAR cChapHostName[PPP_MAXUSERNAMELEN + 1];
    UCHAR cChapPassword[PPP_MAXUSERPWDLEN + 1];
    UCHAR cPapUserName[PPP_MAXUSERNAMELEN + 1];
    UCHAR cPapPwd[PPP_MAXUSERPWDLEN + 1];
    /* BAPCONFIGINFO_S stBapConfigInfo; */   /* BAP/BACP������Ϣ */

    USHORT  iphc_tcp_space;
    USHORT  iphc_non_tcp_space;
    USHORT usFMaxPeriod;    /* �������ͷ�TCPѹ������������ */
    USHORT usFMaxTime;      /* ���������ײ����������ʱ�� */
    USHORT usMaxHeader;     /* ��ѹ���ײ���󳤶� */
    UCHAR  ucRtpCompression;/* Э��(Enhanced) RTP Compression��ѡ������ */
    UCHAR  ucCompressType;  /* ����ѹ������ */
    /* End of addition for IPHC,2005/09/19*/
    LONG   lCCOMPANY_FORMAT;
    LONG   lDELETE_UDP_CHKSUM;
    
    UCHAR  ucEnableUniDirection;/*�Ƿ�֧��IPHC��ͨ����,add by wuhailan,2008-04-11.*/
    UCHAR  ucPadding_2[3];

    USHORT usDefaultPid;        /* Default PID */
    USHORT usSubFrameLen;       /* �����֡���� */
    USHORT usFrameLen;          /* ��󸴺�֡���� */
    USHORT usSubFrameCount;     /* �����֡�� */
    USHORT usMuxDelay;          /* ����ĸ���ʱ�� */
    
    UCHAR  ucMhfCode;           /* MHFѡ���codeֵ 2:������ͷ��ʽ��6:������ͷ��ʽ */ 
    UCHAR  ucMhfClass;          /* MHFѡ���classֵ:��Ӧͷ��ʽ��֧�ֵĵȼ��� */
    ULONG  ulMcPrefixESum;      /* ���ڵ�ǰ׺ʡ��ӳ�����Ŀ */
    ULONG  ulNcpResendTime;     /* LCP��OPENʱ��NCP����һ��CR���ĺ�����ʱ����һ��NCP CR���ĵ�ʱ�䣬��Χ��0~6000���� */
    MC_PREFIXE_S *pstPrefixE;/* ǰ׺ʡ��ӳ��� */  /* ��Ҫ:Ŀǰ������״Ҫ����ֶα��������; ����ᵼ���߼��쳣 */
}PPPCONFIGINFO_S;


typedef struct tagPppAuthResult
{
    ULONG ulResult;                                  
    ULONG ulUserID;    
    ULONG ulIfnetIndex;                               
    ULONG ulUserType;     
    USHORT usChap;
    CHAR szCallBackDialString[PPP_CALLINGNUM_LEN + 1];
    UCHAR ucPadding_1; 
    ULONG ulIsCallBackUser;                          
    ULONG ulPerUserCfgNum;
    CHAR* pszPerUserCfg[PPP_MAXPERUSERCFGLEN];
    ULONG ulTunnelType; 
    ULONG ulTunnelServerIPNum;                          
    ULONG pulTunnelServerIP[PPPMAXTUNNELSERVERNUM];   
    SHORT   sVpdnGroupNumber;
    UCHAR ucPadding_2[2]; 
}PPPAUTHRESULT_S; 

/*�˲鿪��״̬�ṹ*/
typedef struct tagPppVerifySwitch
{
    ULONG ulSwitch; /*�˲鿪��:1-ʹ��;0-ȥʹ��*/ 
    ULONG ulPeriod; /*�˲�����,[1,0xffffffff),��λs*/   
    ULONG ulIfNum;  /*ÿ�κ˲�ӿ���,[1,0xffffffff)*/
}PPPVERIFYSWITCH_S;

/* IPHCͳ��ס�����ݽṹ */
typedef struct tagTCPIP_IPHC_STATISTICS
{
    ULONG ulRcvTotal;           /* ���ձ������� */
    ULONG ulRcvTcpCompressed;   /* �ɹ���ѹ����TCP������ */
    ULONG ulRcvNoTcpCompressed; /* �ɹ���ѹ���ķ�TCP������ */
    ULONG ulRcvError;           /* ����ʧ�ܵı����� */
    
    ULONG ulSndTotal;           /* ���ͱ������� */
    ULONG ulSndTcpCompressed;   /* �ɹ�ѹ����TCP������ */
    ULONG ulSndNoTcpCompressed; /* �ɹ�ѹ���ķ�TCP������ */
    ULONG ulSndTcpFullHead;     /* ���������ײ���TCP������ */
    ULONG ulSndNoTcpFullHead;   /* ���������ײ��ķ�TCP������ */
}TCPIP_IPHC_STATISTICS_S;

/* PPPЭ��Down��ص���Ϣ */
typedef struct tagPPPDOWNINFO
{
    ULONG ulDownReason;     /* Down Reason */
    ULONG ulWarningRecord;  /* PPPЭ�̹����ж���ͨ���Э��ʧ�ܸ澯��¼ */
}PPPDOWNINFO_S;

/**********************************************************************
*                        �����ṩ�����Ͷ�����û�API����
***********************************************************************/

/************************ ������ʾ��Ϣ ************************/
typedef VOID  (* PPP_GetPeerCallBack_PF)(ULONG ulUserID, ULONG ulIfnetIndex, ULONG ulPeerIPAddress);
typedef ULONG ( * NotifyIpcpDown_HOOK_FUNC)(ULONG ulIfIndex);
typedef ULONG ( * PPPShellAuthRequest)(ULONG ulIfnetIndex, PPPAUTHMSG_S *pMsg);
typedef ULONG ( * PPPShellChapGetUserPsw)(PPPAUTHMSG_S *pstMsg);
typedef ULONG ( * PPPAllocPeerIpAddr)(ULONG ulUserID, ULONG ulIfnetIndex,  PPP_GetPeerCallBack_PF pfGetPeerCallBack);
typedef ULONG ( * PPPFreeAddr)(ULONG ulUserID, ULONG ulIfnetIndex, ULONG ulPeerIPAddress);
typedef ULONG ( * GetLQRStat_HOOK_FUNC)(ULONG ulIfIndex,TCPIP_LQR_STAT_S *pstLQRStat);
typedef ULONG ( * NotifyPppDns_HOOK_FUNC)(ULONG ulIfIndex, ULONG ulSetYes,ULONG ulPriDns, ULONG ulSecDns);
 /* ע���ȡPPP��Ϣ���Ӻ��� */
typedef ULONG ( * GET_PPP_NEGO_IP_HOOK_FUN) (ULONG ulIfIndex, ULONG ulLocalIP, ULONG aulDNSIP[],
                                             ULONG ulRemoteIP, ULONG ulMTU, ULONG ulFlag );

/*******************************************************************************
*    Func Name: TCPIP_ShowPPPEffectiveCfgByIfName
*  Description: ��ʾPPP��·��ǰ��Ч���ò���
*        Input: CHAR *pszIfName:�ӿ���ָ��
*               ULONG ulProtocol:��Э���
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   chenfutian69112         Create
*
*******************************************************************************/

extern VOID TCPIP_ShowPPPEffectiveCfgByIfName(CHAR *pszIfName,ULONG ulProtocol);
/*******************************************************************************
*    Func Name: TCPIP_ShowIfIPHCConfig
*  Description: ��ʾPPP�ӿڵ�IPHC���������Ϣ
*        Input: CHAR *pszIfName:�ӿ���ָ��
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   chenfutian69112         Create
*
*******************************************************************************/
extern VOID TCPIP_ShowIfIPHCConfig(CHAR *pszIfName);
/*******************************************************************************
*    Func Name: TCPIP_ShowIPHCContextByIfName
*  Description: ��ʾPPP�ӿڵ���������ϸ��Ϣ
*        Input: CHAR *pszIfName:�ӿ���ָ��
*               ULONG ulPacketType:���ĸ�ʽ��ǣ��Ƿ�ΪTCP��ʽ��
*               ULONG ulFlag:ѹ��/��ѹ�����
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   chenfutian69112         Create
*
*******************************************************************************/
extern VOID TCPIP_ShowIPHCContextByIfName(CHAR *pszIfName, ULONG ulPacketType, ULONG ulFlag);
/*******************************************************************************
*    Func Name: TCPIP_ShowIfIPHCStat
*  Description: ��ʾPPP�ӿڵ�IPHC����ͳ����Ϣ
*        Input: CHAR *pszIfName:ָ��ӿ����Ƶ�ָ��
*               ULONG ulPacketType:TCP/non-TCP��ʽ���
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   chenfutian69112         Create
*
*******************************************************************************/
extern VOID TCPIP_ShowIfIPHCStat(CHAR *pszIfName, ULONG ulPacketType);
/*******************************************************************************
*    Func Name: TCPIP_ShowPPPStateByIfName
*  Description: ��ʾָ���ӿڵ�Э��״̬��Ϣ
*        Input: CHAR *pszIfName:ָ��ӿ����Ƶ�ָ��
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   chenfutian69112         Create
*
*******************************************************************************/
extern VOID TCPIP_ShowPPPStateByIfName(CHAR *pszIfName);
/*******************************************************************************
*    Func Name: TCPIP_GetPPPInfo
*  Description: ��ȡPPP����Э����ƿ�
*        Input: ULONG ulIfIndex:�ӿ�����
*               ULONG ulType:Ҫ��ȡ��Э����ƿ�����
*               VOID *pstPppInfo:Ҫ���صĿ��ƿ�ṹ
*       Output: pstPppInfo:Ҫ���صĿ��ƿ�ṹ
*       Return: VOS_OK                    �ɹ�
*               PPP_PARA_NULLPOINTER      ָ�����ֵΪ��
*               PPP_NOTHISINTERF_ERROR    �ӿ�����ֵΪ0
*               PPP_IFNETCB_NOEXIST       ָ���ӿڲ�����
*               PPP_NOENCAP_ERROR         ָ���ӿڷ�PPP��·����
*               PPP_PPPCB_NOEXIST         ָ���ӿڵ�PPP���ƿ鲻����
*               PPP_PROTOCOL_INVALID      ָ����Э��������Ч
*               PPP_IPCPCB_NOEXIST        IPCP���ƿ鲻����
*               PPP_MUXCPCB_NOEXIST       PPPMUX���ƿ鲻����
*               PPP_CONFIGINFO_NOEXIST    PPP������Ϣ���ƿ鲻����
*               VOS_ERR                   PPPģ���ڲ�����
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_GetPPPInfo(ULONG ulIfIndex, ULONG ulType,VOID *pstPppInfo);
/*******************************************************************************
*    Func Name: TCPIP_GetFsmState
*  Description: ��ȡ����Э��״̬��״̬
*        Input: ULONG ulIfIndex:�ӿ�����
*               ULONG ulProtocol:Э���
*               ULONG *pulState:״̬��״̬
*       Output: 
*       Return: VOS_OK                    �ɹ�
*               PPP_WRONGPARA_ERROR       ��������ָ�����Ϊ�գ�
*               PPP_NOTHISINTERF_ERROR    ָ���Ľӿ�����Ϊ0
*               PPP_IFNETCB_NOEXIST       ָ���ӿڲ�����
*               PPP_NOENCAP_ERROR         ָ���ӿڷ�PPP��·����
*               PPP_PPPCB_NOEXIST         ָ���ӿڵ�PPP���ƿ鲻����
*               VOS_ERR                   ָ����Э��Ŵ���
*               PPP_FSMSTATE_ERR          Э��״̬������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_GetFsmState(ULONG ulIfIndex, ULONG ulProtocol, ULONG *pulState);
/*******************************************************************************
*    Func Name: TCPIP_GetNegoResult
*  Description: ��ȡЭ�̽��
*        Input: ULONG ulIfIndex:�ӿ�����
*               PPPNEGORESULT_S *pstGotResult:����Э�̽ӿ�����ṹָ��
*               PPPNEGORESULT_S *pstHisResult:�Զ�Э�̽������ṹָ��
*       Output: PPPNEGORESULT_S *pstGotResult:����Э�̽ӿ�����ṹָ��
*               PPPNEGORESULT_S *pstHisResult:�Զ�Э�̽������ṹָ��
*       Return: VOS_OK                    �ɹ�  
*               PPP_PARA_NULLPOINTER      ָ�����ֵΪ��
*               PPP_IFNETCB_NOEXIST       ָ���ӿڲ�����
*               PPP_NOENCAP_ERROR         ָ���ӿڷ�PPP��·����
*               PPP_PPPCB_NOEXIST         ָ���ӿڵ�PPP���ƿ鲻����
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_GetNegoResult ( ULONG ulIfIndex,  PPPNEGORESULT_S *pstGotResult, PPPNEGORESULT_S *pstHisResult );
/*******************************************************************************
*    Func Name: TCPIP_GetPPPDebugInfo
*  Description: ��ȡPPP Debug��Ϣ
*        Input: ULONG ulIfIndex:�ӿ�������Ϊ0ʱ��ʾȡȫ��debug��Ϣ��
*               PPPDEBUGINFO_S *pstPppDebugInfo:��ȡ��debug��Ϣ������ָ��
*       Output: PPPDEBUGINFO_S *pstPppDebugInfo:��ȡ��debug��Ϣ������ָ��
*       Return: VOS_OK                           �ɹ�
*               PPP_PARA_NULLPOINTER             ָ�����ֵΪ��
*               PPP_NOTHISINTERF_ERROR           �ӿ�����ֵΪ0
*               PPP_IFNETCB_NOEXIST              ָ���ӿڲ�����
*               PPP_NOENCAP_ERROR                ָ���ӿڷ�PPP��·����
*               PPP_PPPCB_NOEXIST                ָ���ӿڵ�PPP���ƿ鲻����
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_GetPPPDebugInfo(ULONG ulIfIndex, PPPDEBUGINFO_S *pstPppDebugInfo);
/*******************************************************************************
*    Func Name: TCPIP_GetPppPhase
*  Description: ��ȡPPPЭ�������Ľ׶�
*        Input: ULONG ulIfIndex:�ӿ�����
*               ULONG *pulPhase:PPPЭ�������Ľ׶�
*       Output: pulPhase:PPPЭ�������Ľ׶�
*       Return: VOS_OK                        �ɹ�
*               PPP_NOTHISINTERF_ERROR        �ӿ�����Ϊ0
*               PPP_IFNETCB_NOEXIST           ָ���ӿڲ�����
*               PPP_NOENCAP_ERROR             ָ���ӿڷ�PPP��·����
*               PPP_PPPCB_NOEXIST             ָ���ӿڵ�PPP���ƿ鲻����
*               PPP_WRONGPARA_ERROR           ��������ָ�����Ϊ�գ�
*               PPP_NEGOPHASE_ERR             Э�̽׶δ���
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_GetPppPhase(ULONG ulIfIndex, ULONG *pulPhase);
/*******************************************************************************
*    Func Name: TCPIP_SetInterfaceNego
*  Description: ����ĳ���ӿ��Ƿ����LCP/NCPЭ��
*        Input: ULONG ulIfIndex:�ӿ�����
*               ULONG ulNegoLCP:�Ƿ�Э��LCP��0 ��Э�̣�1 Э��
*               ULONG ulNegoNCP:�Ƿ�Э��NCP��0 ��Э�̣�1 Э��
*       Output: 
*       Return: VOS_OK                             �ɹ�
*               PPP_HA_IS_SMOOTHINGHA              ����ƽ��������ֶ���������
*               PPP_WRONGPARA_ERROR                ���������ǷǱ�����Ϊ0��1��
*               PPP_NOTHISINTERF_ERROR             �ӿ�����ֵΪ0
*               PPP_IFNETCB_NOEXIST                ָ���ӿڲ�����
*               PPP_NOENCAP_ERROR                  ָ���ӿڷ�PPP��·����
*               PPP_PPPCB_NOEXIST                  ָ���ӿڵ�PPP���ƿ鲻����
*               VOS_ERR                            VT�ӿڱ�����LCP
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_SetInterfaceNego(ULONG ulIfIndex,ULONG ulNegoLCP,ULONG ulNegoNCP);
/*******************************************************************************
*    Func Name: TCPIP_GetInterfaceNego
*  Description: ��ȡĳ���ӿ��Ƿ�Ҫ����LCP/NCPЭ��
*        Input: ULONG ulIfIndex:�ӿ�����
*               ULONG *pulNegoLCP:�Ƿ�Э��LCP��0 ��Э�̣�1 Э��
*               ULONG *pulNegoNCP:�Ƿ�Э��NCP��0 ��Э�̣�1 Э��
*       Output: ULONG *pulNegoLCP:�Ƿ�Э��LCP��0 ��Э�̣�1 Э��
*               ULONG *pulNegoNCP:�Ƿ�Э��NCP��0 ��Э�̣�1 Э��
*       Return: VOS_OK                          �ɹ�
*               PPP_WRONGPARA_ERROR             ���������ǷǱ�����Ϊ0��1��
*               PPP_PPPCB_NOEXIST               ָ���ӿڵ�PPP���ƿ鲻����
*               PPP_CONFIGINFO_NOEXISTR         ָ���ӿ�������Ϣ���ƿ鲻����
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_GetInterfaceNego (ULONG ulIfIndex, ULONG *pulNegoLCP, ULONG *pulNegoNCP);
/*******************************************************************************
*    Func Name: TCPIP_GetPppStatics
*  Description: ��ȡ�ӿ��µ�IP����ͳ����Ϣ
*        Input: ULONG ulIfIndex:�ӿ�����
*               PPPSTATISTIC_S * pstStat:����ı���ͳ����Ϣ
*       Output: PPPSTATISTIC_S * pstStat:����ı���ͳ����Ϣ
*       Return: VOS_OK                  �ɹ�
*               PPP_PARA_NULLPOINTER    ָ�����ֵΪ��
*               PPP_IFNETCB_NOEXIST     ָ���ӿڲ�����
*               PPP_NOENCAP_ERROR       ָ���ӿڷ�PPP��·����
*               VOS_ERR                 PPPģ���ڲ�����
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_GetPppStatics(ULONG ulIfIndex, PPPSTATISTIC_S * pstStat);
/*******************************************************************************
*    Func Name: TCPIP_ClrPppStatics
*  Description: ����ӿ��µ�PPP����ͳ����Ϣ
*        Input: ULONG ulIfIndex:�ӿ�����
*       Output: 
*       Return: VOS_OK                                 �ɹ�
*               PPP_IFNETCB_NOEXIST                    ָ���ӿڲ�����
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_ClrPppStatics(ULONG ulIfIndex);
/*******************************************************************************
*    Func Name: TCPIP_SetInterfaceNegoOsicp
*  Description: ����PPP�ӿ��Ƿ����OSICPЭ��
*        Input: ULONG ulIfIndex:�ӿ�����
*               ULONG ulNegoOSICP:ʹ�ܿ���
*       Output: 
*       Return: VOS_OK                        �ɹ�
*               PPP_WRONGPARA_ERROR           ��������      
*               PPP_IFNETCB_NOEXIST           �ӿڿ��ƿ鲻����
*               PPP_NOENCAP_ERROR             ָ���ӿڷ�PPP��·����
*               PPP_CANOT_SET_OSICP           �ýӿڲ��������Ƿ�Э��OSICP
*               PPP_PPPCB_NOEXIST             ָ���ӿڵ�PPP���ƿ鲻����
*               PPP_CONFIGINFO_NOEXIST        ָ���ӿڵ�������Ϣ������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_SetInterfaceNegoOsicp(ULONG ulIfIndex, ULONG ulNegoOSICP);
/*******************************************************************************
*    Func Name: TCPIP_GetInterfaceNegoOsicp
*  Description: ��ѯPPP�ӿ�OSICPЭ������
*        Input: ULONG ulIfIndex:�ӿ�����
*               ULONG *pulNegoOSICP:������Žӿ�OSICPЭ�̵�����
*       Output: ULONG *pulNegoOSICP:������Žӿ�OSICPЭ�̵�����
*       Return: VOS_OK                              �ɹ�
*               PPP_WRONGPARA_ERROR                 ��������
*               PPP_IFNETCB_NOEXIST                 �ӿڿ��ƿ鲻����
*               PPP_NOENCAP_ERROR                   ָ���ӿڷ�PPP��·����
*               PPP_CANOT_SET_OSICP                 �ýӿڲ�֧�ֲ���OSICPѡ��
*               PPP_PPPCB_NOEXIST                   ָ���ӿڵ�PPP���ƿ鲻����
*               PPP_CONFIGINFO_NOEXIST              ָ���ӿڵ�������Ϣ������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_GetInterfaceNegoOsicp(ULONG ulIfIndex, ULONG *pulNegoOSICP);
/*******************************************************************************
*    Func Name: TCPIP_EnableACFC
*  Description: ʹ��/ȥʹ��Э��ACFC
*        Input: ULONG ulIfIndex:PPP��·�Ľӿ�����
*               ULONG ulSetYes:���ÿ��� 1��ʹ�ܣ� 0��ȥʹ�ܣ��������Ƿ�
*       Output: 
*       Return: VOS_OK                          �ɹ�
*               PPP_HA_IS_SMOOTHING             HA����ƽ��������ֶ���������
*               PPP_NOTHISINTERF_ERROR          �ӿ�����ֵΪ0
*               PPP_IFNETCB_NOEXIST             ָ���ӿڲ�����
*               PPP_NOENCAP_ERROR               ָ���ӿڷ�PPP��·����
*               PPP_PPPCB_NOEXIST               ָ���ӿڵ�PPP���ƿ鲻����
*               PPP_CONFIGINFO_NOEXIST          ָ���ӿڵ�������Ϣ������
*               PPP_WRONGPARA_ERROR             �������Ϸ������ر�����Ϊ0��1��
*               PPP_CONFIG_CONFLICT             PPP������ó�ͻ��PPPoE��·��֧��ACFC��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_EnableACFC ( ULONG ulIfIndex, ULONG ulSetYes );
/*******************************************************************************
*    Func Name: TCPIP_SetPppAuthType
*  Description: ����PPP��֤������
*        Input: ULONG ulIfIndex:�ӿ�����
*               ULONG ulType:��֤���ͣ�0����������֤��1������pap��֤��2������chap��֤,3---ALL
*       Output: 
*       Return: VOS_OK                             �ɹ�
*               VOS_ERR                            ʧ��
*               PPP_HA_IS_SMOOTHING                HA����ƽ��������ֶ���������
*               PPP_WRONGPARA_ERROR                �������Ϸ�������/�ǷǱ�����Ϊ0��1��
*               PPP_NOTHISINTERF_ERROR             �ӿ�����ֵΪ0
*               PPP_IFNETCB_NOEXIST                ָ���ӿڲ�����
*               PPP_NOENCAP_ERROR                  ָ���ӿڷ�PPP��·����
*               PPP_PPPCB_NOEXIST                  ָ���ӿڵ�PPP���ƿ鲻����
*               PPP_CONFIGINFO_NOEXIST             ָ���ӿڵ�������Ϣ������
*               PPP_CONFIG_CONFLICT                PPP���ó�ͻ��PAP��CHAP����ͬʱʹ�ܣ�
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_SetPppAuthType(ULONG ulIfIndex, ULONG ulType);


extern ULONG TCPIP_GetPppAuthType(ULONG ulIfIndex, ULONG *pulType, ULONG *pulCallInAuth);

/*******************************************************************************
*    Func Name: TCPIP_SetChapNamePwd
*  Description: ����chap��֤ʱ���û�������֤pwd
*        Input: ULONG ulIfIndex:�ӿ�����
*               ULONG ulSetYes:�Ƿ����ã�0Ϊ��1Ϊ��
*               ULONG usEncrypt:pwd�Ƿ�enc ��1Ϊ����enc ��0Ϊȡ��
*               UCHAR *pcP***W***:�����õ�pwdָ��
*               UCHAR *pcUsername:�����õ��û���ָ��
*       Output: 
*       Return: VOS_OK                     �ɹ�
*               PPP_HA_IS_SMOOTHING        HA����ƽ��������ֶ���������
*               PPP_WRONGPARA_ERROR        �������Ϸ����Ƿ�ֵ��Ϊ0��1��
*               PPP_NOTHISINTERF_ERROR     �ӿ�����ֵΪ0
*               PPP_IFNETCB_NOEXIST        ָ���ӿڲ�����
*               PPP_NOENCAP_ERROR          ָ���ӿڷ�PPP��·����
*               PPP_PPPCB_NOEXIST          ָ���ӿڵ�PPP���ƿ鲻����
*               PPP_CONFIGINFO_NOEXIST     ָ���ӿڵ�������Ϣ������
*               PPP_PARA_NULLPOINTER       ָ�����ֵΪ��
*               PPP_HOSTNAME_INVALID       ��Ч���û���������Ϊ0�򳬹�72��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_SetChapNamePwd(ULONG ulIfIndex,ULONG ulSetYes,  ULONG usEncrypt, UCHAR *pcPassword, UCHAR *pcUsername);
/*******************************************************************************
*    Func Name: TCPIP_ClrIfIPHCContext
*  Description: ����ӿڵ���������Ϣ
*        Input: ULONG ulIfIndex:�ӿ�����
*       Output: 
*       Return: VOS_OK                           �ɹ�
*               PPP_CONFIGINFO_NOTEXIST          ������Ϣ������
*               PPP_IPHC_DISABLE                 IPHC����δʹ��
*               PPP_IPHC_CONTEXT_NOTEXIST        context�洢�ṹ������
*               PPP_IFNETCB_NOEXIST              �ӿڲ�����
*               PPP_NOENCAP_ERROR                �ӿ����Ͳ���PPP
*               PPP_PPPCB_NOEXIST                PPP���ƿ鲻����
*               VOS_ERR                          ��������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_ClrIfIPHCContext (ULONG ulIfIndex);
/*******************************************************************************
*    Func Name: TCPIP_SetPPPCompress
*  Description: ����ppp�Ƿ����ͷ��ѹ��
*        Input: ULONG ulIfIndex:�ӿ�����
*       Output: 
*       Return: VOS_OK                          �ɹ�
*               PPP_GETCONFIGINFO_FAIL          ��ȡ������Ϣʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_SetPPPCompress(ULONG ulIfIndex);
/*******************************************************************************
*    Func Name: TCPIP_SetPPPCompressType
*  Description: ���ýӿڵ�IPHCѹ������
*        Input: ULONG ulIfIndex:�ӿ�����
*               ULONG ulCompressType:����ѹ������
*               ULONG ulReset:����Ĭ��ֵ��ʶ��0�����ã���0����
*       Output: 
*       Return: VOS_OK                    �ɹ�
*               PPP_HA_IS_SMOOTHING       HA����ƽ��������ֶ���������
*               PPP_IPHC_DISABLE          �ӿ���δʹ��IPHC����
*               PPP_WRONGPARA_ERROR       �������Ϸ�
*               PPP_IFNETCB_NOEXIST       �ӿڲ�����
*               PPP_NOENCAP_ERROR         �ӿ����Ͳ���PPP
*               PPP_PPPCB_NOEXIST         PPP���ƿ鲻����
*               PPP_CONFIGINFO_NOEXIST    �ӿ�������Ϣ������
*               VOS_ERR                   ��������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_SetPPPCompressType(ULONG ulIfIndex,ULONG ulCompressType,ULONG ulReset);
/*******************************************************************************
*    Func Name: TCPIP_SetPPPDebug
*  Description: ����debugѡ��
*        Input: ULONG ulIfIndex:�ӿ�����
*               ULONG ulDebugAll:�Ƿ�ȫ���ӿ����ã�1Ϊ��������ѡ�0Ϊ���õ���ѡ��
*               ULONG ulSetYes:�Ƿ����õı�־��1Ϊʹ�ã�0Ϊȡ���������Ƿ�
*               ULONG ulType:ѡ������
*               USHORT usProtocol:ѡ��Э�����ͣ�ΪPPP_LCP��PPP_IPCP��
*               ULONGulPacketNum:��ӡVerbose��Ϣ�Ĵ���
*               ULONG ulPacketOctets:��ӡVerbose��Ϣ��ǰN���ֽ���
*       Output: 
*       Return: VOS_OK                           �ɹ�
*               PPP_WRONGPARA_ERROR              �������Ϸ�
*               PPP_NOENCAP_ERROR                �ӿ����Ͳ���PPP
*               PPP_PPPCB_NOEXIST                PPP���ƿ鲻����
*               VOS_ERR                          ��������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_SetPPPDebug(ULONG ulIfIndex, ULONG ulDebugAll, ULONG ulSetYes, ULONG ulType,USHORT usProtocol,ULONG ulPacketNum, ULONG ulPacketOctets);
/*******************************************************************************
*    Func Name: TCPIP_DelPPPUdpChkSum
*  Description: �����Ƿ�ɾ��UDPУ��ͣ����Ƿ�UDPУ�����0��
*        Input: ULONG ulIfIndex:�ӿ�����
*               ULONG ulDeleteUdpChkSum:�Ƿ�ɾ��UDPУ��ͱ�ǣ�1 ɾ����0��ɾ�������� �Ƿ�
*       Output: 
*       Return: VOS_OK                      �ɹ�
*               PPP_IPHC_DISABLE            IPHC���ܲ�����
*               PPP_WRONGPARA_ERROR         �������Ϸ�
*               PPP_IFNETCB_NOEXIST         �ӿڲ�����
*               PPP_NOENCAP_ERROR           �ӿ����Ͳ���PPP
*               PPP_PPPCB_NOEXIST           PPP���ƿ鲻����
*               PPP_CONFIGINFO_NOEXIST      �ӿ�������Ϣ������
*               PPP_HA_IS_SMOOTHING         HA����ƽ��������ֶ���������
*               VOS_ERR                     ��������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_DelPPPUdpChkSum (ULONG ulIfIndex, ULONG ulDeleteUdpChkSum);
/*******************************************************************************
*    Func Name: TCPIP_SetFMaxPeriod
*  Description: ���ýӿڵ�����������ͷ�TCP�ײ�ѹ��������
*        Input: ULONG ulIfIndex:�ӿ�����
*               ULONG ulFMaxPeriod:����������ͷ�TCP�ײ�ѹ��������
*               ULONG ulReset:����Ĭ��ֵ��ʶ��0 �����ã���0 ����
*       Output: 
*       Return: VOS_OK                        �ɹ�
*               PPP_IPHC_DISABLE              IPHC���ܲ�����
*               PPP_WRONGPARA_ERROR           �������Ϸ�
*               PPP_IFNETCB_NOEXIST           �ӿڲ�����
*               PPP_NOENCAP_ERROR             �ӿ����Ͳ���PPP
*               PPP_PPPCB_NOEXIST             PPP���ƿ鲻����
*               PPP_CONFIGINFO_NOEXIST        �ӿ�������Ϣ������
*               PPP_HA_IS_SMOOTHING           HA����ƽ��������ֶ���������
*               VOS_ERR                       ��������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_SetFMaxPeriod(ULONG ulIfIndex, ULONG ulFMaxPeriod, ULONG ulReset);
/*******************************************************************************
*    Func Name: TCPIP_SetFMaxTime
*  Description: ���ýӿڵķ��������ײ������ʱ��
*        Input: ULONG ulIfIndex:�ӿ�����
*               ULONG ulFMaxTime:���������ײ������ʱ��
*               ULONG ulReset:����Ĭ��ֵ��ʶ��0 �����ã���0 ����
*       Output: 
*       Return: VOS_OK                                �ɹ�
*               PPP_IPHC_DISABLE                      IPHC���ܲ�����
*               PPP_WRONGPARA_ERROR                   �������Ϸ�
*               PPP_IFNETCB_NOEXIST                   �ӿڲ�����
*               PPP_NOENCAP_ERROR                     �ӿ����Ͳ���PPP
*               PPP_PPPCB_NOEXIST                     PPP���ƿ鲻����
*               PPP_CONFIGINFO_NOEXIST                �ӿ�������Ϣ������
*               PPP_HA_IS_SMOOTHING                   HA����ƽ��������ֶ���������
*               VOS_ERR                               ��������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_SetFMaxTime(ULONG ulIfIndex, ULONG ulFMaxTime, ULONG ulReset);
/*******************************************************************************
*    Func Name: TCPIP_EnableIPHC
*  Description: ʹ��/ȥʹ�ܽӿڵ�IPHC����
*        Input: ULONG ulIfIndex:�ӿ�����
*               ULONG ulEnable:ʹ��/ȥʹ�ܱ�ǣ�0  ȥʹ�ܣ���0  ʹ��
*               ULONG ulCCompany:�Զ��Ƿ�C��˾��0  ���ǣ���0 ��
*       Output: 
*       Return: VOS_OK                            �ɹ�
*               PPP_HA_IS_SMOOTHING               HA����ƽ��������ֶ���������
*               PPP_NOTHISINTERF_ERROR            �ӿ�����ֵΪ0
*               PPP_IFNETCB_NOEXIST               ָ���ӿڲ�����
*               PPP_NOENCAP_ERROR                 ָ���ӿڷ�PPP��·����
*               PPP_PPPCB_NOEXIST                 ָ���ӿڵ�PPP���ƿ鲻����
*               PPP_CONFIGINFO_NOEXIST            ָ���ӿڵ�������Ϣ������
*               PPP_CONFIG_CONFLICT               ���ó�ͻ
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_EnableIPHC(ULONG ulIfIndex, ULONG ulEnable, ULONG ulCCompany);
/*******************************************************************************
*    Func Name: TCPIP_SetMaxHeader
*  Description: ���ýӿڵ�����ѹ���ײ�����
*        Input: ULONG ulIfIndex:�ӿ�����
*               ULONG ulMaxHeader:����ѹ���ײ�����
*               ULONG ulReset:����Ĭ��ֵ��ʶ��0 �����ã���0 ����
*       Output: 
*       Return: VOS_OK                  �ɹ�
*               PPP_IPHC_DISABLE        IPHC���ܲ�����
*               PPP_WRONGPARA_ERROR     �������Ϸ�
*               PPP_IFNETCB_NOEXIST     �ӿڲ�����
*               PPP_NOENCAP_ERROR       �ӿ����Ͳ���PPP
*               PPP_PPPCB_NOEXIST       PPP���ƿ鲻����
*               PPP_CONFIGINFO_NOEXIST  �ӿ�������Ϣ������
*               PPP_HA_IS_SMOOTHING     HA����ƽ��������ֶ���������
*               VOS_ERR                 ��������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_SetMaxHeader(ULONG ulIfIndex, ULONG ulMaxHeader, ULONG ulReset);
/*******************************************************************************
*    Func Name: TCPIP_SetNegoSubOptions
*  Description: ���ýӿ��Ƿ�Э����ѡ��
*        Input: ULONG ulIfIndex:�ӿ�����
*               ULONG ulSetYes:Э�̱�ʶ��ʶ��0��Э�̣���0Э�̣������Ƿ�
*       Output: 
*       Return: VOS_OK                           �ɹ�
*               PPP_IPHC_DISABLE                 IPHC���ܲ�����
*               PPP_IFNETCB_NOEXIST              �ӿڲ�����
*               PPP_NOENCAP_ERROR                �ӿ����Ͳ���PPP
*               PPP_PPPCB_NOEXIST                PPP���ƿ鲻����
*               PPP_CONFIGINFO_NOEXIST           �ӿ�������Ϣ������
*               PPP_HA_IS_SMOOTHING              HA����ƽ��������ֶ���������
*               VOS_ERR                          ��������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_SetNegoSubOptions ( ULONG ulIfIndex, ULONG ulSetYes);
/*******************************************************************************
*    Func Name: TCPIP_SetPPPNegTime
*  Description: ����PPPЭ�̳�ʱ��ʱ��
*        Input: ULONG ulIfIndex:�ӿ�����
*               ULONG ulSetYes:�Ƿ����õı�־��1Ϊʹ�ã�0Ϊȡ���������Ƿ�
*               ULONG ulTimeoutTime:Э�̳�ʱʱ��
*       Output: 
*       Return: VOS_OK                      �ɹ�
*               VOS_ERR                     ʧ��
*               PPP_HA_IS_SMOOTHING         HA����ƽ��������ֶ���������
*               PPP_CONFIGINFO_NOEXIST      �û������������Ϣ������
*               PPP_WRONGPARA_ERROR         �������Ϸ�
*               PPP_NOTHISINTERF_ERROR      �ӿ�����Ϊ�գ�������
*               PPP_IFNETCB_NOEXIST         �ӿڲ�����
*               PPP_NOENCAP_ERROR           �ӿ����Ͳ���PPP
*               PPP_PPPCB_NOEXIST           PPP���ƿ鲻����
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_SetPPPNegTime(ULONG ulIfIndex, ULONG ulSetYes, ULONG ulTimeoutTime);
/*******************************************************************************
*    Func Name: TCPIP_SetNonTcpSpace
*  Description: ���ýӿڵķ�TCP���ĸ�ʽ���CID
*        Input: ULONG ulIfIndex:�ӿ�����
*               ULONG ulNonTcpSpace:non-TCP��ʽ���CIDֵ
*               ULONG ulReset:����Ĭ��ֵ��ʶ��0 �����ã���0 ����
*       Output: 
*       Return: VOS_OK                       �ɹ�
*               PPP_IPHC_DISABLE             IPHC���ܲ�����
*               PPP_WRONGPARA_ERROR          �������Ϸ�
*               PPP_IFNETCB_NOEXIST          �ӿڲ�����
*               PPP_NOENCAP_ERROR            �ӿ����Ͳ���PPP
*               PPP_PPPCB_NOEXIST            PPP���ƿ鲻����
*               PPP_CONFIGINFO_NOEXIST       �ӿ�������Ϣ������
*               PPP_HA_IS_SMOOTHING          HA����ƽ��������ֶ���������
*               VOS_ERR                      ��������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_SetNonTcpSpace(ULONG ulIfIndex, ULONG ulNonTcpSpace, ULONG ulReset);
/*******************************************************************************
*    Func Name: TCPIP_SetPapNameP**
*  Description: ����PAP��֤���û�����pwd
*        Input: ULONG ulIfIndex:�ӿ�����
*               ULONG ulSetYes:�Ƿ����õı�־��1Ϊʹ�ã�0Ϊȡ���������Ƿ����������ȡ�������������������
*               ULONG usEncrypt:pwd�Ƿ�enc ��1Ϊ����enc ��0Ϊȡ��
*               UCHAR *pcP***W***:pwd���ݣ���Ч���ȷ�enc pwd1��16����enc pwd24��
*               UCHAR *pcUsername:�û�������Ч����1��72��
*       Output: 
*       Return: VOS_OK                        �ɹ�
*               PPP_HA_IS_SMOOTHING           HA����ƽ��������ֶ���������
*               PPP_WRONGPARA_ERROR           �������Ϸ����Ƿ�ֵ��Ϊ0��1��
*               PPP_NOTHISINTERF_ERROR        �ӿ�����ֵΪ0
*               PPP_IFNETCB_NOEXIST           ָ���ӿڲ�����
*               PPP_NOENCAP_ERROR             ָ���ӿڷ�PPP��·����
*               PPP_PPPCB_NOEXIST             ָ���ӿڵ�PPP���ƿ鲻����
*               PPP_CONFIGINFO_NOEXIST        ָ���ӿڵ�������Ϣ���ƿ鲻����
*               PPP_PARA_NULLPOINTER          ָ�����ֵΪ��
*               PPP_CIPHERP***W***_WRONG      enc pwd���ô���
*               PPP_HOSTNAME_INVALID          ��Ч���û���������Ϊ0�򳬹�72��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_SetPapNamePwd(ULONG ulIfIndex,ULONG ulSetYes,  ULONG usEncrypt, UCHAR *pcPassword, UCHAR *pcUsername);
/*******************************************************************************
*    Func Name: TCPIP_EnablePFC
*  Description: ʹ��/ȥʹ��Э��PFC
*        Input: ULONG ulIfIndex:�ӿ�����
*               ULONG ulSetYes:���ÿ��أ� 1  ʹ�ܣ� 0  ȥʹ�ܣ������Ƿ�
*       Output: 
*       Return: VOS_OK                           �ɹ�
*               PPP_HA_IS_SMOOTHING              HA����ƽ��������ֶ���������
*               PPP_NOTHISINTERF_ERROR           �ӿ�����ֵΪ0
*               PPP_IFNETCB_NOEXIST              ָ���ӿڲ�����
*               PPP_NOENCAP_ERROR                ָ���ӿڷ�PPP��·����
*               PPP_PPPCB_NOEXIST                ָ���ӿڵ�PPP���ƿ鲻����
*               PPP_CONFIGINFO_NOEXIST           ָ���ӿڵ�������Ϣ������
*               PPP_WRONGPARA_ERROR              �������Ϸ������ر�����Ϊ0��1��
*               PPP_CONFIG_CONFLICT              PPP������ó�ͻ��PPPoE��·��֧��PFC��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_EnablePFC ( ULONG ulIfIndex, ULONG ulSetYes );
/*******************************************************************************
*    Func Name: TCPIP_SetRtpCompression
*  Description: ���ýӿ��Ƿ�Э��RTP Compression��ѡ�����Enhanced RTP Compression ��ѡ��
*        Input: ULONG ulIfIndex:�ӿ�����
*               ULONG ulRtpCompression:�Ƿ�Э��(Enhanced)RTP Compression��ѡ��
*               ULONG ulReset:����Ĭ��ֵ��ʶ��0 �����ã���0 ����
*       Output: 
*       Return: VOS_OK                          �ɹ�
*               PPP_IPHC_DISABLE                IPHC���ܲ�����
*               PPP_WRONGPARA_ERROR             �������Ϸ�
*               PPP_IFNETCB_NOEXIST             �ӿڲ�����
*               PPP_NOENCAP_ERROR               �ӿ����Ͳ���PPP
*               PPP_PPPCB_NOEXIST               PPP���ƿ鲻����
*               PPP_CONFIGINFO_NOEXIST          �ӿ�������Ϣ������
*               PPP_HA_IS_SMOOTHING             HA����ƽ��������ֶ���������
*               VOS_ERR                         ��������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_SetRtpCompression(ULONG ulIfIndex, ULONG ulRtpCompression, ULONG ulReset);
/*******************************************************************************
*    Func Name: TCPIP_SetTcpSpace
*  Description: ���ýӿڵ�TCP���ĸ�ʽ���CID
*        Input: ULONG ulIfIndex:�ӿ�����
*               ULONG ulTcpSpace:TCP��ʽ���CIDֵ
*               ULONG ulReset:����Ĭ��ֵ��ʶ��0 �����ã���0 ����
*       Output: 
*       Return: VOS_OK                      �ɹ�
*               PPP_IPHC_DISABLE            IPHC���ܲ�����
*               PPP_WRONGPARA_ERROR         �������Ϸ�
*               PPP_IFNETCB_NOEXIST         �ӿڲ�����
*               PPP_NOENCAP_ERROR           �ӿ����Ͳ���PPP
*               PPP_PPPCB_NOEXIST           PPP���ƿ鲻����
*               PPP_CONFIGINFO_NOEXIST      �ӿ�������Ϣ������
*               PPP_HA_IS_SMOOTHING         HA����ƽ��������ֶ���������
*               VOS_ERR                     ��������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_SetTcpSpace (ULONG ulIfIndex, ULONG ulTcpSpace, ULONG ulReset);
/*******************************************************************************
*    Func Name: TCPIP_SetPPPDebugSwitch
*  Description: ����ȫ��debug����
*        Input: ULONG ulPppDebugFlag:debug���أ�0  �رգ�1  �򿪣������Ƿ�
*       Output: 
*       Return: VOS_OK                         �ɹ�
*               VOS_ERR                        ʧ��
*               PPP_WRONGPARA_ERROR            �������Ϸ�
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_SetPPPDebugSwitch(ULONG ulPppDebugFlag);
/*******************************************************************************
*    Func Name: TCPIP_EnableVjComp
*  Description: �����Ƿ�ʹ��VJѹ��
*        Input: ULONG ulIfIndex:�ӿ�����
*               ULONG ulSetYes:ʹ�ܱ�־��0  �رգ�1  ʹ�ܣ������Ƿ�
*       Output: 
*       Return: VOS_OK                    �ɹ�
*               VOS_ERR                   ʧ��
*               PPP_WRONGPARA_ERROR       �������Ϸ�
*               PPP_HA_IS_SMOOTHING       HA����ƽ��������ֶ���������
*               PPP_NOTHISINTERF_ERROR    �ӿ�����Ϊ�գ�������
*               PPP_IFNETCB_NOEXIST       �ӿڲ�����
*               PPP_NOENCAP_ERROR         �ӿ����ͷ�PPP����
*               PPP_PPPCB_NOEXIST         PPP���ƿ鲻����
*               PPP_CONFIG_CONFLICT       PPP������ó�ͻ���ýӿ�����ʹ��IPHC��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_EnableVjComp(ULONG ulIfIndex, ULONG ulSetYes);
/*******************************************************************************
*    Func Name: TCPIP_SetDiscrSpecial
*  Description: ����MP֧��CBTS��Ʒ�ķǱ��Զ�������ʽ�Խ�
*        Input: ULONG ulSetYes:���ÿ��أ�1-֧��  0-��֧��
*       Output: 
*       Return: VOS_OK                   �ɹ�
*               VOS_ERR                  ʧ��  
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_SetDiscrSpecial ( ULONG ulSetYes);
/*******************************************************************************
*    Func Name: TCPIP_SetPPPResetTime
*  Description: ����PPP��λ��ʱ��
*        Input: ULONG ulTime:���õ��¼����
*       Output: 
*       Return: VOS_OK                  �ɹ�
*               VOS_ERR                 ʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_SetPPPResetTime(ULONG ulTime);
/*******************************************************************************
*    Func Name: TCPIP_SetLQMNeg
*  Description: �����Ƿ�ʹ��LQM����
*        Input: ULONG ulIfIndex:�ӿ�����
*               ULONG ulSetYes:ʹ�ܱ�־��0  ȥʹ�ܣ�1  ʹ�ܣ������Ƿ���Ĭ��Ϊ0��
*       Output: 
*       Return: VOS_OK                        �ɹ�
*               PPP_HA_IS_SMOOTHING           �����ֶ���������ƽ������
*               PPP_WRONGPARA_ERROR           ��������
*               PPP_IFNETCB_NOEXIST           �ӿڲ�����
*               PPP_PHYTYPE_ERR               �ӿ����ʹ���
*               PPP_CONFIGINFO_NOEXIST        ������PPP���ÿ��ƿ�
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_SetLQMNeg( ULONG ulIfIndex, ULONG ulSetYes);
/*******************************************************************************
*    Func Name: TCPIP_SetLQMPeriod
*  Description: ����LQM����ֵ
*        Input: ULONG ulIfIndex:�ӿ�����
*               USHORT usLqrPeriod:���õ�����ֵ(��Χ10��100��Ĭ��Ϊ50)
*       Output: 
*       Return: VOS_OK                  �ɹ�
*               PPP_HA_IS_SMOOTHING     �����ֶ���������ƽ������
*               PPP_WRONGPARA_ERROR     ��������
*               PPP_IFNETCB_NOEXIST     �ӿڲ�����
*               PPP_PHYTYPE_ERR         �ӿ����ʹ���
*               PPP_CONFIGINFO_NOEXIST  ������PPP���ÿ��ƿ�
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_SetLQMPeriod( ULONG ulIfIndex, USHORT usLqrPeriod);
/*******************************************************************************
*    Func Name: TCPIP_SetLQMLimit
*  Description: ����LQM�رա��ָ���ֵ
*        Input: ULONGulIfIndex:�ӿ�����
*               ULONG ulCloseValue:�رշ�ֵ(��Χ0��100��Ĭ��Ϊ80)
*               ULONG ulResumeValue:�ָ���ֵ(��Χ0��100��Ĭ��Ϊ80)
*       Output: 
*       Return: VOS_OK                   �ɹ�
*               PPP_HA_IS_SMOOTHING      �����ֶ�������ƽ������
*               PPP_WRONGPARA_ERROR      ��������
*               PPP_IFNETCB_NOEXIST      �ӿڲ�����
*               PPP_PHYTYPE_ERR          �ӿ����ʹ���
*               PPP_CONFIGINFO_NOEXIST   ������PPP���ÿ��ƿ�
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_SetLQMLimit(ULONG ulIfIndex,ULONG ulCloseValue,ULONG ulResumeValue);
/*******************************************************************************
*    Func Name: TCPIP_SetIpcpNegoDns
*  Description: ʹ��/ȥʹ����IPCP�׶��Ƿ�Э��DNSѡ��
*        Input: ULONG ulIfIndex:�ӿ�����
*               ULONG ulSetYes:ʹ�ܱ�־��1 ʹ�ܣ�0 ȥʹ��
*       Output: 
*       Return: VOS_OK                   �ɹ�
*               PPP_WRONGPARA_ERROR      ��������
*               PPP_HA_IS_SMOOTHING      HA����ƽ��������ֶ���������
*               PPP_GETCONFIGINFO_FAIL   ��ȡPPP������Ϣʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_SetIpcpNegoDns (ULONG ulIfIndex, ULONG ulSetYes);
/*******************************************************************************
*    Func Name: TCPIP_SetIPCPDNSAddr
*  Description: ����/ɾ��IPCPЭ�̵�DNS��������ַ���ṩ���Զ�
*        Input: ULONG ulIfIndex:�ӿ�����
*               ULONG ulSetYes:���ñ�־��1���ã�0 ɾ��
*               ULONG ulNum_Pri:��DNS��������ַ
*               ULONG ulNum_Sec:��DNS��������ַ
*       Output: 
*       Return: VOS_OK                      �ɹ�
*               PPP_CONFIG_IFCONFLICT       �ӿ�ʧ��
*               PPP_WRONGPARA_ERROR         ����Ĳ�������
*               PPP_HA_IS_SMOOTHING         HA����ƽ��������ֶ���������
*               PPP_DNSIPADDRESS_INVALID    ���õ�����DNS��������ַ��Ч
*               PPP_DNSIPADDRESS_PRI_IS_INVALID ���õ���DNS��������ַ��Ч
*               PPP_DNSIPADDRESS_SEC_IS_INVALID ���õĴ�DNS��������ַ��Ч
*               Other                       ��ȡPPP��Ϣ��Ĵ�����
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_SetIPCPDNSAddr(ULONG ulIfIndex, ULONG ulSetYes, ULONG ulNum_Pri, ULONG ulNum_Sec);
/*******************************************************************************
*    Func Name: TCPIP_SetPppHADbg
*  Description: ����PPPģ��HA���ܵ��Կ���״̬
*        Input: ULONG ulDbg:����PPP��HA���Կ���ֵ
*       Output: 
*       Return: VOS_OK                         �ɹ�
*               VOS_ERR                        ʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_SetPppHADbg(ULONG ulDbg);
/*******************************************************************************
*    Func Name: TCPIP_GetPppHADbg
*  Description: ��ȡPPPģ��HA���ܵ��Կ���״̬
*        Input: ULONG *pulDbg:������Ϣ�������ָ��
*       Output: ULONG *pulDbg:������Ϣ�������ָ��
*       Return: VOS_OK                     �ɹ�
*               VOS_ERR                    ʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_GetPppHADbg (ULONG *pulDbg);
/*******************************************************************************
*    Func Name: TCPIP_SetMpEDConsistent
*  Description: ����MP�ն�������һ���Լ�⿪��
*        Input: ULONG ulSetYes:����MP�ն�������һ���Լ�⿪��
*       Output: 
*       Return: VOS_OK                   �ɹ�
*               VOS_ERR                  ʧ��
*               PPP_HA_IS_SMOOTHING      ����ƽ�������ֶ���������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_SetMpEDConsistent (ULONG ulSetYes);
/*******************************************************************************
*    Func Name: TCPIP_GetMpEDConsistent
*  Description: ��ȡMP�ն�������һ���Լ�⿪��
*        Input: VOID
*       Output: 
*       Return: MP�ն�������һ���Լ�⿪��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_GetMpEDConsistent(VOID);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncNotifyIpcpDownHook
*  Description: ֪ͨIPCP down
*        Input: NotifyIpcpDown_HOOK_FUNC pfHookFunc:��������
*       Output: 
*       Return: VOS_OK                 �ɹ�
*               VOS_ERR                ʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncNotifyIpcpDownHook(NotifyIpcpDown_HOOK_FUNC pfHookFunc);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncShellAuthRequestHook
*  Description: ����֤ģ�鷢����֤����
*        Input: PPPShellAuthRequest pfHookFunc:��������
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncShellAuthRequestHook(PPPShellAuthRequest pfHookFunc);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncShellChapGetUserPswHook
*  Description: CHAP��֤ʱ�����û�����ȡ�û���pwd
*        Input: PPPShellChapGetUserPsw pfHookFunc:��������
*       Output: 
*       Return: VOS_OK                �ɹ�
*               VOS_ERR               ʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-17   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncShellChapGetUserPswHook(PPPShellChapGetUserPsw pfHookFunc);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncAllocPPPHook
*  Description: ��ȡ������Զ˵ĵ�ַ
*        Input: PPPAllocPeerIpAddr pfHookFunc:��������
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-17   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncAllocPPPHook(PPPAllocPeerIpAddr pfHookFunc);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncFreeAddrHook
*  Description: �ͷŷ�����Զ˵ĵ�ַ
*        Input: PPPFreeAddr pfHookFunc:��������
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-17   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncFreeAddrHook(PPPFreeAddr pfHookFunc);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncGetLQRStatHook
*  Description: ��ȡLQR�����ͳ����Ϣ,����ʱ��Ҫע��Adapter������ͬ���ļ�
*        Input: GetLQRStat_HOOK_FUNC pfHookFunc:��������
*       Output: 
*       Return: VOS_OK                     �ɹ�
*               VOS_ERR                    ʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-17   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncGetLQRStatHook(GetLQRStat_HOOK_FUNC pfHookFunc);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncNotifyPppDnsHook
*  Description: PPPЭ��ʱ��ȡDNS�ĵ�ַ
*        Input: NotifyPppDns_HOOK_FUNC pfHookFunc:��������
*       Output: 
*       Return: VOS_OK           �ɹ�
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-17   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncNotifyPppDnsHook(NotifyPppDns_HOOK_FUNC pfHookFunc);
/*******************************************************************************
*    Func Name: TCPIP_ADP_NotifyPppDns
*  Description: PPPЭ��ʱ��ȡDNS�ĵ�ַ
*        Input: ULONG ulIfIndex:�ӿ�����ֵ
*               ULONG ulSetYes:1��ʾɾ��, 0��ʾ����
*               ULONG ulPriDns:��DNS��������ַ(�����ֽ���)
*               ULONG ulSecDns:��DNS��������ַ(�����ֽ���)
*       Output: 
*       Return: VOS_OK:����ɹ�
*              ����  :����ʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-28   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_ADP_NotifyPppDns(ULONG ulIfIndex, ULONG ulSetYes,ULONG ulPriDns, ULONG ulSecDns);
/*******************************************************************************
*    Func Name: TCPIP_ShowPppGlobalInfo
*  Description: PPPģ���Ʒ��������ʹ�ܿ��ؼ�����ȫ����Ϣ��ʾ�ӿ�
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-17   chenfutian69112         Create
*
*******************************************************************************/
extern VOID TCPIP_ShowPppGlobalInfo (VOID);
/*******************************************************************************
*    Func Name: TCPIP_ShowPppStatistic
*  Description: PPPģ��ͳ������Ϣ��ʾ�ӿ�
*        Input: CHAR *pName:�ӿ�����
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-17   chenfutian69112         Create
*
*******************************************************************************/
extern VOID TCPIP_ShowPppStatistic(CHAR *pName);
/*******************************************************************************
*    Func Name: TCPIP_ShowPPPCfgInfo
*  Description: ��ʾPPP��չһЩ������Ϣ
*        Input: CHAR *pszIfName:�ӿ�����
*               ULONG ulProtocol:��չЭ���
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-17   chenfutian69112         Create
*
*******************************************************************************/
extern VOID TCPIP_ShowPPPCfgInfo(CHAR *pszIfName,ULONG ulProtocol);
/*******************************************************************************
*    Func Name: TCPIP_ResetIPCP
*  Description: ����IPCPЭ��
*        Input: ULONG ulIfIndex:            �ӿ�����
*       Output: 
*       Return: VOS_OK                      �ɹ�
*               PPP_HA_IS_SMOOTHING         �����ֶ�������ƽ������
*               PPP_IFNETCB_NOEXIST         �ӿ�ָ��Ϊ��
*               PPP_PPPCB_NOEXIST           PPP���ƿ鲻����
*               PPP_NOENCAP_ERROR           ��PPPЭ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-17   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_ResetIPCP (ULONG ulIfIndex);

/*******************************************************************************
*    Func Name: TCPIP_ResetIP6CP
* Date Created: 2009-03-20
*       Author: hanna55555
*  Description: ����IP6CPЭ��
*        Input: ULONG ulIfIndex:            �ӿ�����
*       Output: 
*       Return: VOS_OK                      �ɹ�
*               PPP_HA_IS_SMOOTHING         �����ֶ�������ƽ������
*               PPP_IFNETCB_NOEXIST         �ӿ�ָ��Ϊ��
*               PPP_ERR_PORT_IS_VIRTUAL   �Ǳ���ӿ� 
*               PPP_PPPCB_NOEXIST           PPP���ƿ鲻����
*               PPP_IP6CPCB_NOEXIST          IP6CP���ƿ鲻����
*               PPP_NOENCAP_ERROR           ��PPPЭ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-03-20   hanna55555         Create in VISPV1R8C01 for ppp-link support ipv6
*
*******************************************************************************/
extern ULONG TCPIP_ResetIP6CP (ULONG ulIfIndex);

/*******************************************************************************
*    Func Name: TCPIP_ResetOSICP
*  Description: ����OSICPЭ��
*        Input: ULONG ulIfIndex:            �ӿ�����
*       Output: 
*       Return: VOS_OK                      �ɹ�
*               PPP_HA_IS_SMOOTHING         �����ֶ�������ƽ������
*               PPP_IFNETCB_NOEXIST         �ӿ�ָ��Ϊ��
*               PPP_PPPCB_NOEXIST           PPP���ƿ鲻����
*               PPP_NOENCAP_ERROR           ��PPPЭ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-17   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_ResetOSICP (ULONG ulIfIndex);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncGetPPPNegoIP
*  Description: ע��PPPЭ��Э���ϱ����Ӵ�����
*        Input: GET_PPP_NEGO_IP_HOOK_FUN pfGetPPPNegoIP
*               
*       Output: 
*       Return: VOS_ERR
                VOS_OK
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-12   wangbin(62223)           Create
*
*******************************************************************************/
    
extern ULONG TCPIP_RegFuncGetPPPNegoIP (GET_PPP_NEGO_IP_HOOK_FUN pfGetPPPNegoIP);
/*******************************************************************************
*    Func Name: TCPIP_SetPPPNegoIP
*  Description: �����·�PPPЭ�̻�ȡ��Ϣ�ӿ�
*        Input: ULONG ulIfIndex:    �ӿ�����
                ULONG ulLocalIP:    ���ص�ַ(������)
*               ULONG aulDNSIP[]:   DNS��ַ(������)
                ULONG ulRemoteIP:   �Զ˵�ַ(������)
                ULONG ulMTU:        MTU
                ULONG ulFlag:       ���ɾ����־:0���,1ɾ��
*       Output: 
*       Return: PPP_HA_IS_SMOOTHING:ϵͳ����ƽ�����ֶ������׶�
                PPP_NOT_3D_MODE:    ����άģʽ
                PPP_COM_NULL:       ���Ϊ��
                PPP_WRONGPARA_ERROR:��������
                VRP_IFNET_ENOSUCHIF:�ӿ�ָ��Ϊ��
                VOS_OK:             ����ɹ�
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-12   wangbin(62223)           Create
*
*******************************************************************************/

extern ULONG TCPIP_SetPPPNegoIP(ULONG ulIfIndex,ULONG ulLocalIP, ULONG aulDNSIP[DHCP4C_DNSIP_NUM],
                                ULONG ulRemoteIP,ULONG ulMTU, ULONG ulFlag);
/*******************************************************************************
*    Func Name: TCPIP_SetIPHCUniDirection
*  Description: ʹ��/ȥʹ�ܽӿڵ�IPHC��ͨ������
*        Input: ULONG ulIfIndex:�ӿ�����
*               ULONG ulEnable:ʹ�ܱ��,0ȥʹ��,����ʹ��
*       Output: ��
*       Return: VOS_OK�ɹ�,��������ʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-15   wuhailan                Create
*
*******************************************************************************/
extern ULONG TCPIP_SetIPHCUniDirection(ULONG ulIfIndex, ULONG ulEnable);

/*******************************************************************************
*    Func Name: TCPIP_ReceiveAuthResult
*  Description: �û��ڽ�����֤У�Ժ�ͨ���˽ӿ�������֤������ظ�VISP
*        Input: PPPAUTHRESULT_S *pstAuthResult:���ص���֤���
*       Output: ��
*       Return: �ɹ�VOS_OK,��������ʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-07-01   wuhailan                Create
*
*******************************************************************************/
extern ULONG TCPIP_ReceiveAuthResult(PPPAUTHRESULT_S *pstAuthResult);
/*******************************************************************************
*    Func Name: TCPIP_SetPPPVerifySwitch
*  Description: ʹ��/ȥʹ��PPP/MP���ݺ˲鹦��(�˲�VISP�·�NP�������Ϣ)
*        Input: ULONG ulSwitch:����(1:ʹ�ܣ�0:ȥʹ��)
*               ULONG ulPeriod:�˲����ڣ�ȡֵ��Χ: [1��0xffffffff������λs��
*               ULONG ulIfNum: ÿ�κ˲�Ľӿ�����ȡֵ��Χ��[1��128]��
*       Output: 
*       Return: VOS_OK��ʹ��/ȥʹ�ܳɹ�
*               VOS_ERR��ʹ��/ȥʹ��ʧ��
*               PPP_WRONGPARA_ERROR:�������Ϸ�
*               PPP_HA_IS_SMOOTHING:HA����ƽ��������ֶ���������
*               PPP_FUNCHOOK_NULL:��������Ϊ��
*               PPP_COM_NULL:������Ϊ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-08-20   fuxiaodong(54882)       Create
*
*******************************************************************************/
extern ULONG TCPIP_SetPPPVerifySwitch(ULONG ulSwitch, ULONG ulPeriod, ULONG ulIfNum);
/*******************************************************************************
*    Func Name: TCPIP_GetPPPVerifySwitch
*  Description: ��ȡPPP NP�·���Ϣ�˲鿪��״̬
*        Input: 
*       Output: PPPVERIFYSWITCH_S *pstPppVerifySwitch:���ؿ���״̬
*       Return: VOS_OK����ȡ�ɹ�
*               ��������ȡʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-08-20   fuxiaodong(54882)       Create
*
*******************************************************************************/
extern ULONG TCPIP_GetPPPVerifySwitch(PPPVERIFYSWITCH_S *pstPppVerifySwitch);
/*******************************************************************************
*    Func Name: TCPIP_ClearIfIPHCStat
*  Description: ���ָ���ӿڵ�IPHC������ͳ����Ϣ
*        Input: ULONG ulIfIndex: �ӿ�����
*       Output: 
*       Return��VOS_OK          �ɹ�
*               ����            ʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-9-19  zhangchunyu(62474)   Create
*
*******************************************************************************/
extern ULONG TCPIP_ClearIfIPHCStat(ULONG ulIfIndex);


extern ULONG TCPIP_GetIfIPHCStatistics(ULONG ulIfIndex,TCPIP_IPHC_STATISTICS_S *pstIPHCStatistics);

/*******************************************************************************
*    Func Name: TCPIP_PPP_Set_NegTimeoutWaring
* Date Created: 2009-02-26
*       Author: zengshaoyang62531/hexianjun00121208
*  Description: ����/ȡ���״�Э�̲�������澯����
*        Input: ULONG ulTime:Ϊ0ʱ��ʾȡ��Э�̲�������澯����
*                            ��0��ʾ����Э�̲�������澯���ܣ�
*                            ulTime��ֵ��ʾ�û�ָ����Э��ʱ��
*       Output: 
*       Return: �ɹ�:VOS_OK;ʧ��:���ش�����
*      Caution: ulTime����Ϊ5�ı���,���򷵻ش���,���Ϊ600s
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                                     DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-26   zengshaoyang62531/hexianjun00121208       Create
*
*******************************************************************************/
extern ULONG TCPIP_PPP_Set_NegTimeoutWaring(ULONG ulTime);
/*******************************************************************************
*    Func Name: TCPIP_PPP_Get_NegTime
* Date Created: 2009-02-26
*       Author: zengshaoyang62531/hexianjun00121208
*  Description: ��ȡ�û����õ��״�Э�̲�������澯ʱ��
*        Input: ULONG ulTime: �״�Э�̲�������澯ʱ��
*       Output: 
*       Return: �ɹ�:VOS_OK;ʧ��:���ش�����
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-26   zengshaoyang62531/hexianjun00121208       Create
*
*******************************************************************************/
extern ULONG TCPIP_PPP_Get_NegTime(ULONG *pulTime);


extern ULONG TCPIP_SetNegoMagicNum(ULONG ulIfIndex, ULONG ulSetYes);


extern ULONG TCPIP_GetNegoMagicNum(ULONG ulIfIndex, ULONG *pulSetYes);


extern ULONG TCPIP_SetPppSelfLoop(ULONG ulIfIndex, ULONG ulSetYes);


extern ULONG TCPIP_GetPppSelfLoop(ULONG ulIfIndex, ULONG *pulSetYes);


extern ULONG TCPIP_SetNcpResendTime(ULONG ulIfIndex, ULONG ulTime);


extern ULONG TCPIP_GetNcpResendTime(ULONG ulIfIndex, ULONG *pulTime);


extern VOID TCPIP_ShowConfigInfo(CHAR *szName);


extern VOID TCPIP_ShowUsedConfigInfo(CHAR *szName);

/*******************************************************************************
*    Func Name: TCPIP_GetLcpEchoInfo
* Date Created: 2008-11-9
*       Author: zhangchunyu(62474)
*  Description: NP�߼���ȡVISP�ڲ�PPP Lcp Echo�����Ϣ
*        Input: ULONG ulIfIndex: �ӿ�����
*               ULONG ulCmd: ������
*               VOID  *pData: ����������Ӧ�����ݽṹ,�������
*       Output: pData
*       Return: VOS_OK �ɹ�  ���� ʧ��
*      Caution: ֻ�еײ��봦��Echo���ĵ�ʱ��,�ſ��Ե��û�ȡPPP Lcp������Ϣ��
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-11-9    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_GetLcpEchoInfo(ULONG ulIfIndex, ULONG ulCmd, VOID  *pData);



extern ULONG TCPIP_SetDealAcfcPfcFlag(ULONG ulIfIndex, ULONG ulFlag);


extern ULONG TCPIP_GetDealAcfcPfcFlag(ULONG ulIfIndex, ULONG *pulFlag);


/*******************************************************************************
*    Func Name: TCPIP_GR_PPPRestore
* Date Created: 2008-8-16
*       Author: zhangchunyu(62474)
*  Description: PPP����ָ��ӿ�, �û��ӿ�
*        Input: VOID
*       Output: 
*       Return: GR_SUCCESS: �ɹ�, ����: ʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-8-16    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_GR_PPPRestore(VOID);

/*******************************************************************************
*    Func Name: TCPIP_GR_PPPSmooth
* Date Created: 2008-8-16
*       Author: zhangchunyu(62474)
*  Description: PPPģ�鱣��ƽ������, �û��ӿ�
*        Input: VOID
*       Output: 
*       Return: GR_SUCCESS: �ɹ�, ����: ʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-8-16    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_GR_PPPSmooth(VOID);


extern ULONG TCPIP_SetMaxLoopbackDetectTime(ULONG ulTime);


extern ULONG TCPIP_GetMaxLoopbackDetectTime(ULONG *pulTime);


extern VOID TCPIP_ShowPPPNegoInfoByIf(CHAR *szName);


extern ULONG TCPIP_GetPPPFSMState(ULONG ulIfIndex, ULONG *pulPppPhase,ULONG *pulPppNegoType, ULONG *pulPppFsmState );


extern ULONG TCPIP_GetPapUserName(ULONG ulIfIndex, UCHAR *pucUserName);


extern ULONG TCPIP_GetChapUserName(ULONG ulIfIndex, UCHAR *pucUserName);


extern ULONG TCPIP_GetPppDownInfo(ULONG ulIfIndex, ULONG ulProtocolType, PPPDOWNINFO_S *pstPppDownInfo);


/*******************************************************************************
* Func Name: TCPIP_SyncPPPKeepaliveProbe 
* Date Created: 25-04-2013
*       Author: s72256	
*  Description: Function to sync PPP keep aliave probe while switchig from one board to another.
*        Input: ULONG ulIfIndex:   Interface Index
*               ULONG ulProbeSup:          Flag to indicate that NP supports ppp keep alive.
*       Output: 
*       Return: VOS_OK in case of success
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  25-04-2013   s72256               Create
*
*******************************************************************************/
extern ULONG TCPIP_SyncPPPKeepaliveProbe (ULONG ulIfIndex, ULONG ulProbeSup);


#ifdef __cplusplus
}
#endif


#endif

