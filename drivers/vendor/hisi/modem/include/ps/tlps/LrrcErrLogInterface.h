/******************************************************************************

    Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : LrrcErrLogInterface.h
  Description     : LrrcErrLogInterface.h header file
  History         :
     1.HANLUFENG 41410       2013-8-27     Draft Enact
     2.
******************************************************************************/

#ifndef __LRRCERRLOGINTERFACE_H__
#define __LRRCERRLOGINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include  "vos.h"


#include "omerrorlog.h"
#include "AppRrcInterface.h"


#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif


/*****************************************************************************
  2 macro
*****************************************************************************/

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/
/* LTE֧��CA����£�֧�ֵ������Ƶ����V9R1Ϊ1��V7R2��K3V3Ϊ2��Э��涨���ֵΪ5 */
#define LRRC_APP_MAX_NUM 5

/* RRC error����ʱ��RRC�Ľ�����Ϣ��¼����������������ԭ��ͽ�� */
#define RRC_APP_MAX_RRC_EST_INFO_NUM              (5)

/* Э��ֵ:3 */
#define RRC_APP_MAX_NUM_OF_MCC                    (3)

/* RRC error����ʱ����ӡ�����Ϣ������¼���� */
#define RRC_APP_ERROR_PRINT_INFO_NUM              (4)

/* RRC error����ʱ��ģ�����������Ϣ������¼���� */
#define RRC_APP_RECEIVE_MSG_INFO_NUM              (16)

/* RRC error����ʱ������RRC�����������¼���� */
#define RRC_APP_CODE_NUM                          (4)

/* LTE֧��MIMOʱ�����ͬʱ֧�ֵ������� */
#define NUM_OF_CODEWORD                           (2)

/* ErrorLog����������Ϣbegin */
/* RRC error����ʱ����������¼���� */
#define RRC_ERRLOG_AREA_LOST_MAX_NUM             (4)
/* ErrorLog����������Ϣend */

#define LRRC_OM_Q_LOW_CELL_NUM_MAX                (8)
#define LRRC_OM_PING_PONG_INFO_NUM_MAX            (8)
#define LRRC_OM_PING_PONG_CELL_NUM_MAX            (8)
#define LRRC_OM_MOBILITY_2_QLOW_NUM_MAX           (8)
#define LRRC_OM_ESR_NUM_MAX                       (8)
#define LRRC_OM_OUT_OF_SYNC_NUM_MAX               (8)

/*****************************************************************************
  4 Enum
*****************************************************************************/
 enum RRC_APP_FTM_TYPE_ENUM
 {
    RRC_APP_FTM_PERIOD_INFO,     /* �������ϱ��Ĺ���ģʽ��Ϣ��ĿǰIdle״̬�ϱ�����ΪDRX���ڣ�Connected״̬������Ϊ1�� */
    RRC_APP_FTM_CHANGE_INFO,     /* ���º��ϱ��͵Ĺ���ģʽ��Ϣ */
    RRC_APP_FTM_INFO_BUTT
 };
 typedef VOS_UINT32 RRC_APP_FTM_TYPE_ENUM_UINT32;

/*****************************************************************************
 ö����    : RRC_APP_PAGING_CYCLE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : Ѱ�����ڣ�RFXX��XX��ʾ����֡��������λΪ10ms,RF32������320ms��������ʾΪXXXms
*****************************************************************************/
enum RRC_APP_PAGING_CYCLE_ENUM
{
    RRC_APP_RF32                                     = 0,
    RRC_APP_RF64                                     = 1,
    RRC_APP_RF128                                    = 2,
    RRC_APP_RF256                                    = 3
};
typedef VOS_UINT32 RRC_APP_PAGING_CYCLE_ENUM_UINT32;
/*****************************************************************************
 ö����    : RRC_APP_TRANSM_MODE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ����ģʽ���ͣ�����ֱ����ʾTMX_TRANSM_MODE����
*****************************************************************************/
enum RRC_APP_TRANSM_MODE_ENUM
{
    RRC_APP_TM1_TRANSM_MODE                          = 0,
    RRC_APP_TM2_TRANSM_MODE                          = 1,
    RRC_APP_TM3_TRANSM_MODE                          = 2,
    RRC_APP_TM4_TRANSM_MODE                          = 3,
    RRC_APP_TM5_TRANSM_MODE                          = 4,
    RRC_APP_TM6_TRANSM_MODE                          = 5,
    RRC_APP_TM7_TRANSM_MODE                          = 6,
    RRC_APP_TM8_TRANSM_MODE                          = 7,
    RRC_APP_TM9_TRANSM_MODE                          = 8,
    RRC_APP_TRANSM_MODE_BUTT
};
typedef VOS_UINT32 RRC_APP_TRANSM_MODE_ENUM_UINT32;
/*****************************************************************************
 ö����    : RRC_APP_PROTOCOL_STATE_IND
 Э����  :
 ASN.1���� :
 ö��˵��  : RRCЭ��״̬����
*****************************************************************************/
enum RRC_APP_PROTOCOL_STATE_IND_ENUM
{
    RRC_APP_PROTOCOL_IDLE                   = 0 ,
    RRC_APP_PROTOCOL_CONNECTED,
    RRC_APP_PROTOCOL_STATE_BUTT
};
typedef VOS_UINT8 RRC_APP_PROTOCOL_STATE_IND_ENUM_UINT8;

/*****************************************************************************
 ö����    : RRC_APP_ERROR_CODE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : RRC����������
*****************************************************************************/
enum RRC_APP_ERROR_CODE_ENUM
{
    RRC_APP_RB_MEAS_CHECK_ERR               = 0, /* ������ʧ��--measConfig���ʧ�� */
    RRC_APP_RB_MOCTRL_CHECK_ERR             = 1, /* ������ʧ��--MobilCtrlInfo �л���Ϣ���ʧ�� */
    RRC_APP_RB_RADIOSRC_CHECK_ERR           = 2, /* ������ʧ��--RadioRsrcConfigDedic ��Ϣ���ʧ�� */
    RRC_APP_RB_TTIBUNDING_CHECK_ERR         = 3, /* ������ʧ��--TTIBundling ���ʧ�� */
    RRC_APP_RB_SECU_CHECK_ERR               = 4, /* ������ʧ��--SecurCfgHo �л��а�ȫ���ʧ�� */
    RRC_APP_RB_CFGDSP_ERR                   = 5, /* ������ʧ��--����DSP��DSP����ʧ�� */
    RRC_APP_RB_CFGL2_ERR                    = 6, /* ������ʧ��--����L2,L2����ʧ�� */
    RRC_APP_RB_CFGDSP_TIMEROUT_ERR          = 7, /* ������ʧ��--����DSP��������ʱ����ʱ */
    RRC_APP_RB_CFGL2_TIMEROUT_ERR           = 8, /* ������ʧ��--����L2��������ʱ����ʱ */

    RRC_APP_EST_PRESENT                         = 12, /* RRC���ӽ���ʧ��--RRC�����Ѵ���*/
    RRC_APP_EST_ESTING                          = 13, /* RRC���ӽ���ʧ��--RRC���ڽ���*/
    RRC_APP_EST_DELING                          = 14, /* RRC���ӽ���ʧ��--RRC�����ͷ�����*/
    RRC_APP_EST_DSDS_NO_RF                      = 15, /* RRC���ӽ���ʧ��--˫ͨ:����Ƶ��Դ*/
    RRC_APP_EST_CELL_SEARCHING                  = 16, /* RRC���ӽ���ʧ��--RRC��������*/
    RRC_APP_EST_EUTRAN_REJ                      = 17, /* RRC���ӽ���ʧ��--����ܾ�����*/

    RRC_APP_EST_MT_T302_ERR                     = 18, /* RRC���ӽ���ʧ��--MT Call��T302��ʱ�������� */

    RRC_APP_EST_MO_T302_ERR                     = 22, /* RRC���ӽ���ʧ��--Mo Data��T302��ʱ�������� */
    RRC_APP_EST_MO_T303_ERR                     = 23, /* RRC���ӽ���ʧ��--Mo Data��T303��ʱ�������� */
    RRC_APP_EST_MO_ACC_PROBABILITY_ERR          = 24, /* RRC���ӽ���ʧ��--Mo Data��ACC����ȼ����� */
    RRC_APP_EST_MO_RHPLMN_PROBABILITY_ERR       = 25, /* RRC���ӽ���ʧ��--Mo Data��Rplmn��Hplmn���� */
    RRC_APP_EST_MO_ACC_RHPLMN_PROBABILITY_ERR   = 26, /* RRC���ӽ���ʧ��--Mo Data��AcBarringForMoData�����жϱ�Bar */

    RRC_APP_EST_MS_T302_ERR                     = 28, /* RRC���ӽ���ʧ��--Mo Signalling��T302��ʱ�������� */
    RRC_APP_EST_MS_T305_ERR                     = 29, /* RRC���ӽ���ʧ��--Mo Signalling��T305��ʱ�������� */
    RRC_APP_EST_MS_ACC_PROBABILITY_ERR          = 30, /* RRC���ӽ���ʧ��--Mo Signalling��ACC����ȼ����� */
    RRC_APP_EST_MS_RHPLMN_PROBABILITY_ERR       = 31, /* RRC���ӽ���ʧ��--Mo Signalling��Rplmn��Hplmn���� */
    RRC_APP_EST_MS_ACC_RHPLMN_PROBABILITY_ERR   = 32, /* Mo Signalling��AcBarringForMoData�����жϱ�Bar */
    RRC_APP_EST_T300_EXPIRED_ERR                = 33, /* RRC���ӽ���ʧ��--T300��ʱ*/

    RRC_APP_EST_AREA_LOST_ERR                   = 34, /* ��ǰ�Ѿ���������ֱ�Ӹ�NAS��ʧ�� */

    /* ErrorLog����������Ϣbegin */
    RRC_APP_AREA_LOST_ERR                       = 35,  /* �ϱ�NAS���� */
    /* ErrorLog����������Ϣend */

    RRC_APP_REEST_T311_TIMEROUT_ERR             = 49, /* �ؽ���ʧ��--�ؽ�������С������T311��ʱ����ʱ */
    RRC_APP_REEST_T301_TIMEROUT_ERR             = 50, /* �ؽ���ʧ��--���ͽ���Req��Ϣ�󣬵ȴ��ؽ���Ӧ��Ϣ��T301��ʱ */
    RRC_APP_REEST_SRB0CFGDSP_ERR                = 51, /* �ؽ���ʧ��--����DSP��DSP����ʧ�� */
    RRC_APP_REEST_SRB0CFGL2_ERR                 = 52, /* �ؽ���ʧ��--����L2��L2����ʧ�� */
    RRC_APP_REEST_MACCFG_CHECK_ERR              = 53, /* �ؽ���ʧ��--��Ϣ���MasCfgʧ�� */
    RRC_APP_REEST_PHYDEDIC_CHECK_ERR            = 54, /* �ؽ���ʧ��--��Ϣ���PhyCfgDedicʧ�� */
    RRC_APP_REEST_TTIBUND_CHECK_ERR             = 55, /* �ؽ���ʧ��--ttiBundling���ʧ�� */
    RRC_APP_REEST_SRB_CHECK_ERR                 = 56, /* �ؽ���ʧ��--SRB���ʧ�ܳ�ʱ */
    RRC_APP_REEST_SPS_CHECK_ERR                 = 57, /* �ؽ���ʧ��--SPS���ʧ�� */
    RRC_APP_REEST_SRB1CFGDSP_ERR                = 58, /* �ؽ���ʧ��--����DSP��DSP����ʧ�� */
    RRC_APP_REEST_SRB1CFGL2_ERR                 = 59, /* �ؽ���ʧ��--����L2��L2����ʧ�� */
    RRC_APP_REEST_SECU_ERR                      = 60, /* �ؽ���ʧ��--��ȫ������ʧ�� */

    RRC_APP_QLOW_WARN                           = 70,/* ��ʱ��פ������С������----������ܲ����� */
    RRC_APP_PINGPONG_WARN                       = 71,/* ƹ����ѡ�澯----���ܵ��±��в�ͨ */
    RRC_APP_CSFB_FAIL_ERR                       = 72,/* CSFBʧ�� --- ���ܵ������л򱻽в�ͨ */
    RRC_APP_MOBILITY_2_QLOW_WARN                = 73,/* ��ѡ�ض�����С��----������ܲ����� */
    RRC_APP_OUT_SYNC_ERR                        = 74,/* ʧ������ */
    RRC_APP_SRCHED_FIRST_FREQ_INFO              = 75,/* �����ѵ���һ��MCCʱ��Ƶ����Ϣ�ϱ� major */
    RRC_APP_SRCHED_SUCC_FREQ_INFO               = 76,/* �����ɹ�ʱƵ����Ϣ�ϱ� major */
    RRC_APP_ERR_CODE_BUTT
};
typedef VOS_UINT16 RRC_APP_ERROR_CODE_ENUM_UINT16;

/*****************************************************************************
 ö����    : LRRC_LNAS_EST_CAUSE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : RRMM_EST_REQ_STRU��Ϣ�е�enEstCause
              emergency, highPriorityAccess, mt-Access, mo-Signalling, mo-Data,delayTolerantAccess-v1020 ,
*****************************************************************************/
enum LRRC_APP_LNAS_EST_CAUSE_ENUM
{
    LRRC_APP_LNAS_EST_CAUSE_EMERGENCY_CALL          = 0,
    LRRC_APP_LNAS_EST_CAUSE_HIGH_PRIORITY_ACCESS,
    LRRC_APP_LNAS_EST_CAUSE_MT_ACCESS,
    LRRC_APP_LNAS_EST_CAUSE_MO_SIGNALLING,
    LRRC_APP_LNAS_EST_CAUSE_MO_DATA,
    LRRC_APP_LNAS_EST_CAUSE_BUTT
};
typedef VOS_UINT8 LRRC_APP_LNAS_EST_CAUSE_ENUM_UINT8;

/*****************************************************************************
 ö����    : LRRC_LNAS_EST_RESULT_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : �������ӽ��ö������
*****************************************************************************/
enum LRRC_APP_LNAS_EST_RESULT_ENUM
{
    LRRC_APP_EST_SUCCESS                         = 0,       /* �������ӽ����ɹ� */
    LRRC_APP_EST_PRESENT                         = 1,       /* �����������Ѿ����� */
    LRRC_APP_EST_ESTING                          = 2,       /* �������������ڽ��� */
    LRRC_APP_EST_DELING                          = 3,       /* ���������������ͷ� */
    LRRC_APP_EST_ACCESS_BARRED_MO_CALL           = 4,       /* access barred when MO Call */
    LRRC_APP_EST_ACCESS_BARRED_MO_SIGNAL         = 5,       /* access barred When MO SIGNAL */
    LRRC_APP_EST_ACCESS_BARRED_EMERGENCY_CALL    = 6,       /* access barred When Emergency Call */
    LRRC_APP_EST_ACCESS_BARRED_ALL               = 7,       /* access barred When Rrc Con Rej */
    LRRC_APP_EST_EST_CONN_FAIL                   = 8,       /* RR connection establish failure  */
    LRRC_APP_EST_RJ_INTER_RAT                    = 9,       /* RR connection Reject: ָʾ������ϵͳ */
    LRRC_APP_EST_IMMEDIATE_ASSIGN_REJECT         = 10,      /* �����Ľ�����̣�����RA������յ�����ָ�ɾܾ���Ϣ��
                                                                û���յ�����ָ����Ϣ�����µĽ���ʧ�� */
    LRRC_APP_EST_RANDOM_ACCESS_REJECT            = 11,      /* �����Ľ�����̣�����RA�����û���յ�����������ָ�ɣ�
                                                                Ҳû���յ�����ָ�ɾܾ�������ʧ�� */
    LRRC_APP_EST_CELL_SEARCHING                  = 12,      /* RRCĿǰ���ܴ���������NAS�յ���ԭ��ֵ��
                                                                ֱ���յ�RRC_MM_SYS_INFO_IND�ٷ�����*/
    LRRC_APP_EST_RESULT_BUTT
};
typedef VOS_UINT8 LRRC_APP_LNAS_EST_RESULT_ENUM_UINT8;

/*****************************************************************************
 ö����    : LRRC_FLOW_CTRL_TYPE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ���̿�������ö��
             �޸�ö��ʱ��Ҫע�⣬ʧ������ȡֵ = ��������ȡֵ+1
 ����: LRRC_FLOW_CTRL_TYPE_G2L_RESEL_FAIL = LRRC_FLOW_CTRL_TYPE_G2L_START_RESEL + 1
*****************************************************************************/
enum LRRC_APP_FLOW_CTRL_TYPE_ENUM
{
    LRRC_APP_FLOW_CTRL_TYPE_L2L_NORMAL            = 0,     /* LTE������ */
    LRRC_APP_FLOW_CTRL_TYPE_G2L_START_RESEL,               /* G->L��ʼ��ѡ */
    LRRC_APP_FLOW_CTRL_TYPE_G2L_RESEL_FAIL,                /* G->L��ѡʧ�� */
    LRRC_APP_FLOW_CTRL_TYPE_G2L_STOP_RESEL,                /* G->Lֹͣ��ѡ */
    LRRC_APP_FLOW_CTRL_TYPE_G2L_START_REDIR,               /* G->L��ʼ�ض��� */
    LRRC_APP_FLOW_CTRL_TYPE_G2L_REDIR_FAIL,                /* G->L�ض���ʧ�� */
    LRRC_APP_FLOW_CTRL_TYPE_G2L_STOP_REDIR,                /* G->Lֹͣ�ض��� */
    LRRC_APP_FLOW_CTRL_TYPE_G2L_START_CCO,                 /* G->L��ʼCCO */
    LRRC_APP_FLOW_CTRL_TYPE_G2L_CCO_FAIL,                  /* G->L CCOʧ�� */
    LRRC_APP_FLOW_CTRL_TYPE_G2L_STOP_CCO,                  /* G->LֹͣCCO */
    LRRC_APP_FLOW_CTRL_TYPE_G2L_START_HO,                  /* G->L��ʼHO */
    LRRC_APP_FLOW_CTRL_TYPE_G2L_HO_FAIL,                   /* G->L HOʧ�� */
    LRRC_APP_FLOW_CTRL_TYPE_G2L_STOP_HO,                   /* G->LֹͣHO */
    LRRC_APP_FLOW_CTRL_TYPE_W2L_START_RESEL,               /* W->L��ʼ��ѡ */
    LRRC_APP_FLOW_CTRL_TYPE_W2L_RESEL_FAIL,                /* W->L��ѡʧ�� */
    LRRC_APP_FLOW_CTRL_TYPE_W2L_STOP_RESEL,                /* W->Lֹͣ��ѡ */
    LRRC_APP_FLOW_CTRL_TYPE_W2L_START_REDIR,               /* W->L��ʼ�ض��� */
    LRRC_APP_FLOW_CTRL_TYPE_W2L_REDIR_FAIL,                /* W->L�ض���ʧ�� */
    LRRC_APP_FLOW_CTRL_TYPE_W2L_STOP_REDIR,                /* W->Lֹͣ�ض��� */
    LRRC_APP_FLOW_CTRL_TYPE_W2L_START_HO,                  /* W->L��ʼHO */
    LRRC_APP_FLOW_CTRL_TYPE_W2L_HO_FAIL,                   /* W->L HOʧ�� */
    LRRC_APP_FLOW_CTRL_TYPE_W2L_STOP_HO,                   /* W->LֹͣHO */
    LRRC_APP_FLOW_CTRL_TYPE_W2L_START_PLMN,                /* W->L��ʼPLMN���� */
    LRRC_APP_FLOW_CTRL_TYPE_W2L_DONE_PLMN,                 /* W->L PLMN������� */
    LRRC_APP_FLOW_CTRL_TYPE_W2L_STOP_PLMN,                 /* W->LֹͣPLMN���� */
    LRRC_APP_FLOW_CTRL_TYPE_L2G_START_RESEL,               /* L->G��ʼ��ѡ */
    LRRC_APP_FLOW_CTRL_TYPE_L2G_RESEL_FAIL,                /* L->G��ѡʧ�� */
    LRRC_APP_FLOW_CTRL_TYPE_L2G_START_REDIR,               /* L->G�ض��� */
    LRRC_APP_FLOW_CTRL_TYPE_L2G_REDIR_FAIL,                /* L->G�ض���ʧ�� */
    LRRC_APP_FLOW_CTRL_TYPE_L2G_START_CCO,                 /* L->G��ʼCCO */
    LRRC_APP_FLOW_CTRL_TYPE_L2G_CCO_FAIL,                  /* L->G CCOʧ�� */
    LRRC_APP_FLOW_CTRL_TYPE_L2G_START_HO,                  /* L->G��ʼ�л� */
    LRRC_APP_FLOW_CTRL_TYPE_L2G_HO_FAIL,                   /* L->G�л�ʧ�� */
    LRRC_APP_FLOW_CTRL_TYPE_L2W_START_RESEL,               /* L->W��ʼ��ѡ */
    LRRC_APP_FLOW_CTRL_TYPE_L2W_RESEL_FAIL,                /* L->W��ѡʧ�� */
    LRRC_APP_FLOW_CTRL_TYPE_L2W_START_REDIR,               /* L->W�ض��� */
    LRRC_APP_FLOW_CTRL_TYPE_L2W_REDIR_FAIL,                /* L->W�ض���ʧ�� */
    LRRC_APP_FLOW_CTRL_TYPE_L2W_START_HO,                  /* L->W��ʼ�л� */
    LRRC_APP_FLOW_CTRL_TYPE_L2W_HO_FAIL,                   /* L->W�л�ʧ�� */
    LRRC_APP_FLOW_CTRL_TYPE_G2L_IDLE_MEAS,                 /* G->L IDLE�������� */
    LRRC_APP_FLOW_CTRL_TYPE_W2L_IDLE_MEAS,                 /* W->L IDLE�������� */
    LRRC_APP_FLOW_CTRL_TYPE_G2L_CONN_MEAS,                 /* G->L CONN�������� */
    LRRC_APP_FLOW_CTRL_TYPE_W2L_CONN_MEAS,                 /* W->L CONN�������� */
    LRRC_APP_FLOW_CTRL_TYPE_W2L_RELALL,                    /* W->L RELALL */
    LRRC_APP_FLOW_CTRL_TYPE_L2W_START_CELL_SRCH,           /* L->W ���� */
    LRRC_APP_FLOW_CTRL_TYPE_L2W_STOP_CELL_SRCH,            /* L->W ֹͣ���� */
    LRRC_APP_FLOW_CTRL_TYPE_L2G_START_CELL_SRCH,           /* L->G ���� */
    LRRC_APP_FLOW_CTRL_TYPE_L2G_STOP_CELL_SRCH,            /* L->G ֹͣ���� */
    LRRC_APP_FLOW_CTRL_TYPE_T2L_RELALL,                    /* T->L RELALL */
    LRRC_APP_FLOW_CTRL_TYPE_G2L_RELALL,                    /* G->L RELALL */
    LRRC_APP_FLOW_CTRL_TYPE_L2T_START_REDIR,               /* L->T�ض��� */
    LRRC_APP_FLOW_CTRL_TYPE_L2T_START_HO,                  /* L->T��ʼ�л� */
    LRRC_APP_FLOW_CTRL_TYPE_L2T_START_RESEL,               /* L->T��ʼ��ѡ */
    LRRC_APP_FLOW_CTRL_TYPE_T2L_IDLE_MEAS,                 /* T->L IDLE�������� */
    LRRC_APP_FLOW_CTRL_TYPE_T2L_CONN_MEAS,                 /* G->L CONN�������� */

    LRRC_APP_FLOW_CTRL_TYPE_BUTT
};
typedef VOS_UINT8 LRRC_APP_FLOW_CTRL_TYPE_ENUM_UINT8;

/*****************************************************************************
 ö����    : RRC_APP_BOOL_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : PSͳһ��������ö�ٶ���
*****************************************************************************/
enum RRC_APP_BOOL_ENUM
{
    RRC_APP_PS_FALSE                            = 0,
    RRC_APP_PS_TRUE                             = 1,
    RRC_APP_PS_BOOL_BUTT
};
typedef VOS_UINT8   RRC_APP_BOOL_ENUM_UINT8;

/*****************************************************************************
 ö����    : RRC_UE_CATEGORY_ENUM_UINT8
 Э����  :
 ASN.1���� :
 ö��˵��  : UE Category����μ�36306Э��
*****************************************************************************/
enum RRC_APP_CATEGORY_ENUM
{
    RRC_APP_UE_CATEGORY_1                   = 0,
    RRC_APP_UE_CATEGORY_2                   = 1,
    RRC_APP_UE_CATEGORY_3                   = 2,
    RRC_APP_UE_CATEGORY_4                   = 3,
    RRC_APP_UE_CATEGORY_5                   = 4,
    RRC_APP_UE_CATEGORY_6                   = 5,
    RRC_APP_UE_CATEGORY_7                   = 6,
    RRC_APP_UE_CATEGORY_BUTT
};
typedef VOS_UINT8 RRC_APP_CATEGORY_ENUM_UINT8;
/*****************************************************************************
 ö����    : RRC_CONN_REEST_IND_ENUM_UINT8
 Э����  :
 ASN.1���� :
 ö��˵��  : RRC�����ؽ������ԭ��
*****************************************************************************/
enum RRC_APP_CONN_REEST_IND_ENUM
{
    RRC_APP_CONN_REEST_FOR_RBCFG_ERROR      = 1,                                    /* 0:����RB����ʧ�ܵ��µ�RRC�����ؽ� */
    RRC_APP_CONN_REEST_FOR_HANDOVER_ERROR   = 2,                                    /* 1:�����л�ʧ�ܵ��µ�RRC�����ؽ� */
    RRC_APP_CONN_REEST_FOR_OTHER_ERROR      = 3,                                    /* 2:����������·ʧ�ܻ�����������֤ʧ�ܵ��µ�RRC�����ؽ� */
    RRC_APP_CONN_REEST_FOR_BUTT
};
typedef VOS_UINT8 RRC_APP_CONN_REEST_IND_ENUM_UINT8;

/*********************************************************
 ö����    : RRC_APP_FTM_CHANGE_INFO_TYPE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ����ϱ�����ģʽ���Ͷ���
**********************************************************/
enum RRC_APP_FTM_CHANGE_INFO_TYPE_ENUM
{
    RRC_APP_FTM_CHANGE_CELL_INFO,  /* RRCפ��С����Ϣ���仯���ϱ����л�����ѡ��ɺ��ϱ� */
    RRC_APP_FTM_CHANGE_STATE_INFO, /* RRC״̬��Ϣ���仯���ϱ� */
    RRC_APP_FTM_CHANGE_BUTT
};

typedef VOS_UINT32 RRC_APP_FTM_CHANGE_INFO_TYPE_ENUM_UINT32;
/*********************************************************
 ö����    : LRRC_LPHY_LTE_BAND_WIDTH_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : LTE����WIDTH_3M���Ǳ�ʾ���д�����3M��������ʾ3M����
**********************************************************/
enum LRRC_APP_BAND_WIDTH_ENUM
{
    LRRC_APP_LTE_BAND_WIDTH_1D4M = 0,
    LRRC_APP_LTE_BAND_WIDTH_3M,
    LRRC_APP_LTE_BAND_WIDTH_5M,
    LRRC_APP_LTE_BAND_WIDTH_10M,
    LRRC_APP_LTE_BAND_WIDTH_15M,
    LRRC_APP_LTE_BAND_WIDTH_20M,
    LRRC_APP_LTE_BAND_WIDTH_BUTT
};
typedef VOS_UINT16 LRRC_APP_BAND_WIDTH_ENUM_UINT16;

enum LRRC_OM_QLOW_WATCH_TYPE_ENUM
{
    LRRC_OM_QLOW_WATCH_NONE = 0,
    LRRC_OM_QLOW_WATCH_L2L_REDIR,
    LRRC_OM_QLOW_WATCH_L2L_RESEL,
    LRRC_OM_QLOW_WATCH_U2L_REDIR,
    LRRC_OM_QLOW_WATCH_U2L_RESEL,
    LRRC_OM_QLOW_WATCH_G2L_REDIR,
    LRRC_OM_QLOW_WATCH_G2L_RESEL,
    LRRC_OM_QLOW_WATCH_C2L_RESEL,
    LRRC_OM_QLOW_WATCH_BUTT
};
typedef VOS_UINT8 LRRC_OM_QLOW_FLOW_TYPE_ENUM_UINT8;

/*****************************************************************************
 �ṹ��    :LRRC_ERRLOG_ESR_CS_FAIL_TYPE_ENUM32
 �ṹ˵��  :
*****************************************************************************/
enum LRRC_OM_RAT_TYPE_ENUM
{
    LRRC_OM_RAT_TYPE_GSM = 1,                         /* GSM���뼼�� */
    LRRC_OM_RAT_TYPE_UTRA,                            /* UTRA���뼼�� */
    LRRC_OM_RAT_TYPE_LTE,                             /* LTE���뼼�� */
    LRRC_OM_RAT_TYPE_HRPD,                            /* CDMA HRPD*/
    LRRC_OM_RAT_TYPE_BUTT
};
typedef VOS_UINT16  LRRC_OM_RAT_TYPE_ENUM_UINT16;

/*****************************************************************************
 �ṹ��    :LRRC_CHR_MEAS_STATE_AND_CNF_ENUM_UINT16
 �ṹ˵��  :���ڽ���LRRC_OM_NCELL_INFO�е�usMeasCnfAndState
*****************************************************************************/
enum  LRRC_CHR_MEAS_STATE_AND_CNF_ENUM
{
    LRRC_CHR_MEAS_STATE_BitOpIntraReselCfg = 0x8000,
    LRRC_CHR_MEAS_STATE_bitOpInterMeasCfg = 0x4000,
    LRRC_CHR_MEAS_STATE_bitOp2GMeasCfg = 0x2000,
    LRRC_CHR_MEAS_STATE_bitOp3GMeasCfg = 0x1000,
    LRRC_CHR_MEAS_STATE_bitOpIntraMeasState = 0x0800,
    LRRC_CHR_MEAS_STATE_bitOpInterMeasState = 0x0400,
    LRRC_CHR_MEAS_STATE_bitOp2GMeasState = 0x0200,
    LRRC_CHR_MEAS_STATE_bitOp3GMeasState = 0x0100,
    LRRC_CHR_MEAS_STATE_bitOpValidIntraCell = 0x0080,
    LRRC_CHR_MEAS_STATE_bitOpValidInterCell = 0x0040,
    LRRC_CHR_MEAS_STATE_bitOpValid2GCell = 0x0020,
    LRRC_CHR_MEAS_STATE_bitOpValid3GCell = 0x0010,
    LRRC_CHR_MEAS_STATE_BUTT = 0x0000
};
typedef VOS_UINT16  LRRC_CHR_MEAS_STATE_AND_CNF_ENUM_UINT16;

/*****************************************************************************
   5 STRUCT
*****************************************************************************/
/*****************************************************************************
                  ����ģʽ�ϱ��ṹ�嶨��
*****************************************************************************/
/*********************************************************************
* ASN �ı� :MCC
*********************************************************************/
typedef struct
{
    VOS_UINT8                           ucCnt;    /*(0, 3)*/
    VOS_UINT8                           aucItem[RRC_APP_MAX_NUM_OF_MCC];
}RRC_APP_MCC_STRU;

/*********************************************************************
* ASN �ı� :PLMN-Identity
*********************************************************************/
typedef struct
{
    RRC_APP_MCC_STRU                         Mcc;                          /* optional */
    RRC_APP_MCC_STRU                         Mnc;
}LRRC_APP_PLMN_ID_STRU;
/*****************************************************************************
 �ṹ��    :APP_RRC_Txpwr
 �ṹ˵��  :RRC�ϱ���APP�����з��书��
*****************************************************************************/
typedef struct
{
    VOS_INT16                        sPuschTxPwr;
    VOS_INT16                        sPucchTxPwr;
    VOS_INT16                        sSrsTxpwr;
    VOS_UINT16                       usReserved;
}RRC_APP_Txpwr_INFO_STRU;
/*****************************************************************************
 �ṹ��    :RRC_APP_PUSCH_BLER_STRU
 �ṹ˵��  :RRC�ϱ���APP��PUSCH�����ʽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32             ulAckCnt;    /* �յ���ACK���� */
    VOS_UINT32             ulNackCnt;   /* �յ���NACK���� */
}RRC_APP_PUSCH_BLER_STRU;

/*****************************************************************************
 �ṹ��    :RRC_APP_PDSCH_BLER_STRU
 �ṹ˵��  :RRC�ϱ���APP��PDSCH�����ʽṹ����Ҫ��ʾ��ʼ�����ʺ��ۼ������ʣ���Ҫ��������ʾ
*****************************************************************************/
typedef struct
{
    VOS_UINT16              ausCWInitTotal[NUM_OF_CODEWORD]; /* ��ʼ�����ʣ��յ�����֡�����������������ȷ�� */
    VOS_UINT16              ausCWInitError[NUM_OF_CODEWORD]; /* ��ʼ�����ʣ��յ��Ĵ�����֡���� */
    VOS_UINT16              ausCWReTotal[NUM_OF_CODEWORD];   /* ���������ʣ��յ�����֡�����������������ȷ�� */
    VOS_UINT16              ausCWReError[NUM_OF_CODEWORD];   /* ���������ʣ��յ��Ĵ�����֡���� */
}RRC_APP_PDSCH_BLER_STRU;

/*****************************************************************************
 �ṹ��    :RRC_APP_PDCCH_BLER_STRU
 �ṹ˵��  :RRC�ϱ���APP����������Ȩ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32              ulDlGrantCnt; /* ������Ȩ���� */
    VOS_UINT32              ulUlGrantCnt; /* ������Ȩ���� */
}RRC_APP_PDCCH_BLER_STRU;

/*****************************************************************************
 �ṹ��    :APP_RRC_BLER_INFO_STRU
 �ṹ˵��  :RRC�ϱ���APP�������ʽṹ
*****************************************************************************/
typedef struct
{
    RRC_APP_PUSCH_BLER_STRU         stPuschBlerCnt; /* PUSCH �����BLER */
    RRC_APP_PDSCH_BLER_STRU         stPdschBlerCnt; /* PDSCH �����BLER */
    RRC_APP_PDCCH_BLER_STRU         stPdcchBlerCnt; /* PDCCH ��������Ȩ���� */
}RRC_APP_BLER_INFO_STRU;

/*****************************************************************************
 �ṹ��    :RRC_APP_PERIOD_CELL_INFO_STRU
 �ṹ˵��  :RRC�����ϱ���APP��פ��С����Ϣ
*****************************************************************************/
typedef struct
{
    VOS_INT16                           sRsrp;              /* RSRP����ֵ��Χ��(-141,-44)����λdbm*/
    VOS_INT16                           sRsrq;              /* RSRQ����ֵ��Χ��(-40, -6) */
    VOS_INT16                           sRssi;              /* RSSI����ֵ����λdbm */
    VOS_UINT16                          usRI;               /* RIֵ */
    VOS_UINT16                          ausCQI[2];          /* CQI�������֣�ֻ��һ������ʱ�������һ��ֵ��Ч */
    VOS_INT32                           lSINR;              /* SINR��С���ο��ź������ */
    RRC_APP_Txpwr_INFO_STRU             stTxPwr;            /* LTE�����ŵ����͹��� */
    RRC_APP_BLER_INFO_STRU              stBler;             /* LTE������ */
}RRC_APP_PERIOD_CELL_INFO_STRU;
/*****************************************************************************
 �ṹ��    : RRC_APP_FREQ_PARA_STRU
�ṹ˵��  : RRC�ϱ�����Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usUlFreq;          /* ��������Ƶ�� ��λ:100Khz */
    VOS_UINT16                              usDlFreq;          /* ��������Ƶ�� ��λ:100Khz */
    LRRC_APP_BAND_WIDTH_ENUM_UINT16         enDlBandwidth;     /* ���д��� */
    VOS_UINT8                               usBand;            /* Ƶ��ָʾ */
    VOS_UINT8                               aucResv[1];
} RRC_APP_FREQ_PARA_STRU;

/*****************************************************************************
 �ṹ��    : RRC_APP_CHANGE_CELL_INFO_STRU
 �ṹ˵��  : �仯�ϱ��Ĺ���ģʽ�ṹ--פ��С����Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                ulValidNum;                      /* LTE֧��CA����£���Ч��Ƶ���� */
    RRC_APP_FREQ_PARA_STRU                    astFreqInfo[LRRC_APP_MAX_NUM];   /* LTE֧��CA����£�������Ƶ����Ϣ */
    VOS_UINT16                                astPhyCellId[LRRC_APP_MAX_NUM];  /* LTE֧��CA����£�����С��ID��Ϣ */
    VOS_UINT8                                 ucSbuFrmAssignmentType;          /* TDDģʽ����Ч��LTE��֡��ȣ�0xFFΪ��Чֵ */
    VOS_UINT8                                 ucSpecialSubFrmPatterns;         /* TDDģʽ����Ч��LTE������֡��ȣ�0xFFΪ��Чֵ */
    RRC_APP_PAGING_CYCLE_ENUM_UINT32          enPagingCycle;                   /* Ѱ������ */
    RRC_APP_TRANSM_MODE_ENUM_UINT32           enTranMode;                      /* LTE����ģʽ */
}RRC_APP_CHANGE_CELL_INFO_STRU;

/*****************************************************************************
 �ṹ��    : RRC_APP_FTM_CHANGE_INFO_STRU
 �ṹ˵��  : �仯�ϱ��Ĺ���ģʽ�ṹ
*****************************************************************************/
typedef struct
{
    RRC_APP_FTM_CHANGE_INFO_TYPE_ENUM_UINT32  ulFtmChangeInfoType;

    union
    {
        RRC_APP_CHANGE_CELL_INFO_STRU             stCellInfo;  /* �仯�ϱ��Ĺ���ģʽ�ṹ--פ��С����Ϣ */
        RRC_APP_PROTOCOL_STATE_IND_ENUM_UINT8     enState;     /* �仯�ϱ��Ĺ���ģʽ�ṹ--״̬��Ϣ������Э��״̬���ڲ�����״̬ */
    }u;
}RRC_APP_FTM_CHANGE_INFO_STRU;
/*****************************************************************************
 �ṹ��    : RRC_APP_FTM_PERIOD_INFO_STRU
 �ṹ˵��  : �����ϱ��Ĺ���ģʽ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                 ulValidNum;
    RRC_APP_PERIOD_CELL_INFO_STRU              astCellInfo[LRRC_APP_MAX_NUM]; /* RRC�����ϱ���APP��פ��С����Ϣ */
}RRC_APP_FTM_PERIOD_INFO_STRU;

/*****************************************************************************
 �ṹ��    : RRC_APP_FTM_INFO_STRU
 �ṹ˵��  : ����ģʽ�ϱ����ݽṹ
*****************************************************************************/
typedef struct
{
    RRC_APP_FTM_TYPE_ENUM_UINT32             enRrcAppFtmType; /* ����ģʽ�£��ϱ���Ϣ����--�����ϱ��ͱ���ϱ����� */

    union
    {
        RRC_APP_FTM_PERIOD_INFO_STRU         stPeriodInfo;    /* ����ģʽ�£������ϱ����ݣ� Idle״̬�ϱ�����ĿǰΪDRX���ڣ�Connected״̬������Ϊ1��*/
        RRC_APP_FTM_CHANGE_INFO_STRU         stChangeInfo;    /* ����ģʽ�£�������ϱ����� */
    }u;
}RRC_APP_FTM_INFO_STRU;

/*****************************************************************************
 �ṹ��    : RRC_APP_FTM_INFO_STRU
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

    RRC_APP_FTM_INFO_STRU               stLrrcFtmInfo;

}LRRC_OM_FTM_REPROT_CONTENT_STRU;

/*****************************************************************************
 �ṹ��    : RRC_APP_FTM_INFO_STRU
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
    LRRC_OM_FTM_REPROT_CONTENT_STRU     stLrrcFtmContent;
}LRRC_OM_FTM_REPROT_IND_STRU;

/*****************************************************************************
                   ERROR LOG�ϱ��ṹ�嶨��
*****************************************************************************/
/*begin:edit by wangmiao00272217 for ErrorLog Rebuild */
/*****************************************************************************
 ö����    : LRRC_OM_ALARMID_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ErrorLog Cnf��Ϣ�ṹ���AlarmIdö��
*****************************************************************************/
enum LRRC_OM_ALARMID_ENUM
{
    LRRC_OM_ALARMID_ENUM_RECFG          = 1,                /*�����ô���*/
    LRRC_OM_ALARMID_ENUM_REEST          = 2,                /*�ؽ�������*/
    LRRC_OM_ALARMID_ENUM_EST            = 3,                /*��������*/
    LRRC_OM_ALARMID_ENUM_LOSTAREA       = 4,                /*����*/
    LRRC_OM_ALARMID_ENUM_OVERFLOW       = 5,                /*��Ϣ���������*/
    LRRC_OM_ALARMID_ENUM_QLOW_CELL      = 6,                /*פ������С���澯*/
    LRRC_OM_ALARMID_ENUM_PINGPONG_RESEL = 7,                /*ƹ����ѡ�澯*/
    LRRC_OM_ALARMID_ENUM_CSFB_FAIL      = 8,                /*CSFBʧ��*/
    LRRC_OM_ALARMID_ENUM_MOBILITY_2_QLOW_CELL = 9,          /*��ѡ���ض�����С���澯*/
    LRRC_OM_ALARMID_ENUM_OUT_OF_SYNC    = 10,               /*ʧ������*/
    LRRC_OM_ALARMID_ENUM_CSEL_INFO      = 11,               /* С��ѡ����Ϣ */
    LRRC_OM_ALARMID_ENUM_BUTT           = 12
};
typedef VOS_UINT16 LRRC_OM_ALARMID_ENUM_UINT16;

/*****************************************************************************
 ö����    : LRRC_OM_ALARMID_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ErrorLog Cnf��Ϣ�ṹ���AlarmIdö��
*****************************************************************************/
enum LRRC_OM_SRCHED_FREQ_SCENARIO_ENUM
{
    LRRC_OM_RREQ_SCENARIO_ENUM_FIRST_MCC = 1,
    LRRC_OM_RREQ_SCENARIO_ENUM_CSEL_SUCC,
    LRRC_OM_RREQ_SCENARIO_ENUM_BUTT
};
typedef VOS_UINT16 LRRC_OM_SRCHED_FREQ_SCENARIO_ENUM_UINT16;

/*****************************************************************************
 �ṹ��    : LRRC_OM_ACC_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RRC������Ϣ�洢
*****************************************************************************/
typedef struct
{
    VOS_UINT8                              ucAsRelBitmap;      /* ��������UE�����汾��1��֧�֣�0����֧�֣��ӵ͵���λ�ֱ�����ָʾRel8,Rel9,.... */
    VOS_UINT8                              aucReserved[3];
    VOS_UINT32                             ulFeatureGroupInds; /* ��μ�36.331 B.1  Feature group indicators �½ڣ���λȡֵ */
}LRRC_OM_ACC_INFO_STRU;

/*****************************************************************************
 �ṹ��    : RRC_RRC_EST_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RRC������Ϣ�洢
*****************************************************************************/
typedef struct
{
    LRRC_APP_LNAS_EST_CAUSE_ENUM_UINT8     enEstCause;             /* ����ԭ�� */
    LRRC_APP_LNAS_EST_RESULT_ENUM_UINT8    enResult;               /* ������� */
    VOS_UINT8                              ucNumOfPrembSentR11;
    VOS_UINT8                              ucContentionDetctR11;
    VOS_UINT8                              ucMaxTxPwrReachedR11;
    VOS_UINT8                              aucRsv[3];
}LRRC_OM_RRC_EST_LIST_INFO_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_OM_STATE_INFO_STRU
 �ṹ˵��  : ERROR LOG RRC״̬��Ϣ
*****************************************************************************/
typedef struct
{
    RRC_APP_PROTOCOL_STATE_IND_ENUM_UINT8       enState;            /* RRCЭ��״̬ */
    VOS_UINT8                                   ucErrcTopMsState;   /* RRC��״̬�����ڲ������״̬�� */
    VOS_UINT8                                   ucErrcTopSsState;   /* RRC��״̬�����ڲ������״̬�� */
    LRRC_APP_FLOW_CTRL_TYPE_ENUM_UINT8          enErrcFlowCtrlType; /* LTE������ϵͳ����ʱ����ϵͳ���̱�ʶ */
}LRRC_OM_STATE_INFO_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_OM_SYNC_INFO_STRU
 �ṹ˵��  : ERR LOG ͬ����Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT32          ulInSyncCnt;   /* LRRC�յ�LPHY�������ͬ������ */
    VOS_UINT32          ulOutSyncCnt;  /* LRRC�յ�LPHY�������ʧ������ */
}LRRC_OM_SYNC_INFO_STRU;

/*****************************************************************************
 ö����    : LRRC_APP_ERR_LOG_RAT_TYPE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ���뼼��ö��ֵ�����ݼ������GUTL���Զ��嵫���ָ���ʽ˳��һ��
*****************************************************************************/
enum LRRC_APP_ERR_LOG_RAT_TYPE_ENUM
{
    LRRC_APP_ERR_LOG_RAT_TYPE_GSM      = 1,      /* GSM ���뼼��*/
    LRRC_APP_ERR_LOG_RAT_TYPE_WCDMA,             /* WCDMA ���뼼��*/
    LRRC_APP_ERR_LOG_RAT_TYPE_LTE,               /* LTE ���뼼��*/
    LRRC_APP_ERR_LOG_RAT_TYPE_TDS,               /* TDS ���뼼��*/
    LRRC_APP_ERR_LOG_RAT_TYPE_BUTT
};
typedef VOS_UINT8  LRRC_APP_ERR_LOG_RAT_TYPE_ENUM_UINT8;

/*****************************************************************************
 ö����    : LRRC_APP_ERR_LOG_AREA_LOST_CAUSE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : �����ϱ�ԭ��ֵ
*****************************************************************************/
enum LRRC_APP_ERR_LOG_AREA_LOST_CAUSE_ENUM
{
    LRRC_APP_ERR_LOG_AREA_LOST_BUTT = 1         /* ��ǰԤ����ö��ֵ*/
};
typedef VOS_UINT8  LRRC_APP_ERR_LOG_AREA_LOST_CAUSE_ENUM_UINT8;

/*****************************************************************************
 �ṹ��    : LRRC_OM_OVERFLOW_INFO_STRU
 �ṹ˵��  : ERR LOG ����������ṹ
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                  stHead;
    VOS_UINT32                              ulCount;    /*�������������*/
}LRRC_OM_OVERFLOW_INFO_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_OM_CAMP_THRESHOLD_STRU
 �ṹ˵��  : С����ѡ�ĵ���ֵ��Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_INT16 sQRxLevMin;                      /* ʵ��ֵ���������*2 */
    VOS_INT16 sQRxLevMinOffset;                /* ʵ��ֵ���������*2,Ĭ��0 */
    VOS_INT16 sQqualMin;                       /* ʵ��ֵ��Ĭ����С RRC_INT16_NEGATIVE_INFINITY*/
    VOS_INT16 sQqualMinOffset;                 /* ʵ��ֵ��Ĭ��0 */
}LRRC_OM_CAMP_THRESHOLD_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_OM_TAC_STRU
 �ṹ˵��  : TAC ��Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucTac;
    VOS_UINT8                           ucTacCont;
    VOS_UINT8                           aucReserved[2];
}LRRC_OM_TAC_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_OM_CELL_MEAS_INFO
 �ṹ˵��  : LTE����С���������
*****************************************************************************/
typedef struct
{
    VOS_INT16                                           sRsrp;                          /* RSRPֵ,ʵ��ֵ */
    VOS_INT16                                           sRsrq;                          /* RSRqֵ��ʵ��ֵ */
    VOS_INT16                                           sRssi;                          /* RSSIֵ��ʵ��ֵ */
    VOS_INT16                                           sSValue;                        /* S Criteria Value */
    VOS_INT16                                           sRValue;                        /* R Criteria Value */
    VOS_INT16                                           sSqual;                         /* S Criteria RSRQ Value */
}LRRC_OM_CELL_MEAS_INFO;

/*****************************************************************************
 �ṹ��    : LRRC_OM_SCELL_ID
 �ṹ˵��  : LTE����С��ʶ����Ϣ������Plmn\Gci\Tac\PhyCellId\Arfcn\Band��
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                          ulGci;                          /* sib1�е�GlobalCellId */
    VOS_UINT32                                          ulMcc;                          /* Mcc */
    VOS_UINT32                                          ulMnc;                          /* Mnc */
    LRRC_OM_TAC_STRU                                    stTac;                          /* tac */
    VOS_UINT16                                          usPhyCellId;                    /* ����С��id */
    VOS_UINT16                                          usUlEarfcn;                     /*����Ƶ�ʣ���λ100khz*/
    VOS_UINT16                                          usDlEarfcn;                     /*����Ƶ�ʣ���λ100khz*/
    VOS_UINT8                                           ucServerCellBandInd;            /* ����band*/
    VOS_UINT8                                           ucRsv;
}LRRC_OM_SCELL_ID;

/*****************************************************************************
 �ṹ��    : LRRC_CHR_SCELL_INFO
 �ṹ˵��  : ����С����Ƶ�㣬������Ƶ�������ޣ�PLMNID�� ���ݽṹ
*****************************************************************************/
typedef struct
{
    LRRC_OM_SCELL_ID                                   stSCellIdInfo;                  /*����С��Id��Ϣ*/
    LRRC_OM_CELL_MEAS_INFO                             stSCellMeasRst;                 /*С���������*/
    LRRC_OM_CAMP_THRESHOLD_STRU                        stCampThreshold;                /*פ������*/
}LRRC_OM_SCELL_INFO;

/*****************************************************************************
 �ṹ��    : LRRC_OM_AREA_LOST_INFO_STRU
 �ṹ˵��  : �����ϱ�ERROR LOG����С����Ƶ�㣬������Ƶ�������ޣ�PLMNID�� ���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                          ulTimeStamp;                    /* ����������ʱ�� */
    VOS_UINT32                                          ulGci;                          /* sib1�е�GlobalCellId */
    VOS_UINT32                                          ulMcc;                          /* MCC,3 bytes      */
    VOS_UINT32                                          ulMnc;                          /* MNC,2 or 3 bytes */
    LRRC_OM_TAC_STRU                                    stTac;                          /* tac */
    VOS_UINT16                                          usPhyCellId;                    /* ����С��id */
    VOS_UINT16                                          usUlEarfcn;                     /*����Ƶ�ʣ���λ100khz*/
    VOS_UINT16                                          usDlEarfcn;                     /*����Ƶ�ʣ���λ100khz*/
    VOS_INT16                                           sRsrp;                          /* RSRPֵ,ʵ��ֵ */
    VOS_INT16                                           sRsrq;                          /* RSRqֵ��ʵ��ֵ */
    VOS_INT16                                           sRssi;                          /* RSSIֵ��ʵ��ֵ */
    LRRC_OM_CAMP_THRESHOLD_STRU                         stCampThreshold;                /* פ������*/
    VOS_UINT8                                           ucServerCellBandInd;            /* ����band*/
    LRRC_APP_ERR_LOG_AREA_LOST_CAUSE_ENUM_UINT8         enSubCase;                      /* ����ԭ��:�ݱ���������չ */
    VOS_UINT8                                           aucResv[2];
}LRRC_OM_AREA_LOST_INFO_STRU;

/*****************************************************************************
 �ṹ��    : RRC_OM_AREA_LOST_STRU
 �ṹ˵��  : ������Ϣ
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                  stHead;
    RRC_APP_ERROR_CODE_ENUM_UINT16          enErrorCode;            /* �������ϱ��ṹ��ÿ��ģ�鵥����� */
    LRRC_APP_ERR_LOG_RAT_TYPE_ENUM_UINT8    enRatType;              /* ��������ʱ�Ľ��뼼�� */
    VOS_UINT8                               ucRsv;
    LRRC_OM_AREA_LOST_INFO_STRU             stAreaLostInfo;        /* ������Ϣ */
}RRC_OM_AREA_LOST_STRU;


/*****************************************************************************
 �ṹ��    : LRRC_OM_EST_INFO_STRU
 �ṹ˵��  : ERR LOG ���ӽ������ݽṹ
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                  stHead;
    RRC_APP_ERROR_CODE_ENUM_UINT16          enErrorCode;            /* �������ϱ��ṹ��ÿ��ģ�鵥����� */
    VOS_UINT16                              usRsv;
    LRRC_OM_SCELL_ID                        stPCellInfo;
    LRRC_OM_CELL_MEAS_INFO                  stPCellMeasInfo;
    LRRC_OM_RRC_EST_LIST_INFO_STRU          stEstInfoList;          /* ������� */
    LRRC_OM_ACC_INFO_STRU                   stAccInfo;              /* RRC����ʱ��UE��������ṹ */
    LRRC_OM_STATE_INFO_STRU                 stRrcAppStateInfo;      /* ��������ʱ��RRC״̬��Ϣ������Э��״̬�����ڲ�����״̬�� */
}LRRC_OM_EST_INFO_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_OM_REEST_INFO_STRU
 �ṹ˵��  : ERR LOG �ؽ������ݽṹ
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU              stHead;
    RRC_APP_ERROR_CODE_ENUM_UINT16      enErrorCode;            /* �������ϱ��ṹ��ÿ��ģ�鵥����� */
    RRC_APP_CONN_REEST_IND_ENUM_UINT8   enReestConnCause;       /* ���һ���ؽ�ԭ�� */
    VOS_UINT8                           ucNumOfPrembSentR11;
    VOS_UINT8                           ucContentionDetctR11;
    VOS_UINT8                           ucMaxTxPwrReachedR11;
    VOS_UINT16                          usRsv;
    LRRC_OM_SCELL_ID                    stPCellInfo;
    LRRC_OM_CELL_MEAS_INFO              stPCellMeasInfo;
    LRRC_OM_SYNC_INFO_STRU              stSyncInfo;             /* �����ͬ����Ϣ */
    LRRC_OM_STATE_INFO_STRU             stRrcAppStateInfo;      /* ��������ʱ��RRC״̬��Ϣ������Э��״̬�����ڲ�����״̬�� */
}LRRC_OM_REEST_INFO_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_OM_RECFG_INFO_STRU
 �ṹ˵��  : ERR LOG ���������ݽṹ
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU              stHead;
    RRC_APP_ERROR_CODE_ENUM_UINT16      enErrorCode;            /* �������ϱ��ṹ��ÿ��ģ�鵥����� */
    VOS_UINT8                           ucNumOfPrembSentR11;
    VOS_UINT8                           ucContentionDetctR11;
    VOS_UINT8                           ucMaxTxPwrReachedR11;
    VOS_UINT8                           ucRsv[3];
    LRRC_OM_SCELL_ID                    stPCellInfo;
    LRRC_OM_CELL_MEAS_INFO              stPCellMeasInfo;
    LRRC_OM_STATE_INFO_STRU             stRrcAppStateInfo;      /* ��������ʱ��RRC״̬��Ϣ������Э��״̬�����ڲ�����״̬�� */
}LRRC_OM_RECFG_INFO_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_OM_SRCHED_FREQ_INFO_STRU
 �ṹ˵��  : ERR LOG �ϱ�����Ƶ����Ϣ
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                      stHead;
    RRC_APP_ERROR_CODE_ENUM_UINT16              enErrorCode;            /* �������ϱ��ṹ��ÿ��ģ�鵥����� */
    VOS_UINT16                                  usBandInd;
    VOS_UINT16                                  usAllBandSrchIdx;
    PS_BOOL_ENUM_UINT8                          enIsHistoryFreqFlg;
    VOS_UINT8                                   ucRsv;
    VOS_UINT32                                  ulDlArfcn;
    VOS_UINT32                                  ulGci;
    VOS_UINT32                                  ulMcc;                  /* Mcc */
    VOS_UINT32                                  ulMnc;                  /* Mnc */
}LRRC_OM_SRCHED_FREQ_INFO_STRU;

/*****************************************************************************
 �ṹ��    : OM_ERR_LOG_REPORT_CNF_STRU
 �ṹ˵��  : Balongƽ̨�ڲ�������ERROR LOG ���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    VOS_UINT32                          ulMsgType;
    VOS_UINT32                          ulMsgSN;
    VOS_UINT32                          ulRptlen;      /* �������ݳ���,���ulRptlenΪ0,aucContent���ݳ���ҲΪ0 */
    VOS_UINT8                           aucContent[4]; /* �������� */
} LRRC_OM_ERR_LOG_REPORT_CNF_STRU;
/*end:edit by wangmiao00272217 for ErrorLog*/

/*****************************************************************************
 �ṹ��    : LRRC_OM_FAULT_ERR_LOG_IND_STRU
 �ṹ˵��  : Balongƽ̨�ڲ������������ϱ�Fault���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    VOS_UINT32                          ulMsgType;
    VOS_UINT32                          ulMsgSN;
    VOS_UINT32                          ulRptlen;      /* �������ݳ���,���ulRptlenΪ0,aucContent���ݳ���ҲΪ0 */
    VOS_UINT8                           aucContent[4]; /* �������� */
}LRRC_OM_FAULT_ERR_LOG_IND_STRU;

typedef LRRC_OM_FAULT_ERR_LOG_IND_STRU LRRC_OM_ALARM_ERR_LOG_IND_STRU;

/*****************************************************************************
�ṹ��    : LRRC_CHR_NCELL_INFO
Э����  :
ASN.1���� :
�ṹ˵��  : ������ѡ�����Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usMeasCnfAndState;
    VOS_UINT16                          usMeasLevel;
}LRRC_OM_NCELL_INFO;

/*****************************************************************************
�ṹ��    : LRRC_ERRLOG_Q_LOW_CELL_INFO
Э����  :
ASN.1���� :
�ṹ˵��  : CHR ��С����¼ rsrq < -15db
*****************************************************************************/
typedef struct
{
    LRRC_OM_SCELL_INFO                 stSCellInfo;                    /* ����С����Ϣ */
    LRRC_OM_NCELL_INFO                 stNcellInfo;                    /* ����������Ϣ*/
    VOS_UINT32                         ulCampTimes;                    /* פ����¼����������*10sΪ��С����פ��ʱ�� */
}LRRC_OM_Q_LOW_CELL_INFO;

/*****************************************************************************
�ṹ��    : LRRC_OM_QLOW_CELL_INFO_STRU
Э����  :
ASN.1���� :
�ṹ˵��  : ��С����Ϣ
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU              stHead;
    RRC_APP_ERROR_CODE_ENUM_UINT16      enErrorCode;            /* �������ϱ��ṹ��ÿ��ģ�鵥����� */
    VOS_UINT16                          usQlowCellInfoNum;
    LRRC_OM_Q_LOW_CELL_INFO             astQLowCellInfoList[LRRC_OM_Q_LOW_CELL_NUM_MAX];
}LRRC_OM_QLOW_CELL_INFO_STRU;

/*****************************************************************************
�ṹ��    : LRRC_OM_UTRA_CELL_INFO
�ṹ˵��  : ƹ����ѡutranС����ѡ��Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usArfcn;
    VOS_UINT16                          usPrimaryCode;                      /* С����Ϣ */
}LRRC_OM_UTRA_CELL_INFO;

/*****************************************************************************
�ṹ��    : LRRC_OM_GSM_CELL_INFO
�ṹ˵��  : ƹ����ѡgsmС����ѡ��Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usArfcn;
    VOS_UINT16                          enBandInd;
    VOS_UINT16                          usNcc;
    VOS_UINT16                          usBcc;
    VOS_UINT16                          usRsv;
    VOS_INT16                           sGeranCellRxlev;
}LRRC_OM_GSM_CELL_INFO;

/*****************************************************************************
�ṹ��    : LRRC_OM_CDMA_CELL_INFO
�ṹ˵��  : ƹ����ѡcdmaС����ѡ��Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucBand;
    VOS_UINT8                           aucRsv[3];
    VOS_UINT16                          usArfcn;
    VOS_UINT16                          usPn;                               /* С����Ϣ */
}LRRC_OM_CDMA_CELL_INFO;

/*****************************************************************************
�ṹ��    : LRRC_OM_PINGPONG_LTE_CELL_INFO
�ṹ˵��  : ƹ����ѡlteС����ѡ��Ϣ
*****************************************************************************/
typedef struct
{
    LRRC_OM_SCELL_ID                        stLteScellId;
    LRRC_OM_CELL_MEAS_INFO                  stScellMeasInfo;
}LRRC_OM_PINGPONG_LTE_CELL_INFO;

/*****************************************************************************
�ṹ��    : LRRC_OM_PINGPONG_CELL_INFO
�ṹ˵��  : ƹ����ѡС����ѡ��Ϣ
*****************************************************************************/
typedef struct
{
    LRRC_OM_RAT_TYPE_ENUM_UINT16         usRatType;
    VOS_UINT16                           usRsv;
    union
    {
        LRRC_OM_PINGPONG_LTE_CELL_INFO   stLteCellInfo;
        LRRC_OM_UTRA_CELL_INFO           stUtraCellInfo;
        LRRC_OM_GSM_CELL_INFO            stGsmCellInfo;
        LRRC_OM_CDMA_CELL_INFO           stCdmaCellInfo;
    }u;
}LRRC_OM_PINGPONG_CELL_INFO;

/*****************************************************************************
�ṹ��    : LRRC_OM_PINGPONG_RESEL_RECORD
�ṹ˵��  : ƹ����ѡ��¼
*****************************************************************************/
typedef struct
{
    VOS_UINT8                               ucPingPongCellNum;
    VOS_UINT8                               ucRsv;
    VOS_UINT16                              usPingPongTimes;
    LRRC_OM_PINGPONG_CELL_INFO              astPpCellReselCellList[LRRC_OM_PING_PONG_CELL_NUM_MAX];
}LRRC_OM_PINGPONG_RESEL_RECORD;

/*****************************************************************************
�ṹ��    : LRRC_CHR_PINGPONG_RESEL_LIST_INFO
�ṹ˵��  : ƹ����ѡ��Ϣ
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                stHead;
    RRC_APP_ERROR_CODE_ENUM_UINT16        enErrorCode;            /* �������ϱ��ṹ��ÿ��ģ�鵥����� */
    VOS_UINT16                            usPpCellReselRecordNum;
    LRRC_OM_PINGPONG_RESEL_RECORD         astPpCellReselRecordList[LRRC_OM_PING_PONG_INFO_NUM_MAX];
}LRRC_OM_PINGPONG_RESEL_INFO_STRU;

/*****************************************************************************
�ṹ��    : RRC_ERRLOG_ESR_CS_FAIL_STRU
Э����  :
ASN.1���� :
�ṹ˵��  : CSʧ�ܼ�¼
*****************************************************************************/
typedef struct
{
    LRRC_OM_SCELL_ID                        stScellId;
    VOS_UINT16                              usCsTotalTimes;                 /* ��cs���� */
    VOS_UINT16                              usCsFailTimes;                  /* csʧ�ܴ��� */
    VOS_UINT16                              usConnPagingRelTimes;           /* ����̬Ѱ���Ż���Ч���� */
    VOS_UINT16                              usCsReestRelTimes;              /* cs�ڼ��ؽ����Ż���Ч���� */
    VOS_UINT16                              usCsExpiredRelTimes;            /* cs�ڼ䳬ʱ�ͷ��Ż���Ч���� */
    VOS_UINT16                              ausRsv[9];
}LRRC_OM_ESR_CS_FAIL_RECORD;

/*****************************************************************************
�ṹ��    : LRRC_OM_CSFB_FAIL_INFO_STRU
Э����  :
ASN.1���� :
�ṹ˵��  : CSFBʧ����Ϣ
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU              stHead;
    RRC_APP_ERROR_CODE_ENUM_UINT16      enErrorCode;            /* �������ϱ��ṹ��ÿ��ģ�鵥����� */
    VOS_UINT16                          usCsfbFailInfoNum;
    LRRC_OM_ESR_CS_FAIL_RECORD          astEsrFailList[LRRC_OM_ESR_NUM_MAX];
}LRRC_OM_CSFB_FAIL_INFO_STRU;

/*****************************************************************************
�ṹ��    : LRRC_CHR_MOBILITY_2_QLOW_CELL_INFO
Э����  :
ASN.1���� :
�ṹ˵��  : Mobility2QLowCell��¼
*****************************************************************************/
typedef struct
{
    LRRC_OM_QLOW_FLOW_TYPE_ENUM_UINT8       usMobiltyFLowType;
    VOS_UINT8                               aucRsv[3];
    LRRC_OM_SCELL_ID                        stScellId;
    LRRC_OM_CELL_MEAS_INFO                  stScellMeasInfo;
}LRRC_OM_MOBILITY_2_QLOW_CELL_RECORD;

/*****************************************************************************
�ṹ��    : LRRC_OM_MOBILITY_2_QLOW_CELL_INFO_STRU
Э����  :
ASN.1���� :
�ṹ˵��  : Mobility2QLowCell��Ϣ
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                  stHead;
    RRC_APP_ERROR_CODE_ENUM_UINT16          enErrorCode;            /* �������ϱ��ṹ��ÿ��ģ�鵥����� */
    VOS_UINT16                              usMobility2QLowInfoNum;
    LRRC_OM_MOBILITY_2_QLOW_CELL_RECORD     astMobility2QLowRecordList[LRRC_OM_MOBILITY_2_QLOW_NUM_MAX];
}LRRC_OM_MOBILITY_2_QLOW_CELL_INFO_STRU;

/*****************************************************************************
�ṹ��    : LRRC_CHR_OUT_OF_SYNC_INFO
Э����  :
ASN.1���� :
�ṹ˵��  : ʧ����¼
*****************************************************************************/
typedef struct
{
    LRRC_OM_SCELL_ID                        stScellId;
    VOS_UINT32                              ulOutOfSyncNum;
    VOS_UINT32                              ulInSyncNum;
}LRRC_OM_OUT_OF_SYNC_RECORD;

/*****************************************************************************
�ṹ��    : LRRC_CHR_OUT_OF_SYNC_INFO_LIST
Э����  :
ASN.1���� :
�ṹ˵��  : ʧ����¼��Ϣ
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                       stHead;
    RRC_APP_ERROR_CODE_ENUM_UINT16               enErrorCode;                   /* �������ϱ��ṹ��ÿ��ģ�鵥����� */
    VOS_UINT16                                   usOutOfSyncRecordNum;          /*ʧ����¼���������Ϊ8*/
    LRRC_OM_OUT_OF_SYNC_RECORD                   astOutOfSyncInfoList[LRRC_OM_OUT_OF_SYNC_NUM_MAX];
}LRRC_OM_OUT_OF_SYNC_INFO_STRU;

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

#endif /* end of LrrcErrLogInterface.h */


