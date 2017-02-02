

#ifndef __MMA_APPLOCAL_H__
#define __MMA_APPLOCAL_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "Ps.h"
#include "MnComm.h"
#include "Taf_Tafm_Remote.h"
#include "Taf_Common.h"
#include "Taf_Tafm_Local.h"
#include "TafAppMma.h"
#include "NasUtranCtrlInterface.h"
/* Added by wx270776 for OM�ں�, 2015-6-27, begin */
#include "TafLog.h"
/* Added by wx270776 for OM�ں�, 2015-6-27, end */

/* ɾ��ExtAppMsccInterface.h*/


#include "Taf_Status.h"
#include "Taf_Status_Itf.h"

#include "NVIM_Interface.h"
#include "UsimPsInterface.h"
#include "CardLockCipher.h"
#include "siappstk.h"
#include "MmaMsccInterface.h"

#include "NasNvInterface.h"

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
#include "TafMtcApi.h"
#endif

#include "MtcMmaInterface.h"
#include "TafMmaCtx.h"



#pragma pack(4)
/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define MMA_SUCCESS     STA_SUCCESS
#define MMA_ERROR       STA_ERROR
#define MMA_FAILURE     TAF_FAILURE
/* BEGIN: Added by liuyang id:48197, 2006/3/13   PN:A32D02500*/
#define MMA_NORMAL      0X10
/* END:   Added by liuyang id:48197, 2006/3/13 */

#if 0
#define MMA_TRUE     1
#define MMA_FALSE    0
#endif

#define MMA_INVALID_INDEX                (65535)


#define MMA_WRITE_NVIM_TRUE        0
#define MMA_WRITE_NVIM_FALSE       1

#define MMA_HS_ID                  12345678

#define MMA_HS_PROTOCOL_APP        0
#define MMA_HS_PROTOCOL_BOOT       1

#define MMA_HS_ONLINE              0
#define MMA_HS_OFFLINE             1
#define MMA_HS_LPM                 2

#define MMA_HS_PRODUCT_CLASS_GW            0
#define MMA_HS_PRODUCT_CLASS_CDMA_1X       1
#define MMA_HS_PRODUCT_CLASS_CDMA_EVDO     2

/*��Ʒ��ID��ÿһ���Ʒ��Ϊ�������һ��Ψһ��ID, Balongû�в�Ʒ��Ŀǰ���ն�E800A��Ʒ��ͬ*/
#define MMA_HS_PRODUCT_ID                  56

#define MMA_PRINT_INFO    PS_LOG_LEVEL_INFO

#define MMA_PRINT_NORMAL  PS_LOG_LEVEL_NORMAL
/*normal: �������ԵĴ�ӡ���������ĳ��ģ���յ�����_REQ��Ϣ��Ȼ������XX_CNF
  ��Ϣ�ȣ�
  ͨ����ӡ������ֱ���˽����̵Ľ�չ�Լ��ڸ���ģ�������ִ����������������Ǳ�
  ���ӡ������:
  a. ״̬�½�����Ϣ���
  "PID����:��ģ������(��ѡ):ʵ����ʶ(��ѡ):STATE **state RECEIVE **msg\n"
  b. ״̬�·�����Ϣ���
  "PID����:��ģ������(��ѡ):ʵ����ʶ(��ѡ):STATE **state SEND **msg \n"
  c. ״̬��Ǩ���
  "PID����:��ģ������(��ѡ):ʵ����ʶ(��ѡ):STATE **state CHANGE TO **state\n"

  b. ��״̬������
  "PID����:��ģ������(��ѡ):ʵ����ʶ(��ѡ):������:NORMAL:****\n"

  ����ʵ����ʶ��ָ���ڶ�ʵ����ģ����APS����Ҫ��ӡ����ǰ�����ʵ���ż�Tiֵ*/

#define MMA_PRINT_WARNING PS_LOG_LEVEL_WARNING
/*warning: һ���Ƕ�һ���Ѿ����Ƶ����쳣���̷�����Ĵ������緢��ĳ����Ϣ��
  �����ڶ�ʱ����ʱ��
  ������ʧ�ܣ���ͨ��warningͨ������ʧ�ܣ��������յ�����ģ�����Ĳ�����Ҳͨ
  ��warning���:
  "PID����:��ģ������(��ѡ):ʵ����ʶ(��ѡ):������:WARNING:****\n"*/

#define MMA_PRINT_ERROR   PS_LOG_LEVEL_ERROR
/*error: һ���Ƿǳ����صĴ����ͣ������ڴ�����ʧ�ܣ�������ʱ��ʧ�ܣ�״̬Ǩ
  �Ƶ�δ֪״̬��:
  "PID����:��ģ������(��ѡ):ʵ����ʶ(��ѡ):������:ERROR:****\n"*/

#define NAS_LOG( ModulePID, SubMod, Level, String )    TAF_LOG(ModulePID, SubMod, Level, String)
#define NAS_LOG1( ModulePID, SubMod, Level, String, Para )     TAF_LOG1(ModulePID, SubMod, Level, String, Para)
#define NAS_LOG2( ModulePID, SubMod, Level, String, Para1, Para2 )    TAF_LOG2(ModulePID, SubMod, Level, String, Para1, Para2)
#define NAS_LOG3( ModulePID, SubMod, Level, String, Para1, Para2, Para3 ) TAF_LOG3(ModulePID, SubMod, Level, String, Para1, Para2, Para3)
#define NAS_LOG4( ModulePID, SubMod, Level, String, Para1, Para2, Para3, Para4 )  TAF_LOG4(ModulePID, SubMod, Level, String, Para1, Para2, Para3, Para4)


#define MMA_LOG( Level, String )        NAS_LOG( WUEPS_PID_MMA, TAF_MMA, Level, String )
#define MMA_LOG1( Level, String, Para ) NAS_LOG1( WUEPS_PID_MMA, TAF_MMA, Level, String, Para )
/* BEGIN: Added by liuyang id:48197, 2006/3/16   PN:A32D02412*/
#define MMA_INFOLOG( String )   MMA_LOG( MMA_PRINT_INFO, String)
#define MMA_INFOLOG1( String, Para )  MMA_LOG1( MMA_PRINT_INFO, String, Para)
/* END:   Added by liuyang id:48197, 2006/3/16 */
#define MMA_NORMAILLOG( String )    MMA_LOG( MMA_PRINT_NORMAL, String )
#define MMA_WARNINGLOG( String )    MMA_LOG( MMA_PRINT_WARNING, String )
#define MMA_WARNINGLOG1( String, Para )    MMA_LOG1( MMA_PRINT_WARNING, String, Para )
#define MMA_ERRORLOG( String )      MMA_LOG( MMA_PRINT_ERROR, String )
#define MMA_ERRORLOG1( String, Para )     MMA_LOG1(MMA_PRINT_ERROR, String, Para)

/* BEGIN: Added by liuyang id:48197, 2006/3/24   PN:A32D02755*/
/*�ڴ������صĺ궨������*/
#define MMA_ALLOC_MSG_WITHOUT_HEADER_LEN(pMsg, ulLen ) PS_ALLOC_MSG_WITHOUT_HEADER_LEN(pMsg, WUEPS_PID_MMA , ulLen)
#define MMA_ALLOC_MSG_WITHOUT_HEADER_LEN_RTN_FAIL(pMsg, ulLen) PS_ALLOC_MSG_RTN_FAIL_WITHOUT_HEADER_LEN(pMsg, WUEPS_PID_MMA , ulLen)
#define MMA_ALLOC_MSG_WITH_HEADER_LEN(pMsg, ulLen ) PS_ALLOC_MSG(pMsg, WUEPS_PID_MMA , ulLen)
#define MMA_ALLOC_MSG_WITH_HEADER_LEN_RTN_FAIL(pMsg, ulLen ) PS_ALLOC_MSG_RTN_FAIL(pMsg, WUEPS_PID_MMA , ulLen)
#define MMA_FREE_MSG(pMsg) PS_FREEMSG(WUEPS_PID_MMA, pMsg)
#define MMA_MEM_ALLOC(pMem, ulLen) PS_MEM_ALLOC_UNRTN(pMem, WUEPS_PID_MMA , ulLen)
#define MMA_MEM_ALLOC_RTN_FAIL(pMem, ulLen) PS_MEM_ALLOC_RTN_FAIL(pMem, WUEPS_PID_MMA , ulLen)
#define MMA_FREE_MEM(pBuffer) PS_MEM_FREE(WUEPS_PID_MMA,pBuffer)
#define MMA_MEM_CPY(pDestBuffer,pSrcBuffer,ulBufferLen) PS_MEM_CPY(pDestBuffer,pSrcBuffer,ulBufferLen)
#define MMA_MEM_SET(pBuffer,ucData,ulBufferLen) PS_MEM_SET(pBuffer,ucData,ulBufferLen)
/*����ϵͳ��Ϣ�����ض���*/
#define MMA_SND_MSG(pMsg) PS_SEND_MSG(WUEPS_PID_MMA, pMsg)
/* END:   Added by liuyang id:48197, 2006/3/24 */

/* BEGIN: Added by liuyang id:48197, 2006/3/27   PN:A32D02372*/
#define MMA_PLMN_MCC_NONE       0x00
#define MMA_PLMN_MNC_NONE       0x00
/* END:   Added by liuyang id:48197, 2006/3/27 */

/*2GƵ������*/
typedef VOS_UINT16 GSMBANDTYPE;
#define GSM_BAND_NULL                   0x0
#define GSM_BAND_450                    0x0001        /* ARFCN�������Ƶ��:GSM 450 */
#define GSM_BAND_480                    0x0002        /* ARFCN�������Ƶ��:GSM 480 */
#define GSM_BAND_850                    0x0004        /* ARFCN�������Ƶ��:GSM 850 */
#define GSM_BAND_P900                   0x0008        /* ARFCN�������Ƶ��:P-GSM 900 */
#define GSM_BAND_R900                   0x0010        /* ARFCN�������Ƶ��:R-GSM 900 */
#define GSM_BAND_E900                   0x0020        /* ARFCN�������Ƶ��:E-GSM 900 */
#define GSM_BAND_1800                   0x0040        /* ARFCN�������Ƶ��:DCS 1800 */
#define GSM_BAND_1900                   0x0080        /* ARFCN�������Ƶ��:PCS 1900 */
#define GSM_BAND_700                    0x0100        /* ARFCN�������Ƶ��:GSM 700,��֧�� */
#define GSM_BAND_ALL                   ( GSM_BAND_850|GSM_BAND_P900  \
                                        |GSM_BAND_R900|GSM_BAND_E900 \
                                        |GSM_BAND_1800|GSM_BAND_1900 )
/*3GƵ������*/
typedef VOS_UINT16 WCDMABANDTYPE;
#define WCDMA_BAND_NULL                 0x0000
#define WCDMA_BAND_I                    0x0001
#define WCDMA_BAND_II                   0x0002
#define WCDMA_BAND_III                  0x0004
#define WCDMA_BAND_IV                   0x0008
#define WCDMA_BAND_V                    0x0010
#define WCDMA_BAND_VI                   0x0020
#define WCDMA_BAND_VII                  0x0040
#define WCDMA_BAND_VIII                 0x0080
#define WCDMA_BAND_IX                   0x0100

#define WCDMA_BAND_ALL             ( WCDMA_BAND_I  \
                                    |WCDMA_BAND_II \
                                    |WCDMA_BAND_V )


#define MMA_PS_ATTACH              1
#define MMA_CS_ATTACH              2
#define MMA_PS_CS_ATTACH           3
#define MMA_UNKNOW_ATTACH          4

#define MMA_PS_DETACH              1
#define MMA_CS_DETACH              2
#define MMA_PS_CS_DETACH           3

#define MMA_NONEED_PIN1            0
#define MMA_NEED_PIN1              1
#define MMA_NEED_PUK1              2
#define MMA_ENABLE_PIN1_NONEED     3
#define MMA_PUK1_REMAINS_ZERO      4
#define MMA_PUK1_NONEED            5
#define MMA_PIN1_STATUS_FAIL     255

#define MMA_USIM_PRESENT           1
#define MMA_USIM_ABSENT            0
#define MMA_USIM_NOREADY           255

#define MMA_RSSI_UPPER_LIMIT       0
#define MMA_RSSI_LOWER_LIMIT       (-113)

#define MMA_USIM_FILE_EF_NETPAR_GSM_SIZE        72
#define MMA_USIM_FILE_EF_NETPAR_ID              0x6FC4

#define MMA_SIM_FILE_EF_NETPAR_GSM_SIZE         16
#define MMA_SIM_FILE_EF_NETPAR_ID               0x6F74
#define MMA_USIM_TYPE_SIM       0
#define MMA_USIM_TYPE_USIM      1
#define MMA_CLIENTID_NONE       (TAF_MAX_CLIENT_OF_ONE_PROC + 1)
#define MMA_OP_ID_INTERNAL      TAF_INVALID_TAB_INDEX
#define MMA_CLIENTID_BROADCAST  TAF_CLIENTID_BROADCAST
#define TAF_UICC_STATUS_CHANGE                  1
#define TAF_UICC_STATUS_UNCHANGE                0

#define NAS_MMA_AUTOMATIC_START  0
#define NAS_MMA_MANUAL_START     1


/*
  2 minimum functionality
  3 full functionality
  0 disable phone transmit RF circuits only
  1 ensable phone receive RF circuits only
*/
#define TAF_PH_MINI_FUN              2
#define TAF_PH_FULL_FUN              3

#define    MMA_QUICK_START_DISABLE    0x00000000
#define    MMA_QUICK_START_ENABLE     0x01000101
#define    MMA_AUTO_ATTACH_DISABLE    0x00000000
#define    MMA_AUTO_ATTACH_ENABLE     0x00000001
#define    MMA_BIT_ISVALID(a,bit) (((a)&(bit))==(bit))
#define    MMA_RF_AUTO_TEST_DISABLE   0x0
#define    MMA_RF_AUTO_TEST_ENABLE    0x1
#define    MMA_PS_DELAY_DISABLE       0x0                                       /* ����AT+CFUN=6֮��PS���ӳ�5�����Onlinģʽ */
#define    MMA_PS_DELAY_ENABLE        0x1                                       /* ����AT+CFUN=6֮��PS�ӳ�5�����Onlinģʽ */
#define    MMA_NV_RESUME_DISABLE      0x0                                       /* ����AT+CFUN=6֮��PS���ӳ�5�����Onlinģʽ */
#define    MMA_NV_RESUME_ENABLE       0x1                                       /* ����AT+CFUN=6֮��PS�ӳ�5�����Onlinģʽ */


#define TAF_MMA_GetNotDisplayLocalNetworkNameFlg()     (gstMmaValue.ucNotDisplayLocalNetworkNameFlg)

#define MMA_UMTS_UEA0                                       (0)
#define MMA_UMTS_UEA1                                       (8)
#define MMA_UMTS_UEA2                                       (9)

/* ����6F15�ļ���SERVICE GROUP CODEֵ */
#define TAF_MMA_SERVICE_GROUP_CODE_IN_CUSTOMER_SERVICE_PROFILE_FILE    (0xC0)

/* ����6F15�ļ���PLMN MODEλ */
#define TAF_MMA_PLMN_MODE_IN_SERVICE_GROUP_CODE                        (0x80)

/* ����6F15�ļ���PLMN MODEλ��ƫ���� */
#define TAF_MMA_PLMN_MODE_OFFSET_IN_SERVICE_GROUP_CODE                 (7)

/* ����6F15�ļ�ÿ��GROUP�ĳ��� */
#define TAF_MMA_GROUP_LEN_IN_CUSTOMER_SERVICE_PROFILE_FILE             (2)


#define MMA_INVALID_MCC                                 (0xffffffff)            /* MCC����Чֵ */
#define MMA_INVALID_MNC                                 (0xffffffff)            /* MNC����Чֵ */

/* �ú궨���MmcMmaItf.h�ļ���Ų������MmcMmaItf.h����MSCC�ܹ��������ļ�ɾ�� */
/*����RSSI��RSCP����Чֵ*/
#define MMA_UTRA_RSCP_INVALID                           (-140)
#define MMA_UTRA_RSSI_INVALID                           (-120)

#define MMA_INVALID_SID                                 (-1)
#define MMA_INVALID_NID                                 (-1)

/*******************************************************************************
  3 ö�ٶ���
*******************************************************************************/

enum MN_PH_REG_TIME_STATE_ENUM
{
    MN_PH_REG_TIME_STATE_BEGIN,
    MN_PH_REG_TIME_STATE_END,
    MN_PH_REG_TIME_STATE_PINVALID,
    MN_PH_REG_TIME_STATE_BUTT
} ;
typedef VOS_UINT8 MN_PH_REG_TIME_STATE_ENUM_U8;

typedef struct
{
    MN_PH_REG_TIME_STATE_ENUM_U8    enRegTimeState;
    VOS_UINT32                      ulBeginTick;
    VOS_UINT32                      ulEndTick;
    VOS_UINT32                      ulCostTime;
} MN_PH_REG_TIME_INFO_STRU;

typedef struct
{
    TAF_SDC_PLMN_ID_STRU            stPlmn;
    TAF_SDC_SYS_MODE_ENUM_UINT8     enSysMode;
    TAF_SDC_REPORT_SRVSTA_ENUM_UINT8 enServiceStatus;
    VOS_UINT16                      usLac;
    VOS_UINT32                      ulCellId;
}TAF_MMA_LOCATION_STATUS_EVENT_INFO_STRU;



/*****************************************************************************
 ö����    : MMA_CIPHER_ALGOR_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ��ǰW�¼����㷨ö��
*****************************************************************************/
enum MMA_CIPHER_ALGOR_ENUM
{
    MMA_CIPHER_ALGOR_UEA0                 = 0,                /* ����δ�� */
    MMA_CIPHER_ALGOR_UEA1                 = 1,
    MMA_CIPHER_ALGOR_UEA2                 = 2,
    MMA_CIPHER_ALGOR_BUTT
};
typedef VOS_UINT8  MMA_CIPHER_ALGOR_ENUM_UINT8;

typedef struct   TAF_PMU_STATE
{
    unsigned short  charger_PowerOn;         /*1��ʾ��翪����0��ʾ��������*/
    unsigned short  chargerstate;            /* 1��ʾ����У� 0��ʾ���ڳ��*/
    unsigned short  bal_Volt;                /*��ص�ѹ����0��100��200����900��10����0ʱ�ػ���100ʱ������ �����ʾ����ͬ�⼸����Ӧ*/
    unsigned short  chg_timer_overflow;      /*  1��ʾ��糬ʱ������ػ���0��ʾ����*/
    unsigned short  bat_out;                 /* 1��ʾ ��ذγ���0��ʾδ�γ�*/
}TAF_PMU_STATE_STRU;

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
/* move those structure ctx */

typedef VOS_UINT8 TAF_SERVICE_MODE;
#define  TAF_SERVICE_NULL     0       /*PS��CSҵ��û��ʹ��*/
#define  TAF_SERVICE_CS_PS    1       /*PS��CSҵ��ʹ�� */
#define  TAF_SERVICE_PS       2       /*��PSҵ��ʹ�� */
#define  TAF_SERVICE_CS       3       /*��CSҵ��ʹ�� */
#define  TAF_SERVICE_NOCHANGE 4       /*���ı������ */

typedef struct
{
    TAF_PH_PIN_DATA_STRU         stMmaPinData;
    VOS_UINT16                ClientId;
    VOS_UINT8                       OpId;
}MMA_PIN_OP_ST;

typedef enum
{
    MMA_SET_CLASSTYPE_DE_ATTACH_DISABLE = 0,
    MMA_SET_CLASSTYPE_DETACH_ENABLE,
    MMA_SET_CLASSTYPE_ATTACH_ENABLE,
    MMA_SET_CLASSTYPE_DE_ATTACH_ENABLE,
    MMA_SET_CLASSTYPE_DE_ATTACH_FLG_BUTT
}MMA_SET_CLASSTYPE_DE_ATTACH_FLG_ENUM;

typedef struct
{
    TAF_PH_MS_CLASS_TYPE                     MsClassType;             /*�ֻ������趨*/
    TAF_PH_MS_CLASS_TYPE                     NewMsClassType;          /*�����õ��ֻ�����*/
}MMA_SET_MS_CLASS_TYPE_ST;

typedef VOS_UINT16   MMA_SYS_CFG_SET_FLG;
#define  MMA_SYS_CFG_NONE_SET                               0x0000 /*����Ϊ��*/

typedef struct
{
    VOS_UINT16                          usClientId;     /*Client Id*/
    VOS_UINT8                           ucOpId;         /*Operate Id*/
    VOS_UINT8                           aucReserved[1];
}MMA_EOPLMN_SET_STRU;

/*��ʾ��ʼ�����̵�״̬*/
typedef enum
{
    MMA_INIT_POWERON  = 0,
    MMA_INIT_NOUSIM,
    MMA_INIT_NONVIM,
    MMA_INIT_FIN,
    MMA_INIT_STA_BUTT
}MMA_INIT_STA_ENUM;

/*������ʼ���Ĳ�������*/
typedef enum
{
    MMA_INIT_DEFAULT,
    MMA_INIT_OUTSIDE,
    MMA_INIT_TYPE_BUTT
}MMA_INIT_TYPE_ENUM;

/*����һ��ȫ�����ݱ�,��Ϊд��NVIMʹ��*/
typedef struct
{
    MN_MMA_CPAM_RAT_TYPE_ENUM_UINT8    AccessMode;      /*�ֻ�����ģʽ*/
    TAF_PH_PLMN_PRIO PlmnPrio;        /*PLMN�������ȼ�*/

}MMA_PARA_TAB_ST;

/*���ڴ�������nvim�е���Ӫ����Ϣ*/

/*�ֻ�ģʽ�����л�����*/
typedef enum
{
    MMA_CC2CG   = (TAF_PH_MS_CLASS_CC<<4)|TAF_PH_MS_CLASS_CG,
    MMA_CC2A    = (TAF_PH_MS_CLASS_CC<<4)|TAF_PH_MS_CLASS_A,
    MMA_CC2NULL = (TAF_PH_MS_CLASS_CC<<4)|TAF_PH_MS_CLASS_NULL,
    MMA_CG2CC   = (TAF_PH_MS_CLASS_CG<<4)|TAF_PH_MS_CLASS_CC,
    MMA_CG2A    = (TAF_PH_MS_CLASS_CG<<4)|TAF_PH_MS_CLASS_A,
    MMA_CG2NULL = (TAF_PH_MS_CLASS_CG<<4)|TAF_PH_MS_CLASS_NULL,
    MMA_A2CC    = (TAF_PH_MS_CLASS_A<<4)|TAF_PH_MS_CLASS_CC,
    MMA_A2CG    = (TAF_PH_MS_CLASS_A<<4)|TAF_PH_MS_CLASS_CG,
    MMA_A2NULL  = (TAF_PH_MS_CLASS_A<<4)|TAF_PH_MS_CLASS_NULL,
    MMA_NULL2CC = (TAF_PH_MS_CLASS_NULL<<4)|TAF_PH_MS_CLASS_CC,
    MMA_NULL2CG = (TAF_PH_MS_CLASS_NULL<<4)|TAF_PH_MS_CLASS_CG,
    MMA_NULL2A  = (TAF_PH_MS_CLASS_NULL<<4)|TAF_PH_MS_CLASS_A,
    MMA_CLASS_CHANGE_INDEX_BUTT
}MMA_CLASS_CHANGE_INDEX_ENUM;

/*MMA�ڲ�ʹ�õ��ź�ǿ�ȱ���*/
typedef struct
{
    VOS_INT32        lRssiValue;
    VOS_UINT8        ucRssiValue4AT;
    VOS_UINT8        ucChannalQual;
}MMA_RSSI_VALUE_ST;

typedef struct
{
    MMA_RSSI_VALUE_ST       astRssi[TAF_PH_RSSI_MAX_NUM];
    VOS_UINT8               ucRssiNum;
}MMA_RSSI_VALUE_LIST_ST;



typedef VOS_UINT8   MMA_PLMN_SPECIALIZE_FLG;
#define MMA_PLMN_SPECIALIZE_NORMAL        0
#define MMA_PLMN_SPECIALIZE_MANUALAUTO    1

typedef struct
{
    TAF_PH_ICC_ID_STRU           stIccId;
    VOS_UINT16                   ClientId;
    VOS_UINT8                    OpId;
}MMA_GET_ICC_ID_ST;


typedef struct
{
    VOS_UINT16                          usCurrIndex;                    /* ������Ҫ��ȡ��PNN list��ʼλindex */
    VOS_UINT16                          usReadNum;                      /* ���ζ�ȡ��PNN ��Ŀ */
} TAF_MMA_PLMN_LIST_CTRL_STRU;

typedef struct
{
    VOS_UINT16                          usCurrIndex;                    /* ������Ҫ��ȡ��PNN list��ʼλindex */
    VOS_UINT16                          usReadNum;                      /* ���ζ�ȡ��PNN ��Ŀ */
    TAF_PH_ICC_TYPE                     Icctype;                        /* ��¼�������� */
    VOS_UINT8                           aucReserve[3];
}MMA_READ_PNN_LIST_CTRL_STRU;
typedef struct
{
    VOS_UINT16                          usSumPnnNumInSim;               /* ����PNN����Ŀ */
    VOS_UINT16                          usEfLen;                        /* EF�ļ�����(�Զ�������˵���ļ����ȣ��������ļ���˵�Ǽ�¼����)*/
    VOS_UINT8                          *pucPnnData;                       /* ��¼�ӿ����������PNN�б��׵�ַ */
}MMA_READ_PNN_LIST_DATA_STRU;
typedef struct
{
    MMA_READ_PNN_LIST_CTRL_STRU         stPnnListCtrInfo;

    /* Deleted by c00318887 for AT&T phaseII, 2015-3-6, begin */
    /* Deleted by c00318887 for AT&T phaseII, 2015-3-6, end */
}MMA_READ_PNN_LIST_INFO_STRU;

typedef struct
{
    VOS_UINT16                   ClientId;
    VOS_UINT8                    OpId;
    VOS_UINT8                    aucReserve[1];
    MMA_READ_PNN_LIST_INFO_STRU  stPnnListInfo;
}MMA_GET_PNN_ST;

typedef struct
{
    VOS_UINT16                   ClientId;
    VOS_UINT8                    OpId;
}MMA_GET_OPL_ST;


typedef struct
{
    VOS_UINT16                   usClientId;
    VOS_UINT8                    ucOpId;
    VOS_UINT8                    ucHplmnQryFlag;
}TAF_MMA_GET_HPLMN_STRU;

typedef struct
{
    VOS_UINT16                   ClientId;
    VOS_UINT8                    OpId;

    #define MMA_CPNN_WAIT_NULL            0
    #define MMA_CPNN_WAIT_PNN_FLAG        1
    #define MMA_CPNN_WAIT_OPL_FLAG        2
    VOS_UINT8                    ucWaitPnnOPLMask;

    VOS_UINT32                   ulPNNGetRslt;
    TAF_PH_USIM_CPNN_CNF_STRU    stCpnnCnf;
}MMA_GET_CPNN_ST;


typedef struct
{
    VOS_UINT8 ucEnableFlag;
    VOS_UINT8 ucForbidReg2GNetWork;
    VOS_UINT8 ucForbidSndMsg;
    VOS_UINT8 aucReserve[13];
}MMA_EFUST_SERVICE_CFG_STRU;


/* remove this data structure to ctx */

typedef struct
{
    VOS_UINT16                   usClientId;
    VOS_UINT8                    ucOpId;

    VOS_UINT8                    ucReserve;
}MMA_NET_SCAN_STRU;


#define TI_TAF_MMA_NET_SCAN_TIMER_LEN                       (108 * 1000)
#define TI_TAF_MMA_ABORT_NET_SCAN_TIMER_LEN                 (10 * 1000)




typedef struct
{
    STATUS_CONTEXT_STRU          *pg_StatusContext;
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/*----------  MMA����ȫ�ֱ���  -----------*/
/*=======================================================*/
    MMA_PIN_OP_ST                       stOpPinData;                /*MMA��PIN���������*/

    MMA_SET_MS_CLASS_TYPE_ST            stSetMsClass;               /*�ֻ�����������ر�־����*/

    MMA_RSSI_VALUE_LIST_ST              stRssiValue;                /*�ֻ��ź�ǿ��*/
    TAF_MMA_BATTERYPOWER_STRU           stBatteryPower;             /*�ֻ���ع���*/
    TAF_PH_MEINFO_STRU                  stMeInfo;                   /*�ֻ�������Ϣ*/
    TAF_USIM_INFO_STRU                  stUsimInfo;                 /*USIM�����Ϣ*/
    MMA_QUICK_START_STA_UINT32          ulQuickStartFlg;
    MMA_GET_ICC_ID_ST                   stGetIccId;
    MMA_GET_PNN_ST                      stPNN;                  /*��ȡPNN�ļ�����*/
    MMA_GET_OPL_ST                      stOPL;                  /*��ȡOPL�ļ�����*/
    TAF_MMA_GET_HPLMN_STRU              stGetHplmn;                  /*��ȡOPL�ļ�����*/
    VOS_UINT8                           aucReserved1[2];
    MMA_EFUST_SERVICE_CFG_STRU          stEfustServiceCfg;


    VOS_UINT8                           ucReserved2;

    VOS_UINT8                           ucRoamFeatureStatus;
    VOS_UINT8                           ucRoamBrokerSwitch;         /* �Ƿ��roaming broker.VOS_TRUE:��;VOS_FALSE:���򿪡�Ĭ�Ϲر� */



    VOS_UINT8                           ucReportPlmnFlg;

    VOS_UINT8                           ucNotDisplayLocalNetworkNameFlg;

    TAF_PH_RSSI_STRU                      stCerssiValue;                  /* �������������ϱ����ź�������Ϣ */



    MMA_EOPLMN_SET_STRU                 stEOPlmnSet;
    MMA_NET_SCAN_STRU                   stNetScan;
}TAF_MMA_GLOBAL_VALUE_ST;

typedef enum
{
    MMA_STORED_CLIENT_OPID_OP_READ,
    MMA_STORED_CLIENT_OPID_OP_WRITE,
    MMA_STORED_CLIENT_OPID_OP_BUTT
}MMA_STORED_CLIENT_OPID_OP_ENUM;

typedef struct
{
    VOS_UINT16                          ausClientID[6];/* MMA�й�6��client id ��Ҫ���� */
    VOS_UINT8                           aucOPID[6];
}MMA_STORED_CLIENT_OPID_ST;



typedef struct
{
    VOS_UINT8                           ucActiveFlag;
    VOS_UINT8                           ucForbStatus;
    VOS_UINT8                           aucReserve[2];
    TAF_USER_SET_PREF_BAND64            stForbBand; /* NV����ԭʼ��NV��¼ */
    VOS_UINT32                          ulForbBand; /* �ڲ�ʹ�õ�Ƶ����Ϣ */
}MMA_UE_FORB_BAND_ST;

/*��PIN�Ĳ�����������ݽṹ*/
typedef struct TAF_USIM_OPPIN_CNF_MSG
{
    VOS_MSG_HEADER
    TAF_MSG_TYPE                           MsgType;
    TAF_PH_PIN_CNF_STRU                    stPinCnf;
}TAF_USIM_OPPIN_CNF_MSG_ST;
typedef struct TAF_USIM_READ_SPN_CNF_MSG
{
    VOS_MSG_HEADER
    TAF_MSG_TYPE                           MsgType;
    TAF_PH_USIM_SPN_CNF_STRU               stSpnCnf;
}TAF_USIM_READ_SPN_CNF_MSG_ST;

#define TAF_SIM_TIMER_NUM 1
/* 1��Sim������������ʱ��: 0:����pin���� */
enum MN_PH_SIM_TIMER_ENUM
{
    MN_PH_SIM_TIMER_ENUM_PIN,
    MN_PH_SIM_TIMER_ENUM_BUTT
} ;
typedef VOS_UINT8 MN_PH_SIM_TIMER_ENUM_U8;

/*���Ӷ�SPN�ļ����ĺ�*/
#define TAF_USIM_SPN_EFID  0x6f46  /*USIM EFspn��ID*/
#define TAF_SIM_SPN_EFID   0x9f46  /*SIM  EFspn��ID*/
#define TAF_CPHS_SIM_ONS_EFID   0x6F14  /*CPHS SIM OPER NAME STRING��ID*/

/* 6F15�ļ�ID */
#define TAF_MMA_CUSTOMER_SERVICE_PROFILE_FILE_ID            (0x6F15)

/* 4F36�ļ�ID */
#define TAF_MMA_RAT_MODE_FILE_ID                            (0x4F36)

/* 6F15�ļ�Refresh�����Զ������������Գ��Զ�ʱ��ʱ�� */
#define TI_TAF_MMA_PERIOD_TRYING_NETWORK_SELECTION_MENU_LEN (5*1000)

/* 4F36�ļ����� */
#define TAF_MMA_RAT_MODE_FILE_LEN                           (1)



#define MMA_INTERNAL_OP_NONE            0x0
#if 0
#define MMA_INTERNAL_OP_CLASS_CHANGE    0x01
#endif


/* <==A32D12535 */
#define MMA_INTERNAL_SET_BAND_REQ       0x03

#define MMA_WAIT_PHY_READ_MAX_TIMES     0x01
#define MMA_SET_PREF_PLMN_REQ           0x06
#define MMA_WAIT_SET_PREF_PLMN_CNF_MAX_TIMES 0x14
#define MMA_GET_USIM_ICC_ID              0x07
#define MMA_WAIT_GET_USIM_ICC_ID_MAX_TIMES 0x10
#define MMA_WAIT_GET_USIM_FILE_MAX_TIMES 0x5

#define MMA_GET_USIM_MNC_LENGTH_OP       0x0B

#define MMA_TIMER_FOR_PC_REPLAY_VAL      (60*1000)

#define TI_MN_PH_RESET_LENGTH            (50)




#define TI_TAF_MMA_PNN_LIST_MEM_PROTECT_TIMER_LEN     (15 * 1000)

#define TI_TAF_MMA_DELAY_POWER_DOWN_TIMER_LEN               (50)



#define TI_MN_PH_PIN_OPER_LENGTH         (1000)

#define MN_MMA_MNC_LENGTH_INDICATOR_POSITION               (4)                  /* ָʾMNC���ȵ��ֽ���EF�ļ��е�λ�� */
#define MN_MMA_MNC_LENGTH_TWO_BYTES_IN_IMSI                (2)                  /* MNC��IMSI�еĳ�����2 */
#define MN_MMA_MNC_LENGTH_THREE_BYTES_IN_IMSI              (3)                  /* MNC��IMSI�еĳ�����3 */

#define MN_MMA_OCTET_LOW_FOUR_BITS                         (0x0f)               /* ��ȡһ���ֽ��еĵ�4λ */

typedef struct MMA_INTERNAL_TIMER
{
    MMA_TIMER_ST  stTimer;
    VOS_UINT32    ulTimes;
    VOS_UINT32    ulOpType;
    VOS_UINT16 ClientId;
    VOS_UINT8        OpId;
}MMA_INTERNAL_TIMER_ST;
/* END:   Added by liuyang id:48197, 2006/3/2 */

/*TI��¼��*/
typedef struct
{
    VOS_UINT16             ClientId;
    VOS_UINT8                    Id;               /*CallId, Smi, OpId*/
    VOS_UINT8                 ucUsed;
    TAF_PHONE_EVENT           PhoneEvent;       /*��¼��ǰ�¼�*/
}MMA_TI_TABLE;

/*������ʱ��ʹ�õ����ݽṹ*/
#define MMA_START_INITIAL_TIMER_ID  0x88
typedef struct
{
    MMA_TIMER_ST SetupTimer;
    VOS_UINT8    ucTimes;
}MMA_START_INITIAL_TIMER_ST;






/* BEGIN: Added by liuyang id: 48197, 2006/3/20   PN:A32D02500*/
/*������־�����ṹ���壬0��δ������1��������*/
typedef enum
{
    MMA_PS_LOCAL_NOT_START,
    MMA_PS_LOCAL_STARTED,
    MMA_START_FLG_BUTT
}MMA_START_FLG_LOCAOL_ENUM;

typedef enum
{
    MMA_PHONE_NOT_READY,
    MMA_PHONE_READY
}MMA_PHONE_READY_ENUM;

/*�ڲ��������̵Ĵ�������,
MMA_PS_NORMAL_START: �û�����Taf_PhoneStart��������
MMA_PS_TAF_INIT_START:taf_Initʱ�򣬼��usim״̬������PINδʹ�ܴ����ڲ�����
MMA_PS_PIN_OP_START:����������PINʹ�ܣ��û���֤PIN ͨ�������ڲ����̡�
*/
typedef enum
{
    MMA_PS_NORMAL_START,
    MMA_PS_TAF_INIT_START,
    MMA_PS_PIN_OP_START,
    MMA_START_LOCAL_PROC_BUTT
}MMA_START_LOCAL_PROC_ENUM;

/*������־�ṹ��*/
typedef struct
{
    MMA_START_FLG_LOCAOL_ENUM MmaLocalStartFlg;
    MMA_START_LOCAL_PROC_ENUM MmaLocalStartProc;
}MMA_START_FLG_ST;

/* BEGIN: Added by liuyang id:48197, 2006/3/21   PN:A32D02602*/
typedef struct
{
    TAF_PH_PIN_CNF_STRU   stPinDataCnf;
    VOS_UINT8             ucPinDataFlg;
}MMA_PIN_DATA_REPORT_STRU;
/* END:   Added by liuyang id:48197, 2006/3/21 */
/* END:   Added by liuyang id: 48197, 2006/3/20 */

#define MMA_USIM_UPLMN_FILE_INDEX   0x6F60
#define MMA_SIM_PLMN_SEL_FILE_ID    0x6F30
#define MMA_USIM_ICC_ID_INDEX       0x2fe2
#define MMA_USIM_PNN_FILE_INDEX     0x6FC5
#define MMA_USIM_OPL_FILE_INDEX     0x6FC6
#define MMA_USIM_ICC_ID_LENGTH      10
#define MMA_USIM_IMSI_FILE_ID       0x6f07
#define MMA_PS_FLASH_ADDR           0x400

#define MMA_MNC_LENGTH_FILE_ID     (0x6FAD)

#define MMA_USIM_SPDI_FILE_INDEX     0x6FCD


typedef VOS_UINT8  MMA_SIM_LOCK_STATUS;
#define MMA_SIM_IS_UNLOCK           0
#define MMA_SIM_IS_LOCK             1
#define MMA_SIM_LOCK_IS_VERIFY      2

typedef struct
{
    MMA_SIM_LOCK_STATUS                 SimLockStatus;
    TAF_OPERATOR_LOCK_INFO_STRU         stCardLockInfo;
}MMA_ME_PERSONALISATION_STATUS_STRU;

#define EVT_NAS_MMA_OUTSIDE_RUNNING_CONTEXT_FOR_PC_REPLAY   0xaaaa          /* ΪPC���̻طŶ������Ϣ */
#define MMA_MAX_TI                      (TAF_MAX_STATUS_TI + 2)

#define ID_NAS_MMA_MNTN_GET_USIM_STATUS   0xbbbb                                /* USIM��״̬��ά�ɲ⹴�� */







typedef struct
{
    VOS_UINT16    Mcc;
    VOS_UINT16    Mnc;
}TAF_PH_OPERATOR_PLMN_ID_STRU;


typedef struct
{
    TAF_PH_OPERATOR_PLMN_ID_STRU        PlmnId;
    TAF_UINT8                           ucMncLength;
    TAF_UINT8                           aucReserved1[3];
    TAF_CHAR*                           pStrOperatorNameShort ;
    TAF_CHAR*                           pStrOperatorNameLong;
}TAF_PH_OPERATOR_NAME_TBL_STRU;

typedef struct
{
    TAF_PLMN_ID_STRU                        stPlmnId;
    VOS_UINT16                              PlmnRat;
    VOS_UINT16                              usIndex;
}MMA_MODIFY_PLMN_INFO_STRU;


typedef struct
{
    VOS_UINT32                          ulUsimHotInFlg;
    VOS_UINT32                          ulUsimHotOutFlg;
    VOS_UINT32                          ulUsimHotInCount;
    VOS_UINT32                          ulUsimHotOutCount;
    VOS_UINT8                           ucUsimStatusFromUsim;

    VOS_UINT8                           ucMeLockStatus;
    VOS_UINT8                           ucMmaGlobalUsimStatus;
    MMA_START_FLG_ST                    stMmaStartFlg;
}NAS_MMA_USIM_STATUS_INFO_STRT;


typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgID;
    NAS_MMA_USIM_STATUS_INFO_STRT       stStatusInfo;
}NAS_MMA_MNTN_GET_USIM_STATUS_STRU;


/*****************************************************************************
 Structure      : NAS_MMA_OUTSIDE_RUNNING_CONTEXT_ST
 Description    : PC�طŹ��̣��洢����MMA��ص�ȫ�ֱ���
 Message origin :
*****************************************************************************/

typedef struct
{
    VOS_CHAR                                acVersionBuffer[VER_MAX_LENGTH];
    VOS_UINT8                               aucReserve[2];

    VOS_UINT8                               ucSimType;
    VOS_UINT8                               pc_g_aucMmaImsi[9];
    VOS_UINT8                               pc_g_aucMmaImei[TAF_PH_IMEI_LEN-1];
    VOS_UINT8                               reserved[2];

    STATUS_CONTEXT_STRU                     pc_g_StatusContext;
    TAF_MMA_GLOBAL_VALUE_ST                 pc_gstMmaValue;

    MMA_ME_PERSONALISATION_STATUS_STRU      pc_g_stMmaMePersonalisationStatus;
    MMA_TI_TABLE                            pc_gastMmaTiTab[MMA_MAX_TI];

    MMA_INTERNAL_TIMER_ST                   pc_gstMmaInternalTimer;

    MMA_TIMER_ST                            pc_g_MmaSimTimer[TAF_SIM_TIMER_NUM];
} NAS_MMA_OUTSIDE_RUNNING_CONTEXT_ST;

/*****************************************************************************
 Structure      : NAS_MMA_OUTSIDE_RUNNING_CONTEXT_ST
 Description    : PC�طŹ��̣�����MMA��ص�ȫ�ֱ���ͨ��������Ϣ�ṹ����
 Message origin :
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                           usMsgID;
    VOS_UINT16                           usReserved;                            /* ��PACK(1)��PACK(4)�����ж���ı����ֽ� */
    NAS_MMA_OUTSIDE_RUNNING_CONTEXT_ST   stOutsideCtx;
}NAS_MMA_SDT_MSG_ST;

/* ������Ϣֻ��������ʱ��ȡNV�����USIM API��ȡ��ȫ�ֱ��������ڴӿ�����ʼ�Ļط� */
#define EVT_NAS_MMA_FIXED_PART_CONTEXT   0xaabb          /* PC�طŹ��̶̹�����������Ϣ */


/*****************************************************************************
 Structure      : NAS_MMA_FIXED_PART_CONTEXT_ST
 Description    : PC�طŹ��̣��洢����MMA��صĹ̶�����
 Message origin :
*****************************************************************************/

typedef struct
{
    VOS_UINT32                              ulVersion;                       /* increased when add new paras */

    /* ulVersion = 0 part */
    VOS_UINT8                               aucMmaImsi[9];
    VOS_UINT8                               aucSimType;
    VOS_UINT8                               aucReserved1[2];

    VOS_UINT32                              ulPrefBand;                      /* en_NV_Item_User_Set_Freqbands */
    TAF_MMA_UE_SUPPORT_FREQ_BAND_STRU       Band;                            /* en_NV_Item_Support_Freqbands */
    MMA_QUICK_START_STA_UINT32              ulQuickStartFlg;                 /* en_NV_Item_FollowOn_OpenSpeed_Flag */
    VOS_UINT16                              usRfAutoTestFlg;                 /* en_NV_Item_RF_Auto_Test_Flag */
    VOS_UINT8                               aucReserved5[2];
    MMA_EFUST_SERVICE_CFG_STRU              stEfustServiceCfg;               /* en_NV_Item_EFust_Service_Cfg */

    VOS_UINT8                               aucImeiBcd[TAF_PH_IMEI_LEN+1];   /* en_NV_Item_IMEI */
    VOS_UINT8                               aucReserved2[3];

    MN_MMA_CPAM_RAT_TYPE_ENUM_UINT8         enAccessMode;                      /* en_NV_Item_MMA_AccessMode */
    TAF_PH_PLMN_PRIO                        PlmnPrio;
    TAF_PH_MS_CLASS_TYPE                    MsClassType;                     /* en_NV_Item_MMA_MsClass */
    /* Modified by h00313353 for Iteration 13, 2015-4-15, begin */
    TAF_MMA_ROAM_MODE_ENUM_UINT8            enRoam;                          /* en_NV_Item_Roam_Capa */
    /* Modified by h00313353 for Iteration 13, 2015-4-15, end */
    TAF_PH_MEINFO_STRU                      stMeInfo;
    VOS_UINT8                               aucReserved3[2];

    TAF_CUSTOM_SIM_LOCK_PLMN_INFO_STRU      stSimLockPlmnInfo;               /* en_NV_Item_CustomizeSimLockPlmnInfo */
    TAF_CUSTOM_CARDLOCK_STATUS_STRU         stCardLockStatus;                /* en_NV_Item_CardlockStatus */
    TAF_CUSTOM_SIM_LOCK_MAX_TIMES_STRU      stSimLockMaxTimes;               /* en_NV_Item_CustomizeSimLockMaxTimes */

    VOS_UINT8                               aucPwd[TAF_PH_ME_PERSONALISATION_PWD_LEN_MAX +1];    /* en_NV_Item_Sim_Personalisation_Pwd */
    VOS_UINT16                              usSimMePersonalisationActFlag;   /* en_NV_Item_Me_Personalisation_Active_Flag */
    VOS_UINT8                               aucReserved4[1];

    TAF_UINT8                               aucSimPersonalisationStr[TAF_MAX_IMSI_LEN + 1];      /* en_NV_Item_Sim_Personalisation_Imsi_Str */

    /* ulVersion = 1 part */
    TAF_MMA_UE_BAND_CAPA_ST                 gstMmaBandCapa;
    VOS_UINT8                               ucRoamFeatureStatus;
} NAS_MMA_FIXED_PART_CONTEXT_ST;

/*****************************************************************************
 Structure      : NAS_MMA_NEW_ADD_GLABAL_VARIABLE_FOR_PC_REPLAY_ST
 Description    : PC�طŹ��̣�����ȫ�ֱ��������ȡ��NVֵ��
 Message origin :
*****************************************************************************/

typedef struct
{
    VOS_UINT8                               ucSimType;
    VOS_UINT8                               aucImeiBcd[TAF_PH_IMEI_LEN+1];   /* en_NV_Item_IMEI */
    VOS_UINT8                               aucReserved3[2];

    TAF_CUSTOM_SIM_LOCK_PLMN_INFO_STRU      stSimLockPlmnInfo;               /* en_NV_Item_CustomizeSimLockPlmnInfo */
    TAF_CUSTOM_CARDLOCK_STATUS_STRU         stCardLockStatus;                /* en_NV_Item_CardlockStatus */
    TAF_CUSTOM_SIM_LOCK_MAX_TIMES_STRU      stSimLockMaxTimes;               /* en_NV_Item_CustomizeSimLockMaxTimes */

    VOS_UINT8                               aucPwd[TAF_PH_ME_PERSONALISATION_PWD_LEN_MAX +1];    /* en_NV_Item_Sim_Personalisation_Pwd */
    VOS_UINT16                              usSimMePersonalisationActFlag;   /* en_NV_Item_Me_Personalisation_Active_Flag */
    VOS_UINT8                               aucReserved4[1];

    TAF_UINT8                               aucSimPersonalisationStr[TAF_MAX_IMSI_LEN + 1];      /* en_NV_Item_Sim_Personalisation_Imsi_Str */

} NAS_MMA_NEW_ADD_GLABAL_VARIABLE_FOR_PC_REPLAY_ST;

/*****************************************************************************
 Structure      : NAS_MMA_FIXED_CONTEXT_MSG_ST
 Description    : PC�طŹ��̣�����MMA��صĹ̶�ȫ�ֱ���ͨ��������Ϣ�ṹ����
 Message origin :
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                           usMsgID;
    VOS_UINT16                           usReserved;                            /* ��PACK(1)��PACK(4)�����ж���ı����ֽ� */
    NAS_MMA_FIXED_PART_CONTEXT_ST        stFixedOutsideCtx;
}NAS_MMA_FIXED_CONTEXT_MSG_ST;
typedef struct
{
    VOS_UINT8                           ucGprsCipherAlg;                        /* GPRS�����㷨 */
    VOS_UINT8                           ucGprsCipher;                           /* VOS_TRUE:��������,VOS_FALSE:���ܲ�������*/
    MMA_CIPHER_ALGOR_ENUM_UINT8         enCipherAlgorForCSDomain;               /* CS������㷨  0:uea0; 1:uea1; 2:uea2 */
    MMA_CIPHER_ALGOR_ENUM_UINT8         enCipherAlgorForPSDomain;               /* PS������㷨  0:uea0; 1:uea1; 2:uea2 */
}MMA_CIPHER_INFO_STRU;


typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* ��Ϣͷ */
    VOS_UINT32                          ulFileLen;                              /* �ļ����� */
    VOS_UINT8                           aucFileContent[4];                      /* �ļ����� */
}TAF_MMA_GET_CACHE_FILE_STRU;
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* ��Ϣͷ */
    VOS_UINT8                           ucDrxTimerStatus;                       /*  DRX��ʱ����״̬ */
    VOS_UINT8                           aucReserve[3];
}TAF_MMA_DRX_TIMER_STAUTS_STRU;


#define TAF_MMA_LOG_NV_READ_WRITE_RSLT_MSG      0xdddd
#define TAF_MMA_MAX_NV_INFO_LEN                 0x20

typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;/* ��Ϣͷ */ /*_H2ASN_Skip*/
    VOS_UINT32                          ulNvId;
    VOS_UINT32                          ulRslt;/* VOS_TRUE:�ɹ� ;VOS_FALSE:ʧ�� */
    VOS_UINT8                           aucNvInfo[TAF_MMA_MAX_NV_INFO_LEN];/* NV���� */
}TAF_MMA_LOG_READ_WRITE_NV_INFO_STRU;

typedef enum
{
   MMA_GET_REC_I,
   MMA_GET_REC_II,
   MMA_GET_REC_END
}MMA_GET_REC_PHASE;

typedef VOS_UINT32 MMA_GET_REC_PHASE_U32;

typedef struct
{
    USIMM_CARDAPP_ENUM_UINT32           enAppType;
    MMA_GET_REC_PHASE_U32               enNextPhase;
}MMA_GET_REC_INFO_STRU;
enum TAF_MMA_PROC_NET_SCAN_PROTECT_TIMER_ENUM
{
   TAF_MMA_PROC_NET_SCAN_PROTECT_TIMER_START,
   TAF_MMA_PROC_NET_SCAN_PROTECT_TIMER_STOP,

   TAF_MMA_PROC_NET_SCAN_PROTECT_TIMER_BUTT
};
typedef VOS_UINT8 TAF_MMA_PROC_NET_SCAN_PROTECT_TIMER_ENUM_UINT8;


enum TAF_MMA_PROC_ABORT_NET_SCAN_PROTECT_TIMER_ENUM
{
   TAF_MMA_PROC_ABORT_NET_SCAN_PROTECT_TIMER_START,
   TAF_MMA_PROC_ABORT_NET_SCAN_PROTECT_TIMER_STOP,

   TAF_MMA_PROC_ABORT_NET_SCAN_PROTECT_TIMER_BUTT
};
typedef VOS_UINT8 TAF_MMA_PROC_ABORT_NET_SCAN_PROTECT_TIMER_ENUM_UINT8;



enum MMA_DEACT_SIM_WHEN_POWEROFF_ENUM
{
   MMA_DEACT_SIM_WHEN_POWEROFF_DISABLE,
   MMA_DEACT_SIM_WHEN_POWEROFF_ENABLE,

   MMA_DEACT_SIM_WHEN_POWEROFF_BUTT
};
typedef VOS_UINT8 MMA_DEACT_SIM_WHEN_POWEROFF_ENUM_UINT8;

/*****************************************************************************
  8 UNION����
*****************************************************************************/



/*****************************************************************************
  9 OTHERS����
*****************************************************************************/
/*��������*/
/* Deleted by y00322978 for CDMA 1X Iteration 11, 2015-4-11, begin */

/* Deleted by y00322978 for CDMA 1X Iteration 11, 2015-4-11, end */



VOS_VOID TAF_MMA_AtQryPnnListProc(VOS_VOID);


VOS_VOID TAF_MMA_RcvDelayPowerDownTimerExpired(VOS_VOID);


VOS_VOID TAF_MMA_SndAtSubPnnList(
    VOS_UINT32                   ulSndNum,
    TAF_SDC_PNN_FILE_INFO_STRU  *pstPnnFileInfo
);

VOS_VOID TAF_MMA_ClearcPnnListQryCtrInfo(VOS_VOID);

VOS_VOID TAF_MMA_UsimGetFileRspPnnMsgProc(
/* Modified by h00313353 for iteration 9, 2015-2-6, begin */
    USIMM_READFILE_CNF_STRU *pUsimTafMsg
/* Modified by h00313353 for iteration 9, 2015-2-6, end */
);



VOS_UINT32 TAF_MMA_GetPidFromClientId(
    MN_CLIENT_ID_T                      usClientId
);

VOS_VOID MMA_DefPhAccessMode(VOS_UINT16      ClientId,
                             VOS_UINT8             OpId,
                             MN_MMA_CPAM_RAT_TYPE_ENUM_UINT8    AccessMode,
                             TAF_PH_PLMN_PRIO PlmnPrio);
VOS_VOID MMA_DefPhClassType(VOS_UINT16           ClientId,
                            VOS_UINT8                  OpId,
                            TAF_PH_MS_CLASS_TYPE    MsClass);
VOS_VOID MMA_PhModeReport(
    VOS_UINT16                          ClientId,
    VOS_UINT8                           OpId,
    TAF_PH_OP_MODE_CNF_STRU             stPhMode,
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCode
);

NAS_STK_SERVICE_STATUS_ENUM_UINT8 NAS_MMA_ConvertSdcServStaToStkServSta(
    TAF_SDC_REPORT_SRVSTA_ENUM_UINT8    enSdcSrvSta
);


/* MMA_PhSysCfgHandle */


#if (FEATURE_ON == FEATURE_LTE)


/* move this function in SYS CFG state machine */

#endif



/* delete this function */

VOS_VOID TAF_MMA_ReportSysCfgSetCnf(
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCode
);

/* Deleted by y00322978 for CDMA 1X Iteration 11, 2015-4-1, begin */

/* Deleted by y00322978 for CDMA 1X Iteration 11, 2015-4-1, end */

/* Modified by y00322978 for CDMA 1X Iteration 11, 2015-3-26, begin */

VOS_VOID MN_MMA_GetSupportedUserLteBand(
    TAF_USER_SET_PREF_BAND64           *pstLBand
);
/* Modified by y00322978 for CDMA 1X Iteration 11, 2015-3-26, end */

/* move this function in sys cfg state machine */

VOS_VOID MMA_ChangeSrv2Class(
    TAF_MMA_SERVICE_DOMAIN_ENUM_UINT8  enSrvDomain,
    TAF_PH_MS_CLASS_TYPE    *pucMsClass
);
/* Modified by h00313353 for Iteration 13, 2015-4-9, begin */
VOS_VOID MMA_ChangeClass2Srv(TAF_MMA_SERVICE_DOMAIN_ENUM_UINT8 *pucSrvDomain,
/* Modified by h00313353 for Iteration 13, 2015-4-9, end */
                                     TAF_PH_MS_CLASS_TYPE    ucMsClass);
/* ɾ��MMA_FillWholeInfo() */
VOS_UINT32 MMA_GetIdByTi (VOS_UINT8         ucModule,
                          VOS_UINT8         ucTi,
                          VOS_UINT16    *pClientId,
                          VOS_UINT8           *pId,
                          TAF_PHONE_EVENT  *PhoneEvt);
VOS_VOID MMA_GetRssiLevelFromValue( VOS_INT32      lRssiValue, VOS_UINT8    *pucRssiLevel );
VOS_VOID MMA_HandleEventError(VOS_UINT16   ClientId,
                              VOS_UINT8          OpId,
                              VOS_UINT8       ucError,
                              TAF_PHONE_EVENT PhEvent);

VOS_VOID MMA_QryUsimInfo(
    VOS_UINT16        ClientId,
    VOS_UINT8         OpId,
    TAF_PH_QRY_USIM_INFO_STRU           *pstInfo
);

extern VOS_VOID Aps_PowerOff(VOS_VOID);
extern VOS_VOID NAS_RabmPowerOff(VOS_VOID);
extern VOS_VOID Sm_PowerOff(VOS_VOID);
extern VOS_VOID SSA_Init(VOS_VOID);
extern VOS_VOID  SSA_PowerOff(VOS_VOID);
extern VOS_VOID SMS_Poweroff(VOS_VOID);
extern VOS_VOID Cca_Poweroff(VOS_VOID);

extern VOS_UINT32 WAS_MNTN_QueryCSNR(VOS_INT16 *psCpichRscp,VOS_INT16 *psCpichEcNo);
extern VOS_VOID Aps_LoadDefault(VOS_VOID);
extern VOS_VOID Mma_LoadDefault(VOS_VOID);


extern VOS_VOID Tc_TaskInit(VOS_VOID);

extern  VOS_VOID    Ss_Init(VOS_VOID);

/* ɾ���˴��������� */
extern VOS_VOID MN_MSG_PowerOff(VOS_VOID);
extern VOS_VOID NAS_CC_PowerOff(VOS_VOID);
extern VOS_UINT32 sysIMEISet( VOS_UINT8 *pucStr,  VOS_UINT32 ulStrlen, VOS_UINT32 ulOffset);
VOS_VOID    MMA_InitCm(VOS_VOID);
VOS_VOID MMA_Init1(VOS_VOID);
VOS_VOID MMA_Init2(VOS_UINT8    ucUsimStatus);
VOS_VOID MMA_InitEventInfoOP(TAF_PHONE_EVENT_INFO_STRU *pstEvent);
VOS_VOID MMA_GetForbBandFromNV(VOS_VOID);

VOS_VOID MMA_GetUESupportBandFromNV(VOS_VOID);

extern VOS_VOID MMA_InitOrigMeInfo( VOS_VOID );


VOS_VOID  MMA_InitUsimInfo(TAF_USIM_INFO_STRU       *pstUsimInfo,
                           MMA_INIT_TYPE_ENUM      enInitType,
                           TAF_PH_USIM_SPN_CNF_STRU *pstSpnCnfTmp);

TAF_PH_ROAM_STA MMA_IsRoam(
    VOS_UINT8                           ucRoamFlg
);

VOS_VOID MMA_OpPinExpired(VOS_VOID);
VOS_VOID MMA_ParaQueryReport(VOS_UINT16            ClientId,
                              VOS_UINT8                   OpId,
                              TAF_PARA_TYPE      QueryType,
                              VOS_UINT16         usErrorCode,
                              VOS_VOID                 *pucPara);


VOS_UINT32 TAF_MMA_IsCGIInfoChanged(
    TAF_SDC_SYS_INFO_STRU              *pstOldSysInfo,
    TAF_SDC_SYS_INFO_STRU              *pstNewSysInfo
);

VOS_UINT32 TAF_MMA_Rcv3gppMsccSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_VOID TAF_MMA_ProcMsccSysInfoInNormalService(
    VOS_UINT32                          ulCellChangeFlg
);

VOS_UINT32 TAF_MMA_RcvMsccAcInfoChangeInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 MMA_DbProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);



/* Deleted by y00322978 for CDMA 1X Iteration 11, 2015-3-26, begin */

/* Deleted by y00322978 for CDMA 1X Iteration 11, 2015-3-26, end */



VOS_UINT32 MMA_PhoneGetAlphanumericNameByPlmnIdFromNV( TAF_PH_OPERATOR_NAME_STRU   *pstOperName);
VOS_UINT32 MMA_PhoneFindNtwkNameByPlmnId( TAF_PH_OPERATOR_NAME_STRU   *pstOperName);

VOS_VOID MMA_PhoneGetDomain(VOS_UINT16  ClientId,  VOS_UINT8  OpId);
VOS_VOID MMA_PhoneGetIdentificationInfo( VOS_UINT16 ClientId, VOS_UINT8    OpId );
VOS_VOID MMA_PhoneGetImsi(VOS_UINT16           ClientId,
                          VOS_UINT8                  OpId);
/* Deleted by k902809 for Iteration 11, 2015-3-27, begin */
/* Deleted by k902809 for Iteration 11, 2015-3-27, end */
VOS_UINT32 MMA_PhoneGetOperNameInfoByLongOperatorName( TAF_PH_OPERATOR_NAME_STRU   *pstOperName);
VOS_UINT32 MMA_PhoneGetOperInfoByLongNameFromOperTbl( TAF_PH_OPERATOR_NAME_STRU   *pstOperName);
VOS_UINT32 MMA_PhoneGetOperInfoByShortNameFromOperTbl( TAF_PH_OPERATOR_NAME_STRU   *pstOperName);
VOS_UINT32 MMA_PhoneGetOperNameInfoByShortOperatorName( TAF_PH_OPERATOR_NAME_STRU   *pstOperName);
VOS_VOID MMA_PhoneGetProductName( VOS_UINT16     ClientId, VOS_UINT8    OpId );
/* Deleted by k902809 for Iteration 11, 2015-3-28, begin */

/* Deleted by k902809 for Iteration 11, Iteration 11 2015-3-28, end */
VOS_VOID MMA_PhoneGetRoamSta(VOS_UINT16    ClientId,   VOS_UINT8 OpId);

/* Deleted by y00322978 for CDMA 1X Iteration 11, 2015-4-1, begin */
/* Deleted by y00322978 for CDMA 1X Iteration 11, 2015-4-1, end */

VOS_VOID  MMA_PhonePlmnList (VOS_VOID);
VOS_VOID MMA_PhonePlmnUserSel (
    VOS_UINT16                              ClientId,
    VOS_UINT8                               OpId,
    TAF_PLMN_ID_STRU                        Plmn,
    /* Modified by h00313353 for Iteration 13, 2015-4-10, begin */
    TAF_MMA_RAT_TYPE_ENUM_UINT8             enPhRat,
    /* Modified by h00313353 for Iteration 13, 2015-4-10, end */
    TAF_PLMN_RESEL_MODE_TYPE                ReselMode);

/* MMA_PhoneRssiInd�Ƶ�Ԥ�������� */
VOS_VOID MMA_DbQuery(VOS_UINT16             ClientId,
                     VOS_UINT8                    OpId,
                     TAF_PARA_TYPE       ParaType);


VOS_UINT32 MMA_PhoneUsimReady( VOS_UINT16           ClientId,
                               VOS_UINT8                  OpId,
                               TAF_PARA_TYPE     QueryType );
VOS_VOID MMA_PinDataReport( const TAF_PH_PIN_CNF_STRU *pstPinCnf);
VOS_VOID MMA_PinHandle (VOS_UINT16 ClientId, VOS_UINT8 OpId,
                        TAF_PH_PIN_DATA_STRU stPinData);


VOS_VOID MMA_QueryProc(VOS_UINT16 ClientId,
                       VOS_UINT8        OpId,
                       VOS_UINT8    *pMsg);
VOS_VOID MMA_GetUESupportCPHSFlgFromNV(VOS_VOID);



/* Deleted by c00318887 for AT&T phaseII, 2015-2-16, begin */
/* Deleted by c00318887 for AT&T phaseII, 2015-2-16, end */
VOS_BOOL MMA_IsNeedToDisplayCPHSOperNameStr(VOS_VOID);
VOS_VOID MMA_ReportPNNParaFromCPHSOperNameStr(
    VOS_UINT16                          ClientId,
    VOS_UINT8                           OpId
);

VOS_VOID   MMA_ReportOPLParaForCPHSDisplay(
    VOS_UINT16                          ClientId,
    VOS_UINT8                           OpId
);

VOS_VOID MMA_ReportParaQueryError( VOS_UINT16       ClientId,
                                   VOS_UINT8              OpId,
                                   VOS_UINT16           usErrorCode,
                                   TAF_PARA_TYPE ParaType);
VOS_UINT32  MMA_TiAlloc(VOS_UINT8        ucModule,
                        VOS_UINT16    ClientId,
                        VOS_UINT8           Id,
                        TAF_PHONE_EVENT  PhoneEvt,
                        VOS_UINT8       *pucTi);
VOS_VOID MMA_UpdateMsClassTypeGolbalValue(TAF_PH_MS_CLASS_TYPE MsClass);
VOS_VOID TAF_MMA_GetRegStateInfo( TAF_PH_REG_STATE_STRU *pstCurRegInf );
VOS_UINT32 MMA_WriteValue2Nvim(const NV_ID_ENUM_U16 enNVItemType,
                               VOS_VOID *pData, VOS_UINT16 usDataLen);

VOS_VOID TafPhoneGetNetworkNameForListPlmn(TAF_PH_OPERATOR_NAME_FORMAT_OP_STRU *pstOperName);
VOS_UINT32 Taf_PhoneGetOperNameInfo( TAF_PH_OPERATOR_NAME_FORMAT_OP_STRU *pstOperName );
VOS_VOID  Taf_PhoneEvent (TAF_PHONE_EVENT_INFO_STRU  *pEvent);

VOS_VOID MMA_CleanTiVar(VOS_UINT16 ClientId, VOS_UINT8 OpId);
VOS_VOID MMA_ImsiBcd2Ascii(VOS_UINT8 ucLen, VOS_UINT8 *pucNum, VOS_UINT8 *pucAsciiStr);
VOS_VOID MMA_ImeiBcd2Ascii(VOS_UINT8 ucLen, VOS_UINT8 *pucNum, VOS_UINT8 *pucAsciiStr);

VOS_VOID MMA_InitAtMsgReq( VOS_UINT16   ClientId,
                             VOS_UINT8          OpId,
                             TAF_START_INFO_IND_STRU   stAtMsgReq);
VOS_VOID MMA_PhoneEventBroadcast(TAF_PHONE_EVENT_INFO_STRU  *pEvent);
VOS_UINT32 MMA_StartInitialTimer(VOS_VOID);

VOS_VOID MMA_PlmnId2Bcd(TAF_PLMN_ID_STRU *pstPlmnId);
VOS_VOID MMA_PlmnId2NasStyle(TAF_PLMN_ID_STRU *pstPlmnId);

VOS_UINT32 MMA_CheckPin1Satus(VOS_VOID);
VOS_VOID MMA_UsimMsgProc(struct MsgCB *pMsg);
VOS_UINT32 TAF_MMA_IsCardStatusChanged(
    USIMM_CARDSTATUS_IND_STRU          *pstUsimMsg
);

/* Modified by h00313353 for iteration 9, 2015-2-6, begin */
VOS_UINT32 TAF_MMA_IsImsiChanged(
    /* Modified by h00313353 for iteration 9, 2015-2-6, begin */
    USIMM_CARD_STATUS_STRU            *pstUsimMsg,
    VOS_UINT8                         *pstImsi
    /* Modified by h00313353 for iteration 9, 2015-2-6, end */
);


/* Modified by h00313353 for iteration 9, 2015-2-6, end */



/* MMA_UsimChangeProc�ƶ�λ�� */
VOS_UINT32 MMA_PhoneGetUsimStatus( VOS_UINT8 *pucSimStatus );
VOS_UINT32 MMA_CheckPuk1Satus(VOS_VOID);
/* MMA_ResetMsClassFromNvim����ɾ�� */
VOS_UINT32 MMA_CheckPin1SatusSimple(VOS_VOID);
VOS_UINT32 MMA_StartInternalTimer(VOS_UINT32    ulTimes,
                                  VOS_UINT32    ulOpType,
                                  VOS_UINT16 ClientId,
                                  VOS_UINT8        OpId);
VOS_VOID MMA_ExpiredInternalTimer(VOS_VOID);
VOS_UINT32 Mma_CheckPin(TAF_PH_PIN_DATA_STRU stPinData);
VOS_UINT32 Mma_CheckPinTypes(TAF_PH_PIN_TYPE PinTypes);
VOS_UINT32 Mma_CheckPinCmdType(TAF_PH_PIN_CMD_TYPE PinCmdType);
VOS_UINT32 Mma_CheckPinLength(VOS_UINT8 *pucPin);
VOS_UINT32 Mma_CheckPinAvail(VOS_UINT8 *pucPin);
VOS_UINT32 Mma_CheckPinValue(VOS_UINT8 *pucPin);
VOS_VOID MMA_InitTi(VOS_VOID);


VOS_UINT32 MMA_OpPin1Success(const TAF_PH_PIN_CNF_STRU *pstPinCnf);
VOS_UINT32 MMA_Pin1Noneed(VOS_VOID);
VOS_UINT32 MMA_CheckUsimStatus(VOS_VOID);
TAF_PH_MS_CLASS_TYPE MMA_GetCurMsClass(VOS_VOID);
VOS_VOID MMA_ClearCurRegOp(TAF_PH_REG_STATE_STRU  *pstCurRegSta);
VOS_UINT32 MMA_GsmSetFreq(VOS_UINT32 ulGsmFreq);
VOS_UINT32 MMA_PhoneGetUsimType( VOS_UINT8 *pucSimType );
VOS_UINT32 MMA_WcdmaSetFreq(VOS_UINT32 ulDlFreqHighFreq,
                           VOS_UINT32 ulDlFreqLowFreq);
VOS_UINT32 MMA_SetFreq(VOS_UINT32 ulDlFreqHighFreq,
                       VOS_UINT32 ulDlFreqLowFreq,
                       VOS_UINT8  ucRadioAccessMode);
VOS_VOID MMA_StopInternalTimer(VOS_VOID);
VOS_VOID MMA_ResetInternalTimerFlg(VOS_VOID);
VOS_VOID MMA_TurnOnForFlightMode(VOS_VOID);
VOS_VOID MMA_TurnOffForFlightMode(VOS_VOID);


VOS_UINT32 MMA_ChangeBandType4Gsm( GSMBANDTYPE Band );
VOS_UINT32 MMA_ChangeBand4Wcdma( VOS_UINT32                     *pulBand,
                                 NVIM_UE_SUPPORT_FREQ_BAND_STRU *pstBandSet );
VOS_VOID MMA_PhoneGetFreq(VOS_UINT16 ClientId, VOS_UINT8 OpId);

VOS_BOOL MN_PH_IsUsingPlmnSel(VOS_VOID);
VOS_UINT16 MN_PH_GetUpdateFileForPrefPlmn(
    MN_PH_PREF_PLMN_TYPE_ENUM_U8        enPrefPLMNType
);


/* Delete MMA_UpdateUsimPrePlmn */

VOS_UINT32 MMA_CheckSetUplmn();
VOS_VOID MMA_DefPhImei(TAF_UINT16 usClientId, TAF_UINT8 OpId, TAF_PH_IMEI_STRU* pstImei);
/* ɾ��MMA_OmMsg ��MMA_UsimMsg���� */
VOS_VOID  MMA_PhoneGetIccId(VOS_UINT16           ClientId,
                            VOS_UINT8            OpId);

MMA_GET_ICC_ID_ST *TAF_MMA_GetIccIdInfo(VOS_VOID);
TAF_MMA_GET_HPLMN_STRU *TAF_MMA_GetHplmnInfo(VOS_VOID);


VOS_VOID MMA_GetUsimIccIdExpired(VOS_VOID);

VOS_UINT32 MMA_UsimRestrictedAccessCnfMsgProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);



VOS_UINT32 MMA_UsimRestrictedAccessCommandProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 MMA_PhoneProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 MMA_SetCPin(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 MMA_TimeExpired(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT8 MMA_GetUsimStatus(
    VOS_UINT32                          ulUsimStaChg
);


VOS_VOID MMA_GetPhIccType(VOS_UINT16 ClientId, VOS_UINT8 OpId);
VOS_VOID MMA_GetPhIccStatus(VOS_UINT16 ClientId, VOS_UINT8 OpId);
/* VOS_VOID MMA_IccStatusInd(VOS_VOID );
VOS_UINT8 MMA_GetUsimStatus(VOS_VOID); */

VOS_UINT32 MMA_LoadDefaultVaule(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_VOID TAF_MMA_SndAtIccStatusInd(
    VOS_UINT8                           ucSimStatus,
    VOS_UINT8                           ucSimLockStatus
);

VOS_UINT8 MMA_GetMeLockStatus(VOS_VOID);
VOS_VOID MMA_CPnnQuery(VOS_UINT16 ClientId, VOS_UINT8 OpId,TAF_PH_ICC_TYPE  *pIccType);
VOS_VOID MMA_CPnnReport(
    TAF_PH_ICC_TYPE                     ucIccType,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
);
VOS_BOOL MMA_IsSimLockPlmnInfoValid(VOS_VOID);
VOS_UINT32 MMA_GetCardLockInfo(TAF_OPERATOR_LOCK_INFO_STRU *pstOperatorLockInfo);
VOS_VOID MMA_MePersonalisationHandle(VOS_UINT16 ClientId,
                                     VOS_UINT8 OpId,
                                     TAF_ME_PERSONALISATION_DATA_STRU stMePersonalData);
VOS_VOID MMA_MePersonlisationQuery(VOS_UINT16   ClientId,
                                  VOS_UINT8    OpId,
                                  TAF_ME_PERSONALISATION_DATA_STRU stMePersonalData);
VOS_VOID MMA_MePersonlisationRetrieve(VOS_UINT16   ClientId,
                                     VOS_UINT8    OpId,
                                     TAF_ME_PERSONALISATION_DATA_STRU stMePersonalData);
VOS_VOID MMA_MePersonlisationDeactive(VOS_UINT16   ClientId,
                                     VOS_UINT8    OpId,
                                     TAF_ME_PERSONALISATION_DATA_STRU stMePersonalData);
VOS_VOID MMA_MePersonlisationActive(VOS_UINT16   ClientId,
                                   VOS_UINT8    OpId,
                                   TAF_ME_PERSONALISATION_DATA_STRU stMePersonalData);
VOS_VOID MMA_MePersonlisationPwdChange(VOS_UINT16   ClientId,
                                      VOS_UINT8    OpId,
                                      TAF_ME_PERSONALISATION_DATA_STRU stMePersonalData);
VOS_VOID TAF_UsimmStatusCardUnlocked(VOS_VOID);
VOS_VOID MMA_MePersonlisationVerify(VOS_UINT16   ClientId,
                                   VOS_UINT8    OpId,
                                   TAF_ME_PERSONALISATION_DATA_STRU stMePersonalData);
VOS_UINT32   MMA_OperatorPersonlisationVerify(
                                   TAF_ME_PERSONALISATION_DATA_STRU stMePersonalData);
VOS_UINT32 MMA_VerifyOperatorLockPwd(VOS_UINT8 *pucPwd);
VOS_VOID MMA_MePersonlisationSet(VOS_UINT16 ClientId,
                                VOS_UINT8 OpId,
                                TAF_ME_PERSONALISATION_DATA_STRU stMePersonalData);
VOS_UINT32 MMA_CheckMePersonalisationPwd(TAF_ME_PERSONALISATION_DATA_STRU stMePersonalData);
VOS_VOID MMA_MePersonalCnfReport(VOS_UINT16                        ClientId,
                                VOS_UINT8                         OpId,
                                TAF_PH_ME_PERSONLISATION_CNF_STRU stMePersonalCnf);
VOS_UINT32 MMA_CheckMePersonalisationStatus(VOS_VOID);


/* Deleted by k902809 for Iteration 11, 2015-3-27, begin */

/* Deleted by k902809 for Iteration 11, Iteration 11 2015-3-27, end */
VOS_VOID MMA_HomePlmnProc(VOS_UINT16 ClientId, VOS_UINT8 OpId);


/* Deleted by h00313353 for iteration 9, 2015-2-7, begin */

/* Deleted by h00313353 for iteration 9, 2015-2-7, end */

extern TAF_UINT32 Mm_AtTest(VOS_VOID *pInput, VOS_VOID *pRslt);





VOS_UINT32 TAF_MMA_ConvertDetachTypeToMscc(
    TAF_MMA_DETACH_TYPE_ENUM_UINT8           enDetachType,
    NAS_MSCC_PIF_DETACH_TYPE_ENUM_UINT32    *pulMsccDetachType
);

VOS_UINT32 TAF_MMA_ConvertAttachTypeToMscc(
    TAF_MMA_ATTACH_TYPE_ENUM_UINT8                          enMmaAttachType,
    NAS_MSCC_PIF_ATTACH_TYPE_ENUM_UINT32    *pulMsccAttachType
);


VOS_VOID TAF_MMA_ConvertPlmnPriorityClass(
    NAS_MSCC_PIF_PLMN_PRIORITY_CLASS_ENUM_UINT8                  enPrioClass,
    TAF_MMA_PLMN_PRIORITY_CLASS_ENUM_UINT8                 *penDestPrioClass
);
VOS_UINT32 TAF_MMA_ConvertCardType(
    USIMM_CARD_TYPE_ENUM_UINT32                             enCardType,
    TAF_MMA_USIMM_CARD_TYPE_ENUM_UINT32                    *penDestCardType
);
VOS_UINT32 TAF_MMA_ConvertCardStatus(
    USIMM_CARD_SERVIC_ENUM_UINT32       enCardStatus,
    TAF_MMA_CARD_STATUS_ENUM_UINT8     *penDestCardStatus
);

VOS_UINT32 TAF_MMA_ConvertServiceStatus(
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8                       enServiceStatus,
    TAF_PHONE_SERVICE_STATUS                               *penDestServiceStatus
);

VOS_UINT32 MMA_SndMsccDetachAttachReq(VOS_UINT32 ulMsgName,VOS_UINT32 ulDetachAttachType);


VOS_VOID MMA_SwitchUserSetBand2UESupportBand
( TAF_MMA_USER_BAND_SET_UN              uUserSetBand,
  TAF_MMA_UE_SUPPORT_FREQ_BAND_STRU    *pstUeBand
);

VOS_VOID MMA_SwitchUESupportBand2UserSetBand
(
    TAF_MMA_UE_SUPPORT_FREQ_BAND_STRU   stUeBand,
    TAF_MMA_USER_BAND_SET_UN           *puUserSetBand
);

#if (FEATURE_ON == FEATURE_LTE)
VOS_VOID TAF_MMA_UpdateLteBandToNvim(
    TAF_USER_SET_PREF_BAND64           *pstCurrLteBand,
    TAF_USER_SET_PREF_BAND64           *pstLastLteBand
);
#endif

/* MMA_TafMsgProc ����ɾ�� */

VOS_UINT32 MMA_GetUsimStatusFromUsim(VOS_UINT8 *pucCardStatus, VOS_UINT8 *pucCardType);
VOS_UINT8 MMA_CheckUsimStatusForPlmnSel(VOS_VOID);
VOS_UINT32 MMA_IsGsmForbidden(VOS_VOID );
VOS_VOID NAS_MMA_SndOutsideContextData(VOS_VOID);
VOS_VOID NAS_MMA_SndOutsideFixedContextData(VOS_VOID);
VOS_UINT8 MMA_GetCurrentPhoneMode(VOS_VOID);
VOS_VOID MMA_ClearEplmnFromNV(VOS_VOID);

#if (VOS_WIN32 == VOS_OS_VER)
VOS_VOID   NAS_MMA_SndNVData(VOS_VOID);
VOS_UINT32 NAS_MMA_SndNVFileData(const VOS_CHAR * aucNVFolder ,const VOS_CHAR * aucFileName);
#endif

VOS_VOID MN_PH_ResetTimerOutProc( VOS_VOID  );

VOS_VOID MN_PH_PinOperTimerOutProc( VOS_VOID );

VOS_VOID NAS_MMA_TransferSysSubMode2ActForAtCmdCreg(
    VOS_UINT8                           ucSysSubMode,
    TAF_PH_ACCESS_TECH_ENUM_UINT8       *pucAct
);
extern VOS_VOID NAS_MMA_ReportLociStatus(VOS_VOID);

extern VOS_VOID NAS_MMA_SndStkLociStatusEvent(VOS_VOID);
VOS_VOID TAF_MMA_SndStkLocationInfoInd (VOS_VOID);


extern VOS_BOOL NAS_MMA_CellIdChangeForStkLocSta(VOS_VOID);


VOS_VOID MN_PH_SimLockedRpt( VOS_VOID  );
VOS_VOID MN_PH_RoamingRpt( VOS_UINT8 ucTmpRoamStatus );
VOS_VOID MN_PH_AppRoamStatusRpt( VOS_VOID );



MN_MMA_CPAM_RAT_TYPE_ENUM_UINT8 MN_MMA_CovertPlmnRatFromSimToUserFormat(VOS_UINT16 usSimPlmnRat);
VOS_UINT16 MN_MMA_CovertPlmnRatFromUserToSimFormat(MN_MMA_CPAM_RAT_TYPE_ENUM_UINT8 ucPlmnRat);


VOS_UINT8 NAS_MMA_GetPhoneMode(VOS_VOID);

VOS_VOID MN_MMA_ConvertGUFrequencyBand(
    VOS_UINT32                         *pulPrefBand
);

VOS_UINT32 MN_MMA_IsGOnlyMode(
    TAF_MMA_RAT_ORDER_STRU             *pstRatOrder
);

VOS_UINT32 MN_MMA_IsWOnlyMode(
    TAF_MMA_RAT_ORDER_STRU             *pstRatOrder
);

VOS_UINT32 MN_MMA_IsGUDualMode(
    TAF_MMA_RAT_ORDER_STRU             *pstRatOrder
);


#if (FEATURE_ON == FEATURE_LTE)
VOS_UINT32 MN_MMA_IsLOnlyMode(
    TAF_MMA_RAT_ORDER_STRU             *pstRatOrder
);

#endif

VOS_VOID MN_MMA_ReadNvimRoamingBrokerInfo(VOS_VOID);
VOS_UINT8 MN_MMA_GetRoamingBrokerFlg(VOS_VOID);
VOS_VOID MN_MMA_GetCpamGURatPrio(
   MN_MMA_CPAM_RAT_PRIO_ENUM_UINT8     *pucPlmnPrio,
   TAF_MMA_RAT_ORDER_STRU              *pstAllRatOrder
);
VOS_VOID MN_MMA_GetCpamGUAccessRat(
   MN_MMA_CPAM_RAT_TYPE_ENUM_UINT8     *penAccessMode,
   TAF_MMA_RAT_ORDER_STRU              *pstAllRatOrder
);


/* Modified by h00313353 for Iteration 13, 2015-4-10, begin */
VOS_UINT32 MN_MMA_IsSpecRatSupported(
    TAF_MMA_RAT_TYPE_ENUM_UINT8         enSpecRat
);

TAF_MMA_RAT_TYPE_ENUM_UINT8 MN_MMA_GetUserPlmnSelPrioRat(
    TAF_MMA_RAT_TYPE_ENUM_UINT8         enPhRat,
    TAF_PLMN_ID_STRU                    stPlmn
);
/* Modified by h00313353 for Iteration 13, 2015-4-10, end */

/* Modified by h00313353 for Iteration 13, 2015-4-10, begin */
VOS_UINT32 MN_MMA_IsSpecRatInRatList(
    TAF_MMA_RAT_TYPE_ENUM_UINT8         enSpecRat,
    TAF_MMA_RAT_ORDER_STRU             *pstRatPrioList
);
/* Modified by h00313353 for Iteration 13, 2015-4-10, end */


VOS_UINT32 MMA_FormatPlmnStr2PlmnId(TAF_PLMN_ID_STRU *pPlmn,
                                                 VOS_UINT32        usFormat,
                                                 VOS_UINT16        usOprNameLen,
                                                 VOS_CHAR         *pucOprName);

/* Added by c00318887 for AT&T phaseII, 2015-3-13, begin */
VOS_VOID TAF_MMA_QryEonsUcs2(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
);
VOS_VOID TAF_MMA_ReportEonsUcs2Rsp(
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCode,
    TAF_MMA_EONS_UCS2_PLMN_NAME_STRU   *pstEonsUcs2PlmnName
);
 VOS_UINT8 TAF_MMA_TranslateOperatorName2UCS2(
    TAF_SDC_OPERATOR_NAME_STRU  *pstSrcNtwkName,
    VOS_CHAR                    *pucDstNtwkName,
    VOS_UINT8                    ucDstLen
);

/* Added by c00318887 for AT&T phaseII, 2015-3-13, end */

VOS_VOID Taf_InitEventInfoOP(TAF_PHONE_EVENT_INFO_STRU *pstEvent);
/* Deleted by c00318887 for AT&T phaseII, 2015-3-13, begin */
/* Deleted by c00318887 for AT&T phaseII, 2015-3-13, end */





VOS_UINT8 TAF_MMA_IsMncLenVaild(
    VOS_UINT8                           ucMncLen
);

VOS_VOID TAF_MMA_RcvSimLockQry(
    VOS_UINT16                          ClientId,
    VOS_UINT8                           OpId
);

VOS_UINT32 MN_PH_QryLocinfo (
    VOS_UINT32                         *pulMcc,
    VOS_UINT32                         *pulMnc,
    VOS_UINT16                         *pusLac,
    VOS_UINT8                          *pucRac,
    VOS_UINT32                         *pulCellId
);
/* VOS_VOID MMA_SaveWCipherInfo(
    MSCC_MMA_UMTS_CIPHER_INFO_IND_STRU  *pstCipherInfoInd
);
VOS_VOID MMA_SaveGCipherInfo(
    MSCC_MMA_GPRS_CIPHER_INFO_IND_STRU  *pstCipherInfoInd
); */



VOS_VOID MMA_QryCipherInfo(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
);



/* Modified by h00313353 for iteration 9, 2015-2-6, begin */
VOS_VOID TAF_MMA_GetUsimHplmnMncLenFileInd(USIMM_READFILE_CNF_STRU *pUsimTafMsg);
/* Modified by h00313353 for iteration 9, 2015-2-6, end */

VOS_UINT32 TAF_MMA_RcvOamConnectStatusInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_MMA_RcvOamTraceCfgReq(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 MMA_SaveWCipherInfo(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 MMA_SaveGCipherInfo(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);






VOS_UINT32  MN_MMA_IsUserSettedBandValid(
    TAF_MMA_SYS_CFG_PARA_STRU           *pstSysCfgPara
);


VOS_UINT32 NAS_MMA_MntnTraceGetUsimStatus(
    VOS_UINT8                           ucUsimStatus,
    VOS_UINT8                           ucMeLockStatus
);
/* VOS_VOID TAF_MMA_InitNetworkSelectionMenuCtx(VOS_VOID);
VOS_VOID TAF_MMA_InitRatBalancingCtx(VOS_VOID); */
VOS_VOID TAF_MMA_ReadAttEnsCustomNvim(VOS_VOID);
VOS_VOID TAF_MMA_SetNetworkSelectionMenuEnableFlg(VOS_UINT8 ucEnableFlg);
VOS_UINT8 TAF_MMA_GetNetworkSelectionMenuEnableFlg(VOS_VOID);


VOS_UINT32 TAF_MMA_RcvCustomerServiceProfileFile_PreProc(
    VOS_UINT16                          usEfLen,
    VOS_UINT8                          *pucEf
);
VOS_VOID TAF_MMA_ProcCustomerServiceProfileFile(VOS_VOID);


/* VOS_VOID TAF_MMA_ReadPlmnSelectionModeNvim(VOS_VOID); */
VOS_VOID TAF_MMA_SetPlmnSelectionMode(VOS_UINT8 ucPlmnSelMode);
VOS_UINT8 TAF_MMA_GetPlmnSelectionMode(VOS_VOID);
VOS_VOID TAF_MMA_SetAutoPlmnSelUser(TAF_MMA_AUTO_PLMN_SEL_USER_ENUM_UINT8 enAutoPlmnSelUser);
TAF_MMA_AUTO_PLMN_SEL_USER_ENUM_UINT8 TAF_MMA_GetAutoPlmnSelUser(VOS_VOID);
VOS_UINT8 TAF_MMA_GetTiTryingPeriodRatBalancingStatus(VOS_VOID);
VOS_VOID TAF_MMA_SetTiTryingPeriodRatBalancingStatus(VOS_UINT8 ucStatus);
VOS_VOID TAF_MMA_NetworkSelectionMenuCtrlTimerExpired(VOS_VOID);
VOS_VOID TAF_MMA_RatBalancingCtrlTimerExpired(VOS_VOID);
VOS_VOID TAF_MMA_SetPlmnMode_Refresh(TAF_MMA_PLMN_MODE_ENUM_UINT8 enPlmnMode);
TAF_MMA_PLMN_MODE_ENUM_UINT8 TAF_MMA_GetPlmnMode_Refresh(VOS_VOID);
VOS_VOID TAF_MMA_ReadRatBalancingNvim(VOS_VOID);
VOS_UINT32 TAF_MMA_RcvRatModeFileRefresh_PreProc(
    VOS_UINT16                          usEfLen,
    VOS_UINT8                          *pucEf
);
VOS_VOID TAF_MMA_RcvRatModeFileRefresh(
    VOS_UINT16                          usEfLen,
    VOS_UINT8                          *pucEf
);

VOS_UINT32 TAF_MMA_GetIccIdChangedFlg(
    VOS_UINT8                                ucIsCardRefresh,
    NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8      enCsimStatus
);
VOS_UINT8 TAF_MMA_GetTiTryingPeriodNetSelMenuStatus(VOS_VOID);
VOS_VOID TAF_MMA_SetTiTryingPeriodNetSelMenuStatus(VOS_UINT8 ucStatus);
VOS_VOID TAF_MMA_SetRatBalancingEnableFlg(VOS_UINT8 ucEnableFlg);
VOS_UINT8 TAF_MMA_GetRatBalancingEnableFlg(VOS_VOID);
VOS_VOID TAF_MMA_TransferRatMode(
    TAF_MMA_RAT_MODE_ENUM_U8            enRatMode,
    TAF_MMA_RAT_ORDER_STRU             *pstRatModeOrder
);
VOS_VOID TAF_MMA_ReadRatModeFile(VOS_VOID);
VOS_VOID TAF_MMA_ReadRatPrioListNvim(VOS_VOID);
VOS_VOID TAF_MMA_SetRatMode_Refresh(TAF_MMA_RAT_MODE_ENUM_U8 enRatMode);
TAF_MMA_RAT_MODE_ENUM_U8 TAF_MMA_GetRatMode_Refresh(VOS_VOID);
VOS_VOID TAF_MMA_ProcRatMode_EnableStatus(TAF_MMA_RAT_MODE_ENUM_U8 ucRatMode);
VOS_VOID TAF_MMA_ProcRatMode(TAF_MMA_RAT_MODE_ENUM_U8 enRatMode);
VOS_UINT32 TAF_MMA_CheckRatModePara(
    TAF_MMA_RAT_ORDER_STRU             *pstCurRatModeOrder
);
VOS_VOID  TAF_MMA_SndOmGetCacheFile(
    VOS_UINT32                          ulFileId,
    VOS_UINT32                          ulFileLen,
    VOS_UINT8                          *pucFileContent
);

VOS_VOID  TAF_MMA_SndOmLocationStatus(VOS_VOID);


VOS_VOID TAF_MMA_ReadNvimReportPlmnSupportFlg(VOS_VOID);
VOS_VOID TAF_MMA_PlmnIdReport(
    TAF_PLMN_ID_STRU                   *pstPlmn
);



VOS_VOID TAF_MMA_StopPlmnListTimer_UserAbort( VOS_VOID );

VOS_VOID  TAF_MMA_SndDrxTimerInfo( VOS_UINT8 ucDrxTimerStatus );



VOS_VOID TAF_MMA_ReadNvimRatPrioList(
    TAF_MMA_RAT_ORDER_STRU             *pstRatPrioList
);

VOS_VOID MN_MMA_SetDefaultRatPrioList(
    TAF_MMA_RAT_ORDER_STRU             *pstRatPrioList
);

VOS_UINT32 TAF_MMA_IsPlatformSupportSpecUserRat(
/* Modified by h00313353 for Iteration 13, 2015-4-10, begin */
    TAF_MMA_RAT_TYPE_ENUM_UINT8         enUserRat
/* Modified by h00313353 for Iteration 13, 2015-4-10, end */
);
/* Deleted by k902809 for Iteration 11, 2015-3-23, begin */

/* Deleted by k902809 for Iteration 11, Iteration 11 2015-3-23, end */

VOS_VOID TAF_MMA_SaveCellAcInfo(
    MSCC_MMA_AC_INFO_CHANGE_IND_STRU    *pstAcInfoInd
);
VOS_VOID TAF_MMA_InitCellAcInfo(VOS_VOID);

/* VOS_VOID TAF_MMA_RcvMsccAcInfoChangeInd(
    MSCC_MMA_AC_INFO_CHANGE_IND_STRU    *pstAcInfoChangeInd
); */


VOS_VOID TAF_MMA_DelPlatformUnsupportedRat(
    TAF_MMA_RAT_ORDER_STRU             *pstRatPrioList
);

/* Added by k902809 for Iteration 11, 2015-3-24, begin */
VOS_VOID TAF_MMA_FillCopnOperNameList(
    VOS_UINT32                          ulFromIndex,
    VOS_UINT16                          usPlmnNum,
    TAF_MMA_COPN_INFO_QRY_CNF_STRU     *pstCopnQryCnf
);
/* Added by k902809 for Iteration 11, Iteration 11 2015-3-24, end */
/* Deleted by k902809 for Iteration 11, 2015-3-30, begin */

/* Deleted by k902809 for Iteration 11, Iteration 11 2015-3-30, end */
VOS_UINT32 TAF_MMA_TranslateNtwkName2Str(
    TAF_SDC_OPERATOR_NAME_STRU      *pstIeNtwkName,
    VOS_CHAR                        *pucNtwkName,
    VOS_UINT32                       ulLen
);

VOS_UINT8 NAS_MMA_TranslateNtwkName2UCS2(
    VOS_UINT8                   *pucSrcNtwkName,
    VOS_CHAR                    *pucDstNtwkName,
    VOS_UINT8                    ucDstLen
);

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
VOS_VOID TAF_MMA_SndMtcSysInfo(
    VOS_UINT8                           ucIsFobbiddenPlmnFlag,
    VOS_UINT8                           ucPsSupportFlg
);

VOS_VOID TAF_MMA_ConvertRatModeToMtc(
    TAF_SDC_SYS_MODE_ENUM_UINT8         enSysMode,
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enUtranMode,
    MTC_RATMODE_ENUM_UINT8             *pucRatMode
);


VOS_VOID TAF_MMA_SndMtcEplmnInfoInd(
    MSCC_MMA_EPLMN_INFO_IND_STRU        *pstEplmnInfoIndMsg
);
#endif

/* Deleted by k902809 for Iteration 11, 2015-3-30, begin */

/* Deleted by k902809 for Iteration 11, Iteration 11 2015-3-30, end */



VOS_VOID TAF_MMA_InitRssiValue(VOS_VOID);


VOS_UINT32 TAF_MMA_IsModeChangeNeedRpt(VOS_VOID);
VOS_UINT32 TAF_MMA_IsServStatusChangeNeedRpt(VOS_VOID);
VOS_UINT32 TAF_MMA_IsRssiChangeNeedRpt(VOS_VOID);
VOS_UINT32 TAF_MMA_IsTimeChangeNeedRpt(VOS_VOID);
VOS_UINT32 TAF_MMA_IsSimStaChangeNeedRpt(VOS_VOID);
VOS_UINT32 TAF_MMA_IsRegStatusChangeNeedRpt(
    TAF_PH_REG_STATE_STRU                  *pstRegState
);

VOS_UINT32 TAF_MMA_IsPlmnSelectInfoNeedRpt(VOS_VOID);

VOS_UINT32 TAF_MMA_IsRegRejChangeNeedRpt(VOS_VOID);

VOS_VOID TAF_MMA_ReportSrvStatus(VOS_VOID);

NAS_MSCC_PIF_ALLOWED_REG_DOMAIN_ENUM_UINT8 TAF_MMA_GetRegDomain(VOS_VOID);
VOS_UINT32 TAF_MMA_IsEventNeedRpt(
    TAF_PHONE_EVENT_INFO_STRU          *pEvent
);


extern VOS_VOID TAF_MMA_DefaultAlphaToAscii(
    VOS_UINT8                          *pucDefAlpha,
    VOS_UINT8                           ucDefAlphaLen,
    VOS_UINT8                          *pucAsciiChar
);

/* Deleted by k902809 for Iteration 11, 2015-3-26, begin */

/* Deleted by k902809 for Iteration 11, Iteration 11 2015-3-26, end */


VOS_UINT32 MMA_ProcHotInOutUsimStatusInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 MMA_USIMMaxRecordNumCnfProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 MMA_UsimPINOperateMsgProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);



/* Deleted by c00318887 for AT&T phaseII, 2015-3-3, begin */
/* Deleted by c00318887 for AT&T phaseII, 2015-3-3, end */

/* Deleted by k902809 for Iteration 11, 2015-3-27, begin */

/* Deleted by k902809 for Iteration 11, Iteration 11 2015-3-27, end */
VOS_VOID MMA_WriteVersion(VOS_VOID);
VOS_VOID TAF_MMA_ReadSpnFile(VOS_VOID);

VOS_VOID  TAF_DRVAPI_PWRCTRL_SLEEPVOTE_UNLOCK(
    PWC_CLIENT_ID_E                     enPwcClientId
);

VOS_VOID  TAF_DRVAPI_PWRCTRL_SLEEPVOTE_LOCK(
    PWC_CLIENT_ID_E                     enPwcClientId
);

/* Deleted by k902809 for Iteration 11, 2015-3-24, begin */

/* Deleted by k902809 for Iteration 11, Iteration 11 2015-3-24, end */

VOS_VOID MN_MMA_Convert64BitBandTo32Bit(
    TAF_USER_SET_PREF_BAND64           *pstBand,
    VOS_UINT32                         *pulBand
);
VOS_UINT32 TAF_MMA_IsUsimStatusChange_UsimmCardServiceAbsent(
    TAF_SDC_USIM_STATUS_ENUM_UINT8      enPreSimStatus
);

VOS_UINT32 TAF_MMA_IsUsimStatusChange_UsimmCardServiceAvailable(
    TAF_SDC_USIM_STATUS_ENUM_UINT8      enPreSimStatus
);
VOS_UINT32 TAF_MMA_IsUsimStatusChange_UsimmCardServiceSimPin(
    TAF_SDC_USIM_STATUS_ENUM_UINT8      enPreSimStatus
);

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
VOS_VOID TAF_MMA_SndMtcRatModeInd(
    TAF_SDC_SYS_MODE_ENUM_UINT8         enSysMode,
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enUtranMode
);

VOS_VOID TAF_MMA_SndMtcPowerStateInd(MTC_MODEM_POWER_STATE_ENUM_UINT8 enPowerState);

VOS_VOID TAF_MMA_SndMtcCurrCampPlmnInfoInd(
    MMA_MTC_CURR_CAMP_PLMN_INFO_IND_STRU   *pstPlmnInfo
);
VOS_VOID TAF_MMA_SndMtcRegStatusInd(VOS_UINT8 ucIsUsimValidFlag);

VOS_VOID TAF_MMA_SndMtcImsaStateInd(MTC_MODEM_POWER_STATE_ENUM_UINT8 enPowerState);

#endif

/* Added by w00316404 for NEXT B26 Project, 2015-6-17, begin */
#if (FEATURE_ON == FEATURE_IMS)
VOS_VOID TAF_MMA_SndMtcImsVoiceCapInd(VOS_UINT8 ucAvail);
#endif
/* Added by w00316404 for NEXT B26 Project, 2015-6-17, end */


#if (VOS_WIN32 == VOS_OS_VER)
VOS_VOID TAF_MMA_SetSimLockStatus(VOS_UINT8 ucSimLockStatus);
#endif
VOS_UINT32 TAF_MMA_RcvMsccEOPlmnSetCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

/* Deleted by k902809 for Iteration 11, 2015-3-24, begin */

/* Deleted by k902809 for Iteration 11, Iteration 11 2015-3-24, end */
/* Deleted by k902809 for Iteration 11, 2015-3-30, begin */

/* Deleted by k902809 for Iteration 11, Iteration 11 2015-3-30, end */

VOS_UINT32 TAF_MMA_GetPnnNetWorkName(
    TAF_SDC_PLMN_ID_STRU                                   *pstPlmnId,
    TAF_MMA_MM_INFO_PLMN_NAME_STRU                         *pstPlmnName,
    TAF_SDC_NETWORK_NAME_CODE_SCHEME_ENUM_UINT8             enNetNameCodeScheme
);

VOS_UINT32 TAF_MMA_GetCphsNetWorkName(
    TAF_MMA_MM_INFO_PLMN_NAME_STRU                         *pstOperatorName,
    TAF_SDC_NETWORK_NAME_CODE_SCHEME_ENUM_UINT8             enNetNameCodeScheme
);
VOS_UINT32 TAF_MMA_GetMmInfoNetWorkName(
    TAF_SDC_PLMN_ID_STRU                                   *pstPlmnId,
    TAF_MMA_MM_INFO_PLMN_NAME_STRU                         *pstOperatorName,
    TAF_SDC_NETWORK_NAME_CODE_SCHEME_ENUM_UINT8             enNetNameCodeScheme
);
VOS_UINT32 TAF_MMA_GetSpnNetWorkName(
    TAF_SDC_PLMN_ID_STRU                                   *pstPlmnId,
    TAF_MMA_MM_INFO_PLMN_NAME_STRU                         *pstOperatorName,
    TAF_SDC_NETWORK_NAME_CODE_SCHEME_ENUM_UINT8             enNetNameCodeScheme
);
VOS_UINT32 TAF_MMA_GetNvimNetWorkName(
    TAF_PH_NETWORKNAME_STRU           *pstOperatorName
);
VOS_UINT32 TAF_MMA_GetStoredInternalNetWorkName(
    TAF_PH_NETWORKNAME_STRU            *pstOperatorName
);
VOS_VOID TAF_MMA_GetCopsNetWorkName(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
);
VOS_UINT32 TAF_MMA_Get7BitNetworkNameStr(
    TAF_SDC_OPERATOR_NAME_STRU         *pstNetworkLongName,
    TAF_SDC_OPERATOR_NAME_STRU         *pstNetworkShortName,
    TAF_MMA_MM_INFO_PLMN_NAME_STRU     *pstOperatorName
);
VOS_UINT32 TAF_MMA_GetUcs2NetworkName(
    TAF_SDC_OPERATOR_NAME_STRU                             *pstIeNtwkLongName,
    TAF_SDC_OPERATOR_NAME_STRU                             *pstIeNtwkShortName,
    TAF_SDC_NETWORK_NAME_CODE_SCHEME_ENUM_UINT8             enNetNameCodeScheme,
    TAF_MMA_MM_INFO_PLMN_NAME_STRU                         *pstOperatorName
);
VOS_UINT32 TAF_MMA_GetPlmnPnnIndexInOplFile(
    TAF_SDC_PLMN_ID_STRU               *pstPlmnId,
    TAF_SDC_OPL_FILE_INFO_STRU         *pstOplFileInfo
);



VOS_VOID TAF_MMA_UpdateSimRegStatus(VOS_VOID);

VOS_VOID TAF_MMA_NetScanTimerExpired(VOS_VOID);

VOS_VOID TAF_MMA_AbortNetScanTimerExpired(VOS_VOID);

/* Deleted by k902809 for Iteration 11, 2015-3-25, end */

/* Deleted by k902809 for Iteration 11, 2015-3-25, begin */

VOS_VOID TAF_MMA_StartNetScanProtectTimer(VOS_VOID);

VOS_VOID TAF_MMA_StopNetScanProtectTimer(VOS_VOID);

VOS_UINT32 TAF_MMA_StartAbortNetScanProtectTimer(VOS_VOID);

VOS_VOID TAF_MMA_StopAbortNetScanProtectTimer(VOS_VOID);

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
VOS_VOID TAF_MMA_SndMtcCurrCampPlmnInfoInd(
    MMA_MTC_CURR_CAMP_PLMN_INFO_IND_STRU   *pstPlmnInfo
);
#endif

VOS_VOID TAF_MMA_BuildMmaCtrlInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_MMA_CTRL_STRU                  *pstCtrlInfo
);

VOS_UINT32 TAF_MMA_IsPowerOnCLInterWork(VOS_VOID);

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
VOS_UINT32 MMA_MTC_ConvertCardStatus(
    USIMM_CARD_SERVIC_ENUM_UINT32           enCardStatus,
    TAF_MTC_USIMM_CARD_SERVIC_ENUM_UINT16  *penDestCardStatus
);
#endif

#if (FEATURE_LTE == FEATURE_ON)
VOS_VOID TAF_MMA_GetRssiLevelFromLteRssi(
    VOS_INT16                           usLteRssi,
    VOS_UINT8                          *pucRssiLevel
);
#endif

/* Add by l00305157 for Service_State_Optimize_PhaseII, 2015-02-11, begin */
VOS_UINT32 TAF_MMA_IsAppNetworkInfoCellChange(
    TAF_SDC_SERVICED_PLMN_INFO_STRU  *pstAppServPlmnInfo
);
/* Add by l00305157 for Service_State_Optimize_PhaseII, 2015-02-11, end */

#if (FEATURE_ON == FEATURE_BASTET)
VOS_VOID TAF_MMA_SndBastetRatModeInd(
    TAF_SDC_SYS_MODE_ENUM_UINT8  enSysMode,
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enUtranMode
);

VOS_VOID TAF_MMA_SndBastetCsServiceInd(PS_BOOL_ENUM_UINT8 bCSConnected);
VOS_VOID TAF_MMA_SndBastetServiceStatusInd(VOS_VOID);
#endif


/* Added by h00313353 for iteration 9, 2015-2-7, begin */
#if (FEATURE_UE_MODE_CDMA == FEATURE_ON)
VOS_VOID TAF_MMA_SaveCsimCardType(
    VOS_UINT32                          ulCardType
);
#endif

VOS_VOID TAF_MMA_SaveUsimCardType(
    VOS_UINT32                          ulCardType
);

/* Added by h00313353 for iteration 9, 2015-2-7, begin */
VOS_VOID TAF_MMA_SaveUsimCardStatus(
    USIMM_CARD_SERVIC_ENUM_UINT32       enUsimStatus
);

VOS_VOID TAF_MMA_SaveCsimCardStatus(
    USIMM_CARD_SERVIC_ENUM_UINT32       enCsimStatus
);
/* Added by h00313353 for iteration 9, 2015-2-7, end */

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_VOID TAF_MMA_ReportCSid(
    VOS_INT32                          ulSid
);


VOS_VOID TAF_MMA_QueryClSysInfo(
    TAF_PH_SYSINFO_STRU                *pstSysInfo
);

VOS_VOID TAF_MMA_ReprotCdmaServiceState(
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8   enCsServiceStatus,
    TAF_SDC_SYS_MODE_ENUM_UINT8         enSysMode
);
VOS_VOID TAF_MMA_UpdataHrpdServiceStatusAndDomain(
    TAF_SDC_SYS_MODE_ENUM_UINT8         enSysMode
);
VOS_VOID TAF_MMA_Updata1xServiceStatusAndDomain(
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8   enCsServiceStatus,
    TAF_SDC_SYS_MODE_ENUM_UINT8         enSysMode
);

VOS_VOID TAF_MMA_Report1xRegStatus(
    TAF_SDC_REG_STATUS_ENUM_UINT8       enRegState,
    TAF_SDC_SERVICE_DOMAIN_ENUM_UINT8   enCnDomainId
);

VOS_VOID TAF_MMA_Report1xCregStatus(
    TAF_SDC_REG_STATUS_ENUM_UINT8       enRegStatus
);


VOS_VOID TAF_MMA_ConvertSysSubModeToActForAtCmdCgreg(
    TAF_SDC_SYS_SUBMODE_ENUM_UINT8      enSysSubMode,
    TAF_PH_ACCESS_TECH_ENUM_UINT8      *pucAct
);
VOS_VOID TAF_MMA_ReportPsRegStatus(
    TAF_SDC_REG_STATUS_ENUM_UINT8       enRegState,
    TAF_SDC_SERVICE_DOMAIN_ENUM_UINT8   enDomainId
);
/* Added by y00322978 for CDMA Iteration 17, 2015-7-14, begin */
VOS_VOID TAF_MMA_Report1xEmcCallBack(
    VOS_UINT32                          ulIsInCallBack
);
/* Added by y00322978 for CDMA Iteration 17, 2015-7-14, end */
#endif

/* Added by y00307564 for CDMA Iteration 8 2015-2-7 begin */
VOS_UINT16 MMA_CheckCpolPara(
    TAF_PH_SET_PREFPLMN_STRU           *pstPrefPlmnParam,
    TAF_PH_PREF_PLMN_OPERATE_STRU      *pstPrefPlmnOpt);

MMC_MMA_PARA_TYPE_ENUM TAF_MMA_GetPrefPlmnParaType(
    MN_PH_PREF_PLMN_TYPE_ENUM_U8        enPrefPLMNType
);
/* Added by y00307564 for CDMA Iteration 8 2015-2-7 end */

VOS_VOID  MN_PH_GetSysInfoRoamStatus(
    TAF_PH_SYSINFO_STRU                 *pstSysInfo
);

VOS_VOID  MN_PH_GetSysInfoSrvStatus(
    TAF_PH_SYSINFO_STRU                 *pstSysInfo
);

VOS_VOID  MN_PH_GetSysInfoSysModeEx(
    TAF_PH_SYSINFO_STRU                 *pstSysInfo
);

VOS_VOID  MMA_GetSysInfoSysMode(
    TAF_PH_SYSINFO_STRU                 *pstSysInfo
);

VOS_UINT32 MN_PH_QryApHplmn(
    VOS_UINT32                          *pulMcc,
    VOS_UINT32                          *pulMnc
);

VOS_UINT32 MN_PH_QryAnQuery(
    VOS_INT16                           *psCpichRscp,
    VOS_INT16                           *psCpichEcNo,
    VOS_UINT8                           *pucRssi,
    VOS_UINT32                          *pulCellId
);

/* �ýӿڵ�������MmcMmaItf.h��Ų������ʱ�����ڴˣ�����SYSCFG�ع��ĵ��������Ż� */
VOS_BOOL NAS_MMA_GetServiceDomainSet(VOS_VOID);

/* Added by y00307564 for CDMA Iteration 8 2015-3-5 begin */
VOS_BOOL MN_PH_IsPlmnValid(TAF_PLMN_ID_STRU *pstPlmnId);
/* Added by y00307564 for CDMA Iteration 8 2015-3-5 end */

/* Added by y00322978 for CDMA 1X Iteration 11, 2015-3-27, begin */
VOS_VOID MN_PH_GetRssilvForCsqlvlExt (
    VOS_INT32                           lRssiValue,
    VOS_UINT8                           ucCurRaForSysInfo,
    MN_PH_CSQLVLEXT_RSSILV_ENUM_UINT8  *pucRssilv
);
VOS_VOID MMA_CrpnQuery_GetPlmnNum(
    TAF_PH_OPERATOR_NAME_STRU          *pstOrigOperName,
    TAF_MMA_CRPN_QRY_PARA_STRU         *pstMnMmaCrpnQry,
    VOS_UINT8                          *pucMaxMncLen,
    VOS_UINT32                         *pulTotalNum
);
TAF_UINT32 MMA_String2Hex(VOS_UINT8 *nptr,VOS_UINT16 usLen,VOS_UINT32 *pRtn);

VOS_VOID MMA_PhoneGetAllOperInfoByLongNameFromOperTbl(
    TAF_PH_OPERATOR_NAME_STRU   *pstOrigOperName,
    TAF_PH_OPERATOR_NAME_STRU   *pstOperName
);
VOS_VOID MMA_PhoneGetAllOperInfoByShortNameFromOperTbl(
    TAF_PH_OPERATOR_NAME_STRU   *pstOrigOperName,
    TAF_PH_OPERATOR_NAME_STRU   *pstOperName
);



/* Added by y00322978 for CDMA 1X Iteration 11, 2015-3-27, end */


VOS_VOID TAF_MMA_SetSyscfg_PowerOffStatus(
    TAF_MMA_SYS_CFG_REQ_STRU           *pstSysCfgReq
);



VOS_VOID TAF_MMA_ConvertLteFrequencyBand(
    TAF_USER_SET_PREF_BAND64           *pstLBand
);

VOS_UINT32 TAF_MMA_IsUserSettedLBandChanged(
    TAF_USER_SET_PREF_BAND64            *pstLBand,
    TAF_USER_SET_PREF_BAND64            *pstOrigLBand

);

VOS_UINT32 TAF_MMA_IsUserSettedRatOrderChanged(
    TAF_MMA_RAT_ORDER_STRU             *pstUserSettedRatOrder,
    TAF_MMA_RAT_ORDER_STRU             *pstOrigUserSettedRatOrder
);

VOS_VOID TAF_MMA_UpdateSysCfgPara(
    TAF_MMA_SYS_CFG_PARA_STRU          *pstCurrSysCfg
);

VOS_VOID  MN_PH_ConvertSysSubModeToAtFormat_FDD(
    TAF_SYS_SUBMODE_ENUM_UINT8          enSrcSysSubMode,
    MN_PH_SUB_SYS_MODE_EX_ENUM_U8      *penDestSysSubMode
);

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

#endif /* __MMA_APPLOCAL_H__ */

