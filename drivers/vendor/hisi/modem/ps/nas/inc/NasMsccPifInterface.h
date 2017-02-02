
#ifndef _NAS_MSCC_PIF_INTERFACE_H_
#define _NAS_MSCC_PIF_INTERFACE_H_

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "PsTypeDef.h"
#include "TafTypeDef.h"
#include "TafNvInterface.h"
#include "NasNvInterface.h"
#include "ComInterface.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define NAS_MSCC_PIF_CELL_MAX_NUM            (8)                                /* С��������� */
#define NAS_MSCC_PIF_MAX_PLMN_CNT            (37)

#define NAS_MSCC_PIF_MAX_CPOL_PLMN_CNT       (12)

#if (FEATURE_ON == FEATURE_LTE)
#define NAS_MSCC_PIF_MAX_RAT_NUM             (3)                                /* ��ǰ֧�ֵĽ��뼼������ */
#else
#define NAS_MSCC_PIF_MAX_RAT_NUM             (2)                                /* ��ǰ֧�ֵ�GU���뼼������ */
#endif

#define NAS_MSCC_PIF_CAUSE_NULL              (0)

#define NAS_MSCC_PIF_NET_SCAN_MAX_FREQ_NUM   (20)

#define NAS_MSCC_PIF_MAX_EQUPLMN_NUM         (18)                               /* ��Ч��PLMN�������� */
#define NAS_MSCC_PIF_TDS_ARFCN_MAX_NUM       (9)                                /* TDDƵ���б������� */
#define NAS_MSCC_PIF_LTE_ARFCN_MAX_NUM       (8)                                /* LTEƵ���б������� */


#define NAS_MSCC_PIF_REG_MAX_PLMN_NUM        (8)
#define NAS_MSCC_PIF_REG_MAX_CELL_NUM        (8)

#define NAS_MSCC_PIF_INVALID_MNC             (0xffff)

#define NAS_MSCC_PIF_MAX_CFPLMN_NUM          (20)

#define NAS_MSCC_PIF_MAX_OPER_LONG_NAME_LEN                 (100)               /* spn ����ucs2����ʱ��Ҫ�ĳ���Ϊ32�����һ��\0 ���뵽36λ,��Ϊ�����39��long name ,������40*/
#define NAS_MSCC_PIF_MAX_OPER_SHORT_NAME_LEN                (100)               /* spn ����ucs2����ʱ��Ҫ�ĳ���Ϊ32 ,���һ��\0 ���뵽36λ */
#define NAS_MSCC_PIF_MAX_USER_OPLMN_VERSION_LEN             (8)                 /* �û����õ�OPLMN�汾����󳤶� */
#define NAS_MSCC_PIF_MAX_GROUP_CFG_OPLMN_DATA_LEN           (250)               /* ��������OPLMN������ֽ���*/

#define NAS_MSCC_PIF_SCELL_MEAS_TYPE_NONE                   (0x00)              /* AT��ѯ�ϱ�  */
#define NAS_MSCC_PIF_SCELL_MEAS_TYPE_RXLEV                  (0x01)              /* RXLEV�仯�������ϱ� */
#define NAS_MSCC_PIF_SCELL_MEAS_TYPE_RXQUALITY              (0x02)              /* RXQUALITY�仯�������ϱ� */
#define NAS_MSCC_PIF_SCELL_MEAS_TYPE_CELLID                 (0x04)              /* CELL ID�仯�������ϱ� */

#define NAS_MSCC_PIF_MAX_PLMN_NUM                           (256)

#define NAS_MSCC_PIF_MAX_HIGH_QUALITY_PLMN_NUM              (16)
#define NAS_MSCC_PIF_MAX_LOW_QUALITY_PLMN_NUM               (16)

#define NAS_MSCC_PIF_MAX_EHPLMN_NUM                         (16)                    /* EHPLMN���ĸ��� */
#define NAS_MSCC_PIF_MAX_USERPLMN_NUM                       (100)                   /* USERPLMN���ĸ��� */
#define NAS_MSCC_PIF_MAX_OPERPLMN_NUM                       (256)                   /* OPERPLMN���ĸ��� */


/* Modified by l00301449 for CDMA Iteration 15, 2015-5-16, begin */
#define NAS_MSCC_PIF_SRV_ACQ_RAT_NUM_MAX                    (3)
/* Modified by l00301449 for CDMA Iteration 15, 2015-5-16, end */

/* Added by h00313353 for Iteration 17, 2015-7-20, begin */
#define NAS_MSCC_PIF_MAX_WHITE_LOCK_SID_NUM                 (20)
/* Added by h00313353 for Iteration 17, 2015-7-20, end */

#define NAS_MSCC_PIF_MAX_SRCHED_LAI_NUM                     (18)

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/


enum NAS_MSCC_PIF_CARD_STATUS_ENUM
{
    NAS_MSCC_PIF_CARD_STATUS_SIM_PRESENT      = 0,                              /* sim present */
    NAS_MSCC_PIF_CARD_STATUS_USIM_PRESENT     = 1,                              /* usim present */
    NAS_MSCC_PIF_CARD_STATUS_UIM_PRESENT      = 2,
    NAS_MSCC_PIF_CARD_STATUS_CSIM_PRESENT     = 3,
    NAS_MSCC_PIF_CARD_STATUS_ABSENT           = 4,                              /* card absent */
    NAS_MSCC_PIF_CARD_STATUS_BUTT
};
typedef VOS_UINT8 NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8;
enum NAS_MSCC_PIF_BAND_CLASS_ENUM
{
    NAS_MSCC_PIF_BAND_CLASS_TYPE_0                              = 0,    /* 800 MHz cellular band */

    NAS_MSCC_PIF_BAND_CLASS_TYPE_1                              = 1,    /* 1.8 to 2.0 GHz PCS band */

    NAS_MSCC_PIF_BAND_CLASS_TYPE_2                              = 2,    /* 872 to 960 MHz TACS band */

    NAS_MSCC_PIF_BAND_CLASS_TYPE_3                              = 3,    /* 832 to 925 MHz JTACS band */

    NAS_MSCC_PIF_BAND_CLASS_TYPE_4                              = 4,    /* 1.75 to 1.87 GHz Korean PCS band */

    NAS_MSCC_PIF_BAND_CLASS_TYPE_5                              = 5,    /* 450 MHz NMT band */

    NAS_MSCC_PIF_BAND_CLASS_TYPE_6                              = 6,    /* 2 GHz IMT-2000 band */

    NAS_MSCC_PIF_BAND_CLASS_TYPE_7                              = 7,    /* 700 MHz band */

    NAS_MSCC_PIF_BAND_CLASS_TYPE_8                              = 8,    /* 1800 MHz band */

    NAS_MSCC_PIF_BAND_CLASS_TYPE_9                              = 9,    /* 900 MHz band */

    NAS_MSCC_PIF_BAND_CLASS_TYPE_10                             = 10,   /* Secondary 800 MHz band */

    NAS_MSCC_PIF_BAND_CLASS_TYPE_11                             = 11,   /* 400 MHz European PAMR band */

    NAS_MSCC_PIF_BAND_CLASS_TYPE_12                             = 12,   /* 800 MHz PAMR band */

    NAS_MSCC_PIF_BAND_CLASS_TYPE_13                             = 13,   /* 2.5 GHz IMT-2000 Extension Band */

    NAS_MSCC_PIF_BAND_CLASS_TYPE_14                             = 14,   /* US PCS 1.9GHz Band */

    NAS_MSCC_PIF_BAND_CLASS_TYPE_15                             = 15,   /* AWS Band */

    NAS_MSCC_PIF_BAND_CLASS_TYPE_16                             = 16,   /* US 2.5GHz Band */

    NAS_MSCC_PIF_BAND_CLASS_TYPE_17                             = 17,   /* US 2.5GHz Forward Link Only Band */

    NAS_MSCC_PIF_BAND_CLASS_TYPE_18                             = 18,   /* 700 MHz Public Safety Band */

    NAS_MSCC_PIF_BAND_CLASS_TYPE_19                             = 19,   /* Lower 700 MHz Band */

    NAS_MSCC_PIF_BAND_CLASS_TYPE_20                             = 20,   /* L-Band */

    NAS_MSCC_PIF_BAND_CLASS_TYPE_21                             = 21,   /* S-Band */

    NAS_MSCC_PIF_BAND_CLASS_TYPE_31                             = 31,   /* Wildcard Band Class */

    NAS_MSCC_PIF_BAND_CLASS_BUTT
};
typedef VOS_UINT16 NAS_MSCC_PIF_BAND_CLASS_ENUM_UINT16;
enum NAS_MSCC_PIF_PREF_NEG_SYS_ENUM
{
    NAS_MSCC_PIF_PREF_NEG_SYS_NEG                               = 0, /* This field is set to '0' if the mobile station is
                                                                                    not allowed to operate on the system associated
                                                                                    with this record */
    NAS_MSCC_PIF_PREF_NEG_SYS_PREF                              = 1, /* This field is set to ��1�� if the mobile station
                                                                                    is allowed to operate on the system associated with
                                                                                    this record */
    NAS_MSCC_PIF_PREF_NEG_SYS_BUTT
};
typedef VOS_UINT8 NAS_MSCC_PIF_PREF_NEG_SYS_ENUM_UINT8;



enum NAS_MSCC_PIF_PLMN_STATUS_ENUM
{
    NAS_MSCC_PIF_PLMN_STATUS_UNKNOW           = 0,                                    /* ��ǰ����״̬δ֪ */
    NAS_MSCC_PIF_PLMN_STATUS_AVAILIBLE        = 1,                                    /* ��ǰ������� */
    NAS_MSCC_PIF_PLMN_STATUS_CURRENT          = 2,                                    /* ��ǰ������ע�� */
    NAS_MSCC_PIF_PLMN_STATUS_FORBIDDEN        = 3,                                    /* ��ǰ�����ֹ */
    NAS_MSCC_PIF_PLMN_STATUS_BUTT
};
typedef VOS_UINT8 NAS_MSCC_PIF_PLMN_STATUS_ENUM_UINT8;


enum NAS_MSCC_PIF_NET_RAT_TYPE_ENUM
{
    NAS_MSCC_PIF_NET_RAT_TYPE_GSM,           /* GSM���뼼�� */
    NAS_MSCC_PIF_NET_RAT_TYPE_WCDMA,         /* WCDMA���뼼�� */
    NAS_MSCC_PIF_NET_RAT_TYPE_LTE,           /* LTE���뼼�� */
    NAS_MSCC_PIF_NET_RAT_TYPE_1X,            /* 1X���뼼�� */
    NAS_MSCC_PIF_NET_RAT_TYPE_HRPD,          /* 1X���뼼�� */
    NAS_MSCC_PIF_NET_RAT_TYPE_BUTT           /* ��Ч�Ľ��뼼�� */
};
typedef VOS_UINT8 NAS_MSCC_PIF_NET_RAT_TYPE_ENUM_UINT8;


enum NAS_MSCC_PIF_REG_STATE_ENUM
{
    NAS_MSCC_PIF_REG_NOT_REGISTERED_NOT_SEARCH,      /* δע��δ���� */
    NAS_MSCC_PIF_REG_REGISTERED_HOME_NETWORK,        /* ע�ᣬע���� HOME PLMN */
    NAS_MSCC_PIF_REG_NOT_REGISTERED_SEARCHING,       /* δע�ᣬ��������PLMN�������ڸ��Ź��� */
    NAS_MSCC_PIF_REG_REGISTERED_DENIED,              /* ע�ᱻ�ܾ�����ǰ�û�����������ע�ᣬ�������񱻽�ֹ */
    NAS_MSCC_PIF_REG_UNKNOWN,                        /* ������� */
    NAS_MSCC_PIF_REG_REGISTERED_ROAM,                /* ע�ᣬע���ڷ� HOME PLMN */
    NAS_MSCC_PIF_REG_STATUS_BUTT
};
typedef VOS_UINT8 NAS_MSCC_PIF_REG_STATE_ENUM_UINT8;


enum NAS_MSCC_PIF_POWER_OFF_CAUSE_ENUM
{
    NAS_MSCC_PIF_POWER_OFF_CAUSE_SIM_REMOVE,
    NAS_MSCC_PIF_POWER_OFF_CAUSE_NORMAL,
    NAS_MSCC_PIF_POWER_OFF_CAUSE_BUTT
};
typedef VOS_UINT32 NAS_MSCC_PIF_POWER_OFF_CAUSE_ENUM_UINT32;


enum NAS_MSCC_PIF_ROAM_CAPABILITY_ENUM
{
    NAS_MSCC_PIF_ROAM_NATION_ON_INTERNATION_ON                 = 0,
    NAS_MSCC_PIF_ROAM_NATION_ON_INTERNATION_OFF                = 1,
    NAS_MSCC_PIF_ROAM_NATION_OFF_INTERNATION_ON                = 2,
    NAS_MSCC_PIF_ROAM_NATION_OFF_INTERNATION_OFF               = 3,
    NAS_MSCC_PIF_ROAM_UNCHANGE                                 = 4,
    NAS_MSCC_PIF_ROAM_BUTT
};
typedef VOS_UINT8 NAS_MSCC_PIF_ROAM_CAPABILITY_ENUM_UINT8;


enum NAS_MSCC_PIF_ROAM_FEATURE_ENUM
{
    NAS_MSCC_PIF_ROAM_FEATURE_OFF                = 0,
    NAS_MSCC_PIF_ROAM_FEATURE_ON                 = 1,
    NAS_MSCC_PIF_ROAM_FEATURE_BUTT
};
typedef VOS_UINT8 NAS_MSCC_PIF_ROAM_FEATURE_ENUM_U8;


enum NAS_MSCC_PIF_PLMN_SELECTION_RESULT_ENUM
{
    NAS_MSCC_PIF_PLMN_SELECTION_RESULT_NORMAL_SERVICE    = 0,                        /* �������� */
    NAS_MSCC_PIF_PLMN_SELECTION_RESULT_LIMITED_SERVICE   = 1,                        /* ���Ʒ��� */
    NAS_MSCC_PIF_PLMN_SELECTION_RESULT_NO_SERVICE        = 2,                        /* �޷��� */
    NAS_MSCC_PIF_PLMN_SELECTION_RESULT_INTERRUPT         = 3,                        /* �������ж� */
    NAS_MSCC_PIF_PLMN_SELECTION_RESULT_NO_RF             = 4,
    NAS_MSCC_PIF_PLMN_SELECTION_RESULT_L2C               = 5,                        /* CL������L2C */
    NAS_MSCC_PIF_PLMN_SELECTION_RESULT_BUTT
};
typedef VOS_UINT32 NAS_MSCC_PIF_PLMN_SELECTION_RESULT_ENUM_UINT32;
enum NAS_MSCC_PIF_PLMN_SELECTION_START_FLAG_ENUM
{
    NAS_MSCC_PIF_PLMN_SELECTION_START    = 0,                        /* ������ʼ */
    NAS_MSCC_PIF_PLMN_SELECTION_BUTT
};
typedef VOS_UINT32 NAS_MSCC_PIF_PLMN_SELECTION_START_FLAG_ENUM_UINT32;


enum NAS_MSCC_PIF_SYS_CFG_SET_RESULT_ENUM
{
    NAS_MSCC_PIF_SYS_CFG_SET_SUCCESS                  = 0,
    NAS_MSCC_PIF_SYS_CFG_SET_FAILURE_OTHER            = 1,
    NAS_MSCC_PIF_SYS_CFG_SET_FAILURE_CS_SERV_EXIST    = 2,
    NAS_MSCC_PIF_SYS_CFG_SET_BUTT
};
typedef VOS_UINT32 NAS_MSCC_PIF_SYS_CFG_SET_RESULT_ENUM_UINT32;


enum  NAS_MSCC_PIF_CELL_RESTRICTION_TYPE_ENUM
{
    NAS_MSCC_PIF_CELL_RESTRICTION_TYPE_NONE                   = 0,                   /* ��ǰС���������κ�ҵ�� */
    NAS_MSCC_PIF_CELL_RESTRICTION_TYPE_NORMAL_SERVICE         = 1,                   /* ��ǰС����������ҵ�� */
    NAS_MSCC_PIF_CELL_RESTRICTION_TYPE_EMERGENCY_SERVICE      = 2,                   /* ��ǰС�����ƽ���ҵ�� */
    NAS_MSCC_PIF_CELL_RESTRICTION_TYPE_ALL_SERVICE            = 3,                   /* ��ǰС����������ҵ��ͽ���ҵ�� */
    NAS_MSCC_PIF_CELL_RESTRICTION_TYPE_BUTT
};
typedef VOS_UINT8   NAS_MSCC_PIF_CELL_RESTRICTION_TYPE_ENUM_UINT8;


enum NAS_MSCC_PIF_ATTACH_TYPE_ENUM
{
    NAS_MSCC_PIF_ATTACH_TYPE_GPRS          = 1,
    NAS_MSCC_PIF_ATTACH_TYPE_IMSI          = 2,
    NAS_MSCC_PIF_ATTACH_TYPE_GPRS_IMSI     = 3,
    NAS_MSCC_PIF_ATTACH_TYPE_BUTT
};
typedef VOS_UINT32 NAS_MSCC_PIF_ATTACH_TYPE_ENUM_UINT32;


enum NAS_MSCC_PIF_DETACH_TYPE_ENUM
{
    NAS_MSCC_PIF_DETACH_NULL               = 0,
    NAS_MSCC_PIF_DETACH_TYPE_GPRS          = 1,
    NAS_MSCC_PIF_DETACH_TYPE_IMSI          = 2,
    NAS_MSCC_PIF_DETACH_TYPE_GPRS_IMSI     = 3,
    NAS_MSCC_PIF_DETACH_TYPE_BUTT
};
typedef VOS_UINT32 NAS_MSCC_PIF_DETACH_TYPE_ENUM_UINT32;


enum NAS_MSCC_PIF_PLMN_CFG_MODE_ENUM
{
    NAS_MSCC_PIF_PLMN_CFG_MODE_USER_SEL           = 1,                               /* ֪ͨ�û�ѡ����PLMN��Ϣ */
    NAS_MSCC_PIF_PLMN_CFG_MODE_USER_RESEL         = 2,                               /* ����PLMN��User reselection */
    NAS_MSCC_PIF_PLMN_CFG_MODE_BUTT
};
typedef VOS_UINT32 NAS_MSCC_PIF_PLMN_CFG_MODE_ENUM_UINT32;


enum NAS_MSCC_PIF_PLMN_SEL_MODE_ENUM
{
    NAS_MSCC_PIF_PLMN_SEL_MODE_AUTO           = 0,                                   /* �Զ�����ģʽ */
    NAS_MSCC_PIF_PLMN_SEL_MODE_MANUAL         = 1,                                   /* �ֶ�����ģʽ */
    NAS_MSCC_PIF_PLMN_SEL_MODE_BUTT
};
typedef VOS_UINT32 NAS_MSCC_PIF_PLMN_SEL_MODE_ENUM_UINT32;


enum NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_ENUM
{
    NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST          = 0,                        /* �������� */
    NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_ENTER         = 1,                        /* �������� */
    NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_BUTT
};
typedef VOS_UINT32 NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_ENUM_UINT32;


enum NAS_MSCC_PIF_MS_MODE_ENUM
{
    NAS_MSCC_PIF_MS_MODE_CC                  = 0,                                    /* cs mode */
    NAS_MSCC_PIF_MS_MODE_CG                  = 1,                                    /* ps mode */
    NAS_MSCC_PIF_MS_MODE_A                   = 2,                                    /* cs ps mode */
    NAS_MSCC_PIF_MS_MODE_B                   = 4,                                    /* mode B */
    NAS_MSCC_PIF_MS_MODE_NULL                = 5,                                    /* mode null */
    NAS_MSCC_PIF_MS_MODE_BUTT
};
typedef VOS_UINT32 NAS_MSCC_PIF_MS_MODE_ENUM_UINT32;
enum NAS_MSCC_PIF_SERVICE_STATUS_ENUM
{
    NAS_MSCC_PIF_SERVICE_STATUS_NORMAL_SERVICE           = 0,                        /* �������� */
    NAS_MSCC_PIF_SERVICE_STATUS_LIMITED_SERVICE          = 1,                        /* ���Ʒ��� */
    NAS_MSCC_PIF_SERVICE_STATUS_LIMITED_SERVICE_REGION   = 2,                        /* ������������� */
    NAS_MSCC_PIF_SERVICE_STATUS_NO_IMSI                  = 3,                        /* ��imsi */
    NAS_MSCC_PIF_SERVICE_STATUS_NO_SERVICE               = 4,                        /* �޷��� */
    NAS_MSCC_PIF_SERVICE_STATUS_NO_CHANGE                = 5,
    NAS_MSCC_PIF_SERVICE_STATUS_DEEP_SLEEP               = 6,
    NAS_MSCC_PIF_SERVICE_STATUS_BUTT
};
typedef VOS_UINT32 NAS_MSCC_PIF_SERVICE_STATUS_ENUM_UINT32;
enum NAS_MSCC_PIF_SRVDOMAIN_ENUM
{
    NAS_MSCC_PIF_SRVDOMAIN_NO_DOMAIN               = 0,
    NAS_MSCC_PIF_SRVDOMAIN_CS                      = 1,
    NAS_MSCC_PIF_SRVDOMAIN_PS                      = 2,
    NAS_MSCC_PIF_SRVDOMAIN_CS_PS                   = 3,
    NAS_MSCC_PIF_SRVDOMAIN_NO_CHANGE               = 4,
    NAS_MSCC_PIF_SRVDOMAIN_NOT_REG_PLMN_SEARCHING  = 5,
    NAS_MSCC_PIF_SRVDOMAIN_BUTT
};
typedef VOS_UINT32 NAS_MSCC_PIF_SRVDOMAIN_ENUM_UINT32;



enum NAS_MSCC_PIF_DATATRAN_ATTRI_ENUM
{
    NAS_MSCC_PIF_DATATRAN_ATTRI_PDP_ACT          = 0,
    NAS_MSCC_PIF_DATATRAN_ATTRI_PDP_DEACT        = 1,
    NAS_MSCC_PIF_DATATRAN_ATTRI_R99_ONLY         = 2,
    NAS_MSCC_PIF_DATATRAN_ATTRI_HSDPA            = 3,
    NAS_MSCC_PIF_DATATRAN_ATTRI_HSUPA            = 4,
    NAS_MSCC_PIF_DATATRAN_ATTRI_HSDPA_AND_HSUPA  = 5,
    NAS_MSCC_PIF_DATATRAN_ATTRI_HSPA_PLUS        = 6,
    NAS_MSCC_PIF_DATATRAN_ATTRI_LTE_DATA         = 7,
    NAS_MSCC_PIF_DATATRAN_ATTRI_LTE_IDLE         = 8,
    NAS_MSCC_PIF_DATATRAN_ATTRI_DC_HSPA_PLUS     = 9,
    NAS_MSCC_PIF_DATATRAN_ATTRI_DC_MIMO          = 10,
    NAS_MSCC_PIF_DATATRAN_ATTRI_BUTT
};
typedef VOS_UINT8 NAS_MSCC_PIF_DATATRAN_ATTRI_ENUM_UINT8;


enum NAS_MSCC_PIF_ALLOWED_REG_DOMAIN_ENUM
{
    NAS_MSCC_PIF_ALLOWED_REG_DOMAIN_NULL     = 0,                                    /* ��ע��cs��ps */
    NAS_MSCC_PIF_ALLOWED_REG_DOMAIN_PS       = 1,                                    /* ֻע��PS */
    NAS_MSCC_PIF_ALLOWED_REG_DOMAIN_CS       = 2,                                    /* ֻע��CS */
    NAS_MSCC_PIF_ALLOWED_REG_DOMAIN_CS_PS    = 3,                                    /* ע��CS+PS */
    NAS_MSCC_PIF_ALLOWED_REG_DOMAIN_BUTT
};
typedef VOS_UINT8 NAS_MSCC_PIF_ALLOWED_REG_DOMAIN_ENUM_UINT8;


enum NAS_MSCC_PIF_USER_PLMN_SEARCH_RESULT_ENUM
{
    NAS_MSCC_PIF_USER_PLMN_SEARCH_RESULT_SUCCESS = 0,                                /* �ɹ� */
    NAS_MSCC_PIF_USER_PLMN_SEARCH_RESULT_FAIL    = 1,                                /* ʧ�� */
    NAS_MSCC_PIF_USER_PLMN_SEARCH_RESULT_REJ     = 2,
    NAS_MSCC_PIF_USER_PLMN_SEARCH_RESULT_BUTT
};
typedef VOS_UINT8 NAS_MSCC_PIF_USER_PLMN_SEARCH_RESULT_ENUM_UINT8;



enum NAS_MSCC_PIF_NW_IMS_VOICE_CAP_ENUM
{
    NAS_MSCC_PIF_NW_IMS_VOICE_NOT_SUPPORTED    = 0,
    NAS_MSCC_PIF_NW_IMS_VOICE_SUPPORTED        = 1,

    NAS_MSCC_PIF_NW_IMS_VOICE_BUTT
};
typedef VOS_UINT8 NAS_MSCC_PIF_NW_IMS_VOICE_CAP_ENUM_UINT8;


enum NAS_MSCC_PIF_NW_EMC_BS_CAP_ENUM
{
    NAS_MSCC_PIF_NW_EMC_BS_NOT_SUPPORTED       = 0,
    NAS_MSCC_PIF_NW_EMC_BS_SUPPORTED           = 1,

    NAS_MSCC_PIF_NW_EMC_BS_BUTT
};
typedef VOS_UINT8 NAS_MSCC_PIF_NW_EMC_BS_CAP_ENUM_UINT8;


enum NAS_MSCC_PIF_LTE_CS_CAPBILITY_ENUM
{
    NAS_MSCC_PIF_LTE_CS_CAPBILITY_NO_ADDITION_INFO  = 0,
    NAS_MSCC_PIF_LTE_CS_CAPBILITY_CSFB_NOT_PREFER   = 1,
    NAS_MSCC_PIF_LTE_CS_CAPBILITY_SMS_ONLY          = 2,
    NAS_MSCC_PIF_LTE_CS_CAPBILITY_NOT_SUPPORTED     = 3,

    NAS_MSCC_PIF_LTE_CS_CAPBILITY_BUTT
};
typedef VOS_UINT8 NAS_MSCC_PIF_LTE_CS_CAPBILITY_ENUM_UINT8;


enum NAS_MSCC_PIF_IMS_NORMAL_REG_STATUS_ENUM
{
    NAS_MSCC_PIF_IMS_NORMAL_REG_STATUS_DEREG        = 0x00,
    NAS_MSCC_PIF_IMS_NORMAL_REG_STATUS_DEREGING     = 0x01,
    NAS_MSCC_PIF_IMS_NORMAL_REG_STATUS_REGING       = 0x02,
    NAS_MSCC_PIF_IMS_NORMAL_REG_STATUS_REG          = 0x03,

    NAS_MSCC_PIF_IMS_NORMAL_REG_STATUS_BUTT         = 0xFF
};
typedef VOS_UINT8 NAS_MSCC_PIF_IMS_NORMAL_REG_STATUS_ENUM_UINT8;


enum NAS_MSCC_PIF_REG_CONTROL_ENUM
{
    NAS_MSCC_PIF_REG_CONTROL_BY_3GPP_MMC = 0,                 /* ������������Ƿ�ע�ᰴĿǰ3GPPЭ��ģ��MMC���� */
    NAS_MSCC_PIF_REG_CONTROL_BY_3GPP2_CBP,                    /*������������Ƿ�ע����3GPP2Э��CDMA Baseband Protocol���� */
    NAS_MSCC_PIF_REG_CONTROL_BUTT
};
typedef VOS_UINT8 NAS_MSCC_PIF_REG_CONTROL_ENUM_UINT8;


enum NAS_MSCC_PIF_3GPP2_RAT_TYPE_ENUM
{
    NAS_MSCC_PIF_3GPP2_RAT_TYPE_CDMA1X = 0,
    NAS_MSCC_PIF_3GPP2_RAT_TYPE_HRPD,
    NAS_MSCC_PIF_3GPP2_RAT_TYPE_BUTT
};
typedef VOS_UINT8 NAS_MSCC_PIF_3GPP2_RAT_TYPE_ENUM_UINT8;


enum NAS_MSCC_PIF_EPS_ATTACH_REASON_ENUM
{
    NAS_MSCC_PIF_EPS_ATTACH_REASON_INITIAL          = 0,
    NAS_MSCC_PIF_EPS_ATTACH_REASON_HANDOVER         = 1,
    NAS_MSCC_PIF_EPS_ATTACH_REASON_BUTT
};
typedef VOS_UINT32 NAS_MSCC_PIF_EPS_ATTACH_REASON_ENUM_UINT32;


enum NAS_MSCC_PIF_DETACH_REASON_ENUM
{
    NAS_MSCC_PIF_DETACH_REASON_USER_DETACH          = 0,/* �û�������detach���� */
    NAS_MSCC_PIF_DETACH_REASON_RAT_OR_BAND_DETACH   = 1,/* system configure��RAT��band������detach */
    NAS_MSCC_PIF_DETACH_REASON_SRV_DOMAIN_DETACH    = 2,/* system configure�з����򴥷���detach */
    NAS_MSCC_PIF_DETACH_REASON_3GPP2_ATTACHED       = 3,/* 3GPP2������attach */
    NAS_MSCC_PIF_DETACH_REASON_BUTT
};
typedef VOS_UINT32 NAS_MSCC_PIF_DETACH_REASON_ENUM_UINT32;


enum NAS_MSCC_PIF_PLMN_PRIORITY_CLASS_ENUM
{
    NAS_MSCC_PIF_PLMN_PRIORITY_HOME               = 0,    /* home or ehome plmn */
    NAS_MSCC_PIF_PLMN_PRIORITY_PREF               = 1,    /* UPLMN or OPLMN */
    NAS_MSCC_PIF_PLMN_PRIORITY_ANY                = 2,    /* Acceptable PLMN */
    NAS_MSCC_PIF_PLMN_PRIORITY_BUTT
};
typedef VOS_UINT8 NAS_MSCC_PIF_PLMN_PRIORITY_CLASS_ENUM_UINT8;
enum NAS_MSCC_PIF_ACQ_REASON_ENUM
{
    NAS_MSCC_PIF_ACQ_REASON_POWER_UP        = 0,
    NAS_MSCC_PIF_ACQ_REASON_HIGH_PRIORITY   = 1,
    NAS_MSCC_PIF_ACQ_REASON_OTHER           = 2,
    NAS_MSCC_PIF_ACQ_REASON_BUTT
};
typedef VOS_UINT32 NAS_MSCC_PIF_ACQ_REASON_ENUM_UINT32;



enum NAS_MSCC_PIF_ACQ_RESULT_ENUM
{
    NAS_MSCC_PIF_ACQ_RESULT_SUCCESS          = 0,
    NAS_MSCC_PIF_ACQ_RESULT_FAILURE          = 1,
    NAS_MSCC_PIF_ACQ_RESULT_BUTT
};
typedef VOS_UINT32 NAS_MSCC_PIF_ACQ_RESULT_ENUM_UINT32;


enum NAS_MSCC_PIF_REG_RESULT_ENUM
{
    NAS_MSCC_PIF_REG_RESULT_SUCCESS          = 0,
    NAS_MSCC_PIF_REG_RESULT_ACQ_FAILURE      = 1,
    NAS_MSCC_PIF_REG_RESULT_REG_FAILURE      = 2,
    NAS_MSCC_PIF_REG_RESULT_BUTT
};
typedef VOS_UINT32 NAS_MSCC_PIF_REG_RESULT_ENUM_UINT32;



enum NAS_MSCC_PIF_CALL_MODE_ENUM
{
    NAS_MSCC_PIF_ECALL_ONLY            = 0,
    NAS_MSCC_PIF_ECALL_AND_NORMAL_CALL = 1,
    NAS_MSCC_PIF_ECALL_MODE_BUTT
};
typedef VOS_UINT8 NAS_MSCC_PIF_CALL_MODE_ENUM_UINT8;

/*****************************************************************************
 �ṹ����: NAS_MSCC_PIF_LMM_ACCESS_TYPE_ENUM
 Э����:
 ASN.1 ����:
 �ṹ˵��:
*****************************************************************************/
enum NAS_MSCC_PIF_LMM_ACCESS_TYPE_ENUM
{
    NAS_MSCC_PIF_LMM_ACCESS_TYPE_EUTRAN_TDD      = 0,
    NAS_MSCC_PIF_LMM_ACCESS_TYPE_EUTRAN_FDD         ,
    NAS_MSCC_PIF_LMM_ACCESS_TYPE_BUTT
};
typedef VOS_UINT8  NAS_MSCC_PIF_LMM_ACCESS_TYPE_ENUM_UINT8;


/** ****************************************************************************
 * Name        : NAS_MSCC_PIF_CDMA_CALL_TYPE_ENUM_UINT8
 * Description : Call type
 *******************************************************************************/
enum NAS_MSCC_PIF_CDMA_CALL_TYPE_ENUM
{
    NAS_MSCC_PIF_CDMA_CALL_TYPE_1X_EMC_VOICE_CALL      = 0x00,
    NAS_MSCC_PIF_CDMA_CALL_TYPE_1X_NORMAL_VOICE_CALL   = 0x01,
    NAS_MSCC_PIF_CDMA_CALL_TYPE_1X_NORMAL_DATA_CALL    = 0x02,
    NAS_MSCC_PIF_CDMA_CALL_TYPE_DO_NORMAL_DATA_CALL    = 0x03,
    NAS_MSCC_PIF_CDMA_CALL_TYPE_BUTT                   = 0x04
};
typedef VOS_UINT8 NAS_MSCC_PIF_CDMA_CALL_TYPE_ENUM_UINT8;

/** ****************************************************************************
 * Name        : NAS_MSCC_PIF_CDMA_CALL_CAUSE_ENUM_UINT8
 * Description : Call cause
 *******************************************************************************/
enum NAS_MSCC_PIF_CDMA_CALL_CAUSE_ENUM
{
    NAS_MSCC_PIF_CDMA_CALL_CAUSE_NO_SERVICE                           = 0x01, /**<  No Service\x{ff0c}Call Redial */
    NAS_MSCC_PIF_CDMA_CALL_CAUSE_MAX_ACCESS_PROBES                    = 0x02, /**<  Max Access Probes, Call Redial */
    NAS_MSCC_PIF_CDMA_CALL_CAUSE_REORDER_NORMAL                       = 0x03, /**<  Reorder Order, Call Redial */
    NAS_MSCC_PIF_CDMA_CALL_CAUSE_REORDER_LOW_RSSI                     = 0x04, /**<  Reorder Order, Call Redial, RSSI<=-100dB */
    NAS_MSCC_PIF_CDMA_CALL_CAUSE_ACCESS_DENYIED                       = 0x05, /**<  Access Denied, Call Redial */
    NAS_MSCC_PIF_CDMA_CALL_CAUSE_SIGNAL_FADE_NORMAL                   = 0x06, /**<  Signal Fade, Call Redial */
    NAS_MSCC_PIF_CDMA_CALL_CAUSE_SIGNAL_FADE_LOW_RSSI                 = 0x07, /**<  Signal Fade, Call Redial */
    NAS_MSCC_PIF_CDMA_CALL_CAUSE_CHANNEL_ASSIGN_TIMEOUT_NORMAL        = 0x08, /**<  Access Time Out, Call Redial */
    NAS_MSCC_PIF_CDMA_CALL_CAUSE_CHANNEL_ASSIGN_TIMEOUT_LOW_RSSI      = 0x09, /**<  Access Time Out, Call Redial, RSSI<=-100dB */
    NAS_MSCC_PIF_CDMA_CALL_CAUSE_ACCT_BLOCK                           = 0x0A, /**<  Acct Block, Call Redial */
    NAS_MSCC_PIF_CDMA_CALL_CAUSE_NDSS                                 = 0x0B, /**<  Access Control based on Call Type, redial */
    NAS_MSCC_PIF_CDMA_CALL_CAUSE_REDIRECTION                          = 0x0C, /**<  Redirection, Call Redial */
    NAS_MSCC_PIF_CDMA_CALL_CAUSE_ABORT                                = 0x0D, /**<  State can not Process Call, Call Redial */
    NAS_MSCC_PIF_CDMA_CALL_CAUSE_INTERNAL_NO_SERVICE                  = 0x0E, /* Internal No Service\x{ff0c}Call Redial */

    NAS_MSCC_PIF_CDMA_CALL_CAUSE_ACCESS_IN_PROGRESS                   = 0x0F, /* Access In Progress, Call Redial */
    NAS_MSCC_PIF_CDMA_CALL_CAUSE_ACCESS_FAIL                          = 0x10, /* Access fail, Call Redial */
    NAS_MSCC_PIF_CDMA_CALL_CAUSE_SIGNAL_FADE                          = 0x11, /* Signal Fade, Call Redial */
    NAS_MSCC_PIF_CDMA_CALL_CAUSE_BS_RELEASE                           = 0x12, /* BS, Call Redial */
    NAS_MSCC_PIF_CDMA_CALL_CAUSE_CCS_NOT_SUPPORT                      = 0x13, /* Concurrent Service not Support, Call Redial */
    NAS_MSCC_PIF_CDMA_CALL_CAUSE_RTC_RTCACK_FAILURE                   = 0x14, /* RTC ACK FAIL, Call Redial */

    NAS_MSCC_PIF_CDMA_CALL_CAUSE_BUTT                                 = 0xFF
};
typedef VOS_UINT8 NAS_MSCC_PIF_CDMA_CALL_CAUSE_ENUM_UINT8;

/** ****************************************************************************
 * Name        : NAS_MSCC_PIF_CDMACSQ_SET_RESULT_ENUM_UINT8
 * Description : Service status
 *******************************************************************************/
enum NAS_MSCC_PIF_CDMACSQ_SET_RESULT_ENUM
{
    NAS_MSCC_PIF_CDMACSQ_SET_RESULT_SUCC                         = 0x00,
    NAS_MSCC_PIF_CDMACSQ_SET_RESULT_FAIL                         = 0x01,
    NAS_MSCC_PIF_CDMACSQ_SET_RESULT_BUTT                         = 0x02
};
typedef VOS_UINT8 NAS_MSCC_PIF_CDMACSQ_SET_RESULT_ENUM_UINT8;

/** ****************************************************************************
 * Name        : NAS_MSCC_PIF_CDMACSQ_SET_RESULT_ENUM_UINT8
 * Description : Service status
 *******************************************************************************/
enum NAS_MSCC_PIF_CFREQ_LOCK_SET_MODE_ENUM
{
    NAS_MSCC_PIF_CFREQ_LOCK_SET_MODE_DISABLE                          = 0x00,
    NAS_MSCC_PIF_CFREQ_LOCK_SET_MODE_ENABLE                           = 0x01,
    NAS_MSCC_PIF_CFREQ_LOCK_SET_MODE_BUTT                             = 0x02
};

typedef VOS_UINT8 NAS_MSCC_PIF_CFREQ_LOCK_SET_MODE_ENUM_UINT8;


/** ****************************************************************************
 * Name        : NAS_MSCC_PIF_START_RESULT_ENUM_UINT32
 * Description : start result
 *******************************************************************************/
enum	NAS_MSCC_PIF_START_RESULT_ENUM
{
    NAS_MSCC_PIF_START_RESULT_SUCC,
    NAS_MSCC_PIF_START_RESULT_FAIL
};

typedef VOS_UINT32 NAS_MSCC_PIF_START_RESULT_ENUM_UINT32;

/*****************************************************************************
 ö����    : NAS_MSCC_PIF_CFPLMN_OPER_RESULT_ENUM
 �ṹ˵��  : NAS_MSCC_PIF_CFPLMN_OPER_RESULT_ENUM��Ϣ�е�RESULT;
*****************************************************************************/

enum NAS_MSCC_PIF_CFPLMN_OPER_RESULT_ENUM
{
    NAS_MSCC_PIF_CFPLMN_OPER_RESULT_SUCCESS          = 0,
    NAS_MSCC_PIF_CFPLMN_OPER_RESULT_FAILURE          = 1,
    NAS_MSCC_PIF_CFPLMN_OPER_RESULT_BUTT
};
typedef VOS_UINT32 NAS_MSCC_PIF_CFPLMN_OPER_RESULT_ENUM_UINT32;

/*****************************************************************************
 ö����    : NAS_MSCC_PIF_CFPLMN_OPERATE_TYPE_ENUM
 �ṹ˵��  : NAS_MSCC_PIF_CFPLMN_SET_STRU��Ϣ�е�cmdtype;
*****************************************************************************/
enum NAS_MSCC_PIF_CFPLMN_OPERATE_TYPE_ENUM
{
    NAS_MSCC_PIF_CFPLMN_TYPE_QUERY     = 0,
    NAS_MSCC_PIF_CFPLMN_TYPE_DEL_ALL   = 1,
    NAS_MSCC_PIF_CFPLMN_TYPE_DEL_ONE   = 2,
    NAS_MSCC_PIF_CFPLMN_TYPE_ADD_ONE   = 3,
    NAS_MSCC_PIF_CFPLMN_TYPE_BUTT
};
typedef VOS_UINT8  NAS_MSCC_PIF_CFPLMN_OPERATE_TYPE_ENUM_UINT8;


/*****************************************************************************
 ö����    : NAS_MSCC_PIF_PREF_PLMN_OPER_RESULT_ENUM
 �ṹ˵��  : NAS_MSCC_PIF_PREF_PLMN_OPER_RESULT_ENUM��Ϣ�е�RESULT;
*****************************************************************************/

enum NAS_MSCC_PIF_PREF_PLMN_OPER_RESULT_ENUM
{
    NAS_MSCC_PIF_PREF_PLMN_OPER_RESULT_SUCCESS             = 0,
    NAS_MSCC_PIF_PREF_PLMN_OPER_RESULT_FAILURE             = 1,
    NAS_MSCC_PIF_PREF_PLMN_OPER_RESULT_TIMEOUT             = 2,
    NAS_MSCC_PIF_PREF_PLMN_OPER_RESULT_MEM_ALLOC_FAIL      = 3,
    NAS_MSCC_PIF_PREF_PLMN_OPER_RESULT_GET_PLMNINFO_FAIL   = 4,
    NAS_MSCC_PIF_PREF_PLMN_OPER_RESULT_PLMN_INDEX_ERR      = 5,
    NAS_MSCC_PIF_PREF_PLMN_OPER_RESULT_UPDATA_USIM_PLMN    = 6,
    NAS_MSCC_PIF_PREF_PLMN_OPER_RESULT_PLMNID_INVAILD      = 7,
    NAS_MSCC_PIF_PREF_PLMN_OPER_RESULT_SAME_PLMNID         = 8,
    NAS_MSCC_PIF_PREF_PLMN_OPER_RESULT_BUTT
};
typedef VOS_UINT32 NAS_MSCC_PIF_PREF_PLMN_OPER_RESULT_ENUM_UINT32;

/*****************************************************************************
 ö����    : NAS_MSCC_PIF_PREF_PLMN_CMD_TYPE_ENUM
 �ṹ˵��  : PREFPLMN��ѯ��������ö��
 1.��    ��   : 2015��02��06��
   ��    ��   : y00307564
   �޸�����   : �½�
*****************************************************************************/
enum NAS_MSCC_PIF_PREF_PLMN_CMD_TYPE_ENUM
{
    NAS_MSCC_PIF_PREF_PLMN_QUERY      = 0,  /* PREFPLMN��ѯ���� */
    NAS_MSCC_PIF_PREF_PLMN_TEST       = 1,  /* PREFPLMN�������� */
    NAS_MSCC_PIF_PREF_PLMN_BUTT
};

typedef VOS_UINT8 NAS_MSCC_PIF_PREF_PLMN_CMD_TYPE_ENUM_UINT8;

/*****************************************************************************
 ö����    : NAS_MSCC_PIF_PARA_TYPE_ENUM
 �ṹ˵��  : PREFPLMN��ѯ��������ö��
 1.��    ��   : 2015��02��06��
   ��    ��   : y00307564
   �޸�����   : �½�
*****************************************************************************/
typedef enum
{
    NAS_MSCC_PLMN_LIST_INFO,           /*��ȡ������PLMN�б�*/
    NAS_MSCC_OPLMN_INFO,
    NAS_MSCC_UPLMN_INFO,
    NAS_MSCC_HPLMN_INFO,
    NAS_MSCC_PLMNSEL_INFO,

    /*����MMCȫ�ֱ�������*/
    NAS_MSCC_BEGIN_SET_MMC_PARA,
    NAS_MSCC_SET_PLMNSEL_INFO,
    NAS_MSCC_SET_OPLMN_INFO,
    NAS_MSCC_SET_UPLMN_INFO,
    NAS_MSCC_END_SET_MMC_PARA,
    NAS_MSCC_PARA_TYPE_BUTT
}NAS_MSCC_PIF_PARA_TYPE_ENUM;
typedef VOS_UINT8 NAS_MSCC_PIF_PARA_TYPE_ENUM_UINT8;

/*****************************************************************************
 ö����    : NAS_MSCC_PIF_PREF_PLMN_ID_ENUM
 �ṹ˵��  : PREFPLMN����ö��
 1.��    ��   : 2015��02��06��
   ��    ��   : y00307564
   �޸�����   : �½�
*****************************************************************************/
typedef enum
{
    NAS_MSCC_PREF_PLMN_UPLMN,
    NAS_MSCC_PREF_PLMN_OPLMN,
    NAS_MSCC_PREF_PLMN_HPLMN,
    NAS_MSCC_PREF_PLMN_TYPE_BUTT
}NAS_MSCC_PIF_PREF_PLMN_ID_ENUM;
typedef VOS_UINT8 NAS_MSCC_PIF_PREF_PLMN_TYPE_ENUM_UINT8;

/*****************************************************************************
 ö����    : NAS_MSCC_PIF_PREFPLMN_OPERATE_TYPE_ENUM
 �ṹ˵��  : PREFPLMN��ɾ�Ĳ�������ö��
 1.��    ��   : 2015��02��06��
   ��    ��   : y00307564
   �޸�����   : �½�
*****************************************************************************/
typedef enum
{
    NAS_MSCC_PREF_PLMN_QUREY,
    NAS_MSCC_PREF_PLMN_DEL_ONE,
    NAS_MSCC_PREF_PLMN_ADD_ONE,
    NAS_MSCC_PREF_PLMN_MODIFY_ONE,
    NAS_MSCC_PREF_PLMN_OPERATE_TYPE_BUTT
} NAS_MSCC_PIF_PREFPLMN_OPERATE_TYPE_ENUM;
typedef VOS_UINT8 NAS_MSCC_PIF_PREFPLMN_OPERATE_TYPE_ENUM_UINT8;

typedef enum
{
    EN_MMC_PLMN_LIST_INFO,           /*��ȡ������PLMN�б�*/
    EN_MMC_OPLMN_INFO,
    EN_MMC_UPLMN_INFO,
    EN_MMC_HPLMN_INFO,
    EN_MMC_PLMNSEL_INFO,

    /*����MMCȫ�ֱ�������*/
    EN_MMC_BEGIN_SET_MMC_PARA,
    EN_MMC_SET_PLMNSEL_INFO,
    EN_MMC_SET_OPLMN_INFO,
    EN_MMC_SET_UPLMN_INFO,
    EN_MMC_END_SET_MMC_PARA,
    MMC_MMA_PARA_TYPE_BUTT
}MMC_MMA_PARA_TYPE_ENUM;

/** ****************************************************************************
 ö����    : NAS_MSCC_PIF_ACQUIRED_RESULT_ENUM
 �ṹ˵��  : ϵͳ������
 1.��    ��   : 2015��02��06��
   ��    ��   : y00307564
   �޸�����   : �½�
 *******************************************************************************/
enum NAS_MSCC_PIF_ACQUIRED_RESULT_ENUM
{
    NAS_MSCC_PIF_ACQUIRED_RESULT_SUCC        = 0x00000000,
    NAS_MSCC_PIF_ACQUIRED_RESULT_FAIL        = 0x00000001,
    NAS_MSCC_PIF_ACQUIRED_RESULT_ABORTED     = 0x00000002,
    NAS_MSCC_PIF_ACQUIRED_RESULT_NO_RF       = 0x00000003,
    NAS_MSCC_PIF_ACQUIRED_RESULT_ENUM_BUTT   = 0x00000004
};
typedef VOS_UINT32 NAS_MSCC_PIF_ACQUIRED_RESULT_ENUM_UINT32;

typedef VOS_UINT16 NAS_MSCC_USIM_RAT;


enum NAS_MSCC_PIF_NETWORK_DETACH_TYPE_ENUM
{
    NAS_MSCC_PIF_NETWORK_DETACH_TYPE_REATTACH      = 1,
    NAS_MSCC_PIF_NETWORK_DETACH_TYPE_NOATTACH      = 2,
    NAS_MSCC_PIF_NETWORK_DETACH_TYPE_IMSI          = 3,
    NAS_MSCC_PIF_NETWORK_DETACH_TYPE_BUTT
};
typedef VOS_UINT8 NAS_MSCC_PIF_NETWORK_DETACH_TYPE_ENUM_UINT8;


enum MSCC_MMA_SYSTEM_ACQUIRE_RESULT_ENUM
{
    MSCC_MMA_SYSTEM_ACQUIRE_RESULT_NORMAL_SERVICE    = 0,                        /* Normal service*/
    MSCC_MMA_SYSTEM_ACQUIRE_RESULT_LIMITED_SERVICE   = 1,                        /* Limited service */
    MSCC_MMA_SYSTEM_ACQUIRE_RESULT_NO_SERVICE        = 2,                        /* No service */
    MSCC_MMA_SYSTEM_ACQUIRE_RESULT_INTERRUPT         = 3,                        /* sevice interrupted */
    MSCC_MMA_SYSTEM_ACQUIRE_RESULT_NO_RF             = 4,
    MSCC_MMA_SYSTEM_ACQUIRE_RESULT_BUTT
};
typedef VOS_UINT32 MSCC_MMA_SYSTEM_ACQUIRE_RESULT_ENUM_UINT32;


/*****************************************************************************
 ö����    : NAS_MSCC_PIF_NET_SCAN_RESULT_ENUM
 �ṹ˵��  : NAS_MSCC_PIF_NET_SCAN_CNF_STRU��Ϣ�е�enResult;
*****************************************************************************/
enum NAS_MSCC_PIF_NET_SCAN_RESULT_ENUM
{
    NAS_MSCC_PIF_NET_SCAN_RESULT_SUCCESS     = 0,
    NAS_MSCC_PIF_NET_SCAN_RESULT_FAILURE     = 1,
    NAS_MSCC_PIF_NET_SCAN_RESULT_BUTT
};
typedef VOS_UINT8  NAS_MSCC_PIF_NET_SCAN_RESULT_ENUM_UINT8;


enum NAS_MSCC_PIF_NET_SCAN_CAUSE_ENUM
{
    NAS_MSCC_PIF_NET_SCAN_CAUSE_SIGNAL_EXIST        = 0,                /* ������������ */
    NAS_MSCC_PIF_NET_SCAN_CAUSE_STATE_NOT_ALLOWED   = 1,                /* ��ǰδפ�� */
    NAS_MSCC_PIF_NET_SCAN_CAUSE_FREQ_LOCK           = 2,                /* ��ǰ��Ƶ״̬ */
    NAS_MSCC_PIF_NET_SCAN_CAUSE_PARA_ERROR          = 3,                /* �������󣬰������뼼����֧�֣�Ƶ�β�֧�֣�Ƶ������������޴��� */
    NAS_MSCC_PIF_NET_SCAN_CAUSE_CONFLICT            = 4,                /* ����ԭ��ֵ��ͻ */
    NAS_MSCC_PIF_NET_SCAN_CAUSE_SERVICE_EXIST,
    NAS_MSCC_PIF_NET_SCAN_CAUSE_NOT_CAMPED,
    NAS_MSCC_PIF_NET_SCAN_CAUSE_RAT_TYPE_ERROR,
    NAS_MSCC_PIF_NET_SCAN_CAUSE_BUTT
};
typedef VOS_UINT8 NAS_MSCC_PIF_NET_SCAN_CAUSE_ENUM_UINT8;
enum NAS_MSCC_PIF_REJ_TYPE_ENUM
{
    NAS_MSCC_PIF_REJ_TYPE_REG        = 0,
    NAS_MSCC_PIF_REJ_TYPE_USIM_AUTH  = 1,
    NAS_MSCC_PIF_REJ_TYPE_SERV_REQ   = 2,
    NAS_MSCC_PIF_REJ_TYPE_NETWORK_DETACH_IND = 3,
    NAS_MSCC_PIF_REJ_TYPE_BUTT
};
typedef VOS_UINT8 NAS_MSCC_PIF_REJ_TYPE_ENUM_UINT8;


enum NAS_MSCC_PIF_SRV_TYPE_ENUM
{
    NAS_MSCC_PIF_SRV_TYPE_CS_MO_NORMAL_CALL,
    NAS_MSCC_PIF_SRV_TYPE_CS_MO_EMERGENCY_CALL,
    NAS_MSCC_PIF_SRV_TYPE_CS_MO_SS,
    NAS_MSCC_PIF_SRV_TYPE_CS_MO_SMS,
    NAS_MSCC_PIF_SRV_TYPE_PS_CONVERSAT_CALL,
    NAS_MSCC_PIF_SRV_TYPE_PS_STREAM_CALL,
    NAS_MSCC_PIF_SRV_TYPE_PS_INTERACT_CALL,
    NAS_MSCC_PIF_SRV_TYPE_PS_BACKGROUND_CALL,
    NAS_MSCC_PIF_SRV_TYPE_PS_SUBSCRIB_TRAFFIC_CALL,
    NAS_MSCC_PIF_SRV_TYPE_BUTT
};
typedef VOS_UINT8 NAS_MSCC_PIF_SRV_TYPE_ENUM_UINT8;


enum NAS_MSCC_PIF_SRV_ACQ_RESULT_ENUM
{
    NAS_MSCC_PIF_SRV_ACQ_RESULT_SUCCESS = 0,                                /* �ɹ� */
    NAS_MSCC_PIF_SRV_ACQ_RESULT_FAIL    = 1,                                /* ʧ�� */
    NAS_MSCC_PIF_SRV_ACQ_RESULT_BUTT
};
typedef VOS_UINT8 NAS_MSCC_PIF_SRV_ACQ_RESULT_ENUM_UINT8;


enum NAS_MSCC_PIF_VOICE_DOMAIN_ENUM
{
    NAS_MSCC_PIF_VOICE_DOMAIN_CS_ONLY            = 0,    /* CS voice only */
    NAS_MSCC_PIF_VOICE_DOMAIN_IMS_PS_ONLY        = 1,    /* IMS PS voice only */
    NAS_MSCC_PIF_VOICE_DOMAIN_CS_PREFERRED       = 2,    /* CS vocie preferred, IMS PS voice as secondary */
    NAS_MSCC_PIF_VOICE_DOMAIN_IMS_PS_PREFERRED   = 3,    /* IMS PS voice preferred, CS vocie as secondary */

    NAS_MSCC_PIF_VOICE_DOMAIN_BUTT
};
typedef VOS_UINT32  NAS_MSCC_PIF_VOICE_DOMAIN_ENUM_UINT32;


enum NAS_MSCC_PIF_IMS_SWITCH_STATE_ENUM
{
    NAS_MSCC_PIF_IMS_SWITCH_STATE_OFF        = 0,
    NAS_MSCC_PIF_IMS_SWITCH_STATE_ON         = 1,
    NAS_MSCC_PIF_IMS_SWITCH_STATE_BUTT
};
typedef VOS_UINT8 NAS_MSCC_PIF_IMS_SWITCH_STATE_ENUM_UINT8;


enum NAS_MSCC_PIF_IMS_START_RESULT_ENUM
{
    NAS_MSCC_PIF_IMS_START_RESULT_SUCC       = 0,
    NAS_MSCC_PIF_IMS_START_RESULT_TIMEOUT    = 1,

    NAS_MSCC_PIF_IMS_START_RESULT_BUTT
};
typedef VOS_UINT32 NAS_MSCC_PIF_IMS_START_RESULT_ENUM_UINT32;


enum NAS_MSCC_PIF_IMS_STOP_RESULT_ENUM
{
    NAS_MSCC_PIF_IMS_STOP_RESULT_SUCC       = 0,
    NAS_MSCC_PIF_IMS_STOP_RESULT_TIMEOUT    = 1,

    NAS_MSCC_PIF_IMS_STOP_RESULT_BUTT
};
typedef VOS_UINT32 NAS_MSCC_PIF_IMS_STOP_RESULT_ENUM_UINT32;


/** ****************************************************************************
 * Name        : NAS_MSCC_PIF_INTERSYS_CAUSE_ENUM_UINT32
 *
 * Description :
 *******************************************************************************/
enum NAS_MSCC_PIF_INTERSYS_CAUSE_ENUM
{
    NAS_MSCC_PIF_INTERSYS_CAUSE_RESELECT    = 0x00000000,
    NAS_MSCC_PIF_INTERSYS_CAUSE_REDIR       = 0x00000001,
    NAS_MSCC_PIF_INTERSYS_CAUSE_HO          = 0x00000002,
    NAS_MSCC_PIF_INTERSYS_CAUSE_ENUM_BUTT   = 0x00000003
};
typedef VOS_UINT32 NAS_MSCC_PIF_INTERSYS_CAUSE_ENUM_UINT32;

/** ****************************************************************************
 * Name        : NAS_MSCC_PIF_CL_ACQUIRED_RESULT_ENUM_UINT32
 *
 * Description :
 *******************************************************************************/
enum MSCC_MMC_CL_ACQUIRED_RESULT_ENUM
{
    NAS_MSCC_PIF_CL_ACQUIRED_RESULT_SUCC    = 0x00000000,
    NAS_MSCC_PIF_CL_ACQUIRED_RESULT_FAIL    = 0x00000001,
    NAS_MSCC_PIF_CL_ACQUIRED_RESULT_ABORTED = 0x00000002,
    NAS_MSCC_PIF_CL_ACQUIRED_RESULT_ENUM_BUTT= 0x00000003
};
typedef VOS_UINT32 NAS_MSCC_PIF_CL_ACQUIRED_RESULT_ENUM_UINT32;

/** ****************************************************************************
 * Name        : NAS_MSCC_PIF_PRI_CLASS_ENUM
 *
 * Description :
 *******************************************************************************/
enum NAS_MSCC_PIF_PRI_CLASS_ENUM
{
    NAS_MSCC_PIF_PRI_CLASS_HOME             = 0x00,
    NAS_MSCC_PIF_PRI_CLASS_PREF             = 0x01,
    NAS_MSCC_PIF_PRI_CLASS_ANY              = 0x0F,
    NAS_MSCC_PIF_PRI_CLASS_ENUM_BUTT        = 0xF0
};
typedef VOS_UINT8 NAS_MSCC_PIF_PRI_CLASS_ENUM_UINT8;

/* Modified by l00301449 for CDMA Iteration 15, 2015-5-15, begin */
/*****************************************************************************
 ö����    : NAS_MSCC_PIF_SRV_ACQ_RAT_TYPE_ENUM_UINT8
 ö��˵��  : ҵ�񴥷�������RAT����
 1.��    ��   : 2014��5��15��
   ��    ��   : l00301449
   �޸�����   : �½�
*****************************************************************************/
enum NAS_MSCC_PIF_SRV_ACQ_RAT_TYPE_ENUM
{
    NAS_MSCC_PIF_SRV_ACQ_RAT_TYPE_GUL,
    NAS_MSCC_PIF_SRV_ACQ_RAT_TYPE_1X,
    NAS_MSCC_PIF_SRV_ACQ_RAT_TYPE_HRPD,
    NAS_MSCC_PIF_SRV_ACQ_RAT_TYPE_BUTT
};

typedef VOS_UINT8 NAS_MSCC_PIF_SRV_ACQ_RAT_TYPE_ENUM_UINT8;





/*****************************************************************************
 ö����    : NAS_MSCC_PIF_RF_AVAILABLE_RAT_TYPE_ENUM_UINT8
 ö��˵��  : RF AVAILABLE��RAT����
 1.��    ��   : 2014��5��15��
   ��    ��   : l00301449
   �޸�����   : �½�
*****************************************************************************/
enum NAS_MSCC_PIF_RF_AVAILABLE_RAT_TYPE_ENUM
{
    NAS_MSCC_PIF_RF_AVAILABLE_RAT_TYPE_3GPP,
    NAS_MSCC_PIF_RF_AVAILABLE_RAT_TYPE_1X,
    NAS_MSCC_PIF_RF_AVAILABLE_RAT_TYPE_HRPD,
    NAS_MSCC_PIF_RF_AVAILABLE_RAT_TYPE_BUTT
};

typedef VOS_UINT8 NAS_MSCC_PIF_RF_AVAILABLE_RAT_TYPE_ENUM_UINT8;
/* Modified by l00301449 for CDMA Iteration 15, 2015-5-15, end */


/* Added by y00322978 for CDMA Iteration 15, 2015-5-11, begin */
/*****************************************************************************
 ö����    : NAS_MSCC_PIF_PS_RATTYPE_ENUM_UINT32
 �ṹ˵��  : CDMA PS RATTYPE ö������
 1.��    ��   : 2015��05��11��
   ��    ��   : y00322978
   �޸�����   : �½�
*****************************************************************************/
enum NAS_MSCC_PIF_PS_RAT_TYPE_ENUM
{
    NAS_MSCC_PIF_PS_RATTYPE_NULL   = 0,
    NAS_MSCC_PIF_PS_RATTYPE_1X     = 1,
    NAS_MSCC_PIF_PS_RATTYPE_HRPD   = 2,
    NAS_MSCC_PIF_PS_RATTYPE_EHRPD  = 3,
    NAS_MSCC_PIF_PS_RATTYPE_LTE    = 4,
    NAS_MSCC_PIF_PS_RATTYPE_BUTT
};
typedef VOS_UINT32 NAS_MSCC_PIF_PS_RAT_TYPE_ENUM_UINT32;
/* Added by y00322978 for CDMA Iteration 15, 2015-5-11, end */

/* Added by h00313353 for Iteration 17, 2015-7-16, begin */
/*****************************************************************************
 ö����    : NAS_MSCC_PIF_EMC_CALLBACK_MODE_ENUM_UINT32
 �ṹ˵��  : EMC_CALLBACK_MODEö������
 1.��    ��   : 2015��07��16��
   ��    ��   : h00313353
   �޸�����   : �½�
*****************************************************************************/
enum NAS_MSCC_PIF_EMC_CALLBACK_MODE_ENUM
{
    NAS_MSCC_PIF_EMC_CALLBACK_MODE_DISABLE  = 0,
    NAS_MSCC_PIF_EMC_CALLBACK_MODE_ENABLE   = 1,

    NAS_MSCC_PIF_EMC_CALLBACK_MODE_BUTT
};
typedef VOS_UINT32 NAS_MSCC_PIF_EMC_CALLBACK_MODE_ENUM_UINT32;
/* Added by h00313353 for Iteration 17, 2015-7-16, end */

/*****************************************************************************
 ö����    : MMC_MSCC_CL_REG_STATUS_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : CL��VIA��̬ʹ�õ�ATTACHע�����ϱ�ʱ�����Ľ׶�
*****************************************************************************/
enum MMC_MSCC_CL_REG_STATUS_ENUM
{
    MMC_MSCC_CL_REG_STATUS_ATTACH_NOT_SEND            = 0x00,
    MMC_MSCC_CL_REG_STATUS_ATTACH_SEND_WAIT_CN_RSP    = 0x01,
    MMC_MSCC_CL_REG_STATUS_ATTACH_RCV_CN_REJ          = 0x02,
    MMC_MSCC_CL_REG_STATUS_ATTACH_RCV_CN_ACP          = 0x03,
    MMC_MSCC_CL_REG_STATUS_ATTACH_T3410_EXP           = 0x04,
    MMC_MSCC_CL_REG_STATUS_ATTACH_CMP_SEND            = 0x05,

    MMC_MSCC_CL_REG_STATUS_BUTT
};
typedef VOS_UINT8 MMC_MSCC_ATTACH_CL_REG_STATUS_ENUM8;


enum MSCC_MMC_PS_SIGNALING_TYPE_ENUM
{
    MSCC_MMC_PS_SIGNALING_TYPE_GU           = 0,                                /* GU��PS���� */
    MSCC_MMC_PS_SIGNALING_TYPE_LTE          = 1,                                /* LTE��PS���� */

    MSCC_MMC_PS_SIGNALING_TYPE_BUTT
};
typedef VOS_UINT8 MSCC_MMC_PS_SIGNALING_TYPE_ENUM_UINT8;


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
/*******************************************************************************
 * Name        : NAS_MSCC_PIF_CDMA_BAND_STRU
 *
 * Description : CDMA��Ƶ��
 *******************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpBC0_A:1;
    VOS_UINT32                          bitOpBC0_B:1;
    VOS_UINT32                          bitOpBC1:1;
    VOS_UINT32                          bitOpBC2:1;
    VOS_UINT32                          bitOpBC3:1;
    VOS_UINT32                          bitOpBC4:1;
    VOS_UINT32                          bitOpBC5:1;
    VOS_UINT32                          bitOpBC6:1;
    VOS_UINT32                          bitOpBC7:1;
    VOS_UINT32                          bitOpBC8:1;
    VOS_UINT32                          bitOpBC9:1;
    VOS_UINT32                          bitOpBC10:1;
    VOS_UINT32                          bitOpBC11:1;
    VOS_UINT32                          bitOpBC12:1;
    VOS_UINT32                          bitOpBC14:1;
    VOS_UINT32                          bitOpBC15:1;
    VOS_UINT32                          bitOpSpare:16;
}NAS_MSCC_PIF_CDMA_BAND_STRU;


typedef union
{
    VOS_UINT32                          ulCdmaBand;

    NAS_MSCC_PIF_CDMA_BAND_STRU         stCdmaBitBand;
}NAS_MSCC_CDMA_BAND_SET_UN;



typedef struct
{
    VOS_UINT32                          ulMcc;                                  /* MCC,3 bytes */
    VOS_UINT32                          ulMnc;                                  /* MNC,2 or 3 bytes */
}NAS_MSCC_PIF_PLMN_ID_STRU;


typedef struct
{
    NAS_MSCC_PIF_BAND_CLASS_ENUM_UINT16                     enBandClass;
    VOS_UINT16                                              usChannel;
}NAS_MSCC_PIF_FREQENCY_CHANNEL_STRU;


typedef struct
{
    NAS_MSCC_PIF_NET_RAT_TYPE_ENUM_UINT8                    enRat;
    VOS_UINT8                                               aucReserve[3];
    NAS_MSCC_PIF_PLMN_ID_STRU                               stInitAcqPlmnId;
}NAS_MSCC_PIF_INIT_ACQ_PLMN_INFO_STRU;


typedef struct
{
    NAS_MSCC_PIF_NET_RAT_TYPE_ENUM_UINT8                    enRat;                                  /* plmn rat in the plmn list */
    VOS_UINT8                                               ucHighPlmnNum;
    VOS_UINT8                                               ucLowPlmnNum;
    VOS_UINT8                                               aucReserve[1];
    NAS_MSCC_PIF_PLMN_ID_STRU                               astHighPlmnID[NAS_MSCC_PIF_MAX_HIGH_QUALITY_PLMN_NUM];
    NAS_MSCC_PIF_PLMN_ID_STRU                               astLowPlmnID[NAS_MSCC_PIF_MAX_LOW_QUALITY_PLMN_NUM];
}NAS_MSCC_PIF_SEARCHED_PLMN_LIST_INFO_STRU;
typedef struct
{
    NAS_MSCC_PIF_PLMN_ID_STRU                               stPlmnId;
    NAS_MSCC_PIF_PLMN_PRIORITY_CLASS_ENUM_UINT8             enPriClass;
    VOS_UINT8                                               ucIsForbidden;
    VOS_UINT8                                               aucRsv[2];
}NAS_MSCC_PIF_PLMN_PRI_CLASS_INFO_STRU;


typedef struct
{
    NAS_MSCC_PIF_NET_RAT_TYPE_ENUM_UINT8                    enRat;                                  /* plmn rat in the plmn list */
    VOS_UINT8                                               ucHighPlmnNum;
    VOS_UINT8                                               ucLowPlmnNum;
    VOS_UINT8                                               aucReserve[1];
    NAS_MSCC_PIF_PLMN_PRI_CLASS_INFO_STRU                   astHighPlmnPriClassInfo[NAS_MSCC_PIF_MAX_HIGH_QUALITY_PLMN_NUM];
    NAS_MSCC_PIF_PLMN_PRI_CLASS_INFO_STRU                   astLowPlmnPriClassInfo[NAS_MSCC_PIF_MAX_LOW_QUALITY_PLMN_NUM];
}NAS_MSCC_PIF_PLMN_PRI_CLASS_LIST_INFO_STRU;

/*****************************************************************************
 ö����    : NAS_MSCC_PIF_PREF_PLMN_OPERATE_STRU
 �ṹ˵��  : PREFPLMN��������
 1.��    ��   : 2015��02��06��
   ��    ��   : y00307564
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    NAS_MSCC_PIF_PREF_PLMN_TYPE_ENUM_UINT8                  enPrefPLMNType;
    NAS_MSCC_PIF_PREFPLMN_OPERATE_TYPE_ENUM_UINT8           enPrefPlmnOperType;
    NAS_MSCC_USIM_RAT                                       usRat;              /* USIM��ʽ�� ���뼼�� */
    VOS_UINT32                                              ulIndex;
    NAS_MSCC_PIF_PLMN_ID_STRU                               stPlmn;
} NAS_MSCC_PIF_PREF_PLMN_OPERATE_STRU;

/*****************************************************************************
 ö����    : NAS_MSCC_PIF_PREF_PLMN_OPERATE_STRU
 �ṹ˵��  : PREFPLMN��������
 1.��    ��   : 2015��02��06��
   ��    ��   : y00307564
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usPlmnNum;
    VOS_UINT8                           aucReserved[2];
    NAS_MSCC_PIF_PLMN_ID_STRU           Plmn[NAS_MSCC_PIF_MAX_PLMN_NUM];
    NAS_MSCC_USIM_RAT                   ausPlmnRat[NAS_MSCC_PIF_MAX_PLMN_NUM];
}NAS_MSCC_PIF_USER_PLMN_LIST_STRU;


typedef struct
{
    VOS_UINT8                               ucRatNum;                                   /* ��ǰ֧�ֵĽ��뼼������  */
    NAS_MSCC_PIF_NET_RAT_TYPE_ENUM_UINT8    aucRatPrio[NAS_MSCC_PIF_MAX_RAT_NUM];       /* �������ȼ����б� index��ʾ���ȼ�����,0��ߣ�2��� */
#if (FEATURE_OFF == FEATURE_LTE)
    VOS_UINT8                               aucRsv[1];
#endif
}NAS_MSCC_PIF_RAT_PRIO_STRU;


typedef struct
{
    VOS_UINT8                                               ucRatNum;                                   /* ��ǰ֧�ֵĽ��뼼������  */
    NAS_MSCC_PIF_3GPP2_RAT_TYPE_ENUM_UINT8                  auc3GPP2Rat[NAS_MSCC_PIF_3GPP2_RAT_TYPE_BUTT];
    VOS_UINT8                                               aucReserve[1];
}NAS_MSCC_PIF_3GPP2_RAT_STRU;
typedef struct
{
    VOS_UINT8                           ucEquPlmnNum;                           /* ��ǰEquPLMN�ĸ��� */                                                                                /* EPLMN��ɾ����EPLMN����Ϊ0ʱ��Ч,�����������Ч */
    VOS_UINT8                           aucReserved[3];
    NAS_MSCC_PIF_PLMN_ID_STRU           astEquPlmnAddr[NAS_MSCC_PIF_MAX_EQUPLMN_NUM];/* ��ǰEquPLMN�б� */
}NAS_MSCC_PIF_EPLMN_INFO_STRU;



typedef struct
{
    VOS_UINT8                           ucCellNum;
    VOS_UINT8                           aucReserve[3];
    VOS_UINT32                          aulCellId[NAS_MSCC_PIF_CELL_MAX_NUM];
}NAS_MSCC_PIF_CAMP_CELL_INFO_STRU;


typedef struct
{
    NAS_MSCC_PIF_PLMN_ID_STRU           stOperatorPlmnId;
    VOS_UINT8                           aucOperatorNameShort[NAS_MSCC_PIF_MAX_OPER_SHORT_NAME_LEN];/* ��ǰפ��������Ӫ�̵Ķ����� */
    VOS_UINT8                           aucOperatorNameLong[NAS_MSCC_PIF_MAX_OPER_LONG_NAME_LEN];  /* ��ǰפ��������Ӫ�̵ĳ����� */
}NAS_MSCC_PIF_OPERATOR_NAME_INFO_STRU;


typedef struct
{
    WCDMA_BAND_SET_UN                   unWcdmaBand;                            /* wcdma��ǰ����֧�ֵ�Ƶ�� */
    GSM_BAND_SET_UN                     unGsmBand;                              /* gsm��ǰ����֧�ֵ�Ƶ�� */
    LTE_BAND_STRU                       stLteBand;                              /* lte��ǰ����֧�ֵ�Ƶ�� */
    NAS_MSCC_CDMA_BAND_SET_UN           unCdmaBand;                             /* cdma��ǰ����֧�ֵ�Ƶ�� */
}NAS_MSCC_PIF_UE_SUPPORT_FREQ_BAND_STRU;


typedef struct
{
    VOS_INT16                           sRssiValue;
    VOS_INT16                           sRscpValue;
    VOS_UINT8                           ucBer;
    VOS_UINT8                           aucReserved[3];
}NAS_MSCC_PIF_RSSI_VALUE_STRU;


typedef struct
{
    VOS_UINT8                           ucMeasRxlevType          :1;             /* Rxlev�ı䴥���Ĳ����ϱ� */
    VOS_UINT8                           ucMeasRxqualityType      :1;             /* Rxquality�ı䴥���Ĳ����ϱ� */
    VOS_UINT8                           ucMeasCellIdType         :1;             /* Rxquality�ı䴥���Ĳ����ϱ� */
    VOS_UINT8                           ucMeasTypeSpare5         :5;
}NAS_MSCC_PIF_SCELL_MEAS_TYPE_STRU;
typedef union
{
    VOS_UINT8                           ucMeasReportType;

    NAS_MSCC_PIF_SCELL_MEAS_TYPE_STRU   stMeasReportType;
    VOS_UINT8                           aucReserved1[4];
}NAS_MSCC_PIF_SCELL_MEAS_REPORT_TYPE_UN;


typedef struct
{
    MSG_HEADER_STRU                                         MsgHeader;                              /* _H2ASN_Skip */
    VOS_UINT8                                               ucRssiNum;
    VOS_UINT8                                               ucReserved;
    VOS_UINT16                                              usCellDlFreq;                           /*С��Ƶ��(����)*/
    VOS_UINT16                                              usCellUlFreq;                           /*��ǰƵ��(����)*/
    VOS_INT16                                               sUeRfPower;                             /*���书��*/
    NAS_MSCC_PIF_RSSI_VALUE_STRU                            astRssi[NAS_MSCC_PIF_CELL_MAX_NUM];
    NAS_MSCC_PIF_SCELL_MEAS_REPORT_TYPE_UN                  unMeasReportType;                       /* �����ϱ����� */
    NAS_MSCC_PIF_NET_RAT_TYPE_ENUM_UINT8     enRat;                                  /*��ǰ�ϱ��źŵ���ʽ*/
    VOS_UINT8                           aucReserved1[3];
}NAS_MSCC_PIF_RSSI_IND_STRU;


typedef struct
{
    VOS_UINT16                          usRI;                                   /* RI */
    VOS_UINT8                           aucRes[2];
    VOS_UINT16                          ausCQI[2];                              /* CQI�������� */

}NAS_MSCC_PIF_CQI_INFO_STRU;


typedef struct
{
    VOS_INT16                           sRssi;                                  /* Rssi*/
    VOS_INT16                           sRsd;                                   /* ����ֶ�*/
    VOS_INT16                           sRsrp;                                  /* ��Χ��(-141,-44), 99Ϊ��Ч */
    VOS_INT16                           sRsrq;                                  /* ��Χ��(-40, -6) , 99Ϊ��Ч */
    VOS_INT32                           lSINR;                                  /* SINR RS_SNR */
    NAS_MSCC_PIF_CQI_INFO_STRU          stCQI;                                  /* Channle Quality Indicator*/
}NAS_MSCC_PIF_LMM_CELL_SIGN_INFO_STRU;


typedef struct
{
    MSG_HEADER_STRU                               MsgHeader;                    /* _H2ASN_Skip */

    NAS_MSCC_PIF_SCELL_MEAS_REPORT_TYPE_UN        unMeasReportType;             /* �����ϱ����� */
    NAS_MSCC_PIF_LMM_CELL_SIGN_INFO_STRU          stLteRssi;                    /* LTE cell Signal INFO */
}NAS_MSCC_PIF_LMM_CELL_SIGN_INFO_REPORT_IND_STRU;
typedef struct
{
    MSG_HEADER_STRU                                         MsgHeader;          /* _H2ASN_Skip */
    NAS_MSCC_PIF_START_RESULT_ENUM_UINT32                   ulResult;
}NAS_MSCC_PIF_START_CNF_STRU;
typedef struct
{
    MSG_HEADER_STRU                                         MsgHeader;                              /* _H2ASN_Skip */
    NAS_MSCC_PIF_PLMN_ID_STRU                               stPlmnId;
    NAS_MSCC_PIF_NET_RAT_TYPE_ENUM_UINT8                    enCurNetWork;                           /* ��ǰ�������� */
    VOS_UINT8                                               ucRac;
    VOS_UINT8                                               ucSysSubMode;                           /* פ�������ϵͳ��ģʽ��ȡֵ��RRC_NAS_SYS_SUBMODE_ENUM��ͬ */
    VOS_UINT8                                               ucIsFobbiddenPlmnFlag;
    VOS_UINT16                                              usLac;                                  /* λ������Ϣ */
    VOS_UINT8                                               ucRoamFlag;                             /* ��ǰ�Ƿ������� */
    VOS_UINT8                                               ucPsSupportFlg;                         /* ��ǰ�Ƿ�֧��PS�� */
    NAS_MSCC_PIF_CAMP_CELL_INFO_STRU                        stCellId;                               /* С����Ϣ */
    VOS_UINT8                                               ucPsAttachAllowFlag;
    VOS_UINT8                                               ucCsAttachAllowFlag;
    NAS_MSCC_PIF_PLMN_PRIORITY_CLASS_ENUM_UINT8             enPrioClass;
    NAS_MSCC_PIF_LMM_ACCESS_TYPE_ENUM_UINT8                 enLmmAccessType;
    VOS_UINT32                                              ulArfcn;
}NAS_MSCC_PIF_3GPP_SYS_INFO_IND_STRU;

typedef VOS_UINT16 NAS_MSCC_PIF_REG_FAIL_CAUSE_UINT16;

typedef struct
{
    MSG_HEADER_STRU                          MsgHeader;                              /*_H2ASN_Skip*/
    NAS_MSCC_PIF_SRVDOMAIN_ENUM_UINT32       enCnDomainId;
    VOS_UINT8                                ucRegRslt;                              /* VOS_TRUE:ָ����ע��ɹ�; ��֮ע��ʧ�� */
    VOS_UINT8                                ucReportCauseCtrl;                      /* �Ƿ���Ҫ�ϱ�ԭ��ֵ */
    NAS_MSCC_PIF_REG_FAIL_CAUSE_UINT16       enRejCause;
    /* Added by g00322017 for SEARCH_NW_CHR_OPT, 2015-8-17, begin */
    VOS_UINT8                                ucOriginalRejCause;
    VOS_UINT8                                aucReserve[3];
    /* Added by g00322017 for SEARCH_NW_CHR_OPT, 2015-8-17, end */
}NAS_MSCC_PIF_REG_RESULT_IND_STRU;

typedef VOS_UINT16 NAS_MSCC_PIF_SIM_AUTH_FAIL_UINT16;
typedef struct
{
    MSG_HEADER_STRU                             MsgHeader;                      /* _H2ASN_Skip */
    NAS_MSCC_PIF_SRVDOMAIN_ENUM_UINT32          enCnDomainId;
    NAS_MSCC_PIF_SIM_AUTH_FAIL_UINT16           enRejCause;
    VOS_UINT8                                   aucReserve[2];
}NAS_MSCC_PIF_USIM_AUTH_FAIL_IND_STRU;
typedef struct
{
    MSG_HEADER_STRU                              MsgHeader;                     /* _H2ASN_Skip */
    VOS_UINT32                                   bitOpSrvSta     : 1;
    VOS_UINT32                                   bitOpRegSta     : 1;
    VOS_UINT32                                   bitSpare        : 30;

    NAS_MSCC_PIF_SRVDOMAIN_ENUM_UINT32           enCnDomainId;
    VOS_UINT8                                    ucSimCsRegStatus;
    VOS_UINT8                                    ucSimPsRegStatus;
    VOS_UINT8                                    aucReserved[1];
    NAS_MSCC_PIF_REG_STATE_ENUM_UINT8            enRegState;
    NAS_MSCC_PIF_SERVICE_STATUS_ENUM_UINT32      enServiceStatus;
    VOS_UINT32                                   ulOosCause;
}NAS_MSCC_PIF_SERVICE_STATUS_IND_STRU;
typedef struct
{
    MSG_HEADER_STRU                                         MsgHeader;          /* _H2ASN_Skip */
    VOS_UINT8                                               ucIeFlg;
    VOS_INT8                                                cLocalTimeZone;
    VOS_UINT8                                               ucDST;
    VOS_UINT8                                               aucLSAID[3];
    VOS_UINT8                                               aucReserve[2];
    TIME_ZONE_TIME_STRU                                     stUniversalTimeandLocalTimeZone;
    NAS_MSCC_PIF_OPERATOR_NAME_INFO_STRU                    stName;
}NAS_MSCC_PIF_MM_INFO_IND_STRU;
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* _H2ASN_Skip */
    VOS_UINT8                           ucActionType;
    VOS_UINT8                           ucRrcMsgType;
    VOS_UINT8                           ucSignThreshold;                        /* �ź������ı�����ֵ */
    VOS_UINT8                           ucMinRptTimerInterval;                  /* ����ϱ���ʱ��   */
}NAS_MSCC_PIF_SIGN_REPORT_REQ_STRU;
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* _H2ASN_Skip */
    NAS_MSCC_PIF_MS_MODE_ENUM_UINT32    enMsMode;
}NAS_MSCC_PIF_MODE_CHANGE_REQ_STRU;
typedef struct
{
    MSG_HEADER_STRU                                         MsgHeader;          /* _H2ASN_Skip */
    VOS_UINT32                                              ulOpID;
    NAS_MSCC_PIF_ATTACH_TYPE_ENUM_UINT32                    enAttachType;
    NAS_MSCC_PIF_EPS_ATTACH_REASON_ENUM_UINT32              enEpsAttachReason;
}NAS_MSCC_PIF_ATTACH_REQ_STRU;
typedef struct
{
    MSG_HEADER_STRU                                         MsgHeader;          /* _H2ASN_Skip */
    VOS_UINT32                                              ulOpID;
    NAS_MSCC_PIF_SRVDOMAIN_ENUM_UINT32                      enCnDomainId;
    NAS_MSCC_PIF_SERVICE_STATUS_ENUM_UINT32                 enServiceStatus;
    NAS_MSCC_PIF_PLMN_ID_STRU                               stPlmnId;
}NAS_MSCC_PIF_ATTACH_CNF_STRU;
typedef struct
{
    MSG_HEADER_STRU                                         MsgHeader;          /* _H2ASN_Skip */
    VOS_UINT32                                              ulOpID;
    NAS_MSCC_PIF_DETACH_TYPE_ENUM_UINT32                    enDetachType;
    NAS_MSCC_PIF_DETACH_REASON_ENUM_UINT32                  enDetachReason;
}NAS_MSCC_PIF_DETACH_REQ_STRU;
typedef struct
{
    MSG_HEADER_STRU                                         MsgHeader;          /* _H2ASN_Skip */
    VOS_UINT32                                              ulOpID;
    NAS_MSCC_PIF_SRVDOMAIN_ENUM_UINT32                      enCnDomainId;
    NAS_MSCC_PIF_SERVICE_STATUS_ENUM_UINT32                 enServiceStatus;
}NAS_MSCC_PIF_DETACH_CNF_STRU;
typedef struct
{
    MSG_HEADER_STRU                                         MsgHeader;          /* _H2ASN_Skip */
    NAS_MSCC_PIF_SRVDOMAIN_ENUM_UINT32                      enCnDomainId;
    NAS_MSCC_PIF_SERVICE_STATUS_ENUM_UINT32                 enServiceStatus;
    VOS_UINT32                                              ulDetachCause;
    NAS_MSCC_PIF_NETWORK_DETACH_TYPE_ENUM_UINT8             enNetworkDetachType;
    /* Added by g00322017 for SEARCH_NW_CHR_OPT, 2015-8-17, begin */
    VOS_UINT8                                               ucOriginalDetachCause;
    /* Added by g00322017 for SEARCH_NW_CHR_OPT, 2015-8-17, end */
    VOS_UINT8                                               aucReserved[2];

}NAS_MSCC_PIF_DETACH_IND_STRU;


typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* _H2ASN_Skip */
    VOS_UINT32                          ulReserved;
}NAS_MSCC_PIF_PLMN_LIST_REQ_STRU;
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* _H2ASN_Skip */
    VOS_UINT32                          ulCnt;
    NAS_MSCC_PIF_PLMN_ID_STRU           aPlmnList[NAS_MSCC_PIF_MAX_PLMN_CNT];
    VOS_UINT8                           aucPlmnStatus[NAS_MSCC_PIF_MAX_PLMN_CNT];
    VOS_UINT8                           aucRaMode[NAS_MSCC_PIF_MAX_PLMN_CNT];
    VOS_UINT8                           aucReserve[2];
}NAS_MSCC_PIF_PLMN_LIST_CNF_STRU;
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* _H2ASN_Skip */
    VOS_UINT32                          ulReserved;
}NAS_MSCC_PIF_PLMN_LIST_REJ_STRU;
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* _H2ASN_Skip */
    VOS_UINT32                          ulReserved;
}NAS_MSCC_PIF_PLMN_LIST_ABORT_REQ_STRU;
typedef struct
{
    MSG_HEADER_STRU                                         MsgHeader;          /* _H2ASN_Skip */
    NAS_MSCC_PIF_PLMN_SEL_MODE_ENUM_UINT32                  enPlmnSelMode;
}NAS_MSCC_PIF_PLMN_USER_RESEL_REQ_STRU;
typedef struct
{
    MSG_HEADER_STRU                                         MsgHeader;          /* _H2ASN_Skip */
    NAS_MSCC_PIF_PLMN_ID_STRU                               stPlmnId;
    NAS_MSCC_PIF_NET_RAT_TYPE_ENUM_UINT8                    enAccessMode;
    VOS_UINT8                                               aucReserved[3];
}NAS_MSCC_PIF_PLMN_SPECIAL_REQ_STRU;
typedef struct
{
    MSG_HEADER_STRU                                         MsgHeader;          /* _H2ASN_Skip */
    NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_ENUM_UINT32      enCoverageChgMode;
    NAS_MSCC_PIF_PLMN_ID_STRU                               stPlmnId;
    NAS_MSCC_PIF_SERVICE_STATUS_ENUM_UINT32                 enCsSvcSta;
    NAS_MSCC_PIF_SERVICE_STATUS_ENUM_UINT32                 enPsSvcSta;
    VOS_UINT32                                              ulTimMaxFlg;
}NAS_MSCC_PIF_COVERAGE_AREA_IND_STRU;
typedef struct
{
    MSG_HEADER_STRU                                         MsgHeader;          /* _H2ASN_Skip */
    NAS_MSCC_PIF_POWER_OFF_CAUSE_ENUM_UINT32                enCause;
}NAS_MSCC_PIF_POWER_OFF_REQ_STRU;
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* _H2ASN_Skip */
    VOS_UINT32                          ulReserved;
}NAS_MSCC_PIF_POWER_OFF_CNF_STRU;
typedef struct
{
    MSG_HEADER_STRU                                         stMsgHeader;        /* _H2ASN_Skip */
    MSCC_MMA_SYSTEM_ACQUIRE_RESULT_ENUM_UINT32              enResult;
}NAS_MSCC_PIF_SYSTEM_ACQUIRE_CNF_STRU;
typedef struct
{
    MSG_HEADER_STRU                                 MsgHeader;                  /* _H2ASN_Skip */
    NAS_MSCC_PIF_USER_PLMN_SEARCH_RESULT_ENUM_UINT8 enResult;
    VOS_UINT8                                       aucReserved[3];
}NAS_MSCC_PIF_PLMN_SPECIAL_SEL_CNF_STRU;
typedef struct
{
    MSG_HEADER_STRU                                         MsgHeader;          /* _H2ASN_Skip */
    NAS_MSCC_PIF_USER_PLMN_SEARCH_RESULT_ENUM_UINT8         enResult;
    VOS_UINT8                                               aucReserved[3];
}NAS_MSCC_PIF_PLMN_RESEL_CNF_STRU;
typedef struct
{
    MSG_HEADER_STRU                                         MsgHeader;          /* _H2ASN_Skip */
    NAS_MSCC_PIF_DATATRAN_ATTRI_ENUM_UINT8                  enDataTranAttri;
    VOS_UINT8                                               aucReserved[3];
}NAS_MSCC_PIF_DATATRAN_ATTRI_IND_STRU;
typedef struct
{
    MSG_HEADER_STRU                                         MsgHeader;          /* _H2ASN_Skip */
    NAS_MSCC_PIF_RAT_PRIO_STRU                              stRatPrioList;
    NAS_MSCC_PIF_UE_SUPPORT_FREQ_BAND_STRU                  stBand;
    NAS_MSCC_PIF_ROAM_CAPABILITY_ENUM_UINT8                 enRoamCapability;
    VOS_UINT8                                               ucOnlyRoamParaChanged;
    VOS_UINT8                                               ucIsNeedAttachPs;
    VOS_UINT8                                               aucReserved[1];
}NAS_MSCC_PIF_SYS_CFG_SET_REQ_STRU;
typedef struct
{
    MSG_HEADER_STRU                                         MsgHeader;          /* _H2ASN_Skip */
    NAS_MSCC_PIF_SYS_CFG_SET_RESULT_ENUM_UINT32             enRst;
    VOS_UINT16                                              usOpId;
    VOS_UINT8                                               aucReserved[2];
}NAS_MSCC_PIF_SYS_CFG_SET_CNF_STRU;
typedef struct
{
    MSG_HEADER_STRU                                         MsgHeader;                              /* _H2ASN_Skip */
    NAS_MSCC_PIF_ACQ_REASON_ENUM_UINT32                     enAcqReason;
    NAS_MSCC_PIF_INIT_ACQ_PLMN_INFO_STRU                    stInitAcqPlmnInfo;
    NAS_MSCC_PIF_SEARCHED_PLMN_LIST_INFO_STRU               stHighPrioPlmnList;
}NAS_MSCC_PIF_PLMN_SEARCH_REQ_STRU;


typedef NAS_MSCC_PIF_PLMN_SEARCH_REQ_STRU MMA_MSCC_SYSTEM_ACQUIRE_REQ_STRU;
typedef struct
{
    MSG_HEADER_STRU                                         MsgHeader;          /* _H2ASN_Skip */
    NAS_MSCC_PIF_PLMN_SELECTION_RESULT_ENUM_UINT32          enResult;
    VOS_UINT8                                               ucLteCoverageFlg;   /* VOS_TRUE:lte exist coverage; VOS_FALSE:LTE exist no coverage */
    VOS_UINT8                                               aucRsv[3];
}NAS_MSCC_PIF_PLMN_SELECTION_RLST_IND_STRU;


typedef struct
{
    MSG_HEADER_STRU                                         MsgHeader;          /* _H2ASN_Skip */
    NAS_MSCC_PIF_PLMN_SELECTION_START_FLAG_ENUM_UINT32      enPlmnSeleStartFlag;
}NAS_MSCC_PIF_PLMN_SELECTION_START_IND_STRU;
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* _H2ASN_Skip */
    VOS_UINT32                          ulCnt;
    NAS_MSCC_PIF_PLMN_ID_STRU           aPlmnList[NAS_MSCC_PIF_MAX_PLMN_CNT];
    VOS_UINT8                           aucPlmnStatus[NAS_MSCC_PIF_MAX_PLMN_CNT];
    VOS_UINT8                           aucReserved1[3];
    VOS_UINT8                           aucRaMode[NAS_MSCC_PIF_MAX_PLMN_CNT];
    VOS_UINT8                           aucReserved2[3];
}NAS_MSCC_PIF_PLMN_LIST_ABORT_CNF_STRU;
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* _H2ASN_Skip */
    VOS_UINT32                          ulReserved;
}NAS_MSCC_PIF_SPEC_PLMN_SEARCH_ABORT_REQ_STRU;
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* _H2ASN_Skip */
    VOS_UINT32                          ulReserved;
}NAS_MSCC_PIF_SPEC_PLMN_SEARCH_ABORT_CNF_STRU;
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* _H2ASN_Skip */
    VOS_UINT8                           ucCipherAlgorForCSDomain;
    VOS_UINT8                           ucCipherAlgorForPSDomain;
    VOS_UINT8                           aucRcv[2];
}NAS_MSCC_PIF_UMTS_CIPHER_INFO_IND_STRU;
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* _H2ASN_Skip */
    VOS_UINT8                           ucGprsCipherAlg;
    VOS_UINT8                           ucGprsCipher;
    VOS_UINT8                           aucRcv[2];
}NAS_MSCC_PIF_GPRS_CIPHER_INFO_IND_STRU;
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* _H2ASN_Skip */
    VOS_UINT32                          ulReserved;
}NAS_MSCC_PIF_PLMN_SPECIAL_SEL_REJ_STRU;
typedef struct
{
    MSG_HEADER_STRU                                         MsgHeader;          /* _H2ASN_Skip */
    NAS_MSCC_PIF_CELL_RESTRICTION_TYPE_ENUM_UINT8           enCellAcType;
    VOS_UINT8                                               ucRestrictRegister;
    VOS_UINT8                                               ucRestrictPagingRsp;
    VOS_UINT8                                               ucReserved;
    NAS_MSCC_PIF_SRVDOMAIN_ENUM_UINT32                      enCnDomainId;
}NAS_MSCC_PIF_AC_INFO_CHANGE_IND_STRU;
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* _H2ASN_Skip */

    VOS_UINT8                           ucOmConnectFlg;                         /* UE��PC���ߵ����ӱ�־, VOS_TRUE: ������; VOS_FALSE: δ���� */
    VOS_UINT8                           ucOmPcRecurEnableFlg;                   /* OM���õķ���NAS PC�ط���Ϣ��ʹ�ܱ�־ */
    VOS_UINT8                           aucRsv2[2];                             /* ����   */
} NAS_MSCC_PIF_OM_MAINTAIN_INFO_IND_STRU;


typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* _H2ASN_Skip */
    VOS_UINT8                           aucRsv4[4];                             /* ����   */
}NAS_MSCC_PIF_UPDATE_UPLMN_NTF_STRU;


typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* _H2ASN_Skip */
    TAF_UINT8                           aucVersion[NAS_MSCC_PIF_MAX_USER_OPLMN_VERSION_LEN];        /* OPLMN List�汾�� */
    TAF_UINT8                           ucIndex;                                /* ��ǰ���õ���Index */
    TAF_UINT8                           ucOPlmnCount;                           /* ����ʵ������OPLMN�ĸ��� */
    TAF_UINT8                           aucOPlmnWithRat[NAS_MSCC_PIF_MAX_GROUP_CFG_OPLMN_DATA_LEN];  /* OPLMN��PDU���ݣ���EFOplmn�ļ�һ�� */
}NAS_MSCC_PIF_EOPLMN_SET_REQ_STRU;
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* _H2ASN_Skip */
    VOS_UINT32                          ulResult;                               /* OPLMN��nv������*/
}NAS_MSCC_PIF_EOPLMN_SET_CNF_STRU;


typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* _H2ASN_Skip */
    VOS_UINT32                          ulReserved;
}NAS_MSCC_PIF_EOPLMN_SET_ABORT_STRU;
typedef struct
{
    MSG_HEADER_STRU                                         MsgHeader;          /* _H2ASN_Skip */

    VOS_UINT16                                              usCellNum;          /* ��Ҫɨ����������޵�С������ */
    VOS_INT16                                               sCellPow;           /* С������ֵ */
    NAS_MSCC_PIF_NET_RAT_TYPE_ENUM_UINT8                    ucRat;              /* ��Ҫɨ��Ľ���ģʽ */
    VOS_UINT8                                               aucReserve[3];
    NAS_MSCC_PIF_UE_SUPPORT_FREQ_BAND_STRU                  stBand;             /* ��¼GUƵ��*/
}NAS_MSCC_PIF_NET_SCAN_REQ_STRU;
typedef struct
{
    VOS_UINT16                                              usArfcn;                                /* Ƶ�� */
    VOS_UINT16                                              usC1;                                   /* ����GSMС����ѡ��C1ֵ(�ݲ�֧��) */
    VOS_UINT16                                              usC2;                                   /* ����GSMС����ѡ��C2ֵ(�ݲ�֧��) */
    VOS_UINT16                                              usLac;                                  /* λ������ */
    VOS_UINT32                                              ulMcc;                                  /* PLMN������ */
    VOS_UINT32                                              ulMnc;                                  /* PLMN������ */
    VOS_UINT16                                              usBsic;                                 /* GSMС����վ�� */
    VOS_INT16                                               sRxlev;                                 /* ���յ����ź�ǿ�� */
    VOS_INT16                                               sRssi;                                  /* GSM��BCCH�ŵ���RSSI��WCDMA��RSCP */
    VOS_UINT8                                               aucReserve[2];
    VOS_UINT32                                              ulCellId;                               /* С��ID */
    NAS_MSCC_PIF_UE_SUPPORT_FREQ_BAND_STRU                  stBand;                               /* ����ȡֵͬ�ӿ�RRMM_SYS_CFG_REQ_STRU��Ƶ�β��� */
}NAS_MSCC_PIF_NET_SCAN_INFO_STRU;
typedef struct
{
    MSG_HEADER_STRU                                         MsgHeader;          /* _H2ASN_Skip */

    NAS_MSCC_PIF_NET_SCAN_RESULT_ENUM_UINT8                 enResult;
    NAS_MSCC_PIF_NET_SCAN_CAUSE_ENUM_UINT8                  enCause;
    VOS_UINT8                                               ucFreqNum;          /* �ϱ���Ƶ����� */
    VOS_UINT8                                               aucReserve[1];
    NAS_MSCC_PIF_NET_SCAN_INFO_STRU                         astNetScanInfo[NAS_MSCC_PIF_NET_SCAN_MAX_FREQ_NUM];
}NAS_MSCC_PIF_NET_SCAN_CNF_STRU;


typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* _H2ASN_Skip */
    NAS_MSCC_PIF_SRVDOMAIN_ENUM_UINT32  enCnDomainId;
    VOS_UINT16                          usRejCause;
    /* Added by g00322017 for SEARCH_NW_CHR_OPT, 2015-8-17, begin */
    VOS_UINT8                           ucOriginalRejCause;
    VOS_UINT8                           aucReserve[1];
    /* Added by g00322017 for SEARCH_NW_CHR_OPT, 2015-8-17, end */
}NAS_MSCC_PIF_SERV_REJ_IND_STRU;
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* _H2ASN_Skip */
    VOS_UINT32                          ulReserved;
}NAS_MSCC_PIF_ABORT_NET_SCAN_REQ_STRU;
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* _H2ASN_Skip */

    VOS_UINT8                           ucFreqNum;                                      /* �ϱ���Ƶ����� */
    VOS_UINT8                           aucReserve[3];
    NAS_MSCC_PIF_NET_SCAN_INFO_STRU     astNetScanInfo[NAS_MSCC_PIF_NET_SCAN_MAX_FREQ_NUM];
}NAS_MSCC_PIF_ABORT_NET_SCAN_CNF_STRU;


typedef struct
{
    MSG_HEADER_STRU                                         MsgHeader;          /* _H2ASN_Skip */
    NAS_MSCC_PIF_NW_IMS_VOICE_CAP_ENUM_UINT8                enNwImsVoCap ;
    NAS_MSCC_PIF_NW_EMC_BS_CAP_ENUM_UINT8                   enNwEmcBsCap ;
    NAS_MSCC_PIF_LTE_CS_CAPBILITY_ENUM_UINT8                enLteCsCap ;
    VOS_UINT8                                               aucReserve[1];
}NAS_MSCC_PIF_NETWORK_CAPABILITY_INFO_IND_STRU;
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* _H2ASN_Skip */
    VOS_UINT8                           ucCampOnFlg;                            /* VOS_TRUE:פ��;VOS_FALSE:δפ�� */
    VOS_UINT8                           aucRsv[3];                              /* ����   */
}NAS_MSCC_PIF_CAMP_ON_IND_STRU_STRU;
typedef struct
{
    MSG_HEADER_STRU              stMsgHeader;                                   /*_H2ASN_Skip*/
    VOS_UINT32                   bitOpCurrCampPlmnId:1;

    VOS_UINT32                   bitOpEplmnInfo:1;
    VOS_UINT32                   bitSpare:30;

    NAS_MSCC_PIF_PLMN_ID_STRU    stCurrCampPlmnId;                              /* ������д��ǰפ��С����PLMN������������߹ػ��ȷ�פ��״̬��ͳһ��дȫ0xff */
    NAS_MSCC_PIF_EPLMN_INFO_STRU stEplmnInfo;
} NAS_MSCC_PIF_OTHER_MODEM_INFO_NOTIFY_STRU;


typedef struct
{
    MSG_HEADER_STRU                                        stMsgHeader;         /*_H2ASN_Skip*/
    NAS_MMC_NVIM_CFG_DPLMN_NPLMN_INFO_STRU                 stCmccDplmnNplmnInfo;
    NAS_MMC_NVIM_CFG_DPLMN_NPLMN_INFO_STRU                 stUnicomDplmnNplmnInfo;
    NAS_MMC_NVIM_CFG_DPLMN_NPLMN_INFO_STRU                 stCtDplmnNplmnInfo;
} NAS_MSCC_PIF_OTHER_MODEM_DPLMN_NPLMN_INFO_NOTIFY_STRU;
typedef struct
{
    VOS_UINT8                           ucTdsArfcnNum;                          /* 0��ʾTDDƵ�㲻���� */
    VOS_UINT8                           ucReserved;
    VOS_UINT16                          ausTdsArfcnList[NAS_MSCC_PIF_TDS_ARFCN_MAX_NUM];
}NAS_MSCC_PIF_TDS_NCELL_INFO_STRU;
typedef struct
{
    VOS_UINT8                           ucLteArfcnNum;                          /* 0��ʾLTEƵ�㲻���� */
    VOS_UINT8                           aucReserved[3];
    VOS_UINT32                          aulLteArfcnList[NAS_MSCC_PIF_LTE_ARFCN_MAX_NUM];
}NAS_MSCC_PIF_LTE_NCELL_INFO_STRU;
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /*_H2ASN_Skip*/
    NAS_MSCC_PIF_TDS_NCELL_INFO_STRU    stTdsNcellInfo;
    NAS_MSCC_PIF_LTE_NCELL_INFO_STRU    stLteNcellInfo;
}NAS_MSCC_PIF_NCELL_INFO_NOTIFY_STRU;
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /*_H2ASN_Skip*/
    NAS_MSCC_PIF_EPLMN_INFO_STRU        stEplmnInfo;
}NAS_MSCC_PIF_EPLMN_INFO_IND_STRU;
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /*_H2ASN_Skip*/
    VOS_UINT8                           ucCsServiceConnStatusFlag;
    VOS_UINT8                           aucReserved[3];
}NAS_MSCC_PIF_CS_SERVICE_CONN_STATUS_IND_STRU;
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /*_H2ASN_Skip*/
    MTC_PS_TRANSFER_ENUM_UINT8          enSolutionCfg;                          /* PS��Ǩ�Ʒ��� */
    VOS_UINT8                           ucCause;                                /* PS���л�ԭ��ֵ */
    VOS_UINT8                           aucReserved[2];                         /*����λ*/
} NAS_MSCC_PIF_PS_TRANSFER_NOTIFY_STRU;


typedef struct
{
    MSG_HEADER_STRU                                         MsgHeader;          /* _H2ASN_Skip */

    VOS_UINT8                                               ucAvail;            /* IMS VOICE�Ƿ���� */

    VOS_UINT8                                               ucIsExistPersistentBearer;  /* 0:�����ڣ�1������*/
    VOS_UINT8                                               aucRsv[2];
}NAS_MSCC_PIF_IMS_VOICE_CAP_NOTIFY_STRU;
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* _H2ASN_Skip */
    NAS_MSCC_PIF_ACQ_REASON_ENUM_UINT32 enAcqReason;
    VOS_UINT8                           ucNotRegAfterAcqSucc;                  /* �����ɹ����Ƿ���ע��:
                                                                                   VOS_FALSE:�����ɹ�����ע��(default)
                                                                                   VOS_TRUE:�����ɹ��󲻷���ע�� */
    VOS_UINT8                           aucRsv[3];
}NAS_MSCC_PIF_ACQ_REQ_STRU;


typedef struct
{
    MSG_HEADER_STRU                                         stMsgHeader;        /* _H2ASN_Skip */
    NAS_MSCC_PIF_ACQ_RESULT_ENUM_UINT32                     enAcqRslt;
    NAS_MSCC_PIF_PLMN_ID_STRU                               stPlmnId;
    VOS_UINT32                                              ulArfcn;
    NAS_MSCC_PIF_PLMN_PRIORITY_CLASS_ENUM_UINT8             enPrioClass;
    VOS_UINT8                                               aucReserve[3];
}NAS_MSCC_PIF_ACQ_CNF_STRU;
typedef struct
{
    NAS_MSCC_PIF_NET_RAT_TYPE_ENUM_UINT8       ucRat;
    VOS_UINT8                                  ucPlmnNum;
    VOS_UINT8                                  ucCellNum;
    VOS_UINT8                                  aucReserved[1];
    VOS_UINT32                                 ulArfcn;
    NAS_MSCC_PIF_PLMN_ID_STRU                  astPlmnId[NAS_MSCC_PIF_REG_MAX_PLMN_NUM];
    VOS_UINT16                                 ausCellId[NAS_MSCC_PIF_REG_MAX_CELL_NUM];
} NAS_MSCC_PIF_REG_CELL_INFO_STRU;


typedef struct
{
    MSG_HEADER_STRU                                         stMsgHeader;        /* _H2ASN_Skip */
    VOS_UINT32                                              bitOpPrioClass  : 1;
    VOS_UINT32                                              bitOpCellInfo   : 1;
    VOS_UINT32                                              bitSpare        : 30;
    NAS_MSCC_PIF_PLMN_PRIORITY_CLASS_ENUM_UINT8             enPrioClass;
    VOS_UINT8                                               aucReserve[3];
    NAS_MSCC_PIF_REG_CELL_INFO_STRU                         stCellInfo;
}NAS_MSCC_PIF_REG_REQ_STRU;
typedef struct
{
    MSG_HEADER_STRU                                         stMsgHeader;        /* _H2ASN_Skip */
    NAS_MSCC_PIF_REG_RESULT_ENUM_UINT32                     enRegRslt;
    NAS_MSCC_PIF_PLMN_ID_STRU                               stPlmnId;
    VOS_UINT32                                              ulArfcn;
    NAS_MSCC_PIF_PLMN_PRIORITY_CLASS_ENUM_UINT8             enPrioClass;
    MMC_MSCC_ATTACH_CL_REG_STATUS_ENUM8                     enLmmAttachClRegStatus;
    VOS_UINT8                                               aucReserve[2];
}NAS_MSCC_PIF_REG_CNF_STRU;


enum NAS_MSCC_POWER_SAVE_RESULT_ENUM
{
    NAS_MSCC_PIF_POWER_SAVE_SUCCESS             = 0 ,
    NAS_MSCC_PIF_POWER_SAVE_FAILURE             = 1 ,
    NAS_MSCC_PIF_POWER_SAVE_BUTT
};
typedef VOS_UINT8 NAS_MSCC_PIF_POWER_SAVE_RESULT_ENUM_UINT8;


typedef struct
{
    MSG_HEADER_STRU                            stMsgHeader;                     /* _H2ASN_Skip */
    VOS_UINT8                                  aucReserve[4];
}NAS_MSCC_PIF_POWER_SAVE_REQ_STRU;
typedef struct
{
    MSG_HEADER_STRU                                         stMsgHeader;                     /* _H2ASN_Skip */
    NAS_MSCC_PIF_POWER_SAVE_RESULT_ENUM_UINT8               enResult;
    VOS_UINT8                                               aucReserve[3];
}NAS_MSCC_PIF_POWER_SAVE_CNF_STRU;
typedef  NAS_MSCC_PIF_ACQ_CNF_STRU NAS_MSCC_PIF_ACQ_IND_STRU;


typedef struct
{
    MSG_HEADER_STRU                                 stMsgHeader;                            /*_H2ASN_Skip*/
    VOS_UINT8                                       ucPsServiceConnStatusFlag;
    MSCC_MMC_PS_SIGNALING_TYPE_ENUM_UINT8           enPsSigType;
    VOS_UINT8                                       aucReserved[2];
}NAS_MSCC_PIF_PS_SERVICE_CONN_STATUS_IND_STRU;
typedef struct
{
    MSG_HEADER_STRU                                         stMsgHeader;        /*_H2ASN_Skip*/
    /* Modified by l00301449 for CDMA Iteration 15, 2015-5-16, begin */
    NAS_MSCC_PIF_RF_AVAILABLE_RAT_TYPE_ENUM_UINT8           enRatType;
    VOS_UINT8                                               ucRfAvailFlg;       /* VOS_TRUE:��Ƶ��Դ����;VOS_FALSE:RF��Դ������ */
    VOS_UINT8                                               aucReserved[2];
    /* Modified by l00301449 for CDMA Iteration 15, 2015-5-16, end */
}NAS_MSCC_PIF_RF_AVAILABLE_IND_STRU;

/* Modified by l00301449 for CDMA Iteration 15, 2015-5-15, begin */
/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_SRV_ACQ_RAT_LIST_STRU
 �ṹ˵��  : ҵ�񴥷�����������ģʽ�б�
 1.��    ��   : 2015��5��15��
   ��    ��   : L00301449
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucRatNum;
    NAS_MSCC_PIF_SRV_ACQ_RAT_TYPE_ENUM_UINT8                aenRatType[NAS_MSCC_PIF_SRV_ACQ_RAT_NUM_MAX];
}NAS_MSCC_PIF_SRV_ACQ_RAT_LIST_STRU;
/* Modified by l00301449 for CDMA Iteration 15, 2015-5-15, end */

typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /*_H2ASN_Skip*/
    NAS_MSCC_PIF_SRV_TYPE_ENUM_UINT8    enSrvType;
    VOS_UINT8                           aucReserved[3];
    /* Modified by l00301449 for CDMA Iteration 15, 2015-5-15, begin */
    NAS_MSCC_PIF_SRV_ACQ_RAT_LIST_STRU  stRatList;
    /* Modified by l00301449 for CDMA Iteration 15, 2015-5-15, end */
} NAS_MSCC_PIF_SRV_ACQ_REQ_STRU;
typedef struct
{
    MSG_HEADER_STRU                                 stMsgHeader;                /*_H2ASN_Skip*/
    NAS_MSCC_PIF_SRV_ACQ_RESULT_ENUM_UINT8          enResult;
    VOS_UINT8                                       aucReserved[3];
} NAS_MSCC_PIF_SRV_ACQ_CNF_STRU;
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /*_H2ASN_Skip*/
    NAS_MSCC_PIF_SRV_TYPE_ENUM_UINT8    enSrvType;
    VOS_UINT8                           aucReserved[3];
    /* Modified by l00301449 for CDMA Iteration 15, 2015-5-15, begin */
    NAS_MSCC_PIF_SRV_ACQ_RAT_LIST_STRU  stRatList;
    /* Modified by l00301449 for CDMA Iteration 15, 2015-5-15, end */
}NAS_MSCC_PIF_BEGIN_SESSION_NOTIFY_STRU;
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /*_H2ASN_Skip*/
    NAS_MSCC_PIF_SRV_TYPE_ENUM_UINT8    enSrvType;
    VOS_UINT8                           aucReserved[3];
    /* Modified by l00301449 for CDMA Iteration 15, 2015-5-15, begin */
    NAS_MSCC_PIF_SRV_ACQ_RAT_LIST_STRU  stRatList;
    /* Modified by l00301449 for CDMA Iteration 15, 2015-5-15, end */
}NAS_MSCC_PIF_END_SESSION_NOTIFY_STRU;
typedef struct
{
    MSG_HEADER_STRU                            stMsgHeader;                     /* _H2ASN_Skip */
    VOS_UINT8                                  ucImsCallFlg;
    VOS_UINT8                                  aucReserve[3];
}NAS_MSCC_PIF_IMS_SRV_INFO_NOTIFY_STRU;

/** ****************************************************************************
 * Name        : NAS_MSCC_PIF_CDMA_MO_CALL_START_NTF_STRU
 * Description : Mo Call start notification
 *******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                             stMsgHeader;                    /* _H2ASN_Skip */
    NAS_MSCC_PIF_CDMA_CALL_TYPE_ENUM_UINT8      enCallType;
    VOS_UINT8                                   aucReserve[3];
}NAS_MSCC_PIF_CDMA_MO_CALL_START_NTF_STRU;

/** ****************************************************************************
 * Name        : NAS_MSCC_PIF_CDMA_MO_CALL_REDIAL_SYS_ACQ_NTF_STRU
 * Description : Call redial notification
 *******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                             stMsgHeader;                    /* _H2ASN_Skip */
    NAS_MSCC_PIF_CDMA_CALL_TYPE_ENUM_UINT8      enCallType;
    NAS_MSCC_PIF_CDMA_CALL_CAUSE_ENUM_UINT8     enCause;
    VOS_UINT8                                   aucReserve[2];
}NAS_MSCC_PIF_CDMA_MO_CALL_REDIAL_SYS_ACQ_NTF_STRU;

/** ****************************************************************************
 * Name        : NAS_MSCC_PIF_CDMA_MO_CALL_SUCCESS_NTF_STRU
 * Description : Mo Call success notification
 *******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                             stMsgHeader;                    /* _H2ASN_Skip */
    NAS_MSCC_PIF_CDMA_CALL_TYPE_ENUM_UINT8      enCallType;
    VOS_UINT8                                   aucReserve[3];
}NAS_MSCC_PIF_CDMA_MO_CALL_SUCCESS_NTF_STRU;

/** ****************************************************************************
 * Name        : NAS_MSCC_PIF_CDMA_MO_CALL_END_NTF_STRU
 * Description : Mo Call end notification
 *******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                             stMsgHeader;                    /* _H2ASN_Skip */
    NAS_MSCC_PIF_CDMA_CALL_TYPE_ENUM_UINT8      enCallType;
    VOS_UINT8                                   aucReserve[3];
}NAS_MSCC_PIF_CDMA_MO_CALL_END_NTF_STRU;

/** ****************************************************************************
 * Name        : NAS_MSCC_PIF_CFREQ_LOCK_NTF_STRU
 * Description : Start confirm
 *******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                             stMsgHeader;                    /* _H2ASN_Skip */
    NAS_MSCC_PIF_CFREQ_LOCK_SET_MODE_ENUM_UINT8 enFreqLockMode;
    VOS_UINT8                                   aucReserve[1];
    VOS_UINT16                                  usCdmaBandClass;
    VOS_UINT16                                  usSid;
    VOS_UINT16                                  usNid;
    VOS_UINT16                                  usCdmaFreq;
    VOS_UINT16                                  usCdmaPn;
    VOS_UINT16                                  usHrpdBandClass;
    VOS_UINT16                                  usHrpdFreq;
    VOS_UINT16                                  usHrpdPn;
    VOS_UINT8                                   aucReserve1[2];
}NAS_MSCC_PIF_CFREQ_LOCK_NTF_STRU;

/** ****************************************************************************
 * Name        : NAS_MSCC_PIF_CDMACSQ_SET_PARA_STRU
 * Description : CdmaCsq set parameters
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucRptThreshold;
    VOS_UINT8                           ucTimeInterval;
    VOS_UINT8                           aucReserve[2];
}NAS_MSCC_PIF_CDMACSQ_SET_PARA_STRU;

/** ****************************************************************************
 * Name        : NAS_MSCC_PIF_CDMACSQ_SET_REQ_STRU
 * Description :
 *******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* _H2ASN_Skip */
    NAS_MSCC_PIF_CDMACSQ_SET_PARA_STRU  stCdmaCsq;
}NAS_MSCC_PIF_CDMACSQ_SET_REQ_STRU;


/** ****************************************************************************
 * Name        : NAS_MSCC_PIF_CDMACSQ_SET_CNF_STRU
 * Description :
 *******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                 stMsgHeader;                /* _H2ASN_Skip */
    NAS_MSCC_PIF_CDMACSQ_SET_RESULT_ENUM_UINT8      enRslt;
    VOS_UINT8                                       auReserved[3];
}NAS_MSCC_PIF_CDMACSQ_SET_CNF_STRU;


/** ****************************************************************************
 * Name        : XSD_MMA_CDMACSQ_IND_STRU
 * Description :
 *******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                         stMsgHeader;                        /* _H2ASN_Skip */
    VOS_INT8                                cCdmaRssi;
    VOS_INT8                                cCdmaEcIo;
    VOS_UINT8                               aucReserved[2];
}NAS_MSCC_PIF_CDMACSQ_IND_STRU;


/** ****************************************************************************
 * Name        : XSD_MMA_OHM_REG_INFO_STRU
 * Description : Register info of Overhead Message
 *******************************************************************************/
typedef struct
{
    VOS_UINT16                          usRegZone;      /**<  Registration zone */
    VOS_UINT8                           ucRegZoneNum;   /**<  Number of registration zones to be retained */

    /* for reg */
    VOS_UINT8                           ucZoneTimer;    /**<  Zone timer length */

    /* for reg */
    VOS_UINT8                           ucMultiSidFlg;  /**<  Multiple SID storage indicator */

    /* for reg */
    VOS_UINT8                           ucMultiNidFlg;  /**<  Multiple NID storage indicator */

    /* for reg */
    VOS_UINT16                          usRegDistance;  /**<  Registration distance */

    /* for reg */
    VOS_UINT8                           ucRegPeriod;    /**<  Registration period */

    /* for reg */
    VOS_UINT8                           ucHomeReg;      /**<  Home registration indicator */

    /* for roam */
    VOS_UINT8                           ucSidRoamReg;   /**<  SID roamer registration indicator */

    /* for roam */
    VOS_UINT8                           ucNidRoamReg;   /**<  NID roamer registration indicator */

    /* for reg */
    VOS_UINT8                           ucPowerUpReg;   /**<  Power-up registration indicator */

    /* for reg */
    VOS_UINT8                           ucPowerDownReg; /**<  Power-down registration indicator */

    /* for reg */
    VOS_UINT8                           ucParameterReg; /**<  Parameter-change registration indicator */

    /* for reg */
    VOS_UINT8                           aucReserve[1];
}NAS_MSCC_PIF_OHM_REG_INFO_STRU;

/** ****************************************************************************
 * Name        : XSD_MMA_OHM_SERVICE_INFO_STRU
 * Description : Service info of Overhead Message
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucMaxAltSo;            /**<  Max. Num. of alternative service options,for Origination or Page Response Message */
    VOS_UINT8                           ucSDBSupported;        /**<  Short Data Burst supported indicator */
    VOS_UINT8                           ucMoQos;               /**<  permission indicator for QoS in Origination message */
    VOS_UINT8                           ucConcurrentSupported; /**<  concurrent service supported */
    VOS_UINT8                           ucMoPosSupported;      /**<  MS initiated position location supported */
    VOS_UINT8                           ucReserve;
    VOS_UINT16                          usImsi11_12;           /**<  11th and 12th digits of the IMSI */
    VOS_UINT32                          ulMcc;                 /**<  Mobile country code */
    VOS_UINT16                          usMnc;                 /**<  Mobile network code */
    VOS_UINT8                           aucReserve[2];
}NAS_MSCC_PIF_OHM_SERVICE_INFO_STRU;

/** ****************************************************************************
 * Name        : XSD_MMA_OHM_BASE_STATION_INFO_STRU
 * Description : Base station info of Overhead Message
 *******************************************************************************/
typedef struct
{
    VOS_UINT16                          usBaseId;        /**<  Base station identification */

    /* for user zone */
    VOS_UINT8                           ucBaseClass;     /**<  Base station class */
    VOS_UINT8                           aucReserve[1];
    VOS_INT32                           lBaseLatitude;  /**<  Base station latitude */

    /* reg & zone */
    VOS_INT32                           lBaseLongitude; /**<  Base station longitude */

    /* reg & zone */
}NAS_MSCC_PIF_OHM_BASE_STATION_INFO_STRU;

/** ****************************************************************************
 * Name        : NAS_MSCC_PIF_1X_SYS_TIME_STRU
 *
 * Description : System time info
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                           aucSysTime[5];
    VOS_UINT8                           ucLpSec;
    VOS_INT8                            cLtmOff;
    VOS_UINT8                           ucDaylt;
} NAS_MSCC_PIF_1X_SYS_TIME_STRU;

/** ****************************************************************************
 * Name        : NAS_MSCC_PIF_SYSTEM_TIME_IND_STRU
 * Description : System service Info indication
 *******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                         stMsgHeader;                        /* _H2ASN_Skip */
    NAS_MSCC_PIF_1X_SYS_TIME_STRU           stSysTime;
}NAS_MSCC_PIF_1X_SYSTEM_TIME_IND_STRU;

/** ****************************************************************************
 * Name        : NAS_MSCC_PIF_1X_SYS_SRV_INFO_STRU
 * Description : System info
 *******************************************************************************/
typedef struct
{
    VOS_UINT16                                  usBandClass;
    VOS_UINT16                                  usFreq;
    VOS_UINT16                                  usSid;             /**<  System identification */
    VOS_UINT16                                  usNid;             /**<  Network identification */
    NAS_MSCC_PIF_SERVICE_STATUS_ENUM_UINT32     enServiceStatus;
    VOS_UINT8                                   ucRoamingInd;
    VOS_UINT8                                   ucPrevInUse;
    VOS_UINT8                                   ucPzid;    /* Packet Zone Id */
    NAS_MSCC_PIF_PRI_CLASS_ENUM_UINT8           en1xPriClass;         /* 1x priority class */
    NAS_MSCC_PIF_PRI_CLASS_ENUM_UINT8           enAIPriClass;         /* AI priority class */
    PS_BOOL_ENUM_UINT8                          enRegInfoIncl;
    PS_BOOL_ENUM_UINT8                          enBaseStationInfoIncl;
    PS_BOOL_ENUM_UINT8                          enServiceInfoIncl;
    NAS_MSCC_PIF_OHM_REG_INFO_STRU              stRegInfo;
    NAS_MSCC_PIF_OHM_BASE_STATION_INFO_STRU     stBaseStationInfo;
    NAS_MSCC_PIF_OHM_SERVICE_INFO_STRU          stServiceInfo;
}NAS_MSCC_PIF_1X_SYS_SRV_INFO_STRU;

/** ****************************************************************************
 * Name        : NAS_MSCC_PIF_SERVICE_INFO_IND_STRU
 * Description : System service Info indication
 *******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                         stMsgHeader;                        /* _H2ASN_Skip */
    NAS_MSCC_PIF_1X_SYS_SRV_INFO_STRU       stSysSrvInfo;
}NAS_MSCC_PIF_1X_SYSTEM_SERVICE_INFO_IND_STRU;
typedef struct
{
    MSG_HEADER_STRU                                         stMsgHeader;        /* _H2ASN_Skip */
    NAS_MSCC_PIF_CFPLMN_OPERATE_TYPE_ENUM_UINT8             enCmdType;
    VOS_UINT8                                               aucReserve[3];
    NAS_MSCC_PIF_PLMN_ID_STRU                               stPlmnInfo;
}NAS_MSCC_PIF_CFPLMN_SET_REQ_STRU;
typedef struct
{
    MSG_HEADER_STRU                                         stMsgHeader;        /* _H2ASN_Skip */
    VOS_UINT8                                               aucReserve[4];
}NAS_MSCC_PIF_CFPLMN_QUERY_REQ_STRU;
typedef struct
{
    NAS_MSCC_PIF_CFPLMN_OPERATE_TYPE_ENUM_UINT8             ulCmdType;
    VOS_UINT8                                               ucPlmnNum;          /* plmnnum��astplmn���ڴ�Ų�ѯ�Ľ�� */
    VOS_UINT8                                               aucReserve[2];
    NAS_MSCC_PIF_PLMN_ID_STRU                               astPlmn[NAS_MSCC_PIF_MAX_CFPLMN_NUM];
}NAS_MSCC_PIF_CFPLMN_LIST_STRU;
typedef struct
{
    MSG_HEADER_STRU                                         stMsgHeader;        /* _H2ASN_Skip */
    NAS_MSCC_PIF_CFPLMN_OPER_RESULT_ENUM_UINT32             enResult;
}NAS_MSCC_PIF_CFPLMN_SET_CNF_STRU;
typedef struct
{
    MSG_HEADER_STRU                                         stMsgHeader;        /* _H2ASN_Skip */
    NAS_MSCC_PIF_CFPLMN_OPER_RESULT_ENUM_UINT32             enResult;
    VOS_UINT8                                               aucReserve[3];
    VOS_UINT8                                               ucPlmnNum;                         /* plmnnum��astplmn���ڴ�Ų�ѯ�Ľ�� */
    NAS_MSCC_PIF_PLMN_ID_STRU                               astPlmn[NAS_MSCC_PIF_MAX_CFPLMN_NUM];
}NAS_MSCC_PIF_CFPLMN_QUERY_CNF_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_CTRL_STRU
 �ṹ˵��  : NAS_MSCC���ƽṹ��

 �޸���ʷ      :
  1.��    ��   : 2015��02��04��
    ��    ��   : y00307564
    �޸�����   : Iteration 8 �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulModuleId;         /* ����PID */
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;
    VOS_UINT8                           aucReserved[1];
}NAS_MSCC_CTRL_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_CTRL_STRU
 �ṹ˵��  : NAS_MSCC_PLMN_NAME_LIST_STRU

 �޸���ʷ      :
  1.��    ��   : 2015��02��04��
    ��    ��   : y00307564
    �޸�����   : Iteration 8 �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                              ulPlmnNum;
    VOS_BOOL                                                bPlmnSelFlg;
    NAS_MSCC_PIF_OPERATOR_NAME_INFO_STRU                    astPlmnName[NAS_MSCC_PIF_MAX_PLMN_CNT];
    VOS_UINT16                                              ausPlmnRat[NAS_MSCC_PIF_MAX_PLMN_CNT];
    VOS_UINT8                                               aucReserved[2];
}NAS_MSCC_PLMN_NAME_LIST_STRU;


typedef struct
{
    VOS_UINT32                                              ulPlmnNum;
    VOS_BOOL                                                bPlmnSelFlg;
    NAS_MSCC_PIF_OPERATOR_NAME_INFO_STRU                    astPlmnName[NAS_MSCC_PIF_MAX_CPOL_PLMN_CNT];
    VOS_UINT16                                              ausPlmnRat[NAS_MSCC_PIF_MAX_CPOL_PLMN_CNT];
}NAS_MSCC_CPOL_PLMN_NAME_LIST_STRU;

/*****************************************************************************
�ṹ��    : NAS_MSCC_CPOL_INFO_QUERY_REQ_STRU
�ṹ˵��  : AT+CPOL��ѯ����ṹ

�޸���ʷ      :
  1.��    ��   : 2015��02��04��
    ��    ��   : y00307564
    �޸�����   : Iteration 8 �½�
*******************************************************************************/
typedef struct
{
    NAS_MSCC_PIF_PARA_TYPE_ENUM_UINT8                       enPrefPLMNType;                         /* ��ѯ��Ӫ�����Ƶ����� */
    VOS_UINT8                                               aucReserved1[3];
    VOS_UINT32                                              ulFromIndex;                            /* ��ѯ��Ӫ�����Ƶ���ʼλ�� */
    VOS_UINT32                                              ulPlmnNum;                              /* ��ѯ��Ӫ�����Ƶĸ���������A�˺�C��ͨѶ����Ϣ��С�����ƣ����һ������ѯ50����¼ */
    VOS_UINT32                                              ulValidPlmnNum;                         /* ��Ч�������Ӫ�����Ƹ��� */
}NAS_MSCC_CPOL_INFO_QUERY_REQ_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_PREF_PLMN_QUERY_REQ_STRU
 �ṹ˵��  : ��ѯ����PREFPLMN����ӿ�
 1.��    ��   : 2015��02��03��
   ��    ��   : y00307564
   �޸�����   : Iteration 8 �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                         stMsgHeader;        /* _H2ASN_Skip */
    NAS_MSCC_PIF_PREF_PLMN_CMD_TYPE_ENUM_UINT8              enCmdType;
    VOS_UINT8                                               aucReserve[3];
    VOS_BOOL                                                bPlmnSelFlg;
    NAS_MSCC_CPOL_INFO_QUERY_REQ_STRU                       stCpolInfo;
}NAS_MSCC_PIF_PREF_PLMN_QUERY_REQ_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_PREF_PLMN_QUERY_CNF_STRU
 �ṹ˵��  : ��ѯ����PREFPLMN����ظ��ӿ�
 1.��    ��   : 2015��02��03��
   ��    ��   : y00307564
   �޸�����   : Iteration 8 �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                         stMsgHeader;        /* _H2ASN_Skip */
    NAS_MSCC_PIF_PREF_PLMN_CMD_TYPE_ENUM_UINT8              enCmdType;
    VOS_UINT8                                               aucReserve[1];
    VOS_UINT16                                              usPlmnNum;          /* ���ڲ���������� */
    VOS_UINT32                                              ulFromIndex;
    VOS_UINT32                                              ulValidPlmnNum;     /* ��Ч�������Ӫ�����Ƹ��� */
    NAS_MSCC_CPOL_PLMN_NAME_LIST_STRU                       stPlmnName;
    NAS_MSCC_PIF_PREF_PLMN_OPER_RESULT_ENUM_UINT32          enRslt;
}NAS_MSCC_PIF_PREF_PLMN_QUERY_CNF_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_PREF_PLMN_SET_REQ_STRU
 �ṹ˵��  : ����PREFPLMN����ӿ�
 1.��    ��   : 2015��2��3��
   ��    ��   : y00307564
   �޸�����   : Iteration 8 �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                         stMsgHeader;        /* _H2ASN_Skip */
    NAS_MSCC_CTRL_STRU                                      stCtrl;
    NAS_MSCC_PIF_PREF_PLMN_OPERATE_STRU                     stPrefPlmnOpt;
    NAS_MSCC_PIF_PARA_TYPE_ENUM_UINT8                       enPrefPlmnParaType;
    VOS_UINT8                                               aucReserve[3];
}NAS_MSCC_PIF_PREF_PLMN_SET_REQ_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_PREF_PLMN_SET_CNF_STRU
 �ṹ˵��  : ����PREFPLMN����ظ��ӿ�
 1.��    ��   : 2015��2��3��
   ��    ��   : y00307564
   �޸�����   : Iteration 8 �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                         stMsgHeader;        /* _H2ASN_Skip */
    NAS_MSCC_PIF_PREF_PLMN_OPER_RESULT_ENUM_UINT32          enRslt;
}NAS_MSCC_PIF_PREF_PLMN_SET_CNF_STRU;
typedef struct
{
    NAS_MSCC_PIF_PLMN_ID_STRU           stPlmn;
    VOS_UINT16                          usRaMode;
    VOS_UINT8                           ucStatus;
    VOS_UINT8                           aucReserve1[1];
}MMC_TAF_PLMN_INFO_ST;

typedef struct
{
    MMC_TAF_PLMN_INFO_ST    astPlmnInfo[NAS_MSCC_PIF_MAX_PLMN_NUM];
    VOS_UINT16              usCurPlmnNum;
    VOS_UINT8               aucReserve1[2];
}MMC_TAF_PLMN_LIST_INFO_ST;


typedef struct
{
    MMC_MMA_PARA_TYPE_ENUM    enMmaParaType;
    union
    {
        MMC_TAF_PLMN_LIST_INFO_ST           stHPlmn;            /*��ȡHPLMN�б�*/
        MMC_TAF_PLMN_LIST_INFO_ST           stUPlmnInfo;
        MMC_TAF_PLMN_LIST_INFO_ST           stOPlmnInfo;
        MMC_TAF_PLMN_LIST_INFO_ST           stHPlmnInfo;
    }u;
}MMC_MMA_SHARE_PARA_ST;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_IMS_SWITCH_STATE_IND_STRU
 �ṹ˵��  : ָʾIMS�ر�״̬�Ľӿ�
 1.��    ��   : 2015��04��13��
   ��    ��   : f0017928
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                             stMsgHeader;
    NAS_MSCC_PIF_IMS_SWITCH_STATE_ENUM_UINT8    enImsSwitch;                    /* IMS��������,1:��,0:�ر� */
    VOS_UINT8                                   aucReserved[3];
}NAS_MSCC_PIF_IMS_SWITCH_STATE_IND_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_VOICE_DOMAIN_CHANGE_IND_STRU
 �ṹ˵��  : ָʾVOICE DOMAIN�仯�Ľӿ�
 1.��    ��   : 2015��04��13��
   ��    ��   : f0017928
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                             stMsgHeader;
    NAS_MSCC_PIF_VOICE_DOMAIN_ENUM_UINT32       enVoiceDomain;                  /* ������ѡ�� */
}NAS_MSCC_PIF_VOICE_DOMAIN_CHANGE_IND_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_IMS_START_REQ_STRU
 �ṹ˵��  : ����IMS�����Ľӿ�
 1.��    ��   : 2015��04��13��
   ��    ��   : f0017928
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;
    VOS_UINT8                           aucReserve[4];
}NAS_MSCC_PIF_IMS_START_REQ_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_IMS_START_CNF_STRU
 �ṹ˵��  : IMS��������Ļظ��ӿ�
 1.��    ��   : 2015��04��13��
   ��    ��   : f0017928
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                             stMsgHeader;
    NAS_MSCC_PIF_IMS_START_RESULT_ENUM_UINT32   enResult;
}NAS_MSCC_PIF_IMS_START_CNF_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_IMS_STOP_REQ_STRU
 �ṹ˵��  : ����IMS�رյĽӿ�
 1.��    ��   : 2015��04��13��
   ��    ��   : f0017928
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;
    VOS_UINT8                           aucReserve[4];
}NAS_MSCC_PIF_IMS_STOP_REQ_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_IMS_STOP_CNF_STRU
 �ṹ˵��  : IMS�ر�����Ļظ��ӿ�
 1.��    ��   : 2015��04��13��
   ��    ��   : f0017928
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                             stMsgHeader;
    NAS_MSCC_PIF_IMS_STOP_RESULT_ENUM_UINT32    enResult;
}NAS_MSCC_PIF_IMS_STOP_CNF_STRU;


typedef struct
{
    NAS_MSCC_PIF_PLMN_ID_STRU                  stPlmnId;

    VOS_UINT16                                 usLac;
    VOS_UINT8                                  aucReserve[2];
}NAS_MSCC_PIF_LAI_STRU;


typedef struct
{
    MSG_HEADER_STRU                            stMsgHeader;

    NAS_MSCC_PIF_NET_RAT_TYPE_ENUM_UINT8       enRat;
    VOS_UINT8                                  aucReserved[3];

    VOS_UINT32                                 ulLaiNum;
    NAS_MSCC_PIF_LAI_STRU                      astLai[NAS_MSCC_PIF_MAX_SRCHED_LAI_NUM];
}NAS_MSCC_PIF_SRCHED_PLMN_INFO_IND_STRU;


/** ****************************************************************************
 * Name        : NAS_MSCC_PIF_INTERSYS_START_IND_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                         stMsgHeader;        /*_H2ASN_Skip*//* ��Ϣͷ                                   */
    VOS_UINT16                                              usOpId;
    VOS_UINT8                                               aucRsv[2];
    VOS_RATMODE_ENUM_UINT32                                 enOrignRatMode;
    VOS_RATMODE_ENUM_UINT32                                 enDestRatMode;
    NAS_MSCC_PIF_INTERSYS_CAUSE_ENUM_UINT32                 enInterSysCause;
}NAS_MSCC_PIF_INTERSYS_START_IND_STRU;

/** ****************************************************************************
 * Name        : NAS_MSCC_PIF_INTERSYS_END_IND_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;        /*_H2ASN_Skip*//* ��Ϣͷ                                   */
    VOS_UINT16                          usOpId;
    VOS_UINT8                           aucRsv[2];
    VOS_RATMODE_ENUM_UINT32             enCampedRatMode;
}NAS_MSCC_PIF_INTERSYS_END_IND_STRU;

/** ****************************************************************************
 * Name        : NAS_MSCC_PIF_CL_SYSTEM_ACQUIRE_START_IND_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;        /*_H2ASN_Skip*//* ��Ϣͷ                                   */
    VOS_UINT16                          usOpId;
    VOS_UINT8                           aucReserve[2];
}NAS_MSCC_PIF_CL_SYSTEM_ACQUIRE_START_IND_STRU;

/** ****************************************************************************
 * Name        : NAS_MSCC_PIF_CL_SYSTEM_ACQUIRE_END_IND_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                         stMsgHeader;        /*_H2ASN_Skip*//* ��Ϣͷ                                   */
    VOS_UINT16                                              usOpId;
    VOS_UINT8                                               aucRsv[2];
    NAS_MSCC_PIF_CL_ACQUIRED_RESULT_ENUM_UINT32             enRslt;
}NAS_MSCC_PIF_CL_SYSTEM_ACQUIRE_END_IND_STRU;
typedef struct
{
    NAS_MSCC_PIF_PLMN_ID_STRU           stPlmnId;                               /* PLMN ID */
    VOS_UINT16                          usSimRat;                               /* SIM����֧�ֵĽ��뼼�� */
    VOS_UINT8                           aucReserve[2];
}NAS_MSCC_PIF_SIM_PLMN_WITH_RAT_STRU;


typedef struct
{
    VOS_UINT8                           ucEhPlmnNum;                        /* EHPLMN�ĸ���*/
    VOS_UINT8                           aucRsv[3];
    NAS_MSCC_PIF_SIM_PLMN_WITH_RAT_STRU astEhPlmnInfo[NAS_MSCC_PIF_MAX_EHPLMN_NUM];/* EHPLMN ID�б� */
}NAS_MSCC_PIF_SIM_EHPLMN_INFO_STRU;


typedef struct
{
    VOS_UINT8                           ucUserPlmnNum;                          /* UPLMN�ĸ���*/
    VOS_UINT8                           aucReserve3[3];
    NAS_MSCC_PIF_SIM_PLMN_WITH_RAT_STRU astUserPlmnInfo[NAS_MSCC_PIF_MAX_USERPLMN_NUM];/* UPLMN���б�*/
}NAS_MSCC_PIF_SIM_USERPLMN_INFO_STRU;



typedef struct
{
    VOS_UINT16                          usOperPlmnNum;                          /* OPLMN�ĸ���*/
    VOS_UINT8                           aucReserve2[2];
    NAS_MSCC_PIF_SIM_PLMN_WITH_RAT_STRU astOperPlmnInfo[NAS_MSCC_PIF_MAX_OPERPLMN_NUM];/* OPLMN���б�*/
}NAS_MSCC_PIF_SIM_OPERPLMN_INFO_STRU;


/* Added by y00322978 for CDMA Iteration 15, 2015-5-11, begin */
/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_PS_RAT_TYPE_NTF_STRU
 �ṹ˵��  :  PS RATTYPE
 1.��    ��   : 2015��04��13��
   ��    ��   : f0017928
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                             stMsgHeader;
    NAS_MSCC_PIF_PS_RAT_TYPE_ENUM_UINT32        enPsRatType;
}NAS_MSCC_PIF_PS_RAT_TYPE_NTF_STRU;
/* Added by y00322978 for CDMA Iteration 15, 2015-5-11, end */

typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;
    VOS_UINT8                           ucActiveFlg;                            /* �Ƿ��� */
    VOS_UINT8                           aucReserved[3];
}NAS_MSCC_PIF_AUTO_RESEL_SET_STRU;
typedef struct
{
    MSG_HEADER_STRU                             stMsgHeader;
    VOS_UINT8                                   aucReserve[4];
}NAS_MSCC_PIF_GET_GEO_REQ_STRU;


typedef struct
{
    MSG_HEADER_STRU                             stMsgHeader;
    NAS_MSCC_PIF_PLMN_ID_STRU                   stPlmnId;
}NAS_MSCC_PIF_GET_GEO_CNF_STRU;


typedef struct
{
    MSG_HEADER_STRU                             stMsgHeader;
    VOS_UINT8                                   aucReserve[4];
}NAS_MSCC_PIF_STOP_GET_GEO_REQ_STRU;


typedef struct
{
    MSG_HEADER_STRU                             stMsgHeader;
    VOS_UINT8                                   aucReserve[4];
}NAS_MSCC_PIF_STOP_GET_GEO_CNF_STRU;



typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /*_H2ASN_Skip*//* ��Ϣͷ    */
    VOS_UINT16                          usSid;                                  /* SID */
    VOS_UINT16                          usReserved;                             /* ����λ */
}NAS_MSCC_PIF_SID_IND_STRU;

/* Added by h00313353 for Iteration 17, 2015-7-16, begin */
/*****************************************************************************
 �ṹ��    : XSD_MSCC_EMC_CALLBACK_IND_STRU
 �ṹ˵��  : ������CALLBACKģʽ״̬����Ϣ�ṹ
 1.��    ��   : 2015��07��02��
   ��    ��   : h00313353
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                             stMsgHeader;        /*_H2ASN_Skip*//* ��Ϣͷ    */
    NAS_MSCC_PIF_EMC_CALLBACK_MODE_ENUM_UINT32  enCallBackState;    /* �Ƿ���CallBackģʽ�� */
} NAS_MSCC_PIF_EMC_CALLBACK_IND_STRU;
/* Added by h00313353 for Iteration 17, 2015-7-16, end */
/* Added by y00322978 for CDMA Iteration 17, 2015-7-20, begin */
/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_END_EMC_CALLBACK_IND_STRU
 �ṹ˵��  : �ظ��˳�������CallBack�������Ϣ�ṹ
 1.��    ��   : 2015��07��02��
   ��    ��   : y00322978
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;        /*_H2ASN_Skip*//* ��Ϣͷ    */
} NAS_MSCC_PIF_END_EMC_CALLBACK_IND_STRU;
/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_SID_WHITE_LIST_STRU
 �ṹ˵��  : �����SID��MCC��Ϣ

 1.��    ��   : 2015��7��2��
   ��    ��   : y00322978
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usStartSid;
    VOS_UINT16                          usEndSid;
    VOS_UINT32                          ulMcc;
}NAS_MSCC_PIF_SID_WHITE_LIST_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_OPER_LOCK_WHITE_SID_STRU
 �ṹ˵��  : �����SID��������Ϣ
  1.��    ��   : 2015��7��2��
    ��    ��   : y00322978
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEnable;                          /* �������Ƿ�ʹ�� */
    VOS_UINT8                           ucReserved;
    VOS_UINT16                          usWhiteSysNum;                     /* ֧�ְ������ĸ���,����Ϊ0ʱ��ʾ��֧�ְ����� */
    NAS_MSCC_PIF_SID_WHITE_LIST_STRU    astSysInfo[NAS_MSCC_PIF_MAX_WHITE_LOCK_SID_NUM];
}NAS_MSCC_PIF_OPER_LOCK_SYS_WHITE_STRU;
/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_SET_CSIDLIST_REQ_STRU
 �ṹ˵��  : sid white list ��������ṹ��
 1.��    ��   : 2015��07��02��
   ��    ��   : y00322978
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                         stMsgHeader;        /*_H2ASN_Skip*//* ��Ϣͷ    */
    NAS_MSCC_PIF_OPER_LOCK_SYS_WHITE_STRU   stSidWhiteList;
}NAS_MSCC_PIF_SET_CSIDLIST_REQ_STRU;
/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_SET_CSIDLIST_CNF_STRU
 �ṹ˵��  : sid white list ���ûظ��ṹ��
 1.��    ��   : 2015��07��02��
   ��    ��   : y00322978
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;        /*_H2ASN_Skip*//* ��Ϣͷ    */
    VOS_UINT32                          ulRslt;
}NAS_MSCC_PIF_SET_CSIDLIST_CNF_STRU;
typedef struct
{
    MSG_HEADER_STRU                                         stMsgHeader;        /*_H2ASN_Skip*//* ��Ϣͷ    */
    VOS_UINT16                                              usBandClass;
    VOS_UINT16                                              usFreq;
    VOS_UINT16                                              usSid;             /**<  System identification */
    VOS_UINT16                                              usNid;             /**<  Network identification */
    NAS_MSCC_PIF_SERVICE_STATUS_ENUM_UINT32                 enServiceStatus;
    VOS_UINT8                                               ucRoamingInd;
    VOS_UINT8                                               aucReserved[3];
}NAS_MSCC_PIF_SYNC_SERVICE_AVAILABLE_IND_STRU;

/* Added by y00322978 for CDMA Iteration 17, 2015-7-20, end */
/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/


#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif
