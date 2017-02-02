
#ifndef _LPPMTAINTERFACE_H_
#define _LPPMTAINTERFACE_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/*******************************************************************************
 *                          ��Ҫ������ͷ�ļ�.
*******************************************************************************/
#include "vos.h"

/*���ݲ�ͬ��Ʒ�ֱ������ͬ�ĺ궨����ļ� */
/*******************************************************************************
 *                      �ֽڶ��뷽ʽ: һ�ֽڶ���.
*******************************************************************************/
//#pragma pack(1)
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(1)
#else
 #pragma pack(push, 1)
#endif


/*****************************************************************************
  2 Macro
*****************************************************************************/
#define LPP_MAX_GNSS_SUPPORT_ELEMENT_NUM            (16)
#define LPP_MAX_GNSS_GENERIC_ASSISTANCE_DATA_SUPPORT_ELEMENT_NUM        (16)
#define LPP_MAX_SUPPORTED_BAND_EUTRA_NUM            (64)
#define LPP_MAX_EPDU_NUM                            (16)
#define LPP_MAX_EPDU_NAME_LEN                       (32)
#define LPP_MAX_EPDU_BODY_LEN                       (256)                   /* Э��û�����峤�� */
#define LPP_MCC_LENGTH                              (3)
#define LPP_MNC_LENGTH                              (3)
#define LPP_MAX_REF_TIME_FOR_CELL_LEN               (16)
#define LPP_MAX_GPS_TOW_ASSIT_LENGTH                (64)
#define LPP_MAX_GEN_ASSIT_DATA_ELEMENT_LEN          (16)
#define LPP_MAX_GNSS_TIME_MODEL_ELEMENT_LEN         (15)
#define LPP_MAX_FREQ_LAYERS_LEN                     (3)
#define LPP_MAX_POLYGON_POINTS_LEN                  (15)
#define LPP_MAX_GNSS_SAT_MEAS_ELMENT_LEN            (64)
#define LPP_MAX_GNSS_SGN_MEAS_ELMENT_LEN            (8)
#define LPP_MAX_GNSS_MEAS_FOR_ONE_GNSS_LEN          (16)
#define LPP_MAX_NEIGHBOUR_MEAS_ELEMENT_LEN          (24)
#define LPP_MAX_MEAS_RSLT_ELMENT_LEN                (32)
#define LPP_MAX_GNSS_TIME_MODE_ELMENT_LEN           (15)
#define LPP_MAX_DGNSS_CORRECT_ELEMENT_LEN           (64)
#define LPP_MAX_DGNSS_SGN_TYPE_ELEMENT_LEN          (3)
#define LPP_MAX_STANDARD_CLOCK_ELEMENT_LEN          (2)
#define LPP_MAX_NAV_MODEL_SAT_ELEMENT_LEN           (64)
#define LPP_MAX_BAD_SIGNAL_ELEMENT_LEN              (64)
#define LPP_MAX_GNSS_DATA_BITS_LEN                  (128)
#define LPP_MAX_GNSS_DATA_BITS_SGN_ELEMENT_LEN      (8)
#define LPP_MAX_GNSS_DATA_BITS_SAT_ELEMENT_LEN      (64)
#define LPP_MAX_GNSS_ACQUSITON_ASSIST_ELMENT_LEN    (64)
#define LPP_MAX_GNSS_ALMANAC_ELMENT_LEN             (64)
#define LPP_MAX_GNSS_ID_GLONASS_SAT_ELEMENT_LEN     (64)
#define LPP_MAX_GNSS_ID_GPS_SAT_ELEMENT_LEN         (64)
#define LPP_MAX_GNSS_GENERIC_ASSIST_DATA_ELEMENT_LEN    (16)
#define LPP_MAX_GPS_TOW_ASSIST_ELMENT_LEN           (64)
#define LPP_MAX_GNSS_REF_TIME_FOR_CELLS_LEN         (16)
#define LPP_MAX_OTDOA_NEIGHBOUR_CELL_INFO_ELMENT_LEN    (24)
#define LPP_MAX_SAT_LIST_RELATED_DATA_ELEMENT_LEN   (64)
#define LPP_SV_REQ_LIST_LEN                         (8)
#define LPP_MAX_CLOCK_MODEL_ID_PRELIST_LEN          (8)
#define LPP_MAX_ORBIT_MODEL_ID_PREFLIST_LEN         (8)
#define LPP_MAX_GNSS_DATA_BITS_REQ_SAT_LIST_LEN     (64)
#define LPP_MAX_GNSS_GENERIC_ASSIST_DATA_SUPPORT_ELMENT_LEN (16)
#define LPP_DECODE_EXT_CHOICE_INVALID_VALUE         (0xFF)
#define LPP_MTA_MSG_HDR  0
#define MTA_LPP_MSG_HDR  0
#define LPP_MAX_EARFCN   65535



/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/


enum LPP_MTA_MSG_TYPE_ENUM
{
    /*��Ϣԭ��*/
    /*LPP���͸�MTA����Ϣԭ��*/
    ID_LPP_MTA_GNSS_CAP_REQ                     = (LPP_MTA_MSG_HDR),        /* _H2ASN_MsgChoice LPP_MTA_GNSS_CAPABITY_REQ_STRU*/
    ID_LPP_MTA_GNSS_ASSISTDATA_CNF              = (LPP_MTA_MSG_HDR + 0x1),  /* _H2ASN_MsgChoice LPP_MTA_GNSS_PROVIDE_ASSIST_DATA_CNF_STRU*/
    ID_LPP_MTA_GNSS_LOC_INFO_REQ                = (LPP_MTA_MSG_HDR + 0x2),  /* _H2ASN_MsgChoice LPP_MTA_GNSS_LOCATION_INFO_REQ_STRU*/


    /*MTA���͸�LPP����Ϣԭ��*/
    ID_MTA_LPP_GNSS_CAP_CNF                     = (MTA_LPP_MSG_HDR),        /* _H2ASN_MsgChoice MTA_LPP_GNSS_PROVIDE_CAPABITY_CNF_STRU*/
    ID_MTA_LPP_GNSS_ASSISTDATA_REQ              = (MTA_LPP_MSG_HDR + 0x1),  /* _H2ASN_MsgChoice MTA_LPP_GNSS_ASSIST_DATA_REQ_STRU*/
    ID_MTA_LPP_GNSS_LOC_INFO_CNF                = (MTA_LPP_MSG_HDR + 0x2),  /* _H2ASN_MsgChoice MTA_LPP_GNSS_RROVIDE_LOCATION_INFO_CNF_STRU*/

    ID_LPP_MTA_GNSS_BUTT
};
typedef VOS_UINT32 LPP_MTA_MSG_TYPE_ENUM_UINT32;
enum LPP_COMMON_IES_ABORT_ENUM
{
    LPP_COMMON_IES_ABORT_UNDEFINED = 0,
    LPP_COMMON_IES_ABORT_STOP_PERIOD_REPORT,
    LPP_COMMON_IES_ABORT_TARGET_DEVCIE_ABORT,
    LPP_COMMON_IES_ABORT_NET_WORK_ABORT,
    LPP_COMMON_IES_ABORT_BUTT
};
typedef VOS_UINT8  LPP_COMMON_IES_ABORT_ENUM_UINT8;


enum LPP_ECID_TARGET_DEVICE_ERROR_CAUSE_ENUM
{
    LPP_ECID_TARGET_DEVICE_ERROR_CAUSE_UNDEFINED = 0,
    LPP_ECID_TARGET_DEVICE_ERROR_CAUSE_REQ_MEAS_NOT_AVAIL,
    LPP_ECID_TARGET_DEVICE_ERROR_CAUSE_NOT_ALL_REQ_POSSIBLE,
    LPP_ECID_TARGET_DEVICE_ERROR_CAUSE_BUTT
};
typedef VOS_UINT32  LPP_ECID_TARGET_DEVICE_ERROR_CAUSE_ENUM_UINT32;


enum LPP_ECID_LOCATION_SERVER_ERROR_CAUSE_ENUM
{
    LPP_ECID_LOCATION_SERVER_ERROR_CAUSE_UNDEFINED = 0,
    LPP_ECID_LOCATION_SERVER_ERROR_CAUSE_BUTT
};
typedef VOS_UINT32  LPP_ECID_LOCATION_SERVER_ERROR_CAUSE_ENUM_UINT32;


enum LPP_MPATH_DET_ENUM
{
    LPP_MPATH_DET_NOT_MEAS = 0,
    LPP_MPATH_DET_LOW,
    LPP_MPATH_DET_MEDIUM,
    LPP_MPATH_DET_HIGH,
    LPP_MPATH_DET_BUTT
};
typedef VOS_UINT32  LPP_MPATH_DET_ENUM_UINT32;


enum LPP_LOCATION_FAILURE_CAUSE_ENUM
{
    LPP_LOCATION_FAILURE_CAUSE_UNDEFINED = 0,
    LPP_LOCATION_FAILURE_CAUSE_REQ_METHOD_NOT_SUPPORT,
    LPP_LOCATION_FAILURE_CAUSE_POSITON_METHOD_FAILURE,
    LPP_LOCATION_FAILURE_CAUSE_PERIOD_LOCATION_MEAS_NOT_AVAILABLE,
    LPP_LOCATION_FAILURE_CAUSE_BUTT
};
typedef VOS_UINT32  LPP_LOCATION_FAILURE_CAUSE_ENUM_UINT32;


enum LPP_VERTICAL_DIRECT_ENUM
{
    LPP_VERTICAL_DIRECT_UPWARD = 0,
    LPP_VERTICAL_DIRECT_DOWNWARD,
    LPP_VERTICAL_DIRECT_BUTT
};
typedef VOS_UINT32      LPP_VERTICAL_DIRECT_ENUM_UINT32;


enum LPP_ENVIRONMENT_ENUM
{
    LPP_ENVIRONMENT_BAD_AREA = 0,
    LPP_ENVIRONMENT_NOT_BAD_AREA,
    LPP_ENVIRONMENT_MIXED_AREA,
    LPP_ENVIRONMENT_BUTT
};
typedef VOS_UINT8  LPP_ENVIRONMENT_ENUM_UINT8;


enum LPP_ADDITON_REPORT_ENUM
{
    LPP_ADDITON_REPORT_ONLY_RETURN_INFO_REQ = 0,
    LPP_ADDITON_REPORT_MAY_RETURN_ADDITON_INFO,
    LPP_ADDITON_REPORT_BUTT
};
typedef VOS_UINT8  LPP_ADDITON_REPORT_ENUM_UNIT8;


enum LPP_REPORT_INTERVAL_ENUM
{
    LPP_REPORT_INTERVAL_NO_PERIOD_REPORT = 0,
    LPP_REPORT_INTERVAL_RI0_25,
    LPP_REPORT_INTERVAL_RI0_5,
    LPP_REPORT_INTERVAL_RI1,
    LPP_REPORT_INTERVAL_RI2,
    LPP_REPORT_INTERVAL_RI4,
    LPP_REPORT_INTERVAL_RI8,
    LPP_REPORT_INTERVAL_RI16,
    LPP_REPORT_INTERVAL_RI32,
    LPP_REPORT_INTERVAL_RI64,
    LPP_REPORT_INTERVAL_BUTT
};
typedef VOS_UINT32  LPP_REPORT_INTERVAL_ENUM_UINT32;


enum LPP_REPORT_AMOUNT_ENUM
{
    LPP_REPORT_AMOUNT_RA1 = 0,
    LPP_REPORT_AMOUNT_RA2,
    LPP_REPORT_AMOUNT_RA4,
    LPP_REPORT_AMOUNT_RA8,
    LPP_REPORT_AMOUNT_RA16,
    LPP_REPORT_AMOUNT_RA32,
    LPP_REPORT_AMOUNT_RA64,
    LPP_REPORT_AMOUNT_RA_INFINITY,
    LPP_REPORT_AMOUNT_BUTT
};
typedef VOS_UINT32  LPP_REPORT_AMOUNT_ENUM_UINT32;


enum LPP_LOCATION_INFO_TYPE_ENUM
{
    LPP_LOCATION_INFO_TYPE_ESTIMATE_REQUIRED = 0,
    LPP_LOCATION_INFO_TYPE_MEASURE_REQURIED,
    LPP_LOCATION_INFO_TYPE_ESTIMATE_PREFERRED,
    LPP_LOCATION_INFO_TYPE_MEASURE_PREFERRED,
    LPP_LOCATION_INFO_TYPE_BUTT
};
typedef VOS_UINT8  LPP_LOCATION_INFO_TYPE_ENUM_UINT8;


enum LPP_SBAS_ID_ENUM
{
    LPP_SBAS_ID_WAAS     = 0,
    LPP_SBAS_ID_EGNOS,
    LPP_SBAS_ID_MSAS,
    LPP_SBAS_ID_GAGAN,
    LPP_SBAS_ID_BUTT
};
typedef VOS_UINT8 LPP_SBAS_ID_ENUM_UINT8;


enum LPP_BSALIGN_ENUM
{
    LPP_BSALIGN_TRUE = 0,
    LPP_BSALIGN_FALSE,
    LPP_BSALIGN_BUTT
};
typedef VOS_UINT32 LPP_BSALIGN_ENUM_UINT32;


enum LPP_LATITUDE_DIR_ENUM
{
    LPP_LATITUDE_DIR_HEITHT = 0,
    LPP_LATITUDE_DIR_DEPTH,
    LPP_LATITUDE_DIR_BUTT
};
typedef VOS_UINT8   LPP_LATITUDE_DIR_ENUM_UINT8;


enum LPP_LATITUDE_SIGN_ENUM
{
    LPP_LATITUDE_SIGN_NORTH = 0,
    LPP_LATITUDE_SIGN_SOUTH,
    LPP_LATITUDE_SIGN_BUTT
};
typedef VOS_UINT8   LPP_LATITUDE_SIGN_ENUM_UINT8;


enum LPP_INITIATOR_TYPE_ENUM
{
    LPP_INITIATOR_TYPE_LOCATION_SERVER  = 0,
    LPP_INITIATOR_TYPE_TARGET_DEVICE,

    LPP_INITIATOR_TYPE_BUTT
};
typedef VOS_UINT8  LPP_INITIATOR_TYPE_ENUM_UINT8;


enum LPP_GNSS_ID_ENUM
{
    LPP_GNSS_ID_GPS                     = 0,
    LPP_GNSS_ID_SBAS                    = 1,
    LPP_GNSS_ID_QZSS                    = 2,
    LPP_GNSS_ID_GALILEO                 = 3,
    LPP_GNSS_ID_GLONASS                 = 4,

    LPP_GNSS_ID_BUTT
};
typedef VOS_UINT8  LPP_GNSS_ID_ENUM_UINT8;


enum LPP_CONFIDENCE_SUPPORT_R10_ENUM
{
    LPP_CONFIDENCE_SUPPORT_R10_TRUE     = 0,

    LPP_CONFIDENCE_SUPPORT_R10_BUTT
};
typedef VOS_UINT8  LPP_CONFIDENCE_SUPPORT_R10_ENUM_UINT8;


enum LPP_DOPPLER_UNCERTAINTY_EXT_SUPPORT_R10_ENUM
{
    LPP_DOPPLER_UNCERTAINTY_EXT_SUPPORT_R10_TRUE     = 0,

    LPP_DOPPLER_UNCERTAINTY_EXT_SUPPORT_R10_BUTT
};
typedef VOS_UINT8  LPP_DOPPLER_UNCERTAINTY_EXT_SUPPORT_R10_ENUM_UINT8;


enum LPP_INTER_FREQ_RSTD_MEASUREMENT_R10_ENUM
{
    LPP_INTER_FREQ_RSTD_MEASUREMENT_R10_SUPPORT     = 0,

    LPP_INTER_FREQ_RSTD_MEASUREMENT_R10_BUTT
};
typedef VOS_UINT32  LPP_INTER_FREQ_RSTD_MEASUREMENT_R10_ENUM_UINT32;
typedef VOS_UINT32  LPP_ADDITIONAL_NEIGH_CELL_INFO_LIST_R10_ENUM_UINT32;


enum LPP_DOPPLER_EXTR10_ENUM
{
    LPP_DOPPLER_EXTR10_D60 = 0,
    LPP_DOPPLER_EXTR10_D80,
    LPP_DOPPLER_EXTR10_D100,
    LPP_DOPPLER_EXTR10_D120,
    LPP_DOPPLER_EXTR10_NO_INFO,
    LPP_DOPPLER_EXTR10_BUTT
};
typedef VOS_UINT8  LPP_DOPPLER_EXTR10_ENUM_UINT8;


enum LPP_GNSS_LOCATION_SERVER_ERROR_CAUSE_ENUM
{
    LPP_GNSS_LOCATION_SERVER_ERROR_CAUSE_UNDEFINED = 0,
    LPP_GNSS_LOCATION_SERVER_ERROR_UNDELIVERED_ASSIST_DATA_IS_NOT_SUPPORT_BY_SERVER,
    LPP_GNSS_LOCATION_SERVER_ERROR_UNDELIVERED_ASSIST_DATA_IS_SUPPORT_BUT_CURRENT_NOT_AVAIABLE,
    LPP_GNSS_LOCATION_SERVER_ERROR_BUTT
};
typedef VOS_UINT8  LPP_GNSS_LOCATION_SERVER_ERROR_CAUSE_ENUM_UINT8;


enum LPP_GNSS_LOCATION_TARGET_DEVICE_ERROR_CAUSE_ENUM
{
    LPP_GNSS_LOCATION_TARGET_DEVICE_ERROR_UNDEFINED = 0,
    LPP_GNSS_LOCATION_TARGET_DEVICE_ERROR_THREE_WERE_NOT_ENOUGH_SAT_RECEVIE,
    LPP_GNSS_LOCATION_TARGET_DEVICE_ERROR_ASSIST_DATA_MISSING,
    LPP_GNSS_LOCATION_TARGET_DEVICE_ERROR_NOT_ALL_REQ_MEAS_POSSIBLE,
    LPP_GNSS_LOCATION_TARGET_DEVICE_ERROR_BUTT
};
typedef VOS_UINT8 LPP_GNSS_LOCATION_TARGET_DEVICE_ERROR_CAUSE_ENUM_UINT8;


enum LPP_OTDOA_LOCATION_SERVER_ERROR_CAUSE_ENUM
{
    LPP_OTDOA_LOCATION_SERVER_ERROR_CAUSE_UNDEFINED = 0,
    LPP_OTDOA_LOCATION_SERVER_ERROR_ASSIST_DATA_IS_NOT_SUPPORT_BY_SERVER,
    LPP_OTDOA_LOCATION_SERVER_ERROR_ASSIST_DATA_IS_SUPPORT_BUT_CURRENT_NOT_AVAIABLE,
    LPP_OTDOA_LOCATION_SERVER_ERROR_BUTT
};
typedef VOS_UINT8  LPP_OTDOA_LOCATION_SERVER_ERROR_CAUSE_ENUM_UINT8;


enum LPP_OTDOA_LOCATION_TARGET_DEVICE_ERROR_CAUSE_ENUM
{
    LPP_OTDOA_LOCATION_TARGET_DEVICE_ERROR_UNDEFINED = 0,
    LPP_OTDOA_LOCATION_TARGET_DEVICE_ERROR_ASSIST_DATA_MISSING,
    LPP_OTDOA_LOCATION_TARGET_DEVICE_ERROR_UNABLE_TO_MEAS_REF_CELL,
    LPP_OTDOA_LOCATION_TARGET_DEVICE_ERROR_UNABLE_TO_MEAS_ANY_NEIGHBOUR_CELL,
    LPP_OTDOA_LOCATION_TARGET_DEVICE_ERROR_ATTEMP_BUT_UNABLE_TO_MEAS_SOME_NEIGHBOUR_CELL,
    LPP_OTDOA_LOCATION_TARGET_DEVICE_ERROR_BUTT
};
typedef VOS_UINT32 LPP_OTDOA_LOCATION_TARGET_DEVICE_ERROR_CAUSE_ENUM_UINT32;


enum LPP_ANTENNA_PORT_CONFIG_ENUM
{
    LPP_ANTENNA_PORT_CONFIG_PORTS1_OR_2 = 0,
    LPP_ANTENNA_PORT_CONFIG_PORTS4,
    LPP_ANTENNA_PORT_CONFIG_BUTT
};
typedef VOS_UINT8  LPP_ANTENNA_PORT_CONFIG_ENUM_UINT8;


enum LPP_CP_LENGTH_ENUM
{
    LPP_CP_LENGTH_NORMAL = 0,
    LPP_CP_LENGTH_EXTENDED,
    LPP_CP_LENGTH_BUTT
};
typedef VOS_UINT8  LPP_CP_LENGTH_ENUM_UINT8;


enum LPP_PRS_BAND_WITH_ENUM
{
    LPP_PRS_BAND_WITH_N6 = 0,
    LPP_PRS_BAND_WITH_N15,
    LPP_PRS_BAND_WITH_N25,
    LPP_PRS_BAND_WITH_N50,
    LPP_PRS_BAND_WITH_N75,
    LPP_PRS_BAND_WITH_N100,
    LPP_PRS_BAND_WITH_BUTT
};
typedef VOS_UINT8  LPP_PRS_BAND_WITH_ENUM_UINT8;


enum LPP_NUMDL_FRAMES_ENUM
{
    LPP_NUMDL_FRAMES_SF_1 = 0,
    LPP_NUMDL_FRAMES_SF_2,
    LPP_NUMDL_FRAMES_SF_4,
    LPP_NUMDL_FRAMES_SF_6,
    LPP_NUMDL_FRAMES_BUTT
};
typedef VOS_UINT8  LPP_NUMDL_FRAMES_ENUM_UINT8;


enum LPP_COMMON_IES_ERROR_ENUM
{
    LPP_COMMON_IES_ERROR_UNDEFINED = 0,
    LPP_COMMON_IES_ERROR_LPP_MESSAGE_HEADER_ERROR,
    LPP_COMMON_IES_ERROR_LPP_MESSAGE_BODY_ERROR,
    LPP_COMMON_IES_ERROR_EPDU_ERROR,
    LPP_COMMON_IES_ERROR_INCORRECT_DATA_VALUE,
    LPP_COMMON_IES_ERROR_BUTT
};
typedef VOS_UINT8  LPP_COMMON_IES_ERROR_ENUM_UINT8;

/*****************************************************************************
  5 STRUCT
*****************************************************************************/

typedef struct
{
    /*
        plmn-Identity       SEQUENCE {
                                mcc     SEQUENCE (SIZE (3))     OF INTEGER (0..9),
                                mnc     SEQUENCE (SIZE (2..3))  OF INTEGER (0..9)
                            },
    */
    /*����MNC������aucMnc[2]��FF���ʾ��MNC�������ֽ���Ч�������FF��3���ֽ���Ч*/
    VOS_UINT8               aucMcc[LPP_MCC_LENGTH];/*FIXME LIFUXIN*/
    VOS_UINT8               ucRes;
    VOS_UINT8               aucMnc[LPP_MNC_LENGTH];
    VOS_UINT8               ucMncNum;
}LPP_MTA_COMMON_PLMN_IDENTITY_STRU;


typedef struct
{
    /*
    GNSS-SignalIDs  ::= SEQUENCE {
        gnss-SignalIDs      BIT STRING (SIZE(8)),
        ...
    }
    */
    VOS_UINT32                              bitOpGNSSSignalIDsExt   :1;
    VOS_UINT32                              bitOpSpare              :31;

    VOS_UINT8                               ucGNSSSignalIds;
    VOS_UINT8                               aucRes[3];
}LPP_MTA_COMMON_GNSS_SIGNAL_IDS_STRU;


typedef struct
{
    /*
    cellIdentity        CHOICE {
        eutra   BIT STRING (SIZE (28)),
        utra    BIT STRING (SIZE (32))
    },
    */
    VOS_UINT32              ulChoice;
    #define     LPP_EUTRA_CHOSEN    0
    #define     LPP_UTRA_CHOSEN     1

    union
    {
        VOS_UINT32              ulEutra;
        VOS_UINT32              ulUtra;
    }u;
}LPP_MTA_COMMON_CELL_IDENTITY_STRU;


typedef struct
{
    /*
    CellGlobalIdEUTRA-AndUTRA ::= SEQUENCE {
        plmn-Identity       SEQUENCE {
                                mcc     SEQUENCE (SIZE (3))     OF INTEGER (0..9),
                                mnc     SEQUENCE (SIZE (2..3))  OF INTEGER (0..9)
                            },
        cellIdentity        CHOICE {
            eutra   BIT STRING (SIZE (28)),
            utra    BIT STRING (SIZE (32))
        },
        ...
    }
    */
    VOS_UINT32                          bitOpCellGloEUTRAUTRAExt:1;
    VOS_UINT32                          bitOpSpare              :31;

    LPP_MTA_COMMON_PLMN_IDENTITY_STRU   stPlmnIdentity;
    LPP_MTA_COMMON_CELL_IDENTITY_STRU   stCellIdentity;
}LPP_MTA_COMMON_CELL_GLO_EUTRA_UTRA_STRU;


typedef struct
{
    /*
    fdd         SEQUENCE {
                                                        primary-CPICH-Info  INTEGER (0..511),
                                                        ...
                                                      },
    */
    VOS_UINT32              bitOpFddExt:1;
    VOS_UINT32              bitOpSpare:31;

    VOS_UINT32              ulPrimaryCpichInfo;
}LPP_MTA_COMMON_FDD_STRU;


typedef struct
{
    /*
    tdd         SEQUENCE {
                                                        cellParameters      INTEGER (0..127),
                                                        ...
                                                        }
    */
    VOS_UINT32              bitOpTddExt:1;
    VOS_UINT32              bitOpSpare:31;

    VOS_UINT32              ulCellParameters;
}LPP_MTA_COMMON_TDD_STRU;


typedef struct
{
    VOS_UINT32              ulChoice;

    #define     LPP_FDD_CHOSEN            0
    #define     LPP_TDD_CHOSEN            1

    union
    {
        LPP_MTA_COMMON_FDD_STRU           stFdd;
        LPP_MTA_COMMON_TDD_STRU           stTdd;
    }u;
}LPP_MTA_COMMON_MODE_SELECT_STRU;


typedef struct
{
    /*
    CellGlobalIdGERAN ::= SEQUENCE {
        plmn-Identity       SEQUENCE {
                                mcc     SEQUENCE (SIZE (3))     OF INTEGER (0..9),
                                mnc     SEQUENCE (SIZE (2..3))  OF INTEGER (0..9)
                                },
        locationAreaCode        BIT STRING (SIZE (16)),
        cellIdentity            BIT STRING (SIZE (16)),
        ...
    }
    */
    VOS_UINT32                          bitOpCellGLOBALIdGERANExt   :1;
    VOS_UINT32                          bitOpSpare                  :31;

    LPP_MTA_COMMON_PLMN_IDENTITY_STRU   stPlmnIdentity;
    VOS_UINT16                          usLocationAreaCode;
    VOS_UINT16                          usCellIdentity;
}LPP_MTA_COMMON_CELL_GLO_ID_GERAN_STRU;


typedef struct
{
   /*
   SV-ID ::= SEQUENCE {
       satellite-id        INTEGER(0..63),
       ...
   }
   */
   VOS_UINT32       bitOpSVIDExt:1;
   VOS_UINT32       bitOpSpare  :31;

   VOS_UINT8        ucSatelliteId;
   VOS_UINT8        aucRes[3];
}LPP_MTA_COMMON_SV_ID_STRU;


typedef struct
{
    /*
    GNSS-SignalID   ::= SEQUENCE {
        gnss-SignalID       INTEGER (0 .. 7),
        ...
    }
    */
    VOS_UINT32                              bitGNSSSignalIDExt:1;
    VOS_UINT32                              bitOpSpare      : 31;
    VOS_UINT8           ucGNSSSignalId;
    VOS_UINT8           aucRes[3];
}LPP_MTA_COMMON_GNSS_SIGNAL_ID_STRU;


typedef struct
{
    /*
    GNSS-ID-Bitmap ::= SEQUENCE {
        gnss-ids            BIT STRING {    gps         (0),
                                            sbas        (1),
                                            qzss        (2),
                                            galileo     (3),
                                            glonass     (4)  } (SIZE (1..16)),
        ...
    }
    */
    VOS_UINT32                              bitOpGNSSIDBitmapExt:1;
    VOS_UINT32                              bitOpSpare          :31;

    VOS_UINT16                              usGnssIdsCnt;
    VOS_UINT16                              usGNSSIDs;
}LPP_MTA_COMMON_GNSS_ID_BITMAP_STRU;


typedef struct
{
    /*
    GNSS-LocationServerErrorCauses ::= SEQUENCE {
        cause       ENUMERATED  {
                        undefined,
                        undeliveredAssistanceDataIsNotSupportedByServer,
                        undeliveredAssistanceDataIsSupportedButCurrentlyNotAvailableByServer,
                        undeliveredAssistanceDataIsPartlyNotSupportedAndPartlyNotAvailableByServer,
                        ...
                        },
        ...
    }
    */
    VOS_UINT32                                          bitOpGNSSLocationServerErrorCauseExt:1;
    VOS_UINT32                                          bitOpSpare                          :31;

    LPP_GNSS_LOCATION_SERVER_ERROR_CAUSE_ENUM_UINT8     enGNSSLocationServerCause;
    VOS_UINT8                                           aucRsv[3];
}MTA_LPP_GNSS_LOCATION_SERVER_ERROR_CAUSE_STRU;


typedef struct
{
    /*
    GNSS-TargetDeviceErrorCauses ::= SEQUENCE {
        cause       ENUMERATED {    undefined,
                                    thereWereNotEnoughSatellitesReceived,
                                    assistanceDataMissing,
                                    notAllRequestedMeasurementsPossible,
                                    ...
                                },
        fineTimeAssistanceMeasurementsNotPossible       NULL        OPTIONAL,
        adrMeasurementsNotPossible                      NULL        OPTIONAL,
        multiFrequencyMeasurementsNotPossible           NULL        OPTIONAL,
        ...
    }
    */
    VOS_UINT32                                              bitOpGNSSTargetDevErrCauseExt       :1;
    VOS_UINT32                                              bitOpFineTimeAssistMeasNotPossible  :1;
    VOS_UINT32                                              bitOpAdrMeasNotPossibleExt          :1;
    VOS_UINT32                                              bitOpMultiFreqMeasNotPossibleExt    :1;
    VOS_UINT32                                              bitOpSpare                          :28;

    LPP_GNSS_LOCATION_TARGET_DEVICE_ERROR_CAUSE_ENUM_UINT8  enGNSSTargetDeviceErrorCause;
    VOS_UINT8                                               ucFineTimeAssistanceMeasurementsNotPossible;
    VOS_UINT8                                               ucAdrMeasurementsNotPossible;
    VOS_UINT8                                               ucMultiFrequencyMeasurementsNotPossible;
}MTA_LPP_GNSS_TARGET_DEVICE_ERROR_CAUSE_STRU;


typedef struct
{
    /*
    A-GNSS-Error ::= CHOICE {
        locationServerErrorCauses       GNSS-LocationServerErrorCauses,
        targetDeviceErrorCauses         GNSS-TargetDeviceErrorCauses,
        ...
    }
    */
    VOS_UINT32                                          bitOpGNSSErrorExt   :1;
    VOS_UINT32                                          bitOpSpare          :31;
    VOS_UINT32                                          ulChoice;

    #define           LPP_LOCATION_SERVER_ERROR_CAUSE_CHOSEN        0
    #define           LPP_TARGET_DEVICE_ERROR_CAUSE_CHOSEN          1

    union
    {
       MTA_LPP_GNSS_LOCATION_SERVER_ERROR_CAUSE_STRU             stLocationServerErrorCauses;
       MTA_LPP_GNSS_TARGET_DEVICE_ERROR_CAUSE_STRU               stTargetDeviceErrorCauses;
    }u;
}LPP_MTA_COMMON_GNSS_ERROR_STRU;


typedef struct
{
    /*
    ECGI ::= SEQUENCE {
        mcc             SEQUENCE (SIZE (3))     OF INTEGER (0..9),
        mnc             SEQUENCE (SIZE (2..3))  OF INTEGER (0..9),
        cellidentity    BIT STRING (SIZE (28))
    }
    */
    LPP_MTA_COMMON_PLMN_IDENTITY_STRU   stPlmnIdentity;
    VOS_UINT32                          ulCellIdentity;
}LPP_MTA_COMMON_ECGI_STRU;


typedef struct
{
    /*
    Ellipsoid-Point ::= SEQUENCE {
        latitudeSign                ENUMERATED {north, south},
        degreesLatitude             INTEGER (0..8388607),           -- 23 bit field
        degreesLongitude            INTEGER (-8388608..8388607)     -- 24 bit field
    }
    */
    LPP_LATITUDE_SIGN_ENUM_UINT8    enLatitudeSign;
    VOS_UINT8                       aucRes[3];
    VOS_UINT32                      ulDegreeLatitude;
    VOS_INT32                       lDegreesLongitude;
}MTA_LPP_ELLIPSOID_POINT_STRU;


typedef struct
{
    /*
    Ellipsoid-PointWithUncertaintyCircle ::= SEQUENCE {
        latitudeSign                ENUMERATED {north, south},
        degreesLatitude             INTEGER (0..8388607),           -- 23 bit field
        degreesLongitude            INTEGER (-8388608..8388607),    -- 24 bit field
        uncertainty                 INTEGER (0..127)
    }
    */
    LPP_LATITUDE_SIGN_ENUM_UINT8    enLatitudeSign;
    VOS_UINT8                       aucRes[3];
    VOS_UINT32                      ulDegreesLatitude;
    VOS_INT32                       lDegreeLongitude;
    VOS_UINT32                      ulUncretainty;
}MTA_LPP_ELLIPSOID_POINT_WITH_UNCERTAINTY_CIRCLE_STRU;


typedef struct
{
    /*
    EllipsoidPointWithUncertaintyEllipse ::= SEQUENCE {
        latitudeSign                ENUMERATED {north, south},
        degreesLatitude             INTEGER (0..8388607),           -- 23 bit field
        degreesLongitude            INTEGER (-8388608..8388607),    -- 24 bit field
        uncertaintySemiMajor        INTEGER (0..127),
        uncertaintySemiMinor        INTEGER (0..127),
        orientationMajorAxis        INTEGER (0..179),
        confidence                  INTEGER (0..100)
    }
    */
    LPP_LATITUDE_SIGN_ENUM_UINT8    enLatitudeSign;
    VOS_UINT8                       aucRes[3];
    VOS_UINT32                      ulDegreesLatitude;
    VOS_INT32                       lDegreesLongitude;
    VOS_UINT8                       ucUncertaintySemiMajor;
    VOS_UINT8                       ucUncertaintySemiMinor;
    VOS_UINT8                       ucOrientationMajorAxis;
    VOS_UINT8                       ucConfidence;
}MTA_LPP_ELLIPSOID_POINT_WITH_UNCERTAINTY_ELLIPSE_STRU;


typedef struct
{
    /*
    PolygonPoints ::= SEQUENCE {
        latitudeSign                ENUMERATED {north, south},
        degreesLatitude             INTEGER (0..8388607),           -- 23 bit field
        degreesLongitude            INTEGER (-8388608..8388607)     -- 24 bit field
    }
    */
    LPP_LATITUDE_SIGN_ENUM_UINT8    enLatitudeSign;
    VOS_UINT8                       aucRes[3];
    VOS_UINT32                      ulDegreesLatitude;
    VOS_INT32                       lDegreesLatitude;
}MTA_LPP_POLYGON_POINTS_STRU;


typedef struct
{
    /*
    Polygon ::= SEQUENCE (SIZE (3..15)) OF PolygonPoints
    */
    VOS_UINT32                          ulPolygonCnt;
    MTA_LPP_POLYGON_POINTS_STRU         astPolygonArray[LPP_MAX_POLYGON_POINTS_LEN];
}MTA_LPP_POLYGON_STRU;


typedef struct
{
    /*
    EllipsoidPointWithAltitude ::= SEQUENCE {
        latitudeSign                ENUMERATED {north, south},
        degreesLatitude             INTEGER (0..8388607),           -- 23 bit field
        degreesLongitude            INTEGER (-8388608..8388607),    -- 24 bit field
        altitudeDirection           ENUMERATED {height, depth},
        altitude                    INTEGER (0..32767)              -- 15 bit field
    }
    */
    LPP_LATITUDE_SIGN_ENUM_UINT8    enLatitudeSign;
    VOS_UINT8                       aucRes[3];
    VOS_UINT32                      ulDegreesLatitude;
    VOS_INT32                       lDegreesLatitude;
    LPP_LATITUDE_DIR_ENUM_UINT8     enAltitudeDirection;
    VOS_UINT8                       ucRes;
    VOS_UINT16                      usAltitude;
}MTA_LPP_ELLIPSOID_POINT_WITH_ALTITUDE_STRU;


typedef struct
{
    /*
    EllipsoidPointWithAltitudeAndUncertaintyEllipsoid ::= SEQUENCE {
        latitudeSign                ENUMERATED {north, south},
        degreesLatitude             INTEGER (0..8388607),           -- 23 bit field
        degreesLongitude            INTEGER (-8388608..8388607),    -- 24 bit field
        altitudeDirection           ENUMERATED {height, depth},
        altitude                    INTEGER (0..32767),             -- 15 bit field
        uncertaintySemiMajor        INTEGER (0..127),
        uncertaintySemiMinor        INTEGER (0..127),
        orientationMajorAxis        INTEGER (0..179),
        uncertaintyAltitude         INTEGER (0..127),
        confidence                  INTEGER (0..100)
    }
    */
    LPP_LATITUDE_SIGN_ENUM_UINT8    enLatitudeSign;
    VOS_UINT8                       aucRes[3];
    VOS_UINT32                      ulDegreesLatitude;
    VOS_INT32                       lDegreesLongtitude;
    LPP_LATITUDE_DIR_ENUM_UINT8     enAltitudeDirection;
    VOS_UINT8                       ucUncertaintySemiMajor;
    VOS_UINT16                      usAltitude;
    VOS_UINT8                       ucUncertaintySemiMinor;
    VOS_UINT8                       ucOrientationMajorAxis;
    VOS_UINT8                       ucUncertaintyAltitude;
    VOS_UINT8                       ucConfidence;
}MTA_LPP_ELLIPSOID_POINT_WITH_ALTITUDE_AND_UNCERTAINTY_ELLIPSOID_STRU;


typedef struct
{
    /*
    EllipsoidArc ::= SEQUENCE {
        latitudeSign                ENUMERATED {north, south},
        degreesLatitude             INTEGER (0..8388607),           -- 23 bit field
        degreesLongitude            INTEGER (-8388608..8388607),    -- 24 bit field
        innerRadius                 INTEGER (0..65535),             -- 16 bit field,
        uncertaintyRadius           INTEGER (0..127),
        offsetAngle                 INTEGER (0..179),
        includedAngle               INTEGER (0..179),
        confidence                  INTEGER (0..100)
    }
    */
    LPP_LATITUDE_SIGN_ENUM_UINT8    enLatitudeSign;
    VOS_UINT8                       aucRes[3];
    VOS_UINT32                      ulDegreesLatitude;
    VOS_INT32                       lDegreesLongtitude;
    VOS_UINT32                      ulInnerRadius;
    VOS_UINT8                       ucUncertaintyRadius;
    VOS_UINT8                       ucOffsetAngle;
    VOS_UINT8                       ucIncludedAngle;
    VOS_UINT8                       ucConfidence;
}MTA_LPP_ELLIPSOIDARC_STRU;


typedef struct
{
    /*
    LocationCoordinates ::= CHOICE {
        ellipsoidPoint                              Ellipsoid-Point,
        ellipsoidPointWithUncertaintyCircle         Ellipsoid-PointWithUncertaintyCircle,
        ellipsoidPointWithUncertaintyEllipse        EllipsoidPointWithUncertaintyEllipse,
        polygon                                     Polygon,
        ellipsoidPointWithAltitude                  EllipsoidPointWithAltitude,
        ellipsoidPointWithAltitudeAndUncertaintyEllipsoid
                                                    EllipsoidPointWithAltitudeAndUncertaintyEllipsoid,
        ellipsoidArc                                EllipsoidArc,
        ...
    }
    */
    VOS_UINT32                      bitOpLocationCoordinatesExt:1;
    VOS_UINT32                      bitOpSpare:31;
    VOS_UINT32                                          ulChoice;

    #define         LPP_ELLIPSOID_POINT_CHOSEN                                          0
    #define         LPP_ELLIPSOID_POINT_WITH_UNCERTAINTY_CIRCLE_CHOSEN                  1
    #define         LPP_ELLIPSOID_POINT_WITH_UNCERTAINTY_ELLIPSE_CHOSEN                 2
    #define         LPP_POLYGON_CHOSEN                                                  3
    #define         LPP_ELLIPSOID_POINT_WITH_ALTITUDE_CHOSEN                            4
    #define         LPP_ELLIPSOID_POINT_WITH_ALTITUDE_AND_UNCERTAINTY_ELLIPSOID_CHOSEN  5
    #define         LPP_ELLIPSOIDARC_CHOSEN                                             6

        union
        {
            MTA_LPP_ELLIPSOID_POINT_STRU                                            stEllipsoidPoint;
            MTA_LPP_ELLIPSOID_POINT_WITH_UNCERTAINTY_CIRCLE_STRU                    stEllipsoidPointWithUncertaintyCircle;
            MTA_LPP_ELLIPSOID_POINT_WITH_UNCERTAINTY_ELLIPSE_STRU                   stEllipsoidPointWithUncertaintyEllipse;
            MTA_LPP_POLYGON_STRU                                                    stPolygon;
            MTA_LPP_ELLIPSOID_POINT_WITH_ALTITUDE_STRU                              stEllipsoidPointWithAltitude;
            MTA_LPP_ELLIPSOID_POINT_WITH_ALTITUDE_AND_UNCERTAINTY_ELLIPSOID_STRU    stEllipsoidPointWithAltitudeAndUncertaintyEllipsoid;
            MTA_LPP_ELLIPSOIDARC_STRU                                               stEllipsoidArc;
        }u;
}MTA_LPP_LOCATION_COORDINATE_STRU;


typedef struct
{
    /*
    HorizontalVelocity ::= SEQUENCE {
        bearing                     INTEGER(0..359),
        horizontalSpeed             INTEGER(0..2047)
    }
    */
    VOS_UINT16          usBearing;
    VOS_UINT16          usHorizontalSpeed;
}MTA_LPP_HORIZONTAL_VELCOCTIY_STRU;


typedef struct
{
    /*
    HorizontalWithVerticalVelocity ::= SEQUENCE {
        bearing                     INTEGER(0..359),
        horizontalSpeed             INTEGER(0..2047),
        verticalDirection           ENUMERATED{upward, downward},
        verticalSpeed               INTEGER(0..255)
    }
    */
    VOS_UINT16                      usBearing;
    VOS_UINT16                      usHorizontalSpeed;
    LPP_VERTICAL_DIRECT_ENUM_UINT32 enVerticalDirection;
    VOS_UINT32                      ulVerticalSpeed;
}MTA_LPP_HORIZONTAL_WITH_VERTICAL_VELOCITY_STRU;


typedef struct
{
    /*
    HorizontalVelocityWithUncertainty ::= SEQUENCE {
        bearing                     INTEGER(0..359),
        horizontalSpeed             INTEGER(0..2047),
        uncertaintySpeed            INTEGER(0..255)
    }
    */
    VOS_UINT16                      usBearing;
    VOS_UINT16                      usHorizontalSpeed;
    VOS_UINT32                      ulUncertaintySpeed;
}MTA_LPP_HORIZONTAL_VELCCITY_WITH_UNCERTAINTY_STRU;


typedef struct
{
    /*
    HorizontalWithVerticalVelocityAndUncertainty ::= SEQUENCE {
        bearing                     INTEGER(0..359),
        horizontalSpeed             INTEGER(0..2047),
        verticalDirection           ENUMERATED{upward, downward},
        verticalSpeed               INTEGER(0..255),
        horizontalUncertaintySpeed  INTEGER(0..255),
        verticalUncertaintySpeed    INTEGER(0..255)
    }
    */
    VOS_UINT16                      usBearing;
    VOS_UINT16                      usHorizontalSpeed;
    LPP_VERTICAL_DIRECT_ENUM_UINT32 enVerticalDirection;
    VOS_UINT8                       ucVerticalSpeed;
    VOS_UINT8                       ucHorizontalUncertaintySpeed;
    VOS_UINT8                       ucVerticalUncertaintySpeed;
    VOS_UINT8                       ucRes;
}MTA_LPP_HORIZONTAL_WITH_VERTICAL_VELOCITY_AND_UNCERTAINTY_STRU;


typedef struct
{
    /*
    Velocity ::= CHOICE {
        horizontalVelocity                          HorizontalVelocity,
        horizontalWithVerticalVelocity              HorizontalWithVerticalVelocity,
        horizontalVelocityWithUncertainty           HorizontalVelocityWithUncertainty,
        horizontalWithVerticalVelocityAndUncertainty
                                                    HorizontalWithVerticalVelocityAndUncertainty,
        ...
    }
    */
    VOS_UINT32                                          bitOpVelocityExt:1;
    VOS_UINT32                                          bitOpSpare      :31;

    VOS_UINT32                                          ulChoice;

    #define     LPP_HORIZONTAL_VELCOCTIY_CHOSEN                                 0
    #define     LPP_HORIZONTAL_WITH_VERTICAL_VELOCITY_CHOSEN                    1
    #define     LPP_HORIZONTAL_VELCCITY_WITH_UNCERTAINTY_CHOSEN                 2
    #define     LPP_HORIZONTAL_WITH_VERTICAL_VELOCITY_AND_UNCERTAINTY_CHOSEN    3

    union
    {
        MTA_LPP_HORIZONTAL_VELCOCTIY_STRU                               stHorizontalVelocity;
        MTA_LPP_HORIZONTAL_WITH_VERTICAL_VELOCITY_STRU                  stHorizontalWithVerticalVelocity;
        MTA_LPP_HORIZONTAL_VELCCITY_WITH_UNCERTAINTY_STRU               stHorizontalVelocityWithUncertainty;
        MTA_LPP_HORIZONTAL_WITH_VERTICAL_VELOCITY_AND_UNCERTAINTY_STRU  stHorizontalWithVerticalVelocityAndUncertainty;
    }u;
}MTA_LPP_VELOCITY_STRU;


typedef struct
{
    /*
    LocationError ::= SEQUENCE {
        locationfailurecause            LocationFailureCause,
        ...
    }
    */
    VOS_UINT32                                  bitOpLocationErrExt :1;
    VOS_UINT32                                  bitOpSpare          :31;

    LPP_LOCATION_FAILURE_CAUSE_ENUM_UINT32      enLocationFailureCasue;
}MTA_LPP_LOCATION_ERROR_STRU;


typedef struct
{
    /*
    CommonIEsProvideLocationInformation ::= SEQUENCE {
        locationEstimate            LocationCoordinates     OPTIONAL,
        velocityEstimate            Velocity                OPTIONAL,
        locationError               LocationError           OPTIONAL,
        ...
    }
    */
    VOS_UINT32                              bitOpCommonIEsProvideLocationInfoExt:1;
    VOS_UINT32                              bitOpLocationEstimate               :1;
    VOS_UINT32                              bitOpVelocityEstimate               :1;
    VOS_UINT32                              bitOpLocationError                  :1;
    VOS_UINT32                              bitOpSpare                          :28;

    MTA_LPP_LOCATION_COORDINATE_STRU        stLocationEstimate;
    MTA_LPP_VELOCITY_STRU                   stVelocityEstimate;
    MTA_LPP_LOCATION_ERROR_STRU             stLocationError;
}MTA_LPP_COMMON_IES_PROVIDE_LOCATION_INFO_STRU;


typedef struct
{
    /*
    GNSS-ID ::= SEQUENCE {
        gnss-id             ENUMERATED{ gps, sbas, qzss, galileo, glonass, ...},
        ...
    }
    */
    VOS_UINT32                          bitOpGNSSIDExt  :1;
    VOS_UINT32                          bitOpSpare      :31;

    LPP_GNSS_ID_ENUM_UINT8              enGnssId;
    VOS_UINT8                           ucRes[3];
}LPP_MTA_COMMON_GNSS_ID_STRU;


typedef struct
{
    /*
    eUTRA   SEQUENCE {
            physCellId          INTEGER (0..503),
            cellGlobalId        CellGlobalIdEUTRA-AndUTRA       OPTIONAL,
            systemFrameNumber   BIT STRING (SIZE (10)),
            ...
            },

    */
    VOS_UINT32                              bitOpEuraExt    :1;
    VOS_UINT32                              bitCellGlobalId :1;
    VOS_UINT32                              bitOpSpare      :30;

    VOS_UINT32                              ulPhysCellId;
    LPP_MTA_COMMON_CELL_GLO_EUTRA_UTRA_STRU stCellGlobalId;
    VOS_UINT32                              ulSystemFramNumber;
}MTA_LPP_MEAS_REF_TIME_EUTRA;


typedef struct
{
    /*
    uTRA    SEQUENCE {
            mode                    CHOICE {
                                    fdd         SEQUENCE {
                                                primary-CPICH-Info  INTEGER (0..511),
                                                ...
                                                },
                                    tdd         SEQUENCE {
                                                cellParameters      INTEGER (0..127),
                                                ...
                                                }
                                    },
            cellGlobalId            CellGlobalIdEUTRA-AndUTRA       OPTIONAL,
            referenceSystemFrameNumber
                                    INTEGER (0..4095),
            ...
            },

    */
    VOS_UINT32                                  bitOpUtranExt   :1;
    VOS_UINT32                                  bitCellGlobalId :1;
    VOS_UINT32                                  bitOpSpare      :30;

    LPP_MTA_COMMON_MODE_SELECT_STRU             stMode;
    LPP_MTA_COMMON_CELL_GLO_EUTRA_UTRA_STRU     stCellGlobalId;
    VOS_UINT32                                  ulRefSystemFramNumber;
}MTA_LPP_MEAS_REF_TIME_UTRA;


typedef struct
{
    /*
    referenceFrame      SEQUENCE {
                        referenceFN         INTEGER (0..65535),
                        referenceFNMSB      INTEGER (0..63)     OPTIONAL,
                        ...
                        },
    */
    VOS_UINT32                              bitOpRefFrameExt:1;
    VOS_UINT32                              bitOpRefEnmsb   :1;
    VOS_UINT32                              bitOpSpare      :30;

    VOS_UINT16                              usRefFn;
    VOS_UINT16                              usRefFnmsn;
}MTA_LPP_REF_FRAME_STRU;


typedef struct
{
    /*
    gSM     SEQUENCE {
            bcchCarrier         INTEGER (0..1023),
            bsic                INTEGER (0..63),
            cellGlobalId        CellGlobalIdGERAN                   OPTIONAL,
            referenceFrame      SEQUENCE {
                                referenceFN         INTEGER (0..65535),
                                referenceFNMSB      INTEGER (0..63)     OPTIONAL,
                                ...
                                },
            deltaGNSS-TOD       INTEGER (0 .. 127)      OPTIONAL,
            ...
            },
    */
    VOS_UINT32                              bitOpGsmExt     :1;
    VOS_UINT32                              bitCellGlobalId :1;
    VOS_UINT32                              bitDelataGnssTod:1;
    VOS_UINT32                              bitOpSpare      :29;

    VOS_UINT16                              usBcchCarrier;
    VOS_UINT16                              usBsic;
    LPP_MTA_COMMON_CELL_GLO_ID_GERAN_STRU   stCellGlobalId;
    MTA_LPP_REF_FRAME_STRU                  stRefFrame;
    VOS_UINT32                              ulDelaGnssTod;
}MTA_LPP_MEAS_REF_TIME_GSM;


typedef struct
{
    /*
    networkTime         CHOICE {
        eUTRA   SEQUENCE {
                physCellId          INTEGER (0..503),
                cellGlobalId        CellGlobalIdEUTRA-AndUTRA       OPTIONAL,
                systemFrameNumber   BIT STRING (SIZE (10)),
                ...
                },
        uTRA    SEQUENCE {
                mode                    CHOICE {
                                        fdd         SEQUENCE {
                                                    primary-CPICH-Info  INTEGER (0..511),
                                                    ...
                                                    },
                                        tdd         SEQUENCE {
                                                    cellParameters      INTEGER (0..127),
                                                    ...
                                                    }
                                        },
                cellGlobalId            CellGlobalIdEUTRA-AndUTRA       OPTIONAL,
                referenceSystemFrameNumber
                                        INTEGER (0..4095),
                ...
                },
        gSM     SEQUENCE {
                bcchCarrier         INTEGER (0..1023),
                bsic                INTEGER (0..63),
                cellGlobalId        CellGlobalIdGERAN                   OPTIONAL,
                referenceFrame      SEQUENCE {
                                    referenceFN         INTEGER (0..65535),
                                    referenceFNMSB      INTEGER (0..63)     OPTIONAL,
                                    ...
                                    },
                deltaGNSS-TOD       INTEGER (0 .. 127)      OPTIONAL,
                ...
                },
        ...
        }

    */
    VOS_UINT32                                          ulChoice;

    #define         LPP_NETTIME_EUTRA_CHOSEN                0
    #define         LPP_NETTIME_UTRAN_CHOSEN                1
    #define         LPP_NETTIME_GSM_CHOSEN                  2

    union
    {
        MTA_LPP_MEAS_REF_TIME_EUTRA             stLppMeasRefTimeEutra;
        MTA_LPP_MEAS_REF_TIME_UTRA              stLppMeasRefTimeUtra;
        MTA_LPP_MEAS_REF_TIME_GSM               stLppMeasRefTimeGsm;
    }u;
}MTA_LPP_NET_WORK_TIME_MEAS_REF_STRU;


typedef struct
{
    /*
    MeasurementReferenceTime  ::= SEQUENCE {
        gnss-TOD-msec       INTEGER (0..3599999),
        gnss-TOD-frac       INTEGER (0..3999)           OPTIONAL,
        gnss-TOD-unc        INTEGER (0..127)            OPTIONAL,
        gnss-TimeID         GNSS-ID,
        networkTime         CHOICE {
                ......
            }       OPTIONAL,
        ...
    }
    */
    VOS_UINT32                          bitOpMeasRefTimeFExt:1;
    VOS_UINT32                          bitOpGNSSTodFrac    :1;
    VOS_UINT32                          bitOpGNSSTodUnc     :1;
    VOS_UINT32                          bitOpNetWorkTime    :1;
    VOS_UINT32                          bitOpSpare          :28;

    VOS_UINT32                          ulGNSSTodMsec;
    VOS_UINT16                          usGNSSTodFrac;
    VOS_UINT16                          usGNSSTodUnc;
    LPP_MTA_COMMON_GNSS_ID_STRU         stGNSSId;
    MTA_LPP_NET_WORK_TIME_MEAS_REF_STRU stNetWorktime;
}MTA_LPP_MEAS_REF_TIME_STRU;


typedef struct
{
    /*
    GNSS-SatMeasElement ::= SEQUENCE {
        svID                SV-ID,
        cNo                 INTEGER (0..63),
        mpathDet            ENUMERATED {notMeasured (0), low (1), medium (2), high (3), ...},
        carrierQualityInd   INTEGER (0..3)              OPTIONAL,
        codePhase           INTEGER (0..2097151),
        integerCodePhase    INTEGER (0..127)            OPTIONAL,
        codePhaseRMSError   INTEGER (0..63),
        doppler             INTEGER (-32768..32767)     OPTIONAL,
        adr                 INTEGER (0..33554431)       OPTIONAL,
        ...
    }
    */
    VOS_UINT32                          bitOpGNSSSatMeasElementExt  :1;
    VOS_UINT32                          bitOpCarrierQualityInd      :1;
    VOS_UINT32                          bitOpIntegerCodePhase       :1;
    VOS_UINT32                          bitOpDoppler                :1;
    VOS_UINT32                          bitOpAdr                    :1;
    VOS_UINT32                          bitOpSpare                  :27;

    LPP_MTA_COMMON_SV_ID_STRU           stSvId;
    VOS_UINT32                          ulCNo;
    LPP_MPATH_DET_ENUM_UINT32           enMpathDet;
    VOS_UINT8                           ucCrrierQualityInd;
    VOS_UINT8                           aucRes[3];
    VOS_UINT32                          ulCodePhase;
    VOS_UINT8                           ucIntgerCodePhase;
    VOS_UINT8                           ucCodePhaseRmsError;
    VOS_INT16                           sDoppler;
    VOS_UINT32                          ulAdr;
}MTA_LPP_GNSS_SAT_MEAS_ELEMENT_STRU;


typedef struct
{
    /*
    GNSS-SatMeasList ::= SEQUENCE (SIZE(1..64)) OF GNSS-SatMeasElement
    */
    VOS_UINT32                              ulGNSSSatMeasListCnt;
    MTA_LPP_GNSS_SAT_MEAS_ELEMENT_STRU      astGNSSSatMeasListArray[LPP_MAX_GNSS_SAT_MEAS_ELMENT_LEN];
}MTA_LPP_GNSS_SAT_MEAS_LIST_STRU;


typedef struct
{
    /*
    GNSS-SgnMeasElement ::= SEQUENCE {
        gnss-SignalID           GNSS-SignalID,
        gnss-CodePhaseAmbiguity INTEGER (0..127)        OPTIONAL,
        gnss-SatMeasList        GNSS-SatMeasList,
        ...
    }
    */
    VOS_UINT32                          bitOpGNSSSgnMeasElementExt  :1;
    VOS_UINT32                          bitOpGNSSCodePhaseAmbiguity :1;
    VOS_UINT32                          bitOpSpare                  :30;

    LPP_MTA_COMMON_GNSS_SIGNAL_ID_STRU  stGNSSSignalId;
    VOS_UINT32                          ulGNSSCodePhaseAmbiguity;
    MTA_LPP_GNSS_SAT_MEAS_LIST_STRU     stGNSSSatMeasList;
}MTA_LPP_GNSS_SGN_MEAS_ELEMENT_STRU;


typedef struct
{
    /*
    GNSS-SgnMeasList ::= SEQUENCE (SIZE(1..8)) OF GNSS-SgnMeasElement
    */
    VOS_UINT32                              ulGNSSSgnMeasListCnt;
    MTA_LPP_GNSS_SGN_MEAS_ELEMENT_STRU      astGNSSSgnMeasListArray[LPP_MAX_GNSS_SGN_MEAS_ELMENT_LEN];
}MTA_LPP_GNSS_SGN_LIST_STRU;


typedef struct
{
    /*
    GNSS-MeasurementForOneGNSS ::= SEQUENCE {
        gnss-ID                 GNSS-ID,
        gnss-SgnMeasList        GNSS-SgnMeasList,
        ...
    }
    */
    VOS_UINT32                      bitOpGNSSMeasForOneGNSSExt  :1;
    VOS_UINT32                      bitOpSpare                  :31;

    LPP_MTA_COMMON_GNSS_ID_STRU     stGNSSId;
    MTA_LPP_GNSS_SGN_LIST_STRU      stGNSSSgnMeasList;
}MTA_LPP_GNSS_MEAS_FOR_ONE_GNSS_STRU;


typedef struct
{
    /*
    GNSS-MeasurementList  ::= SEQUENCE (SIZE(1..16)) OF GNSS-MeasurementForOneGNSS
    */
    VOS_UINT32                              ulGNSSMeasListCnt;
    MTA_LPP_GNSS_MEAS_FOR_ONE_GNSS_STRU     astGNSSMeasListArray[LPP_MAX_GNSS_MEAS_FOR_ONE_GNSS_LEN];
}MTA_LPP_GNSS_MEAS_LIST_STRU;


typedef struct
{
    /*
    GNSS-SignalMeasurementInformation ::= SEQUENCE {
        measurementReferenceTime        MeasurementReferenceTime,
        gnss-MeasurementList            GNSS-MeasurementList,
        ...
    }
    */
    VOS_UINT32                          bitOpGNSSSignalMeasInfoExt:1;
    VOS_UINT32                          bitOpSpare                :31;

    MTA_LPP_MEAS_REF_TIME_STRU          stMeasRefTime;/*AT��û���ҵ���Ӧ�Ľṹ*/
    MTA_LPP_GNSS_MEAS_LIST_STRU         stGNSSMeasList;
}MTA_LPP_GNSS_SIGNAL_MEAS_INFO_STRU;
typedef struct
{
    /*
    GNSS-LocationInformation ::= SEQUENCE {
        measurementReferenceTime        MeasurementReferenceTime,
        agnss-List                      GNSS-ID-Bitmap,
        ...
    }
    */
    VOS_UINT32                              bitOpGNSSLocationInfoExt:1;
    VOS_UINT32                              bitOpSpare              :31;

    MTA_LPP_MEAS_REF_TIME_STRU              stMeasRefTime;
    LPP_MTA_COMMON_GNSS_ID_BITMAP_STRU      stAGNSSList;
}MTA_LPP_GNSS_LOCATION_INFO_STRU;


typedef struct
{
    /*
    ARFCN-ValueEUTRA ::= INTEGER (0..maxEARFCN)
    maxEARFCN   INTEGER ::= 65535   -- Maximum value of EUTRA carrier frequency
    */
    VOS_UINT32          ulArfcnValueEUTRA;
}LPP_MTA_ARFCN_VALUE_EUTRA_STRU;


typedef struct
{

    VOS_UINT32          bitOpARFCNValueEutraV9A0:1;
    VOS_UINT32          bitOpSpare              :31;

    VOS_UINT32          ulArfcnValueEUTRAv9a0;
}LPP_MTA_ARFCN_VALUE_EUTRA_V9A0_STRU;


typedef struct
{
    /*
    eUTRA       SEQUENCE {
                physCellId          INTEGER (0..503),
                cellGlobalIdEUTRA   CellGlobalIdEUTRA-AndUTRA   OPTIONAL,   -- Need ON
                earfcn              ARFCN-ValueEUTRA,
                ...,
                [[ earfcn-v9a0      ARFCN-ValueEUTRA-v9a0 OPTIONAL  -- Cond EARFCN-max
                ]]  FIXME LIFUXIN
                },
    */
    VOS_UINT32                                  bitOpCellGEutraAndUtra  :1;
    VOS_UINT32                                  bitOpArfcnEutraV9a0     :1;
    VOS_UINT32                                  bitOpEutraExt           :1;
    VOS_UINT32                                  bitOpSpare              :29;

    VOS_UINT16                                  usPhysCellId;
    VOS_UINT8                                   aucRes[2];
    LPP_MTA_COMMON_CELL_GLO_EUTRA_UTRA_STRU     stCellGlobalIdEUTRA;
    LPP_MTA_ARFCN_VALUE_EUTRA_STRU              stEarfcn;
    LPP_MTA_ARFCN_VALUE_EUTRA_V9A0_STRU         stEarfcnV9a0;
}LPP_MTA_EUTRA_STRU;


typedef struct
{
    /*
    ARFCN-ValueUTRA ::= INTEGER(0..16383)
    */
    VOS_UINT32          ulArfcnValueUTRA;
}LPP_MTA_ARFCN_VALUE_UTRA_STRU;


typedef struct
{
    /*
    uTRA        SEQUENCE {
    mode    CHOICE {
                    fdd     SEQUENCE {
                            primary-CPICH-Info  INTEGER (0..511),
                            ...
                            },
                    tdd     SEQUENCE {
                            cellParameters      INTEGER (0..127),
                            ...
                            }
                    },
    cellGlobalIdUTRA    CellGlobalIdEUTRA-AndUTRA   OPTIONAL,   -- Need ON
    uarfcn              ARFCN-ValueUTRA,
    ...
    },
    */
    VOS_UINT32                                  bitOpCellGloEutraAndUtra:1;
    VOS_UINT32                                  bitOpUtraExt            :1;
    VOS_UINT32                                  bitOpSpare              :30;

    LPP_MTA_COMMON_MODE_SELECT_STRU             stMode;
    LPP_MTA_COMMON_CELL_GLO_EUTRA_UTRA_STRU     stCellGlobalIdUTRA;
    LPP_MTA_ARFCN_VALUE_UTRA_STRU               stUarfcn;
}LPP_MTA_UTRA_STRU;


typedef struct
{
    /*
     gSM         SEQUENCE {
             bcchCarrier         INTEGER (0..1023),
             bsic                INTEGER (0..63),
             cellGlobalIdGERAN   CellGlobalIdGERAN           OPTIONAL,   -- Need ON
             ...
             },
    ...
    */
    VOS_UINT32                              bitOpCellGlobalIdGeran:1;
    VOS_UINT32                              bitOpGsmExt:1;
    VOS_UINT32                              bitOpSpare:30;

    VOS_UINT16                              usBcchCarrier;
    VOS_UINT16                              usBsis;
    LPP_MTA_COMMON_CELL_GLO_ID_GERAN_STRU   stCellGlobalIdGeran;
}LPP_MTA_GSM_STRU;


typedef struct
{
    /*
    cellID      CHOICE {
                 eUTRA       SEQUENCE {
                             physCellId          INTEGER (0..503),
                             cellGlobalIdEUTRA   CellGlobalIdEUTRA-AndUTRA   OPTIONAL,   -- Need ON
                             earfcn              ARFCN-ValueEUTRA,
                             ...,
                             [[ earfcn-v9a0      ARFCN-ValueEUTRA-v9a0 OPTIONAL  -- Cond EARFCN-max
                             ]]
                             },
                 uTRA        SEQUENCE {
                             mode    CHOICE {
                                     fdd     SEQUENCE {
                                             primary-CPICH-Info  INTEGER (0..511),
                                             ...
                                             },
                                     tdd     SEQUENCE {
                                             cellParameters      INTEGER (0..127),
                                             ...
                                             }
                                     },
                             cellGlobalIdUTRA    CellGlobalIdEUTRA-AndUTRA   OPTIONAL,   -- Need ON
                             uarfcn              ARFCN-ValueUTRA,
                             ...
                             },
                 gSM         SEQUENCE {
                             bcchCarrier         INTEGER (0..1023),
                             bsic                INTEGER (0..63),
                             cellGlobalIdGERAN   CellGlobalIdGERAN           OPTIONAL,   -- Need ON
                             ...
                             },
                 ...
                 },
    */

    VOS_UINT32              bitOpCellIdExt  :1;
    VOS_UINT32              bitSpace        :31;

    VOS_UINT32              ulChoice;

#define     LPP_CELL_ID_EUTRA_CHOSEN           0
#define     LPP_CELL_ID_UTRA_CHOSEN            1
#define     LPP_CELL_ID_GSM_CHOSEN             2

    union
    {
        LPP_MTA_EUTRA_STRU          stEUtra;
        LPP_MTA_UTRA_STRU           stUtra;
        LPP_MTA_GSM_STRU            stGsm;

    }u;
}LPP_MTA_CELL_ID_STRU;


typedef struct
{
    /*
    NetworkTime ::= SEQUENCE {
        secondsFromFrameStructureStart              INTEGER(0..12533),
        fractionalSecondsFromFrameStructureStart    INTEGER(0..3999999),
        frameDrift                                  INTEGER (-64..63)   OPTIONAL,   -- Cond GNSSsynch
        cellID      CHOICE {
                    eUTRA       SEQUENCE {
                                physCellId          INTEGER (0..503),
                                cellGlobalIdEUTRA   CellGlobalIdEUTRA-AndUTRA   OPTIONAL,   -- Need ON
                                earfcn              ARFCN-ValueEUTRA,
                                ...,
                                [[ earfcn-v9a0      ARFCN-ValueEUTRA-v9a0 OPTIONAL  -- Cond EARFCN-max
                                ]]
                                },
                    uTRA        SEQUENCE {
                                mode    CHOICE {
                                        fdd     SEQUENCE {
                                                primary-CPICH-Info  INTEGER (0..511),
                                                ...
                                                },
                                        tdd     SEQUENCE {
                                                cellParameters      INTEGER (0..127),
                                                ...
                                                }
                                        },
                                cellGlobalIdUTRA    CellGlobalIdEUTRA-AndUTRA   OPTIONAL,   -- Need ON
                                uarfcn              ARFCN-ValueUTRA,
                                ...
                                },
                    gSM         SEQUENCE {
                                bcchCarrier         INTEGER (0..1023),
                                bsic                INTEGER (0..63),
                                cellGlobalIdGERAN   CellGlobalIdGERAN           OPTIONAL,   -- Need ON
                                ...
                                },
                    ...
                    },
        ...
    }

    */
    VOS_UINT32                              bitOpNetworkTimeExt:1;
    VOS_UINT32                              bitOpFrameDrift:1;
    VOS_UINT32                              bitOpSpare:30;

    VOS_UINT32                              ulSecondsFromFrameStructureStart;
    VOS_UINT32                              ulFractionalSecondsFromFrameStructureStart;
    VOS_INT8                                cFrameDrift;
    VOS_UINT8                               aucRes[3];
    LPP_MTA_CELL_ID_STRU                    stCellID;
}LPP_MTA_NET_WORK_TIME_STRU;


typedef struct
{
    /*
    A-GNSS-ProvideLocationInformation ::= SEQUENCE {
        gnss-SignalMeasurementInformation   GNSS-SignalMeasurementInformation       OPTIONAL,
        gnss-LocationInformation            GNSS-LocationInformation                OPTIONAL,
        gnss-Error                          A-GNSS-Error                            OPTIONAL,
        ...
    }
    */
    VOS_UINT32                              bitOpAGNSSProvideLocationInfoExt:1;
    VOS_UINT32                              bitOpGNSSSignalMeasInfo         :1;
    VOS_UINT32                              bitOpGNSSLocationInfo           :1;
    VOS_UINT32                              bitOpGNSSError                  :1;
    VOS_UINT32                              bitOpSpare                      :28;

    MTA_LPP_GNSS_SIGNAL_MEAS_INFO_STRU      stGNSSsignalMeasInfo;
    MTA_LPP_GNSS_LOCATION_INFO_STRU         stGNSSLocationInfo;
    LPP_MTA_COMMON_GNSS_ERROR_STRU          stGNSSError;
}MTA_LPP_AGNSS_PROVIDE_LOCATION_INFO_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                  /*_H2ASN_Skip*/
    VOS_UINT32                                      ulMsgId;        /*_H2ASN_Skip*/ /* ��Ϣͷ */

    VOS_UINT32                                      ulSessionId;    /*��ǰsessionID*/
    MTA_LPP_AGNSS_PROVIDE_LOCATION_INFO_STRU        stGnssReqLocationInfo;
    MTA_LPP_COMMON_IES_PROVIDE_LOCATION_INFO_STRU   stCommonProvideLocInfo;
}MTA_LPP_GNSS_RROVIDE_LOCATION_INFO_CNF_STRU;/*27.007 8.55-19 8.55-11, 8.50-2*/


typedef struct
{
    /*
    TriggeredReportingCriteria ::=      SEQUENCE {
        cellChange                          BOOLEAN,
        reportingDuration                   ReportingDuration,
        ...
    }
    ReportingDuration ::=   INTEGER (0..255)
    */
    VOS_UINT32                      bitOpTriggerReportCriteriaExt   :1;
    VOS_UINT32                      bitOpSpare                      :31;

    VOS_BOOL                        bCellChange;
    VOS_UINT32                      ulReportDuration;
}LPP_MTA_COMMON_TRIGGER_REPORT_CRITERIA_STRU;


typedef struct
{
    /*
    PeriodicalReportingCriteria ::=     SEQUENCE {
        reportingAmount                     ENUMERATED {
                                                ra1, ra2, ra4, ra8, ra16, ra32,
                                                ra64, ra-Infinity
                                            } DEFAULT ra-Infinity,
        reportingInterval                   ENUMERATED {
                                                noPeriodicalReporting, ri0-25,
                                                ri0-5, ri1, ri2, ri4, ri8, ri16, ri32, ri64
                                            }
    }
    */
    LPP_REPORT_AMOUNT_ENUM_UINT32           enReportAmount;
    LPP_REPORT_INTERVAL_ENUM_UINT32         enReportInterval;
}LPP_MTA_COMMON_PERIODICAL_REPORT_STRU;


typedef struct
{
    /*
    HorizontalAccuracy ::= SEQUENCE {
        accuracy        INTEGER(0..127),
        confidence      INTEGER(0..100),
        ...
    }
    */
    VOS_UINT32          bitOpHorizontalAccuracyExt  :1;
    VOS_UINT32          bitOpSpare                  :31;

    VOS_UINT8           ucAccuracy;
    VOS_UINT8           ucConfidence;
    VOS_UINT8           aucRes[2];
}LPP_MTA_COMMON_HORIZONTAL_ACCURACY_STRU;


typedef struct
{
    /*
    VerticalAccuracy ::= SEQUENCE {
        accuracy        INTEGER(0..127),
        confidence      INTEGER(0..100),
        ...
    }
    */
    VOS_UINT32          bitOpVerticalAccuracyExt:1;
    VOS_UINT32          bitOpSpare              :31;

    VOS_UINT8           ucAccuracy;
    VOS_UINT8           ucConfidence;
    VOS_UINT8           aucRes[2];
}LPP_MTA_COMMON_VERTICAL_ACCURACY_STRU;


typedef struct
{
    /*
    ResponseTime ::= SEQUENCE {
        time            INTEGER (1..128),
        ...
    }
    */
    VOS_UINT32          bitOpResponseTimeExt:1;
    VOS_UINT32          bitOpSpare          :31;

    VOS_UINT8           ucTime;
    VOS_UINT8           aucRes[3];
}LPP_MTA_COMMON_RESPONSE_TIME_STRU;


typedef struct
{
    /*
    QoS ::= SEQUENCE {
        horizontalAccuracy          HorizontalAccuracy      OPTIONAL,   -- Need ON
        verticalCoordinateRequest   BOOLEAN,
        verticalAccuracy            VerticalAccuracy        OPTIONAL,   -- Need ON
        responseTime                ResponseTime            OPTIONAL,   -- Need ON
        velocityRequest             BOOLEAN,
        ...
    }
    */
    VOS_UINT32                              bitOpQoSExt             :1;
    VOS_UINT32                              bitOpHoriazontalAccuracy:1;
    VOS_UINT32                              bitOpVerticalAccuracy   :1;
    VOS_UINT32                              bitOpResponseTime       :1;
    VOS_UINT32                              bitOpSpare              :28;

    LPP_MTA_COMMON_HORIZONTAL_ACCURACY_STRU stHorizontalAccuracy;
    VOS_BOOL                                bVerticalCoordinateRequest;
    LPP_MTA_COMMON_VERTICAL_ACCURACY_STRU   stVerticalAccuracy;
    LPP_MTA_COMMON_RESPONSE_TIME_STRU       stResponseTime;
    VOS_BOOL                                bVelocityReq;
}LPP_MTA_COMMON_QOS_STRU;


typedef struct
{
    /*
    LocationCoordinateTypes ::= SEQUENCE {
        ellipsoidPoint                                          BOOLEAN,
        ellipsoidPointWithUncertaintyCircle                     BOOLEAN,
        ellipsoidPointWithUncertaintyEllipse                    BOOLEAN,
        polygon                                                 BOOLEAN,
        ellipsoidPointWithAltitude                              BOOLEAN,
        ellipsoidPointWithAltitudeAndUncertaintyEllipsoid       BOOLEAN,
        ellipsoidArc                                            BOOLEAN,
        ...
    }
    */
    VOS_UINT32                  bitOpExt    :1;
    VOS_UINT32                  bitSpare    :31;

    VOS_BOOL                    bEllipsoidPoint;
    VOS_BOOL                    bEllipsoidPointWithUncertaintyCircle;
    VOS_BOOL                    bEllipsoidPointWithUncertaintyEllipse;
    VOS_BOOL                    bPolygon;
    VOS_BOOL                    bEllipsoidPointWithAltitude;
    VOS_BOOL                    bEllipsoidPointWithAltitudeAndUncertaintyEllipsoid;
    VOS_BOOL                    bEllipsoidArc;
}LPP_MTA_COMMON_LOCATION_COORDINATE_TYPE_STRU;


typedef struct
{
    /*
    VelocityTypes ::= SEQUENCE {
        horizontalVelocity                                      BOOLEAN,
        horizontalWithVerticalVelocity                          BOOLEAN,
        horizontalVelocityWithUncertainty                       BOOLEAN,
        horizontalWithVerticalVelocityAndUncertainty            BOOLEAN,
        ...
    }
    */
    VOS_UINT32              bitOpExt    :1;
    VOS_UINT32              bitSpare    :31;

    VOS_BOOL                bHorizontalVelocity;
    VOS_BOOL                bHorizontalWithVerticalVelocity;
    VOS_BOOL                bHorizontalVelocityWithUncertainty;
    VOS_BOOL                bHorizontalWithVerticalVelocityAndUncertainty;
}LPP_MTA_COMMON_VELOCITY_TYPE_STRU;


typedef struct
{
    /*
    CommonIEsRequestLocationInformation ::= SEQUENCE {
        locationInformationType     LocationInformationType,
        triggeredReporting          TriggeredReportingCriteria  OPTIONAL,   -- Cond ECID
        periodicalReporting         PeriodicalReportingCriteria OPTIONAL,   -- Need ON
        additionalInformation       AdditionalInformation       OPTIONAL,   -- Need ON
        qos                         QoS                         OPTIONAL,   -- Need ON
        environment                 Environment                 OPTIONAL,   -- Need ON
        locationCoordinateTypes     LocationCoordinateTypes     OPTIONAL,   -- Need ON
        velocityTypes               VelocityTypes               OPTIONAL,   -- Need ON
        ...
    }
    */
   VOS_UINT32                                   bitOpCommonIEsReqLocationInfoExt:1;
   VOS_UINT32                                   bitOpTriggeredReportCriteria    :1;
   VOS_UINT32                                   bitOpPeriodicalReportCriteria   :1;
   VOS_UINT32                                   bitOPAddtionInfo                :1;
   VOS_UINT32                                   bitOpQos                        :1;
   VOS_UINT32                                   bitOpEnvironment                :1;
   VOS_UINT32                                   bitOpLocationCoordinateType     :1;
   VOS_UINT32                                   bitOPVelocityTypes              :1;
   VOS_UINT32                                   bitOpSpare                      :24;

   LPP_LOCATION_INFO_TYPE_ENUM_UINT8            enLocationInformationType;
   VOS_UINT8                                    aucRsv1[3];
   LPP_MTA_COMMON_TRIGGER_REPORT_CRITERIA_STRU  stTriggerReportCriteria;
   LPP_MTA_COMMON_PERIODICAL_REPORT_STRU        stPeriodReport;
   LPP_ADDITON_REPORT_ENUM_UNIT8                enAdditonInfo;
   VOS_UINT8                                    aucRsv2[3];
   LPP_MTA_COMMON_QOS_STRU                      stQos;
   LPP_ENVIRONMENT_ENUM_UINT8                   enEnvironment;
   VOS_UINT8                                    aucRsv3[3];
   LPP_MTA_COMMON_LOCATION_COORDINATE_TYPE_STRU stLocationCoordinateType;
   LPP_MTA_COMMON_VELOCITY_TYPE_STRU            stVeloctytype;
}LPP_MTA_COMMON_IES_REQ_LOCATION_INFO_STRU;


typedef struct
{
    /*
    GNSS-PositioningInstructions ::= SEQUENCE {
        gnss-Methods                GNSS-ID-Bitmap,
        fineTimeAssistanceMeasReq   BOOLEAN,
        adrMeasReq                  BOOLEAN,
        multiFreqMeasReq            BOOLEAN,
        assistanceAvailability      BOOLEAN,
        ...
    }
    */
    VOS_UINT32                          bitOpGNSSPositionInstructionExt :1;
    VOS_UINT32                          bitOpSpare                      :31;

    LPP_MTA_COMMON_GNSS_ID_BITMAP_STRU  stGNSSMethods;
    VOS_BOOL                            bFineTimeAssistanceMeasReq;
    VOS_BOOL                            bAdrMeasReq;
    VOS_BOOL                            bMultiFreqMeasReq;
    VOS_BOOL                            bAssistanceAvailability;
}LPP_MTA_GNSS_POSITION_INSTRUCTION_STRU;


typedef struct
{
    /*
    A-GNSS-RequestLocationInformation ::= SEQUENCE {
        gnss-PositioningInstructions        GNSS-PositioningInstructions,
        ...
    }
    */
    VOS_UINT32                                  bitOpAGNSSReqLocationInfoExt:1;
    VOS_UINT32                                  bitOpSpare                  :31;

    LPP_MTA_GNSS_POSITION_INSTRUCTION_STRU      stGNSSPositonINsturction;
}LPP_MTA_AGNSS_REQ_LOCATION_INFO_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                      /*_H2ASN_Skip*/
    VOS_UINT32                                  ulMsgId;                /*_H2ASN_Skip*/ /* ��Ϣͷ */

    VOS_UINT32                                  ulSessionId;            /*��ǰsessionID*/
    LPP_MTA_COMMON_IES_REQ_LOCATION_INFO_STRU   stCommonIESReqLocInfo;
    LPP_MTA_AGNSS_REQ_LOCATION_INFO_STRU        stGnssReqLocationInfo; /*AT��û���ҵ���Ӧ�Ľṹ*/
}LPP_MTA_GNSS_LOCATION_INFO_REQ_STRU;/*27.007 8.55-9*/

typedef struct
{
    /*
    GNSS-TimeModelElement ::= SEQUENCE {
        gnss-TimeModelRefTime       INTEGER (0..65535),
        tA0                         INTEGER (-67108864..67108863),
        tA1                         INTEGER (-4096..4095)                   OPTIONAL,   -- Need ON
        tA2                         INTEGER (-64..63)                       OPTIONAL,   -- Need ON
        gnss-TO-ID                  INTEGER (1..15),
        weekNumber                  INTEGER (0..8191)                       OPTIONAL,   -- Need ON
        deltaT                      INTEGER (-128..127)                     OPTIONAL,   -- Need ON
        ...
    }
    */
    VOS_UINT32                      bitOpGNSSTimeModelElementExt:1;
    VOS_UINT32                      bitOpTA1                    :1;
    VOS_UINT32                      bitOpTA2                    :1;
    VOS_UINT32                      bitOpWeekNumber             :1;
    VOS_UINT32                      bitOpDeltaT                 :1;
    VOS_UINT32                      bitOpSpare                  :27;

    VOS_UINT32                      ulGNSSTimeModelRefTime;
    VOS_INT32                       lTA0;
    VOS_INT16                       sTA1;
    VOS_INT8                        cTA2;
    VOS_UINT8                       ucGNSSToId;
    VOS_UINT16                      usWeekNumber;
    VOS_INT16                       sDeltaT;
}LPP_MTA_GNSS_TIME_MODEL_ELEMENT_STRU;


typedef struct
{
    /*
    GNSS-TimeModelList ::= SEQUENCE (SIZE (1..15)) OF GNSS-TimeModelElement
    */
    VOS_UINT32                              ulGNSSTimeModelListCnt;
    LPP_MTA_GNSS_TIME_MODEL_ELEMENT_STRU    astGNSSTimeModelListArray[LPP_MAX_GNSS_TIME_MODE_ELMENT_LEN];
}LPP_MTA_GNSS_TIME_MODEL_LIST_STRU;


typedef struct
{
    /*
    DGNSS-CorrectionsElement ::= SEQUENCE {
        svID                SV-ID,
        iod                 BIT STRING (SIZE(11)),
        udre                INTEGER (0..3),
        pseudoRangeCor      INTEGER (-2047..2047),
        rangeRateCor        INTEGER (-127..127),
        udreGrowthRate      INTEGER (0..7)          OPTIONAL,   -- Need ON
        udreValidityTime    INTEGER (0..7)          OPTIONAL,   -- Need ON
        ...
    }
    */
    VOS_UINT32                  bitOpDGNSSCorrectElementExt :1;
    VOS_UINT32                  bitOpUdreGrowthRate         :1;
    VOS_UINT32                  bitOpUdreValidityTime       :1;
    VOS_UINT32                  bitOpSpare                  :29;

    LPP_MTA_COMMON_SV_ID_STRU   stSvId;
    VOS_UINT16                  usIod;
    VOS_UINT16                  usUdre;
    VOS_INT16                   sPseudoRangeCor;
    VOS_INT8                    cRangeRateCor;
    VOS_UINT8                   ucUdreGrowthRate;
    VOS_UINT8                   ucudreValidityTime;
    VOS_UINT8                   aucRes[3];
}LPP_MTA_DGNSS_CORRECT_ELEMENT_STRU;


typedef struct
{
    /*DGNSS-SatList ::= SEQUENCE (SIZE (1..64)) OF DGNSS-CorrectionsElement*/
    VOS_UINT32                              ulDGNSSSatListcnt;
    LPP_MTA_DGNSS_CORRECT_ELEMENT_STRU      astDGNSSCorrectElementArray[LPP_MAX_DGNSS_CORRECT_ELEMENT_LEN];
}LPP_MTA_DGNSS_SAT_LIST_STRU;
typedef struct
{
    /*
    DGNSS-SgnTypeElement ::= SEQUENCE {
        gnss-SignalID        GNSS-SignalID,
        gnss-StatusHealth    INTEGER (0..7),
        dgnss-SatList        DGNSS-SatList,
        ...
    }
    */
    VOS_UINT32                          bitOpDGNSSSignalTypeElementExt  :1;
    VOS_UINT32                          bitOpSpare                      :31;

    LPP_MTA_COMMON_GNSS_SIGNAL_ID_STRU  stGNSSSignalId;
    VOS_UINT8                           ucGNSSStatusHealth;
    VOS_UINT8                           aucRes[3];
    LPP_MTA_DGNSS_SAT_LIST_STRU         stDGNSSSatList;
}LPP_MTA_DGNSS_SGN_TYPE_ELEMENT_STRU;


typedef struct
{
    /*
    DGNSS-SgnTypeList ::= SEQUENCE (SIZE (1..3)) OF DGNSS-SgnTypeElement
    */
    VOS_UINT32                              ulDGNSSSgnTypeListCnt;
    LPP_MTA_DGNSS_SGN_TYPE_ELEMENT_STRU     astDGNSSSgnTypeListArray[LPP_MAX_DGNSS_SGN_TYPE_ELEMENT_LEN];
}LPP_MTA_DGNSS_SGN_TYPE_LIST_STRU;


typedef struct
{
    /*
    GNSS-DifferentialCorrections ::= SEQUENCE {
        dgnss-RefTime       INTEGER (0..3599),
        dgnss-SgnTypeList   DGNSS-SgnTypeList,
        ...
    }
    */
    VOS_UINT32                          bitOpGNSSDiffCorrectExt :1;
    VOS_UINT32                          bitOpSpare              :31;

    VOS_UINT16                          usDGNSSRefTime;
    VOS_UINT16                          aucRes;
    LPP_MTA_DGNSS_SGN_TYPE_LIST_STRU    stDGNSSSgnTypeList;
}LPP_MTA_GNSS_DIFF_CORRECT_STRU;


typedef struct
{

    VOS_UINT32                  bitOpStandClockModelListElementExt  :1;
    VOS_UINT32                  bitOpStanClockTgd                   :1;
    VOS_UINT32                  bitOpStanModelId                    :1;
    VOS_UINT32                  bitOpSpare                          :29;

    VOS_UINT16                  usStanClockToc;
    VOS_INT16                   sStanClockAF2;
    VOS_INT32                   lStanClockAF1;
    VOS_INT32                   lStanClockAF0;
    VOS_INT16                   sStanClockTgd;
    VOS_UINT16                  usStanModelID;
}LPP_MTA_STANDARD_CLOCK_MODEL_LIST_ELEMENT_STRU;


typedef struct
{
    /*
    StandardClockModelList ::= SEQUENCE (SIZE(1..2)) OF StandardClockModelElement
    */
    VOS_UINT32                                          ulStandardClockModelListCnt;
    LPP_MTA_STANDARD_CLOCK_MODEL_LIST_ELEMENT_STRU      astStandardClockModelListArray[LPP_MAX_STANDARD_CLOCK_ELEMENT_LEN];
}LPP_MTA_STANDARD_CLOCK_MODEL_LIST_STRU;


typedef struct
{
    /*
    NAV-ClockModel ::= SEQUENCE {
        navToc          INTEGER (0..37799),
        navaf2          INTEGER (-128..127),
        navaf1          INTEGER (-32768..32767),
        navaf0          INTEGER (-2097152..2097151),
        navTgd          INTEGER (-128..127),
        ...
    }
    */
    VOS_UINT32          bitOpNavClockModelExt   :1;
    VOS_UINT32          bitOpSpare              :31;

    VOS_UINT16          usNavToc;
    VOS_INT8            cNavaf2;
    VOS_UINT8           ucRES;
    VOS_INT32           lNavaf1;
    VOS_INT32           lNavaf0;
    VOS_INT8            cNavTgd;
    VOS_UINT8           aucRes[3];
}LPP_MTA_NAV_CLOCK_MODEL_STRU;


typedef struct
{
    /*
    CNAV-ClockModel ::= SEQUENCE {
        cnavToc         INTEGER (0..2015),
        cnavTop         INTEGER (0..2015),
        cnavURA0        INTEGER (-16..15),
        cnavURA1        INTEGER (0..7),
        cnavURA2        INTEGER (0..7),
        cnavAf2         INTEGER (-512..511),
        cnavAf1         INTEGER (-524288..524287),
        cnavAf0         INTEGER (-33554432..33554431),
        cnavTgd         INTEGER (-4096..4095),
        cnavISCl1cp     INTEGER (-4096..4095)           OPTIONAL,   -- Need ON
        cnavISCl1cd     INTEGER (-4096..4095)           OPTIONAL,   -- Need ON
        cnavISCl1ca     INTEGER (-4096..4095)           OPTIONAL,   -- Need ON
        cnavISCl2c      INTEGER (-4096..4095)           OPTIONAL,   -- Need ON
        cnavISCl5i5     INTEGER (-4096..4095)           OPTIONAL,   -- Need ON
        cnavISCl5q5     INTEGER (-4096..4095)           OPTIONAL,   -- Need ON
        ...
    }
    */
    VOS_UINT32                  bitOpCnavClockModelExt  :1;
    VOS_UINT32                  bitOpCnavISCl1cp        :1;
    VOS_UINT32                  bitOpCnavISCl1cd        :1;
    VOS_UINT32                  bitOpCnavISCl1ca        :1;
    VOS_UINT32                  bitOpCnavISCl2c         :1;
    VOS_UINT32                  bitOpCnavISCl5i5        :1;
    VOS_UINT32                  bitOpCnavISCl5q5        :1;
    VOS_UINT32                  bitOpSpare              :25;

    VOS_UINT16                  usCnavToc;
    VOS_UINT16                  uscnavTop;
    VOS_INT8                    cCnavUra0;
    VOS_UINT8                   ucCnavUra1;
    VOS_UINT8                   ucCnavUra2;
    VOS_UINT8                   ucRes;
    VOS_INT32                   lCnavAf2;
    VOS_INT32                   lCnavAf1;
    VOS_INT32                   lCnavAf0;
    VOS_INT16                   sCnavTgd;
    VOS_INT16                   sCnavISCl1cp;
    VOS_INT16                   sCnavISCl1cd;
    VOS_INT16                   sCnavISCl1ca;
    VOS_INT16                   sCnavISCl2c;
    VOS_INT16                   sCnavISCl5i5;
    VOS_INT16                   sCnavISCl5q5;
    VOS_UINT8                   aucRes[2];
}LPP_MTA_CNAV_CLOCK_MODEL_STRU;


typedef struct
{
    /*
    GLONASS-ClockModel ::= SEQUENCE {
        gloTau          INTEGER (-2097152..2097151),
        gloGamma        INTEGER (-1024..1023),
        gloDeltaTau     INTEGER (-16..15)               OPTIONAL,   -- Need ON
        ...
    }
    */
    VOS_UINT32                  bitOpGLONASSClockModelExt   :1;
    VOS_UINT32                  bitOpGloDeltaTau            :1;
    VOS_UINT32                  bitOpSpare                  :30;

    VOS_INT32                   lGloTau;
    VOS_INT16                   sGloGamma;
    VOS_INT16                   sGloDeltatau;
}LPP_MTA_GLONASS_CLOCK_MODEL_STRU;


typedef struct
{
    /*
    SBAS-ClockModel ::= SEQUENCE {
        sbasTo          INTEGER (0..5399),
        sbasAgfo        INTEGER (-2048..2047),
        sbasAgf1        INTEGER (-128..127),
        ...
    }
    */
    VOS_UINT32          bitOpSBASClockModelExt  :1;
    VOS_UINT32          bitOpSpare              :31;

    VOS_UINT16          usSbasTo;
    VOS_INT16           sSbasAgfo;
    VOS_INT16           sSbasAgf1;
    VOS_UINT8           aucRes[2];
}LPP_MTA_SBAS_CLOCK_MODEL_STRU;


typedef struct
{
    /*
    GNSS-ClockModel ::= CHOICE {
        standardClockModelList  StandardClockModelList,         -- Model-1
        nav-ClockModel          NAV-ClockModel,                 -- Model-2
        cnav-ClockModel         CNAV-ClockModel,                -- Model-3
        glonass-ClockModel      GLONASS-ClockModel,             -- Model-4
        sbas-ClockModel         SBAS-ClockModel,                -- Model-5
        ...
    }
    */
    VOS_UINT32                              bitOpGNSSClockModelExt  :1;
    VOS_UINT32                              bitOpSpare              :31;
    VOS_UINT32                              ulChoice;

    #define             LPP_STANDARD_CLOCK_MODEL_LIST_CHOSEN            0
    #define             LPP_NAV_CLOCK_MODEL_CHOSEN                      1
    #define             LPP_CNAV_CLOCK_MODEL_CHOSEN                     2
    #define             LPP_GLONASS_CLOCK_MODEL_CHOSEN                  3
    #define             LPP_SBAS_CLOCK_MODEL_CHOSEN                     4

    union
    {
        LPP_MTA_STANDARD_CLOCK_MODEL_LIST_STRU      stStandardClockModelList;
        LPP_MTA_NAV_CLOCK_MODEL_STRU                stNavClockModel;
        LPP_MTA_CNAV_CLOCK_MODEL_STRU               stCnavClockModel;
        LPP_MTA_GLONASS_CLOCK_MODEL_STRU            stGlonassClockModel;
        LPP_MTA_SBAS_CLOCK_MODEL_STRU               stSbasClockModel;
    }u;
}LPP_MTA_GNSS_CLOCK_MODEL_STRU;


typedef struct
{
    /*
    NavModelKeplerianSet ::= SEQUENCE {
        keplerToe        INTEGER (0 .. 16383),
        keplerW          INTEGER (-2147483648..2147483647),
        keplerDeltaN     INTEGER (-32768..32767),
        keplerM0         INTEGER (-2147483648..2147483647),
        keplerOmegaDot   INTEGER (-8388608.. 8388607),
        keplerE          INTEGER (0..4294967295),
        keplerIDot       INTEGER (-8192..8191),
        keplerAPowerHalf INTEGER (0.. 4294967295),
        keplerI0         INTEGER (-2147483648..2147483647),
        keplerOmega0     INTEGER (-2147483648..2147483647),
        keplerCrs        INTEGER (-32768..32767),
        keplerCis        INTEGER (-32768..32767),
        keplerCus        INTEGER (-32768..32767),
        keplerCrc        INTEGER (-32768..32767),
        keplerCic        INTEGER (-32768..32767),
        keplerCuc        INTEGER (-32768..32767),
        ...
    }
    */
    VOS_UINT32                      bitOpNavModelKeplerianSetExt:1;
    VOS_UINT32                      bitOpSpare:31;

    VOS_UINT32                      ulKeplerToe;
    VOS_INT32                       lKeplerW;
    VOS_INT32                       lKeplerDeltaN;
    VOS_INT32                       lKeplerM0;
    VOS_INT32                       lKeplerOmegaDot;
    VOS_UINT32                      ulKeplerE;
    VOS_INT32                       lKeplerIDot;
    VOS_UINT32                      ulKeplerAPowerHalf;
    VOS_INT32                       lKeplerI0;
    VOS_INT32                       lKeplerOmega0;
    VOS_INT16                       sKeplerCrs;
    VOS_INT16                       sKeplerCis;
    VOS_INT16                       sKeplerCus;
    VOS_INT16                       sKeplerCrc;
    VOS_INT16                       sKeplerCic;
    VOS_INT16                       sKeplerCuc;
}LPP_MTA_NAV_MODEL_KEPLERIAN_SET_STRU;


typedef struct
{
    /*
    ephemSF1Rsvd    SEQUENCE {
        reserved1       INTEGER (0..8388607),   -- 23-bit field
        reserved2       INTEGER (0..16777215),  -- 24-bit field
        reserved3       INTEGER (0..16777215),  -- 24-bit field
        reserved4       INTEGER (0..65535)      -- 16-bit field
    },
    */
    VOS_UINT32                  ulReserved1;
    VOS_UINT32                  ulReserved2;
    VOS_UINT32                  ulReserved3;
    VOS_UINT32                  ulReserved4;
}LPP_MTA_EPHEM_SF1_RSVD_STRU;


typedef struct
{
    /*
    addNAVparam     SEQUENCE {
         ephemCodeOnL2   INTEGER (0..3),
         ephemL2Pflag    INTEGER (0..1),
         ephemSF1Rsvd    SEQUENCE {
             reserved1       INTEGER (0..8388607),   -- 23-bit field
             reserved2       INTEGER (0..16777215),  -- 24-bit field
             reserved3       INTEGER (0..16777215),  -- 24-bit field
             reserved4       INTEGER (0..65535)      -- 16-bit field
         },
         ephemAODA       INTEGER (0..31)
     }
    */
    VOS_UINT8                       ucEphemCodeOnL2;
    VOS_UINT8                       ucEphemL2Pflag;
    VOS_UINT8                       aucRes[2];
    LPP_MTA_EPHEM_SF1_RSVD_STRU     stEphemSF1Rsvd;
    VOS_UINT32                      ulEphemAODA;
}LPP_MTA_ADD_NAV_PARAM_STRU;


typedef struct
{
    /*
    NavModelNAV-KeplerianSet ::= SEQUENCE {
        navURA          INTEGER (0..15),
        navFitFlag      INTEGER (0..1),
        navToe          INTEGER (0..37799),
        navOmega        INTEGER (-2147483648..2147483647),
        navDeltaN       INTEGER (-32768..32767),
        navM0           INTEGER (-2147483648..2147483647),
        navOmegaADot    INTEGER (-8388608..8388607),
        navE            INTEGER (0..4294967295),
        navIDot         INTEGER (-8192..8191),
        navAPowerHalf   INTEGER (0..4294967295),
        navI0           INTEGER (-2147483648..2147483647),
        navOmegaA0      INTEGER (-2147483648..2147483647),
        navCrs          INTEGER (-32768..32767),
        navCis          INTEGER (-32768..32767),
        navCus          INTEGER (-32768..32767),
        navCrc          INTEGER (-32768..32767),
        navCic          INTEGER (-32768..32767),
        navCuc          INTEGER (-32768..32767),
        addNAVparam     SEQUENCE {
            ephemCodeOnL2   INTEGER (0..3),
            ephemL2Pflag    INTEGER (0..1),
            ephemSF1Rsvd    SEQUENCE {
                reserved1       INTEGER (0..8388607),   -- 23-bit field
                reserved2       INTEGER (0..16777215),  -- 24-bit field
                reserved3       INTEGER (0..16777215),  -- 24-bit field
                reserved4       INTEGER (0..65535)      -- 16-bit field
            },
            ephemAODA       INTEGER (0..31)
        }   OPTIONAL,   -- Need ON
        ...
    }
    */
    VOS_UINT32                          bitOpNavClockNavKeplerianSetExt :1;
    VOS_UINT32                          bitOpAddNavParam                :1;
    VOS_UINT32                          bitOpSpare                      :30;

    VOS_UINT8                           ucNavUra;
    VOS_UINT8                           ucNavFitFlag;
    VOS_UINT16                          usNavToe;
    VOS_INT32                           lNavOmega;
    VOS_INT32                           lNavDeltaN;
    VOS_INT32                           lNavMo;
    VOS_INT32                           lNavOmegaADot;
    VOS_UINT32                          ulNavE;
    VOS_INT32                           lNavIDot;
    VOS_UINT32                          ulNavAPowerHalf;
    VOS_INT32                           lNavI0;
    VOS_INT32                           lNavOmegaA0;
    VOS_INT16                           sNavCrs;
    VOS_INT16                           sNavCis;
    VOS_INT16                           sNavCus;
    VOS_INT16                           sNavCrc;
    VOS_INT16                           sNavCic;
    VOS_INT16                           sNavCuc;
    LPP_MTA_ADD_NAV_PARAM_STRU          stAddNavParam;
}LPP_MTA_NAV_MODEL_NAV_KEPLERIAN_SET_STRU;


typedef struct
{
    /*
    NavModelCNAV-KeplerianSet ::= SEQUENCE {
        cnavTop             INTEGER (0..2015),
        cnavURAindex        INTEGER (-16..15),
        cnavDeltaA          INTEGER (-33554432..33554431),
        cnavAdot            INTEGER (-16777216..16777215),
        cnavDeltaNo         INTEGER (-65536..65535),
        cnavDeltaNoDot      INTEGER (-4194304..4194303),
        cnavMo              INTEGER (-4294967296..4294967295),
        cnavE               INTEGER (0..8589934591),
        cnavOmega           INTEGER (-4294967296..4294967295),
        cnavOMEGA0          INTEGER (-4294967296..4294967295),
        cnavDeltaOmegaDot   INTEGER (-65536..65535),
        cnavIo              INTEGER (-4294967296..4294967295),
        cnavIoDot           INTEGER (-16384..16383),
        cnavCis             INTEGER (-32768..32767),
        cnavCic             INTEGER (-32768..32767),
        cnavCrs             INTEGER (-8388608..8388607),
        cnavCrc             INTEGER (-8388608..8388607),
        cnavCus             INTEGER (-1048576..1048575),
        cnavCuc             INTEGER (-1048576..1048575),
        ...
    }
    */
    VOS_UINT32                      bitOpNAVModelCnavKeplerianSetExt:1;
    VOS_UINT32                      bitOpSpare                      :31;

    VOS_UINT16                      usCnavTop;
    VOS_INT16                       sCnavURAindex;
    VOS_INT32                       lCnavDeltaA;
    VOS_INT32                       lCnavAdot;
    VOS_INT32                       lCnavDeltaNo;
    VOS_INT32                       lCnavDeltaNoDot;
    VOS_INT64                       llCnavMo;
    VOS_UINT64                      ullCnavE;
    VOS_INT64                       llCnavOmega;
    VOS_INT64                       llCnavOMEGA0;
    VOS_INT32                       lCnavDeltaOmegaDot;
    VOS_INT64                       llCnavIo;
    VOS_INT32                       lCnavIoDot;
    VOS_INT16                       sCnavCis;
    VOS_INT16                       sCnavCic;
    VOS_INT32                       lCnavCrs;
    VOS_INT32                       lCnavCrc;
    VOS_INT32                       lCnavCus;
    VOS_INT32                       lCnavCuc;
}LPP_MTA_NAV_MODEL_CNAV_KEPLERIAN_SET_STRU;


typedef struct
{
    /*
    NavModel-GLONASS-ECEF ::= SEQUENCE {
        gloEn               INTEGER (0..31),
        gloP1               BIT STRING (SIZE(2)),
        gloP2               BOOLEAN,
        gloM                INTEGER (0..3),
        gloX                INTEGER (-67108864..67108863),
        gloXdot             INTEGER (-8388608..8388607),
        gloXdotdot          INTEGER (-16..15),
        gloY                INTEGER (-67108864..67108863),
        gloYdot             INTEGER (-8388608..8388607),
        gloYdotdot          INTEGER (-16..15),
        gloZ                INTEGER (-67108864..67108863),
        gloZdot             INTEGER (-8388608..8388607),
        gloZdotdot          INTEGER (-16..15),
        ...
    }
    */
    VOS_UINT32              bitOpNavModelGLONASSECEFExt :1;
    VOS_UINT32              bitOpSpare                  :31;

    VOS_UINT8               ucGloEn;
    VOS_UINT8               ucGloP1;
    VOS_UINT8               aucRes[2];
    VOS_BOOL                bGloP2;
    VOS_UINT32              ulGloM;
    VOS_INT32               lGloX;
    VOS_INT32               lGloXdot;
    VOS_INT32               lGloXdotdot;
    VOS_INT32               lGloY;
    VOS_INT32               lGloYdot;
    VOS_INT32               lGloYdotdot;
    VOS_INT32               lGloZ;
    VOS_INT32               lGloZdot;
    VOS_INT32               lGloZdotdot;
}LPP_MTA_NAV_MODEL_GLONASS_ECEF_STRU;


typedef struct
{

    VOS_UINT32                  bitOpNavModelSBASExt:1;
    VOS_UINT32                  bitOpSbasTo         :1;
    VOS_UINT32                  bitOpSpare          :30;

    VOS_UINT16                  sSbasTo;
    VOS_UINT16                  sSbasAccuracy;
    VOS_INT32                   lSbasXg;
    VOS_INT32                   lSbasYg;
    VOS_INT32                   lSbasZg;
    VOS_INT32                   lSbasXgDot;
    VOS_INT32                   lSbasYgDot;
    VOS_INT32                   lSbasZgDot;
    VOS_INT32                   lSbasXgDotDot;
    VOS_INT32                   lSbasYgDotDot;
    VOS_INT32                   lSbasZgDotDot;
}LPP_MTA_NAV_MODEL_SBAS_STRU;


typedef struct
{
    /*
    GNSS-OrbitModel ::= CHOICE {
        keplerianSet            NavModelKeplerianSet,           -- Model-1
        nav-KeplerianSet        NavModelNAV-KeplerianSet,       -- Model-2
        cnav-KeplerianSet       NavModelCNAV-KeplerianSet,      -- Model-3
        glonass-ECEF            NavModel-GLONASS-ECEF,          -- Model-4
        sbas-ECEF               NavModel-SBAS-ECEF,             -- Model-5
        ...
    }
    */
    VOS_UINT32                  bitOpGNSSOrbitModelExt  :1;
    VOS_UINT32                  bitOpSpare              :31;
    VOS_UINT32                  ulChoice;

    #define             LPP_NAV_MODEL_KEPLERIAN_SET_CHOSEN                   0
    #define             LPP_NAV_MODEL_NAV_KEPLERIAN_SET_CHOSEN               1
    #define             LPP_NAV_MODEL_CNAV_KEPLERIAN_SET_CHOSEN              2
    #define             LPP_NAV_MODEL_GLONASS_ECEF_CHOSEN                    3
    #define             LPP_NAV_MODEL_SBAS_CHOSEN                            4

    union
    {
        LPP_MTA_NAV_MODEL_KEPLERIAN_SET_STRU            stkeplerianSet;
        LPP_MTA_NAV_MODEL_NAV_KEPLERIAN_SET_STRU        stNavKeplerianSet;
        LPP_MTA_NAV_MODEL_CNAV_KEPLERIAN_SET_STRU       stCnavKeplerianSet;
        LPP_MTA_NAV_MODEL_GLONASS_ECEF_STRU             stGlonassEcef;
        LPP_MTA_NAV_MODEL_SBAS_STRU                     stSbasEcef;
    }u;
}LPP_MTA_GNSS_ORBIT_MODEL_STRU;


typedef struct
{
    /*
    GNSS-NavModelSatelliteElement ::= SEQUENCE {
        svID                SV-ID,
        svHealth            BIT STRING (SIZE(8)),
        iod                 BIT STRING (SIZE(11)),
        gnss-ClockModel     GNSS-ClockModel,
        gnss-OrbitModel     GNSS-OrbitModel,
        ...
    }
    */
    VOS_UINT32                      bitOpGNSSNavModelSatelliteListElementExt:1;
    VOS_UINT32                      bitOpSpare                              :31;

    LPP_MTA_COMMON_SV_ID_STRU       stSvId;
    VOS_UINT16                      usSvHealth;
    VOS_UINT16                      usIod;
    LPP_MTA_GNSS_CLOCK_MODEL_STRU   stGNSSClockModel;
    LPP_MTA_GNSS_ORBIT_MODEL_STRU   stGNSSOrbitModel;
}LPP_MTA_GNSS_NAV_MODEL_SATELLITE_LIST_ELEMENT_STRU;


typedef struct
{
    /*
    GNSS-NavModelSatelliteList ::= SEQUENCE (SIZE(1..64)) OF GNSS-NavModelSatelliteElement
    */
    VOS_UINT32                                              ulGNSSNavModelSatelliteListCnt;
    LPP_MTA_GNSS_NAV_MODEL_SATELLITE_LIST_ELEMENT_STRU      astGNSSNavModelSatelliteListArray[LPP_MAX_NAV_MODEL_SAT_ELEMENT_LEN];
}LPP_MTA_GNSS_NAV_MODEL_SATELLITE_LIST_STRU;


typedef struct
{
    /*
    GNSS-NavigationModel ::= SEQUENCE {
        nonBroadcastIndFlag     INTEGER (0..1),
        gnss-SatelliteList      GNSS-NavModelSatelliteList,
        ...
    }
    */
    VOS_UINT32                                  bitOpGNSSNavigationModelExt :1;
    VOS_UINT32                                  bitOpSpare                  :31;

    VOS_UINT8                                   ucNonBroadcastIndFlag;
    VOS_UINT8                                   aucRes[3];
    LPP_MTA_GNSS_NAV_MODEL_SATELLITE_LIST_STRU  stGNSSSatelliteList;
}LPP_MTA_GNSS_NAVIGATION_MODEL_STRU;


typedef struct
{
    /*
    BadSignalElement ::= SEQUENCE {
        badSVID             SV-ID,
        badSignalID         GNSS-SignalIDs  OPTIONAL,   -- Need OP
        ...
    }
    */
    VOS_UINT32                              bitOpBadSignalElementExt:1;
    VOS_UINT32                              bitOpGNSSSignalIds      :1;
    VOS_UINT32                              bitOpSpare              :30;

    LPP_MTA_COMMON_SV_ID_STRU               stBadSvid;
    LPP_MTA_COMMON_GNSS_SIGNAL_IDS_STRU     stBadSignalId;
}LPP_MTA_GNSS_BAD_SIGNAL_ELEMENT_STRU;


typedef struct
{
    /*
    GNSS-BadSignalList ::= SEQUENCE (SIZE(1..64)) OF BadSignalElement
    */
    VOS_UINT32                                  ulGNSSBadSignalListCnt;
    LPP_MTA_GNSS_BAD_SIGNAL_ELEMENT_STRU        stGNSSBadSignalListArray[LPP_MAX_BAD_SIGNAL_ELEMENT_LEN];
}LPP_MTA_GNSS_BAD_SIGNAL_LIST_STRU;


typedef struct
{
    /*
    GNSS-RealTimeIntegrity ::= SEQUENCE {
        gnss-BadSignalList  GNSS-BadSignalList,
        ...
    }
    */
    VOS_UINT32                              bitOpGNSSRealtimeIntergrityExt  :1;
    VOS_UINT32                              bitOpSpare                      :31;

    LPP_MTA_GNSS_BAD_SIGNAL_LIST_STRU       stGNSSBadSignalList;
}LPP_MTA_GNSS_REALTIME_INTERGRITY_STRU;


typedef struct
{
    /*
    GNSS-DataBitsSgnElement ::= SEQUENCE {
        gnss-SignalType         GNSS-SignalID,
        gnss-DataBits           BIT STRING (SIZE (1..1024)),
        ...
    }
    */
    VOS_UINT32                          bitOpGNSSDataBitsSgnElementExt  :1;
    VOS_UINT32                          bitOpSpare                      :31;

    LPP_MTA_COMMON_GNSS_SIGNAL_ID_STRU  stGNSSSignalType;
    VOS_UINT32                          ulGnssDataBitsNum;
    VOS_UINT8                           aucGNSSDataBitsArray[LPP_MAX_GNSS_DATA_BITS_LEN];
}LPP_MTA_GNSS_DATA_BITS_SGN_ELEMENT_STRU;


typedef struct
{
    /*
    GNSS-DataBitsSgnList ::= SEQUENCE (SIZE(1..8)) OF GNSS-DataBitsSgnElement
    */
    VOS_UINT32                                  ulGNSSDataBitsSgnListCnt;
    LPP_MTA_GNSS_DATA_BITS_SGN_ELEMENT_STRU     astGNSSDataBitsSgnElementArray[LPP_MAX_GNSS_DATA_BITS_SGN_ELEMENT_LEN];
}LPP_MTA_GNSS_DATA_BITS_SGN_LIST_STRU;


typedef struct
{
    /*
    GNSS-DataBitsSatElement ::= SEQUENCE {
        svID                    SV-ID,
        gnss-DataBitsSgnList    GNSS-DataBitsSgnList,
        ...
    }
    */
    VOS_UINT32                                      bitOpGNSSDataBitsSatElementExt  :1;
    VOS_UINT32                                      bitOpSpare                      :31;

    LPP_MTA_COMMON_SV_ID_STRU                       stSvId;
    LPP_MTA_GNSS_DATA_BITS_SGN_LIST_STRU     stGNSSDataBitsSgnList;
}LPP_MTA_GNSS_DATA_BITS_SAT_ELEMENT_STRU;


typedef struct
{
    /*
    GNSS-DataBitsSatList ::= SEQUENCE (SIZE(1..64))OF GNSS-DataBitsSatElement
    */
    VOS_UINT32                                      ulGNSSDataBitsSatListCnt;
    LPP_MTA_GNSS_DATA_BITS_SAT_ELEMENT_STRU         astGNSSDataBitsSatListArray[LPP_MAX_GNSS_DATA_BITS_SAT_ELEMENT_LEN];
}LPP_MTA_GNSS_DATA_BITS_SATLIST_STRU;


typedef struct
{
    /*
    GNSS-DataBitAssistance ::= SEQUENCE {
        gnss-TOD                INTEGER (0..3599),
        gnss-TODfrac            INTEGER (0..999)        OPTIONAL,   -- Need ON
        gnss-DataBitsSatList    GNSS-DataBitsSatList,
        ...
    }
    */
    VOS_UINT32                          bitOpGNSSDataBitAssistExt:1;
    VOS_UINT32                          bitOpGNSSTodFrac         :1;
    VOS_UINT32                          bitOpSpare               :30;

    VOS_UINT16                          usGNSSTod;
    VOS_UINT16                          usGNSSTodFrac;
    LPP_MTA_GNSS_DATA_BITS_SATLIST_STRU stGNSSDataBitsSatlist;
}LPP_MTA_GNSS_DATA_BIT_ASSIST_STRU;


typedef struct
{
    /*
    GNSS-AcquisitionAssistElement  ::= SEQUENCE {
        svID                        SV-ID,
        doppler0                    INTEGER (-2048..2047),
        doppler1                    INTEGER (0..63),
        dopplerUncertainty          INTEGER (0..4),
        codePhase                   INTEGER (0..1022),
        intCodePhase                INTEGER (0..127),
        codePhaseSearchWindow       INTEGER (0..31),
        azimuth                     INTEGER (0..511),
        elevation                   INTEGER (0..127),
        ...,
        codePhase1023               BOOLEAN             OPTIONAL,   -- Need OP
        dopplerUncertaintyExt-r10   ENUMERATED {    d60,
                                                    d80,
                                                    d100,
                                                    d120,
                                                    noInformation, ... }    OPTIONAL    -- Need ON
    }
    */
    VOS_UINT32                      bitOpGNSSAcquisitAssistElementExt   :1;
    VOS_UINT32                      bitOpCodePhase1023                  :1;
    VOS_UINT32                      bitOpDopplerUncertaintyExtR10       :1;
    VOS_UINT32                      bitOpSpare                          :29;

    LPP_MTA_COMMON_SV_ID_STRU       stSvId;
    VOS_INT16                       sDoppler0;
    VOS_UINT8                       ucDoppler1;
    VOS_UINT8                       ucDopplerUncertainty;
    VOS_UINT16                      usCodePhase;
    VOS_UINT8                       ucIntCodePhase;
    VOS_UINT8                       ucCodePhaseSearchWindow;
    VOS_UINT8                       ucAzimuth;
    VOS_UINT8                       ucElevation;
    VOS_UINT8                       ucRes;
    LPP_DOPPLER_EXTR10_ENUM_UINT8   enDopplerUncertaintyExtR10;
    VOS_BOOL                        bCodePhase1023;
}LPP_MTA_GNSS_ACQUISIT_ASSIST_ELEMENT_STRU;


typedef struct
{
    /*
    GNSS-AcquisitionAssistList ::= SEQUENCE (SIZE(1..64)) OF GNSS-AcquisitionAssistElement
    */
    VOS_UINT32                                  ulGNSSAcquisitAssitListCnt;
    LPP_MTA_GNSS_ACQUISIT_ASSIST_ELEMENT_STRU   astGNSSAcquisitAssistListArray[LPP_MAX_GNSS_ACQUSITON_ASSIST_ELMENT_LEN];
}LPP_MTA_GNSS_ACQUISIT_ASSIST_LIST_STRU;


typedef struct
{
    /*
    GNSS-AcquisitionAssistance ::= SEQUENCE {
        gnss-SignalID               GNSS-SignalID,
        gnss-AcquisitionAssistList  GNSS-AcquisitionAssistList,
        ...,
        confidence-r10              INTEGER (0..100)    OPTIONAL    -- Need ON
    }
    */
    VOS_UINT32                              bitOpGNSSAcquisitAssistExt  :1;
    VOS_UINT32                              bitOpConfidenceR10          :1;
    VOS_UINT32                              bitOpSpare                  :30;

    LPP_MTA_COMMON_GNSS_SIGNAL_ID_STRU      stGNSSSignalId;
    LPP_MTA_GNSS_ACQUISIT_ASSIST_LIST_STRU  stGNSSAcquisitAssistList;
    VOS_UINT32                              ulConfidenceNum;
    VOS_UINT32                              ulConfidenceR10;
}LPP_MTA_GNSS_ACQUISIT_ASSIST_STRU;


typedef struct
{
    /*
    AlmanacKeplerianSet ::= SEQUENCE {
        svID                    SV-ID,
        kepAlmanacE             INTEGER (0..2047),
        kepAlmanacDeltaI        INTEGER (-1024..1023),
        kepAlmanacOmegaDot      INTEGER (-1024..1023),
        kepSVHealth             INTEGER (0..15),
        kepAlmanacAPowerHalf    INTEGER (-65536..65535),
        kepAlmanacOmega0        INTEGER (-32768..32767),
        kepAlmanacW             INTEGER (-32768..32767),
        kepAlmanacM0            INTEGER (-32768..32767),
        kepAlmanacAF0           INTEGER (-8192..8191),
        kepAlmanacAF1           INTEGER (-1024..1023),
        ...
    }
    */
    VOS_UINT32                  bitOpAlmanacKeplerianSetExt :1;
    VOS_UINT32                  bitOpSpare                  :31;

    LPP_MTA_COMMON_SV_ID_STRU   stSvId;
    VOS_UINT16                  usKepAlmanacE;
    VOS_INT16                   sKepAlmanacDeltaI;
    VOS_INT16                   sKepAlmanacOmegaDot;
    VOS_UINT16                  usKepSVHealth;
    VOS_INT32                   ulKepAlmanacAPowerHalf;
    VOS_INT16                   sKepAlmanacOmega0;
    VOS_INT16                   sKepAlmanacW;
    VOS_INT16                   sKepAlmanacM0;
    VOS_INT16                   sKepAlmanacAF0;
    VOS_INT16                   sKepAlmanacAF1;
    VOS_UINT8                   usRes[2];
}LPP_MTA_ALMANAC_KEPLERIAN_SET_STRU;


typedef struct
{
    /*
    AlmanacNAV-KeplerianSet ::= SEQUENCE {
        svID                    SV-ID,
        navAlmE                 INTEGER (0..65535),
        navAlmDeltaI            INTEGER (-32768..32767),
        navAlmOMEGADOT          INTEGER (-32768..32767),
        navAlmSVHealth          INTEGER (0..255),
        navAlmSqrtA             INTEGER (0..16777215),
        navAlmOMEGAo            INTEGER (-8388608..8388607),
        navAlmOmega             INTEGER (-8388608..8388607),
        navAlmMo                INTEGER (-8388608..8388607),
        navAlmaf0               INTEGER (-1024..1023),
        navAlmaf1               INTEGER (-1024..1023),
        ...
    }
    */
    VOS_UINT32                  bitOpAlmanacNAVKeplerianSetExt  :1;
    VOS_UINT32                  bitOpSpare                      :31;

    LPP_MTA_COMMON_SV_ID_STRU   stSvId;
    VOS_UINT16                  usNavAlmE;
    VOS_INT16                   sNavAlmDeltaI;
    VOS_INT16                   sNavAlmOMEGADOT;
    VOS_UINT16                  usNavAlmSVHealth;
    VOS_UINT32                  ulNavAlmSqrtA;
    VOS_INT32                   lNavAlmOMEGAo;
    VOS_INT32                   lNavAlmOmega;
    VOS_INT32                   lNavAlmMo;
    VOS_INT16                   sNavAlmaf0;
    VOS_INT16                   sNavAlmaf1;
}LPP_MTA_ALMANAC_NAV_KEPLERIAN_SET_STRU;


typedef struct
{
    /*
    AlmanacReducedKeplerianSet ::= SEQUENCE {
        svID                    SV-ID,
        redAlmDeltaA            INTEGER (-128..127),
        redAlmOmega0            INTEGER (-64..63),
        redAlmPhi0              INTEGER (-64..63),
        redAlmL1Health          BOOLEAN,
        redAlmL2Health          BOOLEAN,
        redAlmL5Health          BOOLEAN,
        ...
    }
    */
    VOS_UINT32                  bitOpAlmanacReducedKeplerianSetExt:1;
    VOS_UINT32                  bitOpSpare:31;

    LPP_MTA_COMMON_SV_ID_STRU   stSvId;
    VOS_INT8                    cRedAlmDeltaA;
    VOS_INT8                    cRedAlmOmega0;
    VOS_INT8                    cRedAlmPhi0;
    VOS_UINT8                   ucRes;
    VOS_BOOL                    bRedAlmL1Health;
    VOS_BOOL                    bRedAlmL2Health;
    VOS_BOOL                    bRedAlmL5Health;
}LPP_MTA_ALMANAC_REDUCED_KEPLERIAN_SET_STRU;


typedef struct
{

    VOS_UINT32                  bitOpAlmanacMidiAlmanacSetExt   :1;
    VOS_UINT32                  bitOpSpare                      :31;

    LPP_MTA_COMMON_SV_ID_STRU   stSvId;
    VOS_UINT16                  usMidiAlmE;
    VOS_INT16                   sMidiAlmDelatI;
    VOS_INT16                   sMidiAlmOmegaDot;
    VOS_UINT8                   aucRes[2];
    VOS_UINT32                  ulMidiAlmSqrtA;
    VOS_INT16                   sMidiAlmOmega0;
    VOS_INT16                   sMidiAlmOmega;
    VOS_INT16                   sMidiAlmMo;
    VOS_INT16                   sMidiAlmaf0;
    VOS_INT16                   sMidiAlmaf1;
    VOS_INT16                   aucRes1[2];
    VOS_BOOL                    bMidiAlmL1Health;
    VOS_BOOL                    bmidiAlmL2Health;
    VOS_BOOL                    bMidiAlmL5Health;
}LPP_MTA_ALMANAC_MIDI_ALMANAC_STRU;


typedef struct
{

    VOS_UINT32                          bitOpAlmanacGLONASSAlmanacSetExt:1;
    VOS_UINT32                          bitOpGloAlmMa                   :1;
    VOS_UINT32                          bitOpSpare                      :30;

    VOS_UINT16                          usGloAlmNa;
    VOS_UINT8                           ucGloAlmNa1;
    VOS_UINT8                           ucGloAlmHa;
    VOS_INT32                           lGloAlmLambdaA;
    VOS_UINT32                          ulGloAlmtlambdaA;
    VOS_INT32                           lGloAlmDeltaIa;
    VOS_INT32                           lGloAlmDeltaTA;
    VOS_INT16                           sGloAlmDeltaTdotA;
    VOS_UINT16                          usGloAlmEpsilonA;
    VOS_INT16                           sGloAlmOmegaA;
    VOS_INT16                           sGloAlmTauA;
    VOS_UINT8                           ucGloAlmCA;
    VOS_UINT8                           ucGloAlmMA;
    VOS_UINT8                           aucRes[2];
}LPP_MTA_ALMANAC_GLONASS_ALMANAC_SET_STRU;


typedef struct
{
    /*
    AlmanacECEF-SBAS-AlmanacSet ::= SEQUENCE {
        sbasAlmDataID           INTEGER (0..3),
        svID                    SV-ID,
        sbasAlmHealth           BIT STRING (SIZE(8)),
        sbasAlmXg               INTEGER (-16384..16383),
        sbasAlmYg               INTEGER (-16384..16383),
        sbasAlmZg               INTEGER (-256..255),
        sbasAlmXgdot            INTEGER (-4..3),
        sbasAlmYgDot            INTEGER (-4..3),
        sbasAlmZgDot            INTEGER (-8..7),
        sbasAlmTo               INTEGER (0..2047),
        ...
    }
    */
    VOS_UINT32                      bitOpAlmanacECEFSBASAlmanacSetExt   :1;
    VOS_UINT32                      bitOpSpare                          :31;

    VOS_UINT32                      ulSbasAlmDataID;
    LPP_MTA_COMMON_SV_ID_STRU       stSvId;
    VOS_UINT8                       ucSbasAlmHealth;
    VOS_UINT8                       ucRes[3];
    VOS_INT16                       sSbasAlmXg;
    VOS_INT16                       sSbasAlmYg;
    VOS_INT16                       cSbasAlmZg;
    VOS_UINT16                      usSbasAlmTo;
    VOS_INT8                        cSbasAlmXgdot;
    VOS_INT8                        cSbasAlmYgdot;/*forconfirm*/
    VOS_INT8                        cSbasAlmZgdot;
    VOS_UINT8                       ucRes1;
}LPP_MTA_ALMANAC_ECEF_SBAS_ALMANAC_STRU;
typedef struct
{
    /*
    GNSS-AlmanacElement ::= CHOICE {
        keplerianAlmanacSet     AlmanacKeplerianSet,        -- Model-1
        keplerianNAV-Almanac    AlmanacNAV-KeplerianSet,    -- Model-2
        keplerianReducedAlmanac AlmanacReducedKeplerianSet, -- Model-3
        keplerianMidiAlmanac    AlmanacMidiAlmanacSet,      -- Model-4
        keplerianGLONASS        AlmanacGLONASS-AlmanacSet,  -- Model-5
        ecef-SBAS-Almanac       AlmanacECEF-SBAS-AlmanacSet,-- Model-6
        ...
    }
    */
    VOS_UINT32          bitOpGNSSAlmanacElementExt  :1;
    VOS_UINT32          bitOpSpare                  :31;
    VOS_UINT32                              ulChoice;

    #define             LPP_ALMANAC_KEPLERIAN_SET_CHOSEN                   0
    #define             LPP_ALMANAC_NAV_KEPLERIAN_SET_CHOSEN               1
    #define             LPP_ALMANAC_REDUCED_KEPLERIAN_SET_CHOSEN           2
    #define             LPP_ALMANAC_MIDI_ALMANAC_CHOSEN                    3
    #define             LPP_ALMANAC_GLONASS_ALMANAC_SET_CHOSEN             4
    #define             LPP_ALMANAC_ECEF_SBAS_ALMANAC_CHOSEN               5

    union
    {
        LPP_MTA_ALMANAC_KEPLERIAN_SET_STRU            stKeplerianAlmanacSet;
        LPP_MTA_ALMANAC_NAV_KEPLERIAN_SET_STRU        stKeplerianNAVAlmanac;
        LPP_MTA_ALMANAC_REDUCED_KEPLERIAN_SET_STRU    stKeplerianReducedAlmanac;
        LPP_MTA_ALMANAC_MIDI_ALMANAC_STRU             stKeplerianMidiAlmanac;
        LPP_MTA_ALMANAC_GLONASS_ALMANAC_SET_STRU      stKeplerianGLONASS;
        LPP_MTA_ALMANAC_ECEF_SBAS_ALMANAC_STRU        stEcefSbasAlmanac;
    }u;
}LPP_MTA_GNSS_ALMANAC_ELEMENT_STRU;


typedef struct
{
    /*
    GNSS-AlmanacList ::= SEQUENCE (SIZE(1..64)) OF GNSS-AlmanacElement
    */
    VOS_UINT32                          ulGNSSAlmanacListCnt;
    LPP_MTA_GNSS_ALMANAC_ELEMENT_STRU   astGNSSAlmanacListArray[LPP_MAX_GNSS_ALMANAC_ELMENT_LEN];
}LPP_MTA_GNSS_ALMANAC_LIST_STRU;


typedef struct
{
    /*
    GNSS-Almanac ::= SEQUENCE {
        weekNumber                  INTEGER (0..255)    OPTIONAL,   -- Need ON
        toa                         INTEGER (0..255)    OPTIONAL,   -- Need ON
        ioda                        INTEGER (0..3)      OPTIONAL,   -- Need ON
        completeAlmanacProvided     BOOLEAN,
        gnss-AlmanacList            GNSS-AlmanacList,
        ...
    }
    */
    VOS_UINT32                      bitOpGNSSAlmanacExt:1;
    VOS_UINT32                      bitOpWeekNumber:1;
    VOS_UINT32                      bitOpToa:1;
    VOS_UINT32                      bitOpIoda:1;
    VOS_UINT32                      bitOpSpare:28;

    VOS_UINT8                       ucWeekNumber;
    VOS_UINT8                       ucToa;
    VOS_UINT8                       ucIoda;
    VOS_UINT8                       ucRes;
    VOS_BOOL                        bCompleteAlmanacProvided;
    LPP_MTA_GNSS_ALMANAC_LIST_STRU  stGNSSAlmanacList;
}LPP_MTA_GNSS_ALMANAC_STRU;


typedef struct
{
    /*
    UTC-ModelSet1 ::= SEQUENCE {
        gnss-Utc-A1         INTEGER (-8388608..8388607),
        gnss-Utc-A0         INTEGER (-2147483648..2147483647),
        gnss-Utc-Tot        INTEGER (0..255),
        gnss-Utc-WNt        INTEGER (0..255),
        gnss-Utc-DeltaTls   INTEGER (-128..127),
        gnss-Utc-WNlsf      INTEGER (0..255),
        gnss-Utc-DN         INTEGER (-128..127),
        gnss-Utc-DeltaTlsf  INTEGER (-128..127),
        ...
    }
    */
    VOS_UINT32              bitOpUTCModelSet1Ext:1;
    VOS_UINT32              bitOpSpare          :31;

    VOS_INT32               lGNSSUtcA1;
    VOS_INT32               lGNSSUtcA0;
    VOS_UINT8               ucGNSSUtcTot;
    VOS_UINT8               ucGNSSUtcWnt;
    VOS_INT8                cGNSSUtcDeltaTls;
    VOS_UINT8               ucGNSSUtcWnlsf;
    VOS_INT8                cGNSSUtcDn;
    VOS_INT8                cGNSSUtcDeltaTlsf;
    VOS_UINT8               aucRes[2];
}LPP_MTA_UTC_MODEL_SET1_STRU;


typedef struct
{
    /*
    UTC-ModelSet2 ::= SEQUENCE {
        utcA0               INTEGER (-32768..32767),
        utcA1               INTEGER (-4096..4095),
        utcA2               INTEGER (-64..63),
        utcDeltaTls         INTEGER (-128..127),
        utcTot              INTEGER (0..65535),
        utcWNot             INTEGER (0..8191),
        utcWNlsf            INTEGER (0..255),
        utcDN               BIT STRING (SIZE(4)),
        utcDeltaTlsf        INTEGER (-128..127),
        ...
    }
    */
    VOS_UINT32              bitOpUTCModelSet2Ext:1;
    VOS_UINT32              bitOpSpare          :31;

    VOS_INT16               sUtcA0;
    VOS_INT16               sUtcA1;
    VOS_INT8                cUtcA2;
    VOS_INT8                cUtcDeltaTls;
    VOS_UINT16              usUtcTot;
    VOS_UINT16              usUtcWnot;
    VOS_UINT8               ucUtcWnlsf;
    VOS_UINT8               ucUtcDn;
    VOS_INT8                cUtcDeltaTlsf;
    VOS_UINT8               aucRes[3];
}LPP_MTA_UTC_MODEL_SET2_STRU;


typedef struct
{
    /*
    UTC-ModelSet3 ::= SEQUENCE {
        nA                  INTEGER (1..1461),
        tauC                INTEGER (-2147483648..2147483647),
        b1                  INTEGER (-1024..1023)                   OPTIONAL,   -- Cond GLONASS-M
        b2                  INTEGER (-512..511)                     OPTIONAL,   -- Cond GLONASS-M
        kp                  BIT STRING (SIZE(2))                    OPTIONAL,   -- Cond GLONASS-M
        ...
    }
    */
    VOS_UINT32                      bitOpUTCModelSet3Ext:1;
    VOS_UINT32                      bitOpB1             :1;
    VOS_UINT32                      bitOpB2             :1;
    VOS_UINT32                      bitOpKp             :1;
    VOS_UINT32                      bitOpSpare          :28;

    VOS_UINT32                      ulNa;
    VOS_INT32                       lTauC;
    VOS_INT16                       sB1;
    VOS_INT16                       sB2;
    VOS_UINT32                      ulKp;
}LPP_MTA_UTC_MODEL_SET3_STRU;


typedef struct
{
    /*
    UTC-ModelSet4 ::= SEQUENCE {
        utcA1wnt            INTEGER (-8388608..8388607),
        utcA0wnt            INTEGER (-2147483648..2147483647),
        utcTot              INTEGER (0..255),
        utcWNt              INTEGER (0..255),
        utcDeltaTls         INTEGER (-128..127),
        utcWNlsf            INTEGER (0..255),
        utcDN               INTEGER (-128..127),
        utcDeltaTlsf        INTEGER (-128..127),
        utcStandardID       INTEGER (0..7),
        ...
    }
    */
    VOS_UINT32              bitOpUTCModelSet4Ext:1;
    VOS_UINT32              bitOpSpare          :31;

    VOS_INT32               lUtcA1wnt;
    VOS_INT32               lUtcA0wnt;
    VOS_UINT8               ucUtcTot;
    VOS_UINT8               ucUtcWnt;
    VOS_INT8                cUtcDeltaTls;
    VOS_UINT8               ucUtcWnlsf;
    VOS_INT8                cUtcDn;
    VOS_INT8                cUtcDeltaTlsf;
    VOS_UINT8               ucUtcStandardId;
    VOS_UINT8               ucRes;
}LPP_MTA_UTC_MODEL_SET4_STRU;


typedef struct
{
    /*
    GNSS-UTC-Model ::= CHOICE {
        utcModel1           UTC-ModelSet1,  -- Model-1
        utcModel2           UTC-ModelSet2,  -- Model-2
        utcModel3           UTC-ModelSet3,  -- Model-3
        utcModel4           UTC-ModelSet4,  -- Model-4
        ...
    }
    */
    VOS_UINT32                      bitOpGNSSUTCModelExt:1;
    VOS_UINT32                      bitOpSpare          :31;
    VOS_UINT32                      ulChoice;
    #define     LPP_UTC_MODEL1_CHOSEN  0
    #define     LPP_UTC_MODEL2_CHOSEN  1
    #define     LPP_UTC_MODEL3_CHOSEN  2
    #define     LPP_UTC_MODEL4_CHOSEN  3

    union
    {
        LPP_MTA_UTC_MODEL_SET1_STRU         stUtcModel1;
        LPP_MTA_UTC_MODEL_SET2_STRU         stUtcModel2;
        LPP_MTA_UTC_MODEL_SET3_STRU         stUtcModel3;
        LPP_MTA_UTC_MODEL_SET4_STRU         stUtcModel4;
    }u;
}LPP_MTA_GNSS_UTC_MODEL_STRU;


typedef struct
{
    /*
    GNSS-ID-GLONASS-SatElement ::= SEQUENCE {
        svID                SV-ID,
        signalsAvailable    GNSS-SignalIDs,
        channelNumber       INTEGER (-7..13)        OPTIONAL,       -- Cond FDMA
        ...
    }
    */
    VOS_UINT32                              bitOpGNSSIDGLONASSSatElementExt :1;
    VOS_UINT32                              bitOpChannelNumber              :1;
    VOS_UINT32                              bitOpSpare                      :30;

    LPP_MTA_COMMON_SV_ID_STRU               stSvId;
    LPP_MTA_COMMON_GNSS_SIGNAL_IDS_STRU     stSignalsAvailable;
    VOS_INT32                               lChannelNumber;
}LPP_MTA_GNSS_ID_GLONASS_SAT_ELEMENT_STRU;


typedef struct
{
    /*
    GNSS-ID-GLONASS ::= SEQUENCE (SIZE(1..64)) OF GNSS-ID-GLONASS-SatElement
    */
    VOS_UINT32                                  ulGNSSIdGlonassCnt;
    LPP_MTA_GNSS_ID_GLONASS_SAT_ELEMENT_STRU    astGNSSIdGlonassArray[LPP_MAX_GNSS_ID_GLONASS_SAT_ELEMENT_LEN];
}LPP_MTA_GNSS_ID_GLONASS_STRU;


typedef struct
{
    /*
    GNSS-ID-GPS-SatElement ::= SEQUENCE {
        svID                SV-ID,
        signalsAvailable    GNSS-SignalIDs,
        ...
    }
    */
    VOS_UINT32                              bitOpGNSSIDGPSSatElementExt :1;
    VOS_UINT32                              bitOpSpare                  :31;

    LPP_MTA_COMMON_SV_ID_STRU              stSvId;
    LPP_MTA_COMMON_GNSS_SIGNAL_IDS_STRU    stSignalAvailable;
}LPP_MTA_GNSS_ID_GPS_SAT_ELEMENT_STRU;


typedef struct
{
    /*
    GNSS-ID-GPS ::= SEQUENCE    (SIZE(1..64)) OF GNSS-ID-GPS-SatElement
    */
    VOS_UINT32                              ulGNSSIdGpsCnt;
    LPP_MTA_GNSS_ID_GPS_SAT_ELEMENT_STRU    astGNSSIdGpsArray[LPP_MAX_GNSS_ID_GPS_SAT_ELEMENT_LEN];
}LPP_MTA_GNSS_ID_GPS_STRU;


typedef struct
{
    /*
    GNSS-AuxiliaryInformation ::= CHOICE {
        gnss-ID-GPS     GNSS-ID-GPS,
        gnss-ID-GLONASS GNSS-ID-GLONASS,
        ...
    }
    */
    VOS_UINT32                  bitOpGNSSAuxInfoExt :1;
    VOS_UINT32                  bitOpSpare          :31;
    VOS_UINT32                  ulChoice;

    #define             LPP_GNSS_ID_GPS_CHOSEN            0
    #define             LPP_GNSS_ID_GLONASS_CHOSEN        1

    union
    {
        LPP_MTA_GNSS_ID_GPS_STRU                stGNSSIdGps;
        LPP_MTA_GNSS_ID_GLONASS_STRU            stGNSSIdGlonass;
    }u;
}LPP_MTA_GNSS_AUX_INFO_STRU;


typedef struct
{
    /*
    SBAS-IDs ::= SEQUENCE {
        sbas-IDs        BIT STRING {    waas        (0),
                                        egnos       (1),
                                        msas        (2),
                                        gagan       (3)  } (SIZE (1..8)),
        ...
    }
    */
    VOS_UINT32              bitOpSBASIDsExt :1;
    VOS_UINT32              bitOpSpare      :31;

    VOS_UINT8               ucSabsIdsLen;
    VOS_UINT8               ucSBASIDs;
    VOS_UINT8               ucRes[2];
}LPP_MTA_COMMON_SBAS_IDS_STRU;


typedef struct
{
    /*
    SBAS-ID ::= SEQUENCE {
        sbas-id             ENUMERATED { waas, egnos, msas, gagan, ...},
        ...
    }
    */
    VOS_UINT32                              bitOpSBASIDExt      :1;
    VOS_UINT32                              bitSpare            :31;

    LPP_SBAS_ID_ENUM_UINT8                  enLppSbasId;/*forconfirm*/
    VOS_UINT8                               aucRes[3];
}LPP_MTA_COMMON_SBAS_ID_STRU;
typedef struct
{
    /*
    GNSS-GenericAssistDataElement ::= SEQUENCE {
        gnss-ID                         GNSS-ID,
        sbas-ID                         SBAS-ID                         OPTIONAL, -- Cond GNSS-ID-SBAS
        gnss-TimeModels                 GNSS-TimeModelList              OPTIONAL,   -- Need ON
        gnss-DifferentialCorrections    GNSS-DifferentialCorrections    OPTIONAL,   -- Need ON
        gnss-NavigationModel            GNSS-NavigationModel            OPTIONAL,   -- Need ON
        gnss-RealTimeIntegrity          GNSS-RealTimeIntegrity          OPTIONAL,   -- Need ON
        gnss-DataBitAssistance          GNSS-DataBitAssistance          OPTIONAL,   -- Need ON
        gnss-AcquisitionAssistance      GNSS-AcquisitionAssistance      OPTIONAL,   -- Need ON
        gnss-Almanac                    GNSS-Almanac                    OPTIONAL,   -- Need ON
        gnss-UTC-Model                  GNSS-UTC-Model                  OPTIONAL,   -- Need ON
        gnss-AuxiliaryInformation       GNSS-AuxiliaryInformation       OPTIONAL,   -- Need ON
        ...
    }
    */
    VOS_UINT32                              bitOpGNSSGenericAssistDataElementExt:1;
    VOS_UINT32                              bitOpSbasId                         :1;
    VOS_UINT32                              bitOpGNSSTimeModelIs                :1;
    VOS_UINT32                              bitOpGNSSDiffCorrection             :1;
    VOS_UINT32                              bitOpGNSSNavigationModel            :1;
    VOS_UINT32                              bitOpGNSSRealTimeIntegrity          :1;
    VOS_UINT32                              bitOpGNSSDataBitAssit               :1;
    VOS_UINT32                              bitOpGNSSAcqAssit                   :1;
    VOS_UINT32                              bitOpGNSSAlmanac                    :1;
    VOS_UINT32                              bitOpGNSSUtcModel                   :1;
    VOS_UINT32                              bitOpGNSSAuxInfo                    :1;
    VOS_UINT32                              bitOpSpare                          :21;

    LPP_MTA_COMMON_GNSS_ID_STRU             stGNSSId;
    LPP_MTA_COMMON_SBAS_ID_STRU             stSbasId;
    LPP_MTA_GNSS_TIME_MODEL_LIST_STRU       stGNSSTimeModels;
    LPP_MTA_GNSS_DIFF_CORRECT_STRU          stGNSSDiffCorrect;
    LPP_MTA_GNSS_NAVIGATION_MODEL_STRU      stGNSSNavigationModel;
    LPP_MTA_GNSS_REALTIME_INTERGRITY_STRU   stGNSSRealTimeIntergrity;/*AT��û���ҵ���Ӧ�Ľӿ�*/
    LPP_MTA_GNSS_DATA_BIT_ASSIST_STRU       stGNSSDataBitAssistance;/*AT��û���ҵ���Ӧ�Ľӿ�*/
    LPP_MTA_GNSS_ACQUISIT_ASSIST_STRU       stGNSSAcquisitAssit;/*AT��û���ҵ���Ӧ�Ľӿ�*/
    LPP_MTA_GNSS_ALMANAC_STRU               stGNSSAlmanac;/*AT��û���ҵ���Ӧ�Ľӿ�*/
    LPP_MTA_GNSS_UTC_MODEL_STRU             stGNSSUtcModel;/*AT��û���ҵ���Ӧ�Ľӿ�*/
    LPP_MTA_GNSS_AUX_INFO_STRU              stGNSSAuxInfo;/*AT��û���ҵ���Ӧ�Ľӿ�*/
}LPP_MTA_GNSS_GENERIC_ASSIST_DATA_ELEMENT_STRU;


typedef struct
{
    /*
    GNSS-GenericAssistData ::= SEQUENCE (SIZE (1..16)) OF GNSS-GenericAssistDataElement
    */
    VOS_UINT32                                      ulGNSSGenericAssitDataCnt;
    LPP_MTA_GNSS_GENERIC_ASSIST_DATA_ELEMENT_STRU   astGNSSGenericAssistDataArray[LPP_MAX_GNSS_GENERIC_ASSIST_DATA_ELEMENT_LEN];
}LPP_MTA_GNSS_GENERIC_ASSIST_DATA_STRU;


typedef struct
{
    /*
    GPS-TOW-AssistElement ::= SEQUENCE {
        satelliteID     INTEGER (1..64),
        tlmWord         INTEGER (0..16383),
        antiSpoof       INTEGER (0..1),
        alert           INTEGER (0..1),
        tlmRsvdBits     INTEGER (0..3),
        ...
    }
    */
    VOS_UINT32          bitOpGPSTowAssistElementExt :1;
    VOS_UINT32          bitOpSpare                  :31;

    VOS_UINT8           ucSatalliteID;
    VOS_UINT8           ucRes;
    VOS_UINT16          usTlmWord;
    VOS_UINT8           ucAntiSpoof;
    VOS_UINT8           ucAlert;
    VOS_UINT8           ucTlmRsvdBits;/*forconfirm*/
    VOS_UINT8           ucRes1;
}LPP_MTA_GPS_TOW_ASSIST_ELEMENT_STRU;
typedef struct
{
    /*
    GPS-TOW-Assist ::= SEQUENCE (SIZE(1..64)) OF GPS-TOW-AssistElement
    */
    VOS_UINT32                                  ulGpsTowAssistCnt;
    LPP_MTA_GPS_TOW_ASSIST_ELEMENT_STRU         astGpsTowAssistArray[LPP_MAX_GPS_TOW_ASSIST_ELMENT_LEN];
}LPP_MTA_GPS_TOW_ASSIST_STRU;


typedef struct
{
    /*
    GNSS-SystemTime ::= SEQUENCE {
        gnss-TimeID                     GNSS-ID,
        gnss-DayNumber                  INTEGER (0..32767),
        gnss-TimeOfDay                  INTEGER (0..86399),
        gnss-TimeOfDayFrac-msec         INTEGER (0..999)        OPTIONAL,   -- Need ON
        notificationOfLeapSecond        BIT STRING (SIZE(2))    OPTIONAL,   -- Cond gnss-TimeID-glonass
        gps-TOW-Assist                  GPS-TOW-Assist          OPTIONAL,   -- Cond gnss-TimeID-gps
        ...
    }
    */
    VOS_UINT32                      bitOpGNSSSystemTimeExt      :1;
    VOS_UINT32                      bitOpGNSSTimeOfDayFracMsec  :1;
    VOS_UINT32                      bitOpGNSSNotifOfLeapSecond  :1;
    VOS_UINT32                      bitOpGNSSGpsTowAssit        :1;
    VOS_UINT32                      bitOpSpare                  :28;

    LPP_MTA_COMMON_GNSS_ID_STRU     stGNSSTimeID;
    VOS_UINT32                      ulGNSSDayNumber;
    VOS_UINT32                      ulGNSSTimeOfDay;
    VOS_UINT32                      ulGNSSTimeOfDayFracMsec;
    VOS_UINT8                       ucGNSSNotifOfLeapSecond;
    VOS_UINT8                       aucRes[3];
    LPP_MTA_GPS_TOW_ASSIST_STRU     stGpsTowAssist;
}LPP_MTA_GNSS_SYSTEM_TIME_STRU;


typedef struct
{
    /*
    GNSS-ReferenceTimeForOneCell  ::= SEQUENCE {
        networkTime                 NetworkTime,
        referenceTimeUnc            INTEGER (0..127),
        bsAlign                     ENUMERATED {true}   OPTIONAL,
        ...
    }
    */
    VOS_UINT32                      bitOpGNSSReferenceTimeForCellExt:1;
    VOS_UINT32                      bitOpBsAlign                    :1;
    VOS_UINT32                      bitOpSpare                      :30;

    LPP_MTA_NET_WORK_TIME_STRU      stNetWorkTime;/*lifuxin*/
    VOS_UINT8                       ucReferenceTimeUnc;
    VOS_UINT8                       aucRes[3];
    LPP_BSALIGN_ENUM_UINT32         enBsAlign;
}LPP_MTA_GNSS_REFERENCE_TIME_FOR_CELL_STRU;
typedef struct
{
    /*
    GNSS-ReferenceTime ::= SEQUENCE  {
        gnss-SystemTime             GNSS-SystemTime,
        referenceTimeUnc            INTEGER (0..127)                    OPTIONAL,   -- Cond noFTA
        gnss-ReferenceTimeForCells  SEQUENCE (SIZE (1..16)) OF
                                        GNSS-ReferenceTimeForOneCell    OPTIONAL,   -- Need ON
        ...
    }
    */
    VOS_UINT32                                  bitOpGNSSReferenceTimeExt:1;
    VOS_UINT32                                  bitOpGNSSRefTimeUnc      :1;
    VOS_UINT32                                  bitOpGNSSRefTimeForCell  :1;
    VOS_UINT32                                  bitOpSpare               :29;

    LPP_MTA_GNSS_SYSTEM_TIME_STRU               stGNSSSystemTime;
    VOS_UINT8                                   ucRefTimeUnc;
    VOS_UINT8                                   aucRes[3];
    VOS_UINT32                                  ulGNSSReferenceTimeForCellsCnt;
    LPP_MTA_GNSS_REFERENCE_TIME_FOR_CELL_STRU   astGNSSReferenceTimeForCells[LPP_MAX_GNSS_REF_TIME_FOR_CELLS_LEN];
}LPP_MTA_GNSS_REFERENCE_TIME_STRU;


typedef struct
{
    /*
    EllipsoidPointWithAltitudeAndUncertaintyEllipsoid ::= SEQUENCE {
        latitudeSign                ENUMERATED {north, south},
        degreesLatitude             INTEGER (0..8388607),           -- 23 bit field
        degreesLongitude            INTEGER (-8388608..8388607),    -- 24 bit field
        altitudeDirection           ENUMERATED {height, depth},
        altitude                    INTEGER (0..32767),             -- 15 bit field
        uncertaintySemiMajor        INTEGER (0..127),
        uncertaintySemiMinor        INTEGER (0..127),
        orientationMajorAxis        INTEGER (0..179),
        uncertaintyAltitude         INTEGER (0..127),
        confidence                  INTEGER (0..100)
    }
    */
    LPP_LATITUDE_SIGN_ENUM_UINT8    enLatitudeSign;
    VOS_UINT8                       aucRes[3];
    VOS_UINT32                      ulDegreeLatitude;
    VOS_INT32                       lDegreeeLongitude;
    LPP_LATITUDE_DIR_ENUM_UINT8     enAltitudeDirection;
    VOS_UINT16                      usAltitude;
    VOS_UINT8                       ucUncertaintySemiMajor;
    VOS_UINT8                       ucUncertaintySemiMinor;
    VOS_UINT8                       ucOrientationMajorAxis;
    VOS_UINT8                       ucUncertaintyAltitude;
    VOS_UINT8                       ucConfidence;
}LPP_MTA_ELLIP_POINT_WITH_ALTITUDE_UNCERTAIN_ELLIPSOID_STRU;


typedef struct
{
    /*
    GNSS-ReferenceLocation ::= SEQUENCE {
            threeDlocation          EllipsoidPointWithAltitudeAndUncertaintyEllipsoid,
            ...
    }
    */
    VOS_UINT32                                                      bitOpNGSSReferenceLocationExt:1;
    VOS_UINT32                                                      bitOpSpare                   :31;

    LPP_MTA_ELLIP_POINT_WITH_ALTITUDE_UNCERTAIN_ELLIPSOID_STRU      stThreeDlocation;
}LPP_MTA_GNSS_REFERENCE_LOCATION_STRU;


typedef struct
{
    /*
    KlobucharModelParameter ::= SEQUENCE {
        dataID          BIT STRING (SIZE (2)),
        alfa0           INTEGER (-128..127),
        alfa1           INTEGER (-128..127),
        alfa2           INTEGER (-128..127),
        alfa3           INTEGER (-128..127),
        beta0           INTEGER (-128..127),
        beta1           INTEGER (-128..127),
        beta2           INTEGER (-128..127),
        beta3           INTEGER (-128..127),
        ...
    }
    */
    VOS_UINT32              bitOpKlobucharModelParamterExt  :1;
    VOS_UINT32              bitOpSpare                      :31;

    VOS_UINT8               ucDataId;
    VOS_INT8                cAlfa0;
    VOS_INT8                cAlfa1;
    VOS_INT8                cAlfa2;
    VOS_INT8                cAlfa3;
    VOS_INT8                cbeta0;
    VOS_INT8                cbeta1;
    VOS_INT8                cbeta2;/*forconfirm*/
    VOS_INT8                cbeta3;
    VOS_INT8                acRev[3];
}LPP_MTA_KLOBUCHAR_MODEL_PARAMTER_STRU;
typedef struct
{
    /*
    NeQuickModelParameter ::= SEQUENCE {
        ai0             INTEGER (0..4095),
        ai1             INTEGER (0..4095),
        ai2             INTEGER (0..4095),
        ionoStormFlag1  INTEGER (0..1)      OPTIONAL,   -- Need OP
        ionoStormFlag2  INTEGER (0..1)      OPTIONAL,   -- Need OP
        ionoStormFlag3  INTEGER (0..1)      OPTIONAL,   -- Need OP
        ionoStormFlag4  INTEGER (0..1)      OPTIONAL,   -- Need OP
        ionoStormFlag5  INTEGER (0..1)      OPTIONAL,   -- Need OP
        ...
    }
    */
    VOS_UINT32                  bitOpNequickModelParameterExt   :1;
    VOS_UINT32                  bitOpIonoStormFlag1             :1;
    VOS_UINT32                  bitOpIonoStormFlag2             :1;
    VOS_UINT32                  bitOpIonoStormFlag3             :1;
    VOS_UINT32                  bitOpIonoStormFlag4             :1;
    VOS_UINT32                  bitOpIonoStormFlag5             :1;
    VOS_UINT32                  bitOpSpare                      :26;

    VOS_UINT16                  usAi0;
    VOS_UINT16                  usAi1;
    VOS_UINT16                  usAi2;
    VOS_UINT8                   ucInoStormFlag1;
    VOS_UINT8                   ucInoStormFlag2;
    VOS_UINT8                   ucInoStormFlag3;
    VOS_UINT8                   ucInoStormFlag4;
    VOS_UINT8                   ucInoStormFlag5;
    VOS_UINT8                   ucRes;
}LPP_MTA_NEQUICK_MODEL_PARAMETER_STRU;


typedef struct
{
    /*
    GNSS-IonosphericModel ::= SEQUENCE {
        klobucharModel          KlobucharModelParameter     OPTIONAL,   -- Need ON
        neQuickModel            NeQuickModelParameter       OPTIONAL,   -- Need ON
        ...
    }
    */
    VOS_UINT32                              bitOpGNSSIonosphericModelExt:1;
    VOS_UINT32                              bitOpklobucharModel         :1;
    VOS_UINT32                              bitOpneQuickModel           :1;
    VOS_UINT32                              bitOpSpare                  :29;

    LPP_MTA_KLOBUCHAR_MODEL_PARAMTER_STRU   stKlobucharModel;
    LPP_MTA_NEQUICK_MODEL_PARAMETER_STRU    stNeQuickModel;
}LPP_MTA_GNSS_IONOSPHERIC_MODEL_STRU;


typedef struct
{

    VOS_UINT32              bitOpGNSSEarthOrientationParameterExt   :1;
    VOS_UINT32              bitOpSpare                              :31;

    VOS_UINT32              ulTeop;
    VOS_INT32               lPmx;
    VOS_INT32               lPmXdot;
    VOS_INT32               lPmY;
    VOS_INT32               lPmYdot;
    VOS_INT32               lDeltaUt1;
    VOS_INT32               lDeltaUt1Dot;
}LPP_MTA_GNSS_EARTH_ORIENTATION_PARAMETERS_STRU;


typedef struct
{
    /*
    GNSS-CommonAssistData ::= SEQUENCE {
        gnss-ReferenceTime              GNSS-ReferenceTime                  OPTIONAL,   -- Need ON
        gnss-ReferenceLocation          GNSS-ReferenceLocation              OPTIONAL,   -- Need ON
        gnss-IonosphericModel           GNSS-IonosphericModel               OPTIONAL,   -- Need ON
        gnss-EarthOrientationParameters GNSS-EarthOrientationParameters     OPTIONAL,   -- Need ON
        ...
    }
    */
    VOS_UINT32                                      bitOpGNSSCommonAssistDataExt:1;
    VOS_UINT32                                      bitOpGNSSRefTime            :1;
    VOS_UINT32                                      bitOpGNSSRefLocation        :1;
    VOS_UINT32                                      bitOpGNSSIonoModel          :1;
    VOS_UINT32                                      bitOpGNSSEarthOriPara       :1;
    VOS_UINT32                                      bitOpSpare                  :27;

    LPP_MTA_GNSS_REFERENCE_TIME_STRU                stGNSSReferenceTime;
    LPP_MTA_GNSS_REFERENCE_LOCATION_STRU            stGNSSReferenceLocation;
    LPP_MTA_GNSS_IONOSPHERIC_MODEL_STRU             stIonosphericModel;
    LPP_MTA_GNSS_EARTH_ORIENTATION_PARAMETERS_STRU  stEarthOrientationParameters;
}LPP_MTA_GNSS_COMMON_ASSIST_DATA_STRU;


typedef struct
{
    /*
    A-GNSS-ProvideAssistanceData ::= SEQUENCE {
        gnss-CommonAssistData           GNSS-CommonAssistData               OPTIONAL,   -- Need ON
        gnss-GenericAssistData          GNSS-GenericAssistData              OPTIONAL,   -- Need ON
        gnss-Error                      A-GNSS-Error                        OPTIONAL,   -- Need ON
        ...
    }
    */
    VOS_UINT32                                  bitOpAGnssProvideAssistDataExt  :1;
    VOS_UINT32                                  bitOpGNSSCommonAssitData        :1;
    VOS_UINT32                                  bitOpGNSSGenericAssitData       :1;
    VOS_UINT32                                  bitOpGNSSError                  :1;
    VOS_UINT32                                  bitOpSpare                      :28;

    LPP_MTA_GNSS_COMMON_ASSIST_DATA_STRU        stGNSSCommonAssistData;
    LPP_MTA_GNSS_GENERIC_ASSIST_DATA_STRU       stGNSSGenericAssitData;
    LPP_MTA_COMMON_GNSS_ERROR_STRU              stGNSSError;
}LPP_MTA_AGNSS_PROVIDE_ASSIST_DATA_STRU;


typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    VOS_UINT32                                  ulMsgId;        /*_H2ASN_Skip*/ /* ��Ϣͷ */

    VOS_UINT32                                  ulSessionId;    /*��ǰsessionID*/
    LPP_MTA_AGNSS_PROVIDE_ASSIST_DATA_STRU      stGnssProvideAssistData;
}LPP_MTA_GNSS_PROVIDE_ASSIST_DATA_CNF_STRU; /*27.007 8.55-15*/



typedef struct
{
    /*
    GNSS-TimeModelElementReq ::= SEQUENCE {
        gnss-TO-IDsReq  INTEGER (1..15),
        deltaTreq       BOOLEAN,
        ...
    }
    */
    VOS_UINT32          bitOpGNSSTimeModelElementReqExt :1;
    VOS_UINT32          bitOpSpare                      :31;

    VOS_UINT8           ucGNSSToIdsReq;
    VOS_UINT8           aucRes[3];
    VOS_BOOL            bdeltaTreq;
}MTA_LPP_GNSS_TIME_MODEL_ELEMENT_REQ_STRU;


typedef struct
{
    /*
    GNSS-TimeModelListReq ::= SEQUENCE (SIZE(1..15)) OF GNSS-TimeModelElementReq

    */
    VOS_UINT32                                  ulGNSSTimeModelListReqCnt;
    MTA_LPP_GNSS_TIME_MODEL_ELEMENT_REQ_STRU    astGNSSTimeModelListElementReq[LPP_MAX_GNSS_TIME_MODEL_ELEMENT_LEN];
}MTA_LPP_GNSS_TIME_MODEL_LIST_REQ_STRU;


typedef struct
{
    /*
    GNSS-DifferentialCorrectionsReq ::=     SEQUENCE {
        dgnss-SignalsReq            GNSS-SignalIDs,
        dgnss-ValidityTimeReq       BOOLEAN,
        ...
    }
    */
    VOS_UINT32                              bitOpGNSSDiffCorrectReqExt  :1;
    VOS_UINT32                              bitOpSpare                  :31;

    LPP_MTA_COMMON_GNSS_SIGNAL_IDS_STRU     stDGNSSSignalReq;
    VOS_BOOL                                bDGNSSValidityTimeReq;
}MTA_LPP_GNSS_DIFF_CORRECT_REQ_STRU;


typedef struct
{
    /*
    SatListRelatedDataElement ::= SEQUENCE {
        svID                SV-ID,
        iod                 BIT STRING (SIZE(11)),
        clockModelID        INTEGER (1..8)          OPTIONAL,
        orbitModelID        INTEGER (1..8)          OPTIONAL,
        ...
    }
    */
    VOS_UINT32                  bitOpSatListRelatedDataElementExt   :1;
    VOS_UINT32                  bitOpClockModelId                   :1;
    VOS_UINT32                  bitOpOrbitModelId                   :1;
    VOS_UINT32                  bitOpSpare                          :29;

    LPP_MTA_COMMON_SV_ID_STRU   stSvId;
    VOS_UINT16                  usIod;
    VOS_UINT8                   ucClockModelId;
    VOS_UINT8                   ucOrbitModelId;
}MTA_LPP_SATLIST_RELATED_DATALIST_ELEMENT_STRU;


typedef struct
{
    /*SatListRelatedDataList ::= SEQUENCE (SIZE (1..64)) OF SatListRelatedDataElement*/
    VOS_UINT32                                      ulSatListRelatedDataListCnt;
    MTA_LPP_SATLIST_RELATED_DATALIST_ELEMENT_STRU   astSatListRelatedDataListElementArray[LPP_MAX_SAT_LIST_RELATED_DATA_ELEMENT_LEN];
}MTA_LPP_SATLIST_RELATED_DATALIST_STRU;
typedef struct
{
    /*
    StoredNavListInfo ::= SEQUENCE {
        gnss-WeekOrDay          INTEGER (0..4095),
        gnss-Toe                INTEGER (0..255),
        t-toeLimit              INTEGER (0..15),
        satListRelatedDataList  SatListRelatedDataList  OPTIONAL,
        ...
    }
    */
    VOS_UINT32                              bitOpStoredNavListInfoExt   :1;
    VOS_UINT32                              bitOpSatListREalatedDataList:1;
    VOS_UINT32                              bitOpSpare                  :30;

    VOS_UINT16                              usGNSSWeekOrDay;
    VOS_UINT8                               ucGNSSToe;
    VOS_UINT8                               ucGNSSTToeLimit;
    MTA_LPP_SATLIST_RELATED_DATALIST_STRU   stSatlistRelatedDataList;
}MTA_LPP_STORED_NAVLIST_STRU;


typedef struct
{
    /*clockModelID-PrefList   SEQUENCE (SIZE (1..8)) OF   INTEGER (1..8)*/
    VOS_UINT8       ucClockModelIDCount;
    VOS_UINT8       ucRes[3];
    VOS_UINT8       ucClockModelIDList[LPP_MAX_CLOCK_MODEL_ID_PRELIST_LEN];
}LPP_MTA_COMMON_CLOCK_MODEL_ID_STRU;
typedef struct
{
    /*orbitModelID-PrefList   SEQUENCE (SIZE (1..8)) OF   INTEGER (1..8)*/
    VOS_UINT8       ucOrbitModelIDCount;
    VOS_UINT8       ucRes[3];
    VOS_UINT8       ucOrbitModelIDList[LPP_MAX_ORBIT_MODEL_ID_PREFLIST_LEN];
}LPP_MTA_COMMON_ORBIT_MODEL_ID_STRU;
typedef struct
{
    /*
    ReqNavListInfo ::=  SEQUENCE {
        svReqList               BIT STRING (SIZE (64)),
        clockModelID-PrefList   SEQUENCE (SIZE (1..8)) OF   INTEGER (1..8)      OPTIONAL,
        orbitModelID-PrefList   SEQUENCE (SIZE (1..8)) OF   INTEGER (1..8)      OPTIONAL,
        addNavparamReq          BOOLEAN             OPTIONAL,   -- Cond orbitModelID-2
        ...
    }
    */
    VOS_UINT32                              bitOpReqNavListInfoExt      :1;
    VOS_UINT32                              bitOpClockModelIDPrefList   :1;
    VOS_UINT32                              bitOpOrbitModelIDPrefList   :1;
    VOS_UINT32                              bitOpAddNavparamReq         :1;
    VOS_UINT32                              bitOpSpare                  :28;

    VOS_UINT8                               aucSvReqList[LPP_SV_REQ_LIST_LEN];
    LPP_MTA_COMMON_CLOCK_MODEL_ID_STRU      stClockModelID;
    LPP_MTA_COMMON_ORBIT_MODEL_ID_STRU      stOrbitModelID;
    VOS_BOOL                                bAddNavparamReq;
}MTA_LPP_REQ_NAVLIST_STRU;


typedef struct
{
    /*
    GNSS-NavigationModelReq ::=     CHOICE {
        storedNavList       StoredNavListInfo,
        reqNavList          ReqNavListInfo,
        ...
    }
    */
    VOS_UINT32              bitOpGNSSNavigationModelReqExt  :1;
    VOS_UINT32              bitOpSpare                      :31;
    VOS_UINT32              ulChoice;

    #define     LPP_STORED_NAVLIST_CHOSEN            0
    #define     LPP_REQ_NAVLIST_CHOSEN               1

    union
    {
        MTA_LPP_STORED_NAVLIST_STRU             stStoredNavList;
        MTA_LPP_REQ_NAVLIST_STRU                stReqNavList;
    }u;
}MTA_LPP_GNSS_NAVIGATION_MODEL_REQ_STRU;


typedef struct
{
    /*Э��Ϊ��*/
    VOS_UINT32      bitOpGNSSRealtimeIntergrityReqExt   :1;
    VOS_UINT32      bitOpSpare                          :31;
}MTA_LPP_GNSS_REALTIME_INTERGRITY_REQ_STRU;
typedef struct
{
    /*
    GNSS-DataBitsReqSatElement ::= SEQUENCE {
        svID                SV-ID,
        ...
    }
    */
    VOS_UINT32				    bitOpGNSSDataBitReqSatElementFExt   :1;
    VOS_UINT32				    bitOpSpare                          :31;

    LPP_MTA_COMMON_SV_ID_STRU   stSvId;
}MTA_LPP_GNSS_DATA_BIT_REQ_SAT_ELEMENT_STRU;


typedef struct
{
/*
GNSS-DataBitsReqSatList ::= SEQUENCE (SIZE(1..64)) OF GNSS-DataBitsReqSatElement
*/
    VOS_UINT32									ulGNSSDataBitsReqListCnt;
    MTA_LPP_GNSS_DATA_BIT_REQ_SAT_ELEMENT_STRU  astGNSSDataBitReqSatList[LPP_MAX_GNSS_DATA_BITS_REQ_SAT_LIST_LEN];
}MTA_LPP_GNSS_DATA_BIT_REQ_SAT_LIST_STRU;


typedef struct
{
    /*
    GNSS-DataBitAssistanceReq ::=   SEQUENCE {
        gnss-TOD-Req        INTEGER (0..3599),
        gnss-TOD-FracReq    INTEGER (0..999)        OPTIONAL,
        dataBitInterval     INTEGER (0..15),
        gnss-SignalType     GNSS-SignalIDs,
        gnss-DataBitsReq    GNSS-DataBitsReqSatList OPTIONAL,
        ...
    }
    */
    VOS_UINT32                              bitOpGNSSDataBitAssistReqExt    :1;
    VOS_UINT32                              bitOpGNSSTodFracREq             :1;
    VOS_UINT32                              bitOpGNSSDataBitsReq            :1;
    VOS_UINT32                              bitOpSpare                      :29;

    VOS_UINT32                              ulGNSSTodReq;
    VOS_UINT16                              usGNSSTodFracReq;
    VOS_UINT16                              usDataBitInterval;
    LPP_MTA_COMMON_GNSS_SIGNAL_IDS_STRU     stGNSSSignalType;
    MTA_LPP_GNSS_DATA_BIT_REQ_SAT_LIST_STRU stGNSSDataBitsReqSatList;
}MTA_LPP_GNSS_DATA_BIT_ASSIST_REQ_STRU;


typedef struct
{
    /*
    GNSS-AcquisitionAssistanceReq ::=   SEQUENCE {
        gnss-SignalID-Req       GNSS-SignalID,
        ...
    }
    */
    VOS_UINT32                          bitOpGNSSAcquisitAssistReqExt   :1;
    VOS_UINT32                          bitOpSpare                      :31;

    LPP_MTA_COMMON_GNSS_SIGNAL_ID_STRU  stGNSSSignalIdReq;
}MTA_LPP_GNSS_ACQUISIT_ASSIST_REQ_STRU;


typedef struct
{
    /*
    GNSS-AlmanacReq ::= SEQUENCE {
        modelID             INTEGER(1..8)   OPTIONAL,
        ...
    }
    */
    VOS_UINT32          bitOpGNSSAlmanacReqExt  :1;
    VOS_UINT32          bitOpModelId            :1;
    VOS_UINT32          bitOpSpare              :30;

    VOS_UINT8           ucModelId;
    VOS_UINT8           aucRes[3];
}MTA_LPP_GNSS_ALMANAC_REQ_STRU;


typedef struct
{
    /*
    GNSS-UTC-ModelReq ::=   SEQUENCE {
        modelID             INTEGER(1..8)   OPTIONAL,
        ...
    }
    */
    VOS_UINT32          bitOpGNSSUTCModelReqExt :1;
    VOS_UINT32          bitOpModelId            :1;
    VOS_UINT32          bitOpSpare              :30;

    VOS_UINT8           ucModelId;
    VOS_UINT8           aucRes[3];
}MTA_LPP_GNSS_UTC_MODEL_REQ_STRU;


typedef struct
{
    /*
    Э��Ϊ��
    */
    VOS_UINT32      bitOpGNSSAuxInfoReqExt  :1;
    VOS_UINT32      bitOpSpare              :31;
}MTA_LPP_GNSS_AUX_INFO_REQ_STRU;


typedef struct
{
    /*
    GNSS-GenericAssistDataReqElement ::= SEQUENCE {
        gnss-ID                         GNSS-ID,
        sbas-ID                         SBAS-ID                         OPTIONAL, -- Cond GNSS-ID-SBAS
        gnss-TimeModelsReq              GNSS-TimeModelListReq           OPTIONAL, -- Cond TimeModReq
        gnss-DifferentialCorrectionsReq GNSS-DifferentialCorrectionsReq OPTIONAL, -- Cond DGNSS-Req
        gnss-NavigationModelReq         GNSS-NavigationModelReq         OPTIONAL, -- Cond NavModReq
        gnss-RealTimeIntegrityReq       GNSS-RealTimeIntegrityReq       OPTIONAL, -- Cond RTIReq
        gnss-DataBitAssistanceReq       GNSS-DataBitAssistanceReq       OPTIONAL, -- Cond DataBitsReq
        gnss-AcquisitionAssistanceReq   GNSS-AcquisitionAssistanceReq   OPTIONAL, -- Cond AcquAssistReq
        gnss-AlmanacReq                 GNSS-AlmanacReq                 OPTIONAL, -- Cond AlmanacReq
        gnss-UTCModelReq                GNSS-UTC-ModelReq               OPTIONAL, -- Cond UTCModReq
        gnss-AuxiliaryInformationReq    GNSS-AuxiliaryInformationReq    OPTIONAL, -- Cond AuxInfoReq
        ...
    }
    */
    VOS_UINT32                                  bitOpGNSSGenericAssistDataReqExt:1;
    VOS_UINT32                                  bitOpSbasId                     :1;
    VOS_UINT32                                  bitOpGNSSTimeModelIsReq         :1;
    VOS_UINT32                                  bitOpGNSSDiffCorrectionReq      :1;
    VOS_UINT32                                  bitOpGNSSNavigationModelReq     :1;
    VOS_UINT32                                  bitOpGNSSRealTimeIntegrityReq   :1;
    VOS_UINT32                                  bitOpGNSSDataBitAssitReq        :1;
    VOS_UINT32                                  bitOpGNSSAcqAssitReq            :1;
    VOS_UINT32                                  bitOpGNSSAlmanacReq             :1;
    VOS_UINT32                                  bitOpGNSSUtcModelReq            :1;
    VOS_UINT32                                  bitOpGNSSAuxInfoReq             :1;
    VOS_UINT32                                  bitOpSpare                      :21;

    LPP_MTA_COMMON_GNSS_ID_STRU                 stGNSSId;
    LPP_MTA_COMMON_SBAS_ID_STRU                 stSbasId;
    MTA_LPP_GNSS_TIME_MODEL_LIST_REQ_STRU       stGNSSTimeModelsReq;/*empty*/
    MTA_LPP_GNSS_DIFF_CORRECT_REQ_STRU          stGNSSDiffCorrectReq;/*AT�ֲ���û���ҵ�*/
    MTA_LPP_GNSS_NAVIGATION_MODEL_REQ_STRU      stGNSSNavigationModelReq;
    MTA_LPP_GNSS_REALTIME_INTERGRITY_REQ_STRU   stGNSSRealTimeIntergrityReq;/*AT�ֲ���û���ҵ�*/
    MTA_LPP_GNSS_DATA_BIT_ASSIST_REQ_STRU       stGNSSDataBitAssistanceReq;/*AT�ֲ���û���ҵ�*/
    MTA_LPP_GNSS_ACQUISIT_ASSIST_REQ_STRU       stGNSSAcquisitAssitReq;/*empty*/
    MTA_LPP_GNSS_ALMANAC_REQ_STRU               stGNSSAlmanacReq;/*AT�ֲ���û���ҵ�*/
    MTA_LPP_GNSS_UTC_MODEL_REQ_STRU             stGNSSUtcModelReq;/*AT�ֲ���û���ҵ�*/
    MTA_LPP_GNSS_AUX_INFO_REQ_STRU              stGNSSAuxInfoReq;/*AT�ֲ���û���ҵ�*/
}MTA_LPP_GNSS_GENERIC_ASSIST_DATA_REQ_ELEMENT_STRU;


typedef struct
{
    /*
    GNSS-GenericAssistDataReq ::= SEQUENCE (SIZE (1..16)) OF GNSS-GenericAssistDataReqElement
    */
    VOS_UINT32                                              ulGNSSGenericAssistDataReqCnt;
    MTA_LPP_GNSS_GENERIC_ASSIST_DATA_REQ_ELEMENT_STRU       astGNSSGenericAssistDataReqElement[LPP_MAX_GEN_ASSIT_DATA_ELEMENT_LEN];
}MTA_LPP_GNSS_GENERIC_ASSIST_DATA_REQ_STRU;


typedef struct
{
    /*
    GNSS-ReferenceTimeReq ::= SEQUENCE {
        gnss-TimeReqPrefList    SEQUENCE (SIZE (1..8)) OF GNSS-ID,
        gps-TOW-assistReq       BOOLEAN                             OPTIONAL, -- Cond gps
        notOfLeapSecReq         BOOLEAN                             OPTIONAL, -- Cond glonass
        ...
    }
    */
    VOS_UINT32                      bitOpGNSSReferenceTimeReqExt    :1;
    VOS_UINT32                      bitOpGpsTowAssistReq            :1;
    VOS_UINT32                      bitOpNotOfLeapSecReq            :1;
    VOS_UINT32                      bitOpSpare                      :29;

    VOS_UINT32                      ulGNSSTimeReqPrefListCnt;
    LPP_MTA_COMMON_GNSS_ID_STRU     astGNSSTimeReqPrefListArray[8];
    VOS_BOOL                        bGpsTowAssistReq;
    VOS_BOOL                        bNotOFLeapSecReq;
}MTA_LPP_GNSS_REFERENCE_TIME_REQ_STRU;


typedef struct
{
    /*
    Э��Ϊ��
    */
    VOS_UINT32          bitOpGNSSReferenceLocationReqExt:1;
    VOS_UINT32          bitOpSpare:31;
}MTA_LPP_GNSS_REFERENCE_LOCATION_REQ_STRU;


typedef struct
{
    /*
    GNSS-IonosphericModelReq ::=    SEQUENCE {
        klobucharModelReq       BIT STRING (SIZE(2))    OPTIONAL,   -- Cond klobuchar
        neQuickModelReq         NULL                    OPTIONAL,   -- Cond nequick
        ...
    }
    */
    VOS_UINT32                  bitOpGNSSIonosphericModelReqExt :1;
    VOS_UINT32                  bitOpKlobucharModelReq          :1;
    VOS_UINT32                  bitOpNeQuickModelReq            :1;
    VOS_UINT32                  bitOpSpare                      :29;

    VOS_UINT8                   ucKlobucharModelReq;
    VOS_UINT8                   aucRes[3];
    VOS_UINT32                  ulQuickModelReq;
}MTA_LPP_GNSS_IONOSPHERIC_MODEL_REQ_STRU;


typedef struct
{
    /*
    Э��Ϊ��
    */
    VOS_UINT32          ulRes;
}MTA_LPP_GNSS_EARTH_ORIENTATION_PARAMETERS_REQ_STRU;


typedef struct
{
    /*
    GNSS-CommonAssistDataReq ::= SEQUENCE {
        gnss-ReferenceTimeReq               GNSS-ReferenceTimeReq
                                                                    OPTIONAL, -- Cond RefTimeReq
        gnss-ReferenceLocationReq           GNSS-ReferenceLocationReq
                                                                    OPTIONAL, -- Cond RefLocReq
        gnss-IonosphericModelReq            GNSS-IonosphericModelReq
                                                                    OPTIONAL, -- Cond IonoModReq
        gnss-EarthOrientationParametersReq  GNSS-EarthOrientationParametersReq
                                                                    OPTIONAL, -- Cond EOPReq
        ...
    }
    */
    VOS_UINT32                                          bitOpGNSSCommonAssistDataReqExt :1;
    VOS_UINT32                                          bitOpGNSSRefTimeReq             :1;
    VOS_UINT32                                          bitOpGNSSRefLocationReq         :1;
    VOS_UINT32                                          bitOpGNSSIonoModelReq           :1;
    VOS_UINT32                                          bitOpGNSSEarthOriParaReq        :1;
    VOS_UINT32                                          bitOpSpare                      :27;

    MTA_LPP_GNSS_REFERENCE_TIME_REQ_STRU                stGNSSReferenceTimeReq; /*empty*/
    MTA_LPP_GNSS_REFERENCE_LOCATION_REQ_STRU            stGNSSReferenceLocationReq;/*empty*/
    MTA_LPP_GNSS_IONOSPHERIC_MODEL_REQ_STRU             stIonosphericModelReq;/*empty*/
    MTA_LPP_GNSS_EARTH_ORIENTATION_PARAMETERS_REQ_STRU  stEarthOrientationParametersReq;/*empty*/
}MTA_LPP_GNSS_COMMON_ASSIST_DATA_REQ_STRU;


typedef struct
{
    /*
    A-GNSS-RequestAssistanceData ::= SEQUENCE {
        gnss-CommonAssistDataReq        GNSS-CommonAssistDataReq        OPTIONAL, -- Cond CommonADReq
        gnss-GenericAssistDataReq       GNSS-GenericAssistDataReq       OPTIONAL, -- Cond GenADReq
        ...
    }
    */
    VOS_UINT32                                  bitOpAGNSSReqAssistDataExt  :1;
    VOS_UINT32                                  bitOpGNSSCommAssistData     :1;
    VOS_UINT32                                  bitOpGNSSGenericAssistData  :1;
    VOS_UINT32                                  bitOpSpare                  :29;

    MTA_LPP_GNSS_COMMON_ASSIST_DATA_REQ_STRU    stGNSSCommonAssistDataReq;
    MTA_LPP_GNSS_GENERIC_ASSIST_DATA_REQ_STRU   stGNSSGenericAssistDataReq;
}MTA_LPP_AGNSS_REQ_ASSIST_DATA_STRU;


typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                              ulMsgId;        /*_H2ASN_Skip*/ /* ��Ϣͷ */

    VOS_UINT32                              ulSessionId;    /*��ǰsessionID*/
    MTA_LPP_AGNSS_REQ_ASSIST_DATA_STRU      stGnssAssistDataReq;
}MTA_LPP_GNSS_ASSIST_DATA_REQ_STRU;/*27.007 8.55-15*/


typedef struct
{
    /*
    AccessTypes ::= SEQUENCE {
        accessTypes     BIT STRING {    eutra       (0),
                                        utra        (1),
                                        gsm         (2)  } (SIZE (1..8)),
        ...
    }
    */

    VOS_UINT32                              bitOpAccessTypesExt :1;
    VOS_UINT32                              bitSpare            :31;

    VOS_UINT8                               ucAccessTypesCnt;
    VOS_UINT8                               ucAccessTypes;
    VOS_UINT8                               aucRsv[2];
}LPP_MTA_COMMON_ACCESS_TYPES_STRU;


typedef struct
{
    /*
    PositioningModes ::= SEQUENCE {
        posModes        BIT STRING {    standalone  (0),
                                        ue-based    (1),
                                        ue-assisted (2)  } (SIZE (1..8)),
        ...
    }
    */
    VOS_UINT32              bitOpPosModeExt:1;
    VOS_UINT32              bitOpSpare:31;

    VOS_UINT8               ucPosModeLen;
    VOS_UINT8               ucPositioningModes;
    VOS_UINT8               ucRes[2];
}LPP_MTA_COMMON_POSITIONING_MODES_STRU;


typedef struct
{
    /*
    fta-MeasSupport                 SEQUENCE {
                                        cellTime    AccessTypes,
                                        mode        PositioningModes,
                                        ...
                                    }
    */
    VOS_UINT32                              bitOpFtaSupportExt  :1;
    VOS_UINT32                              bitOpSpare          :31;

    LPP_MTA_COMMON_ACCESS_TYPES_STRU        stAccessTypes;
    LPP_MTA_COMMON_POSITIONING_MODES_STRU   stPositioningModes;
}MTA_LPP_FTA_MEAS_SUPPORT_STRU;


typedef struct
{
    /*
    GNSS-SupportElement ::= SEQUENCE {
        gnss-ID                         GNSS-ID,
        sbas-IDs                        SBAS-IDs                    OPTIONAL,   -- Cond GNSS-ID-SBAS
        agnss-Modes                     PositioningModes,
        gnss-Signals                    GNSS-SignalIDs,
        fta-MeasSupport                 SEQUENCE {
                                            cellTime    AccessTypes,
                                            mode        PositioningModes,
                                            ...
                                        }                           OPTIONAL,   -- Cond fta
        adr-Support                     BOOLEAN,
        velocityMeasurementSupport      BOOLEAN,
        ...
    }
    */
    VOS_UINT32                              bitOpGNSSSupportElementExt:1;
    VOS_UINT32                              bitOpSbasIds        : 1;
    VOS_UINT32                              bitOpFtaMeasSupport : 1;
    VOS_UINT32                              bitOpSpare          : 29;

    LPP_MTA_COMMON_GNSS_ID_STRU             stGnssId;
    LPP_MTA_COMMON_SBAS_IDS_STRU            stSbasIds;
    LPP_MTA_COMMON_POSITIONING_MODES_STRU   stAgnssModes;
    LPP_MTA_COMMON_GNSS_SIGNAL_IDS_STRU     stGnssSignals;
    MTA_LPP_FTA_MEAS_SUPPORT_STRU           stFtaMeasSupport;
    VOS_BOOL                                bSdrSupport;
    VOS_BOOL                                bVelocityMeasurementSupport;
}MTA_LPP_GNSS_SUPPORT_ELEMENT_STRU;


typedef struct
{
    /*
    GNSS-SupportList ::= SEQUENCE (SIZE(1..16)) OF GNSS-SupportElement
    */
    VOS_UINT32                                  ulSupportElementNum;                /* ȡֵ[1,16] */
    MTA_LPP_GNSS_SUPPORT_ELEMENT_STRU           astGnssSupportElementArray[LPP_MAX_GNSS_SUPPORT_ELEMENT_NUM];
}MTA_LPP_GNSS_SUPPORT_LIST_STRU;
typedef struct
{
    /*
    GNSS-ReferenceTimeSupport ::=   SEQUENCE {
        gnss-SystemTime     GNSS-ID-Bitmap,
        fta-Support         AccessTypes                                     OPTIONAL, -- Cond fta
        ...
    }
    */
    VOS_UINT32                              bitOpGNSSReferenceTimeSupportExt:1;
    VOS_UINT32                              bitOpFtaSupport                 :1;
    VOS_UINT32                              bitOpSpare                      :30;

    LPP_MTA_COMMON_GNSS_ID_BITMAP_STRU      stGnssSystemTime;
    LPP_MTA_COMMON_ACCESS_TYPES_STRU        stFtaSupport;
}MTA_LPP_GNSS_REFERENCE_TIME_SUPPORT_STRU;


typedef struct
{
    /* Э����˽ṹΪ�� */
    VOS_UINT32          bitOpGNSSRefLocationSupExt  :1;
    VOS_UINT32          bitOpSpare                  :31;
}MTA_LPP_GNSS_REFERENCE_LOCATION_SUPPORT_STRU;
typedef struct
{
    /*
    GNSS-IonosphericModelSupport ::=    SEQUENCE {
        ionoModel       BIT STRING {    klobuchar   (0),
                                        neQuick     (1) } (SIZE (1..8)),
        ...
    }
    */

    VOS_UINT32      bitOpGNSSIonosphericModeSupExt  :1;
    VOS_UINT32      bitOpSpare                      :31;

    VOS_UINT8       ucIonoModel;
    VOS_UINT8       ucIonoModelLen;
    VOS_UINT8       ucRes[2];
}MTA_LPP_GNSS_IONOSPHERIC_MODE_SUPPORT_STRU;


typedef struct
{
    /* Э����˽ṹΪ�� */
    VOS_UINT32      bitOGNSSEarthOrientationParametersSupExt:1;
    VOS_UINT32      bitOpSpare:31;
}MTA_LPP_GNSS_EARTH_ORIENTATION_PARAMETERS_SUPPORT_STRU;
typedef struct
{
    /*
    GNSS-CommonAssistanceDataSupport ::= SEQUENCE {
        gnss-ReferenceTimeSupport               GNSS-ReferenceTimeSupport
                                                                    OPTIONAL, -- Cond RefTimeSup
        gnss-ReferenceLocationSupport           GNSS-ReferenceLocationSupport
                                                                    OPTIONAL, -- Cond RefLocSup
        gnss-IonosphericModelSupport            GNSS-IonosphericModelSupport
                                                                    OPTIONAL, -- Cond IonoModSup
        gnss-EarthOrientationParametersSupport  GNSS-EarthOrientationParametersSupport
                                                                    OPTIONAL, -- Cond EOPSup
        ...
    }
    */
    VOS_UINT32                                              bitOpGNSSCommonAssistDataSupportExt         :1;
    VOS_UINT32                                              bitOpGnssReferenceTimeSupport               :1;
    VOS_UINT32                                              bitOpGnssReferenceLocationSupport           :1;
    VOS_UINT32                                              bitOpGnssIonosphericModelSupport            :1;
    VOS_UINT32                                              bitOpGnssEarthOrientationParametersSupport  :1;
    VOS_UINT32                                              bitOpSpare                                  :27;

    MTA_LPP_GNSS_REFERENCE_TIME_SUPPORT_STRU                stGnssReferenceTimeSupport; /*empty*/
    MTA_LPP_GNSS_REFERENCE_LOCATION_SUPPORT_STRU            stGnssReferenceLocationSupport; /*empty*/
    MTA_LPP_GNSS_IONOSPHERIC_MODE_SUPPORT_STRU              stGnssIonosphericModelSupport; /*empty*/
    MTA_LPP_GNSS_EARTH_ORIENTATION_PARAMETERS_SUPPORT_STRU  stGnssEarthOrientationParametersSupport; /*empty*/
}MTA_LPP_GNSS_COMMON_ASSISTANCE_DATA_SUPPORT_STRU;


typedef struct
{
    /* Э����˽ṹΪ�� */
    VOS_UINT32      bitOGNSSTimeModeListSupExt:1;
    VOS_UINT32      bitOpSpare:31;
}MTA_LPP_GNSS_TIME_MODE_LIST_SUPPORT_STRU;
typedef struct
{
    /*
    GNSS-DifferentialCorrectionsSupport ::=     SEQUENCE {
        gnssSignalIDs           GNSS-SignalIDs,
        dgnss-ValidityTimeSup   BOOLEAN,
        ...
    }
    */
    VOS_UINT32                              bitOpGNSSDiffCorrectSupExt  :1;
    VOS_UINT32                              bitOpSpare                  :31;

    LPP_MTA_COMMON_GNSS_SIGNAL_IDS_STRU     stGnssSignalIDs;
    VOS_BOOL                                bDgnssValidityTimeSup;
}MTA_LPP_GNSS_DIFFERENTIAL_CORRECTIONS_SUPPORT_STRU;


typedef struct
{
    VOS_UINT8                           ucClockModelCnt;
    VOS_UINT8                           ucClockModel;
    VOS_UINT8                           ucRes[2];
}MTA_LPP_CLOCK_MODEL_STRU;


typedef struct
{
    VOS_UINT8                           ucOrbitModelCnt;
    VOS_UINT8                           ucOrbitModel;
    VOS_UINT8                           ucRes[2];
}MTA_LPP_ORBIT_MODEL_STRU;


typedef struct
{
    /*
    GNSS-NavigationModelSupport ::= SEQUENCE {
        clockModel      BIT STRING {    model-1     (0),
                                        model-2     (1),
                                        model-3     (2),
                                        model-4     (3),
                                        model-5     (4) } (SIZE (1..8))     OPTIONAL,
        orbitModel      BIT STRING {    model-1     (0),
                                        model-2     (1),
                                        model-3     (2),
                                        model-4     (3),
                                        model-5     (4) } (SIZE (1..8))     OPTIONAL,
        ...
    }
    */
    VOS_UINT32                          bitOpGNSSNavigationModeSupExt:1;
    VOS_UINT32                          bitOpClockModel : 1;
    VOS_UINT32                          bitOpOrbitModel : 1;
    VOS_UINT32                          bitOpSpare      : 29;

    MTA_LPP_CLOCK_MODEL_STRU            stClockModel;
    MTA_LPP_ORBIT_MODEL_STRU            stOrbitModel;
}MTA_LPP_GNSS_NAVIGATION_MODE_SUPPORT_STRU;


typedef struct
{
    /* Э����˽ṹΪ�� */
    VOS_UINT32      bitOpGNSSRealTimeIntSupExt:1;
    VOS_UINT32      bitOpSpare:31;
}MTA_LPP_GNSS_REAL_TIME_INTEGRITY_SUPPORT_STRU;
typedef struct
{
    /* Э����˽ṹΪ�� */
    VOS_UINT32          bitOpGNSSDataBitAssistSupExt:1;
    VOS_UINT32          bitOpSpare:31;
}MTA_LPP_GNSS_DATA_BIT_ASSISTANCE_SUPPORT_STRU;
typedef struct
{
    /*
    GNSS-AcquisitionAssistanceSupport ::=   SEQUENCE {
        ...,
        confidenceSupport-r10                   ENUMERATED { true }     OPTIONAL,
        dopplerUncertaintyExtSupport-r10        ENUMERATED { true }     OPTIONAL
    }
    */
    VOS_UINT32                                          bitOpGNSSAcquisitionAssistSupExt:1;
    VOS_UINT32                                          bitOpConfidenceSupportR10 : 1;
    VOS_UINT32                                          bitOpDopplerUncertaintyExtSupportR10 : 1;
    VOS_UINT32                                          bitOpSpare      : 29;

    LPP_CONFIDENCE_SUPPORT_R10_ENUM_UINT8               enConfidenceSupportR10;
    LPP_DOPPLER_UNCERTAINTY_EXT_SUPPORT_R10_ENUM_UINT8  enDopplerUncertaintyExtSupportR10;
    VOS_UINT8                                           ucAcquAssitExtNum;
    VOS_UINT8                                           ucRes;
}MTA_LPP_GNSS_ACQUISITION_ASSISTANCE_SUPPORT_STRU;


typedef struct
{
    VOS_UINT32                          ulAlmanacModelCnt;
    VOS_UINT8                           ucAlmanacModel;
    VOS_UINT8                           ucRes[3];
}MTA_LPP_ALMANAC_MODEL_STRU;


typedef struct
{
    /*
    GNSS-AlmanacSupport ::=     SEQUENCE {
        almanacModel        BIT STRING {    model-1     (0),
                                            model-2     (1),
                                            model-3     (2),
                                            model-4     (3),
                                            model-5     (4),
                                            model-6     (5) } (SIZE (1..8))     OPTIONAL,
        ...
    }
    */
    VOS_UINT32                                          bitOpGNSSAlmanacSupExt  :1;
    VOS_UINT32                                          bitOpAlmanacModel       :1;
    VOS_UINT32                                          bitOpSpare              :30;

    MTA_LPP_ALMANAC_MODEL_STRU                              stAlmanacModel;
}MTA_LPP_GNSS_ALMANAC_SUPPORT_STRU;


typedef struct
{
    VOS_UINT32                          ulUtcModelCnt;
    VOS_UINT8                           ucUTCModel;
    VOS_UINT8                           aucRes[3];
}MTA_LPP_UTC_MODEL_STRU;


typedef struct
{
    /*
    GNSS-UTC-ModelSupport ::=   SEQUENCE {
        utc-Model       BIT STRING {    model-1     (0),
                                        model-2     (1),
                                        model-3     (2),
                                        model-4     (3) } (SIZE (1..8))     OPTIONAL,
        ...
    }
    */
    VOS_UINT32                                          bitOpUtcModelExt    :1;
    VOS_UINT32                                          bitOpUtcModel       :1;
    VOS_UINT32                                          bitOpSpare          :30;

    MTA_LPP_UTC_MODEL_STRU                              stUtcModel;
}MTA_LPP_GNSS_UTC_MODEL_SUPPORT_STRU;


typedef struct
{
    /* Э����˽ṹΪ�� */
    VOS_UINT32              bitOGNSSAuxiliaryInfoSupExt :1;
    VOS_UINT32              bitOpSpare                  :31;
}MTA_LPP_GNSS_AUXILIARY_INFORMATION_SUPPORT_STRU;
typedef struct
{
    /*
    GNSS-GenericAssistDataSupportElement ::= SEQUENCE {
        gnss-ID                             GNSS-ID,
        sbas-ID                             SBAS-ID                     OPTIONAL, -- Cond GNSS ID SBAS
        gnss-TimeModelsSupport              GNSS-TimeModelListSupport
                                                                        OPTIONAL, -- Cond TimeModSup
        gnss-DifferentialCorrectionsSupport GNSS-DifferentialCorrectionsSupport
                                                                        OPTIONAL, -- Cond DGNSS-Sup
        gnss-NavigationModelSupport         GNSS-NavigationModelSupport
                                                                        OPTIONAL, -- Cond NavModSup
        gnss-RealTimeIntegritySupport       GNSS-RealTimeIntegritySupport
                                                                        OPTIONAL, -- Cond RTISup
        gnss-DataBitAssistanceSupport       GNSS-DataBitAssistanceSupport
                                                                        OPTIONAL, -- Cond DataBitsSup
        gnss-AcquisitionAssistanceSupport   GNSS-AcquisitionAssistanceSupport
                                                                        OPTIONAL, -- Cond AcquAssistSup
        gnss-AlmanacSupport                 GNSS-AlmanacSupport
                                                                        OPTIONAL, -- Cond AlmanacSup
        gnss-UTC-ModelSupport               GNSS-UTC-ModelSupport
                                                                        OPTIONAL, -- Cond UTCModSup
        gnss-AuxiliaryInformationSupport    GNSS-AuxiliaryInformationSupport
                                                                        OPTIONAL, -- Cond AuxInfoSup
        ...
    }
    */
    VOS_UINT32                                              bitOpGNSSGenAssistDataSupElementExt     :1;
    VOS_UINT32                                              bitOpSbasIds                            :1;
    VOS_UINT32                                              bitOpGnssTimeModelListSupport           :1;
    VOS_UINT32                                              bitOpGnssDifferentialCorrectionsSupport :1;
    VOS_UINT32                                              bitOpGnssNavigationModelSupport         :1;
    VOS_UINT32                                              bitOpRealTimeIntegritySupport           :1;
    VOS_UINT32                                              bitOpDataBitAssistanceSupport           :1;
    VOS_UINT32                                              bitOpAcquisitionAssistanceSupport       :1;
    VOS_UINT32                                              bitOpAlmanacSupport                     :1;
    VOS_UINT32                                              bitOpUtcModelSupport                    :1;
    VOS_UINT32                                              bitOpAuxiliaryInformationSupport        :1;
    VOS_UINT32                                              bitOpSpare                              :21;

    LPP_MTA_COMMON_GNSS_ID_STRU                             stGnssId;
    LPP_MTA_COMMON_SBAS_ID_STRU                             stSbasId;
    MTA_LPP_GNSS_TIME_MODE_LIST_SUPPORT_STRU                stGnssTimeModelListSupport;
    MTA_LPP_GNSS_DIFFERENTIAL_CORRECTIONS_SUPPORT_STRU      stGnssDifferentialCorrectionsSupport;
    MTA_LPP_GNSS_NAVIGATION_MODE_SUPPORT_STRU               stGnssNavigationModelSupport;/*empty*/
    MTA_LPP_GNSS_REAL_TIME_INTEGRITY_SUPPORT_STRU           stGnssRealTimeIntegritySupport;
    MTA_LPP_GNSS_DATA_BIT_ASSISTANCE_SUPPORT_STRU           stGnssDataBitAssistanceSupport;
    MTA_LPP_GNSS_ACQUISITION_ASSISTANCE_SUPPORT_STRU        stGnssAcquisitionAssistanceSupport;/*empty*/
    MTA_LPP_GNSS_ALMANAC_SUPPORT_STRU                       stGnssAlmanacSupport; /*empty*/
    MTA_LPP_GNSS_UTC_MODEL_SUPPORT_STRU                     stGnssUtcModelSupport; /*empty*/
    MTA_LPP_GNSS_AUXILIARY_INFORMATION_SUPPORT_STRU         stGnssAuxiliaryInformationSupport;
}MTA_LPP_GNSS_GENERIC_ASSISTANCE_DATA_SUPPORT_ELEMENT_STRU;


typedef struct
{
    /*
    GNSS-GenericAssistanceDataSupport ::=
                                    SEQUENCE (SIZE (1..16)) OF GNSS-GenericAssistDataSupportElement
    */
    VOS_UINT32                                                  ulSupportElementNum;
    MTA_LPP_GNSS_GENERIC_ASSISTANCE_DATA_SUPPORT_ELEMENT_STRU   astSupportElementArray[LPP_MAX_GNSS_GENERIC_ASSIST_DATA_SUPPORT_ELMENT_LEN];
}MTA_LPP_GNSS_GENERIC_ASSISTANCE_DATA_SUPPORT_STRU;


typedef struct
{
    /*
    AssistanceDataSupportList ::= SEQUENCE {
        gnss-CommonAssistanceDataSupport    GNSS-CommonAssistanceDataSupport,
        gnss-GenericAssistanceDataSupport   GNSS-GenericAssistanceDataSupport,
        ...
    }
    */
    VOS_UINT32                                          bitOpAssistDataSupportListExt   :1;
    VOS_UINT32                                          bitOpSpare                      :31;

    MTA_LPP_GNSS_COMMON_ASSISTANCE_DATA_SUPPORT_STRU    stGnssCommonAssistanceDataSupport;
    MTA_LPP_GNSS_GENERIC_ASSISTANCE_DATA_SUPPORT_STRU   stGnssGenericAssistanceDataSupport;
}MTA_LPP_ASSISTANCE_DATA_SUPPORT_LIST_STRU;


typedef struct
{
    /*
    VelocityTypes ::= SEQUENCE {
        horizontalVelocity                                      BOOLEAN,
        horizontalWithVerticalVelocity                          BOOLEAN,
        horizontalVelocityWithUncertainty                       BOOLEAN,
        horizontalWithVerticalVelocityAndUncertainty            BOOLEAN,
        ...
    }
    */
    VOS_UINT32                          bitOpExtIe  :1;
    VOS_UINT32                          bitSpare    :31;

    VOS_BOOL                            bHorizontalVelocity;
    VOS_BOOL                            bHorizontalWithVerticalVelocity;
    VOS_BOOL                            bHorizontalVelocityWithUncertainty;
    VOS_BOOL                            bHorizontalWithVerticalVelocityAndUncertainty;
}MTA_LPP_VELOCITY_TYPES_STRU;


typedef struct
{
    /*
    A-GNSS-ProvideCapabilities ::= SEQUENCE {
        gnss-SupportList            GNSS-SupportList                OPTIONAL,
        assistanceDataSupportList   AssistanceDataSupportList       OPTIONAL,
        locationCoordinateTypes     LocationCoordinateTypes         OPTIONAL,
        velocityTypes               VelocityTypes                   OPTIONAL,
        ...
    }
    */
    VOS_UINT32                                      bitOpAGNSSProvideCapExt         :1;
    VOS_UINT32                                      bitOpGnssSupportList            :1;
    VOS_UINT32                                      bitOpAssistanceDataSupportList  :1;
    VOS_UINT32                                      bitOpLocationCoordinateTypes    :1;
    VOS_UINT32                                      bitOpVelocityTypes              :1;
    VOS_UINT32                                      bitSpare                        :27;

    MTA_LPP_GNSS_SUPPORT_LIST_STRU                  stGnssSupportList;      /*FIXME:AT�ӿ���û�ж�Ӧ������*/
    MTA_LPP_ASSISTANCE_DATA_SUPPORT_LIST_STRU       stAssistanceDataSupportList;
    LPP_MTA_COMMON_LOCATION_COORDINATE_TYPE_STRU    stLocationCoordinateTypes;/*FIXME:AT�ӿ���û�ж�Ӧ������*/
    MTA_LPP_VELOCITY_TYPES_STRU                     stVelocityTypes;/*FIXME:AT�ӿ���û�ж�Ӧ������*/
}MTA_LPP_AGNSS_PROVIDE_CAP_STRU;
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                              ulMsgId;        /*_H2ASN_Skip*/ /* ��Ϣͷ */

    VOS_UINT32                              ulSessionId;    /*��ǰsessionID*/
    MTA_LPP_AGNSS_PROVIDE_CAP_STRU          stGnssProvideCap;
}MTA_LPP_GNSS_PROVIDE_CAPABITY_CNF_STRU;/*27.007 8.55-4*/


typedef struct
{
    /*
    A-GNSS-RequestCapabilities ::= SEQUENCE {
        gnss-SupportListReq             BOOLEAN,
        assistanceDataSupportListReq    BOOLEAN,
        locationVelocityTypesReq        BOOLEAN,
        ...
    }
    */
    VOS_UINT32                          bitOpAGNSSReqCapExt :1;
    VOS_UINT32                          bitOpSpare          :31;

    VOS_BOOL                            bGnssSupportListReq;
    VOS_BOOL                            bAssistanceDataSupportListReq;
    VOS_BOOL                            blocationVelocityTypesReq;
}LPP_MTA_GNSS_CAP_REQ_STRU;


typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/ /* ��Ϣͷ */

    /*
     27.007(2016-06�汾)�� ����Ϊ�գ���bitλ�����Ƿ�ѡ�У�
     ��������������GNSS������������ϢҲ��MTA����MTA����
     Э������Ƿ�Ҫ����GNSSģ�顣
    */
    VOS_UINT32                          ulSessionId;        /*��ǰsessionID*/
    LPP_MTA_GNSS_CAP_REQ_STRU           stGnssCapReq;
}LPP_MTA_GNSS_CAPABITY_REQ_STRU; /*27.007 8.55-4*/

typedef struct
{
    LPP_MTA_MSG_TYPE_ENUM_UINT32        enMsgID;            /*_H2ASN_MsgChoice_Export LPP_MTA_MSG_TYPE_ENUM_UINT32*/
    VOS_UINT8                           aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          LMM_LPP_MSG_TYPE_ENUM_UINT32
    ****************************************************************************/
}LMM_MTA_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    LMM_MTA_MSG_DATA                     stMsgData;
}LppMtaInterface_MSG;

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
 #pragma pack(pop)
#endif


#ifdef __cplusplus
#if __cplusplus

}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


#endif

