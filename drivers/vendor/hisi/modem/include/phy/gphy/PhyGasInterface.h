/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : PhyGasInterface.h
  �� �� ��   : ����
  ��    ��   : ����
  ��������   : 2007��9��5��
  ����޸�   :
  ��������   : ��ͷ�ļ���Э��ջ�������֮��Ľӿ��ļ���
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2007��9��5��
    ��    ��   : ����
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __PHYGASINTERFACE_H__
#define __PHYGASINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "EdgeInterface.h"
#include "PhyGrrInterface.h"
#include "PhyGasComm.h"


/*****************************************************************************
  2 �궨��
*****************************************************************************/
#pragma pack(1)


/********************* �ṹMPH_RXLEV_REQ_STRU �������ȡֵ ******************/
#define SEARCH_FREQ_BA_MAX_NUM                      ( 500 )                      /* ָ��Ƶ������ʱ�����������������Ƶ����Ŀ */


/*****************************  WCDMA��غ궨��  ****************************/
#define MAX_INTER_CARRIER_NUM                       ( 3 )
#define MAX_INTER_FREQ_INFO_NUM                     ( 32 )

/*****************  �ṹMPH_CELL_RESELECT_REQ_STRU ��ʹ�õĺ� ***************/
#define GSM_STRONGEST_FREQLIST_NUM                  ( 6 )

/******************  ԭ��MPH_MEAS_REPORT_IND ��ʹ�õĺ� *********************/
#define GAS_GCOM_DTX_USED                           ( 1 )
#define GAS_GCOM_DTX_UNUSED                         ( 0 )
#define MPH_MEAS_REPORT_IND_CHANNEL_NUM_MAX         ( 32 )


/********************* ���ݽṹ��usERRCode���������ĺ궨�� ******************/
#define    PHY_SUCCESS                              ( 0 )
#define    PHY_FAILURE                              ( 1 )
#define    PHY_START_TIME_ELAPSED                   ( 2 )


/******************  �ṹMPH_UPDATE_PAGING_PARA_REQ_STRU��ʹ�õĺ� **********/
#define GSM_IMSI_MAX_LEN                            ( 15 )
#define GSM_IMEI_LEN                                ( 15 )
#define GSM_IMEISV_LEN                              ( 16 )


/*********  �ṹMPH_NCELL_RESULT_IND_STRU��MPH_MEAS_REPORT_REQ��ʹ�õĺ� ****/
#define PHY_REPORT_REASON_INIT_NCELL                ( 0x00000001 )              /* ֪ͨ��ʼ����ǿ��С�� */
#define PHY_REPORT_REASON_DSC_FAIL                  ( 0x00000002 )              /* ������·ʧ�� */
#define PHY_REPORT_REASON_RESEL_C1                  ( 0x00000004 )              /* C1����5sС��0 */
#define PHY_REPORT_REASON_RESEL_C2                  ( 0x00000008 )              /* NCELL��SCELL�źź�ʱ */
#define PHY_REPORT_REASON_3G_MEAS                   ( 0x00000010 )              /* ��ϵͳ�������� */
#define PHY_REPORT_REASON_NCELL_CHANGE              ( 0x00000020 )              /* �����ı� */
#define PHY_REPORT_REASON_SCELL_RXLEV               ( 0x00000040 )              /* ����С��ǿ�ȸı� */
#define PHY_REPORT_REASON_RANDOM_ACC_FAIL           ( 0x00000080 )              /* �ϲ��������ʧ�� */
#define PHY_REPORT_REASON_NC_MEAS                   ( 0x00000100 )              /* NC��������(�������Ų���) */
#define PHY_REPORT_REASON_DEDICATED_MEAS            ( 0x00000200 )              /* ר��̬�������� */

#define PHY_REPORT_REASON_NAS_REQUEST               ( 0x00001000 )              /* NAS����С����ѡ*/
#define PHY_REPORT_REASON_GRR_N3102                 ( 0x00002000 )              /* GRR N3102����С����ѡ*/
#define PHY_REPORT_REASON_SCELL_SI_ACQU_FAIL        ( 0x00004000 )              /* GCOMSI ��ȡ����С��ϵͳ��Ϣʧ��*/
#define PHY_REPORT_REASON_SCELL_BARRED              ( 0x00008000 )              /* ����С������*/
#define PHY_REPORT_REASON_RXLEV_REQUST              ( 0x00010000 )              /* ����С���Լ������ϱ�*/
#define PHY_REPORT_REASON_GRR_ACCESS_FAILURE        ( 0x00020000 )              /* GRR �������ʧ������С����ѡ*/

#define PHY_REPORT_REASON_THRESH_GSM_LOW            ( 0x00040000 )              /* ����С������ǿ����������thresh_gsm_low���޵��������Ӳ����㵽����ʱ�ϱ� */
#define PHY_REPORT_REASON_SCELL_TIMING_ERR          ( 0x00080000 )              /* ����С����ʱ���� */

/******  ԭ��PHY_REPORT_REASON_NCELL_CHANGE����ԭ��Я�����ϲ���ڹ۲� *****/
#define PHY_CHANGE_RESON_FIRST_BUILD                ( 0x01000000 )              /* ��һ�ι���С���ϱ���С���ı� */
#define PHY_CHANGE_RESON_UPDATE_BALIST              ( 0x02000000 )              /* BA�����ϱ���С���ı� */
#define PHY_CHANGE_RESON_ENTER_NCELL                ( 0x04000000 )              /* ��С����Χ��ǿ��С�� */
#define PHY_CHANGE_RESON_OUT_NCELL                  ( 0x08000000 )              /* С���߳���ǿ��С�� */
#define PHY_CHANGE_RESON_BSIC_FAIL                  ( 0x10000000 )              /* С��ͬ��BSICʧ�� */
#define PHY_CHANGE_RESON_BSIC_SUCC                  ( 0x20000000 )              /* С��ͬ��BSIC�ɹ� */
#define PHY_CHANGE_RESON_BSIC_CHANGE                ( 0x40000000 )              /* С��ͬ��BSIC�ı� */
#define PHY_CHANGE_RESON_NCC_PERMIT                 ( 0x80000000 )              /* С��ͬ��BSIC��ֹ */

/************************  GASȫ��ϵͳ��Ϣ��TCBitmap ************************/
#define GAS_GPHY_START_BCCH_REDADING_BITMAP_FULL    ( 0xA9FF )

#define GAS_GCOM_PHY_PARAM_INVALID_VALUE            ( 0xFFFF )                  /* ��Чֵ����Ҫ���ڱ�����DSP������ص���Чֵ���Ա��ڸ��²�����DSPʱ��ֱ�Ӹ�ֵ */

#define PHY_GAS_MAX_G_SLAVE_GSM_CELL_NUM            ( 64 )                      /* G��ģ״̬�²���GSMС�������� */
#define PHY_GAS_MAX_G_SLAVE_GSM_BSIC_CELL_NUM       ( 8 )                       /* G��ģ״̬��BSIC��֤GSMС���������� */

#define PHY_GAS_TIMING_OFFSET_FN_INVALID_VALUE      ( 0x7FFFFFFF )              /* ��Чֵ����ʱ����FN����Чֵ */
#define PHY_GAS_TIMING_OFFSET_QB_INVALID_VALUE      ( 0x7FFF )                  /* ��Чֵ����ʱ����QB����Чֵ */

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/


typedef enum
{
    GSM_PAGE_MODE_NORMAL                            =   0,
    GSM_PAGE_MODE_EXT                               =   1,
    GSM_PAGE_MODE_REORG                             =   2,
    GSM_PAGE_MODE_SAME                              =   3
}GSM_PAGE_MODE_ENUM;
typedef VOS_UINT16 GSM_PAGE_MODE_ENUM_UINT16;


typedef enum
{
    GAS_PHY_CHANNEL_MODE_SIGNALLING_ONLY    = 0,
    GAS_PHY_CHANNEL_MODE_TCH_FS             = 1,
    GAS_PHY_CHANNEL_MODE_TCH_EFR            = 2,
    GAS_PHY_CHANNEL_MODE_TCH_AFS            = 3,
    GAS_PHY_CHANNEL_MODE_TCH_F24            = 4,
    GAS_PHY_CHANNEL_MODE_TCH_F48            = 5,
    GAS_PHY_CHANNEL_MODE_TCH_F96            = 6,
    GAS_PHY_CHANNEL_MODE_TCH_F144           = 7,
    GAS_PHY_CHANNEL_MODE_TCH_HS             = 8,
    GAS_PHY_CHANNEL_MODE_TCH_AHS            = 9,
    GAS_PHY_CHANNEL_MODE_TCH_H24            = 10,
    GAS_PHY_CHANNEL_MODE_TCH_H48            = 11,
    GAS_PHY_CHANNEL_MODE_TCH_WFS            = 12,

    GAS_PHY_CHANNEL_MODE_BUTT
}GAS_PHY_CHANNEL_MODE_ENUM;
typedef VOS_UINT16 GAS_PHY_CHANNEL_MODE_ENUM_UINT16;


typedef enum
{
    GAS_PHY_ABType_8bit                             =   0,
    GAS_PHY_ABType_11bit                            =   1
}GAS_PHY_ABType_ENUM;
typedef VOS_UINT16 GAS_PHY_ABType_ENUM_UINT16;



typedef enum
{
    GAS_PHY_RA_TSC0                                 =   0,
    GAS_PHY_RA_TSC1                                 =   1
}GAS_PHY_RA_ENUM;
typedef VOS_UINT16 GAS_PHY_RA_ENUM_UINT16;



typedef enum
{
    GSM_CBCH_TYPE_BASIC                             =   0,                      /* BASIC CBCH �ŵ� */
    GSM_CBCH_TYPE_EXT                               =   1,                      /* EXT   CBCH �ŵ� */
    GSM_CBCH_TYPE_BUTT
}GSM_CBCH_TYPE_ENUM;
typedef VOS_UINT16 GSM_CBCH_TYPE_ENUM_UINT16;



typedef enum
{
    GSM_CBCH_SCHEDULE_INFO_INVALID                  =   0,                      /* CBCH�ŵ�������Ϣ��Ч */
    GSM_CBCH_SCHEDULE_INFO_VALID                    =   1,                      /* CBCH�ŵ�������Ϣ��Ч */
    GSM_CBCH_SCHEDULE_INFO_BUTT
}GSM_CBCH_SCHEDULE_INFO_ENUM;
typedef VOS_UINT16 GSM_CBCH_SCHEDULE_INFO_ENUM_UINT16;



typedef enum
{
    GAS_PHY_NETLOST_CASUE_NORMAL                    =   0,
    GAS_PHY_NETLOST_CASUE_G_INACTIVE                =   1
}GAS_PHY_NETLOST_CASUE_ENUM;
typedef VOS_UINT16 GAS_PHY_NETLOST_CASUE_ENUM_UINT16;



typedef enum
{
    PHY_MONI_AGCH_FLG_NEEDLESS                      =   0,
    PHY_MONI_AGCH_FLG_NEED                          =   1
}PHY_MONI_AGCH_FLG_ENUM;
typedef VOS_UINT16 PHY_MONI_AGCH_FLG_ENUM_UINT16;


enum GAS_PHY_BG_SEARCH_ENUM
{
    GAS_PHY_BG_SEARCH_START             = 0,
    GAS_PHY_BG_SEARCH_STOP              = 1,

    GAS_PHY_BG_SEARCH_BUTT
};
typedef VOS_UINT16 GAS_PHY_BG_SEARCH_ENUM_UINT16;


enum PHY_GAS_HO_RESULT_ENUM
{
    PHY_GAS_HO_RESULT_SUCCESS               = 0,        /* �л��ɹ� */
    PHY_GAS_HO_RESULT_TAOUTRANGE            = 1,        /* �л�ʧ��: TA OUTRANGE */
    PHY_GAS_HO_RESULT_TIMEOUT               = 2,        /* �л�ʧ��: TIMEOUT */
    PHY_GAS_HO_RESULT_OTHERS                = 3,        /* �л�ʧ��: ����ԭ��ֵ */

    PHY_GAS_HO_RESULT_BUTT
};
typedef VOS_UINT16 PHY_GAS_HO_RESULT_ENUM_UINT16;



enum PHY_GAS_COMM_FLAG_ENUM
{
    PHY_GAS_COMM_FLAG_FALSE             = 0,        /* ���򿪻򲻴��� */
    PHY_GAS_COMM_FLAG_TRUE              = 1,        /* �򿪻���� */

    PHY_GAS_COMM_FLAG_BUTT
};
typedef VOS_UINT16 PHY_GAS_COMM_FLAG_ENUM_UINT16;

/*****************************************************************************
 ö����    : PHY_GAS_MEAS_COMMAND_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ������������
*****************************************************************************/
enum PHY_GAS_MEAS_COMMAND_ENUM
{
    PHY_GAS_MEAS_COMMAND_RELEASE          = 0,            /*�����ͷ�*/
    PHY_GAS_MEAS_COMMAND_SETUP            = 1,            /*�������������䶼�ô�����,����2000*/

    PHY_GAS_MEAS_COMMAND_BUTT
};
typedef  VOS_UINT16 PHY_GAS_MEAS_COMMAND_ENUM_UINT16;

/*****************************************************************************
 ö����    : PHY_GAS_VERIFY_TIME_INDEX_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ������INDEX��Ӧ��ϵ����������ģģʽ��AS͸��ö��ֵ��ȷ
*****************************************************************************/
enum PHY_GAS_VERIFY_TIME_INDEX_ENUM
{
    PHY_GAS_VERIFY_TIME_INDEX_0                          = 0,
    PHY_GAS_VERIFY_TIME_INDEX_1                             ,
    PHY_GAS_VERIFY_TIME_INDEX_2                             ,
    PHY_GAS_VERIFY_TIME_INDEX_3                             ,
    PHY_GAS_VERIFY_TIME_INDEX_4                             ,
    PHY_GAS_VERIFY_TIME_INDEX_5                             ,
    PHY_GAS_VERIFY_TIME_INDEX_6                             ,
    PHY_GAS_VERIFY_TIME_INDEX_7                             ,
    PHY_GAS_VERIFY_TIME_INDEX_8                             ,

    PHY_GAS_VERIFY_TIME_INDEX_BUTT
};
typedef VOS_UINT16 PHY_GAS_VERIFY_TIME_INDEX_ENUM_UINT16;


enum PHY_GAS_MASTER_MODE_STATUS_ENUM
{
    PHY_GAS_MASTER_MODE_STATUS_IDLE                             = 0,            /* ����W��ģEN_RRC_RR_WAS_STATUS_IDLE��T��ģTRRC_GRR_MEAS_TAS_STATUS_IDLE��L��ģIDLE */
    PHY_GAS_MASTER_MODE_STATUS_URA_PCH                             ,            /* ����W��ģEN_RRC_RR_WAS_STATUS_URA_PCH��T��ģTRRC_GRR_MEAS_TAS_STATUS_URA_PCH */
    PHY_GAS_MASTER_MODE_STATUS_CELL_PCH                            ,            /* ����W��ģEN_RRC_RR_WAS_STATUS_CELL_PCH��T��ģTRRC_GRR_MEAS_TAS_STATUS_CELL_PCH */
    PHY_GAS_MASTER_MODE_STATUS_FACH                                ,            /* ����W��ģEN_RRC_RR_WAS_STATUS_FACH��T��ģTRRC_GRR_MEAS_TAS_STATUS_FACH */
    PHY_GAS_MASTER_MODE_STATUS_DCH                                 ,            /* ����W��ģEN_RRC_RR_WAS_STATUS_DCH��T��ģTRRC_GRR_MEAS_TAS_STATUS_DCH��L��ģCONN */

    PHY_GAS_MASTER_MODE_STATUS_BUTT
};
typedef VOS_UINT16 PHY_GAS_MASTER_MODE_STATUS_ENUM_UINT16;
enum PHY_GAS_STOP_MEAS_TYPE_ENUM
{
    PHY_GAS_STOP_MEAS_TYPE_ABNORMAL         = 0,        /* �쳣ֹͣ���� */
    PHY_GAS_STOP_MEAS_TYPE_NORMAL           = 1,        /* ����ֹͣ���� */

    PHY_GAS_STOP_MEAS_TYPE_BUTT
};
typedef VOS_UINT16 PHY_GAS_STOP_MEAS_TYPE_ENUM_UINT16;


enum PHY_GAS_BUSINESS_TYPE_ENUM
{
    PHY_GAS_BUSINESS_TYPE_NORMAL        = 0,          /* ����ģʽ */
    PHY_GAS_BUSINESS_TYPE_CT            = 1,
    PHY_GAS_BUSINESS_TYPE_NO_SIG_BT     = 2,
    PHY_GAS_BUSINESS_TYPE_SIG_BT        = 3,
    PHY_GAS_BUSINESS_TYPE_BUTT
};
typedef VOS_UINT16 PHY_GAS_BUSINESS_TYPE_ENUM_UINT16;
enum PHY_GAS_GSM_BANDINDICATOR_ENUM
{
    PHY_GAS_GSM_BANDINDICATOR_DCS1800   = 0,
    PHY_GAS_GSM_BANDINDICATOR_PCS1900      ,

    PHY_GAS_GSM_BANDINDICATOR_BUTT
};
typedef VOS_UINT16 PHY_GAS_GSM_BANDINDICATOR_ENUM_UINT16;


enum PHY_GAS_SCELL_BCCH_READ_TYPE_ENUM
{
    PHY_GAS_SCELL_BCCH_READ_TYPE_RESEL          = 0,        /* ��ѡ�����з���С��ϵͳ��Ϣ��ȡ */
    PHY_GAS_SCELL_BCCH_READ_TYPE_ENH            = 1,        /* ��ǿ���չ�����ϵͳ��Ϣ��ȡ */
    PHY_GAS_SCELL_BCCH_READ_TYPE_PERIOD         = 2,        /* �����Խ��չ�����ϵͳ��Ϣ��ȡ */

    PHY_GAS_SCELL_BCCH_READ_TYPE_BUTT
};
typedef VOS_UINT16 PHY_GAS_SCELL_BCCH_READ_TYPE_ENUM_UINT16;
enum PHY_GAS_NCELL_BCCH_READ_TYPE_ENUM
{
    PHY_GAS_NCELL_BCCH_READ_TYPE_RESEL          = 0,        /* ��ѡ��������С��ϵͳ��Ϣ��ȡ */
    PHY_GAS_NCELL_BCCH_READ_TYPE_DECODE         = 1,        /* ��С�����������ϵͳ��Ϣ��ȡ */
    PHY_GAS_NCELL_BCCH_READ_TYPE_BG             = 2,        /* �����ѹ�����ϵͳ��Ϣ��ȡ */

    PHY_GAS_NCELL_BCCH_READ_TYPE_BUTT
};
typedef VOS_UINT16 PHY_GAS_NCELL_BCCH_READ_TYPE_ENUM_UINT16;
enum PHY_GAS_BCCH_READING_ACT_ENUM
{
    PHY_GAS_BCCH_READING_STOP                   = 0,        /* ֹͣ��ȡϵͳ��Ϣ,���������ȡ���� */
    PHY_GAS_BCCH_READING_START                  = 1,        /* ������ȡϵͳ��Ϣ,����BitMap��ȡ,BitMapΪ0ʱ,��ʱ����ȡ */
    PHY_GAS_BCCH_READING_BUTT
};
typedef VOS_UINT16 PHY_GAS_BCCH_READING_ACT_ENUM_UINT16;





enum PHY_GAS_BCCH_READING_CELL_TYPE_ENUM
{
    PHY_GAS_BCCH_READING_CELL_TYPE_SCELL        = 0,        /* ��ȡ����С��ϵͳ��Ϣ,��ӦSCELL BCCH */
    PHY_GAS_BCCH_READING_CELL_TYPE_PCELL        = 1,        /* ��ȡ��ѡС��ϵͳ��Ϣ,��ӦSTART BCCH */
    PHY_GAS_BCCH_READING_CELL_TYPE_BUTT
};
typedef VOS_UINT16 PHY_GAS_BCCH_READING_CELL_TYPE_ENUM_UINT16;

/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/


typedef struct
{
    PHY_GAS_MSG_ID_ENUM_UINT16              usMsgID;                            /* _H2ASN_MsgChoice_Export      PHY_GAS_MSG_ID_ENUM_UINT16 */
    VOS_UINT8                               aucMsgBlock[4];
    /******************************************************************************************************
        _H2ASN_MsgChoice_When_Comment          PHY_GAS_MSG_ID_ENUM_UINT16
    ******************************************************************************************************/
}PHY_GAS_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    PHY_GAS_MSG_DATA                        stMsgData;
}PhyGasInterface_MSG;


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/

/**************************5.1 NULL״̬�µ�ԭ��******************************/

/*****************************************************************************
 ��Ϣ����  : MPHC_NETWORK_LOST_REQ_STRU
 ��������  : ��С��ѡ��ʧ�ܺ�RR����ԭ���L1����������յ���ԭ��ʹL1����
             NULL״̬����״̬Ϊ�͹���״̬����״̬��Ҫ��DRX�ļ���״̬ͳһ����)��
 �޸���ʷ  :
  1.��    ��   : 2007��09��29��
    ��    ��   : fangjian(48555)
    �޸�����   : �����ɽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GAS_MSG_ID_ENUM_UINT16              usMsgID;                            /* _H2ASN_Skip */ /* ԭ������ */
    GAS_PHY_NETLOST_CASUE_ENUM_UINT16       usCause;                            /* 0: NORMAL, 1: G Inactive */
} MPHC_NETWORK_LOST_REQ_STRU;


/*****************************************************************************
 ��Ϣ����  : MPHC_NETWORK_LOST_CNF_STRU
 ��������  : MPHC_NETWORK_LOST_REQ��ȷ��ԭ�
 �޸���ʷ  :
  1.��    ��   : 2007��09��29��
    ��    ��   : fangjian(48555)
    �޸�����   : �����ɽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GAS_MSG_ID_ENUM_UINT16              usMsgID;                            /* _H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                              usRsv;
} MPHC_NETWORK_LOST_CNF_STRU;


/**********************5.2 Searching BCH״̬�µ�ԭ��*************************/

typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GAS_MSG_ID_ENUM_UINT16              usMsgID;                            /* _H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                              usFreqBand;                         /* ָ��Ƶ�� */
    VOS_UINT16                              usFreqNum;                          /* 0��ʾ��Ҫ����ָ��Ƶ�� */
    VOS_UINT16                              usFreqInfo[SEARCH_FREQ_BA_MAX_NUM];
} MPH_RXLEV_REQ_STRU;



typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GAS_MSG_ID_ENUM_UINT16              usMsgID;                            /* _H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                              usFreqNum;
    RXLEV_MEAS_STRU                         astRxlevResult[SEARCH_SEND_FREQ_INFO_NUM];
} MPH_RXLEV_CNF_STRU;

#define MPH_BCCH_READ_ADDI_ACT_MASK_DEFAULT_ACTION                      (0x0000)
#define MPH_BCCH_READ_ADDI_ACT_MASK_NO_NEED_TO_SYNC                     (0x0001)
#define MPH_BCCH_READ_ADDI_ACT_MASK_NO_NEED_TO_LOCK_AFC                 (0x0002)

/*****************************************************************************
 ��Ϣ����   : MPH_START_BCCH_READING_STRU
 ��������   : ��С��ѡ������У�RR���и�����Ƶ�ĵ�ƽ��RR����ԭ���L1����
              �Ը���Ƶ��ͬ������ȡBCCH��Ϣ��
 �޸���ʷ   :
  1.��    ��    : 2007��09��10��
    ��    ��    : fangjian(48555)
    �޸�����    : �����ɽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GAS_MSG_ID_ENUM_UINT16              usMsgID;                            /* _H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                              usFreqInfo;
    VOS_UINT16                              usSIBitMap;
    VOS_UINT16                              usAddiActMask;                      /* bit0: 1:��������ͬ��;    0:��Ҫ����ͬ��
                                                                                   bit1: 1:������������AFC; 0:��Ҫ��������AFC */
} MPH_START_BCCH_READING_STRU;


/*****************************************************************************
 ��Ϣ����  : MPH_CELL_SB_IND_STRU
 ��������  : ��С��ѡ������У�L1��ȡBCCHʧ�ܺ�������Ϣ��GAS
 �޸���ʷ  :
  1.��    ��    : 2007��10��31��
    ��    ��    : fangjian(48555)
    �޸�����    : �����ɽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GAS_MSG_ID_ENUM_UINT16              usMsgID;                            /* _H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                              usFreqInfo;
    VOS_UINT16                              usErrCode;                          /* 0��Success��1��SB Fail��2��AFC Fail */
    VOS_UINT16                              usBsic;
} MPH_CELL_SB_IND_STRU;
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GAS_MSG_ID_ENUM_UINT16              usMsgID;                            /* _H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                              usERRCode;
    VOS_UINT16                              usFreqInfo;
    VOS_UINT16                              usTC;
    VOS_UINT32                              ulFN;
} MPH_BCCH_READ_FAIL_IND_STRU;


/*****************************************************************************
 ��Ϣ����  : MPH_STOP_BCCH_READING_STRU
 ��������  : ������յ�ԭ��MPH_STOP_BCCH_READINGֹͣ��BCCH���̡���ԭ��Ӧ����
             С��ѡ������С�
 �޸���ʷ  :
  1.��    ��    : 2007��09��10��
    ��    ��    : fangjian(48555)
    �޸�����    : �����ɽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GAS_MSG_ID_ENUM_UINT16              usMsgID;                            /* _H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                              usFreqInfo;
} MPH_STOP_BCCH_READING_STRU;


/**************************5.3 BCH״̬�µ�ԭ��*******************************/

/*****************************************************************************
 ��Ϣ����  : MPH_RA_REQ_STRU
 ��������  : ���ͽ�������
 �޸���ʷ  :
  1.��    ��   : 2007��9��28��
    ��    ��   : fangjian (48555)
    �޸�����   : �޸�ԭ�нṹ��PH_RA_REQΪMPH_RA_REQ_STRU
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GAS_MSG_ID_ENUM_UINT16              usMsgID;                            /* _H2ASN_Skip */ /* ԭ������ */
    GAS_PHY_ABType_ENUM_UINT16              usABType;
    GAS_PHY_RA_ENUM_UINT16                  usTsc;                              /* 8PSK������TSC1��GMSK������TSC0 */
    VOS_UINT16                              usTXPwr;
    VOS_UINT16                              usPowerClassGSM;
    VOS_UINT16                              usPowerclassDCS;
    VOS_UINT16                              usRand;
    VOS_UINT16                              usChanReq;
} MPH_RA_REQ_STRU;


/*****************************************************************************
 ��Ϣ����  : PH_RA_REQ_STRU
 ��������  : ���ͽ�������
 �޸���ʷ  :
  1.��    ��   : 2007��9��28��
    ��    ��   : fangjian (48555)
    �޸�����   : �޸�ԭ�нṹ��PH_RA_REQΪMPH_RA_REQ_STRU
*****************************************************************************/
/* Ϊ�˼���Moiri�Ķ��� */
typedef MPH_RA_REQ_STRU PH_RA_REQ_STRU;
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GAS_MSG_ID_ENUM_UINT16              usMsgID;                            /* _H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                              usRASuccess;                        /* 0��ʧ�ܣ�1���ɹ� */
    VOS_UINT32                              ulFN;
    GAS_PHY_ABType_ENUM_UINT16              usRaBurstType;
    VOS_UINT16                              usChanReq;
} MPH_RA_CNF_STRU;


/*****************************************************************************
 ��Ϣ����  : PH_RA_CNF_STRU
 ��������  : ����Ϣ PH_RA_REQ_STRU �Ļظ�
 �޸���ʷ  :
  1.��    ��   : 2007��9��28��
    ��    ��   : fangjian (48555)
    �޸�����   : �޸�ԭ�нṹ��PH_RA_CNF_STRUΪMPH_RA_CNF_STRU
*****************************************************************************/
/* Ϊ�˼���Moiri�Ķ��� */
typedef MPH_RA_CNF_STRU PH_RA_CNF_STRU;
typedef struct
{
    VOS_INT32                               lTimingOffsetFn;    /* ����FN����Ч��Χ[-2715647, 2715647],��ЧֵPHY_GAS_TIMING_OFFSET_FN_INVALID_VALUE */
    VOS_INT16                               sTimingOffsetQb;    /* ����Qb����Ч��Χ[-4999, 4999]����ЧֵPHY_GAS_TIMING_OFFSET_QB_INVALID_VALUE */
    VOS_UINT16                              ausReserved[1];     /* ����λ */
}PHY_GAS_INTERRAT_TO_GSM_TIMING_INFO_STRU;

/*****************************************************************************
 ��Ϣ����  : MPH_CELL_RESELECT_REQ_STRU
 ��������  : ������յ�ԭ��MPH_CELL_RESELECT_REQ�����һ���µ��ŵ�����������
             ����С����
 �޸���ʷ  :
  1.��    ��    : 2007��09��10��
    ��    ��    : fangjian(48555)
    �޸�����    : �����ɽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GAS_MSG_ID_ENUM_UINT16                  usMsgID;                        /* _H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usFreInfo;
    VOS_UINT16                                  usSyncValid;                    /* �����ͬ����Ϣ�Ƿ���Ч */
    VOS_UINT16                                  usTimeAlignment;                /* ��С����ԭ��С��֮���QNOFFSET�ģ5000����Чֵ��Χ[0,4999],��Чֵ:0xFFFF */
    VOS_UINT32                                  ulFnOffset;                     /* ��С����ԭ��С��֮���FN�ģ2715648,��Чֵ��Χ[0,2715647],��Чֵ:0xFFFFFFFF */
    VOS_UINT16                                  usBSIC;
    VOS_UINT16                                  usReserved;                     /* ����λ */
    VOS_RATMODE_ENUM_UINT32                     enResel2GsmRatType;             /* ��ѡ��GSM�Ľ���ģʽ���ͣ�CCOʹ�ã���ѡ���̲�ʹ�� */
    PHY_GAS_INTERRAT_TO_GSM_TIMING_INFO_STRU    stInterRat2GsmTimingOffset;     /* ��ϵͳ��GSM�Ķ�ʱ������Ϣ��CCOʹ�ã���ѡ���̲�ʹ�� */
} MPH_CELL_RESELECT_REQ_STRU;


/*****************************************************************************
 ��Ϣ����  : MPH_BA_LIST_STRU
 ��������  : ��BCH̬��MS��Ҫ���Ӳ�����6����ǿ�����źţ�L3ͨ��MPH_BA_LISTԭ��
             ����L1 BA�б�L1���������ڴ��У�Ȼ��ʼ�����Բ�����
 �޸���ʷ  :
  1.��    ��   : 2007��09��10��
    ��    ��   : fangjian(48555)
    �޸�����   : �����ɽṹTBD
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usNumOfChans;
    VOS_UINT16                              usRsv;                              /* ����λ */
    VOS_UINT16                              ausA[32];
} BCCH_LIST_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GAS_MSG_ID_ENUM_UINT16              usMsgID;                            /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                              usRsv;                              /* ����λ */
    BCCH_LIST_STRU                          stBCCHAllocation;
} MPH_BA_LIST_STRU;


/*****************************************************************************
 ��Ϣ����  : MPH_BA_LIST_CNF_STRU
 ��������  : MPH_BA_LIST��ȷ��ԭ�
 �޸���ʷ  :
  1.��    ��   : 2007��10��06��
    ��    ��   : fangjian(48555)
    �޸�����   : �����ɽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GAS_MSG_ID_ENUM_UINT16              usMsgID;                            /* _H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                              usRsv;
} MPH_BA_LIST_CNF_STRU;

/*****************************************************************************
 ��Ϣ����  : MPH_SCELL_BCCH_READ_STRU
 ��������  : L3��ԭ��MPH_SCELL_BCCH_READ����L1������С��BCCH�ϵ�ϵͳ��Ϣ��
             L1������ͨ��ԭ��PH_DATA_IND�ϱ�L3��
 �޸���ʷ  :
  1.��    ��   : 2007��09��10��
    ��    ��   : fangjian(48555)
    �޸�����   : �����ɽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GAS_MSG_ID_ENUM_UINT16                  usMsgID;                        /* _H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usSIBitMap;                     /* ϵͳ��Ϣ��ȡ��λͼ */
    PHY_GAS_SCELL_BCCH_READ_TYPE_ENUM_UINT16    enReadType;                     /* ϵͳ��Ϣ��ȡ������ */
    VOS_UINT16                                  usReserved;                     /* ����λ */
} MPH_SCELL_BCCH_READ_STRU;

/*****************************************************************************
 ��Ϣ����  : MPH_NCELL_BCCH_READ_STRU
 ��������  : L3��ԭ��MPH_NCELL_BCCH_READ����L1������BCCH�ϵ�ϵͳ��Ϣ��
             L1������ͨ��ԭ��PH_DATA_IND�ϱ�L2��
 �޸���ʷ  :
  1.��    ��   : 2007��09��10��
    ��    ��   : fangjian(48555)
    �޸�����   : �����ɽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GAS_MSG_ID_ENUM_UINT16                  usMsgID;                        /* _H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usFreqInfo;                     /* Ƶ����Ϣ */
    VOS_UINT16                                  usSIBitMap;                     /* ϵͳ��Ϣ��ȡ��λͼ */
    VOS_UINT16                                  usBSIC;                         /* BSIC��Ϣ */
    VOS_UINT32                                  ulFNOffset;                     /* ֡ƫ�� */
    VOS_UINT16                                  usTimeAlignmt;                  /* ʱ��ƫ�� */
    PHY_GAS_NCELL_BCCH_READ_TYPE_ENUM_UINT16    enReadType;                     /* ϵͳ��Ϣ��ȡ������ */
} MPH_NCELL_BCCH_READ_STRU;

/*****************************************************************************
 ��Ϣ����  : MPH_SCELL_BCCH_READ_CNF_STRU
 ��������  : L3��ԭ��MPH_SCELL_BCCH_READ����L1������С��BCCH�ϵ�ϵͳ��Ϣ��
             ��ԭ����MPH_SCELL_BCCH_READ�Ļظ���
 �޸���ʷ  :
  1.��    ��   : 2007��10��31��
    ��    ��   : fangjian(48555)
    �޸�����   : �����ɽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GAS_MSG_ID_ENUM_UINT16              usMsgID;                            /* _H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                              usERRCode;
} MPH_SCELL_BCCH_READ_CNF_STRU;


/*****************************************************************************
 ��Ϣ����  : MPH_FULL_LIST_REQ_STRU
 ��������  : L3��ԭ��MPH_FULL_LIST����L1����ȫ���ز����ò������Ժ����ڲ���ͬʱ���ڡ�
 �޸���ʷ  :
  1.��    ��   : 2007��09��07��
    ��    ��   : fangjian(48555)
    �޸�����   : �ϲ�MPH_BAND_SELECT_REQ_STRU������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GAS_MSG_ID_ENUM_UINT16              usMsgID;                            /* _H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                              usBandSelect;                       /* MS֧�ֵ�GSMƵ�� */
    VOS_UINT16                              ausMSClass[5];                      /* ��Ƶ�ζ�Ӧ�Ĺ��ʵȼ� */
    VOS_UINT16                              usRsv;                              /* �����ֶ� */
} MPH_FULL_LIST_REQ_STRU;


/*****************************************************************************
 ��Ϣ����  : MPH_FULL_LIST_CNF_STRU
 ��������  : ��ԭ����L1����MPH_FULL_LIST��ȷ�ϡ�
 �޸���ʷ  :
  1.��    ��   : 2007��09��14��
    ��    ��   : fangjian(48555)
    �޸�����   : �����ɽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GAS_MSG_ID_ENUM_UINT16              usMsgID;                            /* _H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                              usERRCode;                          /* ������ */
} MPH_FULL_LIST_CNF_STRU;


/*****************************************************************************
 ��Ϣ����  : MPH_SI_UPDATE_REQ_STRU
 ��������  : L3��ԭ��MPH_SI_UPDATE_REQ����L1����ϵͳ��Ϣ����ԭ��
             MPH_SI_UPDATE_CNFȷ�ϡ�
 �޸���ʷ  :
  1.��    ��   : 2007��09��10��
    ��    ��   : fangjian(48555)
    �޸�����   : �����ɽṹ
  2.��    ��    : 2007��11��01��
    ��    ��    : fangjian(48555)
    �޸�����    : �������������usPAGE_GROUP�޸�ΪusPAGE_MULTIFRAME51_INDEX
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usChannelType;                      /* 1=TCH_F, 2=TCH_H, 3=SDCCH_4, 4=SDCCH_8 */
    VOS_UINT16                              usSubchannel;
    VOS_UINT16                              usTimeslotNumber;
    VOS_UINT16                              usTSC;
    VOS_UINT16                              usHOPING;
    VOS_UINT16                              usFreInfo;
    VOS_UINT16                              usMAIO;
    VOS_UINT16                              usHSN;
} CHANNEL_DESCRIPTION_STRU;


typedef struct
{
    VOS_UINT16                              usBS_PA_MFRMS;
    VOS_UINT16                              usBS_AG_BLOCK_RES;
    VOS_UINT16                              usBS_CC_CHANS;
    VOS_UINT16                              usBS_CCCH_SDCCH_COMB;
    VOS_UINT16                              usCCCH_GROUP;
    VOS_UINT16                              usPAGE_MULTIFRAME51_INDEX;          /* Ѱ�����ڵڼ���51��֡, 45.002 6.5.3 */
    VOS_UINT16                              usPAGE_BLOCK_INDEX;
    VOS_UINT16                              usMS_TXPWR_MAX_CCH;
    VOS_UINT16                              usLB_MS_TXPWR_MAX_CCH;              /* 0xFFFF��ʾ��Ч */
    VOS_UINT16                              usPOWER_OFFSET;
    VOS_UINT16                              usPowerClassGSM;
    VOS_UINT16                              usPowerclassDCS;
    VOS_UINT16                              usTX_Integer;
    VOS_UINT16                              usSplitPageCycle;
    VOS_UINT16                              usCBCHINFOVALID;
    VOS_UINT16                              usReserved;                         /* ���ֽڶ��뱣�� */
    CHANNEL_DESCRIPTION_STRU                stCHCHINFO;
} SI_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GAS_MSG_ID_ENUM_UINT16              usMsgID;                            /* _H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                              usRsv;                              /* ����λ */
    SI_STRU                                 stSIInfo;
} MPH_SI_UPDATE_REQ_STRU;


/*****************************************************************************
 ��Ϣ����  : MPH_SI_UPDATE_CNF_STRU
 ��������  : L3��ԭ��MPH_ SI_UPDATE_REQ����L1����ϵͳ��Ϣ����ԭ��
             MPH_ SI_UPDATE_CNFȷ�ϡ�
 �޸���ʷ  :
  1.��    ��   : 2007��09��10��
    ��    ��   : fangjian(48555)
    �޸�����   : �����ɽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GAS_MSG_ID_ENUM_UINT16              usMsgID;                            /* _H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                              usERRCode;
} MPH_SI_UPDATE_CNF_STRU;


/************************5.4  DCH״̬�µ�ԭ��********************************/

/*****************************************************************************
 ��Ϣ����  : MPH_IMMED_ASSIGN_REQ_STRU
 ��������  : L1����L3������ԭ��MPH_IMMED_ASSIGN_REQ������Ϣ�������ŵ���ȫ����Ϣ��
             L1����������ŵ�����Ϊǰ��û���ŵ�����ԭ��ָ����ŵ�ֻ���������ŵ���
 �޸���ʷ  :
  1.��    ��   : 2007��09��10��
    ��    ��   : fangjian(48555)
    �޸�����   : �����ɽṹ
  2.��    ��   : 2007��10��12��
    ��    ��   : fangjian(48555)
    �޸�����   : ����Before time��ص��ŵ��ṹ�ͱ�־λ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usRFChanCnt;
    VOS_UINT16                              usRsv;
    VOS_UINT16                              ausMA[63+1];
} MOBILE_ALLOCATION_STRU;

typedef struct
{
    VOS_UINT16                              usStartTimePresent;
    VOS_UINT16                              usT1;
    VOS_UINT16                              usT2;
    VOS_UINT16                              usT3;
} STARTING_TIME_STRU;

typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GAS_MSG_ID_ENUM_UINT16              usMsgID;                            /* _H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                              usTA;
    VOS_UINT16                              usDTX;
    VOS_UINT16                              usBeforeChanMark;                   /* 0:�����ڣ�1:���� */
    CHANNEL_DESCRIPTION_STRU                stBeforeChanDesc;                   /* BEFORE TIME���ŵ����� */
    MOBILE_ALLOCATION_STRU                  stBeforeFreqList;                   /* BEFORE TIME��Ƶ���б� */
    CHANNEL_DESCRIPTION_STRU                stChanDesc;
    MOBILE_ALLOCATION_STRU                  stFreqList;
    STARTING_TIME_STRU                      stStartTime;
    BCCH_LIST_STRU                          stBCCHAllocation;
} MPH_IMMED_ASSIGN_REQ_STRU;


/*****************************************************************************
 ��Ϣ����  : MPH_IMMED_ASSIGN_CNF_STRU
 ��������  : ����ϢMPH_IMMED_ASSIGN_REQ�Ļظ�
 �޸���ʷ  :
  1.��    ��   : 2007��09��10��
    ��    ��   : fangjian(48555)
    �޸�����   : �����ɽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GAS_MSG_ID_ENUM_UINT16              usMsgID;                            /* _H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                              usERRCode;
} MPH_IMMED_ASSIGN_CNF_STRU;


/*****************************************************************************
 ��Ϣ����  : MPH_CHANNEL_ASSIGN_REQ_STRU
 ��������  : L1����L3������ԭ��MPH_CHANNEL_ASSIGN_REQ������Ϣ�������ŵ���ȫ��
             ��Ϣ��L1����������ŵ�����ԭ��ָ����ŵ��������κ��ŵ�����ԭ��ʹ
             �õ�ǰ����MS�Ѿ�������һЩר���ŵ��ϡ�
 �޸���ʷ  :
  1.��    ��   : 2007��09��10��
    ��    ��   : fangjian(48555)
    �޸�����   : �����ɽṹ
*****************************************************************************/
typedef struct
{
    VOS_INT16                               sThreshold;
    VOS_INT16                               sHysteresis;
} AMRPARA;

typedef struct
{
    VOS_UINT16                              usLength;
    VOS_UINT16                              usMRVersion;
    VOS_UINT16                              usNSCB;
    VOS_UINT16                              usICMI;
    VOS_UINT16                              usStartMode;
    VOS_UINT16                              usSetofAMRCodecModes;
    AMRPARA                                 ustAmrPara[3];
} AMR_CONFIG_STRU;

typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GAS_MSG_ID_ENUM_UINT16              usMsgID;                            /* _H2ASN_Skip */ /* ԭ������ */
    GAS_PHY_CHANNEL_MODE_ENUM_UINT16        usChanMode;                         /* 0-Signalling Only,1-TCH/FS,2-TCH/EFR,3-TCH/AFS,4-TCH/F24
                                                                                   5-TCH/F48,6-TCH/F96,7-TCH/F144,8-TCH/HS,9-TCH/AHS,
                                                                                   10-TCH/H24,11-TCH/H48, 12-TCH/WFS */
    VOS_UINT16                              usTXPwr;
    VOS_UINT16                              usCipherMode;
    VOS_UINT16                              ausCipherKey[4];
    VOS_UINT16                              usDTX;
    VOS_UINT16                              usBeforeChanMark;                   /* 0:�����ڣ�1:���� */
    CHANNEL_DESCRIPTION_STRU                stBeforeChanDesc;                   /* BEFORE TIME���ŵ����� */
    MOBILE_ALLOCATION_STRU                  stBeforeFreqList;                   /* BEFORE TIME��Ƶ���б� */
    STARTING_TIME_STRU                      stStartTime;
    CHANNEL_DESCRIPTION_STRU                stChanDesc;                         /* AFTER TIME���ŵ����� */
    MOBILE_ALLOCATION_STRU                  stFreqList;                         /* AFTER TIME��Ƶ���б� */
    AMR_CONFIG_STRU                         stAMR_CONFIG;
} MPH_CHANNEL_ASSIGN_REQ_STRU;


/*****************************************************************************
 ��Ϣ����  : MPH_CHANNEL_ASSIGN_CNF_STRU
 ��������  : ��ϢMPH_CHANNEL_ASSIGN_REQ�Ļظ�
 �޸���ʷ  :
  1.��    ��   : 2007��09��10��
    ��    ��   : fangjian(48555)
    �޸�����   : �����ɽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GAS_MSG_ID_ENUM_UINT16              usMsgID;                            /* _H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                              usERRCode;
} MPH_CHANNEL_ASSIGN_CNF_STRU;


/*****************************************************************************
 ��Ϣ����  : MPH_HO_REQ_STRU
 ��������  : L1���Խ���ԭ��MPH_ HO_REQ��ʾͬ���л���Ԥͬ���л���αͬ���л���
             �첽�л���ǰ�����л�L1����4������burst����һ���첽�л�L1������burst
             ֱ��������ɣ��첽�л�ʱ������һ��RA���RR��MPH_ASYNC_HO_CNF��
             �����FACCH���յ�PHYSICAL INFORMATION��Ϣ���ʱ��T3124��ʱ��
             RR��L1��MPH_ABORT_HO_RA_REQ����L1���������burst�󣬻�ԭ��
             MPH_HANDOVER_FINISHED��L3��
 �޸���ʷ  :
  2.��    ��   : 2007��09��14��
    ��    ��   : fangjian(48555)
    �޸�����   : �����ɽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usNCC;
    VOS_UINT16                              usBCC;
    VOS_UINT16                              usBCCHARFCN;
} CELL_DESC_STRU;

typedef struct
{
    VOS_UINT16                              usBSIC;
    VOS_UINT16                              usBCCHARFCN;
    VOS_UINT16                              usChanMode;                         /* 0-Signalling Only,1-TCH/FS,2-TCH/EFR,3-TCH/AFS,4-TCH/F24
                                                                                   5-TCH/F48,6-TCH/F96,7-TCH/F144,8-TCH/HS,9-TCH/AHS,
                                                                                   10-TCH/H24,11-TCH/H48, 12-TCH/WFS */
    VOS_UINT16                              usHOAcc;
    VOS_UINT16                              usTXPwr;
    VOS_UINT16                              usCipherMode;
    VOS_UINT16                              ausCipherKey[4];
    VOS_UINT16                              usBeforeChanMark;                   /* 0:�����ڣ�1:���� */
    VOS_UINT16                              usRsv;
    CHANNEL_DESCRIPTION_STRU                stBeforeChanDesc;                   /* BEFORE TIME���ŵ����� */
    MOBILE_ALLOCATION_STRU                  stBeforeFreqList;                   /* BEFORE TIME��Ƶ���б� */
    STARTING_TIME_STRU                      stStartTime;
    CHANNEL_DESCRIPTION_STRU                stAfterChanDesc;                    /* AFTER TIME���ŵ����� */
    MOBILE_ALLOCATION_STRU                  stAfterFreqList;                    /* AFTER TIME��Ƶ���б� */
} HO_PARAMS_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GAS_MSG_ID_ENUM_UINT16                  usMsgID;                        /* _H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usHOType;                       /* �л�����: 1-ASYNC, 2-SYNC
                                                                                4-PRE_SYNC, 8-PSEUDO_SYNC */
    HO_PARAMS_STRU                              stHOCom;
    VOS_UINT32                                  ulFNOffset;                     /* ��Чֵ��Χ[0,2715647],��Чֵ:0xFFFFFFFF */
    VOS_UINT16                                  usTimeAlignmt;                  /* ��Чֵ��Χ[0,4999],��Чֵ:0xFFFF */
    VOS_UINT16                                  usReserved;                     /* ����λ */
    VOS_RATMODE_ENUM_UINT32                     enHo2GsmRatType;                /* HO��GSM�Ľ���ģʽ���� */
    PHY_GAS_INTERRAT_TO_GSM_TIMING_INFO_STRU    stInterRat2GsmTimingOffset;     /* ��ϵͳ��GSM�Ķ�ʱ������Ϣ */
    VOS_UINT16                                  usTA;
    VOS_UINT16                                  usNCI;
    VOS_UINT16                                  usRTDValid;
    VOS_UINT16                                  usRTD;
    AMR_CONFIG_STRU                             stAMR_CONFIG;
} MPH_HO_REQ_STRU;
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    VOS_UINT16                              usMsgID;                            /* _H2ASN_Skip */ /*��ϢID��MPH_BHO_NCELL_FB_SB_REQ*/
    VOS_UINT16                              usFreqInfo;                         /* С��Ƶ�㣬����Ƶ��MARK*/
} MPH_BHO_NCELL_FB_SB_REQ_STRU;
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    VOS_UINT16                              usMsgID;                            /* _H2ASN_Skip */ /*��ϢID��MPH_BHO_NCELL_FB_SB_CNF */
    VOS_UINT16                              usFreqInfo;                         /* С��Ƶ�㣬����Ƶ��MARK */
    VOS_UINT16                              usSBFoundFlag;                      /* 1����ʾ����SB��0����ʾ���SBʧ�� */
    VOS_UINT16                              usBSIC;                             /* �������BSIC */
    VOS_UINT32                              ulFNOffset;                         /* ֡ƫ�� */
    VOS_UINT16                              usTimeAlignmt;                      /* ʱ��ƫ�� */
    VOS_UINT16                              usRsv;                              /* ����ֶ� */
} MPH_BHO_NCELL_FB_SB_CNF_STRU;



typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    VOS_UINT16                              usMsgID;                            /* _H2ASN_Skip */ /*��ϢID��MPH_BHO_NCELL_FB_SB_CNF */
    VOS_UINT16                              usFreqInfo;                         /* С��Ƶ�㣬����Ƶ��MARK */
} MPH_STOP_BHO_NCELL_FB_SB_REQ_STRU;
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    VOS_UINT16                              usMsgID;                            /* _H2ASN_Skip */ /*��ϢID��MPH_BHO_NCELL_FB_SB_CNF */
    VOS_UINT16                              usRsved;                            /* ����ֶ�*/
} MPH_STOP_BHO_NCELL_FB_SB_CNF_STRU;


/*****************************************************************************
 ��Ϣ����  : MPH_ASYNC_HO_CNF_STRU
 ��������  : �첽�л�����һ��RA burst���RR��MPH_ASYNC_HO_CNF
 �޸���ʷ  :
  1.��    ��   : 2007��09��10��
    ��    ��   : fangjian(48555)
    �޸�����   : �����ɽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GAS_MSG_ID_ENUM_UINT16              usMsgID;                            /* _H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                              usERRCause;
} MPH_ASYNC_HO_CNF_STRU;


/*****************************************************************************
 ��Ϣ����  : MPH_ABORT_HO_RA_REQ_STRU
 ��������  : �ڷ�ͬ���л��У�RR�յ��Ե�ʵ���������Ϣ��ʱ����ʱ������L1ֹͣ
             ����RA��ֹͣ��BCCH��CCCH��ͬʱӦ��TAֵ�����ڵ��ŵ���
 �޸���ʷ  :
  1.��    ��   : 2007��09��10��
    ��    ��   : fangjian(48555)
    �޸�����   : �����ɽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GAS_MSG_ID_ENUM_UINT16              usMsgID;                            /* _H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                              usAbortCause;
    VOS_UINT16                              usTA;
    VOS_UINT16                              usRsv;
} MPH_ABORT_HO_RA_REQ_STRU;


/*****************************************************************************
 ��Ϣ����  : MPH_HANDOVER_FINISHED_STRU
 ��������  : L1���������burst�󣬻�ԭ��MPH_HANDOVER_FINISHED��L3
 �޸���ʷ  :
  1.��    ��   : 2007��09��10��
    ��    ��   : fangjian(48555)
    �޸�����   : �����ɽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GAS_MSG_ID_ENUM_UINT16              usMsgID;                            /* _H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                              usHOType;
    VOS_UINT16                              usOTA;
    PHY_GAS_HO_RESULT_ENUM_UINT16           enERRCause;                         /* �л���� */
} MPH_HANDOVER_FINISHED_STRU;


/*****************************************************************************
 ��Ϣ����  : MPH_HANDOVER_COMPLETE_STRU
 ��������  : RR�յ�LAPDm��DL_RESUME_CNF��, ֪ͨ������л��Ѿ�����,����ɾ���������ʷ�ŵ�����Ϣ
 �޸���ʷ  :
  1.��    ��   : 2006��03��06��
    ��    ��   : zhanghongjun(49106)
    �޸�����   : �����ɽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GAS_MSG_ID_ENUM_UINT16              usMsgID;                            /* _H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                              usCause;                            /* �����ֶ�, Ŀǰ�ݲ�ʹ��, Ŀǰֻ��0x00*/
} MPH_HANDOVER_COMPLETE_STRU;


/*****************************************************************************
 ��Ϣ����  : MPH_HANDOVER_FAIL_REQ_STRU
 ��������  : L1���Խ���ԭ��MPH_HANDOVER_FAIL_REQ���˵��л�ǰ���ŵ���
 �޸���ʷ  :
  1.��    ��   : 2007��09��10��
    ��    ��   : fangjian(48555)
    �޸�����   : �����ɽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GAS_MSG_ID_ENUM_UINT16              usMsgID;                            /* _H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                              usBSIC;
    VOS_UINT16                              usBCCHARFCN;
    VOS_UINT16                              usChanMode;                         /* 0-Signalling Only,1-TCH/FS,2-TCH/EFR,3-TCH/AFS,4-TCH/F24
                                                                                   5-TCH/F48,6-TCH/F96,7-TCH/F144,8-TCH/HS,9-TCH/AHS,
                                                                                   10-TCH/H24,11-TCH/H48, 12-TCH/WFS */
    VOS_UINT16                              usTXPwr;
    VOS_UINT16                              usCipherMode;
    VOS_UINT16                              ausCipherKey[4];
    VOS_UINT16                              usDTX;
    VOS_UINT16                              usTA;
    VOS_UINT16                              usRsv;                              /* ����λ */
    VOS_UINT16                              usTimeAlignmt ;                     /* 0xFFFF=��Чֵ */
    VOS_UINT32                              ulFNOffset ;                        /* 0xFFFFFF=��Чֵ */
    CHANNEL_DESCRIPTION_STRU                stChanDesc;
    MOBILE_ALLOCATION_STRU                  stFreqList;
    STARTING_TIME_STRU                      stStartTime;
    AMR_CONFIG_STRU                         stAMR_CONFIG;
} MPH_HANDOVER_FAIL_REQ_STRU;


/*****************************************************************************
 ��Ϣ����  : MPH_HANDOVER_FAIL_CNF_STRU
 ��������  : ����ϢMPH_HANDOVER_FAIL_REQ�Ļظ���ע������ĳɹ�������������
             ���ŵ�����ɹ���������ʾ�ŵ����˳ɹ���
 �޸���ʷ  :
  1.��    ��   : 2007��09��10��
    ��    ��   : fangjian(48555)
    �޸�����   : �����ɽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GAS_MSG_ID_ENUM_UINT16              usMsgID;                            /* _H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                              usERRCode;
} MPH_HANDOVER_FAIL_CNF_STRU;


/*****************************************************************************
 ��Ϣ����  : MPH_CHANNEL_MODE_MODIFY_REQ_STRU
 ��������  : L1���Խ���ԭ��MPH_CHANNEL_MODE_MODIFY_REQ�޸�ר���ŵ�ģʽ��
 �޸���ʷ  :
  1.��    ��   : 2007��09��10��
    ��    ��   : fangjian(48555)
    �޸�����   : �����ɽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GAS_MSG_ID_ENUM_UINT16              usMsgID;                            /* _H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                              usChanMode;
    VOS_UINT16                              usDTX;
    VOS_UINT16                              usRsv;
    CHANNEL_DESCRIPTION_STRU                stChanDesc;
    AMR_CONFIG_STRU                         stAMRInterface;
} MPH_CHANNEL_MODE_MODIFY_REQ_STRU;


/*****************************************************************************
 ��Ϣ����  : MPH_CHANNEL_MODE_MODIFY_CNF_STRU
 ��������  : ��MPH_CHANNEL_MODE_MODIFY_REQ�Ļظ�
 �޸���ʷ  :
  1.��    ��   : 2007��09��10��
    ��    ��   : fangjian(48555)
    �޸�����   : �����ɽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GAS_MSG_ID_ENUM_UINT16              usMsgID;                            /* _H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                              usERRCode;
} MPH_CHANNEL_MODE_MODIFY_CNF_STRU;


/*****************************************************************************
 ��Ϣ����  : MPH_SET_CIPHERING_REQ_STRU
 ��������  : �ı��ŵ�����ģʽ
 �޸���ʷ  :
  1.��    ��   : 2007��09��10��
    ��    ��   : fangjian(48555)
    �޸�����   : �����ɽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GAS_MSG_ID_ENUM_UINT16              usMsgID;                            /* _H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                              usCipherMode;
    VOS_UINT16                              ausCipherKey[4];
} MPH_SET_CIPHERING_REQ_STRU;


/*****************************************************************************
 ��Ϣ����  : MPH_SET_CIPHERING_CNF_STRU
 ��������  : ����ϢMPH_SET_CIPHERING_REQ�Ļظ�
 �޸���ʷ  :
  1.��    ��   : 2007��09��10��
    ��    ��   : fangjian(48555)
    �޸�����   : �����ɽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GAS_MSG_ID_ENUM_UINT16              usMsgID;                            /* _H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                              usERRCode;
} MPH_SET_CIPHERING_CNF_STRU;


/*****************************************************************************
 ��Ϣ����  : MPH_CHANGE_FREQUENCY_REQ_STRU
 ��������  : �ı���ƵƵ��
 �޸���ʷ  :
  1.��    ��   : 2007��09��10��
    ��    ��   : fangjian(48555)
    �޸�����   : �����ɽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GAS_MSG_ID_ENUM_UINT16              usMsgID;                            /* _H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                              usTransactionID;
    STARTING_TIME_STRU                      stStartTime;
    CHANNEL_DESCRIPTION_STRU                stChanDesc;
    MOBILE_ALLOCATION_STRU                  stFreqList;
} MPH_CHANGE_FREQUENCY_REQ_STRU;


/*****************************************************************************
 ��Ϣ����  : MPH_CHANGE_FREQUENCY_CNF_STRU
 ��������  : ����ϢMPH_CHANGE_FREQUENCY_REQ�Ļظ�
 �޸���ʷ  :
  1.��    ��   : 2007��09��10��
    ��    ��   : fangjian(48555)
    �޸�����   : �����ɽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GAS_MSG_ID_ENUM_UINT16              usMsgID;                            /* _H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                              usTransactionID;
    VOS_UINT16                              usERRCode;
    VOS_UINT16                              usRsv;
} MPH_CHANGE_FREQUENCY_CNF_STRU;


/*****************************************************************************
 ��Ϣ����  : MPH_STOP_DEDICATED_REQ_STRU
 ��������  : L1���Խ���ԭ��MPH_STOP_DEDICATED_REQ�ͷ�ר���ŵ������ָʾBCCH
             ����ʹ�ã��͸����ڸ�BCCH�ϣ�����ȴ�RR֪ͨ����С��������������
             �����ŵ���
 �޸���ʷ  :
  1.��    ��   : 2007��09��10��
    ��    ��   : fangjian(48555)
    �޸�����   : �����ɽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GAS_MSG_ID_ENUM_UINT16              usMsgID;                            /* _H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                              usBCCHFreValid;
    VOS_UINT16                              usFreqInfo;
    VOS_UINT16                              usBSIC;
} MPH_STOP_DEDICATED_REQ_STRU;



typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GAS_MSG_ID_ENUM_UINT16              usMsgID;                            /* _H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                              usERRCode;
    VOS_UINT16                              usTA;                               /* ��ϵͳ�л�ʧ�ܺ󣬻��˵�ԭ�ŵ�ʱʹ�� */
    VOS_UINT16                              usTimeAlignmt;
    VOS_UINT32                              ulFNOffset;
} MPH_STOP_DEDICATED_CNF_STRU;


/*****************************************************************************
 ��Ϣ����  : MPH_CS_DEDICATED_MEAS_IND_STRU
 ��������  : �ϱ�������ƽ�����L3����ͨ��MPH_BA_LISTԭ�����L1����BA�б�L1
             ֹͣ���ڵĲ��������º����³�ʼ���������ݣ���ʼ������
 �޸���ʷ  :
  1.��    ��    : 2007��09��11��
    ��    ��    : jiajing(55331)
    �޸�����    : ɾ��usNumFullBlkMeas��usNumSubBlkMeas��usNumBitMeasFull��usNumBitMeasSub
                   �����ֱ���ϱ������͵�ƽ�����ȼ�,��������BSIC��Ϣ
  2.��    ��    : 2007��10��12��
    ��    ��    : fangjian(48555)
    �޸�����    : ����usWMeasMark��־
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usArfcn;                            /* ��С������Ƶ */
    VOS_UINT16                              usRxlev;                            /* ��С�����źŲ���ֵ */
    VOS_UINT16                              usSyncMark;                         /* ����С���Ƿ����ͬ����Ϣ 1:���� 0:������ */
    VOS_UINT16                              usBsic;                             /* ��С����BSIC */
    VOS_UINT32                              ulFNOffset;                         /* ��С���뵱ǰ����С����֡ƫ�� */
    VOS_UINT16                              usTimeAlignmt;                      /* ��С���뵱ǰ����С��ʱ��ƫ�� */
    VOS_INT16                               sOrder;                             /* ��С����������. */
} GSM_STRONG_NCELL_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GAS_MSG_ID_ENUM_UINT16              usMsgID;                            /* _H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                              usDTX;
    VOS_UINT16                              usRxlevFull;                        /* �ź�ǿ��+ƫ��(316) */
    VOS_UINT16                              usRxlevSub;                         /* �ź�ǿ��+ƫ��(316) */
    VOS_UINT16                              usFrmNumFull;                       /* FULL���ĵ�ƽͳ��֡�� */
    VOS_UINT16                              usFrmNumSub;                        /* SUB���ĵ�ƽͳ��֡�� */
    VOS_UINT16                              usErrBitsFull;                      /* FULL��������BIT�� */
    VOS_UINT16                              usErrBitsSub;                       /* SUB��������BIT�� */
    VOS_UINT16                              usTotalBitsFull;                    /* FULL���ܵı����� */
    VOS_UINT16                              usTotalBitsSub;                     /* SUB���ܵı����� */
    VOS_UINT16                              usRxLevVal;
    VOS_UINT16                              usMeanBep;
    VOS_UINT16                              usCvBep;
    VOS_UINT16                              usNbrRcvdBlocks;
    VOS_UINT16                              usRsv;
    VOS_UINT16                              usNChanNum;
    GSM_STRONG_NCELL_STRU                   astNcellInfo[GSM_STRONGEST_FREQLIST_NUM];   /* �����ϱ������������Ϣ */
} MPH_CS_DEDICATED_MEAS_IND_STRU;


/*****************************************************************************
 ��Ϣ����  : MPH_CHANGE_DTX_REQ_STRU
 ��������  : ��ר��ģʽ��RR����ı�DTX��ʽ���������������
 �޸���ʷ  :
  1.��    ��   : 2007��09��23��
    ��    ��   : fangjian(48555)
    �޸�����   : �����ɽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GAS_MSG_ID_ENUM_UINT16              usMsgID;                            /* _H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                              usDTX;
} MPH_CHANGE_DTX_REQ_STRU;


/*****************************************************************************
 ��Ϣ����  : MPH_CHANGE_DTX_CNF_STRU
 ��������  : ��ר��ģʽ��RR����ı�DTX��ʽ���Ը�ԭ��Ӧ��
 �޸���ʷ  :
  1.��    ��   : 2007��09��23��
    ��    ��   : fangjian(48555)
    �޸�����   : �����ɽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GAS_MSG_ID_ENUM_UINT16              usMsgID;                            /* _H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                              usDTX;
} MPH_CHANGE_DTX_CNF_STRU;


/******************************5.6 ������ԭ��********************************/

/*****************************************************************************
 ��Ϣ����  : MPH_PAGING_MODE_REQ_STRU
 ��������  : ��ԭ�����ڿ���������޸�Ѱ��ģʽ����֪ͨ�����פ��Ŀ��С����
 �޸���ʷ  :
  1.��    ��    : 2007��09��06��
    ��    ��    : fangjian(48555)
    �޸�����    : �����ɽṹ
  2.��    ��    : 2007��10��12��
    ��    ��    : fangjian(48555)
    �޸�����    : �������������usPAGE_GROUP�޸�ΪusPAGE_MULTIFRAME51_INDEX
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GAS_MSG_ID_ENUM_UINT16              usMsgID;                            /* _H2ASN_Skip */ /* ԭ������ */
    GSM_PAGE_MODE_ENUM_UINT16               enPageMode;                         /* Ѱ��ģʽ */
    VOS_UINT16                              usBS_PA_MFRMS;                      /* Ѱ��������51��֡������ */
    VOS_UINT16                              usBS_AG_BLKS_REGS;                  /* ÿ��CCCH��AGCH�������� */
    VOS_UINT16                              usBCCH_COMBINED;                    /* CCCH�Ƿ���SDCCH���,0����ϣ�1��� */
    VOS_UINT16                              usCCCH_GROUP;                       /* CCCH_GROUP��45.002 6.5.2,[0 .. BS_CC_CHANS-1] */
    VOS_UINT16                              usPAGE_MULTIFRAME51_INDEX;          /* Ѱ�����ڵڼ���51��֡, 45.002 6.5.3 */
    VOS_UINT16                              usPAGE_BLOCK_INDEX;                 /* 51��֡��PAGE BLOCK ��INDEX */
} MPH_PAGING_MODE_REQ_STRU;


/*****************************************************************************
 ��Ϣ����  : MPH_PAGING_MODE_CNF_STRU
 ��������  : ��ԭ��������������Э��ջMPH_PAGING_MODE_REQԭ��Ļظ�
 �޸���ʷ  :
  1.��    ��    : 2007��09��07��
    ��    ��    : fangjian(48555)
    �޸�����    : �����ɽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GAS_MSG_ID_ENUM_UINT16              usMsgID;                            /* _H2ASN_Skip */ /* ԭ������ */
    GSM_PAGE_MODE_ENUM_UINT16               enPageMode;                         /* Ѱ��ģʽ */
} MPH_PAGING_MODE_CNF_STRU;


/*****************************************************************************
 ��Ϣ����  : MPH_UPDATE_PARSE_PAGING_PARA_REQ_STRU
 ��������  : ��ԭ������
 �޸���ʷ  :
  1.��    ��    : 2007��09��06��
    ��    ��    : fangjian(48555)
    �޸�����    : �����ɽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GAS_MSG_ID_ENUM_UINT16              usMsgID;                            /* _H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                              usReserved;
    VOS_UINT32                              ulTlli;                             /* �·����µ�TLLIֵ */
    VOS_UINT16                              usTmsiFlag;                         /* TMSI���ڱ��,1:valid,0:invalid */
    VOS_UINT16                              usPtmsiFlag;                        /* PTMSI���ڱ��,1:valid,0:invalid */
    VOS_UINT32                              ulTmsi;
    VOS_UINT32                              ulPtmsi;
    VOS_UINT16                              usImsiFlag;                         /* IMSI���ڱ��,1:valid,0:invalid */
    VOS_UINT16                              usImsiLen;                          /* IMSI ռ�õĳ��� */
    VOS_UINT16                              ausImsi[GSM_IMSI_MAX_LEN];          /* IMSI  */
    VOS_UINT16                              ausImei[GSM_IMEI_LEN];              /* IMEI ռ�õĳ��� */
    VOS_UINT16                              ausImeiSV[GSM_IMEISV_LEN];          /* IMEISV ռ�õĳ��� */
    VOS_UINT16                              usDscInitValueCS;                   /* CS��DSC��ʼֵ */
    VOS_UINT16                              usDscInitValuePS;                   /* PS��DSC��ʼֵ */
} MPH_UPDATE_PARSE_PAGING_PARA_REQ_STRU;


/*****************************************************************************
 ��Ϣ����  :  MPH_UPDATE_PARSE_PAGING_PARA_CNF_STRU
 ��������  :  MPH_UPDATE_PARSE_PAGING_PARA_REQ��ȷ��ԭ�
 �޸���ʷ  :
  1.��    ��    : 2007��10��06��
    ��    ��    : fangjian(48555)
    �޸�����    : �����ɽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GAS_MSG_ID_ENUM_UINT16              usMsgID;                            /* _H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                              usRsv;
} MPH_UPDATE_PARSE_PAGING_PARA_CNF_STRU;


/*****************************************************************************
 ��Ϣ����  : MPH_UPDATE_RESEL_PARA_REQ_STRU
 ��������  : ��ԭ����������������GSM/GPRSС����ѡ��ز���
 �޸���ʷ  :
  1.��    ��    : 2007��09��06��
    ��    ��    : fangjian(48555)
    �޸�����    : �����ɽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usArfcn;                            /* ��С��Ƶ�� */
    VOS_INT16                               sNcellC1Value;                      /* ��С��C1ֵ */
    VOS_INT16                               sNcellC31Value;                     /* ��С��C31ֵ */
    VOS_INT16                               sNcellC32Value;                     /* ��С��C2ֵ����С��C32ֵ */
    VOS_INT16                               sReselOffset;                       /* ���ڴ���PBCCH�ŵ��µ���ѡ */
    VOS_UINT16                              usPriorityClass;                    /* ���ڴ���PBCCH�ŵ��µ���ѡ */
} GSM_NCELL_C_THRESHOLD_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GAS_MSG_ID_ENUM_UINT16              usMsgID;                            /* _H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                              usScellCValueFlag;
    VOS_UINT16                              usCValueMark;
    VOS_INT16                               sScellC1Value;                      /* ����С��C1ֵ */
    VOS_INT16                               sScellC31Value;                     /* ����С��C31ֵ */
    VOS_INT16                               sScellC32Value;                     /* ����С��C2��C32ֵ */
    VOS_UINT16                              usC32Qual;                          /* ����PBCCH�ŵ�ʱ */
    VOS_UINT16                              us3GSearchPrio;                     /* 3G�����Ƿ����Ȳ���,0:2G��BSIC��֤������3G������1:3G����������2G��BSIC��֤ */
    VOS_UINT16                              usSCellPriority;                    /* ����С�����ȼ� */
    VOS_UINT16                              usLteSearchPrio;                    /* Lte�����Ƿ����Ȳ���,0:2G��BSIC��֤������Lte������1:Lte����������2G��BSIC��֤ */
    VOS_UINT16                              usBand18001900Indicator;            /* 0��1800Ƶ��,1��1900Ƶ�� */
    VOS_UINT16                              usMsSupportedBand;                  /* �ֻ�ϵͳ֧�ֵ�Ƶ�� */
    VOS_UINT16                              usMultiBandMode;                    /* ϵͳ֧�ֵ�Ƶ��ģʽ */
    VOS_UINT16                              usNccPermitted;                     /* ���������NCC���� */
    VOS_UINT16                              usNcMode;
    VOS_UINT16                              usGmmState;
    VOS_UINT16                              usMeasOrder;
    VOS_UINT16                              usNcellArraySize;                   /* ��С������ */

    /* A threshold below which the MS is allowed to reselect to lower priority layers,
       0 = 0 dB, 1 = 2 dB, 2 = 4 dB, ��, 13 = 26 dB, 14 = 28 dB, 15 = infinite (always). */
    /* ����MS��ѡ�������ȼ�С�������ޣ�Ĭ��ֵΪ0,GAS�·���ֵΪת��Ϊ��ƽֵ֮ǰ��ֵ[0,15] */
    VOS_UINT16                              usThreshGsmLow;
    VOS_UINT16                              usRsv;                              /* GAS��GDSP֮��Ľӿڱ���λӦʹ��U16 */
    GSM_NCELL_C_THRESHOLD_STRU              astStrongNCellArray[GSM_STRONGEST_FREQLIST_NUM];    /* ��С����Cֵ�Ƿ��иı� */
} MPH_UPDATE_RESEL_PARA_REQ_STRU;


/*****************************************************************************
 ��Ϣ����  :  MPH_UPDATE_RESEL_PARA_CNF_STRU
 ��������  :  MPH_UPDATE_RESEL_PARA_REQ��ȷ��ԭ�
 �޸���ʷ  :
  1.��    ��    : 2007��10��06��
    ��    ��    : fangjian(48555)
    �޸�����    : �����ɽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GAS_MSG_ID_ENUM_UINT16              usMsgID;                            /* _H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                              usRsv;
} MPH_UPDATE_RESEL_PARA_CNF_STRU;



typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GAS_MSG_ID_ENUM_UINT16              usMsgID;                            /* _H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                              us3GSearchPrio;                     /* 3G�����Ƿ����Ȳ���,0:2G��BSIC��֤������3G������1:3G����������2G��BSIC��֤ */
    VOS_UINT16                              usBand18001900Indicator;            /* 0��1800Ƶ��,1��1900Ƶ�� */
    VOS_UINT16                              usMsSupportedBand;                  /* �ֻ�ϵͳ֧�ֵ�Ƶ�� */
    VOS_UINT16                              usMultiBandMode;                    /* ϵͳ֧�ֵ�Ƶ��ģʽ */
    VOS_UINT16                              usNccPermitted;                     /* ���������NCC���� */
    VOS_UINT16                              usPwrc;                             /* Power control indicator */
    VOS_UINT16                              usLteSearchPrio;                    /* Lte�����Ƿ����Ȳ���,0:2G��BSIC��֤������Lte������1:Lte����������2G��BSIC��֤ */
} MPH_UPDATE_DEDICATED_CTRL_PARA_REQ_STRU;
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GAS_MSG_ID_ENUM_UINT16              usMsgID;                            /* _H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                              usRsv;
} MPH_UPDATE_DEDICATED_CTRL_PARA_CNF_STRU;


/*****************************************************************************
 ��Ϣ����  : MPH_CELL_INFO_REPORT_REQ_STRU
 ��������  : ��ԭ�����������ִ��С����ѡԤ�о����Լ������б���º󣬽����֪ͨЭ��ջ
 �޸���ʷ  : MPH_CELL_RESELECT_IND,MPH_UPDATE_STRONG_NCELL_LIST_IND�ϲ�����
  1.��    ��    : 2007��09��06��
    ��    ��    : fangjian(48555)
    �޸�����    : �����ɽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GAS_MSG_ID_ENUM_UINT16              usMsgID;                            /* _H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                              usReserved;
    VOS_UINT32                              u1ActionMask;                       /* ָʾ��������Mask�ж����ϱ�����С��ǿ�ȡ�
                                                                                   NC��������(�������Ų���)��tunning̬������ */
} MPH_CELL_INFO_REPORT_REQ_STRU;


/*****************************************************************************
 ��Ϣ����  : MPH_CELL_INFO_REPORT_IND_STRU
 ��������  : ��ԭ�����������ִ��С����ѡԤ�о����Լ������б���º󣬽����֪ͨЭ��ջ
 �޸���ʷ  : MPH_CELL_RESELECT_IND,MPH_UPDATE_STRONG_NCELL_LIST_IND�ϲ�����
  1.��    ��    : 2007��09��06��
    ��    ��    : fangjian(48555)
    �޸�����    : �����ɽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GAS_MSG_ID_ENUM_UINT16              usMsgID;                            /* _H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                              usArfcn;                            /* ����С��Ƶ��� */
    VOS_UINT32                              ulActionMask;                       /* ������ϱ�ԭ�ﶯ������ */
    VOS_UINT16                              usScellRxlev;                       /* ����С������ֵ */
    VOS_UINT16                              usC;                                /* Cֵ����Χ0~63 */
    VOS_UINT16                              usTimerStatus;                      /* ��ѡ��ʱ��״̬,7bit������С��C1��ʱ��,5bit���ϱ��ĵ�һ����С��C2��ʱ�� */
    VOS_UINT16                              usTargetArfcn;                      /* ������ѡ��Ŀ��С��Ƶ�� */
    VOS_UINT16                              usReadyMark;                        /* ��С���Ƿ��Ѿ������� */
    VOS_UINT16                              usStrongNCellNum;                   /* �����ά������ǿ��С��������ÿ�ζ��� */
    GSM_STRONG_NCELL_STRU                   astStrongNCellArray[GSM_STRONGEST_FREQLIST_NUM];
} MPH_CELL_INFO_REPORT_IND_STRU;



typedef struct
{
    VOS_UINT16                              usPrimaryScramCode;                 /* С����������,9bit,0xFFFF��ʶû�� */
    VOS_UINT16                              usDiversityInd;                     /* �ּ�ָʾ,0:not applied,1:applied */
} WCELL_INFO_STRU;


typedef struct
{
    VOS_UINT16                              usArfcn;                            /* Ƶ����Ϣ [0��16383] */
    VOS_UINT16                              usBandInfo;                         /* Ƶ����Ϣ [0��9] */
    VOS_UINT16                              usCellNum;                          /* һ��Ƶ���µ�С����Ŀ,[1��32] */
    VOS_UINT16                              usNonNCellMeasFlg;
    WCELL_INFO_STRU                         astWCellInfo[MAX_INTER_FREQ_INFO_NUM];
} WCELL_INFO_LIST_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GAS_MSG_ID_ENUM_UINT16              usMsgID;                            /* _H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                              usRsv;                              /* ����λ */
} MPH_WCDMA_MEAS_REQ_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GAS_MSG_ID_ENUM_UINT16              usMsgID;                            /* _H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                              usRsv;
    VOS_UINT32                              ulFrameNum;
} MPH_WCDMA_MEAS_CNF_STRU;


/*****************************************************************************
 ��Ϣ����  :  MPH_NC_MEAS_REPORT_REQ_STRU
 ��������  :  ��ԭ������ָʾ��������Mask�ж����ϱ�����С��ǿ�ȡ�NC��������(�������Ų���)��tunning̬������
 �޸���ʷ  :
  1.��    ��    : 2007��09��06��
    ��    ��    : jiajing(55331)
    �޸�����    : �����ɽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GAS_MSG_ID_ENUM_UINT16              usMsgID;                            /* _H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                              usReserved;
    VOS_UINT32                              ulActionMask;
} MPH_NC_MEAS_REPORT_REQ_STRU;


/*****************************************************************************
 ��Ϣ����  :  MPH_NC_MEAS_REPORT_IND_STRU
 ��������  :  ��ԭ������������ϱ�Э��ջNC�������
 �޸���ʷ  :
  1.��    ��    : 2007��09��06��
    ��    ��    : jiajing(55331)
    �޸�����    : �����ɽṹ
  2.��    ��    : 2007��10��12��
    ��    ��    : fangjian(48555)
    �޸�����    : ����usWMeasMark��־
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GAS_MSG_ID_ENUM_UINT16              usMsgID;                            /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                              usScellRxlev;                       /* ����С����ƽ */
    VOS_UINT16                              usPccchIntRxlev;                    /* ����̬�ϱ�PCCCH���Ų��� */
    VOS_UINT16                              usNcellNum;                         /* ά������������ */
    GSM_STRONG_NCELL_STRU                   astNcellInfo[GSM_STRONGEST_FREQLIST_NUM];   /* ������Ϣ */
} MPH_NC_MEAS_REPORT_IND_STRU;


/*****************************************************************************
 ��Ϣ����  :  MPH_RA_ABORT_REQ_ST
 ��������  :  Э��ջͨ����ԭ��֪ͨ��������RACH������̣��������Ҫ��������AGCH��
              ��ôЭ��ջʹ�ò���MonitorPagch��ָʾ��������AGCH.
 �޸���ʷ  :
  1.��    ��    : 2007��10��06��
    ��    ��    : fangjian(48555)
    �޸�����    : �����ɽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GAS_MSG_ID_ENUM_UINT16              usMsgID;                            /* _H2ASN_Skip */ /* ԭ������ */
    PHY_MONI_AGCH_FLG_ENUM_UINT16           enMonitorAgch;                      /* ָʾPHY�Ƿ����AGCH,0��ʾ���ټ�����1��ʾ�������� */
} MPH_RA_ABORT_REQ_ST;


/*****************************************************************************
 ��Ϣ����  :  MPHP_GPRS_CHANNEL_QUALITY_REPORT_ST
 ��������  :  ��ԭ��������GPRSģʽ��PHY�����Ե���GRR�ϱ��ŵ��������档
 �޸���ʷ  :
  1.��    ��    : 2007��10��06��
    ��    ��    : fangjian(48555)
    �޸�����    : �����ɽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GAS_MSG_ID_ENUM_UINT16              usMsgID;                            /* _H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                              usArfcn;                            /* ������С����Ƶ�� */
    VOS_UINT16                              usC;                                /* Cֵ����ΧΪ0��63 */
    VOS_UINT16                              usRxqual;                           /* RXQUALֵ��Ϊ����������ӳ��ȼ�ֵ����ΧΪ0��7 */
    VOS_UINT16                              usSignalVar;                        /* SIGN_VARֵ�������ź�ǿ�ȵķ���ӳ��ȼ�ֵ����ΧΪ0��63 */
    VOS_UINT16                              ausInLevelTn[GAS_INT_LEVEL_TN_MAX]; /* ��TN0-TN7�Ͻ��и��Ų����Ľ��ӳ��ȼ�ֵ����ΧΪ0��15 */
} MPHP_GPRS_CHANNEL_QUALITY_REPORT_ST;


/*****************************************************************************
 ��Ϣ����  :  MPHP_EGPRS_CHANNEL_QUALITY_REPORT_ST
 ��������  :  ��ԭ��������EGPRSģʽ��PHY�����Ե���GRR�ϱ��ŵ��������档
 �޸���ʷ  :
  1.��    ��    : 2008��2��22��
    ��    ��    : fangjian(48555)
    �޸�����    : �����ɽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GRR_MSG_ID_ENUM_UINT16              usMsgID;                            /* _H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                              usARFCN;                            /* ������С����Ƶ�� */
    VOS_UINT16                              usC;                                /* Cֵ����ΧΪ0��63 */
    VOS_UINT16                              usMeanBepGmsk;                      /* GMSK������ʱ϶��ƽ��������ʣ�0��31    */
    VOS_UINT16                              usMeanBep8Psk;                      /* 8PSK������ʱ϶��ƽ��������ʣ�0��31    */
    VOS_UINT16                              usCVBepGmsk;                        /* GMSK������ʱ϶��������ʷ���ϵ����0��7 */
    VOS_UINT16                              usCVBep8Psk;                        /* 8PSK������ʱ϶��������ʷ���ϵ����0��7 */
    VOS_UINT16                              usTsQualityPresent;                 /* ��ʾ���¼�����EGPRS Timeslot Link Quality��صĲ����Ƿ���ڣ�0,�����ڣ�1,���� */
    VOS_UINT16                              ausMeanBepGmskTn[GAS_MAX_TIMESLOT_NUM];     /* GMSK��TN0-TN7��ƽ��������ʣ�0��31,��ЧֵΪ0xFF    */
    VOS_UINT16                              ausMeanBep8PskTn[GAS_MAX_TIMESLOT_NUM];     /* 8PSK��TN0-TN7��ƽ��������ʣ�0��31,��ЧֵΪ0xFF    */
    VOS_UINT16                              ausInLevelTn[GAS_MAX_TIMESLOT_NUM]; /* ��TN0-TN7�Ͻ��и��Ų����Ľ��ӳ��ȼ�ֵ��0��15,��ЧֵΪ0xFF */
} MPHP_EGPRS_CHANNEL_QUALITY_REPORT_ST;


/*****************************************************************************
  * MPH_PCCCH_ST�ṹ:����ԭ�ж���
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usTsc;
    VOS_UINT16                              usSlotBitMap;                       /* ʱ϶ӳ��ʹ�õ�8bit��bit0��Ӧʱ϶0��bit7��Ӧʱ϶7����Ӧ����Ϊ1��ʾ��ʱ϶������*/
    VOS_UINT16                              usMaio;                             /* ��ƵMAIO     */
    VOS_UINT16                              usHsn;                              /* ��Ƶ���к�*/
    VOS_UINT16                              usFreqNum;                          /* ��ƵƵ�����*/
    VOS_UINT16                              ausFreqList[GAS_MAX_HOPPING_FREQUENCY_NUM];
} MPH_PCCCH_ST;


/*****************************************************************************
 ��Ϣ����  :  MPHP_UPDATE_PSI_PARAM_REQ_ST
 ��������  :  ��С��פ���ɹ���GASͨ����ԭ��֪ͨL1����ϵͳ��Ϣ��
 �޸���ʷ  :
  1.��    ��    : 2007��10��06��
    ��    ��    : fangjian(48555)
    �޸�����    : �����ɽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GAS_MSG_ID_ENUM_UINT16              usMsgID;                            /* _H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                              usPb;                               /* ����˥��ֵ, 0-15��ÿ��2dB*/
    VOS_UINT16                              usABType;                           /* ����burst���� */
    VOS_UINT16                              usGPRSMaxTxPow;                     /* MS����书�� */
    VOS_UINT16                              usLB_MS_TXPWR_MAX_CCH;              /* 0xFFFF��ʾ��Ч */
    VOS_UINT16                              usPccchChannels;                    /* С����Pccch���ŵ����� */
    VOS_UINT16                              usPbcchBlks;                        /* Pbcch��ռ�õĿ��� */
    VOS_UINT16                              usPagBlksRes;                       /* PAGCH��ռ�õĿ��� */
    VOS_UINT16                              usPrachBlks;                        /* Prach��ռ�õĿ��� */
    VOS_UINT16                              usSpgcCcchSup;                      /* CCCHѰ���������*/
    VOS_UINT16                              usDrxCycle;                         /* SPLIT_PG_CYCLE */
    VOS_UINT16                              usKTavgT;                           /* ���鴫��ģʽ�¹��ʿ����м����ź�ǿ���˲����ڲ���*/
    VOS_UINT16                              usKTavgW;                           /* ���鴫��ģʽ�¹��ʿ����м����ź�ǿ���˲����ڲ���*/
    VOS_UINT16                              usKTavgI;                           /* ���ʿ����м������ǿ���˲�������*/
    VOS_UINT16                              usBepPeriod;                        /* �������ڼ���BEP,ȡֵ��Χ[0,10],��ЧֵΪ0XFFFF*/
    VOS_UINT16                              usPCMeasCh;                         /* �����ŵ�ָʾ��0��BCCH��1��PDCH��*/
    VOS_UINT16                              usNetWorkMode;                      /* Mode1��2��3��*/
    VOS_UINT16                              usImsiMod1000;                      /* �ò�����������PPCHλ�ã��μ�05.02 6.5.6*/
    VOS_UINT16                              usPccchValid;                       /* 0��ʾ������,1��ʾ���� */
    VOS_UINT16                              usReserved;                         /* ���ֽڶ��뱣�� */
    MPH_PCCCH_ST                            stPCCChDescription;
} MPHP_UPDATE_PSI_PARAM_REQ_ST;


/*****************************************************************************
 ��Ϣ����  :  MPHP_UPDATE_PSI_PARAM_CNF_ST
 ��������  :  ��ԭ������L1��GRR�ϱ�������ϵͳ��Ϣ����ȷ�ϡ�
 �޸���ʷ  :
  1.��    ��    : 2007��10��06��
    ��    ��    : fangjian(48555)
    �޸�����    : �����ɽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GAS_MSG_ID_ENUM_UINT16              usMsgID;                            /* _H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                              usRsv;
} MPHP_UPDATE_PSI_PARAM_CNF_ST;


/*****************************************************************************
 ��Ϣ����  :  MPHP_SERVING_PBCCH_SETUP_REQ_ST
 ��������  :  ����С��PBCCH����ԭ�Э��ջʹ�ø�ԭ��֪ͨ�������շ���С��ϵͳ��Ϣ��
              �����ͨ������Ϣ�жϵ�ǰ�ķ���С��������פ���ڸ�С����
 �޸���ʷ  :
  1.��    ��    : 2007��10��06��
    ��    ��    : fangjian(48555)
    �޸�����    : �����ɽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GAS_MSG_ID_ENUM_UINT16              usMsgID;                            /* _H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                              usHopping;                          /* ��Ƶָʾ��0��ʾ����Ƶ��1��ʾ��Ƶ; */
    VOS_UINT16                              usHsn;                              /* ��Ƶ���к�;0��63;*/
    VOS_UINT16                              usMaio;                             /* Mobile Allocation Index Offset;���ڲ�����Ƶ���У��ο�05.02����;*/
    VOS_UINT16                              usTsc;                              /* ѵ�����кţ�0��7;*/
    VOS_UINT16                              usPb;                               /* power reduction (usPb) used on PBCCH��0��15;�ο�05.08����;*/
    VOS_UINT16                              usPbcchArfcn;                       /* ����Ƶ���ŵ��ţ�0��1023������Ƶʱ����   */
    VOS_UINT16                              usFreqNum;                          /* ��ƵƵ����Ŀ��[0,64] ��Ƶʱ��Ч */
    VOS_UINT16                              usPbcchFreqList[GAS_MAX_HOPPING_FREQUENCY_NUM]; /* ��Ƶʱ��Ч*/
    VOS_UINT16                              usSlotBitMap;                       /* PBCCH���ڵ�ʱ϶TimeSlot */
    VOS_UINT16                              usPSIRepeatPeriod;                  /* 52 ��֡��PSI 1���ظ����ڣ�1��16;*/
    VOS_UINT16                              usPbcchModeBcc;                     /* ����PBCCH���������ģʽ��0��ʾ����ȫ��ϵͳ��Ϣ��1��ʾ����PSI 1���ϵͳ��Ϣ��2��ʾֻ����PSI 1ϵͳ��Ϣ;*/
    VOS_UINT16                              usPcMeasCh;                         /* �����ŵ�ָʾ��0��ʾBCCH;1��ʾPDCH; �������ȷ���ˣ�Ĭ��ֵ����Ϊ0 */
} MPHP_SERVING_PBCCH_SETUP_REQ_ST;


/*****************************************************************************
 ��Ϣ����  :  MPHP_SERVING_PBCCH_SETUP_CNF_ST
 ��������  :  ����С��PBCCH����ȷ��ԭ�
 �޸���ʷ  :
  1.��    ��    : 2007��10��06��
    ��    ��    : fangjian(48555)
    �޸�����    : �����ɽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GAS_MSG_ID_ENUM_UINT16              usMsgID;                            /* _H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                              usSucessInd;                        /* 0��ʾ�ɹ���1��ʾʧ�ܣ�*/
} MPHP_SERVING_PBCCH_SETUP_CNF_ST;


/*****************************************************************************
 ��Ϣ����  :  MPHP_SERVING_PBCCH_RELEASE_REQ_ST
 ��������  :  ����С��PBCCH�ͷ�ԭ������ʹ�ø�ԭ��ֹͣ����С��ϵͳ��Ϣ���ա�
 �޸���ʷ  :
  1.��    ��    : 2007��10��06��
    ��    ��    : fangjian(48555)
    �޸�����    : �����ɽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GAS_MSG_ID_ENUM_UINT16              usMsgID;                            /* _H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                              usReserved;
} MPHP_SERVING_PBCCH_RELEASE_REQ_ST;


/*****************************************************************************
 ��Ϣ����  :  MPHP_SERVING_PBCCH_RELEASE_CNF
 ��������  :  ����С��PBCCH�ͷ�ȷ��ԭ�
 �޸���ʷ  :
  1.��    ��    : 2007��10��06��
    ��    ��    : fangjian(48555)
    �޸�����    : �����ɽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GAS_MSG_ID_ENUM_UINT16              usMsgID;                            /* _H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                              usSucessInd;                        /* 0��ʾ�ɹ���1��ʾʧ�ܣ�*/
} MPHP_SERVING_PBCCH_RELEASE_CNF;


/*****************************************************************************
 ��Ϣ����  :  MPH_CELL_RESELECT_CNF_STRU
 ��������  :  ����ϢMPHP_CELL_RESELECT_REQ��Ӧ����Ϣ��
 �޸���ʷ  :
  1.��    ��    : 2007��11��27��
    ��    ��    : fangjian(48555)
    �޸�����    : �����ɽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GAS_MSG_ID_ENUM_UINT16              usMsgID;                            /* _H2ASN_Skip */ /* ԭ������ */
    EDGE_CNF_RESULT_ENUM_UINT16             enSucessInd;
    VOS_UINT16                              usBSIC;
    VOS_UINT16                              usRsv;
} MPH_CELL_RESELECT_CNF_STRU;


/* �����ж�ģ��ԭ�� */
typedef struct /*������Ϣ�ϱ�*/
{
    VOS_UINT16                              enAgcNextGain;                      /* ��һ��������AGC��λ*/
    VOS_UINT16                              enExactRssiTsn;                     /* ԭ������ *//* Ӧ�ò����жϵ�ʱ϶*/
    VOS_UINT16                              uhwFreq;                            /* Ƶ��*/
    VOS_INT16                               shwAgcRssi;                         /* ������ƽֵ*/
    VOS_UINT16                              uhwFnMod102;                        /* ֡��ģ��102�Ľ�� */
    VOS_UINT16                              uhwFnMod104;                        /* ֡��ģ��104�Ľ�� */
    VOS_UINT16                              uhwFnMod26;                         /* ֡��ģ��26�Ľ�� */
    VOS_UINT16                              uhwReserved;                        /* ���ֽڶ���*/
} COM_MEAS_ISR_RPT_INFO_STUB_STRU;


/*****************************************************************************
 ��Ϣ����  :  MPH_PHY_MEA_ISR_STUB_REQ_STRU
 ��������  :  ITT���Բ����ж���Ϣ
 �޸���ʷ  :
  1.��    ��    : 2007��11��27��
    ��    ��    : fangjian(48555)
    �޸�����    : �����ɽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GAS_MSG_ID_ENUM_UINT16              usMsgID;                            /* _H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                              usISRID;
    COM_MEAS_ISR_RPT_INFO_STUB_STRU         stMeaIsrResult;
} MPH_PHY_MEA_ISR_STUB_REQ_STRU;


/* ͬ���ж�ģ��ԭ�� *//* ͬ����Ϣ�ϱ� */
typedef struct
{
    VOS_UINT16                              enSyncStateWord;                    /* ͬ��״̬�� */
    VOS_UINT16                              enAfcLock ;                         /* AFC ״̬ */
    VOS_UINT16                              uhwBSIC;                            /* 0xffff ��Ч */
    VOS_UINT16                              uhwT1;                              /* ֡����Ϣ 0xffff ��Ч */
    VOS_UINT16                              uhwT2;                              /* ֡����Ϣ 0xffff ��Ч */
    VOS_UINT16                              uhwT3a;                             /* ֡����Ϣ 0xffff ��Ч */
    VOS_UINT16                              uhwScellTOAOffset;                  /* ������֡ͷƫ������TIMEBASE��ƫ�� */
    VOS_UINT16                              uhwNcellTOAOffset;                  /* ��������ʹ�ã������TIMEBASE��ƫ�� */
    VOS_UINT32                              uwScellFrameNum;                    /* ������ʹ�õ�16bitTDMA֡�ŵ�λ0~26x51-1ѭ������
                                                                                   ��16bitTDMA֡�Ÿ�λ0~2047ѭ������ */
    VOS_UINT32                              uwNcellFrameNum;                    /* ����ʹ�õ�16bitTDMA֡�ŵ�λ0~26x51-1ѭ������
                                                                                   ��16bitTDMA֡�Ÿ�λ0~2047ѭ������ */

} COM_SYN_ISR_RPT_INFO_STUB_STRU;


/*****************************************************************************
 ��Ϣ����  :  MPH_PHY_SYN_ISR_STUB_REQ_STRU
 ��������  :  ITT����ͬ���ж���Ϣ
 �޸���ʷ  :
  1.��    ��    : 2007��11��27��
    ��    ��    : fangjian(48555)
    �޸�����    : �����ɽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GAS_MSG_ID_ENUM_UINT16              usMsgID;                            /* _H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                              usISRID;
    COM_SYN_ISR_RPT_INFO_STUB_STRU          stMeaIsrResult;
} MPH_PHY_SYN_ISR_STUB_REQ_STRU;


/* cs�����ж�ģ��ԭ�� *//* CS������Ϣ�ϱ� */
typedef struct
{
    VOS_UINT16                              enChannelType;
    VOS_UINT16                              enAssignRxTs;
    VOS_UINT16                              uhwFacchStealFlg;                   /* ͵֡��־ 1��ʾ��ǰΪFACCH���룬0��ʾ��FACCH����*/
    VOS_UINT16                              uhwTchHStealFlg;                    /* TCH/H �����͵֡ʹ��,�����ж�������,
                                                                                   0 ��ʾ���������ϱ� 2��ʾ��ǰ����������ĸ�ʱ϶ΪFACCH/H��ǰ�ĸ�ʱ϶�������������� */
    VOS_UINT16                              enCrcFlg;
    VOS_UINT16                              uhwBerBitNum;                       /* ber ͳ�ƴ���bit�� */
    VOS_UINT16                              uhwBerTotalBitNum;                  /* ber ͳ����bit�� */
    VOS_UINT16                              uhwBerClassIbNum;                   /* ClassIb bit error num */
    VOS_UINT16                              enAmrFrameType;                     /* �ϱ�AMR�µ�֡���� */
    VOS_UINT16                              auhwAmrIc[2];                       /* AMR���ڱ��� ic0,ic1�����ֻ��ic��
                                                                                   �����auhwAmrIc[0]��0xfffff��Ч */
    VOS_UINT16                              uhwTC51;                            /* TC = (FN div 51 ) mod 8 */
    VOS_UINT32                              uwFN;                               /* ֡�� */
    VOS_UINT16                              uhwFnMod104;                        /* ֡��ģ��104�Ľ�� */
    VOS_UINT16                              uhwFnMod102;                        /* ֡��ģ��102�Ľ�� */
    VOS_UINT16                              uhwDecDataLen;                      /* ��Ч���ݳ���,32BITΪ��λ���� */
    VOS_UINT16                              uhwReserved;                        /* ���ֽڶ��� */
    VOS_UINT16                              auhwDecDataInfo[10*2];              /* ���������ϱ���������Ϣ */
} COM_CSDEC_ISR_RPT_INFO_STUB_STRU;


/*****************************************************************************
 ��Ϣ����  :  MPH_PHY_CSDEC_ISR_STUB_REQ_STRU
 ��������  :  ITT����CS�����ж���Ϣ
 �޸���ʷ  :
  1.��    ��    : 2007��11��27��
    ��    ��    : fangjian(48555)
    �޸�����    : �����ɽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GAS_MSG_ID_ENUM_UINT16              usMsgID;                            /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                              usISRID;
    COM_CSDEC_ISR_RPT_INFO_STUB_STRU        stMeaIsrResult;
} MPH_PHY_CSDEC_ISR_STUB_REQ_STRU;


/* PS�����ж�ģ��ԭ�� *//* PS������Ϣ�ϱ� */
typedef struct
{
    VOS_UINT16                              enChannelType;
    VOS_UINT16                              enAssignRxTs;
    VOS_UINT16                              enPscodeType;                       /* PDTCH�µı������� */
    VOS_UINT16                              uhwUSFDec;                          /* ������usf */
    VOS_UINT16                              uhwPayLoadType;                     /* PACCHָʾ */
    VOS_UINT16                              uhwTFIDec;                          /* ������tfi */
    VOS_UINT16                              uhwPacchFlag;                       /* ָʾ��ǰ��ΪPACCH��1��ʾΪPACCH */
    VOS_UINT16                              uhwTFIFlag;                         /* Ϊ1��ʾ������tfi������TFIһ�� */
    VOS_UINT16                              aenCrcFlg[3];
    VOS_UINT16                              uhwBerBitNum;                       /* ber ͳ�ƴ���bit�� */
    VOS_UINT16                              uhwBerTotalBitNum;                  /* ber ͳ����bit�� */
    VOS_UINT16                              auhwBepBitNum[4];                   /* BEP bit num */
    VOS_UINT16                              auhwHarqPos[2];                     /* �ϱ�����ǰ���ô�ŵ�HARQ����λ�ã�harq����������Ч */
    VOS_UINT16                              auhwBsn[2];                         /* RLC bsn���룬����HARQ */
    VOS_UINT16                              uhwFnMod26;                         /* ֡��ģ��26�Ľ�� */
    VOS_UINT16                              uhwDecCycleRptNum;                  /* ����ϱ���λ�� */
    VOS_UINT16                              uhwBbpDecDataAddrOffset;            /* ��������ƫ�Ƶ�ַ */
    VOS_UINT16                              uhwDecDataLen;                      /* ��Ч���ݳ��� */
    VOS_UINT16                              uhwCbNum;                           /* ָʾ���������ϱ�������� */
    VOS_UINT16                              auhwDecDataInfo[12];                /* ���������ϱ���������Ϣ,�������Ϣ��ΪPPCH��PTCCH,PACCH */
} COM_PSDEC_ISR_RPT_INFO_STUB_STRU;


/*****************************************************************************
 ��Ϣ����  :  MPH_PHY_PSDEC_ISR_STUB_REQ_STRU
 ��������  :  ITT����PS�����ж���Ϣ
 �޸���ʷ  :
  1.��    ��    : 2007��11��27��
    ��    ��    : fangjian(48555)
    �޸�����    : �����ɽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GAS_MSG_ID_ENUM_UINT16              usMsgID;                            /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                              usISRID;
    COM_PSDEC_ISR_RPT_INFO_STUB_STRU        stMeaIsrResult;
} MPH_PHY_PSDEC_ISR_STUB_REQ_STRU;



/*****************************************************************************
 ��Ϣ����  : MPH_CBCH_READ_REQ_STRU
 ��������  : GAS������㷢����CBCH�ŵ���ȡ����
 �޸���ʷ  :
  1.��    ��    : 2010��04��30��
    ��    ��    : zhaopeng(59430)
    �޸�����    : �����ɽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    VOS_UINT16                              usMsgID;                            /* _H2ASN_Skip */ /* ԭ������ */
    GSM_CBCH_TYPE_ENUM_UINT16               enCBCHType;                         /* CBCH�ŵ����� */
    CHANNEL_DESCRIPTION_STRU                stChanDescription;                  /* CBCH�ŵ����� */
    MOBILE_ALLOCATION_STRU                  stFreqList;                         /* CBCH�ŵ���Ƶʱ��Ƶ���б� */
    GSM_CBCH_SCHEDULE_INFO_ENUM_UINT16      enScheInfoFlg;                      /* CBCH������Ϣ�Ƿ���Ч�ı�־ */
    VOS_UINT16                              usUsedRcvNMBits;                    /* ����NM BIT MAP��ʹ���˶��ٸ�BIT */
    VOS_UINT32                              ulScheMsgFN;                        /* ���½��յ���SCHEDULE Message FIRST BLOCK��֡��, ��GDSP�ϱ�, GAS��� */

    /*******************************************************
       ��ҪDSP���յ�PAGE BIT MAP, aulRcvNMBitmap[0]BIT0����NM1�Ƿ����,
       BIT31����NM32�Ƿ����, aulRcvNMBitmap[1] BIT0����NM33�Ƿ����,
       BIT NΪ1������Ҫ����, BIT NΪ0������Ҫ����, �����ЧBIT���������ϢBIT
    ********************************************************/

    VOS_UINT32                              aulRcvNMBitmap[2];
} MPH_CBCH_READ_REQ_STRU;


/*****************************************************************************
 ��Ϣ����  : MPH_STOP_CBCH_READ_REQ_STRU
 ��������  : GAS������㷢����CBCH�ŵ�ֹͣ��ȡ����
 �޸���ʷ  :
  1.��    ��    : 2010��04��30��
    ��    ��    : zhaopeng(59430)
    �޸�����    : �����ɽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    VOS_UINT16                              usMsgID;                            /* _H2ASN_Skip */ /* ԭ������ */
    GSM_CBCH_TYPE_ENUM_UINT16               enCBCHType;                         /* CBCH�ŵ����� */
} MPH_STOP_CBCH_READ_REQ_STRU;


/*****************************************************************************
 ��Ϣ����  : MPH_STOP_CBCH_CUR_PAGE_REQ_STRU
 ��������  : GCBS������㷢����ֹͣ��ǰҳ��ȡ����
 �޸���ʷ  :
  1.��    ��    : 2010��04��30��
    ��    ��    : zhaopeng(59430)
    �޸�����    : �����ɽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    VOS_UINT16                              usMsgID;                            /* _H2ASN_Skip */ /* ԭ������ */
    GSM_CBCH_TYPE_ENUM_UINT16               enCBCHType;                         /* CBCH�ŵ����� */
    VOS_UINT32                              ulPageFirstBlkFn;                   /* PAGE FIRST BLOCK��֡��, �����DSP�ϱ�, ���������DSP */
} MPH_STOP_CBCH_CUR_PAGE_REQ_STRU;


/*****************************************************************************
 ��Ϣ����  : MPH_CBCH_READ_CNF_STRU
 ��������  : ������յ�CBCH��ȡ�����Ļظ���Ϣ
 �޸���ʷ  :
  1.��    ��    : 2010��04��30��
    ��    ��    : zhaopeng(59430)
    �޸�����    : �����ɽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    VOS_UINT16                              usMsgID;                            /* _H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                              usResult;                           /* 0��ʾ�ɹ���1��ʾʧ�� */
    GSM_CBCH_TYPE_ENUM_UINT16               enCBCHType;                         /* CBCH�ŵ����� */
    VOS_UINT16                              usRsv;
} MPH_CBCH_READ_CNF_STRU;


/*****************************************************************************
 ��Ϣ����  : MPH_STOP_CBCH_READ_CNF_STRU
 ��������  : ������յ�ֹͣ��ȡCBCH��Ļظ���Ϣ
 �޸���ʷ  :
  1.��    ��    : 2010��04��30��
    ��    ��    : zhaopeng(59430)
    �޸�����    : �����ɽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    VOS_UINT16                              usMsgID;                            /* _H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                              usResult;                           /* 0��ʾ�ɹ���1��ʾʧ�� */
    GSM_CBCH_TYPE_ENUM_UINT16               enCBCHType;                         /* CBCH�ŵ����� */
    VOS_UINT16                              usRsv;
} MPH_STOP_CBCH_READ_CNF_STRU;


/*****************************************************************************
 ��Ϣ����  : MPH_STOP_CBCH_CUR_PAGE_CNF_STRU
 ��������  : ������յ�ֹͣ��ǰҳ��ȡ��Ļظ���Ϣ
 �޸���ʷ  :
  1.��    ��    : 2010��04��30��
    ��    ��    : zhaopeng(59430)
    �޸�����    : �����ɽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    VOS_UINT16                              usMsgID;                            /* _H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                              usResult;                           /* 0��ʾ�ɹ���1��ʾʧ�� */
    GSM_CBCH_TYPE_ENUM_UINT16               enCBCHType;                         /* CBCH�ŵ����� */
    VOS_UINT16                              usRsv;
} MPH_STOP_CBCH_CUR_PAGE_CNF_STRU;


/*****************************************************************************
 ��Ϣ����  : MPH_CBS_DATA_IND_STRU
 ��������  : ������ϱ���CBS��Ϣ
 �޸���ʷ  :
  1.��    ��    : 2010��04��30��
    ��    ��    : zhaopeng(59430)
    �޸�����    : �����ɽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    VOS_UINT16                              usMsgID;                            /* _H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                              usRxlev;                            /* �����ź�ǿ�� */
    GSM_CBCH_TYPE_ENUM_UINT16               enCBCHType;                         /* CBCH�ŵ����� */
    VOS_UINT16                              usTC;                               /* 51��֡��, ȡֵ��Χ0-7 */
    VOS_UINT32                              ulFN;                               /* ��ǰ֡�� */
    GSM_CBCH_SCHEDULE_INFO_ENUM_UINT16      enScheInfoFlg;                      /* ��ǰ������Ϣ�Ƿ���Ч */
    VOS_UINT16                              usPageIndex;                        /* ���յ�PAGE INDEX */
    VOS_UINT16                              usRsv;
    VOS_UINT16                              usErrFlg;                           /* �������ָʾ */
    VOS_UINT16                              ausData[12];                        /* CBS���� */
} MPH_CBS_DATA_IND_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GAS_MSG_ID_ENUM_UINT16          enMsgID;                                /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                          usReserved;                             /* ����λ */
    VOS_RATMODE_ENUM_UINT32             enMasterMode;                           /* ����Ϊ��ģ��ģʽ */
    VOS_RATMODE_ENUM_UINT32             enSlaveMode;                            /* ����Ϊ��ģ��ģʽ */
    PHY_GAS_BUSINESS_TYPE_ENUM_UINT16   enBusinessType;                         /* SET WORK MODE�����ͣ�GAS�̶���PHY_GAS_BUSINESS_TYPE_NORMAL */
    PHY_GAS_COMM_FLAG_ENUM_UINT16       enNvUpdateFlag;                         /* �Ƿ���Ҫ����NV������ģʽ�̶���FALSE */
} MPH_SET_WORK_MODE_REQ_STRU;
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GAS_MSG_ID_ENUM_UINT16          enMsgID;                                /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                          usReserved;
    VOS_RATMODE_ENUM_UINT32             enMasterMode;                           /* ����Ϊ��ģ��ģʽ */
    VOS_RATMODE_ENUM_UINT32             enSlaveMode;                            /* ����Ϊ��ģ��ģʽ */
}MPH_SET_WORK_MODE_CNF_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GAS_MSG_ID_ENUM_UINT16      enMsgID;                                    /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                      usReserved;
} MPH_LTE_MEAS_REQ_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GAS_MSG_ID_ENUM_UINT16      enMsgID;                                    /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                      usReserved;
}MPH_LTE_MEAS_CNF_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GAS_MSG_ID_ENUM_UINT16          enMsgID;            /*_H2ASN_Skip */ /* ԭ������ */
    PHY_GAS_STOP_MEAS_TYPE_ENUM_UINT16  enStopType;         /* ֹͣ���������� */
} MPH_STOP_MEAS_REQ_STRU;
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GAS_MSG_ID_ENUM_UINT16          enMsgID;            /*_H2ASN_Skip */ /* ԭ������ */
    PHY_GAS_STOP_MEAS_TYPE_ENUM_UINT16  enStopType;         /* ֹͣ���������� */
}MPH_STOP_MEAS_CNF_STRU;
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GAS_MSG_ID_ENUM_UINT16      enMsgID;                                    /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                      usReserved;
}MPH_TA_INFO_REQ_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GAS_MSG_ID_ENUM_UINT16      enMsgID;                                    /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                      usTAValue;
}MPH_TA_INFO_CNF_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GAS_MSG_ID_ENUM_UINT16      enMsgID;                                    /*_H2ASN_Skip */ /* ԭ������ */
    GAS_PHY_BG_SEARCH_ENUM_UINT16   enType;                                     /* ��������������� */
} MPH_L_BG_SEARCH_REQ_STRU;
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GAS_MSG_ID_ENUM_UINT16      enMsgID;                                    /*_H2ASN_Skip */ /* ԭ������ */
    GAS_PHY_BG_SEARCH_ENUM_UINT16   enType;                                     /* ��������������� */
    VOS_UINT16                      usResult;                                   /* ������ֹͣ����㱳���� L��ȷ�Ͻ����PHY_SUCCESS��ʾ�ɹ���PHY_FAILURE��ʾʧ�� */
    VOS_UINT16                      usReserved;                                 /* ���λ */
}MPH_L_BG_SEARCH_CNF_STRU;
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GAS_MSG_ID_ENUM_UINT16              enMsgID;            /*_H2ASN_Skip */ /* ԭ������ */
    GAS_PHY_BG_SEARCH_ENUM_UINT16           enType;             /* ��������������� */
} MPH_W_BG_SEARCH_REQ_STRU;
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GAS_MSG_ID_ENUM_UINT16              enMsgID;            /*_H2ASN_Skip */ /* ԭ������ */
    GAS_PHY_BG_SEARCH_ENUM_UINT16           enType;             /* ��������������� */
    VOS_UINT16                              usResult;           /* ������ֹͣ����㱳���� W��ȷ�Ͻ����PHY_SUCCESS��ʾ�ɹ���PHY_FAILURE��ʾʧ�� */
    VOS_UINT16                              usReserved;         /* ���λ */
}MPH_W_BG_SEARCH_CNF_STRU;
typedef struct
{
    VOS_UINT16                              usCellID;           /* С��Cell ID */
    VOS_UINT16                              usArfcn;            /* Ƶ����Ϣ��Я��Ƶ����Ϣ */
    PHY_GAS_GSM_BANDINDICATOR_ENUM_UINT16   enBandIndicator;    /* Ƶ��ָʾ������ΪGPHY���棬�ϱ��������ʱ������ֵ���أ�GPHY����Ҫ���߼����� */
    VOS_UINT16                              usReserved;         /* ����λ */
}PHY_GAS_G_SLAVE_GSM_CELL_INFO_ITEM_STRU;


typedef struct
{
    VOS_UINT16                              usCellNum;      /* ��Ҫ������С������ */
    VOS_UINT16                              usMgsmNum;      /* GSM��������������̬��Ч��IDLE̬���ֶα�����W/T��ģ��GAS��̶�ֵ1 */
    PHY_GAS_G_SLAVE_GSM_CELL_INFO_ITEM_STRU astGsmCellInfo[PHY_GAS_MAX_G_SLAVE_GSM_CELL_NUM];   /* ��Ҫ����GSMС���б� */
}PHY_GAS_G_SLAVE_GSM_CELL_INFO_STRU;
typedef struct
{
    VOS_MSG_HEADER                                                  /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GAS_MSG_ID_ENUM_UINT16              enMsgID;                /* _H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                              usOpid;                 /* ������ʶ */
    PHY_GAS_MASTER_MODE_STATUS_ENUM_UINT16  enMasterModeStatus;     /* ��ģ��ǰ״̬ */
    PHY_GAS_MEAS_COMMAND_ENUM_UINT16        enCommand;              /* ��������ָ�����setup��release */
    PHY_GAS_G_SLAVE_GSM_CELL_INFO_STRU      stSlaveGsmCellLst;      /* �������б�ṹ */
}MPH_G_SLAVE_MEAS_REQ_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                  /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GAS_MSG_ID_ENUM_UINT16              enMsgID;                /* _H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                              usOpid;                 /* ������ʶ */
}MPH_G_SLAVE_MEAS_CNF_STRU;
typedef struct
{
    VOS_UINT16                              usCellID;               /* С��Cell ID */
    VOS_UINT16                              usArfcn;                /* Ƶ����Ϣ��Я��Ƶ����Ϣ */
    PHY_GAS_GSM_BANDINDICATOR_ENUM_UINT16   enBandIndicator;        /* Ƶ��ָʾ������ΪGPHY���棬�ϱ��������ʱ������ֵ���أ�GPHY����Ҫ���߼����� */
    VOS_INT16                               sCarrierRSSI;           /* ����RSSIֵ����ֵ���ȴ�ȷ�� *//* [-111,MAX] */
}PHY_GAS_G_SLAVE_GSM_CELL_RESULT_STRU;


typedef struct
{
    VOS_UINT16                              usCellNum;              /*���������õ�GSM�ز�������*/
    VOS_UINT16                              usReserved;
    PHY_GAS_G_SLAVE_GSM_CELL_RESULT_STRU    astGsmCellRslt[PHY_GAS_MAX_G_SLAVE_GSM_CELL_NUM];   /*GSMС���Ĳ������*/
}PHY_GAS_G_SLAVE_MEAS_RESULT_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                  /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GAS_MSG_ID_ENUM_UINT16              enMsgID;                /* _H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                              usOpid;                 /* ������ʶ */
    PHY_GAS_G_SLAVE_MEAS_RESULT_STRU        stGsmCellRltLst;        /* ��������б� */
}MPH_G_SLAVE_MEAS_IND_STRU;


typedef struct
{
    VOS_UINT16                              usCellID;           /* С��Cell ID */
    VOS_UINT16                              usArfcn;            /* Ƶ����Ϣ��Я��Ƶ����Ϣ */
    PHY_GAS_GSM_BANDINDICATOR_ENUM_UINT16   enBandIndicator;    /* Ƶ��ָʾ������ΪGPHY���棬�ϱ��������ʱ������ֵ���أ�GPHY����Ҫ���߼����� */
    VOS_UINT16                              usReserved;         /* ����λ */
    VOS_UINT16                              usNcc;              /* NCCֵ *//* WT��Ч��䣬L�¾���д��Чֵ0x8 */
    VOS_UINT16                              usBcc;              /* BCCֵ *//* WT��Ч��䣬L�¾���д��Чֵ0x8 */
}PHY_GAS_G_SLAVE_CELL_BSIC_INFO_ITEM_STRU;


typedef struct
{
    VOS_UINT16                          usPeriodT;
    VOS_UINT16                          usReserved;
}PHY_GAS_W2G_DRX_BSIC_TIMER_PARA_STRU;


typedef struct
{
    VOS_UINT16                          usMREP;                                 /* [2��4096] frame FACHOccasion���� */
    VOS_UINT16                          usNTTI;                                 /* Sccpch�����TTI����,{1,2,4,8}frame */
    PHY_GAS_COMM_FLAG_ENUM_UINT16       enInterFreqMeasExistFlag;               /* ��Ƶ�����Ƿ���ڵı�� */
    VOS_UINT16                          usReserved;
}PHY_GAS_W2G_FACH_BSIC_TIMER_PARA_STRU;
typedef struct
{
    VOS_UINT16                          usTGL1;                                 /* ��һ��Transmission Gap�ĳ��Ȱ���TGP�Ͽ�ʱ*/
    VOS_UINT16                          usTGL2;                                 /* �ڶ���Transmission Gap�ĳ��Ȱ���TGP PATTERN*/
    VOS_UINT16                          usTGD;                                  /* Transmission gap distance */
    VOS_UINT16                          usTGPL1;                                /* TGP1�ĳ��� */
}PHY_GAS_W2G_DCH_BSIC_PARA_STRU;


typedef struct
{
    PHY_GAS_COMM_FLAG_ENUM_UINT16       enReConfirmParaValidFlag;               /* ��ȷ��ѹģ�����Ƿ���ڵı�� */
    VOS_UINT16                          usReserved;
    PHY_GAS_W2G_DCH_BSIC_PARA_STRU      stInitBsicTimerPara;                    /* DRX״̬(IDLE̬����PCH̬)GPHY����BSIC��֤�ʱ��Ĳ��� */
    PHY_GAS_W2G_DCH_BSIC_PARA_STRU      stReConfirmBsicTimerPara;               /* DRX״̬(IDLE̬����PCH̬)GPHY����BSIC��֤�ʱ��Ĳ��� */
}PHY_GAS_W2G_DCH_BSIC_TIMER_PARA_STRU;
typedef struct
{
    PHY_GAS_MASTER_MODE_STATUS_ENUM_UINT16                  enMasterModeStatus; /* ��ģ��ǰ״̬ */
    VOS_UINT16                                              usReserved;         /* ����λ */
    union
    {
        PHY_GAS_W2G_DRX_BSIC_TIMER_PARA_STRU                stDrxBsicTimerPara; /* ��ӦPHY_GAS_MASTER_MODE_STATUS_IDLE��PHY_GAS_MASTER_MODE_STATUS_URA_PCH��PHY_GAS_MASTER_MODE_STATUS_CELL_PCH */
        PHY_GAS_W2G_FACH_BSIC_TIMER_PARA_STRU               stFachBsicTimerPara;/* ��ӦPHY_GAS_MASTER_MODE_STATUS_FACH */
        PHY_GAS_W2G_DCH_BSIC_TIMER_PARA_STRU                stDchBsicTimerPara; /* ��ӦPHY_GAS_MASTER_MODE_STATUS_DCH */
    } u;
}PHY_GAS_W2G_BSIC_TIMER_PARA_STRU;
typedef struct
{
    VOS_UINT16                                  usCellNum;                      /* С������ */
    PHY_GAS_VERIFY_TIME_INDEX_ENUM_UINT16       enVerifyTimeIdx;                /* T/L 2G GSM BSIC��ʼȷ�Ϻ���ȷ�ϵ�ʱ������ */
    PHY_GAS_W2G_BSIC_TIMER_PARA_STRU            stW2GBsicTimerPara;             /* W2G BSIC��֤ʱ�����,T/L ��ʹ�� */
    PHY_GAS_G_SLAVE_CELL_BSIC_INFO_ITEM_STRU    astGsmCellInfo[PHY_GAS_MAX_G_SLAVE_GSM_BSIC_CELL_NUM];    /* ��Ҫ������GSMС�� */
}PHY_GAS_G_SLAVE_CELL_BSIC_INFO_STRU;


typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    PHY_GAS_MSG_ID_ENUM_UINT16              enMsgID;            /*_H2ASN_Skip*/  /* ԭ������*/
    VOS_UINT16                              usOpid;             /* ������ʶ */
    PHY_GAS_G_SLAVE_CELL_BSIC_INFO_STRU     stGsmCellBsicLst;   /* ��Ҫ������GSMС���б� */
}MPH_G_SLAVE_BSIC_VERIFIED_REQ_STRU;


typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    PHY_GAS_MSG_ID_ENUM_UINT16              enMsgID;            /*_H2ASN_Skip*/  /* ԭ������*/
    VOS_UINT16                              usOpid;             /* ������ʶ */

}MPH_G_SLAVE_BSIC_VERIFIED_CNF_STRU;
typedef struct
{
    VOS_UINT16                                              usCellID;                           /* С��Cell ID */
    VOS_UINT16                                              usArfcn;                            /* Ƶ����Ϣ��Я��Ƶ����Ϣ */
    PHY_GAS_GSM_BANDINDICATOR_ENUM_UINT16                   enBandIndicator;                    /* Ƶ��ָʾ������ΪGPHY���棬�ϱ��������ʱ������ֵ���أ�GPHY����Ҫ���߼����� */
    VOS_UINT16                                              usNcc;                              /* NCCֵ */
    VOS_UINT16                                              usBcc;                              /* BCCֵ */
    VOS_UINT16                                              usTimeAlignment;                    /* TA */
    VOS_UINT32                                              ulFnOffset;                         /* FN */
    PHY_GAS_INTERRAT_TO_GSM_TIMING_INFO_STRU                stInterRat2GsmTimingOffset;         /* ��ϵͳ��GSM�Ķ�ʱ������Ϣ */
}PHY_GAS_G_SLAVE_CELL_BSIC_RLT_ITEM_STRU;


typedef struct
{
    VOS_UINT16                              usCellNum;              /* С������ */
    VOS_UINT16                              usReseverd;             /* ����λ */
    PHY_GAS_G_SLAVE_CELL_BSIC_RLT_ITEM_STRU astGsmCellBsicRslt[PHY_GAS_MAX_G_SLAVE_GSM_BSIC_CELL_NUM];    /* ����С������б� */
}PHY_GAS_G_SLAVE_CELL_BSIC_RLT_STRU;
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    PHY_GAS_MSG_ID_ENUM_UINT16              enMsgID;            /*_H2ASN_Skip*/  /* ԭ������*/
    VOS_UINT16                              usOpid;             /* ������ʶ */
    PHY_GAS_G_SLAVE_CELL_BSIC_RLT_STRU      stGsmCellBsicRslt;  /* GSMС��������� */
}MPH_G_SLAVE_BSIC_VERIFIED_IND_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip */
    PHY_GAS_MSG_ID_ENUM_UINT16      enMsgID;                                    /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                      usReserved;
} MPH_TDS_MEAS_REQ_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip */
    PHY_GAS_MSG_ID_ENUM_UINT16      enMsgID;                                    /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                      usReserved;
}MPH_TDS_MEAS_CNF_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip */
    PHY_GAS_MSG_ID_ENUM_UINT16      enMsgID;                                    /*_H2ASN_Skip */ /* ԭ������ */

    /* ��������ϱ��ı仯����, ��λ:dBm ,ȡֵ��Χ[1,5], �����ֵ����[1,5]��Χ��,
       ���������Ȼʹ��Ĭ��ֵ 3 */
    VOS_UINT16                      usScellMeasRptGapThresh;
    VOS_UINT16                      ausResv[2];
} MPH_MEAS_RLT_RPT_CTRL_REQ_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip */
    PHY_GAS_MSG_ID_ENUM_UINT16      enMsgID;                                    /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                      usReserved;
}MPH_MEAS_RLT_RPT_CTRL_CNF_STRU;



typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip */
    PHY_GAS_MSG_ID_ENUM_UINT16      enMsgID;                                    /*_H2ASN_Skip */ /* ԭ������ */
    PHY_GAS_COMM_FLAG_ENUM_UINT16   enStartFlag;                                /* _TRUE:������_FALSE:������ */
}MPH_NOTCH_CHANNEL_IND_STRU;
typedef struct
{
    VOS_MSG_HEADER                                      /*_H2ASN_Skip */
    PHY_GAS_MSG_ID_ENUM_UINT16      enMsgID;            /*_H2ASN_Skip */ /* ԭ������ */
    PHY_GAS_COMM_FLAG_ENUM_UINT16   enUplinkCloseFlag;  /* _TRUE:�ر����з��䣬_FALSE:���ر����з��� */
}MPH_TDS_LTE_RF_CONTROL_IND_STRU;
typedef struct
{
    VOS_MSG_HEADER                                      /*_H2ASN_Skip */
    PHY_GAS_MSG_ID_ENUM_UINT16      enMsgID;            /*_H2ASN_Skip */ /* ԭ������ */
    PHY_GAS_COMM_FLAG_ENUM_UINT16   enNarrowDcsFlag;    /* _TRUE:������_FALSE:������ */
}MPH_BAND_CFG_IND_STRU;
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip */
    PHY_GAS_MSG_ID_ENUM_UINT16      enMsgID;                                    /*_H2ASN_Skip */ /* ԭ������ */
    PHY_GAS_COMM_FLAG_ENUM_UINT16   enCsFlg;                                    /* CS״̬��־��_TRUE:���ڣ�_FALSE:������ */
    PHY_GAS_COMM_FLAG_ENUM_UINT16   enPsFlg;                                    /* PS״̬��־��_TRUE:���ڣ�_FALSE:������ */
    PHY_GAS_COMM_FLAG_ENUM_UINT16   enSigFlg;                                   /* ����״̬��־��_TRUE:���ڣ�_FALSE:������ */
    PHY_GAS_COMM_FLAG_ENUM_UINT16   enHighPsFlg;                                /* HIGH PS״̬��־��_TRUE:���ڣ�_FALSE:������ */
    VOS_UINT16                      usReserved;
}MPH_AS_CONNECTED_STATUS_IND_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip */
    PHY_GAS_MSG_ID_ENUM_UINT16      enMsgID;                                    /*_H2ASN_Skip */ /* ԭ������ */
    PHY_GAS_COMM_FLAG_ENUM_UINT16   enAvailableFlg;                             /* ��Դ���ñ�־��_TRUE:���ã�_FALSE:������ */
}MPH_RADIO_RESOURCE_IND_STRU;
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GAS_MSG_ID_ENUM_UINT16      enMsgID;                                    /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                      usReserved;
} MPH_RXLEV_STOP_REQ_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GAS_MSG_ID_ENUM_UINT16      enMsgID;                                    /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                      usReserved;
}MPH_RXLEV_STOP_CNF_STRU;


typedef struct
{
    VOS_MSG_HEADER                                      /*_H2ASN_Skip */
    PHY_GAS_MSG_ID_ENUM_UINT16      enMsgID;            /*_H2ASN_Skip */ /* ԭ������ */
    PHY_GAS_COMM_FLAG_ENUM_UINT16   enRseOnFlag;        /* _TRUE:RSE ON��_FALSE:RSE OFF */
}MPH_RSE_CFG_IND_STRU;
typedef struct
{
    VOS_MSG_HEADER                                      /*_H2ASN_Skip */
    PHY_GAS_MSG_ID_ENUM_UINT16      enMsgID;            /*_H2ASN_Skip */ /* ԭ������ */
    PHY_GAS_COMM_FLAG_ENUM_UINT16   enRfShareFlag;      /*_TRUE:����RF(DSDS˫��ģʽ)��_FALSE:��ռRF(��DSDS˫��ģʽ) */
}MPH_AS_ACTIVE_DSDS_STATUS_IND_STRU;
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip */
    PHY_GAS_MSG_ID_ENUM_UINT16                  enMsgID;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usReserved;
    PHY_GAS_BCCH_READING_CELL_TYPE_ENUM_UINT16  enCellType;                     /* 0: SCELL BCCH READING; 1: Pending cell BCCH READING */
    VOS_UINT16                                  usArfcn;
    PHY_GAS_BCCH_READING_ACT_ENUM_UINT16        enReadFlag;
    VOS_UINT16                                  usBitMap;
}MPH_UPDATE_BCCH_READING_REQ_STRU;
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip */
    PHY_GAS_MSG_ID_ENUM_UINT16                  enMsgID;                        /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                                  usReserved;
    PHY_GAS_BCCH_READING_CELL_TYPE_ENUM_UINT16  enCellType;                     /* 0: SCELL BCCH READING; 1: Pending cell BCCH READING */
    VOS_UINT16                                  usArfcn;
    VOS_UINT16                                  usBS_PA_MFRMS;                  /* Ѱ��������51��֡������ */
    VOS_UINT16                                  usBS_AG_BLKS_REGS;              /* ÿ��CCCH��AGCH�������� */
    VOS_UINT16                                  usBCCH_COMBINED;                /* CCCH�Ƿ���SDCCH���,0����ϣ�1��� */
    VOS_UINT16                                  usCCCH_GROUP;                   /* CCCH_GROUP��45.002 6.5.2,[0 .. BS_CC_CHANS-1] */
    VOS_UINT16                                  usPAGE_MULTIFRAME51_INDEX;      /* Ѱ�����ڵڼ���51��֡, 45.002 6.5.3 */
    VOS_UINT16                                  usPAGE_BLOCK_INDEX;             /* 51��֡��PAGE BLOCK ��INDEX */
}MPH_UPDATE_PAGE_PARA_REQ_STRU;
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip */
    PHY_GAS_MSG_ID_ENUM_UINT16             usMsgID;                             /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                             usReserved;
}MPH_UPDATE_BCCH_READING_CNF_STRU;





typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip */
    PHY_GAS_MSG_ID_ENUM_UINT16             usMsgID;                             /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                             usReserved;
}MPH_UPDATE_PAGE_PARA_CNF_STRU;

/*****************************************************************************
 �ṹ��    : MPH_AFC_LOCK_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : AFC���������Ϣ�ϱ�

*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    PHY_GAS_MSG_ID_ENUM_UINT16          enMsgID;                                /* ԭ������*/   /*_H2ASN_Skip*/
    VOS_UINT16                          usAfcLockFlag;                          /* afc ������־��0δ����,1���� */
    VOS_UINT16                          usAfcCurrVal;                           /* ��ǰAFC��ֵ */
    VOS_UINT16                          usReserve;                              /* ���� */
} MPH_AFC_LOCK_IND_STRU;
typedef struct
{
    VOS_UINT32                          ulMcc;                                  /* MCC,3 bytes      */
    VOS_UINT32                          ulMnc;                                  /* MNC,2 or 3 bytes */
    VOS_UINT16                          usLac;                                  /* [0x0001��0xFFFE] λ������  */  
    VOS_UINT16                          usCellId;                               /* С�� ID  */
}PHY_GAS_CELL_CGI_DESCR_STRU;

/*****************************************************************************
 �ṹ��    : MPH_CAMP_SCELL_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : GASֹͣ����֮��ָ��פ��ĳ��С����

*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    PHY_GAS_MSG_ID_ENUM_UINT16          enMsgID;                                /* ԭ������*/   /*_H2ASN_Skip*/
    VOS_UINT16                          usArfcn;                                /* פ��С����Ƶ��ţ�Я����Ƶ��ָʾ */
    VOS_UINT16                          usBsic;                                 /* פ��С����BSIC */
    VOS_UINT16                          usReserve;                              /* ����λ */
    PHY_GAS_CELL_CGI_DESCR_STRU         stCgi;                                  /* С����CGI��Ϣ */
} MPH_CAMP_SCELL_REQ_STRU;

/*****************************************************************************
 �ṹ��    : MPH_CAMP_SCELL_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MPH_CAMP_SCELL_REQ��ȷ��ԭ�

*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    PHY_GAS_MSG_ID_ENUM_UINT16          enMsgID;                                /* ԭ������*/   /*_H2ASN_Skip*/
    PHY_GAS_COMM_FLAG_ENUM_UINT16       enResult;                               /* פ���ɹ���� */
} MPH_CAMP_SCELL_CNF_STRU;


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/


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

#endif /* end of __PHYGASINTERFACE_H__ */

