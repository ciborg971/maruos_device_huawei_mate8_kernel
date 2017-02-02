
#ifndef _TAF_SDC_CTX_H_
#define _TAF_SDC_CTX_H_

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include  "PsTypeDef.h"
#include  "ComInterface.h"
/* Added by zwx247453 for CHR optimize, 2015-3-13 Begin */
#include  "errorlog.h"
#include  "NasErrorLog.h"
/* Added by zwx247453 for CHR optimize, 2015-3-13 End */
#include  "product_config.h"
#include  "NVIM_Interface.h"

#include  "NasNvInterface.h"

#include "omringbuffer.h"

#include "TafNvInterface.h"
#include "UsimPsInterface.h"

#include "NasMsccPifInterface.h"


/* Added by h00313353 for CDMA Iteration 15, 2015-5-28, begin */
#include "TafAppMma.h"
/* Added by h00313353 for CDMA Iteration 15, 2015-5-28, end */
/* Added by y00322978 for CDMA Iteration 17, 2015-7-10, begin */
#include "NasOmTrans.h"
/* Added by y00322978 for CDMA Iteration 17, 2015-7-10, end */


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define TAF_SDC_PLATFORM_MAX_RAT_NUM                        (7)                 /* ƽ̨֧�ֵ������뼼����Ŀ */

#if (FEATURE_ON == FEATURE_LTE)
#define TAF_SDC_MAX_RAT_NUM                             (3)                     /* ��ǰ֧�ֵĽ��뼼������ */
#else
#define TAF_SDC_MAX_RAT_NUM                             (2)                     /* ��ǰ֧�ֵ�GU���뼼������ */
#endif


#define TAF_SDC_MAX_IMSI_LEN                                (9)                 /* IMSI����󳤶� */
#define TAF_SDC_IMSI_INVALID                                (0xFF)              /* IMSI����Чֵ�ĺ궨��     */
#define TAF_SDC_INVALID_MCC                                 (0xFFFFFFFF)        /* MCC����Чֵ */
#define TAF_SDC_INVALID_MNC                                 (0xFFFFFFFF)        /* MNC����Чֵ */
#define TAF_SDC_RAC_INVALID                                 (0xFF)              /* RAC��Ϊ��Чֵ */
#define TAF_SDC_CELLID_INVALID                              (0xFFFFFFFF)
#define TAF_SDC_LAC_INVALID                                 (0xFFFF)
#define TAF_SDC_IMSI_INVALID                                (0xFF)                  /* IMSI����Чֵ�ĺ궨��     */


#define TAF_SDC_SIM_FORMAT_PLMN_LEN                         (3)                 /* SIM����PLMN ID�ĳ��� */

#define TAF_SDC_RPT_CFG_MAX_SIZE                            (8)                 /* �����ϱ���ʶ���ĳ��� */
#define TAF_SDC_MAX_SIGN_THRESHOLD                          (5)                 /* RSSI/CERSSI����ϱ�����ֵ:5DB */


#define TAF_SDC_ASCII2BCDLENGTH(ulAsciiLength)              ((ulAsciiLength + 1) / 2)
#define TAF_SDC_BITS_PER_OCTET                              (8)
#define TAF_SDC_BITS_PER_SEPTET                             (7)
#define TAF_SDC_USSD_7BIT_PAD                               (0x1a)

#define TAF_SDC_EMER_NUM_MAX_LENGTH                         (46)                             /* Emergency Number information������ֽ��� */
#define TAF_SDC_EMER_NUM_LISTS_MAX_NUMBER                   (16)
#define TAF_SDC_NUMOF_EMER_NUMS_NO_USIM                     (8)
#define TAF_SDC_NUMOF_EMER_NUMS_WITH_USIM                   (2)
#define TAF_SDC_MAX_CUSTOM_ECC_NUM                          (20)                             /* �û����ƵĽ���������������� */
#define TAF_SDC_MAX_BCD_NUM_LEN                             (20)                             /* �ú궨���ȡֵ��MN_CALL_MAX_BCD_NUM_LEN��ȡֵ����һ�� */


#define TAF_SDC_ECALL_BCD_NUM_MAX_LEN                        (20)

#define TAF_SDC_SRV_TYPE_CS_MO_NORMAL_CALL                   (0x1)
#define TAF_SDC_SRV_TYPE_CS_MO_EMERGENCY_CALL                (0x2)
#define TAF_SDC_SRV_TYPE_CS_MO_SS                            (0x4)
#define TAF_SDC_SRV_TYPE_CS_MO_SMS                           (0x8)
#define TAF_SDC_SRV_TYPE_PS_CONVERSAT_CALL                   (0x10)
#define TAF_SDC_SRV_TYPE_PS_STREAM_CALL                      (0x20)
#define TAF_SDC_SRV_TYPE_PS_INTERACT_CALL                    (0x40)
#define TAF_SDC_SRV_TYPE_PS_BACKGROUND_CALL                  (0x80)
#define TAF_SDC_SRV_TYPE_PS_SUBSCRIB_TRAFFIC_CALL            (0x100)


#define TAF_SDC_MAX_UCIM_ECC_NUM                              (5)                             /* UIM��CSIM�������Ľ������к������� */

/* Modified by l00305157 for Service_State_Optimize_PhaseI, 2014-11-29, begin */
#define TAF_SDC_BLER_INVALID            (99)                                    /* ��Чֵ */
#define TAF_SDC_RSRP_UNVALID            (99)                                    /* ��Чֵ */
#define TAF_SDC_RSRQ_UNVALID            (99)                                    /* ��Чֵ */
#define TAF_SDC_UE_RFPOWER_INVALID      (0x1fff)                                /* ��Чֵ */
#define TAF_SDC_UE_FREQ_INVALID         (0xffff)                                /* UE FREQ����Чֵ */
#define TAF_SDC_RSSI_UNVALID            (-140)                                  /* RSSI����Чֵ */
#define TAF_SDC_RSSI_VALUE_UNVALID      (0)                                     /*��ת��Ϊ�ȼ���ʾ���ź�ǿ�ȵ���Чֵ*/
/* Modified by l00305157 for Service_State_Optimize_PhaseI, 2014-11-29, end */

/* Added by m00312079 for CDMA 1X Iteration 6 2014-12-27 begin */
#define TAF_SDC_CDMA_INVALID_RSSI_VALUE     (0x7F)
#define TAF_SDC_CDMA_INVALID_ECIO_VALUE     (0x7F)
/* Added by m00312079 for CDMA 1X Iteration 6 2014-12-27 end */

/* Added by c00318887 for AT&T phaseII, 2015-2-25, begin */
#define TAF_SDC_OPL_MAX_RECORD_NUM                           (60)
#define TAF_SDC_PNN_MAX_RECORD_NUM                           (60)
#define TAF_SDC_MAX_OPER_NAME_NUM                            (100)
#define TAF_SDC_MAX_OPER_LONG_NAME_LEN                       (100)                    /* spn ����ucs2����ʱ��Ҫ�ĳ���Ϊ32�����һ��\0 ���뵽36λ,��Ϊ�����39��long name ,������40*/
#define TAF_SDC_MAX_OPER_SHORT_NAME_LEN                      (100)                    /* spn ����ucs2����ʱ��Ҫ�ĳ���Ϊ32 ,���һ��\0 ���뵽36λ */
#define TAF_SDC_MAX_SERVICE_PROVIDER_PLMN_NUM                (50)
#define TAF_SDC_MAX_PLMN_ADDITIONAL_INFO_LEN                 (50)
#define TAF_SDC_MAX_OPER_NAME_PRIO_NUM                       (4)
#define TAF_SDC_INVALID_PLMN_PNN_INDEX                       (0xFFFFFFFF)
#define TAF_SDC_VALID_PNN_LOW_INDEX                          (0x01)
#define TAF_SDC_VALID_PNN_HIGH_INDEX                         (0xFE)
#define TAF_SDC_INVALID_PNN_INDEX                            (0xFF)
#define TAF_SDC_VALID_LAC_RANGE_LOW                          (0x0)
#define TAF_SDC_VALID_LAC_RANGE_HIGH                         (0xFFFE)

#define TAF_SDC_OCTET_LOW_FOUR_BITS                     (0x0f)                  /* ��ȡһ���ֽ��еĵ�4λ */
#define TAF_SDC_OCTET_HIGH_FOUR_BITS                    (0xf0)                  /* ��ȡһ���ֽ��еĸ�4λ */
#define TAF_SDC_OCTET_MOVE_FOUR_BITS                    (0x04)                  /* ��һ���ֽ��ƶ�4λ */
#define TAF_SDC_OCTET_MOVE_EIGHT_BITS                   (0x08)                  /* ��һ���ֽ��ƶ�8λ */
#define TAF_SDC_OCTET_MOVE_SEVEN_BITS                   (0x07)                  /* ��һ���ֽ��ƶ�7λ */
#define NAS_MML_OCTET_MOVE_TWELVE_BITS                  (0x0C)                  /* ��һ���ֽ��ƶ�8λ */
#define TAF_SDC_OCTET_MOVE_SIXTEEN_BITS                 (0x10)                  /* ��һ���ֽ��ƶ�16λ */
#define TAF_SDC_OCTET_MOVE_THREE_BYTES                  (0x03)                  /* �ƶ�3���ֽ� */
#define TAF_SDC_OCTET_MOVE_FOUR_BYTES                   (0x04)                  /* �ƶ�4���ֽ� */
#define TAF_SDC_OCTET_MOVE_FIVE_BYTES                   (0x05)                  /* �ƶ�5���ֽ� */
#define TAF_SDC_OCTET_MOVE_SIX_BYTES                    (0x06)                  /* �ƶ�6���ֽ� */
#define TAF_SDC_OCTET_MOVE_SEVEN_BYTES                  (0x07)                  /* �ƶ�7���ֽ� */

#define TAF_SDC_OPL_BYTE_POSITION_OF_LAC_RANG_LOW       (0x03)                  /* OPL�ļ��е�4,5�ֽڱ�ʾLAC���� */
#define TAF_SDC_OPL_BYTE_POSITION_OF_LAC_RANG_HIGHT     (0x05)                  /* OPL�ļ��е�6,7�ֽڱ�ʾLAC���� */
#define TAF_SDC_OPL_BYTE_POSITION_OF_PNN_INDEX          (0x07)                  /* OPL�ļ��е�8�ֽڱ�ʾPLMN network name record Index */

#define TAF_SDC_PNN_CODING_SCHEME_BIT_MASK              (0x70)                  /* PNN�ļ���bit7-bit5��ʾcoding scheme */
#define TAF_SDC_PNN_SPARE_BIT_MASK                      (0x07)                  /* PNN�ļ���bit3-bit1��ʾNumber of spare bits */

#define TAF_SDC_SPN_DISPLAY_CONDITION_BIT_MASK          (0x03)                  /* ����SPN bit1-bit2,�Ƿ���ʾSPN */
#define TAF_SDC_SPN_SPARE_BIT_MASK                      (0x07)                  /* SPN�ļ���bit3-bit1��ʾNumber of spare bits */
#define TAF_SDC_SPN_UCS2_CODING_FORM1                   (0x80)                  /* SPN Byte1 ��0x80,0x81,0x82ʱ ��ʾUCS2���� */
#define TAF_SDC_SPN_UCS2_CODING_FORM2                   (0x81)                  /* SPN Byte1 ��0x80,0x81,0x82ʱ ��ʾUCS2���� */
#define TAF_SDC_SPN_UCS2_CODING_FORM3                   (0x82)                  /* SPN Byte1 ��0x80,0x81,0x82ʱ ��ʾUCS2���� */

#define TAF_SDC_PLMN_MCC_LEN                             (3)                     /* PLMN �е�MCC�ĳ��� */
#define TAF_SDC_PLMN_MNC_LEN                             (3)                     /* PLMN �е�MNC�ĳ��� */
#define TAF_SDC_MCC_MNC_BYTE_VALUE_MASK                  (0x000000FF)

#define TAF_SDC_MCC_LOW_TWO_BYTE_VALUE_MASK              (0x0000FFFF)
#define TAF_SDC_MCC_THIRD_BYTE_VALUE_MASK                (0x00FF0000)
#define TAF_SDC_PCS1900_MCC_LOW_VALUE                    (0x00000103)
#define TAF_SDC_PCS1900_MCC_HIGH_VALUE_RANGE             (0x00060000)
#define TAF_SDC_PCS1900_MNC_THIRD_BYTE_VALUE_0           (0x00)
#define TAF_SDC_PCS1900_MNC_THIRD_BYTE_VALUE_F           (0x0F)

#define TAF_SDC_LOW_BYTE_INVALID                         (0x0F)

#define TAF_SDC_MAX_DIGIT_VALUE                         (9)
#define NAS_SDC_ONE_THOUSAND_MILLISECOND                (1000)                  /* 1000MS */
#define NAS_MML_SIXTY_SECOND                            (60)                    /* 60�� */

/* Added by c00318887 for AT&T phaseII, 2015-2-26, end */

/* Added by l00301449 for CDMA STK, 2015-07-03, begin */
#define TAF_SDC_GET_STK_MCC(NUM)        (100 * ((NUM  % 1000 / 100 + 9) % 10) \
                                        + 10* ((NUM % 100 / 10 + 9) % 10) \
                                        + (NUM % 10 + 9) %10)

#define TAF_SDC_GET_STK_MNC(NUM)        (10* ((NUM % 100 / 10 + 9) % 10) \
                                        + (NUM % 10 + 9) %10)
/* Added by l00301449 for CDMA STK, 2015-07-03, end */

#define TAF_SDC_ICC_ID_MAX_NUM                          (10)

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/


enum TAF_SDC_USSD_TRAN_MODE_ENUM
{
    TAF_SDC_USSD_NON_TRAN_MODE,                                     /* ��͸��:����֧�ֱ���� */
    TAF_SDC_USSD_TRAN_MODE,                                         /* ͸��:  ���岻����룬ֻ��͸�����ɺ�̨������� */
    TAF_SDC_USSD_TRAN_MODE_BUTT
};
typedef VOS_UINT8 TAF_SDC_USSD_TRAN_MODE_ENUM_UINT8;


enum TAF_SDC_ALPHA_TO_ASCII_TRAN_TABLE_ENUM
{
    TAF_SDC_ALPHA_TO_ASCII_TRAN_TABLE_DEF   = 0X0,                          /* Ĭ�ϵ��ַ���ת����*/
    TAF_SDC_ALPHA_TO_ASCII_TRAN_TABLE_TME,                                  /* TEM�ַ���ת��*/
    TAF_SDC_ALPHA_TO_ASCII_TRAN_TABLE_BUTT
};
typedef VOS_UINT8 TAF_SDC_ALPHA_TO_ASCII_TRAN_TABLE_ENUM_UINT8;


enum TAF_SDC_PLATFORM_RAT_TYPE_ENUM
{
    TAF_SDC_PLATFORM_RAT_GSM   = 0X0,
    TAF_SDC_PLATFORM_RAT_WCDMA,
    TAF_SDC_PLATFORM_RAT_LTE,
    TAF_SDC_PLATFORM_RAT_TDS,
    TAF_SDC_PLATFORM_RAT_1X,
    TAF_SDC_PLATFORM_RAT_HRPD,
    /* Added by y00314741 for CDMA Iteration 15, 2015-5-14, begin */
    TAF_SDC_PLATFORM_RAT_EHRPD,
    /* Added by y00314741 for CDMA Iteration 15, 2015-5-14, end */
    TAF_SDC_PLATFORM_RAT_BUTT
};
typedef VOS_UINT8 TAF_SDC_PLATFORM_RAT_TYPE_ENUM_UINT8;


enum TAF_SDC_INIT_CTX_TYPE_ENUM
{
    TAF_SDC_INIT_CTX_STARTUP                    = 0,
    TAF_SDC_INIT_CTX_POWEROFF                   = 1,
    TAF_SDC_INIT_CTX_BUTT
};
typedef VOS_UINT8 TAF_SDC_INIT_CTX_TYPE_ENUM_UINT8;



enum TAF_SDC_SYS_SUBMODE_ENUM
{
    TAF_SDC_SYS_SUBMODE_NONE                = 0,                                /* �޷��� */
    TAF_SDC_SYS_SUBMODE_GSM                 = 1,                                /* GSMģʽ */
    TAF_SDC_SYS_SUBMODE_GPRS                = 2,                                /* GPRSģʽ */
    TAF_SDC_SYS_SUBMODE_EDGE                = 3,                                /* EDGEģʽ */
    TAF_SDC_SYS_SUBMODE_WCDMA               = 4,                                /* WCDMAģʽ */
    TAF_SDC_SYS_SUBMODE_HSDPA               = 5,                                /* HSDPAģʽ */
    TAF_SDC_SYS_SUBMODE_HSUPA               = 6,                                /* HSUPAģʽ */
    TAF_SDC_SYS_SUBMODE_HSDPA_HSUPA         = 7,                                /* HSDPA+HSUPAģʽ */
    TAF_SDC_SYS_SUBMODE_TD_SCDMA            = 8,                                /* TD_SCDMAģʽ */
    TAF_SDC_SYS_SUBMODE_HSPA_PLUS           = 9,                                /* HSPA+ģʽ */
    TAF_SDC_SYS_SUBMODE_LTE                 = 10,                               /* LTEģʽ */
    TAF_SDC_SYS_SUBMODE_DC_HSPA_PLUS        = 17,                               /* DC-HSPA+ģʽ */
    TAF_SDC_SYS_SUBMODE_DC_MIMO             = 18,                               /* MIMO-HSPA+ģʽ */

    TAF_SDC_SYS_SUBMODE_CDMA_1X             = 23,                               /* CDMA2000 1X*/
    /* Added by m00312079 for CDMA Iteration 12 2015-6-2 begin */
    TAF_SDC_SYS_SUBMODE_EVDO_REL_0          = 24,                               /* EVDO Rel0*/
    /* Added by m00312079 for CDMA Iteration 12 2015-6-2 end */
    TAF_SDC_SYS_SUBMODE_EVDO_REL_A          = 25,                               /* EVDO RelA*/
    /* Added by m00312079 for CDMA Iteration 12 2015-6-3 begin */
    TAF_SDC_SYS_SUBMODE_HYBRID_EVDO_REL_0   = 28,                               /* Hybrid(EVDO Rel0)*/
    /* Added by m00312079 for CDMA Iteration 12 2015-6-3 end */
    TAF_SDC_SYS_SUBMODE_HYBRID_EVDO_REL_A   = 29,                               /* Hybrid(EVDO RelA)*/

    TAF_SDC_SYS_SUBMODE_EHRPD               = 31,                               /* EHRPDģʽ*/

    TAF_SDC_SYS_SUBMODE_BUTT
};
typedef VOS_UINT8  TAF_SDC_SYS_SUBMODE_ENUM_UINT8;
enum TAF_SDC_SYS_MODE_ENUM
{
    TAF_SDC_SYS_MODE_GSM,
    TAF_SDC_SYS_MODE_WCDMA,
    TAF_SDC_SYS_MODE_LTE,

    TAF_SDC_SYS_MODE_CDMA_1X,
    TAF_SDC_SYS_MODE_EVDO,
    TAF_SDC_SYS_MODE_HYBRID,
    TAF_SDC_SYS_MODE_SVLTE,

    TAF_SDC_SYS_MODE_BUTT
};
typedef VOS_UINT8  TAF_SDC_SYS_MODE_ENUM_UINT8;


enum TAF_SDC_COPS_FORMAT_TYPE_ENUM
{
    TAF_SDC_COPS_FORMAT_TYPE_LONG_ALPH,          /* cops������ʾ���ַ�����Ӫ������*/
    TAF_SDC_COPS_FORMAT_TYPE_SHORT_ALPH,         /* cops������ʾ���ַ�����Ӫ������*/
    TAF_SDC_COPS_FORMAT_TYPE_NUMERIC,            /* cops������ʾ���ָ�ʽ��Ӫ������   */
    TAF_SDC_COPS_FORMAT_TYPE_BUTT
};
typedef VOS_UINT8  TAF_SDC_COPS_FORMAT_TYPE_ENUM_UINT8;
enum TAF_SDC_FILE_TYPE_ENUM
{
    TAF_SDC_FILE_TYPE_SIM = 1,
    TAF_SDC_FILE_TYPE_USIM,
    TAF_SDC_FILE_TYPE_BUTT
};
typedef VOS_UINT8  TAF_SDC_FILE_TYPE_ENUM_UINT8;



enum TAF_SDC_OPER_NAME_TYPE_ENUM
{
    TAF_SDC_OPER_NAME_TYPE_PNN = 1,
    TAF_SDC_OPER_NAME_TYPE_CPHS,
    TAF_SDC_OPER_NAME_TYPE_SPN,
    TAF_SDC_OPER_NAME_TYPE_MMINFO,
    TAF_SDC_OPER_NAME_TYPE_BUTT
};
typedef VOS_UINT8  TAF_SDC_OPER_NAME_TYPE_ENUM_UINT8;




enum TAF_SDC_SERVICE_STATUS_ENUM
{
    TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE           = 0,                        /* �������� */
    TAF_SDC_SERVICE_STATUS_LIMITED_SERVICE          = 1,                        /* ���Ʒ��� */
    TAF_SDC_SERVICE_STATUS_LIMITED_SERVICE_REGION   = 2,                        /* ������������� */
    TAF_SDC_SERVICE_STATUS_NO_IMSI                  = 3,                        /* ��imsi */
    TAF_SDC_SERVICE_STATUS_NO_SERVICE               = 4,                        /* �޷��� */
    TAF_SDC_SERVICE_STATUS_NO_CHANGE                = 5,
    TAF_SDC_SERVICE_STATUS_DEEP_SLEEP               = 6,
    TAF_SDC_SERVICE_STATUS_BUTT
};
typedef VOS_UINT8 TAF_SDC_SERVICE_STATUS_ENUM_UINT8;

/*****************************************************************************
    ö����    : TAF_SDC_IMS_NORMAL_REG_STATUS_ENUM
    ö��˵��  : ims����ͨע��״̬
*****************************************************************************/
enum TAF_SDC_IMS_NORMAL_REG_STATUS_ENUM
{
    TAF_SDC_IMS_NORMAL_REG_STATUS_DEREG        = 0x00,
    TAF_SDC_IMS_NORMAL_REG_STATUS_DEREGING     = 0x01,
    TAF_SDC_IMS_NORMAL_REG_STATUS_REGING       = 0x02,
    TAF_SDC_IMS_NORMAL_REG_STATUS_REG          = 0x03,

    TAF_SDC_IMS_NORMAL_REG_STATUS_BUTT         = 0xFF
};
typedef VOS_UINT8 TAF_SDC_IMS_NORMAL_REG_STATUS_ENUM_UINT8;



enum TAF_SDC_RPT_SRVSTA_ENUM
{
    TAF_SDC_REPORT_SRVSTA_NO_SERVICE               = 0,                         /* �޷��� */
    TAF_SDC_REPORT_SRVSTA_LIMITED_SERVICE          = 1,                         /* ���Ʒ��� */
    TAF_SDC_REPORT_SRVSTA_NORMAL_SERVICE           = 2,                         /* �������� */
    TAF_SDC_REPORT_SRVSTA_REGIONAL_LIMITED_SERVICE = 3,                         /* ���޵�������� */
    TAF_SDC_REPORT_SRVSTA_DEEP_SLEEP               = 4,                         /* ʡ�����˯��״̬ */
    TAF_SDC_REPORT_SRVSTA_BUTT
};
typedef VOS_UINT8  TAF_SDC_REPORT_SRVSTA_ENUM_UINT8;
enum  TAF_SDC_CELL_RESTRICTION_TYPE_ENUM
{
    TAF_SDC_CELL_RESTRICTION_TYPE_NONE                   = 0,                   /* ��ǰС���������κ�ҵ�� */
    TAF_SDC_CELL_RESTRICTION_TYPE_NORMAL_SERVICE         = 1,                   /* ��ǰС����������ҵ�� */
    TAF_SDC_CELL_RESTRICTION_TYPE_EMERGENCY_SERVICE      = 2,                   /* ��ǰС�����ƽ���ҵ�� */
    TAF_SDC_CELL_RESTRICTION_TYPE_ALL_SERVICE            = 3,                   /* ��ǰС����������ҵ��ͽ���ҵ�� */
    TAF_SDC_CELL_RESTRICTION_TYPE_BUTT
};
typedef VOS_UINT8  TAF_SDC_CELL_RESTRICTION_TYPE_ENUM_UINT8;


enum  TAF_SDC_USIM_STATUS_ENUM
{
    TAF_SDC_USIM_STATUS_UNVALID         = 0,                                    /* ��ʼ����״̬ */
    TAF_SDC_USIM_STATUS_VALID           = 1,                                    /* ��������CS/PS������Ч */
    TAF_SDC_USIM_STATUS_CS_UNVALID      = 2,
    TAF_SDC_USIM_STATUS_PS_UNVALID      = 3,
    TAF_SDC_USIM_STATUS_CS_PS_UNVALID   = 4,
    TAF_SDC_USIM_STATUS_SIM_PIN         = 5,                                    /* SIM����������PIN��ԭ�򲻿��� */
    TAF_SDC_USIM_STATUS_SIM_PUK         = 6,                                    /* SIM����������PUK��ԭ�򲻿��� */
    TAF_SDC_USIM_STATUS_NET_LCOK        = 7,                                    /* SIM������������������ԭ�򲻿��� */
    TAF_SDC_USIM_STATUS_IMSI_LCOK       = 8,                                    /* SIM����������IMSI����ԭ�򲻿��� */

    TAF_SDC_USIM_STATUS_READY_TIMEROUT  = 9,                                    /* �ȴ�usim��ʱ����ʱԭ�򲻿��� */

    TAF_SDC_USIM_STATUS_ROMSIM          = 240,
    TAF_SDC_USIM_STATUS_NO_PRESENT      = 255,
    TAF_SDC_USIM_STATUS_BUTT            = 254
};

typedef VOS_UINT8  TAF_SDC_USIM_STATUS_ENUM_UINT8;
enum TAF_SDC_SIM_TYPE_ENUM
{
    TAF_SDC_SIM_TYPE_SIM                ,                   /* SIM�� */
    TAF_SDC_SIM_TYPE_USIM               ,                   /* USIM�� */
    TAF_SDC_SIM_TYPE_ROM_SIM            ,
    TAF_SDC_SIM_TYPE_UIM                ,                   /*UIM��*/
    TAF_SDC_SIM_TYPE_CSIM               ,                   /*CSIM��*/
    TAF_SDC_SIM_TYPE_BUTT
};
typedef VOS_UINT8 TAF_SDC_SIM_TYPE_ENUM_UINT8;




enum TAF_SDC_SERVICE_DOMAIN_ENUM
{
    TAF_SDC_SERVICE_DOMAIN_NO_DOMAIN = 0,                                       /* �޷��� */
    TAF_SDC_SERVICE_DOMAIN_CS        = 1,                                       /* ��CS���� */
    TAF_SDC_SERVICE_DOMAIN_PS        = 2,                                       /* ��PS���� */
    TAF_SDC_SERVICE_DOMAIN_CS_PS     = 3,                                       /* PS+CS���� */
    TAF_SDC_SERVICE_DOMAIN_SEARCHING = 4,                                       /* CS��PS��δע�ᣬ����������״̬ */
    TAF_SDC_SERVICE_DOMAIN_BUTT
};
typedef VOS_UINT8  TAF_SDC_SERVICE_DOMAIN_ENUM_UINT8;
enum TAF_SDC_REG_STATUS_ENUM
{
    TAF_SDC_REG_NOT_REGISTERED_NOT_SEARCH,                                      /* δע��δ���� */
    TAF_SDC_REG_REGISTERED_HOME_NETWORK,                                        /* ע�ᣬע���� HOME PLMN */
    TAF_SDC_REG_NOT_REGISTERED_SEARCHING,                                       /* δע�ᣬ��������PLMN�������ڸ��Ź��� */
    TAF_SDC_REG_REGISTERED_DENIED,                                              /* ע�ᱻ�ܾ�����ǰ�û�����������ע�ᣬ�������񱻽�ֹ */
    TAF_SDC_REG_UNKNOWN,                                                        /* ������� */
    TAF_SDC_REG_REGISTERED_ROAM,                                                /* ע�ᣬע���ڷ� HOME PLMN */
    TAF_SDC_REG_STATUS_BUTT
};
typedef VOS_UINT8 TAF_SDC_REG_STATUS_ENUM_UINT8;



enum TAF_SDC_RPT_CMD_INDEX_ENUM
{
    TAF_SDC_RPT_CMD_MODE                     = 0,
    TAF_SDC_RPT_CMD_RSSI,
    TAF_SDC_RPT_CMD_REJINFO,
    TAF_SDC_RPT_CMD_SRVST,
    TAF_SDC_RPT_CMD_PLMNSELEINFO,
    TAF_SDC_RPT_CMD_SIMST,
    TAF_SDC_RPT_CMD_TIME,
    TAF_SDC_RPT_CMD_SMMEMFULL,
    TAF_SDC_RPT_CMD_CTZV,
    TAF_SDC_RPT_CMD_DSFLOWRPT,
    TAF_SDC_RPT_CMD_ORIG,
    TAF_SDC_RPT_CMD_CONF,
    TAF_SDC_RPT_CMD_CONN,
    TAF_SDC_RPT_CMD_CEND,
    TAF_SDC_RPT_CMD_STIN,
    TAF_SDC_RPT_CMD_CERSSI,
    TAF_SDC_RPT_CMD_ANLEVEL,
    TAF_SDC_RPT_CMD_SRCHEDPLMNINFO,
    TAF_SDC_RPT_CMD_LWCLASH,
    TAF_SDC_RPT_CMD_XLEMA,
    TAF_SDC_RPT_CMD_ACINFO,
    TAF_SDC_RPT_CMD_PLMN,
    TAF_SDC_RPT_CMD_CALLSTATE,

    /* ���䵥�����������ϱ���ö�� */
    TAF_SDC_RPT_CMD_CREG,
    TAF_SDC_RPT_CMD_CGREG,
    TAF_SDC_RPT_CMD_CEREG,
    TAF_SDC_RPT_CMD_CTZR,
    TAF_SDC_RPT_CMD_CUSD,
    TAF_SDC_RPT_CMD_CSSI,
    TAF_SDC_RPT_CMD_CSSU,
    TAF_SDC_RPT_CMD_LWURC,
    TAF_SDC_RPT_CMD_CUUS1I,
    TAF_SDC_RPT_CMD_CUUS1U,
    TAF_SDC_RPT_CMD_NCELLMONITOR,

    TAF_SDC_RPT_CMD_MIPICLK,

    TAF_SDC_RPT_CMD_CSID,

    /* Added by x00314862 for CDMA 1X Iteration 6 2014-12-27 begin */
    TAF_SDC_RPT_CMD_CTIME,
    /* Added by x00314862 for CDMA 1X Iteration 6 2014-12-27 end */
    TAF_SDC_RPT_CMD_XPASSINFO,

    /* Added by c00318887 for AT&T phaseII, 2015-2-15, begin */
    TAF_SDC_RPT_CMD_FILECHANGE,
    /* Added by c00318887 for AT&T phaseII, 2015-2-15, end */

    /* Added by w00351686 for CDMA Iteration 16 2015-7-25 begin */
    TAF_SDC_RPT_CMD_CCONTDTMF,
    TAF_SDC_RPT_CMD_CBURSTDTMF,
    /* Added by w00351686 for CDMA Iteration 16 2015-7-25 end */

    TAF_SDC_RPT_CMD_BUTT
};
typedef VOS_UINT8 TAF_SDC_RPT_CMD_INDEX_ENUM_UINT8;
enum TAF_SDC_CALL_STATE_RPT_STATUS_ENUM
{
    TAF_SDC_CALL_STATE_RPT_STATUS_DISABLE,                 /* �����������ϱ� */
    TAF_SDC_CALL_STATE_RPT_STATUS_ENABLE,                  /* ���������ϱ� */
    TAF_SDC_CALL_STATE_RPT_STATUS_BUTT
};
typedef VOS_UINT8 TAF_SDC_CALL_STATE_RPT_STATUS_ENUM_UINT8;


enum TAF_SDC_CMD_RPT_CTRL_TYPE_ENUM
{
    TAF_SDC_CMD_RPT_CTRL_BY_CURC,               /* �����ϱ���CURC���� */
    TAF_SDC_CMD_RPT_CTRL_BY_UNSOLICITED,        /* �����ϱ��ܵ������������ */
    TAF_SDC_CMD_RPT_CTRL_BUTT
};
typedef VOS_UINT8 TAF_SDC_CMD_RPT_CTRL_TYPE_ENUM_UINT8;


enum TAF_SDC_STATUS_RPT_GENERAL_CTRL_TYPE_ENUM
{
    TAF_SDC_STATUS_RPT_GENERAL_CONTROL_TYPE_NO_REPORT = 0,
    TAF_SDC_STATUS_RPT_GENERAL_CONTROL_TYPE_REPORT    = 1,
    TAF_SDC_STATUS_RPT_GENERAL_CONTROL_TYPE_CUSTOM    = 2,
    TAF_SDC_STATUS_RPT_GENERAL_CONTROL_TYPE_BUTT
};
typedef VOS_UINT8 TAF_SDC_STATUS_RPT_GENERAL_CTRL_TYPE_ENUM_UINT8;


/*****************************************************************************
 ö����    : TAF_SDC_NW_IMS_VOICE_CAP_ENUM_UINT8
 �ṹ˵��  : IMS voice capability
 1.��    ��   : 2013��7��13��
   ��    ��   : y0024524
   �޸�����   : �½�
*****************************************************************************/
enum TAF_SDC_NW_IMS_VOICE_CAP_ENUM
{
    TAF_SDC_NW_IMS_VOICE_NOT_SUPPORTED    = 0,
    TAF_SDC_NW_IMS_VOICE_SUPPORTED        = 1,

    TAF_SDC_NW_IMS_VOICE_BUTT
};
typedef VOS_UINT8 TAF_SDC_NW_IMS_VOICE_CAP_ENUM_UINT8;


enum TAF_SDC_NW_EMC_BS_CAP_ENUM
{
    TAF_SDC_NW_EMC_BS_NOT_SUPPORTED       = 0,
    TAF_SDC_NW_EMC_BS_SUPPORTED           = 1,

    TAF_SDC_NW_EMC_BS_BUTT
};
typedef VOS_UINT8 TAF_SDC_NW_EMC_BS_CAP_ENUM_UINT8;


enum TAF_SDC_LTE_CS_CAPBILITY_ENUM
{
    TAF_SDC_LTE_CS_CAPBILITY_NO_ADDITION_INFO  = 0,
    TAF_SDC_LTE_CS_CAPBILITY_CSFB_NOT_PREFER   = 1,
    TAF_SDC_LTE_CS_CAPBILITY_SMS_ONLY          = 2,
    TAF_SDC_LTE_CS_CAPBILITY_NOT_SUPPORTED     = 3,

    TAF_SDC_LTE_CS_CAPBILITY_BUTT
};
typedef VOS_UINT8 TAF_SDC_LTE_CS_CAPBILITY_ENUM_UINT8;


enum TAF_SDC_VOICE_DOMAIN_ENUM
{
    TAF_SDC_VOICE_DOMAIN_CS_ONLY            = 0,                                /**< CS voice only */
    TAF_SDC_VOICE_DOMAIN_IMS_PS_ONLY        = 1,                                /**< IMS PS voice only */
    TAF_SDC_VOICE_DOMAIN_CS_PREFERRED       = 2,                                /**< CS voice preferred, IMS PS Voice as secondary */
    TAF_SDC_VOICE_DOMAIN_IMS_PS_PREFERRED   = 3,                                /**< IMS PS voice preferred, CS Voice as secondary */

    TAF_SDC_VOICE_DOMAIN_BUTT
};
typedef VOS_UINT32 TAF_SDC_VOICE_DOMAIN_ENUM_UINT32;


enum TAF_SDC_SMS_DOMAIN_ENUM
{
    TAF_SDC_SMS_DOMAIN_NOT_USE_SMS_OVER_IP                  = 0,                /**< not to use SMS over ip */
    TAF_SDC_SMS_DOMAIN_PREFER_TO_USE_SMS_OVER_IP            = 1,                /**< prefer to use SMS over ip, CS/PS SMS as secondary */

    TAF_SDC_SMS_DOMAIN_BUTT
};
typedef VOS_UINT8 TAF_SDC_SMS_DOMAIN_ENUM_UINT8;


enum TAF_SDC_LTE_CS_SERVICE_ENUM
{
    TAF_SDC_LTE_SUPPORT_CSFB_AND_SMS_OVER_SGS = 1,                              /* ֧��cs fallback��sms over sgs*/
    TAF_SDC_LTE_SUPPORT_SMS_OVER_SGS_ONLY,                                      /* ֧��sms over sgs only*/
    TAF_SDC_LTE_SUPPORT_1XCSFB,                                                 /* ֧��1XCSFB */
    TAF_SDC_LTE_SUPPORT_BUTT
};
typedef VOS_UINT8 TAF_SDC_LTE_CS_SERVICE_ENUM_UINT8;
enum TAF_SDC_UE_USAGE_SETTING_ENUM
{
    TAF_SDC_UE_USAGE_VOICE_CENTRIC      = 0,                                    /* �������� */
    TAF_SDC_UE_USAGE_DATA_CENTRIC,                                              /* �������� */

    TAF_SDC_UE_USAGE_BUTT
};
typedef VOS_UINT8 TAF_SDC_UE_USAGE_SETTING_ENUM_UINT8;


enum TAF_SDC_PHONE_MODE_ENUM
{
    TAF_SDC_PHONE_MODE_MINI                = 0,   /* minimum functionality*/
    TAF_SDC_PHONE_MODE_FULL                = 1,   /* full functionality */
    TAF_SDC_PHONE_MODE_TXOFF               = 2,   /* disable phone transmit RF circuits only */
    TAF_SDC_PHONE_MODE_RXOFF               = 3,   /* disable phone receive RF circuits only */
    TAF_SDC_PHONE_MODE_RFOFF               = 4,   /* disable phone both transmit and receive RF circuits */
    TAF_SDC_PHONE_MODE_FT                  = 5,   /* factory-test functionality */
    TAF_SDC_PHONE_MODE_RESET               = 6,   /* reset */
    TAF_SDC_PHONE_MODE_VDFMINI             = 7,   /* mini mode required by VDF*/
    TAF_SDC_PHONE_MODE_POWEROFF            = 8,   /* �ػ��µ�ģʽ */
    TAF_SDC_PHONE_MODE_LOWPOWER            = 9,
    TAF_SDC_PHONE_MODE_BUTT
};
typedef VOS_UINT8 TAF_SDC_PHONE_MODE_ENUM_UINT8;
enum TAF_SDC_CALL_MODE_ENUM
{
    TAF_SDC_ECALL_ONLY            = 0,
    TAF_SDC_ECALL_AND_NORMAL_CALL = 1,
    TAF_SDC_CALL_MODE_BUTT
};
typedef VOS_UINT32 TAF_SDC_CALL_MODE_ENUM_UINT8;



enum TAF_SDC_LMM_ACCESS_TYPE_ENUM
{
    TAF_SDC_LMM_ACCESS_TYPE_EUTRAN_TDD      = 0,
    TAF_SDC_LMM_ACCESS_TYPE_EUTRAN_FDD         ,
    TAF_SDC_LMM_ACCESS_TYPE_BUTT
};
typedef VOS_UINT8 TAF_SDC_LMM_ACCESS_TYPE_ENUM_UINT8;


enum TAF_SDC_NETWORK_NAME_CODE_SCHEME_ENUM
{
    TAF_SDC_NETWORK_NAME_CODE_SCHEME_7BIT         = 0,
    TAF_SDC_NETWORK_NAME_CODE_SCHEME_COPS_UCS2    = 1,
    TAF_SDC_NETWORK_NAME_CODE_SCHEME_EONS_UCS2    = 2,
    TAF_SDC_NETWORK_NAME_CODE_SCHEME_BUTT
};
typedef VOS_UINT8 TAF_SDC_NETWORK_NAME_CODE_SCHEME_ENUM_UINT8;



enum TAF_SDC_CREG_TYPE_ENUM
{
    TAF_SDC_CREG_TYPE_NOT_REPORT        = 0,
    TAF_SDC_CREG_TYPE_BREVITE           = 1,
    TAF_SDC_CREG_TYPE_ENTIRE            = 2,
    TAF_SDC_CREG_TYPE_BUTT
};
typedef VOS_UINT8 TAF_SDC_CREG_TYPE_ENUM_UINT8;


enum TAF_SDC_CGREG_TYPE_ENUM
{
    TAF_SDC_CGREG_TYPE_NOT_REPORT       = 0,
    TAF_SDC_CGREG_TYPE_BREVITE          = 1,
    TAF_SDC_CGREG_TYPE_ENTIRE           = 2,
    TAF_SDC_CGREG_TYPE_BUTT
};
typedef VOS_UINT8 TAF_SDC_CGREG_TYPE_ENUM_UINT8;


enum TAF_SDC_CEREG_TYPE_ENUM
{
    TAF_SDC_CEREG_TYPE_NOT_REPORT       = 0,
    TAF_SDC_CEREG_TYPE_BREVITE          = 1,
    TAF_SDC_CEREG_TYPE_ENTIRE           = 2,
    TAF_SDC_CEREG_TYPE_BUTT
};
typedef VOS_UINT8 TAF_SDC_CEREG_TYPE_ENUM_UINT8;


/* Added by m00312079 for CDMA 1X Iteration 6 2014-12-27 begin */
/*****************************************************************************
 ö����    : TAF_SDC_CDMACSQ_MODE_ENUM_UINT8
 �ṹ˵��  :
 1.��    ��   : 2014��12��27��
   ��    ��   : m00312079
   �޸�����   : �½�
*****************************************************************************/
enum TAF_SDC_CDMACSQ_MODE_ENUM
{
    TAF_SDC_CDMACSQ_MODE_DISABLE      = 0,
    TAF_SDC_CDMACSQ_MODE_ENABLE       = 1,
    TAF_SDC_CDMACSQ_MODE_BUTT
};

typedef VOS_UINT8 TAF_SDC_CDMACSQ_MODE_ENUM_UINT8;
/* Added by m00312079 for CDMA 1X Iteration 6 2014-12-27 end */

enum TAF_SDC_SYS_ROAMING_IND_ENUM
{
    /* Roaming Indicator On */
    TAF_SDC_SYS_ROAMING_STATUS_ON                              = 0,

    /* Roaming Indicator Off */
    TAF_SDC_SYS_ROAMING_STATUS_OFF                             = 1,

    /* Roaming Indicator Flashing */
    TAF_SDC_SYS_ROAMING_STATUS_FLASHING                        = 2,

    /* Out of Neighborhood */
    TAF_SDC_SYS_ROAMING_STATUS_OUT_OF_NEIGHBORHOOD             = 3,

    /* Out of Building */
    TAF_SDC_SYS_ROAMING_STATUS_OUT_OF_BUILDING                 = 4,

    /* Roaming - Preferred System */
    TAF_SDC_SYS_ROAMING_STATUS_PREFERRED_SYSTEM                = 5,

    /* Roaming - Available System */
    TAF_SDC_SYS_ROAMING_STATUS_AVAILABLE_SYSTEM                = 6,

    /* Roaming - Alliance Partner */
    TAF_SDC_SYS_ROAMING_STATUS_ALLIANCE_PARTNER                = 7,

    /* Roaming - Premium Partner */
    TAF_SDC_SYS_ROAMING_STATUS_PREMIUM_PARTER                  = 8,

    /* Roaming - Full Service Functionality */
    TAF_SDC_SYS_ROAMING_STATUS_FULL_SRVICE_FUNCTIONALITY       = 9,

    /* Roaming - Partial Service Functionality */
    TAF_SDC_SYS_ROAMING_STATUS_PARTIAL_SRVICE_FUNCTIONALITY    = 10,

    /* Roaming Banner On */
    TAF_SDC_SYS_ROAMING_STATUS_BANNER_ON                       = 11,

    /* Roaming Banner Off */
    TAF_SDC_SYS_ROAMING_STATUS_BANNER_OFF                      = 12,

    TAF_SDC_SYS_ROAMING_STATUS_RESERVED_FOR_STARDARD_EN        = 13,

    /* 01000000 through 01111111 Reserved for Non-Standard Enhanced Roaming Indicator Numbers */
    TAF_SDC_SYS_ROAMING_STATUS_RESERVED_FOR_NON_STARDARD_EN    = 64,

    /* 10000000 through 11111111 Reserved */
    TAF_SDC_SYS_ROAMING_STATUS_RESERVED                        = 128
};
typedef VOS_UINT8 TAF_SDC_PRL_SYS_ROAMING_IND_ENUM_UINT8;
enum TAF_SDC_IMS_SWITCH_STATE_ENUM
{
    TAF_SDC_IMS_SWITCH_STATE_OFF        = 0,
    TAF_SDC_IMS_SWITCH_STATE_ON         = 1,
    TAF_SDC_IMS_SWITCH_STATE_BUTT
};
typedef VOS_UINT8 TAF_SDC_IMS_SWITCH_STATE_ENUM_UINT8;

/* Modified by l00301449 for CDMA Iteration 15, 2015-5-15, begin */
/*****************************************************************************
 ö����    : TAF_SDC_SRV_ACQ_RAT_TYPE_ENUM_UINT8
 ö��˵��  : ҵ�񴥷�������RAT����
 1.��    ��   : 2014��5��15��
   ��    ��   : l00301449
   �޸�����   : �½�
*****************************************************************************/
enum TAF_SDC_SRV_ACQ_RAT_TYPE_ENUM
{
    TAF_SDC_SRV_ACQ_RAT_TYPE_3GPP,
    TAF_SDC_SRV_ACQ_RAT_TYPE_1X,
    TAF_SDC_SRV_ACQ_RAT_TYPE_HRPD,
    TAF_SDC_SRV_ACQ_RAT_TYPE_BUTT
};

typedef VOS_UINT8 TAF_SDC_SRV_ACQ_RAT_TYPE_ENUM_UINT8;

/* Modified by l00301449 for CDMA Iteration 15, 2015-5-15, end */

enum TAF_SDC_1X_UE_MAIN_STATUS_ENUM
{
    TAF_SDC_1X_UE_MAIN_STATUS_INIT_STATE            = 0x00,
    TAF_SDC_1X_UE_MAIN_STATUS_IDLE_STATE            = 0x01,
    TAF_SDC_1X_UE_MAIN_STATUS_ACCESS_STATE          = 0x02,
    TAF_SDC_1X_UE_MAIN_STATUS_TCH_STATE             = 0x03,
    TAF_SDC_1X_UE_MAIN_STATUS_NO_SERVICE_STATE      = 0x04,
    TAF_SDC_1X_UE_MAIN_STATUS_STATE_ENUM_BUTT       = 0x05
};

typedef VOS_UINT8 TAF_SDC_1X_UE_MAIN_STATUS_ENUM_UINT8;



enum TAF_SDC_1X_UE_SUB_STATUS_ENUM
{
    TAF_SDC_1X_UE_SUB_STATUS_NULL                                    = 0x00,
    TAF_SDC_1X_UE_SUB_STATUS_INIT_DETERM_SUB_STATE                   = 0x01,
    TAF_SDC_1X_UE_SUB_STATUS_PILOT_CH_ACQ_SUB_STATE                  = 0x02,
    TAF_SDC_1X_UE_SUB_STATUS_SYNC_CH_ACQ_SUB_STATE                   = 0x03,
    TAF_SDC_1X_UE_SUB_STATUS_TIMING_CHNG_SUB_STATE                   = 0x04,
    TAF_SDC_1X_UE_SUB_STATUS_IDLE_SUB_STATE                          = 0x10,
    TAF_SDC_1X_UE_SUB_STATUS_UPDATE_OVERHEAD_SUB_STATE               = 0x20,
    TAF_SDC_1X_UE_SUB_STATUS_MOB_STATION_ORIG_ATTEMPT_SUB_STATE      = 0x21,
    TAF_SDC_1X_UE_SUB_STATUS_PAG_RESP_SUB_STATE                      = 0x22,
    TAF_SDC_1X_UE_SUB_STATUS_MOB_STATION_ORDR_RESP_SUB_STATE         = 0x23,
    TAF_SDC_1X_UE_SUB_STATUS_REG_ACCESS_SUB_STATE                    = 0x24,
    TAF_SDC_1X_UE_SUB_STATUS_MOB_STATION_MSG_TRANS_SUB_STATE         = 0x25,
    TAF_SDC_1X_UE_SUB_STATUS_TCH_INIT_SUB_STATE                      = 0x30,
    TAF_SDC_1X_UE_SUB_STATUS_REL_SUB_STATE                           = 0x31,
    TAF_SDC_1X_UE_SUB_STATUS_WAIT_FOR_SERVICE_SUB_STATE              = 0x40,
    TAF_SDC_1X_UE_SUB_STATUS_SUB_STATE_ENUM_BUTT                     = 0x41

};

typedef VOS_UINT8 TAF_SDC_1X_UE_SUB_STATUS_ENUM_UINT8;




/* Modified by h00313353 for CDMA Iteration 15, 2015-5-30, begin */

enum TAF_SDC_NETWORK_EXISTANCE_ENUM
{
    TAF_SDC_1X_NETWORK_EXIST                           = 0,              /* 1x has network */
    TAF_SDC_1X_NETWORK_NOT_EXIST                       = 1,              /* 1x does not have network */
    TAF_SDC_HRPD_NETWORK_EXIST                         = 2,              /* hrpd has network */
    TAF_SDC_HRPD_NETWORK_NOT_EXIST                     = 3,              /* hrpd does not have network */
    TAF_SDC_LTE_NETWORK_EXIST                          = 4,
    TAF_SDC_LTE_NETWORK_NOT_EXIST                      = 5,
    TAF_SDC_NETWORK_BUT
};
typedef VOS_UINT32 TAF_SDC_NETWORK_EXISTANCE_ENUM_UINT32;
/* Modified by h00313353 for CDMA Iteration 15, 2015-5-30, end */

typedef struct
{
    VOS_UINT32                                   bitOpCsSrvSta     : 1;
    VOS_UINT32                                   bitOpPsSrvSta     : 1;
    VOS_UINT32                                   bitOpCsRegSta     : 1;
    VOS_UINT32                                   bitOpPsRegSta     : 1;
    VOS_UINT32                                   bitOpSrvDomain    : 1;
    VOS_UINT32                                   bitOpSrvSta       : 1;
    VOS_UINT32                                   bitSpare          : 26;

    TAF_SDC_SERVICE_STATUS_ENUM_UINT8            enCsSrvSta;
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8            enPsSrvSta;
    TAF_SDC_REG_STATUS_ENUM_UINT8                enCsRegSta;
    TAF_SDC_REG_STATUS_ENUM_UINT8                enPsRegSta;
    TAF_SDC_SERVICE_DOMAIN_ENUM_UINT8            enSrvDomain;
    TAF_SDC_REPORT_SRVSTA_ENUM_UINT8             enSrvSta;
}TAF_SDC_SRV_REG_INFO_STRU;


typedef VOS_VOID  (*pTafSdcSysmodServiceRegStaUpdateFunc)(
    TAF_SDC_SRV_REG_INFO_STRU          *pstSrvInfo
);

/* Modified by h00313353 for CDMA Iteration 15, 2015-5-30, begin */

typedef struct
{
    TAF_SDC_NETWORK_EXISTANCE_ENUM_UINT32                   enCdmaNetworkExist;
    TAF_SDC_SYS_MODE_ENUM_UINT8                             enCurSysMode;
    TAF_SDC_SYS_MODE_ENUM_UINT8                             enNewSysMode;
    TAF_SYS_SUBMODE_ENUM_UINT8                              enNewSubMode;
    pTafSdcSysmodServiceRegStaUpdateFunc                    pfuncSysmodServiceRegStatusUpdate;
}TAF_SDC_MAP_SERVICE_STATUS_TO_SYSMODE_TLB_STRU;


/* Modified by h00313353 for CDMA Iteration 15, 2015-5-30, end */

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
    VOS_UINT8                                     ucRatNum;
    TAF_SDC_PLATFORM_RAT_TYPE_ENUM_UINT8          aenRatList[TAF_SDC_PLATFORM_MAX_RAT_NUM];
}TAF_SDC_PLATFORM_RAT_CAP_STRU;


typedef struct
{
    VOS_UINT8                           ucRatNum;
    TAF_SDC_SYS_MODE_ENUM_UINT8         aenRatPrio[TAF_SDC_MAX_RAT_NUM];
}TAF_SDC_RAT_PRIO_STRU;



typedef struct
{
    VOS_UINT8                           ucGsmImsSupportFlag;    /**< GSM IMSʹ����,VOS_TRUE :֧�֣�VOS_FALSE :��֧�� */
    VOS_UINT8                           ucUtranImsSupportFlag;  /**< UNTRAN IMSʹ����,VOS_TRUE :֧�֣�VOS_FALSE :��֧�� */
    VOS_UINT8                           ucLteImsSupportFlag;    /**< LTE IMSʹ����,VOS_TRUE :֧�֣�VOS_FALSE :��֧�� */
    VOS_UINT8                           ucGsmEmsSupportFlag;    /**< GSM EMSʹ����,VOS_TRUE :֧�֣�VOS_FALSE :��֧�� */
    VOS_UINT8                           ucUtranEmsSupportFlag;  /**< UNTRAN EMSʹ����,VOS_TRUE :֧�֣�VOS_FALSE :��֧�� */
    VOS_UINT8                           ucLteEmsSupportFlag;    /**< LTE EMSʹ����,VOS_TRUE :֧�֣�VOS_FALSE :��֧�� */
    VOS_UINT8                           aucReserved[2];
}TAF_SDC_IMS_RAT_SUPPORT_STRU;


typedef struct
{
    VOS_UINT8                           ucVoiceCallOnImsSupportFlag;            /* IMS����ʹ����,VOS_TRUE :֧�֣�VOS_FALSE :��֧�� */
    VOS_UINT8                           ucSmsOnImsSupportFlag;                  /* IMS����ʹ����,VOS_TRUE :֧�֣�VOS_FALSE :��֧�� */
    VOS_UINT8                           ucVideoCallOnImsSupportFlag;            /* IMS��VIDEO CALLʹ����,VOS_TRUE :֧�֣�VOS_FALSE :��֧�� */
    VOS_UINT8                           ucUssdOnImsSupportFlag;                 /* IMS USSDҵ��ʹ���VOS_TRUE :֧�֣�VOS_FALSE :��֧�� */
}TAF_SDC_IMS_CAPABILITY_STRU;


typedef struct
{
    VOS_UINT8                 ucImsRedialCauseNum;                                                  /* IMS call�ز�ԭ��ֵ���� */
    VOS_UINT8                 ucImsaRedialCauseNum;                                                 /* IMSA call�ز�ԭ��ֵ���� */
    VOS_UINT8                 aucReserve[2];
    VOS_UINT16                ausImsRedialCause[TAF_NVIM_IMS2CS_CALL_REDIAL_CAUSE_MAX_NUM];
    VOS_UINT16                ausImsaRedialCause[TAF_NVIM_IMSA2CS_CALL_REDIAL_CAUSE_MAX_NUM];
}TAF_SDC_SWITCH_IMS_TO_CS_REDIAL_CAUSE_CONFIG_STRU;


typedef struct
{
    VOS_UINT8                                               ucCallRedial;                           /* call�ز�flag */
    VOS_UINT8                                               ucSmsRedial;                            /* SMS �ز�flag */
    VOS_UINT8                                               ucSsRedial;                             /* SS  �ز�flag */
    VOS_UINT8                                               aucReserve[1];
    TAF_SDC_SWITCH_IMS_TO_CS_REDIAL_CAUSE_CONFIG_STRU       stCallRedialCauseCfg;
}TAF_SDC_SWITCH_IMS_TO_CS_REDIAL_CONFIG_STRU;
typedef struct
{
    VOS_UINT8                                               ucCallRedial;                           /* call�ز�flag */
    VOS_UINT8                                               ucSmsRedial;                            /* SMS �ز�flag */
    VOS_UINT8                                               ucSsRedial;                             /* SS  �ز�flag */
    VOS_UINT8                                               aucReserve[1];
}TAF_SDC_SWITCH_CS_TO_IMS_REDIAL_CONFIG_STRU;
typedef struct
{
    TAF_SDC_SWITCH_IMS_TO_CS_REDIAL_CONFIG_STRU             stRedialImsToCs;                        /* IMS to CS�ز����ݽṹ  */
    TAF_SDC_SWITCH_CS_TO_IMS_REDIAL_CONFIG_STRU             stRedialCsToIms;                        /* CS to IMS �ز����ݽṹ */
}TAF_SDC_SWITCH_DOMAIN_REDIAL_STRU;



typedef struct
{
    TAF_SDC_IMS_RAT_SUPPORT_STRU        stImsRatSupport;
    TAF_SDC_IMS_CAPABILITY_STRU         stImsCapability;
    TAF_SDC_LTE_CS_SERVICE_ENUM_UINT8   enLteCsServiceCfg;                      /* Lģ֧�ֵ�cs��ҵ������������ */
    TAF_SDC_SMS_DOMAIN_ENUM_UINT8       enSmsDomain;                            /* sms domain preferrece */
    VOS_UINT8                           ucRoamingSupport;
    VOS_UINT8                           aucReserved[1];
    TAF_SDC_SWITCH_DOMAIN_REDIAL_STRU   stRedial;                               /* IMS<-->CS�����ز���־ */
    TAF_SDC_VOICE_DOMAIN_ENUM_UINT32    enVoiceDomain;                          /* voice domain preferrece */

}TAF_SDC_IMS_CONFIG_PARA_STRU;


typedef struct
{
    VOS_UINT8                      ucCategoryValue;                                 /* Emergency Service Category Value         */
    VOS_UINT8                      ucEmcNumLen;                                     /* ���������볤�ȣ���aucEmergencyList����Ч����*/
    VOS_UINT8                      aucEmergencyList[TAF_SDC_EMER_NUM_MAX_LENGTH];   /* �������б� */
}TAF_SDC_EMERGENCY_CONTENT_STRU;
typedef struct
{
    VOS_UINT32                         ulMcc;                                               /* MCC */
    VOS_UINT8                          ucEmergencyNumber;                                   /* ���������� */
    VOS_UINT8                          aucReserved[3];
    TAF_SDC_EMERGENCY_CONTENT_STRU     astEmergencyLists[TAF_SDC_EMER_NUM_LISTS_MAX_NUMBER];/* �������б� */
}TAF_SDC_MM_EMERGENCY_LIST_STRU;
typedef struct
{
    VOS_UINT8                           ucCategory;                             /* �������������� */
    VOS_UINT8                           ucValidSimPresent;                      /* �������������п�ʱ��Ч�����޿�ʱ��Ч��1�п�ʱ��Ч��0�޿�ʱ��Ч */
    VOS_UINT8                           ucAbnormalServiceFlg;                   /* �����������п�ʱ�Ƿ���ڷ���������ʱ��Ч��0:�κη���ʱ����Ч��1:������������ʱ��Ч */
    VOS_UINT8                           ucEccNumLen;                            /* ���������볤�� */
    VOS_UINT8                           aucEccNum[TAF_SDC_MAX_BCD_NUM_LEN];     /* ���������� */
    VOS_UINT32                          ulMcc;                                  /* MCC,3 bytes */
} TAF_SDC_CUSTOM_ECC_NUM_STRU;



typedef struct
{
    VOS_UINT8                           ucEccNumCount;                                  /* �����Ÿ��� */
    VOS_UINT8                           aucReseve[3];
    TAF_SDC_CUSTOM_ECC_NUM_STRU         astCustomEccNumList[TAF_SDC_MAX_CUSTOM_ECC_NUM];/* �������б� */
} TAF_SDC_CUSTOM_ECC_NUM_LIST_STRU;


typedef struct
{
    VOS_UINT8                               ucCustomSetFlg;                     /* VOS_TRUE,����APP�������ö��ƽ��������룬VOS_FALSE,��ʾû�п�ʼ���� */
    VOS_UINT8                               aucReserve[3];
    TAF_SDC_CUSTOM_ECC_NUM_LIST_STRU        stCustomEccNumList;                 /* APP���ƵĽ������б� */
} TAF_SDC_CUSTOM_ECC_CTX_STRU;


typedef struct
{
    VOS_UINT8                                     ucLCEnableFlg;
    TAF_NVIM_LC_RAT_COMBINED_ENUM_UINT8           enRatCombined;
    TAF_NVIM_LC_WORK_CFG_ENUM_UINT8               enLCWorkCfg;
    VOS_UINT8                                     aucReserved[1];
}TAF_SDC_LC_CONFIG_PARA_STRU;


typedef struct
{
    TAF_SDC_PLATFORM_RAT_CAP_STRU       stPlatformRatCap;                       /* ƽ̨���뼼��������Ϣ */

    VOS_UINT8                           ucSvlteSupportFlag;                     /* �Ƿ�֧��SVLTE��־ */
    VOS_UINT8                           aucReserved[3];

    TAF_SDC_IMS_CONFIG_PARA_STRU       stImsConfigPara;                       /* IMS���������Ϣ */

    TAF_SDC_LC_CONFIG_PARA_STRU        stLcConfigPara;
#if (FEATURE_ON == FEATURE_BASTET)
    VOS_UINT8                           ucBastetSupportFlag;                     /* �Ƿ�֧��Bastet��־ */
    VOS_UINT8                           aucBstReserved[3];
#endif

}TAF_SDC_MS_CAP_INFO_STRU;



typedef struct {
    VOS_UINT8                           aucSimPlmn[TAF_SDC_SIM_FORMAT_PLMN_LEN];
    VOS_UINT8                           aucReserve[1];
} TAF_SDC_SIM_FORMAT_PLMN_ID;


typedef struct
{
    VOS_UINT32                          ulMcc;
    VOS_UINT32                          ulMnc;
} TAF_SDC_PLMN_ID_STRU;


typedef struct
{
    VOS_UINT16                          usLac;
    VOS_UINT8                           aucReserve1[2];
    TAF_SDC_PLMN_ID_STRU                stPlmnId;
    VOS_UINT8                           ucRac;
    VOS_UINT8                           ucRoamFlag;                     /* ��ǰפ�������Ƿ����� VOS_TRUE:�������� VOS_FALSE:���������� */
    VOS_UINT8                           ucCampOnFlg;                    /* ��ǰ�Ƿ�פ��,�յ�ϵͳ��Ϣ��Ϊפ��,�յ���������ָʾ��Ϊδפ�� */
    /* Modified by l00301449 for CDMA Iteration 15, 2015-5-15, begin */
    VOS_UINT8                           uc3GppRfAvailFlg;
    /* Modified by l00301449 for CDMA Iteration 15, 2015-5-15, end */

    VOS_UINT32                          ulCellId;
    TAF_SDC_LMM_ACCESS_TYPE_ENUM_UINT8  enLmmAccessType;
    VOS_UINT8                           aucReserve2[3];
    VOS_UINT32                          ulLteArfcn;                             /* LTEפ��Ƶ����Ϣ */

} TAF_SDC_3GPP_SYS_INFO_STRU;

/* Added by m00312079 for CDMA 1X Iteration 6 2014-12-27 begin */
/** ****************************************************************************
 * Name        : TAF_SDC_1X_SIG_QUALITY_RPT_INFO_STRU
 * Description :
 *******************************************************************************/
typedef struct
{
    TAF_SDC_CDMACSQ_MODE_ENUM_UINT8     enMode;
    VOS_UINT8                           ucTimeInterval;
    VOS_UINT8                           ucRptThreshold;
    VOS_INT8                            cCdmaRssi;
    VOS_INT8                            cCdmaEcIo;
    VOS_UINT8                           aucReserve[3];
}TAF_SDC_1X_SIG_QUALITY_INFO_STRU;


/* Added by m00312079 for CDMA 1X Iteration 6 2014-12-27 end */

typedef struct
{
    TAF_SDC_CELL_RESTRICTION_TYPE_ENUM_UINT8    enCellAcType;                   /* С���������� */
    VOS_UINT8                                   ucRestrictRegister;             /* �Ƿ�����ע��VOS_TRUE:���ƣ�VOS_FALSE:������ */
    VOS_UINT8                                   ucRestrictPagingRsp;            /* �Ƿ�������ӦѰ��VOS_TRUE:���ƣ�VOS_FALSE:������ */
    VOS_UINT8                                   ucReserved;
}TAF_SDC_ACCESS_RESTRICTION_STRU;
typedef struct
{
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8      enCsServiceStatus;                   /* cs����״̬ */
    TAF_SDC_REG_STATUS_ENUM_UINT8          enCsRegStatus;                       /* csע��״̬ */
    VOS_UINT8                              ucSimCsRegStatus;    /* SIM��CS���ע�������µĿ��Ƿ���ЧVOS_TRUE:CS��Ŀ���Ч,VOS_FALSE:CS��Ŀ���Ч*/

    VOS_UINT8                              ucCsAttachAllowFlg;                  /* cs�Ƿ�����ע���ʶ */

    TAF_SDC_ACCESS_RESTRICTION_STRU        stCsAcRestriction;                   /* ��ǰCS������������ */
}TAF_SDC_CS_DOMAIN_INFO_STRU;


typedef struct
{
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8      enPsServiceStatus;                                                            /* ps����״̬ */
    TAF_SDC_REG_STATUS_ENUM_UINT8          enPsRegStatus;                       /* psע��״̬ */
    VOS_UINT8                              ucSimPsRegStatus;                    /* SIM��PS���ע�������µĿ��Ƿ���ЧVOS_TRUE:CS��Ŀ���Ч,VOS_FALSE:CS��Ŀ���Ч*/
    VOS_UINT8                              ucPsAttachAllowFlg;                  /* ps�Ƿ�����ע���ʶ */
	TAF_SDC_ACCESS_RESTRICTION_STRU        stPsAcRestriction;                   /* ��ǰPS������������ */

}TAF_SDC_PS_DOMAIN_INFO_STRU;
typedef struct
{
    TAF_SDC_IMS_NORMAL_REG_STATUS_ENUM_UINT8   enImsNormalRegSta;
    VOS_UINT8                                  aucReserved[3];
}TAF_SDC_IMS_DOMAIN_INFO_STRU;


/* Added by m00312079 for CDMA 1X Iteration 6 2015-1-14 begin */
/*****************************************************************************
 �ṹ��    : TAF_SDC_SIGNAL_QUALITY_INFO_STRU
 �ṹ˵��  : �ź�������Ϣ
 1.��    ��   : 2015��01��14��
   ��    ��   : m00312079
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    TAF_SDC_1X_SIG_QUALITY_INFO_STRU                    st1xSigQualityRptInfo;
}TAF_SDC_SIG_QUALITY_INFO_STRU;

/* Added by m00312079 for CDMA 1X Iteration 6 2015-1-14 end */

typedef struct
{
    TAF_SDC_USIM_STATUS_ENUM_UINT8      enSimStatus;
    VOS_UINT8                           aucReserved[3];
}TAF_SDC_SIM_STATUS_STRU;


typedef struct
{
    VOS_UINT8                           aucImsi[TAF_SDC_MAX_IMSI_LEN];

	VOS_UINT8                           aucLastImsi[TAF_SDC_MAX_IMSI_LEN];
    VOS_UINT8                           aucReserved[2];
}TAF_SDC_SIM_MS_IDENTITY_STRU;



typedef struct
{
    TAF_SDC_SIM_STATUS_STRU             stUsimStatus;                            /* SIM��״̬ */
    TAF_SDC_SIM_MS_IDENTITY_STRU        stMsIdentity;                           /* MS Identity��Ϣ */
    TAF_SDC_CALL_MODE_ENUM_UINT8        enCallMode;
    TAF_SDC_SIM_TYPE_ENUM_UINT8         enUsimType;                              /* SIM������ */
    VOS_UINT8                           aucRsv[2];
}TAF_SDC_USIM_INFO_STRU;
typedef struct
{
    TAF_SDC_STATUS_RPT_GENERAL_CTRL_TYPE_ENUM_UINT8   enStatusRptGeneralControl; /* �����Ƿ���������˽������������ϱ� */
    VOS_UINT8                                         aucReserved[3];
    VOS_UINT8                                         aucRptCfg[TAF_SDC_RPT_CFG_MAX_SIZE]; /* 64bit�����ϱ���ʶ */
}TAF_SDC_CURC_RPT_CTRL_STRU;


typedef struct
{
    VOS_UINT8                                         aucRptCfg[TAF_SDC_RPT_CFG_MAX_SIZE]; /* 64bit�����ϱ���ʶ */
}TAF_SDC_UNSOLICITED_RPT_CTRL_STRU;
typedef struct
{
    TAF_SDC_CURC_RPT_CTRL_STRU              stCurcRptCtrl;                      /* CURC���������ϱ� */
    TAF_SDC_UNSOLICITED_RPT_CTRL_STRU       stUnsolicitedRptCtrl;               /* ����������������ϱ� */
}TAF_SDC_RPT_CTRL_STRU;



typedef struct
{
    VOS_UINT8                           ucUssdTransMode;
    VOS_UINT8                           ucAlphaTransMode;
    VOS_UINT8                           aucRsv[2];
}TAF_SDC_USSD_CFG_STRU;



typedef struct
{
    VOS_UINT8                                   ucUtranSkipWPlmnSearchFlag;
    VOS_UINT8                                   aucReserved[3];
}TAF_SDC_DSDA_PLMN_SEARCH_ENHANCED_CFG_STRU;


typedef struct
{
    VOS_UINT8                           ucPlmnExactlyCompareFlag;         /* ��ȷ�Ƚ��Ƿ��� */
    VOS_UINT8                           aucRsv[3];
}TAF_SDC_PLMN_EXACTLY_COMPARE_INFO_STRU;

/*****************************************************************************
�ṹ��    : TAF_SDC_NONNORMAL_REG_STATUS_MERGE_CFG_STRU
�ṹ˵��  : �������������Ƿ��ϱ�ע��״̬�ı�������Ϣ
1.��    ��  : 2015��10��28��
  ��    ��  : z00359541
  �޸�����  : �����ɺ���
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucMergeFlg;                      /* �������������Ƿ��ϱ�ע��״̬�ı� */
    VOS_UINT8                           aucReserved[3];              
} TAF_SDC_NONNORMAL_REG_STATUS_MERGE_CFG_STRU;
typedef struct
{
    TAF_SDC_RPT_CTRL_STRU               stRptCtrl;                              /* ���������ϱ���Ϣ */
    TAF_SDC_USSD_CFG_STRU               stUssdCfg;                              /* USSD������Ϣ */
    VOS_UINT16                          usAppCfgSupportType;                    /*����Ӧ�ð汾*/
    TAF_SDC_UE_USAGE_SETTING_ENUM_UINT8 enUeUsageSetting;                       /* UE's usage setting */

    /* Modified by c00318887 for AT&T phaseII, 2015-2-26, begin */
    VOS_UINT8                                ucRefreshAllFileRestartFlag;
    TAF_SDC_PLMN_EXACTLY_COMPARE_INFO_STRU   stPlmnExactlyCompareInfo;                /* ��ȷ�Ƚ�PLMN��� */
    /* Modified by c00318887 for AT&T phaseII, 2015-2-26, end */


    TAF_SDC_RAT_PRIO_STRU               stPrioRatList;                          /* ���뼼���Լ����ȼ� */

    TAF_SDC_DSDA_PLMN_SEARCH_ENHANCED_CFG_STRU  stDsdaPlmnSearchEnhancedCfg;

    TAF_SDC_NONNORMAL_REG_STATUS_MERGE_CFG_STRU stNonnormalRegStatusMergeCfg;

}TAF_SDC_MS_SYS_CFG_INFO_STRU;
typedef struct
{
    TAF_SDC_MS_CAP_INFO_STRU            stMsCapInfo;                            /* MS��������Ϣ */
    TAF_SDC_MS_SYS_CFG_INFO_STRU        stMsSysCfgInfo;                         /* ϵͳ������Ϣ */
}TAF_SDC_MS_CFG_INFO_STRU;


typedef struct
{
    TAF_SDC_NW_IMS_VOICE_CAP_ENUM_UINT8   enNwImsVoCap;
    TAF_SDC_NW_EMC_BS_CAP_ENUM_UINT8      enNwEmcBsCap;
    TAF_SDC_LTE_CS_CAPBILITY_ENUM_UINT8   enLteCsCap;
    VOS_UINT8                             aucReserved[1];
}
TAF_SDC_NETWORK_CAP_INFO_STRU;

/** ****************************************************************************
 * Name        : TAF_SDC_1X_REG_INFO_STRU
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
}TAF_SDC_1X_REG_INFO_STRU;

/** ****************************************************************************
 * Name        : TAF_SDC_1X_SERVICE_INFO_STRU
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
}TAF_SDC_1X_SERVICE_INFO_STRU;

/** ****************************************************************************
 * Name        : TAF_SDC_1X_BASE_STATION_INFO_STRU
 * Description : Base station info of Overhead Message
 *******************************************************************************/
typedef struct
{
    VOS_UINT16                          usBaseId;        /**<  Base station identification */

    VOS_UINT8                           ucBaseClass;     /**<  Base station class */
    VOS_UINT8                           aucReserve[1];
    /* reg & zone */
    VOS_INT32                           lBaseLatitude;   /**<  Base station latitude */
    VOS_INT32                           lBaseLongitude;  /**<  Base station longitude */

}TAF_SDC_1X_BASE_STATION_INFO_STRU;
typedef struct
{
    VOS_UINT16                          usBandClass;
    VOS_UINT16                          usFreq;
    VOS_INT32                           lSid;             /**<  System identification */
    VOS_INT32                           lNid;             /**<  Network identification */
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-14, begin */
    VOS_UINT32                          ulSidEnable;      /* detemined the sid whether need to indicate*/
    VOS_UINT32                          ulIsInEmcCallBack; /* ��ǰ�Ƿ���callbackģʽ*/
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-14, end */
    VOS_UINT8                           ucRoamingInd;
    VOS_UINT8                           ucPrevInUse;
    VOS_UINT8                           ucPacketZoneId;    /**<  Packet Data service zone identifier */

    /* Modified by l00301449 for CDMA Iteration 15, 2015-5-15, begin */
    VOS_UINT8                           uc1xRfAvailFlg;
    /* Modified by l00301449 for CDMA Iteration 15, 2015-5-15, end */

    TAF_SDC_1X_REG_INFO_STRU            stRegInfo;
    TAF_SDC_1X_BASE_STATION_INFO_STRU   stBaseStationInfo;
    TAF_SDC_1X_SERVICE_INFO_STRU        stServiceInfo;
}TAF_SDC_1X_SYS_INFO_STRU;

/* Modified by l00301449 for CDMA Iteration 15, 2015-5-15, begin */
/*****************************************************************************
 �ṹ��    : TAF_SDC_HRPD_SYS_INFO_STRU
 �ṹ˵��  : ��ǰפ����HRPD���������Ϣ
 1.��    ��   : 2015��5��15��
   ��    ��   : l00301449
   �޸�����   : �½�

  2.��    ��   : 2015��7��9��
    ��    ��   : y00322978
    �޸�����   : ���hrpd��Ϣ���ڿ�ά�ɲ�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                   ucHrpdRfAvailFlg;
    VOS_UINT8                                   ucColorCode;
    VOS_UINT16                                  usBandClass;
    VOS_UINT16                                  usFreq;
    VOS_UINT8                                   ucSubNetMask;
    NAS_OM_MMA_HRPD_SESSION_STATUS_ENUM_UINT8   ucSessionStatus;
    VOS_UINT32                                  ulMcc;                   /**<  Mobile country code */
    VOS_UINT32                                  ulSessionSeed;          /*RATI*/
    VOS_UINT8                                   aucCurUATI[NAS_OM_MMA_UATI_OCTET_LENGTH]; /*UATI*/
    VOS_UINT32                                  ulSector24;
}TAF_SDC_HRPD_SYS_INFO_STRU;

/* Modified by l00301449 for CDMA Iteration 15, 2015-5-15, end */



typedef struct
{
    VOS_UINT8                           aucMeId[NAS_OM_MMA_MEID_OCTET_NUM];    /* 56-bit */
    TAF_SDC_SYS_MODE_ENUM_UINT8         enSysMode;
    TAF_SDC_SYS_SUBMODE_ENUM_UINT8      enSysSubMode;
    NAS_OM_1X_CALL_STATE_ENUM_UINT8     en1xCallState;
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulEsn;                              /* 32-bit */
    VOS_UINT32                          ulRptPeriod;                        /*��ά�ɲ��ϱ�����*/
    TAF_SDC_3GPP_SYS_INFO_STRU          st3gppSysInfo;                         /* ��ǰפ��PLMN��Ϣ */
    TAF_SDC_1X_SYS_INFO_STRU            st1xSysInfo;
    /* Modified by l00301449 for CDMA Iteration 15, 2015-5-15, begin */
    TAF_SDC_HRPD_SYS_INFO_STRU          stHrpdSysInfo;
    /* Modified by l00301449 for CDMA Iteration 15, 2015-5-15, end */
}TAF_SDC_SYS_INFO_STRU;


typedef struct
{
    TAF_SDC_PLMN_ID_STRU                stServicePlmnId;     /*��ǰע��ɹ���PLMN ID*/
    TAF_SDC_SYS_MODE_ENUM_UINT8         enServiceSysMode;    /*��ǰע��ɹ��Ľ��뼼��*/
    VOS_UINT8                           ucServiceUtranMode;  /*ģʽ��FDD����TDD*/
    TAF_SDC_SYS_SUBMODE_ENUM_UINT8      enServiceSysSubMode; /*��ǰע��ɹ�����ϵͳģʽ*/
    VOS_UINT8                           ucServiceRac;        /*��ǰע��ɹ���RAC*/
    VOS_UINT16                          usServiceLac;        /*��ǰע��ɹ���LAC*/
    VOS_UINT8                           ucServiceRoamFlg;    /*��ǰ�Ƿ�����*/
    VOS_UINT8                           aucReserve[1];
    VOS_UINT32                          ulServiceCellId;     /*��ǰע��ɹ���cellid*/
}TAF_SDC_SERVICED_PLMN_INFO_STRU;



typedef struct
{
    VOS_INT16                       sRscpValue;  /* С���ź���������3g��^cerssi�ϱ�ʹ��*/
    VOS_INT16                       sEcioValue;  /* С�����������3g��^cerssi�ϱ�ʹ��*/
    /* ������UIION�����ṹ��(TAF_SDC_2G_CELL_SIGN_INFO_STRU,TAF_SDC_4G_CELL_SIGN_INFO_STRU)
         �ֽڶ��룬������������ṹ�巢���ı䣬�˴�����λҲҪ��Ӧ�޸� */
    VOS_UINT8                       aucReserve[16];
} TAF_SDC_3G_CELL_SIGN_INFO_STRU;


typedef struct
{
    VOS_INT16                       sRssiValue;   /* С���ź���������2g��^cerssi�ϱ�ʹ��,2gû��rscp�ĸ����õ���rssi */
    /* ������UIION�����ṹ��(TAF_SDC_3G_CELL_SIGN_INFO_STRU,TAF_SDC_4G_CELL_SIGN_INFO_STRU)
        �ֽڶ��룬������������ṹ�巢���ı䣬�˴�����λҲҪ��Ӧ�޸� */
    VOS_UINT8                       aucReserve1[18];
} TAF_SDC_2G_CELL_SIGN_INFO_STRU;


typedef struct
{
    VOS_UINT16                          usRI;                                   /* RI*/
    VOS_UINT8                           aucRes[2];
    VOS_UINT16                          ausCQI[2];                              /* CQI�������� */

}TAF_SDC_CQI_INFO_STRU;

typedef struct
{
    VOS_INT16                           sRssi;              /* Rssi*/
    VOS_INT16                           sRsd;               /* ����ֶ�*/
    VOS_INT16                           sRsrp;              /* ��Χ��(-141,-44), 99Ϊ��Ч */
    VOS_INT16                           sRsrq;              /* ��Χ��(-40, -6) , 99Ϊ��Ч */
    VOS_INT32                           lSINR;              /* SINR RS_SNR */
    TAF_SDC_CQI_INFO_STRU               stCQI;                                  /*Channle Quality Indicator*/
}TAF_SDC_4G_CELL_SIGN_INFO_STRU;




typedef struct
{
    VOS_UINT8        ucRssiValue;       /*��ת��Ϊ�ȼ���ʾ���ź�ǿ��*/
    VOS_UINT8        ucChannalQual;     /*������,ֻ������ҵ���ʱ�����,����
                                          Ч��99*/
    VOS_UINT16       usCellDlFreq;       /*С��Ƶ��(����)*/
    VOS_UINT16       usCellUlFreq;       /*��ǰƵ��(����)*/
    VOS_INT16        sUeRfPower;         /*���书��,RRMM_UE_RFPOWER_INVALID��Чֵ*/
    VOS_UINT8        aucReserved[3];
    TAF_SDC_SYS_MODE_ENUM_UINT8          enRat;                                 /*rssi�ϱ�ʱ�Ľ��뼼��*/
    /*פ��С�����ź�����*/
    union
    {
        TAF_SDC_2G_CELL_SIGN_INFO_STRU   st2GCellSignInfo;
        TAF_SDC_3G_CELL_SIGN_INFO_STRU   st3GCellSignInfo;
        TAF_SDC_4G_CELL_SIGN_INFO_STRU   st4GCellSignInfo;
    }u;
}TAF_SDC_RSSI_VALUE_STRU;
typedef struct
{
    TAF_SDC_RSSI_VALUE_STRU          stRssiValue;       /* ��ǰ�ṩ����С�����ź����� */
    TAF_SDC_SERVICED_PLMN_INFO_STRU  stServPlmnInfo;    /* ��ǰ�ṩ����С����PLMN��Ϣ */


    /* Add by l00305157 for Service_State_Optimize_PhaseII, 2015-02-11, begin*/
    TAF_SDC_CS_DOMAIN_INFO_STRU         stCsDomainInfo;                         /*��ǰCS����Ϣ*/
    TAF_SDC_PS_DOMAIN_INFO_STRU         stPsDomainInfo;                         /*��ǰPS����Ϣ*/
    TAF_SDC_REPORT_SRVSTA_ENUM_UINT8    enReportSrvsta;                         /* UE�ķ���״̬ ^srvst�ϱ��ķ���״̬*/
    TAF_SDC_SERVICE_DOMAIN_ENUM_UINT8   enServiceDomain;                        /* UE�ķ�����sysinfo ��ѯʱ�ϱ��ķ�����*/
    /* Add by l00305157 for Service_State_Optimize_PhaseII, 2015-02-11, end */
    VOS_UINT8                           aucReserve[2];

}TAF_SDC_APPNETWORK_INFO;




typedef struct
{
    TAF_SDC_SYS_INFO_STRU               stSysInfo;
    TAF_SDC_CS_DOMAIN_INFO_STRU         stCsDomainInfo;                         /* ��ǰCS����Ϣ */
    TAF_SDC_PS_DOMAIN_INFO_STRU         stPsDomainInfo;                         /* ��ǰPS����Ϣ */
    TAF_SDC_REPORT_SRVSTA_ENUM_UINT8    enReportSrvsta;                         /* UE����״̬^srvst�ϱ��ķ���״̬ */
    TAF_SDC_SERVICE_DOMAIN_ENUM_UINT8   enServiceDomain;                        /* UE������sysinfo��ѯʱ�ϱ��ķ����� */
    VOS_UINT8                           aucReserved[2];
    TAF_SDC_NETWORK_CAP_INFO_STRU       stGuNwCapInfo;                          /* GU������ҵ��������Ϣ */
    TAF_SDC_NETWORK_CAP_INFO_STRU       stLteNwCapInfo;                         /* LTE������ҵ��������Ϣ */

    TAF_SDC_IMS_DOMAIN_INFO_STRU        stImsDomainInfo;                        /* IMS���������Ϣ */

    /* Modified by l00305157 for Service_State_Optimize_PhaseI, 2014-11-29, begin */
    TAF_SDC_RSSI_VALUE_STRU             stRssiValue;
    /* Modified by l00305157 for Service_State_Optimize_PhaseI, 2014-11-29, end */

    /* Added by m00312079 for CDMA 1X Iteration 6 2015-1-14 begin */
    TAF_SDC_SIG_QUALITY_INFO_STRU       stSingalQualityInfo;
    /* Added by m00312079 for CDMA 1X Iteration 6 2015-1-14 end */

}TAF_SDC_NETWORK_INFO_STRU;
typedef struct
{
    VOS_UINT8                           ucNumType;
    VOS_UINT8                           ucLength;
    VOS_UINT8                           aucRsv[2];
    VOS_UINT8                           aucCallNumber[TAF_SDC_ECALL_BCD_NUM_MAX_LEN];
}TAF_SDC_ECALL_NUM_STRU;


typedef struct
{
    TAF_SDC_CALL_MODE_ENUM_UINT8        enCallMode;
    VOS_UINT8                           aucRsv[3];
    TAF_SDC_ECALL_NUM_STRU              stEcallNum;                             /* SDN�ļ���ȡ��test number/reconfiguration number */
}TAF_SDC_ECALL_INFO_STRU;
typedef struct
{
    VOS_UINT8                           ucEccNumLen;                            /* ���������볤�� */
    VOS_UINT8                           aucRsv[3];
    VOS_UINT8                           aucEccNum[TAF_SDC_MAX_BCD_NUM_LEN];     /* ���������� */
} TAF_SDC_UCIM_ECC_NUM_STRU;


typedef struct
{
    VOS_UINT8                           ucEccNumCount;                                  /* �����Ÿ��� */
    VOS_UINT8                           aucReseve[3];
    TAF_SDC_UCIM_ECC_NUM_STRU           astUcimEccNumList[TAF_SDC_MAX_UCIM_ECC_NUM];/* �������б� */
} TAF_SDC_UCIM_ECC_NUM_LIST_STRU;



typedef struct
{
    VOS_UINT8                           ucCsCallExistFlg;                       /* ��ǰ�Ƿ��ں��й�����:VOS_TRUE  ��ǰ���ں��й�����
                                                                                                  VOS_FALSE ��ǰ�����ں��й�����  */
    VOS_UINT8                           ucImsCallExistFlg;                      /* ��ǰ�Ƿ��ں��й�����:VOS_TRUE  ��ǰ���ں��й�����
                                                                                                  VOS_FALSE ��ǰ�����ں��й�����  */
    /* ɾ��SRVCC��־���Ƶ�CALLģ�� */
    VOS_UINT8                           ucIsXsmsCallExistFlg;                   /* ��ǰ�Ƿ��ں��й�����:VOS_TRUE  ��ǰ���ں��й�����*/

    VOS_UINT8                           ucCsEccExistFlg;                        /* ��ǰ�Ƿ��ڽ������й�����:VOS_TRUE  ��ǰ���ڽ������й�����*/

    TAF_SDC_MM_EMERGENCY_LIST_STRU      stMmCallEmerNumList;                    /* MM�������Ľ������б� */
    TAF_SDC_CUSTOM_ECC_CTX_STRU         stCustomCallEccNumCtx;                  /* ��Ӫ�̶��ƵĽ������б� */


    TAF_SDC_ECALL_NUM_STRU              stEcallTestNumber;                      /* SDN�ļ���ȡ��test number */
    TAF_SDC_ECALL_NUM_STRU              stEcallRecfgNumber;                     /* SDN�ļ���ȡ��reconfiguration number */

    TAF_SDC_UCIM_ECC_NUM_LIST_STRU      st1xCallUcimEccNumList;                     /* 1X����UIM��CSIM���еĽ������к����б� */

}TAF_SDC_CALL_INFO_STRU;


typedef struct
{
    VOS_UINT8                           ucCsSmsSrvExistFlg;                     /* CS��Ķ���ҵ����ڱ�ʶ:VOS_TRUE  ��ǰ��CS��Ķ���ҵ��
                                                                                   VOS_FALSE ��ǰû��CS��Ķ���ҵ��  */
    VOS_UINT8                           ucPsSmsSrvExistFlg;                     /* PS��Ķ���ҵ����ڱ�ʶ:VOS_TRUE  ��ǰ��PS��Ķ���ҵ��
                                                                                   VOS_FALSE ��ǰû��PS��Ķ���ҵ��  */
    VOS_UINT8                           ucImsSmsSrvExistFlg;                    /* IMS��Ķ���ҵ����ڱ�ʶ:VOS_TRUE  ��ǰ��IMS��Ķ���ҵ��
                                                                                   VOS_FALSE ��ǰû��IMS��Ķ���ҵ��  */
    VOS_UINT8                           aucReserved[1];
}TAF_SDC_SMS_INFO_STRU;


typedef struct
{
    VOS_UINT8                           ucCsSsSrvExistFlg;                      /* CS��Ĳ���ҵ����ڱ�ʶ:VOS_TRUE  ��ǰ��CS��Ĳ���ҵ��
                                                                                   VOS_FALSE ��ǰû��CS��Ĳ���ҵ��  */
    VOS_UINT8                           ucImsSsSrvExistFlg;                     /* IMS��Ĳ���ҵ����ڱ�ʶ:VOS_TRUE  ��ǰ��IMS��Ĳ���ҵ��
                                                                                   VOS_FALSE ��ǰû��IMS��Ĳ���ҵ��  */
    VOS_UINT8                           aucReserved[2];
}TAF_SDC_SS_INFO_STRU;



typedef struct
{
    VOS_UINT8                           ucCsServiceConnStatusFlag;              /* csҵ�����������Ƿ���ڱ�ʶ */
    VOS_UINT8                           ucReserved[3];                                                                                             VOS_UINT8                           aucReserved[2];
}TAF_SDC_CS_INFO_STRU;
typedef struct
{
    VOS_UINT8                           ucPsServiceConnStatusFlag;              /* psҵ�����������Ƿ���ڱ�ʶ */
    VOS_UINT8                           aucReserved[3];
}TAF_SDC_PS_INFO_STRU;

#if (FEATURE_ON == FEATURE_LTE)
typedef struct
{
    VOS_UINT8                           ucEpsServiceConnStatusFlag;              /* epsҵ�����������Ƿ���ڱ�ʶ */
    VOS_UINT8                           aucReserved[3];
}TAF_SDC_EPS_INFO_STRU;
#endif
typedef struct
{
    VOS_UINT16                           usCsMoNormalCall   :1;
    VOS_UINT16                           usCsMoEmgCall      :1;
    VOS_UINT16                           usCsMoSs           :1;
    VOS_UINT16                           usCsMoSms          :1;
    VOS_UINT16                           usPsConversatCall  :1;
    VOS_UINT16                           usPsStreamCall     :1;
    VOS_UINT16                           usPsInteractCall   :1;
    VOS_UINT16                           usPsBackGroundCall :1;
    VOS_UINT16                           usPsSubscribTrafficCall :1;
    VOS_UINT16                           usReserved7         :7;
}TAF_SDC_TRIG_PLMN_SEARCH_SRV_TYPE_STRU;


typedef union
{
    VOS_UINT16                                usTrigPlmnSearchSrvType;

    TAF_SDC_TRIG_PLMN_SEARCH_SRV_TYPE_STRU    stTrigPlmnSearchSrvType;
}TAF_SDC_TRIG_PLMN_SEARCH_SRV_TYPE_UNION;


typedef struct
{
    TAF_SDC_CALL_INFO_STRU              stCallInfo;                               /* CC�����Ϣ */
    TAF_SDC_SMS_INFO_STRU               stSmsInfo;                              /* SMS�����Ϣ */
    TAF_SDC_SS_INFO_STRU                stSsInfo;                               /* SS�����Ϣ */

    TAF_SDC_CS_INFO_STRU                stCsInfo;                                                                                      VOS_UINT8                           aucReserved[2];

    TAF_SDC_PS_INFO_STRU                stPsInfo;
#if (FEATURE_ON == FEATURE_LTE)
    TAF_SDC_EPS_INFO_STRU               stEpsInfo;
#endif
    TAF_SDC_TRIG_PLMN_SEARCH_SRV_TYPE_UNION stTrigPlmnSrcSrvType;
    VOS_UINT8                               aucReserved1[2];

}TAF_SDC_SERVICE_INFO_STRU;
typedef struct
{
    VOS_UINT8                           bitOpActiveRptFlag    :1;
    VOS_UINT8                           bitOpRatSwitchRptFlag :1;
    VOS_UINT8                           bitOpSpare            :6;
}TAF_SDC_ERRLOG_REPORT_CTRL_OCTET_STRU;


typedef struct
{
    VOS_UINT8                                               ucErrLogCtrlFlag;                       /* ERRLOG�򿪱�ʶ */
    TAF_SDC_ERRLOG_REPORT_CTRL_OCTET_STRU                   stErrLogRptCtrl;
    VOS_UINT16                                              usAlmLevel;                             /* ���ϸ澯���� */
}TAF_SDC_ERRLOG_CTRL_INFO_STRU;


typedef struct
{
    OM_RING_ID                          pstRingBuffer;                          /* MM��Ĺ����� */
    VOS_UINT32                          ulOverflowCnt;                          /* Ringbuf����Ĵ��� */
}TAF_SDC_ERRLOG_BUFF_INFO_STRU;

/* Added by zwx247453 for CHR optimize, 2015-3-13 Begin */
/*****************************************************************************
 �ṹ��    : TAF_SDC_ERRLOG_RAT_FREQUENTLY_SWITCH_INFO_STRU
 �ṹ˵��  : RATƵ���л�����Ϣ�ṹ
 1.��    ��   : 2015��03��13��
   ��    ��   : zwx247453
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulNvStatisticTime;                      /* NV���õ�ͳ��ʱ�� */
    VOS_UINT32                          ulNvSwitchNum;                          /* NV���õ�gutlƵ���л��Ĵ��� */
    VOS_UINT8                           ucOldRatType;                           /* ������Ԫ�ص�ģʽ���� */
    VOS_UINT8                           aucReserved[3];
    OM_RING_ID                          pstRingBuffer;                          /* ��¼Ƶ���л���¼��ѭ������ */
}TAF_SDC_ERRLOG_RAT_FREQUENTLY_SWITCH_INFO_STRU;
/* Added by zwx247453 for CHR optimize, 2015-3-13 End */

typedef struct
{
    VOS_UINT8                           ucCsOosReportToAppFlag;                 /* CS���Ƿ����ϱ���APP�޷��� */
    VOS_UINT8                           ucPsOosReportToAppFlag;                 /* PS���Ƿ����ϱ���APP�޷��� */
    VOS_UINT8                           ucReportPowerOnBeginFlag;               /* �Ƿ����ϱ���������CHR */
    VOS_UINT8                           ucReportPowerOffBeginFlag;              /* �Ƿ����ϱ����ػ���CHR */
}TAF_SDC_ERRLOG_OOS_INFO_STRU;


typedef struct
{
    TAF_SDC_ERRLOG_CTRL_INFO_STRU                       stCtrlInfo;
    TAF_SDC_ERRLOG_BUFF_INFO_STRU                       stBuffInfo;
    /* Added by zwx247453 for CHR optimize, 2015-3-13 Begin */
    TAF_SDC_ERRLOG_RAT_FREQUENTLY_SWITCH_INFO_STRU      stRatFrequentlySwitchInfo;
    /* Added by zwx247453 for CHR optimize, 2015-3-13 End */

    TAF_SDC_ERRLOG_OOS_INFO_STRU                        stOosInfo;

}TAF_SDC_ERRLOG_INFO_STRU;


typedef struct
{
    TAF_SDC_PHONE_MODE_ENUM_UINT8       enPhMode;

    TAF_SDC_IMS_SWITCH_STATE_ENUM_UINT8 enImsSwitchState;

    VOS_UINT8                           aucRsv[2];
}TAF_SDC_PHONE_INFO_STRU;


typedef struct
{
    TAF_SDC_CREG_TYPE_ENUM_UINT8        enCregType;
    TAF_SDC_CGREG_TYPE_ENUM_UINT8       enCgregType;
    TAF_SDC_CEREG_TYPE_ENUM_UINT8       enCeregType;
    VOS_UINT8                           aucRsv;
}TAF_SDC_REG_REPORT_STATUS_STRU;

/* Added by h00313353 for iteration 9, 2015-2-7, begin */
/*****************************************************************************
 �ṹ��    : TAF_SDC_CSIM_INFO_STRU
 �ṹ˵��  : ��¼CSIM����Ϣ
 1.��    ��   : 2015��2��7��
   ��    ��   : h00313353
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    TAF_SDC_SIM_STATUS_STRU             stCsimStatus;                           /* ��״̬ */
    TAF_SDC_SIM_MS_IDENTITY_STRU        stMsIdentity;                           /* MS Identity��Ϣ */
    TAF_SDC_SIM_TYPE_ENUM_UINT8         enCsimType;                              /* ������ */
    VOS_UINT8                           aucRsv[3];
}TAF_SDC_CSIM_INFO_STRU;

/*****************************************************************************
 �ṹ��    : TAF_SDC_ICCID_INFO_STRU
 �ṹ˵��  : ��¼��ICCID��Ϣ
 1.��    ��   : 2015��8��26��
   ��    ��   : h00313353
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucLen;
    VOS_UINT8                           aucIccId[TAF_SDC_ICC_ID_MAX_NUM + 1];
} TAF_SDC_ICCID_INFO_STRU;

/*****************************************************************************
 �ṹ��    : TAF_SDC_CARD_INFO_STRU
 �ṹ˵��  : ��¼����Ϣ
 1.��    ��   : 2015��2��7��
   ��    ��   : h00313353
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    TAF_SDC_USIM_INFO_STRU              stUsimInfo;
    TAF_SDC_CSIM_INFO_STRU              stCsimInfo;
    TAF_SDC_ICCID_INFO_STRU             stIccIdInfo;
}TAF_SDC_CARD_INFO_STRU;
/* Added by h00313353 for iteration 9, 2015-2-7, end */

typedef struct
{
    VOS_UINT8                           bitExt    : 1;
    VOS_UINT8                           bitCoding : 3;    /* �����ʽ */
    VOS_UINT8                           bitAddCi  : 1;
    VOS_UINT8                           bitSpare  : 3;    /* spare bit */
    VOS_UINT8                           ucLength;         /* ��Ӫ�����Ƴ��� */
    VOS_UINT8                           aucReserved[2];
    VOS_UINT8                           aucOperatorName[TAF_SDC_MAX_OPER_NAME_NUM];/* ��Ӫ�̵����� */
}TAF_SDC_OPERATOR_NAME_STRU;


typedef struct
{
    TAF_SDC_PLMN_ID_STRU                stPlmnId;
    VOS_UINT16                          usLacRangeLow;
    VOS_UINT16                          usLacRangeHigh;
    VOS_UINT16                          usPnnIndex;
}TAF_SDC_OPL_RECORD_INFO_STRU;


typedef struct
{
    VOS_UINT32                          ulOplRecordNum;
    VOS_UINT32                          ulOplEfLen;
    TAF_SDC_OPL_RECORD_INFO_STRU        astOplRecordInfo[TAF_SDC_OPL_MAX_RECORD_NUM];
}TAF_SDC_OPL_FILE_INFO_STRU;


typedef struct
{
    TAF_SDC_OPERATOR_NAME_STRU          stOperatorNameShort;/* ��Ӫ�̵Ķ����� */
    TAF_SDC_OPERATOR_NAME_STRU          stOperatorNameLong;  /* ��Ӫ�̵ĳ����� */
    VOS_UINT8                           aucPlmnAdditionalInfo[TAF_SDC_MAX_PLMN_ADDITIONAL_INFO_LEN];                                                        /*PLMN Additional Information (coded using one of the UCS2 code options as defined in TS 31.101 [11]).*/
    VOS_UINT8                           ucPlmnAdditionalInfoLen;       /*PLMN Additional Information ���� */
    VOS_UINT8                           aucReserve[1];
}TAF_SDC_PNN_RECORD_INFO_STRU;



typedef struct
{
    VOS_UINT32                          ulPnnRecordNum;
    VOS_UINT32                          ulPnnEfLen;
    TAF_SDC_PNN_RECORD_INFO_STRU        astPnnRecordInfo[TAF_SDC_PNN_MAX_RECORD_NUM];
}TAF_SDC_PNN_FILE_INFO_STRU;


typedef struct
{
    TAF_SDC_OPERATOR_NAME_STRU          stCPHSOperName;
}TAF_SDC_CPHS_FILE_INFO_STRU;


typedef struct
{
    VOS_UINT8                         ucDispRplmnMode;
    VOS_UINT8                         aucReserve[3];
    TAF_SDC_OPERATOR_NAME_STRU        stSpnOperName;
}TAF_SDC_SPN_FILE_INFO_STRU;


typedef struct
{
    VOS_UINT8                           ucServiceProviderPlmnNum;
    VOS_UINT8                           aucReserve[3];
    TAF_SDC_PLMN_ID_STRU                astSeriveProviderPlmn[TAF_SDC_MAX_SERVICE_PROVIDER_PLMN_NUM];
}TAF_SDC_SPDI_FILE_INFO_STRU;


typedef struct
{
    TAF_SDC_PLMN_ID_STRU                stOperatorPlmnId;
    TAF_SDC_OPERATOR_NAME_STRU          stOperatorNameShort;         /* ��ǰפ��������Ӫ�̵Ķ����� */
    TAF_SDC_OPERATOR_NAME_STRU          stOperatorNameLong;          /* ��ǰפ��������Ӫ�̵ĳ����� */
}TAF_SDC_MM_INFO_STRU;


typedef struct
{
    TAF_SDC_PLMN_ID_STRU                stOperatorPlmnId;
    TAF_SDC_OPERATOR_NAME_STRU          stOperatorNameShort;         /* ��ǰפ��������Ӫ�̵Ķ����� */
    TAF_SDC_OPERATOR_NAME_STRU          stOperatorNameLong;          /* ��ǰפ��������Ӫ�̵ĳ����� */
}TAF_SDC_CUSTOM_OPER_NAME_STRU;



typedef struct
{
    TAF_SDC_CUSTOM_OPER_NAME_STRU   astCustomOperName[TAF_NVIM_STORED_OPER_NAME_NUM];
}TAF_SDC_CUSTOM_OPER_NAME_INFO_STRU;




typedef struct
{
    VOS_UINT8                                   ucOperNamePrioNum;
    VOS_UINT8                                   aucReserved[3];
    TAF_SDC_OPER_NAME_TYPE_ENUM_UINT8           aucOperNameTypePrio[TAF_SDC_MAX_OPER_NAME_PRIO_NUM];
}TAF_SDC_OPER_NAME_TYPE_PRIO_STRU;


typedef struct
{
    TAF_SDC_OPER_NAME_TYPE_PRIO_STRU     stOperNameTypePrio;   /* cops��^eonsucs2��ѯ��PNN��SPN��CPHS��NITZ��ȡ�Ⱥ�˳�����ȼ�*/
    TAF_SDC_OPL_FILE_INFO_STRU           stUsimOplFileInfo;    /* Usim�е�OPL�ļ�0x6FC6��Ϣ */
    TAF_SDC_OPL_FILE_INFO_STRU           stSimOplFileInfo;     /* Sim�е�OPL�ļ�0x6FC6��Ϣ */
    TAF_SDC_PNN_FILE_INFO_STRU           stUsimPnnFileInfo;    /* Usim�е�PNN�ļ�0x6FC5��Ϣ */
    TAF_SDC_PNN_FILE_INFO_STRU           stSimPnnFileInfo;     /* Sim�е�PNN�ļ�0x6FC5��Ϣ */
    TAF_SDC_CPHS_FILE_INFO_STRU          stCphsFileInfo;       /* CPHS�ļ�0x6F14��Ϣ */
    TAF_SDC_SPN_FILE_INFO_STRU           stUsimSpnFileInfo;    /* Usim�е�SPN�ļ�0x6f46��Ϣ */
    TAF_SDC_SPN_FILE_INFO_STRU           stSimSpnFileInfo;     /* Sim�е�SPN�ļ�0x6f46��Ϣ */
    TAF_SDC_SPDI_FILE_INFO_STRU          stUsimSpdiFileInfo;   /* USIM��SPDI�ļ�0x6FCD��Ϣ*/
    TAF_SDC_SPDI_FILE_INFO_STRU          stSimSpdiFileInfo;    /* SIM��SPDI�ļ�0x6FCD��Ϣ*/
    TAF_SDC_MM_INFO_STRU                 stMmInfo;             /* ��¼MM/GMM/EMM info��Ϣ�е���Ϣ*/
    TAF_SDC_CUSTOM_OPER_NAME_INFO_STRU   stCustomOperNameInfo; /* 50024 nv�����õ���Ӫ�̶������� */
    TAF_SDC_COPS_FORMAT_TYPE_ENUM_UINT8  enCopsFormatType;
    VOS_CHAR                             cWildCard;             /* ͨ���,ȡֵa-f,�ɴ���0-9�������� */
    VOS_UINT8                            aucReserved[2];
}TAF_SDC_ENHANCED_OPERATOR_NAME_INFO_STRU;
typedef struct
{
    /* Modified by h00313353 for iteration 9, 2015-2-7, begin */
    TAF_SDC_CARD_INFO_STRU              stSimInfo;                              /* �������Ϣ */
    /* Modified by h00313353 for iteration 9, 2015-2-7, end */
    TAF_SDC_MS_CFG_INFO_STRU            stMsCfgInfo;                            /* MS��������Ϣ */
    TAF_SDC_NETWORK_INFO_STRU           stNetworkInfo;                          /* ��ǰפ����������Ϣ */
    TAF_SDC_SERVICE_INFO_STRU           stServiceInfo;                          /* ��ǰҵ�������Ϣ */

    TAF_SDC_PHONE_INFO_STRU             stPhoneInfo;

    TAF_SDC_ERRLOG_INFO_STRU            stErrlogInfo;

    TAF_SDC_REG_REPORT_STATUS_STRU      stRegReportStatus;

    TAF_SDC_APPNETWORK_INFO             stAppNetworkInfo;                       /* �ϱ���APP�õ�������Ϣ����ʵʱ���� */

    TAF_SDC_ENHANCED_OPERATOR_NAME_INFO_STRU stEnhancedOperatorNameInfo;

    TAF_SDC_1X_UE_MAIN_STATUS_ENUM_UINT8     enCasState;
    VOS_UINT8                                aucRsv[3];

}TAF_SDC_CTX_STRU;
typedef struct
{
    VOS_UINT8                           ucSignThreshold;                        /* �źű仯����,��RSSI�仯������ֵ���������Ҫ�����ϱ��ź�������ȡֵ0��ʾ����㰴Ĭ��ֵ���� */
    VOS_UINT8                           ucMinRptTimerInterval;                  /* ����ϱ���ʱ��   */
} TAF_SDC_CELL_SIGN_REPORT_CFG_STRU;

/* call state NVɾ����call state���ϱ���curcͳһ���� */




/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
TAF_SDC_CTX_STRU*  TAF_SDC_GetSdcCtx( VOS_VOID );

TAF_SDC_MS_CAP_INFO_STRU*  TAF_SDC_GetMsCapInfo( VOS_VOID );

TAF_SDC_PLATFORM_RAT_CAP_STRU*  TAF_SDC_GetPlatformRatCap( VOS_VOID );

TAF_SDC_CURC_RPT_CTRL_STRU*  TAF_SDC_GetCurcRptCtrl( VOS_VOID );
TAF_SDC_UNSOLICITED_RPT_CTRL_STRU*  TAF_SDC_GetUnsolicitedRptCtrl( VOS_VOID );


TAF_SDC_NETWORK_CAP_INFO_STRU *TAF_SDC_GetGuNwCapInfo(VOS_VOID);


TAF_SDC_NETWORK_CAP_INFO_STRU *TAF_SDC_GetLteNwCapInfo(VOS_VOID);


VOS_VOID TAF_SDC_SetGuNwCapInfo(TAF_SDC_NETWORK_CAP_INFO_STRU *pstNwCapInfo);


VOS_VOID TAF_SDC_SetLteNwCapInfo(TAF_SDC_NETWORK_CAP_INFO_STRU *pstNwCapInfo);

/* Deleted by h00313353 for CDMA Iteration 15, 2015-5-30, begin */

/* Deleted by h00313353 for CDMA Iteration 15, 2015-5-30, end */
VOS_VOID TAF_SDC_InitMsCapInfo(
    TAF_SDC_INIT_CTX_TYPE_ENUM_UINT8     enInitType,
    TAF_SDC_MS_CAP_INFO_STRU            *pstMsCapInfo
);

VOS_VOID TAF_SDC_InitCtx(
    TAF_SDC_INIT_CTX_TYPE_ENUM_UINT8     enInitType,
    TAF_SDC_CTX_STRU                    *pstSdcCtx
);

TAF_SDC_SYS_MODE_ENUM_UINT8 TAF_SDC_GetSysMode( VOS_VOID );
VOS_VOID TAF_SDC_SetSysMode(TAF_SDC_SYS_MODE_ENUM_UINT8 enSysMode);
TAF_SDC_SYS_SUBMODE_ENUM_UINT8 TAF_SDC_GetSysSubMode( VOS_VOID );
VOS_VOID TAF_SDC_SetSysSubMode(TAF_SDC_SYS_SUBMODE_ENUM_UINT8 enSysSubMode);
TAF_SDC_3GPP_SYS_INFO_STRU* TAF_SDC_Get3gppSysInfo( VOS_VOID );
TAF_SDC_SYS_INFO_STRU* TAF_SDC_GetSysInfo( VOS_VOID );
TAF_SDC_SERVICE_STATUS_ENUM_UINT8 TAF_SDC_GetCsServiceStatus( VOS_VOID );
VOS_VOID TAF_SDC_SetCsServiceStatus(TAF_SDC_SERVICE_STATUS_ENUM_UINT8 enCsServiceStatus);
TAF_SDC_SERVICE_STATUS_ENUM_UINT8 TAF_SDC_GetPsServiceStatus( VOS_VOID );
VOS_VOID TAF_SDC_SetPsServiceStatus(TAF_SDC_SERVICE_STATUS_ENUM_UINT8 enPsServiceStatus);
TAF_SDC_SERVICE_DOMAIN_ENUM_UINT8 TAF_SDC_GetServiceDomain( VOS_VOID );
VOS_VOID TAF_SDC_SetServiceDomain(TAF_SDC_SERVICE_DOMAIN_ENUM_UINT8 enServiceDomain);
TAF_SDC_REG_STATUS_ENUM_UINT8 TAF_SDC_GetCsRegStatus( VOS_VOID );
VOS_VOID TAF_SDC_SetCsRegStatus(TAF_SDC_REG_STATUS_ENUM_UINT8 enCsRegStatus);
TAF_SDC_REG_STATUS_ENUM_UINT8 TAF_SDC_GetPsRegStatus( VOS_VOID );
VOS_VOID TAF_SDC_SetPsRegStatus(TAF_SDC_REG_STATUS_ENUM_UINT8 enPsRegStatus);
/* Add by l00305157 for Service_State_Optimize_PhaseII, 2015-02-11, begin */
TAF_SDC_REG_STATUS_ENUM_UINT8 TAF_SDC_GetAppCsRegStatus( VOS_VOID );
VOS_VOID TAF_SDC_SetAppCsRegStatus(TAF_SDC_REG_STATUS_ENUM_UINT8 enCsRegStatus);
TAF_SDC_REG_STATUS_ENUM_UINT8 TAF_SDC_GetAppPsRegStatus( VOS_VOID );
VOS_VOID TAF_SDC_SetAppPsRegStatus(TAF_SDC_REG_STATUS_ENUM_UINT8 enPsRegStatus);
/* Add by l00305157 for Service_State_Optimize_PhaseII, 2015-02-11, end */
VOS_UINT8* TAF_SDC_GetSimImsi( VOS_VOID );
VOS_VOID TAF_SDC_SetSimImsi( VOS_UINT8 *pstImsi );

VOS_UINT8* TAF_SDC_GetLastSimImsi( VOS_VOID );
VOS_VOID TAF_SDC_SetLastSimImsi( VOS_UINT8 *pstImsi );

TAF_SDC_USIM_STATUS_ENUM_UINT8 TAF_SDC_GetSimStatus( VOS_VOID );

/* Deleted by h00313353 for iteration 9, 2015-2-7, begin */

/* Deleted by h00313353 for iteration 9, 2015-2-7, end */
TAF_SDC_SIM_TYPE_ENUM_UINT8 TAF_SDC_GetSimType( VOS_VOID );
VOS_VOID TAF_SDC_SetCurrCampPlmnId(TAF_SDC_PLMN_ID_STRU *pstPlmnId);
TAF_SDC_PLMN_ID_STRU *TAF_SDC_GetCurrCampPlmnId(VOS_VOID);


VOS_UINT16 TAF_SDC_GetCurrCampLac(VOS_VOID);

VOS_UINT8 TAF_SDC_GetCurrCampRac(VOS_VOID);
VOS_UINT32 TAF_SDC_GetCurrCampCellId(VOS_VOID);

TAF_SDC_REPORT_SRVSTA_ENUM_UINT8 TAF_SDC_GetServiceStatus(VOS_VOID);

VOS_VOID TAF_SDC_SetServiceStatus(TAF_SDC_REPORT_SRVSTA_ENUM_UINT8 enReportSrvsta);


/* Add by l00305157 for Service_State_Optimize_PhaseII, 2015-02-11, begin */
VOS_VOID TAF_SDC_SetAppServiceDomain(TAF_SDC_SERVICE_DOMAIN_ENUM_UINT8 enServiceDomain);
TAF_SDC_SERVICE_DOMAIN_ENUM_UINT8 TAF_SDC_GetAppServiceDomain( VOS_VOID );
VOS_VOID TAF_SDC_SetAppServiceStatus(TAF_SDC_REPORT_SRVSTA_ENUM_UINT8 enReportSrvsta);
TAF_SDC_REPORT_SRVSTA_ENUM_UINT8 TAF_SDC_GetAppServiceStatus(VOS_VOID);
/* Add by l00305157 for Service_State_Optimize_PhaseII, 2015-02-11, end */
VOS_VOID TAF_SDC_SetCurrCampLac(VOS_UINT16 usLac);
VOS_VOID TAF_SDC_SetCurrCampRac(VOS_UINT8 ucRac);
VOS_VOID TAF_SDC_SetCurrCampCellId(VOS_UINT32 ulCellId);
VOS_VOID TAF_SDC_SetCsAcRestriction(TAF_SDC_ACCESS_RESTRICTION_STRU *pstCsAcRetriction);
VOS_VOID TAF_SDC_SetPsAcRestriction(TAF_SDC_ACCESS_RESTRICTION_STRU *pstPsAcRetriction);
TAF_SDC_ACCESS_RESTRICTION_STRU *TAF_SDC_GetCsAcRestriction(VOS_VOID);

TAF_SDC_ACCESS_RESTRICTION_STRU *TAF_SDC_GetPsAcRestriction(VOS_VOID);


TAF_SDC_LMM_ACCESS_TYPE_ENUM_UINT8 TAF_SDC_GetCurrLmmAccessType(VOS_VOID);
VOS_VOID TAF_SDC_SetCurrLmmAccessType(TAF_SDC_LMM_ACCESS_TYPE_ENUM_UINT8 enAccessType);


VOS_VOID TAF_SDC_InitCurcRptCtrlInfo(VOS_VOID);
VOS_VOID TAF_SDC_InitUnsolicitedRptCtrlInfo(VOS_VOID);
VOS_VOID TAF_SDC_ReadCellSignReportCfgNV( VOS_VOID );

VOS_UINT8   TAF_SDC_GetCsCallExistFlg(VOS_VOID);
VOS_VOID    TAF_SDC_SetCsCallExistFlg(
    VOS_UINT8                           ucInCall
);
VOS_VOID    TAF_SDC_SetImsCallExistFlg(
    VOS_UINT8                           ucImsCallExistFlg
);
VOS_UINT8   TAF_SDC_GetImsCallExistFlg(VOS_VOID);

VOS_VOID    TAF_SDC_SetCsEccExistFlg(
    VOS_UINT8                           ucCsEccExistFlg
);
VOS_UINT8 TAF_SDC_GetCsEccExistFlg(VOS_VOID);

/* ɾ��SRVCC��־���Ƶ�CALLģ�� */

TAF_SDC_CALL_INFO_STRU* TAF_SDC_GetCallInfo(VOS_VOID);
VOS_VOID TAF_SDC_SetMmCallEmerNumList(
    TAF_SDC_MM_EMERGENCY_LIST_STRU     *pstMmCallEmerNumList
);
TAF_SDC_MM_EMERGENCY_LIST_STRU* TAF_SDC_GetMmCallEmerNumList(VOS_VOID);
VOS_VOID TAF_SDC_SetCustomCallEccNumCtx(
    TAF_SDC_CUSTOM_ECC_CTX_STRU        *pstCustomCallEccNumCtx
);
TAF_SDC_CUSTOM_ECC_CTX_STRU* TAF_SDC_GetCustomCallEccNumCtx(VOS_VOID);
VOS_CHAR** TAF_SDC_GetCallEmerNumsNoUsimTblAddr(VOS_VOID);
VOS_CHAR** TAF_SDC_GetCallEmerNumsWithUsimTblAddr(VOS_VOID);



VOS_VOID   TAF_SDC_SetUssdTransMode(
    VOS_UINT8                           ucTransMode
);
VOS_UINT8   TAF_SDC_GetUssdTransMode(VOS_VOID);

VOS_VOID TAF_SDC_InitUssdCfgInfo(VOS_VOID);

VOS_VOID TAF_SDC_ReadUssdTransModeNvim(VOS_VOID);
VOS_VOID TAF_SDC_ReadUssdTransTableNvim(VOS_VOID);

VOS_VOID TAF_SDC_InitServiceInfo(
    TAF_SDC_SERVICE_INFO_STRU          *pstServiceInfo
);

VOS_UINT8 TAF_SDC_GetCsServiceConnStatusFlag(VOS_VOID);
VOS_VOID TAF_SDC_SetCsServiceConnStatusFlag(
    VOS_UINT8                           ucCsServiceConnStatusFlag
);


TAF_SDC_TRIG_PLMN_SEARCH_SRV_TYPE_UNION *TAF_SDC_GetTrigPlmnSearchSrvType(VOS_VOID);


VOS_VOID TAF_SDC_InitCallInfo(
    TAF_SDC_CALL_INFO_STRU             *pstCallInfo
);
VOS_VOID TAF_SDC_ReadCustomEccNumListNvim(VOS_VOID);


VOS_VOID TAF_SDC_InitAppCfgSupportType(VOS_VOID);

VOS_VOID TAF_SDC_InitGuNwCapInfo(
    TAF_SDC_NETWORK_CAP_INFO_STRU *pstGuNwCapInfo
);
VOS_VOID TAF_SDC_InitLteNwCapInfo(
    TAF_SDC_NETWORK_CAP_INFO_STRU *pstLteNwCapInfo
);
VOS_VOID TAF_SDC_InitNetWorkInfo(
    TAF_SDC_NETWORK_INFO_STRU *pstNetworkInfo
);


VOS_VOID TAF_SDC_InitCsInfo(TAF_SDC_CS_INFO_STRU *pstCsInfo);
VOS_VOID TAF_SDC_InitPsInfo(TAF_SDC_PS_INFO_STRU *pstPsInfo);
#if (FEATURE_ON == FEATURE_LTE)
VOS_VOID TAF_SDC_InitEpsInfo(TAF_SDC_EPS_INFO_STRU *pstEpsInfo);
#endif


VOS_VOID TAF_SDC_InitUeUsageSetting(VOS_VOID);

VOS_UINT8   TAF_SDC_Get7BitToAssicTableType(VOS_VOID);
VOS_VOID    TAF_SDC_Set7BitToAssicTableType(
    VOS_UINT8                           ucType
);

VOS_UINT8*   TAF_SDC_GetCurr7BitToAsciiTableAddr(VOS_VOID);

/* Added by l00301449 for CDMA STK, 2015-07-03, begin */
VOS_VOID TAF_SDC_Get3GppCurrentLai(
    VOS_UINT8                          *aucLai,
    VOS_UINT32                         *pulLaiLen
);

VOS_VOID TAF_SDC_GetCurrentLai(
    VOS_UINT8                          *aucLai,
    VOS_UINT32                         *pulLaiLen
);
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_VOID TAF_SDC_Get3Gpp2CurrentLai(
    VOS_UINT8                          *aucLai,
    VOS_UINT32                         *pulLaiLen
);
#endif

/* Added by l00301449 for CDMA STK, 2015-07-03, end */


VOS_VOID    TAF_SDC_SetSvlteSupportFlag(
    VOS_UINT8                           ucSvlteSupportFlag
);
VOS_UINT8   TAF_SDC_GetSvlteSupportFlag(VOS_VOID);
VOS_VOID    TAF_SDC_SetCsSmsSrvExistFlg(
    VOS_UINT8                           ucCsSmsSrvExistFlg
);
VOS_UINT8   TAF_SDC_GetCsSmsSrvExistFlg(VOS_VOID);
VOS_VOID TAF_SDC_SetPsSmsSrvExistFlg(
    VOS_UINT8                           ucPsSmsSrvExistFlg
);
VOS_UINT8 TAF_SDC_GetPsSmsSrvExistFlg(VOS_VOID);
VOS_VOID TAF_SDC_SetImsSmsSrvExistFlg(
    VOS_UINT8                           ucImsSmsSrvExistFlg
);
VOS_UINT8 TAF_SDC_GetImsSmsSrvExistFlg(VOS_VOID);
VOS_VOID    TAF_SDC_SetImsSsSrvExistFlg(
    VOS_UINT8                           ucImsSsSrvExistFlg
);
VOS_UINT8   TAF_SDC_GetImsSsSrvExistFlg(VOS_VOID);
VOS_VOID    TAF_SDC_SetCsSsSrvExistFlg(
    VOS_UINT8                           ucCsSsSrvExistFlg
);
VOS_UINT8   TAF_SDC_GetCsSsSrvExistFlg(VOS_VOID);
VOS_VOID TAF_SDC_InitSvlteSupportFlag(
    TAF_SDC_INIT_CTX_TYPE_ENUM_UINT8    enInitType,
    TAF_SDC_MS_CAP_INFO_STRU           *pstMsCapInfo
);


VOS_VOID TAF_SDC_InitImsRatSupport(
    TAF_SDC_INIT_CTX_TYPE_ENUM_UINT8    enInitType,
    TAF_SDC_MS_CAP_INFO_STRU           *pstMsCapInfo
);
VOS_VOID TAF_SDC_InitImsCapability(
    TAF_SDC_INIT_CTX_TYPE_ENUM_UINT8    enInitType,
    TAF_SDC_MS_CAP_INFO_STRU           *pstMsCapInfo
);
VOS_VOID TAF_SDC_InitVoiceDomain(
    TAF_SDC_INIT_CTX_TYPE_ENUM_UINT8    enInitType,
    TAF_SDC_MS_CAP_INFO_STRU           *pstMsCapInfo
);
VOS_VOID TAF_SDC_InitSmsDomain(
    TAF_SDC_INIT_CTX_TYPE_ENUM_UINT8    enInitType,
    TAF_SDC_MS_CAP_INFO_STRU           *pstMsCapInfo
);

VOS_VOID TAF_SDC_InitImsConfigPara(
    TAF_SDC_INIT_CTX_TYPE_ENUM_UINT8    enInitType,
    TAF_SDC_MS_CAP_INFO_STRU           *pstMsCapInfo
);
VOS_VOID TAF_SDC_InitLteCsServiceCfg(
    TAF_SDC_INIT_CTX_TYPE_ENUM_UINT8    enInitType,
    TAF_SDC_MS_CAP_INFO_STRU           *pstMsCapInfo
);

VOS_VOID TAF_SDC_InitRedialCfgInfo(
    TAF_SDC_INIT_CTX_TYPE_ENUM_UINT8    enInitType,
    TAF_SDC_MS_CAP_INFO_STRU           *pstMsCapInfo
);

VOS_VOID TAF_SDC_InitImsRoamingCfgInfo(
    TAF_SDC_INIT_CTX_TYPE_ENUM_UINT8    enInitType,
    TAF_SDC_MS_CAP_INFO_STRU           *pstMsCapInfo
);

VOS_VOID TAF_SDC_InitImsUssdCfgInfo(
    TAF_SDC_INIT_CTX_TYPE_ENUM_UINT8    enInitType,
    TAF_SDC_MS_CAP_INFO_STRU           *pstMsCapInfo
);
VOS_VOID TAF_SDC_InitLcConfigPara(
    TAF_SDC_LC_CONFIG_PARA_STRU        *pstLcConfigPara
);


VOS_VOID TAF_SDC_SetGsmImsSupportFlag(
    VOS_UINT8                          ucGsmImsSupportFlag
);
VOS_UINT8 TAF_SDC_GetGsmImsSupportFlag(VOS_VOID);
VOS_VOID TAF_SDC_SetUtranImsSupportFlag(
    VOS_UINT8                          ucUtranImsSupportFlag
);
VOS_UINT8 TAF_SDC_GetUtranImsSupportFlag(VOS_VOID);

VOS_VOID TAF_SDC_SetLteImsSupportFlag(
    VOS_UINT8                           ucImsSupportFlag
);
VOS_UINT8 TAF_SDC_GetLteImsSupportFlag(VOS_VOID);
VOS_VOID TAF_SDC_SetAppCfgSupportType(
    VOS_UINT16                          usAppCfgSupportType
);
VOS_UINT16 TAF_SDC_GetAppCfgSupportType(VOS_VOID);


VOS_VOID TAF_SDC_SetCsAttachAllowFlg(VOS_UINT8 ucCsAttachAllowFlg);
VOS_UINT8 TAF_SDC_GetCsAttachAllowFlg(VOS_VOID);


OM_RING_ID TAF_SDC_GetErrLogRingBufAddr(VOS_VOID);
VOS_VOID TAF_SDC_SetErrLogRingBufAddr(OM_RING_ID pRingBuffer);
VOS_UINT8 TAF_SDC_GetErrlogCtrlFlag(VOS_VOID);
VOS_VOID TAF_SDC_SetErrlogCtrlFlag(VOS_UINT8 ucFlag);
VOS_UINT16 TAF_SDC_GetErrlogAlmLevel(VOS_VOID);
VOS_VOID TAF_SDC_SetErrlogAlmLevel(VOS_UINT16 usAlmLevel);
VOS_UINT32 TAF_SDC_GetErrlogOverflowCnt(VOS_VOID);
VOS_VOID TAF_SDC_SetErrlogOverflowCnt(VOS_UINT32 ulOverflowCnt);

VOS_UINT8 TAF_SDC_GetErrLogCsOosReportToAppFlag(VOS_VOID);
VOS_VOID TAF_SDC_SetErrLogCsOosReportToAppFlag(VOS_UINT8 ucFlag);
VOS_UINT8 TAF_SDC_GetErrLogPsOosReportToAppFlag(VOS_VOID);
VOS_VOID TAF_SDC_SetErrLogPsOosReportToAppFlag(VOS_UINT8 ucFlag);
VOS_UINT8 TAF_SDC_GetErrLogReportPowerOnBeginFlag(VOS_VOID);
VOS_VOID TAF_SDC_SetErrLogReportPowerOnBeginFlag(VOS_UINT8 ucFlag);
VOS_UINT8 TAF_SDC_GetErrLogReportPowerOffBeginFlag(VOS_VOID);
VOS_VOID TAF_SDC_SetErrLogReportPowerOffBeginFlag(VOS_UINT8 ucFlag);

/* Added by zwx247453 for CHR optimize, 2015-3-13 Begin */
VOS_UINT8 TAF_SDC_GetErrlogActiveRptFlag(VOS_VOID);
VOS_VOID TAF_SDC_SetErrlogActiveRptFlag(VOS_UINT8 ucActiveRptFlag);
VOS_UINT8 TAF_SDC_GetErrlogRatSwitchRptFlag(VOS_VOID);
VOS_VOID TAF_SDC_SetErrlogRatSwitchRptFlag(VOS_UINT8 ucRatSwitchRptFlag);
VOS_UINT32 TAF_SDC_GetErrlogRatSwitchStatisticTime(VOS_VOID);
VOS_VOID TAF_SDC_SetErrlogRatSwitchStatisticTime(
    VOS_UINT32                           ulStatisticTime
);
VOS_UINT32 TAF_SDC_GetErrlogRatSwitchStatisticNum(VOS_VOID);
VOS_VOID TAF_SDC_SetErrlogRatSwitchStatisticNum(
    VOS_UINT32                           ulSwitchNum
);
VOS_VOID TAF_SDC_ReadRatFrequentlySwitchChrRptCfgNvim(VOS_VOID);
VOS_UINT8 TAF_SDC_GetErrLogOldRatType(VOS_VOID);
VOS_VOID TAF_SDC_SetErrLogOldRatType(
    VOS_UINT8                           ucRatType
);
OM_RING_ID TAF_SDC_GetRatSwitchRingBufAddr(VOS_VOID);
VOS_VOID TAF_SDC_SetRatSwitchRingBufAddr(
    OM_RING_ID                          pRingBuffer
);
/* Added by zwx247453 for CHR optimize, 2015-3-13 End */
VOS_VOID TAF_SDC_ReadErrlogCtrlInfoNvim(VOS_VOID);
VOS_VOID TAF_SDC_InitErrLogInfo(
    TAF_SDC_ERRLOG_INFO_STRU           *pstErrLogInfo
);
#if (FEATURE_ON == FEATURE_PTM)
VOS_UINT32 TAF_SDC_PutRatSwitchRingBuf(
    VOS_CHAR                           *pbuffer,
    VOS_UINT32                          ulbytes
);
VOS_UINT32 TAF_SDC_RatSwitchRingBufRemoveRecord(
    VOS_UINT32                          ulbytes
);
VOS_UINT32 TAF_SDC_GetRecordFromRatSwitchRingBuf(
    VOS_CHAR                           *pbuffer,
    VOS_UINT32                          ulbytes
);
VOS_UINT32 TAF_SDC_GetRatSwitchRingBufferFreeBytes(VOS_VOID);
VOS_VOID TAF_SDC_CleanRatSwitchRingBuf(VOS_VOID);

VOS_VOID TAF_SDC_CreatRatSwitchRingBuf(VOS_VOID);
extern VOS_UINT32 TAF_SDC_PutErrLogRingBuf(
    VOS_CHAR                           *pbuffer,
    VOS_UINT32                          ulbytes
);
extern VOS_UINT32 TAF_SDC_GetErrLogRingBufContent(
    VOS_CHAR                           *pbuffer,
    VOS_UINT32                          ulbytes
);
extern VOS_UINT32 TAF_SDC_GetErrLogRingBufferUseBytes(VOS_VOID);

extern VOS_VOID TAF_SDC_CleanErrLogRingBuf(VOS_VOID);
#endif

VOS_VOID TAF_SDC_SetVoiceCallOnImsSupportFlag(
    VOS_UINT8                          ucVoiceCallOnImsSupportFlag
);
VOS_UINT8 TAF_SDC_GetVoiceCallOnImsSupportFlag(VOS_VOID);
VOS_VOID TAF_SDC_SetSmsOnImsSupportFlag(
    VOS_UINT8                          ucSmsOnImsSupportFlag
);
VOS_UINT8 TAF_SDC_GetSmsOnImsSupportFlag(VOS_VOID);
VOS_VOID TAF_SDC_SetVideoCallOnImsSupportFlag(
    VOS_UINT8                          ucVideoCallOnImsSupportFlag
);
VOS_UINT8 TAF_SDC_GetVideoCallOnImsSupportFlag(VOS_VOID);
VOS_VOID TAF_SDC_SetVoiceDomain(
    TAF_SDC_VOICE_DOMAIN_ENUM_UINT32    enVoiceDomain
);
TAF_SDC_VOICE_DOMAIN_ENUM_UINT32 TAF_SDC_GetVoiceDomain(VOS_VOID);
VOS_VOID TAF_SDC_SetSmsDomain(
    TAF_SDC_SMS_DOMAIN_ENUM_UINT8      enSmsDomain
);
TAF_SDC_SMS_DOMAIN_ENUM_UINT8 TAF_SDC_GetSmsDomain(VOS_VOID);
VOS_VOID TAF_SDC_SetLteEmsSupportFlag(
    VOS_UINT8                           ucLteEmsSupportFlag
);
VOS_UINT8 TAF_SDC_GetLteEmsSupportFlag(VOS_VOID);
VOS_VOID TAF_SDC_SetLteCsSeviceCap(
    TAF_SDC_LTE_CS_SERVICE_ENUM_UINT8   enLteCsServiceCap
);
TAF_SDC_LTE_CS_SERVICE_ENUM_UINT8 TAF_SDC_GetLteCsSeviceCap(VOS_VOID);
TAF_SDC_UE_USAGE_SETTING_ENUM_UINT8 TAF_SDC_GetUeUsageSetting(VOS_VOID);
VOS_VOID TAF_SDC_SetUeUsageSetting(
    TAF_SDC_UE_USAGE_SETTING_ENUM_UINT8   enUeUsageSetting
);

VOS_UINT8 TAF_SDC_GetRoamFlag(VOS_VOID);
VOS_VOID  TAF_SDC_SetRoamFlag(VOS_UINT8 ucRoamFlag);

VOS_UINT8 TAF_SDC_GetCampOnFlag( VOS_VOID );
VOS_VOID  TAF_SDC_SetCampOnFlag(VOS_UINT8 ucCampOnFlg);

/* Deleted by l00301449 for CDMA Iteration 15, 2015-5-18, begin */
/* Deleted by l00301449 for CDMA Iteration 15, 2015-5-18, end */


/* Modified by l00301449 for CDMA Iteration 15, 2015-5-15, begin */
VOS_VOID TAF_SDC_Set3GppRfAvailFlag(
    VOS_UINT8                           ucRfAvailFlg
);

VOS_UINT8 TAF_SDC_Get3GppRfAvailFlag(VOS_VOID);

VOS_VOID TAF_SDC_Set1xRfAvailFlag(
    VOS_UINT8                           ucRfAvailFlg
);

VOS_UINT8 TAF_SDC_Get1xRfAvailFlag(VOS_VOID);

VOS_VOID TAF_SDC_SetHrpdRfAvailFlag(
    VOS_UINT8                           ucRfAvailFlg
);

VOS_UINT8 TAF_SDC_GetHrpdRfAvailFlag(VOS_VOID);


/* Modified by l00301449 for CDMA Iteration 15, 2015-5-15, end */


TAF_SDC_SYS_MODE_ENUM_UINT8 TAF_SDC_GetCampSysMode( VOS_VOID );

VOS_UINT8 TAF_SDC_GetSimCsRegStatus( VOS_VOID );
VOS_VOID TAF_SDC_SetSimCsRegStatus(
    VOS_UINT8       ucSimCsRegStatus
);


VOS_UINT8 TAF_SDC_GetSimPsRegStatus( VOS_VOID );
VOS_VOID TAF_SDC_SetSimPsRegStatus(
    VOS_UINT8       ucSimPsRegStatus
);

TAF_SDC_RAT_PRIO_STRU* TAF_SDC_GetMsPrioRatList( VOS_VOID );
VOS_VOID TAF_SDC_SetMsPrioRatList(
    TAF_SDC_RAT_PRIO_STRU              *pstPrioRatList
);


VOS_UINT8 TAF_SDC_GetCallRedailFromImsToCsSupportFlag(VOS_VOID);

VOS_VOID TAF_SDC_SetCallRedailFromImsToCsSupportFlag(VOS_UINT8 ucCallRedialFromImsToCs);

VOS_UINT8 TAF_SDC_GetSmsRedailFromImsToCsSupportFlag(VOS_VOID);

VOS_VOID TAF_SDC_SetSmsRedailFromImsToCsSupportFlag(VOS_UINT8 ucSmsRedialFromImsToCs);

VOS_UINT8 TAF_SDC_GetRoamingSupportFlag(VOS_VOID);

VOS_VOID TAF_SDC_SetRoamingSupportFlag(VOS_UINT8 ucRoamingSupport);

VOS_VOID    TAF_SDC_SetImsNormalRegStatus(
    TAF_SDC_IMS_NORMAL_REG_STATUS_ENUM_UINT8    enRegStatus
);

TAF_SDC_IMS_NORMAL_REG_STATUS_ENUM_UINT8   TAF_SDC_GetImsNormalRegStatus(VOS_VOID);


VOS_VOID  TAF_SDC_SetCurPhoneMode(
    TAF_SDC_PHONE_MODE_ENUM_UINT8       enPhoneMode
);

TAF_SDC_PHONE_MODE_ENUM_UINT8  TAF_SDC_GetCurPhoneMode(VOS_VOID);

TAF_SDC_CREG_TYPE_ENUM_UINT8  TAF_SDC_GetCregType(VOS_VOID);

TAF_SDC_CGREG_TYPE_ENUM_UINT8  TAF_SDC_GetCgregType(VOS_VOID);

TAF_SDC_CEREG_TYPE_ENUM_UINT8  TAF_SDC_GetCeregType(VOS_VOID);

VOS_VOID  TAF_SDC_SetCregType(TAF_SDC_CREG_TYPE_ENUM_UINT8 enCregType);

VOS_VOID  TAF_SDC_SetCgregType(TAF_SDC_CGREG_TYPE_ENUM_UINT8 enCgregType);

VOS_VOID  TAF_SDC_SetCeregType(TAF_SDC_CEREG_TYPE_ENUM_UINT8 enCeregType);

#if (FEATURE_ON == FEATURE_ECALL)
TAF_SDC_ECALL_NUM_STRU*                 TAF_SDC_GetEcallTestNumber(VOS_VOID);
TAF_SDC_ECALL_NUM_STRU*                 TAF_SDC_GetEcallRecfgNumber(VOS_VOID);
TAF_SDC_CALL_MODE_ENUM_UINT8            TAF_SDC_GetCurCallMode(VOS_VOID);
VOS_VOID  TAF_SDC_SetCurCallMode(
    TAF_SDC_CALL_MODE_ENUM_UINT8        enCallMode
);
#endif

VOS_VOID TAF_SDC_InitPhoneInfo(
    TAF_SDC_PHONE_INFO_STRU            *pstPhInfo
);

VOS_VOID TAF_SDC_InitRegReportStatus(
    TAF_SDC_REG_REPORT_STATUS_STRU     *pstRegReportStatus
);


VOS_VOID TAF_SDC_InitDsdaPlmnSearchEnhancedCfg(VOS_VOID);

VOS_UINT8 TAF_SDC_GetPsAttachAllowFlg(VOS_VOID);
VOS_VOID TAF_SDC_SetPsAttachAllowFlg(VOS_UINT8 ucPsAttachAllowFlg);


VOS_VOID  TAF_SDC_SetUtranSkipWPlmnSearchFlag(VOS_UINT8  ucUtranSkipWPlmnSearchFlag);
VOS_UINT8  TAF_SDC_GetUtranSkipWPlmnSearchFlag(VOS_VOID);


VOS_UINT8 TAF_SDC_GetUssdOnImsSupportFlag(VOS_VOID);

VOS_VOID TAF_SDC_SetUssdOnImsSupportFlag(VOS_UINT8 ucUssdOnImsSupportFlag);
VOS_VOID TAF_SDC_SetLCEnableFlg(
    VOS_UINT8                           ucLCEnableFlg
);

VOS_UINT8 TAF_SDC_GetLCEnableFlg(VOS_VOID);

VOS_UINT8 TAF_SDC_GetLCWorkCfg(VOS_VOID);
VOS_VOID   TAF_SDC_SetLCWorkCfg(
    TAF_NVIM_LC_WORK_CFG_ENUM_UINT8     enLCWorkCfg
);

VOS_UINT8 TAF_SDC_GetLCRatCombined(VOS_VOID);

TAF_SDC_LC_CONFIG_PARA_STRU* TAF_SDC_GetLcConfigPara(VOS_VOID);

/* Added by h00313353 for iteration 9, 2015-2-17, begin */
VOS_VOID TAF_SDC_SaveCsimCardType(
    USIMM_CARD_TYPE_ENUM_UINT32         enCardType
);

VOS_VOID TAF_SDC_SaveUsimCardType(
    USIMM_CARD_TYPE_ENUM_UINT32         enCardType
);

VOS_VOID TAF_SDC_SaveUsimCardStatus(
    USIMM_CARD_SERVIC_ENUM_UINT32       enUsimStatus
);

VOS_VOID TAF_SDC_SaveCsimCardStatus(
    USIMM_CARD_SERVIC_ENUM_UINT32       enCsimStatus
);
/* Added by h00313353 for iteration 9, 2015-2-17, end */

#if (FEATURE_ON == FEATURE_ECALL)
VOS_VOID TAF_SDC_InitECallNumber(
    TAF_SDC_ECALL_NUM_STRU             *pstECallNumber
);
#endif


VOS_VOID TAF_SDC_SetPsServiceConnStatusFlag(
    VOS_UINT8                           ucPsServiceConnStatusFlag
);
VOS_UINT8 TAF_SDC_GetPsServiceConnStatusFlag(VOS_VOID);
#if (FEATURE_ON == FEATURE_LTE)
VOS_VOID TAF_SDC_SetEpsServiceConnStatusFlag(
    VOS_UINT8                           ucEpsServiceConnStatusFlag
);
VOS_UINT8 TAF_SDC_GetEpsServiceConnStatusFlag(VOS_VOID);
#endif
#if (FEATURE_ON == FEATURE_BASTET)
VOS_UINT8   TAF_SDC_GetBastetSupportFlag(VOS_VOID);
#endif

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_VOID TAF_SDC_Set1xCallUcimEmccNumList(
    TAF_SDC_UCIM_ECC_NUM_LIST_STRU     *pstUcimEccNumList
);

TAF_SDC_UCIM_ECC_NUM_LIST_STRU* TAF_SDC_Get1xCallUcimEmccNumList(VOS_VOID);

VOS_INT32 TAF_SDC_Get1xSid(VOS_VOID);

VOS_INT32 TAF_SDC_Get1xNid(VOS_VOID);

VOS_UINT8 TAF_SDC_Get1xRoamingFlag(VOS_VOID);

VOS_VOID TAF_SDC_Set1xSysInfo(
    NAS_MSCC_PIF_1X_SYS_SRV_INFO_STRU          *pSysInfo
);

TAF_SDC_1X_SYS_INFO_STRU* TAF_SDC_Get1xSysInfo(VOS_VOID);
TAF_SDC_HRPD_SYS_INFO_STRU* TAF_SDC_GethrpdSysInfo(VOS_VOID);

/* Added by y00307564 for CDMA 1X Iteration 6 2015-1-10 begin */

TAF_SDC_1X_SIG_QUALITY_INFO_STRU* TAF_SDC_Get1xSigQualityInfo(VOS_VOID);
VOS_VOID TAF_SDC_Init1xSigQualityRptValue(VOS_VOID);
/* Added by y00307564 for CDMA 1X Iteration 6 2015-1-10 end */

/* Added by z00316370 for UTS 2015-5-16 begin */
VOS_UINT8 TAF_SDC_Get1xPrevInUse(VOS_VOID);

VOS_UINT16 TAF_SDC_Get1xChan(VOS_VOID);
/* Added by z00316370 for UTS 2015-5-16 end */
/* Added by y00322978 for CDMA Iteration 17, 2015-7-9, begin */
VOS_VOID TAF_SDC_SetXCaLLState(
    NAS_OM_1X_CALL_STATE_ENUM_UINT8        enXCallState
);
NAS_OM_1X_CALL_STATE_ENUM_UINT8 TAF_SDC_GetXCallState(
    VOS_VOID
);
VOS_VOID TAF_SDC_SetCdmaStatusReportPeriod(
    VOS_UINT32                          ulRptPeriod
);
VOS_UINT32  TAF_SDC_GetCdmaStatusReportPeriod(
    VOS_VOID
);
VOS_VOID TAF_SDC_Init1xSysInfo(
    TAF_SDC_1X_SYS_INFO_STRU           *pst1xSysInfo
);
VOS_VOID TAF_SDC_InitHrpdSysInfo(
    TAF_SDC_HRPD_SYS_INFO_STRU         *pstHrpdSysInfo
);
/* Added by y00322978 for CDMA Iteration 17, 2015-7-9, end */

#endif


/* Modified by l00305157 for Service_State_Optimize_PhaseI, 2014-11-29, begin */
#if (FEATURE_ON == FEATURE_LTE)
VOS_VOID TAF_SDC_InitAppNetwork_Info(TAF_SDC_APPNETWORK_INFO *pstAppNetworkInfo);
VOS_VOID TAF_SDC_InitNetworkRssiValue( TAF_SDC_RSSI_VALUE_STRU    *pstRssiValue);
VOS_VOID TAF_SDC_InitAppNetworkPlmnInfo(TAF_SDC_SERVICED_PLMN_INFO_STRU  *pstServPlmnInfo);
#endif
/* Modified by l00305157 for Service_State_Optimize_PhaseI, 2014-11-29, begin */

/* Added by c00318887 for AT&T phaseII, 2015-2-26, begin */
TAF_SDC_OPL_FILE_INFO_STRU* TAF_SDC_GetUsimOplFileInfo(VOS_VOID);
VOS_VOID TAF_SDC_SetCopsFormatType(
    TAF_SDC_COPS_FORMAT_TYPE_ENUM_UINT8                     enCopsFormatType
);
TAF_SDC_COPS_FORMAT_TYPE_ENUM_UINT8 TAF_SDC_GetCopsFormatType(VOS_VOID);

TAF_SDC_OPL_FILE_INFO_STRU* TAF_SDC_GetSimOplFileInfo(VOS_VOID);
TAF_SDC_PNN_FILE_INFO_STRU* TAF_SDC_GetUsimPnnFileInfo(VOS_VOID);
TAF_SDC_PNN_FILE_INFO_STRU* TAF_SDC_GetSimPnnFileInfo(VOS_VOID);
TAF_SDC_SPN_FILE_INFO_STRU* TAF_SDC_GetUsimSpnFileInfo(VOS_VOID);
TAF_SDC_SPN_FILE_INFO_STRU* TAF_SDC_GetSimSpnFileInfo(VOS_VOID);
TAF_SDC_CPHS_FILE_INFO_STRU* TAF_SDC_GetChpsFileInfo(VOS_VOID);
TAF_SDC_SPDI_FILE_INFO_STRU* TAF_SDC_GetUsimSpdiFileInfo(VOS_VOID);
TAF_SDC_SPDI_FILE_INFO_STRU* TAF_SDC_GetSimSpdiFileInfo(VOS_VOID);
TAF_SDC_MM_INFO_STRU* TAF_SDC_GetMmInfo(VOS_VOID);
TAF_SDC_OPER_NAME_TYPE_PRIO_STRU* TAF_SDC_GetOperNamePrio(VOS_VOID);
VOS_VOID TAF_SDC_InitEnhancedOperatorNameInfo(
    TAF_SDC_ENHANCED_OPERATOR_NAME_INFO_STRU               *pstEnhancedOperatorNameInfo
);
VOS_VOID TAF_SDC_ReadEnhancedOperNameServiceCfgNvim( VOS_VOID );

VOS_VOID TAF_SDC_ReadCustomOperNameInfoNvim(VOS_VOID);

TAF_SDC_ENHANCED_OPERATOR_NAME_INFO_STRU *TAF_SDC_GetEnhancedOperatorNameInfo(VOS_VOID);
TAF_SDC_CUSTOM_OPER_NAME_INFO_STRU* TAF_SDC_GetCustomOperNameInfo(VOS_VOID);

VOS_UINT8 TAF_SDC_GetPlmnExactlyCompareFlg(VOS_VOID);
VOS_VOID  TAF_SDC_SetPlmnExactlyCompareFlg(VOS_UINT8  ucPlmnExactlyComparaFlag);
VOS_VOID  TAF_SDC_SetPlmnCompareWildCard(
    VOS_CHAR                            cWildCard
);
VOS_CHAR  TAF_SDC_GetPlmnCompareWildCard(VOS_VOID);
VOS_VOID TAF_SDC_InitPlmnExactlyCompareFlg(VOS_VOID);
VOS_VOID TAF_SDC_InitRefreshAllFileRestartFlag(VOS_VOID);
VOS_VOID TAF_SDC_SetRefreshAllFileRestartFlag(
    VOS_UINT8                           ucRefreshAllFileRestartFlag
);
VOS_UINT8 TAF_SDC_GetRefreshAllFileRestartFlag(VOS_VOID);

/* Added by c00318887 for AT&T phaseII, 2015-2-26, end */

/* Modified by l00305157 for for Service_State_Optimize_PhaseI, 2014-11-29, begin */
TAF_SDC_NETWORK_INFO_STRU* TAF_SDC_GetCurrNetworkInfo(VOS_VOID);
VOS_VOID TAF_SDC_SetAppRssiValue(VOS_UINT8 ucRssiValue);
VOS_UINT8 TAF_SDC_GetAppRssiValue(VOS_VOID);
VOS_UINT16 TAF_SDC_GetAppCellUlFreq(VOS_VOID);
VOS_UINT16 TAF_SDC_GetAppCellDlFreq(VOS_VOID);
VOS_UINT32 TAF_SDC_GetAppLteArfcn(VOS_VOID);
VOS_VOID TAF_SDC_SetAppLteArfcn(VOS_UINT32 ulLteArfcn);
VOS_VOID TAF_SDC_SetAppServicePlmnId(TAF_SDC_PLMN_ID_STRU *pstPlmnId);
TAF_SDC_PLMN_ID_STRU *TAF_SDC_GetAppServicePlmnId(VOS_VOID);
VOS_VOID TAF_SDC_SetAppSysMode(TAF_SDC_SYS_MODE_ENUM_UINT8 enSysMode);
TAF_SDC_SYS_MODE_ENUM_UINT8 TAF_SDC_GetAppSysMode( VOS_VOID );
VOS_VOID TAF_SDC_SetAppSysSubMode(TAF_SDC_SYS_SUBMODE_ENUM_UINT8 enSysSubMode);
TAF_SDC_SYS_SUBMODE_ENUM_UINT8 TAF_SDC_GetAppSysSubMode( VOS_VOID );
VOS_VOID TAF_SDC_SetAppCampLac(VOS_UINT16 usLac);
VOS_UINT16 TAF_SDC_GetAppCampLac(VOS_VOID);
VOS_VOID TAF_SDC_SetAppCampRac(VOS_UINT8 ucRac);
VOS_UINT8 TAF_SDC_GetAppCampRac(VOS_VOID);
VOS_VOID TAF_SDC_SetAppCampCellId(VOS_UINT32 ulServiceCellId);
VOS_UINT32 TAF_SDC_GetAppCampCellId(VOS_VOID);
VOS_VOID TAF_SDC_SetAppUtranMode(VOS_UINT8 ucServiceUtranMode);
VOS_UINT8 TAF_SDC_GetAppUtranMode(VOS_VOID);
VOS_VOID TAF_SDC_SetAppRoamFlg(VOS_UINT8 ucServiceRoamFlg);
VOS_UINT8 TAF_SDC_GetAppRoamFlg(VOS_VOID);
TAF_SDC_APPNETWORK_INFO* TAF_SDC_GetAppNetworkInfo(VOS_VOID);
/* Modified by l00305157 for for Service_State_Optimize_PhaseI, 2014-11-29, end*/

VOS_VOID  TAF_SDC_SetCurImsSwitchState(
    TAF_SDC_IMS_SWITCH_STATE_ENUM_UINT8       enState
);
TAF_SDC_IMS_SWITCH_STATE_ENUM_UINT8  TAF_SDC_GetCurImsSwitchState(VOS_VOID);

/* Add by l00305157 for Service_State_Optimize_PhaseII, 2015-02-11, begin */
TAF_SDC_SERVICE_STATUS_ENUM_UINT8 TAF_SDC_GetAppCsServiceStatus( VOS_VOID );
VOS_VOID TAF_SDC_SetAppCsServiceStatus(TAF_SDC_SERVICE_STATUS_ENUM_UINT8 enCsServiceStatus);
TAF_SDC_SERVICE_STATUS_ENUM_UINT8 TAF_SDC_GetAppPsServiceStatus( VOS_VOID );

VOS_VOID TAF_SDC_SetAppPsServiceStatus(TAF_SDC_SERVICE_STATUS_ENUM_UINT8 enPsServiceStatus);
/* Add by l00305157 for Service_State_Optimize_PhaseII, 2015-02-11, end */

/* Added by h00313353 for iteration 9, 2015-2-9, begin */
VOS_VOID TAF_SDC_SetUsimStatus(
    TAF_SDC_USIM_STATUS_ENUM_UINT8 enSimStatus
);

VOS_VOID TAF_SDC_SetCsimStatus(
    TAF_SDC_USIM_STATUS_ENUM_UINT8      enSimStatus
);

VOS_VOID TAF_SDC_SetIccIdInfo(
    VOS_UINT8                   ucLen,
    VOS_UINT8                  *pucIccId
);

TAF_SDC_ICCID_INFO_STRU *TAF_SDC_GetIccIdInfo( VOS_VOID );

TAF_SDC_SIM_TYPE_ENUM_UINT8 TAF_SDC_GetUsimType(
    VOS_VOID
);

TAF_SDC_SIM_TYPE_ENUM_UINT8 TAF_SDC_GetCsimType(
    VOS_VOID
);

TAF_SDC_USIM_STATUS_ENUM_UINT8 TAF_SDC_GetUsimStatus(
    VOS_VOID
);

TAF_SDC_USIM_STATUS_ENUM_UINT8 TAF_SDC_GetCsimStatus(
    VOS_VOID
);

VOS_VOID TAF_SDC_SetCsimType(
    TAF_SDC_SIM_TYPE_ENUM_UINT8         enCsimType
);

VOS_VOID TAF_SDC_SetUsimType(
    TAF_SDC_SIM_TYPE_ENUM_UINT8         enCsimType
);

VOS_VOID TAF_SDC_InitSimInfo(TAF_SDC_USIM_INFO_STRU *pstSimInfo);

TAF_SDC_SWITCH_IMS_TO_CS_REDIAL_CAUSE_CONFIG_STRU *
TAF_SDC_GetImsToCsRedialCauseConfig(VOS_VOID);


/* Added by h00313353 for iteration 9, 2015-2-9, end */

/* Deleted by h00313353 for CDMA Iteration 15, 2015-5-30, begin */

/* Deleted by h00313353 for CDMA Iteration 15, 2015-5-30, end */

VOS_VOID    TAF_SDC_SetXsmsCallExistFlg(
    VOS_UINT8                           ucIsXsmsCallExistFlg
);

VOS_UINT8 TAF_SDC_GetXsmsCallExistFlg(
    VOS_VOID
);

VOS_UINT16 TAF_SDC_Get1xBaseId(VOS_VOID);

VOS_VOID TAF_SDC_SetCdmaCurUeState(
    TAF_SDC_1X_UE_MAIN_STATUS_ENUM_UINT8    enCasState
);

VOS_UINT8 TAF_SDC_GetCdmaCurUeState(
    VOS_VOID
);

TAF_SDC_NONNORMAL_REG_STATUS_MERGE_CFG_STRU* TAF_SDC_GetNonnormalRegStatusMergeCfg(VOS_VOID);

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

#endif /* end of TafSdcCtx.h */
