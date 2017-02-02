
#ifndef _MM_GLOBAL_H_
#define _MM_GLOBAL_H_


#include "NasMmlCtx.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif                                                                          /* __cpluscplus                             */
#endif                                                                          /* __cpluscplus                             */

#pragma pack(4)

/******************************************************************************/
/****************************  MMȫ�ֿ�����Ϣ *********************************/
/******************************************************************************/

/*****************************************************************************
 ö����    : NAS_MM_CONN_CTRL_ENUM
 �ṹ˵��  : MM Connection����
*****************************************************************************/
enum NAS_MM_CONN_CTRL_ENUM
{
    MM_CONN_CTRL_CC                     = 0 ,
    MM_CONN_CTRL_SMS,
    MM_CONN_CTRL_SS,
    MM_CONN_CTRL_BUTT
};
typedef VOS_UINT8   NAS_MM_CONN_CTRL_ENUM_UINT8;

/*****************************************************************************
 �ṹ��      : NAS_MM_PROC_TYPE_ENUM
 �ṹ˵��    : MM ��������
*****************************************************************************/
enum NAS_MM_PROC_TYPE_ENUM
{
    MM_NULL_PROC                        = 0,
    MM_LU_PROC                          = 1,
    MM_GMM_ATTACH_PROC                  = 2,
    MM_GMM_RAU_PROC                     = 3,
    MM_COMB_ATTACH_PROC                 = 4,
    MM_COMB_RAU_PROC                    = 5,
    MM_GMM_SR_PROC                      = 6,
    MM_NET_DETACH_PROC                  = 7,
    MM_AUTH_FAIL_PROC                   = 8,
    MM_MM_CONN_PROC                     = 9,
    MM_MM_NET_ABORT                     = 10,
    MM_IMSI_DETACH                      = 11,
    MM_MM_MS_AUTH_FAIL_PROC             = 12,
    NAS_MM_PROC_TYPE_BUTT
};
typedef VOS_UINT8   NAS_MM_PROC_TYPE_ENUM_UINT8;


enum NAS_MM_T3212_START_SCENE_ENUM
{
    NAS_MM_T3212_START_SCENE_NORMAL_START                                 = 0,  /* ����������T3212���� */
    NAS_MM_T3212_START_SCENE_LAU_RRC_EST_REL_BY_AS                        = 1,  /* ��LAU����ʱ��REL����T3212���� */
    NAS_MM_T3212_START_SCENE_LAU_RRC_EST_CONN_FAIL                        = 2,  /* ��LAU����ʱʧ��ʱ������T3212���� */
    NAS_MM_T3212_START_SCENE_LAU_RRC_EST_FAIL_CELL_BAR                    = 3,  /* ��LAU����ʱ��BARʧ��ʱ������T3212���� */

    NAS_MM_T3212_START_SCENE_BUTT
};
typedef VOS_UINT32 NAS_MM_T3212_START_SCENE_ENUM_UINT32;



enum NAS_MM_T3212_LEN_TYPE_ENUM
{
    NAS_MM_T3212_LEN_TYPE_NETWORK_ALLOC_LEN             = 0,
    NAS_MM_T3212_LEN_TYPE_NETWORK_ALLOC_RANDOM_LEN      = 1,
    NAS_MM_T3212_LEN_TYPE_NV_DEFINED                    = 2,
    NAS_MM_T3212_LEN_TYPE_BUTT
};
typedef VOS_UINT8 NAS_MM_T3212_LEN_TYPE_ENUM_UINT8;
/*****************************************************************************
 �ṹ��      : NAS_MM_LINK_CTRL_STRU
 �ṹ˵��    : MM �������ӹ���
*****************************************************************************/
typedef struct
{
    NAS_MM_PROC_TYPE_ENUM_UINT8         ucCurrentProc;                          /* ��ǰ���� */
    VOS_UINT8                           ucExistedRrcConn;                       /* �����Ƿ������Ѵ��ڵ�RRC������ */
    VOS_UINT8                           ucSmcOrFirstNasMsgRcvdFlg;              /* �Ƿ�������յ�Security Mode Command����NAS����Ϣ */
    VOS_UINT8                           ucReserve;
}NAS_MM_LINK_CTRL_STRU;


#ifndef _PLMN_ID_
#define _PLMN_ID_
typedef struct
{
    VOS_UINT32                               ulMcc;                             /* MCC,3 bytes                              */
    VOS_UINT32                               ulMnc;                             /* MNC,2 or 3 bytes                         */
}MM_PLMN_ID_STRU;
#endif

#ifndef _LAI_
#define _LAI_
typedef struct
{
    MM_PLMN_ID_STRU                          PlmnId;
    VOS_UINT32                               ulLac;                             /* BIT STRING(SIZE(16))                     */
}MM_LAI_STRU;
#endif

/* CS��İ�ȫ��Ϣ */


typedef struct
{
#define     MM_CIPHER_NOSTART           0
#define     MM_CIPHER_START             1

    VOS_UINT8                   ucSecurityType;                                 /* ȡֵͬ RRMM_SECURITY_IND_STRU ulRptMode  */
}MM_CS_SECURITY_INFO_STRU;


/* MS CS�����Ϣ */
typedef struct
{
    VOS_UINT8                               ucLength;                           /* ��digitΪ��λ,һ���ֽڴ��2��digit       */
    VOS_UINT8                               aucImsi[8];                         /* IMSI����BCD����,���Ȳ�����15λ,����
                                                                                 * aucImsi[0]����λ��ŵ���IMSI��digit 1,
                                                                                 * aucImsi[0]����λȫΪ1,���洢��Ϣ,
                                                                                 * aucImsi[1]����λ��ŵ���IMSI��digit 3,
                                                                                 * aucImsi[1]����λ��ŵ���IMSI��digit 2,
                                                                                 * �Դ�����                                 */
}MM_IMSI_STRU;

typedef struct {
#define     MM_MS_ID_ABSENT             0x00
#define     MM_MS_ID_IMSI_PRESENT       0x01
#define     MM_MS_ID_IMEI_PRESENT       0x02

#define     MM_MS_ID_IMEISV_PRESENT     0x04
#define     MM_MS_ID_TMSI_PRESENT       0x08

    VOS_UINT8                           ucMsIdFlg;                              /* MsId���ڱ�ʶ                             */
    MM_IMSI_STRU                        Imsi;
    VOS_UINT8                           aucImei[8];                             /* IMEI ����BCD����,����15λ,����ͬIMSI     */
    VOS_UINT8                           aucImeisv[9];                           /* IMEISV ����BCD����,����16λ,����ͬIMSI   */
    VOS_UINT8                           aucTmsi[4];                             /* BIT STRING(SIZE(32))                     */
}MM_MOBILE_ID_STRU;

typedef struct
{

    #define     MM_NO_FORBIDDEN                         MMCMM_NO_FORBIDDEN
    #define     MM_FORBIDDEN_PLMN                       MMCMM_FORBIDDEN_PLMN
    #define     MM_FORBIDDEN_PLMN_FOR_GPRS              MMCMM_FORBIDDEN_PLMN_FOR_GPRS
    #define     MM_FORBIDDEN_LA_FOR_ROAM                MMCMM_FORBIDDEN_LA_FOR_ROAM
    #define     MM_FORBIDDEN_LA_FOR_REG_PRVS_SVS        MMCMM_FORBIDDEN_LA_FOR_REG_PRVS_SVS
    VOS_UINT32                          ulCurFobidnFlg;                         /* ��ǰPLMN�Ľ�ֹ��Ϣ                       */

    /* ɾ���¾�LAI��Ϣ,�ɵ�LAI�ŵ�MML�б��� */

    VOS_UINT8                           ucCsDrxLen;                             /* CS���DRX lengthϵ�� */
    MM_MOBILE_ID_STRU                   MobileId;                               /* MOBILE ID  */
    MM_PLMN_ID_STRU                     stPlmnId;                               /* ��ӦTMSI��PLMN ID */
    VOS_UINT32                          ulCellId;
    VOS_UINT8                           ucCellChgFlg;

    VOS_UINT8                           ucOldRac;                               /* ���һ��ע��ɹ���RAC */

    MM_LAI_STRU                         stAttemptToUpdateLai;                   /* ���ע�ᱻ����ATTEMPT TO UPDATE״̬�����¼��LAI��Ϣ���ڷ���LAUʱ��������ñ�� */
}MM_MS_CS_INFO_STRU;

#define     MM_AUTHEN_RAND_REPEAT           0
#define     MM_AUTHEN_RAND_DIFFER           1

/* Authentication ���ֿ��Ʋ��� */
typedef struct
{
#define     MM_AUTHEN_SUPPORT_UMTS_ALGO     0
#define     MM_AUTHEN_NOSUPPORT_UMTS_ALGO   1
    VOS_UINT8                               ucSptUmtsAuthAlgo;                  /* ֧��UMTS ��Ȩ�㷨�ı�ʶ                  */

#define     MM_AUTHEN_COUNTER_MAX_CNT       3                                   /* Authentication attempt counter������   */
    VOS_UINT8                               ucAuthenAttmptCnt;                  /* Authentication attempt counter           */

#define     MM_AUTHEN_NO_CAUSE              0
#define     MM_MAC_CODE_FAIL                1
#define     MM_SQN_FAIL                     2
    VOS_UINT8                               ucLastFailCause;                    /* �ϴ�Authenticationʧ�ܵ�ԭ��             */
    VOS_UINT8                               ucFailParaLength;                   /* Failure Parameter�ĳ��ȣ���λΪ�ֽ�      */
    VOS_UINT8                               aucFailPara[14];                    /* Failure Parameter                        */

#define     MM_AUTHEN_RAND_PRESENT          0
#define     MM_AUTHEN_RAND_ABSENT           1
    VOS_UINT8                               ucRandFlg;                          /* ��RAND�Ƿ���Ч                           */

    VOS_UINT8                               ucRandRepeat;                       /* �� RAND �Ƿ����ϴ���ͬ */
    VOS_UINT8                               ucSresFlg;                          /* SRES���ڱ�־,                             */

#define     MM_MAX_SIZE_RAND                16
    VOS_UINT8                               aucOldRand[MM_MAX_SIZE_RAND];       /* �ɵ�RAND                                 */
    VOS_UINT8                               aucCurRand[MM_MAX_SIZE_RAND];       /* ��ǰ��RAND                               */

#define     MM_AUTN_MAX_LENGTH              0x10
    VOS_UINT8                               ucAutnLen;
    VOS_UINT8                               aucAutn[MM_AUTN_MAX_LENGTH];

#define     MM_AUTHEN_RES_ABSENT            0
#define     MM_AUTHEN_RES_PRESENT           1
    VOS_UINT8                               ucResFlg;                           /* RES���ڱ�־,                             */
                                                                                /* 1:��ʧ���ڴ治Ϊ��,
                                                                                 * RAND��RESΪ��ʧ���ڴ��е�ֵ              *
                                                                                 * 0:��ʧ���ڴ�Ϊ��,RANDΪ��һ�ε�RAND��ֵ  */
    VOS_UINT8                               aucRes[4];                          /* RES                                      */
    VOS_UINT8                               ucExtRspLength;                     /* Extension Response�ĳ��ȣ���λΪ�ֽ�     */

#define     MM_MAX_RES_EXT_LEN              12
    VOS_UINT8                               aucExtRes[MM_MAX_RES_EXT_LEN];      /* Extension Response                       */

    VOS_UINT8                               ucLastAuthType;                     /* �ϴμ�Ȩ����                             */
    VOS_UINT8                               ucOpId;
}MM_AUTHEN_CTRL_STRU;


/* MM Connection  ���ֵ����ݽṹ */

typedef struct
{
    VOS_UINT32   ulTransactionId;                                               /* TI                                       */
    VOS_UINT32   ulCallType;                                                    /* ��������                                 */
    VOS_UINT32   ulCallPri ;                                                    /* �������ȼ�                               */
    VOS_UINT32   ulCallMode;                                                    /* ����ģʽ,speech��video�������� */
    VOS_UINT8    ucFlg;                                                         /* �Ƿ���Ҫ����������                       */
    VOS_UINT8    ucReserved[3];
}MM_RCV_XX_EST_REQ_STRU;

typedef struct
{
    MM_RCV_XX_EST_REQ_STRU  RcvXXEstReq;                                        /* ��¼�ڽ������ؽ�MM���ӵĹ�����           *
                                                                                 * CM��Ҫ�����ĵ�һ������MM���ӵ�������Ϣ */
    VOS_UINT8                   aucMMConnExtFlg[2];                             /* ��¼MM�����Ƿ���ڱ�־                   */
    VOS_UINT8                   aucMMConnReestFlg[2];                           /* ��CC�����ؽ�����ʱ��¼��Ҫ�ؽ���MM����   */

#define  NO_MM_CONN_ESTING                                  255                 /* û�����ڽ�����MM����,                    *
                                                                                 * �ú�Ҳ����ucMMConnEstingPD               */
    VOS_UINT8                   ucMMConnEstingTI;                               /* ���ڽ�����MM���ӵ�TI                     */

    VOS_UINT8                   ucEstingCallTypeFlg;                            /* ���ڽ�����MM�����Ƿ��ǽ�������           */
    VOS_UINT8                   ucRat;
}MM_CONN_CTRL_STRU;

enum LAU_TYPE_ENUM
{
    MM_IE_LUT_NORMAL_LU                   = 0,
    MM_IE_LUT_PERIODIC_UPDATING           = 1,
    MM_IE_LUT_IMSI_ATTACH                 = 2,
    MM_IE_LUT_TYPE_BUTT
};
typedef VOS_UINT8 LAU_TYPE_ENUM_UINT8;


typedef struct
{
    LAU_TYPE_ENUM_UINT8       ucLuType;                                         /* Location updating type                   */
    VOS_UINT8                 ucLuAttmptCnt;                                    /* LU attempt counter                       */
    VOS_UINT8                 ucRetryFlg;                                       /* �����µ�С���Ƿ����LU                   */
    VOS_UINT8                 ucEnterState;                                     /* �ͷ�RR����֮������״̬                 */
    VOS_UINT8                 ucT3212ExpiredFlg;                                /* ��¼T3212����ı�־                      */
    VOS_UINT8                 ucT3213AttmptCnt;                                 /* T3213��ʱ������                          */
    VOS_UINT8                 ucImmAccRejLuAttmptCnt;                           /* G������ָ�ɾܾ�����LU���Դ���*/

    VOS_UINT8                 ucCsfbMtLauFlg;                                   /* CSFB�յ�Ѱ��������MT FLG,�ں���LAUʱ��Я��MT��־ */

    VOS_UINT8                 ucPsRandomAccessFailCnt;                                /* W������Attach����RAU������ʧ�ܵĴ��� */
    VOS_UINT8                 ucReserved1;
    VOS_UINT8                 ucReserved2;
    VOS_UINT8                 ucReserved3;
}MM_LU_INFO_STRU;


/* MM ȫ���� */
#define  MM_RAU_ATTACH_COUNTER_MAX                      5                       /* RAU/ATTACH attempt counter������       */

enum MN_STATE_ENUM
{
    MM_STATE_NULL                                           = 0,
    MM_IDLE_NO_CELL_AVAILABLE                               = 1,
    MM_IDLE_PLMN_SEARCH                                     = 2,
    MM_IDLE_NORMAL_SERVICE                                  = 3,
    MM_IDLE_LIMITED_SERVICE                                 = 4,
    MM_IDLE_ATTEMPTING_TO_UPDATE                            = 5,
    MM_IDLE_LOCATION_UPDATE_NEEDED                          = 6,
    MM_IDLE_PLMN_SEARCH_NORMAL_SERVICE                      = 7,
    MM_IDLE_NO_IMSI                                         = 8,
    WAIT_FOR_OUTGOING_MM_CONNECTION                         = 9,
    MM_CONNECTION_ACTIVE                                    = 10,
    WAIT_FOR_NETWORK_COMMAND                                = 11,
    WAIT_FOR_RR_CONNECTION_MM_CONNECTION                    = 12,
    WAIT_FOR_REESTABLISH_WAIT_FOR_REEST_REQ                 = 13,
    WAIT_FOR_REESTABLISH_WAIT_FOR_EST_CNF                   = 14,
    WAIT_FOR_RR_ACTIVE                                      = 15,
    WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION              = 16,
    LOCATION_UPDATING_PENDING                               = 17,
    IMSI_DETACH_PENDING                                     = 18,
    MM_WAIT_FOR_ATTACH                                      = 19,
    WAIT_FOR_RR_CONNECTION_LOCATION_UPDATING                = 22,
    LOCATION_UPDATING_INITIATED                             = 23,
    LOCATION_UPDATE_REJECTED                                = 24,
    WAIT_FOR_RR_CONNECTION_IMSI_DETACH                      = 25,
    IMSI_DETACH_INITIATED                                   = 26,
    PROCESS_CM_SERVICE_PROMPT                               = 27,
    TEST_CONTROL_ACTIVE                                     = 31,
    MM_INTER_RAT_CHANGE                                     = 32,
    MM_IDLE_ECALL_INACTIVE                                  = 33,

    MM_STATE_MAX
};
typedef VOS_UINT8 NAS_MM_STATE_ENUM_UINT8;

/* ����״̬���� */
enum MM_SERVICE_STATUS_ENUM
{
    MM_NORMAL_SERVICE       =           0,
    MM_LIMITED_SERVICE      =           1,
    MM_LIMIT_REGION_SERVICE =           2,
    MM_NO_IMSI              =           3,
    MM_NO_SERVICE           =           4,
    MM_ATTEMPTING_TO_UPDATE =           7,
    MM_DETACHED             =           8,
    MM_DISABLE              =           9
};

typedef VOS_UINT8 MM_SERVICE_STATUS_ENUM_UINT8;

/* MM_SUSPEND_SHARE_STRU ucSuspendFlg ȡֵ*/
#define MM_SUSPEND_STATE        1
#define MM_SUSPEND_STATE_NOT    0

/* �ָ���� ResumeResult ȡֵ */
#define MM_RESUME_RESULT_SUCCESS    0x00
#define MM_RESUME_RESULT_FAILURE    0x01
typedef struct
{
    NAS_RRC_RE_TX_MSG_STRU              astReTxMsg[NAS_RRC_MAX_RE_TX_MSG_NUM];  /* ������ϱ����ش���Ϣ */
    VOS_UINT8                           ucSuspendFlg;                           /* MM�Ƿ��ڹ���״̬��־             */
    VOS_UINT8                           ucSuspendCause;                         /* ����ԭ���л�������С����ѡ���� */
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enOldNetType;                           /* ����ǰ��������뼼�� */

    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enDestSuspendRat;                       /* Ҫ�����Ŀ��RAT */
}MM_SUSPEND_SHARE_STRU;


typedef struct
{
    VOS_UINT8                                       ucState;                           /* MM״̬*/
    VOS_UINT8                                       ucPreState;                        /* MMǰ״̬                                 */
    MM_SERVICE_STATUS_ENUM_UINT8                    enMmServiceState;                  /* MM�ķ���״̬*/
    VOS_UINT8                                       ucNtMod;                           /* ����ģʽ*/
    VOS_UINT8                                       ucCsSigConnFlg;                    /* CS�����������Ƿ���ڱ�־ */
    NAS_MML_RRC_INTEGRITY_PROTECT_ENUM_UINT8        enCsIntegrityProtect;              /* �����Ա��� */
    VOS_UINT16                                      usRac;                             /* RAC                                      */
    VOS_UINT32                                      ulT3212Value;                      /* T3212��ʱ��                              */
    MM_LU_INFO_STRU                                 stLuInfo;                          /* LU������Ҫ����ز��� */
    MM_CS_SECURITY_INFO_STRU                        stCsSecutityInfo;                  /* CS��İ�ȫinfomation*/
    MM_MS_CS_INFO_STRU                              stMsCsInfo;                        /* MS CS����Ϣ                              */

    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8       enCsUpdateStatus;                  /* status of location update */
    VOS_UINT8                                       aucTmsi[NAS_MML_MAX_TMSI_LEN];     /* tmsi������ */
    NAS_MML_SIM_CS_SECURITY_INFO_STRU               stCsSimSecuInfo;
    NAS_MML_LAI_STRU                                stCsSuccLai;
    NAS_MML_EQUPLMN_INFO_STRU                       stBackupEquPlmnInfo;

    VOS_UINT8                                       ucT3211Status;
    VOS_UINT8                                       aucReserved[3];

}MM_BACKUP_SHARE_STRU;


typedef struct
{
    NAS_MML_TIN_TYPE_ENUM_UINT8         enTinType;                              /* TIN���� */
    VOS_UINT8                           aucReserve[2];
    VOS_UINT8                           aucImsi[NAS_MML_MAX_IMSI_LEN];          /* �ϴα����IMSI������ */
}NAS_MM_NVIM_TIN_INFO_STRU;



enum NAS_MM_ATTACH_TYPE_ENUM
{
    MM_WAIT_NULL_ATTACH  = 0,
    MM_WAIT_PS_ATTACH,
    MM_WAIT_CS_ATTACH,
    MM_WAIT_CS_PS_ATTACH,
    MM_WAIT_ATTACH_BUTT
};
typedef VOS_UINT32 NAS_MM_ATTACH_TYPE_ENUM_UINT32;


enum NAS_MM_DETACH_TYPE_ENUM
{
    MM_WAIT_NULL_DETACH  = 0,
    MM_WAIT_PS_DETACH,
    MM_WAIT_CS_DETACH,
    MM_WAIT_CS_PS_DETACH,
    MM_WAIT_DETACH_BUTT
};
typedef VOS_UINT32 NAS_MM_DETACH_TYPE_ENUM_UINT32;


typedef struct
{
    VOS_UINT32                          ulOpid;                                 /* MMA���ɺ�ʹ�� */
    NAS_MM_ATTACH_TYPE_ENUM_UINT32      enAttachType;                           /* �ȴ�ATTACH��Ӧ��Ϣ������ */
}NAS_MM_ATTACH_INFO_STRU;


typedef struct
{
    VOS_UINT32                          ulOpid;                                 /* MMA���ɺ�ʹ�� */
    NAS_MM_DETACH_TYPE_ENUM_UINT32      enDetachType;                           /* �ȴ�DETACH��Ӧ��Ϣ������                 */
}NAS_MM_DETACH_INFO_STRU;


typedef struct
{
    VOS_UINT8                           ucT3242ExpiredFlg;
    VOS_UINT8                           ucT3243ExpiredFlg;
    VOS_UINT8                           ucT3242StartNeededFlg;
    VOS_UINT8                           ucT3243StartNeededFlg;

}NAS_MM_ECALL_INFO_STRU;


enum NAS_MM_NETWORK_T3212_VALUE_TYPE_ENUM
{
    NAS_MM_T3212_VALUE_TYPE_BROADCAST,       /* T3212��ʱ��ʱ��ȡ��ϵͳ��Ϣ��Я����ʱ�� */
    NAS_MM_T3212_VALUE_TYPE_NONE_BROADCAST,  /* T3212��ʱ��ʱ��ȡ��lau accept��Per MS T3212 IE Я����ʱ�� */
    NAS_MM_T3212_VALUE_TYPE_BUTT
};
typedef VOS_UINT8 NAS_MM_NETWORK_T3212_VALUE_TYPE_ENUM_UINT8;

typedef struct
{
    /* ʹ��NV�е�T3212ʱ������ */
    VOS_UINT32                          ulUseNvT3212StartLenCount;

    /* ��������T3212ʱ���ı��������ʱ��ʱ�� */
    VOS_UINT32                          ulNetworkT3212RandLen;

    NAS_MML_LAI_STRU                            stAllocT3212ValueLaiInfo;    /* �·�t3212��ʱ��ʱ����������Ϣ */
    NAS_MM_NETWORK_T3212_VALUE_TYPE_ENUM_UINT8  enNetworkT3212ValueType;      /* ����T3212��ʱ��ʱ����Դ�Ǵ�ϵͳ��Ϣ���Ǵ�lau accept��
                                                                                 Per Ms t3212 IE,lau accept������ */
    VOS_UINT8                                   aucReserved[3];
}NAS_MM_T3212_INFO_STRU;


typedef struct
{


    VOS_UINT32                               ulCnfStatus;                       /* �ȴ�CNFԭ��ı��                        */

    MM_MS_CS_INFO_STRU                       MsCsInfo;                          /* MS CS����Ϣ                              */



#define                 MM_CONN_CM_ENTITY_NUM         0x03                      /* CM��ʵ��������                         */

    MM_CONN_CTRL_STRU                   ConnCtrlInfo[MM_CONN_CM_ENTITY_NUM];    /* MM���ӿ��Ʋ���                           */

    VOS_UINT16                               usRac;                             /* RAC                                      */
    NAS_MM_STATE_ENUM_UINT8                  ucState;                           /* MM״̬                                   */
    NAS_MM_STATE_ENUM_UINT8                  ucPreState;                        /* MMǰ״̬                                 */

#define MM_ATT_NOT_NEED                                 0                       /* ATT FLG������                            */

#define MM_ATT_NEED                                     1                       /* ATT FLG����                              */

    VOS_UINT8                               ucAttFlg;                           /* ATT���ڱ�־                              */
#define MM_NOT_SUPPORT                                  0                       /* ��֧��                                   */
#define MM_SUPPORTING                                   1                       /* ֧��                                     */
    VOS_UINT8                               ucMmInfoSuprt;                      /* �Ƿ�֧��MM INFORMAITON                   */
    VOS_UINT8                               ucEmlppSuprt;                       /* �Ƿ�֧��eMLPP                            */

#define     MM_NET_MODE_I                               1                       /* ����ģʽI                                */
#define     MM_NET_MODE_II                              2                       /* ����ģʽII                               */

#define     MM_NET_MODE_III                             3                       /* ����ģʽIII                              */
#define     MM_NET_MODE_INVALID                         0                       /* ����ģʽ��Ч                              */

    VOS_UINT8                               ucNtMod;                            /* ����ģʽ                                 */
    VOS_UINT8                               ucNewNtMod;                         /* �µ�����ģʽ                             */

#define     MM_MS_MODE_NULL                             0                       /* ��ģʽ                                   */
#define     MM_MS_MODE_CS_PS                            1                       /* ģʽA                                    */
#define     MM_MS_MODE_CS                               2                       /* ģʽB                                    */
#define     MM_MS_MODE_PS                               3                       /* ģʽC                                    */
    VOS_UINT8                               ucMsMod;                            /* �û�ģʽ                                 */

#define     MM_CS_SIG_CONN_PRESENT                      0                       /* CS���������Ӵ���                         */
#define     MM_CS_SIG_CONN_ABSENT                       1                       /* CS���������Ӳ�����                       */
    VOS_UINT8                               ucCsSigConnFlg;                     /* CS�����������Ƿ���ڱ�־                 */

#define     MM_FOLLOW_ON                                0                       /* ָʾFollow on                            */
#define     MM_NO_FOLLOW_ON                             1                       /* û��ָʾFollow on                        */
    VOS_UINT8                               ucFollowOnFlg;                      /* �����ӳ�ʹ�ñ�־                         */

    MM_SERVICE_STATUS_ENUM_UINT8            ucMmServiceState;                   /* MM�ķ���״̬                             */

    VOS_UINT8                               ucSecurityMode;                     /* ��ȫģʽ */

    MM_CS_SECURITY_INFO_STRU                CsSecutityInfo;                     /* CS��İ�ȫinfomation                     */

#define                 MM_DETACH_CS_POWEROFF           1
#define                 MM_DETACH_USIM_REMOVE           2
#define                 MM_DETACH_CS_NORMAL             3
#define                 MM_DETACH_NEED_DELAY            4
#define                 MM_DETACH_TYPE_BUTT             5

    VOS_UINT8                               ucDetachType;                       /* DETACH������                             */


    MM_AUTHEN_CTRL_STRU                     AuthenCtrlInfo;                     /* ��Ȩ���̿��Ʋ���                         */

    VOS_UINT8    ucStaAfterWaitForNwkCmd;                                       /* ��¼WAIT FOR NETWORK COMMAND״̬��       *
                                                                                 * Ҫ�����IDLE��״̬                       */

    VOS_UINT8                   ucMMConnEstingPD;                               /* ���ڽ�����MM���ӵ�PD���궨������Ϣ�е�   */

    VOS_UINT8                   ucStaOfRcvXXEstReq;                             /* ��¼�յ�MMXX_EST_REQʱMM��״̬           */

    /* ���ԭ�����ṹ */
    /* ��RRC�Ľӿڹ���ṹ */
    /* RRMM_EST_REQ/RRMM_EST_CNF���� */
#define                 MM_RCV_FLG_NULL                 0x00
#define                 MM_RCV_RRMM_EST_CNF_FLG         0x01
    VOS_UINT8                               ucRcvRrcFlg;

    /* ��AGENT�Ľӿڹ���ṹ */
#define                 MM_RCV_STATUS_CNF_FLG               0x01
#define                 MM_RCV_AUTH_CNF_FLG                 0x02
#define                 MM_RCV_IMEI_CNF_FLG                 0x04

#define                 MM_RCV_READ_FILE_CNF_IMSI_FLG       0x08
#define                 MM_RCV_READ_FILE_CNF_CKIK_FLG       0x10
#define                 MM_RCV_READ_FILE_CNF_LOCA_INFO_FLG  0x20

    VOS_UINT8                               ucRcvAgentFlg;
    /* ���нӿ���Ϣ����ṹ */
    /* CM SERVICE REQUEST���� */
    /* CM RE-ESTABILISHMENT REQUEST���� */
    /* LOCATION UPDATING REQUEST���� */
#define                 MM_RCV_CM_SVC_ACCPT_FLG         0x01
#define                 MM_RCV_LU_ACCPT_FLG             0x02
    VOS_UINT8                               ucRcvMsgFlg;

    VOS_UINT8                               ucSimStatusOpid;
    VOS_UINT8                               ucRrEstReqOpid;

    MM_LU_INFO_STRU                         LuInfo;                             /* LU�����Ϣ                               */

    NAS_MM_PROC_TYPE_ENUM_UINT8         ucProc;                                     /* ��ǰ������                               */

    VOS_UINT16                      usCauseVal;                                 /* ��¼��ԭ��ֵ                             */

    VOS_UINT8                       ucLikeB;                                    /* ��A+Iģʽ��ʱ��,�Ƿ�����A+II��B�Ĵ���    */

    VOS_UINT8                       ucAttDelay;                                 /* �����Attach��־                         */

    VOS_UINT8                       ucSysInfoFlg;

    VOS_UINT8                       ucConnRcvSysFlg;

    VOS_UINT8                       ucPowerOnFlg;

    VOS_UINT8                       ucPagingCause;                              /* Paging Cause                             */

    VOS_UINT8                       ucRejectCause;                              /* ���һ�α��ܾ���ʧ�ܵ�ԭ��ֵ��
                                                                                   ��ӦMM��ѯ��Ϣ���ڵ�"enRejectCause"      */
    VOS_UINT8                       ucCsCipherAlgor ;                           /* �����㷨                                 */

#define MM_IMSI_PAGING                  1
#define MM_TMSI_PAGING                  2

#define MM_STMSI_PAGING                (3)                                      /* L��s-tmsiѰ��*/

    VOS_UINT8                       ucPagingRecordTypeId;                       /* Paging Record Type Id                    */

#define MM_NO_PAGING                    0
#define MM_MO_PAGING                    1
#define MM_MT_PAGING                    2
    VOS_UINT8                       ucPagingType;                               /* Paging Type,ֻ��¼����Ϣ���кͱ���        */

#define MM_LU_FALSE                     0
#define MM_LU_TRUE                      1
    VOS_UINT8                       ucLuState;
    /* ��MM���ӽ����������յ�ϵͳ��Ϣ�����LAI�ı䣬
    ��Ҫ��ֹ��ǰ��MM���ӽ������̣�������LU��
    ���յ�RRMM_REL_IND����˱�־��
    ���յ�RRMM_SYS_INFO_IND������˱�־
    VOS_TRUE:�յ�RRMM_REL_IND����Ҫ��LU
    VOS_FALSE:����Ҫ��LU */
    VOS_UINT8                       ucPendingLu;
    VOS_UINT8                       ucLikeNetmode2;
    VOS_UINT8                       ucSuspendPreState;                                /* MM����ǰ״̬ */

    VOS_UINT8                       ucTime2Sndout;                                    /* ��ǰ�Ƿ���Ҫ����ȫ�ֱ������ط� */

	VOS_UINT8                       aucReserved1[2];

    VOS_BOOL                        bWaitingEstCnf;

    NAS_MM_LINK_CTRL_STRU           stMmLinkCtrl;                               /* MM�����ͷŹ��� */
    VOS_UINT8                       ucRetryLauFlg;                              /* �Ƿ���Ҫ���յ�sys info ���·���LAU */
    VOS_UINT8                       ucGasRrChanIndMsgValidFlg;                  /* GAS���͵�GAS_RR_CHAN_IND��Ϣ�Ƿ�����Ч��־ */
    VOS_UINT8                       ucCallRetryCount;                           /* GSM�£�����ʧ�ܺ����·������������ */
    VOS_UINT8                       ucNotCampONPreState;

    MM_SUSPEND_SHARE_STRU           stSuspendShare;                           /* ����ϵͳ��ѡ���л���CCO��MM���õ�һЩȫ�ֱ���*/
    MM_BACKUP_SHARE_STRU            stBackupShare;
    NAS_MM_ATTACH_INFO_STRU         stAttachInfo;                           /* �ȴ�ATTACH�������Ϣ */
    NAS_MM_DETACH_INFO_STRU         stDetachInfo;                           /* �ȴ�DETACH�������Ϣ */

    /* MM������ȫ�ֱ���ָʾ�Ƿ��������ע�� */
    VOS_UINT8                        ucIsComBined;


    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enPreRatType;

    VOS_UINT8                           ucLauAcceptContainDiffNbLaiFlg;             /* lau accept��Ϣ��Я����ϵͳ��Ϣ��λ������ͬ��NB LAI,UE��Ҫ�������ͷź����Ϸ���lau */

    VOS_UINT8                           ucSrvccFlg;
    /* VOS_TRUE:��ǰ����SRVCC������ VOS_FALSE:��ǰ������SRVCC������;�յ�RRC��SRVCC֪ͨ����ΪTRUE,�յ�RRC��RESUME INDָʾ����� */

    VOS_UINT8                           ucRcvSrvccCallInfoFlg;                  /* SRVCC������CCͬ��CALLINFO��ʶ */
    VOS_UINT8                           aucReserve[1];

    NAS_MM_ECALL_INFO_STRU              stEcallInfo;

    RRC_NAS_EST_RESULT_ENUM_UINT32     enEstCnfResult;

    NAS_MM_T3212_INFO_STRU              stT3212Info;
    /* Added by n00355355 for �����ؽ�, 2015-9-29, begin */
    VOS_UINT32                          ulTransactionEnqSenderPid;
    /* Added by n00355355 for �����ؽ�, 2015-9-29, end */
}MM_GLOBAL_CTRL_STRU;


/* MM Timer����ṹ */
#define             MM_TIMER_STOP        0
#define             MM_TIMER_RUNNING     1
#define             MM_TIMER_PAUSE       2
typedef struct{
    HTIMER               hTimer;
    VOS_UINT32           ulTimerLen;
    VOS_UINT32           ulParam;
    VOS_UINT8            ucMode;
    VOS_UINT8            ucTimerStatus;
}MM_TIMER_STRU;

typedef VOS_VOID  (*MM_CELL_FUN_TYPE)(VOS_VOID *);

typedef VOS_INT32 (*RR_DATA_REQ_FUNC)(VOS_UINT8 ucCnDomain, VOS_UINT8 ucPriority, VOS_UINT32 ulSize, VOS_INT8 *pData);
typedef VOS_INT32 (*RR_EST_REQ_FUNC)(VOS_UINT32 ulOpId, VOS_UINT8 ucCnDomain, VOS_UINT32 ulEstCause, IDNNS_STRU *pIdnnsInfo,
                                     RRC_PLMN_ID_STRU *pstPlmnId, VOS_UINT32 ulSize, VOS_INT8 *pFisrstMsg);
typedef VOS_INT32 (*RR_REL_REQ_FUNC)(VOS_UINT8 ucCnDomain,RRC_CELL_BAR_ENUM_UINT32 enBarValidFlg);
typedef VOS_INT32 (*RR_ABORT_REQ_FUNC)(VOS_UINT32 ulAbortType);
typedef VOS_INT32 (*ATTACH_INFO_REQ_FUNC)(ATTACH_INFO_STRU *pAttachInfo);
typedef VOS_INT32 (*SIM_STATUS_REQ_FUNC) (USIM_VALID_INFO_STRU *pUsimValidInfo);
typedef VOS_INT32 (*PS_DRX_LEN_REQ_FUNC)(VOS_UINT8 ucDrxLen);
typedef VOS_INT32 (*SK_CHANGE_REQ_FUNC)(SECURITY_KEY_INFO_STRU *pSecurityKeyInfo);
typedef VOS_INT32 (*TMSI_LAI_INFO_REQ_FUNC)(NAS_INFO_TMSI_LAI_STRU*);
typedef VOS_INT32 (*DEL_KEY_REQ_FUNC)(VOS_UINT8 ucCnDomain);

typedef struct
{

    struct
    {
        RR_DATA_REQ_FUNC            RrDataReqFunc;
    }SigDataTransfer;

    struct
    {
        RR_EST_REQ_FUNC             RrEstReqFunc;
        RR_REL_REQ_FUNC             RrRelReqFunc;
    }SigConnCtrl;

    /* ָʾ��ǰ����ָ��ָ�� GSM ���� WCDMA �����ͺ��� */
    VOS_UINT8           ucFuncEnvironment;

}NAS_MM_IMPORTED_FUNC_LIST_STRU;

typedef struct
{
    VOS_UINT8       ucExtRspLength;                                             /* Extension Response�ĳ��ȣ���λΪ�ֽ�     */
#define AGENT_AUTH_FAIL_MAC_CODE   0
#define AGENT_AUTH_FAIL_SQN        1
    VOS_UINT8       ucFailureCause;                                             /* AUTN�����ԭ��                           */
    VOS_UINT8       ucFailParaLength;                                           /* Failure Parameter�ĳ��ȣ���λΪ�ֽ�      */

#define AGENT_AUTH_RST_SUCCESS   0
#define AGENT_AUTH_RST_FAILURE   1
    VOS_UINT8       ucCheckRst;                                                 /* �����                                 */
    VOS_UINT8       aucResponse[4];                                             /* RES��byte1��byte4                        */

    VOS_UINT8       aucExtResponse[12];                                         /* Extension Response                       */
    VOS_UINT8       aucCipheringKey[16];                                        /* Cipher Key                               */
    VOS_UINT8       aucIntegrityKey[16];                                        /* Integrity Key                            */

    VOS_UINT8       ucKcLength;
    VOS_UINT8       aucKc[NAS_MML_GSM_KC_LEN];                                        /* Kc */
    VOS_UINT8       aucFailPara[16];                                            /* Failure Parameter                        */
}MM_USIM_AUTHENTICATION_CNF_STRU;

#define WAIT_FOR_WUEPS_START                0
#define WAIT_FOR_MMCMM_START_REQ            1
#define WAIT_FOR_NORMAL_MSG                 2

#define     MM_NSD_MOD_R98_OR_OLDER         2
#define     MM_NSD_MOD_R99_ONWARDS          4

#define     MM_NSD_INITAL_VALUE             0
typedef struct{
    VOS_UINT8           ucNsd;
    VOS_UINT8           ucNsdMod;
}MM_NSD_INFO_ST;

typedef struct
{
    VOS_UINT32                   ulTransactionId;                               /* TI                                       */
    VOS_UINT32                   ulCallType;                                    /* ��������                                  */
    VOS_UINT32                   ulCallMode;
    VOS_UINT32                   ulCallPri ;                                    /* �������ȼ�                                */
}MMCC_EST_REQ_ST;


typedef struct
{
    VOS_UINT32                   ulReleaseType;                                 /* �ͷ�����                                  */
    VOS_UINT32                   ulTransactionId;                               /* TI                                       */
}MMCC_REL_REQ_ST;

typedef struct
{
    VOS_UINT32                   ulTransactionId;                               /* TI                                       */
}MMCC_ABORT_REQ_ST;

typedef struct
{
    VOS_UINT32                   ulTransactionId;                               /* TI                                       */
}MMCC_REEST_REQ_ST;

typedef struct
{
    VOS_UINT32                   ulRefuseCause;                                 /* �ܾ�ԭ��                                  */
}MMCC_PROMPT_REJ_ST;

typedef struct
{
    VOS_UINT32                 ulTi;                                            /* Transaction Id                          */
}MMSS_EST_REQ_ST;

typedef struct
{
    VOS_UINT32                 ulTi;                                            /* Transaction Id                         */
}MMSS_REL_REQ_ST;

typedef struct
{
    VOS_UINT32                   ulTransactionId;                               /* TI                                       */
}MMSS_ABORT_REQ_ST;

typedef struct
{
    VOS_UINT32   ulTi;                                                          /* Transaction Id                           */
    VOS_UINT32   ulEstCause;                                                    /* RRC���ӽ���ԭ��                          */
}MMSMS_EST_REQ_ST;

typedef struct
{
    VOS_UINT32               ulTi;                                              /* transaction id                           */
}MMSMS_REL_REQ_ST;

typedef struct
{
    VOS_UINT32                   ulTransactionId;                               /* TI                                       */
}MMSMS_ABORT_REQ_ST;

typedef struct rrmm_sync_ind_st
{
    VOS_UINT32                   ulChannelMode;                                 /* �ŵ�ģʽ����GSM */
    VOS_UINT32                   ulRabCnt;                                      /* ��Ҫͬ��RAB����                          */
    struct
    {
        VOS_UINT32               ulRabId;                                       /* RAB ID                                   */
        VOS_UINT32               ulCnDomainId;                                  /* ��RAB������                              */
        VOS_UINT32               ulRabSyncInfo;                                 /* ��RAB��ͬ��ָʾ                          */
    }NasSyncInfo[RRC_NAS_MAX_RAB_SETUP];
    VOS_UINT32                   ulReason;
}RRMM_SYNC_IND_ST;

typedef struct
{
    VOS_UINT32                   ulCcMsgSize;
    VOS_UINT8                    aucCcMsg[255];
}CC_MSG_FOR_PCLINT_STRU;

typedef struct
{
    MSG_HEADER_STRU              MsgHeader;
    VOS_UINT32                   ulTransactionId;
    CC_MSG_FOR_PCLINT_STRU       RcvCcMsg;
}MMCC_DATA_IND_FOR_PCLINT_STRU;

typedef struct
{
    VOS_UINT32                   ulSsMsgSize;
    VOS_UINT8                    aucSsMsg[255];
}SS_MSG_FOR_PCLINT_STRU;
typedef struct
{
    MSG_HEADER_STRU              MsgHeader;
    VOS_UINT32                   ulTi;
    SS_MSG_FOR_PCLINT_STRU       SsMsg;
}MMSS_DATA_IND_FOR_PCLINT_STRU;

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif                                                                          /* __cpluscplus                             */

#endif



