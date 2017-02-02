/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : ppp_type.h
  版 本 号   : 初稿
  作    者   : luofang
  生成日期   : 2012年11月8日
  最近修改   :
  功能描述   : PPP模块类型定义
  函数列表   :
*
*

  修改历史   :
  1.日    期   : 2012年11月8日
    作    者   : luofang
    修改内容   : 创建文件

******************************************************************************/


#ifndef      _PPP_TYPE_H_
#define      _PPP_TYPE_H_

#ifdef      __cplusplus
extern "C" {
#endif/* end of __cplusplus */

#ifndef PPP_MAXUSERNAMELEN
#define PPP_MAXUSERNAMELEN 128
#endif

#define IMSI_ASCII_LEN 16
#define MSISDN_ASCII_LEN 16
#define PPP_SHARE_MEM_LEN 32

#define PPP_AUTH_FLAG   1
#define PPC_AUTH_FLAG   2



/* 配置信息 */
typedef struct tagPppConfigInfo
{
    ULONG bCallbackReq            : 1,
          bCallbackAcc            : 1,
          bCallInAuth             : 1,
          bAuthRmtChap            : 1,
          bAuthRmtPap             : 1,
          bAuthRmtEap             : 1,
          bEnableVJComp           : 1,
          bEnableComp             : 1,
          bSetAsMp                : 1,
          bPapPwdEncrypt          : 1,
          bChapPwdEncrypt         : 1,
          bAuthRmtList            : 1,
          bStacCompress           : 1,
          bMppcCompress           : 1,        /* WGGSN_B03_L2TP_PPPC_COMP*/
          bAuthMethod             : 2,        /* 认证方式 0: 无 1: 强制认证 2: 协商鉴权  */
          bUsedFlag               : 1,        /* 控制块占用标记，1为占用 */
          bRadiusPri              : 1,        /* radius优先分配IP是否打开0 关闭 1 打开*/
          bVsncpAPNAmbrFlag       : 1,
          bVsncpDefApnIndFlag     : 1;

    ULONG  ulNegTimeOut;

    USHORT usMru;
    UCHAR  ucDomainName[PDSN_DOMAINNAME_LEN + 1];
    UCHAR cChapHostName[PPP_MAXUSERNAMELEN + 1];
    UCHAR cChapPassword[PPP_MAXUSERPWDLEN + 1];
    UCHAR cPapUserName[PPP_MAXUSERNAMELEN + 1];
    UCHAR cPapPwd[PPP_MAXUSERPWDLEN + 1];
    UCHAR ucPppcnfRev;                                 /* luofang--八字节对齐 */
} PPPCONFIGINFO_S;


 typedef struct tagPppDebugInfo
{
    ULONG bDebug_Lcp_Packet     : 1,
        bDebug_Lcp_Event        : 1,
        bDebug_Lcp_Error        : 1,
        bDebug_Lcp_StateChange  : 1,
        bDebug_Ipcp_Packet      : 1,
        bDebug_Ipcp_Event       : 1,
        bDebug_Ipcp_Error       : 1,
        bDebug_Ipcp_StateChange : 1,
        bDebug_Ipv6cp_Packet    : 1,
        bDebug_Ipv6cp_Event     : 1,
        bDebug_Ipv6cp_Error     : 1,
        bDebug_Ipv6cp_StateChange: 1,

        bDebug_Pap_Packet       : 1,
        bDebug_Pap_Event        : 1,
        bDebug_Pap_Error        : 1,
        bDebug_Pap_StateChange  : 1,

        bDebug_Chap_Packet      : 1,
        bDebug_Chap_Event       : 1,
        bDebug_Chap_Error       : 1,
        bDebug_Chap_StateChange : 1,

        bDebug_Ccp_Packet       : 1,
        bDebug_Ccp_Event        : 1,
        bDebug_Ccp_Error        : 1,
        bDebug_Ccp_StateChange  : 1,

        bDebug_Ip_Packet        : 1,
        bDebug_Scp_Packet       : 1,
        bDebug_Core_Event       : 1,
        bDebug_Imsi             : 1, /* 单用户调试开关 */ /*Added by hyj for B02*/

        bDebug_EAP_Packet: 1,
        bDebug_EAP_Event: 1,
        bDebug_EAP_Error: 1,
        bDebug_EAP_StateChange: 1;

}  VOS_PACKED PPPDEBUGINFO_S;/* Modified by liutao 38563 at 2005-01-05 PDSN9660 V800R002C01 for BYHD04147 */

typedef struct tagPppCallbacks
{
    ULONG (*pfPhyTransmit)(ULONG, PMBUF_S *);    /* 底层在链路层上注册的供链路层使用的发送报文函数
                                            PDSN: A11_PPPC_A10_Encap */
    ULONG (*pfUpIoCtl)(ULONG, VOID *, ULONG);   /* 上层提供给链路层的向上传递控制信息的函数
                                                PDSN: A11_PPPC_SendUsrInfor */
    ULONG (*pfPhyIoCtl)(ULONG, UCHAR);    /* 底层在链路层上注册的供链路层使用的流程控制函数
                                            PDSN: A11_PPPC_ReleaseA10Inform */
} PPPCALLBACK_S;


 /* 鉴权请求 */
typedef struct tagPppAaaAuthReqMsg
{
    MSG_HDR_S stMsgHdr;             /* NE80头 */
    ULONG     ulMsgType;            /* 消息类型 */
    ULONG     ulSDBIndex;            /* SDB索引 */

    USHORT usCDBIndex;                /* GGSN:APNIndex PDSN:DomainIndex */
    UCHAR  ucPktID;                 /* 用户认证请求包ID */
    UCHAR  ucUsernameLen;           /* 用户名长度 */

    UCHAR ucUsername[A11_MAX_NAI_LENGTH + 1]; /* 用户名 */
    UCHAR ucPwd[18];                /* 密码 */
    UCHAR ucPwdLen;                    /* 密码长度 */
    UCHAR ucChapResponseLen;        /* Chap-Response长度 */

    UCHAR ucChapResponse[256];        /* Chap-Response */
    UCHAR ucChapChallenge[256];        /* Chap-Challenge */

    UCHAR  ucChapChallengeLen;       /* Response长度 */
    UCHAR  ucRes;
    USHORT usVPNID;                 /* VPN ID */

    ULONG  ulIp;                       /* IP地址 */
    A11_IMSI_S stIMSI;                  /* IMSI */
    ULONG  ulIpMask;                   /* IP地址子网掩码 */
    ULONG  ulG4EvtTime;               /* Event Time */
    UCHAR  aucC2CorLID[8];           /* Correlation ID */
    ULONG  ulCurVolume;         /* 流量值 */
    ULONG  ulCurDuration;       /* 时间值 */
    ULONG  ulVUATS;                /* 费率切换点之后的用户流量 */
    USHORT usGroupIndex;                    /* test 消息专用 */
    UCHAR  ucPreparedFlag;   /* 使用A11_PPC_TYPE_E定义 */
    UCHAR  ucUpdateReason;  /* 更新原因 */
    UCHAR  ucRenegoFlag;    /* 重协商标记 */
    UCHAR  ucPPPFlag;       /*携带标志位，值为 1，AUTH判断是PPP或PPC消息*/
    UCHAR  ucReserved[6];
 } AAA_AUTHREQ_S;


 /* IP地址申请消息 */
typedef struct tagPppcApplyIpReqMsg
{
    MSG_HDR_S stMsghead;      /*消息头结构*/
    ULONG     ulIndex;              /*上下文索引*/
    ULONG     ulCDBIndex;        /*索引*/
    ULONG     ulReqIPFlag;          /*申请IP标志，1为申请IP，0为不申请IP*/
    ULONG ulIpadd;
    ULONG ulreserverd;
    UCHAR ucAddrType;
    UCHAR ucScid;
    UCHAR ucReserved[2];
} PPPC_APPLYIP_REQ_MSG_S;

/* IP地址申请响应消息 */
typedef struct tagPppcApplyIpAckMsg
{
    MSG_HDR_S stMsghead;       /*消息头结构*/
    ULONG     ulRetCode;             /*返回码，成功或失败*/
    ULONG     ulIndex;               /*上下文索引*/
    ULONG     ulIpAddr;              /*分配的IP地址*/
    ULONG     ulReserved;           /* luofang--八字节对齐 */
} PPPC_APPLYIP_ACK_MSG_S;



typedef struct tagPppA11Msg         /* A11消息结构 */
{
    ULONG     ulRPIndex;
    ULONG     ulMsgCode;          /* luofang--八字节对齐 */
    union
    {
        ULONG ulSwitchRPIndex;      /* ISPCFSWITCH */
        PPP_LUPPARA_S stLupPara;    /* ISLUP */
    } para;
    ULONG ulL2tpType;
    ULONG ulLcpSendFlag;        /* 1-- send   0-- nosend */
} PPP_A11MSG_S;

typedef struct tagPppIpcpOption
{
    /* 是否协商 */
#if (UGW_BYTE_ORDER == UGW_LITTLE_ENDIAN)
    ULONG neg_addr :         1,   /* Negotiate IP Address? */
            old_addrs:         1,             /* Use old (IP-Addresses) option? */
            req_addr:         1,              /* Ask peer to send IP address? */
            neg_vj:           1,              /* Van Jacobson Compression? */
            neg_dnsaddr0:     1,              /* negotiate Primary DNS server address? */
            req_dnsaddr0:     1,              /* Ask peer to send DNS server address? */
            neg_nbnsaddr0:    1,              /* negotiate Primary NBNS server address? */
            req_nbnsaddr0:    1,              /* Ask peer to send NBNS server address? */
            neg_dnsaddr1:     1,              /* negotiate Secondary DNS server address? */
            req_dnsaddr1:     1,              /* Ask peer to send DNS server address? */
            neg_nbnsaddr1:    1,              /* negotiate Secondary NBNS server address? */
            req_nbnsaddr1:    1,              /* Ask peer to send NBNS server address? */
            accept_dnsaddr0:  1,              /* accept peer's value is changed */
            accept_dnsaddr1:  1,              /* accept peer's value is changed */
            accept_nbnsaddr0: 1,              /* accept peer's value is changed */
            accept_nbnsaddr1: 1,              /* accept peer's value is changed */
            accept_reserved: 16;
#else
    ULONG accept_reserved: 16,
            accept_nbnsaddr1: 1,              /* accept peer's value is changed */
            accept_nbnsaddr0: 1,              /* accept peer's value is changed */
            accept_dnsaddr1:  1,              /* accept peer's value is changed */
            accept_dnsaddr0:  1,              /* accept peer's value is changed */
            req_nbnsaddr1:    1,              /* Ask peer to send NBNS server address? */
            neg_nbnsaddr1:    1,              /* negotiate Secondary NBNS server address? */
            req_dnsaddr1:     1,              /* Ask peer to send DNS server address? */
            neg_dnsaddr1:     1,              /* negotiate Secondary DNS server address? */
            req_nbnsaddr0:    1,              /* Ask peer to send NBNS server address? */
            neg_nbnsaddr0:    1,              /* negotiate Primary NBNS server address? */
            req_dnsaddr0:     1,              /* Ask peer to send DNS server address? */
            neg_dnsaddr0:     1,              /* negotiate Primary DNS server address? */
            neg_vj:           1,              /* Van Jacobson Compression? */
            req_addr:         1,              /* Ask peer to send IP address? */
            old_addrs:         1,             /* Use old (IP-Addresses) option? */
            neg_addr :         1;   /* Negotiate IP Address? */
#endif
    ULONG  ouraddr;
    ULONG  hisaddr;      /* Addresses in NETWORK BYTE ORDER */
    ULONG  dnsaddr0;
    ULONG  nbnsaddr0;   /* Primary DNS address and Primary NDNS address */
    ULONG  dnsaddr1;
    ULONG nbnsaddr1;   /* Secondary DNS and NBNS address */
    USHORT vj_protocol;           /* protocol value to use in VJ option */
    UCHAR  maxslotindex;
    UCHAR  cflag;   /* values for RFC1332 VJ compression neg. */
} VOS_PACKED PPP_IPCP_OPTION_S;

typedef struct tagPppIpv6cpOption
{
    /* 是否协商 */
#if (UGW_BYTE_ORDER == UGW_LITTLE_ENDIAN)
    ULONG   neg_addr :        1,   /* Negotiate IP Address? */
            old_addrs:        1,             /* Use old (IP-Addresses) option? */
            req_addr:         1,              /* Ask peer to send IP address? */
            neg_vj:           1,              /* Van Jacobson Compression? */
            neg_dnsaddr0:     1,              /* negotiate Primary DNS server address? */
            req_dnsaddr0:     1,              /* Ask peer to send DNS server address? */
            neg_nbnsaddr0:    1,              /* negotiate Primary NBNS server address? */
            req_nbnsaddr0:    1,              /* Ask peer to send NBNS server address? */
            neg_dnsaddr1:     1,              /* negotiate Secondary DNS server address? */
            req_dnsaddr1:     1,              /* Ask peer to send DNS server address? */
            neg_nbnsaddr1:    1,              /* negotiate Secondary NBNS server address? */
            req_nbnsaddr1:    1,              /* Ask peer to send NBNS server address? */
            accept_dnsaddr0:  1,              /* accept peer's value is changed */
            accept_dnsaddr1:  1,              /* accept peer's value is changed */
            accept_nbnsaddr0: 1,              /* accept peer's value is changed */
            accept_nbnsaddr1: 1,              /* accept peer's value is changed */
            accept_reserved: 16;            /* luofang--八字节对齐 */
#else
      ULONG accept_reserved: 16,            /* luofang--八字节对齐 */
            accept_nbnsaddr1: 1,              /* accept peer's value is changed */
            accept_nbnsaddr0: 1,              /* accept peer's value is changed */
            accept_dnsaddr1:  1,              /* accept peer's value is changed */
            accept_dnsaddr0:  1,              /* accept peer's value is changed */
            req_nbnsaddr1:    1,              /* Ask peer to send NBNS server address? */
            neg_nbnsaddr1:    1,              /* negotiate Secondary NBNS server address? */
            req_dnsaddr1:     1,              /* Ask peer to send DNS server address? */
            neg_dnsaddr1:     1,              /* negotiate Secondary DNS server address? */
            req_nbnsaddr0:    1,              /* Ask peer to send NBNS server address? */
            neg_nbnsaddr0:    1,              /* negotiate Primary NBNS server address? */
            req_dnsaddr0:     1,              /* Ask peer to send DNS server address? */
            neg_dnsaddr0:     1,              /* negotiate Primary DNS server address? */
            neg_vj:           1,              /* Van Jacobson Compression? */
            req_addr:         1,              /* Ask peer to send IP address? */
            old_addrs:        1,             /* Use old (IP-Addresses) option? */
            neg_addr :        1;   /* Negotiate IP Address? */
#endif

    USHORT vj_protocol;                      /* protocol value to use in VJ option */
    UCHAR  maxslotindex;
    UCHAR  cflag;              /* values for RFC1332 VJ compression neg. */
    USHORT OurV6InId[IPV6_ADDR_LEN/2];
    USHORT HisV6InId[IPV6_ADDR_LEN/2];    /*保存aaa下发的接口id*/
    USHORT ConfigV6InId[IPV6_ADDR_LEN/2]; /*保存本地配置的接口id*/
} VOS_PACKED PPP_IPV6CP_OPTION_S;
typedef struct ccp_options
{
    ULONG  ulMppc_supportedbits;  /* # Supported Bits for MPPC Compress */
    USHORT usStac_historys;        /* # history number for stacker Compress */

#if (UGW_BYTE_ORDER == UGW_LITTLE_ENDIAN)

    UCHAR   bStac_compress : 1,       /* do stacker Compress? */
            bLZS0_comp: 1,
            bLZS1_comp: 1,
            bMppc_compress: 1,                 /* do Mppc Compress? */
            breserved: 4;        /* luofang--八字节对齐 */
#else
    UCHAR   breserved: 4,        /* luofang--八字节对齐 */
            bMppc_compress: 1,                 /* do Mppc Compress? */
            bLZS1_comp: 1,
            bLZS0_comp: 1,
            bStac_compress : 1;       /* do stacker Compress? */
#endif

    UCHAR ucStac_checkmode;      /* # stacker compress check mode ( sequence number ) */
} PPP_CCP_options_S;

typedef struct tagPppRenegoInfo
{
    UCHAR               ucIpcpFlag;
    UCHAR               ucIpV6cpFlag;
    UCHAR               ucCcpFlag;
    UCHAR               ucPrenegoRev[5];
    PPP_IPCP_OPTION_S   stIpcpOptions;
    PPP_IPV6CP_OPTION_S stIpcpV6Options;
    PPP_CCP_options_S   stCcpOptions;
} PPPRENOGOINFO;

#ifndef LAP_POOL_NAME_MAX_LENGTH
#define LAP_POOL_NAME_MAX_LENGTH 32
#endif
/* PPP控制块 */
typedef struct tagPppInfo
{
    /*********************************/
    /*       指针定义              */
    /*********************************/
    PPPCONFIGINFO_S* pstConfigInfo;         /* 配置信息 */
    PPPCONFIGINFO_S* pstUsedConfigInfo;     /* 当前接口上用户输入的配置信息,只对配置可见接口有效 */
    PPPRENOGOINFO*   pstPppRenegoInfo;      /* 重协商信息 */

    VOID* pstLcpInfo;           /* LCP  控制块指针 */
    VOID* pstPapInfo;           /* PAP  控制块指针 */
    VOID* pstChapInfo;          /* CHAP 控制块指针 */
    VOID* pstEapInfo;           /* EAP  控制块 */
    VOID* pstIpcpInfo;          /* IPCP 控制块指针 */
    VOID* pstIpV6cpInfo;        /* IPV6CP 控制块指针 */
    VOID* pstVsncpInfo;         /* VSNCP 控制块指针 */
    VOID* pstCcpInfo;           /* CCP  控制块指针 */
    VOID* pL2tpPara;            /* L2TP需要的参数 */
    VOID* pulCurrFsm;           /* 当前状态机 */
    VOID* pstHdlcInfo;

    ULONG bIsAsync          : 1,        /* 是否是异步口, 在LCP中判断是否协商ACCMAP */
          bSynAsyConvert    : 1,        /* 对于异步口，用于确定是否由PPP进行同/异步报文转换 */
          bLoopBacked       : 1,        /* 接口是否发生了自环 */
          bLowerIsUp        : 1,
          bIPReleaseFlg     : 1,        /* 0: 需要释放IP， 1: 不需要释放IP(MIP&L2tp用户)*/
          bIPTech           : 2,        /* 0: SIP; 1: MIP; 2: MIPAgent ;3 NIL*/
          bAuthServer       : 1,        /* PDSN产品形态仅支持server模式；0表示认证完毕或者免认证；1正在进行认证 */
          bAuthClient       : 1,        /* PDSN产品形态不支持client模式；该值始终为零 */
          bReNego           : 1,        /* 重协商标志 */
          bReNegoV6         : 1,        /* IPV6重协商标志 */
          bPppStateFlg      : 2,        /* 稳态连接标记 */
          bPppMode          : 1,        /* 终结模式为0，续传模式为1 */
          bPppClient        : 1,        /* 客户端模式为1，否则为0 */
          bPhaseFlag        : 2,        /* 0:LCP阶段，1:鉴权阶段，2:IPCP阶段 3:成功阶段 */
          bFailFlag         : 4,        /* 0:自己协商失败. 1:A11/GTPC通知删除. 2:用户要求下线. 3:L2TP通知删除 */
          bMppcFlag         : 1,        /* MPPC用户数统计标志 */
          bVjFlag           : 1,        /* VJ用户数统计标志 */
          bLzs0Flag         : 1,        /* Stac_Lzs0用户数统计 */
          bLzs1Flag         : 1,        /* Stac_Lzs1用户数统计 */
          bPpcAAAFlag       : 1,
          bPppSuccess       : 1,        /* PPP建立成功标记,用于PPP指标优化 */
          bAuthFlag         : 1,        /* 用于判断是否已经完成过chap或pap鉴权,若是VOS_TRUE,则重协商不再走AAA */
          bIpcpSucFlag      : 1,        /* PPP协商IPCP协商成功标记,该标记在重协商过程也不会改变 */
          bPppStateFlgV6    : 2,        /* IPV6稳态连接标记 */
          bPccFlag          : 1;        /* 是否为PCC用户标识*/

    ULONG bRecvLcpMsgFlag   : 1,        /* 表示是否收到过LCP的消息*/
          bIpv6cpNoToPDN    : 1,        /* ipv6cp finish 时是否通知PDN, 0表示通知， 1为不通知 */
          bIpcpNoToPDN      : 1,        /* ipcp finish 时是否通知PDN, 0表示通知， 1为不通知 */
          bEhrpdUser        : 1,        /* 是否为eHRPD用户 */
          bEAPAuthFlag      : 1,        /* EAP是否已经成功过 */
          bIPCPNakHandFlag  : 1,        /* IPCP NAK HANDLING */
          bReservNew        : 26;       /* 注意修改为对齐 */


    /*********************************/
    /*       结构体定义              */
    /*********************************/
    IMSI_S            stIMSI;

    PPPDEBUGINFO_S stPppDebugInfo;    /* 调试信息 */
    ULONG ulNowUTCInSec;
    ULONG ulRemoteAccm;         /* 对端ACCM控制字 */
    ULONG ulLocalAccm;          /* 本端ACCM控制字 */
    ULONG ulRPIndex;
    ULONG ulPcfIP;
    ULONG ulIPAddr;             /* 本端IP地址，初始化为2.2.2.2 */
    ULONG ulPeerIPAddr;         /* 保存RADIUS SERVER或DHCP发送的用户IP地址 */
    ULONG ulDNSAddr1;
    ULONG ulDNSAddr2;
    ULONG64 ulNegoStartTime;      /* PPP协商开始时间 */
    ULONG64 ulNegoEndTime;
    USHORT usPeerId;                /* 保存第一次发送服务器id */
    USHORT usTokenId;

    USHORT usState;
    USHORT usPhase;              /* PPP当前所处协商阶段,可以为如下值:
                                                 PPP_PHASE_DEAD
                                                 PPP_PHASE_ESTABLISH
                                                 PPP_PHASE_AUTHENTICATE
                                                 PPP_PHASE_CBCP
                                                 PPP_PHASE_NETWORK
                                                 PPP_PHASE_TERMINATE
                                               */
    USHORT usCDBIndex;     /* GGSN:APNIndex PDSN:DomainIndex */
    USHORT usVirtualDomainIdx;

    USHORT usMtu;
    USHORT usPcfIndex;

    USHORT usIpv6Addr[IPV6_ADDR_LEN];     /*本端ipv6地址，初始化为:FE80::FFFF:FFFF:FFFF:FFFF*/
    USHORT usPeerIPv6Addr[IPV6_ADDR_LEN]; /* 保存RADIUS SERVER或lap分配的用户IPv6地址包含前缀和接口id*/


    UCHAR ucNAI[A11_MAX_NAI_LENGTH + 1];

    UCHAR  ucServiceOpt;
    UCHAR  ucFSMFailType;           /* FSM_CODE_E */
    UCHAR  ucDmpuId;                /* 压缩子卡CPU号, 0为CPU2, 1为CPU3 */
    UCHAR  ucDpeId;                 /* 子卡DPE号 */

    UCHAR  ucIpCapability;     /*ip能力，参见枚举 PDSN_PPP_IPTYE 定义 */

    UCHAR ucPppRleaseCode;    /* PPP模块发起退网通知USM原因值 */
    UCHAR ucV4NcpReleaseCode;   /* 网络阶段协商失败通知PDN的原因值 */
    UCHAR ucV6NcpReleaseCode;   /* 网络阶段协商失败通知PDN的原因值 */
    UCHAR ucAAAType;            /* ehrpd aaa 服务器类型 */

    PS_BOOL_ENUM_UINT8      enServerTermReq;  /* 记录是否是由网侧断开所有PDN连接导致PPP释放链路 */

    VOS_UINT8 aucReserved[6];
} PPPINFO_S;


/* Multilink User链表节点 */
typedef struct tagPppMultilinkUser
{
    struct tagPppMultilinkUser *pNext;        /* 链表指针 */
    CHAR cUserName[PPP_MAXUSERNAMELEN + 2];   /* 用户名 */
    CHAR c_IntfName[200 + 2];                 /* virtual template接口名 */
    CHAR ucReserved[4];                       /* luofang--八字节对齐 */
} PPPMULTILINKUSER_S;

/* 状态机模块数据结构定义 */
typedef struct tagPppFsm
{
    CHAR *    pProtocolInfo;         /* 子协议控制块指针 */
    CHAR *    pPppInfo;             /* PPP控制块指针 */
    struct tagPppFsmCallbacks *pstCallBacks;  /* 回调函数集 */
    ULONG     ulTimeOutTime;         /* config request报文的超时时间 */
    ULONG     ulEchoTimeOutTime;     /* LCP Echo request报文的超时时间 */
    RELTMR_T     ulTimeOutID;           /* config request报文的定时器 */
    RELTMR_T  ulEchoTimeoutID;       /* LCP Echo request报文的定时器 */
    RELTMR_T     ulVendorSpecificTimeID;      /* 版本能力协商响应定时器 */
    USHORT usProtocol;             /* 子协议的PPP协议号 */
    SHORT  sRetransmits;            /* config request报文重传次数 */
    USHORT usNakloops;             /* Nak对方同一个选项的次数 */
    UCHAR  ucState;                  /* 协议状态 */
    UCHAR  ucPktId;                  /* 本协议当前报文的ID */
    UCHAR  ucEchoId;                 /* LCP Echo request报文的ID */
    UCHAR  ucEchoState;            /*r002 add record echo state*/
    SHORT  usVSRetransmits;        /* 版本能力协商指示报文重传次数 */
    UCHAR  ucVSId;                 /*版本能力协商指示报文的Identifier */
    UCHAR  ucTimerType;
    UCHAR  ucRev[6];
} PPPFSM_S;

typedef struct tagPppFsmCallbacks
{
    /* 动作：协商报文处理 */
    VOID (*resetci)(PPPFSM_S *);   /* 根据配置信息设置协商初始值 */
    USHORT (*cilen)(PPPFSM_S *);    /* 我要发送的request报文长度 */
    VOID (*addci)(PPPFSM_S *, UCHAR *);

    /* 组织协商报文 */
    USHORT (*ackci)(PPPFSM_S *, UCHAR *, ULONG);

    /* 处理对方的ack报文 */
    USHORT (*nakci)(PPPFSM_S *, UCHAR *, ULONG);

    /* 处理对方的nak报文 */
    USHORT (*rejci)(PPPFSM_S *, UCHAR *, ULONG);

    /* 处理对方的reject报文 */
    UCHAR (*reqci)(PPPFSM_S *, UCHAR *, ULONG *);

    /* 处理对方的request报文 */
    USHORT (*extcode)(PPPFSM_S *, UCHAR, UCHAR, UCHAR *, UCHAR *, ULONG, ULONG);/* Modified by liutao 38563 at 2004-09-22 V800R002 for PPP压缩移植 */
    /* 处理协议特有的报文，如protocol reject等 */

    /* 事件：协议转入了终止状态 */
    VOID (*up)(PPPFSM_S *);         /* 协议up */
    VOID (*down)(PPPFSM_S *);       /* 协议暂时down,马上要重新协商.
                                       与finished的区别是:对于PPPOE、DDR等的情况，
                                       不用通知下层拆除链路 */
    VOID (*finished)(PPPFSM_S *);   /* 协议结束，通知底层:拆除链路.对于LCP,只要不是
                                       PPPOE、DDR等的情况,则会设置reset定时器,
                                       超时后重新启动协商 */
    VOID (*starting)(PPPFSM_S *);   /* tls(This-Layer-Started)动作中，通知下层:我准
                                       备好了重新协商,如可能,请发一个up事件.
                                       协议对这个动作没有具体规定,可以不实现*/

    /* 子协议信息 */
    CHAR proto_name[8];             /* 子协议名 */
} PPPFSMCALLBACK_S;

/*用于用户名和密码验证(CHAP/PAP)*/
typedef struct tagPppAuthMsg
{
    USHORT usType;
    UCHAR  ucPktID;
    CHAR   szUsrName[PPP_MAXUSERNAMELEN + 2];
    UCHAR  ucUsrNameLen;
    CHAR   szPwd[256];
    UCHAR  ucPwdLen;
    CHAR   szResponse[256];
    UCHAR  ucResponseLen;
} PPPAUTHMSG_S;

 typedef struct tagPppNegoNode
{
    struct tagPppNegoNode* pNext;
    ULONG ulRpIndex;
    ULONG ulPDNIndex;
    UCHAR ucCounter;   /* 协商超时计数器 */
    UCHAR ucNodeType;
    UCHAR aucRsv[2];
} PPP_NEGO_NODE_S;

 typedef struct tagPppLcpOption
{
    /* 是否协商 */
    ULONG neg_mru           : 1,
          neg_asyncmap      : 1,
          neg_upap          : 1,
          neg_chap          : 1,
          neg_eap           : 1,
          neg_magicnumber   : 1,
          neg_pcompression  : 1,
          neg_accompression : 1,
          neg_lqr           : 1,
          neg_mrru          : 1,
          neg_ssnhf         : 1,
          neg_discr         : 1,
          neg_callback      : 1,
          neg_reserved      :19;    /* luofang--八字节对齐 */

    /* 协商参数值 */
    USHORT mru;
    USHORT mrru;
    ULONG  asyncmap;
    ULONG  magicnumber;
    ULONG  numloops;
    ULONG  lqr_period;      /* Reporting period for LQR 1/100ths second */
    UCHAR  chap_mdtype;
    UCHAR  discr_len;
    UCHAR  discr_class;
    UCHAR  callbackopr;
    UCHAR  discr_addr[20];
    UCHAR  callbackinfo[PPP_MAX_CALLBACK_INFO_LEN];
    UCHAR  callbacklen;
    UCHAR  ucReserved[3];   /* luofang--八字节对齐 */
} PPP_LCP_OPTION_S;

typedef struct tagPPP_PPPINFO_BKP_V
{
    IMSI_S stIMSI;
    PPPDEBUGINFO_S stPppDebugInfo; /* 接口的debug开关信息 */
    PPP_LCP_OPTION_S  stLcpGotOptions;
    PPP_IPCP_OPTION_S stIpcpGotOptions;
    PPP_IPV6CP_OPTION_S stIpv6cpGotOptions;

    ULONG bIsAsync      : 1,        /* 是否是异步口, 在LCP中判断是否协商ACCMAP */
          bSynAsyConvert: 1,        /* 对于异步口，用于确定是否由PPP进行同/异步报文转换 */
          bLoopBacked   : 1,        /* 接口是否发生了自环 */
          bLowerIsUp    : 1,
          bIPTech       : 2,        /* 0: SIP; 1: MIP; 2: MIPAgent */
          bAuthServer   : 1,
          bAuthClient   : 1,
          bReNego       : 1,        /* 重协商标志 */
          bStac         : 1,        /* stac压缩标记 */
          bMppc         : 1,        /* mppc压缩标记 */
          bPppMode      : 1,        /* 终结模式为0，续传模式为1 */
          bPppClient    : 1,        /* 客户端模式为1，否则为0 */
          bIsNullFlag   : 1,        /* 空的控制块标记 */
          bIPReleaseFlg : 1,        /* 0: 需要释放IP， 1: 不需要释放IP(MIP&L2tp用户)*/
          bReNegoV6     : 1,        /* IPV6重协商标志 */
          bPppStateFlg  : 2,        /* ipv4稳态连接标记 */
          bPppStateFlgV6: 2,        /* ipv6稳态连接标记 */
          bPhaseFlag    : 2,        /* 该标记目前仅用于SNMP告警统计，后续可以考虑优化。
                                                          0:LCP阶段，1:鉴权阶段，2:IPCP阶段 3:成功阶段 */
          bRev: 10;

    ULONG  ulDhcpTimeOutTime;    /* 超时时间 */
    ULONG  ulDNSAddr1;
    ULONG  ulDNSAddr2;
    ULONG  ulRemoteAccm;        /* 对端ACCM控制字 */
    ULONG  ulLocalAccm;         /* 本端ACCM控制字 */
    ULONG  ulRPIndex;
    ULONG  ulPeerIPAddr;        /* 保存RADIUS SERVER或DHCP发送的用户IP地址 */
    ULONG  ulPcfIP;             /* PCFIP */

    USHORT usMtu;
    USHORT usCDBIndex;

    USHORT usVirtualDomainIdx;
    USHORT usPeerIPv6Addr[IPV6_ADDR_LEN]; /* 保存RADIUS SERVER或lap分配的用户IPv6地址 包含前缀和接口id*/

    UCHAR ucDmpuId;
    UCHAR ucDpeId;
    UCHAR ucDhcpUsed;           /*dhcp控制块占用标记 1 已占用 0 未占用*/
    UCHAR ucIpCapability;     /*ip能力，参见枚举 PDSN_PPP_IPTYE 定义 */
    UCHAR ucIpv6cpPktId;
    UCHAR ucPpcAAAFlag;
    UCHAR ucNAI[A11_MAX_NAI_LENGTH + 1];
}PPP_PPPINFO_BKP_S;

/* PPPC控制块的备份结构 */
typedef struct tagPPP_BKP_V
{
    HAMSGHEAD_S       stHaMsg;
    UCHAR             ulRecordCount;
    UCHAR             ucRev[7];
    PPP_PPPINFO_BKP_S stPppInfobkp[PPP_BKP_INFO_MAX];
} VOS_PACKED PPP_BKP_S;

/* 记录定时备份时间间隔内发生改变的控制块索引的结构*/
typedef struct tagPPP_CHANGEDINFO_BKP_S
{
    ULONG ulChangeFlag;
    ULONG ulNextIndex;
} VOS_PACKED PPP_CHANGEDINFO_BKP_S;


typedef struct
{
    ULONG ulLCPInitFail;      /*LCP init 失败*/
    ULONG ulLCPStartingFail;  /*LCP Starting 失败*/
    ULONG ulLCPClosedFail;    /*LCP Closed 失败*/
    ULONG ulLCPStopedFail;    /*LCP Stoped 失败*/
    ULONG ulLCPClosingFail;   /*LCP Closing 失败*/
    ULONG ulLCPStoppingFail;  /*LCP Stopping 失败*/
    ULONG ulLCPReqsentFail;   /*LCP Reqsent 失败*/
    ULONG ulLCPAckrcvdFail;   /*LCP Ackrcvd 失败*/
    ULONG ulLCPAcksentFail;   /*LCP Acksent 失败*/
    ULONG ulLCPOtherFail;     /*LCP 其他原因失败*/
    ULONG ulIPCPInitFail;     /* IPCP Init 失败*/
    ULONG ulIPCPStartingFail; /* IPCP Starting 失败*/
    ULONG ulIPCPClosedFail;   /* IPCP Closed 失败*/
    ULONG ulIPCPStopedFail;   /* IPCP Stoped 失败*/
    ULONG ulIPCPClosingFail;  /* IPCP Closing 失败*/
    ULONG ulIPCPStoppingFail; /* IPCP Stopping 失败*/
    ULONG ulIPCPReqsentFail;  /* IPCP Reqsent 失败*/
    ULONG ulIPCPAckrcvdFail;  /* IPCP Ackrcvd 失败*/
    ULONG ulIPCPAcksentFail;  /* IPCP Acksent 失败*/
    ULONG ulIPCPOtherFail;    /*IPCP 其他原因失败*/
} PPP_FAIL_COUNTER;

/* L2TP用户数告警结构 */
typedef struct
{
    ULONG ulsn; /*槽号*/
    ULONG ulrate; /* 用户上线率 */
} PPP_L2TP_USERALARM_S;

typedef struct tagCCPMsg
{
    MSG_HDR_S stMsgHdr;
    ULONG     ulUserIndex; /*该用户的索引*/
    UCHAR     ucCode; /*ccp报文的code*/
    UCHAR     ucIdFlag; /*ccp报文中的ID*/
    USHORT    usReserved; /* 保留字段，为了四字节对齐 */
} PPPCOMP_CCPMSG_S;

typedef struct tagLinkItem
{
    PF_USHORT offset;
    PF_USHORT lcopy;
    PF_ULONG  seq;
    PF_USHORT litem;
    PF_USHORT usRsvd[3];    /*保证后面的指针按8字节对齐*/
    PF_UCHAR *pdata;        /*用于存储MBUF数据区地址(偏过IP+GRE)*/
    PMBUF_S  *pMbuf;        /*用于存储MBUF地址*/
    struct tagLinkItem* pnext;
}LINKITEM_S;

typedef struct tagLinkTcb
{
    PF_UCHAR tcounter : 1;
    PF_UCHAR seqflag  : 1;
    PF_UCHAR endflag  : 1;  /*之前发出的最后一个报文以7E结尾*/
    PF_UCHAR clearflag: 1;
    PF_UCHAR grpkt    : 4;  /*链中等待重组的数据包的个数*/

    PF_UCHAR pkt_num;
    PF_UCHAR ucNum_seq;
    PF_UCHAR aucRsv1[1];

    LINKITEM_S* phead;      /*保证phead按8字节对齐*/
    PF_ULONG seq_late;      /*等待的下一个序列号*/
}LINKTCB_S;



#ifdef      __cplusplus
}
#endif      /* end of __cplusplus */

#endif      /* end of _PPP_TYPE_H_ */
