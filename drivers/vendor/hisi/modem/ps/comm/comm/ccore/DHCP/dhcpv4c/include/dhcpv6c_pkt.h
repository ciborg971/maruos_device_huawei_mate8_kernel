
#ifndef __DHCPV6C_PKT_H__
#define __DHCPV6C_PKT_H__

#ifdef    __cplusplus
extern "C" {
#endif


/*******************************************************************************************************/
/********************                          �궨��                           ************************/
/*******************************************************************************************************/

#define DHCPV6C_SEND_MSG_MAXLEN 1024  /* ������Ϣ��󳤶� */

#define DHCPV6C_HUNDRED 100

/* transaction-id��� */
/* DE�壺TIDΪtoken(13bit)+sc id(2bit)+sequence(9bit)*/
/* F�壺 TIDΪtoken(14bit)+Sequence(10bit)*/
#define DHCPV6C_MAX_SEQUENCE_ID_DE       0x1ff  /* DE�� sequenceNum ���ID */
#define DHCPV6C_MAX_SEQUENCE_ID_F       0x3ff   /* F�� sequenceNum ���ID */
#define DHCPV6C_TOKEN_BIT11       11   /* DE�� TOKENռ�ñ�����--13BIT */
#define DHCPV6C_TOKEN_BIT10       10   /* F�� TOKENռ�ñ�����--14BIT */
#define DHCPV6C_SCID_BIT9       9   /* DE�� SCռ�ñ�����--2BIT */
#define DHCPV6C_MAX_SEQUENCE_NUM_DE       512  /* DE�� sequenceNum ����� */
#define DHCPV6C_MAX_SEQUENCE_NUM_F       1024  /* F�� sequenceNum ����� */
#define DHCPV6C_MAX_SEQUENCE_NUM      g_usDhcpv6cMaxSeqNum 
#define DHCPV6C_MAX_DNS_NUM      2 

#define DHCPV6C_GET_MSG_TYPE(pucDhcpv6Msg) (((DHCPV6C_MSG_S *)(pucDhcpv6Msg))->ulMsgTypeBit8)

/* ����teidc��ȡtoken */
#ifdef __LINUX_PLATFORM__
#define DHCPC_GET_TOKEN_BY_TEIDC(teid) ((teid) >> 18)
#else
#define DHCPC_GET_TOKEN_BY_TEIDC(teid) ((teid) >> 19)
#endif

/* ����token��ȡteidc */
#define DHCPC_GET_TEIDC_BY_TOKEN(token) ((token) << 19)

/* DUID-type ����1,2,3 */
#define DHCPC_CHECK_DUIDTYPE_INCORRECT(usDuidType) \
(                                                 \
    ((DHCPV6_MSG_OPTION_DUID_LLT != (usDuidType)) \
    && (DHCPV6_MSG_OPTION_DUID_EN != (usDuidType)) \
    && (DHCPV6_MSG_OPTION_DUID_LL != (usDuidType))) ? \
    VOS_TRUE : VOS_FALSE \
)

#define DHCPV6C_SET_V6ADDR_NULL(aulV6Addr) \
{ \
    (aulV6Addr)[0] = DHCP_INVALID_ULONG; \
    (aulV6Addr)[1] = DHCP_INVALID_ULONG; \
    (aulV6Addr)[2] = DHCP_INVALID_ULONG; \
    (aulV6Addr)[3] = DHCP_INVALID_ULONG; \
}

/* V6��ַ������  */
#define DHCPC_CHECK_V6ADDR_IS_NULL(aulV6Addr) \
(                                                 \
    ((DHCP_INVALID_ULONG == ((aulV6Addr)[0])) \
    && (DHCP_INVALID_ULONG == ((aulV6Addr)[1])) \
    && (DHCP_INVALID_ULONG == ((aulV6Addr)[2])) \
    && (DHCP_INVALID_ULONG == ((aulV6Addr)[3]))) ? \
    VOS_TRUE : VOS_FALSE \
)

/*******************************************************************************************************/
/********************                        �ṹ����                           ************************/
/*******************************************************************************************************/

/***************************************************************/
/**************         DHCPV6 Option�ṹ��      ***************/
/***************************************************************/

/*�����ȫ����չ���� 1�ֽڶ���*/
#pragma pack(1)

/* ����TLV��ʽ��OPTION */
typedef struct tagDHCPV6C_TLV_OPTION_S
{
    USHORT usType;    /* Type */
    USHORT usLen;     /* Length */
    UCHAR ucData[0];  /* value */
}DHCPV6C_TLV_OPTION_S;

/* DUID-LLT */
typedef struct tagDHCPV6C_DUID_LLT_OPTION_S
{
    USHORT usType;    /* Type */
    USHORT usHardWare;     /* HardWare */
    ULONG  ulTime;     /* Time */
    UCHAR ucData[0];  /* value */
}DHCPV6C_DUID_LLT_OPTION_S;

/* DUID-EN */
typedef struct tagDHCPV6C_DUID_EN_OPTION_S
{
    USHORT usType;    /* Type */
    ULONG  ulEnterpriseNum;     /* EnterpriseNum */
    UCHAR ucData[0];  /* value */
}DHCPV6C_DUID_EN_OPTION_S;

/* DUID-LL */
typedef struct tagDHCPV6C_DUID_LL_OPTION_S
{
    USHORT usType;    /* Type */
    USHORT  usHardWare;     /* HardWare */
    UCHAR ucData[0];  /* value */
}DHCPV6C_DUID_LL_OPTION_S;

/* IANA_OPTION */
typedef struct tagDHCPV6C_IANA_OPTION_S
{
    USHORT usType;    /* Type */
    USHORT usLen;     /* Length */
    ULONG ulId;     /* IA-ID */
    ULONG ulT1;       /* t1 */
    ULONG ulT2;       /* t2 */
    UCHAR ucData[0];  /* IA_NA-options */
}DHCPV6C_IANA_OPTION_S;

/* IAADDR_OPTION */
typedef struct tagDHCPV6C_IAADDR_OPTION_S
{
    USHORT usType;             /* Type */
    USHORT usLen;              /* Length */
    in6_addr stIpv6Addr;      /* IPv6 address */
    ULONG ulPreTime;          /* preferred-lifetime */
    ULONG ulValidTime;        /* valid-lifetime */
    UCHAR ucData[0];  /* IA_NA-options */
}DHCPV6C_IAADDR_OPTION_S;

/* STATUS_CODE_OPTION */
typedef struct tagDHCPV6C_STATUS_CODE_OPTION_S
{
    USHORT usType;      /* Type */
    USHORT usLen;       /* Length */
    USHORT usCode;      /* status-code */
    UCHAR ucData[0];   /* status-message */
}DHCPV6C_STATUS_CODE_OPTION_S;

#pragma pack()

/* DHCPV6C��Ϣoption���� */
typedef struct tagDHCPV6C_OPTION_INFO_S
{
    DHCPV6C_TLV_OPTION_S *pstClientIdOption;
    DHCPV6C_DUID_EN_OPTION_S *pstCiDuidEn;    
    DHCPV6C_TLV_OPTION_S *pstServerIdOption;
    DHCPV6C_IANA_OPTION_S *pstIaNaOption;
    DHCPV6C_IAADDR_OPTION_S *pstIaAddrOption;
    DHCPV6C_TLV_OPTION_S *pstDnsOption; /* DNS */
    DHCPV6C_STATUS_CODE_OPTION_S *pstMsgStatusCodeOption; /* ��Ϣ��Я���� */
    DHCPV6C_STATUS_CODE_OPTION_S *pstIaNaStatusCodeOption; /* IA-NA-option��Я���� */
    DHCPV6C_STATUS_CODE_OPTION_S *pstIaAddrStatusCodeOption; /* IA-addr-option��Я���� */   
    UCHAR ucMainDnsFlg;
    UCHAR ucSecdDnsFlg;
    UCHAR aucRev6[6];    
 } DHCPV6C_OPTION_INFO_S; 

/* DHCPV6C��Ϣ */
typedef struct tagDHCPV6C_MSG_INFO_S
{    
    UCHAR *pucMsg;          /* ��Ϣ��ָ�� */
    ULONG ulMsgLen;        /* ��Ϣ���� */
    USHORT usSeqNum;    
    UCHAR aucResed[2];        
    DHCPV6C_OPTION_INFO_S stDhcpv6cOptionInfo;  /* ��Ϣ��չͷ��Ϣ */
} DHCPV6C_MSG_INFO_S;

/********************************************************************/
/************************�������************************************/
/********************************************************************/
/* SequenceNum������Դ����ṹ */
typedef struct tagDHCPV6C_SEQNUM_FREELINK_S
{
    USHORT* pusNextNode;                /* ����������һ���ڵ������ */
    USHORT usUsedNum;                   /* ռ�ýڵ��� */
    USHORT usFreeHead;                  /* ���нڵ�����ͷ */
    USHORT usFreeTail;                  /* ���нڵ�����β */
    USHORT usReseved;                  
}DHCPV6C_SEQNUM_FREELINK_S;

/* SequenceNum��DHCP���ƿ��Ӧ��ϵ�ṹ */
typedef struct tagDHCPV6C_SEQNUM_CONTEXT_S
{
    ULONG ulTeidc;    /* teidc */
    UCHAR ucbit2IpAddrType : 2;   /* ��ַ���� */
    UCHAR ucbit2UsedFlg : 2;      /* ʹ�ñ�� */
    UCHAR ucbit4AgeingCnt : 4;    /* �ϻ�����----������ͷ�ʱ����,��ʱ����ʱ�ۼ� */    
                                   /* ����DHCPC_AGEING_SEQNUM_MAX_CNTʱ˵��seqnum����,��Ҫ�ͷ� */
    UCHAR aucResed[3];            
}DHCPV6C_SEQNUM_CONTEXT_S;

/*******************************************************************************************************/
/********************                        ȫ�ֱ���                           ************************/
/*******************************************************************************************************/
extern UCHAR* g_pucDhcpv6cSendBuff;        /*������Ϣ����*/
extern UCHAR* g_pucDhcpv6cRevBuff;         /*������Ϣ����*/

extern USHORT g_usDhcpv6cMaxSeqNum; /* SequencNum���,DE512,F1024*/
extern DHCPV6C_SEQNUM_FREELINK_S g_stDhcpv6cSeqNumLink; /* SequencNum��������� */
extern DHCPV6C_SEQNUM_CONTEXT_S *g_pstDhcpv6cSeqContext; /*  SequenceNum��DHCP���ƿ��Ӧ��ϵ */


/*******************************************************************************************************/
/********************                        �ⲿ�ӿ�                           ************************/
/*******************************************************************************************************/

extern ULONG DHCPV6C_InitFreeLink(DHCPV6C_SEQNUM_FREELINK_S* pstFreeLink, VOS_UINT16 usTotalNum);
extern ULONG DHCPV6C_AllocSeqNum(USHORT *pusSeqNum, ULONG ulTeidc, UCHAR ucIpAddrType);
extern ULONG DHCPV6C_QuryTeidcBySeqNum(USHORT usSeqNum, ULONG *pulTeidc, UCHAR *pucIpAddrType);
extern VOID DHCPV6C_FreeSeqNum(USHORT usSeqNum);

extern USHORT LAP_IPv6GetAddrType( in6_addr *addr );
extern ULONG DHCPV6C_MsgDecode(DHCPV6C_MSG_INFO_S *pstMsgInfo);
extern ULONG DHCPV6C_CheckOption(DHCPV6C_OPTION_INFO_S *pstDhcpv6cOptionInfo,
                                      DHCPC_CTRLBLK *pstDhcpcContext);
extern ULONG DHCPV6C_SendPacket(DHCPC_CTRLBLK *pstDhcpcContext, ULONG ulDhpcv6MsgType);
extern VOID DHCPV6C_SaveOptionToContext(DHCPC_CTRLBLK *pstDhcpcContext, 
                                                 DHCPV6C_OPTION_INFO_S *pstDhcpv6Option);
extern ULONG DHCPM_GetDhcpSrvVpnByIndex(ULONG ulDhcpIndex, ULONG *pulVpnIndex);
extern ULONG DHCPC_SelectAndGetServerCfg(DHCPC_CTRLBLK *pstDhcpcContext, ULONG aulServerIp[LAP_IP_ULONG_NUM]);
extern VOID DHCPCv6_OmMsgTrc(UCHAR *pucDhcpv6Msg,DHCPC_CTRLBLK *pstDhcpcContext, UCHAR ucMsgType,ULONG ulMsgLen, UCHAR MsgDirection);
extern VOID DHCPV6C_GetSeqNumByMsg(USHORT *pusSeqNum, UCHAR *pucMsg);
#ifdef    __cplusplus
}
#endif

#endif


