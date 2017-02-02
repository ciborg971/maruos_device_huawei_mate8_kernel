

#ifndef _NASEMMPUBUCNMSGDECODE_H
#define _NASEMMPUBUCNMSGDECODE_H


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include    "vos.h"
#include    "NasEmmPubUGlobal.h"
#include    "NasEmmIdenPubInterface.h"

#include    "LRrcLNasInterface.h"

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
#define NAS_EMM_NULL                    0


#define NAS_EMM_CN_MSG_HEADER           VOS_UINT8        ucPd;\
                                        VOS_UINT8        ucSecurityHeadType;\
                                        VOS_UINT8        ucMt;\
                                        VOS_UINT8        ucRsv;
#define NAS_EMM_CN_MSG_TYPE             NAS_EMM_CN_MSG_TYPE_ENUM_UINT8      ulCnMsgType;\
                                        VOS_UINT8                           aucRsv[3];
/*��Ϣ��ԪIEI����*/
#define NAS_EMM_MSG_TAI_IEI             0x54   /*��Ҫ�����������ȷ��һ��ֵ
 */
#define NAS_EMM_MSG_GUTI_IEI            0x50
#define NAS_EMM_MSG_MSID_IEI            0x23
#define NAS_EMM_MSG_LAI_IEI             0x13
#define NAS_EMM_MSG_T3402_2_IEI         0x16    //GPRS timer2 9.9.3.16A
#define NAS_EMM_MSG_T3402_IEI           0x17
#define NAS_EMM_MSG_T3423_IEI           0x59
#define NAS_EMM_MSG_T3412_IEI           0x5A
#define NAS_EMM_MSG_T3442_IEI           0x5B
#define NAS_EMM_MSG_PLMNLIST_IEI        0x4A
#define NAS_EMM_MSG_EMERGENCYLIST_IEI   0x34
#define NAS_EMM_MSG_EPSNETFEATURE_IEI   0x64
#define NAS_EMM_MSG_UPDATERSLT_IEI      0xF0
#define NAS_EMM_MSG_CON_IEI             0x78
#define NAS_EMM_MSG_EMMCAU_IEI          0x53
#define NAS_EMM_MSG_EPSBTXT_STUS_IEI    0x57
#define NAS_EMM_MSG_KSI_IMEISV_IEI      0xC
#define NAS_EMM_MSG_T3346_IEI           0x5F
#define NAS_EMM_MSG_EXTENDED_EMM_CAUSE  0xA0
#define NAS_EMM_EUTRAN_NOT_ALLOWED      1
#define NAS_EMM_EUTRAN_ALLOWED          0
#define NAS_EMM_MSG_EXT_3402_IEI        0x16


#define NAS_EMM_MSG_SEC_TYPE_NAS        0x01
#define NAS_EMM_MSG_SEC_TYPE_SERREQ     0x0C


#define NAS_EMM_CN_MSG_MAX_SIZE         1024
#define NAS_EMM_CN_ATT_RST_VAL_MAX      0x02
#define NAS_EMM_CN_TAU_RST_VAL_MAX      0x04

#define NAS_EMM_CN_MAX_TAI_LIST_LEN     96
#define NAS_EMM_CN_MIN_TAI_LIST_LEN     6

#define NAS_EMM_CN_HIGH_4_BIT           0xF0
#define NAS_EMM_CN_HIGH_3_BIT           0xE0
#define NAS_EMM_CN_LOW_3_BIT            0x07
#define NAS_EMM_CN_LOW_5_BIT            0x1F
#define NAS_EMM_MOVEMENT_5_BITS         5


#define NAS_EMM_TA_MAX_TAC_MUN          16

#define NAS_EMM_CN_GUTI_MAX_LEN         11

#define NAS_EMM_CN_EPS_TYPE_IMSI        0x01
#define NAS_EMM_CN_EPS_TYPE_GUTI        0x06

#define NAS_EMM_TA_LIST_0               0x00
#define NAS_EMM_TA_LIST_1               0x01
#define NAS_EMM_TA_LIST_2               0x02

#define NAS_EMM_CN_LAI_LEN              5

#define NAS_EMM_CN_MSID_MIN_LEN         5
#define NAS_EMM_CN_MSID_MAX_LEN         8

#define NAS_EMM_CN_PLMNLIST_MIN_LEN     3
#define NAS_EMM_CN_PLMNLIST_MAX_LEN     45

#define NAS_EMM_CN_EMERGENCYLIST_MIN_LEN     3
#define NAS_EMM_CN_EMERGENCYLIST_MAX_LEN     48

#define NAS_EMM_CN_EPS_NET_FEATURE_LEN       1


#define NAS_EMM_CN_MSGCON_MAX_LEN       LRRC_LNAS_MAX_DATA_LENGTH

#define NAS_EMM_CN_MSID_IMSI            0x01
#define NAS_EMM_CN_MSID_IMEI            0x02
#define NAS_EMM_CN_MSID_IMEISV          0x03
#define NAS_EMM_CN_MSID_TMSI_PTMSI      0x04
#define NAS_EMM_CN_MSID_TMGI_MBMS       0x05

#define NAS_EMM_CN_TMGI_PLMN_SLCT       0x10
#define NAS_EMM_CN_TMGI_MBMS_SEC_SLCT   0x20

#define NAS_EMM_CN_UEID_IMEI_SIZE       8
#define NAS_EMM_CN_UEID_IMEISV_SIZE     8
#define NAS_EMM_CN_UEID_IMSI_SIZE       8
#define NAS_EMM_CN_UEID_TMSI_SIZE       4
#define NAS_EMM_CN_UEID_TMGI_SIZE       6

#define NAS_EMM_TIMEZONE_LEN            2
#define NAS_EMM_TIME_TIMEZONE_LEN       8
#define NAS_EMM_DAYLIGHTTIME            3
#define NAS_EMM_CODESCHM_RESERVED       2

#define NAS_EMM_IE_L_LENGTH             1

#define NAS_EMM_RAND_LEN                16
#define NAS_EMM_AUTN_LEN                16

#define NAS_EMM_IE_NAME_LEN                   20
#define NAS_EMM_DECODE_OCTET_USE_8_BITS       0xFF
#define NAS_EMM_DECODE_OCTET_USE_HIGH_4_BITS  0xF0
#define NAS_EMM_DECODE_OCTET_USE_LOW_4_BITS   0x0F
#define NAS_EMM_DECODE_IE_M                   1      /*��ѡ��Ԫ      */
#define NAS_EMM_DECODE_IE_O                   0      /*��ѡ��Ԫ      */
#define NAS_EMM_MSG_RESERVE_IEI               0xFF   /*Ԥ��ֵ����Ԫ  */
#define NAS_EMM_MSG_IE_OPT_BITS               32

#define NAS_EMM_CN_FULL_NAME            0x43
#define NAS_EMM_CN_SHORT_NAME           0x45
#define NAS_EMM_LOCAL_TIME_ZONE         0x46
#define NAS_EMM_UNIVTIME_LOCALTIMEZONE  0x47
#define NAS_EMM_CN_DAYLIGHT_SAVE_TIME   0x49

#define NAS_EMM_DOWNLINK_NAS_TRANSPORT_MAX_LEN 251

#define NAS_EMM_CLI_MIN_LEN             (1)
#define NAS_EMM_CLI_MAX_LEN             (12)
#define NAS_EMM_LCS_CLIENT_ID_MIN_LEN   (1)
#define NAS_EMM_LCS_CLIENT_ID_MAX_LEN   (255)
#define NAS_EMM_MSG_CLI_IEI             (0x60)
#define NAS_EMM_MSG_SS_CODE_IEI         (0x61)
#define NAS_EMM_MSG_LCS_INDICATOR_IEI   (0x62)
#define NAS_EMM_MSG_LCS_CLIENT_ID_IEI   (0x63)

#define NAS_EMM_ADDITIONAL_INFO_IEI     (0x65)
#define NAS_EMM_LPP_MSG                 (0x01)
#define NAS_EMM_LCS_MSG                 (0x02)
/*lint -e961*/
#define NAS_EMM_DECODE_LOCAL_TIME(ucTime) ((VOS_UINT8)((ucTime)& NAS_EMM_LOW_HALF_BYTE_F)*10 + (((ucTime) & NAS_EMM_HIGH_HALF_BYTE_F)>>NAS_EMM_MOVEMENT_4_BITS))
/*lint +e961*/
/*���ڳ�ʼ���ṹ��*/
#define NAS_EMM_DECODE_IE_ITEM(ucIEI,ucIEBits,ucIEBitsMove,ucIELen,\
                                                ucIEFormat,usIEStructSize,acIEName,\
                                                pfIEDecodeFun)\
                    {\
                        ucIEI,ucIEBits,ucIEBitsMove,ucIELen,NAS_EMM_NULL,ucIEFormat,\
                        usIEStructSize,acIEName,pfIEDecodeFun\
                    }

#define NAS_EMM_DECODE_MSG_IE_ITEM(stIEInfo,ucIEMust)\
                    {\
                        stIEInfo,{NAS_EMM_NULL},ucIEMust \
                    }

#define NAS_EMM_DECODE_MSG_ITEM(ucMsgType,pastMsgIETable,acMsgName)\
                                    {\
                                        {NAS_EMM_NULL},ucMsgType,\
                                        (sizeof(pastMsgIETable)/sizeof(NAS_EMM_DECODE_MSG_IE_INFO_STRU)),\
                                        pastMsgIETable,acMsgName\
                                    }

#define NAS_EMM_DECODE_MSG_FUN_ITEM(ucMsgType,pDecodeMsgFun)\
                                    {\
                                        {NAS_EMM_NULL},ucMsgType,\
                                        pDecodeMsgFun \
                                    }

/*��Ԫ�Ķ���,���Գ����Ż������ִ����Զ���Ϊ��*/
#define NAS_EMM_MSG_T3412_IE_ITEM \
NAS_EMM_DECODE_IE_ITEM(NAS_EMM_MSG_T3412_IEI,\
                            NAS_EMM_DECODE_OCTET_USE_8_BITS,\
                            NAS_EMM_AD_MOVEMENT_0_BIT,\
                            2,\
                            NAS_EMM_DECODE_IE_FORMAT_TV,\
                            sizeof(NAS_EMM_TIMER_STRU),\
                            "T3412_IE",\
                            NAS_EMM_DecodeTimer)

#define NAS_EMM_MSG_GUTI_IE_ITEM \
NAS_EMM_DECODE_IE_ITEM(NAS_EMM_MSG_GUTI_IEI,\
                            NAS_EMM_DECODE_OCTET_USE_8_BITS,\
                            NAS_EMM_AD_MOVEMENT_0_BIT,\
                            NAS_EMM_NULL,\
                            NAS_EMM_DECODE_IE_FORMAT_TLV,\
                            sizeof(NAS_EMM_GUTI_STRU),\
                            "GUTI_IE",\
                            NAS_EMM_DecodeGuti)
#define NAS_EMM_MSG_TAI_IE_ITEM \
NAS_EMM_DECODE_IE_ITEM(NAS_EMM_MSG_TAI_IEI,\
                            NAS_EMM_DECODE_OCTET_USE_8_BITS,\
                            NAS_EMM_AD_MOVEMENT_0_BIT,\
                            NAS_EMM_NULL,\
                            NAS_EMM_DECODE_IE_FORMAT_TLV,\
                            sizeof(NAS_EMM_TA_LIST_STRU),\
                            "TAI_IE",\
                            NAS_EMM_DecodeTai)

#define NAS_EMM_MSG_EPSBTXT_STUS_IE_ITEM \
NAS_EMM_DECODE_IE_ITEM(NAS_EMM_MSG_EPSBTXT_STUS_IEI,\
                            NAS_EMM_DECODE_OCTET_USE_8_BITS,\
                            NAS_EMM_AD_MOVEMENT_0_BIT,\
                            NAS_EMM_NULL,\
                            NAS_EMM_DECODE_IE_FORMAT_TLV,\
                            sizeof(NAS_EMM_EPS_BEARER_STATUS_STRU),\
                            "EPSBTXT_STUS_IE",\
                            NAS_EMM_DecodeBearerTxtStus)
#define NAS_EMM_MSG_LAI_IE_ITEM \
NAS_EMM_DECODE_IE_ITEM(NAS_EMM_MSG_LAI_IEI,\
                            NAS_EMM_DECODE_OCTET_USE_8_BITS,\
                            NAS_EMM_AD_MOVEMENT_0_BIT,\
                            6,\
                            NAS_EMM_DECODE_IE_FORMAT_TV,\
                            sizeof(NAS_EMM_LA_STRU),\
                            "LAI_IE",\
                            NAS_EMM_DecodeLai)

#define NAS_EMM_MSG_MSID_IE_ITEM \
NAS_EMM_DECODE_IE_ITEM(NAS_EMM_MSG_MSID_IEI,\
                            NAS_EMM_DECODE_OCTET_USE_8_BITS,\
                            NAS_EMM_AD_MOVEMENT_0_BIT,\
                            NAS_EMM_NULL,\
                            NAS_EMM_DECODE_IE_FORMAT_TLV,\
                            sizeof(NAS_EMM_MSID_STRU),\
                            "MSID_IE",\
                            NAS_EMM_DecodeMsId)
#define NAS_EMM_MSG_EMMCAU_IE_ITEM \
NAS_EMM_DECODE_IE_ITEM(NAS_EMM_MSG_EMMCAU_IEI,\
                            NAS_EMM_DECODE_OCTET_USE_8_BITS,\
                            NAS_EMM_AD_MOVEMENT_0_BIT,\
                            2,\
                            NAS_EMM_DECODE_IE_FORMAT_TV,\
                            sizeof(NAS_EMM_CN_CAUSE_ENUM_UINT8),\
                            "EMMCAU_IE",\
                            NAS_EMM_DecodeEmmCau)

#define NAS_EMM_MSG_T3402_IE_ITEM \
NAS_EMM_DECODE_IE_ITEM(NAS_EMM_MSG_T3402_IEI,\
                            NAS_EMM_DECODE_OCTET_USE_8_BITS,\
                            NAS_EMM_AD_MOVEMENT_0_BIT,\
                            2,\
                            NAS_EMM_DECODE_IE_FORMAT_TV,\
                            sizeof(NAS_EMM_TIMER_STRU),\
                            "T3402_IE",\
                            NAS_EMM_DecodeTimer)

#define NAS_EMM_MSG_T3423_IE_ITEM \
NAS_EMM_DECODE_IE_ITEM(NAS_EMM_MSG_T3423_IEI,\
                            NAS_EMM_DECODE_OCTET_USE_8_BITS,\
                            NAS_EMM_AD_MOVEMENT_0_BIT,\
                            2,\
                            NAS_EMM_DECODE_IE_FORMAT_TV,\
                            sizeof(NAS_EMM_TIMER_STRU),\
                            "T3423_IE",\
                            NAS_EMM_DecodeTimer)

#define NAS_EMM_MSG_PLMNLIST_IE_ITEM \
NAS_EMM_DECODE_IE_ITEM(NAS_EMM_MSG_PLMNLIST_IEI,\
                            NAS_EMM_DECODE_OCTET_USE_8_BITS,\
                            NAS_EMM_AD_MOVEMENT_0_BIT,\
                            NAS_EMM_NULL,\
                            NAS_EMM_DECODE_IE_FORMAT_TLV,\
                            sizeof(NAS_EMM_PLMN_LIST_STRU),\
                            "PLMNLIST_IE",\
                            NAS_EMM_DecodePlmnList)

#define NAS_EMM_MSG_EMERGENCYLIST_IE_ITEM \
NAS_EMM_DECODE_IE_ITEM(NAS_EMM_MSG_EMERGENCYLIST_IEI,\
                            NAS_EMM_DECODE_OCTET_USE_8_BITS,\
                            NAS_EMM_AD_MOVEMENT_0_BIT,\
                            NAS_EMM_NULL,\
                            NAS_EMM_DECODE_IE_FORMAT_TLV,\
                            sizeof(NAS_LMM_EMERGENCY_NUM_LIST_STRU),\
                            "EMERGENCYLIST_IE",\
                            NAS_EMM_DecodeEmergencyNumList)

#define NAS_EMM_MSG_EPSNETFEATURE_IE_ITEM \
NAS_EMM_DECODE_IE_ITEM(NAS_EMM_MSG_EPSNETFEATURE_IEI,\
                            NAS_EMM_DECODE_OCTET_USE_8_BITS,\
                            NAS_EMM_AD_MOVEMENT_0_BIT,\
                            NAS_EMM_NULL,\
                            NAS_EMM_DECODE_IE_FORMAT_TLV,\
                            sizeof(VOS_UINT8),\
                            "EPSNETFEATURE_IE",\
                            NAS_EMM_DecodeEpsNetFeatureSupport)

#define NAS_EMM_MSG_ESMMSGCON_IE_ITEM \
NAS_EMM_DECODE_IE_ITEM(NAS_EMM_MSG_CON_IEI,\
                            NAS_EMM_DECODE_OCTET_USE_8_BITS,\
                            NAS_EMM_AD_MOVEMENT_0_BIT,\
                            NAS_EMM_NULL,\
                            NAS_EMM_DECODE_IE_FORMAT_TLV_E,\
                            sizeof(NAS_EMM_CN_MSGCON_STRU),\
                            "ESM_MSG_CONN_IE",\
                            NAS_EMM_DecodeEsmMsgCon)

#define NAS_EMM_MSG_T3402_2_IE_ITEM \
NAS_EMM_DECODE_IE_ITEM(NAS_EMM_MSG_T3402_2_IEI,\
                            NAS_EMM_DECODE_OCTET_USE_8_BITS,\
                            NAS_EMM_AD_MOVEMENT_0_BIT,\
                            NAS_EMM_NULL,\
                            NAS_EMM_DECODE_IE_FORMAT_TLV,\
                            sizeof(NAS_EMM_TIMER_STRU),\
                            "T3402_2_IE",\
                            NAS_EMM_DecodeTimer2)


#define NAS_EMM_MSG_UPDTAERSLT_IE_ITEM \
NAS_EMM_DECODE_IE_ITEM(NAS_EMM_MSG_UPDATERSLT_IEI,\
                            NAS_EMM_DECODE_OCTET_USE_HIGH_4_BITS,\
                            NAS_EMM_AD_MOVEMENT_0_BIT,\
                            1,\
                            NAS_EMM_DECODE_IE_FORMAT_TV,\
                            sizeof(NAS_LMM_ADDITIONAL_UPDATE_RSLT_ENUM_UINT32),\
                            "UPDATERSLT_IE",\
                            NAS_EMM_DecodeAdditionalUpdateRslt)


#define NAS_EMM_MSG_KSI_IE_ITEM \
NAS_EMM_DECODE_IE_ITEM(NAS_EMM_MSG_KSI_IMEISV_IEI,\
                            NAS_EMM_DECODE_OCTET_USE_HIGH_4_BITS,\
                            NAS_EMM_AD_MOVEMENT_4_BITS,\
                            1,\
                            NAS_EMM_DECODE_IE_FORMAT_TV,\
                            sizeof(NAS_EMM_CN_KSIASME_UINT8),\
                            "KSIasme",\
                            NAS_EMM_DecodeKSIasme)

/*����Ԫ����Ԥ�����ֽ�,��ԪID�Ļ�ȡ��ʽ�����˸���Ԫ��Զ������*/
#define NAS_EMM_MSG_AUCRESERVE_IE_ITEM(uclen) \
NAS_EMM_DECODE_IE_ITEM(NAS_EMM_MSG_RESERVE_IEI,\
                            NAS_EMM_DECODE_OCTET_USE_LOW_4_BITS,\
                            NAS_EMM_AD_MOVEMENT_0_BIT,\
                            NAS_EMM_NULL,\
                            NAS_EMM_DECODE_IE_FORMAT_TV,\
                            uclen,\
                            "RESERVE",\
                            NAS_EMM_NULL)



/*������Ϣ����*/
#define NAS_EMM_CN_TAU_ACP_STR      "MM_TAU_ACP"
#define NAS_EMM_CN_ATTACH_ACP_STR   "MM_ATTACH_ACP"

#define NAS_EMM_CN_ATTACH_REJ_STR   "MM_ATTACH_REJ"

#define NAS_EMM_DECODE_BUFFER_MSG_OPT(pstMsgStru) \
    (VOS_UINT32*)(((VOS_UINT8*)(pstMsgStru))+sizeof(NAS_EMM_DECODE_CN_MSG_HEADER_STRU));


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/



/*****************************************************************************
  4 Enum
*****************************************************************************/
/*��Ԫ���͵�ö�ٶ���*/
typedef VOS_UINT8 NAS_EMM_CN_KSIASME_UINT8;

/*****************************************************************************
�ṹ����    : NAS_EMM_EPS_UPDATE_RST_ENUM
ʹ��˵��    : TAU ACCEPT�е�EPS UPDATE RESULT��Ԫ
*****************************************************************************/
enum NAS_EMM_EPS_UPDATE_RST_ENUM
{
    NAS_EMM_EPS_UPDATE_RST_TA_UPDATED                       = 0x00,
    NAS_EMM_EPS_UPDATE_RST_COMBINED_TA_LA_UPDATED           = 0x01,
    NAS_EMM_EPS_UPDATE_RST_TA_UPDATED_AND_ISR               = 0x04,
    NAS_EMM_EPS_UPDATE_RST_COMBINED_TA_LA_UPDATED_AND_ISR   = 0x05,

    NAS_EMM_EPS_UPDATE_RST_BUTT
};
typedef VOS_UINT8 NAS_EMM_EPS_UPDATE_RST_ENUM_UINT8;


/*****************************************************************************
�ṹ����    :
ʹ��˵��    :
*****************************************************************************/
enum NAS_EMM_ATTACH_RST_ENUM
{
    EMM_ATTACH_RST_PS                   = 0x01,
    EMM_ATTACH_RST_PS_CS                = 0x02,

    EMM_ATTACH_RST_BUTT
};
typedef VOS_UINT8   NAS_EMM_ATTACH_RST_ENUM_UINT8;

/*****************************************************************************
�ṹ����    :
ʹ��˵��    :
*****************************************************************************/
enum    NAS_EMM_DETACH_TYPE_MT_ENUM
{

    NAS_EMM_DETACH_TYPE_MT_REATTACH     = 0x01,
    NAS_EMM_DETACH_TYPE_MT_NOT_REATTACH = 0x02,
    NAS_EMM_DETACH_TYPE_MT_IMSI_DETACH  = 0x03,
    NAS_EMM_DETACH_TYPE_MT_RESERVED1    = 0x06,
    NAS_EMM_DETACH_TYPE_MT_RESERVED2    = 0x07,

    NAS_EMM_DETACH_TYPE_MT_BUTT
};
typedef VOS_UINT8   NAS_EMM_DETACH_TYPE_MT_ENUM_UINT8;


/*****************************************************************************
�ṹ����    :
ʹ��˵��    :
*****************************************************************************/
enum NAS_EMM_MSG_DECODE_TYPE_ENUM
{
    NAS_EMM_MSG_DECODE_TYPE_TLV = 0,
    NAS_EMM_MSG_DECODE_TYPE_LV,
    NAS_EMM_MSG_DECODE_TYPE_TV,
    NAS_EMM_MSG_DECODE_TYPE_V,

    NAS_EMM_MSG_DECODE_TYPE_REESV
};
typedef VOS_UINT8  NAS_EMM_MSG_DECODE_TYPE_ENUM_UINT8;

/*****************************************************************************
 ö����    : NAS_EMM_IMEISV_REQUEST_INFO_ENUM
 �ṹ˵��  : NAS���������Ƿ����
*****************************************************************************/
enum NAS_EMM_IMEISV_REQUEST_INFO_ENUM
{
    NAS_EMM_IMEISV_NOT_REQUEST,                         /* ����ҪIMEISV */
    NAS_EMM_IMEISV_REQUEST,                             /* ��ҪIMEISV */

    NAS_EMM_IMEISV_REQUEST_INFO_BUTT
};
typedef VOS_UINT8   NAS_EMM_IMEISV_REQUEST_INFO_ENUM_UINT8;

/*****************************************************************************
 ö����    : NAS_EMM_DECODE_IE_FORMAT_ENUM
 �ṹ˵��  : ��Ԫ�ĸ�ʽ����
*****************************************************************************/

enum NAS_EMM_DECODE_IE_FORMAT_ENUM
{
    NAS_EMM_DECODE_IE_FORMAT_V                 = 0x01,
    NAS_EMM_DECODE_IE_FORMAT_L                 = 0x02,
    NAS_EMM_DECODE_IE_FORMAT_T                 = 0x04,
    NAS_EMM_DECODE_IE_FORMAT_E                 = 0x08,
    NAS_EMM_DECODE_IE_FORMAT_LV                = NAS_EMM_DECODE_IE_FORMAT_L | NAS_EMM_DECODE_IE_FORMAT_V,
    NAS_EMM_DECODE_IE_FORMAT_TV                = NAS_EMM_DECODE_IE_FORMAT_T | NAS_EMM_DECODE_IE_FORMAT_V,
    NAS_EMM_DECODE_IE_FORMAT_TLV               = NAS_EMM_DECODE_IE_FORMAT_T | NAS_EMM_DECODE_IE_FORMAT_L | NAS_EMM_DECODE_IE_FORMAT_V,
    NAS_EMM_DECODE_IE_FORMAT_LV_E              = NAS_EMM_DECODE_IE_FORMAT_L | NAS_EMM_DECODE_IE_FORMAT_V |NAS_EMM_DECODE_IE_FORMAT_E,
    NAS_EMM_DECODE_IE_FORMAT_TLV_E             = NAS_EMM_DECODE_IE_FORMAT_T | NAS_EMM_DECODE_IE_FORMAT_L | NAS_EMM_DECODE_IE_FORMAT_V |NAS_EMM_DECODE_IE_FORMAT_E,

    NAS_EMM_DECODE_IE_FORMAT_BUTT
};
typedef VOS_UINT8 NAS_EMM_DECODE_IE_FORMAT_ENUM_UINT8;
/*****************************************************************************
 ö����    : NAS_EMM_CN_MSG_IE_TYPE_ENUM
 �ṹ˵��  : EMM CN MSG IE����,�ṩ����ά�ɲ�ʹ��
*****************************************************************************/
enum NAS_EMM_CN_MSG_IE_TYPE_ENUM
{
    NAS_EMM_CN_MSG_T3412_IE                          = 0x01,
    NAS_EMM_CN_MSG_GUTI_IE                           = 0x02,
    NAS_EMM_CN_MSG_TAI_IE                            = 0x03,
    NAS_EMM_CN_MSG_LAI_IE                            = 0x04,
    NAS_EMM_CN_MSG_MSID_IE                           = 0x05,
    NAS_EMM_CN_MSG_T3402_IE                          = 0x06,
    NAS_EMM_CN_MSG_T3423_IE                          = 0x07,
    NAS_EMM_CN_MSG_PLMNLIST_IE                       = 0x08,
    NAS_EMM_CN_MSG_EMERGENCYLIST_IE                  = 0x09,
    NAS_EMM_CN_MSG_EPSNETFEATURE_IE                  = 0x0a,
    NAS_EMM_CN_MSG_UPDTAERSLT_IE                     = 0x0b,
    NAS_EMM_CN_MSG_ATTRSLT_IE                        = 0x0c,
    NAS_EMM_CN_MSG_ESMMSG_IE                         = 0x0d,
    NAS_EMM_CN_MSG_TAURSLT_IE                        = 0x0e,
    NAS_EMM_CN_MSG_ADDITIONAL_IE                     = 0x0f,
    NAS_EMM_CN_MSG_PD_IE                             = 0x10,
    NAS_EMM_CN_MSG_SEC_HEAD_TYPE_IE                  = 0x11,
    NAS_EMM_CN_MSG_MSG_TYPE_IE                       = 0x12,
    NAS_EMM_CN_MSG_CLI_IE                            = 0x13,
    NAS_EMM_CN_MSG_LCS_CLIENT_ID_IE                  = 0x14,
    NAS_EMM_CN_MSG_SS_CODE_ID_IE                     = 0x15,
    NAS_EMM_CN_MSG_LCS_IND_IE                        = 0x16,
    NAS_EMM_CN_MSG_GENERIC_MSG_CONT_IE               = 0x17,
    NAS_EMM_CN_MSG_DAYLIGHT_IE                       = 0x18,
    NAS_EMM_CN_MSG_TIMER2_IE                         = 0x19,
    NAS_EMM_CN_MSG_OPTION_IE                         = 0x1a,

    NAS_EMM_CN_MSG_IE_BUTT
};
typedef VOS_UINT32 NAS_EMM_CN_MSG_IE_TYPE_ENUM_UINT32;
/*****************************************************************************
 ö����    : NAS_EMM_CN_MSG_IE_TYPE_ENUM
 �ṹ˵��  : EMM CN MSG IE����ʧ��ԭ��,�ṩ����ά�ɲ�ʹ��
*****************************************************************************/
enum NAS_EMM_CN_MSG_IE_DECODE_FAIL_CAUSE_ENUM
{
    EMM_CN_MSG_IE_ATTRSLT_INVALID            = 0x1,
    EMM_CN_MSG_IE_LEN_INVALID                = 0x2,
    EMM_CN_MSG_IE_TAILIST_TYPE_INVALID       = 0x3,
    EMM_CN_MSG_IE_TYPE_INVALID               = 0x4,
    EMM_CN_MSG_IE_TAURSLT_INVALID            = 0x5,
    EMM_CN_MSG_IE_ADDITONAL_INFO_TOO_SHORT   = 0x6,
    EMM_CN_MSG_PD_INVALID                    = 0x7,
    EMM_CN_MSG_SEC_HEAD_TYPE_INVALID         = 0x8,
    EMM_CN_MSG_MSG_TYPE_INVALID              = 0x9,
    EMM_CN_MSG_IE_DECODE_FAIL_CAUSE_BUTT
};
typedef VOS_UINT32 NAS_EMM_CN_MSG_DECODE_FAIL_CAUSE_ENUM_UINT32;



/*****************************************************************************
  5 STRUCT
*****************************************************************************/


/*****************************************************************************
�ṹ����    :NAS_EMM_TIMER_STRU
ʹ��˵��    :Figure 10.5.146/3GPP TS 24.008: GPRS Timer information element
             ucUnit     : Bits 8 to 6 of ucTimerVal is the same as  Bits 8 to 6
                          of octet 2 of  GPRS Timer information element
             ucTimerVal : Bits 5 to 1 of ucTimerVal is the same as  Bits 5 to 1
                          of octet 2 of  GPRS Timer information element
*****************************************************************************/
typedef struct
{
   NAS_EMM_TIMER_UNIT_ENUM_UINT8        ucUnit ;            /*000:value is incremented in multiples of 2 seconds
                                                              001:value is incremented in multiples of 2 minute
                                                              010:value is incremented in multiples of decihours
                                                              111:value indicated that the timer is deactivated*/

    VOS_UINT8                           ucTimerVal;

    VOS_UINT8                           ucRsv[2];

}NAS_EMM_TIMER_STRU;

/*****************************************************************************
�ṹ����    :NAS_EMM_CN_MSGCON_STRU
ʹ��˵��    :24301 8.2.1.1: ATTACH ACCEPT message
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulMsgLen;
    VOS_UINT8                           aucMsg[NAS_EMM_CN_MSGCON_MAX_LEN];

}NAS_EMM_CN_MSGCON_STRU;


/*****************************************************************************
�ṹ����    :NAS_EMM_CN_ATTACH_ACP_STRU
ʹ��˵��    :24301 8.2.1.1: ATTACH ACCEPT message
*****************************************************************************/
typedef struct
{
    NAS_EMM_CN_MSG_HEADER

    VOS_UINT32                          ucBitOpGuti             :1; /* 1: VALID; 0: INVALID*/
    VOS_UINT32                          ucBitOpLai              :1;
    VOS_UINT32                          ucBitOpMsId             :1;
    VOS_UINT32                          ucBitOpEmmCau           :1;
    VOS_UINT32                          ucBitOpaucRsv2          :1;
    VOS_UINT32                          ucBitOpT3402            :1;
    VOS_UINT32                          ucBitOpT3423            :1;
    VOS_UINT32                          ucBitOpPlmnList         :1;
    VOS_UINT32                          ucBitOpEmergencyList    :1;
    VOS_UINT32                          ucBitOpEpsNetFeature    :1;
    VOS_UINT32                          ucBitOpaucRsv           :1;
    VOS_UINT32                          ucBitOpAdditionalUpRslt :1;
    VOS_UINT32                          ucBitRsv                :20;

    NAS_EMM_ATTACH_RST_ENUM_UINT8       ucAttachRst;
    VOS_UINT8                           aucRsv1[3];
    NAS_EMM_TIMER_STRU                  stT3412Value;
    NAS_EMM_TA_LIST_STRU                stTaiList;
    NAS_EMM_CN_MSGCON_STRU              stMsgCon;
    NAS_EMM_GUTI_STRU                   stGuti;
    NAS_EMM_LA_STRU                     stLai;
    NAS_EMM_MSID_STRU                   stMsId;
    NAS_EMM_CN_CAUSE_ENUM_UINT8         ucEMMCause;
    VOS_UINT8                           aucRsv2[3];
    NAS_EMM_TIMER_STRU                  stT3402Value;
    NAS_EMM_TIMER_STRU                  stT3423Value;
    NAS_EMM_PLMN_LIST_STRU              stPlmnList;
    NAS_LMM_EMERGENCY_NUM_LIST_STRU     stEmergencyNumList;
    /*
    -----------------------------------------------------------------------------
    bit8    |  bit7  | bit6  | bit5  | bit4   | bit3   |  bit2  | bit1
    -----------------------------------------------------------------------------
                Spare        |    CS-LCS      |EPC-LCS |  EMC BS  |  IMS VoPS
    -----------------------------------------------------------------------------
    */
    VOS_UINT8                           ucEpsNetFeature;
    VOS_UINT8                           aucRsv[3];
    NAS_LMM_ADDITIONAL_UPDATE_RSLT_ENUM_UINT32    ulAdditionUpRslt;

}NAS_EMM_CN_ATTACH_ACP_STRU;

/*****************************************************************************
�ṹ����    :NAS_EMM_CN_ATTACH_REJ_STRU
ʹ��˵��    :24301 8.2.3.1: ATTACH REJECT message
*****************************************************************************/
typedef struct
{
    NAS_EMM_CN_MSG_HEADER

    VOS_UINT32                          ucBitOpMsgCon   :1; /* 1: VALID; 0: INVALID*/
    VOS_UINT32                          ucBitOpT3402    :1;
    VOS_UINT32                          ucBitOpExtCause :1;

    VOS_UINT32                          ucBitRsv        :29;
    NAS_EMM_CN_CAUSE_ENUM_UINT8         ucCause;
    NAS_EMM_CN_CAUSE_ENUM_UINT8         ucEsmCause;
    VOS_UINT8                           ucExtendedEmmCause;
    VOS_UINT8                           ucRsv1;
    NAS_EMM_CN_MSGCON_STRU              stMsgCon;
    NAS_EMM_TIMER_STRU                  stT3402Value;

}NAS_EMM_CN_ATTACH_REJ_STRU;


/*****************************************************************************
�ṹ����    :NAS_EMM_CN_DETACH_ACP_MO_STRU
ʹ��˵��    :Table 8.2.9.1.1: DETACH ACCEPT message content
             CN->UE
*****************************************************************************/
typedef struct
{
    NAS_EMM_CN_MSG_HEADER

}NAS_EMM_CN_DETACH_ACP_MO_STRU;



/*****************************************************************************
�ṹ����    :NAS_EMM_CN_DETACH_REQ_MT_STRU
ʹ��˵��    :Table 8.2.10.2.1: DETACH REQUEST message content
             CN->UE
*****************************************************************************/
typedef struct
{
    NAS_EMM_CN_MSG_HEADER

    VOS_UINT32                          ucBitOpCause   :1;  /* 1: VALID; 0: INVALID*/
    VOS_UINT32                          ucBitRsv       :31;

    NAS_EMM_DETACH_TYPE_MT_ENUM_UINT8   ucDetType;
    NAS_EMM_CN_CAUSE_ENUM_UINT8         ucEmmCause;
    VOS_UINT8                           aucRsv[2];

}NAS_EMM_CN_DETACH_REQ_MT_STRU;


/*****************************************************************************
�ṹ����    :NAS_EMM_EPS_BEARER_STATUS_STRU
ʹ��˵��    :
*****************************************************************************/
typedef struct
{

    VOS_UINT32                          ulEpsIdNum;         /* �Ѽ����EPSID���� */
    VOS_UINT32                          aulEsmEpsId[EMM_ESM_MAX_EPS_BEARER_NUM];
}NAS_EMM_EPS_BEARER_STATUS_STRU;


/*****************************************************************************
�ṹ����    :NAS_EMM_CN_TAU_ACP_STRU
ʹ��˵��    :Table 8.2.24: TRACKING AREA UPDATE COMPLETE message
             CN->UE
*****************************************************************************/
typedef struct
{
    NAS_EMM_CN_MSG_HEADER

    VOS_UINT32                          ucBitOpT3412            :1; /* 1: VALID; 0: INVALID*/
    VOS_UINT32                          ucBitOpGuti             :1; /* 1: VALID; 0: INVALID*/
    VOS_UINT32                          ucBitOpTaiList          :1; /* 1: VALID; 0: INVALID*/
    VOS_UINT32                          ucBitOpEPSstatus        :1; /* 1: VALID; 0: INVALID*/
    VOS_UINT32                          ucBitOpLai              :1; /* 1: VALID; 0: INVALID*/
    VOS_UINT32                          ucBitOpMsId             :1; /* 1: VALID; 0: INVALID*/
    VOS_UINT32                          ucBitOpEmmCau           :1; /* 1: VALID; 0: INVALID*/
    VOS_UINT32                          ucBitOpaucRsv1          :1; /* 1: VALID; 0: INVALID*/
    VOS_UINT32                          ucBitOpT3402            :1; /* 1: VALID; 0: INVALID*/
    VOS_UINT32                          ucBitOpT3423            :1; /* 1: VALID; 0: INVALID*/
    VOS_UINT32                          ucBitOpEquivalentPLMNs  :1; /* 1: VALID; 0: INVALID*/
    VOS_UINT32                          ucBitOpEmergencyList    :1;
    VOS_UINT32                          ucBitOpEpsNetFeature    :1;
    VOS_UINT32                          ucBitOpaucRsv2          :1;
    VOS_UINT32                          ucBitOpAdditionalUpRslt :1;
    VOS_UINT32                          ucBitShare              :17;


    NAS_EMM_EPS_UPDATE_RST_ENUM_UINT8   ucEPSupdataRst;
    VOS_UINT8                           aucRsv[3];

    NAS_EMM_TIMER_STRU                  stT3412;
    NAS_EMM_GUTI_STRU                   stGuti;
    NAS_EMM_TA_LIST_STRU                stTaiList;
    NAS_EMM_EPS_BEARER_STATUS_STRU      stEPSBearerstatus;
    NAS_EMM_LA_STRU                     stLai;
    NAS_EMM_MSID_STRU                   stMsId;
    NAS_EMM_CN_CAUSE_ENUM_UINT8         ucEMMCause;
    VOS_UINT8                           aucRsv1[3];

    NAS_EMM_TIMER_STRU                  stT3402;
    NAS_EMM_TIMER_STRU                  stT3423;
    NAS_EMM_PLMN_LIST_STRU              stEquivalentPLMNs;

    NAS_LMM_EMERGENCY_NUM_LIST_STRU     stEmergencyNumList;
    /*
    -----------------------------------------------------------------------------
    bit8    |  bit7  | bit6  | bit5  | bit4   | bit3   |  bit2  | bit1
    -----------------------------------------------------------------------------
                Spare        |    CS-LCS      |EPC-LCS |  EMC BS  |  IMS VoPS
    -----------------------------------------------------------------------------
    */
    VOS_UINT8                           ucEpsNetFeature;
    VOS_UINT8                           aucRsv2[3];
    NAS_LMM_ADDITIONAL_UPDATE_RSLT_ENUM_UINT32    ulAdditionUpRslt;
}NAS_EMM_CN_TAU_ACP_STRU;

/*****************************************************************************
�ṹ����    :NAS_EMM_CN_TAU_REJ_STRU
ʹ��˵��    :24301 8.2.25 : TAU REJECT message
*****************************************************************************/
typedef struct
{
    NAS_EMM_CN_MSG_HEADER

    VOS_UINT32                          ucBitOpT3346    :1; /* 1: VALID; 0: INVALID*/
    VOS_UINT32                          ucBitOpExtCause :1;
    VOS_UINT32                          ucBitRsv        :30;

    NAS_EMM_CN_CAUSE_ENUM_UINT8         ucEMMCause;
    VOS_UINT8                           ucEmmExtCause;
    VOS_UINT8                           aucRsv[2];
    NAS_EMM_TIMER_STRU                  stT3346;

}NAS_EMM_CN_TAU_REJ_STRU;

/*****************************************************************************
�ṹ����    :NAS_EMM_CN_SER_REJ_STRU
ʹ��˵��    :24301 8.2.21 : SER REJECT message
*****************************************************************************/
typedef struct
{
    NAS_EMM_CN_MSG_HEADER

    VOS_UINT32                          ucBitOpT3442    :1; /* 1: VALID; 0: INVALID*/
    VOS_UINT32                          ucBitRsv        :31;

    NAS_EMM_CN_CAUSE_ENUM_UINT8         ucEMMCause;
    VOS_UINT8                           aucRsv[3];
    NAS_EMM_TIMER_STRU                  stT3442;

}NAS_EMM_CN_SER_REJ_STRU;


/*****************************************************************************
�ṹ����    :NAS_EMM_GUTI_REALLOCATION_CMD_STRU
ʹ��˵��    :Table 8.2.13.1: GUTI REALLOCATION COMMAND message content
*****************************************************************************/
typedef struct
{
    NAS_EMM_CN_MSG_HEADER

    VOS_UINT32                          ucBitOpTaiList :1;  /* 1: VALID; 0: INVALID*/
    VOS_UINT32                          ucBitShare     :31;

    NAS_EMM_GUTI_STRU                   stGuti;

    NAS_EMM_TA_LIST_STRU                stTaiList;

}NAS_EMM_GUTI_REALLOCATION_CMD_STRU;


/*****************************************************************************
�ṹ����    :NAS_EMM_IDENTITY_REQUEST_STRU
ʹ��˵��    :Table 8.2.15.1: IDENTITY REQUEST message content
*****************************************************************************/
typedef struct
{
    NAS_EMM_CN_MSG_HEADER

    NAS_EMM_IDENTITY_TYPE_ENUM_UINT8    ucIdenType;
    VOS_UINT8                           aucRsv[3];

}NAS_EMM_IDEN_REQ_STRU;
/*****************************************************************************
�ṹ����    :NAS_EMM_MSG_IE_COMMON_STRU
ʹ��˵��    :����TLV�ṹ����Ԫ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucLen;              /* IE�ĳ��� */
    VOS_UINT8                           aucRsv[3];          /* ���ֽڶ��룬���� */
    VOS_UINT8                          *pucValue;           /* IE���׵�ַ */
}NAS_EMM_MSG_IE_COMMON_STRU;

/*****************************************************************************
�ṹ����    :NAS_EMM_SMC_SCRTY_CPBLTY_STRU
ʹ��˵��    :24301-9.9.3.30 UE security capability
*****************************************************************************/
typedef  NAS_EMM_MSG_IE_COMMON_STRU NAS_EMM_SMC_SECURITY_CAPA_STRU;

/*****************************************************************************
�ṹ����    :NAS_EMM_AUTH_REQ_STRU
ʹ��˵��    :Table 8.2.7.1: AUTHENTICATION  REQUEST message content
*****************************************************************************/
typedef struct
{
    NAS_EMM_CN_MSG_HEADER

    VOS_UINT8                           ucKsi;                                /*��Կ����*/
    VOS_UINT8                           aucRsv[3];
    VOS_UINT8                           aucRand[NAS_EMM_RAND_LEN];        /*����������Կ�������*/
    VOS_UINT8                           aucAutn[NAS_EMM_AUTN_LEN];        /*����������Կ�Ĳ���*/
    VOS_UINT32                          ulAutnLen;

}NAS_EMM_AUTH_REQ_STRU;

/*****************************************************************************
�ṹ����    :NAS_EMM_AUTH_REJ_STRU
ʹ��˵��    :Table 8.2.6.1: AUTHENTICATION REJECT message content
*****************************************************************************/
typedef struct
{
    NAS_EMM_CN_MSG_HEADER

}NAS_EMM_AUTH_REJ_STRU;

/*****************************************************************************
�ṹ����    :NAS_EMM_SMC_CMD_STRU
ʹ��˵��    :Table 8.2.17.1: SECURITY MODE COMMAND message content
*****************************************************************************/
typedef struct
{
    NAS_EMM_CN_MSG_HEADER

    VOS_UINT8                                 ucSelAlgrthm;     /* UEѡ��ļ��ܺ������Ա����㷨 */
    VOS_UINT8                                 ucKSIasme;        /* ��Կ������ */
    NAS_EMM_IMEISV_REQUEST_INFO_ENUM_UINT8    ucImeisvRsq;      /* �ظ�����Ϣ�Ƿ���ҪIMEISV */
    VOS_UINT8                                 ucReserved;
    NAS_EMM_SMC_SECURITY_CAPA_STRU            stReSecurityCapa; /* UE�İ�ȫ���� */
}NAS_EMM_SMC_CMD_STRU;

typedef VOS_UINT32 ( * NAS_EMM_DECODE_IE_FUN)
(
    VOS_UINT8 * ,                           /* ����ָ�� */
    VOS_UINT32 *,                           /* ����ͳ��ָ�� */
    VOS_VOID * ,                            /* �������ָ�� */
    NAS_EMM_CN_MSG_TYPE_ENUM_UINT8  enMsgTp /*��Ϣid,��һ������ʹ�ã����������Ż�*/
);

/*****************************************************************************
�ṹ����    :NAS_EMM_DECODE_IE_INFO_STRU (������Ԫ������Ϣ)
ʹ��˵��    :����ѭ��������Ԫ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                 ucIEI;                        /* ��Ԫ��id */
    VOS_UINT8                                 ucIEBits;                     /* ��Ԫ��bitλ��������������Ĳ��� */
    VOS_UINT8                                 ucIEBitsMove;                 /* ��Ҫ��λ��λ��*/
    VOS_UINT8                                 ucIELen;                      /* ��Ԫ����*/
    VOS_UINT8                                 ucRsv;                        /* ��Ԫ��ѡ*/
    NAS_LMM_IE_FORMAT_ENUM_UINT8               ucIEFormat;                   /* ��Ԫ����*/
    VOS_UINT16                                usIEStructSize;               /* �ڲ�������Ԫ�Ľṹ��ռ� */
    VOS_CHAR                                  acIEName[NAS_EMM_IE_NAME_LEN];/* ��Ԫ����*/
    NAS_EMM_DECODE_IE_FUN                     pfIEDecodeFun;                /* ��Ԫ��������ָ��*/
}NAS_EMM_DECODE_IE_INFO_STRU;

/*****************************************************************************
�ṹ����    :NAS_EMM_DECODE_MSG_IE_INFO_STRU  (��Ϣ����Ԫ��Ϣ)
ʹ��˵��    :��Ϣ��Ԫ�б�
*****************************************************************************/
typedef struct
{
    NAS_EMM_DECODE_IE_INFO_STRU               stIEInfo;                     /* ��Ԫ������Ϣ*/
    VOS_UINT8                                 aucRsv[3];                    /* �ֽڶ��� */
    VOS_UINT8                                 ucIEMust;                     /* ��ѡ��Ԫ */

}NAS_EMM_DECODE_MSG_IE_INFO_STRU;

/*****************************************************************************
�ṹ����    :NAS_EMM_DECODE_MSG_INFO_STRU  (��Ϣ����Ԫ��Ϣ)
ʹ��˵��    :��Ϣ�б�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucRsv[2];
    NAS_EMM_CN_MSG_TYPE_ENUM_UINT8      ucMsgType;                          /*��Ϣ����*/
    VOS_UINT8                           ucMsgIETableSize;                   /*��Ԫ�б�Ĵ�С*/
    NAS_EMM_DECODE_MSG_IE_INFO_STRU     *pastMsgIETable;                    /*��Ϣ��Ԫ�б�*/
    VOS_CHAR                            acMsgName[NAS_EMM_IE_NAME_LEN];     /* ��Ϣ����*/
}NAS_EMM_DECODE_MSG_INFO_STRU;

/*****************************************************************************
�ṹ����    :NAS_EMM_DECODE_CN_MSG_HEADER_STRU  (��Ϣ����Ԫ��Ϣ)
ʹ��˵��    :��NAS_EMM_CN_MSG_HEADER ͬ���Ľṹ��,����ȡ����
*****************************************************************************/
typedef struct
{
    NAS_EMM_CN_MSG_TYPE
    NAS_EMM_CN_MSG_HEADER
}NAS_EMM_DECODE_CN_MSG_HEADER_STRU;

/*****************************************************************************
�ṹ����    :NAS_EMM_DECODE_IEOPT_PARA_ENTRY  (��Ԫ�б�����������)
ʹ��˵��    :���ڴ���������������в�������һ��
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           *pRcvMsg;                           /*���������ַ*/
    VOS_UINT8                           aucRsv[3];
    VOS_UINT32                          ulLength;                           /*����ʣ�೤��*/
    VOS_UINT32                          *pCnMsgOpt;                         /*���ڱ�־λ�洢��ַ*/
    VOS_UINT32                          ulOptPos;                           /*���ڱ�־λ���λ�� > 0 */
    VOS_VOID                            *pstCnMsgStru;                      /*��Ϣ�ڲ��洢���ݽṹ��ڵ�ַ */
    NAS_EMM_DECODE_MSG_INFO_STRU        *pstCnMsgInfo;                      /*��Ϣ������ָ��*/

}NAS_EMM_DECODE_IELIST_PARA_STRU;

typedef struct
{
    NAS_EMM_CN_MSG_HEADER

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
 }NAS_EMM_CN_EMM_INFO_STRU;

typedef struct
{
    NAS_EMM_CN_MSG_HEADER

    VOS_UINT8                                 ucEmmCause;
}NAS_EMM_CN_EMM_STATU_STRU;

typedef struct
{
    NAS_EMM_CN_MSG_HEADER

    VOS_UINT8                                 ucDownlinkNasTransportLen;
    VOS_UINT8                                 aucDownlinkNasTransportMsg[NAS_EMM_DOWNLINK_NAS_TRANSPORT_MAX_LEN];
}NAS_EMM_CN_DOWNLINK_NAS_TRANSPORT_STRU;

typedef VOS_VOID ( * NAS_LMM_TAU_REJ_CAUSE_PROC_FUN )
(
    NAS_EMM_CN_CAUSE_ENUM_UINT8         enRejCauseVal,
    NAS_EMM_CN_TAU_REJ_STRU            *pstTAURej
);

typedef struct
{
    NAS_EMM_CN_CAUSE_ENUM_UINT8         enRejCauseVal; /* �ܾ�ԭ��ֵ */
    NAS_LMM_TAU_REJ_CAUSE_PROC_FUN      pfRejCauseProcFun; /* �ܾ�ԭ��ֵ�Ĵ����� */
}NAS_LMM_TAU_REJ_CAUSE_PROC_STRU;



/*****************************************************************************
�ṹ����    :NAS_EMM_CN_CS_SER_NOTIFICAIOTN_STRU
ʹ��˵��    :Table 8.2.9.1: CS SERVICE NOTIFICATION message content
*****************************************************************************/
typedef struct
{
    NAS_EMM_CN_MSG_HEADER

    VOS_UINT32                          bitOpCli            :1;
    VOS_UINT32                          bitOpSsCode         :1;
    VOS_UINT32                          bitOpLcsIndicator   :1;
    VOS_UINT32                          bitOpLcsClientId    :1;
    VOS_UINT32                          bitShare            :28;

    VOS_UINT8                           ucPagingIdenity;    /* 0:IMSI;1:TMSI */
    VOS_UINT8                           ucSsCodeValue;
    VOS_UINT8                           ucCliLength;        /* 1~12*/
    VOS_UINT8                           aucCliValue[NAS_EMM_CLI_MAX_LEN];    /* �տ�����������������24008 10.5.4.9��Call party BCD��3��14�ֶεı��뷽ʽһ�� */
    VOS_UINT8                           ucLcsIndicatorValue;
    VOS_UINT8                           ucLcsClientIdLen;
    VOS_UINT8                           aucLcsClientId[NAS_EMM_LCS_CLIENT_ID_MAX_LEN];
}NAS_EMM_CN_CS_SER_NOTIFICAIOTN_STRU;


typedef struct
{
    VOS_UINT16                          usMsgLen;
    VOS_UINT8                           aucRsv[2];
    VOS_UINT8                           aucMsg[NAS_EMM_CN_MSGCON_MAX_LEN];
} NAS_EMM_GENERIC_MESSAGE_CONTAINER_STRU;

typedef struct
{
    VOS_UINT8                           ucMsgLen;
    VOS_UINT8                           aucRsv[3];
    VOS_UINT8                           aucMsg[256];
} NAS_EMM_ADDITIONAL_INFOR_STRU;

typedef struct
{
    NAS_EMM_CN_MSG_HEADER

    VOS_UINT32                          bitOpAdditionalInfo :1;
    VOS_UINT32                          bitRsv              :31;

    VOS_UINT8                           ucContainerType;
    VOS_UINT8                           aucRsv[3];
    NAS_EMM_GENERIC_MESSAGE_CONTAINER_STRU stContainer;
    NAS_EMM_ADDITIONAL_INFOR_STRU       stAdditionalInfo;
} NAS_EMM_CN_DOWNLINK_GENERIC_NAS_TRANSPORT_STRU;


/*****************************************************************************
  6 UNION
*****************************************************************************/

typedef union
{
    NAS_EMM_CN_ATTACH_ACP_STRU          stAttAcp;
    NAS_EMM_CN_ATTACH_REJ_STRU          stAttRej;

    NAS_EMM_CN_DETACH_ACP_MO_STRU       stDetachAcp;
    NAS_EMM_CN_DETACH_REQ_MT_STRU       stDetachReq;

    NAS_EMM_CN_TAU_ACP_STRU             stTauAcp;
    NAS_EMM_CN_TAU_REJ_STRU             stTauRej;

    NAS_EMM_CN_SER_REJ_STRU             stSerRej;

    NAS_EMM_GUTI_REALLOCATION_CMD_STRU  stGutiReaCmd;

    NAS_EMM_IDEN_REQ_STRU               stIdenReq;
    NAS_EMM_AUTH_REQ_STRU               stAuthReq;
    NAS_EMM_AUTH_REJ_STRU               stAuthRej;
    NAS_EMM_SMC_CMD_STRU                stSecurModeCtrl;
    NAS_EMM_CN_EMM_STATU_STRU           stEmmStatus;
    NAS_EMM_CN_EMM_INFO_STRU            stEmmInfo;
    NAS_EMM_CN_DOWNLINK_NAS_TRANSPORT_STRU  stDownlinkNasTransport;
    NAS_EMM_CN_CS_SER_NOTIFICAIOTN_STRU stCsSerNotification;
    NAS_EMM_CN_DOWNLINK_GENERIC_NAS_TRANSPORT_STRU stDownlinkGenericNasTransport;
}NAS_EMM_CN_MSG_STRU_UNION;



typedef struct
{
    NAS_EMM_CN_MSG_TYPE

    NAS_EMM_CN_MSG_STRU_UNION           uCnMsgStru;
}NAS_EMM_CN_MSG_STRU;

/*��������Ϣ���������б�Ķ���*/
/* ��Ϣ�������������Ͷ���*/
typedef VOS_UINT32 ( * NAS_EMM_DECODE_MSG_FUN)
(
    LRRC_LNAS_MSG_STRU *,                   /* ����ָ�� */
    VOS_UINT32 ,                          /* ������ʼλ�� */
    NAS_EMM_CN_MSG_STRU *                 /* �������ָ�� */
);

/*****************************************************************************
�ṹ����    :NAS_EMM_DECODE_MSG_FUNS_STRU
ʹ��˵��    :��Ϣ������������Ϣid�Ľṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                       aucRsv[3];
    NAS_EMM_CN_MSG_TYPE_ENUM_UINT8  enMsgTp;            /*��Ϣid*/
    NAS_EMM_DECODE_MSG_FUN          pDecodeMsgFun;      /* ����ָ��*/
}NAS_EMM_DECODE_MSG_FUNS_STRU;
/*�����ֽ�����ж�*/
typedef union
{
    VOS_UINT8   aucMember[4];
    VOS_UINT32  ulMember;
}NAS_EMM_DECODE_EDIAN_UION;
typedef struct
{
    MSG_HEADER_STRU                                      stMsgHeader;     /*_H2ASN_Skip*/
    NAS_EMM_CN_MSG_IE_TYPE_ENUM_UINT32                   enIeType;
    NAS_EMM_CN_MSG_DECODE_FAIL_CAUSE_ENUM_UINT32         enCause;
    VOS_UINT32                                           ulValue;
}NAS_LMM_OM_LOG_CN_MSG_DECODE_FAIL_STRU;

/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/

/*zhuyqmm:*/
/*
extern NAS_EMM_CN_MSGCON_STRU                  g_stAirMsgEncode;
*/
extern NAS_EMM_DECODE_MSG_FUNS_STRU g_astEmmCnMsgFuns[];
extern VOS_UINT32 g_ulSizeof_g_astEmmCnMsgFuns;

extern NAS_LMM_TAU_REJ_CAUSE_PROC_STRU  gstEmmTauRejCauseProcTbl[];
extern VOS_UINT32        gstEmmTauRejCauseProcTblLen;

/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern  VOS_UINT32  NAS_EMM_DecodeCnMsg(MsgBlock               *pOsaMsg,
                                    NAS_EMM_CN_MSG_STRU            *pstCnMsgStru);
extern  VOS_UINT32  NAS_EMM_DecodeCnAttachAcpMsg(LRRC_LNAS_MSG_STRU  *pRcvMsg,
                                    VOS_UINT32                      ulLength,
                                    NAS_EMM_CN_MSG_STRU            *pstCnMsgStru);
extern  VOS_UINT32  NAS_EMM_DecodeCnAttachRejMsg(LRRC_LNAS_MSG_STRU  *pRcvMsg,
                                    VOS_UINT32                      ulLength,
                                    NAS_EMM_CN_MSG_STRU            *pstCnMsgStru);

extern  VOS_UINT32  NAS_EMM_DecodeCnDetachReqMsg(LRRC_LNAS_MSG_STRU  *pRcvMsg,
                                    VOS_UINT32                      ulLength,
                                    NAS_EMM_CN_MSG_STRU            *pstCnMsgStru);
extern  VOS_UINT32  NAS_EMM_DecodeCnGUTICmdMsg(LRRC_LNAS_MSG_STRU  *pRcvMsg,
                                    VOS_UINT32                      ulLength,
                                    NAS_EMM_CN_MSG_STRU            *pstCnMsgStru);
extern  VOS_UINT32  NAS_EMM_DecodeCnSerRejMsg(LRRC_LNAS_MSG_STRU  *pRcvMsg,
                                    VOS_UINT32                      ulLength,
                                    NAS_EMM_CN_MSG_STRU            *pstCnMsgStru);
extern  VOS_UINT32  NAS_EMM_DecodeCnTAUAcpMsg(LRRC_LNAS_MSG_STRU  *pRcvMsg,
                                    VOS_UINT32                      ulLength,
                                    NAS_EMM_CN_MSG_STRU            *pstCnMsgStru);
extern  VOS_UINT32  NAS_EMM_DecodeCnDetachAcpMsg(LRRC_LNAS_MSG_STRU  *pRcvMsg,
                                    VOS_UINT32                      ulLength,
                                    NAS_EMM_CN_MSG_STRU            *pstCnMsgStru);
extern  VOS_UINT32  NAS_EMM_DecodeCnIdenReqMsg(LRRC_LNAS_MSG_STRU  *pRcvMsg,
                                    VOS_UINT32                      ulLength,
                                    NAS_EMM_CN_MSG_STRU            *pstCnMsgStru);
extern  VOS_UINT32  NAS_EMM_DecodeCnTAURejMsg(LRRC_LNAS_MSG_STRU  *pRcvMsg,
                                    VOS_UINT32                      ulLength,
                                    NAS_EMM_CN_MSG_STRU            *pstCnMsgStru);
extern  VOS_UINT32  NAS_EMM_DecodeCnAuthRejMsg(LRRC_LNAS_MSG_STRU  *pRcvMsg,
                                    VOS_UINT32                      ulLength,
                                    NAS_EMM_CN_MSG_STRU            *pstCnMsgStru);
extern  VOS_UINT32  NAS_EMM_DecodeCnAuthReqMsg
(
    LRRC_LNAS_MSG_STRU                    *pRcvMsg,
    VOS_UINT32                          ulLength,
    NAS_EMM_CN_MSG_STRU                 *pstCnMsgStru
);

extern VOS_UINT32  NAS_EMM_DecodeCnAuthReqMsgNasMsg
(
    LRRC_LNAS_MSG_STRU                    *pRcvMsg,
    VOS_UINT8                           *pucRcvCnNasMsg,
    VOS_UINT32                          ulLength,
    NAS_EMM_CN_MSG_STRU                 *pstCnMsgStru
);
extern VOS_UINT32  NAS_EMM_DecodeCnSecurModeCtrlMsg
(
    LRRC_LNAS_MSG_STRU                    *pRcvMsg,
    VOS_UINT32                          ulLength,
    NAS_EMM_CN_MSG_STRU                 *pstCnMsgStru
);
extern VOS_UINT32  NAS_EMM_DecodeCnSecurModeCtrlMsgNasMsg
(
    LRRC_LNAS_MSG_STRU                    *pRcvMsg,
    VOS_UINT8                           *pucRcvCnNasMsg,
    VOS_UINT32                          ulLength,
    NAS_EMM_CN_MSG_STRU                 *pstCnMsgStru
);

extern  VOS_UINT32  NAS_EMM_DecodeTai(
                                    VOS_UINT8  *pRcvMsg,
                                    VOS_UINT32 *pulIndex,
                                    VOS_VOID   *pstTaiStru,
                                    NAS_EMM_CN_MSG_TYPE_ENUM_UINT8  enMsgTp);

extern  VOS_UINT32  NAS_EMM_DecodeMsgCon(VOS_UINT8  *pRcvMsg,
                                        VOS_UINT32  *ulIndex,
                                    NAS_EMM_CN_MSGCON_STRU   *pstMsgConStru);
extern VOS_UINT32  NAS_EMM_DecodeCnDetachReqMsgNasMsg(
                                        LRRC_LNAS_MSG_STRU           *pRcvMsg,
                                        VOS_UINT8                  *pucRcvCnNasMsg,
                                        VOS_UINT32                  ulLength,
                                        NAS_EMM_CN_MSG_STRU        *pstCnMsgStru);

extern  VOS_UINT32  NAS_EMM_DecodeMsId(
                                    VOS_UINT8   *pRcvMsg,
                                    VOS_UINT32  *pulIndex,
                                    VOS_VOID    *pstMsIdStru,
                                    NAS_EMM_CN_MSG_TYPE_ENUM_UINT8  enMsgTp);
extern  VOS_UINT32  NAS_EMM_DecodeLai(
                                    VOS_UINT8   *pRcvMsg,
                                    VOS_UINT32  *pulIndex,
                                    VOS_VOID    *pstLaiStru,
                                    NAS_EMM_CN_MSG_TYPE_ENUM_UINT8  enMsgTp);
extern  VOS_UINT32  NAS_EMM_DecodeGuti(
                                    VOS_UINT8   *pRcvMsg,
                                    VOS_UINT32  *pulIndex,
                                    VOS_VOID    *pstGutiStru,
                                    NAS_EMM_CN_MSG_TYPE_ENUM_UINT8  enMsgTp);
extern  VOS_UINT32  NAS_EMM_DecodePlmnList(
                                    VOS_UINT8   *pRcvMsg,
                                    VOS_UINT32  *pulIndex,
                                    VOS_VOID    *pstPlmnListStru,
                                    NAS_EMM_CN_MSG_TYPE_ENUM_UINT8  enMsgTp);

extern  VOS_UINT32  NAS_EMM_DecodeEmergencyNumList
(
                                    VOS_UINT8   *pRcvMsg,
                                    VOS_UINT32  *pulIndex,
                                    VOS_VOID    *pstEmergencyListStru,
                                    NAS_EMM_CN_MSG_TYPE_ENUM_UINT8  enMsgTp
);

extern VOS_UINT32  NAS_EMM_DecodeEpsNetFeatureSupport
(
    VOS_UINT8   *pRcvMsg,
    VOS_UINT32  *pulIndex,
    VOS_VOID    *pucNetFeature,
    NAS_EMM_CN_MSG_TYPE_ENUM_UINT8  enMsgTp
);

extern VOS_UINT32  NAS_EMM_DecodeAdditionalUpdateRslt
(
    VOS_UINT8   *pRcvMsg,
    VOS_UINT32  *pulIndex,
    VOS_VOID    *pucNetFeature,
    NAS_EMM_CN_MSG_TYPE_ENUM_UINT8  enMsgTp
);
extern VOS_UINT32  NAS_EMM_DecodeTimer(
                                    VOS_UINT8   *pucRcvMsg,
                                    VOS_UINT32  *pulIndex,
                                    VOS_VOID    *pstTimer,
                                    NAS_EMM_CN_MSG_TYPE_ENUM_UINT8  enMsgTp);
extern VOS_UINT32  NAS_EMM_DecodeBearerTxtStus(
                                    VOS_UINT8   *pRcvMsg,
                                    VOS_UINT32  *pulIndex,
                                    VOS_VOID    *pstBTxtStus,
                                    NAS_EMM_CN_MSG_TYPE_ENUM_UINT8  enMsgTp);
extern VOS_UINT32  NAS_EMM_DecodeEmmCau(
                                    VOS_UINT8   *pRcvMsg,
                                    VOS_UINT32  *pulIndex,
                                    VOS_VOID    *pstCnMsgStru,
                                    NAS_EMM_CN_MSG_TYPE_ENUM_UINT8  enMsgTp);
extern VOS_UINT32  NAS_EMM_DecodeKSIasme(
                                    VOS_UINT8   *pRcvMsg,
                                    VOS_UINT32  *pulIndex,
                                    VOS_VOID    *pstCnMsgStru,
                                    NAS_EMM_CN_MSG_TYPE_ENUM_UINT8  enMsgTp);
extern VOS_UINT32  NAS_EMM_DecodeCnMsgIEOptList(
                                    NAS_EMM_DECODE_IELIST_PARA_STRU *pstIEOptParaList,
                                    VOS_UINT32  *pulSum
                                          );
extern VOS_UINT32  NAS_EMM_DecodeCnTAUAcpMsgNasMsg(
                                    LRRC_LNAS_MSG_STRU           *pRcvMsg,
                                    VOS_UINT8                  *pucRcvCnNasMsg,
                                    VOS_UINT32                  ulLength,
                                    NAS_EMM_CN_MSG_STRU        *pstCnMsgStru);
extern VOS_UINT32  NAS_EMM_DecodeCnAttachAcpMsgNasMsg(
                                    LRRC_LNAS_MSG_STRU           *pRcvMsg,
                                    VOS_UINT8                  *pucRcvCnNasMsg,
                                    VOS_UINT32                  ulLength,
                                    NAS_EMM_CN_MSG_STRU        *pstCnMsgStru);
extern VOS_UINT32 NAS_EMM_DecodeCnMsgIEOptListParaChk(
                                    NAS_EMM_DECODE_IELIST_PARA_STRU *pstIEOptParaList
                                                                   );
extern VOS_VOID  NAS_EMM_DecodeCnMsgIEEdianChk(
                                    VOS_UINT32  *pulOptpos,
                                    VOS_UINT8   ucOptbits
                                          );
extern VOS_UINT32 NAS_EMM_DecodeIsLittleEdian(VOS_VOID);

extern VOS_UINT32 NAS_EMM_DecodeType0Tai(VOS_UINT32 *pulTaiLength,
                                       VOS_UINT32 ulTaiNumSum,
                                       VOS_UINT8  *pucTmpMsg,
                                       NAS_EMM_TA_LIST_STRU   *pstTaiStru);
extern VOS_UINT32 NAS_EMM_DecodeType1Tai(VOS_UINT32 *pulTaiLength,
                                       VOS_UINT32 ulTaiNumSum,
                                       VOS_UINT8  *pucTmpMsg,
                                       NAS_EMM_TA_LIST_STRU   *pstTaiStru);
extern VOS_UINT32 NAS_EMM_DecodeType2Tai(VOS_UINT32 *pulTaiLength,
                                       VOS_UINT32 ulTaiNumSum,
                                       VOS_UINT8  *pucTmpMsg,
                                       NAS_EMM_TA_LIST_STRU   *pstTaiStru);
extern VOS_UINT32  NAS_EMM_DecodeCnEmmStatusMsg(LRRC_LNAS_MSG_STRU           *pRcvMsg,
                                       VOS_UINT32                  ulLength,
                                       NAS_EMM_CN_MSG_STRU        *pstCnMsgStru);
extern VOS_UINT32  NAS_EMM_DecodeCnDownlinkNasTransportMsg(LRRC_LNAS_MSG_STRU           *pRcvMsg,
                                       VOS_UINT32                  ulLength,
                                       NAS_EMM_CN_MSG_STRU        *pstCnMsgStru);

extern VOS_UINT32  NAS_EMM_DecodeCnEmmInfoMsg(LRRC_LNAS_MSG_STRU          *pRcvMsg,
                                        VOS_UINT32                  ulLength,
                                        NAS_EMM_CN_MSG_STRU        *pstCnMsgStru);

extern VOS_UINT32  NAS_EMM_DecodeNwName(
                                        NAS_EMM_CN_NETWORK_NAME_STRU   *pstNwName,
                                        VOS_UINT8                      *pTmpRcvMsg,
                                        VOS_UINT32                     *pulIndex);
extern VOS_UINT32  NAS_EMM_DecodeDaylight(
                                        NAS_LMM_DAYLIGHT_SAVE_TIME_ENUM_UINT8       *pstDaylight,
                                        VOS_UINT8                      *pTmpRcvMsg,
                                        VOS_UINT32                     *pulIndex);
extern VOS_UINT32  NAS_EMM_DecodeLocalTimeZone(
                                        NAS_EMM_CN_TIMEZONE_UNITIME_STRU *pstLocalTZ,
                                        VOS_UINT8                        *pTmpRcvMsg,
                                        VOS_UINT32                       *pulIndex);
extern VOS_UINT32  NAS_EMM_DecodeTimeZone(
                                        NAS_EMM_CN_TIMEZONE_STRU       *pstTimeZone,
                                        VOS_UINT8                      *pTmpRcvMsg,
                                        VOS_UINT32                     *pulIndex);

extern VOS_UINT32  NAS_EMM_VerifyEpsUpdateRslt
(
    VOS_UINT8                           ucEPSUpdateRslt
);
extern VOS_UINT32  NAS_EMM_DecodeCnCsSerNotification
(
    LRRC_LNAS_MSG_STRU                 *pRcvMsg,
    VOS_UINT32                          ulLength,
    NAS_EMM_CN_MSG_STRU                *pstCnMsgStru
);

extern NAS_EMM_CN_CAUSE_ENUM_UINT8  NAS_EMM_DecodeCnEmmCause
(
    VOS_UINT8    ucEMMCau
);

extern VOS_UINT32  NAS_EMM_DecodeCnDownlinkGenericNasTransportMsg
(
    LRRC_LNAS_MSG_STRU                 *pRcvMsg,
    VOS_UINT32                          ulLength,
    NAS_EMM_CN_MSG_STRU                *pstCnMsgStru
);


extern VOS_VOID NAS_LMM_SndOmLogCnMsgDecodeFail
(
    NAS_EMM_CN_MSG_IE_TYPE_ENUM_UINT32                  enIeType,
    NAS_EMM_CN_MSG_DECODE_FAIL_CAUSE_ENUM_UINT32        enCause,
    VOS_UINT32                                          ulValue
);

extern VOS_UINT32  NAS_EMM_DecodeEsmMsgCon
(
    VOS_UINT8   *pRcvMsg,
    VOS_UINT32  *pulIndex,
    VOS_VOID    *pulUpRslt,
    NAS_EMM_CN_MSG_TYPE_ENUM_UINT8  enMsgTp
);
extern VOS_UINT32  NAS_EMM_DecodeTimer2
(
    VOS_UINT8   *pucRcvMsg,
    VOS_UINT32  *pulIndex,
    VOS_VOID    *pulUpRslt,
    NAS_EMM_CN_MSG_TYPE_ENUM_UINT8  enMsgTp
);
extern VOS_UINT32  NAS_EMM_DecodeCnAttachRejMsgNasMsg
(
    LRRC_LNAS_MSG_STRU           *pRcvMsg,
    VOS_UINT8                  *pucRcvCnNasMsg,
    VOS_UINT32                  ulLength,
    NAS_EMM_CN_MSG_STRU        *pstCnMsgStru
);

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

#endif /* end of MapsTemplate.h*/
