

#ifndef __USIMM_BASE_H__
#define __USIMM_BASE_H__

#include "product_config.h"

#if (FEATURE_ON == FEATURE_UE_UICC_MULTI_APP_SUPPORT)

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "UsimmApi.h"
#include "UsimPsInterface.h"
#include "usimmapdu.h"
#include "omnvinterface.h"
#include "NasNvInterface.h"
#include "TafNvInterface.h"
#include "OamXmlComm.h"
#include "omerrorlog.h"
#include "pamom.h"
#include "msp_diag_comm.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#if (FEATURE_VSIM == FEATURE_ON)

#define USIMM_VSIM_TYPE_STR         "TYPE"
#define USIMM_VSIM_USIM_STR         "USIM"
#define USIMM_VSIM_SIM_STR          "SIM"
#define USIMM_VSIM_AUTH_STR         "ALGORITHM"
#define USIMM_VSIM_AUTH_3G_STR      "MILENAGE"
#define USIMM_VSIM_AUTH_2GV1_STR    "COMP128V1"
#define USIMM_VSIM_AUTH_2GV2_STR    "COMP128V2"
#define USIMM_VSIM_AUTH_2GV3_STR    "COMP128V3"
#define USIMM_VSIM_KI_STR           "EFKI"
#define USIMM_VSIM_OPC_STR          "EFOPC"
#define USIMM_VSIM_VERIFY_HASH_STR  "VERIFYHASH"
#define USIMM_VSIM_NAME_STR         "NAME"
#define USIMM_VSIM_HASH_LEN         (32)

#endif

/*fid���ȼ�*/
#define MAPS_USIMM_FID_PRIORITY         VOS_PRIORITY_P1

//���ٿ�����ʼ��
#define USIMM_OPENSPEEDENABLE           0x01000101
#define USIMM_OPENSPEEDDISABLE          0x00000000

/*Ecc����*/
#define ECC_USIM                        1
#define ECC_SIM                         0

/*ATR tag*/
#define CTLV_IND_TAG                    0x80
#define CARD_SVR_TAG                    0x30
#define CARD_CPB_TAG                    0x70
#define CARD_CPB3_TAG                   0x73

/*EFDIR tag*/
#define APP_TMP_TAG                     0x61
#define APP_IND_TAG                     0x4F

#define APP_TMP_TAG_OFFSET              (0)
#define APP_IND_TAG_OFFSET              (2)
#define APP_AID_LEN_OFFSET              (3)
#define APP_AID_VALUE_OFFSET            (4)


#define USIMM_RID_LEN                   (5)
#define USIMM_APP_CODE_LEN              (2)

/*fcp tag*/
#define USIMM_FCP_TAG                   0x62
#define USIMM_FCP_FILE_DES_TAG          0x82
#define USIMM_FCP_FID_TAG               0x83
#define USIMM_FCP_NAME_TAG              0x84
#define USIMM_FCP_PRIVITE_TAG           0xA5
#define USIMM_FCP_CHARA_TAG             0x80
#define USIMM_FCP_SA_CF_TAG             0x8C
#define USIMM_FCP_SA_EF_TAG             0xAB
#define USIMM_FCP_SA_REF_TAG            0x8B
#define USIMM_FCP_PIN_TO_TAG            0xC6
#define USIMM_FCP_FILESIZE_TAG          0x80
#define USIMM_FCP_SFI_TAG               0x88
#define USIMM_FCP_PRO_INFO_TAG          0xA5
#define USIMM_FCP_LCSI_TAG              0x8A
#define USIMM_FCP_TOTAL_SIZE_TAG        0x81
#define USIMM_FCP_PINMAP_TAG            0x90
#define USIMM_FCP_PINRER_TAG            0x83
#define USIMM_FCP_PINQUALIFER_TAG       0x95
#define USIMM_FCP_SUPSYSCMD_TAG         0x87

/*�ļ�������ļ���Ŀ*/
#define USIMM_POOL_MAX_NUM              (64)

/*�������ļ�������ļ��ռ�*/
#define USIMM_MAX_FILE_SIZE             (0x2000)

/*��ʼ���ļ�������,��Ϊ����PIN�����ģ�����PIN������Mandatory��Optional�ļ�*/
#define USIMM_INITFIRST_FILENUM        2
#define USIMM_INITSIM_OFILENUM         12
#define USIMM_INITUSIM_OFILENUM        15

/* Optional�ļ���ʼ������ļ����� */
#define USIMM_INIT_OFILE_MUX_NUM       (16)

/* ATT�����ļ���ʼ���ļ��б��� */
#define USIMM_USIM_ATT_INITFILE_NUM     2
#define USIMM_SIM_ATT_INITFILE_NUM      1

//�ļ���ϵ��ֵ����
#define USIMM_SIMDFGSMGDF_MAX           2
#define USIMM_SIMDFTELGDF_MAX           1
#define USIMM_SIMDFCONTENT_MAX          2

#define USIMM_USIMADFGDF_MAX            4
#define USIMM_USIMADFTELGDF_MAX         2
#define USIMM_USIMDFCONTENT_MAX         3

/*�жϿ���λ״̬��ѭ������*/
#define USIMM_GET_SCISTATUS_MAX         300

/*��λ����������*/
#define USIMM_RESET_CARD                0
#define USIMM_CHANGE_VCC                1

/*SCI�����������*/
#define USIMM_SCI_SUCCESS               0
#define USIMM_SCI_NONEED_CHANGEVCC      1

/*��ȡȫ���ļ�����*/
#define USIMM_READ_ALL_FILE_CONTENT     0

/*�����Ը�λ�¼�*/
#define USIMM_PROTECT_RESET             0xFF

#define USIMM_PROTECT_MAX_NUM           (3)

/*��ǰ��¼�ļ����������ṹ����ʹ����Ҫ4�ֽڶ���*/
#define USIMM_LOG_FILE_MAX_NUM          (4)

/*��ǰ��¼�ļ�����������ṹ����ʹ����Ҫ4�ֽڶ���*/
#define USIMM_LOG_FILE_NAME_LEN         (0x10)

#define USIMM_LOG_DATA_TAG              (0x5A)

#define USIMM_LOG_START_TAG             (0x5555AAAA)

/*��ǰ��¼����������Ĵ�С*/
#define USIMM_LOG_DATA_MAX_LEN          (8*1024)
#define USIMM_EXCLOG_DATA_MAX_LEN       (4*1024)

/* ATT����Support Table�ĳ��� */
#define USIMM_ATT_SUPPORT_TABLE_MAX     (16)
#define USIMM_ATT_SUPPORT_TABLE_MIN     (8)

/* ATT����Support Table�ֽ�ƫ���� */
#define USIMM_ATT_SCAN_CTRL_OFFSET          (0)
#define USIMM_ATT_NETWORK_SELECTION_OFFSET  (1)
#define USIMM_ATT_ACTING_HPLMN              (2)
#define USIMM_ATT_3G_SUPPORT                (3)
#define USIMM_ATT_RAT_BALANCING             (4)
#define USIMM_ATT_BIP_SUPPORT               (5)
#define USIMM_ATT_LTE_SUPPORT               (6)
#define USIMM_ATT_CSG_SUPPORT               (7)

/* ATT����Support Table��LTE���� */
#define USIMM_ATT_LTE_DATA_ONLY             (0x01)
#define USIMM_ATT_LTE_DATE_VOICE_CSFB       (0x02)
#define USIMM_ATT_LTE_DATE_VOICE_CSFB_IMS   (0x03)


#define USIMM_ENVELOPE_PPDOWN                (0xD1)
#define USIMM_ENVELOPE_CBDOWN                (0xD2)

/* ATR��Ϣ */
#define USIMM_ATR_MAX_LEN                   (80)
#define USIMM_ATR_T0_OFFSET                 (1)

/* Session ID���ֵ */
#define USIMM_SESSION_ID_MAX                (0x7fffffff)

/* ͨ�������ֵ */
#define USIMM_CHANNEL_INVALID_NUM           (0xffffffff)

/* UICC����ͨ���� */
#define USIMM_BASE_CHANNEL_NUM              (0)

#define USIMM_RAND_SEED_MAX                 (0xffffffff)

/* ���Է���ѡ���ļ�APDU�������� */
#define USIMM_SELECT_MAX_TIME               (3)

#define USIMM_SIM_SELECT_P2_PARA            (0x00)

#define USIMM_2G_AUTH_SRES_LEN              (4)
#define USIMM_2G_AUTH_KC_LEN                (8)

/* ��Ȩ������ʹ�õ�TAG��ʾ */
#define USIMM_GBA_AUTH_TAG                  (0xDD)
#define USIMM_NAF_AUTH_TAG                  (0xDE)
#define USIMM_AUTH_SUCCESS_TAG              (0xDB)
#define USIMM_AUTH_SYNC_FAIL_TAG            (0xDC)


/* ��Ȩģʽ���壬��ӦAPDU�е�P2���� */
#define USIMM_SIM_2G_AUTH_MODE              (0x00)
#define USIMM_USIM_2G_AUTH_MODE             (0x80)
#define USIMM_USIM_3G_AUTH_MODE             (0x81)
#define USIMM_USIM_GBA_AUTH_MODE            (0x84)
#define USIMM_ISIM_AKA_AUTH_MODE            (0x81)
#define USIMM_ISIM_HTTP_AUTH_MODE           (0x82)
#define USIMM_ISIM_GBA_NAF_AUTH_MODE        (0x84)

/* ��������ļ����� */
#define USIMM_FILE_TYPE(usFileId)           (VOS_UINT8)((usFileId>>0x08)&0x00FF)

/* �ж������ļ��Ƿ�ΪDF�ļ� */
#define USIMM_IS_DF_FILE(usFileId) \
        (USIMM_DF_FILE == (((usFileId)>>0x0C)&0x01))

#define USIMM_FILE_PATH_MAX_LEN         100

#if( (VOS_WIN32 == VOS_OS_VER) ||  (defined __PS_WIN32_RECUR__) )
#define USIMM_LOG_PATH                  "Sim1"
#define USIMM_LOGCTRL_FILE              "Sim1/usimmlogctrl.bin"

#define USIMM_UNITARY_LOG_PATH          USIMM_LOG_PATH

#define USIMM_UNITARY_LOGCTRL_FILE      USIMM_LOGCTRL_FILE

#elif (( VOS_VXWORKS == VOS_OS_VER ) || ( VOS_RTOSCK == VOS_OS_VER ))
#if defined (INSTANCE_1)    /*SIM card 1*/
#define USIMM_LOG_PATH                  "/mnvm3:0/DrvLog/Sim1"

#define USIMM_LOGCTRL_FILE              "/mnvm3:0/DrvLog/Sim1/usimmlogctrl.bin"

#define USIMM_UNITARY_LOG_PATH          "/modem_log/DrvLog/Sim1"

#define USIMM_UNITARY_LOGCTRL_FILE      "/modem_log/DrvLog/Sim1/usimmlogctrl.bin"

#elif defined (INSTANCE_2)   /*SIM card 2*/
#define USIMM_LOG_PATH                  "/mnvm3:0/DrvLog/Sim2"

#define USIMM_LOGCTRL_FILE              "/mnvm3:0/DrvLog/Sim2/usimmlogctrl.bin"

#define USIMM_UNITARY_LOG_PATH          "/modem_log/DrvLog/Sim2"

#define USIMM_UNITARY_LOGCTRL_FILE      "/modem_log/DrvLog/Sim2/usimmlogctrl.bin"
#else                       /*SIM Card 0*/
#define USIMM_LOG_PATH                  "/mnvm3:0/DrvLog/Sim0"

#define USIMM_LOGCTRL_FILE              "/mnvm3:0/DrvLog/Sim0/usimmlogctrl.bin"

#define USIMM_UNITARY_LOG_PATH          "/modem_log/DrvLog/Sim0"

#define USIMM_UNITARY_LOGCTRL_FILE      "/modem_log/DrvLog/Sim0/usimmlogctrl.bin"

#endif /* end of INSTANCE_1*/
#endif /* end of VOS_WIN32*/


#define USIMM_MNC_TWO_BYTES_LEN        (2)             /* MNC����Ϊ2 */
#define USIMM_MNC_THREE_BYTES_LEN      (3)             /* MNC����Ϊ3 */
#define USIMM_AD_MNC_LEN_POS           (3)             /* AD�ļ���MNC�����ֶ�����λ�� */
#define USIMM_IMSI_MAX_LEN             (8)             /* IMSI��ָʾ���ȵ����ֵ */

#define USIMM_BIT_NUM_IN_BYTE          (8)             /* һ���ֽ��а�����bit�� */
#define USIMM_MNC_MCC_FIG_NUM          (3)             /* MNC,MCC���ָ�����MNC���ֲ���3��ʱ����0 */
#define USIMM_ISIMEFTOUSIMEF_TBL_SIZE  (5)             /* ISIM�ļ���USIM�ļ�ת�����С */

#define USIMM_ISIM_FILE_TAG            (0x80)

#define USIMM_AUTH_XRES_LEN             (8)     /* 3G��Ȩ�ķ�������     */
#define USIMM_AUTH_RES_LEN              (4)     /* 2G��Ȩ�ķ�������     */
#define USIMM_AUTH_CK_LEN               (16)    /* 3G��Ȩ��CK           */
#define USIMM_AUTH_IK_LEN               (16)    /* 3G��Ȩ��IK           */
#define USIMM_AUTH_KC_LEN               (8)     /* 2G��Ȩ��Kc           */
#define USIMM_AUTH_KI_LEN               (16)    /* ��Ȩ��KI             */
#define USIMM_AUTH_OPC_LEN              (16)    /* ��Ȩ��OPC            */

#define USIMM_VSIM_SECUR_MAX_LEN        (32)    /* vSIM����������ݳ��� */

#define USIMM_VSIM_SIM_KEY_HASH_LEN     (96)    /* IMSI+KI+OPC���ܳ���  */


#if (FEATURE_VSIM == FEATURE_ON)
#define USIMM_VSIM_IS_FILE_ATTR_VALID(index)      ( (USIMM_MANDATORY_FILE         == g_astUSIMMVSimFileInfo[index].enFileAttr) \
                                                  ||((USIMM_USIM_MANDATORY_FILE  == g_astUSIMMVSimFileInfo[index].enFileAttr) \
                                                    &&(USIMM_PHYCARD_TYPE_UICC   == USIMM_CCB_GetCardType())) \
                                                  ||((USIMM_SIM_MANDATORY_FILE   == g_astUSIMMVSimFileInfo[index].enFileAttr) \
                                                    &&(USIMM_PHYCARD_TYPE_ICC    == USIMM_CCB_GetCardType())) )
#endif

#define USIMM_EF_CST_MAX_LEN            (12)

#define USIMM_INITAPPS_TIMES_MAX        (3)

#define USIMM_CHANNEL_NUMBER_MAX        (20)

#define USIMM_PIN_NUMBER_MAX            (8)

#define USIMM_CDMA_DEFAULT_SCM          (8)

#define EFICCID                                 (0x2FE2)

/* ATT�Զ����ļ�ID */
#define EFACTINGHPLMN                           (0x4F34)
#define EFRATMODE                               (0x4F36)
#define EFTERMINALSUPPORTTABLE                  (0x6FD2)

/*PB �ļ�ID���� */
#define EFPSC                                   (0x4F22)
#define EFCC                                    (0x4F23)
#define EFPUID                                  (0x4F24)

/* ISIM �ļ�ID���� �ο�31.103 */
#define EFISIMIMPI                              (0x6F02)
#define EFISIMDOMAIN                            (0x6F03)
#define EFISIMIMPU                              (0x6F04)
#define EFISIMAD                                (0x6FAD)
#define EFISIMIST                               (0x6F07)
#define EFISIMPCSCF                             (0x6F09)
#define EFISIMGBABP                             (0x6FD5)
#define EFISIMGBANL                             (0x6FD7)
#define EFISIMNAFKCA                            (0x6FDD)
#define EFISIMUICCIARI                          (0x6FE7)

/* USIM �ļ�ID���� �ο�31.102 */
#define EFPL                                    (0x2F05)
#define EFICCID                                 (0x2FE2)
#define EFLP                                    (0x6F05)
#define EFIMSI                                  (0x6F07)
#define EFAD                                    (0x6FAD)
#define EFEST                                   (0x6F56)
#define EFADN                                   (0x6F3A)
#define EFBDN                                   (0x6F4D)
#define EFFDN                                   (0x6F3B)
#define EFECC                                   (0x6FB7)
#define EFMSISDN                                (0x6F40)
#define EFPHASE                                 (0x6FAE)
#define EFGBABP                                 (0x6FD6)
#define EFGBANL                                 (0x6FDA)
#define EFNAFKCA                                (0x6FDD)
#define EFUICCIARI                              (0x6FE7)
#define EFUST                                   (0x6F38)

/* UIM �ļ�ID���壬�ο�C.S0023 */
#define EFCST                                   (0x6F32)
#define EF_CSIM_EST                             (0x6F75)   /*T*/
#define EF_CUIM_ECC                             (0x6F47)   /*T*/
#define EF_CUIM_AD                              (0x6F43)   /*T*/
#define EF_CUIM_CST                             (0x6F32)   /*T*/
#define EF_CUIM_IMSIM                           (0x6F22)   /*T*/
#define EF_CUIM_IMSIT                           (0x6F23)   /*T*/
#define EF_CUIM_TMSI                            (0x6F24)   /*T*/

/* CSIM �ļ�ID���� */
#define EFCSIMST                                (0x6F32)
/* SIM �ļ�ID���� */
#define EFSST                                   (0x6F38)

/* VSIM �ļ�ID */
#define EFFPLMN                                 (0x6F7B)
#define EFPSLOCI                                (0x6F73)
#define EFLOCIGPRS                              (0x6F53)
#define EFLOCI                                  (0x6F7E)
/*******************************************************************************
  3 ö�ٶ���
*******************************************************************************/
typedef VOS_UINT32 (*PCARDINITPROC)(VOS_VOID);

typedef struct
{
    PCARDINITPROC                pProcFun;        /* ������ */
}USIMM_CARD_INIT_FUNC;

typedef struct
{
    USIMM_CARD_INIT_FUNC         *pInitFunTbl;
    VOS_UINT32                   ulStepNum;
}USIMM_CARD_INIT_TBL_ST;

/* MANAGE CHANNEL ����ö�� ���·����ݵ�Ԫ��p1�������μ�Э��102.221��11.1.17 */
enum USIMM_MANAGE_CHANNEL_ENUM
{
    USIMM_OPEN_CHANNEL         =0x00,
    USIMM_CLOSE_CHANNEL        =0x80,
    USIMM_MANAGE_CHANNEL_BUTT
};
typedef VOS_UINT32      USIMM_MANAGE_CHANNEL_ENUM_UINT32;

/*�Ƿ�֧��sfi*/
enum USIMM_SUPPORT_SFI_ENUM
{
    USIMM_NOTSUPPORT_SFI         =0,
    USIMM_SUPPORT_SFI            =1,
    USIMM_SUPPORT_SFI_ENUM_BUTT
};
typedef VOS_UINT32      USIMM_SUPPORT_SFI_ENUM_UINT32;


/*�Ƿ�֧��path*/
enum USIMM_SUPPORT_PATH_ENUM
{
    USIMM_NOTSUPPORT_PATH       = 0,
    USIMM_SUPPORT_PATH          = 1,
    USIMM_SUPPORT_PATH_BUTT
};
typedef VOS_UINT32      USIMM_SUPPORT_PATH_ENUM_UINT32;


/*�Ƿ�֧��logic channel*/
enum USIMM_SUPPORT_CHANNEL_ENUM
{
    USIMM_NOTSUPPORT_CHANNEL    = 0,
    USIMM_SUPPORT_CHANNEL       = 1,
    USIMM_SUPPORT_CHANNEL_BUTT
};
typedef VOS_UINT32      USIMM_SUPPORT_CHANNEL_ENUM_UINT32;

enum USIMM_CLKLEVEL_ENUM
{
    USIMM_CLKLEVEL_LOW          = 0,
    USIMM_CLKLEVEL_HIGH         = 1,
    USIMM_CLKLEVEL_NONE         = 2,
    USIMM_CLKLEVEL_BUTT
};
typedef VOS_UINT32      USIMM_CLKLEVEL_ENUM_UINT32;

enum USIMM_CLKSTOP_ENUM
{
    USIMM_CLKSTOP_ALLOW             = 0,
    USIMM_CLKSTOP_NOALLOW           = 1,
    USIMM_CLKSTOP_BUTT
};
typedef VOS_UINT32      USIMM_CLKSTOP_ENUM_UINT32;

enum USIMM_SAT_STATE_ENUM
{
    USIMM_SAT_STATE_NODATA          = 0,
    USIMM_SAT_STATE_NEEDFETCH       = 1,
    USIMM_SAT_STATE_NEEDRESPONSE    = 2,
    USIMM_SAT_STATE_BUTT
};
typedef VOS_UINT32      USIMM_SAT_STATE_ENUM_UINT32;


enum USIMM_UNIVERSAL_PIN_STATUS_ENUM
{
    USIMM_UNIVERSAL_PIN_DISABLE     = 0,
    USIMM_UNIVERSAL_PIN_ENABLE      = 1,
    USIMM_UNIVERSAL_PIN_BUTT
};
typedef VOS_UINT32      USIMM_UNIVERSAL_PIN_STATUS_ENUM_UINT32;


/*�ļ��ṹ*/
enum USIMM_EF_TYPE_ENUM
{
    USIMM_EFSTRUCTURE_NONE          = 0,
    USIMM_EFSTRUCTURE_TRANSPARENT   = 1,
    USIMM_EFSTRUCTURE_FIXED         = 2,
    USIMM_EFSTRUCTURE_CYCLE         = 3,
    USIMM_EFSTRUCTURE_ENUM_BUTT
};
typedef VOS_UINT32      USIMM_EF_TYPE_ENUM_UINT32;

enum USIMM_SC_ATTRIB_MODE_ENUM
{
    USIMM_SC_ATTRIB_NO          = 0,
    USIMM_SC_ATTRIB_COMPACT     = 1,
    USIMM_SC_ATTRIB_EXPANDED    = 2,
    USIMM_SC_ATTRIB_REFERENCE   = 3,
    USIMM_SC_ATTRIB_BUTT
};
typedef VOS_UINT32      USIMM_SC_ATTRIB_MODE_ENUM_UINT32;


enum USIMM_AC_LEVEL_ENUM
{
    USIMM_AC_LEVEL_ALW          = 0,
    USIMM_AC_LEVEL_PIN1         = 1,
    USIMM_AC_LEVEL_PIN2         = 2,
    USIMM_AC_LEVEL_UPIN         = 3,
    USIMM_AC_LEVEL_ADM          = 4,
    USIMM_AC_LEVEL_NEV          = 5,
    USIMM_AC_LEVEL_BUTT
};
typedef VOS_UINT32      USIMM_AC_LEVEL_ENUM_UINT32;

enum USIMM_POOLSTATUS_ENUM
{
    USIMM_POOL_NOINTIAL         =  0,
    USIMM_POOL_INITIALED        =  1,
    USIMM_POOL_FIRST_STEP       =  2,
    USIMM_POOL_AVAILABLE        =  3,
    USIMM_POOLSTATUS_BUTT
};
typedef VOS_UINT32      USIMM_POOLSTATUS_ENUM_UINT32;

enum USIMM_CARD_STATE_CHANGE_ENUM
{
    USIMM_CARD_STATE_NOCHANGE   = 0,
    USIMM_CARD_STATE_CHANGED    = 1,
    USIMM_CARD_STATE_CHANGE_BUTT
};
typedef VOS_UINT32      USIMM_CARD_STATE_CHANGE_ENUM_UINT32;

enum USIMM_FILE_NEED_FCP_ENUM
{
    USIMM_NO_NEED_FCP           = 0,
    USIMM_NEED_FCP              = 1,
    USIMM_NEED_FCP_BUTT
};
typedef VOS_UINT32      USIMM_FILE_NEED_FCP_ENUM_UINT32;

enum USIMM_LOG_STATE_ENUM
{
    USIMM_NEED_LOG              = 0,
    USIMM_NO_NEED_LOG           = 1,
    USIMM_LOG_STATE_BUTT
};
typedef VOS_UINT32      USIMM_LOG_STATE_ENUM_UINT32;

enum USIMM_SUPPORT_SYSTEM_COMMAND_ENUM
{
    USIMM_NO_SUPSYSCMD           = 0,
    USIMM_SUPSYSCMD              = 1,
    USIMM_SUPSYSCMD_BUTT
};
typedef VOS_UINT32      USIMM_SUPPORT_SYSTEM_COMMAND_ENUM_UINT32;

enum USIMM_MODE_TYPE_ENUM
{
    USIMM_NORMAL_MODE           = 0,    /* �����ϵ�����ģʽ */
    USIMM_RESET_MODE            = 1,    /* ��λ����ģʽ */
    USIMM_REFRESH_MODE          = 2,    /* refreshģʽ */
    USIMM_PROTECT_RESET_MODE    = 3,    /* �����Ը�λģʽ */
    USIMM_MODE_TYPE_BUTT
};
typedef VOS_UINT8      USIMM_MODE_TYPE_ENUM_UINT8;


/* USIM����ѹ�ȼ���Э��TS102221 11.1.1.4.6.1 */
enum USIMM_VOLTAGE_CLASS_ENUM
{
    USIMM_VOLTAGE_5V           = 0x10,   /* supply voltage class A */
    USIMM_VOLTAGE_3V           = 0x20,   /* supply voltage class B */
    USIMM_VOLTAGE_1_8V         = 0x40,   /* supply voltage class C */
    USIMM_VOLTAGE_CLASS_BUTT
};
typedef VOS_UINT32      USIMM_VOLTAGE_CLASS_ENUM_UINT32;

/* SIM����PHASEö�� */
enum USIMM_SIM_PHASE_ENUM
{
    USIMM_SIM_PHASE_ONE        = 0x00,   /* PHASE1 ��SIM�� */
    USIMM_SIM_PHASE_TWO        = 0x02,   /* PHASE2 ��SIM�� */
    USIMM_SIM_PHASE_PLUS       = 0x03,   /* PHASE2+ ��SIM�� */
    USIMM_SIM_PHASE_BUTT
};
typedef VOS_UINT32      USIMM_SIM_PHASE_ENUM_UINT32;

enum USIMM_PROFILE_DOWNLOAD_ENUM
{
    USIMM_PROFILE_DOWNLOAD_SUCCESS      = VOS_OK,
    USIMM_PROFILE_DOWNLOAD_FAIL,
    USIMM_PROFILE_DOWNLOAD_BUTT
};

typedef VOS_UINT8       USIMM_PROFILE_DOWNLOAD_ENUM_UINT8;

/* ��ʼ���׶�ECC�ļ���ʼ��״̬ö�� */
enum USIMM_ECC_INIT_STATUS_ENUM
{
    USIMM_ECC_INIT_SUCCESS      = VOS_OK,
    USIMM_ECC_SELECT_FAIL,
    USIMM_ECC_READ_FAIL,
    USIMM_ECC_TYPE_ERR,
    USIMM_ECC_INIT_STATUS_BUTT
};

typedef VOS_UINT8       USIMM_ECC_INIT_STATUS_ENUM_UINT8;

enum USIMM_SIM_FILE_TYPE_ENUM
{
    USIMM_SIM_FILE_TYPE_RFU = 0x00,
    USIMM_SIM_FILE_TYPE_MF  = 0x01,
    USIMM_SIM_FILE_TYPE_DF  = 0x02,
    USIMM_SIM_FILE_TYPE_EF  = 0x04,
    USIMM_SIM_FILE_TYPE_BUTT
};

typedef VOS_UINT8 USIMM_SIM_FILE_TYPE_ENUM_UINT8;

enum USIMM_VSIM_AUTH_ENUM
{
    USIMM_VSIM_AUTH_NULL        = 0,
    USIMM_VSIM_MILENAGE         = 1,
    USIMM_VSIM_COMPV1           = 2,
    USIMM_VSIM_COMPV2           = 3,
    USIMM_VSIM_COMPV3           = 4,
    USIMM_VSIM_AUTH_BUTT
};
typedef VOS_UINT8      USIMM_VSIM_AUTH_ENUM_UINT8;
typedef VOS_UINT32     USIMM_VSIM_AUTH_ENUM_UINT32;

enum USIMM_FILE_ATTR_ENUM
{
    USIMM_MANDATORY_FILE        = 0,    /*SIM USIM����Ҫ���ļ�*/
    USIMM_USIM_MANDATORY_FILE   = 1,
    USIMM_SIM_MANDATORY_FILE    = 2,
    USIMM_OPTIONAL_FILE         = 3,
    USIMM_FILE_ATTR_BUTT
};
typedef VOS_UINT8      USIMM_FILE_ATTR_ENUM_UINT8;

enum USIMM_VSIM_AC_ENUM
{
    USIMM_VSIM_WRITE_AVALIBALE        = 0,    /*VSIM���Ը��µ��ļ�*/
    USIMM_VSIM_WRITE_UNAVALIBALE      = 1,    /*VSIM�����Ը��µ��ļ�*/
    USIMM_VSIM_AC_ENUM_BUTT
};
typedef VOS_UINT8      USIMM_VSIM_AC_ENUM_UINT8;

/*****************************************************************************
 ö����    : USIMM_T1_IFS_SEND_STATUS_ENUM
 �ṹ˵��  : T=1 IFS �����״̬ö��
*****************************************************************************/
enum USIMM_T1_IFS_SEND_STATUS_ENUM
{
    USIMM_T1_IFS_SEND_SUCCESS = VOS_OK,          /* T=1Э���·���IFS����ɹ� */
    USIMM_T1_IFS_SEND_FAILURE,                   /* T=1Э���·���IFS����ʧ�� */
    USIMM_T1_IFS_SEND_STATUS_BUTT
};

typedef VOS_UINT32      USIMM_T1_IFS_SEND_STATUS_ENUM_UINT32;

/*****************************************************************************
 ö����    : USIMM_MNTN_ERROR_LEVEL_ENUM
 �ṹ˵��  : USIMM ERROR LOG����ö��
*****************************************************************************/
enum USIMM_MNTN_ERROR_LEVEL_ENUM
{
    USIMM_MNTN_ERROR_LEVEL_CRITICAL = 1,    /* ���� */
    USIMM_MNTN_ERROR_LEVEL_MAJOR,           /* ��Ҫ */
    USIMM_MNTN_ERROR_LEVEL_MINOR,           /* ��Ҫ */
    USIMM_MNTN_ERROR_LEVEL_WARNING,         /* �澯 */
    USIMM_MNTN_ERROR_LEVEL_INFO,            /* ��Ϣ */
    USIMM_MNTN_ERROR_LEVEL_BUTT
};
typedef  VOS_UINT16  USIMM_MNTN_ERROR_LEVEL_ENUM_UINT16;

/*****************************************************************************
 ö����    : USIMM_MNTN_STATE_ERROR_REASON_ENUM
 �ṹ˵��  : USIMM ERROR LOG �¼�ö��
*****************************************************************************/
enum USIMM_MNTN_STATE_ERROR_REASON_ENUM
{
    USIMM_MNTN_STATE_OK = 0,
    USIMM_MNTN_STATE_INIT_FAIL,
    USIMM_MNTN_STATE_POLLING_FAIL,
    USIMM_MNTN_STATE_ERROR_REASON_BUTT
};
typedef  VOS_UINT32  USIMM_MNTN_STATE_ERROR_REASON_ENUM_UINT32;

/*****************************************************************************
 ö����    : USIMM_PIN_ENUM
 �ṹ˵��  : PIN������ֵ
*****************************************************************************/
enum USIMM_PIN_ENUM
{
    USIMM_UNIVERSIAL_PIN = 0,
    USIMM_KEY_REF_PIN_01,
    USIMM_KEY_REF_PIN_02,
    USIMM_KEY_REF_PIN_03,
    USIMM_KEY_REF_PIN_04,
    USIMM_KEY_REF_PIN_05,
    USIMM_KEY_REF_PIN_06,
    USIMM_KEY_REF_PIN_07,
    USIMM_KEY_REF_PIN_08,
    USIMM_KEY_REF_PIN_BUTT,
};
typedef VOS_UINT32      USIMM_COMM_PIN_ENUM_UINT32;

/*****************************************************************************
 ö����    : USIMM_TEST_PHYCARD_TYPE_ENUM
 �ṹ˵��  : ���Կ�����
*****************************************************************************/
enum USIMM_TEST_PHYCARD_TYPE_ENUM
{
    USIMM_TEST_TYPE_NONE        = 0x00,
    USIMM_TEST_TYPE_ROM_SIM,
    USIMM_TEST_TYPE_GCF_SIM,
    USIMM_TEST_TYPE_BUTT
};
typedef VOS_UINT32 USIMM_TEST_PHYCARD_TYPE_ENUM_UINT32;

/*****************************************************************************
  4 STRUCT����
*****************************************************************************/

/*effcp��Ϣ��¼�ṹ*/
typedef struct
{
    VOS_UINT16                          usFileLen;              /*��ǰ�ļ�����*/
    VOS_UINT8                           ucRecordNum;            /*��ǰ��¼�ļ��ļ�¼��*/
    VOS_UINT8                           ucRecordLen;            /*��ǰ��¼�ļ��ļ�¼����*/
    VOS_UINT8                           ucSFI;                  /*��ǰ�ļ���SFI*/
    VOS_UINT8                           ucArrNo;                /*EFARR�ļ�¼��*/
    VOS_UINT16                          usEFArrID;              /*��¼��ȫ������EFARR��SFI*/
    USIMM_EF_TYPE_ENUM_UINT32           enFileType;             /*��ǰ�ļ�����*/
    USIMM_EFSTATUS_ENUM_UINT8           enFileStatus;           /*��ǰ�ļ�״̬*/
    USIMM_EFRWFLAG_ENUM_UINT8           enFileReadUpdateFlag;   /*��ǰ�ļ���Чʱ���ļ��ɶ���ɸ��±�־*/
    VOS_UINT8                           aucRsv[2];
    USIMM_SC_ATTRIB_MODE_ENUM_UINT32    enSCMode;               /*��ǰ�ļ��İ�ȫ��ʶ����*/
    USIMM_AC_LEVEL_ENUM_UINT32          enUpdateAC;             /*��ǰ�ļ��ĸ���Ȩ��*/
    USIMM_AC_LEVEL_ENUM_UINT32          enReadAC;               /*��ǰ�ļ��Ķ�ȡȨ��*/
    USIMM_AC_LEVEL_ENUM_UINT32          enActiveAC;             /*��ǰ�ļ��ļ���Ȩ��*/
    USIMM_AC_LEVEL_ENUM_UINT32          enDeaciveAC;            /*��ǰ�ļ���ȥ����Ȩ��*/
}USIMM_EFFCP_ST;

/*dffcp��Ϣ��¼�ṹ*/
typedef struct
{
    VOS_UINT16                          usDFID;         /*��ǰѡ��DFID*/
    VOS_UINT8                           ucPIN1RefNum;   /*��ǰDF��PIN1����*/
    VOS_UINT8                           ucPIN2RefNum;   /*��ǰDF��PIN2����*/
    VOS_UINT8                           ucCharaByte;
    VOS_UINT8                           ucNameLen;      /*��ǰDF�����ֳ���*/
    VOS_UINT8                           aucName[16];    /*��ǰDF����������*/
    VOS_UINT8                           ucSupCmd;       /*֧��terminal capability */
    VOS_UINT8                           ucRsv;
    USIMM_SC_ATTRIB_MODE_ENUM_UINT32    enSCMode;       /*��ǰDF�İ�ȫ��ʶ��ʽ*/
    USIMM_PIN_INFO_STRU                 stPINInfo;
}USIMM_DFFCP_ST;

/*sim dffcp ���ݼ�¼�ṹ,��Ա�����Э��3gpp ts 11.11 ��9.2.1*/
typedef struct
{
    VOS_UINT8                           ucReserve[2];
    VOS_UINT16                          usMemRes;
    VOS_UINT16                          usFileID;
    VOS_UINT8                           ucFileType;
    VOS_UINT8                           ucReserve2[5];
    VOS_UINT8                           ucDataLen;
    VOS_UINT8                           ucFileChara;
    VOS_UINT8                           ucDFsNum;
    VOS_UINT8                           ucEFsNum;
    VOS_UINT8                           ucSecurityCodeNum;
    VOS_UINT8                           ucReserve3;
    VOS_UINT8                           ucPIN1RemainTime;
    VOS_UINT8                           ucPUK1RemainTime;
    VOS_UINT8                           ucPIN2RemainTime;
    VOS_UINT8                           ucPUK2RemainTime;
}USIMM_SIMDF_FCP_ST;

/*sim effcp ���ݼ�¼�ṹ,��Ա�����Э��3gpp ts 11.11 ��9.2.1*/
/*lint -e959 -e958*/
typedef struct
{
    VOS_UINT8                           ucReserve[2];
    VOS_UINT16                          usFileLen;
    VOS_UINT16                          usFileID;
    VOS_UINT8                           ucFileType;
    VOS_UINT8                           ucCyclicEFTag;
    VOS_UINT8                           ucAccessCnd[3];
    VOS_UINT8                           ucFileStatus;
    VOS_UINT8                           ucDataLen;
    VOS_UINT8                           ucEFStruct;
    VOS_UINT8                           ucRecordLen;
}USIMM_SIMEF_FCP_ST;
/*lint +e959 +e958*/

typedef struct
{
    VOS_UINT32                          ulAIDLen;       /*��ǰ��AID����*/
    VOS_UINT8                           aucAID[USIMM_AID_LEN_MAX];     /*��ǰAID����*/
}USIMM_AID_INFO_STRU;

typedef struct
{
    USIMM_PB_INIT_STATUS_ENUM_UINT16    enPBInitStatus;     /*��ǰ�绰����ʼ��״̬���Ծ����Ƿ���Խ���ʱ��ֹͣģʽ*/
    VOS_UINT16                          usPBDfID;           /*��ǰ�绰����4F�ļ����ڵ�·��*/
}USIMM_PB_INFO_STRU;

/*������Ϣ��¼�ṹ*/
typedef struct
{
    VOS_UINT8                               ucCLA;              /*��ǰCLAֵ*/
    VOS_UINT8                               ucCurChannelNum;    /*��ǰ������ͨ����*/
    VOS_UINT16                              usSATLen;           /*��ǰ�����������*/
    USIMM_CARDAPP_ENUM_UINT32               enMainAppType;      /*��Ӧ������*/
    USIMM_PHYCARD_TYPE_ENUM_UINT32          enCardType;         /*���濨����*/
    USIMM_CARD_STATE_CHANGE_ENUM_UINT32     enStateChange;      /* ״̬��� */
    USIMM_SUPPORT_SFI_ENUM_UINT32           enSupportSFI;       /*�Ƿ�֧��SFI*/
    USIMM_SUPPORT_PATH_ENUM_UINT32          enSupportPath;      /*�Ƿ�֧��·��ѡ��*/
    USIMM_SUPPORT_CHANNEL_ENUM_UINT32       enSupportChannel;   /*�Ƿ�֧���߼�ͨ��*/
    USIMM_UNIVERSAL_PIN_STATUS_ENUM_UINT32  enUniversalPINStatus;/*��ǰȫ��PIN״̬*/
    USIMM_SAT_STATE_ENUM_UINT32             enSATState;         /*��ǰ��������״̬*/
    VOS_BOOL                                bTimeOut;           /*����TimeOut�¼���ʱ����*/
    USIMM_PB_INFO_STRU                      stPBInfo;           /*��ǰ�绰����ʱ����Ϣ*/
}USIMM_BASE_INFO_ST;

typedef struct
{
    VOS_UINT32                              ulIsimEFID;
    VOS_UINT32                              ulUsimEFID;
}USIMM_ISIMUSIM_EFTBL_STRU;

/*������Ϣ��¼�ṹ*/
typedef struct
{
    USIMM_CLKLEVEL_ENUM_UINT32              enCLKLevel;         /*��ǰCLK level���ȼ�*/
    USIMM_CLKSTOP_ENUM_UINT32               enCLKStop;          /*��ǰCLK �Ƿ�����ֹͣ*/
}USIMM_DRV_INFO_ST;

/*��ǰ�ļ���Ϣ��¼�ṹ*/
typedef struct
{
    VOS_UINT16                              usCurDFID;      /*��ǰѡ��DFID*/
    VOS_UINT16                              usCurEFID;      /*��ǰѡ��EFID*/
    VOS_UINT16                              usCurDFFcpLen;  /*��ǰѡ�е�DF��FCP����*/
    VOS_UINT16                              usFilePathLen;
    VOS_UINT16                              ausFilePath[USIMM_MAX_PATH_LEN];  /*��ǰ·����Ϣ*/
    USIMM_DFFCP_ST                          stDFInfo;       /*��ǰDF��Ϣ*/
    USIMM_EFFCP_ST                          stEFInfo;       /*��ǰEF��Ϣ*/
}USIMM_CURFILEINFO_ST;


typedef struct
{
    VOS_UINT16                              usEFId;         /* �ļ�ID */
    VOS_UINT16                              usLen;          /* �ļ����ݳ��� */
    USIMM_CARDAPP_ENUM_UINT32               enAppType;      /* APP���� */
    USIMM_EF_TYPE_ENUM_UINT32               enFileType;     /* �ļ����� */
    VOS_UINT8                              *pucContent;     /* �ļ�����ָ�� */
}USIMM_POOL_ONERECORD_ST;
typedef struct
{
    VOS_UINT16                              usOptionFileNum;
    VOS_UINT16                              aucOptionFilelist[USIMM_INIT_OFILE_MUX_NUM];
}USIMM_POOL_OPTION_FILE_CFG_ST;


typedef struct
{
    USIMM_POOL_ONERECORD_ST                 astpoolRecord[USIMM_POOL_MAX_NUM];  /* �ļ��صļ�¼���� */
    USIMM_POOLSTATUS_ENUM_UINT32            enPoolStatus;                       /* �ļ��ص�״̬ */
    VOS_UINT8                               ucPoolFileCount;                    /* �ļ����ļ����� */
    VOS_UINT8                               aucReserved[3];
}USIMM_POOL_ST;


typedef VOS_UINT32 (*PUSIMMAPPPROC)(USIMM_CMDHEADER_REQ_STRU * pMsg);

typedef struct
{
    USIMM_CMDTYPE_REQ_ENUM_UINT32           enMsgType;        /* ��ϢID */
    PUSIMMAPPPROC                           pProcFun;        /* ������ */
}USIMMAPP_FUNCLIST_ST;

typedef struct
{
    USIMM_LOG_STATE_ENUM_UINT32             enLogState;
    VOS_UINT32                              ulDataLen;
    VOS_UINT8                               *pucData;
}USIMM_LOG_DATA_STRU;

typedef struct
{
    VOS_UINT32                              ulCurFile;
    VOS_CHAR                                aucFileName[USIMM_LOG_FILE_MAX_NUM][USIMM_LOG_FILE_NAME_LEN];
}USIMM_LOG_CTRLFILE_STRU;
typedef struct
{
    USIMM_DEF_FILEID_ENUM_UINT32        enDefFileID;
    VOS_UINT32                          ulService;
}USIMM_OPFILE_LIST_STRU;

/*****************************************************************************
�ṹ��    : USIMM_TERMINAL_POWER_SUPPLY_STRU
�ṹ˵��  : �ն˵�ѹ��Ӧ�ṹ����ӦЭ��102.221��11.1.19.2.1
*****************************************************************************/
typedef struct
{
    VOS_UINT8                          ucTag;              /* terminal power supply ��tag:0x80 */
    VOS_UINT8                          ucLen;              /* ���� */
    VOS_UINT8                          ucActSupVolCla;     /* ʵ��ʹ�õĹ����ѹ�ȼ� */
    VOS_UINT8                          ucMaxAvaPower;      /* �ն��������õ�ѹ��Ӧ */
    VOS_UINT8                          ucActFre;           /* ʵ��ʹ�õ�ʱ��Ƶ�� */
}USIMM_TERMINAL_POWER_SUPPLY_STRU;

/*****************************************************************************
�ṹ��    : USIMM_EXT_LOG_CHANNEL_SUPPORT_STRU
�ṹ˵��  : �ն˵�ѹ��Ӧ�ṹ����ӦЭ��102.221��11.1.19.2.2
*****************************************************************************/
typedef struct
{
    VOS_UINT8                          ucTag;              /* extended logical channel terminal support��tag:0x81 */
    VOS_UINT8                          ucLen;              /* ���� */
}USIMM_EXT_LOG_CHANNEL_SUPPORT_STRU;

/*****************************************************************************
�ṹ��    : USIMM_ADDITIONAL_INTERFACES_SUPPORT_STRU
�ṹ˵��  : �ն˵�ѹ��Ӧ�ṹ����ӦЭ��102.221��11.1.19.2.3
*****************************************************************************/
typedef struct
{
    VOS_UINT8                          ucTag;              /* the additional interface support��tag:0x82 */
    VOS_UINT8                          ucLen;              /* ���� */
    VOS_UINT8                          ucAddInterface;     /* ���ӽӿ� */
}USIMM_ADDITIONAL_INTERFACES_SUPPORT_STRU;

/*****************************************************************************
�ṹ��    : USIMM_CARD_INIT_INFO_LOG_STRU
�ṹ˵��  : ����ʼ���׶ε���Ϣ��¼
*****************************************************************************/
typedef struct
{
    USIMM_PROFILE_DOWNLOAD_ENUM_UINT8  enTPDownloadStatus;    /* terminal profile�Ƿ��·�ʧ�� */
    USIMM_ECC_INIT_STATUS_ENUM_UINT8   enEccInitStatus;       /* ECC�ļ���ʼ��״̬ */
    VOS_UINT8                          ucVoltageSwitchFlag;   /* ��ѹ�Ƿ��л� */
    VOS_UINT8                          ucVoltageMismatchFlag; /* ��ѹ��ƥ���� */
}USIMM_CARD_INIT_RECORD_STRU;

typedef struct
{
    VOS_UINT8                          ucInsertPoolFailFlag;  /* �ļ����뻺���ʧ�ܱ�� */
    USIMM_CARD_INIT_RECORD_STRU        stUSIMMInfo;
}USIMM_CARD_INIT_INFO_LOG_STRU;

typedef struct
{
    USIMM_CARDAPP_ENUM_UINT32           enAppType;
    USIMM_PHYCARD_TYPE_ENUM_UINT32      enCardType;
    USIMM_FILE_NEED_FCP_ENUM_UINT32     enEfFcpFlag;
}USIMM_SELECT_PARA_STUR;

typedef struct
{
    USIMM_CARDAPP_ENUM_UINT32           enAppType;
    USIMM_FILEPATH_INFO_STRU            stFilePath;
    VOS_UINT8                           ucRecordNum;
    VOS_UINT8                           aucRsv[3];
}USIMM_GET_COMM_FILE_STRU;

#if (FEATURE_VSIM == FEATURE_ON)
typedef struct
{
    VOS_CHAR                                *pcVSIMName;
    VOS_UINT16                              usFileID;
    USIMM_FILE_ATTR_ENUM_UINT8              enFileAttr;
    USIMM_VSIM_AC_ENUM_UINT8                enFileAC;
}USIMM_VSIM_FILE_INFO_STRU;

typedef struct
{
    VOS_UINT32                              ulLen;
    VOS_UINT8                               aucData[USIMM_VSIM_SECUR_MAX_LEN * 2];
}USIMM_VSIM_BASE16_DATA_STRU;

typedef struct
{
    VOS_UINT8                               ucKILen;
    VOS_UINT8                               ucOpcLen;
    USIMM_VSIM_AUTH_ENUM_UINT8              enAuthType;
    VOS_UINT8                               ucRfu;
    VOS_UINT8                               aucKi[USIMM_VSIM_SECUR_MAX_LEN];
    VOS_UINT8                               aucOpc[USIMM_VSIM_SECUR_MAX_LEN];
    VOS_UINT8                               aucSimKeyHash[USIMM_VSIM_SIM_KEY_HASH_LEN];
    USIMM_VSIM_BASE16_DATA_STRU             stBase16Ki;
    USIMM_VSIM_BASE16_DATA_STRU             stBase16Opc;
}USIMM_VSIM_AUTH_INFO_STRU;
#endif

#if(FEATURE_ON == FEATURE_PTM)
/*****************************************************************************
 �ṹ����  : USIMM_MNTN_STATE_ERROR_EVENT_STRU
 �ṹ˵��  : USIMM ERROR LOG�ϱ��ṹ
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                          stHeader;
    USIMM_MNTN_STATE_ERROR_REASON_ENUM_UINT32       enStateErrorReason;     /*���쳣ԭ��*/
    SCI_RECORD_INFO_S                               stSCIRecordInfo;        /*SCI�����쳣��Ϣ*/
    VOS_UINT32                                      aulRsv[4];              /*������չ�ֶ� */
}USIMM_MNTN_STATE_ERROR_EVENT_STRU;
#endif

/*****************************************************************************
 �ṹ��    : USIMM_CHANNEL_INFO_STRU
 �ṹ˵��  : USIMģ��CHANNEL INFO�����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulRspLen;                               /* GetResponse���� */
    VOS_UINT32                          ulAIDFcpLen;
    VOS_UINT8                           aucRspContent[USIMM_APDU_MAXLEN];   /* GetResponse������ */
    VOS_UINT8                           aucAIDFcp[USIMM_APDU_MAXLEN];
}USIMM_CHANNEL_RESPONSE_STRU;

/*****************************************************************************
 �ṹ��    : USIMM_APP_PIN_INFO_STRU
 �ṹ˵��  : PIN����Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                               ucPINRefNum;
    VOS_UINT8                               ucPinRemainTime;            /* PIN��ʣ�����      */
    VOS_UINT8                               ucPukRemainTime;            /* PUK��ʣ�����      */
    VOS_UINT8                               ucPINLen;                   /* aucPin�������Ƿ���Ч */
    USIMM_PIN_ENABLE_STATUS_ENUM_UINT32     enPinEnable;                /* PIN����״̬        */
    USIMM_PIN_VERIY_STATUS_ENUM_UINT32      enPinVerified;              /* PIN��֤״̬        */
    VOS_UINT8                               aucPin[USIMM_PINNUMBER_LEN];/* PIN������ɹ����¼�µ�ǰPIN�� */
}USIMM_APP_PIN_INFO_STRU;

/*****************************************************************************
 �ṹ��    : USIMM_UICC_ADF_INFO_STRU
 �ṹ˵��  : ADF��Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                              ulAIDLen;                   /* ��ǰ��AID���� */
    VOS_UINT8                               aucAID[USIMM_AID_LEN_MAX];  /* ��ǰAID���� */
    VOS_UINT8                               ucCharaByte;
    VOS_UINT8                               ucSupCmd;
    VOS_UINT16                              usFcpLen;
}USIMM_UICC_ADF_INFO_STRU;

/*****************************************************************************
 �ṹ��    : USIMM_COMM_PIN_INFO_STRU
 �ṹ˵��  :��Ӧ�õ�PIN��Ϣ
*****************************************************************************/
typedef struct
{
    USIMM_PIN_TYPE_ENUM_UINT32              enCurPINType;       /* ��ǰ�������� */
    USIMM_COMM_PIN_ENUM_UINT32              enPinKeyRef;        /* PIN1���KeyReference */
    USIMM_APP_PIN_INFO_STRU                 stPin2Info;         /* PIN2����Ϣ */
}USIMM_COMM_PIN_INFO_STRU;

/*****************************************************************************
 �ṹ��    : USIMM_COMM_CARD_APP_INFO_STRU
 �ṹ˵��  : ��Ӧ����Ϣ
*****************************************************************************/
typedef struct
{
    USIMM_CARDAPP_ENUM_UINT32               enAppType;          /* ��ǰӦ��ʹ�õ����� */
    USIMM_CARD_SERVIC_ENUM_UINT32           enAppService;       /* ��ǰ����״̬ */
    USIMM_SIM_PHASE_ENUM_UINT32             enSimPhase;         /* ָʾSIM���Ľ׶� */
    USIMM_CURFILEINFO_ST                    stCurFileInfo;      /* ��ǰ�ļ���Ϣ */
    USIMM_UICC_ADF_INFO_STRU                stAdfInfo;          /* ��ǰӦ�õ�UICC��Ϣ */
    USIMM_COMM_PIN_INFO_STRU                stPinInfo;          /* ��ǰӦ�õ�PIN��Ϣ */
    USIMM_FDNSTATUS_ENUM_UINT32             enFDNStatus;        /* ��ǰFDN״̬ */
    USIMM_BDNSTATUS_ENUM_UINT32             enBDNStatus;        /* ��ǰBDN״̬ */
}USIMM_COMM_CARD_APP_INFO_STRU;

/*****************************************************************************
 �ṹ��    : PUSIMPROTECTPROC
 �ṹ˵��  : �����Ը�λ����ָ������
*****************************************************************************/
typedef VOS_UINT32 (*PUSIMPROTECTPROC)(VOS_VOID);

/*****************************************************************************
  5 ȫ�ֱ�������
*****************************************************************************/
#if(FEATURE_ON == FEATURE_PTM)
extern USIMM_MNTN_STATE_ERROR_EVENT_STRU    g_stCardErrorLog;

extern NV_ID_ERR_LOG_CTRL_INFO_STRU         g_stErrLogCtrlInfo;
#endif

extern USIMM_BASE_INFO_ST                    gstUSIMMBaseInfo;

extern VOS_UINT32                            gulUsimSupportIMS;

extern USIMM_ISIMUSIM_EFTBL_STRU             g_astUSIMMIsimUsimEFTBL[USIMM_ISIMEFTOUSIMEF_TBL_SIZE];

extern USIMM_DRV_INFO_ST                     gstUSIMMDrvInfo;

extern USIMM_AID_INFO_STRU                   g_astUSIMMInitAIDInfo[USIMM_CARDAPP_BUTT];

extern USIMM_LOG_DATA_STRU                   g_stUSIMMLogData;

extern VOS_UINT32                            g_ulUSIMMExcLogLenBK;

extern USIMM_LOG_DATA_STRU                   g_stUSIMMExcLogData;

extern USIMM_POOL_ST                         gstUSIMMPOOL;

extern VOS_UINT32                            gulUSIMMOpenSpeed;

extern VOS_UINT16                            gausInitFileOne[USIMM_INITFIRST_FILENUM];

extern USIMM_OPFILE_LIST_STRU gastSimInitOFile[USIMM_INITSIM_OFILENUM];

extern USIMM_OPFILE_LIST_STRU gastUsimInitOFile[USIMM_INITUSIM_OFILENUM];

extern USIMM_DEF_FILEID_ENUM_UINT32 g_aulAttUsimInitFile[USIMM_USIM_ATT_INITFILE_NUM];

extern USIMM_DEF_FILEID_ENUM_UINT32 g_aulAttSimInitFile[USIMM_SIM_ATT_INITFILE_NUM];

extern USIMM_FEATURE_CFG_STRU       g_stUsimmFeatureCfg;

extern VOS_UINT32                   g_ulATTSpecErrSWCnt;

extern USIMM_CHANNEL_RESPONSE_STRU  g_astUSIMMChGetRsp[USIMM_CHANNEL_NUMBER_MAX];

extern USIMM_CARD_INIT_INFO_LOG_STRU       g_stUSIMMInitInfo;

extern USIMM_DL_T_MODE_ENUM_UINT32         g_enUSIMMTMode;
extern VOS_BOOL                            g_bSendIFSReqFlag;

extern USIMM_TEST_PHYCARD_TYPE_ENUM_UINT32 g_enTestCardType;

extern USIMM_APP_PIN_INFO_STRU             g_astUSIMMAppPIN1Info[USIMM_KEY_REF_PIN_BUTT];

extern VOS_UINT8                        g_ucStoreEsMeidResult;

#if (FEATURE_VSIM == FEATURE_ON)
extern USIMM_VSIM_AUTH_INFO_STRU        g_stUSIMMVSimAuthInfo;

extern USIMM_VSIM_FILE_INFO_STRU        g_astUSIMMVSimFileInfo[];

extern VOS_CHAR                         *g_pcUSIMMVSimXmlFilePath;

extern VOS_UINT8                        *g_pucUSIMMVsimData ;
#endif

extern USIMM_FILEID_PATHSTR_TABLE_STRU g_stUSIMMFilePathTable[USIMM_DEF_FILEID_BUTT];

/*****************************************************************************
  6 Function����
*****************************************************************************/
#ifdef  USIMM_DEBUG_PEINT
#define USIMM_NORMAL                0
#define USIMM_INFO                  1
#define USIMM_WARNING               2
#define USIMM_ERROR                 3

#define USIMM_NORMAL_LOG(string)    USIMM_PRINT(USIMM_NORMAL,string)
#define USIMM_INFO_LOG(string)      USIMM_PRINT(USIMM_INFO,string)
#define USIMM_WARNING_LOG(string)   USIMM_PRINT(USIMM_WARNING,string)
#define USIMM_ERROR_LOG(string)     USIMM_PRINT(USIMM_ERROR,string)
#else
#define USIMM_NORMAL_LOG(string)    PS_LOG(WUEPS_PID_USIM, 0, PS_PRINT_NORMAL, string)
#define USIMM_INFO_LOG(string)      PS_LOG(WUEPS_PID_USIM, 0, PS_PRINT_INFO, string)
#define USIMM_WARNING_LOG(string)   PS_LOG(WUEPS_PID_USIM, 0, PS_PRINT_WARNING, string)
#define USIMM_ERROR_LOG(string)     PS_LOG(WUEPS_PID_USIM, 0, PS_PRINT_ERROR, string)
#endif
VOS_UINT32 USIMM_UiccProtectReactiveChannels(VOS_VOID);

extern VOS_VOID USIMM_LogDataClear(VOS_VOID);

extern VOS_UINT32 USIMM_CdmaSpecAuthHandle(
    USIMM_CMDHEADER_REQ_STRU            *pMsg);

extern VOS_UINT32 USIMM_RAccessPathHandle(
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    VOS_UINT16                          usFileID,
    VOS_UINT8                           ucPathLen,
    VOS_UINT16                         *pusPath,
    USIMM_RESTRIC_CMD_ENUM_UINT32       ulCmdType);

extern VOS_UINT32 USIMM_RAccessHandle(
    USIMM_CMDHEADER_REQ_STRU            *pMsg);

extern VOS_UINT32 USIMM_RefreshHandle(
    USIMM_CMDHEADER_REQ_STRU                *pMsg);

extern VOS_VOID USIMM_ChangePathToU16(
    VOS_UINT32                              ulDataLen,
    VOS_UINT8                               *pucData,
    VOS_UINT32                              *pulLen,
    VOS_UINT16                              *pusPath);

extern VOS_UINT32 USIMM_SelectFile(
    USIMM_CARDAPP_ENUM_UINT32               enAppType,
    USIMM_FILE_NEED_FCP_ENUM_UINT32         enEfFcpFlag,
    USIMM_FILEPATH_INFO_STRU                *pstFilePath);

extern VOS_UINT32  USIMM_GetDefTFMem(
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    USIMM_DEF_FILEID_ENUM_UINT32        enDefFileId,
    VOS_UINT16                         *pusReadLen,
    VOS_UINT8                          **pucData);

extern VOS_UINT32  USIMM_GetTFByDefFID(
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    USIMM_DEF_FILEID_ENUM_UINT32        enDefFileId,
    VOS_UINT16                          usReadLen,
    VOS_UINT8                          *pucData);

extern VOS_UINT32  USIMM_WriteTFFileByDefID(
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    USIMM_DEF_FILEID_ENUM_UINT32        enDefFileId,
    VOS_UINT16                          usDataLen,
    VOS_UINT8                          *pucData);

extern VOS_VOID USIMM_PRINT(
    VOS_UINT32                          ulPrintLev,
    VOS_INT8                            *pucString);

extern VOS_UINT32 USIMM_SelectDFFile(
    VOS_UINT16                          usFileId,
    USIMM_SELECT_PARA_STUR              *pstSelectPara,
    USIMM_CURFILEINFO_ST                *pstCurFileInfo);

extern VOS_UINT32 USIMM_SelectEFByID(
    VOS_UINT16                          usFileId,
    USIMM_SELECT_PARA_STUR              *pstSelectPara,
    USIMM_CURFILEINFO_ST                *pstCurFileInfo);

extern VOS_UINT32 USIMM_SelectFileWithPath(
    USIMM_SELECT_PARA_STUR             *pstSelectPara,
    USIMM_U16_LVDATA_STRU              *pstFilePath,
    USIMM_CURFILEINFO_ST               *pstCurFileInfo,
    VOS_UINT16                         *pusCurPathLen
);

extern VOS_UINT32 USIMM_ReadLFFile(
    USIMM_CARDAPP_ENUM_UINT32            enAppType,
    USIMM_EFFCP_ST                      *pstCurEFFcp,
    VOS_UINT8                            ucRecordNum,
    VOS_UINT8                           *pucContent);

extern VOS_UINT32 USIMM_STATUSProc(VOS_VOID);

extern VOS_UINT32 USIMM_VerifyNCK(
    VOS_UINT8                           ucLen,
    VOS_UINT8                           *pucPassword);

extern VOS_UINT32 USIMM_VerifyPCK(
    VOS_UINT8                           ucLen,
    VOS_UINT8                           *pucPassword);

extern VOS_UINT32 USIMM_ChangePIN(
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    USIMM_PIN_TYPE_ENUM_UINT32          enPINType,
    VOS_UINT8                           *pucOldPIN,
    VOS_UINT8                           *pucNewPIN);

extern VOS_UINT32 USIMM_UnblockPIN(
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    USIMM_PIN_TYPE_ENUM_UINT32          enPINType,
    VOS_UINT8                           *pucPUK,
    VOS_UINT8                           *pucNewPIN);

extern VOS_UINT32 USIMM_PINVerify(
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    USIMM_PIN_TYPE_ENUM_UINT32          enPINType,
    VOS_UINT8                           ucPINCmd,
    VOS_UINT8                           *pucPIN);

extern VOS_UINT32 USIMM_InitUsimFDNBDNStatus(VOS_VOID);

extern VOS_VOID USIMM_FdnCapabilityRequest(
    USIMM_FDNSTATUS_ENUM_UINT32         *pulFdnStatus);

extern VOS_VOID USIMM_BdnCapabilityRequest(
    USIMM_BDNSTATUS_ENUM_UINT32         *pulBdnStatus);

extern VOS_UINT32 USIMM_SimFDNBDNProcess(VOS_VOID);

extern VOS_UINT32 USIMM_UICCFDNEnable(
    USIMM_CARDAPP_ENUM_UINT32           enAppType);

extern VOS_UINT32 USIMM_ICCFDNEnable(
    USIMM_CARDAPP_ENUM_UINT32           enAppType);

extern VOS_UINT32 USIMM_UICCFDNDisable(
    USIMM_CARDAPP_ENUM_UINT32           enAppType);

extern VOS_UINT32 USIMM_ICCFDNDisable(
    USIMM_CARDAPP_ENUM_UINT32           enAppType);

extern VOS_VOID USIMM_FDNEstChgInd(VOS_VOID);

extern VOS_UINT32 USIMM_FindTagInBERTLV(
    VOS_UINT8                           *pucDataBuf,
    VOS_UINT8                           ucTag,
    VOS_UINT32                          ulDataLen);

extern VOS_UINT32 USIMM_FindTagInSMPTLV(
    VOS_UINT8                           *pucDataBuf,
    VOS_UINT8                           ucTag,
    VOS_UINT32                          ulDataLen);

extern VOS_UINT32 USIMM_FindTagInCTLV(
    VOS_UINT8                           *pucDataBuf,
    VOS_UINT8                           ucTag,
    VOS_UINT32                          ulDataLen);

extern VOS_UINT32 USIMM_GetBitFromBuf(
    VOS_UINT8                           *pucDataBuf,
    VOS_UINT32                          ulBitNo,
    VOS_UINT32                          ulBufLen);

extern VOS_UINT32 USIMM_DecodeEFFcp(
    USIMM_PHYCARD_TYPE_ENUM_UINT32      enCurCardType,
    USIMM_APDU_RSP_STRU                 *pstApduRspData,
    USIMM_CURFILEINFO_ST                *pstCurFileInfo);

extern VOS_UINT32 USIMM_DecodeDFFcp(
    USIMM_PHYCARD_TYPE_ENUM_UINT32      enCurCardType,
    USIMM_APDU_RSP_STRU                 *pstApduRspData,
    USIMM_CURFILEINFO_ST                *pstCurFileInfo);

extern VOS_UINT32 USIMM_DecodeFileFcp(
    USIMM_PHYCARD_TYPE_ENUM_UINT32      enCardType,
    USIMM_U16_LVDATA_STRU               *pstFilePath,
    USIMM_APDU_RSP_STRU                 *pstApduRspData,
    USIMM_CURFILEINFO_ST                *pstCurFileInfo);

extern VOS_VOID USIMM_ReportEvent(
    VOS_UINT16                          usEventId);

extern VOS_VOID USIMM_RefreshFileIndHandle(
    USIMM_STKREFRESH_REQ_STRU           *pstMsg,
    USIMM_CARDAPP_ENUM_UINT32           enAppType);

extern USIMM_REFRESH_FILE_TYPE_UINT16 USIMM_GetRefreshIndType(
    USIMM_STKREFRESH_REQ_STRU                   *pstMsg);

extern VOS_UINT32 USIMM_CardFilePathCMP(
    VOS_UINT32                          ulPath1Len,
    VOS_UINT16                          *pusPath1,
    VOS_UINT32                          ulPath2Len,
    VOS_UINT16                          *pusPath2);

extern VOS_BOOL USIMM_IsCLEnable(VOS_VOID);

extern VOS_UINT8 USIMM_GetRATMode(VOS_VOID);

extern USIMM_NV_CARDAPP_ENUM_UINT32 USIMM_GetPreferApp(VOS_VOID);

extern VOS_VOID USIMM_FileAccessFix( VOS_VOID );

extern VOS_VOID USIMM_SetAccFileAccess( VOS_VOID );

extern VOS_VOID USIMM_SetImsiFile(VOS_VOID);

extern VOS_UINT32 USIMM_IS_EF_FILE(
    VOS_UINT16                          usFileId);

extern VOS_UINT32 USIMM_GetFreeAppInfo(
    VOS_UINT32                          *pulIndex);

extern VOS_UINT32 USIMM_SelectAIDFile(
    VOS_UINT8                           ucChannelNo,
    USIMM_SELECT_P2_PARA_ENUM_UINT8     enMode,
    USIMM_AID_INFO_STRU                *pstAIDInfo,
    USIMM_APDU_RSP_STRU                *pstApduRsp
);

extern VOS_UINT32 USIMM_CloseChannel(
    VOS_UINT8                           ucChannelID);

extern VOS_UINT32 USIMM_OpenChannel(
    VOS_UINT8                           *pucChannelNo);

extern VOS_BOOL USIMM_SearchAllAID(
    VOS_UINT32                          ulAIDLen,
    VOS_UINT8                           *pucAID,
    VOS_UINT8                           *pucChannelNo);

extern VOS_VOID USIMM_RecordCardErrorLog(
    USIMM_MNTN_STATE_ERROR_REASON_ENUM_UINT32                   enErrorReason,
    USIMM_MNTN_ERROR_LEVEL_ENUM_UINT16                          enAlmLevel);

extern VOS_UINT32 USIMM_MakeCHAPCmdData(
    USIMM_COMPUTEIP_CHAP_STRU	        *pstChapData,
    USIMM_U8_DATA_STRU                  *pstCmdData);

extern VOS_UINT32 USIMM_MakeMNHACmdData(
    USIMM_COMPUTEIP_MNHA_STRU	        *pstMNHAData,
    USIMM_U8_DATA_STRU                  *pstCmdData);

extern VOS_UINT32 USIMM_MakeMIPCmdData(
    USIMM_COMPUTEIP_MIPRRQHASH_STRU     *pstMIPData,
    USIMM_U8_DATA_STRU                  *pstCmdData);

extern VOS_UINT32 USIMM_MakeMNAAACmdData(
    USIMM_COMPUTEIP_MNAAA_STRU	        *pstMNAAAData,
    USIMM_U8_DATA_STRU                  *pstCmdData);

extern VOS_UINT32 USIMM_MakeHRPDCmdData(
    USIMM_COMPUTEIP_HRPD_STRU	        *pstHRPDData,
    USIMM_U8_DATA_STRU                  *pstCmdData);

extern VOS_UINT32 USIMM_CdmaSpecAuthComputeIP(
    VOS_UINT8                           ucChannelID,
    USIMM_CMDHEADER_REQ_STRU            *pstMsgHeader,
    USIMM_COMPUTEIP_AUTH_STRU			*pstComputeIP);

extern VOS_UINT32 USIMM_CdmaSpecAuthComputeIP(
    VOS_UINT8                           ucChannelID,
    USIMM_CMDHEADER_REQ_STRU            *pstMsgHeader,
    USIMM_COMPUTEIP_AUTH_STRU			*pstComputeIP);

extern VOS_UINT32 USIMM_MakeRetrieveSKData(
    USIMM_BCMCS_RETRIEVESK_STRU	        *pstRetrieveSK,
    USIMM_U8_DATA_STRU                  *pstCmdData);

extern VOS_UINT32 USIMM_MakeUpdateBAKData(
    USIMM_BCMCS_UPDATABAK_STRU	        *pstUpdateBAK,
    USIMM_U8_DATA_STRU                  *pstCmdData);

extern VOS_UINT32 USIMM_MakeDeleteBAKData(
    USIMM_BCMCS_DELETEBAK_STRU	        *pstDeleteBAK,
    USIMM_U8_DATA_STRU                  *pstCmdData);

extern VOS_UINT32 USIMM_MakeReSRTPData(
    USIMM_BCMCS_RETRIEVE_SRTPSK_STRU	*pstReSRTPSK,
    USIMM_U8_DATA_STRU                  *pstCmdData);

extern VOS_UINT32 USIMM_MakeGenAuthData(
    USIMM_BCMCS_GENAUTH_SIGN_STRU	    *pstGenAuthSign,
    USIMM_U8_DATA_STRU                  *pstCmdData);

extern VOS_UINT32 USIMM_MakeBCMCSAuthData(
    USIMM_BCMCS_AUTHENTICATION_STRU	    *pstAuthentication,
    USIMM_U8_DATA_STRU                  *pstCmdData);

extern VOS_UINT32 USIMM_CdmaSpecAuthBCMCS(
    VOS_UINT8                           ucChannelID,
    USIMM_CMDHEADER_REQ_STRU            *pstMsgHeader,
    USIMM_BCMCS_DATA_STRU				*pstBCMCS);

extern VOS_UINT32 USIMM_CdmaSpecAuthApp(
    VOS_UINT8                           ucChannelID,
    USIMM_CMDHEADER_REQ_STRU            *pstMsgHeader,
    USIMM_CDMAAPP_AUTH_STRU				*pstAppAuth);

extern VOS_VOID USIMM_CheckTimeOutError(VOS_VOID);

/*POOL��������*/

extern VOS_UINT32 USIMM_VsimPoolSearchFile(
    VOS_UINT16                          usFileId,
    VOS_UINT32                          *pulData);

extern VOS_UINT32 USIMM_PoolFindFile(
    VOS_UINT16                          usEFileId,
    VOS_UINT32                         *pulPoolIndex,
    USIMM_CARDAPP_ENUM_UINT32           enAppType);

extern VOS_UINT32 USIMM_PoolInsertOneFile(
    USIMM_POOL_ONERECORD_ST             *pstRecord);

extern VOS_UINT32 USIMM_PoolUpdateOneFile(
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    VOS_UINT16                          usFileID,
    VOS_UINT32                          ulNewLen,
    VOS_UINT8                           *pucNewData);

extern VOS_UINT32 USIMM_InsertFileToPool(
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    USIMM_DEF_FILEID_ENUM_UINT32        enFileID);

extern VOS_UINT32 USIMM_PoolDelOneFile(
    VOS_UINT16                          usFileId,
    USIMM_CARDAPP_ENUM_UINT32           enAppType);

extern VOS_UINT32 USIMM_PoolReadOneFile(
    VOS_UINT16                          usFileId,
    VOS_UINT16                          usLen,
    VOS_UINT8                          *pucData,
    USIMM_CARDAPP_ENUM_UINT32           enAppType);

extern VOS_UINT32 USIMM_PoolDelFilesByAppType(
    USIMM_CARDAPP_ENUM_UINT32           enAppType);

extern VOS_VOID USIMM_PoolDelAll(VOS_VOID);

extern VOS_VOID USIMM_PoolDelOneRecByIndex(
    VOS_UINT32                          ulIndex);

extern VOS_VOID USIMM_PoolInsertOneRecByIndex(
    VOS_UINT32                           ulIndex,
    USIMM_POOL_ONERECORD_ST             *pstRecord
);
extern VOS_VOID USIMM_ClearCurDFInfo(
    USIMM_CURFILEINFO_ST                *pstCurFileInfo);

extern VOS_VOID USIMM_ClearCurEFInfo(
    USIMM_CURFILEINFO_ST                *pstCurFileInfo);

extern VOS_VOID USIMM_ClearCurFileInfo(
    USIMM_CARDAPP_ENUM_UINT32           enCardApp);

extern VOS_VOID USIMM_SaveDFPinInfo(VOS_VOID);

extern VOS_VOID USIMM_OpenSpeedFileInit(VOS_VOID);

extern VOS_UINT32 USIMM_InitProfileStep(VOS_VOID);

extern VOS_UINT32 USIMM_InitCardOptionalFile(
    USIMM_CMDHEADER_REQ_STRU            *pMsg);

extern VOS_VOID USIMM_AttUpdataSupportTable(
    VOS_UINT8                           ucChannelID);

extern VOS_VOID USIMM_AttEfTerminalSupportTableValueGet(
    VOS_UINT8                           *pucValue);

extern VOS_UINT32 USIMM_InitUsimEccFile(VOS_VOID);

extern VOS_UINT32 USIMM_InitSimEccFile(
    VOS_UINT8                           ucChannelID);

extern VOS_UINT32 USIMM_SelectFileNoPath(
    USIMM_SELECT_PARA_STUR              *pstSelectPara,
    USIMM_U16_LVDATA_STRU               *pstFilePath,
    USIMM_CURFILEINFO_ST                *pstCurFileInfo,
    VOS_UINT16                          *pusCurPathLen);

extern VOS_UINT32 USIMM_SelectFileByPath(
    USIMM_SELECT_PARA_STUR              *pstSelectPara,
    USIMM_U16_LVDATA_STRU               *pstFilePath,
    USIMM_CURFILEINFO_ST                *pstCurFileInfo);

extern VOS_UINT32 USIMM_SelectFileByRelativePath(
    USIMM_SELECT_PARA_STUR              *pstSelectPara,
    USIMM_U16_LVDATA_STRU               *pstFilePath,
    USIMM_CURFILEINFO_ST                *pstCurFileInfo);

extern VOS_VOID USIMM_UpdateFilePath(
    USIMM_SELECT_PARA_STUR              *pstSelectPara,
    USIMM_U16_LVDATA_STRU               *pstFilePath,
    USIMM_CURFILEINFO_ST                *pstUSIMMCurFileInfo);

extern VOS_VOID USIMM_UpdateFileByRelativePath(
    USIMM_SELECT_PARA_STUR              *pstSelectPara,
    USIMM_U16_LVDATA_STRU               *pstFilePath,
    USIMM_CURFILEINFO_ST                *pstUSIMMCurFileInfo);

extern VOS_VOID USIMM_SciDataHook(
    VOS_UINT32                          ulLength,
    VOS_UINT8                           *pucData);

extern USIMM_CARDAPP_ENUM_UINT32 USIMM_GetAIDType(
    VOS_UINT32                          ulAidLen,
    VOS_UINT8                           *pucAid);

extern VOS_VOID USIMM_RefreshNoFileIndHandle(
    USIMM_STKREFRESH_REQ_STRU           *pstMsg);

extern VOS_VOID USIMM_RefreshInd(
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    USIMM_STKREFRESH_REQ_STRU          *pstMsg);

extern VOS_UINT32 USIMM_UsimRefreshFilePbAppCheck(
    VOS_UINT16                          *pusFilePath,
    VOS_UINT32                          ulPathLen);

extern VOS_VOID USIMM_RefreshIsimFileIndHandle(
    USIMM_STKREFRESH_IND_STRU           *pstRefreshMsg);

extern VOS_UINT32 USIMM_GetEFPathFromFList(
    VOS_UINT8                          *pucFileList,
    VOS_UINT32                          ulFileLen,
    USIMM_FILEPATH_INFO_STRU           *pstFilePath,
    VOS_UINT32                         *pulLen);

extern VOS_UINT32 USIMM_RefreshNoReset(
    USIMM_STKREFRESH_REQ_STRU           *pstMsg);

extern VOS_UINT32 USIMM_RefreshUICCFile(
    USIMM_STKREFRESH_REQ_STRU           *pstMsg);

extern VOS_UINT32 USIMM_RefreshICCFile(
    USIMM_STKREFRESH_REQ_STRU           *pstMsg);

extern VOS_VOID USIMM_RefreshCardFile(
    USIMM_STKREFRESH_REQ_STRU           *pstMsg,
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    VOS_BOOL                            bUpdatePool);

extern VOS_VOID USIMM_SendRefreshTR(
    USIMM_STKREFRESH_REQ_STRU           *pstMsg,
    VOS_UINT32                          ulResult);

extern VOS_UINT32 USIMM_SelectFileByDefFileId(
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    USIMM_FILE_NEED_FCP_ENUM_UINT32     enEfFcpFlag,
    USIMM_DEF_FILEID_ENUM_UINT32        enDefFileId
);

/*log����ӿ�*/
extern VOS_VOID USIMM_InitLogFile(VOS_VOID);

extern VOS_VOID USIMM_SaveLogFile(VOS_VOID);

extern VOS_VOID USIMM_LogDataSave(
    VOS_UINT8                           *pucData,
    VOS_UINT8                           ucDataLen);

extern VOS_VOID USIMM_ExcLogDataClear(VOS_VOID);

extern VOS_VOID USIMM_ExcLogDataSave(
    VOS_UINT8                           *pucData,
    VOS_UINT8                           ucDataLen);

extern VOS_VOID USIMM_ExcLogDataBK(VOS_VOID);

extern VOS_VOID USIMM_ExcLogDataRE(VOS_VOID);

extern VOS_VOID USIMM_SaveExcLogFile(VOS_VOID);

extern VOS_VOID USIMM_InitExcLogFile(VOS_VOID);

/*Base Func*/
extern VOS_UINT32  USIMM_PinStatusCheck(
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    USIMM_PIN_CMD_TYPE_ENUM_UINT32      enCmdType,
    USIMM_PIN_TYPE_ENUM_UINT32          enPINType,
    VOS_UINT32                         *pulResult
);
extern VOS_UINT32 USIMM_SAT_TerminalResopnse(
    USIMM_CMDHEADER_REQ_STRU            *pMsg);

extern VOS_UINT32 USIMM_SAT_Envelope(
    USIMM_CMDHEADER_REQ_STRU            *pMsg);

extern VOS_UINT32 USIMM_PINHandle(
    USIMM_CMDHEADER_REQ_STRU            *pMsg);

extern VOS_UINT32 USIMM_CheckChangeCardByICCID(VOS_VOID);

extern VOS_UINT32 USIMM_PinPreProcHandle(
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    USIMM_PINHANDLE_REQ_STRU           *pstMsg
);

extern VOS_UINT32 USIMM_PinHandleCardStatusCheck(
    USIMM_CARDAPP_ENUM_UINT32           enAppType);

extern VOS_VOID USIMM_BuildPrePinInfo(
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    USIMM_PIN_INFO_STRU                *pstPINInfo
);

extern VOS_UINT32 USIMM_ProtectReset(
    USIMM_CMDHEADER_REQ_STRU            *pstMsg);

extern VOS_UINT32 USIMM_ProtectResetProc(
    USIMM_PHYCARD_TYPE_ENUM_UINT32      enCardType);

extern VOS_UINT32 USIMM_UiccProtectResetProc(VOS_VOID);

extern VOS_UINT32 USIMM_IccProtectResetProc(VOS_VOID);

extern VOS_UINT32 USIMM_UiccProtectResumeAppStep(VOS_VOID);

extern VOS_UINT32 USIMM_UiccProtectProfileDownloadStep(VOS_VOID);

extern VOS_UINT32 USIMM_UiccProtectFirstStep(VOS_VOID);

extern VOS_UINT32 USIMM_IccProtectFdnBdnStep(VOS_VOID);

extern VOS_UINT32 USIMM_IccProtectProfileDownloadStep(VOS_VOID);

extern VOS_UINT32 USIMM_IccProtectAutoVerifyPin(VOS_VOID);

extern VOS_UINT32 USIMM_IccProtectFirstStep(VOS_VOID);

extern VOS_UINT32 USIMM_StatusHandle(
    USIMM_CMDHEADER_REQ_STRU            *pMsg);

extern VOS_UINT32 USIMM_SetFileCommHandle(
    USIMM_UPDATEFILE_REQ_STRU           *pstUpdateMsg,
    VOS_UINT16                          usEFID);

extern VOS_UINT32 USIMM_UpdateFile(
    USIMM_EF_TYPE_ENUM_UINT32           enEFFileType,
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    VOS_UINT8                           ucRecordNum,
    VOS_UINT16                          usDataLen,
    VOS_UINT8                          *pucData);

extern VOS_UINT32 USIMM_SetSPBFileHandle(
    USIMM_CMDHEADER_REQ_STRU            *pstMsgHeader);

extern VOS_UINT32 USIMM_ChannelCmdParaCheck(
    USIMM_SENDTPDUDATA_REQ_STRU         *pstMsg);

extern VOS_VOID USIMM_SAT_Fetch(
    VOS_UINT16                          usLen);

extern VOS_UINT32 USIMM_GetRealFile(
    USIMM_READFILE_REQ_STRU             *pstReadMsg,
    VOS_UINT16                          usEFID);

extern VOS_VOID USIMM_ErrorLogProc(
    USIMM_CMDHEADER_REQ_STRU            *pMsg);

#if(FEATURE_ON == FEATURE_PTM)
extern VOS_VOID USIMM_MsgProc(
    USIMM_CMDHEADER_REQ_STRU            *pMsg);
#endif

extern VOS_UINT32 USIMM_UsimVoltageSwitch(
    VOS_UINT8                           ucCharaByte,
    VOS_UINT8                           *pucVoltageMismatchFlag);

extern VOS_VOID USIMM_UsimTerminalCapability(VOS_VOID);

extern VOS_VOID USIMM_QueryPINType(
    USIMM_APP_PIN_INFO_STRU            *pstPin1Info,
    USIMM_APP_PIN_INFO_STRU            *pstPin2Info,
    VOS_UINT8                          *pucPINType
);

extern VOS_UINT32 USIMM_HandlePINType(
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    VOS_UINT8                           ucCmdType,
    VOS_UINT32                         *pulPINType
);

extern USIMM_DEF_FILEID_ENUM_UINT32 USIMM_IsimEFIDToUsimEFID(
    USIMM_DEF_FILEID_ENUM_UINT32        enIsimID);

extern USIMM_DEF_FILEID_ENUM_UINT32 USIMM_UsimEFIDToIsimEFID(
    USIMM_DEF_FILEID_ENUM_UINT32        enUsimID);

extern VOS_UINT8 USIMM_GetMncLen(
    VOS_UINT8                           *pucAdContent,
    VOS_UINT32                          ulFileSize);

extern VOS_VOID USIMM_GetAsciiMCCAndMNC(
    VOS_UINT8                           *pucAsciiImsi,
    VOS_UINT8                           *pucAsciiMCC,
    VOS_UINT8                           *pucAsciiMNC);

extern VOS_VOID USIMM_BcdNumToAsciiNum(
    VOS_UINT8                           *pucAsciiNum,
    VOS_UINT8                           *pucBcdNum,
    VOS_UINT8                           ucBcdNumLen);

extern VOS_UINT32 USIMM_ImsiBcd2Ascii(
    VOS_UINT8                           *pucAsciiStr);

extern VOS_UINT32 USIMM_InitIsimHandle(
    USIMM_CMDHEADER_REQ_STRU            *pMsg);

extern VOS_UINT32 USIMM_GetReadFilePara(
    VOS_UINT8                           ucRecordNum,
    USIMM_EFFCP_ST                      *pstEFInfo,
    USIMM_GETCNF_INFO_STRU              *pstCnfInfo);

extern VOS_UINT32 USIMM_ReadFile(
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    USIMM_EFFCP_ST                     *pstCurEFFcp,
    USIMM_GETCNF_INFO_STRU             *pstCnfInfo);

extern VOS_UINT32 USIMM_IsSIMServiceAvailable(
    UICC_SERVICES_TYPE_ENUM_UINT32      enService);

extern VOS_UINT32 USIMM_IsUSIMServiceAvailable(
    UICC_SERVICES_TYPE_ENUM_UINT32      enService);

extern VOS_UINT32 USIMM_IsISIMServiceAvailable(
    UICC_SERVICES_TYPE_ENUM_UINT32      enService);

extern VOS_UINT32 USIMM_IsUIMServiceAvailable(
    UICC_SERVICES_TYPE_ENUM_UINT32      enService);

extern VOS_UINT32 USIMM_IsCSIMServiceAvailable(
    UICC_SERVICES_TYPE_ENUM_UINT32      enService);

extern VOS_UINT32 USIMM_GetFileFromCard(
    USIMM_GET_COMM_FILE_STRU            *pstFileInfo,
    USIMM_GETCNF_INFO_STRU              *pstCnfInfo);

extern VOS_UINT32 USIMM_CheckSetFilePara(
    USIMM_EFFCP_ST                      *pstCurEFFcp,
    VOS_UINT8                           ucRecordNum,
    VOS_UINT16                          usDataLen);

/*vSIM API*/
extern VOS_VOID USIMM_InitVsimGlobal(VOS_VOID);

extern VOS_UINT32 USIMM_SetVsimFile(
    USIMM_UPDATEFILE_REQ_STRU           *pstUpdateMsg,
    VOS_UINT16                          usEFID);

extern VOS_UINT32 USIMM_GetVsimFile(
    USIMM_READFILE_REQ_STRU             *pstReadMsg,
    VOS_UINT16                          usEFID);

extern VOS_VOID USIMM_VsimConfidentialDataVerifyErrHandle(VOS_VOID);

extern VOS_UINT32 USIMM_VsimConfidentialDataVerify(VOS_VOID);

extern VOS_UINT32 USIMM_VsimBase16Decode(
    VOS_CHAR                            *pcSrc,
    VOS_UINT32                          ulSrcLen,
    VOS_UINT8                           *pucDst,
    VOS_UINT32                          *pulDstLen);

extern VOS_VOID USIMM_VsimBase16Encode(
    VOS_UINT8                           *pucSrc,
    VOS_UINT8                           *pucDst,
    VOS_UINT32                          ulLen);

extern VOS_UINT32 USIMM_VirtualSimAuthenticationProc(
    USIMM_AUTHENTICATION_REQ_STRU       *pstMsg);

extern VOS_UINT32 USIMM_VirtualUsimAuthenticationProc(
    USIMM_AUTHENTICATION_REQ_STRU       *pstMsg);

extern VOS_UINT32 USIMM_VirtualAuthenticationProc(
    USIMM_AUTHENTICATION_REQ_STRU       *pstMsg);

extern VOS_UINT32 USIMM_DeactiveVsim(
    USIMM_MsgBlock                      *pMsg);

extern VOS_UINT32 USIMM_InitVsimCard(
    USIMM_MsgBlock                      *pMsg);

extern VOS_UINT32 USIMM_VsimGetRealKiOpc(
    VOS_UINT8                           *pucKi,
    VOS_UINT8                           *pucOpc);

extern VOS_UINT32 USIMM_CheckVsimFileInPool(VOS_VOID);

extern VOS_UINT32 USIMM_AddVsimFileToPool(
    VOS_CHAR                            *pucFileStr,
    VOS_UINT32                          ulStrLen,
    VOS_CHAR                            *pcValue,
    VOS_UINT32                          ulValueLen);

extern VOS_UINT32 USIMM_AddVsimAuthPara(
    VOS_CHAR                            *pucFileStr,
    VOS_UINT32                          ulFileLen,
    VOS_CHAR                            *pcValue,
    VOS_UINT32                          ulValueLen);

extern VOS_UINT32 USIMM_AddVsimVerifyHashPara(
    VOS_CHAR                            *pucFileStr,
    VOS_UINT32                          ulFileLen,
    VOS_CHAR                            *pcValue,
    VOS_UINT32                          ulValueLen);

extern VOS_UINT32 USIMM_DecodeVsimEf(
    OAM_XML_NODE_STRU                   *pstXmlNode);

extern VOS_VOID USIMM_VsimDecodeCardType(
    VOS_CHAR                            *pucStr,
    VOS_UINT32                          ulStrLen,
    USIMM_PHYCARD_TYPE_ENUM_UINT32      *pulCardType);

extern VOS_VOID USIMM_VsimDecodeAuthType(
    VOS_CHAR                            *pucStr,
    VOS_UINT32                          ulStrLen,
    USIMM_VSIM_AUTH_ENUM_UINT32         *pulAuthType);

extern VOS_UINT32 USIMM_DecodeVsimRoot(
    OAM_XML_NODE_STRU                   *pstXmlNode,
    USIMM_PHYCARD_TYPE_ENUM_UINT32      *pulCardType,
    USIMM_VSIM_AUTH_ENUM_UINT8          *pucAuthType);

extern VOS_UINT32 USIMM_DecodeVsimFile(
    VOS_UINT8                           *pucData);

extern VOS_UINT8* USIMM_ReadVsimFile(
    VOS_UINT32                          ulReadPID);

extern VOS_UINT32 USIMM_InitCardHandle(
    USIMM_CMDHEADER_REQ_STRU            *pMsg);

extern VOS_UINT32 USIMM_DeactiveRealCard(
    USIMM_MsgBlock                      *pMsg);

extern VOS_VOID USIMM_CardStatusRegCbFuncProc(VOS_VOID);

extern VOS_UINT32 USIMM_CardStatusHandle(
    USIMM_CMDHEADER_REQ_STRU            *pstMsg);

extern VOS_UINT32 USIMM_CheckAIDFcp(
    USIMM_SENDTPDUDATA_REQ_STRU         *pstMsg,
    USIMM_SENDTPDU_CNFINFO_STRU         *pstDataCnf);

extern VOS_UINT32 USIMM_SelectTPDUProc(
    USIMM_SENDTPDUDATA_REQ_STRU        *pstMsg,
    USIMM_APDU_RSP_STRU                *pstRspData);

extern VOS_UINT32 USIMM_GutlAuthenticationProc(
    USIMM_AUTHENTICATION_REQ_STRU       *pstMsg);

extern VOS_UINT32 USIMM_ImsAuthenticationProc(
    USIMM_AUTHENTICATION_REQ_STRU       *pstMsg);

extern VOS_UINT32 USIMM_CdmaAuthHandle(
    USIMM_AUTHENTICATION_REQ_STRU       *pstMsg);

extern VOS_UINT32 USIMM_IsimAuthenticationProc(
    USIMM_AUTHENTICATION_REQ_STRU       *pstMsg);

extern VOS_UINT32 USIMM_USIMAuthHandle(
    USIMM_AUTHENTICATION_REQ_STRU       *pstMsg);

extern VOS_UINT32 USIMM_SIMAuthHandle(
    USIMM_AUTHENTICATION_REQ_STRU       *pstMsg);

extern VOS_VOID USIMM_IsimAkaAuthRspProc(
    USIMM_AUTHENTICATION_REQ_STRU       *pstMsg,
    USIMM_APDU_RSP_STRU                 *pstRspData);

extern VOS_VOID USIMM_IsimHttpAuthRspProc(
    USIMM_AUTHENTICATION_REQ_STRU       *pstMsg,
    USIMM_APDU_RSP_STRU                 *pstRspData);

extern VOS_VOID USIMM_IsimGbaAuthRspProc(
    USIMM_AUTHENTICATION_REQ_STRU       *pstMsg,
    USIMM_APDU_RSP_STRU                 *pstRspData);

extern VOS_VOID USIMM_IsimNafAuthRspProc(
    USIMM_AUTHENTICATION_REQ_STRU       *pstMsg,
    USIMM_APDU_RSP_STRU                 *pstRspData);

extern VOS_UINT32 USIMM_AuthenticationHandle(
    USIMM_CMDHEADER_REQ_STRU            *pMsg);

extern VOS_UINT32 USIMM_BSChallengeHandle(
    USIMM_CMDHEADER_REQ_STRU            *pstMsg);

extern VOS_UINT32 USIMM_ManageSsdHandle(
    USIMM_CMDHEADER_REQ_STRU            *pMsg);

extern VOS_UINT32 USIMM_GenerateKeyVpmHandle(
    USIMM_CMDHEADER_REQ_STRU            *pMsg);

extern VOS_UINT32 USIMM_ReadFileHandle(
    USIMM_CMDHEADER_REQ_STRU            *pstMsgHeader);

extern VOS_UINT32 USIMM_UpdateFileHandle(
    USIMM_CMDHEADER_REQ_STRU            *pstMsgHeader);

extern VOS_UINT32 USIMM_FDNHandle(
    USIMM_CMDHEADER_REQ_STRU            *pMsg);

extern VOS_UINT32 USIMM_QueryFileHandle(
    USIMM_CMDHEADER_REQ_STRU            *pstMsgHeader);

extern VOS_UINT32 USIMM_SearchFileHandle(
    USIMM_CMDHEADER_REQ_STRU            *pstMsgHeader);

extern VOS_UINT32 USIMM_SendTPDUDataHandle(
    USIMM_CMDHEADER_REQ_STRU            *pstMsgHeader);

/*�ⲿ�ӿ�*/
extern VOS_VOID HPA_USIMLowPowerLock(
    VOS_UINT32                          ulPid );

extern VOS_VOID HPA_USIMLowPowerUnLock(
    VOS_UINT32                          ulPid );

extern USIMM_CARD_TYPE_ENUM_UINT32 USIMM_COMM_CardAppToType(
    USIMM_CARDAPP_ENUM_UINT32           enAppType
);

extern VOS_UINT32 USIMM_DecideTMode(
    SCI_ATRINFO_S                       *pstSCIATRInfo);

extern VOS_UINT32 USIMM_AuthenticationDataFillDataProc(
    USIMM_AUTHENTICATION_REQ_STRU      *pstMsg,
    USIMM_U8_DATA_STRU                 *pstData);

extern VOS_VOID USIMM_SendTPDUCnf(
    VOS_UINT32                          ulReceiverPid,
    VOS_UINT32                          ulSendPara,
    VOS_UINT32                          ulResult,
    USIMM_SENDTPDU_CNFINFO_STRU        *pstDataCnf,
    USIMM_CURFILEINFO_ST               *pstCurFile);

extern VOS_UINT32 USIMM_GetFileCommHandle(
    USIMM_READFILE_REQ_STRU            *pstReadMsg,
    USIMM_GETCNF_INFO_STRU             *pstCnfInfo,
    VOS_UINT16                          usEFID);

extern VOS_UINT32 USIMM_CardInOutHandle(
    USIMM_CMDHEADER_REQ_STRU           *pMsg);

extern VOS_UINT32 USIMM_OpenChannelHandle(
    USIMM_CMDHEADER_REQ_STRU            *pMsg);

extern VOS_UINT32 USIMM_CloseChannelHandle(
    USIMM_CMDHEADER_REQ_STRU            *pMsg);

extern VOS_VOID USIMM_ApplicationMsgProc(
    USIMM_CMDHEADER_REQ_STRU            *pMsg);

extern VOS_UINT32 USIMM_ISIMAuthHandle(
    USIMM_AUTHENTICATION_REQ_STRU       *pstMsg);

extern VOS_UINT32 USIMM_GetResponseTPDUProc(
    USIMM_SENDTPDUDATA_REQ_STRU        *pstMsg,
    USIMM_APDU_RSP_STRU                *pstRspData);

extern VOS_BOOL USIMM_CheckSupportAP(VOS_VOID);

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#else

#include "UsimmApi.h"
#include "UsimPsInterface.h"
#include "omnvinterface.h"
#include "NasNvInterface.h"
#include "TafNvInterface.h"
#include "OamXmlComm.h"
#include "omerrorlog.h"
#include "pamom.h"
#include "msp_diag_comm.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#if (FEATURE_VSIM == FEATURE_ON)

#define USIMM_VSIM_TYPE_STR         "TYPE"
#define USIMM_VSIM_USIM_STR         "USIM"
#define USIMM_VSIM_SIM_STR          "SIM"
#define USIMM_VSIM_AUTH_STR         "ALGORITHM"
#define USIMM_VSIM_AUTH_3G_STR      "MILENAGE"
#define USIMM_VSIM_AUTH_2GV1_STR    "COMP128V1"
#define USIMM_VSIM_AUTH_2GV2_STR    "COMP128V2"
#define USIMM_VSIM_AUTH_2GV3_STR    "COMP128V3"
#define USIMM_VSIM_KI_STR           "EFKI"
#define USIMM_VSIM_OPC_STR          "EFOPC"
#define USIMM_VSIM_VERIFY_HASH_STR  "VERIFYHASH"
#define USIMM_VSIM_NAME_STR         "NAME"
#define USIMM_VSIM_HASH_LEN         (32)

#endif

#define USIMM_CHANNEL_NUMBER_MAX        (20)

/*fid���ȼ�*/
#define MAPS_USIMM_FID_PRIORITY         VOS_PRIORITY_P1

//���ٿ�����ʼ��
#define USIMM_OPENSPEEDENABLE           0x01000101
#define USIMM_OPENSPEEDDISABLE          0x00000000

/*Ecc����*/
#define ECC_USIM                        1
#define ECC_SIM                         0

/*ATR tag*/
#define CTLV_IND_TAG                    0x80
#define CARD_SVR_TAG                    0x30
#define CARD_CPB_TAG                    0x70
#define CARD_CPB3_TAG                   0x73

/*EFDIR tag*/
#define APP_TMP_TAG                     0x61
#define APP_IND_TAG                     0x4F

#define APP_TMP_TAG_OFFSET              (0)
#define APP_IND_TAG_OFFSET              (2)
#define APP_AID_LEN_OFFSET              (3)
#define APP_AID_VALUE_OFFSET            (4)


#define USIMM_RID_LEN                   (5)
#define USIMM_APP_CODE_LEN              (2)

/*fcp tag*/
#define USIMM_FCP_TAG                   0x62
#define USIMM_FCP_FILE_DES_TAG          0x82
#define USIMM_FCP_FID_TAG               0x83
#define USIMM_FCP_NAME_TAG              0x84
#define USIMM_FCP_PRIVITE_TAG           0xA5
#define USIMM_FCP_CHARA_TAG             0x80
#define USIMM_FCP_SA_CF_TAG             0x8C
#define USIMM_FCP_SA_EF_TAG             0xAB
#define USIMM_FCP_SA_REF_TAG            0x8B
#define USIMM_FCP_PIN_TO_TAG            0xC6
#define USIMM_FCP_FILESIZE_TAG          0x80
#define USIMM_FCP_SFI_TAG               0x88
#define USIMM_FCP_PRO_INFO_TAG          0xA5
#define USIMM_FCP_LCSI_TAG              0x8A
#define USIMM_FCP_TOTAL_SIZE_TAG        0x81
#define USIMM_FCP_PINMAP_TAG            0x90
#define USIMM_FCP_PINRER_TAG            0x83
#define USIMM_FCP_PINQUALIFER_TAG       0x95
#define USIMM_FCP_SUPSYSCMD_TAG         0x87


/*Usimm DL���÷���ֵ*/
#define USIMM_DL_SUCESS                 0
#define USIMM_DL_SEND_ERROR             1
#define USIMM_DL_RECEIVE_ERROR          2

/*�ļ�������ļ���Ŀ*/
#define POOLMAXNUM                      32

/*�������ļ�������ļ��ռ�*/
#define USIMM_MAX_FILE_SIZE             0x2000

/*��ʼ���ļ�������,��Ϊ����PIN�����ģ�����PIN������Mandatory��Optional�ļ�*/
#define USIMM_INITFIRST_FILENUM        2
#define USIMM_INITSIM_MFILENUM         8
#define USIMM_INITUSIM_MFILENUM        12
#define USIMM_INITSIM_OFILENUM         12
#define USIMM_INITUSIM_OFILENUM        15

/* Optional�ļ���ʼ������ļ����� */
#define USIMM_INIT_OFILE_MUX_NUM       (16)

/* ATT�����ļ���ʼ���ļ��б��� */
#define USIMM_USIM_ATT_INITFILE_NUM     2
#define USIMM_SIM_ATT_INITFILE_NUM      1

//�ļ���ϵ��ֵ����
#define USIMM_SIMDFGSMGDF_MAX           2
#define USIMM_SIMDFTELGDF_MAX           1
#define USIMM_SIMDFCONTENT_MAX          2

#define USIMM_USIMADFGDF_MAX            4
#define USIMM_USIMADFTELGDF_MAX         2
#define USIMM_USIMDFCONTENT_MAX         3

/*��ȡ�ļ�*/
#define USIMM_READ_ALLRECORD            0

/*�жϿ���λ״̬��ѭ������*/
#define USIMM_GET_SCISTATUS_MAX         300

/*��λ����������*/
#define USIMM_RESET_CARD                0
#define USIMM_CHANGE_VCC                1

/*SCI�����������*/
#define USIMM_SCI_SUCCESS               0
#define USIMM_SCI_NONEED_CHANGEVCC      1

/*��ȡȫ���ļ�����*/
#define USIMM_READ_ALL_FILE_CONTENT     0

/*�����Ը�λ�¼�*/
#define USIMM_PROTECT_RESET             0xFF

#define USIMM_PROTECT_MAX_NUM           (3)

/*��ǰ��¼�ļ����������ṹ����ʹ����Ҫ4�ֽڶ���*/
#define USIMM_LOG_FILE_MAX_NUM          (4)

/*��ǰ��¼�ļ�����������ṹ����ʹ����Ҫ4�ֽڶ���*/
#define USIMM_LOG_FILE_NAME_LEN         (0x10)

#define USIMM_LOG_DATA_TAG              (0x5A)

#define USIMM_LOG_START_TAG             (0x5555AAAA)

/*��ǰ��¼����������Ĵ�С*/
#define USIMM_LOG_DATA_MAX_LEN          (8*1024)
#define USIMM_EXCLOG_DATA_MAX_LEN       (4*1024)

/* ATT����Support Table�ĳ��� */
#define USIMM_ATT_SUPPORT_TABLE_MAX     (16)
#define USIMM_ATT_SUPPORT_TABLE_MIN     (8)

/* ATT����Support Table�ֽ�ƫ���� */
#define USIMM_ATT_SCAN_CTRL_OFFSET          (0)
#define USIMM_ATT_NETWORK_SELECTION_OFFSET  (1)
#define USIMM_ATT_ACTING_HPLMN              (2)
#define USIMM_ATT_3G_SUPPORT                (3)
#define USIMM_ATT_RAT_BALANCING             (4)
#define USIMM_ATT_BIP_SUPPORT               (5)
#define USIMM_ATT_LTE_SUPPORT               (6)
#define USIMM_ATT_CSG_SUPPORT               (7)

/* ATT����Support Table��LTE���� */
#define USIMM_ATT_LTE_DATA_ONLY             (0x01)
#define USIMM_ATT_LTE_DATE_VOICE_CSFB       (0x02)
#define USIMM_ATT_LTE_DATE_VOICE_CSFB_IMS   (0x03)


#define USIMM_ENVELOPE_PPDOWN                (0xD1)
#define USIMM_ENVELOPE_CBDOWN                (0xD2)

/* ATR��Ϣ */
#define USIMM_ATR_MAX_LEN                   (80)
#define USIMM_ATR_T0_OFFSET                 (1)

/* �߼�ͨ�������� */
#define USIMM_CHANNEL_NUM_MAX               (4)

/* Session ID���ֵ */
#define USIMM_SESSION_ID_MAX                (0x7fffffff)

/* ͨ�������ֵ */
#define USIMM_CHANNEL_INVALID_NUM           (0xffffffff)

/* UICC����ͨ���� */
#define USIMM_BASE_CHANNEL_NUM              (0)

/* �����������ͨ���Ż��SessionID */
#define USIMM_SESSION_ID(RandNum, ChannelID) \
        ((RandNum & (~(USIMM_CHANNEL_NUM_MAX - 1))) | ChannelID)

#define USIMM_RAND_SEED_MAX                 (0xffffffff)

/* ���Է���ѡ���ļ�APDU�������� */
#define USIMM_SELECT_MAX_TIME               (3)

#define USIMM_SIM_SELECT_P2_PARA            (0x00)

/*USIMMģ��֧�ֵ����APDU�����*/
#define USIMM_APDU_MAXLEN                   (256)

#define USIMM_2G_AUTH_SRES_LEN              (4)
#define USIMM_2G_AUTH_KC_LEN                (8)

/* ��Ȩ������ʹ�õ�TAG��ʾ */
#define USIMM_GBA_AUTH_TAG                  (0xDD)
#define USIMM_NAF_AUTH_TAG                  (0xDE)
#define USIMM_AUTH_SUCCESS_TAG              (0xDB)
#define USIMM_AUTH_SYNC_FAIL_TAG            (0xDC)


/* ��Ȩģʽ���壬��ӦAPDU�е�P2���� */
#define USIMM_SIM_2G_AUTH_MODE              (0x00)
#define USIMM_USIM_2G_AUTH_MODE             (0x80)
#define USIMM_USIM_3G_AUTH_MODE             (0x81)
#define USIMM_USIM_GBA_AUTH_MODE            (0x84)

/* ��������ļ����� */
#define USIMM_FILE_TYPE(usFileId)           (VOS_UINT8)((usFileId>>0x08)&0x00FF)

/* �ж������ļ��Ƿ�ΪDF�ļ� */
#define USIMM_IS_DF_FILE(usFileId) \
        (USIMM_DF_FILE == ((usFileId>>0x0C)&0x01))


#define USIMM_FILE_PATH_MAX_LEN         100

#if( (VOS_WIN32 == VOS_OS_VER) ||  (defined __PS_WIN32_RECUR__) )
#define USIMM_LOG_PATH                  "Sim1"
#define USIMM_LOGCTRL_FILE              "Sim1/usimmlogctrl.bin"

#define USIMM_UNITARY_LOG_PATH          USIMM_LOG_PATH

#define USIMM_UNITARY_LOGCTRL_FILE      USIMM_LOGCTRL_FILE

#elif (( VOS_VXWORKS == VOS_OS_VER ) || ( VOS_RTOSCK == VOS_OS_VER ))
#if defined (INSTANCE_1)    /*SIM card 1*/
#define USIMM_LOG_PATH                  "/mnvm3:0/DrvLog/Sim1"

#define USIMM_LOGCTRL_FILE              "/mnvm3:0/DrvLog/Sim1/usimmlogctrl.bin"

#define USIMM_UNITARY_LOG_PATH          "/modem_log/DrvLog/Sim1"

#define USIMM_UNITARY_LOGCTRL_FILE      "/modem_log/DrvLog/Sim1/usimmlogctrl.bin"
#elif defined (INSTANCE_2)   /*SIM card 2*/
#define USIMM_LOG_PATH                  "/mnvm3:0/DrvLog/Sim2"

#define USIMM_LOGCTRL_FILE              "/mnvm3:0/DrvLog/Sim2/usimmlogctrl.bin"

#define USIMM_UNITARY_LOG_PATH          "/modem_log/DrvLog/Sim2"

#define USIMM_UNITARY_LOGCTRL_FILE      "/modem_log/DrvLog/Sim2/usimmlogctrl.bin"
#else                       /*SIM Card 0*/
#define USIMM_LOG_PATH                  "/mnvm3:0/DrvLog/Sim0"

#define USIMM_LOGCTRL_FILE              "/mnvm3:0/DrvLog/Sim0/usimmlogctrl.bin"

#define USIMM_UNITARY_LOG_PATH          "/modem_log/DrvLog/Sim0"

#define USIMM_UNITARY_LOGCTRL_FILE      "/modem_log/DrvLog/Sim0/usimmlogctrl.bin"

#endif /* end of INSTANCE_1*/
#endif /* end of VOS_WIN32*/


#define USIMM_MNC_TWO_BYTES_LEN        (2)             /* MNC����Ϊ2 */
#define USIMM_MNC_THREE_BYTES_LEN      (3)             /* MNC����Ϊ3 */
#define USIMM_AD_MNC_LEN_POS           (3)             /* AD�ļ���MNC�����ֶ�����λ�� */
#define USIMM_IMSI_MAX_LEN             (8)             /* IMSI��ָʾ���ȵ����ֵ */

#define USIMM_BIT_NUM_IN_BYTE          (8)             /* һ���ֽ��а�����bit�� */
#define USIMM_MNC_MCC_FIG_NUM          (3)             /* MNC,MCC���ָ�����MNC���ֲ���3��ʱ����0 */
#define USIMM_ISIMEFTOUSIMEF_TBL_SIZE  (5)             /* ISIM�ļ���USIM�ļ�ת�����С */

#define USIMM_ISIM_FILE_TAG            (0x80)

#define USIMM_AUTH_XRES_LEN             (8)     /* 3G��Ȩ�ķ�������     */
#define USIMM_AUTH_RES_LEN              (4)     /* 2G��Ȩ�ķ�������     */
#define USIMM_AUTH_CK_LEN               (16)    /* 3G��Ȩ��CK           */
#define USIMM_AUTH_IK_LEN               (16)    /* 3G��Ȩ��IK           */
#define USIMM_AUTH_KC_LEN               (8)     /* 2G��Ȩ��Kc           */
#define USIMM_AUTH_KI_LEN               (16)    /* ��Ȩ��KI             */
#define USIMM_AUTH_OPC_LEN              (16)    /* ��Ȩ��OPC            */

#define USIMM_VSIM_SECUR_MAX_LEN        (32)    /* vSIM����������ݳ��� */

#define USIMM_VSIM_SIM_KEY_HASH_LEN     (96)    /* IMSI+KI+OPC���ܳ���  */


#if (FEATURE_VSIM == FEATURE_ON)
#define USIMM_VSIM_IS_FILE_ATTR_VALID(index)      ( (USIMM_MANDATORY_FILE         == g_astUSIMMVSimFileInfo[index].enFileAttr) \
                                                  ||((USIMM_USIM_MANDATORY_FILE  == g_astUSIMMVSimFileInfo[index].enFileAttr) \
                                                    &&(USIMM_CARD_USIM         == gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardType)) \
                                                  ||((USIMM_SIM_MANDATORY_FILE   == g_astUSIMMVSimFileInfo[index].enFileAttr) \
                                                    &&(USIMM_CARD_SIM          == gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardType)) )
#endif

#define USIMM_SIM_REFRESH_IS_NEED_TP(enRefreshType)      ( (USIMM_INITIAL_FULL_FILE_CHANGE_NOTIFY == (enRefreshType)) \
                                                        || (USIMM_INITIAL_FILE_CHANGE_NOTIFY == (enRefreshType)) \
                                                        || (USIMM_INITIALIZATION == (enRefreshType)) )


#define USIMM_EF_CST_MAX_LEN            (12)

#define USIMM_HUK_LEN                   (0x10)

#define USIMM_HUK_BITS                  (128)


/*******************************************************************************
  3 ö�ٶ���
*******************************************************************************/
typedef VOS_UINT32 (*PCARDINITPROC)(VOS_VOID);

typedef struct
{
    PCARDINITPROC                pProcFun;        /* ������ */
}USIMM_CARD_INIT_FUNC;

typedef struct
{
    USIMM_CARD_INIT_FUNC         *pInitFunTbl;
    VOS_UINT32                   ulStepNum;
}USIMM_CARD_INIT_TBL_ST;

/* MANAGE CHANNEL ����ö�� ���·����ݵ�Ԫ��p1�������μ�Э��102.221��11.1.17 */
enum USIMM_MANAGE_CHANNEL_ENUM
{
    USIMM_OPEN_CHANNEL         =0x00,
    USIMM_CLOSE_CHANNEL        =0x80,
    USIMM_MANAGE_CHANNEL_BUTT
};
typedef VOS_UINT32      USIMM_MANAGE_CHANNEL_ENUM_UINT32;

/*�Ƿ�֧��sfi*/
enum USIMM_SUPPORT_SFI_ENUM
{
    USIMM_NOTSUPPORT_SFI         =0,
    USIMM_SUPPORT_SFI            =1,
    USIMM_SUPPORT_SFI_ENUM_BUTT
};
typedef VOS_UINT32      USIMM_SUPPORT_SFI_ENUM_UINT32;


/*�Ƿ�֧��path*/
enum USIMM_SUPPORT_PATH_ENUM
{
    USIMM_NOTSUPPORT_PATH       = 0,
    USIMM_SUPPORT_PATH          = 1,
    USIMM_SUPPORT_PATH_BUTT
};
typedef VOS_UINT32      USIMM_SUPPORT_PATH_ENUM_UINT32;


/*�Ƿ�֧��logic channel*/
enum USIMM_SUPPORT_CHANNEL_ENUM
{
    USIMM_NOTSUPPORT_CHANNEL    = 0,
    USIMM_SUPPORT_CHANNEL       = 1,
    USIMM_SUPPORT_CHANNEL_BUTT
};
typedef VOS_UINT32      USIMM_SUPPORT_CHANNEL_ENUM_UINT32;

enum USIMM_CLKLEVEL_ENUM
{
    USIMM_CLKLEVEL_LOW          = 0,
    USIMM_CLKLEVEL_HIGH         = 1,
    USIMM_CLKLEVEL_NONE         = 2,
    USIMM_CLKLEVEL_BUTT
};
typedef VOS_UINT32      USIMM_CLKLEVEL_ENUM_UINT32;

enum USIMM_CLKSTOP_ENUM
{
    USIMM_CLKSTOP_ALLOW             = 0,
    USIMM_CLKSTOP_NOALLOW           = 1,
    USIMM_CLKSTOP_BUTT
};
typedef VOS_UINT32      USIMM_CLKSTOP_ENUM_UINT32;

enum USIMM_SAT_STATE_ENUM
{
    USIMM_SAT_STATE_NODATA          = 0,
    USIMM_SAT_STATE_NEEDFETCH       = 1,
    USIMM_SAT_STATE_NEEDRESPONSE    = 2,
    USIMM_SAT_STATE_BUTT
};
typedef VOS_UINT32      USIMM_SAT_STATE_ENUM_UINT32;


enum USIMM_UNIVERSAL_PIN_STATUS_ENUM
{
    USIMM_UNIVERSAL_PIN_DISABLE     = 0,
    USIMM_UNIVERSAL_PIN_ENABLE      = 1,
    USIMM_UNIVERSAL_PIN_BUTT
};
typedef VOS_UINT32      USIMM_UNIVERSAL_PIN_STATUS_ENUM_UINT32;


/*�ļ��ṹ*/
enum USIMM_EF_TYPE_ENUM
{
    USIMM_EFSTRUCTURE_NONE          = 0,
    USIMM_EFSTRUCTURE_TRANSPARENT   = 1,
    USIMM_EFSTRUCTURE_FIXED         = 2,
    USIMM_EFSTRUCTURE_CYCLE         = 3,
    USIMM_EFSTRUCTURE_ENUM_BUTT
};
typedef VOS_UINT32      USIMM_EF_TYPE_ENUM_UINT32;

enum USIMM_SC_ATTRIB_MODE_ENUM
{
    USIMM_SC_ATTRIB_NO          = 0,
    USIMM_SC_ATTRIB_COMPACT     = 1,
    USIMM_SC_ATTRIB_EXPANDED    = 2,
    USIMM_SC_ATTRIB_REFERENCE   = 3,
    USIMM_SC_ATTRIB_BUTT
};
typedef VOS_UINT32      USIMM_SC_ATTRIB_MODE_ENUM_UINT32;


enum USIMM_AC_LEVEL_ENUM
{
    USIMM_AC_LEVEL_ALW          = 0,
    USIMM_AC_LEVEL_PIN1         = 1,
    USIMM_AC_LEVEL_PIN2         = 2,
    USIMM_AC_LEVEL_UPIN         = 3,
    USIMM_AC_LEVEL_ADM          = 4,
    USIMM_AC_LEVEL_NEV          = 5,
    USIMM_AC_LEVEL_BUTT
};
typedef VOS_UINT32      USIMM_AC_LEVEL_ENUM_UINT32;

enum USIMM_POOLSTATUS_ENUM
{
    USIMM_POOL_NOINTIAL         =  0,
    USIMM_POOL_INITIALED        =  1,
    USIMM_POOL_FIRST_STEP       =  2,
    USIMM_POOL_AVAILABLE        =  3,
    USIMM_POOL_NEED_PASSWORD    =  4,
    USIMM_POOLSTATUS_BUTT
};
typedef VOS_UINT32      USIMM_POOLSTATUS_ENUM_UINT32;

enum USIMM_CARD_STATE_CHANGE_ENUM
{
    USIMM_CARD_STATE_NOCHANGE   = 0,
    USIMM_CARD_STATE_CHANGED    = 1,
    USIMM_CARD_STATE_CHANGE_BUTT
};
typedef VOS_UINT32      USIMM_CARD_STATE_CHANGE_ENUM_UINT32;

enum USIMM_FILE_TYPE_ENUM
{
    USIMM_EF_FILE               = 0,
    USIMM_DF_FILE               = 1,
    USIMM_FILE_TYPE_BUTT
};
typedef VOS_UINT32      USIMM_FILE_TYPE_ENUM_UINT32;

enum USIMM_FILE_NEED_FCP_ENUM
{
    USIMM_NO_NEED_FCP           = 0,
    USIMM_NEED_FCP              = 1,
    USIMM_NEED_FCP_BUTT
};
typedef VOS_UINT32      USIMM_FILE_NEED_FCP_ENUM_UINT32;

enum USIMM_LOG_STATE_ENUM
{
    USIMM_NEED_LOG              = 0,
    USIMM_NO_NEED_LOG           = 1,
    USIMM_LOG_STATE_BUTT
};
typedef VOS_UINT32      USIMM_LOG_STATE_ENUM_UINT32;

enum USIMM_SUPPORT_SYSTEM_COMMAND_ENUM
{
    USIMM_NO_SUPSYSCMD           = 0,
    USIMM_SUPSYSCMD              = 1,
    USIMM_SUPSYSCMD_BUTT
};
typedef VOS_UINT32      USIMM_SUPPORT_SYSTEM_COMMAND_ENUM_UINT32;

enum USIMM_MODE_TYPE_ENUM
{
    USIMM_NORMAL_MODE           = 0,    /* �����ϵ�����ģʽ */
    USIMM_RESET_MODE            = 1,    /* ��λ����ģʽ */
    USIMM_REFRESH_MODE          = 2,    /* refreshģʽ */
    USIMM_PROTECT_RESET_MODE    = 3,    /* �����Ը�λģʽ */
    USIMM_MODE_TYPE_BUTT
};
typedef VOS_UINT8      USIMM_MODE_TYPE_ENUM_UINT8;


/* USIM����ѹ�ȼ���Э��TS102221 11.1.1.4.6.1 */
enum USIMM_VOLTAGE_CLASS_ENUM
{
    USIMM_VOLTAGE_5V           = 0x10,   /* supply voltage class A */
    USIMM_VOLTAGE_3V           = 0x20,   /* supply voltage class B */
    USIMM_VOLTAGE_1_8V         = 0x40,   /* supply voltage class C */
    USIMM_VOLTAGE_CLASS_BUTT
};
typedef VOS_UINT32      USIMM_VOLTAGE_CLASS_ENUM_UINT32;

/* STATUS����ö�� ���·����ݵ�Ԫ��p1�������μ�Э��102.221��11.1.2 */
enum USIMM_STATUS_P1_PARA_ENUM
{
    USIMM_STATUS_NO_INDICATION        = 0x00, /* No indication */
    USIMM_STATUS_CURAPP_INITIALIZED   = 0x01, /* Current application is initialized in the terminal */
    USIMM_STATUS_TERMINATION_CURAPP   = 0x02, /* the terminal will initiate the termination of the current application */
    USIMM_STATUS_P1_PARA_BUTT
};
typedef VOS_UINT8      USIMM_STATUS_P1_PARA_ENUM_UINT8;

/* STATUS����ö�� ���·����ݵ�Ԫ��p2�������μ�Э��102.221��11.1.2 */
enum USIMM_STATUS_P2_PARA_ENUM
{
    USIMM_STATUS_FCP_RETURNED       = 0x00,  /* response paremeters and data identical to the response paremeters and data of the select command */
    USIMM_STATUS_DF_NAME_RETURNED   = 0x01,  /* the DF name TLV-object of the currently selected application is returned */
    USIMM_STATUS_NO_DATA_RETURNED   = 0x0C,  /* No data returned */
    USIMM_STATUS_P2_PARA_BUTT
};
typedef VOS_UINT8      USIMM_STATUS_P2_PARA_ENUM_UINT8;


/* USIM��select����P1�������壬Э��TS102221 11.1.1.2 */
enum USIMM_SELECT_P1_PARA_ENUM
{
    USIMM_SELECT_BY_FILE_ID         = 0x00,   /* select DF,EF or MF by file id */
    USIMM_SELECT_CHILD_DF           = 0X01,   /* select child DF of the current DF */
    USIMM_SELECT_PARENT_DF          = 0X03,   /* select parent DF of the current DF */
    USIMM_SELECT_BY_DF_NAME         = 0x04,   /* selection by DF name,this is selection by AID */
    USIMM_SELECT_BY_PATH_FROM_MF    = 0x08,   /* select by path from MF */
    USIMM_SELECT_BY_PATH_FROM_CURDF = 0x09,   /* select by path from current DF */
    USIMM_SELECT_P1_PARA_BUTT
};
typedef VOS_UINT8      USIMM_SELECT_P1_PARA_ENUM_UINT8;


/* USIM��select����P2�������壬Э��TS102221 11.1.1.2 */
enum USIMM_SELECT_P2_PARA_ENUM
{
    USIMM_SELECT_ACTIVATE_AID         = 0x00,   /* Application session control,����Ӧ�ã�����P1����Ϊ04ʱ�����ֵ�������� */
    USIMM_SELECT_TERMINATION_AID      = 0x40,   /* Application session control,��ֹӦ�ã�����P1����Ϊ04ʱ�����ֵ��������*/
    USIMM_SELECT_RETURN_FCP_TEMPLATE  = 0x04,   /* ��Ҫ����FCP */
    USIMM_SELECT_NO_DATA_RETURNED     = 0x0C,   /* û�����ݴ��� */
    USIMM_SELECT_P2_PARA_BUTT
};
typedef VOS_UINT8      USIMM_SELECT_P2_PARA_ENUM_UINT8;

/* SIM����PHASEö�� */
enum USIMM_SIM_PHASE_ENUM
{
    USIMM_SIM_PHASE_ONE        = 0x00,   /* PHASE1 ��SIM�� */
    USIMM_SIM_PHASE_TWO        = 0x02,   /* PHASE2 ��SIM�� */
    USIMM_SIM_PHASE_PLUS       = 0x03,   /* PHASE2+ ��SIM�� */
    USIMM_SIM_PHASE_BUTT
};
typedef VOS_UINT32      USIMM_SIM_PHASE_ENUM_UINT32;

enum USIMM_PROFILE_DOWNLOAD_ENUM
{
    USIMM_PROFILE_DOWNLOAD_SUCCESS      = VOS_OK,
    USIMM_PROFILE_DOWNLOAD_FAIL,
    USIMM_PROFILE_DOWNLOAD_BUTT
};

typedef VOS_UINT8       USIMM_PROFILE_DOWNLOAD_ENUM_UINT8;

/* ��ʼ���׶�ECC�ļ���ʼ��״̬ö�� */
enum USIMM_ECC_INIT_STATUS_ENUM
{
    USIMM_ECC_INIT_SUCCESS      = VOS_OK,
    USIMM_ECC_SELECT_FAIL,
    USIMM_ECC_READ_FAIL,
    USIMM_ECC_TYPE_ERR,
    USIMM_ECC_INIT_STATUS_BUTT
};

typedef VOS_UINT8       USIMM_ECC_INIT_STATUS_ENUM_UINT8;

/* ����ʼ�����践��ֵ */
enum USIMM_INIT_RESULT_ENUM
{
    USIMM_INIT_OK       = VOS_OK,
    USIMM_INIT_FAIL     = VOS_ERR,
    USIMM_INIT_RESET,
    USIMM_INIT_NEEDPIN,
    USIMM_INIT_SUSPEND,
    USIMM_INIT_FAIL_CONTINUE,
    USIMM_INIT_FAIL_RESTART,
    USIMM_INIT_FATAL_EXIT,
    USIMM_INIT_BUTT
};

typedef VOS_UINT32 USIMM_INIT_RESULT_ENUM_32;

enum USIMM_UICC_APP_ENUM
{
    USIMM_UICC_USIM,
    USIMM_UICC_ISIM,
#if (FEATURE_UE_MODE_CDMA == FEATURE_ON)
    USIMM_UICC_CDMA,
#endif
    USIMM_UICC_BUTT
};

typedef VOS_UINT32 USIMM_UICC_APP_ENUM_32;

enum USIMM_SIM_FILE_TYPE_ENUM
{
    USIMM_SIM_FILE_TYPE_RFU = 0x00,
    USIMM_SIM_FILE_TYPE_MF  = 0x01,
    USIMM_SIM_FILE_TYPE_DF  = 0x02,
    USIMM_SIM_FILE_TYPE_EF  = 0x04,
    USIMM_SIM_FILE_TYPE_BUTT
};

typedef VOS_UINT8 USIMM_SIM_FILE_TYPE_ENUM_UINT8;

enum USIMM_VSIM_AUTH_ENUM
{
    USIMM_VSIM_AUTH_NULL        = 0,
    USIMM_VSIM_MILENAGE         = 1,
    USIMM_VSIM_COMPV1           = 2,
    USIMM_VSIM_COMPV2           = 3,
    USIMM_VSIM_COMPV3           = 4,
    USIMM_VSIM_AUTH_BUTT
};
typedef VOS_UINT8      USIMM_VSIM_AUTH_ENUM_UINT8;
typedef VOS_UINT32     USIMM_VSIM_AUTH_ENUM_UINT32;

enum USIMM_FILE_ATTR_ENUM
{
    USIMM_MANDATORY_FILE        = 0,    /*SIM USIM����Ҫ���ļ�*/
    USIMM_USIM_MANDATORY_FILE   = 1,
    USIMM_SIM_MANDATORY_FILE    = 2,
    USIMM_OPTIONAL_FILE         = 3,
    USIMM_FILE_ATTR_BUTT
};
typedef VOS_UINT8      USIMM_FILE_ATTR_ENUM_UINT8;

enum USIMM_VSIM_AC_ENUM
{
    USIMM_VSIM_WRITE_AVALIBALE        = 0,    /*VSIM���Ը��µ��ļ�*/
    USIMM_VSIM_WRITE_UNAVALIBALE      = 1,    /*VSIM�����Ը��µ��ļ�*/
    USIMM_VSIM_AC_ENUM_BUTT
};
typedef VOS_UINT8      USIMM_VSIM_AC_ENUM_UINT8;

/*****************************************************************************
 ö����    : USIMM_T1_IFS_SEND_STATUS_ENUM
 �ṹ˵��  : T=1 IFS �����״̬ö��
*****************************************************************************/
enum USIMM_T1_IFS_SEND_STATUS_ENUM
{
    USIMM_T1_IFS_SEND_SUCCESS = VOS_OK,          /* T=1Э���·���IFS����ɹ� */
    USIMM_T1_IFS_SEND_FAILURE,                   /* T=1Э���·���IFS����ʧ�� */
    USIMM_T1_IFS_SEND_STATUS_BUTT
};

typedef VOS_UINT32      USIMM_T1_IFS_SEND_STATUS_ENUM_UINT32;

/*****************************************************************************
 ö����    : USIMM_MNTN_ERROR_LEVEL_ENUM
 �ṹ˵��  : USIMM ERROR LOG����ö��
*****************************************************************************/
enum USIMM_MNTN_ERROR_LEVEL_ENUM
{
    USIMM_MNTN_ERROR_LEVEL_CRITICAL = 1,    /* ���� */
    USIMM_MNTN_ERROR_LEVEL_MAJOR,           /* ��Ҫ */
    USIMM_MNTN_ERROR_LEVEL_MINOR,           /* ��Ҫ */
    USIMM_MNTN_ERROR_LEVEL_WARNING,         /* �澯 */
    USIMM_MNTN_ERROR_LEVEL_INFO,            /* ��Ϣ */
    USIMM_MNTN_ERROR_LEVEL_BUTT
};
typedef  VOS_UINT16  USIMM_MNTN_ERROR_LEVEL_ENUM_UINT16;

/*****************************************************************************
 ö����    : USIMM_MNTN_STATE_ERROR_REASON_ENUM
 �ṹ˵��  : USIMM ERROR LOG �¼�ö��
*****************************************************************************/
enum USIMM_MNTN_STATE_ERROR_REASON_ENUM
{
    USIMM_MNTN_STATE_OK = 0,
    USIMM_MNTN_STATE_INIT_FAIL,
    USIMM_MNTN_STATE_POLLING_FAIL,
    USIMM_MNTN_STATE_ERROR_REASON_BUTT
};
typedef  VOS_UINT32  USIMM_MNTN_STATE_ERROR_REASON_ENUM_UINT32;

enum USIMM_CARD_VERSION_TYPE
{
    USIMM_CARD_NON_TYPE             = 0,
    USIMM_CARD_ICC_TYPE             = 1,
    USIMM_CARD_UICC_TYPE            = 2,
    USIMM_CARD_VERSION_TYPE_BUTT
};
typedef  VOS_UINT8  USIMM_CARD_VERSION_TYPE_UINT8;


/*****************************************************************************
  4 STRUCT����
*****************************************************************************/

typedef struct
{
    VOS_UINT16                          usDfID;
    VOS_UINT16                          usEFNum;
    VOS_UINT16                          *pusEFList;
}USIMM_FILE_CONTENT_ST;

typedef struct
{
    USIMM_FILE_CONTENT_ST               stFileCont;
    VOS_UINT32                          ulDfFcpLen;
}USIMM_SINGLE_FILEMAP_ST;

typedef struct
{
    USIMM_SINGLE_FILEMAP_ST             stDFFileMap;
    USIMM_SINGLE_FILEMAP_ST             stGDFFileMap;
}USIMM_CARD_FILEMAP_ST;

typedef struct
{
    USIMM_FILE_CONTENT_ST               stDFCont;
    VOS_UINT32                          ulGDFNum;
    USIMM_FILE_CONTENT_ST               *pstGDFCont;
}USIMM_DF_CONTENT_ST;

/*effcp��Ϣ��¼�ṹ*/
typedef struct
{
    VOS_UINT16                          usFileLen;              /*��ǰ�ļ�����*/
    VOS_UINT8                           ucRecordNum;            /*��ǰ��¼�ļ��ļ�¼��*/
    VOS_UINT8                           ucRecordLen;            /*��ǰ��¼�ļ��ļ�¼����*/
    VOS_UINT8                           ucSFI;                  /*��ǰ�ļ���SFI*/
    VOS_UINT8                           ucArrNo;                /*EFARR�ļ�¼��*/
    VOS_UINT16                          usEFArrID;              /*��¼��ȫ������EFARR��SFI*/
    USIMM_EF_TYPE_ENUM_UINT32           enFileType;             /*��ǰ�ļ�����*/
    USIMM_EFSTATUS_ENUM_UINT8           enFileStatus;           /*��ǰ�ļ�״̬*/
    USIMM_EFRWFLAG_ENUM_UINT8           enFileReadUpdateFlag;   /*��ǰ�ļ���Чʱ���ļ��ɶ���ɸ��±�־*/
    VOS_UINT8                           aucRsv[2];
    USIMM_SC_ATTRIB_MODE_ENUM_UINT32    enSCMode;               /*��ǰ�ļ��İ�ȫ��ʶ����*/
    USIMM_AC_LEVEL_ENUM_UINT32          enUpdateAC;             /*��ǰ�ļ��ĸ���Ȩ��*/
    USIMM_AC_LEVEL_ENUM_UINT32          enReadAC;               /*��ǰ�ļ��Ķ�ȡȨ��*/
    USIMM_AC_LEVEL_ENUM_UINT32          enActiveAC;             /*��ǰ�ļ��ļ���Ȩ��*/
    USIMM_AC_LEVEL_ENUM_UINT32          enDeaciveAC;            /*��ǰ�ļ���ȥ����Ȩ��*/
}USIMM_EFFCP_ST;

/*dffcp��Ϣ��¼�ṹ*/
typedef struct
{
    VOS_UINT16                          usDFID;         /*��ǰѡ��DFID*/
    VOS_UINT8                           ucPIN1RefNum;   /*��ǰDF��PIN1����*/
    VOS_UINT8                           ucPIN2RefNum;   /*��ǰDF��PIN2����*/
    VOS_UINT8                           ucCharaByte;
    VOS_UINT8                           ucNameLen;      /*��ǰDF�����ֳ���*/
    VOS_UINT8                           aucName[16];    /*��ǰDF����������*/
    VOS_UINT8                           ucSupCmd;       /*֧��terminal capability */
    VOS_UINT8                           ucRsv;
    USIMM_SC_ATTRIB_MODE_ENUM_UINT32    enSCMode;       /*��ǰDF�İ�ȫ��ʶ��ʽ*/
    USIMM_PIN_INFO_STRU                 stPINInfo;
}USIMM_DFFCP_ST;

/*sim dffcp ���ݼ�¼�ṹ,��Ա�����Э��3gpp ts 11.11 ��9.2.1*/
typedef struct
{
    VOS_UINT8                           ucReserve[2];
    VOS_UINT16                          usMemRes;
    VOS_UINT16                          usFileID;
    VOS_UINT8                           ucFileType;
    VOS_UINT8                           ucReserve2[5];
    VOS_UINT8                           ucDataLen;
    VOS_UINT8                           ucFileChara;
    VOS_UINT8                           ucDFsNum;
    VOS_UINT8                           ucEFsNum;
    VOS_UINT8                           ucSecurityCodeNum;
    VOS_UINT8                           ucReserve3;
    VOS_UINT8                           ucPIN1RemainTime;
    VOS_UINT8                           ucPUK1RemainTime;
    VOS_UINT8                           ucPIN2RemainTime;
    VOS_UINT8                           ucPUK2RemainTime;
}USIMM_SIMDF_FCP_ST;

/*sim effcp ���ݼ�¼�ṹ,��Ա�����Э��3gpp ts 11.11 ��9.2.1*/
/*lint -e959 -e958*/
typedef struct
{
    VOS_UINT8                           ucReserve[2];
    VOS_UINT16                          usFileLen;
    VOS_UINT16                          usFileID;
    VOS_UINT8                           ucFileType;
    VOS_UINT8                           ucCyclicEFTag;
    VOS_UINT8                           ucAccessCnd[3];
    VOS_UINT8                           ucFileStatus;
    VOS_UINT8                           ucDataLen;
    VOS_UINT8                           ucEFStruct;
    VOS_UINT8                           ucRecordLen;
}USIMM_SIMEF_FCP_ST;
/*lint +e959 +e958*/

typedef struct
{
    VOS_UINT32                          ulAIDLen;       /*��ǰ��AID����*/
    VOS_UINT8                           aucAID[USIMM_AID_LEN_MAX];     /*��ǰAID����*/
    VOS_UINT8                           ucPIN1RefNum;   /*��ǰDF��PIN1����*/
    VOS_UINT8                           ucPIN2RefNum;   /*��ǰDF��PIN2����*/
#if (FEATURE_UE_MODE_CDMA == FEATURE_ON)
    VOS_UINT8                           ucCharaByte;
    VOS_UINT8                           ucSupCmd;
#else
    VOS_UINT16                          usRsv;
#endif
    USIMM_PIN_INFO_STRU                 stPINInfo;      /*��ǰ������Ϣ*/
    USIMM_PIN_VERIY_STATUS_ENUM_UINT32  enPin1Verified; /* PIN1��֤״̬         */
    USIMM_PIN_VERIY_STATUS_ENUM_UINT32  enPin2Verified; /* PIN2��֤״̬         */
    VOS_UINT8                           aucPin1[USIMM_PINNUMBER_LEN];/* PIN������ɹ����¼�µ�ǰPIN�� */
}USIMM_ADF_INFO_STRU;
typedef struct
{
    VOS_UINT32                          ulAIDLen;       /*��ǰ��AID����*/
    VOS_UINT8                           aucAID[USIMM_AID_LEN_MAX];     /*��ǰAID����*/
}USIMM_AID_INFO_STRU;

typedef struct
{
    USIMM_PB_INIT_STATUS_ENUM_UINT16    enPBInitStatus;     /*��ǰ�绰����ʼ��״̬���Ծ����Ƿ���Խ���ʱ��ֹͣģʽ*/
    VOS_UINT16                          usPBDfID;           /*��ǰ�绰����4F�ļ����ڵ�·��*/
}USIMM_PB_INFO_STRU;

typedef struct
{
    USIMM_CARD_TYPE_ENUM_UINT32             enCardType;         /* ��ǰ������ */
    USIMM_CARD_SERVIC_ENUM_UINT32           enCardService;      /* ��ǰ����״̬ */
    USIMM_CARD_STATE_CHANGE_ENUM_UINT32     enStateChange;      /* ״̬��� */
}USIMM_CARD_APP_INFO_ST;

/*������Ϣ��¼�ṹ*/
typedef struct
{
    VOS_UINT8                               ucCLA;              /*��ǰCLAֵ*/
    VOS_UINT8                               ucCurChannelNum;    /*��ǰ������ͨ����*/
    VOS_UINT16                              usSATLen;           /*��ǰ�����������*/
    USIMM_SUPPORT_SFI_ENUM_UINT32           enSupportSFI;       /*�Ƿ�֧��SFI*/
    USIMM_SUPPORT_PATH_ENUM_UINT32          enSupportPath;      /*�Ƿ�֧��·��ѡ��*/
    USIMM_SUPPORT_CHANNEL_ENUM_UINT32       enSupportChannel;   /*�Ƿ�֧���߼�ͨ��*/
    USIMM_PIN_TYPE_ENUM_UINT32              enCurPINType;       /*��ǰ��������*/
    VOS_UINT32                              ulSimPhase;         /*��ΪSIM��ʱ������PHASE*/
    USIMM_FDNSTATUS_ENUM_UINT32             enFDNStatus;        /*��ǰFDN״̬*/
    USIMM_BDNSTATUS_ENUM_UINT32             enBDNStatus;        /*��ǰBDN״̬*/
    USIMM_UNIVERSAL_PIN_STATUS_ENUM_UINT32  enUniversalPINStatus;/*��ǰȫ��PIN״̬*/
    USIMM_SAT_STATE_ENUM_UINT32             enSATState;         /*��ǰ��������״̬*/
    USIMM_PB_INFO_STRU                      stPBInfo;           /*��ǰ�绰����ʱ����Ϣ*/
}USIMM_BASE_INFO_ST;

typedef struct
{
    VOS_UINT16                              usIsimEFID;
    VOS_UINT16                              usUsimEFID;
}USIMM_ISIM_USIM_CONVERSION_ST;

/*������Ϣ��¼�ṹ*/
typedef struct
{
    USIMM_CLKLEVEL_ENUM_UINT32              enCLKLevel;         /*��ǰCLK level���ȼ�*/
    USIMM_CLKSTOP_ENUM_UINT32               enCLKStop;          /*��ǰCLK �Ƿ�����ֹͣ*/
}USIMM_DRV_INFO_ST;

/*��ǰ�ļ���Ϣ��¼�ṹ*/
typedef struct
{
    VOS_UINT16                              usCurDFID;      /*��ǰѡ��DFID*/
    VOS_UINT16                              usCurEFID;      /*��ǰѡ��EFID*/
    VOS_UINT16                              usCurDFFcpLen;  /*��ǰѡ�е�DF��FCP����*/
    VOS_UINT16                              usFilePathLen;
    VOS_UINT16                              ausFilePath[USIMM_MAX_PATH_LEN];  /*��ǰ·����Ϣ*/
    USIMM_DFFCP_ST                          stDFInfo;       /*��ǰDF��Ϣ*/
    USIMM_EFFCP_ST                          stEFInfo;       /*��ǰEF��Ϣ*/
}USIMM_CURFILEINFO_ST;
typedef struct
{
    VOS_UINT16                              usFId;          /* �ļ�ID */
    VOS_UINT16                              usLen;          /* �ļ����ݳ��� */
    USIMM_APP_TYPE_ENUM_UINT32              enAppType;      /* APP���� */
    USIMM_EF_TYPE_ENUM_UINT32               enFileType;     /* �ļ����� */
    VOS_UINT8                              *pucContent;     /* �ļ�����ָ�� */
}USIMM_POOL_ONERECORD_ST;
typedef struct
{
    VOS_UINT16                              usOptionFileNum;
    VOS_UINT16                              aucOptionFilelist[USIMM_INIT_OFILE_MUX_NUM];
}USIMM_POOL_OPTION_FILE_CFG_ST;


typedef struct
{
    USIMM_POOL_ONERECORD_ST                 astpoolRecord[POOLMAXNUM];
    USIMM_POOLSTATUS_ENUM_UINT32            enPoolStatus;
    VOS_UINT8                               ucNowLen;
    VOS_UINT8                               aucReserved[3];
}USIMM_POOL_ST;


typedef VOS_UINT32 (*PUSIMMAPPPROC)(USIMM_CMDHEADER_REQ_STRU * pMsg);

typedef struct
{
    USIMM_CMDTYPE_REQ_ENUM_UINT32           enMsgType;        /* ��ϢID */
    PUSIMMAPPPROC                           pProcFun;        /* ������ */
}USIMMAPP_FUNCLIST_ST;

typedef struct
{
    USIMM_LOG_STATE_ENUM_UINT32             enLogState;
    VOS_UINT32                              ulDataLen;
    VOS_UINT8                               *pucData;
}USIMM_LOG_DATA_STRU;

typedef struct
{
    VOS_UINT32                              ulCurFile;
    VOS_CHAR                                aucFileName[USIMM_LOG_FILE_MAX_NUM][USIMM_LOG_FILE_NAME_LEN];
}USIMM_LOG_CTRLFILE_STRU;


typedef struct
{
    VOS_UINT16                          usFileId;
    VOS_UINT16                          usService;
}USIMM_OPFILE_LIST_STRU;

/*****************************************************************************
�ṹ��    : USIMM_TERMINAL_POWER_SUPPLY_STRU
�ṹ˵��  : �ն˵�ѹ��Ӧ�ṹ����ӦЭ��102.221��11.1.19.2.1
*****************************************************************************/
typedef struct
{
    VOS_UINT8                          ucTag;              /* terminal power supply ��tag:0x80 */
    VOS_UINT8                          ucLen;              /* ���� */
    VOS_UINT8                          ucActSupVolCla;     /* ʵ��ʹ�õĹ����ѹ�ȼ� */
    VOS_UINT8                          ucMaxAvaPower;      /* �ն��������õ�ѹ��Ӧ */
    VOS_UINT8                          ucActFre;           /* ʵ��ʹ�õ�ʱ��Ƶ�� */
}USIMM_TERMINAL_POWER_SUPPLY_STRU;

/*****************************************************************************
�ṹ��    : USIMM_EXT_LOG_CHANNEL_SUPPORT_STRU
�ṹ˵��  : �ն˵�ѹ��Ӧ�ṹ����ӦЭ��102.221��11.1.19.2.2
*****************************************************************************/
typedef struct
{
    VOS_UINT8                          ucTag;              /* extended logical channel terminal support��tag:0x81 */
    VOS_UINT8                          ucLen;              /* ���� */
}USIMM_EXT_LOG_CHANNEL_SUPPORT_STRU;

/*****************************************************************************
�ṹ��    : USIMM_ADDITIONAL_INTERFACES_SUPPORT_STRU
�ṹ˵��  : �ն˵�ѹ��Ӧ�ṹ����ӦЭ��102.221��11.1.19.2.3
*****************************************************************************/
typedef struct
{
    VOS_UINT8                          ucTag;              /* the additional interface support��tag:0x82 */
    VOS_UINT8                          ucLen;              /* ���� */
    VOS_UINT8                          ucAddInterface;     /* ���ӽӿ� */
}USIMM_ADDITIONAL_INTERFACES_SUPPORT_STRU;

/*****************************************************************************
�ṹ��    : USIMM_CARD_INIT_INFO_LOG_STRU
�ṹ˵��  : ����ʼ���׶ε���Ϣ��¼
*****************************************************************************/
typedef struct
{
    USIMM_PROFILE_DOWNLOAD_ENUM_UINT8  enTPDownloadStatus;    /* terminal profile�Ƿ��·�ʧ�� */
    USIMM_ECC_INIT_STATUS_ENUM_UINT8   enEccInitStatus;       /* ECC�ļ���ʼ��״̬ */
    VOS_UINT8                          ucVoltageSwitchFlag;   /* ��ѹ�Ƿ��л� */
    VOS_UINT8                          ucVoltageMismatchFlag; /* ��ѹ��ƥ���� */
}USIMM_CARD_INIT_RECORD_STRU;

typedef struct
{
    VOS_UINT8                          ucInsertPoolFailFlag;  /* �ļ����뻺���ʧ�ܱ�� */
    USIMM_CARD_INIT_RECORD_STRU        stUSIMMInfo;
}USIMM_CARD_INIT_INFO_LOG_STRU;

typedef struct
{
    USIMM_APP_TYPE_ENUM_UINT32          enFileApp;
    USIMM_CARD_TYPE_ENUM_UINT32         enCardType;
    USIMM_FILE_NEED_FCP_ENUM_UINT32     enEfFcpFlag;
}USIMM_SELECT_PARA_STUR;

typedef struct
{
    VOS_UINT32                  ulLeValue;                          /* �������ݳ��� */
    VOS_UINT32                  ulLcValue;                          /* �������ݳ��� */
    VOS_UINT32                  ulRecDataLen;
    VOS_UINT8                   ucResult;
    VOS_UINT8                   ucACK;                              /*���յ�ACK*/
    VOS_UINT8                   ucSW1;                              /*����������SW1*/
    VOS_UINT8                   ucSW2;                              /*����������SW2*/
    VOS_UINT8                   ucApduSW1;                          /*�����һ�η��͵�SW1*/
    VOS_UINT8                   ucApduSW2;                          /*�����һ�η��͵�SW2*/
    VOS_UINT8                   aucAPDU[USIMM_APDU_HEADLEN];        /*�����APDU*/
    VOS_UINT8                   aucGetRepAPDU[USIMM_APDU_HEADLEN];  /*Get Response�����APDU*/
    VOS_UINT8                   aucRecvBuf[USIMM_APDU_MAXLEN];      /* ������������*/
    VOS_UINT8                   aucSendBuf[USIMM_APDU_MAXLEN];      /* ������������*/
}USIMM_APDU_ST;

typedef struct
{
    USIMM_APP_TYPE_ENUM_UINT32      enAppType;
    VOS_UINT32                      ulPathLen;
    VOS_UINT16                      *pusFilePath;
    VOS_UINT8                       ucRecordNum;
    VOS_UINT8                       aucRsv[3];
}USIMM_GET_COMM_FILE_STRU;

typedef struct
{
    USIMM_APP_TYPE_ENUM_UINT32      enAppType;
    USIMM_EF_TYPE_ENUM_UINT32       enEFFileType;
    VOS_UINT16                      usFileID;
    VOS_UINT16                      usDataLen;
    VOS_UINT8                       ucRecordNum;
    VOS_UINT8                       aucRsv[3];
    VOS_UINT8                       *pucData;
}USIMM_SET_COMM_FILE_STRU;

#if (FEATURE_VSIM == FEATURE_ON)
typedef struct
{
    VOS_CHAR                                *pcVSIMName;
    VOS_UINT16                              usFileID;
    USIMM_FILE_ATTR_ENUM_UINT8              enFileAttr;
    USIMM_VSIM_AC_ENUM_UINT8                enFileAC;
}USIMM_VSIM_FILE_INFO_STRU;

typedef struct
{
    VOS_UINT32                              ulLen;
    VOS_UINT8                               aucData[USIMM_VSIM_SECUR_MAX_LEN * 2];
}USIMM_VSIM_BASE16_DATA_STRU;

typedef struct
{
    VOS_UINT8                               ucKILen;
    VOS_UINT8                               ucOpcLen;
    USIMM_VSIM_AUTH_ENUM_UINT8              enAuthType;
    VOS_UINT8                               ucRfu;
    VOS_UINT8                               aucKi[USIMM_VSIM_SECUR_MAX_LEN];
    VOS_UINT8                               aucOpc[USIMM_VSIM_SECUR_MAX_LEN];
    VOS_UINT8                               aucSimKeyHash[USIMM_VSIM_SIM_KEY_HASH_LEN];
    USIMM_VSIM_BASE16_DATA_STRU             stBase16Ki;
    USIMM_VSIM_BASE16_DATA_STRU             stBase16Opc;
}USIMM_VSIM_AUTH_INFO_STRU;
#endif

#if(FEATURE_ON == FEATURE_PTM)
/*****************************************************************************
 �ṹ����  : USIMM_MNTN_STATE_ERROR_EVENT_STRU
 �ṹ˵��  : USIMM ERROR LOG�ϱ��ṹ
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                          stHeader;
    USIMM_MNTN_STATE_ERROR_REASON_ENUM_UINT32       enStateErrorReason;     /*���쳣ԭ��*/
    SCI_RECORD_INFO_S                               stSCIRecordInfo;        /*SCI�����쳣��Ϣ*/
    VOS_UINT32                                      aulRsv[4];              /*������չ�ֶ� */
}USIMM_MNTN_STATE_ERROR_EVENT_STRU;
#endif

/*****************************************************************************
 �ṹ��    : USIMM_CHANNEL_INFO_STRU
 �ṹ˵��  : USIMģ��CHANNEL INFO�����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulRspLen;                               /* GetResponse���� */
    VOS_UINT8                           aucRspContent[USIMM_APDU_MAXLEN];       /* GetResponse������ */
}USIMM_CHANNEL_GET_RSP_STRU;

typedef struct
{
    USIMM_CARD_VERSION_TYPE_UINT8       enCardMode;
    VOS_UINT8                           ucHasCModule;
    VOS_UINT8                           ucHasWGModule;
    VOS_UINT8                           ucRfu;
} USIMM_CARD_VERSIONTYPE_STRU;


/*****************************************************************************
  5 ȫ�ֱ�������
*****************************************************************************/
#if(FEATURE_ON == FEATURE_PTM)
extern USIMM_MNTN_STATE_ERROR_EVENT_STRU    g_stCardErrorLog;

extern NV_ID_ERR_LOG_CTRL_INFO_STRU         g_stErrLogCtrlInfo;
#endif

extern USIMM_BASE_INFO_ST                    gstUSIMMBaseInfo;

extern USIMM_CARD_APP_INFO_ST                gastUSIMMCardAppInfo[USIMM_UICC_BUTT];

extern VOS_UINT32                            gulUsimSupportIMS;

extern USIMM_ISIM_USIM_CONVERSION_ST         gastIsimUsimEFConTBL[5];

extern USIMM_ISIM_USIM_CONVERSION_ST         gastIsimToUsimEFTBL[5];

extern USIMM_DRV_INFO_ST                     gstUSIMMDrvInfo;

extern USIMM_CURFILEINFO_ST                  gstUSIMMCurFileInfo;

extern USIMM_ADF_INFO_STRU                   gstUSIMMADFInfo;

extern USIMM_AID_INFO_STRU                   g_astAidInfo[3];

extern USIMM_LOG_DATA_STRU                   g_stUSIMMLogData;

extern VOS_UINT32                           g_ulUSIMMExcLogLenBK;

extern USIMM_LOG_DATA_STRU                  g_stUSIMMExcLogData;

extern USIMM_POOL_ST                         gstUSIMMPOOL;

extern VOS_UINT32                            gulUSIMMOpenSpeed;

extern VOS_UINT16 gausInitFileOne[USIMM_INITFIRST_FILENUM];

extern VOS_UINT16 gausSimInitMFile[USIMM_INITSIM_MFILENUM];

extern VOS_UINT16 gausUsimInitMFile[USIMM_INITUSIM_MFILENUM];

extern USIMM_OPFILE_LIST_STRU gastSimInitOFile[USIMM_INITSIM_OFILENUM];

extern USIMM_OPFILE_LIST_STRU gastUsimInitOFile[USIMM_INITUSIM_OFILENUM];

extern VOS_UINT16 g_ausAttUsimInitFile[USIMM_USIM_ATT_INITFILE_NUM];

extern VOS_UINT16 g_ausAttSimInitFile[USIMM_SIM_ATT_INITFILE_NUM];

extern VOS_UINT16 gausSimDFTELFile[15];

extern VOS_UINT16 gausSimDFGSMFile[46];

extern VOS_UINT16 gausUsimDFGSMFile[39];

extern VOS_UINT16 gausUsimDFTELFile[17];

extern VOS_UINT16 gausUsimADFFile[88];

extern USIMM_CARD_FILEMAP_ST g_stUSIMMCardFileMap[10];

extern USIMM_FILE_CONTENT_ST g_stSimDFGSMContent[USIMM_SIMDFGSMGDF_MAX];

extern USIMM_FILE_CONTENT_ST g_stSimDFTELContent[USIMM_SIMDFTELGDF_MAX];

extern USIMM_DF_CONTENT_ST g_stSimDFContent[USIMM_SIMDFCONTENT_MAX];

extern USIMM_FILE_CONTENT_ST g_astUsimADFContent[USIMM_USIMADFGDF_MAX];

extern USIMM_FILE_CONTENT_ST g_astUsimDFTELContent[USIMM_USIMADFTELGDF_MAX];

extern USIMM_DF_CONTENT_ST g_stUsimDFContent[USIMM_USIMDFCONTENT_MAX];

extern USIMM_CARD_INIT_FUNC   g_aUsimInitCardProcFuncTbl[USIMM_INIT_USIM_CARD_NUM];

extern USIMM_CARD_INIT_FUNC   g_aSimInitCardProcFuncTbl[USIMM_INIT_SIM_CARD_NUM];

extern USIMM_CARD_INIT_TBL_ST g_aCardInitTbl[USIMM_CARD_INIT_TBL_SIZE];

extern USIMM_FEATURE_CFG_STRU   g_stUsimmFeatureCfg;

extern VOS_UINT32               g_ulATTSpecErrSWCnt;

extern USIMM_CHANNEL_INFO_STRU  g_astUSIMMChCtrl[USIMM_CHANNEL_NUM_MAX];

extern USIMM_CHANNEL_GET_RSP_STRU g_astUSIMMChGetRsp[USIMM_CHANNEL_NUM_MAX];

extern USIMM_CHANNEL_AIDFCPINFO_STRU       g_astUSIMMChAIDFCP[USIMM_CHANNEL_NUM_MAX];

extern USIMM_CARD_INIT_INFO_LOG_STRU       g_stUSIMMInitInfo;

extern USIMM_DL_T_MODE_ENUM_UINT32         g_enUSIMMTMode;
extern VOS_BOOL                            g_bSendIFSReqFlag;


#if (FEATURE_VSIM == FEATURE_ON)
extern USIMM_VSIM_AUTH_INFO_STRU        g_stUSIMMVSimAuthInfo;

extern USIMM_VSIM_FILE_INFO_STRU        g_astUSIMMVSimFileInfo[];

extern VOS_CHAR                         *g_pcUSIMMVSimXmlFilePath;

extern VOS_UINT8                        *g_pucUSIMMVsimData ;
#endif

extern USIMM_CARD_VERSIONTYPE_STRU  g_stUSIMMCardVersionType;

extern VOS_UINT32 g_ulCsimSessionId;

extern USIMM_FILEID_PATHSTR_TABLE_STRU g_stUSIMMFilePathTable[USIMM_DEF_FILEID_BUTT];

/*****************************************************************************
  6 Function����
*****************************************************************************/
#ifdef USIMM_DEBUG_PEINT
#define USIMM_NORMAL                0
#define USIMM_INFO                  1
#define USIMM_WARNING               2
#define USIMM_ERROR                 3

#define USIMM_NORMAL_LOG(string)    USIMM_PRINT(USIMM_NORMAL,string)
#define USIMM_INFO_LOG(string)      USIMM_PRINT(USIMM_INFO,string)
#define USIMM_WARNING_LOG(string)   USIMM_PRINT(USIMM_WARNING,string)
#define USIMM_ERROR_LOG(string)     USIMM_PRINT(USIMM_ERROR,string)
#else
#define USIMM_NORMAL_LOG(string)    PS_LOG(WUEPS_PID_USIM, 0, PS_PRINT_NORMAL, string)
#define USIMM_INFO_LOG(string)      PS_LOG(WUEPS_PID_USIM, 0, PS_PRINT_INFO, string)
#define USIMM_WARNING_LOG(string)   PS_LOG(WUEPS_PID_USIM, 0, PS_PRINT_WARNING, string)
#define USIMM_ERROR_LOG(string)     PS_LOG(WUEPS_PID_USIM, 0, PS_PRINT_ERROR, string)
#endif


/*Common ����*/
extern VOS_VOID USIMM_ChangePathToU16(VOS_UINT32 ulDataLen, VOS_UINT8 *pucData, VOS_UINT32 *pulLen, VOS_UINT16 *pusPath);

extern VOS_UINT32 USIMM_SelectFileHandle(USIMM_SELECT_PARA_STUR *pstSelectPara,USIMM_U16_LVDATA_STRU *pstFilePath);

extern VOS_UINT32 USIMM_SelectFile(USIMM_APP_TYPE_ENUM_UINT32 enFileApp,USIMM_FILE_NEED_FCP_ENUM_UINT32 enEfFcpFlag,VOS_UINT32 ulPathLen,VOS_UINT16 *pusFilePath);

extern VOS_UINT32 USIMM_GetFileAllPath(USIMM_SELECT_PARA_STUR       *pstSelectPara,
                                        USIMM_U16_LVDATA_STRU      *pstFilePathIn,
                                        USIMM_U16_LVDATA_STRU      *pstFilePathOut);

extern VOS_UINT32 USIMM_ReadTFFile(VOS_UINT16 usLen, VOS_UINT8 *pucContent);

extern VOS_UINT32  USIMM_GetTFFile(USIMM_APP_TYPE_ENUM_UINT32 enAppType, VOS_UINT16 usFileId, VOS_UINT16 usReadLen,VOS_UINT8 *pucData);

extern VOS_UINT32 USIMM_SelectUiccADF(VOS_VOID);

extern VOS_VOID USIMM_PRINT(VOS_UINT32 ulPrintLev,VOS_INT8*pucString);

extern VOS_UINT32 USIMM_SelectDFFile(
    VOS_UINT16                        usFileId,
    USIMM_SELECT_PARA_STUR           *pstSelectPara,
    USIMM_CURFILEINFO_ST             *pstCurFileInfo);

extern VOS_UINT32 USIMM_SelectEFByID(VOS_UINT16 usFileId,USIMM_SELECT_PARA_STUR *pstSelectPara,USIMM_CURFILEINFO_ST *pstCurFileInfo);

extern VOS_UINT32 USIMM_GetCardFilePath(USIMM_APP_TYPE_ENUM_UINT32 enFileApp,VOS_UINT16 usFileId, VOS_UINT32 *pulPathLen, VOS_UINT16 *pusPath);

extern VOS_UINT32 USIMM_GetAttFilePath(VOS_UINT16 usFileId, VOS_UINT32 *pulPathLen, VOS_UINT16 *pusPath);

extern VOS_UINT32 USIMM_SelectFileWithPath(USIMM_SELECT_PARA_STUR *pstSelectPara, USIMM_U16_LVDATA_STRU *pstFilePath, USIMM_CURFILEINFO_ST *pstCurFilePath,VOS_UINT16 *pstFilePathResult);

extern VOS_UINT32 USIMM_UpdateLFFile(VOS_UINT8 ucRecordNum, VOS_UINT8 *pucData, VOS_UINT8 ucLen);

extern VOS_UINT32 USIMM_UpdateTFFile(VOS_UINT16 usLen, VOS_UINT8 *pucData);

extern VOS_UINT32 USIMM_UpdateCLFFile(VOS_UINT8 *pucData, VOS_UINT8 ucDataLen);

extern VOS_UINT32 USIMM_ReadLFFile(USIMM_EFFCP_ST *pstCurEFFcp, VOS_UINT8 ucRecordNum, VOS_UINT8 *pucContent);

extern VOS_UINT32 USIMM_STATUSProc(VOS_VOID);

extern VOS_UINT32 USIMM_AdjudgeCardState(VOS_VOID);

extern VOS_UINT32 USIMM_GetPINRemainTime(VOS_UINT8 ucPINNo);

extern VOS_UINT32 USIMM_GetPUKRemainTime(VOS_UINT8 ucPINNo);

extern VOS_UINT32 USIMM_VerifyNCK(VOS_UINT8 ucLen,VOS_UINT8 *pucPassword);

extern VOS_UINT32 USIMM_VerifyPCK(VOS_UINT8 ucLen,VOS_UINT8 *pucPassword);

extern VOS_UINT32 USIMM_ChangePIN(USIMM_PIN_TYPE_ENUM_UINT32 enPINType, VOS_UINT8 *pucOldPIN, VOS_UINT8 *pucNewPIN);

extern VOS_UINT32 USIMM_UnblockPIN(USIMM_PIN_TYPE_ENUM_UINT32 enPINType, VOS_UINT8 *pucPUK, VOS_UINT8 *pucNewPIN);

extern VOS_UINT32 USIMM_PINVerify(USIMM_PIN_TYPE_ENUM_UINT32 enPINType,VOS_UINT8 ucPINCmd,VOS_UINT8 *pucPIN);

extern VOS_UINT32 USIMM_InitUsimFDNBDNStatus(VOS_VOID);

extern VOS_UINT32 USIMM_InitSimFDNBDNStatus(VOS_VOID);

extern VOS_VOID USIMM_FdnCapabilityRequest(USIMM_FDNSTATUS_ENUM_UINT32 *pulFdnStatus);

extern VOS_VOID USIMM_BdnCapabilityRequest(USIMM_BDNSTATUS_ENUM_UINT32 *pulBdnStatus);

extern VOS_UINT32 USIMM_SimFDNBDNProcess(VOS_VOID);

extern VOS_UINT32 USIMM_FDNEnable(VOS_VOID);

extern VOS_UINT32 USIMM_FDNDisable(VOS_VOID);

extern VOS_VOID USIMM_FDNEstChgInd(VOS_VOID);

extern VOS_UINT32 USIMM_FindTagInBERTLV(VOS_UINT8 *pucDataBuf, VOS_UINT8 ucTag, VOS_UINT32 ulDataLen);

extern VOS_UINT32 USIMM_FindTagInSMPTLV(VOS_UINT8 *pucDataBuf, VOS_UINT8 ucTag, VOS_UINT32 ulDataLen);

extern VOS_UINT32 USIMM_FindTagInCTLV(VOS_UINT8 *pucDataBuf, VOS_UINT8 ucTag, VOS_UINT32 ulDataLen);

extern VOS_UINT32 USIMM_GetBitFromBuf(VOS_UINT8 *pucDataBuf, VOS_UINT32 ulBitNo,VOS_UINT32 ulBufLen);

extern VOS_UINT32 USIMM_DecodeATR(VOS_VOID);

extern VOS_VOID   USIMM_DecodeATRSecondStep(VOS_VOID);

extern VOS_UINT32 USIMM_DecodeEFFcp(USIMM_CARD_TYPE_ENUM_UINT32 enCurCardType, USIMM_APDU_ST *pstApduData, USIMM_CURFILEINFO_ST *pstCurFileInfo);

extern VOS_UINT32 USIMM_DecodeDFFcp(USIMM_CARD_TYPE_ENUM_UINT32 enCurCardType,USIMM_APDU_ST *pstApduData,USIMM_CURFILEINFO_ST *pstCurFileInfo);

extern VOS_UINT32 USIMM_DecodeFileFcp(USIMM_CARD_TYPE_ENUM_UINT32 enCardType,USIMM_U16_LVDATA_STRU *pstFilePath,USIMM_APDU_ST *pstApduData,USIMM_CURFILEINFO_ST *pstCurFileInfo);

extern VOS_UINT32 USIMM_DecodeEFDIR(VOS_VOID);

extern VOS_VOID USIMM_ReportEvent(VOS_UINT16 usEventId);

extern VOS_VOID USIMM_RefreshFileIndHandle(USIMM_STKREFRESH_REQ_STRU *pstMsg);

extern VOS_UINT32 USIMM_RefrehFilePath(VOS_UINT8 *pucDstPath, VOS_UINT16 *pusDstLen, VOS_UINT8 *pucSrcPath, VOS_UINT16 usSrcLen);

extern VOS_UINT32 USIMM_CardFilePathCMP(VOS_UINT32 ulPath1Len, VOS_UINT16 *pusPath1,VOS_UINT32 ulPath2Len, VOS_UINT16 *pusPath2);

extern VOS_BOOL USIMM_IsCLEnable(VOS_VOID);

extern TAF_NVIM_LC_RAT_COMBINED_ENUM_UINT8 USIMM_GetRATMode(VOS_VOID);

extern VOS_VOID USIMM_FileAccessFix( VOS_VOID );

extern VOS_VOID  USIMM_SetAccFileAccess( VOS_VOID );



/* Add by H00300778 for MultiAppSync Begin 2015-05-12 */
extern VOS_UINT32 USIMM_IS_EF_FILE(VOS_UINT16 usFileId);
/* Add by H00300778 for MultiAppSync End 2015-05-12 */

/*POOL��������*/
extern VOS_VOID USIMM_RefreshFileRead(USIMM_STKREFRESH_REQ_STRU *pstMsg);

extern VOS_VOID USIMM_PoolDataInit(VOS_VOID);

extern VOS_VOID USIMM_FeatureGlobalInit(VOS_VOID);

extern VOS_UINT32 USIMM_VsimPoolSearchFile(VOS_UINT16 usFileId, VOS_UINT32 *pulData);

extern VOS_UINT32 USIMM_PoolFindFile(VOS_UINT16 usFileId, VOS_UINT32 *pulData, USIMM_APP_TYPE_ENUM_UINT32 enAppType);

extern VOS_UINT32 USIMM_PoolInsertOneFile(VOS_UINT16 usFileId, VOS_UINT16 usLen, VOS_UINT8* pData,
                                                 USIMM_APP_TYPE_ENUM_UINT32 enAppType,
                                                 USIMM_EF_TYPE_ENUM_UINT32 enFileType);

extern VOS_UINT32 USIMM_InsertFileToPool(USIMM_APP_TYPE_ENUM_UINT32 enAppType, VOS_UINT16 usFileID);

extern VOS_VOID   USIMM_RefreshFileAppCheck(USIMM_APP_TYPE_ENUM_UINT32 *penAppType, VOS_UINT16 *pusFilePath, VOS_UINT32 ulPathLen);

extern VOS_UINT32 USIMM_PoolDelOneFile(VOS_UINT16 usFileId, USIMM_APP_TYPE_ENUM_UINT32 enAppType);

extern VOS_UINT32 USIMM_PoolReadOneFile(VOS_UINT16 usFileId, VOS_UINT16 usLen, VOS_UINT8* pData,
                                                USIMM_APP_TYPE_ENUM_UINT32 enAppType);

extern VOS_VOID USIMM_PoolDelAll(VOS_VOID);

extern VOS_UINT32  USIMM_PoolUpdateOneFile(VOS_UINT16 usFileId, USIMM_APP_TYPE_ENUM_UINT32 enAppType, VOS_UINT32 ulDataLen, VOS_UINT8 *pucData);

extern VOS_VOID USIMM_ClearCurDFInfo(USIMM_CURFILEINFO_ST *pstCurFileInfo);

extern VOS_VOID USIMM_ClearCurEFInfo(USIMM_CURFILEINFO_ST *pstCurFileInfo);

extern VOS_VOID USIMM_ClearCurFileInfo(VOS_VOID);

extern VOS_VOID USIMM_SaveDFPinInfo(VOS_VOID);

extern VOS_VOID USIMM_InitGlobalVarOnReset(VOS_VOID);

extern VOS_VOID USIMM_InitGlobalVarOnPower(VOS_VOID);

extern VOS_VOID USIMM_OpenSpeedFileInit(VOS_VOID);

extern VOS_VOID USIMM_InitOpenSpeed(VOS_VOID);

extern VOS_UINT32 USIMM_InsertNoNeedPinFileToPool(VOS_VOID);

extern VOS_UINT32 USIMM_InsertLPFileToPool(VOS_VOID);

extern VOS_VOID USIMM_InitNeedPinSteps(USIMM_MODE_TYPE_ENUM_UINT8 ucMode);

extern VOS_VOID USIMM_AttFileInit(VOS_VOID);

extern VOS_VOID USIMM_InsertAttFileToPool(USIMM_APP_TYPE_ENUM_UINT32 enAppType, VOS_UINT16 usFile);

extern VOS_UINT32 USIMM_InitProfileStep(VOS_VOID);

extern VOS_UINT32 USIMM_InitCardOptionalFile(USIMM_CMDHEADER_REQ_STRU *pMsg);

extern VOS_UINT32 USIMM_InitThirdSteps(VOS_VOID);

extern VOS_VOID USIMM_GetTerminalProfile(USIMM_STK_CFG_STRU *pstProfileContent);

extern VOS_UINT32 USIMM_UsimProfileDownload(VOS_VOID);

extern VOS_VOID USIMM_SimProfileDownload(USIMM_MODE_TYPE_ENUM_UINT8 ucMode);

extern VOS_VOID USIMM_AttUpdataSupportTable(VOS_VOID);

extern VOS_VOID USIMM_AttEfTerminalSupportTableValueGet(VOS_UINT8 *pucValue);

extern VOS_UINT32 USIMM_InitUsimEccFile(VOS_VOID);

extern VOS_UINT32 USIMM_InitSimEccFile(VOS_VOID);

extern VOS_UINT32 USIMM_CheckCLStep(VOS_VOID);

extern VOS_UINT32 USIMM_InitCardPINInfo(VOS_VOID);

extern VOS_UINT32 USIMM_InitCardTypeByATR(VOS_VOID);

extern VOS_UINT32 USIMM_InitCard(USIMM_MsgBlock *pMsg);

extern VOS_UINT32 USIMM_SelectFileNoPath(
    USIMM_SELECT_PARA_STUR             *pstSelectPara,
    USIMM_U16_LVDATA_STRU              *pstFilePath,
    USIMM_CURFILEINFO_ST               *pstCurFileInfo,
    VOS_UINT16                         *pusCurPathLen);

extern VOS_UINT32 USIMM_SelectFileByPath(USIMM_SELECT_PARA_STUR *pstSelectPara, USIMM_U16_LVDATA_STRU *pstFilePath, USIMM_CURFILEINFO_ST *pstCurFileInfo);

extern VOS_UINT32 USIMM_SelectFileByRelativePath(
    USIMM_SELECT_PARA_STUR             *pstSelectPara,
    USIMM_U16_LVDATA_STRU              *pstFilePath,
    USIMM_CURFILEINFO_ST               *pstCurFileInfo);

extern VOS_VOID USIMM_UpdateFilePath(USIMM_SELECT_PARA_STUR *pstSelectPara,
                                            USIMM_U16_LVDATA_STRU  *pstFilePath,
                                            USIMM_CURFILEINFO_ST   *pstUSIMMCurFileInfo);

extern VOS_VOID USIMM_UpdateFileByRelativePath(USIMM_SELECT_PARA_STUR *pstSelectPara,
                                            USIMM_U16_LVDATA_STRU  *pstFilePath,
                                            USIMM_CURFILEINFO_ST   *pstUSIMMCurFileInfo);

extern VOS_UINT32 USIMM_InitUsimGlobal(VOS_VOID);

extern VOS_UINT32 USIMM_InitSimGlobal(VOS_VOID);

extern VOS_UINT32 USIMM_Select2GApp(VOS_VOID);

extern VOS_UINT32 USIMM_Select3GApp(VOS_VOID);

extern VOS_VOID USIMM_Reselect3GApp(VOS_VOID);

extern VOS_UINT32 USIMM_RefreshAidVerify(VOS_UINT32 ulAidLen, VOS_UINT8 *pucAid);

extern VOS_UINT32 USIMM_InitUsimCardFileMap(VOS_VOID);

extern VOS_UINT32 USIMM_InitSimCardFileMap(VOS_VOID);

extern VOS_VOID USIMM_SciDataHook(VOS_UINT32 ulLength, VOS_UINT8 *pucData);

extern VOS_VOID USIMM_RefreshNoFileIndHandle(USIMM_STKREFRESH_REQ_STRU *pstMsg);

extern VOS_VOID USIMM_RefreshInd(USIMM_STKREFRESH_REQ_STRU *pstMsg);

extern VOS_UINT32 USIMM_SimRefreshFilePbAppCheck(VOS_UINT16 *pusFilePath, VOS_UINT32 ulPathLen);

extern VOS_UINT32 USIMM_UsimRefreshFilePbAppCheck(VOS_UINT16 *pusFilePath, VOS_UINT32 ulPathLen);

extern VOS_VOID USIMM_RefreshIsimFileIndHandle(USIMM_STKREFRESH_IND_STRU *pstRefreshMsg);

/*log����ӿ�*/
extern VOS_VOID USIMM_InitLogFile(VOS_VOID);

extern VOS_VOID USIMM_SaveLogFile(VOS_VOID);

extern VOS_VOID USIMM_LogDataSave(VOS_UINT8 *pucData, VOS_UINT8 ucDataLen);

extern VOS_VOID USIMM_ExcLogDataClear(VOS_VOID);

extern VOS_VOID USIMM_ExcLogDataSave(VOS_UINT8 *pucData, VOS_UINT8 ucDataLen);

extern VOS_VOID USIMM_ExcLogDataBK(VOS_VOID);

extern VOS_VOID USIMM_ExcLogDataRE(VOS_VOID);

extern VOS_VOID USIMM_SaveExcLogFile(VOS_VOID);

extern VOS_VOID USIMM_InitExcLogFile(VOS_VOID);

/*Base Func*/
extern VOS_UINT32  USIMM_PinStatusCheck(USIMM_PIN_CMD_TYPE_ENUM_UINT32 enCmdType,USIMM_PIN_TYPE_ENUM_UINT32 enPINType,VOS_UINT32 *pulResult);

extern VOS_UINT32 USIMM_SAT_TerminalResopnse(USIMM_CMDHEADER_REQ_STRU *pMsg);

extern VOS_UINT32 USIMM_SAT_Envelope(USIMM_CMDHEADER_REQ_STRU *pMsg);

extern VOS_UINT32 USIMM_PINHandle(USIMM_CMDHEADER_REQ_STRU *pMsg);

extern VOS_UINT32 USIMM_PinPreProcHandle( USIMM_PINHANDLE_REQ_STRU  *pNewstMsg, USIMM_PIN_REQ_STRU  *pPreMsg);

extern VOS_UINT32 USIMM_PinHandleCardStatusCheck(VOS_VOID);

extern VOS_UINT32 USIMM_StatusHandle(USIMM_CMDHEADER_REQ_STRU *pMsg);

extern VOS_UINT32 USIMM_UpdateFile(USIMM_EF_TYPE_ENUM_UINT32  enEFFileType, VOS_UINT8  ucRecordNum, VOS_UINT16  usDataLen,  VOS_UINT8  *pucData);

extern VOS_UINT32 USIMM_SetSPBFileHandle(USIMM_CMDHEADER_REQ_STRU *pstMsgHeader);

extern VOS_UINT32 USIMM_SetFileHandle(USIMM_MsgBlock *pMsg, USIMM_UPDATEFILE_REQ_STRU *pstNewMsg);

extern VOS_UINT32 USIMM_GetMaxRecordNum(USIMM_MsgBlock *pMsg, USIMM_QUERYFILE_REQ_STRU *pstNewMsg);

extern VOS_VOID USIMM_SAT_Fetch(VOS_UINT16 usLen);

extern VOS_UINT32 USIMM_GetRealFile(USIMM_GETFILE_REQ_STRU* pstOldMsg, USIMM_READFILE_REQ_STRU *pstNewMsg);

extern VOS_UINT32 USIMM_GetFileHandle(USIMM_GETFILE_REQ_STRU* pstOldMsg, USIMM_READFILE_REQ_STRU *pstNewMsg);

extern VOS_UINT32 USIMM_IsdbAccessHandle(USIMM_MsgBlock *pMsg);

extern VOS_VOID USIMM_ErrorLogProc(USIMM_CMDHEADER_REQ_STRU * pMsg);

#if(FEATURE_ON == FEATURE_PTM)
extern VOS_VOID USIMM_MsgProc(USIMM_CMDHEADER_REQ_STRU * pMsg);
#endif

extern VOS_UINT32 USIMM_ProtectFirstStep(VOS_UINT32  ulOldCardType);

extern VOS_UINT32 USIMM_UsimVoltageSwitch(VOS_UINT8 ucCharaByte, VOS_UINT8 *pucVoltageMismatchFlag);

extern VOS_VOID USIMM_UsimTerminalCapability(VOS_VOID);

extern VOS_UINT32 USIMM_AutoVerifyPIN(USIMM_PIN_ENABLE_STATUS_ENUM_UINT32 enPinEnable,    USIMM_PIN_VERIY_STATUS_ENUM_UINT32 *penPinVerified, VOS_UINT8 ucPinRefNum, VOS_UINT8 *paucPin);

extern VOS_VOID USIMM_QueryPINType(VOS_UINT8 *pucPINType);

extern VOS_UINT32 USIMM_HandlePINType(VOS_UINT8 ucCmdType, VOS_UINT32 *pulPINType);

extern VOS_UINT16 USIMM_IsimEFIDToUsimEFID(VOS_UINT16 usFileID);

extern VOS_UINT16 USIMM_UsimEFIDToIsimEFID(VOS_UINT16 usFileID);

extern VOS_UINT8 USIMM_GetMncLen(VOS_UINT8 *pucAdContent, VOS_UINT32 ulFileSize);

extern VOS_VOID USIMM_GetAsciiMCCAndMNC(VOS_UINT8 *pucAsciiImsi, VOS_UINT8 *pucAsciiMCC, VOS_UINT8 *pucAsciiMNC);

extern VOS_VOID USIMM_BcdNumToAsciiNum(VOS_UINT8 *pucAsciiNum, VOS_UINT8 *pucBcdNum, VOS_UINT8 ucBcdNumLen);

extern VOS_UINT32 USIMM_ImsiBcd2Ascii(VOS_UINT8 *pucAsciiStr);

extern VOS_UINT32 USIMM_InitIsimHandle(USIMM_CMDHEADER_REQ_STRU *pMsg);

extern VOS_UINT32 USIMM_GetReadFilePara(VOS_UINT8 ucRecordNum, USIMM_EFFCP_ST *pstEFInfo, USIMM_GETCNF_INFO_STRU *pstCnfInfo);

extern VOS_UINT32 USIMM_ReadFile(USIMM_EFFCP_ST               *pstCurEFFcp,
                                 VOS_UINT8                   ucRecordNum,
                                 VOS_UINT16                  usDataLen,
                                 VOS_UINT8                   *pucData);

extern VOS_UINT32 USIMM_IsSIMServiceAvailable(UICC_SERVICES_TYPE_ENUM_UINT32 enService);

extern VOS_UINT32 USIMM_IsUSIMServiceAvailable(UICC_SERVICES_TYPE_ENUM_UINT32 enService);

extern VOS_UINT32 USIMM_IsISIMServiceAvailable(UICC_SERVICES_TYPE_ENUM_UINT32 enService);

extern VOS_UINT32 USIMM_IsUIMServiceAvailable(UICC_SERVICES_TYPE_ENUM_UINT32 enService);

extern VOS_UINT32 USIMM_IsCSIMServiceAvailable(UICC_SERVICES_TYPE_ENUM_UINT32 enService);

extern VOS_UINT32 USIMM_GetFileFromCard(USIMM_GET_COMM_FILE_STRU *pstFileInfo, USIMM_GETCNF_INFO_STRU *pstCnfInfo);

extern VOS_UINT32 USIMM_CheckSetFilePara(USIMM_EFFCP_ST *pstCurEFFcp, VOS_UINT8 ucRecordNum, VOS_UINT16 usDataLen);

/*vSIM API*/
extern VOS_VOID USIMM_InitVsimGlobal(VOS_VOID);

extern VOS_UINT32 USIMM_SetVsimFile(USIMM_SETFILE_REQ_STRU *pstMsg, USIMM_UPDATEFILE_REQ_STRU *pstNewMsg);

extern VOS_UINT32 USIMM_GetVsimFile(USIMM_GETFILE_REQ_STRU  *pstOldMsg, USIMM_READFILE_REQ_STRU *pstNewMsg);

extern VOS_VOID USIMM_VsimConfidentialDataVerifyErrHandle(VOS_VOID);

extern VOS_UINT32 USIMM_VsimConfidentialDataVerify(VOS_VOID);

extern VOS_UINT32 USIMM_VsimBase16Decode(VOS_CHAR *pcSrc, VOS_UINT32 ulSrcLen, VOS_UINT8 *pucDst, VOS_UINT32 *pulDstLen);

extern VOS_VOID USIMM_VsimBase16Encode(VOS_UINT8 *pucSrc, VOS_UINT8 *pucDst, VOS_UINT32 ulLen);

extern VOS_UINT32 USIMM_AuthenVirtulSim(USIMM_AUTH_REQ_STRU *pstMsg);

extern VOS_UINT32 USIMM_AuthenVirtulUsim(USIMM_AUTH_REQ_STRU *pstMsg);

extern VOS_UINT32 USIMM_DeactiveVsim(USIMM_MsgBlock *pMsg);

extern VOS_UINT32 USIMM_InitVsimCard(USIMM_MsgBlock *pMsg);

extern VOS_VOID USIMM_ClearVsimGlobal(VOS_VOID);

extern VOS_UINT32 USIMM_VsimGetRealKiOpc(VOS_UINT8 *pucKi, VOS_UINT8 *pucOpc);

extern VOS_UINT32 USIMM_CheckVsimFileInPool(VOS_VOID);

extern VOS_UINT32 USIMM_AddVsimFileToPool(VOS_CHAR *pucFileStr, VOS_UINT32 ulStrLen, VOS_CHAR *pcValue, VOS_UINT32 ulValueLen);

extern VOS_UINT32 USIMM_AddVsimAuthPara(VOS_CHAR *pucFileStr, VOS_UINT32 ulFileLen, VOS_CHAR *pcValue, VOS_UINT32 ulValueLen);

extern VOS_UINT32 USIMM_AddVsimVerifyHashPara(VOS_CHAR *pucFileStr, VOS_UINT32 ulFileLen, VOS_CHAR *pcValue, VOS_UINT32 ulValueLen);

extern VOS_UINT32 USIMM_DecodeVsimEf(OAM_XML_NODE_STRU *pstXmlNode);

extern VOS_VOID USIMM_VsimDecodeCardType(VOS_CHAR *pucStr,VOS_UINT32 ulStrLen,USIMM_CARD_TYPE_ENUM_UINT32 *pulCardType);

extern VOS_VOID USIMM_VsimDecodeAuthType(VOS_CHAR *pucStr, VOS_UINT32 ulStrLen,USIMM_VSIM_AUTH_ENUM_UINT32*pulAuthType);

extern VOS_UINT32 USIMM_DecodeVsimRoot(OAM_XML_NODE_STRU *pstXmlNode,USIMM_CARD_TYPE_ENUM_UINT32 *pulCardType,USIMM_VSIM_AUTH_ENUM_UINT8 *pucAuthType);

extern VOS_UINT32 USIMM_DecodeVsimFile(VOS_UINT8 *pucData);

extern VOS_UINT8* USIMM_ReadVsimFile(VOS_UINT32 ulReadPID);

extern VOS_UINT32 USIMM_InitCardHandle(USIMM_CMDHEADER_REQ_STRU *pMsg);

extern VOS_UINT32 USIMM_VsimHUKDecode(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          ulSrcLen,
    VOS_UINT8                           *pucDst,
    VOS_UINT32                          *pulDstLen);

extern VOS_BOOL USIMM_CheckSupportAP(VOS_VOID);

extern VOS_UINT32 USIMM_DeactiveRealCard(USIMM_MsgBlock *pMsg);

extern VOS_VOID USIMM_CardStatusRegCbFuncProc(VOS_VOID);

extern VOS_UINT32 USIMM_CardStatusHandle(USIMM_CMDHEADER_REQ_STRU *pstMsg);

extern VOS_UINT32 USIMM_OpenChannel(VOS_UINT8 *pucChannelID, VOS_UINT32 *pulSessionId);

extern VOS_UINT32 USIMM_CloseChannel(VOS_UINT8 ucChannelID);

extern VOS_UINT32 USIMM_OpenChannelForCSIM(VOS_VOID);

extern VOS_UINT32 USIMM_CheckAIDFcp(VOS_UINT32                   ulChannelId,
                                             USIMM_APDU_ST               *pstUsimmApdu,
                                             USIMM_SENDTPDU_CNFINFO_STRU *pstDataCnf);

extern VOS_UINT8 USIMM_SearchCHCtrl(VOS_UINT32 ulSessionId);

extern VOS_VOID USIMM_AuthMsgTransferFillDataProc( USIMM_AUTHENTICATION_REQ_STRU *pstNewMsg, USIMM_AUTH_REQ_STRU *pstPrvMsg);

extern VOS_UINT32 USIMM_AuthMsgTransferProc( USIMM_AUTHENTICATION_REQ_STRU *pstNewMsg, USIMM_AUTH_REQ_STRU *pstPrvMsg);

extern VOS_UINT32 USIMM_AuthenticationHandle(USIMM_CMDHEADER_REQ_STRU *pMsg);

extern VOS_UINT32 USIMM_ChangeToOldApp(VOS_UINT32                   ulSenderPID,
                                       USIMM_FILEPATH_INFO_STRU    *pstFilePath,
                                       USIMM_CARDAPP_ENUM_UINT32    enNewAPP,
                                       VOS_UINT16                   usDFID,
                                       USIMM_APP_TYPE_ENUM_UINT32  *pstOldApp);

extern VOS_UINT32 USIMM_ReadFileHandle(USIMM_CMDHEADER_REQ_STRU *pstMsgHeader);

extern VOS_UINT32 USIMM_UpdateFileHandle(USIMM_CMDHEADER_REQ_STRU *pstMsgHeader);

extern VOS_UINT32 USIMM_FDNHandle(USIMM_CMDHEADER_REQ_STRU *pMsg);

extern VOS_UINT32 USIMM_QueryFileHandle(USIMM_CMDHEADER_REQ_STRU *pstMsgHeader);

extern VOS_UINT32 USIMM_SearchFileHandle(USIMM_CMDHEADER_REQ_STRU *pstMsgHeader);

extern VOS_UINT32 USIMM_SendTPDUDataHandle(USIMM_CMDHEADER_REQ_STRU *pstMsgHeader);

extern VOS_UINT32 USIMM_CheckChangeCardByICCID(VOS_VOID);

/*usimmcuim.c*/
#if (FEATURE_UE_MODE_CDMA == FEATURE_ON)
extern USIMM_CARD_VERSION_TYPE_UINT8   g_enCardVersionType;

extern USIMM_ADF_INFO_STRU             g_stCSIMADFInfo;

extern VOS_UINT8                       g_aucCUIMCstInfo[12];   /*����洢CST�ļ��Ŀռ�*/

extern VOS_UINT8                       g_ucCSIMESTInfo;

extern VOS_UINT8                       g_ucStoreEsMeidResult;

extern VOS_VOID UICC_InitCsimGlobal(VOS_VOID);

extern VOS_VOID UICC_InitUimGlobal(VOS_VOID);

extern VOS_VOID UICC_InitUICCGlobal(VOS_VOID);

extern VOS_VOID UICC_InitICCGlobal(VOS_VOID);

extern VOS_VOID UICC_SaveDFPinInfo(USIMM_ADF_INFO_STRU *pstADFInfo);

extern VOS_UINT32 UICC_InitDecodeEFDIR(VOS_VOID);

extern VOS_UINT32 UICC_InitCommResetStep(VOS_VOID);

extern VOS_VOID UICC_GetTerminalProfile(USIMM_STK_CFG_STRU *pstProfileContent);

extern VOS_UINT32 UICC_TerminalProfileDownload(VOS_VOID);

extern VOS_UINT32 UICC_InitCommCSIMStep(VOS_VOID);

extern VOS_UINT32 UICC_InitCommUIMStep(VOS_VOID);

extern VOS_UINT32 UICC_InitCommStep(VOS_VOID);

extern VOS_UINT32 UICC_SelectCSIMADF(VOS_VOID);

extern VOS_UINT32 UICC_InitCUIMTFileContent(VOS_UINT16 usFileID, USIMM_U8_LVDATA_STRU *pstFileData);

extern VOS_VOID UICC_InitCUIMTFile(VOS_UINT16 usFileID);

extern VOS_VOID UICC_InitCUIMEccFile(VOS_VOID);

extern VOS_VOID UICC_InitCUIMCstFile(VOS_VOID);

extern VOS_VOID UICC_InitCSIMEstFile(VOS_VOID);

extern VOS_UINT32 UICC_InitCUIMEsnMeid(VOS_VOID);

extern VOS_UINT32 UICC_GetPUKRemainTime(VOS_UINT8 ucPINNo, USIMM_ADF_INFO_STRU *pstADFInfo);

extern VOS_UINT32 UICC_GetPINRemainTime(VOS_UINT8 ucPINNo, USIMM_ADF_INFO_STRU *pstADFInfo);

extern VOS_UINT32 UICC_InitPINRemainTime(USIMM_ADF_INFO_STRU *pstADFInfo);

extern VOS_UINT32 UICC_InitCardAppPINInfo(USIMM_CARD_VERSION_TYPE_UINT8 enCardVersionType, USIMM_ADF_INFO_STRU *pstADFInfo);

extern VOS_VOID UICC_AdjudgeAppState(USIMM_CARD_APP_INFO_ST *pstAppState, USIMM_ADF_INFO_STRU *pstADFInfo);

extern VOS_UINT32 UICC_InitCSIMNeedPINStep(VOS_VOID);

extern VOS_UINT32 UICC_InitCSIM(VOS_VOID);

extern VOS_VOID UICC_UIMFdnRequest(USIMM_FDNSTATUS_ENUM_UINT32 *pulFdnStatus);

extern VOS_VOID UICC_UimFDNProcedure(VOS_VOID);

extern VOS_VOID UICC_CsimFDNCheck(VOS_VOID);

extern VOS_UINT32 UICC_InitUIMNeedPINStep(VOS_VOID);

extern VOS_UINT32 UICC_InitUIM(VOS_VOID);

extern VOS_UINT32 UICC_InitCardHandle(USIMM_MsgBlock *pMsg);

extern VOS_UINT32 USIMM_SelectCdmaFile(USIMM_FILE_NEED_FCP_ENUM_UINT32 enEfFcpFlag, VOS_UINT32 ulPathLen, VOS_UINT16 *pusFilePath);

extern VOS_UINT32 USIMM_SetCdmaFileHandle(USIMM_MsgBlock *pMsg, USIMM_UPDATEFILE_REQ_STRU *pstNewMsg);

extern VOS_UINT32 USIMM_GetCdmaFileFromCard(USIMM_GET_COMM_FILE_STRU *pstFileInfo, USIMM_GETCNF_INFO_STRU *pstCnfInfo);

extern VOS_UINT32 USIMM_GetCdmaFileHandle(USIMM_MsgBlock *pstMsg, USIMM_CMDHEADER_REQ_STRU *pstReqMsg);

extern VOS_UINT32 USIMM_BSChallengeHandle(USIMM_CMDHEADER_REQ_STRU *pstMsg);

extern VOS_UINT32 USIMM_ManageSsdHandle(USIMM_CMDHEADER_REQ_STRU *pMsg);

extern VOS_UINT32 USIMM_GenerateKeyVpmHandle(USIMM_CMDHEADER_REQ_STRU *pMsg);

extern VOS_UINT32 USIMM_CdmaAuthHandle(USIMM_AUTH_REQ_STRU *pMsg);

extern VOS_UINT32  USIMM_SearchHandle(USIMM_SEARCH_REQ_STRU *pstOldMsg, USIMM_SEARCHFILE_REQ_STRU *pstNewMsg);

extern VOS_UINT32 USIMM_PBInitStatusIndHandle(USIMM_CMDHEADER_REQ_STRU *pMsg);

#endif /*(FEATURE_UE_MODE_CDMA == FEATURE_ON)*/

/*�ⲿ�ӿ�*/
extern VOS_VOID HPA_USIMLowPowerLock( VOS_UINT32 ulPid );

extern VOS_VOID HPA_USIMLowPowerUnLock( VOS_UINT32 ulPid );

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
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

#endif /* end of UsimmBase.h*/

