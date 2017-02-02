

#ifndef __USM_API_H__
#define __USM_API_H__

#include "li_am_public.h"

extern PTM_COMPONENT_INFO_S g_stHsgwUsmCompInfo;
#define USM_SELF_CSI       g_stHsgwUsmCompInfo.ullSelfCsi
#define USM_SELF_CMPIDX    g_stHsgwUsmCompInfo.ulSelfCmpIdx
#define USM_HANDLE         g_stHsgwUsmCompInfo.ulHandle
#define USM_SELF_SGID_INOS      g_stHsgwUsmCompInfo.ullSelfSgId
#define USM_SELF_CMPID_INSG      g_stHsgwUsmCompInfo.ulSelfCmpIdxInSG

/* Diameter Auth��USM֮�����Ϣ���� */
#define USM_DIAM_AAA_REAUTHOR_REQ      1
#define DIAM_AAA_USM_REAUTHOR_RSP      2
#define DIAM_AAA_USM_REAUTHOR_NOTIFY   3

#define USM_EHRPD_SESSION_TIMEOUT_MIN             300
#define USM_EHRPD_REAUTH_TIME_AMOUNT_IN_ADVANCE   120

typedef enum
{
    USM_INNER_MSG_CODE_EXIT,  /* �ڲ�����������Ϣ */
    USM_INNER_MSG_CODE_PHASE_RESULT, /* �ڲ�����״̬�������������ģ��֪ͨ�׶������Ϣ */
    USM_INNER_MSG_CODE_PDN_RELEASE,    
    USM_INNER_MSG_CODE_PDN_RECONNECT,        
    USM_INNER_MSG_CODE_BACKUP_BATCH, 
    USM_INNER_MSG_CODE_BACKUP_SMOOTH,
    USM_INNER_MSG_DPS_CHECK,
    USM_INNER_MSG_CODE_BUTT

}USM_INNER_MSG_CODE_E;

typedef struct tagHSGW_TOKEN_STATE_S
{
    UCHAR ucLockFlag;
    UCHAR ucTerminateFlag;
    UCHAR ucRsv[2];
}HSGW_TOKEN_STATE_S;

typedef struct tagHSGW_DEA_RP_INFO_S
{
    ULONG  ulRPIndex;   //��¼���һ��ȥ���������Index
    USHORT usTokenId;    //��¼ȥ���Token id
    UCHAR  ucDeaCause;   //��¼ȥ��ԭ��
    UCHAR  ucReserved;
}HSGW_DEA_RP_INFO_S;

/* A11֪ͨUSM����������Ϣ�ṹ�� */
typedef struct
{
    A11_IMSI_S stIMSI;
    ULONG ulRelReason;       /* �û�ȥ���ԭ���� */
}USM_A112USM_NEWREG_S;


/* A11 link up�Ժ�֪ͨUSM�Ľṹ�� */
typedef struct
{
    ULONG ulRpIndex;
    ULONG ulResultCode;
    ULONG ulMsgType;
}USM_A11_LINKUP_RESULT_S;

typedef struct 
{
    ULONG ulRpIndex;
    /* LCP */
    ULONG ulMagicNum;                /* Magic-Number */
    ULONG ulAccm;
    USHORT usMtu; 
    UCHAR ucPPPMode;
    UCHAR ucReserve;
}USM_PPPC_LCPUP_USERINFO_S;      /* LCP OK��PPPC����USM���û���Ϣ�ṹ */

typedef struct
{
    ULONG ulRpIndex;
    /* IPCP */
    ULONG ulPppFlag;
    UCHAR ucPPPConFlag;  
    UCHAR ucDmpuId;
    UCHAR ucDmpuDpeId;
   /* IPV6CP */

   /* CCP */ 

}USM_PPPC_IPCPUP_USERINFO_S;    /* IPV4V6CP OK ��PPPC����USM���û���Ϣ�ṹ */


/* diam��Ȩ���� */
typedef struct tagUSMDiamAuthMsg
{
    ULONG ulMsgType;            /* ��Ϣ���� */
    ULONG ulRpIndex;            /* SDB���� */
    ULONG ulNowUTCInSec;
    USHORT usPeerID;            /* diameter aaa server ID */
    USHORT usTokenId;           /* �����ĵ�TOKEN ID */ 
    A11_IMSI_S stIMSI;
    UCHAR aucUserName[DIAM_AUTH_USERNAME_MAX_LEN + 1];
    UCHAR ucAAAType;
}USM_DIAM_AUTH_MSG_S;

typedef struct tagDiamAuthUSMMsg
{
    ULONG ulMsgType;                                                    /* ��Ϣ���� */
    ULONG ulRpIndex;                                                    /* context���� ��SDB���� */
    ULONG ulQosProfileID;                                               /* qos profile id */
    ULONG ulSessionTimeout;                                             /* session timeout */
    ULONG ulAccountInterval;                                            /* Accounting-Interim-Interval */
    ULONG ulDefaultAPNId;                                               /* default APN id */
    DIAM_AUTH_APN_INFO_S stApnInfo[DIAM_AUTH_APN_INFO_MAX_NUMBER];      /* APN CONFIGURATION */
    USHORT us3GPPCC;                               /* �Ʒ����� */ 
    UCHAR aucMdn[MDN_MAX_LEN+1];                                        /* ����MDN���� */
    UCHAR ucResult;                                                     /* ��Ȩ��� */
    UCHAR ucApnInfoNum;                                                 /* APN INFO���� */
    UCHAR aucRsv[3];
}DIAM_AUTH_USM_MSG_S;

/* PPP link up�Ժ�֪ͨUSM�Ľṹ�� */
typedef struct
{
    UCHAR *pucMsg; /* ppp�����û�������Ҫ��AAA_AUTHRSP_S����EAP��Ȩ��Ӧ�ṹ�� */
    ULONG ulRpIndex;    
    ULONG ulResultCode;
    USHORT usDomainIndex;
    USHORT usVirtualDomainIndex;    
    UCHAR  aucNAI[A11_MAX_NAI_LENGTH + 1];                /* NAI */
}USM_PPP_LINKUP_RESULT_S;

/* PMIPv6ģ��PDSNʱ��Ҫʹ�õ��ֶ�----NVSE��չ��NAI */
typedef struct tagUSM_PMIPV6_CONTEXT_DATA
{
    /* PDSN��Ҫʹ�õ���Ϣ */
    UCHAR aucNai[A11_MAX_NAI_LENGTH +1];                /* NAI */
    
    ULONG ulPcfIP;
    ULONG ulCorrelationID;
    
    UCHAR aucSubnet[A11_AIR_REC_MAX_SUBNET_LEN];      /*Subnet For HRPD d7*/
    UCHAR ucSubnetLen;
    UCHAR aucBsId[A11_MSID_LEN];
    UCHAR aucEsn[A11_AIR_REC_MAX_ESN_LEN/2];  
    
    UCHAR ucServiceOption;   
    UCHAR bBsidFlagPmipv6:1;  /* BSID�Ƿ�Я����� */
    UCHAR aucReserved3[2];

    /* HSGW��Ҫʹ�õ���Ϣ */
    GTP_MSISDN szMsisdn; /* MSISDN */
    UCHAR aucMnId[DIAM_AUTH_MNID_MAX_LENGTH + 1];    /* ��DEA��Ϣ��Mobile-Node-Identifier�ֶλ�ȡ */

    ULONG ulMagGreKey; /* HSGW */
    ULONG ulLmaGreKey;    
}USM_PMIPV6_CONTEXT_DATA_S;
typedef enum
{
    EHRPD_VSNCP_PRO_OK = 0,                 /* �������� */
    EHRPD_VSNCP_PRO_ERR = 1,                /* �쳣���� */
    EHRPD_VSNCP_PRO_COPY = 2,               /* ���洦�� */
    EHRPD_VSNCP_PRO_BUTT
}EHRPD_VSNCP_PRO_CODE_E;


typedef enum
{
    USM_STATE_INIT = 1,                 /* 1 ��ʼ״̬ */
    USM_STATE_WT_A11_SETUP,             /* 2 �ȴ�A11��·������� */
    USM_STATE_WT_PPP_SETUP,             /* 3 �ȴ�PPP��·������� */
    USM_STATE_WT_PDN_SETUP,             /* 4 �ȴ�PDN������� */
    USM_STATE_ACTIVE,                   /* 5 ����̬ */  
    USM_STATE_DIFF_HANDOFF,             /* 6 �л�̬ */ 
    USM_STATE_WT_DIAM_AUTHORIZE,        /* 7 �ȴ���ȡ��Ȩ��Ϣ */ 
    USM_STATE_WT_PPP_RELEASE,           /* 8 �ȴ�PPP��·�ͷ���� */
    USM_STATE_WT_A11_RELEASE,           /* 9 �ȴ�A11��·�ͷ���� */
    USM_STATE_WT_PDN_RELEASE,           /* 10 �ȴ�PDN��·�ͷ���� */

    USM_STATE_BUTT
}USM_STATE_E;



/* ����ģ��֪ͨUSM����Ϣ�� */
typedef enum tagUSM_OTHER2USM_MSGTYPE_E
{
    E_USM_MSGTYPE_A112USM_SETUP = 200, /* A11֪ͨUSM������ɵ���Ϣ�� */
    E_USM_MSGTYPE_PPP2USM_SETUP,       /* PPP֪ͨUSM������ɵ���Ϣ�� */
    E_USM_MSGTYPE_PDN2USM_SETUP,       /* PDN֪ͨUSM������ɵ���Ϣ�� */   
    E_USM_MSGTYPE_PPP2USM_RELEASE,     /* PPP֪ͨUSMȥ����ɵ���Ϣ�� */
    E_USM_MSGTYPE_A112USM_RELEASE,     /* A11֪ͨUSMȥ����ɵ���Ϣ�� */
    E_USM_MSGTYPE_PDN2USM_RELEASE,     /* PDN֪ͨUSMȥ����ɵ���Ϣ�� */
    E_USM_MSGTYPE_BUTT,

}USM_OTHER2USM_MSGTYPE_E;

/* USM״̬���¼����壬ע��Ҫ��g_pszUsmEventName����һ�� */
typedef enum
{
    USM_EVENT_A11_NEW_REG        = 1,   /* ���û������¼� */
    USM_EVENT_A11_SETUP_OK,             /* A11��·�����ɹ��¼� */    
    USM_EVENT_A11_SETUP_FAIL,           /* A11��·����ʧ���¼� */
    USM_EVENT_A11_RELEASE_OK,           /* �û�ȥ��ʱA11����·�ͷ�����¼� */    
    USM_EVENT_A11_UPDATE         = 5,   /* A11����Ĳ��������¼� */
    USM_EVENT_PPP_SETUP_OK,             /* PPP��·�����ɹ��¼� */
    USM_EVENT_PPP_SETUP_FAIL,           /* PPP��·Э��ʧ���¼� */
    USM_EVENT_PPP_RELEASE_OK,           /* �û�ȥ��ʱPPP����·�ͷ�����¼� */    
    USM_EVENT_PDN_SETUP_OK,             /* PDN�����ɹ��¼� */
    USM_EVENT_PDN_SETUP_FAIL     = 10,  /* PDN����ʧ���¼� */
    USM_EVENT_PDN_RELEASE_OK,           /* �û�ȥ��ʱPDN�ͷ�����¼� */    
    USM_EVENT_RELEASE_USER,             /* ��ģ�鷢���ȥ���¼� */    
    USM_EVENT_A11_LINK_DOWN,            /* pcf�����ȥ���¼� */
    USM_EVENT_LMA_RELEASE_DIFFHAND,     /* LMA��Ϊ�û���������л��ͷ�PDN */
    USM_EVENT_DIAM_REAUTHOR_NOTIFY,     /* AAA��������Ȩ���ɹ���Diameter Auth֪ͨUSM�����¼� */
    USM_EVENT_DIAM_REAUTHOR_OK,         /* USM��������Ȩ��Diameter Auth����Ȩ�ɹ��¼� */
    USM_EVENT_DIAM_REAUTHOR_FAIL,       /* USM��������Ȩ��Diameter Auth����Ȩʧ���¼� */
    
    USM_EVENT_A11_SETUP_TIMEOUT,        /* �ȴ�A11��·������ɳ�ʱ */
    USM_EVENT_PPP_SETUP_TIMEOUT,        /* �ȴ�PPP��·������ɳ�ʱ */
    USM_EVENT_PDN_SETUP_TIMEOUT,        /* �ȴ�PDN��·������ɳ�ʱ */
    USM_EVENT_A11_RELEASE_TIMEOUT,      /* �ȴ�A11��·�ͷ���ɳ�ʱ */
    USM_EVENT_PPP_RELEASE_TIMEOUT,      /* �ȴ�PPP��·�ͷ���ɳ�ʱ */
    USM_EVENT_PDN_RELEASE_TIMEOUT,      /* �ȴ�PDN��·�ͷ���ɳ�ʱ */
    USM_EVENT_DIAM_REAUTHOR_TIMEOUT,    /* �ȴ�Diameter Auth����Ȩ��ɳ�ʱ */
    USM_EVENT_CON_MAINTAIN_TIMEOUT,     /* �����л���Դ������ʱ����ʱ */
    USM_EVENT_REAUTH_TIMEOUT,           /* �ؼ�Ȩ��ʱ����ʱ */

    USM_EVENT_INNER_ERR,                /* USM״̬���ڲ��쳣�¼� */
     
    USM_EVENT_COA_UPD,                  /* auth֪ͨCOA�����¼� */
    
    /*Added by liushuang for qos-update*/
    USM_EVENT_SM_QOSUPD,             /*sm ֪ͨqos����*/
    /*End of liushuang*/
    USM_EVENT_BUTT
}USM_EVENT_E;


typedef enum enumUSM_BLACK_BOX_STRING_CODE_E
{
    USM_BLACK_BOX_STRING_A11_T_BIT_ERR = 1,

    USM_BLACK_BOX_STRING_CODE_BULT_E,
}USM_BLACK_BOX_STRING_CODE_E;

typedef struct
{   
    A11_IMSI_S stImsi;
    ULONG   ulPeerSigAddr;
    ULONG    ulPeerTeidc;
    UCHAR *pucDomain;  /* domain ���� apn */
    
    ULONG ulImsiFlg :1;
    ULONG ulPeerSigAddrFlg :1;
    ULONG ulPeerTeidcFlg   :1;
    ULONG uleHRPDMode      :1;
    UCHAR *pucReason;
    UCHAR *pucSuggestion;
}HSGW_EMS_ARGUMENT_S;

typedef enum
{
    HSGW_EMS_MODULE_USM,
    HSGW_EMS_MODULE_A11,
    HSGW_EMS_MODULE_PPP,
    HSGW_EMS_MODULE_PDN,
    HSGW_EMS_MODULE_FA,
    HSGW_EMS_MODULE_PMIPV6,
    HSGW_EMS_MODULE_AUTH,
    HSGW_EMS_MODULE_DIAM_AUTH,
    HSGW_EMS_MODULE_RESV,
    HSGW_EMS_MODULE_DHCP,
    HSGW_EMS_MODULE_HSGWSDU,
    
    HSGW_EMS_MODULE_BULT,
}HSGW_EMS_MODULE_E;

typedef enum
{
    EMS_USM_0_EHRPD_USER_LIMIT,
    EMS_USM_1_HRPD_1XUSER_LICE_LIMIT,
    EMS_USM_2_HRPD_DOUSER_LICE_LIMIT,    
    EMS_USM_3_HRPD_RPUSER_LICE_LIMIT,
    EMS_USM_4_CREATE_RPCONTEXT_FAIL,    
    EMS_USM_5_ALLOC_CHARGEID_FAIL,
    EMS_USM_6_HSGW_AUTH_FAIL_NO_APN,    
    EMS_USM_7_HSGW_REAUTH_FAIL_NO_APN,    
    EMS_USM_8_USER_RELEASE_CODE,
    EMS_USM_9_HSGW_IMSI_MISMATCH,
    EMS_USM_10_HSGW_MNID_IMSI_INVALID,   
    EMS_USM_11_HSGW_NO_APN_RESOURCE,
    EMS_USM_12_NOT_ENOUGH_HSGW_PDN_LICENSE,
    EMS_USM_BULT,
};

typedef enum
{
    EMS_A11_0_LOCK,
    EMS_A11_1_TIMESTAMP_NOTIN_RANGE,
    EMS_A11_2_PCF_NOT_CONFIG,
    EMS_A11_3_AUTH_CHECK_FAIL,
    EMS_A11_4_PCFIP_KEY_CONFLICT,
    EMS_A11_5_ENTRY_NO_AUXA10,
    EMS_A11_6_ENTRY_NO_SETUP,
    EMS_A11_7_HSGW_SO_ERR,
    EMS_A11_8_UPD_SO_ERR,
    EMS_A11_9_NO_ACT_CREATE_AUX,
    EMS_A11_10_L2TP_NO_AUX,
    EMS_A11_11_PREPAID_NO_AUX,
    EMS_A11_12_NVSE_ERR,
    EMS_A11_13_CVSE_ERR,
    EMS_A11_14_IMSI_MSID_ERR,
    EMS_A11_15_FLAG_ERR,
    EMS_A11_16_HA_NOT_0,
    EMS_A11_17_HAGENT_ERR,
    EMS_A11_18_SO33_AUX_ERR,
    EMS_A11_19_AUX_TOO_MUCH,
    EMS_A11_20_HRPD_NO_VERCHG,
    EMS_A11_21_VERCHG_LIS_LIMIT,
    EMS_A11_22_EHRPD_NO_VERCHG,
    EMS_A11_23_VERCHG_LIS_LIMIT,
    EMS_A11_24_KEY_ERR,
    EMS_A11_25_EHRPD_SO_ERR,
    EMS_A11_26_A10_TOO_MUCH,
    EMS_A11_27_HSGW_A10_LIS_LIMIT,
    EMS_A11_28_EVDO_A10_LIS_LIMIT,
    EMS_A11_29_CRTEAT_10_ERR,
    EMS_A11_30_UPD_A10_ERR,
    EMS_A11_31_CREATE_A10_ERR,
    EMS_A11_32_WAIT_2ND_RRQ_FAIL,
    EMS_A11_33_AUX_SO_ERR,
    EMS_A11_34_SQOS_NO_64,
    EMS_A11_35_SQOS_NO_67,
    EMS_A11_36_NO_FLOW_ID,
    EMS_A11_37_FILL_QOS_ERR,
    EMS_A11_38_NO_FLOW_ID,
    EMS_A11_39_NO_FLOW_ID,
    EMS_A11_40_ENTRY_SO_ERR,
    EMS_A11_41_FLOWLICENSE_OVER_ERR,
    EMS_A11_42_FLOWLICENSE_IS_ZERO,
    EMS_A11_43_A11_MSG_AUTHEXT_NOT_EXIST,
    EMS_A11_44_A11_MSG_UNKNOW_EXT,
    
    EMS_A11_BULT,
};

typedef enum
{
    EMS_PPP_0,
    EMS_PPP_1,
    EMS_PPP_2,
    EMS_PPP_3,
    EMS_PPP_4,
    EMS_PPP_5,
    EMS_PPP_6,
    EMS_PPP_7,
    EMS_PPP_8,
    EMS_PPP_9,
    EMS_PPP_10,
    EMS_PPP_11,
    EMS_PPP_12,
    EMS_PPP_13,
    EMS_PPP_14,
    EMS_PPP_15,
    EMS_PPP_16,
    EMS_PPP_17,
    EMS_PPP_18,
    EMS_PPP_19,
    EMS_PPP_20,
    EMS_PPP_21,
    EMS_PPP_22,
    EMS_PPP_23,
    EMS_PPP_24,
    EMS_PPP_25,
    EMS_PPP_26,
    EMS_PPP_27,
    EMS_PPP_28,
    EMS_PPP_29,
    EMS_PPP_30,
    EMS_PPP_31,
    EMS_PPP_32,
    EMS_PPP_33,
    EMS_PPP_34,
    EMS_PPP_35,
    EMS_PPP_36,
    EMS_PPP_37,
    EMS_PPP_38,
    EMS_PPP_39,
    EMS_PPP_40,
    EMS_PPP_41,
    EMS_PPP_42,
    EMS_PPP_43,
    EMS_PPP_44,
    EMS_PPP_45,
    EMS_PPP_46,
    EMS_PPP_47,
    EMS_PPP_48,
    EMS_PPP_49,
    EMS_PPP_50,
    EMS_PPP_BULT,
};

typedef enum
{
    EMS_PDN_0_NO_AAA_IPV6,
    EMS_PDN_1_STATIC_IP_TOO_MUCH, 
    EMS_PDN_2_NO_FREE_IP, 
    EMS_PDN_3_CONFLICT, 
    EMS_PDN_4_NOT_IN_RANGE,        
    EMS_PDN_5_NO_FREE_IP,        
    EMS_PDN_6_IP_TYPE_ERR,        
    EMS_PDN_7_IPCP_TIMEOUT,        
    EMS_PDN_8,        
    EMS_PDN_9,        
    EMS_PDN_10_TOO_MUCH_PDN,     
    EMS_PDN_11_APN_NOT_CONFIGURED,     
    EMS_PDN_12_APN_AAA_NOT,     
    EMS_PDN_13_PDN_TYPE_NOT_INDICATED,     
    EMS_PDN_14_FQDN_NOT_FIND,     
    EMS_PDN_15_HOST_NOT_FIND,     
    EMS_PDN_16_SELECT_DNS_ERR,     
    EMS_PDN_17_NO_PDSN_PCC_LIS,     
    EMS_PDN_18_NO_HSGW_PCC_LIC,     
    EMS_PDN_19_GET_PGW_FAIL,     
    EMS_PDN_20_NO_IPV4,     
    EMS_PDN_21_NO_IPV6,     
    EMS_PDN_22_IPV6_ERR,     
    EMS_PDN_23_DEA_CALL_BY_LNS,     
    EMS_PDN_24_DEA_TUN_BY_LNS,     
    EMS_PDN_25_DEA_TUN_BY_FAULT,     
    EMS_PDN_26_DEA_TUN_CHAP_ERR,     
    EMS_PDN_27_NO_VPN,     
    EMS_PDN_28_NO_PIIF,     
    EMS_PDN_29_NO_PMIP_LIC,     
    EMS_PDN_30_GET_PARA_FAIL,     
    EMS_PDN_31_HA_ADDR_ERR,     
    EMS_PDN_32_IPV6_LIC_LIMIT,     
    EMS_PDN_33_NO_POOL,     
    EMS_PDN_34_CONFLICT,     
    EMS_PDN_35_NOT_IN_RANGE,     
    EMS_PDN_36_ALLOC_FAIL,     
    EMS_PDN_37_MIP_LIC_LIMIT,     
    EMS_PDN_38_NO_HSGW_PDN_LICENSE,     
    EMS_PDN_39_PDN_HAS_SETUP,     
    EMS_PDN_40_DEA_BY_L2TP,    
    EMS_PDN_41_NO_HSGW_DUALSTACK_LICENSE,
    EMS_PDN_42_NO_PMIPV6_LICENSE, 
    EMS_PDN_43_DNS_SORT_ERR,     
    EMS_PDN_44_DNS_NO_CLIENT_IP, 
    EMS_PDN_45_NO_DNS_SERVER,     
    EMS_PDN_46_DNS_INSERT_TARGET_FAIL, 
    EMS_PDN_47_DNS_TARGET_TIMEOUT,     
    EMS_PDN_48_DNS_REMOTE_QRY_FAIL, 
    EMS_PDN_49_VSNCP_RECONNECT_REL, 
    
    EMS_PDN_BULT,
};


typedef enum
{
    EMS_FA_0_NO_FA_HA_SA,
    EMS_FA_1,
    EMS_FA_2,  
    EMS_FA_3,  
    EMS_FA_4,
    EMS_FA_5,
    EMS_FA_6,
    EMS_FA_7,
    EMS_FA_8,
    EMS_FA_9,
    EMS_FA_10,
    EMS_FA_11, 
    EMS_FA_12,
    EMS_FA_13,
    EMS_FA_14,
    EMS_FA_15,
    EMS_FA_16,
    EMS_FA_17,
    EMS_FA_18,
    EMS_FA_19,
    EMS_FA_20,
    EMS_FA_21,
    EMS_FA_22,
    EMS_FA_23,
    EMS_FA_24,
    EMS_FA_25,
    EMS_FA_26,
    EMS_FA_27,
    EMS_FA_28,
    EMS_FA_29,
    EMS_FA_30,
    EMS_FA_31,
    EMS_FA_32,
    EMS_FA_33,
    EMS_FA_34,
    EMS_FA_35,
    EMS_FA_36,
    EMS_FA_37,
    EMS_FA_38,
    EMS_FA_39,
    EMS_FA_40,
    EMS_FA_41,
    EMS_FA_42,
    EMS_FA_43,
    EMS_FA_44,
    EMS_FA_45,
    EMS_FA_46,
    EMS_FA_47,
    EMS_FA_48,
    EMS_FA_49,
    EMS_FA_50,
    EMS_FA_51,
    EMS_FA_52,
    EMS_FA_53,
    EMS_FA_54,
    EMS_FA_55,
    EMS_FA_56,
    EMS_FA_57,
    EMS_FA_58,
    EMS_FA_59,
    EMS_FA_60,
    EMS_FA_61,
    EMS_FA_62,
    EMS_FA_63,
    EMS_FA_64,
    EMS_FA_65,
    EMS_FA_66,
    EMS_FA_67,
    EMS_FA_68,    
    EMS_FA_69,      
    EMS_FA_70,  
    EMS_FA_71,      
    EMS_FA_72, 
    EMS_FA_73,
    EMS_FA_74, 
    EMS_FA_75,
    
    EMS_FA_BULT,
};

typedef enum
{
    EMS_PMIPV6_0_LMA_IFADDRESS_NOMATCH,
    EMS_PMIPV6_1_PBA_MNAUTH_LENTH_SHORT,
    EMS_PMIPV6_2_PBA_LAST_ISNOT_MNAUTH,
    EMS_PMIPV6_3_PBA_MNAUTHSUB_ISNOT_MNHA,
    EMS_PMIPV6_4_PBA_SPI_NOTMATCH,
    EMS_PMIPV6_5_PBA_AUTHEN_NOPASS,
    EMS_PMIPV6_6_PBA_STATUS_ABNORMAL,
    EMS_PMIPV6_7_UPDPBA_IPV4ADDR_INVALID,
    EMS_PMIPV6_8_UPDPBA_IPV6ADDR_INVALID,
    EMS_PMIPV6_9_PBA_NO_TIMESSTAMP,
    EMS_PMIPV6_10_PDSN_NO_MNID,
    EMS_PMIPV6_11_PDSN_HANDOFFID_ERR,
    EMS_PMIPV6_12_PDSN_ACCESSTECH_ERR,
    EMS_PMIPV6_13_PDSN_TIMESSTAMP_ERR,
    EMS_PMIPV6_14_PDSN_CORRID_ERR,
    EMS_PMIPV6_15_HSGW_MNID_ERR,
    EMS_PMIPV6_16_HSGW_HANDOFFID_ERR,
    EMS_PMIPV6_17_HSGW_ACCESSTECH_ERR,
    EMS_PMIPV6_18_HSGW_TIMESSTAMP_ERR,
    EMS_PMIPV6_19_HSGW_SSM_ERR,
    EMS_PMIPV6_20_HSGW_GREKEY_ERR,
    EMS_PMIPV6_21_HSGW_CHARGINGID_ERR,
    EMS_PMIPV6_22_PBA_IPADDR_NOMATCH,
    EMS_PMIPV6_23_PBA_LINKLOCAL_ERR,
    EMS_PMIPV6_24_PBA_DEFUALTROUTER_ERR,
    EMS_PMIPV6_25_IPV4ADDR_ERR,
    EMS_PMIPV6_26_IPV6ADDR_ERR,
    EMS_PMIPV6_27_NOT_IPBOTH,
    EMS_PMIPV6_28_GREKEY_CHANGE,
    EMS_PMIPV6_29_LIFETIME_ERR,
    EMS_PMIPV6_30_LIFETIME_ERR,
    EMS_PMIPV6_31_LIFETOUT,
    EMS_PMIPV6_32_PBA_REG_LIFETOUT,
    EMS_PMIPV6_33_RELV6_ERR,
    EMS_PMIPV6_34_RELV4_ERR,    
    EMS_PMIPV6_35_PBA_STATUS_128,
    EMS_PMIPV6_36_PBA_STATUS_129,
    EMS_PMIPV6_37_PBA_STATUS_130,
    EMS_PMIPV6_38_PBA_STATUS_131,
    EMS_PMIPV6_39_PBA_STATUS_132,
    EMS_PMIPV6_40_PBA_STATUS_133,
    EMS_PMIPV6_41_PBA_STATUS_134,
    EMS_PMIPV6_42_PBA_STATUS_135,
    EMS_PMIPV6_43_PBA_STATUS_136,
    EMS_PMIPV6_44_PBA_STATUS_137,
    EMS_PMIPV6_45_PBA_STATUS_138,
    EMS_PMIPV6_46_PBA_STATUS_139,
    EMS_PMIPV6_47_PBA_STATUS_140,
    EMS_PMIPV6_48_PBA_STATUS_141,
    EMS_PMIPV6_49_PBA_STATUS_142,
    EMS_PMIPV6_50_PBA_STATUS_143,
    EMS_PMIPV6_51_PBA_STATUS_144,
    EMS_PMIPV6_52_PBA_STATUS_145,
    EMS_PMIPV6_53_PBA_STATUS_146,
    EMS_PMIPV6_54_PBA_STATUS_147,
    EMS_PMIPV6_55_PBA_STATUS_148,
    EMS_PMIPV6_56_PBA_STATUS_149,
    EMS_PMIPV6_57_PBA_STATUS_150,
    EMS_PMIPV6_58_PBA_STATUS_151,
    EMS_PMIPV6_59_PBA_STATUS_152,
    EMS_PMIPV6_60_PBA_STATUS_153,
    EMS_PMIPV6_61_PBA_STATUS_154,
    EMS_PMIPV6_62_PBA_STATUS_155,
    EMS_PMIPV6_63_PBA_STATUS_156,
    EMS_PMIPV6_64_PBA_STATUS_157,
    EMS_PMIPV6_65_PBA_STATUS_158,
    EMS_PMIPV6_66_PBA_STATUS_159,
    EMS_PMIPV6_67_PBA_STATUS_160,
    EMS_PMIPV6_68_PBA_STATUS_161,
    EMS_PMIPV6_69_PBA_STATUS_162,
    EMS_PMIPV6_70_PBA_STATUS_163,
    EMS_PMIPV6_71_PBA_STATUS_164,
    EMS_PMIPV6_72_PBA_STATUS_165,
    EMS_PMIPV6_73_PBA_STATUS_166,
    EMS_PMIPV6_74_PBA_STATUS_167,
    EMS_PMIPV6_75_PBA_STATUS_168,
    EMS_PMIPV6_76_PBA_STATUS_169,
    EMS_PMIPV6_77_PBA_STATUS_170,
    EMS_PMIPV6_78_PBA_STATUS_171,
    EMS_PMIPV6_79_PBA_STATUS_172,
    EMS_PMIPV6_80_PBA_STATUS_173,
    EMS_PMIPV6_81_PBA_STATUS_174,
    EMS_PMIPV6_82_PBA_STATUS_175,
    EMS_PMIPV6_83_PBA_STATUS_176,    
    EMS_PMIPV6_84_PBA_STATUS_OTHER,
    EMS_PMIPV6_85_NO_VALID_PIIF,
    EMS_PMIPV6_86_NO_VALID_LMA,
    EMS_PMIPV6_87_NO_VALID_LMA,

    EMS_PMIPV6_BULT,
};


typedef enum
{
    EMS_AUTH_0_NO_SERVER,
    EMS_AUTH_1_GET_SERVER_FAIL,
    EMS_AUTH_2_GET_SRCIP_FAIL,
    EMS_AUTH_3_DECODE_FAIL,
    EMS_AUTH_4_CHECK_AUTH_FAIL,
    EMS_AUTH_5_CHECK_PCC_FAIL,
    EMS_AUTH_6_AAA_REJECT,
    EMS_AUTH_7_NO_SERVER,
    EMS_AUTH_8_CHECK_MIP_FAIL,
    EMS_AUTH_9_GET_APN_FAIL,
    EMS_AUTH_10_GET_PASSWORD_FAIL,    
    EMS_AUTH_11_CHECK_L2TP_FAIL,
    EMS_AUTH_BULT,
};

typedef enum
{
    EMS_DIAM_AUTH_0,
    EMS_DIAM_AUTH_1,
    EMS_DIAM_AUTH_2,
    EMS_DIAM_AUTH_3,
    EMS_DIAM_AUTH_4,
    EMS_DIAM_AUTH_5,
    EMS_DIAM_AUTH_6,
    EMS_DIAM_AUTH_7,
    EMS_DIAM_AUTH_8,
    EMS_DIAM_AUTH_9,
    EMS_DIAM_AUTH_10,
    EMS_DIAM_AUTH_11,
    EMS_DIAM_AUTH_12,
    EMS_DIAM_AUTH_13,
    EMS_DIAM_AUTH_14,
    EMS_DIAM_AUTH_15,
    EMS_DIAM_AUTH_16,
    EMS_DIAM_AUTH_17,
    EMS_DIAM_AUTH_18,
    EMS_DIAM_AUTH_19,

    EMS_DIAM_AUTH_20,
    EMS_DIAM_AUTH_21,
    EMS_DIAM_AUTH_22,
    EMS_DIAM_AUTH_23,
    EMS_DIAM_AUTH_24,
    EMS_DIAM_AUTH_25,
    EMS_DIAM_AUTH_26,    
    EMS_DIAM_AUTH_27,
    EMS_DIAM_AUTH_28,
    EMS_DIAM_AUTH_29,
    EMS_DIAM_AUTH_BULT,
};

typedef enum
{
    EMS_RESV_0,
    
    EMS_RESV_BULT,
};

typedef enum
{
    EMS_DHCP_0_NO_RELAY_FLAG,
    EMS_DHCP_1_MSG_INVALID,
    EMS_DHCP_2_ACKMSG_IP_INCORRECT,
    EMS_DHCP_BULT,
};

typedef enum
{
    EMS_HSGWSDU_0_SEL_TOKEN_FAIL,
    EMS_HSGWSDU_1_ADD_NODE_FAIL,
    
    EMS_HSGWSDU_BULT,
};

typedef enum
{
    USM_BLACKBOX_CODE_0,
    USM_BLACKBOX_CODE_1,
    USM_BLACKBOX_CODE_2, 
    USM_BLACKBOX_CODE_3,
    USM_BLACKBOX_CODE_4,
    USM_BLACKBOX_CODE_5,/* not used from here */
    
    USM_BLACKBOX_CODE_BULT = 20,      
}USM_BLACKBOX_CODE_E;



#define M_STATE_IS_DELETPROCESS(enstate)    \
    ((USM_STATE_WT_PDN_RELEASE == enstate) \
    || (USM_STATE_WT_PPP_RELEASE == enstate) \
    || (USM_STATE_WT_A11_RELEASE == enstate))

#define M_STATE_IS_ENTERPROCESS(enstate)    \
    ((USM_STATE_INIT == enstate)   \
    ||(USM_STATE_WT_A11_SETUP == enstate) \
    ||(USM_STATE_WT_PPP_SETUP == enstate) \
    ||(USM_STATE_WT_PDN_SETUP == enstate)) \

#define M_STATE_IS_ACTIVE(enstate) \
    ((USM_STATE_ACTIVE == enstate)   \
    ||(USM_STATE_DIFF_HANDOFF == enstate) \
    ||(USM_STATE_WT_DIAM_AUTHORIZE == enstate)) \

#define M_STATE_IS_TEMP(enstate) (!M_STATE_IS_ACTIVE(enstate))

#define M_USM_SETLI_HANDOFF_INFO(Option, HandOffPcfInfo, RpContext, LiContextInfo) \
    if ((PDSN_OPTION_HANDOFF == (Option)) && ((HandOffPcfInfo) != NULL)) \
    { \
        (LiContextInfo).uchandOffType = 1; \
        (LiContextInfo).ucGotOldIpFlag = VOS_TRUE; \
        (LiContextInfo).ucCanIdLen = A11_MAX_ANID_LENGTH; \
        (LiContextInfo).ucPanIdLen = A11_MAX_ANID_LENGTH; \
        VOS_MemCpy((LiContextInfo).szPanId, (RpContext)->ucPanid, (LiContextInfo).ucPanIdLen); \
        VOS_MemCpy((LiContextInfo).szCanId, (RpContext)->ucCanid, (LiContextInfo).ucCanIdLen); \
        VOS_MemCpy((VOID *)(LiContextInfo).szAccPcfIpAddr, (VOID *)&((HandOffPcfInfo)->ulPrePcfIp), sizeof(ULONG)); \
        VOS_MemCpy((VOID *)(LiContextInfo).szCurPcfIPAdd, (VOID *)&((HandOffPcfInfo)->ulCurPcfIp), sizeof(ULONG)); \
    }

#define M_USM_SETLI_ESN_INFO(Esn, LiContextInfo) \
    if( 0 == VOS_StrLen(Esn) ) \
    { \
        (LiContextInfo)->ucEsnLen = 0; \
    } \
    else \
    { \
        (LiContextInfo)->ucEsnLen = ESNBCDLEN; \
        VOS_MemCpy((LiContextInfo)->szESN, (Esn), ESNBCDLEN); \
    }

#define  M_USM_SETLI_MEID_INFO(RpContext, LiContextInfo) \
    if( VOS_FALSE == (RpContext)->bMEIDValidFlg )  \
    { \
        (LiContextInfo)->ucMeidLen = 0; \
    } \
    else \
    { \
        (LiContextInfo)->ucMeidLen = MEIDBCDLEN; \
        VOS_MemCpy((LiContextInfo)->szMEID, ((RpContext)->aucMEID), MEIDBCDLEN); \
    }
    
#define  M_USM_SETLI_MDN_INFO(RpContext, LiContextInfo) \
    if ( VOS_FALSE == (RpContext)->ucMsisdnFlag) \
    { \
        (LiContextInfo)->ucMdnLen = 0;       \
    } \
    else \
    { \
        (LiContextInfo)->ucMdnLen = MDNBCDLEN; \
        VOS_MemCpy((LiContextInfo)->szMDN, (RpContext)->szMsisdn, MDNBCDLEN); \
    }
    
#define  M_USM_SETLI_BSID_INFO(RpContext, LiContextInfo) \
    if ((RpContext)->bBsidFlag) \
    { \
        (LiContextInfo)->ucBsidFlag = (RpContext)->bBsidFlag ; \
        VOS_MemCpy((LiContextInfo)->aucBsid, (RpContext)->ucBsId, AM_BSID_LEN); \
    }
    
#define  M_USM_SETLI_FAIL_INFO(Flag, Option, ResultCode, LiContextInfo) \
       if ((PDSN_FAIL == (Flag)) && (PDSN_OPTION_SETUP == (Option))) \
       { \
           if ( E_LI_A11_ADMIN_PROHIBTED == (ResultCode) ) \
           { \
               (LiContextInfo).usFailureCause = 0xD2; \
           } \
           else \
           { \
               (LiContextInfo).usFailureCause = (ResultCode); \
           } \
       } 
       
#define  M_USM_SETLI_RELEASE_INFO(Option, ResultCode, LiContextInfo) \
       if (PDSN_OPTION_RELEASE == (Option)) \
       { \
           (LiContextInfo).usReleaseCause = (ResultCode); \
       }

#define M_USM_SETLI_PACKETFILTER_INFO(PfContext, LiContextInfo) \
    if (NULL != (PfContext)) \
    { \
        (LiContextInfo).stX2PacketFilterInfo.next   = NULL; \
        if ( (PfContext)->ucLength <= 100 ) \
        { \
            (LiContextInfo).stX2PacketFilterInfo.length = (PfContext)->ucLength; \
        } \
        else \
        { \
            (LiContextInfo).stX2PacketFilterInfo.length = 100; \
        } \
        VOS_MemCpy((LiContextInfo).stX2PacketFilterInfo.value, PfContext, (LiContextInfo).stX2PacketFilterInfo.length);  \
    }


extern UCHAR *g_pucLiReleaseCvt;

/*  ��ȡ����������ԭ��ֵ */
#define M_USM_GETLI_RELEASE_CODE(ReleaseCode)  (AM_RELCODE_BUTT <= (ReleaseCode))? E_LI_RELEASE_PDSN_ERR : g_pucLiReleaseCvt[ReleaseCode]

#define A11_MAX_QOSCAR_RATE_BPS     14*1024*1024
#define A11_MAX_QOSCAR_RATE_KBPS    14*1024

#define USM_SPU_RPODUCT_TYPE g_ulHsgwUsmProductType

extern ULONG g_ulHsgwUsmProductType;
extern CRM_SPU_BOARD_TYPE_ENUM g_ulHsgwUsmSpuType;
extern ULONG g_ulHsgwSduNum;
extern VOS_UINT64 *g_pullHsgwSduCsi;
extern ULONG g_ulUsmDelSduNaiResFlg;
extern ULONG g_ulUsmDelL2tpResFlg;
extern ULONG g_ulHsgwDbgEmsFlg;
extern ULONG g_ulUsmSgRestartAtActiveBoardFlg;

extern ULONG USM_GetCmReleaseCode( ULONG ulRelCode );
extern ULONG USM_NotifyReleaseUserMsg(ULONG ulRpIndex, ULONG ulReleaseCode);
extern ULONG USM_NotifyReleaseUserFunc(ULONG ulRpIndex, ULONG ulReleaseCode, UCHAR* pucMsg);
extern ULONG USM_NotifyPhaseResultFunc(ULONG ulRpIndex, ULONG ulMsgtype, VOS_VOID *pResultInfo);
extern ULONG USM_NotifyPhaseResultMsg(ULONG ulRpIndex, ULONG ulMsgtype);
extern VOS_BOOL USM_IsDefaultApn(ULONG ulRpIndex, USHORT usApnIndex);
extern ULONG USM_GetApnCfgByApnName(UCHAR *pucApnName, HSGW_APN_INFO_S **ppstHsgwApn);
extern ULONG USM_GetApnCfgByApnIndex(USHORT usApnIndex, HSGW_APN_INFO_S **ppstHsgwApn);
extern ULONG USM_Pmipv6GetRpDataByPdnIndex(ULONG ulPdnIndex, 
                                                        USM_PMIPV6_CONTEXT_DATA_S *pstPmipv6RpContextData);
extern ULONG USM_Pmipv6GetDataForPfTable(ULONG ulPdnIndex, 
                                                ULONG *pulTeidc,
                                                UCHAR *pucDpeId);
extern DIAM_AUTH_APN_INFO_S* USM_GetDiamApnInfo(ULONG ulRpIndex, USHORT usApnIndex);
extern DIAM_AUTH_APN_INFO_S* USM_GetApnWithCorrectFunction(ULONG ulRpIndex, USHORT usApnIndex, ULONG* pulFlag);
extern ULONG USM_GetApnIndexByApnName(UCHAR *pucApnName, USHORT *pusApnIndex);
extern ULONG USM_GetPcrfcReleaseCode( ULONG ulRelCode );
extern ULONG USM_GetSduCsiBySduId(ULONG ulSduId, VOS_UINT64 *pullSduCsi);
extern VOID USM_DebugOut(ULONG ulLevel, CHAR* pszFile, ULONG ulLineNo, CHAR *pszFuncName, CHAR *pszFormat, ...);
extern ULONG USM_A11NotifyUpdateReg( SDB_PDSN_RP_CONTEXT_S *pstRpContext, UCHAR *pucMsg);
extern ULONG USM_A11NotifyNewReg(A11_IMSI_S stIMSI , UCHAR *pucMsg);
extern UCHAR USM_GetA11ReleaseCode( ULONG ulRelCode );
extern ULONG USM_NotifyReconnectPDNMsg(UCHAR *pucMsg, ULONG ulRpIndex, ULONG ulReleaseCode);
/* BEGIN: Added for PN: PS10.1 HSGW by lihairong, 2013/3/19 */
extern ULONG USM_NotifyReleasePDNMsg(ULONG ulRpIndex, ULONG ulReleaseCode);
/* END:   Added for PN: PS10.1 HSGW by lihairong, 2013/3/19 */
extern ULONG USM_GetVsncpNegoFlag(ULONG ulRpIndex);


extern ULONG USM_BackupSlaveCreUpdRpProc(UCHAR *pucCurrent);
extern ULONG USM_BackupSlaveUpdateApnProc(UCHAR *pucCurrent);
extern ULONG USM_BackupMasterCreUpdRpProc(ULONG ulRpIndex, ULONG ulOperType, UCHAR **ppucCurrent, ULONG *pulEncapLen);
extern ULONG USM_BackupMasterUpdateApnProc(ULONG ulRpIndex, ULONG ulOperType, UCHAR **ppucCurrent, ULONG *pulEncapLen);
extern ULONG USM_BackupMasterDelRpProc(ULONG ulRpIndex, ULONG ulOperType, UCHAR **ppucCurrent, ULONG *pulEncapLen);
extern ULONG USM_BackupSlaveDelRpProc(UCHAR * pucCurrent);
extern VOID USM_SendInnerLowMsg( ULONG ulMsgType, ULONG  ulPara );
extern ULONG USM_BackupSmoothSingleUser(SDB_PDSN_RP_CONTEXT_S *pstRpContext);
extern VOID OM_EncryptPrivacyData(const VOS_CHAR * strIn, VOS_INT32 lenIn, VOS_CHAR * strOut);

extern VOS_BOOL USM_IsActiveState(ULONG ulRpIndex);
extern VOS_BOOL USM_IsEntryState(ULONG ulRpIndex);
extern VOS_BOOL USM_IsReleaseState(ULONG ulRpIndex);
extern VOID USM_PdnNotifyUpdateFinishProc(ULONG ulRpIndex, ULONG ulUpdateType);
extern ULONG USM_GetEhrpdModeFromRp(ULONG ulRpIndex, UCHAR *pucEhrpdMode);
extern VOID USM_BackupSlaveDelAllResource(ULONG ulRpIndex);
extern VOID USM_NotiyLIWithoutContextForPDSN(UCHAR ucCause, A11_PRE_PARSER_S *pstPreParser, A11_LI_PDSN_OPTION_E enOp);

extern VOID USM_NotifyLIForPDSN(ULONG ulRpindex, 
                                USHORT usResultCode,
                                A11_RESV_PF_CONTENT_S *pstPfContext,
                                A11_LI_PCF_CONTEXT_S *pstHandOffPcfInfo,
                                A11_LI_PDSN_OPTION_E ulOption, 
                                A11_LI_PDSN_FLAG ulFlag);
extern VOID USM_SetLiFlagToRpcontext(ULONG ulRpindex,LI_USM_FLAG_S *pstLiUsmFlag);
extern ULONG USM_LIGetContextByTargetID(UCHAR ucTargetIdType,UCHAR *pucTargetId,LI_CDMA2000_PDPINFO_S *pstLiPdpinfo);
extern VOID PPP_LI_SetAuInfo(LI_CDMA2000_PDPINFO_S *pstLiContextInfo, ULONG ulRpindex);
extern ULONG USM_LIGetContextByRpintexforBatchBackup(ULONG ulRpIndex,LI_CDMA2000_PDPINFO_S *pstLiPdpinfo);
extern ULONG USM_LICheckInEnterProcess(ULONG ulRpindex);

extern ULONG USM_GetDiamauthReleaseCode( ULONG ulRelCode );
VOID HSGW_EmsTraceByA11ParserNoContext(A11_PRE_PARSER_S *pstPreParser, ULONG ulModule, ULONG ulCode);
VOID HSGW_EmsTraceByRpIndex(ULONG ulRpIndex, ULONG ulModule, ULONG ulCode);
VOID HSGW_EmsTraceByRpContext(SDB_PDSN_RP_CONTEXT_S *pstRpContext, 
                              HSGW_EMS_ARGUMENT_S *pstArgs,
                              HSGW_EMS_MODULE_E enInnerModuleType, ULONG ulCode);
VOID HSGW_EmsTraceByPdnIndex(ULONG ulPdnIndex, ULONG ulModule, ULONG ulCode);
extern ULONG HSGW_RegEmsAtSduSG(VOID);
extern VOID USM_LiImsiToString( A11_IMSI_S stImsi ,UCHAR*szTemp);
extern void USM_LiStringToBCD(CHAR *strSrc, UCHAR DstArr[], UCHAR ucMaxNum);
extern ULONG USM_LIRelContextByTargetID(UCHAR ucTargetIdType,UCHAR * pucTargetId);
extern ULONG USM_GetContextTokenNumOfCurSg(VOID);
extern VOID HSGW_EmsTraceByRpContextAndSuggArgus(SDB_PDSN_RP_CONTEXT_S *pstRpContext, 
                                          HSGW_EMS_ARGUMENT_S *pstArgs,
                                          HSGW_EMS_MODULE_E enInnerModuleType, ULONG ulCode, UCHAR *pszFormat, ...);

extern ULONG USM_GetDeaSingleUserMaxTime(VOID);

#endif /* __USM_API_H__ */
