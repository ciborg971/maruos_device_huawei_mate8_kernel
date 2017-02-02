

#ifndef __LPPLRRCINTERFACE_H__
#define __LPPLRRCINTERFACE_H__


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include "LPSCommon.h"
#include "ComInterface.h"
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 macro
*****************************************************************************/

#define LPP_LRRC_MSG_HDR                                    (PS_MSG_ID_LPP_TO_LRRC_BASE)
#define LRRC_LPP_MSG_HDR                                    (PS_MSG_ID_LRRC_TO_LPP_BASE)


/* UE֧�����BAND */
#define LRRC_LPP_MAX_BAND_IND_NUM                           (256)
/* ���BAND��Ϣ�������� */
#define LRRC_LPP_MAX_BAND_IND_ARRAY_NUM                     (8)

/* GNSS���ݳ��� */
#define LPP_LRRC_MAX_LOCATION_COORDINATES_DATA_LEN          (96)
#define LPP_LRRC_MAX_CHORIZONTAL_VELOCITY_DATA_LEN          (3)
#define LPP_LRRC_MAX_GNSS_TOD_MSEC_DATA_LEN                 (3)


/* ECID�ϱ������������ */
#define LRRC_LPP_MAX_ECID_MEAS_NCELL_RESULT_NUM             (32)

/* ECID�ϱ������С���������� + ����С�� */
#define LRRC_LPP_MAX_ECID_MEAS_RESULT_NUM                   (LRRC_LPP_MAX_ECID_MEAS_NCELL_RESULT_NUM + 1)


/* OTDOA ����PRS MUTING INFO ����  4���ֽ�*/
#define LPP_LRRC_MAX_PRS_MUTING_INFO_LEN                    (4)



/* OTDOA֧��������Ƶ����Ƶ�� */
#define LPP_LRRC_MAX_OTDOA_NEIGHBOUR_FREQ_INFO_NUM          (3)
/* OTDOA֧������Ƶ���� */
#define LPP_LRRC_MAX_OTDOA_FREQ_INFO_NUM                    (LPP_LRRC_MAX_OTDOA_NEIGHBOUR_FREQ_INFO_NUM + 1)

/* OTDOAÿ������Ƶ����֧�ֵ����С������*/
#define LPP_LRRC_MAX_OTDOA_NEIGHBOUR_SINGLE_FREQ_CELL_NUM   (24)

/* OTDOA����Ƶ��֧�ֵ����С������*/
#define LRRC_LPP_MAX_OTDOA_NEIGHBOUR_ALL_FREQ_CELL_NUM     \
                              (LPP_LRRC_MAX_OTDOA_NEIGHBOUR_SINGLE_FREQ_CELL_NUM * LPP_LRRC_MAX_OTDOA_NEIGHBOUR_FREQ_INFO_NUM)







/*****************************************************************************
  3 Massage Declare
*****************************************************************************/



/*****************************************************************************
  4 Enum
*****************************************************************************/
/*****************************************************************************
 ö����    : LPP_LRRC_MSG_ID_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : LPP��LRRC����Ϣԭ������
*****************************************************************************/
enum LPP_LRRC_MSG_ID_ENUM
{
    /* LPP����LRRC��ԭ�� */
    ID_LPP_LRRC_GNSS_DATA_INFO_IND                  = (LPP_LRRC_MSG_HDR + 0x00),/* _H2ASN_MsgChoice LPP_LRRC_GNSS_DATA_INFO_IND_STRU */
    ID_LPP_LRRC_ECID_MEAS_REQ                       = (LPP_LRRC_MSG_HDR + 0x01),/* _H2ASN_MsgChoice LPP_LRRC_ECID_MEAS_REQ_STRU */
    ID_LPP_LRRC_OTDOA_MEAS_REQ                      = (LPP_LRRC_MSG_HDR + 0x02),/* _H2ASN_MsgChoice LPP_LRRC_OTDOA_MEAS_REQ_STRU */

    /* LRRC����LPP��ԭ�� */
    ID_LRRC_LPP_LAS_LCS_CAPABILITY_IND              = (LRRC_LPP_MSG_HDR + 0x00),/* _H2ASN_MsgChoice LRRC_LPP_LAS_LCS_CAPABILITY_IND_STRU */
    ID_LRRC_LPP_ECID_MEAS_CNF                       = (LRRC_LPP_MSG_HDR + 0x01),/* _H2ASN_MsgChoice LRRC_LPP_ECID_MEAS_CNF_STRU */
    ID_LRRC_LPP_ECID_MEAS_IND                       = (LRRC_LPP_MSG_HDR + 0x02),/* _H2ASN_MsgChoice LRRC_LPP_ECID_MEAS_IND_STRU */
    ID_LRRC_LPP_OTDOA_MEAS_CNF                      = (LRRC_LPP_MSG_HDR + 0x03),/* _H2ASN_MsgChoice LRRC_LPP_OTDOA_MEAS_CNF_STRU */
    ID_LRRC_LPP_OTDOA_MEAS_IND                      = (LRRC_LPP_MSG_HDR + 0x04),/* _H2ASN_MsgChoice LRRC_LPP_OTDOA_MEAS_IND_STRU */

    ID_LPP_LRRC_MSG_ID_BUTT
};
typedef VOS_UINT32   LPP_LRRC_MSG_ID_ENUM_UINT32;

/*****************************************************************************
 ö����    : LPP_LRRC_INFO_FLAG_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : LPP��LRRC��Ϣ��Ч�Ա��
*****************************************************************************/
enum LPP_LRRC_INFO_FLAG_ENUM
{
    LPP_LRRC_INFO_FLAG_INVALID,
    LPP_LRRC_INFO_FLAG_VALID,
    LPP_LRRC_INFO_FLAG_BUTT
};
typedef VOS_UINT8   LPP_LRRC_INFO_FLAG_ENUM_UINT8;

/*****************************************************************************
 �ṹ����   : LPP_LRRC_LOCATION_COORDINATES_TYPE_ENUM
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : LPP֪ͨLRRC GPS��������
*****************************************************************************/
enum LPP_LRRC_LOCATION_COORDINATES_TYPE_ENUM
{
    LPP_LRRC_LOC_COOR_ELLIP_POINT,
    LPP_LRRC_LOC_COOR_ELLIP_POINT_WITH_ALTI,
    LPP_LRRC_LOC_COOR_ELLIP_POINT_WITH_UNCERTAIN_CIRCLE,
    LPP_LRRC_LOC_COOR_ELLIP_POINT_WITH_UNCERTAIN_ELLIPS,
    LPP_LRRC_LOC_COOR_ELLIP_POINT_WITH_ALTI_AND_UNCERTAIN_ELLIPS,
    LPP_LRRC_LOC_COOR_ELLIP_ARC,
    LPP_LRRC_LOC_COOR_POLYGON,
    LPP_LRRC_LOC_COOR_BUTT
};
typedef VOS_UINT8   LPP_LRRC_LOCATION_COORDINATES_TYPE_ENUM_UINT8;

/*****************************************************************************
 �ṹ����   : LPP_LRRC_LCS_MEAS_CMD_ENUM
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : LPP����LCS�Ĳ�������
*****************************************************************************/
enum LPP_LRRC_LCS_MEAS_CMD_ENUM
{
    LPP_LRRC_LCS_MEAS_CMD_REL,
    LPP_LRRC_LCS_MEAS_CMD_SETUP,
    LPP_LRRC_LCS_MEAS_CMD_BUTT
};
typedef VOS_UINT8   LPP_LRRC_LCS_MEAS_CMD_ENUM_UINT8;

/*****************************************************************************
 �ṹ����   : LRRC_LPP_LCS_MEAS_RESULT_ENUM
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : LRRC�ظ�LPP�����������
*****************************************************************************/
enum LRRC_LPP_LCS_MEAS_RESULT_ENUM
{
    LRRC_LPP_LCS_MEAS_RESULT_SUCC,
    LRRC_LPP_LCS_MEAS_IDLE_STATUS_ERROR,                                        /* RRC����IDLE̬���� */
    LRRC_LPP_LCS_MEAS_CONN_REL_STATUS_ERROR,                                    /* RRC��������̬�ͷ����� */
    LRRC_LPP_LCS_MEAS_PHY_FAIL_STATUS_ERROR,                                    /* RRC����PHYʧ�� */
    LRRC_LPP_LCS_MEAS_PARAM_INVALID_ERROR,                                      /* �������Ϸ�������EARFCNԽ�� */
    LRRC_LPP_LCS_MEAS_RESULT_OTHER_CAUSE,
    LRRC_LPP_LCS_MEAS_RESULT_BUTT
};
typedef VOS_UINT8   LRRC_LPP_LCS_MEAS_RESULT_ENUM_UINT8;

/*****************************************************************************
 �ṹ����   : LPP_LRRC_OTDOA_PRS_BANDWIDTH_ENUM
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : PRS�Ĵ���
*****************************************************************************/
enum LPP_LRRC_OTDOA_PRS_BANDWIDTH_ENUM
{
    LPP_LRRC_OTDOA_PRS_BANDWIDTH_N6,
    LPP_LRRC_OTDOA_PRS_BANDWIDTH_N15,
    LPP_LRRC_OTDOA_PRS_BANDWIDTH_N25,
    LPP_LRRC_OTDOA_PRS_BANDWIDTH_N50,
    LPP_LRRC_OTDOA_PRS_BANDWIDTH_N75,
    LPP_LRRC_OTDOA_PRS_BANDWIDTH_N100,
    LPP_LRRC_OTDOA_PRS_BANDWIDTH_BUTT
};
typedef VOS_UINT8   LPP_LRRC_OTDOA_PRS_BANDWIDTH_ENUM_UINT8;

/*****************************************************************************
 �ṹ����   : LPP_LRRC_OTDOA_PRS_BANDWIDTH_ENUM
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : PRS�Ĵ���
*****************************************************************************/
enum LPP_LRRC_OTDOA_NUMDL_FRAMES_ENUM
{
    LPP_LRRC_OTDOA_NUMDL_FRAMES_1                   = 1,
    LPP_LRRC_OTDOA_NUMDL_FRAMES_2                   = 2,
    LPP_LRRC_OTDOA_NUMDL_FRAMES_4                   = 4,
    LPP_LRRC_OTDOA_NUMDL_FRAMES_6                   = 6,
    LPP_LRRC_OTDOA_NUMDL_FRAMES_BUTT
};
typedef VOS_UINT8   LPP_LRRC_OTDOA_NUMDL_FRAMES_ENUM_UINT8;

/*****************************************************************************
 �ṹ����   : LPP_LRRC_OTDOA_PRS_BANDWIDTH_ENUM
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : PRS�Ĵ���
*****************************************************************************/
enum LPP_LRRC_OTDOA_PRS_MUTING_INFO_TYPE_ENUM
{
    LPP_LRRC_OTDOA_PRS_MUTING_INFO_TYPE_PO2,
    LPP_LRRC_OTDOA_PRS_MUTING_INFO_TYPE_PO4,
    LPP_LRRC_OTDOA_PRS_MUTING_INFO_TYPE_PO8,
    LPP_LRRC_OTDOA_PRS_MUTING_INFO_TYPE_PO16,
    LPP_LRRC_OTDOA_PRS_MUTING_INFO_TYPE_BUTT
};
typedef VOS_UINT8   LPP_LRRC_OTDOA_PRS_MUTING_INFO_TYPE_ENUM_UINT8;

/*****************************************************************************
 �ṹ����   : LPP_LRRC_OTDOA_ANT_PORT_CFG_ENMUM
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : CRI��PORT
*****************************************************************************/
enum LPP_LRRC_OTDOA_ANT_PORT_CFG_ENUM
{
    LPP_LRRC_OTDOA_ANT_PORT_1_OR_2,
    LPP_LRRC_OTDOA_ANT_PORT_4,

    LPP_LRRC_OTDOA_ANT_PORT_BUTT
};
typedef VOS_UINT8   LPP_LRRC_OTDOA_ANT_PORT_CFG_ENUM_UINT8;

/*****************************************************************************
 �ṹ����   : LPP_LRRC_OTDOA_CP_TYPE_ENMUM
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : OTDOA assistance info�е���������
*****************************************************************************/
enum LPP_LRRC_OTDOA_CP_TYPE_ENUM
{
    LPP_LRRC_OTDOA_CP_TYPE_NORMAL,

    LPP_LRRC_OTDOA_CP_TYPE_EXTENDED,

    LPP_LRRC_OTDOA_CP_TYPE_BUTT
};
typedef VOS_UINT8   LPP_LRRC_OTDOA_CP_TYPE_ENUM_UINT8;

/*********************************************************
 ö����    : LPP_LRRC_OTDOA_RPRT_INTERVAL_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  :
**********************************************************/
enum LPP_LRRC_OTDOA_RPRT_INTERVAL_ENUM
{
    LPP_LRRC_OTDOA_RPRT_INTERVAl_SECOND_1 = 0,
    LPP_LRRC_OTDOA_RPRT_INTERVAl_SECOND_2,
    LPP_LRRC_OTDOA_RPRT_INTERVAl_SECOND_4,
    LPP_LRRC_OTDOA_RPRT_INTERVAl_SECOND_8,
    LPP_LRRC_OTDOA_RPRT_INTERVAl_SECOND_10,
    LPP_LRRC_OTDOA_RPRT_INTERVAl_SECOND_16,
    LPP_LRRC_OTDOA_RPRT_INTERVAl_SECOND_20,
    LPP_LRRC_OTDOA_RPRT_INTERVAl_SECOND_32,
    LPP_LRRC_OTDOA_RPRT_INTERVAl_SECOND_64,
    LPP_LRRC_OTDOA_RPRT_INTERVAl_BUTT
};
typedef VOS_UINT16 LPP_LRRC_OTDOA_RPRT_INTERVAL_ENUM_UINT16;

/*****************************************************************************
 ö����    : OTDOA_TARGET_DEVICE_ERROR_CAUSES_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : OTDOA_TARGET_DEVICE_ERROR_CAUSES_ENUM_UINT16
*****************************************************************************/
enum LRRC_LPP_OTDOA_TARGET_DEVICE_ERROR_CAUSES_ENUM
{
    LRRC_LPP_OTDOA_MEAS_NO_ERROR,
    LRRC_LPP_OTDOA_TARGET_DEVICE_UNDEFINED,
    LRRC_LPP_OTDOA_ASSISTANCE_DATA_MISSING,
    LRRC_LPP_OTDOA_UNABLE_TO_MEASURE_REF_CELL,
    LRRC_LPP_OTDOA_UNABLE_TO_MEASURE_ANY_NEIGHBOUR_CELL,
    LRRC_LPP_OTDOA_ATTEMPTED_BUT_UNABLE_TO_MEASURE_SOME_NEIGHBOUR_CELLS,
    LRRC_LPP_OTDOA_TARGET_DEVICE_ERROR_CAUSES_BUFF
};
typedef VOS_UINT16 LRRC_LPP_OTDOA_TARGET_DEVICE_ERROR_CAUSES_ENUM_UINT16;

/*****************************************************************************
  5 Struct
*****************************************************************************/

/*****************************************************************************
 �ṹ����   : LRRC_LPP_LAS_LCS_CAPABILITY_IND_STRU
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : LRRC�ϱ�LCSҵ��UE������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LPP_LRRC_MSG_ID_ENUM_UINT32                     enMsgId;                    /*_H2ASN_Skip*/

    /* 0:����֧�֣�1:����֧��*/
    LPP_LRRC_INFO_FLAG_ENUM_UINT8                   ucUeRxTxTimeDiffMeasFlag;

    LPP_LRRC_INFO_FLAG_ENUM_UINT8                   ucOtdoaUeAssistFlag;

    /* 0:����֧�֣�1:����֧�� */
    LPP_LRRC_INFO_FLAG_ENUM_UINT8                   ucInterFreqRSTDMeasFlag;

    /* 0:����֧�֣�1:����֧�� */
    LPP_LRRC_INFO_FLAG_ENUM_UINT8                   ucAddOtdoaNeighbourCellInfoListFlag;

    /*
    usBandNum ȡֵ��Χ[1,256]
    ulBandInd,ÿ��BIT��1:����֧�֣�0����֧�֣�ulBandInd[0]�е�һ��BIT����BAND1,��������;
    */

    VOS_UINT32                                      ulBandNum;
    VOS_UINT32                                      aulBandInd[LRRC_LPP_MAX_BAND_IND_ARRAY_NUM];

}LRRC_LPP_LAS_LCS_CAPABILITY_IND_STRU;

/*****************************************************************************
 �ṹ����   : LPP_LRRC_LOCATION_COORDINATES_DATA_STRU
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : LocationCoordinatesData������Ϣ
*****************************************************************************/
typedef struct
{
    LPP_LRRC_LOCATION_COORDINATES_TYPE_ENUM_UINT8   enLocationCoordinatesType;
    VOS_UINT16                                      usLocationCoordinatesDataLen;
    VOS_UINT8                                       ucReserved;
    VOS_UINT8                                       aucLocationCoordinatesData[LPP_LRRC_MAX_LOCATION_COORDINATES_DATA_LEN];
}LPP_LRRC_LOCATION_COORDINATES_DATA_STRU;

/*****************************************************************************
 �ṹ����   : LPP_LRRC_GPS_DATA_INFO_REQ_STRU
 Э����   :
 ASN.1 ���� : 36.331Э��LocationInfo-r10
 �ṹ˵��   : LPP�·�LocationCoordinatesData���ݸ�LRRC
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LPP_LRRC_MSG_ID_ENUM_UINT32                     enMsgId;                    /*_H2ASN_Skip*/
    /*

    0: ɾ�����ݣ�RRC�����������
    1: �����������ݣ����Ǳ�������

    */

    LPP_LRRC_INFO_FLAG_ENUM_UINT8                   ucGnssDataFlag;

    /* 0:����û�����ݣ�1:������*/
    LPP_LRRC_INFO_FLAG_ENUM_UINT8                   ucHorizontalVelocityFlag;

    /* 0:����û�����ݣ�1:������*/
    LPP_LRRC_INFO_FLAG_ENUM_UINT8                   ucGnssTodMsecFlag;

    /* 0:����û�����ݣ�1:������*/
    LPP_LRRC_INFO_FLAG_ENUM_UINT8                   ucLocationDataFlag;

    /*
    GPS�������ݵĳ��ȣ���λ�ֽڣ����Ǳ��������ݳ���
    ellipsoid-Point-r10                                       6
    ellipsoidPointWithAltitude-r10                            8
    ellipsoidPointWithUncertaintyCircle-r11                   7
    ellipsoidPointWithUncertaintyEllipse-r11                  10
    ellipsoidPointWithAltitudeAndUncertaintyEllipsoid-r11     13
    ellipsoidArc-r11                                          12
    polygon-r11                                               90

    horizontalVelocity-r10                                    3
    gnss-TOD-msec-r10                                         3

    */

    VOS_UINT8                                       aucHorizontalVelocityData[LPP_LRRC_MAX_CHORIZONTAL_VELOCITY_DATA_LEN];
    VOS_UINT8                                       aucGnssTodMsecData[LPP_LRRC_MAX_GNSS_TOD_MSEC_DATA_LEN];
    VOS_UINT8                                       aucReserved[2];

    LPP_LRRC_LOCATION_COORDINATES_DATA_STRU         stLocationCoordinatesData;
}LPP_LRRC_GNSS_DATA_INFO_IND_STRU;

/*****************************************************************************
 �ṹ����   : LPP_LRRC_ECELL_ID_MEAS_REQ_STRU
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : LPP�·�LRRC��������ֹͣECELL ID��������
*****************************************************************************/
typedef struct
{

    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LPP_LRRC_MSG_ID_ENUM_UINT32                     enMsgId;                    /*_H2ASN_Skip*/

    LPP_LRRC_LCS_MEAS_CMD_ENUM_UINT8                ucLcsMeasCmd;

    /* 0:����֧�֣�1:����֧��*/
    VOS_UINT8                                       ucRxTxTimeDiffMeasFlag;
    VOS_UINT8                                       aucReserved[2];
}LPP_LRRC_ECID_MEAS_REQ_STRU;

/*****************************************************************************
 �ṹ����   : LRRC_LPP_ECID_MEAS_CNF_STRU
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : LRRC�ظ�LPP�ظ���ȷ����Ϣ
*****************************************************************************/
typedef struct
{

    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LPP_LRRC_MSG_ID_ENUM_UINT32                     enMsgId;                    /*_H2ASN_Skip*/

    LRRC_LPP_LCS_MEAS_RESULT_ENUM_UINT8             ucResult;
    VOS_UINT8                                       aucReserved[3];
}LRRC_LPP_ECID_MEAS_CNF_STRU;

/*****************************************************************************
 �ṹ����   : LRRC_LPP_CELL_GLOBAL_ID_INFO_STRU
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : GLOBAL ID��Ϣ
*****************************************************************************/
typedef struct
{
    /* PLMN ID��տڱ���һ�� */
    VOS_UINT8                           aucPlmnId[3];
    VOS_UINT8                           ucReserved;

    /* ϵͳ��Ϣ���CELL ID ��Ϣ*/
    VOS_UINT32                          ulCellIdentity;
}LRRC_LPP_CELL_GLOBAL_ID_INFO_STRU;

/*****************************************************************************
 �ṹ����   : LRRC_LPP_ECID_MEAS_RESULT_STRU
 Э����   :
 ASN.1 ���� : 36355��MeasuredResultsElement IE
 �ṹ˵��   : LRRC�ϱ�ECID����ÿ��С���������Ϣ
*****************************************************************************/
typedef struct
{

    /* 0:����UeRxTxTimeDiff������Ч��1:����UeRxTxTimeDiff������Ч ,SFN��UeRxTxTimeDiffͬʱ��Ч��������С��������Ч */
    LPP_LRRC_INFO_FLAG_ENUM_UINT8                   ucUeRxTxTimeDiffMeasFlag;

    /* 0:����CellGlobalId������Ч��1:����CellGlobalId������Ч */
    LPP_LRRC_INFO_FLAG_ENUM_UINT8                   ucCellGlobalIdFlag;

    /* ȡֵ[0,97] */
    VOS_UINT8                                       ucRsrp;
    /* ȡֵ[0,34] */
    VOS_UINT8                                       ucRsrq;

    VOS_UINT32                                      ulArfcn;

    /* ȡֵ[0,503] */
    VOS_UINT16                                      usPhyCellId;

    VOS_UINT16                                      usSfn;
    /* ȡֵ[0,4095] */
    VOS_UINT16                                      usUeRxTxTimeDiff;

    VOS_UINT16                                      usReserved;

    LRRC_LPP_CELL_GLOBAL_ID_INFO_STRU               stGlobalIdInfo;
}LRRC_LPP_ECID_MEAS_RESULT_STRU;

/*****************************************************************************
 �ṹ����   : LRRC_LPP_ECID_MEAS_RESULT_LIST_STRU
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : LRRC�ϱ�ECELL ID������Ϣ�б�
*****************************************************************************/
typedef struct
{
    /* ȡֵ[1,33] */
    VOS_UINT32                                      ulCellNum;
    LRRC_LPP_ECID_MEAS_RESULT_STRU                  astLrrcLppEcidMeasResult[LRRC_LPP_MAX_ECID_MEAS_RESULT_NUM];
}LRRC_LPP_ECID_MEAS_RESULT_LIST_STRU;

/*****************************************************************************
 �ṹ����   : LRRC_LPP_ECID_MEAS_IND_STRU
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : LRRC�ϱ�ECELL ID������Ϣ
*****************************************************************************/
typedef struct
{

    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LPP_LRRC_MSG_ID_ENUM_UINT32                     enMsgId;                    /*_H2ASN_Skip*/

    LRRC_LPP_ECID_MEAS_RESULT_LIST_STRU             stLrrcLppEcidMeasResultList;
}LRRC_LPP_ECID_MEAS_IND_STRU;

/*****************************************************************************
 �ṹ����   : LPP_LRRC_PRS_INFO_STRU
 Э����   :
 ASN.1 ���� : 36355 PRS-Info
 �ṹ˵��   : PRS��Ϣ
*****************************************************************************/
typedef struct
{
    /* 0:����PRS_MUTING_INFO������Ч��1:����PRS_MUTING_INFO������Ч */
    LPP_LRRC_INFO_FLAG_ENUM_UINT8                   ucPrsMutingInfoFlag;

    LPP_LRRC_OTDOA_PRS_BANDWIDTH_ENUM_UINT8         ucPrsBandWidth;
    LPP_LRRC_OTDOA_NUMDL_FRAMES_ENUM_UINT8          ucNumdlFrames;

    VOS_UINT8                                       ucResvered1;

    /* ȡֵ (0,4095)*/
    VOS_UINT16                                      usPrsConfigurationIndex;

    VOS_UINT8                                       ucResvered2;

    LPP_LRRC_OTDOA_PRS_MUTING_INFO_TYPE_ENUM_UINT8  ucPrsMutingInfoType;

    VOS_UINT16                                      usPrsMutingInfo;
    VOS_UINT8                                       aucResvered3[2];

}LPP_LRRC_PRS_INFO_STRU;

/*****************************************************************************
 �ṹ����   : LPP_LRRC_OTDOA_REFERENCE_CELL_INFO_STRU
 Э����   :
 ASN.1 ���� : 36355 OTDOA-ReferenceCellInfo
 �ṹ˵��   : OTDOA REFERENCE CELL INFO
*****************************************************************************/
typedef struct
{
    /* 0:����CellGlobalId������Ч��1:����CellGlobalId������Ч */
    LPP_LRRC_INFO_FLAG_ENUM_UINT8                   ucCellGlobalIdFlag;

    /* 0:PRS INFO ��Ч��1: PRS INFO ��Ч */
    LPP_LRRC_INFO_FLAG_ENUM_UINT8                   ucPrsInfoFlag;

    /* 0:ucAntennaPortConfig ��Ч��1: ucAntennaPortConfig ��Ч */
    LPP_LRRC_INFO_FLAG_ENUM_UINT8                   ucAntennaPortConfigFlag;

    /* ����տ�û�����ã����·������ʱ����LRRC��д������С��һ��, */
    /*
    The field is mandatory present if the antenna port configuration of the OTDOA assistance data reference cell is not the same as the antenna port configuration of the target devices's current primary cell.
    */
    LPP_LRRC_OTDOA_ANT_PORT_CFG_ENUM_UINT8          ucAntennaPortConfig;

    LPP_LRRC_OTDOA_CP_TYPE_ENUM_UINT8               ucCpLen;

    VOS_UINT8                                       aucReserved[1];

    /* ȡֵ[0,503] */
    VOS_UINT16                                      usPhyCellId;

    VOS_UINT32                                      ulEarfcn;

    LRRC_LPP_CELL_GLOBAL_ID_INFO_STRU               stCellGlobalIdInfo;

    LPP_LRRC_PRS_INFO_STRU                          stPrsInfo;

}LPP_LRRC_OTDOA_REFERENCE_CELL_INFO_STRU;

/*****************************************************************************
 �ṹ����   : LPP_LRRC_OTDOA_NEIGHBOUR_CELL_INFO_STRU
 Э����   :
 ASN.1 ���� : 36355 OTDOA-NeighbourCellInfoElement
 �ṹ˵��   : OTDOA ������Ϣ
*****************************************************************************/
typedef struct
{
    /* 0:����CellGlobalId������Ч��1:����CellGlobalId������Ч */
    LPP_LRRC_INFO_FLAG_ENUM_UINT8                   ucCellGlobalIdFlag;

    /* 0:PRS INFO ��Ч��1: PRS INFO ��Ч */
    LPP_LRRC_INFO_FLAG_ENUM_UINT8                   ucPrsInfoFlag;

    /* 0:ucAntennaPortConfig ��Ч��1: ucAntennaPortConfig ��Ч */
    LPP_LRRC_INFO_FLAG_ENUM_UINT8                   ucAntennaPortConfigFlag;

    /* 0:SlotNumberOffset ��Ч��1: SlotNumberOffset ��Ч */
    LPP_LRRC_INFO_FLAG_ENUM_UINT8                   ucSlotNumberOffsetFlag;

    /* 0:prs-SubframeOffset ��Ч��1: prs-SubframeOffset ��Ч */
    LPP_LRRC_INFO_FLAG_ENUM_UINT8                   ucPrsSubFramOffsettFlag;


    /* The field is mandatory present if the antenna port configuration is not the same as for the assistance data reference cell; otherwise it is not present. */
    LPP_LRRC_OTDOA_ANT_PORT_CFG_ENUM_UINT8          ucAntennaPortConfig;


    /* The field is mandatory present if the cyclic prefix length is not the same as for the assistance data reference cell; otherwise it is not present. */
    LPP_LRRC_OTDOA_CP_TYPE_ENUM_UINT8               ucCpLen;

    /* ȡֵ[0,19] */
    VOS_UINT8                                       ucSlotNumberOffset;

    /* ȡֵ[0,503] */
    VOS_UINT16                                      usPhyCellId;

    /* ȡֵ[0,1279] */
    VOS_UINT16                                      usPrsSubframeOffset;

    /* ȡֵ[0,16383] */
    VOS_UINT16                                      usExpectedRSTD;

    /* ȡֵ[0,1023] */
    VOS_UINT16                                      usExpectedRSTDUncertainty;

    LRRC_LPP_CELL_GLOBAL_ID_INFO_STRU               stCellGlobalIdInfo;

    /* The field is mandatory present if the PRS configuration is not the same as for the assistance data reference cell; otherwise it is not present. */
    LPP_LRRC_PRS_INFO_STRU                          stPrsInfo;

}LPP_LRRC_OTDOA_NEIGHBOUR_CELL_INFO_STRU;

/*****************************************************************************
 �ṹ����   : LPP_LRRC_OTDOA_NEIGHBOUR_FREQ_INFO_STRU
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : ÿ������Ƶ���С����Ϣ�б�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                      ulEarfcn;
    VOS_UINT32                                      ulCellNum;
    LPP_LRRC_OTDOA_NEIGHBOUR_CELL_INFO_STRU         stOtdoaNeighbourCellInfoList[LPP_LRRC_MAX_OTDOA_NEIGHBOUR_SINGLE_FREQ_CELL_NUM];
}LPP_LRRC_OTDOA_NEIGHBOUR_FREQ_INFO_STRU;

/*****************************************************************************
 �ṹ����   : LPP_LRRC_OTDOA_NEIGHBOUR_CELL_INFO_LIST_STRU
 Э����   :
 ASN.1 ���� : 36355 OTDOA-NeighbourCellInfoList
 �ṹ˵��   : OTDOA NEIGHBOUR CELL INFO
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                      ulFreqInfoNum;

    LPP_LRRC_OTDOA_NEIGHBOUR_FREQ_INFO_STRU         stOtdoaNeighbourFreqInfoList[LPP_LRRC_MAX_OTDOA_NEIGHBOUR_FREQ_INFO_NUM];
}LPP_LRRC_OTDOA_NEIGHBOUR_CELL_INFO_LIST_STRU;

/*****************************************************************************
 �ṹ����   : LPP_LRRC_OTDOA_MEAS_ASSISTANCE_DATA_STRU
 Э����   :
 ASN.1 ���� : 36355  OTDOA-ProvideAssistanceData
 �ṹ˵��   : OTDOA ��������
*****************************************************************************/
typedef struct
{
    /* 0:otdoa ReferenceCellInfo ��Ч��1: otdoa ReferenceCellInfo ��Ч */
    LPP_LRRC_INFO_FLAG_ENUM_UINT8                   ucOtdoaReferenceCellInfoFlag;

    /* 0:otdoa NeighbourCellInfo ��Ч��1: otdoa NeighbourCellInfo ��Ч */
    LPP_LRRC_INFO_FLAG_ENUM_UINT8                   ucOtdoaNeighbourCellInfoFlag;

    VOS_UINT8                                       aucReserved[2];

    LPP_LRRC_OTDOA_REFERENCE_CELL_INFO_STRU         stOtdoaReferenceCellInfo;

    LPP_LRRC_OTDOA_NEIGHBOUR_CELL_INFO_LIST_STRU    stOtdoaNeighbourCellInfo;
}LPP_LRRC_OTDOA_MEAS_ASSISTANCE_DATA_STRU;

/*****************************************************************************
 �ṹ����   : LPP_LRRC_OTDOA_MEAS_REQ_STRU
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : LPP�·�LRRC��������ֹͣOTDOA��������
*****************************************************************************/
typedef struct
{

    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LPP_LRRC_MSG_ID_ENUM_UINT32                     enMsgId;                    /*_H2ASN_Skip*/

    LPP_LRRC_LCS_MEAS_CMD_ENUM_UINT8                ucLcsMeasCmd;

    /* 0:OtdoaMeasAssistanceData  ��Ч��1: OtdoaMeasAssistanceData ��Ч */
    LPP_LRRC_INFO_FLAG_ENUM_UINT8                   ucOtdoaMeasAssistanceDataFlag;
    LPP_LRRC_OTDOA_RPRT_INTERVAL_ENUM_UINT16        enOtdoaRprtInterval;

    LPP_LRRC_OTDOA_MEAS_ASSISTANCE_DATA_STRU        stLppLrrcOtdoaMeasAssistanceData;
}LPP_LRRC_OTDOA_MEAS_REQ_STRU;

/*****************************************************************************
 �ṹ����   : LPP_LRRC_OTDOA_MEAS_CNF_STRU
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : LPP�·�LRRC��������ֹͣOTDOA��������
*****************************************************************************/
typedef struct
{

    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LPP_LRRC_MSG_ID_ENUM_UINT32                     enMsgId;                    /*_H2ASN_Skip*/
    LRRC_LPP_LCS_MEAS_RESULT_ENUM_UINT8             ucResult;
    VOS_UINT8                                       aucReserved[3];
}LRRC_LPP_OTDOA_MEAS_CNF_STRU;

/*****************************************************************************
 �ṹ����   : LRRC_LPP_OTDOA_MEAS_QUALITY_STRU
 Э����   :
 ASN.1 ���� : 36355 OTDOA-MeasQuality
 �ṹ˵��   : OTDOA MEAS QUALITY��Ϣ
*****************************************************************************/
typedef struct
{

    /* 0:����ErrorNumSample������Ч��1:����ErrorNumSample������Ч */
    LPP_LRRC_INFO_FLAG_ENUM_UINT8                   ucErrorNumSampleFlag;

    /* ȡֵ[0,3]*/
    VOS_UINT8                                       ucErrorResolution;

    /* ȡֵ[0,31]*/
    VOS_UINT8                                       ucErrorValue;

    /* ȡֵ[0,7]*/
    VOS_UINT8                                       ucErrorNumSample;

}LRRC_LPP_OTDOA_MEAS_QUALITY_STRU;

/*****************************************************************************
 �ṹ����   : LRRC_LPP_OTDOA_NEIGHBOUR_MEAS_STRU
 Э����   :
 ASN.1 ���� : 36331 NeighbourMeasurementElement
 �ṹ˵��   : OTDOA����������Ϣ
*****************************************************************************/
typedef struct
{

    /* 0:����CellGlobalId������Ч��1:����CellGlobalId������Ч */
    LPP_LRRC_INFO_FLAG_ENUM_UINT8                   ucCellGlobalIdFlag;

    VOS_UINT8                                       aucReserved[3];

    /* ȡֵ[0,503] */
    VOS_UINT16                                      usPhyCellIdNeighbour;

    /* ȡֵ[0,12711] */
    VOS_UINT16                                      usRstd;

    VOS_UINT32                                      ulEarfcn;

    LRRC_LPP_CELL_GLOBAL_ID_INFO_STRU               stCellGlobalIdInfo;

    LRRC_LPP_OTDOA_MEAS_QUALITY_STRU                stNeighboureMeasQuality;

}LRRC_LPP_OTDOA_NEIGHBOUR_MEAS_STRU;

/*****************************************************************************
 �ṹ����   : LRRC_LPP_OTDOA_NEIGHBOUR_MEAS_LIST_STRU
 Э����   :
 ASN.1 ���� : 36355 NeighbourMeasurementList
 �ṹ˵��   : OTDOA�ϱ��������Ĳ�����Ϣ
*****************************************************************************/
typedef struct
{

    VOS_UINT32                                      ulCellNum;
    LRRC_LPP_OTDOA_NEIGHBOUR_MEAS_STRU              stNeighbourMeasurement[LRRC_LPP_MAX_OTDOA_NEIGHBOUR_ALL_FREQ_CELL_NUM];
}LRRC_LPP_OTDOA_NEIGHBOUR_MEAS_LIST_STRU;

/*****************************************************************************
 �ṹ����   : LPP_LRRC_OTDOA_MEAS_IND_STRU
 Э����   :
 ASN.1 ���� : 36355 OTDOA-SignalMeasurementInformation
 �ṹ˵��   : LRRC�ϱ�OTDOA���
*****************************************************************************/
typedef struct
{

    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    LPP_LRRC_MSG_ID_ENUM_UINT32                     enMsgId;                    /*_H2ASN_Skip*/

    LRRC_LPP_OTDOA_TARGET_DEVICE_ERROR_CAUSES_ENUM_UINT16 usError;

    /* 0:����CellGlobalId������Ч��1:����CellGlobalId������Ч */
    LPP_LRRC_INFO_FLAG_ENUM_UINT8                   ucCellGlobalIdFlag;

    /* 0:����OTDOA-MeasQuality������Ч��1:����OTDOA-MeasQuality������Ч */
    LPP_LRRC_INFO_FLAG_ENUM_UINT8                   ucOtdoaMeasqualityFlag;

    VOS_UINT16                                      usSfn;

    /* ȡֵ[0,503] */
    VOS_UINT16                                      usPhyCellIdRef;

    VOS_UINT32                                      ulEarfcn;


    LRRC_LPP_CELL_GLOBAL_ID_INFO_STRU               stCellGlobalIdInfo;

    LRRC_LPP_OTDOA_MEAS_QUALITY_STRU                stReferenceMeasQuality;

    LRRC_LPP_OTDOA_NEIGHBOUR_MEAS_LIST_STRU         stNeighbourMeasurementList;

}LRRC_LPP_OTDOA_MEAS_IND_STRU;

/*****************************************************************************
 �ṹ��    : LppLRrcInterface_MSG
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����
*****************************************************************************/
typedef struct
{
    LPP_LRRC_MSG_ID_ENUM_UINT32                     enMsgID;                    /*_H2ASN_MsgChoice_Export LPP_LRRC_MSG_ID_ENUM_UINT32*/
    VOS_UINT8                                       aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          LPP_LRRC_MSG_ID_ENUM_UINT32
    ****************************************************************************/
}LPP_LRRC_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    LPP_LRRC_MSG_DATA                               stMsgData;
}LppLRrcInterface_MSG;


/*****************************************************************************
  6 OTHERS
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

