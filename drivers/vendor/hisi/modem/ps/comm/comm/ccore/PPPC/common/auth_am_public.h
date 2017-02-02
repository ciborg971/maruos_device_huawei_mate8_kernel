#ifndef _AUTH_AM_PUBLIC_H_H_H_
#define _AUTH_AM_PUBLIC_H_H_H_

#include "a11_ip_public.h"

#define BUFF_2048BYTE              2048
#define AAA_PPPC_AUTH_EVENTBIT              0x1<<4


#define AAA_L2TP_LNS_NUM 2
#define RD_TUNNEL_STR_MAX_LENG 32
#define RD_FRAMED_POOL_MAX_LENG 31

/* ���¶���AAAģ���еĴ���ԭ��ֵ��������g_RDA_ulErrCode */
#define RDA_SUCCESS        0         /* �ɹ� */
#define RDA_FAIL           1         /* ʧ�� */
#define RDA_UNKNOW_ERR     3         /* ���̳�����Ӧ�÷����ĵط�ʹ�õķ���ֵ */
#define RDA_AUTH_FAIL      4
#define RDA_CREAT_PACKET_FAIL              20   /* �߼�������ʧ�� */
#define RDA_GET_NAS_IP_FAIL                21   /* �õ�NAS IPʧ�� */
#define RDA_NO_MEMORY                      22   /* û���ڴ�       */

#define RDA_DNS_CFG_LOCAL     0
#define RDA_DNS_CFG_RADIUS    1
#define RDA_DNS_CFG_DHCP     2

/*  ��PPPC�����Ϣ����  */
#define    PPPC_AAA_CREAT_REQ                0    /* ��Ȩ���� */
#define    AAA_PPPC_CREAT_RSP                1    /* ��Ȩ��Ӧ */

/*  ��ȨӦ��ԭ��ֵ  */
#define  AAA_AUTH_SUCCESS           0  /* ��Ȩ�ɹ� */
#define  AAA_AUTH_FAIL              1  /* ��Ȩ�ܾ� */
#define  AAA_AUTH_SRV_ERR           2  /* ���������ϻ��������ͨ���쳣 */
#define  AAA_AUTH_CLT_ERR           3  /* RDAģ������Դ�ľ����쳣 */
#define  AAA_AUTH_MSG_FMT_ERR       4  /* ��Ϣ��ʽ���� */
#define  AAA_AUTH_IP_ERR            5  /* IP��ַ�������� */
#define  AAA_POD_DELETE            6  /* PODȥ�� */
#define NAI_NAME_LEN            63/* Modified by zhudaoming 62333 at 2007-12-05 GGSN9811V9R7C01B02 for L2TP/PPP V9��ֲ */
#define RD_FRAMED_INTERFACE_ID_LEN  8
#define RD_FRAMED_IPV6_PREFIX_LEN   16
#define RD_FRAMED_IPV6_PREFIX_BIT_LEN   64
#define HSGW_MAX_CLASS_LEN               128

#define NEMC_AAA_BASE    0xa500

/*�����й�MipAgent�ı��λ*/
#define AAA_MIPAGENT_FLAGBIT_S  0x80
#define AAA_MIPAGENT_FLAGBIT_D  0x20
#define AAA_MIPAGENT_FLAGBIT_R  0x04
#define AAA_MIPAGENT_FLAGBIT_T  0x02
#define AAA_MIPAGENT_FLAGBIT_X  0x01

#define AAA_MIPAGENT_FLAGBIT_ALL  0x6f
#define AAA_TELE_MIPAGENT_FLAGBIT_ALL  0x49

#define RD_HW_MIPAGENT_MNHA_SECRET_MAXLEN   18
#define RD_MIPV6AGENT_MNHA_SECRET_LEN 32

/*�����û�����*/
#define FA_USERTYPE_SIP         0
#define FA_USERTYPE_MIP         1
#define FA_USERTYPE_MIPAGENT    2

#define RD_MIPAGENT_USERTYPE_BIT 0x01
#define RD_MIPAGENT_FLAGS_BIT 0x02
#define RD_MIPAGENT_LIFETIME_BIT 0x04
#define RD_MIPAGENT_HAADDR_BIT 0x08
#define RD_MIPAGENT_HOMEADDR_BIT 0x10
#define RD_MIPAGENT_SPI_BIT 0x20
#define RD_MIPAGENT_SECRET_BIT 0x40



typedef enum
{
    A11_NO_SEND = 0,

    A11_FIRST_TIME,

    A11_SECOND_TIME,

    A11_PPP_RENEGO

}A10_TBL_SEND_TIME_E;     /* A10���ʹ�������Ҫ�����η��ͣ�*/

enum AAA_MsgCode
{
    NEMC_AAA_DUMMY = NEMC_AAA_BASE,
    NEMC_AAA_AUTH_GTPC_REQ,             /* GTPC��Ȩ������Ϣ 0xf201*/
    NEMC_AAA_GTPC_DEL_REQ,              /* AAA����ȥ����Ϣ  0xf203*/
    NEMC_AAA_PPPC_AUTH_REQ,             /* PPPC��Ȩ������Ϣ 0xf204*/
    NEMC_AAA_SERVER_TO_AAA,           /* Server���͸�AAA����Ϣ*/
    AAA_GET_SERVER_STATUS
};

typedef struct
{
    ULONG ulIpQos;
    ULONG ulSessionTimeOut;
    ULONG ulAAAindex;
    ULONG ulInputPeakRate;      /* ���з�ֵ����, ��λΪbps*/
    ULONG ulOutputPeakRate;     /* ���з�ֵ����, ��λΪbps*/
    ULONG ulGuarantBitRateUp;   /* PDSN�û����б�֤���� (bps)*/
    ULONG ulGuarantBitRateDown; /* PDSN�û����б�֤����(bps) */
    UCHAR ucRateFlag;
    UCHAR ucPreparedFlag;
    UCHAR ucResv[2];
    /* ucRateFlag��4λ��־��������Щ������Ϣ��0��ʾû�У�1��ʾ�յ�����
    0000***1                ��0λ��ʾ�Ƿ��յ�ulInputPeakRate
    0000**1*                ��1λ��ʾ�Ƿ��յ�ulOutputPeakRate
    0000*1**                ��2λ��ʾ�Ƿ��յ�ulGuarantBitRateUp
    00001***                ��3λ��ʾ�Ƿ��յ�ulGuarantBitRateDown */
}VOS_PACKED QOS_ACCOUNT_INFOR;


typedef struct tagMIPAGENT_SHARESECRET_S
{
    UCHAR ucLen;
    UCHAR ucSecret[RD_HW_MIPAGENT_MNHA_SECRET_MAXLEN];  /* ������� */
	UCHAR ucResv;      /*zhaoxu00140270*/
} MIPAGENT_SHARESECRET_S;




/*MIP Agent�������Ե��ݴ�ṹ*/
typedef struct tagRD_MIPAGENT_VSA_S
{
    UCHAR                  ucVsaFlag;
    UCHAR                  ucCdmaUserType;/*0-SIP, 1---MIP, 2---MIP Agent*/
    USHORT                 usMipAgentLifetime;   /* LNS��ַ */
    ULONG                  ulMipAgentHaAddr;
    ULONG                  ulMipAgentHomeAddr;
    ULONG                  ulMipAgentSpi;
    MIPAGENT_SHARESECRET_S stMipAgentSecret;  /* ������� */
    UCHAR                  ucMipAgentFlag;
    UCHAR                  ucResv[3];
} RD_MIPAGENT_VSA_S;


#define AAA_AUTHRSP_S AAA_PPPC_AUTH_RSP_S



#define A11_USER_PROFILE_NAME_LENGTH 64

/* ��Ȩ��Ӧ */
typedef struct tagAaaAuthRspMsg
{
    MSG_HDR_S stNeMsgHdr;             /* NE80ͷ */
    ULONG ulMsgType;                /* ��Ϣ���� */
    ULONG ulSDBIndex;               /* context���� ��SDB���� */

    UCHAR ucStcValue;

    UCHAR ucResv;
    UCHAR ucResult;                 /* ��Ȩ��� */
    UCHAR ucUsernameLen;            /* �û������� */
    UCHAR ucUsername[NAI_NAME_LEN+1]; /* �û��� */
    QOS_ACCOUNT_INFOR stQosAccInfo; /* �Ʒ���Ϣ */
    ULONG ulIdleTimeout;            /* �Ự��ʱʱ�� */
    ULONG ulIPMTU;                  /* MTU���� */
    ULONG ulIp;                     /* IP��ַ */
    ULONG ulIpMask;                 /* IP��ַ�������� */
    ULONG ulPIMARY_DNS_SERVER;      /* ��DNS SERVER */
    ULONG ulSECOND_DNS_SERVER;      /* ��DNS SERVER */
    ULONG ulAlwaysOn;               /*r002*/
    ULONG ulMNAAAFlag;
    ULONG ulAcctInterimInterval;
     /* L2TP */
    USHORT usTunnelType[AAA_L2TP_LNS_NUM];                 /* ������ͣ�Ŀǰֻ֧��L2TP */
    USHORT usTunnelMediaType[AAA_L2TP_LNS_NUM];            /* ���������ͣ�Ŀǰֻ֧��IP */
    ULONG  ulTunnelServer[AAA_L2TP_LNS_NUM];                   /* LNS��ַ */
    ULONG  ulTunnelPreference[AAA_L2TP_LNS_NUM];
    UCHAR  ucTunnelClientAuthId[AAA_L2TP_LNS_NUM][RD_TUNNEL_STR_MAX_LENG];   /* LAC�� */
    UCHAR  ucTunnelServerAuthId[AAA_L2TP_LNS_NUM][RD_TUNNEL_STR_MAX_LENG];  /* LNS�� */
    UCHAR  ucTunnelPrivateGroupId[AAA_L2TP_LNS_NUM][RD_TUNNEL_STR_MAX_LENG];          /* ���GroupID */
    UCHAR  ucTunnelAssignId[AAA_L2TP_LNS_NUM][RD_TUNNEL_STR_MAX_LENG];         /* ���ID */
    UCHAR  ucPassword[AAA_L2TP_LNS_NUM][RD_TUNNEL_STR_MAX_LENG+1];   /* ������� */
    UCHAR ucAAANotReturnIP;
    UCHAR ucRes;

    UCHAR  ucFramedPool[RD_FRAMED_POOL_MAX_LENG+1];  /* AAA ���صĵ�ַ����framed-pool */
    UCHAR ucReplyMsg[NAI_NAME_LEN+1];

    UCHAR ucNaiMsid[NAI_NAME_LEN+1];
    /* Added start by zhangxiujuan 60016360 at 2006-07-06 V800R005C01B010 for MIP Agent */
    UCHAR  ucCdmaUserType;                /*0-SIP, 1---MIP, 2---MIP Agent*/
    UCHAR  ucMipAgentFlag;
    USHORT usMipAgentLifetime;
    ULONG  ulMipAgentHaAddr;
    ULONG  ulMipAgentHomeAddr;
    ULONG  ulMipAgentSpi;                       /* PMIPv4�û���HA�䰲ȫ����SPI */
    ULONG  ulPmipV6Spi;                         /* PMIPv6�û���LMA�䰲ȫ����SPI */

    MIPAGENT_SHARESECRET_S stMipAgentSecret;                   /* PMIPv4��ȫ���� */
    UCHAR aucPmipV6Secret[RD_MIPV6AGENT_MNHA_SECRET_LEN];      /* PMIPv6��ȫ���� */
    UCHAR ucMdn[MDN_MAX_LEN+1];
    UCHAR ucResv3;
    USHORT  bulIpQosFlag : 1,                  /* IP Qos */
            bulInputPeakRateFlag : 1,  /*���з�ֵ���ʣ� ��λΪbps*/
            bulOutputPeakRateFlag : 1, /*���з�ֵ���ʣ� ��λΪbps*/
            bulGuarantBitRateUpFlag : 1, /*PDSN�û����б�֤���� (bps)*/
            bulGuarantBitRateDownFlag : 1, /* PDSN�û����б�֤����(bps) */
            bulAllowed_AB_BETFlag : 1, /*bps*/
            bulMaxConnectionFlag : 1,
            bucRateFlagFlag : 1,
            bucAllowed_PTFTsFlag : 1,  /* Allowed Persistent TFTs */
            bucMaxPerFlowPriorityforUserFlag : 1,        /* Maximum Per Flow Priority for the User  */
            bucInterUserPriorityFlag : 1,                /* Inter-User Priority */
            bstA11SOProfileFlag : 1,
            bstAuthFlowProfileIDFlag : 1,     /* Authorized Flow Profile IDs for the User */
            bstAllowedDSCPMarkingFlag : 1; /* Allowed Differentiated Services Marking */

    A11_QOS_INFO_S stA11QoS;
    UCHAR szUserProfileName[A11_USER_PROFILE_NAME_LENGTH + 1]; /*User Profile���Ƶ��ַ���*/
    UCHAR ucResv4[3];

    UCHAR aucVpnName[RD_HW_VPN_NAME_LEN_MAX + 1]; /* vpn name */
    UCHAR ucFilterID;
    UCHAR ucIPType;
    UCHAR ucIPTypeFlag; /* ���������Ƿ�Я����RD_3GPP2_IP_SERVICES_AUTHORIZED���ԣ�1��Я����0��δЯ�� */
    UCHAR ucActiveStopIndication:1;
    UCHAR ucUserClassAAAFlag:1;
    UCHAR ucResrved:6;
/* Added end by zhangxiujuan 60016360 at 2006-07-06 V800R005C01B010 for MIP Agent */
    UCHAR ucFramedInterfaceID[RD_FRAMED_INTERFACE_ID_LEN];
    UCHAR ucFramedIPV6Pool[RD_FRAMED_POOL_MAX_LENG + 1];
    UCHAR ucFramedIPV6Prefix[RD_FRAMED_IPV6_PREFIX_LEN];
    UCHAR ucLmaAddr[RD_FRAMED_IPV6_PREFIX_LEN];         /* PMIPv6 LMA��ַ */
    ULONG ulIpv6Mask;                     //��չ�ֶ�
    in6_addr stPriDNSIP;
    in6_addr stSecDNSIP;

}AAA_PPPC_AUTH_RSP_S;

#define CHARGE_RULE_BASE_NAME_MAX_LEN  32

/* COA_USM��Ϣ���Խṹ */
typedef struct tagCOA_UPDATE_S
{
    A11_SQOS_DSCP_S stAllowedDSCPMarking;
    ULONG ulAllowed_AB_BET;

    UCHAR aucChargeRuleName[CHARGE_RULE_BASE_NAME_MAX_LEN];
    UCHAR ucInterUserPriority;
    UCHAR ucFilterID;

    UCHAR bucAllowed_AB_BETFlag : 1;
    UCHAR bucAllowedDSCPMarkingFlag : 1;
    UCHAR bucInterUserPriorityFlag : 1;
    UCHAR bucFilterIDFlag : 1;
    UCHAR baucChargeRuleNameFlag : 1;

} COA_UPDATE_S;

extern ULONG  RDA_GetApnDNSCfg(USHORT usApnIndex, DOMAINDNS_S *pstApn);
extern ULONG  RDA_GetApnDNSIpv6Cfg(USHORT usApnIndex, DOMAINDNS_S *pstApn);
extern ULONG RDA_CheckRadiusGroupForVirtualDomain(USHORT usDomainIndex, USHORT usGroupId, UCHAR *pucStatus);
extern VOID hmac_md5(UCHAR *text, int text_len, UCHAR *key, int key_len, UCHAR *digest);
extern ULONG AUTH_GetVpnNameByIdx(ULONG ulVpnIndex, UCHAR *uzVpnName);
extern ULONG HSGW_AUTHOmInitial(VOID);
#endif


