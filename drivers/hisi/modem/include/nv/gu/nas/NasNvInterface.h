/******************************************************************************

  Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : NasNvInterface.h
  Description     : NasNvInterface.h header file
  History         :

******************************************************************************/

#ifndef __NASNVINTERFACE_H__
#define __NASNVINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

#include "PsTypeDef.h"

/*****************************************************************************
  2 Macro
*****************************************************************************/
#define NAS_MMC_NV_ITEM_ACTIVE          (1)                                     /* NV��� */
#define NAS_MMC_NV_ITEM_DEACTIVE        (0)                                     /* NV��δ���� */

/* GPRS GEA �㷨֧�ֺ궨�� */
#define NAS_MMC_GPRS_GEA1_SUPPORT       (0x01)                                  /* ֧��GPRS GEA1�㷨 */
#define NAS_MMC_GPRS_GEA1_VALUE         (0x80)                                  /* ֧��GEA1ʱ����������ֵ */
#define NAS_MMC_GPRS_GEA2_VALUE         (0x40)                                  /* ֧��GEA2ʱ����������ֵ */
#define NAS_MMC_GPRS_GEA3_VALUE         (0x20)                                  /* ֧��GEA3ʱ����������ֵ */
#define NAS_MMC_GPRS_GEA4_VALUE         (0x10)                                  /* ֧��GEA4ʱ����������ֵ */
#define NAS_MMC_GPRS_GEA5_VALUE         (0x08)                                  /* ֧��GEA5ʱ����������ֵ */
#define NAS_MMC_GPRS_GEA6_VALUE         (0x04)                                  /* ֧��GEA6ʱ����������ֵ */
#define NAS_MMC_GPRS_GEA7_VALUE         (0x02)                                  /* ֧��GEA7ʱ����������ֵ */

#define NAS_MMC_GPRS_GEA2_SUPPORT       (0x02)                                  /* ֧��GPRS GEA2�㷨 */
#define NAS_MMC_GPRS_GEA3_SUPPORT       (0x04)                                  /* ֧��GPRS GEA3�㷨 */
#define NAS_MMC_GPRS_GEA4_SUPPORT       (0x08)                                  /* ֧��GPRS GEA4�㷨 */
#define NAS_MMC_GPRS_GEA5_SUPPORT       (0x10)                                  /* ֧��GPRS GEA5�㷨 */
#define NAS_MMC_GPRS_GEA6_SUPPORT       (0x20)                                  /* ֧��GPRS GEA6�㷨 */
#define NAS_MMC_GPRS_GEA7_SUPPORT       (0x40)                                  /* ֧��GPRS GEA7�㷨 */
#define NAS_MMC_NVIM_MAX_EPLMN_NUM      (16)                                    /* en_NV_Item_EquivalentPlmn NV�е�Чplmn���� */
#define NAS_MMC_NVIM_MAX_MCC_SIZE       (3)                                     /* plmn��Mcc��󳤶� */
#define NAS_MMC_NVIM_MAX_MNC_SIZE       (3)                                     /* plmn��Mnc��󳤶� */
#define NAS_MMC_LOW_BYTE_MASK           (0x0f)

#define NAS_MMC_NVIM_MAX_USER_CFG_IMSI_PLMN_NUM                  (6)                 /* �û����õ�����֧�ֵ�USIM/SIM���ĸ��� */
#define NAS_MMC_NVIM_MAX_USER_CFG_EHPLMN_NUM                     (6)                 /* �û����õ�EHplmn�ĸ��� */
#define NAS_MMC_MAX_BLACK_LOCK_PLMN_WITH_RAT_NUM            (8)                 /* ��ֹ���뼼����PLMN ID�������� */
#define NAS_MMC_NVIM_MAX_USER_CFG_EXT_EHPLMN_NUM              (8)                /* ��չ��NV���EHplmn���������*/
#define NAS_MMC_NVIM_MAX_USER_OPLMN_VERSION_LEN               (8)               /* �û����õ�OPLMN�汾����󳤶� */
#define NAS_MMC_NVIM_MAX_USER_OPLMN_IMSI_NUM                  (6)               /* �û����õ�OPLMN����֧�ֵ�USIM/SIM���ĸ��� */
#define NAS_MMC_NVIM_MAX_USER_CFG_OPLMN_NUM                   (256)             /* �û����õ�OPLMN�������� */
#define NAS_MMC_NVIM_OPLMN_WITH_RAT_UNIT_LEN                  (5)               /* �û����õĴ����뼼��OPLMN������Ԫ���ȣ���6F61�ļ��Ļ������ȵ�ԪΪ5 */
#define NAS_MMC_NVIM_MAX_USER_CFG_OPLMN_DATA_LEN              (500)             /* �û�����OPLMN������ֽ���,����ǰֻ֧��500*/
#define NAS_MMC_NVIM_MAX_USER_CFG_OPLMN_DATA_EXTEND_LEN       (1280)            /* ��չ����û�����OPLMN������ֽ���*/


/* Modified by c00318887 for DPlmn���ݺ����Ƚ���HPLMN, 2015-5-18, begin */
/* ����:��128��256; ����Ԥ��������Ϣ,��6��7*/
#define NAS_MMC_NVIM_MAX_CFG_DPLMN_DATA_LEN             (7*256)            /* ��չ����û�����DPLMN������ֽ��� */
#define NAS_MMC_NVIM_MAX_CFG_NPLMN_DATA_LEN             (7*256)            /* ��չ����û�����NPLMN������ֽ��� */
/* Modified by c00318887 for DPlmn���ݺ����Ƚ���HPLMN, 2015-5-18, end */

#define NAS_MMC_NVIM_MAX_CFG_DPLMN_DATA_EXTEND_LEN       (6*128)            /* ��չ����û�����DPLMN������ֽ���*/
#define NAS_MMC_NVIM_MAX_CFG_NPLMN_DATA_EXTEND_LEN       (6*128)            /* ��չ����û�����NPLMN������ֽ���*/
#define NAS_MMC_NVIM_MAX_CFG_HPLMN_NUM                   (3*8)


#define NAS_NVIM_MAX_OPER_SHORT_NAME_LEN                36
#define NAS_NVIM_MAX_OPER_LONG_NAME_LEN                 40

#define NAS_NVIM_ITEM_MAX_IMSI_LEN          (9)                     /* ����IMSI�ĳ��� */
#define NAS_MML_NVIM_PS_LOCI_SIM_FILE_LEN                    (14)                    /* USIM��PSLOCI�ļ��ĳ��� */
#define NAS_NVIM_PS_LOCI_SIM_FILE_LEN                    (14)                    /* USIM��PSLOCI�ļ��ĳ��� */

#define NAS_UTRANCTRL_MAX_NVIM_CFG_TD_MCC_LIST_NUM          (6)                 /* ģʽ�Զ��л������Ŀ����ù�������� */
#define NAS_UTRANCTRL_MAX_NVIM_CFG_IMSI_PLMN_LIST_NUM       (6)                 /* ģʽ�Զ��л������Ŀ�����USIM/IMSI������Ÿ��� */

#define NAS_MML_NVIM_MAX_DISABLED_RAT_PLMN_NUM              (8)                 /* ��ֹ���뼼����PLMN ID�������� */

#define NAS_SIM_FORMAT_PLMN_LEN                     (3)                     /* Sim����ʽ��Plmn���� */

#define NAS_MML_NVIM_MAX_BLACK_LOCK_PLMN_NUM                 (16)                    /* ����������֧�ֵ�PLMN ID�������� */

#define NAS_MML_NVIM_MAX_WHITE_LOCK_PLMN_NUM                 (16)                    /* ����������֧�ֵ�PLMN ID�������� */

#define NAS_MML_BG_SEARCH_REGARDLESS_MCC_NUMBER         (10)                     /* BG�Ѳ����ǹ�����Ĺ����������� */
#define NAS_MML_SINGLE_DOMAIN_FAIL_ACTION_MAX_LIST      (5)                     /* ����ԭ��ֵ����б� */

#define NV_ITEM_NET_CAPABILITY_MAX_SIZE                     (10)

#define NAS_MMC_NVIM_SUPPORTED_3GPP_RELEASE_SIZE            (2)                 /* ��ǰ֧�ֵ�Э��汾 */

#define NAS_MMC_NVIM_MAX_IMSI_LEN                           (9)                     /* ����IMSI�ĳ��� */

#define NVIM_MAX_EPLMN_NUM                                  (16)
#define NVIM_MAX_MCC_SIZE                                   (3)
#define NVIM_MAX_MNC_SIZE                                   (3)

#define NVIM_MAX_FDD_FREQ_BANDS_NUM                         (12)

/*+CGMI - ��ȡ����������*/

#define NAS_NVIM_MAX_IMSI_FORBIDDEN_LIST_NUM         (16)
#define NAS_NVIM_MAX_RAT_FORBIDDEN_LIST_NUM          (8)    /* Ԥ����չ */
#define NAS_NVIM_MAX_SUPPORTED_FORBIDDEN_RAT_NUM     (2)

#define NAS_NVIM_FORBIDDEN_RAT_NUM_0                 (0)
#define NAS_NVIM_FORBIDDEN_RAT_NUM_1                 (1)
#define NAS_NVIM_FORBIDDEN_RAT_NUM_2                 (2)


#define NAS_NVIM_MAX_REJECT_NO_RETRY_CAUSE_NUM              (8)

#define NAS_NVIM_MAX_LAU_REJ_TRIG_PLMN_SEARCH_CAUSE_NUM     (12)

/* ��NVIDö�ٵ�ת����(PS_NV_ID_ENUM, SYS_NV_ID_ENUM, RF_NV_ID_ENUM) */
typedef VOS_UINT16  NV_ID_ENUM_U16;
#define NV_ITEM_IMEI_SIZE                      16
#define NV_ITEM_MMA_OPERATORNAME_SIZE          84

#define NV_ITEM_OPER_NAME_LONG          (40)
#define NV_ITEM_OPER_NAME_SHORT         (36)
#define NV_ITEM_PLMN_ID_LEN             (8)

#define NV_ITEM_AT_PARA_SIZE                   100
#define NV_ITEM_HPLMN_FIRST_SEARCH_SIZE        1  /* ��һ��HPLMN������ʱ���� */
#define NVIM_ITEM_MAX_IMSI_LEN          (9)                     /* ����IMSI�ĳ��� */

#define CNAS_NVIM_MAX_1X_MRU_SYS_NUM                            (12)

#define NAS_MMC_NVIM_MAX_CAUSE_NUM      (10)     /* NV����ԭ��ֵ������ */

#define CNAS_NVIM_PRL_SIZE                                      (4096) /* PRL NV size: 4K byte */

#define CNAS_NVIM_MAX_1X_BANDCLASS_NUM                          (32)

/* Added by h00313353 for iteration 7, 2014-12-31, begin */
#define CNAS_NVIM_MAX_1X_HOME_SID_NID_NUM                       (20)
#define CNAS_NVIM_MAX_OOC_SCHEDULE_PHASE_NUM                    (8)
/* Added by h00313353 for iteration 7, 2014-12-31, end */

/* Added by H00300778 for CDMA EVDO Iteration 0, 2014-12-11, begin */
#define CNAS_NVIM_MAX_HRPD_MRU_SYS_NUM                           (12)
#define CNAS_NVIM_HRPD_SUBNET_LEN                                (16)
/* Added by H00300778 for CDMA EVDO Iteration 0, 2014-12-11, end */

/* Added by n00742771 for CDMA 1X Iteration 8 2015-2-7 begin */
#define CNAS_NVIM_MAX_STORAGE_BLOB_LEN                      ( 255 )
/* Added by n00742771 for CDMA 1X Iteration 8 2015-2-7 end */

#define NAS_NVIM_BYTES_IN_SUBNET                            (16)
#define NAS_NVIM_MAX_RAT_NUM                                (7)                 /* Ԥ����1X��HRPD */

#define NAS_MSCC_NVIM_MLPL_SIZE                                      (1024) /* PRL NV size: 1K byte */
#define NAS_MSCC_NVIM_MSPL_SIZE                                      (1024) /* PRL NV size: 1K byte */

#define NAS_NV_TRI_MODE_CHAN_PARA_PROFILE_NUM      ( 8 )                       /*  ����ȫ��ͨ���ص�ͨ�����ó�����Ŀ */

/* Added by y00307564 for CDMA Iteration 12 2015-5-30 begin */
#define CNAS_NVIM_ICCID_OCTET_LEN                            (10)
#define CNAS_NVIM_MEID_OCTET_NUM                             (7)
#define CNAS_NVIM_UATI_OCTET_LENGTH                          (16)
/* Added by y00307564 for CDMA Iteration 12 2015-5-30 end */

#define CNAS_NVIM_MAX_WHITE_LOCK_SYS_NUM                     (20)

#define CNAS_NVIM_MAX_HRPD_CUSTOMIZE_FREQ_NUM                (10)

/* Added by h00313353 for Iteration 17, 2015-8-11, begin */
#define CNAS_NVIM_MAX_CDMA_1X_CUSTOM_PREF_CHANNELS_NUM              (10)
/* Added by h00313353 for Iteration 17, 2015-8-11, end */

/* Added by c00318887 for file refresh��Ҫ����������, 2015-4-28, begin */
/* �����ȼ�PLMN refresh ����������Ĭ���ӳ�ʱ��: ��λ �� */
#define NV_ITEM_HIGH_PRIO_PLMN_REFRESH_TRIGGER_BG_SEARCH_DEFAULT_DELAY_LEN    (5)
/* Added by c00318887 for file refresh��Ҫ����������, 2015-4-28, end */

#define NAS_NVIM_LTE_OOS_2G_PREF_PLMN_SEL_MAX_IMSI_LIST_NUM      (16)    /* SIM���б� (LTE OOS������2G����3G) */

/* Added by z00359541 for CS REG FAIL FORB LA, 2015-9-23, begin */
#define NAS_MML_NVIM_MAX_REG_FAIL_CAUSE_NUM        (16)        /*֧�ֵĽ�ֹLA�б��С*/
/* Added by z00359541 for CS REG FAIL FORB LA, 2015-9-23, end */

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/

enum NAS_MMC_NVIM_SINGLE_DOMAIN_REG_FAIL_ACTION_ENUM
{
    NAS_MMC_NVIM_SINGLE_DOMAIN_REG_FAIL_ACTION_PLMN_SELECTION                    = 0,            /* �������� */
    NAS_MMC_NVIM_SINGLE_DOMAIN_REG_FAIL_ACTION_NORMAL_CAMP_ON                    = 1,            /* ����פ�� */
    NAS_MMC_NVIM_SINGLE_DOMAIN_REG_FAIL_ACTION_OPTIONAL_PLMN_SELECTION           = 2,            /* ������ѡ���� */
    NAS_MMC_NVIM_SINGLE_DOMAIN_REG_FAIL_ACTION_LIMITED_CAMP_ON                   = 3,            /* ����פ�� */

    NAS_MMC_NVIM_SINGLE_DOMAIN_ROAMING_REG_FAIL_ACTION_PLMN_SELECTION            = 4,            /* ������������ע�ᷢ����������HOME�����ϲ���Ч */

    NAS_MMC_NVIM_SINGLE_DOMAIN_REG_FAIL_ACTION_BUTT
};
typedef VOS_UINT8 NAS_MMC_NVIM_SINGLE_DOMAIN_REG_FAIL_ACTION_ENUM_UINT8;
enum NAS_MMC_NVIM_REG_FAIL_CAUSE_ENUM
{
    NAS_MMC_NVIM_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN = 14,
    NAS_MMC_NVIM_REG_FAIL_CAUSE_TIMER_TIMEOUT               = 301,                                 /* �ȴ���������ʱ����ʱ */
    NAS_MMC_NVIM_REG_FAIL_CAUSE_BUTT
};
typedef VOS_UINT16 NAS_MMC_NVIM_REG_FAIL_CAUSE_ENUM_UINT16;
enum NAS_MMC_NVIM_REG_DOMAIN_ENUM
{
    NAS_MMC_NVIM_REG_DOMAIN_CS = 1,
    NAS_MMC_NVIM_REG_DOMAIN_PS = 2,                                 /* �ȴ���������ʱ����ʱ */
    NAS_MMC_NVIM_REG_DOMAIN_BUTT
};
typedef VOS_UINT8 NAS_MMC_NVIM_REG_DOMAIN_ENUM_UINT8;

enum NAS_MMC_UCS2_ENUM
{
    NAS_MMC_UCS2_HAS_PREFER                                = 0,
    NAS_MMC_UCS2_NO_PREFER                                 = 1,

    NAS_MMC_UCS2_BUTT
};

typedef VOS_UINT16 NAS_MMC_UCS2_ENUM_UINT16;

enum NV_MS_MODE_ENUM
{
    NV_MS_MODE_CS_ONLY,                                                 /* ��֧��CS�� */
    NV_MS_MODE_PS_ONLY,                                                 /* ��֧��PS�� */
    NV_MS_MODE_CS_PS,                                                   /* CS��PS��֧�� */

    NV_MS_MODE_ANY,                                                     /* ANY,�൱�ڽ�֧��CS�� */

    NV_MS_MODE_BUTT
};
typedef VOS_UINT8 NV_MS_MODE_ENUM_UINT8;


enum NAS_NVIM_CHANGE_REG_REJ_CAUSE_TYPE_ENUM
{
    NAS_NVIM_CHANGE_REG_REJ_CAUSE_TYPE_INACTIVE     = 0,        /* ���ܲ���Ч */
    NAS_NVIM_CHANGE_REG_REJ_CAUSE_TYPE_CS_PS,                   /* �޸�CS+PS�ľܾ�ԭ��ֵ */
    NAS_NVIM_CHANGE_REG_REJ_CAUSE_TYPE_CS_ONLY,                 /* ���޸�CS��ľܾ�ԭ��ֵ */
    NAS_NVIM_CHANGE_REG_REJ_CAUSE_TYPE_PS_ONLY,                 /* ���޸�PS��ľܾ�ԭ��ֵ */
    NAS_NVIM_CHANGE_REG_REJ_CAUSE_TYPE_BUTT
};
typedef VOS_UINT8 NAS_NVIM_CHANGE_REG_REJ_CAUSE_TYPE_ENUM_UINT8;

/* Added by h00313353 for iteration 7, 2015-1-8, begin */
/*****************************************************************************
 ö����    : NAS_NVIM_CHAN_REPEAT_SCAN_ENUM_UINT8
 �ṹ˵��  : Ƶ���ظ���������ö��
 1.��    ��   : 2015��01��08��
   ��    ��   : h00313353
   �޸�����   : ����
*****************************************************************************/
enum NAS_NVIM_CHAN_REPEAT_SCAN
{
    NAS_NVIM_CHAN_SCAN_NORMAL,
    NAS_NVIM_CHAN_REPEAT_SCAN_REACQ_0_1_2_3_4S,
    NAS_NVIM_CHAN_REPEAT_SCAN_PING_5,
    NAS_NVIM_CHAN_REPEAT_SCAN_2_7,

    NAS_NVIM_CHAN_REPEAT_SCAN_BUTT
};
typedef VOS_UINT8 NAS_NVIM_CHAN_REPEAT_SCAN_ENUM_UINT8;
/* Added by h00313353 for iteration 7, 2015-1-8, end */

enum NAS_NVIM_EPDSZID_SUPPORT_TYPE_ENUM
{
    NAS_NVIM_EPDSZID_SUPPORT_TYPE_PDSZID,
    NAS_NVIM_EPDSZID_SUPPORT_TYPE_PDSZID_SID,
    NAS_NVIM_EPDSZID_SUPPORT_TYPE_PDSZID_SID_NID,

    NAS_NVIM_EPDSZID_SUPPORT_TYPE_BUTT
};
typedef VOS_UINT8 NAS_NVIM_EPDSZID_SUPPORT_TYPE_ENUM_UINT8;


enum NAS_NVIM_LC_RAT_COMBINED_ENUM
{
    NAS_NVIM_LC_RAT_COMBINED_GUL,
    NAS_NVIM_LC_RAT_COMBINED_CL,

    NAS_NVIM_LC_RAT_COMBINED_BUTT
};
typedef VOS_UINT8 NAS_NVIM_LC_RAT_COMBINED_ENUM_UINT8;


enum CNAS_NVIM_1X_NEG_PREF_SYS_CMP_TYPE_ENUM
{
    CNAS_NVIM_1X_NEG_PREF_SYS_CMP_BAND_CHAN_AMBIGUOUS_MATCH,                /* Band Channel ģ��ƥ�� */
    CNAS_NVIM_1X_NEG_PREF_SYS_CMP_BAND_CHAN_ACCURATE_MATCH,                 /* Band Channel ��ȷƥ��*/
    CNAS_NVIM_1X_NEG_PREF_SYS_CMP_BUTT
};
typedef VOS_UINT8 CNAS_NVIM_1X_NEG_PREF_SYS_CMP_TYPE_ENUM_UINT8;


/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/*****************************************************************************
*                                                                            *
*                           ����������Ϣ�ṹ                                 *
*                                                                            *
******************************************************************************/

typedef struct
{
    VOS_UINT16                          usManualSearchHplmnFlg; /*Range:[0,1]*/
}NAS_MMC_NVIM_MANUAL_SEARCH_HPLMN_FLG_STRU;

typedef struct
{
    VOS_UINT16                          usAutoSearchHplmnFlg; /*Range:[0,3]*/
}NAS_MMC_NVIM_AUTO_SEARCH_HPLMN_FLG_STRU;

/*****************************************************************************
 �ṹ��    : NAS_NVIM_ADD_EHPLMN_WHEN_SRCH_HPLMN_CFG_STRU
 �ṹ˵��  : NV en_NV_Item_Add_EHPLMN_WHEN_SRCH_HPLMN_CFG �Ľṹ�ṹ

  1.��    ��   : 2015��9��30��
    ��    ��   : c00318887
    �޸�����   : �½�����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucActiveFlag;       /* ucActiveFlag �Ƿ񼤻VOS_TRUE:���VOS_FALSE:δ���� */
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
    VOS_UINT8                           ucReserve3;    
}NAS_NVIM_ADD_EHPLMN_WHEN_SRCH_HPLMN_CFG_STRU;
typedef struct
{
    VOS_UINT16                          usEHPlmnSupportFlg; /*Range:[0,1]*/
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}NAS_MMC_NVIM_EHPLMN_SUPPORT_FLG_STRU;
typedef struct
{
    VOS_UINT16                          usStkSteeringOfRoamingSupportFlg; /*Range:[0,1]*/
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}NAS_MMC_NVIM_STK_STEERING_OF_ROAMING_SUPPORT_FLG_STRU;
typedef struct
{
    VOS_UINT8                           ucNvimActiveFlg;                        /* en_NV_Item_Scan_Ctrl_Para NV���Ƿ񼤻VOS_TRUE:���VOS_FALSE:δ���� */
    VOS_UINT8                           ucReserved1;                            /* ���� */
    VOS_UINT8                           ucReserved2;                            /* ���� */
    VOS_UINT8                           ucReserved3;                            /* ���� */
}NVIM_SCAN_CTRL_STRU;


typedef struct
{
    VOS_UINT32                          ulMcc;                                  /* MCC,3 bytes */
    VOS_UINT32                          ulMnc;                                  /* MNC,2 or 3 bytes */
}NAS_NVIM_PLMN_ID_STRU;


typedef struct
{
    NAS_NVIM_PLMN_ID_STRU               stOperatorPlmnId;
    VOS_UINT8                           aucOperatorNameShort[NAS_NVIM_MAX_OPER_SHORT_NAME_LEN];/* ��ǰפ��������Ӫ�̵Ķ����� */
    VOS_UINT8                           aucOperatorNameLong[NAS_NVIM_MAX_OPER_LONG_NAME_LEN];  /* ��ǰפ��������Ӫ�̵ĳ����� */
}NAS_MMC_NVIM_OPERATOR_NAME_INFO_STRU;


typedef struct
{
    VOS_UINT32                          ulBlackPlmnLockNum;                     /* ֧�ֺ������ĸ���,����Ϊ0ʱ��ʾ��֧�ֺ����� */
    NAS_NVIM_PLMN_ID_STRU               astBlackPlmnId[NAS_MML_NVIM_MAX_BLACK_LOCK_PLMN_NUM];
}NAS_MMC_NVIM_OPER_LOCK_BLACKPLMN_STRU;
typedef struct
{
    VOS_UINT8                           ucEnableFlg;                            /* �������Ƿ�� */
    VOS_UINT8                           ucHighPrioRatType;                              /* ����֧�ֵĽ��뼼�� */
    VOS_UINT8                           aucReserve[2];
    NAS_NVIM_PLMN_ID_STRU               stHighPrioPlmnId;                       /* ����֧�ֵĸ����ȼ���PLMN ID ,��ʹפ����HPLMN��,��PLMNID�����ȼ�Ҳ�ϸ�*/
    NAS_NVIM_PLMN_ID_STRU               stSimHPlmnId;                           /* SIM����HPLMN ID */
}NAS_MMC_NVIM_AIS_ROAMING_CFG_STRU;


typedef struct
{
    VOS_UINT8                           ucAutoReselActiveFlg;                   /* �Ƿ�����LTE�������α��:VOS_TRUE ��ʾ����LTE�������� VOS_FALSE ��ʾ��ֹLTE�������� */
    VOS_UINT8                           ucReserve;
}NAS_MMC_NVIM_USER_AUTO_RESEL_CFG_STRU;
typedef struct
{
    VOS_UINT8                            ucStatus;        /* NV��Ч��־, 1: ��Ч��0����Ч */
	VOS_UINT8                            ucReserved;      /* ���ֽڶ��� */
    VOS_UINT16                           usPrioHplmnAct;      /*���Ƶ����Ƚ��뼼��*/
}NAS_MMC_NVIM_PRIO_HPLMNACT_CFG_STRU;


typedef struct
{
    VOS_UINT32                          ulFirstSearchTimeLen;                   /* available timer��ʱ����һ�ε�ʱ�� */
    VOS_UINT32                          ulFirstSearchTimeCount;                 /* available timer��ʱ����һ�εĴ��� */
    VOS_UINT32                          ulDeepSearchTimeLen;                    /* available timer��ʱ����˯��ʱ�� */
    VOS_UINT32                          ulDeepSearchTimeCount;
}NAS_MMC_NVIM_AVAIL_TIMER_CFG_STRU;
typedef struct
{
    VOS_UINT32                          ulNvActiveFlg;                          /* ���Ƶ�ǰNV�Ƿ�ʹ�� */
    VOS_UINT32                          ulT3212StartSceneCtrlBitMask;           /* BIT0~BIT31,���ڿ�����·ʧ�ܺ�����T3212ʱ���Ƿ�ʹ�õ�ǰNV���õ�ʱ�� */
    VOS_UINT32                          ulT3212Phase1TimeLen;                   /* t3212��ʱ����1�׶ε�ʱ��,��λΪs */
    VOS_UINT32                          ulT3212Phase1Count;                     /* t3212��ʱ����1�׶εĴ��� */
    VOS_UINT32                          ulT3212Phase2TimeLen;                   /* t3212��ʱ����2�׶ε�ʱ��,��λΪs  */
    VOS_UINT32                          ulT3212Phase2Count;                     /* t3212��ʱ����2�׶εĴ��� */
}NAS_MMC_NVIM_T3212_TIMER_CFG_STRU;


typedef struct
{
    VOS_UINT32                          ulWhitePlmnLockNum;                     /* ֧�ְ������ĸ���,����Ϊ0ʱ��ʾ��֧�ְ����� */
    NAS_NVIM_PLMN_ID_STRU               astWhitePlmnId[NAS_MML_NVIM_MAX_WHITE_LOCK_PLMN_NUM];
}NAS_MMC_NVIM_OPER_LOCK_WHITEPLMN_STRU;
typedef struct
{
    VOS_UINT16                          usSupportFlg; /*Range:[0,1]*/
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}NAS_MMC_NVIM_CPHS_SUPPORT_FLG_STRU;
typedef struct
{
    VOS_UINT8                           ucStatus;                               /*�Ƿ񼤻0�����1���� */
    VOS_UINT8                           ucActFlg;
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}NAS_PREVENT_TEST_IMSI_REG_STRU;
/*****************************************************************************
*                                                                            *
*                           ����������Ϣ�ṹ                                 *
*                                                                            *
******************************************************************************/


typedef struct
{
    VOS_UINT8   ucHplmnSearchPowerOn;
    VOS_UINT8   ucReserve1;
    VOS_UINT8   ucReserve2;
    VOS_UINT8   ucReserve3;
}NAS_MMC_NVIM_HPLMN_SEARCH_POWERON_STRU;



typedef struct
{
    VOS_UINT8                           ucTinType;                              /* TIN���� */
    VOS_UINT8                           aucReserve[2];
    VOS_UINT8                           aucImsi[NAS_NVIM_ITEM_MAX_IMSI_LEN];        /* �ϴα����IMSI������ */
}NAS_NVIM_TIN_INFO_STRU;


typedef struct
{
    VOS_UINT32 ulAutoStart;
}NAS_MMA_NVIM_AUTO_START_STRU;



typedef struct
{
    VOS_UINT8                           ucSingleDomainFailPlmnSrchFlag;         /* DT�������󣬵���ע�ᱻ�ܺ���Ҫ�������� */
    VOS_UINT8                           ucReserved;                             /* ����*/
}NAS_MMC_NVIM_SINGLE_DOMAIN_FAIL_CNT_STRU;


typedef struct
{
    VOS_UINT8                           aucPsLocInfo[NAS_NVIM_PS_LOCI_SIM_FILE_LEN];
}NAS_NVIM_PS_LOCI_SIM_FILES_STRU;


typedef struct
{
    VOS_UINT8                          ucStatus;                                /* NV�Ƿ񼤻��־, 0: �����1: ���� */
    VOS_UINT8                          ucGeaSupportCtrl;                        /* �ն�����:GPRS GEA�㷨֧�ֿ��� */
}NAS_MMC_NVIM_GPRS_GEA_ALG_CTRL_STRU;


typedef struct
{
    VOS_UINT8                           ucNvimActiveFlg;    /* en_NV_Item_Lte_Cs_Service_Config NV���Ƿ񼤻VOS_TRUE:���VOS_FALSE:δ���� */
    VOS_UINT8                           ucLteCsServiceCfg;  /* LTE֧�ֵ� cs��ҵ������*/
}NAS_NVIM_LTE_CS_SERVICE_CFG_STRU;


typedef struct
{
    VOS_UINT8                           ucNvimActiveFlg;
    VOS_UINT8                           ucWaitSysinfoTimeLen;
}NAS_MMC_NVIM_HO_WAIT_SYSINFO_TIMER_CFG_STRU;




typedef struct
{
    VOS_UINT8                           ucLteRoamAllowedFlg;
    VOS_UINT8                           aucReserve[1];
    VOS_UINT8                           aucRoamEnabledMccList[20];/* �������εĹ������б� */
}NAS_MMC_NVIM_LTE_INTERNATIONAL_ROAM_CFG_STRU;
typedef struct
{
    VOS_UINT8                           ucRoamRplmnflg;
    VOS_UINT8                           aucReserve[3];
    VOS_UINT32                         aucRoamEnabledMccList[5];/* �������εĹ������б� */
}NAS_MMC_NVIM_ROAM_SEARCH_RPLMN_CFG_STRU;
typedef struct
{
    VOS_UINT8                           ucActFlg;
    VOS_UINT8                           aucReserved[3];
}NAS_NVIM_CLOSE_SMS_CAPABILITY_CFG_STRU;

typedef struct
{
    VOS_UINT8                           ucWcdmaPriorityGsmFlg;                  /* H3G��������W����������G*/

    VOS_UINT8                           ucSortAvailalePlmnListRatPrioFlg;    /* �Ƿ�syscfg���ý��뼼�����ȼ�����ߵ����������б��ʶ��1:��; 0:���Ǹ��������簴���������������粻����*/
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}NAS_MMC_NVIM_WCDMA_PRIORITY_GSM_FLG_STRU;


typedef struct
{
    VOS_UINT8                           ucPsOnlyCsServiceSupportFlg;            /* ����������ΪPS ONLYʱ���Ƿ�֧��CS����źͺ���ҵ��(�������г���)*/
    VOS_UINT8                           ucReserved1;                            /* ����*/
    VOS_UINT8                           ucReserved2;                            /* ����*/
    VOS_UINT8                           ucReserved3;                            /* ����*/
}NAS_NVIM_PS_ONLY_CS_SERVICE_SUPPORT_FLG_STRU;


typedef struct
{
    VOS_UINT8                           ucCcbsSupportFlg;                       /* CCBS(��æ�������)ҵ��*/
    VOS_UINT8                           ucReserved1;                            /* ����*/
    VOS_UINT8                           ucReserved2;                            /* ����*/
    VOS_UINT8                           ucReserved3;                            /* ����*/
}NAS_NVIM_CCBS_SUPPORT_FLG_STRU;


typedef struct
{
    VOS_UINT8                           ucNvimActiveFlg;
    VOS_UINT8                           ucCustomMccNum;
    VOS_UINT8                           aucReserve[2];
    VOS_UINT32                          aulCustommMccList[10];                   /* �������εĹ������б� */
}NAS_MMC_NVIM_HPLMN_SEARCH_REGARDLESS_MCC_SUPPORT_STRU;
typedef struct
{
    VOS_UINT8                           ucNvimActiveFlg;
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
}NVIM_ACTING_HPLMN_SUPPORT_FLAG_STRU;


typedef struct
{
    VOS_UINT8                           ucNvimActiveFlg;
    VOS_UINT8                           ucReserved1;                            /* ����*/
    VOS_UINT8                           ucReserved2;                            /* ����*/
    VOS_UINT8                           ucReserved3;                            /* ����*/
}NAS_MMC_NVIM_REG_FAIL_NETWORK_FAILURE_CUSTOM_FLG_STRU;
typedef struct
{
    NAS_MMC_NVIM_REG_FAIL_CAUSE_ENUM_UINT16                 enRegCause;
    NAS_MMC_NVIM_REG_DOMAIN_ENUM_UINT8                      enDomain;
    NAS_MMC_NVIM_SINGLE_DOMAIN_REG_FAIL_ACTION_ENUM_UINT8   enAction;
}NAS_MMC_NVIM_SINGLE_DOMAIN_REG_FAIL_ACTION_STRU;



typedef struct
{
    VOS_UINT8                                               ucActiveFlag;
    VOS_UINT8                                               ucCount;
    VOS_UINT8                                               auReserv[2];
    NAS_MMC_NVIM_SINGLE_DOMAIN_REG_FAIL_ACTION_STRU         astSingleDomainFailActionList[NAS_MML_SINGLE_DOMAIN_FAIL_ACTION_MAX_LIST];
}NAS_MMC_NVIM_SINGLE_DOMAIN_FAIL_ACTION_LIST_STRU;

/*****************************************************************************
 �ṹ��    : NAS_SIM_FORMAT_PLMN_ID
 �ṹ˵��  : Sim PLMN ID�Ĵ洢�ṹ
 1.��    ��   : 2011��5��28��
   ��    ��   : zhoujun 40661
   �޸�����   : �½�
*****************************************************************************/
typedef struct {
    VOS_UINT8                           aucSimPlmn[NAS_SIM_FORMAT_PLMN_LEN];
    VOS_UINT8                           aucReserve[1];
}NAS_SIM_FORMAT_PLMN_ID;


typedef struct
{
    VOS_UINT8                           ucUtranMode;                            /* ��ǰ֧�ֵ�UTRANģʽ */
    VOS_UINT8                           ucReserve;
}NAS_UTRANCTRL_NVIM_UTRAN_MODE_STRU;
typedef struct
{
    VOS_UINT8                           ucUtranSwitchMode;                      /* 0��UTRANģʽΪFDD 1��UTRANģʽΪTDD 2:AUTO SWITCH */
    VOS_UINT8                           ucTdMccListNum;                         /* ֧��TD����Ĺ��ҺŸ��� */
    VOS_UINT8                           ucImsiPlmnListNum;                      /* ����IMS PLMN����UTRANģʽ�Ƿ�AUTO SWITCHʱ����ǰIMSI��PLMN�ڴ��б��еĶ�֧���Զ��л�������̶�ΪWģ */
    VOS_UINT8                           aucReserve[1];

    VOS_UINT32                          aulTdMccList[NAS_UTRANCTRL_MAX_NVIM_CFG_TD_MCC_LIST_NUM];
    NAS_SIM_FORMAT_PLMN_ID              astImsiPlmnList[NAS_UTRANCTRL_MAX_NVIM_CFG_IMSI_PLMN_LIST_NUM];
}NAS_UTRANCTRL_NVIM_UTRAN_MODE_AUTO_SWITCH_STRU;
typedef struct
{
    VOS_UINT8                           ucIsUtranTddCsSmcNeeded;                /* ������3G TDDģʽ���Ƿ���Ҫ����CS SMC��֤���:0-����Ҫ��1-��Ҫ */
    VOS_UINT8                           ucIsUtranTddPsSmcNeeded;                /* ������3G TDDģʽ���Ƿ���Ҫ����PS SMC��֤���:0-����Ҫ��1-��Ҫ */
    VOS_UINT8                           aucReserved[2];                         /* ���� */
}NAS_UTRANCTRL_NVIM_SMC_CTRL_FLAG_STRU;
typedef struct
{
    VOS_UINT8   ucAccBarPlmnSearchFlg;
    VOS_UINT8   aucReserve[3];
}NAS_MMC_NVIM_ACC_BAR_PLMN_SEARCH_FLG_STRU;



typedef struct
{
    VOS_UINT8                           ucActiveFlg;                                          /* ������ʹ�ܱ�־ */
    VOS_UINT8                           ucImsiCheckFlg;                                       /* �Ƿ���IMSI�б�İ�������0:����Ҫ 1:��Ҫ */
    VOS_UINT8                           aucVersion[NAS_MMC_NVIM_MAX_USER_OPLMN_VERSION_LEN];  /* �������õİ汾�� */
    VOS_UINT8                           ucImsiPlmnListNum;                                    /* ���Ƶ�IMSI�б���� */
    VOS_UINT8                           ucOplmnListNum;                                       /* �������õ�Oplmn�ĸ��� */
    NAS_SIM_FORMAT_PLMN_ID              astImsiPlmnList[NAS_MMC_NVIM_MAX_USER_OPLMN_IMSI_NUM];
    VOS_UINT8                           aucOPlmnList[NAS_MMC_NVIM_MAX_USER_CFG_OPLMN_DATA_LEN];/* OPLMN��PDU���ݣ���EFOplmn�ļ�һ�� */
}NAS_MMC_NVIM_USER_CFG_OPLMN_INFO_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_USER_CFG_OPLMN_EXTEND_STRU
 �ṹ˵��  : NAS_MMC_NVIM_USER_CFG_OPLMN_EXTEND_STRU NVIM���е��û����õ�OPLMN
 1.��    ��   : 2013��11��26��
   �޸�����   : ��NV֧�ֵ����OPLMN������չ��256��
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucActiveFlg;                                          /* ������ʹ�ܱ�־ */
    VOS_UINT8                           ucImsiCheckFlg;                                       /* �Ƿ���IMSI�б�İ�������0:����Ҫ 1:��Ҫ */
    VOS_UINT8                           aucVersion[NAS_MMC_NVIM_MAX_USER_OPLMN_VERSION_LEN];  /* �������õİ汾�� */
    VOS_UINT16                          usOplmnListNum;                                       /* �������õ�Oplmn�ĸ��� */
    VOS_UINT8                           ucImsiPlmnListNum;                                    /* ���Ƶ�IMSI�б���� */
    VOS_UINT8                           aucReserve[3];
    NAS_SIM_FORMAT_PLMN_ID              astImsiPlmnList[NAS_MMC_NVIM_MAX_USER_OPLMN_IMSI_NUM];
    VOS_UINT8                           aucOPlmnList[NAS_MMC_NVIM_MAX_USER_CFG_OPLMN_DATA_EXTEND_LEN];/* OPLMN��PDU���ݣ���EFOplmn�ļ�һ�� */
}NAS_MMC_NVIM_USER_CFG_OPLMN_EXTEND_STRU;


/* Added by c00318887 for DPlmn���ݺ����Ƚ���HPLMN, 2015-5-28, begin */
/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_CFG_DPLMN_NPLMN_INFO_STRU
 �ṹ˵��  : en_NV_Item_CMCC_Cfg_Dplmn_Nplmn_Info NVIM
            en_NV_Item_UNICOM_Cfg_Dplmn_Nplmn_Info
            en_NV_Item_CT_Cfg_Dplmn_Nplmn_Info
            �е�DPLMN NPLMN������Ϣ
 1.��    ��   : 2015��5��28��
   ��    ��   : c00318887
   �޸�����   : �����Ż�����DPlmn���ݺ����Ƚ���HPLMN
*****************************************************************************/
typedef struct
{
    VOS_UINT16                         usDplmnListNum;                                       /* �������õ�Dplmn�ĸ��� */
    VOS_UINT16                         usNplmnListNum;                                       /* �������õ�Nplmn�ĸ��� */

    /* DPLMN����,ÿ7���ֽڴ���һ��dplmn��Ϣ����1-3���ֽ�Ϊsim����ʽplmn id��
       ��4-5�ֽ�Ϊ֧�ֵĽ��뼼��(0x8000Ϊ֧��w��0x4000Ϊ֧��lte��0x0080Ϊ֧��gsm)��
       ��6�ֽ�Ϊ����Ϣ:1(cs��ע��ɹ�)��2(ps��ע��ɹ�)��3(cs ps��ע��ɹ�)
       ��7ֱ��ΪԤ�ñ�ʾ��Ϣ: 1(Ԥ��Dplmn), 0(��ѧϰ����DPLMN) */
    VOS_UINT8                          aucDPlmnList[NAS_MMC_NVIM_MAX_CFG_DPLMN_DATA_LEN];

    /* NPLMN����,ÿ7���ֽڴ���һ��nplmn��Ϣ����1-3���ֽ�Ϊsim����ʽplmn id��
       ��4-5�ֽ�Ϊ֧�ֵĽ��뼼��(0x8000Ϊ֧��w��0x4000Ϊ֧��lte��0x0080Ϊ֧��gsm)��
       ��6�ֽ�Ϊ����Ϣ:1(cs��ע��ɹ�)��2(ps��ע��ɹ�)��3(cs ps��ע��ɹ�)
       ��7ֱ��ΪԤ�ñ�ʾ��Ϣ: 1(Ԥ��nplmn), 0(��ѧϰ����nplmn) */
    VOS_UINT8                          aucNPlmnList[NAS_MMC_NVIM_MAX_CFG_NPLMN_DATA_LEN];/* NPLMN����*/
}NAS_MMC_NVIM_CFG_DPLMN_NPLMN_INFO_STRU;
typedef struct
{
    VOS_UINT16                         usDplmnListNum;                                       /* �������õ�Dplmn�ĸ��� */
    VOS_UINT16                         usNplmnListNum;                                       /* �������õ�Nplmn�ĸ��� */

    /* DPLMN����,ÿ6���ֽڴ���һ��dplmn��Ϣ����1-3���ֽ�Ϊsim����ʽplmn id��
       ��4-5�ֽ�Ϊ֧�ֵĽ��뼼��(0x8000Ϊ֧��w��0x4000Ϊ֧��lte��0x0080Ϊ֧��gsm)����6�ֽ�Ϊ����Ϣ:1(cs��ע��ɹ�)��2(ps��ע��ɹ�)��3(cs ps��ע��ɹ�)*/
    VOS_UINT8                          aucDPlmnList[NAS_MMC_NVIM_MAX_CFG_DPLMN_DATA_EXTEND_LEN];

    /* NPLMN����,ÿ6���ֽڴ���һ��nplmn��Ϣ����1-3���ֽ�Ϊsim����ʽplmn id��
       ��4-5�ֽ�Ϊ֧�ֵĽ��뼼��(0x8000Ϊ֧��w��0x4000Ϊ֧��lte��0x0080Ϊ֧��gsm)����6�ֽ�Ϊ����Ϣ:1(cs��ע��ɹ�)��2(ps��ע��ɹ�)��3(cs ps��ע��ɹ�)*/
    VOS_UINT8                          aucNPlmnList[NAS_MMC_NVIM_MAX_CFG_NPLMN_DATA_EXTEND_LEN];/* NPLMN����*/
}NAS_MMC_NVIM_CFG_DPLMN_NPLMN_INFO_OLD_STRU;
/* Added by c00318887 for DPlmn���ݺ����Ƚ���HPLMN, 2015-5-28, end */


typedef struct
{
    VOS_UINT16                         usCfgDplmnNplmnFlag;
    VOS_UINT8                          ucCMCCHplmnNum;
    VOS_UINT8                          aucCMCCHplmnList[NAS_MMC_NVIM_MAX_CFG_HPLMN_NUM];
    VOS_UINT8                          ucUNICOMHplmnNum;
    VOS_UINT8                          aucUNICOMHplmnList[NAS_MMC_NVIM_MAX_CFG_HPLMN_NUM];
    VOS_UINT8                          ucCTHplmnNum;
    VOS_UINT8                          aucCTHplmnList[NAS_MMC_NVIM_MAX_CFG_HPLMN_NUM];
    VOS_UINT8                          aucReserve[3];
}NAS_MMC_NVIM_CFG_DPLMN_NPLMN_FLAG_STRU;



typedef struct
{
    VOS_UINT8                           ucImsiPlmnListNum;                      /* ���Ƶ�IMSI�б���� */
    VOS_UINT8                           ucEhplmnListNum;                        /* �û����õ�EHplmn�ĸ��� */
    VOS_UINT8                           aucReserve[2];
    NAS_SIM_FORMAT_PLMN_ID              astImsiPlmnList[NAS_MMC_NVIM_MAX_USER_CFG_IMSI_PLMN_NUM];
    NAS_SIM_FORMAT_PLMN_ID              astEhPlmnList[NAS_MMC_NVIM_MAX_USER_CFG_EHPLMN_NUM];
}NAS_MMC_NVIM_USER_CFG_EHPLMN_INFO_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_USER_CFG_EXT_EHPLMN_INFO_STRU
 �ṹ˵��  : en_NV_Item_User_Cfg_Ehplmn NVIM���е��û����õ������Ehplmn List��
 1.��    ��   : 2014��12��19��
   ��    ��   : wx270776
   �޸�����   : �����ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                ulNvimEhplmnNum;
    NAS_MMC_NVIM_USER_CFG_EHPLMN_INFO_STRU    astNvimEhplmnInfo[NAS_MMC_NVIM_MAX_USER_CFG_EXT_EHPLMN_NUM];
}NAS_MMC_NVIM_USER_CFG_EXT_EHPLMN_INFO_STRU;


typedef struct
{
    VOS_UINT32                          ulMcc;                                  /* MCC,3 bytes */
    VOS_UINT32                          ulMnc;                                  /* MNC,2 or 3 bytes */
    VOS_UINT8                           enRat;
    VOS_UINT8                           aucReserve[3];
}NAS_MMC_NVIM_PLMN_WITH_RAT_STRU;



typedef struct
{
    VOS_UINT32                          ulDisabledRatPlmnNum;                   /* ֧�ֽ�ֹ���뼼����PLMN����,����Ϊ0��ʾ��֧�ָ����� */

    NAS_MMC_NVIM_PLMN_WITH_RAT_STRU     astDisabledRatPlmnId[NAS_MML_NVIM_MAX_DISABLED_RAT_PLMN_NUM];/* ��ֹ���뼼����PLMN��RAT��Ϣ */

}NAS_MMC_NVIM_DISABLED_RAT_PLMN_INFO_STRU;


enum NAS_MMC_NVIM_RAT_FORBIDDEN_LIST_SWITCH_FLAG_ENUM
{
    NAS_MMC_NVIM_RAT_FORBIDDEN_LIST_SWITCH_INACTIVE                   = 0,           /* ����δ���� */
    NAS_MMC_NVIM_RAT_FORBIDDEN_LIST_SWITCH_BLACK                      = 1,           /* �������������� */
    NAS_MMC_NVIM_RAT_FORBIDDEN_LIST_SWITCH_WHITE                      = 2,           /* �������������� */
    NAS_MMC_NVIM_RAT_FORBIDDEN_LIST_SWITCH_BUTT
};
typedef VOS_UINT8 NAS_MMC_NVIM_RAT_FORBIDDEN_LIST_SWITCH_FLAG_ENUM_UINT8;
enum NAS_MMC_NVIM_PLATFORM_SUPPORT_RAT_ENUM
{
    NAS_MMC_NVIM_PLATFORM_SUPPORT_RAT_GERAN                   = 0,           /* GERAN */
    NAS_MMC_NVIM_PLATFORM_SUPPORT_RAT_UTRAN                   = 1,           /* UTRAN����WCDMA/TDS-CDMA */
    NAS_MMC_NVIM_PLATFORM_SUPPORT_RAT_EUTRAN                  = 2,           /* E-UTRAN */
    NAS_MMC_NVIM_PLATFORM_SUPPORT_RAT_BUTT
};
typedef VOS_UINT8 NAS_MMC_NVIM_PLATFORM_SUPPORT_RAT_ENUM_UINT8;
enum NAS_MSCC_NVIM_SYS_PRIORITY_CLASS_ENUM
{
    NAS_MSCC_NVIM_SYS_PRI_CLASS_HOME             = 0,    /* home or ehome plmn */
    NAS_MSCC_NVIM_SYS_PRI_CLASS_PREF             = 1,    /* UPLMN or OPLMN */
    NAS_MSCC_NVIM_SYS_PRI_CLASS_ANY              = 2,    /* Acceptable PLMN */
    NAS_MSCC_NVIM_SYS_PRI_CLASS_BUTT
};
typedef VOS_UINT8 NAS_MSCC_NVIM_SYS_PRI_CLASS_ENUM_UINT8;
typedef struct
{
    NAS_MMC_NVIM_RAT_FORBIDDEN_LIST_SWITCH_FLAG_ENUM_UINT8  enSwitchFlag;                                         /*�����Ƿ���Ч�����ܵ�����  */
    VOS_UINT8                                               ucImsiListNum;                                        /*������Ч��SIM����Ŀ(������/������)  */
    VOS_UINT8                                               ucForbidRatNum;                                       /*��ֹRAT����Ŀ  */
    VOS_UINT8                                               aucReserve[1];
    NAS_SIM_FORMAT_PLMN_ID                                  astImsiList[NAS_NVIM_MAX_IMSI_FORBIDDEN_LIST_NUM];        /* SIM���б� (������/������) */
    NAS_MMC_NVIM_PLATFORM_SUPPORT_RAT_ENUM_UINT8            aenForbidRatList[NAS_NVIM_MAX_RAT_FORBIDDEN_LIST_NUM];    /*��ֹ�Ľ��뼼��  */
}NAS_MMC_NVIM_RAT_FORBIDDEN_LIST_STRU;
typedef struct
{
    VOS_UINT8                           ucCsfbEmgCallLaiChgLauFirstFlg;
    VOS_UINT8                           aucRserved[1];
}NAS_MMC_NVIM_CSFB_EMG_CALL_LAI_CHG_LAU_FIRST_CFG_STRU;

typedef struct
{
    VOS_UINT8                           ucPlmnExactlyCompareFlag;
    VOS_UINT8                           aucRsv[3];                         /* ����*/
}NAS_MMC_NVIM_PLMN_EXACTLY_COMPARE_FLAG_STRU;
typedef struct
{
    VOS_UINT8                           ucHplmnRegisterCtrlFlg;                 /* HPLMNע����Ʊ�� */
    VOS_UINT8                           aucRsv[3];                              /* ���� */
}NAS_MMC_NVIM_HPLMN_REGISTER_CTRL_FLAG_STRU;

typedef struct
{
    VOS_UINT8                                               ucSignThreshold;    /* �źű仯����,��RSSI�仯������ֵ��
                                                                                  �������Ҫ�����ϱ��ź�������ȡֵ0��ʾ����㰴Ĭ��ֵ���� */
    VOS_UINT8                                               ucMinRptTimerInterval;     /* ����ϱ���ʱ��   */
    VOS_UINT8                                               ucRserved1;
    VOS_UINT8                                               ucRserved2;
} NAS_NVIM_CELL_SIGN_REPORT_CFG_STRU;
typedef struct
{
    VOS_UINT8                           ucH3gCtrlFlg;                           /* H3G���Ʊ�� */
    VOS_UINT8                           aucRsv[3];                              /* ���� */
}NAS_MMC_NVIM_H3G_CTRL_FLAG_STRU;


typedef struct
{
    VOS_UINT16                          usUcs2Customization;
    VOS_UINT8                           ucRserved1;
    VOS_UINT8                           ucRserved2;
}NAS_MMC_NVIM_UCS2_CUSTOMIZATION_STRU;


typedef struct
{
    VOS_UINT16                          usTc1mLength;
    VOS_UINT16                          usTr1mLength;
    VOS_UINT16                          usTr2mLength;
    VOS_UINT16                          usTramLength;
}SMS_NVIM_TIMER_LENGTH_STRU;



typedef struct
{
    VOS_UINT8                           ucStatus;                               /* NV�Ƿ񼤻��־, 0: �����1: ���� */
    VOS_UINT8                           ucStatusRptGeneralControl;        /* ˽�������Ƿ�����״̬�ϱ� 0:���ϱ���1:�ϱ� */
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}NVIM_PRIVATE_CMD_STATUS_RPT_STRU;


typedef struct
{
    VOS_UINT8                           ucStatus;                               /* NV�Ƿ񼤻��־, 0: �����1: ����  */
    VOS_UINT8                           ucSpecialRoamFlg;                         /* Vplmn��Hplmn��ͬ������ʱ,�Ƿ�����ص�Hplmn,1:����0:������ */
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}NAS_MMC_NVIM_SPECIAL_ROAM_STRU;


typedef struct
{
    VOS_UINT16                          usEnhancedHplmnSrchFlg;
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}NAS_MMC_NVIM_ENHANCED_HPLMN_SRCH_FLG_STRU;


typedef struct
{
    VOS_UINT8   ucT305Len;
    VOS_UINT8   ucT308Len;
    VOS_UINT8   aucReserve[2];
}NAS_CC_NVIM_TIMER_LEN_STRU;

/*****************************************************************************
 �ṹ��    : NAS_CC_NVIM_T303_LEN_CFG_STRU
 �ṹ˵��  : NAS_CC_NVIM_T303_LEN_CFG_STRU�ṹen_NV_Item_CC_T303_Len_Cfg
  1.��    ��   : 2015��3��20��
    ��    ��   : wx270776
    �޸�����   : �½��ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucT303ActiveFlag;                       /* �Ƿ���T303��ʱ����0:�رգ�1:������*/
    VOS_UINT8                           ucT303Len;                              /* T303��ʱ��ʱ�� */
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}NAS_CC_NVIM_T303_LEN_CFG_STRU;


typedef struct
{
    VOS_UINT8   ucCmSrvExistTrigPlmnSearch;                                                     /* ҵ�����ʱ�Ƿ񴥷����� */
    VOS_UINT8   ucCmSrvTrigPlmnSearchCauseNum;                                                  /* ����ҵ�����ʱ���������ı���ԭ��ֵ���� */
    VOS_UINT8   ucReserve1;
    VOS_UINT8   ucReserve2;
    VOS_UINT8   aucCmSrvTrigPlmnSearchCause[NAS_NVIM_MAX_LAU_REJ_TRIG_PLMN_SEARCH_CAUSE_NUM];   /* ����ҵ�����ʱ���������ı���ԭ��ֵ */
    VOS_UINT8   aucReserve[NAS_NVIM_MAX_LAU_REJ_TRIG_PLMN_SEARCH_CAUSE_NUM];                    /* Ԥ����ע�ᱻ�ܴ�������ʹ�� */
}NAS_NVIM_LAU_REJ_TRIG_PLMN_SEARCH_CFG_STRU;


typedef struct
{
    VOS_UINT8   ucLauRejCauseNum;
    VOS_UINT8   ucLauRejTimes;
    VOS_UINT8   ucReserve1;
    VOS_UINT8   ucReserve2;
    VOS_UINT8   aucLauRejCause[NAS_NVIM_MAX_REJECT_NO_RETRY_CAUSE_NUM];
}NAS_NVIM_LAU_REJ_NORETRY_WHEN_CM_SRV_EXIST_CFG_STRU;


typedef struct
{
    NAS_NVIM_CHANGE_REG_REJ_CAUSE_TYPE_ENUM_UINT8           enChangeRegRejCauCfg;
    VOS_UINT8   ucPreferredRegRejCau_HPLMN_EHPLMN;             /* HPLMN/EHPLMNʱʹ�õľܾ�ԭ��ֵ */
    VOS_UINT8   ucPreferredRegRejCau_NOT_HPLMN_EHPLMN;         /* ��HPLMN/EHPLMNʱʹ�õľܾ�ԭ��ֵ */
    VOS_UINT8   aucReserve[1];
}NAS_NVIM_CHANGE_REG_REJECT_CAUSE_FLG_STRU;


typedef struct
{
    VOS_UINT8   ucNoRetryRejectCauseNum;
    VOS_UINT8   aucNoRetryRejectCause[NAS_NVIM_MAX_REJECT_NO_RETRY_CAUSE_NUM];
    VOS_UINT8   aucReserve[3];
}NAS_NVIM_ROAMINGREJECT_NORETYR_CFG_STRU;


typedef struct
{
   VOS_UINT8                           ucIgnoreAuthRejFlg;
   VOS_UINT8                           ucMaxAuthRejNo;
   VOS_UINT8                           aucReserved[2];
}NAS_MMC_NVIM_IGNORE_AUTH_REJ_CFG_STRU;


typedef struct
{
    VOS_UINT8 ucStatus;
    VOS_UINT8 ucReserved1;
    VOS_UINT8 aucE5GwMacAddr[18];
}NAS_NV_GWMAC_ADDR_STRU;


typedef struct
{
    VOS_UINT8 aucE5_RoamingWhiteList_Support_Flg[2];
}NAS_NVIM_E5_ROAMING_WHITE_LIST_SUPPORT_FLG_STRU;


typedef struct
{
    VOS_UINT32 ulNDIS_DIALUP_ADDRESS;
}NAS_NVIM_NDIS_DIALUP_ADDRESS_STRU;


typedef struct
{
    VOS_UINT8 ucBreOnTime; /*Range:[0,7]*/
    VOS_UINT8 ucBreOffTime; /*Range:[0,7]*/
    VOS_UINT8 ucBreRiseTime; /*Range:[0,5]*/
    VOS_UINT8 ucBreFallTime; /*Range:[0,5]*/
}NAS_NVIM_NV_BREATH_LED_STR_STRU;


typedef struct
{
VOS_UINT8  aucwlAuthMode[16];
VOS_UINT8  aucBasicEncryptionModes[5];
VOS_UINT8  aucWPAEncryptionModes[5];
VOS_UINT8  aucwlKeys1[27];
VOS_UINT8  aucwlKeys2[27];
VOS_UINT8  aucwlKeys3[27];
VOS_UINT8  aucwlKeys4[27];
VOS_UINT32 ulwlKeyIndex;
VOS_UINT8  aucwlWpaPsk[65];
VOS_UINT8  ucwlWpsEnbl;
VOS_UINT8  ucwlWpsCfg;
VOS_UINT8  ucReserved;
}NAS_NVIM_NV_WIFI_KEY_STRU;


typedef struct
{
VOS_UINT8 aucPRIVersion[32];
VOS_UINT8 aucReserve[32];
}NAS_NVIM_NV_PRI_VERSION_STRU;


typedef struct
{
    VOS_UINT16                          usSysAppConfigType;
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}NAS_NVIM_SYSTEM_APP_CONFIG_STRU;


typedef struct
{
    VOS_UINT8                           aucNetworkCapability[NV_ITEM_NET_CAPABILITY_MAX_SIZE];
}NAS_MMC_NVIM_NETWORK_CAPABILITY_STRU;


typedef struct
{
    VOS_UINT16                          usAutoattachFlag;
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}NAS_NVIM_AUTOATTACH_STRU;


typedef struct
{
    VOS_UINT16                          usSelPlmnMode;
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}NAS_NVIM_SELPLMN_MODE_STRU;


typedef struct
{
    VOS_UINT8                           aucAccessMode[2];
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}NAS_MMA_NVIM_ACCESS_MODE_STRU;


typedef struct
{
    VOS_UINT8                           ucMsClass;
    VOS_UINT8                           ucReserved;
}NAS_NVIM_MS_CLASS_STRU;


typedef struct
{
    VOS_UINT16                          usRfAutoTestFlg;
}NAS_MMA_NVIM_RF_AUTO_TEST_FLAG_STRU;


typedef struct
{
    VOS_UINT8   ucHplmnTimerLen;
    VOS_UINT8   ucReserved1;
    VOS_UINT8   ucReserved2;
    VOS_UINT8   ucReserved3;
}NAS_NVIM_HPLMN_FIRST_TIMER_STRU;


typedef struct
{
    VOS_UINT8   aucSupported3GppRelease[NAS_MMC_NVIM_SUPPORTED_3GPP_RELEASE_SIZE];
}NAS_MMC_NVIM_SUPPORT_3GPP_RELEASE_STRU;


typedef struct
{
    VOS_UINT8   ucValid;
    VOS_UINT8   aucImsi[NAS_MMC_NVIM_MAX_IMSI_LEN];
    VOS_UINT8   ucReserved1;
    VOS_UINT8   ucReserved2;
}NAS_MMC_NVIM_LAST_IMSI_STRU;


typedef struct
{
    VOS_UINT8   aucRoamingBroker[2];
}NAS_MMA_NVIM_ROAMING_BROKER_STRU;


typedef struct
{
    VOS_UINT16  usUseSingleRplmnFlag;
    VOS_UINT8   ucReserved1;
    VOS_UINT8   ucReserved2;
}NAS_MMC_NVIM_USE_SINGLE_RPLMN_STRU;

/* en_NV_Item_EquivalentPlmn 8215 */

typedef struct
{
    VOS_UINT8    ucMcc[NVIM_MAX_MCC_SIZE];
    VOS_UINT8    ucMnc[NVIM_MAX_MNC_SIZE];
}NVIM_PLMN_VALUE_STRU;


typedef struct
{
    VOS_UINT8             ucCount;
    NVIM_PLMN_VALUE_STRU  struPlmnList[NVIM_MAX_EPLMN_NUM];
    VOS_UINT8             aucReserve[3];   /*NV����صĽṹ�壬��4�ֽڷ�ʽ�£����ֶ�����ն�*/
}NVIM_EQUIVALENT_PLMN_LIST_STRU;

/*en_NV_Item_Support_Freqbands 8229*/
/*
NVIM_UE_SUPPORT_FREQ_BAND_STRU�ṹ˵��:
usWcdmaBand��usGsmBand��Bitλ��ʾ�û����õ�Ƶ�Σ�bit1����Ƶ��I,bit2����Ƶ��II,
��������,����λΪ1,��ʾ֧�ָ�Ƶ��.�±��Ǳ���λ��Ƶ�ζ�Ӧ��ϵ:
-------------------------------------------------------------------------------
        bit8       bit7      bit6     bit5    bit4     bit3      bit2     bit1
-------------------------------------------------------------------------------
WCDMA   900(VIII)  2600(VII) 800(VI)  850(V)  1700(IV) 1800(III) 1900(II) 2100(I) oct1
        spare      spare     spare    spare   spare    spare     spare   J1700(IX)oct2
-------------------------------------------------------------------------------
GSMƵ�� 1900(VIII) 1800(VII) E900(VI) R900(V) P900(IV) 850(III)  480(II)  450(I)  oct3
        spare      spare     spare    spare   spare    spare     spare    700(IX) oct4
-------------------------------------------------------------------------------
aucUeSupportWcdmaBand��aucUeSupportGsmBand�������ʾUE֧�ֵ�Ƶ��,���Դ洢˳���
�Ⱥ��ʾƵ������˳��,��0xff��ʾ��Ч.

����:
oct1-oct4�ֱ��ǣ�0x03,0x00,0x7B,0x00
   ������û�����Ƶ��Ϊ��W��WCDMA-I-2100, WCDMA-II-1900
                         G��850(III),P900(IV),R900(V),E900(VI),1800(VII)
oct5-oct16�ֱ���:2,5,1,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff
   �����UE֧��WƵ��I,II,V,����˳����:II,V,I.
oct17-oct28�ֱ���:4,5,8,7,6,3,0xff,0xff,0xff,0xff,0xff,0xff
   �����UE֧��GƵ��III,IV,V,VI,VII,VIII,����˳����:IV,V,VIII,VII,VI,III.
*/

typedef struct
{
    VOS_UINT32                  ulWcdmaBand;
    VOS_UINT32                  ulGsmBand;
    VOS_UINT8                   aucReserved1[12];
    VOS_UINT8                   aucReserved2[12];
    VOS_UINT8                   aucReserved[24];        /* Ϊ��֤nv����һ�±��� */
}NVIM_UE_SUPPORT_FREQ_BAND_STRU;

/*en_NV_Item_Roam_Capa 8266*/

typedef struct
{
    VOS_UINT8                               ucRoamFeatureFlg;                   /*��¼���������Ƿ񼤻�,VOS_FALSE:������,VOS_TRUE:����*/
    VOS_UINT8                               ucRoamCapability;                   /*��¼�û����õ���������*/
    VOS_UINT8                               ucReserve1;
    VOS_UINT8                               ucReserve2;
}NAS_NVIM_ROAM_CFG_INFO_STRU;

/*en_NV_Item_CustomizeService 8271*/

typedef struct
{
    VOS_UINT32                          ulStatus;           /*�Ƿ񼤻0�����1���� */
    VOS_UINT32                          ulCustomizeService; /*�ն�˵������1��byte��Ϊ��û�пն��������4byte����3byte����*/
}NAS_NVIM_CUSTOMIZE_SERVICE_STRU;

/*en_NV_Item_RPlmnWithRat 8275*/

typedef struct
{
    NAS_NVIM_PLMN_ID_STRU               stGRplmn;                               /* G RPLMN��Ϣ */
    NAS_NVIM_PLMN_ID_STRU               stWRplmn;                               /* W RPLMN��Ϣ*/
    VOS_UINT8                           ucLastRplmnRat;                         /* �ϴιػ�ʱפ������Ľ��뼼��0:GSM;1:WCDMA;0xFF:��Чֵ */
    VOS_UINT8                           ucLastRplmnRatEnableFlg;                /* 0:NV δ����; 1:NV���� */
    VOS_UINT8                           aucReserved[2];                          /* ���� */
}NAS_NVIM_RPLMN_WITH_RAT_STRU;
typedef struct
{
    VOS_UINT8                            ucStatus;                              /* 0:NV δ����; 1:NV ���� */
    VOS_UINT8                            ucReserve;                             /* ����δ�� */
    VOS_UINT16                           usSrchHplmnTimerValue;                 /* VPLMN�·��״���HPLMNʱ��,��λ:���� */

}NAS_MMC_NVIM_SEARCH_HPLMN_TIMER_STRU;

/* Added by c00318887 for file refresh��Ҫ����������, 2015-4-28, begin */
/*****************************************************************************
 �ṹ��    : NAS_MML_HIGH_PRIO_PLMN_REFRESH_TRIGGER_BG_SEARCH_CFG_STRU
 �ṹ˵��  : en_NV_Item_HIGH_PRIO_PLMN_REFRESH_TRIGGER_BG_SEARCH_CFG NV��ṹ
 1.��    ��   : 2015��4��28��
   ��    ��   : c00318887
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucTriggerBGSearchFlag;  /* 0: mmc�յ������ȼ�PLMN����ʱ������BG SEARCH; 1:mmc�յ������ȼ�PLMN����ʱ����BG SEARCH */
    VOS_UINT8                           ucReserved;
    VOS_UINT16                          usSearchDelayLen;             /* BG SEARCH Delay ʱ��, ��λ: ��  */
}NAS_MMC_NVIM_HIGH_PRIO_PLMN_REFRESH_TRIGGER_BG_SEARCH_STRU;

/* Added by c00318887 for file refresh��Ҫ����������, 2015-4-28, end */


/*en_NV_Item_EFust_Service_Cfg 8285*/

typedef struct
{
    VOS_UINT8                           ucStatus;                               /* NV���Ƿ񼤻�0��δ���1������ */
    VOS_UINT8                           ucForbidReg2GNetWork;                   /* 0��EFust GSM�����־������ȥʹ�ܡ��������������EFust 27��38������GSM���롣
                                                                                   �������ö�������UE����SIM���е�EFust 27��38λ��ȷ���Ƿ�����GSM���룬
                                                                                   ���EFUST�ļ���ֹ����λ��ͬʱ����Ϊ0�������ֹGSM����ע�ᣬ����GSM���Խ��롣
                                                                                   ע�⣺SIM���в�����EFust 27��38λ����˸ù��ܽ����USIM����Ч��1��EFust GSM�����־������ʹ�� */
    VOS_UINT8                           ucForbidSndMsg;                         /* 0��EFust���ŷ��ͱ�־������ȥʹ�ܡ��������������EFust 10��12������SMS���͡�
                                                                                   1��EFust���ŷ��ͱ�־������ʹ�ܡ�NV���ö�������UE����SIM����EFUST��10��12λ��
                                                                                   ȷ���Ƿ��ֹ���ŷ���,�����ֹ����λ��ͬʱ����Ϊ0�������ֹ����SMS�����򣬶��ſ��Է��͡�*/
    VOS_UINT8                           ucReserved[13];
}NAS_MMC_NVIM_EFUST_SERVICE_CFG_STRU;

/*en_NV_Item_UE_MSCR_VERSION 8289*/

typedef struct
{
    VOS_UINT8                           ucStatus;                               /* NV�Ƿ񼤻��־, 0: �����1: ���� */
    VOS_UINT8                           ucUeMscrVersion;                        /* �ն��ϱ���SGSN�汾 */
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}NAS_MMC_NVIM_MSCR_VERSION_STRU;

/*en_NV_Item_UE_SGSNR_VERSION 8290*/

typedef struct
{
    VOS_UINT8                           ucStatus;                               /* NV�Ƿ񼤻��־, 0: �����1: ���� */
    VOS_UINT8                           ucUeSgsnrVersion;                       /* �ն��ϱ���SGSN�汾 */
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}NAS_MMC_NVIM_SGSNR_VERSION_STRU;

/*en_NV_Item_SteeringofRoaming_SUPPORT_CTRL 8292*/

typedef struct
{
    VOS_UINT8                           ucStatus;                               /* NV�Ƿ񼤻��־, 0: �����1: ���� */
    VOS_UINT8                           ucCsRejSearchSupportFlg;                /* vodafone��������������,CS��ʧ���Ĵκ��·���������,VOS_FALSE:��֧��,VOS_TRUE:֧�� */
}NAS_MMC_NVIM_CS_REJ_SEARCH_SUPPORT_STRU;

/*en_NV_Item_Max_Forb_Roam_La 8320*/

typedef struct
{
    VOS_UINT8                           ucMaxForbRoamLaFlg;                     /* NV�����õ�����ֹLA�����Ƿ���Ч: VOS_TRUE:valid;VOS_FALSE:INVALID */
    VOS_UINT8                           ucMaxForbRoamLaNum;                     /* NV�����õ�����ֹLA���� */
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}NAS_MMC_NVIM_MAX_FORB_ROAM_LA_STRU;

/*en_NV_Item_Default_Max_Hplmn_Srch_Peri 8321*/

typedef struct
{
    VOS_UINT8                           ucDefaultMaxHplmnPeriFlg;               /* Ĭ������HPLMN���������Ƿ���Ч��־,VOS_TRUE:valid;VOS_FALSE:INVALID */
    VOS_UINT8                           ucDefaultMaxHplmnTim;                   /* �û����Զ���Ĭ�ϵ�����HPLMN�������� */
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}NAS_MMC_NVIM_DEFAULT_MAX_HPLMN_PERIOD_STRU;

/*en_NV_Item_USSD_Apha_To_Ascii 8327*/
/*����USSDת���ַ���*/

typedef struct
{
    VOS_UINT8                       ucStatus;            /*�Ƿ񼤻0�����1���� */
    VOS_UINT8                       ucAlphaTransMode;    /* �ַ���ת��*/
}NAS_SSA_NVIM_ALPHA_to_ASCII_STRU;

/*en_NV_Item_Register_Fail_Cnt 8338*/

typedef struct
{
    VOS_UINT8                           ucNvActiveFlag;                         /* ��ǰNV���Ƿ񼤻� */
    VOS_UINT8                           ucRegFailCnt;                           /* NV�����õ�ע��ʧ�ܵĴ�����Ĭ��ֵΪ2����ע��ʧ�����κ��������� */
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}NAS_MMC_NVIM_REG_FAIL_CNT_STRU;

/*en_NV_Item_CREG_CGREG_CI_Four_Byte_Rpt 8345*/
/* VDF����: CREG/CGREG����<CI>���Ƿ���4�ֽ��ϱ���NV����ƽṹ�� */

typedef struct
{
    VOS_UINT8                           ucStatus;                        /* 1: NV��Ч��־λ��0����Ч */
    VOS_UINT8                           ucCiBytesRpt;                    /* <CI>���ϱ��ֽ�����־��0��2�ֽ��ϱ�, 1��4�ֽ��ϱ� */
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
}NAS_NV_CREG_CGREG_CI_FOUR_BYTE_RPT_STRU;


typedef struct
{
    VOS_UINT8                           ucEnableFlg;                            /* ���ű����Ƿ�ʹ�� VOS-TRUE:���ű���֧�� VOS_FALSE:���ű��ܲ�֧�� */
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
    VOS_UINT8                           ucReserve3;
}NAS_MMC_NVIM_DAIL_REJECT_CFG_STRU;

/* en_NV_Item_NDIS_DHCP_DEF_LEASE_TIME 8344 */
typedef struct
{
    VOS_UINT32                          ulDhcpLeaseHour;    /*Range:[0x1,0x2250]*/
}NDIS_NV_DHCP_LEASE_HOUR_STRU;

typedef struct
{
    VOS_UINT32                          ulIpv6Mtu;          /*Range:[1280,65535]*/
}NDIS_NV_IPV6_MTU_STRU;


typedef struct
{
    VOS_UINT8                           ucStatus;
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
}NAS_NVIM_CCALLSTATE_RPT_STATUS_STRU;


typedef struct
{
   VOS_UINT8                            ucPlmnExactlyCompareFlag;               /* PLMN�Ƚ��Ƿ���о�ȷ�Ƚϵķ�ʽ�ı�� */
   VOS_UINT8                            aucRsv[3];                              /* ����λ */
}NVIM_PLMN_EXACTLY_COMPARE_FLAG_STRU;


enum PLATFORM_RAT_TYPE_ENUM
{
    PLATFORM_RAT_GSM,                                                       /*GSM���뼼�� */
    PLATFORM_RAT_WCDMA,                                                     /* WCDMA���뼼�� */
    PLATFORM_RAT_LTE,                                                       /* LTE���뼼�� */
    PLATFORM_RAT_TDS,                                                       /* TDS���뼼�� */
    PLATFORM_RAT_1X,                                                        /* CDMA-1X���뼼�� */
    PLATFORM_RAT_HRPD,                                                      /* CDMA-EV_DO���뼼�� */

    PLATFORM_RAT_BUTT
};
typedef VOS_UINT16 PLATFORM_RAT_TYPE_ENUM_UINT16;

#define PLATFORM_MAX_RAT_NUM            (7)                                    /* ���뼼�����ֵ */

typedef struct
{
    VOS_UINT16                           usRatNum;                              /* ���뼼������Ŀ*/
    PLATFORM_RAT_TYPE_ENUM_UINT16        aenRatList[PLATFORM_MAX_RAT_NUM];  /* ���뼼�� */
}PLATAFORM_RAT_CAPABILITY_STRU;

/*en_NV_Item_Rplmn 8216*/

typedef struct
{
    VOS_UINT8                           aucRplmnInfo[56];
}NAS_NVIM_RPLMN_INFO_STRU;


typedef struct
{
    VOS_UINT8                           ucSvlteSupportFlag;                     /* SVLTE�����Ƿ�֧��:0-��֧�֣�1-֧�� */
    VOS_UINT8                           aucReserved[3];                         /* ���� */
}SVLTE_SUPPORT_FLAG_STRU;



typedef struct
{
    VOS_UINT8                           ucNvimActiveFlag;                       /* 0: nv��δ���1:nv��� */
    VOS_UINT8                           ucCsPsMode1EnableLteTimerLen;           /* 1)cs ps mode1 L����ע��eps only�ɹ�cs����#16/#17/#22������������disable lteʱ����enable lte��ʱ��ʱ��
                                                                                   2)cs ps mode1 L����ע��cs eps��ʧ��ԭ��ֵother cause ������������disable lte����enable lte��ʱ��ʱ��,��λ:���ӣ� nv���ʱ���Ϊ0Ĭ��54���� */
    VOS_UINT8                           ucCsfbEmgCallEnableLteTimerLen;         /* L�½��������޷�����csfb��gu��ͨ��������gu����disable lte����enable lte��ʱ��ʱ������λ:���ӣ� nv���ʱ���Ϊ0Ĭ��5���� */

    /* ����ԭ��ֵΪ#16��#17��#18������ע��ɹ���Additional Update Result IE��Ϣ��
    ָʾSMS Only��CSFB Not Preferred��Ҫdisable lteʱ�����Э��汾���ڵ���R11��
    ���ñ��ܾ���PLMN��RAT��¼�ڽ�ֹ���뼼�������б��еĳͷ�ʱ�䣬���Ϊ0xFF��ʾ���óͷ�
    ��λ:���� */
    VOS_UINT8                           ucLteVoiceNotAvailPlmnForbiddenPeriod;
}NAS_MMC_NVIM_ENABLE_LTE_TIMER_LEN_STRU;



typedef struct
{
    VOS_UINT8                                               ucIsrSupport;       /* ISR ???? */
    VOS_UINT8                                               ucReserve1;
} NAS_NVIM_ISR_CFG_STRU;
typedef struct
{
    VOS_UINT8                           ucIsRauNeedFollowOnCsfbMtFlg;           /* Csfb mt�����У�RAU�Ƿ���Ҫ��follow on���:0-����Ҫ��1-��Ҫ */
    VOS_UINT8                           ucIsRauNeedFollowOnCsfbMoFlg;           /* Csfb mo�����У�RAU�Ƿ���Ҫ��follow on���:0-����Ҫ��1-��Ҫ */
    VOS_UINT8                           aucReserved[2];                         /* ���� */
}NAS_MMC_CSFB_RAU_FOLLOW_ON_FLAG_STRU;


typedef struct
{
   VOS_UINT16                           usSolutionMask;/*����ͨ������Modem����Ϣ��������ǿ�͵��������ԣ�Bitλ���Ƹ����������ԣ�bitn=0����n�����Թرգ�bitn=1����n�����Կ�����
                                                         Ŀǰֻ��bit0��bit1 ��Ч��
                                                         BIT0������˫Modem��ͨ����һModem��PLMN��Ϣ����FDD�����Ƿ������Ĳ����Ƿ�������
                                                         BIT1��ͨ��Modem1��GSM�ϱ���L��TDS������Ϣ, Modem0��֧��GSM������£�T/L�������ܹ����ݴ��ݵ�����Ƶ�����������TDS/LTE��
                                                               ���Modem1���ݹ�����������Ϣ�����ڵ�����£�Ҳ��ͨ����ʷƵ��֧��NCELL������������������Ƶ����ucSolution2NcellSearchTimer������
                                                         BIT2~BIT15:Ԥ��*/
   VOS_UINT8                            ucSolution2NcellQuickSearchTimer;       /*����Ƶ������������Ե�һ�׶�ʱ��������λ�룩��*/

   VOS_UINT8                            ucSolution2NcellQuickSearchTimer2;      /* ����Ƶ������������ԵĶ��׶�ʱ��������λ�룩��*/
   VOS_UINT8                            aucAdditonCfg[4];
}NV_DSDA_PLMN_SEARCH_ENHANCED_CFG_STRU;



typedef struct
{
    VOS_UINT8   ucRelFlg;
    VOS_UINT8   ucReserve;
}NV_NAS_GMM_REL_CONN_AFTER_PDP_DEACT_STRU;


typedef struct
{
    VOS_UINT32                          ulWband;                                /* ֧�ֵ�WCDMA����ͨ· */
    VOS_UINT32                          ulWbandExt;                             /* ֧�ֵ�WCDMA����ͨ·��չ�ֶ� */
    VOS_UINT32                          ulGband;                                /* ֧�ֵ�GSM����ͨ· */
}NAS_NVIM_WG_RF_MAIN_BAND_STRU;
typedef struct
{
    VOS_UINT8                           ucImsVoiceInterSysLauEnable;           /* ISR�������ϵͳ��L�任��GU��LAIδ�ı䣬�Ƿ���Ҫǿ��LAU */
    VOS_UINT8                           ucImsVoiceMMEnable;         /* IMS�ƶ��Թ��� NV */
    VOS_UINT8                           aucReserved[2];             /* ���� */
}NAS_MMC_IMS_VOICE_MOBILE_MANAGEMENT;


typedef struct
{
    VOS_UINT8                           ucLDisabledRauUseLInfoFlag;             /* l disabled��rau�Ƿ���Ҫ��l��ȡ��ȫ�����Ļ�gutiӳ����Ϣ��vos_true:��Ҫ��ȡ��vos_false:�����ȡ*/
    VOS_UINT8                           ucReserved[3];
}NAS_MMC_LTE_DISABLED_USE_LTE_INFO_FLAG_STRU;
typedef struct
{
    VOS_UINT8                           ucActiveFlg;                            /* �Ƿ񼤻�� */
    VOS_UINT8                           ucCsOnlyDataServiceSupportFlg;          /* PSע�ᱻ��ֹ����£��Ƿ���������ҵ�񴥷�ע��ı�־ */
}NAS_MML_CS_ONLY_DATA_SERVICE_SUPPORT_FLG_STRU;

typedef struct
{
    VOS_UINT8                           ucActiveFLg;                             /* �ö�ʱ���Ƿ�ʹ�� */                       /* TD��ʼ�����ѵĴ��� */
    VOS_UINT8                           aucRsv[3];
    VOS_UINT32                          ulFirstSearchTimeLen;                   /* high prio rat timer��ʱ����һ�ε�ʱ�� ��λ:�� */
    VOS_UINT32                          ulFirstSearchTimeCount;                 /* high prio rat timer��ʱ����һ��ʱ���������������� */
    VOS_UINT32                          ulNonFirstSearchTimeLen;                /* high prio rat timer��ʱ�����״ε�ʱ�� ��λ:�� */
    VOS_UINT32                          ulRetrySearchTimeLen;                   /* high prio rat �ѱ���ֹ���������������Ե�ʱ�� ��λ:��*/
}NAS_MMC_NVIM_HIGH_PRIO_RAT_HPLMN_TIMER_INFO_STRU;
typedef struct
{
    VOS_UINT8                           ucActiveFLg;                            /* �ö�ʱ���Ƿ�ʹ�� */
    VOS_UINT8                           ucTdThreshold;                          /* TD��ʼ�����ѵĴ��� */
    VOS_UINT8                           aucRsv[2];
    VOS_UINT32                          ulFirstSearchTimeLen;                   /* high prio rat timer��ʱ����һ�ε�ʱ�� ��λ:�� */
    VOS_UINT32                          ulFirstSearchTimeCount;                 /* high prio rat timer��ʱ����һ��ʱ���������������� */
    VOS_UINT32                          ulNonFirstSearchTimeLen;                /* high prio rat timer��ʱ�����״ε�ʱ�� ��λ:�� */
    VOS_UINT32                          ulRetrySearchTimeLen;                   /* high prio rat �ѱ���ֹ���������������Ե�ʱ�� ��λ:��*/
}NAS_MMC_NVIM_HIGH_PRIO_RAT_HPLMN_TIMER_CFG_STRU;



typedef struct
{
    VOS_UINT8                           ucUltraFlashCsfbSupportFLg;                 /* �Ƿ�֧��ultra flash csfb */
    VOS_UINT8                           aucRsv[3];
}NAS_MMC_NVIM_ULTRA_FLASH_CSFB_SUPPORT_FLG_STRU;
typedef struct
{
    VOS_UINT8                           uc3GPP2UplmnNotPrefFlg;                    /* �Ƿ���3GPP2 pref plmn */
    VOS_UINT8                           aucRsv[3];
}NAS_MMC_NVIM_3GPP2_UPLMN_NOT_PREF_STRU;
typedef struct
{
    VOS_UINT8                           ucHighPrioRatPlmnSrchFlg;                  /* �Ƿ��������ȼ����뼼������ */
    VOS_UINT8                           aucReserved1[3];
}NAS_MMC_NVIM_SYSCFG_TRIGGER_PLMN_SEARCH_CFG_STRU;
typedef struct
{
    VOS_UINT32                           ulCsRegEndSessionDelayTime;              /* Lau�ӳ�ʱ������λ:���� */
    VOS_UINT32                           ulPsRegEndSessionDelayTime;              /* Rau�ӳ�ʱ������λ:���� */
    VOS_UINT32                           ulReserve1;
    VOS_UINT32                           ulReserve2;
} NAS_MMC_NVIM_DSDS_END_SESSION_DELAY_STRU;


typedef struct
{
    VOS_UINT16                                              usSid;
    VOS_UINT16                                              usNid;
    VOS_UINT16                                              usBandClass;
    VOS_UINT16                                              usChannel;
}CNAS_NVIM_1X_SYSTEM_STRU;


typedef struct
{
    VOS_UINT8                           ucSysNum;
    VOS_UINT8                           aucReserve[3];
    CNAS_NVIM_1X_SYSTEM_STRU            astSystem[CNAS_NVIM_MAX_1X_MRU_SYS_NUM];
}CNAS_NVIM_1X_MRU_LIST_STRU;



typedef struct
{
    VOS_UINT8                           ucReadNvPrlDirectly;
    VOS_UINT8                           ucReadDefaultPrl;        /* ��ȡDefault Prl */
    VOS_UINT8                           aucReserve[14];
}CNAS_NVIM_TEST_CONFIG_STRU;

/* Added by h00313353 for Iteration 17, 2015-7-2, begin */
/*****************************************************************************
 �ṹ��    : CNAS_NVIM_1X_CALLBACK_CFG_STRU
 �ṹ˵��  : en_Nv_Item_CNAS_XSD_CALLBACK_CFG NV��ṹ
 1.��    ��   : 2015��7��2��
   ��    ��   : h00313353
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulCallBackEnableFlg;
    VOS_UINT32                          ulCallBackModeTimerLen;
} CNAS_NVIM_1X_CALLBACK_CFG_STRU;
/* Added by h00313353 for Iteration 17, 2015-7-2, end */

typedef struct
{
    VOS_UINT8                           ucIsNegSysAdd;
    VOS_UINT8                           aucReserve[15];
}CNAS_NVIM_1X_ADD_AVOID_LIST_CFG_STRU;


typedef struct
{
    CNAS_NVIM_1X_NEG_PREF_SYS_CMP_TYPE_ENUM_UINT8           enNegPrefSysCmpType;
    VOS_UINT8                                               aucReserve[15];
}CNAS_NVIM_1X_NEG_PREF_SYS_CMP_CTRL_STRU;


typedef struct
{
    VOS_UINT8                                               ucIsL3ErrReOrigCount;
    VOS_UINT8                                               aucReserve[15];
}CNAS_NVIM_1X_CALL_NVIM_CFG_STRU;


/*****************************************************************************
 �ṹ��    : CNAS_NVIM_1X_SUPPORT_BANDCLASS_MASK_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �ն�֧�ֵ�Ƶ����������  3601
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulSupportBandclassMask;               /* �ն�֧�ֵ�Ƶ���������룬ÿbit��ʾ�Ƿ�֧�ֶ�Ӧ��Ƶ������������0x00000001��ʾֻ֧��Ƶ��0 */
}CNAS_NVIM_1X_SUPPORT_BANDCLASS_MASK_STRU;

/* Added by x00306642, 2015-8-25, begin */
/*****************************************************************************
 �ṹ��    : CNAS_NVIM_HRPD_SUPPORT_BANDCLASS_MASK_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �ն�֧�ֵ�Ƶ����������  3601
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulSupportBandclassMask;               /* �ն�֧�ֵ�Ƶ���������룬ÿbit��ʾ�Ƿ�֧�ֶ�Ӧ��Ƶ������������0x00000001��ʾֻ֧��Ƶ��0 */
}CNAS_NVIM_HRPD_SUPPORT_BANDCLASS_MASK_STRU;
/* Added by x00306642, 2015-8-25, end */

/*****************************************************************************
�ṹ����    :NAS_MMC_NVIM_ADAPTION_CAUSE_STRU
ʹ��˵��    :�û���������ԭ������ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCnCause;     /* ����ԭ��ֵ */
    VOS_UINT8                           ucHplmnCause;  /* �û�����ƥ��HPLMN��ԭ��ֵ */
    VOS_UINT8                           ucVplmnCause;  /* �û�����ƥ��VPLMN��ԭ��ֵ */
    VOS_UINT8                           aucReserved[1];
}NAS_MMC_NVIM_ADAPTION_CAUSE_STRU;

/*****************************************************************************
�ṹ����    :NAS_MMC_NVIM_CHANGE_NW_CAUSE_CFG_STRU
ʹ��˵��    :en_NV_Item_ChangeNWCause_CFG NV��ṹ
*****************************************************************************/
typedef struct
{
    /* CS��ע������(LU)�ܾ�ԭ��ֵ�滻��Ϣ */
    VOS_UINT8                           ucCsRegCauseNum;
    VOS_UINT8                           aucReserved1[3];
    NAS_MMC_NVIM_ADAPTION_CAUSE_STRU    astCsRegAdaptCause[NAS_MMC_NVIM_MAX_CAUSE_NUM];

    /* PS��ע������(ATTACH/RAU)�ܾ�ԭ��ֵ�滻��Ϣ */
    VOS_UINT8                           ucPsRegCauseNum;
    VOS_UINT8                           aucReserved2[3];
    NAS_MMC_NVIM_ADAPTION_CAUSE_STRU    astPsRegAdaptCause[NAS_MMC_NVIM_MAX_CAUSE_NUM];

    /* ����GPRS Detach ���ܾ̾�ԭ��ֵ�滻��Ϣ */
    VOS_UINT8                           ucDetachCauseNum;
    VOS_UINT8                           aucReserved3[3];
    NAS_MMC_NVIM_ADAPTION_CAUSE_STRU    astDetachAdaptCause[NAS_MMC_NVIM_MAX_CAUSE_NUM];

    /* GMM service request���ܾ̾�ԭ��ֵ�滻��Ϣ */
    VOS_UINT8                           ucPsSerRejCauseNum;
    VOS_UINT8                           aucReserved4[3];
    NAS_MMC_NVIM_ADAPTION_CAUSE_STRU    astPsSerRejAdaptCause[NAS_MMC_NVIM_MAX_CAUSE_NUM];

    /* MM ABORT���ܾ̾�ԭ��ֵ�滻��Ϣ */
    VOS_UINT8                           ucMmAbortCauseNum;
    VOS_UINT8                           aucReserved5[3];
    NAS_MMC_NVIM_ADAPTION_CAUSE_STRU    astMmAbortAdaptCause[NAS_MMC_NVIM_MAX_CAUSE_NUM];

    /* CM Service���ܾ̾�ԭ��ֵ�滻��Ϣ */
    VOS_UINT8                           ucCmSerRejCauseNum;
    VOS_UINT8                           aucReserved6[3];
    NAS_MMC_NVIM_ADAPTION_CAUSE_STRU    astCmSerRejAdaptCause[NAS_MMC_NVIM_MAX_CAUSE_NUM];

    VOS_UINT8                           ucHplmnPsRejCauseChangTo17MaxNum; /* HPLMN PS/EPS��ܾ�ԭ��ֵ�޸�Ϊ#17�������� */
    VOS_UINT8                           ucHplmnCsRejCauseChangTo17MaxNum; /* HPLMN CS��ܾ�ԭ��ֵ�޸�Ϊ#17�������� */
    VOS_UINT8                           ucVplmnPsRejCauseChangTo17MaxNum; /* VPLMN PS/EPS��ܾ�ԭ��ֵ�޸�Ϊ#17�������� */
    VOS_UINT8                           ucVplmnCsRejCauseChangTo17MaxNum; /* VPLMN CS��ܾ�ԭ��ֵ�޸�Ϊ#17�������� */
}NAS_MMC_NVIM_CHANGE_NW_CAUSE_CFG_STRU;


typedef struct
{
    VOS_UINT8                           ucRelPsSignalConFlg;/* �Ƿ�������������������� */

    VOS_UINT8                           ucPdpExistNotStartT3340Flag; /* rau��attach���󲻴�follow on������ظ�attach accept��rau acceptҲ����follow on������pdp�����ĳ����Ƿ���Ҫ����T3340,0:��Ҫ����T3340; 1:����Ҫ���� */
    VOS_UINT8                           aucReserved[2];

    VOS_UINT32                          ulT3340Len;         /* ���õ�GMM T3340��ʱ��,��λ:�� */
}NAS_MMC_NVIM_REL_PS_SIGNAL_CON_CFG_STRU;
typedef struct
{
    VOS_UINT8   ucEnableFlag;/*ʹ�ܿ��� */
    VOS_UINT8   aucReserve[3];
    VOS_UINT32  ulMcc;    /*���ڲ���ʹ��ָ��MCC*/
    VOS_UINT32  ulMnc;    /*���ڲ���ʹ��ָ��MNC*/
}NAS_RABM_NVIM_WCDMA_VOICE_PREFER_STRU;
/*Added by z00306637 for RATRFSWITCH, 2015-01-04, begin*/
/*****************************************************************************
 �ṹ��    : NAS_NV_TRI_MODE_ENABLE_STRU
 �ṹ˵��  : en_NV_Item_TRI_MODE_ENABLE NV��ṹ
 1.��    ��   : 2015��01��04��
 ��    ��   : z00306637
 �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usEnable;                          /* ȫ��ͨ���Կ��� */
    VOS_UINT16                              usReserved;
}NAS_NV_TRI_MODE_ENABLE_STRU;

/*****************************************************************************
 �ṹ��    : NAS_NV_TRI_MODE_FEM_PROFILE_ID_STRU
 �ṹ˵��  : en_NV_Item_TRI_MODE_FEM_PROFILE_ID NV��ṹ
 1.��    ��   : 2015��01��04��
 ��    ��   : z00306637
 �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                              ulProfileId;                        /* ����ʹ�ó���������ǰ�����������µ磨ABB��TCXO��RF���Լ�RFͨ���Ŀ��ơ�
                                                                                   ��AT�����·����á�Ĭ��ֵΪ0��ȡֵ��Χ0-7�� */
    VOS_UINT32                              ulReserved[3];                     /* ������������չʹ�� */
}NAS_NV_TRI_MODE_FEM_PROFILE_ID_STRU;



/*****************************************************************************
�ṹ��    : NAS_NV_MODE_BASIC_PARA_STRU
�ṹ˵��  :
��ӦNVID:

  1.��    ��   : 2014��12��30��
    ��    ��   : z00306637
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usABBSwitch;                       /* ����ABB PLL���صĿ��ơ�0:ABB CH0 1:ABB CH1 2:ABB CH0&CH1���� */
    VOS_UINT16                              usRFSwitch;                        /* ����RFIC��Դ���صĿ��ơ�0:RFICʹ��MIPI0���ƹ��緽ʽ 1��RFICʹ��MIPI1���ƹ��緽ʽ 2��ͬʱ����·��Դ��*/
    VOS_UINT16                              usTCXOSwitch;                      /* 0:TCXO0 1:TCXO1 */
    VOS_UINT16                              usReserved;                        /* ������������չʹ�� */
}NAS_NV_MODE_BASIC_PARA_STRU;

/*****************************************************************************
 �ṹ��    : NV_TRI_MODE_CHAN_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ȫ��ͨͨ���������ò���  (���ܸı�)
*****************************************************************************/
typedef struct
{
    NAS_NV_MODE_BASIC_PARA_STRU            stModeBasicPara[2];                  /* �±�[0]:��ʾGSMģʽ�µ�ǰ�����������µ���ơ�
                                                                                   �±�[1]:��ʾWCDMAģʽ�µ�ǰ�����������µ���ơ�
                                                                                    ע������ʱ����ʹ��WCDMAģʽ�����á�*/
    VOS_UINT32                              ulRfSwitch;                         /* ���ڿ��ƹ��ּ��Ŀ��� */
    VOS_UINT32                              ulGsmRficSel;                       /* ����ģʽ�µ�ǰʹ�õ�ͨ����0��RF0,1��RF1�� */
    VOS_UINT32                              ulGpioCtrl;                         /* gpio */
    VOS_UINT32                              aulReserved[14];                    /* ������������չʹ�� */
}NAS_NV_TRI_MODE_CHAN_PARA_STRU;

/*****************************************************************************
 �ṹ��    : NAS_NV_TRI_MODE_FEM_CHAN_PROFILE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : 8�ֳ�����ͨ������
*****************************************************************************/
typedef struct
{
    NAS_NV_TRI_MODE_CHAN_PARA_STRU          stPara[NAS_NV_TRI_MODE_CHAN_PARA_PROFILE_NUM];  /* ���֧��8������������ */
}NAS_NV_TRI_MODE_FEM_CHAN_PROFILE_STRU;




/*Added by z00306637 for RATRFSWITCH, 2015-01-04, end*/


typedef struct
{
    VOS_UINT8                           ucCsmoSupportedFlg;
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
}NAS_MMC_NVIM_CSMO_SUPPORTED_CFG_STRU;



typedef struct
{
    VOS_UINT8                           ucHplmnInEplmnDisplayHomeFlg;
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
}NAS_MMC_NVIM_ROAM_DISPLAY_CFG_STRU;


typedef struct
{
    VOS_UINT16                          usMtCsfbPagingProcedureLen;
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
}NAS_MMC_NVIM_PROTECT_MT_CSFB_PAGING_PROCEDURE_LEN_STRU;


typedef struct
{
    VOS_UINT8                           ucRoamPlmnSelectionSortFlg;
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
}NAS_MMC_NVIM_ROAM_PLMN_SELECTION_SORT_CFG_STRU;


typedef struct
{
    VOS_UINT8                           ucActiveFlg;                            /* NV���Ƿ񼤻� */
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
    VOS_UINT32                          ulFirstTimerLen;                        /* ��һ�׶�ʱ��,��λ:s */
    VOS_UINT32                          ulSecondTimerLen;                       /* �ڶ��׶�ʱ��,��λ:s */
}NAS_MMC_NVIM_HISTORY_SEARCH_CFG_STRU;
typedef struct
{
    VOS_UINT8                           ucRatOrderNum;                          /* ��ȡ����λ����Ϣ�Ľ��뼼������ */
    VOS_UINT8                           aucRatOrder[NAS_NVIM_MAX_RAT_NUM];      /* ��ȡ����λ����Ϣ�Ľ��뼼�����ȼ� */
}NAS_NVIM_GET_GEO_PRIO_RAT_LIST_STRU;


typedef struct
{
    VOS_UINT8                                               ucActiveFlag;               /* NV���Ƿ񼤻� */
    VOS_UINT8                                               ucGetGeoTimerlen;           /* ��ȡ�����붨ʱ��ʱ������λ���� */
    VOS_UINT8                                               ucReserved1;
    VOS_UINT8                                               ucReserved2;
    VOS_UINT32                                              ulGeoEffectiveTimeLen;      /* ���������Ч��ʱ������λ�Ƿ��� */
    NAS_NVIM_GET_GEO_PRIO_RAT_LIST_STRU                     stGetGeoPrioRatList;        /* ��ȡ����λ����Ϣ�Ľ��뼼�����ȼ��б���Ϣ */
}NAS_NVIM_GET_GEO_CFG_INFO_STRU;


typedef struct
{
    VOS_UINT8                           ucLowPrioAnycellSearchLteFlg;
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
}NAS_NVIM_LOW_PRIO_ANYCELL_SEARCH_LTE_FLG_STRU;


typedef struct
{
    VOS_UINT8                           ucDeleteRplmnFlg;
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
}NAS_NVIM_REFRESH_RPLMN_WHEN_EPLMN_INVALID_CFG_STRU;


typedef struct
{
    VOS_UINT8                                               ucActiveFlag;       /* NV���Ƿ񼤻� */
    VOS_UINT8                                               ucReserved1;
    VOS_UINT8                                               ucReserved2;
    VOS_UINT8                                               ucReserved3;
    VOS_UINT32                                              ulRecordNum;        /* ��¼�Ĵ��� */
}NAS_NVIM_NW_SEARCH_CHR_RECORD_CFG_STRU;


typedef struct
{
    VOS_UINT8                           ucPrlData[CNAS_NVIM_PRL_SIZE];
}CNAS_NVIM_1X_EVDO_PRL_LIST_STRU;

/* Added by h00313353 for iteration 7, 2014-12-31, begin */
/*****************************************************************************
 �ṹ��    : CNAS_NVIM_1X_HOME_SID_NID_STRU
 �ṹ˵��  : HOME_SID_NID�����Ϣ
 1.��    ��   : 2014��12��31��
   ��    ��   : h00313353
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usSid;
    VOS_UINT16                          usNid;
    VOS_UINT16                          usBand;
    VOS_UINT16                          usReserved;
}CNAS_NVIM_1X_HOME_SID_NID_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_NVIM_1X_HOME_SID_NID_LIST_STRU
 �ṹ˵��  : HOME_SID_NID����б���Ϣ
 1.��    ��   : 2014��12��31��
   ��    ��   : h00313353
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSysNum;
    VOS_UINT8                           aucReserve[3];
    CNAS_NVIM_1X_HOME_SID_NID_STRU      astHomeSidNid[CNAS_NVIM_MAX_1X_HOME_SID_NID_NUM];
}CNAS_NVIM_1X_HOME_SID_NID_LIST_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_NVIM_1X_SEARCH_INTERVAL_STRU
 �ṹ˵��  : ɨ��������������Ϣ
 1.��    ��   : 2014��12��31��
   ��    ��   : h00313353
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usTimes;
    VOS_UINT16                          usTimerLen;
}CNAS_NVIM_OOC_TIMER_INFO_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_NVIM_1X_SEARCH_INTERVAL_LIST_STRU
 �ṹ˵��  : ɨ�������������б���Ϣ
 1.��    ��   : 2014��12��31��
   ��    ��   : h00313353
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucMru0SearchTimerLen;
    VOS_UINT8                           ucPhaseNum;
    VOS_UINT8                           aucReserved[2];
    CNAS_NVIM_OOC_TIMER_INFO_STRU       astOocTimerInfo[CNAS_NVIM_MAX_OOC_SCHEDULE_PHASE_NUM];
}CNAS_NVIM_OOC_TIMER_SCHEDULE_INFO_STRU;
/* Added by h00313353 for iteration 7, 2014-12-31, end */
/* Added by h00313353 for iteration 7, 2015-1-8, begin */
/*****************************************************************************
 �ṹ��    : CNAS_NVIM_1X_SEARCH_INTERVAL_LIST_STRU
 �ṹ˵��  : ɨ�������������б���Ϣ
 1.��    ��   : 2015��01��08��
   ��    ��   : h00313353
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucInsertOrigChanFlg;        /* ��ͬ������ǰ�Ƿ������ǰפ��Ƶ�� */
    NAS_NVIM_CHAN_REPEAT_SCAN_ENUM_UINT8                    enChanRepeatScanStrategy;   /*Ƶ���ظ��������� */
    VOS_UINT8                                               aucReserved[2];
}CNAS_NVIM_OOC_REPEAT_SCAN_STRATEGY_INFO_STRU;
/* Added by h00313353 for iteration 7, 2015-1-8, end */

typedef struct
{
    NAS_NVIM_EPDSZID_SUPPORT_TYPE_ENUM_UINT8                ucEpdszidType;  /* EPDSZID֧������ */
    VOS_UINT8                                               ucHatLen;       /* HATʱ������λs */
    VOS_UINT8                                               ucHtLen;        /* HTʱ������λs */
    VOS_UINT8                                               aucReserved[5];
}CNAS_NVIM_1X_EPDSZID_FEATURE_CFG_STRU;

/* Added by H00300778 for CDMA EVDO Iteration 0, 2014-12-11, begin */
/*****************************************************************************
 �ṹ��    : CNAS_NVIM_HRPD_SYSTEM_STRU
 �ṹ˵��  : NV����HRDP�����������BAND��Channel��Ϣ�ṹ
 1.��    ��   : 2014��12��11��
   ��    ��   : h00300778
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                          aucSubnet[CNAS_NVIM_HRPD_SUBNET_LEN];
    VOS_UINT16                         usBandClass;
    VOS_UINT16                         usChannel;
}CNAS_NVIM_HRPD_SYSTEM_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_NVIM_HRPD_MRU_LIST_STRU
 �ṹ˵��  : en_NV_Item_HRPD_MRU_LIST NV��ṹ
 1.��    ��   : 2014��12��11��
   ��    ��   : h00300778
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSysNum;
    VOS_UINT8                           aucRsv[3];
    CNAS_NVIM_HRPD_SYSTEM_STRU          astSystem[CNAS_NVIM_MAX_HRPD_MRU_SYS_NUM];
}CNAS_NVIM_HRPD_MRU_LIST_STRU;


typedef struct
{
    VOS_UINT32                          ulSicValue;
}CNAS_NVIM_1X_LAST_SCI_STRU;
/* Added by H00300778 for CDMA EVDO Iteration 0, 2014-12-11, end */

typedef struct
{
    VOS_UINT8                           ucNvimActiveFlag;                       /* 0: nv��δ���1:nv��� */
    VOS_UINT8                           ucWaitImsVoiceAvailTimerLen;            /* �ȴ�IMS VOICE�Ŀ���ָʾ�Ķ�ʱ��ʱ��,��λΪ�뼶,��Ҫת��Ϊ���� */
    VOS_UINT8                           aucRsv[2];
}NAS_NVIM_WAIT_IMS_VOICE_AVAIL_TIMER_LEN_STRU;
/*****************************************************************************
 Name    : CNAS_NVIM_HRPD_LOC_INFO_STRU
 Description  : Structure for en_NV_Item_HRPD_LOC_INFO
 History     :
  1.Date     : 2015-02-05
    Author   : n00742771
    Modify   : create
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulIsValid;
    VOS_UINT8                           ucLocType;
    VOS_UINT8                           ucLocLen;
    VOS_UINT16                          usSID;
    VOS_UINT16                          usNID;
    VOS_UINT8                           ucPacketZoneID;
    VOS_UINT8                           ucReserve;
}CNAS_NVIM_HRPD_LOC_INFO_STRU;

/*****************************************************************************
 Name    : CNAS_NVIM_HRPD_STORAGE_BLOB_STRU
 Description  : Structure for en_NV_Item_HRPD_STORAGE_BLOB
 History     :
  1.Date     : 2015-02-05
    Author   : n00742771
    Modify   : create
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulIsValid;
    VOS_UINT16                          usStrgBLOBType;
    VOS_UINT8                           ucStrgBLOBLen;
    VOS_UINT8                           aucStorageBLOB[CNAS_NVIM_MAX_STORAGE_BLOB_LEN];
    VOS_UINT8                           aucReserve[2];
}CNAS_NVIM_HRPD_STORAGE_BLOB_STRU;


typedef struct
{
    VOS_UINT8                           ucLteRejCause14Flg;               /* �Ƿ���LTE #14ԭ��ܾ��Ż���0: δ������1:���� */
    VOS_UINT8                           aucReserved[1];
    VOS_UINT16                          usLteRejCause14EnableLteTimerLen; /* LTE #14ԭ��ܾ�ʱ��ͨ��������gu����disable lte����enable lte��ʱ��ʱ������λ:���� */
}NAS_MMC_NVIM_LTE_REJ_CAUSE_14_CFG_STRU;

#if 0
/****************************************************************************
Structure name  :   CNAS_EHSM_RETRY_CONN_EST_NVIM_INFO_STRU
Description     :   Structure for context of the EHSM module
Modify History:
    1)  Date    :   2015-05-21
        Author  :   K00902809
        Modify content :    Create
****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulExpireTimerLen;
    VOS_UINT32                          ulActiveFlag;
    VOS_UINT16                          usMaxNoOfRetry;
    VOS_UINT8                           aucRsv[2];
}CNAS_EHSM_RETRY_CONN_EST_NVIM_INFO_STRU;
#endif

/****************************************************************************
Structure name  :   CNAS_NVIM_EHRPD_PDN_SETUP_RETRY_STRU
Description     :   Structure for context of the EHSM module
Modify History:
    1)  Date    :   2015-05-21
        Author  :   K00902809
        Modify content :    Create
****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulActiveFlag;
    VOS_UINT32                          ulExpireTimerLen;
    VOS_UINT16                          usMaxNoOfRetry;
    VOS_UINT8                           aucRsv[2];
}CNAS_NVIM_EHRPD_PDN_SETUP_RETRY_STRU;


enum NAS_SMS_PS_CONCATENATE_ENUM
{
    NAS_SMS_PS_CONCATENATE_DISABLE      = 0,
    NAS_SMS_PS_CONCATENATE_ENABLE,

    NAS_SMS_PS_CONCATENATE_BUTT
};
typedef VOS_UINT8 NAS_SMS_PS_CONCATENATE_ENUM_UINT8;


typedef struct
{
    NAS_SMS_PS_CONCATENATE_ENUM_UINT8   enSmsConcatenateFlag;
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
} NAS_NV_SMS_PS_CTRL_STRU;

/* Added by h00313353 for SMS Filter Prj, 2015-9-17, begin */
/*****************************************************************************
 �ṹ����  : NAS_NV_SMS_FILTER_CFG_STRU
 �ṹ˵��  : ���Ź���������Ϣ

  1.��    ��   : 2015��09��17��
    ��    ��   : h00313353
    �޸�����   : �����ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSmsFilterEnableFlg;
    VOS_UINT8                           aucReserved[3];
} NAS_NV_SMS_FILTER_CFG_STRU;
/* Added by h00313353 for SMS Filter Prj, 2015-9-17, end */

typedef struct
{

    VOS_UINT8                           ucBsrTimerActiveFlag; /* If the Flag is TRUE, then BSR Timer value is read from NV
                                                                  If FALSE, the BSR timer value is read from SIM */

    VOS_UINT8                           aucReserved[3];

    VOS_UINT32                          ulFirstSearchAvailTimerLen; /* Contains the Available timer length to be used , when the
                                                                    number of successive triggers is less than ulFirstSearchAvailTimerCount */

    VOS_UINT32                          ulFirstSearchAvailTimerCount; /* For the number successive triggers of avaiable timer less
                                                                      than or equal to ulFirstSearchAvailTimerCount , MSCC uses a timer
                                                                      length value of ulFirstSearchAvailTimerLen */

    VOS_UINT32                          ulDeepSearchAvailTimerLen;  /* For the number successive triggers of avaiable timer greater
                                                                    than ulFirstSearchAvailTimerCount , MSCC uses a timer
                                                                    length value of ulDeepSearchAvailTimerLen */

    VOS_UINT32                          ulScanTimerLen; /* Contains the scan timer length */
    VOS_UINT32                          ulBsrTimerLen; /* Contains the BSR Timer length */
    VOS_UINT32                          ulSleepTimerLen; /* Contains the sleep timer length */
}NAS_NVIM_MSCC_SYS_ACQ_TIMER_CFG_STRU;
typedef struct
{
    VOS_UINT32                                              ulMcc;
    VOS_UINT32                                              ulMnc;
    VOS_UINT16                                              usSid;
    VOS_UINT16                                              usNid;

    NAS_MSCC_NVIM_SYS_PRI_CLASS_ENUM_UINT8                  en1xPrioClass;
    NAS_MSCC_NVIM_SYS_PRI_CLASS_ENUM_UINT8                  enAIPrioClass;
    VOS_UINT8                                               aucRsv[2];  /* remain four bytes in future */
}NAS_NVIM_1X_LOC_INFO_STRU;
typedef struct
{
    VOS_UINT32                                              ulMcc;                                  /* MCC,3 bytes */
    VOS_UINT32                                              ulMnc;                                  /* MNC,2 or 3 bytes */
    NAS_MSCC_NVIM_SYS_PRI_CLASS_ENUM_UINT8                  enPrioClass;
    VOS_UINT8                                               aucRsv[3];  /* remain four bytes in future */
}NAS_NVIM_3GPP_LOC_INFO_STRU;
typedef struct
{
    VOS_UINT8                           ucIsLocInfoUsedInSwitchOn;
    NAS_NVIM_LC_RAT_COMBINED_ENUM_UINT8 enSysAcqMode;
    VOS_UINT8                           ucIs1xLocInfoValid;
    VOS_UINT8                           ucIsLteLocInfoValid;
    NAS_NVIM_1X_LOC_INFO_STRU           st1xLocInfo;
    NAS_NVIM_3GPP_LOC_INFO_STRU         st3gppLocInfo;
}NAS_NVIM_MMSS_LAST_LOCATION_INFO_STRU;


typedef struct
{

    VOS_UINT8                                               ucReAcqLteOnHrpdSyncIndFlag; /* The NVIM Flag controls if
                                                                                                       MSCC must search  for LTE Service
                                                                                                       when HSD sends Sync Ind, if LTE
                                                                                                       is preferred */

    VOS_UINT8                                               ucIs1xLocInfoPrefThanLte;  /* The NVIM Flag controls if CDMA 1x
                                                                                                     Loc info is more preferred than LTe
                                                                                                     Loc Info */
    VOS_UINT8                                               aucReserved[2];
    NAS_NVIM_MSCC_SYS_ACQ_TIMER_CFG_STRU                    stMmssSysAcqTimerCfg;  /* Contains the Timer Configuration
                                                                                                for MMSS System Acquire */
}NAS_NVIM_MMSS_SYSTEM_ACQUIRE_CFG_STRU;



typedef struct
{
    VOS_UINT8                           ucMlplMsplActiveFlag;
    VOS_UINT8                           aucRsv[3];
    VOS_UINT16                          usMlplBufSize;
    VOS_UINT16                          usMsplBufSize;
    VOS_UINT8                           aucMlplBuf[NAS_MSCC_NVIM_MLPL_SIZE];
    VOS_UINT8                           aucMsplBuf[NAS_MSCC_NVIM_MSPL_SIZE];
}NAS_MSCC_NVIM_MLPL_MSPL_STRU;


typedef struct
{
    VOS_UINT8                           ucMobTermForNid;
    VOS_UINT8                           ucMobTermForSid;
    VOS_UINT8                           ucMobTermHome;
    VOS_UINT8                           ucRsv;
}CNAS_NVIM_1X_MOB_TERM_STRU;


typedef struct
{
    VOS_UINT8                           ucActiveFlag;           /* NV item is active not not */
    VOS_UINT8                           ucRsv1;
    VOS_UINT16                          usActTimerLen;          /* Session activate timer length, unit is second */
    VOS_UINT8                           ucMaxActCountConnFail;  /* Max session activate count of reason conntion fail */
    VOS_UINT8                           ucMaxActCountOtherFail; /* Max session activate count of reason other fail */
    VOS_UINT8                           ucRsv2;
    VOS_UINT8                           ucRsv3;
}CNAS_HSM_NVIM_SESSION_RETRY_CFG_STRU;

/*****************************************************************************
 Name    : CNAS_HSM_NVIM_SESSION_CTRL_CFG_STRU
 Description  : Structure definition for en_NV_Item_CNAS_HRPD_Session_Ctrl_Cfg
 History     :
  1.Date     : 2015-09-23
    Author   : m00312079
    Modify   : create
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucStartUatiReqAfterSectorIdChgFlg;   /* Ϊ��ͨ��RF���Ժ�CCF2.2.2.8����������NV����
                                                                                          NV��(Ĭ��):���ձ��ֻҪsector ID�����仯������UATI��������
                                                                                          NV�ر�:      �ϸ���Э��C.S0024 7.3.7.1.6.1������ֻ����HO����
                                                                                                       Conn Close��sector ID�����仯������UATI�������� */

    VOS_UINT8                           aucRsv[31];
}CNAS_HSM_NVIM_SESSION_CTRL_CFG_STRU;


typedef struct
{
    VOS_UINT8                           ucIsKeepAliveInfoValid;    /* If TRUE, then the Keep alive paramters are valid */
    VOS_UINT8                           ucRsv1;                    /* for padding */
    VOS_UINT16                          usTsmpClose;               /* stores the TsmpClose value of the last session. Unit is minutes */
    VOS_UINT32                          ulTsmpCloseRemainTime;     /* Stores the time remaining for Tsmpclose minutes to
                                                                               expire. Unit is seconds */
    VOS_UINT32                          aulLastPowerOffSysTime[2]; /* Stores the CDMA system time at last Power Off.
                                                                              Unit is Milliseconds. */
}CNAS_HSM_NVIM_SESSION_KEEP_ALIVE_INFO_STRU;

/* Added by t00323010 for CDMA Iteration 12 2015-6-2 begin */
/*****************************************************************************
 Name    : NAS_NVIM_EHRPD_SUPPORT_FLG_STRU
 Description  : Structure definition for en_Nv_Item_EHRPD_Support_Flg
 History     :
  1.Date     : 2015-06-02
    Author   : t00323010
    Modify   : create
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEhrpdSupportFlg;       /* EHRPD is support or not */
    VOS_UINT8                           ucRsv1;
    VOS_UINT8                           ucRsv2;
    VOS_UINT8                           ucRsv3;
}NAS_NVIM_EHRPD_SUPPORT_FLG_STRU;
/* Added by t00323010 for CDMA Iteration 12 2015-6-2 end */


/* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-8-26, begin */
/*****************************************************************************
 �ṹ��    : NAS_NVIM_PLMN_SEARCH_PHASE_ONE_TOTAL_TIMER_CFG_STRU
 �ṹ˵��  : en_NV_Item_Plmn_Search_Phase_One_Total_Timer_CFG NV��ṹ
  1.��    ��   : 2015��8��26��
    ��    ��   : c00318887
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucActiveFlag;                           /* NV���Ƿ񼤻� */
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
    VOS_UINT32                          ulTotalTimeLen;                         /* ��һ�׶�������ʱ��,��λ:s */
}NAS_NVIM_PLMN_SEARCH_PHASE_ONE_TOTAL_TIMER_CFG_STRU;

/* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-8-26, end */

/* Added by z00359541 for CS REG FAIL FORB LA, 2015-9-23, begin */
/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_CUSTOMIZED_FORB_LA_CFG_STRU
 �ṹ˵��  : en_NV_Item_CS_REG_FAIL_CAUSE_FORB_LA_TIME_CFG NV��ṹ
  1.��    ��   : 2015��9��23��
    ��    ��   : z00359541
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usRegFailCauseNum;                      /* ֧�ֵ�ע��ʧ��ԭ��ֵ����,����Ϊ0��ʾ��֧�ָ����� */
    VOS_UINT16                          usForbLaTimeLen;                        /* ��ֹLAʱ��,��λ:s */
    VOS_UINT16                          usPunishTimeLen;                        /* ��ƹ�һ�������Ҫ�ͷ���ʱ�� */
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT16                          ausRegFailCauseList[NAS_MML_NVIM_MAX_REG_FAIL_CAUSE_NUM];
}NAS_MMC_NVIM_CUSTOMIZED_FORB_LA_CFG_STRU;
/* Added by z00359541 for CS REG FAIL FORB LA, 2015-9-23, end */

/* Added by y00307564 for CDMA Iteration 12 2015-6-3 begin */

enum CNAS_NVIM_HRPD_SESSION_STATUS_ENUM
{
    CNAS_NVIM_HRPD_SESSION_STATUS_CLOSE,
    CNAS_NVIM_HRPD_SESSION_STATUS_OPEN,
    CNAS_NVIM_HRPD_SESSION_STATUS_BUTT
};
typedef VOS_UINT8 CNAS_NVIM_HRPD_SESSION_STATUS_ENUM_UINT8;


enum CNAS_NVIM_HRPD_SESSION_TYPE_ENUM
{
    CNAS_NVIM_HRPD_SESSION_TYPE_HRPD,
    CNAS_NVIM_HRPD_SESSION_TYPE_EHRPD,
    CNAS_NVIM_HRPD_SESSION_TYPE_BUTT
};
typedef VOS_UINT8 CNAS_NVIM_HRPD_SESSION_TYPE_ENUM_UINT8;


enum CNAS_NVIM_HARDWARE_ID_TYPE_ENUM
{
    CNAS_NVIM_HARDWARE_ID_TYPE_MEID                    = 0x0000FFFF,
    CNAS_NVIM_HARDWARE_ID_TYPE_ESN                     = 0x00010000,
    CNAS_NVIM_HARDWARE_ID_TYPE_NULL                    = 0x00FFFFFF,
    CNAS_NVIM_HARDWARE_ID_TYPE_BUTT
};
typedef VOS_UINT32 CNAS_NVIM_HARDWARE_ID_TYPE_ENUM_UINT32;


enum CNAS_NVIM_HARDWARE_ID_SRC_TYPE_ENUM
{
    CNAS_NVIM_HARDWARE_ID_SRC_TYPE_NVIM,
    CNAS_NVIM_HARDWARE_ID_SRC_TYPE_RAND,
    CNAS_NVIM_HARDWARE_ID_SRC_TYPE_UIM,
    CNAS_NVIM_HARDWARE_ID_SRC_TYPE_BUTT
};
typedef VOS_UINT32 CNAS_NVIM_HARDWARE_ID_SRC_TYPE_ENUM_UINT32;



typedef struct
{
    VOS_UINT8                           aucCurUATI[CNAS_NVIM_UATI_OCTET_LENGTH];
    VOS_UINT8                           ucUATIColorCode;
    VOS_UINT8                           ucUATISubnetMask;
    VOS_UINT8                           ucUATIAssignMsgSeq;
    VOS_UINT8                           ucRsv2;
}CNAS_NVIM_HRPD_UATI_INFO_STRU;

/*****************************************************************************
 Structure Name    : CNAS_NVIM_HARDWARE_ID_INFO_STRU
 Description       : the HARDWARE id info
 History     :
  1.Date     : 2015-06-03
    Author   : y00307564
    Modify   : create

*****************************************************************************/
typedef struct
{
    CNAS_NVIM_HARDWARE_ID_TYPE_ENUM_UINT32                  enHwidType;
    CNAS_NVIM_HARDWARE_ID_SRC_TYPE_ENUM_UINT32              enHwidSrcType;
    VOS_UINT32                                              ulEsn;                                /* 32-bit */
    VOS_UINT8                                               aucMeId[CNAS_NVIM_MEID_OCTET_NUM];    /* 56-bit */
    VOS_UINT8                                               ucRsv1;
}CNAS_NVIM_HARDWARE_ID_INFO_STRU;

/*****************************************************************************
 Structure Name    : CNAS_NVIM_LOC_INFO_STRU
 Description       : Location info
 1.Date            : 29/05/2015
   Author          : m00312079
   Modification    : Create

*****************************************************************************/
typedef struct
{
    VOS_INT32                           lLongitude;
    VOS_INT32                           lLatitude;
}CNAS_NVIM_LOC_INFO_STRU;

/*****************************************************************************
 Name    : CNAS_NVIM_HRPD_SESSION_INFO_STRU
 Description  : Structure definition for en_Nv_Item_HRPD_Session_Info
 History     :
  1.Date     : 2015-06-03
    Author   : y00307564
    Modify   : create
*****************************************************************************/
typedef struct
{
    CNAS_NVIM_HRPD_SESSION_STATUS_ENUM_UINT8                enSessionStatus;
    CNAS_NVIM_HRPD_SESSION_TYPE_ENUM_UINT8                  enSessionType;
    VOS_UINT8                                               aucIccid[CNAS_NVIM_ICCID_OCTET_LEN];
    CNAS_NVIM_HRPD_UATI_INFO_STRU                           stUatiInfo;
    CNAS_NVIM_LOC_INFO_STRU                                 stLocInfo;
    CNAS_NVIM_HARDWARE_ID_INFO_STRU                         stHwid;
}CNAS_NVIM_HRPD_SESSION_INFO_STRU;
/* Added by y00307564 for CDMA Iteration 12 2015-6-3 end */

/*****************************************************************************
 Name    : CNAS_NVIM_HRPD_SESSION_INFO_EX_STRU
 Description  : Structure definition for en_Nv_Item_HRPD_Session_Info_Ex
 History     :
  1.Date     : 2015-09-18
    Author   : m00312079
    Modify   : create
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulSessionSeed;
    VOS_UINT8                           aucReserve[16];
}CNAS_NVIM_HRPD_SESSION_INFO_EX_STRU;

typedef struct
{
    VOS_UINT8                 ucPsRegFailMaxTimesTrigLauOnceFlg;
    VOS_UINT8                 ucReserved1;
    VOS_UINT8                 ucReserved2;
    VOS_UINT8                 ucReserved3;
}NAS_NVIM_PS_REG_FAIL_MAX_TIMES_TRIG_LAU_ONCE_CFG_STRU;


typedef struct
{
    VOS_UINT8                 ucKeepSrchHplmnEvenRejByCause13Flg;
    VOS_UINT8                 ucReserved1;
    VOS_UINT8                 ucReserved2;
    VOS_UINT8                 ucReserved3;
}NAS_NVIM_KEEP_SRCH_HPLMN_EVEN_REJ_BY_CAUSE_13_CFG_STRU;


typedef struct
{
    VOS_UINT8                 ucEpsRejByCause14InVplmnAllowPsRegFlg;
    VOS_UINT8                 ucReserved1;
    VOS_UINT8                 ucReserved2;
    VOS_UINT8                 ucReserved3;
}NAS_NVIM_EPS_REJ_BY_CAUSE_14_IN_VPLMN_ALLOW_PS_REG_CFG_STRU;


enum NAS_MMC_NVIM_CARRY_EPLMN_SWITCH_FLAG_ENUM
{
    NAS_MMC_NVIM_CARRY_EPLMN_SWITCH_OFF                     = 0,           /* �رմ��Ż� */
    NAS_MMC_NVIM_CARRY_EPLMN_SWITCH_ON_FOR_ROAM             = 1,           /* �Ż��򿪣����ǽ�������ʱ��Ч */
    NAS_MMC_NVIM_CARRY_EPLMN_SWITCH_ON_FOR_ALL              = 2,           /* �Ż��򿪣�����������ζ���Ч */
    NAS_MMC_NVIM_CARRY_EPLMN_SWITCH_BUTT
};
typedef VOS_UINT8 NAS_MMC_NVIM_CARRY_EPLMN_SWITCH_FLAG_ENUM_UINT8;
typedef struct
{
    NAS_MMC_NVIM_CARRY_EPLMN_SWITCH_FLAG_ENUM_UINT8         enSwitchFlag;
    VOS_UINT8                                               ucCarryEplmnSceneSwitchOn;
    VOS_UINT8                                               ucCarryEplmnSceneAreaLost;
    VOS_UINT8                                               ucCarryEplmnSceneAvailableTimerExpired;
    VOS_UINT8                                               ucCarryEplmnSceneSysCfgSet;
    VOS_UINT8                                               ucCarryEplmnSceneDisableLte;
    VOS_UINT8                                               ucCarryEplmnSceneEnableLte;
    VOS_UINT8                                               ucCarryEplmnSceneCSFBServiceRej;
    VOS_UINT8                                               ucReserved1;
    VOS_UINT8                                               ucReserved2;
    VOS_UINT8                                               ucReserved3;
    VOS_UINT8                                               ucReserved4;
}NAS_NVIM_CARRY_EPLMN_WHEN_SRCH_RPLMN_CFG_STRU;


typedef struct
{
    VOS_UINT8                           ucHomeSidNidDependOnPrlFlg;
    VOS_UINT8                           aucReserved[3];
}CNAS_NVIM_HOME_SID_NID_DEPEND_ON_PRL_CFG_STRU;


typedef struct
{
    VOS_UINT16                          usStartSid;
    VOS_UINT16                          usEndSid;
    VOS_UINT32                          ulMcc;
}CNAS_NVIM_SYS_INFO_STRU;


typedef struct
{
    VOS_UINT8                           ucEnable;                          /* �������Ƿ�ʹ�� */
    VOS_UINT8                           ucReserved;
    VOS_UINT16                          usWhiteSysNum;                     /* ֧�ְ������ĸ���,����Ϊ0ʱ��ʾ��֧�ְ����� */
    CNAS_NVIM_SYS_INFO_STRU             astSysInfo[CNAS_NVIM_MAX_WHITE_LOCK_SYS_NUM];
}CNAS_NVIM_OPER_LOCK_SYS_WHITE_LIST_STRU;


typedef struct
{
    VOS_UINT16                          usChannel;
    VOS_UINT8                           aucReserved[2];
}CNAS_NVIM_FREQENCY_CHANNEL_STRU;


typedef struct
{
    VOS_UINT8                           ucEnableFlg;
    VOS_UINT8                           ucReserved;
    VOS_UINT16                          usFreqNum;
    CNAS_NVIM_FREQENCY_CHANNEL_STRU     astFreqList[CNAS_NVIM_MAX_HRPD_CUSTOMIZE_FREQ_NUM];
}CNAS_NVIM_CTCC_CUSTOMIZE_FREQ_LIST_STRU;


typedef struct
{
    VOS_UINT16                          usPrimaryA;
    VOS_UINT16                          usPrimaryB;
    VOS_UINT16                          usSecondaryA;
    VOS_UINT16                          usSecondaryB;
}CNAS_NVIM_CDMA_STANDARD_CHANNELS_STRU;


typedef struct
{
    VOS_UINT32                                              ulEnableFlag;
}CNAS_NVIM_NO_CARD_MODE_CFG_STRU;


typedef struct
{
    VOS_UINT8                          ucImsiListNum;                                                  /*������Ч��SIM����Ŀ(LTE OOS������2G����3G)  */
    VOS_UINT8                          ucReserved1;
    VOS_UINT8                          ucReserved2;
    VOS_UINT8                          ucReserved3;
    NAS_SIM_FORMAT_PLMN_ID             astImsiList[NAS_NVIM_LTE_OOS_2G_PREF_PLMN_SEL_MAX_IMSI_LIST_NUM];/* SIM���б� (LTE OOS������2G����3G) */
}NAS_MMC_NVIM_LTE_OOS_2G_PREF_PLMN_SEL_CFG_STRU;

/* Added by h00313353 for Iteration 17, 2015-8-11, begin */
/*****************************************************************************
 �ṹ��    : CNAS_NVIM_CUSTOM_FREQUENCY_CHANNEL_STRU
 �ṹ˵��  : Ƶ�κ�Ƶ��ṹ
  1.��    ��   : 2015��7��3��
    ��    ��   : h00313353
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usChannel;
    VOS_UINT16                          usBandClass;
} CNAS_NVIM_CUSTOM_FREQUENCY_CHANNEL_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_NVIM_CDMA_1X_PREF_CHANNELS_STRU
 �ṹ˵��  : �й�����1X��ѡƵ��ṹ
  1.��    ��   : 2015��7��3��
    ��    ��   : h00313353
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                               ucEnableFlg;
    VOS_UINT8                               ucReserved;
    VOS_UINT16                              usFreqNum;
    CNAS_NVIM_CUSTOM_FREQUENCY_CHANNEL_STRU astFreqList[CNAS_NVIM_MAX_CDMA_1X_CUSTOM_PREF_CHANNELS_NUM];
} CNAS_NVIM_CDMA_1X_CUSTOM_PREF_CHANNELS_STRU;
/* Added by h00313353 for Iteration 17, 2015-8-11, end */

typedef struct
{
    VOS_UINT8                           ucIsStartT310AccordWith3GPP;            /* ��proceeding����progress�У�Я��progress indicatorֵΪ#1��#2��#64ʱ��
                                                                                   �Ƿ�����T310, 0 - ����Э����;  1 -  ����Э���� */
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
}NAS_NVIM_PROGRESS_INDICATOR_START_T310_INFO_STRU;


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

#endif /* end of NasNvInterface.h */
