

#ifndef __HSGW_PMIPV6_AM_PUBLIC_H__
#define  __HSGW_PMIPV6_AM_PUBLIC_H__

/*******************************************************************************************************/
/********************                          �궨��                           ************************/
/*******************************************************************************************************/

#define PMIPV6_MAX_V6ADDR_LEN 16   /* V6��ַ��󳤶� */
#define PMIPV6_MAX_PREFIX_LEN 8    /* V6��ַǰ׺��󳤶� */
#define PMIPV6_MAX_V4ADDR_LEN 4    /* V4��ַ��󳤶� */
#define PMIPV6_MAX_MNID_LEN 63     /* MNID��󳤶� */
#define PMIPV6_MAX_MSISDN_LEN 8     /* MSISDN��󳤶� */
#define PMIPV6_MAX_3GPP_PCO_VALUE_TOTAL_LEN     253   /* PCO��󳤶�253 */
#define PMIPV6_MAX_3GPP_PCO1_VALUE_LEN     248   /* PCO��󳤶�248 �ο�29282Э�� */
#define PMIPV6_MAX_3GPP_PCO1_EXTERN_LEN     254   
#define PMIPV6_MAX_3GPP_PCO2_VALUE_LEN     5   /* �ڶ���PCO��չ��󳤶� */
#define PMIPV6_MAX_3GPP_PCO2_EXTERN_LEN     11   
#define PMIPV6_MAX_KEY_LEN 32 /* PDSN�û����authentication��չ */

/* ipv4��װʱPMIPV6�˿ںŶ��� */
#define PMIPV6_IPV4_SRC_PORT    5436
#define PMIPV6_IPV4_DST_PORT    5436

/* ��Ϣ���泤�� */
#define PMIPV6_REV_MSG_MAXLEN 4096  /* ������Ϣ��󳤶� */
#define PMIPV6_SEND_MSG_MAXLEN 1024  /* ������Ϣ��󳤶� PCO 253�ֽ� */
#define PMIPV6_CHECKSUM_MAXLEN PMIPV6_REV_MSG_MAXLEN + 40  /* ������Ϣ��󳤶� */

/* PMIPV6��Ϣͷ���� */
#define PMIPV6_NEXTHDR_MH    135
#define PMIPV6_NEXTHDR_NONEXTHEADER    59

/* PMIPV6�¼�λ */
#define PMIPV6_PBA_EVENT             0x01
#define PMIPV6_BRI_EVENT             0x02
#define PMIPV6_HEART_EVENT           0x04
#define PMIPV6_PDN_EVENT            0x08
#define PMIPV6_TIMER_EVENT          0x10
#define PMIPV6_INNER_HIGH_EVENT     0x20
#define PMIPV6_INNER_LOW_EVENT      0x40

/* �û����� */
typedef enum
{
    PMIPV6_USER_TYPE_PDSN,  /* PDSN */
    PMIPV6_USER_TYPE_HSGW,  /* HSGW */

    PMIPV6_USER_TYPE_BUTT
} PMIPV6_USER_TYPE_E;

/* ��ַ���� */
typedef enum
{
    PMIPV6_ADDR_TYPE_NONE = 0,  /* ��ַ���ͷǷ� */
    PMIPV6_ADDR_TYPE_V4 = 1,  /* V4��ջ */
    PMIPV6_ADDR_TYPE_V6 = 2,  /* V6��ջ */
    PMIPV6_ADDR_TYPE_V4V6,   /* ˫ջ */

    PMIPV6_ADDR_TYPE_BUTT
} PMIPV6_ADDR_TYPE_E;



/* PGW�ܾ��ĵ�ַ���� */
typedef enum
{
    PMIPV6_PDN_INDIC_V4 = 1,  /* V4 */
    PMIPV6_PDN_INDIC_V6,      /* V6 */

    PMIPV6_PDN_INDIC_BUTT
} PMIPV6_PDN_INDIC_E;

/* Handoff Indicator */
 typedef enum
 {
    PMIPV6_HI_RESERVED    = 0,
    PMIPV6_HI_NEW_INTER   = 1,
    PMIPV6_HI_DIFFERNT    = 2,
    PMIPV6_HI_SAME        = 3,
    PMIPV6_HI_UNKNOWN     = 4,
    PMIPV6_HI_NO_CHANGE   = 5,
    
    PMIPV6_HI_BUTT
 }PMIPV6_HI_TYPE_E;


/* PDN���͸�PMIPV6��������Ϣ��Ϣ�� */
typedef enum
{
     E_AM_PDN_PMIPV6_REG_REQ,       /* 0 ��ʼע��ʱʹ�� */
     E_AM_PDN_PMIPV6_ALLOC_IPV4_REQ,/* 1 ����V4��ջ */
     E_AM_PDN_PMIPV6_ALLOC_IPV6_REQ,/* 2 ����V6��ջ --ֻ��pdsn���� */
     E_AM_PDN_PMIPV6_REL_IPV4_REQ,  /* 3 �ͷ�V4��ջ --ֻ��pdsn���� */
     E_AM_PDN_PMIPV6_REL_IPV6_REQ,  /* 4 �ͷ�V6��ջ --ֻ��pdsn���� */
     E_AM_PDN_PMIPV6_REL_REQ,        /* 5 �ͷ��û� */
     E_AM_PDN_PMIPV6_UPDATE_WIRELESS,  /* 6 ���߲������� --ֻ��pdsn���� */
     E_AM_PDN_PMIPV6_UPDATE_VSNCP,      /* 7 PCO���� --ֻ��hsgw���� */     
     
     E_AM_PDN_PMIPV6_MSGCODE_BUTT,
} PDN_PMIPV6_MSGCODE_E;

/* PMIPV6���͸�PDN����Ϣ�� */
typedef enum
{
    /* ��Ӧ */
    E_AM_PMIPV6_PDN_REG_RSP,  
    E_AM_PMIPV6_PDN_ALLOC_IPV4_RSP,  
    E_AM_PMIPV6_PDN_ALLOC_IPV6_RSP, /* 2 ����V6��ջ --ֻ��pdsn���� */  
    E_AM_PMIPV6_PDN_UPDATE_VSNCP_RSP, /* 3 PCO������Ӧ --ֻ��hsgw���� */  

    /* ��Ҫ��װ��Ϣ�����Ϣ����ڸ���Ϣ��֮ǰ */
    E_AM_PMIPV6_PDN_REL_IPV4_RSP,  /* 4 �ͷ�V4��ջ --ֻ��pdsn���� */  
    E_AM_PMIPV6_PDN_REL_IPV6_RSP,  /* 5 �ͷ�V6��ջ --ֻ��pdsn���� */   

    /* ���� */
    E_AM_PMIPV6_PDN_REL,/* �ͷ�������ͷ���Ӧʹ��һ����Ϣ��*/
    E_AM_PMIPV6_PDN_REL_IP_REQ,/* ֪ͨPDN�ͷŵ�ջ �ͷ�������PMIPV6_PDN_MSG_S--ucbit2RelAddrTypeЯ�� */

    E_AM_PMIPV6_PDN_MSGCODE_BUTT,
} PMIPV6_PDN_MSGCODE_E;

/*******************************************************************************************************/
/********************                          �ṹ��                           ************************/
/*******************************************************************************************************/

/* ������Ϣʹ�õĵ�ַ��Ϣ */
typedef struct tagPMIPV6_IP_INFO
{
    ULONG ulMagSubId;
    ULONG ulMagIfId;    
    ULONG ulMoudleId;
    USHORT usMagVpnId;
    UCHAR ucEncapeType;
    UCHAR ucDpeId;
    ULONG ulMagIpv4Addr;    
    UCHAR aucMagIpv6Addr[PMIPV6_MAX_V6ADDR_LEN]; 
    UCHAR aucLmaAddr[PMIPV6_MAX_V6ADDR_LEN]; 
}PMIPV6_IP_INFO_S;

/* PDN���͸�PMIPV6��������Ϣ�ṹ�� */
typedef struct tagPDN_PMIPV6_REQ
{
    A11_IMSI_S stImsi;                     /* IMSI */

    ULONG ulPdnIndex;                     /* PDN���� */
    ULONG ulPmipv6Index;                  /* PMIPV6���� */

    ULONG ulLmaAddrV4;                         /* LMA-v4��ַ */
    ULONG ulHomeAddrV4;                        /* IPV4 address */

    ULONG ulUpdateMask;                          /* �������µ�����--ֻ��pdsn���� */    
    USHORT usApnIndex;                           /* ��DEA��Ϣ��ȡAPN��Ӧ������--ֻ��hsgw���� */    
    UCHAR ucDpeId;
    UCHAR ucbit2AddrType:2;                   /* 1-v4, 2-v6, 3-˫ջ PMIPV6_ADDR_TYPE_E */
    UCHAR ucbit1UserType:1;                   /* �û����� 0-HSGW,1-PDSN PMIPV6_USER_TYPE_E */
    UCHAR ucbit3HandOffFlg:3;                 /* �Ƿ���HSGW�л�--PMIPV6_HI_TYPE_E */
    UCHAR ucbit2Reserved:2;

    UCHAR aucHomeAddrV6[PMIPV6_MAX_V6ADDR_LEN];  /* IPV6 address */
    UCHAR aucLmaAddrV6[PMIPV6_MAX_V6ADDR_LEN];   /* LMA-v6��ַ */
    UCHAR aucShareKey[PMIPV6_MAX_KEY_LEN];       /* PMN-LMA */
    
    UCHAR auc3GppPco[PMIPV6_MAX_3GPP_PCO_VALUE_TOTAL_LEN];
    UCHAR uc3GppPcoLen;
    USHORT us3GppChargingChara;                 /* chargingchara Ϊ�ַ�--ֻ��hsgw���� */

    ULONG ulSpi;                                  /* ֻ��pdsn���� */
    UCHAR aucRes4[4];
} PDN_PMIPV6_REQ_S;

/* PMIPV6���͸�PDN����Ϣ�ṹ�� */
typedef struct tagPMIPV6_PDN_MSG
{
    ULONG ulPdnIndex;                /* PDN���� */
    ULONG ulPmipv6Index;            /* Pmipv6���� */    
    ULONG ulResultCode;             /* ��Ϣ�� 0-success */
    UCHAR aucReserved[4];

    UCHAR ucbit2PdnIndicator :2;   /* 1-v4,2-v6 PMIPV6_PDN_INDIC_E--ֻ��hsgw���� */
    UCHAR ucbit1DelayFlg :1;       /* V4�ӳٷ����־--ֻ��hsgw���� */
    UCHAR ucbit1SigEncapeType:1;   /* �����װ��ʽ 0-v4,1-v6 PMIPV6_SIG_ENCAPE_TYPE_E*/
    UCHAR ucbit2RelAddrType :2;    /* �ͷŵ�ջ���� PMIPV6_ADDR_TYPE_E */
    UCHAR ucbit2Resved :2;    
    UCHAR ucPdnIndicatorCause;  /* PDN Type Indication-causeֵ--ֻ��hsgw���� */
    UCHAR ucPmipv6ErrCode;      /* 3GPP Specific PMIPv6 Error Code--ֻ��hsgw����  */
    UCHAR ucReserved;
    
    ULONG ulHomeAddrV4;                             /*IPV4 address */
    ULONG ulRouterAddrV4;                           /*router address--ֻ��hsgw���� */
    ULONG ulPriDnsIp;                               /*IPV4 Primary DNS--ֻ��pdsn���� */
    ULONG ulSecDnsIp;                               /*IPV4 Secondary DNS--ֻ��pdsn���� */

    UCHAR aucLmaAddr[PMIPV6_MAX_V6ADDR_LEN];        /*LMA address--ֻ��pdsn����(CSN����)*/    
    UCHAR aucHomeAddrV6[PMIPV6_MAX_V6ADDR_LEN];     /*IPV6 address*/
    UCHAR aucLinkLocalAddr[PMIPV6_MAX_V6ADDR_LEN];  /*Link local address*/
    UCHAR aucPriV6DnsIp[PMIPV6_MAX_V6ADDR_LEN];     /*IPV6 Primary DNS--ֻ��pdsn���� */
    UCHAR aucSecV6DnsIp[PMIPV6_MAX_V6ADDR_LEN];     /*IPV6 Secondary DNS--ֻ��pdsn���� */

    ULONG ulGreKey;                                  /* ֻ��hsgw���� */
    ULONG ulChargingId;                              /* ֻ��hsgw���� */
    
    UCHAR auc3GppPco[PMIPV6_MAX_3GPP_PCO_VALUE_TOTAL_LEN]; /* ֻ��hsgw���� */
    UCHAR uc3GppPcoLen;                              /* ֻ��hsgw���� */
    USHORT usVpn6Index;
}PMIPV6_PDN_MSG_S;

/*******************************************************************************************************/
/********************                          ��������                           ************************/
/*******************************************************************************************************/
extern ULONG PMIPV6_MsgParse(UCHAR *pucMsg, ULONG ulMsgLen, UCHAR *pucImsi, UCHAR *pucUserType);
extern USHORT PMIPV6_GetSubIdByEncapeType(UCHAR ucSigEncapeType, UCHAR ucUserType);
extern ULONG PMIPV6_GetContexSize(VOID);
extern ULONG PMIPV6_CreatProcess(PDN_PMIPV6_REQ_S *pstPdnReqMsg); 
extern ULONG PMIPV6_CheckMnIdByImsi(UCHAR *pucMnId, A11_IMSI_S stImsi);
extern ULONG PMIPV6_GetImsiFromMnId(UCHAR *pucMnId, ULONG ulMnIdLen, UCHAR aucImsi[]); 
extern ULONG PMIPV6_CheckImsiFromMnIdForUsm(UCHAR aucImsi[]); 
extern ULONG PMIPV6_GetHsgwRpContextByImsi(UCHAR **ppucRpContext, A11_IMSI_S *pstImsi);
extern VOS_VOID PMIPV6_GetDataEncapeValidFlg(UCHAR *pucChecksumFlg, UCHAR *pucSequenceFlg);
extern ULONG PMIPV6_GetIpInfoByPdnIndex(PMIPV6_IP_INFO_S *pstPmipv6IpInfo, ULONG ulPdnIndex);
extern ULONG PHGW_SendMsgToLma(UCHAR *pucMsg, ULONG ulMsgLen, ULONG ulPdnIndex);
extern ULONG PMIPV6_GetS2AIntfType(VOID);
extern ULONG PMIPV6_GetIndexByMcc(A11_IMSI_S stImsi);
extern ULONG PMIPV6_BackupMasterCreUpdPmipv6Proc(ULONG ulPmipv6Index, ULONG ulOperType, 
                                               UCHAR **ppucCurrent, ULONG *pulEncapLen);
extern ULONG PMIPV6_BackupSlaveCreUpdPmipv6Proc(UCHAR *pucCurrent);

extern VOID PMIPV6_FreeResBeforeFreePdnRes(ULONG ulMipIndex);
extern ULONG Pmipv6_BackupSmoothPmipv6Context(PDN_CONTEXT_S *pstPdnContext);
extern ULONG PMIPV6_GetRpIndexByPmipv6Index(ULONG ulPmipv6Index, ULONG *pulRpIndex);
extern ULONG PMIPV6_CheckPfTable(ULONG ulPmipv6Index);
extern ULONG PMIPV6_ResCheckByPmipv6Index(ULONG ulPmipv6Index);
extern VOS_VOID PMIPV6_InitPerfCounterAddr(VOS_VOID);


#endif
