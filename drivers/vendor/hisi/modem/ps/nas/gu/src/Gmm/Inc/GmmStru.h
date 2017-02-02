
#ifndef _GMMSTRUCTURE_H_
#define _GMMSTRUCTURE_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#include "GmmCasDef.h"
#include "NasMmlCtx.h"
#include "GmmDef.h"
#include "SmGmmInterface.h"

#pragma pack(4)
/******************************************************************************/
/**************************** GMMȫ�ֿ�����Ϣ *********************************/
/******************************************************************************/

/*****************************************************************************
 ö����    : NAS_GMM_SPEC_PROC_TYPE_ENUM
 �ṹ˵��  : GMM���̶���
*****************************************************************************/
enum NAS_GMM_SPEC_PROC_TYPE_ENUM
{
    GMM_NULL_PROCEDURE                  = 0x00,                                 /* û������                                 */

    GMM_ATTACH_COMBINED                 = 0x10,                                 /* combined attach                          */
    GMM_ATTACH_WHILE_IMSI_ATTACHED      = 0x11,                                 /* GPRS attach while IMSI attached          */
    GMM_ATTACH_NORMAL                   = 0x12,                                 /* normal attach                            */
    GMM_ATTACH_NORMAL_CS_TRANS          = 0x13,                                 /* CSͨ���е�normal attach(A+I)             */

    GMM_RAU_COMBINED                    = 0x20,                                 /* combined RAU                             */
    GMM_RAU_WITH_IMSI_ATTACH            = 0x21,                                 /* combined RAU with IMSI attach            */
    GMM_RAU_NORMAL                      = 0x22,                                 /* normal RAU                               */
    GMM_RAU_NORMAL_CS_TRANS             = 0x23,                                 /* CSͨ���е�normal RAU(A+I)                */
    GMM_RAU_NORMAL_CS_UPDATED           = 0x24,

    GMM_DETACH_COMBINED                 = 0x30,                                 /* GPRS/IMSI detach without switching off   */
    GMM_DETACH_NORMAL                   = 0x31,                                 /* GPRS detach without switching off        */
    GMM_DETACH_WITH_IMSI                = 0x32,                                 /* IMSI detach                              */
    GMM_DETACH_COMBINED_POWER_OFF       = 0x33,                                 /* GPRS/IMSI detach with switching off      */
    GMM_DETACH_NORMAL_POWER_OFF         = 0x34,                                 /* GPRS detach with switching off           */
    GMM_DETACH_COMBINED_SIM_REMOVE      = 0x35,                                 /* GPRS/IMSI detach with switching off      */
    GMM_DETACH_NORMAL_SIM_REMOVE        = 0x36,                                 /* GPRS detach with switching off           */
    GMM_DETACH_NORMAL_NETMODE_CHANGE    = 0x37,                                 /* GPRS detach with netmode change          */

    GMM_SERVICE_REQUEST_DATA_IDLE       = 0x40,                                 /* PMM-IDLE�´�����service request(data)    */
    GMM_SERVICE_REQUEST_DATA_CONN       = 0x41,                                 /* PMM-CONNECTED�´���service request(data) */
    GMM_SERVICE_REQUEST_SIGNALLING      = 0x42,                                 /* service request(signalling)              */
    GMM_SERVICE_REQUEST_PAGING_RSP      = 0x43,                                 /* service request(paging response)         */

    GMM_ABORT_CURRENT_SERVICE           = 0x5f,                                 /* abort current service                    */
    NAS_GMM_SPEC_PROC_TYPE_BUTT
};

typedef VOS_UINT8   NAS_GMM_SPEC_PROC_TYPE_ENUM_UINT8;

/*****************************************************************************
 �ṹ��      : NAS_GMM_LINK_CTRL_STRU
 �ṹ˵��    : GMM RRC���Ӻ�PS�������ӿ���
*****************************************************************************/
typedef struct
{
    NAS_GMM_SPEC_PROC_TYPE_ENUM_UINT8   ucCurrentProc;                          /* ��ǰ���� */
    VOS_UINT8                           ucExistedRrcConn;                       /* �����Ƿ������Ѵ��ڵ�RRC������ */
    VOS_UINT8                           ucExistedPsSignallingConn;              /* �����Ƿ������Ѵ��ڵ�PS���������� */
    VOS_UINT8                           ucSmcOrFirstNasMsgRcvdFlg;              /* �Ƿ�������յ�Security Mode Command����NAS����Ϣ */
}NAS_GMM_LINK_CTRL_STRU;



typedef struct
{
    VOS_UINT8                               aucMccDigit[3];                         /* INTEGER(0..9)                            */
    VOS_UINT8                               ucMncCnt;                               /* MNC�ĸ���                                */
    VOS_UINT8                               aucMncDigit[3];                         /* INTEGER(0..9)                            */
}GMM_PLMN_ID_STRU;

typedef struct
{
    VOS_UINT32             ulMcc;
    VOS_UINT32             ulMnc;
}GMM_PLMN_ID_U32_STRU;

typedef struct
{
    GMM_PLMN_ID_STRU                        PlmnId;
    VOS_UINT8                               aucLac[2];                              /* The LAC field consists of 16 bits.       *
                                                                                 * Bit 8 in octet 1 is the most significant *
                                                                                 * bit and bit 1 in octet 2 is the least    *
                                                                                 * significant bit.                         */
}GMM_LAI_STRU;

typedef struct
{
    GMM_LAI_STRU                            Lai;
    VOS_UINT8                               ucRac;                                  /* BIT STRING(SIZE(8))                      */
}GMM_RAI_STRU;


/* ϵͳ��Ϣ */
typedef struct
{
    GMM_RAI_STRU                            Rai;                                    /* RAI                                      */
    VOS_UINT8                               ucNetMod;                               /* ����ģʽ                                 */
    VOS_UINT8                               ucPsDrxLen;                             /* PS���DRX lengthϵ��                     */
                                                                                /* ucPsDrxLenȡֵ��Χ0����Чֵ����6��9 */

#define GMM_NO_FORBIDDEN                    MMC_GMM_NO_FORBIDDEN                  /* �����κν�ֹ�б���                       */
#define GMM_FORBIDDEN_PLMN                  MMC_GMM_FORBIDDEN_PLMN                /* ��forbidden PLMN list��                  */
#define GMM_FORBIDDEN_PLMN_FOR_GPRS         MMC_GMM_FORBIDDEN_PLMN_FOR_GPRS       /* ��forbidden PLMN for GPRS list��         */
#define GMM_FORBIDDEN_LA_FOR_ROAM           MMC_GMM_FORBIDDEN_LA_FOR_ROAM         /* ��forbidden LA for roaming��             */
#define GMM_FORBIDDEN_LA_FOR_REG_PRVS_SVS   MMC_GMM_FORBIDDEN_LA_FOR_REG_PRVS_SVS /* ��forbidden LA for regional provision of *
                                                                                 * service��                                */
    VOS_UINT8                               ucForbMask;                             /* �Ƿ��ڽ�ֹ�б���                         */

    VOS_UINT8                               ucSysValidFlg;                          /* ϵͳ��Ϣ�Ƿ���Ч��־                     */


#define GMM_NOT_SUPPORT_GPRS                1                                    /* ��ǰС����֧��GPRS                       */
#define GMM_SUPPORT_GPRS                    0                                    /* ��ǰС��֧��GPRS                         */
    VOS_UINT8                               ucNotSupportGprs;                       /* ��ǰС���Ƿ�֧��GPRS��־                 */
    VOS_UINT16                              usGsmCellId;           /* ��ǰС��ID, only for GSM */
    VOS_UINT8                               ucNtType;              /* ��¼ϵͳ��Ϣ������GSM��WCDMA���� */
    VOS_UINT32                              ulCellId;
    VOS_UINT8                               ucCellChgFlg;
}GMM_SYS_INFO_STRU;

/* PS��İ�ȫ��Ϣ */
typedef struct
{
#define GMM_CIPHER_ALGO_UEA0    0
#define GMM_CIPHER_ALGO_UEA1    1
    VOS_UINT8                   ucCiperAlgor;               /*3000�ӿڸ���������Ч*/
}GMM_PS_SECURITY_INFO_STRU;


#define  GMM_MAX_SIZE_IMEISV                                        16
#if (FEATURE_ON == FEATURE_LTE)
#define  NAS_GMM_LMM_TOKEN_LEN                                      32
#endif
typedef struct
{
#define    GMM_UEID_INVALID                                   0x00

#define    GMM_UEID_IMSI                                      0x01
#define    GMM_UEID_P_TMSI                                    0x02
#define    GMM_UEID_P_TMSI_SIGNATURE                          0x04
    VOS_UINT8                               ucUeIdMask;                             /* UeId���ڱ�ʶ                             */

    VOS_UINT8       aucImeisv[GMM_MAX_SIZE_IMEISV];                                 /* IMEISV                                   */
}GMM_UEID_STRU;

/*�˶����Ƶ�LMM��*/
#define GMM_NON_DRX_TIMER_MAX           7


/* GMM_MSG_HOLD_STRU: ulMsgHoldMskȡֵ */
#define                 GMM_MSG_HOLD_FOR_ATTACH    0x00000001
#define                 GMM_MSG_HOLD_FOR_RAU       0x00000002
#define                 GMM_MSG_HOLD_FOR_DETACH    0x00000004
#define                 GMM_MSG_HOLD_FOR_SERVICE   0x00000008
#define                 GMM_MSG_HOLD_FOR_PAGING    0x00000010
#define                 GMM_MSG_HOLD_FOR_SM        0x00000020
#define                 GMM_MSG_HOLD_FOR_POWEROFF  0x00000040
#define                 GMM_MSG_HOLD_FOR_SMS       0x00000080

#define                 GMM_MSG_HOLD_FOR_GSM_SYSINFO       (0x00000100)

/* �˱�־���������³���ʱ��������ϵͳ��Ϣ: PS���������з���RA�ı䣬
�ó��������CS����ҵ����PS����RAU�ᱻ��ȷ�����Ƴٵ�CS�����ͷ�ʱ������
�޸Ĵ˳����еĲ�������:��CS����ҵ�����WAS����RRMM_REL_REQ������WAS�ͷ�
���ӣ�������ϵͳ��Ϣ�����յ�WAS��RRMM_REL_INDʱ�ñ����ϵͳ��Ϣ��RAU */
#define                 GMM_MSG_HOLD_FOR_WAS_SYSINFO     (0x00000200)

/* ��Ϣ�������ݽṹ */
typedef struct{
    VOS_UINT32                               ulMsgHoldMsk;                           /* ������Ϣ������ı�־��                   *
                                                                                 * ÿһ��bit����һ�ֱ����������            */
    VOS_UINT32                               ulMsgAddrForAttach;                     /* ���������Ϣ���׵�ַ                     */
    VOS_UINT32                               ulMsgAddrForRau;                        /* ���������Ϣ���׵�ַ                     */
    VOS_UINT32                               ulMsgAddrForDetach;                     /* ���������Ϣ���׵�ַ                     */
    VOS_UINT32                               ulMsgAddrForService;                    /* ���������Ϣ���׵�ַ                     */
    VOS_UINT32                               ulMsgAddrForPaging;                     /* ���������Ϣ���׵�ַ                     */
    VOS_UINT32                               ulMsgAddrForSm;                         /* ���������Ϣ���׵�ַ                     */
    VOS_UINT32                               ulMsgAddrForPowerOff;                   /* ���������Ϣ���׵�ַ                     */
    VOS_UINT32                               ulMsgAddrForSMS;                        /* ���������Ϣ���׵�ַ                     */
    VOS_UINT32                               ulMsgAddrForGsmSysinfo;                 /* ���������Ϣ���׵�ַ                     */

    VOS_UINT32                               ulMsgAddrForWasSysinfo;

    VOS_UINT8                                ucHandleRauFlg;                         /* ���̽�����Ҫ����RAU�ı�־                */
    VOS_UINT8                                ucInitiateLuFlg;                        /* GMM���ܽ���RAUʱ���Ƿ�Ҫ����MM��LU���̵�
                                                                                 * ��־                                     */
    VOS_UINT8                                ucMmT3211ExpiredDelayRauFlag;      /* �����յ�MM T3211��ʱ��Ϣ��Ҫ�ӳ���rau��ʶ*/
    VOS_UINT8                                ucReserved;

}GMM_MSG_HOLD_STRU;


/* UE��Ϣ */
typedef struct
{
    VOS_UINT8                               ucUpdateSta;                            /* ����״̬                                 */

#define  GMM_MAX_SIZE_NET_CAPABILITY        9
    VOS_UINT8                               ucReserved[2];

#define  GMM_NOT_SUPPORT_INFORMATION_MSG    0
#define  GMM_SUPPORT_INFORMATION_MSG        1
    VOS_UINT8                               ucSupportInfoFlg;                       /* �Ƿ�֧��GMM INFORMATION��Ϣ��־          */
    VOS_UINT8                               aucRadioCpb[MS_RADIO_ACCESS_CAPABILITY_MAX_SIZE];
    VOS_UINT8                               aucTdsRadioCpb[MS_RADIO_ACCESS_CAPABILITY_MAX_SIZE];/* TD��rac������Ϣ */
#if (FEATURE_ON == FEATURE_LTE)


    NAS_MML_PLMN_RAT_PRIO_STRU              stRadioCpbRelatedRatList;          /* ��ǰRadiocCapability��Ӧ�Ľ��뼼���б�  */

#endif


    GMM_UEID_STRU                           UeId;

    /* PS���DRX parameter ���壬��GMM����MML�У������¼�ϴ�Attach����RAUʱDrx������Я��״̬*/
    NAS_MML_PS_REG_CONTAIN_DRX_PARA_ENUM_UINT8              enLatestAttachOrRauContainDrx;

    VOS_UINT8                                               ucMsRadioCapSupportLteFromRegReq;   /* ATTACH��RAUʱЯ����MS Radio Access capability IE�Ƿ�֧��LTE,VOS_TRUE:֧��LTE,VOS_FALSE:��֧��LTE */
    VOS_UINT8                                               ucMsRadioCapSupportLteFromAs;       /* ��¼GAS����㷢�͵�GRRMM_MS_RADIO_ACCESS_CAPABILITIES_IND��GRRMM_MS_RADIO_ACCESS_CAPABILITIES_TDS_IND
                                                                                                  �Ƿ�֧��LTE,VOS_TRUE:֧��L��VOS_FALSE:��֧��L */
    NAS_MML_VOICE_DOMAIN_PREFERENCE_ENUM_UINT8              enVoiceDomainFromRegReq;            /* ��¼����ATTACH��RAUʱ��voice domain */

}GMM_UE_INFO_STRU;

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �ṹ��    : GMM_MAPPED_INFO_FROM_EPS_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��Lģ��ȡ����Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucUeIdMask;                             /* UeId���ڱ�ʶ                             */
    VOS_UINT8                           aucPtmsi[NAS_MML_MAX_PTMSI_LEN];           /* BIT STRING(SIZE(32))                     */
    VOS_UINT8                           aucPtmsiSignature[NAS_MML_MAX_PTMSI_SIGNATURE_LEN];
    GMM_RAI_STRU                        Rai;
    VOS_UINT8                           aucNasToken[NAS_GMM_LMM_TOKEN_LEN];
}GMM_MAPPED_INFO_FROM_EPS_STRU;
#endif




/* CS��������Ϣ */
typedef struct
{
    VOS_UINT8                               ucCsTransFlg;                           /* CS���Ƿ�ͨ���б�־                       */

}GMM_CS_INFO_STRU;

typedef struct
{
    VOS_UINT8                               ucYear;                                 /* ��                                       */
    VOS_UINT8                               ucMonth;                                /* ��                                       */
    VOS_UINT8                               ucDay;                                  /* ��                                       */
    VOS_UINT8                               ucHour;                                 /* Сʱ                                     */
    VOS_UINT8                               ucMinute;                               /* ����                                     */
    VOS_UINT8                               ucSecond;                               /* ��                                       */
    VOS_UINT8                               ucTimeZone;                             /* ʱ��                                     */
}GMM_UNIV_TIME_LOC_TIME_ZONE_STRU;


/* GMM infomation */
typedef struct
{
    VOS_UINT8                               ucFullNameLen;                          /* Full name for network�ĳ���              */
#define     GMM_MAX_SIZE_FULL_NAME_FOR_NETWORK                8
    VOS_UINT8       aucFullNtName[GMM_MAX_SIZE_FULL_NAME_FOR_NETWORK];              /* Full name for network                    */
    VOS_UINT8                               ucShortNameLen;                         /* Short name for network�ĳ���             */
#define     GMM_MAX_SIZE_SHORT_NAME_FOR_NETWORK               4
    VOS_UINT8       aucShortNtName[GMM_MAX_SIZE_SHORT_NAME_FOR_NETWORK];            /* Short name for network                   */
#define     GMM_UNIVERSAL_TIME                 0x01
#define     GMM_LOCAL_TIME_ZONE                0x02
#define     GMM_DAYLIGHT_TIME                  0x04
    VOS_UINT32                               ulInfoMsk;                              /* Information�и���IE���ޱ�־��            *
                                                                                 * ÿһ��bit����һ��IE                      */

    GMM_UNIV_TIME_LOC_TIME_ZONE_STRU        UnivTime;                               /* Universal time and local time zone       */
    VOS_UINT8                               ucLocTimeZone;                          /* Local time zone                          */
    VOS_UINT8                               ucSavTime;                              /* Network Daylight Saving Time             */
    VOS_UINT8                               ucLsaIdLen;                             /* Length of LSA Identifier contents        */
    VOS_UINT8                               aucLsaId[3];                            /* LSA Identifier                           */
}GMM_INFO_STRU;

/* GMM״̬  */
#define     GMM_NULL                                          0x00              /* GMM_NULL״̬                             */
#define     GMM_REGISTERED_INITIATED                          0x01              /* GMM-REGISTERED-INITIATED״̬             */
#define     GMM_DEREGISTERED_INITIATED                        0x02              /* GMM_DEREGISTERED_INITIATED               */
#define     GMM_ROUTING_AREA_UPDATING_INITIATED               0x03              /* GMM_ROUTING_AREA_UPDATING_INITIATED      */
#define     GMM_SERVICE_REQUEST_INITIATED                     0x04              /* GMM-SERVICE-REQUEST-INITIATED            */

#define     GMM_TC_ACTIVE                                     0x05              /* GMM-TC-ACTIVE(����TCʱ��״̬)            */
#define     GMM_GPRS_SUSPENSION                               0x06              /* (GSM only)GMM_GPRS_SUSPENSION */

#define     GMM_DEREGISTERED_NORMAL_SERVICE                   0x10              /* GMM-DEREGISTERED.NORMAL-SERVICE          */
#define     GMM_DEREGISTERED_LIMITED_SERVICE                  0x11              /* GMM-DEREGISTERED.LIMITED-SERVICE         */
#define     GMM_DEREGISTERED_ATTACH_NEEDED                    0x12              /* GMM-DEREGISTERED.ATTACH-NEEDED           */
#define     GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH             0x13              /* GMM-DEREGISTERED.ATTEMPTING-TO-ATTACH    */
#define     GMM_DEREGISTERED_NO_CELL_AVAILABLE                0x14              /* GMM-DEREGISTERED.NO-CELL-AVAILABLE       */
#define     GMM_DEREGISTERED_PLMN_SEARCH                      0x15              /* GMM-DEREGISTERED.PLMN-SEARCH             */
#define     GMM_DEREGISTERED_NO_IMSI                          0x16              /* GMM-DEREGISTERED.NO-IMSI                 */

#define     GMM_REGISTERED_NORMAL_SERVICE                     0x20              /* GMM-REGISTERED.NORMAL-SERVICE            */
#define     GMM_REGISTERED_LIMITED_SERVICE                    0x21              /* GMM-REGISTERED.LIMITED-SERVICE           */
#define     GMM_REGISTERED_UPDATE_NEEDED                      0x22              /* GMM-REGISTERED.UPDATE-NEEDED             */
#define     GMM_REGISTERED_ATTEMPTING_TO_UPDATE               0x23              /* GMM-REGISTERED.ATTEMPTING-TO-UPDATE      */
#define     GMM_REGISTERED_NO_CELL_AVAILABLE                  0x24              /* GMM-REGISTERED.NO-CELL-AVAILABLE         */
#define     GMM_REGISTERED_PLMN_SEARCH                        0x25              /* GMM-REGISTERED.PLMN-SEARCH               */
#define     GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM            0x26              /* GMM-REGISTERED.ATTEMPTING-TO-UPDATE-MM   */
#define     GMM_REGISTERED_IMSI_DETACH_INITIATED              0x27              /* GMM-REGISTERED.IMSI-DETACH-INITIATED     */

#define     GMM_SUSPENDED_NORMAL_SERVICE                      0x30              /* GMM-SUSPENDED.NORMAL-SERVICE             */
#define     GMM_SUSPENDED_GPRS_SUSPENSION                     0x31              /* GMM-SUSPENDED.GPRS-SUSPENSION            */
#define     GMM_SUSPENDED_WAIT_FOR_SYSINFO                    0x32              /* GMM-SUSPENDED.WAIT-FOR-SYSINFO           */

typedef VOS_UINT8   GMM_STATE_TYPE_UINT8;

#define     GMM_NET_MODE_I                                    1                 /* ����ģʽI                                */
#define     GMM_NET_MODE_II                                   2                 /* ����ģʽII                               */
#define     GMM_NET_MODE_III                                  3                 /* ����ģʽIII                              */
typedef VOS_UINT8   GMM_NET_MODE_TYPE_UINT8;


#define  GMM_REAL_PROCEDURE        MMC_GMM_REAL_PROCEDURE                       /* ������������                             */
#define  GMM_UNREAL_PROCEDURE      MMC_GMM_UNREAL_PROCEDURE                     /* û��������������                         */

typedef struct
{
    VOS_UINT8                           ucSndDetachCnt;
    RRC_NAS_EST_RESULT_ENUM_UINT32      ulEstResult;           /* �ػ�ʱ�������ӽ������ */
}GMM_POWER_OFF_CTRL_STRU;

enum GMM_SERVICE_REQ_TYPE_ENUM
{
    GMM_SERVICE_REQ_NONE                  = 0,                /* ��ʾ����������û�з������� */
    GMM_SERVICE_REQ_PAGING                = 1,                /* ��ʾ���������н��յ�paging��Ϣ */
    GMM_SERVICE_REQ_PDPACT                = 2,                /* ��ʾ���������н��յ�PDP�������� */
    GMM_SERVICE_REQ_BUTT
};
typedef VOS_UINT8 GMM_SERVICE_REQ_TYPE_ENUM_UINT8;



typedef struct
{
    VOS_UINT8                                   ucState;                                /* GMM״̬*/
    VOS_UINT8                                   ucNtMod;                                /* ����ģʽ*/
    VOS_UINT8                                   ucPsSigConnFlg;                         /* PS�����������Ƿ���ڱ�־ */
    NAS_MML_RRC_INTEGRITY_PROTECT_ENUM_UINT8    enPsIntegrityProtect;                   /* �����Ա�����Ϣ */
    VOS_UINT8                                   ucRauAttmptCnt;                         /* RAU attempt counter                      */
    GMM_GPRS_SRV_STATE                          ucSrvState;                             /* ��ǰGMM GPRS����״̬ */
    GMM_PS_SECURITY_INFO_STRU                   stPsSecutityInfo;                       /* PS���security information*/
    NAS_MML_SIM_PS_SECURITY_INFO_STRU           stSimPsSecurity;                        /* SIM���е�PS��İ�ȫ���� */
    GMM_SYS_INFO_STRU                           stSysInfo;                              /* ��ǰϵͳ��Ϣ */
    GMM_UE_INFO_STRU                            stUeInfo;                               /* UE ��Ϣ                                  */

    NAS_MML_EQUPLMN_INFO_STRU                   stBackupEquPlmnInfo;

    NAS_MML_TIN_TYPE_ENUM_UINT8                 enTinType;                              /* TIN����*/
    VOS_UINT8                                   ucT3311Status;
    VOS_UINT8                                   aucReserved[2];
}GMM_BACKUP_SHARE_STRU;
enum NAS_GMM_ATTACH_TYPE_ENUM
{
    GMM_WAIT_NULL_ATTACH  = 0,
    GMM_WAIT_PS_ATTACH,
    GMM_WAIT_CS_ATTACH,
    GMM_WAIT_CS_PS_ATTACH,
    GMM_WAIT_ATTACH_BUTT
};
typedef VOS_UINT8 NAS_GMM_ATTACH_TYPE_ENUM_UINT32;


enum NAS_GMM_DETACH_TYPE_ENUM
{
    GMM_WAIT_NULL_DETACH = 0,
    GMM_WAIT_PS_DETACH,
    GMM_WAIT_CS_DETACH,
    GMM_WAIT_CS_PS_DETACH,
    GMM_WAIT_DETACH_BUTT
};

typedef VOS_UINT32 NAS_GMM_DETACH_TYPE_ENUM_UINT32;


typedef struct
{
    VOS_UINT32                          ulOpid;                                 /* MMA���ɺ�ʹ�� */
    NAS_GMM_ATTACH_TYPE_ENUM_UINT32     enAttachType;                           /* �ȴ�ATTACH��Ӧ��Ϣ������ */
}NAS_GMM_ATTACH_INFO_STRU;


typedef struct
{
    VOS_UINT32                          ulOpid;                                 /* MMA���ɺ�ʹ�� */
    NAS_GMM_DETACH_TYPE_ENUM_UINT32     enDetachType;                           /* �ȴ�DETACH��Ӧ��Ϣ������                 */
}NAS_GMM_DETACH_INFO_STRU;


typedef struct
{
    NAS_MML_TIN_TYPE_ENUM_UINT8         enTinType;                              /* TIN���� */
    VOS_UINT8                           aucReserve[2];
    VOS_UINT8                           aucImsi[NAS_MML_MAX_IMSI_LEN];          /* �ϴα����IMSI������ */
}NAS_GMM_NVIM_TIN_INFO_STRU;


enum NAS_GMM_LOG_OM_INFO_ENUM
{
    NAS_GMM_LOG_GUTI_INFO_IND       = 0xa00,
    NAS_GMM_LOG_TIN_TYPE_INFO_IND,
    NAS_GMM_LOG_PS_REG_DRX_INFO_IND,
    NAS_GMM_LOG_BUTT
};
typedef VOS_UINT32 NAS_GMM_LOG_OM_INFO_ENUM_UINT32;


typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;
    NAS_MML_TIN_TYPE_ENUM_UINT8         enTinType;                              /* TIN���� */
    VOS_UINT8                           aucReserve[3];
}NAS_GMM_LOG_TIN_INFO_STRU;
typedef struct
{
    MSG_HEADER_STRU                               stMsgHeader;
    NAS_MML_PS_REG_CONTAIN_DRX_PARA_ENUM_UINT8    enPsRegContainDrx;            /* �Ƿ�Я��Drx ��������*/
    VOS_UINT8                                     aucReserve[3];
}NAS_GMM_LOG_PS_REG_DRX_INFO_STRU;

/* ucEventCauseʹ�õĺ궨�� */
#define GMM_EVENT_CAUSE_INVALID      0xff
typedef struct
{
    GMM_MSG_HOLD_STRU                   MsgHold;                                /* ԭ�ﱣ���ṹ                             */
    GMM_PLMN_ID_U32_STRU                aEquPlmnIdList[15];                     /* ����RAU Accept��Ϣ�е�Equ Plmn��Ϣ����������ʹ�� */
    VOS_UINT8                           ucEquPlmnNum;
    GMM_STATE_TYPE_UINT8                ucState;                                /* GMM״̬                                  */
    VOS_UINT8                           ucServPreSta;                           /* ����SERVICE REQ���̷���ǰ��GMM״̬       */
    VOS_UINT8                           ucPlmnSrchPreSta;                       /* ����ǰ��״̬ */
    GMM_NET_MODE_TYPE_UINT8             ucNetMod;                               /* ����ģʽ                                 */
    NAS_GMM_SPEC_PROC_TYPE_ENUM_UINT8   ucSpecProc;                             /* ��ǰ���е�specific����                   */
    NAS_GMM_SPEC_PROC_TYPE_ENUM_UINT8   ucSpecProcHold;                         /* ������specific����                       */
    NAS_GMM_SPEC_PROC_TYPE_ENUM_UINT8   ucSpecProcInCsTrans;                    /* CSͨ���н��е�specific����               */
    VOS_UINT8                           ucSigConFlg;                            /* ���������Ƿ���ڱ�־                     */
    VOS_UINT8                           ucFollowOnFlg;                          /* �����ӳ�ʹ�ñ�־                         */
    VOS_UINT8                           ucCvrgAreaLostFlg;                      /* �Ƿ���������ı�־                       */
    VOS_UINT8                           ucRealProFlg;                           /* �Ƿ������������̱�־                     */
    VOS_UINT8                           ucTcPreSta;                             /* ����TC֮ǰ��״̬                         */
    VOS_UINT8                           ucCipherStartFlg;                       /* ����������־                             */
    VOS_UINT8                           ucRelCause;                             /* ���һ�����������ͷ�ԭ��                 */
    VOS_UINT8                           ucIntegrityProtStart;                   /* �����Ա���������־                       */
    VOS_UINT8                           ucGprsResumeFlg;
    VOS_UINT8                           ucSuspendProc;
    VOS_UINT8                           ucRaiChgRelFlg;                         /* �Ƿ���RAI�ı䵼������Ҫ���ͷ����ӵı�־  */
    VOS_UINT8                           ucLaNotAllowFlg;                        /* ��¼PS�����̱��ܾ���ԭ��ֵ�Ƿ���#12    */
    VOS_UINT8                           ucTime2Sndout;                          /* ��ǰ�Ƿ���Ҫ����ȫ�ֱ������ط� */
    VOS_UINT8                           ucFopFlg;                               /* ��¼�տ���Ϣ��ָʾ�Ƿ�Follow On PS�������ӵı�־ */
    VOS_UINT8                           ucNeedChgServiceStatus;                 /* �Ƿ���Ҫ֪ͨMMC�ı�MMC�ķ���״̬,VOS_TRUE:��Ҫ,VOS_FALSE:����Ҫ */
    VOS_UINT8                           ucEventCause;                           /* �ϱ�OM�¼���ʹ�õ�ԭ��ֵ����ֵ��Чʱ��ʹ�ú������Դ���ԭ��ֵ */
    GMM_SERVICE_REQ_TYPE_ENUM_UINT8     enServReq;
    GMM_UE_INFO_STRU                    UeInfo;                                 /* UE ��Ϣ                                  */
    GMM_SYS_INFO_STRU                   SysInfo;                                /* �ϴ�פ����ϵͳ��Ϣ                                 */
    GMM_SYS_INFO_STRU                   SysInfo_Registered;                     /* �ɹ�ע��ʱ����С����ϵͳ��Ϣ                                 */
    GMM_PS_SECURITY_INFO_STRU           PsSecutityInfo;                         /* PS���security information               */
    GMM_CS_INFO_STRU                    CsInfo;                                 /* CS��������Ϣ                           */
    GMM_POWER_OFF_CTRL_STRU             stPowerOffCtrl;
    VOS_UINT32                          ulEstCause;                             /* ��¼RRC���ӽ���ԭ����;��Follow On��������ָʾ���ӳ�
                                                                                    PS����������ͷ�֮�����½���RRC������д����ԭ�� */
    VOS_UINT32                          ulGmmAttachFlg;

    NAS_GMM_LINK_CTRL_STRU              stGmmLinkCtrl;                          /* GMM �����ͷŹ��� */

    VOS_UINT8                           ucInterRatFlg;                          /* ��¼��wait for sysinfo״̬���յ�Gas�Ĺ���ʱ����RABM����gprs suspension��*/
                                                                                /* ������Ϊhandover.���յ�Gas�Ļָ�����RABM����gprs resume��������Ϊhandover*/
    VOS_UINT8                           ucUserPsAttachFlag;                     /* AT ����ATTACH�ı�־ ,VOS_TRUE��ʾAT������ATTACH,VOS_FALSE��ʾû�� */
    VOS_UINT16                          usUplinkDataStatus;                     /* ����RABM���͵�GMMRABM_REESTABLISH_REQ��Ϣ�е���·״̬��Ϣ */
#if( FEATURE_ON == FEATURE_LTE)
    GMM_MAPPED_INFO_FROM_EPS_STRU       stMappedUeInfoFromEps;                  /* ��LMM��ȡ������Ϣ                            */
#endif
    GMM_BACKUP_SHARE_STRU               stBackupShare;                            /* GMM���ݵ�һЩȫ�ֱ�����Ŀǰֻ��CCO�����õ� */

    NAS_GMM_ATTACH_INFO_STRU            stAttachInfo;                           /* �ȴ�ATTACH�������Ϣ */
    NAS_GMM_DETACH_INFO_STRU            stDetachInfo;                           /* �ȴ�DETACH�������Ϣ */

    VOS_UINT8                           ucDetachAcceptedFlg;                    /* ��־��¼GMM�Ƿ�շ�����DETACH ACCEPTED��Ϣ��LL */
    VOS_UINT8                           ucRelConnAfterPdpDeact;
    GMM_SM_CAUSE_ENUM_UINT16            enAttach2DetachCause;
    VOS_UINT8                           ucRcvNetDetachFlg;

    VOS_UINT8                           ucIsNeedStartT3340PdpExist;
    VOS_UINT8                           aucReseve[2];

    /* ��¼GMMǨ��ATTEMPT TO UPDATE״̬��update statusǨ��2ʱ��RAI��Ϣ���ڿ�����ps��csps detach����ע��ʱ��������ñ�� */
    NAS_MML_RAI_STRU                     stAttemptToUpdateRai;

    NAS_MML_PLMN_WITH_RAT_STRU           stAllocT3302ValuePlmnWithRat;  /* �·�T3302��ʱ��ʱ����������Ϣ */
}GMM_GLOBAL_CTRL_STRU;


enum NAS_GMM_SPEC_PROC_ENUM
{
    NAS_GMM_SPEC_PROC_ATTACH  = 0,
    NAS_GMM_SPEC_PROC_RAU        ,
    NAS_GMM_SPEC_PROC_BUTT
};
typedef VOS_UINT8 NAS_GMM_SPEC_PROC_ENUM_UINT8;

/*  ��ȡlMM�İ�ȫ�������� ���淢�� Attach��Rau���Լ� RAU������ */
typedef struct
{
    NAS_GMM_SPEC_PROC_ENUM_UINT8        enGmmSpecProc;
    VOS_UINT8                           ucRauType;

}GMM_SPEC_PROC_CONTEXT_STRU;


/******************************************************************************/
/*************************** GMM�շ�ԭ��Ĺ��� ********************************/
/******************************************************************************/

typedef struct
{
#define     GMM_RRC_RRMM_EST_CNF_FLG                          0x01              /* ���յ��쳣ԭ��ʱ����ñ�־               */

#define     GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG             0x02

    VOS_UINT8                               ucCnfMask;                              /* �ȴ�CNFԭ��ı��                        */
    /* opidʹ��ԭ���ȼӺ��� */
    VOS_UINT8                               ucUsimStaOpid;                          /* AGENT_USIM_STATUS_REQԭ���е�Opid        */
    VOS_UINT8                               ucRrmmEstOpid;                          /* RRMM_EST_REQԭ���е�Opid                 */

}GMM_REQ_CNF_MNG_STRU;



/******************************************************************************/
/*************************** GMM Timer���� ************************************/
/******************************************************************************/

typedef struct
{
    /* MASKʹ��˵������ʱ������ʱusTimerRunMask����λ��usTimerSusMask�����㣻
       ��ʱ������ʱusTimerRunMask���䣨��Ȼ��λ����usTimerSusMask����λ��
       ��ʱ��ֹͣʱusTimerRunMask�����㣻usTimerSusMask�����㡣
       ���տ���Ϣ�и��¶�ʱ��ʱ��ʱusTimerValMask����λ����ʱ������ʱ�жϣ�
       �类��λ�������OS API����ʱ��������usTimerSusMask���㣬Ȼ����������*/
    VOS_UINT32                               ulTimerRunMask;                         /* TIMER ID С��32ʱ��Timer�������(����ЩTimer������)         */
    VOS_UINT32                               ulTimerRunMaskEx;                       /* TIMER ID 32-64 ʱ��Timer�������(����ЩTimer������)         */
    
    VOS_UINT32                               ulTimerSusMask;                         /* TIMER ID С��32ʱ��Timer������(����ЩTimer������)         */
    VOS_UINT32                               ulTimerSusMaskEx;                       /* TIMER ID 32-64ʱ��Timer������(����ЩTimer������)         */

    VOS_UINT32                               ulTimerSusTcMask;                       /* TIMER ID С��32ʱ��Timer��TC�й�����(����ЩTimer������)   */
    VOS_UINT32                               ulTimerSusTcMaskEx;                     /* TIMER ID 32-64ʱ��Timer��TC�й�����(����ЩTimer������)   */

    VOS_UINT32                               ulTimerValMask;                         /* TIMER ID С��32ʱ��Timerʱ�����±��(����ЩTimerʱ��������) */
    VOS_UINT32                               ulTimerValMaskEx;                       /* TIMER ID 32-64ʱ��Timerʱ�����±��(����ЩTimerʱ��������) */

    struct{
        HTIMER                               hTimer;                                /* TimerID                                  */
        VOS_UINT32                           ulTimerVal;                             /* Timerʱ��(��λ������)                    */
        VOS_UINT32                           ulParam;
        VOS_UINT8                            ucMode;
    }aTimerInf[GMM_TIMER_NUM];
}GMM_TIMER_STRU;

/******************************************************************************/
/*************************** ATTACH ���ֵ����ݽṹ ****************************/
/******************************************************************************/

typedef struct
{
    VOS_UINT8                              ucAttachAttmptCnt;                       /* ATTACH attempt counter                   */
    VOS_UINT8                              ucT3310outCnt;                           /* T3310�������n                           */
    VOS_UINT8                              ucRetryFlg;                              /* �����µ�С���Ƿ����attach               */
    VOS_UINT8                              ucSmCnfFlg;                              /* attach������,�Ƿ�ʹ��CNFԭ���ϱ���SM     */

    VOS_UINT8                              ucPagingWithImsiFlg;                     /* ATTACH�Ĵ���ԭ���Ƿ����յ������IMSIѰ�� */
    VOS_UINT8                              ucRetryAttachForRelCtrlFlg;              /* Attach���̱��쳣�ͷţ���Ҫ���յ�ϵͳ��Ϣ�����·��� */
    VOS_UINT8                              ucReserve;

}GMM_ATTACH_CTRL_STRU;


/******************************************************************************/
/*************************** RAU ���ֵ����ݽṹ *******************************/
/******************************************************************************/
/* ���ڱ������е�NPDU��Ϣ����GSM�£������������յ������RAU ACCEPT��Ϣʱʹ�� */
#define                 GMM_MAX_SIZE_N_PDU                    17
typedef struct
{
    VOS_UINT8                              ucNpduCnt;                               /* N-PDU Numbers�ĸ���                      */
    VOS_UINT8                              aucNpduNum[GMM_MAX_SIZE_N_PDU];          /* N-PDU Numbers                            */
}GMM_DOWNLINK_NPDU_STRU;

typedef struct
{
    VOS_UINT8                           ucRauAttmptCnt;                          /* RAU attempt counter                      */
    VOS_UINT8                           ucT3330outCnt;                           /* T3330�������n                           */
    VOS_UINT8                           ucCsSpringRauFlg;                        /* MmcCmServiceRejectInd #4 ����RAU�ı�־   */

    VOS_UINT8                           ucRetryFlg;                              /* �����µ�С���Ƿ����RAU                  */
    VOS_UINT8                           ucT3312ExpiredFlg;                       /* ��������ʱT3312�����־                  */
    VOS_UINT8                           ucPeriodicRauFlg;                        /* ��ǰRAU�Ƿ�������RAU��־                 */
    VOS_UINT8                           ucNpduCnt;                               /* N-PDU Numbers�ĸ���                      */

    VOS_UINT8                           aucNpduNum[GMM_MAX_SIZE_N_PDU];          /* N-PDU Numbers                            */
    VOS_BOOL                            bNpduPresentInRauAccFlg;
    VOS_UINT8                           ucRetryRauForRelCtrlFlg;                 /* ��RAU���̱��쳣�ͷź��Ƿ���Ҫ���·����־ */
    VOS_UINT8                           ucT3311ExpiredFlg;
    VOS_UINT8                           aucReserve[2];
}GMM_RAU_CTRL_STRU;


/******************************************************************************/
/*************************** DETACH ���ֵ����ݽṹ ****************************/
/******************************************************************************/

typedef struct
{
    VOS_UINT8                           ucT3321OutCnt;                          /* T3321�������n                           */
    VOS_UINT8                           ucRetryDetachForRelCtrlFlg;             /* Detach���̱��쳣�ͷţ���Ҫ���յ�ϵͳ��Ϣ�����·��� */
    NAS_GMM_SPEC_PROC_TYPE_ENUM_UINT8   ucDetachProc;                           /* ����Detach�������� */

    VOS_UINT8                           ucSysCfgDetachFlg;

}GMM_DETACH_CTRL_STRU;

/******************************************************************************/
/*************************** Authentication ���ֵ����ݽṹ ********************/
/******************************************************************************/
#define GMM_AUTHEN_REJ_CAUSE_INVALID     0
#define GMM_AUTHEN_REJ_CAUSE_MAC_FAIL    1
#define GMM_AUTHEN_REJ_CAUSE_SYNC_FAIL   2
#define GMM_AUTHEN_REJ_CAUSE_GSM_FAIL    3

typedef struct
{
    VOS_UINT8                              ucAuthenAttmptCnt;                       /* Authentication attempt counter           */
    VOS_UINT8                              ucRandStoredFlg;                         /* RAND�Ƿ񱻴洢�ı�־                     */
    VOS_UINT8                              ucResStoredFlg;                          /* ��ʧ���ڴ�洢��־                       */
                                                                                /* 1:��ʧ���ڴ治Ϊ��                       *
                                                                                 *   RAND��RESΪ��ʧ���ڴ��е�ֵ            *
                                                                                 * 0:��ʧ���ڴ�Ϊ��,RANDΪ��һ�ε�RAND��ֵ  */
#define                 GMM_MAX_SIZE_RAND                     16
    VOS_UINT8                              aucRand[GMM_MAX_SIZE_RAND];              /* ARAND                                    */
#define                 GMM_MAX_SIZE_RES                      4
    VOS_UINT8                              aucRes[GMM_MAX_SIZE_RES];                /* RES                                      */

    VOS_UINT8                              ucResExtLen;                             /* RES(EXTERN)�ĳ��ȣ�Ϊ0ʱaucResExt������  */
#define                 GMM_MAX_SIZE_RES_EXT                  12
    VOS_UINT8                              aucResExt[GMM_MAX_SIZE_RES_EXT];         /* RES(EXTERN)                              */


    VOS_UINT8                              ucImeisvFlg;                             /* RESPONSE��Ϣ���Ƿ�Ҫ��IMEISV             */
    VOS_UINT8                              ucAcRefNum;                              /* A&C reference number                     */
    VOS_UINT8                              ucCksnSav;                               /* �ݴ���Ϣ�е�CKSN                         */

    VOS_UINT8                              aucRandSav[GMM_MAX_SIZE_RAND];           /* �ݴ���Ϣ�е�RAND                         */
    VOS_UINT8                              ucAutnLen;                               /* AUTN���� */
#define                 GMM_MAX_SIZE_AUTN                     17
    VOS_UINT8                          aucAutn[GMM_MAX_SIZE_AUTN];              /* AUTN���� */
#define  GMM_UMTS_AUTHEN_SUPPORTED     1
#define  GMM_UMTS_AUTHEN_UNSUPPORTED   0
    VOS_UINT8                              ucUmtsAuthFlg;                           /* UMTS authentication supported flag       */

    VOS_UINT8                              ucLastFailCause;
    VOS_UINT8                              reserve;

    VOS_UINT32                             ulNasMsgSize;                        /* ���浱ǰ�յ��������Ȩ��Ϣ */
    VOS_UINT8                              aucNasMsg[255];
    VOS_UINT8                              ucOpId;

}GMM_AUTHEN_CTRL_STRU;


/******************************************************************************/
/*************************** SR ���ֵ����ݽṹ ********************************/
/******************************************************************************/

typedef struct
{
    VOS_UINT8                           ucSmsFlg;                               /* �Ƿ���SMS������SR���̱�־                */
    VOS_UINT8                           ucSmFlg;                                /* �Ƿ���SM������SR���̱�־                */
    VOS_UINT8                           ucRejCauseVaildFlg;
    VOS_UINT8                           ucRejCause;

    VOS_UINT8                           ucRetrySrForRelCtrlFlg;                 /* ��·�ͷź��Ƿ���Ҫ���·���Service Quest ����*/
    NAS_GMM_SPEC_PROC_TYPE_ENUM_UINT8   ucServiceRequestProc;
    VOS_UINT8                           aucReserve[2];
}GMM_SR_CTRL_STRU;


/*******************************************************************************
 �ṹ��    : GMM_INTER_RAT_HANDOVER_INFO_CTRL_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����inter rat hand over info���ݣ�����ؿ���״̬��
*******************************************************************************/
typedef struct
{
    /* �Ƿ���Ҫ�ȴ�WRR�ظ�InterRatInfoCnf��Ϣ�󣬲Żظ�����Attach Complete��Ϣ,
       VOS_TRUE:��Ҫ,VOS_FALSE:����Ҫ */
    VOS_UINT8                           ucAttachCmpWaitInterRatCnfMsg;
    /* �Ƿ���Ҫ�ȴ�WRR�ظ�InterRatInfoCnf��Ϣ�󣬲Żظ�����RAU Complete��Ϣ,
       VOS_TRUE:��Ҫ,VOS_FALSE:����Ҫ */
    VOS_UINT8                           ucRauCmpWaitInterRatCnfMsg;

    /* CNF��Ϣ�Ƿ����յ���*/
    VOS_UINT8                           ucInterRatCnfMsgRcvdFlg;

    VOS_UINT8                           ucDataLen;
    VOS_UINT8                           aucData[RRC_NAS_INTER_RAT_HANDOVER_INFO_LEN];

    VOS_UINT8                           ucEutranInterRatInfoRequestedFlag;
    VOS_UINT8                           ucReserve[1];
}GMM_INTER_RAT_HANDOVER_INFO_CTRL_STRU;

/******************************************************************************/
/*************************** ��Ϣ���������ݽṹ *******************************/
/******************************************************************************/
#define NAS_GMM_ENCODE_IE_MAX_NUM       (17)           /* GMM����attach��rau���ʱ��¼����IE�������� */

typedef struct
{
    VOS_UINT32                             ulOptionalIeMask;                        /* ��ѡIE��MASK                             */

    VOS_UINT8                              aucIeOffset[NAS_GMM_ENCODE_IE_MAX_NUM];                        /* IE��ƫ�����Ĵ洢�ռ�                     */
    VOS_UINT8                              aucReserved[3];
}GMM_MSG_RESOLVE_STRU;

/* ucRauCause */
#define GMM_RAU_FOR_NORMAL                  0
#define GMM_RAU_FOR_INTERSYSTEM             1
#define GMM_RAU_FOR_WAITSERVICE             2

/* ucT3312State */
#define GMM_T3312_NOT_TIMEOUT               0
#define GMM_T3312_TIMEOUT                   1
/* ucPowerOff */
#define GMM_POWER_OFF_NOT_RCV               0
#define GMM_POWER_OFF_RCV                   1
typedef struct
{
    VOS_UINT32          ulTimerRunMask;                 /* ��¼�л�֮ǰ��ʱ��״̬ */
    VOS_UINT32          ulTimerRunMaskEx;                 /* ��¼�л�֮ǰ��ʱ��״̬ */
    VOS_UINT32          ulTimerValue[GMM_TIMER_NUM];
    VOS_UINT8           ucPreState;                     /* ��¼�л�֮ǰGMM״̬ */
    VOS_UINT8           ucPreSrvState;                  /* ��¼�л�֮ǰGMM����״̬ */
    VOS_UINT8           ucPreRat;                       /* ��¼�л�ʱ���������ģʽ */
    VOS_UINT8           ucRauCause;                     /* ��¼RAUԭ��  */
    VOS_UINT8           ucSuspendCause;                 /* ��¼����ԭ��,ȡֵ��RRMM_SUSPEND_IND */
    VOS_UINT8           ucT3312State;                   /* ��¼�ڹ��������T3312�Ƿ�ʱ       */
    VOS_UINT8           ucNetModeChange;                /* ��¼��ϵͳ�ı�ʱ����ģʽ�ı������ */
    VOS_UINT8           ucPowerOff;                     /* ��¼�Ƿ����POWER OFF����          */

    VOS_UINT8           ucGetLteSecContext;             /* ��¼��ϵͳ�Ƿ��Ѿ���Lte��ȡ�˰�ȫ������,VOS_TRUE,�ѻ�ȡ,VOS_FALSEδ��ȡ */
}GMM_SUSPEND_CTRL_STRU;

/*******************************************************************************
 �ṹ��    : GMM_CALL_SUPPORT_CODEC_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��ǰ֧�ֵ�codec����,bitλ��1��ʾ��codec��Ч
*******************************************************************************/
typedef struct
{
    VOS_UINT16                          CodecType_GSMFR         :1;
    VOS_UINT16                          CodecType_GSMHR         :1;
    VOS_UINT16                          CodecType_GSMEFR        :1;
    VOS_UINT16                          CodecType_GSMFRAMR      :1;
    VOS_UINT16                          CodecType_GSMHRAMR      :1;
    VOS_UINT16                          CodecType_UMTSAMR       :1;
    VOS_UINT16                          CodecType_UMTSAMR2      :1;
    VOS_UINT16                          CodecType_TDMAEFR       :1;
    VOS_UINT16                          CodecType_PDCEFR        :1;
    VOS_UINT16                          CodecType_GSMFRAMRWB    :1;
    VOS_UINT16                          CodecType_UMTSAMRWB     :1;
    VOS_UINT16                          CodecType_OHR_AMR       :1;
    VOS_UINT16                          CodecType_OFR_AMR_WB    :1;
    VOS_UINT16                          CodecType_OHR_AMR_WB    :1;
    VOS_UINT16                          BandSpare               :2;
}GMM_CALL_SUPPORT_CODEC_STRU;

/*******************************************************************************
 �ṹ��    :MN_CALL_SUPPORT_CODEC_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��ǰ֧�ֵ�codec����,bitλ��1��ʾ��codec��Ч
*******************************************************************************/
typedef union
{
    GMM_CALL_SUPPORT_CODEC_STRU         stSupportCodec;
    VOS_UINT16                          usSupportCodec;
}GMM_CALL_SUPPORT_CODEC_UNION;

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif/* __cpluscplus */

#endif /* _GMMSTRUCTURE_H_ */

