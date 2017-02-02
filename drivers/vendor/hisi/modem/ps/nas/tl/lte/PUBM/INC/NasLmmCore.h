/******************************************************************************

        @(#)Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : NasLmmCore.h
    Description :
    History     :
      1.  hanlufeng 41410  Draft Enact
      2. zhengjunyan 2009-12-09  24301-CR39:TAU REQ��Ԫ���
      3. zhengjunyan 2011-05-28  �ļ����� NasMmCore.h�޸�Ϊ NasLmmCore.h
******************************************************************************/

#ifndef _NASLMMCORE_H
#define _NASLMMCORE_H

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include    "vos.h"
#include    "AppNasComm.h"
#include    "EmmEsmInterface.h"
#include    "NasLmmPubMFsm.h"
#include    "GmmLmmInterface.h"
#include    "NasEmmTauInterface.h"
#include    "MmLmmInterface.h"
#include    "LNasNvInterface.h"
#include    "UsimPsInterface.h"
#include    "EmmRabmInterface.h"
#include    "AppEsmInterface.h"

#include "product_config.h"



/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
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
  2 macro
*****************************************************************************/
#define NAS_LMM_MAX_EQU_PLMN_NUM         16

#define NAS_LMM_MAX_FORBTA_NUM           64                  /* FORBID TA ������ */
#define NAS_LMM_MAX_FORBLA_NUM           64                  /* FORBID LA ������ */

#define NAS_LMM_AUTH_RES_LEN             8
#define NAS_LMM_ALGORITHM_NOT_SUPPORT    0
#define NAS_LMM_ALGORITHM_SUPPORT        1

#define NAS_LMM_MAX_SUP_CODEC_NUM        10

#define NAS_LMM_NKSI_NO_KEY_IS_AVAILABLE 7

#define NAS_LMM_UE_NET_CAP_LEN           0x04

#define NAS_EMM_CN_NAME_MAX_LEN         255                 /* �������ֵ���󳤶� */

#define NAS_LMM_UE_NET_CAP_EEA           0xA0
#define NAS_LMM_UE_NET_CAP_EIA           0x20
#define NAS_LMM_UE_NET_CAP_UEA           0x00
#define NAS_LMM_UE_NET_CAP_UIA           0x00

#define NAS_LMM_MAX_EMG_NUM_LEN          48

#define NAS_EMM_EPS_LOC_MAX_LEN          sizeof(LNAS_LMM_NV_EPS_LOC_STRU)


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/



/*****************************************************************************
  4 Enum
*****************************************************************************/
/*****************************************************************************
�ṹ����    :NAS_MM_CN_CAUSE_ENUM
ʹ��˵��    :24301 9.9.3.7 EMM cause
*****************************************************************************/
enum    NAS_MM_CN_CAUSE_ENUM
{
    NAS_LMM_CAUSE_NULL                                       = 0x00, /* NULL����ԭ��                           */
    NAS_LMM_CAUSE_IMSI_UNKNOWN_IN_HSS                        = 0x02, /* IMSI unknown in HLR                      */
    NAS_LMM_CAUSE_ILLEGAL_UE                                 = 0x03, /* Illegal MS                               */

    NAS_LMM_CAUSE_IMEI_NOT_ACCEPTED                          = 0x05, /* IMEI not accepted                        */
    NAS_LMM_CAUSE_ILLEGAL_ME                                 = 0x06, /* Illegal ME                               */
    NAS_LMM_CAUSE_EPS_SERV_NOT_ALLOW                         = 0x07, /* GPRS services not allowed                */
    NAS_LMM_CAUSE_EPS_SERV_AND_NON_EPS_SERV_NOT_ALLOW        = 0x08, /* GPRS services and non-GPRS
                                                                       services not allowed                     */
    NAS_LMM_CAUSE_UE_ID_NOT_DERIVED                          = 0x09, /* MS identity cannot be derived
                                                                       by the network                           */
    NAS_LMM_CAUSE_IMPLICIT_DETACHED                          = 0x0A, /* Implicitly detached                      */
    NAS_LMM_CAUSE_PLMN_NOT_ALLOW                             = 0x0B, /* PLMN not allowed                         */
    NAS_LMM_CAUSE_TA_NOT_ALLOW                               = 0x0C, /* Location area not allowed                */
    NAS_LMM_CAUSE_ROAM_NOT_ALLOW                             = 0x0D, /* Roaming not allowed in
                                                                       this location area                       */
    NAS_LMM_CAUSE_EPS_SERV_NOT_ALLOW_IN_PLMN                 = 0x0E, /* GPRS services not allowed in this PLMN   */
    NAS_LMM_CAUSE_NO_SUITABL_CELL                            = 0x0F, /* No Suitable Cells In Location Area       */
    NAS_LMM_CAUSE_MSC_UNREACHABLE                            = 0x10, /* MSC temporarily not reachable            */
    NAS_LMM_CAUSE_NETWORK_FAILURE                            = 0x11, /* Network failure                          */
    NAS_LMM_CAUSE_CS_NOT_AVAIL                               = 0x12,
    NAS_LMM_CAUSE_ESM_FAILURE                                = 0x13,
    NAS_LMM_CAUSE_MAC_FAILURE                                = 0x14, /* MAC failure                              */
    NAS_LMM_CAUSE_SYNCH_FAILURE                              = 0x15, /* Synch failure                            */
    NAS_LMM_CAUSE_PROCEDURE_CONGESTION                       = 0x16, /* Congestion                               */
    NAS_LMM_CAUSE_UE_SECU_CAP_MISMATCH                       = 0x17,
    NAS_LMM_CAUSE_SECU_MODE_REJECTED_UNSPECIFIED             = 0x18,
    NAS_LMM_CAUSE_NOT_AUTHORIZED_FOR_THIS_CSG                = 0x19,

    NAS_LMM_CAUSE_REQUESTED_SER_OPTION_NOT_AUTHORIZED_IN_PLMN= 0x23,/* Requested service option not authorized in this PLMN */

    NAS_LMM_CAUSE_CS_FALLBACK_CALL_EST_NOT_ALLOWED           = 0x26,
    NAS_LMM_CAUSE_CS_DOMAIN_TMP_NOT_ALLOWED                  = 0x27,
    NAS_LMM_CAUSE_NO_EPS_BEARER_CONTEXT_ACTIVATED            = 0x28,

    NAS_LMM_CAUSE_SERVER_NETWORK_FAILURE                     = 0x2A,

    NAS_LMM_CAUSE_SEMANTICALLY_INCORRECT_MSG                 = 0x5F, /* Semantically incorrect message           */
    NAS_LMM_CAUSE_INVALID_MANDATORY_INF                      = 0x60, /* Invalid mandatory information            */
    NAS_LMM_CAUSE_MSG_NONEXIST_NOTIMPLEMENTE                 = 0x61, /* Message type non-existent or
                                                                       not implemented                          */
    NAS_LMM_CAUSE_MSG_TYPE_NOT_COMPATIBLE                    = 0x62, /* Message type not compatible with the
                                                                       protocol state                           */
    NAS_LMM_CAUSE_IE_NONEXIST_NOTIMPLEMENTED                 = 0x63, /* Information element non-existent or
                                                                       not implemented                          */
    NAS_LMM_CAUSE_CONDITIONAL_IE_ERROR                       = 0x64, /* Conditional IE error                     */
    NAS_LMM_CAUSE_MSG_NOT_COMPATIBLE                         = 0x65, /* Message not compatible with
                                                                       protocol state                           */
    NAS_LMM_CAUSE_PROTOCOL_ERROR                             = 0x6F /* Protocol error, unspecified              */
};
typedef VOS_UINT8 NAS_MM_CN_CAUSE_ENUM_UINT8;
typedef NAS_MM_CN_CAUSE_ENUM_UINT8  NAS_EMM_CN_CAUSE_ENUM_UINT8;
typedef NAS_MM_CN_CAUSE_ENUM_UINT8  NAS_EMMC_CN_CAUSE_ENUM_UINT8;


/*****************************************************************************
 ö����    : NAS_EMM_EPS_BEARER_CONTEXT_STATUS_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ���뼼����ȡֵ
*****************************************************************************/
enum NAS_EMM_EPS_BEARER_CONTEXT_STATUS_ENUM
{
    NAS_EMM_EPS_BEARER_STATUS_NOCHANGE = 0,
    NAS_EMM_EPS_BEARER_STATUS_CHANGEED = 1,
    NAS_EMM_EPS_BEARER_STATUS_BUTT
};
typedef VOS_UINT32  NAS_EMM_EPS_BEARER_CONTEXT_STATUS_ENUM_UINT32;
typedef NAS_EMM_EPS_BEARER_CONTEXT_STATUS_ENUM_UINT32  NAS_EMMC_EPS_BEARER_CONTEXT_STATUS_ENUM_UINT32;



/*****************************************************************************
 ö����    : NAS_LMM_GLOBLE_PARA_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ȫ�ֲ�������
*****************************************************************************/
enum NAS_LMM_GLOBLE_PARA_ENUM
{
    NAS_LMM_GLOBLE_PARA_UPLMNLIST                    = 0,
    NAS_LMM_GLOBLE_PARA_OPLMNLIST                       ,
    NAS_LMM_GLOBLE_PARA_IMSI                            ,
    NAS_LMM_GLOBLE_PARA_UEID                            ,
    NAS_LMM_GLOBLE_PARA_MNC_LEN                         ,
    NAS_LMM_GLOBLE_PARA_FPLMNLIST                       ,
    NAS_LMM_GLOBLE_FORB_TA_FOR_ROAMING                  ,
    NAS_LMM_GLOBLE_FORB_TA_FOR_RPOS                     ,
    NAS_LMM_GLOBLE_PRESENT_NET_ID                       ,
    NAS_LMM_GLOBLE_NET_INFO                             ,
    NAS_LMM_GLOBLE_TA_LIST                              ,
    NAS_LMM_GLOBLE_PARA_MAX_NUM_OF_FPLMN_BY_USIM        ,
    NAS_LMM_GLOBLE_PARA_HPLMN_ACT_LIST                  ,
    NAS_LMM_GLOBLE_PARA_LRPLMNSI                        ,
    NAS_LMM_GLOBLE_PARA_BUTT
};
typedef VOS_UINT32  NAS_LMM_GLOBLE_PARA_ENUM_UINT32;

enum NAS_LMM_TIMEZONE_ENUM
{
    NAS_LMM_TIMEZONE_POSITIVE                        = 0,
    NAS_LMM_TIMEZONE_NAGETIVE                           ,
    NAS_LMM_TIMEZONE_BUTT
};
typedef VOS_UINT8  NAS_LMM_TIMEZONE_ENUM_UINT8;

enum NAS_LMM_DAYLIGHT_SAVE_TIME_ENUM
{
    NAS_LMM_DAYLIGHT_NO_ADJUST                         = 0,
    NAS_LMM_DAYLIGHT_1_HOUR_ADJUST                        ,
    NAS_LMM_DAYLIGHT_2_HOUR_ADJUST                        ,
    NAS_LMM_DAYLIGHT_BUTT
};
typedef VOS_UINT8  NAS_LMM_DAYLIGHT_SAVE_TIME_ENUM_UINT8;

enum    NAS_EMM_CN_MSG_TYPE_ENUM
{
    EMM_MSG_TYPE_INVALID                = 0x00,

    NAS_EMM_CN_MT_ATTACH_REQ            = 0x41,
    NAS_EMM_CN_MT_ATTACH_ACP            = 0x42,
    NAS_EMM_CN_MT_ATTACH_CMP            = 0x43,
    NAS_EMM_CN_MT_ATTACH_REJ            = 0x44,

    NAS_EMM_CN_MT_DETACH_REQ_MT         = 0x45,
  /*NAS_EMM_CN_MT_DETACH_ACP_MT         = 0xC5,*/
  /*NAS_EMM_CN_MT_DETACH_REQ_MO         = 0xD6,*/
    NAS_EMM_CN_MT_DETACH_ACP_MO         = 0x46,


    NAS_EMM_CN_MT_TAU_REQ               = 0x48,
    NAS_EMM_CN_MT_TAU_ACP               = 0x49,
    NAS_EMM_CN_MT_TAU_CMP               = 0x4A,
    NAS_EMM_CN_MT_TAU_REJ               = 0x4B,

    NAS_EMM_CN_MT_SER_REQ               = 0xC7,
    NAS_EMM_CN_MT_EXT_SER_REQ           = 0x4C,
    NAS_EMM_CN_MT_SER_REJ               = 0x4E,
    /*NAS_EMM_CN_SER_ACP,*/

    NAS_EMM_CN_MT_GUTI_CMD              = 0x50,
    NAS_EMM_CN_MT_GUTI_CMP              = 0x51,

    NAS_EMM_CN_MT_AUTH_REQ              = 0x52,/* 0101 0010  Authentication request  */
    NAS_EMM_CN_MT_AUTH_RSP              = 0x53,/* 0101 0011  Authentication response */
    NAS_EMM_CN_MT_AUTH_REJ              = 0x54,/* 0101 0100  Authentication response */
    NAS_EMM_CN_MT_IDEN_REQ              = 0x55,
    NAS_EMM_CN_MT_IDEN_RSP              = 0x56,


    NAS_EMM_CN_MT_AUTH_FAIl             = 0x5C,/* 0101 0100  Authentication failure */

    NAS_EMM_CN_MT_SMC_CMD               = 0x5D,/* 0101 0010  Security mode command  */
    NAS_EMM_CN_MT_SMC_CMP               = 0x5E,/* 0101 0010  Security mode complete */
    NAS_EMM_CN_MT_SMC_REJ               = 0x5F,/* 0101 0010  Security mode reject   */

    NAS_EMM_CN_MT_EMM_STATUS            = 0x60,/* 0110 0000 */
    NAS_EMM_CN_MT_EMM_INFO              = 0x61,/* 0110 0001 */

    NAS_EMM_CN_MT_DOWNLINK_NAS_TRANSPORT= 0x62,/* 0110 0010 */
    NAS_EMM_CN_MT_UPLINK_NAS_TRANSPORT  = 0x63,/* 0110 0011 */

    NAS_EMM_CN_CS_SER_NOTIFICATION      = 0x64,/* 0110 0100 */

    NAS_EMM_CN_MT_DOWNLINK_GENERIC_NAS_TRANSPORT    = 0x68,/* 0110 1000 */
    NAS_EMM_CN_MT_UPLINK_GENERIC_NAS_TRANSPORT      = 0x69,/* 0110 1001 */

    NAS_EMM_CN_MT_BUTT
};
typedef VOS_UINT8 NAS_EMM_CN_MSG_TYPE_ENUM_UINT8;

enum    NAS_EMM_T3402_SRC_TYPE_ENUM
{

    NAS_EMM_T3402_SRC_ATTACH_REJ,
    NAS_EMM_T3402_SRC_OTHERS,

    NAS_EMM_T3402_SRC_BUTT
};
typedef VOS_UINT8 NAS_EMM_T3402_SRC_ENUM_UINT8;


/*****************************************************************************
 �ṹ��    : NAS_LMM_SIM_SRV_STATUS_ENUM_UINT32
 �ṹ˵��  :
*****************************************************************************/
enum NAS_LMM_SIM_SRV_STATUS_ENUM
{
    NAS_LMM_SIM_SRV_UNAVAILABLE          = 0x0000,
    NAS_LMM_SIM_SRV_AVAILABLE                     ,
    NAS_LMM_SIM_SRV_BUTT
};
typedef VOS_UINT32 NAS_LMM_SIM_SRV_STATUS_ENUM_UINT32;


/*****************************************************************************
 �ṹ��    : NAS_LMM_SIM_STAT_ENUM
 �ṹ˵��  :
*****************************************************************************/
enum NAS_LMM_SIM_STAT_ENUM
{
    NAS_LMM_SIM_STATUS_UNAVAILABLE,
    NAS_LMM_SIM_STATUS_AVAILABLE,
    NAS_LMM_SIM_STATUS_BUTT
};
typedef VOS_UINT32 NAS_LMM_SIM_STAT_ENUM_UINT32;


/*****************************************************************************
 �ṹ��    : NAS_LMM_SIM_VALIDITY_ENUM
 �ṹ˵��  :
*****************************************************************************/
enum NAS_LMM_SIM_VALIDITY_ENUM
{
    NAS_LMM_SIM_VALID,
    NAS_LMM_SIM_INVALID,
    NAS_LMM_SIM_VALIDITY_BUTT
};
typedef VOS_UINT32 NAS_LMM_SIM_VALIDITY_ENUM_UINT32;


/*****************************************************************************
 �ṹ��    : NAS_LMM_NET_FEATURE_ENUM
 �ṹ˵��  :
*****************************************************************************/
enum NAS_LMM_NET_FEATURE_ENUM
{
    NAS_LMM_NET_FEATURE_IMSVOPS                     = 0x01,
    NAS_LMM_NET_FEATURE_EMCBS                       = 0x02,
    NAS_LMM_NET_FEATURE_EPCLCS                      = 0x04,
    NAS_LMM_NET_FEATURE_CSLCS                       = 0x08,

    NAS_LMM_NET_FEATURE_BUTT
};
typedef VOS_UINT8 NAS_LMM_NET_FEATURE_ENUM_UINT8;


/*****************************************************************************
 �ṹ��    : NAS_LMM_ADDITION_UPDATE_RSLT_ENUM
 �ṹ˵��  :
*****************************************************************************/
enum NAS_LMM_ADDITIONAL_UPDATE_RSLT_ENUM
{
    NAS_LMM_ADDITIONAL_UPDATE_NO_INFO           = 0, /* NO_INFO��ʾCS֧��ȫ���� */
    NAS_LMM_ADDITIONAL_UPDATE_CSFB_NOT_PREFERED = 1,
    NAS_LMM_ADDITIONAL_UPDATE_SMS_ONLY          = 2,
    NAS_LMM_ADDITIONAL_UPDATE_NOT_ATTACHED      = 3,
    NAS_LMM_ADDITIONAL_UPDATE_BUTT
};
typedef VOS_UINT32 NAS_LMM_ADDITIONAL_UPDATE_RSLT_ENUM_UINT32;
/*****************************************************************************
 �ṹ����:  NAS_LMM_REG_DOMAIN_ENUM
 Э����:  Lģ��ע��ɹ�����
 ASN.1 ����:
 �ṹ˵��:
*****************************************************************************/
enum NAS_LMM_REG_DOMAIN_ENUM
{
    NAS_LMM_REG_DOMAIN_NULL             = 0x00,
    NAS_LMM_REG_DOMAIN_PS               = 0x01,
    NAS_LMM_REG_DOMAIN_CS               = 0x02,
    NAS_LMM_REG_DOMAIN_CS_PS            = 0x03,

    NAS_LMM_REG_DOMAIN_BUTT
};
typedef VOS_UINT32  NAS_LMM_REG_DOMAIN_ENUM_UINT32;

/*****************************************************************************
 ö����    : NAS_EMM_LAU_OR_COMBINED_RAU_FLAG_ENUM
 ö��˵��  : LAU��������RAU��ʶö��
*****************************************************************************/
enum  NAS_EMM_LAU_OR_COMBINED_RAU_FLAG_ENUM
{
    NAS_EMM_LAU_OR_COMBINED_RAU_NOT_HAPPENED        = 0,
    NAS_EMM_LAU_OR_COMBINED_RAU_HAPPENED            = 1,

    NAS_EMM_LAU_OR_COMBINED_RAU_FLAG_BUTT
};
typedef VOS_UINT32   NAS_EMM_LAU_OR_COMBINED_RAU_FLAG_ENUM_UINT32;

/*****************************************************************************
 ö����    : NAS_EMM_SRVCC_FLAG_ENUM
 ö��˵��  : SRVCC��ʶö��
*****************************************************************************/
enum  NAS_EMM_SRVCC_FLAG_ENUM
{
    NAS_EMM_SRVCC_NOT_HAPPENED        = 0,
    NAS_EMM_SRVCC_HAPPENED            = 1,

    NAS_EMM_SRVCC_FLAG_BUTT
};
typedef VOS_UINT32   NAS_EMM_SRVCC_FLAG_ENUM_UINT32;


/*****************************************************************************
 ö����    : NAS_EMM_FIRST_TAU_FLAG_ENUM
 ö��˵��  : ��һ��TAU��ʶö��
*****************************************************************************/
enum  NAS_EMM_FIRST_TAU_FLAG_ENUM
{
    NAS_EMM_NOT_FIRST_TAU               = 0,
    NAS_EMM_FIRST_TAU                   = 1,

    NAS_EMM_FIRST_TAU_FLAG_BUTT
};
typedef VOS_UINT32   NAS_EMM_FIRST_TAU_FLAG_ENUM_UINT32;
/*****************************************************************************
 �ṹ����   : NAS_LMM_SUSPEND_NOTIFY_ENUM
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : LRRC��ID_LRRC_LNAS_SYS_CFG_CNF֪ͨLMM �˴��Ƿ���ҪLMM����LRRC���Լ������ԭ��
*****************************************************************************/
enum NAS_LMM_SUSPEND_TYPE_NOTIFY_ENUM
{
    NAS_LMM_NOT_SUSPEND                  = 0,
    NAS_LMM_SUSPEND_LTE_RAT_NOT_ACTIVE   = 1,
    NAS_LMM_SUSPEND_LTE_BAND_NOT_SUPPORT = 2,

    NAS_LMM_SUSPEND_NOTIFY_BUTT
};
typedef VOS_UINT32 NAS_LMM_SUSPEND_TYPE_NOTIFY_ENUM_UINT32;

/*****************************************************************************
 �ṹ����   : NAS_LMM_CONNECTION_CLIENTID_ENUM
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   :
*****************************************************************************/
enum NAS_LMM_CONNECTION_CLIENT_ID_ENUM
{
    NAS_LMM_CONNECTION_CLIENT_ID_NULL      = 0,
    NAS_LMM_CONNECTION_CLIENT_ID_SMS      = 1,


    NAS_LMM_CONNECTION_CLIENT_ID_BUTT
};
typedef VOS_UINT32 NAS_LMM_CONNECTION_CLIENT_ID_ENUM_UINT32;
/*****************************************************************************
 ö����    : NAS_EMM_REJ_FLAG_ENUM
 ö��˵��  : �ܾ���ʶ
*****************************************************************************/
enum  NAS_EMM_REJ_FLAG_ENUM
{
    NAS_EMM_REJ_NO                      = 0,
    NAS_EMM_REJ_YES                     = 1,

    NAS_EMM_REJ_BUTT
};
typedef VOS_UINT32   NAS_EMM_REJ_FLAG_ENUM_UINT32;
/*****************************************************************************
 ö����    : NAS_EMM_PLMN_SRCH_ENUM
 ö��˵��  : PLMN_SRCH��ʶ
*****************************************************************************/
enum  NAS_EMM_PLMN_SRCH_FLAG_ENUM
{
    NAS_EMM_PLMN_SRCH_FLAG_INVALID                   = 0,
    NAS_EMM_PLMN_SRCH_FLAG_VALID                     = 1,

    NAS_EMM_PLMN_SRCH_FLAG_BUTT
};
typedef VOS_UINT32   NAS_EMM_PLMN_SRCH_FLAG_ENUM_UINT32;
/*****************************************************************************
 �ṹ����   : NAS_LMM_LTE_ENABLE_STA_ENUM
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   :�յ�MMC�·���DISABLE����ENABLE LTE��Ϣ����¼LTE���뼼����ʹ��״̬
             Ŀǰ��δ�����ñ�ʶ�����á�
*****************************************************************************/
enum NAS_LMM_LTE_ENABLE_STA_ENUM
{
    NAS_LMM_LTE_ENABLED              = 0,
    NAS_LMM_LTE_DISABLED             = 1,

    NAS_LMM_LTE_ENABLE_STA_BUTT
};

typedef VOS_UINT32 NAS_LMM_LTE_ENABLE_STA_ENUM_UINT32;

/*****************************************************************************
 ö����    : NAS_EMM_FIRST_TAU_FLAG_ENUM
 ö��˵��  : ��ʶ������REG+NORMAL_SERVICEʱ���Ƿ���Ҫ��Ϊ����REG+ATTEMPT_TO_UPDATE_MM
*****************************************************************************/
enum  NAS_EMM_UPDATE_MM_FLAG_ENUM
{
    NAS_EMM_UPDATE_MM_FLAG_INVALID      = 0,
    NAS_EMM_UPDATE_MM_FLAG_VALID        = 1,

    NAS_EMM_UPDATE_MM_FLAG_BUTT
};
typedef VOS_UINT32   NAS_EMM_UPDATE_MM_FLAG_ENUM_UINT32;

/*****************************************************************************
 ö����    : NAS_LMM_REG_STATUS_ENUM
 ö��˵��  : ��ʶע��״̬
*****************************************************************************/
enum  NAS_LMM_REG_STATUS_ENUM
{
    NAS_LMM_REG_STATUS_DEREG                    = 0,
    NAS_LMM_REG_STATUS_EMC_REGING               = 1,
    NAS_LMM_REG_STATUS_NORM_REGED               = 2,
    NAS_LMM_REG_STATUS_EMC_REGED                = 3,
    NAS_LMM_REG_STATUS_NORM_REGED_AND_EMC_BEAR  = 4,

    NAS_LMM_REG_STATUS_BUTT
};
typedef VOS_UINT32   NAS_LMM_REG_STATUS_ENUM_UINT32;

/*****************************************************************************
 �ṹ����   : NAS_LMM_UE_RADIO_CAP_CHANGE_ENUM
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : LRRC��ID_LRRC_LNAS_SYS_CFG_CNF֪ͨLMM , UE�����߽�������
              �����ı仯�����У�LTE�����仯����GUL�д���L�仯�����������
              GU�����仯����L������GU�仯�����������
*****************************************************************************/
enum NAS_LMM_UE_RADIO_CAP_CHANGE_ENUM
{
    NAS_LMM_UE_RADIO_CAP_NOT_CHG              = 0,
    NAS_LMM_UE_RADIO_CAP_GU_CHG               = 1,
    NAS_LMM_UE_RADIO_CAP_LTE_CHG              = 2,

    NAS_LMM_UE_RADIO_CAP_CHG_BUTT
};
typedef VOS_UINT32  NAS_LMM_UE_RADIO_CAP_CHANGE_ENUM_UINT32;

/*****************************************************************************
 ö����    : NAS_LMM_SYSCFG_ENUM
 �ṹ˵��  : UE��syscfg��ʶ
*****************************************************************************/
enum NAS_LMM_SYSCFG_FLAG_ENUM
{
   NAS_LMM_SYSCFG_FLAG_INVALID                  = 0,    /* SYSCFG��ʶ��Ч */
   NAS_LMM_SYSCFG_FLAG_VALID                    = 1,    /* SYSCFG��ʶ��Ч */

   NAS_LMM_SYSCFG_FLAG_BUTT
};
typedef VOS_UINT32   NAS_LMM_SYSCFG_FLAG_ENUM_UINT32;

/*****************************************************************************
 ö����    : NAS_EMM_DSDS_TAU_TYPE_ENUM_UINT32
 ö��˵��  : DSDS TAU��ʶö��
*****************************************************************************/
enum  NAS_EMM_DSDS_TAU_TYPE_ENUM
{
    NAS_EMM_DSDS_LOW_TAU        = 0,
    NAS_EMM_DSDS_HIGH_TAU       = 1,

    NAS_EMM_DSDS_TAU_BUTT
};
typedef VOS_UINT32  NAS_EMM_DSDS_TAU_TYPE_ENUM_UINT32;


/*****************************************************************************
  5 STRUCT
*****************************************************************************/

/*****************************************************************************
 �ṹ��    : NAS_LMM_PID_MSG_STRU
 �ṹ˵��  : NAS_LMM PID �����Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;                /* ��Ϣ ID */
    VOS_UINT8                           aucMsgData[4];          /* ������Ϣ�洢 */
}NAS_LMM_PID_MSG_STRU;



/*****************************************************************************
�ṹ����    :
ʹ��˵��    :
*****************************************************************************/
typedef struct
{
    NAS_LMM_TIMEZONE_ENUM_UINT8          enPosNegTimeZone;
    VOS_UINT8                           ucTimeZone;
    VOS_UINT8                           aucRsv[2];
}NAS_EMM_CN_TIMEZONE_STRU;

typedef struct
{
    NAS_EMM_CN_TIMEZONE_STRU            stTimeZone;
    VOS_UINT8                           ucYear;
    VOS_UINT8                           ucMonth;
    VOS_UINT8                           ucDay;
    VOS_UINT8                           ucHour;
    VOS_UINT8                           ucMinute;
    VOS_UINT8                           ucSecond;
    VOS_UINT8                           aucRsv[2];
}NAS_EMM_CN_TIMEZONE_UNITIME_STRU;



/*****************************************************************************
�ṹ����    :NAS_EMM_CN_Network_Name_STRU
ʹ��˵��    :24301 8.2.1.1: Emm Information message
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucMsgLen; /*��ʾ������TextString�ĳ���*/
    VOS_UINT8                           ucCodingScheme;
    VOS_UINT8                           ucAddCI;
    VOS_UINT8                           ucNumOfSpareInLastByte;
    VOS_UINT8                           aucMsg[NAS_EMM_CN_NAME_MAX_LEN];
    VOS_UINT8                           ucRsv;
}NAS_EMM_CN_NETWORK_NAME_STRU;


/*==============================================================================
�ṹ����    : NAS_LMM_UEID_STRU
ʹ��˵��    : IMSI, IMEI, IMEISV, TMSI, PTMSI�Ĵ�Ÿ�ʽ���� 31.102 4.2.2ִ��

    digit n �� 24.008 10.5.4  Mobile Identity information element �Ķ�Ӧ��ϵ:

    One digit occupies half of a byte.

    Э�������� ��DIGIT���ֽ�/λ�Ĺ�ϵ����:
    ----------------------------------------------------------------------------------
    (BIT8)|(BIT7)|(BIT6)|(BIT5)|(BIT4)|(BIT3)|(BIT2)|(BIT1)
    ----------------------------------------------------------------------------------
        Length of mobile identity contents, UNIT is byte
    ----------------------------------------------------------------------------------
        Identity digit 1       | OorE |  Type of identity
    ----------------------------------------------------------------------------------
        Identity digit 3       |           Identity digit 2
    ----------------------------------------------------------------------------------
        Identity digit i + 1   |           Identity digit i
    ----------------------------------------------------------------------------------
        ......                 |           ......
    ----------------------------------------------------------------------------------
        Identity digit P + 1   |           Identity digit P
    ----------------------------------------------------------------------------------

    ��, �ӿ������и� DIGIT���ֽ�λ�ö�Ӧ��ϵ����:
    -----------------------------------------------------------------------------------------------
    (digit 15) | (digit 14) |.....| (digit  2) | (digit  1) |OorE|TypeOfId|Length of mobile identity contents, UNIT is byte
    -----------------------------------------------------------------------------------------------
    aucImsi[7] | aucImsi [7]|.....| aucImsi[2] | aucImsi[1] | aucImsi[1]  | aucImsi[0] | aucImsi[0]
    -----------------------------------------------------------------------------------------------
    aucImei[7] | aucImei [7]|.....| aucImei[2] | aucImei[1] | aucImei[1]  | aucImei[0] | aucImei[0]
    -----------------------------------------------------------------------------------------------
    aucTmsi[7] | aucTmsi [7]|.....| aucTmsi[2] | aucTmsi[1] | aucTmsi[1]  | aucTmsi[0] | aucTmsi[0]
    -----------------------------------------------------------------------------------------------
    aucPTmsi[7]|aucPTmsi [7]|.....| aucPTmsi[2]| aucPTmsi[1]| aucPTmsi[1] | aucPTmsi[0]| aucPTmsi[0]
    -----------------------------------------------------------------------------------------------
    aucImeisv[7]|aucImeisv[7]|....|aucImeisv[2]|aucImeisv[1]|aucImeisv[1] |aucImeisv[0]| aucImeisv[0]
    -----------------------------------------------------------------------------------------------


    e.g.          IMSI = 230 040 680000079
    ��RRC_NAS�Ľӿ����� aucImsi[] �д��λ������:

    Э�������Ĵ��λ������:
    -------------------------------------------------------------------------------
                           (BIT8)|(BIT7)|(BIT6)|(BIT5)|(BIT4)|(BIT3)|(BIT2)|(BIT1)
    -------------------------------------------------------------------------------
    aucImsi[0] | aucImsi[0]                           8
    ----------------------------------------------------------------------------
    aucImsi[1] | aucImsi[1]               2           |           9
    ----------------------------------------------------------------------------
    aucImsi[2] | aucImsi[2]               0           |           3
    ----------------------------------------------------------------------------
    aucImsi[3] | aucImsi[3]               4           |           0
    -------------------------- -------------------------------------------------
    aucImsi[4] | aucImsi[4]               6           |           0
    ---------------------------------------------------- -----------------------
    aucImsi[5] | aucImsi[5]               0           |           8
    ---------------------------------------------------- -----------------------
    aucImsi[6] | aucImsi[6]               0           |           0
    ----------------------------------------------------------------------------
    aucImsi[7] | aucImsi[7]               0           |           0
    ----------------------------------------------------------------------------
    aucImsi[8] | aucImsi[8]               9           |           7
    ----------------------------------------------------------------------------

    ��, �ӿ������и� DIGIT���ֽ�λ�ö�Ӧ��ϵ����:
    -----------------------------------------------------------------------------------------------
    aucImsi[7] | aucImsi [7]|.....| aucImsi[2] | aucImsi[1] | aucImsi[1]|aucImsi[0] | aucImsi[0]
    -----------------------------------------------------------------------------------------------
    (   9    ) | (    7   ) |.....| (    3   ) | (    2   ) | (   9   ) |           8
    -----------------------------------------------------------------------------------------------


     bitOp**����ʶ��Ӧ����Ϣ�Ƿ���Ч��ȡֵ����������:
     #define NAS_EMM_BIT_SLCT      1 :      VALID
     #define NAS_EMM_BIT_NO_SLCT   0 :      INVALID
==============================================================================*/
typedef struct
{
    VOS_UINT32                          bitOpImsi     :1; /* 1: VALID; 0: INVALID*/
    VOS_UINT32                          bitOpImei     :1;
    VOS_UINT32                          bitOpImeisv   :1;
    VOS_UINT32                          bitOpTmsi     :1; /* TMSI status  24.008 10.5.5.4 */
    VOS_UINT32                          bitOpPtmsi    :1;
    VOS_UINT32                          bitOpGuti     :1;
    VOS_UINT32                          bitOpTmgiMbms :1; /* 1: VALID; 0: INVALID*/
    VOS_UINT32                          bitOpRsv      :25;


    VOS_UINT8                           aucImsi[NAS_MM_MAX_UEID_BUF_SIZE];
    VOS_UINT8                           aucReserved1[2];
    VOS_UINT8                           aucImei[NAS_MM_MAX_UEID_BUF_SIZE];
    VOS_UINT8                           aucReserved2[2];
    VOS_UINT8                           aucImeisv[NAS_MM_MAX_UEID_BUF_SIZE];
    VOS_UINT8                           aucReserved3[2];
    VOS_UINT8                           aucTmsi[NAS_MM_MAX_UEID_BUF_SIZE];
    VOS_UINT8                           aucReserved4[2];
    VOS_UINT8                           aucPtmsi[NAS_MM_MAX_UEID_BUF_SIZE];
    VOS_UINT8                           aucReserved5[2];
    NAS_MM_GUTI_STRU                    stGuti;
    NAS_MM_TMGI_MBMS_STRU               stTmgiMbms;
    VOS_UINT32                          ulImsiMncLen;
}NAS_LMM_UEID_STRU;
typedef NAS_LMM_UEID_STRU                NAS_EMM_UEID_STRU;
typedef NAS_LMM_UEID_STRU                NAS_EMMC_UEID_STRU;



/*****************************************************************************
�ṹ����    :MS identity_STRU
ʹ��˵��    :24301 8.2.1.1: Emm Information message
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucMsId[NAS_MM_MAX_MSID_SIZE];
    VOS_UINT8                           aucReserved1[2];
}NAS_LMM_MSID_STRU;
typedef NAS_LMM_MSID_STRU                NAS_EMM_MSID_STRU;


/*****************************************************************************
�ṹ����    :NAS_LMM_CODEC_STRU
ʹ��˵��    :24.008 840 10.5.4.32 Supported codec list
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSysId;
    VOS_UINT8                           ucLenOfBitmap;
    VOS_UINT8                           aucCodecBitmap[2];

}NAS_LMM_CODEC_STRU;

/*****************************************************************************
�ṹ����    :NAS_LMM_SUP_CODEC_LIST_STRU
ʹ��˵��    :24.008 840 10.5.4.32 Supported codec list
[10.5.4.32] of 24.008
8       7       6       5       4       3       2       1
������������������������������������������������������������������
��                  Supported Codec List IEI                    ��Octet 1
������������������������������������������������������������������
��                Length Of Supported Codec list                ��Octet 2
������������������������������������������������������������������
��               System Identification 1 (SysID 1)              ��Octet 3
������������������������������������������������������������������
��                 Length Of Bitmap for SysID 1                 ��Octet 4
������������������������������������������������������������������
��             Codec Bitmap for SysID 1, bits 1 to 8            ��Octet 5
������������������������������������������������������������������
��             Codec Bitmap for SysID 1, bits 9 to 16           ��Octet 6
������������������������������������������������������������������
��               System Identification 2 (SysID 2)              ��Octet j
������������������������������������������������������������������
��                 Length Of Bitmap for SysID 2                 ��Octet j+1
������������������������������������������������������������������
��             Codec Bitmap for SysID 2, bits 1 to 8            ��Octet j+2
������������������������������������������������������������������
��             Codec Bitmap for SysID 2, bits 9 to 16           ��Octet j+3
������������������������������������������������������������������
��               System Identification x (SysID x)              ��Octet m
������������������������������������������������������������������
��                 Length Of Bitmap for SysID x                 ��Octet m+1
������������������������������������������������������������������
��             Codec Bitmap for SysID x, bits 1 to 8            ��Octet m+2
������������������������������������������������������������������
��             Codec Bitmap for SysID x, bits 9 to 16           ��Octet m+3
������������������������������������������������������������������

*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucLenOfCodecList;
    VOS_UINT8                           aucRsv[3];

    NAS_LMM_CODEC_STRU                   astCodec[NAS_LMM_MAX_SUP_CODEC_NUM];
}NAS_LMM_CODEC_LIST_STRU;
typedef NAS_LMM_CODEC_LIST_STRU          NAS_EMM_CODEC_LIST_STRU;
typedef NAS_LMM_CODEC_LIST_STRU          NAS_EMMC_CODEC_LIST_STRU;



/*****************************************************************************
�ṹ����    :NAS_LMM_NETWORK_INFO_STRU
ʹ��˵��    :MM�Ĺ���������Ϣ
             1. FORBIDEN PLMN�б���Ϣ��MMCģ�鱣�棬�������ﱣ��;
             2. ATTACH, DETACH, TAU, SERVICE, AUTH�Ľ�����漰��������������Ϣ
                ���޸Ĳ����У�ֻ�� stEPlmnList �Ĳ�����MMC���յ�ACTION_RST ��Ϣ
                ���޸Ĵ˴�ȫ�ֱ�����������Ϣ�ɸ�ģ���յ�CN������Ϣ���޸�ά����
             bitOp**����ʶ��Ӧ����Ϣ�Ƿ���Ч��ȡֵ����������:
             #define NAS_EMM_BIT_SLCT      1 :      VALID
             #define NAS_EMM_BIT_NO_SLCT   0 :      INVALID
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpPresentNetId   :1;
    VOS_UINT32                          bitOpLastRegNetId   :1;
    VOS_UINT32                          bitOpLastAttmpRegTa   :1;
    VOS_UINT32                          bitOpEPlmnList      :1;
    VOS_UINT32                          bitOpTaiList        :1;
    VOS_UINT32                          bitOpHplmn          :1;

    VOS_UINT32                          bitOpEHplmnList     :1;
    VOS_UINT32                          bitOpFoibTaForRpos  :1;
    VOS_UINT32                          bitOpFoibTaForRoam  :1;
    VOS_UINT32                          bitOpForbTaForRej15 :1;
    /* Mod by y00307272 for LNAS_POSITION_INFO, 2015-10-15, Begin */
    VOS_UINT32                          bitOpRsv            :22;
    /* Mod by y00307272 for LNAS_POSITION_INFO, 2015-10-15, End */

    NAS_MM_NETWORK_ID_STRU              stPresentNetId;     /* ��ǰפ����������Ϣ */
    NAS_MM_NETWORK_ID_STRU              stLastRegNetId;     /* �ϴγɹ�ע���������Ϣ */

    NAS_MM_TA_STRU                      stLastAttmpRegTa;   /* �ϴγ��Է���ע���TA��Ϣ */


    NAS_MM_PLMN_LIST_STRU               stEPlmnList;
    NAS_MM_TA_LIST_STRU                 stTaiList;

    NAS_MM_PLMN_ID_STRU                 stHplmn;
    NAS_MM_PLMN_LIST_STRU               stEHplmnList;

    NAS_MM_FORB_TA_LIST_STRU            stForbTaForRoam;    /* forbidden tracking areas for roaming*/
    NAS_MM_FORB_TA_LIST_STRU            stForbTaForRpos;    /* forbidden tracking areas for
                                                               regional provision of service*/
    NAS_MM_FORB_TA_LIST_STRU            stForbTaForRej15;   /* �û�ָ��������ATTACH��TAU�ܾ�#15�󱣴���б�*/

}NAS_LMM_NETWORK_INFO_STRU;
typedef NAS_LMM_NETWORK_INFO_STRU        NAS_EMM_NETWORK_INFO_STRU;
typedef NAS_LMM_NETWORK_INFO_STRU        NAS_EMMC_NETWORK_INFO_STRU;

/*****************************************************************************
�ṹ����    :NAS_LMM_APP_PARA_STRU
ʹ��˵��    :
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulMsgId;
    VOS_UINT32                          ulOpId;
}NAS_LMM_APP_PARA_STRU;


/*****************************************************************************
�ṹ����    :NAS_EMM_PUB_INFO_STRU
ʹ��˵��    :MM�Ĺ�����Ϣ
             bitOp**����ʶ��Ӧ����Ϣ�Ƿ���Ч��ȡֵ����������:
             #define NAS_EMM_BIT_SLCT      1 :      VALID
             #define NAS_EMM_BIT_NO_SLCT   0 :      INVALID
*****************************************************************************/
typedef struct
{
    VOS_UINT32                            bitOpFullName              :1; /* 1: VALID; 0: INVALID*/
    VOS_UINT32                            bitOpShortName             :1; /* 1: VALID; 0: INVALID*/
    VOS_UINT32                            bitOpLocTimeZone           :1; /* 1: VALID; 0: INVALID*/
    VOS_UINT32                            bitOpUniTimeLocTimeZone    :1; /* 1: VALID; 0: INVALID*/
    VOS_UINT32                            bitOpDaylightTime          :1; /* 1: VALID; 0: INVALID*/
    VOS_UINT32                            bitShare                   :27;

    NAS_EMM_CN_TIMEZONE_STRU              stLocTimeZone;
    NAS_EMM_CN_TIMEZONE_UNITIME_STRU      stTimeZoneAndTime;
    NAS_LMM_DAYLIGHT_SAVE_TIME_ENUM_UINT8  enDaylightSavingTime;
    VOS_UINT8                             aucOperatorNameLong[MMC_LMM_MAX_OPER_LONG_NAME_LEN];
    VOS_UINT8                             aucOperatorNameShort[MMC_LMM_MAX_OPER_SHORT_NAME_LEN];
    VOS_UINT8                             aucRsv[3];
}NAS_EMM_INFO_STRU;



/*****************************************************************************
 ö����: MMC_LMM_TRANSCEIVER_TYPE_ENUM
 Э���ʽ:
 ASN.1����:
 ö��˵��:��������ȡֵ
*****************************************************************************/
enum NAS_EMM_TRANSCEIVER_TYPE_ENUM
{
    NAS_EMM_TRANSCEIVER_TYPE_SINGLE     = 0,
    NAS_EMM_TRANSCEIVER_TYPE_DUAL           ,

    NAS_EMM_TRANSCEIVER_TYPE_BUTT
};
typedef VOS_UINT32 NAS_EMM_TRANSCEIVER_TYPE_ENUM_UINT32;


/*****************************************************************************
 ö����    : NAS_EMM_RAT_TYPE_ENUM_UINT8
 Э����  :
 ASN.1���� :
 ö��˵��  : ��ʽ����
*****************************************************************************/
enum NAS_EMM_RAT_TYPE_ENUM
{
    /* ������ĳ�ֻ������н��뼼�� */
    NAS_EMM_RAT_NONE                = 0,
    NAS_EMM_RAT_LTE_FDD             = 1,
    NAS_EMM_RAT_LTE_TDD             = 2,
    NAS_EMM_RAT_LTE_ALL             = 3,
    NAS_EMM_RAT_UTRAN_FDD           = 4,
    NAS_EMM_RAT_UTRAN_TDD           = 8,
    NAS_EMM_RAT_UTRAN_ALL           = 12,
    NAS_EMM_RAT_GERAN               = 16,
    NAS_EMM_RAT_ALL                 = 31,
    NAS_EMM_RAT_BUTT
};
typedef VOS_UINT8 NAS_EMM_RAT_TYPE_ENUM_UINT8;


/*****************************************************************************
�ṹ����    :NAS_EMM_START_INFO_STRU
ʹ��˵��    :������Ϣ
*****************************************************************************/
typedef struct
{
    MMC_LMM_TRANSCEIVER_TYPE_ENUM_UINT32 ulTransceiverType;

    NAS_LMM_RAT_PRIO_ENUM_UINT8          aucRatPrioList[NAS_LMM_RAT_TYPE_BUTT];     /* ��ģ�����ȼ� */

    NAS_LMM_RAT_PRIO_ENUM_UINT8          aucCurRatPrioList[NAS_LMM_RAT_TYPE_BUTT];
    NAS_LMM_RAT_PRIO_ENUM_UINT8          aucPreRatPrioList[NAS_LMM_RAT_TYPE_BUTT];

    VOS_UINT8                            aucRsv[1];
}NAS_EMM_START_INFO_STRU;



/*****************************************************************************
 �ṹ����: NAS_LMM_SUS_SYS_CHNG_DIR_ENUM
 Э����:
 ASN.1 ����:
 �ṹ˵��:
*****************************************************************************/
enum   NAS_LMM_SUS_SYS_CHNG_DIR_ENUM
{

    NAS_LMM_SUS_SYS_CHNG_DIR_L2W            = 0x00000000,
    NAS_LMM_SUS_SYS_CHNG_DIR_L2G,
    NAS_LMM_SUS_SYS_CHNG_DIR_L2C,

    NAS_LMM_SUS_SYS_CHNG_DIR_BUTT
};
typedef VOS_UINT32 NAS_LMM_SUS_SYS_CHNG_DIR_ENUM_UINT32;


/*****************************************************************************
 �ṹ����:  NAS_LMM_SYS_CHNG_DIR_ENUM
 Э����:
 ASN.1 ����:
 �ṹ˵��:
*****************************************************************************/
enum    NAS_LMM_RSM_SYS_CHNG_DIR_ENUM
{

    NAS_LMM_RSM_SYS_CHNG_DIR_W2L            = 0x00000000,
    NAS_LMM_RSM_SYS_CHNG_DIR_G2L,

    NAS_LMM_RSM_SYS_CHNG_DIR_BUTT
};
typedef VOS_UINT32  NAS_LMM_RSM_SYS_CHNG_DIR_ENUM_UINT32;



/*****************************************************************************
 �ṹ����:NAS_LMM_SYS_CHNG_TYPE_ENUM
 Э����:
 ASN.1 ����:
 �ṹ˵��:ϵͳ���������
*****************************************************************************/
enum    NAS_LMM_SYS_CHNG_TYPE_ENUM
{

    NAS_LMM_SYS_CHNG_TYPE_RSL                = 0x00000000,
    NAS_LMM_SYS_CHNG_TYPE_HO ,
    NAS_LMM_SYS_CHNG_TYPE_CCO ,
    NAS_LMM_SYS_CHNG_TYPE_REDIR ,

    /* ϵͳ���ˣ���ֻ��LRRC_LMM_RESUME_IND��ʹ�� */
    NAS_LMM_SYS_CHNG_TYPE_REVERSE_RSL,
    NAS_LMM_SYS_CHNG_TYPE_REVERSE_HO,
    NAS_LMM_SYS_CHNG_TYPE_REVERSE_CCO,
    NAS_LMM_SYS_CHNG_TYPE_REVERSE_REDIR,

    NAS_LMM_SYS_CHNG_TYPE_BUTT
};
typedef VOS_UINT32 NAS_LMM_SYS_CHNG_TYPE_ENUM_UINT32;



/*****************************************************************************
 �ṹ����:NAS_LMM_SUS_CAUSE_ENUM
 Э����:
 ASN.1 ����:
 �ṹ˵��:LRRC֪ͨNAS�����ԭ��
*****************************************************************************/
enum    NAS_LMM_SUS_CAUSE_ENUM
{

    NAS_LMM_SUS_CAUSE_CSFB                = 0x00000000,

    /* ����CSFB���µĹ��������BUTTֵ */
    NAS_LMM_SUS_CAUSE_BUTT
};
typedef VOS_UINT32 NAS_LMM_SUS_CAUSE_ENUM_UINT32;



/*****************************************************************************
 �ṹ����:NAS_LMM_SYS_CHNG_ORI_ENUM
 Э����:
 ASN.1 ����:
 �ṹ˵��:
*****************************************************************************/
enum    NAS_LMM_SYS_CHNG_ORI_ENUM
{

    NAS_LMM_SYS_CHNG_ORI_MMC                = 0x00000000,
    NAS_LMM_SYS_CHNG_ORI_LRRC,

    NAS_LMM_SYS_CHNG_ORI_BUTT
};
typedef VOS_UINT32 NAS_LMM_SYS_CHNG_ORI_ENUM_UINT32;



enum    NAS_LMM_GU_ACTION_TYPE_ENUM
{
    MMC_LMM_GU_ACTION_ATTACH              = 0x00000000,
    MMC_LMM_GU_ACTION_RAU                  ,
    MMC_LMM_GU_ACTION_LAU                  ,
    MMC_LMM_GU_ACTION_PS_SERVICE_REQ       ,
    MMC_LMM_GU_ACTION_DETACH               ,
    MMC_LMM_GU_ACTION_CM_REQ               ,
    MMC_LMM_GU_ACTION_TYPE_BUTT
};
typedef VOS_UINT32 NAS_LMM_GU_ACTION_TYPE_ENUM_UINT32;



enum    NAS_LMM_GU_ACTION_RSLT_TYPE_ENUM
{
    MMC_LMM_GU_RSLT_TYPE_SUCCESS                     = 0,
    MMC_LMM_GU_RSLT_TYPE_FAILURE,                                                  /*ʧ�ܰ�������ܾ�������Ӧ*/
    MMC_LMM_GU_RSLT_TYPE_CN_REJ,
    MMC_LMM_GU_RSLT_TYPE_AUTH_REJ,                                                 /* ��Ȩ���� */
    MMC_LMM_GU_RSLT_TYPE_BUTT
};
typedef VOS_UINT32 NAS_LMM_GU_ACTION_RSLT_TYPE_ENUM_UINT32;


enum NAS_LMM_GU_DOMAIN_ENUM
{
    MMC_LMM_GU_PS_ONLY                     = 0x00000000,                           /*��ǰRAU/Attach����ΪPS only  */
    MMC_LMM_GU_IMSI_ONLY,                                                          /*��ǰ ����ΪCS only  */
    MMC_LMM_GU_COMBINED_PS_IMSI ,                                                  /*��ǰ ����Ϊ���ϴ���  */

    MMC_LMM_GU_DOMAIN_BUTT
};
typedef VOS_UINT32 NAS_LMM_GU_DOMAIN_ENUM_UINT32;

enum NAS_LMM_MT_DETACH_TYPE_ENUM
{
    MMC_LMM_GU_MT_DET_REATTACH_REQUIRED                = 1,
    MMC_LMM_GU_MT_DET_REATTACH_NOT_REQUIRED            = 2,
    MMC_LMM_GU_MT_DET_IMSI                             = 3,

    MMC_LMM_GU_MT_DETACH_TYPE_BUTT
};
typedef VOS_UINT32 NAS_LMM_MT_DETACH_TYPE_ENUM_UINT32;

/*leili modify for isr begin*/
/*****************************************************************************
 �ṹ����:NAS_EMM_CCO_CHANGE_TIN_FLAG_ENUM
 Э����:
 ASN.1 ����:
 �ṹ˵��: ����CCO���̵��¸���TINֵ��ʶ
*****************************************************************************/

enum NAS_EMM_CCO_CHANGE_TIN_FLAG_ENUM
{
    NAS_EMM_CCO_CHANGE_TIN_INVALID        = 0,
    NAS_EMM_CCO_CHANGE_TIN_VALID,
    NAS_EMM_CCO_CHANGE_TIN_BUTT,
};
typedef VOS_UINT32 NAS_EMM_CCO_CHANGE_TIN_FLAG_ENUM_UINT32;

/*leili modify for isr end*/
/*****************************************************************************
 �ṹ����: NAS_LMM_HO_SECU_PARA_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��:
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucHoSecuPara;
    VOS_UINT8                           aucRsv[3];
} NAS_LMM_HO_SECU_PARA_STRU;


/*****************************************************************************
 �ṹ����: NAS_LMM_SYS_CHNG_CTRL_STRU
 Э����:
 ASN.1����:
 �ṹ˵�� :
*****************************************************************************/
typedef struct
{
    NAS_LMM_SYS_CHNG_ORI_ENUM_UINT32        ulSusOri;       /* ����ķ�Դ�� */
    NAS_LMM_SYS_CHNG_ORI_ENUM_UINT32        ulRsmOri;       /* �ָ��ķ�Դ�� */

    NAS_LMM_SUS_SYS_CHNG_DIR_ENUM_UINT32    ulSusDir;       /* RRC����ķ��� */
    NAS_LMM_RSM_SYS_CHNG_DIR_ENUM_UINT32    ulRsmDir;       /* RRC�ָ��ķ��� */

    NAS_LMM_SYS_CHNG_TYPE_ENUM_UINT32       ulSusType;      /* RRC��������� */
    NAS_LMM_SYS_CHNG_TYPE_ENUM_UINT32       ulRsmType;      /* RRC�ָ������� */

    NAS_LMM_SUS_CAUSE_ENUM_UINT32           ulSusCause;     /* RRC�����ԭ��: ��CSFB */

    /*LRRC_LMM_SUSPEND_IND��Ϣ��Я����HoSecuPra*/
    NAS_LMM_HO_SECU_PARA_STRU               stHoSecuPara;

    /* ����ǰ��״̬ */
    NAS_LMM_FSM_STATE_STRU                   stStateBeforeSuspend;

    /* �ָ�ǰ��״̬ */
    NAS_LMM_FSM_STATE_STRU                   stStateBeforeResume;

    VOS_UINT32                              ulUpLayerCount; /* ֪ͨ�߲�ļ����� */

}NAS_LMM_SYS_CHNG_CTRL_STRU;
typedef struct
{
    VOS_UINT32                          bitOpGuReqDomain  : 1;
    VOS_UINT32                          bitOpGuRstDomain  : 1;
    VOS_UINT32                          bitOpGuMtDetachType:1;
    VOS_UINT32                          bitOpGuCnCause    : 1;
    VOS_UINT32                          bitOpGuAtmpCnt    : 1;
    VOS_UINT32                          bitSpare          : 27;
    /* ��������*/
    NAS_LMM_GU_ACTION_TYPE_ENUM_UINT32              ulGuActionType;

    /* CN_ACCEPT, CN_REJECT��������������Ӧ�Ľ�� */
    NAS_LMM_GU_ACTION_RSLT_TYPE_ENUM_UINT32         ulGuActRst;


    /* ����ҵ��ʱ������:��ATTACH, RAU, DETACHʱ��Ч */
    NAS_LMM_GU_DOMAIN_ENUM_UINT32                   ulGuActReqDomain;

    /* ��������ͣ���ATTACH, TAU, DETACHʱ��Ч��������Ӧ�Ľ�� */
    NAS_LMM_GU_DOMAIN_ENUM_UINT32                   ulGuActRstDomain;

    /*  �� MT DETACHʱ��Ч */
    NAS_LMM_MT_DETACH_TYPE_ENUM_UINT32              ulGuMtDetachType;

    /* �����·���ԭ�� */
    NAS_EMM_CN_CAUSE_ENUM_UINT8                     ucCnCause;

    VOS_UINT8                                       aucRsv1[3];

    /* ATTACH��RAUʧ�ܳ��Դ��� */
    VOS_UINT32                                      ulAttemptCount;
}NAS_LMM_GU_ACT_RST_STRU;


/*****************************************************************************
 �ṹ����: NAS_LMM_EMERGENCY_NUM_LIST
 Э����:
 ASN.1����:
 �ṹ˵�� :See subclause 10.5.3.13 in 3GPP TS 24.008

        8       7       6       5       4       3       2       1
    ������������������������������������������������������������������
    ��                 Emergency Number List IEI                    ��Octet 1
    ������������������������������������������������������������������
    ��    Length of Emergency Number List IE contents               ��Octet 2
    ������������������������������������������������������������������
    ��    Length of 1st Emergency Number information note 1)        ��Octet 3
    ������������������������������������������������������������������
    ��              spare   ��   mergency Service Category Value    ��
    ��                      ��(see Table 10.5.135d/3GPP TS 24.008)) ��Octet 4
    ������������������������������������������������������������������
    ��    Number digit 2    ��          Number digit 1              ��Octet 5
    ������������������������������������������������������������������
    ��    Number digit 4    ��          Number digit 3              ��Octet 6*
    ������������������������������������������������������������������
    ��                    ...                                       ��
    ������������������������������������������������������������������
    ��                                                              ��Octet j-1*
    ������������������������������������������������������������������
    ��      Length of 2nd Emergency Number information note 1)      ��Octet j*
    ������������������������������������������������������������������
    ��              spare   ��   mergency Service Category Value    ��
    ��                      ��(see Table 10.5.135d/3GPP TS 24.008)) ��Octet j+1*
    ������������������������������������������������������������������
    ��    Number digit 2    ��          Number digit 1              ��Octet j+2*
    ������������������������������������������������������������������
    ��    Number digit 4    ��          Number digit 3              ��Octet j+3*
    ������������������������������������������������������������������
    ��                    ...                                       ��
    ������������������������������������������������������������������
    ��                                                              ��Octet n*
    ������������������������������������������������������������������
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEmergencyNumAmount;
    VOS_UINT8                           aucReserved[3];
    LMM_MM_EMERGENCY_NUM_STRU           astEmergencyNumList[MM_LMM_EMERGENCY_NUM_LIST_MAX_RECORDS];
}NAS_LMM_EMERGENCY_NUM_LIST_STRU;

/*****************************************************************************
 �ṹ����: NAS_EMM_REJ_RECODE_STRU
 Э����:
 ASN.1����:
 �ṹ˵�� :UE���ܼ�¼
*****************************************************************************/
typedef struct
{
    NAS_EMM_REJ_FLAG_ENUM_UINT32        enRejCause2Flag;
    NAS_EMM_REJ_FLAG_ENUM_UINT32        enRejCause18Flag;
} NAS_EMM_REJ_RECODE_STRU;
/*****************************************************************************
 �ṹ����: NAS_EMM_TRIGGER_TAU_FLAG_STRU
 Э����:
 ASN.1����:
 �ṹ˵�� :����TAU���
*****************************************************************************/
typedef struct
{
    GMM_LMM_GPRS_MM_STATE_ENUM_UINT32            enGprsMmState;
    GMM_LMM_PACKET_MM_STATE_ENUM_UINT32          enPacketMmState;
    GMM_LMM_GPRS_SUSPENSION_STATE_ENUM_UINT32    enGprsSuspensionState;
    NAS_EMM_LAU_OR_COMBINED_RAU_FLAG_ENUM_UINT32 enLauOrCombinedRauFlag;
    NAS_EMM_T3412_EXP_ENUM_UINT32                enEmmT3412ExpCtrl;      /*T3412��ʱ��Ϣ�Ƿ�ʱ*/
    VOS_UINT32                                   ulEmmDrxNetCapChange;   /*ָʾDrx��NetCapability�ı�*/
    NAS_EMM_TRIGGER_TAU_RRC_REL_ENUM_UINT32      enTriggerTauRrcRel;     /*RRC����ɾ��ԭ���Ƿ��ܹ�����TAU*/
    VOS_UINT32                                   ulTriggerTauSysChange;  /*ָʾϵͳ�任�ܷ񴥷�TAU*/
    /*leili modify for isr begin*/
    NAS_EMM_EPS_BEARER_CONTEXT_STATUS_ENUM_UINT32   enStatusChange;
    /*leili modify for isr end*/
    NAS_EMM_SRVCC_FLAG_ENUM_UINT32                enSrvccFlag;

    VOS_UINT32                                  ulVoiceDomainChange;    /* voice domain�����仯����Ҫ����TAU */
    VOS_UINT8                                   ucLaiChangeFlag;        /* LAI�����仯 */
    VOS_UINT8                                   ucEmcConnExitFlag;      /* �����˽������� */
    VOS_UINT8                                   aucRsv[2];
} NAS_EMM_TRIGGER_TAU_FLAG_STRU;

/*leili modify for isr begin*/
/*****************************************************************************
 �ṹ����: NAS_EMM_TRIGGER_TAU_FLAG_STRU
 Э����:
 ASN.1����:
 �ṹ˵�� :����TAU���
*****************************************************************************/
typedef struct
{
    NAS_EMM_CCO_CHANGE_TIN_FLAG_ENUM_UINT32     ulTinChagFlag;
    MMC_LMM_TIN_TYPE_ENUM_UINT32                ulTinType;
} MMC_LMM_CCO_FLAG_STRU;
/*leili modify for isr end*/
/*****************************************************************************
 �ṹ��    : NAS_LMM_SYSCFG_CTRL_STRU
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    NAS_LMM_UE_RADIO_CAP_CHANGE_ENUM_UINT32                   enRadioAccCapChgFlag;
    NAS_LMM_SYSCFG_FLAG_ENUM_UINT32                           enSyscfgFlag;
}NAS_LMM_SYSCFG_CTRL_STRU;

/*****************************************************************************
�ṹ����    :LNAS_LMM_ATT_REQUIRE_PARA_STRU
ʹ��˵��    :AT&T��������EMMά�������ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                    ulCServiceMax;       /* NV�е�ֵ����Ч��Χ1-60��Ĭ��ֵ5 */
    VOS_UINT32                    ulCServiceCount;     /* EMM����ά��CService����         */
    VOS_UINT32                    ulT3402Len;          /* EMM����ά��T3402ʱ��            */
    NAS_DAM_CONFIG_PLMN_PARA      stDamConfigPlmnPara; /* DAM������Ч��PLMN�б�           */
} LNAS_LMM_DAM_PARA_STRU;


/*****************************************************************************
 ö����    : NAS_EMM_SUSPEND_CAUSE_ENUM
 ö��˵��  : ��ʶ������REG+NORMAL_SERVICEʱ���Ƿ���Ҫ��Ϊ����REG+ATTEMPT_TO_UPDATE_MM
*****************************************************************************/
enum  NAS_EMM_SUSPEND_REL_CAUSE_ENUM
{
    NAS_EMM_SUSPEND_REL_CAUSE_MMC_ORI       = 1,
    NAS_EMM_SUSPEND_REL_CAUSE_ABORT_CSFB    = 2,

    NAS_EMM_SUSPEND_REL_CAUSE_BUTT
};
typedef VOS_UINT32   NAS_EMM_SUSPEND_REL_CAUSE_ENUM_UINT32;


/*****************************************************************************
�ṹ����    :NAS_EMM_PUB_INFO_STRU
ʹ��˵��    :MM�Ĺ�����Ϣ
             bitOp**����ʶ��Ӧ����Ϣ�Ƿ���Ч��ȡֵ����������:
             #define NAS_EMM_BIT_SLCT      1 :      VALID
             #define NAS_EMM_BIT_NO_SLCT   0 :      INVALID
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpUeId           :1;
    VOS_UINT32                          bitOpNetInfo        :1;
    VOS_UINT32                          bitOpDrx            :1;
    VOS_UINT32                          bitOpUeNetCap       :1;
    VOS_UINT32                          bitOpMsNetCap       :1;
    VOS_UINT32                          bitOpSupCodecList   :1;
    VOS_UINT32                          bitOpRaMod          :1;
    VOS_UINT32                          bitOpAppPara        :1;
    VOS_UINT32                          bitOpUeMode         :1;
    VOS_UINT32                          bitOpCsService      :1;
    VOS_UINT32                          bitOpVoiceDomain    :1;
    VOS_UINT32                          bitOpEmgList        :1;
    VOS_UINT32                          bitOpNetFeature     :1;
    VOS_UINT32                          bitOpRsv            :19;

    NAS_LMM_UEID_STRU                   stMmUeId;
    NAS_LMM_NETWORK_INFO_STRU           stNetInfo;
    NAS_MM_DRX_STRU                     stDrx;
    NAS_MM_UE_NET_CAP_STRU              stUeNetCap;
    NAS_MM_MS_NET_CAP_STRU              stMsNetCap;
    /*leili modify for isr begin*/
    /*NAS_LMM_EPS_BEARER_CONTEXT_STRU     stEpsBearerCxt;*/
    /*leili modify for isr end*/

    NAS_LMM_CODEC_LIST_STRU             stSupCodecList;
    NAS_EMM_RAT_TYPE_ENUM_UINT32        enRaMod;    /* V7R1ֻ������LTE��TDD��FDD */
    NAS_LMM_APP_PARA_STRU               stAppPara;
    NAS_EMM_INFO_STRU                   stEmmInfoPara;
    NAS_EMM_CN_MSG_TYPE_ENUM_UINT8      enLastAirMsgType;
    VOS_UINT8                           ucIsMsgIntegrityFlag; /* ��Ϣ�Ƿ��������Ա����ı�ʶ��VOS_TRUE:�������Ա����ģ�VOS_FALSE:���� */
    VOS_UINT8                           ucTmoUsimCardFlag; /* ���������NV��IMSIȷ���Ƿ���TMO���ı�ʶ */
    VOS_UINT8                           aucRsv[1];
    NAS_LMM_SIM_STAT_ENUM_UINT32        ulSimStat;
    NAS_LMM_SIM_VALIDITY_ENUM_UINT32    enPsSimValidity;
    NAS_EMM_START_INFO_STRU             stEmmStartInfo;

    NAS_LMM_SYS_CHNG_CTRL_STRU          stSysChngCtrl;
    NAS_LMM_GU_ACT_RST_STRU             stLmmGuActRst;/*����GU ACT RESULT*/

    NAS_LMM_GU_UE_MODE_ENUM_UINT32              ulGuUeMode;
    NAS_LMM_UE_OPERATION_MODE_ENUM_UINT32       ulLteUeMode;
    NAS_EMM_USAGE_SETTING_UINT32                ulUsageSetting;
    NAS_LMM_CS_SERVICE_ENUM_UINT32              ulCsService;


    NAS_LMM_SUP_ENUM_UINT32                     aulLmmSupVoiceDomain[NAS_LMM_SUP_VOICE_DOMAIN_BUTT]; /* UE ֧����Щ������ */
    NAS_LMM_VOICE_DOMAIN_ENUM_UINT32            ulVoiceDomain;    /*Voice domain preference for E-UTRAN*/

    NAS_LMM_SUP_ENUM_UINT32                     aulLmmSupSmsDomain[NAS_LMM_SUP_SMS_DOMAIN_BUTT]; /* UE ֧����ЩSMS�� */
    NAS_LMM_SUP_SMS_DOMAIN_ENUM_UINT32          ulSmsDomainPrefer;  /* UE ѡ������ʹ���ĸ���ִ��SMSҵ�� */

    NAS_LMM_SUP_ENUM_UINT32                     ulLmmSupIms;    /* UE LMM�Ƿ�֧��IMS������ IMS voice not available */
    /*NAS_LMM_SUP_ENUM_UINT32                     ulCSFBAvail;   */ /*"CS fallback is not available" includes EMM causes #16, #17, #18 and #22*/

    NAS_LMM_EMERGENCY_NUM_LIST_STRU             stEmergencyNumList;

    MMC_LMM_UTRAN_MODE_ENUM_UINT8               enUtranMode;
    VOS_UINT8                                   ucNetFeature;   /* ��ǰ�����Ƿ�֧��IMS */
    /* �ػ���ʶ,�ṩ��LRRC,����LRRC�жϿտ��Ƿ��ǹػ�detach,��lmm�յ�mmc�Ĺػ�����ʱ��Ϊ1�����յ�LRRC�ػ��ظ����ȴ�LRRC�ػ��ظ���ʱ���߿���ʱ��� */
    VOS_UINT8                                   ucLtePowerOffFlag;

    NAS_EMM_T3402_SRC_ENUM_UINT8                enT3402Src;

    /* lihong00150010 ims begin */
    NAS_LMM_ADDITIONAL_UPDATE_RSLT_ENUM_UINT32  enAdditionUpRslt;
    /* lihong00150010 ims end */
    NAS_LMM_REG_DOMAIN_ENUM_UINT32              enRegisteredDomain;
    NAS_EMM_FIRST_TAU_FLAG_ENUM_UINT32          enFirstTauFlag;          /* 0��ʾ��GUע��ɹ���ĵ�һ��TAU��1��ʾGUע��ɹ���ĵ�һ��TAU */
    /* LRRC��SYSCFG ����֪ͨ������ */
    NAS_LMM_SUSPEND_TYPE_NOTIFY_ENUM_UINT32     ulRrcSysCfgSusType;
    NAS_LMM_CONNECTION_CLIENT_ID_ENUM_UINT32     enNasConnectionClientId;
    NAS_EMM_REJ_RECODE_STRU                     stRejRecord;
    NAS_LMM_LTE_ENABLE_STA_ENUM_UINT32          enLteEnableSta; /*��ʶE-UNTRA�Ƿ�ʹ��*/
    NAS_EMM_UPDATE_MM_FLAG_ENUM_UINT32          enUpdateMmFlag;         /* ��ʶ������REG+NORMAL_SERVICEʱ���Ƿ���Ҫ��Ϊ����REG+ATTEMPT_TO_UPDATE_MM */
    VOS_UINT32                                  ulPlmnSrchNoImsiFlag ;

    NAS_LMM_SYSCFG_CTRL_STRU                    stSyscfgCtrl;
    NAS_EMM_TRIGGER_TAU_FLAG_STRU               stTriggerTauFlag;

    MMC_LMM_ATT_REASON_ENUM_UINT32              enMmcAttachReason;  /* MMCָ����ATTACHԭ����CL��ģ���������˱��� */
    /* �����ϴ�д����дNV��EPS LOC���� */
    VOS_UINT8        aucLastWriteUsimPsLoc[NAS_EMM_EPS_LOC_MAX_LEN];

    /*leili modify for isr begin*/
    MMC_LMM_CCO_FLAG_STRU                       stCcoFlag;
    /*leili modify for isr end*/

    NAS_LMM_REG_STATUS_ENUM_UINT32              enRegStatus;        /* ��ʶע��״̬ */
    VOS_UINT32                                  ulIsEmerPndEsting;  /* ��ʶ�Ƿ����ڽ���PDN������0��ʾ���ڽ��У�1��ʾ���ڽ��� */
    VOS_UINT8                                  *pucEsmMsg;          /* ���ڴ洢�������͵�PDN�����Լ�OPID */
    /*VOS_UINT8                                   aucRsv2[3];*/
    GMM_LMM_TIMER_STATE_ENUM_UINT32             enT3312State;
    VOS_UINT32                                  ulNasRelease;

    NAS_EMM_SUSPEND_REL_CAUSE_ENUM_UINT32       ulSuspendRelCause;  /* ֹͣ�������̵�ԭ�� */

    MMC_LMM_IMS_VOICE_CAP_ENUM_UINT8            enImsaVoiceCap;     /*IMS voice capability*/
    /*self-adaption NW cause modify begin for leili*/
    LNAS_LMM_CONFIG_NWCAUSE_STRU                stConfCause;
    /*self-adaption NW cause modify end for leili*/

    NAS_EMM_DSDS_TAU_TYPE_ENUM_UINT32          enDsdsTauType;

    LNAS_LMM_DAM_PARA_STRU                      stDamPara;           /* ������ĿDAM���� */
    VOS_UINT32                                  ulRej19AtmptCntFlag; /* NV�����õ�ATTACH�յ�REJ#19ʱ�ɳ��Դ�����ʶ */

}NAS_LMM_PUB_INFO_STRU;
typedef NAS_LMM_PUB_INFO_STRU            NAS_EMM_PUB_INFO_STRU;
typedef NAS_LMM_PUB_INFO_STRU            NAS_MMC_PUB_INFO_STRU;
/*PC REPLAY MODIFY BY LEILI DELETE*/


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

#endif /* end of NasLmmCore.h*/
