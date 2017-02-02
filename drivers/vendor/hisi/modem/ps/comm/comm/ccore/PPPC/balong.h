#ifdef    __cplusplus
extern "C" {
#endif

#include "pppc_pdn.h"

#if 1
extern ULONG g_ulHsgwA10TestDbgFlg;
extern ULONG g_ulA11RmiCommendDbgFlg;

#define UGW_LITTLE_ENDIAN VOS_LITTLE_ENDIAN
#define UGW_BIG_ENDIAN    VOS_BIG_ENDIAN
#define UGW_BYTE_ORDER UGW_LITTLE_ENDIAN


#define  AM_PRINT_64( ul64Value )  ( ULONG )(( ul64Value ) >> 32 ), ( ULONG )(( ul64Value ))
#define M_PTM_QUE_NAME_LEN  31
#define PPP_MAXQUELEN   1024
#define VOS_TIMER_EVENT 0x10000000
#define DVM_SELF_CPUID (DVM_GetSelfCpuId())
#define VOS_EV_ANY  0x0
#define VOS_MCQUEUE_NO_WAIT   ((VOS_UINT32)1 << 5) /* ���ȴ�ģʽ */
#define VOS_NO_WAIT                 ((VOS_UINT32)1 << 31)

#define A11_SO_33      33
#define A11_INVALID_RPINDEX  0
#define IPV6_DNS_LEN 4
#define DBG_LOG_FILE_NAME_LEN  8
#define DBG_LOG_SYSTEM_NAME_LEN  8
#define DBG_LOG_MODULE_NAME_LEN  8
#define DBG_LOG_SUB_MODULE_NAME_LEN  8

// relative timer
#define VOS_DBGASSERT(lExpression) \
        ( (lExpression)?(VOS_VOID)0:vos_assert( __FILE__, __LINE__ ) )
#define VOS_TIMER_LOOP      VOS_RELTIMER_LOOP
#define VOS_TIMER_NOLOOP    VOS_RELTIMER_NOLOOP

/*  ��PPPC�����Ϣ����  */
#define PPPC_AAA_CREAT_REQ                0    /* ��Ȩ���� */
#define E_COMP_TYPE_L2TT                  (3295)//3295
#define E_COMP_TYPE_AUTH                  (3298)//3298
#define E_COMP_TYPE_DIAMAUTH              (3357)//3357
#define E_COMP_TYPE_FA                    (3358)//3358
#define E_COMP_TYPE_USM                   (3256)//3256
#define M_CDB_TABLE_FUN_TYPE_TBL_INIT (0)
#define M_CDB_TABLE_FUN_TYPE_REC_APP  (1)
#define M_CDB_TABLE_FUN_TYPE_REC_DEL  (2)
#define M_CDB_TABLE_FUN_TYPE_REC_MOD  (3)
#define M_CDB_TABLE_FUN_TYPE_TBL_MOD  (4)
#define M_CDB_TABLE_FUN_TYPE_REC_NULL (0xFF)
#define M_GGSN_CARD_GSPU  2


#define SOFTPARA_BIT1398                  0
#define  M_SPM_PDSN_UDP_CHECKSUM     569
#define AAA_IN_CLASSA(i)        (((long)(i) & 0x80000000L) == 0)
#define AAA_IN_CLASSA_NET       0xff000000L
#define AAA_IN_CLASSA_HOST      0x00ffffffL
#define AAA_IN_CLASSB(i)        (((long)(i) & 0xc0000000L) == 0x80000000L)
#define AAA_IN_CLASSB_NET       0xffff0000L
#define AAA_IN_CLASSB_HOST      0x0000ffffL
#define AAA_IN_CLASSC(i)        (((long)(i) & 0xe0000000L) == 0xc0000000L)
#define AAA_IN_CLASSC_NET       0xffffff00L
#define AAA_IN_CLASSC_HOST      0x000000ffL
#define AAA_INADDR_ANY          (ULONG)0x00000000L
#define AAA_INADDR_BROADCAST    (ULONG)0xffffffffL  /* must be masked */
#define AAA_INADDR_LOOP        0x7f000000L
#define A11_PERF_OPERATOR_PLUS   0
#define A11_PERF_OPERATOR_SUB   1
#define PDSN_DBGLVL_CRITICAL   0
#define PDSN_DBGLVL_ERROR   1
#define PDSN_DBGLVL_ALARM   2
#define PDSN_DBGLVL_INFO   3
#define A11_INVALID_A10INDEX  0
#define M_SPM_PDSN_SNMP_ACCESS_FUNCTION  0/* SNMP?����?����㨹???��?��D�䨨???1|?����?��?��1?��,����2??��?a0����,2?��1?�� ;?a1����,��1?��  */
#define M_ALM_USERACCESS_FAILURE_ALARM  1415
#define M_ALM_TYPE_EVENT 2                                 /* ��??t???�� */
#define PPP_MRU_MAX_PDSN    1500
#define PPP_MRU_MAX_HSGW    1501
#define PPP_VSNCP_APN_AMBR_FLAG   0x01
#define PPP_VSNCP_DEFUALT_APN_INDICATIOR_FLAG   0x02
#define HSGW_PRODUCT_VJ_USER_NUMBER     100
#define SOFTPARA_BIT1408 0
#define  RP_MSGTYPE_A11     1
#define  RP_MSGTYPE_PPP     2
#define  RP_MSGTYPE_RSVP    4
#define  RP_MSGTYPE_FA      8
#define  RP_MSGTYPE_DHCPV4  16
#define  RP_MSGTYPE_DHCPV6  32
#define  RP_MSGTYPE_IPV6    64
#define  RP_MSGTYPE_EMS     128
#define  RP_MSGTYPE_ALL     255
#define  PUSER_MSGTYPE_PPP          0x02 /* 1 */
#define M_CDB_MAX_FIELD_LENGTH   (256 * 2)
#define M_CFG_CDB_EQUAL             0
#define SC_NUM 1
#define HSGW_PRODUCT_MPPC_PDP_NUMBER    100
#define CDB_AM_MIN_ID 50                        //50
#define CDB_AM_MAX_ID (CDB_AM_MIN_ID + 300)       //350
#define MAX_DOMAIN_NUM                  3000    /* ���DOMAIN������ */
#define SC_GRM_ADD  0
#define SC_GRM_DEC  1
#define SC_GRM_SET  2
#define AUTH_PAP_PPP 1
#define AUTH_CHAP_PPP 0
#define ASN_TIMER_DEF_TYPE(Style, TimerMid, Sub) ((((Style)&0xFF)<<24)  |(((TimerMid) &0xFF)<<16) | ((Sub)&0xFFFF))
/* IPv6ջ״̬����ʱ�� */
#define TIMER_TYPE_PDN_IPV6_FSM_TIEMR \
    ASN_TIMER_DEF_TYPE(ASN_CP_COMMON_TIMER_STYLE, ASN_COMMON_TIMER_MODULE_PDN, 3)

#define A11_PPP_FLAG_MODE           0x01

#define A11_PPP_FLAG_SYNASY         0x02

#define A11_PPP_FLAG_PFC            0x04

#define A11_PPP_FLAG_ACFC           0x08

#define A11_PPP_FLAG_IPTECH         0x01

#define A11_PPP_FLAG_STAC           0x02

#define A11_PPP_FLAG_MPPC           0x04

#define A11_PPP_FLAG_VJ             0x08
#define HSGW_DOMAIN_L2TP_ATTRIBUTE_MDN     1

#define A11_MAX_NAI_LENGTH  63     /* ���NAI���� */
#define M_CFG_MAX_APN_STRING_LEN 64
#define M_CFG_MAX_VRFNAME_LEN 32
#define M_CFG_MAX_APN_PASS_LEN 128
#define IPV6_INTERFACEID_LENGTH 8
#define HSGW_SECRET_SA_SIMPLE_LENTH     16
#define HSGW_SECRET_SA_OLD_CIPHER_LEN   24
#define HSGW_SECRET_SA_NEW_CIPHER_LEN   32
#define DIAM_AUTH_REALM_OR_HOST_MAX_LENGTH  63   /* diameter ����������������󳤶� */
#define DIAM_AUTH_DRA_HOST_MAX_LENGTH  127       /* DRA��������󳤶� */
#define MAX_DMPU_NUM      2   /* DMPU�ӿ��� */
#define MAX_DPE_NUM_PDSN  32
#define AAA_AUTHRSP_S AAA_PPPC_AUTH_RSP_S
#define A11_USER_PROFILE_NAME_LENGTH 64
#define RD_FRAMED_INTERFACE_ID_LEN  8
#define RD_FRAMED_IPV6_PREFIX_LEN   16
#define RD_FRAMED_IPV6_PREFIX_BIT_LEN   64
#define HSGW_MAX_CLASS_LEN               128
#define NAI_NAME_LEN 63/* Modified by zhudaoming 62333 at 2007-12-05 GGSN9811V9R7C01B02 for L2TP/PPP V9��??2 */
#define A11_SUBNET_LENGTH 37 /* SUBNET */
#define AAA_L2TP_LNS_NUM 2
#define RD_TUNNEL_STR_MAX_LENG 32
#define RD_FRAMED_POOL_MAX_LENG 31
#define MDN_MAX_LEN 20
#define RD_HW_MIPAGENT_MNHA_SECRET_MAXLEN 18
#define RD_HW_VPN_NAME_LEN_MAX          31     /* VPN Name�Ϊ31���ֽ� */
#define RD_MIPV6AGENT_MNHA_SECRET_LEN 32
#define A11_MAX_SO_NUM                      4
#define A11_MAX_FLOW_PROFILE_ID 16
/*ip��ַ��ulong��Ŀ*/
#define LAP_IP_ULONG_NUM     4
/*MSISDN���õ�ULONG��*/
#define LAP_MSISDN_ULONG_NUM        2
#ifndef LAP_POOL_NAME_MAX_LENGTH
#define LAP_POOL_NAME_MAX_LENGTH    32
#endif
#define DIAM_AUTH_MNID_MAX_LENGTH            63   /* MNID��?�䨮3��?��  */
#define DIAM_AUTH_NAI_MAX_LEN 63                     /* ��??��??��?�䨮3��?�� */
#define DIAM_AUTH_USERNAME_MAX_LEN 255               /* ��??��??��?�䨮3��?�� */
#define DIAM_AUTH_MN_LEN 8                           /* MN3��?�� */
#define DIAM_AUTH_MSK_LEN 64                         /* MSK3��?�� */
#define DIAM_AUTH_CORLID_LEN 64                      /* Correlation ID3��?�� */
#define DIAM_AUTH_APN_NAME_LEN 63                    /* APN NAME3��?�� */
#define DIAM_AUTH_PMK_LEN 20                         /* PMK3��?�� */
#define SDB_MAX_A10_PER_RP_SESSION          31
#define A11_MAX_ANID_LENGTH                 5
#define A11_AIR_REC_MAX_SUBNET_LEN    37
#define AM_BSID_LEN 6
#define A11_MAX_A10_PER_RP_SESSION      6/*1??��??���?�䨮��?A10��??����y*/
#define DIAM_AUTH_STATE_LEN 20                         /* STATE3��?�� */
#define DIAM_AUTH_MAX_APN_VNID              63     /* visited-Network-Identifier */
#define DIAM_AUTH_MAX_APN_DEST_HOST         255    /* Destination-Host */
#define DIAM_AUTH_MAX_APN_OI_REPLACEMENT    63     /* APN OI REPLACEMENT */
#define DIAM_AUTH_APN_INFO_MAX_NUMBER       17        /* ?��3?��?APN INFO ��?�䨮??��y */
#define PMBUF_CTL_BLK_SIZE              (252)
#define PPP_MAX_DNS_HOSTNAME_LENGTH           32
#define L2TP_TUNNEL_NAME_LEN        30
#define L2TP_TUNNEL_ASSIGNEDID_LEN  30
#define L2TP_MAX_LNS_IP_ADDRESS     2
#define L2TP_TUNNEL_PASS_LEN        32
#define L2TP_MAX_PPP_OPTION_LEN     200
#define L2TP_CHALLENGE_LEN          154
#define L2TP_RESPONSE_LEN           64
#define L2TP_USER_NAME_LEN          62
#define L2TP_SUBADDRESS_LEN         20
#define L2TP_DOMAINNAME_MAXLEN      62
#define L2TP_DIALEDNUM_LEN          64
#define L2TP_DIALINGNUM_LEN         20
#define SDB_MAX_PDSN_RP_CONTEXT_NUM   10                       /* PDSN SPU�������ı��С */
#define PTM_LOG_CNT_PREFIX_NAME_MAX_LEN  31 /* ??��y?���o??3?��?�䨮3��?�� */
#define IPV6_V6_USER       1
#define IPV6_V4V6_USER     2
#define  AAA_AUTH_SUCCESS           0  /* ??����3��1| */
#define  AAA_AUTH_FAIL              1  /* ??����?��?? */
#define  AAA_AUTH_SRV_ERR           2  /* ��t???��1��???����?��t???�¨���D?����3�� */
#define  AAA_AUTH_CLT_ERR           3  /* RDA?��?��?������?��o???�̨�����3�� */
#define  AAA_AUTH_MSG_FMT_ERR       4  /* ???��??��?�䨪?�� */
#define  AAA_AUTH_IP_ERR            5  /* IP��??����???��D?�� */
#define  AAA_POD_DELETE             6  /* POD����?? */
#define  AAA_COA_MSG                7  /* COA???��  */
#define  AAA_AUTH_SRV_NO_RSP        8  /* ��t???��1��???����?��t???�¨���D?����3�� */
#define  AAA_AUTH_SER_NOT_SUPPORT   9  /* AAA??����Service Awarness��?D????��*/
#define AAA_AUTH_EXCEED_WAL        10 /* AAA??����Service Awarness��?D????��*/
#define A11_PPP_FLAG_LZS0         0x10

#define A11_PPP_FLAG_LZS1        0x20

#define PDN_IPV6INTF_LEN        8       /* IPV6?��?��3��?�� */
#define PDN_IPV6PREF_LEN        8       /* IPV6?���o3��?�� */
#define SM_TRUE                     1
#define SM_FALSE                    0

#define IPV6_IPV6CP_ATTEMPT  1
#define IPV6_IPV6CP_SUCC     2

#define BOOL_TRUE   (1)
#define BOOL_FALSE  (0)

#define SM_NULL_PTR                 0
#define SM_RET_OK                   0
#define SM_RET_ERR                  1


#define IPV6_ADDR_ANY        0x0000U
#define IPV6_ADDR_UNICAST    0x0001U
#define IPV6_ADDR_MULTICAST  0x0002U
#define IPV6_ADDR_NODELOCAL  0x0010U

#define IPV6_ADDR_LOOPBACK   0x0004U
#define IPV6_ADDR_LINKLOCAL  0x0020U
#define IPV6_ADDR_SITELOCAL  0x0040U

#define IPV6_ADDR_COMPATv4   0x0080U
#define IPV6_ADDR_GLOBAL     0x0100U
#define IPV6_ADDR_SCOPE_MASK 0x00f0U
#define IPV6_ADDR_MAPPED     0x1000U
#define IPV6_ADDR_RESERVED   0x2000U
#define STAC_SENDRSTREQTIMEOUT       2000
#define SOFTPARA_BIT1455 0

#define DVM_SELF_SLOTID 5
#define SOFTPARA_BIT1383 0
#define PPP_USERTYPE_NULL 3

#define GTP_MAX_MSISDN_LEN             8
typedef UCHAR GTP_MSISDN[GTP_MAX_MSISDN_LEN];

#define COMP_T_PGPSTART 3000
#define DOPRA_MID_START                 0x00000000
#define DOPRA_MID_RESERVE               8191
#define DOPRA_MID_END                   (DOPRA_MID_START + DOPRA_MID_RESERVE) /*0x1FFFF0000*/

#define DOPRA_ADAPT_MID_START           (DOPRA_MID_END + 1) /*0x2000*/
#define DOPRA_ADAPT_MID_RESERVE         8191
#define DOPRA_ADAPT_MID_END             (DOPRA_ADAPT_MID_START + DOPRA_ADAPT_MID_RESERVE) /*0x3FFF*/

#define VRP_MID_START                   (DOPRA_ADAPT_MID_END + 1) /*0x4000*/
#define VRP_MID_RESERVE                 12287
#define VRP_MID_END                     (VRP_MID_START + VRP_MID_RESERVE)  /*0X6FFFF*/

#define IPOS_MID_START                  (VRP_MID_END + 1)  /*0X7000*/
#define IPOS_MID_RESERVE                12287
#define IPOS_MID_END                    (IPOS_MID_START + IPOS_MID_RESERVE) /*0X9FFF*/
#define SOFTPARA_BIT1478 0

/* Added start by jiangyongliang 50758 at 2013-04-25 PGPV2R6C01 for 8090V6R6forPGP */
#define PGP_MID_START                   (IPOS_MID_END + 1) /*0Xa000*/
#define PGP_MID_RESERVE                 256 /*����3?o�� R6C0��???*/
#define PGP_MID_END                     (PGP_MID_START + PGP_MID_RESERVE)
#define PS_MID_START                    (PGP_MID_END + 1) /*0Xa101*/
#define PS_MID_END                      (PS_MID_START + PGP_MID_RESERVE)
#define MBB_MID_COMPT_START             (PS_MID_END + 1) /*0Xa202*/
/* Added end by jiangyongliang 50758 at 2013-04-25 PGPV2R6C01 for 8090V6R6forPGP */
#define E_COMP_TYPE_PPPT   3296

#define MID_PF_COMMON   MID_PPPC
#define FWD_PID_PPP MID_PPPC

#define LINELENGTH 80

#define SOFTPARA_BIT1395 0


typedef struct Command_S* LPCommand_S;
typedef struct Command_Group_S* LPCommand_Group_S;

struct Command_S
{
    CHAR szCommand[LINELENGTH];
    CHAR szHelp[2*LINELENGTH];
    LPCommand_Group_S lpArgument;
    VOID (*CommandProc) (ULONG, CHAR*[]);
};

struct Command_Group_S
{
    LONG lCommandNo;
    LONG lHelpPos;
    LPCommand_S lpCommand;
};

typedef enum enSTATUS_CHG_FLAG
{
    STATUS_RUN,         /* 0:��???DD���䨬?; */
    STATUS_MS,          /* 1:?�¡�?���䨬?, ulPreStatus?����??��: SRM_MASTER_STATUS , SRM_SLAVE_STATUS */
    STATUS_ONLINE,      /* 2:?��??���䨬?,*/
    STATUS_PULLOUT,     /* 3:�̣���?��?3?*/
    STATUS_INSERT,      /* 4:�̣���?2?��?(SPU�̣���?����2��o���䣤����)*/
    STATUS_RESET,       /* 5:�̣���?????*/
    STATUS_LOCK,        /* 6:�̣���?CPU???��???��*/
    STATUS_SWITCHOFF,   /* 7:�̣���?CPUDY?????��*/
    STATUS_ZOMBIE,      /* 8:�̣���?zombie???��*/
    STATUS_SGRESET,     /* 9:�̣�SG?��??*/
    STATUS_SGINSERT,    /* 10:�̣�SG����2��*/
    STATUS_END          /* ?? */
} STATUS_CHG_FLAG_E;

/* !!!���騰a:???��D?��?Type���騰aDT??USM_BackupGetRpContexto��CM_PDSN_BKP_TransBackupTypeo����y */
typedef enum
{
    CKP_BACKUP_TYPE_UNKNOWN,
    CKP_BACKUP_TYPE_CREATE_RP,   /* ��??��?��??3��1|D??��rp�䣤���騰?��?��??�쨢��?����?��?��?��?��Y �㨹����RP,A10,PDN�̨�?����D����?�� */
    CKP_BACKUP_TYPE_CREATE_PDN,  /* PDN?������3��1|�䣤���騰?��?PDN����?����?��?��?��?��Y �㨹����PDN��?????,TFT,PMIPV6/FA/L2TP/SIP/EHRPD,CM,SM?����D��y?Y */
    CKP_BACKUP_TYPE_CREATE_A10,  /* A10?������3��1|�䣤���騰?��?A10����?����?��?��?��?��Y �㨹����A10��?????,CM?����D��y?Y */
    CKP_BACKUP_TYPE_COMMON_UPDATE_RP,
    CKP_BACKUP_TYPE_COA_UPDATE_RP, /* 5 */
    CKP_BACKUP_TYPE_PCCROLLBACK_UPDATE_RP,
    CKP_BACKUP_TYPE_UPDATE_APNINFO,
    CKP_BACKUP_TYPE_UPDATE_PPP,
    CKP_BACKUP_TYPE_UPDATE_A10,
    CKP_BACKUP_TYPE_COMMON_UPDATE_PDN, /* 10 */
    CKP_BACKUP_TYPE_COA_UPDATE_PDN,
    CKP_BACKUP_TYPE_PCCROLLBACK_UPDATE_PDN,
    CKP_BACKUP_TYPE_UPDATE_TFT,
    CKP_BACKUP_TYPE_UPDATE_FA,
    CKP_BACKUP_TYPE_UPDATE_FA_ADVSEQ, /* 15 */
    CKP_BACKUP_TYPE_UPDATE_PMIPV6,
    CKP_BACKUP_TYPE_UPDATE_PDN_FORWARDFLG,  /* PDN ��a�������???? */
    CKP_BACKUP_TYPE_UPDATE_A10CM,
    CKP_BACKUP_TYPE_UPDATE_PDNCM,
    CKP_BACKUP_TYPE_UPDATE_PDN_OCSC,  /* 20 */
    CKP_BACKUP_TYPE_CREATE_SM,
    CKP_BACKUP_TYPE_COMMON_UPDATE_SM,
    CKP_BACKUP_TYPE_COA_UPDATE_SM,
    CKP_BACKUP_TYPE_PCCROLLBACK_UPDATE_SM,
    CKP_BACKUP_TYPE_CREATE_PDN_PCC,     /* 25 */
    CKP_BACKUP_TYPE_AM_CREATE_PDN_PCC,
    /* ???��delete��??tD����aDT??CKP_BACKUP_TYPE_IS_DELETEo��?����? */
    CKP_BACKUP_TYPE_DELETE_RP,
    CKP_BACKUP_TYPE_DELETE_A10,
    CKP_BACKUP_TYPE_DELETE_A10CM,
    CKP_BACKUP_TYPE_DELETE_PDN,       /*30*/
    CKP_BACKUP_TYPE_DELETE_PDNCM,
    CKP_BACKUP_TYPE_DELETE_TFT,
    CKP_BACKUP_TYPE_DELETE_SM,
    CKP_BACKUP_TYPE_DELETE_PDN_PCC,
    CKP_BACKUP_TYPE_DELETE_PDN_OCSC,
    CKP_BACKUP_TYPE_CREATE_LI,

    CKP_BACKUP_TYPE_BUTT
}CKP_BACKUP_TYPE_E;

typedef enum tagE_SDB_TABLE_ID
{
    E_SDB_TABLE_UGW  = 0,                     /* UGW Table ID */
    E_SDB_TABLE_SCCG = 1,                     /* SCCG Table ID */
    E_SDB_TABLE_MSD  = 2,                     /* MSD Table ID */
    E_SDB_TABLE_VOG  = 3,                     /* VOG Table ID */
    E_SDB_TABLE_RP   = 4,                     /* PDSN RP Table ID */
    E_SDB_TABLE_A10  = 5,                     /* PDSN A10 Table ID */
    E_SDB_TABLE_PDN  = 6,                     /* PDSN PDSN Table ID */
    E_SDB_TABLE_FA   = 7,                     /* PDSN FA Table ID */
    E_SDB_TABLE_TFT  = 8,                     /* PDSN TFT Table ID */
    E_SDB_TABLE_PMIPV6  = 9,                  /* PMIPV6 Table ID */
    E_SDB_TABLE_DIAMAUTH  = 10,                /* DIAMAUTH Table ID */
    MAX_DAT_TBL_NUM                           /* ?����? */
}E_SDB_TABLE_ID;

/*?������?��?����??����?*/
typedef enum
{
    ASN_CP_COMMON_TIMER_STYLE   = 0x01,             /* ������???������??Y��??������?��*/
    ASN_CP_LOOP_TIMER_STYLE,                                      /* ������??-?��?������?�� */

    ASN_CP_TIMER_STYLE_BUTT
}ASN_COMM_TIMER_STYLE_E;


/* 2�����¨���D�� */
typedef enum PerfOpType
{
    PERF_ADD,   /* ++2������ */
    PERF_SUB    /* --2������ */
}PERFOPTYPE_ENUM;

typedef enum
{
    PTM_BATCH_CMD_RSP_CONTINUE,
    PTM_BATCH_CMD_RSP_END,
    PTM_BATCH_CMD_RSP_ARGUMENT_NUM_ERR,
    PTM_BATCH_CMD_RSP_KEYWORD_ERR,
    PTM_BATCH_CMD_RSP_ARGUMENTS_ERR,
} PTM_BATCH_CMD_RSP_E;

#define M_PS_MSG_TYPE_BASE 11

typedef enum
{
    PPP_MSG_TYPE_TIMER = M_PS_MSG_TYPE_BASE, /* ?������?��???�� */
    PPP_MSG_TYPE_AUTH,              /* ??������|��e???�� */
    PPP_MSG_TYPE_USM,               /* USM?��??����?????�� */
    PPP_MSG_TYPE_GTPC,              /* USM?��??����?????�� */
    PPP_MSG_TYPE_L2TP,              /* L2TP?��??��|��e???�� */
    PPP_MSG_TYPE_LAP,               /* ��??������??��|��e???�� */
    PPP_MSG_TYPE_DDU,               /* ?����?PF��?PPPD?��????���???��|"SxPP"?����D */
    PPP_MSG_TYPE_FCM,               /* FCM???�� */
    PPP_MSG_TYPE_INNER,
    PPP_MSG_TYPE_DIAMAAA,           /* HSGW��?��?DIMA AAA��????�� */
    PPP_MSG_TYPE_END,
}PPP_MSG_TYPE_E;
/* ��1��??������?�¦�??��?��ID��?D????��?����?D??����?��|???��mid��??����? */
typedef enum
{
    ASN_COMMON_TIMER_MODULE_START,
    ASN_COMMON_TIMER_MODULE_A11,                         /* a11?��?��?������?�¨�1��?��?MID */
    ASN_COMMON_TIMER_MODULE_IPV6,                       /* IPV6?��?��?������?�¨�1��?��?MID */
    ASN_COMMON_TIMER_MODULE_PDN,                       /* PDN?��?��?������?�¨�1��?��?MID */
    ASN_COMMON_TIMER_MODULE_USM,                       /* USM?��?��?������?�¨�1��?��?MID */
    ASN_COMMON_TIMER_MODULE_FA,                          /* FA?��?��?������?�¨�1��?��?MID */
    ASN_COMMON_TIMER_MODULE_PMIPV6,                      /* PMIPV6?��?��?������?�¨�1��?��?MID */
    ASN_COMMON_TIMER_MODULE_RESV,                        /*RESV?��?��?������?�¨�1��?��?MID */
    ASN_COMMON_TIMER_MODULE_END
}ASN_COMM_TIMER_MID_E;



typedef enum enMSG_QUE_TYPE_E
{
    MSG_QUETYPE_MCQ = 1,
    MSG_QUETYPE_VOSQ,
    MSG_QUETYPE_LFQ,
    MSG_QUETYPE_DMSQ,
}MSG_QUE_TYPE_E;

typedef enum
{
    TUNNEL_PPTP = 1,
    TUNNEL_L2F,
    TUNNEL_L2TP,
    TUNNEL_ATMP,
    TUNNEL_VTP,
    TUNNEL_AH,
    TUNNEL_IPIP,
    TUNNEL_MINIPIP,
    TUNNEL_ESP,
    TUNNEL_GRE,
    TUNNEL_DVS,
    TUNNEL_IPINIP
}L2TP_TUNNELTYPE_E;

typedef enum
{
    L2TP_TEXTUAL = 1,
    L2TP_PPP_CHAP,
    L2TP_PPP_PAP ,
    L2TP_NONE,
    L2TP_MSCHAPV1,       /*???��2??��3?*/
    L2TP_AUTHTYPE_MAX
}L2TP_AUTHTYPE_E;

typedef enum
{
    IP_TYPE_V4 = 1,   /* V4����D����??�� */
    IP_TYPE_V6,       /* V6����D����??�� */
    IP_TYPE_V6_V4,
    IP_TYPE_NON
} PPPC_IP_INFOR_FLAG_E;

/* added by gxf for GGSN80 20030212 */
/* �̡�2?��?������??t */
enum enumPPP_LowToUp
{
    PPP_ISLUP=0 ,       /* �̡�2?UP */
    PPP_ISLDOWN ,       /* �̡�2?DOWN */
    ISPCFSWITCH,    /* BS/PCF?????D?? */
    ISLRENEGO,      /* ??D-���� */
    PPP_ISLSYNTOASY,
    PPP_ISLASYTOSYN,
    PPPC_L2TPUP,
    PPPC_L2TPDOWN,  /* Added by heyajun kf1199 at 2004-06-15 V800R001B03D004 for BYHD02811 */
    ISLTUEND        /* added by gxf 200300306   end flag of enumLowToUp */
};

typedef enum
{
    E_GRM_VJ_USERNUM     = 0,
    E_GRM_MPPC_USERNUM,
    E_GRM_BUTT
}ENUM_GRM_COMPSTAT;


/* AUTH?����??����D???�騤��D��?����? */
typedef enum enAUTH_MSG_TYPE_E
{
    AUTH_MSG_TYPE_POD = M_PS_MSG_TYPE_BASE, /* AUTH?����?POD???��?����D(FCM�����̨�) */
    AUTH_MSG_TYPE_GTPC,  /* AUTH?����?USM,PPP??����???��,??��|"A_GT"?����D */
    AUTH_MSG_TYPE_IPC,   /* AUTH?����?SRU��?IPC???��?����D */
    AUTH_MSG_TYPE_PF,    /* AUTH?����???����?����|???��?����D */
    AUTH_MSG_TYPE_TIMER, /* AUTH?��?������?��???��?����D */
    AUTH_MSG_TYPE_PPP,
    AUTH_MSG_TYPE_FA,
    AUTH_MSG_TYPE_PPC,
    AUTH_MSG_TYPE_UDR,
    AUTH_MSG_TYPE_BATCH_CMD_REQ, /* ��|����?����?��|�����̡¨�??����????�� */
    AUTH_MSG_TYPE_END,
}AUTH_MSG_TYPE_E;

typedef enum
{
    /* Session����???-���� */
    L2TP_DEA_CALL_BY_USER  = 1,     /* ��??��?��?������?? */
    L2TP_DEA_CALL_BY_LNS,           /* ��?��?LNS CDN???�騨��?? */
    L2TP_DEA_CALL_BY_CMD,           /* ����1y?����?����?? */
    L2TP_DEA_CALL_BY_ERR,           /* ?��2?����3�ꨨ��?? */
    L2TP_DEA_CALL_BY_BACKBORD,      /* ��?��?����??��?2?D����a����???�� */
    L2TP_DEA_CALL_BY_NORESC,        /* ?T����?��?��??����㨹*/
    L2TP_DEA_CALL_END,

    /* Tunnel����???-���� */
    L2TP_DEA_TUNL_BY_NORMAL,        /* ?y3�ꨦ?3y */
    L2TP_DEA_TUNL_BY_LNS,           /* LNS����?e��?3y?���̨� */
    L2TP_DEA_TUNL_BY_FAULT,         /* LNS1��??��?3y?���̨� */
    L2TP_DEA_TUNL_BY_CMD,           /* ?����?����?e����?? */
    L2TP_DEA_TUNL_BY_ERR,           /* ?��2?����3�ꡤ��?e����?? */
    L2TP_DEA_TUNL_BY_BACKBORD,      /* ��?��?����??��?2?D����a����???�� */
    L2TP_DEA_TUNL_CHAP_ERR,         /* SCCRP???��?D��?Challenge Response�䨪?�� */

    /* ???��?��??����㨹?-���� */
    L2TP_DEA_NO_CLIENTIP,           /* L2TP-Group????��D�㨮?��client-ip */
    L2TP_DEA_APN_NO_CLIENTIP,       /* APN????��D�㨮?��client-ip */
    L2TP_DEA_REASON_BUTT
}L2TP_DEA_REASON_E;

typedef enum
{
    BEARER_TYPE_ANALOG = 1,
    BEARER_TYPE_DIGITAL,
    BEARER_TYPE_BOTH
}L2TP_CALLBEARETYPE_E;

typedef enum
{
    FRAMING_TYPE_SYN = 1,
    FRAMING_TYPE_ASYN,
    FRAMING_TYPE_BOTH
}L2TP_FRAMINGTYPE_E;

typedef enum
{
    L2TP_MSG_TYPE_FCM = M_PS_MSG_TYPE_BASE, /* FCM???�� */
    L2TP_MSG_TYPE_DDU,      /* ?����?PF��?L2TPD?��????���???��|"06A5"?����D */
    L2TP_MSG_TYPE_TIMER,    /* ?������?��???�� */
    L2TP_MSG_TYPE_PPPC,     /* PPPC???�� */
    L2TP_MSG_TYPE_GTPC,     /* USM???�� */
    L2TP_MSG_TYPE_HIGH,     /* ??��??��???��2??����D */
    L2TP_MSG_TYPE_LOW,      /* �̨���??��???��2??����D */
    L2TP_MSG_TYPE_TUNNEL_RECOVERY,   /* F��?�̣�SG?��??3??�㡤��?����?TUNNEL???��???�� */
    L2TP_MSG_TYPE_END,
}L2TP_MSG_TYPE_E;

/** SPU�̣���?ACTIVE/STANDBY���䨬? */
typedef enum tagCRM_PRIMARY_INFO_ENUM
{
    E_CRM_ACTIVE = 0,       /**< �̣���??aACTIVE���䨬? */
    E_CRM_STANDBY,          /**< �̣���??aSTANDBY���䨬? */
    E_CRM_PRIMARY_NULL      /**< ?TD����䨬? */
}  CRM_PRIMARY_INFO_ENUM ;

/*!!!!!!!!!!!!!���騰a: D???��?��??-����?�̡�?D����a?��USM_DebugRegRelReasonStro����y?D����2����??? */

/*��???D??���????��??��e*/
typedef enum
{
    LOGLVL_CRITICAL = 0, /*????�䨪?��*/
    LOGLVL_COMMON    = 1, /*��?��?�䨪?��*/
    LOGLVL_EVENT    = 2, /*��??t*/
    LOGLVL_BUTT     = 3  /*?����?����??*/
} E_LOG_LVL;

typedef enum
{
    M_OS_PPPCOMPRESS_FLD_GROUPNUMBER ,
    M_OS_PPPCOMPRESS_FLD_INSTANCEID  ,
    M_OS_PPPCOMPRESS_FLD_ID   ,
    M_OS_PPPCOMPRESS_FLD_BUTT
}E_OS_PPP_COMPRESS_TBL_FLD;

typedef enum enumUSM_LOG_LVL_E
{
    USM_LOG_INFO = 0,
    USM_LOG_WARNING,
    USM_LOG_ERR,
    USM_LOG_PRINTINFO,/*INFO??��e��?1?2???����????��???�䨰��?����??��1��?��???��e,????��y?????��????��?????��???*/
    USM_LOG_BUTT
}USM_LOG_LVL_E;

typedef enum
{
    E_FSM_FINISHED,     /* ���䨬??��??DD?����? */
    E_FSM_RUN_ERR,      /* ���䨬??����|����o����y?��DD����㨹 */
    E_FSM_WAIT_EVENT,   /* �̨���y��a2?��??t */
    E_FSM_CONTINUE,     /* ?��D???��???���䨬???DD */
    E_FSM_REDIRECT,     /* ???��?����?2??����?���䨬?��?D?��??t����?a��?��? */
    E_FSM_MISMATCH,     /* ���䨬??����??t?��??����㨹 */
    E_FSM_UNKNOWN_ERR,  /* ???��?-���� */

    E_FSM_RESULT_BUTT,
}FSM_RESULT_E;


/* ��??��o��PDN����???-����?�� */
typedef enum
{
    AM_RELCODE_UNKNOWN                  = 0,    /* ?��?a?-���� */
    AM_RELCODE_COMMAND,                         /* ��??��?����?����?e����?? */
    AM_RELCODE_FOR_UPGRADE,

    /* USM��???����???-���� */
    AM_RELCODE_USM_BEGIN                = 10,
    AM_RELCODE_USM_FSM_INNER_ERR,               /* USM?�¡������䨬?��|������y?e��?��?��? */
    AM_RELCODE_USM_SESSION_TIMEOUT,             /* ��??��session time out�䣤�����?��?��? */
    AM_RELCODE_USM_POD_REL,                     /* AAA����?ePOD��?��?��? */
    AM_RELCODE_USM_EHRPD_NOPDN,                 /* eHRPD��??��?Tpdn��??����������??��??�� */
    AM_RELCODE_USM_EHRPD_AAA_REL        = 15,   /* eHRPD��??��AAA����?e��?����?? */
    AM_RELCODE_USM_EHRPD_REAUTH_REL,            /* eHRPD��??��??������������㨹 */
    AM_RELCODE_USM_EHRPD_ALL_APN_CHANGE,        /* eHRPD��??�쨺������D??��??���騦����??�� */
    AM_RELCODE_USM_EHRPD_NO_APN,                /* eHRPD?T��������D??�� */
    AM_RELCODE_USM_CON_MAINTAIN_TIMEOUT,        /* eHRPD��??��䨮E-UTRAN��??????D?������?��3?��������??��??�� */
    AM_RELCODE_USM_DIFF_HANDOFF_VSNCP  = 20,    /* eHRPD��??��䨮E-UTRAN��??????D?������?��3?����?�㨺?��?VSNCP???����?����??��??�� */
    AM_RELCODE_USM_SG_EXCEPTION,                /* SG����3�ꡤ��?e����?? */
    AM_RELCODE_USM_SMOOTH_FAIL,                 /* ????����㨹����?e����?? */
    AM_RELCODE_USM_DEA_IMSI_MISMATCH,           /* eHRPD????����IMSI��??�� */
    AM_RELCODE_USM_DEA_IMSI_INVALID,           /* eHRPD??����IMSI2?o?���� */
    AM_RELCODE_USM_EHRPD_NO_APN_RESOURCE,       /* eHRPD??���� �����?APN����?TAPN����?�� */
    AM_RELCODE_USM_END                  = 30,

    /* A11��???����???-���� */
    AM_RELCODE_A11_BEGIN                = 31,
    AM_RELCODE_A11_PCF_ORGIN,                    /* PCF?��?������?e����?? */
    AM_RELCODE_A11_LIFETIME_EXCP,               /* A11 LIFETIME3?���� */
    AM_RELCODE_A11_RRQ2_RPO_FAIL,               /* A11��|�����̨�?t��?RRQ����㨹 */
    AM_RELCODE_A11_RRQ2_WAIT_TIMEOUT   = 35,    /* A11�̨���y�̨�?t��?RRQ3?���� */
    AM_RELCODE_A11_ACTIVE_UPDATE_FAIL,          /* A11?��??��??��D?����㨹 */
    AM_RELCODE_A11_ENTRY_UPDATE_FAIL  ,         /* A11��?��?��??��D?����㨹 */
    AM_RELCODE_A11_ACTIVE_HANDOFF_FAIL,         /* A11?��??��??D??����㨹 */
    AM_RELCODE_A11_ENTRY_HANDOFF_FAIL,          /* A11��?��?��??D??����㨹 */
    AM_RELCODE_A11_ACTIVE_UPDATEA10_FAIL = 40,  /* A11?��???��D?A10����㨹 */
    AM_RELCODE_A11_ACTIVE_ADD_LIFETIME_FAIL,    /* A11?��?????��lifetime?������?�¨���㨹 */
    AM_RELCODE_A11_UPDATE_UPDATEA10_FAIL ,      /* A11?��D?A10?��D?����㨹 */
    AM_RELCODE_A11_UPDATE_LIFETIME,              /* A11?��D?lifetime����㨹 */
    AM_RELCODE_A11_EXIT_WAIT_PCFRELEASE_FAIL,   /* A11��?��?�̨���ypcf release3?���� */
    AM_RELCODE_A11_EXIT_WAIT_REG_ACK_FAIL = 45,  /* A11��?��?�̨���yREG ACK3?���� */
    AM_RELCODE_A11_CHECK_UPDATE_MSG_FAIL,        /* A11?��2��?��D????�騺��㨹 */
    AM_RELCODE_A11_UPDATE_FAIL,
    AM_RELCODE_A11_AUXA10_TO_LIMIT,
    AM_RELCODE_A11_CREATE_A10_FAIL,
    AM_RELCODE_A11_END                 = 55,

    /* PPP��???����???-���� */
    AM_RELCODE_PPP_BEGIN               = 56,
    AM_RELCODE_PPP_LCP_NEGONAK  ,                /* LCPD-����2??������ */
    AM_RELCODE_PPP_LCP_NEGOTIMEOUT,             /* LCPD-����3?���� */
    AM_RELCODE_PPP_LCP_ECHOTIMEOUT,             /* LCP ECHO3?���� */
    AM_RELCODE_PPP_LCP_USERDEL        = 60,      /* LCP��??�졤��?e����?? */
    AM_RELCODE_PPP_LCP_LOOPBACK,                /* LCP?��???��?����??�� */
    AM_RELCODE_PPP_PAP_NAK  ,                    /* PAP??����?��1?2?3��1| */
    AM_RELCODE_PPP_PAP_REQTIMEOUT,              /* �̨���yPAP???��3?���� */
    AM_RELCODE_PPP_PAP_SEND_REQTIMEOUT,         /* PAP?��?������?��REQ???��3?���� */
    AM_RELCODE_PPP_PAP_AAATIMEOUT    = 65,      /* PAP�̨���yAAA???��3?���� */
    AM_RELCODE_PPP_CHAP_NAK,                     /* CHAP??����?��1?2?3��1| */
    AM_RELCODE_PPP_CHAP_CHLTIMEOUT ,            /* CHAP����?��Challenge3?���� */
    AM_RELCODE_PPP_CHAP_RSPTIMEOUT,             /* �̨���yMN???��3?���� */
    AM_RELCODE_PPP_CHAP_AAATIMEOUT,             /* CHAP�̨���yAAA???��3?���� */
    AM_RELCODE_PPP_IPCP_NEGONAK      = 70,      /* IPCPD-����2??��?������ */
    AM_RELCODE_PPP_IPCP_NEGOTIMEOUT,            /* IPCPD-����3?���� */
    AM_RELCODE_PPP_IPCP_USERDEL ,               /* IPCP��??�졤��?e����?? */
    AM_RELCODE_PPP_IPV6CP_NEGONAK,              /* IPV6CPD-����2??��?������ */
    AM_RELCODE_PPP_IPV6CP_NEGOTIMEOUT,          /* IPV6CPD-����3?���� */
    AM_RELCODE_PPP_IPV6CP_USERDEL    = 75,      /* IPV6CP��??�졤��?e����?? */
    AM_RELCODE_PPP_ECHORRP_MAGIC_ERR,           /* ????����?����?ECHO replay???���?magic num�䨪?�� */
    AM_RELCODE_PPP_TOTAL_TIMEOUT ,               /* PPPD-����3?���� */
    AM_RELCODE_PPP_VSNCP_NEGOTIMEOUT,           /* VSNCPD-����3?���� */
    AM_RELCODE_PPP_VSNCP_USERDEL,               /* VSNCP��??�졤��?e����?? */
    AM_RELCODE_PPP_VSNCP_NEGONAK    = 80,       /* VSNCPD-����2??��?������ */
    AM_RELCODE_PPP_EAP_FAIL,                     /* eap??����?��1?2?3��1| */
    AM_RELCODE_PPP_CMPRESS_RENEGO_FAIL ,        /* ?1????D-��������㨹 */
    AM_RELCODE_PPP_RECHLLENGE_FAIL,             /* lcp??D-������?��???��������㨹 */
    AM_RELCODE_PPP_L2TPTUNLPARA_ERR,            /* AAA??����?���̨�����D����?L2tp,����??��1?����?����2?��1?������??��??�� */
    AM_RELCODE_DEA_CMIP_FOR_BIT1493 =85,      /* ����2?BIT_1493�䨰?a������??��IPCP����?��?��??��??��?����? */
    AM_RELCODE_PPP_END              = 95,

    /* PDN��???����?? */
    AM_RELCODE_PDN_BEGIN            = 96,
    AM_RELCODE_PDN_INNER_ERR ,                   /* PDN?��2?����3���???��?��? */
    AM_RELCODE_PDN_USM_DEACTIVE,                /* USM����?e��?��?��?��??��?a?��???-����??������1��? */
    AM_RELCODE_PDN_CM_ACT_FAIL,                 /* CM?��??����㨹 */
    AM_RELCODE_PDN_CM_ACT_TIMOUT   = 100,       /* CM?��??3?���� */
    AM_RELCODE_PDN_CM_UPD_FAIL,                 /* CM?��D?����㨹 */
    AM_RELCODE_PDN_CM_UPD_TIMOUT,                /* CM?��D?3?���� */
    AM_RELCODE_PDN_CM_DEA_PREPAID_USEOUT,      /* CM?��?������?e��?��?��??��??��?3??? */
    AM_RELCODE_PDN_CM_DEACTIVE,                 /* CM?��?������?e��?��?, ?????-���� */
    AM_RELCODE_PDN_PCRF_ACT_FAIL,               /* PCRF?��??����㨹 */
    AM_RELCODE_PDN_PCRF_ACT_TIMOUT = 106,      /* PCRF?��??3?���� */
    AM_RELCODE_PDN_PCRF_UPD_FAIL,               /* PCRF?��D?����㨹 */
    AM_RELCODE_PDN_PCRF_UPD_TIMOUT,             /* PCRF?��D?3?���� */
    AM_RELCODE_PDN_PCRF_REL,                    /* PCRF?��?������?e��?��? */
    AM_RELCODE_PDN_ECHOTIMEOUT_COMM,            /* PDSN��?ALWAYSON��??��IDLE3?������?��? */
    AM_RELCODE_PDN_NETWK_EST_TIMEOUT = 111,    /* PDN�̨���y�������䨬??��3?���� */
    AM_RELCODE_PDN_COMMAND,                     /* ?����?����?ePDN����?? */
    AM_RELCODE_PDN_SM_NOTIFY_FAIL,              /* PDN����?aSM����㨹*/
    AM_RELCODE_PDN_HSGW_IDLETIMEOUT,            /* EHRPD����?aIDLETIMEOUT*/
    AM_RELCODE_PDN_RES_CHECK_FAIL,              /* PDN����?��o?2������㨹 */
    AM_RELCODE_PDN_EHRPD_APN_CHANGE = 116,      /* eHRPD��??�쨺������D??��??���騦����??�� */
    AM_RELCODE_PDN_DUALSTACK_LICENSE_FAIL,      /* PDN????License Check ����㨹 */
    AM_RELCODE_PDN_END                 = 125,

    /*!!!!!!!!!!!!!���騰a: D???��?��??-����?�̡�?D����a?��USM_DebugRegRelReasonStro����y?D����2����??? */

    /* Sub-PDN�������䨬??������?? */
    AM_RELCODE_SUBNET_BEGIN           = 126,
    AM_RELCODE_SUBNET_INNER_ERR ,              /* �������䨬??��?��2?��|��������㨹 */
    AM_RELCODE_SUBNET_PDN_REL,                  /* PDN���䨬??������?a�������䨬??��������? */
    AM_RELCODE_SUBNET_IPCPV4_REL,               /* IPCPv4������??������㨹 */
    AM_RELCODE_SUBNET_IPCPV4_TIMEOUT = 130,     /* IPCPv43?���� */
    AM_RELCODE_SUBNET_IPCPV6_REL,               /* IPCPv6������??������㨹 */
    AM_RELCODE_SUBNET_IPCPV6_TIMEOUT ,          /* IPCPv63?���� */
    AM_RELCODE_SUBNET_LAP_FAIL,                 /* LAP����㨹��??��?a?��???-������?��1��? */
    AM_RELCODE_SUBNET_LAP_TIMEOUT,              /* LAP3?���� */
    AM_RELCODE_SUBNET_L2TP_REL       = 135,     /* L2TP����?e��?��?��??��?a?��???-������?��1��? */
    AM_RELCODE_SUBNET_L2TP_TIMEOUT,             /* L2TP3?���� */
    AM_RELCODE_SUBNET_FA_REL ,                  /* FA����?e��?��?��??��?a?��???-������?��1��? */
    AM_RELCODE_SUBNET_FA_TIMEOUT,               /* FA3?���� */
    AM_RELCODE_SUBNET_INVAILD_PGW,              /* ��?����PGW��??�� */
    AM_RELCODE_SUBNET_CMIP_LICE = 140,                /* ��?��?lice */
    AM_RELCODE_SUBNET_PMIPV4_LICE,              /* ��?��?lice */
    AM_RELCODE_SUBNET_PMIPV6_LICE,              /* ��?��?lice */
    AM_RELCODE_SUBNET_SIPV6_LICE,               /* ��?��?lice */
    AM_RELCODE_SUBNET_PDSNPCC_LICE,             /* ��?��?lice */
    AM_RELCODE_SUBNET_HSGWPCC_LICE = 145,            /* ��?��?lice */
    AM_RELCODE_SUBNET_LI_BAN_FORBIT,           /* ?����y?a??ban1|?��???1��??��?����? */
    AM_RELCODE_SUBNET_VSNCP_RECONNECT,         /* VSNCP???��PDN��??�� */
    AM_RELCODE_SUBNET_VSNCP_REL,               /* VSNCP������??������㨹 */
    AM_RELCODE_SUBNET_VSNCP_TIMEOUT ,          /* VSNCP3?���� */
    AM_RELCODE_SUBNET_END             = 150,

    /*!!!!!!!!!!!!!���騰a: D???��?��??-����?�̡�?D����a?��USM_DebugRegRelReasonStro����y?D����2����??? */

    /* LAP��???����?? */
    AM_RELCODE_LAP_BEGIN              = 151,
    AM_RELCODE_LAP_ALLOC_FAIL,                  /* ��?��?��???��??������㨹 */
    AM_RELCODE_LAP_NO_FREE_IP,                  /* ??��D???D��??�� */
    AM_RELCODE_LAP_CONFLICT,                    /* ?2��?��??��3?��? */
    AM_RELCODE_LAP_RECYLE,                      /* ��??��??��? */
    AM_RELCODE_LAP_END                = 160,

    /* L2TP��???����?? */
    AM_RELCODE_L2TP_BEGIN             = 161,
    AM_RELCODE_L2TP_NO_RESC,                    /* L2TP?T����?��?����? */
    AM_RELCODE_L2TP_LNS_NORESP,                 /* LNS?T��|��e */
    AM_RELCODE_L2TP_LNS_ORGIN,                  /* LNS?��?������?e����?? */
    AM_RELCODE_L2TP_TUNNEL_AUTH_FAIL = 165,    /* TUNNEL��??�診��㨹 */
    AM_RELCODE_L2TP_NO_CLIENT_IP,               /* ��?��??????T����??��?��?��???IP��??�� */
    AM_RELCODE_L2TP_NO_RADIUS_CLIENT_IP,       /* RADIUS??L2TP2?��y?T����??��?��?��???IP��??�� */
    AM_RELCODE_L2TP_INNER_ERR,                  /* L2TP?��2?����3�� */
    AM_RELCODE_L2TP_CHECK_ERR,                  /* PDNo?2��L2tp��??�쨺��㨹 */
    AM_RELCODE_L2TP_END                = 170,

    /* FA��???����???-���� */
    AM_RELCODE_FA_BEGIN                = 171,
    AM_RELCODE_PMIP_FOR_HAERR,                  /* deactive for HA ?��???��D?����㨹 */
    AM_RELCODE_PMIP_FOR_FAERR,                  /* deactive for FA ����3�� */
    AM_RELCODE_PMIP_FOR_LIFETIME_OUT,           /* deactive for FA ����3�� */
    AM_RELCODE_CMIP_FOR_HADEL         = 175,    /* deactive for HA ����?e��?��?��? */
    AM_RELCODE_CMIP_FOR_FAERR,                  /* deactive for FA ����3�� */
    AM_RELCODE_CMIP_FOR_LIFETIME_OUT,          /* deactive for lifetime 3?���� */
    AM_RELCODE_PMIP_FOR_REVOCATION_SEND_LCP,
    AM_RELCODE_PMIP_FOR_REVOCATION_NO_SEND_LCP,
    AM_RELCODE_CMIP_FOR_WAIT_RRQ_TIMEOUT = 180, /*deactive for �̨���yRRQ3?����*/
    AM_RELCODE_CMIP_FOR_PDSN_RVOCATION,         /*deactive for PDN����?e��?��?*/
    AM_RELCODE_CMIP_FOR_MN_RVOCATION,
    AM_RELCODE_CMIP_FOR_FAERR_NOSENDLCP,
    AM_RELCODE_FA_END                 = 190,

    /* pmipv6��???����?? */
    AM_RELCODE_PMIPV6_BEGIN          = 191,
    AM_RELCODE_PMIPV6_INNER_ERR,               /* PMIPV6?��2?����3�� */
    AM_RELCODE_PMIPV6_LMA_TOUT,                 /* lma?����|3?���� */
    AM_RELCODE_PMIPV6_LMA_FAIL,                 /* lma����??����㨹 */
    AM_RELCODE_PMIPV6_LMA_CHECK_ERR = 195,     /* lma???��?��2������㨹 */
    AM_RELCODE_PMIPV6_LIFE_TOUT,                /* lifetime3?���� */
    AM_RELCODE_PMIPV6_PGW_REL_NORMAL,           /* PGW����?e?y3�ꨨ��?? */
    AM_RELCODE_PMIPV6_PGW_REL_SAME_HAND,        /* PGW����?e����?? - HSGW???D??*/
    AM_RELCODE_PMIPV6_PGW_REL_DIFF_HAND,        /* PGW����?e����?? - ��????D??*/
    AM_RELCODE_PMIPV6_PGW_REL_UNKNOWN_HAND,     /* PGW����?e����?? - ?��?a?D??*/
    AM_RELCODE_PMIPV6_PDN_REL_RSP,              /*  ???��PDN����?????�� */
    AM_RELCODE_PMIPV6_END          = 210,

    /*!!!!!!!!!!!!!���騰a: D???��?��??-����?�̡�?D����a?��USM_DebugRegRelReasonStro����y?D����2����??? */

    /* dhcp��???����?? */
    AM_RELCODE_DHCP_BEGIN          = 211,
    AM_RELCODE_DHCP_REL,                        /* DHCP����?e��?����?? */
    AM_RELCODE_DHCP_END             = 220,

    /* DNS����㨹?-���� */
    AM_RELCODE_DNS_BEGIN            = 221,
    AM_RELCODE_DNS_ERR,  /* DNS������?����㨹 */
    AM_RELCODE_DNS_FQDN_NOT_FOUND,              /* FQDN2��?������㨹 */
    AM_RELCODE_DNS_HOST_NOT_FOUND,              /* Host�㨮?��2��?������㨹 */
    AM_RELCODE_DNS_SORT_ERR,                    /* ??D��2�����¨���㨹 */
    AM_RELCODE_DNS_END              = 230,

    /* PF����?a����?? */
    AM_RELCODE_PF_NTY_DEA_USER_BY_IPVPN = 231,
    AM_RELCODE_PF_NTY_DEA_USER_BY_GIDEFEND,

    AM_RELCODE_BUTT,          /* ?TD��?�� */

}AM_RELEASE_CODE_E;

/* ?����D��??��???����? */
typedef enum tag_URTD_Priority_Type
{
    URTD_PRIORITY_HIGH,      /* 12?��?����D??��??��?? */
    URTD_PRIORITY_LOW,       /* 12?��?����D�̨���??��?? */
    URTD_PRIORITY_MAX_NUM
}URTD_Priority_Type_S;


enum enumRTDPRI
{
    RTD_PRIORITY_HIGH   = 0x1,/* 12?��?����D??��??��?? */
    RTD_PRIORITY_MIDDLE = 0x2,/* 12?��?����D?D��??��?? */
    RTD_PRIORITY_LOW    = 0x4,/* 12?��?����D�̨���??��?? */
};

typedef enum
{
    AM_DBG_MODULE_TELNET_SITCH,
    //AM_DBG_MODULE_ALL_RES,
    //AM_DBG_MODULE_CLEAR_ALL_CNT,
    AM_DBG_MODULE_BULT,
} AM_DBG_MODULE_CALL_BACK_E;


typedef enum enE_CDB_AM_GLOBAL_TBL
{
    M_CHR_FILTER_TBL_ID = CDB_AM_MIN_ID,
    M_AM_LICENSE_ALARM_TBL_ID,
    M_SC_USERTRACE_TBL_ID,
    M_LAP_IPV6_TBL_ID,
    M_LAP_POOL_TBL_ID,
    M_LAP_SECTION_TBL_ID,
    M_LAP_DOMAIN_POOL_TBL_ID,
    M_LAP_CONFIGURATION_TBL_ID,
    M_AM_SOFTPARA_TBL_ID,
    M_GM_IPSQM_SHAPING_TBL_ID,
    M_GM_IPSQM_DYNAMIC_INTER_TBL_ID,

    CDB_AM_GLOBAL_END_TBl_ID,        //61
}E_CDB_AM_GLOBAL_TBL;

typedef enum enE_CDB_AM_MULTI_INSTANCE_TBL
{
    M_OS_APN_DOMAINSEPARATOR_TBL_ID = CDB_AM_GLOBAL_END_TBl_ID + 1,
    M_OS_PPPCFG_TBL_ID,
    M_OS_L2TP_GROUP_TBL_ID,
    M_OS_L2TP_DEFAULT_TBL_ID,
    M_LI_TARGET_TBL_ID,
    M_LI_STANDARD_TYPE_TBL_ID,
    M_LI_DFCFG_TBL_ID,
    M_LI_GLOBAL_CFG_TBL_ID,
    M_LI_IFNETCFG_TBL_ID,
    M_LI_ADMF_TBL_ID,
    M_LI_DF_TBL_ID,
    M_LI_CHN_TIMER_TBL_ID,
    M_LI_CHN_AUTHPARA_TBL_ID,
    M_SC_APN_COMMOM_TBL_ID,
    CDB_AM_GUL_PDSN_END_TBl_ID,   //75
}E_CDB_AM_MULTI_INSTANCE_TBL;


typedef enum enE_CDB_AM_PHGW_TBL
{
    M_HSGW_MCC_MNC_TBL_ID = CDB_AM_GUL_PDSN_END_TBl_ID + 1,
    M_SC_A11_PCFPERFOBJECT_TBL_ID,
    M_AM_PDP_BWM_PCFIP_TBL_ID,
    M_HSGW_VIRTUALAPN_DFCFG_TBL_ID,
    M_SC_FAHASA_TBL_ID,                 //80
    M_SC_MIP_FA_TBL_ID,
    M_SC_MNFASA_TBL_ID,
    M_SC_MNHASA_TBL_ID,
    M_SC_FA_MN_ENABLE_TBL_ID,
    M_HSGW_APN_INFO_TBL_ID,
    M_OS_PPPCOMPRESS_TBL_ID,
    M_HSGW_SERVER_GROUP_TBL_ID,
    M_OM_QOS_PRIVATEPROFILECFG_TBL_ID,
    M_HSGW_PMIPV6_COMMONCFG_TBL_ID,
    M_OM_QOS_PROFILECFG_TBL_ID,             //90
    M_HSGW_QOS_CAR_TBL_ID,
    M_SC_SUBSCRIBERQOSII_TBL_ID,
    M_OM_A11_VOIPCAR_TBL_ID,
    M_SC_SUBSCRIBERQOS_TBL_ID,
    M_HSGW_QOSMAP_TBL_ID,
    M_AM_MIP_VPN_TBL_ID,
    M_SC_A11_PCFCFG_TBL_ID,
    M_SC_A11_CFG_TBL_ID,
    M_HSGW_APN_COMMOM_TBL_ID,
    M_HSGW_APN_DNS_TBL_ID,                 //100
    M_HSGW_APN_ROUTE_TBL_ID,
    M_DIAM_SERVER_GROUP_TBL_ID,
    M_HSGW_AAA_DIAMETER_SERVER_TBL_ID,
    M_SC_STA_LOCALINFO_TBL_ID,
    M_HSGW_DIAM_SERVER_GROUP_TBL_ID,
    M_HSGW_CSN_POOL_TBL_ID,
    M_HSGW_CSN_POOL_NODE_TBL_ID,
    M_HSGW_CSN_FUNCTION_TBL_ID,
    M_HSGW_CSN_RECOMMEND_IMSI_TBL_ID,
    M_HSGW_CSN_RECOMMEND_IMSISEG_TBL_ID,   //110
    M_HSGW_CSN_RECOMMEND_PCFIP_TBL_ID,
    M_HSGW_CSN_DETECT_TBL_ID,
    M_HSGW_CSN_PDSN_SA_TBL_ID,
    M_HSGW_PMIPV6_CHECKSUMCALC_TBL_ID,
    M_HSGW_SUBSCRIBER_APN_QOS_TBL_ID,
    M_HSGW_MNC_LENGTH_TBL_ID,
    M_HSGW_HANDOFF_TIMER_TBL_ID,
    M_HSGW_SERVER_GROUP_AUTH_3GPP2_VSA_TBL_ID,
    M_HSGW_MIP_UPDATE_TRIGGER_TBL_ID,
    M_HSGW_DNS_HOSTNAME_TBL_ID,             //120
    M_HSGW_DNS_FQDN_TBL_ID,
    M_AM_PDP_BWM_BSID_GROUP_TBL_ID,
    M_HSGW_MIP_DATA_ENCAPE_TBL_ID,
    M_HSGW_QOS_USERPRIORITY_MAP_TBL_ID,
    M_SC_PMIPV4_COM_CONFIG_TBL_ID,
    M_HSGW_PGW_IMSI_FQDN_MAP_TBL_ID ,
    M_HSGW_QOS_AMBR_MAX_AGGREGATE_BAND_TBL_ID,
    M_HSGW_PMIPV4_UPDATE_TRIGGER_TBL_ID,
    M_PDSN_MIP_PCC_CONFIG_TBL_ID,
    M_HSGW_DNS_SERVER_GROUP_TBL_ID,         //130
    M_HSGW_DNS_SERVER_TBL_ID,
    M_HSGW_DNS_CLIENT_IP_TBL_ID,

    M_HSGW_DNS_RUN_PARAMETER_TBL_ID,
    M_HSGW_MCC_MNC_HSGW_TBL_ID,
    M_HSGW_APN_CORRECT_SWITCH_TBL_ID,
    M_HSGW_APN_CORRECT_RULE_TBL_ID,
    CDB_AM_PHGW_END_TBL_ID = CDB_AM_MAX_ID,
}E_CDB_AM_PHGW_TBL;



typedef enum
{
    EHRPD_VSNCP_PRO_OK = 0,                 /* ?y3���|���� */
    EHRPD_VSNCP_PRO_ERR = 1,                /* ����3���|���� */
    EHRPD_VSNCP_PRO_COPY = 2,               /* ?o��?��|���� */
    EHRPD_VSNCP_PRO_BUTT
}EHRPD_VSNCP_PRO_CODE_E;

typedef enum
{
    PPP_MSG_CODE_LINK_UP = 1,       /* AM��??��?��?????�� */
    PPP_MSG_CODE_LINK_DOWN,         /* AM��??�쨨��?????�� */

    PPP_MSG_CODE_L2TP_UP,           /* L2TP��??��?��?????�� */
    PPP_MSG_CODE_L2TP_DOWN,         /* L2TP��??�쨨��?????�� */
    PPP_MSG_CODE_L2TP_CLEARSTATISC, /* ??3y?���̨���3??D??�� */

    PPP_MSG_CODE_AUTH_RSP,          /* AUTH??������|��e???�� */

    PPP_MSG_CODE_LAP_RSP, //= LAP2_SND2_USM_MSG,   /* LAP��??����???��|��e???�� */

}PPP_MSG_CODE_E;

typedef enum tagFWD_TO_CTRL_MSG_EN
{
    /*to TCP Que*/
    MSG_FWD_TO_CTRL_TCP_PKT = 10,                       /* 10*/
    MSG_FWD_TO_CTRL_TCP_GM,                             /* 11 */
    MSG_FWD_TO_CTRL_TCP_X2X3,                           /* 12 */
    MSG_FWD_TO_CTRL_TCP_PKT_LAP,                        /* 13 */

    MSG_FWD_TO_CTRL_TCP_PKT_ICAP,                       /* 14*/

    /*to SC Que*/
    MSG_FWD_TO_CTRL_MIP_ASL = 20,                       /* 20*/
    MSG_FWD_TO_CTRL_MIP_RRQ,                            /* 21 */
    MSG_FWD_TO_CTRL_ICMP6_RS,                           /* 22 */
    MSG_FWD_TO_CTRL_ICMP6_NS,                           /* 23 */
    MSG_FWD_TO_CTRL_PPP_LCP,                            /* 24 */
    MSG_FWD_TO_CTRL_PPP_OTHER,                          /* 25 */
    MSG_FWD_TO_CTRL_TRACE,                              /* 26 */
    MSG_FWD_TO_CTRL_MBMS_TRACE,                         /* 27 */
    MSG_FWD_TO_CTRL_DROP_TRACE,                         /* 28 */
    /*to IF3 Signal Que*/
    MSG_FWD_TO_CTRL_IF3_NWHS = 30,                      /* 30 */
    MSG_FWD_TO_CTRL_IF3_NWSDU,                          /* 31 */
    MSG_FWD_TO_CTRL_IF3_SD_REQUEST,                     /* 32 */
    MSG_FWD_TO_CTRL_IF3_SD_RESPONSE,                    /* 33 */

    MSG_FWD_TO_CTRL_PPP_EXCP,                           /* 34 */
    MSG_FWD_TO_CTRL_L2TP_IPCP_ACK,                      /* 35 */

    /*to GTPSignal Que*/
    MSG_FWD_TO_CTRL_GTP0_ACTIVE  = 40,                  /* 40*/
    MSG_FWD_TO_CTRL_GTP1_ACTIVE,                        /* 41 */
    MSG_FWD_TO_CTRL_GTP0_UPDATE,                        /* 42 */
    MSG_FWD_TO_CTRL_GTP1_UPDATE,                        /* 43 */
    MSG_FWD_TO_CTRL_GTP0_DEACTIVE,                      /* 44 */
    MSG_FWD_TO_CTRL_GTP1_DEACTIVE,                      /* 45 */
    MSG_FWD_TO_CTRL_GTP0_ERRINDICATION,                 /* 46 */
    MSG_FWD_TO_CTRL_GTP1_ERRINDICATION,                 /* 47 */
    MSG_FWD_TO_CTRL_GTP0_PATH_MAINTAIN_ECHO_REQUEST,    /* 48 */
    MSG_FWD_TO_CTRL_GTP1_PATH_MAINTAIN_ECHO_REQUEST,    /* 49 */
    MSG_FWD_TO_CTRL_GTP0_PATH_MAINTAIN_ECHO_RESPONSE,   /* 50 */
    MSG_FWD_TO_CTRL_GTP1_PATH_MAINTAIN_ECHO_RESPONSE,   /* 51 */
    MSG_FWD_TO_CTRL_LI,                                 /* 52 */
    MSG_FWD_TO_CTRL_GTP0_OTHER,                         /* 53 */
    MSG_FWD_TO_CTRL_GTP1_OTHER,                         /* 54 */
    MSG_FWD_TO_CTRL_GTP2_ACTIVE,                        /* 55 */
    MSG_FWD_TO_CTRL_GTP2_UPDATE,                        /* 56 */
    MSG_FWD_TO_CTRL_GTP2_DEACTIVE,                      /* 57 */
    MSG_FWD_TO_CTRL_GTP2_ERRINDICATION,                 /* 58 */
    MSG_FWD_TO_CTRL_GTP2_PATH_MAINTAIN_ECHO_REQUEST,    /* 59 */
    MSG_FWD_TO_CTRL_GTP2_OTHER,                         /* 60 */
    MSG_FWD_TO_CTRL_GTP2_TRACE,                         /* 61 */
    MSG_FWD_TO_CTRL_MS_CHANGE,                          /* 62 */
    MSG_FWD_TO_CTRL_RESPONSE,                           /* 63 */
    MSG_FWD_TO_CTRL_GTP2_MBMS,                          /* 64 */
    MSG_FWD_TO_CTRL_VIP_GTP1_ACT_UPD,                   /* 65 */
    MSG_FWD_TO_CTRL_VIP_GTP1_DEACTIVE,                  /* 66 */

    /*To UDP Que*/
    MSG_FWD_TO_CTRL_GTP0_CHARGE = 70,                   /* 70  udp == 3386*/
    MSG_FWD_TO_CTRL_GTP1_CHARGE,                        /* 71  udp == 3386*/
    MSG_FWD_TO_CTRL_RADIUS,                             /* 72  udp == 3799*/
    MSG_FWD_TO_CTRL_DHCP,                               /* 73  udp == 67  */
    MSG_FWD_TO_CTRL_AAA,                                /* 74  udp == 68  */
    MSG_FWD_TO_CTRL_L2TP_SIGNAL,                        /* 75  udp == 1701*/
    MSG_FWD_TO_CTRL_CHR1,                               /* 76  udp == 6010*/
    MSG_FWD_TO_CTRL_CHR2,                               /* 77  udp == 6011*/
    MSG_FWD_TO_CTRL_CHR3,                               /* 78  udp == 6012*/
    MSG_FWD_TO_CTRL_CHR4,                               /* 79  udp == 6013*/
    MSG_FWD_TO_CTRL_MIP_RRQ_zz,                         /* 80  upd == 434 */
    MSG_FWD_TO_CTRL1_MIP_RRP,                           /* 81  udp == 10701*/
    MSG_FWD_TO_CTRL2_MIP_RRP,                           /* 82  udp == 10702*/
    MSG_FWD_TO_CTRL3_MIP_RRP,                           /* 83  udp == 10703*/
    MSG_FWD_TO_CTRL4_MIP_RRP,                           /* 84  udp == 10704*/
    MSG_FWD_TO_CTRL_GX,                                 /* 85  udp == 10501*/
    MSG_FWD_TO_CTRL_GY,                                 /* 86  udp == 10502*/
    MSG_FWD_TO_CTRL_GO,                                 /* 87  udp == 10503*/
    MSG_FWD_TO_CTRL_GMB,                                /* 88  udp == 10504*/
    MSG_FWD_TO_CTRL_X2,                                 /* 89  udp == 10505*/
    MSG_FWD_TO_CTRL_X3,                                 /* 90  udp == 10506*/
    MSG_FWD_TO_CTRL_RMI,                                /* 91  udp == 10507*/
    MSG_FWD_TO_CTRL_CY1,                                /* 92  udp == 10508*/
    MSG_FWD_TO_CTRL_CY2,                                /* 93  udp == 10509*/
    MSG_FWD_TO_CTRL_CY3,                                /* 94  udp == 10510*/
    MSG_FWD_TO_CTRL_CY4,                                /* 95  udp == 10511*/
    MSG_FWD_TO_CTRL_CY5,                                /* 96  udp == 10512*/
    MSG_FWD_TO_CTRL_CY6,                                /* 97  udp == 10513*/
    MSG_FWD_TO_CTRL_CY7,                                /* 98  udp == 10514*/
    MSG_FWD_TO_CTRL_CY8,                                /* 99  udp == 10515*/
    MSG_FWD_TO_CTRL_CY9,                                /* 100 udp == 10516*/
    MSG_FWD_TO_CTRL_CY10,                               /* 101 udp == 10517*/
    MSG_FWD_TO_CTRL_CY11,                               /* 102 udp == 10518*/
    MSG_FWD_TO_CTRL_CY12,                               /* 103 udp == 10519*/
    MSG_FWD_TO_CTRL_CY13,                               /* 104 udp == 10520*/
    MSG_FWD_TO_CTRL_CY14,                               /* 105 udp == 10521*/
    MSG_FWD_TO_CTRL_CY15,                               /* 106 udp == 10522*/
    MSG_FWD_TO_CTRL_CY16,                               /* 107 udp == 10523*/
    MSG_FWD_TO_CTRL1_GTP_CHARGE,                        /* 108 udp == 10601*/
    MSG_FWD_TO_CTRL2_GTP_CHARGE,                        /* 109 udp == 10602*/
    MSG_FWD_TO_CTRL3_GTP_CHARGE,                        /* 110 udp == 10603*/
    MSG_FWD_TO_CTRL4_GTP_CHARGE,                        /* 111 udp == 10604*/
    MSG_FWD_TO_CTRL1_AUTHORIZE,                         /* 112 udp == 10001��-10010*/
    MSG_FWD_TO_CTRL2_AUTHORIZE,                         /* 113 udp == 10031��-10040*/
    MSG_FWD_TO_CTRL3_AUTHORIZE,                         /* 114 udp == 10061��-10070*/
    MSG_FWD_TO_CTRL4_AUTHORIZE,                         /* 115 udp == 10091��-10100*/
    MSG_FWD_TO_CTRL1_CHARGE,                            /* 116 udp == 10011��-10030*/
    MSG_FWD_TO_CTRL2_CHARGE,                            /* 117 udp == 10041��-10060*/
    MSG_FWD_TO_CTRL3_CHARGE,                            /* 118 udp == 10071��-10090*/
    MSG_FWD_TO_CTRL4_CHARGE,                            /* 119 udp == 10101��-10120*/


    /*UDP-?��?a???��o?*/
    MSG_FWD_TO_CTRL_UNKNOWN_UDP_PORT,                   /* 120 */
    MSG_FWD_TO_CTRL_PMIPv6_OVER_IPv4_SIG,               /* 121 */
    MSG_FWD_TO_CTRL_GTPv2_SIG,                          /* 122 */

    MSG_FWD_TO_CTRL_DHCPv4_CLIENT,                      /* 123 */
    MSG_FWD_TO_CTRL_DHCPv4_SERVER,                      /* 124 */
    MSG_FWD_TO_CTRL_DHCPv6_CLIENT,                      /* 125 */
    MSG_FWD_TO_CTRL_DHCPv6_SERVER,                      /* 126 */
    MSG_FWD_TO_CTRL_IPv6,                               /* 127 */
    MSG_FWD_TO_CTRL_IPv6_PMIPv6_SIG,                    /* 128,IPV6��?��?������?PMIPV6D?��?*/
    MSG_FWD_TO_CTRL_IPv4_UDP_PMIPv6_SIG,                /* 129,IPV4��?��?��?UDP������?PMIPV6D?��?*/
    MSG_FWD_TO_CTRL_IPv4_NO_UDP_PMIPv6_SIG,             /* 130,IPV4��?��?2?��?UDP������?PMIPV6D?��?*/
    MSG_FWD_TO_CTRL_DL_DATA_NOTIFY,                     /* 131,idle���䨬?������?��???DD����??o������?aAM*/
    MSG_FWD_TO_DPS_DPE_UPDATEGTPU_ACTIVE,               /* 132,????????3ygtpu����??��??o��?����??o��DPS����?aDPE??DD����??3??o��?��|����*/
    MSG_FWD_TO_DPS_DPE_UPDATEGTPU_IDLE,                 /* 133,????????gtpu����??��??o��?����??o��DPS����?aDPE???o��?���������DD��*/
    MSG_FWD_TO_DPS_DPE_UPDATEGTPU_DEL_PKT,              /* 134,????????gtpu����??��?��?3y?o��?����??����??o��DPS����?aDPE??3y?o��?�������*/
    /*added start by wanghongbin at 2009.04.15 for IPPM*/
    MSG_FWD_TO_CTRL_IPPM_SIG,                           /* 135,IPPM��?D??D?��????*/
    MSG_FWD_TO_CTRL_IPPM_TRACE,                         /* 136,IPPM��?D??DD����a��?����GM��??����������??*/
    /*added end by wanghongbin at 2009.04.15 for IPPM*/
    MSG_FWD_TO_CTRL_PMIPv6_HEARTBEAT,
    MSG_FWD_TO_CTRL_UE_HEART=0x92,                      /* 146 */
    MSG_FWD_TO_CTRL_GTP_STATIC_USER,                    /* 147 */

    /*****************************/
    /*for PDSN*/
    /*****************************/
    MSG_FWD_TO_CTRL_A11_DEA = 150,                      /* 150 */
    MSG_FWD_TO_CTRL_A11_ACT,                            /* 151 */
    MSG_FWD_TO_CTRL_A11_UPD,                            /* 152 */
    MSG_FWD_TO_CTRL_A11_SUPD,                           /* 153 */

    MSG_FWD_TO_CTRL_RSVPv4,                             /* 154 */
    MSG_FWD_TO_CTRL_RSVPv6,                             /* 155 */

    MSG_FWD_TO_CTRL_COMPRESS,                           /* 154 */
    MSG_FWD_TO_CTRL_UNCOMPRESS,                         /* 155 */

    MSG_FWD_TO_DPE_PPP_LINKCUT,                         /* 156 ppp ??����*/

    MSG_FWD_TO_CTRL1_MIP_REVOCATION,                    /* 157 mip revocation sc0*/
    MSG_FWD_TO_CTRL2_MIP_REVOCATION,                    /* 158 mip revocation sc1*/
    MSG_FWD_TO_CTRL3_MIP_REVOCATION,                    /* 159 mip revocation sc2*/
    MSG_FWD_TO_CTRL4_MIP_REVOCATION,                    /* 160 mip revocation sc3*/

    MSG_FWD_TO_CTRL_RPT_HEARTBEAT,

    GTP_MBMS_SESSION_START_SIGNAL_MESSAGE_TYPE_1 = 200, /* 200,������?MBMS��?Session Start???��*/
    GTP_MBMS_SESSION_STOP_SIGNAL_MESSAGE_TYPE_1,        /* 201,������?MBMS��?Session Stop???��*/

    MSG_FWD_TO_CTRL_SCTP_PKT = 220,
    MSG_FWD_TO_CTRL_SCTP_PKT_LAP,
    MSG_FWD_TO_CTRL_SCTP_X2X3,
    MSG_FWD_TO_CTRL_SCTP_PKT_ICAP,

    MSG_FWD_TO_CTRL_IPv4_UDP_PMIPv6_MH6_SIG = 300,
    MSG_FWD_TO_CTRL_IPv4_UDP_PMIPv6_MH13_SIG,
    MSG_FWD_TO_CTRL_IPv4_UDP_PMIPv6_MH16_SIG,
    MSG_FWD_TO_CTRL_IPv6_PMIPv6_MH6_SIG,
    MSG_FWD_TO_CTRL_IPv6_PMIPv6_MH13_SIG,
    MSG_FWD_TO_CTRL_IPv6_PMIPv6_MH16_SIG,

    MSG_FWD_TO_CTRL_BUTTON,/*?TD��*/
}FWD_TO_CTRL_MSG_EN;

typedef enum tagLICENSE_ITEM
{
    /* ����License?a??����2����?��?o����Y������???��?DD?�����������???License��?2??����?�䨪??��??????����??��?��2��?��?? */
    /* ???y������?D��????���騺����?����??o������???����?��?1��???����??��?����?2����?3D����?srv_lice_adp.c???t?D��??����?��y����??DD?eDD����???��2����?����?�訪����?��?��???��| */

    LICE_LIMIT_ITEM_PDP_NUM_GGSN,                                          /* AutoTag[LKW5NoBF01:PDP Context Numbers of Supporting GGSN Basic Function](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_GGSN_PDP_NUM,                                          /* AutoTag[LKW5W9BSG01:PDP Context Numbers of Supporting Basic Software for GGSN](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SGW_PDP_NUM,                                           /* AutoTag[LKW5W9BSW02:PDP Context Numbers of Supporting Basic Software for S-GW](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_PGW_PDP_NUM,                                           /* AutoTag[LKW5W9BSP02:PDP Context Numbers of Supporting Basic Software for P-GW](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SPGW_PDP_NUM,                                          /* AutoTag[LKW5W9BSWP2:PDP Context Numbers of Supporting Basic Software for Integrated S-GW and P-GW](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_CONVERGENCE_PDP_NUM,                                   /* AutoTag[LKW5W9BSI02:PDP Context Numbers of Supporting Basic Software for Integrated GGSN and S-GW and P-GW](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_BASIC_PDP_NUM,                                     /* AutoTag[LKW5W9DBAS01:PDP Context Numbers of Supporting SA-Basic](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_PIPELINE_CONCATENATION,                                /* AutoTag[LKW5W9PIP02:PDP Context Numbers of Supporting SA-HTTP Pipeline and WAP Concatenation](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_P2P_NUM,                                           /* AutoTag[LKW5W9P2P02:PDP Context Numbers of Supporting SA-P2P](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_VOIP_NUM,                                          /* AutoTag[LKW5W9VOIP02:PDP Context Numbers of Supporting SA-VOIP](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_IM_NUM,                                            /* AutoTag[LKW5W9DPIM02:PDP Context Numbers of Supporting SA-IM](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_NEW_WEBBROWSING_PDP_NUM,                           /* AutoTag[LKW5W9WEBB03:PDP Context Numbers of Supporting SA-Web Browsing](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_NEW_FILEACCESS_PDP_NUM,                            /* AutoTag[LKW5W9DFAP03:PDP Context Numbers of Supporting SA-File Access](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_NEW_STREAMING_PDP_NUM,                             /* AutoTag[LKW5W9DSTM03:PDP Context Numbers of Supporting SA-Streaming](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_STOCK_NUM,                                         /* AutoTag[LKW5W9DSTK02:PDP Context Numbers of Supporting SA-Stock](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_GAME_NUM,                                          /* AutoTag[LKW5W9DGME02:PDP Context Numbers of Supporting SA-Game](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_NEW_EMAIL_PDP_NUM,                                 /* AutoTag[LKW5W9DEMA01:PDP Context Numbers of Supporting SA-Email](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_NEW_TUNNELING_PDP_NUM,                             /* AutoTag[LKW5W9DTUN01:PDP Context Numbers of Supporting SA-Tunneling](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_NEW_NETWORK_ADMIN_PDP_NUM,                         /* AutoTag[LKW5W9DNAD03:PDP Context Numbers of Supporting SA-Network Administration](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_REMOTECONNECT_NUM,                                 /* AutoTag[LKW5W9DRCE02:PDP Context Numbers of Supporting SA-Remote Connectivity](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_NEW_DATABASE_PDP_NUM,                              /* AutoTag[LKW5W9DDSE01:PDP Context Numbers of Supporting SA-Database](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_NEW_NETWORK_STORAGE_PDP_NUM,                       /* AutoTag[LKW5W9DNSR01:PDP Context Numbers of Supporting SA-Network Storage](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_NEW_MOBILE_PDP_NUM,                                /* AutoTag[LKW5W9DMOB03:PDP Context Numbers of Supporting SA-Mobile](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_NEW_OTHER_PDP_NUM,                                 /* AutoTag[LKW5W9DOTR01:PDP Context Numbers of Supporting SA-Others](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_REPORTING_RECORD_GENERATE_PDP_NUM,                     /* AutoTag[LKW5WPSRRG01:PDP Context Numbers of Supporting Reporting Record Generating](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_TCP_ID_NUM,                                            /* AutoTag[LKW5W9TCPR02:PDP Context Numbers of Supporting TCP Retransmission Identification](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_L7_NUM,                                            /* AutoTag[LKW5W9L7TD02:PDP Context Numbers of Supporting Layer 7 Traffic Discrimination](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_HSDPA_4M,                                              /* AutoTag[LKW5W9HSDPA1:PDP Context Numbers of Supporting HSDPA, 2M-4M](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_HSDPA_8M,                                              /* AutoTag[LKW5W9HSDPA2:PDP Context Numbers of Supporting HSDPA Expansion 1, 4M-8M](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_HSDPA_16M,                                             /* AutoTag[LKW5W9HSDPA3:PDP Context Numbers of Supporting HSDPA Expansion 2, 8M-16M](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_HSDPA_32M,                                             /* AutoTag[LKW5WHSDPA01:PDP Context Numbers of Supporting HSDPA Expansion 3, 16M-32M](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_HSDPA_48M,                                             /* AutoTag[LKW5WHSDPA02:PDP Context Numbers of Supporting HSDPA Expansion 4, 32M-48M](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_HSDPA_84M,                                             /* AutoTag[LKW5WHSDPA03:PDP Context Numbers of Supporting HSDPA Expansion 5, 48M-84M](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_HSDPA_168M,                                            /* AutoTag[LKW5WHSDPA04:PDP Context Numbers of Supporting HSDPA Expansion 6, 84M-168M](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_HSDPA_256M,                                            /* AutoTag[LKW5W9HSDPA4:PDP Context Numbers of Supporting HSPA+(DOWNLINK) 16M+](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_HSUPA_4M,                                              /* AutoTag[LKW5W9HSUPA1:PDP Context Numbers of Supporting HSUPA,2M-4M](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_HSUPA_8M,                                              /* AutoTag[LKW5W9HSUPA2:PDP Context Numbers of Supporting HSUPA Expansion 1, 4M-8M](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_HSUPA_12M,                                             /* AutoTag[LKW5WHSUPA01:PDP Context Numbers of Supporting HSUPA Expansion 2, 8M-12M](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_HSUPA_24M,                                             /* AutoTag[LKW5WHSUPA02:PDP Context Numbers of Supporting HSUPA Expansion 3, 12M-24M](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_HSUPA_256M,                                            /* AutoTag[LKW5W9HSUPA3:PDP Context Numbers of Supporting HSPA+(UPLINK) 8M+](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SCTP_PDP_NUM,                                          /* AutoTag[LKW5WPSCTP01:PDP Context Numbers of Supporting SCTP](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_PCC_FUNC_NUM,                                          /* AutoTag[LKW5W9SPCC01:PDP Context Numbers of Supporting PCC Basic Function](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_MS_INFO_CHANGE_CRTL_NUM,                               /* AutoTag[LKW5W9PCRL02:PDP Context Numbers of Supporting Policy control based on real-time location](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_INITIAL_LOCATION,                                      /* AutoTag[LKW5W9PBIL02:PDP Context Numbers of Supporting Policy Control based on Initial Access Location](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SERVICE_AWARENESS_BWM_PDP,                             /* AutoTag[LKW5W9TCSA01:PDP Context Numbers of Supporting Traffic Control Based on Service Awareness](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_POLICY_CTRL_TRAFFIC_NUM,                               /* AutoTag[LKW5W9PCBT02:PDP Context Numbers of Supporting Policy control based on traffic](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_POLICY_CTRL_SERVICE_TRAFFIC_NUM,                       /* AutoTag[LKW5WPFPBS01:PDP Context Numbers of Fair Usage Policy Control Based on Service Accumulate Traffic](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_WEB_PROXY,                                             /* AutoTag[LKW5W9WEB02:PDP Context Numbers of Supporting Web Proxy](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_CAPTIVE_PORTAL,                                        /* AutoTag[LKW5W9SCCP02:PDP Context Numbers of Supporting Captive Portal](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SHAPING,                                               /* AutoTag[LKW5W9SHAP02:PDP Context Numbers of Supporting The service-based traffic shaping](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DIFFSV_PDP_NUM,                                        /* AutoTag[LKW5W9DSER01:PDP Context Numbers of Supporting Differentiated Services](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_QOS_BASED_ON_SERVICE,                                  /* AutoTag[LKW5W9QOS02:PDP Context Numbers of Supporting QoS Control Based on Service](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_QOS_PDP_NUM,                                           /* AutoTag[LKW5W9TCQS01:PDP Context Numbers of Supporting Conversational Traffic Class QoS Service Bearing](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_LOCALQOS_PDP_NUM,                                      /* AutoTag[LKW5W9LQOS02:PDP Context Numbers of Supporting Local QoS Control](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SUP_EXTENDQCI,                                         /* AutoTag[LKW5W9QCIE02:PDP Context Numbers of Supporting QCI Extension](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_HEADENR_HHEN01,                                        /* AutoTag[LKW5W9HTTPE2:PDP Context Numbers of Supporting HTTP header enrichment](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_HEADENR_ANTI_FRAUD,                                    /* AutoTag[LKW5W9HTTPE4:PDP Context Numbers of Supporting HTTP Header Anti-Spoofing](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DNS_CHARGING_ANTI_SPOOFING_PDP_NUM,                    /* AutoTag[LKW5WPDNCA01:PDP Context Numbers of Supporting DNS Charging Anti-Spoofing](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_HTTP_CHARGING_ANTI_SPOOFING_PDP_NUM,                   /* AutoTag[LKW5WPHPCA01:PDP Context Numbers of Supporting HTTP Charging Anti-Spoofing](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DNS_ERRCODERED_PDP_NUM,                                /* AutoTag[LKW5WPDNSO01:PDP Context Numbers of Supporting DNS Overwriting](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_HTTP_ERRCODERED_PDP_NUM,                               /* AutoTag[LKW5WPSHPR01:PDP Context Numbers of Supporting Smart HTTP Redirection](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_HTTPS_SERVICE_IP_ADDRESS_PARSER_PDP_NUM,               /* AutoTag[LKW5WPHSAP01:PDP Context Numbers of Supporting HTTPS Service IP Address Parser](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_L7_QOS_ENF_PDP_NUM,                                /* AutoTag[LKW5W9STQE01:PDP Context Numbers of Supporting Service Triggered QOS Enforcement](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_IM_RESRC_CONTROL_FUN,                                  /* AutoTag[LKW5W9RCIM02:PDP Context Numbers of Supporting IM Type Services Radio Resources Management](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_HEADEN_RTSP_PDP_NUM,                                   /* AutoTag[LKW5W9BRHE02:PDP Context Numbers of Supporting Basic RTSP Header Enrichment](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_HEAT_PAY_NUM,                                          /* AutoTag[LKW5W9HOT02:PDP Context Numbers of Supporting Hot Billing](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_CON_PAY_NUM,                                           /* AutoTag[LKW5W9BCC02:PDP Context Numbers of Supporting Basic Content Based Charging](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DIAMETER_PDP_NUM,                                      /* AutoTag[LKW5W9DOCH02:PDP Context Numbers of Supporting Gy Interface Online Charging](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_CONVOLUME_PDP_NUM,                                     /* AutoTag[LKW5WPVBCS01:PDP Context Numbers of Supporting Volume Based Charging of Service](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_CONTIME_PDP_NUM,                                       /* AutoTag[LKW5W9TBCS02:PDP Context Numbers of Supporting Time Based Charging of Service](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_EVENT_CHARGING,                                        /* AutoTag[LKW5W9EBCS02:PDP Context Numbers of Supporting Event Based Charging of Service](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_ASN_ROAMING_CHARGING,                                  /* AutoTag[LKW5W9ASNR01:PDP Context Numbers of Supporting ASN roaming charging](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_COA_PDP_NUM,                                           /* AutoTag[LKW5W9SCOA02:PDP Context Numbers of Supporting CoA](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_OCS_ENVELOPE_PDP_NUM,                                  /* AutoTag[LKW5W9ENRE02:PDP Context Numbers of Supporting Envelope Reporting](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_RADIUS_PDP_NUM,                                        /* AutoTag[LKW5W9RADF02:PDP Context Numbers of Supporting Radius](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_CM_CREDITPOOL_PDP_NUM,                                 /* AutoTag[LKW5W9CEPL02:PDP Context Numbers of Supporting Credit Pooling](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_REFERER_CHARGE_PDP_NUM,                                /* AutoTag[LKW5W9RUCF02:PDP Context Numbers of Supporting Referer URL Charging](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_IPV6_NUM,                                              /* AutoTag[LKW5W9IPV602:PDP Context Numbers of Supporting IPv6](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_IPV6_PDP_NUM,                                      /* AutoTag[LKW5W9V6DP02:PDP Context Numbers of Supporting IPv6 SA](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_IPV6_DIAMETER_NUM,                                     /* AutoTag[LKW5W9V6OC02:PDP Context Numbers of Supporting IPV6 Online Charging](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_IPV4V6_NUM,                                            /* AutoTag[LKW5W9VDSA02:PDP Context Numbers of Supporting IPv4v6 Dual Stack Access](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_LTE2UTRAN_NUM,                                         /* AutoTag[LKW5W9LTEUT2:PDP Context Numbers of Supporting Inter-RAT Mobility between LTE and GSM/UMTS](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_LTE2CDMA_NUM,                                          /* AutoTag[LKW5W9LTEC02:PDP Context Numbers of Supporting Handover without Optimizations between LTE and eHRPD](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_IMS_NUM,                                               /* AutoTag[LKW5W9IMSA02:PDP Context Numbers of Supporting IMS access](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SRVCC_NUM,                                             /* AutoTag[LKW5WPRVCC01:PDP Context Numbers of Supporting SRVCC](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_PMIP_PDP_NUM,                                          /* AutoTag[LKW5W9PMIP02:PDP Context Numbers of Supporting PMIP](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_L2TP_VPN_PDP_NUM,                                      /* AutoTag[LKW5W9L2TP02:PDP Context Numbers of Supporting L2TP VPN](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_PPP_OVER_GTP_NUM,                                      /* AutoTag[LKW5W9PPPG01:PDP Context Numbers of Supporting PPP over GTP](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_MPLS_VPN_PDP_NUM,                                      /* AutoTag[LKW5W9MPLS02:PDP Context Numbers of Supporting MPLS VPN](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_CONTENT_FILTERING_PDP_NUM,                             /* AutoTag[LKW5W9CNFL02:PDP Context Numbers of Supporting URL Filtering Base Function](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_CF_TIMERANGE_PDP_NUM,                                  /* AutoTag[LKW5W9CFTM01:PDP Context Numbers of Supporting Time Based URL Filtering](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_IPPM_PDP_NUM,                                          /* AutoTag[LKW5W9IPPM01:PDP Context Numbers of Supporting IP Performance Monitor](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_BASIC_RPT,                                             /* AutoTag[LKW5W9BSTR02:PDP Context Numbers of Supporting Basic Traffic Reporting](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SAMPLE_RPT,                                            /* AutoTag[LKW5W9FSTR02:PDP Context Numbers of Supporting Full Sampling for Reporting](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_BLOCKED_RPT,                                           /* AutoTag[LKW5W9TTTR02:PDP Context Numbers of Supporting Throttling Traffic Reporting](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_PCCRULE_RPT,                                           /* AutoTag[LKW5W9PCRR01:PDP Context Numbers of Supporting PCC Rules Reporting](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_VOIP_INSIGHT_REPORTING_PDP_NUM,                        /* AutoTag[LKW5WPVOIR01:PDP Context Numbers of Supporting VOIP Insight Reporting](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_WEB_SQI_INSIGHT_REPORTING_PDP_NUM,                     /* AutoTag[LKW5WPWSQR01:PDP Context Numbers of Supporting Web Service Insight Reporting](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_CHR_NUM,                                               /* AutoTag[LKW5W9CHR01:PDP Context Numbers of Supporting Call History Record](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DDOS_PDP_NUM,                                          /* AutoTag[LKW5W9DDOS02:PDP Context Numbers of Supporting DDOS Attack Proof](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_IPSEC_NUM,                                             /* AutoTag[LKW5W9IPS02:PDP Context Numbers of Supporting IPSec](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SGSN_BLACK_WHITE_LIST_PDP_NUM,                         /* AutoTag[LKW5W9SBWL01:PDP Context Numbers of Supporting SGSN Black/White List](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DIRECT_TUNNEL_NUM,                                     /* AutoTag[LKW5W9DIRT01:PDP Context Numbers of Supporting Direct Tunnel](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_LITARGET_NUM,                                          /* AutoTag[LKW5W9LAWI02:PDP Context Numbers of Supporting Lawful Interception](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_VIRTUAL_APN_NUM,                                       /* AutoTag[LKW5W9VAPN02:PDP Context Numbers of Supporting Virtual APN](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_VIRTUAL_LACTAC_APN_NUM,                              /* AutoTag[LKW5WPLBSM01:PDP Contexts Numbers of Supporting Location-Based Service Management](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_APNALLIAS_PDP_NUM,                                     /* AutoTag[LKW5W9AAPN02:PDP Context Numbers of Supporting Alias APN](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_S4SGSN_NUM,                                            /* AutoTag[LKW5WPSS4A01:PDP Context Numbers of Supporting S4 Architecture](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_MULTISERV_PDP_NUM,                                     /* AutoTag[LKW5W9MAPN02:PDP Context Numbers of Supporting Multi-service APN](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_ANONYMOUS_ACC,                                         /* AutoTag[LKW5W9ANAC02:PDP Context Numbers of Supporting Anonymous Access](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_QCHAT_PDP_NUM,                                         /* AutoTag[LKW5W9PTOU02:PDP Context Numbers of Supporting PTT over UMTS](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SECONDPDP_NUM,                                         /* AutoTag[LKW5W9SACT01:PDP Context Numbers of Supporting Secondary Activation Initiated by User](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_ROUTING_BEHIND_MS,                                     /* AutoTag[LKW5W9RBMS02:PDP Context Numbers of Supporting Routing Behind MS](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_PLMN_ID_NUM,                                           /* AutoTag[LKW5W9PLMNE2:PDP Context Numbers of Supporting PLMN ID Extraction](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_RECLAIM_PDP_NUM,                                       /* AutoTag[LKW5W9REC02:PDP Context Numbers of Supporting Reclaim PDP Context](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DHCP_NUM,                                              /* AutoTag[LKW5W9DHCP02:PDP Context Numbers of Supporting DHCP Address Allocation](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_REFLECTION_RAT_NUM,                                    /* AutoTag[LKW5W9RUT02:PDP Context Numbers of Supporting Reflection of User Type](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_NETWORK_SECOND_ACTIVE_NUM,                             /* AutoTag[LKW5W9NISA02:PDP Context Numbers of Supporting Network Initiated Dedicated PDP/ Bearer Activation](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_NETWORK_SECOND_ACTIVE_EX1_NUM,                         /* AutoTag[LKW5WPNISA01:PDP Context Numbers of Supporting Network Initiated Dedicated PDP/Bearer Activation, Expansion 1](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_NETWORK_SECOND_ACTIVE_EX2_NUM,                         /* AutoTag[LKW5WPNISA02:PDP Context Numbers of Supporting Network Initiated Dedicated PDP/Bearer Activation, Expansion 2](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_TETHERING_DETECT,                                      /* AutoTag[LKW5W9TETH01:PDP Context Numbers of Supporting Identification of Tethering Subscribers](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_CM_ONESHOT_PDP_NUM,                                    /* AutoTag[LKW5W9RCIN01:PDP Context Numbers of Supporting Real-time Charging Information Notification](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_LOCAL_LOCATION_REPORT_NUM,                             /* AutoTag[LKW5W9RTLR01:PDP Context Numbers of Supporting Real-Time Subscriber Location Reporting](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_NW_LINK_PDP_NUM,                                       /* AutoTag[LKW5W9UCQD01:PDP Context Numbers of Supporting User Connection Quality Detection](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_NW_QUERY_PDP_NUM,                                      /* AutoTag[LKW5W9NUII01:PDP Context Numbers of Supporting Networker User Information Inquiry](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_FPI_NUM,                                               /* AutoTag[LKW5W9WOFP01:PDP Context Numbers of Supporting Wireless Optimization Based on Flow Priority](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_CONGESTION_PDP_NUM,                                    /* AutoTag[LKW5W9WOCR01:PDP Context Numbers of Supporting Wireless Optimization Based on Cell Load Reporting](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_ADC_PDP_NUM,                                           /* AutoTag[LKW5W9ADCB01:PDP Context Numbers of Supporting Gx Enhanced for ADC Function](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_GATEWAY_SELECTION_PDP_NUM,                             /* AutoTag[LKW5W9GSSL01:PDP Context Numbers of Supporting Gateway Selection Based on System Loading](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_EMC_PDP_NUM,                                           /* AutoTag[LKW5W9ECAL01:PDP Context Numbers of Supporting VoLTE Emergency Call](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_VVOI_PDP_NUM,                                          /* AutoTag[LKW5WPVVLE01:PDP Context Numbers of Supporting VIP Voice VoLTE](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_TCP_OPTIMIZATION,                                      /* AutoTag[LKW5W9TCPO01:PDP Context Numbers of Supporting TCP Optimization](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_IMS_RESTORATION_PDP_NUM,                               /* AutoTag[LKW5W9IMSR01:PDP Context Numbers of Supporting IMS Restoration for P-CSCF Failure](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_IPV6_PD_PDP_NUM,                                       /* AutoTag[LKW5W9V6PD01:PDP Context Numbers of Supporting IPv6 Prefix Delegation](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DHCPV6_PDP_NUM,                                        /* AutoTag[LKW5W9V6AA01:PDP Context Numbers of Supporting DHCPv6 Address Allocation](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_VIP_FUNC,                                              /* AutoTag[LKW5W9VPAP02:PDP Context Numbers of Supporting VIP Access Priority](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_COMMON_RESTRICT_FUNC,                                  /* AutoTag[LKW5W9DRNV02:PDP Context Numbers of Supporting Data Service Restriction to Non-VIP subscribers](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_LWHO_PDP_NUM,                                          /* AutoTag[LKW5WPHOLW01:PDP Context Numbers of Supporting Handover without Optimizations between LTE and WLAN](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_GGSN_SESSION_NUM,                                      /* AutoTag[LKW5W9BSG02:Session Numbers of Supporting Basic Software for GGSN](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SGW_SESSION_NUM,                                       /* AutoTag[LKW5W9BSW01:Session Numbers of Supporting Basic Software for S-GW](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_PGW_SESSION_NUM,                                       /* AutoTag[LKW5W9BSP01:Session Numbers of Supporting Basic Software for P-GW](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SPGW_SESSION_NUM,                                      /* AutoTag[LKW5W9BSWP1:Session Numbers of Supporting Basic Software for Integrated S-GW and P-GW](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_CONVERGENCE_SESSION_NUM,                               /* AutoTag[LKW5W9BSI01:Session Numbers of Supporting Basic Software for Integrated GGSN and S-GW and P-GW](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_BASIC_SESSION_NUM,                                 /* AutoTag[LKW5W9DBAS02:Session Numbers of Supporting SA-Basic](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_PIPELINE_CONCATENATION_SESSION,                        /* AutoTag[LKW5W9PIP01:Session Numbers of Supporting SA-HTTP Pipeline and WAP Concatenation](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_P2P_SESSION_NUM,                                   /* AutoTag[LKW5W9P2P01:Session Numbers of Supporting SA-P2P](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_VOIP_SESSION_NUM,                                  /* AutoTag[LKW5W9VOIP01:Session Numbers of Supporting SA-VOIP](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_IM_SESSION_NUM,                                    /* AutoTag[LKW5W9DPIM01:Session Numbers of Supporting SA-IM](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_NEW_WEBBROWSING_SESSION_NUM,                       /* AutoTag[LKW5W9WEBB04:Session Numbers of Supporting SA-Web Browsing](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_NEW_FILEACCESS_SESSION_NUM,                        /* AutoTag[LKW5W9DFAP04:Session Numbers of Supporting SA-File Access](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_NEW_STREAMING_SESSION_NUM,                         /* AutoTag[LKW5W9DSTM04:Session Numbers of Supporting SA-Streaming](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_STOCK_SESSION_NUM,                                 /* AutoTag[LKW5W9DSTK01:Session Numbers of Supporting SA-Stock](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_GAME_SESSION_NUM,                                  /* AutoTag[LKW5W9DGME01:Session Numbers of Supporting SA-Game](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_NEW_EMAIL_SESSION_NUM,                             /* AutoTag[LKW5W9DEMA02:Session Numbers of Supporting SA-Email](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_NEW_TUNNELING_SESSION_NUM,                         /* AutoTag[LKW5W9DTUN02:Session Numbers of Supporting SA-Tunneling](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_NEW_NETWORK_ADMIN_SESSION_NUM,                     /* AutoTag[LKW5W9DNAD04:Session Numbers of Supporting SA-Network Administration](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_REMOTECONNECT_SESSION_NUM,                         /* AutoTag[LKW5W9DRCE01:Session Numbers of Supporting SA-Remote Connectivity](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_NEW_DATABASE_SESSION_NUM,                          /* AutoTag[LKW5W9DDSE02:Session Numbers of Supporting SA-Database](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_NEW_NETWORK_STORAGE_SESSION_NUM,                   /* AutoTag[LKW5W9DNSR02:Session Numbers of Supporting SA-Network Storage](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_NEW_MOBILE_SESSION_NUM,                            /* AutoTag[LKW5W9DMOB04:Session Numbers of Supporting SA-Mobile](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_NEW_OTHER_SESSION_NUM,                             /* AutoTag[LKW5W9DOTR02:Session Numbers of Supporting SA-Others](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_REPORTING_RECORD_GENERATE_SESSION_NUM,                 /* AutoTag[LKW5WSSRRG01:Session Numbers of Supporting Reporting Record Generating](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_TCP_ID_SESSION_NUM,                                    /* AutoTag[LKW5W9TCPR01:Session Numbers of Supporting TCP Retransmission Identification](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_L7_SESSION_NUM,                                    /* AutoTag[LKW5W9L7TD01:Session Numbers of Supporting Layer 7 Traffic Discrimination](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_HSDPA_4M_SESSION,                                      /* AutoTag[LKW5WSHSDPA1:Session Numbers of Supporting HSDPA, 2M-4M](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_HSDPA_8M_SESSION,                                      /* AutoTag[LKW5WSHSDPA2:Session Numbers of Supporting HSDPA Expansion 1, 4M-8M](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_HSDPA_16M_SESSION,                                     /* AutoTag[LKW5WSHSDPA3:Session Numbers of Supporting HSDPA Expansion 2, 8M-16M](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_HSDPA_32M_SESSION,                                     /* AutoTag[LKW5WHSDPA05:Session Numbers of Supporting HSDPA Expansion 3, 16M-32M](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_HSDPA_48M_SESSION,                                     /* AutoTag[LKW5WHSDPA06:Session Numbers of Supporting HSDPA Expansion 4, 32M-48M](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_HSDPA_84M_SESSION,                                     /* AutoTag[LKW5WHSDPA07:Session Numbers of Supporting HSDPA Expansion 5, 48M-84M](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_HSDPA_168M_SESSION,                                    /* AutoTag[LKW5WHSDPA08:Session Numbers of Supporting HSDPA Expansion 6, 84M-168M](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_HSDPA_256M_SESSION,                                    /* AutoTag[LKW5WSHSDPA4:Session Numbers of Supporting HSPA+(DOWNLINK) 16M+](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_HSUPA_4M_SESSION,                                      /* AutoTag[LKW5WSHSUPA1:Session Numbers of Supporting HSUPA,2M-4M](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_HSUPA_8M_SESSION,                                      /* AutoTag[LKW5WSHSUPA2:Session Numbers of Supporting HSUPA Expansion 1, 4M-8M](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_HSUPA_12M_SESSION,                                     /* AutoTag[LKW5WHSUPA03:Session Numbers of Supporting HSUPA Expansion 2, 8M-12M](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_HSUPA_24M_SESSION,                                     /* AutoTag[LKW5WHSUPA04:Session Numbers of Supporting HSUPA Expansion 3, 12M-24M](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_HSUPA_256M_SESSION,                                    /* AutoTag[LKW5WSHSUPA3:Session Numbers of Supporting HSPA+(UPLINK) 8M+](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SCTP_SESSION_NUM,                                      /* AutoTag[LKW5WSSCTP01:Session Numbers of Supporting SCTP](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_PCC_FUNC_SESSION_NUM,                                  /* AutoTag[LKW5W9SPCC02:Session Numbers of Supporting PCC Basic Function](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_MS_INFO_CHANGE_CRTL_SESSION_NUM,                       /* AutoTag[LKW5W9PCRL01:Session Numbers of Supporting Policy control based on real-time location](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_INITIAL_LOCATION_SESSION,                              /* AutoTag[LKW5W9PBIL01:Session Numbers of Supporting Policy Control based on Initial Access Location](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SERVICE_AWARENESS_BWM_SESSION,                         /* AutoTag[LKW5W9TCSA02:Session Numbers of Supporting Traffic Control Based on Service Awareness](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_POLICY_CTRL_TRAFFIC_SESSION_NUM,                       /* AutoTag[LKW5W9PCBT01:Session Numbers of Supporting Policy control based on traffic](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_POLICY_CTRL_SERVICE_TRAFFIC_SESSION_NUM,               /* AutoTag[LKW5WSFPBS01:Session Numbers of Fair Usage Policy Control Based on Service Accumulate Traffic](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_WEB_PROXY_SESSION,                                     /* AutoTag[LKW5W9WEB01:Session Numbers of Supporting Web Proxy](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_CAPTIVE_PORTAL_SESSION,                                /* AutoTag[LKW5W9SCCP01:Session Numbers of Supporting Captive Portal](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SHAPING_SESSION,                                       /* AutoTag[LKW5W9SHAP01:Session Numbers of Supporting The service-based traffic shaping](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DIFFSV_SESSION_NUM,                                    /* AutoTag[LKW5W9DSER02:Session Numbers of Supporting Differentiated Services](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_QOS_BASED_ON_SERVICE_SESSION,                          /* AutoTag[LKW5W9QOS01:Session Numbers of Supporting QoS Control Based on Service](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_QOS_SESSION_NUM,                                       /* AutoTag[LKW5W9TCQS02:Session Numbers of Supporting Conversational Traffic Class QoS Service Bearing](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_LOCALQOS_SESSION_NUM,                                  /* AutoTag[LKW5W9LQOS01:Session Numbers of Supporting Local QoS Control](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SUP_EXTENDQCI_SESSION,                                 /* AutoTag[LKW5W9QCIE01:Session Numbers of Supporting QCI Extension](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_HEADENR_HHEN01_SESSION,                                /* AutoTag[LKW5W9HTTPE1:Session Numbers of Supporting HTTP header enrichment](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_HEADENR_ANTI_FRAUD_SESSION,                            /* AutoTag[LKW5W9HTTPE3:Session Numbers of Supporting HTTP Header Anti-Spoofing](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DNS_CHARGING_ANTI_SPOOFING_SESSION_NUM,                /* AutoTag[LKW5WSDNCA01:Session Numbers of Supporting DNS Charging Anti-Spoofing](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_HTTP_CHARGING_ANTI_SPOOFING_SESSION_NUM,               /* AutoTag[LKW5WSHPCA01:Session Numbers of Supporting HTTP Charging Anti-Spoofing](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DNS_ERRCODERED_SESSION_NUM,                            /* AutoTag[LKW5WSDNSO01:Session Numbers of Supporting DNS Overwriting](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_HTTP_ERRCODERED_SESSION_NUM,                           /* AutoTag[LKW5WSSHPR01:Session Numbers of Supporting Smart HTTP Redirection](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_HTTPS_SERVICE_IP_ADDRESS_PARSER_SESSION_NUM,           /* AutoTag[LKW5WSHSAP01:Session Numbers of Supporting HTTPS Service IP Address Parser](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_L7_QOS_ENF_SESSION_NUM,                            /* AutoTag[LKW5W9STQE02:Session Numbers of Supporting Service Triggered QOS Enforcement](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_IM_RESRC_CONTROL_FUN_SESSION,                          /* AutoTag[LKW5W9RCIM01:Session Numbers of Supporting IM Type Services Radio Resources Management](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_HEADEN_RTSP_SESSION_NUM,                               /* AutoTag[LKW5W9BRHE01:Session Numbers of Supporting Basic RTSP Header Enrichment](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_HEAT_PAY_SESSION_NUM,                                  /* AutoTag[LKW5W9HOT01:Session Numbers of Supporting Hot Billing](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_CON_PAY_SESSION_NUM,                                   /* AutoTag[LKW5W9BCC01:Session Numbers of Supporting Basic Content Based Charging](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DIAMETER_SESSION_NUM,                                  /* AutoTag[LKW5W9DOCH01:Session Numbers of Supporting Gy Interface Online Charging](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_CONVOLUME_SESSION_NUM,                                 /* AutoTag[LKW5WSVBCS01:Session Numbers of Supporting Volume Based Charging of Service](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_CONTIME_SESSION_NUM,                                   /* AutoTag[LKW5W9TBCS01:Session Numbers of Supporting Time-based Charging of Service](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_EVENT_CHARGING_SESSION,                                /* AutoTag[LKW5W9EBCS01:Session Numbers of Supporting Event Based Charging of Service](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_ASN_ROAMING_CHARGING_SESSION,                          /* AutoTag[LKW5W9ASNR02:Session Numbers of Supporting ASN roaming charging](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_COA_SESSION_NUM,                                       /* AutoTag[LKW5W9SCOA01:Session Numbers of Supporting CoA](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_OCS_ENVELOPE_SESSION_NUM,                              /* AutoTag[LKW5W9ENRE01:Session Numbers of Supporting Envelope Reporting](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_RADIUS_SESSION_NUM,                                    /* AutoTag[LKW5W9RADF01:Session Numbers of Supporting Radius](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_CM_CREDITPOOL_SESSION_NUM,                             /* AutoTag[LKW5W9CEPL01:Session Numbers of Supporting Credit Pooling](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_REFERER_CHARGE_SESSION_NUM,                            /* AutoTag[LKW5W9RUCF01:Session Numbers of Supporting Referer URL Charging](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_IPV6_SESSION_NUM,                                      /* AutoTag[LKW5W9IPV601:Session Numbers of Supporting IPv6](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_IPV6_SESSION_NUM,                                  /* AutoTag[LKW5W9V6DP01:Session Numbers of Supporting IPv6 SA](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_IPV6_DIAMETER_SESSION_NUM,                             /* AutoTag[LKW5W9V6OC01:Session Numbers of Supporting IPv6 Online Charging](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_IPV4V6_SESSION_NUM,                                    /* AutoTag[LKW5W9VDSA01:Session Numbers of Supporting IPv4v6 Dual Stack Access](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_LTE2UTRAN_SESSION_NUM,                                 /* AutoTag[LKW5W9LTEUT1:Session Numbers of Supporting Inter-RAT Mobility between LTE and GSM/UMTS](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_LTE2CDMA_SESSION_NUM,                                  /* AutoTag[LKW5W9LTEC01:Session Numbers of Supporting Handover without Optimizations between LTE and eHRPD](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_IMS_SESSION_NUM,                                       /* AutoTag[LKW5W9IMSA01:Session Numbers of Supporting IMS access](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SRVCC_SESSION_NUM,                                     /* AutoTag[LKW5WSRVCC01:Session Numbers of Supporting SRVCC](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_PMIP_SESSION_NUM,                                      /* AutoTag[LKW5W9PMIP01:Session Numbers of Supporting PMIP](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_L2TP_VPN_SESSION_NUM,                                  /* AutoTag[LKW5W9L2TP01:Session Numbers of Supporting L2TP VPN](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_PPP_OVER_GTP_SESSION_NUM,                              /* AutoTag[LKW5W9PPPG02:Session Numbers of Supporting PPP over GTP](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_MPLS_VPN_SESSION_NUM,                                  /* AutoTag[LKW5W9MPLS01:Session Numbers of Supporting MPLS VPN](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_CONTENT_FILTERING_SESSION_NUM,                         /* AutoTag[LKW5W9CNFL01:Session Numbers of Supporting URL Filtering Base Function](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_CF_TIMERANGE_SESSION_NUM,                              /* AutoTag[LKW5W9CFTM02:Session Numbers of Supporting Time Based URL Filtering](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_IPPM_SESSION_NUM,                                      /* AutoTag[LKW5W9IPPM02:Session Numbers of Supporting IP Performance Monitor](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_BASIC_RPT_SESSION,                                     /* AutoTag[LKW5W9BSTR01:Session Numbers of Supporting Basic Traffic Reporting](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SAMPLE_RPT_SESSION,                                    /* AutoTag[LKW5W9FSTR01:Session Numbers of Supporting Full Sampling for Reporting](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_BLOCKED_RPT_SESSION,                                   /* AutoTag[LKW5W9TTTR01:Session Numbers of Supporting Throttling Traffic Reporting](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_PCCRULE_RPT_SESSION,                                   /* AutoTag[LKW5W9PCRR02:Session Numbers of Supporting PCC Rules Reporting](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_VOIP_INSIGHT_REPORTING_SESSION_NUM,                    /* AutoTag[LKW5WSVOIR01:Session Numbers of Supporting VOIP Insight Reporting](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_WEB_SQI_INSIGHT_REPORTING_SESSION_NUM,                 /* AutoTag[LKW5WSWSQR01:Session Numbers of Supporting Web Service Insight Reporting](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_CHR_SESSION_NUM,                                       /* AutoTag[LKW5W9CHR02:Session Numbers of Supporting Call History Record](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DDOS_SESSION_NUM,                                      /* AutoTag[LKW5W9DDOS01:Session Numbers of Supporting DDOS Attack Proof](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_IPSEC_SESSION_NUM,                                     /* AutoTag[LKW5W9IPS01:Session Numbers of Supporting IPSec](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SGSN_BLACK_WHITE_LIST_SESSION_NUM,                     /* AutoTag[LKW5W9SBWL02:Session Numbers of Supporting SGSN Black/White List](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DIRECT_TUNNEL_SESSION_NUM,                             /* AutoTag[LKW5W9DIRT02:Session Numbers of Supporting Direct Tunnel](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_LITARGET_SESSION_NUM,                                  /* AutoTag[LKW5W9LAWI01:Session Numbers of Supporting Lawful Interception](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_VIRTUAL_APN_SESSION_NUM,                               /* AutoTag[LKW5W9VAPN01:Session Numbers of Supporting Virtual APN](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_VIRTUAL_LACTAC_APN_SESSION_NUM,                       /* AutoTag[LKW5WSLBSM01:Session Numbers of Supporting Location-Based Service Management](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_APNALLIAS_SESSION_NUM,                                 /* AutoTag[LKW5W9AAPN01:Session Numbers of Supporting Alias APN](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_S4SGSN_SESSION_NUM,                                    /* AutoTag[LKW5WSSS4A01:Session Numbers of Supporting S4 Architecture](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_MULTISERV_SESSION_NUM,                                 /* AutoTag[LKW5W9MAPN01:Session Numbers of Supporting Multi-service APN](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_ANONYMOUS_ACC_SESSION,                                 /* AutoTag[LKW5W9ANAC01:Session Numbers of Supporting Anonymous Access](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_QCHAT_SESSION_NUM,                                     /* AutoTag[LKW5W9PTOU01:Session Numbers of Supporting PTT over UMTS](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SECONDPDP_SESSION_NUM,                                 /* AutoTag[LKW5W9SACT02:Session Numbers of Supporting Secondary Activation Initiated by User](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_ROUTING_BEHIND_MS_SESSION,                             /* AutoTag[LKW5W9RBMS01:Session Numbers of Supporting Routing Behind MS](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_PLMN_ID_SESSION_NUM,                                   /* AutoTag[LKW5W9PLMNE1:Session Numbers of Supporting PLMN ID Extraction](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_RECLAIM_SESSION_NUM,                                   /* AutoTag[LKW5W9REC01:Session Numbers of Supporting Reclaim Bearer](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DHCP_SESSION_NUM,                                      /* AutoTag[LKW5W9DHCP01:Session Numbers of Supporting DHCP Address Allocation](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_REFLECTION_RAT_SESSION_NUM,                            /* AutoTag[LKW5W9RUT01:Session Numbers of Supporting Reflection of User Type](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_NETWORK_SECOND_ACTIVE_SESSION_NUM,                     /* AutoTag[LKW5W9NISA01:Session Numbers of Supporting Network Initiated Dedicated PDP/ Bearer Activation](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_PGW_PROXY_SESSION_NUM,                                 /* AutoTag[LKW5W9PROXY01:Session Numbers of Supporting PGW Proxy](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_NETWORK_SECOND_ACTIVE_EX1_SESSION_NUM,                 /* AutoTag[LKW5WSNISA01:Session Numbers of Supporting Network Initiated Dedicated PDP/Bearer Activation, Expansion 1](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_NETWORK_SECOND_ACTIVE_EX2_SESSION_NUM,                 /* AutoTag[LKW5WSNISA02:Session Numbers of Supporting Network Initiated Dedicated PDP/Bearer Activation, Expansion 2](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_TETHERING_DETECT_SESSION,                              /* AutoTag[LKW5W9TETH02:Session Numbers of Supporting Identification of Tethering Subscribers](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_CM_ONESHOT_SESSION_NUM,                                /* AutoTag[LKW5W9RCIN02:Session Numbers of Supporting Real-time Charging Information Notification](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_LOCAL_LOCATION_REPORT_SESSION_NUM,                     /* AutoTag[LKW5W9RTLR02:Session Numbers of Supporting Real-Time Subscriber Location Reporting](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_NW_LINK_SESSION_NUM,                                   /* AutoTag[LKW5W9UCQD02:Session Numbers of Supporting User Connection Quality Detection](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_NW_QUERY_SESSION_NUM,                                  /* AutoTag[LKW5W9NUII02:Session Numbers of Supporting Networker User Information Inquiry](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_FPI_SESSION_NUM,                                       /* AutoTag[LKW5W9WOFP02:Session Numbers of Supporting Wireless Optimization Based on Flow Priority](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_CONGESTION_SESSION_NUM,                                /* AutoTag[LKW5W9WOCR02:Session Numbers of Supporting Wireless Optimization Based on Cell Load Reporting](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_ADC_SESSION_NUM,                                       /* AutoTag[LKW5W9ADCB02:Session Numbers of Supporting Gx Enhanced for ADC Function](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_GATEWAY_SELECTION_SESSION_NUM,                         /* AutoTag[LKW5W9GSSL02:Session Numbers of Supporting Gateway Selection Based on System Loading](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_EMC_SESSION_NUM,                                       /* AutoTag[LKW5W9ECAL02:Session Numbers of Supporting VoLTE Emergency Call](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_VVOI_SESSION_NUM,                                      /* AutoTag[LKW5WSVVLE01:Session Numbers of Supporting VIP Voice VoLTE](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_TCP_OPTIMIZATION_SESSION,                              /* AutoTag[LKW5W9TCPO02:Session Numbers of Supporting TCP Optimization](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_IMS_RESTORATION_SESSION_NUM,                           /* AutoTag[LKW5W9IMSR02:Session Numbers of Supporting IMS Restoration for P-CSCF Failure](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_IPV6_PD_SESSION_NUM,                                   /* AutoTag[LKW5W9V6PD02:Session Numbers of Supporting IPv6 Prefix Delegation](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DHCPV6_SESSION_NUM,                                    /* AutoTag[LKW5W9V6AA02:Session Numbers of Supporting DHCPv6 Address Allocation](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_VIP_FUNC_SESSION,                                      /* AutoTag[LKW5W9VPAP01:Session Numbers of Supporting VIP Access Priority](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_COMMON_RESTRICT_FUNC_SESSION,                          /* AutoTag[LKW5W9DRNV01:Session Numbers of Supporting Data Service Restriction to Non-VIP subscribers](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_LWHO_SESSION_NUM,                                      /* AutoTag[LKW5WSHOLW01:Session Numbers of Supporting Handover without Optimizations between LTE and WLAN](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_MUTI_HPLMN,                                            /* AutoTag[LKW5W9HPLMN1:Numbers of Supporting Multiple Trusted HPLMN](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_ACTIVE_BOARD_NUM,                                      /* AutoTag[LKW5W9SPUR01:Numbers of Supporting SPU Redundancy Enhancement](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_NPE_SOLUTION_NUM,                                      /* AutoTag[LKW5W9NPES01:Numbers of NPE Solution](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_IPSQM_THROUGHPUT_NUM,                                  /* AutoTag[LKW5W9IPSQM1:Throughput of eNodeB Based IPSQM](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_MBMS_SESSION_NUM,                                      /* AutoTag[LKW5W9MBMS02:MBMS Session Numbers of Supporting eMBMS Base Function](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SBR_WHOLE_NUM,                                         /* AutoTag[LKW5W9TSBR01:Throughput of Service Based Routing](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_UGW_VOG_VDO_CACHE_PACING_THROUGHPUT,                   /* AutoTag[LKW5W9TBVO01:Throughput of Video Caching and Pacing](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_UGW_VOG_VDO_TC_BITRATE_ADAPTATION_THROUGHPUT,          /* AutoTag[LKW5W9VTBA01:Throughput of Video Transcoding and Bitrate Adaptation](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_UGW_VOG_VDO_SUBSCRIBER_TYPE_THROUGHPUT,                /* AutoTag[LKW5W9TBST01:Throughput of Video Optimization Based on Subscriber Type](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_UGW_VOG_VDO_CELL_LOAD_THROUGHPUT,                      /* AutoTag[LKW5W9TBCL01:Throughput of Video Optimization Based on Cell Load](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_UGW_THROUGHPUT_NUM,                                    /* AutoTag[LKW5W9THP01:Throughput of Whole UGW](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_HARDWARE_NUM,                                          /* AutoTag[LKW5W9HRES01:Numbers of Hardware Resource](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_RADIUS_COPY,                                           /* AutoTag[LKW5W9RADC01:Supporting Radius Carbon-copy](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_LOAD_BALANCE_AAA_NUM,                                  /* AutoTag[LKW5W9LBAAA1:Supporting Load Balance for AAA](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_IPV6_NETWORKING,                                       /* AutoTag[LKW5W9V6NF01:Supporting IPv6 Networking on Gi/Sgi](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SNMP,                                                  /* AutoTag[LKW5W9SNMP01:Supporting SNMP](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_E2E_TRACE,                                             /* AutoTag[LKW5W9EEST01:Supporting E2E Subscriber Tracing](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_BFD,                                                   /* AutoTag[LKW5W9BFD01:Supporting BFD](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SUPPORTING_NULLMSISDN,                                 /* AutoTag[LKW5W9NUMD01:Supporting Null-MSISDN](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SUPPORTING_SIGNALING_PROXY,                            /* AutoTag[LKW5W9GPSP01:Supporting GGSN/PGW Signaling Proxy](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_HTTP_NUM,                                          /* AutoTag[LKW5W9HTTP02:PDP Context Numbers of Supporting SA-HTTP](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_FTP_NUM,                                           /* AutoTag[LKW5W9FTP02:PDP Context Numbers of Supporting SA-FTP](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_WAP_NUM,                                           /* AutoTag[LKW5W9WAP02:PDP Context Numbers of Supporting SA-WAP](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_RTSP_NUM,                                          /* AutoTag[LKW5W9RTSP02:PDP Context Numbers of Supporting SA-RTSP](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_MMS_NUM,                                           /* AutoTag[LKW5W9MMS02:PDP Context Numbers of Supporting SA-MMS](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_DNS_NUM,                                           /* AutoTag[LKW5W9DNS02:PDP Context Numbers of Supporting SA-DNS](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_SMTP_NUM,                                          /* AutoTag[LKW5W9SMTP02:PDP Context Numbers of Supporting SA-SMTP](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_POP3_NUM,                                          /* AutoTag[LKW5W9POP302:PDP Context Numbers of Supporting SA-POP3](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_IMAP_NUM,                                          /* AutoTag[LKW5W9IMAP02:PDP Context Numbers of Supporting SA-IMAP](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_TFTP_NUM,                                          /* AutoTag[LKW5W9TFTP02:PDP Context Numbers of Supporting SA-TFTP](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_MMSP_NUM,                                          /* AutoTag[LKW5W9MMSP02:PDP Context Numbers of Supporting SA-MMSP](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_BLACKBERRY_NUM,                                    /* AutoTag[LKW5W9BLBE02:PDP Context Numbers of Supporting SA-BLACKBERRY](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_WEBBROWSING_NUM,                                   /* AutoTag[LKW5W9WEBB02:PDP Context Numbers of Supporting SA-Web Browsing](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_FILEACCESS_NUM,                                    /* AutoTag[LKW5W9DFAP02:PDP Context Numbers of Supporting SA-File Access Protocol](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_STREAMING_NUM,                                     /* AutoTag[LKW5W9DSTM02:PDP Context Numbers of Supporting SA-Streaming](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_EMAIL_NUM,                                         /* AutoTag[LKW5W9DWMA02:PDP Context Numbers of Supporting SA-Webmail](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_NETWORKADMIN_NUM,                                  /* AutoTag[LKW5W9DNAD02:PDP Context Numbers of Supporting SA-Network Administration](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_STORAGE_NUM,                                       /* AutoTag[LKW5W9DSTR02:PDP Context Numbers of Supporting SA-Storage](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_MOBILE_NUM,                                        /* AutoTag[LKW5W9DMOB02:PDP Context Numbers of Supporting SA-Mobile](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_MISC_NUM,                                          /* AutoTag[LKW5W9DMIC02:PDP Context Numbers of Supporting SA-MISC](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_PCC_NUM,                                               /* AutoTag[LKW5W9GX02:PDP Context Numbers of Supporting Gx/Gxc interface based dispatch](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_RPT_FLOW,                                              /* AutoTag[LKW5W9TRAR02:PDP Context Numbers of Supporting Traffic Reporting](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_RPT_PROTOCOL,                                          /* AutoTag[LKW5W9PROR02:PDP Context Numbers of Supporting Protocol Reporting](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_RPT_SUBSCRIBER_GENERAL,                                /* AutoTag[LKW5W9USER02:PDP Context Numbers of Supporting User Reporting](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_RPT_SPECIFIC_PROTOCOL,                                 /* AutoTag[LKW5W9DEPR02:PDP Context Numbers of Supporting Designated Protocol Reporting](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_RPT_SPECIFIC_SUBSCRIBER,                               /* AutoTag[LKW5W9DEUR02:PDP Context Numbers of Supporting Designated User Reporting](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_P2P_VOIP_TRAFFIC_CTRL_NUM,                             /* AutoTag[LKW5W9PVTC02:PDP Context Numbers of Supporting P2P/VoIP Traffic Control](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_HTTP_SESSION_NUM,                                  /* AutoTag[LKW5W9HTTP01:Session Numbers of Supporting SA-HTTP](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_FTP_SESSION_NUM,                                   /* AutoTag[LKW5W9FTP01:Session Numbers of Supporting SA-FTP](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_WAP_SESSION_NUM,                                   /* AutoTag[LKW5W9WAP01:Session Numbers of Supporting SA-WAP](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_RTSP_SESSION_NUM,                                  /* AutoTag[LKW5W9RTSP01:Session Numbers of Supporting SA-RTSP](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_MMS_SESSION_NUM,                                   /* AutoTag[LKW5W9MMS01:Session Numbers of Supporting SA-MMS](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_DNS_SESSION_NUM,                                   /* AutoTag[LKW5W9DNS01:Session Numbers of Supporting SA-DNS](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_SMTP_SESSION_NUM,                                  /* AutoTag[LKW5W9SMTP01:Session Numbers of Supporting SA-SMTP](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_POP3_SESSION_NUM,                                  /* AutoTag[LKW5W9POP301:Session Numbers of Supporting SA-POP3](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_IMAP_SESSION_NUM,                                  /* AutoTag[LKW5W9IMAP01:Session Numbers of Supporting SA-IMAP](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_TFTP_SESSION_NUM,                                  /* AutoTag[LKW5W9TFTP01:Session Numbers of Supporting SA-TFTP](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_MMSP_SESSION_NUM,                                  /* AutoTag[LKW5W9MMSP01:Session Numbers of Supporting SA-MMSP](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_BLACKBERRY_SESSION_NUM,                            /* AutoTag[LKW5W9BLBE01:Session Numbers of Supporting SA-BLACKBERRY](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_WEBBROWSING_SESSION_NUM,                           /* AutoTag[LKW5W9WEBB01:Session Numbers of Supporting SA-Web Browsing](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_FILEACCESS_SESSION_NUM,                            /* AutoTag[LKW5W9DFAP01:Session Numbers of Supporting SA-File Access Protocol](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_STREAMING_SESSION_NUM,                             /* AutoTag[LKW5W9DSTM01:Session Numbers of Supporting SA-Streaming](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_EMAIL_SESSION_NUM,                                 /* AutoTag[LKW5W9DWMA01:Session Numbers of Supporting SA-Webmail](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_NETWORKADMIN_SESSION_NUM,                          /* AutoTag[LKW5W9DNAD01:Session Numbers of Supporting SA-Network Administration](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_STORAGE_SESSION_NUM,                               /* AutoTag[LKW5W9DSTR01:Session Numbers of Supporting SA-Storage](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_MOBILE_SESSION_NUM,                                /* AutoTag[LKW5W9DMOB01:Session Numbers of Supporting SA-Mobile](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_MISC_SESSION_NUM,                                  /* AutoTag[LKW5W9DMIC01:Session Numbers of Supporting SA-MISC](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_PCC_SESSION_NUM,                                       /* AutoTag[LKW5W9GX01:Session Numbers of Supporting Gx/Gxc interface based dispatch](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_RPT_FLOW_SESSION,                                      /* AutoTag[LKW5W9TRAR01:Session Numbers of Supporting Traffic Reporting](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_RPT_PROTOCOL_SESSION,                                  /* AutoTag[LKW5W9PROR01:Session Numbers of Supporting Protocol Reporting](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_RPT_SUBSCRIBER_GENERAL_SESSION,                        /* AutoTag[LKW5W9USER01:Session Numbers of Supporting User Reporting](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_RPT_SPECIFIC_PROTOCOL_SESSION,                         /* AutoTag[LKW5W9DEPR01:Session Numbers of Supporting Designated Protocol Reporting](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_RPT_SPECIFIC_SUBSCRIBER_SESSION,                       /* AutoTag[LKW5W9DEUR01:Session Numbers of Supporting Designated User Reporting](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_P2P_VOIP_TRAFFIC_CTRL_SESSION_NUM,                     /* AutoTag[LKW5W9PVTC01:Session Numbers of Supporting P2P/VoIP Traffic Control](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DEDICATED_BEARER_NUM,                                  /* AutoTag[LKW5W9DEBE01:Session Numbers of Supporting Dedicated Bearer Based on Service Flow](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DIAMETER_PDP_NUM_GGSN,                                 /* AutoTag[LKW5NoDOC01:PDP Context Numbers of Supporting Gy interface online charging](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_OCS_ENVELOPE_REPORTING,                                /* AutoTag[LKW5NoENRP01:PDP Context Numbers of Supporting Envelope reporting](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_QOS_PDP_NUM_GGSN,                                      /* AutoTag[LKW5NoSCCT01:PDP Context Numbers of Supporting Conversational traffic class QoS service bearing](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SHAPING_GGSN,                                          /* AutoTag[LKW5BWM002:PDP Context Numbers of Supporting The service-based traffic shaping](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_IM_RESRC_CONTROL_FUN_GGSN,                             /* AutoTag[LKW5RRCIMS01:PDP Context Numbers of Supporting IM Type Services Radio Resources Management](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_RADIUS_FUN_PDP_NUM_GGSN,                               /* AutoTag[LKW5RADIUS01:PDP Context Numbers of Supporting Radius](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_COA_NUM_GGSN,                                          /* AutoTag[LKW5NOCOA01:PDP Context Numbers of Supporting CoA](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_INITIAL_LOCATION_GGSN,                                 /* AutoTag[LKW5PCBOIL01:PDP Context Numbers of Supporting Policy control based on initial location](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_IPSEC_NUM_GGSN,                                        /* AutoTag[LKW5NoIPSE01:PDP Context Numbers of Supporting IPSec](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_LITARGET_NUM_GGSN,                                     /* AutoTag[LKW5NoLAWI01:PDP Context Numbers of Supporting Lawful Interception](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_VIRTUAL_APN_NUM_GGSN,                                  /* AutoTag[LKW5NoVAPN01:PDP Context Numbers of Supporting Virtual APN](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_APNALLIAS_PDP_NUM_GGSN,                                /* AutoTag[LKW5NoAAPN01:PDP Context Numbers of Supporting Alias APN](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_MULTISERV_GGSN,                                        /* AutoTag[LKW5MSAPN01:PDP Context Numbers of Supporting Multi-service APN](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_MULTIPLE_HPLMN_GGSN,                                   /* AutoTag[LKW5MHPLMN01:Support Multiple Trusted HPLMN](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_HSDPA_4M_GGSN,                                         /* AutoTag[LKW5NHSDPA04:PDP Context Numbers of Supporting HSDPA, 2M-4M](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_HSDPA_8M_GGSN,                                         /* AutoTag[LKW5NHSDPA06:PDP Context Numbers of Supporting HSDPA Expansion 1, 4M-8M](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_HSDPA_16M_GGSN,                                        /* AutoTag[LKW5NHSDPA08:PDP Context Numbers of Supporting HSDPA Expansion 2, 8M-16M](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_HSUPA_4M_GGSN,                                         /* AutoTag[LKW5NHSUPA04:PDP Context Numbers of Supporting HSUPA, 2M-4M](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_HSUPA_8M_GGSN,                                         /* AutoTag[LKW5NHSUPA06:PDP Context Numbers of Supporting HSUPA Expansion 1, 4M-8M](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_MBMS_SESSION_NUM_GGSN,                                 /* AutoTag[LKW5NoMBMS01:Bear Context Numbers of Supporting MBMS](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DDOS_PDP_NUM_GGSN,                                     /* AutoTag[LKW5NoDDOS01:PDP Context Numbers of Supporting DDOS Attack Proof](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_PCC_NUM_GGSN,                                          /* AutoTag[LKW5PCC01:PDP Context Numbers of Supporting Gx interface](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_MS_INFO_CHANGE_CRTL_GGSN,                              /* AutoTag[LKW5RTLPCO01:PDP Context Numbers of Supporting Policy control based on real-time location](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_RPT_FLOW_GGSN,                                         /* AutoTag[LKW5RPT01:PDP Context Numbers of Supporting Traffic reporting](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_RPT_PROTOCOL_GGSN,                                     /* AutoTag[LKW5RPT02:PDP Context Numbers of Supporting Protocol reporting](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_RPT_SUBSCRIBER_GENERAL_GGSN,                           /* AutoTag[LKW5RPT03:PDP Context Numbers of Supporting User reporting](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_RPT_SPECIFIC_PROTOCOL_GGSN,                            /* AutoTag[LKW5RPT04:PDP Context Numbers of Supporting Designated Protocol reporting](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_RPT_SPECIFIC_SUBSCRIBER_GGSN,                          /* AutoTag[LKW5RPT05:PDP Context Numbers of Supporting Designated User reporting](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DIRECT_TUNNEL_GGSN,                                    /* AutoTag[LKW5NODT02:PDP Context Numbers of Supporting Direct Tunnel](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_IPV6_NUM_GGSN,                                         /* AutoTag[LKW5IPV601:PDP Context Numbers of Supporting IPV6 PDP Context](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_HSDPA_256M_GGSN,                                       /* AutoTag[LKW5NHSDPA10:PDP Context Numbers of Supporting HSPA+(DOWNLINK)  16M+](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_HSUPA_256M_GGSN,                                       /* AutoTag[LKW5NHSUPA08:PDP Context Numbers of Supporting HSPA+(UPLINK)  8M+](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_ROUTING_BEHIND_MS_RES_GGSN,                            /* AutoTag[LKW5RBMS02:PDP Context Numbers of Supporting Routing Behind MS](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_QCHAT_GGSN,                                            /* AutoTag[LKW5SPTT01:PDP Context Numbers of Supporting PTT over UMTS](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_VIP_FUNC_GGSN,                                         /* AutoTag[LKW5SVIPAP01:PDP Context Numbers of Supporting VIP Access Priority](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_COMMON_RESTRICT_FUNC_GGSN,                             /* AutoTag[LKW5NVIPDR01:PDP Context Numbers of Supporting Data Service Restriction to Non-VIP subscribers](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SECONDPDP_NUM_GGSN,                                    /* AutoTag[LKW5NoSECA01:PDP Context Numbers of Supporting Secondary Activation Initiated by User](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_PPP_OVER_GTP_GGSN,                                     /* AutoTag[LKW5PPPB01:PDP Context Numbers of Supporting PPP over GTP](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_LOCALQOS_PDP_NUM_GGSN,                                 /* AutoTag[LKW5NoLQOS01:PDP Context Numbers of Supporting Local QoS Control](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_L2TP_VPN_PDP_NUM_GGSN,                                 /* AutoTag[LKW5NoL2TP01:PDP Context Numbers of Supporting L2TP VPN](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DIFFSV_PDP_NUM_GGSN,                                   /* AutoTag[LKW5NoDSER01:PDP Context Numbers of Supporting Differentiated Services](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_WHOLE_GGSN_NUM_GGSN,                                   /* AutoTag[LKW5ToGGSN02:Throughput of Whole GGSN(Mbps)](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_HARDWARE_NUM_GGSN,                                     /* AutoTag[LKW5HPDP01:Hardware Resource Numbers](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SNMP_FUNC_GGSN,                                        /* AutoTag[LKW5SNMP01:Supporting SNMP](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_RECLAIM_PDP_GGSN,                                      /* AutoTag[LKW5RPDP01:Supporting Reclaim PDPs](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_RADIUS_COPY_GGSN,                                      /* AutoTag[LKW5RM01:Supporting Radius Carbon-copy](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_REFLECTION_OF_RAN_TYPE_GGSN,                           /* AutoTag[LKW5RFRAN01:Supporting Reflection of User Type](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_PCC_TRAFFIC_GGSN,                                      /* AutoTag[LKW5PCBT01:Supporting Policy control based on traffic](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_IPV6_BASIC_FUNC_GGSN,                                  /* AutoTag[LKW5IPV602:Supporting IPV6 Networking Function](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_IMS_ACC_GGSN,                                          /* AutoTag[LKW5IMS01:Supporting IMS access](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_LOAD_BALANCE_FOR_AAA_GGSN,                             /* AutoTag[LKW5LBAAA01:Supporting Load Balance for AAA](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_BFD_GGSN,                                              /* AutoTag[LKW5BFD01:Supporting BFD](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_ANONYMOUS_ACC_GGSN,                                    /* AutoTag[LKW5AAS01:Supporting Anonymous Access](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_MPLS_VPN_GGSN,                                         /* AutoTag[LKW5MVPN01:Supporting MPLS VPN](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_CHR_FUNC_GGSN,                                         /* AutoTag[LKW5CHR01:Supporting Call History Record](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_PLMN_ID_EXTRATION_GGSN,                                /* AutoTag[LKW5PLMNIE01:Supporting PLMN ID Extraction](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SGSN_BLACK_WHITE_LIST_GGSN,                            /* AutoTag[LKW5SGSNBW01:Supporting SGSN Black/White List](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_ASN_ROAMING_CHARGE_GGSN,                               /* AutoTag[LKW5ASNRC01:Supporting ASN roaming charging](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DHCP_ADDRESS_ALLOCATION_GGSN,                          /* AutoTag[LKW5DHCPA01:Supporting DHCP Address Allocation](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_HSUPA_NUM_GGSN,                                        /* AutoTag[LKW5NHSUPA01:PDP Context Numbers of Supporting HSUPA](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_HSDPA_NUM_GGSN,                                        /* AutoTag[LKW5NHSDPA01:PDP Context Numbers of Supporting HSDPA](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_ROUTING_BEHIND_MS_FUN_GGSN,                            /* AutoTag[LKW5RBMS01:Supporting Routing Behind MS](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_CON_PAY_NUM_GGSN,                                      /* AutoTag[LKW5NoBCBC01:PDP Context Numbers of Supporting Basic Content Based Billing](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_HTTP_NUM_GGSN,                                     /* AutoTag[LKW5NoHTTP01:PDP Context Numbers of Supporting SA-HTTP](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_FTP_NUM_GGSN,                                      /* AutoTag[LKW5NoFTP01:PDP Context Numbers of Supporting SA-FTP](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_WAP_NUM_GGSN,                                      /* AutoTag[LKW5NoWAP01:PDP Context Numbers of Supporting SA-WAP](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_RTSP_NUM_GGSN,                                     /* AutoTag[LKW5NoRTSP01:PDP Context Numbers of Supporting SA-RTSP](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_MMS_NUM_GGSN,                                      /* AutoTag[LKW5NoMMS01:PDP Context Numbers of Supporting SA-MMS](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_DNS_NUM_GGSN,                                      /* AutoTag[LKW5NoDNS01:PDP Context Numbers of Supporting SA-DNS](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_PIPELINE_CONCATENATION_GGSN,                           /* AutoTag[LKW5NoHPWC01:PDP Context Numbers of Supporting SA-HTTP Pipeline and WAP Concatenation](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_L7_NUM_GGSN,                                       /* AutoTag[LKW5NoL7TD01:PDP Context Numbers of Supporting Layer 7 traffic discrimination](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_SMTP_NUM_GGSN,                                     /* AutoTag[LKW5NoSMTP01:PDP Context Numbers of Supporting SA-SMTP](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_POP3_NUM_GGSN,                                     /* AutoTag[LKW5NoPOP301:PDP Context Numbers of Supporting SA-POP3](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_IMAP_NUM_GGSN,                                     /* AutoTag[LKW5NoIMAP01:PDP Context Numbers of Supporting SA-IMAP](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_TFTP_NUM_GGSN,                                     /* AutoTag[LKW5NoTFTP01:PDP Context Numbers of Supporting SA-TFTP](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_MMSP_NUM_GGSN,                                     /* AutoTag[LKW5NoMMSP01:PDP Context Numbers of Supporting SA-MMSP](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_P2P_NUM_GGSN,                                      /* AutoTag[LKW5NoP2P01:PDP Context Numbers of Supporting SA-P2P](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_VOIP_NUM_GGSN,                                     /* AutoTag[LKW5NoVOIP01:PDP Context Numbers of Supporting SA-VOIP](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_BLACKBERRY_NUM_GGSN,                               /* AutoTag[LKW5NoBKBY01:PDP Context Numbers of Supporting SA-BLACKBERRY](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_IM_NUM_GGSN,                                       /* AutoTag[LKW5NoIM01:PDP Context Numbers of Supporting SA-IM](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_WEBBROWSING_NUM_GGSN,                              /* AutoTag[LKW5DPIWBR01:PDP Context Numbers of Supporting SA-Web Browsing](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_FILEACCESS_NUM_GGSN,                               /* AutoTag[LKW5DPIFAP01:PDP Context Numbers of Supporting SA-File Access Protocol](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_STREAMING_NUM_GGSN,                                /* AutoTag[LKW5DPISTM01:PDP Context Numbers of Supporting SA-Streaming](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_STOCK_NUM_GGSN,                                    /* AutoTag[LKW5DPISTK01:PDP Context Numbers of Supporting SA-Stock](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_GAME_NUM_GGSN,                                     /* AutoTag[LKW5DPIGAM01:PDP Context Numbers of Supporting SA-Game](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_EMAIL_NUM_GGSN,                                    /* AutoTag[LKW5DPIWMA01:PDP Context Numbers of Supporting SA-Webmail](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_NETWORKADMIN_NUM_GGSN,                             /* AutoTag[LKW5DPINAD01:PDP Context Numbers of Supporting SA-Network Administration](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_REMOTECONNECT_NUM_GGSN,                            /* AutoTag[LKW5DPIRCE01:PDP Context Numbers of Supporting SA-Remote Connectivity](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_STORAGE_NUM_GGSN,                                  /* AutoTag[LKW5DPISTR01:PDP Context Numbers of Supporting SA-Storage](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_MOBILE_NUM_GGSN,                                   /* AutoTag[LKW5DPIMOB01:PDP Context Numbers of Supporting SA-Mobile](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_DPI_MISC_NUM_GGSN,                                     /* AutoTag[LKW5DPIMIS01:PDP Context Numbers of Supporting SA-MISC](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_WEB_PROXY_GGSN,                                        /* AutoTag[LKW5NoSCWP01:PDP Context Numbers of Supporting Web proxy](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_CAPTIVE_PORTAL_GGSN,                                   /* AutoTag[LKW5NoSCCP01:PDP Context Numbers of Supporting Captive portal](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_QOS_CONTROL_BASED_ON_SERVICE_GGSN,                     /* AutoTag[LKW5NoSCQC01:PDP Context Numbers of Supporting QoS control based on service](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_BWM_NUM_GGSN,                                          /* AutoTag[LKW5BWM001:PDP Context Numbers of Supporting P2P/VoIP Traffic Control](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_HEADENR_HHEN01_GGSN,                                   /* AutoTag[LKW5HHEN01:PDP Context Numbers of Supporting HTTP Header Enrichment](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_TCP_RETRAN_GGSN,                                       /* AutoTag[LKW5TCPRETR01:Supporting TCP retransmission identification](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SCCG_NUM,                                              /* AutoTag[LKW5SGBSSG01:Session Numbers of Supporting Basic Software for EPSN](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SCCG_GUL,                                              /* AutoTag[LKW5SGGAPD01:Session Numbers of Supporting GGSN and PGW Deployment](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SCCG_BRAS,                                             /* AutoTag[LKW5SGDSLA01:Session Numbers of Supporting Fixed Network DSL Deployment](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SCCG_SA_BASIC_SESSION_NUM,                             /* AutoTag[LKW5SGSABA01:Session Numbers of Supporting SA-Basic](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SCCG_SA_WEBBROWSING_SESSION_NUM,                       /* AutoTag[LKW5SGSAWB01:Session Numbers of Supporting SA-Web Browsing](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SCCG_PIPELINE_CONCATENATION_SESSION,                   /* AutoTag[LKW5SGSAHW01:Session Numbers of Supporting SA-HTTP Pipeline and WAP Concatenation](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SCCG_SA_P2P_SESSION_NUM,                               /* AutoTag[LKW5SGSP2P01:Session Numbers of Supporting SA-P2P](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SCCG_SA_VOIP_SESSION_NUM,                              /* AutoTag[LKW5SGVOIP01:Session Numbers of Supporting SA-VOIP](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SCCG_SA_IM_SESSION_NUM,                                /* AutoTag[LKW5SGSAIM01:Session Numbers of Supporting SA-IM](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SCCG_SA_FILEACCESS_SESSION_NUM,                        /* AutoTag[LKW5SGFILE01:Session Numbers of Supporting SA-File Access](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SCCG_SA_STREAMING_SESSION_NUM,                         /* AutoTag[LKW5SGSASM01:Session Numbers of Supporting SA-Streaming](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SCCG_SA_STOCK_SESSION_NUM,                             /* AutoTag[LKW5SGSASK01:Session Numbers of Supporting SA-Stock](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SCCG_SA_GAME_SESSION_NUM,                              /* AutoTag[LKW5SGSAGM01:Session Numbers of Supporting SA-Game](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SCCG_SA_EMAIL_SESSION_NUM,                             /* AutoTag[LKW5SGEMIL01:Session Numbers of Supporting SA-Email](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SCCG_SA_TUNNELING_SESSION_NUM,                         /* AutoTag[LKW5SGTUNL01:Session Numbers of Supporting SA-Tunneling](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SCCG_SA_NETWORK_ADMIN_SESSION_NUM,                     /* AutoTag[LKW5SGNEAD01:Session Numbers of Supporting SA-Network Administration](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SCCG_SA_REMOTECONNECT_SESSION_NUM,                     /* AutoTag[LKW5SGRECO01:Session Numbers of Supporting SA-Remote Connectivity](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SCCG_SA_DATABASE_SESSION_NUM,                          /* AutoTag[LKW5SGDATA01:Session Numbers of Supporting SA-Database](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SCCG_SA_NETWORK_STORAGE_SESSION_NUM,                   /* AutoTag[LKW5SGNESR01:Session Numbers of Supporting SA-Network Storage](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SCCG_SA_MOBILE_SESSION_NUM,                            /* AutoTag[LKW5SGMOBL01:Session Numbers of Supporting SA-Mobile](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SCCG_SA_OTHER_SESSION_NUM,                             /* AutoTag[LKW5SGOTHR01:Session Numbers of Supporting SA-Others](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SCCG_REPORTING_RECORD_GENERATE_SESSION_NUM,            /* AutoTag[LKW5SGSRRG01:Session Numbers of Supporting Reporting Record Generating](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SCCG_TCP_ID_SESSION_NUM,                               /* AutoTag[LKW5SGTPRI01:Session Numbers of Supporting TCP Retransmission Identification](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SCCG_SA_L7_SESSION_NUM,                                /* AutoTag[LKW5SGL7TS01:Session Numbers of Supporting Layer 7 Traffic Statisitics](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SCCG_SCTP_NUM,                                         /* AutoTag[LKW5ENSCTP01:Session Numbers of Supporting SCTP](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SCCG_PCC_NUM,                                          /* AutoTag[LKW5SGPCCS01:Session Numbers of Supporting PCC Basic Function](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SCCG_INITIAL_LOCATION_SESSION,                         /* AutoTag[LKW5SGPCAL01:Session Numbers of Supporting Policy Control Based on Initial Access Location](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SCCG_SERVICE_AWARENESS_BWM_SESSION,                    /* AutoTag[LKW5SGTCSA01:Session Numbers of Supporting Traffic Control Based on Service Awareness](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SCCG_POLICY_CTRL_TRAFFIC_SESSION_NUM,                  /* AutoTag[LKW5SGPCBT01:Session Numbers of Supporting Policy Control Based on Traffic](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SCCG_POLICY_CTRL_SERVICE_TRAFFIC_SESSION_NUM,          /* AutoTag[LKW5SGPBSA01:Session Numbers of Fair Usage Policy Control Based on Service Accumulate Traffic](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SCCG_WEB_PROXY_SESSION,                                /* AutoTag[LKW5SGWEBP01:Session Numbers of Supporting Web Proxy](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SCCG_CAPTIVE_PORTAL_SESSION,                           /* AutoTag[LKW5SGCPPT01:Session Numbers of Supporting Captive Portal](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SCCG_SHAPPING,                                         /* AutoTag[LKW5SGSBTS01:Session Numbers of Supporting Service-based Traffic Shaping](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SCCG_HEADENR_HHEN01_SESSION,                           /* AutoTag[LKW5SGHPHE01:Session Numbers of Supporting HTTP Header Enrichment](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SCCG_HEADEN_RTSP_SESSION_NUM,                          /* AutoTag[LKW5SGRPHE01:Session Numbers of Supporting Basic RTSP Header Enrichment](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SCCG_HEADENR_ANTI_FRAUD_SESSION,                       /* AutoTag[LKW5SGHHAS01:Session Numbers of Supporting HTTP Header Anti-Spoofing](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SCCG_DNS_CHARGING_ANTI_CHARGING_SPOOFING_SESSION_NUM,  /* AutoTag[LKW5SGDNCA01:Session Numbers of Supporting DNS Charging Anti-Spoofing](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SCCG_HTTP_CHARGING_ANTI_SPOOFING_SESSION_NUM,          /* AutoTag[LKW5SGHPCA01:Session Numbers of Supporting HTTP Charging Anti-Spoofing](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SCCG_DNS_ERRCODERED_SESSION_NUM,                       /* AutoTag[LKW5SGDNSC01:Session Numbers of Supporting DNS Overwriting](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SCCG_HTTP_ERRCODERED_SESSION_NUM,                      /* AutoTag[LKW5SGHPCO01:Session Numbers of Supporting Smart HTTP Redirection](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_EPSN_HTTPS_SERVICE_IP_ADDRESS_PARSER_SESSION_NUM,      /* AutoTag[LKW5ENHSAP01:Session Numbers of Supporting HTTPS Service IP Address Parser](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SCCG_CON_PAY_SESSION_NUM,                              /* AutoTag[LKW5SGBFCG01:Session Numbers of Supporting Basic Flow-based Charging](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SCCG_DIAMETER_NUM,                                     /* AutoTag[LKW5SGGIOC01:Session Numbers of Supporting Gy Interface Online Charging](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SCCG_CONVOLUME_SESSION_NUM,                            /* AutoTag[LKW5SGVBCS01:Session Numbers of Supporting Volume Based Charging of Service](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SCCG_CONTIME_SESSION_NUM,                              /* AutoTag[LKW5SGTBCS01:Session Numbers of Supporting Time-based Charging of Service](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SCCG_EVENT_CHARGING_SESSION,                           /* AutoTag[LKW5SGEBCS01:Session Numbers of Supporting Event-based Charging of Service](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SCCG_OCS_ENVELOPE_SESSION_NUM,                         /* AutoTag[LKW5SGENRE01:Session Numbers of Supporting Envelope Reporting](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SCCG_CM_CREDITPOOL_SESSION_NUM,                        /* AutoTag[LKW5SGCRPL01:Session Numbers of Supporting Credit Pooling](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SCCG_REFERER_CHARGE_SESSION_NUM,                       /* AutoTag[LKW5SGURLC01:Session Numbers of Supporting Referer URL Charging](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SCCG_IPV6_ACCESS_SESSION_NUM,                          /* AutoTag[LKW5ENP6UA01:Session Numbers of Supporting IPv6 User Access](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SCCG_IPV6_SA_SESSION_NUM,                              /* AutoTag[LKW5ENP6SA01:Session Numbers of Supporting IPv6 SA](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SCCG_IPV6_ONLINE_CHARGING_SESSION_NUM,                 /* AutoTag[LKW5ENP6OC01:Session Numbers of Supporting IPv6 Online Charging](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SCCG_IPV4V6_ACCESS_SESSION_NUM,                        /* AutoTag[LKW5EN46DS01:Session Numbers of Supporting IPv4v6 Dual Stack Access](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SCCG_URL_NUM,                                          /* AutoTag[LKW5SGBURF01:Session Numbers of Supporting Basic URL Filtering](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SCCG_CF_TIMERANGE_SESSION_NUM,                         /* AutoTag[LKW5SGTBUF01:Session Numbers of Supporting Time-based URL Filtering](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SCCG_BASIC_RPT_SESSION,                                /* AutoTag[LKW5SGBTRP01:Session Numbers of Supporting Basic Traffic Reporting](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SCCG_SAMPLE_RPT_SESSION,                               /* AutoTag[LKW5SGFSRP01:Session Numbers of Supporting Full Sampling for Reporting](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SCCG_BLOCKED_RPT_SESSION,                              /* AutoTag[LKW5SGTTRP01:Session Numbers of Supporting Throttling Traffic Reporting](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SCCG_PCCRULE_RPT_SESSION,                              /* AutoTag[LKW5SGPCRR01:Session Numbers of Supporting PCC Rules Reporting](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SCCG_VOIP_INSIGHT_REPORTING_SESSION_NUM,               /* AutoTag[LKW5ENVOIR01:Session Numbers of Supporting VOIP Insight Reporting](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SCCG_WEB_SQI_INSIGHT_REPORTING_SESSION_NUM,            /* AutoTag[LKW5ENWSQR01:Session Numbers of Supporting Web Service Insight Reporting](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SCCG_TETHERING_DETECT_SESSION,                         /* AutoTag[LKW5SGIDTS01:Session Numbers of Supporting Identification of Tethering Subscribers](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SCCG_CM_ONESHOT_SESSION_NUM,                           /* AutoTag[LKW5SGRCIN01:Session Numbers of Supporting Real-time Charging Information Notification](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SCCG_ADC_NUM,                                          /* AutoTag[LKW5SGADCF01:Session Numbers of Supporting Gx Enhanced for ADC Function](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SCCG_NPE_SOLUTION_NUM,                                 /* AutoTag[LKW5SGNPES01:Numbers of Supporting NPE Solution](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SCCG_THROUGHPUT_NUM,                                   /* AutoTag[LKW5SGTHRP01:Throughput of Whole EPSN](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SCCG_ROUTE,                                            /* AutoTag[LKW5SGTSBR01:Throughput of Service Based Routing](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_EPSN_VOG_VDO_CACHE_PACING_THROUGHPUT,                  /* AutoTag[LKW5ENTBVO01:Throughput of Video Caching and Pacing](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_EPSN_VOG_VDO_TC_BITRATE_ADAPTATION_THROUGHPUT,         /* AutoTag[LKW5ENVTBA01:Throughput of Video Transcoding and Bitrate Adaptation](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_EPSN_VOG_VDO_SUBSCRIBER_TYPE_THROUGHPUT,               /* AutoTag[LKW5ENTBST01:Throughput of Video Optimization Based on Subscriber Type](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_EPSN_VOG_VDO_CELL_LOAD_THROUGHPUT,                     /* AutoTag[LKW5ENTBCL01:Throughput of Video Optimization Based on Cell Load](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SCCG_TCP_OPTIMIZATION_SESSION,                         /* AutoTag[LKW5SGTCPO01:Session Numbers of Supporting TCP Optimization](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SCCG_POD_NUM,                                          /* AutoTag[LKW5SGPODS01:Session Numbers of Supporting Network Initiate User Deactivation Processing](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SCCG_MULTIPLE_HPLMN,                                   /* AutoTag[LKW5SGHLMN01:Numbers of Supporting Multiple Trusted HPLMN](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SCCG_SPU_ENCHANCE,                                     /* AutoTag[LKW5SGSPRE01:Numbers of Supporting SPU Redundancy Enhancement](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_SCCG_BFD,                                              /* AutoTag[LKW5SGSBFD01:Supporting BFD](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_RP_NUM,                                                 /* AutoTag[LKW5PN1XEV01:PPP Session Numbers of Supporting CDMA2000 1X/EVDO](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_1X_PPP_NUM,                                             /* AutoTag[LKW5PN1X1X01:PPP Session Numbers of Supporting CDMA2000 1X](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_EVDO_PPP_NUM,                                           /* AutoTag[LKW5PNEVDO01:PPP Session Numbers of Supporting CDMA2000 EVDO](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_EVDO_AUX_A10_NUM,                                       /* AutoTag[LKW5PNAA1001:A10 Connection Numbers of Supporting Auxiliary A10](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_MIP_NUM,                                                /* AutoTag[LKW5PNCMIP01:PPP Session Numbers of Supporting CMIPv4](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_PMIP_NUM,                                               /* AutoTag[LKW5PNPMIP01:PPP Session Numbers of Supporting PMIPv4](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_PRECHARGE_NUM,                                          /* AutoTag[LKW5PN3GPP01:PPP Session Numbers of Supporting 3GPP2 Packet Prepaid](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_LI_NUM,                                                 /* AutoTag[LKW5PNLFIP01:PPP Session Numbers of Supporting Lawful Interception](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_MPPC_PPP_NUM,                                           /* AutoTag[LKW5PNMPPC01:PPP Session Numbers of Supporting MPPC](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_TCPIP_PPP_NUM,                                          /* AutoTag[LKW5PNTIHC01:PPP Session Numbers of Supporting TCP/IP Header Compression](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_CHARGE_CONTENT_NUM,                                     /* AutoTag[LKW5PNBCBC01:PPP Session Numbers of Supporting Basic Content Based Charging](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_L7_TRAFFIC_DISCRIMINATION_NUM,                          /* AutoTag[LKW5PNL7TD01:PPP Session Numbers of Supporting Layer 7 Traffic Discrimination](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_CHARGE_BASED_TIME_NUM,                                  /* AutoTag[LKW5PNTBCS01:PPP Session Numbers of Supporting Time Based Charging of Service](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_CHARGE_DIAMETER_NUM,                                    /* AutoTag[LKW5PNGIOC01:PPP Session Numbers of Supporting Gy Interface Online Charging](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_TRAFFIC_CLASS_QOS_BEARING_PPP_NUM,                      /* AutoTag[LKW5PNQCBS01:PPP Session Numbers of Supporting QoS Control Based on Service](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_SERVICE_AND_BANDWITH_PPP_NUM,                           /* AutoTag[LKW5PNTCBS01:PPP Session Numbers of Supporting Traffic Control Based on Service Awareness](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_HTTPS_SERVICE_IP_ADDRESS_PARSER_PPP_NUM,                /* AutoTag[LKW5PNHSAP01:PPP Session Numbers of Supporting HTTPS Service IP Address Parser](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_CSN_FUNC,                                               /* AutoTag[LKW5PNSCSN01:PPP Session Numbers of Supporting CSN](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_COA_FUNC,                                               /* AutoTag[LKW5PNSCOA01:PPP Session Numbers of Supporting CoA](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_SERVICE_BASED_SHAPING_NUM,                              /* AutoTag[LKW5PNSBTS01:PPP Session Numbers of Supporting The Service-based Traffic Shaping](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_REDIRECT_CREDIT_EXHAUS_BASED_AAA_NUM,                   /* AutoTag[LKW5PNRCEA01:PPP Session Numbers of Supporting Redirection for Credit Exhaustion Based on AAA Interface](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_IPV6_PPP_NUM,                                           /* AutoTag[LKW5PNSIP601:PPP Session Numbers of Supporting SIPv6](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_HTTP_HEADER_ENRICH_NUM,                                 /* AutoTag[LKW5PNHPHE01:PPP Session Numbers of Supporting HTTP Header Enrichment](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_PCC_NUM,                                                /* AutoTag[LKW5PNPCCB01:PPP Session Numbers of Supporting PCC Basic Function](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_POLICY_CONTROL_BASED_TRAFFIC_NUM,                       /* AutoTag[LKW5PNPCBT01:PPP Session Numbers of Supporting Policy Control Based on Traffic](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_POLICY_CONTROL_BASED_ACCUMULATE_TRAFFIC_NUM,            /* AutoTag[LKW5PNFPBA01:PPP Session Numbers of Supporting Fair Usage Policy Control Based on Service Accumulate Traffic](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_USER_PRIORITY_PPP_NUM,                                  /* AutoTag[LKW5PNUPMS01:PPP Session Numbers of Supporting User Priority Management Based on Service](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_SA_WEB_BROWSING_NUM,                                    /* AutoTag[LKW5PNSAWB01:PPP Session Numbers of Supporting SA-Web Browsing](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_SA_HTTP_PIPELINE_AND_WAP_NUM,                           /* AutoTag[LKW5PNHPWC01:PPP Session Numbers of Supporting SA-HTTP Pipeline and WAP Concatenation](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_SA_P2P_NUM,                                             /* AutoTag[LKW5PNSAPP01:PPP Session Numbers of Supporting SA-P2P](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_SA_VOIP_NUM,                                            /* AutoTag[LKW5PNSAVP01:PPP Session Numbers of Supporting SA-VOIP](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_SA_IM_NUM,                                              /* AutoTag[LKW5PNSAIM01:PPP Session Numbers of Supporting SA-IM](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_SA_FILE_NUM,                                            /* AutoTag[LKW5PNSAFA01:PPP Session Numbers of Supporting SA-File Access](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_SA_STREAMING_NUM,                                       /* AutoTag[LKW5PNSASM01:PPP Session Numbers of Supporting SA-Streaming](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_SA_STOCK_NUM,                                           /* AutoTag[LKW5PNSATK01:PPP Session Numbers of Supporting SA-Stock](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_SA_GAME_NUM,                                            /* AutoTag[LKW5PNSAGM01:PPP Session Numbers of Supporting SA-Game](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_SA_EMAIL_NUM,                                           /* AutoTag[LKW5PNSAEL01:PPP Session Numbers of Supporting SA-Email](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_SA_NETWORK_ADMIN_NUM,                                   /* AutoTag[LKW5PNSANA01:PPP Session Numbers of Supporting SA-Network Administration](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_SA_REMOTE_CONNECT_NUM,                                  /* AutoTag[LKW5PNSARC01:PPP Session Numbers of Supporting SA-Remote Connectivity](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_SA_NETWORK_STORAGE_NUM,                                 /* AutoTag[LKW5PNSANS01:PPP Session Numbers of Supporting SA-Network Storage](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_SA_MOBILE_NUM,                                          /* AutoTag[LKW5PNSAMB01:PPP Session Numbers of Supporting SA-Mobile](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_SA_OTHERS_NUM,                                          /* AutoTag[LKW5PNSAOR01:PPP Session Numbers of Supporting SA-Others](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_USER_QOS_RATE_CTRL_PPP_NUM,                             /* AutoTag[LKW5PNUQRC01:PPP Session Numbers of Supporting User QoS and Rate Control](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_DM_PPP_NUM,                                             /* AutoTag[LKW5PNPSDM01:PPP Session Numbers of Supporting DM](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_MPLS_VPN_PPP_NUM,                                       /* AutoTag[LKW5PNMPLS01:PPP Session Numbers of Supporting MPLS VPN](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_VIRTUAL_DOMAIN_PPP_NUM,                                 /* AutoTag[LKW5PNVTDM01:PPP Session Numbers of Supporting Virtual Domain](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_TCP_RETRAS_IDENFIY_NUM,                                 /* AutoTag[LKW5PNTCRI01:PPP Session Numbers of Supporting TCP Retransmission Identification](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_IPV6_SA_NUM,                                            /* AutoTag[LKW5PNP6SA01:PPP Session Numbers of Supporting IPv6 SA](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_PMIPV6_PPP_NUM,                                         /* AutoTag[LKW5PNPMP601:PPP Session Numbers of Supporting PMIPv6](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_SA_BASIC_NUM,                                           /* AutoTag[LKW5PNSABA01:PPP Session Numbers of Supporting SA-Basic](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_SA_DATABASE_NUM,                                        /* AutoTag[LKW5PNSADB01:PPP Session Numbers of Supporting SA-Database](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_SA_TUNNELING_NUM,                                       /* AutoTag[LKW5PNSATL01:PPP Session Numbers of Supporting SA-Tunneling](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_IPSEC_NUM,                                              /* AutoTag[LKW5PNIPSC01:PPP Session Numbers of Supporting IPSec](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_IPV6_NET_ON_PIS2A_NUM,                                  /* AutoTag[LKW5PNPI2A01:PPP Session Numbers of Supporting IPv6 Networking on Pi/S2a](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_TCP_OPTIMIZATION_NUM,                                   /* AutoTag[LKW5PNTCPO01:PPP Session Numbers of Supporting TCP Optimization](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_HSGW_ITEM_EHRPD_PDN_NUM,                                          /* AutoTag[LKW5HWHRDA01:PDN Session Numbers of Supporting eHRPD Access](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_HSGW_ITEM_EHRPD_AUX_A10_NUM,                                      /* AutoTag[LKW5HWAA1001:A10 Connection Numbers of Supporting Auxiliary A10](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_HSGW_ITEM_EHRPD_CSN_FUN,                                          /* AutoTag[LKW5HWPCSN01:PDN Session Numbers of Supporting CSN](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_HSGW_ITEM_EHRPD_DUAL_STACK_PDN_NUM,                               /* AutoTag[LKW5HW46DS01:PDN Session Numbers of Supporting IPv4v6 Dual Stack Access](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_HSGW_ITEM_EHRPD_PCC_PDN_NUM,                                      /* AutoTag[LKW5HWPCCB01:PDN Session Numbers of Supporting PCC Basic Function](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_HSGW_ITEM_EHRPD_IPV6_NET_ON_PIS2A_NUM,                            /* AutoTag[LKW5HWPI2A01:PDN Session Numbers of Supporting IPv6 Networking on Pi/S2a](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_HSGW_ITEM_EHRPD_CL_HANDOVER_NUM,                                  /* AutoTag[LKW5HWHOLE01:PDN Session Numbers of Supporting Handover without Optimizations between LTE and eHRPD](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_HSGW_ITEM_EHRPD_NET_INIT_PDPACTIVE_NUM,                           /* AutoTag[LKW5HWNIDA01:PDN Session Numbers of Supporting Network Initiated Dedicated Bearer/PDP Activation](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_HSGW_ITEM_EHRPD_POLICY_CONTROL_BASED_REALTIME_LOCATION_NUM,       /* AutoTag[LKW5HWCBRL01:PDN Session Numbers of Supporting Policy Control Based on Real-time Location](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_HSGW_ITEM_EHRPD_QOS_BASED_USER_PRRORITY_NUM,                      /* AutoTag[LKW5HWQSUP01:PDN Session Numbers of Supporting QoS Based on User Priority](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_WHOLE_PDSN_THROUGHPUT,                                  /* AutoTag[LKW5PNTHPU01:Throughput of Whole PDSN](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_HSGW_ITEM_WHOLE_HSGW_THROUGHPUT,                                  /* AutoTag[LKW5HWTHPU01:Throughput of Whole HSGW](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_HSGW_ITEM_SCTP_HSGW_PDN_NUM,                                      /* AutoTag[LKW5HWSCTP01:PDN Session Numbers of Supporting SCTP](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_SUPPORT_MEID_FUNC,                                      /* AutoTag[LKW5PNMEID01:Supporting MEID](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_SUPPORT_BFD_FUNC,                                       /* AutoTag[LKW5PNSBFD01:Supporting BFD](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_HSGW_ITEM_SUPPORT_BFD_FUNC,                                       /* AutoTag[LKW5HWSBFD01:Supporting BFD](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_OLD_RP_NUM,                                             /* AutoTag[LKC7COM1XDO:PPP Session Numbers of Supporting CDMA2000 1X/EVDO](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_OLD_1X_PPP_NUM,                                         /* AutoTag[LKC7SYS01:PPP Session Numbers of Supporting CDMA2000 1X](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_OLD_EVDO_PPP_NUM,                                       /* AutoTag[LKC7CoEVDO01:PPP Session Numbers of Supporting CDMA2000 EVDO](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_OLD_EVDO_AUX_A10_NUM,                                   /* AutoTag[LKC7CoAA1001:Auxiliary A10 Connection Numbers of Supporting CDMA2000 EVDO](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_OLD_MIP_NUM,                                            /* AutoTag[LKC7MIPFA01:PPP Session Numbers of Supporting CMIP](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_OLD_PMIP_NUM,                                           /* AutoTag[LKC7PMIP01:PPP Session Numbers of Supporting PMIP](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_OLD_PRECHARGE_NUM,                                      /* AutoTag[LKC7PPS01:PPP Session Numbers of Supporting 3GPP2 Packet Prepaid](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_OLD_LI_NUM,                                             /* AutoTag[LKC7LI01:PPP Session Numbers of Supporting Lawful Interception](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_OLD_MPPC_PPP_NUM,                                       /* AutoTag[LKC7MPPC01:PPP Session Numbers of Supporting MPPC Compression](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_OLD_LZS_NUM,                                            /* AutoTag[LKC7LZS01:PPP Session Numbers of Supporting LZS Compression](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_OLD_TCPIP_PPP_NUM,                                      /* AutoTag[LKC7VJHC01:PPP Session Numbers of Supporting TCP/IP Header Compression](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_OLD_ROHC_AUX_A10_NUM,                                   /* AutoTag[LKC7ROHC01:Auxiliary A10 Connection Numbers of Supporting ROHC Compression](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_OLD_CHARGE_CONTENT_NUM,                                 /* AutoTag[LKC7NOBCBC01:PPP Session Numbers of Supporting Basic Content Based Charging](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_OLD_DPI_HTTP_NUM,                                       /* AutoTag[LKC7NOHTTP01:PPP Session Numbers of Supporting SA-HTTP](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_OLD_DPI_FTP_NUM,                                        /* AutoTag[LKC7NOFTP01:PPP Session Numbers of Supporting SA-FTP](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_OLD_DPI_WAP_NUM,                                        /* AutoTag[LKC7NOWAP01:PPP Session Numbers of Supporting SA-WAP](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_OLD_DPI_RTSP_NUM,                                       /* AutoTag[LKC7NORTSP01:PPP Session Numbers of Supporting SA-RTSP](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_OLD_DPI_MMS_NUM,                                        /* AutoTag[LKC7NOMMS01:PPP Session Numbers of Supporting SA-MMS](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_OLD_DPI_DNS_NUM,                                        /* AutoTag[LKC7NODNS01:PPP Session Numbers of Supporting SA-DNS](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_OLD_DPI_HTTP_AND_WAP_NUM,                               /* AutoTag[LKC7NOHPWC01:PPP Session Numbers of Supporting SA-HTTP Pipeline and WAP Concatenation](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_OLD_L7_TRAFFIC_DISCRIMINATION_NUM,                      /* AutoTag[LKC7NOL7TD01:PPP Session Numbers of Supporting Layer 7 Traffic Discrimination](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_OLD_CHARGE_BASED_TIME_NUM,                              /* AutoTag[LKC7NOTBCS01:PPP Session Numbers of Supporting Time Based Charging of Service](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_OLD_CHARGE_DIAMETER_NUM,                                /* AutoTag[LKC7NODOC01:PPP Session Numbers of Supporting Gy Interface Online Charging](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_OLD_DPI_SMTP_NUM,                                       /* AutoTag[LKC7DPSMTP01:PPP Session Numbers of Supporting SA-SMTP](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_OLD_DPI_POP3_NUM,                                       /* AutoTag[LKC7DPPOP301:PPP Session Numbers of Supporting SA-POP3](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_OLD_DPI_IMAP_NUM,                                       /* AutoTag[LKC7DPIMAP01:PPP Session Numbers of Supporting SA-IMAP](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_OLD_DPI_TFTP_NUM,                                       /* AutoTag[LKC7DPTFTP01:PPP Session Numbers of Supporting SA-TFTP](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_OLD_DPI_MMSP_NUM,                                       /* AutoTag[LKC7DPMMSP01:PPP Session Numbers of Supporting SA-MMSP](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_OLD_DPI_P2P_NUM,                                        /* AutoTag[LKC7DPIP2P01:PPP Session Numbers of Supporting SA-P2P](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_OLD_DPI_VOIP_NUM,                                       /* AutoTag[LKC7DPVOIP01:PPP Session Numbers of Supporting SA-VOIP](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_OLD_DPI_IM_NUM,                                         /* AutoTag[LKC7DPIIM01:PPP Session Numbers of Supporting SA-IM](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_OLD_DPI_BLACKBERRY_NUM,                                 /* AutoTag[LKC7DPBLBE01:PPP Session Numbers of Supporting SA-BLACKBERRY](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_OLD_TRAFFIC_CLASS_QOS_BEARING_PPP_NUM,                  /* AutoTag[LKC7TCQOSB01:PPP Session Numbers of Supporting QoS Control Based on Service](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_OLD_SERVICE_AND_BANDWITH_PPP_NUM,                       /* AutoTag[LKC7SCBWMA01:PPP Session Numbers of Supporting Bandwidth Management Based on Service](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_OLD_CSN_FUNC,                                           /* AutoTag[LKC7SUCSNF01:PPP Session Numbers of Supporting CSN](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_OLD_COA_FUNC,                                           /* AutoTag[LKC7S0COAF01:PPP Session Numbers of Supporting CoA](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_OLD_SERVICE_BASED_SHAPING_NUM,                          /* AutoTag[LKC7SHAPNG01:PPP Session Numbers of Supporting Shaping Based on Service](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_OLD_REDIRECT_CREDIT_EXHAUS_BASED_AAA_NUM,               /* AutoTag[LKC7S0UARF01:PPP Session Numbers of Supporting Redirection for Credit Exhaustion Based on AAA Interface](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_OLD_IPV6_PPP_NUM,                                       /* AutoTag[LKC7SOIPV601:PPP Session Numbers of Supporting IPv6](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_OLD_HTTP_HEADER_ENRICH_NUM,                             /* AutoTag[LKC7HTTPHE01:PPP Session Numbers of Supporting HTTP Header Enrichment](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_OLD_PCC_NUM,                                            /* AutoTag[LKC7GXIPCC01:PPP Session Numbers of Supporting Gx Interface PCC](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_OLD_POLICY_CONTROL_BASED_TRAFFIC_NUM,                   /* AutoTag[LKC7SPCBCT01:PPP Session Numbers of Supporting Policy Control Based on Cumulative Traffic](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_OLD_POLICY_CONTROL_BASED_ACCUMULATE_TRAFFIC_NUM,        /* AutoTag[LKC7SUPMBS01:PPP Session Numbers of Supporting User Priority Management Based on Service](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_OLD_DPI_WEB_BROWSING_NUM,                               /* AutoTag[LKC7DPIWBB01:PPP Session Numbers of Supporting SA-Web Browsing](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_OLD_DPI_FILE_ACCESS_NUM,                                /* AutoTag[LKC7DPIFAC01:PPP Session Numbers of Supporting SA-File Access](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_OLD_DPI_STREAMING_NUM,                                  /* AutoTag[LKC7DPISTM01:PPP Session Numbers of Supporting SA-Streaming](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_OLD_DPI_STOCK_NUM,                                      /* AutoTag[LKC7DPISTK01:PPP Session Numbers of Supporting SA-Stock](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_OLD_DPI_GAME_NUM,                                       /* AutoTag[LKC7DPIGME01:PPP Session Numbers of Supporting SA-Game](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_OLD_DPI_EMAIL_NUM,                                      /* AutoTag[LKC7DPIEML01:PPP Session Numbers of Supporting SA-Email](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_OLD_DPI_NET_ADMIN_NUM,                                  /* AutoTag[LKC7DPINAD01:PPP Session Numbers of Supporting SA-Network Administration](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_OLD_DPI_REMOTE_CONNECT_NUM,                             /* AutoTag[LKC7DPIREC01:PPP Session Numbers of Supporting SA-Remote Connectivity](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_OLD_DPI_STORAGE_NUM,                                    /* AutoTag[LKC7DPISTR01:PPP Session Numbers of Supporting SA-Storage](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_OLD_DPI_MOBILE_NUM,                                     /* AutoTag[LKC7DPIMOB01:PPP Session Numbers of Supporting SA-Mobile](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_OLD_DPI_OTHERS_NUM,                                     /* AutoTag[LKC7DPIOTH01:PPP Session Numbers of Supporting SA-Others](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_OLD_SYSTEM_TRACE_NUM,                                   /* AutoTag[LKC7SYSTRA01:PPP Session Numbers of Supporting System Tracing](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_OLD_USER_QOS_AND_RATE_CTRL_NUM,                         /* AutoTag[LKC7PSUQRC01:PPP Session Numbers of Supporting User QoS and Rate Control](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_OLD_DM_NUM,                                             /* AutoTag[LKC7PPPSDM01:PPP Session Numbers of Supporting DM](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_OLD_MPLS_VPN_NUM,                                       /* AutoTag[LKC7MPLVPN01:PPP Session Numbers of Supporting MPLS VPN](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_OLD_VIRTUAL_DOMAIN_NUM,                                 /* AutoTag[LKC7VDMAIN01:PPP Session Numbers of Supporting Virtual Domain](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_OLD_TCP_RETRAS_NUM,                                     /* AutoTag[LKC7TRANIF01:PPP Session Numbers of Supporting TCP Retransmission Identification](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_OLD_IPSEC_FUNCTION,                                     /* AutoTag[LKC7IPSec01:Supporting IPSec](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_OLD_SSL_FUNCTION,                                       /* AutoTag[LKC7SUPSSL01:Supporting SSL](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_OLD_SSH_FUNCTION,                                       /* AutoTag[LKC7SPOSSH01:Supporting SSH](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_OLD_BFD_FUNCTION,                                       /* AutoTag[LKC7SPOBFD01:Supporting BFD](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_PDSN_ITEM_OLD_MEID_FUNCTION,                                      /* AutoTag[LKC7SPMEID01:Supporting MEID](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */
    LICE_LIMIT_ITEM_HARDWARE_SPUF_NUM,                                     /* AutoTag[LKW5W9SPUF01:Numbers of extended service processing unit F](��?������??��?��2����?��y����??��|1??��,???�ꡤ?����D��2�����?�����???�㨮��???����??y����!) */

    LICE_LIMIT_ITEM_BUTT /* <=M_LIC_MAX_LIMIT_ITEM_NUM */
}ENUM_LICENSE;

typedef enum
{
    CKP_SUCC_0,
    CKP_SUCC_1,
    CKP_SUCC_2,
    CKP_SUCC_3,
    CKP_SUCC_4,
    CKP_SUCC_5,
    CKP_SUCC_6,
    CKP_SUCC_7,
    CKP_SUCC_8,
    CKP_SUCC_9,
    CKP_SUCC_10,
    CKP_SUCC_11,
    CKP_SUCC_12,
    CKP_SUCC_13,
    CKP_SUCC_14,
    CKP_SUCC_15,
    CKP_SUCC_16,
    CKP_SUCC_17,
    CKP_SUCC_18,
    CKP_SUCC_19,
    CKP_SUCC_20,
    CKP_SUCC_21,
    CKP_SUCC_22,
    CKP_SUCC_23,
    CKP_SUCC_24,
    CKP_SUCC_25,
    CKP_SUCC_26,
    CKP_SUCC_27,
    CKP_SUCC_28,
    CKP_SUCC_29,
    CKP_SUCC_30,
    CKP_SUCC_31,
    CKP_SUCC_32,
    CKP_SUCC_33,
    CKP_SUCC_34,
    CKP_SUCC_35,
    CKP_SUCC_36,
    CKP_SUCC_37,
    CKP_SUCC_38,
    CKP_SUCC_39,
    CKP_SUCC_40,
    CKP_SUCC_41,
    CKP_SUCC_42,
    CKP_SUCC_43,
    CKP_SUCC_44,
    CKP_SUCC_45,
    CKP_SUCC_46,
    CKP_SUCC_47,
    CKP_SUCC_48,
    CKP_SUCC_49,
    CKP_SUCC_50,
    CKP_SUCC_51,
    CKP_SUCC_52,
    CKP_SUCC_53,
    CKP_SUCC_54,
    CKP_SUCC_55,
    CKP_SUCC_56,
    CKP_SUCC_57,
    CKP_SUCC_58,
    CKP_SUCC_59,
    CKP_SUCC_60,
    CKP_SUCC_61,
    CKP_SUCC_62,
    CKP_SUCC_63,
    CKP_SUCC_64,
    CKP_SUCC_65,
    CKP_SUCC_66,
    CKP_SUCC_67,
    CKP_SUCC_68,
    CKP_SUCC_69,
    CKP_SUCC_70,
    CKP_SUCC_71,
    CKP_SUCC_72,
    CKP_SUCC_73,
    CKP_SUCC_74,
    CKP_SUCC_75,
    CKP_SUCC_76,
    CKP_SUCC_77,
    CKP_SUCC_78,
    CKP_SUCC_79,
    CKP_SUCC_80,
    CKP_SUCC_81,
    CKP_SUCC_82,
    CKP_SUCC_83,
    CKP_SUCC_84,
    CKP_SUCC_85,
    CKP_SUCC_86,
    CKP_SUCC_87,
    CKP_SUCC_88,
    CKP_SUCC_89,
    CKP_SUCC_90,
    CKP_SUCC_91,
    CKP_SUCC_92,
    CKP_SUCC_93,
    CKP_SUCC_94,
    CKP_SUCC_95,
    CKP_SUCC_96,
    CKP_SUCC_97,
    CKP_SUCC_98,
    CKP_SUCC_99,
    CKP_SUCC_100,
    CKP_SUCC_101,
    CKP_SUCC_102,
    CKP_SUCC_103,
    CKP_SUCC_104,
    CKP_SUCC_105,
    CKP_SUCC_106,
    CKP_SUCC_107,
    CKP_SUCC_108,
    CKP_SUCC_109,
    CKP_SUCC_110,
    CKP_SUCC_111,
    CKP_SUCC_112,
    CKP_SUCC_113,
    CKP_SUCC_114,
    CKP_SUCC_115,
    CKP_SUCC_116,
    CKP_SUCC_117,
    CKP_SUCC_118,
    CKP_SUCC_119,
    CKP_SUCC_120,
    CKP_SUCC_121,
    CKP_SUCC_122,
    CKP_SUCC_123,
    CKP_SUCC_124,
    CKP_SUCC_125,
    CKP_SUCC_126,
    CKP_SUCC_127,
    CKP_SUCC_128,
    CKP_SUCC_129,
    CKP_SUCC_130,
    CKP_SUCC_131,
    CKP_SUCC_132,
    CKP_SUCC_133,
    CKP_SUCC_134,
    CKP_SUCC_135,
    CKP_SUCC_136,
    CKP_SUCC_137,
    CKP_SUCC_138,
    CKP_SUCC_139,
    CKP_SUCC_140,
    CKP_SUCC_141,
    CKP_SUCC_142,
    CKP_SUCC_143,
    CKP_SUCC_144,
    CKP_SUCC_145,
    CKP_SUCC_146,
    CKP_SUCC_147,
    CKP_SUCC_148,
    CKP_SUCC_149,
    CKP_SUCC_150,
    CKP_SUCC_151,
    CKP_SUCC_152,
    CKP_SUCC_153,
    CKP_SUCC_154,
    CKP_SUCC_155,
    CKP_SUCC_156,
    CKP_SUCC_157,
    CKP_SUCC_158,
    CKP_SUCC_159,
    CKP_SUCC_160,
    CKP_SUCC_161,
    CKP_SUCC_162,
    CKP_SUCC_163,
    CKP_SUCC_164,
    CKP_SUCC_165,
    CKP_SUCC_166,
    CKP_SUCC_167,
    CKP_SUCC_168,
    CKP_SUCC_169,
    CKP_SUCC_170,
    CKP_SUCC_171,
    CKP_SUCC_172,
    CKP_SUCC_173,
    CKP_SUCC_174,
    CKP_SUCC_175,
    CKP_SUCC_176,
    CKP_SUCC_177,
    CKP_SUCC_178,
    CKP_SUCC_179,
    CKP_SUCC_180,
    CKP_SUCC_181,
    CKP_SUCC_182,
    CKP_SUCC_183,
    CKP_SUCC_184,
    CKP_SUCC_185,
    CKP_SUCC_186,
    CKP_SUCC_187,
    CKP_SUCC_188,
    CKP_SUCC_189,
    CKP_SUCC_190_REMOVE_TOKENCONTEXT,
    CKP_SUCC_191_INSERT_TOKENCONTEXT,
    CKP_SUCC_192,/* nor used from here */
    CKP_SUCC_193,
    CKP_SUCC_194,
    CKP_SUCC_195,
    CKP_SUCC_196,
    CKP_SUCC_197,
    CKP_SUCC_198,
    CKP_SUCC_199,
    CKP_SUCC_200_SEND_FCM_MSG,
    CKP_SUCC_201_RECV_FCM_MSG,
    CKP_SUCC_202_RECV_SPLITTED_FCM_MSG,
    CKP_SUCC_203_RECV_HANOTIFY,
    CKP_SUCC_204_RECV_HANOTIFY_BATCH,
    CKP_SUCC_205_RECV_HANOTIFY_REALSTART,
    CKP_SUCC_206_RECV_HANOTIFY_REALEND,
    CKP_SUCC_207_RECV_HANOTIFY_SMOOTH,
    CKP_SUCC_208_RECV_HANOTIFY_BATCHDATA,
    CKP_SUCC_209_RECV_HANOTIFY_REALDATA,
    CKP_SUCC_210_BATCH_ONE_TOKEN_FINISHED,
    CKP_SUCC_211_SMOOTH_ONE_TOKEN_FINISHED,
    CKP_SUCC_212_ENC_MSG_SPLITTED,
    CKP_SUCC_213_BATCH_OK,
    CKP_SUCC_214_ADDHA_TOKENNODE,
    CKP_SUCC_215_DELHA_TOKENNODE,
    CKP_SUCC_216_SMOOTH_NUMBER,
    CKP_SUCC_END,

    CKP_ERR_0,
    CKP_ERR_1,
    CKP_ERR_2,
    CKP_ERR_3,
    CKP_ERR_4,
    CKP_ERR_5,
    CKP_ERR_6,
    CKP_ERR_7,
    CKP_ERR_8,
    CKP_ERR_9,
    CKP_ERR_10,
    CKP_ERR_11_SlaveBackErr,
    CKP_ERR_12,
    CKP_ERR_13_SlaveFunErr,
    CKP_ERR_14,
    CKP_ERR_15,
    CKP_ERR_16,
    CKP_ERR_17,
    CKP_ERR_18,
    CKP_ERR_19,
    CKP_ERR_20,
    CKP_ERR_21,
    CKP_ERR_22,
    CKP_ERR_23,
    CKP_ERR_24,
    CKP_ERR_25,
    CKP_ERR_26,
    CKP_ERR_27,
    CKP_ERR_28,
    CKP_ERR_29,
    CKP_ERR_30,
    CKP_ERR_31,
    CKP_ERR_32,
    CKP_ERR_33,
    CKP_ERR_34,
    CKP_ERR_35,
    CKP_ERR_36,
    CKP_ERR_37,
    CKP_ERR_38,
    CKP_ERR_39,
    CKP_ERR_40,
    CKP_ERR_41,
    CKP_ERR_42,
    CKP_ERR_43,
    CKP_ERR_44,
    CKP_ERR_45,
    CKP_ERR_46,
    CKP_ERR_47,
    CKP_ERR_48,
    CKP_ERR_49_GetPppNull,
    CKP_ERR_50,
    CKP_ERR_51,
    CKP_ERR_52,
    CKP_ERR_53,
    CKP_ERR_54,
    CKP_ERR_55,
    CKP_ERR_56,
    CKP_ERR_57,
    CKP_ERR_58,
    CKP_ERR_59,
    CKP_ERR_60,
    CKP_ERR_61,
    CKP_ERR_62,
    CKP_ERR_63,
    CKP_ERR_64,
    CKP_ERR_65,
    CKP_ERR_66,
    CKP_ERR_67_SlaveUpdNoRp,
    CKP_ERR_68_SmoothPppFail,
    CKP_ERR_69_SmoothA10Fail,
    CKP_ERR_70_SmoothPdnFail,
    CKP_ERR_71,
    CKP_ERR_72,
    CKP_ERR_73,
    CKP_ERR_74,
    CKP_ERR_75,
    CKP_ERR_76,
    CKP_ERR_77,
    CKP_ERR_78,
    CKP_ERR_79,
    CKP_ERR_80,
    CKP_ERR_81_FCM_DISCARD,
    CKP_ERR_82,
    CKP_ERR_83,
    CKP_ERR_84,
    CKP_ERR_85,
    CKP_ERR_86,
    CKP_ERR_87,
    CKP_ERR_88,
    CKP_ERR_89,
    CKP_ERR_90,
    CKP_ERR_91,
    CKP_ERR_92,
    CKP_ERR_93,
    CKP_ERR_94_encapbackmsglenerr,
    CKP_ERR_95,
    CKP_ERR_96,
    CKP_ERR_97,
    CKP_ERR_98,
    CKP_ERR_99,
    CKP_ERR_100,
    CKP_ERR_101,
    CKP_ERR_102,
    CKP_ERR_103,/* not used from here */
    CKP_ERR_104,
    CKP_ERR_105,
    CKP_ERR_106,
    CKP_ERR_107,
    CKP_ERR_108,
    CKP_ERR_109,
    CKP_ERR_110,
    CKP_ERR_111,
    CKP_ERR_112,
    CKP_ERR_113,
    CKP_ERR_114,
    CKP_ERR_115,
    CKP_ERR_116,
    CKP_ERR_117,
    CKP_ERR_118,
    CKP_ERR_119,
    CKP_ERR_120,
    CKP_ERR_121,
    CKP_ERR_122,
    CKP_ERR_123,
    CKP_ERR_124,
    CKP_ERR_125,
    CKP_ERR_126,
    CKP_ERR_127,
    CKP_ERR_128,
    CKP_ERR_129,

    /* ����3��??��y */
    CKP_ERR_130_FCM_MSG_TOO_BIG,
    CKP_ERR_131_FCM_MSG_LENGTH_ERR,
    CKP_ERR_132_NOTIFY_REALBACKUP,
    CKP_ERR_133_QUERYRP_FAIL,
    CKP_ERR_134_ADDTOKENCONTEXT_FAIL,
    CKP_ERR_135_DELETETOKENCONTEXT_FAIL,
    CKP_ERR_136_TOKENTBL_PROC_GETRPCONTEXT_FAIL,
    CKP_ERR_137_SLAVE_TOKENTBL_PROC_GETRPCONTEXT_FAIL,
    CKP_ERR_138_TOKENCONTEXT_GETFREEINDEX_FAIL,
    CKP_ERR_139_INSERT_TOKENCONTEXT,  /* not used */
    CKP_ERR_140_INSERT_TOKENCONTEXT_REPEAT,
    CKP_ERR_141_INSERT_TOKENCONTEXT_NOTEXIST,
    CKP_ERR_142_GET_TOKENINDEX_BYID_FAIL,
    CKP_ERR_143_GET_TOKENTBL_BYINDEX_FAIL,
    CKP_ERR_144_REMOVE_TOKENCONTEXT,     /* not used */
    CKP_ERR_145_REMOVE_QUERYTOKENCONTEXT_FAIL,
    CKP_ERR_146_REMOVE_TOKENCONTEXT_ALREADYFREE,
    CKP_ERR_147_REMOVE_TOKENCONTEXT_BATCHNODE,
    CKP_ERR_148_REMOVE_TOKENCONTEXT_SMOOTHNODE,
    CKP_ERR_149_TOKENSTATUS_GETFREEINDEX_FAIL,
    CKP_ERR_150_TOKENSTATUS_ERR,
    CKP_ERR_151_GETDSTSLOT_ERR,
    CKP_ERR_152_ENCAP_MSG_FAIL,
    CKP_ERR_153_FCMSEND_FAIL,
    CKP_ERR_154_RPSTATE_ERR,
    CKP_ERR_155_REALTIME_ENCAPMSG_FAIL,
    CKP_ERR_156_BATCH_GET_DST_CSI_FAIL,
    CKP_ERR_157_BATCH_QUERYTOKEN_FAIL,
    CKP_ERR_158_BATCH_TOKENUSERCOUNT_ZERO,
    CKP_ERR_159_BATCH_QUERYRP_FAIL,
    CKP_ERR_160_BATCH_ENCAPMSG_FAIL,
    CKP_ERR_161_BATCH_TOKEN_NOTEQUAL,
    CKP_ERR_162_NOTIFY_BATCH_BYTOKEN,
    CKP_ERR_163_MALLOC_TOKENNODE_FAIL,
    CKP_ERR_164_TOKENNODE_EXIST,
    CKP_ERR_165_INSERT_TOKENNODE_FAIL,
    CKP_ERR_166_SLAVE_RECVMSG,
    CKP_ERR_167_SLAVE_CRERP_MSG,
    CKP_ERR_168_SLAVE_CRECONN_MSG,
    CKP_ERR_169_SLAVE_DEL_MSG,
    CKP_ERR_170_SLAVE_IP_VPN_SAME,
    CKP_ERR_171_SLAVE_CREATERP_FAIL,
    CKP_ERR_172_SLAVE_CREATECONN_FAIL,
    CKP_ERR_173_SLAVE_DEL_QUERYRP_FAIL,
    CKP_ERR_174_SMOOTH_QUERYTOKEN_FAIL,
    CKP_ERR_175_SMOOTH_QUERYRP_FAIL,
    CKP_ERR_176_SMOOTH_TOKEN_NOTEQUAL,
    CKP_ERR_177_ENCAP_HEAD_GET_RP_FAIL,
    CKP_ERR_178_SLAVE_ENCAP_HEAD_GET_RP_FAIL,
    CKP_ERR_179_SLAVE_NOTIFY_DELETE_RP_BACKUP,
    CKP_ERR_180_BATCH_BACKUP_DSTCSI_ERR,
    CKP_ERR_181_BACKUP_DSTCSI_ERR,
    CKP_ERR_182_ALREADY_BATCH,
    CKP_ERR_183_ENCAP_RP_STATE_ERR,
    CKP_ERR_184_ENCAP_RP_STATE_RELEASE,
    CKP_ERR_185_DECAP_MSG_TYPE_TOO_BIG,
    CKP_ERR_186_DECAP_FUNC_NULL,

    CKP_ERR_187_CHECK_HEAD_IMSI_NOT_SAME,
    CKP_ERR_188_RP_ENC_GET_CONTEXT_ERR,
    CKP_ERR_189_RP_ENC_GET_LIFETIME_ERR,
    CKP_ERR_190_RP_ENC_GET_SESSTIME_ERR,
    CKP_ERR_191_RP_DEC_GET_CONTEXT_ERR,
    CKP_ERR_192_RP_UPD_KEY_ERR,
    CKP_ERR_193_RP_DEC_BLD_RESC_ERR,
    CKP_ERR_194_RP_DEC_DEL_INPUT_ERR,
    CKP_ERR_195_RP_DEC_DEL_GET_CONTEXT_ERR,
    CKP_ERR_196_RP_DEC_DEL_MSG_TYPE_ERR,
    CKP_ERR_197_RP_DEC_DEL_GET_PPP_ERR,
    CKP_ERR_198_APN_ENC_GET_RP_CONTEXT_ERR,
    CKP_ERR_199_APN_DEC_GET_RP_CONTEXT_ERR,
    CKP_ERR_200_APN_DEC_MALLOC_ERR,
    CKP_ERR_201_FA_ENC_GET_CONTEXT_ERR,
    CKP_ERR_202_FA_ENC_GET_LIFETIME_ERR,
    CKP_ERR_203_FA_ENC_GET_AGENTTIME_ERR,
    CKP_ERR_204_FA_DEC_GET_PDN_ERR,
    CKP_ERR_205_FA_DEC_GET_RP_ERR,
    CKP_ERR_206_FA_DEC_CRE_FA_ERR,
    CKP_ERR_207_A10_ENC_GET_A10_ERR,
    CKP_ERR_208_A10_DEC_MSGTYPE_ERR,
    CKP_ERR_209_A10_DEC_GET_RP_ERR,
    CKP_ERR_210_A10_DEC_GET_A10_ERR,
    CKP_ERR_211_A10_DEC_CREATE_A10_ERR,
    CKP_ERR_212_A10_DEC_SRID_ERR,
    CKP_ERR_213_A10_DEC_A10_EXIST,
    CKP_ERR_214_A10_ENC_DEL_GET_A10_ERR,
    CKP_ERR_215_PMIPV6_ENC_GET_CONTEXT_ERR,
    CKP_ERR_216_PMIPV6_DEC_INPUT_ERR,
    CKP_ERR_217_PMIPV6_ENC_GET_LIFETIME_ERR,
    CKP_ERR_218_PMIPV6_ENC_GET_UPDTIME_ERR,
    CKP_ERR_219_PDN_ENC_CRE_GET_CONTEXT_ERR,
    CKP_ERR_220_PDN_DEC_CRE_GET_RP_ERR,
    CKP_ERR_221_PDN_DEC_CRE_GET_PDN_ERR,
    CKP_ERR_222_PDN_DEC_CRE_PDN_EXIST,
    CKP_ERR_223_PDN_DEC_CRE_PDN_FULL,
    CKP_ERR_224_PDN_DEC_CRE_CONTEXT_ERR,
    CKP_ERR_225_PDN_DEC_BUILD_RES_ERR,
    CKP_ERR_226_PDN_DEC_UPD_CONTEXT_NULL,
    CKP_ERR_227_PDN_DEC_DEL_CONTEXT_NULL,
    CKP_ERR_228_PDN_DEC_DEL_CONTEXT_ERR,
    CKP_ERR_229_SIP_ENC_INPUT_ERR,
    CKP_ERR_230_SIP_ENC_GET_PDN_CONTEXT_ERR,
    CKP_ERR_231_SIP_DEC_INPUT_ERR,
    CKP_ERR_232_SIP_DEC_GET_PDN_CONTEXT_ERR,
    CKP_ERR_233_MIP_ENC_INPUT_ERR,
    CKP_ERR_234_MIP_ENC_GET_PDN_CONTEXT_ERR,
    CKP_ERR_235_MIP_DEC_INPUT_ERR,
    CKP_ERR_236_MIP_DEC_GET_PDN_CONTEXT_ERR,
    CKP_ERR_237_MIPV6_ENC_INPUT_ERR,
    CKP_ERR_238_MIPV6_ENC_GET_PDN_CONTEXT_ERR,
    CKP_ERR_239_MIPV6_DEC_INPUT_ERR,
    CKP_ERR_240_MIPV6_DEC_GET_PDN_CONTEXT_ERR,
    CKP_ERR_241_MIPV6_DEC_CRE_PMIPV6_ERR,
    CKP_ERR_242_L2TP_ENC_INPUT_ERR,
    CKP_ERR_243_L2TP_ENC_GET_PDN_CONTEXT_ERR,
    CKP_ERR_244_L2TP_DEC_INPUT_ERR,
    CKP_ERR_245_L2TP_DEC_GET_PDN_CONTEXT_ERR,

    CKP_ERR_246_EHRPD_ENC_INPUT_ERR,
    CKP_ERR_247_EHRPD_ENC_GET_PDN_CONTEXT_ERR,
    CKP_ERR_248_EHRPD_DEC_INPUT_ERR,
    CKP_ERR_249_EHRPD_DEC_GET_PDN_CONTEXT_ERR,

    CKP_ERR_250_TFT_ENC_GET_PDN_ERR,
    CKP_ERR_251_TFT_ENC_NO_TFT_ERR,
    CKP_ERR_252_TFT_ENC_INDEX_ERR,
    CKP_ERR_253_TFT_ENC_GET_CONTEXT_ERR,
    CKP_ERR_254_TFT_DEC_GET_CONTEXT_ERR,
    CKP_ERR_255_TFT_DEC_CRE_TFT_ERR,
    CKP_ERR_256_TFT_ENC_DEL_GET_CONTEXT_ERR,
    CKP_ERR_257_TFT_DEC_DEL_FREE_TFT_ERR,
    CKP_ERR_258_TFT_DEC_DEL_GET_PDN_ERR,

    CKP_ERR_259_RP_SMOOTH_NOT_ACTIVE_STATE,
    CKP_ERR_260_RP_SMOOTH_LIFE_TIME_ZERO,
    CKP_ERR_261_RP_SMOOTH_SESS_TIME_ZERO,
    CKP_ERR_262_RP_SMOOTH_PPP_NOT_EXSIT,
    CKP_ERR_263_RP_SMOOTH_PPP_RP_NOT_SAME,
    CKP_ERR_264_RP_SMOOTH_PPP_IMSI_NOT_SAME,
    CKP_ERR_265_RP_SMOOTH_A10_NOT_EXSIT,
    CKP_ERR_266_SMOOTH_A10_RP_NOT_SAME,
    CKP_ERR_267_RP_SMOOTH_A10_CM_ERR,
    CKP_ERR_268_RP_SMOOTH_A10_NUMBER_ERR,
    CKP_ERR_269_RP_SMOOTH_PDN_NOT_EXSIT,
    CKP_ERR_270_RP_SMOOTH_PDN_STATE_ERR,
    CKP_ERR_271_RP_SMOOTH_PDN_RP_NOT_SAME,
    CKP_ERR_272_RP_SMOOTH_PDN_CM_ERR,
    CKP_ERR_273_RP_SMOOTH_PDN_PCC_ERR,
    CKP_ERR_274_RP_SMOOTH_PDN_NUMBER_ERR,
    CKP_ERR_275_RP_SMOOTH_TFT_NOT_EXSIT,
    CKP_ERR_276_RP_SMOOTH_TFT_PDN_NOT_SAME,
    CKP_ERR_277_RP_SMOOTH_TFT_NUMBER_NOT_SAME,
    CKP_ERR_278_RP_SMOOTH_FA_NOT_EXSIT,
    CKP_ERR_279_RP_SMOOTH_FA_STATE_ERR,
    CKP_ERR_280_RP_SMOOTH_FA_PDN_NOT_SAME,
    CKP_ERR_281_RP_SMOOTH_PMIPV6_NOT_EXSIT,
    CKP_ERR_282_RP_SMOOTH_PMIPV6_STATE_ERR,
    CKP_ERR_283_RP_SMOOTH_PMIPV6_PDN_NOT_SAME,


    CKP_ERR_284_RP_SMOOTH_CREAT_SESS_TIMER_ERR,
    CKP_ERR_285_RP_SMOOTH_CREAT_LIFE_TIMER_ERR,
    CKP_ERR_286_FA_SMOOTH_LEFT_TIME_ZERO,
    CKP_ERR_287_FA_SMOOTH_CREAT_LIFE_TIMER_ERR,
    CKP_ERR_288_MIPV6_SMOOTH_LIFE_TIME_ZERO,
    CKP_ERR_289_MIPV6_SMOOTH_CREATE_LIFE_TIME_ERR,
    CKP_ERR_290_MIPV6_SMOOTH_UPDATE_TIME_ZERO,
    CKP_ERR_291_MIPV6_SMOOTH_CREATE_UPDATE_TIME_ERR,
    CKP_ERR_292_RCV_BKPMSG_AFTER_SMOOTH_ERR,
    CKP_ERR_293_SMOOTH_SLAVE_REL,

    CKP_DEBUG_MAX,
}CKP_DEBUG_TYPE_E;

typedef enum
{
    L2TP_MSGCODE_DUMMY = 0,                 /* ?TD��???��?? */
    L2TP_MSGCODE_UP,                        /*ppp����?al2tp up��??t*/
    L2TP_MSGCODE_DOWN,                      /*ppp����?al2tp down��??t*/
    L2TP_MSGCODE_BACKUP_CALL_REB,           /*?��?���?��????��???��*/
    L2TP_MSGCODE_BACKUP_CALL_DEL,           /*?��?���?��?��?3y???��*/
    L2TP_MSGCODE_SOURCE_CHECK_RSP,          /*GTPC����?��o?2����|��e???�� */
    L2TP_MSGCODE_BACKUP,                    /* ��?��Y???�� */
}L2TP_MSGCODE_E;



typedef enum
{
    USM_STATE_INIT = 1,                 /* 1 3?��?���䨬? */
    USM_STATE_WT_A11_SETUP,             /* 2 �̨���yA11����?��?�����騪��3�� */
    USM_STATE_WT_PPP_SETUP,             /* 3 �̨���yPPP����?��?�����騪��3�� */
    USM_STATE_WT_PDN_SETUP,             /* 4 �̨���yPDN?�����騪��3�� */
    USM_STATE_ACTIVE,                   /* 5 ?��??��? */
    USM_STATE_DIFF_HANDOFF,             /* 6 ?D??��? */
    USM_STATE_WT_DIAM_AUTHORIZE,        /* 7 �̨���y??��?��������D??�� */
    USM_STATE_WT_PPP_RELEASE,           /* 8 �̨���yPPP����?��������?����3�� */
    USM_STATE_WT_A11_RELEASE,           /* 9 �̨���yA11����?��������?����3�� */
    USM_STATE_WT_PDN_RELEASE,           /* 10 �̨���yPDN����?��������?����3�� */

    USM_STATE_BUTT
}USM_STATE_E;

/* ?????��?������?aUSM��????��?? */
typedef enum tagUSM_OTHER2USM_MSGTYPE_E
{
    E_USM_MSGTYPE_A112USM_SETUP = 200, /* A11����?aUSM?�����騪��3����????��?? */
    E_USM_MSGTYPE_PPP2USM_SETUP,       /* PPP����?aUSM?�����騪��3����????��?? */
    E_USM_MSGTYPE_PDN2USM_SETUP,       /* PDN����?aUSM?�����騪��3����????��?? */
    E_USM_MSGTYPE_PPP2USM_RELEASE,     /* PPP����?aUSM����??����3����????��?? */
    E_USM_MSGTYPE_A112USM_RELEASE,     /* A11����?aUSM����??����3����????��?? */
    E_USM_MSGTYPE_PDN2USM_RELEASE,     /* PDN����?aUSM����??����3����????��?? */
    E_USM_MSGTYPE_BUTT,

}USM_OTHER2USM_MSGTYPE_E;

#define M_CFG_ERR_DBAPI                     200
#define M_CFG_DB_API_DBERROR                1L
#define M_CFG_DB_API_SUCCESS                VOS_OK
#define M_CFG_DB_API_NOTFOUND               (M_CFG_ERR_DBAPI + 2)   /*202*/
#define M_CFG_DB_API_EMPTY                  (M_CFG_ERR_DBAPI + 3)   /*203*/
#define M_CFG_DB_API_FULL                   (M_CFG_ERR_DBAPI + 4)   /*204*/
#define M_CFG_DB_API_DUPLICATE              (M_CFG_ERR_DBAPI + 5)   /*205*/
#define M_CFG_DB_API_CURSOREND              (M_CFG_ERR_DBAPI + 6)   /*206*/
#define M_CFG_DB_API_PERMISSION_DENIED      (M_CFG_ERR_DBAPI + 7)   /*207*/
#define M_CFG_DB_API_BATCH_NEEDED           (M_CFG_ERR_DBAPI + 8)   /*208*/
#define M_CFG_DB_API_TRANSFER_ERROR         (M_CFG_ERR_DBAPI + 9)   /*209*/
#define M_CFG_ERR_CONDITION_NUM_TOO_MORE    (M_CFG_ERR_DBAPI + 10)  /*210*/
#define M_CFG_ERR_CONDITION_INVALID         (M_CFG_ERR_DBAPI + 11)  /*211*/
#define M_CFG_ERR_DBAPI_UNKNOWN_OPERATOR    (M_CFG_ERR_DBAPI + 12)  /*212*/
#define M_CFG_DB_API_INVALID_PARA           (M_CFG_ERR_DBAPI + 13)  /*213*/
#define M_CFG_DB_API_NOT_MATER_TMN          (M_CFG_ERR_DBAPI + 14)  /*214*/
#define M_CFG_DB_API_RDWR_DISABLE           (M_CFG_ERR_DBAPI + 20)  /*220*/
#define M_CFG_DB_API_RDONLY_ENABLE          (M_CFG_ERR_DBAPI + 21)  /*221*/
#define M_CFG_DB_API_RDWR_ENABLE            (M_CFG_ERR_DBAPI + 22)  /*222*/
#define M_CFG_DB_API_PARAERROR              (M_CFG_ERR_DBAPI + 23)  /*223*/
#define M_CFG_DB_API_REGISTERED             (M_CFG_ERR_DBAPI + 24)  /*224*/
#define M_CFG_DB_API_PRODUCTTYPE_ERROR      (M_CFG_ERR_DBAPI + 25)  /*225*/



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
}EMS_PPP_E;

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
    E_PDNTYPE_UNKNOWN = 0,
    E_PDNTYPE_SIP,
    E_PDNTYPE_L2TP,
    E_PDNTYPE_CMIP,
    E_PDNTYPE_PMIPV4,
    E_PDNTYPE_PMIPV6,
    E_PDNTYPE_EHRPD,

    E_PDNTYPE_BUTT
}PDN_TYPE_E;

/* SDB����???? */
typedef enum tagSDB_RETURNCODE_E
{
    SDB_SUCCESS              = 0,                     /* 3��1|����?? */
    SDB_INVALID_INPUT        = 1,                     /* ��?��?��?���� */
    SDB_RECORD_NOT_EXIST     = 2,                     /* ?��2����??����|???? */
    SDB_RECORD_EXIST         = 3,                     /*2��?��????��??-��??�� */
    SDB_TABLE_FULL           = 4,                     /* ������??��(?T?????����???) */
    SDB_INIT_FAILURE         = 5,                     /* 3?��??������㨹 */
    SDB_INCONSISTENT         = 6,                     /* ����??2?��??? */
    SDB_FIND_IDLE_RECORD     = 7,                     /* ???????D */
    SDB_INVALID_MSG          = 8,                     /* ��?����???�� */
    SDB_EMPTY_HASH_CHAIN     = 9,                     /* ??1t??3?��?���� */
    SDB_SYSTEM_FAILURE       = 10,                     /* SDB?��?��???���䨪?�� */
    SDB_CONTINUED_TO_SEARCH   = 11,
    NO_LICENSE =12 ,
    SDB_APN_USERCONTROL      = 13,                     /* APN��??�쨺y?????�䨪��1y*/
    SDB_APN_BANDCONTROL      = 14,                     /* APN��??��?T???�䨪��1y */
    SDB_TRAFFIC_CLASS_BANDCONTROL    = 15,             /* Traffic Class��??��?T???�䨪��1y */
    SDB_APN_SPU_BANDCONTROL      = 16,                    /* �̣���?��??��?T???�䨪��1y */
    SDB_IP_CONFLICT            =  17,                   /*IP��??��3?��?*/
    SDB_DIFFSRV_REACH_APN_PDPNUM_TC_REJTHRD = 20,
    SDB_DIFFSRV_REACH_APN_PDPNUM_GENERAL_REJTHRD = 21,
    SDB_DIFFSRV_REACH_GLOB_PDPNUM_TC_REJTHRD = 22,
    SDB_DIFFSRV_REACH_GLOB_PDPNUM_GENERAL_REJTHRD =  23 ,
    SDB_DIFFSRV_REACH_APN_BANDWIDTH_TC_REJTHRD = 24,
    SDB_DIFFSRV_REACH_APN_BANDWIDTH_GENERAL_REJTHRD = 25,
    SDB_IMS_USER_NO_LICENSE   = 40,
    SDB_WHOLE_THROUTPUT_NO_LICENSE = 41,
    SDB_DIFFSRV_REACH_REJECT_THRESHOLD  =  100,
    SDB_DHCP_PARA_ERROR = 0xFF + 1, /* DHCP����??2?��y�䨪?��*/
    SDB_DHCP_POOL_ERROR = 0xFF + 2,     /* DHCP����??��??��3?�䨪?��*/
    SDB_DHCP_NO_IP_AVAILABLE = 0xFF + 3, /*?T?����?��??����???*/
    SDB_DMT_NO_RECORD        = 28101,                 /* DMT2��?��????2?��??�� */
    SDB_DMT_INVALID_INPUT    = 28102,                 /* DMT2��?����?��?2?��y?TD�� */
    SDB_FAILURE,
    SDB_NOT_ALLOW_CREATE_RANDOM_SDB,
    SDB_RETURNCODE_BUTT      = 0xffffffff             /* ?����?����?? */

}SDB_RETURNCODE_E;



/* o��D?��|???2��?USM ?��??PDN */
typedef enum
{
    A11_ACCT_TERM_USER_REQUEST = 1,
    A11_ACCT_TERM_IDLE_TIMEOUT = 4,
    A11_ACCT_TERM_SESSION_TIMEOUT = 5,
    A11_ACCT_TERM_ADMIN_RESET = 6,
    A11_ACCT_TERM_PORT_ERROR = 8,
    A11_ACCT_TERM_NAS_ERROR = 9,
    A11_ACCT_TERM_NAS_REQUEST = 10,
    A11_ACCT_TERM_SERV_UNAVAILABLE = 15,
    A11_ACCT_TERM_USER_ERROR = 17,
    A11_ACCT_TERM_PPP_RENEGO = 18,
    A11_ACCT_TERM_FA_REQUEST = 19,
    A11_ACCT_TERM_PPC_DUR = 254, /* ?��??��?����3��????2?��? */
    A11_ACCT_TERM_PPC = 255 /* ?��??��?���¨�?????2?��? */
}A11_ACCT_TERM_CAUSE_E;

/* HSGW/PDSN ���䨬??��ID��3��??����? */
typedef enum
{
    E_FSM_ID_USM = 1,
    E_FSM_ID_A11,
    E_FSM_ID_PDN,
    E_FSM_ID_SIPV4,
    E_FSM_ID_SIPV6,
    E_FSM_ID_CMIP,
    E_FSM_ID_PMIPV4,
    E_FSM_ID_PMIPV6_4,
    E_FSM_ID_PMIPV6_6,
    E_FSM_ID_L2TP,
    E_FSM_ID_EHRPD,
    E_FSM_ID_DHCP,
    E_FSM_ID_PMV6,

    E_FSM_ID_BUTT
}HSGW_FSM_ID_E;

/** SPU�̣���?��2?t����D��?����? */
typedef enum tagCRM_SPU_BOARD_TYPE_ENUM
{
    CRM_BOARD_TYPE_UNKNOWN = 0,  /**< ?��??��?�̣���?��??1����D����??a?��?a����D�� */
    CRM_BOARD_TYPE_SPUD,         /**< SPUD��?�ꡧ�㨹o?��?TCAM???����? */
    CRM_BOARD_TYPE_SPUE,         /**< SPUE��? */
    CRM_BOARD_TYPE_PEU,          /**< PEU��? */
    CRM_BOARD_TYPE_SPUF,
    CRM_BOARD_TYPE_MSU,          /**< MSU��? */
    CRM_BOARD_TYPE_SPUF1,
    CRM_BOARD_TYPE_MSUF1,
    CRM_BOARD_TYPE_MAX,           /**< ?TD�쨮2?t����D�� */
}  CRM_SPU_BOARD_TYPE_ENUM ;


typedef enum tagRTFCompConstruct
{
    RTF_COMP_CONSTRUCT_STAGE1 = 0, /**< �̨���??��??��??����?3?��??����?��|��?����?t����???����?�̨�2�����¡�?3?��??������?t��?LOCAL��y?Y��??��??3��?��?��*/
    RTF_COMP_CONSTRUCT_STAGE2,     /**< �̨�?t?��??��???��?HA���䨬?��???��?��?����?tHA���䨬?��??��?YHA���䨬?3?��??��2?��?��??�̨�3����?��?��*/
    RTF_COMP_CONSTRUCT_STAGE3,     /**< �̨���y?��??��????????���??��?Y����?tHA���䨬???��?????��y?Y?��*/

    RTF_COMP_CONSTRUCT_STAGE_BUTT
} RTF_COMP_CONSTRUCT_STAGE_E;

typedef struct tagAPNDNS
{
    ULONG  stMainDNSServerIpv6[IPV6_DNS_LEN];    /* ?�¨�?IPv6 DNS��t???�� */
    ULONG  stBackupDNSServerIpv6[IPV6_DNS_LEN];  /* ��?��?IPv6 DNS��t???�� */
    ULONG    ulMainDNSServer;     /* ?��DNS��t???�� */
    ULONG    ulBackupDNSServer;   /* ��?DNS��t???�� */
    USHORT   usApnIndex ;         /* APN?�¨�y   */
    //UCHAR    ucDNSSelectMode;   /* 0 ��?��?????��??����? 1 Radius???����??�� ,2 DHCP???����??��*/
    //UCHAR    ucDNSSelectModeIPv6;     /* 0 ��?��?????��??��, 1 Radius???����??�� , 2 DHCP???����??��*/
    UCHAR    ucFirstSelectModeIpv4;
    UCHAR    ucSecondSelectModeIpv4;
    UCHAR    ucThirdSelectModeIpv4;
    UCHAR    ucFirstSelectModeIpv6;
    UCHAR    ucSecondSelectModeIpv6;
    //UCHAR    ucDNSSelectMode;     /* 0 ��?��?????��??����? 1 Radius???����??�� ,2 DHCP???����??��*/
    //UCHAR    ucDNSSelectModeIPv6; /* 0 ��?��?????��??��, 1 Radius???����??�� , 2 DHCP???����??��*/
    UCHAR    ucReserve[1];
}VOS_PACKED   APNDNS_S;

typedef struct tagPMBUF_DataBlockDescriptor
{
    ULONG ulDataLength;         /* ��y?Y?��?D��y?Y��?3��?����?��??�̡�??��[0, ulDataBlockLength]*/
    UCHAR * pucData;            /* ��y?Y?��?D��y?Y��??e��?��??��, [pucDataBlock + 512, pucDataBlock + ulDataBlockLength]*/
    ULONG ulDataBlockLength;    /* ��y?Y?����?����3��?��,*/
    UCHAR * pucDataBlock;       /* ��y?Y?����??e��?��??����? NULL������??TD���?????������?��DD��*/
    ULONG ulType;               /* MBUF_TYPE_XXX */
    struct tagPMBUF_DataBlockDescriptor * pstNextDataBlockDescriptor;/*??��???��y?Y?��?����?��?��? Always NULL*/
}PMBUF_DATABLOCKDESCRIPTOR_S;    /* ��y?Y?��?����?��?��y?Y?��11*/

/* PPP link up��?o������?aUSM��??��11��? */
typedef struct
{
    UCHAR *pucMsg; /* ppp?��?Y��??�쨤��D��D����a1��AAA_AUTHRSP_S?��??EAP??����?����|?��11��? */
    ULONG ulRpIndex;
    ULONG ulResultCode;
    USHORT usDomainIndex;
    USHORT usVirtualDomainIndex;
    UCHAR  aucNAI[A11_MAX_NAI_LENGTH + 1];                /* NAI */
}USM_PPP_LINKUP_RESULT_S;

typedef struct
{
    ULONG  ulTick;     /* ��?�������騦����?TICK��y */
    DATE_T stDate;
    TIME_T stTime;
}VOS_PACKED S_FAM_BAM_TRC_TIME_DATA;

typedef struct tagPTM_QUEUE_INFO
{
    VOS_UINT64 ullSelfCsi;
    VOS_UINT32 ulMsgType;
    VOS_UINT32 ulQueType;
    VOS_UINT32 ulQueLen;
    VOS_UINT32 ulEvent;
    VOS_UINT32 ulTaskId;
    VOS_CHAR szQueName[M_PTM_QUE_NAME_LEN + 1];
    VOS_UINT8  aucReserved[4];
}PTM_QUEUE_INFO_S;

typedef struct
{
    UCHAR  aucImsi[16];
    ULONG  ulMsgType;
}A11_S_USERTRC_FILTER;

typedef struct
 {
     ULONG   ulUserTotalNum;            /* HRPD��??�쨺y*/
     ULONG   ulA10RpNum;                /* HRPD��??��A10��?��?????��y*/
     ULONG   ulL2tpNum;                 /* rp��?????��y*/
     ULONG   ulSIPUserNum;              /* ?���̣�IP��??�쨺y */
     ULONG   ulCMIPUserNum;             /* CMIP��??�쨺y */
     ULONG   ulPMIPUserNum;             /* PMIPv4��??�쨺y */
     ULONG   ulPMIPv6UserNum;           /* PMIPv6��??�쨺y */
     ULONG   ulPpcUserNum;              /* PPC��??�쨺y */
     ULONG   ulOnlineUserNum;           /* ?��????��?��??�쨺y */
     ULONG   ulContentUserNum;          /* ?����Y??��?��??�쨺y */
     ULONG   ulVjUserNum;               /* VJ ?1??��??�� */
     ULONG   ulMppcUserNum;             /* MPPC?1??��??�� */
     ULONG   ulMppVjUserNum;            /* MPPC + VJ?1??��??�� */
     ULONG   ulPccUserNum;              /* PCC��??��*/
     ULONG   ulDoUserNum;               /* DO��??�쨺y*/
     ULONG   ul1xUserNum;               /* 1X��??�쨺y*/
     ULONG   ulWifiUserNum;             /* Wifi��??�쨺y*/
     ULONG   ulSipv6UserNum;            /* IPv6�̣�??��??�쨺y*/
     ULONG   ulSipDualStackUserNum;     /* IPv6????��??�쨺y*/
     ULONG   ulPMIPv6S6UserNum;         /* PMIPv6 IPv6�̣�??��??�쨺y*/
     ULONG   ulPMIPv6DualStackUserNum;  /* PMIPv6????��??�쨺y*/
     ULONG   ulEhrpdUserTotalNum;       /* eHRPD��??�쨺y */
     ULONG   ulEhrpdUserA10Num;         /* eHRPD��??��A10��?????��y */
     ULONG   ulEhrpdPdnNumber;          /* eHRPD��??���?pdn��??����y */
     ULONG   ulEhrpdPccSessionNum;      /*PCC session��??����y*/
     ULONG   ulEhrpdDualStackPdnNumber;  /*eHRPD��??��????PDN��??����y*/
     ULONG   ulEhrpdIpv6StackPdnNumber;  /*eHRPD��??��IPV6-PDN��??����y*/
 }stDomainNumInfo;

 typedef  struct tagCPU_STATUS_CHG
{
    ULONG ulSlotId;         /**< ���䨬?���騦����??����?CPU��????-2???o? */
    ULONG ulCpuId;          /**< ���䨬?���騦����??����?CPU��?CPUo? */

    ULONG ulStatus_flg;     /**< ���䨬?��??������??��?��??�̡�??��: STATUS_CHG_FLAG_E */
    ULONG ulPreStatus;      /**< CPU?-�����?���䨬? */
    ULONG ulNowStatus;      /**< CPU???����?���䨬? */

    ULONG ulBoardType;      /**< ���䨬?���騦����??����?CPU��?�̣���?����D�� */
    ULONG ulProductType;    /**< 2��?������D�� GGSN?��PDSN?��DPI �̨� */
    ULONG ulBoardExtType;   /**< �̣���?��??1����D�� */
    /* Added start by majun 52643 at 2013-02-25 PGP V2R6C01 for ������?1������???? */
    ULONG ulBoardRawType;   /**< �̣���?��??1����D�� */
    ULONG ulBoardVirtualType;   /**< �̣���?��??1����D�� */
    /* Added end by majun 52643 at 2013-02-25 PGP V2R6C01 for ������?1������???? */

    ULONG ulSGIndex;    /**< �̣�SG?��??������?����??o? */
    ULONG ulSGType;     /**< �̣�SG?��??������?����D�� */
    ULONG ulMemSize;    /**< CPU?����?����D�� */
    ULONG ulModeType;   /**< ???��?�꨺? */

    ULONG ulReserve2;
    ULONG ulReserve1;
} CPU_STATUS_CHG_S;

typedef  struct tagCPU_STATUS_PKG
{
    ULONG ulCpuChgNum;/**< ���䨬?���騦����?CPU��??����?�̣���?��y��? */
    CPU_STATUS_CHG_S   *pstStatusChg; /**< �̣���?��?CPU���䨬?��??����y?Y */
} CPU_STATUS_PKG_S;

typedef struct tagA11_S_IFTRC_FILTER
{
    ULONG ulFlag;                                       /* ������??��������?��?*/
    ULONG ulLogicIp;                                    /* ��???IP��??�� */
    ULONG ulVpnIndex;                                   /* VPN?�¨�y*/
    ULONG ulPeerIp;                                     /* ????IP��??�� */
    ULONG ulMsgType;                                    /* ???�騤��D�� */
}A11_S_IFTRC_FILTER;

/* PPP����?aL2TP Down��????��?��11 */
typedef struct
{
    ULONG   ulPdpindex;
    ULONG   ulTeidc;
    USHORT  usLocalTID;   /*��????���̨�id*/
    USHORT  usLocalSID;   /*��????��?��id*/
    ULONG   ulGiifIndex ; /*piif???-?��?��?�¨�y*/
    UCHAR   ucScid;         /*ppp?��?��sc???-id*/
    UCHAR   aucRev[3];    /*���ꨢ?��???,?Y?T��1��?*/
}L2TP_DOWNPARA_S;


typedef struct {
  ULONG state[4];        /* state (ABCD) */
  ULONG count[2];        /* number of bits, modulo 2^64 (lsb first) */
  UCHAR buffer[64];      /* input buffer */
} MD5_CTX;

typedef struct
{
    PF_USHORT usCtrlFlag;
                           /*bit 15:?a1����?�¨�??2��?��??����??���a��?��??��??D?��?
                              bit14-bit12:res
                              bit11-bit10:??��?��?��?��?��a��?����???������
                                        00��oUGW/MSD <-> NET/SP
                                        01��oUGW <-> MSD
                                        10��oMSD <-> VAS
                                        11��oMSD <-> MSU
                              bit9:?��bit7-bit6?a10������DD���?������?F��?��???��?COLOR
                              bit8:?����a��?????����??
                              bit8:IPPM����??��?��?��??������
                              bit7-bit6:??��?3?��?IPPM��?????����???1��?????��e��?����??
                                        00��o?y3��D?��?����??��?
                                        01��o������?��?IPPM��?FM??��?PF��?��e3?����o��D����a��?��?D?��???
                                        10 :IPPM��?FM��?��???
                              bit5-bit4:
                                        :�̡�bit0(GtpuFlag)???a1����(��??��??����??)��?������?GTP����??��?3?GW��?����2��(??DD)?1��?����2��(��?DD).
                                        ������?PMIP(GRE)��??��??����??3?GW��?����2��(??DD)?1��?����2��(��?DD)?��
                                        00: ����2��GTP����??(??DD), 01:����2��GTP����??(��?DD), 10: ����2��PMIP(GRE)(??DD), 11:����2��PMIP(GRE)(��?DD)
                              bit3 : LiFlag,0: UP , 1:DN
                              bit2-bit1 : TraceFlag,00:UP_IN,01:UP_OUT,10: DN_IN,11:DN_OUT,
                              bit0 : GtpuFlag,1:indirect forwarding,0:��????����a�������??*/
    PF_USHORT usPktType;    /*����??����D��:1-psf 2-gre ping*/
    PF_ULONG  ulDpeTimeStamp;
    PF_ULONG  ulSubIndex;
    PF_ULONG  ulVcpuId;
    PF_ULONG  ulModuleId;
    PF_ULONG  ulMsgCode;
    PF_ULONG  ulPdpIndex;   /* GSDBindex,PF��??��??????������??��?Ygtpuindex�䨮GTPU����?D??
                               ��?GSDBindex,�䨮??????��?��?����??o����??��?Y???�̡̦¨�?AM?��?��
                               ??��?gtpuindex */
    PF_ULONG  ulVrfIndex;
} FWD_TO_CTRL_HDR;

typedef struct tagHSGW_APN_INFO_S
{
    USHORT usApnInfoIndex;
    UCHAR aucApnInfoName[M_CFG_MAX_APN_STRING_LEN];
    VOS_UINT8 aucReserved[2];

    UCHAR ucPmipv6TransportPrior; /* pmipv6D?��?��?��?��??��?? */
    UCHAR ucIdleFlg;               /* idle-timerout ?a1? */
    USHORT usIdleLen;              /* idle-timerout 3��?�� �̣�??:minute */

    ULONG ulIpv6RaInterval;       /* ����?��?����������??��?�䨮����3�� */

}VOS_PACKED HSGW_APN_INFO_S;

typedef struct
{
    VOS_UINT8  ucOper;
    VOS_UINT8  aucReserved[3];
    VOS_UINT32 udwFieldId;
    VOS_INT8   aValue[M_CDB_MAX_FIELD_LENGTH];
} S_CFG_CDB_CONDITION;


typedef struct tagCKP_BACKUP_MSGTLV_HEAD_S
{
    ULONG   ulType;        /*D����a��?��??��11��?type*/
    ULONG   ulSdbIndex;    /* ��a�����?TLV��y?Y������?����????����?����?sdb��??????�¨�y */
    ULONG   ulSessionIndex;
    UCHAR   ucNum;         /*?a?����??��11D����a��?��??������??*/
    UCHAR   ucReserved;    /*���ꨢ?��???*/
    USHORT  usStrLen;      /*?a???��11��?3��?�� 2?�㨹����TLV������?3��?��??��?��?��Y��y?Y?����Y3��?��*/
    UCHAR   ucValue[0];    /* ��?��Y��?��y?Y */
}CKP_BACKUP_MSGTLV_HEAD_S;
#define CKP_BACKUP_TLV_SIZE   sizeof(CKP_BACKUP_MSGTLV_HEAD_S)



typedef struct tagLI_X2PACKET_FILTER_INFO
{
    struct  tagLI_X2PACKET_FILTER_INFO *next;
    ULONG length;
    UCHAR value[100];
} LI_X2PACKET_FILTER_INFO;

#define IMSIBCDLEN   8
#define ESNBCDLEN    4
#define MEIDBCDLEN   7
#define MDNBCDLEN    8
#define NAILEN      65


typedef struct
{
    ULONG ulPdpIndex;       /* RP ��??????�¨�y */
    ULONG ulTeidc;
    ULONG ulPcfKey;         /* PCF������? */
    ULONG ulHaAddr;
    ULONG ulCoAAddr;
    ULONG ulSetUpTimeInSec;

    UCHAR szIMSI[IMSIBCDLEN];        /* ����D��BCD?? */
    UCHAR szESN[ESNBCDLEN];
    UCHAR szMEID[MEIDBCDLEN];
    UCHAR ucMeidLen;
    UCHAR szMDN[MDNBCDLEN];          /* ����D��BCD?? */

    UCHAR szNAI[NAILEN];
    UCHAR ucNaiLen;
    UCHAR ucImsiLen;
    UCHAR ucEsnLen;

    UCHAR aucBsid[6];
    UCHAR ucMdnLen;
    UCHAR ucBsidFlag;

    UCHAR szPdsnIpAddr[16];   /* DPSN��??�� */
    UCHAR szSubIpAddr[16];    /* ��?������????a��?????������???��?IP��??�� */

    UCHAR ucPdsnIpType;       /* 0:IPv4, 1:IPv6 */
    UCHAR ucSubIpType;        /* 0:IPv4, 1:IPv6 */
    UCHAR ucSIPorMIP;         /* ??3?��?????������1��?��?��??���̣�IP?1��?��??��IP?��SIP����PDSN?��AAA��???��?MIP����HA��????�� */
    UCHAR ucGotOldIpFlag;     /* ?D??������?��??1?��??��?��??-PCF IP 0:??��?2?��?,1:??��?��?*/

    UCHAR ucAccPcfIpType;     /* 0:IPv4, 1:IPv6 */
    UCHAR ucCurPcfIPType;
    UCHAR uchandOffType;      /* handoff ����D�� */
    UCHAR ucOtherNetIdLen;

    UCHAR szAccPcfIpAddr[16]; /* ?D??����������??-PCF IP */
    UCHAR szCurPcfIPAdd[16];  /* ?D??����������??D??o��PCF IP */
    UCHAR szOtherNetId[20];   /* handoff 3??�� */

    UCHAR szCanId[10];        /* �̡�?��?����?��???������? */
    UCHAR ucCanIdLen;
    UCHAR ucPanIdLen;

    UCHAR szPanId[10];        /* ?D???�㨪???������? */
    UCHAR ucSuccessFlag;
    UCHAR ucPacketFilterFlag; /*packerfilter D����?����??*/

    UCHAR ucAuType;           /* ��?????����?����?��?������???������??��AAA?D??DD??������?��?��? */
    UCHAR ucAuFlag;           /* 1:ucAuType��DD���? 0:ucAuType?TD�� */
    UCHAR ucSubPasswordLen;
    UCHAR ucChapChallengeLen;

    UCHAR szSubPassword[20];  /* ��?????������????��?��?? */
    UCHAR szChapChallenge[16];/* ��?2����?CHAP��??�診����??���???������?��???16������?��????����y */

    USHORT usFailureCause;    /* ?��???��?��D?����㨹?-����?�� */
    USHORT usReleaseCause;    /* ����???-����?�� */

    USHORT usIriTargetMap;    /*��?������?3?��?��??????D��?bitmap ?��*/
    USHORT usIdpTargetMap;    /*��?������?3?��?��??????D��?bitmap ?��*/

    UCHAR ucPortType;         /*PPP��??��?1��?IP ��??��*/
    UCHAR ucSduVcpu;

    UCHAR ucRev[2];

    LI_X2PACKET_FILTER_INFO stX2PacketFilterInfo;

}LI_CDMA2000_PDPINFO_S;



typedef struct tagPPPCONIFG_OPTION_S
{
    UCHAR ucType;
    UCHAR ucLen;
    UCHAR aucValue[0];
} PPPCONIFG_OPTION_S ;

typedef struct tagRP_SEQUENCE_NUM
{
    UCHAR  ucUsed:1;
    UCHAR  ucSetupFlag:1;
    UCHAR  ucStartFlag:1;
    UCHAR  ucStopFlag:1;
    UCHAR  ucSdbFlag:1;
    UCHAR  ucActive:2;
    UCHAR  ucReserved:1;

    UCHAR  ucSRID;
    UCHAR  aucRese[2];

    ULONG  ulSetupSeqNum;
    ULONG  ulStartSeqNum;
    ULONG  ulStopSeqNum;
    ULONG  ulSdbSeqNum;
}VOS_PACKED RP_SEQUENCE_NUM_S;

typedef struct tagA11_SQOS_DSCP
{
#if VOS_LITTLE_ENDIAN == VOS_BYTE_ORDER
   UCHAR ucReserve1:4,              /* ���ꨢ? */
         ucReversDscpRemarkFlag:1,  /* ��?����������?AAA��?��???���騢?Allowed Differentiated Services Marking ?��o?��?D? */
         ucDSCPFlag_O:1,            /* ????����������?MS??��?DD��?��������??����??��?��������?��?��???����?��?��1��? */
         ucDSCPFlag_E:1,            /* ????����������?MS??��?DD��?��������??����??����?����?��1��?EF DSCP */
         ucDSCPFlag_A:1;            /* ????����������?MS??��?DD��?��������??����??����?����?��1��?AF DSCP */

   UCHAR ucReserve2   :2,
         ucForwardDscp:6;           /*��?�䨮��?����D��????����??*/

   UCHAR ucReserve3     :1,
         ucDscpRtBitFlag:1,         /* AAA??�����?��?D??D��?��?�㨹o?RT-Marking��?��?1?�㨹o??��????��?��??��?��?a0 */
         ucReverseDscp  :6;         /* ����?��?���̨�����?? */

   UCHAR ucReserve4[1];
#else
   UCHAR ucDSCPFlag_A:1,            /* ????����������?MS??��?DD��?��������??����??����?����?��1��?AF DSCP */
         ucDSCPFlag_E:1,            /* ????����������?MS??��?DD��?��������??����??����?����?��1��?EF DSCP */
         ucDSCPFlag_O:1,            /* ????����������?MS??��?DD��?��������??����??��?��������?��?��???����?��?��1��? */
         ucReversDscpRemarkFlag:1,  /* ��?����������?AAA��?��???���騢?Allowed Differentiated Services Marking ?��o?��?D? */
         ucReserve1:4;              /* ���ꨢ? */

   UCHAR ucForwardDscp:6,           /*��?�䨮��?����D��????����??*/
         ucReserve2   :2;

   UCHAR ucReverseDscp:6,           /* ����?��?���̨�����?? */
         ucDscpRtBitFlag:1,         /* AAA??�����?��?D??D��?��?�㨹o?RT-Marking��?��?1?�㨹o??��????��?��??��?��?a0 */
         ucReserve3:1;

   UCHAR ucReserve4[1];

#endif
}VOS_PACKED A11_SQOS_DSCP_S;

/* IPv6 ��??����y?Y?��11 */
typedef struct  tagin6_addr
{
    union
    {
        UCHAR        u6_addr8[16];
        USHORT       u6_addr16[8];
        ULONG        u6_addr32[4];
    } in6_u;
    #define s6_addr      in6_u.u6_addr8
    #define s6_addr16    in6_u.u6_addr16
    #define s6_addr32    in6_u.u6_addr32
}in6_addr;

typedef struct tagA11ServiceOption
{
    ULONG ulMaximumLinkFlowsTotal;
    UCHAR ucSOProfile[A11_MAX_SO_NUM];
    /* Service Option Profile
    ��y����??����0������? SO?a33��???��y
    ��y����??����1������? SO?a59��???��y
    ��y����??����2������? SO?a64��???��y
    ��y����??����3������? SO?a67��???��y*/
}VOS_PACKED A11_SQOS_SERVICEOPTION_S;

typedef  struct tagA11AuthFlowProfileID
{
    USHORT usAuthFlowProfileID;
    UCHAR ucDirection;/*?��?��  1 ����?�� 0 ???�� 2*/
    UCHAR ucResv[1];
}VOS_PACKED A11_AUTH_FLOWPROFILE_ID;

typedef struct tagA11_QOS_INFO
{
    ULONG ulIpQos;                  /* IP Qos */
    ULONG ulInputPeakRate;  /*��?DD��??��?��?����? �̣�???abps*/
    ULONG ulOutputPeakRate; /*??DD��??��?��?����? �̣�???abps*/
    ULONG ulGuarantBitRateUp; /*PDSN��??�쨦?DD����?��?��?�� (bps)*/
    ULONG ulGuarantBitRateDown; /* PDSN��??��??DD����?��?��?��(bps) */
    ULONG ulAllowed_AB_BET; /*bps*/

    ULONG ulMaxConnection;
    UCHAR ucRateFlag;
    UCHAR ucAllowed_PTFTs;  /* Allowed Persistent TFTs */
    UCHAR ucMaxPerFlowPriorityforUser;        /* Maximum Per Flow Priority for the User  */

    #if (UGW_BYTE_ORDER == UGW_BIG_ENDIAN)
    UCHAR ucInterUserPriority: 4;                /* Inter-User Priority 0 ~7*/
    UCHAR ucOriInterUserPriority: 4;             /*��??��3?��?????��??��?? 0~7 ����1???SM��1��?��?����3��?????�̨���????��?D��?��*/
    #else
    UCHAR ucOriInterUserPriority: 4;             /*��??��3?��?????��??��?? 0~7 ����1???SM��1��?��?����3��?????�̨���????��?D��?��*/
    UCHAR ucInterUserPriority: 4;                /* Inter-User Priority 0 ~7*/
    #endif

    A11_SQOS_SERVICEOPTION_S stA11SOProfile;
    A11_AUTH_FLOWPROFILE_ID stAuthFlowProfileID[A11_MAX_FLOW_PROFILE_ID];     /* Authorized Flow Profile IDs for the User */
    A11_SQOS_DSCP_S stAllowedDSCPMarking; /* Allowed Differentiated Services Marking */
}VOS_PACKED A11_QOS_INFO_S;

typedef struct tagMIPAGENT_SHARESECRET_S
{
    UCHAR ucLen;
    UCHAR ucSecret[RD_HW_MIPAGENT_MNHA_SECRET_MAXLEN];  /* ?���̨�?��?? */
    UCHAR ucResv;      /*zhaoxu00140270*/
} MIPAGENT_SHARESECRET_S;


typedef struct
{
    ULONG ulIpQos;
    ULONG ulSessionTimeOut;
    ULONG ulAAAindex;
    ULONG ulInputPeakRate;      /* ��?DD��??��?��?��, �̣�???abps*/
    ULONG ulOutputPeakRate;     /* ??DD��??��?��?��, �̣�???abps*/
    ULONG ulGuarantBitRateUp;   /* PDSN��??�쨦?DD����?��?��?�� (bps)*/
    ULONG ulGuarantBitRateDown; /* PDSN��??��??DD����?��?��?��(bps) */
    UCHAR ucRateFlag;
    UCHAR ucPreparedFlag;
    UCHAR ucResv[2];
    /* ucRateFlago��4??����???����?��???D??��?��D??��ꡧ0������???��D��?1������?��?��?��?��o
    0000***1                �̨�0??������?��?��?��?��?ulInputPeakRate
    0000**1*                �̨�1??������?��?��?��?��?ulOutputPeakRate
    0000*1**                �̨�2??������?��?��?��?��?ulGuarantBitRateUp
    00001***                �̨�3??������?��?��?��?��?ulGuarantBitRateDown */
}VOS_PACKED QOS_ACCOUNT_INFOR;

typedef struct
{
    UCHAR ucGroupNumber;
    UCHAR ucInstanceId;
    UCHAR ucCompressFlag;
}PPP_COMPRESS_CFG;

typedef struct tagPTM_COMPONENT_INFO
{
    VOS_UINT64 ullSelfCsi;      /* ��?����?tCSI */
    VOS_UINT64 ullSelfSgId;     /* ��?����?t?��?��SGID */
    VOS_UINT32 ulSelfCmpIdx;    /* OS?����?����D������?t?�¨�y */
    VOS_UINT32 ulSelfCmpIdxInSG;/* SG?����?����D������?t?�¨�y */
    VOS_UINT32 ulHandle;        /* HANDLE��?��?�����̡�2a */
    USHORT usOsID;               /* ���騰a:2?��??��?����D?��?��??3?��??����? */
    USHORT usReserve990;
}PTM_COMPONENT_INFO_S;

/* ?1??����?�䨪3???��11 */
typedef struct
{
    ULONG ulDmpuDpeNum;                                     /* ����?����?DPE??3����y��????��1��?��?a14 */
    ULONG ulMppcUserNum[MAX_DMPU_NUM][MAX_DPE_NUM_PDSN];    /* ��??����??��?�¡���?��DPE��??��??��?MPPC��??�쨺y */
    ULONG ulVjUserNum[MAX_DMPU_NUM][MAX_DPE_NUM_PDSN];      /* ��??����??��?�¡���?��DPE��??��??��?VJ��??�쨺y */
    UCHAR ucDpeCpuRate[MAX_DPE_NUM_PDSN];                   /* ��??����???��|����?��?��DPE��?CPU??��??�� */
}SC_COMPRESS_STATE_S;

/*
 * ��?��Y1y3��?D����?��o��?����?��????���???��?
 */
typedef struct tagHAMsgHead
{
    struct tagHAMsgHead *pNext;
    USHORT  usSrcSlot;
    USHORT  usDstSlot;
    ULONG   ulSrcModuleID;
    ULONG   ulSrcSubID;
    ULONG   ulDstModuleID;
    ULONG   ulDstSubID;
    USHORT  usMsgMode;
    USHORT  usMsgType;
    ULONG   ulMsgLen;
    ULONG  ulSequence;  /*a sequence of message when message be into sending quene*/
    /* Added before Union since application assign their data to ulMsgData.
     * This can be used by application for recognising ack for which data
     */
    ULONG ulApplData;
    union
    {
        ULONG ulErrID;
        ULONG ulMsgData;
    }unMsgInfo;
}HAMSGHEAD_S;

typedef struct  tagSYS_MSG
{
    USHORT   usMessageType;              /*��?����??��?����?��?��?����?*/
    USHORT   usPririty;                          /*?����??��??�ꡧ��??���??o?����?��?,?��3?4??��??��?? */
    ULONG    ulSrcModuleID;                 /*?��?��?��o?*/
    ULONG    ulDstModuleID;                 /*??����?��?��o?*/
    ULONG    ulSequence;                      /*����?��D��o?,RPC������?*/

    ULONG    ulSrcSlotID;                    /* ?��2???o? */
    ULONG    ulDstSlotID;                       /* ??��?2???o? */
    UCHAR    ucMsgType;                     /* ???�騤��D����?��?PDU, TIMER, REQUEST, NOTIFY... */
    UCHAR    ucMsgBodyStyle;            /*��?����???��???�騪��o��???�騬?��?��?��?��?��?��?,?��FSU?D?�¨�a��?����??��?��?��?MBuf��?��?*/
    USHORT   usMsgCode;                    /* ???��??��???��????�騤��D����???��? */

    USHORT   usResponseType;             /* ��?��?��a?��?����?��?��??�쨮|��e��oACK/ NOACK/NEGACK*/
    USHORT   usFrameLen;                     /* frame content ��?3��?�� ��?��??�쨺y?Y??3��?��   */
/* Modified start by jiangyongliang 50758 at 2012-03-09 PGPV2R6 for 1��3������??linux */
#ifndef __X86_PLATFORM__
    VOID   * ptrMsgBody;                   /*???�騬?????*/
#else
    ULONG    ulMsgBodyOffset;                   /*???�騬?????*/
#endif
/* Modified end by jiangyongliang 50758 at 2012-03-09 PGPV2R6 for 1��3������??linux */
    USHORT   usAppSeqNum;                /*��|��?2??�̨�Do?��?��?��������?����?o��?����?��????����|��e?????������1?��a*/
    USHORT   usReserved;                     /*���ꨢ? ��?��?o����?3?��1��?*/
}  MSG_HDR_S, SYS_MSG_S;

/* APN 1?��D��?D?����?��11 */
typedef struct
{
    VOS_UINT16  usApnIndex;         /*APN ��?index*/
    VOS_UINT8   ucSelectionMode;    /*??��??��D����?��??????�꨺?D??��??DD?��2��0 ?��2�� 12??��2��*/
    VOS_UINT8   ucTransAccess;      /*��??��?����?��?��?*/

    VOS_UINT8   aucAPN[M_CFG_MAX_APN_STRING_LEN]; /*APN ??*/
    VOS_UINT8   aucVRF[M_CFG_MAX_VRFNAME_LEN];  /*VPN ??*/

    VOS_UINT32 ulVPNId;             /*VPN index*/

    VOS_UINT8   ucAuthMode;         /*��?��??��?����?��??��??��������D��:*/
    VOS_UINT8   szAuthPwd[M_CFG_MAX_APN_PASS_LEN + 1];   /*��??��?��??*/
    VOS_UINT8   ucLock;             /*???������??*/
    VOS_UINT8   ucL2tp;             /*l2tp����??build2��1��?*/

    VOS_UINT8   ucAddrMod;              /*��??����???��?��?*/
    VOS_UINT8   ucAddrModRadiusPrior;   /*?��3?radius ��??����???��??��*/
    VOS_UINT8   ucStaticIpConflict;     /*��??��3?��?����??*/
    VOS_UINT8   ucStaticIpRouteFlag;    /*?������??�������??*/

    VOS_UINT8   ucPPPAddrMod;           /*ppp��??����???��?��?build2��1��?*/
    VOS_UINT8   ucMipAgent;                  /*mip agent����??*/
    VOS_UINT8   ucMipAaa;               /*mipaaa ����??build2��1��?*/
    VOS_UINT8   ucMipAaaRmv;            /*mipaaarmv ����??build2��1��?*/

    VOS_UINT8   ucVirtualApn ;          /*��?��??��3?D��?aAPN*/
    VOS_UINT8   ucVirtualApnActFlg ;    /*D��?aAPN��?��??����?��D��??��?��??*/
    VOS_UINT8   ucSessionSw;            /*session-timerout ����D��*/
    VOS_UINT8   ucIdleSw;               /*idle-timerout ����D��*/

    VOS_UINT8   ucRoamControl;          /* ?t��?��??��?����?????����?? 1:?��D��?����? 0:2??��D��?����? */
    VOS_UINT8   ucVisitControl;         /* ��Y��?��??��?����?????����?? 1:?��D��?����? 0:2??��D��?����? */
    VOS_UINT8   ucStripFlag;            /* ��t��?����??*/
    VOS_UINT8   ucCdVersion;            /* ����3��??��??��̣�������??-��?D-������?��?*/

    VOS_UINT8   ucVolumnMode;           /* ���¨�?��3??��?������?*/
    VOS_UINT8   ucPcopri;
    VOS_UINT8   ucCdVersionSwitch;      /*���ꨢ?��???��??Y����??��D��?��?o����??1*/
    VOS_UINT8   ucRadiusDisconnectFlag; /* ��?��?��|����pod disconnect???�����??��???��??aenable��1?����|���� */

    VOS_UINT16  usIdleTime;             /*idle-timerout ��?����3��*/
    VOS_UINT16  usSessionTime;          /*session-timer��?����3��*/

    VOS_UINT8   aucGnifName[M_CFG_MAX_VRFNAME_LEN+1];   /*Gn?����?��??��32??��?��?*/
    VOS_UINT8   ucAuthModePcoPriorFlag;                 /*PCO ��?D?��??��*/
    VOS_UINT8   ucAccessStaticIpFlag;                   /*?2��?��??��?����?����??*/
    VOS_UINT8   ucpppAccess;                            /*��?��?PPP ?����?����??*/

    VOS_UINT16  usServerGroupID;        /*radius-server ID*/
    VOS_UINT16  usQosProfileIndex;      /*QoSprofile*/
    VOS_UINT32  ulGnIpAddress;          /*Gn?����?IP ��??��*/

    VOS_UINT16  usGroupNum;
    VOS_UINT8   ucPppAddrModRadiusPrior;
    VOS_UINT8   ucSgsnMappingPlmnFlag;  /* ��?��?��1?��sgsn-ip��3��?plmn */

    VOS_UINT8   ucSgsnMappingRatFlag;   /* ��?��?��1?��sgsn-ip��3��?rat */
    VOS_UINT8   ucAaaApnSecondAuth ;    /*��?��??��3?��?��?��??��̨�?t��?����AAA??����*/
    VOS_UINT8   ucPerfApnType;          /*D??����3??��1��?��?APN����D��*/
    VOS_UINT8   ucAaaAcctApnType;       /*AAA??��????�騺1��?��?APN����D��*/

    VOS_UINT8   ucOcsApnType;       /*��?OCS???��???�騺1��?��?APN����D��*/
    VOS_UINT8   ucCgApnType;        /*?��̣���1��?��?APN����D��*/
    VOS_UINT8   ucIdleUpdataeMsg;   /*��?1?idle3?������?��?����?��?��D????��*/
    VOS_UINT8   ucQoSSWFlag;        /*���ꨢ?��???*/

    VOS_UINT16  usPppMru;           /*MRU*/
    VOS_UINT8   ucStaticIpRouteType;/*��̬·���·�����*/
    VOS_UINT8   aucReserved[1];

    VOS_UINT8   aucL2tpVRF[M_CFG_MAX_VRFNAME_LEN];

    VOS_UINT32  ulL2tpVPNId;
    VOS_UINT8   ucServiceReportSwitch;
    VOS_UINT8   ucBwmControlFlag;
    VOS_UINT8   aucReserved1[2];

    VOS_UINT8   aucIterfaceID[IPV6_INTERFACEID_LENGTH+1];   /*ipv6 �ӿ�id*/
    VOS_UINT8   ucV6AddrMod;
    VOS_UINT8   ucPmipv4VpnSwitch;
    VOS_UINT8   ucL2tpAttribute;

    VOS_UINT8   aucIpv6VRF[M_CFG_MAX_VRFNAME_LEN];  /*VPN ??*/
    VOS_UINT32  ulIpv6VPNId;             /*VPN index*/
    VOS_UINT32  ulPmipv4VPNId;             /* pmipv4 VPN index */

    VOS_UINT32   ulPmipHaip;
    VOS_UINT32   ulPmipSpi;

    VOS_UINT16   usPmipLifetime;
    UCHAR     aucPmipSkey[HSGW_SECRET_SA_SIMPLE_LENTH + 1];        /* Skey */
    UCHAR     aucPmipCkey[HSGW_SECRET_SA_NEW_CIPHER_LEN + 1];        /* Ckey */

    UCHAR     ucPmipEncryptFlag;
    UCHAR    aucReserve1265[11];               /* ?�¨�a1????�診1��? */
}VOS_PACKED S_CFG_DOMAINNODE;

typedef struct
{
#if (UGW_BYTE_ORDER == UGW_LITTLE_ENDIAN)

    UCHAR IMSI_OE_IND: 4;

    UCHAR IMSI_ID1: 4;

    UCHAR IMSI_ID2: 4;

    UCHAR IMSI_ID3: 4;

    UCHAR IMSI_ID4: 4;

    UCHAR IMSI_ID5: 4;

    UCHAR IMSI_ID6: 4;

    UCHAR IMSI_ID7: 4;

    UCHAR IMSI_ID8: 4;

    UCHAR IMSI_ID9: 4;

    UCHAR IMSI_ID10: 4;

    UCHAR IMSI_ID11: 4;

    UCHAR IMSI_ID12: 4;

    UCHAR IMSI_ID13: 4;

    UCHAR IMSI_ID14: 4;

    UCHAR IMSI_ID15: 4;

#else

    UCHAR IMSI_ID1: 4;

    UCHAR IMSI_OE_IND: 4;

    UCHAR IMSI_ID3: 4;

    UCHAR IMSI_ID2: 4;

    UCHAR IMSI_ID5: 4;

    UCHAR IMSI_ID4: 4;

    UCHAR IMSI_ID7: 4;

    UCHAR IMSI_ID6: 4;

    UCHAR IMSI_ID9: 4;

    UCHAR IMSI_ID8: 4;

    UCHAR IMSI_ID11: 4;

    UCHAR IMSI_ID10: 4;

    UCHAR IMSI_ID13: 4;

    UCHAR IMSI_ID12: 4;

    UCHAR IMSI_ID15: 4;

    UCHAR IMSI_ID14: 4;

#endif
}A11_IMSI_S; /* A11D?��??D��?��?��?IMSI?����?*/

//
//imsi stuct define
//
typedef struct tagGTP_IMSI_S
{
#if UGW_BYTE_ORDER == UGW_LITTLE_ENDIAN
     UCHAR MCC1  : 4;
     UCHAR MCC2  : 4;
     UCHAR MCC3  : 4;
     UCHAR MNC1  : 4;
     UCHAR MNC2  : 4;
     UCHAR MSIN1 : 4;
     UCHAR MSIN2 : 4;
     UCHAR MSIN3 : 4;
     UCHAR MSIN4 : 4;
     UCHAR MSIN5 : 4;
     UCHAR MSIN6 : 4;
     UCHAR MSIN7 : 4;
     UCHAR MSIN8 : 4;
     UCHAR MSIN9 : 4;
     UCHAR MSIN10: 4;
     UCHAR SPARE : 4;        /* ��?1��?3? */
#else
     UCHAR MCC2  : 4;
     UCHAR MCC1  : 4;
     UCHAR MNC1  : 4;
     UCHAR MCC3  : 4;
     UCHAR MSIN1 : 4;
     UCHAR MNC2  : 4;
     UCHAR MSIN3 : 4;
     UCHAR MSIN2 : 4;
     UCHAR MSIN5 : 4;
     UCHAR MSIN4 : 4;
     UCHAR MSIN7 : 4;
     UCHAR MSIN6 : 4;
     UCHAR MSIN9 : 4;
     UCHAR MSIN8 : 4;
     UCHAR SPARE : 4;        /* ��?1��?3? */
     UCHAR MSIN10: 4;
#endif
} GTP_IMSI_S;

/*AM-USMo��AM-LAP2????��????��???��*/
/* ?D?��:DT??��??��11��?D����a��?2?DT???��2??������???t */
typedef struct tagUSM_LAP2_MSG
{
    UCHAR ucMsgType;         /*?����?��??������???��?����?��??��������??��???��?���??����????����|?��?2��?��??��?��???��?2��?��??�쨨��??*/
    UCHAR ucMaskForFrameRouteCheck;         /* o��?������?����?o?2��������1��? */
    UCHAR ucSectionNum;      /*LAP��???��?��??��?��?����?��??��??o?*/
    UCHAR ucLapNo;

    UCHAR ucMaskOrPrefixLen;
    UCHAR ucGtpVers;
    UCHAR ucSduVcpuId;       /* zhangjinquan IP Lease��?D? ???��SduVcpuId��??? 2011-08-31 */
    UCHAR ucDelCause;         /* �����?����???-��������D�� */

    VOS_UINT64 u64Csi;        /*��??��???������?e?��?����?CSI*/
    GTP_IMSI_S stImsi;        /* zhangjinquan IP Lease��?D? ��??��IMSID??��(D-) ��?8��??��*/
    ULONG ulPdpIndex;        /*PDP��??????�¨�y*/
    ULONG ulTeidc;

    ULONG aulPdpAddr[LAP_IP_ULONG_NUM];     /*��??��*/
    ULONG aulMSISDN[LAP_MSISDN_ULONG_NUM];      /*MSISDN*/
    ULONG aulPrimaryDNS[LAP_IP_ULONG_NUM];
    ULONG aulSecondaryDNS[LAP_IP_ULONG_NUM];

    USHORT usVpnID;           /*VPN ID*/
    USHORT usPoolIndex;      /*AAA����??��??��3??�¨�y*/
    USHORT usApnIndex;       /*APN?�¨�y*/
    USHORT usCheckSum;       /*?��?��o��*/

    UCHAR aucPoolName[LAP_POOL_NAME_MAX_LENGTH + 1];
    UCHAR ucUserType:2;       /*0  GTPC    1 PPP   2 MBMS*/
    UCHAR ucStaticIpRouteType:2;/*?������??���騤��D��*/
    UCHAR ucSCID:4;          /*SC ID*/
    UCHAR ucAddrAllocType:4; /*��??����???��?��?*/
    UCHAR ucAddressType:4;   /*��??������D��*/
    UCHAR ucAddrInheritFlag     :1;         /* ������?��?��?��1��?��?��??��?��3D */
    UCHAR ucIsTimeOutFlag       :1;         /* zhangjinquan ???������??��?��?��?��?lap3��1|???��o��??��D��?????��?3?����?��?? */
    UCHAR ucIsDualStack         :1;
    UCHAR ucFindLAPCenterErr    :1;
    UCHAR ucRedudancyFlag       :1;         /* ?2��?��??���?��Y��?D?��??2��?��?��Y��1?������???? */
    UCHAR ucRedundancyRouteFlag  :1;
    UCHAR ucReleaseTimeRedirectFlag    :2;         /* VOS_TRUE:������?��?1?????��?release time,��??��1���̨���y������?���䨺����1��?��?����???aMin[byte318?��,release-time]  */

    UCHAR aucReserve[4];     /*???��11��?��?D?8��??��????*/
}USM_LAP2_MSG_S;

/* ??����?����| */
typedef struct tagAaaAuthRspMsg
{
    MSG_HDR_S stNeMsgHdr;             /* NE80���� */
    ULONG ulMsgType;                /* ???�騤��D�� */
    ULONG ulSDBIndex;               /* context?�¨�y ?��SDB?�¨�y */

    UCHAR ucStcValue;

    UCHAR ucResv;
    UCHAR ucResult;                 /* ??����?��1? */
    UCHAR ucUsernameLen;            /* ��??��??3��?�� */
    UCHAR ucUsername[NAI_NAME_LEN+1]; /* ��??��?? */
    QOS_ACCOUNT_INFOR stQosAccInfo; /* ??��?D??�� */
    ULONG ulIdleTimeout;            /* ?��?��3?��������?? */
    ULONG ulIPMTU;                  /* MTU2?��y */
    ULONG ulIp;                     /* IP��??�� */
    ULONG ulIpMask;                 /* IP��??��������??��?? */
    ULONG ulPIMARY_DNS_SERVER;      /* ?��DNS SERVER */
    ULONG ulSECOND_DNS_SERVER;      /* �䨮DNS SERVER */
    ULONG ulAlwaysOn;               /*r002*/
    ULONG ulMNAAAFlag;
    ULONG ulAcctInterimInterval;
     /* L2TP */
    USHORT usTunnelType[AAA_L2TP_LNS_NUM];                 /* ?���̨�����D����????��???��3?L2TP */
    USHORT usTunnelMediaType[AAA_L2TP_LNS_NUM];            /* 1?12��?����D����????��???��3?IP */
    ULONG  ulTunnelServer[AAA_L2TP_LNS_NUM];                   /* LNS��??�� */
    ULONG  ulTunnelPreference[AAA_L2TP_LNS_NUM];
    UCHAR  ucTunnelClientAuthId[AAA_L2TP_LNS_NUM][RD_TUNNEL_STR_MAX_LENG];   /* LAC?? */
    UCHAR  ucTunnelServerAuthId[AAA_L2TP_LNS_NUM][RD_TUNNEL_STR_MAX_LENG];  /* LNS?? */
    UCHAR  ucTunnelPrivateGroupId[AAA_L2TP_LNS_NUM][RD_TUNNEL_STR_MAX_LENG];          /* ?���̨�GroupID */
    UCHAR  ucTunnelAssignId[AAA_L2TP_LNS_NUM][RD_TUNNEL_STR_MAX_LENG];         /* ?���̨�ID */
    UCHAR  ucPassword[AAA_L2TP_LNS_NUM][RD_TUNNEL_STR_MAX_LENG+1];   /* ?���̨�?��?? */
    UCHAR ucAAANotReturnIP;
    UCHAR ucRes;

    UCHAR  ucFramedPool[RD_FRAMED_POOL_MAX_LENG+1];  /* AAA ����??��?��??��3???framed-pool */
    UCHAR ucReplyMsg[NAI_NAME_LEN+1];

    UCHAR ucNaiMsid[NAI_NAME_LEN+1];
    /* Added start by zhangxiujuan 60016360 at 2006-07-06 V800R005C01B010 for MIP Agent */
    UCHAR  ucCdmaUserType;                /*0-SIP, 1---MIP, 2---MIP Agent*/
    UCHAR  ucMipAgentFlag;
    USHORT usMipAgentLifetime;
    ULONG  ulMipAgentHaAddr;
    ULONG  ulMipAgentHomeAddr;
    ULONG  ulMipAgentSpi;                       /* PMIPv4��??�쨮?HA??��2��?��a??SPI */
    ULONG  ulPmipV6Spi;                         /* PMIPv6��??�쨮?LMA??��2��?��a??SPI */

    MIPAGENT_SHARESECRET_S stMipAgentSecret;                   /* PMIPv4��2��?��a?? */
    UCHAR aucPmipV6Secret[RD_MIPV6AGENT_MNHA_SECRET_LEN];      /* PMIPv6��2��?��a?? */
    UCHAR ucMdn[MDN_MAX_LEN+1];
    UCHAR ucResv3;
    USHORT  bulIpQosFlag : 1,                  /* IP Qos */
            bulInputPeakRateFlag : 1,  /*��?DD��??��?��?����? �̣�???abps*/
            bulOutputPeakRateFlag : 1, /*??DD��??��?��?����? �̣�???abps*/
            bulGuarantBitRateUpFlag : 1, /*PDSN��??�쨦?DD����?��?��?�� (bps)*/
            bulGuarantBitRateDownFlag : 1, /* PDSN��??��??DD����?��?��?��(bps) */
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
    UCHAR szUserProfileName[A11_USER_PROFILE_NAME_LENGTH + 1]; /*User Profile??3?��?��?��?��?*/
    UCHAR ucResv4[3];

    UCHAR aucVpnName[RD_HW_VPN_NAME_LEN_MAX + 1]; /* vpn name */
    UCHAR ucFilterID;
    UCHAR ucIPType;
    UCHAR ucIPTypeFlag; /* ��?����??��?��?��?D����?��?RD_3GPP2_IP_SERVICES_AUTHORIZED��?D?��?1��oD����??��0��o?��D����? */
    UCHAR ucActiveStopIndication:1;
    UCHAR ucUserClassAAAFlag:1;
    UCHAR ucResrved:6;
/* Added end by zhangxiujuan 60016360 at 2006-07-06 V800R005C01B010 for MIP Agent */
    UCHAR ucFramedInterfaceID[RD_FRAMED_INTERFACE_ID_LEN];
    UCHAR ucFramedIPV6Pool[RD_FRAMED_POOL_MAX_LENG + 1];
    UCHAR ucFramedIPV6Prefix[RD_FRAMED_IPV6_PREFIX_LEN];
    UCHAR ucLmaAddr[RD_FRAMED_IPV6_PREFIX_LEN];         /* PMIPv6 LMA��??�� */
    ULONG ulIpv6Mask;                     //��??1��???
    in6_addr stPriDNSIP;
    in6_addr stSecDNSIP;

}AAA_PPPC_AUTH_RSP_S;


typedef struct tagRP_EHRPD_USER_INFO_S
{
    /* eHRPD��??��?��1?��?D? */
    USHORT us3GPPCC;
    UCHAR aucUsername[DIAM_AUTH_NAI_MAX_LEN + 1];    /* ��??��?? */
    UCHAR aucMnId[DIAM_AUTH_MNID_MAX_LENGTH + 1];        /* Mobile-Node-Identifier */
    UCHAR aucMSK[DIAM_AUTH_MSK_LEN];                 /* MSK */
    UCHAR ucApnInfoNum;                              /* AAA����12??����?������??apninfoD??�� */
    UCHAR ucReserved;
    UCHAR aucApnInfo[0];                             /* APN CONFIGURATION */
}RP_EHRPD_USER_INFO_S;

typedef struct tagA11_HANDOFF_INFO_S
{
    ULONG ulSrcPcfIp;
    ULONG ulSrcKey;

    RELTMR_T ulUpdTimerId;

    ULONG ulSrcSpi;
    UCHAR ucstate;
    UCHAR ucUpdSendTimes;
    UCHAR ucResv[2];            /*�ֽڶ���*/
}A11_HANDOFF_INFO_S;


typedef struct
{
    ULONG ulRpIndex;
    ULONG ulTeidc;

    /* ?�¨�y��??? */
    ULONG       ulPcfIP;
    A11_IMSI_S  stImsi;
    GTP_MSISDN  szMsisdn;                     /* ��??��MSISDND??��(D-)��?8��??�� */
    UCHAR       aucMEID[8];
    UCHAR       aucESN[4];
    UCHAR       pucNAI[A11_MAX_NAI_LENGTH +1];                /* NAI */

    ///TODO:���騰a:DT??��??��11��???��?����????��?��?DT????��|��?USM_BACKUP_RP_INFO_S��?��Y?��11��?����?a��1??o��3??����a
    ///TODO:���騰a:��?��?��???D����a����?��8��??��????��?��DD?����?����?��???,???����???o������?��,?��??��?��???��?��?hash?�¨�y,��??��?��3????��hash����㨹!!!

    RP_EHRPD_USER_INFO_S *pstEhrpdUserInfo;  /* hsgw��??������?apn�̨�D??�� */
    UCHAR       *pstUsername;                /* �̡���??��??3��?���䨮����63��1��??����?����???����?��?��? */
    UCHAR       *pucVsncpReq;                /* ?D??3??�㨺?��??������pdn��????��???�� */
    ULONG       ulUsmStateTimerId;          /* USM���䨬??��?������?��ID */
    ULONG       ulA11StateTimerId;          /* A11���䨬??��?������?��ID */

    ULONG       ulSessionTimeOut;           /* Session Time Out */
    ULONG       ulReleaseCode;              /* ��??�쨨��???��2??-����??��?AM_RELEASE_CODE_E��??����D???����?��������???-����??������?��a????��? */

    ULONG       ulMainA10Key;               /* Main A10 GRE KEY */
    ULONG       ulSpi;                      /*SPI */

    ULONG       ulReqIDHigh;                /* A11-Registration Request Identification high */
    ULONG       ulReqIDLow;                 /* A11-Registration Request Identification low */

    ULONG       ulUpdIDHigh;                /* A11-Registration Update Identification high */
    ULONG       ulUpdIDLow;                 /* A11-Registration Update Identification low */

    ULONG       ulLifeTimerId;              /* LifeTime?������?��ID */
    ULONG       ulSessionUpdateTimerId;     /* SessionUpdateReq??����?������?��ID */

    ULONG       ulRegUpdateTimerId;         /* RegUpdateReq??����?������?��ID */
    ULONG       ulSessionTimeId;            /* ��??���?session time?������?��ID */
    ULONG       ulReAuthTimeId;             /* ��??���?reauth time?������?��ID */
    /* BEGIN: Added for PN: PS10.1 HSGW by lihairong, 2013/3/4 */
    ULONG       ulConMainTimerId;          /* A11,LCP,EAP����?����ꨢ??������?��ID */
    /* END:   Added for PN: PS10.1 HSGW by lihairong, 2013/3/4 */

    ULONG       ulWaitPcfReleaseTimeId;     /* lifetime ��? 0��?rrq?������?��id */
    ULONG       ulCorrelationID;

    ULONG       ulSetUpTimeStamp;
    ULONG       ulCurAllowed_AB_BET;

    USHORT      ausA10IndexArray[SDB_MAX_A10_PER_RP_SESSION];
    USHORT      ausPdnIndexArray[A11_MAX_PDN_NUM];
    UCHAR       ucMaxSLotId;
    UCHAR       aucReserv3[3];
    //UCHAR       ucPdnId4TFT[SDB_MAX_TFT_PER_RP_SESSION];
    A11_IMSI_S  stLuimImsi;

    ULONG       ulMagicNum;             /* Magic-Number */
    ULONG       ulAccm;                 /* ACCM */

    USHORT      usBsGroupIdx;
    USHORT      usPcfIndex;
    USHORT      usTrcMsgLen;
    USHORT      usMtu;                  /* MTU */


    USHORT      usDomainIndex;              /* Domain Index */
    USHORT      usVirtualDomainIndex;       /* virtual Domain Index */
    USHORT      usLifetime;                 /* Lifetime?������?�¨���3���?�̣�??:s */
    USHORT      usProtocolType;

    USHORT      usTokenId;
    USHORT      bAlawysOn           : 1,            /* ��?��??aAlwaysOn��??�� */
                bDataTrcUp          : 1,            /* ��??�쨦?DD?����������?? */
                bDataTrcDown        : 1,            /* ��??��??DD?����������?? */
                beHRPDMode          : 1,            /* 0:PDSN  1:HSGW */
                ucLiFlag            : 1,            /* ��?��??����y��y?Y */
                bUsmNotifyA11Flag   : 1,            /* ��??��?��??1y3����?��?����?a1yA11 */
                bUsmNotifyPPPFlag   : 1,            /* ��??��?��??1y3����?��?����?a1yPPP */
                bUsmNotifyPDNFlag   : 1,            /* ��??��?��??1y3����?��?����?a1yPDN */
                bUsmHasExitFuncEntry : 1,           /* ��?��???��?1y��3��?��?��?o����y ��?����??2?D����a��?��Y */
                bUsmActiveUserNumFlg : 1,           /* ��?��?��3??1y��??�쨺y����?? ��?����??2?D����a��?��Y */
                bUsmLicenseFlg      : 1,            /* ��?��?��3??1ylicense ��?����??2?D����a��?��Y */
                usVirtualDomainPerf : 1,            /* ��?��?��?D��?aDomain??DDD??����3?? */
                ucHandoff           : 2,
                bHandoffExecution   : 1,
                bMEIDValidFlg       : 1;            /* aucMEID��DD��D?����?? */

    USHORT      usIriTargetMap;
    USHORT      usIdpTargetMap;

    A11_HANDOFF_INFO_S stHandoffInfo;
    A11_QOS_INFO_S stA11QoS;
    RP_SEQUENCE_NUM_S astSequenceNum[A11_MAX_A10_PER_RP_SESSION];

    UCHAR       ucPanid[A11_MAX_ANID_LENGTH];
    UCHAR       ucCanid[A11_MAX_ANID_LENGTH];
    UCHAR       aucSubnet[A11_AIR_REC_MAX_SUBNET_LEN];      /*Subnet For HRPD d7*/
    UCHAR       ucSubnetLen;

    UCHAR       ucBsId[AM_BSID_LEN];
    UCHAR       ucMeiCVSE;
    UCHAR       bSeqLinkNo : 3,  /*��?����????��???teidc�㨮?����?sequece����?�¨�y*/
                bSlaveReleaseFlg : 1, /* ?��SG?��??o����?��?��?��?��?��a2?����??��??t */
                bReservd33355 : 4;

    UCHAR       ucUsmState;                 /* USM���䨬??���̡�?����䨬? */
    UCHAR       ucA11State;                 /* A11���䨬??���̡�?����䨬? */
    UCHAR       ucDpeId;
    UCHAR       ucSduVcpuId;
    UCHAR       ucSdbKeyMask;
    UCHAR       ucPdnNum;
    UCHAR       ucSessionUpdateRetryCount;  /* SessionUpdateReq??�����?��y */
    UCHAR       ucRegUpdateReqRetryCount;   /* RegistrationUpdateReq??�����?��y */

    UCHAR       ucServiceOption;
    UCHAR       ucA10ConnNumbers;
    UCHAR       ucDmpuId;                   /* ??��?����?�� ��??��?a2?��??3*/
    UCHAR       ucDmpuDpeId;                /* ??��?����?��DPE */

    UCHAR       ucCode;                     /* ��?����LI��?��?��??-���� */
    UCHAR       bSessionVersion : 1,
                bWifiUserFalg   : 1,        /* ��?��??aWIFI��??�� */
                ucSqosFlag      : 1,
                ucSessUpdFlag   : 1,
                ucNotifyDataTrc : 1,
                ucDataTrc       : 2,
                ucBackupAddTokenTbl  : 1;     /* ��?��Y?��1?,����????��??�쨦??????�¨�y��?��?��??-?����?Token������? */
    UCHAR       ucBackupBatchFlag    : 1,     /* ��?��Y?��1?,����????��??�쨺?��??����?����3��VOS_FALSE,VOS_TRUE */
                bPfcFlag        : 1,          /* ��?��???DDD-��������?1?? */
                bAcfcFlag       : 1,          /* ��?��???DD��??������?1?? */
                bVjFlag         : 1,          /* ��?��???DDVJ?1?? */
                bMppcFlag       : 1,          /* ��?��???DDMPPC?1?? */
                bLzs0Flag       : 1,          /* ��?��???DDLZS0?1?? */
                bLzs1Flag       : 1,          /* ��?��???DDLZS1?1?? */
                bBsidFlag       : 1;          /* ��?��?D-D����?bsid,VOS_TRUED����?��?VOS_FLASE?��D����? */
    UCHAR       ucMsisdnFlag    : 1,
                ucVjStatiscFlg  : 1,
                bNotifyCompFlg  : 1,
                bSignalEmsFlg   : 1,          /* ��?��?��?����1ySignal ems, ����?1???�䨦?���� */
                bSaEmsFlag     : 1,          /* sa EMS?����������?? */
                bDropEmsFlag    : 1,          /* DATA DROP EMS?����������?? */
                ucRev           : 2;

    ULONG       ulBackupPreRpIndex;     /*��?��Y?��1?*/
    ULONG       ulBackupNextRpIndex;    /*��?��Y?��1?*/
    ULONG       ulBackupLifetimeExpire; /*��?��Y?��1?,?����?��?��?��??�¡�?��?lifetime?������?�¡�?��Y��y?Yo����?��?��?????��?3?��?  */
    ULONG       ulBackupSesstimeExpire; /*��?��Y?��1?,?����?��?��?��??�¡�?��?session timeout?������?�¡�?��Y��y?Yo����?��?��?????��?3?��?  */



}SDB_PDSN_RP_CONTEXT_S;

typedef struct tagDiamAuthEpsQosInfo
{
    UCHAR ucQCI;
    UCHAR ucArp;
    UCHAR aucRsv[2];
}DIAM_AUTH_EPSQOS_INFO_S;

/* ?����?APN INFO */
typedef struct tagDiamAuthApnInfo
{
    ULONG ulContextId;                 /* APN ID */
    ULONG ulMIPAgentAddr;
    ULONG ulServedPartyIPV4;
    ULONG ulULMaxBw;                                                    /* ��?DD��?�䨮???����??�� */
    ULONG ulDLMaxBw;                                                    /* ??DD��?�䨮???����??�� */
    USHORT usApnIndex;                 /* APN Index */
    USHORT us3GPPCC;                    /* ??��?��?D? */
    DIAM_AUTH_EPSQOS_INFO_S stQosInfo;
    in6_addr stMIPAgentAddress;        /* MIP AGENT ADDRESS */
    in6_addr stServedPartyIPV6;        /* served party ip address */
    UCHAR aucVNID[DIAM_AUTH_MAX_APN_VNID + 1];
    UCHAR aucMIPAgentHost[DIAM_AUTH_MAX_APN_DEST_HOST + 1];   /* destioation host */
    UCHAR aucApnOIReplace[DIAM_AUTH_MAX_APN_OI_REPLACEMENT + 1];

    #if (UGW_BYTE_ORDER == UGW_BIG_ENDIAN)
    UCHAR ucChangeFlag:1;              /* ??��������?��??????����������1��? */
    UCHAR ucDefualtApnFlag:1;          /* ����??��?apn��?��??adefaultapn */
    UCHAR ucMIPAddrType:3;
    UCHAR ucPdnAddrType:3;             /* PDN ADDRESS TYPE DIAM??���騨??��??DIAM_AUTH_PDN_TYPE, GW?��2?��?����?��??��??PPPC_IP_INFOR_FLAG_E*/
    #else
    UCHAR ucPdnAddrType:3;              /* ??��������?��??????����������1��? */
    UCHAR ucMIPAddrType:3;          /* ����??��?apn��?��??adefaultapn */
    UCHAR ucDefualtApnFlag:1;
    UCHAR ucChangeFlag:1;
    #endif

    #if (UGW_BYTE_ORDER == UGW_BIG_ENDIAN)
    UCHAR ucPGWAllocationType :2;              /* PDN-GW-Allocation-Type 0:static 1:dynamic */
    UCHAR ucVPLMNDynamicAddressAllowed :2;     /* VPLMN-Dynamic-Address-Allowed 0:notallow 1:allow*/
    UCHAR ucRev : 4;
    #else
    UCHAR ucRev : 4;
    UCHAR ucVPLMNDynamicAddressAllowed :2;     /* VPLMN-Dynamic-Address-Allowed 0:notallow 1:allow*/
    UCHAR ucPGWAllocationType :2;              /* PDN-GW-Allocation-Type 0:static 1:dynamic */
    #endif

    #if (UGW_BYTE_ORDER == UGW_BIG_ENDIAN)
    UCHAR ucDLMaxBwFlag : 1;
    UCHAR ucULMaxBwFlag : 1;
    UCHAR ucRev6 : 6;
    #else
    UCHAR ucRev6 : 6;
    UCHAR ucULMaxBwFlag : 1;
    UCHAR ucDLMaxBwFlag : 1;
    #endif

    VOS_UINT8   aucReserved[1];
}DIAM_AUTH_APN_INFO_S;

/* 2a��????��?�¨�y  */
typedef struct MeaObjIndex
{
    ULONG  ulRpIndex;   /* ?TD�쨺����?0 */
    USHORT usPcfIndex;  /* ?TD�쨺����?0xffff */
    USHORT usReserved;  /* ��?������?o����??1, ?TD�쨺����?0 */
}MEAOBJINDEX_STRU;


typedef struct tagPPP_CFG_INFO_REC_S
{
    UCHAR          ucAuthmod;                                            /* ??������?��? */
    UCHAR          aucHostname[PPP_MAX_DNS_HOSTNAME_LENGTH+1];          /* ?��?��?? */
    USHORT         usMru;                                                /* Maximum-receive-unit */
    UCHAR          ucTimeout;                                            /* D-����???��3?��������?? */
    UCHAR          ucAuthoption;                                            /* ??������?��?����?��*/    /* Added by LHT04029 at 2006-06-15 R2C02B025 for BYHD10294 */
    UCHAR     ucIpv6Flag;                                  /* ipv61|?����1?������??:0,?��3?ipv61|?����?1 2??��3?ipv61|?�� */
    UCHAR     ucVSNCPFlag;
} VOS_PACKED PPP_CFG_INFO_REC_S;

/* AM����?��??CM��?PPP??D-����?��11?����? */
typedef struct
{
    ULONG   ulPdnIndex;    /* ��??????�¨�y */
    A11_ACCT_TERM_CAUSE_E  enReasonCode;  /* ?-����?�� */
}AM_CM_PPP_RENEGO_MSG_S;


 typedef struct
{
    ULONG ulRpIndex;
    ULONG ulMagicNum;                /* Magic-Number */
    ULONG ulAccm;
    ULONG ulPppFlag;
    USHORT usMtu;
    UCHAR ucPPPMode;
    UCHAR ucPPPConFlag;
    UCHAR ucDmpuId;
    UCHAR ucDmpuDpeId;
    UCHAR ucPcfReleaseFlag;
    UCHAR ucmaxslotindex;

}A11_PPPC_USR_INFOR_S;      /* PPPC���騪��A11��?��??��D??��?��11 */


#define  L2TP_MSISDN_LEN 8
#define  L2TP_IMSI_LEN 8
#define  L2TP_IMEI_LEN 8
typedef UCHAR L2TP_MSISDN[L2TP_MSISDN_LEN];
typedef UCHAR L2TP_IMSI[L2TP_IMSI_LEN];
typedef UCHAR L2TP_IMEI[L2TP_IMEI_LEN];

/*l2tp ����?appp l2tp up��?��y?Y?��11*/
typedef struct tagL2TP_NOTIFY_PPPC_UP_INFO
{
    ULONG   ulTeidc;               /*pdp��?????������?*/
    ULONG   ulPdpindex;            /*pdp��??????�¨�y*/
    ULONG   ulGtpuIndex;           /*??����??��a����??��?gtpuindex,??��?o��*/
    ULONG   ulFilterTableIndex;    /*��y?Y??1y??��??t���������??�¨�yn��???��?o��*/
    ULONG   ulSendACCM;            /*ACCM applied to send message */
    ULONG   ulRecvACCM;            /*ACCM applied to receive message*/
    ULONG   ulIFIndex;             /*����?��?��?�¨�y*/
    ULONG   ulLocalIP;
    ULONG   ulPeerIP;             /*lns ip */
    USHORT  usReqApnIdx;
    USHORT  usApnIndex;
    USHORT  usTraceId;             /*��?��??������*/
    USHORT  usLocalTunnelId;       /* local_tunnel_id */
    USHORT  usLocalSessionId;      /* local_session_id */
    USHORT  usPeerTunnelId;        /* Peer_tunnel_id  */
    USHORT  usPeerSessionId;       /* Peer_session_id */
    USHORT  usReserved;
    UCHAR   ucCompInstIdx;          /*OS ?��PPP����?t���̨�yo?*/
    UCHAR   ucDpeId;
    UCHAR   ucPgwIsTraceFlag;      /*��?��??������*/
    UCHAR   ucPgwListOfInterfaces; /*��?��??������*/
    UCHAR   ucRandomNo;
    UCHAR   ucUgwRole;          /*?����???UGW_NET_ELEMENT_ROLE_E*/
    UCHAR   ucLcpRe;
    UCHAR   ucAliaApnFlg;
    L2TP_IMSI   szImsi;
    L2TP_MSISDN szMsisdn;
}L2TP_NOTIFY_PPPC_UP_INFO;

/*L2TP����?aPPPC?��?��L2TP DOWN��|������??��?��?��11*/
typedef struct tagL2TP_NOTIFY_PPPC_DOWN_INFO
{
    ULONG   ulTeidc;
    ULONG   ulPdpindex;            /*pdp��??????�¨�y*/
    USHORT  usFailReason;      /*GTP ERROR REQUIREMENT*/
    USHORT  usReserved;
} L2TP_NOTIFY_PPPC_DOWN_INFO;

typedef struct
{
    ULONG      ulTeidc;                     /*��??�������?*/
    ULONG      ulPdpIndex;                  /*��??�������?*/
    ULONG      ulGtpuIndex;                 /*??����??��a����??��?gtpuindex��???��?o��*/
    ULONG      ulFilterTableIndex;          /*��y?Y??1y??��??t���������??�¨�yn��???��?o��*/
    USHORT     usTraceId;
    USHORT     usApnIndex;
    USHORT     usReqApnIdx;
    UCHAR      ucAliaApnFlg;
    UCHAR      ucCompInstIdx;               /*ppp����?t?��OS?����?���̨�yo?*/
    UCHAR      ucDpeId;
    UCHAR      ucPgwIsTraceFlag;
    UCHAR      ucPgwListOfInterfaces;
    UCHAR      ucRandomNo;               /* ???��???��?������o? */
    UCHAR      ucUgwRole;                /*?����???UGW_NET_ELEMENT_ROLE_E*/
    UCHAR      ucLcpRe;
    UCHAR      ucRev[2];
    L2TP_IMSI   szImsi;
    L2TP_IMEI   szImei;
    L2TP_MSISDN szMsisdn;
}L2TP_USERINFO_S;

typedef struct
{
    ULONG  ulVpnId;
    ULONG  ulGiifIndex;
    USHORT usGroupNum;                          /* VPDN������?����o?,��?��??????��??��DD�� */
    UCHAR  ucTunnelClientAuthId[L2TP_TUNNEL_NAME_LEN + 1];   /* LAC?? */
    UCHAR  ucTunnelServerAuthId[L2TP_TUNNEL_NAME_LEN + 1];   /* LNS?? */
    UCHAR  ucTunnelAssignId[L2TP_TUNNEL_ASSIGNEDID_LEN + 1];     /* ?���̨�ID */
    UCHAR  bType : 1,                              /* 0: ��?��????? 1: Radius????, Group num from 1000 to 1999*/
           bFailReason : 7;

    struct
    {
        ULONG ulLnsIpAddr;
        ULONG ulTunnelPreference;
        UCHAR ucTunnelPasswd[L2TP_TUNNEL_PASS_LEN + 1];
        UCHAR ucRev[3];
    }stLnsInfo[L2TP_MAX_LNS_IP_ADDRESS];
}L2TP_LNSPARA_S;

typedef struct
{
    VOS_UINT32 bLcpOptionUsed      : 1,                 /*L2TP��?��?��?��Y?��D-����D??��*/
               bProxyAuthenUsed    : 1,                 /*L2TP��?��?��1��?�䨲����?��?��*/
               bBearTypeUsed       : 1,                 /*��?��?D����?BearType��???*/
               bPrivateGroupIdUsed : 1,                 /*��?��?D����?PrivateGroupId��???*/
               bNoDialingNumber    : 1,                 /* ��?��?D����?DialingNumber */
               bAliaApnFlg         : 1,                 /* D��?aAPN����?? */
               bReserv             : 26;
    VOS_UINT32 ulInitialRcvLen;                         /*��?3??����?��?LCP confreq3��?��*/
    VOS_INT8  szInitialRcv[L2TP_MAX_PPP_OPTION_LEN];    /*��?3??����?��?LCP confreq*/
    VOS_UINT32 ulLastSentLen;                           /*��?o�������?LCP confreq3��?��*/
    VOS_INT8  szLastSent[L2TP_MAX_PPP_OPTION_LEN];      /*��?o�������?LCP confreq*/
    VOS_UINT32 ulLastRcvLen;                            /*��?o��?����?��?LCP confreq 3��?��*/
    VOS_INT8  szLastRcv[L2TP_MAX_PPP_OPTION_LEN];       /*��?o��?����?��?LCP confreq*/
    VOS_UINT32 ulChallengeLen;                          /*�䨲����?��?���??��?��3��?��*/
    VOS_INT8  szChallenge[L2TP_CHALLENGE_LEN+2];        /*�䨲����?��?���?CHAP?��?��*/
    VOS_UINT32 ulResponseLen;                           /*�䨲����?��?���?CHAP??��|3��?��*/
    VOS_INT8  szResponse[L2TP_RESPONSE_LEN+4];            /*�䨲����?��?���?CHAP??��|*/
    VOS_INT8  szAuthenName[L2TP_USER_NAME_LEN + 2];     /*�䨲����?��?���?��??��??*/
    VOS_UINT16 usAuthenID;                              /*LAC??PPPo����??��??DD?��?���?������?ID*/
    VOS_UINT16 usAuthenType;                            /*�䨲����?��?�訤��D��*/
    VOS_UINT16 usApnIndex;                              /* APN */
    VOS_UINT16 usReqApnIdx;                             /* ?��??APN */

    VOS_UINT32 ulAccm;

    VOS_UINT32 ulBearType;                              /* 3D???����|��?L2TP_CALLBEARETYPE_E */
    VOS_UINT32 ulFramType;                              /* L2TP_FRAMINGTYPE_E */
    VOS_UINT32 lPrivateGroupID;

    VOS_INT32 lRxConnectSpd;                            /* LAC��?��y?Y?����??��?��*/
    VOS_INT32 lTxConnectSpd;                            /* LAC��?��y?Y����?��?��?��*/
    VOS_INT8 szSubAddress[L2TP_SUBADDRESS_LEN];         /*������??����?��?��?��?������?*/
    VOS_INT8 szDialedNumber[L2TP_DIALEDNUM_LEN];        /*��??Do???��?*/
    VOS_INT8 szDialingNumber[L2TP_DIALINGNUM_LEN];      /*?��?Do???��?*/
}L2TP_SESSIONPARA_S;

/* PPP����?aL2TP UP��????��?��11 */
typedef  struct tagL2TP_PPPPara
{
    L2TP_LNSPARA_S      stLnsInfo;          /* LNS?��1?��?2?��y */
    L2TP_SESSIONPARA_S  stSessionInfo;      /* ��??��L2TP?��?��?��1?2?��y */
    L2TP_USERINFO_S     stUserInfo;         /* ��??��???��2?��y,L2TP����?t2?1?���� */
}L2TP_PPPPARA_S;

/*���ָ����������͵�ȫ��ö�ٱ����ṹ��Ķ���,�������ʹ�0x02��ʼ*/
typedef enum tagEN_TRACE_TYPE
{
    TRC_TYPE_RPCSN = 0x22,
    TRC_TYPE_BUTT
}E_TRACE_TYPE;

extern S_CFG_DOMAINNODE g_pstApnByIndex[];

typedef struct
{
    ULONG ulFsmId;          /* ���䨬??�����̨�yo?*/
    ULONG ulCurState;       /* �̡�?����䨬?*/
    ULONG ulEvent;          /* ��?��?��??t */
    ULONG ulRelCode;

    SDB_PDSN_RP_CONTEXT_S *pstRpContext;
    UCHAR *pucMsg;

}USM_FSM_PRE_RESULT_S;


#endif

#ifdef __cplusplus
}
#endif
