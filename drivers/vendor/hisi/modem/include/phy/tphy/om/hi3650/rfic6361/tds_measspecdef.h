

#ifndef __TDS_MEASSPECDEF_H__
#define __TDS_MEASSPECDEF_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include "product_config.h"
#include "TPsTPhyInterface.h"

/*#pragma pack(4)*/


/*****************************************************************************
  2 Macro
*****************************************************************************/

/*��Ƶ���������С������*/
#define TDS_MEAS_MAX_INTRA_FREQ_CELL    32

/*����������ƵС�������ܺ�:8 ����Ƶ�µ�С�������ܺͲ���32*/
#define TDS_MEAS_MAX_INTER_FREQ_CELL    32

/* ÿ��Ƶ����С���������ֵ:8 ����Ƶ+1����Ƶ��ÿ��Ƶ���µ�С��������󲻳�32*/
#define TDS_MEAS_MAX_CELL_PER_FREQ      32


/*��������С�������ܺ�:ͬƵ����Ƶ��С�������ܺ�*/
#define TDS_MEAS_MAX_CELL               (maxCellNum)

/*����������Ƶ�ʸ���*/
#define TDS_MEAS_MAX_INTER_FREQ         23

/*��������Ƶ�ʸ���:1��Ƶ + 8����Ƶ*/
#define TDS_MEAS_MAX_FREQ               ((TDS_MEAS_MAX_INTER_FREQ) + 1)

/*�������Ĵ������:6*/
#define TDS_MEAS_MAX_TRCH               (maxTrCH)

/*������������ʱ϶����*/
#define TDS_MEAS_MAX_TX_TS_NUM          (maxTS_1)

/*��������ʱ϶����:�������к�����*/
#define TDS_MEAS_MAX_TS_NUM          (7)

/*���midamble�ĸ���������ͳһ���*/
#define TDS_MEAS_BASE_MIDAMBLE_MAX_NUM      128

/*#define TDS_MEAS_MAX_PULSE_ARRAY_LEN        ((TDS_MEAS_BASE_MIDAMBLE_MAX_NUM) * 2)*/
#define TDS_MEAS_MAX_PULSE_ARRAY_LEN        (256)

/*base midamble��i��q������ܺ͸���:TDS_MEAS_BASE_MIDAMBLE_MAX_NUM*2*/
#define TDS_MEAS_BASE_MIDAMBLE_I_Q_NUM      (256)

/*rscp���������ֵ*/
#define TDS_MEAS_MAX_RSCP_PWR       0x7FFFFFFF

//#define TDS_MEAS_MAX_ISCP_PWR      0x7FFFFFFF


/*rscp�����DBֵ*/
#define TDS_MEAS_MAX_RSCP_DB        (-25)

/*rscp����СDBֵ*/
#define TDS_MEAS_MIN_RSCP_DB        (-116)

/*rscp level�����DBֵ*/
#define TDS_MEAS_MAX_RSCP_LVL        (91)

/*rscp level����СDBֵ*/
#define TDS_MEAS_MIN_RSCP_LVL        (0)


/*rssi�����DBֵ*/
#define TDS_MEAS_MAX_RSSI_DB        (-25)

/*rssi����СDBֵ*/
#define TDS_MEAS_MIN_RSSI_DB        (-100)

/*rssi level�����DBֵ*/
#define TDS_MEAS_MAX_RSSI_LVL        (76)

/*rssi level����СDBֵ*/
#define TDS_MEAS_MIN_RSSI_LVL        (0)

/*SCALE����С��������ֵ*/
#define TDS_MEAS_SCALE_VALID_THRES   (12)


/*ÿ��Ƶ������detectС������*/
#define TDS_MEAS_CS_SYNC_CELL_NUM     12

/*����Ƶ����������detectedС�������ܺ�*/
#define TDS_MEAS_DETECT_CELL_MAX_NUM   144

/*���ŵ����Ƶ����С����������*/
#define TDS_MEAS_BEST_CELL_NUM          6

/*����Ƶ�����г������С������*/
//#define TDS_MEAS_ALL_FREQ_BEST_CELL_MAX_NUM 6

#define TDS_MEAS_REBUILD_CELL_MAX_NUM       2

#define TDS_MEAS_AFC_CELL_MAX_NUM       4

//#define TDS_MEAS_OM_BEST_CELL_NUM       (TDS_MEAS_BEST_CELL_NUM)


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/


/*****************************************************************************
  5 STRUCT
*****************************************************************************/


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










/*
#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif
*/





#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of Tds_MeasSpecDef.h */
