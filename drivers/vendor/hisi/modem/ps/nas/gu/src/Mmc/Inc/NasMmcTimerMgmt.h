/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : NasMmcTimerMgmt.h
  �� �� ��   : ����
  ��    ��   : zhoujun 40661
  ��������   : 2011��5��30��
  ����޸�   : 2011��5��30��
  ��������   : ���嶨ʱ������ģ��Ľӿ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2011��5��30��
    ��    ��   : zhoujun 40661
    �޸�����   : �����ļ�
******************************************************************************/
#ifndef  NAS_MMC_TIMER_MGMT_PROC_H
#define  NAS_MMC_TIMER_MGMT_PROC_H

#pragma pack(4)

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "vos.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 �궨��
*****************************************************************************/

/* MMC��ͬʱ���еĶ�ʱ���������Ŀ,Ĭ��Ϊ30�� */
#define NAS_MMC_MAX_TIMER_NUM                       (30)

/* MMC�ж�ʱ����ʱ�� */
#define TI_NAS_MMC_WAIT_MM_START_CNF_LEN            (30*1000)


#define TI_NAS_MMC_WAIT_GAS_START_CNF_LEN           (7*1000)                    /* GAS��������ʱ��Ϊ5S */

#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
#define TI_NAS_MMC_WAIT_WAS_START_CNF_LEN           (40*1000)                   /* MMC�ȴ�WAS��TDģ�Ŀ����ظ���ʱ��ʱ�� */
#else
#define TI_NAS_MMC_WAIT_WAS_START_CNF_LEN           (8 * 1000)                  /* WAS�ı�����ʱ��Ϊ5S,NAS���ӱ�����7S */
#endif

#define TI_NAS_MMC_WAIT_LMM_START_CNF_LEN           (30*1000)
#define TI_NAS_MMC_WAIT_READ_SIM_FILES_LEN          (10*1000)
#define TI_NAS_MMC_WAIT_GAS_SYSCFG_CNF_LEN          (10*1000)

#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
#define TI_NAS_MMC_WAIT_WAS_SYSCFG_CNF_LEN           (21 * 1000)                /* MMC�ȴ�WAS��TDģ��SYSCFG���ûظ���ʱ�� */
#else
#define TI_NAS_MMC_WAIT_WAS_SYSCFG_CNF_LEN           (10 * 1000)
#endif

#define TI_NAS_MMC_WAIT_LMM_SYSCFG_CNF_LEN          (10*1000)
#define TI_NAS_MMC_WAIT_EPS_CONN_REL_IND_LEN        (10*1000)
#define TI_NAS_MMC_WAIT_RRC_CONN_REL_LEN            (15*1000)
#define TI_NAS_MMC_FORBID_LA_TIMER_LEN              (12*60*60*1000)
#define TI_NAS_MMC_AVAILABLE_TIMER_LEN              (5*1000)
#define TI_NAS_MMC_HPLMN_TIMER_FIRST_LEN            (2*60*1000)
#define TI_NAS_MMC_HPLMN_TIMER_DEFAULT_LEN          (60 * 60 * 1000)
#define TI_NAS_MMC_DEFAULT_MAX_SEARCH_HPLMN_LEN     (18*60*1000)                /* Ĭ�ϵ����HPLMN��������18���� */

#define TI_NAS_MMC_HIGH_RPIO_RAT_HPLMN_TIMER_FIRST_LEN              (2 * 60)
#define TI_NAS_MMC_HIGH_PRIO_RAT_HPLMN_TIMER_NON_FIRST_LEN          (30 * 60)
#define TI_NAS_MMC_HIGH_RPIO_RAT_HPLMN_TIMER_FIRST_SEARCH_COUNT     (1)

#define TI_NAS_MMC_WAIT_MM_SUSPEND_RSP_LEN          (8*1000)

#define TI_NAS_MMC_WAIT_AS_RESUME_IND_LEN           (90*1000)

#define TI_NAS_MMC_DSDS_WAIT_AS_RESUME_IND_LEN                          (160 * 1000)
#define TI_NAS_MMC_DSDS_INTER_SYS_GU_REDIR_WAIT_AS_RESUME_IND_LEN       (160*1000)
#define TI_NAS_MMC_DSDS_INTER_SYS_OOS_WAIT_AS_RESUME_IND_LEN            (160*1000)

#define TI_NAS_MMC_WAIT_CMMCA_RESUME_IND_LEN        (180*1000)

#define TI_NAS_MMC_INTER_SYS_OOS_WAIT_AS_RESUME_IND_LEN          (90*1000)
#define TI_NAS_MMC_INTER_SYS_GU_REDIR_WAIT_AS_RESUME_IND_LEN     (90*1000)
#define TI_NAS_MMC_INTER_SYS_GUL_REDIR_WAIT_AS_RESUME_IND_LEN     (200*1000)
#define TI_NAS_MMC_WAIT_WAS_SUSPEND_REL_CNF_LEN     (6*1000)
#define TI_NAS_MMC_WAIT_GAS_SUSPEND_REL_CNF_LEN     (10*1000)
#define TI_NAS_MMC_WAIT_LMM_SUSPEND_REL_CNF_LEN     (8*1000)
#define TI_NAS_MMC_WAIT_MM_RESUME_RSP_LEN           (5*1000)

#define TI_NAS_MMC_PERIOD_DELETE_DISABLED_PLMN_WITH_RAT_TIMER_LEN (60 * 1000)  /* ��ʱ��ʱ��Ϊ1����*/

/* �Ƚ�����SYSINFO�Ķ�ʱ������ʹ�� */

#define TI_NAS_MMC_WAIT_EST_IND_LEN                 (20*1000)
#define TI_NAS_MMC_WAIT_AS_SUSPEND_IND_LEN          (20*1000)
#define TI_NAS_MMC_WAIT_LMM_USIM_STATUS_CNF_LEN     (5*1000)
#define TI_NAS_MMC_WAIT_MM_POWEROFF_CNF_LEN         (10*1000)

#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
/* �Ƚ����ػ��ظ��Ķ�ʱ������ʹ�� */
#define TI_NAS_MMC_WAIT_MASTER_MODE_POWEROFF_CNF_LEN        (21 * 1000)         /* ֪ͨ�ر���ģʱ�ı�����ʱ��ʱ�� */
#define TI_NAS_MMC_WAIT_SLAVE_MODE_POWEROFF_CNF_LEN         (21 * 1000)         /* ֪ͨ�رմ�ģʱ�ı�����ʱ��ʱ�� */
#else
/* �Ƚ����ػ��ظ��Ķ�ʱ������ʹ�� */
#define TI_NAS_MMC_WAIT_MASTER_MODE_POWEROFF_CNF_LEN        (10 * 1000)         /* ֪ͨ�ر���ģʱ�ı�����ʱ��ʱ�� */
#define TI_NAS_MMC_WAIT_SLAVE_MODE_POWEROFF_CNF_LEN         (10 * 1000)         /* ֪ͨ�رմ�ģʱ�ı�����ʱ��ʱ�� */
#endif

#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
#define TI_NAS_MMC_WAIT_UTRAN_PLMN_SEARCH_CNF_LEN   (301 * 1000)                /* ƽ̨ͬʱ֧��W/TDʱ���������ظ��ı�����ʱ��ʱ�� */
#endif
#define TI_NAS_MMC_WAIT_WAS_PLMN_SEARCH_CNF_LEN     (150 * 1000)

#define TI_NAS_MMC_WAIT_WAS_FAST_PLMN_SEARCH_CNF_LEN        (150 * 1000)        /* ��W�¿���ָ����ʱ��Ķ�ʱ��ʱ�� */

#define TI_NAS_MMC_DSDS_SCEAN_WAIT_GAS_PLMN_SEARCH_CNF_LEN     (17000*1000)     /* ��ǰԼΪ4Сʱ��ע��OSA�����ʱ��Ϊ18Сʱ */

#define TI_NAS_MMC_WAIT_GAS_PLMN_SEARCH_CNF_LEN     (90*1000)
#define TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF_LEN     (120*1000)

#define TI_NAS_MMC_WAIT_WAS_SUSPEND_CNF_LEN         (10 * 1000)

#define TI_NAS_MMC_WAIT_GAS_SUSPEND_CNF_LEN         (10*1000)
#define TI_NAS_MMC_WAIT_LMM_SUSPEND_CNF_LEN         (10*1000)
#define TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF_LEN       (7*1000)
#define TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF_LEN       (7*1000)
#define TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF_LEN       (7*1000)

#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
#define TI_NAS_MMC_WAIT_WAS_SYS_INFO_LEN                                (23 * 1000)

/* ���������У�WAS�ϱ�ϵͳ��Ϣʱ��ϳ����˴�����Ϊ20S */
#define TI_NAS_MMC_INTER_SYS_FALL_BACK_WAIT_WAS_SYS_INFO_LEN            (33 * 1000)
#define TI_NAS_MMC_WAIT_GAS_SYS_INFO_LEN                                (23 * 1000)
#define TI_NAS_MMC_WAIT_LMM_SYS_INFO_LEN                                (23 * 1000)
#else
#define TI_NAS_MMC_WAIT_WAS_SYS_INFO_LEN                                (10*1000)

/* ���������У�WAS�ϱ�ϵͳ��Ϣʱ��ϳ����˴�����Ϊ20S */
#define TI_NAS_MMC_INTER_SYS_FALL_BACK_WAIT_WAS_SYS_INFO_LEN            (20 * 1000)
#define TI_NAS_MMC_WAIT_GAS_SYS_INFO_LEN                                (10 * 1000)
#define TI_NAS_MMC_WAIT_LMM_SYS_INFO_LEN                                (10 * 1000)
#endif

/* �޸�GU�µȴ�CSPS��ע����ʱ����375��Ϊ495S */
/* �޸�GU�µȴ�CSPS��ע����ʱ����495��Ϊ675S */
#define TI_NAS_MMC_WAIT_CSPS_REG_IND_LEN            (675*1000)
#define TI_NAS_MMC_WAIT_TBF_REL_LEN                 (10*1000)
#define TI_NAS_MMC_WAIT_EPS_REG_IND_LEN             (180*1000)
#define TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST_LEN     (5*1000)
#define TI_NAS_MMC_PERIOD_TRYING_INTER_PLMN_LIST_LEN    (5*1000)

#define TI_NAS_MMC_CAMP_ON_WAIT_WAS_PLMN_LIST_CNF_LEN       (320*1000)          /* פ��̬��MMC�ȴ�WAS�б��ѵ�ʱ��(��ģ) */
#define TI_NAS_MMC_CAMP_ON_WAIT_GAS_PLMN_LIST_CNF_LEN       (320*1000)          /* פ��̬��MMC�ȴ�GAS�б��ѵ�ʱ��(��ģ) */
#define TI_NAS_MMC_CAMP_ON_WAIT_LMM_PLMN_LIST_CNF_LEN       (320*1000)          /* פ��̬��MMC�ȴ�L�б��ѵ�ʱ��(��ģ) */

#define TI_NAS_MMC_NOT_CAMP_ON_WAIT_WAS_PLMN_LIST_CNF_LEN   (180*1000)          /* ��פ��̬��MMC�ȴ�WAS�б��ѵ�ʱ��(��ģ) */
#define TI_NAS_MMC_NOT_CAMP_ON_WAIT_GAS_PLMN_LIST_CNF_LEN   (180*1000)          /* ��פ��̬��MMC�ȴ�GAS�б��ѵ�ʱ��(��ģ) */
#define TI_NAS_MMC_NOT_CAMP_ON_WAIT_LMM_PLMN_LIST_CNF_LEN   (190*1000)          /* ��פ��̬��MMC�ȴ�L�б��ѵ�ʱ��(��ģ) */

#define TI_NAS_MMC_WAIT_WAS_BG_PLMN_SEARCH_CNF_LEN      (180*1000)
#define TI_NAS_MMC_WAIT_GAS_BG_PLMN_SEARCH_CNF_LEN      (180*1000)
#define TI_NAS_MMC_WAIT_WAS_BG_PLMN_STOP_CNF_LEN        (10*1000)
#define TI_NAS_MMC_WAIT_GAS_BG_PLMN_STOP_CNF_LEN        (10*1000)
#define TI_NAS_MMC_PERIOD_TRYING_HIGH_PRIO_PLMN_SEARCH_LEN  (10*1000)
#define TI_NAS_MMC_STK_STEERING_TRYING_HIGH_PRIO_PLMN_SEARCH_LEN  (1*1000)

#define TI_NAS_MMC_ACTING_HPLMN_REFRESH_TRYING_HIGH_PRIO_PLMN_SEARCH_LEN  (1*1000)

#define TI_NAS_MMC_WAIT_WAS_OOS_SYS_INFO_LEN                      (155*1000)

/* �ػ�ʱRECAMP VPLMN�Ķ�ʱ��ʱ�� */
#define TI_NAS_MMC_FAST_RECAMP_VPLMN_WAIT_WAS_PLMN_SEARCH_CNF_LEN     (5 * 1000)
#define TI_NAS_MMC_FAST_RECAMP_VPLMN_WAIT_GAS_PLMN_SEARCH_CNF_LEN     (5 * 1000)
#define TI_NAS_MMC_FAST_RECAMP_VPLMN_WAIT_LMM_PLMN_SEARCH_CNF_LEN     (5 * 1000)

#define TI_NAS_MMC_WAIT_LMM_BG_PLMN_STOP_CNF_LEN            (10*1000)
#define TI_NAS_MMC_WAIT_LMM_BG_PLMN_SEARCH_CNF_LEN          (180*1000)


/* ɾ��TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER_LEN��nv���л�ȡ */

#define TI_NAS_MMC_PERIODIC_NET_SCAN_TIMER_LEN              (10 * 1000)

#define TI_NAS_MMC_NCELL_PLMN_SEARCH_AVAILABLE_TIMER_LEN    (1 * 1000)          /* 1s��ʱ�� */

/*********************************UTRANCTRLģ����ض�ʱ��ʱ��*********************************/
/* UTRANCTRLģ��PLMN SELECTION״̬����ض�ʱ�� */
#define TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF_LEN            (10*1000)
#define TI_NAS_UTRANCTRL_WAIT_TD_PLMN_SEARCH_CNF_LEN        (150*1000)          /* TD�µ�DSP����ʱ��Ϊ150S, */
#define TI_NAS_UTRANCTRL_WAIT_TD_PLMN_STOP_CNF_LEN          (7*1000)
#define TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF_LEN           (10 * 1000)
#define TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_SEARCH_CNF_LEN       (150 * 1000)
#define TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_STOP_CNF_LEN         (7 * 1000)

/* UTRANCTRLģ��MODE CHANGE״̬����ض�ʱ�� */
#define TI_NAS_UTRANCTRL_WAIT_SLAVEMODE_UTRAN_MODE_CNF_LEN  (5*1000)
#define TI_NAS_UTRANCTRL_WAIT_MASTERMODE_UTRAN_MODE_CNF_LEN (3*1000)

/* UTRANCTRL: POWER OFF״̬��ض�ʱ�� */
#define TI_NAS_UTRANCTRL_WAIT_TD_POWER_OFF_CNF_LEN          (12 * 1000)
#define TI_NAS_UTRANCTRL_WAIT_WAS_POWER_OFF_CNF_LEN         (12 * 1000)         /* WAS�ػ�����ʱ��Ϊ10S */

/* UTRANCTRL: SWITCH ON״̬��ض�ʱ�� */
#define TI_NAS_UTRANCTRL_WAIT_TD_START_CNF_LEN              (32 * 1000)         /* TD�Ŀ�������ʱ��Ϊ30S */
#define TI_NAS_UTRANCTRL_WAIT_WAS_START_CNF_LEN             (7 * 1000)          /* WAS�Ŀ�������ʱ��Ϊ5S */

/* UTRANCTRL: syscfg״̬��ض�ʱ�� */
#define TI_NAS_UTRANCTRL_WAIT_TD_SYSCFG_CNF_LEN             (10 * 1000)
#define TI_NAS_UTRANCTRL_WAIT_WAS_SYSCFG_CNF_LEN            (10 * 1000)
/******************************************************************************************************************************/

#define TI_NAS_MMC_WAIT_MSCC_REG_REQ_LEN                     (60 * 1000)

/* Added by y00307564 for CDMA Iteration 8 2015-2-8 begin */
#define TI_NAS_MMC_WAIT_USIM_SET_FILE_CNF_LEN                (5 * 1000)
/* Added by y00307564 for CDMA Iteration 8 2015-2-8 end */

/* Added by l00324781 for CDMA Iteration 10, 2015-4-7, begin */
#define   TI_NAS_MMC_WAIT_LMM_BG_SEARCH_HRPD_CNF_LEN          (100*1000)
/* Added by l00324781 for CDMA Iteration 10, 2015-4-7, end */
#define TI_NAS_MMC_WAIT_CSS_BAND_SCAN_CNF_LEN                (2 * 1000)
#define TI_NAS_MMC_WAIT_CSS_STOP_BAND_SCAN_CNF_LEN           (2 * 1000)

/* Added by l00324781 for CDMA Iteration 12, 2015-5-29, begin */
/* CLģʽ�£�LTE2HRPD��ʱ��ʱ���� ��ѡΪ35s��
��Ϊ�ض�����ҪȫƵ����������ȷ�������飬һ�����һ��Ƶ����Ҫ150s
������Ҫ��������,�����ݶ�Ϊ180S
*/
#define   TI_NAS_MMC_WAIT_MSCC_INTERSYS_HRPD_NTF_REDIR_LEN      (180*1000)
#define   TI_NAS_MMC_WAIT_MSCC_INTERSYS_HRPD_NTF_RESELCT_LEN    (35*1000)
/* Added by l00324781 for CDMA Iteration 12, 2015-5-29, end */

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

enum NAS_MMC_TIMER_ID_ENUM
{
    /* ��ʼ��ʱ����ֵΪ8192����ASN����һ�� */
    TI_NAS_MMC_FORBID_LA_TIMER                     = 8192,
    TI_NAS_MMC_AVAILABLE_TIMER                     = 8193,
    TI_NAS_MMC_HPLMN_TIMER                         = 8194,

    /* ������ض�ʱ��*/
    TI_NAS_MMC_WAIT_MM_START_CNF                   = 8195,
    TI_NAS_MMC_WAIT_LMM_START_CNF                  = 8197,
    TI_NAS_MMC_WAIT_READ_SIM_FILES                 = 8198,

    /* plmn srch ����������ض�ʱ�� */
    TI_NAS_MMC_WAIT_WAS_PLMN_SEARCH_CNF            = 8199,
    TI_NAS_MMC_WAIT_GAS_PLMN_SEARCH_CNF            = 8200,
    TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF            = 8201,
    TI_NAS_MMC_WAIT_WAS_SUSPEND_CNF                = 8202,
    TI_NAS_MMC_WAIT_GAS_SUSPEND_CNF                = 8203,
    TI_NAS_MMC_WAIT_LMM_SUSPEND_CNF                = 8204,
    TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF              = 8205,
    TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF              = 8206,
    TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF              = 8207,

    /* ע�ᴦ����ض�ʱ�� */
    TI_NAS_MMC_WAIT_WAS_SYS_INFO                   = 8208,
    TI_NAS_MMC_WAIT_GAS_SYS_INFO                   = 8209,
    TI_NAS_MMC_WAIT_LMM_SYS_INFO                   = 8210,
    TI_NAS_MMC_WAIT_CSPS_REG_IND                   = 8211,
    TI_NAS_MMC_WAIT_RRC_CONN_REL                   = 8212,
    TI_NAS_MMC_WAIT_TBF_REL                        = 8213,

    /* POWER OFF ״̬��ض�ʱ�� */
    TI_NAS_MMC_WAIT_LMM_USIM_STATUS_CNF            = 8214,
    TI_NAS_MMC_WAIT_MM_POWEROFF_CNF                = 8215,

    /* �Ƚ����ػ��ظ��Ķ�ʱ������ʹ�� */

    /* suspend״̬��ض�ʱ�� */
    TI_NAS_MMC_WAIT_MM_SUSPEND_RSP                 = 8217,                      /* �ȴ�MM/GMMģ�����ظ��ı�����ʱ�� */
    TI_NAS_MMC_WAIT_AS_RESUME_IND                  = 8218,                      /* �ȴ�������ϱ��ָ�ָʾ�ı�����ʱ�� */
    TI_NAS_MMC_WAIT_MM_RESUME_RSP                  = 8219,                      /* �ȴ�MM/GMMģ��ָ��ظ��ı�����ʱ�� */
    TI_NAS_MMC_WAIT_WAS_SUSPEND_REL_CNF            = 8220,                      /* �ȴ�WAS�Ĺ����ͷŻظ��ı�����ʱ�� */
    TI_NAS_MMC_WAIT_EST_IND                        = 8221,                      /* �ȴ�CS/PS/EPS�Ľ������ָʾ�ı�����ʱ�� */
    TI_NAS_MMC_WAIT_AS_SUSPEND_IND                 = 8222,                      /* CCO����ʱ�ȴ�������ϱ�����ָʾ�ı�����ʱ�� */

    /* �ȴ�ע������ض�ʱ�� */
    TI_NAS_MMC_WAIT_EPS_REG_IND                    = 8223,
    TI_NAS_MMC_WAIT_EPS_CONN_REL_IND               = 8224,

    /* LIST������ض�ʱ��*/
    TI_NAS_MMC_WAIT_WAS_PLMN_LIST_CNF              = 8225,                      /* �ȴ�WAS��PLMN LIST�����ظ��ı�����ʱ�� */
    TI_NAS_MMC_WAIT_GAS_PLMN_LIST_CNF              = 8226,                      /* �ȴ�GAS��PLMN LIST�����ظ��ı�����ʱ�� */
    TI_NAS_MMC_WAIT_LMM_PLMN_LIST_CNF              = 8227,                      /* �ȴ�LMM��PLMN LIST�����ظ��ı�����ʱ�� */
    TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST        = 8228,                      /* �����Գ����û�LIST�����Ķ�ʱ�� */
    TI_NAS_MMC_PERIOD_TRYING_INTER_PLMN_LIST       = 8229,                      /* �����Գ����ڲ�LIST�����Ķ�ʱ�� */

    /* syscfg״̬��ض�ʱ��*/
    TI_NAS_MMC_WAIT_GAS_SYSCFG_CNF                 = 8230,
    TI_NAS_MMC_WAIT_WAS_SYSCFG_CNF                 = 8231,
    TI_NAS_MMC_WAIT_LMM_SYSCFG_CNF                 = 8232,

    /* �����ȼ�������ض�ʱ��*/
    TI_NAS_MMC_WAIT_WAS_BG_PLMN_SEARCH_CNF         = 8233,                      /* �ȴ�WAS BG�������������ʱ����ʱ��180s */
    TI_NAS_MMC_WAIT_GAS_BG_PLMN_SEARCH_CNF         = 8234,                      /* �ȴ�GAS BG�������������ʱ����ʱ��180s */
    TI_NAS_MMC_WAIT_WAS_BG_PLMN_STOP_CNF           = 8235,                      /* �ȴ�WASֹͣBG�������������ʱ����ʱ��30s */
    TI_NAS_MMC_WAIT_GAS_BG_PLMN_STOP_CNF           = 8236,                      /* �ȴ�GASֹͣBG�������������ʱ����ʱ��30s */
    TI_NAS_MMC_PERIOD_TRYING_HIGH_PRIO_PLMN_SEARCH = 8237,                      /* �����Գ��Ը����ȼ������Ķ�ʱ����ʱ��10s */

    TI_NAS_MMC_WAIT_WAS_OOS_SYS_INFO               = 8238,

    TI_NAS_MMC_WAIT_LMM_BG_PLMN_SEARCH_CNF         = 8239,                      /* �ȴ�Lmm BG�������������ʱ�� */
    TI_NAS_MMC_WAIT_LMM_BG_PLMN_STOP_CNF           = 8240,                      /* �ȴ�LMMֹͣBG�������������ʱ�� */

    /* MMC: SWITCH ON״̬��ض�ʱ�� */
    TI_NAS_MMC_WAIT_GAS_START_CNF                           = 8241,
    TI_NAS_MMC_WAIT_WAS_START_CNF                           = 8242,
    TI_NAS_MMC_WAIT_MASTER_MODE_POWEROFF_CNF                = 8243,
    TI_NAS_MMC_WAIT_SLAVE_MODE_POWEROFF_CNF                 = 8244,

    TI_NAS_MMC_WAIT_GAS_SUSPEND_REL_CNF                     = 8245,                      /* �ȴ�GAS�Ĺ����ͷŻظ��ı�����ʱ�� */
    TI_NAS_MMC_WAIT_LMM_SUSPEND_REL_CNF                     = 8246,                      /* �ȴ�LMM�Ĺ����ͷŻظ��ı�����ʱ�� */

    TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER                        = 8247,             /* �ڽ�������,����ִ��CSFBʱ,��Ҫdisable LTE,Ŀǰdisableʱ����5MINS */

    /* MMC NETSCAN������ɨ�趨ʱ�� */
    TI_NAS_MMC_PERIODIC_NET_SCAN_TIMER                      = 8248,

    /* �����ȼ����뼼����HPLMN������ʱ�� */
    TI_NAS_MMC_HIGH_PRIO_RAT_HPLMN_TIMER                    = 8249,

    TI_NAS_MMC_WAIT_MSCC_REG_REQ                             = 8250,
    TI_NAS_MMC_WAIT_CMMCA_RESUME_IND                        = 8251,

    TI_NAS_MMC_PERIOD_DELETE_DISABLED_PLMN_WITH_RAT_TIMER   = 8252,

    /* Added by l00324781 for CDMA Iteration 10, 2015-4-7, begin */
    TI_NAS_MMC_WAIT_LMM_BG_SEARCH_HRPD_CNF                  = 8253,
    /* Added by l00324781 for CDMA Iteration 10, 2015-4-7, end */

    TI_NAS_MMC_WAIT_CSS_BAND_SCAN_CNF                       = 8254,
    TI_NAS_MMC_WAIT_CSS_STOP_BAND_SCAN_CNF                  = 8255,

    /* Added by l00324781 for CDMA Iteration 12, 2015-5-29, begin */
    TI_NAS_MMC_WAIT_MSCC_INTERSYS_HRPD_NTF                  = 8256,
    /* Added by l00324781 for CDMA Iteration 12, 2015-5-29, end */

    /* Modified by w00351686 for dts: 2015072306197 2015-8-25 begin */
    TI_NAS_MMC_WAIT_USIM_SET_FILE_CNF                       = 8257,
    /* Modified by w00351686 for dts: 2015072306197 2015-8-25 end */

    /* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-8-26, begin */
    TI_NAS_MMC_PLMN_SEARCH_PHASE_ONE_TOTAL_TIMER            = 8258,             /* ��һ�׶�������ʱ�䶨ʱ�� */
    /* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-8-26, end */

    /* Added by z00359541 for CS REG FAIL FORB LA, 2015-9-23, begin */
    TI_NAS_MMC_CUSTOMIZED_FORB_LA_TIMER                     = 8259,    
    /* Added by z00359541 for CS REG FAIL FORB LA, 2015-9-23, end */
    
    /*********************************UTRANCTRLģ����ض�ʱ��,ID��9000��ʼ,�м�Ԥ����MMC�����µĶ�ʱ��*********************************/
    /* UTRANCTRLģ��PLMN SELECTION״̬����ض�ʱ�� */
    TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF                    = 9000,             /* �ȴ�TDRRC����ظ���ʱ��,ʱ�� */
    TI_NAS_UTRANCTRL_WAIT_TD_PLMN_SEARCH_CNF                = 9001,             /* �ȴ�TDRRC�����ظ���ʱ��,ʱ�� */
    TI_NAS_UTRANCTRL_WAIT_TD_PLMN_STOP_CNF                  = 9002,             /* �ȴ�TDRRCֹͣ�����ظ���ʱ��,ʱ�� */
    TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF                   = 9003,             /* �ȴ�WAS����ظ���ʱ��,ʱ�� */
    TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_SEARCH_CNF               = 9004,             /* �ȴ�WAS�����ظ���ʱ��,ʱ�� */
    TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_STOP_CNF                 = 9005,             /* �ȴ�WASֹͣ�����ظ���ʱ��,ʱ�� */

    /* UTRANCTRLģ��MODE CHANGE״̬����ض�ʱ�� */
    TI_NAS_UTRANCTRL_WAIT_SLAVEMODE_UTRAN_MODE_CNF          = 9006,             /* �ȴ���ģģʽ����ظ���ʱ��,ʱ�� */
    TI_NAS_UTRANCTRL_WAIT_MASTERMODE_UTRAN_MODE_CNF         = 9007,             /* �ȴ�WASģʽ����ظ���ʱ��,ʱ�� */

    /* UTRANCTRL: POWER OFF״̬��ض�ʱ�� */
    TI_NAS_UTRANCTRL_WAIT_WAS_POWER_OFF_CNF                 = 9008,
    TI_NAS_UTRANCTRL_WAIT_TD_POWER_OFF_CNF                  = 9009,

    /* UTRANCTRL: SWITCH ON״̬��ض�ʱ�� */
    TI_NAS_UTRANCTRL_WAIT_WAS_START_CNF                     = 9010,
    TI_NAS_UTRANCTRL_WAIT_TD_START_CNF                      = 9011,

    /* UTRANCTRL: syscfg״̬��ض�ʱ�� */
    TI_NAS_UTRANCTRL_WAIT_WAS_SYSCFG_CNF                    = 9012,
    TI_NAS_UTRANCTRL_WAIT_TD_SYSCFG_CNF                     = 9013,
    /******************************************************************************************************************************/

    /* Deleted by w00351686 for dts: 2015072306197 2015-8-25 begin */

    /* Deleted by w00351686 for dts: 2015072306197 2015-8-25 end */
    TI_NAS_MMC_TIMER_BUTT
};
typedef VOS_UINT16  NAS_MMC_TIMER_ID_ENUM_UINT16;

/*****************************************************************************
 ö����    : NAS_MMC_TIMER_STATUS_ENUM
 �ṹ˵��  : MMC��ʱ��״̬,ֹͣ������
  1.��    ��   : 2011��5��28��
    ��    ��   : zhoujun 40661
    �޸�����   : �½�
*****************************************************************************/
enum NAS_MMC_TIMER_STATUS_ENUM
{
    NAS_MMC_TIMER_STATUS_STOP,              /* ��ʱ��ֹͣ״̬ */
    NAS_MMC_TIMER_STATUS_RUNING,            /* ��ʱ������״̬ */
    NAS_MMC_TIMER_STATUS_BUTT
};
typedef VOS_UINT8 NAS_MMC_TIMER_STATUS_ENUM_U8;

/*****************************************************************************
  3 �ṹ����
*****************************************************************************/

/*****************************************************************************
 �ṹ��    : NAS_MMC_TIMER_CXT_STRU
 �ṹ˵��  : MMC��ʱ������������
 1.��    ��   : 2011��5��28��
   ��    ��   : zhoujun 40661
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    HTIMER                              hTimer;                                 /* ��ʱ��������ָ�� */
    NAS_MMC_TIMER_ID_ENUM_UINT16        enTimerId;                              /* ��ʱ����ID */
    NAS_MMC_TIMER_STATUS_ENUM_U8        enTimerStatus;                          /* ��ʱ��������״̬,������ֹͣ */
    VOS_UINT8                           ucReserve;
} NAS_MMC_TIMER_CTX_STRU;

/*****************************************************************************
  4 ��������
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : NAS_MMC_InitAllTimers
 ��������  : ��ʼ�����ж�ʱ����Ӧ��MMC��ʼ����Resetʱ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��5��30��
    ��    ��   : zhoujun 40661
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  NAS_MMC_InitAllTimers(
    NAS_MMC_TIMER_CTX_STRU              *pstMmcTimerCtx
);


/*****************************************************************************
 �� �� ��  : NAS_MMC_StartTimer
 ��������  : ����ָ����MMC��ʱ��
 �������  : enTimerId - ��Ҫ�����Ķ�ʱ��ID
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��5��30��
    ��    ��   : zhoujun 40661
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32  NAS_MMC_StartTimer(
    NAS_MMC_TIMER_ID_ENUM_UINT16        enTimerId,
    VOS_UINT32                          ulLen
);

/*****************************************************************************
 �� �� ��  : NAS_MMC_StopTimer
 ��������  : ָֹͣ����MMC��ʱ��
 �������  : enTimerId - ��Ҫֹͣ�Ķ�ʱ��ID
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��5��30��
    ��    ��   : zhoujun 40661
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  NAS_MMC_StopTimer(
    NAS_MMC_TIMER_ID_ENUM_UINT16        enTimerId
);


/*****************************************************************************
 �� �� ��  : NAS_MMC_StopAllTimer
 ��������  : ֹͣMMC�����ж�ʱ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��5��30��
    ��    ��   : zhoujun 40661
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  NAS_MMC_StopAllTimer( VOS_VOID );

NAS_MMC_TIMER_STATUS_ENUM_U8  NAS_MMC_GetTimerStatus(
    NAS_MMC_TIMER_ID_ENUM_UINT16        enTimerId
);

VOS_TIMER_PRECISION_ENUM_UINT32 NAS_MMC_GetTimerPrecision(
    NAS_MMC_TIMER_ID_ENUM_UINT16        enTimerId
);

VOS_VOID  NAS_MMC_SetTimerStopStatus(
    NAS_MMC_TIMER_ID_ENUM_UINT16        enTimerId
);

VOS_UINT32  NAS_MMC_GetTimerRemainLen(
    NAS_MMC_TIMER_ID_ENUM_UINT16        enTimerId
);


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

#endif /* NAS_MMC_TIMER_MGMT_PROC_H */

