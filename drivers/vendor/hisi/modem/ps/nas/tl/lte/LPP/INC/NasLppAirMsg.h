/*******************************************************************************
 * File name:    NasLppAirMsg.h
 * Description:  Lpp模块外部接口消息详细数据结构
                 根据LPP协议(3GPP TS 36.355 V10.5.0 (2012-12))制定
 * Histoty:
                    1. sunbing 49683  2012-12-6 create
*******************************************************************************/
/*******************************************************************************
 * 说明:
 *           1. choice 类型使用1字节(或2字节)来判断，并用宏表示其意义，
 *              所用宏名的后缀为_CHOSEN
 *           2. sequence 类型使用位域来记录可选项的存在与否
 *           3. 若可选项为数组，则用数组长度标识该数组可选与否，不再使用位域方法标识
 *              长度为0表示该项不选，长度不为0表示选中
 *           4. 所有的类型名和宏名采用大写字母来表示，相邻两个单词之间用下划线连接
 *           5. 所有的变量名只采用大小写字母，变量名前缀为小写字母的类型标识符，
 *              每个单词首字母大写，其余字母小写
 *           6. 变量名前缀表示类型如下:
 *                  a      -    array
 *                  g      -    global
 *                  c      -    ASN1_INT8
 *                  s      -    ASN1_INT16
 *                  l      -    ASN1_INT32
 *                  uc     -    ASN1_UINT8
 *                  us     -    ASN1_UINT16
 *                  ul     -    ASN1_UINT32
 *                  ull    -    ASN1_UINT64
 *                  en     -    enum
 *                  un     -    union
 *                  b      -    bool
 *
 *
*******************************************************************************/

#ifndef _NASLPPAIRMSG_H_
#define _NASLPPAIRMSG_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/*******************************************************************************
 *                          需要包含的头文件.
*******************************************************************************/
#include "vos.h"
#include "LppMtaInterface.h"
#include "NasLppAirMsg.h"

/*根据不同产品分别包含不同的宏定义的文件 */
//#include "eNodeB_UuUserMacro.h"
/*******************************************************************************
 *                      字节对齐方式: 一字节对齐.
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

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/

/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/*以下接口是复用了GNSS相关跟AT相关的接口*/
typedef LPP_MTA_COMMON_PLMN_IDENTITY_STRU   LPP_PLMN_IDENTITY_STRU;
typedef LPP_MTA_COMMON_GNSS_SIGNAL_IDS_STRU LPP_GNSS_SIGNAL_IDS_STRU;
typedef LPP_MTA_COMMON_CELL_IDENTITY_STRU   LPP_CELL_IDENTITY_STRU;
typedef LPP_MTA_COMMON_CELL_GLO_EUTRA_UTRA_STRU LPP_CELL_GLO_EUTRA_UTRA_STRU;
typedef LPP_MTA_COMMON_FDD_STRU LPP_FDD_STRU;
typedef LPP_MTA_COMMON_TDD_STRU LPP_TDD_STRU;
typedef LPP_MTA_COMMON_MODE_SELECT_STRU LPP_MODE_SELECT_STRU;
typedef LPP_MTA_COMMON_CELL_GLO_ID_GERAN_STRU LPP_CELL_GLO_ID_GERAN_STRU;
typedef  LPP_MTA_COMMON_SV_ID_STRU  LPP_SV_ID_STRU;
typedef LPP_MTA_COMMON_GNSS_SIGNAL_ID_STRU LPP_GNSS_SIGNAL_ID_STRU;
typedef LPP_MTA_COMMON_GNSS_ID_BITMAP_STRU LPP_GNSS_ID_BITMAP_STRU;
typedef MTA_LPP_GNSS_LOCATION_SERVER_ERROR_CAUSE_STRU LPP_GNSS_LOCATION_SERVER_ERROR_CAUSE_STRU;
typedef MTA_LPP_GNSS_TARGET_DEVICE_ERROR_CAUSE_STRU LPP_GNSS_TARGET_DEVICE_ERROR_CAUSE_STRU;
typedef LPP_MTA_COMMON_GNSS_ERROR_STRU LPP_GNSS_ERROR_STRU;
typedef LPP_MTA_COMMON_ECGI_STRU LPP_ECGI_STRU;
typedef MTA_LPP_ELLIPSOID_POINT_STRU LPP_ELLIPSOID_POINT_STRU;
typedef MTA_LPP_ELLIPSOID_POINT_WITH_UNCERTAINTY_CIRCLE_STRU LPP_ELLIPSOID_POINT_WITH_UNCERTAINTY_CIRCLE_STRU;
typedef MTA_LPP_ELLIPSOID_POINT_WITH_UNCERTAINTY_ELLIPSE_STRU LPP_ELLIPSOID_POINT_WITH_UNCERTAINTY_ELLIPSE_STRU;
typedef MTA_LPP_POLYGON_POINTS_STRU LPP_POLYGON_POINTS_STRU;
typedef MTA_LPP_POLYGON_STRU LPP_POLYGON_STRU;
typedef MTA_LPP_ELLIPSOID_POINT_WITH_ALTITUDE_STRU LPP_ELLIPSOID_POINT_WITH_ALTITUDE_STRU;
typedef MTA_LPP_ELLIPSOID_POINT_WITH_ALTITUDE_AND_UNCERTAINTY_ELLIPSOID_STRU LPP_ELLIPSOID_POINT_WITH_ALTITUDE_AND_UNCERTAINTY_ELLIPSOID_STRU;
typedef MTA_LPP_ELLIPSOIDARC_STRU LPP_ELLIPSOIDARC_STRU;
typedef MTA_LPP_LOCATION_COORDINATE_STRU LPP_LOCATION_COORDINATE_STRU;
typedef MTA_LPP_HORIZONTAL_WITH_VERTICAL_VELOCITY_STRU LPP_HORIZONTAL_WITH_VERTICAL_VELOCITY_STRU;
typedef MTA_LPP_HORIZONTAL_VELCCITY_WITH_UNCERTAINTY_STRU LPP_HORIZONTAL_VELCCITY_WITH_UNCERTAINTY_STRU;
typedef MTA_LPP_HORIZONTAL_WITH_VERTICAL_VELOCITY_AND_UNCERTAINTY_STRU LPP_HORIZONTAL_WITH_VERTICAL_VELOCITY_AND_UNCERTAINTY_STRU;
typedef MTA_LPP_VELOCITY_STRU LPP_VELOCITY_STRU;
typedef MTA_LPP_HORIZONTAL_VELCOCTIY_STRU LPP_HORIZONTAL_VELCOCTIY_STRU;
typedef MTA_LPP_LOCATION_ERROR_STRU LPP_LOCATION_ERROR_STRU;
typedef MTA_LPP_COMMON_IES_PROVIDE_LOCATION_INFO_STRU LPP_COMMON_IES_PROVIDE_LOCATION_INFO_STRU;
typedef LPP_MTA_COMMON_GNSS_ID_STRU LPP_GNSS_ID_STRU;
typedef MTA_LPP_MEAS_REF_TIME_EUTRA  LPP_MEAS_REF_TIME_EUTRA;
typedef MTA_LPP_MEAS_REF_TIME_UTRA LPP_MEAS_REF_TIME_UTRA;
typedef MTA_LPP_REF_FRAME_STRU LPP_REF_FRAME_STRU;
typedef MTA_LPP_MEAS_REF_TIME_GSM LPP_MEAS_REF_TIME_GSM;
typedef MTA_LPP_NET_WORK_TIME_MEAS_REF_STRU LPP_NET_WORK_TIME_MEAS_REF_STRU;
typedef MTA_LPP_MEAS_REF_TIME_STRU LPP_MEAS_REF_TIME_STRU;
typedef MTA_LPP_GNSS_SAT_MEAS_ELEMENT_STRU LPP_GNSS_SAT_MEAS_ELEMENT_STRU;
typedef MTA_LPP_GNSS_SAT_MEAS_LIST_STRU LPP_GNSS_SAT_MEAS_LIST_STRU;
typedef MTA_LPP_GNSS_SGN_MEAS_ELEMENT_STRU LPP_GNSS_SGN_MEAS_ELEMENT_STRU;
typedef MTA_LPP_GNSS_SGN_LIST_STRU LPP_GNSS_SGN_LIST_STRU;
typedef MTA_LPP_GNSS_MEAS_FOR_ONE_GNSS_STRU LPP_GNSS_MEAS_FOR_ONE_GNSS_STRU;
typedef MTA_LPP_GNSS_MEAS_LIST_STRU LPP_GNSS_MEAS_LIST_STRU;
typedef MTA_LPP_GNSS_SIGNAL_MEAS_INFO_STRU LPP_GNSS_SIGNAL_MEAS_INFO_STRU;
typedef MTA_LPP_GNSS_LOCATION_INFO_STRU LPP_GNSS_LOCATION_INFO_STRU;
typedef LPP_MTA_ARFCN_VALUE_EUTRA_STRU LPP_ARFCN_VALUE_EUTRA_STRU;
typedef LPP_MTA_ARFCN_VALUE_EUTRA_V9A0_STRU LPP_ARFCN_VALUE_EUTRA_V9A0_STRU;
typedef LPP_MTA_EUTRA_STRU LPP_EUTRA_STRU;
typedef LPP_MTA_ARFCN_VALUE_UTRA_STRU LPP_ARFCN_VALUE_UTRA_STRU;
typedef LPP_MTA_UTRA_STRU LPP_UTRA_STRU;
typedef LPP_MTA_GSM_STRU LPP_GSM_STRU;
typedef LPP_MTA_CELL_ID_STRU LPP_CELL_ID_STRU;
typedef LPP_MTA_NET_WORK_TIME_STRU LPP_NET_WORK_TIME_STRU;
typedef MTA_LPP_AGNSS_PROVIDE_LOCATION_INFO_STRU LPP_AGNSS_PROVIDE_LOCATION_INFO_STRU;
typedef LPP_MTA_COMMON_TRIGGER_REPORT_CRITERIA_STRU LPP_TRIGGER_REPORT_CRITERIA_STRU;
typedef LPP_MTA_COMMON_PERIODICAL_REPORT_STRU LPP_PERIODICAL_REPORT_STRU;
typedef LPP_MTA_COMMON_HORIZONTAL_ACCURACY_STRU LPP_HORIZONTAL_ACCURACY_STRU;
typedef LPP_MTA_COMMON_VERTICAL_ACCURACY_STRU LPP_VERTICAL_ACCURACY_STRU;
typedef LPP_MTA_COMMON_RESPONSE_TIME_STRU LPP_RESPONSE_TIME_STRU;
typedef LPP_MTA_COMMON_QOS_STRU LPP_QOS_STRU;
typedef LPP_MTA_COMMON_LOCATION_COORDINATE_TYPE_STRU LPP_LOCATION_COORDINATE_TYPE_STRU;
typedef LPP_MTA_COMMON_VELOCITY_TYPE_STRU LPP_VELOCITY_TYPE_STRU;
typedef LPP_MTA_COMMON_IES_REQ_LOCATION_INFO_STRU LPP_COMMON_IES_REQ_LOCATION_INFO_STRU;
typedef LPP_MTA_GNSS_POSITION_INSTRUCTION_STRU LPP_GNSS_POSITION_INSTRUCTION_STRU;
typedef LPP_MTA_AGNSS_REQ_LOCATION_INFO_STRU LPP_AGNSS_REQ_LOCATION_INFO_STRU;
typedef LPP_MTA_GNSS_TIME_MODEL_ELEMENT_STRU LPP_GNSS_TIME_MODEL_ELEMENT_STRU;
typedef LPP_MTA_GNSS_TIME_MODEL_LIST_STRU LPP_GNSS_TIME_MODEL_LIST_STRU;
typedef LPP_MTA_DGNSS_CORRECT_ELEMENT_STRU LPP_DGNSS_CORRECT_ELEMENT_STRU;
typedef LPP_MTA_DGNSS_SAT_LIST_STRU LPP_DGNSS_SAT_LIST_STRU;
typedef LPP_MTA_DGNSS_SGN_TYPE_ELEMENT_STRU LPP_DGNSS_SGN_TYPE_ELEMENT_STRU;
typedef LPP_MTA_DGNSS_SGN_TYPE_LIST_STRU LPP_DGNSS_SGN_TYPE_LIST_STRU;
typedef LPP_MTA_GNSS_DIFF_CORRECT_STRU LPP_GNSS_DIFF_CORRECT_STRU;
typedef LPP_MTA_STANDARD_CLOCK_MODEL_LIST_ELEMENT_STRU LPP_STANDARD_CLOCK_MODEL_LIST_ELEMENT_STRU;
typedef LPP_MTA_STANDARD_CLOCK_MODEL_LIST_STRU LPP_STANDARD_CLOCK_MODEL_LIST_STRU;
typedef LPP_MTA_NAV_CLOCK_MODEL_STRU LPP_NAV_CLOCK_MODEL_STRU;
typedef LPP_MTA_CNAV_CLOCK_MODEL_STRU LPP_CNAV_CLOCK_MODEL_STRU;
typedef LPP_MTA_GLONASS_CLOCK_MODEL_STRU LPP_GLONASS_CLOCK_MODEL_STRU;
typedef LPP_MTA_SBAS_CLOCK_MODEL_STRU LPP_SBAS_CLOCK_MODEL_STRU;
typedef LPP_MTA_GNSS_CLOCK_MODEL_STRU LPP_GNSS_CLOCK_MODEL_STRU;
typedef LPP_MTA_NAV_MODEL_KEPLERIAN_SET_STRU LPP_NAV_MODEL_KEPLERIAN_SET_STRU;
typedef LPP_MTA_EPHEM_SF1_RSVD_STRU LPP_EPHEM_SF1_RSVD_STRU;
typedef LPP_MTA_ADD_NAV_PARAM_STRU LPP_ADD_NAV_PARAM_STRU;
typedef LPP_MTA_NAV_MODEL_CNAV_KEPLERIAN_SET_STRU LPP_NAV_MODEL_CNAV_KEPLERIAN_SET_STRU;
typedef LPP_MTA_NAV_MODEL_NAV_KEPLERIAN_SET_STRU LPP_NAV_MODEL_NAV_KEPLERIAN_SET_STRU;
typedef LPP_MTA_NAV_MODEL_GLONASS_ECEF_STRU LPP_NAV_MODEL_GLONASS_ECEF_STRU;
typedef LPP_MTA_NAV_MODEL_SBAS_STRU LPP_NAV_MODEL_SBAS_STRU;
typedef LPP_MTA_GNSS_ORBIT_MODEL_STRU LPP_GNSS_ORBIT_MODEL_STRU;
typedef LPP_MTA_GNSS_NAV_MODEL_SATELLITE_LIST_ELEMENT_STRU LPP_GNSS_NAV_MODEL_SATELLITE_LIST_ELEMENT_STRU;
typedef LPP_MTA_GNSS_NAV_MODEL_SATELLITE_LIST_STRU LPP_GNSS_NAV_MODEL_SATELLITE_LIST_STRU;
typedef LPP_MTA_GNSS_NAVIGATION_MODEL_STRU LPP_GNSS_NAVIGATION_MODEL_STRU;
typedef LPP_MTA_GNSS_BAD_SIGNAL_ELEMENT_STRU LPP_GNSS_BAD_SIGNAL_ELEMENT_STRU;
typedef LPP_MTA_GNSS_BAD_SIGNAL_LIST_STRU LPP_GNSS_BAD_SIGNAL_LIST_STRU;
typedef LPP_MTA_GNSS_REALTIME_INTERGRITY_STRU LPP_GNSS_REALTIME_INTERGRITY_STRU;
typedef LPP_MTA_GNSS_DATA_BITS_SGN_ELEMENT_STRU LPP_GNSS_DATA_BITS_SGN_ELEMENT_STRU;
typedef LPP_MTA_GNSS_DATA_BITS_SGN_LIST_STRU LPP_GNSS_DATA_BITS_SGN_LIST_STRU;
typedef LPP_MTA_GNSS_DATA_BITS_SAT_ELEMENT_STRU LPP_GNSS_DATA_BITS_SAT_ELEMENT_STRU;
typedef LPP_MTA_GNSS_DATA_BITS_SATLIST_STRU LPP_GNSS_DATA_BITS_SATLIST_STRU;
typedef LPP_MTA_GNSS_DATA_BIT_ASSIST_STRU LPP_GNSS_DATA_BIT_ASSIST_STRU;
typedef LPP_MTA_GNSS_ACQUISIT_ASSIST_ELEMENT_STRU LPP_GNSS_ACQUISIT_ASSIST_ELEMENT_STRU;
typedef LPP_MTA_GNSS_ACQUISIT_ASSIST_LIST_STRU LPP_GNSS_ACQUISIT_ASSIST_LIST_STRU;
typedef LPP_MTA_GNSS_ACQUISIT_ASSIST_STRU LPP_GNSS_ACQUISIT_ASSIST_STRU;
typedef LPP_MTA_ALMANAC_KEPLERIAN_SET_STRU LPP_ALMANAC_KEPLERIAN_SET_STRU;
typedef LPP_MTA_ALMANAC_NAV_KEPLERIAN_SET_STRU LPP_ALMANAC_NAV_KEPLERIAN_SET_STRU;
typedef LPP_MTA_ALMANAC_REDUCED_KEPLERIAN_SET_STRU LPP_ALMANAC_REDUCED_KEPLERIAN_SET_STRU;
typedef LPP_MTA_ALMANAC_MIDI_ALMANAC_STRU LPP_ALMANAC_MIDI_ALMANAC_STRU;
typedef LPP_MTA_ALMANAC_GLONASS_ALMANAC_SET_STRU LPP_ALMANAC_GLONASS_ALMANAC_SET_STRU;
typedef LPP_MTA_ALMANAC_ECEF_SBAS_ALMANAC_STRU LPP_ALMANAC_ECEF_SBAS_ALMANAC_STRU;
typedef LPP_MTA_GNSS_ALMANAC_ELEMENT_STRU LPP_GNSS_ALMANAC_ELEMENT_STRU;
typedef LPP_MTA_GNSS_ALMANAC_LIST_STRU LPP_GNSS_ALMANAC_LIST_STRU;
typedef LPP_MTA_GNSS_ALMANAC_STRU LPP_GNSS_ALMANAC_STRU;
typedef LPP_MTA_UTC_MODEL_SET1_STRU LPP_UTC_MODEL_SET1_STRU;
typedef LPP_MTA_UTC_MODEL_SET2_STRU LPP_UTC_MODEL_SET2_STRU;
typedef LPP_MTA_UTC_MODEL_SET3_STRU LPP_UTC_MODEL_SET3_STRU;
typedef LPP_MTA_UTC_MODEL_SET4_STRU LPP_UTC_MODEL_SET4_STRU;
typedef LPP_MTA_GNSS_UTC_MODEL_STRU LPP_GNSS_UTC_MODEL_STRU;
typedef LPP_MTA_GNSS_ID_GLONASS_SAT_ELEMENT_STRU LPP_GNSS_ID_GLONASS_SAT_ELEMENT_STRU;
typedef LPP_MTA_GNSS_ID_GLONASS_STRU LPP_GNSS_ID_GLONASS_STRU;
typedef LPP_MTA_GNSS_ID_GPS_SAT_ELEMENT_STRU LPP_GNSS_ID_GPS_SAT_ELEMENT_STRU;
typedef LPP_MTA_GNSS_ID_GPS_STRU LPP_GNSS_ID_GPS_STRU;
typedef LPP_MTA_GNSS_AUX_INFO_STRU LPP_GNSS_AUX_INFO_STRU;
typedef LPP_MTA_COMMON_SBAS_IDS_STRU LPP_SBAS_IDS_STRU;
typedef LPP_MTA_COMMON_SBAS_ID_STRU LPP_SBAS_ID_STRU;
typedef LPP_MTA_GNSS_GENERIC_ASSIST_DATA_ELEMENT_STRU LPP_GNSS_GENERIC_ASSIST_DATA_ELEMENT_STRU;
typedef LPP_MTA_GNSS_GENERIC_ASSIST_DATA_STRU LPP_GNSS_GENERIC_ASSIST_DATA_STRU;
typedef LPP_MTA_GPS_TOW_ASSIST_ELEMENT_STRU LPP_GPS_TOW_ASSIST_ELEMENT_STRU;
typedef LPP_MTA_GPS_TOW_ASSIST_STRU LPP_GPS_TOW_ASSIST_STRU;
typedef LPP_MTA_GNSS_SYSTEM_TIME_STRU LPP_GNSS_SYSTEM_TIME_STRU;
typedef LPP_MTA_GNSS_REFERENCE_TIME_FOR_CELL_STRU LPP_GNSS_REFERENCE_TIME_FOR_CELL_STRU;
typedef LPP_MTA_GNSS_REFERENCE_TIME_STRU LPP_GNSS_REFERENCE_TIME_STRU;
typedef LPP_MTA_ELLIP_POINT_WITH_ALTITUDE_UNCERTAIN_ELLIPSOID_STRU LPP_ELLIP_POINT_WITH_ALTITUDE_UNCERTAIN_ELLIPSOID_STRU;
typedef LPP_MTA_GNSS_REFERENCE_LOCATION_STRU LPP_GNSS_REFERENCE_LOCATION_STRU;
typedef LPP_MTA_KLOBUCHAR_MODEL_PARAMTER_STRU LPP_KLOBUCHAR_MODEL_PARAMTER_STRU;
typedef LPP_MTA_NEQUICK_MODEL_PARAMETER_STRU LPP_NEQUICK_MODEL_PARAMETER_STRU;
typedef LPP_MTA_GNSS_IONOSPHERIC_MODEL_STRU LPP_GNSS_IONOSPHERIC_MODEL_STRU;
typedef LPP_MTA_GNSS_EARTH_ORIENTATION_PARAMETERS_STRU LPP_GNSS_EARTH_ORIENTATION_PARAMETERS_STRU;
typedef LPP_MTA_GNSS_COMMON_ASSIST_DATA_STRU LPP_GNSS_COMMON_ASSIST_DATA_STRU;
typedef LPP_MTA_AGNSS_PROVIDE_ASSIST_DATA_STRU LPP_AGNSS_PROVIDE_ASSIST_DATA_STRU;
typedef MTA_LPP_GNSS_TIME_MODEL_ELEMENT_REQ_STRU LPP_GNSS_TIME_MODEL_ELEMENT_REQ_STRU;
typedef MTA_LPP_GNSS_TIME_MODEL_LIST_REQ_STRU LPP_GNSS_TIME_MODEL_LIST_REQ_STRU;
typedef MTA_LPP_GNSS_DIFF_CORRECT_REQ_STRU LPP_GNSS_DIFF_CORRECT_REQ_STRU;
typedef MTA_LPP_SATLIST_RELATED_DATALIST_ELEMENT_STRU LPP_SATLIST_RELATED_DATALIST_ELEMENT_STRU;
typedef MTA_LPP_SATLIST_RELATED_DATALIST_STRU LPP_SATLIST_RELATED_DATALIST_STRU;
typedef MTA_LPP_STORED_NAVLIST_STRU LPP_STORED_NAVLIST_STRU;
typedef LPP_MTA_COMMON_CLOCK_MODEL_ID_STRU LPP_CLOCK_MODEL_ID_STRU;
typedef LPP_MTA_COMMON_ORBIT_MODEL_ID_STRU LPP_ORBIT_MODEL_ID_STRU;
typedef MTA_LPP_REQ_NAVLIST_STRU LPP_REQ_NAVLIST_STRU;
typedef MTA_LPP_GNSS_NAVIGATION_MODEL_REQ_STRU LPP_GNSS_NAVIGATION_MODEL_REQ_STRU;
typedef MTA_LPP_GNSS_REALTIME_INTERGRITY_REQ_STRU LPP_GNSS_REALTIME_INTERGRITY_REQ_STRU;
typedef MTA_LPP_GNSS_DATA_BIT_REQ_SAT_ELEMENT_STRU LPP_GNSS_DATA_BIT_REQ_SAT_ELEMENT_STRU;
typedef MTA_LPP_GNSS_DATA_BIT_REQ_SAT_LIST_STRU LPP_GNSS_DATA_BIT_REQ_SAT_LIST_STRU;
typedef MTA_LPP_GNSS_DATA_BIT_ASSIST_REQ_STRU LPP_GNSS_DATA_BIT_ASSIST_REQ_STRU;
typedef MTA_LPP_GNSS_ACQUISIT_ASSIST_REQ_STRU LPP_GNSS_ACQUISIT_ASSIST_REQ_STRU;
typedef MTA_LPP_GNSS_ALMANAC_REQ_STRU LPP_GNSS_ALMANAC_REQ_STRU;
typedef MTA_LPP_GNSS_UTC_MODEL_REQ_STRU LPP_GNSS_UTC_MODEL_REQ_STRU;
typedef MTA_LPP_GNSS_AUX_INFO_REQ_STRU LPP_GNSS_AUX_INFO_REQ_STRU;
typedef MTA_LPP_GNSS_GENERIC_ASSIST_DATA_REQ_ELEMENT_STRU LPP_GNSS_GENERIC_ASSIST_DATA_REQ_ELEMENT_STRU;
typedef MTA_LPP_GNSS_GENERIC_ASSIST_DATA_REQ_STRU LPP_GNSS_GENERIC_ASSIST_DATA_REQ_STRU;
typedef MTA_LPP_GNSS_REFERENCE_TIME_REQ_STRU LPP_GNSS_REFERENCE_TIME_REQ_STRU;
typedef MTA_LPP_GNSS_REFERENCE_LOCATION_REQ_STRU LPP_GNSS_REFERENCE_LOCATION_REQ_STRU;
typedef MTA_LPP_GNSS_IONOSPHERIC_MODEL_REQ_STRU LPP_GNSS_IONOSPHERIC_MODEL_REQ_STRU;
typedef MTA_LPP_GNSS_EARTH_ORIENTATION_PARAMETERS_REQ_STRU LPP_GNSS_EARTH_ORIENTATION_PARAMETERS_REQ_STRU;
typedef MTA_LPP_GNSS_COMMON_ASSIST_DATA_REQ_STRU LPP_GNSS_COMMON_ASSIST_DATA_REQ_STRU;
typedef MTA_LPP_AGNSS_REQ_ASSIST_DATA_STRU LPP_AGNSS_REQ_ASSIST_DATA_STRU;
typedef LPP_MTA_COMMON_ACCESS_TYPES_STRU LPP_ACCESS_TYPES_STRU;
typedef LPP_MTA_COMMON_POSITIONING_MODES_STRU LPP_POSITIONING_MODES_STRU;
typedef MTA_LPP_FTA_MEAS_SUPPORT_STRU LPP_FTA_MEAS_SUPPORT_STRU;
typedef MTA_LPP_GNSS_SUPPORT_ELEMENT_STRU LPP_GNSS_SUPPORT_ELEMENT_STRU;
typedef MTA_LPP_GNSS_SUPPORT_LIST_STRU LPP_GNSS_SUPPORT_LIST_STRU;
typedef MTA_LPP_GNSS_REFERENCE_TIME_SUPPORT_STRU LPP_GNSS_REFERENCE_TIME_SUPPORT_STRU;
typedef MTA_LPP_GNSS_REFERENCE_LOCATION_SUPPORT_STRU LPP_GNSS_REFERENCE_LOCATION_SUPPORT_STRU;
typedef MTA_LPP_GNSS_IONOSPHERIC_MODE_SUPPORT_STRU LPP_GNSS_IONOSPHERIC_MODE_SUPPORT_STRU;
typedef MTA_LPP_GNSS_EARTH_ORIENTATION_PARAMETERS_SUPPORT_STRU LPP_GNSS_EARTH_ORIENTATION_PARAMETERS_SUPPORT_STRU;
typedef MTA_LPP_GNSS_COMMON_ASSISTANCE_DATA_SUPPORT_STRU LPP_GNSS_COMMON_ASSISTANCE_DATA_SUPPORT_STRU;
typedef MTA_LPP_GNSS_TIME_MODE_LIST_SUPPORT_STRU LPP_GNSS_TIME_MODE_LIST_SUPPORT_STRU;
typedef MTA_LPP_GNSS_DIFFERENTIAL_CORRECTIONS_SUPPORT_STRU LPP_GNSS_DIFFERENTIAL_CORRECTIONS_SUPPORT_STRU;
typedef MTA_LPP_CLOCK_MODEL_STRU LPP_CLOCK_MODEL_STRU;
typedef MTA_LPP_ORBIT_MODEL_STRU LPP_ORBIT_MODEL_STRU;
typedef MTA_LPP_GNSS_NAVIGATION_MODE_SUPPORT_STRU LPP_GNSS_NAVIGATION_MODE_SUPPORT_STRU;
typedef MTA_LPP_GNSS_REAL_TIME_INTEGRITY_SUPPORT_STRU LPP_GNSS_REAL_TIME_INTEGRITY_SUPPORT_STRU;
typedef MTA_LPP_GNSS_DATA_BIT_ASSISTANCE_SUPPORT_STRU LPP_GNSS_DATA_BIT_ASSISTANCE_SUPPORT_STRU;
typedef MTA_LPP_GNSS_ACQUISITION_ASSISTANCE_SUPPORT_STRU  LPP_GNSS_ACQUISITION_ASSISTANCE_SUPPORT_STRU;
typedef MTA_LPP_ALMANAC_MODEL_STRU LPP_ALMANAC_MODEL_STRU;
typedef MTA_LPP_GNSS_ALMANAC_SUPPORT_STRU LPP_GNSS_ALMANAC_SUPPORT_STRU;
typedef MTA_LPP_UTC_MODEL_STRU LPP_UTC_MODEL_STRU;
typedef MTA_LPP_GNSS_UTC_MODEL_SUPPORT_STRU LPP_GNSS_UTC_MODEL_SUPPORT_STRU;
typedef MTA_LPP_GNSS_AUXILIARY_INFORMATION_SUPPORT_STRU LPP_GNSS_AUXILIARY_INFORMATION_SUPPORT_STRU;
typedef MTA_LPP_GNSS_GENERIC_ASSISTANCE_DATA_SUPPORT_ELEMENT_STRU LPP_GNSS_GENERIC_ASSISTANCE_DATA_SUPPORT_ELEMENT_STRU;
typedef MTA_LPP_GNSS_GENERIC_ASSISTANCE_DATA_SUPPORT_STRU LPP_GNSS_GENERIC_ASSISTANCE_DATA_SUPPORT_STRU;
typedef MTA_LPP_ASSISTANCE_DATA_SUPPORT_LIST_STRU LPP_ASSISTANCE_DATA_SUPPORT_LIST_STRU;
typedef MTA_LPP_VELOCITY_TYPES_STRU LPP_VELOCITY_TYPES_STRU;
typedef MTA_LPP_AGNSS_PROVIDE_CAP_STRU LPP_AGNSS_PROVIDE_CAP_STRU;
typedef LPP_MTA_GNSS_CAP_REQ_STRU LPP_AGNSS_REQ_CAP_STRU;

/*******************************************************************************
 结构名    : LPP_EPDU_IDENTIFIER_STRU
 结构说明  : epdu identifier
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    /*
    EPDU-ID ::= INTEGER (1..256)

    EPDU-Name ::= VisibleString (SIZE (1..32))
    */
    VOS_UINT32                          bitOpEpduIdentifierExt   : 1;
    VOS_UINT32                          bitOpEpduName   : 1;
    VOS_UINT32                          bitOpSpare      : 30;

    VOS_UINT32                          ulEpduId;
    VOS_UINT32                          ulEpduNameLength;
    VOS_UINT8                           acEpduName[LPP_MAX_EPDU_NAME_LEN];
}LPP_EPDU_IDENTIFIER_STRU;

/*******************************************************************************
 结构名    : LPP_EPDU_BODY_STRU
 结构说明  : EPDU-Body
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    /*EPDU-Body ::= OCTET STRING*/
    VOS_UINT32                          ulBodyLen;
    VOS_UINT8                           aucBodyData[LPP_MAX_EPDU_BODY_LEN];
}LPP_EPDU_BODY_STRU;

/*******************************************************************************
 结构名    : LPP_EPDU_STRU
 结构说明  : EPDU
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    /*
    EPDU ::= SEQUENCE {
        ePDU-Identifier         EPDU-Identifier,
        ePDU-Body               EPDU-Body
    }
    */
    LPP_EPDU_IDENTIFIER_STRU            stEpduIdentifier;
    LPP_EPDU_BODY_STRU                  stEpduBody;
}LPP_EPDU_STRU;

/*******************************************************************************
 结构名    : LPP_EPDU_SEQUENCE_STRU
 结构说明  : EPDU_SEQUENCE
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    VOS_UINT32                          ulEpduNum;
    LPP_EPDU_STRU                       astEpduArray[LPP_MAX_EPDU_NUM];
}LPP_EPDU_SEQUENCE_STRU;

/*******************************************************************************
 结构名    : LPP_OTDOA_LOCATION_SERVER_ERROR_CAUSE_STRU
 结构说明  : OTDOA-LocationServerErrorCauses
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    /*
    OTDOA-LocationServerErrorCauses ::= SEQUENCE {
        cause       ENUMERATED  {   undefined,
                                    assistanceDataNotSupportedByServer,
                                    assistanceDataSupportedButCurrentlyNotAvailableByServer,
                                    ...
                                },
        ...
    }*/
    VOS_UINT32                                              bitOpOtdoaLocationServerErrorCauseExt:1;
    VOS_UINT32                                              bitOpSpare:31;
    LPP_OTDOA_LOCATION_SERVER_ERROR_CAUSE_ENUM_UINT8        enOtdoaLocationServerErrorCause;
    VOS_UINT8                                               aucRsv[3];
}LPP_OTDOA_LOCATION_SERVER_ERROR_CAUSE_STRU;

/*******************************************************************************
 结构名    : LPP_OTDOA_TARGET_DEVICE_ERROR_CAUSE_STRU
 结构说明  : OTDOA-TargetDeviceErrorCauses
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    /*
    OTDOA-TargetDeviceErrorCauses ::= SEQUENCE {
        cause       ENUMERATED {    undefined,
                                    assistance-data-missing,
                                    unableToMeasureReferenceCell,
                                    unableToMeasureAnyNeighbourCell,
                                    attemptedButUnableToMeasureSomeNeighbourCells,
                                    ...
                                },
        ...
    }
    */
    VOS_UINT32                                                      bitOpOtdoaTargetDeviceErrorCauseExt:1;
    VOS_UINT32                                                      bitOpSpare:31;
    LPP_OTDOA_LOCATION_TARGET_DEVICE_ERROR_CAUSE_ENUM_UINT32        enOtoaTargetDeviceErrorCause;
    VOS_UINT8                                                       aucRsv[3];
}LPP_OTDOA_TARGET_DEVICE_ERROR_CAUSE_STRU;

/*******************************************************************************
 结构名    : LPP_OTDOA_ERROR_STRU
 结构说明  : OTDOA-Error
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    /*
    OTDOA-Error ::= CHOICE {
        locationServerErrorCauses       OTDOA-LocationServerErrorCauses,
        targetDeviceErrorCauses         OTDOA-TargetDeviceErrorCauses,
        ...
    }
    */
    VOS_UINT32                                          bitOpOtdoaErrorExt:1;
    VOS_UINT32                                          bitOpSpare:31;
    VOS_UINT32                                          ulChoice;

    #define           LPP_OTDOA_LOCATION_SERVER_ERROR_CAUSE_CHOSEN        0
    #define           LPP_OTDOA_TARGET_DEVICE_ERROR_CAUSE_CHOSEN          1

    union
    {
       LPP_OTDOA_LOCATION_SERVER_ERROR_CAUSE_STRU             stLocationServerErrorCauses;
       LPP_OTDOA_TARGET_DEVICE_ERROR_CAUSE_STRU               stTargetDeviceErrorCauses;
    }u;
}LPP_OTDOA_ERROR_STRU;

/*******************************************************************************
 结构名    : LPP_TRANSACTION_ID_STRU
 结构说明  : LPP-TransactionID
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    /*
    LPP-TransactionID ::= SEQUENCE {
        initiator               Initiator,
        transactionNumber       TransactionNumber,
        ...
    }
    */

    VOS_UINT32                      bitOpTransactionIDExt:1;
    VOS_UINT32                      bitOpSpare:31;

    LPP_INITIATOR_TYPE_ENUM_UINT8       enInitiator;
    VOS_UINT8                           ucTransactionNumber;
    VOS_UINT8                           aucRes[2];
}LPP_TRANSACTION_ID_STRU;

/*******************************************************************************
 结构名    : LPP_SEQUENCE_NUMBER_STRU
 结构说明  : SequenceNumber
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    /*
    SequenceNumber ::= INTEGER (0..255)
    */
    VOS_UINT8                           ucSequenceNumber;
    VOS_UINT8                           aucRes[3];
}LPP_SEQUENCE_NUMBER_STRU;

/*******************************************************************************
 结构名    : LPP_ACKNOWLEDGEMENT_STRU
 结构说明  : Acknowledgement
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    /*
    Acknowledgement ::= SEQUENCE {
        ackRequested    BOOLEAN,
        ackIndicator    SequenceNumber      OPTIONAL
    }
    */
    VOS_UINT32                          bitOpAckIndicator:1;
    VOS_UINT32                          bitOpSpare:31;

    VOS_BOOL                            bAckRequested;
    LPP_SEQUENCE_NUMBER_STRU            stAckIndicator;
}LPP_ACKNOWLEDGEMENT_STRU;

/*******************************************************************************
 结构名    : LPP_COMMON_IES_ERROR_STRU
 结构说明  : CommonIEsError
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    /*
    CommonIEsError ::= SEQUENCE {
        errorCause      ENUMERATED {
            undefined,
            lppMessageHeaderError,
            lppMessageBodyError,
            epduError,
            incorrectDataValue,
            ...
        }
    }
    */
    VOS_UINT32                          bitOpCommonIEsErrorExt:1;
    VOS_UINT32                          bitOpSpare:31;

    LPP_COMMON_IES_ERROR_ENUM_UINT8     enCommonIesErrorCasue;
    VOS_UINT8                           aucRsv[3];
}LPP_COMMON_IES_ERROR_STRU;

/*******************************************************************************
 结构名    : LPP_ERROR_R9_STRU
 结构说明  : Error-r9-IEs
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    /*
    Error-r9-IEs ::= SEQUENCE {
        commonIEsError      CommonIEsError          OPTIONAL,   -- Need ON
        ...,
        epdu-Error          EPDU-Sequence           OPTIONAL    -- Need ON
    }
    */
    VOS_UINT32                      bitOpErrorR9IEsExt:1;
    VOS_UINT32                      bitOpCommonIesError:1;
    VOS_UINT32                      bitOpEpduError:1;
    VOS_UINT32                      bitOpSpare:29;

    LPP_COMMON_IES_ERROR_STRU       stCommonIesError;
    LPP_EPDU_SEQUENCE_STRU          stEpduError;
}LPP_ERROR_R9_STRU;

/*******************************************************************************
 结构名    : LPP_MESSAGE_ERROR_STRU
 结构说明  : Error
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    /*
    Error ::= CHOICE {
        error-r9                    Error-r9-IEs,
        criticalExtensionsFuture    SEQUENCE {}
    }
    */
    VOS_UINT32                                          ulChoice;

    #define           LPP_ERROR_R9_IES_CHOSEN                0
    #define           LPP_ERROR_EXT_FUTURE_CHOSEN            1

     union
     {
        LPP_ERROR_R9_STRU                               stErrorR9;
        VOS_UINT8                                       ucCritiExtFuture;
     }u;
}LPP_MESSAGE_ERROR_STRU;


/*******************************************************************************
 结构名    : LPP_COMMON_IES_ABORT_STRU
 结构说明  : CommonIEsAbort
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    /*
    CommonIEsAbort ::= SEQUENCE {
        abortCause          ENUMERATED {
            undefined,
            stopPeriodicReporting,
            targetDeviceAbort,
            networkAbort,
            ...
        }
    }
    */
    VOS_UINT32                              bitOpCommonIEsAbortExt:1;
    VOS_UINT32                              bitOpSpare:31;

    LPP_COMMON_IES_ABORT_ENUM_UINT8         enCommonIesAbortCasue;
    VOS_UINT8                               aucRsv[3];
}LPP_COMMON_IES_ABORT_STRU;

/*******************************************************************************
 结构名    : LPP_ABORT_R9_IES_STRU
 结构说明  : Abort-r9-IEs
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/

typedef struct
{
    /*
    Abort-r9-IEs ::= SEQUENCE {
        commonIEsAbort      CommonIEsAbort          OPTIONAL,   -- Need ON
        ...,
        epdu-Abort          EPDU-Sequence           OPTIONAL    -- Need ON
    }
    */
    VOS_UINT32                  bitOpAbortR9IEsExt:1;
    VOS_UINT32                  bitOpCommonIesAbort:1;
    VOS_UINT32                  bitOpEpduAbort:1;
    VOS_UINT32                  bitOpSpare:29;

    LPP_COMMON_IES_ABORT_STRU   stCommonIesAbort;
    LPP_EPDU_SEQUENCE_STRU      stEpduAbort;
}LPP_ABORT_R9_IES_STRU;

/*******************************************************************************
 结构名    : LPP_C1_EXT_ABORT_STRU
 结构说明  :
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/

typedef struct
{
    VOS_UINT32                                          ulChoice;

    #define         LPP_C1_CRITI_EXT_ABORT_R9_CHOSEN              0
    #define         LPP_SPARE3_C1_CRITI_EXT_ABORT_CHOSEN          1
    #define         LPP_SPARE2_C1_CRITI_EXT_ABORT_CHOSEN          2
    #define         LPP_SPARE1_C1_CRITI_EXT_ABORT_CHOSEN          3

    union
    {
        LPP_ABORT_R9_IES_STRU                               stAbortR9;
        VOS_UINT8                                           ucSpare3;
        VOS_UINT8                                           ucSpare2;
        VOS_UINT8                                           ucSpare1;
    }u;
}LPP_C1_EXT_ABORT_STRU;

/*******************************************************************************
 结构名    : LPP_CRIT_EXT_ABORT_STRU
 结构说明  :
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct

{
    VOS_UINT32                                          ulChoice;

    #define         LPP_CRITI_EXT_ABORT_CHOSEN                      0
    #define         LPP_CRITI_EXT_ABORT_FUTURE_CHOSEN                1


    union
    {
        LPP_C1_EXT_ABORT_STRU                               stAbortExtC1;
        VOS_UINT8                                           ucCritiExtFutue;
    }u;
}LPP_CRIT_EXT_ABORT_STRU;

/*******************************************************************************
 结构名    : LPP_MESSAGE_ABORT_STRU
 结构说明  : Abort
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    /*
    Abort ::= SEQUENCE {
        criticalExtensions      CHOICE {
            c1                      CHOICE {
                abort-r9        Abort-r9-IEs,
                spare3 NULL, spare2 NULL, spare1 NULL
            },
            criticalExtensionsFuture    SEQUENCE {}
        }
    }
    */

        LPP_CRIT_EXT_ABORT_STRU                        stC1;

}LPP_MESSAGE_ABORT_STRU;

/*******************************************************************************
 结构名    : LPP_OTDOA_MEAS_QUALITY_STRU
 结构说明  : OTDOA-MeasQuality
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    /*
    OTDOA-MeasQuality ::= SEQUENCE {
        error-Resolution        BIT STRING (SIZE (2)),
        error-Value             BIT STRING (SIZE (5)),
        error-NumSamples        BIT STRING (SIZE (3))               OPTIONAL,
        ...
    }
    */
    VOS_UINT32                      bitOpOtdoaMeasQualityExt:1;
    VOS_UINT32                      bitOpErrorNumSampiles:1;
    VOS_UINT32                      bitOpSpare:30;


    VOS_UINT8                       ucErrorResolution; /*FIXME LIFUXIN*/
    VOS_UINT8                       ucErrorValuse;
    VOS_UINT8                       ucErrorNumSamples;
    VOS_UINT8                       ucRes;
}LPP_OTDOA_MEAS_QUALITY_STRU;

/*******************************************************************************
 结构名    : LPP_NEIGHBOUR_MEAS_ELEMENT_STRU
 结构说明  : NeighbourMeasurementElement
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    /*
    NeighbourMeasurementElement ::= SEQUENCE {
        physCellIdNeighbor      INTEGER (0..503),
        cellGlobalIdNeighbour   ECGI                    OPTIONAL,
        earfcnNeighbour         ARFCN-ValueEUTRA        OPTIONAL,       -- Cond NotSameAsRef2
        rstd                    INTEGER (0..12711),
        rstd-Quality            OTDOA-MeasQuality,
        ...,
        [[ earfcnNeighbour-v9a0 ARFCN-ValueEUTRA-v9a0   OPTIONAL        -- Cond NotSameAsRef3
        ]]
    }
    */
    VOS_UINT32                          bitOpNeighbourMeasElementExt:1;
    VOS_UINT32                          bitOpCellGlobalIdNeighbour:1;
    VOS_UINT32                          bitOpArfcnValueEutra:1;
    VOS_UINT32                          bitOpArfcnValueEutraV9a0:1;
    VOS_UINT32                          bitOpSpare:30;

    VOS_UINT32                          ulPhysCellIdNeighbor;
    LPP_ECGI_STRU                       stCellGlobalIdNeighbour;
    LPP_ARFCN_VALUE_EUTRA_STRU          stEarfcnNeighbour;
    VOS_UINT32                          ulRstd;
    LPP_OTDOA_MEAS_QUALITY_STRU         stRstdQuality;
    LPP_ARFCN_VALUE_EUTRA_V9A0_STRU     stEarfcnNeighbourV9a0;
}LPP_NEIGHBOUR_MEAS_ELEMENT_STRU;

/*******************************************************************************
 结构名    : LPP_NEIGHBOUR_MEAS_LIST_STRU
 结构说明  : NeighbourMeasurementList
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    /*
    NeighbourMeasurementList ::= SEQUENCE (SIZE(1..24)) OF NeighbourMeasurementElement
    */
    VOS_UINT32                              ulNeighbourMeasListCnt;
    LPP_NEIGHBOUR_MEAS_ELEMENT_STRU         astNeighbourMeasListArray[LPP_MAX_NEIGHBOUR_MEAS_ELEMENT_LEN];
}LPP_NEIGHBOUR_MEAS_LIST_STRU;

/*******************************************************************************
 结构名    : LPP_OTDOA_SIGNAL_MEAS_INFO_STRU
 结构说明  : OTDOA-SignalMeasurementInformation
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    /*
    OTDOA-SignalMeasurementInformation ::= SEQUENCE {
        systemFrameNumber       BIT STRING (SIZE (10)),
        physCellIdRef           INTEGER (0..503),
        cellGlobalIdRef         ECGI                    OPTIONAL,
        earfcnRef               ARFCN-ValueEUTRA        OPTIONAL,       -- Cond NotSameAsRef0
        referenceQuality        OTDOA-MeasQuality       OPTIONAL,
        neighbourMeasurementList    NeighbourMeasurementList,
        ...,
        [[ earfcnRef-v9a0       ARFCN-ValueEUTRA-v9a0   OPTIONAL        -- Cond NotSameAsRef1
        ]]
    }
    */
    VOS_UINT32                          bitOpOtdoaSignalMeasInfoExt:1;
    VOS_UINT32                          bitOpCellGlobalIdRef:1;
    VOS_UINT32                          bitOpArfcnValueEutra:1;
    VOS_UINT32                          bitOpRefQuality:1;
    VOS_UINT32                          bitOpArfcnValueEutraV9a0:1;
    VOS_UINT32                          bitOpSpare:27;

    VOS_UINT16                          usSystemFrameNumber;
    VOS_UINT16                          usPhysCellIdRef;
    LPP_ECGI_STRU                       stCellGlobalIdRef;
    LPP_ARFCN_VALUE_EUTRA_STRU          stEarfcnRef;
    LPP_OTDOA_MEAS_QUALITY_STRU         stReferenceQuality;/*edited by wangensheng,missing object*/
    LPP_NEIGHBOUR_MEAS_LIST_STRU        stNeighbourMeasList;
    LPP_ARFCN_VALUE_EUTRA_V9A0_STRU     stEarfcnRefV9a0;
}LPP_OTDOA_SIGNAL_MEAS_INFO_STRU;

/*******************************************************************************
 结构名    : LPP_OTDOA_PROVIDE_LOCATION_INFO_STRU
 结构说明  : OTDOA-ProvideLocationInformation
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    /*
    OTDOA-ProvideLocationInformation ::= SEQUENCE {
        otdoaSignalMeasurementInformation   OTDOA-SignalMeasurementInformation  OPTIONAL,
        otdoa-Error                         OTDOA-Error                         OPTIONAL,
        ...
    }
    */
    VOS_UINT32                              bitOpOtdoaProvideLocationInfoExt:1;
    VOS_UINT32                              bitOpOtdoaSignalMeasInfo:1;
    VOS_UINT32                              bitOpOtdoaError:1;
    VOS_UINT32                              bitOpSpare:29;

    LPP_OTDOA_SIGNAL_MEAS_INFO_STRU         stOtdoaSignalMeasInfo;
    LPP_OTDOA_ERROR_STRU                    stOtdoaError;
}LPP_OTDOA_PROVIDE_LOCATION_INFO_STRU;

/*******************************************************************************
 结构名    : LPP_MEAS_RESULT_ELEMENT_STRU
 结构说明  : MeasuredResultsElement
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    /*
    MeasuredResultsElement ::= SEQUENCE {
        physCellId      INTEGER (0..503),
        cellGlobalId    CellGlobalIdEUTRA-AndUTRA           OPTIONAL,
        arfcnEUTRA      ARFCN-ValueEUTRA,
        systemFrameNumber
                        BIT STRING (SIZE (10))              OPTIONAL,
        rsrp-Result     INTEGER (0..97)                     OPTIONAL,
        rsrq-Result     INTEGER (0..34)                     OPTIONAL,
        ue-RxTxTimeDiff INTEGER (0..4095)                   OPTIONAL,
        ...,
        [[ arfcnEUTRA-v9a0      ARFCN-ValueEUTRA-v9a0       OPTIONAL        -- Cond EARFCN-max
        ]]
    }
    */
    VOS_UINT32                          bitOpMeasResultElementExt:1;
    VOS_UINT32                          bitOpCellGlobalId:1;
    VOS_UINT32                          bitOpSystemFrameNumber:1;
    VOS_UINT32                          bitOpRsrpResult:1;
    VOS_UINT32                          bitOpRsrqResult:1;
    VOS_UINT32                          bitOpUeRxTxTimeDiff:1;
    VOS_UINT32                          bitOpArfcnEutraV9a0:1;
    VOS_UINT32                          bitOpSpare:25;

    VOS_UINT32                          ulPhyCellId;
    LPP_CELL_GLO_EUTRA_UTRA_STRU        stCellGloId;
    LPP_ARFCN_VALUE_EUTRA_STRU          stArfcnEutra;
    VOS_UINT16                          usSystemFrameNumber;
    VOS_UINT8                           ucRsrpResult;
    VOS_UINT8                           ucRsrqResult;
    VOS_UINT32                          ulUeRxTxTimeDiff;
    LPP_ARFCN_VALUE_EUTRA_V9A0_STRU     stArfcnEutraV9a0;
}LPP_MEAS_RESULT_ELEMENT_STRU;

/*******************************************************************************
 结构名    : LPP_MEAS_RESULT_LIST_STRU
 结构说明  : MeasuredResultsList
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    /*
    MeasuredResultsList ::= SEQUENCE (SIZE(1..32)) OF MeasuredResultsElement
    */
    VOS_UINT32                          ulMeasResultsListCnt;
    LPP_MEAS_RESULT_ELEMENT_STRU        astMeasResultsList[LPP_MAX_MEAS_RSLT_ELMENT_LEN];
}LPP_MEAS_RESULT_LIST_STRU;

/*******************************************************************************
 结构名    : LPP_ECID_SIGNAL_MEAS_INFO_STRU
 结构说明  : ECID-SignalMeasurementInformation
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    /*
    ECID-SignalMeasurementInformation ::= SEQUENCE {
        primaryCellMeasuredResults  MeasuredResultsElement  OPTIONAL,
        measuredResultsList         MeasuredResultsList,
        ...
    }
    */
    VOS_UINT32                          bitOpEcidSignalMeasInfoExt:1;
    VOS_UINT32                          bitOpPrimaryCellMeasRslt:1;
    VOS_UINT32                          bitOpSpare:30;

    LPP_MEAS_RESULT_ELEMENT_STRU        stPrimaryCellMeasResult;
    LPP_MEAS_RESULT_LIST_STRU           stMeasResultList;
}LPP_ECID_SIGNAL_MEAS_INFO_STRU;

/*******************************************************************************
 结构名    : LPP_ECID_LOCATION_SERVER_ERROR_CAUSE_STRU
 结构说明  : ECID-LocationServerErrorCauses
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    /*
    ECID-LocationServerErrorCauses ::= SEQUENCE {
        cause       ENUMERATED  {   undefined,
                                    ...
                                },
        ...
    }
    */
    VOS_UINT32      bitOpEcidLocationServerErrCauseExt:1;
    VOS_UINT32      bitOpSpare:31;

    LPP_ECID_LOCATION_SERVER_ERROR_CAUSE_ENUM_UINT32    enEcidLocatSerErrorCause;
}LPP_ECID_LOCATION_SERVER_ERROR_CAUSE_STRU;

/*******************************************************************************
 结构名    : LPP_ECID_TARGET_DEVICE_ERROR_CAUSE_STRU
 结构说明  : ECID-TargetDeviceErrorCauses
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    /*
    ECID-TargetDeviceErrorCauses ::= SEQUENCE {
        cause       ENUMERATED {    undefined,
                                    requestedMeasurementNotAvailable,
                                    notAllrequestedMeasurementsPossible,
                                    ...
                                },
        rsrpMeasurementNotPossible              NULL        OPTIONAL,
        rsrqMeasurementNotPossible              NULL        OPTIONAL,
        ueRxTxMeasurementNotPossible            NULL        OPTIONAL,
        ...
    }
    */
    VOS_UINT32      bitOpEcidTargetDevErrCauseExt:1;
    VOS_UINT32      bitOpRsrpMeasNotPossible:1;
    VOS_UINT32      bitOpRsrqMeasNotPossible:1;
    VOS_UINT32      bitOpRxTxMeasNotPossible:1;
    VOS_UINT32      bitOpSpare:31;
    LPP_ECID_TARGET_DEVICE_ERROR_CAUSE_ENUM_UINT32          enEcidTargetDeviceErrorCause;
    VOS_UINT8                                               ucRsrpMeasurementNotPossible;
    VOS_UINT8                                               ucRsrqMeasurementNotPossible;
    VOS_UINT8                                               ucUeRxTxMeasurementNotPossible;
    VOS_UINT8                                               ucRes;
}LPP_ECID_TARGET_DEVICE_ERROR_CAUSE_STRU;

/*******************************************************************************
 结构名    : LPP_ECID_ERROR_STRU
 结构说明  : ECID-Error
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    /*
    ECID-Error ::= CHOICE {
        locationServerErrorCauses       ECID-LocationServerErrorCauses,
        targetDeviceErrorCauses         ECID-TargetDeviceErrorCauses,
        ...
    }
    */
    VOS_UINT32                      bitOpEcidErrorExt:1;
    VOS_UINT32                      bitOpSpare:31;
    VOS_UINT32                                          ulChoice;

    #define           LPP_ECID_LOCATION_SERVER_ERROR_CAUSE_CHOSEN         0
    #define           LPP_ECID_TARGET_DEVICE_ERROR_CAUSE_CHOSEN           1

    union
    {
       LPP_ECID_LOCATION_SERVER_ERROR_CAUSE_STRU             stLocationServerErrorCauses;
       LPP_ECID_TARGET_DEVICE_ERROR_CAUSE_STRU               stTargetDeviceErrorCauses;
    }u;

}LPP_ECID_ERROR_STRU;

/*******************************************************************************
 结构名    : LPP_ECID_PROVIDE_LOCATION_INFO_STRU
 结构说明  : ECID-ProvideLocationInformation
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    /*
    ECID-ProvideLocationInformation ::= SEQUENCE {
        ecid-SignalMeasurementInformation   ECID-SignalMeasurementInformation       OPTIONAL,
        ecid-Error                          ECID-Error                              OPTIONAL,
        ...
    }
    */
    VOS_UINT32                              bitOpECIDProvideLocateInfoExt:1;
    VOS_UINT32                              bitOpEcidSignalMeasInfo:1;
    VOS_UINT32                              bitOpEcidError:1;
    VOS_UINT32                              bitOpSpare:29;

    LPP_ECID_SIGNAL_MEAS_INFO_STRU          stEcidSignalMeasInfo;
    LPP_ECID_ERROR_STRU                     stEcidError;
}LPP_ECID_PROVIDE_LOCATION_INFO_STRU;

/*******************************************************************************
 结构名    : LPP_EPDU_PROVIDE_LOCATION_INFO_STRU
 结构说明  : EPDU-Sequence
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    /*
    EPDU-Sequence ::= SEQUENCE (SIZE (1..maxEPDU)) OF EPDU
    */
    VOS_UINT32                          ulEpduSequenceCnt;
    LPP_EPDU_STRU                       astEpduSequenceArray[LPP_MAX_EPDU_NUM];
}LPP_EPDU_PROVIDE_LOCATION_INFO_STRU;

/*******************************************************************************
 结构名    : LPP_PROVIDE_LOCATION_INFO_R9_IES_STRU
 结构说明  : ProvideLocationInformation-r9-IEs
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    /*
    ProvideLocationInformation-r9-IEs ::= SEQUENCE {
        commonIEsProvideLocationInformation
                                        CommonIEsProvideLocationInformation     OPTIONAL,
        a-gnss-ProvideLocationInformation   A-GNSS-ProvideLocationInformation   OPTIONAL,
        otdoa-ProvideLocationInformation    OTDOA-ProvideLocationInformation    OPTIONAL,
        ecid-ProvideLocationInformation     ECID-ProvideLocationInformation     OPTIONAL,
        epdu-ProvideLocationInformation     EPDU-Sequence                       OPTIONAL,
        ...
    }
    */
    VOS_UINT32                          bitOpLPPProvideLocationInfoExt:1;
    VOS_UINT32                          bitOpCommonIEsPRovideLocationInfo:1;
    VOS_UINT32                          bitOpAGNSSPRovideLocationInfo:1;
    VOS_UINT32                          bitOpOtdoaPRovideLocationInfo:1;
    VOS_UINT32                          bitOpEcidPRovideLocationInfo:1;
    VOS_UINT32                          bitOpEpduSequence:1;
    VOS_UINT32                          bitOpSpare:26;

    LPP_COMMON_IES_PROVIDE_LOCATION_INFO_STRU           stCommonIEsPRovideLocationInfo;
    LPP_AGNSS_PROVIDE_LOCATION_INFO_STRU                stAGNSSPRovideLocationInfo;
    LPP_OTDOA_PROVIDE_LOCATION_INFO_STRU                stOtdoaPRovideLocationInfo;
    LPP_ECID_PROVIDE_LOCATION_INFO_STRU                 stEcidPRovideLocationInfo;
    LPP_EPDU_PROVIDE_LOCATION_INFO_STRU                 stEpduPRovideLocationInfo;
}LPP_PROVIDE_LOCATION_INFO_R9_IES_STRU;

/*******************************************************************************
 结构名    : LPP_CRITI_EXT_PROVIDE_LOCATION_INFO_STRU
 结构说明  :
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    VOS_UINT32                                          ulChoice;

    #define         LPP_C1_CRITI_EXT_PROVIDE_LOCATION_INFO_R9_CHOSEN              0
    #define         LPP_SPARE3_C1_CRITI_EXT_PROVIDE_LOCATION_INFO_CHOSEN          1
    #define         LPP_SPARE2_C1_CRITI_EXT_PROVIDE_LOCATION_INFO_CHOSEN          2
    #define         LPP_SPARE1_C1_CRITI_EXT_PROVIDE_LOCATION_INFO_CHOSEN          3

        union
        {
            LPP_PROVIDE_LOCATION_INFO_R9_IES_STRU               stProLocationInfoR9;
            VOS_UINT8                                           ucSpare3;
            VOS_UINT8                                           ucSpare2;
            VOS_UINT8                                           ucSpare1;
        }u;
}LPP_CRITI_EXT_PROVIDE_LOCATION_INFO_STRU;

/*******************************************************************************
 结构名    : LPP_MESSAGE_PROVIDE_LOCATION_INFO_STRU
 结构说明  :ProvideLocationInformation
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    /*
    ProvideLocationInformation ::= SEQUENCE {
        criticalExtensions      CHOICE {
            c1                      CHOICE {
                provideLocationInformation-r9   ProvideLocationInformation-r9-IEs,
                spare3 NULL, spare2 NULL, spare1 NULL
            },
            criticalExtensionsFuture    SEQUENCE {}
        }
    }
    */
    VOS_UINT32                                          ulChoice;

    #define           LPP_C1_CRITI_EXT_PROVIDE_LOCATION_INFO_CHOSEN                0
    #define           LPP_CRITI_EXT_FUTURE_PROVIDE_LOCATION_INFO_CHOSEN            1

     union
     {
        LPP_CRITI_EXT_PROVIDE_LOCATION_INFO_STRU            stC1;
        VOS_UINT8                                       ucCritiExtFuture;
     }u;
}LPP_MESSAGE_PROVIDE_LOCATION_INFO_STRU;


/*******************************************************************************
 结构名    : LPP_OTDOA_REQ_LOCATION_INFO_STRU
 结构说明  :OTDOA-RequestLocationInformation
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    /*
    OTDOA-RequestLocationInformation ::= SEQUENCE {
        assistanceAvailability      BOOLEAN,
        ...
    }
    */
    VOS_UINT32                      bitOpOtdoaReqLocationInfoExt:1;
    VOS_UINT32                      bitOpSpare:31;
    VOS_BOOL                        bAssistanceAvailability;
}LPP_OTDOA_REQ_LOCATION_INFO_STRU;

/*******************************************************************************
 结构名    : LPP_REQ_MEASUREMENT_STRU
 结构说明  :OTDOA-RequestLocationInformation
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{

    VOS_UINT8           ucRequestedMeasCnt;
    VOS_UINT8           ucRequestedMeas;
    VOS_UINT8           ucRes[2];
}LPP_REQ_MEASUREMENT_STRU;

/*******************************************************************************
 结构名    : LPP_ECID_REQ_LOCATION_INFO_STRU
 结构说明  :ECID-RequestLocationInformation
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    /*
    ECID-RequestLocationInformation ::= SEQUENCE {
        requestedMeasurements       BIT STRING {    rsrpReq     (0),
                                                    rsrqReq     (1),
                                                    ueRxTxReq   (2) } (SIZE(1..8)),
        ...
    }
    */

    VOS_UINT32                      bitOpEcidRequestLocationInformationExt:1;
    VOS_UINT32                      bitOpSpare:31;
    LPP_REQ_MEASUREMENT_STRU        stRequestedMeasurements;
}LPP_ECID_REQ_LOCATION_INFO_STRU;

/*******************************************************************************
 结构名    : LPP_EPDU_REQ_LOCATION_INFO_STRU
 结构说明  :EPDU-Sequence
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    /*
    EPDU-Sequence ::= SEQUENCE (SIZE (1..maxEPDU)) OF EPDU
    */
    VOS_UINT32              ulEpduSequence;
    LPP_EPDU_STRU           astEpduSequence[LPP_MAX_EPDU_NUM];
}LPP_EPDU_REQ_LOCATION_INFO_STRU;

/*******************************************************************************
 结构名    : LPP_REQ_LOCATION_INFO_R9_IES_STRU
 结构说明  :RequestLocationInformation-r9-IEs
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    /*
    RequestLocationInformation-r9-IEs ::= SEQUENCE {
        commonIEsRequestLocationInformation
                                        CommonIEsRequestLocationInformation     OPTIONAL,   -- Need ON
        a-gnss-RequestLocationInformation   A-GNSS-RequestLocationInformation   OPTIONAL,   -- Need ON
        otdoa-RequestLocationInformation    OTDOA-RequestLocationInformation    OPTIONAL,   -- Need ON
        ecid-RequestLocationInformation     ECID-RequestLocationInformation     OPTIONAL,   -- Need ON
        epdu-RequestLocationInformation     EPDU-Sequence                       OPTIONAL,   -- Need ON
        ...
    }
    */
    VOS_UINT32                          bitOpLPPReqLocationInfoExt:1;
    VOS_UINT32                          bitOpCommonIEsReqLocationInfo:1;
    VOS_UINT32                          bitOpAGNSSReqLocationInfo:1;
    VOS_UINT32                          bitOpOtdoaReqLocationInfo:1;
    VOS_UINT32                          bitOpEcidReqLocationInfo:1;
    VOS_UINT32                          bitOpEpduSequence:1;
    VOS_UINT32                          bitOpSpare:26;

    LPP_COMMON_IES_REQ_LOCATION_INFO_STRU           stCommonIEsReqLocationInfo;
    LPP_AGNSS_REQ_LOCATION_INFO_STRU                stAGNSSReqLocationInfo;
    LPP_OTDOA_REQ_LOCATION_INFO_STRU                stOtdoaReqLocationInfo;
    LPP_ECID_REQ_LOCATION_INFO_STRU                 stEcidReqLocationInfo;
    LPP_EPDU_REQ_LOCATION_INFO_STRU                 stEpduReqLocationInfo;
}LPP_REQ_LOCATION_INFO_R9_IES_STRU;

/*******************************************************************************
 结构名    : LPP_CRITI_EXT_REQ_LOCATION_INFO_STRU
 结构说明  :
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    VOS_UINT32                                          ulChoice;

    #define         LPP_C1_CRITI_EXT_REQ_LOCATION_INFO_R9_CHOSEN              0
    #define         LPP_SPARE3_C1_CRITI_EXT_REQ_LOCATION_INFO_CHOSEN          1
    #define         LPP_SPARE2_C1_CRITI_EXT_REQ_LOCATION_INFO_CHOSEN          2
    #define         LPP_SPARE1_C1_CRITI_EXT_REQ_LOCATION_INFO_CHOSEN          3

        union
        {
            LPP_REQ_LOCATION_INFO_R9_IES_STRU               stReqLocationInfoR9;
            VOS_UINT8                                       ucSpare3;
            VOS_UINT8                                       ucSpare2;
            VOS_UINT8                                       ucSpare1;
        }u;
}LPP_CRITI_EXT_REQ_LOCATION_INFO_STRU;

/*******************************************************************************
 结构名    : LPP_MESSAGE_REQUEST_LOCATION_INFO_STRU
 结构说明  :RequestLocationInformation
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    /*
    RequestLocationInformation ::= SEQUENCE {
        criticalExtensions      CHOICE {
            c1                      CHOICE {
                requestLocationInformation-r9   RequestLocationInformation-r9-IEs,
                spare3 NULL, spare2 NULL, spare1 NULL
            },
            criticalExtensionsFuture    SEQUENCE {}
        }
    }
    */
    VOS_UINT32                                          ulChoice;

    #define           LPP_C1_CRITI_EXT_REQ_LOCATION_INFO_CHOSEN                0
    #define           LPP_CRITI_EXT_FUTURE_REQ_LOCATION_INFO_CHOSEN            1

     union
     {
        LPP_CRITI_EXT_REQ_LOCATION_INFO_STRU            stC1;
        VOS_UINT8                                       ucCritiExtFuture;
     }u;
}LPP_MESSAGE_REQUEST_LOCATION_INFO_STRU;

/*******************************************************************************
 结构名    : LPP_COMMON_IES_PROVIDE_ASSIST_DATA_STRU
 结构说明  :    协议为空
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    /*协议为空*/
    VOS_UINT32              bitOpCommonIEsProvideAssistDataExt:1;
    VOS_UINT32              bitOpSpare:31;
}LPP_COMMON_IES_PROVIDE_ASSIST_DATA_STRU;

/*******************************************************************************
 结构名    : LPP_PRS_MUTING_INFO_R9_STRU
 结构说明  :    协议为空
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    VOS_UINT32                                          ulChoice;

    #define           LPP_PRS_MUTING_INFO_PO2_R9_CHOSEN         0
    #define           LPP_PRS_MUTING_INFO_PO4_R9_CHOSEN         1
    #define           LPP_PRS_MUTING_INFO_PO8_R9_CHOSEN         2
    #define           LPP_PRS_MUTING_INFO_PO16_R9_CHOSEN        3

    union
    {
        VOS_UINT16       usPo2R9;
        VOS_UINT16       usPo4R9;
        VOS_UINT16       usPo8R9;
        VOS_UINT16       usPo16R9;/*edited by wangensheng to follow the protocol*/
    }u;
}LPP_PRS_MUTING_INFO_R9_STRU;

/*******************************************************************************
 结构名    : LPP_PRS_INFO_STRU
 结构说明  :PRS-Info
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    /*
    PRS-Info ::= SEQUENCE {
        prs-Bandwidth           ENUMERATED { n6, n15, n25, n50, n75, n100, ... },
        prs-ConfigurationIndex  INTEGER (0..4095),
        numDL-Frames            ENUMERATED {sf-1, sf-2, sf-4, sf-6, ...},
        ...,
        prs-MutingInfo-r9       CHOICE {
            po2-r9                  BIT STRING (SIZE(2)),
            po4-r9                  BIT STRING (SIZE(4)),
            po8-r9                  BIT STRING (SIZE(8)),
            po16-r9                 BIT STRING (SIZE(16)),
            ...
        }                                                       OPTIONAL                -- Need OP
    }
    */
    VOS_UINT32                              bitOpPrsInfoExt:1;
    VOS_UINT32                              bitOpPrsMutingInfoR9:1;
    VOS_UINT32                              bitOpSpare:30;

    LPP_PRS_BAND_WITH_ENUM_UINT8            enPrsBandWith;
    VOS_UINT8                               aucRsv[3];
    VOS_UINT32                              ulPrsConfigIndex;
    LPP_NUMDL_FRAMES_ENUM_UINT8             enNumDlFrames;
    VOS_UINT8                               aucRsv1[3];
    LPP_PRS_MUTING_INFO_R9_STRU             stPrsMutingInfoR9;
}LPP_PRS_INFO_STRU;

/*******************************************************************************
 结构名    : LPP_OTDOA_REF_CELL_INFO_STRU
 结构说明  :OTDOA-ReferenceCellInfo
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    /*
    OTDOA-ReferenceCellInfo ::= SEQUENCE {
        physCellId                  INTEGER (0..503),
        cellGlobalId                ECGI                        OPTIONAL,       -- Need ON
        earfcnRef                   ARFCN-ValueEUTRA            OPTIONAL,       -- Cond NotSameAsServ0
        antennaPortConfig           ENUMERATED {ports1-or-2, ports4, ... }
                                                                OPTIONAL,       -- Cond NotSameAsServ1
        cpLength                    ENUMERATED { normal, extended, ... },
        prsInfo                     PRS-Info                    OPTIONAL,       -- Cond PRS
        ...,
        [[ earfcnRef-v9a0           ARFCN-ValueEUTRA-v9a0       OPTIONAL        -- Cond NotSameAsServ2
        ]]
    }
    */
    VOS_UINT32                          bitOpOtdoaRefCellInfoExt:1;/*edited by wangensheng ,for the ext-object */
    VOS_UINT32                          bitOpCellGlobalId:1;
    VOS_UINT32                          bitOpEarFcnRef:1;
    VOS_UINT32                          bitOpAntennaPortConfig:1;
    VOS_UINT32                          bitOpPrsInfo:1;
    VOS_UINT32                          bitOpEarfcnRefV9a0:1;
    VOS_UINT32                          bitOpSpare:26;

    VOS_UINT16                          usPhyCellId;
    VOS_UINT8                           aucRes[2];
    LPP_ECGI_STRU                       stCellGlobalId;
    LPP_ARFCN_VALUE_EUTRA_STRU          stEarfcnRef;
    LPP_ANTENNA_PORT_CONFIG_ENUM_UINT8 enAntennaPortConfig;
    LPP_CP_LENGTH_ENUM_UINT8           enCpLength;
    VOS_UINT8                           aucRes1[2];/*forconfirm*/
    LPP_PRS_INFO_STRU                   stPrsInfo;
    LPP_ARFCN_VALUE_EUTRA_V9A0_STRU     stEarfcnRefV9a0;
}LPP_OTDOA_REF_CELL_INFO_STRU;

/*******************************************************************************
 结构名    : LPP_OTDOA_NEIGHBOUR_CELL_INFO_ELEMENT_STRU
 结构说明  :OTDOA-NeighbourCellInfoElement
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    /*
    OTDOA-NeighbourCellInfoElement ::= SEQUENCE {
        physCellId                          INTEGER (0..503),
        cellGlobalId                        ECGI                OPTIONAL,       -- Need ON
        earfcn                              ARFCN-ValueEUTRA    OPTIONAL,       -- Cond NotSameAsRef0
        cpLength                            ENUMERATED {normal, extended, ...}
                                                                OPTIONAL,       -- Cond NotSameAsRef1
        prsInfo                             PRS-Info            OPTIONAL,       -- Cond NotSameAsRef2
        antennaPortConfig                   ENUMERATED {ports-1-or-2, ports-4, ...}
                                                                OPTIONAL,       -- Cond NotsameAsRef3
        slotNumberOffset                    INTEGER (0..19)     OPTIONAL,       -- Cond NotSameAsRef4
        prs-SubframeOffset                  INTEGER (0..1279)   OPTIONAL,       -- Cond InterFreq
        expectedRSTD                        INTEGER (0..16383),
        expectedRSTD-Uncertainty            INTEGER (0..1023),
        ...,
        [[ earfcn-v9a0          ARFCN-ValueEUTRA-v9a0           OPTIONAL        -- Cond NotSameAsRef5
        ]]
    }
    */
    VOS_UINT32                              bitOpNeighbourCellInfoElementExt:1;
    VOS_UINT32                              bitOpCellGlobalId:1;
    VOS_UINT32                              bitOpEarfcn:1;
    VOS_UINT32                              bitOpCpLength:1;
    VOS_UINT32                              bitOpPrsInfo:1;
    VOS_UINT32                              bitOpAntennaPortconfig:1;
    VOS_UINT32                              bitOpSlotNumberOffset:1;
    VOS_UINT32                              bitOpPrsSubFrameOffset:1;
    VOS_UINT32                              bitOpEarfcnV9a0:1;/*edited by wangensheng ,EXT-object */
    VOS_UINT32                              bitOpSpare:23;

    VOS_UINT32                              ulPhysCellId;
    LPP_ECGI_STRU                           stCellGlobalId;
    LPP_ARFCN_VALUE_EUTRA_STRU              stEarfcn;
    LPP_CP_LENGTH_ENUM_UINT8                enCpLength;
    VOS_UINT8                               aucRsv[3];
    LPP_PRS_INFO_STRU                       stPrsInfo;
    LPP_ANTENNA_PORT_CONFIG_ENUM_UINT8      enAntennaPortConfig;
    VOS_UINT8                               uacRsv1[3];
    VOS_UINT16                              usSlotNumberOffset;
    VOS_UINT16                              usPrsSubframeOffset;
    VOS_UINT16                              usExpectedRSTD;
    VOS_UINT16                              usExpectedRSTDUncertainty;
    LPP_ARFCN_VALUE_EUTRA_V9A0_STRU         stEarfcnv9a0;/*Add this optional object ,edited by wangensheng*/
}LPP_OTDOA_NEIGHBOUR_CELL_INFO_ELEMENT_STRU;

/*******************************************************************************
 结构名    : LPP_OTDOA_NEIGHBOUR_FREQ_INFO_STRU
 结构说明  :OTDOA-NeighbourFreqInfo
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    /*
    OTDOA-NeighbourFreqInfo ::= SEQUENCE (SIZE (1..24)) OF OTDOA-NeighbourCellInfoElement
    */
    VOS_UINT32                          ulOtdoaNeighbourFreqInfoCnt;
    LPP_OTDOA_NEIGHBOUR_CELL_INFO_ELEMENT_STRU  astOtdoaNeighbourFreqInfoArray[LPP_MAX_OTDOA_NEIGHBOUR_CELL_INFO_ELMENT_LEN];
}LPP_OTDOA_NEIGHBOUR_FREQ_INFO_STRU;

/*******************************************************************************
 结构名    : LPP_OTDOA_NEIGHOUR_CELL_INFO_STRU
 结构说明  :OTDOA-NeighbourCellInfoList
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    /*
    OTDOA-NeighbourCellInfoList ::= SEQUENCE (SIZE (1..maxFreqLayers)) OF OTDOA-NeighbourFreqInfo
    */
    VOS_UINT32                          ulOtdoaNeighbourCellInfoListCnt;
    LPP_OTDOA_NEIGHBOUR_FREQ_INFO_STRU  astOtdoaNeighourFreqInfoArray[LPP_MAX_FREQ_LAYERS_LEN];
}LPP_OTDOA_NEIGHOUR_CELL_INFO_STRU;
/*******************************************************************************
 结构名    : LPP_OTDOA_PROVIDE_ASSIST_DATA_STRU
 结构说明  :OTDOA-ProvideAssistanceData
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    /*
    OTDOA-ProvideAssistanceData ::= SEQUENCE {
        otdoa-ReferenceCellInfo         OTDOA-ReferenceCellInfo             OPTIONAL,   -- Need ON
        otdoa-NeighbourCellInfo         OTDOA-NeighbourCellInfoList         OPTIONAL,   -- Need ON
        otdoa-Error                     OTDOA-Error                         OPTIONAL,   -- Need ON
        ...
    }
    */
    VOS_UINT32                          bitOpOtdoaProvideAssistanceDataExt:1;
    VOS_UINT32                          bitOpOtdoaReferenceCellInfo:1;
    VOS_UINT32                          bitOpOtdoaNeighbourCellInfo:1;
    VOS_UINT32                          bitOpOtdoaError:1;
    VOS_UINT32                          bitOpSpare:28;

    LPP_OTDOA_REF_CELL_INFO_STRU        stOtdoaRefCellInfo;
    LPP_OTDOA_NEIGHOUR_CELL_INFO_STRU   stOtdoaNeighbourCellInfo;
    LPP_OTDOA_ERROR_STRU                stOtdoaError;
}LPP_OTDOA_PROVIDE_ASSIST_DATA_STRU;
/*******************************************************************************
 结构名    : LPP_EPDU_PROVIDE_ASSIST_DATA_STRU
 结构说明  :EPDU-Sequence
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    /*
    EPDU-Sequence ::= SEQUENCE (SIZE (1..maxEPDU)) OF EPDU
    */
    VOS_UINT32              ulEpduCnt;
    LPP_EPDU_STRU           astEpduSequenceArray[LPP_MAX_EPDU_NUM];
}LPP_EPDU_PROVIDE_ASSIST_DATA_STRU;

/*******************************************************************************
 结构名    : LPP_PROVIDE_ASSIST_DATA_R9_IES_STRU
 结构说明  :ProvideAssistanceData-r9-IEs
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    /*
    ProvideAssistanceData-r9-IEs ::= SEQUENCE {
        commonIEsProvideAssistanceData      CommonIEsProvideAssistanceData      OPTIONAL,   -- Need ON
        a-gnss-ProvideAssistanceData        A-GNSS-ProvideAssistanceData        OPTIONAL,   -- Need ON
        otdoa-ProvideAssistanceData         OTDOA-ProvideAssistanceData         OPTIONAL,   -- Need ON
        epdu-Provide-Assistance-Data        EPDU-Sequence                       OPTIONAL,   -- Need ON
        ...
    }
    */
    VOS_UINT32                          bitOpLPPProvideAssistDataExt:1;
    VOS_UINT32                          bitOpCommonIEsProvideAssitData:1;
    VOS_UINT32                          bitOpAGNSSProvideAssistData:1;
    VOS_UINT32                          bitOpOTDOAProvideAssistData:1;
    VOS_UINT32                          bitOpEPDUSequence:1;
    VOS_UINT32                          bitOpSpare:27;

    LPP_COMMON_IES_PROVIDE_ASSIST_DATA_STRU         stCommonIEsProvideAssistanceData;
    LPP_AGNSS_PROVIDE_ASSIST_DATA_STRU              stAGNSSProvideAssistanceData;
    LPP_OTDOA_PROVIDE_ASSIST_DATA_STRU              stOTDOAProvideAssistanceData;
    LPP_EPDU_PROVIDE_ASSIST_DATA_STRU               stEPDUProvideAssistanceData;
}LPP_PROVIDE_ASSIST_DATA_R9_IES_STRU;

/*******************************************************************************
 结构名    : LPP_CRITI_EXT_PROVIDE_ASSIST_DATA_STRU
 结构说明  :
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    VOS_UINT32                                          ulChoice;

    #define         LPP_C1_CRITI_EXT_PROVIDE_ASSIST_DATA_R9_CHOSEN              0
    #define         LPP_SPARE3_C1_CRITI_EXT_PROVIDE_ASSIST_DATA_CHOSEN          1
    #define         LPP_SPARE2_C1_CRITI_EXT_PROVIDE_ASSIST_DATA_CHOSEN          2
    #define         LPP_SPARE1_C1_CRITI_EXT_PROVIDE_ASSIST_DATA_CHOSEN          3

    union
    {
        LPP_PROVIDE_ASSIST_DATA_R9_IES_STRU             stProvideAssitDataR9;
        VOS_UINT8                                       ucSpare3;
        VOS_UINT8                                       ucSpare2;
        VOS_UINT8                                       ucSpare1;
    }u;
}LPP_CRITI_EXT_PROVIDE_ASSIST_DATA_STRU;

/*******************************************************************************
 结构名    : LPP_MESSAGE_PROVIDE_ASSIST_DATA_STRU
 结构说明  :ProvideAssisData
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    /*
    ProvideAssisData ::= SEQUENCE {
        criticalExtensions      CHOICE {
            c1                      CHOICE {
                ProvideAssisData-r9      ProvideAssisData-r9-IEs,
                spare3 NULL, spare2 NULL, spare1 NULL
            },
            criticalExtensionsFuture    SEQUENCE {}
        }
    }

   ProvideAssisData-r9-IEs ::= SEQUENCE {
        commonIEsProvideAssisData        CommonIEsProvideAssisData       	OPTIONAL,
        a-gnss-ProvideAssisData         A-GNSS-ProvideAssisData          		OPTIONAL,
        otdoa-ProvideAssisData          OTDOA-ProvideAssisData       			OPTIONAL,
        epdu-ProvideAssisData            EPDU-Sequence                      		OPTIONAL,
        ...
    }
    */
    VOS_UINT32                                          ulChoice;

    #define           LPP_C1_CRITI_EXT_PROVIDE_ASSIST_DATA_CHOSEN        0
    #define           LPP_CRITI_EXT_FUTURE_PROVIDE_ASSIST_DATA_CHOSEN    1

    union
    {
        LPP_CRITI_EXT_PROVIDE_ASSIST_DATA_STRU           stC1;
        VOS_UINT8                                        ucCritiExtFuture;
    }u;
}LPP_MESSAGE_PROVIDE_ASSIST_DATA_STRU;

/*******************************************************************************
 结构名    : LPP_OTDOA_REQ_ASSIST_DATA_STRU
 结构说明  :OTDOA-RequestAssistanceData
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    /*
    OTDOA-RequestAssistanceData ::= SEQUENCE {
        physCellId      INTEGER (0..503),
        ...
    }
    */
    VOS_UINT32          bitOpOtdoaReqAssistDataExt:1;
    VOS_UINT32          bitOpSpare:31;

    VOS_UINT16          usPhyCellId;
    VOS_UINT16          usRes;/*forconfirm*/
}LPP_OTDOA_REQ_ASSIST_DATA_STRU;

/*******************************************************************************
 结构名    : LPP_EPDU_REQ_ASSIST_DATA_STRU
 结构说明  :EPDU-Sequence
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    /*EPDU-Sequence ::= SEQUENCE (SIZE (1..maxEPDU)) OF EPDU*/
    LPP_EPDU_SEQUENCE_STRU      astReqAssistDataEpduSeq;
}LPP_EPDU_REQ_ASSIST_DATA_STRU;

/*******************************************************************************
 结构名    : LPP_COMMON_IES_REQ_ASSIST_DATA_STRU
 结构说明  :CommonIEsRequestAssistanceData
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    /*
    CommonIEsRequestAssistanceData ::= SEQUENCE {
        primaryCellID       ECGI        OPTIONAL,   -- Cond EUTRA
        ...
    }
    */
    VOS_UINT32      bitOpCommonIEsReqAssistDataExt:1;
    VOS_UINT32      bitOpPrimaryCellID:1;
    VOS_UINT32      bitOpSpare:30;

    LPP_ECGI_STRU   stPrimaryCellID;

}LPP_COMMON_IES_REQ_ASSIST_DATA_STRU;

/*******************************************************************************
 结构名    : LPP_REQUEST_ASSIST_DATA_R9_IES_STRU
 结构说明  :RequestAssistanceData-r9-IEs
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    /*
    RequestAssistanceData ::= SEQUENCE {
        criticalExtensions      CHOICE {
            c1                      CHOICE {
                requestAssistanceData-r9    RequestAssistanceData-r9-IEs,
                spare3 NULL, spare2 NULL, spare1 NULL
            },
            criticalExtensionsFuture    SEQUENCE {}
        }
    }

    RequestAssistanceData-r9-IEs ::= SEQUENCE {
        commonIEsRequestAssistanceData      CommonIEsRequestAssistanceData      OPTIONAL,
        a-gnss-RequestAssistanceData        A-GNSS-RequestAssistanceData        OPTIONAL,
        otdoa-RequestAssistanceData         OTDOA-RequestAssistanceData         OPTIONAL,
        epdu-RequestAssistanceData          EPDU-Sequence                       OPTIONAL,
        ...
    }
    */
    VOS_UINT32                          bitOpLPPRequestAssistDataExt:1;
    VOS_UINT32                          bitOpCommonIEsRequestAssitData:1;
    VOS_UINT32                          bitOpAGNSSRequestAssistData:1;
    VOS_UINT32                          bitOpOTDOARequestAssistData:1;
    VOS_UINT32                          bitOpEPDUSequence:1;
    VOS_UINT32                          bitOpSpare:27;

    LPP_COMMON_IES_REQ_ASSIST_DATA_STRU         stCommonIEsRequestAssistanceData;
    LPP_AGNSS_REQ_ASSIST_DATA_STRU              stAGNSSRequestAssistanceData;
    LPP_OTDOA_REQ_ASSIST_DATA_STRU              stOTDOARequestAssistanceData;
    LPP_EPDU_REQ_ASSIST_DATA_STRU               stEPDURequestAssistanceData;
}LPP_REQUEST_ASSIST_DATA_R9_IES_STRU;

/*******************************************************************************
 结构名    : LPP_CRITI_EXT_REQUEST_ASSIST_DATA_STRU
 结构说明  :RequestAssistanceData
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    VOS_UINT32                                          ulChoice;

    #define         LPP_C1_CRITI_EXT_REQUEST_ASSIST_DATA_R9_CHOSEN              0
    #define         LPP_SPARE3_C1_CRITI_EXT_REQUEST_ASSIST_DATA_CHOSEN          1
    #define         LPP_SPARE2_C1_CRITI_EXT_REQUEST_ASSIST_DATA_CHOSEN          2
    #define         LPP_SPARE1_C1_CRITI_EXT_REQUEST_ASSIST_DATA_CHOSEN          3

    union
    {
        LPP_REQUEST_ASSIST_DATA_R9_IES_STRU             stRequestAssitDataR9;
        VOS_UINT8                                       ucSpare3;
        VOS_UINT8                                       ucSpare2;
        VOS_UINT8                                       ucSpare1;
    }u;
}LPP_CRITI_EXT_REQUEST_ASSIST_DATA_STRU;

/*******************************************************************************
 结构名    : LPP_MESSAGE_REQUEST_ASSIST_DATA_STRU
 结构说明  :RequestAssistanceData
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    VOS_UINT32                                          ulChoice;

    #define           LPP_C1_CRITI_EXT_REQUEST_ASSIST_DATA_CHOSEN        0
    #define           LPP_CRITI_EXT_FUTURE_REQUEST_ASSIST_DATA_CHOSEN    1

     union
     {
        LPP_CRITI_EXT_REQUEST_ASSIST_DATA_STRU           stC1;
        VOS_UINT8                                        ucCritiExtFuture;
     }u;
}LPP_MESSAGE_REQUEST_ASSIST_DATA_STRU;

/*******************************************************************************
 结构名    : LPP_COMMON_IES_PROVIDE_CAP_STRU
 结构说明  :
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    /*协议为空*/
    VOS_UINT32          bitOpCommonIEsProvideCapExt:1;
    VOS_UINT32          bitOpSpare:31;
}LPP_COMMON_IES_PROVIDE_CAP_STRU;

/*******************************************************************************
 结构名    : LPP_OTDOA_MODE_STRU
 结构说明  :
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    VOS_UINT8                               ucOTDOAMode;
    VOS_UINT8                               ucOTDOAModeLen;
    VOS_UINT8                               ucRes[2];
}LPP_OTDOA_MODE_STRU;

/*******************************************************************************
 结构名    : LPP_SUPPORTED_BAND_EUTRA_STRU
 结构说明  :SupportedBandEUTRA
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    /*
    SupportedBandEUTRA ::= SEQUENCE {
        bandEUTRA                           INTEGER (1..maxFBI)
    }

    maxFBI                          INTEGER::=64-- Maximum value of frequency band indicator
    */

    VOS_UINT32                              ulBandEutra;
}LPP_SUPPORTED_BAND_EUTRA_STRU;

/*******************************************************************************
 结构名    : LPP_SUPPORTED_BAND_LIST_EUTRA_STRU
 结构说明  :
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    VOS_UINT32                              ulSupportBandNum;
    LPP_SUPPORTED_BAND_EUTRA_STRU           astSupportedBandArray[LPP_MAX_SUPPORTED_BAND_EUTRA_NUM];
}LPP_SUPPORTED_BAND_LIST_EUTRA_STRU;

/*******************************************************************************
 结构名    : LPP_SUPPORTED_BAND_EUTRA_V9A0_STRU
 结构说明  :SupportedBandEUTRA-v9a0
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    /*
    SupportedBandEUTRA-v9a0 ::=     SEQUENCE {
        bandEUTRA-v9a0                      INTEGER (maxFBI-Plus1..maxFBI2)     OPTIONAL
    }

    maxFBI-Plus1                        INTEGER ::= 65  -- lowest value extended FBI range
    maxFBI2                             INTEGER ::= 256 -- highest value extended FBI range
    */
    VOS_UINT32                              bitOpBandEutraV9A0:1;
    VOS_UINT32                              bitOpSpare:31;
    VOS_UINT32                              ulBandEutraV9A0;
}LPP_SUPPORTED_BAND_EUTRA_V9A0_STRU;

/*******************************************************************************
 结构名    : LPP_SUPPORTED_BAND_LIST_EUTRA_V9A0_STRU
 结构说明  :
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    VOS_UINT32                              ulSupportBandNum;
    LPP_SUPPORTED_BAND_EUTRA_V9A0_STRU      astSupportedBandArray[LPP_MAX_SUPPORTED_BAND_EUTRA_NUM];
}LPP_SUPPORTED_BAND_LIST_EUTRA_V9A0_STRU;

/*******************************************************************************
 结构名    : LPP_OTDOA_PROVIDE_CAP_STRU
 结构说明  :OTDOA-ProvideCapabilities
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    /*
    OTDOA-ProvideCapabilities ::= SEQUENCE {
             otdoa-Mode      BIT STRING {    ue-assisted (0) } (SIZE (1..8)),
             ...,
             supportedBandListEUTRA      SEQUENCE (SIZE (1..maxBands)) OF SupportedBandEUTRA     OPTIONAL,
             supportedBandListEUTRA-v9a0 SEQUENCE (SIZE (1..maxBands)) OF SupportedBandEUTRA-v9a0
                                                                                                 OPTIONAL,
             interFreqRSTDmeasurement-r10        ENUMERATED { supported }                        OPTIONAL,
             additionalNeighbourCellInfoList-r10 ENUMERATED { supported }                        OPTIONAL
         }
    */
    VOS_UINT32                                      bitOpOtdoaProvideCapExt:1;
    VOS_UINT32                                      bitOpSupportedBandListEutra     : 1;
    VOS_UINT32                                      bitOpSupportedBandListEutraV9A0 : 1;
    VOS_UINT32                                      bitOpInterFreqRSTDmeasurementR10: 1;
    VOS_UINT32                                      bitOpAdditionalNeighbourCellInfoListR10:1;
    VOS_UINT32                                      bitOpSpare  : 27;

    LPP_OTDOA_MODE_STRU                                 stOtdoaMode;
    LPP_SUPPORTED_BAND_LIST_EUTRA_STRU                  stSupportedBandListEutra;
    LPP_SUPPORTED_BAND_LIST_EUTRA_V9A0_STRU             stSupportedBandListEutraV9A0;
    LPP_INTER_FREQ_RSTD_MEASUREMENT_R10_ENUM_UINT32     enInterFreqRSTDmeasurementR10;
    LPP_ADDITIONAL_NEIGH_CELL_INFO_LIST_R10_ENUM_UINT32 enAdditionalNeighbourCellInfoListR10;
}LPP_OTDOA_PROVIDE_CAP_STRU;

/*******************************************************************************
 结构名    : LPP_ECID_MEAS_SUPPORTED_STRU
 结构说明  :
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    VOS_UINT8           ucEcidMeasSupCnt;
    VOS_UINT8           ucEcidMeasSup;
    VOS_UINT8           ucRes[2];
}LPP_ECID_MEAS_SUPPORTED_STRU;

/*******************************************************************************
 结构名    : LPP_ECID_PROVIDE_CAP_STRU
 结构说明  :
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    VOS_UINT32                  bitOpEcidProvideCapExt:1;
    VOS_UINT32                  bitOpSpare:31;
    LPP_ECID_MEAS_SUPPORTED_STRU        stEcidMeasSupported;
}LPP_ECID_PROVIDE_CAP_STRU;

/*******************************************************************************
 结构名    : LPP_PROVIDE_CAPABILITIES_R9_IES_STRU
 结构说明  :ProvideCapabilities-r9-IEs
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    /*
    ProvideCapabilities-r9-IEs ::= SEQUENCE {
        commonIEsProvideCapabilities        CommonIEsProvideCapabilities        OPTIONAL,
        a-gnss-ProvideCapabilities          A-GNSS-ProvideCapabilities          OPTIONAL,
        otdoa-ProvideCapabilities           OTDOA-ProvideCapabilities           OPTIONAL,
        ecid-ProvideCapabilities            ECID-ProvideCapabilities            OPTIONAL,
        epdu-ProvideCapabilities            EPDU-Sequence                       OPTIONAL,
        ...
    }
    */
    VOS_UINT32                              bitOpLPPProvideCapabilitiesExt:1;
    VOS_UINT32                              bitOpCommonIEsProvideCapabilities:1;
    VOS_UINT32                              bitOpAGNSSProvideCapabilities:1;
    VOS_UINT32                              bitOpOTDOAProvideCapabilities:1;
    VOS_UINT32                              bitOpECIDProvideCapabilities:1;
    VOS_UINT32                              bitOpEPDUProvideCapabilities:1;
    VOS_UINT32                              bitOpSpare:26;

    LPP_COMMON_IES_PROVIDE_CAP_STRU         stCommonIEsProvideCapabilities;
    LPP_AGNSS_PROVIDE_CAP_STRU              stAGNSSProvideCapabilities;
    LPP_OTDOA_PROVIDE_CAP_STRU              stOTDOAProvideCapabilities;
    LPP_ECID_PROVIDE_CAP_STRU               stECIDProvideCapabilities;
    LPP_EPDU_SEQUENCE_STRU                  stEPDURequestCapabilities;
}LPP_PROVIDE_CAPABILITIES_R9_IES_STRU;

/*******************************************************************************
 结构名    : LPP_CRITI_EXT_PROVIDE_CAPABILITIES_STRU
 结构说明  :
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    VOS_UINT32                                      ulChoice;

    #define         LPP_PROVIDE_CAPABILITIES_R9_CHOSEN              0
    #define         LPP_PROVIDE_CAPABILITIES_SPARE3_CHOSEN          1
    #define         LPP_PROVIDE_CAPABILITIES_SPARE2_CHOSEN          2
    #define         LPP_PROVIDE_CAPABILITIES_SPARE1_CHOSEN          3

    union
    {
        LPP_PROVIDE_CAPABILITIES_R9_IES_STRU        stProvideCapabilitiesR9;
        VOS_UINT8                                   ucSpare3;
        VOS_UINT8                                   ucSpare2;
        VOS_UINT8                                   ucSpare1;
    }u;
}LPP_CRITI_EXT_PROVIDE_CAPABILITIES_STRU;

/*******************************************************************************
 结构名    : LPP_MESSAGE_PROVIDE_CAPABILITIES_STRU
 结构说明  :ProvideCapabilities
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    /*
    ProvideCapabilities ::= SEQUENCE {
        criticalExtensions      CHOICE {
            c1                      CHOICE {
                provideCapabilities-r9      ProvideCapabilities-r9-IEs,
                spare3 NULL, spare2 NULL, spare1 NULL
            },
            criticalExtensionsFuture    SEQUENCE {}
        }
    }
    */
    VOS_UINT32                                          ulChoice;

    #define           LPP_C1_CRITI_EXT_PROVIDE_CAPABILITIES_CHOSEN        0
    #define           LPP_CRITI_EXT_FUTURE_PROVIDE_CAPABILITIES_CHOSEN    1

    union
    {
       LPP_CRITI_EXT_PROVIDE_CAPABILITIES_STRU          stC1;
       VOS_UINT8                                        ucCritiExtFuture;
    }u;
}LPP_MESSAGE_PROVIDE_CAPABILITIES_STRU;

/*******************************************************************************
 结构名    : LPP_EPDU_REQ_CAP_STRU
 结构说明  :EPDU-Sequence
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    /*EPDU-Sequence ::= SEQUENCE (SIZE (1..maxEPDU)) OF EPDU*/
    VOS_UINT32                      ulEpduSequenceCnt;
    LPP_EPDU_STRU                   astEpduArray[LPP_MAX_EPDU_NUM];
}LPP_EPDU_REQ_CAP_STRU;

/*******************************************************************************
 结构名    : LPP_ECID_REQ_CAP_STRU
 结构说明  :
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
/*协议里此结构为空*/
        VOS_UINT32      bitOpEcidReqCapExt:1;
        VOS_UINT32      bitOpSpare:31;
}LPP_ECID_REQ_CAP_STRU;

/*******************************************************************************
 结构名    : LPP_OTDOA_REQ_CAP_STRU
 结构说明  :协议里此结构为空
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
/*协议里此结构为空*/
        VOS_UINT32      bitOpOtdoaReqCapExt:1;
        VOS_UINT32      bitOpSpare:31;

        VOS_UINT32      ulRes;
}LPP_OTDOA_REQ_CAP_STRU;

/*******************************************************************************
 结构名    : LPP_COMMON_IES_REQ_CAP_STRU
 结构说明  :协议里此结构为空
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
/*协议里此结构为空*/
    VOS_UINT32          bitOpCommonIEsReqCapabilitiesExt:1;
    VOS_UINT32          bitOpSpare:31;
}LPP_COMMON_IES_REQ_CAP_STRU;

/*******************************************************************************
 结构名    : LPP_REQUEST_CAPABILITIES_R9_IES_STRU
 结构说明  :RequestCapabilities-r9-IEs
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    /*
    RequestCapabilities-r9-IEs ::= SEQUENCE {
        commonIEsRequestCapabilities        CommonIEsRequestCapabilities        OPTIONAL,   -- Need ON
        a-gnss-RequestCapabilities          A-GNSS-RequestCapabilities          OPTIONAL,   -- Need ON
        otdoa-RequestCapabilities           OTDOA-RequestCapabilities           OPTIONAL,   -- Need ON
        ecid-RequestCapabilities            ECID-RequestCapabilities            OPTIONAL,   -- Need ON
        epdu-RequestCapabilities            EPDU-Sequence                       OPTIONAL,   -- Need ON
        ...
    }
    */
    VOS_UINT32                          bitOpLPPReqCapaabilitiesExt:1;
    VOS_UINT32                          bitOpCommonIEsRequestCapabilities:1;
    VOS_UINT32                          bitOpAGNSSRequestCapabilities:1;
    VOS_UINT32                          bitOpOTDOARequestCapabilities:1;
    VOS_UINT32                          bitOpECIDRequestCapabilities:1;
    VOS_UINT32                          bitOpEPDUSequence:1;
    VOS_UINT32                          bitOpSpare:26;

    LPP_COMMON_IES_REQ_CAP_STRU         stCommonIEsRequestCapabilities;
    LPP_AGNSS_REQ_CAP_STRU              stAGNSSRequestCapabilities;
    LPP_OTDOA_REQ_CAP_STRU              stOTDOARequestCapabilities;
    LPP_ECID_REQ_CAP_STRU               stECIDRequestCapabilities;
    LPP_EPDU_REQ_CAP_STRU               stEPDURequestCapabilities;
}LPP_REQUEST_CAPABILITIES_R9_IES_STRU;

/*******************************************************************************
 结构名    : LPP_CRITI_EXT_REQUEST_CAPABILITIES_STRU
 结构说明  :
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    VOS_UINT32                                          ulChoice;

    #define         LPP_C1_CRITI_EXT_REQUEST_CAPABILITIES_R9_CHOSEN              0
    #define         LPP_SPARE3_C1_CRITI_EXT_REQUEST_CAPABILITIES_CHOSEN          1
    #define         LPP_SPARE2_C1_CRITI_EXT_REQUEST_CAPABILITIES_CHOSEN          2
    #define         LPP_SPARE1_C1_CRITI_EXT_REQUEST_CAPABILITIES_CHOSEN          3

    union
    {
        LPP_REQUEST_CAPABILITIES_R9_IES_STRU            stRequestCapabilitiesR9;
        VOS_UINT8                                       ucSpare3;
        VOS_UINT8                                       ucSpare2;
        VOS_UINT8                                       ucSpare1;
    }u;
}LPP_CRITI_EXT_REQUEST_CAPABILITIES_STRU;

/*******************************************************************************
 结构名    : LPP_MESSAGE_REQUEST_CAPABILITIES_STRU
 结构说明  :RequestCapabilities
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    /*
    RequestCapabilities ::= SEQUENCE {
        criticalExtensions      CHOICE {
            c1                      CHOICE {
                requestCapabilities-r9      RequestCapabilities-r9-IEs,
                spare3 NULL, spare2 NULL, spare1 NULL
            },
            criticalExtensionsFuture    SEQUENCE {}
        }
    }
    */
    VOS_UINT32                                          ulChoice;

    #define           LPP_C1_CRITI_EXT_REQUEST_CAPABILITIES_CHOSEN        0
    #define           LPP_CRITI_EXT_FUTURE_REQUEST_CAPABILITIES_CHOSEN    1

    union
    {
       LPP_CRITI_EXT_REQUEST_CAPABILITIES_STRU          stC1;
       VOS_UINT8                                        ucCritiExtFuture;
    }u;
}LPP_MESSAGE_REQUEST_CAPABILITIES_STRU;

/*******************************************************************************
 结构名    : LPP_SUPPORT_MESSAGE_BODY_STRU
 结构说明  :
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    VOS_UINT32                                      ulChoice;

    #define         LPP_SUPPORT_MESSAGE_BODY_REQUEST_CAPABILITIES_CHOSEN                0
    #define         LPP_SUPPORT_MESSAGE_BODY_PROVIDE_CAPABILITIES_CHOSEN                1
    #define         LPP_SUPPORT_MESSAGE_BODY_PEQUEST_ASSISTANCE_DATA_CHOSEN             2
    #define         LPP_SUPPORT_MESSAGE_BODY_PROVIDE_ASSISTANCE_DATA_CHOSEN             3
    #define         LPP_SUPPORT_MESSAGE_BODY_REQUEST_LOCATION_INFO_CHOSEN               4
    #define         LPP_SUPPORT_MESSAGE_BODY_PROVIDE_LOCATION_INFO_CHOSEN               5
    #define         LPP_SUPPORT_MESSAGE_BODY_ABORT_CHOSEN                               6
    #define         LPP_SUPPORT_MESSAGE_BODY_ERROR_CHOSEN                               7
    #define         LPP_SUPPORT_MESSAGE_BODY_SPARE7_CHOSEN                              8
    #define         LPP_SUPPORT_MESSAGE_BODY_SPARE6_CHOSEN                              9
    #define         LPP_SUPPORT_MESSAGE_BODY_SPARE5_CHOSEN                              10
    #define         LPP_SUPPORT_MESSAGE_BODY_SPARE4_CHOSEN                              11
    #define         LPP_SUPPORT_MESSAGE_BODY_SPARE3_CHOSEN                              12
    #define         LPP_SUPPORT_MESSAGE_BODY_SPARE2_CHOSEN                              13
    #define         LPP_SUPPORT_MESSAGE_BODY_SPARE1_CHOSEN                              14
    #define         LPP_SUPPORT_MESSAGE_BODY_SPARE0_CHOSEN                              15

    union
    {
        LPP_MESSAGE_REQUEST_CAPABILITIES_STRU       stRequestCapabilities;
        LPP_MESSAGE_PROVIDE_CAPABILITIES_STRU       stProvideCapabilities;
        LPP_MESSAGE_REQUEST_ASSIST_DATA_STRU        stRequestAssistanceData;
        LPP_MESSAGE_PROVIDE_ASSIST_DATA_STRU        stProvideAssistanceData;
        LPP_MESSAGE_REQUEST_LOCATION_INFO_STRU      stRequestLocationInformation;
        LPP_MESSAGE_PROVIDE_LOCATION_INFO_STRU      stProvideLocationInformation;
        LPP_MESSAGE_ABORT_STRU                      stAbort;
        LPP_MESSAGE_ERROR_STRU                      stError;
        VOS_UINT8                                   ucSpare7;
        VOS_UINT8                                   ucSpare6;
        VOS_UINT8                                   ucSpare5;
        VOS_UINT8                                   ucSpare4;
        VOS_UINT8                                   ucSpare3;
        VOS_UINT8                                   ucSpare2;
        VOS_UINT8                                   ucSpare1;
        VOS_UINT8                                   ucSpare0;
    }u;
}LPP_SUPPORT_MESSAGE_BODY_STRU;

/*******************************************************************************
 结构名    : LPP_MESSAGE_BODY_STRU
 结构说明  :
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    VOS_UINT32                              ulChoice;

    #define             LPP_C1_MESSAGE_BODY_CHOSEN            0
    #define             LPP_C1_MESSAGE_CLASS_EXTENSION        1

    union
    {
        LPP_SUPPORT_MESSAGE_BODY_STRU       stC1;
        VOS_UINT8                           ucMessageClassExtension;
    }u;

}LPP_MESSAGE_BODY_STRU;


/*******************************************************************************
 结构名    : LPP_MESSAGE_BODY_STRU
 结构说明  :LPP_MESSAGE_STRU
 1.日    期   : 2015年07月06日
   作    者   : w00324863
*******************************************************************************/
typedef struct
{
    VOS_UINT32                              bitOpLppTransactionId:1;
    VOS_UINT32                              bitOpSequenceNumber:1;
    VOS_UINT32                              bitOpAcknowledgement:1;
    VOS_UINT32                              bitOpLppMessageBody:1;
    VOS_UINT32                              bitOpSpare:28;

    LPP_TRANSACTION_ID_STRU                 stTransactionId;
    VOS_BOOL                                bEndTransaction;
    LPP_SEQUENCE_NUMBER_STRU                stSequenceNumber;
    LPP_ACKNOWLEDGEMENT_STRU                stAcknowledgement;
    LPP_MESSAGE_BODY_STRU                   stLppMessageBody;
} LPP_MESSAGE_STRU;


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

