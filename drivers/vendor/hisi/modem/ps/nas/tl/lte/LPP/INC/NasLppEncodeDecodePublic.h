


#ifndef __NASLPPENCODE_H__
#define __NASLPPENCODE_H__




/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include    "vos.h"
#include    "LPSCommon.h"
#include    "PsCommonDef.h"
#include    "LPsOm.h"
#include    "NasLppPublic.h"




/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
/*****************************************************************************
  #pragma pack(*)    设置字节对齐方式
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif


/*****************************************************************************
  2 Macro
*****************************************************************************/
#define NAS_LPP_SLCT        (1)
#define NAS_LPP_NO_SLCT     (0)
#define NAS_LPP_TRUE        (TRUE)
#define NAS_LPP_FALSE       (FALSE)
//#define NAS_LPP_DECODE_FAIL (1)
//#define NAS_LPP_DECODE_SUCC (0)
//#define NAS_LPP_ENCODE_SUCC (0)
//#define NAS_LPP_ENCODE_FAIL (1)


/*Encode define start*/
#define NAS_LPP_GNSS_SUPPORT_LIST_MIN       (1)
#define NAS_LPP_GNSS_SUPPORT_LIST_MAX       (16)
#define NAS_LPP_GNSS_IDS_MIN                (1)
#define NAS_LPP_GNSS_IDS_MAX                (16)
#define NAS_LPP_GENERIC_ASSIST_DATA_SUPPORT_MIN     (1)
#define NAS_LPP_GENERIC_ASSIST_DATA_SUPPORT_MAX     (16)
#define NAS_LPP_INOSHER_MODEL_SUPPORT_MIN       (1)
#define NAS_LPP_INOSHER_MODEL_SUPPORT_MAX       (8)
#define NAS_LPP_SBASID_MAX                      (3)
#define NAS_LPP_CLOCK_MODEL_MIN                 (1)
#define NAS_LPP_CLOCK_MODEL_MAX                 (8)
#define NAS_LPP_ORBIT_MODEL_MIN                 (1)
#define NAS_LPP_ORBIT_MODEL_MAX                 (8)
#define NAS_LPP_ALMANAC_MODEL_MIN               (1)
#define NAS_LPP_ALMANAC_MODEL_MAX               (8)
#define NAS_LPP_UTC_MODEL_MIN                   (1)
#define NAS_LPP_UTC_MODEL_MAX                   (8)
#define NAS_LPP_EXT_ENUMERATED_BUTT             (0XFF)
/*Encode define end*/

/*Encode define start*/

/*Encode define end*/

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/



/*****************************************************************************
  4 Enum
*****************************************************************************/


enum NAS_LPP_TO_OM_MSG_ENUM
{
    NAS_LPP_TO_OM_MSG_BASE = 0,
    NAS_LPP_TO_OM_MSG_ASN_FAIL = NAS_LPP_TO_OM_MSG_BASE + 0X01,
};

enum NAS_LPP_ASN_MSG_IE_TYPE_ENUM
{
    NAS_LPP_EPDU_SEQUENCE,
    NAS_LPP_NORMAL_VALUE,
    NAS_LPP_SEQUENCE_OF,
    NAS_LPP_EXT_OBJECT,
    NAS_LPP_BIT_STRING,
    NAS_LPP_SEQUENCE,
    NAS_LPP_INTEGER,
    NAS_LPP_CHOICE,
    NAS_LPP_ENUM,
    NAS_LPP_CHAR,
    NAS_LPP_DECODE_TRANSACTIONID_ERROR,
    NAS_LPP_DECODE_REQCAPAGNSS_ERROR,
    NAS_LPP_DECODE_REQCAPCOMMONIES_ERROR,
    NAS_LPP_DECODE_REQCAPOTDOA_ERROR,
    NAS_LPP_DECODE_EPDUIDENTIFIER_ERROR,
    NAS_LPP_DECODE_EPDUBODY_ERROR,
    NAS_LPP_DECODE_REQCAPR9IES_ERROR,
    NAS_LPP_DECODE_PROASSISTCOMIES_ERROR,
    NAS_LPP_DECODE_PROASSISTAGNSS_ERROR,
    NAS_LPP_DECODE_GNSSCOMMONASSISTDATA_ERROR,
    NAS_LPP_DECODE_GNSSREFTIME_ERROR,
    NAS_LPP_DECODE_GNSSSYSTIME_ERROR,
    NAS_LPP_DECODE_GNSSTIMEIDSTR_ERROR,
    NAS_LPP_DECODE_GPSTOWASSISELEMENT_ERROR,
    NAS_LPP_DECODE_GNSSREFTIMEFORCELL_ERROR,
    NAS_LPP_DECODE_NETTIME_ERROR,
    NAS_LPP_DECODE_EUTRA_ERROR,
    NAS_LPP_DECODE_CELLEUTRANANDUTRA_ERROR,
    NAS_LPP_DECODE_PLMNIDENTITY_ERROR,
    NAS_LPP_DECODE_UTRA_ERROR,
    NAS_LPP_DECODE_FDD_ERROR,
    NAS_LPP_DECODE_TDD_ERROR,
    NAS_LPP_DECODE_GSM_ERROR,
    NAS_LPP_DECODE_CELLGLOBALGERAN_ERROR,
    NAS_LPP_DECODE_GNSSREFLOCATION_ERROR,
    NAS_LPP_DECODE_ELLIPSOIDPOINTWITHALTIANDUNCERTELLIPSOID_ERROR,
    NAS_LPP_DECODE_GNSSIONOMODEL_ERROR,
    NAS_LPP_DECODE_KLOBUCHARMODEL_ERROR,
    NAS_LPP_DECODE_NEQUICKMODEL_ERROR,
    NAS_LPP_DECODE_GNSSEARTHPARAM_ERROR,
    NAS_LPP_DECODE_GNSSGENERICASSISTDATAELEMENT_ERROR,
    NAS_LPP_DECODE_GNSSID_ERROR,
    NAS_LPP_GNSSIDWITHEXTNOCHOICE_ERROR,
    NAS_LPP_SABSIDWITHEXTNOCHOICE_ERROR,
    NAS_LPP_DECODE_SBASID_ERROR,
    NAS_LPP_DECODE_GNSSTIMEMODELREQELEMENT_ERROR,
    NAS_LPP_DECODE_GNSSTIMEMODEL_ERROR,
    NAS_LPP_DECODE_GNSSDIFFCORRECTION_ERROR,
    NAS_LPP_DECODE_DGNSSREFTIME_ERROR,
    NAS_LPP_DECODE_GNSSNAVIGATIONMODEL_ERROR,
    NAS_LPP_DECODE_GNSSNAVMODELLISTELEMENT_ERROR,
    NAS_LPP_DECODE_SVID_ERROR,
    NAS_LPP_DECODE_STANDARDCLOCKMODELLISTELEMENT_ERROR,
    NAS_LPP_DECODE_NAVCLOCKMODEL_ERROR,
    NAS_LPP_DECODE_CNAVCLOCKMODEL_ERROR,
    NAS_LPP_DECODE_GLONASSCLOCKMODEL_ERROR,
    NAS_LPP_DECODE_SBASCLOCKMODEL_ERROR,
    NAS_LPP_DECODE_KEPLERSET_ERROR,
    NAS_LPP_DECODE_NAVKEPLERSET_ERROR,
    NAS_LPP_DECODE_CNAVKEPLERSET_ERROR,
    NAS_LPP_DECODE_GLONASSECEF_ERROR,
    NAS_LPP_DECODE_SBASECEF_ERROR,
    NAS_LPP_DECODE_GNSSREALTIMEINTEGRITY_ERROR,
    NAS_LPP_DECODE_GNSSBADSIGNALLISTELEMENT_ERROR,
    NAS_LPP_DECODE_GNSSSIGNALIDS_ERROR,
    NAS_LPP_DECODE_GNSSBADBITSSATLISTELEMENT_ERROR,
    NAS_LPP_DECODE_GNSSSIGNALID_ERROR,
    NAS_LPP_DECODE_GNSSBADBITSSGNLISTELEMENT_ERROR,
    NAS_LPP_DECODE_DATABITSASSIT_ERROR,
    NAS_LPP_DECODE_GNSSACQUISITIONASSIT_ERROR,
    NAS_LPP_DECODE_GNSSACQUISITIONASSITLISTELEMENT_ERROR,
    NAS_LPP_DECODE_GNSSALMANAC_ERROR,
    NAS_LPP_DECODE_KEPLERIANALMANACSET_ERROR,
    NAS_LPP_DECODE_KEPLERIANNAVALMANAC_ERROR,
    NAS_LPP_DECODE_KEPLERIANREDUCEDALMANAC_ERROR,
    NAS_LPP_DECODE_KEPLERIANMIDIALMANAC_ERROR,
    NAS_LPP_DECODE_KEPLERIANGLONASS_ERROR,
    NAS_LPP_DECODE_ECEFSBASALMANAC_ERROR,
    NAS_LPP_ECELLIDERROR_ERROR,
    NAS_LPP_GNSSUTCMODEL_ERROR,
    NAS_LPP_DECODE_UTCMODEL1_ERROR,
    NAS_LPP_DECODE_UTCMODEL2_ERROR,
    NAS_LPP_DECODE_UTCMODEL3_ERROR,
    NAS_LPP_DECODE_UTCMODEL4_ERROR,
    NAS_LPP_GNSSAUXILIARYINFO_ERROR,
    NAS_LPP_DECODE_GNSSIDGPSELEMENT_ERROR,
    NAS_LPP_DECODE_GNSSIDGLONASSELEMENT_ERROR,
    NAS_LPP_GNSSERROR_ERROR,
    NAS_LPP_DECODE_GNSSERRORLOCATIONSERVER_ERROR,
    NAS_LPP_DECODE_GNSSTARGETDEVICE_ERROR,
    NAS_LPP_GNSSTARGETDEVICEERRORCAUSE_ERROR,
    NAS_LPP_DECODE_PROASSISTDATAR9IES_ERROR,
    NAS_LPP_DECODE_PROASSISTDATAOTDOA_ERROR,
    NAS_LPP_DECODE_OTDOAREFCELLINFO_ERROR,
    NAS_LPP_ARFCNEUTRANV9A0_ERROR,
    NAS_LPP_DECODE_PRSINFO_ERROR,
    NAS_LPP_PRSMUTINGINFOR9_ERROR,
    NAS_LPP_CPLENGTH_ERROR,
    NAS_LPP_DECODE_OTDOANEIGHBOURCELLINFOELEMENT_ERROR,
    NAS_LPP_ANTENNAPORTCONFIG_ERROR,
    NAS_LPP_PRSBANDWIDTH_ERROR,
    NAS_LPP_OTDOANEIGHBOURCELLINFOLIST_ERROR,
    NAS_LPP_OTDOANEIGHBOURCELLINFO_ERROR,
    NAS_LPP_DECODE_OTDOATARGETDEVICE_ERROR,
    NAS_LPP_OTDOATARGETDEVICEERRORCAUSE_ERROR,
    NAS_LPP_DECODE_OTDOAERRORLOCATIONSERVER_ERROR,
    NAS_LPP_OTDOAERROR_ERROR,
    NAS_LPP_MESSAGE_ERROR,
    NAS_LPP_DECODE_LOCATIONADDITONINFO_ERROR,
    NAS_LPP_ERRORCAUSE_ERROR,
    NAS_LPP_ABORTCAUSE_ERROR,
    NAS_LPP_LOCATIONINFOTYPE_ERROR,
    NAS_LPP_LOCATIONENVIRONMENT_ERROR,
    NAS_LPP_OTDOALOCATIONSERVERERRORCAUSE_ERROR,
    NAS_LPP_NUMDIFRAMES_ERROR,
    NAS_LPP_GNSSLOCATIONSERVERERRORCAUSE_ERROR,
    NAS_LPP_GNSSTIMEID_ERROR,
    NAS_LPP_DOPPLERUNCERTEXTR10_ERROR,
    NAS_LPP_EPDUERROR_ERROR,
    NAS_LPP_DGNSSSGNTYPELIST_ERROR,
    NAS_LPP_DECODE_CRITEXTABORTR9_ERROR,
    NAS_LPP_DECODE_OTDOAREQLOCATIONINFO_ERROR,
    NAS_LPP_DECODE_VERTICALACCURACY_ERROR,
    NAS_LPP_DECODE_HORIAZONTALACCURACY_ERROR,
    NAS_LPP_DECODE_ERRORIESR9_ERROR,
    NAS_LPP_DECODE_MESSAGE_ERROR,
    NAS_LPP_DECODE_ECELLIDREQLOCATIONINFO_ERROR,
    NAS_LPP_DECODE_AGNSSREQLOCATIONINFO_ERROR,
    NAS_LPP_DECODE_GNSSPOSITIONINGINSTRUCT_ERROR,
    NAS_LPP_DECODE_LOCATIONVELOCITYTYPES_ERROR,
    NAS_LPP_REPORTINGINTERVAL_ERROR,
    NAS_LPP_INTIATOR_ERROR,
    NAS_LPP_DECODE_DGNSSSGNTYPELISTELEMENT_ERROR,
    NAS_LPP_DECODE_RESPONSETIME_ERROR,
    NAS_LPP_CLOCKMODEL_ERROR,
    NAS_LPP_DECODE_LOCATIONQOS_ERROR,
    NAS_LPP_DECODE_LOCATIONCOORDINATETYPE_ERROR,
    NAS_LPP_DECODE_DGNSATLISTELEMENT_ERROR,
    NAS_LPP_MUTINGINFO_ERROR,
    NAS_LPP_DECODE_COMMONIESREQLOCATIONINFO_ERROR,
    NAS_LPP_DECODE_REQLOCINFOR9IES_ERROR,
    NAS_LPP_DECODE_LOCATIONTRIGGEREDREPORTING_ERROR,
    NAS_LPP_CELLID_ERROR,
    NAS_LPP_DECODE_GNSSMETHODS_ERROR,
    NAS_LPP_GNSSALMANACLISTELEMENT_ERROR,

    /* ENCODE IE */
    NAS_LPP_ENCODE_EPDUBODY_ERROR,
    NAS_LPP_EPDUIDENTIFIER_ERROR,
    NAS_LPP_EPDUSEQUENCE_ERROR,
    NAS_LPP_INITIATOR_ERROR,
    NAS_LPP_GNSSID_ERROR,
    NAS_LPP_SBASIDS_ERROR,
    NAS_LPP_ACCESSTYPES_ERROR,
    NAS_LPP_POSITIONMODE_ERROR,
    NAS_LPP_AGNSSIESPROVIDECAPABILITIESGNSSSUPPORTLIST_ERROR,
    NAS_LPP_GNSSSYSTEMTIME_ERROR,
    NAS_LPP_GNSSCOMMONASSISTANCEDATASUPPORTINONMODELSUPPORT_ERROR,
    NAS_LPP_SBASID_ERROR,
    NAS_LPP_GNSSNAVIGATIONMODELSUPPORT_ERROR,
    NAS_LPP_UTCMODELSUPPORT_ERROR,
    NAS_LPP_ALMANACSUPPORT_ERROR,
    NAS_LPP_OTDOAMODE_ERROR,
    NAS_LPP_GNSSGENERICASSISTANCEDATASUPPORT_ERROR,
    NAS_LPP_SUPBANDEUTRA_ERROR,
    NAS_LPP_SUPBANDLISTEUTRA_ERROR,
    NAS_LPP_SUPBANDLISTEUTRAV9A0_ERROR,
    NAS_LPP_SUPBANDEUTRAV9A0_ERROR,
    NAS_LPP_ADNEIGHBOURCELLINFOLISTR10_ERROR,
    NAS_LPP_FREQRSTDMEASUREMENTR10_ERROR,
    NAS_LPP_ECIDMEASSUPPORTED_ERROR,
    NAS_LPP_PROVIDECAPABILITYC1_ERROR,
    NAS_LPP_PROVIDECAPABILITY_ERROR,
    NAS_LPP_OTDOAREQASSISTDATA_ERROR,
    NAS_LPP_GNSSREFTIMEREQ_ERROR,
    NAS_LPP_GNSSTIMEMODELELEMENTREQ_ERROR,
    NAS_LPP_GNSSTIMEMODELLISTREQ_ERROR,
    NAS_LPP_SVID_ERROR,
    NAS_LPP_SATLISTRELATEDDATALISTELEMENT_ERROR,
    NAS_LPP_STORENAVLISTINFO_ERROR,
    NAS_LPP_ORBITMODELID_ERROR,
    NAS_LPP_CLOCKMODELID_ERROR,
    NAS_LPP_GNSSNAVMODELREQ_ERROR,
    NAS_LPP_GNSSDATABITASSISTREQ_ERROR,
    NAS_LPP_SATLISTRELATEDDATALIST_ERROR,
    NAS_LPP_GNSSDATABITREQSATLIST_ERROR,
    NAS_LPP_GNSSSSIGNALID_ERROR,
    NAS_LPP_PRIMARYCELLID_ERROR,
    NAS_LPP_GNSSUTCMODELREQ_ERROR,
    NAS_LPP_GNSSALMANACREQ_ERROR,
    NAS_LPP_GNSSGENREQASSISTDATA_ERROR,
    NAS_LPP_EXTREQUESTASSISTDATA_ERROR,
    NAS_LPP_ELLIPSOIDPOINTWITHALTITUDE_ERROR,
    NAS_LPP_ELLIPSOIDARC_ERROR,
    NAS_LPP_POLYGONPOINTS_ERROR,
    NAS_LPP_LOCTIONESTIMATE_ERROR,
    NAS_LPP_POLYGON_ERROR,
    NAS_LPP_ELLIPSOIDPOINTWITHALTITUDEANDELLIPOID_ERROR,
    NAS_LPP_REQUESTASSISTDATA_ERROR,
    NAS_LPP_HORIZONTALWITHVERTICALVELOCITY_ERROR,
    NAS_LPP_HORIZONTALVELCOCTIY_ERROR,
    NAS_LPP_ELLIPSOIDPOINTWITHUNCERTAINTYELLIPSE_ERROR,
    NAS_LPP_HORIZONTALWITHUNCERITANITY_ERROR,
    NAS_LPP_HORIZONTALWITHVELOCTIYANDUNCERTAAINTY_ERROR,
    NAS_LPP_VELOCITYESTIMATE_ERROR,
    NAS_LPP_LOCATONFAILURECAUSE_ERROR,
    NAS_LPP_PLMNIDENTITY_ERROR,
    NAS_LPP_CELLIDENTITYETRANANDUTRAN_ERROR,
    NAS_LPP_UTRANMODE_ERROR,
    NAS_LPP_EUTRA_ERROR,
    NAS_LPP_GSM_ERROR,
    NAS_LPP_REFFRAME_ERROR,
    NAS_LPP_GNSSSATMEASELMENT_ERROR,
    NAS_LPP_MEASREFTIME_ERROR,
    NAS_LPP_GNSSSATMEASLIST_ERROR,
    NAS_LPP_GNSSSGNMEASLIST_ERROR,
    NAS_LPP_GNSSSGNMEASELEMENT_ERROR,
    NAS_LPP_AGNSSLIST_ERROR,
    NAS_LPP_ENCODE_GNSSLOCATIONSERVERERRORCAUSE_ERROR,
    NAS_LPP_ENCODE_GNSSTARGETDEVICEERRORCAUSE_ERROR,
    NAS_LPP_ENCODE_OTDOALOCATIONSERVERERRORCAUSE_ERROR,
    NAS_LPP_ENCODE_OTDOATARGETDEVICEERRORCAUSE_ERROR,
    NAS_LPP_MEASLIST_ERROR,
    NAS_LPP_AGNSSERROR_ERROR,
    NAS_LPP_ARFCNVALUEEUTRAN_ERROR,
    NAS_LPP_OTDOASIGNALMEASINFO_ERROR,
    NAS_LPP_EARFCNREFV9A0_ERROR,
    NAS_LPP_ENCODE_OTDOAERROR_ERROR,
    NAS_LPP_PRIMARYCELLMEASUREDRSLT_ERROR,
    NAS_LPP_MEASRSLTLIST_ERROR,
    NAS_LPP_ECELLIDLOCATIONSERVERERRORCAUSE_ERROR,
    NAS_LPP_NEIGHBOURMEASELEMENT_ERROR,
    NAS_LPP_ECELLIDTARGETDEVICEERRORCAUSE_ERROR,
    NAS_LPP_ENCODE_MESSAGE_ERROR,
    NAS_LPP_LPPMSGBODY_ERROR,
    NAS_LPP_LPPMSGC1_ERROR,
    NAS_LPP_ERRORMESSAGE_ERROR,
    NAS_LPP_ERRORR9IES_ERROR,
    NAS_LPP_COMMONIESERROR_ERROR,
    NAS_LPP_EXTABORTMESSAGE_ERROR,
    NAS_LPP_COMMONIESABORT_ERROR,
    NAS_LPP_C1EXTABORTMESSAGE_ERROR,
    NAS_LPP_NEIGHBOURMEASLIST_ERROR
};
typedef VOS_UINT32  NAS_LPP_ASN_MSG_IE_TYPE_ENUM_UINT32;
enum NAS_LPP_ASN_MSG_ERR_CAUSE_ENUM
{
    NAS_LPP_EXT_OBJECT_BIT_WARNING,
    NAS_LPP_EXT_OBJECT_BIT_ERROR,
    NAS_LPP_CHOICE_EXT_OBJECT_WARNING,
    NAS_LPP_SEQUENCE_OF_NUM_OUT_OF_RANGE,
    NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
    NAS_LPP_EPDU_SEQUENCE_LEN_ERROR,
    NAS_LPP_NORMAL_VALUE_BIT_ERROR,
    NAS_LPP_BIT_STRING_LEN_ERROR,
    NAS_LPP_CHOICE_OUT_OF_RANGE,
    NAS_LPP_ENUM_OUT_OF_RANGE_WARNING,
    NAS_LPP_ENUM_OUT_OF_RANGE_ERROR,
    NAS_LPP_EMPTY_POINT,
    NAS_LPP_CHAR_LEN_ERROR,
    NAS_LPP_CHOICE_EXT_OBJECT_ERROR,
    NAS_LPP_NORMAL_VALUE_LARGE_WARNING,
    NAS_LPP_NORMAL_VALUE_LARGE_ERROR,
    NAS_LPP_OCTET_LEN_OUT_OF_RANGE
};
typedef VOS_UINT32  NAS_LPP_ASN_MSG_ERROR_CAUSE_ENUM_UINT32;
enum NAS_LPP_DECODE_CAUSE_ENUM
{
    NAS_LPP_DECODE_SUCC = 0,                                    /*成功*/
    NAS_LPP_DECODE_FAIL,                                        /*失败*/
    /*公共错误*/
    NAS_LPP_DECODE_NULL_PTR,                                    /*空指针，不大可能用到,严格意义上，解码不可能有空指针*/
    /*MsgHeaderError，映射到LPP error空口中的头错误*/
    NAS_LPP_DECODE_MSG_HEADER_ERROR_INCORRECT_VALUE,            /*消息头值不正确*/
    NAS_LPP_DECODE_MSG_HEADER_ERROR_LOGIC_ABNORMAL,             /*消息头的语义错误，这一块错误后续可扩展，在流程中进一步细分*/
    /*IncorrectError，映射到LPP error不正确值的错误*/
    NAS_LPP_DECODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR,         /*整型值不正确*/
    NAS_LPP_DECODE_MSG_VALUE_ERROR_ENUM_VALUE_ERROR,            /*枚举值不正确*/
    NAS_LPP_DECODE_MSG_VALUE_ERROR_STRING_VALUE_ERROR,          /*STRING类型的错误， 包括*/
    NAS_LPP_DECODE_MSG_VALUE_ERROR_SEQUENCE_OF_LEN_ERROR,       /*结构体数组的有效长度超限*/
    NAS_LPP_DECODE_MSG_VALUE_ERROR_EXT_IE_LEN_ERROR,            /*结构体有扩展的项,或者枚举扩展项的长度太长，超过了65535*/
    NAS_LPP_DECODE_MSG_VALUE_ERROR_CHAR_LEN_ERROR,              /*字符型变量长度不正确*/
    NAS_LPP_DECODE_MSG_VALUE_ERROR_CHOICE_ERROR,                /*choice值超过范围*/

    /*MsgBodyError，映射到LPP error消息体错误*/
    NAS_LPP_DECODE_MSG_BODY_ERROR_HAVE_EXT_IE_BUT_DONOT_TAKE,   /*有扩展的结构体，有必选的扩展项，但是没有选中*/
    NAS_LPP_DECODE_MSG_BODY_ERROR_TOTOAL_LEN_MISMATCH,          /*解码的总长度跟解码之后的总长度不匹配*/
    NAS_LPP_DECODE_MSG_BODY_ERROR_OPTION_IE_BECOME_COERCIVE_IE, /*某一信元为可选信元，但是某些流程中是必选信元没有带过来*/
    NAS_LPP_DECODE_MSG_BODY_ERROR_OPTION_IE_LV_VALUE_MISMATCH,  /*扩展项L+V的值不匹配*/
    NAS_LPP_DECODE_MSG_BODY_ERROR_VALUE_ERROR_IN_CERTAIN_PROCESS,   /*在某些流程中，某些信元的值一定不对，这种也算消息体错误*/
    NAS_LPP_DECODE_MSG_BODY_ERROR_TOO_SHORT,                    /*消息体太短*/
    NAS_LPP_DECODE_MSG_BODY_ERROR_TYPE_NON_EXIST,               /*消息类型不存在*/
    /*EpuduError, 映射到LPP error中的epdu错误*/
    NAS_LPP_DECODE_MSG_EPDU_ERROR_VALUE_ERROR,                  /*EPDU中值解码错误*/
    /*Undefined, 映射到LPP error中的undefined错误*/
    NAS_LPP_DECODE_MSG_UNDEFINED_ERROR,                         /*除开上面错误状态之外的状态*/

    NAS_LPP_DECODE_MSG_ERROR_BUTT
};
typedef VOS_UINT32  NAS_LPP_CAUSE_DECODE_CAUSE_ENUM_UINT32;

enum NAS_LPP_ENCODE_CAUSE_ENUM
{
    NAS_LPP_ENCODE_SUCC = 0,                                    /*成功*/
    NAS_LPP_ENCODE_FAIL,                                        /*失败*/
    /*公共错误*/
    NAS_LPP_ENCODE_NULL_PTR,                                    /*空指针，不大可能用到,严格意义上，解码不可能有空指针*/
    /*MsgHeaderError，映射到LPP error空口中的头错误*/
    NAS_LPP_ENCODE_MSG_HEADER_ERROR_INCORRECT_VALUE,            /*消息头值不正确*/
    NAS_LPP_ENCODE_MSG_HEADER_ERROR_LOGIC_ABNORMAL,             /*消息头的语义错误，这一块错误后续可扩展，在流程中进一步细分*/
    /*IncorrectError，映射到LPP error不正确值的错误*/
    NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR,         /*整型值不正确*/
    NAS_LPP_ENCODE_MSG_VALUE_ERROR_ENUM_VALUE_ERROR,            /*枚举值不正确*/
    NAS_LPP_ENCODE_MSG_VALUE_ERROR_CHOICE_VALUE_ERROR,          /*选择体值不正确*/
    NAS_LPP_ENCODE_MSG_VALUE_ERROR_STRING_VALUE_ERROR,          /*STRING类型的错误， 包括*/
    NAS_LPP_ENCODE_MSG_VALUE_ERROR_SEQUENCE_OF_LEN_ERROR,       /*结构体数组的有效长度超限*/
    NAS_LPP_ENCODE_MSG_VALUE_ERROR_EXT_IE_LEN_ERROR,            /*结构体有扩展的项,或者枚举扩展项的长度太长，超过了65535*/
    NAS_LPP_ENCODE_MSG_VALUE_ERROR_CHAR_LEN_ERROR,              /*字符型变量长度不正确*/
    NAS_LPP_ENCODE_MSG_VALUE_ERROR_CHOICE_ERROR,                /*choice值超过范围*/

    /*MsgBodyError，映射到LPP error消息体错误*/
    NAS_LPP_ENCODE_MSG_BODY_ERROR_HAVE_EXT_IE_BUT_DONOT_TAKE,   /*有扩展的结构体，有必选的扩展项，但是没有选中*/
    NAS_LPP_ENCODE_MSG_BODY_ERROR_TOTOAL_LEN_MISMATCH,          /*解码的总长度跟解码之后的总长度不匹配*/
    NAS_LPP_ENCODE_MSG_BODY_ERROR_OPTION_IE_BECOME_COERCIVE_IE, /*某一信元为可选信元，但是某些流程中是必选信元没有带过来*/
    NAS_LPP_ENCODE_MSG_BODY_ERROR_VALUE_ERROR_IN_CERTAIN_PROCESS,   /*在某些流程中，某些信元的值一定不对，这种也算消息体错误*/
    NAS_LPP_ENCODE_MSG_BODY_ERROR_TYPE_NON_EXIST,               /*消息类型不存在*/
    /*EpuduError, 映射到LPP error中的epdu错误*/
    NAS_LPP_ENCODE_MSG_EPDU_ERROR_VALUE_ERROR,                  /*EPDU中值错误*/
    /*Undefined, 映射到LPP error中的undefined错误*/
    NAS_LPP_ENCODE_MSG_UNDEFINED_ERROR,                         /*除开上面错误状态之外的状态*/

    NAS_LPP_ENCODE_MSG_ERROR_BUTT
};
typedef VOS_UINT16  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16;

enum LPP_ENCODE_ERR_STR_ENUM
{
    LPP_ENCODE_ERR_STR_TRANSATION_ID = 0,
    LPP_ENCODE_ERR_STR_SEQUENCE_NUMBER,
    LPP_ENCODE_ERR_STR_ACKNOWLEGMENT,
    LPP_ENCODE_ERR_STR_PROVIDE_CAPABILITIES,
    LPP_ENCODE_ERR_STR_BUTT
};
typedef VOS_UINT32   LPP_ENCODE_ERR_STR_ENUM_ENUM_UINT32;

enum LPP_DECODE_ERR_STR_ENUM
{
    LPP_DECODE_ERR_STR_TRANSATION_ID = 0,
    LPP_DECODE_ERR_STR_SEQUENCE_NUMBER,
    LPP_DECODE_ERR_STR_ACKNOWLEGMENT,
    LPP_DECODE_ERR_STR_REQ_CAPABILITIES,
    LPP_DECODE_ERR_STR_BUTT
};
typedef VOS_UINT32   LPP_ENCODE_ERR_STR_ENUM_UINT32;

enum LPP_ENCODE_DECODE_ERR_ENUM
{
    LPP_ENCODE_DECODE_ERR_VALUE_OUT_OF_RANGE = 0, /*表示编解码的时候值超出范围*/
    LPP_ENCODE_DECODE_ERR_PROTOCOL_MISMATCH,      /*表示协议版本不一致*/
    LPP_DECODE_DECODE_ERR_MSG_EXCEED_TOTOL_LEN,   /*表示总长度超长*/
    LPP_ENCODE_DECODE_ERR_NULL_POINTER,           /*表示入参空指针*/
    LPP_DECODE_DECODE_ERR_BUTT
};
typedef VOS_UINT32   LPP_ENCODE_DECODE_ERR_ENUM_UINT32;



/*****************************************************************************
  5 STRUCT
*****************************************************************************/

typedef struct
{
    LPP_ENCODE_DECODE_ERR_ENUM_UINT32       enEncodeDecodeErrType;      /*表示错误类型*/
    VOS_UINT8                               aucAbortIeName[16];         /*异常IE名字*/
    VOS_UINT32                              ulMinValue;                 /*取值的下界*/
    VOS_UINT32                              ulMaxValue;                 /*取值的上界*/
    VOS_UINT32                              ulLineNo;                   /*出错时候的行号*/
    VOS_UINT32                              ulErrPos;                   /*出现解码错误时刻的位置*/
    VOS_UINT32                              ulErrByte;
    VOS_UINT8                               ucProtocolVersionOfCn;      /*网络侧协议版本*/
    VOS_UINT8                               ucExtIeNum;                 /*网络侧扩展信元的计数*/
    VOS_UINT8                               aucRsv[2];
    VOS_UINT32                              aulRsv[10];                 /*保留项，便于后续扩展*/
} LPP_DEBUG_INFO_STRU;


/*L模使用*/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
}PS_HEADER_STRU;

/*L模使用
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    VOS_UINT16                          usOpId;
    VOS_UINT8                           aucRsv[2];
}LHPA_MSG_HEADER_STRU;*/

typedef struct
{
    PS_HEADER_STRU                                          stMsgHeader;     /*_H2ASN_Skip*/
    NAS_LPP_ASN_MSG_IE_TYPE_ENUM_UINT32                     enIeType;
    NAS_LPP_ASN_MSG_ERROR_CAUSE_ENUM_UINT32                 enCause;
    VOS_UINT32                                              ulBitPosValue;
    VOS_UINT32                                              ulLineNum;
    VOS_UINT32                                              ulRsvData;
}NAS_LPP_ASN_FAIL_STRU;





/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/

/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern VOS_VOID NAS_LPP_EncodeBitSteam(
                                    VOS_UINT8       *pTarget,
                                    VOS_UINT16      *pulPos,
                                    VOS_UINT16      usLen,
                                    VOS_UINT8       *pSource);
extern VOS_VOID NAS_LPP_SetBitStreamFromStream(
                                    VOS_UINT8       *pTarget,
                                    VOS_UINT16      ulPos,
                                    VOS_UINT16      usLen,
                                    VOS_UINT8       *pSource);


extern VOS_UINT32 NAS_LPP_GetParamFromBitStream(
                                            VOS_UINT8       aArr[],
                                            VOS_UINT32      ulPos,
                                            VOS_UINT8       usLen);
extern VOS_UINT32 NAS_LPP_GetDataFromBitStream(
                                            VOS_UINT8       aArr[],
                                            VOS_UINT32      *ulPos,
                                            VOS_UINT8       usLen);

extern VOS_UINT32 NAS_LPP_GetLongDataFromBitStream(
                                                VOS_UINT8       aArr[],
                                                VOS_UINT32      *ulPos,
                                                VOS_UINT8       usLen,
                                                VOS_UINT64      *pllDestData);
extern VOS_UINT32 NAS_LPP_GetLongBitFromBitStream(
                                                VOS_UINT8       aArr[],
                                                VOS_UINT32      *ulPos,
                                                VOS_UINT16       usLen,
                                                VOS_UINT8      *pllDestData);

extern VOS_UINT16 NAS_LPP_EncodeExtBit(
                        VOS_UINT16      *pBitPos,
                        VOS_UINT8       *pEncodeOutMsg);
extern VOS_VOID NAS_LPP_EncodeBitsLess8(
                                    VOS_UINT8       *pEncodeOutMsg,
                                    VOS_UINT16      *pBitPos,
                                    VOS_UINT16      usLen,
                                    VOS_UINT8       ucSource);

extern VOS_UINT32  NAS_LPP_DecodeExtIeWithPartValid(
                        VOS_UINT8                               *pDecodeBitStream,
                        VOS_UINT32                              *pCurrentBitPos,
                        VOS_UINT32                              ulInvalidExtIeLen);

extern VOS_UINT32  NAS_LPP_Decode_ExtChoiceCellId(
                                    VOS_UINT8                       *pDecodeBitStream,
                                    VOS_UINT32                      *pCurrentBitPos,
                                    VOS_UINT8                       ucLen,
                                    VOS_UINT32                      *pExtChoiceValue);

extern VOS_VOID NAS_LPP_EncodeEncodeLongData(
                                    VOS_UINT8       *pEncodeOutMsg,
                                    VOS_UINT16      *pBitPos,
                                    VOS_UINT16      usLen,
                                    VOS_UINT32      ulSource);

extern  VOS_VOID    NAS_LPP_ASN_FAIL_Message(
                                    VOS_UINT32          ucIEType,
                                    VOS_UINT32          ucIEErrorType,
                                    VOS_UINT32          ulBitPos,
                                    VOS_UINT32          ulLineNum,
                                    VOS_UINT32          ulRsv);

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

#endif











































