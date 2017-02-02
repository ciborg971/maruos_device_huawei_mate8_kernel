
#ifndef _DHCPC_DEF_H_
#define _DHCPC_DEF_H_

#ifndef AF_INET
#define AF_INET    2               /* internetwork: UDP, TCP, etc. */
#endif

/* add by w00316385 start */
#ifdef __WIN32_PLATFORM__
#include "stdio.h"
#endif

#include "v_typdef.h"
#include "TtfDrvInterface.h"
#include "PsTypeDef.h"

#ifndef VOS_PACKED
#ifdef __WIN32_PLATFORM__
#define     VOS_PACKED
#else
#define     VOS_PACKED      __attribute__ ((__packed__))
#endif
#endif

#define VOS_ASSERT( exp )          ( (exp) ? (VOS_VOID)0 : vos_assert( __FILE__, __LINE__ ) )

#define VOS_Assert(lExpression)                                     \
    ( (lExpression)?(VOS_VOID)0:vos_assert( __FILE__, __LINE__ ) )  \

#ifndef VOS_DBGASSERT
#define VOS_DBGASSERT(lExpression)                                  \
    ( (lExpression)?(VOS_VOID)0:vos_assert( __FILE__, __LINE__ ) )  \

#endif

#ifndef VOS_Free
#define VOS_Free(p)                                 { free((p));(p) = NULL; }
#endif

#ifndef VOS_Mem_Zero
#define VOS_Mem_Zero(pBuffPtr, ulLen)               (void)memset((pBuffPtr), (0), (ulLen))
#endif

// handle��D/E/F�϶���32λ��
#define PGP_MemAlloc(handle, size)  VOS_MemAlloc(handle, DYNAMIC_MEM_PT, size)
#define PGP_MemReMalloc(handle, pOldMemPtr, uvNewSize) VOS_MemAlloc(0, 0, 0)
#define PGP_MemFree(handle, ptr) VOS_MemFree(handle, ptr)
#define PGP_MemZero(ptr, size) VOS_Mem_Zero(ptr, size)

#define MSPS_PID_DHCP UEPS_PID_DHCP
#define MID_DHCPM     MSPS_PID_DHCP
#define MID_DHCPC     MSPS_PID_DHCP
#define MID_DHCPS     MSPS_PID_DHCP
#define MID_DHCPSV6   MSPS_PID_DHCP
#define FSU_TID_DHCP  MSPS_PID_DHCP


#ifndef _lint
typedef unsigned long   ULONG;
typedef unsigned char   UCHAR;
typedef unsigned short  USHORT;
#endif
typedef signed long     LONG;
typedef signed short    SHORT;

#ifdef _lint
typedef signed char     CHAR;
#endif

typedef unsigned long long ULONG64;
typedef signed long long   LONG64;
#ifndef _lint
typedef unsigned long long UINT64;
#endif
typedef unsigned int    SEC_UINT32;


//typedef VOS_SIZE_T      SIZE_T;
typedef signed int      CDB_RECID;
typedef unsigned short  DMS_IID_T;
typedef unsigned int    DMS_COMMID_T;


typedef void            PF_VOID;
typedef long            PF_LONG;
typedef unsigned long   PF_ULONG;
typedef unsigned char   PF_UCHAR;
typedef short           PF_SHORT;
typedef unsigned short  PF_USHORT;
typedef signed char     PF_CHAR;
typedef unsigned long long PF_DULONG;
typedef int                         SM_LONG;
typedef unsigned int                SM_ULONG;
typedef unsigned char               SM_UCHAR;
typedef SM_ULONG                    SM_BOOL;
typedef void                        SM_VOID;
typedef unsigned long long DULONG;

typedef signed int  CDB_DBID;
typedef signed int  CDB_TBLID;


#define VOS_NTOHS(x)  ((((x)& 0xFF00)>>8) |  (((x) & 0x00FF)<<8))
#define VOS_NTOHL(x) ((((x)&0xff)<<24)|(((x)&0xff00)<<8)|(((x)&0xff0000)>>8)|(((x)&0xff000000)>>24))
#define VOS_HTONS(x)                   ((((x) & 0x00ff) << 8) | \
                                        (((x) & 0xff00) >> 8))
#define VOS_HTONL(x)                   ((((x) & 0x000000ff) << 24) | \
                                        (((x) & 0x0000ff00) <<  8) | \
                                        (((x) & 0x00ff0000) >>  8) | \
                                        (((x) & 0xff000000) >> 24))

/** CRM�������سɹ� */
#ifndef CRM_OK
#define CRM_OK    0
#endif

/** CRM�������ش��� */
#ifndef CRM_ERROR
#define CRM_ERROR 1
#endif

/** CRM������� */
#ifndef CRM_YES
#define CRM_YES   1
#endif

/** CRM��������� */
#ifndef CRM_NO
#define CRM_NO    0
#endif

#ifndef MC_RWLOCK_ID
#define  MC_RWLOCK_ID    VOS_VOID*
#endif

#define LAP_DHCP_SERVER_INVALID_IP                   0

#if(VRP_MAIN_BOARD == VRP_YES)

/******************************************************************************
    �������ͣ�CDB_TABLE_INIT_FUN
    ���������ʼ�������࣬��C��ʵ��Ϊһ��������ԭ��Ϊ
    VOS_VOID (* CDB_TABLE_INIT_FUN)(TBLID nTbl)

******************************************************************************/

typedef VOS_VOID (* CDB_TABLE_INIT_FUN)(CDB_DBID DBID, CDB_TBLID nTbl);

typedef VOS_VOID (* CDB_CALLBACK_FUN)(CDB_DBID nDBId, CDB_TBLID nTbl, ...);

#else

/******************************************************************************
    �������ͣ�CDB_TABLE_INIT_FUN
    ���������ʼ�������࣬��C��ʵ��Ϊһ��������ԭ��Ϊ
    VOS_VOID (* CDB_TABLE_INIT_FUN)(TBLID nTbl)

******************************************************************************/

typedef VOS_VOID (* CDB_TABLE_INIT_FUN)(CDB_TBLID nTbl);

typedef VOS_VOID (* CDB_CALLBACK_FUN)(CDB_TBLID nTbl, ...);

#endif

typedef enum
{
    PTM_DBG_PRINT_MODULE_PATH,
    PTM_DBG_PRINT_MODULE_MBMS,
    PTM_DBG_PRINT_MODULE_DHCPM,
    PTM_DBG_PRINT_MODULE_PTM_COMM,
    PTM_DBG_PRINT_MODULE_PTM_HASH,
    PTM_DBG_PRINT_MODULE_UGW_BLACK_BOX,
    PTM_DBG_PRINT_MODULE_HSGW_SDU,
    PTM_DBG_PRINT_MODULE_HSGW_FA,
    PTM_DBG_PRINT_MODULE_HSGW_SD,
    PTM_DBG_PRINT_MODULE_HSGW_CMP,
    PTM_DBG_PRINT_MODULE_COMM_FSM,
    PTM_DBG_PRINT_MODULE_A11,
    PTM_DBG_PRINT_MODULE_S6B,
    PTM_DBG_PRINT_MODULE_NW,
    PTM_DBG_PRINT_MODULE_MSE_SC,
    PTM_DBG_PRINT_MODULE_MSD_SDU,
    PTM_DBG_PRINT_MODULE_VAS_SDU,
    PTM_DBG_PRINT_MODULE_BULT,
}PTM_DBG_PRINT_MODULE_E;

/** ��ȡ��SPU��Ĳ�λ�� */
#define DVM_SELF_SLOTID (DVM_GetSelfLogicSlotID())

/** ��ȡ��CpuID */
#define DVM_SELF_CPUID (DVM_GetSelfCpuId())

/* �������ͺ궨�� */
#define M_GGSN_CARD_GSPU  2

#define M_CDB_TABLE_FUN_TYPE_TBL_INIT (0)
#define M_CDB_TABLE_FUN_TYPE_REC_APP  (1)
#define M_CDB_TABLE_FUN_TYPE_REC_DEL  (2)
#define M_CDB_TABLE_FUN_TYPE_REC_MOD  (3)
#define M_CDB_TABLE_FUN_TYPE_TBL_MOD  (4)
#define M_CDB_TABLE_FUN_TYPE_REC_NULL (0xFF)

#define M_PTM_SYSTEM_NAME "PTM"

#define M_PTM_MODULE_DHCPM  "DHCPM"

/* BEGIN: Added by jixiaoming at 2011-09-27 for  CR20101222007 */
#define M_ALM_PATHDHCPSERVERDOWN  840
/* END: Added by jixiaoming at 2011-09-27 for  CR20101222007 */

#ifndef M_ALM_TYPE_RESTORE
 #define M_ALM_TYPE_RESTORE 0                               /* �ָ��澯 */
 #define M_ALM_TYPE_FAULT 1                                 /* ���ϸ澯 */
 #define M_ALM_TYPE_EVENT 2                                 /* �¼��澯 */
 #define M_ALM_TYPE_SECURITY 4                              /*��ȫ�澯*/
#endif

//Cyjun: ȷ���Ƿ�ֶ�: M_SPM_DPR_ALM��ֵҵ������Բ��ã���ƽ̨�ֶ�������Щ��
/*DWORD���ͺ궨��*/
typedef enum enU_SOFTPARA_DWORD_VALUE
{
    M_SPM_DPR_ALM = 1,/*���и澯������� Added by wangbin 63984 at 2007-11-19 PGPV2R1-NE40E-1 for SRM-PDB */
    M_SPM_DPR_ALMEX = 2,/*���и澯������� Added by wangbin 63984 at 2007-11-19 PGPV2R1-NE40E-1 for SRM-PDB */

    /*begin: add by wangweihua@2008-05-22 for ѡ��DPE�����(Ĭ����ѡ�����򰴱���IP��ַ����)*/
    M_SPM_PF_FLAG = 3,
    /*end: add by wangweihua@2008-05-22 for ѡ��DPE�����(Ĭ����ѡ�����򰴱���IP��ַ����)*/

    /* Added start by y102283 at 2008-07-30 V9R7C01 Build2 for APN-loadshare */
    M_SPM_APN_TIME_THRESHOLD = 4,
    /* Added end by y102283 at 2008-07-30 V9R7C01 Build2 for APN-loadshare */
    M_SPM_UGW_AAA_TRY_INTERVAL = 5,
    M_SPM_OCS_CONNECT_PORT = 7,  //���ڿ���ocs�����˿�
    M_SPM_CHR_DEVNO = 8,
    M_SPM_CM_INVALID_VOLUME_QUOTA = 21,
    M_SPM_PF_NEW_FLAG  =  51, /*PS9.1 �������ʹ��DWORD51*/
    /* BEGIN: Added by xuyaoqiang, 2012/2/14   ���ⵥ��:PS9.2 VF DCCA V2.1 */
    M_SPM_CM_OCSC_QUOTA_ZERO_NPT  =  61,
    /* END:   Added by xuyaoqiang, 2012/2/14 */
    M_SPM_PF_IPSQM_CBS  =  62,
    M_SPM_PTM_DHCP_SERVER_INTERVAL = 71,
    M_SPM_IPN_TCP_MSS_DEFAULT_VALUE = 72,
    /*Add by xsm00201057 20130304 for PDSNC06�����ֲ*/
    M_SPM_PF_PDSN_FLAG = 76,
    /*End by xsm00201057 20130304 for PDSNC06�����ֲ*/
    M_SPM_PDSN_AAA_TRY_INTERVAL = 78,
    /*Add by xsm00201057 20130520 for PDSN����costos���ܿ�������޸�*/
    M_SPM_PF_PDSN_NEW_FLAG = 84,

    M_SPM_DEF_DWORD_END
}U_SOFTPARA_DWORD_VALUE;

/* CDB�ӿں��������� */
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

/* IPC������Ϣ�ɹ�/ʧ�ܻ���յ���Ϣʱ��֪ͨ��ʽ */
#define     IPC_NOTI_VIA_NONE   0x00000000
#define     IPC_NOTI_VIA_QUEUE  0x00000001      /* ͨ����Ϣ֪ͨ           */
#define     IPC_NOTI_VIA_FUNC   0x00000002      /* ͨ���ص�����֪ͨ       */

typedef VOID (*IPC_RTNOTIFY_FUNC)
(
    VOS_UINT32 uiFlag,
    VOS_UINT64 ul64DstCsi,
    VOS_VOID * pData,
    VOS_UINT32 uiLen
);

/*----------------------------------------------*
 * �궨��                                       *
 *----------------------------------------------*/
#define VOS_QUEUE_NO_WAIT             ((VOS_UINT32)1 << 5)


typedef enum enumPTM_LOG_LVL_E
{
    PTM_LOG_INFO,   /* ���¼��־������Ϊ��ʾ��Ҳ��ӡ���� */
    PTM_LOG_WARNING,/* ���¼��־������Ϊ�澯��Ҳ��ӡ���� */
    PTM_LOG_ERR,    /* ���¼��־������Ϊ����Ҳ��ӡ���� */
    PTM_LOG_DEBUG,  /* ����¼��־��ֻ��ӡ���� */
    PTM_LOG_BUTT
}PTM_LOG_LVL_E;


#ifdef __WIN32_PLATFORM__
#define PTM_DebugPrint PTM_DebugOut_ForPtmDebugOut
#else
#define PTM_DebugPrint(moduletype, level, fmt...) DHCPC_DebugPrint(level, ##fmt)
#endif


#define M_PMIP_BSID_LEN 12
#define M_TWANID_SSID_LEN 32
#define M_TWANID_BSSID_LEN 6
#define M_TWANID_SSID_LEN_INCONTEXT 19

/*ip��ַ��ulong��Ŀ*/
#define LAP_IP_ULONG_NUM     4
#define LAP_ULONG_BIT_NUM   32

/*MSISDN���õ�ULONG��*/
#define LAP_MSISDN_ULONG_NUM        2

//
//msisdn define
//
#define GTP_MAX_MSISDN_LEN             8
typedef UCHAR GTP_MSISDN[GTP_MAX_MSISDN_LEN];

/*LAP2��DHCPģ��佻������Ϣ*/
typedef struct tagLAP2_DHCP_MSG
{
    UCHAR ucMsgType;         /*��Ϣ���ͣ�������ԭ��ֵ*/
    UCHAR ucSCID:4;            /*SC ID*/
    UCHAR ucAddressType:4;       /*��ַ����*/
    UCHAR ucUserType;          /*0  GTPC    1 PPP
                               LAP2_USER_TYPE_GTP 0
                               LAP2_USER_TYPE_PPP 1 */
    UCHAR ucGtpVer;         /*�û�����:V0:0;V1:1;V2:2*/
    ULONG aulPdpAddr[LAP_IP_ULONG_NUM];       /*IP��ַ*/
    ULONG aulMSISDN[LAP_MSISDN_ULONG_NUM];        /*MSISDN*/
    ULONG ulIndex;             /*����������*/
    ULONG aulAgentIP[LAP_IP_ULONG_NUM];           /*Agent IP*/
    ULONG aulPrimaryDNS[LAP_IP_ULONG_NUM];
    ULONG aulSecondaryDNS[LAP_IP_ULONG_NUM];
    ULONG ulTeidc;            /*TEIDC*/
    USHORT usVpnId;           /*VPN ID*/
    USHORT usPoolIndex;        /*��ַ������*/
    USHORT usDhcpGroupIndex;   /*DHCP������������*/
    USHORT usApnIndex;         /*APN����*/
    UCHAR ucStaticIpRouteType;  // TODO:jxmûʲô��
    UCHAR ucLAPNo;
    UCHAR ucSectionNum;
#if 0
    UCHAR ucReserve;           /*�����ֶ�*/
#endif
    UCHAR ucRabId;             /*RabId*/
    USHORT enModemId;          /*enModemId*/
}LAP2_DHCPC_MSG_S;

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
     UCHAR SPARE : 4;        /* ��1��� */
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
     UCHAR SPARE : 4;        /* ��1��� */
     UCHAR MSIN10: 4;
#endif
} GTP_IMSI_S;

#ifndef LAP_IPV4
#define LAP_IPV4 0
#endif
#ifndef LAP_IPV6
#define LAP_IPV6 1
#endif

//
//ipv6 define
//
#define   M_SDB_IPV4_LENGTH                 4
#define   M_SDB_IPV6_LENGTH                 16

/* IP ��ַ����*/
typedef VOS_UINT8 DHCPC_IPV4[M_SDB_IPV4_LENGTH];
typedef VOS_UINT8 DHCPC_IPV6[M_SDB_IPV6_LENGTH];

/* IPv6 ��ַ���ݽṹ */
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

#define M_AM_USM_INVALID_IP_ADDR        0xffffffff
#define M_AM_USM_ADDRTYPE_IPV4        0
#define M_AM_USM_ADDRTYPE_IPV6        1


/***** Type Definitions *****/
typedef struct DLL_NODE{
    struct DLL_NODE *pNext; /* Points at the next node in the list */
    struct DLL_NODE *pPrev; /* Points at the previous node in the list */
    ULONG ulHandle;	        /* 2000/4/21, ������ȫΪ�û����ã�VOS����������û����ô���洢���� */
}DLL_NODE_S;

typedef struct DLL{
    DLL_NODE_S Head;        /**** Header List Node        ****/
    ULONG      u4_Count;    /**** Number Of Nodes In List ****/
}DLL_S;

#define GNDEBUGTRACE_MAX_LENGTH_REASON 256
#define GNDEBUGTRACE_MAX_LENGTH_SUGGESTION 258

#define M_MNT_MAX_PDP_NUM 11

#define     V_MSGTYPE_DHCPV4    0x01
#define     V_MSGTYPE_DHCPV6    0x02
#define     V_MSGTYPE_ALL        0x03

#define     V_ADDRTYPE_DHCPV4    0x01 /* 1 :DHCP-V�ӿڸ���, ��ʾ�Զ�IP����ΪIPV4 */
#define     V_ADDRTYPE_DHCPV6    0x02 /* 2 :DHCP-V�ӿڸ���, ��ʾ�Զ�IP����ΪIPV6 */

/** SPU Group����״̬�仯���Ͷ��� */
typedef enum tagCRM_BRDSTATE_CHG_ENUM
{
    CRM_BRDSTATE_CHG_BEGIN,          /**< BEGIN */
    CRM_BRDSTATE_CHG_SPUREG = 1,     /**< 1,����ע�� */
    CRM_BRDSTATE_CHG_SPURESET,       /**< 2,���帴λ */
    CRM_BRDSTATE_CHG_SPUPULLOUT,     /**< 3,���屻�γ� */
    CRM_BRDSTATE_CHG_CPUREG,         /**< 4,CPUע�� */
    CRM_BRDSTATE_CHG_CPURESET,       /**< 5,CPU��λ */
    CRM_BRDSTATE_CHG_CPUPULLOUT,     /**< 6,CPU���γ� */
    CRM_BRDSTATE_CHG_PGPREADY,       /**< 7,PGP READY */
    CRM_BRDSTATE_CHG_SERVICEREADY,   /**< 8,Service READY */
    CRM_BRDSTATE_CHG_CPUPGPREADY,    /**< 9,CPU PGP READY */
    CRM_BRDSTATE_CHG_CPUSERVICEREADY,/**< 10,CPU Service READY */
    CRM_BRDSTATE_CHG_SWITCHOFF,      /**< 11,����CPU������Ϣ */
    CRM_BRDSTATE_CHG_ZOMBIE,         /**< 12,����Zombie */
    CRM_BRDSTATE_CHG_STANDBY_TO_ACTIVE,    /**< 13,�����ɱ�����Ϊ���� */
    CRM_BRDSTATE_CHG_ACTIVE_TO_STANDBY,    /**< 14,���������彵Ϊ���� */
    CRM_BRDSTATE_CHG_ACTIVE_TO_ACTIVE,     /**< 15,����ע��ʱ״̬Ϊ���� */
    CRM_BRDSTATE_CHG_STANDBY_TO_STANDBY,   /**< 16,����ע��ʱ״̬Ϊ���� */
    /* Added start by jiangyongliang 50758 at 2012-08-14 PGPV2R6 for CRM-READY */
    CRM_BRDSTATE_CHG_SGREG,          /**< 17,SGע�� */
    CRM_BRDSTATE_CHG_SGRESET,        /**< 18,SG��λ */
    CRM_BRDSTATE_CHG_SGPGPREADY,     /**< 19,SG PGP READY */
    CRM_BRDSTATE_CHG_SGSERVICEREADY, /**< 20,SG Service READY */
    /* Added end by jiangyongliang 50758 at 2012-08-14 PGPV2R6 for CRM-READY */
    CRM_BRDSTATE_CHG_TYPE_MAX        /**< ��Ч����״̬�仯���� */
} CRM_SPUSTATE_CHG_ENUM;

//Cyjun: ��Ʒ���UFPԭ��ʹ��SHR_MEM_TYPE_E
//���ú�ת����SERVICE_MEM_TYPE_E��ά���ɱ��ߣ��ң�ͳһΪSERVICE_MEM_TYPE_E
/*ҵ���ڴ�����ö��ֵ*/
typedef enum enSERV_MEM_TYPE_E
{
    SERVICE_MEM_TYPE_SHARE_GLOBAL = 0,
    SERVICE_MEM_TYPE_SHARE_ROUTE,
    SERVICE_MEM_TYPE_SHARE_CONTROL_PLANE,
    SERVICE_MEM_TYPE_SHARE_GM_SC,
    SERVICE_MEM_TYPE_SHARE_GM_PARSER,
    SERVICE_MEM_TYPE_SHARE_SC_DPE_PARSER,
    SERVICE_MEM_TYPE_SHARE_DPE_PARSER_RPT,
    SERVICE_MEM_TYPE_GM0_LAP2_SDU,
    SERVICE_MEM_TYPE_LOCAL,
    SERVICE_MEM_TYPE_END
}SERVICE_MEM_TYPE_E;

#ifndef M_PS_MSG_TYPE_BASE
#define M_PS_MSG_TYPE_BASE 11
#else
#if (M_PS_MSG_TYPE_BASE != 11)
#error
#endif
#endif

/* DHCPM���ܶ�����Ϣ���Ͷ��� */
typedef enum
{
    DHCPM_MSG_TYPE_TIMER = M_PS_MSG_TYPE_BASE, /* ��ʱ����Ϣ */
    DHCPM_MSG_TYPE_BULT,
}DHCPM_MSG_TYPE_E;

/* DHCPV4 Client���ܶ�����Ϣ���Ͷ��� */
typedef enum
{
    DHCPC_MSG_TYPE_FCM = M_PS_MSG_TYPE_BASE,  /* LAP��FCM��Ӧ��Ϣ,ʹ����E�� */
    DHCPC_MSG_TYPE_SERVER,       /* DHCP server��Ӧ��Ϣ */
    DHCPC_MSG_TYPE_DHCPV6_SERVER,
    DHCPC_MSG_TYPE_LAP,      /* LAP��Ӧ��Ϣ */
    DHCPC_MSG_TYPE_TIMER,    /* ��ʱ����Ϣ */
    DHCPC_MSG_TYPE_SELF,     /* ������Ϣ */

    DHCPC_MSG_TYPE_BATCH_CMD_REQ, /* ����PTM�������������������Ϣ */
    DHCPC_MSG_TYPE_BULT,
}DHCPC_MSG_TYPE_E;

/* DHCPV4 Server���ܶ�����Ϣ���Ͷ��� */
typedef enum
{
    DHCPS_MSG_TYPE_PF = M_PS_MSG_TYPE_BASE,  /* ����pf��������Ϣ, ��ӦS%luDHCPv4S���� */
    DHCPS_MSG_TYPE_USM,          /* ����USM����Ϣ ��ӦDHCPS_USM���� */
    DHCPS_MSG_TYPE_TIMER,       /* ��ʱ����Ϣ ��ӦDST���� */
    DHCPS_MSG_TYPE_SELF,        /* ������Ϣ ��ӦDHCI���� */
    DHCPS_MSG_TYPE_BULT,
}DHCPS_MSG_TYPE_E;


/* DHCPV6 Server���ܶ�����Ϣ���Ͷ��� */
typedef enum
{
    DHCPV6S_MSG_TYPE_PF = M_PS_MSG_TYPE_BASE, /* ����pf��������Ϣ ��ӦS%luDHCPv6SR���� */

    DHCPV6S_MSG_TYPE_BULT,
}DHCPV6S_MSG_TYPE_E;

/* BEGIN: Added by jixiaoming for dhcpv6c at 2012-8-21 */
typedef enum tagEMS_CODE_PTM_DHCPC_E
{
    EMS_CODE_DHCPV6C_LEASE_EXPIRE = 1,
    EMS_CODE_DHCPV6C_SERVER_NO_RSP,           /* ����������Ӧ */
    EMS_CODE_DHCPV6C_SERVER_MSG_EXCEPTION,     /* ��Ϣ�쳣 */
    EMS_CODE_DHCPV6C_SERVER_NO_AVAILABLE_ADDR,           /* �������޵�ַ */
    EMS_CODE_DHCPV6C_TID_EXHAUST,              /* Transaction Id�ľ� */
    EMS_CODE_DHCPC_BUFF
}EMS_CODE_PTM_DHCPC_E;
/* END: Added by jixiaoming for dhcpv6c at 2012-8-21 */

/*LAP2��DHCP֮�����Ϣ������Ϣ����*/
#define LAP2_SND2_DHCPC_ADDR_REQ_MSG        1   /*LAP2���͸�DHCPC�ĵ�ַ������Ϣ*/
#define LAP2_SND2_DHCPC_ADDR_CONFLICT_MSG   2   /*LAP2���͸�DHCPC�ĵ�ַ��ͻ��Ϣ*/
#define LAP2_SND2_DHCPC_ADDR_REL_MSG        3   /*LAP2���͸�DHCPC�ĵ�ַ�ͷ���Ϣ*/
#define LAP2_SND2_DHCPC_REBUILD_ADD_MSG     4   /*LAP2���͸�DHCPC���ؽ������Ϣ*/
#define LAP2_SND2_DHCPC_REBUILD_DEL_MSG     5   /*LAP2���͸�DHCPC���ؽ�ɾ����Ϣ*/
#define LAP2_SND2_DHCPC_ADDR_FORCE_REL_MSG  6   /*LAP2���͸�DHCPC�ĵ�ַǿ�ƻ�����Ϣ*/
#define LAP2_SND2_DHCPC_IPADDR_RENEW        10  /*LAP2���͸�DHCPC��������IP��ַ��Ϣ */
#define LAP2_SND2_DHCPC_ADDR_REN_MSG        12  /*��ʱ������޸�*/
#define DHCPC_SND2_LAP2_NO_RSP_MSG          13  /*DHCPC���͸�LAP2��DHCP����������Ӧ*/
#define DHCPC_SND2_LAP2_LEASE_REL           14  /*��ַ���ڵ�dhcp����ȥ����Ϣ��lap2*/
#define DHCPC_SND2_LAP2_REL_CONTEXT         15  /*dhcp �˲�ȥ��������*/
#define DHCPC_SND2_LAP2_ADDR_SUCCESS_MSG    7
#define DHCPC_SND2_LAP2_ADDR_FAILED_MSG     8
#define DHCPC_SND2_LAP2_ADDR_REL_MSG        9   /*DHCPC���͸�LAP2�ĵ�ַ�ͷ���Ϣ*/


/*���ָ����������͵�ȫ��ö�ٱ����ṹ��Ķ���,�������ʹ�0x02��ʼ*/
typedef enum tagEN_TRACE_TYPE
{
    TRC_TYPE_GNGP             = 0X00,      /* Gtpc��Gn/Gp�ӿڸ��� */
    TRC_TYPE_USER_TYPE          = 0x01,     /* �û����� */
    TRC_TYPE_DEBUG              = 0x02,     /* Gn��ά�� */
    TRC_TYPE_GI                   = 0X03,    /* Gi��AAA�Ľӿڸ��� */
    TRC_TYPE_GA                 = 0X04,     /* Ga�ӿڸ��� */
    TRC_TYPE_GMB                = 0X06,     /* Gmb�ӿڸ��� */
    TRC_TYPE_GY                 = 0X07,
    TRC_TYPE_MBMS_SESSION       = 0X08,
    TRC_TYPE_GX                 = 0x09,     /* GX�ӿڸ��� */
    TRC_TYPE_EXTERN_SGW_S4S11S12S1U    = 0X0A,     /* SGW��S4/S11/S12/S1-U�ⲿ�ӿڸ��� */
    TRC_TYPE_EXTERN_SGW_S5S8           = 0x0B,     /* SGW��S5/S8�ⲿ�ӿڸ��� */
    TRC_TYPE_EXTERN_PGW_S5S8S2AS2BGNGP    = 0x0C,     /* PGW��S5/S8/S2a/Gn/Gp�ⲿ�ӿڸ��� */
    TRC_TYPE_GIS6B              = 0x0D,     /* Gi/S6b�ӿڸ��� */
    TRC_TYPE_EXT_IPPM       = 0x0E,     /* IPPM�ⲿ�ӿڸ��� */
    TRC_TYPE_IPPM               = 0x0F,     /* IPPM�ӿڸ��� */
    TRC_TYPE_TCP                = 0x10,     /* TCP�����Ϣ���� */
    /* BEGIN: Added by yangyun00161310, 2010/11/21   for IKE_TRACE */
    TRC_TYPE_IKE                 = 0x11,                          /* IKE  ��Ϣ���� */
    /* END:   Added by yangyun00161310, 2010/11/21 for IKE_TRACE */
    TRC_TYPE_INTER_MODULE               = 0x15,
    TRC_TYPE_USER_INTER_TYPE            = 0x16,
    TRC_TYPE_GA_INTER                   = 0x14,
    TRC_TYPE_GI_INTER                   = 0x1D,
    TRC_TYPE_SGW_S4S11S12S1U    = 0X1A,     /* SGW��S4/S11/S12/S1-U�ӿڸ��� */
    TRC_TYPE_SGW_S5S8           = 0x1B,     /* SGW��S5/S8�ӿڸ��� */
    TRC_TYPE_PGW_S5S8S2AGNGP    = 0x1C,     /* PGW��S5/S8/S2a/Gn/Gp�ӿڸ��� */
    TRC_TYPE_GY_INTER                   = 0x17,
    TRC_TYPE_GX_INTER                   = 0x19,
    TRC_TYPE_V                  = 0x1E, /* DHCP�����V�ӿڸ��� */
    TRC_TYPE_GCF                    = 0x1F,
    TRC_TYPE_PDSN_USER = 0x20,
    TRC_TYPE_PI = 0x21,
    TRC_TYPE_RPCSN = 0x22,
    TRC_TYPE_STA = 0x23,
    /* BEGIN: Added by chenlibin, 2012/10/10 */
    TRC_TYPE_SCCG_SESSION           = 0x24, /*SCCG�û�����*/
    /* END:   Added by chenlibin, 2012/10/10 */
    TRC_TYPE_S6B              = 0x25,     /* Gi/S6b�ӿڸ��� */
    TRC_TYPE_EPSNUSER         = 0x26,     /*EPSN�û�����*/
    TRC_TYPE_S6B_INTER = 0x27,
    TRC_TYPE_BUTT

}E_TRACE_TYPE;



//
//imei stuct define
//
#define GTP_MAX_IMEI_LEN 8
typedef struct tagGTP_IMEI_S
{
    UCHAR     Value[GTP_MAX_IMEI_LEN];
} VOS_PACKED GTP_IMEI_S;


#define SDB_INVALID_IP_ADDR   0xffffffff         /* ��Ч��IP��ַ*/
#define SDB_INVALID_INDEX   0xFFFFFFFF
#define MAX_IDENTIFY_LEN 64
#define MAX_MACADDRESS_LEN 6
#define MAX_IPV6_LEN 8
#define MAX_3GPP_SESSION_LEN 24
#define MAX_BRAS_SESSION_LEN 36
#define MAX_MULTI_SESSION_LEN 36
#define MAX_CONGESTION_RPT_ULI_LEN 8
#define SCCG_MAX_L2_LEN 28
#define SCCG_MIN_L2_LEN  12
#define SDB_BUILD_OPER 0
#define SDB_DEL_OPER 1
#define SDB_STRING_CONSIST               0 /*�ַ�����ͬ*/


/*===================================================================================*
* packet filter���ݽṹ��Э����������                                               *
*===================================================================================*/
typedef struct tagSDB_FILTER_CONTENT_S
{
  ULONG  ulIPSecSpi;                            /* IPSec SPI */
  USHORT usSourcePortNoLowLmt;    /* Դ�˿ںű仯��Χ������ */
  USHORT usSourcePortNoHiLmt;     /* Դ�˿ںű仯��Χ������ */
  USHORT usDestPortNoLowLmt;      /* Ŀ�Ķ˿ںű仯��Χ������ */
  USHORT usDestPortNoHiLmt;       /* Ŀ�Ķ˿ںű仯��Χ������ */
  UCHAR  ucProtocolNum;                         /* protocol number for ipv4 or next header type for ipv6 */
  UCHAR  ucTos;                                 /* Type of service */
  UCHAR  ucTosMask;                             /* TOS mask */
  UCHAR  ucEvalIndex;                           /* packet filter evaluation precedence */

  in6_addr in6DestIP;                 /* Ŀ�ĵ�ַ */
  in6_addr in6SourceIP;               /* Դ��ַ */
  UCHAR    ucSourceIPMask;                        /* Դ��ַ�������볤�� */
  UCHAR    ucDestIPMask;                          /* Ŀ�ĵ�ַ�������볤��*/
  UCHAR    usIPVersionFlag  : 2;                   /*IP�İ汾��0:IPV4; 1:IPV6*/
  UCHAR    usSrcIPFlag      : 1;                    /*���ԴIP��Ч����1*/
  UCHAR    usDstIPFlag      : 1;                    /*���Ŀ��IP��Ч����1*/
  UCHAR    usIPSecSPIFlag   : 1;                    /*���IPSecSPI��Ч����1*/
  UCHAR    usSrcPortRngFlag : 1;                    /*���Դ�˿ڷ�Χ��Ч����1*/
  UCHAR    usDstPortRngFlag : 1;                    /*���Ŀ�Ķ˿ڷ�Χ��Ч����1*/
  UCHAR    usProtocolFlag   : 1;                    /*���Э������Ч����1*/
  UCHAR    usTOSFlag        : 1;                    /*���TOS��TOSMask��Ч����1 */
  UCHAR    usPriorityFlag   : 1;                    /*������ȼ���Ч����1*/
  UCHAR    usFlowLabelFlag:1;           /*���������Ч����1*/
  UCHAR usGateStatusFlag : 1;          /*���Gate�رգ�Ϊ0������Ϊ1*/
  UCHAR usUpDir          : 1;                       /*0����ʾFilter���������У�1����ʾ��������*/
  UCHAR usDownDir        : 1;                       /*0����ʾFilter���������У�1����ʾ��������*/
  UCHAR    usSmPccCrtFlg : 1;                       /*���Ϊ�˴�sm ��̬pcc��������1*/
  UCHAR    usSmPccCrtFilter : 1;                       /*���filter��sm ��̬pcc��������1*/
  UCHAR ucFlag;                    /*��Ч���*/
  UCHAR ucIsSrcPortRng :1;  /*��ʾԴ�˿�Ϊ���䷶Χ����ֻ�ж˿ں�:1��ʾ��Χ;0��ʾ�˿�*/
  UCHAR ucIsDstPortRng :1;  /*��ʾĿ�Ķ˿�Ϊ���䷶Χ����ֻ�ж˿ں�:1��ʾ��Χ;0��ʾ�˿�*/
  UCHAR ucReverd : 6;
  UCHAR ucEvalIndexUp;      /*����PCRFC�·���һ��filterͬʱ�������е������ ���ڴ洢���ж�Ӧ�����ط�������ȼ�*/
  UCHAR ucReserv;
  ULONG ulFlowLabel;                /*flow loabel type(ipv6)*/
} VOS_PACKED SDB_FILTER_CONTENT_S;
typedef struct tagSDB_FILTER_S
{
  UCHAR ucFilterId;
  /*filter�����룬Ŀǰ����Gx�ں�GGSNʹ�ã����ݴ˲������filter list���жϳ���ǰҪ������filter
    GTPC_CREATE_NEW_TFT��GTPC_DELETE_EXISTING_TFT����Ҫ��ֵ*/
  UCHAR ucFilterOpCode;
  SDB_FILTER_CONTENT_S stFilterContent;
  ULONG ulNwFilterId;
  ULONG ulNwFilterIdSecond;
  struct tagSDB_FILTER_S * pstNext;
} VOS_PACKED SDB_FILTER_S;

/*===================================================================================*
* GSPU����TFT��Ϣ�ṹ                                                               *
*===================================================================================*/
typedef struct tagSDB_TFT_S
{
  SDB_FILTER_S *pstFilter;
  UCHAR         ucFilterNum;
  UCHAR         ucReserved;
  /*modify start by wangboyu at 2011-05-27 for TFT buf */
  USHORT        usFilterOperIndic;/*��������filter��ʶ*/
  /*modify end by wangboyu at 2011-05-27 for TFT buf */
} VOS_PACKED SDB_TFT_S;

typedef struct tag3GPP_PDP_Str
{
  ULONG ulAcctSessionLen;
  UCHAR ulAcctSessionId[MAX_3GPP_SESSION_LEN];   /* acct session id */
  SDB_TFT_S* pstTft;
  struct tag3GPP_PDP_Str* pNext;
}GTP_PDP_Str;

typedef struct tagAM_IPN_MSE_PROFILE_INFO_S
{
    USHORT ausMseProfileId[8];
    UCHAR aucMseProfileIdOP[8];
    UCHAR ucMseProfileNum;
    UCHAR ucResved[7];
} AM_IPN_MSE_PROFILE_INFO_S;

/* QOS�Ķ��� */
/*
 *�������б����QoS(12 Byte) -------
 */

/* modified start by lujun 56856 at 2008-11-18 SAE1.0 */
typedef struct tagGTP_GGSN_QOS_S
{
#if UGW_BYTE_ORDER == UGW_LITTLE_ENDIAN
    UCHAR  ucReliabilityClass       : 3;
    UCHAR  ucDelayClass             : 3;
    UCHAR  ucSpare1                 : 2;
    UCHAR  ucPrecedenceClass        : 3;
    UCHAR  ucSpare2                 : 1;
    UCHAR  ucPeakThroughput         : 4;
    UCHAR  ucMeanThroughput         : 5;
    UCHAR  ucSpare3                 : 3;
    UCHAR  ucDeliveryErroSdu        : 3;
    UCHAR  ucDeliveryOrder          : 2;
    UCHAR  ucTrafficClass           : 3;
    UCHAR  ucMaxSduSize;
    UCHAR  ucMaxBitRateUp;
    UCHAR  ucMaxBitRateDown;
    UCHAR  ucSduErrorRatio          : 4;
    UCHAR  ucResidualBer            : 4;
    UCHAR  ucTrafficHandlPriority   : 2;
    UCHAR  ucTransferDelay          : 6;
    UCHAR  ucGuarantBitRateUp;
    UCHAR  ucGuarantBitRateDown;
    UCHAR  ucSourceStatisticsDescriptor  : 4;
    UCHAR  ucSignallingIndication         : 1;
    UCHAR  ucSpare4                         : 3;
    UCHAR  ucMaxBitRateDownExtended;
    UCHAR  ucGuarantBitRateDownExtended;
    UCHAR  ucMaxBitRateUpExtended;
    UCHAR  ucGuarantBitRateUpExtended;
    UCHAR  ucAllocaRetentPriority;
#else
    UCHAR  ucSpare1                 : 2;
    UCHAR  ucDelayClass             : 3;
    UCHAR  ucReliabilityClass       : 3;
    UCHAR  ucPeakThroughput         : 4;
    UCHAR  ucSpare2                 : 1;
    UCHAR  ucPrecedenceClass        : 3;
    UCHAR  ucSpare3                 : 3;
    UCHAR  ucMeanThroughput         : 5;
    UCHAR  ucTrafficClass           : 3;
    UCHAR  ucDeliveryOrder          : 2;
    UCHAR  ucDeliveryErroSdu        : 3;
    UCHAR  ucMaxSduSize;
    UCHAR  ucMaxBitRateUp;
    UCHAR  ucMaxBitRateDown;
    UCHAR  ucResidualBer            : 4;
    UCHAR  ucSduErrorRatio          : 4;
    UCHAR  ucTransferDelay          : 6;
    UCHAR  ucTrafficHandlPriority   : 2;
    UCHAR  ucGuarantBitRateUp;
    UCHAR  ucGuarantBitRateDown;
    UCHAR  ucSpare4                                    : 3;
    UCHAR  ucSignallingIndication               : 1;
    UCHAR  ucSourceStatisticsDescriptor      : 4;
    UCHAR  ucMaxBitRateDownExtended;
    UCHAR  ucGuarantBitRateDownExtended;
    UCHAR  ucMaxBitRateUpExtended;
    UCHAR  ucGuarantBitRateUpExtended;
    UCHAR  ucAllocaRetentPriority;
#endif
} VOS_PACKED GTP_GGSN_QOS_S,CDRF_GTP_QOS_S;

typedef struct tagGTP_SAE_QOS_S
{
#if UGW_BYTE_ORDER == UGW_LITTLE_ENDIAN
    UCHAR ucPreemptionVulnerability : 1;
    UCHAR ucSpare2 : 1;
    UCHAR ucAllocaRetentPriority : 4;
    UCHAR ucPreemptionCapability : 1;
    UCHAR ucSpare1 : 1;

    UCHAR  ucVer : 4;
    UCHAR  ucQosClassIdentifier    : 4;/*�����û���ҵ��qci��ȡֵ��Χ1-9�����������������Լ���ת���±���*/
#else
    UCHAR ucSpare1 : 1;
    UCHAR ucPreemptionCapability : 1;
    UCHAR ucAllocaRetentPriority : 4;
    UCHAR ucSpare2 : 1;
    UCHAR ucPreemptionVulnerability : 1;

    UCHAR  ucQosClassIdentifier    : 4;/*�����û���ҵ��qci��ȡֵ��Χ1-9�����������������Լ���ת���±���*/
    UCHAR  ucVer : 4;
#endif
    UCHAR  ucRealQci;  /*���������û�����ʵqci��֧����չ��ȡֵ��Χ1-��չ���ֵ�����ڷ�װ��Ϣ*/
    UCHAR  ucTrafficHandlPriority;
    UCHAR  aucMaxBitRateUp[5];          //��4�ֽ�Ϊ������
    UCHAR  aucMaxBitRateDown[5];        //��4�ֽ�Ϊ������
    UCHAR  aucGuarantBitRateUp[5];      //��4�ֽ�Ϊ������
    UCHAR  aucGuarantBitRateDown[5];    //��4�ֽ�Ϊ������
} VOS_PACKED GTP_SAE_QOS_S;

typedef union unGTP_QOS
{
    GTP_GGSN_QOS_S    stGgsnQos; /* GGSN��ƷQOS���� */
    GTP_SAE_QOS_S     stSaeQos;  /* SAE��ƷQOS���� */
} VOS_PACKED unGTP_QOS;

typedef struct tagGTP_QOS_S
{
    unGTP_QOS unCommonQos;
} VOS_PACKED GTP_QOS_S;

typedef struct tagAPN_AMBR_S
{
    ULONG ulAmbrUL;
    ULONG ulAmbrDL;
}VOS_PACKED APN_AMBR_S;

typedef struct tagMEDIA_DETECT_S
{
    GTP_QOS_S           stLastSavedNormReqQos;
    GTP_QOS_S           stLastSavedNormNegQos;
    /*���ڱ���˴����ݸ�֪����֮ǰ�������е�AMBRֵ,���˴�����ʧ��ʱ���л���*/
    APN_AMBR_S          stLastSaveAmbr;
    /*���ڱ���IPN�������ݸ�֪����ǰ�������е�AMBRֵ,������෢����º��AMBRֵ,����IPN����qos��������ʱʹ��(usReqQoSLevelΪ0)*/

    /*4Gʱ�洢IPN����ǰ��QOS��Ϣ�������ϻ�����*/
    GTP_QOS_S           stOriginSavedNormReqQos;
    GTP_QOS_S           stOriginSavedNormNegQos;
    APN_AMBR_S          stOriginAmbr;

}  VOS_PACKED MEDIA_DETECT_S;

//
//l2tp define
//
typedef struct tagSDB_L2TP_INFO
{
    ULONG  ulMagicNum;                            /* Magic-Number LCP */
    ULONG  ulAccm;                              /* ACCM */
    ULONG ulGiifIndex;
    USHORT usMtu;
    USHORT usLocalTunnelId;                  /* local_tunnel_id  */
    USHORT usLocalSessionId;                  /* local_session_id */
    USHORT usLocalPort;
    ULONG  ulLocalIP;
    ULONG  ulPeerIP;
    USHORT usPeerTunnelId;                  /* Peer_tunnel_id  */
    USHORT usPeerSessionId;                  /* Peer_session_id */
    ULONG  ulMSIP;
    USHORT usPeerPort;
    UCHAR  ucVer;
    UCHAR  ucPppMode;
    UCHAR  ucDpeId;
    UCHAR  Res[3];
} SDB_L2TP_INFO_S;

//
//gtpv2 servinc network define
//

typedef struct tagAM_GTPV2_SERVING_NETWORK_S
{
#if (UGW_BYTE_ORDER == UGW_BIG_ENDIAN)
    VOS_UINT8 btMCC2:4;
    VOS_UINT8 btMCC1:4;
    VOS_UINT8 btMNC3:4;
    VOS_UINT8 btMCC3:4;
    VOS_UINT8 btMNC2:4;
    VOS_UINT8 btMNC1:4;
#else
    VOS_UINT8 btMCC1:4;
    VOS_UINT8 btMCC2:4;
    VOS_UINT8 btMCC3:4;
    VOS_UINT8 btMNC3:4;
    VOS_UINT8 btMNC1:4;
    VOS_UINT8 btMNC2:4;
#endif
} VOS_PACKED AM_GTPV2_SERVING_NETWORK_S;

//
//gtpv2 USER LOCATION define
//
/*USER LOCATION INFOMATION IE*/
#define GTP_MAX_USER_LOCATION_INFO_LEN 8
typedef   struct    tagGTP_USER_LOCATION_INFO_S
 {
    UCHAR  ucGeographicLocationType;
#if UGW_BYTE_ORDER == UGW_LITTLE_ENDIAN
     UCHAR    MCC1  : 4;
     UCHAR    MCC2  : 4;
     UCHAR    MCC3  : 4;
     UCHAR    MNC3  : 4;
     UCHAR    MNC1  : 4;
     UCHAR    MNC2  : 4;

#else
     UCHAR  MCC2  : 4;
     UCHAR  MCC1  : 4;
     UCHAR  MNC3  : 4;
     UCHAR  MCC3  : 4;
     UCHAR  MNC2  : 4;
     UCHAR  MNC1  : 4;
#endif
  USHORT LAC;
   union   unCiOrSac
     {
         USHORT usCI;
         USHORT usSAC;
      } ciOrSac;

#define  CI  ciOrSac.usCI
#define  SAC   ciOrSac.usSAC
} VOS_PACKED  GTP_USER_LOCATION_INFO_S;

/*lint -align_max(push) -align_max(1)*/
//
//gtp rai define
//
typedef struct tagGTP_RAI_S
{
#if UGW_BYTE_ORDER == UGW_LITTLE_ENDIAN
    UCHAR  MCC1  : 4;
    UCHAR  MCC2  : 4;
    UCHAR  MCC3  : 4;
    UCHAR  MNC3  : 4;
    UCHAR  MNC1  : 4;
    UCHAR  MNC2  : 4;
    USHORT LAC;
    UCHAR  RAC;
#else
    UCHAR  MCC2  : 4;
    UCHAR  MCC1  : 4;
    UCHAR  MNC3  : 4;
    UCHAR  MCC3  : 4;
    UCHAR  MNC2  : 4;
    UCHAR  MNC1  : 4;
    USHORT LAC;
    UCHAR  RAC;
#endif
}VOS_PACKED  GTP_RAI_S;
/*lint -align_max(pop)*/

typedef struct tagGTP_GGSN_ULI_S
{
    GTP_USER_LOCATION_INFO_S stUserLocationInfo; /*8*/
    GTP_RAI_S stRAI; /*6*/
    GTP_RAI_S stOldRAI;     /*6*/
}VOS_PACKED GTP_GGSN_ULI_S;

typedef struct tagAM_GTPV2_ULI_TAI_S
{
#if (UGW_BYTE_ORDER == UGW_BIG_ENDIAN)
    VOS_UINT8 btMCC2:4;
    VOS_UINT8 btMCC1:4;
    VOS_UINT8 btMNC3:4;
    VOS_UINT8 btMCC3:4;
    VOS_UINT8 btMNC2:4;
    VOS_UINT8 btMNC1:4;
#else
    VOS_UINT8 btMCC1:4;
    VOS_UINT8 btMCC2:4;
    VOS_UINT8 btMCC3:4;
    VOS_UINT8 btMNC3:4;
    VOS_UINT8 btMNC1:4;
    VOS_UINT8 btMNC2:4;
#endif  /*3*/
    VOS_UINT16 usTrackingAreaCode;
} VOS_PACKED AM_GTPV2_ULI_TAI_S;

typedef struct tagAM_GTPV2_ULI_ECGI_S
{
#if (UGW_BYTE_ORDER == UGW_BIG_ENDIAN)
    VOS_UINT8 btMCC2:4;
    VOS_UINT8 btMCC1:4;
    VOS_UINT8 btMNC3:4;
    VOS_UINT8 btMCC3:4;
    VOS_UINT8 btMNC2:4;
    VOS_UINT8 btMNC1:4;
#else
    VOS_UINT8 btMCC1:4;
    VOS_UINT8 btMCC2:4;
    VOS_UINT8 btMCC3:4;
    VOS_UINT8 btMNC3:4;
    VOS_UINT8 btMNC1:4;
    VOS_UINT8 btMNC2:4;
#endif  /*3*/
#if UGW_BYTE_ORDER == UGW_BIG_ENDIAN
            VOS_UINT32 btReserved:4;
            VOS_UINT32 btECI:28;
#else
            VOS_UINT32 btECI:28;
            VOS_UINT32 btReserved:4;
#endif


} VOS_PACKED AM_GTPV2_ULI_ECGI_S;

typedef struct tagAM_GTPV2_ULI_LTE_S
{
    AM_GTPV2_ULI_TAI_S stTAI;/*5*/
    AM_GTPV2_ULI_ECGI_S stECGI;/*7*/
} VOS_PACKED GTPV2_ULI_LTE_S;

//
//gtpv2 uli define
//

typedef struct tagAM_GTPV2_ULI_CGI_S
{
#if (UGW_BYTE_ORDER == UGW_BIG_ENDIAN)
    VOS_UINT8 btMCC2:4;
    VOS_UINT8 btMCC1:4;
    VOS_UINT8 btMNC3:4;
    VOS_UINT8 btMCC3:4;
    VOS_UINT8 btMNC2:4;
    VOS_UINT8 btMNC1:4;
#else
    VOS_UINT8 btMCC1:4;
    VOS_UINT8 btMCC2:4;
    VOS_UINT8 btMCC3:4;
    VOS_UINT8 btMNC3:4;
    VOS_UINT8 btMNC1:4;
    VOS_UINT8 btMNC2:4;
#endif  /*3*/
    VOS_UINT16 usLocationAreaCode;
    VOS_UINT16 usCellIdentity;
} VOS_PACKED AM_GTPV2_ULI_CGI_S;

typedef struct tagAM_GTPV2_ULI_SAI_S
{
    VOS_UINT16 usLocationAreaCode;
    VOS_UINT16 usServiceAreaCode;
} VOS_PACKED AM_GTPV2_ULI_SAI_S;


typedef struct tagAM_GTPV2_ULI_RAI_S
{
    VOS_UINT16 usLocationAreaCode;
    VOS_UINT16 usRoutingAreaCode;
} VOS_PACKED AM_GTPV2_ULI_RAI_S;

typedef struct tagAM_GTPV2_ULI_GU_S
{
#if (UGW_BYTE_ORDER == UGW_BIG_ENDIAN)
    VOS_UINT8 btMCC2:4;
    VOS_UINT8 btMCC1:4;
    VOS_UINT8 btMNC3:4;
    VOS_UINT8 btMCC3:4;
    VOS_UINT8 btMNC2:4;
    VOS_UINT8 btMNC1:4;
#else
    VOS_UINT8 btMCC1:4;
    VOS_UINT8 btMCC2:4;
    VOS_UINT8 btMCC3:4;
    VOS_UINT8 btMNC3:4;
    VOS_UINT8 btMNC1:4;
    VOS_UINT8 btMNC2:4;
#endif  /*3*/
    AM_GTPV2_ULI_CGI_S stCGI;/*7*/
    AM_GTPV2_ULI_SAI_S stSAI;/*4*/
    AM_GTPV2_ULI_RAI_S stRAI;/*4*/
} VOS_PACKED GTPV2_ULI_GU_S;

typedef union unGTP_SAE_ULI_S
{
    GTPV2_ULI_LTE_S stGtpv2LteULI;/*12*/
    GTPV2_ULI_GU_S  stGtpv2GuUli;/*18*/
} VOS_PACKED unGTP_SAE_ULI_S;

typedef struct tagAM_GTPV2_ULI_S
{
#if (UGW_BYTE_ORDER == UGW_BIG_ENDIAN)
    VOS_UINT8 btReserved:3;
    VOS_UINT8 btECGI:1;
    VOS_UINT8 btTAI:1;
    VOS_UINT8 btRAI:1;
    VOS_UINT8 btSAI:1;
    VOS_UINT8 btCGI:1;
#else
    VOS_UINT8 btCGI:1;
    VOS_UINT8 btSAI:1;
    VOS_UINT8 btRAI:1;
    VOS_UINT8 btTAI:1;
    VOS_UINT8 btECGI:1;
    VOS_UINT8 btReserved:3;
#endif  /*1*/
    unGTP_SAE_ULI_S unCommonULI;   /*18*/
} VOS_PACKED GTP_SAE_ULI_S;

typedef struct tagGTP_PMIP_BSID_S
{
    /*BSID PCCģ���·�,����CM*/
    UCHAR aucBSID[M_PMIP_BSID_LEN + 1];
    /*BSID�Ƿ���Ч��־*/
#if (UGW_BYTE_ORDER == UGW_BIG_ENDIAN)
    UCHAR btBSID:1;
    UCHAR btReserved:7;
#else
    UCHAR btReserved:7;
    UCHAR btBSID:1;
#endif
    UCHAR aucReserved[2];
}VOS_PACKED GTP_PMIP_BSID_S;

/*����Ŀǰ���������������ڴ�,��˽�TWAN Identifier��Ԫ��ֳ������������б���,SSID���ֺ�uli
����,uli�ṹ��ԭ�г�����20,�����ȻЭ�鶨��SSID�������Ϊ32,ĿǰҲֻ����19���ֽ�(SEȷ��Ŀǰ
�оֵ�ʹ�õ�17���ֽ�,�ٳ���Ŀǰ��û�п���)(s2a����ʱ�϶�����Я��uli��˿��Թ���)*/
typedef struct tagGTP_TWAN_ID_SSID_S
{
    UCHAR ucSSIDLen;
    UCHAR aucSSID[M_TWANID_SSID_LEN_INCONTEXT];
}VOS_PACKED GTP_TWAN_ID_SSID_S;

typedef union unGTP_ULI
{
    GTP_GGSN_ULI_S stGgsnUliAndRai; /* GGSN��ƷQOS����20 */
    GTP_SAE_ULI_S  stSaeULI;  /* SAE��ƷQOS���� 19 */
    GTP_PMIP_BSID_S stPmipBsid;
    GTP_TWAN_ID_SSID_S stTwanSSID;
} VOS_PACKED unGTP_ULI;

typedef struct tagGTP_ULI_S
{
    unGTP_ULI unCommonULI;    /*20*/
} VOS_PACKED GTP_ULI_S;

//
//pco define
//
#define GTP_MAX_ADDITIONALTRACEINFO_LEN 8
#define GTP_MAX_PROTO_CFG_OPTION_LEN   253
typedef struct tagGTP_ADDITIONALTRACEINFO_S
{
    UCHAR     Value[GTP_MAX_ADDITIONALTRACEINFO_LEN];
} VOS_PACKED GTP_ADDITIONALTRACEINFO_S;

//
//qos define
//
typedef struct tagGTP_QOS_NECESSARY_S
{
#if UGW_BYTE_ORDER == UGW_LITTLE_ENDIAN
    UCHAR  ucTrafficClass       : 4;
    UCHAR  ucDelayClass         : 4;
    UCHAR  ucPeakThroughput     : 4;
    UCHAR  ucPrecedenceClass    : 3;
    UCHAR  ucReserved           : 1;
    UCHAR  ucSpare1;
    UCHAR  ucGuarantBitRateUp;
    UCHAR  ucGuarantBitRateDown;
    UCHAR  ucMaxBitRateDownExtended;
    UCHAR  ucGuarantBitRateDownExtended;
    UCHAR  ucTrafficHandlPriority;
    ULONG  ulGuarantBitRateUp;     /*���ֶ�ר����UGW*/
    ULONG  ulGuarantBitRateDown;  /*���ֶ�ר����UGW*/
    UCHAR  ucMaxBitRateUpExtended;
    UCHAR  ucGuarantBitRateUpExtended;
    UCHAR  ucSpare2;
    UCHAR  ucRealQci;
#else
    UCHAR  ucDelayClass           : 4;
    UCHAR  ucTrafficClass         : 4;
    UCHAR  ucReserved             : 1;
    UCHAR  ucPrecedenceClass      : 3;
    UCHAR  ucPeakThroughput       : 4;
    UCHAR  ucSpare1;
    UCHAR  ucGuarantBitRateUp;
    UCHAR  ucGuarantBitRateDown;
    UCHAR  ucMaxBitRateDownExtended;
    UCHAR  ucGuarantBitRateDownExtended;
    UCHAR  ucTrafficHandlPriority;
    ULONG  ulGuarantBitRateUp;   /*���ֶ�ר����UGW*/
    ULONG  ulGuarantBitRateDown; /*���ֶ�ר����UGW*/
    UCHAR  ucMaxBitRateUpExtended;
    UCHAR  ucGuarantBitRateUpExtended;
    UCHAR  ucSpare2;
    UCHAR  ucRealQci;
#endif
}VOS_PACKED GTP_QOS_NECESSARY_S;

typedef struct tag3GPP_SGSN_MCC_MNC_S       /*  SGSN_MCC_MNC�ṹ  */
{
#if UGW_BYTE_ORDER == UGW_LITTLE_ENDIAN   /*  С������  */
    UCHAR MCC1  : 4;
    UCHAR MCC2  : 4;
    UCHAR MCC3  : 4;
    UCHAR MNC1  : 4;
    UCHAR MNC2  : 4;
    UCHAR MNC3  : 4;
#else

    UCHAR MCC2  : 4;
    UCHAR MCC1  : 4;
    UCHAR MNC1  : 4;
    UCHAR MCC3  : 4;
    UCHAR MNC3  : 4;
    UCHAR MNC2  : 4;
#endif
    UCHAR ucFlag;   /* �Ƿ���Ч�ı�־��ȡ��ԭ����ȫf�жϷ�ʽ����������4�ֽڡ�0��Ч��1��Ч */
} T3GPP_SGSN_MCC_MNC_S; /*  SGSN_MCC_MNC�ṹ  */

//
//am cm used define
//

typedef struct tagAM_CM_UPDATETYPE
{
    UCHAR  ucVersionChangeFlag:1; /* PDP�汾�仯 */
    UCHAR  ucQosChangeFlag:1;  /* QOS:�����ն��û������QoS�仯����DCC�ͻ���������� */
    UCHAR  ucSgsnChangeFlag:1; /* SGSN:����SGSN IP��ַ�仯����DCC�ͻ���������� */
    UCHAR  ucUserLocChangeFlag:1; /* LOCATION�����ն��û�λ�ñ仯����DCC�ͻ���������� */
    UCHAR  ucRatChangeFlag:1;  /* RAT: �������߽��뼼���仯����DCC�ͻ���������� */
    UCHAR  ucPLMNChangeFlag:1; /* ����PLMN�仯����DCC�ͻ���������� */
    UCHAR  ucRoamingChangeFlag:1; /* ���α仯 */
    UCHAR  ucTFTChangeFlag:1;  /* ��ΪTFT�任 */

    UCHAR  ucTimeZoneChangeFlag :1; /* ����msTimeZone�仯����DCC�ͻ���������� */
    UCHAR  ucRaiChangeFlag :1;  /* ����RAI�ı� */
    UCHAR  ucRoleChangeFlag : 1;  /*������ɫ�ı�*/
    UCHAR  ucUpdateUplink            : 1;
    UCHAR  ucUpdateDownlink          : 1;
    UCHAR  ucUpdateIndirectForward   : 1;
    UCHAR  ucUpdateLiFlag            : 1;
    UCHAR  ulUpdateEndMarkFlag       : 1; /* EndMarker��ʶ. 1: �·�����ʱ��Ҫ�ȴ�ת������Ӧ. 0: ����Ҫ�ȴ�, Ĭ��Ϊ0
                                             ��Update User Plane ������,��Ҫ�ȴ�ת������Ӧ,���ڳ���End Marker��Ϣ */
    UCHAR  ucLossOfBearerFlag:1;
    UCHAR  ucRecoveryOfBearerFlag:1;
    UCHAR  ucMaxNRBearerReachedFlag:1;
    UCHAR  ucQosChangeExceedAuthFlag:1;
    UCHAR  ucIpCanChangeFlag:1;
    UCHAR  ucGWMalfunctionFlag :1;
    UCHAR  ucResourcesLimatitionFlag :1;
    UCHAR  ucNoEventTriggerFlag:1;

    UCHAR  ucCoaUserProfileChangeFlag:1;  /* AAA�����CoA����,UserProfile�仯 */
    UCHAR  ucMMEChangeFlag:1;    /* MME IP��ַ�仯 */
    UCHAR  ucSGWChangeFlag:1;    /* SGW IP��ַ�仯 */
    UCHAR  ucIPAllcationFlag:1;  /* UE_IP_ADDRESS_ALLOCATE  */
    UCHAR  ucIPReleaseFlag:1;    /* UE_IP_ADDRESS_RELEASE */
    UCHAR  ucCGIPChangeFlag:1;/* CG IP change Added by zjl at 2010-01-20 for UGWC03*/
    UCHAR  ucSessionStopIndication:1; /* For CM last deleted bear */
    UCHAR  ucIdletimeFlag :1;

    UCHAR  ucCGIChangeFlag:1; /* ULI�е�CGI�仯*/
    UCHAR  ucSAIChangeFlag:1; /* ULI�е�SAI�仯*/
    UCHAR  ucECGIChangeFlag:1; /* ULI�е�ECGI�仯*/
    UCHAR  ucTAIChangeFlag:1; /* ULI�е�TAI�仯*/
    UCHAR  ucQosTrafficClass     :1;    /* CHANGE_IN_QOS_TRAFFIC_CLASS */
    UCHAR  ucQosRelClass         :1;    /* CHANGE_IN_QOS_RELIABILITY_CLASS */
    UCHAR  ucQosDelayClass       :1;    /* CHANGE_IN_QOS_DELAY_CLASS */
    UCHAR  ucQosPeakThr          :1;    /* CHANGE_IN_QOS_PEAK_THROUGHPUT */

    UCHAR  ucQosPrecedenceClass  :1;    /* CHANGE_IN_QOS_PRECEDENCE_CLASS */
    UCHAR  ucQosMeanThroughput   :1;    /* CHANGE_IN_QOS_MEAN_THROUGHPUT */
    UCHAR  ucQosMBRForUp         :1;    /* CHANGE_IN_QOS_MAXIMUM_BIT_RATE_FOR_UPLINK */
    UCHAR  ucQosMBRForDown       :1;    /* CHANGE_IN_QOS_MAXIMUM_BIT_RATE_FOR_DOWNLINK */
    UCHAR  ucQosResidualBer      :1;    /* CHANGE_IN_QOS_RESIDUAL_BER */
    UCHAR  ucQosSduErrRadio      :1;    /* CHANGE_IN_QOS_SDU_ERROR_RATIO */
    UCHAR  ucQosTransferDelay    :1;    /* CHANGE_IN_QOS_TRANSFER_DELAY */
    UCHAR  ucQosTrafficHandpri   :1;    /* CHANGE_IN_QOS_TRAFFIC_HANDLING_PRIORITY */

    UCHAR  ucQosGBRForUp         :1;    /* CHANGE_IN_QOS_GUARANTEED_BIT_RATE_FOR_UPLINK */
    UCHAR  ucQosGBRForDown       :1;    /* CHANGE_IN_QOS_GUARANTEED_BIT_RATE_FOR_DOWNLINK */
    UCHAR  ucLocMcc              :1;    /* CHANGE_IN_LOCATION_MCC */
    UCHAR  ucLocMnc              :1;    /* CHANGE_IN_LOCATION_MNC */
    UCHAR  ucLocRac              :1;    /* CHANGE_IN_LOCATION_RAC */
    UCHAR  ucLoclac              :1;    /* CHANGE_IN_LOCATION_LAC  */
    UCHAR  ucLocCellid           :1;    /* CHANGE_IN_LOCATION_CellId */
    UCHAR  ucTmoCoaChangeFlag    :1;    /* AAA�·�Coa��Ϣ�����ĸ��� */

    UCHAR  ucDTChangeFlag        :1;  /* DTģʽ�仯*/
    UCHAR  ucGtpuChangeFlag      :1;/* GTP-U��ַ�仯*/
    UCHAR  ucQciArpChangeFlag    :1;
    UCHAR  ucAmbrChangeFlag      :1;
    UCHAR  ucEarpChangeFlag      :1;
    UCHAR  ucPcscfFaultFlag          :1;
    //UCHAR  ucVogProfileChangeFlag      :1;/* ���͵�MSU��vog-profile�仯*/
    UCHAR  ucCongestionChangeFlag          :1;

    UCHAR  ucSubNetChangeFlag :1;
    UCHAR  ucbit2SuspendUpd:2;         /*ADD: CSFB suspend update flag, jiangxu 90004782*/
    UCHAR  ucCLHandoverFlag :1;   /*��ʶ��ǰ��C/L���еĳ���*/
    UCHAR  ucC2LSecondMatchFlag:1;
    UCHAR  uc34HOQosVersionChgFlg :1;
    UCHAR  ucRsv :3;
} VOS_PACKED AM_CM_UPDATETYPE_S;

//
//gtp ip define
//
/* ������Ϣ��IP��ַ��Ϣ */
typedef struct tagSDB_REQ_MSG_IP_INFO_S
{
    ULONG ulPeerIp;     /* �Զ˵�ַ */
    ULONG ulLocalIp;    /* ���˵�ַ */
    ULONG ulVrfIndex;   /* VPN���� */
} SDB_REQ_MSG_IP_INFO_S;

typedef struct tagGTP_QOS_SUB_S
{
    UCHAR  ucMaxBitRateUp;
    UCHAR  ucMaxBitRateDown;
    UCHAR  ucMaxBitRateUpExtended;
    UCHAR  ucMaxBitRateDownExtended;
    UCHAR  ucGuarantBitRateUp;
    UCHAR  ucGuarantBitRateDown;
    UCHAR  ucGuarantBitRateUpExtended;
    UCHAR  ucGuarantBitRateDownExtended;
} GTP_QOS_SUB_S;

typedef struct tagGTP_EVOLVED_ARP_S
{
#if UGW_BYTE_ORDER == UGW_LITTLE_ENDIAN
    UCHAR ucPreemptionVulnerability  : 1;
    UCHAR ucSpare2                   : 1;
    UCHAR ucAllocaRetentPriority     : 4;
    UCHAR ucPreemptionCapability     : 1;
    UCHAR ucSpare1                   : 1;
#else
    UCHAR ucSpare1                   : 1;
    UCHAR ucPreemptionCapability     : 1;
    UCHAR ucAllocaRetentPriority     : 4;
    UCHAR ucSpare2                   : 1;
    UCHAR ucPreemptionVulnerability  : 1;
#endif
} VOS_PACKED GTP_EVOLVED_ARP;

//
//qos common flag define
//

/*
 *Common Flags IE
 */
typedef struct tagGTP_COMMON_FLAGS_S
{
#if UGW_BYTE_ORDER == UGW_LITTLE_ENDIAN
    UCHAR  ucProhibitPayloadCompression       :1;
    UCHAR  ucMbmsServiceType                         :1;
    UCHAR  ucRanProceduresReady                    :1;
    UCHAR  ucMbmsCountingInformation            :1;
    UCHAR  ucNoQosNegotiation                          :1;
    UCHAR  ucNrsn                          :1;
    UCHAR  ucUpgradeQosSupported   :1 ;
    UCHAR  ucDualAddressBearerFlag      :1;
#else
    UCHAR  ucDualAddressBearerFlag      :1;
    UCHAR  ucUpgradeQosSupported   :1 ;
    UCHAR  ucNrsn                          :1;
    UCHAR  ucNoQosNegotiation                          :1;
    UCHAR  ucMbmsCountingInformation            :1;
    UCHAR  ucRanProceduresReady                    :1;
    UCHAR  ucMbmsServiceType                         :1;
    UCHAR  ucProhibitPayloadCompression       : 1;
#endif
} VOS_PACKED GTP_COMMON_FLAGS_S;

//
//gtp backup define
//


typedef struct tagSDB_WITHDRAW_DATA_S
{
    UCHAR ucUgwRole;        /* ��ɫ��Ϣ */
    UCHAR ucRatType;        /* RAT Type */
    UCHAR ucLeftSigIfType;  /* ��������ӿ����� */
    UCHAR ucRightSigIfType; /* �Ҳ������ӿ����� */

    AM_GTPV2_SERVING_NETWORK_S stGTPV2ServingNetwork; /* Serving Network */
    UCHAR ucEPSBearId; /* NSAPI��Ϣ(Э)��ȡֵ��Χ0��15 */

    GTP_ULI_S stULI;

    UCHAR ucSelectMode;     /* Selection Mode */
    UCHAR ucPdpType;        /* PDN Type */
    UCHAR ucRoleChanged;    /* ��ɫ�Ƿ�仯����ʵ����ָ�Ƿ������л� */
    UCHAR ucMsisdnLen;
    GTP_MSISDN szMsisdn;

    /* ������Ҳ���Ϣ����һ������Ҫ���ݣ��������������ʱ�����б��� */

    ULONG ulSgwLeftPeerTeidc;     /* ���Զ����������ʶ */
    ULONG ulSgwLeftLocTeidc;      /* ��౾�����������ʶ */
    ULONG ulLeftPeerSigIpInHeader;/* IPͷ�е����Զ�����IP */
    ULONG ulSgwLeftPeerSigIP;     /* ��Ԫ�н����������Զ�IP */
    ULONG ulSgwLeftLocSigIP;      /* ��౾������IP */
    USHORT usSgwLeftPeerSigPort;  /* ���Զ�����˿� */
    USHORT usSgwLeftLocSigPort;   /* ��౾������˿� */
    ULONG ulSgwLeftLocDataIP;     /* ��౾������IP */
    ULONG ulSgwLeftLocDataIfIndex;  /* ��౾�����ݽӿ����� */
    ULONG ulSgwLeftPeerDataIP;    /* ���Զ�����IP */
    USHORT usLeftSigPathId;       /* �������·��ID */
    USHORT usLeftDataPathId;      /* �������·��ID */

    ULONG ulS5_Gn_PeerTeidc;      /* �Ҳ�Զ����������ʶ */
    ULONG ulS5_Gn_LocTeidc;       /* �Ҳ౾�����������ʶ */
    ULONG ulS5_Gn_PeerSigIP;      /* �Ҳ�Զ�����IP */
    ULONG ulS5_Gn_LocSigIP;       /* �Ҳ౾������IP */
    USHORT usS5_Gn_PeerSigPort;   /* �Ҳ�Զ�����˿� */
    USHORT usS5_Gn_LocSigPort;  /* �Ҳ౾������˿� */
    ULONG ulS5_Gn_PeerDataIP;   /* �Ҳ�Զ�����IP */
    ULONG ulS5_Gn_LocDataIP;    /* �Ҳ౾������IP */
    ULONG ulS5_Gn_LocDataIfIndex; /* �Ҳ౾�����ݽӿ����� */
    USHORT usRightSigPathId;    /* �Ҳ�����·��ID */
    USHORT usRightDataPathId;   /* �Ҳ�����·��ID */

    UCHAR ucLeftEncapType;     /* ����װ����*/
    UCHAR ucRightEncapType;    /* �Ҳ��װ����*/

    /* PDN Address Allocation (PAA)��Ԫ��ص���Ϣ */
    UCHAR ucIPv4AllocType;     /* ��ַ���䷽ʽ����̬�����أ�RADIUS�� */
    UCHAR ucIPv6AllocType;     /* ��ַ���䷽ʽ����̬�����أ�RADIUS�� */
    //S_GTPV2_PAA stGTPV2PAA;
    ULONG ulIPv4Addr;
    in6_addr stIPv6Addr;

    UCHAR ucChargingChar[2];   /* Charging Characteristics */
    UCHAR ucApnRestriction ;   /* Maximum APN Restriction */
    UCHAR ucLeftDataIfType;    /* ���������ӿ����� */
    ULONG ulSgwLeftPeerTeidu;  /* ���Զ����������ʶ */
    ULONG ulSgwLeftLocTeidu;   /* ��౾�����������ʶ */
    ULONG ulS5_Gn_PeerTeidu;   /* �Ҳ౾�����������ʶ */
    ULONG ulS5_Gn_LocTeidu;    /* �Ҳ�Զ����������ʶ */
    ULONG ulChargingId;

    GTP_ADDITIONALTRACEINFO_S stAdditionalTraceInfo;
    GTP_QOS_S stReqQos;        /* �����QOS��Ϣ */
    GTP_QOS_S stNegQos;        /* ����Э�̵�QOS��Ϣ */
    GTP_QOS_NECESSARY_S stOldQos;/*����ʹ�ã����浱ǰ�Ѿ���ʹ�õ�Qos �ı������*/

    APN_AMBR_S stApnAmbr;
    UCHAR ucIsSecActivateFlg : 2; /* ���������Ƿ��Ƕ��μ��������ĵı�ʶ, normal ��ʾ��һ�μ����ȱʡ, second��ʾ���λ�ר�г���*/
    UCHAR ucGtpVer:2;  /* Э��汾�� */
    UCHAR ucDTI : 1;   /* Direct Tunnel Flag��Ԫ��DTI��־λ,0��ʾ2Tunnel,1��ʾ1Tunnel */
    UCHAR ucSgwIsTraceFlag : 1;
    UCHAR ucPgwIsTraceFlag : 1;
    UCHAR ucSendTraceInfoToPgw : 1;
    UCHAR ucMachineState;      /* GTPV2 һ��״̬; GTPV1 ״̬ */
    UCHAR ucMachineL2State;    /* GTPV2 ����״̬*/
    UCHAR ucUsrTypeFlg : 2;       /* �����������е��û�������Ϣ*/
    UCHAR ucIsActByTauOrHo : 1;
    UCHAR ucReserve : 5;          /* �������ֽڶ��룬����ʹ��������ʹ�ñ����ֶ� */
    USHORT usTraceId;
    UCHAR ucSgwListOfInterfaces;
    UCHAR ucPgwListOfInterfaces;

    /* Added start by liruixue on 2011-6-3 for CR20110415042 */
    ULONG ulSgwIfindex;      /* ���ڱ����鼶�ӿڵ�Sgw ���Ifindex */
    ULONG ulPgwIfindex;      /* ���ڱ����鼶�ӿڵ�Pgw or GGSN ���Ifindex */
    /* Added end by liruixue on 2011-6-3 for CR20110415042 */
    T3GPP_SGSN_MCC_MNC_S stSgsnPlmn;
    AM_CM_UPDATETYPE_S stUpdateType; /*4�ֽ�*/            /*��������:GTP_CHANGE_SGSN_IP,GTP_CHANGE_QOS,GTP_CHANGE_LOCATION,GTP_CHANGE_RAT */
    USHORT usLeftRecovery;  /*ucLeftRecovery*/
    UCHAR ucBitMsChangeExtendFlag    : 1;
    UCHAR ucVIPUserFlg               : 1;
    UCHAR ucVIPNewByUpdate           : 1;
    UCHAR ucVIPAccessPrioFlg         : 1;
    UCHAR ucRatTypeOccur             : 1;
    UCHAR ucUserLocationInfoOccur    : 1;
    UCHAR ucMSTimeZoneOccur          : 1;
    UCHAR ucAdditionalTraceInfoOccur : 1;
    UCHAR ucRAIUpdateFlag            : 1;
    UCHAR ucDataFlag:2;           /*add: CSFB�������ǰ��ת�����*/
    UCHAR ucbit1SuspendFlag :1;
    UCHAR ucReserve4                : 4;
    SDB_REQ_MSG_IP_INFO_S stReqMsgIpInfo;
    GTP_QOS_SUB_S stSubQos;
    USHORT usMSTimeZone;
    GTP_EVOLVED_ARP stEvolvedARP;
    GTP_COMMON_FLAGS_S stCommonFlags;
    USHORT usPeerDataFlowLbl;
    USHORT usPeerSigFlowLbl;
    UCHAR  ucIdlePagingIndication;      /*add: CSFB�������ǰ��paging���*/
    UCHAR ucRightDataIfType;        /* �Ҳ�������ӿ����� */
    UCHAR aucRet[2];
    /* PMIPʹ�õ��ֶ� */
    in6_addr stPmipv6LeftPeerAddr;
    ULONG ulReqMsgVrfIndex;
}VOS_PACKED SDB_WITHDRAW_DATA_S; /* Cyjun: ��ʱʹ��һ�ֽڶ��룬�����ݽṹ�ȶ��������ٵ��� */

/*
 *Protocol configuration option IE
 */
typedef struct tagGTP_IE_PROTO_CONF_OPT_S
{
    UCHAR     ucType;
    USHORT    usLen;
    UCHAR     szProtoCfgOption[GTP_MAX_PROTO_CFG_OPTION_LEN];
} VOS_PACKED GTP_IE_PROTO_CONF_OPT_S;

#define M_CFG_MAX_APN_USER_LEN 64
#define M_CFG_MAX_APN_PASS_LEN 128
#ifndef MAXUSERNAMELEN
#define MAXUSERNAMELEN M_CFG_MAX_APN_USER_LEN
#endif
#ifndef MAXUSERPWDLEN
#define MAXUSERPWDLEN M_CFG_MAX_APN_PASS_LEN
#endif

#define MAX_IPCP_PARSE 8  /*���ɴ���������8��IPCP*/
#define GTP_PCO_MAX_IPCP_OPTIONS 20
typedef struct tagGTP_IE_PCO_PARSE_IPCP_S
{
    in6_addr     stIPCPReqIpAddr;
    in6_addr     stIPCPReqDNSAddr0;
    in6_addr     stIPCPReqDNSAddr1;
    ULONG       ulIPCPReqNBNSAddr0;
    ULONG       ulIPCPReqNBNSAddr1;
    ULONG       ulIPCPReqIPCompContent;         /* �洢������ */
    ULONG       ulIPCPReqMobileIPV4;
    UCHAR       ucIpcpReqExist;               /* PCO�Ƿ���IPCP cfg req��0��ʾ��,1��ʾ�� *//*added by haifeng for BYHD02976; */
    UCHAR       ucIpcpReqConfType;               /* PCO��IpcpЭ�����ͣ�0��ʾ������ */
    UCHAR       ucIpcpPktID;                     /* PCO��IpcpЭ��packet ID */
    UCHAR       ucRsv;
    UCHAR       ucIPCPOptionSequence[GTP_PCO_MAX_IPCP_OPTIONS];    /*store IPCP option types as in Configure Request*/
}GTP_IE_PCO_PARSE_IPCP_S;

/* PCO�������ݽṹ*/
/*modified for �ֽڶ��� for v9_b011_t */
typedef struct tagGTP_IE_PCO_PARSE_S
{
    UCHAR       *pucCurPosofIeMem;               /* PCO��Ϣ��ǰָ�� */
    UCHAR       *pucEndofIeMem;                  /* PCO��Ϣ��βָ�� */
    UCHAR       *pucWriteCurPos;                 /* PCOӦ����Ϣд��ǰָ�룬ʹ��ǰӦ����ΪӦ����Ϣ�����ڴ� */
    UCHAR       *pucLcpReqOptions;

    in6_addr    stUserIP;                         /* �û�IP */
    int         iSendControlIndex;               /* ���Ϳ��ƿ����� */

    USHORT      usResponseLen;                   /* ��Ȩ��Ӧ����*/
    USHORT      usPwdLen;                        /* ���볤�� */

    USHORT      usAuthProto;                     /* ��AAA������ʹ�õļ�ȨЭ�� PAP or CHAP    */
    UCHAR       ucAuthReqConfType;               /* PCO��ʹ�õļ�ȨЭ��     */
    UCHAR       ucPktID;                         /* PCO�м�ȨЭ�� packet ID */

    UCHAR       ucUsrName[MAXUSERNAMELEN + 2];   /* �û���*/
    UCHAR       ucImsFlag;                       /*�õ���λ�ֱ��ʶIMS���������ļ���������Ϣ��PCO��Դ���Ƿ�Я���������*/
    UCHAR       ucUsrNameLen;                    /* �û������� */

    UCHAR      ucNRSN;                         /*Network Request Support Network (NRSN) */
    UCHAR       ucPwd[MAXUSERPWDLEN+1];           /* ���� */
    UCHAR       ucCallFromId[20];                /* ���к��� */
    UCHAR       ucCallFromIdLen;                 /* ���к��볤��*/
    UCHAR       ucCallToId[64];                  /* ���к��� */
    UCHAR       ucCallToIdLen;                   /* ���к��볤�� */
    UCHAR       ucResponse[256];                 /* ��Ȩ��Ӧ */

    UCHAR      ucAddrDhcpsFlag;
    UCHAR      ucAddrNasFlag;
    UCHAR       ucIPv6DnsCount;
    UCHAR       ucIPv4DnsCount;

    UCHAR       ucMSISDN;
    UCHAR       ucLcpReqConfType;               /* PCO��LcpЭ�����ͣ�0��ʾ������,1��ʾ�� */
    UCHAR       ucLcpPktID;                     /* PCO��lcpЭ��packet ID */
    UCHAR       ucLcpReqLen;

    ULONG       ulPCSCFIPV4IP;
    in6_addr    stPcscfIPV6IP;
    GTP_IE_PCO_PARSE_IPCP_S stIpcp[MAX_IPCP_PARSE];
} GTP_IE_PCO_PARSE_S;

#if 0
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
     UCHAR SPARE : 4;        /* ��1��� */
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
     UCHAR SPARE : 4;        /* ��1��� */
     UCHAR MSIN10: 4;
#endif
} GTP_IMSI_S;
#endif

//
//gtp trce define
//
typedef struct tagAM_GTPV2_TRACE_INFO_S
{
#if (UGW_BYTE_ORDER == UGW_BIG_ENDIAN)
    VOS_UINT8 btMCC2:4;
    VOS_UINT8 btMCC1:4;
    VOS_UINT8 btMNC3:4;
    VOS_UINT8 btMCC3:4;
    VOS_UINT8 btMNC2:4;
    VOS_UINT8 btMNC1:4;
#else
    VOS_UINT8 btMCC1:4;
    VOS_UINT8 btMCC2:4;
    VOS_UINT8 btMCC3:4;
    VOS_UINT8 btMNC3:4;
    VOS_UINT8 btMNC1:4;
    VOS_UINT8 btMNC2:4;
#endif
    VOS_UINT8 aucTraceId[3];
    VOS_UINT8 aucTriggerEvents[9];
    VOS_UINT16 usListOfNeTypes;
    VOS_UINT8 ucSessionTraceDepth;
    VOS_UINT8 aucListOfInterfaces[12];
    VOS_UINT32 ulIpOfTreceCollEntity;
} VOS_PACKED AM_GTPV2_TRACE_INFO_S;


//
//gtpv2 define
//
//typedef S_DUAL_IP S_GTPV2_PAA;
typedef struct
{
    /* IPv4 ~ 1; IPv6 ~ 2; IPv4/IPv6 ~ 3 */
    VOS_UINT8 ucPdnType;

    /* IPV6����IPV4/IPV6��Чʱ��ָIPV6��ַ��ǰ׺���� */
    /* In GTP 29.274 Rel 8, Prefix length has a fixed value of /64 */
    VOS_UINT8 ucIPV6PrefixLen;

    VOS_UINT8 aucReserved[2];

    DHCPC_IPV4 aucIPV4;
    DHCPC_IPV6 aucIPV6;
}VOS_PACKED S_GTPV2_PAA;

#define AAA_MAX_SERVICE_LIST_NUM     10 /* Added by shexinyuan00140430 at 2010-04-01 V9R8C01 for SSG */
#define M_CFG_MAX_MULTI_APN_PASS_LEN 63

//
//aaa struct define
//
typedef struct  tagAAA_Service_Node
{
    ULONG      ulServiceChargingType;
    UCHAR      ucServiceUsername[MAXUSERNAMELEN];
    UCHAR      ucPassword[M_CFG_MAX_MULTI_APN_PASS_LEN + 1];
    USHORT     usServiceIndex;
    UCHAR      ucTag;
    UCHAR      ucReserved;
}AAA_Service_Node;

typedef struct  tagAAA_Service_List
{
    UCHAR                 ucServiceListNum;              /*service�ĸ���*/
    UCHAR                 ucPrimaryIndicator;          /*��־�ĸ�����service*/
    UCHAR                 ucReserved[2];
    AAA_Service_Node      astServicelist[AAA_MAX_SERVICE_LIST_NUM];
}AAA_Service_List;

typedef struct tagUGW_QOS_UPDATE_BAKUP_S
{
    UCHAR   ucQosType;
    UCHAR   ucOldRealQCI;          /* PCRFC_PDP_BEARER_RLN_S�е���Ӧ�ֶ� */
    UCHAR   ucOldQCI;          /* PCRFC_PDP_BEARER_RLN_S�е���Ӧ�ֶ� */
    UCHAR   ucOldArp : 4;          /* PCRFC_PDP_BEARER_RLN_S�е���Ӧ�ֶ� */
    UCHAR   ucBit1PEC :1; //Pre-emption-Capability
    UCHAR   ucBit1PEV :1; //Pre-emption-Vulnerability
    UCHAR   ucBit2Rev :2;
    ULONG   ulApnAmbrUL;
    ULONG   ulApnAmbrDL;
    ULONG   ulGbrUpLink;
    ULONG   ulGbrDwLink;
    ULONG   ulMbrUpLink;
    ULONG   ulMbrDwLink;
} UGW_TFT_QOS_UPDATE_BAKUP_S;

//
//mcc-mnc define
//
typedef struct tag3GPP_IMSI_MCC_MNC_S       /*  IMSI_MCC_MNC�ṹ  */
{
#if UGW_BYTE_ORDER == UGW_LITTLE_ENDIAN   /*  С������  */
    UCHAR MCC1  : 4;
    UCHAR MCC2  : 4;
    UCHAR MCC3  : 4;
    UCHAR MNC1  : 4;
    UCHAR MNC2  : 4;
    /*UCHAR SPARE : 4;*/                        /*  ������1  */
    /* BEGIN: Added by Ԭ�, 2003/7/29 */
    UCHAR MNC3  : 4;
    /* END:   Added by Ԭ�, 2003/7/29 */
#else

    UCHAR MCC2  : 4;
    UCHAR MCC1  : 4;
    UCHAR MNC1  : 4;
    UCHAR MCC3  : 4;
    /*UCHAR SPARE : 4;*/                        /*  ������1  */
    /* BEGIN: Added by Ԭ�, 2003/7/29 */
    UCHAR MNC3  : 4;
    /* END:   Added by Ԭ�, 2003/7/29 */
    UCHAR MNC2  : 4;
#endif
} VOS_PACKED T3GPP_IMSI_MCC_MNC_S;

typedef T3GPP_IMSI_MCC_MNC_S T3GPP_GGSN_MCC_MNC_S; /*  GGSN_MCC_MNC�ṹ  */

//
//trig define
//
/* sdb��stTriggerType������ */
typedef struct tagAM_AUTH_TMO_TRIGGER_TYPE
{
    UCHAR ucChangeInSgsnIp:1;
    UCHAR ucChangeInQos:1;
    UCHAR ucChangeInLocation:1;
    UCHAR ucChangeInRat:1;
    UCHAR ucChangeInQosTrafficClass:1;
    UCHAR ucChangeInQosReliabilityClass:1;
    UCHAR ucChangeInQosDelayClass:1;
    UCHAR ucChangeInQosPeakThroughput:1;
    UCHAR ucChangeInQosPrecedenceClass:1;
    UCHAR ucChangeInQosMeanThrroughput:1;
    UCHAR ucChangeInQosMBRup:1;
    UCHAR ucChangeInQosMBRdn:1;
    UCHAR ucChangeInQosResidualBer:1;
    UCHAR ucChangeInQosSDUErrorRatio:1;
    UCHAR ucChangeInQosTransferDelay:1;
    UCHAR ucChangeInQosTrafficHandPri:1;

    UCHAR ucChangeInQosGBRup:1;
    UCHAR ucChangeInQosGBRdn:1;
    UCHAR ucChangeInLocationMCC:1;
    UCHAR ucChangeInLocationMNC:1;
    UCHAR ucChangeInLocationRAC:1;
    UCHAR ucChangeInLocationLAC:1;
    UCHAR ucChangeInLocationCellID:1;
    UCHAR ucTmoAcctInterimInterval:1;
    UCHAR ucTmoAcctInterimVolume:1;
    UCHAR ucChangeInCellCongestion:1;
    UCHAR ucChangeInEcgi:1;
    UCHAR ucChangeInTai:1;
    UCHAR ucChangeInRai:1;
    UCHAR ucChangeInUli:1;
    UCHAR ucValidFlg:1;     /* �Ƿ���Ч */
    UCHAR ucRemoveFlag:1;

} VOS_PACKED AM_AUTH_TMO_TRIGGER_TYPE_S;

typedef struct tagBRAS_PDP_Str
{
    ULONG ulAcctSessionLen;
    UCHAR ulAcctSessionId[MAX_BRAS_SESSION_LEN];   /* acct session id */
    struct tagBRAS_PDP_Str*  pNext;
} BRAS_PDP_Str;

typedef struct tagBRAS_Session_Info
{
    UCHAR aucMacAddress[MAX_MACADDRESS_LEN];/* ����MAC��ַ */
    ULONG ulUplinkCommittedRate;
    ULONG ulDownlinkCommittedRate;
    ULONG ulUplinkPeakRate;
    ULONG ulDownlinkPeakRate;
    BRAS_PDP_Str* pstPdpinfo;    /* ר�г��ص���Ϣ*/
} BRAS_Session_Info;

typedef union tagunSession_Info
{
    BRAS_Session_Info  stBRASSession;
}unSession_Info;

#define MAX_CFPROFILES_FROM_ONE_GX_MESSAGE        5
#define MAX_CFPROFILE_IN_PDC                      10

/* BEGIN: Added by chenlibin, 2013/4/6 */
typedef struct tagSCCG_LICENSETYPE_S
{
    UCHAR  ucBrasFlag:1;  /*�Ƿ�Ϊ����������û�*/
    UCHAR  ucHotBilling:1;  /*�Ƿ�Ϊhot billing */
    UCHAR  ucPccLicenseFlag:1;    /*�Ƿ�ΪPCC�û�����*/
    UCHAR  ucSCCGFlag:1;/*�Ƿ�Ϊradius�����û�*/
    UCHAR  ucOnlineChargeFlag:1;/*�Ƿ�Ϊ���߼Ʒ��û�*/
    UCHAR  ucGulFlag:1;/*�Ƿ�ΪGGSN&PGW������û� */
    UCHAR  ucContentChargingFlag:1;  /*�Ƿ�Ϊ���ݼƷ�(FBC)�û�*/
    UCHAR  ucIpv6SessionFlag:1;               /*�Ƿ�Ϊipv6�����û�*/
    UCHAR  ucIpv6OnlineChargingSessFlag:1;    /*�Ƿ�Ϊipv6�Ʒ��û�*/
    UCHAR  ucIpv4v6SessionFlag:1;             /*�Ƿ�Ϊipv4v6�����û�*/
    UCHAR  ucReserved:6;
    UCHAR  ucReserved1[2];
}SCCG_LICENSETYPE_S;
/* END:   Added by chenlibin, 2013/4/6 */

#define RELTMR_T VOS_UINT32
#if 0
/* ��Ҫ:�޸����½ṹ���Ա��Ҫͬ���޸�g_SdbSccgPdpcontextFieldDesc�г�Ա����*/
/* SDB���ݽṹ���� */
typedef struct  tagSDB_SCCG_CONTEXT_S
{

   /*8**/
    ULONG  ucSeqLinkNo:3;
    ULONG  ucSendToPfFlag:1;
    ULONG  ucDataFlag        : 2;      /* ����ת����־ */
    ULONG  ucDataTrcFlg      : 2;
    ULONG ulBackupNext : 24; /*�������*/
    ULONG ucBackupFlag:1;
    ULONG ucBatchNotActive:1;
    ULONG bit1MSUFlagc:1;
    ULONG  ucVIPUserFlg:1;
    ULONG ucQchatFlag:1;           /* �Ƿ�ΪQchat�û���־ */
    ULONG ucSupprotFPIFlag:1;/*FPI���Ա�־*/
    ULONG ucSupAreaCongestionRpt:1; /*С��ӵ���ϱ�*/
    ULONG ucBitAreaCongTriggerFlag:1;
    ULONG ulBackupPre : 24; /*�������*/

    ULONG      ulGspuBdIndex;
    ULONG      ulTeidc;         /* PDN�û������ĵ�TEIDC */
    ULONG      ulTeidu;       /* PDN�û������ĵ�TEIDU */
    ULONG      ulIPv4Addr;
    in6_addr    stIPv6Addr;
    GTP_IMSI_S   stImsi;      /* �û�IMSI��Ϣ8�ֽ�*/
    GTP_MSISDN szMsisdn;  /* �û�MSISDN��Ϣ8�ֽ� */
    GTP_IMEI_S stIMEI;                      /*8�ֽ�*/

    UCHAR* pucAAANegoRspMsg; /* AAA��Ȩ��Ӧ��Ϣָ��Session��idleʱ������������*/
    SDB_TFT_S* pstTft;
    GTP_PDP_Str* pstPdpinfo;  /* ר�г��ص���Ϣ*/
    AM_IPN_MSE_PROFILE_INFO_S *pstMseProfileInfo;  //10.1MSE Profile������ǿ
    /* ckp��� */
    VOID *pstSGWFqCsidNext;
    VOID *pstPGWFqCsidNext;
    GTP_QOS_S *pstOriginalNegoQos; /* To remove */
    MEDIA_DETECT_S * pstMediaDetectElement;
    GTP_SAE_QOS_S *pstOriginalUEReqQos; /*���ڼ�¼UE�������qos��Ϣ������ۼӵĽ��*/
    SDB_L2TP_INFO_S * pstL2TPInfo;
    SDB_WITHDRAW_DATA_S *pstWithdrawData;
    GTP_IE_PROTO_CONF_OPT_S * pstPCO;           /* Protocol Configuration Option(Э) */
    GTP_IE_PCO_PARSE_S * pstPCOParse;       /* PCO�����������*/
    AM_GTPV2_TRACE_INFO_S *pstTraceInfo;/*UGW 1.1:Trace info�ݴ�ָ�룬������Ϣ��ָ���ͷ�*/
    S_GTPV2_PAA *pstGTPV2PAA;
    AAA_Service_List *pstServiceList; /* Servic-Listָ�� */
    UCHAR *pstPrcfUpdateMsg;       /* ����PCRFC RAR������Ϣ */
    /* add start by wangboyu at 2011-09-30 for PCC��ǿ */
    UGW_TFT_QOS_UPDATE_BAKUP_S *pstQosRollBack;     /*  �û�ȱʡ���ص�QOS���� */
    UCHAR* pucLapRspMsg; /*����DHCPV6��Ϣ��Lap��Ӧ��Ϣ���ڴ˴�*/

    /* ckp��� */
    UCHAR       ucAcctMultiSessionId[MAX_MULTI_SESSION_LEN];
    UCHAR       ucMultiSessionidLen;
    UCHAR       ucTimeStampFlag: 1;
    UCHAR       ucBWMUsrFlg: 1;
    UCHAR       ucNotDelGiFlg: 1;
    UCHAR       ucRever: 5;
    UCHAR    ucSessionStopInd;
    UCHAR     ucCbnCpyAckType:1;
    UCHAR      ucCongestionLevel:6;
    UCHAR      ucCongestionFlag:1;


    in6_addr     stNasIP;      /* NAS_IP_Address */
    UCHAR       ucNasIdentify[MAX_IDENTIFY_LEN]; /* NAS���豸�� */

    UCHAR       ucFrameProtocol;  /**/
    UCHAR       ucAccessType: 3;  /* �������� ACCESS_3GPP,ACCESS_3GPP2,ACCESS_BRAS */
    UCHAR       ucAcctAuthentic: 2; /*��ȫ��ʽ*/
    UCHAR       ucIsSecActivateFlg:2;          /* ���������Ƿ��Ƕ��μ��������ĵı�ʶ ,normal ��ʾ��һ�μ����ȱʡ��second��ʾ���λ�ר�г���*/
    UCHAR       ucPreCMFail      : 1;                  /* �Ƿ�CM�ڼ�������ʱʧ��  ����ά������ò��� ����ʱ���Ʒѷ��سɹ�����������ʧ��ɾ��ʱ֪ͨ�ƷѲ��������� */
    UCHAR      ucPdpType;  /* PDP����,ȡֵ�μ�gtp.h ,ע��GGSN��USM���ת��*/
    UCHAR      ucRatType;             /* ��������*/

    UCHAR      ucUgwRole;/*��Ԫ��ɫ*/
    UCHAR      ucEPSBearId;         /* EPS Bear ID, GGSNʹ�������������NSAPI���˴�ֻ����һ�������ĵ�ֵ*/
    USHORT usMSTimeZone;
    ULONG      ulFilterTableIndex;             /*����������������������n*/
    ULONG      ulGtpuIndex;             /*�·���ת�����gtpuindex*/
    RELTMR_T ulTimerId;              /* ��ʱ���¼�ID */
    RELTMR_T ulT3N3TimerId;              /* ��ʱ���¼�ID */
    UCHAR  ucCurrentBearerNum;         /* ��ǰ���صĸ���*/
    T3GPP_GGSN_MCC_MNC_S stMccMnc; /* ��GGSN,PGW,P+S HPLMN,����stImsi��HPLMNƥ�䵽��HPLMN�������SGW�ϣ����ֶα�ʾPGW��PLMN */
    T3GPP_SGSN_MCC_MNC_S stSgsnPlmn; /* �����SGW�����ֶα�ʾPGW��PLMN�������GGSN,PGW,PS�����ֶα�ʾ�Զ�SGW,SGSN��PLMN */
    GTP_QOS_S stNegQos;      /* ����Э�̵�QOS��Ϣ(Э) ,24�ֽ�*/
    ULONG ulSgsnAsn;         /* ASN���μƷ�,AMдCM��*/
    UCHAR   ucUserLocationInfo[8];

    ULONG  stSGSNIP;        /* �û�IP */
    ULONG  stGGSNIP;       /* �û�IP */
    ULONG  ulActiveTimeStamp; /*����ʱ���*/
    UCHAR  ucDpeId;                 /* DPE �߼�ID  */
    UCHAR  ucPccMode;
    UCHAR  ucRandomNo:3;           /* �������*/
    UCHAR  ucTriggerChangeFlag:1;
    UCHAR  ucReserved1:3;
    UCHAR  ucReserved2:1;

    UCHAR   ucSduVcpuId;   /* SDU �������ڵ�VCPU */

    ULONG   ulSlaveTimeStamp;
    ULONG  ulIdleTime;              /* ����ȷ�ϵĿ���������ʱ�� */

    UCHAR  ucUsername[MAXUSERNAMELEN];/*CM SM�Ʒ�ʹ��*/
    AM_CM_UPDATETYPE_S stUpdateType;   /* ��������*/
    UCHAR  ucChargingChar[2];    /* �Ʒ�����(Э) */
    USHORT usTokenId;     /* �����ĵ�TOKEN ID */

    ULONG ulCgAddr;               /* CG��ַ */

    /*========G��Ϣ��Я������Ԫ��ʾ=======*/
    UCHAR ucIMEISVOccur:1;
    UCHAR ucRatTypeOccur:1;
    UCHAR ucUserLocationInfoOccur:1;
    UCHAR ucMSTimeZoneOccur:1;
    UCHAR ucChargingCharOccur:1;
     /*========��Ϣ��Я������Ԫ��ʾ=======*/
    UCHAR ucSelectMode  : 3;
    UCHAR  ucRecordType:2;  /* �����ɼ����ͣ� 0: ͳ��3��4������ ,1:ͳ��7������*/
    UCHAR  ucChargeMode:2; /* �Ʒ����ԣ�0:���߼Ʒ� , 1:���߼Ʒ�*/
    UCHAR  ucChargePropertyFlag:2;  /*��ʶ���û��Ƿ����ݼƷ��û���0:��ͨ,1:���ݼƷ�(FBC CBB),2:PDP CBB.��0��û��userprofile��1��2������userprofile��*/
    UCHAR  ucAliasMarking:1;   /* Alias Markingʹ�ܱ�ʶ,0:δʹ��,1:ʹ�� */
    UCHAR  ucDDosFlag:1;        /* ��DDOS����ʹ��,0:δʹ��,1:ʹ�� */
    USHORT usUserProfileID;   /* ���û�ƥ���User Profile ID*/


    UCHAR   ucAAAUserProfileFlag:1; /*0��ʾuserprofile�Ǳ��ط��䣻1��ʾAAAָ��*/
    UCHAR   ucPerfForCmcc:1;           /*��ʶ�û��Ƿ����cmcc����ͳ�ƣ��ñ����ipn����am��Ҫ͸����pf*/
    UCHAR   ucPccL7ProcessFlag:2;
    UCHAR   ucPppFailReason:4;             /* �����ֶ� */
    UCHAR  ucBwmSubscriberEnable:2;  /* �û���BWM����ʹ�ܱ�־*/
    UCHAR  ucBwmGroupEnable:2;         /* �û��鼶BWM����ʹ�ܱ�־ */
    UCHAR  ucBwmGlobalEnable:2;        /* ȫ�ּ�BWM����ʹ�ܱ�־ */
    UCHAR  ucEMSstartmesgFlag:1;        /*EMS  ������Ϣ�жϱ�־λ*/
    UCHAR  ucGxRelType:1;

    USHORT usUserProfileGroupID;        /* ���û�ƥ���User Profile Group ID*/

    /* Cm ʹ�õ��ֶ� */
    ULONG ulCdrfChargingId;           /* CDRF�Ʒ�ID(Э) */
    ULONG ulRadiusIndex;               /* AAA�Ʒѵ�����*/
    //UCHAR ucGxRelType:1;
    UCHAR ucDelCause;                 /* ȥ��ԭ��ֵ*/
    UCHAR ucULIValid:1;                  /* ��ʾ�������е�ULI��Ϣ�Ϸ�CM��ʹ��*/
    UCHAR ucTimeZoneValid:1;        /* ��ʾ�������е�Timezone��Ϣ�Ϸ�CM��ʹ��*/
    UCHAR ucIsTftExist:1;     /* ���������Ƿ����TFT�ı�ʶ */
    UCHAR ucImsFlag:2;       /* ���������ͱ�־*/
    UCHAR ucSrvLevel:3;      /* ҵ�񼶱�*/
    UCHAR usAcctStopCause:4;     /* �Ʒѽ���ԭ��ֵ */
    UCHAR bit1OnlChrgEnabled:1;  /*1: online charging enabled; 0: online charging disabled*/
    UCHAR bit1OflChrgEnabled:1;   /*1: offline charging enabled; 0: offline charging disabled*/
    UCHAR ucOfflineBillAttrFlg:1;    /* TMO-Offline-Billing-Attr�Ƿ���Чֵ��0��ʾ��Ч��1��ʾ��Ч */
    UCHAR ucVogProfileChangeFlag      :1;/* ���͵�MSU��vog-profile�仯*/
    //UCHAR ucCMWaitAAAStatus     : 1;    //xuyaoqiang 2013513 for all in one
    UCHAR  ucAmRsv;   /*��������session�м���������ĵĸ���*/
    ULONG  ulpdpActForCmStampLow;/*�����ļ���ʱ���--��λ*/
    ULONG  ulpdpActForCmStampHig;/*�����ļ���ʱ���--��λ*/
    ULONG  ulpdpDelForCmStampLow;  /*������ȥ��ʱ���--��λ*/
    ULONG  ulpdpDelForCmStampHig;  /*������ȥ��ʱ���--��λ*/


    ULONG ulSessionIndex;   /* index of session cb*/
    ULONG ulBearerIndex;    /* index of bearer cb*/
    UCHAR ucPriOfcsIndex;   /* ��offline function(CG)������*/
    UCHAR ucSecOfcsIndex; /* ��offline function(CG)������*/
    USHORT usPcrfGrpIndex;


    UCHAR ucCcSelectMode;
    UCHAR ucApnLockDelUserFlag;   /* ��ʾ�Ƿ�lock enable deactive enableȥ����û�*/
    GTP_COMMON_FLAGS_S stCommonFlags;
    UCHAR ucRsv_1;    /* ��λ�ã�������Ǹ��û��Ƿ��յ���ȥ����Ϣ�� */
    USHORT     usApnIndex; /* �������Ķ�Ӧ��APN������ */
    UCHAR       ucMachineState;      /* һ��״̬ */
    UCHAR       ucMachineL2State;  /* ����״̬ */
    ULONG  ulDefaultGspuIndex;
    ULONG ulSgwLeftLocTeidc; /*��ʱ����*/
    ULONG ulS5_Gn_LocTeidc;
    ULONG ulSgwLeftPeerTeidu;
    ULONG ulS5_Gn_PeerTeidu;
    ULONG ulS5_Gn_PeerTeidc;
    UCHAR ucIPv4AllocType;      /* ��ַ���䷽ʽ����̬�����أ�RADIUS�� */
    UCHAR ucIPv6AllocType;      /* ��ַ���䷽ʽ����̬�����أ�RADIUS�� */
    UCHAR ucDtMode;
    UCHAR ucGtpVer;

    USHORT usTraceId;
    USHORT usAliaCdbIndex;           /* APN������CDB�е�index(0-999)*/
    GTP_QOS_S stReqQos;              /* �����QOS��Ϣ ,24�ֽ�*/
    USHORT usVirtualapnIndex;       /* ����APN����single APN*/
    UCHAR ucSgwListOfInterfaces;
    UCHAR ucPgwListOfInterfaces;
    UCHAR ucSgwIsTraceFlag:1;
    UCHAR ucPgwIsTraceFlag:1;
    UCHAR ucVirtualapnFlag :1;        /* �Ƿ�����APNӳ�䵽��ʵAPN*/
    UCHAR ucMainContextFlag : 1;   /* ���ֶν���ƽ��ʱʹ��,���ڱ�ʶ��ǰ�û����*/
    UCHAR ucRadiusDisablePcc :1;  /* ��ʶRADIUS�Ƿ��·�����PCC��־*/
    UCHAR ucUsrTypeFlg :2;            /* �û��������ͣ�����ɵ���ע���滻����*/
    UCHAR ucAAARspCCFlag:1;       /* ��ʹ��for Celcom Single APN��AAA���ص�CCֵ�Ƿ�Ϸ���1Ϊ�Ϸ� */
    UCHAR ucTimeQuotaType;      /* TMO-Offline-Billing-Attr������Time-Quota-Type��ֵ*/
    UCHAR ucChargingType;   /* AAA�������·���Billing-Type : 0=prepaid��1=post-paid��2=post-paid with credit control,
                                               3=prepaid with credit control��4=HLR, 5=wallet specific,
                                                6=wallet specific without credit control, 7=hot billing*/
    UCHAR ucHomeZoneId;           /* Home Zoneģ�鷵�ص�Home Zone������״̬ */
    ULONG ulBaseTimeInterval;    /* TMO-Offline-Billing-Attr������Base-Time-Interval��ֵ*/
    USHORT usPriFuncNameIdx;   /* TMO-Primary-Event-Charging-Function-Name���Զ�Ӧ��index��ȫf��ʾ��Ч */
    USHORT usSecFuncNameIdx;  /* TMO-Secondary-Event-Charging-Function-Name���Զ�Ӧ��index��ȫf��ʾ��Ч */
    ULONG ulVirtualGiId;            /* ���ڴ洢AAA���·���GiId*/

    AM_AUTH_TMO_TRIGGER_TYPE_S stTriggerType;  /* ��ӦAM_AUTH_TMO_TRIGGER_TYPE_S */
    UCHAR aucTransparentData[32]; /* TMO-Transparent-Data���ԣ����Ϊ8 */

    ULONG ulSgwLeftPeerSigIP;     /* ��Ԫ�н����������Զ�IP */
    ULONG ulSgwLeftLocSigIP;       /* ��౾������IP */
    ULONG ulSgwLeftPeerDataIP;  /* ���Զ�����IP */
    ULONG ulSgwLeftLocDataIP;    /* ��౾������IP */
    ULONG ulSgwLeftLocTeidu;      /* ��౾�����������ʶ */
    ULONG ulS5_Gn_PeerSigIP;    /* �Ҳ�Զ�����IP */
    ULONG ulS5_Gn_LocSigIP;      /* �Ҳ౾������IP */
    ULONG ulS5_Gn_PeerDataIP; /* �Ҳ�Զ�����IP */
    ULONG ulS5_Gn_LocDataIP;   /* �Ҳ౾������IP */
    ULONG ulS5_Gn_LocTeidu;      /* �Ҳ�Զ����������ʶ */

    GTP_ULI_S stULI;/* 20 */
    USHORT usExternalEvent; /* ԭʼ���� */
    UCHAR  bit1SgwOflChrgEnabled:1;
    UCHAR  ucHZUserFlag:1;   /* ��ʶ���û��Ƿ�ΪHome Zone�û���0:��Home Zone�û���1��Home Zone�û�*/
    UCHAR  ucHZApnFlag:1;    /* ��ʶ���û��Ƿ���Home Zone APN���0:��Home Zone APN��1��Home Zone APN*/
    UCHAR ucbit1TightInterwork:1; /* 0:�����  1:����� */
    UCHAR ucVirtualGiIdFlag:1;  /* ���ڱ��AAA�Ƿ�����GiId*/
    UCHAR ucMultiServiceFlg:1;     /* ��¼�Ƿ���Multi-Service�û� */
    UCHAR ucMultiContextFlg:1;    /* ��¼�Ƿ���Multi-Service������ */
    UCHAR ucRadiusServerFlag:1; /* ��ʶ�û��Ƿ�ʹ��radius����*/
    UCHAR ucLeftSigIfType;           /* ��������ӿ����� */


    APN_AMBR_S stApnAmbr;      /* Aggregate Maximum Bit Rate AMBR */
    APN_AMBR_S stOldApnAmbr;      /* Aggregate Maximum Bit Rate AMBR */
    UCHAR  ucIpv6PrefixLength; /* radius ���ص� IPV6 ǰ׺����*/
    UCHAR ucChargingCharInMsg[2];   /* ���ڴ洢SGSNЯ����CC��Ԫ��ֵ*/
    UCHAR ucPcrfLocalIndex;
    ULONG ulPdnConnectionId;            /* ���ڼ�¼ȱʡ���ص�ulCdrfChargingId */


    USHORT usNoConfigApnIndex;      /* SGWδ����APN��Index(1-3000)*/
    USHORT usServiceIndex;         /* ����service PDP,���浱ǰ�����service-index; ����default PDP,����multiple-apn��index */
    ULONG ulDefaultPDPIndex;     /* ��¼Default PDP�������������ü�¼ֻ��Multi-Service�û���Ч */

    /* �������*/

    /* SM��Ҫ���ֶ�*/
    ULONG  ulUsageRptCBIndex; /* Added by hourufeng for SM R8 ͬ��*/
    UCHAR  ucRightEncapType;    /* �Ҳ��װ����*/
    UCHAR  ucActionSupport:1;
    UCHAR  ucBit1OnlineCharGranFlag:1;
    UCHAR  ucHZErrorFlag:1;  /* ��ʶ���û����ӵ���HomeZone Server��ǰ�Ƿ�����������0:������1��HomeZone Server����Ӧ*/
    UCHAR  ucHZRspFlag:1;    /* �Ƿ��յ�HomeZone Server��Ӧ��Ϣ��־����ʼ��Ϊ0 0��û���յ� 1���յ�*/
    UCHAR  ucCoaNotifyUserProfileUpdated:1;  /* COA����UserProfile��־��1,��ʾCOA���¹�,������SGSN�ĸ���; 0,COAδ����,����SGSN���� */
    UCHAR  ucCoaQosChangedFlag:1;                /* 1,�����ı� 0,δ�����ı� */
    UCHAR  ucCoaUserProfileChangedFlag:1;    /* 1,�����ı� 0,δ�����ı� */
    UCHAR  ucPccRollBackFlag:1; /* PCRFC֪ͨAM PCC�ع�ʱ��AM�ø�λΪ1��IPNͨ���˱�־�ڱ������ع����������ֶ���PCRFC��AM�ظ�����Ӧ��revoke��Ϣʱ��λ*/
    UCHAR  ucBitCfFlag:1;            /* 1��ʾCF�û���0��ʾ����CF�û�*/
    UCHAR  ucPccIndicate:4;       /* Pcc Indicate Num, IPNд��AM�����·����ֶθ�PF  by penghui for 9.0 2011-2-6 */
    UCHAR  ucIsRTUser:1;          /* ����ʵʱ�û����*/
    UCHAR  ucRuleChangeFlag         :1;
    UCHAR  ucSAEmsFlag:1;       /*Gn��ά��SA���*/
    UCHAR  ucUserLevelServiceType;

    UCHAR ucMsisdnLen;                /* ����msisdn���� */
    UCHAR  ucGroupLevelServiceType;  /* ��¼�û��鼶��ҵ�����ͣ� tos /non-tos*/
    USHORT usCFTemplateID;
    USHORT usUserGroupID;      /* �û���ID��ͬʱҲ���û��鼶BWM_CB�����������*/
    USHORT usPolicyId;              /* SMʹ�õ�Policy Id*/



    unSession_Info  unSessionInfo;

    /*chenjinbo���*/
    ULONG       ulOutVPNIndex;      /* �û���Ӧ�ĳ��ӿ�*/
    ULONG       ulTimeStamp;          /* ��Ϣ�Դ����¼���*/
    ULONG       ulLastTimestamp;    /* ������һ����Ϣ���¼���*/
    ULONG       ulCurTimeStamp;
    UCHAR       ucL2Info[SCCG_MAX_L2_LEN];
    UCHAR       ucNsapi;        /* ���ֶ���ʱ��ʹ�� */
    UCHAR       ucACCIdentifier;
//  AM_SCCG_PF_CTRL_Info stPfCtrlInfo;
    /*chenjinbo��� end*/

    UCHAR      ucDTI : 1;
    UCHAR      ucIsActByTauOrHo : 1;    /* �������ı�����������TAU��HANDOVER��־,�븽������  */
    UCHAR      ucAdcFlag           :1;/*ADC�û�����*/
    UCHAR      ucAdcRuleFlag       :1;/*�Ƿ���ADC����*/
    UCHAR      ucAdcChangeFlag       :1;/*ADC�Ƿ����*/
    UCHAR      ucBrasUserType:3;
    UCHAR      uceQci; /*���ڱ���PCRFC�·�����չQci,��仰��ʹ��*/


    USHORT usFramedRouteCount;
    USHORT usMMECsId;
    ULONG  ulSGWNodeId;
    ULONG  ulSGWFqCsidIndex;
    ULONG  ulPGWNodeId;
    ULONG  ulPGWFqCsidIndex;
    ULONG  pstMMEFqCsidNext;
    ULONG  ulMMEFqCsidIndex;
    ULONG  ulMMENodeId;
    USHORT usSGWCsId;
    USHORT usPGWCsId;
    UCHAR  ucL2TPFlag;
    UCHAR ucUpAmbrCarFlag  : 2;            /* ���ڱ�ʶȱʡ�����Ƿ�ʹ��������AMBR CAR����,�Ա�ר�г��ؾݴ��ж��Ƿ���ҪCAR���� */
    UCHAR ucDownAmbrCarFlag  : 2;          /* ���ڱ�ʶȱʡ�����Ƿ�ʹ��������AMBR CAR����,�Ա�ר�г��ؾݴ��ж��Ƿ���ҪCAR���� */
    UCHAR  ucProcFail     : 1;                      /* ���̴���ʧ�ܱ�ǡ����ڼ��з���Ϣ */
    UCHAR  ucBitPcrfCarryCfFlag : 1;
    UCHAR  ucBitPcrfCfFlag : 1;
    UCHAR  ucSdbReserved : 1;
    UCHAR  ucDhcpIPV6Flg;
    UCHAR  ucLeftEncapType;


    USHORT usFirstFramedRouteIndex;
    USHORT usRightSigPathId;
    UCHAR  ucBackupType:8;
    UCHAR ucOldUpBandFlag   : 4;
    UCHAR ucOldDownBandFlag : 4;
    UCHAR ucMultiAddressInherit:1;
    UCHAR ucSlavePdpFlag:1;
    UCHAR ucNotifyPcrfcFlag:2;
    UCHAR ucActDedBearerNum:4;
    UCHAR ucUserPerfFlag  :2;    /*�û����Ƿ�����ı��,0,δ����;1,�Ѽ���;2,���ü���*/
    UCHAR  ucPdnConnectPerfFlag:2;
    UCHAR ucDropEmsFlag:1; /*������ά���Ƿ�ʼ�ı��*/
    UCHAR ucImsiInvalidFlag : 1;       /*��ʶ��ǰ�û��Ƿ���ڿ��õ�IMSI;0:��ǰ�û�IMSI����;1:��ǰ�û�IMSI������*/
    UCHAR ucBearerPerfFlag  :1;    /*context �Ƿ�����ı��,0,δ����;1,�Ѽ���;*/
    UCHAR  ucSlaveSessionTimeOutFlg:1;  /* �������SESSION TIMEOUT��ʱ���¼��־��ƽ��ʱɾ�����������嶪ʧ���ݵ����û����� */
    //14
    UCHAR  ucAddrAllocDhcpsFlag:1;
    UCHAR ucLiFlag          : 1;
    UCHAR ucOcscForceDropFlag  : 1; /*tianshuang for CR20120301017*/
    UCHAR ucMSRarUpdBakFlag:1;
    UCHAR bit1MsuFlag:1;
    UCHAR ucSmoothFailFlag:3;
    UCHAR ucTempTftOperCode:3 ;
    UCHAR ucBufferOperCode:2;
    UCHAR ucNotifyDelGi: 1;
    UCHAR  ucPmipLifeTimeOP:2;
    UCHAR ucRspHZSameMsgNum;            /* ��ʾ�յ�HZģ����ͬ��״̬֪ͨ��Ϣ���� */
    UCHAR ucPcrfcDelCause;
    USHORT usPmipLifetime;
    USHORT usTempFilterOperIndic;
    ULONG  ulIndirectForwardLocTeidu;
    ULONG  ulResource;
    ULONG  ulSessionTimeout;
    USHORT usIPv4VpnId;
    USHORT usIPv6VpnId;
    USHORT usLeftDataPathId;
    USHORT usLeftSigPathId;
    USHORT usRightDataPathId;
    USHORT usLeftRecovery;
    USHORT usS5_Gn_PeerSigPort;
    USHORT usS5_Gn_LocSigPort;
    USHORT usSgwLeftPeerSigPort;
    USHORT usSgwLeftLocSigPort;
    ULONG ulIndirectForwardPeerULTeidu;                /* ���м��ת���Զ��������������ʶ */
    ULONG ulSgwLeftPeerTeidc;          /* ���Զ����������ʶ */

    USHORT ulControlBlockIndex;
    UCHAR ucLeftDataIfType;         /* ���������ӿ����� */
    UCHAR ucRightDataIfType;        /* �Ҳ�������ӿ����� */
    UCHAR ucIndirectForwardInputInterfaceType;      /* ���ת����ӿ����� */
    UCHAR ucIndirectForwardOutputInterfaceType;     /* ���ת�����ӿ����� */
    UCHAR ucIndirectForwardInputEncapType;          /* ���ת�����װ���� */
    UCHAR ucIndirectForwardOutputEncapType;         /* ���ת������װ���� */

    ULONG ulUpInterfaceIndex;      /* ���нӿ�Subindex*/
    ULONG ulDnInterfaceIndex;      /* ���нӿ�Subindex*/
    ULONG ulIndirectFwdIndex;      /* ת��ģʽ�Ľӿ�Subindex*/
    ULONG ulIndirectForwardPeerULDataIP;               /* ���м��ת���Զ�����IP */
    ULONG ulIndirectForwardPeerTeidu;                /* ���м��ת���Զ����������ʶ */
    ULONG ulIndirectForwardPeerDataIP;               /* ���м��ת���Զ�����IP */
    //34
    USHORT usCfProfileListId[MAX_CFPROFILES_FROM_ONE_GX_MESSAGE];  /*���cf-profile id������*/
    UCHAR  ucCfProfileListNum;              /*cf-profile�ĸ���*/
    UCHAR  ucAccMsgType;
    USHORT usCoaPort;
    UCHAR ucSendCoaReqN3Times;
    UCHAR ucIdentifier;
    ULONG ulPdpIndex;  /*��ת��ͷ�л�ȡ������TB,TP*/
    UCHAR ucRoleChanged;          /* �жϽ�ɫ�Ƿ������仯 */
    UCHAR ucIdlePagingIndication;        /* ��ʶidlePaging����,�±���ʱ,��Ҫ���ݸ�ָʾ,����idlePaging��ر�ʶ */
    UCHAR ucPppFlag         : 4;                      /* ����ppp��־ */
    UCHAR ucLocCOAFlag     : 1;                      /* ����ppp��־ */
    UCHAR ucBitRatChangeTriggerFlag:1;
    UCHAR ucBitCongestionRptFlag:1;
    UCHAR ucNewRaiChangeFlag :1;
    UCHAR ucPcscfMainIpv4   :4;
    UCHAR ucPcscfMainIpv6   :4;
    UCHAR ucPcscfBkpIpv4   :4;
    UCHAR ucPcscfBkpIpv6   :4;
    SCCG_LICENSETYPE_S ucLicneseType;
    UCHAR ucCiifFlag:2;
    UCHAR ucSendPodMsgTimes:6;
    GTP_EVOLVED_ARP stEvolvedARP;  /*1�ֽ�*/
    USHORT usPcscfGrpoupIndex;
    USHORT usPcscfGrpoupIndexV6;


    /*  */
    ULONG ulPcrfcTransID;
    ULONG ulPcrfcTransIDRSV;
    ULONG ulGtpv2Scene;
    ULONG ulLeftIpAddr;
    //60
    //USHORT usMSProfilelistIndex;  /*���ڼ�¼��̬���ԣ�����������Ƿ����ж�Ϊ��MSD�û�, �˱����IPN�޸ģ�AM���� AM�����޸�bit1MsdFlag ���*/
    USHORT usNasSigPort;
    UCHAR ucAuthenticator[16];
    ULONG ulRadiusServerIP;
    UCHAR ucTetheringFlag;
    //UCHAR ucMseProfileListOper;
    UCHAR ucMsdLogicalSlotId;     /*MSD���slot*/

    UCHAR ucMsdOSId;                  /*MSD���OS*/
    UCHAR ucSGType;
    UCHAR ucMsdSgId;                   /*MSD���SG*/
    UCHAR ucLocalLocationReportFlag;
    UCHAR ucBitRaiTriggerFlag :1;
    UCHAR ucClearFlg   :1;
    UCHAR ucBitTaiTriggerFlag :1;
    UCHAR ucBitEcgiTriggerFlag :1;
    UCHAR ucBitUliTriggerFlag :1;
    UCHAR bit1MsdFlag :1;  /*�Ƿ���MSD�û�, �ñ����MSD������ЧSG����Ϣʱ��λ*/
    UCHAR bit1MSDFlagc:1;           /*�Ƿ����ڽ�������ע��*/
    /*SPU��MSD-SDU������Ϣ���¼�ѷ�������Ϣ��ǣ������յ�MSD���ص���Ӧ��Ϣ������˱��.
       ���SPU��û���ͼ������󣬾��յ�MS����Ӧ��Ϣ����ֱ�Ӷ�������Ϣ��*/
    UCHAR bit1SendReqFlag:1;
    UCHAR aucUliInfo[MAX_CONGESTION_RPT_ULI_LEN];
    UCHAR ucL2InfoLen;
    UCHAR ucContChargingAdded:1;
    UCHAR ucIpv6Added:1;
    UCHAR ucIpv6ChargingAdded:1;
    UCHAR ucIpv4v6Added:1;
    UCHAR ucBit2SelectType:2;
    UCHAR ucSendCreatHashFlag:2 ;  /* �Ƿ���Ҫ֪ͨSD��SDU�ؽ����� */
    UCHAR ucMseDataTrcUpFlag         :1;
    UCHAR ucMseDataTrcDownFlag       :1;
    UCHAR ucMseDropEmsFlag           :1;
    UCHAR ucbit1VogEmsFlag:1;
    UCHAR ucBit4Reserved:4;
}SDB_SCCG_CONTEXT_S,SDB_GSPU_CONTEXT_S;
#endif

//
//license define
//
typedef struct tagGTP_LICENSETYPE_S
{
    UCHAR  ucContextBaseBill:1;  /*�Ƿ�Ϊ���ݼƷ�*/
    UCHAR  ucCamel3Prepay:1;  /*�Ƿ�Ϊcamel3 Ԥ����*/
    UCHAR  ucHotBilling:1;  /*�Ƿ�Ϊhit billing */
    UCHAR  ucL2tpFlag:1;    /*�Ƿ�Ϊl2tp*/
    UCHAR  ucIpV6Flag:1;   /*�Ƿ�ΪIPV6*/
    UCHAR  ucIpV4V6Flag:1;   /*�Ƿ�ΪIPv4V6*/
    UCHAR  ucPccLicenseFlag:1;    /*�Ƿ�ΪPCC�û�����*/
    /* Add begin by wangyuting 42209 at 2009-09-23 V9R8C00 for HomeZone */
    UCHAR  ucHomeZoneLicenseFlag:1;    /*�Ƿ�ΪHZ�û�����*/
    /* Add end by wangyuting 42209 at 2009-09-23 V9R8C00 for HomeZone */
    /* Add begin by wangyuting 42209 at 2009-11-6 V9R8C00 for routing behind ms */
    UCHAR  ucRoutingBehindMsFlag:1;  /*�Ƿ�Ϊrouting behind ms�û�*/
    /* Add end by wangyuting 42209 at 2009-11-6 V9R8C00 for routing behind ms */
    /*Wangyuting modified begin for Routing behind ms,2009-11-18*/
    UCHAR   ucRadiusFlag:1;/*�Ƿ�Ϊradius�����û�*/
    UCHAR ucQchatLicenseFlag:1;    /*�Ƿ�ΪQchat�û�����*/
    //UCHAR ucReserve:6;
    UCHAR ucMultiServLicenseFlag:1;    /*�Ƿ�ΪMulti Service�û�����*/
    UCHAR  ucOnlineChargeFlag:1;/*�Ƿ�Ϊ���߼Ʒ��û�*/
    /* Modified start at 2012-3-6 by yuanhao for �������μ���License���� */
    UCHAR ucNetSecActFlag:1;   /* �Ƿ��������μ��ֻ�������ں����ص�Gn/Gp SGSN���� */
    /* Modified start at 2012-3-6 by yuanhao for �������μ���License���� */

    /*add start by tianshuang for DHCP-IPV6 2012-07-10*/
    UCHAR ucDhcpv6Flg:1;
    /*add end by tianshuang for DHCP-IPV6 2012-07-10*/
    UCHAR ucPdv6flag:1;
    ULONG ucAdcAdd: 1;    /* 1,���ӹ�ADC��licenseͳ�� 0��û�����ӹ�ADC��licenseͳ��*/
    UCHAR reserv:7;
    UCHAR reserv1;
}VOS_PACKED GTP_LICENSETYPE_S;

//
//gtpv2 indication define
//

//from beijing UGW---
typedef struct tagAM_GTPV2_INDICATION_S
{
#if (UGW_BYTE_ORDER == UGW_BIG_ENDIAN)
    VOS_UINT8 btDAF:1;
    VOS_UINT8 btDTF:1;
    VOS_UINT8 btHI:1;
    VOS_UINT8 btDFI:1;
    VOS_UINT8 btOI:1;
    VOS_UINT8 btISRSI:1;
    VOS_UINT8 btISRAI:1;
    VOS_UINT8 btSGWCI:1;
    VOS_UINT8 btReserved:1;
    VOS_UINT8 btUIMSI:1;
    VOS_UINT8 btCFSI:1;
    VOS_UINT8 btCRSI:1;
    VOS_UINT8 btP:1;
    VOS_UINT8 btPT:1;
    VOS_UINT8 btSI:1;
    VOS_UINT8 btMSV:1;
    VOS_UINT8 btRetLoc:1;       /*add by tianshuang 20101108 for ims location report*/
    VOS_UINT8 btReserved1:2;
    VOS_UINT8 btS6AF:1;
    VOS_UINT8 btS4AF:1;
    VOS_UINT8 btReserved2:1;
    VOS_UINT8 btISRAU:1;
    VOS_UINT8 btCCRSI:1;
    VOS_UINT8 ucLen;

#else
    VOS_UINT8 btSGWCI:1;
    VOS_UINT8 btISRAI:1;
    VOS_UINT8 btISRSI:1;
    VOS_UINT8 btOI:1;
    VOS_UINT8 btDFI:1;
    VOS_UINT8 btHI:1;
    VOS_UINT8 btDTF:1;
    VOS_UINT8 btDAF:1;
    VOS_UINT8 btMSV:1;
    VOS_UINT8 btSI:1;
    VOS_UINT8 btPT:1;
    VOS_UINT8 btP:1;
    VOS_UINT8 btCRSI:1;
    VOS_UINT8 btCFSI:1;
    VOS_UINT8 btUIMSI:1;
    VOS_UINT8 btReserved:1;
    VOS_UINT8 btCCRSI:1;
    VOS_UINT8 btISRAU:1;
    VOS_UINT8 btReserved2:1;
    VOS_UINT8 btS4AF:1;
    VOS_UINT8 btS6AF:1;
    VOS_UINT8 btReserved1:2;
    VOS_UINT8 btRetLoc:1;   /*add by tianshuang 20101108 for ims location report*/
    VOS_UINT8 ucLen;
#endif
} VOS_PACKED AM_GTPV2_INDICATION_S;

#define M_MAX_BEARER_NUM        11

/*BSSID���ֺ�stPmipv6LeftPeerAddr����(���ֶ�ֻ��pmip�û�ʹ��,��s2a���뻥��,���Թ���)*/
typedef struct tagGTP_TWAN_ID_BSSID_S
{
#if (UGW_BYTE_ORDER == UGW_BIG_ENDIAN)
    UCHAR btBSSID:1;       /*BSSID �Ƿ���Ч��־λ*/
    UCHAR btReserved:7;
#else
    UCHAR btReserved:7;
    UCHAR btBSSID:1;       /*BSSID �Ƿ���Ч��־λ*/
#endif
    UCHAR aucBSSID[M_TWANID_BSSID_LEN];
}VOS_PACKED GTP_TWAN_ID_BSSID_S;

/*pmip�Զ�V6��ַ��twanid�е�bssid��������*/
typedef union unGTP_PMIPV6PEERADDR_BSSID
{
    in6_addr stPmipv6LeftPeerAddr;     /* 16�ֽ� */
    GTP_TWAN_ID_BSSID_S stBSSID;       /* 7�ֽ� */
} VOS_PACKED unGTP_PMIPV6PEERADDR_BSSID;

typedef struct tagGTP_PMIPV6PEERADDR_BSSID
{
    unGTP_PMIPV6PEERADDR_BSSID unPmipV6addrOrBSSID;    /*16*/
} VOS_PACKED GTP_PMIPV6PEERADDR_BSSID;

//
//sdb data struct define
//


typedef struct tagSDB_GSPU_CONTEXT_S
{
    /**********************�������***************************/
    ULONG ucBackupType: 8;    /* ������� */
    ULONG ulBackupNext : 24;  /* ������� */
    ULONG ucBackupFlag: 1;    /* ������� */
    ULONG ucNotifyDelGi: 1;
    ULONG ucBatchNotActive: 1;/* ������ʱ�򣬴��ڸ���״̬���û� */
    ULONG ucQosRleaseFlag: 1; /* SGW�ı������л�ʧ�� �ͷű�ʶ */
    ULONG ucEarpChangeForMsgProc: 1;
    ULONG ucSgsnReqMsgWithEarp: 1;
    ULONG ucCpuxDeleteFlag: 1;
    ULONG ucCarType: 1;
    ULONG ulBackupPre : 24;   /* ������� */
    ULONG ulGspuBdIndex;      /* �ü�¼��SC��PDP Context�������� */
    ULONG ulDefaultGspuIndex; /* ר�г�������Ӧ��ȱʡ���ص�gspu index�����ڸ���ר�г��ط���ȱʡ���أ�ȱʡ���ظ��ֶ�Ϊȫf*/

    /**************** ָ���ֶ�ͳһ������ǰ�� *********************/
    AM_IPN_MSE_PROFILE_INFO_S *pstMseProfileInfo;
    GTP_IE_PROTO_CONF_OPT_S * pstPCO; /* Protocol Configuration Option(Э) */
    GTP_IE_PCO_PARSE_S * pstPCOParse; /* PCO�����������*/
    AM_GTPV2_TRACE_INFO_S *pstTraceInfo;/*UGW 1.1:Trace info�ݴ�ָ�룬������Ϣ��ָ���ͷ�*/
    UCHAR* pucAAANegoRspMsg;          /* AAA��Ȩ��Ӧ��Ϣָ��Session��idleʱ������������*/
    SDB_L2TP_INFO_S * pstL2TPInfo;
    S_GTPV2_PAA *pstGTPV2PAA;
    VOID *pstMMEFqCsidNext;           /* MME FQ-CSID�����е���һ����� */
    VOID *pstSGWFqCsidNext;           /* SGW FQ-CSID�����е���һ����� */
    VOID *pstPGWFqCsidNext;           /* PGW FQ-CSID�����е���һ����� */
    SDB_TFT_S* pstTft;
    SDB_WITHDRAW_DATA_S *pstWithdrawData;
    GTP_QOS_S *pstOriginalNegoQos;
    MEDIA_DETECT_S * pstMediaDetectElement;
    GTP_SAE_QOS_S *pstOriginalUEReqQos; /*���ڼ�¼UE�������qos��Ϣ������ۼӵĽ��*/
    AAA_Service_List *pstServiceList; /* Servic-Listָ�� */
    UCHAR *pstPrcfUpdateMsg;          /* ����PCRFC RAR������Ϣ */
    UGW_TFT_QOS_UPDATE_BAKUP_S *pstQosRollBack;     /* �û�ȱʡ���ص�QOS���� */
    UCHAR* pucLapRspMsg;              /* ����DHCPV6��Ϣ��Lap��Ӧ��Ϣ���ڴ˴� */

    RELTMR_T ulTimerId;               /* ��ʱ���¼�ID */
    RELTMR_T ulBearCmdTimerId;        /* ��ʱ���¼�ID */

    GTP_IMSI_S stImsi;                /* �û�IMSI��Ϣ(Э) ��8�ֽ� */
    GTP_IMEI_S stIMEI;                /* 8�ֽ� */
    GTP_MSISDN szMsisdn;              /* �û�MSISDN��Ϣ(Э)��8�ֽ� */
    ULONG ulSgwLeftLocTeidc;          /* ��౾�����������ʶ */
    ULONG ulS5_Gn_LocTeidc;           /* �Ҳ౾�����������ʶ */
    ULONG ulSgwLeftPeerTeidu;         /* ���Զ����������ʶ */
    ULONG ulS5_Gn_PeerTeidu;          /* �Ҳ౾�����������ʶ */
    ULONG ulS5_Gn_PeerTeidc;          /* �Ҳ�Զ����������ʶ */
    ULONG ulIPv4Addr;                 /* GGSNʹ����������ֻ���ַ */
    in6_addr stIPv6Addr;

    /******************************************************************************************************/
    /* ��Ҫ��������ֶ��Ѿ���֤4/8�ֽڶ��룻�޸�ʱ��Ҫע��ͬ���޸������ֵ�sdbdatarecord.c��sdbproduct.h */
    /******************************************************************************************************/

    USHORT usVpnId;            /* IPV4 VPN ID */
    USHORT usIpv6VpnId;        /* IPV6 VPN ID */

    UCHAR ucPdpType;           /* PDP����,ȡֵ�μ�gtp.h ,ע��GGSN��USM���ת�� */
    UCHAR ucRatType;           /* �������� */
    USHORT usApnIndex;         /* �������Ķ�Ӧ��APN������(Э) */

    UCHAR ucIPv4AllocType;     /* ��ַ���䷽ʽ����̬�����أ�RADIUS�� */
    UCHAR ucIPv6AllocType;     /* ��ַ���䷽ʽ����̬�����أ�RADIUS�� */
    UCHAR ucDpeId;             /* DPE �߼�ID  */
    UCHAR ucRspCause;          /* �û����Ӧ����Ϣ��ӦЯ����ԭ��ֵ */

    ULONG ulFilterTableIndex;  /* ����������������������n*/
    ULONG ulActiveTimeStamp;   /* ����ʱ��� */
    ULONG ulSessionTimeout;    /* Session ��ʱʱ�䳤 */

    UCHAR ucMachineState;      /* GTPV2 һ��״̬ */
    UCHAR ucMachineL2State;    /* GTPV2 ����״̬ */
    UCHAR ucRoleChanged;       /* �жϽ�ɫ�Ƿ������仯 */
    UCHAR ucIpResourceFlag: 1; /* 1��ʾռ�ã�0��ʾδռ�� */
    UCHAR ucNotifyPeerDel : 1;
    UCHAR ucOldUsrTypeFlg : 2;
    UCHAR ucTimezoneFlagForS1Handover: 1;   /* �л�����һ������S1 Handover����Ҫ��ʱ�洢ʱ���Ƿ�ı����Ϣ for BI8D02475 */
    UCHAR ucGtpuExtendFlag: 1;   /* ���ڸ�PF�·�GTP-U��װ��ʶ*/
    UCHAR ucLeftNoCrsiFlag: 1;   /* ����BRC��Ϣ��ֻ��trigger�仯��crsi��֧��ʱ�������ز���update��Ϣ*/
    UCHAR ucCrsiChangeFlag: 1;   /* �洢CRSI��־�Ƿ���֮ǰ�����˱仯 */

    UCHAR ucChargingChar[2];     /* �Ʒ�����(Э) */
    UCHAR ucSelectMode  : 3;     /* APNѡ��ģʽ(Э)��ȡֵ�μ�����ĺ� */
    UCHAR ucUEInitProc  : 1;     /* ��UE�����Ĵ���Wangyuting add for BI8D00507,2009-5-4*/
    UCHAR ucDTI : 1;             /* ������Ϣ��Direct Tunnel Flag��Ԫ��DTI��־λ,0��ʾ2Tunnel,1��ʾ1Tunnel */
    UCHAR ucChargeOnlineFlag : 1;
    UCHAR ucChargeOfflineFlag : 1;
    UCHAR ucAmbrChangeFlag : 1;  /* �ж�AMBR�Ƿ������仯 */

    UCHAR ucGtpVer      : 2;     /* �汾��Ϣ(Э)��ȡֵ�μ�gtp.h */
    UCHAR usAcctStopCause   : 4; /* �Ʒѽ���ԭ��ֵ */
    UCHAR ucIsActByTauOrHo : 1;  /* �������ı�����������TAU��HANDOVER��־,�븽������  */
    UCHAR ucGetIpFromDhcps : 1;

    USHORT usLocSigFlowLbl;      /* ����(GGSN)����GTP-Flow��ʶ(Э) ��ֻ��v0ʹ��*/
    USHORT usLocDataFlowLbl;     /* ��������GTP-Flow��ʶ ֻ��v0ʹ��*/
    USHORT usPeerSigFlowLbl;     /* �Զ�(SGSN)����GTP-Flow��ʶ ֻ��v0ʹ��*/
    USHORT usPeerDataFlowLbl;    /* �Զ�����GTP-Flow��ʶ ֻ��v0ʹ��*/

    USHORT usMSTimeZone;
    USHORT usLeftRecovery;
    USHORT usRightRecovery;
    UCHAR ucMsdMseCompInstanceID;
    UCHAR ucChrPTI;

    GTP_ADDITIONALTRACEINFO_S stAdditionalTraceInfo;     /*������Ϣ,8�ֽ�*/

    USHORT usTraceId;
    UCHAR ucSgwListOfInterfaces;
    UCHAR ucPgwListOfInterfaces;

    ULONG ulGtpuIndex;                /*�·���ת�����gtpuindex*/
    ULONG ulSlaveTimeStamp;
    ULONG pathallowsn : 2;            /*��Ϣ��ͻ�����������ж��Ƿ���path�����sn,�����ڷ���Ϣʱ���*/
    ULONG ulPathSn: 16;
    ULONG ulNotifyPcrfChangeULI:1;
    ULONG ucPcoDir :1;    /*�����ϱ�pco���� VOS_TURE����NET-UE;VOS_FALSE����UE-NET*/
    ULONG ulUserTrafficPerf:4;        /*�û�TrafficClass��Դλ��*/
    ULONG ulDiffUserPriPerFlag : 2;   /*�����ֶ���δʹ��*/
    ULONG ulDiffServicePriPerFlag : 3;/*�����ֶ���δʹ��*/
    ULONG ulUserPriPerfFlag  : 3;     /*�û����ȼ�����ͳ����Դλ*/

    /*========AMר������==============*/
    UCHAR ucIsSecActivateFlg  : 2;         /* ���������Ƿ��Ƕ��μ��������ĵı�ʶ ,normal ��ʾ��һ�μ����ȱʡ��second��ʾ���λ�ר�г���*/
    UCHAR ucPreCMFail         : 1;         /* �Ƿ�CM�ڼ�������ʱʧ��*/
    UCHAR ucPreCMFailSendFlag : 1;         /* ��һ�ν��յ�����Ϣ����  */
    UCHAR ucSmResourceAdd     : 1;         /* ��Ƿ�������Ϣ����SM Wangboyu:�ñ�־λ��1��ʾ��Ҫ֪ͨIPN�ͷ���Դ���ͷ���Դ�ļ���Ϊ�û����𣬷���ᵼ��user-profileɾ������ */
    UCHAR ucRepeatFlag        : 1;         /* ������ʹ��,�����ظ�������ж�,�����ɾ��Gi��*/
    UCHAR ucIsMnrg            : 1;         /* ��SGSN���͵���Ӧ��Ϣ���Ƿ�Я��������TEID ��   ���μ���Ͳ���Я����ȥ*/
    UCHAR ucIsReactiveFlg     : 1;         /* �ж��Ƿ�Ϊ�ظ��������� 0 �� �ǣ�1���ظ������� */
    UCHAR ucPrevMsgType;                   /* ��һ�ν��յ�����Ϣ����  */
    UCHAR ucVirtualApnMapCounter : 2;      /* ������¼����apnӳ���������������ӳ�����ͣ��������*/
    UCHAR ucApnRestricFlag       : 1;      /* apn-restriction */
    UCHAR ucGxRelType            : 1;
    UCHAR Conflict               : 2;      /* ��Ϣ��ͻʱ�������ս���Ϣ */
    UCHAR ucIPReleaseFlag        : 1;      /* ����ǰ�յ���ַ�ͷ���Ϣ */
    UCHAR ucFilterTableIndexReleaseFlag:1; /* add by mayouwei 20090407 for c01 B037 ��ַй©*/
    UCHAR ucUgwRole;                       /* �����UGW_NET_ELEMENT_ROLE_E */
    UCHAR ucHplmnIndex;                    /* ����HPLMN INDEX���û�����ʱ���棬���κ�ר�������ļ̳и��ֶ� */
    T3GPP_GGSN_MCC_MNC_S stMccMnc;         /* 3�ֽ� ��GGSN,PGW,P+S HPLMN,����stImsi��HPLMNƥ�䵽��HPLMN�������SGW�ϣ����ֶα�ʾPGW��PLMN */

    UCHAR ucUsername[MAXUSERNAMELEN];      /* 64 CM SM�Ʒ�ʹ�� */

    /*========AM�������̱�ʾ=======*/
    UCHAR ucSgwIsTraceFlag     : 1;
    UCHAR ucPgwIsTraceFlag     : 1;
    UCHAR ucSendTraceInfoToPgw : 1;
    UCHAR ucArpChanged         : 1;        /* ���ڼ�¼�������е�ARP�Ƿ�仯 */
    UCHAR ucSendDDNFlag        : 1;        /* ��¼UE�Ƿ񷢹�DDN��Ϣ:0:û�з���DDN;1:�Ѿ�����DDN*/
    UCHAR ucUsrInforTime       : 3;        /* PPP�·��������� */

    UCHAR ucNoGiTableFlag    : 1;          /* �Ƿ��·�Gi����ı��PPPЭ�̵�ʱ�����·�Gi�� */
    UCHAR ucVerChange        : 2;          /* 0:V0 ,1:V1,2 V0->V1 3 V1-<V0 ��GGSNר�ã��漰�������·����֣���Ҫ�޸�*/
    UCHAR ucaddAllocType     : 1;          /* IPV4,��ʶ�Ƿ����AAA���ص�ַ 0:��ʾû�в���AAA���ص�ַ��1��ʾ����AAA���ص�ַ*/
    UCHAR ucIPV6addAllocType : 1;          /* ��ʶ�Ƿ�ʹ��aaa���ص�IPV6��ַ��0��ʾ��ʹ�ã�1��ʾʹ��*/
    UCHAR ucCfPerfFlg        : 1;          /* cf�û�����ͳ�Ʊ�ʾ��ͳ����ipn��am����ͳ�ƣ�Ϊ���⵹���ڼ���ɾ������˱��*/
    UCHAR ucStaticIpRouteType: 2;          /* route�·�����:0 ALL,1 HLR,2 RADIUS,3 DISABLE*/

    USHORT usAliaCdbIndex;                 /* APN������CDB�е�index(0-999)*/
    T3GPP_SGSN_MCC_MNC_S stSgsnPlmn;       /* 4�ֽ� �����SGW�����ֶα�ʾPGW��PLMN�������GGSN,PGW,PS�����ֶα�ʾ�Զ�SGW,SGSN��PLMN */

    /*========AM�������̱�ʾ=======*/

    GTP_QOS_S stReqQos;                    /* �����QOS��Ϣ ,24�ֽ�*/
    GTP_QOS_S stNegQos;                    /* ����Э�̵�QOS��Ϣ(Э) ,24�ֽ� */
    GTP_QOS_NECESSARY_S stOldQos;          /* 20�ֽڣ�����ʹ�ã����浱ǰ�Ѿ���ʹ�õ�Qos �ı������*/
    USHORT usVirtualapnIndex;              /* ����APN����single APN */
    UCHAR ucAuthCounter   : 3;             /* ������¼�û���Ȩ���� */
    UCHAR ucVirtualapnFlag :1;             /* �Ƿ�����APNӳ�䵽��ʵAPN */
    UCHAR ucIdleTimerOutFlag :1;           /* �Ƿ�idle ��ʱ */
    UCHAR ucAntiSpoofingDelFlag:1;         /* ���������Ѿ����͹�ȥ������ */
    UCHAR ucMainContextFlag : 1;           /* ���ֶν���ƽ��ʱʹ��,���ڱ�ʶ��ǰ�û����*/
    UCHAR ucAddrAllocDhcpsFlag:1;          /* �Ƿ�dhcp ��ʽ�����ַ��UGWר��*/

    UCHAR ucDelCause;


    /*�ֱ��������棨����ʱ��������ԭ���������д���ֱ�ռ�ñ��*/
    UCHAR ucUpBandFlag      : 4;
    UCHAR ucDownBandFlag    : 4;

    UCHAR ucOldUpBandFlag   : 4;
    UCHAR ucOldDownBandFlag : 4;

    UCHAR ucULIValid        : 1; /* ��ʾ�������е�ULI��Ϣ�Ϸ�CM��ʹ��*/
    UCHAR ucTimeZoneValid   : 1; /* ��ʾ�������е�Timezone��Ϣ�Ϸ�CM��ʹ��*/
    UCHAR ucNegoUsrPriResv  : 1;
    /* Added start by jiexianzhu at 2013.12.16 for ����ӳ�� VLRID/GT */
    UCHAR ucTransparentFromRadiusFlag : 1; /* ��� aucTransparentData �����ݼ���ʱ��radius��ȡ(1),�ӱ������û�ȡ(0) */
    /* Added end by jiexianzhu at 2013.12.16 for ����ӳ�� VLRID/GT */
    UCHAR ucGateWayProxyFlag : 1;      /* Proxy �����ı��*/
    UCHAR ucProxyWaitResponseFlag : 1;  /* Proxy �����ĵȴ���Ӧ��Ϣ���*/
    UCHAR ucRedundancyV4Flag: 1;
    UCHAR ucRedundancyV6Flag: 1;

    UCHAR ucOldUsrPri   : 3;     /* �����û����ڼ���ɹ����ֵ����Ҫ����QOS����ʱ���µ�����QOS���жԱ�*/
    UCHAR ucOldSrvLevel : 5;

    ULONG ulWaitCmTimeStamp;     /* ��¼ɾ�������еȴ�cm��Ӧʱ��� */

    /* ���ӿ�������IP�����û��������У�Ϊ��ʵ��N+1�Ŀ�ת*/
    ULONG ulUpInterfaceIndex;    /* ���нӿ�Subindex*/
    ULONG ulDnInterfaceIndex;    /* ���нӿ�Subindex*/

    /*========GTP��Ϣ��Я������Ԫ��ʾ=======*/
    UCHAR ucIMEISVOccur              : 1;
    UCHAR ucRatTypeOccur             : 1;
    UCHAR ucUserLocationInfoOccur    : 1;
    UCHAR ucMSTimeZoneOccur          : 1;
    UCHAR ucAdditionalTraceInfoOccur : 1;
    UCHAR ucChargingCharOccur        : 1;
    UCHAR ucRAIUpdateFlag            : 1;
    UCHAR ucLifeTimeFlag                 : 1;   /* ����PMIP�����±�ʶ��ʱ������ */

    /*========���������ͺ����Եı�ʾ=======*/
    UCHAR ucIsTftExist      : 1;       /* ���������Ƿ����TFT�ı�ʶ */
    UCHAR ucDataFlag        : 2;       /* ����ת����־ */
    UCHAR ucL2TPFlag        : 1;       /* ����L2TP��� */
    UCHAR ucPppFlag         : 4;       /* ����ppp��־ */

    UCHAR ucCmdProcess      : 1;
    UCHAR ucLiFlag          : 1;
    UCHAR ucDataTrcFlg      : 2;
    UCHAR ucIpv6RouteMsgNum : 4;       /* ��ǰ��ucMsgNum */

    UCHAR ucFlagRsv      : 5;          /* ϵͳ����Ҫ����ı�־λ;Ŀǰʹ�õ�0λ���浱ǰ�������Ƿ�ʹ����GGSN QOS*/
    UCHAR ucImsFlag      : 2;          /* ���������ͱ�־*/
    UCHAR ucDhcpFlag     : 1;          /* ���ӱ�ʾ�Ƿ���DHCP�û��ı�־  */
    /* ����4�ֽڶ��� */

    UCHAR ucBit2SelectType    : 2;   /*PCCʹ���ֶ�: 0 ����pcrfgrpѡ��service��1:����ȫ��realmIdexѡ��������2:����apn�µ�realmѡ������; 3:��ʼ��ֵ(��AM��֤)*/
    UCHAR ucStripFlag        : 1;      /* ����������־ */
    UCHAR ucConfict : 1;
    UCHAR ucLcenseFlag       : 1;
    UCHAR ucErrorIndicationDirect : 1; /* SGW�ϱ�ʾerror indication�ķ���:0-��ʾ������յ���1-��ʾ���Ҳ��յ�*/
    UCHAR ucPrepImsFlag      : 2;      /* ר�г�����IMS���������ĵ�Ԥ��ָʾ���Ⱥ�PCRF������󼴿�ת��*/

    UCHAR ucLapSectionV4Num;
    UCHAR ucLapSectionV6Num;
    UCHAR ucipv4LAPSequence:4;      /*ipv4��ַ��Ӧ��lap���е���*/
    UCHAR ucipv6LAPSequence:4;      /*ipv6��ַ��Ӧ��lap���е���*/
    /* ����4�ֽڶ��� */

    GTP_LICENSETYPE_S ucLicneseType;/* 4�ֽڣ�����license �жϵ�����*/
    USHORT usPoolIndex;             /* AAA���صĵ�ַ������*/
    USHORT usPoolIPV6Index;         /* AAA���ص�ipv6��ַ������*/

    /*========CM���=======*/
    ULONG ulCdrfChargingId;         /* CDRF�Ʒ�ID(Э) */
    ULONG ulCgAddr;                 /* CG��ַ */
    ULONG ulRadiusIndex;            /* AAA�Ʒѵ�����*/
    ULONG ulIdleTime;               /* ����ȷ�ϵĿ���������ʱ��*/

    UCHAR ucChargeFlag        : 4;  /* �ȼƷѣ�ʵʱ�Ʒѵȱ�ǣ�CM����һ��*/
    UCHAR bit1OnlChrgEnabled  : 1;  /* 1: online charging enabled; 0: online charging disabled*/
    UCHAR bit1OflChrgEnabled  : 1;  /* 1: offline charging enabled; 0: offline charging disabled*/
    UCHAR ucOfflineBillAttrFlg: 1;  /* TMO-Offline-Billing-Attr�Ƿ���Чֵ��0��ʾ��Ч��1��ʾ��Ч */
    UCHAR ucBitAccountingFlag : 1;  /* �Ƿ�ʹ��AAA�Ʒ� */
    UCHAR ucTimeQuotaType;          /* TMO-Offline-Billing-Attr������Time-Quota-Type��ֵ*/

    USHORT usMMECsId;               /* MME FQ-CSID�е�CSID����*//*Wangyuting add for UGW1.1*/
    USHORT usSGWCsId;               /* SGW FQ-CSID�е�CSID����*//*Wangyuting add for UGW1.1*/
    USHORT usPGWCsId;               /* PGW FQ-CSID�е�CSID����*//*Wangyuting add for UGW1.1*/
    ULONG ulMMENodeId;              /* MME FQ-CSID�е�NODE-ID���֣���ʱֻIPV4��ַ*//*Wangyuting add for UGW1.1*/
    ULONG ulSGWNodeId;              /* SGW FQ-CSID�е�NODE-ID���֣���ʱֻIPV4��ַ*//*Wangyuting add for UGW1.1*/
    ULONG ulPGWNodeId;              /* PGW FQ-CSID�е�NODE-ID���֣���ʱֻIPV4��ַ*//*Wangyuting add for UGW1.1*/
    ULONG ulMMEFqCsidIndex;         /* MME FQ-CSID��������*//*Wangyuting add for UGW1.1*/
    ULONG ulSGWFqCsidIndex;         /* SGW FQ-CSID��������*//*Wangyuting add for UGW1.1*/
    ULONG ulPGWFqCsidIndex;         /* PGW FQ-CSID��������*//*Wangyuting add for UGW1.1*/

    ULONG ulBaseTimeInterval;       /* TMO-Offline-Billing-Attr������Base-Time-Interval��ֵ*/
    ULONG ulAcctInterimVolume;      /* TMO-Acct-Interim-Volume���� */

    USHORT usPriFuncNameIdx;        /* TMO-Primary-Event-Charging-Function-Name���Զ�Ӧ��index��ȫf��ʾ��Ч */
    USHORT usSecFuncNameIdx;        /* TMO-Secondary-Event-Charging-Function-Name���Զ�Ӧ��index��ȫf��ʾ��Ч */
    AM_AUTH_TMO_TRIGGER_TYPE_S stTriggerType;  /* 4�ֽ� ��ӦAM_AUTH_TMO_TRIGGER_TYPE_S */

    AM_CM_UPDATETYPE_S stUpdateType;/* 9�ֽڸ�������:GTP_CHANGE_SGSN_IP,GTP_CHANGE_QOS,GTP_CHANGE_LOCATION,GTP_CHANGE_RAT */
    UCHAR ucHomeZoneId;             /* Home Zoneģ�鷵�ص�Home Zone������״̬ */
    UCHAR ucChargingType;           /* AAA�������·���Billing-Type : 0=prepaid��1=post-paid��2=post-paid with credit control,
                                       3=prepaid with credit control��4=HLR, 5=wallet specific,
                                       6=wallet specific without credit control, 7=hot billing*/

    UCHAR ucIndirectForwardInputInterfaceType; /* ���ת����ӿ����� */
    UCHAR ucIndirectForwardOutputInterfaceType;/* ���ת�����ӿ����� */

    UCHAR bit1SgwOflChrgEnabled: 1;
    UCHAR ucOcscForceDropFlag  : 1; /* tianshuang for CR20120301017*/
    UCHAR ucDhcpIPV6Flg        : 1; /* tianshuang for DHCP-IPV6 2012-07-10 ��ʶ�û��Ƿ�ΪIPV6*/
    UCHAR ucBWMUsrFlg          : 1;
    UCHAR ucBit4BearerReqMsgLeft:4;

    UCHAR ucSrvLevel         : 3;   /* ҵ�񼶱�*/
    UCHAR ucL2tpChkFlg        :1;    /* l2tp�û��˲��־λ���÷�:�Ѿ��˲����1��δ�˲����0���˲�������½����û���1 */
    UCHAR ucRadiusDisablePcc : 1;   /* ��ʶRADIUS�Ƿ��·�����PCC��־*/
    UCHAR ucUsrTypeFlg       : 2;   /* �û��������ͣ�����ɵ���ע���滻����*/
    UCHAR ucAAARspCCFlag     : 1;   /* ��ʹ��for Celcom Single APN��AAA���ص�CCֵ�Ƿ�Ϸ���1Ϊ�Ϸ� */

    UCHAR ucUpAmbrCarFlag    : 2;   /* ���ڱ�ʶȱʡ�����Ƿ�ʹ��������AMBR CAR����,�Ա�ר�г��ؾݴ��ж��Ƿ���ҪCAR���� */
    UCHAR ucDownAmbrCarFlag  : 2;   /* ���ڱ�ʶȱʡ�����Ƿ�ʹ��������AMBR CAR����,�Ա�ר�г��ؾݴ��ж��Ƿ���ҪCAR���� */
    UCHAR ucNotifyPcrfcFlag  : 2;
    UCHAR ucTeardownFlag     : 1;   /* ��¼ȥ���������Ƿ�Я����teardown��������CHR�ϱ�ʱʹ��*/
    UCHAR ucPcoBcmMode       : 1;   /* 0��ʾPCO��Ԫ��Я����֧��UE_NW��1��ʾ֧��UE_NW*/

    UCHAR aucTransparentData[32];   /* TMO-Transparent-Data���ԣ����Ϊ8 */

    /*========CMʹ��=======*/

    ULONG   ulpdpActForCmStampLow;  /* �����ļ���ʱ���--��λ*/
    ULONG   ulpdpActForCmStampHig;  /* �����ļ���ʱ���--��λ*/
    ULONG   ulpdpDelForCmStampLow;  /* ������ȥ��ʱ���--��λ*/
    ULONG   ulpdpDelForCmStampHig;  /* ������ȥ��ʱ���--��λ*/

    /*========SMʹ��=======*/
    USHORT usUserProfileID;         /* ���û�ƥ���User Profile ID*/

    UCHAR  ucRecordType         : 2;/* �����ɼ����ͣ� 0: ͳ��3��4������ ,1:ͳ��7������*/
    UCHAR  ucChargeMode         : 2;/* �Ʒ����ԣ�0:���߼Ʒ� , 1:���߼Ʒ�*/
    UCHAR  ucChargePropertyFlag : 2;/* ��ʶ���û��Ƿ����ݼƷ��û���0:��ͨ,1:���ݼƷ�(FBC CBB),2:PDP CBB.��0��û��userprofile��1��2������userprofile��*/
    UCHAR  ucAliasMarking       : 1;/* Alias Markingʹ�ܱ�ʶ,0:δʹ��,1:ʹ�� */
    UCHAR  ucDDosFlag           : 1;/* ��DDOS����ʹ��,0:δʹ��,1:ʹ�� */

    UCHAR  ucAAAUserProfileFlag : 1;/* 0��ʾuserprofile�Ǳ��ط��䣻1��ʾAAAָ��*/
    UCHAR  ucPerfForCmcc        : 1;/* ��ʶ�û��Ƿ����cmcc����ͳ�ƣ��ñ����ipn����am��Ҫ͸����pf*/
    UCHAR  ucPccL7ProcessFlag   : 2;
    UCHAR  ucPppFailReason      : 4;/* Modified by zhudaoming 62333 at 2008-05-15 V9R7C01B02 for AX4D02290 */

    USHORT usUserProfileGroupID;    /* ���û�ƥ���User Profile Group ID*/

    UCHAR  ucBwmSubscriberEnable: 2;/* �û���BWM����ʹ�ܱ�־*/
    UCHAR  ucBwmGroupEnable     : 2;/* �û��鼶BWM����ʹ�ܱ�־ */
    UCHAR  ucBwmGlobalEnable    : 2;/* ȫ�ּ�BWM����ʹ�ܱ�־ */
    UCHAR  ucActionSupport      : 1;
    UCHAR  ucBit1OnlineCharGranFlag :1;

    UCHAR  ucHZUserFlag:1;   /* ��ʶ���û��Ƿ�ΪHome Zone�û���0:��Home Zone�û���1��Home Zone�û�*/
    UCHAR  ucHZErrorFlag:1;  /* ��ʶ���û����ӵ���HomeZone Server��ǰ�Ƿ�����������0:������1��HomeZone Server����Ӧ*/
    UCHAR  ucHZRspFlag:1;    /* �Ƿ��յ�HomeZone Server��Ӧ��Ϣ��־����ʼ��Ϊ0 0��û���յ� 1���յ�*/
    UCHAR  ucHZApnFlag:1;    /* ��ʶ���û��Ƿ���Home Zone APN���0:��Home Zone APN��1��Home Zone APN*/
    UCHAR  ucCoaNotifyUserProfileUpdated:1;  /* COA����UserProfile��־��1,��ʾCOA���¹�,������SGSN�ĸ���; 0,COAδ����,����SGSN���� */
    UCHAR  ucCoaQosChangedFlag:1;            /* 1,�����ı� 0,δ�����ı� */
    UCHAR  ucCoaUserProfileChangedFlag:1;    /* 1,�����ı� 0,δ�����ı� */
    UCHAR  ucFbcAdd:1;                       /* 1,���ӹ�FBC��ͳ�� 0��û�����ӹ�FBC��ͳ��*/

    ULONG  ulUsageRptCBIndex;
    USHORT usPmipLifetime;
    UCHAR ucRadiusL2tpFlg:1;           /* ʹ�ñ�Ǳ�ʶ��radius���ص�L2TP���ԣ���¼���������� */
    UCHAR ucSlaveSessionTimeOutFlg:1;  /* �������SESSION TIMEOUT��ʱ���¼��־��ƽ��ʱɾ�����������嶪ʧ���ݵ����û����� */
    UCHAR ucActDedBearerFlag:1;        /* ��������session�м����ר�г��صĸ�����������Ӧ��ȱʡ������ͳ��*/
    UCHAR ucOldGtpVer:2;
    UCHAR ucPppNotL2tpFlag:1;          /* ����ȷ��PPP�ս��û��������ͳ���Ƿ�ͳ�ƹ�*/
    UCHAR ucSADedic:2;                /* ��ʶר�г����Ƿ�ΪDPI��L3,4���������,ue������̬pcc����:0��DPI:1��L34��:2*/
    UCHAR ucAmRsv;                     /* Session������������ĳ������� */

    SDB_REQ_MSG_IP_INFO_S stReqMsgIpInfo; /* 12�ֽ� ������Ϣ�е�IPͷ��Ϣ���ڻ���Ӧ��Ϣʱʹ�ã�����Ҫ���� */

    ULONG ulLeftPeerTeidcOld;          /* �����л�����ԭ��Զ���Ԫ��MME��SGW����Ϣ�û�������Ϣ����*/
    ULONG ulSgwLeftPeerSigIP;          /* ��Ԫ�н����������Զ�IP */
    ULONG ulSgwLeftLocSigIP;           /* ��౾������IP */
    USHORT usSgwLeftPeerSigPort;       /* IPͷ�е����Զ�����port */
    USHORT usSgwLeftLocSigPort;        /* ��౾������port */
    ULONG ulSgwLeftPeerDataIP;         /* ���Զ�����IP */
    ULONG ulSgwLeftLocDataIP;          /* ��౾������IP */
    USHORT usLeftSigPathId;            /* �������·������*/
    USHORT usLeftDataPathId;           /* �������·������ */
    ULONG ulSgwLeftPeerTeidc;          /* ���Զ����������ʶ */
    ULONG ulSgwLeftLocTeidu;           /* ��౾�����������ʶ */
    ULONG ulLeftSendSeqNo;             /* ��෢�͵���Ϣ���к� */
    ULONG ulLeftRcvSeqNo;              /* �����յ���Ϣ���к� */
    ULONG ulLeftTimeStamp;             /* ��������Ϣ��ʱ��� */

    UCHAR ucLeftDataIfType;            /* ���������ӿ����� */
    UCHAR ucLeftSigIfType;             /* ��������ӿ����� */
    UCHAR ucLeftEncapType;             /* ����װ����*/
    UCHAR ucRightDataIfType;           /* �Ҳ�������ӿ����� */

    UCHAR ucRightSigIfType;            /* �Ҳ������ӿ����� */
    UCHAR ucRightEncapType;            /* �Ҳ��װ����*/
    USHORT usPolicyId;                 /* SMʹ�õ�Policy Id */

    ULONG ulS5_Gn_PeerSigIP;           /* �Ҳ�Զ�����IP */
    ULONG ulS5_Gn_LocSigIP;            /* �Ҳ౾������IP */
    USHORT usS5_Gn_PeerSigPort;        /* �Ҳ�Զ�����port */
    USHORT usS5_Gn_LocSigPort;         /* �Ҳ౾������port */
    ULONG ulS5_Gn_PeerDataIP;          /* �Ҳ�Զ�����IP */
    ULONG ulS5_Gn_LocDataIP;           /* �Ҳ౾������IP */
    USHORT usRightSigPathId;           /* �Ҳ�����·��ID */
    USHORT usRightDataPathId;          /* �Ҳ�����·��ID */
    ULONG ulS5_Gn_LocTeidu;            /* �Ҳ�Զ����������ʶ */
    ULONG ulRightSendSeqNo;            /* �Ҳ෢�͵���Ϣ���к� */
    ULONG ulRightRcvSeqNo;             /* �Ҳ���յ���Ϣ���к� */
    ULONG ulRightTimeStamp;            /* �Ҳ������Ϣ��ʱ��� */
    ULONG ulControlBlockIndex;         /* ���ƿ����� */
    ULONG ulIndirectForwardPeerDataIP; /* ���м��ת���Զ�����IP */
    ULONG ulIndirectForwardPeerTeidu;  /* ���м��ת���Զ����������ʶ */
    ULONG ulIndirectForwardLocTeidu;   /* ���м��ת������Ϊ�Զ˷�������������ʶ */

    GTP_ULI_S stULI;                   /* 20 */

    UCHAR ucHeartBeatTimoutNum;        /* ��ʶ���������Ϣ��ʱ���� */
    AM_GTPV2_SERVING_NETWORK_S stGTPV2ServingNetwork;/*3�ֽ�*/
    UCHAR  ucRevForULI;                /* SDU �������ڵ�VCPU */
    UCHAR  ucSduVcpuId;                /* SDU �������ڵ�VCPU */
    USHORT usTokenId;                  /* �����ĵ�TOKEN ID */

    AM_GTPV2_INDICATION_S  stGTPV2Indication;  /* 4�ֽ� */

    UCHAR ucChangeReportingAction;

    UCHAR ucServingNetworkOccur: 1;    /* ��Ϣ���Ƿ�Я����Serving NetWork��Ԫ */
    UCHAR ucNetworkSecActFlag  : 1;    /* �������μ��Ϊ1��ʾ�ö�����������������ഥ���ģ�ֻ�������ں�������V1�û���Ϊ0��ʾ��ͨ����༤�� */
    UCHAR ucBitPcrfCfFlag      : 1;    /* pcrf�·���cf��ʶ��Ĭ��ֵΪ 0 */
    UCHAR  ucBitPcrfCarryCfFlag: 1;    /* 1��ʾpcrfc �·���cf��ǣ�0��ʾpcrfc δ�·���cf���*/
    UCHAR ucIpflag             : 1;
    UCHAR ucSeqLinkNo          : 3;    /* ���ڼ�¼����teidc�󶨵�sequece������*/

    GTP_EVOLVED_ARP stEvolvedARP;      /* 1�ֽ� */

    UCHAR ucEmergencyFlag     : 1;     /* ��ʶ��ǰ�û��ǲ��ǽ��������û�,0:��ǰ�û����ǽ��������û�;1:��ǰ�û��ǽ��������û�*/
    UCHAR ucImsiInvalidFlag   : 1;     /* ��ʶ��ǰ�û��Ƿ���ڿ��õ�IMSI;0:��ǰ�û�IMSI����;1:��ǰ�û�IMSI������*/
    UCHAR ucBitTaiTriggerFlag : 1;
    UCHAR ucBitEcgiTriggerFlag: 1;
    UCHAR ucImsLocChangeFlag  : 1;     /* imsλ���ϱ����λ,���ڱ�ʾ��pcrfc֪ͨ����ʱ�Ƿ���Ҫ����෢����º�indication�ֶ�Octet 7��bit8��1 */
    UCHAR bit1MsdFlag         : 1;     /* �Ƿ���MSD�û�, �ñ����MSD������ЧSG����Ϣʱ��λ*/
    UCHAR bit1UptByIdleTimeOut: 1;
    UCHAR bit1SendReqFlag     : 1;     /* SPU��MSD-SDU������Ϣ���¼�ѷ�������Ϣ��ǣ������յ�MSD���ص���Ӧ��Ϣ������˱��.
                                          ���SPU��û���ͼ������󣬾��յ�MS����Ӧ��Ϣ����ֱ�Ӷ�������Ϣ��*/
    /*4*/

    USHORT usExternalEvent;            /* ԭʼ���� */
    UCHAR ucLinkedEPSBearId;
    UCHAR ucbit1TightInterwork: 1;     /* 0:�����  1:����� */
    UCHAR ucTetheringFlag     : 1;
    UCHAR ucLiDirectFlg       : 1;
    UCHAR usPMIPTimeoutFlg    : 1;
    UCHAR ucCorrelationID     : 4;     /* ������μ���ʹ�� */
    /*4*/

    ULONG ulCmdSeqNo;                  /* cmd ��������к� */

    USHORT usCmdType;
    UCHAR ucNotifyLeftDel : 1;
    UCHAR ucNotifyRightDel: 1;
    UCHAR ucPartNum       : 6;
    UCHAR ucRatTypeOld;                /* rattype�仯��ʱ������ͳ�Ƶ�ǰratֵ��Ӧ���û��� */
    /*4*/

    UCHAR ucEPSBearId;                 /* EPS Bear ID, GGSNʹ�������������NSAPI*/
    UCHAR ucPTI;                       /* Procedure Transaction Id*/

    UCHAR ucBCM              :2;       /* Bearer Control Mode*/
    UCHAR ucOldDTI           :1;       /* DT�û�ͳ��ʹ�� */
    UCHAR ucApplyAddrSuccFlag:2;       /* ���� */
    UCHAR ucRcvLBIFlag       :1;       /* �����SGW �յ���Modify ��Ӧ��Ϣ��Я��LBI ��Ԫ*/
    UCHAR ucApplyAddrFailFlag:2;       /* ����*/

    UCHAR ucConvergenceLicType     :3; /* �ں�license����,����UGW_NET_ELEMENT_ROLE_E��ʾ*/
    UCHAR ucConvergenceLicTypeForHO:3; /* �л����������Ҫ���ں�license����,����UGW_NET_ELEMENT_ROLE_E��ʾ*/
    UCHAR ucVirtualGiIdFlag        :1; /* ���ڱ��AAA�Ƿ�����GiId*/
    UCHAR ucSendToPcrfMBCMsg       :1; /* 0��ʾ����MBR��Ϣ,1��ʾ����MBC��Ϣ */
    /*4*/

    ULONG ulVirtualGiId;               /* ���ڴ洢AAA���·���GiId */
    UCHAR ucBearCmdEBINum;             /* bearer resource /delete /modify command������ */
    UCHAR ucBearCmdEBI[M_MAX_BEARER_NUM];
    /*16*/

    UCHAR ucAllFilterNum    :5;        /* ��̬pccʱ���ڼ�¼��ǰ����filter��*/
    UCHAR ucSendRsp2Sm      :1;        /* �Ƿ���Ҫ��sm����Ϣ, 1:��Ҫ��0:����Ҫ */
    UCHAR ucIsCreatedByUE   :1;        /* �Ƿ���UE����������ר�г���, 1:�ǣ�0:����-���ع��򴥷� */
    UCHAR ucNeedSaveUEReqQos:1;        /* �Ƿ���Ҫ����UE�����qos, 1:�ǣ�0:����*/

    UCHAR ucLocalFilterNum       :5;   /* DPI����L3,4�㴥����filter����*/
    UCHAR ucIsAlreadySaveUEReqQos:1;   /* �Ƿ��Ѿ�����UE�����qos, 1:�ǣ�0:����*/
    UCHAR ucSendToPfFlag         :1;
    UCHAR ucDDNCauseFlag         :1;   /* ����DDN��ϢʱЯ��ԭ��ֵ�ı�־:0:��Я��;1:Я��*/

    UCHAR ucApnRestrictionForRsp ;     /* ��������apn�µ����õ�APN Restrictionֵ���Ա����Ϣʱֱ�Ӵ��������л�ȡ����ʡһ�ζ�CDB����*/
    UCHAR ucPcrfcDelCause;             /* AM��pcrfc��ȥ��ԭ��ֵ */
    ULONG ulStateMachineTrace;         /* ״̬������λ�� */
    /*8*/

    in6_addr stMainDnsIp;
    in6_addr stBackupDnsIp;
    /*32*/

    ULONG ulIpv4PriDnsIp;              /* ��IPV4 DNS��ַ */
    ULONG ulIpv4SecDnsIp;              /* ��IPV4 DNS��ַ */
    /*8*/

    UCHAR ucGroupLevelServiceType;     /* ��¼�û��鼶��ҵ�����ͣ� tos /non-tos*/
    UCHAR ucPccMode;                   /* modify by wangboyu at 2011-08-31 for PCC �ں� */
    USHORT usUserGroupID;              /* �û���ID��ͬʱҲ���û��鼶BWM_CB����������� */
    USHORT usPmipSequence;
    UCHAR ucHandoffIndicator;
    UCHAR ucIpv6PrefixLength;          /* radius ���ص� IPV6 ǰ׺���� */
    /*8*/

    UCHAR ucToBeRmvFlag             :1;
    UCHAR ucRATorAMBRorULIChangeFlag:1;/* create/modifyʱRAT��AMBR�Ƿ�ı�*/
    UCHAR ucRightTunnelHasCreat     :1;/* ����SGWʹ�ã��������SGW�Ƿ��Ѿ���Right Local FTEID-U ��Ϣ���͸�PGW,
                                          SGW������CreatSession����Modify Bearer��Ϣ�У�����Ϣ����PGW */
    UCHAR ucLocSccgChangeFlg        :1;
    UCHAR ucLocDst                  :2;
    UCHAR ucPmipLifeTimeOP          :2;/* PMIP LifeTime��ʱ��������ʶ:0:��Ч;1:����;2:ɾ��;3:ɾ��������*/

    UCHAR ucUserAttri               :4;
    UCHAR ucSupExtendQci            :4;

    UCHAR ucIdlePagingIndication;      /* ��ʶidlePaging����,�±���ʱ,��Ҫ���ݸ�ָʾ,����idlePaging��ر�ʶ */
    UCHAR ucApnRestriction ;           /* ��������createsessionrequest��Ϣ�е�APN Restrictionֵ��������apn�����ñȽϼ��ط���Ϣ�б�ѡ��Ԫ�ļ��*/
    /*4*/

    USHORT usS6bCurDiamSrvIndex;
    USHORT usS6bDraRealmIndex;

    APN_AMBR_S stApnAmbr;              /* 8�ֽ�Aggregate Maximum Bit Rate AMBR */

    ULONG ulPcrfcTransID;
    ULONG ulSessionIndex;              /* index of session cb */
    ULONG ulBearerIndex;               /* index of bearer cb */

    UCHAR ucPriOfcsIndex;              /* ��offline function(CG)������*/
    UCHAR ucSecOfcsIndex;              /* ��offline function(CG)������*/

    UCHAR ucIsRTUser :1;               /* ����ʵʱ�û���� */
    UCHAR ucBcmChanged:1;              /* ��ʾ�յ�PCRFC������Ϣ�е�BCM�Ƿ��б仯*/
    UCHAR ucUserDefaultIdleTime:1;     /* ��ʶδ����idle-timeoutʱʹ��Ĭ�ϵ�idleʱ��,ĿǰΪ1��,�����bit1157����,Ĭ�Ͽ�,�������û���Ч*/
    UCHAR ucSuspendAdd:1;              /* 1,���ӹ�suspend��ͳ��  0��û�����ӹ�suspend��ͳ��*/
    UCHAR ucSPGWCsFlag:1;              /* SPGW����ʧ��ʱ��Ӧ��Ϣ��Causeֵ��CSλ��1������0,1��ʾCS��Ҫ��1,0��ʾCS��Ҫ��0*/
    UCHAR ucLiBkpFlag :1;
    UCHAR ucFupEnableFlag :1;          /* ��ʶPCRF������FUP,���ڸ�PF�±��� */
    UCHAR ucPrivateExtensionOccur:1;

    UCHAR ucUsmBackupFlg:1;            /* �����Ƿ��Ѿ����ݹ���־*/
    UCHAR ucPrivateDelCause:3;
    UCHAR ucIsQchatIdletime:1;         /* idletime�Ƿ�ʹ�� qchat��idletime*/
    UCHAR ucCoaQosFlag:1;
    UCHAR ucSAEmsFlag:1;              /* Gn��ά��SA���*/
    UCHAR ucDropEmsFlag:1;             /* ������ά���Ƿ�ʼ�ı��*/

    UCHAR ucPcrfcAuthReqType       :3; /* AM ����pcrfc������Ϣʱ����ϢԤ���� 0 :�ɹ�; 1: ʧ��*/
    UCHAR ucPcrfcDelType           :1; /* AM ��pcrfc�����Ϣȥ������: 1 :session; 0: bearer*/
    UCHAR ucSlavePdpFlag           :1; /* ʹ�ñ�Ǳ�ʶ�Ǳ����û�������ƽ��ʱ����ͳ�ƻָ��� */
    UCHAR ucNeedSendToMMEFlag      :1; /* �����ظ�����Ϊ��һʱʹ�ã����ڱ�ʶ֪ͨpgwɾ����delete-rsp��Ϣ�����͸�mme��1:����Ҫ��0:��Ҫ*/
    UCHAR ucRadiusPCMode           :2; /* ���� */

    UCHAR ucPccResourceFlag        :1; /* ucPccResourceFlag: 1:ռ��PCC��Դ       0:��ʾû��ռ��PCC��Դ*/
    UCHAR ucReportingLevelDefault  :1;
    UCHAR ucMessageCode            :6; /* modify by wangboyu at 2011-08-31 for PCC �ں� */

    UCHAR ucRuleChangeFlag         :1;
    UCHAR ucTriggerChangeFlag      :1;
    UCHAR ucPcrfcQosNegoSwitch     :1;
    UCHAR ucPcrfNotifyQosUpdateFlag:1;
    UCHAR ucPccUpdataFlag          :1; /* AM ��pcrfc�����Ϣ��������: 1 :session; 0: bearer*/
    UCHAR ucPccRollQos             :1;
    UCHAR ucPccEveTriFlag          :2; /* ���ڱ�ʾ�Ƿ��и�����Ҫ�ϱ�PCRFC ,1 ��ʾ��Ҫ�ϱ�*/

    UCHAR ucTftOperCode     :3;        /* tft�����룬��Ӧ6������*/
    UCHAR ucTempTftOperCode :3;        /* ���泡��ʹ�ã��ڶ���filter������*/
    UCHAR ucBufferOperCode  :2;        /* ��¼���泡����C+U,U+U*/

    USHORT usPcrfGrpIndex;
    USHORT usFilterIDAllocation;       /* filter id����λͼ, �ӵ͵���0~15λ��1��ʾ�ѷ��� */
    ULONG ulGtpv2Scene;
    USHORT usFirstFramedRouteIndex;
    USHORT usFramedRouteCount;

    ULONG ulSgsnAsn;                   /* ASN���μƷ�,AMдCM�� */
    UCHAR ucAsnState;                  /* ��ǰPDP�Ƿ��ڵ�״̬*/
    UCHAR ucCcSelectMode;
    UCHAR ucPrivateCause;                /* for perf at 2013.12.2��˽��ԭ��ֵ����ʶ���ַ�Э��涨��ԭ������ͳ���� */
    UCHAR ucApnLockDelUserFlag;        /* ��ʾ�Ƿ�lock enable deactive enableȥ����û�*/

    GTP_COMMON_FLAGS_S stCommonFlags;  /* 1�ֽ� */
    UCHAR ucChargingCharInMsg[2];      /* ���ڴ洢SGSNЯ����CC��Ԫ��ֵ*/
    UCHAR ucUpdatePccFlag   :1;
    UCHAR ucPccFilterType   :1;
    UCHAR ucSendDelSessReq  :1;
    UCHAR ucSendDelBearerReq:1;
    UCHAR ucSendDelBearerCmd:1;
    UCHAR ucRcvDelBearerReq :1;
    UCHAR ucPccResved       :1;        /* �Ѿ�ʹ�� */
    UCHAR ucBearerLevelQosChanged :1;

    USHORT usSeqNo;
    USHORT usReqQoSLevel;

    ULONG ulResource;                  /* ��Դλ,ugw��GGSNʹ�õĲ�ͬ������ʹ���ĸ�? */
    ULONG ulSgwIfindex;                /* ���ڱ����鼶�ӿڵ�Sgw ���Ifindex */
    ULONG ulPgwIfindex;                /* ���ڱ����鼶�ӿڵ�Pgw or GGSN ���Ifindex */
    ULONG ulPdnConnectionId;           /* ���ڼ�¼ȱʡ���ص�ulCdrfChargingId */
    USHORT usNoConfigApnIndex;         /* SGWδ����APN��Index(1-3000)*/
    UCHAR aucAPNOI[6];                 /* ���APN OI��Ϣ*/

    UCHAR ucPcrfLocalIndex;
    UCHAR ucBit1HandOverSucNotify:1;   /* 11.0 EE���� ��־ePDG��LTE֮����л� pcc�ظ��ɹ�����ACK���ظ�ʧ�ܲ��÷���ACK */
    UCHAR ucGul4To3TimerFlag :1;       /*GUL4��3�������Ӷ�ר�г��صı�����ʱ������ֹ����PDN��û���л��ɹ��ĳ���CR-0000057833*/
    UCHAR ucoldImsflg        :1;
    UCHAR ucAfdnsFlag        :1;       /* anti-fraud-dns��ʶ�Ƿ��ǿ���DNS����թ���ܵ��û� */
    UCHAR ucMseOldUsrFlg    : 1; /* ���ڶ�ҵ���û�����ͳ�Ʊ��*/
    UCHAR ucCLPdnTypeFlag: 1;              /* C->C, L->C�л�����, PBU������ϢЯ��˫ջ, Э�̺󷵻�PBA��ϢΪ��ջ,
                                               ��ҪЯ��pdn-type-indication��չ, ʹ�øñ���ж� */
    UCHAR ucOverloadFlag:1;            /* 11.0��������������ԣ�0:��SDU������ͨ��ɾ��������Ϣ��1:��SDU�����������������Ϣ */

    UCHAR ucBitcommendFlag : 1;  /* ��ʾ�ü����������Ϣ��������Ƽ�*/
    USHORT usTempFilterOperIndic;      /* ���泡��ʹ�ã���¼�ڶ��α�������filter��ʶ*/

    UCHAR ucMultiServiceFlg     :1;    /* ��¼�Ƿ���Multi-Service�û� */
    UCHAR ucMultiContextFlg     :1;    /* ��¼Multi-Service�û���������,0:service pdp,1 ��pdp */
    UCHAR ucMultiUpdateFlg      :2;    /* ��¼service PDP����δ����̬ʱ�յ��������� */
    UCHAR ucMultiAddressInherit :1;    /* ��¼multiple-apn�µ�address-inherit����ֵ */
    UCHAR ucRadiusServerFlag    :1;    /* ��ʶ�û��Ƿ�ʹ��radius����*/
    UCHAR ucChrDelDirect        :1;    /* CHR��ʶ�û�ȥ���Ĭ��Ϊ0��GGSN����ȥ�� 1ΪSGSN����ȥ��*/
    UCHAR ucUGWAllocSeqNo       :1;    /* ��ʶ�Ƿ���UGW�����������Ϣ����ʱSeqNo��UGW���з���:1��ʶUGW����SeqNo,0��ʶ��UGW����*/

    UCHAR ucMsisdnLen;                 /* ����msisdn���� */
    USHORT usServiceIndex;             /* ����service PDP,���浱ǰ�����service-index; ����default PDP,����multiple-apn��index */

    ULONG ulDefaultPDPIndex;           /* ��¼Default PDP�������������ü�¼ֻ��Multi-Service�û���Ч */

    UCHAR ucMultiSerDelNum:4;          /* RAR����Serivce Listʱ����Ҫɾ����S-PDP��������󲻳���10 */
    UCHAR ucMultiSerCreateNum:4;       /* RAR����Serivce Listʱ����Ҫ������S-PDP��������󲻳���10 */

    UCHAR ucMultiSerPcrfUdpFlg:3;      /* RAR����AM��PCRFC��Ӧʹ�÷���ֵ �ɹ�:0 ʧ��:1 ��Ȩʧ��:2 */
    UCHAR ucMSRarDelSerPdpFlg:1;       /* RAR������Ҫɾ��Service PDP�ñ�־Ϊ1 */
    UCHAR ucMSRarUpdBakFlag:1;         /* RAR����ʱ��Ҫ֪ͨIPN���б��ݵı�־ */
    UCHAR ucPccRollBackFlag:1;         /* PCRFC֪ͨAM PCC�ع�ʱ��AM�ø�λΪ1��IPNͨ���˱�־�ڱ������ع����������ֶ���PCRFC��AM�ظ�����Ӧ��revoke��Ϣʱ��λ*/
    UCHAR ucBitCfFlag :1;              /* 1��ʾCF�û���0��ʾ����CF�û�*/
    UCHAR ucDelNullflg:1;              /* ��ʹ�� PCC�û�ͨ��BRC��Ϣɾ��filterʱ�����ȫ��filterid���޷��ҵ���Ӧ��filterʱ��UGW������²�������֪ͨPCC  modify start by wangboyu for TFT�쳣���� at 2012-01-31   */

    UCHAR ucVIPDelByLicense:1;         /* ����license���㣬VIP�û���������µ���ͨ�û�ȥ�� */
    UCHAR ucOldVIPUserFlg:1;           /* ��������ͳ��*/
    UCHAR ucVIPAccessPrioFlg:1;        /* ��ʶVIP�û��Ƿ����Ƚ��� */
    UCHAR ucVIPUserFlg:1;
    UCHAR ucSmoothFailFlag:4;          /* ƽ��ʧ�ܺ�ȥ�����ͱ�ʶ:0:�����û� 1:CMƽ��ʧ�� 2: */

    UCHAR ucUserLevelServiceType;

    UCHAR szHomeZoneResultCode[6];     /* �û���resultcode */
    UCHAR ucRspHZSameMsgNum;           /* ��ʾ�յ�HZģ����ͬ��״̬֪ͨ��Ϣ���� */
    UCHAR ucBitSendDeacToSgsn:1;       /* �Ƿ��SGSN����ȥ�������־ */
    UCHAR ucPccIndicate:4;             /* Pcc Indicate Num, IPNд��AM�����·����ֶθ�PF  by penghui for 9.0 2011-2-6 */
    UCHAR ucRandomNo:3;                /* �������*/

    ULONG ulIndirectForwardPeerULDataIP;/* ���м��ת���Զ�����IP */
    ULONG ulIndirectForwardPeerULTeidu; /* ���м��ת���Զ��������������ʶ */
    ULONG ulIndirectForwardLocULTeidu;  /* ���м��ת������Ϊ�Զ˷�������������ʶ */
    ULONG ulChrProcID;                  /* CHR�ϱ�ʱ����ͬһ���ն���һ�����߹����еĲ�ͬ���̣�����ȱʡ���ؽ����ۼ�*/
    ULONG ulTcpChkTimeStamp;
    ULONG ulNWSessionIndex;            /* NW-AGENTģ����������������ֱ������NW������ */

    T3GPP_SGSN_MCC_MNC_S stOldSgsnPlmn;/* 4�ֽ� */
    USHORT usCFTemplateID;
    USHORT usCfProfileListId[MAX_CFPROFILES_FROM_ONE_GX_MESSAGE];  /*���cf-profile id������*/

    UCHAR ucBitLocReportFlag:2;        /* MS INFO Change Reporting Action:0:Stop reporting,1:start report CGI/SAI,2:start reporting rai*/
    UCHAR ucBitMsChangeExtendFlag:1;   /* ��Ϣ���Ƿ�Я��MS Info Change Reporting support indication��չͷ*/
    UCHAR ucBitRaiTriggerFlag:1;       /* PCRF/AAA/OCS/CG�Ƿ��·�rai trigger*/
    UCHAR ucBitUliTriggerFlag:1;       /* PCRF/AAA/OCS/CG�Ƿ��·�ULI trigger*/
    UCHAR ucBitMsFlag:1;               /* ��ǰ���ڴ���ms info change request��Ϣ������Ϣ��PCRF/CM����ʱ�����ʧ�ܻ�ʱ��ȥ���û�*/
    UCHAR ucAAAQosFlag:1;              /* 1,AAA�·�����Ч��QosId��0��AAAû���·�QosId */
    UCHAR ucQchatFlag:1;               /* �Ƿ�ΪQchat�û���־ */

    UCHAR ucPerfLicenseDownFlag:4;
    UCHAR ucPerfLicenseUpFlag:4;

    UCHAR ucbitLiRoamingChgFlag:1;
    UCHAR ucBitAreaCongTriggerFlag:1;
    UCHAR ucSupAreaCongestionRpt:1;    /* С��ӵ���ϱ�*/
    UCHAR ucSupprotFPIFlag:1;          /* FPI���Ա�־*/
    UCHAR ucbitTerminalFlg:1;
    UCHAR ucAdcFlag           :1;      /* ADC�û�����*/
    UCHAR ucAdcRuleFlag       :1;      /* �Ƿ���ADC����*/
    UCHAR ucAdcChangeFlag       :1;    /* ADC�Ƿ����*/

    UCHAR ucAreaCongTriggerFuncFlag:1;
    UCHAR ucGgsnInitUpdateBit:7;

    UCHAR ucCfProfileListNum;          /* cf-profile�ĸ���*/
    UCHAR uceQci;                      /* ���ڱ���PCRFC�·�����չQci,��仰��ʹ��*/
    UCHAR ucAAAQoSId;                  /* COA��AAA�·���QosId */
    UCHAR ucAcctLinkCount;

    GTP_QOS_SUB_S stSubQos;            /* ������������Qos */

    USHORT usIriTargetMap;
    USHORT usIdpTargetMap;

    UCHAR ucPcscfGrpoupIndex :4;       /* �ֱ��ʾʹ�õ�v4����v4����v6����v6��group����*/
    UCHAR ucUsedPcscf: 4;              /* ����Ѱ��ueʹ�õ�pcscf��ַ*/

    UCHAR ucSbrVogCHOFlag:3;             /* SBR/VOG�������л���� 1Ϊ���� 2Ϊ���� 3Ϊ���� 4Ϊ����*/
    UCHAR bitHoldingTimeFlag :1;       /* holding time ��Session timeoutȥ���ǣ�1:holding time 0:Session timeout */
    UCHAR btUIMSI            :1;       /* IMSI�Ƿ��Ȩ��� */
    UCHAR ucoldnullMisdnFlag:1;
    UCHAR ucnullMisdnFlag:1;
    UCHAR ucSessionStopIndicationPF:1; /* ɾ��ʱ���һ�����صı�־����PF��*/
    UCHAR ucPcscfMainIpv4;             /* V4 ����ʹ�õ���pcscf ����*/
    UCHAR ucPcscfMainIpv6;             /* V6 ����ʹ�õ���pcscf ����*/
    UCHAR ucPcscfBkpIpv4;              /* V4 ����ʹ�õı�pcscf ����*/
    UCHAR ucPcscfBkpIpv6;              /* V6 ����ʹ�õı�pcscf ����*/

    UCHAR ucPcscfFaultV4   :1;         /* V4 pcscf�Ƿ�fault���λ,�����ж��Ƿ�����෢����Ϣ*/
    UCHAR ucPcscfFaultV6   :1;         /* V6 pcscf�Ƿ�fault���λ,�����ж��Ƿ�����෢����Ϣ*/
    UCHAR bit1MsuFlag:1;
    UCHAR bit1MSUFlagc:1;
    UCHAR ucPerfRole:3;                /* ���ڱ�ǽ�������ͳ�ƽ�ɫ������:V0/V1/SGW/PGW/SPGW*/
    UCHAR ucNotifyPcrfcRel:1;          /* ���ڱ�ʾ�Ƿ�֪ͨPCRFC�ͷ���Դ(ֻ�������ں�����)*/

    UCHAR ucVogProfileChangeFlag:1;
    UCHAR ucMseRebuildFlag:1;      /*�ؽ���ǣ��ؽ�ʱ������һ���յ�MSD��Ӧʱ�����ټ�һ��
                                                        1��ʾ�Ѿ���MSD���ؽ���Ϣ ��û���յ���Ӧ��SPU��ļ����Ѽ�.
                                                        0��ʾ�ؽ��ɹ����յ�MSD����Ӧ�����Ǽ���ɹ���*/
    UCHAR ucMultiUpdFirstSucFlag:1;    /*PS11.0 PCC�����ط����Լ�¼PCC�����ĸ��������filter��Ϊ����Updateʱ��¼��һ���Ƿ�ɹ���ǣ������ط������Ƿ��͵�һ��*/
    UCHAR ucReactivationReDelFlag:1;              /* ��ʹ�ã���ʾȥ��ʱ��Я��reactivationԭ��ֵ*/
    UCHAR ucAccessGWType:4;              /* �û��������ص����ͣ�0��ʾGUL��1��ʾSCCG*/
    UCHAR ucMseProfileListOper;
    UCHAR ucMsdLogicalSlotId;          /* MSD���slot*/
    UCHAR ucMsdOSId;                   /* MSD���OS*/
    UCHAR ucSGType;

    USHORT usMSProfilelistIndex;       /* ���ڼ�¼��̬���ԣ�����������Ƿ����ж�Ϊ��MSD�û�, �˱����IPN�޸ģ�AM���� AM�����޸�bit1MsdFlag ���*/
    UCHAR ucMsdSgId;                   /* MSD���SG*/
    UCHAR ucLocalLocationReportFlag;
    UCHAR ucBriTrigger;
    UCHAR ucBri3GppErrCode;

    UCHAR ucMsdTCPOptiFlag           :1;
    UCHAR ucMseDataTrcUpFlag         :1;
    UCHAR ucMseDataTrcDownFlag       :1;
    UCHAR ucMseDropEmsFlag           :1;
    UCHAR ucSGSNS4Flag               :1;
    UCHAR ucBitPmipLapFail           :1;
    UCHAR ucBitPmipDhcpFsmFlg        :1;/* PMIP �ӳٷ��������ַ�Ƿ��Ѿ�ת״̬�� */
    UCHAR ucCrtByServOrForbiddentoCrt:1;

    UCHAR ucbit1SuspendFlag :1;        /* suspend ����״̬�����*/
    UCHAR ucbit1VoiceFlag :1;          /* Delete bearer cmd�� Voice bearer��־*/
    UCHAR ucPostLapRelease    : 2;

    UCHAR ucBit4S6bSrvSelectType:3;

    UCHAR ucbit1VogEmsFlag:1;
    GTP_PMIPV6PEERADDR_BSSID stPmipV6addrOrBSSID;     /* 16�ֽ� */
    T3GPP_SGSN_MCC_MNC_S stPmipMnIdMccMnc;/* 4�ֽ� */
    ULONG ulS6bSessionIdTimeStamp;
    T3GPP_IMSI_MCC_MNC_S stPmipApnOi;  /* 3�ֽ� */
    UCHAR ucIpType :3;                /* ipv4:0, ipv6:1*/
    UCHAR ucbit1RecvSuspendAckSuccFlag:1;                  /*sgw�յ�suspend��Ϣ�󣬸�pgw͸�������յ��ɹ�suspend ackʱ���˱�ʾ��λΪVOS_TRUE*/
    UCHAR ucOldSGSNS4Flag :1;          /* ����ԭ�е�s4SGSN��ʾ */
    UCHAR ucOldSupAreaCongestionRpt :1; /* ����ԭ�е�С��ӵ���ı�ʾ */
    UCHAR ucOldSupprotFPIFlag :1;     /* ����ԭ��FPI�ı�ʾ */
    UCHAR ucBitSgwHoTauDelFlag :1;    /*CR-0000067599 VF SGW��SGW�л��û�ȥ�����߻����ر�ԭ��ֵ����*/
}SDB_GSPU_CONTEXT_S, SIG_GGSN_PDP_CONTEXT_S;

//
//socket path define
//

/* socket ·���ṹ */
typedef struct tagRM_SOCKET_PATH_S
{
    ULONG  ulPeerAddr;                    /* �Զ˵�ַ */
    ULONG  ulLocalAddr;                /* ���˵�ַ */
    USHORT usPeerPort;                    /* �Զ˶˿� */
    USHORT usLocalPort;                /* ���˶˿� */
    ULONG  ulVrfIndex;                //VPN����
    ULONG  ulGroupifIndex;            //�鼶ifindex
    ULONG  ulLocalSubindex;           /*���˵�ַ�ӿ�����*/
    UCHAR ucProxyCode;
    UCHAR ucCommendFlag; /*����Ƽ�������������Ϣ������Ӧ��Ϣ����Ҫʹ��ԭ������߼��ӿڵ�ַ*/
    USHORT usApnIndex;   /* apn ���������ڽӿڸ��ٵ���Ϣ�ϱ� */
    UCHAR ucAliaApnFlag ;   /* ��ʾ������Ǳ���APN */
    UCHAR ucRev[3];
}VOS_PACKED RM_SOCKET_PATH_S;

/* BEGIN: Added for PN: ȫ������  by LiHairong, 2010/4/8 */
#pragma pack (1)
typedef struct
{
    /* ������� */
    UCHAR *pucTrcMsg;           /* ��Ϣ�� */
    UCHAR  ucMsgType;           /* ��Ϣ���� */
    UCHAR  ucUgwRole;           /* ��Ԫ��ɫ */
    USHORT usMsgLen;            /* ��Ϣ���� */
    ULONG  ulEmsTrcDir;         /* ȫ��������Ϣ���� ���� 1; ���� 0 */
    ULONG  ulUsrTrcDir;         /* �û�������Ϣ���� 0x000,0x100,0x200,0x300,0x400... */
    /* �������� */
    USHORT usTraceId;
    UCHAR  ucSgwTrcFlg;
    UCHAR  ucPgwTrcFlg;
    UCHAR  ucSgwTrcIf;
    UCHAR  ucPgwTrcIf;
    UCHAR  ucProType;
    UCHAR  ucMsgIntf;
    UCHAR  ucMsgSndFlg;
    UCHAR  ucReserved[3];
}VOS_PACKED S_OM_EMS_TRC_PARA;

typedef struct tagINADDR
{
    VOS_UINT32 s_ulAddr;
}INADDR_S;

typedef struct tagSOCKADDRIN
{
    UCHAR   sin_chLen;
    UCHAR   sin_chFamily;
    USHORT  sin_usPort;
    struct  tagINADDR sin_stAddr;
    char    sin_chZero_a[8];
}SOCKADDRIN_S;

typedef   struct    tagIN6Addr
{
    union
    {
        UCHAR     u6_ucaddr[16];
        USHORT    u6_usaddr[8];
        ULONG     u6_uladdr[4];
    } u6_addr;    /* 128-bit IP6 address */
} IN6ADDR_S;

typedef struct tagSOCKADDR_IN6 {
    UCHAR       ucSin6_len;         /* length of this struct(sa_family_t)*/
    UCHAR       ucSin6_family;      /* AF_INET6 (sa_family_t) */
    USHORT      usSin6_port;        /* Transport layer port # (in_port_t)*/
    ULONG       ulSin6_flowinfo;    /* IP6 flow information */
    IN6ADDR_S   stSin6_addr;    /* IP6 address */
    ULONG       ulSin6_scope_id;    /* scope zone index */
}SOCKADDR_IN6_S;

typedef struct tagPacketInfo
{
    ULONG ulVpnId;      /*VPN IDΪ0ʱ��Ϊ����һ��ȫ�ֽӿ� */
    ULONG ulFamily;      /*IP��ַ���� AF_INET,AF_INET6 */
    union{
        SOCKADDRIN_S stAddrSrc;
        SOCKADDR_IN6_S stAddr6Src;
    }uaddrSrc;/* ����IP��ַ���˿ں� */
    union{
        SOCKADDRIN_S stAddrDst;
        SOCKADDR_IN6_S stAddr6Dst;
    }uaddrDst;/* �Զ�IP��ַ���˿ں� */
    CHAR *pData;        /* ָ��Mbuf���û����ݵ�ָ�� */
    ULONG ulDataLen;
    UCHAR ucControlCheckSum;
    UCHAR aucResv[3];
} UDPS_PACKET_INFO_S;

/* ������/��д�����ͽṹ���� */
typedef struct tagpgp_spinlock
{
    volatile VOS_UINT32 uiSlock; /* ���������� */
    VOS_UINT32 uiUnlockSGId : 6;
    VOS_UINT32 uiReserve    : 26;
    VOS_UINT64 ulTick;
}PGP_SPINLOCK_S;

/* ���������Ͷ���� */
#define PGP_SPINLOCK_ID   PGP_SPINLOCK_S

typedef struct tagDHCP_SERVER_STATUS_S
{
    PGP_SPINLOCK_ID stSpinLockId;

    UCHAR   ucPrimarySrvStatus:3;
    UCHAR   ucPrimarySrvTest:1;
    UCHAR   ucSecondarySrvStatus:3;
    UCHAR   ucSecondarySrvTest:1;
    UCHAR   ucPrimSrvTimerStatus;       /* ���÷�����״̬ɨ�趨ʱ��״̬ */
    UCHAR   ucPrimTimeoutNum;           /* �����������ϸ澯���� */
    UCHAR   ucSecTimeoutNum;            /* �����������ϸ澯���� */

    USHORT  usPrimTryTimeInterval;      /* ����������ΪTry��ʣ��ʱ�� */
    USHORT  usSecTryTimeInterval;       /* ����������ΪTry��ʣ��ʱ�� */

    UCHAR   ucPrimRequestTimeout;
    UCHAR   ucSecRequestTimeout;
    UCHAR   ucPrimaryAlarmFlag:1;       /* ���������Ѿ����͹���·�ϸ澯�ı�־ */
    UCHAR   ucSecondaryAlarmFlag:1;     /* �Ѿ����͹���·�ϸ澯�ı�־ */
    UCHAR   ucResBit:6;               /* �����ֶ� */
    UCHAR   ucReserve;            /* �����ֶ� */
}DHCP_SERVER_STATUS_S;


typedef enum UGW_NET_ELEMENT_ROLE_E
{
    E_NET_ELEMENT_ROLE_GGSN = 0,
    E_NET_ELEMENT_ROLE_PGW,
    E_NET_ELEMENT_ROLE_SGW,
    E_NET_ELEMENT_ROLE_PGW_AND_SGW,
    E_NET_ELEMENT_ROLE_HSGW,
    E_NET_ELEMENT_ROLE_PDSN,
    E_NET_ELEMENT_ROLE_BUTT
}UGW_NET_ELEMENT_ROLE_E;

#define M_LAP_DHCP_TBL_MAX_TUPLE_NUM       1000    /* CDB�������¼�� */
#define M_LAP_DHCP_TBL_IDX_NUM                1    /* CDB����������� */
#define M_LAP_DHCP_TBL_GROUP_IDX_ID           0    /*  ������� */
typedef enum
{
    M_LAP_DHCP_TBL_PRIMARY_SERVER_IP_FLD_ID    ,     /* CDB����ֶ�01��� */
    M_LAP_DHCP_TBL_SECONDARY_SERVER_IP_FLD_ID  ,     /* CDB����ֶ�02��� */
    M_LAP_DHCP_TBL_VPN_INDEX_FLD_ID            ,     /* CDB����ֶ�03��� */
    M_LAP_DHCP_TBL_SERVER_GROUP_NAME_FLD_ID    ,     /* CDB����ֶ�04��� */
    M_LAP_DHCP_TBL_LEASETIME_FLD_ID            ,     /* CDB����ֶ�05��� */
    M_LAP_DHCP_TBL_SERVER_GROUP_INDEX_FLD_ID   ,     /* CDB����ֶ�06��� */
    M_LAP_DHCP_TBL_VPN_NAME_FLD_ID             ,     /* CDB����ֶ�07��� */
    M_LAP_DHCP_TBL_IS_DHCPV6_FLD_ID            ,     /* CDB����ֶ�08��� */
    M_LAP_DHCP_TBL_RETRANSMIT_NUM_FLD_ID       ,     /* CDB����ֶ�09��� */
    M_LAP_DHCP_TBL_RETRANSMIT_TIMEOUT_FLD_ID   ,     /* CDB����ֶ�10��� */
    M_LAP_DHCP_TBL_RESERVE_FLD_ID              ,     /* CDB����ֶ�11��� */
    M_LAP_DHCP_TBL_BUTT
}E_LAP_DHCP_TBL_FLD;


/*GTPC��״̬���壬ע��ͬ���޸�g_ucStateMachineDescrip*/

typedef enum
{
    USM_IDLE = 0,                     /*����״̬*/
    USM_RADIUS_NEGO,            /*RADIUSЭ��״̬*/
    USM_IP_APPLY,                   /*�����ַ�ĵȴ�״̬*/
    USM_PCRFC_NEGO,
    USM_SM_NEGO,                    /* SMЭ�̵ĵȴ�״̬*/
    USM_ASN_NEGO,
    USM_CM_NEGO,                   /*CMЭ�̵ĵȴ�״̬*/
    USM_ACTIVE,                         /*����̬*/
    USM_PCRFC_UPDATE,
    USM_ASN_UPDATE,
    USM_CM_UPDATE,                  /*10*/       /*���µȴ�CM*//* Added by tangbenying at 2008-01-26 V9R7 for V9R7C1 */
    USM_PCRFC_DELETE,                 /*PCRFCɾ���ĵȴ�״̬*/
    USM_CM_DELETE,                   /*CMɾ���ĵȴ�״̬*/
    USM_WAIT_SGSN_DELETE,
    USM_WAIT_SGSN_UPDATE,
    USM_L2TP_IPCP_NEGO,             /*15*/
    USM_WAIT_PCRF_RAR_UPDATE,        /*Pcrfc����Rar���£��ȴ����³ɹ�״̬*/

    USM_DHCP_IP_APPLY,
    USM_WAIT_SGSN_INIT_RSP, /*�ȴ�SGSN����Initiate PDP Activation Response��Ϣ*/
    USM_WAIT_NW_CREATE,                   /*�ȴ�SGSN���������Ķ��μ���*/
    USM_END,
} E_GTPC_STATE_MACHINE_TYPE;

/* һ��״̬���� */
typedef enum tagAM_USM_L1_STATE_E
{
    E_AM_USM_L1_STATE_INIT,             /*����״̬*/
    E_AM_USM_L1_STATE_CREATE,           /*����״̬*/
    E_AM_USM_L1_STATE_ACTIVE,           /*����״̬*/
    E_AM_USM_L1_STATE_UPDATE,           /*����״̬*/
    E_AM_USM_L1_STATE_DELETE,           /*ɾ��״̬*/

    E_AM_USM_L1_STATE_BUTT              /*��Ч״̬*/
} AM_USM_L1_STATE_E;

/* ����״̬���壬ע����5��Ϊһ�飬������� */
typedef enum tagAM_USM_L2_STATE_E
{
    E_AM_USM_L2_STATE_INIT,             /*0 ��ʼ״̬*/

    E_AM_USM_L2_STATE_AUTH,             /*1 ��֤�ȴ�״̬*/
    E_AM_USM_L2_STATE_L2TP,             /*2 L2TP��������ȴ�״̬*/
    E_AM_USM_L2_STATE_LAP,              /*3 lap�����ַ��״̬*/
    E_AM_USM_L2_STATE_PCC,              /*4 PCC�ȴ�״̬*/
    E_AM_USM_L2_STATE_S6B,              /*5 S6B�ȴ�״̬*/
    E_AM_USM_L2_STATE_UGW,              /*6 �ȴ�PGW��SGW��Ӧ״̬*/

    E_AM_USM_L2_STATE_SM,               /*7 SM�ȴ�״̬*/
    E_AM_USM_L2_STATE_ASN,              /*8 ��ȡASN ���μƷ�����״̬*/
    E_AM_USM_L2_STATE_CM,               /*9 CM�ȴ�״̬*/

    E_AM_USM_L2_STATE_BUTT              /*10 ��Ч״̬*/
} AM_USM_L2_STATE_E;

/* AM�����ID��:300 */
#define CDB_AM_MIN_ID 50                        //50
#define CDB_AM_MAX_ID CDB_AM_MIN_ID + 300       //350

/*************************1.���в�Ʒ��̬��ʹ�õ�,��ID��Χ��0-10*************************/
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

/***************2.GUL��PDSN��Ʒ��̬ʹ�õı�,��ID�����CDB_AM_ALL_END_TBl_ID+1��ʼ***************/
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

/***************3.GUL��Ʒ��̬ʹ�õı�,��ID�����CDB_AM_GUL_PDSN_END_TBl_ID+1��ʼ ��125��***************/
typedef enum enE_CDB_AM_GUL_TBL
{
    CDB_APN_NBNS_TBL_ID = CDB_AM_GUL_PDSN_END_TBl_ID + 1, //74
    M_AM_BATCH_DEACTIVE_RATE_TBL_ID,//75
    M_AM_GOM_HOMEZONE_CONNECTION_TBL_ID,//76
    M_AM_GOM_HOMEZONE_GROUP_TBL_ID,//77
    M_AM_GOM_HOMEZONE_SERVER_TBL_ID,//78
    M_AM_IMSIINSTANCE_BUILDING_TBL_ID,//79
    M_AM_INTELLIGENT_SELECT_DEFAULT_TBL_ID,//80

    M_AM_INTELLIGENT_SELECT_TBL_ID,//81
    M_AM_LOCAL_LOCATION_TRIGGER_ID,
    M_AM_PCRFC_APN_IMS_SWITCH_CFG_TBL_ID,
    M_AM_PCRFC_APN_IMSSIGFILTER_CFG_TBL_ID,
    M_AM_PCRFC_P_CSCF_GROUP_TBL_ID,

    M_AM_PCRFC_PCC_IMS_SWITCH_CFG_TBL_ID,//86
    M_AM_PCRFC_PCC_IMSSIGFILTER_CFG_TBL_ID,
    M_AM_PCRFC_PCSCFGROUP_BIND_APN_TBL_ID,
    M_AM_PCRFC_PCSCFGROUP_BIND_PCC_TBL_ID,
    M_AM_SGSN_ACCESS_LIST_SWITCH_TBL_ID,

    M_AM_SGSN_ACCESS_LIST_TBL_ID,//91
    M_AM_SGSN_ACCESS_LIST_TYPE_TBL_ID,
    M_AM_SGSN_SCI_CTRL_TBL_ID,
    M_APN_UE_HEART_BEAT_INFO_TBL_ID,
    M_EPRPDYN_ATTR_TBL_ID,

    M_GM_IPPM_ALARM_THRESHOLD_TBL_ID,//96
    M_GM_IPPM_CONFIG_TBL_ID,
    M_GM_IPPM_GLOBAL_TBL_ID,
    M_GM_IPPM_PERF_TBL_ID,
    M_GM_IPSQM_LOCK_PEU_TBL_ID,

    M_GM_IPSQM_PATHSHAPPING_TBL_ID, //101
    M_GM_IPSQM_PORTSHAPPING_TBL_ID,
    M_GTPC_ASN_CONFIGURATION_TBL_ID,
    M_GTPC_ASN_FUNCTION_TBL_ID,
    M_HZ_SOURCEID_TBL_ID,

    M_IP_SPOOFING_CFG_TBL_ID,//106
    M_LAP_BLACK_LIST_TBL_ID,
    M_LAP_DHCP_TBL_ID,
    M_LI_X1AUTH_TBL_ID,
    M_MBMS_CTEID_TBL_ID,

    M_NW_ENABLERGROUP_TBL_ID, //111
    M_NW_ENABLERINFO_TBL_ID,
    M_NW_HSFUNCTION_TBL_ID,
    M_NW_NWCLIENTIP_TBL_ID,
    M_NW_NWFUNCTION_TBL_ID,

    M_NW_NWSAMPLING_TBL_ID,//116
    M_NW_RETRYINTERVAL_TBL_ID,
    M_OS_APN_COMUSER_TBL_ID,
    M_OS_L2TP_GROUP_INTERFACE_TBL_ID,
    M_PCRFC_DEFAULT_P_CSCF_GROUP_TBL_ID,

    M_RCS_APN_DNS_TBL_ID,//121
    M_SC_ACCESS_CTRL_DEGREE_TBL_ID,
    M_SC_APN_ABNORMAL_CTRL_TBL_ID,
    M_SC_APN_CLIENT_IP_TBL_ID,
    M_SC_APN_COMMON_TBL_DEFAULT_FLD_ID,

    M_SC_APN_CONTROL_TBL_ID,//126
    M_SC_APN_INTERFACE_TBL_ID,
    M_SC_APN_NAS_IP_TBL_ID,
    M_SC_APN_PERF_TBL_ID,
    M_SC_APN_PRIORITY_CONTROL_TBL_ID,

    M_SC_APN_ROUTE_TBL_ID,//131
    M_SC_APNQOS_CFG_TBL_ID,
    M_SC_APNQOS_MAPINFO_TBL_ID,
    M_SC_ARP_CFG_TBL_ID,
    M_SC_ARP_PRI_MAPPING_TBL_ID,

    M_SC_COMMEND_SOLT_CPU_TBL_ID,//136
    M_SC_DEFAULT_SGSN_NODE_TBL_ID,
    M_SC_DHCPS_EXPIRED_TBL_ID,
    M_SC_DHCPS_FUNCTION_TBL_ID,
    M_SC_DHCPS_OPTION_TBL_ID,

    M_SC_DIFFSRV_FUNCTION_TBL_ID,//141
    M_SC_DIFFSVR_CFG_BW_THRESHOLD_TBL_ID,
    M_SC_DIFFSVR_CFG_PDP_THRESHOLD_TBL_ID,
    M_SC_GATEWAY_PROXY_TBL_ID,
    M_SC_GTP_PROTOCOL_TBL_ID,

    M_SC_HOMEGATEWAY_TBL_ID,//146
    M_SC_HOMEGATEWAYGROUP_TBL_ID,
    M_SC_HOMEIMSIMSISDNGROUP_TBL_ID,
    M_SC_LOCATION_REPORTING_TIMER_CTRL_TBL_ID,
    M_SC_MBMS_BMSC_CFG_TBL_ID,

    M_SC_MBMS_BMSCGROUP_CFG_TBL_ID,//151
    M_SC_MBMS_LOCAL_CFG_TBL_ID,
    M_SC_MBMS_PARA_CFG_TBL_ID,
    M_SC_MCC_MNC_TBL_ID,
    M_SC_MCC_MNCLENGTH_TBL_ID,

    M_SC_PATH_ALARM_THRESHOLD_TBL_ID,//156
    M_SC_PLMN_PRIORITY_CFG_TBL_ID,
    M_SC_PMIP_TBL_ID,
    M_SC_PUBLICAPN_TBL_ID,
    M_SC_QOS_CAR_TBL_ID,

    M_SC_QOS_CFG_TBL_ID,//161
    M_SC_QOS_FUNCTION_TBL_ID,
    M_SC_QOS_MAPINFO_TBL_ID,
    M_SC_QOS_PROFILE_TBL_ID,
    M_SC_QOS_REMARK_TBL_ID,

    M_SC_QOS_SHAPE_TBL_ID,//166
    M_SC_QOS_VER_TRANS_RULE_TBL_ID,
    M_SC_RAT_PRIORITY_CFG_TBL_ID,
    M_SC_S6B_AAA_HOST_INFO_TBL_ID,
    M_SC_S6B_DIAMSVR_GROUP_TBL_ID,

    M_SC_S6B_LOCALINFO_TBL_ID, //171
    M_SC_SERVER_GROUP_ACCEPT_ATTR_TBL_ID,
    M_SC_SERVER_GROUP_AUTH_3GPP_VSA_TBL_ID,
    M_SC_SERVER_GROUP_AUTH_ATTR_TBL_ID,
    M_SC_SERVER_GROUP_TBL_ID,

    M_SC_SGSN_PLMN_NODE_TBL_ID,//176
    M_SC_SGSN_RAT_NODE_TBL_ID,
    M_SC_SUB_QOS_TBL_ID,
    M_SC_TRAFFIC_CLASS_TBL_ID,
    M_SC_UGW_APNQOS_MAPINFO_TBL_ID,

    M_SC_UGW_GLOBALQOS_MAPINFO_TBL_ID,//181
    M_SC_UGW_QOS_DEFAULTVALUE_TBL_ID,
    M_SC_UGW_QOS_GLOBAL_ARPQCIMAPPING_TBL_ID,
    M_SC_UGW_QOS_GLOBAL_EXTENDQCI_TBL_ID,
    M_SC_UGW_QOS_GLOBAL_EXTQCIMAPPING_TBL_ID,

    M_SC_UGW_QOS_GLOBAL_QCILEVEL_TBL_ID,//186
    M_SC_UGW_QOS_GLOBAL_QCIPRIORITY_TBL_ID,
    M_SC_UGW_QOS_MAP_QCI2TRAFFICCLASS_TBL_ID,
    M_SC_UP_DOWN_BAND_RATE_TBL_ID,
    M_SC_USERRUNNING_TBL_ID,

    M_SC_VIP_MANAGE_FUNCTION_TBL_ID,//191
    M_SC_VIP_QOS_MAPINFO_TBL_ID,
    M_SC_VIP_RESERVE_BANDWIDTH_TBL_ID,
    M_VIRTUALAPN_DFCFG_TBL_ID,
    M_SC_S6B_GROUP_S6B_ATTR_TBL_ID,

    M_SC_S6B_PGWHOSTNAME_TBL_ID,
    M_SC_PATH_PMIPV6_HEARTBEAT_TBL_ID,
    M_SC_UGW_TO2_TBL_ID,
    M_AM_UDP_CHECKSUM_TBL_ID,
    M_SC_EPC_GW_TBL_ID,

    M_LI_TARGET_FOR_SPUF1_TBL_ID,//201
    M_LI_TARGET_FOR_SPUF_TBL_ID,
    M_PATH_ECHO_LIST_SWITCH_TBL_ID,
    M_PATH_ECHO_LIST_TYPE_TBL_ID,
    M_PATH_ECHO_LIST_IP_TBL_ID,

    M_OS_L2TP_DEFAULT_ATTRIBUTE_TBL_ID,
    M_AM_UGW_DDN_FLOW_CONTROL_TBL_ID,
    M_SC_VIP_SWITCH_FUNCTION_TBL_ID,

    /* Added start by jiexianzhu at 2013.12.16 for ����ӳ�� VLRID/GT */
    M_SC_TRANSPARENT_TBL_ID,
    M_SC_PLMN_TRANSPARENT_TBL_ID,
    M_SC_DEFAULT_TRANSPARENT_TBL_ID,
    /* Added end by jiexianzhu at 2013.12.16 for ����ӳ�� VLRID/GT */
    /* Added start by jiexianzhu at 2014.01.15 for overload control */
    M_SC_SDU_OVERLOAD_CTRL_TBL_ID,
    /* Added end by jiexianzhu at 2013.01.15 for overload control */

    M_SC_HOMEGROUPBINDAPN_TBL_ID,  /*211*/

    M_MSG_CON_RESEND_SW_FUNCTION_TBL_ID,
    M_SC_ACCESS_REACTIVATION_REQ_DEL_TBL_ID,
    M_SC_LACGROUP_TBL_ID,  /*213*/
    M_SC_TACGROUP_TBL_ID,  /*214*/
    M_SC_LACTACRAC_SECTION_TBL_ID,    /*215*/
    M_SC_RACGROUP_TBL_ID,  /*216*/
    M_SC_SPECIFICAPNVALUE_TBL_ID, /* 217 */

    M_SC_CPU_UPDATARATE_TBL_ID,
    M_SC_ENGIN_REACTIVATION_REQ_DEL_TBL_ID,
    CDB_AM_GUL_END_TBL_ID = CDB_AM_MAX_ID,
}E_CDB_AM_GUL_TBL;

#define PMBUF_GET_TOTAL_DATA_LENGTH(pstMBufM) ( (pstMBufM)->ulTotalDataLength )
#define PMBUF_GET_DATA_BLOCK_NUMBER(pstMBufM) ( (pstMBufM)->ulDataBlockNumber )

typedef struct tagMBUF_USERTAGDATA_S
{
    ULONG ulVrfIndex;
    ULONG ulIfIndex;
} MBUF_USERTAGDATA_S;

#define PMBUF_S_RES_SIZE 4

typedef struct tagMBUF_DataBlockDescriptor
{
    ULONG ulDataLength;         /* ���ݿ������ݵĳ��ȣ�ȡֵ��Χ[0, ulDataBlockLength]*/
    UCHAR * pucData;            /* ���ݿ������ݵ���ʼ��ַ, [pucDataBlock + 512, pucDataBlock + ulDataBlockLength]*/
    ULONG ulDataBlockLength;    /* ���ݿ���ܳ���,*/
    UCHAR * pucDataBlock;       /* ���ݿ����ʼ��ַ�� NULL��ʾ��Ч��������ʾ��Ч */
    ULONG ulType;               /* MBUF_TYPE_XXX */
    struct tagMBUF_DataBlockDescriptor * pstNextDataBlockDescriptor;/* ��һ�����ݿ��������� Always NULL*/
}MBUF_DATABLOCKDESCRIPTOR_S,SM_MBUF_DATABLOCKDESCRIPTOR_S;    /* ���ݿ����������ݽṹ */

typedef struct tagMBuf
{
    struct tagMBuf * pstNextMBuf;                       /* ��һ��mbuf�� NULL��ʾ��Ч��������ʾ��Ч */
    ULONG ulTotalDataLength;                            /* mbuf �����ݵ��ܳ��ȣ�ͬһ��MBUF�е��������ݵĳ��Ⱥ� */
    MBUF_DATABLOCKDESCRIPTOR_S stDataBlockDescriptor;   /* Mbuf ����������Ϣ */
    ULONG ulDataBlockNumber;                            /* mbuf �����ݿ�ĸ��� */
    MBUF_USERTAGDATA_S stUserTagData;                   /* Mbuf ������Ϣ */
    ULONG ulResv[PMBUF_S_RES_SIZE];
    ULONG ulMagicWord;
}MBUF_S, PMBUF_S, SM_MBUF_S, TP_PMBUF_S;  /* mbuf��ͷ��ǩ���ݽṹ */

typedef struct tagPTM_COMPONENT_INFO
{
    VOS_UINT64 ullSelfCsi;      /* �����CSI */
    VOS_UINT64 ullSelfSgId;     /* ���������SGID */
    VOS_UINT32 ulSelfCmpIdx;    /* OS��ͬ����������� */
    VOS_UINT32 ulSelfCmpIdxInSG;/* SG��ͬ����������� */
    VOS_UINT32 ulHandle;        /* HANDLE�����ڵ��� */
    USHORT usOsID;               /* ע��:��һ������ģ�鶼��ʼ���� */
    USHORT usReserve990;
}PTM_COMPONENT_INFO_S;

/** SPU����Ӳ�����Ͷ��� */
typedef enum tagCRM_SPU_BOARD_TYPE_ENUM
{
    CRM_BOARD_TYPE_UNKNOWN = 0,  /**< δ��ȡ������չ���ͣ�Ϊδ֪���� */
    CRM_BOARD_TYPE_SPUD,         /**< SPUD�壨������TCAM�ۿ��� */
    CRM_BOARD_TYPE_SPUE,         /**< SPUE�� */
    CRM_BOARD_TYPE_PEU,          /**< PEU�� */
    CRM_BOARD_TYPE_SPUF,
    CRM_BOARD_TYPE_MSU,          /**< MSU�� */
    CRM_BOARD_TYPE_SPUF1,
    CRM_BOARD_TYPE_MSUF1,
    CRM_BOARD_TYPE_MAX,           /**< ��ЧӲ������ */
}  CRM_SPU_BOARD_TYPE_ENUM ;

#define M_CDB_MAX_FIELD_LENGTH   (256 * 2)

typedef struct
{
    VOS_UINT8  ucOper;
    VOS_UINT32 udwFieldId;
    VOS_INT8   aValue[M_CDB_MAX_FIELD_LENGTH];
} S_CFG_CDB_CONDITION;

typedef struct
{
    ULONG  ulTick;     /* �ϱ�������TICK�� */
    DATE_T stDate;
    TIME_T stTime;
}VOS_PACKED S_FAM_BAM_TRC_TIME_DATA;

/*add by lixueli @20090917 --- start*/
#ifndef VOS_TIMER_LOOP
#define VOS_TIMER_LOOP 0x1
#endif

#define M_CFG_CDB_EQUAL             0


/* SDB������ */
typedef enum tagSDB_RETURNCODE_E
{
    SDB_SUCCESS              = 0,                     /* �ɹ����� */
    SDB_INVALID_INPUT        = 1,                     /* ����Ƿ� */
    SDB_RECORD_NOT_EXIST     = 2,                     /* δ�鵽��Ӧ��¼ */
    SDB_RECORD_EXIST         = 3,                     /*��ѯ��¼�Ѿ����� */
    SDB_TABLE_FULL           = 4,                     /* ������(�޼�¼�ɷ���) */
    SDB_INIT_FAILURE         = 5,                     /* ��ʼ��ʧ�� */
    SDB_INCONSISTENT         = 6,                     /* �Ƚϲ�һ�� */
    SDB_FIND_IDLE_RECORD     = 7,                     /* ��¼���� */
    SDB_INVALID_MSG          = 8,                     /* �Ƿ���Ϣ */
    SDB_EMPTY_HASH_CHAIN     = 9,                     /* �չ�ϡ��ͻ�� */
    SDB_SYSTEM_FAILURE       = 10,                     /* SDBģ���������� */
    SDB_CONTINUED_TO_SEARCH   = 11,
    NO_LICENSE =12 ,
    SDB_APN_USERCONTROL 	 = 13,					   /* APN�û�������δͨ��*/
    SDB_APN_BANDCONTROL 	 = 14,					   /* APN��������δͨ�� */
    SDB_TRAFFIC_CLASS_BANDCONTROL 	 = 15,			   /* Traffic Class��������δͨ�� */
    SDB_APN_SPU_BANDCONTROL 	 = 16,			          /* �����������δͨ�� */
    SDB_IP_CONFLICT            =  17,                   /*IP��ַ��ͻ*/
    SDB_DIFFSRV_REACH_APN_PDPNUM_TC_REJTHRD = 20,
    SDB_DIFFSRV_REACH_APN_PDPNUM_GENERAL_REJTHRD = 21,
    SDB_DIFFSRV_REACH_GLOB_PDPNUM_TC_REJTHRD = 22,
    SDB_DIFFSRV_REACH_GLOB_PDPNUM_GENERAL_REJTHRD =  23 ,
    SDB_DIFFSRV_REACH_APN_BANDWIDTH_TC_REJTHRD = 24,
    SDB_DIFFSRV_REACH_APN_BANDWIDTH_GENERAL_REJTHRD = 25,
    SDB_IMS_USER_NO_LICENSE   = 40,
    SDB_WHOLE_THROUTPUT_NO_LICENSE = 41,
    SDB_DIFFSRV_REACH_REJECT_THRESHOLD  =  100,
    SDB_DHCP_PARA_ERROR = 0xFF + 1, /* DHCP���ز�������*/
    SDB_DHCP_POOL_ERROR = 0xFF + 2,     /* DHCP���ص�ַ�ش���*/
    SDB_DHCP_NO_IP_AVAILABLE = 0xFF + 3, /*�޿��õ�ַ����*/
    SDB_DMT_NO_RECORD        = 28101,                 /* DMT��ѯ��¼������ */
    SDB_DMT_INVALID_INPUT    = 28102,                 /* DMT��ѯ���������Ч */
    SDB_FAILURE,
    SDB_NOT_ALLOW_CREATE_RANDOM_SDB,
    SDB_RETURNCODE_BUTT      = 0xffffffff             /* ������־ */

}SDB_RETURNCODE_E;

#define PTM_LOG_CNT_PREFIX_NAME_MAX_LEN  31 /* ����ǰ׺������󳤶� */

typedef struct PTM_LogCnt_RecRegInfo
{
    UINT64  ul64ComCsi;             /* ���CSI,������ʱ��ʱʹ�� */
    ULONG   **ppulCntAddr;          /* �������������Ԫ��ʼ��ַ������ */
    VOID    (*pPreCallBack)();      /* ��ӡ����ǰ,�ص����� */
    ULONG   (*pIsReady)();          /* �ж��Ƿ���Կ�ʼ��ӡ */

    ULONG   ulDBGLogRegId;                                          /* д�����־��ID */
    ULONG   ulComHandle;            /* ���Handle,���������ڴ� */
    UCHAR   aucPrefixName[PTM_LOG_CNT_PREFIX_NAME_MAX_LEN + 1];     /* �������ǰ׺���� */
    ULONG   ulTotalCntElemNum;      /* һ����������Ԫ����Ԫ�ظ��� */
    ULONG   ulCntUnitNum;           /* ��������Ԫ�ĸ��� */
    ULONG   ulTimeMsgType;          /* ������ʱ��ʱ�������Ϣ����  */
    ULONG   ulIsTimerSupport;       /* ע���������,�Ƿ�֧�ִ���ʱ��Ϣ. VOS_TRUE VOS_FALSE
                                     * ��֧��ҪдVOS_FALSE��������ܻ���ɼ����޷���ӡ��־ */
}PTM_LogCnt_RecRegInfo_S;


typedef enum
{
    PTM_BATCH_CMD_RSP_CONTINUE,
    PTM_BATCH_CMD_RSP_END,
    PTM_BATCH_CMD_RSP_ARGUMENT_NUM_ERR,
    PTM_BATCH_CMD_RSP_KEYWORD_ERR,
    PTM_BATCH_CMD_RSP_ARGUMENTS_ERR,
} PTM_BATCH_CMD_RSP_E;


#define GTP_DHCP_ALLOC_ADDR         4   /* DHCP�����������ַ(B01��֧��) */

enum enumRTDPRI
{
    RTD_PRIORITY_HIGH   = 0x1,/* ������и����ȼ� */
    RTD_PRIORITY_MIDDLE = 0x2,/* ������������ȼ� */
    RTD_PRIORITY_LOW    = 0x4,/* ������е����ȼ� */
};

/*-------------------------- BEGIN: Mbuf ------------------------------------*/
#define PMBUF_MIN(a,b) (((a) < (b)) ? (a) : (b))
#define PMBUF_MTOD(pstMBufM, DataTypeM) ( (DataTypeM)(pstMBufM)->stDataBlockDescriptor.pucData)
#define PMBUF_TYPE_DATA             1

/*************************************************************************************/
/*                                ������ע��                                         */
/*************************************************************************************/
#define LINELENGTH 80

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


#define GTPC_SND2_LAP_CNT_COUNT 200

/* �������ȼ����� */
typedef enum tag_URTD_Priority_Type
{
    URTD_PRIORITY_HIGH,      /* ������и����ȼ� */
    URTD_PRIORITY_LOW,       /* ������е����ȼ� */
    URTD_PRIORITY_MAX_NUM
}URTD_Priority_Type_S;

#define M_EMS_TRC_SEND_MSG    0
#define M_EMS_TRC_RECV_MSG    1

#define  GTPC_GUSER_MSGTYPE_DHCPV4               0x21
#define  GTPC_GUSER_MSGTYPE_DHCPV6               0x22

#define  TRC_DIRECTION_LEFT_IN_SGW          0x000
#define  TRC_DIRECTION_RIGHT_OUT_SGW        0x100
#define  TRC_DIRECTION_LEFT_IN_PGW          0x200
#define  TRC_DIRECTION_LEFT_IN_PGW_PMIP     0x210

#define  TRC_DIRECTION_DHCPV6_IN_PGW          0x1000
#define  TRC_DIRECTION_DHCPV6_OUT_PGW         0x1100

#define  TRC_DIRECTION_DHCPV6_IN_GGSN         0x1200
#define  TRC_DIRECTION_DHCPV6_OUT_GGSN        0x1300

#define  TRC_DIRECTION_DHCPV6_IN_SGW          0x1400
#define  TRC_DIRECTION_DHCPV6_OUT_SGW         0x1500

#define  GUSER_MSGTYPE_DHCPV4           0x0200
#define  GUSER_MSGTYPE_DHCPV6           0x0400


#define M_PTM_QUE_NAME_LEN  31

typedef struct tagPTM_QUEUE_INFO
{
    VOS_UINT64 ullSelfCsi;
    VOS_UINT32 ulMsgType;
    VOS_UINT32 ulQueType;
    VOS_UINT32 ulQueLen;
    VOS_UINT32 ulEvent;
    VOS_UINT32 ulTaskId;
    VOS_CHAR szQueName[M_PTM_QUE_NAME_LEN + 1];
}PTM_QUEUE_INFO_S;

typedef enum enMSG_QUE_TYPE_E
{
    MSG_QUETYPE_MCQ = 1,
    MSG_QUETYPE_VOSQ,
    MSG_QUETYPE_LFQ,
    MSG_QUETYPE_DMSQ,
}MSG_QUE_TYPE_E;

/* ��ʱ���¼�λ */
#ifndef VOS_TIMER_EVENT
#define VOS_TIMER_EVENT                 (1 << 15 )
#endif

//��������Ƿ���⻹Ҫ�ٿ�һ�£����pgp_id.h������Ϊ�ӿ��ļ�����������Ƶ�pgp_id.h��
/******************************************************************************/
/*                PS COMPONONT Definition                                         * /
/******************************************************************************/
enum enumPSCompType
{
    COMP_T_PSSTART = 3256,      /* !!!!!���￪ʼPSʹ�� */
    COMP_T_PSEND = 3511         /* ǰ���Ʒʹ�� */
};

//3256~3409Ϊ����ҵ��ʹ�õ����id��Χ��
#define M_PS_COMP_TYPE_BASE COMP_T_PSSTART
//Cyjun: ƽ̨UFP�������涨�壬��ȷ��
//#define M_PS_COMP_TYPE_BASE 3100

//3410-3512Ϊ��ֵ��ҵ��ʹ�õ����id��Χ������VOG/HOSTING/SBR�����Ǻ���UGW/SCCG/PDSN/WASN����ʹ�ô˶Σ��������ิ�á�
#define M_PS_VAS_COMP_TYPE_BASE (M_PS_COMP_TYPE_BASE + 154)


/* !!!ö��˳�򲻿������޸ģ������SPUCFGһ�£�Ŀǰ������������������鲻����������!!! */
/* ʵ��������ͣ��ڴ˶����������ͻ�ֱ��Ӱ��ҵ��Ĳ��𣬻�д�뵽spucfg�� */
typedef enum enCOMP_TYPE_E
{
    // ========================= ������� ================================
    // AM���
    E_COMP_TYPE_USM  = M_PS_COMP_TYPE_BASE,   /* ���㣬����ֵ���� */
    E_COMP_TYPE_SDUA, //3257
    E_COMP_TYPE_SDU, //3258
    E_COMP_TYPE_SD, //3259
    E_COMP_TYPE_CKPA, //3260
    E_COMP_TYPE_CKPC, //3261
    E_COMP_TYPE_GRMA, //3262
    E_COMP_TYPE_GTRC, //3263
    E_COMP_TYPE_USM_SRU, //3264
    E_COMP_TYPE_MASTERM, //3265
    E_COMP_TYPE_AM_SCCG_CDB,
    E_COMP_TYPE_NWCENTER, //3267
    E_COMP_TYPE_NWA, //3268

    // CM ���
    E_COMP_TYPE_CMCR, //3269
    E_COMP_TYPE_GACT, //3270
    E_COMP_TYPE_GAAG, //3271
    E_COMP_TYPE_CDRF, //3272
    E_COMP_TYPE_CMOC, //3273
    E_COMP_TYPE_OCSC, //3274
    E_COMP_TYPE_OCGM, //3275
    E_COMP_TYPE_PCSD, //3276
    E_COMP_TYPE_DIAM, //3277
    E_COMP_TYPE_PCSM, //3278
    E_COMP_TYPE_PCCR, //3279
    E_COMP_TYPE_CMAC, //3280
    E_COMP_TYPE_ACCT, //3281
    E_COMP_TYPE_CM_STG, //3282
    E_COMP_TYPE_SRU_CDRF, //3283
    E_COMP_TYPE_CM_GOM, //3284
    E_COMP_TYPE_SRU_ACCT, //3285
    E_COMP_TYPE_ICPM, //3286
    E_COMP_TYPE_CM_PCRFC_GOM, //3287
    E_COMP_TYPE_CM_SRU_POSTPAID, //3288

    // PTM���
    E_COMP_TYPE_PRPC, //3289
    E_COMP_TYPE_ASN, //3290
    E_COMP_TYPE_PAGP, //3291
    E_COMP_TYPE_CPATH, //3292
    E_COMP_TYPE_PAPI, //3293
    E_COMP_TYPE_PAGM, //3294
    E_COMP_TYPE_L2TT, //3295
    E_COMP_TYPE_PPPT, //3296
    E_COMP_TYPE_IPV6, //3297
    E_COMP_TYPE_AUTH, //3298
    E_COMP_TYPE_AAAGM, //3299
    E_COMP_TYPE_S6B, //3300
    E_COMP_TYPE_POD, //3301
    E_COMP_TYPE_GLAP2, //3302
    E_COMP_TYPE_LAP1, //3303
    E_COMP_TYPE_LAPSC, //3304
    E_COMP_TYPE_CLAP, //3305
    E_COMP_TYPE_DHCPC, //3306
    E_COMP_TYPE_DHCPCGM, //3307
    E_COMP_TYPE_DSV4, //3308
    E_COMP_TYPE_DSV6, //3309
    E_COMP_TYPE_IPPMSRU, //3310
    E_COMP_TYPE_IPPMSPU, //3311
    E_COMP_TYPE_IPPMPEU, //3312
    E_COMP_TYPE_GMBMS, //3313
    E_COMP_TYPE_CMBMS, //3314
    E_COMP_TYPE_LIX1, //3315
    E_COMP_TYPE_LIX2, //3316
    E_COMP_TYPE_LIX3, //3317
    E_COMP_TYPE_X2PA, //3318
    E_COMP_TYPE_X3PA, //3319
    E_COMP_TYPE_X2SE, //3320
    E_COMP_TYPE_X3SE, //3321
    E_COMP_TYPE_LISC, //3322
    E_COMP_TYPE_LIGM, //3323
    E_COMP_TYPE_HZT, //3324
    E_COMP_TYPE_SRUMBMS, //3325
    E_COMP_TYPE_PTMAPP, //3326
    E_COMP_TYPE_NW_HANDSHAKE, //3327
    E_COMP_TYPE_S6BM, //3328
    E_COMP_TYPE_PTM_RESERVED3, //3329
    E_COMP_TYPE_PTM_RESERVED4, //3330

    // IPN���
    E_COMP_TYPE_RPT, //3331
    E_COMP_TYPE_ICAP, //3332
    E_COMP_TYPE_SOMT, //3333
    E_COMP_TYPE_SOMS, //3334
    E_COMP_TYPE_SOM0, //3335
    E_COMP_TYPE_SPE, //3336
    E_COMP_TYPE_ASPE, //3337
    E_COMP_TYPE_ACCESS, //3338
    E_COMP_TYPE_SM_GOM, //3339
    E_COMP_TYPE_SM_RESERVED1, //3340
    E_COMP_TYPE_SM_RESERVED2, //3341
    E_COMP_TYPE_SM_RESERVED3, //3342
    E_COMP_TYPE_SM_RESERVED4, //3343
    E_COMP_TYPE_SM_RESERVED5, //3344

    // AM���2
    E_COMP_TYPE_AM_SEG2 = 3345,
    E_COMP_TYPE_AM_TDFI,

    // HSGW��Ʒ���
    E_COMP_TYPE_CM_SRU_PREPAID = 3349, //3349
    E_COMP_TYPE_PDSNKERNEL, //3350
    E_COMP_TYPE_POSTPAID,   //3351
    E_COMP_TYPE_PREPAID,    //3352
    E_COMP_TYPE_CONTENT,    //3353
    E_COMP_TYPE_PDSNACCT,   //3354
    E_COMP_TYPE_TIMER,      //3355
    E_COMP_TYPE_RESV,       //3356
    E_COMP_TYPE_DIAMAUTH,   //3357
    E_COMP_TYPE_FA,         //3358
    E_COMP_TYPE_CMPM,       //3359
    E_COMP_TYPE_CSN,        //3360
    E_COMP_TYPE_DNSC,       //3361
    E_COMP_TYPE_HSGW_PMIPV6,//3362
    E_COMP_TYPE_HSGW_STACFG,//3363
    E_COMP_TYPE_CMPTHREAD,  //3364

    // PTM���2
    E_COMP_TYPE_PTM_SEG2 = 3375,
    E_COMP_TYPE_DEBUG,      //3376

    // CM���2
    E_COMP_TYPE_CM_SEG2 = 3390,
    E_COMP_TYPE_CM_FC, //3391
    //E_COMP_TYPE_CM_FC_TRY, //3392

    // IPN���
    E_COMP_TYPE_IPN_SEG2 = 3400,

    // ========================= ��ֵҵ����� ================================
    /*MSD�����*/
    E_COMP_TYPE_MSD_SDI = M_PS_VAS_COMP_TYPE_BASE, //3410
    E_COMP_TYPE_MSD_SDE,     //3411
    E_COMP_TYPE_MSD_SOMT,    //3412
    E_COMP_TYPE_MSD_SOM0,    //3413
    E_COMP_TYPE_MSD_SMAGENT, //3414
    E_COMP_TYPE_MSD_TCPP,    //3415

    E_COMP_TYPE_MSD_SDUA,    //3416
    E_COMP_TYPE_MSD_SDU,     //3417
    E_COMP_TYPE_MSD_UPM,     //3418
    E_COMP_TYPE_MSD_GRMA,    //3419

    E_COMP_TYPE_MSD_SOM,     //3420
    E_COMP_TYPE_PRO_DPSO,    //3421

    /*MSU�����*/
    E_COMP_TYPE_VAS_SDUA,   //3422
    E_COMP_TYPE_VAS_SDU,    //3423
    E_COMP_TYPE_VOG_UPM,    //3424
    E_COMP_TYPE_VOG_GRMA,   //3425
    E_COMP_TYPE_VOG_RPT,    //3426
    E_COMP_TYPE_VOG_SOM,    //3427
    E_COMP_TYPE_VOG_OMA,    //3428
    E_COMP_TYPE_PGP_SOCKET, //3429
    E_COMP_TYPE_VOG_ME,     //3430
    E_COMP_TYPE_VOG_TCC,    //3431
    E_COMP_TYPE_VOG_OFFTC,  //3432
    E_COMP_TYPE_VOG_TCS,    //3433

	// OTHERS
	E_COMP_TYPE_VBS = 3511,  // HUTAF_COVERAGE


    E_COMP_TYPE_NUM,
}DHCP_COMP_TYPE_E;

/************************* MACRO & TYPE DEFINITION ***************************/
/**
* @ingroup  v_mcque
*
* ����ID���Ͷ��塣
*/
typedef VOS_VOID* MC_QUE_ID;


typedef enum  enAM_USM_QUE_TYPE_E
{
    E_AM_USM_QUE_START = M_PS_MSG_TYPE_BASE,
    E_AM_USM_QUE_SD_UPDATE,         /* ���յ�SD ��GTP���¶��У���ӦQGTPUPDSC%02lu ���� */
    E_AM_USM_QUE_SD_DELETE,         /* ���յ�SD ��GTPȥ����У���ӦQGTPDEASC%02d ���� */
    E_AM_USM_QUE_SD_RESPONSE,       /* ���յ�SD ��GTP��Ӧ���У���ӦQGTPRSPSC%02d ���� */
    E_AM_USM_QUE_SD_MSINFO,         /* ���յ�SD ��ms info change notification request���У���ӦQMSCSC%02d ���� */
    E_AM_USM_QUE_SD_VIP_CREATE,     /* ���յ�SD ��GTP VIP�û�������¶��У���ӦQVIPSC%02d ���� */
    E_AM_USM_QUE_SD_VIP_DELETE,     /* ���յ�SD ��GTP VIP�û�ȥ����У���ӦQVIPDSC%02d ���� */
    E_AM_USM_QUE_SD_SECOND,         /* ���յ�SD ��GTP ���μ�����У���ӦQSECACTSC%02d ���� */
    E_AM_USM_QUE_SD_CREATE1,        /* ���յ�SD ��GTP �û��������֮���ȼ�1����ӦQACTP1SC%02d ���� */
    E_AM_USM_QUE_SD_CREATE2,        /* ���յ�SD ��GTP �û��������֮���ȼ�2����ӦQACTP2SC%02d ���� */
    E_AM_USM_QUE_SD_CREATE3,        /* ���յ�SD ��GTP �û��������֮���ȼ�3����ӦQACTP3SC%02d ���� */
    E_AM_USM_QUE_SD_CREATE4,        /* ���յ�SD ��GTP �û��������֮���ȼ�4����ӦQACTP4SC%02d ���� */
    E_AM_USM_QUE_SD_CREATE5,        /* ���յ�SD ��GTP �û��������֮���ȼ�5����ӦQACTP5SC%02d ���� */
    E_AM_USM_QUE_SD_ERR_INDICATION, /* ���յ�SD ��Error Indication���У���ӦQV0V1ERRSC%02d ���� */
    E_AM_USM_QUE_SD_GENERAL,        /* ���յ�SD ��General���У���ӦSGENSC%02d ���� */
    E_AM_USM_QUE_SD_DELETE_TEID0,   /* SDU�ַ���SD��TEIDCΪ0��ȥ������Ϣ����ӦQDEACTIVESC%02d ���� */
    E_AM_USM_QUE_SD_PMIP,           /* SD�ַ�PMIP����Ϣ����Ӧ QPMIP%02lu����*/

    E_AM_USM_QUE_SC_GTPV2_MSG,      /* SC�Ͻ��յ�GTPv2�ڲ���Ϣ���У���ӦU_GTPV2 ���� */
    E_AM_USM_QUE_SC_GTPV2_SELF_MSG, /* SC�Ͻ��յ�GTPv2�ڲ���Ϣ���У���ӦU_V2SLF ���� */
    E_AM_USM_QUE_SC_AUTH_MSG,       /* SC�Ͻ��յ�AUTHģ����Ϣ���У���ӦU_AUTH ���� */
    E_AM_USM_QUE_SC_SM_MSG,         /* SC�Ͻ��յ�IPNģ����Ϣ���У���ӦU_SM ���� */
    E_AM_USM_QUE_SC_CM_MSG,         /* SC�Ͻ��յ�CMģ����Ϣ���У���ӦU_CM ���� */
    E_AM_USM_QUE_SC_PMIP_MSG,       /* SC�Ͻ��յ�PMIPģ����Ϣ���У���ӦU_PMIP ���� */
    E_AM_USM_QUE_SC_IPC_MSG,        /* SC�Ͻ��յ�IPCģ����Ϣ���У���ӦU_IPC ���� */
    E_AM_USM_QUE_SC_SELF_MSG,       /* SC�Ͻ��յ�USMģ����Ϣ���У���ӦU_SELF ���� */
    E_AM_USM_QUE_SC_PCRF_MSG,       /* SC�Ͻ��յ�PCRFģ����Ϣ���У���ӦU_PCRF ���� */
    E_AM_USM_QUE_SC_PPP_MSG,        /* SC�Ͻ��յ�PPPģ����Ϣ���У���ӦU_PPP ���� */
    E_AM_USM_QUE_SC_L2TP_MSG,       /* SC�Ͻ��յ�L2TPģ����Ϣ���У���ӦU_L2TP ���� */
    E_AM_USM_QUE_SC_ERR_MSG,        /* SC�Ͻ��յ�USMģ����Ϣ���У���ӦU_ERR ���� */
    E_AM_USM_QUE_SC_LAP_MSG,        /* SC�Ͻ��յ�LAPģ����Ϣ���У���ӦU_LAP ���� */
    E_AM_USM_QUE_SC_DHCPV4S_MSG,    /* SC�Ͻ��յ�DHCPV4Sģ����Ϣ���У���ӦU_DHCPV4 ���� */
    E_AM_USM_QUE_SC_DLDN_MSG,       /* SC�Ͻ��յ�USMģ����Ϣ���У���ӦU_DLDN ���� */
    E_AM_USM_QUE_SC_PFUPDTBL_MSG,   /* SC�Ͻ��յ�ģ����Ϣ���У���ӦU_PFUPDTBL ���� */
    E_AM_USM_QUE_SC_S6B_MSG,        /* SC�Ͻ��յ�S6Bģ����Ϣ���У���ӦU_S6B ���� */
    E_AM_USM_QUE_SC_ASN_QUERY,      /* SC�Ͻ��յ�ASNģ����Ϣ���У���ӦU_ASN ���� */

    E_AM_USM_QUE_IPN_QOS_UPDATE,    /* ����SM�����ݸ�֪������Ϣ���У���ӦAMRcvSMMsgQue%02lu ���� */

    E_AM_USM_QUE_LAP,               /* ����LAP�Ĺ�����Ϣ���У���ӦSC%02lu_V2USM_QUE ���� */
    E_AM_USM_QUE_HOMEZONE,          /* ����HOMEZONE������Ϣ���У���ӦHZGT%d ���� */
    E_AM_USM_QUE_L2TP,              /* ����L2TP������Ϣ���У���ӦL2TP-GTPC%lu ���� */
    E_AM_USM_QUE_ASN,               /* ����ASN������Ϣ���У���ӦASNSC%02d ���� */

    E_AM_USM_QUE_PF_DL_NOTIFY,      /* ����PF��downlink-data-notify֪ͨ������Ϣ���У���ӦS%luDLNOTIFY ���� */
    E_AM_USM_QUE_PF_TBL_OPT_FAIL,   /* ����PF���±���Ľ����֪ͨ���У���ӦDPS_TblOptFailAck_SC%2lu ���� */

    E_AM_USM_QUE_TIMER,             /* ���ն�ʱ����Ϣ���У���ӦU_TM ���� */
    E_AM_USM_QUE_GM_RANDOM,         /* ��������û����ٹ�����Ϣ���У���ӦRANDOM_GTPCRCV%2d ���� */

    /* add start by jiexianzhu at 2012.08.25 for �������� */
    E_AM_USM_QUE_SC_GRM_MSG,        /* GRM����SC���յ���������Ķ��У���ӦGRMWriteSCRead%2lu ���� */
    /* add end by jiexianzhu at 2012.08.25 for �������� */

    E_AM_USM_QUE_FCM_GTP,           /* ��ӦFCM_SUB_MID_GTPC  ��ش��� */
    E_AM_USM_QUE_FCM_GTPC_FSDB,     /* ��ӦFCM_SUB_MID_GTPC_FSDB CKP��ش��� */
    E_AM_USM_QUE_FCM_MSU,     /* MSU�û�����ע�뿪ʼ��Ϣ */

    E_AM_USM_QUE_SELFMSG_FOR_SPUF,  /* USM �����Լ�����Ϣ,Ŀǰֻ����F��û�д�����Ӧ�Ķ���*/

    E_AM_USM_QUE_SELF_CHECK,        /* ��Ӧԭ��DE����ֺ˲���Ϣ */

    E_AM_USM_QUE_FCM_MSD,           /* ����MSD����Ϣ */
    E_AM_USM_QUE_TYPE_END,
}AM_USM_QUE_TYPE_E;

/* �¼����� */
#define M_AM_USM_EV_GTPV2_MSG            (1 << 0)   /*����GTPV2��������Ϣ*/
#define M_AM_USM_EV_GTPV2_SELF_MSG      (1 << 0)   /*����USM�����͸��Լ���GTPV2��Ϣ�¼�λ */
#define M_AM_USM_EV_SELF_MSG             (1 << 0)   /*�����Լ����͵ĵ���Ϣ�¼� */

#define M_AM_USM_EV_AUTH_MSG             (1 << 1)    /*����AAA����Ϣ�¼� */
#define M_AM_USM_EV_LAP2_MSG             (1 << 2)    /*����LAP2����Ϣ�¼� */
#define M_AM_USM_EV_RANDOM_TRC           (1 << 3)   /* GRMд��USM����������¼�λ */
#define M_AM_USM_EV_CM_MSG               (1 << 4)    /*����CM-CORE����Ϣ�¼� */
#define M_AM_USM_EV_RCPF_MSG             (1 << 5)    /*����RCPFC��������Ϣ�¼�*/
#define M_AM_USM_EV_IPC_EVENT_MSG       (1 << 6)    /*����IPC��Ϣ�¼� */

#ifndef VOS_NO_WAIT
#define VOS_NO_WAIT                 ((VOS_UINT32)1 << 31)
#endif

#ifndef VOS_EV_ANY
#define VOS_EV_ANY                  ((VOS_UINT32)1 << 26)
#endif

#ifndef VOS_WAIT
#define VOS_WAIT                    ((VOS_UINT32)1 << 30)
#endif

/* ��д����ģʽ */
#define VOS_MCQUEUE_WAIT      ((VOS_UINT32)1 << 4) /* �ȴ�ģʽ   */
#define VOS_MCQUEUE_NO_WAIT   ((VOS_UINT32)1 << 5) /* ���ȴ�ģʽ */


#define M_SPM_BYTE_024  24
#define M_SPM_BIT_218  218


/*----------------------------------------------------------------------*/
/*
 * ���������궨���ˡ������͡��ء�����״̬���������걻�����
 * �����á����磺
 *
 *  #define VRP_MODULE_RTPRO_OSPF   VRP_NO
 *  #define VRP_MODULE_RTPRO_RIP    VRP_YES
 *
 * ��ʾ��̬·��Э��OSPF���رգ�����̬·��Э��RIP����������
 * ����VRPϵͳ�ڱ���ʱ���Ϳ��Բ��OSPFģ�������RIPģ�顣
 * ��Ҫע�������Щ�����ϻ����һ�Ժ꣬���ܱ�ͬʱ��Ϊ
 * ��VRP_YES����VRP_NO������һ�㽫�����ں���������С�
 * ע�⣬�벻Ҫ�޸����������ֵ��
 */
#define VRP_YES     1
#define VRP_NO      0
/*----------------------------------------------------------------------*/


/*BYTE���ͺ궨��*/
typedef enum enU_SOFTPARA_BYTE_VALUE
{
    //Cyjun: ��Ȼʵ���Ǹ���ļ��ϣ�ҵ���õ������ȥ��ƽ̨�Ժ궨����M_SPM_ALM_SUMMUMER
    M_SPM_ALM_SUMMUMER = 2,/*�澯ʱ������ʱ*/

    M_SPM_DHCP_AGENTIP_USAGE_CTR = 3,

    M_SPM_DHCP_AGENTIP_NUM_CTR = 4,

    //Cyjun: ��Ȼʵ���Ǹ���ļ��ϣ�ҵ���õ������ȥ��ƽ̨�Ժ궨����M_SPM_SEC_UMT
    M_SPM_SEC_UMT = 10,/*M2000UMTS5.0 and UMTS6.0,��ο���*/

    /* Added start by chenlibin58790 at 2008-01-18 V9R7 for AM */
    M_SPM_SGSN_GGSNACK_ACT = 13,/*�������ÿ���GGSN���ظ��ն�config-ack��Ϣ*/
    M_SPM_GGSN_TNA_ACT = 14,/*���ڿ���͸������Ȩ�û��Ƿ�Ѽ��������е�CHAP/PAP��Ȩ��Ϣ���ظ��ն�*/
    M_SPM_GGSN_AUTH_ACT = 15,/*���ڿ���͸����Ȩ���߲�͸�������Ƿ��ڼ�����Ӧ��Ϣ��Я��CHAP/PAP��Ȩ��Ϣ���ظ��ն�*/
    M_SPM_CM_ACCT_INTERVAL =    18,/*���ڿ���ACCT�Ƿ�֧��AAA��Ȩ�·���ʱ����ֵ:1֧�ֲ�֧��*/

    M_SPM_GGSN_R5SWITCH_ACT = 19,/*�ÿ�����Ϊ��֧��R5 Qos���ģ������Ƿ�֧��CR411*/

    M_SPM_GGSN_VIRTUALAPNRULE_LOADSHARE = 20,/*bit2,���ڿ��Ƹ��ɷֵ���ʽ������APN�������ʵAPN�󶨵�AAA�Ʒѷ����������ã������ò���AAA��Ӧ��������Ӧ��AAA��Ӧ��ʱ��ȥ�����û�ʱ�Ƿ�����ѡ���APN��*/

    M_SPM_CM_DIAM_PROXY = 25,/* ���ڿ������߼Ʒ�ʱDCC��Ϣ�Ƿ�֧��proxy */

    M_SPM_CM_OCSC_CHECKHOST = 27,/* �������߼Ʒ�ʱ�Ƿ���CCA��Ϣ��origin-host */

    M_SPM_GGSN_SAMEIMSI_ACT = 31,/*���ڿ��Ƶ��û�����GGSN�Ѿ����ں͸��û�����������ͬ��IMSI����MSISDN��ͬ��PDP������ʱ���Ƿ������û�����*/
    /* Added end by chenlibin58790 at 2008-01-18 V9R7 for AM */

    M_SPM_CM_OCSC_USER_EQUIPMENT_INFO = 33, /* ����CCR��Ϣ��IMEIV��Ԫ��ʽΪBCD���UTF8String���� */
    /* Added start by y102283 at 2008-07-22 V9R7C01Build2 for AM */
    M_SPM_PLMN_ARP_CONTROL_POINT = 36,     /* ��ȡplmn�Լ����컯���Ŀ��Ƶ�����ȥAAA��Ȩ֮ǰ����֮�� */
    M_SPM_UGW_AAA_ALARM_INTERVAL = 41,     /* AAA�澯ɨ��server״̬�ļ�� */
    M_SPM_UGW_AAA_ALARM_ACCUMULATE = 42,    /* �ۼ�����down�Ĵ������ϱ��澯 */
    /* Added end by y102283 at 2008-07-22 V9R7C01Build2 for AM */

    /* BEGIN: Added for PN:AX4D10219 by jiahuidong, 2009/10/24 */
    M_SPM_AM_DHCP_KPN = 39,
    /* END:   Added for PN:AX4D10219 by jiahuidong, 2009/10/24 */

    /*43����ζ���SC �û�����ȥ��������T3N3��ʱ���Ƿ�澯��
       �����ֵΪ0���Ͳ���澯��·���ϣ������1��15��ֵ����ʾ��ǰ
       SCҪ��������������õĸ����󶼳�ʱ�����ø�SC��·���ϣ��������SD*/
    M_SPM_AM_SFN_PATH_ALARM_SW = 43,
    M_SPM_UDP_CHECKSUM = 45,        /* ���ڿ���UDP CheckSum, bit0:L2tp������Ϣ,bit1:L2tp������Ϣ,bit2:Gtp, bit3:DHCP */
    /*����AAA��Ȩ���Ʒ��Լ�������OCS��APN���Ƿ��д*/
    M_SPM_GGSN_APN_UPPERCONTROL = 40,

    /* BEGIN: Added for PN:AX4D04896 by jiahuidong, 2008/11/29 */
    M_SPM_AM_ADDR_CONFLIC_CHECK_SW = 44,
    /* END:   Added for PN:AX4D04896 by jiahuidong, 2008/11/29 */
    M_SPM_L2TP_UDP_CHECKSUM = 45,
    M_SPM_AM_GRM_CONTROL_TIMER = 46,
    M_SPM_GGSN_DEACTIVE_CAUSE_CTRL = 62,

    /* Added start by chenlibin58790 at 2008-10-27 V9R7C01 for AX4D05697 */
    M_SPM_AM_GGSN_TAKE_CGADDRESS = 49, /*GGSN�ڼ���͸���Ӧ�����Ƿ�Я��CG��ַ*/
    /* Added end by chenlibin58790 at 2008-10-27 V9R7C01 for AX4D05697 */

    /* Added start by zhaolindong at 2008-11-28 GGSN9811V9R7C01Build2CM for AX4D05596 */
    M_SPM_CM_OCSC_FAILOVER_NODE_NUM = 50,   /* ����Failover�ڵ���� */
    /* Added end by zhaolindong at 2008-11-28 GGSN9811V9R7C01Build2CM for AX4D05596 */

    /* Added start by huxiang 55400 at 2008-09-01 V9R7B032SPC001 for AX4D04490 */
    /* 52����ζ�����RG�ڵ��Ƿ���Ҫ�ϻ��ı��
    ȡֵ��ΧΪ0-255�������Ĭ��ֵ����Ϊ0��������㣬�򳬹�30����ϻ�*/
    M_SPM_SM_RG_AGE_FLAG = 52,
    /* 53����ζ�����pipeline�����Ƿ�򿪱��
    ȡֵ��ΧΪ0-255�������Ĭ��ֵ����Ϊ0��pipeline���ܹرգ�������㣬pipeline���ܴ�*/
    M_SPM_SM_PIPELINE_FLAG = 53,
    /* Added end by huxiang 55400 at 2008-09-01 V9R7B032SPC001 for AX4D04490 */

    /* Added start by chenlibin58790 at 2008-05-05 V9R7 for chen20080505 */
    M_SPM_GGSN_ACCOUT_ACT= 54,
    /* Added end by chenlibin58790 at 2008-05-05 V9R7 for chen20080505 */

    /* Added start by chenlibin58790 at 2008-01-18 V9R7 for AX4D00454 */
    M_SPM_GGSN_CHARGE_ACT = 55,/*���ڿ��Ƶ��û�����GGSN�Ѿ����ں͸��û�����������ͬ��IMSI����MSISDN��ͬ��PDP������ʱ���Ƿ������û�����*/
    /* Added end by chenlibin58790 at 2008-01-18 V9R7 for AX4D00454 */

    M_SPM_CM_ACCT_VENDORID = 56,/*���ڿ���TMO��չ��ԪVENDORID��TMO����HUAWEI:1��huawei ;0��TMO*/

    /* Added start by huxiang 55400 at 2007-12-11 V9R7 Build1 SM for ST */
    /* 57����ζ����˵����ݼƷ����ڵ���Դ�ľ�ʱ�Ĵ�������
    ���bitΪ��Ԫ��ڵ�ľ���������͵ڶ�bitΪRG�ڵ�ľ�����
    0Ϊ������1ΪPass���Ʒ�*/
    M_SPM_SM_SFN_RESOURCE_EXHAULT_ACT = 57,
    /* Added end by huxiang 55400 at 2007-12-11 V9R7 Build1 SM for ST */

    M_SPM_PPP_L2TP_AUTH_IPCP_SWITCH = 59, /* for M1  */

    M_SPM_L2TP_INVALID_TUNL_EXIST = 63, /* ��ЧL2TP������ʱ�䣬��λ:Сʱ */

    M_SPM_SM_SAM_INDENTIFY_THRESHOLD = 66, /*������ʶ�����*/

    M_SPM_IMSIMSISDN_SELECT = 68,
    /*���ڿ�������ͳ��ʱ���ĸ�APN����ͳ��,������ֵΪ1��������APN��������ͳ��,���ֵΪ0������ʵAPN��������ͳ��*/
    M_SPM_CM_CAPABILITY_STAT_APN_TYPE = 75,

    /* Added start by liwei 57151 at 2008-12-22 V9R7C02 for C02V8������ֲ */
    /* ����diameter��Ϣcalled-station-id AVP���λ */
    M_SPM_CM_DIAM_CSIAVPFLAG = 76,
    /* 1,2,3 bit����V8 I+D����4 bit����NSN�Խ����� */
    M_SPM_CM_V8_SOFT_PARAM = 77,
    /* Added end by liwei 57151 at 2008-12-22 V9R7C02 for C02V8������ֲ */

    /*60�����������������Ƭ���ϻ�ʱ�䣬��λΪ250ms
      ȡֵ��Χ 1~255��ȱʡֵ120,������Ϊ0��ȡ120*/
    M_SPM_PF_EXTERIOR_FRAG_AGING_THR = 60,

    /*61��������������ڲ��Ƭ���ϻ�ʱ�䣬��λΪ250ms
      ȡֵ��Χ 1~255��ȱʡֵ120,������Ϊ0��ȡ120*/
    M_SPM_PF_INTERIOR_FRAG_AGING_THR = 61,

    /*64������������üƷ�һ��BTI�ڵ�������ֵ
      ȡֵ��Χ 0~40��ȱʡֵ0*/
    M_SPM_PF_CHARGE_BTI_FLOW_THR = 64,

    M_SPM_CM_CDRF_CTRLIDLE = 65,

    //begin added by liuyan 39579 for R007C02 V8������ֲ
    M_SPM_CM_V8_SOFT_PARA = 79,
    //end added by liuyan for R007C02 V8������ֲ
    /* Bit0��Bit1��λ,�¼��Ʒѵ�����:  00��SCUR�¼��Ʒ�   01��IEC  10����ǿ��ECUR
      Bit2λ��1������block���ܣ������CCR������CCA,Tx��ʱ������ת���ߣ��������¼��Ʒ�ҵ������ 0���ر�block���� */
    M_SPM_CM_IEC_ECUR_SCUR_EVENT = 80,
    M_SPM_CM_NPT_SOFT_PARA = 81,

    M_SPM_CM_CCA_TIMEOUT_ALM = 82,
    M_SPM_CM_CCA_TIMEOUT_ALM_RESTORE = 83,
    M_SPM_PF_IPv6_UDP_CHKSUM_FLAG = 84,

    M_SPM_CM_OCSC_SUPPORTED_VENDOR_ID = 85,
    /* added start by lijie for GGSNV9R8*/
    M_SPM_CM_TFA_FUN_SWITCH = 87, /* ���������߼Ʒ�����*/
    /*begin added by liuyan 39579 for CR20090811006 AM_Mexico_PS_CDR*/
    M_SPM_CM_CDR_ADAPT_FOR_OPERATE = 88,
    /*end added by liuyan 39579 for CR20090811006 AM_Mexico_PS_CDR*/

    M_SPM_LI_TAI_MAXSEQNUMDELTA = 89,

    M_SPM_CM_DIAM_DEBUG_CONTROL_FLAG = 90,
    M_SPM_L2TP_PRILNS_DETECT_INTERVAL = 92, /* ��ЧL2TP������ʱ�䣬��λ:Сʱ */
    M_SPM_CM_DIAM_XML_FILE_OPERATOR_ID = 93,

    M_SPM_CM_DIAM_CAPABILITY_EXCHANGE_CONTROL = 91,

    M_SPM_AM_MSG_AUTHENTICATOR_FLAG = 95,
    M_SPM_AM_MSG_ACCESSPREFIX_FLAG = 96,
    /* Modified start by Libin 51420 at 2009-10-29 GGSNV9R8-IPN for ҵ�񱨱���ǿ */
    M_SPM_PF_CAR_RETRIEVE_RATE = 97,
    M_SPM_SM_FD_QUICK_AGE_TIME = 98,

    M_SPM_L2TP_ICCN_LCP_FLAG = 110,

    /*Wangyuting add begin for CR20100428010,2010-5-6*/
    M_SPM_AM_FORWARDING_AGE_TIME =115,  /*ת�������ϻ�����ʱ�䣬��ЧֵΪ0-24.ֵΪ0ʱ��Ĭ��3�㡣1-24ʱ������ʱ��Ϊ1-24�㡣*/
    /*Wangyuting add end for CR20100428010,2010-5-6*/

    M_SPM_AM_GTPC_WAL_MAX = 121,
    M_SPM_AM_GTPC_WAL_PERCENT = 122,
    M_SPM_AM_GTPC_N_MIN = 123,
    M_SPM_AM_GTPC_APN_FAULT_INTERVAL = 124,
    M_SPM_AM_SD_NORMAL_CEREATE_NUM = 125,
    M_SPM_AM_SD_VIP_CEREATE_NUM = 126,
    M_SPM_AM_SD_ALARM_INTERVAL = 127,
    M_SPM_AM_SD_ALARM_TIMES = 128,
    M_SPM_AM_SD_RESTORE_ALARM_INTERVAL = 129,
    M_SPM_AM_SD_RESTORE_ALARM_TIMES = 130,

    /* BEGIN: Added by jixiaoming at 2011-09-27 for  CR20101222007 */
    M_SPM_DHCP_SERVER_TEST_INTERVAL = 132,     /* DHCP ̽��server״̬��ʱ����ʱ���� */
    M_SPM_DHCP_ALARM_INTERVAL = 133,           /* DHCP �澯ɨ��server״̬�ļ�� */
    M_SPM_DHCP_ALARM_ACCUMULATE = 134,         /* �ۼ�����down�Ĵ������ϱ��澯 */
    /* END: Added by jixiaoming at 2011-09-27 for  CR20101222007 */

    M_SPM_WAITREL_TIME_REDIRECT = 318,
    M_SPM_WAITREL_TIME_GIDEFEND = 612,
    M_SPM_CM_TARIFF_USER_PER_SECON = 38,

    M_SPM_AM_GTPC_CACHE_TIME = 102,
    M_SPM_AM_UPM_ONLINE_INJECT = 103,
    M_SPM_IPN_RPT_SUBSCRIBER_SWITCH = 105,
    /* Modified end by Libin 51420 at 2009-10-29 GGSNV9R8-IPN for ҵ�񱨱���ǿ */

    M_SPM_IPN_CACHE_FD_AGETIME = 107,    /* С��Ԫ���ϻ�ʱ�� 1-255 ��ʾ 10s~2550s */

    M_SPM_SM_PCC_FUP_RGSID_OR_MKEY = 108,

    M_SPM_CM_OCSC_VDF = 113,

    M_SPM_AM_MULTI_ACCESS_MODE = 114,    /* ҵ��ģʽ������ģʽ��Σ�Ĭ��Ϊ����ģʽ */

    /* �쳣�����붯�������� */
    M_SPM_CM_OCSC_RETCODE_ACTION = 116,

    M_SPM_AM_HZ_ACT_NUM_IN_SEC_MAX = 117,/*Added by c0011085 for homezone ����*/

    /*Added Start by liuli 67542, 2011-05-25 for ps9.1 sync GGSNV9R8C01 CR20101208036 ������Դ��̬��������*/
    M_SPM_IP_2G_RES_DYN_CTRL = 131,
    /*Added end by liuli 67542, 2011-05-25 for ps9.1 sync GGSNV9R8C01 CR20101208036 ������Դ��̬��������*/

    M_SPM_PATH_RECOVERY_SWITCH = 144,

    M_SPM_UGW_DEACTIVE_CAUSE_CTRL = 200,

    M_SPM_UGW_AAA_ALM_RESUME_CONTROL = 201,

    M_SPM_CM_CDRF_CTROL_AMACCESS    = 203,

    M_SPM_IPN_DPILOGIC_FUNC_SWITCH = 243, /*����DPIӲ�����ٹ����Ƿ�ʹ��*/
    M_SPM_IPN_DPILOGIC_FUNC_HEARTBEAT = 244,  /*����DPIӲ��������⹦���Ƿ�ʹ���Լ�DPI����������

    /* Added start by liuhui 63136 at 2011-02-21 PS9.0 for Single_ip */
    M_SPM_AM_GTP_PROXY_CONTROL = 248,
    /* Added end by liuhui 63136 at 2011-02-21 PS9.0 for Single_ip */
    M_SPM_LI_SINGLE_IP_MULTI_PORT_CONTROL = 249,
    M_SPM_SM_FORCE_MERGE_METHOD = 301,
    M_SPM_CM_EVENTTRIGGER_SUPPORT_DIFF_RELEASE = 302,
    M_SPM_GUL_CONFLIT = 303,
    M_SPM_QOS_NOKEY_ATTR_SAE_TO_GGSN = 304,
    M_SPM_LOGIC_TCPBUFFER_TIME = 305,
    M_SPM_PF_EXTERN_TRACE = 307,
    M_SPM_CM_OCSC_HOLDING_TIMER_AMAN = 309,   //��������command���յ��쳣�����������holding-time��ʱ��
    M_SPM_CM_OCSC_CCR_I_WAL_PERCENT = 310,   //��������command���յ��쳣�����������holding-time��ʱ��
    M_SPM_CM_OCSC_CCR_TYPE_WAL_CTRL = 311,   //��������command���յ��쳣�����������holding-time��ʱ��
    /* Added start by jiexianzhu at 2014.05.05 for CR20130409041 */
    M_EMS_KPI_PDP_ACTIVE_SUCCESS_RATIO_RANG = 312,
    /* Added end by jiexianzhu at 2014.05.05 for CR20130409041 */
    M_SPM_KPI_FW_SUCCESS_RATIO_RANG = 313,
    M_SPM_KPI_ALARM_THRESHOLD = 315,
    M_SPM_BYTE_CAN_BOARD_ACCESS = 316,  //single IP��������E F���Ƿ�����弶����:0 ����1 ������

    M_SPM_BYTE_QOS_UPGRADE_R7 = 325,

    M_SPM_IP_IPSQM_EN_PKT_NUM = 401,
    M_SPM_IP_IPSQM_DE_PKT_NUM = 402,
    /* BEGIN: Added by yuehongwei, 2012/2/8   ���ⵥ��:PS9.2 SRU��������*/
    M_SPM_SRU_CPU_CTRL = 403,
    /* END:   Added by yuehongwei, 2012/2/8 */

    M_SPM_LI_CONGEST_TIMER = 408,

    M_SPM_SM_PCC_PRODUCT_MODE = 409,
    /* Begin: added for AIS migrate from 10.0 g90006569*/
    M_SPM_SM_PCC_ADAPTER_FOR_AIS = 501,
    /* End: added for AIS migrate from 10.0 g90006569 */
    M_SPM_AM_PROTOCOL_UPGRADE = 502,
     M_SPM_IPN_TCP_OPTIMIZE_ALGORITHM = 503,
    M_SPM_CM_OCSC_AISBYT504 = 504,

    M_SPM_CM_OCSC_QOS_INFORMATION = 505,
    M_SPM_SM_MSD_VAS_FAULT_PKT_ACTION = 507,
    M_SPM_SM_MSD_MAX_FD_NUM_PER_USER = 508,

    M_SPM_IPN_TCP_BUFCC_SIZE = 509,

    M_SPM_SM_FUI_DNS_PASS_MAX_NUM = 511,
    M_SPM_AM_AUTH_FLOWCONTROL_FLAG = 512,
    M_SPM_CM_AUTH_FC_INTER_CTRL = 512,
    M_SPM_SM_L347_BUFFMBUF_AGE_TIME = 513,

    M_SPM_LI_SPUF_X3_TCP_MAXPACKETNUM_PPS = 514,
    M_SPM_LI_SPUF_X3_UDP_MAXPACKETNUM_PPS = 515,

    /*Begin: added for AIS migrate from 10.0 g90006569*/
    M_SPM_SM_GXGY_ADAPTER_FOR_AIS = 516,
    /*End: added for AIS migrate from 10.0 g90006569*/

    M_SPM_SCCG_SD_NORMAL_CEREATE_NUM = 525,
    M_SPM_SCCG_TIME_STAMP = 527,

    M_SPM_IPN_NUM_HOPS_FOR_ROUTE_EPSN = 528, /* ����SCCG��Tethering�����������豸֮������������·������ */
    M_SPM_CM_PHGW_DIAM_PROXY = 538,
    M_SPM_CM_PHGW_OCSC_CHECKHOST = 539,
    M_SPM_CM_PHGW_FT_MOD = 540,
    M_SPM_CM_PHGW_CHINATEL_MOD = 549,
    /* 57�������pdsn��Ʒ��Ϊ555�����˵����ݼƷ����ڵ���Դ�ľ�ʱ�Ĵ�������
    ���bitΪ��Ԫ��ڵ�ľ���������͵ڶ�bitΪRG�ڵ�ľ�����
    0Ϊ������1ΪPass���Ʒ�*/
    M_SPM_SM_SFN_RESOURCE_EXHAULT_ACT_PDSN = 555,
    /* PDSN ��Ʒ53�������pdsn��Ʒ��Ϊ557 , ������pipeline�����Ƿ�򿪱��
    ȡֵ��ΧΪ0-255�������Ĭ��ֵ����Ϊ0��pipeline���ܹرգ�������㣬pipeline���ܴ�*/
    M_SPM_SM_PIPELINE_FLAG_PDSN = 557,
    M_SPM_CM_PHGW_FT_VOIP_QHT = 559,
    M_SPM_PDSN_UDP_CHECKSUM = 569,
    M_SPM_PDSN_AAA_ALARM_INTERVAL = 546,     /* AAA�澯ɨ��server״̬�ļ�� */
    M_SPM_PDSN_AAA_ALARM_ACCUMULATE = 552,    /* �ۼ�����down�Ĵ������ϱ��澯 */
    M_SPM_PDSN_L2TP_INVALID_TUNL_EXIST = 560,
    M_SPM_CM_PHGW_EXPIRED_THRESHOLD = 572,
    M_SPM_SM_PDSN_THUNDER_HTTP_DETECTION = 575,
    M_SPM_CM_PHGW_EXIST_STORAGE_FILE = 583,
    M_SPM_CM_DIAM_ROUTE_FAILOVER  = 589,
    M_SPM_PDSN_L2TP_ICCN_LCP_FLAG = 590,
    /*Add by xsm00201057 20130304 for PDSNC06�����ֲ*/
    /*60�����������������Ƭ���ϻ�ʱ�䣬��λΪ250ms
      ȡֵ��Χ 1~255��ȱʡֵ120,������Ϊ0��ȡ120*/
    M_SPM_PF_PDSN_EXTERIOR_FRAG_AGING_THR = 594,
    /*61��������������ڲ��Ƭ���ϻ�ʱ�䣬��λΪ250ms
      ȡֵ��Χ 1~255��ȱʡֵ120,������Ϊ0��ȡ120*/
    M_SPM_PF_PDSN_INTERIOR_FRAG_AGING_THR = 595,
    /*End by xsm00201057 20130304 for PDSNC06�����ֲ*/
    /* 68�������pdsn��Ʒ��Ϊ596 */
    M_SPM_IMSIMSISDN_SELECT_PDSN = 596,
    /* 66�������pdsn��Ʒ��Ϊ597 */
    M_SPM_SM_SAM_INDENTIFY_THRESHOLD_PDSN = 597, /*������ʶ�����*/
    /* 98�������pdsn��Ʒ��Ϊ598 */
    M_SPM_SM_FD_QUICK_AGE_TIME_PDSN = 598,
    /* 107�������pdsn��Ʒ��Ϊ599 */
    M_SPM_IPN_CACHE_FD_AGETIME_PDSN = 599,    /* С��Ԫ���ϻ�ʱ�� 1-255 ��ʾ 10s~2550s */

    M_SPM_PDSN_LI_BAN = 574, /*PDSN LI ban����*/ /*PDSN LI ���� */
    M_SPM_LI_PDSNTAI_MAXSEQNUMDELTA = 602, /*PDSN LI ����TAI����*/ /*PDSN LI ���� */

    M_SPM_AM_AAA_ALM_RESUME_CONTROL_PDSN = 604,
    M_SPM_LI_PDSNCONGEST_TIMER = 605, /*PDSN LI ����X3 ӵ���澯����*/ /*PDSN LI ���� */
    M_SPM_PF_PDSN_CAR_RETRIEVE_RATE = 606,
    M_SPM_SM_PDSN_L347_BUFFMBUF_AGE_TIME = 607,
    M_SPM_IPN_PDSN_DECIDE_MODE = 608, /* PDSN �ڴ�ģʽ��0:��ͨģʽ��1:���ݼƷ�ģʽ */

    M_SPM_PF_PDSN_GIDEFEND_DNUPPKT_RATION = 610, /*PDSN���������б����б��ĵı�����ֵ����������ֵ����Ϊ������Ϊ*/
    M_SPM_PF_PDSN_GIDEFEND_PKT_PERIOD = 611,        /*PDSN�����ü�ⱨ�ĵ�����*/
    M_SPM_PF_UGW_GIDEFEND_DNUPPKT_RATION = 613, /*UGW ���������б����б��ĵı�����ֵ����������ֵ����Ϊ������Ϊ*/
    M_SPM_PF_UGW_GIDEFEND_PKT_PERIOD = 614,         /*UGW �����ü�ⱨ�ĵ�����*/
    M_SPM_PF_PDSN_GIDEFEND_FLAGS = 619,         /*PDSN/HSGW��ʶ�𹥻��ı�ʶ��Ϣ*/
    M_SPM_PF_UGW_GIDEFEND_FLAGS = 620,         /*GUL��ʶ�𹥻��ı�ʶ��Ϣ*/
    M_SPM_IPN_NUM_HOPS_FOR_ROUTE = 621, /* ����UGW��Tethering�����������豸֮������������·������ */

    M_SPM_HSGW_DNS_BYTE_616 = 616,
    M_SPM_HSGW_DNS_BYTE_617 = 617,
    M_SPM_HSGW_DNS_BYTE_618 = 618,
    M_SPM_SM_ANTI_FRAUD_DNS_VOLUMN_RATIO = 650,             /*DNS����թ:������DNS����������ֵ��ȱʡΪ80%*/
    M_SPM_SM_ANTI_FRAUD_DNS_TOTAL_VOLUMN = 651,             /*DNS����թ:DNS��������ֵ��ȱʡ10K*/
    M_SPM_SM_ANTI_FRAUD_DNS_DN_VOLUMN_DEVIATION = 652,      /*DNS����թ:����������ƫ��ƽ��ֵ��ֵ��ȱʡ10*/
    M_SPM_CM_DIAM_DEBUG_SWITCH_P_BIT = 653,               /* �����Ƿ���CCA��Ϣ��P Bitλ */

    M_SPM_AM_MSG_CON_RESEND_CAUSE = 659,      /*���ƶ�ʧ��PCC�ش�����ԭ��ֵ*/

    M_SPM_BYTE_GX_SAME_PEER_RETRAN_NUM = 704,
    M_SPM_BYTE_GX_SAME_PEER_RETRAN_DELAY_TIME = 705,


    M_SPM_DEF_BYTE_END
}U_SOFTPARA_BYTE_VALUE;

/**
* @ingroup vrp_timer
* ����vrp��ʱ�����ͣ����ζ�ʱ����
 */
#ifndef VOS_TIMER_NOLOOP
#define VOS_TIMER_NOLOOP             0
#endif

/** SPU����ACTIVE/STANDBY״̬ */
typedef enum tagCRM_PRIMARY_INFO_ENUM
{
    E_CRM_ACTIVE = 0,       /**< ����ΪACTIVE״̬ */
    E_CRM_STANDBY,          /**< ����ΪSTANDBY״̬ */
    E_CRM_PRIMARY_NULL      /**< ��Ч״̬ */
}  CRM_PRIMARY_INFO_ENUM ;


#ifndef __FWD_TO_CTRL_HDR__
#define __FWD_TO_CTRL_HDR__
typedef struct
{
    PF_USHORT usCtrlFlag;
	                       /*bit 15:Ϊ1�����Ǿ�̬��ַ�û�ת��ļ�������
                              bit14-bit12:res
                              bit11-bit10:�����Ƿ���ת�屨�ĸ���
                                        00��UGW/MSD <-> NET/SP
                                        01��UGW <-> MSD
                                        10��MSD <-> VAS
                                        11��MSD <-> MSU
                              bit9:��bit7-bit6Ϊ10ʱ��Ч����ʶFȾɫ֡��COLOR
    						  bit8:��ת�����ı�־
                              bit8:IPPM�����Ƿ񱻸���
                              bit7-bit6:���ֳ���IPPM�Ŀ��Ʊ��Ļ���������ı���
                                        00����������ģ�
                                        01����ʾ��IPPM��FM֡��PFʶ���������Ҫ��һЩ�ֶ�
                                        10 :IPPM��FMȾɫ֡
                              bit5-bit4:
                                        :��bit0(GtpuFlag)��Ϊ1ʱ(�û��汨��)����ʾGTP�����ǳ�GW�����(����)�����Ҳ�(����).
                                        ��ʾPMIP(GRE)�û��汨�ĳ�GW�����(����)�����Ҳ�(����)��
                                        00: ���GTP����(����), 01:�Ҳ�GTP����(����), 10: ���PMIP(GRE)(����), 11:�Ҳ�PMIP(GRE)(����)
                              bit3 : LiFlag,0: UP , 1:DN
                              bit2-bit1 : TraceFlag,00:UP_IN,01:UP_OUT,10: DN_IN,11:DN_OUT,
                              bit0 : GtpuFlag,1:indirect forwarding,0:�Ǽ��ת������*/
    PF_USHORT usPktType;    /*��������:1-psf 2-gre ping*/
    PF_ULONG  ulDpeTimeStamp;
    PF_ULONG  ulSubIndex;
    PF_ULONG  ulVcpuId;
    PF_ULONG  ulModuleId;
    PF_ULONG  ulMsgCode;
    PF_ULONG  ulPdpIndex;   /* GSDBindex,PF���Ϳ�����ʱ������gtpuindex��GTPU���л�
                               ȡGSDBindex,�ӿ������յ����ĺ󣬸��ݸ�ֵ����AM�ӿ�
                               ��ȡgtpuindex */
    PF_ULONG  ulVrfIndex;
} FWD_TO_CTRL_HDR;
#endif

typedef enum tagAM_CHECKSUM_MSG_CODE
{
    AM_CHECKSUM_L2TP_CTRL,
    AM_CHECKSUM_L2TP_DATA,
    AM_CHECKSUM_GTPP,
    AM_CHECKSUM_DHCP,
    AM_CHECKSUM_BUTT
}AM_CHECKSUM_MSG_CODE_E;

/** SPU���屸��ģʽ���Ͷ��� */
typedef enum tagCRM_BKUP_MODE_ENUM
{
    CRM_BKUP_LOAD_SHARING = 0, /**< ���ɷֵ�����ģʽ */
    CRM_BKUP_1_PLUS_1,         /**< 1+1����ģʽ */
    CRM_BKUP_N_PLUS_1,         /**< N+1����ģʽ */
    CRM_BKUP_TYPE_MAX          /**< ��Ч����ģʽ���� */
} CRM_BKUP_MODE_ENUM ;

typedef enum
{
    SDB_NOT_BACKUP = 0,                                    /* û�ж�ʱ���� */
    SDB_CREATE_BACKUP = 1,                             /* �������� */
    SDB_UPDATEVERNOTCHANGE_BACKUP = 2,   /* ����(�汾����)���� */
    SDB_UPDATEV1TOV0_BACKUP = 3,            /* ����(�л���V0)���� */
    SDB_UPDATEV0TOV1_BACKUP = 4,              /* ����(�л���V1)���� */
    SDB_DELETE_BACKUP = 5,                        /* ɾ������ */
    SDB_PPP_UPDATE_BACKUP = 6,
    SDB_L2TP_UPDATE_BACKUP = 7,
    SDB_UPDATESESSIONID_BACKUP = 8 ,
    SDB_INVALID_BACKUP_TYPE = 9,                  /* ��Ч�������� */
    SDB_NOT_NEED_BACKUP = 10                          /* ���跢�ͱ�����Ϣ������ */
} SDB_BACKUP_TYPE_E;

/* �޸Ķ���֪ͨ������ */
typedef enum E_PERF_OBJ_CHANGE_TYPE
{
    E_PERF_OBJECT_ADD = 0,      /* ������ӳɹ�֪ͨ */
    E_PERF_OBJECT_DEL,          /* ����ɾ���ɹ�֪ͨ */

    E_PERF_OBJECT_BUTT,
} E_PERF_OBJ_CHANGE_TYPE;


#define GTPC_IMSI_MSISDN_LENGTH 16


#define  TRC_DIRECTION_LEFT_IN_SGW          0x000
#define  TRC_DIRECTION_RIGHT_OUT_SGW        0x100
#define  TRC_DIRECTION_LEFT_IN_PGW          0x200
#define  TRC_DIRECTION_LEFT_IN_PGW_PMIP     0x210
#define  TRC_DIRECTION_RIGHT_OUT_PGW        0x300
#define  TRC_DIRECTION_RIGHT_IN_PGW         0x400
#define  TRC_DIRECTION_LEFT_OUT_PGW         0x500
#define  TRC_DIRECTION_LEFT_OUT_PGW_PMIP    0x510
#define  TRC_DIRECTION_RIGHT_IN_SGW         0x600
#define  TRC_DIRECTION_LEFT_OUT_SGW         0x700
#define  TRC_DIRECTION_IN_GGSN              0x800
#define  TRC_DIRECTION_OUT_GGSN             0x900
/* Start: Add by zhangyang for PN:BI8D02498, 2010/4/24 */
#define  TRC_DIRECTION_RIGHT_IN_UGW         0xa00
#define  TRC_DIRECTION_RIGHT_OUT_UGW        0xb00
#define  TRC_DIRECTION_RIGHT_IN_UGW_ERR     0xc00


/* --------------------------------------------------------------------------- */
/* -----------------------------EMS ģ�鶨��----------------------------- */
/* --------------------------------------------------------------------------- */
typedef enum tagEMS_DEBUG_MODULE_TYPE
{
    EMS_MODULE_TYPE_AM_GTPC           = 0x01,
    EMS_MODULE_TYPE_AM_LAP            = 0x02,
    EMS_MODULE_TYPE_AM_DHCP           = 0x03,
    EMS_MODULE_TYPE_AM_AUTH           = 0x04,
    EMS_MODULE_TYPE_AM_L2TP           = 0x05,
    EMS_MODULE_TYPE_AM_VOG            = 0x06,
    EMS_MODULE_TYPE_AM_PMIP           = 0x07,
    EMS_MODULE_TYPE_AM_S6B            = 0x08,


    EMS_MODULE_TYPE_CM_OSC            = 0x011,
    EMS_MODULE_TYPE_CM_PCRF           = 0x012,
    EMS_MODULE_TYPE_CM_ACCT           = 0x013,
    EMS_MODULE_TYPE_CM_CORE           = 0x014,
    EMS_MODULE_TYPE_SM                = 0x020,
    EMS_MODULE_TYPE_SM_MSD            = 0x021,
    EMS_MODULE_TYPE_SM_VOG            = 0x022,
    EMS_MODULE_TYPE_PF                = 0x030,

    /* PDSN */
    EMS_MODULE_TYPE_AM_CSN            = 64,
    EMS_MODULE_TYPE_AM_A11            = 65,
    EMS_MODULE_TYPE_AM_PPP            = 66,
    EMS_MODULE_TYPE_AM_AAA_AUTH_PDSN  = 67,
    EMS_MODULE_TYPE_AM_DIAM_AUTH_PDSN = 68,
    EMS_MODULE_TYPE_AM_LAP_PDSN       = 69,
    EMS_MODULE_TYPE_AM_DHCP_PDSN      = 70,
    EMS_MODULE_TYPE_AM_FA             = 71,
    EMS_MODULE_TYPE_AM_PMIPV6_PDSN    = 72,
    EMS_MODULE_TYPE_AM_RSVP           = 73,

    EMS_MODULE_TYPE_HSGW_CM_CORE           = 80,
    EMS_MODULE_TYPE_HSGW_CM_CDRF           = 81,
    EMS_MODULE_TYPE_HSGW_CM_OCSC           = 82,
    EMS_MODULE_TYPE_HSGW_CM_PCEF           = 83,
    EMS_MODULE_TYPE_HSGW_CM_KERNEL         = 84,
    EMS_MODULE_TYPE_HSGW_CM_POSTPAID       = 85,
    EMS_MODULE_TYPE_HSGW_CM_PREPAID        = 86,


}E_EMS_DEBUG_MODULE_TYPE;


#define IPV6_ADDR_ANY        0x0000U
#define IPV6_ADDR_UNICAST    0x0001U
#define IPV6_ADDR_MULTICAST  0x0002U
#define IPV6_ADDR_LOOPBACK   0x0010U
#define IPV6_ADDR_NODELOCAL  0x0010U
#define IPV6_ADDR_LINKLOCAL  0x0020U
#define IPV6_ADDR_SITELOCAL  0x0040U
#define IPV6_ADDR_GLOBAL     0x0100U
#define IPV6_ADDR_COMPATv4   0x0080U
#define IPV6_ADDR_SCOPE_MASK 0x00f0U
#define IPV6_ADDR_MAPPED     0x1000U
#define IPV6_ADDR_RESERVED   0x2000U /* reserved address space */

/* VRP_MODULE_IPV6  */
#ifndef AF_INET6
#define AF_INET6        29             /* added by mayun for IPv6 */
#endif

#define AM_TRC_IPV6_LEN 16

typedef struct tagUGW_EXTERN_INTF_TRACE_S
{
    ULONG  ulMsgClass;      //��Ϣ����
    ULONG  ulGtpMsgType;    //��Ϣ����
    ULONG  ulLocalIpAddr;   //����IP
    UCHAR  aucLocalIpv6Addr[AM_TRC_IPV6_LEN];   //����Ipv6
    ULONG  ulVpnIndex;      //����IP�󶨵�VPN����
    ULONG  ulPeerIpAddr;    //�Զ�IP
    UCHAR  aucPeerIpv6Addr[AM_TRC_IPV6_LEN];  //�Զ�IPv6
    ULONG  ulMsgLen;        //��Ϣ����
    USHORT usApnIndex;      //APN����:GNGP APN���ȿ�������
    UCHAR  ucAliaApnFlag;   //����APN��־λ:GNGP APN���ȿ�������
    UCHAR  ucRev;
}UGW_EXTERN_INTF_TRACE_S;

typedef struct tagUGW_EXTERN_INTF_TRACE_INFO_S
{
    UCHAR* pucTrcMsg;
    UCHAR  ucMsgType;
    UCHAR  ucVersion;
    USHORT usMsgLen;
    ULONG  ulMsgClass;      //��Ϣ����
    ULONG  ulGtpMsgType;    //��Ϣ����
    ULONG  ulDirection;
    ULONG  ulPeerIp;
    ULONG  ulIntfType;
    ULONG  ulLocalIp;
    ULONG  ulSourceIP;
    ULONG  ulVpnIndex;
    USHORT usPeerPort;
    USHORT usLocalPort;
    UCHAR  ucIpAddrType; //ipv4��ipv6
    USHORT usApnIndex;
    UCHAR  ucAliaApnFlag;
    UCHAR  aucLocalIpv6Addr[AM_TRC_IPV6_LEN];   //����Ipv6
    UCHAR  aucPeerIpv6Addr[AM_TRC_IPV6_LEN];  //�Զ�IPv6
}UGW_EXTERN_INTF_TRACE_INFO_S;



/* Added end by fanlianrong kf25870 on 2010-12-04 for PGPV2R5 OMADA-TCP���� */
/* SGW S4/S11�ӿڵ���Ϣ����(ҵ����ʹ��)*/
#define  S4S11_MSGTYPE_PATH         0x01
#define  S4S11_MSGTYPE_GTP          0x02
#define  S4S11_MSGTYPE_PMIPV6       0x04
#define  S4S11_MSGTYPE_DHCPV6       0x08
#define  S4S11_MSGTYPE_DHCPV4       0x10
#define  S4S11_MSGTYPE_IPV6         0x20
#define  S4S11_MSGTYPE_EMS_SIGNALING    0x40
#define  S4S11_MSGTYPE_ALL          0x7F

/* SGW S5/S8�ӿڵ���Ϣ����(ҵ����ʹ��)*/
#define  S5S8_MSGTYPE_PATH         0x01
#define  S5S8_MSGTYPE_GTP          0x02
#define  S5S8_MSGTYPE_PMIPV6       0x04
#define  S5S8_MSGTYPE_DHCPV4       0x08
#define  S5S8_MSGTYPE_DHCPV6       0x10
#define  S5S8_MSGTYPE_IPV6         0x20
#define  S5S8_MSGTYPE_ALL          0x3F

/* PGW S5/S8/S2a�ӿڵ���Ϣ����(ҵ����ʹ��)*/
#define  S5S8S2A_MSGTYPE_PATH         0x01
#define  S5S8S2A_MSGTYPE_GTP          0x02
#define  S5S8S2A_MSGTYPE_PMIPV6       0x04
#define  S5S8S2A_MSGTYPE_DHCPV4       0x08
#define  S5S8S2A_MSGTYPE_DHCPV6       0x10
#define  S5S8S2A_MSGTYPE_IPV6         0x20
#define  S5S8S2A_MSGTYPE_PPP          0x40
#define  S5S8S2A_MSGTYPE_EMS_SIGNALING          0x80
#define  S5S8S2A_MSGTYPE_ALL          0xFF

typedef struct tagUDPHDR
{
    USHORT    uh_usSPort;        /* source port */
    USHORT    uh_usDPort;        /* destination port */
    SHORT     uh_sULen;          /* udp length */
    USHORT    uh_usSum;          /* udp checksum */
}UDPHDR_S;

#define IPV6_HEADER_LEN     40
#define UDP_HEADER_LENGTH   8   /*udp ͷ����*/

#define IPV6_ICMP_PRO      58
#define IPV6_UDP_PRO       17
#define SDB_MAX_CONTEXT_NUM 12500   /*1250*/

/*IPV6 FIXED HEADER */
typedef struct tagIpv6hdr {
#if (UGW_BYTE_ORDER == UGW_LITTLE_ENDIAN)
    ULONG        traffic_class_1:4,
                 version:4,
                 flow_lbl_1:4,
                 traffic_class_2:4,
                 flow_lbl_2:16;
#else
    ULONG        version:4,
                 traffic_class:8,
                 flow_lbl:20;
#endif

    USHORT       payload_len;
    UCHAR        nexthdr;
    UCHAR        hop_limit;

    in6_addr    saddr;
    in6_addr    daddr;
}VOS_PACKED IPV6HDR_S;


/**
* @ingroup  v_mcque
* ������Ϣ�ж������ֳ���(����������)��
*/
#define MCQUEUE_INFO_NAME_LEN 32

/**
* @ingroup  v_mcque
*
* �ýṹ���ڱ��������Ϣ��
*/
typedef struct tagMCQueInfo
{
    VOS_CHAR achQueName[MCQUEUE_INFO_NAME_LEN]; /* �������� */
    VOS_UINT32 ulHeader;         /* ����ħ���� */
    VOS_UINT32 ulState;          /* ����״̬ */
    VOS_UINT32 ulMod;            /* ����ģʽ */
    VOS_UINT32 ulLength;         /* ���г��� */
    VOS_UINT32 ulCurrentLen;     /* ���е�ǰ���� */
} MC_QUE_Info;


#ifndef _SYS_MSG_S_
#define _SYS_MSG_S_
typedef struct  tagSYS_MSG
{
    USHORT usMessageType;              /*����ָʾ���ͻ����*/
    USHORT usPririty;                  /*�����ȼ����û��Լ����壩,֧��4�����ȼ� */
    ULONG  ulSrcModuleID;               /*Դģ���*/
    ULONG  ulDstModuleID;               /*Ŀ��ģ���*/
    ULONG  ulSequence;                  /*�������,RPCר��*/

    ULONG  ulSrcSlotID;                 /* Դ��λ�� */
    ULONG  ulDstSlotID;                 /* Ŀ�Ĳ�λ�� */
    UCHAR  ucMsgType;                   /* ��Ϣ���ͣ���PDU, TIMER, REQUEST, NOTIFY... */
    UCHAR  ucMsgBodyStyle;              /*����ָ����Ϣͷ����Ϣ���Ƿ���һ���,��FSU����Ҫ���������Ƿ�MBuf��ʽ*/
    USHORT usMsgCode;                 /* ��Ϣ�룬������Ϣ���͵�ϸ�� */

    USHORT   usResponseType;             /* �Ƿ�Ҫ����շ��û�Ӧ��ACK/ NOACK/NEGACK*/
    USHORT   usFrameLen;                 /* frame content �ĳ��� ���û�����������   */
    VOID    *ptrMsgBody;                 /*��Ϣ��ָ��*/
    USHORT   usAppSeqNum;                /*Ӧ�ò�ϵ�кţ����ڷ��ͷ��ͽ��շ�����Ӧ��֮�佨������*/
    USHORT   usReserved;                 /*���� ���Ժ�����ʹ��*/
}  MSG_HDR_S, SYS_MSG_S;
#endif

typedef struct
{
    USHORT usApnIndex;
    USHORT usDay;

    UCHAR ucHour;
    UCHAR ucMinute;
    USHORT usUnlimited;
}DHCPS_EXPIRED_REC_S;

#ifdef __WIN32_PLATFORM__
#define MAX_APN_NUM 100
#else
#define MAX_APN_NUM 3000                   /*������APN��Ŀ*/
#endif

enum E_PERF_UNIT
{
    PERF_TYPE_SGW_FW,
    PERF_TYPE_SGW_APN_FW,
    PERF_TYPE_SGW_S5,
    PERF_TYPE_SGW_S5_ERR,
    PERF_TYPE_S11,
    PERF_TYPE_SGW_SM,
    PERF_TYPE_SGW_SM_APN,
    PERF_TYPE_SGW_USERS,
    PERF_TYPE_SGW_CDR,
    PERF_TYPE_PGW_FW,
    PERF_TYPE_PGW_APN_FW,
    PERF_TYPE_PGW_S5,
    PERF_TYPE_PGW_S5_ERR,
    PERF_TYPE_PGW_SM,
    PERF_TYPE_PGW_SM_APN,
    PERF_TYPE_PGW_USERS,
    PERF_TYPE_PGW_CDR,
    PERF_TYPE_GW_FW,
    PERF_TYPE_SM,
    PERF_TYPE_FW,
    PERF_TYPE_GCDR,
    PERF_TYPE_GTP,
    PERF_TYPE_AAA,
    PERF_TYPE_PPPC,
    PERF_TYPE_L2TPC,
    PERF_TYPE_DHCP,
    PERF_TYPE_SM_BY_BIZID,
    PERF_TYPE_FW_BY_BIZID,
    PERF_TYPE_USERS,
    PERF_TYPE_7PARSE,
    PERF_TYPE_GY,
    PERF_TYPE_PREPAIDSERVICE,
    PERF_TYPE_MBMS,
    PERF_TYPE_DIFF_PDPCONTEXT,
    PERF_TYPE_CLIT_PERFMEA,
    PERF_TYPE_FLOW_NODES,
    PERF_TYPE_CPU_RES,
    PERF_TYPE_BRD_RES,
    PERF_TYPE_GTP_TO_CG,
    PERF_TYPE_APN_SM_3G,
    PERF_TYPE_APN_SM_2G,
    PERF_TYPE_APN_SM_STATUS,
    PERF_TYPE_IMSI_GCDR,
    PERF_TYPE_APN_AAA,
    PERF_TYPE_APN_FW,
    PERF_TYPE_APN_SM_BY_BIZID,
    PERF_TYPE_HPLMN_SM,
    PERF_TYPE_SGSN_SM,
    PERF_TYPE_GX,
    PERF_TYPE_APN_GX,
    PERF_TYPE_PCRF_GX,
    PERF_TYPE_PCC,
    PERF_TYPE_APN_PCC,
    PERF_TYPE_PCRF_PCC,
    PERF_TYPE_SPGW_SM,
    PERF_TYPE_SPGW_SM_APN,
    PERF_TYPE_GW_SM,
    PERF_TYPE_GW_APN_FW,
    PERF_TYPE_SPGW_USERS,
    PERF_TYPE_APN_L2TPC,
    PERF_TYPE_PHYPORT,
    PERF_TYPE_ERR_CAUSE,
    PERF_TYPE_IPPM,
    PERF_TYPE_SPGW_APN_FW,
    PERF_TYPE_GW_USERS,
    PERF_TYPE_AAA_DIAMETER,
    PERF_TYPE_IPSEC_SA,
    PERF_TYPE_TUNNEL_IPSEC_SA,
    PERF_TYPE_VUGW_SM,
    PERF_TYPE_VUGW_FW,
    PERF_TYPE_HOMEZONE,
    PERF_TYPE_GRE,
    PERF_TYPE_7PARSE_HTTP_HEADER,
    PERF_TYPE_BWM,
    PERF_TYPE_PGW_CLIT_PERFMEA,
    PERF_TYPE_GCF,
    PERF_TYPE_CMD_OCS,
    PERF_TYPE_MSCC_OCS,
    PERF_TYPE_VPLMN_SM,
    PERF_TYPE_VPLMN_FW,
    PERF_TYPE_GW_SM_APN,
    PERF_TYPE_PREPAIDSERVICE_OCS,
    PERF_TYPE_IPSQM_ENODEB,
    PERF_TYPE_VUGW_TCPPROXY,
    PERF_TYPE_MSE_SERVER_IP,
    PERF_TYPE_SCCG_SM,
    PERF_TYPE_SCCG_SM_APN,
    PERF_TYPE_SCCG_SM_NASIP,
    PERF_TYPE_SCCG_FW,
    PERF_TYPE_SCCG_FW_APN,
    PERF_TYPE_SCCG_FW_NASIP,
    PERF_TYPE_SCCG_PGW_CDR,
    PERF_TYPE_SCCG_GCDR,
    PERF_TYPE_SCCG_GTP,
    PERF_TYPE_SCCG_7PARSE,
    PERF_TYPE_SCCG_7PARSE_HTTP_HEADER,
    PERF_TYPE_SGW_CLIT_PERFMEA,
    PERF_TYPE_SCCG_GY,
    PERF_TYPE_SCCG_PREPAIDSERVICE,
    PERF_TYPE_SCCG_GTP_TO_CG,
    PERF_TYPE_SCCG_GX,
    PERF_TYPE_SCCG_PCRF_GX,
    PERF_TYPE_SCCG_BWM,
    PERF_TYPE_SCCG_GCF,
    PERF_TYPE_SCCG_CMD_OCS,
    PERF_TYPE_SCCG_MSCC_OCS,
    PERF_TYPE_SCCG_PREPAIDSERVICE_OCS,
    PERF_TYPE_EPRPDYN_S5S8PGW,
    PERF_TYPE_EPRPDYN_S11SGW,
    PERF_TYPE_EPRPDYN_S4SGW,
    PERF_TYPE_EPRPDYN_S5S8SGW,
    PERF_TYPE_MSE_SERVER_GROUP,
    PERF_TYPE_MSE_USERS,
    PERF_TYPE_IPSQM,
    PERF_TYPE_URL_REDIRECT,
    PERF_TYPE_VSCCG_SM,
    PERF_TYPE_VSCCG_FW,
    PERF_TYPE_PREPAIDSERVICE_3GPP_AAA,
    PERF_TYPE_SERVICE_INSTANCE,
    PERF_TYPE_SCCG_SERVICE_INSTANCE,
    PERF_TYPE_SCTP,
    PERF_TYPE_EPSN_SCTP,
    PERF_TYPE_VOG_FW,
    PERF_TYPE_VOG_SVC_OPT,
    PERF_TYPE_PDSN_FW,
    PERF_TYPE_PDSN_A11,
    PERF_TYPE_PDSN_AAA,
    PERF_TYPE_PDSN_PPP,
    PERF_TYPE_PDSN_L2TP,
    PERF_TYPE_PDSN_FA,
    PERF_TYPE_PDSN_PMIP,
    PERF_TYPE_PDSN_RSVP,
    PERF_TYPE_PDSN_GY,
    PERF_TYPE_PDSN_OCS,
    PERF_TYPE_PDSN_SESSION,
    PERF_TYPE_PDSN_LI,
    PERF_TYPE_PDSN_L7PARSE,
    PERF_TYPE_PDSN_L7PARSE_HTTP_HEADER,
    PERF_TYPE_EPSN_PCRF_HOST_GX,
    PERF_TYPE_PDSN_PCF_FW,
    PERF_TYPE_PDSN_PCF_CM,
    PERF_TYPE_PDSN_DN_SESSION,
    PERF_TYPE_PDSN_DN_FW,
    PERF_TYPE_PDSN_VPDSN_SM,
    PERF_TYPE_PDSN_VPDSN_FW,
    PERF_TYPE_PDSN_GX,
    PERF_TYPE_PDSN_PCRF_GX,
    PERF_TYPE_IP_POOL,
    PERF_TYPE_HSGW_FW,
    PERF_TYPE_HSGW_STA,
    PERF_TYPE_HSGW_S2A,
    PERF_TYPE_HSGW_RSVP,
    PERF_TYPE_HSGW_SESSION,
    PERF_TYPE_HSGW_PCF_FW,
    PERF_TYPE_HSGW_PCF_CM,
    PERF_TYPE_HSGW_GCDR,
    PERF_TYPE_HSGW_GTP,
    PERF_TYPE_HSGW_GX,
    PERF_TYPE_HSGW_DNS,
    PERF_TYPE_DIAMETER_DRA,
    PERF_TYPE_EPSN_DIAMETER_DRA,
    PERF_TYPE_PCRF_HOST_GX,
    PERF_TYPE_PCRF_HOST_PCC,
    PERF_TYPE_ANTI_SPOOFING,
    PERF_TYPE_EPSN_ANTI_SPOOFING,
    PERF_TYPE_KEY_RESOURCES_MONITOR,
    PERF_TYPE_BUTT
};

enum E_PERF_ENTITY
{
    PERF_ENTITY_BEGIN = 10000,

    PERF_TYPE_SGW_SM_BEGIN =  13000,
    PERF_TYPE_SGW_SM_S5S8_CURRENT_GTP_PATH_NUM,
    PERF_TYPE_SGW_SM_S5S8_GTP_PEER_EQUIP_RESTARTS,
    PERF_TYPE_SGW_SM_S5S8_GTP_C_PATH_INTERRUPTIONS,
    PERF_TYPE_SGW_SM_S5S8_GTP_U_PATH_INTERRUPTIONS,
    PERF_TYPE_SGW_SM_S5S8_PMIP_PATH_INTERRUPTIONS,
    PERF_TYPE_SGW_SM_S5S8_CURRENT_PMIP_PATH_NUM,
    PERF_TYPE_SGW_SM_S11_S4_CURRENT_GTP_PATH_NUM,
    PERF_TYPE_SGW_SM_S11_S4_GTP_PEER_EQUIP_RESTARTS,
    PERF_TYPE_SGW_SM_S11_S4_GTP_C_PATH_INTERRUPTIONS,
    PERF_TYPE_SGW_SM_S11_S4_GTP_U_PATH_INTERRUPTIONS,
    PERF_TYPE_SGW_SM_CRE_BEARER_CONTEXT_REQ,
    PERF_TYPE_SGW_SM_SUCC_BEARER_CONTEXT_CRE,
    PERF_TYPE_SGW_SM_ALL_BEARER_GROSS_LIFETIME_CONTEXTS_S11_S4,
    PERF_TYPE_SGW_SM_ALL_BEARER_GROSS_LIFETIME_CONTEXTS_DEDICATED,
    PERF_TYPE_SGW_SM_GROSS_NEW_CRE_BEARER_CONTEXTS_S11_S4,
    PERF_TYPE_SGW_SM_GROSS_NEW_CRE_SESSIONS_S11_S4,
    PERF_TYPE_SGW_SM_GROSS_NEW_CRE_BEARER_CONTEXTS_DEDICATED,
    PERF_TYPE_SGW_SM_MAX_SIM_ACT_BEARER_CONTEXTS_S11_S4,
    PERF_TYPE_SGW_SM_MAX_SIM_ACT_SESSIONS_S11_S4,
    PERF_TYPE_SGW_SM_MAX_SIM_ACT_BEARER_CONTEXTS_DEDICATED,
    PERF_TYPE_SGW_SM_AVG_ACT_BEARER_CONTEXTS_S11_S4,
    PERF_TYPE_SGW_SM_AVG_ACT_SESSIONS_S11_S4,
    PERF_TYPE_SGW_SM_AVG_ACT_BEARER_CONTEXTS_DEDICATED,
    PERF_TYPE_SGW_SM_CURRENT_ACT_BEARER_CONTEXTS_S11_S4,
    PERF_TYPE_SGW_SM_CURRENT_ACT_SESSIONS_S11_S4,
    PERF_TYPE_SGW_SM_CURRENT_ACT_BEARER_CONTEXTS_DEDICATED,
    PERF_TYPE_SGW_SM_PEAK_CRE_BEARER_REQ_RATE_S11_S4,
    PERF_TYPE_SGW_SM_FAIL_BEARER_CONTEXT_CRE_S11_S4_NO_SDB_RES,
    PERF_TYPE_SGW_SM_FAIL_BEARER_CONTEXT_CRE_S11_S4_NO_LICENSE_RES,
    PERF_TYPE_SGW_SM_FAIL_BEARER_CONTEXT_CRE_S11_S4_NO_QOS_RES,
    PERF_TYPE_SGW_SM_FAIL_BEARER_CONTEXT_DEL_S11_S4_NON_EXIST_CONTEXT,
    PERF_TYPE_SGW_SM_FAIL_BEARER_CONTEXT_CRE_S11_S4_VER_NOT_SUPPORT,
    PERF_TYPE_SGW_SM_FAIL_BEARER_CONTEXT_CRE_S11_S4_INVAL_LENGTH,
    PERF_TYPE_SGW_SM_FAIL_BEARER_CONTEXT_CRE_S11_S4_SERVICE_NOT_SUPPORTED,
    PERF_TYPE_SGW_SM_FAIL_BEARER_CONTEXT_CRE_S11_S4_INCORRECT_MAN_IE,
    PERF_TYPE_SGW_SM_FAIL_BEARER_CONTEXT_CRE_S11_S4_MISS_MAN_IE,
    PERF_TYPE_SGW_SM_FAIL_BEARER_CONTEXT_CRE_S11_S4_INCORRECT_OPT_IE,
    PERF_TYPE_SGW_SM_FAIL_BEARER_CONTEXT_CRE_S11_S4_SYS_FAIL,
    PERF_TYPE_SGW_SM_FAIL_BEARER_CONTEXT_CRE_S11_S4_TFT_SEM_ERR,
    PERF_TYPE_SGW_SM_FAIL_BEARER_CONTEXT_CRE_S11_S4_TFT_SYN_ERR,
    PERF_TYPE_SGW_SM_FAIL_BEARER_CONTEXT_CRE_S11_S4_SEM_ERR_PKT_FILTER,
    PERF_TYPE_SGW_SM_FAIL_BEARER_CONTEXT_CRE_S11_S4_SYN_ERR_PKT_FILTER,
    PERF_TYPE_SGW_SM_FAIL_BEARER_CONTEXT_CRE_S11_S4_MISS_OR_UNKNOWN_APN,
    PERF_TYPE_SGW_SM_FAIL_BEARER_CONTEXT_CRE_S11_S4_UNEXP_REPEATED_IE,
    PERF_TYPE_SGW_SM_FAIL_BEARER_CONTEXT_CRE_S11_S4_GRE_KEY_NOT_FOUND,
    PERF_TYPE_SGW_SM_FAIL_BEARER_CONTEXT_CRE_S11_S4_REALLOC_FAIL,
    PERF_TYPE_SGW_SM_FAIL_BEARER_CONTEXT_CRE_S11_S4_DENIED_RAT,
    PERF_TYPE_SGW_SM_FAIL_BEARER_CONTEXT_CRE_S11_S4_PREFERED_PDN_TYPE_NOT_SUPPORTED,
    PERF_TYPE_SGW_SM_FAIL_BEARER_CONTEXT_CRE_S11_S4_ALL_DYNAMIC_ADDR_OCCUPIED,
    PERF_TYPE_SGW_SM_FAIL_BEARER_CONTEXT_CRE_S11_S4_UE_CONTEXT_WITHOUT_TFT_ALREADY_ACT,
    PERF_TYPE_SGW_SM_FAIL_BEARER_CONTEXT_CRE_S11_S4_PROTOCOL_NOT_SUPPORTED,
    PERF_TYPE_SGW_SM_FAIL_BEARER_CONTEXT_CRE_S11_S4_NO_MEM_AVAILABLE,
    PERF_TYPE_SGW_SM_FAIL_BEARER_CONTEXT_CRE_S11_S4_USER_AUTH_FAIL,
    PERF_TYPE_SGW_SM_FAIL_BEARER_CONTEXT_CRE_S11_S4_NO_SUBSCRIPTION,
    PERF_TYPE_SGW_SM_RCV_DHCPV4_DIS_FROM_UE_PKTS,
    PERF_TYPE_SGW_SM_RCV_DHCPV4_REQ_FROM_UE_PKTS,
    PERF_TYPE_SGW_SM_RCV_DHCPV4_DEC_FROM_UE_PKTS,
    PERF_TYPE_SGW_SM_RCV_DHCPV4_REL_FROM_UE_PKTS,
    PERF_TYPE_SGW_SM_RCV_DHCPV4_INFO_FROM_UE_PKTS,
    PERF_TYPE_SGW_SM_SEND_DHCPV4_OFFER_TO_UE_PKTS,
    PERF_TYPE_SGW_SM_SEND_DHCPV4_ACK_TO_UE_PKTS,
    PERF_TYPE_SGW_SM_SEND_DHCPV4_NAK_TO_UE_PKTS,
    PERF_TYPE_SGW_SM_RCV_DHCPV6_INFO_REQ_FROM_UE_PKTS,
    PERF_TYPE_SGW_SM_SEND_DHCPV6_ACK_TO_UE_PKTS,
    PERF_TYPE_SGW_SM_RCV_IPV6_RS_FROM_UE_PKTS,
    PERF_TYPE_SGW_SM_SEND_IPV6_RA_PKTS,
    PERF_TYPE_SGW_SM_ATTEMPT_NUM_PGW_DEDICAT_BEARER_CRT,
    PERF_TYPE_SGW_SM_SUCC_NUM_PGW_DEDICAT_BEARER_CRT,
    PERF_TYPE_SGW_SM_FAIL_NUM_PGW_DEDICAT_BEARER_CRT,
    PERF_TYPE_SGW_SM_MEAN_NUM_EPS_BEARER,
    PERF_TYPE_SGW_SM_MEAN_NUM_EPS_SESSION,
    PERF_TYPE_SGW_SM_MAX_NUM_EPS_BEARER,
    PERF_TYPE_SGW_SM_MAX_NUM_EPS_SESSION,
    PERF_TYPE_SGW_SM_ATTEMPT_NUM_PGW_DEDICAT_BEARER_DEL,
    PERF_TYPE_SGW_SM_SUCC_NUM_PGW_DEDICAT_BEARER_DEL,
    PERF_TYPE_SGW_SM_FAIL_NUM_PGW_DEDICAT_BEARER_DEL,
    PERF_TYPE_SGW_SM_ATTEMPT_NUM_MME_DEDICAT_BEARER_DEL,
    PERF_TYPE_SGW_SM_SUCC_NUM_MME_DEDICAT_BEARER_DEL,
    PERF_TYPE_SGW_SM_FAIL_NUM_MME_DEDICAT_BEARER_DEL,
    PERF_TYPE_SGW_SM_ATTEMPT_NUM_PGW_DEDICAT_BEARER_MOD_NO_QOS_U,
    PERF_TYPE_SGW_SM_SUCC_NUM_PGW_DEDICAT_BEARER_MOD_NO_QOS_U,
    PERF_TYPE_SGW_SM_FAIL_NUM_PGW_DEDICAT_BEARER_MOD_NO_QOS_U,
    PERF_TYPE_SGW_SM_ATTEMPT_NUM_PGW_DEDICAT_BEARER_MOD_QOS_U,
    PERF_TYPE_SGW_SM_SUCC_NUM_PGW_DEDICAT_BEARER_MOD_QOS_U,
    PERF_TYPE_SGW_SM_FAIL_NUM_PGW_DEDICAT_BEARER_MOD_QOS_U,
    PERF_TYPE_SGW_SM_ATTEMPT_NUM_HSS_QOS_MOD,
    PERF_TYPE_SGW_SM_SUCC_NUM_HSS_QOS_MOD,
    PERF_TYPE_SGW_SM_FAIL_NUM_HSS_QOS_MOD,
    PERF_TYPE_SGW_SM_ATTEMPT_NUM_UE_BEARER_RES_MOD,
    PERF_TYPE_SGW_SM_SUCC_NUM_UE_BEARER_RES_MOD,
    PERF_TYPE_SGW_SM_FAIL_NUM_UE_BEARER_RES_MOD,
    PERF_TYPE_SGW_SM_OWN_CUST_ATTEMPT_COUNT,
    PERF_TYPE_SGW_SM_OWN_CUST_ACCEPT_COUNT,
    PERF_TYPE_SGW_SM_OWN_CUST_REJECT_COUNT,
    PERF_TYPE_SGW_SM_ROAM_ATTEMPT_COUNT,
    PERF_TYPE_SGW_SM_ROAM_ACCEPT_COUNT,
    PERF_TYPE_SGW_SM_ROAM_REJECT_COUNT,
    PERF_TYPE_SGW_SM_OWN_CUST_BEARER_ATTEMPT_COUNT,
    PERF_TYPE_SGW_SM_OWN_CUST_BEARER_ACCEPT_COUNT,
    PERF_TYPE_SGW_SM_OWN_CUST_BEARER_REJECT_COUNT,
    PERF_TYPE_SGW_SM_ROAM_BEARER_ATTEMPT_COUNT,
    PERF_TYPE_SGW_SM_ROAM_BEARER_ACCEPT_COUNT,
    PERF_TYPE_SGW_SM_ROAM_BEARER_REJECT_COUNT,
    PERF_TYPE_SGW_SM_S1_RELEASE_ATTEMPT_COUNT,
    PERF_TYPE_SGW_SM_S1_RELEASE_ACCEPT_COUNT,
    PERF_TYPE_SGW_SM_S1_RELEASE_REJECT_COUNT,
    PERF_TYPE_SGW_SM_NET_SERV_REQ_ATTEMPT_COUNT,
    PERF_TYPE_SGW_SM_NET_SERV_REQ_ACCEPT_COUNT,
    PERF_TYPE_SGW_SM_NET_SERV_REQ_REJECT_COUNT,
    PERF_TYPE_SGW_SM_ROAMING_SESSION_ACTIVE_CURRENT,
    PERF_TYPE_SGW_SM_ROAMING_SESSION_ACTIVE_AVERAGE,
    PERF_TYPE_SGW_SM_ROAMING_SESSION_ACTIVE_MAX,
    PERF_TYPE_SGW_SM_ROAMING_BEARER_PDP_ACTIVE_CURRENT,
    PERF_TYPE_SGW_SM_ROAMING_BEARER_PDP_ACTIVE_AVERAGE,
    PERF_TYPE_SGW_SM_ROAMING_BEARER_PDP_ACTIVE_MAX,
    PERF_TYPE_SGW_SM_CONTENT_CHARGE_PDP_ACTIVE_CURRENT,
    PERF_TYPE_SGW_SM_CONTENT_CHARGE_PDP_ACTIVE_AVERAGE,
    PERF_TYPE_SGW_SM_CONTENT_CHARGE_PDP_ACTIVE_MAX,
    PERF_TYPE_SGW_SM_SIMULTANEOUSLY_ATTACHED_ACTIVE_CURRENT,
    PERF_TYPE_SGW_SM_SIMULTANEOUSLY_ATTACHED_ACTIVE_AVERAGE,
    PERF_TYPE_SGW_SM_MAX_SIMULTANEOUSLY_ATTACHED_ACTIVE,
    PERF_TYPE_SGW_RCV_SUSPEND_NOTIFICATION_MSG,
    PERF_TYPE_SGW_SND_SUCESS_SUSPEND_ACK_MSG,
    PERF_TYPE_SGW_RCV_RESUME_NOTIFICATION_MSG,
    PERF_TYPE_SGW_SND_SUCESS_RESUME_ACK_MSG,
    PERF_TYPE_SGW_SMFAIL_BEARER_CONTEXT_CRE_EXTERNAL,
    PERF_TYPE_SGW_SM_AUX_BEGIN,
    PERF_TYPE_SGW_SM_S5S8_CURRENT_GTP_PATH,
    PERF_TYPE_SGW_SM_S5S8_CURRENT_PMIP_PATH,
    PERF_TYPE_SGW_SM_S11_CURRENT_GTP_PATH,
    PERF_TYPE_SGW_SM_CURRENT_ACT_BEARER_CONTEXTS_S11_S4_REALTIME,
    PERF_TYPE_SGW_SM_CURRENT_ACT_BEARER_CONTEXTS_DEDICATED_REALTIME,
    PERF_TYPE_SGW_SM_CURRENT_ACT_SESSIONS_S11_S4_REALTIME,
    PERF_TYPE_SGW_SM_NUM_EPS_BEARER,
    PERF_TYPE_SGW_SM_NUM_EPS_SESSION,
    PERF_TYPE_SGW_SM_ROAMING_SESSION_ACTIVE_CURRENT_REALTIME,
    PERF_TYPE_SGW_SM_ROAMING_BEARER_ACTIVE_CURRENT_REALTIME,
    PERF_TYPE_SGW_SM_CONTEXT_CHARGE_PDP_ACTIVE_CURRENT_REALTIME,
    PERF_TYPE_SGW_SM_SIMULTANEOUSLY_ATTACHED_ACTIVE_CURRENT_REALTIME,
    PERF_TYPE_SGW_SM_CURRENT_ACT_BEARER_CONTEXTS_S11_S4_REALTIME_AUX,
    PERF_TYPE_SGW_SM_CURRENT_ACT_BEARER_CONTEXTS_DEDICATED_REALTIME_AUX,
    PERF_TYPE_SGW_SM_CURRENT_ACT_SESSIONS_S11_S4_REALTIME_AUX,
    PERF_TYPE_SGW_SM_CRE_BEARER_CONTEXT_REQ_AUX,
    PERF_TYPE_SGW_SM_NUM_EPS_BEARER_AUX,
    PERF_TYPE_SGW_SM_NUM_EPS_SESSION_AUX,
    PERF_TYPE_SGW_SM_ROAMING_SESSION_ACTIVE_CURRENT_REALTIME_AUX,
    PERF_TYPE_SGW_SM_ROAMING_BEARER_ACTIVE_CURRENT_REALTIME_AUX,
    PERF_TYPE_SGW_SM_CONTENT_CHARGE_PDP_ACTIVE_CURRENT_REALTIME_AUX,
    PERF_TYPE_SGW_SM_SIMULTANEOUSLY_ATTACHED_ACTIVE_CURRENT_REALTIME_AUX,
    PERF_TYPE_SGW_SM_END,

    PERF_TYPE_PGW_S5_BEGIN =  16000,
    PERF_TYPE_PGW_S5_RCV_GTP_ERR_SIG_TRAFFIC_PKTS,
    PERF_TYPE_PGW_S5_RCV_GTP_UNEXPECTED_SIG_TRAFFIC_PKTS,
    PERF_TYPE_PGW_S5_RCV_GTP_SIG_TRAFFIC_PKTS,
    PERF_TYPE_PGW_S5_SND_GTP_SIG_TRAFFIC_PKTS,
    PERF_TYPE_PGW_S5_RCV_GTP_SIG_TRAFFIC_PEAK_PKTSPS,
    PERF_TYPE_PGW_S5_SND_GTP_SIG_TRAFFIC_PEAK_PKTSPS,
    PERF_TYPE_PGW_S5_RCV_GTP_PATH_REQ_MSG,
    PERF_TYPE_PGW_S5_SND_GTP_PATH_RSP_MSG,
    PERF_TYPE_PGW_S5_SND_GTP_PATH_REQ_MSG,
    PERF_TYPE_PGW_S5_RCV_GTP_PATH_RSP_MSG,
    PERF_TYPE_PGW_S5_RCV_CRE_DEFAULT_BEARER_REQ_MSG,
    PERF_TYPE_PGW_S5_SND_SUCC_CRE_DEFAULT_BEARER_RSP_MSG,
    PERF_TYPE_PGW_S5_SND_FAIL_CRE_DEFAULT_BEARER_RSP_MSG,
    PERF_TYPE_PGW_S5_SND_CRE_DEDICATED_BEARER_REQ_MSG,
    PERF_TYPE_PGW_S5_RCV_SUCC_CRE_DEDICATED_BEARER_RSP_MSG,
    PERF_TYPE_PGW_S5_RCV_FAIL_CRE_DEDICATED_BEARER_RSP_MSG,
    PERF_TYPE_PGW_S5_SND_UPD_BEARER_REQ_MSG,
    PERF_TYPE_PGW_S5_RCV_SUCC_UPD_BEARER_RSP_MSG,
    PERF_TYPE_PGW_S5_RCV_FAIL_UPD_BEARER_RSP_MSG,
    PERF_TYPE_PGW_S5_RCV_UPD_BEARER_REQ_MSG,
    PERF_TYPE_PGW_S5_SND_SUCC_UPD_BEARER_RSP_MSG,
    PERF_TYPE_PGW_S5_SND_FAIL_UPD_BEARER_RSP_MSG,
    PERF_TYPE_PGW_S5_SND_DEL_BEARER_REQ_MSG,
    PERF_TYPE_PGW_S5_RCV_SUCC_DEL_BEARER_RSP_MSG,
    PERF_TYPE_PGW_S5_RCV_FAIL_DEL_BEARER_RSP_MSG,
    PERF_TYPE_PGW_S5_RCV_DEL_BEARER_REQ_MSG,
    PERF_TYPE_PGW_S5_SND_SUCC_DEL_BEARER_RSP_MSG,
    PERF_TYPE_PGW_S5_SND_FAIL_DEL_BEARER_RSP_MSG,
    PERF_TYPE_PGW_S5_RCV_REQ_BEARER_RES_MOD_MSG,
    PERF_TYPE_PGW_S5_RCV_PMIP_SIG_TRAFFIC_PKTS,
    PERF_TYPE_PGW_S5_SND_PMIP_SIG_TRAFFIC_PKTS,
    PERF_TYPE_PGW_S5_RCV_PMIP_ERR_SIG_TRAFFIC_PKTS,
    PERF_TYPE_PGW_S5_RCV_PMIP_UNEXPECTED_SIG_TRAFFIC_PKTS,
    PERF_TYPE_PGW_S5_RCV_PMIP_SIG_TRAFFIC_PEAK_PKTSPS,
    PERF_TYPE_PGW_S5_SND_PMIP_SIG_TRAFFIC_PEAK_PKTSPS,
    PERF_TYPE_PGW_S5_RCV_PMIP_PATH_REQ_MSG,
    PERF_TYPE_PGW_S5_SND_PMIP_PATH_RSP_MSG,
    PERF_TYPE_PGW_S5_SND_PMIP_PATH_REQ_MSG,
    PERF_TYPE_PGW_S5_RCV_PMIP_PATH_RSP_MSG,
    PERF_TYPE_PGW_S5_RCV_LIFETIME_NOT_EQUAL_ZERO_PBU_MSG,
    PERF_TYPE_PGW_S5_RCV_LIFETIME_EQUAL_ZERO_PBU_MSG,
    PERF_TYPE_PGW_S5_SND_STATUS_SMALLER_TO128_PBA_MSG,
    PERF_TYPE_PGW_S5_SND_STATUS_BIGER_THAN128_PBA_MSG,
    PERF_TYPE_PGW_S5_SND_BRI_MSG,
    PERF_TYPE_PGW_S5_RCV_STATUS_SMALLER_TO128_BRA_MSG,
    PERF_TYPE_PGW_S5_RCV_STATUS_BIGER_THAN128_BRA_MSG,
    PERF_TYPE_PGW_RCV_DHCPV4_DIS_FROM_UE_PKTS,
    PERF_TYPE_PGW_RCV_DHCPV4_OFFER_FROM_SERVER_PKTS,
    PERF_TYPE_PGW_RCV_DHCPV4_REQ_FROM_UE_PKTS,
    PERF_TYPE_PGW_RCV_DHCPV4_ACK_FROM_SERVER_PKTS,
    PERF_TYPE_PGW_RCV_DHCPV4_NAK_FROM_SERVER_PKTS,
    PERF_TYPE_PGW_RCV_DHCPV4_DEC_FROM_UE_PKTS,
    PERF_TYPE_PGW_RCV_DHCPV4_REL_FROM_UE_PKTS,
    PERF_TYPE_PGW_RCV_DHCPV4_INFORM_FROM_UE_PKTS,
    PERF_TYPE_PGW_SEND_DHCPV4_OFFER_TO_UE_PKTS,
    PERF_TYPE_PGW_SEND_DHCPV4_ACK_TO_UE_PKTS,
    PERF_TYPE_PGW_SEND_DHCPV4_NAK_TO_UE_PKTS,
    PERF_TYPE_PGW_SEND_DHCPV4_DIS_TO_SERVER_PKTS,
    PERF_TYPE_PGW_SEND_DHCPV4_REQ_TO_SERVER_PKTS,
    PERF_TYPE_PGW_SEND_DHCPV4_DEC_TO_SERVER_PKTS,
    PERF_TYPE_PGW_SEND_DHCPV4_REL_TO_SERVER_PKTS,
    PERF_TYPE_PGW_RCV_DHCPV6_INFO_REQ_FROM_UE_PKTS,
    PERF_TYPE_PGW_SEND_DHCPV6_ACK_TO_UE_PKTS,
    PERF_TYPE_PGW_RCV_IPV6_RS_FROM_UE_PKTS,
    PERF_TYPE_PGW_SEND_IPV6_RA_FROM_UE_PKTS,
    PERF_TYPE_PGW_S5_RCV_LIFETIME_NOT_EQUAL_ZERO_PBU_MSG_FOR_HO_HSGW,
    PERF_TYPE_PGW_S5_SND_SUCC_PBA_MSG_FOR_HO_HSGW,
    PERF_TYPE_PGW_S5_RCV_LIFETIME_NOT_EQUAL_ZERO_PBU_MSG_FOR_HO_LTOC,
    PERF_TYPE_PGW_S5_SND_SUCC_PBA_MSG_FOR_HO_LTOC,
    PERF_TYPE_PGW_S5_RCV_CRE_DEFAULT_BEARER_REQ_MSG_FOR_HO_CTOL,
    PERF_TYPE_PGW_S5_SND_SUCC_CRE_DEFAULT_BEARER_RSP_MSG_FOR_HO_CTOL,
    PERF_TYPE_PGW_S2B_RCV_CRE_DEFAULT_BEARER_REQ_MSG_FOR_HO_LTOW,
    PERF_TYPE_PGW_S2B_SND_SUCC_CRE_DEFAULT_BEARER_RSP_MSG_FOR_HO_LTOW,
    PERF_TYPE_PGW_S5_SND_SUCC_CRE_DEFAULT_BEARER_RSP_MSG_FOR_HO_WTOL,
    PERF_TYPE_PGW_S2A_RCV_CRE_DEFAULT_BEARER_REQ_MSG_FOR_HO_LTOW,
    PERF_TYPE_PGW_S2A_SND_SUCC_CRE_DEFAULT_BEARER_RSP_MSG_FOR_HO_LTOW,
    PERF_TYPE_PGW_S5_AUX_BEGIN,
    PERF_TYPE_PGW_S5_RCV_GTP_SIG_TRAFFIC_PKTS_AUX,
    PERF_TYPE_PGW_S5_SND_GTP_SIG_TRAFFIC_PKTS_AUX,
    PERF_TYPE_PGW_S5_RCV_PMIP_SIG_TRAFFIC_PKTS_AUX,
    PERF_TYPE_PGW_S5_SND_PMIP_SIG_TRAFFIC_PKTS_AUX,
    PERF_TYPE_PGW_S5_END,

    PERF_ENTITY_BUTT
};

/* ϵͳ��Ϣ���Ͷ��� */
#ifndef _MsgType_E_
#define _MsgType_E_
enum ucMsgType
{
    /* ��FSU���õ���Ϣ���� */
    MSG_TIMER,
    MSG_PDU,
    MSG_NOTIFY,
    MSG_REQUEST,
    MSG_ACK,

    /* ֻ�����ذ�ʹ�õ���Ϣ���� */
    MSG_CONF,
    MSG_BACKUP,     /* ���ݱ�����Ϣ Added by ������ */

    MSG_SPU_TEST,

    /* ���ڴ�����µ���Ϣ���� */
    MSG_TYPE_END
};
#endif

typedef struct tagAM_CTX_APN_INFO_S
{
    USHORT usApnIndex;
    USHORT usVirtualapnIndex;
    USHORT usNoConfigApnIndex;
    USHORT usAliaCdbIndex;
    UCHAR ucVirtualapnFlag;
    UCHAR aucReserved[3];
}AM_CTX_APN_INFO_S;


/* ǿ�ƴ�ӡ��������������� */
#define PTM_PRINT_EXCEPTION_END PTM_Print_Exception_End

/* ��ӡ�쳣�ַ��� */
#define PTM_PRINT_EXCEPTION_INFO PTM_Print_Exception_Info
#if 0
/* ��ӡ�쳣����������abc=1 */
#define PTM_PRINT PTM_Print_With_Equal

/* ��ӡ���ã�����abc:1 (������gm������ִ�е�������ʱ������Խ�������ۼ�)*/
#define PTM_PRINT_WITH_DOT PTM_Print_With_Dot

/* ��ӡ�쳣����������abc=1 */
#define PTM_PRINT_EXCEPTION     PTM_Print_Exception
#endif
/* ѭ����ӡĳ�쳣���������ó���:�����쳣��������ʵ������ */
#define PTM_PRINT_EXCEPTION_LOOP PTM_Print_Exception_Loop
#define PTM_PRINT_STRING_WITH_ARGUMENTS PTM_Print_String_With_Arguments

#ifndef __tabSPINLOCK_T__
#define __tabSPINLOCK_T__
typedef struct
{
  volatile unsigned int lock;
} spinLock, spinlock_t;
#endif


#ifdef __X86_PLATFORM__
#define PGP_SpinLockNoSchedule(pstLock)                   MEM_SpinLockCTL(pstLock,__FILE__, __LINE__)
#define PGP_SpinTryLockNoSchedule(pstLock)                MEM_SpinTryLockCTL(pstLock,__FILE__, __LINE__)
#define PGP_SpinUnlockNoSchedule(pstLock)                 MEM_SpinUnlockCTL(pstLock, __FILE__, __LINE__)

#define PGP_RWReadLockNoSchedule(pstLock)                 MEM_RWReadLockCTL(pstLock)
#define PGP_RWReadUnlockNoSchedule(pstLock)               MEM_RWReadUnlockCTL(pstLock)
#define PGP_RWWriteLockNoSchedule(pstLock)                MEM_RWWriteLockCTL(pstLock)
#define PGP_RWWriteUnlockNoSchedule(pstLock)              MEM_RWWriteUnlockCTL(pstLock)
#else
#define PGP_SpinLockNoSchedule(pstLock)                   spin_lock(pstLock)
//#define PGP_SpinTryLockNoSchedule(pstLock)                spin_trylock(pstLock)
#define PGP_SpinUnlockNoSchedule(pstLock)                 spin_unlock(pstLock)

#define PGP_RWReadLockNoSchedule(pstLock)                 VOS_MCRWReadLock(*pstLock, (VOS_CHAR*)__FILE__, __LINE__)
#define PGP_RWReadUnlockNoSchedule(pstLock)               VOS_MCRWReadUnlock(*pstLock, (VOS_CHAR*)__FILE__, __LINE__)
#define PGP_RWWriteLockNoSchedule(pstLock)                VOS_MCRWWriteLock(*pstLock, (VOS_CHAR*)__FILE__, __LINE__)
#define PGP_RWWriteUnlockNoSchedule(pstLock)              VOS_MCRWWriteUnlock(*pstLock, (VOS_CHAR*)__FILE__, __LINE__)
#endif


// SG��ʹ��
#define PGP_ShrRWLockCreate(name,plock)  VOS_MCRWLockCreate(name,plock,1)

typedef enum tagDBG_LOG_LEVEL
{
    DBG_LOG_INFO,           /* 0 �¼���¼����Ӧ�����־��"INFO" */
    DBG_LOG_WARNING,        /* 1�澯��Ϣ����Ӧ�����־��" WARNING" */
    DBG_LOG_ERROR,          /* 2 ������Ϣ����Ӧ�����־��" ERROR" */
    DBG_LOG_END             /* 3 No use */
}DBG_LOG_LEVEL_E;

#define PGP_TmNowInSec VOS_Tm_NowInSec

#define VOS_StrCmp(x,y) strcmp(x,y)


/*************************************************
**** This Macro get the handle value of DLL node ****
**************************************************/
#define DLL_GET_HANDLE(pNode)	((pNode)->ulHandle)

#define UDPS_SET_CHECK_SUM_ENABLE(pstNode) ((pstNode)->ucControlCheckSum |= 1)

#define  PGP_SYS_MSG(pMsgBuff)              ((SYS_MSG_S*)((UCHAR *)(pMsgBuff) - sizeof(SYS_MSG_S)))
#define  RTD_SET_MSGCODE(pMsg, MsgCode)     (PGP_SYS_MSG(pMsg)->usMsgCode = (MsgCode))


/*==============================================*
*      constants or macros define              *
*----------------------------------------------*/
/* BEGIN: modified by wangtao at 2012/5/2 for SPU2.0 FCM */

typedef struct tag_Fwd_ComChannel
{
    PF_UCHAR  ucMsgCode;                  /* ģ�����Ϣ�룬��ǰת����ƽ̨��û��ʹ�ã���������ҵ������չʹ�� */

    union
    {
        PF_UCHAR  ucPriority;
        struct
        {
        #if(FWD_LITTLE_ENDIAN == FWD_YES)
            PF_UCHAR ucPriority:1;  /* PFͨ��Priority��PPEͷ������ǣ�
                                    Priority=H���ΪInter-CPU Message��Priority=L���ΪInter-CPU Signal */

            PF_UCHAR ucOrdered:1;  /* �����Ƿ���Ordered=1����Ǳ�����Ҫ����PF��Hash�㷨��
                                   ������ת�����̶���vcpu���ն��У�Ordered=0����Ǳ��Ĳ���Ҫ����
                                   PF����ѯ��ʽ��������ת������ͬ��vcpu���ն��� */
            PF_UCHAR ucMsgType:6;   /*msg type*/
        #else
            PF_UCHAR ucMsgType:6;   /*msg type*/
            PF_UCHAR ucOrdered:1;  /* �����Ƿ���Ordered=1����Ǳ�����Ҫ����PF��Hash�㷨��
                                   ������ת�����̶���vcpu���ն��У�Ordered=0����Ǳ��Ĳ���Ҫ����
                                   PF����ѯ��ʽ��������ת������ͬ��vcpu���ն��� */

            PF_UCHAR ucPriority:1;  /* PFͨ��Priority��PPEͷ������ǣ�
                                    Priority=H���ΪInter-CPU Message��Priority=L���ΪInter-CPU Signal */
		#endif
        }s;
    }Priority;

    PF_USHORT usStake;                     /* ���ĵĿ�ʼ�ֽ�ƫ�Ƴ���*/

    union
    {
        PF_USHORT usDstCompInfo;               /*comp type + submodule id*/
        struct
        {
        #if(FWD_LITTLE_ENDIAN == FWD_YES)
            PF_UCHAR ucDstCompTypeHi:6;     /* Ŀ��������� high 6 bit*/
            PF_UCHAR ucDstCompRsv:2;
            PF_UCHAR ucDstSubModuleId:2;    /* Ŀ����ģ��Id,�������� */
            PF_UCHAR ucDstCompTypeLo:6;     /* Ŀ��������� low 6 bit*/
        #else
            PF_UCHAR ucDstCompRsv:2;
            PF_UCHAR ucDstCompTypeHi:6;     /* Ŀ��������� high 6 bit*/
            PF_UCHAR ucDstCompTypeLo:6;     /* Ŀ��������� low 6 bit*/
            PF_UCHAR ucDstSubModuleId:2;    /* Ŀ����ģ��Id */
        #endif
        }s;
    }DstModule;

    union
    {
        PF_USHORT usDstNode;               /* slot/cpu/vcpu�Ļ�ϱ��� */
        struct
        {
        #if(FWD_LITTLE_ENDIAN == FWD_YES)
                PF_UCHAR ucDstCpuId:3;             /* Ŀ��CPU */
                PF_UCHAR ucDstSlotId:5;            /* Ŀ���߼���λ�� */
                PF_UCHAR usDstOSSGIndex:7;         /*Ŀ��Vcpu���߼�����id */
                PF_UCHAR ucDstSGReserve:1;
        #else
                PF_UCHAR ucDstSlotId:5;            /* Ŀ���߼���λ�� */
                PF_UCHAR ucDstCpuId:3;             /* Ŀ��CPU */
                PF_UCHAR ucDstSGReserve:1;
                PF_UCHAR usDstOSSGIndex:7;           /*Ŀ��Vcpu���߼�����id */
        #endif
        }s;
   }DstNode;

    union
    {
        PF_USHORT usSrcCompInfo;            /*comp type + submodule id*/
        struct
        {
        #if(FWD_LITTLE_ENDIAN == FWD_YES)
            PF_UCHAR ucSrcCompTypeHi: 6;      /* Դ������� high 6 bit*/
            PF_UCHAR ucSrcCompTypeRsv: 2;
            PF_UCHAR ucSrcSubModuleId: 2;     /* Դ��ģ��Id, ��������*/
            PF_UCHAR ucSrcCompTypeLo: 6;      /* Դ������� low 6 bit*/
        #else
            PF_UCHAR ucSrcCompTypeRsv: 2;
            PF_UCHAR ucSrcCompTypeHi: 6;      /* Դ������� high 6 bit*/
            PF_UCHAR ucSrcCompTypeLo: 6;      /* Դ������� low 6 bit*/
            PF_UCHAR ucSrcSubModuleId: 2;     /* Դ��ģ��Id, ��������*/
        #endif
        }s;
    }SrcModule;

    union
    {
        PF_USHORT usSrcNode;               /* slot/cpu/vcpu�Ļ�ϱ��� */
        struct
        {
        #if(FWD_LITTLE_ENDIAN == FWD_YES)
                    PF_UCHAR ucSrcCpuId: 3;            /* ԴCPU ID */
                    PF_UCHAR ucSrcSlotId: 5;            /* Դ�߼���λ�� */
                    PF_UCHAR usSrcOSSGIndex: 7;           /*Ŀ��Vcpu���߼�����id */
                    PF_UCHAR ucSrcSGReserve: 1;
        #else
                    PF_UCHAR ucSrcSlotId: 5;            /* Դ�߼���λ�� */
                    PF_UCHAR ucSrcCpuId: 3;            /* ԴCPU ID */
                    PF_UCHAR ucSrcSGReserve: 1;
                    PF_UCHAR usSrcOSSGIndex: 7;           /*Ŀ��Vcpu���߼�����id */
        #endif
        }s;
    }SrcNode;

    PF_ULONG ulHashGene;

    union
    {
        PF_USHORT usCompEntityInfo;
        struct
        {
        #if(FWD_LITTLE_ENDIAN == FWD_YES)
            PF_UCHAR ucDstCompEntityResv: 2;   /*Ŀ��SG��ͬ�������ʵ�������ֶ�*/
            PF_UCHAR ucDstCompEntityID: 6;   /*Ŀ��SG��ͬ�������ʵ����*/
            PF_UCHAR ucSrcCompEntityResv: 2;   /*ԴSG��ͬ�������ʵ�������ֶ�*/
            PF_UCHAR ucSrcCompEntityID: 6;   /*ԴSG��ͬ�������ʵ����*/
        #else
            PF_UCHAR ucDstCompEntityID: 6;   /*Ŀ��SG��ͬ�������ʵ����*/
            PF_UCHAR ucDstCompEntityResv: 2;   /*Ŀ��SG��ͬ�������ʵ�������ֶ�*/
            PF_UCHAR ucSrcCompEntityID: 6;   /*ԴSG��ͬ�������ʵ����*/
            PF_UCHAR ucSrcCompEntityResv:2;   /*ԴSG��ͬ�������ʵ�������ֶ�*/
        #endif
        }s;
    }CompEntity;

#if (FWD_LITTLE_ENDIAN == FWD_YES)
    PF_UCHAR ucRes1: 5;
    PF_UCHAR ucSendCopy: 2;
    PF_UCHAR ucMultiCast: 1;
#else
    PF_UCHAR ucMultiCast: 1;
    PF_UCHAR ucSendCopy: 2;
    PF_UCHAR ucRes1: 5;
#endif

    PF_UCHAR  ucRes[1];

}FWD_COMCHANNEL_S;
/* END: modified by wangtao at 2012/5/2 for SPU2.0 FCM */

#define FWD_COMMCHANNEL_SIZE    sizeof(FWD_COMCHANNEL_S)

#define URTD_SET_MSGCODE(pMBuf, MsgCode) \
(((FWD_COMCHANNEL_S*)((PMBUF_MTOD((pMBuf), CHAR*)) - FWD_COMMCHANNEL_SIZE))->ucMsgCode) = (MsgCode)

#define URTD_GET_MSGCODE(pMBuf) \
((FWD_COMCHANNEL_S*)((PMBUF_MTOD((pMBuf), CHAR*)) - FWD_COMMCHANNEL_SIZE))->ucMsgCode

/* IMSI ��MSISDN ����*/
#define M_SC_MSISDN_LEN  8

#ifndef __NEW_COMPILER_MSISDN__
#define __NEW_COMPILER_MSISDN__
typedef VOS_UINT8 MSISDN[ M_SC_MSISDN_LEN ]; /* MSISDN */
#endif


typedef VOID (*IPC_RPC_RECEIVE_NOTIFY)
(
        ULONG ulSrcNode,                /* Դ�ڵ�ID          */
        ULONG ulSrcModuleID,            /* Դģ��ID          */
        VOID *pReceiveData,             /* ���յ�����        */
        ULONG ulReceiveDataLen,         /* �������ݵĳ���    */
        VOID **ppSendData,              /* ���͵�����        */
        ULONG *pulSendDataLen           /* �������ݵĳ���    */
);






/* add by w00316385 end */


#define DHCPC_INNER_EVENT   1
#define DHCPC_LAP_MSG_EV    (1<<2)
#define DHCPC_V4_SVR_EV     (1<<3)
#define DHCPC_V6_SVR_EV     (1<<4)

/*DHCP���ƿ��ϣ���С*/
#if defined(__LINUX_VM__) || defined(__WIN32_PLATFORM__)
#define DHCPC_CTRLBLK_HASH_TABLE_SIZE 60
#else
#define DHCPC_CTRLBLK_HASH_TABLE_SIZE 65535
#endif

/* #define     FSU_TID_DHCP      0xfd000035 */  /* Deleted by tangbenying at 2008-02-01 V9R7 for V9R7C1 Memory Optimize */
#define     MS_OPERATION_ADD    0
/* #define MID_DHCPC        0x085f0000     /* DHCP Client*/   /* Deleted by tangbenying at 2008-02-01 V9R7 for V9R7C1 Memory Optimize */

#define DHCPC_IPOK                      0            /*IP����ɹ�*/
#define DHCPC_IPFAIL                    1            /*IP����ʧ��*/

#define DHCPC_FIRSTSEND                 0            /* ��һ�η��ͣ����ط� */
#define DHCPC_ALREADYRESEND             1            /* �Ѿ��ط� */
#define DHCPC_SNDSRVSEND                2            /* ���������ط�һ�� */

#define DHCPC_CTRLBLK_IDLE              0            /*���б�־*/
#define DHCPC_CTRLBLK_OCCUPIED          1            /*ռ�ñ�־*/

#define DHCPC_INVALID_UDPSNO        -1            /*��Ч��UDPS�����*/

#define DHCPC_TMPCTRLBLK_IDSTR         "DhcpBlk"        /*DHCP���ƿ��ʶ��*/
#define DHCPC_RENEW_TIMER_LENGTH     1000    /*��ַ���ö�ʱ��ʱ��1s*/
#define DHCPC_SPU_GP_EVENTBIT         0x1
#define DHCPC_SERVER_EVENTBIT        0x2

#define DHCPC_SRV_TIMER_LENGTH      (60*1000*10)   /* ���÷�����û10����̽��һ�� */

#ifdef __WIN32_PLATFORM__
#define DHCPS_DBG_ENVENTBIT            0x9
#define inline
#endif

#define DHCPC_MAXMSGS_PEREVENT        50
#define DHCPC_DEFAULT_MAX_APP_MSG_NUM   4096

#define DHCPC_4_SECONDS        4
#define DHCPC_8_SECONDS        8

#define DHCPC_RENEW_NUM            80
#if defined(__LINUX_VM__) || defined(__WIN32_PLATFORM__)
#define DHCPC_MAX_CTRLBLKNUM        4        /*DHCP��ʱ���ƿ���*/
#else
#define DHCPC_MAX_CTRLBLKNUM        1300        /*DHCP��ʱ���ƿ���*/
#endif

#define DHCPC_DFTCB_TIMER_INTERVAL    (1000*60*5)   /*5���Ӷ�ʱ����dft�ϱ���*/
#define DHCPC_CTRL_BLOCK_AGING_TIMER_INTERVAL    (1000*60*60*4)   /*4Сʱ��ʱ������ַ�ϻ���*/
#define DHCPC_RETRANS_TIMER_LENGTH    100            /*DHCP�ط���ʱ��ʱ��0.1s*/
#define DHCPC_RETRANS_STEPS_PERSEC    (1000/DHCPC_RETRANS_TIMER_LENGTH)            /*ÿ���ӵĿ̶���*/
#define DHCPC_TMR_CIRCLE_TIME            (8 * DHCPC_RETRANS_STEPS_PERSEC)          /*�ܹ��Ŀ̶���*/
#define DHCPC_FREE_SCAN_TIMER_LENGTH  (1000*60*60)

/* DS.UGWV9R10C0.DHCPv6.DHCP.0024֧��TIDʹ�������ά��--��Сʱ�ϻ�һ�� */
#ifdef __WIN32_PLATFORM__
#define DHCPC_AGEING_SEQNUM_TIMER_LENGTH  (1000*6)
#else
#define DHCPC_AGEING_SEQNUM_TIMER_LENGTH  (1000*60*30)
#endif
#define DHCPC_AGEING_SEQNUM_MAX_CNT  2 /* ����ϻ����� */

#define DHCPC_INVALID_INDEX            0xffffffff    /*��Ч�Ķ�ʱ����������ֵ*/
#define DHCPC_HEADNODE_TYPE            0xffffffff    /*��ʱ������ͷ����־*/


#define DHCPC_PKT_PORTNO                68            /*DHCP�ͻ��˶˿ں�*/
#define DHCPS_PKT_PORTNO                67            /*DHCP�������˿ں�*/

#define DHCPC_MAX_LEASE_TIME            (8*24)        /*���IP��Чʱ��(hour);������ذ嶨��һ��*/

#define DHCPC_PKT_FIXEDFIELD_LEN        ( (ULONG)sizeof(DHCP_S) )     /*=236bytes*/

#define DHCPC_PKT_LEN                    300            /*ȥIP/UDPͷ*/

#define DHCP_OP_REQUEST                1
#define DHCP_OP_REPLY                    2

#define DHCP_ETHERNETHARDWARETYPE    1
#define DHCP_ETHERNETHARDWARELEN        6

/* BEGIN: Added by jixiaoming at 2011-11-28 for CR20110907018 */
#define DHCP_PKT_ASSUME_MAX_LEN (3*1024)  /* �ٶ�DHCP���ĵ���󳤶�Ϊ3k,������ֵ��Ϊ�����쳣.һ�㱨��Ϊ0.5k���� */
/* END: Added by jixiaoming at 2011-11-28 for CR20110907018 */

/*DHCP������"options"�ֶε�CODE��  */
#define DHCP_SUBNETMASK_CODE            0x01 /*DHCP����"options"�ֶκ���"Subnet mask"ѡ��ı�ʶ��*/
#define DHCP_ROUTERIP_CODE            0x03 /*DHCP����"options"�ֶκ���"Routet "ѡ��ı�ʶ��*/
#define DHCP_DNSIP_CODE                0x06 /*DHCP����"options"�ֶκ���"DNS server "ѡ��ı�ʶ��*/
#define DHCP_HOSTNAME_CODE            0x0c /*DHCP����"options"�ֶκ���"Host name"ѡ��ı�ʶ��*/
#define DHCP_DOMAINNAME_CODE            0x0f /*DHCP����"options"�ֶκ���"Domain name"ѡ��ı�ʶ��*/
/*Ϊ����5201��CM,IDT,PC���豸����Ҫ��ѡ�� δ����Щѡ��  */
#define DHCP_VENDORINFO_CODE            0x29  /*DHCP����"options"�ֶκ���"Vendor specific information"ѡ��ı�ʶ��*/
#define DHCP_NBNS_CODE                0x2c /*DHCP����"options"�ֶκ���"Netbios name server"ѡ��ı�ʶ��*/
#define DHCP_NBDS_CODE                0x2d /*DHCP����"options"�ֶκ���"Netbios data distribute server"ѡ��ı�ʶ��*/
#define DHCP_NBNT_CODE                    0x2e /*DHCP����"options"�ֶκ���"Netbios node type"ѡ��ı�ʶ��*/
#define DHCP_NBSCOPE_CODE                0x2f /*DHCP����"options"�ֶκ���"Netbios scope"ѡ��ı�ʶ��*/
#define DHCP_REQUESTEDIP_CODE            0x32  /*DHCP����"options"�ֶκ���"Requested Ip"ѡ��ı�ʶ��*/
#define DHCP_IPLEASETIME_CODE            0x33  /*DHCP����"options"�ֶκ���"Dhcp Ip address lease time"ѡ��ı�ʶ��*/
#define DHCP_MESSAGETYPE_CODE        0x35  /*DHCP����"options"�ֶκ���"Dhcp Message Type"ѡ��ı�ʶ��*/
#define DHCP_SERVERIP_CODE                0x36  /*DHCP����"options"�ֶκ���"Dhcp Server Ip"ѡ��ı�ʶ��*/
#define DHCP_REQPARAM_CODE            0x37  /*DHCP����"options"�ֶκ���"Requested parameter list"ѡ��ı�ʶ��*/
#define DHCP_RENEWTIME_CODE            0x3a  /*DHCP����"options"�ֶκ���"Renew time"ѡ��ı�ʶ��*/
#define DHCP_REBINDTIME_CODE            0x3b  /*DHCP����"options"�ֶκ���"Rebind time"ѡ��ı�ʶ��*/
#define DHCP_CLIENTID_CODE                0x3d  /*DHCP����"options"�ֶκ���"Dhcp client Id"ѡ��ı�ʶ��*/
#define DHCP_TFTPSERVER_CODE            66
#define DHCP_BOOTFILE_CODE            67
#define DHCP_OPTION60                    60      /*�����Զ�������*/
#define DHCP_OPT82_CODE                82      /*DHCP����"options"�ֶκ���"OPTION 82"ѡ��ı�ʶ��*/
#define DHCP_OPT82_CIRCUITID            1
#define DHCP_OPT82_REMOTEID            2

#define DHCP_OPTION_COUNT                20
#define DCHP_MAGICCOOKIE                0x63825363
#define DHCP_ENDOFOPTIONS                0xff

/*DHCPC Error Codes:*/
#define DHCPC_MODID_ERR                1
#define DHCPC_MEM_ERR                    2
#define DHCPC_QUEWRITE_ERR                3
#define DHCPC_USER_NOT_EXIST            4

#define DHCP_MAX_MSISDN_LEN 8
#define DHCP_MAX_MSISDN_STRING_LEN GTPC_IMSI_MSISDN_LENGTH

/*DHCPC Debug Levels*/
#define DHCPC_DBG_L0    1        /*���̹ؼ���*/
#define DHCPC_DBG_L1    2        /*�쳣��*/
#define DHCPC_DBG_L2    3        /*������Ϣ*/

#define DHCPC_DEBUGBUF_LEN                (1024 + 2)


#define DHCPC_RUN_TIME_MILLSECS     100
#define DHCPC_TASK_DELAY_MILLSECS   10

/* BEGIN: Added by jixiaoming at 2011-09-27 for  CR20101222007 */

#define DHCP_VPN_INSTANCE_NAME_MAX_LENGTH  32              /*VPN���ֳ���*/
#define DHCP_NO_ALARM                      0               /* DHCP û�з�����·�ϸ澯 */
#define DHCP_ALARMED                       1               /* DHCP �Ѿ�������·�ϸ澯 */
/* END: Added by jixiaoming at 2011-09-27 for  CR20101222007 */

#define DHCPC_BLOCK_USED 1
#ifdef __WIN32_PLATFORM__
#define DHCP_BLOCK_MAX_SACNNUM 3
#else
#define DHCP_BLOCK_MAX_SACNNUM 10
#endif

/* �뼶ʱ��۵Ķ�ʱ���� */
#define DHCPC_SECOND_TIMER_INTERVAL 200
#define DHCPC_SECONDS_PER_HOUR 3600
#define DHCPC_MILLSECONDS_PER_SECOND 1000
#define DHCPC_SECONDS_PER_MINUTE 60
#define DHCPC_DAYS_PER_MONTH 31
#define DHCPC_HOURS_PER_DAY 24
/* �뼶ʱ��ۣ����ǵ��������⣬200���봦��һ������3600��/Сʱ*200����/ÿ��=18000 */
#define DHCPC_SECOND_TIMER_LEN (DHCPC_SECONDS_PER_HOUR*DHCPC_MILLSECONDS_PER_SECOND/DHCPC_SECOND_TIMER_INTERVAL)
/* Сʱʱ��۵Ķ�ʱ���� */
#define DHCPC_HOUR_TIMER_INTERVAL (DHCPC_SECONDS_PER_MINUTE*DHCPC_MILLSECONDS_PER_SECOND)
/* Сʱʱ��ۣ���31��*24Сʱ/��=744����λ */
#define DHCPC_HOUR_TIMER_LEN (DHCPC_DAYS_PER_MONTH*DHCPC_HOURS_PER_DAY)

#define DHCPC_FIND_SAME_NODE_MAX_CNT 5

/* ��ʱ���������� */
typedef enum enDHCP_LIST_TYPE
{
    DHCPC_LIST_TYPE_SECOND,
    DHCPC_LIST_TYPE_HOUR,
    DHCPC_LIST_TYPE_MAX,
} DHCP_LIST_TYPE_EN;

extern ULONG g_ulDHCPCTimerListNodeNum[DHCPC_LIST_TYPE_MAX];

/* ����ʱ������ȡ�뼶���Ĳ���λ�� */
#define DHCPC_GET_SECOND_INSPOS(ulTimerInterval) ((DHCPC_getCurTimerSecondPos() + (ulTimerInterval)) % DHCPC_SECOND_TIMER_LEN)
/* ����ʱ������ȡСʱ���Ĳ���λ�� */
#define DHCPC_GET_HOUR_INSPOS(ulTimerInterval) ((DHCPC_getCurTimerHourPos() + (ulTimerInterval)) % DHCPC_HOUR_TIMER_LEN)

#define DHCPC_GET_HASHKEY(ulHashElement) (((ulHashElement) % DHCPC_CTRLBLK_HASH_TABLE_SIZE + (ulHashElement) / DHCPC_CTRLBLK_HASH_TABLE_SIZE) % DHCPC_CTRLBLK_HASH_TABLE_SIZE)

/* ��ʱ���ص������� */
typedef ULONG (* DHCPC_TIMER_CALLBACK)(UCHAR ucIpType, ULONG ulTeidc, UCHAR ucEvent);

typedef struct tagDHCPC_TIMER_NODE_S
{
    struct tagDHCPC_TIMER_NODE_S *pstPrevNode;     /* ʱ�����ϵ���һ���ڵ� */
    struct tagDHCPC_TIMER_NODE_S *pstNextNode;     /* ʱ�����ϵ���һ���ڵ� */
    struct tagDHCPC_TIMER_NODE_S *pstHashNextNode; /* ��ϣ���ϵ���һ���ڵ� */
    DHCPC_TIMER_CALLBACK pCallBackFun;
    ULONG  ulCircleNum;   /* ��Լ��������0��ʾ����һ���� */
    ULONG  ulTeidc;
    USHORT usSecondField; /* �뼶ʱ���Ӧ�ùҵ�λ�� */
    UCHAR  ucIpType;
    UCHAR  ucEvent;
    UCHAR  ucListType;   /* ��������: 0-�뼶����1-Сʱ���� */
    UCHAR  aucReserve[3];
} DHCPC_TIMER_NODE_S;

typedef struct tagDHCPC_TIMER_LIST_HEAD_S
{
    DHCPC_TIMER_NODE_S *pstNextNode;
} DHCPC_TIMER_LIST_HEAD_S;

extern DHCPC_TIMER_LIST_HEAD_S *g_pstDHCPTimerHashList;

/* �뼶��ʱ��id */
extern RELTMR_T g_ulDHCPCSecondTimerId;
/* Сʱ��ʱ��id */
extern RELTMR_T g_ulDHCPCHourTimerId;

typedef enum
{
    DHCPC_INNER_MSGCODE_CHECK_PDP = 1,
    DHCPC_INNER_MSGCODE_CHECK_CNTRL_BLCK,
    DHCPC_INNER_MSGCODE_TIM_RESTORE,
    DHCPC_INNER_MSGCODE_BOARD_STATE_CHANGE,
} ;


typedef struct tagDHCPC_INNER_MSG_S
{
    ULONG ulMsgCode;
    ULONG ulPdpIndex;
    ULONG ulCtlBlockHashValue;
    ULONG ulReserve34566;
} DHCPC_INNER_MSG_S;


/*===================MACROS====================================*/
#define DHCP_LENGTHTO300(pulMagicCookie,pucDhcpOption) \
{\
    ULONG i;\
\
    i=(ULONG)((UCHAR *)pucDhcpOption-(UCHAR *)pulMagicCookie);\
    if(i>(DHCPC_PKT_LEN -sizeof(DHCP_S))) VOS_Assert(0);\
    for ( ; i <= (DHCPC_PKT_LEN -sizeof(DHCP_S)) ; i++ )\
    {\
        *(pucDhcpOption++) = 0;\
    }\
}

#define DHCPC_INIT_ITEM(pItem)  \
{\
    VOS_StrCpy(((CHAR *)(pItem)->ucCtrlBlkFlgStr), DHCPC_TMPCTRLBLK_IDSTR/*,VOS_StrLen(DHCPC_TMPCTRLBLK_IDSTR) for code review*/); \
    (pItem)->ulPdpIndex = NULL;      \
    (pItem)->ulModId = NULL;        \
    (pItem)->usDhcpStatus = NULL;     \
    (pItem)->ulSrvIp = NULL;     \
    (pItem)->ulUserIpAddr = NULL;    \
    (pItem)->usLease = 0;    \
    (pItem)->ulTimeStamp = NULL;    \
    (pItem)->ulXid = NULL;    \
    (pItem)->usAlreadySendFlg = DHCPC_FIRSTSEND;    \
}

#define DHCPC_INIT_CTRLBLK(pItem)  \
{\
    (pItem)->ulDHCPCtxIdx = 0;      \
    (pItem)->aulMSISDN[0] = 0;\
    (pItem)->aulMSISDN[1] = 0;\
    (pItem)->ulPDPIndex = 0;    \
    (pItem)->usDhcpStatus = 0;        \
    (pItem)->usLease = 0;     \
    (pItem)->ulTimeStamp = 0;     \
    (pItem)->ulSrvIp = 0;    \
    (pItem)->ulUserIpAddr = 0;    \
    (pItem)->ulTimeStamp = 0;    \
    (pItem)->ulTmpVar = 0;    \
}

#define DHCPC_BACKUPMSG2ITEM(pMsg, pItem) \
{\
    (pItem)->ulDHCPCtxIdx = (pMsg)->ulDHCPCtxIdx;      \
    (pItem)->ulPDPIndex = (pMsg)->ulPDPIndex;    \
    (pItem)->usDhcpStatus = (pMsg)->usDhcpStatus;        \
    (pItem)->usLease = (pMsg)->usLease;     \
    (pItem)->ulTimeStamp = (pMsg)->ulTimeStamp;     \
    (pItem)->ulSrvIp = (pMsg)->ulSrvIp;    \
    (pItem)->ulUserIpAddr = (pMsg)->ulUserIpAddr;    \
    (pItem)->ulTimeStamp = (pMsg)->ulTimeStamp;    \
    (pItem)->ulTmpVar = (pMsg)->ulTmpVar0;    \
}


#define DHCPC_MSG2ITEM(pMsg, pItem) \
{\
    (pItem)->ulPdpIndex      = (pMsg)->ulIndex ;     \
    (pItem)->ucSCID = (pMsg)->ucSCID;\
    (pItem)->usDhcpGroupIndex   = (pMsg)->usDhcpGroupIndex;   \
}


#define DHCPC_RELEASEMSG2ITEM(pMsg, pItem) \
{\
    (pItem)->ulPdpIndex    = (pMsg)->ulIndex ;     \
    (pItem)->ucSCID = (pMsg)->ucSCID; \
    (pItem)->ulUserIpAddr = (pMsg)->aulPdpAddr[0]; \
    (pItem)->aulMSISDN[0] = (pMsg)->aulMSISDN[0]; \
    (pItem)->aulMSISDN[1] = (pMsg)->aulMSISDN[1]; \
    (pItem)->usDhcpGroupIndex = (pMsg)->usDhcpGroupIndex; \
}


#define DHCPC_ITEM2MSG(pItem, pMsg) \
{\
    VOS_MemCpy(((pMsg)->szMac), ((pItem)->szMac) , 6);\
    (pMsg)->usCid   =   (pItem)->usCid ;        \
    (pMsg)->ulAddr  =   (pItem)->ulIPAddr;      \
    (pMsg)->ulMask  =   (pItem)->ulMask;        \
    (pMsg)->ulLeaseTime     =   (pItem)->ulLeaseTime;       \
    (pMsg)->ulGatewayAddr   =   (pItem)->ulGatewayAddr;     \
    (pMsg)->ulPriDnsAddr    =   (pItem)->ulPriDnsAddr;      \
    (pMsg)->ulSecDnsAddr    =   (pItem)->ulSecDnsAddr;      \
    (pMsg)->ulPriNbnsAddr   =   (pItem)->ulPriNbnsAddr;     \
    (pMsg)->ulSecNbnsAddr   =   (pItem)->ulSecNbnsAddr;     \
    (pMsg)->ulDhcpSvrAddr   =   (pItem)->ulDhcpSvrAddr;     \
}

#define DHCPC_ITEM_SETSATE(pItem, State)        \
{\
       (pItem)->usDhcpStatus/*ucState*/     = (State) ;           \
}

/*��GGSN��MAC��ַ���Բ��
 *����μ�RFC2131 page 23
 */
#define DHCP_FILLFIXEDFIELD(ucOpp,pstSendDhcp,ulXiid,usSecss,usFlagg,ulUserIpAddr,ulGiaddrr,ulCiaddrr,szChaddrr) \
{\
    ULONG ii; \
    \
    pstSendDhcp->ucOp     = ucOpp;\
    pstSendDhcp->ucHtype  = DHCP_ETHERNETHARDWARETYPE;\
    pstSendDhcp->ucHlen   = DHCP_ETHERNETHARDWARELEN;\
    pstSendDhcp->ucHops   = 0;\
    pstSendDhcp->ulXid    = VOS_HTONL(ulXiid);\
    pstSendDhcp->usSecs   = VOS_HTONS(usSecss);\
    pstSendDhcp->usFlag   = VOS_HTONS(usFlagg);\
    pstSendDhcp->ulYiaddr = ulUserIpAddr; \
    pstSendDhcp->ulGiaddr = ulGiaddrr;\
    pstSendDhcp->ulCiaddr = ulCiaddrr;\
    for(ii = 0; ii < DHCP_ETHERNETHARDWARELEN; ii++)\
    {\
        pstSendDhcp->szChaddr[ii] = szChaddrr[ii];\
    }\
}

#define DHCP_FILLMAGICCODE(pulMagicCookie) \
{\
    *pulMagicCookie = VOS_HTONL(DCHP_MAGICCOOKIE);\
}

#define DHCP_FILLMESSAGETYPEOPTION(pucDhcpOption,ucValue) \
{\
    *pucDhcpOption++ = DHCP_MESSAGETYPE_CODE;\
    *pucDhcpOption++ = 1;\
    *pucDhcpOption++ = ucValue;\
}

#define DHCP_FILLIPOPTION(pucDhcpOption,ulOptionId,ulValue) \
{\
    ULONG *pulRequestedIp = NULL;\
\
    *pucDhcpOption++ = ulOptionId;\
    *pucDhcpOption++ = 4;\
    pulRequestedIp   = (ULONG *)pucDhcpOption;\
    *pulRequestedIp  = (ULONG)ulValue;\
    pucDhcpOption    = (UCHAR *)(pulRequestedIp + 1);\
}

#define DHCP_FILLULONGOPTION(pucDhcpOption,ulOptionId,ulValue) \
{\
    ULONG *pulValue = NULL;\
\
    *pucDhcpOption++ = ulOptionId;\
    *pucDhcpOption++ = 4;\
    pulValue   = (ULONG *)pucDhcpOption;\
    *pulValue  = VOS_HTONL((ULONG)ulValue);\
    pucDhcpOption    = (UCHAR *)(pulValue + 1);\
}

#define DHCP_FILLENDOPTION(pucDhcpOption) \
{\
   *pucDhcpOption++   = DHCP_ENDOFOPTIONS;\
}
#define DHCP_FILLPARALISTOPTION(pucDhcpOption)\
{\
    *pucDhcpOption++ = DHCP_REQPARAM_CODE;\
    *pucDhcpOption++ = 0x02;\
    *pucDhcpOption++ = DHCP_SUBNETMASK_CODE;\
    *pucDhcpOption++ = DHCP_DNSIP_CODE;\
}
/* Added start by niutao 60002996 at 2006-08-25 V800R002C05B010 for KPN Project*/
#define DHCP_SLOT_ONE    1
#define DHCP_SLOT_THREE    3
#define DHCP_SLOT_FIVE    5
#define DHCP_SLOT_SEVEN    7

enum DHCPC_AGING_STATUS_FLAG
{
    DHCPC_NOT_AGING = 0,
    DHCPC_CHECKING_WITH_PDP,
    DHCPC_AGING,
    DHCPC_AGING_MAX,
};

/* BEGIN: Added by jixiaoming at 2011-09-27 for  CR20101222007 */
#define DHCPC_GROUP_BITSIZE 16
/* END: Added by jixiaoming at 2011-09-27 for  CR20101222007 */
extern ULONG DHCPC_StartTimer(UCHAR ucIpType, ULONG ulTeidc, UCHAR ucEvent, ULONG ulTimerInterval, DHCPC_TIMER_CALLBACK pCallBackFun);

#endif /* #ifndef _DHCP_DEF_H_ */
