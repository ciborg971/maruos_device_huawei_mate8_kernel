

#ifndef __LRRCLNASINTERFACE_H__
#define __LRRCLNASINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include "LPSCommon.h"
#include "ComInterface.h"
#include "LNasNvInterface.h"

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 macro
*****************************************************************************/

/* ��ЧPLMN������ */
#define LRRC_LNAS_MAX_EQUPLMN_NUM         16

/* EHPLMN������ */
#define LRRC_LNAS_MAX_EHPLMN_NUM          (LRRC_LNAS_MAX_EQUPLMN_NUM + 1)

/* FORBID LA ������ */
#define LRRC_LNAS_MAX_FORBLA_NUM          64

/* lishangfeng bg begin */
/* FORBID LA ������ */
#define LRRC_LNAS_BG_MAX_FORBLA_NUM       16

#define LRRC_LNAS_BG_MAX_SRCH_PLMN_NUM    16

#define LRRC_LNAS_MAX_RAT_NUM             (3)

/* lishangfeng bg end */


/* FORBID TA ������ */
#define LRRC_LNAS_MAX_FORBTA_NUM          64

/* ������PLMN ������ */
#define LRRC_LNAS_MAX_HIGH_PLMN_NUM       48

/* ������PLMN ������ */
#define LRRC_LNAS_MAX_LOW_PLMN_NUM        48

/* ָ��plmn����ʧ�ܺ��ϱ���plmn�����  */
#define LRRC_LNAS_MAX_SEARCHED_PLMN_NUM   16

/*begin:add by wangmiao00272217 for ���������Ż�*/
#define LRRC_LMM_MAX_SEARCHED_TAI_NUM    16
/*end:add by wangmiao00272217 for ���������Ż�*/

/* NAS������󳤶� */
#define LRRC_LNAS_MAX_DATA_LENGTH         1024

/* ��GU�л���L��LRRC�ϱ��İ�ȫ�����ĳ���*/
#define LRRC_LNAS_GU2L_HO_SECU_PARA_LEN   6



/* ���� UE ID ��ŵ�����ֽ���Ŀ,����LENTH�ֽ�:
   The IMSI shall not exceed 15 digits, ie 7 and a half of bytes;
   the TMSI/P-TMSI is 4 octets long;
   the IMEI is composed of 15 digits;
   the IMEISV is 16 digits;
*/
#define LRRC_LNAS_MAX_UEID_BUF_SIZE       10                  /* UNIT: BYTE  */

#define LRRC_LNAS_MAX_ASME_KEY_LEN        32

#define LRRC_LNAS_MAX_RAB_SETUP_NUM       11                  /* ���������RAB��  */
/* ncell spec search begin */
#define LRRC_LNAS_MAX_ARFCN_NUM          (8)                  /* LTEƵ���б������� */
/* ncell spec search end */

/*Modify by sunbing 49683 for CL multimode 2014-01-09 begin*/
#define LRRC_LNAS_LTE_CELL_ID_MAX_NUM    (8)                  /* LTEС��ID������ */
/*Modify by sunbing 49683 for CL multimode 2014-01-09 end*/

/* add for LTE NetScan begin */
#define LRRC_LNAS_NETSCAN_MAX_FREQ_NUM   (20)
/* add for LTE NetScan end */

#define LRRC_LMM_BG_HRPD_MAX_SUBNET_NUM   16
#define LRRC_LMM_HRPD_SUBNET_MAX_LEN      16

#define LMM_LRRC_MSG_HDR                  (PS_MSG_ID_NAS_TO_RRC_BASE)
#define LRRC_LMM_MSG_HDR                  (PS_MSG_ID_RRC_TO_NAS_BASE)
#define LRABM_LRRC_MSG_HDR                (PS_MSG_ID_NAS_TO_RRC_BASE + 0x40)
#define LRRC_LRABM_MSG_HDR                (PS_MSG_ID_RRC_TO_NAS_BASE + 0x40)

#define LRRC_LRRC_IsGUCRedir_Flow()      ( LRRC_COMM_GetFlowCtrlFlg() ==LRRC_FLOW_CTRL_TYPE_L2W_REDIR_FAIL || \
                                             LRRC_COMM_GetFlowCtrlFlg() ==LRRC_FLOW_CTRL_TYPE_L2W_START_REDIR || \
                                             LRRC_COMM_GetFlowCtrlFlg() ==LRRC_FLOW_CTRL_TYPE_L2G_REDIR_FAIL || \
                                             LRRC_COMM_GetFlowCtrlFlg() ==LRRC_FLOW_CTRL_TYPE_L2G_START_REDIR || \
                                             LRRC_COMM_GetFlowCtrlFlg() ==LRRC_FLOW_CTRL_TYPE_L2T_START_REDIR || \
                                             LRRC_COMM_GetFlowCtrlFlg() ==LRRC_FLOW_CTRL_TYPE_L2C_START_RESEL || \
                                             LRRC_COMM_GetFlowCtrlFlg() ==LRRC_FLOW_CTRL_TYPE_L2C_RESEL_FAIL || \
                                             LRRC_COMM_GetFlowCtrlFlg() ==LRRC_FLOW_CTRL_TYPE_L2C_START_REDIR || \
                                             LRRC_COMM_GetFlowCtrlFlg() ==LRRC_FLOW_CTRL_TYPE_L2C_REDIR_FAIL || \
                                             LRRC_COMM_GetFlowCtrlFlg() ==LRRC_FLOW_CTRL_TYPE_L2W_START_HO || \
                                             LRRC_COMM_GetFlowCtrlFlg() ==LRRC_FLOW_CTRL_TYPE_L2W_HO_FAIL || \
                                             LRRC_COMM_GetFlowCtrlFlg() ==LRRC_FLOW_CTRL_TYPE_L2W_START_RESEL || \
                                             LRRC_COMM_GetFlowCtrlFlg() ==LRRC_FLOW_CTRL_TYPE_L2W_RESEL_FAIL || \
                                             LRRC_COMM_GetFlowCtrlFlg() ==LRRC_FLOW_CTRL_TYPE_L2G_START_HO || \
                                             LRRC_COMM_GetFlowCtrlFlg() ==LRRC_FLOW_CTRL_TYPE_L2G_HO_FAIL || \
                                             LRRC_COMM_GetFlowCtrlFlg() ==LRRC_FLOW_CTRL_TYPE_L2G_START_RESEL || \
                                             LRRC_COMM_GetFlowCtrlFlg() ==LRRC_FLOW_CTRL_TYPE_L2G_RESEL_FAIL || \
                                             LRRC_COMM_GetFlowCtrlFlg() ==LRRC_FLOW_CTRL_TYPE_L2G_START_CCO || \
                                             LRRC_COMM_GetFlowCtrlFlg() ==LRRC_FLOW_CTRL_TYPE_L2G_CCO_FAIL || \
                                             LRRC_COMM_GetFlowCtrlFlg() ==LRRC_FLOW_CTRL_TYPE_L2T_START_HO || \
                                             LRRC_COMM_GetFlowCtrlFlg() ==LRRC_FLOW_CTRL_TYPE_L2T_START_RESEL)

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/



/*****************************************************************************
  4 Enum
*****************************************************************************/
/*****************************************************************************
 ö����    : LRRC_LNAS_MSG_ID_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : NAS��RRC����Ϣԭ������
*****************************************************************************/
enum LRRC_LNAS_MSG_ID_ENUM
{
    /* MM����RRC��ԭ�� */
    ID_LRRC_LMM_START_REQ                 = (LMM_LRRC_MSG_HDR + 0x00),   /* _H2ASN_MsgChoice LRRC_LMM_START_REQ_STRU */
    ID_LRRC_LMM_PLMN_SEARCH_REQ           = (LMM_LRRC_MSG_HDR + 0x01),   /* _H2ASN_MsgChoice LRRC_LMM_PLMN_SEARCH_REQ_STRU */
    ID_LRRC_LMM_PLMN_SEARCH_STOP_REQ      = (LMM_LRRC_MSG_HDR + 0x02),   /* _H2ASN_MsgChoice LRRC_LMM_PLMN_SEARCH_STOP_REQ_STRU */
    ID_LRRC_LMM_EQU_PLMN_NOTIFY_REQ       = (LMM_LRRC_MSG_HDR + 0x03),   /* _H2ASN_MsgChoice LRRC_LMM_EQU_PLMN_NOTIFY_REQ_STRU */
    ID_LRRC_LMM_NAS_INFO_CHANGE_REQ       = (LMM_LRRC_MSG_HDR + 0x04),   /* _H2ASN_MsgChoice LRRC_LMM_NAS_INFO_CHANGE_REQ_STRU */
    ID_LRRC_LMM_CELL_SELECTION_CTRL_REQ   = (LMM_LRRC_MSG_HDR + 0x05),   /* _H2ASN_MsgChoice LRRC_LMM_CELL_SELECTION_CTRL_REQ_STRU */
    ID_LRRC_LMM_EST_REQ                   = (LMM_LRRC_MSG_HDR + 0x06),   /* _H2ASN_MsgChoice LRRC_LMM_EST_REQ_STRU */
    ID_LRRC_LMM_REL_REQ                   = (LMM_LRRC_MSG_HDR + 0x07),   /* _H2ASN_MsgChoice LRRC_LMM_REL_REQ_STRU */
    ID_LRRC_LMM_DATA_REQ                  = (LMM_LRRC_MSG_HDR + 0x08),   /* _H2ASN_MsgChoice LRRC_LMM_DATA_REQ_STRU */
    ID_LRRC_LMM_POWER_OFF_REQ             = (LMM_LRRC_MSG_HDR + 0x09),   /* _H2ASN_MsgChoice LRRC_LMM_POWER_OFF_REQ_STRU */
    ID_LRRC_LMM_SUSPEND_RSP               = (LMM_LRRC_MSG_HDR + 0x0a),   /* _H2ASN_MsgChoice LRRC_LMM_SUSPEND_RSP_STRU */
    ID_LRRC_LMM_RESUME_RSP                = (LMM_LRRC_MSG_HDR + 0x0b),   /* _H2ASN_MsgChoice LRRC_LMM_RESUME_RSP_STRU */
    ID_LRRC_LMM_SUSPEND_REQ               = (LMM_LRRC_MSG_HDR + 0x0c),   /* _H2ASN_MsgChoice LRRC_LMM_SUSPEND_REQ_STRU */
    ID_LRRC_LMM_SECU_PARA_RSP             = (LMM_LRRC_MSG_HDR + 0x0d),   /* _H2ASN_MsgChoice LRRC_LMM_SECU_PARA_RSP_STRU */
    ID_LRRC_LMM_SYS_CFG_REQ               = (LMM_LRRC_MSG_HDR + 0x0e),   /* _H2ASN_MsgChoice LRRC_LNAS_SYS_CFG_REQ_STRU */
    ID_LRRC_LMM_MBMS_SESSION_CFG_REQ      = (LMM_LRRC_MSG_HDR + 0x0f),   /* _H2ASN_MsgChoice LRRC_LMM_MBMS_SESSION_CFG_REQ_STRU */
    ID_LRRC_LMM_OOS_STATE_REQ             = (LMM_LRRC_MSG_HDR + 0x10),   /* _H2ASN_MsgChoice LRRC_LMM_OOS_STATE_REQ_STRU */
    ID_LRRC_LMM_CLEAR_BUFF_NOTIFY         = (LMM_LRRC_MSG_HDR + 0x11),   /* _H2ASN_MsgChoice LRRC_LMM_CLEAR_BUFF_NOTIFY_STRU */
    ID_LRRC_LMM_BG_PLMN_SEARCH_REQ        = (LMM_LRRC_MSG_HDR + 0x12),   /* _H2ASN_MsgChoice LRRC_LMM_BG_PLMN_SEARCH_REQ_STRU */
    ID_LRRC_LMM_BG_PLMN_SEARCH_STOP_REQ   = (LMM_LRRC_MSG_HDR + 0x13),   /* _H2ASN_MsgChoice LRRC_LMM_BG_PLMN_SEARCH_REQ_STOP_STRU */
    ID_LRRC_LMM_SUSPEND_REL_REQ           = (LMM_LRRC_MSG_HDR + 0x14),   /* _H2ASN_MsgChoice LRRC_LMM_SUSPEND_REL_REQ_STRU */
    ID_LRRC_LMM_OTHER_MODEM_INFO_NOTIFY   = (LMM_LRRC_MSG_HDR + 0x15),    /* _H2ASN_MsgChoice LMM_LRRC_OTHER_MODEM_INFO_NOTIFY_STRU*/
    ID_LRRC_LMM_BEGIN_SESSION_NOTIFY      = (LMM_LRRC_MSG_HDR + 0x16),    /* _H2ASN_MsgChoice LRRC_LMM_BEGIN_SESSION_NOTIFY_STRU*/
    ID_LRRC_LMM_END_SESSION_NOTIFY        = (LMM_LRRC_MSG_HDR + 0x17),    /* _H2ASN_MsgChoice LRRC_LMM_END_SESSION_NOTIFY_STRU*/
    ID_LMM_LRRC_NETSCAN_REQ               = (LMM_LRRC_MSG_HDR + 0x18),    /* _H2ASN_MsgChoice LRRC_LMM_NETSCAN_REQ_STRU */
    ID_LMM_LRRC_NETSCAN_STOP_REQ          = (LMM_LRRC_MSG_HDR + 0x19),    /* _H2ASN_MsgChoice LRRC_LMM_NETSCAN_STOP_REQ_STRU */
    ID_LRRC_LMM_CELL_SIGN_REPORT_NOTIFY   = (LMM_LRRC_MSG_HDR + 0x1a),    /* _H2ASN_MsgChoice LRRC_LMM_CELL_SIGN_REPORT_NOTIFY_STRU*/
    ID_LRRC_LMM_DETACH_IND                = (LMM_LRRC_MSG_HDR + 0x20),     /* _H2ASN_MsgChoice LRRC_LMM_DETACH_IND_STRU */

    ID_LRRC_LMM_DISABLE_LTE_NOTIFY        = (LMM_LRRC_MSG_HDR + 0x21),     /* _H2ASN_MsgChoice LRRC_LMM_DISABLE_LTE_NOTIFY_STRU*/

    /*LMM���͸�RRC��ָʾ�����������Ż�������Ŀ��*/
    ID_LRRC_LMM_EXPERIENCE_SPEC_REQ       = (LMM_LRRC_MSG_HDR + 0x22),     /* _H2ASN_MsgChoice LRRC_LMM_EXPERIENCE_SPEC_REQ */
    /* ������Ϣ,����֪ͨLRRC CSFB���������Լ�ֹͣ,���CSFB�����ղ�������REL�Ż� */
    ID_LRRC_LMM_CSFB_NOTIFY               = (LMM_LRRC_MSG_HDR + 0x23),     /* _H2ASN_MsgChoice LRRC_LMM_CSFB_NOTIFY_STRU */

    ID_LRRC_LMM_BG_SEARCH_HRPD_REQ        = (LMM_LRRC_MSG_HDR + 0x24),     /* _H2ASN_MsgChoice LRRC_LMM_BG_SEARCH_HRPD_REQ_STRU*/
    ID_LRRC_LMM_BG_SEARCH_HRPD_STOP_REQ   = (LMM_LRRC_MSG_HDR + 0x25),     /* _H2ASN_MsgChoice LRRC_LMM_BG_SEARCH_HRPD_STOP_REQ_STRU*/

    /* RABM����RRC��ԭ�� */
    ID_LRRC_LRABM_QOS_UPDATE_REQ          = (LRABM_LRRC_MSG_HDR + 0x0a),   /* _H2ASN_MsgChoice LRRC_LRABM_QOS_UPDATE_REQ_STRU */
    ID_LRRC_LRABM_RAB_RSP                 = (LRABM_LRRC_MSG_HDR + 0x0b),   /* _H2ASN_MsgChoice LRRC_LRABM_RAB_RSP_STRU */
    ID_LRRC_LRABM_STATUS_RSP              = (LRABM_LRRC_MSG_HDR + 0x0c),   /* _H2ASN_MsgChoice LRRC_LRABM_STATUS_RSP_STRU */

    /* RRC����MM��ԭ�� */
    ID_LRRC_LMM_START_CNF                 = (LRRC_LMM_MSG_HDR + 0x00),     /* _H2ASN_MsgChoice LRRC_LMM_START_CNF_STRU */
    ID_LRRC_LMM_PLMN_SEARCH_CNF           = (LRRC_LMM_MSG_HDR + 0x01),     /* _H2ASN_MsgChoice LRRC_LMM_PLMN_SEARCH_CNF_STRU */
    ID_LRRC_LMM_PLMN_SEARCH_STOP_CNF      = (LRRC_LMM_MSG_HDR + 0x02),     /* _H2ASN_MsgChoice LRRC_LMM_PLMN_SEARCH_STOP_CNF_STRU */
    ID_LRRC_LMM_EST_CNF                   = (LRRC_LMM_MSG_HDR + 0x03),     /* _H2ASN_MsgChoice LRRC_LMM_EST_CNF_STRU */
    ID_LRRC_LMM_REL_CNF                   = (LRRC_LMM_MSG_HDR + 0x04),     /* _H2ASN_MsgChoice LRRC_LMM_REL_CNF_STRU */
    ID_LRRC_LMM_REL_IND                   = (LRRC_LMM_MSG_HDR + 0x05),     /* _H2ASN_MsgChoice LRRC_LMM_REL_IND_STRU */
    ID_LRRC_LMM_ERR_IND                   = (LRRC_LMM_MSG_HDR + 0x06),     /* _H2ASN_MsgChoice LRRC_LMM_ERR_IND_STRU */
    ID_LRRC_LMM_AREA_LOST_IND             = (LRRC_LMM_MSG_HDR + 0x07),     /* _H2ASN_MsgChoice LRRC_LMM_AREA_LOST_IND_STRU */
    ID_LRRC_LMM_SYS_INFO_IND              = (LRRC_LMM_MSG_HDR + 0x08),     /* _H2ASN_MsgChoice LRRC_LMM_SYS_INFO_IND_STRU */
    ID_LRRC_LMM_PAGING_IND                = (LRRC_LMM_MSG_HDR + 0x09),     /* _H2ASN_MsgChoice LRRC_LMM_PAGING_IND_STRU */
    ID_LRRC_LMM_DATA_IND                  = (LRRC_LMM_MSG_HDR + 0x0a),     /* _H2ASN_MsgChoice LRRC_LMM_DATA_IND_STRU */
    ID_LRRC_LMM_SECURITY_IND              = (LRRC_LMM_MSG_HDR + 0x0b),     /* _H2ASN_MsgChoice LRRC_LMM_SECURITY_IND_STRU */
    ID_LRRC_LMM_POWER_OFF_CNF             = (LRRC_LMM_MSG_HDR + 0x0c),     /* _H2ASN_MsgChoice LRRC_LMM_POWER_OFF_CNF_STRU */
    ID_LRRC_LMM_ACCESS_GRANT_IND          = (LRRC_LMM_MSG_HDR + 0x0d),     /* _H2ASN_MsgChoice LRRC_LMM_ACCESS_GRANT_IND_STRU */
    ID_LRRC_LMM_DATA_CNF                  = (LRRC_LMM_MSG_HDR + 0x0e),     /* _H2ASN_MsgChoice LRRC_LMM_DATA_CNF_STRU */
    ID_LRRC_LMM_SUSPEND_IND               = (LRRC_LMM_MSG_HDR + 0x0f),     /* _H2ASN_MsgChoice LRRC_LMM_SUSPEND_IND_STRU */
    ID_LRRC_LMM_RESUME_IND                = (LRRC_LMM_MSG_HDR + 0x10),     /* _H2ASN_MsgChoice LRRC_LMM_RESUME_IND_STRU */
    ID_LRRC_LMM_SUSPEND_CNF               = (LRRC_LMM_MSG_HDR + 0x11),     /* _H2ASN_MsgChoice LRRC_LMM_SUSPEND_CNF_STRU */
    ID_LRRC_LMM_SECU_PARA_IND             = (LRRC_LMM_MSG_HDR + 0x12),     /* _H2ASN_MsgChoice LRRC_LMM_SECU_PARA_IND_STRU */
    ID_LRRC_LMM_SYS_CFG_CNF               = (LRRC_LMM_MSG_HDR + 0x13),     /* _H2ASN_MsgChoice LRRC_LNAS_SYS_CFG_CNF_STRU */
    ID_LRRC_LMM_MBMS_SESSION_CFG_CNF      = (LRRC_LMM_MSG_HDR + 0x14),     /* _H2ASN_MsgChoice LRRC_LMM_MBMS_SESSION_CFG_CNF_STRU */
    ID_LRRC_LMM_MBMS_SESSION_IND          = (LRRC_LMM_MSG_HDR + 0x15),     /* _H2ASN_MsgChoice LRRC_LMM_MBMS_SESSION_IND_STRU */
    ID_LRRC_LMM_BG_PLMN_SEARCH_CNF        = (LRRC_LMM_MSG_HDR + 0x16),     /* _H2ASN_MsgChoice LRRC_LMM_BG_PLMN_SEARCH_CNF_STRU */
    ID_LRRC_LMM_BG_PLMN_SEARCH_STOP_CNF   = (LRRC_LMM_MSG_HDR + 0x17),     /* _H2ASN_MsgChoice LRRC_LMM_BG_PLMN_SEARCH_STOP_CNF_STRU */
    ID_LRRC_LMM_NOT_CAMP_ON_IND           = (LRRC_LMM_MSG_HDR + 0x18),     /* _H2ASN_MsgChoice LRRC_LNAS_NOT_CAMP_ON_IND_STRU */
    ID_LRRC_LMM_UTRAN_MODE_REQ            = (LRRC_LMM_MSG_HDR + 0x19),     /* _H2ASN_MsgChoice LRRC_LMM_UTRAN_MODE_REQ_STRU */
    ID_LRRC_LMM_SUSPEND_REL_CNF           = (LRRC_LMM_MSG_HDR + 0x1b),     /* _H2ASN_MsgChoice LRRC_LMM_SUSPEND_REL_CNF_STRU */
    ID_LRRC_LMM_UTRAN_MODE_CNF            = (LRRC_LMM_MSG_HDR + 0x20),     /* _H2ASN_MsgChoice LRRC_LMM_UTRAN_MODE_CNF_STRU */
    ID_LRRC_LMM_SUSPEND_INFO_CHANGE_IND   = (LRRC_LMM_MSG_HDR + 0x21),     /* _H2ASN_MsgChoice LRRC_LMM_SUSPEND_INFO_CHANGE_IND_STRU */
    ID_LRRC_LMM_NETSCAN_CNF               = (LRRC_LMM_MSG_HDR + 0x22),     /* _H2ASN_MsgChoice LRRC_LMM_NETSCAN_CNF_STRU */
    ID_LRRC_LMM_NETSCAN_STOP_CNF          = (LRRC_LMM_MSG_HDR + 0x23),     /* _H2ASN_MsgChoice LRRC_LMM_NETSCAN_STOP_CNF_STRU */
    ID_LRRC_LMM_CELL_SIGN_REPORT_IND      = (LRRC_LMM_MSG_HDR + 0x24),     /* _H2ASN_MsgChoice LRRC_LMM_CELL_SIGN_REPORT_IND_STRU */
    ID_LRRC_LMM_SEARCHED_PLMN_INFO_IND    = (LRRC_LMM_MSG_HDR + 0x25),     /* _H2ASN_MsgChoice LRRC_LMM_SEARCHED_PLMN_INFO_IND_STRU */
    ID_LRRC_LMM_INTER_OPT_IND             = (LRRC_LMM_MSG_HDR + 0x26),     /* _H2ASN_MsgChoice LRRC_LMM_INTER_OPT_IND */

    /* RRC����RABM��ԭ�� */
    ID_LRRC_LRABM_RAB_IND                 = (LRRC_LRABM_MSG_HDR + 0x0d),   /* _H2ASN_MsgChoice LRRC_LRABM_RAB_IND_STRU */
    ID_LRRC_LRABM_STATUS_IND              = (LRRC_LRABM_MSG_HDR + 0x0e),   /* _H2ASN_MsgChoice LRRC_LRABM_STATUS_IND_STRU */
    ID_LRRC_LMM_BG_SEARCH_HRPD_CNF        = (LRRC_LMM_MSG_HDR + 0x27),   /* _H2ASN_MsgChoice LRRC_LMM_BG_SEARCH_HRPD_CNF_STRU */
    ID_LRRC_LMM_BG_SEARCH_HRPD_STOP_CNF   = (LRRC_LMM_MSG_HDR + 0x28),   /* _H2ASN_MsgChoice LRRC_LMM_BG_SEARCH_HRPD_STOP_CNF_STRU */

    ID_LRRC_LNAS_MSG_ID_BUTT
};
typedef VOS_UINT32   LRRC_LNAS_MSG_ID_ENUM_UINT32;

/*****************************************************************************
 ö����    : LRRC_LNAS_ATTACH_STATUS_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : NAS_INFO_STRU enAttachȡֵ
*****************************************************************************/
enum LRRC_LNAS_ATTACH_STATUS_ENUM
{
    LRRC_LNAS_ATTACH                      = 0,
    LRRC_LNAS_NOT_ATTACH                  = 1,
    LRRC_LNAS_ATTACH_STATUS_BUTT
};
typedef VOS_UINT32 LRRC_LNAS_ATTACH_STATUS_ENUM_UINT32;

/*****************************************************************************
 ö����    : LRRC_LNAS_SIM_STATUS_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ��״̬ȡֵ
*****************************************************************************/
enum LRRC_LNAS_SIM_STATUS_ENUM
{
    LRRC_LNAS_USIM_ABSENT                 = 0,                /* �������� */
    LRRC_LNAS_USIM_PRESENT                = 1,                /* ������,������Ϊ USIM �� */
    LRRC_LNAS_USIM_PRESENT_INVALID        = 2,                /* ������,������Ч,������Ϊ USIM �� */
    LRRC_LNAS_USIM_STATUS_BUTT
};
typedef VOS_UINT32  LRRC_LNAS_SIM_STATUS_ENUM_UINT32;


/*****************************************************************************
 ö����    : LRRC_LNAS_START_RESULT_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : NAS��RRC֮��ԭ��ִ�н��ȡֵ
*****************************************************************************/
enum LRRC_LNAS_START_RESULT_ENUM
{
    LRRC_LNAS_START_SUCCESS               = 0,
    LRRC_LNAS_START_FAILURE               = 1,
    LRRC_LNAS_START_BUTT
};
typedef VOS_UINT32 LRRC_LNAS_START_RESULT_ENUM_UINT32;

/*****************************************************************************
 ö����    : LRRC_LNAS_PLMN_SEARCH_TYPE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : PLMN��������ȡֵ
*****************************************************************************/
enum LRRC_LNAS_PLMN_SEARCH_TYPE_ENUM
{
    LRRC_LNAS_PLMN_SEARCH_SPEC            = 0,                /* ָ����PLMN������ */
    /* lishangfeng bg begin */
    LRRC_LNAS_PLMN_SEARCH_FAST_SPEC       = 1,                /* ����ָ����PLMN������ */
    LRRC_LNAS_PLMN_SEARCH_LIST            = 2,                /* PLMN�б������   */
    LRRC_LNAS_PLMN_SEARCH_ANY             = 3,                /* any cell ���� */
    /* lishangfeng bg end*/
    /* ncell spec search begin */
    LRRC_LNAS_PLMN_SEARCH_NCELL_SPEC      = 4,
    /* ncell spec search end */
    LRRC_LNAS_PLMN_SRCH_HISTORY             = 5,                /* ��ʷ��Ϣ���� */
    LRRC_LNAS_PLMN_GET_GEO                  = 6,                /* ��ȡ����λ����Ϣ */
    LRRC_LNAS_PLMN_SEARCH_TYPE_BUTT
};
typedef VOS_UINT32 LRRC_LNAS_PLMN_SEARCH_TYPE_ENUM_UINT32;
/*****************************************************************************
 ö����    : LRRC_LNAS_FFT_SCAN_TYPE_ENUM_UINT8
 Э����  :
 ASN.1���� :
 ö��˵��  : PLMN�������ȡֵ
*****************************************************************************/
enum LRRC_LNAS_FFT_SCAN_TYPE_ENUM
{
    LRRC_LNAS_FFT_SCAN_TYPE_NONE     = 0,                 /* ����COMM SRCH��ȡFFTɨƵ֮���Ƶ�� */
    LRRC_LNAS_FFT_SCAN_TYPE_LOW      = 1,                 /* ��COMM SRCH��ȡFFTɨƵ֮�������פ�����޵�Ƶ�� */
    LRRC_LNAS_FFT_SCAN_TYPE_HIGH     = 2,                 /* ��COMM SRCH��ȡFFTɨƵ֮��������������޵�Ƶ�� */
    LRRC_LNAS_FFT_SCAN_TYPE_BUTT
};
typedef VOS_UINT8  LRRC_LNAS_FFT_SCAN_TYPE_ENUM_UINT8;

/*****************************************************************************
 ö����    : LRRC_LNAS_PLMN_SEARCH_RLT_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : PLMN�������ȡֵ
*****************************************************************************/
enum LRRC_LNAS_PLMN_SEARCH_RLT_ENUM
{
    LRRC_LNAS_PLMN_SEARCH_RLT_SPEC_SUCC   = 0,                /* ָ����PLMN ID �����ɹ� */
    LRRC_LNAS_PLMN_SEARCH_RLT_LIST_SUCC   = 1,                /* PLMN List�����ɹ�      */
    LRRC_LNAS_PLMN_SEARCH_RLT_SPEC_FAIL   = 2,                /* ָ��PLMN ID����ʧ��    */
    LRRC_LNAS_PLMN_SEARCH_RLT_LIST_FAIL   = 3,                /* PLMN List����ʧ��      */
/* lishangfeng bg begin */
    LRRC_LNAS_PLMN_SRCH_RLT_LIST_REJ      = 4,                /* פ��̬���б��������ǳ����������̴�� */
/* lishangfeng bg end */

    LRRC_LNAS_PLMN_SEARCH_RLT_SPEC_NO_RF   = 5,/* ���� */
    LRRC_LNAS_PLMN_SEARCH_RLT_LIST_NO_RF   = 6,/* ���� */

    LRRC_LNAS_PLMN_SRCH_RLT_HISTORY_FAIL    = 7,
    LRRC_LNAS_PLMN_SRCH_RLT_HISTORY_SUCC    = 8,
    LRRC_LNAS_PLMN_SRCH_RLT_HISTORY_NO_RF   = 9,
    LRRC_LNAS_PLMN_SRCH_RLT_GET_GEO_FAIL    = 10,
    LRRC_LNAS_PLMN_SRCH_RLT_GET_GEO_SUCC    = 11,
    LRRC_LNAS_PLMN_SRCH_RLT_GET_GEO_NO_RF   = 12,

    LRRC_LNAS_PLMN_SEARCH_RLT_BUTT
};
typedef VOS_UINT32  LRRC_LNAS_PLMN_SEARCH_RLT_ENUM_UINT32;

/*****************************************************************************
 ö����    : LRRC_LNAS_RAT_TYPE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ���뼼����ȡֵ
*****************************************************************************/
enum LRRC_LNAS_MSG_WAIT_TYPE_ENUM
{
    LRRC_LNAS_MSG_WAIT_ERR                = 0,                /*�������ó���*/
    LRRC_LNAS_MSG_NO_WAIT,                                    /*RRC����Ҫ�ȴ�NAS����Ӧ��Ϣ*/
    LRRC_LNAS_MSG_WAIT,                                       /*RRC��Ҫ�ȴ�NAS����Ӧ��Ϣ  */
    LRRC_LNAS_MSG_BUTT
};
typedef VOS_UINT32  LRRC_LNAS_MSG_WAIT_TYPE_ENUM_UINT32;

/*****************************************************************************
 ö����    : LRRC_LNAS_INFO_TYPE_ENUM_UINT32
 Э����  :
 ASN.1���� :
 ö��˵��  : NAS��Ϣö������
*****************************************************************************/
enum LRRC_LNAS_INFO_TYPE_ENUM
{
    LRRC_LNAS_INFO_TYPE_UEID              = 0,                /*����ģ���ȡUEID,Ŀǰֻ��IMSI*/
    LRRC_LNAS_INFO_TYPE_DRX,
    LRRC_LNAS_INFO_TYPE_AC,
    LRRC_LNAS_INFO_TYPE_PLMNID,
    LRRC_LNAS_INFO_TYPE_HO_PRIO_SELECT_PLMNID,
    LRRC_LNAS_INFO_TYPE_RPLMN,
    LRRC_LNAS_INFO_TYPE_GU_PLMN,

    LRRC_LNAS_INFO_TYPE_BUTT
};
typedef VOS_UINT32 LRRC_LNAS_INFO_TYPE_ENUM_UINT32;

/*****************************************************************************
 ö����    : LRRC_LNAS_RESEL_TYPE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : С������ԭ��ö������
*****************************************************************************/
enum LRRC_LNAS_RESEL_TYPE_ENUM
{
    LRRC_LNAS_CELL_SELECTION              = 0,
    LRRC_LNAS_RESEL_SUITABLE              = 1,
    LRRC_LNAS_FORBLA_CHANGE               = 2,
    LRRC_LNAS_RESEL_ACCEPTABLE            = 3,
    LRRC_LNAS_FORBTA_CHANGE               = 4,
    LRRC_LNAS_RESEL_BUTT
};
typedef VOS_UINT32  LRRC_LNAS_RESEL_TYPE_ENUM_UINT32;

/*****************************************************************************
 ö����    : LRRC_LNAS_EST_RESULT_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : �������ӽ��ö������
*****************************************************************************/
enum LRRC_LNAS_EST_RESULT_ENUM
{
    LRRC_EST_SUCCESS                         = 0,                                /* �������ӽ����ɹ�                     */
    LRRC_EST_PRESENT                         = 1,                                /* �����������Ѿ�����                   */
    LRRC_EST_ESTING                          = 2,                                /* �������������ڽ���                   */
    LRRC_EST_DELING                          = 3,                                /* ���������������ͷ�                   */
    LRRC_EST_ACCESS_BARRED_MO_CALL           = 4,                                /* access barred when MO Call  */
    LRRC_EST_ACCESS_BARRED_MO_SIGNAL         = 5,                                /* access barred When MO SIGNAL  */
    LRRC_EST_ACCESS_BARRED_EMERGENCY_CALL    = 6,                                /* access barred When Emergency Call  */
    LRRC_EST_ACCESS_BARRED_ALL               = 7,                                /* access barred When Rrc Con Rej */
    LRRC_EST_EST_CONN_FAIL                   = 8,                                /* RR connection establish failure      */
    LRRC_EST_RJ_INTER_RAT                    = 9,                                /* RR connection Reject: ָʾ������ϵͳ */
    LRRC_EST_IMMEDIATE_ASSIGN_REJECT         = 10,                               /* �����Ľ�����̣�����RA������յ�����ָ�ɾܾ���Ϣ��
                                                                                û���յ�����ָ����Ϣ�����µĽ���ʧ�� */
    LRRC_EST_RANDOM_ACCESS_REJECT            = 11,                               /* �����Ľ�����̣�����RA�����û���յ�����������ָ�ɣ�
                                                                                Ҳû���յ�����ָ�ɾܾ�������ʧ�� */
    LRRC_EST_CELL_SEARCHING                  = 12,                               /* RRCĿǰ���ܴ���������NAS�յ���ԭ��ֵ��
                                                                                   ֱ���յ�RRC_MM_SYS_INFO_IND�ٷ�����*/

    /* v7r2 lld begin */
    LRRC_EST_ACCESS_BARRED_MT_CALL           = 13,                              /* access barred when MT Call  */
    LRRC_EST_ACCESS_BARRED_MO_CSFB           = 14,                              /* access barred when MO CSFB  */
    LRRC_EST_ACCESS_BARRED_MO_CALL_AND_CSFB  = 15,                              /* access barred when MO Call AND MO CSFB  */
    /* v7r2 lld end */

    LRRC_EST_NO_RF                           = 16, /* DSDS NORF */

    LRRC_EST_RESULT_BUTT
};
typedef VOS_UINT32 LRRC_LNAS_EST_RESULT_ENUM_UINT32;

/*****************************************************************************
 ö����    : LRRC_LNAS_EST_CAUSE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : RRMM_EST_REQ_STRU��Ϣ�е�enEstCause
              emergency, highPriorityAccess, mt-Access, mo-Signalling, mo-Data,delayTolerantAccess-v1020 ,
*****************************************************************************/
enum LRRC_LNAS_EST_CAUSE_ENUM
{
    LRRC_LNAS_EST_CAUSE_EMERGENCY_CALL          = 0,
    LRRC_LNAS_EST_CAUSE_HIGH_PRIORITY_ACCESS,
    LRRC_LNAS_EST_CAUSE_MT_ACCESS,
    LRRC_LNAS_EST_CAUSE_MO_SIGNALLING,
    LRRC_LNAS_EST_CAUSE_MO_DATA,
    /* v7r2 lld begin */
    LRRC_LNAS_EST_CAUSE_DELAYTOLERANT_ACCESS,
    /* v7r2 lld end */
    LRRC_LNAS_EST_CAUSE_BUTT
};
typedef VOS_UINT32 LRRC_LNAS_EST_CAUSE_ENUM_UINT32;

/*****************************************************************************
 ö����    : LRRC_LNAS_REL_CAUSE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : NASɾ��RRC��ԭ��ֵö������
*****************************************************************************/
enum LRRC_LNAS_REL_CAUSE_ENUM
{
    /* RRC Connection Release��Ϣ�е�ԭ�� */
    LRRC_LNAS_REL_CAUSE_CONN_FAIL                  = 0,  /* RR Connection Failure                             */
    LRRC_LNAS_REL_CAUSE_LOAD_BALANCE_REQ           = 1,  /* Rrc Con Release ���е�ԭ��Ϊ
                                                          loadBalancingTAUrequired                          */
    LRRC_LNAS_REL_CAUSE_OTHER_REASON               = 2,  /* Rrc Con Release ���е�ԭ����
                                                          loadBalancingTAUrequired����������·ʧ���ͷ�ԭ��  */
    LRRC_LNAS_REL_CAUSE_NAS_DATA_ABSENT            = 3,  /* NAS Data Request: Connection Absent               */
/*    RRC_NAS_REL_CAUSE_MSG_TRANS_FAIL             = 4,*/  /* Rrc ����Nas��Ϣʧ��*/
    LRRC_LNAS_REL_CAUSE_RRC_ABNORMAL               = 4,  /* RRC��ײ�ϵͳ�쳣�ͷ�ԭ��                         */

    LRRC_LNAS_REL_CAUSE_GU2L_HO_ERR,                    /* GU��L�л�ʧ�� */

    LRRC_LNAS_REL_CAUSE_L2GU_REDIRECT,                  /* ��ϵͳ�ض��� */

    /* v7r2 code begin */
    LRRC_LNAS_REL_CAUSE_CSFB_HIGH_PRIOR,                /* Rrc Con Release ���е�ԭ�� cs-FallbackHighPriority */
    /* v7r2 code end */

    LRRC_LNAS_REL_CAUSE_NO_RF,  /* ����ԭ�� */

    LRRC_LNAS_REL_CAUSE_BUTT
};
typedef VOS_UINT32 LRRC_LNAS_REL_CAUSE_ENUM_UINT32;

/*****************************************************************************
 ö����    : LRRC_LNAS_ERR_CAUSE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : RRC��NAS��������ö������
*****************************************************************************/
enum LRRC_LNAS_ERR_CAUSE_ENUM
{
    LRRC_LNAS_ERR_NORMAL                      = 0,
    LRRC_LNAS_ERR_CAUSE_BUTT
};
typedef VOS_UINT32 LRRC_LNAS_ERR_CAUSE_ENUM_UINT32;

/*****************************************************************************
 ö����    : LRRC_LNAS_AREA_LOST_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : RRMM_AREA_LOST_IND_STRU��Ϣ�е�enRptMode
*****************************************************************************/
enum LRRC_LNAS_AREA_LOST_ENUM
{
    LRRC_LNAS_SERVICE_AREA_LOST           = 0,                /* ��������ʧ,LTE��ʱ���� */
    LRRC_LNAS_COVERAGE_AREA_LOST          = 1,                /* ��������ʧ */
    LRRC_LNAS_RADIO_RESOURCE_AREA_LOST    = 2,   /*��Ƶ��Դ������*/
    LRRC_LNAS_AREA_LOST_BUTT
};
typedef VOS_UINT32  LRRC_LNAS_AREA_LOST_ENUM_UINT32;

/*****************************************************************************
 ö����    : LRRC_LNAS_PAGING_TYPE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : RRMM_PAGING_IND_STRU enPagingTypeȡֵ
*****************************************************************************/
enum LRRC_LNAS_PAGING_TYPE_ENUM
{
    LRRC_LNAS_PAGING_TYPE1                = 0,                /* Paging Type 1 */
    LRRC_LNAS_PAGING_TYPE2                = 1,                /* Paging Type 2 */
    LRRC_LNAS_PAGING_TYPE_BUTT
};
typedef VOS_UINT32 LRRC_LNAS_PAGING_TYPE_ENUM_UINT32;

/*****************************************************************************
 ö����    : LRRC_LNAS_PAGING_CAUSE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : LRRC_LNAS_PAGING_CAUSE_ENUM enPagingCauseȡֵ
*****************************************************************************/
enum LRRC_LNAS_PAGING_CAUSE_ENUM
{
    LRRC_LNAS_PAGING_CAUSE_TERMINAT_CONVERSAT_CALL          = 0,
    LRRC_LNAS_PAGING_CAUSE_TERMINAT_STREAM_CALL             = 1,
    LRRC_LNAS_PAGING_CAUSE_TERMINAT_INTERACT_CALL           = 2,
    LRRC_LNAS_PAGING_CAUSE_TERMINAT_BACKGROUND_CALL         = 3,
    LRRC_LNAS_PAGING_CAUSE_TERMINAT_HIGH_PRIORITY_SIGNAL    = 4,
    LRRC_LNAS_PAGING_CAUSE_TERMINAT_LOW_PRIORITY_SIGNAL     = 5,
    LRRC_LNAS_PAGING_CAUSE_TERMINAT_CAUSE_UNKNOWN           = 6,

    LRRC_LNAS_PAGING_CAUSE_BUTT
};
typedef VOS_UINT32 LRRC_LNAS_PAGING_CAUSE_ENUM_UINT32;

/*****************************************************************************
 ö����    : LRRC_LNAS_PAGING_UE_ID_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : LRRC_LNAS_PAGING_UE_ID_ENUM enPagingUeIdȡֵ
*****************************************************************************/
enum LRRC_LNAS_PAGING_UE_ID_ENUM
{
    LRRC_LNAS_IMSI_GSM_MAP                = 0,                /* used for Paging Type 1/2 */
    LRRC_LNAS_TMSI_GSM_MAP_P_TMSI         = 1,                /* used for Paging Type 1   */
    LRRC_LNAS_IMSI_DS41                   = 2,                /* used for Paging Type 1/2 */
    LRRC_LNAS_TMSI_DS41                   = 3,                /* used for Paging Type 1/2 */
    LRRC_LNAS_P_TMSI_GSM_MAP              = 4,                /* used for Paging Type 1   */
    LRRC_LNAS_IMSI_LTE,
    LRRC_LNAS_S_TMSI_LTE,

    LRRC_PAGE_UE_ID_BUTT
};
typedef VOS_UINT32 LRRC_LNAS_PAGING_UE_ID_ENUM_UINT32;

/*****************************************************************************
 ö����    : LRRC_LNAS_SECURITY_RPT_MODE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : LRRC_LNAS_SECURITY_RPT_MODE_ENUM enRptModeȡֵ
*****************************************************************************/
enum LRRC_LNAS_SECURITY_RPT_MODE_ENUM
{
    LRRC_LNAS_SECURITY_CS_SMC_CMPL        = 0,                /* һ��CS SMC���̽���                       */
    LRRC_LNAS_SECURITY_DEL_CS_KEY         = 1,                /* USIM��CS��CK��IK��ɾ��                   */
    LRRC_LNAS_SECURITY_DEL_PS_KEY         = 2,                /* USIM��PS��CK��IK��ɾ��                   */
    LRRC_LNAS_SECURITY_DEL_CS_PS_KEY      = 3,                /* USIM��CS+PS��CK��IK��ɾ��                */
    LRRC_LNAS_SECURITY_CS_SMC_RCV         = 4,                /* �յ���Ч��CS SMC��Ϣ                     */
    LRRC_LNAS_SECURITY_PS_SMC_RCV         = 5,                /* �յ���Ч��PS SMC��Ϣ                     */
    LRRC_LNAS_SECURITY_PS_SMC_CMPL        = 6,                /* һ��PS SMC���̽���                       */
    LRRC_LNAS_SECURITY_RB_CTRL_MSG        = 7,                /* �յ�������Ϣ�޸ļ����㷨                 */
    LRRC_LNAS_SECURITY_MOBI_MSG           = 8,                /* �յ�CELL/URA UPDATE CNF��Ϣ�޸ļ����㷨  */
    LRRC_LNAS_SECURITY_RPT_MODE_BUTT
};
typedef VOS_UINT32 LRRC_LNAS_SECURITY_RPT_MODE_ENUM_UINT32;

/*****************************************************************************
 ö����    : LRRC_LNAS_RAB_STATUS_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : LRRC_LNAS_RAB_STATUS_ENUM enStatusȡֵ
*****************************************************************************/
enum LRRC_LNAS_RAB_STATUS_ENUM
{
    LRRC_LNAS_RAB_STATUS_STOP             = 0,                /* ֹͣ���ݴ��� */
    LRRC_LNAS_RAB_STATUS_CONTINUE         = 1,                /* �ָ����ݴ��� */
    LRRC_LNAS_RAB_STATUS_BUTT
};
typedef VOS_UINT32 LRRC_LNAS_RAB_STATUS_ENUM_UINT32;

/*****************************************************************************
 ö����    : LRRC_LNAS_RAB_CHANGE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : RAB����������
*****************************************************************************/
enum LRRC_LNAS_RAB_CHANGE_ENUM
{
    LRRC_LNAS_RAB_SETUP_REQUEST           = 0,                /* �������µ�RAB   */
    LRRC_LNAS_RAB_SETUP_SUCCESS           = 1,                /* �ɹ������µ�RAB   */
    LRRC_LNAS_RAB_SETUP_FAILURE           = 2,                /* �����µ�RABʧ��   */
    LRRC_LNAS_RAB_RECONFIG                = 3,                /* �����Ѿ�������RAB */
    LRRC_LNAS_RAB_RELEASE                 = 4,                /* �ͷ��Ѿ�������RAB */
    LRRC_LNAS_RAB_CHANGE_BUTT
};
typedef VOS_UINT32 LRRC_LNAS_RAB_CHANGE_ENUM_UINT32;

/*****************************************************************************
 ö����    : LRRC_LNAS_CELL_STATUS_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : С��פ��״̬,RRC֪ͨMM��ǰפ��С����AnyCell״̬����Normal״̬
*****************************************************************************/
enum LRRC_LNAS_CELL_STATUS_ENUM
{
    LRRC_LNAS_CELL_STATUS_NORMAL          = 0,                                    /* ����פ��    */
    LRRC_LNAS_CELL_STATUS_ANYCELL         = 1,                                    /* AnyCellפ�� */
    LRRC_LNAS_CELL_STATUS_BUTT
};
typedef VOS_UINT32 LRRC_LNAS_CELL_STATUS_ENUM_UINT32;

/*****************************************************************************
 ö����    : LRRC_LNAS_ACCESS_GRANT_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : RRC֪ͨnas��ǰ��access Bar alleviation
*****************************************************************************/
enum LRRC_LNAS_ACCESS_GRANT_ENUM
{
    LRRC_LNAS_ACCESS_GRANT_MT              = 0,                                   /* ���Խ���MT */
    LRRC_LNAS_ACCESS_GRANT_MO_CALL         = 1,                                   /* ���Խ���MO Call */
    LRRC_LNAS_ACCESS_GRANT_MO_SIGNAL       = 2,                                   /* ���Խ���MO Signalling */
    LRRC_LNAS_ACCESS_GRANT_MO_CALL_AND_MT  = 3,                                   /* ���Խ���MO Call�� MT */
    LRRC_LNAS_ACCESS_GRANT_MO_SIGNAL_AND_MT= 4,                                   /* ���Խ���MO Signalling �� MT */
    LRRC_LNAS_ACCESS_GRANT_ALL             = 5,                                   /* �����Խ��� */
    /* v7r2 code begin */
    LRRC_LNAS_ACCESS_GRANT_MO_CALL_AND_MO_SIGNAL,
    LRRC_LNAS_ACCESS_GRANT_MO_CALL_AND_MO_SIGNAL_AND_MT,
    LRRC_LNAS_ACCESS_GRANT_MO_CSFB,
    LRRC_LNAS_ACCESS_GRANT_MO_CALL_AND_MO_CSFB,
    LRRC_LNAS_ACCESS_GRANT_MO_SIGNAL_AND_MO_CSFB,
    LRRC_LNAS_ACCESS_GRANT_MO_CALL_AND_MO_SIGNAL_AND_MO_CSFB,
    LRRC_LNAS_ACCESS_GRANT_MO_CSFB_AND_MT,
    LRRC_LNAS_ACCESS_GRANT_MO_CALL_AND_MO_CSFB_AND_MT,
    LRRC_LNAS_ACCESS_GRANT_MO_SIGNAL_AND_MO_CSFB_AND_MT,/* = 14 */
    /* v7r2 code end */
    LRRC_LNAS_ACCESS_GRANT_BUTT
 };
typedef VOS_UINT32 LRRC_LNAS_ACCESS_GRANT_ENUM_UINT32;

/*****************************************************************************
 ö����    : LRRC_LMM_BARRED_IND_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : nas�ڷ����ͷ�����ʱ,ָʾ��ǰʹ�õ�С���Ƿ�bar
*****************************************************************************/
enum LRRC_LMM_BARRED_IND_ENUM
{
    LRRC_LMM_NOT_BARRED                   = 0,                                    /* ԭС��û�б�barred */
    LRRC_LMM_BARRED                       = 1,                                    /* ԭС����barred */
    LRRC_LNAS_BARRED_IND_BUTT
};
typedef VOS_UINT32 LRRC_LMM_BARRED_IND_ENUM_UINT32;

/*****************************************************************************
 ö����    : LRRC_LNAS_STATUS_RESULT_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : RAB������RSP��Ϣ�Ľ��
*****************************************************************************/
enum LRRC_LNAS_STATUS_RESULT_ENUM
{
    LRRC_LNAS_STATUS_SUCC                 = 0,
    LRRC_LNAS_STATUS_FAIL                    ,
    LRRC_LNAS_STATUS_BUTT
};
typedef VOS_UINT32 LRRC_LNAS_STATUS_RESULT_ENUM_UINT32;

/*****************************************************************************
 ö����    : LRRC_LNAS_RESULT_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : RAB������RSP��Ϣ�Ľ��
*****************************************************************************/
enum LRRC_LNAS_RESULT_ENUM
{
    LRRC_LNAS_SUCC                      = 0,
    LRRC_LNAS_FAIL                    ,
    LRRC_LNAS_BUTT
};
typedef VOS_UINT32 LRRC_LNAS_RESULT_ENUM_UINT32;

/*****************************************************************************
 ö����    : LRRC_LNAS_SMC_CTRL_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : NAS��ȫ��������״̬
*****************************************************************************/
enum LRRC_LNAS_SMC_CTRL_ENUM
{
    LRRC_LNAS_SMC_OPEN                        = 0,
    LRRC_LNAS_SMC_CLOSE                          ,
    LRRC_LNAS_SMC_CTRL_BUTT
};
typedef VOS_UINT8 LRRC_LNAS_SMC_CTRL_ENUM_UINT8;

/*****************************************************************************
 ö����    : LRRC_LMM_DATA_CNF_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : MMֱ����Ϣȷ������
*****************************************************************************/
enum LRRC_LMM_DATA_CNF_ENUM
{
    LRRC_LMM_DATA_CNF_NOT_NEED       = 0,
    LRRC_LMM_DATA_CNF_NEED              ,
    LRRC_LMM_DATA_CNF_BUTT
};
typedef VOS_UINT32 LRRC_LMM_DATA_CNF_ENUM_UINT32;

/*****************************************************************************
 ö����    : RRC_MM_DATA_CNF_RSLT_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : MMֱ����Ϣȷ�Ͻ��
*****************************************************************************/
enum LRRC_LMM_SEND_RSLT_ENUM
{
    LRRC_LMM_SEND_RSLT_SUCCESS    = 0,
    LRRC_LMM_SEND_RSLT_FAILURE_HO          ,
    LRRC_LMM_SEND_RSLT_FAILURE_CONN_REL,
    LRRC_LMM_SEND_RSLT_FAILURE_CTRL_NOT_CONN,
    LRRC_LMM_SEND_RSLT_FAILURE_TXN,
    LRRC_LMM_SEND_RSLT_FAILURE_RLF,
    LRRC_LMM_SEND_RSLT_NO_RF,
    LRRC_LMM_SEND_RSLT_BUTT
};
typedef VOS_UINT32 LRRC_LMM_SEND_RSLT_ENUM_UINT32;

/*****************************************************************************
 �ṹ����   : LRRC_LMM_SUS_SYS_CHNG_DIR_ENUM
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : LRRC֪ͨLMM����ķ���
*****************************************************************************/
enum LRRC_LMM_SUS_SYS_CHNG_DIR_ENUM
{
    LRRC_LMM_SUS_SYS_CHNG_DIR_L2W   = 0,
    LRRC_LMM_SUS_SYS_CHNG_DIR_L2G,

    /*Modify by sunbing 49683 for CL multimode 2014-01-09 begin*/
    LRRC_LMM_SUS_SYS_CHNG_DIR_L2C,
    /*Modify by sunbing 49683 for CL multimode 2014-01-09 end*/

    LRRC_LMM_SUS_SYS_CHNG_DIR_BUTT
};
typedef VOS_UINT32 LRRC_LMM_SUS_SYS_CHNG_DIR_ENUM_UINT32;

/*****************************************************************************
 �ṹ����   : LRRC_LMM_SYS_CHNG_TYPE_ENUM
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : ϵͳ���������
*****************************************************************************/
enum LRRC_LMM_SYS_CHNG_TYPE_ENUM
{
    LRRC_LMM_SYS_CHNG_TYPE_RESEL    = 0,
    LRRC_LMM_SYS_CHNG_TYPE_HO,
    LRRC_LMM_SYS_CHNG_TYPE_CCO,
    LRRC_LMM_SYS_CHNG_TYPE_REDIR,

    LRRC_LMM_SYS_CHNG_TYPE_RESEL_REVERSE,
    LRRC_LMM_SYS_CHNG_TYPE_HO_REVERSE,
    LRRC_LMM_SYS_CHNG_TYPE_CCO_REVERSE,
    LRRC_LMM_SYS_CHNG_TYPE_REDIR_REVERSE,

    LRRC_LMM_SYS_CHNG_TYPE_BUTT
};
typedef VOS_UINT32 LRRC_LMM_SYS_CHNG_TYPE_ENUM_UINT32;

/*****************************************************************************
 �ṹ����   : LRRC_LMM_SUS_CAUSE_ENUM
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : LRRC֪ͨLMM�����ԭ��
*****************************************************************************/
enum LRRC_LMM_SUS_CAUSE_ENUM
{
    LRRC_LMM_SUS_CAUSE_CSFB          = 0,

    /* ����CSFB���µĹ��������BUTTֵ */
    LRRC_LMM_SUS_CAUSE_BUTT
};
typedef VOS_UINT32 LRRC_LMM_SUS_CAUSE_ENUM_UINT32;

/*****************************************************************************
 �ṹ����   : LRRC_LMM_RSM_SYS_CHNG_DIR_ENUM
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : LRRC֪ͨLMM�ָ��ķ���
*****************************************************************************/
enum LRRC_LMM_RSM_SYS_CHNG_DIR_ENUM
{

    LRRC_LMM_RSM_SYS_CHNG_DIR_W2L    = 0,
    LRRC_LMM_RSM_SYS_CHNG_DIR_G2L,
    /*Modify by sunbing 49683 for CL multimode 2014-01-09 begin*/
    LRRC_LMM_RSM_SYS_CHNG_DIR_C2L,
    /*Modify by sunbing 49683 for CL multimode 2014-01-09 end*/
    LRRC_LMM_RSM_SYS_CHNG_DIR_BUTT
};
typedef VOS_UINT32 LRRC_LMM_RSM_SYS_CHNG_DIR_ENUM_UINT32;

/*****************************************************************************
 �ṹ����   : LRRC_LMM_CSFB_RESULT_ENUM
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : LRRC֪ͨLMM CSFBʧ�ܽ��
*****************************************************************************/
enum LRRC_LMM_CSFB_RESULT_ENUM
{
    LRRC_LMM_CSFB_RESULT_FAIL          = 0,

    /* ���CSFB�����ڣ�����LRRC_LMM_CSFB_RESULT_BUTT */
    LRRC_LMM_CSFB_RESULT_BUTT
};
typedef VOS_UINT32 LRRC_LMM_CSFB_RESULT_ENUM_UINT32;

/*****************************************************************************
 �ṹ����   : LRRC_LNAS_SUSPEND_NOTIFY_ENUM
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : LRRC֪ͨLMM �˴��Ƿ���ҪLMM����LRRC���Լ������ԭ��
*****************************************************************************/
enum LRRC_LNAS_SUSPEND_NOTIFY_ENUM
{
    LRRC_LNAS_NOT_SUSPEND   = 0,
    LRRC_LNAS_SUSPEND_LTE_RAT_NOT_ACTIVE,
    LRRC_LNAS_SUSPEND_LTE_BAND_NOT_SUPPORT,

    LRRC_LNAS_SUSPEND_NOTIFY_BUTT
};
typedef VOS_UINT32 LRRC_LNAS_SUSPEND_NOTIFY_ENUM_UINT32;

/*****************************************************************************
ö����    : LRRC_LNAS_RAT_PRIO_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ��ʽ���ȼ�����
*****************************************************************************/
enum LRRC_LNAS_RAT_PRIO_ENUM
{
    LRRC_LNAS_RAT_PRIO_NULL                = 0,          /* �ý��뼼��������*/
    LRRC_LNAS_RAT_PRIO_LOW                 = 1,          /* ���ȼ��ϵ�   */
    LRRC_LNAS_RAT_PRIO_MIDDLE              = 2,          /* ���ȼ��м�   */
    LRRC_LNAS_RAT_PRIO_HIGH                = 3,          /* ���ȼ��ϸ�   */
    LRRC_LNAS_RAT_PRIO_BUTT
};
typedef VOS_UINT8  LRRC_LNAS_RAT_PRIO_ENUM_UINT8;

/*****************************************************************************
ö����    : LRRC_LNAS_RAT_TYPE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ��ʽ����
*****************************************************************************/
enum LRRC_LNAS_RAT_TYPE_ENUM
{
    LRRC_LNAS_RAT_TYPE_GSM = 0,                         /* GSM���뼼�� */
    LRRC_LNAS_RAT_TYPE_WCDMA,                           /* WCDMA���뼼�� */
    LRRC_LNAS_RAT_TYPE_LTE,                             /* LTE���뼼�� */
    /*Modify by sunbing 49683 for CL multimode 2014-01-09 begin*/
    LRRC_LNAS_RAT_TYPE_CDMA1X,                          /* 1x*/
    LRRC_LNAS_RAT_TYPE_HRPD,                            /* HRPD*/
    /*Modify by sunbing 49683 for CL multimode 2014-01-09 end*/
    LRRC_LNAS_RAT_TYPE_BUTT
};

/* Ϊ�˺���SYSCFG PHASE I ��׮ ,��GU SYSCFG���Ժ�������´���ɾ��----begin*/
typedef VOS_UINT8 LRRC_LNAS_RAT_TYPE_ENUM_UINT8;
/*****************************************************************************
 ö����    : LRRC_LNAS_ATTACH_STATUS_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : NAS_INFO_STRU enAttachȡֵ
*****************************************************************************/
enum LRRC_LNAS_MBMS_SESSION_CFG_ENUM
{
    LRRC_LNAS_MBMS_CFG_STOP                = 0,
    LRRC_LNAS_MBMS_CFG_START               = 1,
    LRRC_LNAS_MBMS_CFG_BUTT
};
typedef VOS_UINT32 LRRC_LNAS_MBMS_SESSION_CFG_ENUM_UINT32;


/* add by lishangfeng bg begin */

/*****************************************************************************
 ö����    : LRRC_LMM_BG_SRCH_RLT_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : BG�������
*****************************************************************************/
enum LRRC_LMM_BG_SRCH_RLT_ENUM
{
    LRRC_LMM_BG_SRCH_RLT_SUCC               = 0,                /* ָ����PLMN�����ɹ� */
    LRRC_LMM_BG_SRCH_RLT_FAIL               = 1,                /* ʵ�ʷ�������������������ʧ�� */
    LRRC_LMM_BG_SRCH_RLT_ABORT              = 2,                /* û�з�����������Ϊ��ǰ״̬��������������ֹ */
    LRRC_LMM_BG_SRCH_RLT_BUTT
};
typedef VOS_UINT32  LRRC_LMM_BG_SRCH_RLT_ENUM_UINT32;

/*****************************************************************************
 ö����    : LRRC_LMM_RAT_LIST_SEARCH_RSLT_ENUM
 �ṹ˵��  : LRRC_LNAS_LIST_SEARCH_RAT_INFO_STRU��Ϣ�е�LIST����������
*****************************************************************************/
enum LRRC_LMM_RAT_LIST_SEARCH_RSLT_ENUM
{
    LRRC_LMM_RAT_LIST_SEARCH_NOT_START      = 0,                /* LIST����δ����        */
    LRRC_LMM_RAT_LIST_SEARCH_PARTIAL_CMPL   = 1,                /* LIST����������,������� */
    LRRC_LMM_RAT_LIST_SEARCH_CMPL           = 2,                /* LIST�������          */
    LRRC_LMM_RAT_LIST_SEARCH_BUTT
};
typedef VOS_UINT8  LRRC_LMM_RAT_LIST_SEARCH_RSLT_ENUM_UINT8;

enum LRRC_LNAS_UTRAN_MODE_ENUM
{
    LRRC_LNAS_UTRAN_MODE_WCDMA         = 0x00,     /* ��ǰ����ģʽΪWCDMA */
    LRRC_LNAS_UTRAN_MODE_TDSCDMA       = 0x01,     /* ��ǰ����ģʽΪTDSCDMA */
    LRRC_LNAS_UTRAN_MODE_BUTT
};
typedef VOS_UINT8  LRRC_LNAS_UTRAN_MODE_ENUM_UINT8;


/*****************************************************************************
 ö����    : LRRC_LNAS_GUMMEI_TYPE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : GUMMEI typeö��
*****************************************************************************/
enum LRRC_LNAS_GUMMEI_TYPE_ENUM
{
    LRRC_LNAS_GUMMEI_TYPE_NATIVE             = 0,                /* NATIVE GUMMEI */
    LRRC_LNAS_GUMMEI_TYPE_MAPPED             = 1,                /* MAPPED GUMMEI */

    LRRC_LNAS_GUMMEI_TYPE_BUTT
};
typedef VOS_UINT8  LRRC_LNAS_GUMMEI_TYPE_ENUM_UINT8;

/*****************************************************************************
 ö����    : LRRC_LNAS_ACCESS_MODE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : SysInfoInd��Ϣ�е�accessMode
*****************************************************************************/
enum LRRC_LNAS_ACCESS_MODE_ENUM
{
    LRRC_LNAS_ACCESS_MODE_TDD           = 0,                /* TDDģʽ*/
    LRRC_LNAS_ACCESS_MODE_FDD           = 1,                /* FDDģʽ */
    LRRC_LNAS_ACCESS_MODE_BUTT
};
typedef VOS_UINT8  LRRC_LNAS_ACCESS_MODE_ENUM_UINT8;

/*****************************************************************************
 ö����    : RRC_NAS_CAPABILITY_CHANGE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : NAS��RRC֮��ԭ��ִ�н��ȡֵ
*****************************************************************************/
enum LRRC_LNAS_CAPABILITY_CHANGE_ENUM
{
    LRRC_LNAS_UE_CAPABILITY_NOT_CHANGE         = 0,         /* UE�����������ı�*/
    LRRC_LNAS_UE_CAPABILITY_CHANGE             = 1,         /* UE���������ı� */
    LRRC_LNAS_UE_CAPABILITY_BUTT
};
typedef VOS_UINT32  LRRC_LNAS_CAPABILITY_CHANGE_ENUM_UINT32;

/*****************************************************************************
 ö����    : LRRC_LNAS_RAT_CHANGE_CAUSE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  :
*****************************************************************************/
enum LRRC_LNAS_SUSPEND_INFO_CHANGE_TYPE_ENUM
{
    LRRC_LNAS_SUSPEND_RAT_INFO_CHANGE   = 0,     /* CSFB���ض��������RAT�����ı�*/
    LRRC_LNAS_SUSPEND_INFO_CHANGE_BUTT
};
typedef VOS_UINT32  LRRC_LNAS_SUSPEND_INFO_CHANGE_TYPE_ENUM_UINT32;

/*****************************************************************************
 ö����    : LRRC_LNAS_RAT_CHANGE_CAUSE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  :
*****************************************************************************/
enum LRRC_LNAS_RAT_CHANGE_TYPE_ENUM
{
    LRRC_LNAS_RAT_CHANGE_G2W   = 0,
    LRRC_LNAS_RAT_CHANGE_W2G   = 1,
    LRRC_LNAS_RAT_CHANGE_TYPE_BUTT
};
typedef VOS_UINT32  LRRC_LNAS_RAT_CHANGE_TYPE_ENUM_UINT32;


/*****************************************************************************
 ö����    : LRRC_LNAS_CALL_TYPE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : CALL typeö��
*****************************************************************************/
enum LRRC_LNAS_CALL_TYPE_ENUM
{
    LRRC_LNAS_CALL_TYPE_ORIGINATING_SIGNALLING       = 0,            /* MO signalling */
    LRRC_LNAS_CALL_TYPE_ORIGINATING_CALL             = 1,            /* MO call */
    LRRC_LNAS_CALL_TYPE_TERMINATING_CALL             = 2,            /* MT call */
    LRRC_LNAS_CALL_TYPE_EMERGENCY_CALL               = 3,            /* EMERGENCY call */
    LRRC_LNAS_CALL_TYPE_MO_CSFB                      = 4,            /* MO CSFB */

    LRRC_LNAS_CALL_TYPE_BUTT
};
typedef VOS_UINT32  LRRC_LNAS_CALL_TYPE_ENUM_UINT32;

/*****************************************************************************
 ö����: LRRC_LNAS_PLMN_SRCH_RLT_ENUM
 Э���ʽ:
 ASN.1����:
 ö��˵��:
*****************************************************************************/
enum LRRC_LNAS_COVERAGE_TYPE_ENUM
{
    LRRC_LNAS_COVERAGE_TYPE_NONE      = 0,                /* �����縲�� */
    LRRC_LNAS_COVERAGE_TYPE_LOW       = 1,                 /* ���������縲��   */
    LRRC_LNAS_COVERAGE_TYPE_HIGH      = 2,                /* �и��������縲�� */
    LRRC_LNAS_COVERAGE_TYPE_BUTT
};
typedef VOS_UINT32  LRRC_LNAS_COVERAGE_TYPE_ENUM_UINT32;
enum LRRC_LNAS_SESSION_TYPE_ENUM
{
    LRRC_LNAS_SESSION_TYPE_MO_NORMAL_CALL           =0,
    LRRC_LNAS_SESSION_TYPE_MT_NORMAL_CALL           =1,
    LRRC_LNAS_SESSION_TYPE_MO_EMERGENCY_CALL        =2,
    LRRC_LNAS_SESSION_TYPE_MO_SS                    =3,
    LRRC_LNAS_SESSION_TYPE_MT_SS                    =4,
    LRRC_LNAS_SESSION_TYPE_MO_SMS                   =5,
    LRRC_LNAS_SESSION_TYPE_MT_SMS                   =6,
    LRRC_LNAS_SESSION_TYPE_MO_NORMAL_CSFB           =7,
    LRRC_LNAS_SESSION_TYPE_MO_EMERGENCY_CSFB        =8,
    LRRC_LNAS_SESSION_TYPE_MT_CSFB                  =9,
    LRRC_LNAS_SESSION_TYPE_PS_CONVERSAT_CALL        =10,
    LRRC_LNAS_SESSION_TYPE_PS_STREAM_CALL           =11,
    LRRC_LNAS_SESSION_TYPE_PS_INTERACT_CALL         =12,
    LRRC_LNAS_SESSION_TYPE_PS_BACKGROUND_CALL       =13,
    LRRC_LNAS_SESSION_TYPE_PS_SUBSCRIB_TRAFFIC_CALL =14,
    LRRC_LNAS_SESSION_TYPE_PS_ATTACH                =15,
    LRRC_LNAS_SESSION_TYPE_PS_LOW_TAU               =16,
    LRRC_LNAS_SESSION_TYPE_PS_HIGH_TAU              =17,
    LRRC_LNAS_SESSION_TYPE_PS_DETACH                =18,
    LRRC_LNAS_SESSION_TYPE_PS_ESM                   =19,
    LRRC_LNAS_SESSION_TYPE_BUTT
};
typedef VOS_UINT8 LRRC_LNAS_SESSION_TYPE_ENUM_UINT8;

/*****************************************************************************
 ö����    : LRRCL_NAS_NETSCAN_RESULT_ENUM
 �ṹ˵��  : �����ظ�NASɨ����
*****************************************************************************/
enum LRRC_LNAS_NETSCAN_RESULT_ENUM
{
    LRRC_LNAS_NETSCAN_RESULT_SUCCESS        = 0,
    LRRC_LNAS_NETSCAN_RESULT_FAILURE        = 1,

    LRRC_LNAS_NETSCAN_RESULT_BUTT
};
typedef   VOS_UINT8    LRRC_LNAS_NETSCAN_RESULT_ENUM_UINT8;

/*****************************************************************************
 ö����    : LRRC_LNAS_BOOL_ENUM
 �ṹ˵��  : �����NETSCAN BOOLֵ
*****************************************************************************/
enum LRRC_LNAS_BOOL_ENUM
{
    LRRC_LNAS_FALSE                                  = 0,
    LRRC_LNAS_FALSE_TRUE                             = 1,

    LRRC_LNAS_FALSE_BOOL_BUTT
};
typedef   VOS_UINT8    LRRC_LNAS_BOOL_ENUM_UINT8;


/*****************************************************************************
 ö����    : LRRC_LNAS_NETSCAN_CAUSE_ENUM
 �ṹ˵��  : �����ظ�NASɨ��ʧ��ԭ�������ǰû���κ�ģʽפ����NASֱ�ӻظ�ATʧ��
*****************************************************************************/
enum LRRC_LNAS_NETSCAN_CAUSE_ENUM
{
    LRRC_LNAS_NETSCAN_CAUSE_SIGNAL_EXIST = 0,                /* �����������ӣ�NAS�ظ�AT�Ժ��ٳ��� */
    LRRC_LNAS_NETSCAN_CAUSE_STATE_NOT_ALLOWED,               /* ��ǰ״̬������NAS�ظ�AT�Ժ��ٳ��� */
    LRRC_LNAS_NETSCAN_CAUSE_FREQ_LOCK,                       /* ��ǰ��Ƶ״̬��NAS�ظ�ATʧ�� */
    LRRC_LNAS_NETSCAN_CAUSE_PARA_ERROR,                      /* �������󣬰������뼼����֧�֣�Ƶ�β�֧�֣�Ƶ������������޴���NAS�ظ�ATʧ�� */

    LRRC_LNAS_NETSCAN_CAUSE_BUTT
};
typedef   VOS_UINT8    LRRC_LNAS_NETSCAN_CAUSE_ENUM_UINT8;

/*****************************************************************************
 �ṹ����   : LRRC_INTER_OPT_TYPE_ENUM
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : LRRC֪ͨLMM����X->L������������
*****************************************************************************/
enum LRRC_LNAS_INTER_OPT_TYPE_ENUM
{
    LRRC_LNAS_INTER_OPT_TYPE_U2L_RESEL,
    LRRC_LNAS_INTER_OPT_TYPE_U2L_REDIR,
    LRRC_LNAS_INTER_OPT_TYPE_U2L_HO,

    LRRC_LNAS_INTER_OPT_TYPE_G2L_RESEL,
    LRRC_LNAS_INTER_OPT_TYPE_G2L_REDIR,
    LRRC_LNAS_INTER_OPT_TYPE_G2L_HO,
    LRRC_LNAS_INTER_OPT_TYPE_G2L_CCO,

    LRRC_LNAS_INTER_OPT_TYPE_BUTT
};
typedef VOS_UINT32 LRRC_LNAS_INTER_OPT_TYPE_ENUM_UINT32;

/*****************************************************************************
 �ṹ����   : LRRC_INTER_OPT_INFO_TYPE_ENUM
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : LRRC֪ͨLMM����X->L������������
*****************************************************************************/
enum LRRC_INTER_OPT_INFO_TYPE_ENUM
{
    LRRC_LNAS_INTER_OPT_INFO_TAILIST,

    LRRC_LNAS_INTER_OPT_INFO_BUTT
};
typedef VOS_UINT32 LRRC_INTER_OPT_INFO_TYPE_ENUM_UINT32;


/*****************************************************************************
 �ṹ����   : LRRC_INTER_OPT_TYPE_ENUM
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : LRRC֪ͨLMM����X->L������������
*****************************************************************************/
enum LRRC_LMM_EXPERIENCE_SPEC_REQ_TYPE_ENUM
{
    LRRC_LMM_EXPERIENCE_SPEC_REQ_STOP_SLAVEMEAS,
    LRRC_LMM_EXPERIENCE_SPEC_REQ_RESTART_SLAVEMEAS,

    LRRC_LMM_EXPERIENCE_SPEC_REQ_BUTT
};
typedef VOS_UINT32 LRRC_LMM_EXPERIENCE_SPEC_REQ_TYPE_ENUM_UINT32;
/*****************************************************************************
 �ṹ����   : lRRC_LNAS_CSFB_STATUS_ENUM
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : LMM֪ͨLRRC CSFB����������
*****************************************************************************/
enum lRRC_LNAS_CSFB_STATUS_ENUM
{
    LRRC_LNAS_CSFB_STATUS_INIT,
    LRRC_LNAS_CSFB_STATUS_START,
    LRRC_LNAS_CSFB_STATUS_END,

    LRRC_LNAS_CSFB_STATUS_BUTT
};
typedef VOS_UINT16  LRRC_LNAS_CSFB_STATUS_ENUM_UINT16;


typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32          enMsgId;            /*_H2ASN_Skip*/
    LRRC_LNAS_SESSION_TYPE_ENUM_UINT8                 enSessionType;
    VOS_UINT8                                       aucReserved[3];
}LRRC_LMM_BEGIN_SESSION_NOTIFY_STRU;


typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32          enMsgId;            /*_H2ASN_Skip*/
    LRRC_LNAS_SESSION_TYPE_ENUM_UINT8                 enSessionType;
    VOS_UINT8                                       aucReserved[3];
}LRRC_LMM_END_SESSION_NOTIFY_STRU;


typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32          enMsgId;            /*_H2ASN_Skip*/
 }LRRC_LMM_DETACH_IND_STRU;

/*****************************************************************************
 �ṹ����   : LRRC_LMM_HO_SECU_PARA_STRU
 Э����   : L->GU�л�ʱ��ȫ����
 ASN.1 ���� :
 �ṹ˵��   : LRRC_LMM_HO_SECU_PARA_STRU���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucHoSecuPara;
    VOS_UINT8                           aucRsv[3];
} LRRC_LMM_HO_SECU_PARA_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LMM_START_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RRC_MM_START_REQ_STRU���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32          enMsgId;            /*_H2ASN_Skip*/
    LRRC_LNAS_SIM_STATUS_ENUM_UINT32      enSimStatus;        /* SIM��״̬*/

    /* ��ģ�����ȼ�
        -------------------------------------------------------------
        aucRatPrioList [0]      |     LRRC_LNAS_RAT_TYPE_GSM
        -------------------------------------------------------------
        aucRatPrioList [1]      |     LRRC_LNAS_RAT_TYPE_WCDMA
        -------------------------------------------------------------
        aucRatPrioList [2]      |     LRRC_LNAS_RAT_TYPE_LTE
        -------------------------------------------------------------
    */

    LRRC_LNAS_RAT_PRIO_ENUM_UINT8        aucRatPrioList[LRRC_LNAS_RAT_TYPE_BUTT];

    /* ��Ҫ����ָʾͬʱ����LTE_TDD��LTE_FDD��ʽ������ʹ��������ʽ
    1:��ʾ������FDDģʽ��2:��ʾ������TDDģʽ */
    VOS_UINT8                            enLteRatPrio;
    LRRC_LNAS_UTRAN_MODE_ENUM_UINT8      enUtranMode;
    /*Modify by sunbing 49683 for CL multimode 2014-01-09 begin*/
    VOS_UINT8                            aucReserved[1];
    /*Modify by sunbing 49683 for CL multimode 2014-01-09 end*/
}LRRC_LMM_START_REQ_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LMM_START_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RRC_MM_START_CNF_STRU���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32          enMsgId;            /*_H2ASN_Skip*/

    LRRC_LNAS_START_RESULT_ENUM_UINT32    enResult;           /* ������� */
}LRRC_LMM_START_CNF_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LNAS_PLMN_WITH_RAT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucPlmnId[3];
    LRRC_LNAS_RAT_TYPE_ENUM_UINT8       enPlmnRat;
}LRRC_LNAS_PLMN_WITH_RAT_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LNAS_LAC_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : AC��Ϣ �ɲο�24.008 10.5.1.3
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucLac;
    VOS_UINT8                           ucLacCont;
    VOS_UINT8                           aucReserved[2];
}LRRC_LNAS_LAC_STRU;

/*****************************************************************************
 �ṹ��    : RRC_NAS_RAC_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RAC��Ϣ �ɲο�24.008 10.5.5.15
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucRac;
    VOS_UINT8                           aucReserved[3];
}RRC_NAS_RAC_STRU;

/*****************************************************************************
 �ṹ��    : RRC_NAS_RAC_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : TAC��Ϣ  24.301  9.9.3.28
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucTac;
    VOS_UINT8                           ucTacCont;
    VOS_UINT8                           aucReserved[2];
}LRRC_LNAS_TAC_STRU;


/*****************************************************************************
 �ṹ��    : LRRC_LNAS_LA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LA��Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    LRRC_LNAS_PLMN_ID_STRU                stPlmnId;
    LRRC_LNAS_LAC_STRU                    stLac;
}LRRC_LNAS_LA_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LNAS_RA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RA��Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    LRRC_LNAS_PLMN_ID_STRU                stPlmnId;
    LRRC_LNAS_LAC_STRU                    stLac;
    RRC_NAS_RAC_STRU                      stRac;
}LRRC_LNAS_RA_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LNAS_TA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : TA��Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    LRRC_LNAS_PLMN_ID_STRU                stPlmnId;
    LRRC_LNAS_TAC_STRU                    stTac;
}LRRC_LNAS_TA_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LNAS_EPLMN_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��ЧPLMN���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                            ulPlmnIdNum;        /* PLMN ID����   */
    LRRC_LNAS_PLMN_ID_STRU                astEplmnIdList[LRRC_LNAS_MAX_EQUPLMN_NUM];
}LRRC_LNAS_EPLMN_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LNAS_EPLMN_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��ЧPLMN���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                            ulForbLaNum;        /* ��ֹע�����ĸ��� */
    LRRC_LNAS_LA_STRU                     astForbLacList[LRRC_LNAS_MAX_FORBLA_NUM];
}LRRC_LNAS_FORB_LA_LIST_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LNAS_FORB_TA_LIST_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : forbid ta �б����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                            ulTaNum;            /* TA�ĸ���    */
    LRRC_LNAS_TA_STRU                     astForbTa[LRRC_LNAS_MAX_FORBTA_NUM];
}LRRC_LNAS_FORB_TA_LIST_STRU;
/* ncell spec search begin */
/*****************************************************************************
 �ṹ��    : LRRC_LNAS_NCELL_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : NCELL �������ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucLteArfcnNum;         /* 0��ʾLTEƵ�㲻���� */
    VOS_UINT8                           aucRsv[3];             /* ����λ */
    VOS_UINT32                          aulLteArfcnList[LRRC_LNAS_MAX_ARFCN_NUM];
    LRRC_LNAS_EPLMN_STRU                stEplmnList;           /* ������ص�ЧPLMN��Ϣ*/

    /*Modify by sunbing 49683 for CL multimode 2014-01-09 begin*/
    VOS_UINT8                           ucLteCellIdNum;                         /*0��ʾLTEС��ID������*/
    VOS_UINT8                           aucRsv1[3];
    VOS_UINT16                          ausLteCellIdList[LRRC_LNAS_LTE_CELL_ID_MAX_NUM];
    /*Modify by sunbing 49683 for CL multimode 2014-01-09 end*/
}LRRC_LNAS_NCELL_INFO_STRU;
/* ncell spec search end */

/*****************************************************************************
 �ṹ��    : LRRC_LMM_PLMN_SEARCH_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RRC_MM_PLMN_SEARCH_REQ_STRU���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32              enMsgId;        /*_H2ASN_Skip*/

    VOS_UINT32                              bitOpSpecPlmn: 1;
    VOS_UINT32                              bitOpEqlPlmn : 1;
    VOS_UINT32                              bitOpForbLa  : 1;
    VOS_UINT32                              bitOpForbTa  : 1;
    /* ncell spec search begin */
    VOS_UINT32                              bitOpNcellInfo: 1;
    VOS_UINT32                              bitOpPlmnInfoCampFlg:1; /* �ײ��ϱ���PLMN�Ƿ���Ҫ����פ��������Ŀǰ���ڻ�ȡ������Ϣ�ӿ���ʹ�� */
    VOS_UINT32                              bitSpare     : 26;
    /* ncell spec search end */

    /* �������� */
    LRRC_LNAS_PLMN_SEARCH_TYPE_ENUM_UINT32    enSearchType;
    LRRC_LNAS_FFT_SCAN_TYPE_ENUM_UINT8        enFftScanType;
    VOS_UINT8                                 aucReserve[3];

    /* ָ��PLMN ID */
    LRRC_LNAS_PLMN_ID_STRU                    stSpecPlmnId;

    /* ��ЧPLMN LIST */
    LRRC_LNAS_EPLMN_STRU                      stEplmn;

    /* ��ֹLA�б�  */
    LRRC_LNAS_FORB_LA_LIST_STRU               stForbLaList;

    /* ��ֹTA�б�  */
    LRRC_LNAS_FORB_TA_LIST_STRU               stForbTaList;
    /* ncell spec search begin */
    LRRC_LNAS_NCELL_INFO_STRU                 stNcellInfo;
    /* ncell spec search end */
}LRRC_LMM_PLMN_SEARCH_REQ_STRU;


/*****************************************************************************
 �ṹ��    : LRRC_LNAS_LOW_PLMN_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RRC_NAS_LOW_PLMN_INFO_STRU���ݽṹ
*****************************************************************************/
typedef struct
{
    LRRC_LNAS_PLMN_ID_STRU                stPlmnId;           /* PLMN ID    */
    VOS_INT32                             lRscp;              /* RSCP����ֵ */
}LRRC_LNAS_LOW_PLMN_INFO_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LNAS_LOW_PLMN_WITH_RAT_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LRRC_LNAS_LOW_PLMN_WITH_RAT_INFO_STRU���ݽṹ
*****************************************************************************/
typedef struct
{
    LRRC_LNAS_PLMN_WITH_RAT_STRU          stPlmnId;           /* PLMN ID    */
    VOS_INT32                             lRscp;              /* RSCP����ֵ */
}LRRC_LNAS_LOW_PLMN_WITH_RAT_INFO_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LNAS_PLMN_ID_LIST_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RRC_NAS_PLMN_ID_LIST_STRU���ݽṹ
*****************************************************************************/
typedef struct
{
    /* ������PLMN�ĸ��� */
    VOS_UINT32                            ulHighPlmnNum;

    /* ������PLMN�б�   */
    LRRC_LNAS_PLMN_WITH_RAT_STRU          astHighPlmnWithRatList[LRRC_LNAS_MAX_HIGH_PLMN_NUM];


    /* ������PLMN�ĸ��� */
    VOS_UINT32                            ulLowPlmnNum;

    /* ������PLMN�б�   */
    LRRC_LNAS_LOW_PLMN_WITH_RAT_INFO_STRU astLowPlmnWithRatList[LRRC_LNAS_MAX_LOW_PLMN_NUM];
}LRRC_LNAS_PLMN_ID_LIST_STRU;


/*****************************************************************************
 �ṹ��    : LRRC_LNAS_SUIT_PLMN_ID_LIST_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RRC_NAS_SUIT_PLMN_ID_LIST_STRU���ݽṹ
*****************************************************************************/
typedef struct
{
    /* ��ǰС��ϵͳ��Ϣ�а����ĵ�Чplmn id�ĸ��� */
    VOS_UINT32                            ulSuitPlmnNum;

    /* ��Ч��plmn id����Ϣ   */
    LRRC_LNAS_PLMN_ID_STRU                astSuitPlmnList[LRRC_LNAS_MAX_SEARCHED_PLMN_NUM];
} LRRC_LNAS_SUIT_PLMN_ID_LIST_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LNAS_LIST_SEARCH_RAT_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LRRC_LNAS_LIST_SEARCH_RAT_INFO_STRU���ݽṹ
*****************************************************************************/
typedef struct
{
    LRRC_LNAS_RAT_TYPE_ENUM_UINT8             senRat;                            /* �����Ľ��뼼�� */
    LRRC_LMM_RAT_LIST_SEARCH_RSLT_ENUM_UINT8  enListSearchRlt;                  /* ���뼼��LIST������ɽ�� */
    VOS_UINT8                                 aucReserved[2];
}LRRC_LNAS_LIST_SEARCH_RAT_INFO_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LMM_PLMN_SEARCH_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RRC_MM_PLMN_SEARCH_CNF_STRU���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32          enMsgId;            /*_H2ASN_Skip*/

    /* ������� */
    LRRC_LNAS_PLMN_SEARCH_RLT_ENUM_UINT32 enRlst;

    LRRC_LNAS_COVERAGE_TYPE_ENUM_UINT32   enCoverageType;     /* ��ǰ���뼼���µ����縲������ */

    /* ָ��PLMN�����ɹ�ʱ,�ѵ���PLMN ID,��ulSeaRltΪָ�������ɹ�ʱ��Ч */
    LRRC_LNAS_SUIT_PLMN_ID_LIST_STRU      stSpecPlmnIdList;

    /* ��¼L��ģ�±����Ѿ������Ľ��뼼���������б�����ʱ��Ч */
    LRRC_LNAS_LIST_SEARCH_RAT_INFO_STRU   astSearchRatInfo[LRRC_LNAS_MAX_RAT_NUM];

    /* LIST PLMN����ʱ,��spec plmn����ʧ��ʱ��������Ч */
    LRRC_LNAS_PLMN_ID_LIST_STRU           stPlmnIdList;
}LRRC_LMM_PLMN_SEARCH_CNF_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LMM_SEARCHED_PLMN_LIST_INFO_IND_STRU
 Э����  : ����plmn list��plmn spec������������nas�ϱ���ǰ�������
 ASN.1���� :
 �ṹ˵��  : LRRC_LMM_SEARCHED_PLMN_LIST_INFO_IND_STRU���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                            /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32          enMsgId;            /*_H2ASN_Skip*/

    VOS_UINT32                            ulTaiNum;            /* Plmn�ĸ���    */

    LRRC_LNAS_TA_STRU                     stTaiList[LRRC_LMM_MAX_SEARCHED_TAI_NUM];
}LRRC_LMM_SEARCHED_PLMN_INFO_IND_STRU;


/*****************************************************************************
 �ṹ��    : LRRC_LMM_PLMN_SEARCH_STOP_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : NASֻ��NAS��ʽ��ʹ��RRC_MM_PLMN_SEARCH_REQ��Ϣ�����SPEC PLMN��
              PLMN LIST�����У�ʹ�ô���Ϣ֪ͨRRCֹͣPLMN������
              ������������NASҪ����PLMN���������ȸ�RRC ����RRC_MM_REL_REQ
              ��Ϣ�� Ȼ���ٷ���PLMN������Ϣ����ȷ��RRC�ܽ��к�����PLMN����;
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32          enMsgId;            /*_H2ASN_Skip*/
}LRRC_LMM_PLMN_SEARCH_STOP_REQ_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LMM_PLMN_SEARCH_STOP_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RRC�ø�ԭ���RRC_GMM_PLMN_SEARCH_STOP_REQȷ�ϡ�
              ��RRC��ǰ���ڽ���SPEC PLMN����PLMN LIST��������Ҫֹͣ��ز�����
              �ظ�����Ϣ���ȴ�NAS����RRC_MM_PLMN_SEARCH_REQ��Ϣ��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32          enMsgId;            /*_H2ASN_Skip*/
}LRRC_LMM_PLMN_SEARCH_STOP_CNF_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LMM_EQU_PLMN_NOTIFY_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RRC_MM_EQU_PLMN_NOTIFY_REQ_STRU���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32          enMsgId;            /*_H2ASN_Skip*/

    /* RPLMN */
    LRRC_LNAS_PLMN_ID_STRU                stRPlmnId;          /* ��ǰע���ϵ�PLMN��
                                                               ��û��ע��ɹ�����Ϊ0xFFFFFF*/

    /* EPLMN�ĸ���,����RPLMN */
    VOS_UINT32                            ulEquPlmnNum;

    /* ��EPLMN LIST���ܸ��µĳ���:
       ע��ɹ�ʱ�����а������������·���EPLMN LIST�͸�ע��ɹ���RPLMN��
       ע��ʧ��ʱ���£�1) ɾ��EPLMN�б����б�Ϊ�գ�
                       2) ��ǰ��ע���PLMN�������� EPLMNLIST�����ұ����԰����ղ�
                          ��RPLMN���������������ղŵ�RPLMN */
    LRRC_LNAS_PLMN_ID_STRU                aEquPlmnIdList[LRRC_LNAS_MAX_EQUPLMN_NUM];
} LRRC_LMM_EQU_PLMN_NOTIFY_REQ_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LNAS_S_TMSI_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : S-TMSI���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucMmec;
    VOS_UINT8                           aucReserved[3];
    VOS_UINT32                          ulMTmsi;
}LRRC_LNAS_S_TMSI_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LNAS_GUMMEI_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : globally unique MME identifier ���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucMmec;
    LRRC_LNAS_GUMMEI_TYPE_ENUM_UINT8     enGummeiType;
    VOS_UINT16                          usMmeGi;
    LRRC_LNAS_PLMN_ID_STRU              stPlmnId;
}LRRC_LNAS_GUMMEI_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LNAS_EST_INFO_STRU
 �ṹ˵��  : NAS��������ʱ��ͨ������ϢЯ��S-TMSI������GUMMEI,�Դ���֪ͨENB��
 ʹ�����ַ�ʽѡ��MME
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ucBitOpSTmsi    :1;
    VOS_UINT32                          ucBitOpRegGummei:1;
    VOS_UINT32                          ucBitSpare      :30;

    LRRC_LNAS_S_TMSI_STRU               stStmsi;
    LRRC_LNAS_GUMMEI_STRU               stRegGummei;
}LRRC_LNAS_EST_INFO_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LNAS_EPLMN_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��ЧPLMN���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulEHplmnIdNum;        /* PLMN ID����   */
    LRRC_LNAS_PLMN_ID_STRU              astEHplmnIdList[LRRC_LNAS_MAX_EHPLMN_NUM];
}LRRC_LNAS_EHPLMN_LIST_STRU;

/*****************************************************************************
�ṹ��    :LRRC_NAS_UEID_STRU
Э����  :
ASN.1���� :
�ṹ˵��  : IMSI, IMEI, IMEISV, TMSI, PTMSI�Ĵ�Ÿ�ʽ���� 31.102 4.2.2ִ��

    digit n �� 24.008 10.5.4  Mobile Identity information element �Ķ�Ӧ��ϵ:

    One digit occupies half of a byte.

    Э�������� ��DIGIT���ֽ�/λ�Ĺ�ϵ����:
    ----------------------------------------------------------------------------------
    (BIT8)|(BIT7)|(BIT6)|(BIT5)|(BIT4)|(BIT3)|(BIT2)|(BIT1)
    ----------------------------------------------------------------------------------
        Length of mobile identity contents, UNIT is byte
    ----------------------------------------------------------------------------------
        Identity digit 1       | OorE |  Type of identity
    ----------------------------------------------------------------------------------
        Identity digit 3       |           Identity digit 2
    ----------------------------------------------------------------------------------
        Identity digit i + 1   |           Identity digit i
    ----------------------------------------------------------------------------------
        ......                 |           ......
    ----------------------------------------------------------------------------------
        Identity digit P + 1   |           Identity digit P
    ----------------------------------------------------------------------------------

    ��, �ӿ������и� DIGIT���ֽ�λ�ö�Ӧ��ϵ����:
    -----------------------------------------------------------------------------------------------
    (digit 15) | (digit 14) |.....| (digit  2) | (digit  1) |OorE|TypeOfId|Length of mobile identity contents, UNIT is byte
    -----------------------------------------------------------------------------------------------
    aucImsi[7] | aucImsi [7]|.....| aucImsi[2] | aucImsi[1] | aucImsi[1]  | aucImsi[0] | aucImsi[0]
    -----------------------------------------------------------------------------------------------
    aucImei[7] | aucImei [7]|.....| aucImei[2] | aucImei[1] | aucImei[1]  | aucImei[0] | aucImei[0]
    -----------------------------------------------------------------------------------------------
    aucTmsi[7] | aucTmsi [7]|.....| aucTmsi[2] | aucTmsi[1] | aucTmsi[1]  | aucTmsi[0] | aucTmsi[0]
    -----------------------------------------------------------------------------------------------
    aucPTmsi[7]|aucPTmsi [7]|.....| aucPTmsi[2]| aucPTmsi[1]| aucPTmsi[1] | aucPTmsi[0]| aucPTmsi[0]
    -----------------------------------------------------------------------------------------------
    aucImeisv[7]|aucImeisv[7]|....|aucImeisv[2]|aucImeisv[1]|aucImeisv[1] |aucImeisv[0]| aucImeisv[0]
    -----------------------------------------------------------------------------------------------


    e.g.          IMSI = 230 040 680000079
    ��RRC_NAS�Ľӿ����� aucImsi[] �д��λ������:

    Э�������Ĵ��λ������:
    ----------------------------------------------------------------------------------
                           (BIT8)|(BIT7)|(BIT6)|(BIT5)|(BIT4)|(BIT3)|(BIT2)|(BIT1)
    ------------------------------------------------------------------------------------------------------------
    aucImsi[0] | aucImsi[0]                           8
    --------------------------------------------------------------------------------------------------------------------------------------
    aucImsi[1] | aucImsi[1]               2           |           9
    --------------------------------------------------------------------------------------------------------------------------------------
    aucImsi[2] | aucImsi[2]               0           |           3
    --------------------------------------------------------------------------------------------------------------------------------------
    aucImsi[3] | aucImsi[3]               4           |           0
    -------------------------- ------------------------------------------------------------------------------------------------------------
    aucImsi[4] | aucImsi[4]               6           |           0
    ---------------------------------------------------- ----------------------------------------------------------------------------------
    aucImsi[5] | aucImsi[5]               0           |           8
    ---------------------------------------------------- ----------------------------------------------------------------------------------
    aucImsi[6] | aucImsi[6]               0           |           0
    --------------------------------------------------------------------------------------------------------------------------------------
    aucImsi[7] | aucImsi[7]               0           |           0
    --------------------------------------------------------------------------------------------------------------------------------------
    aucImsi[8] | aucImsi[8]               9           |           7
    ------------------------------------------------------------------------------------------------------------

    ��, �ӿ������и� DIGIT���ֽ�λ�ö�Ӧ��ϵ����:
    -----------------------------------------------------------------------------------------------
    aucImsi[7] | aucImsi [7]|.....| aucImsi[2] | aucImsi[1] | aucImsi[1]|aucImsi[0] | aucImsi[0]
    -----------------------------------------------------------------------------------------------
    (   9    ) | (    7   ) |.....| (    3   ) | (    2   ) | (   9   ) |           8
    -----------------------------------------------------------------------------------------------
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ucBitOpImsi     :1; /* 1: VALID; 0: INVALID*/
    VOS_UINT32                          ucBitOpHplmn    :1; /* 1: VALID; 0: INVALID*/
    VOS_UINT32                          ucBitOpEHplmn   :1; /* 1: VALID; 0: INVALID*/
    VOS_UINT32                          ucBitOpSTmsi    :1; /* 1: VALID; 0: INVALID*/
    VOS_UINT32                          ucBitShare      :28;


    VOS_UINT8                           aucImsi[LRRC_LNAS_MAX_UEID_BUF_SIZE];
    VOS_UINT8                           aucReserved1[2];
    LRRC_LNAS_S_TMSI_STRU               stStmsi;
    LRRC_LNAS_PLMN_ID_STRU              stHplmnId;
    LRRC_LNAS_EHPLMN_LIST_STRU          stEHplmn;
}LRRC_NAS_UEID_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LNAS_SECURITY_KEY_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RRC_NAS_SECURITY_KEY_STRU���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulNasCount;
    VOS_UINT8                           aucKasme[LRRC_LNAS_MAX_ASME_KEY_LEN];
}LRRC_LNAS_SECURITY_KEY_STRU;


/*****************************************************************************
 �ṹ��    : LRRC_LNAS_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RRC_NAS_INFO_STRU���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpAttach     : 1;
    VOS_UINT32                          bitOpSecurityKey: 1;
    VOS_UINT32                          bitOpDrxLength  : 1;
    /* gaojishan-anycamp-normal-camp */
    VOS_UINT32                          bitOpUsimStatus : 1;
    VOS_UINT32                          bitSpare        : 28;

    LRRC_LNAS_ATTACH_STATUS_ENUM_UINT32   enAttach;           /* Attach��Deattach��־ */
    LRRC_LNAS_SECURITY_KEY_STRU           stSecurityKey;
    VOS_UINT32                            ulDrxLength;        /* PS��Э�̺��DRX����  */
    /* gaojishan-anycamp-normal-camp */
    LRRC_LNAS_SIM_STATUS_ENUM_UINT32      enUsimStatus;
}LRRC_LNAS_INFO_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LMM_NAS_INFO_CHANGE_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RRC_MM_NAS_INFO_CHANGE_REQ_STRU���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32          enMsgId;            /*_H2ASN_Skip*/
    LRRC_LNAS_INFO_STRU                   stNasInfo;
}LRRC_LMM_NAS_INFO_CHANGE_REQ_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LMM_CELL_SELECTION_CTRL_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RRC_MM_CELL_SELECTION_CTRL_REQ_STRU���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32          enMsgId;            /*_H2ASN_Skip*/

    LRRC_LNAS_RESEL_TYPE_ENUM_UINT32      enReselectInd;      /* ��ѡ����ָʾ */

    /* ��ֹע�����б� */
    LRRC_LNAS_FORB_LA_LIST_STRU           stForbLaList;
    /* ��ֹTA�б�  */
    LRRC_LNAS_FORB_TA_LIST_STRU           stForbTaList;

} LRRC_LMM_CELL_SELECTION_CTRL_REQ_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LNAS_MSG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LRRC_LNAS_MSG_STRU���ݽṹ
*****************************************************************************/
typedef struct
{
    /* [1,LRRC_LNAS_MAX_DATA_LENGTH],Byte */
    VOS_UINT32                          ulNasMsgSize;

    /* ��Ϣ��ǰ�ĸ��ֽ�����  */
    VOS_UINT8                           aucNasMsg[4];
    /*************************************************************************
        _H2ASN_Array2String
    *************************************************************************/
}LRRC_LNAS_MSG_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LMM_EST_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RRC_MM_EST_REQ_STRU���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32          enMsgId;            /*_H2ASN_Skip*/
    LRRC_LNAS_EST_CAUSE_ENUM_UINT32       enEstCause;         /* RRC Connection Reqԭ�� */
    LRRC_LNAS_CALL_TYPE_ENUM_UINT32       enCallType;
    LRRC_LNAS_EST_INFO_STRU               stEstInfo ;         /* NAS������ʱЯ������Ϣ��eNB���ݸ���Ϣѡ��MME*/
    LRRC_LNAS_MSG_STRU                    stFirstNasMsg;      /* ����CN�ĵ�һ��NAS��Ϣ */
}LRRC_LMM_EST_REQ_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LMM_EST_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RRC_MM_EST_CNF_STRU���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32          enMsgId;            /*_H2ASN_Skip*/
    LRRC_LNAS_EST_RESULT_ENUM_UINT32      enResult;           /* ���ӽ������ */
    /* v7r2 code begin */
    /* extendedWaitTime [1,1800][s]��������ʱĬ��Ϊ0 */
    VOS_UINT16                            usExtendedWaitTime;
    VOS_UINT8                             aucReserved[2];
    /* v7r2 code end */
}LRRC_LMM_EST_CNF_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LMM_REL_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : NASͨ������Ϣ֪ͨRRC�ͷ�RRC���ӣ��ͷ�ʱ��֪ RRC��ǰС���Ƿ�barred
              NAS�쳣��Ҳͨ������Ϣ֪ͨRRC�ͷ�RRC���ӣ���֪ͨRRC�ͷ���Դ��
              ���ش���Ҫͨ��RRC_MM_START_REQ��֪ͨRRC�ͷ���Դ��
              RRC�յ�����Ϣ���ͷ�RRC���ӣ���׼������NAS�������ܽ��е���
              ����ע�᣻
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32          enMsgId;            /*_H2ASN_Skip*/

    LRRC_LMM_BARRED_IND_ENUM_UINT32       enBarInd;
}LRRC_LMM_REL_REQ_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LMM_REL_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RRC_MM_REL_CNF_STRU���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32          enMsgId;          /*_H2ASN_Skip*/
}LRRC_LMM_REL_CNF_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LMM_REL_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �����Ļ��쳣��RRC���������RRC�����ͷţ�ͨ������Ϣ֪ͨNAS��
              ����NAS��RRCû��RRC���ӵ�����£�Ҫ��RRCת��NAS��Ϣ��RRCͨ��
              ����Ϣ֪ͨNAS������ʧ�ܣ���ǰû��RRC����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32          enMsgId;          /*_H2ASN_Skip*/

    LRRC_LNAS_REL_CAUSE_ENUM_UINT32       enRelCause;       /* �����ͷ�ԭ�� */
    /* v7r2 code begin */
    /* extendedWaitTime [1,1800][s]��������ʱĬ��Ϊ0 */
    VOS_UINT16                            usExtendedWaitTime;
    VOS_UINT8                             aucReserved[2];
    /* v7r2 code end */
}LRRC_LMM_REL_IND_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LMM_ERR_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RRC��L1���������쳣��ʹ��RRC_MM_ERR_IND֪ͨNAS��
              NAS�յ�����Ϣ�Ĵ�����NAS�յ�APP_START_REQ��Ϣ�Ĵ���������ͬ
              ����NAS�յ�������NAS��ǰ����Դ�������ʼ�����״̬��NAS����
              ��ɣ�Ȼ���RRC����START_REQ��Ϣ���ٷ���������ע�᣻
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32          enMsgId;          /*_H2ASN_Skip*/

    LRRC_LNAS_ERR_CAUSE_ENUM_UINT32       enErrCause;
}LRRC_LMM_ERR_IND_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LMM_SYS_INFO_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RRC_MM_SYS_INFO_IND_STRU�����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32          enMsgId;          /*_H2ASN_Skip*/

    LRRC_LNAS_AREA_LOST_ENUM_UINT32       enRptMode;        /* ����ģʽ */
}LRRC_LMM_AREA_LOST_IND_STRU;


/*****************************************************************************
 �ṹ��    : LRRC_LMM_SYS_INFO_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RRC_MM_SYS_INFO_IND_STRU�����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32          enMsgId;          /*_H2ASN_Skip*/

    LRRC_LNAS_SUIT_PLMN_ID_LIST_STRU      stSpecPlmnIdList;
    LRRC_LNAS_TAC_STRU                    stTac;              /* Tracking Area Code */
    VOS_UINT32                            ulCellId;           /* Cell Identity */
    VOS_UINT16                            usPhysCellId;       /* physCellId 0-503 */
    VOS_UINT8                             aucResverd[2];
    LRRC_LNAS_CELL_STATUS_ENUM_UINT32     enCellStatusInd;    /* С��״ָ̬ʾ */

    /* LTE��ǰפ����Ƶ�Σ�LTE��Ƶ�ζ���,aulLteBand[0]�����32,
        aulLteBand[1]�����32��Band, ���� �û�����Band1,Band3,
        ��aulLteBand[0]=0x05,aulLteBand[1]=0x00 */
    VOS_UINT32                            aulLteBand[2];

    /*Modify by sunbing 49683 for CL multimode 2014-01-09 begin*/
    VOS_UINT32                           ulArfcn;            /* פ��Ƶ����Ϣ */
    VOS_UINT8                             ucBandWidth;        /* ������Ϣ */
    /*Modify by sunbing 49683 for CL multimode 2014-01-09 end*/

    LRRC_LNAS_ACCESS_MODE_ENUM_UINT8    enAccessType;
    VOS_UINT8                           usResrved[2];
}LRRC_LMM_SYS_INFO_IND_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LMM_PAGING_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RRC_MM_PAGING_IND_STRU�����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32          enMsgId;          /*_H2ASN_Skip*/

    LRRC_LNAS_PAGING_TYPE_ENUM_UINT32     enPagingType;     /* Ѱ����Ϣ����     */
    LRRC_LNAS_PAGING_CAUSE_ENUM_UINT32    enPagingCause;    /* Paging Cause,     */
    LRRC_LNAS_PAGING_UE_ID_ENUM_UINT32    enPagingUeId;     /* Paging Recorder Id*/
}LRRC_LMM_PAGING_IND_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LMM_DATA_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RRC_MM_DATA_REQ_STRU�����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32          enMsgId;          /*_H2ASN_Skip*/
    VOS_UINT32                            ulOpId;
    LRRC_LMM_DATA_CNF_ENUM_UINT32         enDataCnf;

    LRRC_LNAS_MSG_STRU                    stNasMsg;         /* Ҫ���͵�NAS��Ϣ*/
}LRRC_LMM_DATA_REQ_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LMM_DATA_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RRC_MM_DATA_CNF_STRU�����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32          enMsgId;          /*_H2ASN_Skip*/
    VOS_UINT32                            ulOpId;
    LRRC_LMM_SEND_RSLT_ENUM_UINT32        enSendRslt;
}LRRC_LMM_DATA_CNF_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LMM_DATA_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RRC_MM_DATA_IND_STRU�����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32          enMsgId;          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_STRU                    stNasMsg;
}LRRC_LMM_DATA_IND_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LMM_SECURITY_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RRC_MM_SECURITY_IND_STRU�����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32               enMsgId;     /*_H2ASN_Skip*/

    LRRC_LNAS_SECURITY_RPT_MODE_ENUM_UINT32    enRptMode;   /* ����ģʽ  */
}LRRC_LMM_SECURITY_IND_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LMM_POWER_OFF_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RRC_MM_POWER_OFF_REQ_STRU�����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32          enMsgId;          /*_H2ASN_Skip*/
    VOS_UINT8                             aucRsv[4];
}LRRC_LMM_POWER_OFF_REQ_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LMM_POWER_OFF_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RRC_MM_POWER_OFF_CNF_STRU�����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32          enMsgId;          /*_H2ASN_Skip*/
    VOS_UINT8                             aucReserved[4];
}LRRC_LMM_POWER_OFF_CNF_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LRABM_QOS_UPDATE_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RRC_RABM_QOS_UPDATE_REQ_STRU�����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32          enMsgId;          /*_H2ASN_Skip*/
}LRRC_LRABM_QOS_UPDATE_REQ_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LNAS_RAB_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RRC_NAS_RAB_INFO_STRU���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                            ulRabId;            /* RAB ID, �� LTE�е� EPS ID */
    VOS_UINT32                            ulRbId;             /* ��RAB ��Ӧ��RB ID */
    LRRC_LNAS_RAB_CHANGE_ENUM_UINT32      enRabChangeType;    /* RAB�Ĳ������� */
}LRRC_LNAS_RAB_INFO_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LRABM_RAB_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RRC_RABM_RAB_IND_STRU�����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32          enMsgId;          /*_H2ASN_Skip*/

    VOS_UINT32                            ulRabCnt;         /* ����RAB���������� */
    LRRC_LNAS_RAB_INFO_STRU               astRabInfo[LRRC_LNAS_MAX_RAB_SETUP_NUM];
}LRRC_LRABM_RAB_IND_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LRABM_RAB_RSP_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RRC_RABM_RAB_RSP_STRU���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32          enMsgId;          /*_H2ASN_Skip*/

    VOS_UINT32                            ulRabCnt;         /* ����RAB���� */
    VOS_UINT32                            aulRabId[LRRC_LNAS_MAX_RAB_SETUP_NUM];
}LRRC_LRABM_RAB_RSP_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LMM_ACCESS_GRANT_IND_STRU
 Э����  : ��RRC��Access Barred�������ѡ��RRCʹ�ø�ԭ��֪ͨMM
 ASN.1���� :
 �ṹ˵��  : RRC_MM_CELL_STATUS_IND_STRU���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32           enMsgId;         /*_H2ASN_Skip*/

    LRRC_LNAS_ACCESS_GRANT_ENUM_UINT32     enAccessGrantType;
} LRRC_LMM_ACCESS_GRANT_IND_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LRABM_STATUS_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RRC_RABM_STATUS_IND_STRU�����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32          enMsgId;          /*_H2ASN_Skip*/

    /* RAB��״̬���� */
    LRRC_LNAS_RAB_STATUS_ENUM_UINT32      enStatus;

    /* RAB���� */
    VOS_UINT32                          ulRabCnt;
    VOS_UINT32                          aulRabId[LRRC_LNAS_MAX_RAB_SETUP_NUM];
}LRRC_LRABM_STATUS_IND_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LRABM_STATUS_RSP_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RRC_RABM_STATUS_RSP_STRU�����ݽṹ�����ڶ�RRC_RABM_STATUS_IND_STRU
            ��Ӧ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32          enMsgId;          /*_H2ASN_Skip*/
    LRRC_LNAS_STATUS_RESULT_ENUM_UINT32   enResult;
}LRRC_LRABM_STATUS_RSP_STRU;


/*****************************************************************************
 �ṹ��    : LRRC_LMM_SUSPEND_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LRRC_LMM_SUSPEND_IND_STRU����֪ͨLMM��������ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32            enMsgId;        /*_H2ASN_Skip*/

    VOS_UINT32                              bitOpHoSecuPara : 1;
    VOS_UINT32                              bitSpare        : 31;

    LRRC_LMM_SUS_SYS_CHNG_DIR_ENUM_UINT32   enSysChngDir;
    LRRC_LMM_SYS_CHNG_TYPE_ENUM_UINT32      enSysChngType;
    LRRC_LMM_SUS_CAUSE_ENUM_UINT32          enSusCause;

    LRRC_LMM_HO_SECU_PARA_STRU              stHoSecuPara;
} LRRC_LMM_SUSPEND_IND_STRU;

/*****************************************************************************
 �ṹ����   : LRRC_LMM_SUSPEND_RSP_STRU
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : LMM��LRRC_LMM_SUSPEND_IND_STRU����Ӧ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32            enMsgId;        /*_H2ASN_Skip*/

    LRRC_LNAS_RESULT_ENUM_UINT32            enRslt;
} LRRC_LMM_SUSPEND_RSP_STRU;

/*****************************************************************************
 �ṹ����   : LRRC_LMM_RESUME_IND_STRU
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : LRRC_LMM_RESUME_IND_STRU����֪ͨLMM��ҵ����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32            enMsgId;        /*_H2ASN_Skip*/
    LRRC_LMM_RSM_SYS_CHNG_DIR_ENUM_UINT32   enRsmDir;
    LRRC_LMM_SYS_CHNG_TYPE_ENUM_UINT32      enResumeType;
    LRRC_LMM_CSFB_RESULT_ENUM_UINT32        enCsfbRslt;
} LRRC_LMM_RESUME_IND_STRU;

/*****************************************************************************
 �ṹ����   : LRRC_LMM_RESUME_RSP_STRU
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : LMM��LRRC_LMM_RESUME_RSP_STRU����Ӧ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32            enMsgId;        /*_H2ASN_Skip*/

    VOS_UINT32                              ulRsv;
} LRRC_LMM_RESUME_RSP_STRU;

/*****************************************************************************
 �ṹ����   : LRRC_LMM_SUSPEND_REQ_STRU
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : LRRC_LMM_SUSPEND_REQ_STRU����֪ͨLRRC��ϵͳ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32            enMsgId;        /*_H2ASN_Skip*/

    VOS_UINT32                              ulRsv;
} LRRC_LMM_SUSPEND_REQ_STRU;

/*****************************************************************************
 �ṹ����   : LRRC_LMM_SUSPEND_CNF_STRU
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : LRRC��LRRC_LMM_SUSPEND_CNF_STRU����Ӧ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32            enMsgId;        /*_H2ASN_Skip*/

    VOS_UINT32                              ulRsv;
} LRRC_LMM_SUSPEND_CNF_STRU;

/* MBMS Begin */
/*****************************************************************************
 �ṹ����   : LRRC_LMM_MBMS_SESSION_CFG_REQ_STRU
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : LRRC_LMM_MBMS_SESSION_CFG_REQ_STRU����֪ͨLRRC MBMS������ֹͣ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32            enMsgId;        /*_H2ASN_Skip*/

    LRRC_LNAS_MBMS_SESSION_CFG_ENUM_UINT32  enSessionCfg;
} LRRC_LMM_MBMS_SESSION_CFG_REQ_STRU;

/*****************************************************************************
 �ṹ����   : LRRC_LMM_SUSPEND_CNF_STRU
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : LRRC��LRRC_LMM_SUSPEND_CNF_STRU����Ӧ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32            enMsgId;        /*_H2ASN_Skip*/

    VOS_UINT32                              ulRsv;
} LRRC_LMM_MBMS_SESSION_CFG_CNF_STRU;

/*****************************************************************************
 �ṹ����   : LRRC_LMM_SUSPEND_CNF_STRU
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : LRRC��LRRC_LMM_SUSPEND_CNF_STRU����Ӧ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32            enMsgId;        /*_H2ASN_Skip*/

    VOS_UINT32                              ulRsv;
} LRRC_LMM_MBMS_SESSION_IND_STRU;

/* MBMS End */

/*****************************************************************************
 �ṹ����   : LRRC_LMM_SECU_PARA_IND_STRU
 Э����   : ��GU�л���L,LRRC��LNAS�ϱ���ȫ����
 ASN.1 ���� :
 �ṹ˵��   : 24301 9.9.2.7 NAS security parameters to E-UTRA
                8 |  7 |  6 |  5 |  4 |  3 |  2 |  1 |
              ----------------------------------------------
                          NonceMME value                      octet 1-4
              ----------------------------------------------
                0 |              |  0 |
             spare|    EEA       |spare|    EIA       |       octet 5
              ----------------------------------------------
               |0 |  0 |  0 |  0 |TSC |NAS key set identifier octet 6
              ----------------------------------------------
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32            enMsgId;        /*_H2ASN_Skip*/

    VOS_UINT8                               aucSecuPara[LRRC_LNAS_GU2L_HO_SECU_PARA_LEN];
    VOS_UINT8                               aucRsv[2];
} LRRC_LMM_SECU_PARA_IND_STRU;

/*****************************************************************************
 �ṹ����   : LRRC_LMM_SECU_PARA_RSP_STRU
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : ��ϵͳHO�����£�LNASͨ������Ϣ֪ͨLRRC, Kasme�� UP_NASCOUNT
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32            enMsgId;        /*_H2ASN_Skip*/

    LRRC_LNAS_SECURITY_KEY_STRU             stSecuKey;
} LRRC_LMM_SECU_PARA_RSP_STRU;

/*****************************************************************************
 �ṹ����: LRRC_LNAS_SYS_CFG_REQ_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��:
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32        ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    /* ��AT�����Ȼͬʱ����RAT��BAND���˴���bitop��Ȼͬʱ��1�� */
    VOS_UINT32                          bitOpRat:1;
    VOS_UINT32                          bitOpBand:1;
    VOS_UINT32                          bitSpare:30;

    NAS_RRC_USER_SET_FREQ_BAND_STRU     stBand;                                 /* Ƶ�� */
    LRRC_LNAS_RAT_PRIO_ENUM_UINT8       aucRatPrioList[LRRC_LNAS_RAT_TYPE_BUTT];/* ��ģ�����ȼ� */
    /* add for Balong CL begin */
    LRRC_LNAS_UTRAN_MODE_ENUM_UINT8     enUtranMode;
    /* add for Balong CL end */
    /*Modify by sunbing 49683 for CL multimode 2014-01-09 begin*/
    VOS_UINT8                           aucReserved[2];                         /* �ֽڶ��� */
    /*Modify by sunbing 49683 for CL multimode 2014-01-09 end*/
} LRRC_LNAS_SYS_CFG_REQ_STRU;

/*****************************************************************************
 �ṹ��    :  LRRC_LNAS_SYS_CFG_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32        enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    LRRC_LNAS_RESULT_ENUM_UINT32         enRslt;            /* Ŀǰ�Ľӿڣ�ֻ��ɹ� */
    LRRC_LNAS_SUSPEND_NOTIFY_ENUM_UINT32 enSusNotify;       /* �Ƿ����LTE */
    /* gaojishan-2011-12-01-for-SYSCFG-Begin  */
    /* ָʾEUTRAN��UTRAN��GERAN���߽��������Ƿ��б仯��
            ��enSusNotifyָʾ��Ҫ����LTEʱ���ֶ���Ч��
           bit0��bit1��bit2�ֱ��ʶEUTRAN��UTRAN��GERAN��ģ���������Ƿ��б�,��λԤ��
           '0'bit:��ʶ�ޱ仯��'1'bit��ʶ�б仯
           eg. ucRadioAccCapChgInd = 6(dec)����ʾ UTRAN��GERAN�б仯��EUTRAN�ޱ仯 */

    VOS_UINT8                           ucRadioAccCapChgInd;
    VOS_UINT8                           aucRsvd[3];
    /* gaojishan-2011-12-01-for-SYSCFG-End  */
}LRRC_LNAS_SYS_CFG_CNF_STRU;


/*****************************************************************************
 �ṹ����   : LRRC_LMM_OOS_STATE_REQ_STRU
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : �������������֪ͨLRRC �л�����ģ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32            enMsgId;        /*_H2ASN_Skip*/

    VOS_UINT8                               aucReservered[4];
} LRRC_LMM_OOS_STATE_REQ_STRU;
/*****************************************************************************
 �ṹ����   : LRRC_LMM_CLEAR_BUFF_NOTIFY_STRU
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : ATTACH_COMPLETE����ʧ�ܣ�TA���ͱ仯��֪ͨLRRC�建��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32            enMsgId;        /*_H2ASN_Skip*/

    VOS_UINT8                               aucReservered[4];
} LRRC_LMM_CLEAR_BUFF_NOTIFY_STRU;

/* lishangfeng bg begin */

/*****************************************************************************
 �ṹ��    :  LRRC_LNAS_NOT_CAMP_ON_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32        enMsgId;            /*_H2ASN_Skip*/

    VOS_UINT8                           aucReservered[4];
}LRRC_LNAS_NOT_CAMP_ON_IND_STRU;

/*****************************************************************************
�ṹ��    :LRRC_LMM_PLMN_ID_WITH_RAT_STRU
Э����  :
ASN.1���� :
�ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucPlmnId[3];
    LRRC_LNAS_RAT_TYPE_ENUM_UINT8       enPlmnRat;
}LRRC_LMM_PLMN_ID_WITH_RAT_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LMM_BG_PLMN_SEARCH_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LRRC_LMM_BG_PLMN_SEARCH_REQ_STRU���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32        enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    /* ָ��PLMN ID�����뼼�� */
    LRRC_LMM_PLMN_ID_WITH_RAT_STRU      stSpecPlmnWithRat;

    /* ��ֹע�����ĸ���,������LTE����ʱ��Ч */
    VOS_UINT32                          ulForbRoamLaiNum;

    /* ��ֹLAI��Ϣ,������LTE����ʱ��Ч */
    LRRC_LNAS_LA_STRU                   astForbRoamLaiList[LRRC_LNAS_BG_MAX_FORBLA_NUM];
}LRRC_LMM_BG_PLMN_SEARCH_REQ_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LMM_BG_PLMN_SEARCH_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LRRC_LMM_BG_PLMN_SEARCH_CNF_STRU���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32        enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    /* ������� */
    LRRC_LMM_BG_SRCH_RLT_ENUM_UINT32    enRlst;

    /* spec plmn����ʧ��ʱ��������Ч */
    VOS_UINT32                          ulPlmnNum;
    LRRC_LMM_PLMN_ID_WITH_RAT_STRU      astPlmnIdWithRatList[LRRC_LNAS_BG_MAX_SRCH_PLMN_NUM];
} LRRC_LMM_BG_PLMN_SEARCH_CNF_STRU;

/*****************************************************************************
�ṹ��    : LRRC_LMM_BG_PLMN_SEARCH_REQ_STOP_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :LRRC_LMM_BG_PLMN_SEARCH_REQ_STOP_STRU
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32        enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    VOS_UINT8                           aucRsv[4];
} LRRC_LMM_BG_PLMN_SEARCH_REQ_STOP_STRU;
/*****************************************************************************
 �ṹ����   : LRRC_LMM_SUSPEND_REL_REQ_STRU
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : LRRC_LMM_SUSPEND_REL_REQ����֪ͨLRRCֹͣL��GU���ض�������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32            enMsgId;        /*_H2ASN_Skip*/

    VOS_UINT8                               aucRsv[4];
} LRRC_LMM_SUSPEND_REL_REQ_STRU;


/*****************************************************************************
 �ṹ��    : LRRC_LMM_BG_PLMN_SEARCH_STOP_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LRRC_MMC_BG_PLMN_SEARCH_STOP_CNF_STRU �����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32        enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    VOS_UINT8                           aucRsv[4];
} LRRC_LMM_BG_PLMN_SEARCH_STOP_CNF_STRU;

/* lishangfeng bg end */

/*****************************************************************************
 �ṹ��    : LRRC_NAS_AC_CLASS_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : AC����
*****************************************************************************/
typedef struct
{
    /* Access control class���ӵ�λ����λ���ֱ���� 0~15 �����뼶��,An AC is "allocated"
       if the corresponding bit is set to 1 and "not allocated" if this bit is set to 0. */
    VOS_UINT16                          usAccClassMask;
    VOS_UINT8                           aucRsvd[2];
}LRRC_NAS_AC_CLASS_STRU;


typedef struct
{
    VOS_MSG_HEADER                                             /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32            enMsgId;           /*_H2ASN_Skip*/
    LRRC_LNAS_UTRAN_MODE_ENUM_UINT8         enUtranMode;       /* UTRAN�Ĺ���ģʽ*/
    VOS_UINT8                               aucRsv[3];
} LRRC_LMM_UTRAN_MODE_REQ_STRU;


typedef struct
{
    VOS_MSG_HEADER                                             /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32               enMsgId;        /*_H2ASN_Skip*/
    LRRC_LNAS_CAPABILITY_CHANGE_ENUM_UINT32    enCapChangeInd;     /* ָʾUE�����Ƿ��͸ı�*/
}LRRC_LMM_UTRAN_MODE_CNF_STRU;

/*****************************************************************************
 �ṹ����   : LRRC_LMM_SUSPEND_REL_CNF_STRU
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : LRRC_LMM_SYSPEND_REL_CNF����֪ͨLMMֹͣL��GU���ض������̳ɹ�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32            enMsgId;        /*_H2ASN_Skip*/

    VOS_UINT8                               aucRsv[4];
} LRRC_LMM_SUSPEND_REL_CNF_STRU;



/*****************************************************************************
 �ṹ����   : LRRC_LMM_RAT_CHANGE_IND_STRU
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : LRRC_LMM_RAT_CHANGE_IND_STRU����֪ͨLMM�ײ�Ľ��뼼�������仯
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32            enMsgId;        /*_H2ASN_Skip*/

    LRRC_LNAS_SUSPEND_INFO_CHANGE_TYPE_ENUM_UINT32  ulInfoType;/*��Ϣ������� : CSFB_REDIR_RAT_CHANGE;*/
    LRRC_LNAS_RAT_CHANGE_TYPE_ENUM_UINT32   ulRatChangeType;/* ö�٣�����ֵ��U2G, G2U*/
    VOS_UINT8                               aucRsv[4];      /* Ԥ�� */
}LRRC_LMM_SUSPEND_INFO_CHANGE_IND_STRU;

/*****************************************************************************
 �ṹ����: LMM_LRRC_OTHER_MODEM_INFO_NOTIFY_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��:
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                         /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32    ulMsgId;               /*_H2ASN_Skip*/
    VOS_UINT32                      bitOpCurrCampPlmnId:1;
    VOS_UINT32                      bitSpare:31;
    LRRC_LNAS_PLMN_ID_STRU        stCurrCampPlmnId;
}LMM_LRRC_OTHER_MODEM_INFO_NOTIFY_STRU;

/* add for LTE NetScan begin */
/*****************************************************************************
 �ṹ����  : LRRC_LMM_NETSCAN_REQ_STRU;
 �ṹ˵��  : LTE LRRC_LMM_NETSCAN_REQ_STRU�ṹ��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                        /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32      enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                        aulLteBand[2];      /* ����ȡֵͬ�ӿ�RRMM_SYS_CFG_REQ_STRU��Ƶ�β���һ����LTE_BAND_STRU*/
    VOS_UINT16                        usCellNum;          /* ��Ҫɨ����������޵�С����������������Ϊ20*/
    VOS_INT16                         sCellPow;           /* С������ֵ:������յ�����RSRP������*/
    LRRC_LNAS_BOOL_ENUM_UINT8         enLteRat;           /* 0:����ģʽ����LTE��1: ����ģʽ��LTE */
    VOS_UINT8                         aucReserve[3];
}LRRC_LMM_NETSCAN_REQ_STRU;


/*****************************************************************************
 �ṹ��    : LRRC_LMM_NETSCAN_INFO_STRU;
 �ṹ˵��  : LTE LRRC_LMM_NETSCAN_INFO_STRU CNF�ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT16                       usArfcn;/*Frequency Channel Number��EARFCN��*/
    VOS_UINT16                       usTac;  /*Tracking Area Code,����������*/
    VOS_UINT32                       ulMcc;
    VOS_UINT32                       ulMnc;
    VOS_UINT32                       ulCI;   /*string type; four byte GERAN/UTRAN/E-UTRAN cell ID in hexadecimal format,RRC_SIB_TYPE1: cell identity������ҵ�����������ʹ��*/
    VOS_UINT32                       aulBand[2]; /* ����ȡֵͬ�ӿ�RRMM_SYS_CFG_REQ_STRU��Ƶ�β���һ����LTE_BAND_STRU*/
    VOS_UINT32                       ulPci;  /*L��Ҫʹ��physical cell id��Ƶ������ȷ��һ��С��*/
    VOS_INT16                        sRxlev;/*receive signal level (dBm)*/
    VOS_INT16                        sRsrp; /*RSRP:Parameter determines the received signal code power level of the cell that was scanned, range from -140 dBm to -44 dBm*/
}LRRC_LMM_NETSCAN_INFO_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LMM_NETSCAN_CNF_STRU;
 �ṹ˵��  : LTE LRRC_LMM_NETSCAN_CNF_STRU CNF�ṹ��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                           /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32             enMsgId;        /*_H2ASN_Skip*/
    LRRC_LNAS_NETSCAN_RESULT_ENUM_UINT8      enResult;
    LRRC_LNAS_NETSCAN_CAUSE_ENUM_UINT8       enCause;
    VOS_UINT8                                ucFreqNum;
    VOS_UINT8                                aucReserve[1];
    LRRC_LMM_NETSCAN_INFO_STRU               astNetScanInfo[LRRC_LNAS_NETSCAN_MAX_FREQ_NUM];
}LRRC_LMM_NETSCAN_CNF_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LMM_NETSCAN_STOP_REQ_STRU
 �ṹ˵��  : LMM��������ֹͣ��������ɨ����Ϣ�ṹ��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32        enMsgId;            /*_H2ASN_Skip*/
}LRRC_LMM_NETSCAN_STOP_REQ_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LMM_NETSCAN_STOP_CNF_STRU
 �ṹ˵��  : LRRC�����ֹͣɨ�����ظ���Ϣ�ṹ��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32        enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                           ucFreqNum;
    VOS_UINT8                           aucReserve[3];
    LRRC_LMM_NETSCAN_INFO_STRU          astNetScanInfo[LRRC_LNAS_NETSCAN_MAX_FREQ_NUM];
}LRRC_LMM_NETSCAN_STOP_CNF_STRU;
/* add for LTE NetScan end */

/* add for AT&T LRRC DAM begin */
/*****************************************************************************
 �ṹ����: LRRC_LMM_DISABLE_LTE_NOTIFY_STRU
 Э����: ����AT&T��������֪ͨLRRC LTE��disable
 ASN.1 ����:
 �ṹ˵��:
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                        /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32    ulMsgId;              /*_H2ASN_Skip*/

    VOS_UINT32                      ulRsv;
}LRRC_LMM_DISABLE_LTE_NOTIFY_STRU;
/* add for AT&T LRRC DAM end */


/*chengmin add for L signal report begin*/
/*****************************************************************************
 �ṹ����   : LRRC_LMM_CELL_SIGN_REPORT_NOTIFY_STRU
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : ID_LRRC_LMM_CELL_SIGN_REPORT_NOTIFY��Ӧ�ṹ�壬����֪ͨLRRC�ź������ϱ�������ֵ��ʱ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32    ulMsgId;                /*_H2ASN_Skip*/
    VOS_UINT8                       ucMinRptTimerInterval;  /*ʱ������Ϊ0ʱ:RSSI�仯�ﵽ����ֵʱ�����ϱ�������ȡֵ����*/
    VOS_UINT8                       ucSignThreshold;        /*����ֵ��Ϊ0ʱ:���֮ǰû�и������֪ͨ����Чֵ(1-5db),�������
                                                              NV����ֵ�����֮ǰ�������֪ͨ����Чֵ���������Ȼ���ϴε���Чֵ*/
    VOS_UINT8                       aucRsv[2];
}LRRC_LMM_CELL_SIGN_REPORT_NOTIFY_STRU;

/*****************************************************************************
 �ṹ����   : LRRC_LMM_CQI_INFO_STRU
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : LTE�µ��ŵ��������������ֱַ�����Ӵ�CQI�Ϳ��CQI
*****************************************************************************/
typedef struct
{
    VOS_UINT16                      usRI;                   /*RIֵ��1ʱ��ausCQI[0]��Ч��2ʱausCQI[0]��ausCQI[1]����Ч*/
    VOS_UINT8                       aucRes[2];
    VOS_UINT16                      ausCQI[2];
}LRRC_LMM_CQI_INFO_STRU;

/*****************************************************************************
 �ṹ����   : LRRC_LMM_CELL_SIGN_REPORT_IND_STRU
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : ID_LRRC_LMM_CELL_SIGN_REPORT_IND��Ӧ�ṹ�壬LTE�µ�Rssi��Rsrp��Rsrq��CQI
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                            /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32        ulMsgId;              /*_H2ASN_Skip*/
    VOS_INT16                           sRssi;                /**/
    VOS_INT16                           sRsd;                 /*����ֶ�*/
    VOS_INT16                           sRsrp;                /*��Χ(-141,-44),99Ϊ��Ч*/
    VOS_INT16                           sRsrq;                /*��Χ(-40,-6),99Ϊ��Ч*/
    VOS_INT32                           lSinr;
    LRRC_LMM_CQI_INFO_STRU              stCQI;
}LRRC_LMM_CELL_SIGN_REPORT_IND_STRU;
/*chengmin add for L signal report end*/

/*****************************************************************************
 �ṹ��    : LRRC_LMM_EXPERIENCE_SPEC_REQ
 �ṹ˵��  : LMM�·���RRC���漰�û������ָʾ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32         enMsgId;           /*_H2ASN_Skip*/
    LRRC_LMM_EXPERIENCE_SPEC_REQ_TYPE_ENUM_UINT32  enSpecReq;
    VOS_UINT16                           usRsv0;
    VOS_UINT16                           usRsv1;
    VOS_UINT8                            ausData[4];
}LRRC_LMM_EXPERIENCE_SPEC_REQ;

/*****************************************************************************
 �ṹ��    : LRRC_LMM_BG_SEARCH_HRPD_REQ_STRU
 �ṹ˵��  : LMM��LRRC�·��ı�����EHRPD�������Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32        enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    VOS_UINT8                           ausData[4];
}LRRC_LMM_BG_SEARCH_HRPD_REQ_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LMM_BG_SEARCH_HRPD_STOP_REQ_STRU
 �ṹ˵��  : LMM��LRRC�·���ֹͣ������EHRPD�������Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32        enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    VOS_UINT8                           ausData[4];
}LRRC_LMM_BG_SEARCH_HRPD_STOP_REQ_STRU;


typedef struct
{
    VOS_UINT32                            ulTaiNum;            /* Plmn�ĸ���    */
    LRRC_LNAS_TA_STRU                     stTaiList[LRRC_LMM_MAX_SEARCHED_TAI_NUM];
}LRRC_LNAS_OPT_INFO_TAILIST_STRU;


/*****************************************************************************
 �ṹ��    : LRRC_LMM_INTER_OPT_IND
 �ṹ˵��  : LRRC��LMMָʾ�������������̵ĳɹ���ʧ��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                            /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32          enMsgId;            /*_H2ASN_Skip*/
    LRRC_LNAS_INTER_OPT_TYPE_ENUM_UINT32  enInterOptType;
    VOS_UINT32                            ulBitOpTaList :1;
    VOS_UINT32                            ulBitRsv :1;
    VOS_UINT32                            ulBitRsv1:1;
    VOS_UINT32                            ulBitRsv2:1;
    VOS_UINT32                            ulBitRsv3:28;

    VOS_UINT32                            ulRsv;
    VOS_UINT16                            usRsv0;
    VOS_UINT16                            usRsv1;

    LRRC_LNAS_OPT_INFO_TAILIST_STRU       stOptInfoTaiList;
}LRRC_LMM_INTER_OPT_IND;

typedef struct
{
    LRRC_LNAS_MSG_ID_ENUM_UINT32        enMsgID;            /*_H2ASN_MsgChoice_Export LRRC_LNAS_MSG_ID_ENUM_UINT32*/
    VOS_UINT8                           aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          LRRC_LNAS_MSG_ID_ENUM_UINT32
    ****************************************************************************/
}LRRC_LNAS_MSG_DATA;
/*_H2ASN_Length UINT32*/


typedef struct
{
    VOS_MSG_HEADER
    LRRC_LNAS_MSG_DATA                    stMsgData;
} RrcNasInterface_MSG;
/*****************************************************************************
 �ṹ��    : LRRC_LMM_CSFB_NOTIFY_STRU
 �ṹ˵��  : LMM֪ͨLRRC CSFB���������Լ�����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                            /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32          enMsgId;            /*_H2ASN_Skip*/
    LRRC_LNAS_CSFB_STATUS_ENUM_UINT16     enCsfbStatus;
    VOS_UINT16                            usRsv;
}LRRC_LMM_CSFB_NOTIFY_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LMM_HRPD_SYS_STRU
 �ṹ˵��  : EHRPD���������
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucSubnetId[LRRC_LMM_HRPD_SUBNET_MAX_LEN];
    VOS_UINT16                          usBandClass;
    VOS_UINT16                          usFreq;
}LRRC_LMM_HRPD_SYS_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LMM_BG_SEARCH_HRPD_CNF_STRU
 �ṹ˵��  : LRRC��LMM�ظ��ı�����EHRPD�����Ϣ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32        enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    LRRC_LMM_BG_SRCH_RLT_ENUM_UINT32    enRslt;

    VOS_UINT8                           ucHrpdSysNum;
    VOS_UINT8                           aucRsv[3];
    LRRC_LMM_HRPD_SYS_STRU              astHrpdSysList[LRRC_LMM_BG_HRPD_MAX_SUBNET_NUM];

}LRRC_LMM_BG_SEARCH_HRPD_CNF_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LMM_BG_SEARCH_HRPD_STOP_CNF_STRU
 �ṹ˵��  : LRRC��LMM�ظ���ֹͣ������EHRPDȷ����Ϣ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LRRC_LNAS_MSG_ID_ENUM_UINT32        enMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    VOS_UINT8                           aucRsv[4];
}LRRC_LMM_BG_SEARCH_HRPD_STOP_CNF_STRU;


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
 Function Name  : LRRC_LNAS_GetMmInfo
 Discription    : ������ģ���ṩ�ӿڣ�ʹ������ģ���ܻ�ȡUE ��ID��Ϣ��C03�汾
                  Ŀǰֻ��IMSI��Ϣ��
 Input          : LRRC_LNAS_INFO_TYPE_ENUM_UINT32  ulInfoType
 Output         : None
 Return         : VOS_NULL:  ��ȡʧ��
                  ����    :  LRRC_NAS_UEID_STRU * ,ָ��IMSI����,
                             g_stGmmStaticPara.stGmmUeId,�׵�ַ��ָ��
 History:
*****************************************************************************/
VOS_VOID*  LRRC_LNAS_GetMmInfo( LRRC_LNAS_INFO_TYPE_ENUM_UINT32  enInfoType );
extern LRRC_LNAS_SMC_CTRL_ENUM_UINT8 LRRC_LNAS_GetSmcState( VOS_VOID );

extern LRRC_LNAS_RESULT_ENUM_UINT32  LRRC_GetEutraUeCap(
        const LRRC_LNAS_PLMN_ID_STRU stPlmnId, VOS_UINT16 *pusDataLen, VOS_UINT8 *pucEncData );



extern VOS_UINT8 LRRC_LNAS_GetPowerOffFlag(VOS_VOID);

/* add for AT&T LRRC DAM begin */
extern VOS_UINT8 LRRC_LNAS_IsDamConfitionSatisfied(VOS_VOID);
/* add for AT&T LRRC DAM end */

/* zhaochen 00308719 begin for SMS Message hook */
extern VOS_UINT8 LRRC_LNAS_IsMsgContainsSMS(VOS_UINT32 ulMsgSize, VOS_UINT8 *pstMsg);
/* zhaochen 00308719 end for SMS Message hook */

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

#endif /* end of ����ģ��+����ģ��+Interface.h */

