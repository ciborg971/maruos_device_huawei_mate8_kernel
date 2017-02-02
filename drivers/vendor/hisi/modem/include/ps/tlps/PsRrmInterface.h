

#ifndef __PSRRMINTERFACE_H__
#define __PSRRMINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include  "vos.h"
#include  "PsTypeDef.h"

#if (VOS_OS_VER != VOS_WIN32)
#include  "vos_Id.h"
#endif

/*****************************************************************************
  #pragma pack(*)    �����ֽڶ��뷽ʽ
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 �궨��
*****************************************************************************/


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

enum PS_RRM_MSG_TYPE_ENUM
{
    ID_PS_RRM_RADIO_RESOURCE_APPLY_REQ                          = 0x0001,       /* _H2ASN_MsgChoice PS_RRM_RADIO_RESOURCE_APPLY_REQ_STRU */
    ID_RRM_PS_RADIO_RESOURCE_APPLY_CNF                          = 0x0002,       /* _H2ASN_MsgChoice RRM_PS_RADIO_RESOURCE_APPLY_CNF_STRU */

    ID_PS_RRM_RADIO_RESOURCE_RELEASE_IND                        = 0x0003,       /* _H2ASN_MsgChoice PS_RRM_RADIO_RESOURCE_RELEASE_IND_STRU */

    ID_RRM_PS_RADIO_RESOURCE_OCCUPY_REQ                         = 0x0004,       /* _H2ASN_MsgChoice RRM_PS_RADIO_RESOURCE_OCCUPY_REQ_STRU */
    ID_PS_RRM_RADIO_RESOURCE_OCCUPY_CNF                         = 0x0005,       /* _H2ASN_MsgChoice PS_RRM_RADIO_RESOURCE_OCCUPY_CNF_STRU */

    ID_PS_RRM_PROTECT_PS_IND                                    = 0x0006,       /* _H2ASN_MsgChoice PS_RRM_PROTECT_PS_IND_STRU */
    ID_PS_RRM_DEPROTECT_PS_IND                                  = 0x0007,       /* _H2ASN_MsgChoice PS_RRM_DEPROTECT_PS_IND_STRU */

    ID_PS_RRM_REGISTER_IND                                      = 0x0008,       /* _H2ASN_MsgChoice PS_RRM_REGISTER_IND_STRU */
    ID_PS_RRM_DEREGISTER_IND                                    = 0x0009,       /* _H2ASN_MsgChoice PS_RRM_DEREGISTER_IND_STRU */

    ID_RRM_PS_STATUS_IND                                        = 0x000a,       /* _H2ASN_MsgChoice RRM_PS_STATUS_IND_STRU */

    ID_RRM_PS_ERROR_IND                                         = 0x000b,       /* _H2ASN_MsgChoice RRM_PS_ERROR_IND_STRU */

    ID_RRM_PS_ABNORMAL_STATUS_IND                               = 0x000c,       /* _H2ASN_MsgChoice RRM_PS_ABNORMAL_STATUS_IND_STRU */

    ID_PS_RRM_PROTECT_SIGNAL_IND                                = 0x000d,       /* _H2ASN_MsgChoice PS_RRM_PROTECT_SIGNAL_IND_STRU */
    ID_PS_RRM_DEPROTECT_SIGNAL_IND                              = 0x000e,       /* _H2ASN_MsgChoice PS_RRM_DEPROTECT_SIGNAL_IND_STRU */

    ID_RRM_PS_USED_TASK_STATUS_IND                              = 0x000f,       /* _H2ASN_MsgChoice RRM_PS_USED_TASK_STATUS_IND_STRU */

    ID_PS_RRM_RAT_COMBINED_MODE_IND                             = 0x0010,       /* _H2ASN_MsgChoice PS_RRM_RAT_COMBINED_MODE_IND_STRU */
    ID_PS_RRM_MSG_TYPE_BUTT
};
typedef VOS_UINT32 PS_RRM_MSG_TYPE_ENUM_UINT32;



enum RRM_PS_URGENT_TYPE_ENUM
{
    RRM_PS_URGENT_TYPE_NO_URGENT                           = 0,                 /* ������ */
    RRM_PS_URGENT_TYPE_SHORT_OCCUPY                        = 1,                 /* �����Ľ������� */
    RRM_PS_URGENT_TYPE_URGENT                              = 2,                 /* �������� */
    RRM_PS_URGENT_TYPE_BUTT
};
typedef VOS_UINT8 RRM_PS_URGENT_TYPE_ENUM_UINT8;
enum RRM_PS_TASK_TYPE_ENUM
{
    /* ��ʼ״̬������ */
    RRM_PS_TASK_TYPE_NONE                           = 0,

    /* 1-100���ڶ���NAS���� */
    RRM_PS_TASK_TYPE_NAS_SEARCH                     = 1,

    /* 101-200���ڶ���GSM���� */
    RRM_PS_TASK_TYPE_GSM_CS_NORMAL                  = 101,
    RRM_PS_TASK_TYPE_GSM_CS_MO_CALL                 = 102,
    RRM_PS_TASK_TYPE_GSM_CS_MT_CALL                 = 103,
    RRM_PS_TASK_TYPE_GSM_CS_EMERGENCY_CALL          = 104,
    RRM_PS_TASK_TYPE_GSM_CS_NAS_SESSION             = 105,
    RRM_PS_TASK_TYPE_GSM_ATTACH                     = 106,
    RRM_PS_TASK_TYPE_GSM_CS_DETACH                  = 107,
    RRM_PS_TASK_TYPE_GSM_LAU                        = 108,
    RRM_PS_TASK_TYPE_GSM_RAU                        = 109,
    RRM_PS_TASK_TYPE_GSM_SS                         = 110,
    RRM_PS_TASK_TYPE_GSM_SMS                        = 111,
    RRM_PS_TASK_TYPE_GSM_NAS_SPEC_SEARCH            = 112,
    RRM_PS_TASK_TYPE_GSM_NAS_LIST_SEARCH            = 113,
    RRM_PS_TASK_TYPE_GSM_AS_SEARCH                  = 114,
    RRM_PS_TASK_TYPE_GSM_PS_NORMAL                  = 115,
    RRM_PS_TASK_TYPE_GSM_PS_PAGE_RSP                = 116,
    RRM_PS_TASK_TYPE_GSM_PS_CELL_UPDT               = 117,
    RRM_PS_TASK_TYPE_GSM_PS_MM_PROC                 = 118,
    RRM_PS_TASK_TYPE_GSM_PS_DETACH                  = 119,
    RRM_PS_TASK_TYPE_GSM_NAS_FAST_SPEC_SEARCH       = 120,
    RRM_PS_TASK_TYPE_GSM_PS_SUBSCRIB_TRAFFIC_CALL   = 121,              /* PDP �������� */

    /* 201-300���ڶ���WCDMA���� */
    RRM_PS_TASK_TYPE_WCDMA_NAS_SPEC_SEARCH          = 201,
    RRM_PS_TASK_TYPE_WCDMA_NAS_LIST_SEARCH          = 202,
    RRM_PS_TASK_TYPE_WCDMA_AS_SEARCH                = 203,
    RRM_PS_TASK_TYPE_WCDMA_PS_RRC_NORMAL            = 204,
    RRM_PS_TASK_TYPE_WCDMA_CS_RRC_NORMAL            = 205,
    RRM_PS_TASK_TYPE_WCDMA_CS_RRC_HIGH              = 206,
    RRM_PS_TASK_TYPE_WCDMA_CS_MO_NORMAL_CALL        = 207,
    RRM_PS_TASK_TYPE_WCDMA_CS_MO_EMERGENCY_CALL     = 208,
    RRM_PS_TASK_TYPE_WCDMA_CS_MO_SS                 = 209,
    RRM_PS_TASK_TYPE_WCDMA_CS_MO_SMS                = 210,
    RRM_PS_TASK_TYPE_WCDMA_CS_MT_NORMAL_CALL        = 211,
    RRM_PS_TASK_TYPE_WCDMA_CS_MT_EMERGENCY_CALLBACK = 212,
    RRM_PS_TASK_TYPE_WCDMA_CS_MT_SS                 = 213,
    RRM_PS_TASK_TYPE_WCDMA_CS_MT_SMS                = 214,
    RRM_PS_TASK_TYPE_WCDMA_CS_LAU                   = 215,
    RRM_PS_TASK_TYPE_WCDMA_CS_DETACH                = 216,
    RRM_PS_TASK_TYPE_WCDMA_CS_MO_NORMAL_CSFB        = 217,
    RRM_PS_TASK_TYPE_WCDMA_CS_MO_EMERGENCY_CSFB     = 218,
    RRM_PS_TASK_TYPE_WCDMA_CS_MT_CSFB               = 219,
    RRM_PS_TASK_TYPE_WCDMA_PS_CONVERSAT_CALL        = 220,
    RRM_PS_TASK_TYPE_WCDMA_PS_STREAM_CALL           = 221,
    RRM_PS_TASK_TYPE_WCDMA_PS_INTERACT_CALL         = 222,
    RRM_PS_TASK_TYPE_WCDMA_PS_BACKGROUND_CALL       = 223,
    RRM_PS_TASK_TYPE_WCDMA_PS_SUBSCRIB_TRAFFIC_CALL = 224,
    RRM_PS_TASK_TYPE_WCDMA_PS_MO_SMS                = 225,
    RRM_PS_TASK_TYPE_WCDMA_PS_MT_SMS                = 226,
    RRM_PS_TASK_TYPE_WCDMA_PS_ATTACH                = 227,
    RRM_PS_TASK_TYPE_WCDMA_PS_RAU                   = 228,
    RRM_PS_TASK_TYPE_WCDMA_PS_DETACH                = 229,
    RRM_PS_TASK_TYPE_WCDMA_NAS_FAST_SPEC_SEARCH     = 230,

    /* 301-400���ڶ���TD-SCDMA���� */
    RRM_PS_TASK_TYPE_TRRC_CS_PAGING                 = 301,
    RRM_PS_TASK_TYPE_TRRC_CS_CONNECTION             = 302,
    RRM_PS_TASK_TYPE_TRRC_PS_CONNECTION             = 303,
    RRM_PS_TASK_TYPE_TRRC_IRAT                      = 304,
    RRM_PS_TASK_TYPE_TDS_AS_SEARCH                  = 305,
    RRM_PS_TASK_TYPE_TDS_NAS_SPEC_SEARCH            = 306,
    RRM_PS_TASK_TYPE_TDS_NAS_FAST_SPEC_SEARCH       = 307,
    RRM_PS_TASK_TYPE_TDS_NAS_LIST_SEARCH            = 308,
    RRM_PS_TASK_TYPE_TDS_CS_MO_NORMAL_CALL          = 309,
    RRM_PS_TASK_TYPE_TDS_CS_MO_EMERGENCY_CALL       = 310,
    RRM_PS_TASK_TYPE_TDS_CS_MO_SS                   = 311,
    RRM_PS_TASK_TYPE_TDS_CS_MO_SMS                  = 312,
    RRM_PS_TASK_TYPE_TDS_CS_MT_NORMAL_CALL          = 313,
    RRM_PS_TASK_TYPE_TDS_CS_MT_EMERGENCY_CALLBACK   = 314,
    RRM_PS_TASK_TYPE_TDS_CS_MT_SS                   = 315,
    RRM_PS_TASK_TYPE_TDS_CS_MT_SMS                  = 316,
    RRM_PS_TASK_TYPE_TDS_CS_LAU                     = 317,
    RRM_PS_TASK_TYPE_TDS_CS_DETACH                  = 318,
    RRM_PS_TASK_TYPE_TDS_CS_MO_NORMAL_CSFB          = 319,
    RRM_PS_TASK_TYPE_TDS_CS_MO_EMERGENCY_CSFB       = 320,
    RRM_PS_TASK_TYPE_TDS_CS_MT_CSFB                 = 321,
    RRM_PS_TASK_TYPE_TDS_PS_CONVERSAT_CALL          = 322,
    RRM_PS_TASK_TYPE_TDS_PS_STREAM_CALL             = 323,
    RRM_PS_TASK_TYPE_TDS_PS_INTERACT_CALL           = 324,
    RRM_PS_TASK_TYPE_TDS_PS_BACKGROUND_CALL         = 325,
    RRM_PS_TASK_TYPE_TDS_PS_SUBSCRIB_TRAFFIC_CALL   = 326,
    RRM_PS_TASK_TYPE_TDS_PS_MO_SMS                  = 327,
    RRM_PS_TASK_TYPE_TDS_PS_MT_SMS                  = 328,
    RRM_PS_TASK_TYPE_TDS_PS_ATTACH                  = 329,
    RRM_PS_TASK_TYPE_TDS_PS_RAU                     = 330,
    RRM_PS_TASK_TYPE_TDS_PS_DETACH                  = 331,

    /* 401-500���ڶ���LTE���� */
    RRM_PS_TASK_TYPE_LRRC_PS_PAGING                 = 401,
    RRM_PS_TASK_TYPE_LRRC_PS_CONNECTION             = 402,
    RRM_PS_TASK_TYPE_LRRC_IRAT                      = 403,
    RRM_PS_TASK_TYPE_LRRC_ETWS                      = 404,
    RRM_PS_TASK_TYPE_LRRC_CMAS                      = 405,
    RRM_PS_TASK_TYPE_LTE_AS_SEARCH                  = 406,
    RRM_PS_TASK_TYPE_LTE_NAS_SPEC_SEARCH            = 407,
    RRM_PS_TASK_TYPE_LTE_NAS_FAST_SPEC_SEARCH       = 408,
    RRM_PS_TASK_TYPE_LTE_NAS_LIST_SEARCH            = 409,
    RRM_PS_TASK_TYPE_LTE_MO_NORMAL_CALL             = 410,
    RRM_PS_TASK_TYPE_LTE_MT_NORMAL_CALL             = 411,
    RRM_PS_TASK_TYPE_LTE_MO_EMERGENCY_CALL          = 412,
    RRM_PS_TASK_TYPE_LTE_PS_MO_SS                   = 413,
    RRM_PS_TASK_TYPE_LTE_PS_MT_SS                   = 414,
    RRM_PS_TASK_TYPE_LTE_CS_MO_NORMAL_CSFB          = 415,
    RRM_PS_TASK_TYPE_LTE_CS_MO_EMERGENCY_CSFB       = 416,
    RRM_PS_TASK_TYPE_LTE_CS_MT_CSFB                 = 417,
    RRM_PS_TASK_TYPE_LTE_PS_CONVERSAT_CALL          = 418,
    RRM_PS_TASK_TYPE_LTE_PS_STREAM_CALL             = 419,
    RRM_PS_TASK_TYPE_LTE_PS_INTERACT_CALL           = 420,
    RRM_PS_TASK_TYPE_LTE_PS_BACKGROUND_CALL         = 421,
    RRM_PS_TASK_TYPE_LTE_PS_SUBSCRIB_TRAFFIC_CALL   = 422,
    RRM_PS_TASK_TYPE_LTE_PS_MO_SMS                  = 423,
    RRM_PS_TASK_TYPE_LTE_PS_MT_SMS                  = 424,
    RRM_PS_TASK_TYPE_LTE_PS_ATTACH                  = 425,
    RRM_PS_TASK_TYPE_LTE_PS_LOW_TAU                 = 426,
    RRM_PS_TASK_TYPE_LTE_PS_HIGH_TAU                = 427,
    RRM_PS_TASK_TYPE_LTE_PS_DETACH                  = 428,
    RRM_PS_TASK_TYPE_LTE_PS_ESM                     = 429,
    RRM_PS_TASK_TYPE_LTE_IMS_MO_NORMAL_CALL         = 430,
    RRM_PS_TASK_TYPE_LTE_IMS_MT_NORMAL_CALL         = 431,
    RRM_PS_TASK_TYPE_LTE_IMS_EMERGENCY_CALL         = 432,
    RRM_PS_TASK_TYPE_LTE_IMS_MO_SS                  = 433,
    RRM_PS_TASK_TYPE_LTE_IMS_MT_SS                  = 434,
    RRM_PS_TASK_TYPE_LTE_IMS_MO_SMS                 = 435,
    RRM_PS_TASK_TYPE_LTE_IMS_MT_SMS                 = 436,
    RRM_PS_TASK_TYPE_LTE_IMS_REGISTER               = 437,

    /* 501-600���ڶ���1x,HRPD���� */
    RRM_PS_TASK_TYPE_1X_NETWORK_SEARCH              = 501,
    RRM_PS_TASK_TYPE_1X_REGISTER                    = 502,
    RRM_PS_TASK_TYPE_1X_CS_CALL                     = 503,
    RRM_PS_TASK_TYPE_1X_PS_CALL                     = 504,
    RRM_PS_TASK_TYPE_1X_SIGNAL                      = 505,
    RRM_PS_TASK_TYPE_1X_SMS                         = 506,

    RRM_PS_TASK_TYPE_HRPD_NETWORK_SEARCH            = 521,
    RRM_PS_TASK_TYPE_HRPD_PS_NORMAL                 = 522,
    RRM_PS_TASK_TYPE_HRPD_LU                        = 523,
    RRM_PS_TASK_TYPE_HRPD_UATI                      = 524,
    RRM_PS_TASK_TYPE_HRPD_SESSION_CLOSE             = 525,
    RRM_PS_TASK_TYPE_HRPD_ATTACH                    = 526,
    RRM_PS_TASK_TYPE_HRPD_PDN_CONN                  = 527,
    RRM_PS_TASK_TYPE_HRPD_PDN_DISCONN               = 528,
    RRM_PS_TASK_TYPE_HRPD_DETACH                    = 529,
    RRM_PS_TASK_TYPE_HRPD_SESSION_NEG               = 530,
    RRM_PS_TASK_TYPE_HRPD_PS_CONNECTION             = 531,
    RRM_PS_TASK_TYPE_HRPD_SIGNAL                    = 532,
    RRM_PS_TASK_TYPE_HRPD_MO_KEEP_ALIVE             = 533,
    RRM_PS_TASK_TYPE_HRPD_MT_KEEP_ALIVE             = 534,
    RRM_PS_TASK_TYPE_HRPD_HARD_ID                   = 535,

    RRM_PS_TASK_TYPE_BUTT
};
typedef VOS_UINT16 RRM_PS_TASK_TYPE_ENUM_UINT16;


enum PS_RRM_RESULT_ENUM
{
    PS_RRM_RESULT_SUCCESS               = 0,
    PS_RRM_RESULT_FAIL_OTHER_ERROR      = 1,
    PS_RRM_RESULT_BUTT
};
typedef VOS_UINT8 PS_RRM_RESULT_ENUM_UINT8;



enum RRM_PS_CHECK_MSG_RESULT_ENUM
{
    RRM_PS_CHECK_MSG_RESULT_OK                       = 0,
    RRM_PS_CHECK_MSG_RESULT_DSDS_NOT_SUPPORT_ERROR   = 1,
    RRM_PS_CHECK_MSG_RESULT_PARA_ERROR               = 2,
    RRM_PS_CHECK_MSG_RESULT_RESOURCE_VALUE_ERROR     = 3,
    RRM_PS_CHECK_MSG_RESULT_BUTT
};
typedef VOS_UINT8 RRM_PS_CHECK_MSG_RESULT_ENUM_UINT8;


enum PS_RRM_SIGNAL_READY_ENUM
{
    PS_RRM_SIGNAL_NOT_READY         = 0,
    PS_RRM_SIGNAL_READY             = 1,
    PS_RRM_SIGNAL_DSDS_NOT_SUPPROT  = 2,
    PS_RRM_SIGNAL_READY_BUTT
};
typedef VOS_UINT8 PS_RRM_SIGNAL_READY_ENUM_UINT8;


enum PS_RRM_RF_SHARED_ENUM
{
    PS_RRM_RF_NOT_SHARED                = 0,
    PS_RRM_RF_SHARED                    = 1,
    PS_RRM_RF_SHARED_DSDS_NOT_SUPPROT   = 2,
    PS_RRM_RF_SHARED_BUTT
};
typedef VOS_UINT8 PS_RRM_RF_SHARED_ENUM_UINT8;


enum PS_RRM_RF_AVAILABLE_ENUM
{
    PS_RRM_RF_NOT_AVAILABLE                 = 0,
    PS_RRM_RF_AVAILABLE                     = 1,
    PS_RRM_RF_AVAILABLE_DSDS_NOT_SUPPROT    = 2,
    PS_RRM_RF_AVAILABLE_BUTT
};
typedef VOS_UINT8 PS_RRM_RF_AVAILABLE_ENUM_UINT8;


enum PS_RRM_IS_PREEMPTED_ENUM
{
    PS_RRM_NOT_PREEMPTED                = 0,
    PS_RRM_COULD_PREEMPTED              = 1,
    PS_RRM_PREEMPTED_DSDS_NOT_SUPPROT   = 2,
    PS_RRM_PREEMPTED_BUTT
};
typedef VOS_UINT8 PS_RRM_IS_PREEMPTED_ENUM_UINT8;


enum PS_RRM_RAT_COMBINED_MODE_ENUM
{
    PS_RRM_RAT_COMBINED_MODE_CL                 = 0, /* ��ǰ֧��1X����EVDO */
    PS_RRM_RAT_COMBINED_MODE_GUL                = 1, /* ��ǰ֧��GUL,������֧��LTE����� */
    PS_RRM_RAT_COMBINED_MODE_BUTT
};
typedef VOS_UINT8 PS_RRM_RAT_COMBINED_MODE_ENUM_UINT8;


/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/

/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/

/*****************************************************************************
  7 STRUCT����
*****************************************************************************/

typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;        /* ��Ϣͷ */ /*_H2ASN_Skip*/
    MODEM_ID_ENUM_UINT16                enModemId;          /* _H2ASN_Replace VOS_UINT16 enModemId; */
    RRM_PS_TASK_TYPE_ENUM_UINT16        enTaskType;
    VOS_RATMODE_ENUM_UINT32             enRatType;          /* ��Ҫʹ����Ƶ��Դ��ģʽ���������ϵͳ����������дĿ��ģʽ */ /* _H2ASN_Replace VOS_UINT32 enRatType; */
}PS_RRM_RADIO_RESOURCE_APPLY_REQ_STRU;
typedef struct
{
    MSG_HEADER_STRU                    stMsgHeader;         /* ��Ϣͷ */ /*_H2ASN_Skip*/
    RRM_PS_TASK_TYPE_ENUM_UINT16       enTaskType;
    PS_RRM_RESULT_ENUM_UINT8           enResult;
    VOS_UINT8                          aucReserved[1];
} RRM_PS_RADIO_RESOURCE_APPLY_CNF_STRU;
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;        /* ��Ϣͷ */ /*_H2ASN_Skip*/
    MODEM_ID_ENUM_UINT16                enModemId;          /* _H2ASN_Replace VOS_UINT16 enModemId; */
    RRM_PS_TASK_TYPE_ENUM_UINT16        enTaskType;         /* �ͷŵ�������Դ���� */
    PS_BOOL_ENUM_UINT8                  enRelAllFlag;       /* �ͷű�PID�������������Դ���� */
    VOS_UINT8                           aucReserved[3];
    VOS_RATMODE_ENUM_UINT32             enRatType;          /* �ͷ���Ƶ��Դ��ģʽ���������ϵͳ����������дĿ��ģʽ */ /* _H2ASN_Replace VOS_UINT32 enRatType; */
    VOS_UINT32                          ulRelDelaytimer;    /* �ӳ��ͷ���Ƶ��Դ��ʱ�䣬��λ:ms,
                                                               ���ӳ�ʱ��ֵ����Ϊ0������ӳ�ֵΪ10000ms(10s),
                                                               ֻ��Ծ��������ҵ�ǰ��Դ���ڱ�������ʹ�ã��ͷ���Դʱ���ӳ�ʱ�����Ч��
                                                               ���enRelAllFlag = PS_TRUE��Ч�� ���ӳ�ʱ�䲻��Ч */
}PS_RRM_RADIO_RESOURCE_RELEASE_IND_STRU;


typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;        /* ��Ϣͷ */ /*_H2ASN_Skip*/
    RRM_PS_URGENT_TYPE_ENUM_UINT8       enUrgentType;       /* ��ռ�Ľ������� */
    VOS_UINT8                           aucReserved[3];
} RRM_PS_RADIO_RESOURCE_OCCUPY_REQ_STRU;


typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;        /* ��Ϣͷ */ /*_H2ASN_Skip*/
    VOS_UINT8                           aucReserved[4];
} PS_RRM_RADIO_RESOURCE_OCCUPY_CNF_STRU;
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;        /* ��Ϣͷ */ /*_H2ASN_Skip*/
    MODEM_ID_ENUM_UINT16                enModemId;          /* _H2ASN_Replace VOS_UINT16 enModemId; */
    VOS_UINT8                           aucReserved[2];
} PS_RRM_PROTECT_PS_IND_STRU;


typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;        /* ��Ϣͷ */ /*_H2ASN_Skip*/
    MODEM_ID_ENUM_UINT16                enModemId;          /* _H2ASN_Replace VOS_UINT16 enModemId; */
    VOS_UINT8                           aucReserved[2];
} PS_RRM_DEPROTECT_PS_IND_STRU;


typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;        /* ��Ϣͷ */ /*_H2ASN_Skip*/
    MODEM_ID_ENUM_UINT16                enModemId;          /* _H2ASN_Replace VOS_UINT16 enModemId; */
    RRM_PS_TASK_TYPE_ENUM_UINT16        enTaskType;         /* ��Ч������ע�� */
    VOS_RATMODE_ENUM_UINT32             enRatType;          /* _H2ASN_Replace VOS_UINT32 enRatType; */
} PS_RRM_REGISTER_IND_STRU;


typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;        /* ��Ϣͷ */ /*_H2ASN_Skip*/
    MODEM_ID_ENUM_UINT16                enModemId;          /* _H2ASN_Replace VOS_UINT16 enModemId; */
    RRM_PS_TASK_TYPE_ENUM_UINT16        enTaskType;         /* ��Ч����ȥע�� */
    VOS_RATMODE_ENUM_UINT32             enRatType;          /* _H2ASN_Replace VOS_UINT32 enRatType; */
} PS_RRM_DEREGISTER_IND_STRU;



typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;        /* ��Ϣͷ */ /*_H2ASN_Skip*/
    RRM_PS_TASK_TYPE_ENUM_UINT16        enTaskType;
    VOS_UINT8                           aucReserved[2];
    VOS_RATMODE_ENUM_UINT32             enRatType;          /* _H2ASN_Replace VOS_UINT32 enRatType; */
} RRM_PS_STATUS_IND_STRU;



typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;        /* ��Ϣͷ */ /*_H2ASN_Skip*/
    RRM_PS_CHECK_MSG_RESULT_ENUM_UINT8  enCheckMsgRlst;
    VOS_UINT8                           aucReserved[3];
} RRM_PS_ERROR_IND_STRU;
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;        /* ��Ϣͷ */ /*_H2ASN_Skip*/
    VOS_UINT8                           aucReserved[4];
} RRM_PS_ABNORMAL_STATUS_IND_STRU;
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;        /* ��Ϣͷ */ /*_H2ASN_Skip*/
    MODEM_ID_ENUM_UINT16                enModemId;          /* _H2ASN_Replace VOS_UINT16 enModemId; */
    VOS_UINT8                           aucReserved[2];
    VOS_RATMODE_ENUM_UINT32             enRatType;          /* ��Ҫʹ����Ƶ��Դ��ģʽ���������ϵͳ����������дĿ��ģʽ */ /* _H2ASN_Replace VOS_UINT32 enRatType; */
} PS_RRM_PROTECT_SIGNAL_IND_STRU;
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;         /* ��Ϣͷ */ /*_H2ASN_Skip*/
    MODEM_ID_ENUM_UINT16                enModemId;           /* _H2ASN_Replace VOS_UINT16 enModemId; */
    VOS_UINT8                           aucReserved[2];
    VOS_RATMODE_ENUM_UINT32             enRatType;           /* ��Ҫʹ����Ƶ��Դ��ģʽ���������ϵͳ����������дĿ��ģʽ */ /* _H2ASN_Replace VOS_UINT32 enRatType; */
} PS_RRM_DEPROTECT_SIGNAL_IND_STRU;
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;        /* ��Ϣͷ */ /*_H2ASN_Skip*/
    PS_BOOL_ENUM_UINT8                  enResourceUsedFlag; /* ��Դ�Ƿ�����ʹ�� */
    PS_BOOL_ENUM_UINT8                  enNotStealFlag;     /* ��ǰ����ʹ����Դ���������Ƿ���ڲ�����͵֡������ */
    MODEM_ID_ENUM_UINT16                enModemId;          /* _H2ASN_Replace VOS_UINT16 enModemId; */
} RRM_PS_USED_TASK_STATUS_IND_STRU;


typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;        /* ��Ϣͷ */ /*_H2ASN_Skip*/
    PS_RRM_RAT_COMBINED_MODE_ENUM_UINT8 enRatCombMode;
    VOS_UINT8                           aucReserved[1];
    MODEM_ID_ENUM_UINT16                enModemId;          /* _H2ASN_Replace VOS_UINT16 enModemId; */
} PS_RRM_RAT_COMBINED_MODE_IND_STRU;


/*****************************************************************************
  8 UNION����
*****************************************************************************/

/*****************************************************************************
  9 OTHERS����
*****************************************************************************/

/*****************************************************************************
  H2ASN������Ϣ�ṹ����
*****************************************************************************/

/*****************************************************************************
 �ṹ��    : PS_RRM_MSG_DATA
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PS_RRM_MSG_DATA���ݽṹ����������ASN�ļ�
*****************************************************************************/
typedef struct
{
    PS_RRM_MSG_TYPE_ENUM_UINT32         enMsgId;            /*_H2ASN_MsgChoice_Export PS_RRM_MSG_TYPE_ENUM_UINT32 */
    VOS_UINT8                           aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          PS_RRM_MSG_TYPE_ENUM_UINT32
    ****************************************************************************/
}PS_RRM_MSG_DATA;

/*_H2ASN_Length UINT32*/

/*****************************************************************************
 �ṹ��    : PsRrmInterface_MSG
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PsRrmInterface_MSG���ݽṹ,��������ASN�ļ�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    PS_RRM_MSG_DATA                     stMsgData;
}PsRrmInterface_MSG;

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
/* ������Դ���ɱ���ռ */
extern PS_RRM_SIGNAL_READY_ENUM_UINT8 RRM_DisableRfResourceOccupy
(
   VOS_UINT32                           ulPidValue,
   MODEM_ID_ENUM_UINT16                 enModemId,
   VOS_RATMODE_ENUM_UINT32              enRatType
);

/* ������Դ���Ա���ռ */
extern VOS_VOID RRM_EnableRfResourceOccupy
(
   VOS_UINT32                           ulPidValue,
   MODEM_ID_ENUM_UINT16                 enModemId,
   VOS_RATMODE_ENUM_UINT32              enRatType
);


/* ��Դ�Ƿ���� */
extern PS_RRM_RF_AVAILABLE_ENUM_UINT8 RRM_RfResourceIsAvailable
(
   MODEM_ID_ENUM_UINT16                 enModemId,
   VOS_RATMODE_ENUM_UINT32              enRatType,
   VOS_UINT32                          *pulStartingTimer
);


/* ��̽�¿���Դ�Ƿ�ɵõ� */
extern PS_RRM_IS_PREEMPTED_ENUM_UINT8 RRM_RfResourceIsPreempted
(
   MODEM_ID_ENUM_UINT16                 enModemId,
   VOS_RATMODE_ENUM_UINT32              enRatType,
   RRM_PS_TASK_TYPE_ENUM_UINT16         enTaskType
);


/* ��Դ�Ƿ��ǹ���� */
extern PS_RRM_RF_SHARED_ENUM_UINT8 RRM_RfResourceIsShared
(
   MODEM_ID_ENUM_UINT16                 enModemId,
   VOS_RATMODE_ENUM_UINT32              enRatType
);

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/


/*****************************************************************************
  9 OTHERS
*****************************************************************************/
//#endif




#if (VOS_OS_VER != VOS_WIN32)
 #pragma pack()
#else
 #pragma pack(pop)
#endif

#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif

#endif /* end of PsRrmInterface.h */


