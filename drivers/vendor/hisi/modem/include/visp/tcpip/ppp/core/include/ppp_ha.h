

#ifndef _PPP_HA_H_
#define _PPP_HA_H_

#ifdef  __cplusplus
extern "C"{
#endif

#define  PPP_BAK_PRFIX_GOTOPT       0X00000001
#define  PPP_BAK_PRFIX_HISOPT       0X00000002
#define  PPP_BAK_PRFIX_WANTOPT      0X00000004
#define  PPP_BAK_PRFIX_ALLOWOPT     0X00000008

#define  PPP_BAK_PRFIX_CONFIG       0X00000001
#define  PPP_BAK_PRFIX_USEDCONFIG   0X00000002

#define  PPP_BAK_NO_SMOOTH                      0X00000001

/* PPP ���ƿ鱸����Ϣ�ṹ */
typedef struct tagPppInfoBak
{
    ULONG   bIsAsync:1,         /* �Ƿ����첽��, ��LCP���ж��Ƿ�Э��ACCMAP */
            bSynAsyConvert:1,   /* �����첽�ڣ�����ȷ���Ƿ���PPP����ͬ/�첽����ת�� */
            bLoopBacked:1,      /* �ӿ��Ƿ������Ի� */ 
            bLowerIsUp:1,       /* �ײ��Ƿ�UP */ 
            bMpChannelType:2 ,  /* MPͨ������ */
            bPppInterleave:1,   /* �Ƿ�����LFI */
            bRunningPoeClient:1, /* ������PPP Info�ṹ�Ƿ�����PPPoE Client*/ 
            bLqmStatus:1,
            bReserved: 23  ;     /* */
    ULONG   ulRemoteAccm ;       /* �Զ�ACCM������*/
    ULONG   ulMpgroupIfIndex ;   /* �������ͨ���汣�游ͨ��������*/
    ULONG   ulLocalAccm ;        /* ����ACCM������*/
    ULONG   ulRouteIfIndex ;     /* ·�ɿɼ��ӿڵ�IFNET����*/
    ULONG   ulPhase ;            /* PPP��ǰ����Э�̽׶�*/
    USHORT  usMtu;               /* MTUֵ*/
    UCHAR   ucAuthServer ;       /* ������Ϊ��֤��**/
    UCHAR   ucAuthClient ;       /* ������Ϊ����֤��*/
} PPPINFO_BAK_S ;


typedef struct tagMCPrefixEBak
{ 
    UCHAR aucPrefixE[MC_PREFIXE_MAX_STR];   /* ����ǰ׺ʡ���ֶΣ���󳤶�Ϊ8�ֽ�*/
    UCHAR ucIsUsedFlag;                     /* �Ƿ����øõȼ�ǰ׺ʡ�Ա�־ */
    UCHAR ucClass;                          /* ����Class�ȼ� */
    UCHAR ucPrefixELen;                     /* ǰ׺�ֶγ��� */      
    UCHAR ucReserve;                        /* ���� */
} MC_PREFIXE_BAK_S;

/* ����������,�����޸����κγ�Ա */
typedef struct tagPppConfigInfoForBak 
{
    ULONG bCallbackReq    : 1,
          bCallbackAcc    : 1,
          bCallInAuth     : 1,
          bAuthRmtChap    : 1,
          bAuthRmtPap     : 1,
          bEnableVJComp   : 1,
          bEnablePComp    : 1,
          bEnableACComp   : 1,
          bSetAsMp        : 1,
          bPapPwdEncrypt  : 1,
          bChapPwdEncrypt : 1,
          bAuthRmtList    : 1,

          bAcceptPeerDNS0      :1,
          bRejectPeerDNS0      :1,
          bAcceptPeerDNS1      :1,
          bRejectPeerDNS1      :1,
  
          bEnableIPHComp  : 1,
          bNegoSubOptions : 1,  /* �Ƿ�Э��RFC3544�涨����ѡ��*/ 
          bStacCompress   : 1,   
          
          bPppInterleave  : 1,  /* �Ƿ�ʹ��MP�ķ�Ƭ���湦�� */

          bPppReorderWindow  : 1, 
          bMpDiscriminator:1,   /* discriminator negotiation */
          bNegoLCPEnable:  1,   
          bNegoNCPEnable:  1,
          bMc         :1,
          bMcPrefixE  :1,
          bSsnhf      :1,
          bPPPMux     :1,  /* �Ƿ�Э��PPP MUX */
          bNegoDNSEnable   :1, /* ����POECЭ��DNS */
          bLqmNegEnable    :1, /* �Ƿ�Э��LQM */
          bNegoOSICPEnable :1, /* �Ƿ�Э��OSI */
          bReserved   :1;  /* ����,�Ժ�ʹ�� */
    ULONG ulNegTimeOut;

    USHORT usMaxMpBindNum;/*������·��*/
    USHORT usMinFragLen; /*MP��ʼ�ֶε���С����*/
    ULONG  ulBindType;
    ULONG  ulBindVTNum;
    ULONG  ulEndpointDiscriminator; /*MP�ն�������ֵ*/
    
    USHORT usMaxDelayLFI; 
    USHORT usLqmPeriod;   /* LQM ��������ֵ */
    USHORT usUpSublinkLowLimit; /* mp�ӿڳ�Ա�˿�UP���ﵽ��ֵʱ�Ž��������Э�� */
    UCHAR  ucPadding[2];
    
    ULONG  ulClosePercentage;   /* �趨�Ĺر���·������ */
    ULONG  ulResumePercentage;  /* �趨������������·������ */
    ULONG  ulPrimDNSIPAddr;     /* �趨��Primary DNS Server��ַ */
    ULONG  ulSndDNSIPAddr;      /* �趨��Secondary DNS Server��ַ */

    UCHAR cChapHostName[PPP_MAXUSERNAMELEN + 1];
    UCHAR cChapPassword[PPP_MAXUSERPWDLEN + 1];
    UCHAR cPapUserName[PPP_MAXUSERNAMELEN + 1];
    UCHAR cPapPwd[PPP_MAXUSERPWDLEN + 1];


    USHORT  iphc_tcp_space;
    USHORT  iphc_non_tcp_space;
    USHORT usFMaxPeriod;    /* �������ͷ�TCPѹ������������ */
    USHORT usFMaxTime;      /* ���������ײ����������ʱ�� */
    USHORT usMaxHeader;     /* ��ѹ���ײ���󳤶� */
    UCHAR  ucRtpCompression;/* Э��(Enhanced) RTP Compression��ѡ������ */
    UCHAR  ucCompressType;  /* ����ѹ������ */
    LONG   lCCOMPANY_FORMAT;
    LONG   lDELETE_UDP_CHKSUM;

    USHORT usDefaultPid;     /* Default PID */
    USHORT usSubFrameLen;    /* �����֡���� */
    USHORT usFrameLen;       /* ��󸴺�֡���� */
    USHORT usSubFrameCount;  /* �����֡�� */
    USHORT usMuxDelay;       /* ����ĸ���ʱ�� */
    
    UCHAR  ucMhfCode;        /* MHFѡ���codeֵ 2:������ͷ��ʽ��6:������ͷ��ʽ */ 
    UCHAR  ucMhfClass;       /* MHFѡ���classֵ:��Ӧͷ��ʽ��֧�ֵĵȼ��� */
    ULONG  ulMcPrefixESum;   /* ���ڵ�ǰ׺ʡ��ӳ�����Ŀ */
}PPPCONFIGINFO_FOR_BAK_S;
/* ����������,�����޸����κγ�Ա */

typedef struct tagPppConfigInfoForBakOld
{
    ULONG bCallbackReq    : 1,
          bCallbackAcc    : 1,
          bCallInAuth     : 1,
          bAuthRmtChap    : 1,
          bAuthRmtPap     : 1,
          bEnableVJComp   : 1,
          bEnablePComp    : 1,
          bEnableACComp   : 1,
          bSetAsMp        : 1,
          bPapPwdEncrypt  : 1,
          bChapPwdEncrypt : 1,
          bAuthRmtList    : 1,

          bAcceptPeerDNS0      :1,
          bRejectPeerDNS0      :1,
          bAcceptPeerDNS1      :1,
          bRejectPeerDNS1      :1,
  
          bEnableIPHComp  : 1,
          bNegoSubOptions : 1,  /* �Ƿ�Э��RFC3544�涨����ѡ��*/ 
          bStacCompress   : 1,   
          
          bPppInterleave  : 1,  /* �Ƿ�ʹ��MP�ķ�Ƭ���湦�� */

          bPppReorderWindow  : 1, 
          bMpDiscriminator:1,   /* discriminator negotiation */
          bNegoLCPEnable:  1,   
          bNegoNCPEnable:  1,
          bMc         :1,
          bMcPrefixE  :1,
          bSsnhf      :1,
          bPPPMux     :1,  /* �Ƿ�Э��PPP MUX */
          bNegoDNSEnable   :1, /* ����POECЭ��DNS */
          bLqmNegEnable    :1, /* �Ƿ�Э��LQM */
          bNegoOSICPEnable :1, /* �Ƿ�Э��OSI */
          bReserved   :1;  /* ����,�Ժ�ʹ�� */
    ULONG ulNegTimeOut;

    USHORT usMaxMpBindNum;/*������·��*/
    USHORT usMinFragLen; /*MP��ʼ�ֶε���С����*/
    ULONG  ulBindType;
    ULONG  ulBindVTNum;
    ULONG  ulEndpointDiscriminator; /*MP�ն�������ֵ*/
    
    USHORT usMaxDelayLFI; 
    USHORT usLqmPeriod;   /* LQM ��������ֵ */
    USHORT usUpSublinkLowLimit; /* mp�ӿڳ�Ա�˿�UP���ﵽ��ֵʱ�Ž��������Э�� */
    UCHAR  ucPadding[2];
    
    ULONG  ulClosePercentage;   /* �趨�Ĺر���·������ */
    ULONG  ulResumePercentage;  /* �趨������������·������ */
    ULONG  ulPrimDNSIPAddr;     /* �趨��Primary DNS Server��ַ */
    ULONG  ulSndDNSIPAddr;      /* �趨��Secondary DNS Server��ַ */

    UCHAR cChapHostName[PPP_MAXUSERNAMELEN + 1];
    UCHAR cChapPassword[PPP_MAXUSERPWDLENOLD+ 1];
    UCHAR cPapUserName[PPP_MAXUSERNAMELEN + 1];
    UCHAR cPapPwd[PPP_MAXUSERPWDLENOLD + 1];


    USHORT  iphc_tcp_space;
    USHORT  iphc_non_tcp_space;
    USHORT usFMaxPeriod;    /* �������ͷ�TCPѹ������������ */
    USHORT usFMaxTime;      /* ���������ײ����������ʱ�� */
    USHORT usMaxHeader;     /* ��ѹ���ײ���󳤶� */
    UCHAR  ucRtpCompression;/* Э��(Enhanced) RTP Compression��ѡ������ */
    UCHAR  ucCompressType;  /* ����ѹ������ */
    LONG   lCCOMPANY_FORMAT;
    LONG   lDELETE_UDP_CHKSUM;

    USHORT usDefaultPid;     /* Default PID */
    USHORT usSubFrameLen;    /* �����֡���� */
    USHORT usFrameLen;       /* ��󸴺�֡���� */
    USHORT usSubFrameCount;  /* �����֡�� */
    USHORT usMuxDelay;       /* ����ĸ���ʱ�� */
    
    UCHAR  ucMhfCode;        /* MHFѡ���codeֵ 2:������ͷ��ʽ��6:������ͷ��ʽ */ 
    UCHAR  ucMhfClass;       /* MHFѡ���classֵ:��Ӧͷ��ʽ��֧�ֵĵȼ��� */
    ULONG  ulMcPrefixESum;   /* ���ڵ�ǰ׺ʡ��ӳ�����Ŀ */
}PPPCONFIGINFO_FOR_BAK_OLD_S;

typedef struct tagPppLcpOptionBak
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
         neg_mrru : 1,
         neg_ssnhf : 1,
         neg_discr : 1,
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
    /*�ú��������������ĳ���*/
    UCHAR   discr_addr[PPP_MP_DISCR_MAX_LENGTH];
    UCHAR   callbackinfo[PPP_MAX_CALLBACK_INFO_LEN];
    UCHAR   callbacklen;

    UCHAR ucPrefixELen;       /* Req������ǰ׺ʡ��ѡ��ĳ��� */
    UCHAR ucMhfCode;          /* MHFѡ����codeֵ */
    UCHAR ucMhfClass;         /* MHFѡ����classֵ */
    UCHAR ucReserve; 
} PPP_LCP_OPTION_BAK_S;

typedef struct tagPppIpcpOptionBak
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

} PPP_IPCP_OPTION_BAK_S;

typedef struct tagPppMuxcpOptionBak
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
} PPP_MUXCP_OPTION_BAK_S; 

/* Begin of HA UPGRADE modification, 2010 December to 2011 January */
/* ��������ṹ����Ϊ�˽��VR6C02��VR6C05�汾�ϣ�PPP_MUXCP_OPTION_BAK_S���ڴ���ֽ����ʹ�ò���ȷ������ */
typedef struct tagPppMuxcpPid_LD
{
    /* �Ƿ�Э�� */
    ULONG bReserve       : 31,   /* Ϊ���Ժ���չԤ��Э��λ */
          neg_defaultpid : 1;    /* Negotiate Default Pid */
}PPP_MUXCP_PID_LD_S;

/* End of HA UPGRADE modification, 2010 December to 2011 January */

typedef struct tagPppOsicpOptionBak
{
    /* �Ƿ�Э�� */
    UCHAR neg_Align_NPDU ;
    /* Э�̲���ֵ */
    UCHAR ucAlign_NPDU;
	
	UCHAR ucRes[2];
} PPP_OSICP_OPTION_BAK_S; 

#define PPP_COPY_IPCP_OPTION(to, from) \
{ \
    (to).neg_addr = (from).neg_addr; \
    (to).old_addrs = (from).old_addrs; \
    (to).req_addr = (from).req_addr; \
    (to).neg_vj = (from).neg_vj; \
    (to).neg_dnsaddr0 = (from).neg_dnsaddr0; \
    (to).req_dnsaddr0 = (from).req_dnsaddr0; \
    (to).neg_nbnsaddr0 = (from).neg_nbnsaddr0; \
    (to).req_nbnsaddr0 = (from).req_nbnsaddr0; \
    (to).neg_dnsaddr1 = (from).neg_dnsaddr1; \
    (to).req_dnsaddr1 = (from).req_dnsaddr1; \
    (to).neg_nbnsaddr1 = (from).neg_nbnsaddr1; \
    (to).req_nbnsaddr1 = (from).req_nbnsaddr1; \
    (to).accept_dnsaddr0 = (from).accept_dnsaddr0; \
    (to).accept_dnsaddr1 = (from).accept_dnsaddr1; \
    (to).accept_nbnsaddr0 = (from).accept_nbnsaddr0; \
    (to).neg_iphc = (from).neg_iphc; \
    (to).accept_nbnsaddr1 = (from).accept_nbnsaddr1; \
    (to).breserved = (from).breserved; \
    (to).vj_protocol = (from).vj_protocol; \
    (to).maxslotindex = (from).maxslotindex; \
    (to).cflag = (from).cflag; \
    (to).ouraddr = (from).ouraddr; \
    (to).hisaddr = (from).hisaddr; \
    (to).dnsaddr0 = (from).dnsaddr0; \
    (to).nbnsaddr0 = (from).nbnsaddr0; \
    (to).dnsaddr1 = (from).dnsaddr1; \
    (to).nbnsaddr1 = (from).nbnsaddr1; \
    (to).iphc_protocol = (from).iphc_protocol; \
    (to).us_tcp_space = (from).us_tcp_space; \
    (to).us_non_tcp_space = (from).us_non_tcp_space; \
    (to).us_f_max_period = (from).us_f_max_period; \
    (to).us_f_max_time = (from).us_f_max_time; \
    (to).us_max_header = (from).us_max_header; \
    (to).ucRtpCompression = (from).ucRtpCompression; \
    (to).ucCompressType = (from).ucCompressType; \
}

#define PPP_COPY_PPPMUX_OPTION(to, from) \
{ \
    (to).neg_defaultpid = (from).neg_defaultpid; \
    (to).bReserve = (from).bReserve; \
    (to).usDefaultPid = (from).usDefaultPid; \
    (to).usReserved = (from).usReserved; \
}

#define PPP_COPY_OSICP_OPTION(to, from) \
{ \
    (to).neg_Align_NPDU = (from).neg_Align_NPDU; \
    (to).ucAlign_NPDU = (from).ucAlign_NPDU; \
}


#define PPP_COPY_LCPOPTION_EXCEPT_PREFIX(to, from) \
{ \
    (to)->neg_mru = (from)->neg_mru; \
    (to)->neg_asyncmap = (from)->neg_asyncmap; \
    (to)->neg_upap = (from)->neg_upap; \
    (to)->neg_chap = (from)->neg_chap; \
    (to)->neg_magicnumber = (from)->neg_magicnumber; \
    (to)->neg_pcompression = (from)->neg_pcompression; \
    (to)->neg_accompression =  (from)->neg_accompression; \
    (to)->neg_lqr = (from)->neg_lqr; \
    (to)->neg_mrru = (from)->neg_mrru; \
    (to)->neg_ssnhf = (from)->neg_ssnhf; \
    (to)->neg_discr = (from)->neg_discr; \
    (to)->neg_callback = (from)->neg_callback; \
    (to)->neg_mhf = (from)->neg_mhf; \
    (to)->neg_prefixE = (from)->neg_prefixE; \
    (to)->bReserve = (from)->bReserve; \
    (to)->mru = (from)->mru; \
    (to)->mrru = (from)->mrru; \
    (to)->asyncmap = (from)->asyncmap; \
    (to)->magicnumber = (from)->magicnumber; \
    (to)->numloops = (from)->numloops; \
    (to)->chap_mdtype = (from)->chap_mdtype; \
    (VOID)TCPIP_Mem_Copy((to)->ucPadding, sizeof((to)->ucPadding), (from)->ucPadding, 3); \
    (to)->lqr_period = (from)->lqr_period; \
    (to)->discr_len = (from)->discr_len;  \
    (to)->discr_class = (from)->discr_class; \
    (to)->callbackopr = (from)->callbackopr; \
    (VOID)TCPIP_Mem_Copy((to)->discr_addr, sizeof((to)->discr_addr), (from)->discr_addr, PPP_MP_DISCR_MAX_LENGTH); \
    (VOID)TCPIP_Mem_Copy((to)->callbackinfo, sizeof((to)->callbackinfo), (from)->callbackinfo, PPP_MAX_CALLBACK_INFO_LEN); \
    (to)->callbacklen = (from)->callbacklen; \
    (to)->ucPrefixELen = (from)->ucPrefixELen; \
    (to)->ucMhfCode = (from)->ucMhfCode; \
    (to)->ucMhfClass = (from)->ucMhfClass; \
    (to)->ucReserve = (from)->ucReserve; \
}

#define PPP_COPY_PREFIX(to, from) \
{ \
    ULONG ulCopyTime; \
    for ( ulCopyTime = 0; ulCopyTime < MC_PREFIXE_MAX_NUM; ulCopyTime++ ) \
    { \
        (VOID)TCPIP_Mem_Copy(to[ulCopyTime].aucPrefixE, sizeof(to[ulCopyTime].aucPrefixE), from[ulCopyTime].aucPrefixE, MC_PREFIXE_MAX_STR); \
        to[ulCopyTime].ucIsUsedFlag = from[ulCopyTime].ucIsUsedFlag; \
        to[ulCopyTime].ucClass = from[ulCopyTime].ucClass; \
        to[ulCopyTime].ucPrefixELen = from[ulCopyTime].ucPrefixELen; \
        to[ulCopyTime].ucReserve = from[ulCopyTime].ucReserve; \
    } \
}
 

/*Ϊ�˴���򵥣����¶���һ���ṹ*/
typedef struct tagPppConfigInfoBak
{
    PPPCONFIGINFO_FOR_BAK_S stPppConfigInfo;
    MC_PREFIXE_BAK_S stPrefixE[MC_PREFIXE_MAX_NUM];/* ǰ׺ʡ��ӳ��� */    
}PPPCONFIGINFO_BAK_S;

typedef struct tagPppConfigInfoBakOld
{
    PPPCONFIGINFO_FOR_BAK_OLD_S stPppConfigInfo;
    MC_PREFIXE_BAK_S stPrefixE[MC_PREFIXE_MAX_NUM];/* ǰ׺ʡ��ӳ��� */    
}PPPCONFIGINFO_BAK_OLD_S;

/*Ϊ�˴���򵥣����¶���һ���ṹ*/
typedef struct tagPppLcpBAkOption
{
    PPP_LCP_OPTION_BAK_S stPppLcpOption;
    MC_PREFIXE_BAK_S stPrefixE[MC_PREFIXE_MAX_NUM]; /* ǰ׺ʡ��ӳ����ñ���һ��16��MC_PREFIXE_SԪ�ص����飬�洢ǰ׺ʡ�Թ��� */
} PPP_LCPBAK_OPTION_S;

/* ״̬��ģ�鱸�����ݽṹ */
typedef struct tagPppFsmBak
{
    ULONG   ulTimeOutTime;       /* config request���ĵĳ�ʱʱ�� */
    ULONG   ulEchoTimeOutTime;   /* LCP Echo request���ĵĳ�ʱʱ�� */
    USHORT  usProtocol;          /* ��Э���PPPЭ���  */
    UCHAR   ucState ;            /* Э��״̬ */
    UCHAR   ucNeedNego;          /* �Ƿ�Э����Э�� */
} PPPFSM_BAK_S ;


/* LCP���ƿ鱸�����ݽṹ */
typedef struct tagPppLcpInfoBak
{
    PPPFSM_BAK_S     stFsmBak;        /* LCPЭ��״̬����Ҫ���ݵ����� */
    ULONG            ulBakPrefix ;    /* �Ƿ񱸷�ǰ׺��,�ǰ�λ�жϵ� */
    PPP_LCPBAK_OPTION_S stGotOptions;    /* �Ѿ�Э�̵����ҵ�ѡ�� */
    PPP_LCPBAK_OPTION_S stHisOptions;    /* �Ѿ�Э�̵��ĶԷ���ѡ�� */
    PPP_LCPBAK_OPTION_S stWantOptions;   /* ��ϣ����Է�Э�̵��ҵ�ѡ�� */
    PPP_LCPBAK_OPTION_S stAllowOptions;  /* ������Է�Э�̵��ҵ�ѡ�� */
} PPPLCPINFO_BAK_S ;


/* IPCP���ƿ鱸�����ݽṹ */
typedef struct tagPppIpcpInfoBak
{
    PPPFSM_BAK_S      stFsmBak;       /* IPCPЭ��״̬��Ҫ���ݵ����� */   
    PPP_IPCP_OPTION_BAK_S stGotOptions;   /* �Ѿ�Э�̵����ҵ�ѡ�� */   
    PPP_IPCP_OPTION_BAK_S stHisOptions;   /* �Ѿ�Э�̵��ĶԷ���ѡ�� */   
    PPP_IPCP_OPTION_BAK_S stWantOptions;  /* ��ϣ����Է�Э�̵��ҵ�ѡ�� */   
    PPP_IPCP_OPTION_BAK_S stAllowOptions; /* ������Է�Э�̵��ҵ�ѡ�� */   
} PPPIPCPINFO_BAK_S ;


/* MUXCP���ƿ鱸�����ݽṹ */
typedef struct tagPppMUXCPInfoBak
{
    PPPFSM_BAK_S      stFsmBak;         /* MUXVPЭ��״̬��Ҫ���ݵ����� */  
    PPP_MUXCP_OPTION_BAK_S  stGotOptions;   /* �Ѿ�Э�̵����ҵ�ѡ�� */   
    PPP_MUXCP_OPTION_BAK_S stHisOptions;    /* �Ѿ�Э�̵��ĶԷ���ѡ�� */  
    PPP_MUXCP_OPTION_BAK_S stWantOptions;   /* ��ϣ����Է�Э�̵��ҵ�ѡ�� */
    PPP_MUXCP_OPTION_BAK_S stAllowOptions;  /* ������Է�Э�̵��ҵ�ѡ�� */
} PPPMUXCPINFO_BAK_S;

/* OSICP���ƿ鱸�����ݽṹ */
typedef struct tagPppOSICPInfoBak
{
    PPPFSM_BAK_S      stFsmBak;         /* OSICPЭ��״̬��Ҫ���ݵ����� */  
    PPP_OSICP_OPTION_BAK_S stGotOptions;    /* �Ѿ�Э�̵����ҵ�ѡ�� */   
    PPP_OSICP_OPTION_BAK_S stHisOptions;    /* �Ѿ�Э�̵��ĶԷ���ѡ�� */  
    PPP_OSICP_OPTION_BAK_S stWantOptions;   /* ��ϣ����Է�Э�̵��ҵ�ѡ�� */
    PPP_OSICP_OPTION_BAK_S stAllowOptions;  /* ������Է�Э�̵��ҵ�ѡ�� */
} PPPOSICPINFO_BAK_S;

/* OSICP���ƿ������������ݽṹ */
typedef struct tagPppOSICPBatchBak
{
    ULONG ulIfIndex;                       /* �ӿ����� */
    PPPOSICPINFO_BAK_S  stInfoBak;         /* OSICPЭ�鱸�ݵ����� */  
} PPPOSICPBATCH_BAK_S;

/* PAP���ƿ鱸�����ݽṹ */
typedef struct tagPppPapInfoBak
{
    UCHAR ucServerState;               /* Server ״̬ */ 
    UCHAR ucClientState;               /* Client ״̬ */ 
    UCHAR ucAuthServer ;               /* ������Ϊ��֤��* */ 
    UCHAR ucAuthClient ;               /* ������Ϊ����֤�� */ 
    UCHAR szPapUsrName[PPP_MAXUSERNAMELEN + 2];  /* �û���  */ 
    UCHAR szPapUsrPwd[PPP_MAXUSERPWDLEN + 2];    /* �û�pwd */ 
}PPPPAPINFO_BAK_S;

/* CHAP���ƿ鱸�����ݽṹ */
typedef struct tagPppChapInfoBak 
{
    UCHAR ucServerState;         /* Server ״̬ */ 
    UCHAR ucClientState;         /* Client ״̬ */ 
    UCHAR ucAuthServer ;         /* ������Ϊ��֤��* */
    UCHAR ucAuthClient ;         /* ������Ϊ����֤�� */
    UCHAR szHostName[PPP_MAXUSERNAMELEN + 2]; /* ������ */
    UCHAR szHostPwd[PPP_MAXUSERPWDLEN + 2];   /* pwd */
} PPPCHAPINFO_BAK_S ;

/* PAP���ƿ鱸�����ݽṹ */
typedef struct tagPppPapInfoBakOld
{
    UCHAR ucServerState;               /* Server ״̬ */ 
    UCHAR ucClientState;               /* Client ״̬ */ 
    UCHAR ucAuthServer ;               /* ������Ϊ��֤��* */ 
    UCHAR ucAuthClient ;               /* ������Ϊ����֤�� */ 
    UCHAR szPapUsrName[PPP_MAXUSERNAMELEN + 2];  /* �û���  */ 
    UCHAR szPapUsrPwd[PPP_MAXUSERPWDLENOLD + 2];    /* �û�pwd */ 
}PPPPAPINFO_BAK_OLD_S;

/* CHAP���ƿ鱸�����ݽṹ */
typedef struct tagPppChapInfoBakOld 
{
    UCHAR ucServerState;         /* Server ״̬ */ 
    UCHAR ucClientState;         /* Client ״̬ */ 
    UCHAR ucAuthServer ;         /* ������Ϊ��֤��* */
    UCHAR ucAuthClient ;         /* ������Ϊ����֤�� */
    UCHAR szHostName[PPP_MAXUSERNAMELEN + 2]; /* ������ */
    UCHAR szHostPwd[PPP_MAXUSERPWDLENOLD + 2];   /* pwd */
} PPPCHAPINFO_BAK_OLD_S ;

/* PPP�ӿ���Ϣ�������ݽṹ������������ʱ�Խӿ�Ϊ��λ�ռ�������Ϣ */
typedef struct tag_PPPINTF_BAK_S
{
    ULONG   bBakPppCb: 1,    /* �����ж��Ƿ񱸷�PPP CB ��Ϣ */
            bBakLcp: 1,      /* �����ж��Ƿ񱸷�LCP ��Ϣ*/
            bBakIpcp: 1,     /* �����ж��Ƿ񱸷�IPCP ��Ϣ*/
            bBakMuxcp: 1,    /* �����ж��Ƿ񱸷�Muxcp ��Ϣ*/
            bBakPap: 1,      /* �����ж��Ƿ񱸷�PAP ��Ϣ*/
            bBakChap: 1,     /* �����ж��Ƿ񱸷�CHAP ��Ϣ*/
            bBakConfig:1,    /* �����ж��Ƿ񱸷�config������Ϣ��Ϣ*/
            bBakConfigPrefixE:1,    /* config���Ƿ����ǰ׺��*/
            bBakUsedConfig:1,    /* �����ж��Ƿ񱸷�usedconfig������Ϣ��Ϣ*/
            bBakUsedConfigPrefixE:1,    /* usedconfig���Ƿ����ǰ׺��*/
            bReserved :22;   /* */
    
    PPPCONFIGINFO_BAK_S   stPppConfig;
    PPPCONFIGINFO_BAK_S   stPppUsedConfig;
    PPPINFO_BAK_S        stPppCBInfo; /* PPP���ƿ���Ϣ */
    PPPLCPINFO_BAK_S     stLcpInfo;   /* LCP���ƿ���Ϣ */
    PPPIPCPINFO_BAK_S    stIpcpInfo;  /* IPCP���ƿ���Ϣ */
    PPPMUXCPINFO_BAK_S   stMuxcpInfo; /* Muxcp���ƿ���Ϣ */
    PPPPAPINFO_BAK_S     stPapInfo;   /* PAP���ƿ���Ϣ */ 
    PPPCHAPINFO_BAK_S    stChapInfo;  /* CHAP���ƿ���Ϣ */
}PPPINTF_BAK_S;

typedef struct tag_PPPINTF_BAK_OLD_S
{
    ULONG   bBakPppCb: 1,    /* �����ж��Ƿ񱸷�PPP CB ��Ϣ */
            bBakLcp: 1,      /* �����ж��Ƿ񱸷�LCP ��Ϣ*/
            bBakIpcp: 1,     /* �����ж��Ƿ񱸷�IPCP ��Ϣ*/
            bBakMuxcp: 1,    /* �����ж��Ƿ񱸷�Muxcp ��Ϣ*/
            bBakPap: 1,      /* �����ж��Ƿ񱸷�PAP ��Ϣ*/
            bBakChap: 1,     /* �����ж��Ƿ񱸷�CHAP ��Ϣ*/
            bBakConfig:1,    /* �����ж��Ƿ񱸷�config������Ϣ��Ϣ*/
            bBakConfigPrefixE:1,    /* config���Ƿ����ǰ׺��*/
            bBakUsedConfig:1,    /* �����ж��Ƿ񱸷�usedconfig������Ϣ��Ϣ*/
            bBakUsedConfigPrefixE:1,    /* usedconfig���Ƿ����ǰ׺��*/
            bReserved :22;   /* */
    
    PPPCONFIGINFO_BAK_OLD_S   stPppConfig;
    PPPCONFIGINFO_BAK_OLD_S   stPppUsedConfig;
    PPPINFO_BAK_S        stPppCBInfo; /* PPP���ƿ���Ϣ */
    PPPLCPINFO_BAK_S     stLcpInfo;   /* LCP���ƿ���Ϣ */
    PPPIPCPINFO_BAK_S    stIpcpInfo;  /* IPCP���ƿ���Ϣ */
    PPPMUXCPINFO_BAK_S   stMuxcpInfo; /* Muxcp���ƿ���Ϣ */
    PPPPAPINFO_BAK_OLD_S     stPapInfo;   /* PAP���ƿ���Ϣ */ 
    PPPCHAPINFO_BAK_OLD_S    stChapInfo;  /* CHAP���ƿ���Ϣ */
}PPPINTF_BAK_OLD_S;


/*��Э�鱸�ݻ���������,����������ʱ���ӿ�����������ı��ݳ���Ϊ���ݻ���������*/
#define  PPP_MAX_PROTOCOL_INFO_LEN       sizeof(PPPINTF_BAK_S)   

/* PPP��Э�鱸�����ݽṹ */
typedef struct tag_PPP_PROTOCOL_BAK_S
{
    ULONG ulIfIndex;    /* ��Э����ƿ�����Ӧ�Ľӿ����� */
    ULONG ulProtocol;   /* ��Э���PPPЭ��� */
    CHAR szProtocolInfo[PPP_MAX_PROTOCOL_INFO_LEN] ;/* ��Э����ƿ���Ϣ�洢�� */
}PPP_PROTOCOL_BAK_S;


/* PPP���ձ������ݽṹ */
typedef struct tag_PPP_BAK_S
{
    ULONG ulProMsgType ;   /* ������Ϣ���� */
    PPP_PROTOCOL_BAK_S   stPPPBak  ;  /* ��Ҫ���ݵ���Ϣ */
}PPP_BAK_S;

/* MP����Ϣ���ݽṹ */
typedef struct tag_PPPMP_BAK_S 
{
    UCHAR ucMpGroupName[IF_MAX_INTERFACE_NAME_LEN+1];  /* �ӿ���*/
    ULONG ulIfindexArrary[MP_SUPPORT_MAX_BIND];    /* �ӿ������� */
}PPPMP_BAK_S;

/* MP����Ϣ���ݽṹ */
typedef struct tag_MPCFG_BAK_S
{
    ULONG  ulflag;        /* ��Ǳ��ݵ��������� */
    ULONG  ulSubIfIndex;  /* ��ͨ������ */
    CHAR   szMpGroupName [ IF_MAX_INTERFACE_NAME_LEN+1];   /* ���ӿ���*/
}MPCFG_BAK_S;

/* PPPģ��ȫ�ֱ������ݽṹ */
typedef struct tag_PPPGLOBALVAR_BAK_S
{
    ULONG   ulDiscrSpecial;  /* HDLC�Զ��������ܿ��ر��ݱ��� */
    ULONG   ulPPPResetTime;  /* ��ʱ����ʱʱ�䵥λΪ���� */
    ULONG   ulMpReorderWinTimes;/*MP���鴰�ڵ�����Ϣ*/
    ULONG   ulMpEDConsistent; /* MP�ն���������һ���Կ��� */
}PPPGLOBALVAR_BAK_S;

#define PPP_HA_TLLENGTH 4

typedef struct tagPPPTYPELENGTH
{
    USHORT usType;             /*type*/
    USHORT usLength;           /*length*/
}PPPTYPELENGTH_S;

/*T*/
typedef enum tagPPPBAKTYPE
{
    PPP_HA_SET_NEGTIME = 0x1000
}PPPBAKTYPE_E;

/*V*/
typedef struct tagPPP_NEGTIME_BAK
{
    ULONG  ulNegTime;
}PPP_NEGTIME_BAK_S;

/*����PPPģ��HA�ı�׼������Ϣͷ�����ݽṹ,add by wuhailan,2008-04-11.*/
/*PPPģ��HA������Ϣͷ*/
typedef struct tagPPP_HA_HEAD
{
    USHORT usPppOprType;  /* PPP������Ϣ����  */
    USHORT usPppOprLen;   /* PPP������Ϣ����  */
}PPP_HA_HEAD_S;

/*��������Ϣ����TLV�ṹ*/
typedef struct tagPPP_CFG_UNIDIRECTION_HA_TLV
{
    USHORT usMsgType;
    USHORT usMsgLen;
    UCHAR  ucEnableUniDirection;  /*�Ƿ�֧��IPHC��ͨ����*/
    UCHAR  ucPadding[3];
}PPP_CFG_UNIDIRECTION_HA_TLV_S;

/*PPPģ��������ϢHA���ݱ�׼��Ϣͷ*/
typedef struct tagPPP_NEW_CFG_BAK  
{
    /*����������*/
    ULONG ulIfIndex;    /*�ӿ�����*/
    PPP_CFG_UNIDIRECTION_HA_TLV_S stConfigUniDirection;/*��ͨ������������Ϣ����*/
}PPP_NEW_CFG_BAK_S;

/*PPPģ��������ϢHA���ݱ�׼��Ϣͷ*/
typedef struct tagPPP_NEW_GLOBARVAR_BAK  
{
    USHORT usMsgType;
    USHORT usMsgLen;
    PPPVERIFYSWITCH_S stVerifySwitch; /*�˲鿪��*/
}PPP_NEW_GLOBARVAR_VERIFYSWITCH_BAK_S;

/* ����TLV�е�TL�ֶ� */
typedef struct tagPPP_HA_TLV
{
    USHORT usSubMsgType; /* ��������Ϣ���� */
    USHORT usSubMsgLen;  /* ��������Ϣ���� */
}PPP_HA_TLV_S;

typedef struct tagPPP_CFG_NEGO_MAGICNUM_BAK
{
    ULONG ulIfIndex;         /* �ӿ����� */
    ULONG ulNegoMagicNum;    /* �Ƿ�Э��Magic Numberѡ���� */
}PPP_CFG_NEGO_MAGICNUM_BAK_S;

typedef struct tagPPP_CFG_SELFLOOP_BAK
{
    ULONG ulIfIndex;         /* �ӿ����� */
    ULONG ulSelfLoop;        /* �Ƿ�����Ϊ�Ի�ģʽ��� */
}PPP_CFG_SELFLOOP_BAK_S;

typedef struct tagPPP_CFG_DR_BAK
{
    ULONG ulIfIndex;       /*�ӿ�����*/
    ULONG ulDiscardReq;    /*�Ƿ���Discard Request���Ŀ���*/
}PPP_CFG_DR_BAK_S;

/* ����NCP��ʱ����һ��NCP CR���ĵ�TLV�ṹ */
typedef struct tagPPP_CFG_NRT_BAK
{
    ULONG ulIfIndex;        /* �ӿ����� */
    ULONG ulNcpResendTime;  /* NCP��ʱ����һ��NCP CR���ĵ�ʱ��ֵ */
}PPP_CFG_NRT_BAK_S;

/*����PPP����Ի�����*/
typedef struct tagPPP_LOOPBACKTIME_BAK  
{
    USHORT usMsgType;
    USHORT usMsgLen;
    ULONG ulPPPLoopbackTime; /*�Ի�������*/
}PPP_LOOPBACKTIME_BAK_S;

typedef struct tagPPP_HA_VIRTUAL_INFO_BAK
{
    ULONG ulIfIndex;
    ULONG ulLocalIp;
    ULONG ulRemoteIp;
    ULONG ulMtu;
    ULONG ulFlag;
    ULONG ulVlinkIndex;
}PPP_HA_VIRTUAL_INFO_BAK_S;

typedef struct tagPPP_DNSTLV_BAK
{
    USHORT usType;
    USHORT usLen;
    ULONG aulDNSIP[DHCP4C_DNSIP_NUM];  
}PPP_DNSTLV_BAK_S;

typedef struct tagPPP_CFG_DEALACFCPFC_BAK
{
    ULONG ulIfIndex;        /* �ӿ����� */
    ULONG ulDealAcfcPfc;    /* �Ƿ���ܺʹ���ACFC/PFCЭ��ѡ���� */
}PPP_CFG_DEALACFCPFC_BAK_S;

typedef struct tagPPP_ISISFLAG_BAK
{
    ULONG ulIfIndex;        /* �ӿ����� */
    ULONG ulIsIsFlag;       /* �Ƿ�ʹ��ISIS���ķ��� */
}PPP_ISISFLAG_BAK_S;


enum enumPPPBAKMsgType  /*��������*/
{
    PPP_BAK_BATCH_MPINFO = 1,   /*������MP����Ϣ*/
    PPP_BAK_BATCH_PPPINFO,     /*������PPP��Ϣ*/
    PPP_BAK_REALTIME_PPPINFO,  /*PPPʵʱ����*/
    PPP_BAK_REALTIME_CONFIGINFO, /*������Ϣ����*/
    PPP_BAK_MPCONFIG_INFO,     /*Mp������Ϣ����*/
    PPP_BAK_EVENT_OPENED,      /*PPP ��Э��OPEN������*/
    PPP_BAK_EVENT_INIT,        /*PPP ��Э��DOWN������*/
    PPP_BAK_EVENT_SHUTDOWN,    /*�ӿڱ�shutdown����PPP ��Э��DOWN������*/
    PPP_BAK_LCP_OPENED,        /*LCP Э��OPEN*/
    PPP_BAK_IPCP_OPENED,       /* IPCPЭ��OPEN*/
    PPP_BAK_MUXCP_OPENED,      /* MUXCPЭ��OPEN*/
    PPP_BAK_PAP_OPENED,        /* PAPЭ��OPEN*/
    PPP_BAK_CHAP_OPENED,       /* CHAPЭ��OPEN*/
    PPP_BAK_MPSUBLINK_OPENED,  /*MP��ͨ���󶨳ɹ�*/
    PPP_BAK_CONFIG_INFO,       /*����CONFIG������Ϣ*/
    PPP_BAK_USEDCONFIG_INFO,   /*����USEDCONFIG������Ϣ*/
    PPP_BAK_NO_PPPMULTILINK,   /*MP������Ϣ*/
    PPP_BAK_BINDTO_MPGROUP,    /*MP����Ϣ*/
    PPP_BAK_GLOBALVAR,         /*ȫ�ֱ�������*/
    
    /*VISPV1R7�����ı������������ֵ��0X80��ʼ,ǰ���ֵԤ����VISPV1R6*/
    PPP_BAK_BATCH_NEW_PPPINFO = 0X80,
    PPP_BAK_VIRTUAL,
    PPP_BAK_NEW_GLOBALVAR,
    PPP_NEWBAK_TLV_MSG,        /* ���ݵ���������Ϣ���ǰ�TLV��ʽ����� */
    PPP_BAK_OSICP_OPENED,      /* OSICPЭ��OPEN*/
};

/*�µ�PPP HAͷ��Ϣ����, ֧����������, ���Ͷ��岻���ظ�, �����޸Ľ�ֹɾ��*/
enum enumPPPNEWBAKMsgType  
{
    /*VISPV1R7�����ı���������ֵ��0X0100��ʼ,ǰ���ֵԤ����VISPV1R6*/
    PPP_NEWBAK_CONFIG_INFO = 0X0100, /*��������Ϣ����,���������·�ö������enumPPPNEWCFGBAKSubMsgType����*/
    
    PPP_VIRTUAL_CONFIG_INFO = 0X0200,/*��ά����PPP�ӿ���״̬��Ϣ��ʵʱ������Ϣ����*/    
    PPP_DNS_BAK_INFO_CODE = 0X0201,
    
    PPP_NEWBAK_GLOBAL_INFO = 0X0300,  /*��ȫ�ֱ�������*/
    PPP_NEWBAK_GLOBAL_INFO_VERIFYSWITCH = 0X0301, /*ȫ�ֱ���g_stPppVerifySwitch��������*/
    PPP_NEWBAK_GLOBAL_INFO_LOOPBACKTIME = 0x0302, /*ȫ�ֱ���g_ulPPPLoopBackTime��������*/
};

enum enumPPPNEWCFGBAKSubMsgType  /*PPP_NEWBAK_CONFIG_INFO��Ϣ�����µ�����Ϣ����,ռ�����ֽ�*/
{
    PPP_NEWBAK_CONFIG_INFO_CODE = 0X0100,   /*VISPV1R7�����ı���������ֵ��0X0100��ʼ,ǰ���ֵԤ����VISPV1R6*/
};

enum PPP_NEWBAK_TLV_MSG_TYPE  /*PPP_NEWBAK_TLV_MSG��Ϣ�����µ�����Ϣ����,ռ�����ֽ�*/
{
    PPP_NEWBAK_TLV_DISCARDREQ_CFG = 1, /* �������õ�Discard Request���ص�����Ϣ���ͣ�V1R7C01������  */
    /*Mod End*/
    PPP_NEWBAK_TLV_DISCARDREQ_USE,      /* ������Ч��Discard Request���ص�����Ϣ���ͣ�V1R7C01������ */
    PPP_NEWBAK_TLV_DEAL_ACFCPFC_CFG,    /* �������õ�"�Ƿ���ܺʹ���ACFC/PFCЭ��ѡ��ı��"����Ϣ���ͣ�VR6C05���� */
    PPP_NEWBAK_TLV_DEAL_ACFCPFC_USE,    /* ������Ч��"�Ƿ���ܺʹ���ACFC/PFCЭ��ѡ��ı��"����Ϣ���ͣ�VR6C05���� */
    PPP_NEWBAK_TLV_IPHCUNIDIRT_USE,
    PPP_NEWBAK_TLV_NEGO_MAGICNUM_USE,   /* ������Ч��"�Ƿ�Э��Magic Numberѡ��ı��"����Ϣ���ͣ�VR6C02���� */
    PPP_NEWBAK_TLV_NEGO_MAGICNUM_CFG,   /* �������õ�"�Ƿ�Э��Magic Numberѡ��ı��"����Ϣ���ͣ�VR6C02���� */
    PPP_NEWBAK_TLV_SELFLOOP_USE,        /* ������Ч��"�Ƿ������Ի�ģʽ���"����Ϣ���ͣ�VR6C02���� */
    PPP_NEWBAK_TLV_SELFLOOP_CFG,        /* �������õ�"�Ƿ������Ի�ģʽ���"����Ϣ���ͣ�VR6C02���� */
    PPP_NEWBAK_TLV_NCPRESENDTIME_USE,   /* ������Ч��"��ʱ����һ��NCP CR���ĵ�ʱ��"����Ϣ���� */
    PPP_NEWBAK_TLV_NCPRESENDTIME_CFG,   /* �������õ�"��ʱ����һ��NCP CR���ĵ�ʱ��"����Ϣ���� */
    PPP_NEWBAK_TLV_OSICP_INFO,          /* ����OSICPЭ����Ϣ */
    PPP_NEWBAK_TLV_ISISFLAG_INFO,       /* ����ISIS�����Ϣ */
};

#define PPP_TLV_HEAD_LENGTH     4  /*TLV��ʽ�̶��ײ�����*/

#define PPP_HA_ENCAPTLV(pBuf, usMsgType, usMsgLen, pPara)\
{\
    USHORT *pusBuf = (USHORT *)(pBuf);\
    *pusBuf = (usMsgType);\
    *(pusBuf+1) = (usMsgLen);\
    (pBuf) += PPP_TLV_HEAD_LENGTH;\
    (VOID)TCPIP_Mem_Copy((pBuf), (usMsgLen) - PPP_TLV_HEAD_LENGTH, (pPara), (usMsgLen) - PPP_TLV_HEAD_LENGTH);\
    (pBuf) += (usMsgLen) - PPP_TLV_HEAD_LENGTH;\
}

#define PPP_BAKUP_FSM_INFO(from, to) \
{ \
    (to).ulTimeOutTime     = (from).ulTimeOutTime; \
    (to).ulEchoTimeOutTime = (from).ulEchoTimeOutTime; \
    (to).usProtocol        = (from).usProtocol; \
    (to).ucState           = (from).ucState; \
}



/* ����IPCP��Ϣ */
/*
from: PPPIPCPINFO_S*
to:   PPPIPCPINFO_BAK_S*
*/

#define PPP_BAKUP_IPCP_INFO_SND(from, to) \
{ \
    PPP_BAKUP_FSM_INFO((from)->stFsm, (to)->stFsmBak); \
    PPP_COPY_IPCP_OPTION((to)->stGotOptions, (from)->stGotOptions); \
    PPP_COPY_IPCP_OPTION((to)->stHisOptions, (from)->stHisOptions); \
    PPP_COPY_IPCP_OPTION((to)->stWantOptions, (from)->stWantOptions); \
    PPP_COPY_IPCP_OPTION((to)->stAllowOptions, (from)->stAllowOptions); \
}

#define PPP_BAKUP_IPCP_INFO_RCV(from, to) \
{ \
    PPP_BAKUP_FSM_INFO((from)->stFsmBak, (to)->stFsm); \
    PPP_COPY_IPCP_OPTION((to)->stGotOptions, (from)->stGotOptions); \
    PPP_COPY_IPCP_OPTION((to)->stHisOptions, (from)->stHisOptions); \
    PPP_COPY_IPCP_OPTION((to)->stWantOptions, (from)->stWantOptions); \
    PPP_COPY_IPCP_OPTION((to)->stAllowOptions, (from)->stAllowOptions); \
}

/* ����MUXCP��Ϣ */
/*
from: PPPMUXCPINFO_S*
to:   PPPMUXCPINFO_BAK_S*
*/

#define PPP_BAKUP_MUXCP_INFO_SND(from, to) \
{ \
    PPP_BAKUP_FSM_INFO((from)->stFsm, (to)->stFsmBak); \
    PPP_COPY_PPPMUX_OPTION((to)->stGotOptions, (from)->stGotOptions);\
    PPP_COPY_PPPMUX_OPTION((to)->stHisOptions, (from)->stHisOptions);\
    PPP_COPY_PPPMUX_OPTION((to)->stWantOptions, (from)->stWantOptions);\
    PPP_COPY_PPPMUX_OPTION((to)->stAllowOptions, (from)->stAllowOptions);\
}

#define PPP_BAKUP_MUXCP_INFO_RCV(from, to) \
{ \
    PPP_BAKUP_FSM_INFO((from)->stFsmBak, (to)->stFsm); \
    PPP_COPY_PPPMUX_OPTION((to)->stGotOptions, (from)->stGotOptions);\
    PPP_COPY_PPPMUX_OPTION((to)->stHisOptions, (from)->stHisOptions);\
    PPP_COPY_PPPMUX_OPTION((to)->stWantOptions, (from)->stWantOptions);\
    PPP_COPY_PPPMUX_OPTION((to)->stAllowOptions, (from)->stAllowOptions);\
}

/* pwd��󳤶�Ϊ20λ */
/* ����PAP��Ϣ */
#define PPP_BAKUP_PAP_INFO_PROC(from, to) \
{ \
    (to)->ucServerState = (from)->ucServerState; \
    (to)->ucClientState = (from)->ucClientState; \
    (VOID)TCPIP_Mem_Copy((to)->szPapUsrName, sizeof((to)->szPapUsrName), (from)->szPapUsrName, PPP_MAXUSERNAMELEN + 2); \
    (VOID)TCPIP_Mem_Copy((to)->szPapUsrPwd, sizeof((to)->szPapUsrPwd), (from)->szPapUsrPwd, PPP_MAXUSERPWDLEN + 2); \
}
/* ����CHAP��Ϣ */
#define PPP_BAKUP_CHAP_INFO_PROC(from, to) \
{ \
    (to)->ucClientState = (from)->ucClientState; \
    (to)->ucServerState = (from)->ucServerState; \
    (VOID)TCPIP_Mem_Copy((to)->szHostName, sizeof((to)->szHostName), (from)->szHostName, PPP_MAXUSERNAMELEN + 2);\
    (VOID)TCPIP_Mem_Copy((to)->szHostPwd, sizeof((to)->szHostPwd), (from)->szHostPwd, PPP_MAXUSERPWDLEN + 2);\
}

/* pwd��󳤶�Ϊ16λ */
/* ����PAP��Ϣ */
#define PPP_BAKUP_PAP_INFO_PROC_OLD(from, to) \
{ \
    (to)->ucServerState = (from)->ucServerState; \
    (to)->ucClientState = (from)->ucClientState; \
    (VOID)TCPIP_Mem_Copy((to)->szPapUsrName, sizeof((to)->szPapUsrName), (from)->szPapUsrName, PPP_MAXUSERNAMELEN + 2); \
    (VOID)TCPIP_Mem_Copy((to)->szPapUsrPwd, sizeof((to)->szPapUsrPwd), (from)->szPapUsrPwd, PPP_MAXUSERPWDLENOLD + 2); \
}
/* ����CHAP��Ϣ */
#define PPP_BAKUP_CHAP_INFO_PROC_OLD(from, to) \
{ \
    (to)->ucClientState = (from)->ucClientState; \
    (to)->ucServerState = (from)->ucServerState; \
    (VOID)TCPIP_Mem_Copy((to)->szHostName, sizeof((to)->szHostName), (from)->szHostName, PPP_MAXUSERNAMELEN + 2);\
    (VOID)TCPIP_Mem_Copy((to)->szHostPwd, sizeof((to)->szHostPwd), (from)->szHostPwd, PPP_MAXUSERPWDLENOLD + 2);\
}

/* ����OSICP��Ϣ */
/*
from: PPPOSICPINFO_S*
to:   PPPOSICPINFO_BAK_S*
*/

#define PPP_BAKUP_OSICP_INFO_SND(from, to) \
{ \
    PPP_BAKUP_FSM_INFO((from)->stFsm, (to)->stFsmBak); \
    PPP_COPY_OSICP_OPTION((to)->stGotOptions, (from)->stGotOptions);\
    PPP_COPY_OSICP_OPTION((to)->stHisOptions, (from)->stHisOptions);\
    PPP_COPY_OSICP_OPTION((to)->stWantOptions, (from)->stWantOptions);\
    PPP_COPY_OSICP_OPTION((to)->stAllowOptions, (from)->stAllowOptions);\
}

#define PPP_BAKUP_OSICP_INFO_RCV(from, to) \
{ \
    PPP_BAKUP_FSM_INFO((from)->stFsmBak, (to)->stFsm); \
    PPP_COPY_OSICP_OPTION((to)->stGotOptions, (from)->stGotOptions);\
    PPP_COPY_OSICP_OPTION((to)->stHisOptions, (from)->stHisOptions);\
    PPP_COPY_OSICP_OPTION((to)->stWantOptions, (from)->stWantOptions);\
    PPP_COPY_OSICP_OPTION((to)->stAllowOptions, (from)->stAllowOptions);\
}

extern ULONG PPP_HA_VirtualCfgInput(UCHAR *pBuf, ULONG ulMsgLen);
extern VOID PPP_HA_SendVirtualInfo(IFNET_S *pstIf);
extern ULONG PPP_HA_ProcessVlinkDel(IFNET_S *pstIf,PPP_IPCP_OPTION_S *pstGotOptions,PPPINFO_S *pstPppInfo);
extern ULONG PPP_HA_ProcessMuxCpDown(IFNET_S *pstIf, PPPINFO_S *pstPppInfo);
extern ULONG PPP_HA_ProcessIpcpDown(IFNET_S *pstIf,PPPINFO_S *pstPppInfo);
extern ULONG PPP_HA_ProcessLcpDown (PPPINFO_S *pstPppInfo);
extern ULONG PPP_HA_ProcessNcpDown (PPPINFO_S *pstPppInfo);

extern ULONG PPP_HA_BatchBackup ();
extern ULONG PPP_HA_RealSnd_PppInfo (PPPINFO_S *pstPppInfo, ULONG  ulMsgType,ULONG ulOper);
extern VOID  PPP_HA_RealSnd_CfgInfo (ULONG ulIfIndex, ULONG  ulMsgType);
extern ULONG PPP_HA_RealSnd_MPCfgInfo (ULONG  ulMsgType,ULONG ulSubIfindex,UCHAR *pszMpGroupName);
extern ULONG PPP_HA_Input(UCHAR * pBuf, ULONG ulMsgLen);
extern ULONG  PPP_HA_Smooth();
extern ULONG PPP_HA_GetPppDbg (ULONG *pulDbg);
extern ULONG TCPIP_HA_SetPppDbg (ULONG ulDbg);
extern VOID PPP_HA_DebugOutPut(UCHAR *pBuf,ULONG ulMsgLen,ULONG ulCmd);
extern ULONG PPP_HA_SetVerboseDbg (ULONG ulDbg);
extern ULONG PPP_HA_GetVerboseDbg (ULONG *pulDbg);
extern ULONG PPP_HA_SearchMpGroupList(ULONG ulFartherIndex ,ULONG ulSonIndex);
extern VOID PPP_HA_GlobalVar();
extern ULONG PPP_HA_Clean();
extern VOID PPP_HA_IPCPDownProcess(PPPINFO_S *pstPppInfo);

extern VOID PPP_HA_NEW_RealSnd_CfgInfo(ULONG ulIfIndex, ULONG ulSubMsgType);
extern ULONG PPP_HA_NEW_SendMsg(UCHAR *pucHABuf, ULONG ulDataLen);
extern ULONG PPP_HA_NEW_BatchCfgInfo(UCHAR *pucHABuf, ULONG ulBakTotalLen, ULONG ulOffsetLen,
                                     ULONG ulType, VOID *pucNode, ULONG *pulBakNodeLen);
extern ULONG PPP_HA_NEW_BatchPppInfo(VOID);
extern ULONG PPP_HA_NEW_BatchCfgInput(UCHAR *pBuf, ULONG ulMsgLen);
extern ULONG PPP_HA_NEW_BatchPppInput(UCHAR *pBuf, ULONG ulMsgLen);
extern VOID PPP_HA_NEW_RealSnd_GlobalVar(USHORT usMsgType);
extern VOID PPP_HA_NEW_BatchGlobalVar();
extern ULONG PPP_HA_NEW_GlobalVarInput(UCHAR *pBuf, ULONG ulMsgLen);
extern ULONG PPP_HA_TLV_BuildOnePkt(ULONG ulIfIndex, UCHAR *pucBuf, USHORT usOffset, USHORT usSubMsgType, USHORT *pusBakLen);
extern ULONG PPP_HA_TLV_RealTimeBak(ULONG ulIfIndex, USHORT usSubMsgType);
extern ULONG PPP_HA_TLV_BatchBak(VOID);
extern ULONG PPP_HA_TLV_Input(UCHAR *pucBuf, ULONG ulMsgLen);
extern ULONG PPP_HA_TLV_Restore(ULONG ulIfIndex, UCHAR *pucBuf, USHORT usMsgType);
extern ULONG PPP_HA_TLV_OutputMsg(UCHAR *pucBuf, UCHAR ucOperation, USHORT usMsgLen);
extern ULONG PPP_HA_TLV_CalcMsgLen(USHORT usSubMsgType, USHORT *pusMsgLen);
extern ULONG PPP_HA_ProcessOsiCpDown(IFNET_S *pstIf, PPPINFO_S *pstPppInfo);
extern ULONG PPP_HA_TLV_PPPStateBatchBak(VOID);

#ifdef  __cplusplus
}
#endif
#endif


