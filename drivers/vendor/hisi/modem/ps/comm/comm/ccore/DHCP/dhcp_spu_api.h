
#ifndef __DHCP_SPU_API_H__
#define __DHCP_SPU_API_H__

/*******************************************************************************************************/
/********************                          宏定义                           ************************/
/*******************************************************************************************************/
/*dhcp数据包中的chaddr 域,sname域和file域的长度*/
#define DHCPS_CHADDR_LEN               16
#define DHCPS_SNAME_LEN                64
#define DHCPS_FILE_LEN                128

#define DHCPV6C_MAX_DUID_LEN 14 /* DUID 的最大长度 14字节 */

/* 24bit大小字节序转换---主要是transctionId是24bit 0x15001605----0x15051600*/
#ifndef VOS_NTOHBIT24
#if VOS_BYTE_ORDER == VOS_BIG_ENDIAN
#define VOS_NTOHBIT24(x)    (x)
#define VOS_HTONBIT24(x)    (x)
#else
#define VOS_NTOHBIT24(x)    ((((x) & 0x0000ff) << 16) | \
             ((x) & 0x00ff00) | \
             (((x) & 0xff0000) >> 16) )

#define VOS_HTONBIT24(x)    ((((x) & 0x0000ff) << 16) | \
             ((x) & 0x00ff00) | \
             (((x) & 0xff0000) >> 16) )
#endif
#endif

/*******************************************************************************************************/
/********************                        结构定义                           ************************/
/*******************************************************************************************************/

/*DHCPS和USM之间的消息类型*//*需要放到pub.h中*/
typedef enum tagDHCPS_USM_MSG_E
{
    DHCPS_USM_APPLYIP_MSG           =  1,   /*DHCPS发送给USM申请IP地址*/
    DHCPS_USM_RELEASEIP_MSG        =  2,  /*DHCPS发送给USM释放IP地址*/
    DHCPS_USM_APPLYIPOK_MSG       = 3,  /*USM回应的申请地址成功*/
    DHCPS_USM_APPLYIPFAILED_MSG = 4,  /*USM回应的申请地址失败*/
    DHCPS_USM_DEACTIVE_MSG         = 5,  /*USM发送的取活用户*/
    DHCPS_USM_MSG_END
}DHCPS_USM_MSG_E;

/*DHCP控制块*/
typedef struct tagDHCPC_CTRLBLK
{
    struct tagDHCPC_CTRLBLK *pstPreNode;
    struct tagDHCPC_CTRLBLK *pstNextNode;
    VOID *pTmpDhcpCtrlBlkPtr;       /* 用于保存临时控制块指针 */
    ULONG       ulDHCPCtxIdx;       /*DHCP控制块索引*/
    ULONG       ulPDPIndex;         /*用户的上下文索引*/
    ULONG       aulMSISDN[2];       /*MSISDN*/
    ULONG       aulIMSI[2];         /*IMSI*/
    ULONG       aulIMEI[2];         /* IMEI */
    ULONG       ulLease;            /*获得的lease*/
    ULONG       ulTimeStamp;        /*发送REQ消息的系统时间*/
    ULONG       aulSrvIp[4];        /*交互的server IP*/
    ULONG       aulUserIpAddr[4];   /*用户上下文的IP地址*/
    ULONG       aulMainDnsAddr[4];  /*主DNS-IP地址*/
    ULONG       aulSecdDnsAddr[4];  /*备DNS-IP地址*/
    ULONG       aulAgentIpAddr[4];  /*代理IP地址*/
    ULONG       ulTmpVar;           /*临时变量，用于保存临时控制块指针及续约时发送REQ的ulTimeStamp*/
    ULONG       ulTEIDC;            /* TEIDC. 注意!!!! 不可随意修改。在Dhcpv6的使用中,仅可在控制块管理函数中修改。 */
    ULONG       ulT1;               /* DHCPv6地址的T1时间 */
    ULONG       ulT2;               /* DHCPv6地址的T2时间 */

    USHORT      usVPNIndex;         /* 保存LAP消息中的VPN索引 */
    USHORT      usPoolIndex;
    USHORT      usServerGrpIndex;   /*ServerGrp index*/
    USHORT      usApnIndex;         /*APN索引*/ /* Modified by heguangwei 65937 at 2008-04-29 performance for AX4D00955 */

    USHORT      usSeqNum;
    UCHAR       ucUserType:4;       /*UserType ppp,gtp*/
    UCHAR       usDhcpStatus:4;     /*DHCP状态*/ /* Modified by heguangwei 65937 at 2008-04-29 performance for AX4D00955 */
    UCHAR       ucRole:4;
    UCHAR       ucUser:4;            /*用户类型:V0:0;V1:1;V2:2*/
    UCHAR       ucCurSvrSendCount:4; /* 向当前Server发送消息的次数 */
    UCHAR       ucTotalSendCount:4;  /* 向Server发送消息的总次数 */
    UCHAR       ucResendTimeout;     /* 在发送消息的第一次获取,重发消息过程中不获取. */
    UCHAR       ucCurrentServer:1;
    UCHAR       ucWaitRspTimeOutNum:4;
    UCHAR       ucAgingFlag:3;       /* 控制块标记 */
    UCHAR       ucLAPNo;

    UCHAR       aucSiDuid[DHCPV6C_MAX_DUID_LEN]; /* 分配地址的DHCP服务器ID */
    UCHAR       ucIpType:4;
    UCHAR       ucResource:3;       /* 资源位标志 */
    UCHAR       ucUsedFlag:1;       /* 控制块是否占用标志. 注意!!!! 仅可在控制块管理函数中修改。  */
    UCHAR       ucLeaseStatus:4;    /* 租约状态 */
    UCHAR       ucCause:4;

    UCHAR       ucRandomNo;

#if 0
    UCHAR       aucResved[3];       /*保留字段*/
#endif
    VOS_UINT8   ucRabId;                      /*RabId*/
    MODEM_ID_ENUM_UINT16  enModemId;          /*enModemId*/
}DHCPC_CTRLBLK;

/* BEGIN: Added by jixiaoming for 节省内存 at 2012-10-26 */

typedef struct tagDHCPV4C_BAK_INFO_S
{
    ULONG       ulUserIpAddr;
    ULONG       ulAgentIpAddr;
    ULONG       ulServerIp;
    UCHAR       aucReserve[44];
}DHCPV4C_BAK_INFO_S;

typedef struct tagDHCPV6C_BAK_INFO_S
{
    ULONG       aulUserIpAddr[4];
    ULONG       aulAgentIpAddr[4];
    ULONG       ulT1;               /* DHCPv6地址的T1时间 */
    ULONG       ulT2;               /* DHCPv6地址的T2时间 */
    UCHAR       aucSiDuid[DHCPV6C_MAX_DUID_LEN];    /* 分配地址的DHCPV6服务器ID */
    UCHAR       ucLeaseStatus:4;    /* 租约状态.V6是使用 */
    UCHAR       ucResource:3;       /* 资源位,V6使用 */
    UCHAR       ucCurrentServer:1;  /* 当前使用的Server,V6使用 */
    UCHAR       ucReserve;
}DHCPV6C_BAK_INFO_S;

/*
   DHCP Client备份控制块.其中存放的为必须备份的数据,非必须备份数据不可放入。
   修改该结构体,会影响到CKP申请的内存大小。所以修改该结构体务必通过MDE评审。
*/
typedef struct tagDHCPC_BACKBLK_S
{
    ULONG       aulMSISDN[2];       /* MSISDN */
    ULONG       aulIMSI[2];         /* IMSI */
    ULONG       aulIMEI[2];         /* IMEI */
    ULONG       ulLease;            /* lease时长,V4、V6共用 */
    ULONG       ulTimeStamp;        /* 地址申请或renew成功的时间点 */
    ULONG       ulTEIDC;
    ULONG       ulPDPIndex;         /* 上下文索引 */
    USHORT      usVPNIndex;         /* 保存从LAP消息中获取的VPN索引 */
    USHORT      usPoolIndex;        /* 地址池索引 */
    USHORT      usServerGrpIndex;   /* ServerGrp index*/
    USHORT      usApnIndex;         /* APN索引 */

    union
    {
        DHCPV4C_BAK_INFO_S stDhcpv4;
        DHCPV6C_BAK_INFO_S stDhcpv6;
    }unBakInfo;

    UCHAR       ucLAPNo;            /* 分配地址的LAP集中点的编号 */
    UCHAR       ucRandomNo;         /* 随机跟踪号 */
    UCHAR       ucRole:4;           /* 目前保存上下文的角色 */
    UCHAR       usDhcpStatus:4;     /* DHCP状态 */
    UCHAR       ucReserve;
}DHCPC_BACK_BLK_S;
/* END: Added by jixiaoming for 节省内存 at 2012-10-26 */

/*dhcp网络包物理结构DHCPS_ANALYZEDPACKET_S*/
typedef struct tagDHCPS_ANALYZEDPACKET
{
    ULONG        ulRequestedAddr;      /*请求的ip地址*/
    USHORT      usPacketLength;       /*数据包长度*/
    UCHAR        ucPacketType;          /*数据包类型*/
    UCHAR        ucHtype;                 /* 用户硬件类型*/

    ULONG        ulXid;                       /* Transaction ID */
    USHORT      usFlags;                  /* Flag bits */
    USHORT      usMaxDhcpSize;     /*最大的包的长度 */

    ULONG        ulCiaddr;                 /* Client IP address (if already in use) */
    ULONG        ulGiaddr;                 /* DHCP relay agent IP address */
    UCHAR        pucChaddr [DHCPS_CHADDR_LEN];       /* Client hardware address */
    ULONG        ulYiaddr;                 /* Client IP address */
    ULONG        ulServerId;             /* 服务器的IP地址 */
    UCHAR        aucParaReqList[256];   /*1~254, 最多保存254个*/
    UCHAR        ucParaReqLen;
    UCHAR        ucOptionOverload;  /*字段 overload标志*/
    UCHAR       ucRapidCommitFlag;
    UCHAR       aucRev[1];
}DHCPS_ANALYZEDPACKET_S;

/*租约分配信息结构DHCPS_LEASE_S*/
typedef struct tagDHCPS_LEASE
{
    DHCPS_ANALYZEDPACKET_S  *pstAnalyzedPacket;       /*对应的原始报文的解析信息*/
    ULONG                   ulAddr;                   /*lease的ipv4地址*/
    ULONG                   ulIndex;                  /*租约的索引也是用户的上下文索引*/

    UCHAR                   ucPmipFlag;               /*S5S8接口的协议标志  0 gtp  1 pmip*/
    UCHAR                   ucRole;                   /*增加角色*/
    UCHAR                   ucLeaseState:4;           /*表明LEASE的状态 */
    UCHAR                   ucLeaseTimerOP:3;         /*通知备板租约定时器操作标志:0表示无效;1表示启动;2表示删除;3表示先删除后启动*/
    UCHAR                   ucUsed:1;                 /*使用标记*/
    UCHAR                   ucUserNumFlag:1;          /*预留字段*/
    UCHAR                   ucFirstRequestMsgFlag:1;  /*直接发送Request消息的标志位*/
    UCHAR                   ucReserveBit:6;
#ifdef __LINUX_PLATFORM__
    UCHAR                   aucReserve[4];
#endif
}DHCPS_LEASE_S;

typedef struct tagDHCP
{
    UCHAR       ucOp; /*1=请求；2=应答*/
    UCHAR       ucHtype; /*client的硬件地址类型:1=Ethernet*/
    UCHAR       ucHlen; /*client的硬件地址长度:Ethernet=6*/
    UCHAR       ucHops;
    ULONG       ulXid;
    USHORT      usSecs;
    USHORT      usFlag;
    ULONG       ulCiaddr;
    ULONG       ulYiaddr; /*Server分配给client的IP地址*/
    ULONG       ulSiaddr;
    ULONG       ulGiaddr; /*网关地址*/
    UCHAR       szChaddr[DHCPS_CHADDR_LEN];/*client的硬件地址*/
    CHAR        szSname[DHCPS_SNAME_LEN];
    CHAR        szFile[DHCPS_FILE_LEN];
}VOS_PACKED DHCP_S;

/*DHCPS和USM接口的数据结构类型*/
typedef struct tagDHCPS_USM_MSG_S
{
    ULONG ulMsgType;                    /*消息类型*/
    ULONG ulPDPContextIndex;     /*PDP上下文的索引就是租约的索引*/
    ULONG ulAddress;                    /*IP地址*/
} DHCPS_USM_MSG_S;

/***************************************************************/
/**************         DHCPV6 消息结构体         ***************/
/***************************************************************/

/*信令和全部扩展定义 1字节对齐*/
#pragma pack(1)
/* DHCPV6消息体定义 */
typedef struct tagDHCPV6C_MSG_S
{
    ULONG  ulMsgTypeBit8:8;  /* 消息类型 */
    ULONG  ulTransIdBit24:24; /* transaction ID */
    UCHAR  ucData[0];    /* options (variable) */
}DHCPV6C_MSG_S;
#pragma pack()

/*******************************************************************************************************/
/********************                        全局变量                           ************************/
/*******************************************************************************************************/

extern ULONG g_ulDhcpDebug;
extern ULONG g_ulDHCPSUSMQueId;
extern ULONG g_ulDhcpServerTaskId ;

/*******************************************************************************************************/
/********************                        函数声明                           ************************/
/*******************************************************************************************************/
extern ULONG DHCPC_BackupProc( char **ppbuff, UCHAR ucIpType, ULONG ulTEIDC);
extern ULONG DHCPC_BKRestoreProc( char **ppbuff, UCHAR ucIpType, ULONG ulTEIDC );
//extern ULONG DHCPC_BKDeleteProc( UCHAR ucIpType, ULONG ulTEIDC, UCHAR ucUser, ULONG ulPDPIndex );

#endif /* end of __DHCP_SPU_API_H__ */
