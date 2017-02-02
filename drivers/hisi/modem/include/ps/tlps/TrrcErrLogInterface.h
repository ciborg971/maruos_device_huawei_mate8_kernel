

#ifndef __TRRCERRLOGINTERFACE_H__
#define __TRRCERRLOGINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include "omerrorlog.h"
#pragma pack(4)

/*****************************************************************************
  2 macro
*****************************************************************************/
#include  "vos.h"
#include "omerrorlog.h"
#include "omringbuffer.h"
/*****************************************************************************
  3 Massage Declare
*****************************************************************************/
/* TDS���������������ϱ���ǿ3������ */
#define TRRC_APP_MAX_NCELL_NUM                     (3)
#define TRRC_OM_MAX_TDS_CELLS_NUM_WITHOUT_LTE_NCELL         (5)
/*****************************************************************************
  4 Enum
*****************************************************************************/
/*****************************************************************************
 ö����    : TRRC_ERRORLOG_ALARM_ID_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : ERRORLOG ALARM_ID����
*****************************************************************************/
enum TRRC_ERRORLOG_ALARM_ID_ENUM
{
    TRRC_ERRORLOG_ALARM_ID_EST_FAIL           =1,   /* ����ʧ��*/
    TRRC_ERRORLOG_ALARM_ID_RB_FAIL,                 /* RB����ʧ�� */
    TRRC_ERRORLOG_ALARM_ID_RBREC_FAIL,              /* RB������ʧ�� */
    TRRC_ERRORLOG_ALARM_ID_CELLUPDATE_FAIL,         /* CELLUPDATEʧ�� */
    TRRC_ERRORLOG_ALARM_ID_AREA_LOST,               /* ���� */
    TRRC_ERRORLOG_ALARM_ID_INTEGRITY_FAIL,          /* ��������֤ʧ��*/
    TRRC_ERRORLOG_ALARM_ID_ASN_RSLT_FAIL,           /* asn������� */
    TRRC_ERRORLOG_ALARM_ID_MEAS_CTRL_FAIL,          /* �������ô��� */
    TRRC_ERRORLOG_ALARM_ID_CS_HO_FAIL,              /* CS�л�ʧ�ܸ澯 */
    TRRC_ERRORLOG_ALARM_ID_CS_HO_EXP,               /* CS�л���ʱ�澯 */
    TRRC_ERRORLOG_ALARM_ID_RL_FAIL,                 /* ������·ʧ�ܸ澯 */
    TRRC_ERRORLOG_ALARM_ID_BUFF_OVER_FLOW,          /* ��������澯*/
    TRRC_ERRORLOG_ALARM_ID_NOT_TO_LTE,               /*��ʱ�䲻��LTE�澯*/
    TRRC_ERRORLOG_ALARM_ID_CS_SIGNAL_REL,               /*cs�ͷŸ澯*/
    TRRC_ERRORLOG_ALARM_ID_BUTT
};
typedef VOS_UINT16  TRRC_ERRORLOG_ALARM_ID_ENUM_UINT16;

/*****************************************************************************
 ö����    : TRRC_ERRORLOG_ALARM_TYPE_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : ���ø澯����ö�ٶ���
*****************************************************************************/
enum TRRC_ERRORLOG_ALARM_TYPE_ENUM
{
    TRRC_ERRORLOG_ALARM_TYPE_COMMUNICATION             = 1 ,      /* ��ʾͨ��: ����ȷ�ϴ�1��ʼ��GUTL�ֱ����*/
    TRRC_ERRORLOG_ALARM_TYPE_TRANSACTION_QULITY            ,      /* ��ʾҵ������ */
    TRRC_ERRORLOG_ALARM_TYPE_PROCESS_ERROR                 ,      /* ��ʾ������� */
    TRRC_ERRORLOG_ALARM_TYPE_EQIPMENT_ERROR                ,      /* ��ʾ�豸���� */
    TRRC_ERRORLOG_ALARM_TYPE_ENVIR_ERROR                   ,      /* ��ʾ�������� */
    TRRC_ERRORLOG_ALARM_TYPE_BUTT
};
typedef VOS_UINT16  TRRC_ERRORLOG_ALARM_TYPE_ENUM_UINT16;


/*****************************************************************************
 ö����    : RRC_APP_ERROR_CODE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : RRC����������
*****************************************************************************/
enum TRRC_APP_ERROR_CODE_ENUM
{
    TRRC_APP_RB_PROTOCOL_CHECK_ERR            = 0,   /* RB����ʧ��--Protocol���ʧ�� */
    TRRC_APP_RB_TRANSACTION_CHECK_ERR,               /* RB����ʧ��--Transaction ID���ʧ�� */
    TRRC_APP_RB_INTEGRITY_CHECK_ERR,                 /* RB����ʧ��--Integrity���ʧ�� */

    TRRC_APP_RBREC_PROTOCOL_CHECK_ERR         = 10,  /* RB������ʧ��--Protocol���ʧ�� */
    TRRC_APP_RBREC_TRANSACTION_CHECK_ERR,            /* RB������ʧ��--Transaction ID���ʧ�� */
    TRRC_APP_RBREC_INTEGRITY_CHECK_ERR,              /* RB������ʧ��--Integrity���ʧ�� */

    TRRC_APP_CELLUPDATECNF_PROTOCOL_CHECK_ERR     =20,  /* С������ʧ��--Protocol���ʧ�� */
    TRRC_APP_CELLUPDATECNF_TRANSACTION_CHECK_ERR,       /* С������ʧ��--Transaction ID���ʧ�� */
    TRRC_APP_CELLUPDATECNF_INTEGRITY_CHECK_ERR,         /* С������ʧ��--Integrity���ʧ�� */

    TRRC_APP_EST_T300_ERR                         =30,  /* ��������N300ʱ��¼ */
    TRRC_APP_EST_CS_ACC_PROBABILITY_ERR,                /* CS����AC�ȼ��ж�ʧ�� */
    TRRC_APP_EST_PS_ACC_PROBABILITY_ERR,                /* PS����AC�ȼ��ж�ʧ�� */

    TRRC_APP_EST_AREA_LOST_ERR                    =40,  /* RRC���� */
    TRRC_APP_ASN_RLST_ERR,                              /* ASN�������� */
    TRRC_APP_AM_INTEGRITY_CHECK_ERR,                    /* AM���������Լ��ʧ�� */
    TRRC_APP_UM_INTEGRITY_CHECK_ERR,                    /* UM���������Լ��ʧ�� */

    TRRC_APP_MEAS_CTRL_PROTOCOL_CHECK_ERR         =50,  /* ��������ʧ��--Protocol���ʧ�� */
    TRRC_APP_MEAS_CTRL_TRANSACTION_CHECK_ERR,           /* ��������ʧ��--Transaction ID���ʧ�� */

    TRRC_APP_HO_FAIL_ERR                          =60,  /* �л�ʧ�� */
    TRRC_APP_HO_TIMER_EXP_ERR,                          /* �л���ʱ */

    TRRC_APP_RL_FAIL_ERR                          =70,  /* ������·ʧ�� */

    TRRC_APP_CS_SIGINAL_REL                       =80,  /* cs����·�ͷ� */

    TRRC_APP_ERR_CODE_BUTT
};
typedef VOS_UINT8 TRRC_APP_ERROR_CODE_ENUM_UINT8;

/*****************************************************************************
 ö����    : TRRC_APP_FTM_TYPE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ����ģʽ�ϱ����ͣ����������ϱ������º��ϱ���
*****************************************************************************/
enum TRRC_APP_FTM_TYPE_ENUM
 {
    TRRC_APP_FTM_PERIOD_INFO,     /* �������ϱ��Ĺ���ģʽ��Ϣ��ĿǰIdle״̬�ϱ�����ΪDRX���ڣ�Connected״̬������Ϊ1�� */
    TRRC_APP_FTM_CHANGE_INFO,     /* ���º��ϱ��͵Ĺ���ģʽ��Ϣ������ϱ����������� */
    TRRC_APP_FTM_INFO_BUIT
 };
 typedef VOS_UINT32 TRRC_APP_FTM_TYPE_ENUM_UINT32;

 /*********************************************************
 ö����    : TRRC_APP_FTM_CHANGE_INFO_TYPE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ����ϱ�����ģʽ���Ͷ���
**********************************************************/
 enum TRRC_APP_FTM_CHANGE_INFO_TYPE_ENUM
 {
     TRRC_APP_FTM_CHANGE_CELL_INFO,      /* RRCפ��С����Ϣ���仯���ϱ����л�����ѡ��ɺ��ϱ� */
     TRRC_APP_FTM_CHANGE_STATE_INFO,     /* RRC״̬��Ϣ���仯���ϱ� */

     TRRC_APP_FTM_CHANGE_BUTT
 };
  typedef VOS_UINT32 TRRC_APP_FTM_CHANGE_INFO_TYPE_ENUM_UINT32;

 /*****************************************************************************
  ö����    : TRRC_APP_PROTOCOL_STATE_ENUM
  Э����  :
  ASN.1���� :
  ö��˵��  : TRRCЭ��״̬
 *****************************************************************************/
 enum TRRC_APP_PROTOCOL_STATE_ENUM
 {
     TRRC_APP_PROTOCOL_STATE_IDLE                           = 0,                /* IDLE̬ */
     TRRC_APP_PROTOCOL_STATE_CELL_PCH                          ,                /* CELL_PCH̬ */
     TRRC_APP_PROTOCOL_STATE_URA_PCH                           ,                /* URA_PCH̬ */
     TRRC_APP_PROTOCOL_STATE_CELL_FACH                         ,                /* CELL_FACH̬ */
     TRRC_APP_PROTOCOL_STATE_CELL_DCH                          ,                /* CELL_DCH̬ */

     TRRC_APP_PROTOCOL_STATE_BUTT
 };
 typedef VOS_UINT8 TRRC_APP_PROTOCOL_STATE_ENUM_UINT8;

 /*****************************************************************************
  ö����     :TRRC_APP_GRR_BANDINDICATOR_ENUM
  Э����  :
  ASN.1����   :
  ö��˵�� : 2GС��Ƶ��ָʾ
 *****************************************************************************/
 enum TRRC_APP_GRR_BANDINDICATOR_ENUM
 {
     TRRC_APP_GRR_BANDINDICATOR_DCS1800       = 0,
     TRRC_APP_GRR_BANDINDICATOR_PCS1900       ,

     TRRC_APP_GRR_BANDINDICATOR_BUTT
 };
 typedef VOS_UINT16    TRRC_APP_GRR_BANDINDICATOR_ENUM_UINT16;

  /*****************************************************************************
  ö����     :TRRC_APP_RRC_STATE_ENUM
  Э����  :
  ASN.1����   :
  ö��˵�� : RRC״̬���ڲ�״̬����Э��״̬
 *****************************************************************************/
 enum TRRC_APP_RRC_STATE_ENUM
 {
    TRRC_APP_NUL,   // 0x00  /* TTRRC_APP_CHANGE FOR ע��: ����ǰ���Ͷ�ʧ����*/
    TRRC_APP_SEL,   // 0x01
    TRRC_APP_IDL,   // 0x02
    TRRC_APP_RES,   // 0x03
    TRRC_APP_ACC,   // 0x04
    TRRC_APP_FCH,   // 0x05
    TRRC_APP_DCH,   // 0x06
    TRRC_APP_PCH,   // 0x07
    TRRC_APP_WCA,   // 0x08
    TRRC_APP_REL,   // 0x09
    TRRC_APP_CNF,   // 0x0A
    TRRC_APP_LIM,   // 0x0b
    TRRC_APP_SNW,   // 0x0c
    TRRC_APP_INACTIVE,
    TRRC_APP_PREDEF,
    TRRC_APP_PEND,
    TRRC_APP_RATHO,
    TRRC_APP_WAIT,
    TRRC_APP_POWEROFF
 };
typedef VOS_UINT8 TRRC_APP_RRC_STATE_ENUM_UINT8;
/*****************************************************************************
 ö����    : TRRC_FLOW_CTRL_TYPE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ���̿�������ö��
             �޸�ö��ʱ��Ҫע�⣬ʧ������ȡֵ = ��������ȡֵ+1
 ����: LRRC_FLOW_CTRL_TYPE_G2L_RESEL_FAIL = LRRC_FLOW_CTRL_TYPE_G2L_START_RESEL + 1
*****************************************************************************/
enum TRRC_APP_FLOW_CTRL_TYPE_ENUM
{
    TRRC_APP_FLOW_CTRL_TYPE_T2T_NORMAL            = 0,     /* TDS�����̱߽� */
    TRRC_APP_FLOW_CTRL_TYPE_T2T_NORMAL_IDL_SYS_UPDATA,     /* TDS������IDL̬ϵͳ��Ϣ���²����������� */
    TRRC_APP_FLOW_CTRL_TYPE_T2T_NORMAL_PCH_SYS_UPDATA,     /* TDS������PCH̬ϵͳ��Ϣ���²����������� */
    TRRC_APP_FLOW_CTRL_TYPE_T2T_NORMAL_ENTER_PCH,          /* TDS�����̴�����״̬��DCH/FACH->PCH̬ת������ */
    TRRC_APP_FLOW_CTRL_TYPE_T2T_NORMAL_ENTER_FCH,          /* TDS�����̴�����״̬��IDL->FCH̬ת������ */
    TRRC_APP_FLOW_CTRL_TYPE_T2T_NORMAL_ENTER_DCH,          /* TDS�����̴�����״̬��IDL->DCH̬ת������ */
    TRRC_APP_FLOW_CTRL_TYPE_T2T_RES_ENTER_FCH,             /* TDS��������ѡ�����FCH״̬���� */
    /* TL RESEL PHASE2 begin */
    TRRC_APP_FLOW_CTRL_TYPE_T2T_NAS_SUSPEND,               /* TDS������NAS�������� */
    /* TL RESEL PHASE2 end */
    TRRC_APP_FLOW_CTRL_TYPE_T2T_NORMAL_END,                /* TDS�����̱߽� */
    TRRC_APP_FLOW_CTRL_TYPE_G2T_START_RESEL,               /* G->T��ʼ��ѡ */
    TRRC_APP_FLOW_CTRL_TYPE_G2T_RESEL_FAIL,                /* G->T��ѡʧ�� */
    TRRC_APP_FLOW_CTRL_TYPE_G2T_STOP_RESEL,                /* G->Tֹͣ��ѡ */

    TRRC_APP_FLOW_CTRL_TYPE_T2G_START_RESEL,               /* T->G��ʼ��ѡ */
    TRRC_APP_FLOW_CTRL_TYPE_T2G_RESEL_FAIL,                /* T->G��ѡʧ�� */

    TRRC_APP_FLOW_CTRL_TYPE_G2T_MEAS,                      /* G->T �������� */
    /* TL RESEL BEGIN */
    TRRC_APP_FLOW_CTRL_TYPE_L2T_START_RESEL,               /* L->T��ʼ��ѡ */
    TRRC_APP_FLOW_CTRL_TYPE_L2T_RESEL_FAIL,                /* L->T��ѡʧ�� */
    TRRC_APP_FLOW_CTRL_TYPE_L2T_STOP_RESEL,                /* L->Tֹͣ��ѡ */

    TRRC_APP_FLOW_CTRL_TYPE_L2T_IDLE_MEAS,                 /* L->T IDLE�������� */
    TRRC_APP_FLOW_CTRL_TYPE_L2T_CONN_MEAS,                 /* L->T CONN�������� */
    TRRC_APP_FLOW_CTRL_TYPE_L2T_RELALL,                    /* L->T RELALL */

    TRRC_APP_FLOW_CTRL_TYPE_T2L_START_RESEL,               /* T->L��ʼ��ѡ */
    TRRC_APP_FLOW_CTRL_TYPE_T2L_RESEL_FAIL,                /* T->L��ѡʧ�� */

	/* TOER_HO BEGIN */
    TRRC_APP_FLOW_CTRL_TYPE_G2T_START_CCO,                 /* G->T��ʼCCO */
    TRRC_APP_FLOW_CTRL_TYPE_G2T_CCO_FAIL,                  /* G->T CCOʧ�� */
    TRRC_APP_FLOW_CTRL_TYPE_G2T_STOP_CCO,                  /* G->TֹͣCCO */

    TRRC_APP_FLOW_CTRL_TYPE_T2G_START_CCO,                 /* T->G��ʼCCO */
    TRRC_APP_FLOW_CTRL_TYPE_T2G_CCO_FAIL,                  /* T->G CCOʧ�� */

    TRRC_APP_FLOW_CTRL_TYPE_T2L_START_HO,                  /* T->L��ʼ�л� */
    TRRC_APP_FLOW_CTRL_TYPE_T2L_HO_FAIL,                   /* T->L�л�ʧ�� */

    TRRC_APP_FLOW_CTRL_TYPE_L2T_START_HO,                  /* L->T��ʼHO */
    TRRC_APP_FLOW_CTRL_TYPE_L2T_HO_FAIL,                   /* L->T HOʧ�� */
    TRRC_APP_FLOW_CTRL_TYPE_L2T_STOP_HO,                   /* L->TֹͣHO */

    TRRC_APP_FLOW_CTRL_TYPE_T2G_START_HO,                  /* T->G��ʼ�л� */
    TRRC_APP_FLOW_CTRL_TYPE_T2G_HO_FAIL,                   /* T->G�л�ʧ�� */

    TRRC_APP_FLOW_CTRL_TYPE_G2T_START_HO,                  /* G->T��ʼHO */
    TRRC_APP_FLOW_CTRL_TYPE_G2T_HO_FAIL,                   /* G->T HOʧ�� */
    TRRC_APP_FLOW_CTRL_TYPE_G2T_STOP_HO,                   /* G->TֹͣHO */
    /* TOER_HO END */

    TRRC_APP_FLOW_CTRL_TYPE_T2T_SYSCFG_SUSPEND,            /* TDS���������ҹ������� */
    /* TL RESEL end */
    /* TL Redir begin */
    TRRC_APP_FLOW_CTRL_TYPE_T2L_REDIR,                     /* T->L�ض��� */
    /* TL Redir end */
    LRRC_APP_FLOW_CTRL_TYPE_L2T_REDIR_FAIL,                /* L->W�ض���ʧ�� */

    TRRC_APP_FLOW_CTRL_TYPE_L2T_STOP_REDIR,                /* L->T�ض���ֹͣ */

    /*׼FR����begin*/
    TRRC_APP_FLOW_CTRL_TYPE_T2G_REDIR,                     /* T->G�ض��� */

    TRRC_APP_FLOW_CTRL_TYPE_G2T_REDIR_FAIL,                /* G->T�ض���ʧ�� */

    TRRC_APP_FLOW_CTRL_TYPE_G2T_STOP_REDIR,                /* G->T�ض���ֹͣ */
    /*׼FR����end*/

    TRRC_APP_FLOW_CTRL_TYPE_BUTT
};
typedef VOS_UINT16 TRRC_APP_FLOW_CTRL_TYPE_ENUM_UINT16;
/*****************************************************************************
 ö����    : TRRC_APP_EST_SIGNALLING_TYPE
 Э����  :
 ASN.1���� :
 ö��˵��  : ��·����
*****************************************************************************/

enum  TRRC_APP_EST_SIGNALLING_TYPE
{
  TRRC_APP_NO_SIGNALLING_CONNECTION = 0,
  TRRC_APP_SIGNALLING_CONNECTION_ESTABLISHING,
  TRRC_APP_SIGNALLING_CONNECTION_ESTABLISHED
};

typedef VOS_UINT32 TRRC_APP_EST_SIGNALLING_TYPE_UINT32;
/*****************************************************************************
 ö����    : TRRC_APP_EST_CAUSE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : RRMM_EST_REQ_STRU��Ϣ�е�enEstCause����25.331Э�鶨�屣��һ��
*****************************************************************************/
enum TRRC_APP_EST_CAUSE_ENUM
{
    TRRC_APP_EST_CAUSE_ORIGIN_CONVERSAT_CALL             = 0,
    TRRC_APP_EST_CAUSE_ORIGIN_STREAM_CALL                = 1,
    TRRC_APP_EST_CAUSE_ORIGIN_INTERACT_CALL              = 2,
    TRRC_APP_EST_CAUSE_ORIGIN_BACKGROUND_CALL            = 3,
    TRRC_APP_EST_CAUSE_ORIGIN_SUBSCRIB_TRAFFIC_CALL      = 4,
    TRRC_APP_EST_CAUSE_TERMINAT_CONVERSAT_CALL           = 5,
    TRRC_APP_EST_CAUSE_TERMINAT_STREAM_CALL              = 6,
    TRRC_APP_EST_CAUSE_TERMINAT_INTERACT_CALL            = 7,
    TRRC_APP_EST_CAUSE_TERMINAT_BACKGROUND_CALL          = 8,
    TRRC_APP_EST_CAUSE_EMERGENCY_CALL                    = 9,
    TRRC_APP_EST_CAUSE_INTER_RAT_CELL_RESELECT           = 10,
    TRRC_APP_EST_CAUSE_INTER_RAT_CELL_CHANGE_ORDER       = 11,
    TRRC_APP_EST_CAUSE_REGISTRATION                      = 12,
    TRRC_APP_EST_CAUSE_DETACH                            = 13,
    TRRC_APP_EST_CAUSE_ORIGIN_HIGH_PRIORITY_SIGNAL       = 14,
    TRRC_APP_EST_CAUSE_ORIGIN_LOW_PRIORITY_SIGNAL        = 15,
    TRRC_APP_EST_CAUSE_CALL_RE_ESTABLISH                 = 16,
    TRRC_APP_EST_CAUSE_TERMINAT_HIGH_PRIORITY_SIGNAL     = 17,
    TRRC_APP_EST_CAUSE_TERMINAT_LOW_PRIORITY_SIGNAL      = 18,
    TRRC_APP_EST_CAUSE_TERMINAT_CAUSE_UNKNOWN            = 19,
    TRRC_APP_EST_CAUSE_BUTT
};
typedef VOS_UINT32 TRRC_APP_EST_CAUSE_ENUM_UINT32;

/* ErrorLog����������Ϣbegin */
/*****************************************************************************
 ö����    : TDS_APP_FREQ_BAND_LIST_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : TDS band��Ϣö��ֵ
*****************************************************************************/
enum TDS_APP_FREQ_BAND_LIST_ENUM
{
    TDS_APP_FREQ_BAND_NONE      = 0x00,
    TDS_APP_FREQ_BAND_A         = 0x01,         /* Ƶ�㷶Χ: 9504~9596  10054~10121 */
    TDS_APP_FREQ_BAND_B         = 0x02,         /* Ƶ�㷶Χ: 9254~9546  9654~9946 */
    TDS_APP_FREQ_BAND_C         = 0x04,         /* Ƶ�㷶Χ: 9554~9646 */
    TDS_APP_FREQ_BAND_D         = 0x08,         /* Ƶ�㷶Χ: 12854~13096 */
    TDS_APP_FREQ_BAND_E         = 0x10,         /* Ƶ�㷶Χ: 11504~11996 */
    TDS_APP_FREQ_BAND_F         = 0x20,         /* Ƶ�㷶Χ: 9404~9596 */
    TDS_APP_FREQ_BAND_BUTT
};
typedef VOS_UINT8  TDS_APP_FREQ_BAND_LIST_ENUM_UINT8;

/*****************************************************************************
 ö����    : TDS_APP_ERR_LOG_RAT_TYPE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ���뼼��ö��ֵ�����ݼ������GUTL���Զ��嵫���ָ���ʽ˳��һ��
*****************************************************************************/
enum TDS_APP_ERR_LOG_RAT_TYPE_ENUM
{
    TDS_APP_ERR_LOG_RAT_TYPE_GSM      = 1,      /* GSM ���뼼��*/
    TDS_APP_ERR_LOG_RAT_TYPE_WCDMA,             /* WCDMA ���뼼��*/
    TDS_APP_ERR_LOG_RAT_TYPE_LTE,               /* LTE ���뼼��*/
    TDS_APP_ERR_LOG_RAT_TYPE_TDS,               /* TDS ���뼼��*/
    TDS_APP_ERR_LOG_RAT_TYPE_BUTT
};
typedef VOS_UINT8  TDS_APP_ERR_LOG_RAT_TYPE_ENUM_UINT8;

/*****************************************************************************
 ö����    : TDS_APP_ERR_LOG_AREA_LOST_CAUSE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : �����ϱ�ԭ��ֵ
*****************************************************************************/
enum TDS_APP_ERR_LOG_AREA_LOST_CAUSE_ENUM
{
    TDS_APP_ERR_LOG_AREA_LOST_BUTT = 1         /* ��ǰԤ����ö��ֵ*/
};
typedef VOS_UINT8  TDS_APP_ERR_LOG_AREA_LOST_CAUSE_ENUM_UINT8;
/* ErrorLog����������Ϣend */
/* Seattle Begin */
/*****************************************************************************
 ö����    : TDS_ERR_LOG_CS_HANDOVER_FAIL_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : �л�ʧ�ܵ�ԭ��ֵ
*****************************************************************************/
enum TDS_ERR_LOG_CS_HANDOVER_FAIL_ENUM
{
    ERR_TRRC_GRR_HANDOVER_RESULT_FREQ_NOT_IMPLEMENTED =1,
    ERR_TRRC_GRR_HANDOVER_RESULT_CONFIG_UNKNOW,
    ERR_TRRC_GRR_HANDOVER_RESULT_INVALID_CONFIG,
    ERR_TRRC_GRR_HANDOVER_RESULT_RRC_CONNECT_FAILURE,
    ERR_TRRC_GRR_HANDOVER_RESULT_PROTOCOL_ERROR,
    ERR_TRRC_GRR_HANDOVER_RESULT_UNSUPORTED_CONFIGURATION,
    ERR_TRRC_GRR_HANDOVER_RESULT_PHY_CHANNEL_FAIL,
    ERR_TRRC_GRR_HANDOVER_RESULT_MESSAGE_INVALID,
    ERR_TRRC_GRR_HANDOVER_RESULT_UNSPECIFIC,
    ERR_TRRC_GRR_HANDOVER_RESULT_BUTT
};
typedef VOS_UINT16 TDS_ERR_LOG_CS_HANDOVER_FAIL_ENUM_UINT16;

/*****************************************************************************
 ö����    : TDS_ERR_LOG_CS_LINK_ERROR_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ������·ʧ�ܵ�ԭ��ֵ
*****************************************************************************/
enum TDS_ERR_LOG_CS_LINK_ERROR_ENUM
{
    TDS_CS_LINK_ERROR_T312_TIMEOUT =0,
    TDS_CS_LINK_ERROR_T313_TIMEOUT,
    TDS_CS_LINK_ERROR_BUTT
};
typedef VOS_UINT16 TDS_ERR_LOG_CS_LINK_ERROR_ENUM_UINT16;

/*****************************************************************************
 ö����     :ERR_LOG_GSM_BAND_INDICATOR_ENUM
 Э����  :
 ASN.1����   :
 ö��˵�� : GSMС��Ƶ��ָʾö��
*****************************************************************************/
typedef enum
{
    ERR_LOG_EN_DSC_1800_USED                    = 0,
    ERR_LOG_EN_PDS_1900_USED
}ERR_LOG_GSM_BAND_INDICATOR_ENUM;
typedef VOS_UINT32  ERR_LOG_GSM_BAND_INDICATOR_ENUM_UINT32;

/* Seattle End */
/*****************************************************************************
   5 STRUCT
*****************************************************************************/

/*****************************************************************************
                               ����ģʽ �ϱ����ݽṹ
*****************************************************************************/

/*****************************************************************************
 �ṹ��    : TRRC_APP_CHANGE_CELL_INFO_STRU
 �ṹ˵��  : �仯�ϱ��Ĺ���ģʽ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                usUlFreq;          /* ��������Ƶ�㵥λ:100Khz */
    VOS_UINT16                                usDlFreq;          /* ��������Ƶ�㵥λ:100Khz */
    VOS_UINT32                                ulCellId;          /* TD-SCDMAС��ID��ָRRC���С��ID������������ */
    VOS_UINT16                                usPagingCycle;     /* Ѱ������128,256,512,1024����λms*/
    VOS_UINT16                                usReserved;
}TRRC_APP_CHANGE_CELL_INFO_STRU;

/*****************************************************************************
 �ṹ��    : TRRC_APP_TDS_NCELL_INFO_STRU
 �ṹ˵��  : TD-SCDMAͬƵ����ƵС����Ϣ�ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT16                         usFrequency;      /* TD-SCDMA��С����������Ƶ�� ��λ:100Khz */
    VOS_UINT16                         usCellId;         /* TD-SCDMA��С��С��ID */
    VOS_UINT8                          ucRscp;           /* TD-SCDMA��С��Rscp���չ��ʣ���ʵֵ=ucRscp - 116����λdbm */
    VOS_UINT8                          aucReserved[3];
}TRRC_APP_TDS_NCELL_INFO_STRU;

/*****************************************************************************
 �ṹ��    : TRRC_APP_TDS_NCELL_STRU
 �ṹ˵��  : TD-SCDMAͬƵ����ƵС����Ϣ�ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT32                      ulNCellNumber;
    TRRC_APP_TDS_NCELL_INFO_STRU    stCellMeasInfo[TRRC_APP_MAX_NCELL_NUM];
}TRRC_APP_TDS_NCELL_STRU;

/*****************************************************************************
 �ṹ��    : TRRC_APP_LTE_NCELL_INFO_STRU
 �ṹ˵��  : TD-SCDMA��ϵͳLTEС����Ϣ�ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usArfcn;
    VOS_UINT16                          usCellId;   /* ����С��ID */
    VOS_INT16                           sRsrp;      /* �������RSRP */
    VOS_INT16                           sRsrq;      /* �������RSRQ */
}TRRC_APP_LTE_NCELL_INFO_STRU;

/*****************************************************************************
 �ṹ��    : TRRC_APP_LTE_NCELL_STRU
 �ṹ˵��  : TD-SCDMA��ϵͳLTEС����Ϣ�ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT32                      ulNCellNumber;
    TRRC_APP_LTE_NCELL_INFO_STRU    stCellMeasInfo[TRRC_APP_MAX_NCELL_NUM];
}TRRC_APP_LTE_NCELL_STRU;

/*****************************************************************************
 �ṹ��    : TRRC_APP_GERAN_NCELL_INFO_STRU
 �ṹ˵��  : TD-SCDMA��ϵͳGSMС����Ϣ�ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usArfcn;
    TRRC_APP_GRR_BANDINDICATOR_ENUM_UINT16                  enBandInd;          /* ����T->Gʱ����������Ϣ�е�Ƶ��ָʾһ�� */
    VOS_INT16                                               sRssi;              /* sRssi ȡֵ��Χ[-110 * 8,-48 * 8],��λ:dbm,����1/8 */
    VOS_UINT8                                               ucNcc;              /*  �ƶ�ͨѶGSM����ʶ�����: ����ɫ��(NCC) */
    VOS_UINT8                                               ucBcc;              /*  �ƶ�ͨѶGSM����ʶ�����: ��վɫ��(BCC) */
}TRRC_APP_GERAN_NCELL_INFO_STRU;

/*****************************************************************************
 �ṹ��    : TRRC_APP_GERAN_NCELL_STRU
 �ṹ˵��  : TD-SCDMA��ϵͳGSMС����Ϣ�ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT32                        ulNCellNumber;
    TRRC_APP_GERAN_NCELL_INFO_STRU    stCellMeasInfo[TRRC_APP_MAX_NCELL_NUM];
}TRRC_APP_GERAN_NCELL_STRU;

/*****************************************************************************
 �ṹ��    : TRRC_APP_NCELL_INFO_STRU
 �ṹ˵��  : ����С����ͬƵ����Ƶ�Լ���ϵͳ�������
*****************************************************************************/
typedef struct
{
    TRRC_APP_TDS_NCELL_STRU               stIntraFreqInfo;/* ͬƵ������Ϣ*/
    TRRC_APP_TDS_NCELL_STRU               stInterFreqInfo;/* ��Ƶ������Ϣ*/
    TRRC_APP_LTE_NCELL_STRU               stLTENcellInfo; /* LTE��ϵͳ����*/
    TRRC_APP_GERAN_NCELL_STRU             stGeranNcellInfo; /* GERAN��ϵͳ���� */
}TRRC_APP_NCELL_INFO_STRU;

/****************************************************************************
 �ṹ��    : TRRC_APP_FTM_CHANGE_INFO_STRU
 �ṹ˵��  : �仯�ϱ��Ĺ���ģʽ�ṹ
*****************************************************************************/
typedef struct
{
    TRRC_APP_FTM_CHANGE_INFO_TYPE_ENUM_UINT32     ulFtmChangeInfoType;

    union
    {
        TRRC_APP_CHANGE_CELL_INFO_STRU            stCellInfo;
        TRRC_APP_PROTOCOL_STATE_ENUM_UINT8        enTrrcProtocolState;
    }uchangeInfo;
}TRRC_APP_FTM_CHANGE_INFO_STRU;
/*****************************************************************************
 �ṹ��    : APP_RRC_SINR_INFO_STRU
 �ṹ˵��  : SINR�ṹ
*****************************************************************************/
typedef struct
{
	VOS_UINT16                                     usModuFormat;
	VOS_UINT16                                     usTbiOut;
}TRRC_APP_CQI_INFO_STRU;
/*****************************************************************************
 �ṹ��    : APP_RRC_SINR_INFO_STRU
 �ṹ˵��  : SINR�ṹ
*****************************************************************************/
typedef struct
{
    VOS_INT16                              sSinrDB;
    VOS_UINT16                             usRev;
}TRRC_APP_DPCH_SINR_INFO_STRU;
/*****************************************************************************
 �ṹ��    : TDS_ERRLOG_UL_POWER_STRU
 �ṹ˵��  : UE���з��书��
*****************************************************************************/
typedef struct
{
	VOS_INT16 sDpchPwr;
	VOS_INT16 sEpuchPwr;
}TDS_APP_ERRLOG_UL_POWER_STRU;
/*****************************************************************************
 �ṹ��    : RRC_APP_FTM_PERIOD_INFO
 �ṹ˵��  : �����ϱ��Ĺ���ģʽ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_INT16                           sCellRSCP;
    VOS_UINT16                          usReserved;
    TDS_APP_ERRLOG_UL_POWER_STRU        stUeTxPower;
    TRRC_APP_DPCH_SINR_INFO_STRU        stSINR;             /* SINR  RS_SNR */
    TRRC_APP_CQI_INFO_STRU              stCQI;              /* CQI�������� */
    TRRC_APP_NCELL_INFO_STRU            stNcellInfo;        /*������Ϣ*/
}TRRC_APP_FTM_PERIOD_INFO_STRU;

/*****************************************************************************
 �ṹ��    : RRC_APP_FTM_INFO_STRU
 �ṹ˵��  : ����ģʽ�ϱ����ݽṹ
*****************************************************************************/
typedef struct
{
    TRRC_APP_FTM_TYPE_ENUM_UINT32             enRrcAppFtmType;

    union
    {
        TRRC_APP_FTM_PERIOD_INFO_STRU         stPeriodInfo;  /* ����ģʽ�£������ϱ����ݣ� Idle״̬�ϱ�����ĿǰΪDRX���ڣ�Connected״̬������Ϊ1�� */
        TRRC_APP_FTM_CHANGE_INFO_STRU         stChangInfo;   /* ����ģʽ�£�������ϱ����� */
    }u;
}TRRC_APP_FTM_INFO_STRU;
/*****************************************************************************
 �ṹ��    : TRRC_OM_FTM_REPROT_CONTENT_STRU
 �ṹ˵��  : ����ģʽ�ϱ����ݽṹ
*****************************************************************************/
typedef struct
{
    /* ��ģ��ID */
    OM_ERR_LOG_MOUDLE_ID_ENUM_UINT32    ulMsgModuleID;

    /* 00������, 01������ ,10/11:����  */
    VOS_UINT16                          usModemId;

    VOS_UINT16                          usProjectID;
    VOS_UINT32                          ulLength;

    TRRC_APP_FTM_INFO_STRU               stTrrcFtmInfo;

}TRRC_OM_FTM_REPROT_CONTENT_STRU;

/*****************************************************************************
 �ṹ��    : TRRC_OM_FTM_REPROT_IND_STRU
 �ṹ˵��  : ����ģʽ�ϱ����ݽṹ
*****************************************************************************/
/* ���������ģʽ�����ϱ����� ����� -> OM*/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    VOS_UINT32                          ulMsgType;
    VOS_UINT32                          ulMsgSN;
    VOS_UINT32                          ulRptlen;      /* ����ģʽ�ϱ������ݳ���,���ulRptlenΪ0,aucContent���ݳ���ҲΪ0 */
    TRRC_OM_FTM_REPROT_CONTENT_STRU     stTrrcFtmContent;
}TRRC_OM_FTM_REPROT_IND_STRU;

/* Seattle Begin */
/*****************************************************************************
 �ṹ��     :ERR_LOG_SAVE_CELL_INFO_FOR_GAS_ST
 Э����  :
 ASN.1����   :
 �ṹ˵��  :GSMС������Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulNCC;
    VOS_UINT32                          ulBCC;
    VOS_UINT32                          ulBcchArcfn;
    VOS_UINT32                          ulFreqBandInd;
    VOS_UINT32                          ulFlag;                                 /* �ñ������ָʾlFNOffset��ulTimeAlignmt�Ƿ������ݣ�0:��ʾ������ 1: ��ʾ������*/
    VOS_INT32                           lFNOffset;
    VOS_UINT32                          ulTimeAlignmt;
    VOS_INT16                           sRxlev;                                 /* GС���źŵ�ƽ����λ��dBm,û�в⵽�źŵ�ƽʱ��ֵΪRRWRR_INVALID_RXLEV */
    VOS_UINT8                           aucReserve1[2];                         /* 4�ֽڶ��룬���� */

}ERR_LOG_SAVE_CELL_INFO_FOR_GAS_ST;

/*****************************************************************************
 �ṹ��     :TDS_ERR_LOG_CELL_INFO_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                   ucCellId;                   /*С��ID*/
    VOS_UINT8                                   ucRscp;                     /*����*/
    VOS_UINT16                                  usFreqId;                   /*����Ƶ��*/
} TDS_ERR_LOG_CELL_INFO_STRU;

/*****************************************************************************
 �ṹ��     :TDS_ERR_LOG_GSM_CELL_INFO_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    ERR_LOG_SAVE_CELL_INFO_FOR_GAS_ST           stRrcSaveInfoForGas;        /* ע�⣬ֻ��1��С������Ϣ�����л��ӿڲ�ͬs */
    ERR_LOG_GSM_BAND_INDICATOR_ENUM_UINT32      enBandIndictor;             /* Bandָʾ */
} TDS_ERR_LOG_GSM_CELL_INFO_STRU;

/*****************************************************************************
 �ṹ��     :TDS_ERR_LOG_EVT_CS_HANDOVER_FAIL_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    TDS_ERR_LOG_CS_HANDOVER_FAIL_ENUM_UINT16    enHandoverFailCause;  /* �л�ʧ��ԭ��ֵ*/
    VOS_UINT8                                   aucReserve[2];        /* ����λ */
    TDS_ERR_LOG_CELL_INFO_STRU                  stTdsOrginalCell;     /* �л���TDSԴС����Ϣ */
    TDS_ERR_LOG_GSM_CELL_INFO_STRU              stGsmTargetCell;      /* �л���GSMĿ��С����Ϣ*/
}TDS_ERR_LOG_EVT_CS_HANDOVER_FAIL_STRU;

/*****************************************************************************
 �ṹ��     :TDS_ERR_LOG_EVT_CS_HANDOVER_SLOW_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    TDS_ERR_LOG_CELL_INFO_STRU                  stTdsOrginalCell;     /* �л���TDSԴС����Ϣ */
    TDS_ERR_LOG_GSM_CELL_INFO_STRU              stGsmTargetCell;      /* �л���GSM Ŀ��С����Ϣ*/
    VOS_UINT32                                  ulHandoverTime;       /* �л�ʱ��*/
}TDS_ERR_LOG_EVT_CS_HANDOVER_SLOW_STRU;

/*****************************************************************************
 �ṹ��     :TDS_ERR_LOG_EVT_CS_HANDOVER_SLOW_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                  ulStatus;           /*��ǰ״̬*/
    TDS_ERR_LOG_CELL_INFO_STRU                  stTdsOrginalCell;   /* �л���TDSԴС����Ϣ */
} TDS_ERR_LOG_STATUS_INFO_STRU;

/*****************************************************************************
 �ṹ��     :TDS_ERR_LOG_EVT_CS_LINK_ERROR_STRU
 Э����  :
 ASN.1����   :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    TDS_ERR_LOG_CS_LINK_ERROR_ENUM_UINT16       enRadioLinkErrorCause;      /*������·�쳣ԭ��*/
    VOS_UINT8                                   aucReserve[2];              /* ����λ */
    TDS_ERR_LOG_STATUS_INFO_STRU                stTdsStatusInfo;            /* TDS ��ǰ״̬��Ϣ��¼*/
}TDS_ERR_LOG_EVT_CS_LINK_ERROR_STRU;
/* Seattle End */

/*****************************************************************************
                               ERROR LOG �ϱ����ݽṹ
*****************************************************************************/

/*****************************************************************************
 �ṹ��    : RRC_APP_STATE_INFO_STRU
 �ṹ˵��  : ERROR LOG RRC״̬��Ϣ������Э��״̬���ڲ�״̬����ϵͳ����
*****************************************************************************/
typedef struct
{
    TRRC_APP_PROTOCOL_STATE_ENUM_UINT8          enTrrcProtocolState;   /* RRCЭ��״̬ */
    TRRC_APP_RRC_STATE_ENUM_UINT8               enRrcState;            /* RRC״̬���ڲ�״̬����Э��״̬ */
    TRRC_APP_FLOW_CTRL_TYPE_ENUM_UINT16         enErrcFlowCtrlType;    /* TD-SCDMA������ϵͳ����ʱ����ϵͳ���̱�ʶ */
}TRRC_APP_STATE_INFO_STRU;
/*****************************************************************************
 �ṹ��    : TRRC_APP_ACC_FAIL_INFO_STRU
 �ṹ˵��  : ERROR LOG RRC����ʧ���ϱ���Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                 ulMcc;           /* MCC,3 bytes      */
    VOS_UINT32                                 ulMnc;           /* MNC,2 or 3 bytes */
    VOS_UINT16                                 usFrequency;     /* �������ʧ��ʱ����С������Ƶ�� ��λ:100Khz */
    VOS_UINT16                                 usCellId;        /* �������ʧ��ʱ����С��ID��Ϣ */
    TDS_APP_FREQ_BAND_LIST_ENUM_UINT8          enBandInfo;      /* �������ʧ��ʱ����С������band��Ϣ */
    VOS_INT8                                   ucRscp;          /* �������ʧ��ʱ����С������ֵ,ʵ��ֵ - 116����λdbm */
    VOS_INT8                                   ucQrxLevMin;     /* �������ʧ��ʱ����С��פ������*/
    VOS_UINT8                                  ucRac;           /* Rac */
    VOS_UINT16                                 usLac;           /* lac */
    VOS_UINT8                                  aucResv[2];      /*����λ*/

}TRRC_APP_ACC_FAIL_INFO_STRU;
/*****************************************************************************
 �ṹ��    : TRRC_APP_EST_INFO_STRU
 �ṹ˵��  : ERROR LOG RRC������Ϣ
 enEstSignallingType[0]:CS;enEstSignallingType[1]:ps
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                     stHeader;                /* Errorlog ��Ϣͷ */
    TRRC_APP_ERROR_CODE_ENUM_UINT8             enErrorCode;             /* ������*/
    VOS_UINT8                                  aucResv[3];              /* ����λ */
    TRRC_APP_STATE_INFO_STRU                   stRrcAppStateInfo;       /* ��������ʱ״̬��Ϣ */
    TRRC_APP_EST_SIGNALLING_TYPE_UINT32        enEstSignallingType[2];  /* ����״̬��Ϣ*/
    TRRC_APP_EST_CAUSE_ENUM_UINT32             enEstCause;              /* ����ԭ�� */
    /*������뽨��ʧ��CHR�ϱ� add by lilin 2015-9-16 begin*/
    TRRC_APP_ACC_FAIL_INFO_STRU                stRrcAppAccFailInfo;              
    /*������뽨��ʧ��CHR�ϱ� add by lilin 2015-9-16 end*/
}TRRC_APP_EST_INFO_STRU;

/* ErrorLog����������Ϣbegin */

/*****************************************************************************
 �ṹ��    : TDS_APP_AREA_LOST_INFO_STRU
 �ṹ˵��  : TDS������λ��Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                 ulTimeStamp;     /* ��¼������ʱ�� */
    VOS_UINT32                                 ulMcc;           /* MCC,3 bytes      */
    VOS_UINT32                                 ulMnc;           /* MNC,2 or 3 bytes */
    VOS_UINT16                                 usFrequency;     /* ����ʱ����С������Ƶ�� ��λ:100Khz */
    VOS_UINT16                                 usCellId;        /* ����ʱ����С��ID��Ϣ */
    TDS_APP_FREQ_BAND_LIST_ENUM_UINT8          enBandInfo;      /* ����ʱ����С������band��Ϣ */
    VOS_INT8                                   ucRscp;          /* ����ǰ����С������ֵ,ʵ��ֵ - 116����λdbm */
    VOS_INT8                                   ucQrxLevMin;     /* ����ʱ����С��פ������*/
    VOS_UINT8                                  ucRac;           /* Rac */
    VOS_UINT16                                 usLac;           /* lac */
    TDS_APP_ERR_LOG_AREA_LOST_CAUSE_ENUM_UINT8 ucSubCause;      /* ��¼����ԭ��ֵ:��ʱ������������չʹ�� */
    VOS_UINT8                                  ucResv;          /* ���� */
}TDS_APP_AREA_LOST_INFO_STRU;

/*****************************************************************************
 �ṹ��    : TRRC_APP_AREA_LOST_INFO_STRU
 �ṹ˵��  : TDS������λ��Ϣ
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                     stHeader;                /* Errorlog ��Ϣͷ*/
    TRRC_APP_ERROR_CODE_ENUM_UINT8             enErrorCode;             /* ������*/
    TDS_APP_ERR_LOG_RAT_TYPE_ENUM_UINT8        enRatType;               /* ����������������ʽ */
    VOS_UINT8                                  aucResv[2];
    TRRC_APP_STATE_INFO_STRU                   stRrcAppStateInfo;       /* ��������ʱ״̬��Ϣ */
    TDS_APP_AREA_LOST_INFO_STRU                stTdsArealostInfo;       /* ������Ϣ�ṹ */
}TRRC_APP_AREA_LOST_INFO_STRU;

/* ErrorLog����������Ϣend */
/*****************************************************************************
 �ṹ��    : TRRC_APP_CS_HO_FAIL_ERROR_INFO_STRU
 �ṹ˵��  : TDS CS�л�ʧ��
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                          stHeader;                /* Errorlog ��Ϣͷ*/
    TRRC_APP_ERROR_CODE_ENUM_UINT8                  enErrorCode;             /* ������*/
    VOS_UINT8                                       aucResv[3];
    TRRC_APP_STATE_INFO_STRU                        stRrcAppStateInfo;       /* ��������ʱ״̬��Ϣ */
    TDS_ERR_LOG_EVT_CS_HANDOVER_FAIL_STRU           stTdsHoFailInfo;         /* �л�ʧ��*/
}TRRC_APP_CS_HO_FAIL_ERROR_INFO_STRU;

/*****************************************************************************
 �ṹ��    : TRRC_APP_CS_HO_EXP_ERROR_INFO_STRU
 �ṹ˵��  : TDS CS�л���ʱ
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                          stHeader;                /* Errorlog ��Ϣͷ*/
    TRRC_APP_ERROR_CODE_ENUM_UINT8                  enErrorCode;             /* ������*/
    VOS_UINT8                                       aucResv[3];
    TRRC_APP_STATE_INFO_STRU                        stRrcAppStateInfo;       /* ��������ʱ״̬��Ϣ */
    TDS_ERR_LOG_EVT_CS_HANDOVER_SLOW_STRU           stTdsHoTimeExpInfo;      /* CS�л���ʱ*/
}TRRC_APP_CS_HO_EXP_ERROR_INFO_STRU;


/*****************************************************************************
 �ṹ��    : TRRC_APP_RL_ERROR_INFO_STRU
 �ṹ˵��  : TDS������·ʧ����Ϣ
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                     stHeader;                /* Errorlog ��Ϣͷ*/
    TRRC_APP_ERROR_CODE_ENUM_UINT8             enErrorCode;             /* ������*/
    VOS_UINT8                                  aucResv[3];
    TRRC_APP_STATE_INFO_STRU                   stRrcAppStateInfo;       /* ��������ʱ״̬��Ϣ */
    TDS_ERR_LOG_EVT_CS_LINK_ERROR_STRU         stTdsRLErrorInfo;        /* ������·ʧ����Ϣ�ṹ */
}TRRC_APP_RL_ERROR_INFO_STRU;
/* Seattle End */

/*****************************************************************************
 �ṹ��    : TRRC_APP_RB_ERROR_INFO_STRU
 �ṹ˵��  : TDS RB���ô�����Ϣ
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                     stHeader;                /* Errorlog ��Ϣͷ*/
    TRRC_APP_ERROR_CODE_ENUM_UINT8             enErrorCode;             /* ������*/
    VOS_UINT8                                  aucResv[3];
    TRRC_APP_STATE_INFO_STRU                   stRrcAppStateInfo;       /* ��������ʱ״̬��Ϣ */

}TRRC_APP_RB_ERROR_INFO_STRU;

/*****************************************************************************
 �ṹ��    : TRRC_APP_RBREC_ERROR_INFO_STRU
 �ṹ˵��  : TDS RB�����ô�����Ϣ
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                     stHeader;                /* Errorlog ��Ϣͷ*/
    TRRC_APP_ERROR_CODE_ENUM_UINT8             enErrorCode;             /* ������*/
    VOS_UINT8                                  aucResv[3];
    TRRC_APP_STATE_INFO_STRU                   stRrcAppStateInfo;       /* ��������ʱ״̬��Ϣ */

}TRRC_APP_RBREC_ERROR_INFO_STRU;

/*****************************************************************************
 �ṹ��    : TRRC_APP_CELLUPDATE_ERROR_INFO_STRU
 �ṹ˵��  : TDS cellupdateconfirm������Ϣ
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                     stHeader;                /* Errorlog ��Ϣͷ*/
    TRRC_APP_ERROR_CODE_ENUM_UINT8             enErrorCode;             /* ������*/
    VOS_UINT8                                  aucResv[3];
    TRRC_APP_STATE_INFO_STRU                   stRrcAppStateInfo;       /* ��������ʱ״̬��Ϣ */
    /*������뽨��ʧ��CHR�ϱ� add by lilin 2015-9-16 begin*/
    TRRC_APP_ACC_FAIL_INFO_STRU                stRrcAppAccFailInfo;              
    /*������뽨��ʧ��CHR�ϱ� add by lilin 2015-9-16 end*/
}TRRC_APP_CELLUPDATE_ERROR_INFO_STRU;

/*****************************************************************************
 �ṹ��    : TRRC_APP_INTEGRITY_ERROR_INFO_STRU
 �ṹ˵��  : TDS INTEGRITY fail��Ϣ
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                     stHeader;                /* Errorlog ��Ϣͷ*/
    TRRC_APP_ERROR_CODE_ENUM_UINT8             enErrorCode;             /* ������*/
    VOS_UINT8                                  aucResv[3];
    TRRC_APP_STATE_INFO_STRU                   stRrcAppStateInfo;       /* ��������ʱ״̬��Ϣ */

}TRRC_APP_INTEGRITY_ERROR_INFO_STRU;

/*****************************************************************************
 �ṹ��    : TRRC_APP_MEAS_CTRL_ERROR_INFO_STRU
 �ṹ˵��  : TDS MEAS_CTRL������Ϣ
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                     stHeader;                /* Errorlog ��Ϣͷ*/
    TRRC_APP_ERROR_CODE_ENUM_UINT8             enErrorCode;             /* ������*/
    VOS_UINT8                                  aucResv[3];
    TRRC_APP_STATE_INFO_STRU                   stRrcAppStateInfo;       /* ��������ʱ״̬��Ϣ */

}TRRC_APP_MEAS_CTRL_ERROR_INFO_STRU;

/*****************************************************************************
 �ṹ��    : TRRC_APP_ASN_RLST_ERR_INFO_STRU
 �ṹ˵��  : TDS ASN����ʧ����Ϣ
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                     stHeader;                /* Errorlog ��Ϣͷ*/
    TRRC_APP_ERROR_CODE_ENUM_UINT8             enErrorCode;             /* ������*/
    VOS_UINT8                                  aucResv[3];
    TRRC_APP_STATE_INFO_STRU                   stRrcAppStateInfo;       /* ��������ʱ״̬��Ϣ */

}TRRC_APP_ASN_RLST_ERR_INFO_STRU;
/*****************************************************************************
 �ṹ��    : TRRC_APP_BUFF_OVER_FLOW_ERR_INFO_STRU
 �ṹ˵��  : �������
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                     stHeader;                /* Errorlog ��Ϣͷ*/
    VOS_UINT32                                 ulCount;                 /* ������� */
}TRRC_APP_BUFF_OVER_FLOW_ERR_INFO_STRU;

/*****************************************************************************
 �ṹ��    : OM_ERR_LOG_REPORT_CNF_STRU
 �ṹ˵��  : ERROR LOG ���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    VOS_UINT32                          ulMsgType;
    VOS_UINT32                          ulMsgSN;
    VOS_UINT32                          ulRptlen;      /* �������ݳ���,���ulRptlenΪ0,aucContent���ݳ���ҲΪ0 */
    VOS_UINT8                           aucContent[4]; /* �������� */
} TRRC_OM_ERR_LOG_REPORT_CNF_STRU;


typedef struct
{
    VOS_UINT32                                 ulMcc;           /* MCC,3 bytes      */
    VOS_UINT32                                 ulMnc;           /* MNC,2 or 3 bytes */
    VOS_UINT16                                 usFrequency;     /* ��С������Ƶ�� ��λ:100Khz */
    VOS_UINT16                                 usCellId;        /* ����С��ID��Ϣ */
    VOS_INT8                                   ucRscp;          /* ����С������ֵ,ʵ��ֵ - 116����λdbm */
    VOS_UINT8                                  ucRac;           /* Rac */
    VOS_UINT16                                 usLac;           /* lac */

}TRRC_OM_TDS_SERV_CELL_INFO_STRU;
typedef struct
{
    VOS_UINT8                                   ucTdsCellNum;                   /* δ����4G������TDSС������ */
    VOS_UINT8                                   aucRsv[3];                      /* ���ֽڶ���ı���λ */
    TRRC_OM_TDS_SERV_CELL_INFO_STRU             astCellinfo[TRRC_OM_MAX_TDS_CELLS_NUM_WITHOUT_LTE_NCELL]; /* δ����4G������С���б� */

} TRRC_OM_TDS_CELLS_LIST_WITHOUT_LTE_NCELL_STRU;
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                              stHeader;
    TDS_APP_ERR_LOG_RAT_TYPE_ENUM_UINT8                 enRatType;                       /*��ʱ�䲻��LTE������ģʽ*/
    VOS_UINT8                                           ucLteMeasValidFlag;              /*�Ƿ������LTE�źű�־*/
    VOS_INT16                                           sLteMaxRsrp;                     /*T3�����ڲ���������ǿ��LTE�ź�ǿ�� */
    TRRC_OM_TDS_CELLS_LIST_WITHOUT_LTE_NCELL_STRU       stTdsCellListWithoutLteNcell;    /*δ����LTE������С���б�*/
    TRRC_OM_TDS_SERV_CELL_INFO_STRU                     stServCellInfo;                  /*��ǰע��С����Ϣ */

} TRRC_ERR_LOG_EVT_NO_T2L_OPERATION_ONE_CYCLE_STRU;
typedef struct
{
    VOS_UINT16                                 usCellId;                /* ����С��ID */
    VOS_UINT16                                 usFrequency;             /* ����Ƶ�� */
    TDS_APP_FREQ_BAND_LIST_ENUM_UINT8          enBandInfo;              /* ����Ƶ������BAND��Ϣ */
    VOS_INT8                                   ucRscp;                  /* ����С������ */
    VOS_UINT8                                  aucResv[2];
}TRRC_APP_CS_RELEASE_CELL_INFO_STRU;


typedef struct
{
    OM_ERR_LOG_HEADER_STRU                     stHeader;                /* Errorlog ��Ϣͷ */
    TRRC_APP_ERROR_CODE_ENUM_UINT8             enErrorCode;             /* ������*/
    VOS_UINT8                                  aucResv[3];
    TRRC_APP_STATE_INFO_STRU                   stRrcAppStateInfo;       /* ��������ʱ״̬��Ϣ */
    TRRC_APP_CS_RELEASE_CELL_INFO_STRU         stServCellInfo;         /* ����С����Ϣ */
}TRRC_APP_CS_RELEASE_INFO_STRU;

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






#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of TrrcErrLogInterface.h */


