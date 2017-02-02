/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : RrcPhyInterface.h
  �� �� ��   : ����
  ��    ��   : chengong
  ��������   : 2006��08��29��
  ����޸�   : �����µı�̹淶�ƶ�Hi4131�������ӿ����ݽṹ
               ������HSDPA/HSUPA �����ݽṹ
  ��������   : RrcPhyInterface.h ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2006��10��31��
    ��    ��   : Jinying
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __RRCPHYINTERFACE_H__
#define __RRCPHYINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "Hi_Config.h"
#include "product_config.h"
#include "wasphycomminterface.h"
#include "WUeSpec.h"

#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/

/**************һЩ����֧�ֿ���********************/
#define RRC_PHY_CBS_SWITCH                      (FEATURE_WCBS)     /*����Ϊ1��ʾ֧��,Ϊ0��ʾ��֧��*/

/*************�����ŵ���صĺ�*********************/

/*6720���֧�ֵ������ŵ���*/
#define  RRC_PHY_MAX_PHYCHAN_NUM                (10)     /*nDLDPCH(FDPCH)+1ULDPCH(ULDPCCH)+1HSDPA+1 UL HSUPA + 1 DL HSUPA��n=6Ϊ�����������·��*/

/*6720���֧�ֵ�RL ��Ŀ*/
#define  RRC_PHY_MAX_RL_NUM                     (6)

/* ����ֹͣ������Сֵ */
#define  RRC_PHY_MEAS_STOP_TRESH_MIN            (0)

/* ����ֹͣ�������ֵ */
#define  RRC_PHY_MEAS_STOP_TRESH_MAX            (20)

#define  RRC_PHY_MAX_SLOT_PLUS1_NUM             (16)


/*�����ŵ��������*/
#define  RRC_PHY_MAX_DLDPCH_CHAN_NUM            (1)

#define  RRC_PHY_MAX_SIGNATURE_NUM              (16)

#define  RRC_PHY_MAX_SUBCHANNEL_NUM             (12)

#define  RRC_PHY_MAX_ASC_NUM                    (8)

/**************����ϴ����ŵ���صĺ�***************/

#define  RRC_PHY_MAX_TRCH_NUM                   (8)

#define  RRC_PHY_CCTRCH_NUM                     (1)     /*Ҫ���õ���������ϴ����ŵ�����HSDPA��HSUPA����Ҫ��������ϴ����ŵ�*/

#define  RRC_PHY_CCTRCH_PARA_LEN                (4096)  /*CCTRCH �ŵ������ĳ���*/

#define  RRC_PHY_MAX_AMR_TRCH_NUM               (3)     /*AMR����������������ӳ���ϵ���� */

/*************С��ѡ����ѡ�Ͳ�����صĺ�************/
#define  RRC_PHY_MAX_CANDIDATE_SRCD             (8)     /*���ֵ��֪����ʲôʹ�ã�û�м������õĵط�*/

#define  RRC_PHY_MAX_ADDITIONAL_CARRIER_NUM     (2)     /* Used FreqƵ����⣬֧�ֵ������Ƶ�� */


#define  RRC_PHY_MAX_EACH_FREQ_CELL_NUM         (64)    /*��Ƶ��������ÿ����ƵЯ�������С������*/

#define  RRC_PHY_MAX_INTRA_FREQ_CELL_NUM        (64)    /*ͬƵ��������Я�������С������*/

#define  RRC_PHY_MAX_INTER_FREQ_CELL_NUM        (64)    /*��Ƶ��������У�Я�������С������*/
#define RRC_PHY_MAX_INTER_RAT_LTE_FREQ           (8)    /* W�²���LTEƵ����� */
#define RRC_PHY_MAX_SLAVE_WCDMA_CARRIER_NUM      (3)    /* wΪ��ģʱ��WCDMA��Ƶ����� */

#define RRC_PHY_MAX_SLAVE_WCDMA_CELL_PER_FREQ_NUM (32)


#define  RRC_PHY_MAX_POS_CELL_NUM               (64)   /*��λҪ���������С����*/

#define  RRC_PHY_MAX_SEC_UL_FREQ_CELL_NUM       (32)    /*��Ƶ������Ҫ����Second UL Freq�����С������*/

#define  RRC_PHY_MAX_ADJACENT_FREQ_CELL_NUM     (RRC_PHY_MAX_SEC_UL_FREQ_CELL_NUM+RRC_PHY_MAX_INTER_FREQ_CELL_NUM)    /*��Ƶ��������Я�������С������*/

#define  PHY_RRC_MAX_REPORT_EACH_FREQ_CELL_NUM         (32) /*��Ƶ�����ϱ�ʱ��Я����ÿ����Ƶ�����С������*/

#define  PHY_RRC_MAX_REPORT_INTRA_FREQ_CELL_NUM        (32) /*ͬƵ�����ϱ�ʱ��Я�������С������*/

#define  PHY_RRC_MAX_REPORT_SEC_UL_FREQ_CELL_NUM       (32) /*ͬƵ�����ϱ�ʱ��Я����Second UL FreqС��������*/

/**************С��������صĺ�***********************/

#define  RRC_PHY_FREQ_BAND_MAX_NUM              (6)    /*���������Ƶ����Ϊ6��,��UE֧�ֵ�Ƶ��������һ��*/

#define  RRC_PHY_MAX_RSSI_FREQ_GROUP_NUM        (10)    /*��ʼ���ϱ�������Ƶ������*/

#define  RRC_PHY_MAX_RSSI_FREQ_RPT_NUM          (8)    /*��ʼ���ϱ���ÿ������Ƶ�����*/

#define  RRC_PHY_RSSI_Threshold                 (-960)  /* ��ʼ�� RSSI���ޣ���������ĳƵ��RSSI����ֵС�ڸ����޵Ĳ��ϱ�*/

#define RRC_PHY_HISTORY_FREQS_MAX_NUM           (6)

#define  RRC_PHY_BG_SEARCH_Threshold_Invalid    (0x7FFF)
/**************ѹ��ģʽ��صĺ�***********************/
#define  RRC_PHY_MAX_TGPS                       (6)


/**************HSDPA��صĺ�***************************/
#define  RRC_PHY_MAX_HSSCCH_NUM                 (4)     /*����HSSCCH��Ϊ4��*/
#define  RRC_PHY_MAX_HSDPA_PROCESSES            (16)    /*����HSDPA������Ϊ 16��*/
#define  RRC_PHY_MAX_QUEUE_NUM                  (8)     /*����HSDPA������Ϊ8��*/
#define  RRC_PHY_MAX_MAC_D_PDU_SIZES_NUM        (8)     /*����HSDPA Mad_D PDU Size��Ϊ8��*/

/**************HSUPA��صĺ�***************************/
#define  RRC_PHY_MAX_EDCH_REFTFCI_NUM           (8)     /*����EDCH_�ο�TFCI��Ϊ8��*/
#define  RRC_PHY_MAC_EDCH_MAX_MACD_FLOW_NUM     (8)     /*����EDCH MAC_d����ĿΪ8��*/
#define  RRC_PHY_MAX_RLC_PDU_SIZE_NUM_PER_LOCH  (32)    /*ÿ���߼��ŵ��������õ�����RLC PDU��Ŀ*/

#define  RRC_PHY_ACTIVE_NOW                     (-1)    /*��������*/


/**************CBS��صĺ�****************************/
#define  RRC_PHY_MAX_DRXBS_OFFSETLSTLEN         (255)

/********************֧�ֵĴ�ӡ�Ĵ����������Ŀ***************/
#define  RRC_PHY_MAX_RTT_REG_NUM                (32)


/* һ��Ƶ������е�Ƶ����� */
#define  RRC_PHY_MAX_FREQ_NUM_PER_BAND          (292)    /*RSSI���ϱ���ÿ��BAND����Ƶ�����*/

/*V3 R7_7C1 Start */
/* UE֧������߼��ŵ����� */
#define  RRC_PHY_MAX_LOCH_NUM                   (16)
/* V3 R7_7C1 End */

#define RR_PHY_MAX_MSG_SIZE                     (230)
#define PHY_RR_MAX_MSG_SIZE                     (80)


#define RRC_PHY_MAX_TB_SIZE_NUM                 (2)
#define RRC_PHY_MAX_HSSCCH_LESS_TB_NUM          (4)

#define RRC_PHY_INVALID_MSG_OPID                        (0XFFFF)
#define PHYITF_EDCH_TRANS_CONTINU_BACK_OFF_INFINITY     (0XFFFF)

/* ������Ҫ�ͷŵĲ������͵�MASK */
#define RRC_PHY_REL_MEAS_TYPE_INTRA_FREQ                      0x0001
#define RRC_PHY_REL_MEAS_TYPE_INTER_FREQ                      0x0002
#define RRC_PHY_REL_MEAS_TYPE_INTER_RAT_GSM                   0x0004
#define RRC_PHY_REL_MEAS_TYPE_INTER_RAT_LTE                   0x0008
#define RRC_PHY_REL_MEAS_TYPE_ALL                             0x0040


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

/*****************************************************************************
 ö����    : PHYITF_IDLE_MEAS_TYPE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : IDLE̬������������ö��
*****************************************************************************/
enum    PHYITF_IDLE_MEAS_TYPE_ENUM
{
    PHYITF_IDLE_MEAS_TYPE_INTRA_FREQ      = 0,    /* ͬƵ������Ϣ */    /* _H2ASN_MsgChoice PHYITF_INTRA_FREQ_CELL_INFO_STRU */
    PHYITF_IDLE_MEAS_TYPE_INTER_FREQ      = 1,    /* ��Ƶ������Ϣ */    /* _H2ASN_MsgChoice PHYITF_INTER_FREQ_CELL_INFO_STRU */
    PHYITF_IDLE_MEAS_TYPE_INTER_RAT       = 2,    /* ��ϵͳGSM������Ϣ */  /* _H2ASN_MsgChoice PHYITF_INTER_RAT_CELL_INFO_STRU */
    PHYITF_IDLE_MEAS_TYPE_INTER_RAT_LTE   = 3,    /* ��ϵͳLTE������Ϣ */  /* _H2ASN_MsgChoice PHYITF_INTER_RAT_LTE_CELL_INFO_STRU */
    PHYITF_IDLE_MEAS_TYPE_BUTT

};
typedef VOS_UINT16  PHYITF_IDLE_MEAS_TYPE_ENUM_UINT16;

/*****************************************************************************
 ö����    : PHYITF_CONN_MEAS_TYPE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : CONN̬������������ö��
*****************************************************************************/
enum    PHYITF_CONN_MEAS_TYPE_ENUM
{
    PHYITF_CONN_MEAS_TYPE_INTRA_FREQ      = 0,    /* ͬƵ������Ϣ */    /* _H2ASN_MsgChoice PHYITF_INTRA_FREQ_CELL_INFO_STRU */
    PHYITF_CONN_MEAS_TYPE_INTER_FREQ      = 1,    /* ��Ƶ������Ϣ */    /* _H2ASN_MsgChoice PHYITF_INTER_FREQ_CELL_INFO_STRU */
    PHYITF_CONN_MEAS_TYPE_INTER_RAT       = 2,    /* ��ϵͳGSM������Ϣ */  /* _H2ASN_MsgChoice PHYITF_INTER_RAT_CELL_INFO_STRU */
    PHYITF_CONN_MEAS_TYPE_INTER_RAT_LTE   = 3,    /* ��ϵͳLTE������Ϣ */  /* _H2ASN_MsgChoice PHYITF_INTER_RAT_LTE_CELL_INFO_STRU*/
    PHYITF_CONN_MEAS_TYPE_BUTT

};
typedef VOS_UINT16  PHYITF_CONN_MEAS_TYPE_ENUM_UINT16;


/*****************************************************************************
 ö����    : PHYITF_IDLE_MEAS_REQ_END_FLAG_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : �������������־ö��
*****************************************************************************/
enum    PHYITF_MEAS_REQ_END_FLAG_ENUM
{
    PHYITF_MEAS_REQ_END_FLAG_FALSE = 0,    /* IDLE̬�����������ö�٣�0����ʾδ���� */ /* _H2ASN_MsgChoice RRC_PHY_IDLE_MEASURE_REQ_STRU */
    PHYITF_MEAS_REQ_END_FLAG_TRUE  = 1,    /* IDLE̬�����������ö�٣�1����ʾ���� */   /* _H2ASN_MsgChoice RRC_PHY_IDLE_MEASURE_REQ_STRU */
    PHYITF_MEAS_REQ_END_FLAG_BUTT
};

typedef VOS_UINT16  PHYITF_MEAS_REQ_END_FLAG_ENUM_UINT16;


/*****************************************************************************
 ö����    : PHYITF_PHYCH_TYPE_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : �����ŵ�����ö��
*****************************************************************************/

enum    PHYITF_PHYCH_TYPE_ENUM
{

    PHYITF_PHY_NONE                     = 0,
    PHYITF_PHY_SCCPCH                   = 1,                /* _H2ASN_MsgChoice PHYITF_SCCPCH_PARA_STRU */
    PHYITF_PHY_DLDPCH                   = 2,                /* _H2ASN_MsgChoice PHYITF_DOWNLINK_DPCH_PARA_STRU */
    PHYITF_PHY_PICH                     = 4,                /* _H2ASN_MsgChoice PHYITF_PICH_STRU */
    PHYITF_PHY_AICH                     = 5,                /* _H2ASN_MsgChoice PHYITF_AICH_STRU */
    PHYITF_PHY_PRACH                    = 20,               /* _H2ASN_MsgChoice PHYITF_PRACH_STRU */
    PHYITF_PHY_ULDPCH                   = 22,               /* _H2ASN_MsgChoice PHYITF_UPLINK_DPCH_STRU */
    PHYITF_PHY_HSDPA                    = 32,               /* _H2ASN_MsgChoice PHYITF_HSDPA_PHY_STRU */
    PHYITF_PHY_UL_HSUPA                 = 64,               /* _H2ASN_MsgChoice PHYITF_UL_HSUPA_PHY_STRU */
    PHYITF_PHY_DL_HSUPA                 = 128,              /* _H2ASN_MsgChoice PHYITF_DL_HSUPA_PHY_STRU */
    PHYITF_PHY_FDPCH                    = 256,              /* _H2ASN_MsgChoice PHYITF_DOWNLINK_FDPCH_PARA_STRU */
/*V3 R7_7C1 Start */
    PHYITF_PHY_HSDPAPLUS                = 512,              /* _H2ASN_MsgChoice PHYITF_HSDPAPLUS_PHY_STRU */
/* V3 R7_7C1 End */

    PHYITF_PHY_FACH_HSDPAPLUS           = 513,              /* _H2ASN_MsgChoice PHYITF_FACH_HSDPAPLUS_PHY_STRU */
    PHYITF_PHY_SCND_HSDPAPLUS           = 514,              /* _H2ASN_MsgChoice PHYITF_SCND_HSDPAPLUS_PHY_STRU */
    PHYITF_PHY_SCND_UL_HSUPA            = 515,              /* _H2ASN_MsgChoice PHYITF_SCND_UL_HSUPA_PHY_STRU */
    PHYITF_PHY_SCND_DL_HSUPA            = 516,              /* _H2ASN_MsgChoice PHYITF_SCND_DL_HSUPA_PHY_STRU */
    PHYITF_PHY_SCND_FDPCH               = 517,              /* _H2ASN_MsgChoice PHYITF_SCND_DL_FDPCH_PARA_STRU */
    PHYITF_PHY_E_RACH                   = 518,             /* _H2ASN_MsgChoice PHYITF_E_RACH_REQ_STRU */
    PHYITF_PHY_BUTT

};
typedef VOS_UINT16 PHYITF_PHYCH_TYPE_ENUM_UINT16;


/*****************************************************************************
 ö����    : PHYITF_CCTRCH_ID_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : CCTRCH �ŵ�ID
*****************************************************************************/

enum    PHYITF_CCTRCH_ID_ENUM
{

    PHYITF_CCTRCH_PCCPCH                = 0,    /*ʵ�ʲ���ҪRRC����PCCPCH����ϴ����ŵ�����������ΪPHY��MAC�ӿ����д˲������˴�������ֵ�ѱ�PCCPCHռ��*/
    PHYITF_CCTRCH_SCCPCH                = 1,    /* _H2ASN_MsgChoice PHYITF_DL_CCTRCH_STRU */
    PHYITF_CCTRCH_DLDPCH                = 2,    /* _H2ASN_MsgChoice PHYITF_DL_CCTRCH_STRU */
    PHYITF_CCTRCH_PRACH                 = 3,    /* _H2ASN_MsgChoice PHYITF_UL_CCTRCH_STRU */
    PHYITF_CCTRCH_ULDPCH                = 4,    /* _H2ASN_MsgChoice PHYITF_UL_CCTRCH_STRU */
    PHYITF_CCTRCH_HSDPA                 = 6,    /*ʵ�ʲ���ҪRRC����HSDPA����ϴ����ŵ�����������ΪPHY��MAC�ӿ����д˲������˴�������ֵ�ѱ�HSDPA ռ��*/
    PHYITF_CCTRCH_HSUPA                 = 7,    /*ʵ�ʲ���ҪRRC����HSUPA����ϴ����ŵ�����������ΪPHY��MAC�ӿ����д˲������˴�������ֵ�ѱ�HSUPA ռ��*/

    PHYITF_CCTRCH_ALL                   = 255,  /*���ͷ����д����ŵ�ʱʹ��*/

    PHYITF_CCTRCH_BUTT

};
typedef VOS_UINT16 PHYITF_CCTRCH_ID_ENUM_UINT16;



/*****************************************************************************
 ö����    : PHYITF_TIMING_INDIACTION_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : HHO ��ʱָʾ��Ϣ
*****************************************************************************/

enum    PHYITF_TIMING_INDIACTION_ENUM
{
    PHYITF_TIME_INITIALISE              = 0,    /* ��ʶӲ�л�����ʱ��ʽΪ��ʼ�� */
    PHYITF_TIME_MAINTAIN                = 1,    /* ��ʶӲ�л�����ʱ��ʽΪά�� */
    PHYITF_TIME_INITIAL_RESUME          = 2,    /* ��ʶӲ�л�ʧ�ܣ��ָ���ʱ��ʼ�� */
    PHYITF_TIME_MAINTAIN_RESUME         = 3,    /* ��ʶӲ�л�ʧ�ܣ��ָ���ʱά�� */
    PHYITF_TIME_INVALID_MAINTAIN        = 4,    /* ��ʶ��Ӳ�л�*/
    PHYITF_TIME_INTERRAT_RESUME         = 5,    /* ��ϵͳ�л����� */

    PHYITF_TIME_BUTT

};
typedef VOS_UINT16 PHYITF_TIMING_INDIACTION_ENUM_UINT16;



/*****************************************************************************
 ö����    : PHYITF_CELL_ADJUGE_TYPE_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : PHYITF_CELL_ADJUGE_PARA_INFO_STRU�е�С������
*****************************************************************************/

enum    PHYITF_CELL_ADJUGE_TYPE_ENUM
{
    PHYITF_CELL_NO_HCS_TYPE     = 0,            /*��HCSС��*/
    PHYITF_CELL_HCS_TYPE        = 1,            /*HCSС��*/

    PHYITF_CELL_ADJUGE_TYPE_BUTT

};
typedef VOS_UINT16 PHYITF_CELL_ADJUGE_TYPE_ENUM_UINT16;

/*****************************************************************************
 ö����    : PHYITF_SERVE_CELL_STATUS_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ����С��״̬
*****************************************************************************/

enum    PHYITF_SERVE_CELL_STATUS_ENUM
{
    PHYITF_SERV_CELL_NOT_BAR    = 0,
    PHYITF_SERV_CELL_BAR        = 1,

    PHYITF_SERV_CELL_STATUS_BUTT
};
typedef VOS_UINT16 PHYITF_SERVE_CELL_STATUS_ENUM_UINT16;


/*****************************************************************************
 ö����    : PHYITF_CELL_SEARCH_FLAG_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : С��ѡ���־
*****************************************************************************/

enum    PHYITF_CELL_SEARCH_FLAG_ENUM
{
    PHYITF_CELL_SEARCH_FLAG_ABSENT   = 0,
    PHYITF_CELL_SEARCH_FLAG_PRESENT  = 1,
    PHYITF_CELL_SEARCH_FLAG_INVALID  = 2,

    PHYITF_CELL_SEARCH_FLAG_BUTT
};
typedef VOS_UINT16 PHYITF_CELL_SEARCH_FLAG_ENUM_UINT16;


/*****************************************************************************
 ö����    : PHYITF_MEAS_QUANTITY_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : С��ѡ���־
*****************************************************************************/

enum    PHYITF_MEAS_QUANTITY_ENUM
{
    PHYITF_MEAS_QUANTITY_RSCP        = 0,
    PHYITF_MEAS_QUANTITY_ECN0        = 1,

    PHYITF_MEAS_QUANTITY_BUTT
};
typedef VOS_UINT16 PHYITF_MEAS_QUANTITY_ENUM_UINT16;


/*****************************************************************************
 ö����    : PHYITF_E_DPDCH_MAX_CHLS_CODES_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : HSUPA ��SF�������
*****************************************************************************/

enum    PHYITF_E_DPDCH_MAX_CHLS_CODES_ENUM
{
    PHYITF_E_DPDCH_MAX_CHLS_CODES_SF256             = 0,
    PHYITF_E_DPDCH_MAX_CHLS_CODES_SF128             = 1,
    PHYITF_E_DPDCH_MAX_CHLS_CODES_SF64              = 2,
    PHYITF_E_DPDCH_MAX_CHLS_CODES_SF32              = 3,
    PHYITF_E_DPDCH_MAX_CHLS_CODES_SF16              = 4,
    PHYITF_E_DPDCH_MAX_CHLS_CODES_SF8               = 5,
    PHYITF_E_DPDCH_MAX_CHLS_CODES_SF4               = 6,
    PHYITF_E_DPDCH_MAX_CHLS_CODES_SF4X2             = 7,
    PHYITF_E_DPDCH_MAX_CHLS_CODES_SF2X2             = 8,
    PHYITF_E_DPDCH_MAX_CHLS_CODES_SF4X2_AND_SF2X2   = 9,

    PHYITF_E_DPDCH_MAX_CHLS_CODES_SF_BUTT

};
typedef VOS_UINT16 PHYITF_E_DPDCH_MAX_CHLS_CODES_ENUM_UINT16;


/*****************************************************************************
 ö����    : PHYITF_RVVERSION_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : HSUPA ��RV �汾
*****************************************************************************/

enum    PHYITF_RVVERSION_ENUM
{
    PHYITF_RVVERSION_RV0                = 0,
    PHYITF_RVVERSION_RVTABLE            = 1,

    PHYITF_RVVERSION_BUTT

};
typedef VOS_UINT16 PHYITF_RVVERSION_ENUM_UINT16;


/*****************************************************************************
 ö����    : PHYITF_EDCH_TTI_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : HSUPA ��EDCH TTI
*****************************************************************************/

enum    PHYITF_EDCH_TTI_ENUM
{
    PHYITF_EDCH_TTI_10MS                = 0,
    PHYITF_EDCH_TTI_2MS                 = 1,

    PHYITF_EDCH_TTI_BUTT

};
typedef VOS_UINT16 PHYITF_EDCH_TTI_ENUM_UINT16;

/*****************************************************************************
 ö����    : PHYITF_FACH_OCCASION_MEAS_TYPE_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : FACH ����ʱ������
*****************************************************************************/

enum    PHYITF_FACH_OCCASION_MEAS_TYPE_ENUM
{
    PHYITF_FACH_OCCASION_MEAS_INTER_FREQ         = 0,

    PHYITF_FACH_OCCASION_MEAS_INTER_RAT          = 1,

    PHYITF_FACH_OCCASION_MEAS_INTER_FREQANDRAT   = 2,

    PHYITF_FACH_OCCASION_MEAS_BUTT

};
typedef VOS_UINT16 PHYITF_FACH_OCCASION_MEAS_TYPE_ENUM_UINT16;

/*****************************************************************************
 ö����    : PHYITF_E_CELLFACH_MEAS_PERIOD_TYPE_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : E CELL_FACH ������������
*****************************************************************************/
enum    PHYITF_E_CELLFACH_MEAS_PERIOD_TYPE_ENUM
{
    PHYITF_E_CELLFACH_DRX_STATUS            = 0,                                /* CELL_FACH״̬֧��DRX,��д��ֵ����Ӧ�ṹPHYITF_E_CELLFACH_DRX_INFO_STRU */
    PHYITF_E_CELLFACH_OCCATION_STAUS        = 1,                                /* CELL_FACH״̬�²�֧��DRX�������д��ֵ,��Ӧ�ṹPHYITF_E_CELLFACH_MEAS_PARA_STRU */
    PHYITF_E_CELLFACH_MEAS_INVALID          = 2,                                /* ��CELL_FACH״̬����д��ֵ */
    PHYITF_E_CELLFACH_MEAS_PERIOD_TYPE_BUTT
};
typedef VOS_UINT16 PHYITF_E_CELLFACH_MEAS_PERIOD_TYPE_ENUM_UINT16;


/*****************************************************************************
 ö����    : PHYITF_SCRAMBLE_CODE_CHANGE_TYPE_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : ��������ı��ʶ
*****************************************************************************/

enum    PHYITF_SCRAMBLE_CODE_CHANGE_TYPE_ENUM
{
    PHYITF_SCRAMBLE_CODE_CHANGE            = 0,
    PHYITF_SCRAMBLE_CODE_NO_CHANGE         = 1,
    PHYITF_SCRAMBLE_CODE_CHANGE_INVALID    = 2,

    PHYITF_SCRAMBLE_CODE_CHANGE_TYPE_BUTT

};
typedef VOS_UINT16 PHYITF_SCRAMBLE_CODE_CHANGE_TYPE_ENUM_UINT16;


/*****************************************************************************
 ö����    : PHYITF_SCRAMBL_CODE_TYPE_ENUM_UINT16
 Э����  :
 ASN.1���� : ScramblingCodeType
 ö��˵��  : ��������
*****************************************************************************/
enum    PHYITF_SCRAMBL_CODE_TYPE_ENUM
{
    PHYITF_SHORT_SCRAMBL_CODE              = 0,
    PHYITF_LONG_SCRAMBL_CODE               = 1,
    PHYITF_SCRAMBL_CODE_TYPE_BUTT

} ;
typedef VOS_UINT16 PHYITF_SCRAMBL_CODE_TYPE_ENUM_UINT16;


/*****************************************************************************
 ö����    : PHYITF_UL_DPCH_PWRCTRL_ALGO_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : ���й��ص��㷨
*****************************************************************************/
enum    PHYITF_UL_DPCH_PWRCTRL_ALGO_ENUM
{
    PHYITF_UL_DPCH_PWRCTRL_ALGOR1       = 1,
    PHYITF_UL_DPCH_PWRCTRL_ALGOR2       = 2,

    PHYITF_UL_DPCH_PWRCTRL_ALGOR_BUTT

} ;
typedef VOS_UINT16 PHYITF_UL_DPCH_PWRCTRL_ALGO_UINT16;


/*****************************************************************************
 ö����    : PHYITF_DPC_MODE_TYPE_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : ���й��� DPC Mode Type
*****************************************************************************/
enum    PHYITF_DPC_MODE_TYPE_ENUM
{
    PHYITF_DPC_MODE_SINGLE              = 1,
    PHYITF_DPC_MODE_TRIPLET             = 2,

    PHYITF_DPC_MODE_TYPE_BUTT

} ;
typedef VOS_UINT16 PHYITF_DPC_MODE_TYPE_ENUM_UINT16;


/*****************************************************************************
 ö����    : PHYITF_SCCPCH_DEMODULATE_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : SCCPCH ���ָʾ
*****************************************************************************/

enum    PHYITF_SCCPCH_DEMODULATE_ENUM
{
    PHYITF_SCCPCH_NO_PICH               = 0 ,            /* �ڼ���ʱ��涨��ʱ������SCCPCH��� */
    PHYITF_SCCPCH_WITH_PICH             = 1 ,            /* ����PI������SCCPCH��� */

    PHYITF_SCCPCH_DEMODULATE_BUTT

};

typedef VOS_UINT16 PHYITF_SCCPCH_DEMODULATE_ENUM_UINT16;


/*****************************************************************************
 ö����    : PHYITF_COMPRS_MODE_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : ѹ��ģʽ��
             ��R6��Э�����Ѿ�ɾ���˴�׷�ʽ��
             ֻ����Ƶ���Ӽ���͸߲���ȡ�
             6720оƬ�Ѿ�û���˴�����ã�
             ��6511����֧�֡�
             ������������·��˴�����ã��������
             ��֧�֣��������Ҫ��������ʧ��

*****************************************************************************/
enum    PHYITF_COMPRS_MODE_ENUM
{
    PHYITF_COMPRS_MODE_DUMMY                = 0,
    PHYITF_COMPRS_MODE_SF2                  = 1,
    PHYITF_COMPRS_MODE_HIGHER_LAYER_SCHEDUL = 2,

    PHYITF_COMPRS_MODE_BUTT

} ;

typedef VOS_UINT16 PHYITF_COMPRS_MODE_ENUM_UINT16;


/*****************************************************************************
 ö����    : PHYITF_QUA_MEAS_RPT_CRTR_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ���������ı�׼

*****************************************************************************/
enum    PHYITF_QUA_MEAS_RPT_CRTR_ENUM
{
    PHYITF_QUA_PERIODIC_REPORT                  = 0,    /* _H2ASN_MsgChoice PHYITF_QUA_PERIODIC_CRITERIA_STRU */
    PHYITF_QUA_EVENT_REPORT                     = 1,    /* _H2ASN_MsgChoice PHYITF_QUA_EVENT_CRITERIA_STRU */
    PHYITF_QUA_PERIODIC_AND_EVENT_REPORT        = 2,    /* ֻ����RRC��Ҫͬʱ�ͷ����е��������� */

    PHYITF_QUA_REPORT_BUTT
};

typedef VOS_UINT16 PHYITF_QUA_MEAS_RPT_CRTR_ENUM_UINT16;

/*****************************************************************************
 ö����    : PHYITF_QUA_MEAS_RPT_IND_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ���������Ĳ�������ṹ

*****************************************************************************/
enum    PHYITF_QUA_MEAS_RPT_IND_ENUM
{
    PHYITF_QUA_PERIODIC_RPT_IND              = 0,       /* _H2ASN_MsgChoice PHYITF_QUALITY_PERIO_REPORT_STRU */
    PHYITF_QUA_EVENT_RPT_IND                 = 1,       /* _H2ASN_MsgChoice PHYITF_QUALITY_EVENT_REPORT_STRU */

    PHYITF_QUA_RPT_IND_BUTT
};

typedef VOS_UINT16 PHYITF_QUA_MEAS_RPT_IND_ENUM_UINT16;

/*****************************************************************************
 ö����    : PHYITF_MAC_E_SCHED_GRANT_INFO_CHOSEN_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ���������Ĳ�������ṹ

*****************************************************************************/
enum    PHYITF_MAC_E_SCHED_GRANT_INFO_CHOSEN_ENUM
{
    PHYITF_MAC_E_NON_SCHED_GRANT_INFO_CHOSEN              = 0,       /* _H2ASN_MsgChoice PHYITF_MAC_E_NON_SCHED_GRANT_STRU */
    PHYITF_MAC_E_SCHED_GRANT_INFO_CHOSEN                  = 1,       /* _H2ASN_MsgChoice VOS_UINT32 */

    PHYITF_MAC_E_SCHED_GRANT_INFO_CHOSEN_BUTT
};

typedef VOS_UINT16 PHYITF_MAC_E_SCHED_GRANT_INFO_CHOSEN_ENUM_UINT16;

/*****************************************************************************
 ö����    : PHYITF_CHANNEL_CONFIG_RESULT_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : �ŵ����ý��ָʾ

*****************************************************************************/
enum    PHYITF_CHANNEL_CONFIG_RESULT_ENUM
{
    PHYITF_CHANNEL_CONFIG_SUCCESS               = 0,     /*�ŵ����óɹ������������������á��ͷ�*/
    PHYITF_CHANNEL_SETUP_OVERLAP_ERROR          = 1,     /*�ŵ����ظ�����*/
    PHYITF_CHANNEL_SETUP_STATE_ERROR            = 2,     /*�����ŵ��͵�ǰϵͳ״̬��һ��*/
    PHYITF_CHANNEL_MODIFY_WITHOUT_CHANNEL_ERROR = 3,     /*���ŵ�������ʱ�����ŵ�������*/
    PHYITF_CHANNEL_CONFIG_PARA_ERROR            = 4,     /*�ŵ���������*/
    PHYITF_CHANNEL_CONFIG_ERROR                 = 5,     /*�ŵ�����ʧ��*/

    PHYITF_CHANNEL_CONFIG_BUTT
};
typedef VOS_UINT16 PHYITF_CHANNEL_CONFIG_RESULT_ENUM_UINT16;

/*****************************************************************************
 ö����    : PHYITF_DPCH_COMPRESSED_MODE_STATUS_CHANGE_RESULT_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ѹ��ģʽ�ı���ָʾ
*****************************************************************************/
enum    PHYITF_DPCH_COMPRESSED_MODE_STATUS_CHANGE_RESULT_ENUM
{

    PHYITF_DPCH_COMPRESSED_MODE_STATUS_CHANGE_SUCC  = 0,  /*ѹģ״̬�ı�ɹ�*/
    PHYITF_DPCH_COMPRESSED_MODE_STATUS_CHANGE_ERROR = 1,  /*ѹģ״̬�ı�ʧ��*/

    PHYITF_DPCH_COMPRESSED_MODE_STATUS_CHANGE_BUTT

};
typedef VOS_UINT16 PHYITF_DPCH_COMPRESSED_MODE_STATUS_CHANGE_RESULT_ENUM_UINT16;



/*****************************************************************************
 ö����    : PHYITF_CAMPED_MAINCELL_RESULT_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ��С��פ�����

*****************************************************************************/
enum    PHYITF_CAMPED_MAINCELL_RESULT_ENUM
{
    PHYITF_CAMPED_MAINCELL_SUCCESS              = 0,     /*��С��פ���ɹ�*/
    PHYITF_CAMPED_MAINCELL_FAIL                 = 1,     /*��С��פ��ʧ��*/

    PHYITF_CAMPED_MAINCELL_BUTT

};
typedef VOS_UINT16 PHYITF_CAMPED_MAINCELL_RESULT_ENUM_UINT16;

/*****************************************************************************
 ö����    : PHYITF_CONNECT_MEAS_REQ_TYPE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ����״̬����������Ϣ����
*****************************************************************************/
enum PHYITF_CONNECT_MEAS_REQ_TYPE_ENUM
{
    PHYITF_CONNECT_MEAS_REQ_INTRA_CELL      = 41,                               /* _H2ASN_MsgChoice PHYITF_INTRA_FREQ_MEASURE_STRU */
    PHYITF_CONNECT_MEAS_REQ_INTER_CELL      = 42,                               /* _H2ASN_MsgChoice PHYITF_INTER_FREQ_MEASURE_STRU */
    PHYITF_CONNECT_MEAS_REQ_INTERNAL        = 43,                               /* _H2ASN_MsgChoice VOS_UINT16 */
    PHYITF_CONNECT_MEAS_REQ_CELLSEL         = 44,                               /* _H2ASN_MsgChoice PHYITF_CELL_SEL_MEASURE_STRU */
    PHYITF_CONNECT_MEAS_REQ_INTERRAT        = 45,
    PHYITF_CONNECT_MEAS_REQ_ADJACENTFREQ    = 46,                               /* _H2ASN_MsgChoice PHYITF_ADJACENT_FREQ_MEASURE_STRU */
    PHYITF_CONNECT_MEAS_REQ_INTER_RAT_LTE   = 47,                               /* _H2ASN_MsgChoice PHYITF_INTER_RAT_LTE_CELL_INFO_STRU */
    PHYITF_CONNECT_MEAS_REQ_TYPE_BUTT
};
typedef VOS_UINT16  PHYITF_CONNECT_MEAS_REQ_TYPE_ENUM_UINT16;

/*****************************************************************************
 ö����    : PHYITF_CONNECT_MEAS_IND_TYPE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ����״̬�����ϱ�����
*****************************************************************************/
enum PHYITF_CONNECT_MEAS_IND_TYPE_ENUM
{
    PHYITF_CONNECT_MEAS_IND_INTRA_CELL          = 51,           /* _H2ASN_MsgChoice PHYITF_INTRA_FREQ_REPORT_STRU */
    PHYITF_CONNECT_MEAS_IND_INTER_CELL          = 52,           /* _H2ASN_MsgChoice PHYITF_INTER_FREQ_REPORT_STRU */
    PHYITF_CONNECT_MEAS_IND_CELLSEL             = 54,           /* _H2ASN_MsgChoice PHYITF_CELL_SEL_REPORT_STRU   */
    PHYITF_CONNECT_MEAS_IND_TYPE_BUTT
};
typedef VOS_UINT16  PHYITF_CONNECT_MEAS_IND_TYPE_ENUM_UINT16;

/*****************************************************************************
 ö����    : PHYITF_MEASURE_COMMAND_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ������������
*****************************************************************************/
enum PHYITF_MEASURE_COMMAND_ENUM
{
    PHYITF_MEASURE_COMMAND_RELEASE          = 0,            /*�����ͷ�*/
    PHYITF_MEASURE_COMMAND_SETUP            = 1,            /*�������������䶼�ô�����,����2000*/
    PHYITF_MEASURE_COMMAND_MODIFY           = 2,            /*��������*/

    PHYITF_MEASURE_COMMAND_BUTT
};
typedef  VOS_UINT16 PHYITF_MEASURE_COMMAND_ENUM_UINT16;

/*****************************************************************************
 ö����    : PHYITF_MODIFY_TYPE_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : ������������
*****************************************************************************/
enum PHYITF_MODIFY_TYPE_ENUM
{
    PHYITF_MEASURE_MODIFY_ALL                   = 0,            /*���������ò����б�Ͳ�������*/
    PHYITF_MEASURE_MODIFY_ONLY_MEAS_PARA        = 1,            /*�������������*/

    PHYITF_MEASURE_MODIFY_BUTT
};
typedef  VOS_UINT16 PHYITF_MODIFY_TYPE_ENUM_UINT16;


/*****************************************************************************
 ö����    : PHYITF_64QAM_CONFIGURED_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : 64QAM����
*****************************************************************************/
enum PHYITF_64QAM_CONFIGURED_ENUM
{
    PHYITF_64QAM_CONFIGURED_NOT_PRESENT          = 0,            /* 64QAM������ */
    PHYITF_64QAM_CONFIGURED_PRESENT              = 1,            /* 64QAM���� */

    PHYITF_64QAM_CONFIGURED_BUTT
};
typedef VOS_UINT16 PHYITF_64QAM_CONFIGURED_ENUM_UINT16;

/*****************************************************************************
 ö����    : PHYITF_DL_SCND_CELL_INFO_CFG_INFO_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  :
*****************************************************************************/
enum  PHYITF_DL_SCND_CELL_INFO_CFG_INFO_ENUM
{
    PHYITF_DL_SCND_CELL_INFO_CFG_INFO_CONTINUE = 0,
    PHYITF_DL_SCND_CELL_INFO_CFG_INFO_NEW_CFG,
    PHYITF_DL_SCND_CELL_INFO_CFG_INFO_BUTT
};
typedef VOS_UINT16 PHYITF_DL_SCND_CELL_INFO_CFG_INFO_ENUM_UINT16;


/*****************************************************************************
 ö����    : PHYITF_MAC_RPT_MODE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ����BBP����mac ͷ��ģʽ
*****************************************************************************/
enum PHYITF_MAC_RPT_MODE_ENUM
{
    PHYITF_MAC_RPT_MODE_NO_MAC_HEADER          = 0,            /* BBP������macͷ */
    PHYITF_MAC_RPT_MODE_MAC_HS_HEADER          = 1,            /* BBP����mac hs����macͷ */
    PHYITF_MAC_RPT_MODE_MAC_EHS_HEADER         = 2,            /* BBP����mac Ehs����macͷ */
    PHYITF_MAC_RPT_MODE_BUTT
};
typedef VOS_UINT16 PHYITF_MAC_RPT_MODE_ENUM_UINT16;

/*****************************************************************************
 ö����    : PHYITF_MAC_RESET_TYPE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ����reset ͷ����
*****************************************************************************/
enum PHYITF_MAC_RESET_TYPE_ENUM
{
    PHYITF_MAC_HS_RESET                       = 0,            /* ָʾreset mac hsʵ�� */
    PHYITF_MAC_EHS_RESET                      = 1,            /* ָʾreset mac ehs ʵ��*/
    PHYITF_MAC_RESET_BUTT
};
typedef VOS_UINT16 PHYITF_MAC_RESET_TYPE_ENUM_UINT16;

/*****************************************************************************
 ö����    : PHYITF_MAC_E_I_RESET_TYPE_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : MAC_E/MAC_I reset
*****************************************************************************/
enum PHYITF_MAC_E_I_RESET_TYPE_ENUM
{
    PHYITF_MAC_E_RESET                      = 0,                /* ָʾreset mac hsʵ�� */
    PHYITF_MAC_I_RESET                      = 1,                /* ָʾreset mac ehs ʵ��*/
    PHYITF_MAC_E_I_RESET_BUTT
};
typedef VOS_UINT16 PHYITF_MAC_E_I_RESET_TYPE_ENUM_UINT16;


/*****************************************************************************
 ö����    : PHYITF_HSDSCH_TB_SIZE_TABLE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : TB SIZE TABLE ���뷽ʽ
*****************************************************************************/
enum PHYITF_HSDSCH_TB_SIZE_TABLE_ENUM
{
    PHYITF_HSDSCH_TB_SIZE_TABLE_BIT_ALIGNED     = 0,     /* ʹ��HS-DSCH TB SIZE TBLE BIT ALIGNED ��ʽ*/
    PHYITF_HSDSCH_TB_SIZE_TABLE_OCTET_ALIGNED   = 1,     /* ʹ��HS-DSCH TB SIZE TBLE OCTET ALIGNED ��ʽ*/

    PHYITF_HSDSCH_TB_SIZE_TABLE_BUTT
};
typedef VOS_UINT16 PHYITF_HSDSCH_TB_SIZE_TABLE_ENUM_UINT16;
/* V3 R7_7C1 End */


/*****************************************************************************
 ö����    : PHYITF_MIMO_OPER_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : MIMO������ʽ
*****************************************************************************/
enum  PHYITF_MIMO_OPER_ENUM
{
    PHYITF_MIMO_OPER_START                      = 0,                            /* ָʾMIMO��ʼ���� */
    PHYITF_MIMO_OPER_CONTINUE,                                                  /* ָʾMIMO������ǰ����  */
    PHYITF_MIMO_OPER_STOP,                                                      /* ָʾMIMOֹͣ */
    PHYITF_MIMO_OPER_BUTT
};
typedef VOS_UINT16 PHYITF_MIMO_OPER_ENUM_UINT16;

/*****************************************************************************
 ö����    : PHYITF_MIMO_N_M_RATIO_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : MIMO N/M RATIO
*****************************************************************************/
enum  PHYITF_MIMO_N_M_RATIO_ENUM
{
    PHYITF_MIMO_N_M_RATIO_MNM1_2 = 0,
    PHYITF_MIMO_N_M_RATIO_MNM2_3,
    PHYITF_MIMO_N_M_RATIO_MNM3_4,
    PHYITF_MIMO_N_M_RATIO_MNM4_5,
    PHYITF_MIMO_N_M_RATIO_MNM5_6,
    PHYITF_MIMO_N_M_RATIO_MNM6_7,
    PHYITF_MIMO_N_M_RATIO_MNM7_8,
    PHYITF_MIMO_N_M_RATIO_MNM8_9,
    PHYITF_MIMO_N_M_RATIO_MNM9_10,
    PHYITF_MIMO_N_M_RATIO_MNM1_1,
    PHYITF_MIMO_N_M_RATIO_BUTT
};
typedef VOS_UINT16 PHYITF_MIMO_N_M_RATIO_ENUM_UINT16;


/*****************************************************************************
 ö����    : PHYITF_MIMO_SCPICH_PATTERN_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : S-CPICH PATTERN
*****************************************************************************/
enum  PHYITF_MIMO_SCPICH_PATTERN_ENUM
{
    PHYITF_MIMO_NORMAL                          = 0,
    PHYITF_MIMO_DIVERSITY,
    PHYITF_MIMO_PATTERN_BUTT
};
typedef VOS_UINT16 PHYITF_MIMO_SCPICH_PATTERN_ENUM_UINT16;
/*****************************************************************************
 ö����    : PHYITF_PCPICH_USAGE_FOR_CH_EST_ENUM
 Э����  :
 ASN.1���� :   MinReduced-E-DPDCH-GainFactor
 ö��˵��  : E_DPDCH���ʻ�������
*****************************************************************************/
enum PHYITF_MIN_REDUC_E_DPDCH_GAIN_FACTOR_ENUM
{
    PHYITF_MIN_REDUC_E_DPDCH_GAIN_FACTOR_M815   = 0,
    PHYITF_MIN_REDUC_E_DPDCH_GAIN_FACTOR_M1115     ,
    PHYITF_MIN_REDUC_E_DPDCH_GAIN_FACTOR_M1515     ,
    PHYITF_MIN_REDUC_E_DPDCH_GAIN_FACTOR_M2115     ,
    PHYITF_MIN_REDUC_E_DPDCH_GAIN_FACTOR_M3015     ,
    PHYITF_MIN_REDUC_E_DPDCH_GAIN_FACTOR_M4215     ,
    PHYITF_MIN_REDUC_E_DPDCH_GAIN_FACTOR_M6015     ,
    PHYITF_MIN_REDUC_E_DPDCH_GAIN_FACTOR_M8415     ,
    PHYITF_MIN_REDUC_E_DPDCH_GAIN_FACTOR_BUTT
};
typedef VOS_UINT16 PHYITF_MIN_REDUC_E_DPDCH_GAIN_FACTOR_ENUM_UINT16;

/*****************************************************************************
 ö����    : PHYITF_DATA_TYPE_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  :
*****************************************************************************/
enum PHYITF_LOCH_DATA_TYPE_ENUM
{
    PHYITF_LOCH_DATA_TYPE_CCCH          = 0,
    PHYITF_LOCH_DATA_TYPE_SRB              ,
    PHYITF_LOCH_DATA_TYPE_CS               ,
    PHYITF_LOCH_DATA_TYPE_PS               ,
    PHYITF_LOCH_DATA_TYPE_BUTT
};
typedef VOS_UINT16 PHYITF_LOCH_DATA_TYPE_ENUM_UINT16;

/*****************************************************************************
 ö����    : PHYITF_RLC_PDU_SIZE_LI_SIZE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  :
*****************************************************************************/
enum PHYITF_RLC_PDU_SIZE_LI_SIZE_ENUM
{
    PHYITF_FLEX_RLC_PDU_SIZE_LI_SIZE_7_BIT  = 7,
    PHYITF_FLEX_RLC_PDU_SIZE_LI_SIZE_15_BIT = 15,
    PHYITF_FLEX_RLC_PDU_SIZE_LI_SIZE_BUTT
};
typedef VOS_UINT16 PHYITF_RLC_PDU_SIZE_LI_SIZE_ENUM_UINT16;


/*****************************************************************************
 ö����    : PHYITF_TSN_BIT_LEN_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  :
*****************************************************************************/
enum PHYITF_TSN_BIT_LEN_ENUM
{
    PHYITF_TSN_LEN_6_BIT        = 6,
    PHYITF_TSN_LEN_14_BIT       = 14,
    PHYITF_TSN_LEN_BUTT
};
typedef VOS_UINT16 PHYITF_TSN_BIT_LEN_ENUM_UINT16;

/*****************************************************************************
 ö����    : PHYITF_SYNC_NEED_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  :  ����dpch/fdpchʱ�Ƿ���Ҫͬ����ָʾ
*****************************************************************************/

enum PHYITF_SYNC_NEED_ENUM
{
    PHYITF_SYNC_NEED                      = 0,    /* ��Ҫͬ�� */
    PHYITF_SYNC_NO_NEED                   = 1,    /* ����ͬ�� */
    PHYITF_SYNC_UNKOWN                    = 2,    /* WAS�޷��ж��Ƿ�ͬ������DSP�ж� */
    PHYITF_SYNC_BUTT
};
typedef VOS_UINT16  PHYITF_SYNC_NEED_ENUM_UINT16;

/*****************************************************************************
 ö����    : PHYITF_UE_MOBILITY_STATE_ENUM16
 Э����  :
 ASN.1���� :
 ö��˵��  : UE�ƶ�״̬��ö��
*****************************************************************************/
enum PHYITF_HIGH_RATE_FLAG_ENUM
{
    PHYITF_HIGH_RATE_FLAG_FALSE   = 0,                                        /* UE���ڵ����ƶ�״̬ */
    PHYITF_HIGH_RATE_FLAG_TRUE    = 1,                                        /* UE���ڸ����ƶ�״̬ */
    PHYITF_HIGH_RATE_FLAG_BUTT
};
typedef VOS_UINT16 PHYITF_HIGH_RATE_FLAG_ENUM_UINT16;

/*****************************************************************************
 ö����    : PHYITF_RRC_STATUS_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : RRC״̬
*****************************************************************************/
enum PHYITF_RRC_STATUS_ENUM
{
    PHYITF_RRC_STATUS_IDLE          = 0,                                        /* IDLE̬ */
    PHYITF_RRC_STATUS_PCH           = 1,                                        /* PCH״̬ */
    PHYITF_RRC_STATUS_FACH          = 2,                                        /* FACH״̬ */
    PHYITF_RRC_STATUS_DCH           = 3,                                        /* DCH״̬ */

    PHYITF_RRC_STATUS_BUTT
};
typedef  VOS_UINT16 PHYITF_RRC_STATUS_ENUM_UINT16;

/*****************************************************************************
 ö����    : PHYITF_W_BG_SEARCH_OTHER_RAT_CMD_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : ��ʼ����ֹͣ������
*****************************************************************************/
enum  PHYITF_W_BG_SEARCH_OTHER_RAT_CMD_ENUM
{
    PHYITF_W_BG_SEARCH_OTHER_RAT_CMD_START                  = 0,
    PHYITF_W_BG_SEARCH_OTHER_RAT_CMD_STOP                      ,
    PHYITF_W_BG_SEARCH_OTHER_RAT_CMD_BUTT
};
typedef VOS_UINT16 PHYITF_W_BG_SEARCH_OTHER_RAT_CMD_ENUM_UINT16;

/*****************************************************************************
 ö����    : PHYITF_W_BG_SEARCH_RAT_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : ������L����G
*****************************************************************************/
enum  PHYITF_W_BG_SEARCH_RAT_ENUM
{
    PHYITF_W_BG_SEARCH_RAT_L                                 = 0,
    PHYITF_W_BG_SEARCH_RAT_G                                    ,
    PHYITF_W_BG_SEARCH_RAT_BUTT
};
typedef VOS_UINT16 PHYITF_W_BG_SEARCH_RAT_ENUM_UINT16;

/*****************************************************************************
  7 STRUCT����
*****************************************************************************/

/**********************************���нӿ���Ϣ�����ݽṹ****************************/
/*****************************************************************************
 �ṹ��    : RRC_PHY_MSG_HEAD_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RRC-PHY�Ĺ�����Ϣͷ,��WAS HPAʹ��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16    enMsgID;                  /*_H2ASN_Skip*/  /* ԭ������*/
    VOS_UINT16                    usOPID;                   /* ������ʶ */
}RRC_PHY_MSG_HEAD_STRU;

/*****************************************************************************
 �ṹ��    : RRC_PHY_UPLINK_MAXTXPWR_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ������й���������Ϣ�����ݽṹ, ����Ϣ����ҪCNF
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16    enMsgID;                  /*_H2ASN_Skip*/  /* ԭ������*/
    VOS_UINT16                    usOPID;                   /* ������ʶ */
    VOS_INT16                     sActiveTime;              /* ����ʱ�� */
    VOS_INT16                     sMaxTxPwr;                /* [-50��33],������·����书��= min(Maximum allowed UL TX Power=�������õ������, PMAX =UE������ʹ��),dbm */

}RRC_PHY_UPLINK_MAXTXPWR_REQ_STRU;


/*****************************************************************************
 �ṹ��    : PHY_RRC_UPLINK_MAXTXPWR_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ���й�������Cnf ID_PHY_RRC_UPLINK_MAXTXPWR_CNF
 *****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16                enMsgID;          /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                usOPID;           /* ������ʶ */
    PHYITF_CHANNEL_CONFIG_RESULT_ENUM_UINT16  enIndicator;      /* ���ý��,0����ɹ�����������ʧ��*/
    VOS_UINT16                                usReserve1;

}PHY_RRC_UPLINK_MAXTXPWR_CNF_STRU;

/*****************************************************************************
 �ṹ��    : PHY_RRC_UPLINK_MAXTXPWR_ACTIVATE_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ���й�������Active In ID_PHY_RRC_UPLINK_MAXTXPWR_ACTIVATE_IND
 *****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16                enMsgID;          /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                usOPID;           /* ������ʶ */
    VOS_UINT16                                usCFN;            /* ������Ч��CFN */
    PHYITF_CHANNEL_CONFIG_RESULT_ENUM_UINT16  enIndicator;      /* ���ý��,0����ɹ�����������ʧ��*/

}PHY_RRC_UPLINK_MAXTXPWR_ACTIVATE_IND_STRU;

/*****************************************************************************
 �ṹ��    : PHY_RRC_CAMPED_MAINCELL_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��С��פ��֤ʵ��Ϣ�����ݽṹ

*****************************************************************************/

typedef struct
{
    VOS_MSG_HEADER                                            /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16                enMsgID;        /*_H2ASN_Skip*/ /* ԭ������ */
    VOS_UINT16                                usOPID;         /* ������ʶ */

    PHYITF_CAMPED_MAINCELL_RESULT_ENUM_UINT16 enResult;       /*��С��פ�����*/
    VOS_UINT16                                usReserve1;

}PHY_RRC_CAMPED_MAINCELL_CNF_STRU;


/******************************�ŵ����ò���************************************/
/**********SCCPCH �ŵ�����******************/

/*****************************************************************************
 �ṹ��    : PHYITF_FACH_OCCASION_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CELL_FACH ״̬�½�����Ƶ����ϵͳ�Ĳ���ʱ��
*****************************************************************************/
typedef struct
{
    PHYITF_BOOL_ENUM_UINT16                     enValidIndicator;
    VOS_UINT16                                  usSameOrDifferent;      /* 0����ʾ���������û���������仯���������²�����ָʾ��ָ����ʱ�̽���Ƶ�����1����ʾδ�仯 */
    VOS_UINT16                                  usStartSFN;             /* [0��4095] FACHOccasion�������ƫ��ֵ */
    VOS_UINT16                                  usMREP;                 /* [2��4096] frame FACHOccasion���� */
    VOS_UINT16                                  usNTTI;                 /* Sccpch�����TTI����,{1,2,4,8}frame */
    PHYITF_FACH_OCCASION_MEAS_TYPE_ENUM_UINT16  enMeasTypeFlag;         /* ��Ƶ����GSM����ָʾ */
    VOS_UINT32                                  ulInterMeasPeriod;      /* CELL_FACH״̬����Ƶ���������ڣ���λms */
    VOS_UINT16                                  usInterRatMeasPeriod;   /* 480,CELL_FACH״̬��GSM���������ڣ���ֵΪ�̶�����480��λms�� */
    VOS_UINT16                                  usMinIntraCellNum;      /* CELL_FACH״̬��ͬƵ������С������С���� */

}PHYITF_FACH_OCCASION_STRU;


typedef struct
{
    VOS_UINT16                                  usMTTI;   /*����CTCH��FACH ʹ�õ�TTI֡��*/
    VOS_UINT16                                  usN;      /* CTCH ������S-CCPCH������*/
    VOS_UINT16                                  usK;      /* CBS ֡ƫ��*/
    VOS_UINT16                                  usP;      /* ������Ϣ������ */

} PHYITF_CTCH_OCCASION_STRU;

typedef struct
{

    VOS_UINT16                                  usSFN;  /*��ǰ�յ�������Ϣʱ��SFN*/
    VOS_UINT16                                  usMTTI; /*����CTCH��FACH ʹ�õ�TTI֡��*/

    VOS_UINT16                                  usDrxBSOffsetListLen;     /* CTCH BS offset�б���Ч���� */
    VOS_UINT16                                  ausDrxBSOffsetList[RRC_PHY_MAX_DRXBS_OFFSETLSTLEN]; /* CTCH BS offset�б� */

} PHYITF_CBS_DRX_STRU;


/*****************************************************************************
 �ṹ��    : PHYITF_SCCPCH_PARA_STRU
 Э����  : RRC��ʹ��RRC_PHY_RL_SETUP_REQԭ������SCCPCH��PICH�����ŵ�ʱ��
             Ҫ��֤������֮ǰ�Ѿ�����ǰ��SCCPCH��PICH�����ŵ��ͷŵ���
             ����ᷢ�����󡣻���ʹ��RRC_PHY_RL_MODIFY_REQԭ������޸ģ�
             Ҫ��֤ͬʱ�·�CCPCH��PICH�����ŵ�����������ᷢ������
 ASN.1���� :
 �ṹ˵��  : SCCPCH �ŵ�����
*****************************************************************************/
#if(RRC_PHY_CBS_SWITCH == FEATURE_OFF)

typedef struct
{
    PHYITF_PHYCH_TYPE_ENUM_UINT16        enPhyChannelType;     /* �����ŵ����� *//*_H2ASN_Skip*/
    /*  sActiveTime ����FACHӳ���SCCPCHΪCFN����ָ��CFN��ʼ���
        -1��ʾ�����������; ����PCHӳ���SCCPCH�ò�����Ч */
    VOS_INT16                            sActiveTime;          /* [-1, 255]����ʱ��    */
    VOS_UINT16                           usFreqInfo;           /* [0,16383]Ƶ����Ϣ    */
    VOS_UINT16                           usSlotFormat;         /* [0, 17]ʱ϶��ʽ��,ָʾSCCPCH�����ŵ��ĵ�ǰʹ�õ�ʱ϶��ʽ */
    VOS_UINT16                           usFrameTimingOffset;  /* [0, 149]�����CPICH�ŵ���֡ƫ��,��256 chipΪ��λ����Χ0~38144 chip */
    PHYITF_TX_DIVER_IND_ENUM_UINT16      enTDIndicator;
    VOS_UINT16                           usFreqBandNo;         /* Ƶ�κ�:1,2,3,4,5,6*/
    VOS_UINT16                           usTxRxFreqSeparation; /* �շ�Ƶ��*/
    VOS_UINT16                           usSecScramCode;       /* [0, 15]�ڶ�����0����ʾʹ��������; */
    VOS_UINT16                           usOvsfCodeNum;        /* [0, 511]��Ƶ���,OVSF��� */
    VOS_UINT16                           usReserve3;
    PHYITF_SCCPCH_DEMODULATE_ENUM_UINT16 enSccpchDemInd;       /* ���ָʾ */

    PHYITF_FACH_OCCASION_STRU            stFACHOccasionInfo;   /* FACH Occation:phase 2 */

}PHYITF_SCCPCH_PARA_STRU;

#else

typedef struct
{
    PHYITF_PHYCH_TYPE_ENUM_UINT16        enPhyChannelType;     /* �����ŵ����� *//*_H2ASN_Skip*/

    /*  sActiveTime ����FACHӳ���SCCPCHΪCFN����ָ��CFN��ʼ���
        -1��ʾ�����������; ����PCHӳ���SCCPCH�ò�����Ч */
    VOS_INT16                            sActiveTime;          /* [-1, 255]����ʱ��    */

    VOS_UINT16                           usFreqInfo;           /* [0,16383]Ƶ����Ϣ    */
    VOS_UINT16                           usSlotFormat;         /* [0, 17]ʱ϶��ʽ��,ָʾSCCPCH�����ŵ��ĵ�ǰʹ�õ�ʱ϶��ʽ */
    VOS_UINT16                           usFrameTimingOffset;  /* [0, 149]�����CPICH�ŵ���֡ƫ��,��256 chipΪ��λ����Χ0~38144 chip */
    PHYITF_TX_DIVER_IND_ENUM_UINT16      enTDIndicator;
    VOS_UINT16                           usFreqBandNo;         /* Ƶ�κ�:1,2,3,4,5,6*/
    VOS_UINT16                           usTxRxFreqSeparation; /* �շ�Ƶ��*/
    VOS_UINT16                           usSecScramCode;       /* [0, 15]�ڶ�����0����ʾʹ��������; */
    VOS_UINT16                           usOvsfCodeNum;        /* [0, 511]��Ƶ���,OVSF��� */
    VOS_UINT16                           usSccpchIndex;        /* [0,1]  ֧�ֶ���sccpchʱ����Ӧ�������� */
    PHYITF_SCCPCH_DEMODULATE_ENUM_UINT16 enSccpchDemInd;       /* ���ָʾ */

    PHYITF_FACH_OCCASION_STRU            stFACHOccasionInfo;   /* FACH Occation:phase 2 */
    PHYITF_BOOL_ENUM_UINT16              enSupportCtch;        /* �Ƿ�֧��cbs */
    VOS_UINT16                           usReserve1;

}PHYITF_SCCPCH_PARA_STRU;

#endif

/*****************************CBS���ò���***************************************/
/*****************************************************************************
 ö����    : PHYITF_CBS_ACTION_ENUM_UINT16
 Э����  : cbs����ͣ����
 ASN.1���� :
 ö��˵��  :
*****************************************************************************/
enum PHYITF_CBS_ACTION_ENUM
{
    PHYITF_CBS_START                = 0,
    PHYITF_CBS_STOP                 = 1,
    PHYITF_ACTION_BUTT
};
typedef VOS_UINT16 PHYITF_CBS_ACTION_ENUM_UINT16;

/*****************************************************************************
 ö����    : PHYITF_CBS_CFGTYPE_ENUM_UINT16
 Э����  : cbs����������
 ASN.1���� :
 ö��˵��  :
*****************************************************************************/
enum PHYITF_CBS_CFGTYPE_ENUM
{
     PHYITF_CBS_CFG_CTCH_OCCASION           = 0,          /* CBS�����ò���CTCH_OCCASION_STRU�е����� */  /* _H2ASN_MsgChoice PHYITF_CTCH_OCCASION_STRU */
     PHYITF_CBS_CFG_CBS_DRX                 = 1,          /* CBS�����ò���CBS_DRX_STRU�е����� */    /* _H2ASN_MsgChoice PHYITF_CBS_DRX_STRU */

     PHYITF_CFGTYPE_BUTT
};
typedef VOS_UINT16 PHYITF_CBS_CFGTYPE_ENUM_UINT16;


/*****************************************************************************
 �ṹ��    : RRC_PHY_CBS_CONFIG_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CBS��������
 *****************************************************************************/
typedef   struct
{
    VOS_MSG_HEADER /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;               /* ԭ������ */ /*_H2ASN_Skip */
    VOS_UINT16                          usOPID;                 /* ������ʶ */
    PHYITF_CBS_ACTION_ENUM_UINT16       enAction;               /* ��ʼ��ֹͣ����cbs */
    PHYITF_CBS_CFGTYPE_ENUM_UINT16      enCBSCfgTypeChoice;      /* _H2ASN_IeChoice_Export PHYITF_CBS_CFGTYPE_ENUM_UINT16 */
    union /*_H2ASN_Skip*/
    {     /*_H2ASN_Skip*/
        PHYITF_CTCH_OCCASION_STRU        stCtchOccationInfo;    /* _H2ASN_Skip */
        PHYITF_CBS_DRX_STRU              stCbsDrxInfo;
        /******************************************************************************************************
            _H2ASN_IeChoice_When        PHYITF_CBS_CFGTYPE_ENUM_UINT16
        ******************************************************************************************************/
    }u;  /* _H2ASN_Skip */
}RRC_PHY_CBS_CONFIG_REQ_STRU;

/*****************************************************************************
 �ṹ��    : PHY_RRC_CBS_CONFIG_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : cbs ������Ӧ
 *****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16                enMsgID;          /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                usOPID;           /* ������ʶ */
    PHYITF_CHANNEL_CONFIG_RESULT_ENUM_UINT16  enIndicator;      /* ���ý��,0����ɹ�����������ʧ��*/
    VOS_UINT16                                usReserve1;

}PHY_RRC_CBS_CONFIG_CNF_STRU;


/*****************************PICH �ŵ�����***************************************/
/*****************************************************************************
 �ṹ��    : PHYITF_PAGING_OCCATION_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : Ѱ��ʱ��
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usStartSFN;                             /*���������ʼʱ��*/
    VOS_UINT16                          usPeriodT;

}PHYITF_PAGING_OCCATION_STRU;

/*****************************************************************************
 �ṹ��    : PHYITF_PICH_STRU
 Э����  : RRC��ʹ��RRC_PHY_RL_SETUP_REQԭ������SCCPCH��PICH�����ŵ�ʱ��
             Ҫ��֤������֮ǰ�Ѿ�����ǰ��SCCPCH��PICH�����ŵ��ͷŵ���
             ����ᷢ�����󡣻���ʹ��RRC_PHY_RL_MODIFY_REQԭ������޸ģ�
             Ҫ��֤ͬʱ�·�CCPCH��PICH�����ŵ�����������ᷢ������
 ASN.1���� :
 �ṹ˵��  : PICH �ŵ�����
*****************************************************************************/
typedef  struct
{
    PHYITF_PHYCH_TYPE_ENUM_UINT16       enPhyChannelType;                       /* �����ŵ�����                             *//*_H2ASN_Skip*/
    VOS_UINT16                          usFreqInfo;                             /* Ƶ����Ϣ                                 */
    VOS_UINT16                          usOvsfCodeNum;                          /* OVSF���                                 */
    VOS_UINT16                          usPiNumber;                             /* һ֡�е�Pi����                           */
    VOS_INT16                           sPichPowerOffset;                       /* PICH����ƫ��                             */
    VOS_UINT16                          usPI;                                   /* Piλ�ò���                               */
    PHYITF_TX_DIVER_IND_ENUM_UINT16     enTDIndicator;
    VOS_UINT16                          usFreqBandNo;                           /* Ƶ�κ�:1,2,3,4,5,6*/
    VOS_UINT16                          usTxRxFreqSeparation;                   /* �շ�Ƶ��*/
    VOS_UINT16                          usReserve1;
    PHYITF_PAGING_OCCATION_STRU         stPaggingOccasion;

}PHYITF_PICH_STRU;


/*****************************AICH �ŵ�����***************************************/
/*****************************************************************************
 �ṹ��    : PHYITF_AICH_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : AICH �ŵ�����
*****************************************************************************/
typedef   struct
{
    PHYITF_PHYCH_TYPE_ENUM_UINT16       enPhyChannelType;                       /* �����ŵ�����                             *//*_H2ASN_Skip*/
    VOS_UINT16                          usFreqInfo;                             /* Ƶ����Ϣ                                 */
    VOS_UINT16                          usOvsfCodeNum;                          /* ��Ƶ���                                 */
    VOS_UINT16                          usAichTransmissionTiming;               /* AICH��ʱ����                             */
    VOS_INT16                           sAichPowerOffset;                       /* AICH����ƫ��                             */
    PHYITF_TX_DIVER_IND_ENUM_UINT16     enTDIndicator;
    VOS_UINT16                          usFreqBandNo;                          /* Ƶ�κ�:1,2,3,4,5,6*/
    VOS_UINT16                          usTxRxFreqSeparation;                   /* �շ�Ƶ��*/
}PHYITF_AICH_STRU;

/*****************************PRACH �ŵ�����***************************************/

/*****************************************************************************
 �ṹ��    : PHYITF_AVAIL_SIGNATURE_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PRACH SIGNATURE �ŵ�����
*****************************************************************************/
/* AVAILABLE_SIGNATURE_INFO�����ݽṹ */
typedef struct
{
    VOS_UINT16                          usSignaltureNum;                        /* ���õ�signature�� */
    VOS_UINT16                          usReserve1;
    VOS_INT16                           asAvailableSignature[RRC_PHY_MAX_SIGNATURE_NUM]; /* ÿһ������signature�ı�� */

}PHYITF_AVAIL_SIGNATURE_INFO_STRU;


/*****************************************************************************
 �ṹ��    : PHYITF_AVAIL_SUB_CHAN_NUM_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PRACH SUB CHANNEL �ŵ�����
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usSubChanNum;                           /* ����SubChan��Ŀ */
    VOS_UINT16                          usReserve1;
    VOS_INT16                           asAvailableSubChanNum[RRC_PHY_MAX_SUBCHANNEL_NUM];  /* �������SubChan �ı�� */

}PHYITF_AVAIL_SUB_CHAN_NUM_INFO_STRU;


/*****************************************************************************
 �ṹ��    : PHYITF_ASC_ITEM_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PRACH ÿ�� ACCESS SERVICE CLASS ����
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usAvailSignatureStartIdx;               /* ����Signature��ʼ������ */
    VOS_UINT16                          usAvailSignatureStopIdx;                /* ����Signature���������� */
    VOS_INT16                           sAvailableSubChanCnt;                   /* ��ʹ�õ�subchannel������ */
    VOS_UINT16                          usReserve1;
#if (INTERFACE_TYPE == INTERFACE_PS)
    VOS_UINT8                           aucAvailSubChanIdx[RRC_PHY_MAX_SUBCHANNEL_NUM]; /* Subchannel������ */
#elif (INTERFACE_TYPE == INTERFACE_DSP)
    VOS_UINT16                          ausAvailSubChanIdx[RRC_PHY_MAX_SUBCHANNEL_NUM/2]; /* _H2ASN_Skip Subchannel������ */
#endif
}PHYITF_ASC_ITEM_STRU;

/*****************************************************************************
 �ṹ��    : PHYITF_ASC_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PRACH ���ܵ� ACCESS SERVICE CLASS ����
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usAscNum;                               /* ����ASC��Ŀ  */
    VOS_UINT16                          usReserve1;
    PHYITF_ASC_ITEM_STRU                astAccessServiceClass[RRC_PHY_MAX_ASC_NUM];  /* ���������� */

}PHYITF_ASC_STRU;


/*****************************************************************************
 �ṹ��    : PHYITF_PRACH_PWR_CTRL_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PRACH �Ĺ��ʿ��Ʋ���
*****************************************************************************/
typedef struct
{
    VOS_INT16                           sPrachInitialTxPower;                   /* Preamble��ʼ���ʿ���,��λdBm */
    VOS_UINT16                          usPowerRampStep;                        /* ��������Preamble�Ĺ��ʲ�ֵ,��λdB */
    VOS_UINT16                          usPreambleRetryMax;                     /* һ��������̷���Preamble������������ */
    VOS_INT16                           sSCellRscp;

}PHYITF_PRACH_PWR_CTRL_STRU;

/*****************************************************************************
 �ṹ��    : PHYITF_PRACH_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PRACH ���ŵ�����
*****************************************************************************/
typedef  struct
{
    PHYITF_PHYCH_TYPE_ENUM_UINT16       enPhyChannelType;                       /* �����ŵ�����                    *//*_H2ASN_Skip*/
    VOS_UINT16                          usFreqInfo;                             /* Ƶ����Ϣ                        */
    VOS_UINT16                          usScramCodeNum;                         /* ������                        */
    VOS_UINT16                          usTTI;                                  /* PRACH�Ĵ���ʱ����
                                                                                   E-RACH��������ṹʱ�������û���ã��̶���д10ms */

    PHYITF_AVAIL_SIGNATURE_INFO_STRU    stAvailSignatureInfoEntity;             /* ��PRACH���õ�SIGNATURE���ݽṹ  */
    PHYITF_AVAIL_SUB_CHAN_NUM_INFO_STRU stAvailSubChanNumInfoEntity;            /* ��PRACH���õ�SUBCHANNEL���ݽṹ */
    PHYITF_ASC_STRU                     stAccessServiceClassSEntity;            /* ÿ��ASC��Դ��Ϣ                 */
    PHYITF_PRACH_PWR_CTRL_STRU          stPrachPwrCtrlEntity;                   /* PRACH���ʿ�����Ϣ               */
    VOS_UINT16                          usFreqBandNo;                          /* Ƶ�κ�:1,2,3,4,5,6*/
    VOS_UINT16                          usTxRxFreqSeparation;                   /* �շ�Ƶ��*/
}PHYITF_PRACH_STRU;


/*****************************���� DPCH �ŵ�����***************************************/

/*****************************************************************************
 �ṹ��    : PHYITF_DOWNLINKINFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : DOWNLINK ��Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                    usSecScramCode;                         /* �ڶ����룬���������ʹ��0��ʾ��Ч */
    VOS_INT16                                     sOvsfCodeNum;                           /* ��Ƶ��   */
    VOS_UINT16                                    usReserve1;
    PHYITF_SCRAMBLE_CODE_CHANGE_TYPE_ENUM_UINT16  enScrambCodeChange;                     /* ����ı��־ */

}PHYITF_DOWNLINKINFO_STRU;

/*****************************************************************************
 �ṹ��    : PHYITF_DL_MODE_COMPRESS_METHOD_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����ѹ������
*****************************************************************************/
typedef struct
{
    PHYITF_COMPRS_MODE_ENUM_UINT16      enDLMethod;
    VOS_UINT16                          usReserve1;

}PHYITF_DL_COMPRESS_METHOD_STRU;

/*****************************************************************************
 �ṹ��    : PHYITF_DL_MODE_COMPRESS_METHOD_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����ѹ������
*****************************************************************************/
typedef struct
{
    PHYITF_COMPRS_MODE_ENUM_UINT16      enULMethod;
    VOS_UINT16                          usReserve1;

}PHYITF_UL_COMPRESS_METHOD_STRU;

/*****************************************************************************
 �ṹ��    : PHYITF_DL_AND_UL_COMPRESS_METHOD_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ���к�����ѹ������
*****************************************************************************/
typedef struct
{
     PHYITF_COMPRS_MODE_ENUM_UINT16     enDLMethod;                             /* ����ѹ��ģʽ�ķ�ʽ */
     PHYITF_COMPRS_MODE_ENUM_UINT16     enULMethod;                             /* ����ѹ��ģʽ�ķ�ʽ */

}PHYITF_DL_AND_UL_COMPRESS_METHOD_STRU;

/*****************************************************************************
 ö����    : PHYITF_TGMP_ENUM
 Э����  :
 ASN.1���� : TGMP
 ö��˵��  : ѹ��ģʽ����Ŀ��
*****************************************************************************/
enum PHYITF_TGMP_ENUM
{
    PHYITF_TGMP_TDD_MEAS                   = 0,
    PHYITF_TGMP_FDD_MEAS                   = 1,
    PHYITF_TGMP_GSM_CARR_RSSI_MEAS         = 2,
    PHYITF_TGMP_GSM_INIT_BSIC_ID           = 3,
    PHYITF_TGMP_GSM_BSIC_RECNF             = 4,
    PHYITF_TGMP_MULTI_CARR                 = 5,
    PHYITF_TGMP_E_UTRA                     = 6,
    PHYITF_TGMP_BUTT
};
typedef VOS_UINT16 PHYITF_TGMP_ENUM_UINT16;

/*****************************************************************************
 �ṹ��    : PHYITF_COMPRESS_MODE_TGPS_CONFIGPARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : TGPS �����ò���
*****************************************************************************/
typedef struct
{
    VOS_INT16                           sTGPRC;                                 /* TGP�ĸ�������TGP SEQUENCE                                */
    VOS_UINT16                          usTGMP;                                 /* TGP����Ŀ��                              */
    VOS_UINT16                          usTGSN;                                 /* Transmission Gap ��ʼ���ͶϿ��Ĵ�������TGCFN*/
    VOS_UINT16                          usTGL1;                                 /* ��һ��Transmission Gap�ĳ��Ȱ���TGP�Ͽ�ʱ*/
    VOS_UINT16                          usTGL2;                                 /* �ڶ���Transmission Gap�ĳ��Ȱ���TGP PATTERN*/
    VOS_INT16                           sTGD;                                   /* Transmission gap distance                */
    VOS_UINT16                          usTGPL1;                                /* TGP1�ĳ���                               */
    VOS_UINT16                          usTGPL2;                                /* TGP2�ĳ���                               */
    VOS_UINT16                          usRPP;                                  /* TGP �����е�Recovery Period Power����ģʽ*/
    VOS_UINT16                          usITP;                                  /* ѹ��ģʽ�µ�Initial Transmit Power*/
    VOS_UINT16                          usDLFrameType;                          /* ʹ�õ�֡����                             */
    VOS_UINT16                          usDeltaSIR1;                            /* TGP ����������Delta in DL SIR1��Ŀ��ֵ*/
    VOS_UINT16                          usDeltaSIRafter1;                       /* TGP �������̺�Delta in DL SIR1��Ŀ��ֵ*/
    VOS_UINT16                          usDeltaSIR2;                            /* TGP ����������Delta in DL SIR2��Ŀ��ֵ*/
    VOS_UINT16                          usDeltaSIRafter2;                       /* TGP �������̺�Delta in DL SIR2��Ŀ��ֵ*/
    VOS_UINT16                          usNIdentifyabort;
    VOS_UINT16                          usTReconfirmabort;

    #define    PHYITF_COMPRESS_METHOD_UL_CHOSEN         0
    #define    PHYITF_COMPRESS_METHOD_DL_CHOSEN         1
    #define    PHYITF_COMPRESS_METHOD_UL_DL_CHOSEN      2

    VOS_UINT16                          usModeChoice;                           /* ѹ��ģʽ��ʹ��ѡ��                       */
    union
    {

        PHYITF_UL_COMPRESS_METHOD_STRU          stULMode;
        PHYITF_DL_COMPRESS_METHOD_STRU          stDLMode;
        PHYITF_DL_AND_UL_COMPRESS_METHOD_STRU   stDLAndULMode;

    } CompressMethod;
}PHYITF_COMPRESS_MODE_TGPS_CONFIGPARA_STRU;


/*****************************************************************************
 �ṹ��    : PHYITF_COMPRESS_MODE_TGPS_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ĳ�� TGPS ��Ϣ
 *****************************************************************************/
typedef struct
{
     VOS_UINT16                                 usTGPSI;                        /* TGPS��ʶ       */
     VOS_UINT16                                 usTGPSStausFlag;                /* TGPS״̬��־   */
     VOS_INT16                                  sTGCFN;                         /* TGCFN          */
     VOS_UINT16                                 usReserve1;
     PHYITF_COMPRESS_MODE_TGPS_CONFIGPARA_STRU  stTGPSConfigPara;

}PHYITF_COMPRESS_MODE_TGPS_INFO_STRU;


/*****************************************************************************
 �ṹ��    : PHYITF_COMPRESS_MODE_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ѹģ��Ϣ
 *****************************************************************************/
typedef struct
{
    VOS_UINT16                          usTGPSCnt;                              /* TGPS���� */
    VOS_UINT16                          usReserve1;
    PHYITF_COMPRESS_MODE_TGPS_INFO_STRU astTGPS[RRC_PHY_MAX_TGPS];

}PHYITF_COMPRESS_MODE_INFO_STRU;

/**********Second Cpich Info ����******************/

/*****************************************************************************
 �ṹ��    : PHYITF_SECOND_CPICH_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����Ƶ������Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT16   usSecondDlScramblCode;       /* 0��ʾ��Ч,�����������Ƶ������ͬ, ����ȡֵ(1..15)*/
    VOS_UINT16   usOvsfCodeNum;               /* INTEGER(0..255) */
}PHYITF_SECOND_CPICH_STRU;

/*****************************************************************************
 �ṹ��    : PHYITF_JUDGE_SYNC_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ͬʧ���о�����
*****************************************************************************/
typedef struct
{
    VOS_UINT16   usSyncDetect;              /* ͬ����ʼ��飬�Ƿ��ʱ����1֡��û��ͬ���ϣ��Ͳ��õ�T312��ʱ�� ��λframe */
    VOS_UINT16   usT312;                    /* ͬ���о���ʱ������λframe�� ��Χ100-1500 */
    VOS_UINT16   usN312;                    /* ͬ���о����� ��Χ1-1000 */
    VOS_UINT16   usT313;                    /* ʧ���о���ʱ���� ��λframe ��Χ100-1500 */
    VOS_UINT16   usN313;                    /* ʧ���о���������Χ1-200 */
    VOS_UINT16   usN315;                    /* ʧ����ָ�ͬ�������޼�������Χ1-1000 */
    VOS_UINT16   usDisableUlDcchTimer;      /* ������֡ʧ����֪ͨWAS������DCCH��Ϣ��ͬ�������ٴ�֪ͨ����λframe��Ŀǰ�̶�Ϊ4 */
    VOS_UINT16   usResumeUlDcchTimer;       /* ֹͣ���Ͳ��������������֡ͬ���󣬿�ʼ����DCCH��Ϣ����λframe��Ŀǰ�̶�Ϊ1 */
}PHYITF_JUDGE_SYNC_STRU;

/*****************************************************************************
 �ṹ��    : PHYITF_DOWNLINK_DPCH_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����ר�������ŵ�����
 *****************************************************************************/
typedef struct
{
    PHYITF_PHYCH_TYPE_ENUM_UINT16           enPhyChannelType;                   /* �����ŵ����� *//*_H2ASN_Skip*/
    VOS_INT16                               sActiveTime;                        /* ����ʱ�� */
    VOS_UINT16                              usFreqInfo;                         /* Ƶ����Ϣ */
    VOS_UINT16                              usSlotFormat;                       /* ʱ϶��ʽ */
    VOS_UINT16                              usDpchFrameOffset;                  /* ֡ƫ�� */
    PHYITF_TX_DIVER_IND_ENUM_UINT16         enTDIndicator;                      /* �ּ�ָʾ */
    VOS_UINT16                              usDpchChanNum;                      /* DPCH���� */
    VOS_UINT16                              usDownLinkScramCode;                /* ������·������� */
    PHYITF_DOWNLINKINFO_STRU                astDownLinkInfoEntity[RRC_PHY_MAX_DLDPCH_CHAN_NUM]; /* ����DPCH��Ϣ */
    PHYITF_DPC_MODE_TYPE_ENUM_UINT16        enDpcMode;                          /* ���й��ʿ���*/
    VOS_UINT16                              usTpcCombIndex;                     /* TPC������� */
    PHYITF_TIMING_INDIACTION_ENUM_UINT16    enTimingIndication;                 /* Ӳ�л���ʱָʾ */
    VOS_INT16                               sCfnSfnOffset;                      /* CFN-targetSFN frame offset */

    PHYITF_COMPRESS_MODE_INFO_STRU          stCompressMode;                     /* ѹ��ģʽ */
    VOS_UINT16                              usRsv1;

    /* �����3�����δ֪�����л�ʱ����no need��  ��d��d������ֵ���п��ܡ�
      Ӳ�л�ʱ����������unkown�� ��ͨ���䣬��no need��
      ���D2D��ʱά��ʱ,����Ҫͬ��A,������Ҫ */
    PHYITF_SYNC_NEED_ENUM_UINT16            enNeedSync;
    PHYITF_BOOL_ENUM_UINT16                 enPostVerification;                 /* ͬ���Ƿ��ȡpost verification���̣��������ͬ��,��ֵ������ */

    PHYITF_TX_DIVER_IND_ENUM_UINT16         enPcpichTDIndicator;                /*����Ƶ�ŵ��Ƿ�ʹ�÷��ּ�,0:��ʹ�÷ּ�,1:STTD�ּ�,0xFF:�޷���÷ּ���ʽ*/
    VOS_UINT16                              usBlindHhoFlag;                     /*ä�л���� ��1:ä�л�;0:��ä�л�*/

    VOS_UINT16                              usFreqBandNo;                       /* Ƶ�κ�:1,2,3,4,5,6*/
    VOS_UINT16                              usTxRxFreqSeparation;               /* �շ�Ƶ��*/

    PHYITF_BOOL_ENUM_UINT16                 enSecndCpichValidInd;               /*����Ƶ�Ƿ���Ч��־*/
    PHYITF_SECOND_CPICH_STRU                stSecondCpichInfo;                  /*����Ƶ��Ϣ*/
    VOS_UINT16                              usPO2;                              /* Ptpc - Pdpdch (dB),ȡֵ��Χ 0-24,Step:0.25,��Ϊʵ��ֵ*4,����������Ϊ0xFFFF*/
    VOS_UINT16                              usPO3;                              /* Ppilot - Pdpdch (dB),ȡֵ��Χ 0-24,Step:0.25,��Ϊʵ��ֵ*4*/

    PHYITF_JUDGE_SYNC_STRU                  stJudgeSync;                        /* ͬʧ���о����� */
}PHYITF_DOWNLINK_DPCH_PARA_STRU;

/*****************************���� FDPCH �ŵ�����***************************************/
/*****************************************************************************
 �ṹ��    : PHYITF_DOWNLINK_FDPCH_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ���в���ר���ŵ�����
 *****************************************************************************/
typedef struct
{
    PHYITF_PHYCH_TYPE_ENUM_UINT16           enPhyChannelType;                   /* �����ŵ����� *//*_H2ASN_Skip*/
    VOS_INT16                               sActiveTime;                        /* ����ʱ�� */
    VOS_UINT16                              usFreqInfo;                         /* Ƶ����Ϣ */
    VOS_UINT16                              usFdpchFrameOffset;                 /* ֡ƫ�� */
    VOS_UINT16                              usFdpchSlotFormat;                  /* ʱ϶��ʽ��INTEGER(0..9) */
    VOS_UINT16                              usBlindHhoFlag;                     /*ä�л��ı�־*/
    PHYITF_TX_DIVER_IND_ENUM_UINT16         enTDIndicator;                      /* �ּ�ָʾ */
    VOS_UINT16                              usDownLinkScramCode;                /* ������·������� */
    PHYITF_DPC_MODE_TYPE_ENUM_UINT16        enDpcMode;                          /* ���й��ʿ���*/
    VOS_UINT16                              usTpcCombIndex;                     /* TPC������� */
    PHYITF_TIMING_INDIACTION_ENUM_UINT16    enTimingIndication;                 /* Ӳ�л���ʱָʾ */
    VOS_INT16                               sCfnSfnOffset;                      /* CFN-targetSFN frame offset */
    VOS_UINT16                              usSecScramCode;                     /* �ڶ����룬���������ʹ��0��ʾ��Ч */
    VOS_UINT16                              usOvsfCodeNum;                      /* ��Ƶ��   */
    VOS_UINT16                              usTpcErrorRateTarget;               /*��Ϊԭֵ����Ϊ0.01, Ϊ�˱��־���Ŀǰ����ֵ��ԭʼֵ����100��*/
    VOS_INT16                               sInitialSirTarget;                  /*��ʼSirTarget�����⻷����*/
    VOS_INT16                               sDeltaSirTarget;                      /*DeltaSirTarget�����⻷����*/
    VOS_UINT16                              usUpStepSizeFactor ;
    VOS_UINT16                              usDownStepSizeFactor ;
    VOS_UINT16                              usFreqBandNo;                       /* Ƶ�κ�:1,2,3,4,5,6*/
    VOS_UINT16                              usTxRxFreqSeparation;               /* �շ�Ƶ��*/

    PHYITF_BOOL_ENUM_UINT16                 enSecndCpichValidInd;               /*����Ƶ��Чָʾ��ʶ,0:��Ч,����ЧҪʹ������Ƶ���ŵ�����,1:��Ч,Ҫʹ�ø���Ƶ�����ŵ�����*/
    PHYITF_SECOND_CPICH_STRU                stSecondCpichInfo;                  /*����Ƶ������Ϣ*/

    PHYITF_COMPRESS_MODE_INFO_STRU          stCompressMode;                     /* ѹ��ģʽ */

    VOS_UINT16                              usRsv1;

   /* �����3�����δ֪�����л�ʱ����no need��  ��d��d������ֵ���п��ܡ�
     Ӳ�л�ʱ����������unkown�� ��ͨ���䣬��no need��    */
    PHYITF_SYNC_NEED_ENUM_UINT16            enNeedSync;

    PHYITF_BOOL_ENUM_UINT16                 enPostVerification;                 /* ͬ���Ƿ��ȡpost verification���̣��������ͬ��,��ֵ������ */

    PHYITF_TX_DIVER_IND_ENUM_UINT16         enPcpichTDIndicator;                /*����Ƶ�ŵ��Ƿ�ʹ�÷��ּ�,0:��ʹ�÷ּ�,1:STTD�ּ�,0xFF:�޷���÷ּ���ʽ*/

    PHYITF_JUDGE_SYNC_STRU                  stJudgeSync;                        /* ͬʧ���о����� */

}PHYITF_DOWNLINK_FDPCH_PARA_STRU;



/*****************************���� DPCH �ŵ�����***************************************/

/*****************************************************************************
 �ṹ��    : PHYITF_UlDPCH_POWER_CONTROL_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����ר�������ʿ�����Ϣ
 *****************************************************************************/


typedef struct
{
    VOS_INT16                           sDpchInitialTxPower;                    /* ����dpch��ʼ���͹��ʣ�
                                                                                   E-RACHʱû�иò���, ��д0                */
    VOS_UINT16                          usPcPreamble;                           /* ������DPCCH��֡�� ,
                                                                                   E-RACHʱû�иò�������д0 */
    PHYITF_UL_DPCH_PWRCTRL_ALGO_UINT16  enPowerControlAlgorithm;                /* UE����TPC����ʹ�õ�ָ���㷨              */
    VOS_UINT16                          usTpcStepSize;
    VOS_INT16                           sUlDpcchPowerOffset;                    /* E-RACHʱû�иò�������д0 */
    VOS_UINT16                          usBlindHhoFlag;

}PHYITF_ULDPCH_POWER_CONTROL_STRU;

/*****************************************************************************
 �ṹ��    : PHYITF_UPLINK_DPCH_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����ר�������ŵ���Ϣ
 *****************************************************************************/
typedef struct
{
    PHYITF_PHYCH_TYPE_ENUM_UINT16        enPhyChannelType;                       /* �����ŵ����� *//*_H2ASN_Skip*/
    VOS_INT16                            sActivateTime;                          /* ����ʱ�� */
    VOS_UINT16                           usFreqInfo;                             /* Ƶ����Ϣ */
    PHYITF_SCRAMBL_CODE_TYPE_ENUM_UINT16 enScramCodeType;                        /* �������� */
    VOS_UINT32                           ulScramCodeNum;                         /* ������ */
    PHYITF_ULDPCH_POWER_CONTROL_STRU     stUlDpchPowerControl;
    VOS_UINT16                           usDpchNum;                              /* ����DPDCH������ */
    VOS_UINT16                           usSlotFormat;                           /* ����DPCCHʹ�õ�ʱ϶��ʽ */
    VOS_UINT16                           usFreqBandNo;                           /* Ƶ�κ�:1,2,3,4,5,6*/
    VOS_UINT16                           usTxRxFreqSeparation;                   /* �շ�Ƶ��*/
}PHYITF_UPLINK_DPCH_STRU;





/*==========================================================================
                              HSDPA �ŵ�����
============================================================================*/

/*****************************************************************************
 �ṹ��    : PHYITF_MEAS_FEEDBACK_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : HSDPA ����������Ϣ
 *****************************************************************************/
typedef struct
{
    VOS_INT16                           sMeasPwrOffset;     /* INTEGER(-12..26),����Ϊ0.5, ��ʵ��ֵΪ����ֵ��2*/
    VOS_UINT16                          usFeedbackCycle;    /* ��������,ȡֵ(0, 2, 4, 8, 10, 20, 40, 80, 160,16,32,64) ms*/
    VOS_UINT16                          usCqiRepetFactor;   /* INTEGER(1..4) */
    VOS_UINT16                          usDeltaCqi;         /* INTEGER(0..8) */

}PHYITF_MEAS_FEEDBACK_INFO_STRU;

/*****************************************************************************
 �ṹ��    : PHYITF_HS_DPCCH_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : HSDPCCH ��Ϣ
 *****************************************************************************/
typedef  struct
{
    VOS_UINT16                          usDeltaAck;                             /* INTEGER(0..8)  OPTIONAL
                                                                                   E-RACHʱ�������������д8 */

    VOS_UINT16                          usDeltaNack;                            /* INTEGER(0..8)  OPTIONAL
                                                                                  E-RACHʱ�������������д8 */

    VOS_UINT16                          usAckNackRepetFactor;                   /* Ack_Nack�ظ�����(1-4)
                                                                                  E-RACHʱ�������������д1 */

    VOS_UINT16                          usHarqPrbMode;                          /* Harq ǰ��ģʽѡ��,��usHarqPrbModeΪ1��Ч
                                                                                 E-RACHʱ��Я���ò�������д0 */

    VOS_UINT16                          usReserve1;

    /*����������Ϣ,��enMeasFeedBackInfoValidΪ1��Ч*/
    PHYITF_BOOL_ENUM_UINT16             enMeasFeedBackValid;                    /* ָʾ stMeasFeedBackInfo�Ƿ���Ч */
    PHYITF_MEAS_FEEDBACK_INFO_STRU      stMeasFeedBackInfo;

}PHYITF_HS_DPCCH_INFO_STRU;

/*****************************************************************************
 �ṹ��    : PHYITF_HARQ_EXPLI_MEMSIZE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : HARQ �ڴ���ʾ��С��Ϣ
 *****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulCnt;
    VOS_UINT32                          aulMHarqMemorySize[RRC_PHY_MAX_HSDPA_PROCESSES];  /*HARQ_MEMORY_SIZE ��С*/

}PHYITF_HARQ_EXPLI_MEMSIZE_STRU;

/*****************************************************************************
 �ṹ��    : PHYITF_HARQ_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : HARQ ��Ϣ
 *****************************************************************************/
typedef struct
{
    VOS_UINT16                          usNumOfProcesses;                       /* INTEGER(1..16),������ */
    VOS_UINT16                          usReserve1;
    PHYITF_HARQ_EXPLI_MEMSIZE_STRU      stMemoryPartition;                      /* ���̵��ڴ�����С*/

}PHYITF_HARQ_INFO_STRU;


/*****************************************************************************
 �ṹ��    : PHYITF_HS_SCCH_CODE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : HS_SCCH �ŵ�����Ϣ
 *****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulCnt;
    VOS_UINT16                          ausHsScchCodes[RRC_PHY_MAX_HSSCCH_NUM];  /* INTEGER(0..127) */

}PHYITF_HS_SCCH_CODE_STRU;

/*****************************************************************************
 �ṹ��    : PHYITF_HS_SCCH_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : HS_SCCH ��Ϣ
 *****************************************************************************/
typedef struct
{
    VOS_UINT16                          usReserve1;

    /* INTEGER(0..15)  OPTIONAL,�������.��usDlScramblCodeȡֵΪ0��ʾʹ��������,
        ����ʹ�ø����� */
    VOS_UINT16                          usDlScramblCode;

    PHYITF_HS_SCCH_CODE_STRU            stHsScchCodeInfo;   /*HS_SCCH ʹ�õ��ŵ�����Ϣ*/

}PHYITF_HS_SCCH_INFO_STRU;

/*****************************************************************************
 �ṹ��    : PHYITF_HS_PDSCH_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : HS_PDSCH ��Ϣ
 *****************************************************************************/
typedef struct
{
    PHYITF_HS_SCCH_INFO_STRU            stHsScchInfo;    /* HsScchInfo,ȡ��Downlink HS-PDSCH Information*/

}PHYITF_HS_PDSCH_INFO_STRU;


/*****************************************************************************
 �ṹ��    : PHYITF_MAC_D_PDU_SIZE_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : HSDPA MAC_D PDU SIZE ��Ϣ�ṹ
 *****************************************************************************/
typedef struct
{
    /* Mac_D Pdu ����, INTEGER(0..7) */
    VOS_UINT16                             usMacDPduIndex;

    /* Mac_D Pdu Size�Ĵ�С,INTEGER(1..5000) */
    VOS_UINT16                             usMacDPduSize;

} PHYITF_MAC_D_PDU_SIZE_INFO_STRU;

/*****************************************************************************
 �ṹ��    : PHYITF_MAC_HS_QUEUE_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : HSDPA MAC_HS QUEUE ��Ϣ�ṹ
 *****************************************************************************/
typedef struct
{

    /*MacHs �Ķ���ID,INTEGER(0..7)*/
    VOS_UINT16                             usMacHsQueueId;

    /*�ö��е� Mac_D Pdu Size ����Ŀ,INTEGE(1..8)*/
    VOS_UINT16                             usMacDPduSizeCnt;

    /*Mac_D Pdu Size �б�,�洢��ÿ��MacDPdu size�Ĵ�С������*/
    PHYITF_MAC_D_PDU_SIZE_INFO_STRU        astMacDPduSizeInfoList[RRC_PHY_MAX_MAC_D_PDU_SIZES_NUM];

} PHYITF_MAC_HS_QUEUE_INFO_STRU;

/*****************************************************************************
 �ṹ��    : PHYITF_MAC_HS_CFG_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : HSDPA MAC_HS ������Ϣ�ṹ
 *****************************************************************************/
typedef struct
{

    /*MacHs PDU�ϱ���ģʽ,0ֱ���ϱ�,1:��MAC ͷ���������ϱ�,Ŀǰ�̶���Ϊ1*/
    PHYITF_MAC_RPT_MODE_ENUM_UINT16        enMacHsReportMode;

    /*ÿ�������Ƿ����C/T���־, bit0~bit7�ֱ��Ӧqueue0~queue7,����λ����
      BitλΪ1��ʾ����C/T��, BitΪ0��ʾ������C/T��*/
    VOS_UINT16                             usMacHsQueueCTFlag;

    VOS_UINT16                             usReserve1;

    /*Mac_Hs ������Ŀ,INTEGE(1..8)*/
    VOS_UINT16                             usMacHsQueueCnt;

    /*Mac_Hs ������Ϣ�б�*/
    PHYITF_MAC_HS_QUEUE_INFO_STRU          astMacHsQueueInfoList[RRC_PHY_MAX_QUEUE_NUM];

} PHYITF_MAC_HS_CFG_INFO_STRU;

/*V3 R7_7C1 Start */
typedef struct
{
    VOS_UINT16                             usMacHsQueueId;                  /* ����ID */
    VOS_UINT16                             usLochID;                        /* �߼��ŵ�ID */

} PHYITF_MAC_EHS_QUEUE_INFO_STRU;

typedef struct
{
    VOS_UINT16                              usMacEHsLochCnt;                    /* �߼��ŵ����� */
    /*MacHs PDU�ϱ���ģʽ,0ֱ���ϱ�,1:��MAC ͷ��������mac hs���ϱ�,
     2 ��macͷ��������mac ehs���ϱ� */
    PHYITF_MAC_RPT_MODE_ENUM_UINT16         enMacHsReportMode;
    PHYITF_MAC_EHS_QUEUE_INFO_STRU          astMacEHsQueueInfoList[RRC_PHY_MAX_LOCH_NUM]; /* �����߼��ŵ��Ͷ���ӳ���ϵ */

} PHYITF_MAC_EHS_CFG_INFO_STRU;
/* V3 R7_7C1 End */

/*****************************************************************************
 �ṹ��    : PHYITF_HSDPA_PHY_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : HSDPA ���ýṹ
 *****************************************************************************/
typedef   struct
{

    PHYITF_PHYCH_TYPE_ENUM_UINT16       enPhyChannelType; /*32*/                /* _H2ASN_Skip */
    VOS_INT16                           sActiveTime;                 /*�����ʱ��CFN,-1��ʾ��������*/
    VOS_UINT16                          usServHsPdschPrimScramCode;  /*HsPdsch����С���ĵ�Ƶ������,ȡ��Downlink information for each radio link,1���û�ֻ��1��*/
    VOS_UINT16                          usNewHRnti;                  /*�µ�HRnti,�� BitNewHRnti ��λʱ��Ч*/
/*V3 R7_7C1 Start */
    VOS_UINT16                          usHSDSCHPhyCategory;
    VOS_UINT16                          ausReserve1;
/* V3 R7_7C1 End */

    PHYITF_HS_PDSCH_INFO_STRU           stHsPdschInfo;               /*HsPdsch ��Ϣ,��BitHsPdschInfo��λʱ��Ч*/
    PHYITF_HS_DPCCH_INFO_STRU           stHsDpcchInfo;               /*HsDpcch ��Ϣ,��BitHsDpcchInfo��λʱ��Ч*/
    PHYITF_HARQ_INFO_STRU               stHarqInfo;                  /*HARQ ��Ϣ,��BitHarqInfo��λʱ��Ч*/

    PHYITF_MAC_HS_CFG_INFO_STRU         stMacHsCfgInfo;              /*MacHs��������Ϣ,����BBP����MACͷ*/

}PHYITF_HSDPA_PHY_STRU;

/*****************************************************************************
 �ṹ��    : PHYITF_MIMO_SCPICH_DIVERSITY_PAT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : s-cpich�ŵ�mimo����
 *****************************************************************************/
typedef struct
{
    VOS_UINT16                          usChanneCode;                           /* INTEGER(0..255) */
    VOS_INT16                           sSCpichPOMimo;                          /* INTEGER(-6..0), ���粻��ʱ������0ֵ */
}PHYITF_MIMO_SCPICH_DIVERSITY_PAT_STRU;

/*****************************************************************************
 �ṹ��    : PHYITF_MIMO_PILOT_CFG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MIMO PILOT CFG
 *****************************************************************************/
typedef struct
{
    VOS_UINT16                              ausReserve[1];                      /* ���ֽڶ��룬���� */
    PHYITF_MIMO_SCPICH_PATTERN_ENUM_UINT16  enSCpichPat;
    PHYITF_MIMO_SCPICH_DIVERSITY_PAT_STRU   stSCpichDiversityPat;
}PHYITF_MIMO_PILOT_CFG_STRU;

/*****************************************************************************
 �ṹ��    : PHYITF_MIMO_PARAMS_STRU
 Э����  : 10.3.6.41a MIMO parameters
 ASN.1���� :
 �ṹ˵��  : MIMO PARAMS
 *****************************************************************************/
typedef struct
{
    PHYITF_MIMO_OPER_ENUM_UINT16            enMimoOper;                         /* MIMO ����ģʽ */

    PHYITF_MIMO_N_M_RATIO_ENUM_UINT16       enMimoNMRatio;                      /* MIMO N_cqi_typeA/M_cqi ratio */
    PHYITF_MIMO_PILOT_CFG_STRU              stMimoPilotCfg;                     /* MIMO pilot configuration */

    PHYITF_BOOL_ENUM_UINT16                 enPrecodingWeightSetRestric;        /* ����Я��ʱ����Ϊtrue����������false */

    PHYITF_BOOL_ENUM_UINT16                 enSingleStreamStrict;               /* �Ƿ����Ƶ����� */
}PHYITF_MIMO_PARAMS_STRU;
/*****************************************************************************
 �ṹ��    : PHYITF_HSDPAPLUS_PHY_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : HSDPA+ ���ýṹ
 *****************************************************************************/
typedef  struct
{

    PHYITF_PHYCH_TYPE_ENUM_UINT16               enPhyChannelType;               /*512*/       /* _H2ASN_Skip */
    VOS_INT16                                   sActiveTime;                    /*�����ʱ��CFN,-1��ʾ��������*/
    VOS_UINT16                                  usServHsPdschPrimScramCode;     /*HsPdsch����С���ĵ�Ƶ������,ȡ��Downlink information for each radio link,1���û�ֻ��1��*/
    VOS_UINT16                                  usNewHRnti;                     /*�µ�HRnti,�� BitNewHRnti ��λʱ��Ч*/

    PHYITF_HS_PDSCH_INFO_STRU                   stHsPdschInfo;                  /*HsPdsch ��Ϣ,��BitHsPdschInfo��λʱ��Ч*/
    PHYITF_HS_DPCCH_INFO_STRU                   stHsDpcchInfo;                  /*HsDpcch ��Ϣ,��BitHsDpcchInfo��λʱ��Ч*/
    PHYITF_HARQ_INFO_STRU                       stHarqInfo;                     /*HARQ ��Ϣ,��BitHarqInfo��λʱ��Ч*/

    PHYITF_MAC_EHS_CFG_INFO_STRU                stMacEHsCfgInfo;

    PHYITF_64QAM_CONFIGURED_ENUM_UINT16         en64QAMConfig;                  /* HS DSCH�ŵ��Ƿ�ʹ��64QAM */
    PHYITF_HSDSCH_TB_SIZE_TABLE_ENUM_UINT16     enHsDschTbSizeTable;            /* HsDsch TB table ʹ��ģʽ*/

    VOS_UINT16                                  usTsnBitNum;                    /* dc+mimo ʱ����14, ��������6 */

    PHYITF_BOOL_ENUM_UINT16                     enMimoParamsValid;              /* ָʾMIMO PARAMS�Ƿ���Ч */

    PHYITF_MIMO_PARAMS_STRU                     stMimoParams;
}PHYITF_HSDPAPLUS_PHY_STRU;

/* V5R1 E_CELLFACH Start */
/*****************************************************************************
 �ṹ��    : PHYITF_HS_PDSCH_INFO_PCH_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CELL_PCH/URA_PCH��HS_PDSCH ��Ϣ������E_CELLFACH��������
 *****************************************************************************/
typedef struct
{
    VOS_UINT16                          usDlScramblCode;                        /* INTEGER(0..15)  OPTIONAL,�������.��usDlScramblCodeȡֵΪ0��ʾʹ��������,����ʹ�ø����� */

    VOS_UINT16                          usHspdschChlCode;                       /* HS-PDSCH Channelisation Code,Integer (0..15) */

    VOS_UINT16                          usNumOfPcchTrans;                       /* Number of PCCH transmissions,Integer (1..5) */

    VOS_UINT16                          usTBSizeCnt;
    VOS_UINT16                          ausTBSizeIndex[RRC_PHY_MAX_TB_SIZE_NUM];

}PHYITF_HS_PDSCH_INFO_PCH_STRU;


/*******************************************************************************
 �ṹ��    : PHYITF_E_CELLFACH_MEAS_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : E_CELLFACH ״̬�½�����Ƶ����ϵͳ�Ĳ���ʱ��
 25.133 8.4.2.3.2 Measurements in CELL_FACH State when HS-DSCH discontinuous reception is ongoing
*******************************************************************************/
typedef struct
{
    VOS_UINT16                                  usStartSFN;                     /* [0��4095] FACHOccasion�������ƫ��ֵ��Э��8.5.11 */
    VOS_UINT16                                  usMREP;                         /* [2��4096] frame FACHOccasion���� */
    PHYITF_FACH_OCCASION_MEAS_TYPE_ENUM_UINT16  enMeasTypeFlag;                 /* ��Ƶ����GSM����ָʾ */
    VOS_UINT16                                  usInterRatMeasPeriod;           /* 480,CELL_FACH״̬��GSM���������ڣ���ֵΪ�̶�����480��λms�� */
    VOS_UINT32                                  ulInterMeasPeriod;              /* CELL_FACH״̬����Ƶ���������ڣ���λms */
}PHYITF_E_CELLFACH_MEAS_PARA_STRU;


/*****************************************************************************
 �ṹ��    : PHYITF_E_CELLFACH_DRX_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usT321;                                 /*100ms,200,400,800*/
    VOS_UINT16                          usHsDschDrxCycFach;                     /* Determines the length of the DRX Cycle during DRX operation, in frames (4, 8, 16, 32)*/
    VOS_UINT16                          usHsDschDrxBurstFach;                   /* in frames:1, 2, 4, 8, 16 */

    /* TRUE means that the DRX operation can be interrupted by HS-DSCH data.
    FALSE means that the DRX operation cannot be interrupted by HS-DSCH data */
    PHYITF_BOOL_ENUM_UINT16             enDrxIntrrptHsDsch;

}PHYITF_E_CELLFACH_DRX_INFO_STRU;


/*****************************************************************************
 �ṹ��    : PHYITF_FACH_HSDPAPLUS_PHY_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : E_CELLFACH ����HSDPA+ ���ýṹ
 *****************************************************************************/
typedef  struct
{
    PHYITF_PHYCH_TYPE_ENUM_UINT16                   enPhyChannelType;           /* 513 */       /* _H2ASN_Skip */
    VOS_INT16                                       sActiveTime;                /* �����ʱ��CFN,-1��ʾ�������� */
    VOS_UINT16                                      usServHsPdschPrimScramCode; /* HsPdsch����С���ĵ�Ƶ������,ȡ��Downlink information for each radio link,1���û�ֻ��1�� */

    PHYITF_BOOL_ENUM_UINT16                         enHRntiValid;               /* ָʾusHRnti�Ƿ���Ч,��enHRntiValid =PHYITF_VALIDʱ,usHRnti��Ч,��enHRntiValid = PHYITF_INVALIDʱ����ʾä��� */
    VOS_UINT16                                      usHRnti;                    /* HRnti,��HS_DSCH_RECEPTION_OF_CCCH_ENABLED ΪTRUE,ѡ��Common HRNTI����WDSP */
    VOS_UINT16                                      usBcchSpecHRnti;            /* BCCH specific H-RNTI,��HRNTI������ʱ,usBcchSpecHRnti����㲻��ȡ */
    VOS_UINT16                                      usReserve1;
    VOS_UINT16                                      usBitHsPdschInfoForPch;     /* 1:��ʾ��ǰ��PCH,HSDSCH paging system��0:����PCH�򲻴��� */
    PHYITF_HS_PDSCH_INFO_PCH_STRU                   stHsPdschInfoForPch;        /* HSPDSCH��Ϣ��ȡ��SIB5��HS-DSCH paging system information,E_CELLFACH���� ;
                                                                                   ��usBitHsPdschInfoForPch Ϊ1ʱ��WAS����д�ýṹ��
                                                                                   HRNTI��Чʱ������㲻ʹ�øò����� HRNTI��Ч����£������ʹ�øò���*/
    PHYITF_HS_SCCH_INFO_STRU                        stHsScchInfo;               /* WAS����д�ýṹ����H_RNTIʱ�������HsScchInfo��ʹ��*/
    PHYITF_HARQ_INFO_STRU                           stHarqInfo;                 /* HARQ ��Ϣ,��BitHarqInfo��λʱ��Ч */
    PHYITF_MAC_EHS_CFG_INFO_STRU                    stMacEHsCfgInfo;

    PHYITF_HSDSCH_TB_SIZE_TABLE_ENUM_UINT16         enHsDschTbSizeTable;        /* E_CELLFACH�¶������� octet aligned */

    PHYITF_E_CELLFACH_MEAS_PERIOD_TYPE_ENUM_UINT16  enECellFachMeasPeriodType;  /*
                                                                                0��֧��CELL_FACH��DRX���ã���ȡ���������ṹ�Ĳ�����
                                                                                1����֧��CELL_FACH��DRX����FACH occation��Ч����ȡ����������
                                                                                2����֧��CELL_FACH��DRX����FACH occation��Ч���޷���Ƶ��ϵͳ���в���
                                                                                */
    PHYITF_E_CELLFACH_MEAS_PARA_STRU                stECellFachMeasPara;        /* E_CELLFACH�²������� */
    PHYITF_E_CELLFACH_DRX_INFO_STRU                 stECellFachDrxInfo;         /* E_CELLFACH DXR���� */
}PHYITF_FACH_HSDPAPLUS_PHY_STRU;
/* V5 E_CELLFACH End */



/*****************************************************************************
 �ṹ��    : RRC_PHY_RL_SETUP_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �ŵ�����������Ϣ�����ݽṹ
             ������Ҫ�������ŵ�
             ʹ�ø�ԭ����ŵ�Ϊ:


             PHYITF_SCCPCH_PARA_STRU
             PHYITF_PICH_STRU
             PHYITF_AICH_STRU
             PHYITF_PRACH_STRU
             PHYITF_DOWNLINK_DPCH_PARA_STRU
             PHYITF_UPLINK_DPCH_STRU
             PHYITF_HSDPA_PHY_STRU
             PHYITF_HSUPA_PHY_STRU
             PHYITF_HSDPAPLUS_PHY_STRU
             PHYITF_PHY_FACH_HSDPAPLUS
             PHYITF_E_RACH_REQ_STRU
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                          usOPID;                 /* ������ʶ */
    VOS_UINT16                          usPhyChannelNum;        /* �����ŵ��� *//* _H2ASN_IE_DYNAMIC_ARRAY_EXPORT STRUTYPE:VOS_UINT16 EXPORTNAME:usH2ASNPhyChannelNum */
    VOS_UINT16                          usParaSize;             /* �������� */
#if (INTERFACE_TYPE == INTERFACE_PS)
    VOS_UINT8                           aucPhyChannelPara[4];   /* �����ŵ����ò��� */
    /******************************************************************************************************
        _H2ASN_IE_DYNAMIC_ARRAY_COMMENT STRUTYPE:PHYITF_RL_PARA_STRU MINIDX:1 MAXIDX:8 EXPORTNAME:usH2ASNPhyChannelNum
    ******************************************************************************************************/
#elif (INTERFACE_TYPE == INTERFACE_DSP)
    VOS_UINT16                          ausPhyChannelPara[4/2];   /* _H2ASN_Skip  �����ŵ����ò��� */
#endif

}RRC_PHY_RL_SETUP_REQ_STRU;


/*****************************************************************************
 �ṹ��    : RRC_PHY_RL_MODIFY_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �ŵ�������������Ϣ�����ݽṹ
             ������Ҫ�����õ��ŵ�
             ʹ�ø�ԭ����ŵ�Ϊ:


             PHYITF_SCCPCH_PARA_STRU
             PHYITF_PICH_STRU
             PHYITF_AICH_STRU
             PHYITF_PRACH_STRU
             PHYITF_DOWNLINK_DPCH_PARA_STRU
             PHYITF_UPLINK_DPCH_STRU
             PHYITF_HSDPA_PHY_STRU
             PHYITF_HSUPA_PHY_STRU
             PHYITF_HSDPAPLUS_PHY_STRU
             PHYITF_PHY_FACH_HSDPAPLUS
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                          usOPID;                 /* ������ʶ */
    VOS_UINT16                          usPhyChannelNum;        /* �����ŵ��� *//* _H2ASN_IE_DYNAMIC_ARRAY_EXPORT STRUTYPE:VOS_UINT16 EXPORTNAME:usH2ASNPhyChannelNum */
    VOS_UINT16                          usParaSize;             /* �����ŵ��������� */
#if (INTERFACE_TYPE == INTERFACE_PS)
    VOS_UINT8                           aucPhyChannelPara[4];   /* �����ŵ����� */
    /******************************************************************************************************
        _H2ASN_IE_DYNAMIC_ARRAY_COMMENT STRUTYPE:PHYITF_RL_PARA_STRU MINIDX:1 MAXIDX:8 EXPORTNAME:usH2ASNPhyChannelNum
    ******************************************************************************************************/
#elif (INTERFACE_TYPE == INTERFACE_DSP)
    VOS_UINT16                          ausPhyChannelPara[4/2];   /* _H2ASN_Skip �����ŵ����� */
#endif

}RRC_PHY_RL_MODIFY_REQ_STRU;


/*****************************************************************************
 �ṹ��    : PHYITF_PHY_AFFECTED_RL_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PHYITF_PHY_REL_HSUPA_INFO_STRU ��ÿһ���ͷ��ŵ���·�Ľṹ
 *****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulAffectedRlScramCode;/*�ܵ��ͷ�Ӱ���RL(С��)������*/
    PHYITF_BOOL_ENUM_UINT16             enRelEAGCHValid;      /*ָʾ�Ƿ��ͷ����RL(С��)��E_AGCH�ŵ�*/
    PHYITF_BOOL_ENUM_UINT16             enRelEHICHValid;      /*ָʾ�Ƿ��ͷ����RL(С��)��E_HICH�ŵ�*/
    PHYITF_BOOL_ENUM_UINT16             enRelERGCHValid;      /*ָʾ�Ƿ��ͷ����RL(С��)��E_RGCH�ŵ�*/
    VOS_UINT16                          usReserve1;

}PHYITF_PHY_AFFECTED_RL_INFO_STRU;

/*****************************************************************************
 �ṹ��    : PHYITF_PHY_REL_HSUPA_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PHYITF_PHY_REL_CHANNEL_INFO_STRU ��ʹ�õ�Ҫ�ͷ�HSUPA�����ŵ��ṹ
 *****************************************************************************/
typedef struct
{
    PHYITF_BOOL_ENUM_UINT16             enRelAllValid;       /*ָʾ�Ƿ��ͷ����е�Hsupa�����ŵ�*/
    VOS_UINT16                          usRelAffectedRlNum;  /*�ͷ�Ӱ���Rl(С��)��Ŀ*/

    /*Ҫ�ͷŵ�ÿ��Rl(С��)�е��ŵ���Ϣ*/
    PHYITF_PHY_AFFECTED_RL_INFO_STRU    astRelAffectedRlInfo[RRC_PHY_MAX_RL_NUM];

}PHYITF_PHY_REL_HSUPA_INFO_STRU;

/*****************************************************************************
 �ṹ��    : PHYITF_PHY_REL_CHANNEL_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : 6720 �ͷ������ŵ��ṹ
 *****************************************************************************/

typedef struct
{
    PHYITF_PHYCH_TYPE_ENUM_UINT16       enPhyChannelType;       /* �����ŵ����� */
    VOS_INT16                           sActiveTime;            /* ����ʱ�� */
#if FEATURE_WCBS == FEATURE_ON
    VOS_UINT16                          usPhyChIndex;           /* �����ŵ����������ֻ��һ�����̶���0 */
    VOS_UINT16                          usReserv1;
#endif
    VOS_UINT16                          usFreqInfo;             /* Ƶ����Ϣ */
    VOS_INT16                           sSecondScramCode;       /* �ڶ�����,�������������ŵ���Ч,���Ҫ�ͷ�Hsupa����Ч*/
    VOS_UINT32                          ulScramCode;            /* ����,���Ҫ�ͷ�Hsupa����Ч */

    /*  enPhyChannelType == PHYITF_PHY_UL_HSUPA ����
        PHYITF_PHY_DL_HSUPA
        stRelHsupaExtInfo ��Ч��������Ч. */
    PHYITF_PHY_REL_HSUPA_INFO_STRU      stRelHsupaInfo;         /* ��չ��Ҫ�ͷŵ�Hsupa��Ϣ*/

}PHYITF_PHY_REL_CHANNEL_INFO_STRU;


/*****************************************************************************
 �ṹ��    : RRC_PHY_RL_RELEASE_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �ŵ��ͷ�������Ϣ�����ݽṹ
             ������Ҫ�ͷŵ��ŵ�

*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                      /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;         /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                          usOPID;          /* ������ʶ */
    VOS_UINT16                          usReserve1;
    VOS_UINT16                          usPhyChannelNum; /* �����ŵ��� */
    PHYITF_PHY_REL_CHANNEL_INFO_STRU    astPhyChInfo[RRC_PHY_MAX_PHYCHAN_NUM];

}RRC_PHY_RL_RELEASE_REQ_STRU;


/*****************************************************************************
 �ṹ��    : PHY_RRC_RL_EACH_CHANNEL_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ÿ�������ŵ���֤ʵ���ݽṹ

*****************************************************************************/

typedef struct
{
    VOS_UINT16                                  usFreqInfo;                     /* Ƶ����Ϣ */
    VOS_INT16                                   sSecondScrameCode;              /* �ڶ����� */
    VOS_INT32                                   lPrimaryScrameCode;             /* ������   */
    PHYITF_PHYCH_TYPE_ENUM_UINT16               enPhyChannelType;
    PHYITF_CHANNEL_CONFIG_RESULT_ENUM_UINT16    enIndicator;                    /* ���ý��,0����ɹ�����������ʧ��*/
    PHYITF_SYNC_NEED_ENUM_UINT16                enSyncAIndicator;               /* �Ƿ���Ҫͬ��A��ָʾ, ֻ���dpch/fdpch , ֻ�ж�ӦreqΪunkown������ʵֵ����unkown����reqͬ��ָʾ����һ�� �����ŵ�һ����NO NEED��*/
    VOS_UINT16                                  usRsv1;
}PHY_RRC_RL_EACH_CHANNEL_CNF_STRU;

/*****************************************************************************
 �ṹ��    : PHY_RRC_RL_SETUP_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �ŵ�����֤ʵ��Ϣ�����ݽṹ
             ÿ��RRC_PHY_RL_SETUP_REQ_STRU��Ϣ��Ӧһ��CNF��Ϣ

*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                          usOPID;                 /* ������ʶ */

    VOS_UINT16                          usReserve1;             /* �ֽڶ���*/
    VOS_UINT16                          usPhyChannelNum;        /* �����ŵ�Num��*/
    PHY_RRC_RL_EACH_CHANNEL_CNF_STRU    astPhyChannelCnf[RRC_PHY_MAX_PHYCHAN_NUM];

}PHY_RRC_RL_SETUP_CNF_STRU;

/*****************************************************************************
 �ṹ��    : PHY_RRC_RL_MODIFY_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �ŵ��޸�֤ʵ��Ϣ�����ݽṹ
             ÿ��RRC_PHY_RL_MODIFY_REQ_STRU��Ϣ��Ӧһ��CNF��Ϣ

*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                          usOPID;                 /* ������ʶ*/

    VOS_UINT16                          usReserve1;             /* �ֽڶ���*/
    VOS_UINT16                          usPhyChannelNum;        /* �����ŵ�Num��*/
    PHY_RRC_RL_EACH_CHANNEL_CNF_STRU    astPhyChannelCnf[RRC_PHY_MAX_PHYCHAN_NUM]; /* ���ý��������ͬsetup*/

}PHY_RRC_RL_MODIFY_CNF_STRU;

/*****************************************************************************
 �ṹ��    : PHY_RRC_RL_RELEASE_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �ŵ��ͷ�֤ʵ��Ϣ�����ݽṹ
             ÿ��RRC_PHY_RL_RELEASE_REQ_STRU��Ϣ��Ӧһ��CNF��Ϣ

*****************************************************************************/

typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                          usOPID;                 /* ������ʶ */

    VOS_UINT16                          usReserve1;             /* �ֽڶ���*/
    VOS_UINT16                          usPhyChannelNum;        /* �����ŵ�Num��*/
    PHY_RRC_RL_EACH_CHANNEL_CNF_STRU    astPhyChannelCnf[RRC_PHY_MAX_PHYCHAN_NUM]; /* ���ý��������ͬsetup*/

}PHY_RRC_RL_RELEASE_CNF_STRU;

/*****************************************************************************
 �ṹ��    : PHY_RRC_ACTIVATE_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����ָʾ��Ϣ�����ݽṹ
             ÿ������������Ϣ��Ӧһ������ָʾ��Ϣ

*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                          usOPID;                 /* ������ʶ */
    VOS_UINT16                          usMode;                 /* Setup,Modify,Releaseԭ�����Ӧ */
    VOS_UINT16                          usReserve1;             /* �ֽڶ���*/

    VOS_UINT16                          usCFN;                  /* ������Ч��CFN */
    VOS_UINT16                          usPhyChannelNum;        /* �����ŵ�Num��*/
    PHY_RRC_RL_EACH_CHANNEL_CNF_STRU    astPhyChannelCnf[RRC_PHY_MAX_PHYCHAN_NUM]; /* ���ý��������ͬsetup */


}PHY_RRC_ACTIVATE_IND_STRU;


/*****************************************************************************
 �ṹ��    : PHYITF_CCTRCH_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����ϴ����ŵ��ṹ
 *****************************************************************************/
typedef struct
{
    PHYITF_CCTRCH_ID_ENUM_UINT16        enCctrchId;  /* �����ŵ����� */
    VOS_UINT16                          usParamLen;  /* ���õ�CcTrch���� */
#if (INTERFACE_TYPE == INTERFACE_PS)
    VOS_INT8                            acCcTrchParam[RRC_PHY_CCTRCH_PARA_LEN]; /* �ŵ����������� */
#elif (INTERFACE_TYPE == INTERFACE_DSP)
    VOS_INT16                           asCcTrchParam[RRC_PHY_CCTRCH_PARA_LEN/2]; /* _H2ASN_Skip  �ŵ����������� */
#endif
}PHYITF_CCTRCH_STRU;


/*****************************************************************************
 �ṹ��    : RRC_PHY_TRCH_CONFIG_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����ϴ����ŵ�����������Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                          usOPID;                 /* ������ʶ */
    VOS_UINT16                          usReserve1;
    VOS_UINT16                          usCcTrchNum;            /* ���õ�CcTrch�ĸ��� */
    PHYITF_CCTRCH_STRU                  astCcTrch[RRC_PHY_CCTRCH_NUM];   /* �ṹ�� */   /* _H2ASN_Replace PHYITF_CCTRCH_PARA_STRU astCcTrch[RRC_PHY_CCTRCH_NUM]; */

}RRC_PHY_TRCH_CONFIG_REQ_STRU;


/*****************************************************************************
 �ṹ��    : RRC_PHY_TRCH_RELEASE_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����ϴ����ŵ��ͷ�������Ϣ���ݽṹ


*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                          usOPID;                 /* ������ʶ */
    VOS_UINT16                          usCcTrchID;             /* �����ͨ���ı�ʶ */
    VOS_INT16                           sActiveTime;            /* �����ŵ��ͷż���ʱ�� -1Ϊ�������� */
#if FEATURE_WCBS == FEATURE_ON
    VOS_UINT16                          usCcTrchIndex;          /* ����ϴ����ŵ����� */
    VOS_UINT16                          usReserve;              /* ���� */
#endif
}RRC_PHY_TRCH_RELEASE_REQ_STRU;


/*****************************************************************************
 �ṹ��    : PHY_RRC_TRCH_CONFIG_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����ϴ����ŵ�����֤ʵ��Ϣ���ݽṹ


*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                          usOPID;                 /* ������ʶ */
    VOS_UINT16                          usCcTrchID;             /* �����ͨ���ı�ʶ */
    VOS_UINT16                          usReserve1;

}PHY_RRC_TRCH_CONFIG_CNF_STRU;


/*****************************************************************************
 �ṹ��    : PHY_RRC_TRCH_RELEASE_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����ϴ����ŵ��ͷ�֤ʵ��Ϣ���ݽṹ


*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                          usOPID;                 /* ������ʶ */
    VOS_UINT16                          usCcTrchID;             /* �����ͨ���ı�ʶ */
    VOS_UINT16                          usReserve1;

}PHY_RRC_TRCH_RELEASE_CNF_STRU;


/*****************************************************************************
 ö����    : PHYITF_RELALL_REASON_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : REL ALL ԭ��ö��
*****************************************************************************/

enum    PHYITF_RELALL_REASON_ENUM
{

    PHYITF_RELALL_SYSHO                 = 0, /*ϵͳ���л��ͷ�����*/
    PHYITF_RELALL_POWER_OFF             = 1, /*�ػ��ͷ�����*/
    PHYITF_RELALL_OTHER                 = 2, /*����ԭ��RelAll*/
    PHYITF_RELALL_REASON_BUTT

};
typedef VOS_UINT16 PHYITF_RELALL_REASON_ENUM_UINT16;


/*****************************************************************************
 �ṹ��    : PHY_RRC_RELALL_PHYCH_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �ͷ������ŵ����������Դ�������ص���ʱ״̬��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                          usOPID;                 /* ������ʶ */
    PHYITF_RELALL_REASON_ENUM_UINT16    enReason;               /*�ͷŵ�ԭ��*/
    VOS_INT16                           sActiveTime;            /* ����ʱ�� */
}RRC_PHY_RELALL_REQ_STRU;

/*****************************************************************************
 �ṹ��    : PHY_RRC_RELALL_PHYCH_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �ͷ������ŵ����������Դ�������ص���ʱ״̬��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                          usOPID;                 /* ������ʶ */

} PHY_RRC_RELALL_CNF_STRU;

/*****************************************************************************
 �ṹ��    : PHY_RRC_RELALL_PHYCH_ACTIVATE_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �ͷ������ŵ����������Դ������ʱ�䵽������ϱ�active ind
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                          usOPID;                 /* ������ʶ */
    VOS_UINT16                          usCFN;                  /* ������Ч��CFN */
    VOS_UINT16                          usReserve1;             /* ���ֽڶ��� */
}PHY_RRC_RELALL_PHYCH_ACTIVATE_IND_STRU;

/*****************************************************************************
 �ṹ��    : PHYITF_POWER_CONTROL_QUALITY_TARGET_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ���ʿ�������Ŀ��
 *****************************************************************************/
typedef struct
{
    VOS_UINT16                          usTrchID;        /* �����ŵ���ʶ                */
    VOS_INT16                           sQualityValue;   /* ����-6.3~0��ֵ��STEP= 0.1   */

}PHYITF_POWER_CONTROL_QUALITY_TARGET_STRU;

/*****************************************************************************
 �ṹ��    : RRC_PHY_POWER_CONTROL_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ���ʿ���������Ϣ���ݽṹ
             ÿ����Ӧһ��PHY_RRC_POWER_CONTROL_CNF��Ϣ

*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16                  enMsgID;            /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usOPID;             /* ������ʶ */
    VOS_INT16                                   sActiveTime;        /* ����ʱ�� */
    VOS_UINT16                                  usTrchCnt;          /* ����TRCH������ */
    PHYITF_POWER_CONTROL_QUALITY_TARGET_STRU    astQualityTarget[RRC_PHY_MAX_TRCH_NUM];

}RRC_PHY_POWER_CONTROL_REQ_STRU;


/*****************************************************************************
 �ṹ��    : PHY_RRC_POWER_CONTROL_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ���ʿ���֤ʵ��Ϣ���ݽṹ


*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                          usOPID;                 /* ������ʶ */

}PHY_RRC_POWER_CONTROL_CNF_STRU;



/*****************************************************************************
 �ṹ��    : PHY_RRC_SYNC_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �����ͬ��ָʾ��Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_INT16                           sNoSense;               /* not defined yet */

}PHY_RRC_SYNC_IND_STRU;


/*****************************************************************************
 �ṹ��    : PHY_RRC_OUT_OF_SYNC_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �����ʧ��ָʾ��Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                /* ԭ������ */ /*_H2ASN_Skip*/
    PHYITF_BOOL_ENUM_UINT16             enSyncAAFail;           /* �Ƿ�ͬ��AAʧ�� */

}PHY_RRC_OUT_OF_SYNC_IND_STRU;

/*****************************************************************************
 �ṹ��    : PHY_RRC_RL_FAIL_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �������·ʧ����Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_INT16                           sNoSense;               /* not defined yet */

}PHY_RRC_RL_FAIL_IND_STRU;

/*****************************************************************************
 �ṹ��    : PHY_RRC_DISABLE_ULDCCH_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �Ƿ��ֹ��������dcch
 *****************************************************************************/
typedef   struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                /* ԭ������ */ /*_H2ASN_Skip */

    PHYITF_BOOL_ENUM_UINT16             enDisableUlDcch;        /* VALID��ʾ��ֹ���ͣ�invalid��ʾ������������ */

}PHY_RRC_DISABLE_ULDCCH_IND_STRU;


/*****************************************************************************
 �ṹ��    : RRC_PHY_RESET_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��λ�����������Ϣ���ݽṹ


*****************************************************************************/
typedef struct
 {

    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                          usReserve1;

}RRC_PHY_RESET_REQ_STRU;


/*****************************************************************************
 �ṹ��    : PHY_RRC_ERROR_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��������ָʾ��Ϣ���ݽṹ


*****************************************************************************/
typedef  struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_INT16                           sErrorCode;             /* not defined yet */

}PHY_RRC_ERROR_IND_STRU;



/*****************************************************************************
 �ṹ��    : PHYITF_CELL_SEARCH_FREQ_LIST_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : С��������ɢƵ����Ϣ��ָ���ж��ٸ���ɢƵ��Ҫ����
 *****************************************************************************/
typedef struct
{
    VOS_UINT16                              usFreqCnt;                       /* Ƶ���б���Ƶ�����Ŀ,Ϊ0���ʾû�� */
    VOS_UINT16                              usReserve1;
    VOS_UINT16                              ausFreqList[RRC_PHY_MAX_FREQ_NUM];/* Ƶ���б��о����Ƶ����Ϣ,ÿ��ֵΪʵ��Ƶ��ֵ��5*/

}PHYITF_CELL_SEARCH_FREQ_LIST_INFO_STRU;


/**************************С��������ص�����**************************************************/

/****************************�����������ݽṹ***********************************/

/*****************************************************************************
 �ṹ��    : PHYITF_CELL_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : С����Ϣ
 *****************************************************************************/
typedef struct
{
    VOS_INT16                           sCellID;               /* С����ID */
    VOS_UINT16                          usPrimaryScramCode;    /* С���������� */
    VOS_UINT16                          usRefTimeDifference;

    VOS_UINT16                          usReadSFNInd;           /* �Ƿ���Ҫ����SFN */
    VOS_UINT16                          usSFNSFNTimeDiffInd;    /* ����Ҫ����SFN -SFN Time Difference */
    VOS_UINT16                          usOFFInd;               /* �Ƿ���Ҫ����OFF */
    VOS_UINT16                          usTMInd;                /* �Ƿ���Ҫ����TM  */

    /* R׼�����ʹ�õ�ƫ��������ѭ���¹���
 ����  ��С����������EC\N����ʾ��ucQHyst2
       ��С����������RSCP��ʾ��  ucQHyst1
����   ��С����������EC\N����ʾ��sQoffset2SN
������ ��С����������RSCP��ʾ��  sQoffset1SN */

    VOS_INT16                           sOffset1;
    VOS_INT16                           sOffset2;

    VOS_INT16                           sQqualmin;
    VOS_INT16                           sQrxlevmincompensation;

    VOS_UINT16                          usTDIndicator;          /*1��ʾʹ�÷��ּ���0��ʾ��ʹ�÷��ּ�*/


}PHYITF_CELL_INFO_STRU;

/*****************************************************************************
 ö����    : PHYITF_RAT_PRI_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  :
*****************************************************************************/
enum    PHYITF_RAT_PRI_ENUM
{
    PHYITF_RAT_PRI_NULL_PRI     = 0,                                            /* ��Ӧ���뼼����֧�� */
    PHYITF_RAT_PRI_LOW          = 1,                                            /* ��Ӧ���뼼��Ϊ�����ȼ� */
    PHYITF_RAT_PRI_MID          = 2,                                            /* ��Ӧ���뼼��Ϊ�����ȼ� */
    PHYITF_RAT_PRI_HIGH         = 3,                                            /* ��Ӧ���뼼��Ϊ�����ȼ� */

    PHYITF_RAT_PRI_BUTT
};
typedef VOS_UINT16 PHYITF_RAT_PRI_ENUM_UINT16;


/*****************************************************************************
 �ṹ��    : PHYITF_CELL_ADJUGE_PARA_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RRC_PHY_IDLE_MEASURE_REQ_STRU ��
             PHYITF_CELL_SEL_MEASURE_STRU  ��С���о�����
 *****************************************************************************/
typedef struct
{

    PHYITF_CELL_ADJUGE_TYPE_ENUM_UINT16  enCellType;
    PHYITF_CELL_SEARCH_FLAG_ENUM_UINT16  enSSearchFlag ;
    VOS_INT16                            sSSearch;
    PHYITF_MEAS_QUANTITY_ENUM_UINT16     enMeasQuantity;
    PHYITF_SERVE_CELL_STATUS_ENUM_UINT16 enServStatus;
    VOS_INT16                            sMeasStopThr;                          /* ���ڸ����ޣ���ͣ���� */
    VOS_UINT16                           usNlayers;                             /* ���и����ȼ�W��Ƶ,LTEƵ���GSMƵ�����ܸ��� */
    PHYITF_BOOL_ENUM_UINT16              enHighPriMeasFlg;                      /* �����ȼ�������� ,PHYITF_VALID��ʾҪ�������ȼ�����,PHYITF_INVALID��ʾ����H+L */
    PHYITF_RAT_PRI_ENUM_UINT16           enWcdmaPri;                             /* WCDMA���ȼ� */
    PHYITF_RAT_PRI_ENUM_UINT16           enGsmPri;                               /* GSM���ȼ� */
    PHYITF_RAT_PRI_ENUM_UINT16           enLtePri;



    /* >Sprioritysearch1 MP Integer (0..62 by step of 2) dB REL-8 */
    VOS_UINT16                           usPriSearch1;                           /* [0~62] RSCP, dB */

    /* >Sprioritysearch2 MD Integer (0..7 by step of 1) dB, default value is 0 REL-8 */
    VOS_UINT16                           usPriSearch2;                           /* [0~7] dB, default value is 0 */

    PHYITF_CELL_SEARCH_FLAG_ENUM_UINT16  enPriSearchFlg ;
}PHYITF_CELL_ADJUGE_PARA_INFO_STRU;


/*****************************************************************************
 �ṹ��    : PHYITF_INTRA_FREQ_CELL_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ͬƵС����Ϣ
 *****************************************************************************/
typedef struct
{
    VOS_UINT16                          usFreqInfo;                                             /* Ƶ���Ƶ����Ϣ            */

    VOS_UINT16                          usFreqBandNo;                                           /* Ƶ�κ�:1,2,3,4,5,6*/
    VOS_UINT16                          usTxRxFreqSeparation;                                   /* �շ�Ƶ��*/
    VOS_UINT16                          usFreqPriority;                         /* Ƶ�����ȼ� */
    VOS_UINT16                          usReserve1;

    VOS_UINT16                          usIntraFreqCellNum;                     /* �����ͬƵ�ٽ�С������Ŀ  */
    PHYITF_CELL_INFO_STRU               astIntraFreqCell[RRC_PHY_MAX_INTRA_FREQ_CELL_NUM]; /* ͬƵ�ٽ�С���б����Ϣ    */

}PHYITF_INTRA_FREQ_CELL_INFO_STRU;


/*****************************************************************************
 �ṹ��    : PHYITF_INTER_FREQ_CELL_INFO_ITEM_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��ƵС����Ԫ
 *****************************************************************************/
typedef struct
{
    VOS_UINT16                          usFreqInfo;   /* Ƶ���Ƶ����Ϣ */

    VOS_UINT16                          usFreqBandNo;                                           /* Ƶ�κ�:1,2,3,4,5,6*/
    VOS_UINT16                          usTxRxFreqSeparation;                                   /* �շ�Ƶ��*/
    VOS_UINT16                          usFreqPriority;                         /* ��WΪ��ģʱ����Ƶ�����ȼ��̶�Ϊ0. */
    VOS_UINT16                          usDetectedCellMeasureInd;                               /* �Ƿ���Ҫ��������Detected����С�� */

    VOS_UINT16                          usCellNum;                                              /* һ��Ƶ���µ�С����Ŀ */
    PHYITF_CELL_INFO_STRU               astInterCellInfo[RRC_PHY_MAX_EACH_FREQ_CELL_NUM];    /* С������Ϣ               */

}PHYITF_INTER_FREQ_CELL_INFO_ITEM_STRU;


/*****************************************************************************
 �ṹ��    : PHYITF_INTER_FREQ_CELL_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��ƵС����Ϣ
 *****************************************************************************/
typedef struct
{
    VOS_UINT16                              usInterFreqNum;  /* ����ӵ���ƵƵ����Ŀ       */
    VOS_UINT16                              usReserve1;      /* */
    PHYITF_INTER_FREQ_CELL_INFO_ITEM_STRU   astInterFreqCell[RRC_PHY_MAX_ADDITIONAL_CARRIER_NUM];

}PHYITF_INTER_FREQ_CELL_INFO_STRU;

/*****************************************************************************
 �ṹ��    : PHYITF_INTER_RAT_CELL_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��ϵͳС����Ϣ
 *****************************************************************************/
typedef struct
{
    VOS_UINT16                          usReserve1[2];
}PHYITF_INTER_RAT_CELL_INFO_STRU;

/*****************************************************************************
 �ṹ��    : PHYITF_LTE_FREQ_INFO_ITEM_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : WΪ��ģʱ������LTE������Ϣ

*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usFreq;                                 /* LTEƵ��� */
    VOS_UINT16                          usFreqPriority;                         /* LTEƵ�����ȼ���Ϣ , 0~9 */
}PHYITF_LTE_FREQ_INFO_ITEM_STRU;

/*****************************************************************************
 �ṹ��    : PHYITF_INTER_RAT_LTE_CELL_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : WΪ��ģʱ������LTE������Ϣ

*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usFreqNum;     /*��Ҫ������С������*/
    VOS_UINT16                          usReserve1;
    PHYITF_LTE_FREQ_INFO_ITEM_STRU      astLteFreqInfo[RRC_PHY_MAX_INTER_RAT_LTE_FREQ];

}PHYITF_INTER_RAT_LTE_CELL_INFO_STRU;

/*****************************************************************************
 �ṹ��    : RRC_PHY_IDLE_MEASURE_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : IDLE״̬����������Ϣ���ݽṹ

*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usOPID;                 /* ������ʶ */
    PHYITF_MEASURE_COMMAND_ENUM_UINT16          enCommand;              /* REQ������ */
    VOS_UINT16                                  usRelMeasTypeMask;      /* �����REL��Ϣ����������ָ����Ҫ�ͷŵĲ������� */
    PHYITF_MODIFY_TYPE_ENUM_UINT16              enModifyType;           /* ����������:�����ò����б�Ͳ�������, �������ò��������������� */
    PHYITF_HIGH_RATE_FLAG_ENUM_UINT16           enHighRateFlag;         /* �Ƿ��Ǹ��ٵı�־����ʼֵ��HCSС����������Я������ʱ����дΪTRUE */
    PHYITF_CELL_ADJUGE_PARA_INFO_STRU           stCellParaInfo;
    PHYITF_MEAS_REQ_END_FLAG_ENUM_UINT16        usMeaReqEndFlag;        /* �������������־ */  /* _H2ASN_IeChoice_Export PHYITF_MEAS_REQ_END_FLAG_ENUM_UINT16 */
    PHYITF_IDLE_MEAS_TYPE_ENUM_UINT16           enMeasTypeChoice;       /* �������� */ /* _H2ASN_IeChoice_Export PHYITF_IDLE_MEAS_TYPE_ENUM_UINT16 */

    union                                                                   /*_H2ASN_Skip*/
    {/*_H2ASN_Skip*/
        PHYITF_INTRA_FREQ_CELL_INFO_STRU    stIntraFreqCellEntity;  /* _H2ASN_Skip ͬƵ������Ϣ */
        PHYITF_INTER_FREQ_CELL_INFO_STRU    stInterFreqCellEntity;  /* _H2ASN_Skip ��Ƶ������Ϣ */
        PHYITF_INTER_RAT_CELL_INFO_STRU     stInterRatCellEntity;   /* _H2ASN_Skip ��ϵͳ�������Ϣ */
        PHYITF_INTER_RAT_LTE_CELL_INFO_STRU stInterRatLteCellEntity;            /* WΪ��ģʱ������LTE���� */
        /******************************************************************************************************
                _H2ASN_IeChoice_When        PHYITF_IDLE_MEAS_TYPE_ENUM_UINT16
        ******************************************************************************************************/
    }u;/*_H2ASN_Skip*/
}RRC_PHY_IDLE_MEASURE_REQ_STRU;

/*****************************************************************************
 �ṹ��    : PHY_RRC_IDLE_MEASURE_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : IDLE״̬����֤ʵ��Ϣ���ݽṹ

*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                          usOPID;                 /* ������ʶ */

}PHY_RRC_IDLE_MEASURE_CNF_STRU;


/*****************************************************************************
 �ṹ��    : PHYITF_CELL_MEASURE_RESULT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ÿ��С���Ĳ��������Ϣ
 *****************************************************************************/
typedef struct
{
    VOS_INT16                           sCellID;                                /* С����ID                                 */
    VOS_UINT16                          usPrimaryScramCode;                     /* С����������                             */
    VOS_INT32                           lSFNSFNTimeDifference;                  /* ��С������С����SFN��                    */
    VOS_INT16                           sCpichRscp;                             /* CPICH RSCP����ֵ                         */
    VOS_INT16                           sCpichEcN0;                             /* CPICH EcN0����ֵ                         */
    VOS_INT16                           sOFF;                                   /* OFF�������                              */
    VOS_UINT16                          usSfn;                                  /* ��ǰ��SFN,ֻ�������̨����               */
    VOS_INT32                           lTM;                                    /* TM������� */

} PHYITF_CELL_MEASURE_RESULT_STRU;

/*****************************************************************************
 �ṹ��    : PHYITF_INTRA_FREQ_RESULT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ͬƵС���������
 *****************************************************************************/
typedef struct
{
    VOS_UINT16                          usFreqInfo;             /* Ƶ����Ϣ */
    VOS_INT16                           sCarrierRSSI;           /* UtraCarrierRSSI��� */
    VOS_UINT16                          usReserve1;
    VOS_UINT16                          usIntraFreqCellNum;    /* Ƶ��С���ĸ��� */
    PHYITF_CELL_MEASURE_RESULT_STRU     astIntraFreqCell[PHY_RRC_MAX_REPORT_INTRA_FREQ_CELL_NUM];   /* Ƶ��С���Ĳ������                      */

} PHYITF_INTRA_FREQ_RESULT_STRU;

/*****************************************************************************
 �ṹ��    : PHYITF_INTER_FREQ_RESULT_ITEM_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��ƵС�����������Ԫ
 *****************************************************************************/
typedef struct
{
    VOS_UINT16                          usFreqInfo;   /* Ƶ����Ϣ*/
    VOS_INT16                           sCarrierRSSI; /* UtraCarrierRSSI����ֵ */
    VOS_UINT16                          usReserve1;
    VOS_UINT16                          usCellNum;    /* һ��Ƶ�����ϱ���С������ */
    PHYITF_CELL_MEASURE_RESULT_STRU     astInterFreqCell[PHY_RRC_MAX_REPORT_EACH_FREQ_CELL_NUM];     /* Ƶ��С���Ĳ������                       */

} PHYITF_INTER_FREQ_RESULT_ITEM_STRU;

/*****************************************************************************
 �ṹ��    : PHYITF_INTER_FREQ_RESULT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��ƵС���������
 *****************************************************************************/
typedef struct
{
    VOS_UINT16                          usInterFreqNum; /* ������Ƶ��Ƶ��ĸ��� */
    VOS_UINT16                          usReserve1;
    PHYITF_INTER_FREQ_RESULT_ITEM_STRU  astInterFreqReport[RRC_PHY_MAX_ADDITIONAL_CARRIER_NUM];

} PHYITF_INTER_FREQ_RESULT_STRU;

/*****************************************************************************
 �ṹ��    : PHY_RRC_IDLE_MEASURE_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : IDLE״̬����ָʾ��Ϣ�ṹ

*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                          usOPID;                 /* ������ʶ */

    #define     PHYITF_IDLE_MEAS_IND_SERV_CELL_CHOSEN       0
    #define     PHYITF_IDLE_MEAS_IND_INTRA_CELL_CHOSEN      1
    #define     PHYITF_IDLE_MEAS_IND_INTER_CELL_CHOSEN      2

    VOS_UINT16                              usReserve1;
    VOS_UINT16                              usReportTypeChoice;     /* ���α������Ч����*/

    union
    {
        PHYITF_CELL_MEASURE_RESULT_STRU     stServingCellResult;    /* ��ǰ����С���Ĳ������ */
        PHYITF_INTRA_FREQ_RESULT_STRU       stIntraFreqResult;      /* ͬƵС���Ĳ������ */
        PHYITF_INTER_FREQ_RESULT_STRU       stInterFreqResult;      /* ��ƵС���Ĳ������ */
    }unReportResult;
}PHY_RRC_IDLE_MEASURE_IND_STRU;


/*****************************************************************************
 �ṹ��    : PHYITF_CELL_SEL_MEASURE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����״̬�µ�С��ѡ��Ĳ����ṹ
 *****************************************************************************/
typedef struct
{
    VOS_UINT16                          usCurrentStatus;          /* ��ǰUE״̬ */
    VOS_UINT16                          usReserve1;
    PHYITF_CELL_ADJUGE_PARA_INFO_STRU   stCellParaInfo;
    PHYITF_MEAS_REQ_END_FLAG_ENUM_UINT16   usMeaReqEndFlag;              /* �������������־ */  /* _H2ASN_IeChoice_Export PHYITF_MEAS_REQ_END_FLAG_ENUM_UINT16 */
    PHYITF_CONN_MEAS_TYPE_ENUM_UINT16           enMeasTypeChoice;             /* �������� */  /* _H2ASN_IeChoice_Export PHYITF_CONN_MEAS_TYPE_ENUM_UINT16 */
    union                                                                     /* _H2ASN_Skip */
    {                                                                         /* _H2ASN_Skip */
        PHYITF_INTRA_FREQ_CELL_INFO_STRU    stIntraFreqCellEntity;    /* _H2ASN_Skip Ƶ�ڲ�����Ϣ */
        PHYITF_INTER_FREQ_CELL_INFO_STRU    stInterFreqCellEntity;    /* _H2ASN_Skip Ƶ�������Ϣ */
        PHYITF_INTER_RAT_CELL_INFO_STRU     stInterRatCellEntity;     /* _H2ASN_Skip ��ϵͳGSM������Ϣ */
        PHYITF_INTER_RAT_LTE_CELL_INFO_STRU stInterRatLteCellEntity;  /* WΪ��ģPCH̬ʱ������LTE���� */
    /******************************************************************************************************
            _H2ASN_IeChoice_When        PHYITF_CONN_MEAS_TYPE_ENUM_UINT16
    ******************************************************************************************************/
    }u;/* _H2ASN_Skip */
}PHYITF_CELL_SEL_MEASURE_STRU;


/*****************************************************************************
 �ṹ��    : PHYITF_INTRA_FREQ_MEASURE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����״̬�µ�ͬƵ�����ṹ
 *****************************************************************************/
typedef struct
{
    VOS_UINT16                          usFreqInfo;                                             /* Ƶ����Ϣ */

    VOS_UINT16                          usFreqBandNo;                                           /* Ƶ�κ�:1,2,3,4,5,6*/
    VOS_UINT16                          usTxRxFreqSeparation;                                   /* �շ�Ƶ��,�ñ���ĿǰPHYû��ʹ��*/

    VOS_UINT16                          usDetectedCellMeasureInd;                               /* �Ƿ���Ҫ��������Detected����С�� */
    VOS_UINT16                          usDetectedCellSynInfoInd;                               /* ��⼯�Ƿ���Ҫ�ϱ�ͬ����Ϣ,���Ҫ���ϱ���ֵ��Ϊ1������Ϊ0 */
    VOS_UINT16                          usIntraAllCellListNum;                                  /* UE֪��������С������Ŀ*/
    PHYITF_CELL_INFO_STRU               astIntraAllCellList[RRC_PHY_MAX_INTRA_FREQ_CELL_NUM];   /* UE֪��������С������Ϣ�б� */
}PHYITF_INTRA_FREQ_MEASURE_STRU;

/*****************************************************************************
 �ṹ��    : PHYITF_ADJACENT_FREQ_MEASURE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����״̬�µ���Ƶ�����ṹ
 *****************************************************************************/
typedef struct
{
    VOS_UINT16                          usFreqInfo;                                             /* Ƶ����Ϣ */

    VOS_UINT16                          usFreqBandNo;                                           /* Ƶ�κ�:1,2,3,4,5,6*/
    VOS_UINT16                          usTxRxFreqSeparation;                                   /* �շ�Ƶ��,�ñ���ĿǰPHYû��ʹ�� */

    VOS_UINT16                          usDetectedCellMeasureInd;                               /* �Ƿ���Ҫ��������Detected����С�� */
    VOS_UINT16                          usDetectedCellSynInfoInd;                               /* ��⼯�Ƿ���Ҫ�ϱ�ͬ����Ϣ,���Ҫ���ϱ���ֵ��Ϊ1������Ϊ0 */

    VOS_UINT16                          usIntraInterAllCellListNum;                             /* UE֪����Intra Freq��Inter Freq����Ҫ����С������Ŀ,С������astAdjacentFreqCellList������ǰ�ˣ�
                                                                                                   PHY��Ҫ���ⲿ��С����ͬƵ����Ƶ����IND���ϱ� */

    VOS_UINT16                          usIntraAllCellListNum;                                  /* UE֪����Intra Freq��Ҫ����С������Ŀ,��Inter Freq����Ҫ������С������Ŀ��С����astAdjacentFreqCellList����
                                                                                                   ����usIntraInterAllCellListNum֮���ţ�PHY��Ҫ���ⲿ��С����ͬƵ����IND���ϱ� */

    VOS_UINT16                          usInterAllCellListNum;                                  /* UE֪����Inter Freq��Ҫ����С������Ŀ,��Intra Freq����Ҫ������С������Ŀ��С����astAdjacentFreqCellList����
                                                                                                   ����usIntraAllCellListNum֮����,PHY��Ҫ���ⲿ��С������Ƶ����IND���ϱ� */

    PHYITF_CELL_INFO_STRU               astAdjacentFreqCellList[RRC_PHY_MAX_ADJACENT_FREQ_CELL_NUM];     /* UE֪��������Ҫ����С������Ϣ�б�����Intra&Inter Freq��Intra Freq��Inter Freq ˳���������*/
}PHYITF_ADJACENT_FREQ_MEASURE_STRU;


/*****************************************************************************
 �ṹ��    : PHYITF_INTER_FREQ_ALL_CELL_LIST_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����״̬��Ҫ������������ƵС���б�
 *****************************************************************************/
typedef struct
{
    VOS_UINT16                          usFreqInfo;                                             /* ��Ƶ��Ƶ����Ϣ */

    VOS_UINT16                          usFreqBandNo;                                           /* Ƶ�κ�:1,2,3,4,5,6*/
    VOS_UINT16                          usTxRxFreqSeparation;                                   /* �շ�Ƶ��*/

    VOS_UINT16                          usInterFreqCellNum;                                     /* ��Ƶ���µ�С������Ŀ */

    PHYITF_CELL_INFO_STRU               astInterFreqCellInfo[RRC_PHY_MAX_EACH_FREQ_CELL_NUM];   /* һ��Ƶ���µ�����С������Ϣ */

}PHYITF_INTER_FREQ_ALL_CELL_LIST_STRU;

/*****************************************************************************
 �ṹ��    : PHYITF_INTER_FREQ_MEASURE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����״̬�µ���Ƶ�����ṹ
 *****************************************************************************/
typedef struct
{
    VOS_UINT16                          usMeasPeriod;        /* �������� */
    VOS_UINT16                          usMinIntraCellNum;   /* ��Ҫ������Ƶ��С������Ŀ */
    VOS_UINT16                          usInterFreqNum;      /* UE֪������ƵƵ�����Ŀ */
    VOS_UINT16                          usReserve1;

    PHYITF_INTER_FREQ_ALL_CELL_LIST_STRU astInterAllCellList[RRC_PHY_MAX_ADDITIONAL_CARRIER_NUM];

}PHYITF_INTER_FREQ_MEASURE_STRU;

/*****************************************************************************
 �ṹ��    : RRC_PHYITF_CONNECT_MEASURE_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����״̬����������Ϣ���ݽṹ

*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip */
    RRC_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                /* ԭ������ */ /*_H2ASN_Skip */
    VOS_UINT16                                  usOPID;                 /* ������ʶ */
    PHYITF_MEASURE_COMMAND_ENUM_UINT16          enCommand;              /* ��������,0:�ͷţ�1:���� */
    VOS_UINT16                                  usRelMeasTypeMask;      /* �����REL��Ϣ����������ָ����Ҫ�ͷŵĲ������� */
    PHYITF_MODIFY_TYPE_ENUM_UINT16              enModifyType;           /* ����������:�����ò����б�Ͳ�������, �������ò��������������� */
    PHYITF_HIGH_RATE_FLAG_ENUM_UINT16           enHighRateFlag;         /* �Ƿ��Ǹ��ٵı�־����ʼֵ��HCSС����������Я������ʱ����дΪTRUE������ֻ̬��PCH����Ч */
    VOS_UINT16                                  usReserve1;

    PHYITF_CONNECT_MEAS_REQ_TYPE_ENUM_UINT16    enMeasTypeChoice;  /* ����״̬�²������������ */   /* _H2ASN_IeChoice_Export PHYITF_CONNECT_MEAS_REQ_TYPE_ENUM_UINT16 */

    /* ������Ϣ */
    union                                                                                                   /* _H2ASN_Skip */
    {                                                                                                       /* _H2ASN_Skip */
        PHYITF_INTRA_FREQ_MEASURE_STRU      stIntraFreqMeasureEntity;               /* Ƶ�ڲ����Ĳ���     */    /* _H2ASN_Skip */
        PHYITF_INTER_FREQ_MEASURE_STRU      stInterFreqMeasureEntity;               /* Ƶ������Ĳ���     */    /* _H2ASN_Skip */
        VOS_UINT16                          usRptPeriod;                            /* �ڲ������ϱ�����   */    /* _H2ASN_Skip */
        PHYITF_CELL_SEL_MEASURE_STRU        stCellSelMeasureEntity;                 /* С�����Ӳ����Ĳ��� */    /* _H2ASN_Skip */
        PHYITF_INTER_RAT_CELL_INFO_STRU     stInterRatMeasureEntity;                /* ϵͳ������Ĳ���   */    /* _H2ASN_Skip */
        PHYITF_ADJACENT_FREQ_MEASURE_STRU   stAdjacentFreqMeasureEntity;            /* ��Ƶ�����Ĳ���     */    /* _H2ASN_Skip */
        PHYITF_INTER_RAT_LTE_CELL_INFO_STRU     stInterRatLteCellEntity;        /* WΪ��ģʱ������LTE���� */
        /******************************************************************************************************
            _H2ASN_IeChoice_When        PHYITF_CONNECT_MEAS_REQ_TYPE_ENUM_UINT16
        ******************************************************************************************************/
    }u;                                                                         /* _H2ASN_Skip */
}RRC_PHYITF_CONNECT_MEASURE_REQ_STRU;

/*****************************************************************************
 �ṹ��    : PHY_RRC_CONNECT_MEASURE_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����״̬����֤ʵ��Ϣ���ݽṹ

*****************************************************************************/

typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                          usOPID;                 /* ������ʶ */

}PHY_RRC_CONNECT_MEASURE_CNF_STRU;



/*****************************************************************************
 �ṹ��    : PHYITF_CELL_SEL_REPORT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����״̬�µ�С��ѡ��Ĳ�������
 *****************************************************************************/
typedef struct
{
    #define PHYITF_CELL_SEL_REPORT_SEV_CELL_CHOSEN          0
    #define PHYITF_CELL_SEL_REPORT_INTRA_CELL_CHOSEN        1
    #define PHYITF_CELL_SEL_REPORT_INTER_CELL_CHOSEN        2

    VOS_UINT16                          usReserve1;
    VOS_UINT16                          usReportTypeChoice;  /* �������Ч���� */

    /* �ϱ���Ϣ�Ĺ�ͬ�� */
    union
    {
        PHYITF_CELL_MEASURE_RESULT_STRU stServingCellResult; /* ��С���Ĳ������   */
        PHYITF_INTRA_FREQ_RESULT_STRU   stIntraFreqResult;   /* Ƶ��С���Ĳ������ */
        PHYITF_INTER_FREQ_RESULT_STRU   stInterFreqResult;   /* Ƶ��С���Ĳ������ */
    }unReportResult;

}PHYITF_CELL_SEL_REPORT_STRU;


/*****************************************************************************
 �ṹ��    : PHYITF_INTRA_FREQ_REPORT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����״̬�µ�ͬƵ��������
 *****************************************************************************/
typedef struct
{
    VOS_UINT16                          usReportCellNum;                        /* �����а�����С����Ŀ */

    VOS_UINT16                          usReportSecUlFreqCellNum;               /* �����а�����SecULFreqС����Ŀ */

    PHYITF_CELL_MEASURE_RESULT_STRU     astReportCellResult[PHY_RRC_MAX_REPORT_INTRA_FREQ_CELL_NUM]; /* С���Ĳ������ */

    PHYITF_CELL_MEASURE_RESULT_STRU     astReportSecUlFreqCellResult[PHY_RRC_MAX_REPORT_SEC_UL_FREQ_CELL_NUM]; /* SecULFreqС���Ĳ������ */

}PHYITF_INTRA_FREQ_REPORT_STRU;

/*****************************************************************************
 �ṹ��    : PHYITF_INTER_FREQ_REPORT_ITEM_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����״̬�µ���Ƶ����������Ԫ
 *****************************************************************************/
typedef struct
{
    VOS_UINT16                          usFreqInfo;         /* Ƶ����Ϣ */

    VOS_INT16                           sCarrierRSSI;       /* UtraCarrierRSSI����ֵ */

    VOS_UINT16                          usInterFreqCellNum; /* ��Ƶ���µ�С������Ŀ  */

    VOS_UINT16                          usReserve1;

    PHYITF_CELL_MEASURE_RESULT_STRU     astInterFreqCell[PHY_RRC_MAX_REPORT_EACH_FREQ_CELL_NUM];     /* Ƶ��С���Ĳ������ */

}PHYITF_INTER_FREQ_REPORT_ITEM_STRU;

/*****************************************************************************
 �ṹ��    : PHYITF_INTER_FREQ_REPORT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����״̬�µ���Ƶ��������
 *****************************************************************************/
typedef struct

{
    VOS_UINT16                          usInterFreqNum;                         /* �����а�����Ƶ����Ŀ */

    VOS_UINT16                          usReserve1;

    PHYITF_INTER_FREQ_REPORT_ITEM_STRU  astInterFreqReport[RRC_PHY_MAX_ADDITIONAL_CARRIER_NUM];

}PHYITF_INTER_FREQ_REPORT_STRU;

/*****************************************************************************
 �ṹ��    : PHYITF_INTERNAL_REPORT_RXTX_TIME_DIFFS_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����״̬�µ��ڲ�������Rx_Tx��
 *****************************************************************************/
typedef struct
{
    VOS_UINT16                          usRLPrimaryScramCode;    /* RL��������      */

    VOS_UINT16                          usRxTxTimeDifference;    /* Rx��Tx��ʱ���  */
}PHYITF_INTERNAL_REPORT_RXTX_TIME_DIFFS_STRU;


/*****************************************************************************
 �ṹ��    : PHYITF_INTERNAL_REPORT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����״̬�µ��ڲ���������
 *****************************************************************************/
typedef struct
{
    VOS_INT16                                       sTxPower[RRC_PHY_MAX_SLOT_PLUS1_NUM];   /* UE���书��,0~14��ʱ϶�ϱ���ÿ֡�ϱ�һ��  */

    VOS_INT16                                       sTxMaxPower;                            /*ʵ�ʵ�������з��书��*/

    VOS_INT16                                       sTxMinPower;                            /* ʵ�ʵ���С���з��书��*/

    VOS_INT16                                       sUtraCarrierRSSI;                       /* �ز���RSSI�������   */

    VOS_UINT16                                      usRLNum;                                /* �������������ӵ���Ŀ */

    PHYITF_INTERNAL_REPORT_RXTX_TIME_DIFFS_STRU     astRxTxTimeDiffS[RRC_PHY_MAX_RL_NUM];   /* Rx��Tx��ʱ�������   */

}PHYITF_INTERNAL_REPORT_STRU;

/*****************************************************************************
 �ṹ��    : PHY_RRC_CONNECT_MEASURE_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����״̬����ָʾ��Ϣ���ݽṹ

*****************************************************************************/

typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16                  enMsgID;            /*_H2ASN_Skip*/   /* ԭ������ */
    VOS_UINT16                                  usOPID;             /* ������ʶ */

    VOS_UINT16                                  usHighRailwayMode;  /* ����ģʽָʾ���ڱ�Ƶ��������ʱ��Ч��1Ϊ����ģʽ��0Ϊ��ͨģʽ */
    PHYITF_CONNECT_MEAS_IND_TYPE_ENUM_UINT16    enMeasTypeChoice;   /* ������������� */   /* _H2ASN_IeChoice_Export PHYITF_CONNECT_MEAS_IND_TYPE_ENUM_UINT16 */
    union                                                                       /* _H2ASN_Skip */
    {                                                                           /* _H2ASN_Skip */
        PHYITF_INTRA_FREQ_REPORT_STRU           stIntraFreqRpt;                 /* _H2ASN_Skip */
        PHYITF_INTER_FREQ_REPORT_STRU           stInterFreqRpt;                 /* _H2ASN_Skip */
        PHYITF_CELL_SEL_REPORT_STRU             stCellSelRpt;
        /******************************************************************************************************
            _H2ASN_IeChoice_When        PHYITF_CONNECT_MEAS_IND_TYPE_ENUM_UINT16
        ******************************************************************************************************/
    }u;                                                                         /* _H2ASN_Skip */
}PHY_RRC_CONNECT_MEASURE_IND_STRU;

/*****************************************************************************
 �ṹ��    : PHY_RRC_AFC_LOCK_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : AFC���������Ϣ�ϱ�

*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;            /* ԭ������*/   /*_H2ASN_Skip*/
    PHYITF_BOOL_ENUM_UINT16             enAfcLockFlag;
    VOS_UINT16                          usAfcCurrVal;
    VOS_INT16                           sProtectTemp;        /* �±����� */

} PHY_RRC_AFC_LOCK_IND_STRU;

/*****************************************************************************
 �ṹ��    : RRC_PHY_DPCH_COMPRESSED_MODE_STATUS_CHANGE_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ѹģ״̬�ı�������Ϣ���ݽṹ

*****************************************************************************/

typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;            /* ԭ������*/   /*_H2ASN_Skip*/
    VOS_UINT16                          usOPID;             /* ������ʶ */
    VOS_UINT16                          usParaLen;          /* �����ĳ��� */
    VOS_UINT16                          usReserve1;
#if (INTERFACE_TYPE == INTERFACE_PS)
    VOS_UINT8                           aucCompModeChgPara[4]; /* ���ò����ĵ�һ���ֽ� */   /*_H2ASN_Replace PHYITF_COMP_MODE_CHG_PARA_STRU */
#elif (INTERFACE_TYPE == INTERFACE_DSP)
    VOS_UINT16                          ausCompModeChgPara[4/2]; /* _H2ASN_Skip ���ò����ĵ�һ���ֽ� */
#endif
}RRC_PHY_DPCH_COMPRESSED_MODE_STATUS_CHANGE_REQ_STRU;


/*****************************************************************************
 �ṹ��    : PHY_RRC_DPCH_COMPRESSED_MODE_STATUS_CHANGE_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ѹģ״̬�ı�֤ʵ��Ϣ���ݽṹ

*****************************************************************************/

typedef struct
{
    VOS_MSG_HEADER                                                           /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                             /* ԭ������*/   /*_H2ASN_Skip*/
    VOS_UINT16                          usOPID;                              /* ������ʶ */
    PHYITF_DPCH_COMPRESSED_MODE_STATUS_CHANGE_RESULT_ENUM_UINT16 enResult;   /* ѹģ���ý�� */
    VOS_UINT16                          usReserve1;

} PHY_RRC_DPCH_COMPRESSED_MODE_STATUS_CHANGE_CNF_STRU;



/*****************************************************************************
 �ṹ��    : PHYITF_DPCH_COMPRESSED_MODE_TGPS_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ѹģָʾPHY_RRC_DPCH_COMPRESSED_MODE_STATUS_IND_STRU �еĽṹ
 *****************************************************************************/
typedef struct
{
    VOS_UINT16                          usTgpsId;         /* TGPS ID    */
    VOS_UINT16                          usTgpsStatus;     /* TGPS��״̬ */

}PHYITF_DPCH_COMPRESSED_MODE_TGPS_STRU;


/*****************************************************************************
 �ṹ��    : PHY_RRC_DPCH_COMPRESSED_MODE_STATUS_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ѹģ״̬״ָ̬ʾ��Ϣ���ݽṹ

*****************************************************************************/
typedef struct
{

    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16              enMsgID;        /* ԭ������*/   /*_H2ASN_Skip*/
    VOS_UINT16                              usTgpsCnt;      /* �����TGPS���� */
    VOS_UINT16                              usOverlapTgpsCnt;   /* �����ص���TGPS�ĸ��� */
    VOS_UINT16                              usReserve1;

    VOS_UINT16                              ausOverlapTgpsId[RRC_PHY_MAX_TGPS];  /* �����ص���TGPS��ID */
    PHYITF_DPCH_COMPRESSED_MODE_TGPS_STRU   astTgps[RRC_PHY_MAX_TGPS];

}PHY_RRC_DPCH_COMPRESSED_MODE_STATUS_IND_STRU;




/**************************************�����������ݽṹ*******************************/
/*****************************************************************************
 �ṹ��    : PHYITF_QUA_PERIODIC_CRITERIA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ���������е����ڱ����׼
 *****************************************************************************/
typedef struct
{
    VOS_UINT16                          usInterval;
    VOS_UINT16                          usReportMount;

}PHYITF_QUA_PERIODIC_CRITERIA_STRU;


/*****************************************************************************
 �ṹ��    : PHYITF_QUA_EVENT_TRCH_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �¼���׼�е�ÿ�������ŵ���Ϣ
 *****************************************************************************/
typedef struct
{
     VOS_UINT16                         usTrCHID;
     VOS_UINT16                         usTotalCRC;
     VOS_UINT16                         usBadCRC;
     VOS_UINT16                         usPendingTime;

}PHYITF_QUA_EVENT_TRCH_STRU;

/*****************************************************************************
 �ṹ��    : PHYITF_QUA_PERIODIC_CRITERIA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ���������е��¼������׼
 *****************************************************************************/
typedef struct
{
    VOS_UINT16                          usEventTrCHNum;
    VOS_UINT16                          usReserve1;
    PHYITF_QUA_EVENT_TRCH_STRU          astEventTrCH[RRC_PHY_MAX_TRCH_NUM];

}PHYITF_QUA_EVENT_CRITERIA_STRU;

/*****************************************************************************
 �ṹ��    : RRC_PHY_QUALITY_MEASUREMENT_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��������������Ϣ���ݽṹ��
             Ŀǰ6720�汾���������������������:
             (1) BBP����ͬʱ�����8�������ŵ����������Բ�������������ڱ���һ�£�
             (2) BBP����ͬʱ�����3�������ŵ����в����¼�������
             (3) ���������Բ������¼�������������ͬʱ���ڣ�
             (4) ���������¼�����������PHY�������ȽϺ��ʣ�׼ȷ�Ըߣ�

             �ۺ�������������֧��������UE��Ҫ������������:
             (1) UTRAN->RRC: �½���������ʱ����Ҫ����жϵ�ǰ�Ƿ������ͬ����׼
             �������������
                 (1.1) ����Ѿ�������ͬ����׼���������������ܾ��µ�����������
                 ��������FAILURE��ԭ��ֵΪUE��֧�֣�
                 (1.2) �����������ͬ����׼����������������½�������������
             �������ԭ��RM��ͬʱά����������������������֮һ�ı���׼��Ϊ��
             �ڱ��棬��һ���ı���׼��Ϊ�¼����棬������ά��һ������׼��Ϊ������
             ģʽ�ġ�

             (2) UTRAN->RRC: �½���������������׼��Ϊ�����ϱ�ʱ��RRC->PHY: �½�
             ��������������׼����дΪ���ڱ��棬��stPeriodic��Ԫ��ָʾ�ϱ����ں�
             �ϱ���������ͨ��usMonitorTrchNum��ausMonitorTrchID��Ԫָʾ�������
             Ҫ�������ϱ���TrCH ID��

             (3) UTRAN->RRC: �½���������������׼��Ϊ�¼��ϱ�ʱ��RRC->PHY: �½�
             ��������������׼����дΪ�¼����棬��stEvent��Ԫ��ָʾ��Ҫ�����¼���
             ����TrCH ID���Ͷ�Ӧ���¼�����������

             (4) RRC->PHY: �������㵱ǰ�Ѿ������������������ϱ�׼��Ϊ���ڱ���:
                 (4.1) RRC�ٴ�ָʾ������½��ϱ�׼��Ϊ�¼���������������������
                 ���ܸ��¼�����׼�����������������֤ԭ�����ڱ���׼�����������
                 ����Ӱ�졣֮�����������ϱ����������������ָʾ�����ֱ���׼
                 ��Ĳ��������
                 (4.2) RRC�ٴ�ָʾ������½��ϱ�׼��Ϊ���ڱ�������������������
                 ʹ���µ��������ݸ���ԭ�ȵ�����������֮�����������ϱ�������
                 �������

             (5) RRC->PHY: �������㵱ǰ�Ѿ������������������ϱ�׼��Ϊ�¼�����:
                 (5.1) RRC�ٴ�ָʾ������½��ϱ�׼��Ϊ���ڱ�������������������
                 ���ܸ����ڱ���׼�����������������֤ԭ���¼�����׼�����������
                 ����Ӱ�졣֮�����������ϱ����������������ָʾ�����ֱ���׼
                 ��Ĳ��������
                 (5.2) RRC�ٴ�ָʾ������½��ϱ�׼��Ϊ�¼���������������������
                 ʹ���µ��������ݸ���ԭ�ȵ�����������֮�����������ϱ�������
                 �������

             (6) UTRAN->RRC: �ͷ��������������ͷ����������ı���׼��Ϊ�����ϱ�ʱ��
             RRC->PHY: �ͷ�����������usReportCrtr��дΪ�����ϱ�����ָʾ������ͷ�
             ����׼��Ϊ�����ϱ�������������������׼��Ϊ�¼��������������������
             ���У�����Ӱ�졣

             (7) UTRAN->RRC: �ͷ��������������ͷ����������ı���׼��Ϊ�¼��ϱ�ʱ��
             RRC->PHY: �ͷ�����������usReportCrtr��дΪ�¼��ϱ�����ָʾ������ͷ�
             ����׼��Ϊ�¼��ϱ�������������������׼��Ϊ���ڱ������������������
             ���У�����Ӱ�졣

             (8) ĳЩ����£�����D->F״̬ת��ʱ��RRC��Ҫͬʱ�ͷ����е�����������
             ��������׼��Ϊ���ڱ�����¼����������������RRC->PHY: �ͷ�����������
             ��usReportCrtr ��Ϊ"�¼�������"���.

             (9) ����˵��: RRC->PHY�������������ýӿ��е���Ԫ�Ϳտڻ�������һ�£�
             ��Ҫָ�����ǵ�UTRANָʾRRC�½���������������׼��Ϊ����������£�RRC
             ָʾPHY�½���������������׼��Ϊ���ڱ��棬PHY����RRC��ָʾ���в�����
             ��RRC�ϱ����������RRC�յ��ò���������д洢�����������ϱ������ǹ�
             ���������ο�ʹ�á�

*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                               /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16              enMsgID;             /* ԭ������ *//*_H2ASN_Skip*/
    VOS_UINT16                              usOpID;

    PHYITF_MEASURE_COMMAND_ENUM_UINT16      enCommand;
    VOS_UINT16                              usMonitorTrchNum;
    VOS_UINT16                              ausMonitorTrchID[RRC_PHY_MAX_TRCH_NUM];

    VOS_UINT16                              usMeasId;
    PHYITF_QUA_MEAS_RPT_CRTR_ENUM_UINT16    enReportCrtrChoice;    /*����ı�׼*/ /* _H2ASN_IeChoice_Export PHYITF_QUA_MEAS_RPT_CRTR_ENUM_UINT16 */

    union                                                                       /*_H2ASN_Skip*/
    {                                                                           /*_H2ASN_Skip*/
        PHYITF_QUA_PERIODIC_CRITERIA_STRU   stPeriodic;                         /*_H2ASN_Skip*/
        PHYITF_QUA_EVENT_CRITERIA_STRU      stEvent;
        /******************************************************************************************************
            _H2ASN_IeChoice_When        PHYITF_QUA_MEAS_RPT_CRTR_ENUM_UINT16
        ******************************************************************************************************/
    }unCriteria;                                                                /*_H2ASN_Skip*/

}RRC_PHY_QUALITY_MEASUREMENT_REQ_STRU;



/*****************************************************************************
 �ṹ��    : PHY_RRC_QUALITY_MEASUREMENT_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��������֤ʵ��Ϣ���ݽṹ

*****************************************************************************/

typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;            /* ԭ������*/   /*_H2ASN_Skip*/
    VOS_UINT16                          usOpID;

}PHY_RRC_QUALITY_MEASUREMENT_CNF_STRU;



/*****************************************************************************
 �ṹ��    : PHYITF_TRCH_QUA_REPORT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ÿ�������ŵ����������
 *****************************************************************************/

typedef  struct
{
    VOS_UINT16                          usTrCHID;
    VOS_UINT16                          usBLER;

}PHYITF_TRCH_QUA_REPORT_STRU;

/*****************************************************************************
 �ṹ��    : PHYITF_QUALITY_PERIO_REPORT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ������������
 *****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulMonitorTrCHNum;
    PHYITF_TRCH_QUA_REPORT_STRU         astTrCHReport[RRC_PHY_MAX_TRCH_NUM];

}PHYITF_QUALITY_PERIO_REPORT_STRU;

/*****************************************************************************
 �ṹ��    : PHYITF_QUALITY_EVENT_REPORT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �¼���������
 *****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulEventTrCHNum;
    VOS_UINT16                          ausEventTrCHID[RRC_PHY_MAX_TRCH_NUM];

}PHYITF_QUALITY_EVENT_REPORT_STRU;


/*****************************************************************************
 �ṹ��    : PHY_RRC_QUALITY_MEASUREMENT_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��������ָʾ��Ϣ���ݽṹ

*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16              enMsgID;            /* ԭ������ *//*_H2ASN_Skip*/
    VOS_UINT16                              usOpID;
    PHYITF_QUA_MEAS_RPT_IND_ENUM_UINT16     enReportCrtr;       /*����ı�׼*/  /* _H2ASN_IeChoice_Export PHYITF_QUA_MEAS_RPT_IND_ENUM_UINT16 */
    VOS_UINT16                              usMeasId;
    union                                                                       /* _H2ASN_Skip */
    {                                                                           /* _H2ASN_Skip */
        PHYITF_QUALITY_PERIO_REPORT_STRU    stPeriodicReport;                   /* _H2ASN_Skip */
        PHYITF_QUALITY_EVENT_REPORT_STRU    stEventReport;
        /******************************************************************************************************
            _H2ASN_IeChoice_When        PHYITF_QUA_MEAS_RPT_IND_ENUM_UINT16
        ******************************************************************************************************/
    } unReportResult;                                                           /* _H2ASN_Skip */
}PHY_RRC_QUALITY_MEASUREMENT_IND_STRU;


/**************************************��λ�������ݽṹ*******************************/

/*****************************************************************************
 �ṹ��    : PHYITF_POS_BURST_MODE_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ͻ��ģʽ������Ϣ
 *****************************************************************************/

typedef struct
{
    VOS_UINT16                          usBurstStart;
    VOS_UINT16                          usBurstLen;
    VOS_UINT16                          usBurstFreq;
    VOS_UINT16                          usReserve1;

} PHYITF_POS_BURST_MODE_PARA_STRU;

/*****************************************************************************
 �ṹ��    : PHYITF_POS_IPDL_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : IPDL ������Ϣ
 *****************************************************************************/
typedef struct
{
    VOS_UINT16                          usIpSpacing;
    VOS_UINT16                          usIpLen;
    VOS_UINT16                          usIpOffset;
    VOS_UINT16                          usSeed;
    VOS_UINT16                          usReserve1;
    PHYITF_BOOL_ENUM_UINT16             enBurstModeParaValid;
    PHYITF_POS_BURST_MODE_PARA_STRU     stBurstModePara;

} PHYITF_POS_IPDL_PARA_STRU;

/*****************************************************************************
 �ṹ��    : PHYITF_POS_NEIGHBOUR_CELL_SFNSFN_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��С��SFN_SFN��Ķ�λ��Ϣ
 *****************************************************************************/

typedef struct
{
    VOS_INT16                           sSfnSfnDrift;           /*1/256chip per second,[-100,100],0XFF������Ч*/
    VOS_INT16                           sSfnOffset;             /*[-1,0..4095],-1��ʾ��Ч������,��λΪ1֡*/
    VOS_UINT16                          usSfnSfnReltimeDiff;    /*[0..38399] chips,��λΪchip */
    VOS_UINT16                          usSearchWinSize;

    VOS_UINT16                          usReserve1;
    PHYITF_BOOL_ENUM_UINT16             enPosIpdlParaValid;
    PHYITF_POS_IPDL_PARA_STRU           stPosIpdlPara;

}PHYITF_POS_NEIGHBOUR_CELL_SFNSFN_INFO_STRU;


/*****************************************************************************
 �ṹ��    : PHYITF_POS_NEIGHBOUR_CELL_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��С����λ��Ϣ
 *****************************************************************************/

typedef struct
{
    VOS_UINT16                          usPrimScramCode;
    VOS_UINT16                          usFreqInfo;

    /*�����Ƿ���Ҫ����Rx_Tx ʱ���,0:����Ҫ��1:��Ҫ*/
    VOS_UINT16                          usNeedRxTxTimeDiffType2Meas;

    /*�����Ƿ���Ҫ����SFN_SFN �۲�ʱ���,0:����Ҫ��1:��Ҫ*/
    VOS_UINT16                          usNeedSfnSfnObsTimeDiff2Meas;

    /*����Ҫ����SFN_SFN�۲�ʱ���ʱ,stPosNebCellSfnSfnInfo��Ч*/
    PHYITF_POS_NEIGHBOUR_CELL_SFNSFN_INFO_STRU stPosNebCellSfnSfnInfo;

}PHYITF_POS_NEIGHBOUR_CELL_INFO_STRU;



/*****************************************************************************
 �ṹ��    : PHYITF_POS_NEIGHBOUR_CELL_INFO_LIST_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��С���б���Ϣ
 *****************************************************************************/

typedef struct
{
    VOS_UINT16                              usReserve1;
    VOS_UINT16                              usCellNum;
    PHYITF_POS_NEIGHBOUR_CELL_INFO_STRU     astNebCellInfo[RRC_PHY_MAX_POS_CELL_NUM];

 }PHYITF_POS_NEIGHBOUR_CELL_INFO_LIST_STRU ;


/*****************************************************************************
 �ṹ��    : PHYITF_POS_REF_CELL_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �ο�С����Ϣ
 *****************************************************************************/

typedef struct
{
    VOS_UINT16                          usPrimScramCode;
    VOS_UINT16                          usFreqInfo;
    VOS_INT16                           sSfn;   /*-1������Ч*/

    /*�����Ƿ���Ҫ����Rx_Tx ʱ���,0����Ҫ��1��Ҫ*/
    VOS_UINT16                          usNeedRxTxTimeDiffType2Meas;

    VOS_UINT16                          usReserve1;
    PHYITF_BOOL_ENUM_UINT16             enPosIpdlParaValid; /*IPDL�����Ƿ���Ч,0:��Ч��1:��Ч*/
    PHYITF_POS_IPDL_PARA_STRU           stPosIpdlPara;

} PHYITF_POS_REF_CELL_INFO_STRU;


/*****************************************************************************
 �ṹ��    : PHYITF_POS_ASSIST_DATA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��λ��������
 *****************************************************************************/

typedef struct
{
    PHYITF_BOOL_ENUM_UINT16                             enPosRefCellInfoValid;  /*�ο�С����Ϣ�Ƿ���Ч,0:��Ч��1:��Ч*/
    PHYITF_BOOL_ENUM_UINT16                             enPosNeighbCellListValid;/*�����б���Ϣ�Ƿ���Ч,0:��Ч��1:��Ч*/
    PHYITF_POS_REF_CELL_INFO_STRU                       stPosRefCellInfo;       /*��λ�ο�С����Ϣ*/
    PHYITF_POS_NEIGHBOUR_CELL_INFO_LIST_STRU            stPosNeighbCellList;    /*��λ�����б���Ϣ*/

} PHYITF_POS_ASSIST_DATA_STRU;


/*****************************************************************************
 �ṹ��    : RRC_PHY_POSITION_MEASUREMENT_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��λ��������
 *****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                         /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;           /* ԭ������ *//*_H2ASN_Skip*/
    VOS_UINT16                          usOPID;
    PHYITF_MEASURE_COMMAND_ENUM_UINT16  enCommand;         /*0�ͷţ�1����(�����޸�,����������һ��)*/
    VOS_UINT16                          usReserve1;

    VOS_UINT32                          ulRptTimeInterval; /*��λ���������,��λms*/
    PHYITF_POS_ASSIST_DATA_STRU         stPosAssData;      /*��λ�ĸ�������*/

} RRC_PHY_POSITION_MEASUREMENT_REQ_STRU;


/*****************************************************************************
 �ṹ��    : PHY_RRC_POSITION_MEASUREMENT_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��λ����Ӧ����Ϣ���ݽṹ
 *****************************************************************************/

typedef struct
{
    VOS_MSG_HEADER                                         /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;           /* ԭ������ *//*_H2ASN_Skip*/
    VOS_UINT16                          usOPID;

} PHY_RRC_POSITION_MEASUREMENT_CNF_STRU;

/*****************************************************************************
 �ṹ��    : PHYITF_POS_MEAS_QUAL_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��λ��������
 *****************************************************************************/

typedef struct
{
    VOS_UINT16                          usStdResolution;    /*��׼��Ľ�����*/
    VOS_UINT16                          usNumOfMeas;        /*�˴α�׼���Ӧ�˶��ٴβ���*/
    VOS_UINT16                          usStdOfMeas;        /*�����ı�׼��*/
    VOS_UINT16                          usReserve1;

} PHYITF_POS_MEAS_QUAL_STRU;

/*****************************************************************************
 �ṹ��    : PHYITF_REF_CELL_MEAS_RSLT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �ο�С���������
 *****************************************************************************/

typedef struct
{
    VOS_UINT16                          usRefCellScramCode;             /*�ο�С������,0-511*/

    /*��Rx_Txʱ����Ҫ�������������������0.
      [0.. 65535],����㽫RxTxTimeDiffType2�������
      (1/16chip���ȣ��Ŵ�16�����ϱ���Э��ջ,������
      �������1/16chipΪ��λ��*/
    VOS_UINT16                          usRxTxTimeDiffType2Value;
    PHYITF_POS_MEAS_QUAL_STRU           stRxTxTimeDiffType2MeasQual;    /*��Rx_Txʱ����Ҫ�������������������0*/

} PHYITF_POS_REF_CELL_MEAS_RSLT_STRU;

/*****************************************************************************
 �ṹ��    : PHYITF_NEIGHB_CELL_MEAS_RSLT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �����������
 *****************************************************************************/

typedef struct
{
    VOS_UINT16                          usNeignbCellScramCode;          /*��������,0-511*/

    /*��Rx_Txʱ����Ҫ�������������������0.
      [0.. 65535],����㽫RxTxTimeDiffType2�������
      (1/16chip���ȣ��Ŵ�16�����ϱ���Э��ջ,������
      �������1/16chipΪ��λ��*/
    VOS_UINT16                          usRxTxTimeDiffType2Value;
    PHYITF_POS_MEAS_QUAL_STRU           stRxTxTimeDiffType2MeasQual;    /*��Rx_Txʱ����Ҫ�������������������0*/

    VOS_UINT16                          usReserve1;
    VOS_UINT16                          usSfnSfnObsTimeDiff2;           /*��Sfn_Sfn�۲�ʱ����Ҫ�������������������0*/
    PHYITF_POS_MEAS_QUAL_STRU           stSfnSfnObsTimeDiff2MeasQual;   /*��Sfn_Sfn�۲�ʱ����Ҫ�������������������0*/

} PHYITF_POS_NEIGHB_CELL_MEAS_RSLT_STRU;

/*****************************************************************************
 �ṹ��    : PHYITF_POS_NEIGHB_CELLLIST_MEAS_RSLT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �����б�������
 *****************************************************************************/

typedef struct
{

    VOS_UINT16                              usReserve1;
    VOS_UINT16                              usNeighbCellNum;    /*������Ŀ*/
    PHYITF_POS_NEIGHB_CELL_MEAS_RSLT_STRU   astNeighbCellMeasRslt[RRC_PHY_MAX_POS_CELL_NUM];

} PHYITF_POS_NEIGHB_CELLLIST_MEAS_RSLT_STRU ;


/*****************************************************************************
 �ṹ��    : PHYITF_POS_MEAS_RESULT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �������(������Tx_Rx���������SFN_SFN�۲�ʱ���)
             �ο�С�����������Էֱ��ϱ�,Ҳ����һ���ϱ�

 *****************************************************************************/

typedef struct
{

    /*�����ο�С���Ĳ�������Ƿ���Ч,������㲻��Ҫ�����ο�С����
      RxTxTimeDiffType2,���޷��õ��ο�С����RxTxTimeDiffType2ʱ����
      usRefCellMeasValid = 0, ����Ϊ1*/
    PHYITF_BOOL_ENUM_UINT16             enRefCellMeasValid;

    /*���������Ĳ�������Ƿ���Ч,������㲻��Ҫ�������޷��õ�����������
      RxTxTimeDiffType2,��Ҳ����Ҫ�������޷��õ�����������SFN_SFN�Ĳ���ֵ
      ʱ, usNeighbCellMeasListValid = 0, ����Ϊ1*/
    PHYITF_BOOL_ENUM_UINT16             enNeighbCellMeasListValid;

    /*���һ�β���ֵ��SFN*/
    VOS_UINT16                          usSfn;
    VOS_UINT16                          usReserve1;

    /*�ο�С���������*/
    PHYITF_POS_REF_CELL_MEAS_RSLT_STRU              stRefCellMeasRslt;

    /*��С���������*/
    PHYITF_POS_NEIGHB_CELLLIST_MEAS_RSLT_STRU       stNeighbCellListMeasRslt;

} PHYITF_POS_MEAS_RESULT_STRU;


/*****************************************************************************
 �ṹ��    : PHY_RRC_POSITION_MEASUREMENT_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��λ����ָʾ��Ϣ
 *****************************************************************************/

typedef struct
{
    VOS_MSG_HEADER                                       /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16            enMsgID;       /* ԭ������ *//*_H2ASN_Skip*/
    VOS_UINT16                            usOPID;
    PHYITF_POS_MEAS_RESULT_STRU           stPosMeasRslt; /*��λ�������*/

} PHY_RRC_POSITION_MEASUREMENT_IND_STRU;

/*****************************************************************************
 �ṹ��    : PHY_RRC_UE_INTERNAL_MEASUREMENT_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �ڲ�����������ݽṹ
 *****************************************************************************/

typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;            /*_H2ASN_Skip*/   /* ԭ������ */
    VOS_UINT16                          usOPID;             /* ������ʶ */
    PHYITF_INTERNAL_REPORT_STRU         stInternalRpt;
}PHY_RRC_UE_INTERNAL_MEASUREMENT_IND_STRU;

/*==========================================================================
                              HSUPA �ŵ�����
============================================================================*/

/*****************************************************************************
 �ṹ��    : PHYITF_E_AGCH_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : E_AGCH ��Ϣ
 *****************************************************************************/
typedef struct
{
    /*��ʶusPrimERnti�Ƿ���Ч������Ч����enPrimERntiValidΪ1������enPrimERntiValidΪ0*/
    PHYITF_BOOL_ENUM_UINT16             enPrimERntiValid;

    /*��ʶusScndERnti�Ƿ���Ч������Ч����enScndERntiValidΪ1������enScndERntiValidΪ0*/
    PHYITF_BOOL_ENUM_UINT16             enScndERntiValid;

    VOS_UINT16                          usEAgchChlsCode;                        /* INTEGER(0..255) */
    VOS_UINT16                          usPrimERnti;                            /*��E_Rnti,�� enPrimERntiValid Ϊ1ʱ��Ч*/
    VOS_UINT16                          usScndERnti;                            /*��E_Rnti,�� enScndERntiValid Ϊ1ʱ��Ч*/
    VOS_UINT16                          usReserve1;

}PHYITF_E_AGCH_INFO_STRU;


/*****************************************************************************
 �ṹ��    : PHYITF_E_RGCH_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : E_RGCH ����Ϣ
 *****************************************************************************/
typedef struct
{
    VOS_UINT16                          usChlsCode;                             /*  INTEGER(0..127),E_HICH ʹ�õ��ŵ���,
                                                                                    ͬһ����·��E_HICH��E_RGCHʹ�õ��ŵ�����ͬ*/
    PHYITF_BOOL_ENUM_UINT16             enSignSeqValid;                         /* ָʾusSignSeq�Ƿ���� */
    VOS_UINT16                          usSignSeq;                              /* INTEGER(0..39),E_RGCH ʹ�õ�ǩ��*/


    VOS_UINT16                          usERgchCombIndex;                       /* INTEGER(0..5),��·���ϲ�����,ͬһ����·������·��������ͬ��,Ӧ�úϲ�*/
                                                                                /* ����E-RACH��д0 */
}PHYITF_E_RGCH_INFO_STRU;


/*****************************************************************************
 �ṹ��    : PHYITF_E_HICH_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : E_HICH ����Ϣ
 *****************************************************************************/
typedef struct
{
    /*INTEGER(0..127),E_HICH ʹ�õ��ŵ���,ͬһ����·��E_HICH��E_RGCHʹ�õ��ŵ�����ͬ*/
    VOS_UINT16                          usChlsCode;

    /* INTEGER(0..39),E_HICH ʹ�õ�ǩ��*/
    PHYITF_BOOL_ENUM_UINT16             enSignSeqValid;                         /* ָʾusSignSeq�Ƿ���Ч ����Э��10.3.6.123 */
    VOS_UINT16                          usSignSeq;

    /* INTEGER(0..5),��·���ϲ�����,ͬһ����·������·��������ͬ��,Ӧ�úϲ�
       RRC��ÿ��RL ��·�е�DPCH�е�TPC combination index ������ֵ
       E-RACHʱ�̶���д0 */
    VOS_UINT16                          usEHichCombIndex;

}PHYITF_E_HICH_INFO_STRU;


/*****************************************************************************
 �ṹ��    : PHYITF_DL_PER_EDCH_RL_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : HSUPA ������·��Ϣ
 *****************************************************************************/
typedef struct
{

   /*EAgchInfo �Ƿ���Ч������Ч����enEAgchInfoValidΪ1������enEAgchInfoValidΪ0*/
   PHYITF_BOOL_ENUM_UINT16              enEAgchInfoValid;

   /*EHichInfo �Ƿ���Ч������Ч����enEHichInfoValidΪ1������enEHichInfoValidΪ0*/
   PHYITF_BOOL_ENUM_UINT16              enEHichInfoValid;

   /*ERgchInfo �Ƿ���Ч������Ч����enERgchInfoValidΪ1������enERgchInfoValidΪ0*/
   PHYITF_BOOL_ENUM_UINT16              enERgchInfoValid;

   /*ָʾ���С���Ƿ��Ƿ���E_DCHС��*/
   PHYITF_BOOL_ENUM_UINT16              enServingEdchRlInd;

   /*������·�ĵ�Ƶ�ŵ��������룬��ΪĿǰֻ֧������Ƶ�ŵ���
     ����E_HICH,E_AGCH,E_RGCH��ʹ�����������Ϊ�Լ��ŵ�������*/
   VOS_UINT16                           usPrimScramCode;

   VOS_UINT16                           usReserve1;

   PHYITF_E_AGCH_INFO_STRU              stEAgchInfo;                            /* OPTIONAL */
   PHYITF_E_HICH_INFO_STRU              stEHichInfo;                            /* OPTIONAL */
   PHYITF_E_RGCH_INFO_STRU              stERgchInfo;                            /* OPTIONAL */


}PHYITF_DL_PER_EDCH_RL_STRU;

/*****************************************************************************
 �ṹ��    : PHYITF_DL_PER_EDCH_RL_LIST_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : HSUPA ������·�б���Ϣ
             ������EDCH ��·�ͷ�EDCH��·
 *****************************************************************************/
typedef struct
{

   /*ָʾEDCH ����С���Ƿ���,0:�����,1���*/
   VOS_UINT16                           usEServCellChangeInd;

   /*
     ��EDCH ����С��������µ�EDCH����С��������ԭ����EDCH RLSʱ,
     Ӧ�ô���Scheduling Information.
     usEServCellChangeTrigSiInd ָʾ�Ƿ�Ӧ�ô���SI,0:������,1����
     ���ͬʱ����RL SETUP��RL MODIFY������¸�ָʾ������ԭ���ж�ͬʱ����
   */
   VOS_UINT16                           usEServCellChangeTrigSiInd;

   VOS_UINT16                           usDlFreqInfo;                   /* ����Ƶ�㣬INTEGER(0..16383) */

   VOS_UINT16                           usFreqBandNo;                   /* Ƶ�κ�*/
   VOS_UINT16                           usTxRxFreqSeparation;           /* �շ�Ƶ��*/

   VOS_UINT16                           usCnt;
   PHYITF_DL_PER_EDCH_RL_STRU           astDlPerEdchRl[RRC_PHY_MAX_RL_NUM];

}PHYITF_DL_PER_EDCH_RL_LIST_STRU;

/*V3 R7_7C1 Start */
/*****************************************************************************
 �ṹ��    : PHYITF_E_TFC_BOOST_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : E_TFC_BOOST_INFO �ŵ���Ϣ

 *****************************************************************************/

typedef struct
{
    VOS_UINT16                          usDeltaT2Tp;   /* INTEGER(0..6)  OPTIONAL  Ĭ������0 */

    VOS_UINT16                          usETfciBoost;  /* INTEGER(0..127)  Ĭ������127 */

}PHYITF_E_TFC_BOOST_INFO_STRU;
/* V3 R7_7C1 End */

/*****************************************************************************
 �ṹ��    : PHYITF_E_DPCCH_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : HSUPA ����EDPCCH �ŵ���Ϣ

 *****************************************************************************/
typedef struct
{
    /* INTEGER(0..8) */
    VOS_UINT16                          usEDpcchDpcchPwrOffset;

    /* HappyBit ��ʱ�о� */
    VOS_UINT16                          usHappyBitDelayCondi;
    /* EDpdchPwrInterpolation �Ƿ���Ч 0��ʾ��Ч 1��ʾ��Ч  ����տ�û������Ĭ������0*/
    VOS_UINT16                          usEDpdchPwrInterpolation;

    VOS_UINT16                          usResrve1;

    PHYITF_E_TFC_BOOST_INFO_STRU        stETfcBoostInfo;
}PHYITF_E_DPCCH_INFO_STRU;


/*****************************************************************************
 �ṹ��    : PHYITF_E_DPDCH_SCHEDUL_TRANSM_CFG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : HSUPA ������Ȩ��Ϣ

 *****************************************************************************/
typedef struct
{

    /* INTEGER(0..38) */
    VOS_UINT16                          usValue;

    /* ������Ȩѡ��,0ѡ������,1ѡ�񸨵�*/
    VOS_UINT16                          usPrimScndGrantSelect;                  /* E-RACHʱ���粻Я������д0 */

}PHYITF_E_DPDCH_SCHEDUL_TRANSM_CFG_STRU;

/*****************************************************************************
 �ṹ��    : PHYITF_E_DPDCH_REF_E_TFCI_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : HSUPA ����EDPDCH �ο�E_TFCI��Ӧ��Power Offset
             ���ڼ��㹦��
 *****************************************************************************/
typedef struct
{
    /* INTEGER(0..127),�ο�E_TFCI*/
    VOS_UINT16                          usRefETfci;

    /* INTEGER(0..29),�ο�E_TFCI ��Ӧ��Power Offset*/
    VOS_UINT16                          usRefETfciPo;

}PHYITF_E_DPDCH_REF_E_TFCI_STRU;

/*****************************************************************************
 �ṹ��    : PHYITF_E_DPDCH_REF_E_TFCI_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : HSUPA ����EDPDCH �ο�E_TFCI�б�
 *****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulCnt;
    PHYITF_E_DPDCH_REF_E_TFCI_STRU      astDpdchRefETfci[RRC_PHY_MAX_EDCH_REFTFCI_NUM];

}PHYITF_E_DPDCH_REF_E_TFCI_LIST_STRU;


/*****************************************************************************
 �ṹ��    : PHYITF_E_DPDCH_SCHED_INFO_CONFIG_STRU
 Э����  : 10.3.6.99    E-DPDCH Info
                        Scheduling Information Configuration
 ASN.1���� : E_DPDCH_SchedulingInfoConfiguration
 �ṹ˵��  : ������Ϣ
             NOTE:If the Periodicity is set to 4ms and the E-DCH TTI
             is set to 10ms, the UE shall interpret the periodicity value as 10ms.
*****************************************************************************/
typedef struct
{
    /*����EDCH TTI=10ms,��RNC ����usNoGrantPeriodic=4msʱ,RRCȡusNoGrantPeriodicΪ10ms��������*/
    VOS_UINT16                          usNoGrantPeriodic;  /* ��λms, (everyEDCHTTI = 0xffff,4,10,20,50,100,200,500,1000),Default value is "no report"��0��ʾ */

    /*����EDCH TTI=10ms,��RNC ����usGrantPeriodic=4msʱ,RRCȡusGrantPeriodicΪ10ms��������*/
    VOS_UINT16                          usGrantPeriodic;    /* ��λms, (everyEDCHTTI = 0xffff,4,10,20,50,100,200,500,1000),Default value is "no report"��0��ʾ */
    VOS_UINT16                          usSIPowOffset;      /* [0,6] */
    VOS_UINT16                          usReserve1;         /* 4�ֽڶ��룬���� */

}PHYITF_E_DPDCH_SCHED_INFO_CONFIG_STRU;

/*****************************************************************************
 �ṹ��    : PHYITF_E_DPDCH_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : HSUPA ����EDPDCH ��Ϣ
 *****************************************************************************/
typedef struct
{
    VOS_UINT16                                          usETfciTableIndex;      /* INTEGER(0..1) */

    /*usEDchMinSetETfci �Ƿ���Ч������Ч����enEDchMinSetETfciValidΪ1������enEDchMinSetETfciValidΪ0*/
    PHYITF_BOOL_ENUM_UINT16                             enEDchMinSetETfciValid;
    VOS_UINT16                                          usEDchMinSetETfci;      /* INTEGER(0..127)  OPTIONAL */

    PHYITF_MIN_REDUC_E_DPDCH_GAIN_FACTOR_ENUM_UINT16    enMinReducEDpdchGainFactor; /* ���ʻ������ӣ���Я��ʱʹ��Ĭ��ֵ8/15*/

    VOS_UINT16                                          usThreeIndexStepThresh; /* INTEGER(0..37)  OPTIONAL */
    VOS_UINT16                                          usTwoIndexStepThresh;   /* INTEGER(0..37)  OPTIONAL */
    PHYITF_E_DPDCH_MAX_CHLS_CODES_ENUM_UINT16           enMaxChlsCodes;         /* ENUMERATED,ȡֵPHYITF_MAX_CHLSCODES_ENUM�е�ֵ*/
    VOS_UINT16                                          usPlNonMax;             /* INTEGER(11..25) */

    PHYITF_E_DPDCH_REF_E_TFCI_LIST_STRU                 stRefETfcIs;

    PHYITF_E_DPDCH_SCHED_INFO_CONFIG_STRU               stSchedInfoConfig;


}PHYITF_E_DPDCH_INFO_STRU;

/*****************************************************************************
 �ṹ��    : PHYITF_UL_16QAM_CONFIG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
 *****************************************************************************/
typedef struct
{
    PHYITF_BOOL_ENUM_UINT16                 enUl16QamSetting;                   /*�Ƿ�����16QAM,0:��Ч;1:��Ч*/
    VOS_UINT16                              usBetaEdGainEAgchTableSelection;    /* ȡֵ0����1 */
}PHYITF_UL_16QAM_CONFIG_STRU;

/*****************************************************************************
 �ṹ��    : PHYITF_UL_EDCH_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : EDCH ������Ϣ
 *****************************************************************************/
typedef struct
{
    /*���ȴ��� stSchedulTransmCfg �Ƿ���Ч,����Ч����enSchedulTransmValidΪ1������enSchedulTransmValidΪ0*/
    PHYITF_BOOL_ENUM_UINT16                 enSchedulTransmValid;

    VOS_UINT16                              usReserve1;

    /* E_Dpcch��Ϣ */
    PHYITF_E_DPCCH_INFO_STRU                stEDpcchInfo;

    /* E_Dpdch��Ϣ*/
    PHYITF_E_DPDCH_INFO_STRU                stEDpdchInfo;

    /* OPTIONAL�����ȴ�����Ϣ*/
    PHYITF_E_DPDCH_SCHEDUL_TRANSM_CFG_STRU  stSchedulTransmCfg;
    VOS_UINT16                              us2msSchedGrantProcAlloc;           /*BITMAP,2ms TTI,������Ȩ��������,��MAC-d��������
                                                                                ֻ����BITλȡֵΪ1�Ľ����Ϸ���,Bit0��Ӧ����7��Bit1��Ӧ����6���Դ�����...
                                                                                ���粻Я����ʾȫѡ��Default value is: transmission in all HARQ processes is allowed.*/
    VOS_UINT16                              usReserve2;
    PHYITF_UL_16QAM_CONFIG_STRU             stUl16QamConfig;
}PHYITF_UL_EDCH_INFO_STRU;



/*****************************************************************************
 �ṹ��    : PHYITF_MAC_E_NON_SCHED_GRANT_STRU
 Э����  : 10.3.5.1b    Added or reconfigured E-DCH MAC-d flow
 ASN.1���� : transmissionGrantType
 �ṹ˵��  : �ǵ�����Ȩ
*****************************************************************************/
typedef struct
{
    /* */
    VOS_UINT16                          usEFlowMaxMacEPduSize;          /* [1...19982] bit */

    /* BITMAP,2ms TTI,�ǵ�����Ȩ�������ã�
       bitλֵΪ1ʱ������Ч��Bit 0 corresponds to HARQ process 0, bit 1 corresponds to HARQ process 1...
     ���粻Я������ʾȫ�䣬Default value is: transmission in all HARQ processes is allowed.
     Bit 0 is the first/leftmost bit of the bit string.*/
    VOS_UINT16                          us2msNonSchedGrantProcAlloc;

}PHYITF_MAC_E_NON_SCHED_GRANT_STRU ;

/*****************************************************************************
 �ṹ��    : PHYITF_MAC_EFLOW_TRANS_GRANT_INFO_STRU
 Э����  : 10.3.5.1b    Added or reconfigured E-DCH MAC-d flow
 ASN.1���� : transmissionGrantType
             E_DPDCH_SchedulingTransmConfiguration
             ms2_SchedTransmGrantHARQAlloc
 �ṹ˵��  : E DCH��������
*****************************************************************************/
typedef struct
{
    PHYITF_MAC_E_SCHED_GRANT_INFO_CHOSEN_ENUM_UINT16 enChoice;  /* _H2ASN_IeChoice_Export PHYITF_MAC_E_SCHED_GRANT_INFO_CHOSEN_ENUM_UINT16 */
    VOS_UINT16                                       usReserved1;

    union                                                                       /*_H2ASN_Skip*/
    {                                                                           /*_H2ASN_Skip*/
        PHYITF_MAC_E_NON_SCHED_GRANT_STRU    stNonSchedGrant;                   /*_H2ASN_Skip*//*ֻ�е�enChoice��0ʱ���ýṹ����Ч��*/
        VOS_UINT32                           ulReserved;
        /******************************************************************************************************
            _H2ASN_IeChoice_When        PHYITF_MAC_E_SCHED_GRANT_INFO_CHOSEN_ENUM_UINT16
        ******************************************************************************************************/
    }u;                                                                         /*_H2ASN_Skip*/
}PHYITF_MAC_EFLOW_TRANS_GRANT_INFO_STRU;

/*****************************************************************************
 �ṹ��    : PHYITF_MAC_EDCH_FLOW_STRU
 Э����  : 10.3.5.1b    Added or reconfigured E-DCH MAC-d flow
 ASN.1���� : E_DCH_AddReconf_MAC_d_Flow
 �ṹ˵��  : E DCH��������
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usEFlowId;                  /* [0,7] */
    VOS_UINT16                              usEFlowPwrOffset;           /* [0,6],dB ������ʱ������ܲ�Я��������WAS�̶����ø�PHY */
    VOS_UINT16                              usEFlowMaxReTrans;          /* [0,15] ������ʱ������ܲ�Я��������WAS�̶����ø�PHY*/
    VOS_UINT16                              usEFlowMuxlist;             /* BITMAP,Bit0��ӦMAC-d��0��Bit1��ӦMAC-d��1��
                                                                       �Դ����ƣ�BITֵΪ1������Ӧ��MAC-d�������뵱ǰMAC-d��������ͬһMAC-e PDU�з���;
                                                                       �������ȫ0����ʾû�и��� */
    PHYITF_MAC_EFLOW_TRANS_GRANT_INFO_STRU  stEFlowTransGrantInfo;      /* Only allowed to be absent when already defined for this E-DCH MAC-d flow
                                                                       WASÿ�ζ����ø�MAC */
}PHYITF_MAC_EDCH_FLOW_STRU;


/*****************************************************************************
 �ṹ��    : PHYITF_MAC_EDCH_FLOWLIST_STRU
 Э����  : 10.3.5.1b    Added or reconfigured E-DCH MAC-d flow
 ASN.1���� : E_DCH_AddReconf_MAC_d_FlowList
 �ṹ˵��  : E DCH��������
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usReserve1;
    VOS_UINT16                          usEdchFlowCnt;                                   /* FLOW�ĸ��� */
    PHYITF_MAC_EDCH_FLOW_STRU           astEdchFlow[RRC_PHY_MAC_EDCH_MAX_MACD_FLOW_NUM]; /* ÿ��Edch Flow����Ϣ */

}PHYITF_MAC_EDCH_FLOW_LIST_STRU;

/* MOD UL_E_L2 BEGIN */
/*****************************************************************************
 �ṹ��    : PHYITF_RLC_PDU_SIZE_FIXED_STRU
 Э����  :
 ASN.1���� :  ASN.1 �ı� : RLC_PDU_SizeList
 �ṹ˵��  : RLC SIZE
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usDdi;                                  /* [0,62],MAC_Iʵ���ʱ�����ֵWDSP�ǲ�ʹ�õ� */
    VOS_UINT16                          usRlcSizeCnt;                           /* [0,31] */
    VOS_UINT16                          ausRlcSize[RRC_PHY_MAX_RLC_PDU_SIZE_NUM_PER_LOCH];/* [16,5000],by step of 8 */
}PHYITF_RLC_PDU_SIZE_FIXED_STRU;

/*****************************************************************************
 �ṹ��    : PHYITF_RLC_PDU_SIZE_FLEX_STRU
 Э����  :
 ASN.1���� : ASN.1 �ı� : RLC-PDU-SizeConstraint
 �ṹ˵��  : RLC_PDU�ɱ�SIZE�Ĳ���
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usReserve1;
    PHYITF_RLC_PDU_SIZE_LI_SIZE_ENUM_UINT16 enLenIndSize;                       /* ENUMERATED  OPTIONAL��������ʱ��дBUTT */
    VOS_UINT16                              usMinRlcPduSize;                    /* Integer (16..12040 by step of 8) */
    VOS_UINT16                              usLargestRlcPduSize;                /* Integer (16..12040 by step of 8) */
}PHYITF_RLC_PDU_SIZE_FLEX_STRU;

/*****************************************************************************
 �ṹ��    : PHYITF_LOCH_MAPP_RLC_PDU_SIZE_STRU
 Э����  :
 ASN.1���� : UL_LogicalChannelMapping_r6
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                  usReserve1;

    #define    PHYITF_RLC_PDU_SIZE_FIXED_SIZE   0                               /* Fixed size */
    #define    PHYITF_RLC_PDU_SIZE_FLEX_SIZE    1                               /* Flexible size */

    VOS_UINT16                                  usChoice;

    union
    {
        PHYITF_RLC_PDU_SIZE_FIXED_STRU          stFixedSize;                    /* Fixed size */
        PHYITF_RLC_PDU_SIZE_FLEX_STRU           stFlexSize;                     /* Flexible Size */
    }u;

}PHYITF_LOCH_MAPP_RLC_PDU_SIZE_STRU;
/* MOD UL_E_L2 END */


/*****************************************************************************
 �ṹ��    : PHYITF_MAC_EDCH_LOCH_STRU
 Э����  : 10.3.4.21  RB mapping info
 ASN.1���� : UL_LogicalChannelMapping_r6
 �ṹ˵��  : EDCH�߼��ŵ��봫���ŵ��Ķ�Ӧ��ϵ���Լ��߼��ŵ����õ�RLC SIZE
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usLochLabel;        /* �߼��ŵ��ڲ�ʵ��ͳһ��ʶ��[1*2+0,32*2+1],RB ID��Χ:[1..32] */
    VOS_UINT16                          usLochId;           /* INTEGER(1..15),0��ʾ��Ч */
    VOS_UINT16                          usEdchMacdFlowId;   /* [0,7] */
    VOS_UINT16                          usIncludeInSIInd;   /* ָʾ�ڴ���Schedule Information Reportʱ,�Ƿ�Ӧ�ÿ��Ǹ��߼��ŵ�,0:������,1:����
                                                               E-RACH��Я����д0 */

    VOS_UINT16                          usLochPrio;         /* �߼��ŵ����ȼ���[1,8] */
    PHYITF_LOCH_MAPP_RLC_PDU_SIZE_STRU  stRlcPduSize;       /* RLC PDU SIZE,CCCHʱ����д */
    PHYITF_LOCH_DATA_TYPE_ENUM_UINT16   enLochDataType;     /* ָʾ��LOCH��Ӧ��RB���������� */

}PHYITF_MAC_EDCH_LOCH_STRU;


/*****************************************************************************
 �ṹ��    : PHYITF_MAC_EDCH_LOCH_LIST_STRU

 �ṹ˵��  : E DCH�߼��ŵ��б������
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usReserve1;
    VOS_UINT16                          usEdchLochCnt;                              /*��1��RRC_PHY_MAC_EDCH_MAX_LOCH_NUM�� Edch �߼��ŵ��ĸ��� */
    PHYITF_MAC_EDCH_LOCH_STRU           astMacEdchLoch[PS_WUE_MAX_E_DCH_LOCH_NUM];  /* ÿ��Edch �߼��ŵ�����Ϣ */

}PHYITF_MAC_EDCH_LOCH_LIST_STRU;



/*****************************************************************************
 �ṹ��    : PHYITF_UL_HSUPA_PHY_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : UL HSUPA ��Ϣ
 *****************************************************************************/
typedef struct
{

    PHYITF_PHYCH_TYPE_ENUM_UINT16       enPhyChannelType;  /*64*/               /* _H2ASN_Skip */
    VOS_INT16                           sActiveTime;                            /*�����ʱ��CFN,-1��ʾ��������,�����ʾ�����CFN*/
    PHYITF_EDCH_TTI_ENUM_UINT16         enEDCHTTI;                              /*Edch TTI ,ö�� 0:10ms or 1:2ms*/
    PHYITF_RVVERSION_ENUM_UINT16        enRVVersion;                            /*RV �汾��,ENUMERATED,ȡֵ PHYITF_RVVERSION_ENUM 0 ��ʾʹ��RV0,1��ʾʹ��RVTable */

    PHYITF_UL_EDCH_INFO_STRU            stUlEdchInfo;                           /*����Edch ��Ϣ*/

}PHYITF_UL_HSUPA_PHY_STRU;


/*****************************************************************************
 �ṹ��    : PHYITF_DL_HSUPA_PHY_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : DL HSUPA ��Ϣ
 *****************************************************************************/
typedef struct
{

    PHYITF_PHYCH_TYPE_ENUM_UINT16       enPhyChannelType;  /*128*/               /* _H2ASN_Skip */

    VOS_INT16                           sActiveTime;                            /*�����ʱ��CFN,-1��ʾ��������,�����ʾ�����CFN*/

    PHYITF_DL_PER_EDCH_RL_LIST_STRU     stDlRLInfo;                             /*����RL ��Ϣ,��DlRLInfo��λʱ��Ч*/

}PHYITF_DL_HSUPA_PHY_STRU;

/*****************************************************************************
 �ṹ��    : PHYITF_MAC_E_CFG_MODE_ENUM
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MAC-E���÷�ʽ
 *****************************************************************************/
enum    PHYITF_MAC_CFG_MODE_ENUM
{

    PHYITF_MAC_SETUP                     = 0,                         /* �½� */
    PHYITF_MAC_MODIFY                    = 1,                         /* ���� */
    PHYITF_MAC_REVERT                    = 2,                         /* ���˾����� */
    PHYITF_MAC_CFG_BUTT
};
typedef VOS_UINT16  PHYITF_MAC_CFG_MODE_ENUM_UINT16;

/*****************************************************************************
 �ṹ��    : RRC_PHY_MACE_CONFIG_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : HSUPA MACE ��������
 *****************************************************************************/
typedef   struct
{
    VOS_MSG_HEADER /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                          usOPID;                 /* ������ʶ */
    VOS_INT16                           sActiveTime;            /* ����ʱ�� */
    PHYITF_MAC_CFG_MODE_ENUM_UINT16     enMacECfgMode;          /*  MAC-E ���÷�ʽ */
    PHYITF_MAC_EDCH_FLOW_LIST_STRU      stMacEdchFlowList;      /* Mac Edch Flow List Info*/
    PHYITF_MAC_EDCH_LOCH_LIST_STRU      stMacEdchLochList;      /* Mac Edch Loch List Info*/

}RRC_PHY_MACE_CONFIG_REQ_STRU;


/*****************************************************************************
 �ṹ��    : PHY_RRC_MACE_CONFIG_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : HSUPA MACE ����Ӧ��
 *****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16                enMsgID;          /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                usOPID;           /* ������ʶ */
    PHYITF_CHANNEL_CONFIG_RESULT_ENUM_UINT16  enIndicator;      /* ���ý��,0����ɹ�����������ʧ��*/
    VOS_UINT16                                usReserve1;

}PHY_RRC_MACE_CONFIG_CNF_STRU;


/*****************************************************************************
 �ṹ��    : RRC_PHY_MACE_RELEASE_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : HSUPA MACE �ͷ�����
 *****************************************************************************/
typedef   struct
{
    VOS_MSG_HEADER /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                          usOPID;                 /* ������ʶ */
    VOS_INT16                           sActiveTime;            /* ����ʱ�� */
    VOS_UINT16                          usReserve1;             /* �ֽڶ���*/

}RRC_PHY_MACE_RELEASE_REQ_STRU;

/*****************************************************************************
 �ṹ��    : PHY_RRC_MACE_RELEASE_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : HSUPA MACE �ͷ�Ӧ��
 *****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16                enMsgID;          /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                usOPID;           /* ������ʶ */
    PHYITF_CHANNEL_CONFIG_RESULT_ENUM_UINT16  enIndicator;      /* ���ý��,0����ɹ�����������ʧ��*/
    VOS_UINT16                                usReserve1;

}PHY_RRC_MACE_RELEASE_CNF_STRU;

/*****************************************************************************
 �ṹ��    : RRC_PHY_MAC_E_I_RESET_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : HSUPA MACE �ؽ�ָʾ
 *****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16                enMsgID;          /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                usOPID;           /* ������ʶ */
    VOS_INT16                                 sActiveTime;      /* ����ʱ�� */
    PHYITF_MAC_E_I_RESET_TYPE_ENUM_UINT16     enResetType;      /* �ؽ����� */
}RRC_PHY_MAC_E_I_RESET_REQ_STRU;

/*****************************************************************************
 �ṹ��    : PHY_RRC_MAC_E_I_RESET_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : HSUPA MACE �ؽ�ָʾ��Ӧ
 *****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16                enMsgID;          /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                usOPID;           /* ������ʶ */
    PHYITF_CHANNEL_CONFIG_RESULT_ENUM_UINT16  enIndicator;      /* ���ý��,0����ɹ�����������ʧ��*/
    VOS_UINT16                                usReserve1;

}PHY_RRC_MAC_E_I_RESET_CNF_STRU;

/*V3 R7_7C1 Start */
/*****************************************************************************
 �ṹ��    : RRC_PHY_MACHS_RESET_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : HSDPA MACHS �� MACEHS �ؽ�ָʾ
 *****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16                enMsgID;          /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                usOPID;           /* ������ʶ */
    VOS_INT16                                 sActiveTime;      /* ����ʱ�� */
    PHYITF_MAC_RESET_TYPE_ENUM_UINT16         enResetType;      /* �ؽ����� */
}RRC_PHY_MACHS_RESET_REQ_STRU;

/*****************************************************************************
 �ṹ��    : PHY_RRC_MACHS_RESET_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : HSDPA MACHS �� MACEHS �ؽ�ָʾ��Ӧ
 *****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16                enMsgID;          /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                usOPID;           /* ������ʶ */
    PHYITF_CHANNEL_CONFIG_RESULT_ENUM_UINT16  enIndicator;      /* ���ý��,0����ɹ�����������ʧ��*/
    VOS_UINT16                                usReserve1;
}PHY_RRC_MACHS_RESET_CNF_STRU;
/* V3 R7_7C1 End */


/* ADD UL_E_L2 BEGIN */
/*****************************************************************************
 �ṹ��    : RRC_PHY_MACI_CONFIG_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MAC_I���������
 *****************************************************************************/
typedef  struct
{
    VOS_MSG_HEADER /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                          usOPID;                 /* ������ʶ */
    VOS_INT16                           sActiveTime;            /* ����ʱ�� */
    PHYITF_MAC_CFG_MODE_ENUM_UINT16     enMacICfgMode;          /* MAC-I ���÷�ʽ */
    PHYITF_TSN_BIT_LEN_ENUM_UINT16      enTsnBitLen;            /* DCHSUPAʱ����14bit,����Ϊ6bit */
    VOS_UINT16                          usReserve1;             /* ���ֽڶ��� */
    PHYITF_MAC_EDCH_FLOW_LIST_STRU      stMacEdchFlowList;      /* Mac Edch Flow List Info*/
    PHYITF_MAC_EDCH_LOCH_LIST_STRU      stMacEdchLochList;      /* Mac Edch Loch List Info*/

}RRC_PHY_MACI_CONFIG_REQ_STRU;

/*****************************************************************************
 �ṹ��    : PHY_RRC_MACI_CONFIG_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : HSUPA MACI ����Ӧ��
 *****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16                enMsgID;          /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                usOPID;           /* ������ʶ */
    PHYITF_CHANNEL_CONFIG_RESULT_ENUM_UINT16  enIndicator;      /* ���ý��,0����ɹ�����������ʧ��*/
    VOS_UINT16                                usReserve1;
}PHY_RRC_MACI_CONFIG_CNF_STRU;

/*****************************************************************************
 �ṹ��    : RRC_PHY_MACI_RELEASE_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : HSUPA MACI �ͷ�����
 *****************************************************************************/
typedef   struct
{
    VOS_MSG_HEADER /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                          usOPID;                 /* ������ʶ */
    VOS_INT16                           sActiveTime;            /* ����ʱ�� */
    VOS_UINT16                          usReserve1;             /* �ֽڶ���*/
}RRC_PHY_MACI_RELEASE_REQ_STRU;

/*****************************************************************************
 �ṹ��    : PHY_RRC_MACI_RELEASE_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : HSUPA MACI �ͷ�Ӧ��
 *****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16                enMsgID;          /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                usOPID;           /* ������ʶ */
    PHYITF_CHANNEL_CONFIG_RESULT_ENUM_UINT16  enIndicator;      /* ���ý��,0����ɹ�����������ʧ��*/
    VOS_UINT16                                usReserve1;

}PHY_RRC_MACI_RELEASE_CNF_STRU;
/* ADD UL_E_L2 END */


/*****************************************************************************
 �ṹ��    : PHY_RRC_MAC_ACTIVATE_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : HSUPA MACE ���ü���ָʾ
 *****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16                enMsgID;          /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                usOPID;           /* ������ʶ */
    VOS_UINT16                                usCFN;            /* ������Ч��CFN */
    PHYITF_CHANNEL_CONFIG_RESULT_ENUM_UINT16  enIndicator;      /* ���ý��,0����ɹ�����������ʧ��*/
/*V3 R7_7C1 Start */
}PHY_RRC_MAC_ACTIVATE_IND_STRU;
/* V3 R7_7C1 End */

/*****************************************************************************
 �ṹ��    : PHYITF_DL_SCND_CELL_INFO_NEW_CFG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : Downlink secondary cell info FDD����
 *****************************************************************************/
typedef struct
{
    VOS_UINT16                                  usDlFreqInfo;                   /* ���ز�����Ƶ�㣬INTEGER(0..16383) */
    VOS_UINT16                                  usPrimScramCode;                /* ������ */
    VOS_UINT16                                  usSecondScramCode;              /* �����룬INTEGER(1..15)  OPTIONAL ,�����벻������д0 */
    VOS_UINT16                                  usNewHRnti;

    PHYITF_64QAM_CONFIGURED_ENUM_UINT16         enDl64QAMConfig;                /* HS DSCH�ŵ��Ƿ�ʹ��64QAM */
    PHYITF_HSDSCH_TB_SIZE_TABLE_ENUM_UINT16     enHsDschTbSizeTable;            /* HsDsch TB table ʹ��ģʽ */

    VOS_INT16                                   sMeasPwrOffset;                 /* INTEGER(-12..26) */
    PHYITF_BOOL_ENUM_UINT16                     enDiffTxModeFromServHsDschCell; /* TRUE:different;FALSE:not include */

    PHYITF_HS_SCCH_CODE_STRU                    stHsScchCodeInfo;               /* HS_SCCH ʹ�õ��ŵ�����Ϣ */
    PHYITF_HARQ_INFO_STRU                       stHarqInfo;                     /* HARQ INFO,������С����HARQ INFO�õ� */

}PHYITF_DL_SCND_CELL_INFO_NEW_CFG_STRU;

/*****************************************************************************
 �ṹ��    : PHYITF_SCND_HSDPAPLUS_PHY_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : DC HSDPA���ò���
*****************************************************************************/
typedef struct
{
    PHYITF_PHYCH_TYPE_ENUM_UINT16                   enPhyChannelType;           /* 514 */ /* _H2ASN_Skip */
    VOS_INT16                                       sActiveTime;                /*�����ʱ��CFN,-1��ʾ��������*/

    VOS_UINT16                                      usTsnBitNum;                /* 6�� TSN����Ϊ6bit��14��TSN����Ϊ14bit; DC+MIMOʹ��14bit*/

    PHYITF_DL_SCND_CELL_INFO_CFG_INFO_ENUM_UINT16   enDlScndCellInfoCfgInfo;
    PHYITF_DL_SCND_CELL_INFO_NEW_CFG_STRU           stDlScndCellInfo;

    PHYITF_BOOL_ENUM_UINT16                         enNeedRevertOrder;          /* �Ƿ���Ҫ����HS_SCCH order,Ӧ�ó����л�ʧ�ܻ���,SCND_RL_SETUPʱ�ſ�����дPS_TRUE */

    PHYITF_BOOL_ENUM_UINT16                         enMimoParamsValid;          /* ָʾMIMO PARAMS�Ƿ���Ч */
    PHYITF_MIMO_PARAMS_STRU                         stMimoParams;
}PHYITF_SCND_HSDPAPLUS_PHY_STRU;
/*****************************************************************************
 �ṹ��    : ID_RRC_PHY_UPLINK_TRCH_CODEC_MAPPING_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����ҵ�����д����ŵ���AMR����ӳ���ϵ������Ϣ��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                         /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;           /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;            /* ����ID */
    VOS_INT16                           sActiveTime;      /* ����ʱ��[-1,255]ms  -1Ϊ�������� */
    VOS_UINT16                          ausUplinkTrchId[RRC_PHY_MAX_AMR_TRCH_NUM];/* [1,32]AMR��ABC�����ֱ��Ӧ�����д����ŵ��ţ�0xffff��ʾ���������������� */
} RRC_PHY_UPLINK_TRCH_CODEC_MAPPING_REQ_STRU;

/*****************************************************************************
 �ṹ��    : ID_PHY_RRC_UPLINK_TRCH_CODEC_MAPPING_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����ҵ�����д����ŵ���AMR����ӳ���ϵ���õ�CNF��Ϣ��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16               enMsgID;           /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                               usOpId;            /* ����ID */
    PHYITF_CHANNEL_CONFIG_RESULT_ENUM_UINT16 enRslt;            /* ���ý�� */
    VOS_UINT16                               usReserved;
} PHY_RRC_UPLINK_TRCH_CODEC_MAPPING_CNF_STRU;

/*****************************************************************************
 �ṹ��    : ID_RRC_PHY_DNLINK_TRCH_CODEC_MAPPING_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����ҵ�����д����ŵ���AMR����ӳ���ϵ������Ϣ��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                         /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;           /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;            /* ����ID */
    VOS_INT16                           sActiveTime;      /* ����ʱ��[-1,255]ms  -1Ϊ�������� */
    VOS_UINT16                          ausDnlinkTrchId[RRC_PHY_MAX_AMR_TRCH_NUM];/* [1,32]AMR��ABC�����ֱ��Ӧ�����д����ŵ��ţ�0xffff��ʾ���������������� */
} RRC_PHY_DNLINK_TRCH_CODEC_MAPPING_REQ_STRU;

/*****************************************************************************
 �ṹ��    : ID_PHY_RRC_DNLINK_TRCH_CODEC_MAPPING_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����ҵ�����д����ŵ���AMR����ӳ���ϵ���õ�CNF��Ϣ��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16               enMsgID;           /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                               usOpId;            /* ����ID */
    PHYITF_CHANNEL_CONFIG_RESULT_ENUM_UINT16 enRslt;            /* ���ý�� */
    VOS_UINT16                               usReserved;
} PHY_RRC_DNLINK_TRCH_CODEC_MAPPING_CNF_STRU;

/*****************************************************************************
 �ṹ��    : PHYITF_DTX_E_DCH_TTI_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : edch dtx����
*****************************************************************************/
typedef struct
{
    VOS_UINT16                  usUeDtxCyc1;                                  /*  Units of subframes*/
    VOS_UINT16                  usUeDtxCyc2;                                  /*  Units of subframes*/
    VOS_UINT16                  usMacDtxCyc;                                  /*  Units of subframes*/
    VOS_UINT16                  usReserved;
} PHYITF_DTX_E_DCH_TTI_STRU;

/*****************************************************************************
 �ṹ��    : PHYITF_DTX_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : DTX����
*****************************************************************************/
typedef struct
{

    VOS_UINT16                          usReserved1;
    PHYITF_EDCH_TTI_ENUM_UINT16         enDtxEdchTti;                           /* edch tti */
    PHYITF_DTX_E_DCH_TTI_STRU           stDtxEdchTti;

    VOS_UINT16                          usUeDtxCycle2InactThresh;              /* Units of E-DCH TTIs.Enumerated (1, 4, 8, 16, 32, 64, 128, 256) */

    VOS_UINT16                          usUeDtxCycle2DefaultSg;                /* ����������Ϊ0XFFFF,INTEGER(0..38)  OPTIONAL */

    VOS_UINT16                          usUeDtxLongPrbLen;                     /*Units of slots�� Enumerated (4, 15)��default 2 */
    VOS_UINT16                          usMacInactThresh;                      /*Units of E-DCH TTIs��InfinityȡֵΪ0XFFFF; Enumerated (1, 2, 4, 8, 16, 32, 64, 128, 256, 512, Infinity) */
    VOS_UINT16                          usCqiDtxTimer;                         /* InfinityȡֵΪ0XFFFF;Units of subframes��Enumerated (0, 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, Infinity) */
    VOS_UINT16                          usUeDpcchBurst1;                       /* Units of sub-frames;Enumerated (1, 2, 5) */
    VOS_UINT16                          usUeDpcchBurst2;                       /* Units of sub-frames;Enumerated (1, 2, 5) */
    VOS_UINT16                          usReserved2;
}PHYITF_DTX_INFO_STRU;

/*****************************************************************************
 �ṹ��    : PHYITF_DRX_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : DRX����
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usUeDrxCyc;                     /*Units of sub-frames*/
    VOS_UINT16                          usUeDrxCycInactThresh;          /*Units of subframes*/
    VOS_UINT16                          usUeGrantMonitorInactThresh;    /*Units of E-DCH TTIs*/
    PHYITF_BOOL_ENUM_UINT16             enUeDrxGrantMonitoring;         /* BOOLEAN */

}PHYITF_DRX_INFO_STRU;

/*****************************************************************************
 �ṹ��    : PHYITF_DTX_DRX_NEW_TIM_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CPC�µĶ�ʱ����
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usEnablingDelay;                        /*In radio frames, Enumerated (0, 1, 2, 4, 8, 16, 32, 64, 128) */

    VOS_UINT16                          usUeDtxDrxOffset;                       /*Units of subframes, INTEGER(0..159) */

} PHYITF_DTX_DRX_NEW_TIM_STRU;

/*****************************************************************************
 ö����    : PHYITF_DTX_DRX_TIM_INFO_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : CPC��ʱ���÷�ʽ
*****************************************************************************/
enum  PHYITF_DTX_DRX_TIM_INFO_ENUM
{
    PHYITF_DTX_DRX_TIM_CONTINUE = 0,                                            /* Used in reconfigurations without interruption of DTX-DRX and HS-SCCH less*/
    PHYITF_DTX_DRX_TIM_NEW_TIM,
    PHYITF_DTX_DRX_TIM_BUTT
};
typedef VOS_UINT16  PHYITF_DTX_DRX_TIM_INFO_ENUM_UINT16;


/*****************************************************************************
 �ṹ��    : PHYITF_DTX_DRX_TIM_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : dtx-drx��ʱ��Ϣ
*****************************************************************************/
typedef struct
{

    VOS_UINT16                          usReserved;

    PHYITF_DTX_DRX_TIM_INFO_ENUM_UINT16 enDtxDrxTimInfo;

    PHYITF_DTX_DRX_NEW_TIM_STRU         stDtxDrxNewTim;

}PHYITF_DTX_DRX_TIM_INFO_STRU;

/*****************************************************************************
 �ṹ��    : PHYITF_DTX_DRX_PARAMS_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : DTX-DRX ��ز���
*****************************************************************************/
typedef struct
{

    PHYITF_BOOL_ENUM_UINT16             enDtxInfoValid;                         /* �Ƿ����DTX information*/
    PHYITF_BOOL_ENUM_UINT16             enDrxInfoValid;                         /* �Ƿ����DRX information*/

    PHYITF_DTX_INFO_STRU                stDtxInfo;
    PHYITF_DRX_INFO_STRU                stDrxInfo;

    VOS_UINT16                          usUlDpcchSlotFormatInfo;                /* Enumerated (1,4) */
    VOS_UINT16                          usReserved;

    PHYITF_DTX_DRX_TIM_INFO_STRU        stDtxDrxTimInfo;

}PHYITF_DTX_DRX_PARAMS_STRU;

/*****************************************************************************
 �ṹ��    : PHYITF_HS_SCCH_LESS_TBS_LIST
 Э����  :
 ASN.1���� : Transport Block Size List
 �ṹ˵��  : CPC���ò���
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usTBSizeIndex;                          /*Integer (1..90)*/

    PHYITF_BOOL_ENUM_UINT16             enHsPdschSndCodeSuppt;
} PHYITF_HS_SCCH_LESS_TBS_LIST_STRU;


/*****************************************************************************
 �ṹ��    : PHYITF_HS_SCCH_LESS_NEW_OPERATION
 Э����  :
 ASN.1���� : New HS-SCCH less operation
 �ṹ˵��  : CPC���ò���
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usHsPdschCodeIndex;                     /* INTEGER(1..15) */
    VOS_UINT16                          usTBSizeCnt;                            /*1..< maxHS-SCCHLessTrBlk*/
    PHYITF_HS_SCCH_LESS_TBS_LIST_STRU   astHsScchLessTBsList[RRC_PHY_MAX_HSSCCH_LESS_TB_NUM];

} PHYITF_HS_SCCH_LESS_NEW_OPER_STRU;

/*****************************************************************************
 ö����    : PHYITF_HS_SCCH_LESS_OPERATION_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  :
*****************************************************************************/
enum  PHYITF_HS_SCCH_LESS_OPERATION_ENUM
{
    PHYITF_HS_SCCH_LESS_OPERATION_CONTINUE = 0,
    PHYITF_HS_SCCH_LESS_OPERATION_NEW_OPERATION,
    PHYITF_HS_SCCH_LESS_OPERATION_BUTT
};
typedef VOS_UINT16  PHYITF_HS_SCCH_LESS_OPERATION_ENUM_UINT16;

/*****************************************************************************
 �ṹ��    : PHYITF_HS_SCCH_LESS_INFO_STRU
 Э����  :
 ASN.1���� : HS-SCCH-LessInfo-r7
 �ṹ˵��  : HsScchLess ����
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                  usReserved;

    PHYITF_HS_SCCH_LESS_OPERATION_ENUM_UINT16   enHsScchLessOperation;

    PHYITF_HS_SCCH_LESS_NEW_OPER_STRU           stHsScchLessNewOp;

} PHYITF_HS_SCCH_LESS_INFO_STRU;

/*****************************************************************************
 �ṹ��    : RRC_PHY_CPC_CONFIG_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CPC���ò���
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                                /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;                                 /* ����ID */

    VOS_INT16                           sActiveTime;                            /* ����ʱ��[-1,255], -1Ϊ�������� */
    PHYITF_BOOL_ENUM_UINT16             enNeedRevertDtxDrxOrder;                /* �Ƿ���Ҫ����DTX/DRX ORDER */
    PHYITF_BOOL_ENUM_UINT16             enNeedRevertHsscchLessOrder;            /* �Ƿ���Ҫ����HSSCCH-LESS ORDER */
    VOS_UINT16                          usRsv1;

    PHYITF_BOOL_ENUM_UINT16             enDtxDrxStatus;                         /* 0:DTX_DRX_STATUSΪFALSE,1:DTX_DRX_STATUSΪTRUE*/
    PHYITF_BOOL_ENUM_UINT16             enHsScchLessStatus;                     /* 0:HS_SCCH_LESS_STATUSΪFALSE,1:HS_SCCH_LESS_STATUSΪTRUE */

    PHYITF_DTX_DRX_PARAMS_STRU          stDtxDrxParams;

    PHYITF_HS_SCCH_LESS_INFO_STRU       stHsScchLessInfo;
}RRC_PHY_CPC_CONFIG_REQ_STRU;


/*****************************************************************************
 �ṹ��    : PHY_RRC_CPC_CONFIG_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CPC ����Ӧ��
 *****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16                enMsgID;                          /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                usOpId;                           /* ������ʶ */
    PHYITF_CHANNEL_CONFIG_RESULT_ENUM_UINT16  enIndicator;                      /* ���ý��,0����ɹ�����������ʧ��*/
    VOS_UINT16                                usReserve1;
}PHY_RRC_CPC_CONFIG_CNF_STRU;


/*****************************************************************************
 �ṹ��    : RRC_PHY_CPC_DISABLE_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ȥ�����CPC����������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16              enMsgID;                            /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                              usOpId;                             /* ����ID */
    VOS_INT16                               sActiveTime;                        /* ����ʱ�� */
    VOS_UINT16                              usReserve1;
}RRC_PHY_CPC_DISABLE_REQ_STRU;


/*****************************************************************************
 �ṹ��    : PHY_RRC_CPC_DISABLE_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �ͷ�CPC���е�״̬
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                                /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                          usOPID;                                 /* ������ʶ */

} PHY_RRC_CPC_DISABLE_CNF_STRU;


/*****************************************************************************
  8 UNION����
*****************************************************************************/

/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*==========================================================================
               ����ע�͵��Ľṹ��������ASN DLL�ṹ
============================================================================*/

#if 0                                                                           /* _H2ASN_Skip */

/**************************************************************************
 �ṹ��    : WAS_PHYITF_WRR_PHY_UL_POWER_CTRL_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :���й��ʿ��ƽṹ

***************************************************************************/

typedef   struct
{
    /*��������ѡ����[1,2];
    1:Signal Gain Factor, 2:Computed Gain Factor*/
    VOS_UINT8                           ucGainFactor;
    VOS_UINT8                           ucReserved;

    VOS_UINT8                           ucBetaC;
    VOS_UINT8                           ucBetaD;

    /*[-1,3];-1:�����TFC�����ο�,����Ч�ο�ID*/
    VOS_INT8                            cRefTfcId;

    /*[-5,10],*/
    VOS_INT8                            cPowerOffset;

}PHYITF_UL_POWER_CTRL_STRU;

/**************************************************************************
 �ṹ��    : WAS_PHYITF_WRR_PHY_TFC_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :�����ʽ��Ͻṹ

***************************************************************************/
typedef   struct
{
    VOS_UINT16                          usTfci;/*[0,1023]*/
    /*����TRCH Num �� ����*/
    VOS_UINT8                           aucTfiParam[4];
    /******************************************************************************************************
        _H2ASN_IE_DYNAMIC_ARRAY_COMMENT STRUTYPE:VOS_UINT16 MINIDX:1 MAXIDX:8 EXPORTNAME:usH2ASNTrchNum
    ******************************************************************************************************/

}PHYITF_DL_TFC_STRU;

/**************************************************************************
 �ṹ��    : WAS_PHYITF_WRR_PHY_TFC_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :�����ʽ��Ͻṹ

***************************************************************************/
typedef   struct
{
    VOS_UINT16                          usTfci;/*[0,1023]*/
    /*����TRCH Num �� ����*/
    VOS_UINT8                           aucTfiParam[4];
    /******************************************************************************************************
        _H2ASN_IE_DYNAMIC_ARRAY_COMMENT STRUTYPE:VOS_UINT16 MINIDX:1 MAXIDX:8 EXPORTNAME:usH2ASNTrchNum
    ******************************************************************************************************/
    PHYITF_UL_POWER_CTRL_STRU           stUlPowerCtrl;

}PHYITF_UL_TFC_STRU;

/**************************************************************************
 �ṹ��    : WAS_PHYITF_WRR_PHY_TF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :�����ʽ���ݽṹ

***************************************************************************/
typedef struct
{
    VOS_UINT16                          usTfi;          /*[0,32]*/
    VOS_UINT16                          usTBCnt;        /*[0,512];��������*/
    VOS_UINT16                          usTBLen;        /*[0,5034];����鳤��*/

}PHYITF_TF_STRU;

/**************************************************************************
 �ṹ��    : WAS_PHYITF_WRR_PHY_TFS_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :TFS�ṹ
***************************************************************************/
typedef struct
{
    /*[1,32];�����ŵ�ID*/
    VOS_UINT8                           ucTrchID;

    /*[0,2]; �������ͺͱ���Ч�ʣ�0-CC1/2,1-CC1/3,2-Turbo EnCoder*/
    VOS_UINT8                           ucCodeMethod;
    VOS_UINT16                          usRateMatch;    /*��Χ[1,256]*/
    VOS_UINT8                           ucCRCLen;       /*��Χ(0,8,12,16,24)*/
    VOS_UINT8                           ucTti;          /*��Χ(1,2,4,8)~(10,20,40,80)��λms*/
    VOS_UINT16                          usTfNum;        /*TF�ĸ���*/    /* _H2ASN_IE_DYNAMIC_ARRAY_EXPORT STRUTYPE:VOS_UINT16 EXPORTNAME:usH2ASNTfNum */
    VOS_UINT8                           aucTFListParam[4];
    /******************************************************************************************************
        _H2ASN_IE_DYNAMIC_ARRAY_COMMENT STRUTYPE:PHYITF_TF_STRU MINIDX:1 MAXIDX:32 EXPORTNAME:usH2ASNTfNum
    ******************************************************************************************************/

}PHYITF_TFS_STRU;


/**************************************************************************
 �ṹ��    : WAS_PHYITF_WRR_PHY_TfcList
 Э����  :
 ASN.1���� :
 �ṹ˵��  :���д����ʽ����б�ṹ
***************************************************************************/
typedef struct
{
    VOS_UINT16                          usDlTfcCnt;   /* _H2ASN_IE_DYNAMIC_ARRAY_EXPORT STRUTYPE:VOS_UINT16 EXPORTNAME:usH2ASNDlTfcNum */

    VOS_UINT8                           aucDlTfcParam[4];
    /******************************************************************************************************
        _H2ASN_IE_DYNAMIC_ARRAY_COMMENT STRUTYPE:PHYITF_DL_TFC_STRU MINIDX:1 MAXIDX:128 EXPORTNAME:usH2ASNDlTfcNum
    ******************************************************************************************************/

}PHYITF_DL_TFCS_LIST_STRU;

/**************************************************************************
 �ṹ��    : WAS_PHYITF_WRR_PHY_TfcList
 Э����  :
 ASN.1���� :
 �ṹ˵��  :���д����ʽ����б�ṹ
***************************************************************************/
typedef struct
{
    VOS_UINT16                          usUlTfcCnt;   /* _H2ASN_IE_DYNAMIC_ARRAY_EXPORT STRUTYPE:VOS_UINT16 EXPORTNAME:usH2ASNUlTfcNum */

    VOS_UINT8                           aucUlTfcParam[4];
    /******************************************************************************************************
        _H2ASN_IE_DYNAMIC_ARRAY_COMMENT STRUTYPE:PHYITF_UL_TFC_STRU MINIDX:1 MAXIDX:128 EXPORTNAME:usH2ASNUlTfcNum
    ******************************************************************************************************/

}PHYITF_UL_TFCS_LIST_STRU;

/**************************************************************************
 �ṹ��    : WAS_PHYITF_WRR_PHY_UlCcTrch
 Э����  :
 ASN.1���� :
 �ṹ˵��  :����CCTRCH�ṹ
***************************************************************************/
typedef struct
{
    /*[3,4]; 3:PRACH, 4: ULDPCH*/
    VOS_UINT16                          usCcTrchId;

    /*[-1,255],-1 ��������*/
    VOS_INT16                           sActiveTime;

    /*��С��Ƶ����(4,8,16,32,64,128,256)*/
    VOS_UINT16                          usMinSf;

    /*��ռ���:(40,44,48,52,56,60,64,68,72,76,80,84,88,92,96,100)*/
    VOS_UINT16                          usPL;

    /*[1,32]*/
    VOS_UINT16                          usTrchNum;          /* _H2ASN_IE_DYNAMIC_ARRAY_EXPORT STRUTYPE:VOS_UINT16 EXPORTNAME:usH2ASNTrchNum */

    VOS_UINT8                           aucTrchParam[4];
    /******************************************************************************************************
        _H2ASN_IE_DYNAMIC_ARRAY_COMMENT STRUTYPE:PHYITF_TFS_STRU MINIDX:1 MAXIDX:8 EXPORTNAME:usH2ASNTrchNum
    ******************************************************************************************************/
    PHYITF_UL_TFCS_LIST_STRU            stUlTfcs;

}PHYITF_UL_CCTRCH_STRU;

typedef struct
{
    /*ѡ��Ĵ����ŵ�����,���8��*/
    VOS_UINT8                           ucSelTrChNum;

    /*��Ч��Χ [1~32,0XFF] �����⻷����,��1�������ŵ�ID*/
    VOS_UINT8                           ucTrch1ID;

    /*��Ч��Χ [1~32,0XFF] �����⻷����,��2�������ŵ�ID*/
    VOS_UINT8                           ucTrch2ID;

    /*��Ч��Χ [1~32,0XFF] �����⻷����,��3�������ŵ�ID*/
    VOS_UINT8                           ucTrch3ID;

    /*��Ч��Χ [1~32,0XFF] �����⻷����,��4�������ŵ�ID*/
    VOS_UINT8                           ucTrch4ID;

    /*��Ч��Χ [1~32,0XFF] �����⻷����,��5�������ŵ�ID*/
    VOS_UINT8                           ucTrch5ID;

    /*��Ч��Χ [1~32,0XFF] �����⻷����,��6�������ŵ�ID*/
    VOS_UINT8                           ucTrch6ID;

    /*��Ч��Χ [1~32,0XFF] �����⻷����,��7�������ŵ�ID*/
    VOS_UINT8                           ucTrch7ID;

    /*��Ч��Χ [1~32,0XFF] �����⻷����,��8�������ŵ�ID*/
    VOS_UINT8                           ucTrch8ID;

    /*��ʼSirTarget*/
    VOS_UINT8                           ucInitailSirTarget;

    /*������ŵ�ID,0XFF������Ч*/
    VOS_UINT8                           ucSigTrchID;

    /*���й��ز�������,����0.1,��ʵ��ֵΪ����ֵ*0.1 */
    VOS_UINT8                           ucUpStepSizeFactor;

    /*���й��ز�������,����0.1,��ʵ��ֵΪ����ֵ*0.1 */
    VOS_UINT8                           ucDownStepSizeFactor;

    /*�������й��ز�������,����0.1,��ʵ��ֵΪ����ֵ*0.1 */
    VOS_UINT8                           ucSigUpStepSizeFactor;

    /*�������й��ز�������,����0.1,��ʵ��ֵΪ����ֵ*0.1 */
    VOS_UINT8                           ucSigDownStepSizeFactor;

    /*SirTarget������,[-128 --- 127]*/
    VOS_INT8                            cDeltaSirTarget;

	/*TOT OLPC FadeMargin��Ȩֵ*/
    VOS_UINT16                           usMapWeight;

}PHYITF_OLPC_TRCHID_STRU;

/**************************************************************************
 �ṹ��    : PHYITF_DL_CCTRCH_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����CCTRCH
***************************************************************************/
typedef struct
{
    /*[1,2]; 1:SCCPCH, 2:DLDPCH*/
    VOS_UINT16                          usCcTrchId;

#if FEATURE_WCBS == FEATURE_ON
    VOS_UINT16                           usCctrchIndex;        /* cctrch�������������ŵ���Ӧ */
    PHYITF_SCCPCH_DEMODULATE_ENUM_UINT16 enSccpchDemInd;       /* ���ָʾ��Ŀǰ��sccpch���� */
    PHYITF_BOOL_ENUM_UINT16              enSupportCtch;        /* �Ƿ�֧��cbs */
    VOS_UINT16                           usReserv1;            /* ���� */
#endif

    /*[-1,255]; -1 ��������*/
    VOS_INT16                           sActiveTime;

    /*[0,17]; ʱ϶��ʽ*/
    VOS_UINT8                           ucSlotFmt;

    /*[0,1]; 0:flexible position, 1:fixed position*/
    VOS_UINT8                           ucDTXPos;

    /*[1,8]; �����ŵ�����*/
    VOS_UINT16                          usDlTrchNum;    /* _H2ASN_IE_DYNAMIC_ARRAY_EXPORT STRUTYPE:VOS_UINT16 EXPORTNAME:usH2ASNTrchNum */

    VOS_UINT8                           aTrchParams[4];
    /******************************************************************************************************
        _H2ASN_IE_DYNAMIC_ARRAY_COMMENT STRUTYPE:PHYITF_TFS_STRU MINIDX:1 MAXIDX:8 EXPORTNAME:usH2ASNTrchNum
    ******************************************************************************************************/

    PHYITF_DL_TFCS_LIST_STRU            stDlTfcs;
    PHYITF_OLPC_TRCHID_STRU             stOlpcTrchId;

}PHYITF_DL_CCTRCH_STRU;

/*****************************************************************************
 �ṹ��    : PHYITF_CCTRCH_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����ϴ����ŵ��ṹ,����ASN1���ɵ������ṹ
*****************************************************************************/
typedef struct
{
    PHYITF_CCTRCH_ID_ENUM_UINT16        enCctrchId;  /* �����ŵ����� */         /* _H2ASN_IeChoice_Export PHYITF_CCTRCH_ID_ENUM_UINT16 */
    VOS_UINT16                          usParamLen;  /* ���õ�CcTrch���� */

    union                                                                       /* _H2ASN_Skip */
    {                                                                           /* _H2ASN_Skip */
        VOS_UINT16                      stPccpchPara;                           /* _H2ASN_Skip */
        VOS_UINT16                      stSccpchPara;                           /* _H2ASN_Skip */
        VOS_UINT16                      stDlDpchPara;                           /* _H2ASN_Skip */
        VOS_UINT16                      stPrachPara;                            /* _H2ASN_Skip */
        VOS_UINT16                      stUlDpchPara;                           /* _H2ASN_Skip */
        VOS_UINT16                      stHsdpaPara;                            /* _H2ASN_Skip */
        VOS_UINT16                      stHsupaPara;
        /******************************************************************************************************
            _H2ASN_IeChoice_When        PHYITF_CCTRCH_ID_ENUM_UINT16
        ******************************************************************************************************/
    }u;                                                                         /* _H2ASN_Skip */
}PHYITF_CCTRCH_PARA_STRU;

/* ��������ASN.1ʱRL��̬��������� */
typedef struct
{
    PHYITF_PHYCH_TYPE_ENUM_UINT16       enPhyType;    /* _H2ASN_IeChoice_Export PHYITF_PHYCH_TYPE_ENUM_UINT16 */

    union                                                                       /* _H2ASN_Skip */
    {                                                                           /* _H2ASN_Skip */
        PHYITF_SCCPCH_PARA_STRU         stSccpchPara;                           /* _H2ASN_Skip */
        PHYITF_PICH_STRU                stPichPara;                             /* _H2ASN_Skip */
        PHYITF_AICH_STRU                stAichPara;                             /* _H2ASN_Skip */
        PHYITF_PRACH_STRU               stPrachPara;                            /* _H2ASN_Skip */
        PHYITF_DOWNLINK_DPCH_PARA_STRU  stDlDpchPara;                           /* _H2ASN_Skip */
        PHYITF_UPLINK_DPCH_STRU         stUlDpchPara;                           /* _H2ASN_Skip */
        PHYITF_HSDPA_PHY_STRU           stHsdpaPara;                            /* _H2ASN_Skip */
        PHYITF_UL_HSUPA_PHY_STRU        stUlHsupaPara;                          /* _H2ASN_Skip */
        PHYITF_DL_HSUPA_PHY_STRU        stDlHsupaPara;                          /* _H2ASN_Skip */
        PHYITF_DOWNLINK_FDPCH_PARA_STRU stDlFdpchPara;                          /* _H2ASN_Skip */
        PHYITF_HSDPAPLUS_PHY_STRU       stHsdpaPlusPara;                        /* _H2ASN_Skip */
        PHYITF_FACH_HSDPAPLUS_PHY_STRU  stFachHsdpaPlusPara;                    /* _H2ASN_Skip */
        PHYITF_E_RACH_REQ_STRU          stERachPara;                            /* _H2ASN_Skip */
        PHYITF_SCND_HSDPAPLUS_PHY_STRU  stScndHsdpaPlus;
        /******************************************************************************************************
            _H2ASN_IeChoice_When        PHYITF_PHYCH_TYPE_ENUM_UINT16
        ******************************************************************************************************/
    }u;                                                                         /* _H2ASN_Skip */
}PHYITF_RL_PARA_STRU;

/* ��������ASN.1ʱRL��̬��������� */
typedef struct
{
    PHYITF_PHYCH_TYPE_ENUM_UINT16       enPhyType;    /* _H2ASN_IeChoice_Export PHYITF_PHYCH_TYPE_ENUM_UINT16 */
    PHYITF_UL_HSUPA_PHY_STRU            stUlHsupaPara;

}PHYITF_RL_PARA_UL_HSUPA_STRU;

/* ��������ASN.1ʱRL��̬��������� */
typedef struct
{
    PHYITF_PHYCH_TYPE_ENUM_UINT16       enPhyType;    /* _H2ASN_IeChoice_Export PHYITF_PHYCH_TYPE_ENUM_UINT16 */
    PHYITF_AICH_STRU                    stAichPara;

}PHYITF_RL_PARA_AICH_STRU;


enum PHYITF_TGPS_STATE_ENUM
{
    PHYITF_TGPS_STATE_ACTIVE            = 0,
    PHYITF_TGPS_STATE_INACTIVE          = 1,
    PHYITF_TGPS_STATE_NOCHG_ACTIVE      = 2,    /* ״̬���䣬ԭ״̬ΪActive */
    PHYITF_TGPS_STATE_NOCHG_INACTIVE    = 3,    /* ״̬���䣬ԭ״̬ΪInactive */
    PHYITF_TGPS_STATE_BUTT
};
typedef VOS_UINT16  PHYITF_TGPS_STATE_ENUM_UINT16;

typedef struct
{
    VOS_UINT16                          usTGPSI;
    PHYITF_TGPS_STATE_ENUM_UINT16       enTGPSFlag;
    VOS_UINT16                          usTGCfn;
}PHYITF_TGPS_PARA_STRU;

typedef struct
{
    VOS_UINT16                          usTGPSReCfgCfn;
    VOS_UINT16                          usTGPSNum;      /* _H2ASN_IE_DYNAMIC_ARRAY_EXPORT STRUTYPE:VOS_UINT16 EXPORTNAME:usH2ASNTGPSNum */
    VOS_UINT8                           astTGPSPara[4];
    /******************************************************************************************************
        _H2ASN_IE_DYNAMIC_ARRAY_COMMENT STRUTYPE:PHYITF_TGPS_PARA_STRU MINIDX:1 MAXIDX:6 EXPORTNAME:usH2ASNTGPSNum
    ******************************************************************************************************/
}PHYITF_COMP_MODE_CHG_PARA_STRU;


/*****************************************************************************
  H2ASN������Ϣ�ṹ����,��ͷ��Ϣ�������Ż�GTR���̶���
*****************************************************************************/
typedef struct
{
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;    /* _H2ASN_MsgChoice_Export RRC_PHY_MSG_ID_ENUM_UINT16 */

    VOS_UINT8                           aucMsgBlock[2];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          RRC_PHY_MSG_ID_ENUM_UINT16
    ****************************************************************************/
}RRC_PHY_MSG_DATA_NO_LENGTH;


/*****************************************************************************
  H2ASN������Ϣ�ṹ����
*****************************************************************************/
typedef struct
{
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;    /* _H2ASN_MsgChoice_Export RRC_PHY_MSG_ID_ENUM_UINT16 */

    VOS_UINT8                           aucMsgBlock[2];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          RRC_PHY_MSG_ID_ENUM_UINT16
    ****************************************************************************/
}RRC_PHY_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    RRC_PHY_MSG_DATA                    stMsgData;
}RrcPhyInterface_MSG;
#endif                                                                          /* _H2ASN_Skip */


/*==========================================================================
                              ����RTT���ԵĲ�������
============================================================================*/

/*****************************************************************************
 ö����    : PHYITF_RTT_REG_CONFIG_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : �Ĵ���������ö�ٶ���

*****************************************************************************/
enum    PHYITF_RTT_REG_CONFIG_ENUM
{
    PHYITF_RTT_REG_READ              = 0,       /* _H2ASN_MsgChoice PHYITF_RTT_REG_READ_STRU */
    PHYITF_RTT_REG_WRITE             = 1,       /* _H2ASN_MsgChoice PHYITF_RTT_REG_WRITE_STRU */
    PHYITF_RTT_REG_BUTT
};
typedef VOS_UINT16 PHYITF_RTT_REG_CONFIG_ENUM_UINT16;
typedef struct
{
    VOS_UINT32                          ulRegCfgAddr;       /* ���üĴ�����ַ */
    VOS_UINT32                          ulRegCfgValue;      /* ���üĴ���ֵ */
} PHYITF_RTT_TEST_REG_WRITE_ADDR_STRU;

typedef struct
{
    VOS_UINT16                          usRegCfgNum;
    PHYITF_BOOL_ENUM_UINT16             usRptFlag;    /*0Ϊֹͣ�����ϱ���1Ϊ�����ϱ�,�������ϱ���IE��Ч*/
    VOS_UINT16                          usRptNum;   /*�Ĵ���ֵ�ϱ��Ĵ�����0Ϊ�������ϱ�*/
    VOS_UINT16                          usRptPeriod;   /*�ϱ������ڣ�10msΪ��λ*/
    VOS_UINT32                          ulRttTestRegReadAddr[RRC_PHY_MAX_RTT_REG_NUM];
} PHYITF_RTT_REG_READ_STRU;

typedef struct
{
    VOS_UINT16                                  usRegWriteNum;
    VOS_UINT8                                   ucReserve[2];
    PHYITF_RTT_TEST_REG_WRITE_ADDR_STRU         astRttTestRegWriteAddr[RRC_PHY_MAX_RTT_REG_NUM];
} PHYITF_RTT_REG_WRITE_STRU;
/*****************************************************************************
 �ṹ��    : RRC_PHY_RTT_TEST_CFG_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����RTT����ʱ��ͨ��ITT�·����������HPA���
             ���ڼĴ��������ã��Լ���ӡ�Ĵ�����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16              enMsgID;            /* ԭ������ *//*_H2ASN_Skip*/
    PHYITF_RTT_REG_CONFIG_ENUM_UINT16       enRegCfgChoice;     /*�ԼĴ����Ĳ���ѡ��*/ /* _H2ASN_IeChoice_Export PHYITF_RTT_REG_CONFIG_ENUM_UINT16 */

    union                                                                       /*_H2ASN_Skip*/
    {                                                                           /*_H2ASN_Skip*/
        PHYITF_RTT_REG_READ_STRU                stRegRead;      /*_H2ASN_Skip*/
        PHYITF_RTT_REG_WRITE_STRU               stRegWrite;
        /******************************************************************************************************
            _H2ASN_IeChoice_When        PHYITF_RTT_REG_CONFIG_ENUM_UINT16
        ******************************************************************************************************/
    }unRegMode;                                                                /*_H2ASN_Skip*/
} RRC_PHY_RTT_TEST_REG_CFG_REQ_STRU;
typedef struct
{
    VOS_UINT32  ulAddress;
    VOS_UINT32  ulValue;
} PHYITF_RTT_TEST_REG_INFO_STRU;

/*****************************************************************************
 �ṹ��    : PHY_RRC_RTT_TEST_REG_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �Ĵ���ֵ���ϱ��ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                      /*_H2ASN_Skip*/
    VOS_UINT16                      usMsgName;      /* ԭ������ *//*_H2ASN_Skip*/
    VOS_UINT16                      usCfn;
    VOS_UINT16                      usSfn;
    VOS_UINT16                      usCnt;      /* �ϱ��ļĴ������� */
    PHYITF_RTT_TEST_REG_INFO_STRU        astRegInfo[RRC_PHY_MAX_RTT_REG_NUM];

}PHY_RRC_RTT_TEST_REG_IND_STRU;

/*****************************************************************************
 �ṹ��    : PHY_RRC_RTT_TEST_CFG_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����RTT����ʱ��ͨ��ITT�·����������HPA���
             ���ڼĴ��������ã��Լ���ӡ�Ĵ�����
             CNF��Ϣ���ص�ǰ���õ�״̬��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;            /* ԭ������ *//*_H2ASN_Skip*/
    PHYITF_BOOL_ENUM_UINT16             enResult;           /* ���ý�� */
} PHY_RRC_RTT_TEST_CFG_CNF_STRU;

/*****************************************************************************
 �ṹ��    : RRC_PHY_PRACH_INIT_TX_POWER_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ���ڽ���SIB7,���ݽ��յ�SIB7�еĲ��������������ķ��书��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                       /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                 /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_INT16                                   sPrachInitialTxPower;    /* ���ø������ĳ�ʼ���书�� */
}RRC_PHY_PRACH_INIT_TX_POWER_IND_STRU;

/*****************************************************************************
 �ṹ��    : RRC_PHY_SCND_RL_SETUP_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �ŵ�����������Ϣ�����ݽṹ
             ������Ҫ�������ŵ�
             ʹ�ø�ԭ����ŵ�Ϊ:

             PHYITF_PHY_SCND_HSDPAPLUS
             PHYITF_PHY_SCND_FDPCH
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                          usOPID;                 /* ������ʶ */
    VOS_UINT16                          usPhyChannelNum;        /* �����ŵ��� *//* _H2ASN_IE_DYNAMIC_ARRAY_EXPORT STRUTYPE:VOS_UINT16 EXPORTNAME:usH2ASNPhyChannelNum */
    VOS_UINT16                          usParaSize;             /* �������� */

    VOS_UINT8                           aucPhyChannelPara[4];   /* �����ŵ����ò��� */
    /******************************************************************************************************
        _H2ASN_IE_DYNAMIC_ARRAY_COMMENT STRUTYPE:PHYITF_RL_PARA_STRU MINIDX:1 MAXIDX:8 EXPORTNAME:usH2ASNPhyChannelNum
    ******************************************************************************************************/

}RRC_PHY_SCND_RL_SETUP_REQ_STRU;


/*****************************************************************************
 �ṹ��    : RRC_PHY_SCND_RL_MODIFY_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �ŵ�����������Ϣ�����ݽṹ
             ������Ҫ�������ŵ�
             ʹ�ø�ԭ����ŵ�Ϊ:


             PHYITF_PHY_SCND_UL_HSUPA
             PHYITF_PHY_SCND_DL_HSUPA
             PHYITF_PHY_SCND_FDPCH
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                          usOPID;                 /* ������ʶ */
    VOS_UINT16                          usPhyChannelNum;        /* �����ŵ��� *//* _H2ASN_IE_DYNAMIC_ARRAY_EXPORT STRUTYPE:VOS_UINT16 EXPORTNAME:usH2ASNPhyChannelNum */
    VOS_UINT16                          usParaSize;             /* �������� */

    VOS_UINT8                           aucPhyChannelPara[4];   /* �����ŵ����ò��� */
    /******************************************************************************************************
        _H2ASN_IE_DYNAMIC_ARRAY_COMMENT STRUTYPE:PHYITF_RL_PARA_STRU MINIDX:1 MAXIDX:8 EXPORTNAME:usH2ASNPhyChannelNum
    ******************************************************************************************************/

}RRC_PHY_SCND_RL_MODIFY_REQ_STRU;



/*****************************************************************************
 �ṹ��    : PHY_RRC_SCND_RL_SETUP_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �ŵ�����֤ʵ��Ϣ�����ݽṹ
             ÿ��RRC_PHY_SCND_RL_SETUP_REQ_STRU��Ϣ��Ӧһ��CNF��Ϣ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                          usOPID;                 /* ������ʶ */

    VOS_UINT16                          usReserve1;             /* �ֽڶ���*/
    VOS_UINT16                          usPhyChannelNum;        /* �����ŵ�Num��*/
    PHY_RRC_RL_EACH_CHANNEL_CNF_STRU    astPhyChannelCnf[RRC_PHY_MAX_PHYCHAN_NUM];

}PHY_RRC_SCND_RL_SETUP_CNF_STRU;

/*****************************************************************************
 �ṹ��    : PHY_RRC_SCND_RL_MODIFY_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �ŵ��޸�֤ʵ��Ϣ�����ݽṹ
             ÿ��RRC_PHY_SCND_RL_MODIFY_REQ_STRU��Ϣ��Ӧһ��CNF��Ϣ

*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                          usOPID;                 /* ������ʶ*/

    VOS_UINT16                          usReserve1;             /* �ֽڶ���*/
    VOS_UINT16                          usPhyChannelNum;        /* �����ŵ�Num��*/
    PHY_RRC_RL_EACH_CHANNEL_CNF_STRU    astPhyChannelCnf[RRC_PHY_MAX_PHYCHAN_NUM]; /* ���ý��������ͬsetup*/

}PHY_RRC_SCND_RL_MODIFY_CNF_STRU;

/*****************************************************************************
 �ṹ��    : RRC_PHY_SCND_RL_REL_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ���ز��ŵ��ͷ�������Ϣ�����ݽṹ
             ������Ҫ�ͷŵ��ŵ�

*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;            /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                          usOPID;             /* ������ʶ */
    VOS_UINT16                          usReserve1;
    VOS_UINT16                          usPhyChannelNum;    /* �����ŵ��� */
    PHYITF_PHY_REL_CHANNEL_INFO_STRU    astPhyChInfo[RRC_PHY_MAX_PHYCHAN_NUM];

}RRC_PHY_SCND_RL_REL_REQ_STRU;

/*****************************************************************************
 �ṹ��    : PHY_RRC_SCND_RL_REL_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �ŵ��ͷ�֤ʵ��Ϣ�����ݽṹ
             ÿ��RRC_PHY_SCND_RL_RELEASE_REQ_STRU��Ϣ��Ӧһ��CNF��Ϣ

*****************************************************************************/

typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                          usOPID;                 /* ������ʶ */

    VOS_UINT16                          usReserve1;             /* �ֽڶ���*/
    VOS_UINT16                          usPhyChannelNum;        /* �����ŵ�Num��*/
    PHY_RRC_RL_EACH_CHANNEL_CNF_STRU    astPhyChannelCnf[RRC_PHY_MAX_PHYCHAN_NUM]; /* ���ý��������ͬsetup*/

}PHY_RRC_SCND_RL_REL_CNF_STRU;


/* ADD E-RACH BEGIN */
/*****************************************************************************
 �ṹ��    :
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    PHYITF_BOOL_ENUM_UINT16                 enSoffsetValid;                     /* ָʾusSoffset�Ƿ����  */
    VOS_UINT16                              usSoffset;                          /* ��ΧInteger(0..9) ��λ 256chips */
    VOS_UINT16                              usFdpchCodeNum;                     /* F-DPCH Code number */

    PHYITF_BOOL_ENUM_UINT16                 enERgchValid;                       /* ָʾstERgchInfo�Ƿ����  */
    PHYITF_E_RGCH_INFO_STRU                 stERgchInfo;                        /* OPTIONAL */

    PHYITF_E_HICH_INFO_STRU                 stEHichInfo;                        /* MP */

    /*����DPCCH������� */
    PHYITF_SCRAMBL_CODE_TYPE_ENUM_UINT16    enScrambCodeType;                   /* Scrambling code type Enumerated(short, long)*/

    PHYITF_BOOL_ENUM_UINT16                 enScrambCodeNumValid;               /* ָʾulScrambCodeNum�Ƿ���ڣ�MD���㰴10.3.6.87b  */
    VOS_UINT32                              ulScrambCodeNum;                    /* Integer(0..16777215) */

}PHYITF_COMMON_EDCH_RES_CFG_INFO_STRU;

/*****************************************************************************
 �ṹ��    : PHYITF_COMMON_EDCH_RES_CFG_INFO_LIST_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usRsv1;                             /* ���ֽڶ��룬���� */
    VOS_UINT16                              usCommEdchResNum;                   /* EDCH��Դ�� */
    PHYITF_COMMON_EDCH_RES_CFG_INFO_STRU    astCommonEdchResCfgInfo[PS_WUE_MAX_EDCHS];

}PHYITF_COMMON_EDCH_RES_CFG_INFO_LIST_STRU;


/*****************************************************************************
 �ṹ��    : PHYITF_SCND_DL_FDPCH_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usTpcErrorRateTarget;                   /* ��Ϊԭֵ����Ϊ0.01, Ϊ�˱��־���Ŀǰ����ֵ��ԭʼֵ����100��*/
    VOS_INT16                           sInitialSirTarget;                      /* ��ʼSirTarget�����⻷���� ,
                                                                                    E-RACHʱÿ�����ö���д��ʼֵ,F2D������д��ʼֵ */
    VOS_INT16                           sDeltaSirTarget;                        /* ����DPCH��FDPCH�л�ʱ�Ĳ�������
                                                                                   E-RACHʱ��д0 */
    VOS_UINT16                          usUpStepSizeFactor ;
    VOS_UINT16                          usDownStepSizeFactor ;

    VOS_UINT16                          usReserve1;                             /* ���ֽڶ��룬���� */

}PHYITF_FDPCH_OLPC_PARA_STRU;

typedef struct
{

    PHYITF_FREQ_INFO_STRU                   stFdpchFreqInfo;                    /* Ƶ����Ϣ */

    PHYITF_FDPCH_OLPC_PARA_STRU             stFdpchOlpcPara;                    /* �⻷���ز��� */

    VOS_UINT16                              usFdpchSlotFormat;                  /* INTEGER(0..9)  OPTIONAL :����331�ṩ��Ĭ�ϲ����������� */
    PHYITF_TX_DIVER_IND_ENUM_UINT16         enTDIndicator;                      /* �ּ�ָʾ :����Ϊ�Ƿּ�*/
    VOS_UINT16                              usDownLinkScramCode;                /* ������·�������  */
    PHYITF_DPC_MODE_TYPE_ENUM_UINT16        enDpcMode;                          /* ���й��ʿ���:����331�ṩ��Ĭ�ϲ����������� */

    PHYITF_TX_DIVER_IND_ENUM_UINT16         enPcpichTDIndicator;                /* ����Ƶ�ŵ��Ƿ�ʹ�÷��ּ�,0:��ʹ�÷ּ�,1:STTD�ּ�,0xFF:�޷���÷ּ���ʽ */

    VOS_UINT16                              usReserve1;                         /* ���ֽڶ��룬���� */
}PHYITF_DOWNLINK_FDPCH_E_RACH_STRU;


/*****************************************************************************
 �ṹ��    : PHYITF_UPLINK_DPCH_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����ר�������ŵ���Ϣ
 *****************************************************************************/
typedef struct
{
    PHYITF_FREQ_INFO_STRU                stFreqInfo;
    PHYITF_ULDPCH_POWER_CONTROL_STRU     stUlDpchPowerControl;
    VOS_UINT16                           usDpchNum;                              /* ����DPDCH������:�̶���0 */
    VOS_UINT16                           usSlotFormat;                           /* ����DPCCHʹ�õ�ʱ϶��ʽ */
}PHYITF_UPLINK_DPCH_E_RACH_STRU;


/*****************************************************************************
 �ṹ��    : PHYITF_E_RACH_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :������ǿCELL_FACH ��ز����ṹ
*****************************************************************************/

typedef struct
{
    PHYITF_PHYCH_TYPE_ENUM_UINT16                   enPhyChannelType;           /* _H2ASN_Skip */
    VOS_INT16                                       sActiveTime;                /* �̶�-1,��ʾ�������� */

    PHYITF_PRACH_STRU                               stPrachPara;                /* _H2ASN_Replace PHYITF_RL_PARA_STRU *//* PRACH �ŵ���ز������� */

    VOS_INT16                                       sPowerOffsetPpE;            /* Power offset Pp-e [-5...10]*/

    PHYITF_BOOL_ENUM_UINT16                         enEAiInd;                   /* eai�Ƿ���Ч */
    PHYITF_AICH_STRU                                stAichPara;                 /* _H2ASN_Replace PHYITF_RL_PARA_AICH_STRU *//* AICH �ŵ���ز��� */

    PHYITF_UPLINK_DPCH_E_RACH_STRU                  stUpLinkDpch;

    VOS_UINT16                                      usAddEdchTransBackOff;      /* ��Χ: (0..15) ��λ: TTI Additional E-DCH transmission back off  */
    VOS_UINT16                                      usMaxAllocEdchResForCCCH;   /* Enumerated (8, 12, 16, 24, 32, 40, 80, 120),��λ TTI Maximum E-DCH resource allocation for CCCH */
    VOS_UINT16                                      usMaxPrdForCollision;       /* Maximum period for collision resolution phase Integer (8..24) TTI*/
    VOS_UINT16                                      usEdchTransContinuBackOff;  /* E-DCH transmission continuation back off Enumerated (0, 8, 16, 24, 40, 80, 120, infinity)�� infinityʱ��0xffff */
    PHYITF_BOOL_ENUM_UINT16                         enAckNackValid;             /* �Ƿ��ϱ�ack��nack */

    /* ������·�ĵ�Ƶ�ŵ��������룬��ΪĿǰֻ֧������Ƶ�ŵ�
    ����E_HICH,E_AGCH,E_RGCH��ʹ�����������Ϊ�Լ��ŵ������� */
    VOS_UINT16                                      usPrimScramCode;
    PHYITF_E_AGCH_INFO_STRU                         stEAgchInfo;                /* MP */

    PHYITF_UL_HSUPA_PHY_STRU                        stUlHsupaPara;              /* _H2ASN_Replace PHYITF_RL_PARA_UL_HSUPA_STRU *//*����HSUPA */

    PHYITF_DOWNLINK_FDPCH_E_RACH_STRU               stDlFdpchPara;              /* F-DPCH��ز��� */

    PHYITF_HS_DPCCH_INFO_STRU                       stHsDpcchInfo;              /* HS-DPCCH��ز��� */

    PHYITF_COMMON_EDCH_RES_CFG_INFO_LIST_STRU       stCommEdchResCfgList;       /* Common E-DCH Resource Configuration information list */

}PHYITF_E_RACH_REQ_STRU;
/* ADD E-RACH END */

/* DC HSUPA BEGINE */
/*****************************************************************************
 �ṹ��    : RRC_PHY_SCND_UL_FREQ_DEACTIVE_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : Secondary serving E-DCH cell info
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                          usOPID;                 /* ������ʶ*/
}RRC_PHY_SCND_UL_FREQ_DEACTIVE_REQ_STRU;


/*****************************************************************************
 �ṹ��    : PHY_RRC_SCND_UL_FREQ_DEACTIVE_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����RRC_PHY_SCND_UL_FREQ_DEACTIVE_REQ�Ļظ�
 *****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16                enMsgID;          /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                usOPID;           /* ������ʶ */
    PHYITF_CHANNEL_CONFIG_RESULT_ENUM_UINT16  enIndicator;      /* ���ý��,0����ɹ�����������ʧ��*/
    VOS_UINT16                                usReserve1;
}PHY_RRC_SCND_UL_FREQ_DEACTIVE_CNF_STRU;

/*****************************************************************************
 �ṹ��    : PHYITF_SCND_EDCH_CELL_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : Secondary serving E-DCH cell info
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                          usPcPrb;                    /* INTEGER(0..7) */
    PHYITF_SCRAMBL_CODE_TYPE_ENUM_UINT16                enScramCodeType;            /* �������� */
    VOS_UINT32                                          ulScramCodeNum;             /* ������ */

    VOS_UINT16                                          us2msSchedGrantProcAlloc;   /*BITMAP,2ms TTI,������Ȩ��������,��MAC-d��������
                                                                                        ֻ����BITλȡֵΪ1�Ľ����Ϸ���,Bit0��Ӧ����7��Bit1��Ӧ����6���Դ�����...
                                                                                        ���粻Я����ʾȫѡ��Default value is: transmission in all HARQ processes is allowed.��Ч��д:0xFFFF*/
    VOS_UINT16                                          usPrimScndGrantSelect;      /* ������Ȩѡ��,0ѡ������,1ѡ�񸨵�,OP*/
    PHYITF_MIN_REDUC_E_DPDCH_GAIN_FACTOR_ENUM_UINT16    enMinReducEDpdchGainFactor; /* ENUMERATED  OPTIONAL */


    PHYITF_BOOL_ENUM_UINT16                             enEDchMinSetETfciValid; /* usEDchMinSetETfci �Ƿ���Ч������Ч����enEDchMinSetETfciValidΪ1������enEDchMinSetETfciValidΪ0 */
    VOS_UINT16                                          usEDchMinSetETfci;          /* INTEGER(0..127)  OPTIONAL */
    VOS_UINT16                                          usDpcchPwrOffsetScndUlFreq; /* INTEGER(0..7) */

}PHYITF_SCND_EDCH_INFO_COMM_STRU;

/*****************************************************************************
 �ṹ��    : PHYITF_SCND_UL_HSUPA_PHY_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{

    PHYITF_PHYCH_TYPE_ENUM_UINT16       enPhyChannelType;                       /* _H2ASN_Skip */
    VOS_INT16                           sActiveTime;                            /* �����ʱ��CFN,-1��ʾ��������,�����ʾ�����CFN */
    VOS_UINT16                          usUlFreqInfo;                           /* ���ز�����Ƶ����Ϣ */
    VOS_UINT16                          usFreqBandNo;                           /* Ƶ�κ�:1,2,3,4,5,6*/
    VOS_UINT16                          usTxRxFreqSeparation;                   /* �շ�Ƶ��*/
    VOS_UINT16                          usReserve1;
    PHYITF_SCND_EDCH_INFO_COMM_STRU     stScndEdchInfoComm;

}PHYITF_SCND_UL_HSUPA_PHY_STRU;

/*****************************************************************************
 �ṹ��    : PHYITF_SCND_DL_HSUPA_PHY_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{

    PHYITF_PHYCH_TYPE_ENUM_UINT16               enPhyChannelType;               /* _H2ASN_Skip */

    VOS_INT16                                   sActiveTime;                    /*�����ʱ��CFN,-1��ʾ��������,�����ʾ�����CFN*/

    PHYITF_DL_PER_EDCH_RL_LIST_STRU             stDlRLInfo;                     /*����RL ��Ϣ,��DlRLInfo��λʱ��Ч*/
}PHYITF_SCND_DL_HSUPA_PHY_STRU;

/*****************************************************************************
 �ṹ��    : PHYITF_FDPCH_INFO_ON_SND_UL_FREQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : Downlink F-DPCH info for each RL 10.3.6.23ob
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                  usFdpchFrameOffset;             /* INTEGER(0..149) */
    VOS_UINT16                                  usFdpchSlotFormat;              /* INTEGER(0..9)  OPTIONAL */
    VOS_UINT16                                  usReserve1;

    PHYITF_BOOL_ENUM_UINT16                     enSecndCpichValidInd;           /* �Ƿ����*/
    PHYITF_SECOND_CPICH_STRU                    stSecondCpichInfo;              /*����Ƶ������Ϣ*/

    VOS_UINT16                                  usSecScramCode;                 /* �ڶ����룬���������ʹ��0��ʾ��Ч */
    VOS_UINT16                                  usOvsfCodeNum;                  /* ��Ƶ��   */
    VOS_UINT16                                  usTpcCombIndex;                 /* TPC������� */
    PHYITF_TX_DIVER_IND_ENUM_UINT16             enTDIndicator;                  /* �ּ�ָʾ */

}PHYITF_FDPCH_INFO_ON_SCND_UL_FREQ_STRU;

/*****************************************************************************
 �ṹ��    : PHYITF_SCND_DL_FDPCH_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{

    PHYITF_PHYCH_TYPE_ENUM_UINT16               enPhyChannelType;               /* _H2ASN_Skip */
    VOS_INT16                                   sActiveTime;                    /*�����ʱ��CFN,-1��ʾ��������,�����ʾ�����CFN*/
    VOS_UINT16                                  usPrimScramCode;                /* ������ */
    VOS_UINT16                                  usReserve1;

    PHYITF_FREQ_INFO_STRU                       stFdpchFreqInfo;                /* Ƶ����Ϣ */

    PHYITF_FDPCH_INFO_ON_SCND_UL_FREQ_STRU      stDlFdpchInfoPerRlSecUlFreq;
    PHYITF_FDPCH_OLPC_PARA_STRU                 stFdpchOlpcPara;
    PHYITF_BOOL_ENUM_UINT16                     enNeedRevertOrder;              /* �Ƿ���Ҫ����HS_SCCH order,Ӧ�ó����л�ʧ�ܻ���,SCND_RL_SETUPʱ�ſ�����дPS_TRUE */
    PHYITF_TX_DIVER_IND_ENUM_UINT16             enPcpichTDIndicator;            /*����Ƶ�ŵ��Ƿ�ʹ�÷��ּ�,0:��ʹ�÷ּ�,1:STTD�ּ�,0xFF:�޷���÷ּ���ʽ*/
    PHYITF_JUDGE_SYNC_STRU                      stJudgeSync;                    /* ͬʧ���о����� */

}PHYITF_SCND_DL_FDPCH_PARA_STRU;

/* DC HSUPA END */

/*****************************************************************************
 ö����    : PHYITF_BUSINESS_TYPE_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : SET WORK MODE������
*****************************************************************************/
enum    PHYITF_BUSINESS_TYPE_ENUM
{
    PHYITF_BUSINESS_TYPE_NORMAL        = 0,          /* ����ģʽ */
    PHYITF_BUSINESS_TYPE_CT            = 1,
    PHYITF_BUSINESS_TYPE_NO_SIG_BT     = 2,
    PHYITF_BUSINESS_TYPE_SIG_BT        = 3,
    PHYITF_BUSINESS_TYPE_BUTT
};
typedef VOS_UINT16 PHYITF_BUSINESS_TYPE_ENUM_UINT16;

/*****************************************************************************
 �ṹ��    : RRC_PHY_SET_WORK_MODE_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ֪ͨ����㵱ǰ������ģʽΪ��ģ���Ǵ�ģģʽ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                          usOPID;                 /* ������ʶ */

    VOS_RATMODE_ENUM_UINT32              enMasterMode;          /* _H2ASN_Replace VOS_UINT32 enMasterMode; */
    VOS_RATMODE_ENUM_UINT32              enSlaveMode;           /* _H2ASN_Replace VOS_UINT32 enSlaveMode; */

    PHYITF_BUSINESS_TYPE_ENUM_UINT16    enBusinessType;          /* SET WORK MODE�����ͣ�WAS�̶���PHYITF_BUSINESS_TYPE_NORMAL */
    PHYITF_BOOL_ENUM_UINT16             enNvUpdateFlag;          /* �Ƿ���Ҫ����NV������ģʽ�̶���FALSE */
}RRC_PHY_SET_WORK_MODE_REQ_STRU;

/*****************************************************************************
 �ṹ��    : RRC_PHY_SET_RAT_PRI_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����ģʽ���ȼ�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                          usOPID;                 /* ������ʶ */

    PHYITF_RAT_PRI_ENUM_UINT16          enWcdmaPri;                             /* WCDMA���ȼ� */
    PHYITF_RAT_PRI_ENUM_UINT16          enGsmPri;                               /* GSM���ȼ� */
    PHYITF_RAT_PRI_ENUM_UINT16          enLtePri;                               /* LTE���ȼ� */
    VOS_UINT16                          usReserve1;             /* �ֽڶ���*/
}RRC_PHY_SET_RAT_PRI_REQ_STRU;

/*****************************************************************************
 �ṹ��    : PHY_RRC_SET_WORK_MODE_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��RRC_PHY_SET_WORK_MODE_REQ_STRU�Ļظ�
 *****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16                enMsgID;          /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                usOPID;           /* ������ʶ */

    VOS_UINT16                                ausReserve1[2];
}PHY_RRC_SET_WORK_MODE_CNF_STRU;

/*****************************************************************************
 �ṹ��    : PHY_RRC_SET_RAT_PRI_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����RRC_PHY_SET_RAT_PRI_REQ_STRU�Ļظ�
 *****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16                enMsgID;          /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                usOPID;           /* ������ʶ */

    VOS_UINT16                                ausReserve1[2];
}PHY_RRC_SET_RAT_PRI_CNF_STRU;


/*****************************************************************************
 �ṹ��    : PHY_RRC_WCDMA_TIMING_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ������ϱ�W�Ķ�ʱ��Ϣ�����ݽṹ

*****************************************************************************/

typedef struct
{
    VOS_UINT16                          usSfn;
    VOS_UINT16                          usSlot;
    VOS_UINT16                          usChip;
    VOS_UINT16                          usReserve;
} PHY_RRC_WCDMA_TIMING_INFO_STRU;

/*****************************************************************************
 �ṹ��    : PHY_RRC_GSM_TIMING_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ������ϱ�G�Ķ�ʱ��Ϣ�����ݽṹ

*****************************************************************************/

typedef struct
{
    VOS_UINT32                          ulFn;
    VOS_UINT16                          usQb;
    VOS_UINT16                          usKvalue;
} PHY_RRC_GSM_TIMING_INFO_STRU;

/*****************************************************************************
 �ṹ��    : PHY_RRC_LTE_TIMING_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ������ϱ�L�Ķ�ʱ��Ϣ�����ݽṹ

*****************************************************************************/

typedef struct
{
    VOS_UINT16                          usSfn;                                  /* 0~1023 SFN���� */
    VOS_UINT16                          usSlot;                                 /* 0~9 ��֡���� */
    VOS_UINT16                          usChip;                                 /* 0~30719 ��֡�ڼ��� */
    VOS_UINT16                          usReserve;
} PHY_RRC_LTE_TIMING_INFO_STRU;

/*****************************************************************************
 �ṹ��    : PHY_RRC_RAT_TIMING_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ������ϱ���ͬ���뼼���Ķ�ʱ��Ϣ�����ݽṹ

*****************************************************************************/

typedef struct
{
    VOS_UINT32                          ulCtuTime;
    PHY_RRC_WCDMA_TIMING_INFO_STRU      stWTime;
    PHY_RRC_GSM_TIMING_INFO_STRU        stGTime;
    PHY_RRC_LTE_TIMING_INFO_STRU        stLTime;
} PHY_RRC_RAT_TIMING_INFO_STRU;


#define RRC_PHY_MAX_WCDMA_CELL_TIMING_NUM   (6)                                 /* WС����ʱ��Ϣ������� */


/*****************************************************************************
 �ṹ��    : PHY_RRC_WCDMA_CELL_FRAME_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : С��֡ͷ��Ϣ�����ݽṹ

*****************************************************************************/

typedef struct
{
    VOS_UINT16                          usSlotNum;                              /* С��֡ͷ��ʱ϶��Ϣ */
    VOS_UINT16                          usChipNum;                              /* С��֡ͷ����Ƭ��Ϣ */
} PHY_RRC_WCDMA_CELL_FRAME_INFO_STRU;

/*****************************************************************************
 �ṹ��    : PHY_RRC_WCDMA_CELL_TIMING_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : С��֡ͷ��Ϣ�����ݽṹ

*****************************************************************************/

typedef struct
{
    VOS_UINT16                          usPrimaryScramCode;                     /* С����������       */
    VOS_UINT16                          usReserve1;
    PHY_RRC_WCDMA_CELL_FRAME_INFO_STRU  stFrameInfo;                            /* ֡ͷ��Ϣ */
} PHY_RRC_WCDMA_CELL_TIMING_INFO_STRU;

/*****************************************************************************
 �ṹ��    : PHY_RRC_WCDMA_CELL_TIMING_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ������ϱ���ͬ���뼼���Ķ�ʱ��Ϣ�����ݽṹ

*****************************************************************************/

typedef struct
{
    VOS_UINT16                          usFreqInfo;
    VOS_UINT16                          usCellNum;
    PHY_RRC_WCDMA_CELL_TIMING_INFO_STRU astWCellInfo[RRC_PHY_MAX_WCDMA_CELL_TIMING_NUM];
} PHY_RRC_WCDMA_FREQ_CELL_TIMING_INFO_STRU;


/*****************************************************************************
 �ṹ��    : PHY_RRC_WCDMA_CELL_TIMING_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ������ϱ���ͬ���뼼���Ķ�ʱ��Ϣ�����ݽṹ

*****************************************************************************/
typedef struct
{
    VOS_UINT16                                  usFreqNum;
    VOS_UINT16                                  usReserve1;
    PHY_RRC_WCDMA_FREQ_CELL_TIMING_INFO_STRU    astWCellInfo[RRC_PHY_MAX_SLAVE_WCDMA_CARRIER_NUM];
} PHY_RRC_WCDMA_FREQ_TIMING_STRU;


/*****************************************************************************
 �ṹ��    : PHY_RRC_WCDMA_CELL_TIMING_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ������ϱ�С����ʱ��Ϣ�����ݽṹ

*****************************************************************************/

typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                                /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                          usOPID;                                 /* ������ʶ */
    PHY_RRC_RAT_TIMING_INFO_STRU        stRatTiming;                            /* ��ͬ���뼼���Ķ�ʱ��ϵ */
    PHY_RRC_WCDMA_FREQ_TIMING_STRU      stWCellTiming;                          /* WС���Ķ�ʱ��ϵ */
}PHY_RRC_WCDMA_CELL_TIMING_IND_STRU;


/*****************************************************************************
 �ṹ��    : PHY_RRC_WCDMA_TIMING_ERROR_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ������ϱ�С����ʱ������Ϣ�����ݽṹ

*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                                /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                          usOPID;                                 /* ������ʶ */
    VOS_UINT32                          ulReserved;
}PHY_RRC_WCDMA_TIMING_ERROR_IND_STRU;


/*****************************************************************************
 �ṹ��    : RRC_PHY_CAMPED_MAINCELL_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��С��פ��������Ϣ�����ݽṹ
             PHY���յ����ԭ��֮�������ԭ��PHY_RRC_CAMPED_MAINCELL_CNF
             ��RRCȷ�ϣ���������PCPICH���ı�ϵͳ��֡��ʱ��
*****************************************************************************/

typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                  /*_H2ASN_Skip*/  /* ԭ������*/
    VOS_UINT16                          usOPID;                   /* ������ʶ */
    VOS_INT16                           sFreqInfo;                /* [0,16383]CELL ��Ƶ�� */
    VOS_INT16                           sPriScramCode;            /* [0, 511]������ */
    VOS_UINT16                          usFreqBandNo;             /* Ƶ�κ�:1,2,3,4,5,6*/
    VOS_UINT16                          usTxRxFreqSeparation;     /* �շ�Ƶ��*/
    PHYITF_BOOL_ENUM_UINT16             enCellFrameExistFlg;      /* С��֡ͷ���ڵı�� */
    PHYITF_TX_DIVER_IND_ENUM_UINT16     enPcpichTDIndicator;      /* L2W�л�ʱPcpich�ּ���ʽ */

    PHY_RRC_RAT_TIMING_INFO_STRU        stRatTiming;              /* ��ͬ���뼼���Ķ�ʱ��ϵ */
    PHY_RRC_WCDMA_CELL_FRAME_INFO_STRU  stCellFrameInfo;          /* פ��С���Ķ�ʱ��Ϣ */
}RRC_PHY_CAMPED_MAINCELL_REQ_STRU;

/*****************************************************************************
 �ṹ��    : RRC_PHY_PS_CS_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : DSP�͹������󣬵�����CS���ڵ�ʱ��֪ͨDSP����ϢָʾenCsExistFlgΪTRUE,
 CS�����ڵ�ʱ��֪ͨ�����enCsExistFlgΪFALSE;�Ƿ�ͬʱ����cs��ps���������ͨ���������λ����ж�
 WRR��ʼ����PSʱ�ɲ���Ҫ֪ͨDSP��DSP��ʼ״̬���Ƿ�cs only;
 ��D���ŵ�����ʱ��������յ�����Ϣ������
 �뿪D̬ʱ��������Լ�����WAS����Ҫ֪ͨҵ�����͡�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16              enMsgID;                            /* ԭ������ */ /*_H2ASN_Skip*/
    PHYITF_BOOL_ENUM_UINT16                 enCsExistFlg;                       /* PS_TRUE,��ʾ��CS����;PS_FALSE��ʾ����CS������ */
    PHYITF_BOOL_ENUM_UINT16                 enPsExistFlg;                       /* PS_TRUE,��ʾ��PS����;PS_FALSE��ʾ����PS������ */
    VOS_UINT16                              usReserve;
}RRC_PHY_CS_PS_IND_STRU;

/*****************************************************************************
 �ṹ��    : RRC_PHY_INTRA_DETECT_CELL_SEARCH_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����һ�����޺�WAS֪ͨDSP������ֹͣ����������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16              enMsgID;                            /* ԭ������ */ /*_H2ASN_Skip*/
    PHYITF_BOOL_ENUM_UINT16                 enDetectCellSearchFlg;              /* PS_TRUE,��ʾ��������������С��;PS_FALSE��ʾֹͣ������С������ */
}RRC_PHY_INTRA_DETECT_CELL_SEARCH_IND_STRU;

/*****************************************************************************
 �ṹ��    : PHYITF_SLAVE_MEAS_CELL_INFO_ITEM_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : WΪ��ģʱ��LTE����WCDMAС����Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usFreqInfo;                             /* Ƶ���Ƶ����Ϣ */

    VOS_UINT16                          usFreqBandNo;                           /* Ƶ�κ�:1,2,3,4,5,6*/
    VOS_UINT16                          usTxRxFreqSeparation;                   /* �շ�Ƶ��*/
    VOS_UINT16                          usDetectedCellMeasureInd;               /* �Ƿ���Ҫ��������Detected����С�� */
    VOS_UINT16                          usReserve1;

    VOS_UINT16                          usCellNum;                              /* һ��Ƶ���µ�С����Ŀ */
    VOS_UINT16                          ausPrimaryScramCode[RRC_PHY_MAX_SLAVE_WCDMA_CELL_PER_FREQ_NUM];    /* С������Ϣ               */
}PHYITF_SLAVE_MEAS_CELL_INFO_ITEM_STRU;

/*****************************************************************************
 �ṹ��    : PHYITF_SLAVE_WCDMA_CELL_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : WΪ��ģʱ��LTE����WCDMAС����Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                  usFreqNum;                      /* ��Ҫ������ WƵ������ */
    VOS_UINT16                                  usReserve1;
    PHYITF_SLAVE_MEAS_CELL_INFO_ITEM_STRU       astSlaveMeasCellInfo[RRC_PHY_MAX_SLAVE_WCDMA_CARRIER_NUM];
}PHYITF_SLAVE_WCDMA_CELL_INFO_STRU;

/*****************************************************************************
 �ṹ��    : RRC_PHY_SLAVE_MEASURE_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : W��ģ����������Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip */
    RRC_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* ԭ������ */ /*_H2ASN_Skip */
    VOS_UINT16                                  usOPID;                         /* ������ʶ */
    PHYITF_BOOL_ENUM_UINT16                     enIdleStateFlag;                /* ��ģ�Ƿ�����IDLE̬�ı�� */
    PHYITF_MEASURE_COMMAND_ENUM_UINT16          enCommand;                      /* ��������,0:�ͷţ�1:��������ģ����û��MODIFY */
    PHYITF_SLAVE_WCDMA_CELL_INFO_STRU           stSlaveWcdmaCellEntity;         /* WΪ��ģʱ��LTE�²���WС�������� */
}RRC_PHY_SLAVE_MEASURE_REQ_STRU;

/*****************************************************************************
 �ṹ��    : PHY_RRC_SLAVE_MEASURE_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��ģ����������Ӧ��Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;                /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                          usOPID;                 /* ������ʶ */
}PHY_RRC_SLAVE_MEASURE_CNF_STRU;

/*****************************************************************************
 �ṹ��    : PHYITF_SLAVE_CELL_MEASURE_RESULT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��ģÿ��С���Ĳ��������Ϣ
 *****************************************************************************/
typedef struct
{
    VOS_UINT16                          usPrimaryScramCode;                     /* С����������                             */
    VOS_INT16                           sCpichRscp;                             /* CPICH RSCP����ֵ                         */
    VOS_INT16                           sCpichEcN0;                             /* CPICH EcN0����ֵ                         */
    VOS_UINT16                          usSfn;
} PHYITF_SLAVE_CELL_MEASURE_RESULT_STRU;

/*****************************************************************************
 �ṹ��    : PHYITF_INTER_FREQ_REPORT_ITEM_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��ģ�������
 *****************************************************************************/
typedef struct
{
    VOS_UINT16                                usFreqInfo;                       /* Ƶ����Ϣ */
    VOS_INT16                                 sCarrierRSSI;                     /* UtraCarrierRSSI����ֵ */
    VOS_UINT16                                usCellNum;                        /* ��Ƶ���µ�С������Ŀ  */
    VOS_UINT16                                usReserve1;
    PHYITF_SLAVE_CELL_MEASURE_RESULT_STRU     astInterFreqCell[PHY_RRC_MAX_REPORT_EACH_FREQ_CELL_NUM];     /* Ƶ��С���Ĳ������ */
}PHYITF_SLAVE_MEAS_REPORT_ITEM_STRU;

/*****************************************************************************
 �ṹ��    : PHYITF_SLAVE_WCDMA_MEAS_REPORT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : W��Ϊ��ģʱWCDMA��������
 *****************************************************************************/
typedef struct
{
    VOS_UINT16                          usFreqNum;                              /* �����а�����Ƶ����Ŀ */
    VOS_UINT16                          usReserve1;
    PHYITF_SLAVE_MEAS_REPORT_ITEM_STRU  astInterFreqReport[RRC_PHY_MAX_SLAVE_WCDMA_CARRIER_NUM];
}PHYITF_SLAVE_WCDMA_MEAS_REPORT_STRU;

/*****************************************************************************
 �ṹ��    : PHY_RRC_SLAVE_MEASURE_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��ģ�����ϱ���Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /*_H2ASN_Skip*/   /* ԭ������ */
    VOS_UINT16                                  usOPID;                         /* ������ʶ */
    PHYITF_SLAVE_WCDMA_MEAS_REPORT_STRU         stSlaveWcdmaMeasRpt;
}PHY_RRC_SLAVE_MEASURE_IND_STRU;

/*****************************************************************************
 �ṹ��    : RRC_PHY_BSIC_VERIFIED_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ֪ͨWPHY��ʼGSM��BSIC��֤
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;            /*_H2ASN_Skip*/  /* ԭ������*/
    VOS_UINT16                          usOPID;
} RRC_PHY_BSIC_VERIFIED_REQ_STRU;

/*****************************************************************************
 �ṹ��    : PHY_RRC_BSIC_VERIFIED_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : WPHY�Կ�ʼGSM��BSIC��֤����Ӧ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16          enMsgID;            /* ԭ������ */    /*_H2ASN_Skip*/
    VOS_UINT16                          usOPID;
} PHY_RRC_BSIC_VERIFIED_CNF_STRU;

/*****************************************************************************
 �ṹ��    : RRC_PHY_W_BG_SEARCH_OTHER_RAT_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : WΪ��ģʱ��������L����G֪ͨWPHY��LPHY����GPHY����ʱ�������Ϣ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16                                enMsgID;          /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                                usOPID;           /* ������ʶ */
    PHYITF_W_BG_SEARCH_OTHER_RAT_CMD_ENUM_UINT16              enCtrlCmd;        /* ��ģ�������� */
    PHYITF_W_BG_SEARCH_RAT_ENUM_UINT16                        enSrchRat;        /* �����ѵĴ�ģ����ģʽָʾ */
}RRC_PHY_W_BG_SEARCH_OTHER_RAT_REQ_STRU;

/*****************************************************************************
 �ṹ��    : PHY_RRC_W_BG_SEARCH_OTHER_RAT_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : WΪ��ģʱ��������L����G֪ͨWPHY��LPHY����GPHY����ʱ�������Ӧ��Ϣ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16                                enMsgID;          /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                                usOPID;           /* ������ʶ */
    PHYITF_W_BG_SEARCH_OTHER_RAT_CMD_ENUM_UINT16              enCtrlCmd;        /* ��ģ�������� */
    VOS_UINT16                                                usReserve;
}PHY_RRC_W_BG_SEARCH_OTHER_RAT_CNF_STRU;

/*****************************************************************************
 �ṹ��    : PHY_RRC_RADIO_RESOURCE_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ָʾ��Դ�Ƿ���ñ�־
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16 enMsgID;                                         /* ԭ������ */ /*_H2ASN_Skip*/
    PHYITF_BOOL_ENUM_UINT16 enAvailableFlg;                                     /* ��Դ���ñ�־ */
}PHY_RRC_RADIO_RESOURCE_IND_STRU;
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RRC_PHY_MSG_ID_ENUM_UINT16              enMsgID;                            /* ԭ������ */ /*_H2ASN_Skip*/
    PHYITF_BOOL_ENUM_UINT16                 enRfShareFlag;                      /* _VALID:����RF(DSDS˫��ģʽ)��_INVALID:��ռRF(��DSDS˫��ģʽ) */
}RRC_PHY_AS_ACTIVE_DSDS_STATUS_IND_STRU;


/*****************************************************************************
  10 ��������
*****************************************************************************/
extern VOS_VOID   WAS_RRC_GetCurSfnFromPhy(VOS_UINT16 usCurSfn);

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

#endif /* end of RrcPhyInterface.h */

