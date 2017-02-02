/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : tds_datapath_om_def.h
  �� �� ��   : ����
  ��    ��   : mah
  ��������   : 2012��10��8��
  ����޸�   :
  ��������   : TDS  ����ͨ��OM�ӿڶ���
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��10��8��
    ��    ��   : mah
    �޸�����   : �����ļ�

******************************************************************************/
#ifndef __TDS_DATAPATH_OM_DEF_H__
#define __TDS_DATAPATH_OM_DEF_H__

#include "om_base_def.h"
/*----------------------------------------------*
 * �궨��                                       *
 *----------------------------------------------*/
#define TDS_MIDABL_CHIPLEN 144
#define TDS_DWPTS_CHIPLEN 96
/*----------------------------------------------*
 * ö�ٶ���                                       *
 *----------------------------------------------*/
typedef enum TDS_DATA_OM_REQ_MSGID
{
    TPHY_REQ_DATA_LONG_RX      =  OM_TCMD_ID(TPHY_DATA_MID, OM_TYPE_REQ, 0x1),
    TPHY_REQ_DATA_RXTS            =  OM_TCMD_ID(TPHY_DATA_MID, OM_TYPE_REQ, 0x2),
    TPHY_REQ_DATA_TXTS            =  OM_TCMD_ID(TPHY_DATA_MID, OM_TYPE_REQ, 0x3),
	TPHY_REQ_DATA_RPT_REQ             =  OM_TCMD_ID(TPHY_DATA_MID, OM_TYPE_REQ, 0x20),
}TDS_DATA_OM_REQ_MSGID_ENUM;

typedef enum TDS_DATA_OM_RPT_IND
{
    TPHY_DATA_LONGRX_IND     =  OM_TCMD_ID(TPHY_DATA_MID, OM_TYPE_IND, 0x0),   /*TDS?t???D??��3????��y*/
    TPHY_DATA_RXTS_IND         =  OM_TCMD_ID(TPHY_DATA_MID, OM_TYPE_IND, 0x1),   /*TDS��y??����???D??��3????��y*/
    TPHY_DATA_LONGTX_IND     =  OM_TCMD_ID(TPHY_DATA_MID, OM_TYPE_IND, 0x2),   /*TDS��y??tfp����?��?����??D??��3????��y*/
    TPHY_DATA_TXTS_IND         =  OM_TCMD_ID(TPHY_DATA_MID, OM_TYPE_IND, 0x3),   /*TDS��y??HSUPA?D??��3????��y*/
    TPHY_DATA_HEADER_IND      =  OM_TCMD_ID(TPHY_DATA_MID, OM_TYPE_IND, 0x20),
	TPHY_DATA_TS		      =  OM_TCMD_ID(TPHY_DATA_MID, OM_TYPE_IND, 0x21),
	TPHY_DATA_DWPTS           =  OM_TCMD_ID(TPHY_DATA_MID, OM_TYPE_IND, 0x22),
	TPHY_DATA_MIDABLE        =  OM_TCMD_ID(TPHY_DATA_MID, OM_TYPE_IND, 0x23),
	TPHY_DATA_LONG_RX_PER_1024CHIP   =  OM_TCMD_ID(TPHY_DATA_MID, OM_TYPE_IND, 0x24)

}TDS_DATA_OM_RPT_ENUM;

typedef enum   TPHY_TDS_DATA_RPT_SWICH
{
	RPT_DIABLE,
	RPT_ENABLE
}TPHY_TDS_DATA_RPT_SWICH_ENUM;

typedef struct TPHY_TDS_DATA_RPT_REQ
{
	TPHY_TDS_DATA_RPT_SWICH_ENUM enReportAll;
	TPHY_TDS_DATA_RPT_SWICH_ENUM enReportTS;
	TPHY_TDS_DATA_RPT_SWICH_ENUM enReportDwpts;
	TPHY_TDS_DATA_RPT_SWICH_ENUM enReportMidable;
	TPHY_TDS_DATA_RPT_SWICH_ENUM enReportLongRxdata;
}TPHY_TDS_DATA_RPT_REQ_STRU;

typedef struct TDSP_TRACE_INFO
{
   UINT32 ulData[2];
}TPHY_TDS_TRACE_INFO_STRU;

typedef enum TDS_DATA_RPT_TYPE
{
    NOMAL_TDS_TS_DATA,
	DWPTS_DATA,
	MIDABL_DATA,
	LONG_RX_1024CHIP_DATA
}TDS_DATA_RPT_TYPE_ENUM;

typedef struct TPHY_TDS_DATA_RPT_HEADER
{
    UINT16 usSFN;
	UINT16 usTsNum;
	UINT32 usTimeStick;    /*��o?��??����*/
	TDS_DATA_RPT_TYPE_ENUM enDataType;
}TPHY_TDS_DATA_RPT_HEADER_STRU;
typedef struct TPHY_TDS_DATA_TS
{
	//TPHY_TDS_DATA_RPT_HEADER_STRU stHeader;
	UINT32 usData[TDS_TS_DATA_CHIPLEN];
}TPHY_TDS_DARA_TS_STRU;

typedef struct TPHY_TDS_DATA_DWPTS
{
	//TPHY_TDS_DATA_RPT_HEADER_STRU stHeader;
	UINT32 usData[TDS_DWPTS_CHIPLEN+32];
}TPHY_TDS_DARA_DWPTS_STRU;

typedef struct TPHY_TDS_DATA_MIDABL
{
	//TPHY_TDS_DATA_RPT_HEADER_STRU stHeader;
	UINT32 usData[TDS_MIDABL_CHIPLEN];
}TPHY_TDS_DARA_MIDABL_STRU;

typedef struct TPHY_TDS_DATA_1024CHIP
{
	//TPHY_TDS_DATA_RPT_HEADER_STRU stHeader;
	UINT32 usData[1024];
}TPHY_TDS_DARA_1024CHIP_STRU;
/*----------------------------------------------*
 * �ṹ�嶨��                                     *
 *----------------------------------------------*/
typedef struct TPHY_REQ_DATA_RX_LONG
{
    OM_REQ_ENABLE_ENUM_UINT16  enDatReqEna;   /*��ȡTDS  ��������ʹ�ܿ��أ�ǰ�˽������ݴ�ʱ��Ч*/
    UINT16 usTotalGain;
    UINT16 usFreq;
    UINT16 usFourthFastFlg;
}TPHY_REQ_DATA_RX_LONG_STRU;

typedef struct TPHY_REQ_DATA_RXTS
{
    OM_REQ_ENABLE_ENUM_UINT16  enIntStatInfoEna; /*��ȡTDS �ض�ʱ϶��������ʹ�ܿ��أ�ǰ�˽������ݴ�ʱ������Ч�����ݲɼ����ر�*/
    UINT16 usTs;    /*ʱ϶��*/
    UINT16 usTotalGain;
    UINT16 usFreq;
    UINT16 usFourthFastFlg;
    UINT16 usRes;
}TPHY_REQ_DATA_RXTS_STRU;

typedef struct TPHY_REQ_DATA_TXTS
{
    OM_REQ_ENABLE_ENUM_UINT16  enIntStatInfoEna; /*��ȡTDS �ض�ʱ϶��������ʹ�ܿ��أ�ǰ�˽������ݴ�ʱ������Ч�����ݲɼ����ر�*/
    UINT16 usTs;    /*ʱ϶��*/
    UINT16 usTxPow;
    UINT16 usFreq;
}TPHY_REQ_DATA_TXTS_STRU;

typedef struct TPHY_DATA_OM_CTRL
{
    UINT16 usLongRxTaskFlg; /*���ó��ձ��*/
    UINT16 usTdsOmEn;
}TPHY_DATA_OM_CTRL_STRU;

/*BEGIN: by humin, 2015/05/07*/
#if 1
/*BEGIN: by humin, 2015/05/08*/
typedef enum
{
    ABB_RX_ON_ONLY,
	ABB_TX_ON_ONLY,
	ABB_BOTH_ON,
	ABB_NO_NEED_CONFIG,
}ABB_LPC_CONFIG_IND_ENUM;
typedef UINT16 ABB_LPC_CONFIG_IND_ENUM_UINT16;

typedef enum
{
    TDS_DATA_PATH_INIT_STATE = 0,
    TDS_DATA_PATH_CON_RX_START_STATE,    //������
    TDS_DATA_PATH_CON_RX_STOP_STATE,     //�س���
    TDS_DATA_PATH_TS_NORMAL_RX_STATE,    //��������ģʽ
    TDS_DATA_PATH_TS_FAST_RX_STATE,     //Data0��mid���ν���
    TDS_DATA_PATH_TS_TX_STATE,

}TDS_DATA_PATH_STATE_ENUM;

typedef UINT16 TDS_DATA_PATH_STATE_ENUM_UINT16;

typedef enum
{
    TDS_CUR_FRAME = 0,
    TDS_NXT_FRAME,
    TDS_FRAME_BUTT,
}TDS_FRAME_TYPE_ENUM;
typedef UINT16 TDS_FRAME_TYPE_ENUM_UINT16;

typedef enum
{
    TDS_TS0 = 0,
    TDS_DwPts,
    TDS_UwPts,
    TDS_TS1,
    TDS_TS2,
    TDS_TS3,
    TDS_TS4,
    TDS_TS5,
    TDS_TS6,
    TDS_TS_BUTT
}TDS_TS_ENUM;
typedef UINT16 TDS_TS_ENUM_UINT16;
/*END: by humin, 2015/05/08*/

typedef enum
{
    TDS_MEAS_REQ_ID = 0x1,
    TDS_ICS_REQ_ID = 0x2,
    TDS_DCH_VEL_REQ_ID = 0x4,
    TDS_UPLINK_REQ_ID = 0x8,
    TDS_MODU_REQ_ID = 0x10,
    TDS_TIMING_REQ_ID = 0x20,
    TDS_INTERIRATMEAS_REQ_ID = 0x40,
}TDS_DATA_PATH_LOG_IN_ID;
typedef UINT32 TDS_DATA_PATH_LOG_IN_ID_UINT32;

typedef struct
{
    UINT32 ulTdsFreq;
    INT32 lRfStartTime;
    INT32 lRfEndTime;  //RF��Чʱ������λchip
    TDS_DATA_PATH_STATE_ENUM_UINT16 usTdsDataPathState;
    UINT16 usFourthFastFlg;//�ı��ٲ�����0xffffΪ1���٣�1Ϊ4����ʹ��
    INT16 usTdsPowerValue; //dBm��λ
    ABB_LPC_CONFIG_IND_ENUM_UINT16 usAbbState;
    UINT16 usCurChipNum;
    UINT16 usCurSlotNum;
}TDS_DATA_PATH_CONFIG_PARA_STRU;

typedef struct
{
    TDS_DATA_PATH_LOG_IN_ID_UINT32 ulTdsModuReqID;
    TDS_FRAME_TYPE_ENUM_UINT16 usTdsFrameType;
    TDS_TS_ENUM_UINT16 usTdsTsNum;  //��Ҫ��Ч��2Ts��

    TDS_DATA_PATH_CONFIG_PARA_STRU stTdsDataPathConfig;
}TDS_DATA_PATH_LOG_IN_STRU;
#endif
/*END: by humin, 2015/05/07*/
/*----------------------------------------------*
 * �ⲿ����˵��                                 *
 *----------------------------------------------*/

/*----------------------------------------------*
 * �ⲿ����ԭ��˵��                             *
 *----------------------------------------------*/

/*----------------------------------------------*
 * �ڲ�����ԭ��˵��                             *
 *----------------------------------------------*/



/*----------------------------------------------*
 * ȫ�ֱ���                                     *
 *----------------------------------------------*/

/*----------------------------------------------*
 * ģ�鼶����                                   *
 *----------------------------------------------*/

#endif
