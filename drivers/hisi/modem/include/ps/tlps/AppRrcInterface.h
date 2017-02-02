

#ifndef __APPRRCINTERFACE_H__
#define __APPRRCINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include  "vos.h"
#include  "OmCommon.h"
#include  "PsTypeDef.h"
#include  "LPsFsmState.h"
#include  "LPsTimerState.h"
#include  "AppMmInterface.h"
#include  "AppRrcLteCommonInterface.h"
#include "LRrcGuRrcCommInterface.h"
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 macro
*****************************************************************************/
#define RRC_APP_CELL_MAX_COUNT           (32)
#define RRC_APP_MAX_NUM_OF_MCC           (3)

/* gaojishan */
/*typedef DT_CMD_ENUM_UINT8 APP_CMD_ENUM_UINT8;*/
/*typedef DT_RESULT_ENUM_UINT32 APP_RESULT_ENUM_UINT32;*/

/* RRC����������뵽MAC�յ�rar */
#define PS_OM_EST_PTL_SND_MACRA_TO_RCV_RAR_TIME      (11)           /* 11ms T4-T1 */
/* ��mac�յ�rar��������Ϣ3ʱ�� */
#define PS_OM_EST_PTL_RCV_RAR_TO_SND_MSG3_TIME       (3)            /* 2.5ms T5-T4*/
/* ������Ϣ3���յ�setup��Ϣ */
#define PS_OM_EST_PTL_SND_MSG3_TO_RCV_SETUP_TIME     (73)           /* 28.5ms+2*Ts1c  T6-T5*/
/* ����setup��ϢЭ��ʱ�� */
#define PS_OM_EST_PTL_SETUP_TO_CMPL_TIME             (3)             /* 3ms T7-T6*/
/* ����������뵽����setup cmplЭ��ʱ�� */
#define PS_OM_EST_PTL_RRC_SND_MACRA_TO_CMPL_TIME     (92)            /* 47.5ms+2*Ts1c--(50.5~92.5ms) T7-T1*/
/* �����û���ʱ��Э��ֵ */
#define PS_OM_EST_PTL_USER_PLANE_TIME                (106)            /* 61ms+2*Ts1c+Ts1u--66~106ms T13-T1*/

/* С������Э��ʱ�� */
#define PS_OM_REEST_PTL_SEARCH_CELL_TIME             (100)            /* <100ms */
/* ϵͳ��Ϣ����Э��ʱ�� */
#define PS_OM_REEST_PTL_RCV_SI_TIME                  (1280)           /* <1280ms */
/* ��⵽��·ʧ�ܵ�����С���Ϸ����������Э��ʱ�� */
#define PS_OM_REEST_PTL_RCV_REEST_IND_TO_MACRA       (1500)           /* <1500ms */

/*  ������л���ʼ������Э��ʱ�� */
#define PS_OM_HO_PTL_HO_REQ_TO_CNF                   (1)              /* <1ms T6-T5*/

/* ������������յ�Cnf��Э��ʱ�� */
#define PS_OM_HO_PTL_RRC_MACRA_REQ_TO_MACRA_CNF      (11)             /* 2.5 + 1+ 7.5ms T8-T7*/

/* �����л������Ϣ���յ�ȷ����ϢЭ��ʱ�� */
#define PS_OM_HO_PTL_SND_CMPL_TO_CMPL_CNF            (13)             /* 13ms T10-T9*/

/* �յ��л�������Ϣ�������������Э��ʱ�� */
#define PS_OM_HO_PTL_RCV_RBCFG_TO_MACRA_REQ          (50)             /* 50ms T7-T4*/

/* �յ��л���������Ϣ���ظ������û���ʱ��Э��ʱ�� */
#define PS_OM_HO_PTL_USER_PLANE_TIME                 (100)            /* 100ms T11-T4*/

/* add for AT&T LRRC DAM begin */
/* �����б��б���������Ŀ�� */
#define RRC_APP_MAX_LIMITED_ITEM_COUNT         (32)
/* add for AT&T LRRC DAM end */
#define LRRC_LCSEL_INTRA_CELL_REPORT_NUM 4
#define LRRC_LCSEL_INTER_CELL_REPORT_NUM 4
#define LRRC_LCSEL_UTRAN_CELL_REPORT_NUM 4
#define LRRC_LCSEL_INTER_FREQ_REPORT_NUM 9

#define LRRC_SCELL_MAX_NUM 3
#define LRRC_INTRA_CELL_MAX_NUM 16
#define LRRC_INTER_CELL_MAX_NUM 16
#define LRRC_UTRAN_CELL_MAX_NUM 16
#define LRRC_GERAN_CELL_MAX_NUM 16

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/
/*****************************************************************************
 ö����    : APP_RRC_MSG_ID_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : RRC <-> APP �ӿ���ϢID
*****************************************************************************/
enum APP_RRC_MSG_ID_ENUM
{
    /* RRC����APP��ԭ�� */
    ID_APP_RRC_TRANSPARENT_CMD_REQ      = (PS_MSG_ID_APP_TO_RRC_BASE + 0x00),   /* _H2ASN_MsgChoice APP_RRC_TRANSPARENT_CMD_REQ_STRU */
    ID_APP_RRC_CELL_MEAS_RPT_REQ        = (PS_MSG_ID_APP_TO_RRC_BASE + 0x01),   /* _H2ASN_MsgChoice APP_RRC_CELL_MEAS_RPT_REQ_STRU */
    ID_APP_RRC_TIME_DELAY_RPT_REQ       = (PS_MSG_ID_APP_TO_RRC_BASE + 0x02),   /* _H2ASN_MsgChoice APP_RRC_TIME_DELAY_RPT_REQ_STRU */
    ID_APP_RRC_INQ_CAMP_CELL_INFO_REQ   = (PS_MSG_ID_APP_TO_RRC_BASE + 0x03),   /* _H2ASN_MsgChoice APP_RRC_INQ_CAMP_CELL_INFO_REQ_STRU */
    ID_APP_RRC_LOCK_WORK_INFO_REQ       = (PS_MSG_ID_APP_TO_RRC_BASE + 0x04),   /* _H2ASN_MsgChoice APP_RRC_LOCK_WORK_INFO_REQ_STRU */
    ID_APP_RRC_CSQ_REQ                  = (PS_MSG_ID_APP_TO_RRC_BASE + 0x05),   /* _H2ASN_MsgChoice APP_RRC_CSQ_REQ_STRU */
    ID_APP_RRC_PTL_STATE_QUERY_REQ      = (PS_MSG_ID_APP_TO_RRC_BASE + 0x06),   /* _H2ASN_MsgChoice APP_RRC_PTL_STATE_QUERY_REQ_STRU */
    ID_APP_RRC_CELL_INFO_QUERY_REQ      = (PS_MSG_ID_APP_TO_RRC_BASE + 0x07),   /* _H2ASN_MsgChoice APP_RRC_CELL_INFO_QUERY_REQ_STRU */
    ID_APP_RRC_LWCLASH_REQ              = (PS_MSG_ID_APP_TO_RRC_BASE + 0x08),   /* _H2ASN_MsgChoice APP_RRC_PTL_LWCLASH_REQ_STRU */
    /* niuxiufan DT begin */
    ID_APP_RRC_SERVING_CELL_INFO_QUERY_REQ   = (PS_MSG_ID_APP_TO_RRC_BASE + 0x09),   /* _H2ASN_MsgChoice APP_RRC_CELL_INFO_QUERY_REQ_STRU */
    ID_APP_RRC_CSEL_INFO_QUERY_REQ           = (PS_MSG_ID_APP_TO_RRC_BASE + 0x0a),   /* _H2ASN_MsgChoice APP_RRC_CELL_INFO_QUERY_REQ_STRU */
    ID_APP_RRC_UE_CAP_INFO_QUERY_REQ         = (PS_MSG_ID_APP_TO_RRC_BASE + 0x0b),   /* _H2ASN_MsgChoice APP_RRC_CELL_INFO_QUERY_REQ_STRU */
    ID_APP_RRC_AC_BARRING_INFO_QUERY_REQ     = (PS_MSG_ID_APP_TO_RRC_BASE + 0x0c),   /* _H2ASN_MsgChoice APP_RRC_CELL_INFO_QUERY_REQ_STRU */
    ID_APP_RRC_DRX_INFO_QUERY_REQ            = (PS_MSG_ID_APP_TO_RRC_BASE + 0x0d),   /* _H2ASN_MsgChoice APP_RRC_CELL_INFO_QUERY_REQ_STRU */

    /* niuxiufan DT end */
    ID_APP_RRC_NMR_REQ                  = (PS_MSG_ID_APP_TO_RRC_BASE + 0x0e),   /* _H2ASN_MsgChoice APP_RRC_NMR_REQ_STRU */
    ID_APP_RRC_CELLID_REQ               = (PS_MSG_ID_APP_TO_RRC_BASE + 0x0f),   /* _H2ASN_MsgChoice APP_RRC_CELLID_REQ_STRU */

    /* gaojishan-dcom-resel-cfg */
    ID_APP_LRRC_RESEL_OFFSET_CFG_NTF         = (PS_MSG_ID_APP_TO_RRC_BASE + 0x10),   /* _H2ASN_MsgChoice APP_LRRC_RESEL_OFFSET_CFG_NTF_STRU  */
    ID_APP_LRRC_CON_TO_IDLE_NTF          = (PS_MSG_ID_APP_TO_RRC_BASE + 0x11),   /* _H2ASN_MsgChoice APP_LRRC_CON_TO_IDLE_NTF_STRU  */
    /* gaojishan-fast-dorm-cfg */
    ID_APP_LRRC_FAST_DORM_CFG_NTF          = (PS_MSG_ID_APP_TO_RRC_BASE + 0x12),   /* _H2ASN_MsgChoice APP_LRRC_FAST_DORM_CFG_NTF_STRU  */
    ID_APP_LRRC_GET_NCELL_INFO_REQ      = (PS_MSG_ID_APP_TO_RRC_BASE + 0x13),   /* _H2ASN_MsgChoice APP_LRRC_GET_NCELL_INFO_REQ_STRU  */

    /* yangfan Prob Begin */
    ID_APP_LRRC_INQ_TCFG_TXPOWER_REQ    = (PS_MSG_ID_APP_TO_RRC_BASE + 0x14),   /* _H2ASN_MsgChoice APP_RRC_INQ_TCFG_TXPOWER_REQ_STRU */
    /* yangfan Prob End */
    ID_APP_RRC_FORCE_HOANDCSEL_REQ        = (PS_MSG_ID_APP_TO_RRC_BASE + 0x15),/*_H2ASN_MsgChoice APP_RRC_FORCE_HOANDCSEL_REQ_STRU*/
    ID_APP_RRC_BARCELL_ACCESS_REQ        = (PS_MSG_ID_APP_TO_RRC_BASE + 0x16),/*_H2ASN_MsgChoice APP_RRC_BARCELL_ACCESS_REQ_STRU*/
    ID_APP_LRRC_SET_UE_REL_VERSION_REQ      = (PS_MSG_ID_APP_TO_RRC_BASE + 0x17), /* _H2ASN_MsgChoice APP_LRRC_SET_UE_REL_VERSION_REQ_STRU  */

    /* begin:add for ·���ں� */
    ID_DT_LRRC_MEAS_REPORT_REQ         = (PS_MSG_ID_APP_TO_RRC_BASE + 0x18),
    ID_DT_LRRC_SYNC_REPORT_REQ         = (PS_MSG_ID_APP_TO_RRC_BASE + 0x19),
    /* end:add for ·���ں� */

    ID_APP_LRRC_SET_TLPS_PRINT2LAYER_REQ    = (PS_MSG_ID_RRC_TO_APP_BASE + 0x18),

    /* APP����RRC��ԭ�� */
    ID_RRC_APP_TRANSPARENT_CMD_CNF      = (PS_MSG_ID_RRC_TO_APP_BASE + 0x00),   /* _H2ASN_MsgChoice RRC_APP_TRANSPARENT_CMD_CNF_STRU */
    ID_RRC_APP_TRANSPARENT_CMD_IND      = (PS_MSG_ID_RRC_TO_APP_BASE + 0x01),   /* _H2ASN_MsgChoice NULL */
    ID_RRC_APP_CELL_MEAS_RPT_CNF        = (PS_MSG_ID_RRC_TO_APP_BASE + 0x02),   /* _H2ASN_MsgChoice RRC_APP_CELL_MEAS_RPT_CNF_STRU */
    ID_RRC_APP_CELL_MEAS_RPT_IND        = (PS_MSG_ID_RRC_TO_APP_BASE + 0x03),   /* _H2ASN_MsgChoice RRC_APP_CELL_MEAS_REPORT_IND_STRU */
    ID_RRC_APP_TIME_DELAY_RPT_CNF       = (PS_MSG_ID_RRC_TO_APP_BASE + 0x04),   /* _H2ASN_MsgChoice RRC_APP_TIME_DELAY_RPT_CNF_STRU */
    ID_RRC_APP_TIME_DELAY_RPT_IND       = (PS_MSG_ID_RRC_TO_APP_BASE + 0x05),   /* _H2ASN_MsgChoice RRC_APP_TIME_DELAY_RPT_IND_STRU */
    ID_RRC_APP_INQ_CAMP_CELL_INFO_CNF   = (PS_MSG_ID_RRC_TO_APP_BASE + 0x06),   /* _H2ASN_MsgChoice RRC_APP_INQ_CAMP_CELL_INFO_CNF_STRU */
    ID_RRC_APP_INQ_CAMP_CELL_INFO_IND   = (PS_MSG_ID_RRC_TO_APP_BASE + 0x07),   /* _H2ASN_MsgChoice RRC_APP_INQ_CAMP_CELL_INFO_IND_STRU */
    ID_RRC_APP_LOCK_WORK_INFO_CNF       = (PS_MSG_ID_RRC_TO_APP_BASE + 0x08),   /* _H2ASN_MsgChoice RRC_APP_LOCK_WORK_INFO_CNF_STRU */
    ID_RRC_APP_RPT_DBG_INFO_IND         = (PS_MSG_ID_RRC_TO_APP_BASE + 0x09),   /* _H2ASN_MsgChoice RRC_APP_DEBUG_INFO_STRU */
    ID_RRC_APP_CSQ_CNF                  = (PS_MSG_ID_RRC_TO_APP_BASE + 0x0a),   /* _H2ASN_MsgChoice RRC_APP_CSQ_CNF_STRU */
    ID_RRC_APP_CSQ_IND                  = (PS_MSG_ID_RRC_TO_APP_BASE + 0x0b),   /* _H2ASN_MsgChoice RRC_APP_CSQ_IND_STRU */
    ID_RRC_APP_PTL_STATE_QUERY_CNF      = (PS_MSG_ID_RRC_TO_APP_BASE + 0x0c),     /* _H2ASN_MsgChoice RRC_APP_PTL_STATE_QUERY_CNF_STRU */
    ID_RRC_APP_PTL_STATE_CHANGE_IND     = (PS_MSG_ID_RRC_TO_APP_BASE + 0x0d),     /* _H2ASN_MsgChoice RRC_APP_PTL_STATE_CHANGE_IND_STRU */
    ID_RRC_APP_CELL_INFO_QUERY_CNF      = (PS_MSG_ID_RRC_TO_APP_BASE + 0x0e),   /* _H2ASN_MsgChoice RRC_APP_CELL_INFO_QUERY_CNF_STRU */
    ID_RRC_APP_LWCLASH_CNF              = (PS_MSG_ID_RRC_TO_APP_BASE + 0x0f),   /* _H2ASN_MsgChoice RRC_APP_PTL_LWCLASH_IND_STRU */
    ID_RRC_APP_LWCLASH_IND              = (PS_MSG_ID_RRC_TO_APP_BASE + 0x10),   /* _H2ASN_MsgChoice RRC_APP_PTL_LWCLASH_CNF_STRU */
    /*niuxiufan DT begin */
    ID_RRC_APP_SERVING_CELL_INFO_QUERY_CNF    = (PS_MSG_ID_RRC_TO_APP_BASE + 0x11),   /* _H2ASN_MsgChoice RRC_APP_CELL_INFO_QUERY_CNF_STRU */
    ID_RRC_APP_SERVING_CELL_INFO_IND    = (PS_MSG_ID_RRC_TO_APP_BASE + 0x12),   /* _H2ASN_MsgChoice RRC_APP_CELL_INFO_QUERY_CNF_STRU */
    ID_RRC_APP_CSEL_INFO_QUERY_CNF      = (PS_MSG_ID_RRC_TO_APP_BASE + 0x13),   /* _H2ASN_MsgChoice RRC_APP_CELL_INFO_QUERY_CNF_STRU */
    ID_RRC_APP_LTE_CSEL_INFO_IND        = (PS_MSG_ID_RRC_TO_APP_BASE + 0x14),   /* _H2ASN_MsgChoice RRC_APP_CELL_INFO_QUERY_CNF_STRU */

    ID_RRC_APP_UE_CAP_INFO_QUERY_CNF      = (PS_MSG_ID_RRC_TO_APP_BASE + 0x15),   /* _H2ASN_MsgChoice RRC_APP_CELL_INFO_QUERY_CNF_STRU */
    ID_RRC_APP_UE_CAP_INFO_IND            = (PS_MSG_ID_RRC_TO_APP_BASE + 0x16),   /* _H2ASN_MsgChoice RRC_APP_CELL_INFO_QUERY_CNF_STRU */
    ID_RRC_APP_AC_BARRING_INFO_QUERY_CNF  = (PS_MSG_ID_RRC_TO_APP_BASE + 0x17),   /* _H2ASN_MsgChoice RRC_APP_CELL_INFO_QUERY_CNF_STRU */
    ID_RRC_APP_AC_BARRING_INFO_IND        = (PS_MSG_ID_RRC_TO_APP_BASE + 0x18),   /* _H2ASN_MsgChoice RRC_APP_CELL_INFO_QUERY_CNF_STRU */

    ID_RRC_APP_UTRA_CSEL_INFO_IND         = (PS_MSG_ID_RRC_TO_APP_BASE + 0x19),   /* _H2ASN_MsgChoice RRC_APP_CELL_INFO_QUERY_CNF_STRU */
    ID_RRC_APP_GERAN_CSEL_INFO_IND        = (PS_MSG_ID_RRC_TO_APP_BASE + 0x1a),   /* _H2ASN_MsgChoice RRC_APP_CELL_INFO_QUERY_CNF_STRU */
    ID_RRC_APP_DRX_INFO_QUERY_CNF         = (PS_MSG_ID_RRC_TO_APP_BASE + 0x1b),   /* _H2ASN_MsgChoice RRC_APP_CELL_INFO_QUERY_CNF_STRU */
    ID_RRC_APP_DRX_INFO_IND               = (PS_MSG_ID_RRC_TO_APP_BASE + 0x1c),   /* _H2ASN_MsgChoice RRC_APP_CELL_INFO_QUERY_CNF_STRU */
    /*niuxiufan DT end */
    ID_RRC_APP_NMR_CNF                    = (PS_MSG_ID_RRC_TO_APP_BASE + 0x1d),   /* _H2ASN_MsgChoice RRC_APP_NMR_CNF_STRU */
    ID_RRC_APP_CELLID_CNF                 = (PS_MSG_ID_RRC_TO_APP_BASE + 0x1e),   /* _H2ASN_MsgChoice RRC_APP_CELLID_CNF_STRU */
    ID_RRC_APP_GET_NCELL_INFO_CNF       = (PS_MSG_ID_RRC_TO_APP_BASE + 0x1f), /*_H2ASN_MsgChoice LRRC_APP_GET_NCELL_INFO_CNF_STRU*/
	/*add for dcm logger Begin */
    ID_RRC_RPT_EVT_DBG_INFO_IND         = (PS_MSG_ID_RRC_TO_APP_BASE + 0x20),   /* _H2ASN_MsgChoice RRC_APP_DEBUG_INFO_STRU */
    ID_RRC_PTL_TIME_DBG_INFO_IND         = (PS_MSG_ID_RRC_TO_APP_BASE + 0x21),   /* _H2ASN_MsgChoice RRC_APP_DEBUG_INFO_STRU */
   	/*add for dcm logger End */

    ID_RRC_PTL_T310_DBG_INFO_IND                 = (PS_MSG_ID_RRC_TO_APP_BASE + 0x22),
    ID_RRC_PTL_T300_DBG_INFO_IND                 = (PS_MSG_ID_RRC_TO_APP_BASE + 0x23),
    ID_RRC_PTL_T302_DBG_INFO_IND                 = (PS_MSG_ID_RRC_TO_APP_BASE + 0x24),
    ID_RRC_PTL_T303_DBG_INFO_IND                 = (PS_MSG_ID_RRC_TO_APP_BASE + 0x25),
    ID_RRC_PTL_T305_DBG_INFO_IND                 = (PS_MSG_ID_RRC_TO_APP_BASE + 0x26),
    ID_RRC_PTL_T306_DBG_INFO_IND                 = (PS_MSG_ID_RRC_TO_APP_BASE + 0x27),
    ID_RRC_PTL_REEST_T311_DBG_INFO_IND           = (PS_MSG_ID_RRC_TO_APP_BASE + 0x28),
    ID_RRC_PTL_REEST_T301_DBG_INFO_IND           = (PS_MSG_ID_RRC_TO_APP_BASE + 0x29),
    ID_RRC_PTL_T304_DBG_INFO_IND                 = (PS_MSG_ID_RRC_TO_APP_BASE + 0x2a),
    ID_RRC_PTL_LOSTCOVERAGE_DBG_INFO_IND         = (PS_MSG_ID_RRC_TO_APP_BASE + 0x2b),
    ID_RRC_PTL_T320_DBG_INFO_IND                 = (PS_MSG_ID_RRC_TO_APP_BASE + 0x2c),
    ID_RRC_PTL_IDLE_NORMALHYST_DBG_INFO_IND      = (PS_MSG_ID_RRC_TO_APP_BASE + 0x2d),
    ID_RRC_PTL_RESELECTION_DBG_INFO_IND          = (PS_MSG_ID_RRC_TO_APP_BASE + 0x2e),
    ID_RRC_PTL_TBARRED_DBG_INFO_IND              = (PS_MSG_ID_RRC_TO_APP_BASE + 0x2f),
    ID_RRC_PTL_TFORBIDDEN_DBG_INFO_IND           = (PS_MSG_ID_RRC_TO_APP_BASE + 0x30),
    ID_RRC_PTL_GERAN_TBARRED_DBG_INFO_IND        = (PS_MSG_ID_RRC_TO_APP_BASE + 0x31),
    ID_RRC_PTL_GERAN_TFORBIDDEN_DBG_INFO_IND     = (PS_MSG_ID_RRC_TO_APP_BASE + 0x32),
    ID_RRC_PTL_UTRAN_TBARRED_DBG_INFO_IND        = (PS_MSG_ID_RRC_TO_APP_BASE + 0x33),
    ID_RRC_PTL_UTRAN_TFORBIDDEN_DBG_INFO_IND     = (PS_MSG_ID_RRC_TO_APP_BASE + 0x34),
    ID_RRC_PTL_G2L_RESEL_PUNISH_DBG_INFO_IND     = (PS_MSG_ID_RRC_TO_APP_BASE + 0x35),
    ID_RRC_PTL_W2L_REDIR_PUNISH_DBG_INFO_IND     = (PS_MSG_ID_RRC_TO_APP_BASE + 0x36),
    ID_RRC_PTL_MBMS_MCCH_NOTIFY_DBG_INFO_IND     = (PS_MSG_ID_RRC_TO_APP_BASE + 0x37),
    ID_RRC_PTL_CMM_MOBILITY_NORMALHYST_DBG_INFO_IND      = (PS_MSG_ID_RRC_TO_APP_BASE + 0x38),
    ID_RRC_PTL_T321_DBG_INFO_IND                 = (PS_MSG_ID_RRC_TO_APP_BASE + 0x39),
    ID_RRC_PTL_SIB_3HOUR_UPDATE_DBG_INFO_IND     = (PS_MSG_ID_RRC_TO_APP_BASE + 0x3a),
    ID_RRC_PTL_PAGING_VALID_TIMER_DBG_INFO_IND   = (PS_MSG_ID_RRC_TO_APP_BASE + 0x3b),
    ID_RRC_APP_CSEL_L_DBG_INFO_IND               = (PS_MSG_ID_RRC_TO_APP_BASE + 0x3c),
    ID_RRC_APP_CSEL_W_DBG_INFO_IND               = (PS_MSG_ID_RRC_TO_APP_BASE + 0x3d),
    ID_RRC_APP_CSEL_G_DBG_INFO_IND               = (PS_MSG_ID_RRC_TO_APP_BASE + 0x3e),
    ID_RRC_APP_SSAC_DBG_INFO_IND                 = (PS_MSG_ID_RRC_TO_APP_BASE + 0x3f),
    ID_LRRC_APP_SET_UE_REL_VERSION_CNF      = (PS_MSG_ID_RRC_TO_APP_BASE + 0x40),/* _H2ASN_MsgChoice LRRC_APP_SET_UE_REL_VERSION_CNF_STRU  */
    ID_APP_RRC_FORCE_HOANDCSEL_CNF        = (PS_MSG_ID_RRC_TO_APP_BASE + 0x41),/* _H2ASN_MsgChoice RRC_APP_FORCE_HOANDCSEL_CNF_STRU */
    ID_APP_RRC_BARCELL_ACCESS_CNF        = (PS_MSG_ID_RRC_TO_APP_BASE + 0x42),/* _H2ASN_MsgChoice RRC_APP_BARCELL_ACCESS_CNF_STRU */

    /* begin: add for feature v700r500 */
    ID_LRRC_APP_DBG_INFO_IND         = (PS_MSG_ID_RRC_TO_APP_BASE + 0x43),   /* _H2ASN_MsgChoice LRRC_APP_DBG_INFO_STRU */
    /* end: add for feature v700r500 */
    /* add for AT&T LRRC DAM begin */
    ID_RRC_PTL_DAM_CELL_BAR_TIMER_INFO_IND    = (PS_MSG_ID_RRC_TO_APP_BASE + 0x44),
    ID_RRC_APP_DAM_STATUS_DBG_INFO_IND    = (PS_MSG_ID_RRC_TO_APP_BASE + 0x45),/* _H2ASN_MsgChoice LRRC_APP_DAM_STATUS_DBG_INFO_IND_STRU  */
    ID_RRC_APP_DAM_BAR_LIST_DBG_INFO_IND    = (PS_MSG_ID_RRC_TO_APP_BASE + 0x46), /* _H2ASN_MsgChoice LRRC_APP_DAM_BAR_LIST_DBG_INFO_IND_STRU */
    /* add for AT&T LRRC DAM end */
    ID_LRRC_APP_SET_TLPS_PRINT2LAYER_CNF = (PS_MSG_ID_RRC_TO_APP_BASE + 0x47),

    /* begin:add for ·���ں� */
    ID_LRRC_DT_MEAS_REPORT_CNF   = (PS_MSG_ID_RRC_TO_APP_BASE + 0x48),
    ID_LRRC_DT_SYNC_REPORT_CNF   = (PS_MSG_ID_RRC_TO_APP_BASE + 0x49),
    ID_LRRC_DT_MEAS_INFO_IND     = (0x988),/* ���ݶ���ӿڣ�·�����Ind��ϢidΪ0x988������id_lrrc_lphy_conn_meas_ind */
    ID_LRRC_DT_SYNC_INFO_IND     = (0x904),/* ���ݶ���ӿڣ�·�����Ind��ϢidΪ0x904������id_lrrc_lphy_sync_info_ind */
    ID_LRRC_DT_OUT_OF_SYNC_INFO_IND = (0x90f),/* ���ݶ���ӿڣ�·�����Ind��ϢidΪ0x90f������id_lrrc_lphy_out_of_sync_info_ind */
    /* end:add for ·���ں� */

    ID_RRC_APP_SERVING_CELL_CA_INFO_IND          = (PS_MSG_ID_RRC_TO_DT_BASE + 0x12),
    ID_APP_RRC_MSG_ID_BUTT
};
typedef VOS_UINT32    APP_RRC_MSG_ID_ENUM_UINT32;

/*****************************************************************************
  4 Enum
*****************************************************************************/

/*****************************************************************************
 ö����    : APP_RRC_CELL_RPT_PERIOD_ENUM
 ö��˵��  :
*****************************************************************************/
enum APP_RRC_CELL_RPT_PERIOD_ENUM
{
    APP_RRC_CELL_REPORT_PERIOD_300MS = 0,
    APP_RRC_CELL_REPORT_PERIOD_600MS,
    APP_RRC_CELL_REPORT_PERIOD_900MS,
    APP_RRC_CELL_REPORT_PERIOD_1200MS,
    APP_RRC_CELL_REPORT_PERIOD_BUTT
};
typedef VOS_UINT8 APP_RRC_CELL_RPT_PERIOD_ENUM_UINT8;

/*****************************************************************************
 ö����    : RRC_FILE_NAME_ID_ENUM
 ö��˵��  : RRC�ļ���ö��
*****************************************************************************/
enum RRC_FILE_NAME_ID_ENUM
{
    RrcCmmComm_c,
    RrcCmmDebug_c,
    RrcCmmFsm_c,
    RrcCmmGlobal_c,
    RrcCmmHandover_c,
    RrcCmmL3Ie_c,
    RrcCmmL3msg_c,
    RrcCmmMeasCtrl_c,
    RrcCmmMeasEvaluate_c,
    RrcCmmNcellMeasCfg_c,
    RrcCmmPhy_c,
    RrcCmmSpeedState_c,
    RrcCmmState_c,
    RrcCmmTimer_c,
    RrcCselCellSelect_c,
    RrcCselComm_c,
    RrcCselDebug_c,
    RrcCselEvaluate_c,
    RrcCselFsm_c,
    RrcCselGlobal_c,
    RrcCselInit_c,
    RrcCselLimitCell_c,
    RrcCselMeasure_c,
    RrcCselMobility_c,
    RrcCselMsgSend_c,
    RrcCselPlmnSearch_c,
    RrcCselReselect_c,
    RrcCselSysInfo_c,
    RrcCselTimer_c,
    RrcCselPcCellResel_c,
    RrcCselpcCellSearch_c,
    RrcCselPcComm_c,
    RrcCselpcEntry_c,
    RrcCselPcFsm_c,
    RrcCselpcGlobal_c,
    RrcCselpcPlmnSearch_c,
    RrcCselPcStaChange_c,
    RrcCselpcSysInfoUpdate_c,
    RrcItf_c,
    RrcItfFsm_c,
    RrcItfL2Func_c,
    RrcItfNasSndMsg_c,
    RrcItfPhyFunc_c,
    RrcCommPrint_c,
    RrcMainAsn1_c,
    RrcMainEntry_c,
    RrcMainErmmFsm_c,
    RrcMainErrcFsm_c,
    RrcMainFsmComm_c,
    RrcMainGlobal_c,
    RrcMainPrint_c,
    RrcMainTimer_c,
    RrcOmItf_c,
    RrcRbCfgRcvConfigCnf_c,
    RrcRbEntry_c,
    RrcRbFsm_c,
    RrcRbGlobal_c,
    RrcRbHoRcvConfigCnf_c,
    RrcRbRecfgRcvConfigCnf_c,
    RrcRbReconfigMsgProc_c,
    RrcRbSndMsg_c,
    RrcRbUpdateCtx_c,
    RrcReestConnReest_c,
    RrcReestFsm_c,
    RrcReestGlobal_c,
    RrcReestProcConnReestMsg_c,
    RrcReestSndConfigMsg_c,
    RrcReestTimerHandle_c,
    RrcCcb_c,
    RrcComm_c,
    RrcCommSaveIe_c,
    RrcCommSaveSibIe_c,
    RrcRrcConnAccessCtrl_c,
    RrcRrcConnEst_c,
    RrcRrcConnRel_c,
    RrcRrcConnRelComm_c,
    RrcRrcDebug_c,
    RrcRrcErrorProc_c,
    RrcRrcFsm_c,
    RrcRrcGlobal_c,
    RrcRrcNasCmd_c,
    RrcRrcPaging_c,
    RrcRrcProcRrcConnMsg_c,
    RrcRrcPtlTimerHandle_c,
    RrcRrcSndMsg_c,
    RrcRrcUeCapEnquiry_c,
    RrcRrcUeInfoEnquiry_c,
    RrcSndMsgComm_c,
    RrcSibComm_c,
    RrcSibFsm_c,
    RrcSibGlobal_c,
    RrcSibProc_c,
    RrcSmcFsm_c,
    RrcSmcGlobal_c,
    RrcSmcKeyProc_c,
    RrcSmcMsgProc_c,
    LRrcLRrcIratCommProc_c,
    LRrcLRrcIratReselProc_c,
    LRrcLRrcIratRedirProc_c,
    LRrcLRrcIratCcoProc_c,
    LRrcLRrcIratHoProc_c,
    LRrcLRrcIratPlmnSearchProc_c,
    /* MBMS Begin */
    LRrcMbmsComm_c,
    LRrcMbmsProc_c,
    LRrcMbmsGlobal_c,
    LRrcMbmsSndMsg_c,
    /* MBMS End */

    /* bgs begin */
    LRrcLCselBgFsm_c,
    LRrcLCselBgScan_c,
    LRrcLCselBgGlobal_c,
    /* bgs end */
    LRrcLRrcLppCmd_c,
    RRC_FILE_NAME_ID_BUTT
};

typedef VOS_UINT32 RRC_FILE_NAME_ID_ENUM_UINT32;
/*****************************************************************************
 ö����    : APP_LATENCY_TYPE_ENUM
 ö��˵��  :
*****************************************************************************/
enum APP_LATENCY_TYPE_ENUM
{
    APP_LATENCY_EST =0,               /*���ӽ���ʱ��*/
    APP_LATENCY_HO,                   /*�л�ʱ��*/
    APP_LATENCY_REEST,                /*�ؽ�ʱ��*/
    APP_LATENCY_BUTT
};
typedef VOS_UINT8 APP_LATENCY_TYPE_ENUM_UINT8;

/*****************************************************************************
 ö����    : APP_RRC_LOCK_WORK_INFO_TYPE_ENUM
 ö��˵��  : ����������
*****************************************************************************/
enum APP_RRC_LOCK_WORK_INFO_TYPE_ENUM
{
    RRC_APP_LOCK_FREQPOINT,              /* Ƶ������ */
    RRC_APP_LOCK_FREQANDCELL,            /* Ƶ���С���������� */
    RRC_APP_LOCK_FREQBAND,               /* Ƶ������ */
    RRC_APP_LOCK_BUTT
};
typedef VOS_UINT8 APP_RRC_LOCK_WORK_INFO_TYPE_ENUM_UINT8;
/*****************************************************************************
 ö����    : APP_DELAY_TYPE_ENUM
 ö��˵��  :
*****************************************************************************/
enum APP_DELAY_TYPE_ENUM
{
    APP_DELAY_CONTROL_PLANE =0,     /*������ʱ��*/
    APP_DELAY_USER_PLANE,           /*�û���ʱ��*/
    APP_DELAY_HO,                   /*�л�ʱ��*/
    APP_DELAY_BUTT
};
typedef VOS_UINT8 APP_DELAY_TYPE_ENUM_UINT8;
/*****************************************************************************
 ö����    : APP_CAMPED_FLAG_ENUM
 ö��˵��  :
*****************************************************************************/
enum APP_CAMPED_FLAG_ENUM
{
    APP_CAMPED,                 /* ��פ�� */
    APP_NOT_CAMPED,             /* δפ�� */
    APP_CAMPED_BUTT
};
typedef VOS_UINT8 APP_CAMPED_FLAG_ENUM_UINT8;
/*****************************************************************************
 ö����    : APP_DELAY_TYPE_ENUM
 ö��˵��  :
*****************************************************************************/
enum APP_STATE_FLAG_ENUM
{
    APP_STATE_NOT_IN_RANGE,                 /* ���ڳ�ͻ��Χ��,״̬2 */
    APP_STATE_IN_RANGE,                     /* �ڳ�ͻ��Χ��,״̬1*/
    APP_STATE_BUTT
};
typedef VOS_UINT8 APP_STATE_FLAG_ENUM_UINT8;

/*****************************************************************************
   5 STRUCT
*****************************************************************************/
/*****************************************************************************
 �ṹ��    : APP_RRC_CELL_MEAS_RPT_REQ_STRU
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgID;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    APP_CMD_ENUM_UINT8                  enCommand;
    APP_RRC_CELL_RPT_PERIOD_ENUM_UINT8  enPeriod;
    VOS_UINT8                           aucReserved[2];
}APP_RRC_CELL_MEAS_RPT_REQ_STRU;

/*****************************************************************************
 �ṹ��    : RRC_APP_CELL_MEAS_RPT_CNF_STRU
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    APP_RESULT_ENUM_UINT32              enResult;
}RRC_APP_CELL_MEAS_RPT_CNF_STRU;

/*****************************************************************************
 �ṹ��    :RRC_APP_CELL_MEAS_RSLT_STRU
 �ṹ˵��  :С���������
*****************************************************************************/
typedef struct
{
    VOS_UINT16 usCellId;
    VOS_INT16  sRSRP;
    VOS_INT16  sRSRQ;
    VOS_INT16  sRSSI;
}RRC_APP_CELL_MEAS_RSLT_STRU;

/*****************************************************************************
 �ṹ��    :RRC_APP_CELL_MEAS_REPORT_IND_STRU
 �ṹ˵��  :RRCͨ����ԭ�������ϱ�С�����������������
            ��ǰ����ͬƵ����ʱ��RRC�ϱ�С���Ĳ�������������ڣ����ϱ����ݣ�
            �����ǰ������ͬƵ���������������֮������ͬƵ������RRC����֮ǰ��OM���ý����ϱ�С�����������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    VOS_UINT8                           ucCellCnt;                              /* С������ */
    VOS_UINT8                           aucReserved[3];
    RRC_APP_CELL_MEAS_RSLT_STRU         astCellMeasInd[RRC_APP_CELL_MAX_COUNT];
}RRC_APP_CELL_MEAS_REPORT_IND_STRU;

/*****************************************************************************
 �ṹ��    : APP_RRC_TIME_DELAY_RPT_REQ_STRU
 �ṹ˵��  : Ҫ���ϱ�������ʱ�ӡ�������ʱ�ӣ�����RB�����Ŀ���ʱ�䣬���������ӽ�������RB1�����ɹ���ʱ�䡣
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    APP_CMD_ENUM_UINT8                  enCommand;
    APP_DELAY_TYPE_ENUM_UINT8           enDelayType;
    VOS_UINT8                           aucReserved[2];
}APP_RRC_TIME_DELAY_RPT_REQ_STRU;

/*****************************************************************************
 �ṹ��    :RRC_APP_TIME_DELAY_RPT_CNF_STRU
 �ṹ˵��  :��ԭ��APP_RRC_TIME_DELAY_RPT_REQ_STRU�Ļظ�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    APP_DELAY_TYPE_ENUM_UINT8           enDelayType;
    VOS_UINT8                           aucReserved[3];
    APP_RESULT_ENUM_UINT32              enResult;
}RRC_APP_TIME_DELAY_RPT_CNF_STRU;

/*****************************************************************************
 �ṹ��    :APP_RRC_INQ_CAMP_CELL_INFO_REQ_STRU
 �ṹ˵��  :��ȡ��ǰפ��С����ID��Ƶ�����Ϣ�Ĳ�ѯ���󣬻���ֹͣ�ϱ�פ��С����Ϣ������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    APP_CMD_ENUM_UINT8                  enCommand;
    VOS_UINT8                           aucReserved[3];
}APP_RRC_INQ_CAMP_CELL_INFO_REQ_STRU;

/*****************************************************************************
 �ṹ��    :RRC_APP_INQ_CAMP_CELL_INFO_CNF_STRU
 �ṹ˵��  :��ԭ��APP_RRC_INQ_CAMP_CELL_INFO_REQ_STRU�Ļظ�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    APP_RESULT_ENUM_UINT32              enResult;
}RRC_APP_INQ_CAMP_CELL_INFO_CNF_STRU;

/*****************************************************************************
 �ṹ��    :RRC_APP_INQ_CAMP_CELL_INFO_IND_STRU
 �ṹ˵��  :�ϱ���ǰפ��С����Ϣ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    PS_BOOL_ENUM_UINT8                  enValueFlag;
    VOS_UINT8                           aucReserved[3];
    VOS_UINT16                          usCellId;
    VOS_UINT16                          usFreqInfo;
}RRC_APP_INQ_CAMP_CELL_INFO_IND_STRU;

/*****************************************************************************
 �ṹ��    :APP_RRC_FREQ_BAND_STRU
 �ṹ˵��  :Ƶ����Χ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usLowBand;                              /* Ƶ������ */
    VOS_UINT16                          usHighBand;                             /* Ƶ������ */
}APP_RRC_FREQ_BAND_STRU;

/*****************************************************************************
 �ṹ��    :APP_RRC_CELL_INFO_STRU
 �ṹ˵��  :С����Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usCellId;                               /* С��ID */
    VOS_UINT16                          usFreqPoint;                            /* Ƶ����Ϣ */
}APP_RRC_CELL_INFO_STRU;

/*****************************************************************************
 �ṹ��    :APP_RRC_LOCK_INFO_STRU
 �ṹ˵��  :�����������Ϣ
*****************************************************************************/
typedef struct
{
    APP_RRC_LOCK_WORK_INFO_TYPE_ENUM_UINT8  enLockType;                         /* �������� */
    VOS_UINT8                               ucBandInd;
    union
    {
        VOS_UINT16                      usFreqPoint;                            /* ������Ƶ�� */
        APP_RRC_CELL_INFO_STRU          stFreqAndCell;                          /* ������С��ID��Ƶ�� */
        APP_RRC_FREQ_BAND_STRU          stFreqBand;                             /* ����Ƶ���������� */
    }u;
}APP_RRC_LOCK_INFO_STRU;

/*****************************************************************************
 �ṹ��    :APP_RRC_LOCK_WORK_INFO_REQ_STRU
 �ṹ˵��  :·���·�����������Ľṹ��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32 ulMsgID;                                     /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    APP_CMD_ENUM_UINT8                  enCommand;                              /* �������ǽ��� */
    VOS_UINT8                           aucReserved[3];                         /* ����, �˴���2, ����Ϊ��һ���ǵ��ֽ� */
    APP_RRC_LOCK_INFO_STRU              stLockInfo;
}APP_RRC_LOCK_WORK_INFO_REQ_STRU;

/*****************************************************************************
 �ṹ��    :RRC_APP_LOCK_WORK_INFO_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :��ԭ��APP_RRC_LOCK_WORK_INFO_REQ���лظ�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    APP_RESULT_ENUM_UINT32              enResult;
}RRC_APP_LOCK_WORK_INFO_CNF_STRU;


/*****************************************************************************
 �ṹ��    : APP_RRC_TRANSPARENT_CMD_REQ
 Э����  :
 ASN.1���� :
 �ṹ˵��  :͸������ͷ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32 ulMsgId;                                     /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    VOS_UINT16 usTransCmdNum;
    VOS_UINT16 usParaSize;
    VOS_UINT8  aucPara[4];
}APP_RRC_TRANSPARENT_CMD_REQ_STRU;


/*****************************************************************************
 �ṹ��    : RRC_APP_TRANSPARENT_CMD_CNF_STRU
 �ṹ˵��  : PS->OMT��͸������ִ�н�����ݽṹ(
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32          ulMsgId;                            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    VOS_UINT8           aucTransCmdCnf[4];  /*͸���������������ɱ�*/
}RRC_APP_TRANSPARENT_CMD_CNF_STRU;

/*****************************************************************************
 �ṹ��    : RRC_CSELDEBUG_PRINT_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usArfcn;
    VOS_UINT16                          usFreq;
    VOS_UINT16                          usCellId;
    VOS_INT16                           sGeranCellRxlev;
    VOS_UINT16                          usNcc;
    VOS_UINT16                          usBcc;
    VOS_UINT8                           ucBandInd;
    VOS_UINT8                           aucReserved[3];
    VOS_UINT32                          ulTick;
}RRC_CSELDEBUG_PRINT_INFO_STRU;

/*****************************************************************************
 �ṹ��    : RRC_APP_CSELDEBUG_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    RRC_CSELDEBUG_PRINT_INFO_STRU           stRrcCselDbgInfo;
}RRC_APP_CSELDEBUG_INFO_STRU;

typedef struct
{
    VOS_UINT8    ucRrcProtclState;
    VOS_UINT8    ucPlmntype;
    VOS_UINT8    ucMmTelVoicePresent;
    VOS_UINT8    ucMmTelVideoPresent;
    VOS_UINT16   usAccClassMask;
    VOS_UINT8    ucAcBarringForVoiceSpecialAc;
    VOS_UINT8    ucAcBarringForVideoSpecialAc;
    VOS_UINT8    ucBarringFactorForMMTELVoice;
    VOS_UINT8    ucBarringTimeForMMTELVoice;
    VOS_UINT8    ucBarringFactorForMMTELVideo;
    VOS_UINT8    ucBarringTimeForMMTELVideo;
}RRC_SSACDEBUG_INFO_STRU;

/*****************************************************************************
 �ṹ��    : RRC_APP_CSELDEBUG_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    RRC_SSACDEBUG_INFO_STRU             stRrcSsacDbgInfo;
}RRC_APP_SSACDEBUG_INFO_STRU;

/*****************************************************************************
 �ṹ��    : RRC_DEBUG_PRINT_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    RRC_FILE_NAME_ID_ENUM_UINT32        enFileName;
    VOS_UINT32                          ulLineNo;
    RRC_MS_ID_ENUM_UINT16               enMainState;
    RRC_SS_ID_ENUM_UINT16               enSubState;
    RRC_PTL_TI_ENUM_UINT16              enPtlTi;
    RRC_STATE_TI_ENUM_UINT16            enStaTi;
    VOS_UINT32                          ulTick;
    VOS_INT32                           lPara1;
    VOS_INT32                           lPara2;
    VOS_INT32                           lPara3;
    VOS_INT32                           lPara4;
}RRC_DEBUG_PRINT_INFO_STRU;

/*****************************************************************************
 �ṹ��    : RRC_APP_DEBUG_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    RRC_DEBUG_PRINT_INFO_STRU           stRrcDbgInfo;
}RRC_APP_DEBUG_INFO_STRU;

/*****************************************************************************
 �ṹ��    :PS_APP_HO_LATENCY_DETAIL_STRU
 �ṹ˵��  :�л�ʱ�ӹؼ�����ϱ�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          T4_ulRrcRcvHoRecfg;
    VOS_UINT32                          ulRrcRcvNasRabmRsp;
    VOS_UINT32                          ulRrcRcvCmmHoCnf;
    VOS_UINT32                          ulRrcRcvStopPdcpCnf;
    VOS_UINT32                          T5_ulRrcSndDspHoReq;
    VOS_UINT32                          T6_ulRrcRcvDspHoCnf;
    VOS_UINT32                          T7_ulRrcSndMacRaReq;
    VOS_UINT32                          T12_ulMacSndPhyAccessReq;
    VOS_UINT32                          T13_ulMacRcvRar;
    VOS_UINT32                          T8_ulRrcRcvMacRaCnf;
    VOS_UINT32                          ulRrcSndSmcSecuCfg;
    VOS_UINT32                          T9_ulRrcSndRecfgCmp;
    VOS_UINT32                          T10_ulRrcRcvAmDataCnf;
    VOS_UINT32                          ulRrcRcvCqiSrsCnf;
    VOS_UINT32                          ulRrcRcvPdcpContineCnf;
    VOS_UINT32                          T11_ulRrcRcvRabmStatusRsp;
}PS_APP_HO_LATENCY_DETAIL_STRU;
/*****************************************************************************
 �ṹ��    :PS_APP_HO_COMP_DETAIL_STRU
 �ṹ˵��  :�л�ʱ����Э��Ա�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulRealTestT6T5;
    VOS_UINT32                          ulPtlT6T5;          /* 1ms */
    VOS_UINT32                          ulRealTestT8T7;
    VOS_UINT32                          ulPtlT8T7;          /* 2.5 + 1+ 7.5ms */
    VOS_UINT32                          ulRealTestT10T9;
    VOS_UINT32                          ulPtlT10T9;         /* 13ms */
    VOS_UINT32                          ulRealTestT7T4;
    VOS_UINT32                          ulPtlT7T4;          /* 50ms */
    VOS_UINT32                          ulRealTestT11T4;
    VOS_UINT32                          ulPtlT11T4;         /* 100ms */
}PS_APP_HO_COMP_DETAIL_STRU;
/*****************************************************************************
 �ṹ��    :PS_APP_EST_LATENCY_DETAIL_STRU
 �ṹ˵��  :����ʱ�ӹؼ�����ϱ�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          T1_ulRrcSndMacRaReq;
    VOS_UINT32                          T2_ulMacSndPhyAccessReq;
    VOS_UINT32                          T4_ulMacRcvRar;
    VOS_UINT32                          ulRrcRcvMacRaCnf;
    VOS_UINT32                          T5_ulMacSndMsg3;
    VOS_UINT32                          T6_ulRrcRcvSetUp;
    VOS_UINT32                          T7_ulRrcSndEstCmp;
    VOS_UINT32                          ulRrcRcvSecCmd;
    VOS_UINT32                          ulRrcSndSecCmdCmp;
    VOS_UINT32                          ulRrcRcvCapEnq;
    VOS_UINT32                          ulRrcSndCapInfo;
    VOS_UINT32                          ulRrcRcvRecfg;
    VOS_UINT32                          T13_ulRrcSndRecfgCmp;
}PS_APP_EST_LATENCY_DETAIL_STRU;
/*****************************************************************************
 �ṹ��    :PS_APP_EST_COMP_STRU
 �ṹ˵��  :����ʱ����Э��Ա�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulRealTestT4T1;
    VOS_UINT32                          ulPtlT4T1;              /* 5s + 6ms */
    VOS_UINT32                          ulRealTestT5T4;
    VOS_UINT32                          ulPtlT5T4;              /* 2.5ms */
    VOS_UINT32                          ulTestRealT6T5;
    VOS_UINT32                          ulPtlT6T5;              /* 28.5ms+2*Ts1c */
    VOS_UINT32                          ulRealTestT7T6;
    VOS_UINT32                          ulPtlT7T6;              /* 3ms */
    VOS_UINT32                          ulReaTestlT7T1;
    VOS_UINT32                          ulPtlT7T1;              /* 47.5ms+2*Ts1c */
    VOS_UINT32                          ulReaTestlT13T1;
    VOS_UINT32                          ulPtlT13T1;             /* 61ms+2*Ts1c+Ts1u */
}PS_APP_EST_COMP_DETAIL_STRU;
/*****************************************************************************
 �ṹ��    :PS_APP_REEST_LATENCY_DETAIL_STRU
 �ṹ˵��  :�ؽ�ʱ�ӹؼ�����ϱ�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          T2_ulRrcRcvReestInd;
    VOS_UINT32                          T3_ulRrcSndCellSearchReq;
    VOS_UINT32                          T4_ulRrcRcvCellSearchInd;
    VOS_UINT32                          T5_ulRrcRcvSi;
    VOS_UINT32                          T6_ulRrcSndCampReq;
    VOS_UINT32                          T7_ulRrcRcvCampCnf;
    VOS_UINT32                          T10_ulRrcSndMacRaReq;
    VOS_UINT32                          ulMacSndPhyAccessReq;
    VOS_UINT32                          ulMacRcvRar;
    VOS_UINT32                          ulRrcRcvMacRaCnf;
    VOS_UINT32                          ulMacSndMsg3;
    VOS_UINT32                          ulRrcRcvReest;
    VOS_UINT32                          ulRrcSndReestCmpl;
}PS_APP_REEST_LATENCY_DETAIL_STRU;

/*****************************************************************************
 �ṹ��    :PS_APP_REEST_COMP_DETAIL_STRU
 �ṹ˵��  :�ؽ�ʱ����Э��Ա�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulRealTestT4T3;
    VOS_UINT32                          ulPtlT4T3;              /* 100ms */
    VOS_UINT32                          ulRealTestT5T4;
    VOS_UINT32                          ulPtlT5T4;              /* 1280ms */
    VOS_UINT32                          ulRealTestT10T2;
    VOS_UINT32                          ulPtlT10T2;             /* 1500ms */

}PS_APP_REEST_COMP_DETAIL_STRU;
/*****************************************************************************
 �ṹ��    :RRC_APP_TIME_LATENCY_RPT_IND_STRU
 �ṹ˵��  :ʱ��ʱ����ϱ�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                  T7T4_ulHoCPlaneRealLatency;
    VOS_UINT32                                  ulHoCPlanePtlLatency;
    VOS_UINT32                                  T11T4_ulHoUPlaneRealLatency;
    VOS_UINT32                                  ulHoUPlanePtlLatency;
    PS_APP_HO_LATENCY_DETAIL_STRU               stHoLatencyDetail;
    PS_APP_HO_COMP_DETAIL_STRU                  stHoCompDetail;
}PS_APP_HO_LATENCY_STRU;

/*****************************************************************************
 �ṹ��    :PS_APP_REEST_LATENCY_STRU
 �ṹ˵��  :ʱ��ʱ����ϱ�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                  T10T2_ulReestRealLatency;
    VOS_UINT32                                  ulReestPtlLatency;
    PS_APP_REEST_LATENCY_DETAIL_STRU            stReestLatencyDetail;
    PS_APP_REEST_COMP_DETAIL_STRU               stReestCompDetail;
}PS_APP_REEST_LATENCY_STRU;

/*****************************************************************************
 �ṹ��    :PS_APP_EST_LATENCY_STRU
 �ṹ˵��  :ʱ��ʱ����ϱ�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                  T13T1_ulEstUPlaneRealLatency;
    VOS_UINT32                                  ulEstUPlanePtlLatency;
    VOS_UINT32                                  T7T1_ulEstCPlaneRealLatency;
    VOS_UINT32                                  ulEstCPlanePtlLatency;
    PS_APP_EST_LATENCY_DETAIL_STRU              stEstLatencyDetail;
    PS_APP_EST_COMP_DETAIL_STRU                 stEstCompDetail;
}PS_APP_EST_LATENCY_STRU;

/*****************************************************************************
 �ṹ��    :RRC_APP_TIME_LATENCY_RPT_IND_STRU
 �ṹ˵��  :ʱ��ʱ����ϱ�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;

    APP_LATENCY_TYPE_ENUM_UINT8         enLatencyType;
    VOS_UINT8                           aucReserved[3];
union
    {
        PS_APP_HO_LATENCY_STRU             stHoElapse;
        PS_APP_REEST_LATENCY_STRU          stReestElapse;
        PS_APP_EST_LATENCY_STRU            stEstElapse;
    }u;
} RRC_APP_TIME_DELAY_RPT_IND_STRU;

/*****************************************************************************
 �ṹ��    :APP_RRC_CSQ_REQ_STRU
 �ṹ˵��  :CSQ��ѯ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    VOS_UINT16                          usSwt;              /* 0: ֹͣ�����ϱ� 1: ��ѯRSSI��������IND�ϱ�  2: ���������ϱ�RSSI */
    VOS_UINT16                          usPeriod;
    VOS_UINT16                          usNdb;              /* ��Χ 0-5 dbm*/
    VOS_UINT16                          usMs;               /* ��Χ 1-20 s*/
}APP_RRC_CSQ_REQ_STRU;

/*****************************************************************************
 �ṹ��    :RRC_APP_CSQ_CNF_STRU
 �ṹ˵��  :CSQ��ѯ������Ӧ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usRI;                /*RIֵ*/
    VOS_UINT16                          ausCQI[2];           /* CQI�������� */
    VOS_UINT8                           aucRes[2];

}APP_RRC_CQI_INFO_STRU;

/*****************************************************************************
 �ṹ��    :RRC_APP_CSQ_CNF_STRU
 �ṹ˵��  :CSQ��ѯ������Ӧ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    APP_RESULT_ENUM_UINT32              enResult;
    VOS_INT16                           sRsrp;              /* RSRP����ֵ��Χ��(-141,-44) */
    VOS_INT16                           sRsrq;              /* RSRQ����ֵ��Χ��(-40, -6) */
    VOS_INT16                           sRssi;              /* RSSI����ֵ */
    VOS_UINT16                          usBer;              /* ������ */
    VOS_INT32                           lSINR;              /* SINR  RS_SNR */
    APP_RRC_CQI_INFO_STRU               stCQI;              /* CQI�������� */
}RRC_APP_CSQ_CNF_STRU;

/*****************************************************************************
 �ṹ��    :RRC_APP_CSQ_IND_STRU
 �ṹ˵��  :RRC�ϱ���APP������CSQ��ѯָʾ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_INT16                           sRsrp;              /* RSRP����ֵ��Χ��(-141,-44) */
    VOS_INT16                           sRsrq;              /* RSRQ����ֵ��Χ��(-40, -6) */
    VOS_INT16                           sRssi;              /* RSSI����ֵ */
    VOS_UINT16                          usBer;              /* ������ */
    VOS_INT32                           lSINR;              /* SINR  RS_SNR */
    APP_RRC_CQI_INFO_STRU               stCQI;              /* CQI�������� */
}RRC_APP_CSQ_IND_STRU;

/*****************************************************************************
 �ṹ��    :APP_RRC_PTL_STATE_QUERY_REQ_STRU
 �ṹ˵��  :Э��״̬��ѯ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    APP_CMD_ENUM_UINT8                  enCommand;
    APP_RRC_CELL_RPT_PERIOD_ENUM_UINT8  enPeriod;
    VOS_UINT8                           aucReserved[2];

}APP_RRC_PTL_STATE_QUERY_REQ_STRU;

/*****************************************************************************
 �ṹ��    : RRC_APP_PTL_STATE_QUERY_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RRC�ϱ���Э��״̬
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;             /* MSPֱ�ӽ���ID��ΪCmdID����Prob */
    APP_RESULT_ENUM_UINT32              enResult;
    //VOS_UINT32                          ulCurrentState;     /* RRCЭ��״̬, 0:��ʾIDLE̬ 1:��ʾCONNECTED 2:��ʾЭ��״̬��Ч */
}RRC_APP_PTL_STATE_QUERY_CNF_STRU;

/*****************************************************************************
 �ṹ��    : RRC_APP_PTL_STATE_CHANGE_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RRC�ϱ���Э��״̬
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulCurrentState;     /* RRCЭ��״̬, 0:��ʾIDLE̬ 1:��ʾCONNECTED 2:��ʾЭ��״̬��Ч */
}RRC_APP_PTL_STATE_CHANGE_IND_STRU;
/*niuxiufan DT begin */
/*****************************************************************************
 �ṹ��    : RRC_APP_PTL_STATE_CHANGE_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RRC�ϱ���Э��״̬
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    VOS_UINT32                          ulCurrentState;     /* RRCЭ��״̬, 0:��ʾIDLE̬ 1:��ʾCONNECTED 2:��ʾЭ��״̬��Ч */
}RRC_APP_DT_PTL_STATE_IND_STRU;

/*niuxiufan DT end */

/*****************************************************************************
 �ṹ��    :APP_RRC_PTL_STATE_QUERY_REQ_STRU
 �ṹ˵��  :С��������Ϣ��ѯ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
}APP_RRC_CELL_INFO_QUERY_REQ_STRU;

/*****************************************************************************
 �ṹ��    : RRC_APP_PTL_STATE_QUERY_CNF_STRU
 �ṹ˵��  : RRC�ظ���С��������Ϣ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    VOS_UINT16                          usFreq;             /* 0xFFFFΪ��Ч,��λ��100KHz */
    VOS_UINT16                          usPci;              /* 0xFFFFΪ��Ч,��Χ��(0,503) */
    VOS_UINT8                           ucDlBandWidth;      /* 0xffΪ��Ч,��Χ:(0,5): (0 : 1.4M , 1 : 3M , 2 : 5M ,3 : 10M , 4 : 15M, 5 : 20M) */
    VOS_UINT8                           aucReserved[3];
}RRC_APP_CELL_INFO_QUERY_CNF_STRU;

/* niuxiufan DT begin */
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgID;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    APP_CMD_ENUM_UINT8                  enCommand;
    APP_RRC_CELL_RPT_PERIOD_ENUM_UINT8  enPeriod;
    VOS_UINT8                           aucReserved[2];
}APP_RRC_INQ_CMD_REQ_STRU;

typedef APP_RRC_INQ_CMD_REQ_STRU APP_RRC_INQ_SERVING_CELL_INFO_REQ_STRU;

typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgID;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    APP_RESULT_ENUM_UINT32              enResult;
}APP_RRC_INQ_CMD_CNF_HEADER_STRU;
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgID;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
}APP_RRC_INQ_CMD_IND_HEADER_STRU;

/* niuxiufan DT end */

typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    APP_RESULT_ENUM_UINT32              enResult;
}RRC_APP_FORCE_HOANDCSEL_CNF_STRU;
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32 ulMsgID;                                     /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    DT_CMD_ENUM_UINT8                   enCmd;              /* FORCE HO/CSEL FLAG */
    VOS_UINT8                           ucRsv[3];
    VOS_UINT32                          ulPci;              /* PHY Cell ID */
}APP_RRC_FORCE_HOANDCSEL_REQ_STRU;
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    APP_RESULT_ENUM_UINT32              enResult;
}RRC_APP_BARCELL_ACCESS_CNF_STRU;
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32 ulMsgID;                                     /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    DT_CMD_ENUM_UINT8                   enCmd;              /* Bar Cell Access FLAG */
    VOS_UINT8                           ucRsv[3];
}APP_RRC_BARCELL_ACCESS_REQ_STRU;


/*****************************************************************************
 �ṹ��    : APP_RRC_MSG_DATA
 Э����  :
 ASN.1���� :
 �ṹ˵��  : APP_RRC_MSG_DATA���ݽṹ,����ΪRRCר��
*****************************************************************************/
typedef struct
{
    APP_RRC_MSG_ID_ENUM_UINT32          enMsgID;        /*_H2ASN_MsgChoice_Export APP_RRC_MSG_ID_ENUM_UINT32*/
    VOS_UINT8                           aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          APP_RRC_MSG_ID_ENUM_UINT32
    ****************************************************************************/
}APP_RRC_MSG_DATA;

/*_H2ASN_Length UINT32*/

/*****************************************************************************
 �ṹ��    : AppRrcInterface_MSG
 Э����  :
 ASN.1���� :
 �ṹ˵��  : AppRrcInterface_MSG���ݽṹ,����ΪRRCר��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    APP_RRC_MSG_DATA                    stMsgData;
}AppRrcInterface_MSG;
/*********************************************************
 ö����    : LRRC_LPHY_LTE_BAND_WIDTH_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  :
**********************************************************/
enum RRC_APP_BAND_WIDTH_ENUM
{
    RRC_APP_LTE_BAND_WIDTH_1D4M = 0,
    RRC_APP_LTE_BAND_WIDTH_3M,
    RRC_APP_LTE_BAND_WIDTH_5M,
    RRC_APP_LTE_BAND_WIDTH_10M,
    RRC_APP_LTE_BAND_WIDTH_15M,
    RRC_APP_LTE_BAND_WIDTH_20M,
    RRC_APP_LTE_BAND_WIDTH_BUTT
};
typedef VOS_UINT16 RRC_APP_BAND_WIDTH_ENUM_UINT16;

/*****************************************************************************
 �ṹ��    : APP_RRC_LWCLASH_REQ_STRU
 �ṹ˵��  :Э��״̬��ѯ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                      /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;        /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
} APP_RRC_LWCLASH_REQ_STRU;
/*****************************************************************************
 �ṹ��    : RRC_APP_LWCLASH_PARA_STRU
�ṹ˵��  : RRC�ϱ�����Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usUlFreq;          /*��������Ƶ�㵥λ:100Khz*/
    VOS_UINT16                              usDlFreq;          /*��������Ƶ�� ��λ:100Khz*/
    RRC_APP_BAND_WIDTH_ENUM_UINT16          usUlBandwidth;     /*���д��� */
    RRC_APP_BAND_WIDTH_ENUM_UINT16          usDlBandwidth;     /*���д��� */
    APP_CAMPED_FLAG_ENUM_UINT8              enCamped;          /*�Ƿ�פ�� */
    APP_STATE_FLAG_ENUM_UINT8               enState;           /*�Ƿ�Ϊ��ͻ״̬ */
    VOS_UINT8                               usBand;            /*Ƶ��ָʾ */
    VOS_UINT8                               aucResv[1];
} RRC_APP_LWCLASH_PARA_STRU;

/*****************************************************************************
 �ṹ��    : RRC_APP_LWCLASH_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                      /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;        /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;         /* MSPֱ�ӽ���ID��ΪCmdID����Prob */
    RRC_APP_LWCLASH_PARA_STRU       stLWClashPara;
} RRC_APP_LWCLASH_CNF_STRU;
/*****************************************************************************
 �ṹ��    : RRC_APP_LWCLASH_IND_STRU
�ṹ˵��  : RRC�ϱ�����Ϣ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                      /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;        /*_H2ASN_Skip*/
    RRC_APP_LWCLASH_PARA_STRU       stLWClashPara;
} RRC_APP_LWCLASH_IND_STRU;

/*****************************************************************************
 �ṹ��    :APP_RRC_NMR_REQ_STRU
 �ṹ˵��  :NMR��ѯ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
}APP_RRC_NMR_REQ_STRU;

/*****************************************************************************
 �ṹ��    :RRC_APP_NMR_CGI_STRU
 �ṹ˵��  :NMR�ṹ�嶨��
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usMncNum;           /*ָʾ MNC ����*/
    VOS_UINT16                          usMcc;
    VOS_UINT16                          usMnc;
    VOS_UINT8                           aucRes[2];
} RRC_APP_PLMN_ID_STRU;

/*****************************************************************************
 �ṹ��    :RRC_APP_NMR_CGI_STRU
 �ṹ˵��  :NMR�ṹ�嶨��
*****************************************************************************/
typedef struct
{
    RRC_APP_PLMN_ID_STRU                stPlmnId;
    VOS_UINT32                          sCellId;            /* ��Χ��(0,503) */
} RRC_APP_CELL_GLOBAL_ID_STRU;

/*****************************************************************************
 �ṹ��    :RRC_APP_NMR_CGI_STRU
 �ṹ˵��  :NMR�ṹ�嶨��
*****************************************************************************/
typedef struct
{
    RRC_APP_CELL_GLOBAL_ID_STRU         stCellGloId;        /* CellGlobalId */
    VOS_UINT16                          usTAC;
    VOS_UINT16                          usPci;              /* 0xFFFFΪ��Ч,��Χ��(0,503) */
    VOS_INT16                           sRsrp;              /* RSRP����ֵ��Χ��(-141,-44) */
    VOS_INT16                           sRsrq;              /* RSRQ����ֵ��Χ��(-40, -6) */
    VOS_UINT16                          usTa;               /* TAֵ*/
    VOS_UINT8                           aucRes[2];
} RRC_APP_LTE_CELL_INFO_STRU;

/*****************************************************************************
 �ṹ��    :RRC_APP_NMR_CNF_STRU
 �ṹ˵��  :NMR��ѯ������Ӧ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    APP_RESULT_ENUM_UINT32              enResult;
    RRC_APP_LTE_CELL_INFO_STRU          stLteCelInfo;
}RRC_APP_NMR_CNF_STRU;

/*****************************************************************************
 �ṹ��    :APP_RRC_CELLID_REQ_STRU
 �ṹ˵��  :С��������Ϣ��ѯ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
}APP_RRC_CELLID_REQ_STRU;

/*****************************************************************************
 �ṹ��    : RRC_APP_CELLID_CNF_STRU
 �ṹ˵��  : RRC�ظ���С��������Ϣ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    APP_RESULT_ENUM_UINT32              enResult;
    APP_PLMN_ID_STRU                    stPlmnId;
    VOS_UINT32                          ulCi;               /* 0xFFFFΪ��Ч, */
    VOS_UINT16                          usPci;              /* 0xFFFFΪ��Ч,��Χ��(0,503) */
    VOS_UINT16                          usTAC;             /* TAC */
}RRC_APP_CELLID_CNF_STRU;

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/
/*****************************************************************************
 �ṹ��    : APP_LPS_MSG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : Э��ջ��APP��Ľӿ���Ϣ�Ľṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulMsgId;      /*��ϢID*/
    VOS_UINT32                          ulSize;       /*��Ϣ��ĳ���*/
    VOS_UINT8                           aucValue[4];  /*��Ϣ����Ч���ݵ�ָ��*/
}APP_LPS_MSG_STRU;

/*****************************************************************************
 �ṹ��    : APP_LRRC_RESEL_OFFSET_CFG_NTF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : Э��ջ��APP��Ľӿ���Ϣ�Ľṹ��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                         /*_H2ASN_Skip*/
    VOS_UINT32             ulMsgId;        /*_H2ASN_Skip*/

    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    VOS_UINT32                           ulFlag;
}APP_LRRC_RESEL_OFFSET_CFG_NTF_STRU;

/* gaojishan-dcom-resel-cfg */
/*****************************************************************************
 �ṹ��    : APP_LRRC_CON_TO_IDLE_NTF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : Э��ջ��APP��Ľӿ���Ϣ�Ľṹ��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                         /*_H2ASN_Skip*/
    VOS_UINT32             ulMsgId;        /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;

    VOS_INT32              ulReserv;
}APP_LRRC_CON_TO_IDLE_NTF_STRU;

/* gaojishan-fast-dorm-cfg */

/*****************************************************************************
 ö����    : LRRC_LPDCP_FAST_DORMANCY_CMD_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ָʾPDCP������ֹͣFAST_DORMANCY
*****************************************************************************/
enum APP_LRRC_FAST_DORM_ENUM
{
    APP_LRRC_FAST_DORMANCY_STOP         = 0,                                  /* ֹͣFAST_DORMANCY */
    APP_LRRC_FAST_DORMANCY_START,                                             /* ����FAST_DORMANCY */
    APP_LRRC_FAST_DORMANCY_BUTT
};
typedef VOS_UINT32 APP_LRRC_FAST_DORM_ENUM_UINT32;

/*****************************************************************************
 �ṹ��    : APP_LRRC_FAST_DORM_CFG_NTF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : Э��ջ��APP��Ľӿ���Ϣ�Ľṹ��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                         /*_H2ASN_Skip*/
    VOS_UINT32             ulMsgId;        /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;

    APP_LRRC_FAST_DORM_ENUM_UINT32      ulFlag;
    VOS_UINT32            ulTimerLen;   /* unite: s */
}APP_LRRC_FAST_DORM_CFG_NTF_STRU;



/*****************************************************************************
 �ṹ��    : ID_APP_LRRC_SET_UE_REL_VERSION_REQ
 Э����  :
 ASN.1���� :
 �ṹ˵��  : Э��ջ��APP��Ľӿ���Ϣ�Ľṹ��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                         /*_H2ASN_Skip*/
    VOS_UINT32             ulMsgId;        /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    VOS_UINT32              ulMode;     /* 2:LTE , 1:TDS */
    VOS_UINT32              ulVersion;  /* 9 - 14 */
}APP_LRRC_SET_UE_REL_VERSION_REQ_STRU;

/*****************************************************************************
 �ṹ��    : ID_LRRC_APP_SET_UE_REL_VERSION_CNF
 Э����  :
 ASN.1���� :
 �ṹ˵��  : Э��ջ��APP��Ľӿ���Ϣ�Ľṹ��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                      /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;        /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;         /* MSPֱ�ӽ���ID��ΪCmdID����Prob */
    APP_RESULT_ENUM_UINT32              enResult;
} LRRC_APP_SET_UE_REL_VERSION_CNF_STRU;

/* begin: add for feature v700r500 */
/*****************************************************************************
 �ṹ��    : LRRC_APP_DBG_INFO_TYPE_ENUM
 �ṹ˵��  : DBG�ϱ���ö��
*****************************************************************************/
enum LRRC_APP_DBG_INFO_TYPE_ENUM
{
    LRRC_APP_BAR_CELL_INFO,    /* _H2ASN_MsgChoice LRRC_APP_LIMITED_INFO_STRU */
    LRRC_APP_DBG_COMM_INFO,    /* _H2ASN_MsgChoice LRRC_APP_DBG_COMM_INFO_STRU */
    LRRC_APP_DBG_RESEL_INFO,    /* _H2ASN_MsgChoice LRRC_APP_DBG_RESEL_INFO_STRU */
    LRRC_APP_DBG_INFO_TYPE_BUTT
};
typedef VOS_UINT32 LRRC_APP_DBG_INFO_TYPE_ENUM_UNIT32;

/*****************************************************************************
 �ṹ��    : LRRC_LCSEL_FORBIDDEN_CAUSE_ENUM
 Э����  :
 ASN.1���� :
 �ṹ˵��  : FORBIDDEN���������ϸ��ԭ��ֵ��Lģforbidden�б���ʹ�ã�bar�б�������
 *****************************************************************************/
enum LRRC_APP_FORBIDDEN_CAUSE_ENUM
{
    LRRC_APP_FORBIDDEN_CAUSE_NOT_EPLMN  = 0,                                  /* ���ڷ�EPLMNԭ�����forbidden */
    LRRC_APP_FORBIDDEN_CAUSE_FORBIDDEN,                                       /* ����ԭ��forbidden */
    LRRC_APP_FORBIDDEN_CAUSE_BUTT
};
typedef VOS_UINT16  LRRC_APP_FORBIDDEN_CAUSE_ENUM_UINT16;

/*****************************************************************************
 �ṹ��    : RRC_CSEL_LIMITED_ITEM_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����(Barred/Forbidden)С������Դ��,���������޽ڵ����Ϣ,��ʱ��ʱ���
*****************************************************************************/
typedef struct
{
    VOS_UINT16                             usFreqInfo;                             /* ����Ŀ��Ƶ����Ϣ */
    VOS_UINT16                             usCellId;                               /* ����Ŀ��С����Ϣ,����Чֵ��ʾ����Ƶ������ */
    LRRC_APP_FORBIDDEN_CAUSE_ENUM_UINT16   enForbCause;                         /* forbidden�б���forbidden��ԭ�򣬴���ֻ��forbidden�б���ʹ�ã�bar�б�����Ч */
    VOS_UINT8                              ucBandInd;                              /* �����б�����Ҫ���ӣ�bandָʾ */
    VOS_UINT8                              aucReserved[1];
    VOS_UINT32                             ulTimeOutTimeInMs;                      /* ����ĿʵЧ��ʱ�� */
    VOS_UINT32                             ulRemainTimerLenth;                     /* ���볬ʱʣ��ʱ�� */
} LRRC_APP_LIMITED_ITEM_STRU;

typedef struct
{
    VOS_UINT32                             ulCnt;
    LRRC_APP_LIMITED_ITEM_STRU             astLimitedItems[64];
}LRRC_APP_LIMITED_INFO_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_APP_DBG_INFO_TYPE_ENUM
 �ṹ˵��  : DBG�ϱ���ö��
*****************************************************************************/
enum LRRC_APP_DBG_FUN_NAME_ENUM
{
    LRRC_APP_DBG_NO_FUN_NAME = 0,
    SUBFUN_NULL_MARK_ONE_E,
    SUBFUN_NULL_MARK_TWO_E,
    SUBFUN_NULL_MARK_THREE_E,
    SUBFUN_NULL_MARK_FOUR_E,
    SUBFUN_NULL_MARK_FIVE_E,
    SUBFUN_NULL_MARK_SIX_E,
    SUBFUN_NULL_MARK_SEVEN_E,
    SUBFUN_NULL_MARK_EIGHT_E,
    SUBFUN_NULL_MARK_NINE_E,
    SUBFUN_NULL_MARK_TEN_E = 10,
    SUBFUN_NULL_MARK_ELEVEN_E,
    SUBFUN_NULL_MARK_TWELVE_E,
    SUBFUN_NULL_MARK_THIRTEEN_E,
    SUBFUN_NULL_MARK_FOURTEEN_E,
    SUBFUN_NULL_MARK_FIFTEEN_E = 15,
    LRRC_LCSEL_GetSysCfgSuspendFlag_E,
    RRC_CSEL_GetNcellNoEplmnSrchFlg_E,
    RRC_CSEL_CheckIsEPlmn_E,
    RRC_SIB_CheckIsStopRcvOtherSysInfoOrNot_E,
    RRC_CSEL_CheckTcellMultiBandInd_E = 20,
    LRRC_CSEL_CheckIsEmPlmn_E,
    RRC_CheckIsChinaMcc_E,
    LRRC_CSEL_CheckIsCellSearching_E,
    LRRC_CSEL_CheckIsInteroperability_E,
    RRC_CSEL_CheckCellIsBarBySIB1_E,
    RRC_CSEL_CheckIsEplmnBySIB1_E,
    RRC_CSEL_CheckIsForbiddenTacBySIB1_E,
    RRC_CSEL_CheckIsSatifySCritorBySIB1_E,
    RRC_CSEL_CheckTcellFreqBandInd_E,
    RRC_CSEL_CheckTaiNotInForbTa_E = 30,
    RRC_CSEL_CheckTCellBarredForReserved_E,
    RRC_CSEL_ProcSibGetSysinfoCnf_E,
    RRC_CSEL_ProcSibGetSysinfoCnfRcvSucc_E,
    RRC_CSEL_CheckTCellLimitStatus_E,
    RRC_CSEL_CheckTCellLimit_E,
    LRRC_LCSEL_CheckTCellBarred_E,
    RRC_CSEL_CheckCellAllFreqIsSupport_E,
    RRC_CSEL_CheckTCellSuitable_E,
    RRC_CSEL_SearchMovGetSysInfoBarOrForbidenInd_E,
    RRC_CSEL_ProcSibSysInfoSucLimitCell_E = 40,
    RRC_CSEL_CheckBandWidthIsSupport_E,
    LRRC_CSEL_CheckPartBandInCustBand_E,
    RRC_COMM_CheckPartBandInSpecBand_E,
    PS_IE_ABSENT_E,
    RRC_COMM_CalculateBandIndByDlEarfcn_E,
    RRC_COMM_CheckFreqIsInUeCapBand_E,
    RRC_COMM_CheckBandInfo_E,
    RRC_COMM_CalculateDlFreq_E,
    RRC_RB_CheckUuRrcConnRecfgMsgIe_E,
    RRC_RB_CheckTtiBundlingPara_E = 50,
    RRC_RB_CheckTtiBundlingAndSps_E,
    RRC_RRC_CheckTtiBundlingAndSps_E,
    RRC_RRC_CheckTtiBundlingAndSubframeAssign_E,
    RRC_RB_CheckRadioResourceCfgOfRrcConnRecfgMsg_E,
    RRC_RB_ReturnResultOfCheckRadioResDedic_E,
    RRC_RB_CheckPhyCfgDedicatedInfoOfRrcConnRecfgMsg_E,
    RRC_RB_CheckSpsCfgInfoOfRrcConnRecfgMsg_E,
    RRC_RRC_CheckDlSpsCfgInfoOfRrcConnSetupMsg_E,
    RRC_RRC_CheckUlSpsCfgInfoOfRrcConnSetupMsg_E,
    RRC_RB_CheckMacCfgInfoOfRrcConnRecfgMsg_E = 60,
    RRC_RRC_CheckMacMainCfgR11_E,
    RRC_RRC_CheckMacMainCfgR10_E,
    RRC_RRC_CheckConnectedDrxCfgOfRrcConnSetupMsg_E,
    RRC_RRC_CheckUlSchCfgOfRrcConnSetupMsg_E,
    UU_SPARE2_RETX_BSR_TIMER_E,
    RRC_RB_CheckDrbInfoOfRrcConnRecfgMsg_E,
    RRC_RB_CheckSrbInfoOfRrcConnRecfgMsg_E,
    RRC_RB_CheckRadioRsrcCfgPara_E,
    UU_MAX_NUM_OF_DRB_E,
    UU_C1_CRITI_EXT_RRC_CONN_RECFG_CHOSEN_E = 70,
    UU_RRC_CONN_RECFG_R8_C1_RRC_CONN_RECFG_CHOSEN_E,
    RRC_RB_CheckMobilityCtrlInfoOfRrcConnRecfgMsg_E,
    RRC_SMC_INACTIVE_E,
    RRC_COMM_CheckFreqIsInSpecBand_E,
    RRC_RB_CheckEutraCarrierFreqInfoOfMobilityCtrlInfo_E,
    RRC_RB_CheckLocalTtiBundlingAndSpsAfterCheckUu_E,
    RRC_RB_CheckSecurityCfgOfRrcConnRecfgMsg_E,
    RRC_RB_CheckIntraLteHoSecurityCfg_E,
    RRC_SMC_CheckSecurAlgorPara_E,
    RRC_RB_CheckBandWidthOfMobilityCtrlInfo_E = 80,
    UU_SPARE10_DL_BANDWIDTH_E,
    UU_SPARE10_UL_BANDWIDTH_E,
    RRC_RB_CheckAllFreqInMobilityCtrlInfoValid_E,
    RRC_CMM_UuMeasCfgCheck_E,
    RRC_CMM_UuMeasObjCfgCheck_E,
    RRC_CMM_UuMeasRptCfgCheck_E,
    RRC_CMM_UuMeasQuantCfgCheck_E,
    RRC_CMM_UuUtraMeasCfgCheck_E,
    RRC_CMM_UuMeasSpeedCfgCheck_E,
    RRC_CMM_UuUtraMeasCfgThrshldChk_E = 90,
    RRC_RB_CheckFullConfigOfRrcConnRecfgMsg_E,
    RRC_RB_CheckRadioResCfgCommInfoOfMobilityCtrlInfo_E,
    RRC_RB_CheckSrsUlCfgCommInfo_E,
    RRC_RB_CheckAntennaCfgInfoOfMobilityCtrlInfo_E,
    RRC_RB_CheckUpPwrCtrlCommR10OfMobilityCtrlInfo_E,
    RRC_RB_CheckMobilCtrlInfoOfGu2LHo_E,
    LPS_OM_GetTmode_E,
    RRC_CSEL_DecodeAccessSysInfoWhenSearch_E,
    RRC_COMM_CheckIsEqulCell_E,
    RRC_CSEL_GetCampState_E = 100,
    RRC_CSEL_GetSearchCampSate_E,
    LRRC_LCSEL_GetDeleteFddBandMCC_E,
    LRRC_LCSEL_GetDeleteFddBandFlg_E,
    RRC_SIB_GetRcvRslt_E,
    RRC_SIB_IsReceivedAll_E,
    RRC_CSEL_DecodeReselParamInSib3_E,
    RRC_CSEL_DecodeReselParamInSib4_E,
    RRC_CSEL_DecodeReselParamInSib5_E,
    RRC_CSEL_DecodeReselParamInSib6_E,
    LRRC_LCSEL_SaveUtraTddFreqListSib6_E = 110,
    LRRC_LCSEL_SaveUtraFddFreqListSib6_E,
    RRC_CSEL_DecodeReselParamInSib7_E,
	RRC_RRC_JudgeAccessRestrict_E,
    RRC_RRC_JudgeMoSignallingAccessRestrict_E,
    RRC_RRC_JudgeUsimAcIsValid_E,
    RRC_RRC_JudgeCellAccessIsBarredByRandom_E,
    RRC_RRC_JudgeEmergencyAndMoCallAcIsValid_E,
    RRC_COMM_CheckBandInUeCap_E,
    LRRC_COMM_SetMFBISupportFlag_E,
    LRRC_COMM_SetMFBICampOnWiderBandFlag_E = 120,
    LRRC_COMM_SaveCapBandFreqInfoTable_E,
    RRC_COMM_SortAndSaveSubBandInfo_E,
    LRRC_COMM_SrchSupportBandByFreq_E,
    RRC_COMM_DelMFBIBarredCellFromBarList_E,
    RRC_CSEL_DelCellFromBarredList_E,
    LRRC_LRRC_SaveW2LRedirReqMsg_E,
    LRRC_LRRC_SaveG2LRedirReqMsg_E,
    RRC_RRC_ConfigUuUlTransMsg_E,
    RRC_ITFL2_SndUlTransAmDataReq_E,
    RRC_RRC_ProcUlInfoTransMsg_E,
    RRC_COMM_CheckNeedHookDlMsg_E,
    LRRC_COMM_SetANRSupportFlag_E,
    LRRC_APP_DBG_FUN_NAME_ENUM_BUTT
};
typedef VOS_UINT32 LRRC_APP_DBG_FUN_NAME_ENUM_UNIT32;

typedef LRRC_APP_DBG_FUN_NAME_ENUM_UNIT32 LRRC_APP_DBG_SUBFUN_NAME_ENUM_UNIT32;
typedef LRRC_APP_DBG_FUN_NAME_ENUM_UNIT32 LRRC_APP_DBG_PARA_ENUM_UNIT32;
/*****************************************************************************
 �ṹ��    : LRRC_APP_DBG_MSG_TYPE_ENUM
 �ṹ˵��  : DBG�ϱ�������ö��
*****************************************************************************/
enum LRRC_APP_DBG_MSG_TYPE_ENUM
{
    FUNCTION_ENTRY_INFO = 0,                /* ������ڲ�����ӡ */
    CELL_BARED_BY_SIB,                      /* SIB��ϢָʾС����bar */
    CELL_FORBIDENED_BY_SIB,                 /* SIB��ϢָʾС����forbidden */
    CELL_FORBIDENED_BY_TAI,                 /* ����tai����forbidden ta list�� */
    CELL_BARED_BY_EPLMN_AC,                 /* ��ЧPLMN listΪ�� �� AC�����쳣 */
    CELL_BARED_BY_FIRST_PLMN_MCC,           /* SIB1��PlmnIdList�����ĵ�һ��PLMN��MCC������ */
    CELL_BAR_FORBIDEN,                      /* С����bar��forbidden */
    CELL_FREQ_BARED,                        /* Ƶ�ʱ�bar */
    CELL_NO_LIMIT,                          /* С�������� */
    DECODE_SYS_INFO_ERROR,                  /* ϵͳ��Ϣ������� */
    INVALID_S_VALUE,                        /* 10,������S׼�� */
    INVALID_FREQ_CELLID,                    /* Ƶ����� */
    INVALID_BAND,                           /* ��֧�ֵ�band */
    BAND_OUT_CUSTOM,                        /* band��Χ���ڶ��Ʒ�Χ�� */
    BAND_IN_CUSTOM,                         /* band��Χ�ڶ��Ʒ�Χ�� */
    BAND_FREQ_SUPPORT,                      /* band��Ƶ�ʶ���֧�ַ�Χ�� */
    BANDWIDTH_OUT_CUSTOM,                   /* �����ڶ��Ʒ�Χ�� */
    BAND_NOT_64,                            /* ��ǰband����band64 */
    CAMPED_ON_ANY_CELL,                     /* any cellפ��״̬ */
    MEASCFG_MSG_INVALID,                    /* ����������Ϣ���� */
    MSG_NULL,                               /* 20,����Ϣ */
    GU2L_LIMIT_NOTEPLMN_ACESS,              /* GU->L��ѡʱ���ǵ�ЧPLMN���Ƴ���bar */
    GU2L_LIMIT_FORBID_BAR,                  /* GU->L��ѡʱ����forbidden��bar */
    TAI_IN_FORBIDEN_TA,                     /* ����TAI�ڱ���ֹTA�б��� */
    TAI_NOT_IN_FORBIDEN_TA,                 /* TAI�����ڱ���ֹTA�б��� */
    CELL_CSG_INDICATION_TRUE,               /* С����csg-IndicationָʾΪTRUE */
    CELL_NOT_SUITABLE,                      /* ��suitableС�� */
    MAIN_STATUS_INVALID,                    /* ��״̬���� */
    RSRP_INVALID,                           /* RSRP������S׼�� */
    RSRQ_INVALID,                           /* RSRQ��SֵС��0 */
    HO_FAIL_CONF_UNACCEPTABLE,              /* 30,�л�ʧ��ԭ��ֵΪCONF_UNACCEPTABLE */
    HO_FAIL_ARFCN_NOT_SUPPORT,              /* �л�ʧ��ԭ��ֵΪARFCN_NOT_SUPPORT */
    BANDWIDTH_INVALID,                      /* �������� */
    PUCCH_INVALID,                          /* PUCCH������ */
    PARA_VAL_INVALID,                       /* ����ȡֵ�Ƿ� */
    MOBILOTY_AS_SECURITY_INACTIVE,          /* ��ȫδ���� */
    MOBILOTY_INCLUDE_NAS_INFO,              /* ����NAS��Ϣ */
    TMODE_ERROR,                            /* ģʽ���� */
    CONFIG_UNSUPPORT,                       /* ���ò������� */
    ARRAY_OVERFLOW,                         /* ����Խ�� */
    NOT_CHINA_MCC,                          /* 40,�ǹ���MCC */
    JP_MCC_MNC_NOT_EPLMN,                   /* �������ƣ�MNC1����EPLMN */
    NOT_JP_MCC,                             /* ���ձ�MCC */
    CHINA_MODE_DEL_FDD_BAND,                /* ����ģʽɾ��FDDband */
    ONLY_NO_SIB12,                          /* ��û�յ�sib12 */
    USIM_ABSENT_OR_INVALID,                 /* USIM�������ڻ򲻿��� */
    T302_RUNNING,                           /* T302������ */
    T305_RUNNING,                           /* T305������ */
    MFBI_FLAG_OFF,                          /* MFBI���عر� */
    MFBI_FLAG_ON,                           /* 50,MFBI���ش� */
    WIDER_BAND_FLAG,                        /* פ����Э������������Band���� */
    CHECK_ALL_BAND,                         /* ���UE֧�ֵ�����band */
    ULTRANSMSG_MASK,                        /* �����ε�����ֱ����Ϣ */
    DLTRANSMSG_MASK,                        /* �����ε�����ֱ����Ϣ */
    LMM_DATA_REQ,                           /* LMM_LRRC_DATA_REQ */
    AM_DATA_IND,                            /* AM DTAT IND */
    AM_DATA_REQ,                            /* AM DTAT REQ */
    ANR_FLAG,                               /* ANR���� */
    LRRC_APP_DBG_MSG_TYPE_ENUM_BUTT
};
typedef VOS_UINT32 LRRC_APP_DBG_MSG_TYPE_ENUM_UINT32;

/*****************************************************************************
 �ṹ��    : RRC_DEBUG_PRINT_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    LRRC_APP_DBG_MSG_TYPE_ENUM_UINT32       enMsgType;
    LRRC_APP_DBG_FUN_NAME_ENUM_UNIT32       enFunName;
    LRRC_APP_DBG_SUBFUN_NAME_ENUM_UNIT32    enSubFunName;
    LRRC_APP_DBG_PARA_ENUM_UNIT32           enPara1;
    LRRC_APP_DBG_PARA_ENUM_UNIT32           enPara2;
    VOS_INT32                               lPara3;
    VOS_INT32                               lPara4;
    VOS_INT32                               lPara5;
    VOS_INT32                               lPara6;
    VOS_INT32                               lPara7;
    VOS_INT32                               lPara8;
}LRRC_APP_DBG_ERROR_INFO_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_APP_DBG_RESEL_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : 0xFFFFFFFF Ϊ��Чֵ
*****************************************************************************/
typedef struct
{
    LRRC_APP_DBG_FUN_NAME_ENUM_UNIT32           enFunName;
    VOS_UINT32                                  ulFreq;
    VOS_UINT32                                  ulSsc_Switch;
    VOS_UINT32                                  ulAdrx_Switch;
    VOS_INT32                                   lq_RxLevMin;
    VOS_INT32                                   lthreshServingLowP;
    VOS_INT32                                   lthreshServingLowQ;
    VOS_INT32                                   lT_Reselection;
    VOS_INT32                                   lscell_priority;
    VOS_INT32                                   lncell_priority;
    VOS_INT32                                   lthreshX_HighP;
    VOS_INT32                                   lthreshX_LowP;
    VOS_INT32                                   lthreshX_HighQ;
    VOS_INT32                                   lthreshX_LowQ;
    VOS_INT32                                   lSCell_sValue;
    VOS_INT32                                   lNCell_sValue;
    VOS_INT32                                   lSCell_qValue;
    VOS_INT32                                   lNCell_qValue;
    VOS_INT32                                   ls_IntraSerchP;
    VOS_INT32                                   ls_IntraSerchQ;
    VOS_INT32                                   ls_NonIntraSerchP;
    VOS_INT32                                   ls_NonIntraSerchQ;
    VOS_INT32                                   lQ_offset;
    VOS_INT32                                   lQ_Hyst;
    VOS_INT32                                   lStart_Meas_SCell_Rsrp;
    VOS_INT32                                   lStart_Meas_SCell_Rsrq;
    VOS_INT32                                   lHigh_pri_NCell_Rsrp;
    VOS_INT32                                   lHigh_pri_NCell_Rsrq;
    VOS_INT32                                   lLow_pri_SCell_Rsrp;
    VOS_INT32                                   lLow_pri_SCell_Rsrq;
    VOS_INT32                                   lLow_pri_NCell_Rsrp;
    VOS_INT32                                   lLow_pri_NCell_Rsrq;
    VOS_INT32                                   lIntra_Freq_SCell_Rsrp;
    VOS_INT32                                   lIntra_Freq_NCell_Rsrp;
}LRRC_APP_DBG_RESEL_INFO_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_APP_DBG_INFO_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : Debug�ϱ����ͽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                           /*_H2ASN_Skip*/
    VOS_UINT32                               ulMsgId;        /*_H2ASN_Skip*/
    LRRC_APP_DBG_INFO_TYPE_ENUM_UNIT32       enReportType;
    union  /* _H2ASN_Skip */
    {      /* _H2ASN_Skip */
        LRRC_APP_LIMITED_INFO_STRU          stLimitedInfo;   /* _H2ASN_Skip */
        LRRC_APP_DBG_ERROR_INFO_STRU        stCommDbgInfo;   /* _H2ASN_Skip */
        LRRC_APP_DBG_RESEL_INFO_STRU        stReselDbgInfo;
        /******************************************************************************************************
            _H2ASN_IeChoice_When        LRRC_APP_DBG_INFO_TYPE_ENUM_UNIT16
        ******************************************************************************************************/
    }u;  /* _H2ASN_Skip */
}LRRC_APP_DBG_INFO_IND_STRU;
/* end: add for feature v700r500 */

/* add for AT&T LRRC DAM begin */
enum LRRC_APP_CONNREQ_TIMER_STATUS_ENUM
{
    LRRC_APP_CONNREQ_TIMER_STATUS_NOT_USED = 0 ,
    LRRC_APP_CONNREQ_TIMER_STATUS_USED = 1,

    LRRC_APP_CONNREQ_TIMER_STATUS_BUTT
};
typedef VOS_UINT8 LRRC_APP_CONNREQ_TIMER_STATUS_ENUM_UINT8;

enum LRRC_APP_TIMER_STATUS_ENUM
{
    LRRC_APP_TIMER_STATUS_RUNNING = 1,
    LRRC_APP_TIMER_STATUS_STOP = 2,
    LRRC_APP_TIMER_STATUS_BUTT
};
typedef VOS_UINT8 LRRC_APP_TIMER_STATUS_ENUM_UINT8;

/*****************************************************************************
 �ṹ��    : LRRC_APP_DAM_STATUS_DBG_INFO_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    PS_BOOL_ENUM_UINT8                  enDAMSwitchStatus; /* RRC DAM����״̬,0:�ر�,1:�� */
    VOS_UINT8                           ucDAMCRRCCurrentCnt; /* DAM CRRC����������ֵ */
    VOS_UINT8                           ucDAMJudgeMaxCRRCCnt; /* NV�������CRRC������ֵ */
    LRRC_APP_CONNREQ_TIMER_STATUS_ENUM_UINT8         enDAMConnReqTimerStatus; /* DAM��������ʧ���ж϶�ʱ��״̬ */
    VOS_UINT8                           ucDAMCellBarTimerLenth; /* TRRC��ʱ��ʱ�� */
    LRRC_APP_TIMER_STATUS_ENUM_UINT8    enDAMCellBarTimerStatus; /* TRRC��ʱ��״̬ */
    VOS_UINT16                          usSrvCellId; /* ���ֽ���ʧ�ܵķ���С��id */
    VOS_UINT16                          usSrvFreq; /* ���ֽ���ʧ�ܵķ���С��Ƶ�� */
    VOS_UINT16                          usRev; /* ���� */
    VOS_UINT32                          ulTimeOutInMs; /* ���������о���ʱ����ʱʱ��ms */
    VOS_UINT32                          ulCurrentTimeInMs; /* ��ǰʱ��ms */
}LRRC_APP_DAM_STATUS_DBG_INFO_IND_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_DAM_BAR_LIST_ITEM_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usFreqInfo;
    VOS_UINT16                          usCellId;
    VOS_UINT8                           ucBandInd;
    VOS_UINT8                           aucReserved[3];
    VOS_UINT32                          ulTimeOutTimeInMs;
    VOS_UINT32                          ulRemainTimeOutInMs;
}LRRC_DAM_BAR_LIST_ITEM_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_APP_DAM_BAR_LIST_DBG_INFO_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT16                          usItemCount; /* Bar List����Ŀ���� */
    VOS_UINT16                          usRev;  /* ���� */
    LRRC_DAM_BAR_LIST_ITEM_STRU         astDamBarListItem[RRC_APP_MAX_LIMITED_ITEM_COUNT];
}LRRC_APP_DAM_BAR_LIST_DBG_INFO_IND_STRU;
/* add for AT&T LRRC DAM end */
/*****************************************************************************
 �ṹ��    : LRRC_APP_IDLE_SERVE_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : Э��ջ��APP��Ľӿ���Ϣ�Ľṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          enCurrReselPrior;    /* ��ǰʹ�õ���ѡ���ȼ����ƶ���ת����ʱ�� */
    VOS_UINT16                          enBandInd;           /* Ƶ��ָʾ */
    VOS_UINT16                          usFreqInfo;          /* ����С��Ƶ�� */
    VOS_UINT16                          usCellId;            /* ����С��ID */
    VOS_INT16                           sRsrp;               /* RSRP����ֵ */
    VOS_INT16                           sRsrq;               /* RSRQ����ֵ */
    VOS_INT16                           sRssi;               /* RSSI����ֵ */
    VOS_INT16                           sSValue;             /*����õ���SPֵ*/
    VOS_INT16                           sSqual;              /*����õ���SQֵ*/
    VOS_INT16                           sQRxLevMin;          /*׼��RSRP��������*/
    VOS_INT16                           sPCompensation;      /* ���� P-Max �� UE Max Tx power ��������� PCompensation */
    VOS_INT16                           sQqualMin;           /* S׼��RSRQ�������� */
    VOS_INT16                           sSIntraSearchP;      /* ����ͬƵ������rsrp��ֵ���� */
    VOS_INT16                           sSIntraSearchQ;      /* ����ͬƵ������rsrq��ֵ���� */
    VOS_INT16                           sSNonIntraSearchP;   /* ����ͬ���ȼ��͵����ȼ���Ƶ������rsrp��ֵ���� */
    VOS_INT16                           sSNonIntraSearchQ;   /* ����ͬ���ȼ��͵����ȼ���Ƶ������rsrq��ֵ���� */
    VOS_INT16                           sThreshServingLowP;  /* ��Ե����ȼ�С����ѡ�ķ���С���������� */
    VOS_INT16                           sThreshServingLowQ;  /* ��ѡ����ʱʹ��R9���� */
} LRRC_APP_IDLE_SERVE_INFO_STRU;


/*****************************************************************************
 �ṹ��    : LRRC_APP_IDLE_INTRA_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : Э��ջ��APP��Ľӿ���Ϣ�Ľṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usCellId;
    VOS_INT16                           sSValue;            /*����õ���SPֵ*/
    VOS_INT16                           sSqual;             /*����õ���SQֵ*/
    VOS_INT16                           sRsrp;              /* RSRP����ֵ */
    VOS_INT16                           sRsrq;              /* RSRQ����ֵ */
    VOS_INT16                           sRssi;              /* RSSI����ֵ */
}LRRC_APP_IDLE_CELL_MEAS_RESULT_STRU;

typedef struct
{
    VOS_UINT16                          enCurrReselPrior;    /* ��ǰʹ�õ���ѡ���ȼ����ƶ���ת����ʱ�� */
    VOS_UINT16                          enBandInd;           /* Ƶ��ָʾ */
    VOS_UINT16                          usFreqInfo;          /*Ƶ��*/
    VOS_UINT16                          usTotalCellNum;      /*С������*/
    VOS_UINT16                          usDetectedCellNum;   /*��⵽��С����Ŀ*/
    VOS_INT16                           sQRxLevMin;          /*����SPֵ�õ�����ͽ����ƽ*/
    VOS_INT16                           sPCompensation;      /* ���� P-Max �� UE Max Tx power ��������� PCompensation */
    VOS_INT16                           sQqualMin;           /* S׼��RSRQ�������� */
    VOS_INT16                           sSIntraSearchP;      /* ����ͬƵ������rsrp��ֵ���� */
    VOS_INT16                           sSIntraSearchQ;      /* ����ͬƵ������rsrq��ֵ���� */
    LRRC_APP_IDLE_CELL_MEAS_RESULT_STRU astIntraCellMesRslt[LRRC_LCSEL_INTRA_CELL_REPORT_NUM];
}LRRC_APP_IDLE_INTRA_INFO_STRU;



/*****************************************************************************
 �ṹ��    : LRRC_APP_IDLE_INTER_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : Э��ջ��APP��Ľӿ���Ϣ�Ľṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              enCurrReselPrior;    /* ��ǰʹ�õ���ѡ���ȼ����ƶ���ת����ʱ�� */
    VOS_UINT16                              usFreqInfo;
    VOS_UINT16                              enBandInd;           /* Ƶ��ָʾ */
    VOS_INT16                               sThreshLowP;         /* ��Ե����ȼ�С����ѡ�ķ���С���������� */
    VOS_INT16                               sThreshLowQ;         /* ��ѡ����ʱʹ��R9���� */
    VOS_INT16                               sThreshHighP;        /* ��Ե����ȼ�С����ѡ�ķ���С���������� */
    VOS_INT16                               sThreshHighQ;        /* ��ѡ����ʱʹ��R9���� */
    VOS_UINT16                              usTotalCellNum;      /*С������*/
    VOS_UINT16                              usDetectedCellNum;   /*��⵽��С����Ŀ*/
    LRRC_APP_IDLE_CELL_MEAS_RESULT_STRU     astInterCellMesRslt[LRRC_LCSEL_INTER_CELL_REPORT_NUM];/* SCELL���ڵ�һ����λ�� */
}LRRC_APP_IDLE_SINGLE_FREQ_MEAS_RESULT_STRU;

typedef struct
{
    VOS_UINT16                                   usInterFreqNum;
    VOS_INT16                                    sSNonIntraSearchP;   /* ����ͬ���ȼ��͵����ȼ���Ƶ������rsrp��ֵ���� */
    VOS_INT16                                    sSNonIntraSearchQ;   /* ����ͬ���ȼ��͵����ȼ���Ƶ������rsrq��ֵ���� */
    VOS_INT16                                    sServValue;          /*����õ���SPֵ*/
    VOS_INT16                                    sServqual;           /*����õ���SQֵ*/
    VOS_INT16                                    sThreshServingLowP;  /* ��Ե����ȼ�С����ѡ�ķ���С���������� */
    VOS_INT16                                    sThreshServingLowQ;  /* ��ѡ����ʱʹ��R9���� */
    LRRC_APP_IDLE_SINGLE_FREQ_MEAS_RESULT_STRU   astInterFreqMesRslt[LRRC_LCSEL_INTER_FREQ_REPORT_NUM];
}LRRC_APP_IDLE_INTER_INFO_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_APP_IDLE_UTRAN_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : Э��ջ��APP��Ľӿ���Ϣ�Ľṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usPrimaryCode;
    VOS_INT16                               sRscp;               /* ����1/8 */
    VOS_INT16                               sEcN0;               /* ����1/8 */
    VOS_INT16                               sSValue;             /*����õ���SPֵ*/
    VOS_INT16                               sSqual;              /*����õ���SQֵ*/
}LRRC_APP_UTRAN_CELL_MEAS_RESULT_STRU;

typedef struct
{
    VOS_UINT16                              enCurrReselPrior;    /* ��ǰʹ�õ���ѡ���ȼ����ƶ���ת����ʱ�� */
    VOS_UINT16                              usArfcn;
    VOS_INT16                               sRssi;               /* ����1/8 */
    VOS_INT16                               sQRxLevMin;          /*����SPֵ�õ�����ͽ����ƽ*/
    VOS_INT16                               sPCompensation;      /* ���� P-Max �� UE Max Tx power ��������� PCompensation */
    VOS_INT16                               sQqualMin;           /* S׼��RSRQ�������� */
    VOS_INT16                               sThreshLowP;         /* ��Ե����ȼ�С����ѡ�ķ���С���������� */
    VOS_INT16                               sThreshLowQ;         /* ��ѡ����ʱʹ��R9���� */
    VOS_INT16                               sThreshHighP;        /* ��Ե����ȼ�С����ѡ�ķ���С���������� */
    VOS_INT16                               sThreshHighQ;        /* ��ѡ����ʱʹ��R9���� */
    VOS_UINT16                              usCellNum;
    LRRC_APP_UTRAN_CELL_MEAS_RESULT_STRU    astUtranCellMesRslt[LRRC_LCSEL_UTRAN_CELL_REPORT_NUM];
}LRRC_APP_UTRAN_SIGNLE_FREQ_MEAS_RESULT_STRU;

typedef struct
{
    VOS_UINT16                                      usArfcnNum;
    VOS_INT16                                       sSNonIntraSearchP;   /* ����ͬ���ȼ��͵����ȼ���Ƶ������rsrp��ֵ���� */
    VOS_INT16                                       sSNonIntraSearchQ;   /* ����ͬ���ȼ��͵����ȼ���Ƶ������rsrq��ֵ���� */
    VOS_INT16                                       sServValue;          /*����õ���SPֵ*/
    VOS_INT16                                       sServqual;           /*����õ���SQֵ*/
    VOS_INT16                                       sThreshServingLowP;  /* ��Ե����ȼ�С����ѡ�ķ���С���������� */
    VOS_INT16                                       sThreshServingLowQ;  /* ��ѡ����ʱ�S���R9���� */
    LRRC_APP_UTRAN_SIGNLE_FREQ_MEAS_RESULT_STRU     astUtranFreqMesRslt[LRRC_TRRC_PHY_MAX_SUPPORT_CARRIER_NUM];
}LRRC_APP_IDLE_UTRAN_INFO_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_APP_IDLE_UTRAN_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : Э��ջ��APP��Ľӿ���Ϣ�Ľṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              enCurrReselPrior;   /* ��ǰʹ�õ���ѡ���ȼ����ƶ���ת����ʱ�� */
    VOS_UINT16                              usArfcn;
    VOS_UINT16                              enBandInd;          /* Ƶ��ָʾ */
    VOS_INT16                               sRssi;              /* ����1/8 */
    VOS_UINT16                              usNcc;
    VOS_UINT16                              usBcc;
    VOS_INT16                               sSValue;             /*����õ���SPֵ*/
    VOS_INT16                               sQRxLevMin;          /*����SPֵ�õ�����ͽ����ƽ*/
    VOS_INT16                               sPCompensation;      /* ���� P-Max �� UE Max Tx power ��������� PCompensation */
    VOS_INT16                               sThreshLowP;         /* ��Ե����ȼ�С����ѡ�ķ���С���������� */
    VOS_INT16                               sThreshHighP;        /* ��Ե����ȼ�С����ѡ�ķ���С���������� */
}LRRC_APP_GERAN_SIGNLE_FREQ_MEAS_RESULT_STRU;

typedef struct
{
    VOS_UINT16                                    usArfcnNum;
    VOS_INT16                                     sSNonIntraSearchP;   /* ����ͬ���ȼ��͵����ȼ���Ƶ������rsrp��ֵ���� */
    VOS_INT16                                     sSNonIntraSearchQ;   /* ����ͬ���ȼ��͵����ȼ���Ƶ������rsrq��ֵ���� */
    VOS_INT16                                     sServValue;          /*����õ���SPֵ*/
    VOS_INT16                                     sServqual;           /*����õ���SQֵ*/
    VOS_INT16                                     sThreshServingLowP;  /* ��Ե����ȼ�С����ѡ�ķ���С���������� */
    VOS_INT16                                     sThreshServingLowQ;  /* ��ѡ����ʱʹ��R9���� */
    LRRC_APP_GERAN_SIGNLE_FREQ_MEAS_RESULT_STRU   astGeranFreqMesRslt[LRRC_GURRC_GERAN_ARFCN_MAX_NUM];
}LRRC_APP_IDLE_GERAN_INFO_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_APP_CELL_MEAS_RSLT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : Э��ջ��APP��Ľӿ���Ϣ�Ľṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usCellId;
    VOS_UINT16                          usFreqInfo;
    VOS_INT16                           sRsrp;              /* RSRP����ֵ */
    VOS_INT16                           sRsrq;              /* RSRQ����ֵ */
    VOS_INT16                           sRssi;              /* RSSI����ֵ */
} LRRC_APP_CELL_MEAS_RSLT_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_APP_UTRAN_MEAS_RSLT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : Э��ջ��APP��Ľӿ���Ϣ�Ľṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usArfcn;
    VOS_UINT16                          usPrimaryCode;
    VOS_INT16                           sRscp;               /* ����1/8 */
    VOS_INT16                           sEcN0;               /* ����1/8 */
    VOS_INT16                           sRssi;               /* ����1/8 */
    VOS_UINT16                          UtranType;
} LRRC_APP_UTRAN_CELL_RSLT_STRU;
/*****************************************************************************
 ö����     :LRRC_GRR_BANDINDICATOR_ENUM
 Э����  :
 ASN.1����   :
 ö��˵�� : 2GС��Ƶ��ָʾ
*****************************************************************************/
enum LRRC_APP_GERAN_BANDIND_ENUM
{
    DCS1800                          = 0,
    PCS1900                          = 1,

    LRRC_APP_GERAN_BANDIND_BUTT      = 0xFFFF
};
typedef VOS_UINT16    LRRC_APP_GERAN_BANDIND_ENUM_UINT16;

/*****************************************************************************
 �ṹ��    : LRRC_APP_UTRAN_MEAS_RSLT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : Э��ջ��APP��Ľӿ���Ϣ�Ľṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usArfcn;
    LRRC_APP_GERAN_BANDIND_ENUM_UINT16  enBandInd;          /* Ƶ��ָʾ */
    VOS_INT16                           sRssi;              /* ����1/8 */
} LRRC_APP_GERAN_CELL_RSLT_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_APP_SERV_MEAS_RSLT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : Э��ջ��APP��Ľӿ���Ϣ�Ľṹ��
*****************************************************************************/
typedef struct
{
    LRRC_APP_CELL_MEAS_RSLT_STRU       stServCellRslt;                            /* ����С���ϱ���� */
} LRRC_APP_SERV_MEAS_RSLT_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_APP_SCELL_MEAS_RSLT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : Э��ջ��APP��Ľӿ���Ϣ�Ľṹ��
*****************************************************************************/
typedef struct
{
    LRRC_APP_CELL_MEAS_RSLT_STRU       astSCellRslt[LRRC_SCELL_MAX_NUM];          /* SCell�ϱ���� */
} LRRC_APP_SCELL_MEAS_RSLT_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_APP_INTRA_MEAS_RSLT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : Э��ջ��APP��Ľӿ���Ϣ�Ľṹ��
*****************************************************************************/
typedef struct
{
    LRRC_APP_CELL_MEAS_RSLT_STRU       astIntraCellRslt[LRRC_INTRA_CELL_MAX_NUM]; /* ͬƵС���ϱ���� */
} LRRC_APP_INTRA_MEAS_RSLT_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_APP_INTER_MEAS_RSLT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : Э��ջ��APP��Ľӿ���Ϣ�Ľṹ��
*****************************************************************************/
typedef struct
{
    LRRC_APP_CELL_MEAS_RSLT_STRU       astInterCellRslt[LRRC_INTER_CELL_MAX_NUM]; /* ��ƵС���ϱ���� */
} LRRC_APP_INTER_MEAS_RSLT_STRU;
/*****************************************************************************
 �ṹ��    : LRRC_APP_INTER_MEAS_RSLT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : Э��ջ��APP��Ľӿ���Ϣ�Ľṹ��
*****************************************************************************/
typedef struct
{
    LRRC_APP_UTRAN_CELL_RSLT_STRU       astUtranCellRslt[LRRC_UTRAN_CELL_MAX_NUM]; /* ��ƵС���ϱ���� */
} LRRC_APP_UTRAN_MEAS_RSLT_STRU;
/*****************************************************************************
 �ṹ��    : LRRC_APP_INTER_MEAS_RSLT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : Э��ջ��APP��Ľӿ���Ϣ�Ľṹ��
*****************************************************************************/
typedef struct
{
    LRRC_APP_GERAN_CELL_RSLT_STRU       astGeranCellRslt[LRRC_GERAN_CELL_MAX_NUM]; /* ��ƵС���ϱ���� */
} LRRC_APP_GERAN_MEAS_RSLT_STRU;

extern PS_BOOL_ENUM_UINT8  LRRC_COMM_LoadDspAlready( VOS_VOID );

extern VOS_UINT32 LHPA_InitDsp( VOS_VOID );
extern VOS_VOID LHPA_DbgSendSetWorkMode_toMaterMode(VOS_VOID);
extern VOS_VOID LHPA_DbgSendSetWorkMode_toSlaveMode(VOS_VOID);
extern VOS_UINT32  RRC_RRC_LoadDsp( VOS_VOID );
extern VOS_VOID * LAPP_MemAlloc( VOS_UINT32 ulSize );
extern VOS_UINT32  LApp_MemFree(VOS_VOID *pAddr );
extern VOS_UINT32  LAppSndMsgToLPs(APP_LPS_MSG_STRU  *pstAppToPsMsg );
extern 	VOS_UINT32 LHPA_InitDsp_ForAT( VOS_VOID );
extern VOS_UINT32 LHPA_InitDspNvForLteTdsCBT(VOS_VOID);
extern VOS_UINT32 LHPA_LoadDspForLteCBT(VOS_VOID);
extern VOS_VOID   LHPA_DbgSetSlaveModeThenMasterMode(VOS_VOID);

/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/


/*****************************************************************************
  9 OTHERS
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

#endif /* end of AppRrcInterface.h */
