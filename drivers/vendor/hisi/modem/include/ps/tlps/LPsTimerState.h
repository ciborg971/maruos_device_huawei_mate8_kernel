

#ifndef __LPSTIMERSTATE_H__
#define __LPSTIMERSTATE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include  "vos.h"


#pragma pack(4)

/*****************************************************************************
  2 Macro
*****************************************************************************/
#define TI_RRC_PTL_START                ( 0xD000 )


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
/*****************************************************************************
 ö����    : RRC_TIME_STATUS_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ��ʱ����״̬����
*****************************************************************************/
enum RRC_TIME_STATUS_ENUM
{
    RRC_TIMER_DEBUG_STATUS_START,/*������ʱ��*/
    RRC_TIMER_DEBUG_STATUS_STOP,/*��ʱ���Ѿ�ֹͣ*/
    RRC_TIMER_DEBUG_STATUS_MODIFY,/*�޸Ķ�ʱ��*/
    RRC_TIMER_DEBUG_STATUS_EXPIRED /*��ʱ����ʱ*/
};
typedef VOS_UINT32 RRC_TIMER_OPERATE_ENUM_UINT32;
/*****************************************************************************
 ö����    : RRC_MS_ID_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : ״̬����״̬ö�ٶ���
*****************************************************************************/
/*****************************************************************************
 ö����    : RRC_PTL_TI_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : Э�鶨ʱ���͹��ܶ�ʱ�� ����
             BOUNDARY_START����ʶ��ģ�鶨ʱ���ڶ�ʱ�����е���ʼ�±�;
             BOUNDARY_END����ʶ��ģ�鶨ʱ���ڶ�ʱ�����еĽ����±�;
             ����ģ��Ķ�ʱ��������Ҫ�����ڸ�����Ӧ��������.
*****************************************************************************/
enum RRC_PTL_TI_ENUM
{
    /* MAIN ģ�鶨ʱ�� */
    TI_RRC_PTL_MAIN_BOUNDARY_START = TI_RRC_PTL_START,       /* MAIN ��ʱ����ʼ�߽� */
    TI_RRC_PTL_T310,

    /* RRC ģ�鶨ʱ�� */
    TI_RRC_PTL_RRC_BOUNDARY_START,       /* RRC ��ʱ����ʼ�߽� */
    TI_RRC_PTL_T300,
    TI_RRC_PTL_T302,       /* ����MT-CALLʱ,���ӽ�����������ʱ�������˶�ʱ�� */
    TI_RRC_PTL_T303,       /* ��MO-CALLʱ�����ӽ�����������ʱ�������˶�ʱ�� */
    TI_RRC_PTL_T305,       /* ��MO-SIGNALLINGʱ�����ӽ�����������ʱ�������˶�ʱ�� */
    /* v7r2 code begin */
    TI_RRC_PTL_T306,       /* ��MO-CSFBʱ�����ӽ�����������ʱ�������˶�ʱ�� */
    /* v7r2 code end */

    /* V7R2 MDT BEGIN */
    TI_RRC_PTL_T330,       /* �յ�logged MDT��������ʱ�������˶�ʱ�� */
    TI_RRC_PTL_T330_DELAY, /* T330��ʱ������48Сʱ��ʱ���������˶�ʱ�� */
    TI_RRC_PTL_RLF_DELAY,  /* RLF��¼������48Сʱ��ʱ���������˶�ʱ�� */
    /* V7R2 MDT END */

    TI_RRC_RRC_WAIT_SIB_MP,       /* �ȴ�SIB���µı߽絽����ʱ�� */
    TI_RRC_RRC_CONN_REL_DELAY,        /* �յ�UU��RRC CONN RELEASE��Ϣ������60ms�ӳٶ�ʱ�� */

    /* REEST ģ�鶨ʱ�� */
    TI_RRC_PTL_REEST_BOUNDARY_START,       /* REEST ��ʱ����ʼ�߽� */
    TI_RRC_PTL_REEST_T311,       /* �ȴ�RRC�����ؽ�T311��ʱ�� */
    TI_RRC_PTL_REEST_T301,       /* �ȴ�RRC�����ؽ�T301��ʱ�� */

    /* RB ģ�鶨ʱ�� */
    TI_RRC_PTL_RB_BOUNDARY_START,       /* RB ��ʱ����ʼ�߽� */
    TI_RRC_PTL_T304,

    /* CSELPC ģ�鶨ʱ�� */
    TI_RRC_PTL_CSELPC_BOUNDARY_START,       /* CSEL ��ʱ����ʼ�߽� */

    /* CSEL ģ�鶨ʱ�� */
    TI_RRC_PTL_CSEL_BOUNDARY_START,       /* CSEL ��ʱ����ʼ�߽� */
    TI_RRC_PTL_BSIC_VERIFY,                 /* BSIC��֤�����Ч�Զ�ʱ�� */
    TI_RRC_PTL_CSEL_SUITABLE_CELL_DETECT,       /* CSEL ģ��Suitable Cell���ڼ�ⶨʱ�� */
    TI_RRC_PTL_LOSTCOVERAGE,                /* ����������ʱ�� */
    TI_RRC_PTL_CAMPSTICK,                   /* 1s פ����ʱ�� */
    TI_RRC_PTL_T320,                        /* ʹ��ר�����ȼ��Ķ�ʱ�� */
    TI_RRC_PTL_IDLE_NORMALHYST,             /* �ƶ��Լ�ⶨʱ��  THystNormal */
    TI_RRC_PTL_RESELECTION,                 /* ��ѡ��ʱ�� */
    TI_RRC_PTL_TBARRED,                     /* bar��ʱ�� */
    TI_RRC_PTL_TFORBIDDEN,                  /* forbiden��ʱ�� */
    TI_RRC_PTL_GERAN_TBARRED,               /* Gģbar��ʱ�� */
    TI_RRC_PTL_GERAN_TFORBIDDEN,            /* Gģforbiden��ʱ�� */
    TI_RRC_PTL_UTRAN_TBARRED,               /* Uģbar��ʱ�� */
    TI_RRC_PTL_UTRAN_TFORBIDDEN,            /* Uģforbiden��ʱ�� */
    TI_RRC_PTL_G2L_RESEL_PUNISH,        /* G->L��ѡ�ͷ���ʱ�� */
    TI_RRC_PTL_W2L_REDIR_PUNISH,        /* W->L�ض���ͷ���ʱ�� */
    /* MBMS Begin */
    TI_RRC_PTL_MBMS_MCCH_NOTIFY,        /* MCCH msg�仯����������С��ʱ�� */
    /* MBMS End */

    /* CMM ģ�鶨ʱ�� */
    TI_RRC_PTL_RM_BOUNDARY_START,       /* CMM ��ʱ����ʼ�߽� */
    TI_RRC_CMM_NC_EVT_TRIG,
    TI_RRC_CMM_SC_EVT_TRIG,
    TI_RRC_CMM_MOBILITY_NORMALHYST,
    TI_RRC_CMM_PERIOD_RPT,
    TI_RRC_PTL_T321,                    /* CGI�ϱ���ʱ�� */

    /* SIB ģ�鶨ʱ�� */
    TI_RRC_PTL_SIB_BOUNDARY_START,       /* CMM ��ʱ����ʼ�߽� */
    TI_RRC_PTL_SIB_3HOUR_UPDATE,       /* 3Сʱ���¶�ʱ�� */

    TI_RRC_PAGING_VALID_TIMER,  /* PAGING����̬ҵ��Ѱ���յ��󣬸ö�ʱ�������ڼ䣬����ٴ��յ�ҵ��Ѱ�������ж��� */
    /* ITF ģ�鶨ʱ�� */

    /* ASN1 ģ�鶨ʱ�� */
    TI_RRC_PTL_ASN1_BOUNDARY_START,       /* ASN1 ��ʱ����ʼ�߽� */

    /* MNTN ģ�鶨ʱ�� */
    TI_RRC_PTL_MNTN_BOUNDARY_START,       /* MNTN ��ʱ����ʼ�߽� */

    /* gaojishan-fast-dorm-cfg-3 */
    TI_FAST_DORM_CFG_DELAY,               /* fast dorm��ʱ����ʼ�߽� */

    /* CMCC-BEGIN */
    TI_IRAT_REDIR_SEARCH_TIMER,           /* ��ϵͳ�ض����������ƶ�ʱ�� */
    /* CMCC-END */
//#if(FEATURE_MULTI_MODEM == FEATURE_ON)
    /* LRRC MTC AREA LOST Begin */
    TI_MTC_AREA_LOST_TIMER,           /* mtc area lost ���ƶ�ʱ�� */
    /* LRRC MTC AREA LOST End */

    /* LTE PS Transfer begin */
    TI_MTCLOST_PS_TRANSFER_TIMER,     /* LTE->CDMA������ѡ��ʱ�� */
    TI_MTCAVAILABLE_PS_TRANSFER_TIMER,     /* CDMA->LTE������ѡ��ʱ�� */
    /* LTE PS Transfer end */
//#endif

    /* DSDS-BEGIN */
    TI_RRC_DSDS_REL_PS_PAGING_TIMER,      /* �ͷ�dsds��ps paging type����Դ�Ķ�ʱ�� */
    TI_RRC_DSDS_NORF_LOST_COVERAGE,       /* lphy��idle meas indû��dsds����Դʱ���߶����Ķ�ʱ�� */
    TI_RRC_DSDS_SHORT_OCCUPY_RF_RECOVER,  /* lte������̬����Դ�������󣬻ָ�RF��Դ������ʱ�䣬�����ʱ����Ҫ�ͷ��� */
    TI_RRC_DSDS_DELAY_REL_REDIR_RF_RESOURCE_TIME,                   /* 1s פ����ʱ�� */
    TI_RRC_DSDS_OCCUPY_PROTECT_TIMER,     /*�յ��ǽ������ı�����ʱ������ֹ״̬���⣬����һֱ���ظ���ռ�ɹ�*/
    /* DSDS-END */
    /* begin: add for feature v700r500 */
    TI_RRC_PTL_T325,
    TI_RRC_PTL_PWRPREF_IND_TIME,
    /* end: add for feature v700r500 */
    /* add for AT&T LRRC DAM begin */
    TI_RRC_DAM_CELL_BAR_TIMER,    /* DAM������barС����ʱ�� */
    /* add for AT&T LRRC DAM end */

    TI_RRC_PRINT_BUFFER_TIMER,
    TI_RRC_CSFB_OPTIMIZE_PROTECT_TIMER,

    /*begin:add for CHR push notify */
    TI_RRC_CHR_PUSH_NOTIFY_TIMER,   /* 8Сʱ������Ϣ */
    /*end:add for CHR push notify*/
    TI_RRC_PTL_BUTT
};
typedef VOS_UINT16 RRC_PTL_TI_ENUM_UINT16;

/*****************************************************************************
 ö����    : RRC_STATE_TI_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ״̬������ʱ������
             BOUNDARY_START����ʶ��ģ�鶨ʱ���ڶ�ʱ�����е���ʼ�±�;
             BOUNDARY_END����ʶ��ģ�鶨ʱ���ڶ�ʱ�����еĽ����±�;
             ����ģ��Ķ�ʱ��������Ҫ�����ڸ�����Ӧ��������.
*****************************************************************************/
enum RRC_STATE_TI_ENUM
{
    /* MAIN ģ�鶨ʱ�� */
    TI_RRC_STATE_MAIN_BOUNDARY_START = (TI_RRC_PTL_START + 0x100),    /* MAIN ��ʱ����ʼ�߽� */

    /* RRC ģ�鶨ʱ�� */
    TI_RRC_STATE_RRC_BOUNDARY_START,    /* RRC ��ʱ����ʼ�߽� */

    TI_RRC_CSELPC_CELL_RESEL_STOP_CNF,    /* �ȴ�CSLPC����С����ѡֹͣ��Ӧ�Ķ�ʱ�� */
    TI_RRC_CSELPC_CELL_RESEL_START_CNF,    /* �ȴ�CSLPC����С����ѡ������Ӧ�Ķ�ʱ�� */
    TI_RRC_RRC_WAIT_ITFL2_CFG_CNF,    /* �ȴ�ITFL2������Ӧ�Ķ�ʱ�� */
    TI_RRC_RRC_WAIT_ITFL2_REL_CNF,    /* �ȴ�ITFL2�ͷ���Ӧ�Ķ�ʱ�� */
    TI_RRC_RRC_WAIT_ITFPHY_CFG_CNF,    /* �ȴ�ITFPHY������Ӧ�Ķ�ʱ�� */
    TI_RRC_RRC_WAIT_ITFPHY_REL_CNF,    /* �ȴ�ITFPHY�ͷ���Ӧ�Ķ�ʱ�� */
    TI_RRC_RRC_WAIT_MAC_RA_CNF,    /* �ȴ�MAC���������Ӧ�Ķ�ʱ�� */
    TI_RRC_RRC_WAIT_DATA_CNF,    /* �ȴ�PDCP��DATA������Ӧ�Ķ�ʱ�� */
    TI_RRC_RRC_CSELPC_STATE_CHANGE_CNF,    /* �ȴ�CSELPC�����״̬��Ǩ��Ӧ�Ķ�ʱ�� */
    TI_RRC_RRC_CMM_STATE_CHANGE_CNF,    /* �ȴ�CMM�����״̬��Ǩ��Ӧ�Ķ�ʱ�� */
    TI_RRC_RRC_WAIT_DATA_CNF_OF_UL_TRANS,    /* �ȴ�����ֱ����Ϣ�Ĳ�2������Ӧ�ı�����ʱ�� */
    TI_RRC_RRC_WAIT_RRC_CONN_EST_OR_REJECT,    /* �ȴ��տ�RRC���ӽ�����ܾ� */
    TI_LRRC_LRRC_SS_WAIT_ITFL2_RESET_L2_CNF,   /* �ȴ�ITFL2��λMAC��STOP PDCP��REEST RLC����Ӧ��ʱ�� */
    TI_LRRC_LRRC_WAIT_GURRC_UE_CAP_CNF,   /* �ȴ���ȡGURRC UE������Ϣ�Ķ�ʱ�� */
    TI_LRRC_LRRC_WAIT_LPHY_SET_WORK_MODE_CNF,   /* �ȴ�PHYģʽ�л�����Ӧ��ʱ�� */
    TI_LRRC_LRRC_WAIT_LCSELPC_CELL_SEARCH_CNF,   /* �ȴ�LCSELPCС����������Ӧ��ʱ�� */
    TI_LRRC_LRRC_WAIT_LMM_RESUME_RSP,   /* �ȴ�LMM�����Ӧ��ʱ�� */
    TI_LRRC_LRRC_WAIT_LMM_SUSPEND_RSP,   /* �ȴ�LMM������Ӧ��ʱ�� */
    TI_LRRC_LRRC_WAIT_GURRC_CNF,        /* �ȴ�GU RRC�ض���/��ѡ/�л�/CCO��Ӧ�Ķ�ʱ�� */
    TI_LRRC_LRRC_WAIT_LOAD_WDSP_CNF,   /* �ȴ�WRRC����WDSP��Ӧ�Ķ�ʱ�� */
    TI_LRRC_LRRC_WAIT_GURRC_STOP_CNF,  /* �ȴ�GU RRCֹͣ�ض���/��ѡ/�л�/CCO��Ӧ�Ķ�ʱ�� */
    TI_LRRC_LRRC_WAIT_GURRC_REL_ALL_CNF,  /* �ȴ�GURRC REL ALL��Ӧ�Ķ�ʱ�� */
    /* TDS begin */
    TI_LRRC_LRRC_WAIT_TRRC_UE_CAP_CNF,   /* �ȴ���ȡTRRC UE������Ϣ�Ķ�ʱ�� */
    TI_LRRC_LRRC_WAIT_TRRC_CNF,        /* �ȴ�TRRC�ض���/��ѡ/�л�/CCO��Ӧ�Ķ�ʱ�� */
    TI_LRRC_LRRC_WAIT_TRRC_STOP_CNF,  /* �ȴ�TRRCֹͣ�ض���/��ѡ/�л�/CCO��Ӧ�Ķ�ʱ�� */
    TI_LRRC_LRRC_WAIT_TRRC_REL_ALL_CNF,  /* �ȴ�TRRC REL ALL��Ӧ�Ķ�ʱ�� */
    /* TDS end */

    /* REEST ģ�鶨ʱ�� */
    TI_RRC_STATE_REEST_BOUNDARY_START,     /* REEST ��ʱ����ʼ�߽� */
    TI_RRC_REEST_WAIT_NAS_SUSPEND_RABM_RSP,     /* �ȴ�NASֹͣ������Ӧ��ʱ�� */
    TI_RRC_REEST_WAIT_CMM_STATE_CHANGE_CNF,     /* �ȴ�CMM״̬�ı���Ӧ��ʱ�� */
    TI_RRC_REEST_WAIT_ITFL2_CONFIG_L2_CNF,     /* �ȴ�����L2��Ӧ��ʱ�� */
    TI_RRC_REEST_WAIT_ITFPHY_CONFIG_PHY_CNF,     /* �ȴ�����PHY��Ӧ��ʱ�� */
    TI_LRRC_LREEST_WAIT_GURRC_REL_ALL_CNF,  /* �ȴ�GURRC REL ALL��Ӧ�Ķ�ʱ�� */
    /* TDS begin */
    TI_LRRC_LREEST_WAIT_TRRC_REL_ALL_CNF,   /* �ȴ�TRRC REL ALL��Ӧ�Ķ�ʱ�� */
    /* TDS end */
    TI_RRC_REEST_WAIT_CSELPC_STATE_CHANGE_CNF,     /* �ȴ�CSELPC״̬�ı䶨ʱ�� */
    TI_RRC_REEST_WAIT_MAC_RA_CNF,     /* �ȴ�MAC���������Ӧ��ʱ�� */
    TI_RRC_REEST_WAIT_PDCP_DATA_CNF,     /* �ȴ�PDCP���Ϳտ�������Ӧ��ʱ�� */
    TI_RRC_REEST_CONN_REEST_T301,     /* �ȴ�RRC�����ؽ��ط�T301��ʱ�� */
    TI_RRC_REEST_WAIT_RRC_CONN_REEST_OR_REJECT,     /* �ȴ��տ�RRC�����ؽ���ܾ� */
    TI_RRC_REEST_WAIT_SMC_SECU_CONFIG_CNF,     /* �ȴ���ȫ������Ӧ */
    TI_RRC_REEST_WAIT_DSDS_RADIO_RESOURCE_CNF,

    /* RB ģ�鶨ʱ�� */
    TI_RRC_STATE_TI_RB_BOUNDARY_START,     /* RB ��ʱ����ʼ�߽� */
    TI_RRC_RB_WAIT_RABM_STATUS_RSP,     /* ���л���Ϣʱ����NAS���͹�������󣬵ȴ�����NAS��Ӧ��ʱ */
    TI_RRC_RB_WAIT_CMM_HO_CNF,     /* ���л���Ϣʱ����CMM�����л���ʼ�󣬵ȴ�CMM��Ӧ��ʱ */
    TI_RRC_RB_WAIT_ITFPHY_CFG_CNF,     /* ���л���Ϣʱ����PHY�����л���ʼ�󣬵ȴ�PHY��Ӧ��ʱ */
    TI_RRC_RB_WAIT_PHY_SYNC_CNF,     /* ���л���Ϣʱ���ȴ�PHYͬ��CNF��ʱ */
    TI_RRC_RB_WAIT_ITFL2_CFG_CNF,     /* ���л���Ϣʱ������L2���ó�ʱ*/
    TI_RRC_RB_WAIT_SMC_SECU_CFG_CNF,     /* ���л���Ϣʱ����SMC���Ͱ�ȫ������������ʱ����ʱ */
    TI_RRC_RB_WAIT_RABM_STATUS_CNF,     /* ���л���Ϣʱ����NAS���ͽ����������󣬵ȴ�NAS��Ӧ��ʱ */
    TI_RRC_RB_WAIT_CMM_MEAS_CTRL_CNF,     /* ��HO��RB��Ϣʱ��RRC CONNECTION RECONFIGURATION��Ϣ�к���measurement��Ϣ�Ĵ���ʱ */
    TI_RRC_RB_WAIT_PDCP_DATA_CNF,     /* ����AM���ݺ󣬵ȴ�PDCP��Ӧ��ʱ����ʱ */
    TI_RRC_RB_WAIT_REL_NEW_RB_CNF,     /* �ͷ�RB�󣬵ȴ�L2��Ӧ��ʱ����ʱ */
    TI_LRRC_LRB_WAIT_LPHY_SET_WORK_MODE_CNF,   /* �ȴ�PHYģʽ�л�����Ӧ��ʱ�� */
    TI_LRRC_LRB_WAIT_MM_SECU_PARA_RSP,           /* �ȴ�LNAS��ȫ��������Ӧ��ʱ�� */
    TI_LRRC_LRB_WAIT_MM_RESUME_RSP,           /* �ȴ�LNAS��ҵ���Ӧ��ʱ�� */
    TI_LRRC_LRB_WAIT_GURRC_REL_ALL_CNF,  /* �ȴ�GURRC REL ALL��Ӧ�Ķ�ʱ�� */

    /* CSELPC ģ�鶨ʱ��  */
    TI_RRC_STATE_CSELPC_BOUNDARY_START,     /* CSELPC ��ʱ����ʼ�߽� */
    TI_RRC_CSELPC_WAIT_CONFIG_PHY_CNF,     /* �ȴ������������Ӧ�Ķ�ʱ�� */
    TI_RRC_CSELPC_WAIT_PHY_CAMPED_CELL_CNF,     /* �ȴ������פ����Ӧ�Ķ�ʱ�� */
    TI_RRC_CSELPC_WAIT_CONFIG_L2_CNF,
    TI_RRC_CSELPC_WAIT_CSEL_SPEC_PLMN_SEARCH_CNF,     /* �ȴ�cselģ��SPEC PLMN������Ӧ�Ķ�ʱ�� */
    TI_RRC_CSELPC_WAIT_CSEL_PLMN_LIST_SEARCH_CNF,     /* �ȴ�CSEL PLMN LIST������Ӧ�Ķ�ʱ�� */
    TI_RRC_CSELPC_WAIT_CSEL_STOP_PLMN_LIST_CNF,     /* �ȴ�CSELֹͣPLMN LIST��Ӧ�Ķ�ʱ�� */

    TI_RRC_CSELPC_WAIT_CSEL_CELL_SEARCH_CNF,     /* �ȴ�cselģ��������Ӧ�Ķ�ʱ�� */

    TI_RRC_CSELPC_WAIT_CELL_RESEL_STOP_REQ,     /* �ȴ�RRC/REESTС����ѡֹͣ����Ķ�ʱ�� */
    TI_RRC_CSELPC_WAIT_CELL_RESEL_START_REQ,     /* �ȴ�RRC/REESTС����ѡ��ʼ����Ķ�ʱ�� */

    TI_RRC_CSELPC_WAIT_CSEL_RESEL_START_CNF,     /* �ȴ�CSELС����ѡ��ʼ��Ӧ�Ķ�ʱ�� */
    TI_RRC_CSELPC_WAIT_CSEL_RESEL_STOP_CNF,     /* �ȴ�CSELС����ѡֹͣ��Ӧ�Ķ�ʱ�� */

    TI_RRC_CSELPC_WAIT_STATE_CHANGE_REQ,     /* �ȴ�RRC/REEST״̬�л�����Ķ�ʱ�� */
    TI_RRC_CSELPC_WAIT_CSEL_STATE_CHANGE_CNF,     /* �ȴ�CSEL״̬�л���Ӧ�Ķ�ʱ�� */
    TI_RRC_CSELPC_WAIT_SIB_UPDATE_SYSINFO_CNF,     /* �ȴ�SIB����ϵͳ��Ϣ��Ӧ�Ķ�ʱ�� */
    TI_RRC_CSELPC_WAIT_SIB_REL_CNF,                 /* �ȴ�SIB�ͷŵĶ�ʱ�� */
    TI_RRC_CSELPC_WAIT_CSEL_SYS_INFO_CHANGE_CNF,     /* �ȴ�CSELϵͳ��Ϣ�ı���Ӧ�Ķ�ʱ��*/
    TI_RRC_CSELPC_WAIT_CMM_SYSINFO_CHANGE_CNF,     /* �ȴ�CMMϵͳ��Ϣ�ı���Ӧ�Ķ�ʱ��*/
    TI_LRRC_LCSELPC_WAIT_LPHY_SET_WORK_MODE_CNF,   /* �ȴ�PHYģʽ�л�����Ӧ��ʱ�� */

    /* MBMS Begin */
    TI_LRRC_LCSELPC_SS_WAIT_MBMS_FLOW_CMP,
    TI_LRRC_LCSELPC_SS_WAIT_MBMS_MCCH_CFG_CNF,
    TI_LRRC_LCSELPC_SS_WAIT_MBMS_MCCH_MSG_IND,
    TI_LRRC_LCSELPC_SS_WAIT_MBMS_MCCH_RECFG_CNF,
    TI_LRRC_LCSELPC_SS_WAIT_MBMS_L2_CFG_CNF,
    TI_LRRC_LCSELPC_SS_WAIT_MBMS_PHY_CFG_CNF,
    TI_LRRC_LCSELPC_SS_WAIT_MBMS_L2_REL_CNF,
    TI_LRRC_LCSELPC_SS_WAIT_MBMS_PHY_REL_CNF,

     /* MBMS end */


    /* SMC ģ�鶨ʱ�� */
    TI_RRC_STATE_SMC_BOUNDARY_START,        /* SMC ��ʱ����ʼ�߽� */
    TI_RRC_SMC_WAIT_CNF,                    /* PDCP���ñ�����ʱ�� */

    /* CSEL ģ�鶨ʱ�� */
    TI_RRC_STATE_CSEL_BOUNDARY_START,     /* CSEL ��ʱ����ʼ�߽� */
    TI_RRC_CSEL_WAIT_PHY_IND,     /* CSELģ��ȴ�PHY�ظ�С����������ı�����ʱ�� */
    TI_RRC_CSEL_WAIT_PHY_CNF,      /* CSELģ��ȴ�phy�Ĳ�������cnf */
    TI_RRC_CSEL_WAIT_SIB_CNF,     /* CSELģ��ȴ�SIB�ظ�ϵͳ��Ϣ���ձ�����ʱ�� */
    TI_RRC_CSEL_WAIT_GU_MEAS_CNF, /* �ȴ�����GUģ�����ظ���Ϣ������ʱ�� */
    /* TDS begin */
    TI_RRC_CSEL_WAIT_TDS_MEAS_CNF, /* �ȴ�����TDSģ�����ظ���Ϣ������ʱ�� */
    /* TDS end */
    TI_LRRC_LCSEL_WAIT_WRRC_BSIC_VERIFY_CNF,   /* �ȴ�WRRC BSIC��֤��Ӧ�ı�����ʱ�� */
    TI_LRRC_LCSEL_WAIT_LPHY_BSIC_VERIFY_CNF,   /* �ȴ������ BSIC��֤��Ӧ�ı�����ʱ�� */

    /* bgs begin */
    TI_LRRC_LCSELPC_WAIT_LCSELBG_CNF,   /* LCSELPC�ȴ�GURRC������CNF�ı�����ʱ�� */
    TI_LRRC_LCSEL_WAIT_LCSELPC_CNF,   /* LCSEL�ȴ�LCSELPC������CNF�ı�����ʱ�� */
    TI_LRRC_LCSELBG_WAIT_GURRC_CNF,   /* �ȴ�GURRC������CNF�ı�����ʱ�� */
    TI_LRRC_LCSELBG_WAIT_GURRC_IND,   /* �ȴ�GURRC������IND�ı�����ʱ�� */
    /* bgs end */
    TI_RRC_CSEL_WAIT_RSSI_SORT_IND,   /*�ȴ������Ƶ��������Ϣ*/
    TI_RRC_CSEL_WAIT_BGSRESEL_PREWORK_IND,   /*�ȴ���������ѡ��ʽPREWORK*/
    TI_RRC_CSEL_WAIT_BGSRESEL_SIBACQIRE_CNF,   /*�ȴ���������ѡ��ʽ��ʱ*/

    /* SIBģ�鶨ʱ�� */
    TI_RRC_SIB_WAIT_RL_SETUP_CNF,     /* �����ŵ�������ʱ�� */
    TI_RRC_SIB_WAIT_MIB_IND,     /* MIB���ձ�����ʱ�� */
    TI_RRC_SIB_WAIT_RL_REL_CNF,     /* �����ŵ��ͷŶ�ʱ�� */
    TI_RRC_SIB_WAIT_SIB1_IND,     /* SIB1���ձ�����ʱ�� */
    TI_RRC_SIB_WAIT_PHY_CNF,      /* SI ���ñ�����ʱ�� */
    TI_RRC_SIB_WAIT_SIB_IND,     /* SIBn���ձ�����ʱ�� */

    /* CMM ģ�鶨ʱ�� */
    TI_RRC_STATE_CMM_BOUNDARY_START,     /* CMM ��ʱ����ʼ�߽� */
    TI_RRC_CMM_WAIT_PHY_CNF,     /* ��������ñ�����ʱ�� */
    TI_LRRC_LCMM_WAIT_WRRC_BSIC_VERIFY_CNF,   /* �ȴ�WRRC BSIC��֤��Ӧ�ı�����ʱ�� */
    TI_LRRC_LCMM_WAIT_LPHY_BSIC_VERIFY_CNF,   /* �ȴ������ BSIC��֤��Ӧ�ı�����ʱ�� */
    TI_RRC_CMM_WAIT_GU_MEAS_CNF, /* �ȴ�����GUģ�����ظ���Ϣ������ʱ�� */
    /* TDS begin */
    TI_RRC_CMM_WAIT_UTRA_TDD_MEAS_CNF, /* �ȴ�����TDSģ�����ظ���Ϣ������ʱ�� */
    /* TDS end */

    /* ITF ģ�鶨ʱ�� */
    TI_RRC_ITF_WAIT_CNF,

    /* ASN1 ģ�鶨ʱ�� */
    TI_RRC_STATE_ASN1_BOUNDARY_START,     /* ASN1 ��ʱ����ʼ�߽� */

    /* MNTN ģ�鶨ʱ�� */

    /* ���� ��ʱ�� */
    TI_RRC_STATE_FSM_PROTECT_ERRC,     /* ERRC״̬������������ʱ�� */
    TI_RRC_STATE_FSM_PROTECT_CSEL,     /* CSEL״̬������������ʱ�� */
    TI_RRC_STATE_FSM_PROTECT_CMM,     /* CMM״̬������������ʱ�� */
    TI_RRC_STATE_FSM_PROTECT_SIB,     /* SIB״̬������������ʱ�� */
    /* bgs begin */
    TI_RRC_STATE_FSM_PROTECT_CSELBG,  /* CSELBG״̬������������ʱ�� */
    TI_LRRC_LCSELBG_PROTECT_SLAVE_SUSPEND,   /* L��ģ״̬�¹���̬������ʱ�� xrm todo */
    /* bgs end */

    TI_RRC_APP_RSSI_REPORT,           /* RSSI�����ϱ���ʱ�� */
    /* begin: 2014-03- 20 CL MULT add */
    TI_LRRC_LRRC_WAIT_CDMA_CNF,
    TI_LRRC_LRRC_WAIT_CDMA_STOP_CNF,
    /* end: 2014-03- 20 CL MULT add */

    /* DSDS BEGIN */
	TI_LRRC_WAIT_RRM_RADIO_RESOURCE_CNF,
	/* DSDS END */

    TI_RRC_PTL_CONNESTFAIL_DELAY,  /* connestfail��¼������48Сʱ��ʱ���������˶�ʱ�� */
    /* begin: add mbms for feature v700r500 */
    TI_LRRC_LRRC_WAIT_CONN_TO_IDLE_CNF,
    TI_RRC_CSELPC_WAIT_CONN_TO_IDLE_REQ,
    /* end: add mbms for feature v700r500 */

    /* add for Balong CL begin */
    TI_LRRC_LRRC_WAIT_CAS_REL_ALL_CNF,
    TI_LRRC_LRRC_WAIT_CAS_RESEL_CNF,
    TI_LRRC_LRRC_WAIT_CAS_REDIRECT_CNF,
    TI_RRC_CSEL_WAIT_CDMA_HRPD_MEAS_CNF,    /* �ȴ�����CDMA HRPD�����ظ���Ϣ������ʱ�� */
    TI_RRC_CMM_WAIT_HRPD_MEAS_CNF,
    /* add for Balong CL end */

    TI_LRRC_LCSELPC_SS_WAIT_MBMS_PHY_ENABLE_CNF,
    TI_LRRC_LCSELPC_SS_WAIT_MBMS_PHY_DISABLE_CNF,
    TI_LRRC_LCSELPC_SS_WAIT_MBMS_NOTIFY_CFG_CNF,
    TI_LRRC_LCSELPC_SS_WAIT_MBMS_PMCH_CFG_CNF,
    TI_LRRC_LCSELPC_SS_WAIT_MBMS_PMCH_ACTIVE_CNF,

    TI_LRRC_LCMM_WAIT_LPP_LPHY_OTDOA_CNF,
    TI_LRRC_LRRC_WAIT_LPP_LCMM_OTDOA_CNF,

    TI_RRC_STATE_BUTT
};
typedef VOS_UINT16 RRC_STATE_TI_ENUM_UINT16;


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

#endif /* end of LPsTimerState.h */
