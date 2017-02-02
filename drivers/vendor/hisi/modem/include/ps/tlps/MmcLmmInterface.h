
#ifndef __MMCLMMINTERFACE_H__
#define __MMCLMMINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  #pragma pack(*)    �����ֽڶ��뷽ʽ
*****************************************************************************/
/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include "LPSCommon.h"
#include "ComInterface.h"

#include "PsTypeDef.h"

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 Macro
*****************************************************************************/
    /* ��ЧPLMN�����*/
#define MMC_LMM_MAX_EQUPLMN_NUM         (16)

    /* ָ��PLMN�ϱ��Ĺ���PLMN����� */
#define MMC_LMM_MAX_SRCH_PLMN_NUM       (16)

    /* ����PLMN�����ϱ���PLMN����� */
#define MMC_LMM_MAX_BG_SRCH_PLMN_NUM    (16)

    /* ��������GU PLMNʱ���Ľ�ֹLAI���� */
#define MMC_LMM_MAX_FORB_ROAM_LAI_NUM   (16)

    /* ������PLMN����� */
#define MMC_LMM_MAX_HIGH_PLMN_NUM       (48)

    /* ������PLMN����� */
#define MMC_LMM_MAX_LOW_PLMN_NUM        (48)
#define MMC_LMM_PLMN_ID_LEN             (3)

#define NAS_MAX_SIZE_PTMSI              (4)

#define NAS_MAX_SIZE_MS_IDENTITY        (9)


#define NAS_MAX_SIZE_PTMSI_SIGNATURE    (3)

#define NAS_UMTS_CK_LENGTH              (16)
#define NAS_UMTS_IK_LENGTH              (16)
#define MMC_LMM_MAX_PLMN_NUM            (64)

#define MMC_LMM_MAX_RAT_NUM             (3)

#define MMC_LMM_MAX_FORB_ROAM_TAI_NUM   (64)
#define MMC_LMM_MAX_FORB_RPOS_TAI_NUM   (64)

#define MMC_LMM_MAX_OPER_LONG_NAME_LEN       (100)
#define MMC_LMM_MAX_OPER_SHORT_NAME_LEN      (100)

#define  MMC_LMM_LTE_ARFCN_MAX_NUM      (8)                 /* LTEƵ���б������� */

/*Modify by sunbing 49683 for CL multimode 2014-01-09 begin*/
#define  MMC_LMM_LTE_CELL_ID_MAX_NUM      (8)               /* LTEС��ID�б������� */
/*Modify by sunbing 49683 for CL multimode 2014-01-09 end*/

#define LMM_MMC_EMERGENCY_NUM_MAX_LEN            (46)
#define LMM_MMC_EMERGENCY_NUM_LIST_MAX_RECORDS   (16)

#define LMM_MMC_MAX_SEARCHED_TAI_NUM            (16)

#define MMC_LMM_MAX_EUTRAN_NOT_ALLOW_PLMN_NUM   (16)
#define LMM_MMC_HRPD_SUBNET_MAX_LEN             (16)
#define LMM_MMC_BG_HRPD_MAX_SYS_NUM             (16)
/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
enum    MMC_LMM_MSG_ID_ENUM
{
    /* MMC����LMM����Ϣԭ�� */
    ID_MMC_LMM_START_REQ                = (PS_MSG_ID_MMC_TO_LMM_BASE+0x01),     /* _H2ASN_MsgChoice MMC_LMM_START_REQ_STRU */
    ID_MMC_LMM_STOP_REQ                 = (PS_MSG_ID_MMC_TO_LMM_BASE+0x02),     /* _H2ASN_MsgChoice MMC_LMM_STOP_REQ_STRU */
    ID_MMC_LMM_PLMN_SRCH_REQ            = (PS_MSG_ID_MMC_TO_LMM_BASE+0x03),     /* _H2ASN_MsgChoice MMC_LMM_PLMN_SRCH_REQ_STRU */
    ID_MMC_LMM_STOP_PLMN_SRCH_REQ       = (PS_MSG_ID_MMC_TO_LMM_BASE+0x04),     /* _H2ASN_MsgChoice MMC_LMM_STOP_PLMN_SRCH_REQ_STRU */
    ID_MMC_LMM_EPLMN_NOTIFY_REQ         = (PS_MSG_ID_MMC_TO_LMM_BASE+0x05),     /* _H2ASN_MsgChoice MMC_LMM_EPLMN_NOTIFY_REQ_STRU */
    ID_MMC_LMM_CELL_SELECTION_CTRL_REQ  = (PS_MSG_ID_MMC_TO_LMM_BASE+0x06),     /* _H2ASN_MsgChoice MMC_LMM_CELL_SELECTION_CTRL_REQ_STRU */
    ID_MMC_LMM_ACTION_RESULT_REQ        = (PS_MSG_ID_MMC_TO_LMM_BASE+0x07),     /* _H2ASN_MsgChoice MMC_LMM_ACTION_RESULT_REQ_STRU */
    ID_MMC_LMM_REL_REQ                  = (PS_MSG_ID_MMC_TO_LMM_BASE+0x08),     /* _H2ASN_MsgChoice MMC_LMM_REL_REQ_STRU */
    ID_MMC_LMM_SUSPEND_REQ              = (PS_MSG_ID_MMC_TO_LMM_BASE+0x09),     /* _H2ASN_MsgChoice MMC_LMM_SUSPEND_REQ_STRU */
    ID_MMC_LMM_CSFB_REQ                 = (PS_MSG_ID_MMC_TO_LMM_BASE+0x0A),     /* _H2ASN_MsgChoice MMC_LMM_CSFB_REQ_STRU */
    ID_MMC_LMM_SYS_CFG_REQ              = (PS_MSG_ID_MMC_TO_LMM_BASE+0x0B),     /* _H2ASN_MsgChoice MMC_LMM_SYS_CFG_REQ_STRU */
    ID_MMC_LMM_USIM_STATUS_REQ          = (PS_MSG_ID_MMC_TO_LMM_BASE+0x0C),     /* _H2ASN_MsgChoice MMC_LMM_USIM_STATUS_REQ_STRU */
    ID_MMC_LMM_ATTACH_REQ               = (PS_MSG_ID_MMC_TO_LMM_BASE+0x0D),     /* _H2ASN_MsgChoice MMC_LMM_ATTACH_REQ_STRU */
    ID_MMC_LMM_DETACH_REQ               = (PS_MSG_ID_MMC_TO_LMM_BASE+0x0E),     /* _H2ASN_MsgChoice MMC_LMM_DETACH_REQ_STRU */
    ID_MMC_LMM_RESUME_NOTIFY            = (PS_MSG_ID_MMC_TO_LMM_BASE+0x0F),     /* _H2ASN_MsgChoice MMC_LMM_RESUME_NOTIFY_STRU */
    ID_MMC_LMM_SUSPEND_RSP              = (PS_MSG_ID_MMC_TO_LMM_BASE+0x10),     /* _H2ASN_MsgChoice MMC_LMM_SUSPEND_RSP_STRU*/
    ID_MMC_LMM_DISABLE_LTE_NOTIFY       = (PS_MSG_ID_MMC_TO_LMM_BASE+0x11),     /* _H2ASN_MsgChoice MMC_LMM_DISABLE_LTE_NOTIFY_STRU*/
    ID_MMC_LMM_ENABLE_LTE_NOTIFY        = (PS_MSG_ID_MMC_TO_LMM_BASE+0x12),     /* _H2ASN_MsgChoice MMC_LMM_ENABLE_LTE_NOTIFY_STRU*/
    ID_MMC_LMM_USER_PLMN_END_NOTIFY     = (PS_MSG_ID_MMC_TO_LMM_BASE+0x13),     /* _H2ASN_MsgChoice MMC_LMM_USER_PLMN_END_NOTIFY_STRU*/
    ID_MMC_LMM_UE_OOC_STATUS_NOTIFY     = (PS_MSG_ID_MMC_TO_LMM_BASE+0x14),     /* _H2ASN_MsgChoice MMC_LMM_UE_OOC_STATUS_NOTIFY_STRU*/
    ID_MMC_LMM_WCDMA_SYS_INFO_IND       = (PS_MSG_ID_MMC_TO_LMM_BASE+0x15),     /* _H2ASN_MsgChoice MMC_LMM_WCDMA_SYS_INFO_IND_STRU*/
    ID_MMC_LMM_GSM_SYS_INFO_IND         = (PS_MSG_ID_MMC_TO_LMM_BASE+0x16),     /* _H2ASN_MsgChoice MMC_LMM_GSM_SYS_INFO_IND_STRU*/
    ID_MMC_LMM_BG_PLMN_SEARCH_REQ       = (PS_MSG_ID_MMC_TO_LMM_BASE+0x17),     /* _H2ASN_MsgChoice MMC_LMM_BG_PLMN_SEARCH_REQ_STRU*/
    ID_MMC_LMM_STOP_BG_PLMN_SEARCH_REQ  = (PS_MSG_ID_MMC_TO_LMM_BASE+0x18),     /* _H2ASN_MsgChoice MMC_LMM_STOP_BG_PLMN_SEARCH_REQ_STRU*/
    ID_MMC_LMM_UTRAN_MODE_REQ           = (PS_MSG_ID_MMC_TO_LMM_BASE+0x19),     /* _H2ASN_MsgChoice MMC_LMM_UTRAN_MODE_REQ_STRU */

    ID_MMC_LMM_SUSPEND_REL_REQ          = (PS_MSG_ID_MMC_TO_LMM_BASE+0x1A),     /* _H2ASN_MsgChoice MMC_LMM_SUSPEND_REL_REQ_STRU */
    ID_MMC_LMM_LTE_SYS_INFO_IND         = (PS_MSG_ID_MMC_TO_LMM_BASE+0x1B),     /* _H2ASN_MsgChoice MMC_LMM_LTE_SYS_INFO_IND_STRU */
    /*ID_SM_ESM_PDP_CONTEXT_INFO_IND                 ,*/       /* _H2ASN_MsgChoice SM_ESM_PDP_CONTEXT_INFO_IND_STRU */

    ID_MMC_LMM_OTHER_MODEM_INFO_NOTIFY  = (PS_MSG_ID_MMC_TO_LMM_BASE+0x1C),     /* _H2ASN_MsgChoice MMC_LMM_OTHER_MODEM_INFO_NOTIFY_STRU*/

    ID_MMC_LMM_IMS_VOICE_CAP_CHANGE_NOTIFY = (PS_MSG_ID_MMC_TO_LMM_BASE+0x1D),     /* _H2ASN_MsgChoice MMC_LMM_IMS_VOICE_CAP_CHANGE_NOTIFY_STRU*/

    ID_MMC_LMM_BEGIN_SESSION_NOTIFY       = (PS_MSG_ID_MMC_TO_LMM_BASE+0x1E),     /* _H2ASN_MsgChoice MMC_LMM_BEGIN_SESSION_NOTIFY_STRU*/
    ID_MMC_LMM_END_SESSION_NOTIFY         = (PS_MSG_ID_MMC_TO_LMM_BASE+0x1F),     /* _H2ASN_MsgChoice MMC_LMM_END_SESSION_NOTIFY_STRU*/
    ID_MMC_LMM_CELL_SIGN_REPORT_NOTIFY  = (PS_MSG_ID_MMC_TO_LMM_BASE+0x20),     /* _H2ASN_MsgChoice MMC_LMM_CELL_SIGN_REPORT_NOTIFY_STRU*/

    ID_MMC_LMM_VOICE_DOMAIN_CHANGE_IND  = (PS_MSG_ID_MMC_TO_LMM_BASE+0x21),     /* _H2ASN_MsgChoice MMC_LMM_VOICE_DOMAIN_CHANGE_IND_STRU*/
    ID_MMC_LMM_CS_CONN_STATUS_NOTIFY    = (PS_MSG_ID_MMC_TO_LMM_BASE+0x23),     /* _H2ASN_MsgChoice MMC_LMM_CS_CONN_STATUS_NOTIFY_STRU*/

    ID_MMC_LMM_BG_SEARCH_HRPD_REQ       = (PS_MSG_ID_MMC_TO_LMM_BASE+0X24),     /* _H2ASN_MsgChoice MMC_LMM_BG_SEARCH_HRPD_REQ_STRU */
    ID_MMC_LMM_STOP_BG_SEARCH_HRPD_REQ  = (PS_MSG_ID_MMC_TO_LMM_BASE+0x25),     /* _H2ASN_MsgChoice MMC_LMM_STOP_BG_SEARCH_HRPD_REQ_STRU */

    /* LMM���͸�MMC����Ϣԭ��*/
    ID_LMM_MMC_START_CNF                = (PS_MSG_ID_LMM_TO_MMC_BASE+0x01),     /* _H2ASN_MsgChoice LMM_MMC_START_CNF_STRU */
    ID_LMM_MMC_STOP_CNF                 = (PS_MSG_ID_LMM_TO_MMC_BASE+0x02),     /* _H2ASN_MsgChoice LMM_MMC_STOP_CNF_STRU */
    ID_LMM_MMC_PLMN_SRCH_CNF            = (PS_MSG_ID_LMM_TO_MMC_BASE+0x03),     /* _H2ASN_MsgChoice LMM_MMC_PLMN_SRCH_CNF_STRU */
    ID_LMM_MMC_STOP_PLMN_SRCH_CNF       = (PS_MSG_ID_LMM_TO_MMC_BASE+0x04),     /* _H2ASN_MsgChoice LMM_MMC_STOP_PLMN_SRCH_CNF_STRU */
    ID_LMM_MMC_AREA_LOST_IND            = (PS_MSG_ID_LMM_TO_MMC_BASE+0x05),     /* _H2ASN_MsgChoice LMM_MMC_AREA_LOST_IND_STRU */
    ID_LMM_MMC_SYS_INFO_IND             = (PS_MSG_ID_LMM_TO_MMC_BASE+0x06),     /* _H2ASN_MsgChoice LMM_MMC_SYS_INFO_IND_STRU */
    ID_LMM_MMC_EMM_INFO_IND             = (PS_MSG_ID_LMM_TO_MMC_BASE+0x07),     /* _H2ASN_MsgChoice LMM_MMC_EMM_INFO_IND_STRU */
    ID_LMM_MMC_ERR_IND                  = (PS_MSG_ID_LMM_TO_MMC_BASE+0x08),     /* _H2ASN_MsgChoice LMM_MMC_ERR_IND_STRU */
    ID_LMM_MMC_EPS_SERVICE_IND          = (PS_MSG_ID_LMM_TO_MMC_BASE+0x09),     /* _H2ASN_MsgChoice LMM_MMC_EPS_SERVICE_IND_STRU */
    ID_LMM_MMC_SUSPEND_IND              = (PS_MSG_ID_LMM_TO_MMC_BASE+0x0A),     /* _H2ASN_MsgChoice LMM_MMC_SUSPEND_IND_STRU */
    ID_LMM_MMC_SUSPEND_CNF              = (PS_MSG_ID_LMM_TO_MMC_BASE+0x0B),     /* _H2ASN_MsgChoice LMM_MMC_SUSPEND_CNF_STRU */
    ID_LMM_MMC_RESUME_IND               = (PS_MSG_ID_LMM_TO_MMC_BASE+0x0C),     /* _H2ASN_MsgChoice LMM_MMC_RESUME_IND_STRU */
    ID_LMM_MMC_STATUS_IND               = (PS_MSG_ID_LMM_TO_MMC_BASE+0x0D),     /* _H2ASN_MsgChoice LMM_MMC_STATUS_IND_STRU */
    ID_LMM_MMC_SYS_CFG_CNF              = (PS_MSG_ID_LMM_TO_MMC_BASE+0x0E),     /* _H2ASN_MsgChoice LMM_MMC_SYS_CFG_CNF_STRU */
    ID_LMM_MMC_USIM_STATUS_CNF          = (PS_MSG_ID_LMM_TO_MMC_BASE+0x0F),     /* _H2ASN_MsgChoice LMM_MMC_USIM_STATUS_CNF_STRU */
    ID_LMM_MMC_ATTACH_CNF               = (PS_MSG_ID_LMM_TO_MMC_BASE+0x10),     /* _H2ASN_MsgChoice LMM_MMC_ATTACH_CNF_STRU */
    ID_LMM_MMC_ATTACH_IND               = (PS_MSG_ID_LMM_TO_MMC_BASE+0x11),     /* _H2ASN_MsgChoice LMM_MMC_ATTACH_IND_STRU */
    ID_LMM_MMC_DETACH_CNF               = (PS_MSG_ID_LMM_TO_MMC_BASE+0x12),     /* _H2ASN_MsgChoice LMM_MMC_DETACH_CNF_STRU */
    ID_LMM_MMC_DETACH_IND               = (PS_MSG_ID_LMM_TO_MMC_BASE+0x13),     /* _H2ASN_MsgChoice LMM_MMC_DETACH_IND_STRU */
    ID_LMM_MMC_TAU_RESULT_IND           = (PS_MSG_ID_LMM_TO_MMC_BASE+0x14),     /* _H2ASN_MsgChoice LMM_MMC_TAU_RESULT_IND_STRU */
    ID_LMM_MMC_SERVICE_RESULT_IND       = (PS_MSG_ID_LMM_TO_MMC_BASE+0x15),     /* _H2ASN_MsgChoice LMM_MMC_SERVICE_RESULT_IND_STRU */
    ID_LMM_MMC_TIN_TYPE_IND             = (PS_MSG_ID_LMM_TO_MMC_BASE+0x16),     /* _H2ASN_MsgChoice LMM_MMC_TIN_TYPE_IND_STRU */

    /* Deleted by l00305157 for Service_State_Optimize_PhaseII, 2015-02-11, begin */
    /* ɾ��LTE�ϱ�����״̬��ע��״̬�Ľӿ�,  ID_LMM_MMC_SERVICE_STATUS_IND/ID_LMM_MMC_REGISTER_STATUS_IND*/
    /* Deleted by l00305157 for Service_State_Optimize_PhaseII, 2015-02-11, end */

    ID_LMM_MMC_TIMER_STATE_NOTIFY       = (PS_MSG_ID_LMM_TO_MMC_BASE+0x19),     /* _H2ASN_MsgChoice LMM_MMC_TIMER_STATE_NOTIFY_STRU */
    ID_LMM_MMC_BG_PLMN_SEARCH_CNF       = (PS_MSG_ID_LMM_TO_MMC_BASE+0x1A),     /* _H2ASN_MsgChoice LMM_MMC_BG_PLMN_SEARCH_CNF_STRU*/
    ID_LMM_MMC_STOP_BG_PLMN_SEARCH_CNF  = (PS_MSG_ID_LMM_TO_MMC_BASE+0x1B),     /* _H2ASN_MsgChoice LMM_MMC_STOP_BG_PLMN_SEARCH_CNF_STRU*/
    ID_LMM_MMC_NOT_CAMP_ON_IND          = (PS_MSG_ID_LMM_TO_MMC_BASE+0x1C),     /* _H2ASN_MsgChoice LMM_MMC_NOT_CAMP_ON_IND_STRU*/
    ID_LMM_MMC_UTRAN_MODE_CNF           = (PS_MSG_ID_LMM_TO_MMC_BASE+0x1D),     /* _H2ASN_MsgChoice LMM_MMC_UTRAN_MODE_CNF_STRU*/
    ID_LMM_MMC_SUSPEND_REL_CNF          = (PS_MSG_ID_LMM_TO_MMC_BASE+0x1E),     /* _H2ASN_MsgChoice LMM_MMC_SUSPEND_REL_CNF_STRU*/
    /*ID_ESM_SM_EPS_BEARER_INFO_IND                   ,    */   /* _H2ASN_MsgChoice ESM_SM_EPS_BEARER_INFO_IND_STRU */
/* lihong00150010 ims begin */
    ID_LMM_MMC_EMC_PDP_STATUS_NOTIFY    = (PS_MSG_ID_LMM_TO_MMC_BASE+0x1F),     /* _H2ASN_MsgChoice LMM_MMC_EMC_PDP_STATUS_NOTIFY_STRU*/
/* lihong00150010 ims end */
    ID_LMM_MMC_SUSPEND_INFO_CHANGE_NOTIFY  = (PS_MSG_ID_LMM_TO_MMC_BASE+0x20),      /* _H2ASN_MsgChoice LMM_MMC_SUSPEND_INFO_CHANGE_NOTIFY_STRU */
    ID_LMM_MMC_INFO_CHANGE_NOTIFY        = (PS_MSG_ID_LMM_TO_MMC_BASE+0x21),    /* _H2ASN_MsgChoice LMM_MMC_INFO_CHANGE_NOTIFY_STRU*/
    ID_LMM_MMC_SIM_AUTH_FAIL_IND           =  (PS_MSG_ID_LMM_TO_MMC_BASE+0x22),  /* _H2ASN_MsgChoice LMM_MMC_SIM_AUTH_FAIL_IND_STRU */
    ID_LMM_MMC_SEARCHED_PLMN_INFO_IND    = (PS_MSG_ID_LMM_TO_MMC_BASE+0x23),  /* _H2ASN_MsgChoice LMM_MMC_SEARCHED_PLMN_INFO_IND_STRU*/

    ID_LMM_MMC_CELL_SIGN_REPORT_IND     = (PS_MSG_ID_LMM_TO_MMC_BASE+0x24),     /* _H2ASN_MsgChoice LMM_MMC_CELL_SIGN_REPORT_IND_STRU */

    ID_LMM_MMC_T3402_LEN_NOTIFY         = (PS_MSG_ID_LMM_TO_MMC_BASE+0x25),  /* _H2ASN_MsgChoice LMM_MMC_T3402_LEN_NOTIFY_STRU */

    ID_LMM_MMC_EUTRAN_NOT_ALLOW_NOTIFY   = (PS_MSG_ID_LMM_TO_MMC_BASE+0x26),   /* _H2ASN_MsgChoice LMM_MMC_EUTRAN_NOT_ALLOW_NOTIFY_STRU*/

    ID_LMM_MMC_BG_SEARCH_HRPD_CNF       = (PS_MSG_ID_LMM_TO_MMC_BASE+0x27),     /* _H2ASN_MsgChoice LMM_MMC_BG_SEARCH_HRPD_CNF_STRU */
    ID_LMM_MMC_STOP_BG_SEARCH_HRPD_CNF  = (PS_MSG_ID_LMM_TO_MMC_BASE+0x28),     /* _H2ASN_MsgChoice LMM_MMC_STOP_BG_SEARCH_HRPD_CNF_STRU */

    ID_MMC_LMM_MSG_ID_ENUM_BUTT
};
typedef VOS_UINT32 MMC_LMM_MSG_ID_ENUM_UINT32;

/*****************************************************************************
ö����  : MMC_LMM_CELL_SEL_TYPE_ENUM_UINT32
Э���ʽ:
ASN.1����:
ö��˵��:С������ԭ��ö������
*****************************************************************************/
enum MMC_LMM_CELL_SEL_TYPE_ENUM
{
    MMC_LMM_RESEL_SUITABLE              = 0,

    MMC_LMM_CELL_SEL_BUTT
};
typedef VOS_UINT32  MMC_LMM_CELL_SEL_TYPE_ENUM_UINT32;


/*****************************************************************************
 ö����    : MMC_LMM_DISABLE_LTE_REASON_ENUM
 ö��˵��  : Disable Lteԭ��ö�ٶ���
*****************************************************************************/
enum MMC_LMM_DISABLE_LTE_REASON_ENUM
{
    MMC_LMM_DISABLE_LTE_REASON_PS_DETACH                            =0,
    MMC_LMM_DISABLE_LTE_REASON_PS_USIM_INVALID                      =1,
    MMC_LMM_DISABLE_LTE_REASON_LTE_ROAMING_NOT_ALLOWED              =2,
    MMC_LMM_DISABLE_LTE_REASON_LTE_VOICE_NOT_AVAILABLE              =3,
    MMC_LMM_DISABLE_LTE_REASON_EMERGENCY_CALL                       =4,
    MMC_LMM_DISABLE_LTE_REASON_SIM_CARD_SWITCH_ON                   =5,
    MMC_LMM_DISABLE_LTE_REASON_IMSI_IN_FORBIDDEN_LIST               =6,
    MMC_LMM_DISABLE_LTE_REASON_LTE_REJ_CAUSE_14                     =7,
    MMC_LMM_DISABLE_LTE_REASON_LMM_NOTIFY_EUTRAN_NOT_ALLOW          =8,
    MMC_LMM_DISABLE_LTE_REASON_BUTT
};
typedef VOS_UINT32  MMC_LMM_DISABLE_LTE_REASON_ENUM_UINT32;

/*****************************************************************************
 ö����: MMC_LMM_TRANSCEIVER_TYPE_ENUM
 Э���ʽ:
 ASN.1����:
 ö��˵��:��������ȡֵ
*****************************************************************************/
enum MMC_LMM_TRANSCEIVER_TYPE_ENUM
{
    MMC_LMM_TRANSCEIVER_TYPE_SINGLE     = 0,                                    /* ��ģ���� */
    MMC_LMM_TRANSCEIVER_TYPE_DUAL          ,                                    /* ��ģ˫��,L��G ,L��W */
    MMC_LMM_TRANSCEIVER_TYPE_BUTT
};
typedef VOS_UINT32 MMC_LMM_TRANSCEIVER_TYPE_ENUM_UINT32;


/*****************************************************************************
 ö����: MMC_LMM_RESULT_ID_ENUM
 Э���ʽ:
 ASN.1����:
 ö��˵��:
*****************************************************************************/
enum    MMC_LMM_RESULT_ID_ENUM
{
    MMC_LMM_SUCC                        = 0x00000000,
    MMC_LMM_FAIL                        ,
    MMC_LMM_ERR_ID_BUTT
};
typedef VOS_UINT32 MMC_LMM_RESULT_ID_ENUM_UINT32;

/*****************************************************************************
 ö����: MMC_LMM_PLMN_SRCH_TYPE_ENUM
 Э���ʽ:
 ASN.1����:
 ö��˵��:
*****************************************************************************/
enum MMC_LMM_PLMN_SRCH_TYPE_ENUM
{
    MMC_LMM_PLMN_SRCH_SPEC              = 0,                /* ָ����PLMN������ */
    MMC_LMM_PLMN_SRCH_LIST              = 1,                /* PLMN�б������   */
    MMC_LMM_PLMN_SRCH_ANY               = 2,                /* any cell ���� */
    MMC_LMM_PLMN_SRCH_USER_SPEC         = 3,                /* userָ������*/
    MMC_LMM_PLMN_SRCH_FAST_SPEC         = 4,                /* ����ָ����PLMN������ */

    MMC_LMM_PLMN_SRCH_NCELL_SPEC        = 5,               /* SVLTE���Կ���ʱ����modem1 g�ϱ���L����Ƶ����Ϣ�������� */

    MMC_LMM_PLMN_SRCH_HISTORY           = 6,               /*��ʷ��Ϣ����*/
    MMC_LMM_PLMN_SRCH_GET_GEO           = 7,               /*��ȡ������Ϣ*/

    MMC_LMM_PLMN_SRCH_TYPE_BUTT
};
typedef VOS_UINT32 MMC_LMM_PLMN_SRCH_TYPE_ENUM_UINT32;

/*****************************************************************************
 ö����: MMC_LMM_PLMN_SRCH_RLT_ENUM
 Э���ʽ:
 ASN.1����:
 ö��˵��:
*****************************************************************************/
enum MMC_LMM_PLMN_SRCH_RLT_ENUM
{
    MMC_LMM_PLMN_SRCH_RLT_SPEC_SUCC     = 0,                /* ָ����PLMN ID �����ɹ� */
    MMC_LMM_PLMN_SRCH_RLT_LIST_SUCC     = 1,                /* PLMN List�����ɹ�      */
    MMC_LMM_PLMN_SRCH_RLT_SPEC_FAIL     = 2,                /* ָ��PLMN ID����ʧ��    */
    MMC_LMM_PLMN_SRCH_RLT_LIST_REJ      = 3,                /* פ��̬���б��������ǳ����������̴�� */

    MMC_LMM_PLMN_SRCH_RLT_SPEC_NO_RF    = 4,
    MMC_LMM_PLMN_SRCH_RLT_LIST_NO_RF    = 5,

    MMC_LMM_PLMN_SRCH_RLT_HISTORY_FAIL  = 6,
    MMC_LMM_PLMN_SRCH_RLT_HISTORY_SUCC  = 7,
    MMC_LMM_PLMN_SRCH_RLT_HISTORY_NO_RF = 8,

    MMC_LMM_PLMN_SRCH_RLT_GET_GEO_FAIL  = 9,
    MMC_LMM_PLMN_SRCH_RLT_GET_GEO_SUCC  = 10,
    MMC_LMM_PLMN_SRCH_RLT_GET_GEO_NO_RF = 11,

    MMC_LMM_PLMN_SRCH_RLT_BUTT
};
typedef VOS_UINT32  MMC_LMM_PLMN_SRCH_RLT_ENUM_UINT32;

/*****************************************************************************
 ö����    : MMC_LMM_BG_SRCH_RLT_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : BG�������
*****************************************************************************/
enum MMC_LMM_BG_SRCH_RLT_ENUM
{
    MMC_LMM_BG_SRCH_RLT_SUCCESS            = 0,                /* ָ����PLMN�����ɹ� */
    MMC_LMM_BG_SRCH_RLT_FAIL               = 1,                /* ʵ�ʷ�������������������ʧ�� */
    MMC_LMM_BG_SRCH_RLT_ABORT              = 2,                /* û�з�����������Ϊ��ǰ״̬��������������ֹ */
    MMC_LMM_BG_SRCH_RLT_BUTT
};
typedef VOS_UINT32  MMC_LMM_BG_SRCH_RLT_ENUM_UINT32;


/*****************************************************************************
 ö����: MMC_LMM_FFT_SCAN_TYPE_ENUM_UINT8
 Э���ʽ:
 ASN.1����:
 ö��˵��:
*****************************************************************************/
enum MMC_LMM_FFT_SCAN_TYPE_ENUM
{
    MMC_LMM_FFT_SCAN_TYPE_NONE     = 0,                 /* ����COMM SRCH��ȡFFTɨƵ֮���Ƶ�� */
    MMC_LMM_FFT_SCAN_TYPE_LOW      = 1,                 /* ��COMM SRCH��ȡFFTɨƵ֮�������פ�����޵�Ƶ�� */
    MMC_LMM_FFT_SCAN_TYPE_HIGH     = 2,                 /* ��COMM SRCH��ȡFFTɨƵ֮��������������޵�Ƶ�� */
    MMC_LMM_FFT_SCAN_TYPE_BUTT
};
typedef VOS_UINT8  MMC_LMM_FFT_SCAN_TYPE_ENUM_UINT8;

/*****************************************************************************
 ö����: MMC_LMM_CELL_STATUS_ENUM
 Э���ʽ:
 ASN.1����:
 ö��˵��:
*****************************************************************************/
enum MMC_LMM_CELL_STATUS_ENUM
{
    MMC_LMM_CELL_STATUS_NORMAL          = 0,               /* ����פ��    */
    MMC_LMM_CELL_STATUS_ANYCELL         = 1,               /* AnyCellפ�� */
    MMC_LMM_CELL_STATUS_BUTT
};
typedef VOS_UINT32 MMC_LMM_CELL_STATUS_ENUM_UINT32;


/*****************************************************************************
 ö����: MMC_LMM_ACTION_TYPE_ENUM
 Э���ʽ:
 ASN.1����:
 ö��˵��:
*****************************************************************************/
enum MMC_LMM_ACTION_TYPE_ENUM
{
    MMC_LMM_ACTION_ATTACH              = 0x00000000,
    MMC_LMM_ACTION_RAU                  ,
    MMC_LMM_ACTION_LAU                  ,
    MMC_LMM_ACTION_PS_SERVICE_REQ       ,

    MMC_LMM_ACTION_MT_DETACH            ,
    MMC_LMM_ACTION_LOCAL_DETACH         ,
    MMC_LMM_ACTION_MO_DETACH            ,

    MMC_LMM_ACTION_CM_REQ               ,
    MMC_LMM_ACTION_MM_ABORT             ,
    MMC_LMM_ACTION_PERIODC_RAU          ,
    MMC_LMM_ACTION_TYPE_BUTT
};
typedef VOS_UINT32 MMC_LMM_ACTION_TYPE_ENUM_UINT32;


/*****************************************************************************
 ö����: NAS_LMM_CN_CAUSE_ENUM
 ö��˵��:24301 9.9.3.9 EMM cause
*****************************************************************************/
enum    NAS_LMM_CN_CAUSE_ENUM
{
    NAS_EMM_CAUSE_IMSI_UNKNOWN_IN_HSS                                                                  = 0x00000002,    /* IMSI unknown in HSS          */
    NAS_EMM_CAUSE_ILLEGAL_UE                                                                                          = 0x00000003,    /* Illegal UE          */
    NAS_EMM_CAUSE_IMSI_UNKNOWN_IN_VLR                                   = 0x00000004, /*IMSI unknown in VLR*/
    NAS_EMM_CAUSE_IMEI_NOT_ACCEPTED                                     = 0x00000005, /*IMEI not accepted*/
    NAS_EMM_CAUSE_ILLEGAL_ME                                                                                          = 0x00000006,    /* Illegal ME              */
    NAS_EMM_CAUSE_EPS_SERV_NOT_ALLOW                                                                  = 0x00000007,    /* EPS services not allowed                */
    NAS_EMM_CAUSE_EPS_SERV_AND_NON_EPS_SERV_NOT_ALLOW                    = 0x00000008,    /* EPS services and non-EPSservices not allowed                     */
    NAS_EMM_CAUSE_MS_ID_CANNOT_BE_DERIVED_BY_NW                                       = 0x00000009,    /* MS identity cannot be derived by the network             */
    NAS_EMM_CAUSE_EPS_IMPLICITLY_DETACHED                                                          = 0x0000000a,    /* Implicitly detached  */
    NAS_EMM_CAUSE_PLMN_NOT_ALLOW                                                                             = 0x0000000b,    /* PLMN not allowed                         */
    NAS_EMM_CAUSE_TA_NOT_ALLOW                                                                                   = 0x0000000c,    /* Tracking  area not allowed                */
    NAS_EMM_CAUSE_ROAM_NOT_ALLOW                                                                            = 0x0000000d,     /* Roaming not allowed in this tracking area                      */
    NAS_EMM_CAUSE_EPS_SERV_NOT_ALLOW_IN_PLMN                                              = 0x0000000e,    /* EPS services not allowed in this PLMN   */
    NAS_EMM_CAUSE_NO_SUITABL_CELL                                                                             = 0x0000000f,     /* No Suitable Cells In Location Area       */
    NAS_EMM_CAUSE_MSC_TEMPORARILY_NOT_REACHABLE                                                              = 0x00000010,    /* MSC temporarily not reachable     */
    NAS_EMM_CAUSE_NETWORKFAILURE                                                                             = 0x00000011,    /* Network failure     */
    NAS_EMM_CAUSE_CS_DOMAIN_NOT_AVAILABLE                                                        = 0x00000012,    /* CS domain not available       */
    NAS_EMM_CAUSE_ESM_FAILURE                                                                                       = 0x00000013,    /* ESM failure       */
    NAS_EMM_CAUSE_CONGESTION                                                                                        = 0x00000016,    /* Congestion     */
    NAS_EMM_CAUSE_NOT_AUTHORIZED_FOR_THIS_CSG                                             = 0x00000019,    /*  Not authorized for this CSG        */
    NAS_EMM_CAUSE_REQUESTED_SER_OPTION_NOT_AUTHORIZED_IN_PLMN                           = 0x00000023, /*Requested service option not authorized in this PLMN*/
    NAS_EMM_CAUSE_CS_DOMAIN_TEMP_NOT_AVAILABLE                                          = 0x00000027,    /*  CS domain temporarily not available       */
    NAS_EMM_CAUSE_NO_EPS_BEARER_CONTEXT_ACTIVATED                                = 0x00000028,    /*  No EPS bearer context activated        */
    NAS_EMM_CAUSE_SERVER_NETWORK_FAILURE                                         = 0x0000002a,    /*  Server Network Failure  */
    NAS_EMM_CAUSE_SEMANTICALLY_INCORRECT_MSG                                              = 0x0000005f,    /* Semantically incorrect message    */
    NAS_EMM_CAUSE_INVALID_MANDATORY_INFORMATION                                         = 0x00000060,    /* Invalid mandatory information    */
    NAS_EMM_CAUSE_MSG_TYPE_NON_EXIST_OR_IMPLEMENT                                  = 0x00000061,    /* Message type non-existent or not implemented    */
    NAS_EMM_CAUSE_INFO_ELEMENT_NON_EXIST_OR_NOT_IMPLEMENT              = 0x00000063,    /*  Information element non-existent or not implemented    */
    NAS_EMM_CAUSE_MSG_NOT_COMPATIBLE_WITH_PROTOCOL_STATE              = 0x00000065,    /*Message not compatible with protocol state    */
    NAS_EMM_CAUSE_BUTT
};

typedef VOS_UINT8 NAS_LMM_CN_CAUSE_ENUM_UINT8;


/*****************************************************************************
 ö����: MMC_LMM_DOMAIN_ENUM
 Э���ʽ:
 ASN.1����:
 ö��˵��:   ATTACH, RAU, DETACH�� ����ͽ������   ���: 24301  9.9.3.10 / 24008  10.5.5.1
*****************************************************************************/
enum MMC_LMM_DOMAIN_ENUM
{
    MMC_LMM_PS_ONLY                     = 0x00000000,                           /*��ǰRAU/Attach����ΪPS only  */
    MMC_LMM_IMSI_ONLY,                                                          /*��ǰ ����ΪCS only  */
    MMC_LMM_COMBINED_PS_IMSI ,                                                  /*��ǰ ����Ϊ���ϴ���  */

    MMC_LMM_DOMAIN_BUTT
};
typedef VOS_UINT32 MMC_LMM_DOMAIN_ENUM_UINT32;



/*****************************************************************************
 �ṹ����:
 Э����:
 ASN.1 ����:
 �ṹ˵��:   CN_ACCEPT, CN_REJECT��������������Ӧ�Ľ����
*****************************************************************************/
enum MMC_LMM_RSLT_TYPE_ENUM
{
    MMC_LMM_RSLT_TYPE_SUCCESS                     = 0,
    MMC_LMM_RSLT_TYPE_FAILURE,                                                  /*ʧ�ܰ�������ܾ�������Ӧ*/
    MMC_LMM_RSLT_TYPE_CN_REJ,
    MMC_LMM_RSLT_TYPE_AUTH_REJ,                                                 /* ��Ȩ���� */
    MMC_LMM_RSLT_TYPE_ACCESS_BARRED,
    MMC_LMM_RSLT_TYPE_BUTT
};
typedef VOS_UINT32 MMC_LMM_RSLT_TYPE_ENUM_UINT32;


/*****************************************************************************
 �ṹ����:MMC_LMM_SYS_CHNG_TYPE_ENUM
 Э����:
 ASN.1 ����:
 �ṹ˵��:LMM֪ͨMMC����ķ���
*****************************************************************************/
enum    MMC_LMM_SYS_CHNG_DIR_ENUM
{

    MMC_LMM_SYS_CHNG_DIR_L2W            = 0x00000000,
    MMC_LMM_SYS_CHNG_DIR_L2G,
    MMC_LMM_SYS_CHNG_DIR_G2L,
    MMC_LMM_SYS_CHNG_DIR_W2L,

    /*Modify by sunbing 49683 for CL multimode 2014-01-09 begin*/
    MMC_LMM_SYS_CHNG_DIR_L2C,
    /*Modify by sunbing 49683 for CL multimode 2014-01-09 end*/

    MMC_LMM_SYS_CHNG_DIR_BUTT
};
typedef VOS_UINT32 MMC_LMM_SYS_CHNG_DIR_ENUM_UINT32;


/*****************************************************************************
 �ṹ����:MMC_LMM_SYS_CHNG_TYPE_ENUM
 Э����:
 ASN.1 ����:
 �ṹ˵��:ϵͳ���������
*****************************************************************************/
enum MMC_LMM_SYS_CHNG_TYPE_ENUM
{
    MMC_LMM_SUS_TYPE_RSL                = 0x00000000,                           /* ��ѡ */
    MMC_LMM_SUS_TYPE_HO ,                                                       /* HandOver */
    MMC_LMM_SUS_TYPE_CCO ,                                                      /* Cell Change Order */
    MMC_LMM_SUS_TYPE_REDIR ,                                                    /* �����ض��� */
    MMC_LMM_SUS_TYPE_CCO_REVERSE ,      /* G->L��CCOʧ�ܣ���G����ʱ��LMM��MMCָʾ�����͵Ĺ��� */

    MMC_LMM_SUS_TYPE_BUTT
};
typedef VOS_UINT32 MMC_LMM_SYS_CHNG_TYPE_ENUM_UINT32;

/*****************************************************************************
 ö����    : LMM_MMC_CONN_STATE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : LMM��������ö��
*****************************************************************************/
enum MMC_LMM_CONN_STATE_ENUM
{
    MMC_LMM_CONN_IDLE                   = 0x00000000,       /* �����Ӵ��� */
    MMC_LMM_CONN_ESTING ,                                   /* ���������� */
    MMC_LMM_CONNECTED_SIG ,                                 /* ֻ���������� */
    MMC_LMM_CONNECTED_DATA,                                 /* ���������� */

    MMC_LMM_CONN_BUTT
};
typedef VOS_UINT32 MMC_LMM_CONN_STATE_ENUM_UINT32;



/*****************************************************************************
 ö����    : MMC_LMM_STATUS_TYPE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  :״̬���������
*****************************************************************************/
enum MMC_LMM_STATUS_TYPE_ENUM
{

    MMC_LMM_STATUS_TYPE_CONN_STATE      = 0x00000000,                           /* ָʾ����״̬ */
    MMC_LMM_STATUS_TYPE_T3412_EXP,                                              /* T3412��ʱ */
    MMC_LMM_STATUS_TYPE_T3423_EXP,                                              /* T3423��ʱ */
    MMC_LMM_STATUS_TYPE_BUTT
};
typedef VOS_UINT32 MMC_LMM_STATUS_TYPE_ENUM_UINT32;

/* Ƶ���ţ�ȡֵ��Χ��1��40���ֱ��Ӧ 36.101  5.5 �� band ȡֵ */
typedef VOS_UINT32 MMC_LMM_LTE_BAND_UINT32;

/*****************************************************************************
 ö����    : SMS_LMM_REG_STATE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  :
*****************************************************************************/
enum MMC_LMM_USIM_STATUS_ENUM
{
    MMC_LMM_USIM_VALID                  = 0x00000000,                           /* ��Ч�� */
    MMC_LMM_USIM_INVALID,                                                       /* �޿�����Ч */

    MMC_LMM_USIM_STATUS_BUTT
};
typedef VOS_UINT32 MMC_LMM_USIM_STATUS_ENUM_UINT32;


/*****************************************************************************
 ö������: NAS_GUMM_INFO_TYPE_ENUM_UINT32
 Э����:
 ASN.1 ����:
 ö��˵��:MMC����LTEģ����Ϣ������GUģ�Ĳ�������GUL���õĲ���
*****************************************************************************/
enum NAS_GUMM_INFO_TYPE_ENUM
{
    NAS_GUMM_PTMSI                      = 0x00000000,
    NAS_GUMM_PTMSI_SIGNATURE,
    NAS_GUMM_LAI,
    NAS_GUMM_RAI,
    NAS_GUMM_UMTS_SECU_PARA,
    NAS_GUMM_TMSI_STATUS,

    NAS_GUMM_INFO_TYPE_BUTT
};
typedef VOS_UINT32 NAS_GUMM_INFO_TYPE_ENUM_UINT32;

/****************************************************************************
 ö������: NAS_LMM_INFO_TYPE_ENUM_UINT32
 Э����:
 ASN.1 ����:
 ö��˵��:   LTEģ�ṩ��GUģ����Ϣö��
*****************************************************************************/
enum NAS_LMM_INFO_TYPE_ENUM
{
    NAS_LMM_GUTI                        = 0x00000000,
    NAS_LMM_RPLMN,
    NAS_LMM_FORB_TAI_ROAM_LIST,
    NAS_LMM_FORB_TAI_RPOS_LIST,

    NAS_LMM_CS_DOMAIN_UNAVAILABLE_PLMN_LIST,

    NAS_LMM_INFO_TYPE_BUTT
};
typedef VOS_UINT32 NAS_LMM_INFO_TYPE_ENUM_UINT32;


/****************************************************************************
 ö������: MMC_LMM_EPS_UPDATE_STATUS_ENUM
 Э����:
 ASN.1 ����:
 ö��˵��:   LTE��EUֵö��
*****************************************************************************/
enum MMC_LMM_EPS_UPDATE_STATUS_ENUM
{
    MMC_LMM_EPS_UPDATE_STATUS_UPDATED               = 0x00,             /* UPDATED */
    MMC_LMM_EPS_UPDATE_STATUS_NOT_UPDATED           = 0x01,             /* NOT UPDATED */
    MMC_LMM_EPS_UPDATE_STATUS_ROAMING_NOT_ALLOWED   = 0x02,             /* ROAMING NOT ALLOWED */

    MMC_LMM_EPS_UPDATE_STATUS_BUTT
};
typedef VOS_UINT8  MMC_LMM_EPS_UPDATE_STATUS_ENUM_UINT8;

/****************************************************************************
 ö������: MMC_LMM_TAI_IN_LIST_FLAG_ENUM
 Э����:
 ASN.1 ����:
 ö��˵��: TAI�Ƿ���TAI LIST�б�ʶö��
*****************************************************************************/
enum MMC_LMM_TAI_IN_LIST_FLAG_ENUM
{
    MMC_LMM_TAI_IN_TAI_LIST             = 0x00,                         /* TAI IN TAI LIST */
    MMC_LMM_TAI_NOT_IN_TAI_LIST         = 0x01,                         /* TAI NOT IN TAI LIST */

    MMC_LMM_TAI_IN_LIST_FLAG_BUTT
};
typedef VOS_UINT8 MMC_LMM_TAI_IN_LIST_FLAG_ENUM_UINT8;



/*****************************************************************************
 ö������: MMC_LMM_TMSI_STATUS_TYPE_ENUM_UINT32
 Э����:
 ASN.1 ����:
 ö��˵��:GU�ṩ��LTEģ����Ϣö��
*****************************************************************************/
enum MMC_LMM_TMSI_STATUS_TYPE_ENUM
{
    MMC_LMM_TMSI_STATUS_VALID           = 0x00000000,
    MMC_LMM_TMSI_STATUS_INVALID        ,

    MMC_LMM_TMSI_STATUS_BUTT
};
typedef VOS_UINT32 MMC_LMM_TMSI_STATUS_TYPE_ENUM_UINT32;

/*****************************************************************************
 ö������: MMC_LMM_INFO_TYPE_ENUM_UINT32
 Э����:
 ASN.1 ����:
 ö��˵��:MMCģ�ṩ��GU��LTEģ����Ϣö��
*****************************************************************************/
enum MMC_LMM_INFO_TYPE_ENUM
{
    MMC_LMM_TIN_TYPE                    = 0x00000000,                           /* Tin ����*/
    MMC_LMM_EPLMN                       ,                                       /* ��ЧPlmn */
    MMC_LMM_FPLMN                       ,                                       /* ��ֹPlmn */
    MMC_LMM_FPLMN_FOR_GPRS              ,                                       /* ��ֹPlmn for gprs */
    MMC_LMM_EHPLMN                      ,
    MMC_LMM_HPLMN                       ,

    MMC_LMM_INFO_TYPE_BUTT
};
typedef VOS_UINT32 MMC_LMM_INFO_TYPE_ENUM_UINT32;

/*****************************************************************************
 ö������: MMC_LMM_TIN_TYPE_ENUM
 Э����:
 ASN.1 ����:
 ö��˵��:  Tin������
*****************************************************************************/
enum MMC_LMM_TIN_TYPE_ENUM
{
    MMC_LMM_TIN_P_TMSI                  = 0x00000000,
    MMC_LMM_TIN_GUTI                    ,
    MMC_LMM_TIN_RAT_RELATED_TMSI        ,
    MMC_LMM_TIN_INVALID                 ,

    MMC_LMM_TIN_BUTT
};
typedef VOS_UINT32 MMC_LMM_TIN_TYPE_ENUM_UINT32;



/*****************************************************************************
 ö������: MMC_LMM_RADIO_CAP_UPD_NEED_TYPE_ENUM
 Э����:
 ASN.1 ����:
 ö��˵��:
*****************************************************************************/
enum MMC_LMM_RADIO_CAP_UPD_NEED_TYPE_ENUM
{
    MMC_LMM_RADIO_CAP_UPD_NO_NEED    = 0x00000000,
    MMC_LMM_RADIO_CAP_UPD_NEED ,

    MMC_LMM_RADIO_CAP_UPD_BUTT
};
typedef VOS_UINT32 MMC_LMM_RADIO_CAP_UPD_NEED_TYPE_ENUM_UINT32;

/*****************************************************************************
 ö����    : MMC_LMM_PLMN_CTRL_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : PLMN�Ƿ��ֹ��ʶ
*****************************************************************************/
enum MMC_LMM_PLMN_CTRL_ENUM
{
    MMC_LMM_PLMN_ALLOW_REG              = 0,                                    /* ����ע�� */
    MMC_LMM_PLMN_NOT_ALLOW_REG          ,                                        /*������ע�� */
    MMC_LMM_PLMN_CTRL_BUTT
};
typedef VOS_UINT32 MMC_LMM_PLMN_CTRL_ENUM_UINT32;
/*****************************************************************************
 ö����    : MMC_LMM_ATT__REQ_TYPE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : UE������ATTACH TYPE
*****************************************************************************/
enum MMC_LMM_ATT_REQ_TYPE_ENUM
{
    MMC_LMM_ATT_REQ_TYPE_CS_ONLY                      = 0,
    MMC_LMM_ATT_REQ_TYPE_PS_ONLY                      = 1,
    MMC_LMM_ATT_REQ_TYPE_CS_PS                        = 2,
    MMC_LMM_ATT_REQ_TYPE_BUTT
};
typedef VOS_UINT32 MMC_LMM_ATT_REQ_TYPE_ENUM_UINT32;

/*Modify by sunbing 49683 for CL multimode 2014-01-09 begin*/
/*****************************************************************************
 ö����    : MMC_LMM_ATT_REASON_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ������ATTACHԭ��
*****************************************************************************/
enum MMC_LMM_ATT_REASON_ENUM
{
    MMC_LMM_ATT_REASON_INITIAL,
    MMC_LMM_ATT_REASON_HANDOVER,
    MMC_LMM_ATT_REASON_BUTT
};
typedef VOS_UINT32 MMC_LMM_ATT_REASON_ENUM_UINT32;
/*Modify by sunbing 49683 for CL multimode 2014-01-09 end*/


/*****************************************************************************
 ö����    : MMC_LMM_ATTACH_TYPE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : UE������ATTACH TYPE
*****************************************************************************/
enum MMC_LMM_ATTACH_TYPE_ENUM
{
    MMC_LMM_ATT_TYPE_EPS_ONLY                     = 1,
    MMC_LMM_ATT_TYPE_COMBINED_EPS_IMSI            = 2,
    MMC_LMM_ATT_TYPE_EPS_EMERGENCY                = 6,
    MMC_LMM_ATT_TYPE_BUTT
};
typedef VOS_UINT32 MMC_LMM_ATTACH_TYPE_ENUM_UINT32;

/*****************************************************************************
 ö����    : MMC_LMM_ATTACH_CN_RSLT_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ������Ӧ��ATTACH�������
*****************************************************************************/
enum MMC_LMM_ATTACH_CN_RSLT_ENUM
{
    MMC_LMM_ATT_CN_RSLT_EPS_ONLY                     = 1,
    MMC_LMM_ATT_CN_RSLT_COMBINED_EPS_IMSI            = 2,
    MMC_LMM_ATT_CN_RSLT_BUTT
};
typedef VOS_UINT32 MMC_LMM_ATTACH_CN_RSLT_ENUM_UINT32;

/*****************************************************************************
 ö����    : MMC_LMM_CL_REG_STATUS_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : CL��VIA��̬ʹ�õ�ATTACHע�����ϱ�ʱ�����Ľ׶�
*****************************************************************************/
enum MMC_LMM_CL_REG_STATUS_ENUM
{
    MMC_LMM_CL_REG_STATUS_ATTACH_NOT_SEND            = 0x00,
    MMC_LMM_CL_REG_STATUS_ATTACH_SEND_WAIT_CN_RSP    = 0x01,
    MMC_LMM_CL_REG_STATUS_ATTACH_RCV_CN_REJ          = 0x02,
    MMC_LMM_CL_REG_STATUS_ATTACH_RCV_CN_ACP          = 0x03,
    MMC_LMM_CL_REG_STATUS_ATTACH_T3410_EXP           = 0x04,
    MMC_LMM_CL_REG_STATUS_ATTACH_CMP_SEND            = 0x05,

    MMC_LMM_CL_REG_STATUS_BUTT
};
typedef VOS_UINT8 MMC_LMM_ATTACH_CL_REG_STATUS_ENUM8;

/*****************************************************************************
 ö����    : MMC_LMM_ATTACH_RSLT_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ATTACH�Ľ������
*****************************************************************************/
enum MMC_LMM_ATTACH_RSLT_ENUM
{

    MMC_LMM_ATT_RSLT_SUCCESS                     = 0x00000000,
    MMC_LMM_ATT_RSLT_FAILURE,                                                   /*����ATTACHδָ��ԭ���ʧ�� */
    MMC_LMM_ATT_RSLT_ACCESS_BAR,                                                /* ���뱻 Barred */
    MMC_LMM_ATT_RSLT_TIMER_EXP,                                                 /* ��������Ӧ */
    MMC_LMM_ATT_RSLT_CN_REJ,                                                    /* ������ȷ�ܾ� */
    MMC_LMM_ATT_RSLT_AUTH_REJ,                                                  /* ��Ȩ���� */
    MMC_LMM_ATT_RSLT_PS_ATT_NOT_ALLOW,                                          /* psע���ǲ�����ע��*/
    MMC_LMM_ATT_RSLT_FORBID_PLMN,                                               /* PLMN����*/
    MMC_LMM_ATT_RSLT_FORBID_PLMN_FOR_GPRS,                                      /* PLMN FOR GRPS����*/
    MMC_LMM_ATT_RSLT_FORBID_TA_FOR_ROAMING,                                     /* TA FOR ROAM����*/
    MMC_LMM_ATT_RSLT_FORBID_TA_FOR_RPOS,                                        /* TA FOR RPOS����*/
    MMC_LMM_ATT_RSLT_ESM_FAILURE,
    MMC_LMM_ATT_RSLT_MO_DETACH_FAILURE,
    MMC_LMM_ATT_RSLT_MT_DETACH_FAILURE,
    MMC_LMM_ATT_RSLT_T3402_RUNNING,
    MMC_LMM_ATT_RSLT_BUTT
};
typedef VOS_UINT32 MMC_LMM_ATTACH_RSLT_ENUM_UINT32;

/*****************************************************************************
 ö����    : MMC_LMM_MO_DETACH_TYPE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : UE������DETACH TYPE
*****************************************************************************/
enum MMC_LMM_MO_DETACH_TYPE_ENUM
{
    MMC_LMM_MO_DET_PS_ONLY                        = 1,
    MMC_LMM_MO_DET_CS_ONLY                        = 2,
    MMC_LMM_MO_DET_CS_PS                          = 3,
    MMC_LMM_MO_DETACH_TYPE_BUTT
};
typedef VOS_UINT32 MMC_LMM_MO_DETACH_TYPE_ENUM_UINT32;

/*Modify by sunbing 49683 for CL multimode 2014-01-09 begin*/
/*****************************************************************************
 ö����    : MMC_LMM_DETACH_RESEAON_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : DETACH�����ԭ��
*****************************************************************************/
enum MMC_LMM_DETACH_RESEAON_ENUM
{
    MMC_LMM_DETACH_RESEAON_NULL,                  /*������ԭ��*/
    MMC_LMM_DETACH_RESEAON_NON_3GPP_ATTACH,       /*non-3GPP���뼼�����ն���ע�ᣬLTE����Ҫȥע��*/
    MMC_LMM_DETACH_RESEAON_BUTT
};
typedef VOS_UINT32 MMC_LMM_DETACH_RESEAON_ENUM_UINT32;
/*Modify by sunbing 49683 for CL multimode 2014-01-09 end*/


/*****************************************************************************
 ö����    : MMC_LMM_MT_DETACH_TYPE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ���ഥ����DETACH TYPE
*****************************************************************************/
enum MMC_LMM_MT_DETACH_TYPE_ENUM
{
    MMC_LMM_MT_DET_REATTACH_REQUIRED                = 1,
    MMC_LMM_MT_DET_REATTACH_NOT_REQUIRED            = 2,
    MMC_LMM_MT_DET_IMSI                             = 3,

    MMC_LMM_MT_DETACH_TYPE_BUTT
};
typedef VOS_UINT32 MMC_LMM_MT_DETACH_TYPE_ENUM_UINT32;

/*****************************************************************************
 ö����    : MMC_LMM_DETACH_RSLT_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : DETACH�Ľ������
*****************************************************************************/
enum MMC_LMM_DETACH_RSLT_ENUM
{
    MMC_LMM_DETACH_RSLT_SUCCESS         = 0,
    MMC_LMM_DETACH_RSLT_ACCESS_BARED    ,
    MMC_LMM_DETACH_RSLT_FAILURE         ,
    MMC_LMM_DETACH_RSLT_AUTH_REJ        ,

    MMC_LMM_DETACH_RSLT_BUTT
};
typedef VOS_UINT32 MMC_LMM_DETACH_RSLT_ENUM_UINT32;

/*****************************************************************************
 ö����    : MMC_LMM_DETACH_TYPE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ���ഥ����DETACH�򱾵�DETACH
*****************************************************************************/
enum MMC_LMM_DETACH_TYPE_ENUM
{
    MMC_LMM_DETACH_LOCAL                            = 1,
    MMC_LMM_DETACH_MT                               = 2,

    MMC_LMM_DETACH_TYPE_BUTT
};
typedef VOS_UINT32 MMC_LMM_DETACH_TYPE_ENUM_UINT32;


/*****************************************************************************
 ö����    : MMC_LMM_TAU_TYPE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : UE������TAU����
*****************************************************************************/
enum MMC_LMM_TAU_TYPE_ENUM
{
    MMC_LMM_TA_UPDATING                     = 0,
    MMC_LMM_COMBINED_TA_LA_UPDATING         = 1,
    MMC_LMM_COMBINED_TA_LA_WITH_IMSI        = 2,
    MMC_LMM_PS_PERIODIC_UPDATING            = 3,
    MMC_LMM_CS_PS_PERIODIC_UPDATING         = 4,
    MMC_LMM_TAU_TYPE_BUTT
};
typedef VOS_UINT32 MMC_LMM_TAU_TYPE_ENUM_UINT32;

/*****************************************************************************
 ö����    : MMC_LMM_TAU_CN_RSLT_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ������Ӧ��TAU�������
*****************************************************************************/
enum MMC_LMM_TAU_CN_RSLT_ENUM
{
    MMC_LMM_TA_UPDATED                     = 0,
    MMC_LMM_COMBINED_TA_LA_UPDATED         = 1,
    MMC_LMM_TA_UPDATED_ISR_ACTIVATED       = 4,
    MMC_LMM_COMBINED_TA_LA_UPDATED_ISR_ACTIVATED              = 5,
    MMC_LMM_TAU_CN_RSLT_BUTT
};
typedef VOS_UINT32 MMC_LMM_TAU_CN_RSLT_ENUM_UINT32;

/*****************************************************************************
 ö����    : MMC_LMM_TAU_RSLT_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : TAU�Ľ������
*****************************************************************************/
enum MMC_LMM_TAU_RSLT_ENUM
{

    MMC_LMM_TAU_RSLT_SUCCESS                     = 0,
    MMC_LMM_TAU_RSLT_FAILURE,                           /*����δָ��ԭ���ʧ��*/
    MMC_LMM_TAU_RSLT_ACCESS_BARED,                      /*TAU���뱻bar*/
    MMC_LMM_TAU_RSLT_TIMER_EXP,                         /*TAU��ʱ����ʱ*/
    MMC_LMM_TAU_RSLT_CN_REJ,                            /*TAU����ܾ�*/
    MMC_LMM_TAU_RSLT_AUTH_REJ,                          /*��Ȩ�ܾ�*/
    MMC_LMM_TAU_RSLT_FORBID_PLMN,                       /* PLMN����*/
    MMC_LMM_TAU_RSLT_FORBID_PLMN_FOR_GPRS,              /* PLMN FOR GRPS����*/
    MMC_LMM_TAU_RSLT_FORBID_TA_FOR_ROAMING,             /* TA FOR ROAM����*/
    MMC_LMM_TAU_RSLT_FORBID_TA_FOR_RPOS,                /* TA FOR RPOS����*/
    MMC_LMM_TAU_RSLT_MO_DETACH_FAILURE,
    MMC_LMM_TAU_RSLT_MT_DETACH_FAILURE,
    MMC_LMM_TAU_RSLT_T3402_RUNNING,
    MMC_LMM_TAU_RSLT_BUTT
};
typedef VOS_UINT32 MMC_LMM_TAU_RSLT_ENUM_UINT32;

/*****************************************************************************
 ö����    : MMC_LMM_SERVICE_RSLT_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : SERVICE�Ľ������
*****************************************************************************/
enum MMC_LMM_SERVICE_RSLT_ENUM
{

    MMC_LMM_SERVICE_RSLT_FAILURE        = 0,                                    /*������ܾ����ʧ��*/
    MMC_LMM_SERVICE_RSLT_ACCESS_BARED   ,                                       /*���뱻bar*/
    MMC_LMM_SERVICE_RSLT_CN_REJ         ,                                       /*����ܾ�*/
    MMC_LMM_SERVICE_RSLT_AUTH_REJ       ,                                       /*��Ȩ�ܾ�*/
    MMC_LMM_SERVICE_RSLT_TIMER_EXP      ,                                       /*��ʱ����ʱ��PS��CSFB�������*/

    MMC_LMM_SERVICE_RSLT_BUTT
};
typedef VOS_UINT32 MMC_LMM_SERVICE_RSLT_ENUM_UINT32;

/*****************************************************************************
 ö����    : MMC_LMM_SERVICE_TYPE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : UE������EXTENDED SERVICE�����ͣ���ʱ����
*****************************************************************************/
enum MMC_LMM_SERVICE_TYPE_ENUM
{
    MMC_LMM_SERVICE_MO_CSFB_1XCSFB              = 0,
    MMC_LMM_SERVICR_MT_CSFB_1XCSFB,
    MMC_LMM_SERVICR_MO_CSFB_1XCSFB_EMERGENCY,
    MMC_LMM_SERVICE_TYPE_BUTT
};
typedef VOS_UINT32 MMC_LMM_SERVICE_TYPE_ENUM_UINT32;
/* ע��/����״̬�ϱ�����MMC��ɾ��ע��/����״̬��ش��� */
/*****************************************************************************
 ö����    : MMC_LMM_SYS_MODE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : LMM�ϱ���sys mode
*****************************************************************************/
enum MMC_LMM_SYS_MODE_ENUM
{
    MMC_LMM_SERVICE_MODE_NO_SERVICE             = 0,
    MMC_LMM_SERVICE_MODE_GSM,
    MMC_LMM_SERVICE_MODE_CDMA,
    MMC_LMM_SERVICE_MODE_WCDMA,
    MMC_LMM_SERVICE_MODE_TDSCDMA,
    MMC_LMM_SERVICE_MODE_WIMAX,
    MMC_LMM_SERVICE_MODE_LTE,
    MMC_LMM_SERVICE_MODE_TYPE_BUTT
};
typedef VOS_UINT32 MMC_LMM_SYS_MODE_ENUM_UINT32;
/* ע��/����״̬�ϱ�����MMC��ɾ��ע��/����״̬��ش��� */


/*****************************************************************************
 ö����    : MMC_LMM_L_LOCAL_DETACH_TYPE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ����DETACH����
*****************************************************************************/
enum MMC_LMM_L_LOCAL_DETACH_TYPE_ENUM
{
    MMC_LMM_L_LOCAL_DETACH_IMSI_PAGING          = 0,
    MMC_LMM_L_LOCAL_DETACH_OTHERS               = 1,

    MMC_LMM_L_LOCAL_DETACH_TYPE_BUTT
};
typedef VOS_UINT32 MMC_LMM_L_LOCAL_DETACH_TYPE_ENUM_UINT32;

/*****************************************************************************
 ö����    : MMC_LMM_GPRS_UPDATE_STATUS_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : GPRS update statusö��
*****************************************************************************/
enum MMC_LMM_GPRS_UPDATE_STATUS_ENUM
{
    MMC_LMM_GPRS_UPDATE_STATUS_UPDATED,
    MMC_LMM_GPRS_UPDATE_STATUS_NOT_UPDATED,
    MMC_LMM_GPRS_UPDATE_STATUS_PLMN_NOT_ALLOWED,
    MMC_LMM_GPRS_UPDATE_STATUS_ROUTING_AREA_NOT_ALLOWED,
    MMC_LMM_GPRS_UPDATE_STATUS_BUTT
};
typedef VOS_UINT8 MMC_LMM_GPRS_UPDATE_STATUS_ENUM_UINT8;

/*****************************************************************************
 ö����    : MMC_LMM_CS_UPDATE_STATUS_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : MM update statusö��
*****************************************************************************/
enum MMC_LMM_CS_UPDATE_STATUS_ENUM
{
    MMC_LMM_CS_UPDATE_STATUS_UPDATED,
    MMC_LMM_CS_UPDATE_STATUS_NOT_UPDATED,
    MMC_LMM_CS_UPDATE_STATUS_PLMN_NOT_ALLOWED,
    MMC_LMM_CS_UPDATE_STATUS_LOCATION_AREA_NOT_ALLOWED,
    MMC_LMM_CS_UPDATE_STATUS_UPDATING_DISABLED,
    MMC_LMM_CS_UPDATE_STATUS_BUTT
};
typedef VOS_UINT8 MMC_LMM_CS_UPDATE_STATUS_ENUM_UINT8;


/*****************************************************************************
 ö����    : MMC_LMM_GU_LOCAL_DETACH_TYPE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : UE����detach type
*****************************************************************************/
enum MMC_LMM_GU_LOCAL_DETACH_TYPE_ENUM
{
    MMC_LMM_GU_LOCAL_DET_IMSI_PAGING,
    MMC_LMM_GU_LOCAL_DET_OTHERS,
    MMC_LMM_GU_LOCAL_DET_BUTT
};
typedef VOS_UINT32 MMC_LMM_GU_LOCAL_DETACH_TYPE_ENUM_UINT32;



enum LMM_MMC_TIMER_STATE_ENUM
{
    LMM_MMC_TIMER_STOP         = 0,
    LMM_MMC_TIMER_START,
    LMM_MMC_TIMER_EXP,

    LMM_MMC_TIMER_BUTT
};
typedef VOS_UINT32 LMM_MMC_TIMER_STATE_ENUM_UINT32;

/*****************************************************************************
 ö����    : MMC_LMM_RAT_TYPE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ���뼼��ö�ٶ���
*****************************************************************************/
enum MMC_LMM_RAT_TYPE_ENUM
{
    MMC_LMM_RAT_GSM                     = 0,
    MMC_LMM_RAT_WCDMA_FDD               = 1,
    MMC_LMM_RAT_LTE                     = 2,
    MMC_LMM_RAT_TYPE_BUTT
};
typedef VOS_UINT8  MMC_LMM_RAT_TYPE_ENUM_UINT8;

/*****************************************************************************
 ö����    : MMC_LMM_RAT_LIST_SEARCH_RSLT_ENUM
 �ṹ˵��  : LMM_MMC_PLMN_SRCH_CNF_STRU��Ϣ�е�LIST����������
*****************************************************************************/
enum MMC_LMM_RAT_LIST_SEARCH_RSLT_ENUM
{
    MMC_LMM_RAT_LIST_SEARCH_NOT_START      = 0,                /* LIST����δ����        */
    MMC_LMM_RAT_LIST_SEARCH_PARTIAL_CMPL   = 1,                /* LIST����������,������� */
    MMC_LMM_RAT_LIST_SEARCH_CMPL           = 2,                /* LIST�������          */
    MMC_LMM_RAT_LIST_SEARCH_BUTT
};
typedef VOS_UINT8  MMC_LMM_RAT_LIST_SEARCH_RSLT_ENUM_UINT8;


/*****************************************************************************
 ö����: MMC_LMM_PLMN_SRCH_RLT_ENUM
 Э���ʽ:
 ASN.1����:
 ö��˵��:
*****************************************************************************/
enum MMC_LMM_COVERAGE_TYPE_ENUM
{
    MMC_LMM_COVERAGE_TYPE_NONE     = 0,                /* �����縲�� */
    MMC_LMM_COVERAGE_TYPE_LOW      = 1,                 /* ���������縲��   */
    MMC_LMM_COVERAGE_TYPE_HIGH     = 2,                /* �и��������縲�� */
    MMC_LMM_COVERAGE_TYPE_BUTT
};
typedef VOS_UINT32  MMC_LMM_COVERAGE_TYPE_ENUM_UINT32;
enum MMC_LMM_UTRAN_MODE_ENUM
{
    MMC_LMM_UTRAN_MODE_FDD          = 0,     /* ��ǰ����ģʽΪWCDMA */
    MMC_LMM_UTRAN_MODE_TDD          = 1,     /* ��ǰ����ģʽΪTDSCDMA */
    MMC_LMM_UTRAN_MODE_BUTT
};
typedef VOS_UINT8  MMC_LMM_UTRAN_MODE_ENUM_UINT8;



enum MMC_LMM_SESSION_TYPE_ENUM
{
    MMC_LMM_SESSION_TYPE_CS_MO_NORMAL_CALL,
    MMC_LMM_SESSION_TYPE_CS_MO_EMERGENCY_CALL,
    MMC_LMM_SESSION_TYPE_CS_MO_SS,
    MMC_LMM_SESSION_TYPE_CS_MO_SMS,
    MMC_LMM_SESSION_TYPE_PS_CONVERSAT_CALL,
    MMC_LMM_SESSION_TYPE_PS_STREAM_CALL,
    MMC_LMM_SESSION_TYPE_PS_INTERACT_CALL,
    MMC_LMM_SESSION_TYPE_PS_BACKGROUND_CALL,
    MMC_LMM_SESSION_TYPE_PS_SUBSCRIB_TRAFFIC_CALL,
    MMC_LMM_SESSION_TYPE_BUTT
};
typedef VOS_UINT8 MMC_LMM_SESSION_TYPE_ENUM_UINT8;


enum MMC_LMM_AREA_LOST_REASON_ENUM
{
    MMC_LMM_AREA_LOST_REASON_NO_COVERAGE,
    MMC_LMM_AREA_LOST_REASON_NO_RF,
    MMC_LMM_AREA_LOST_REASON_BUTT
};
typedef  VOS_UINT32 MMC_LMM_AREA_LOST_REASON_UINT32;





enum MMC_LMM_IMS_VOICE_CAP_ENUM
{
    MMC_LMM_IMS_VOICE_CAP_UNAVAILABLE             = 0,
    MMC_LMM_IMS_VOICE_CAP_AVAILABLE                 = 1,

    MMC_LMM_IMS_VOICE_CAP_CHANGE_BUTT
};
typedef VOS_UINT8  MMC_LMM_IMS_VOICE_CAP_ENUM_UINT8;


/*****************************************************************************
 ö����    : LMM_MMC_NW_IMS_VOICE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ����֧�ֵ�IMS VOICEö��
*****************************************************************************/
enum LMM_MMC_NW_IMS_VOICE_ENUM
{
    LMM_MMC_NW_IMS_VOICE_NOT_SUPPORTED   = 0,
    LMM_MMC_NW_IMS_VOICE_SUPPORTED        = 1,

    LMM_MMC_NW_IMS_VOICE_BUTT
};
typedef VOS_UINT32 LMM_MMC_NW_IMS_VOICE_ENUM_UINT32;

/*****************************************************************************
 ö����    : LMM_MMC_NW_EMC_BS_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ����֧�ֵ�EMC BEARER SERVICEEö��
*****************************************************************************/
enum LMM_MMC_NW_EMC_BS_ENUM
{
    LMM_MMC_NW_EMC_BS_NOT_SUPPORTED      = 0,
    LMM_MMC_NW_EMC_BS_SUPPORTED           = 1,

    LMM_MMC_NW_EMC_BS_BUTT
};
typedef VOS_UINT32 LMM_MMC_NW_EMC_BS_ENUM_UINT32;

/*****************************************************************************
 ö����    : LMM_MMC_LTE_CS_CAPBILITY_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : LTE��CS������
*****************************************************************************/
enum LMM_MMC_LTE_CS_CAPBILITY_ENUM
{
    LMM_MMC_LTE_CS_CAPBILITY_NO_ADDITION_INFO  = 0,  /* NO_ADDITION_INFO��ʾCS֧��ȫ���� */
    LMM_MMC_LTE_CS_CAPBILITY_CSFB_NOT_PREFER   = 1,
    LMM_MMC_LTE_CS_CAPBILITY_SMS_ONLY          = 2,
    LMM_MMC_LTE_CS_CAPBILITY_NOT_ATTACHED      = 3,
    LMM_MMC_LTE_CS_CAPBILITY_BUTT
};
typedef VOS_UINT32 LMM_MMC_LTE_CS_CAPBILITY_ENUM_UINT32;

/*****************************************************************************
 �ṹ����: MMC_LMM_ACCESS_TYPE_ENUM
 Э����:
 ASN.1 ����:
 �ṹ˵��:
*****************************************************************************/
enum MMC_LMM_ACCESS_TYPE_ENUM
{
    MMC_LMM_ACCESS_TYPE_EUTRAN_TDD      = 0,
    MMC_LMM_ACCESS_TYPE_EUTRAN_FDD         ,
    MMC_LMM_ACCESS_TYPE_BUTT
};
typedef VOS_UINT8  MMC_LMM_ACCESS_TYPE_ENUM_UINT8;


/*****************************************************************************
 �ṹ����: LMM_MMC_SIM_AUTH_FAIL_ENUM
 Э����:
 ASN.1 ����:
 �ṹ˵��: ����Ȩʧ��ԭ��ֵLMM֪ͨMMC�ӿ� 20141103add
*****************************************************************************/
enum LMM_MMC_SIM_AUTH_FAIL_ENUM
{
    LMM_MMC_SIM_AUTH_FAIL_NULL                      = 0,
    LMM_MMC_SIM_AUTH_FAIL_MAC_FAILURE               = 1,
    LMM_MMC_SIM_AUTH_FAIL_SYNC_FAILURE              = 2,
    LMM_MMC_SIM_AUTH_FAIL_OTHER                     = 3,
    LMM_MMC_SIM_AUTH_FAIL_BUTT
};
typedef VOS_UINT16  LMM_MMC_SIM_AUTH_FAIL_ENUM_UINT16;

/*****************************************************************************
 �ṹ����: LMM_MMC_SRV_DOMAIN_ENUM
 Э����:
 ASN.1 ����:
 �ṹ˵��: ����Ȩʧ�ܷ�����LMM֪ͨMMC�ӿ� 20141103add
*****************************************************************************/
enum LMM_MMC_SRV_DOMAIN_ENUM
{
    LMM_MMC_SRV_DOMAIN_CS                           = 1,
    LMM_MMC_SRV_DOMAIN_PS                           = 2,
    LMM_MMC_SRV_DOMAIN_CS_PS                        = 3,
    LMM_MMC_SRV_DOMAIN_BUTT
};
typedef VOS_UINT8  LMM_MMC_SRV_DOMAIN_ENUM_UINT8;


enum MMC_LMM_VOICE_DOMAIN_ENUM
{
    MMC_LMM_VOICE_DOMAIN_CS_ONLY            = 0,    /* CS voice only */
    MMC_LMM_VOICE_DOMAIN_IMS_PS_ONLY        = 1,    /* IMS PS voice only */
    MMC_LMM_VOICE_DOMAIN_CS_PREFERRED       = 2,    /* CS vocie preferred, IMS PS voice as secondary */
    MMC_LMM_VOICE_DOMAIN_IMS_PS_PREFERRED   = 3,    /* IMS PS voice preferred, CS vocie as secondary */

    MMC_LMM_VOICE_DOMAIN_BUTT
};
typedef VOS_UINT8  MMC_LMM_VOICE_DOMAIN_ENUM_UINT32;

/*****************************************************************************
  5 STRUCT
*****************************************************************************/

/*****************************************************************************
�ṹ��    :MMC_LMM_PLMN_ID_STRU��
Э����  :
ASN.1���� :
�ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucPlmnId[MMC_LMM_PLMN_ID_LEN];
    VOS_UINT8                           ucRsv;
}MMC_LMM_PLMN_ID_STRU;

/*****************************************************************************
�ṹ��    :MMC_LMM_PLMN_ID_WITH_RAT_STRU��
Э����  :
ASN.1���� :
�ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucPlmnId[MMC_LMM_PLMN_ID_LEN];
    MMC_LMM_RAT_TYPE_ENUM_UINT8         enPlmnRat;
}MMC_LMM_PLMN_ID_WITH_RAT_STRU;

/*****************************************************************************
 �ṹ��    : MMC_LMM_EPLMN_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��ЧPLMN���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulPlmnNum;                              /* ��Ч PLMN ����   */
    MMC_LMM_PLMN_ID_STRU                astEplmnList[MMC_LMM_MAX_EQUPLMN_NUM];
}MMC_LMM_EPLMN_STRU;

/*****************************************************************************
 �ṹ��    : MMC_LMM_SUIT_PLMN_ID_LIST_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MMC_LMM_SUIT_PLMN_ID_LIST_STRU���ݽṹ
*****************************************************************************/
typedef struct
{
    /* ��ǰС��ϵͳ��Ϣ�а����Ĺ��� plmn id�ĸ��� */
    VOS_UINT32                          ulSuitPlmnNum;

    /* С��ϵͳ��Ϣ�а�������� ����plmn id�ĸ���   */
    MMC_LMM_PLMN_ID_STRU                astSuitPlmnList[MMC_LMM_MAX_SRCH_PLMN_NUM];
} MMC_LMM_SUIT_PLMN_ID_LIST_STRU;


/*****************************************************************************
 �ṹ��    : MMC_LMM_LOW_PLMN_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MMC_LMM_LOW_PLMN_INFO_STRU���ݽṹ
*****************************************************************************/
typedef struct
{
    MMC_LMM_PLMN_ID_STRU                stPlmnId;                               /* PLMN ID    */
    VOS_INT32                           lRscp;                                  /* RSCP����ֵ */
}MMC_LMM_LOW_PLMN_INFO_STRU;

/*****************************************************************************
 �ṹ��    : MMC_LMM_LOW_PLMN_WITH_RAT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MMC_LMM_LOW_PLMN_WITH_RAT_STRU���ݽṹ
*****************************************************************************/
typedef struct
{
    MMC_LMM_PLMN_ID_WITH_RAT_STRU       stPlmnIdWithRat;                        /* PLMN ID    */
    VOS_INT32                           lRscp;                                  /* RSCP����ֵ */
}MMC_LMM_LOW_PLMN_WITH_RAT_STRU;

/*****************************************************************************
 �ṹ��    : MMC_LMM_PLMN_ID_LIST_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MMC_LMM_PLMN_ID_LIST_STRU���ݽṹ
*****************************************************************************/
typedef struct
{
    /* ������PLMN�ĸ��� */
    VOS_UINT32                          ulHighPlmnNum;

    /* ������PLMN�б�   */
    MMC_LMM_PLMN_ID_WITH_RAT_STRU       astHighPlmnWithRatList[MMC_LMM_MAX_HIGH_PLMN_NUM];


    /* ������PLMN�ĸ��� */
    VOS_UINT32                          ulLowPlmnNum;

    /* ������PLMN�б�   */
    MMC_LMM_LOW_PLMN_WITH_RAT_STRU      astLowPlmnWithRatList[MMC_LMM_MAX_LOW_PLMN_NUM];
}MMC_LMM_PLMN_ID_LIST_STRU;

/*****************************************************************************
 �ṹ��    : MMC_LMM_LIST_SEARCH_RAT_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MMC_LMM_LIST_SEARCH_RAT_INFO_STRU���ݽṹ
*****************************************************************************/
typedef struct
{
    MMC_LMM_RAT_TYPE_ENUM_UINT8              enRat;                            /* �����Ľ��뼼�� */
    MMC_LMM_RAT_LIST_SEARCH_RSLT_ENUM_UINT8  enListSearchRlt;                  /* ���뼼��LIST������ɽ�� */
    VOS_UINT8                                aucReserve[2];
}MMC_LMM_LIST_SEARCH_RAT_INFO_STRU;

/*****************************************************************************
�ṹ����    :MMC_LMM_LAC_STRU
ʹ��˵��    :TAC��Ϣ  24.301  9.9.3.26
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucLac;
    VOS_UINT8                           ucLacCnt;
    VOS_UINT8                           aucRsv[2];
}MMC_LMM_LAC_STRU;

/*****************************************************************************
�ṹ����    :NAS_LMM_TAC_STRU
ʹ��˵��    :TAC��Ϣ  24.301  9.9.3.26
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucTac;
    VOS_UINT8                           ucTacCnt;
    VOS_UINT8                           aucRsv[2];
}NAS_LMM_TAC_STRU;

/*****************************************************************************
 �ṹ����: NAS_LMM_SYS_INFO_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��:LTEģ��С��ϵͳ��Ϣ
*****************************************************************************/
typedef struct
{
    MMC_LMM_SUIT_PLMN_ID_LIST_STRU      stSpecPlmnIdList;                       /* ��ǰС���Ĺ��������б� */
    NAS_LMM_TAC_STRU                    stTac;                                  /* TrackingAreaCode */
    VOS_UINT32                          ulCellId;                               /* Cell Identity */
    MMC_LMM_CELL_STATUS_ENUM_UINT32     enCellStatusInd;                        /* С��״ָ̬ʾ */

    LTE_BAND_STRU                       stLteBand;                              /* Lģ��ǰפ����Ƶ����Ϣ */

    /*Modify by sunbing 49683 for CL multimode 2014-01-09 begin*/
    /* Modified by w00316404 for R11 Update LTE Arf, 2015-07-20, begin */
    VOS_UINT32                          ulArfcn;                                /* פ��Ƶ����Ϣ */
    /* Modified by w00316404 for R11 Update LTE Arf, 2015-07-20, end */
    VOS_UINT8                           ucBandWidth;                            /* ������Ϣ */
    MMC_LMM_ACCESS_TYPE_ENUM_UINT8      enAccessType;                           /* ��������:TDD/FDD */
    /*Modify by sunbing 49683 for CL multimode 2014-01-09 end*/
    /* Modified by w00316404 for R11 Update LTE Arf, 2015-07-20, begin */
    VOS_UINT8                           aucReserved[2];
    /* Modified by w00316404 for R11 Update LTE Arf, 2015-07-20, end */

}MMC_LMM_SYS_INFO_STRU;


/*****************************************************************************
 �ṹ��    : MMC_LMM_LAI_STRU
 �ṹ˵��  : LA��Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    MMC_LMM_PLMN_ID_STRU                stPlmnId;
    MMC_LMM_LAC_STRU                    stLac;
}MMC_LMM_LAI_STRU;

/*****************************************************************************
 �ṹ��    : MMC_LMM_RAI_STRU
 �ṹ˵��  : RAI��Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    MMC_LMM_LAI_STRU                    stLai;
    VOS_UINT8                           ucRac;
    VOS_UINT8                           aucReserve[3];
}MMC_LMM_RAI_STRU;

/*****************************************************************************
 �ṹ����: MMC_LMM_MS_IDNETITY_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��:
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucMsIdentity[NAS_MAX_SIZE_MS_IDENTITY];
    VOS_UINT8                           aucRsv[3];
} MMC_LMM_MS_IDNETITY_STRU;


/*****************************************************************************
 �ṹ����: NAS_GUMM_PTMSI_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��: �� 24.008 10.5.1.4
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucPtmsi[NAS_MAX_SIZE_PTMSI];
} NAS_GUMM_PTMSI_STRU;


/*****************************************************************************
 �ṹ����: NAS_GUMM_PTMSI_SIGNATURE_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��:��24.008 10.5.5.8
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucPtmsiSign[NAS_MAX_SIZE_PTMSI_SIGNATURE];
    VOS_UINT8                           ucRsv;
} NAS_GUMM_PTMSI_SIGNATURE_STRU;

/*****************************************************************************
 �ṹ����: NAS_GUMM_SECU_CONTEXT_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��:��ҪLMM��������ĸ�RAT��LTE�任��
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucKSI;
    VOS_UINT8                           aucRsv[3];
    VOS_UINT8                           aucCK[NAS_UMTS_CK_LENGTH];
    VOS_UINT8                           aucIK[NAS_UMTS_IK_LENGTH];

} NAS_GUMM_UMTS_CONTEXT_STRU;

/****************************************************************************
�ṹ����    : NAS_LMM_GUTI_HEAD_STRU
�ṹ˵��    : 24.301 9.9.3.10  EPS mobile identity
****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucLenth;
    VOS_UINT8                           ucOeToi;
    VOS_UINT8                           aucRsv[2];
}NAS_LMM_GUTI_HEAD_STRU;



/****************************************************************************
�ṹ����    :NAS_LMM_MME_GROUPID_STRU
ʹ��˵��    :NAS_LMM_MME_GROUPID_STRU����ز���
Э�������� ��DIGIT���ֽ�/λ�Ĺ�ϵ����:
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucGroupId;
    VOS_UINT8                           ucGroupIdCnt;
    VOS_UINT8                           aucRsv[2];
}NAS_LMM_MME_GROUPID_STRU;

/****************************************************************************
�ṹ����    :NAS_LMM_MME_CODE_STRU
ʹ��˵��    :NAS_LMM_MME_CODE_STRU����ز���
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucMmeCode;
    VOS_UINT8                           aucRsv[3];
}NAS_LMM_MME_CODE_STRU;

/****************************************************************************
�ṹ����    :NAS_LMM_MTMSI_STRU
ʹ��˵��    :NAS_LMM_MTMSI_STRU����ز���
Э�������� ��DIGIT���ֽ�/λ�Ĺ�ϵ����:
*************************************************************/
typedef struct
{
    VOS_UINT8                           ucMTmsi;
    VOS_UINT8                           ucMTmsiCnt1;
    VOS_UINT8                           ucMTmsiCnt2;
    VOS_UINT8                           ucMTmsiCnt3;
}NAS_LMM_MTMSI_STRU;

/*****************************************************************************
�ṹ����    :NAS_MM_GUTI_STRU
ʹ��˵��    :NAS_MM_GUTI_STRU����ز���
*****************************************************************************/
typedef struct
{
    NAS_LMM_GUTI_HEAD_STRU               stGutiHead;
    MMC_LMM_PLMN_ID_STRU                 stPlmnId;
    NAS_LMM_MME_GROUPID_STRU             stMmeGroupId;
    NAS_LMM_MME_CODE_STRU                stMmeCode;
    NAS_LMM_MTMSI_STRU                   stMTmsi;
}NAS_LMM_GUTI_STRU;

/*****************************************************************************
�ṹ����    :NAS_MM_PLMN_LIST_STRU
ʹ��˵��    :10.5.13/3GPP TS 24.008 PLMN List information element
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulPlmnNum;
    MMC_LMM_PLMN_ID_STRU                astPlmnId[MMC_LMM_MAX_PLMN_NUM];
}MMC_LMM_PLMN_LIST_STRU;

/*****************************************************************************
 �ṹ��    : NAS_LMM_TAI_STRU
 �ṹ˵��  : TA��Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    MMC_LMM_PLMN_ID_STRU                 stPlmnId;
    NAS_LMM_TAC_STRU                     stTac;
}NAS_LMM_TAI_STRU;


/*****************************************************************************
 �ṹ��    : NAS_LMM_TAI_LIST_STRU
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT32                           ulTaNum;
    NAS_LMM_TAI_STRU                     astTa[MMC_LMM_MAX_FORB_ROAM_TAI_NUM];
}NAS_LMM_TAI_LIST_STRU;


/*****************************************************************************
 �ṹ����: MMC_LMM_START_REQ_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��:
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    MMC_LMM_TRANSCEIVER_TYPE_ENUM_UINT32 ulTransceiverType;
    MMC_LMM_USIM_STATUS_ENUM_UINT32      ulUsimState;
    RRMM_RAT_PRIO_ENUM_UINT8             aucRatPrioList[RRMM_RAT_TYPE_BUTT];     /* ��ģ�����ȼ� */
    MMC_LMM_UTRAN_MODE_ENUM_UINT8       enUtranMode;                            /* ��ǰUTRAN�Ĺ���ģʽ:0---FDD 1---TDD */
    /*Modify by sunbing 49683 for CL multimode 2014-01-09 begin*/
    VOS_UINT8                           aucRsv[2];
    /*Modify by sunbing 49683 for CL multimode 2014-01-09 end*/
} MMC_LMM_START_REQ_STRU;

/*****************************************************************************
 �ṹ����: LMM_MMC_START_CNF_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��:
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    /* ִ�н�� */
    MMC_LMM_RESULT_ID_ENUM_UINT32          ulRst;
} LMM_MMC_START_CNF_STRU;

/*****************************************************************************
 �ṹ����: MMC_LMM_STOP_REQ_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��:MMC_LMM_STOP_REQ_STRU�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    VOS_UINT8                           aucRsv[4];
}MMC_LMM_STOP_REQ_STRU;

/*****************************************************************************
 �ṹ��    : LMM_MMC_STOP_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    VOS_UINT8                           aucRsv[4];
}LMM_MMC_STOP_CNF_STRU;


/*****************************************************************************
 �ṹ��    : MMC_LMM_ATTACH_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MMC_LMM_ATTACH_REQ_STRU���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    MMC_LMM_ATT_REQ_TYPE_ENUM_UINT32    ulAttachType;
    /*Modify by sunbing 49683 for CL multimode 2014-01-09 begin*/
    MMC_LMM_ATT_REASON_ENUM_UINT32      ulAttachReason;
    /*Modify by sunbing 49683 for CL multimode 2014-01-09 end*/
}MMC_LMM_ATTACH_REQ_STRU;


/*****************************************************************************
 �ṹ��    : LMM_MMC_ATTACH_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LMM_MMC_ATTACH_CNF_STRU���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    MMC_LMM_ATTACH_RSLT_ENUM_UINT32     ulAttachRslt;       /* ATTACH��� */
    MMC_LMM_ATT_REQ_TYPE_ENUM_UINT32    ulReqType;          /* �û������ATTACH���� */

}LMM_MMC_ATTACH_CNF_STRU;


/*****************************************************************************
 �ṹ��    : LMM_MMC_ATTACH_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LMM_MMC_ATTACH_IND_STRU���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    VOS_UINT32                          bitOpCnRslt     : 1;
    VOS_UINT32                          bitOpCnCause    : 1;
    VOS_UINT32                          bitOpAtmpCnt    : 1;
    VOS_UINT32                          bitOpEplmn      : 1;
    VOS_UINT32                          bitOpLai        : 1;
    VOS_UINT32                          bitOpMsIdentity : 1;
    VOS_UINT32                          bitSpare        : 26;

    MMC_LMM_ATTACH_RSLT_ENUM_UINT32     ulAttachRslt;
    MMC_LMM_ATTACH_TYPE_ENUM_UINT32     ulReqType;
    MMC_LMM_ATTACH_CN_RSLT_ENUM_UINT32  ulCnRslt;
    NAS_LMM_CN_CAUSE_ENUM_UINT8         ucCnCause;        /* �����·���ԭ��ֵ*/
    /* VIA CL��ģʹ�õ�ATTACH���̽׶��ϱ�����״̬LMM��������̬����д��MMCֻ��VIA CL��ģʱʹ�� */
    MMC_LMM_ATTACH_CL_REG_STATUS_ENUM8  enClAttRegStatus;
    VOS_UINT8                           aucRsv[2];
    VOS_UINT32                          ulAttemptCount;   /* ATTACH���Դ��� */
    MMC_LMM_EPLMN_STRU                  stEplmnList;      /*��ЧPLMN LIST, CN��Ϣ�е�EPLMN */
    MMC_LMM_LAI_STRU                    stLai;
    MMC_LMM_MS_IDNETITY_STRU            stMsIdentity;

}LMM_MMC_ATTACH_IND_STRU;


/*****************************************************************************
 �ṹ����: MMC_LMM_DETACH_REQ_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��:MMC_LMM_DETACH_REQ_STRU�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    MMC_LMM_MO_DETACH_TYPE_ENUM_UINT32  ulDetachType;
    /*Modify by sunbing 49683 for CL multimode 2014-01-09 begin*/
    MMC_LMM_DETACH_RESEAON_ENUM_UINT32  ulDetachReason;
    /*Modify by sunbing 49683 for CL multimode 2014-01-09 end*/
}MMC_LMM_DETACH_REQ_STRU;


/*****************************************************************************
 �ṹ����: LMM_MMC_DETACH_CNF_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��:LMM_MMC_DETACH_CNF_STRU�ṹ,��ATTACH�������յ�MMC���͵�DETACH REQ��Ϣ��
 LMM ͨ������Ϣ��Ӧ�������ٷ���LMM_MMC_ATTACH_CNF��LMM_MMC_ATTACH_IND��Ϣ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    /*UE������DETACH��Ӧ���*/
    MMC_LMM_DETACH_RSLT_ENUM_UINT32     ulDetachRslt;

    /*UE������DETACH����*/
    MMC_LMM_MO_DETACH_TYPE_ENUM_UINT32  ulReqType;

}LMM_MMC_DETACH_CNF_STRU;


/*****************************************************************************
 �ṹ����: LMM_MMC_DETACH_IND_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��:LMM_MMC_DETACH_IND_STRU�ṹ,��ATTACH�������յ�CN���͵�MT DETACH��Ϣ��
 LMM ͨ������Ϣ��Ӧ�������ٷ���LMM_MMC_ATTACH_CNF��LMM_MMC_ATTACH_IND��Ϣ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    VOS_UINT32                          bitOpCnReqType  : 1;
    VOS_UINT32                          bitOpCnCause    : 1;
    VOS_UINT32                          bitOpLocDetType : 1;
    VOS_UINT32                          bitSpare        : 29;

    /*DETACH����Ӧ���:���ഥ����DETACH�򱾵�DETACH*/
    MMC_LMM_DETACH_TYPE_ENUM_UINT32     ulDetachType;

    /* ����DETACH���� */
    MMC_LMM_L_LOCAL_DETACH_TYPE_ENUM_UINT32 ulLocDetType;
    /*���ഥ����DETACH����*/
    MMC_LMM_MT_DETACH_TYPE_ENUM_UINT32  ulCnReqType;/*�ӿ��ĵ�����˵��*/

    /* �����·���ԭ��ֵ*/
    NAS_LMM_CN_CAUSE_ENUM_UINT8         ucCnCause;
    VOS_UINT8                           aucRsv[3];


}LMM_MMC_DETACH_IND_STRU;

/*****************************************************************************
 �ṹ��    : MMC_LMM_CELL_SELECTION_CTRL_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MMC_LMM_CELL_SELECTION_CTRL_REQ_STRU�����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    MMC_LMM_CELL_SEL_TYPE_ENUM_UINT32   ulSelecType;

} MMC_LMM_CELL_SELECTION_CTRL_REQ_STRU;


/*****************************************************************************
 �ṹ��    : LMM_MMC_TAU_RESULT_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LMM_MMC_TAU_RESULT_IND_STRU���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    VOS_UINT32                          bitOpCnCause    : 1;
    VOS_UINT32                          bitOpAtmpCnt    : 1;
    VOS_UINT32                          bitOpEplmn      : 1;
    VOS_UINT32                          bitOpLai        : 1;
    VOS_UINT32                          bitOpMsIdentity : 1;
    VOS_UINT32                          bitOpCnRst      : 1;
    VOS_UINT32                          bitOpEpsUpdateStuts : 1;
    VOS_UINT32                          bitOpTaiInListFlag  : 1;
    VOS_UINT32                          bitSpare        : 24;


    /* TAU��Ӧ���*/
    MMC_LMM_TAU_RSLT_ENUM_UINT32        ulTauRst;

    /* TAU����ҵ��ʱ������*/
    MMC_LMM_TAU_TYPE_ENUM_UINT32        ulReqType;

    /*������Ӧ��TAU���������*/
    MMC_LMM_TAU_CN_RSLT_ENUM_UINT32     ulCnRst;

    /* �����·���ԭ��ֵ*/
    NAS_LMM_CN_CAUSE_ENUM_UINT8         ucCnCause;
    VOS_UINT8                           aucRsv1[3];

    /* TAU����ʧ�ܴ��� */
    VOS_UINT32                          ulAttemptCount;

    /*�������ĵ�ЧPLMN LIST */
    MMC_LMM_EPLMN_STRU                  stEplmnList;
    MMC_LMM_LAI_STRU                    stLai;

    MMC_LMM_MS_IDNETITY_STRU            stMsIdentity;

    /* EPS UPDATE STATUS */
    MMC_LMM_EPS_UPDATE_STATUS_ENUM_UINT8 enEmmUpStat;

    /* ��ʶTAI�Ƿ���TAI LIST�� */
    MMC_LMM_TAI_IN_LIST_FLAG_ENUM_UINT8 enTaiInListFlag;

    VOS_UINT8                           aucReserved[2];
} LMM_MMC_TAU_RESULT_IND_STRU;

/*****************************************************************************
 �ṹ��    : LMM_MMC_SERVICE_RESULT_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LMM_MMC_SERVICE_RESULT_IND_STRU���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    VOS_UINT32                          bitOpCnCause    : 1;
    VOS_UINT32                          bitSpare        : 31;


    /* SERVICE��Ӧ���:����ܾ�*/
    MMC_LMM_SERVICE_RSLT_ENUM_UINT32    ulServiceRst;


    /* �����·���ԭ��ֵ*/
    NAS_LMM_CN_CAUSE_ENUM_UINT8         ucCnCause;
    VOS_UINT8                           ucIsReachMaxTimes;  /* 1��Ч��0��Ч����ATT��PLMN���� */
    VOS_UINT8                           aucRsv[2];

} LMM_MMC_SERVICE_RESULT_IND_STRU;
typedef struct
{
    VOS_UINT8                           ucLteArfcnNum;                          /* 0��ʾLTEƵ�㲻���� */
    VOS_UINT8                           aucRsv[3];                              /* ����λ */
    VOS_UINT32                          aulLteArfcnList[MMC_LMM_LTE_ARFCN_MAX_NUM];
    MMC_LMM_EPLMN_STRU                  stEplmnList;                            /* ������ص�Чplmn��Ϣ*/

    /*Modify by sunbing 49683 for CL multimode 2014-01-09 begin*/
    VOS_UINT8                           ucLteCellIdNum;                         /* 0��ʾLTEС��ID������ */
    VOS_UINT8                           aucRsv1[3];                              /* ����λ */
    VOS_UINT16                          ausLteCellIdList[MMC_LMM_LTE_CELL_ID_MAX_NUM];
    /*Modify by sunbing 49683 for CL multimode 2014-01-09 end*/
}MMC_LMM_NCELL_INFO_STRU;

/*****************************************************************************
 �ṹ��    : MMC_LMM_PLMN_SRCH_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MMC_LMM_PLMN_SRCH_REQ_STRU���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    VOS_UINT32                          bitOpSpecPlmn: 1;
    VOS_UINT32                          bitOpEqlPlmn : 1;

    VOS_UINT32                          bitOpNcellInfo : 1;
    VOS_UINT32                          bitOpPlmnInfoCampFlg:1;                 /*�ײ��ϱ���PLMN�Ƿ���Ҫ����פ������,Ŀǰ���ڻ�ȡ������Ϣ�ӿ���ʹ��*/
    VOS_UINT32                          bitSpare     : 28;

    /* �������� */
    MMC_LMM_PLMN_SRCH_TYPE_ENUM_UINT32  enSrchType;
    MMC_LMM_FFT_SCAN_TYPE_ENUM_UINT8    enFftScanType;                          /* ֪ͨLMM����ʱ�Ƿ���Ҫ��COMM SRCH��ȡFFTɨƵ֮���Ƶ�㣬Ŀǰ���ڻ�ȡ������Ϣ������ */
    VOS_UINT8                           aucReserve[3];

    /* ָ��PLMN ID */
    MMC_LMM_PLMN_ID_STRU                stSpecPlmnId;

    /* ��ЧPLMN LIST */
    MMC_LMM_EPLMN_STRU                  stEplmnList;                            /* ��ǰפ�������Чplmn */

    MMC_LMM_NCELL_INFO_STRU             stNcellInfo;
}MMC_LMM_PLMN_SRCH_REQ_STRU;


/*****************************************************************************
 �ṹ��    : LMM_MMC_PLMN_SRCH_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LMM_MMC_PLMN_SRCH_CNF_STRU���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    /* ������� */
    MMC_LMM_PLMN_SRCH_RLT_ENUM_UINT32   enRlst;

    /* ��ǰ���뼼���µ����縲������ */
    MMC_LMM_COVERAGE_TYPE_ENUM_UINT32   enCoverageType;
    /* ָ��PLMN�����ɹ�ʱ,�ѵ���PLMN ID,��enRsltΪָ�������ɹ�ʱ��Ч */
    MMC_LMM_SUIT_PLMN_ID_LIST_STRU      stSpecPlmnIdList;

    /* ��¼L��ģ�±����Ѿ������Ľ��뼼���������б�����ʱ��Ч */
    MMC_LMM_LIST_SEARCH_RAT_INFO_STRU   astSearchRatInfo[MMC_LMM_MAX_RAT_NUM];

    /* LIST PLMN����ʱ,��spec plmn����ʧ��ʱ��������Ч */
    MMC_LMM_PLMN_ID_LIST_STRU           stPlmnIdList;
} LMM_MMC_PLMN_SRCH_CNF_STRU;


/*****************************************************************************
�ṹ��    : MMC_LMM_STOP_PLMN_SRCH_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    VOS_UINT8                           aucRsv[4];
} MMC_LMM_STOP_PLMN_SRCH_REQ_STRU;

/*****************************************************************************
 �ṹ��    : LMM_MMC_STOP_PLMN_SRCH_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LMM_MMC_STOP_PLMN_SRCH_CNF_STRU �����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    VOS_UINT8                           aucRsv[4];
} LMM_MMC_STOP_PLMN_SRCH_CNF_STRU;


/*****************************************************************************
 �ṹ��    : MMC_LMM_BG_PLMN_SEARCH_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MMC_LMM_BG_PLMN_SEARCH_REQ_STRU���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    /* ָ��PLMN ID�����뼼�� */
    MMC_LMM_PLMN_ID_WITH_RAT_STRU       stSpecPlmnWithRat;

    /* ��ֹע�����ĸ���,������LTE����ʱ��Ч */
    VOS_UINT32                          ulForbRoamLaiNum;

    /* ��ֹLAI��Ϣ,������LTE����ʱ��Ч */
    MMC_LMM_LAI_STRU                    astForbRoamLaiList[MMC_LMM_MAX_FORB_ROAM_LAI_NUM];

}MMC_LMM_BG_PLMN_SEARCH_REQ_STRU;

/*****************************************************************************
 �ṹ��    : LMM_MMC_BG_PLMN_SEARCH_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LMM_MMC_BG_PLMN_SEARCH_CNF_STRU���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    /* ������� */
    MMC_LMM_BG_SRCH_RLT_ENUM_UINT32     enRlst;

    /* spec plmn����ʧ��ʱ��������Ч */
    VOS_UINT32                          ulPlmnNum;
    MMC_LMM_PLMN_ID_WITH_RAT_STRU       astPlmnIdWithRatList[MMC_LMM_MAX_BG_SRCH_PLMN_NUM];

} LMM_MMC_BG_PLMN_SEARCH_CNF_STRU;


/*****************************************************************************
�ṹ��    : MMC_LMM_STOP_BG_PLMN_SEARCH_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :MMC_LMM_STOP_BG_PLMN_SEARCH_REQ_STRU
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    VOS_UINT8                           aucRsv[4];
} MMC_LMM_STOP_BG_PLMN_SEARCH_REQ_STRU;

/*****************************************************************************
 �ṹ��    : LMM_MMC_STOP_BG_PLMN_SEARCH_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LMM_MMC_STOP_BG_PLMN_SEARCH_CNF_STRU �����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    VOS_UINT8                           aucRsv[4];
} LMM_MMC_STOP_BG_PLMN_SEARCH_CNF_STRU;

/*****************************************************************************
 �ṹ��    : LMM_MMC_NOT_CAMP_ON_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LMM_MMC_NOT_CAMP_ON_IND_STRU �����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    VOS_UINT8                           aucRsv[4];
} LMM_MMC_NOT_CAMP_ON_IND_STRU;

/*****************************************************************************
 �ṹ��    : MMC_LMM_EPLMN_NOTIFY_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
        MMCֻ������������������ԭ��MMC_LMM_EPLMN_NOTIFY_REQ֪ͨLMM��
        ��1���յ�LMM��ϵͳ��Ϣ��
        ��2��LMM��EPLMN���������
        ��3����ϵͳ�任�У�GU��������Ŀ��ϵͳΪLTEʱ��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    /* EPLMN�ĸ���,����RPLMN */
    VOS_UINT32                          ulEplmnNum;

    /* ��EPLMN LIST���ܸ��µĳ���:
       ע��ɹ�ʱ: ���а������������·���EPLMN LIST�͸�
                        ע��ɹ���RPLMN��ΪaEplmnList�����һ����ЧPLMNID��
       ע��ʧ��ʱ����: 1) ɾ��EPLMN�б����б�ֻ������ǰפ�����磬ulEplmnNumΪ1��
                       2) ��ǰ��ע���PLMN�������� EPLMNLIST����
                       �ұ����԰����ղŵ�RPLMN��������������
                       �ղŵ�RPLMN */
    MMC_LMM_PLMN_ID_STRU                astEplmnList[MMC_LMM_MAX_EQUPLMN_NUM];

} MMC_LMM_EPLMN_NOTIFY_REQ_STRU;


/*****************************************************************************
 �ṹ��    : LMM_MMC_AREA_LOST_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LMM_MMC_AREA_LOST_IND_STRU�����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    /*�ϱ���PLMN ID�б�*/
    MMC_LMM_PLMN_ID_LIST_STRU           stPlmnIdList;

    MMC_LMM_AREA_LOST_REASON_UINT32    enAreaLostReason;
} LMM_MMC_AREA_LOST_IND_STRU;


/*****************************************************************************
 �ṹ����: LMM_MMC_SYS_INFO_IND_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��:
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    /* ��ǰС����ϵͳ��Ϣ: PLMN_LIST, TAC, CELLID, С��״̬�� */
    MMC_LMM_SYS_INFO_STRU               stLteSysInfo;

} LMM_MMC_SYS_INFO_IND_STRU;

/*****************************************************************************
 �ṹ����: MMC_EMM_INFO_UT_LTZ_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��:
*****************************************************************************/
typedef struct
{
    VOS_UINT8                             ucYear;
    VOS_UINT8                             ucMonth;
    VOS_UINT8                             ucDay;
    VOS_UINT8                             ucHour;
    VOS_UINT8                             ucMinute;
    VOS_UINT8                             ucSecond;
    VOS_INT8                              cTimeZone;
    VOS_UINT8                             aucRsv[1];
} MMC_EMM_INFO_UT_LTZ_STRU;

/*****************************************************************************
 �ṹ����: MMC_EMM_INFO_DST_ENUM
 Э����:
 ASN.1 ����:
 �ṹ˵��:
*****************************************************************************/
enum MMC_EMM_INFO_DST_ENUM
{
    MMC_EMM_INFO_DST_NO_ADJUST                         = 0,
    MMC_EMM_INFO_DST_1_HOUR_ADJUST                        ,
    MMC_EMM_INFO_DST_2_HOUR_ADJUST                        ,
    MMC_EMM_INFO_DST_BUTT
};
typedef VOS_UINT8  MMC_EMM_INFO_DST_UINT8;

/*****************************************************************************
 �ṹ����: MMC_EMM_INFO_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��:
*****************************************************************************/
typedef struct
{
    VOS_UINT32                            bitOpLocTimeZone           :1; /* 1: VALID; 0: INVALID*/
    VOS_UINT32                            bitOpUniTimeLocTimeZone    :1; /* 1: VALID; 0: INVALID*/
    VOS_UINT32                            bitOpDaylightTime          :1; /* 1: VALID; 0: INVALID*/
    VOS_UINT32                            bitOpLongName              :1;
    VOS_UINT32                            bitOpShortName             :1;
    VOS_UINT32                            bitReserved                :27;

    VOS_INT8                              cLocTimeZone;
    MMC_EMM_INFO_UT_LTZ_STRU              stTimeZoneAndTime;
    MMC_EMM_INFO_DST_UINT8                enDaylightSavingTime;
    VOS_UINT8                             aucOperatorNameLong[MMC_LMM_MAX_OPER_LONG_NAME_LEN];
    VOS_UINT8                             aucOperatorNameShort[MMC_LMM_MAX_OPER_SHORT_NAME_LEN];

    VOS_UINT8                             aucRsv[2];
} MMC_EMM_INFO_STRU;

/*****************************************************************************
 �ṹ����: LMM_MMC_EMM_INFO_IND_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��:
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    /* LTE EMM Information���ݽṹ */
    MMC_EMM_INFO_STRU                   stLteEmmInfo;

} LMM_MMC_EMM_INFO_IND_STRU;

/*****************************************************************************
 �ṹ��    : MMC_LMM_ACTION_RESULT_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MMC_LMM_ACTION_RESULT_REQ_STRU�����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    VOS_UINT32                          bitOpReqDomain          : 1;
    VOS_UINT32                          bitOpRstDomain          : 1;
    VOS_UINT32                          bitOpMtDetachType       : 1;
    VOS_UINT32                          bitOpLocalDetachType    : 1;
    VOS_UINT32                          bitOpMoDetachType       : 1;
    VOS_UINT32                          bitOpCnCause            : 1;
    VOS_UINT32                          bitOpGprsUpdateStatus   : 1;
    VOS_UINT32                          bitOpRaiChangFlg        : 1;
    VOS_UINT32                          bitOpAtmpCnt            : 1;
    VOS_UINT32                          bitOpCsUpdateStatus     : 1;
    VOS_UINT32                          bitOpLaiChangFlg        : 1;
    VOS_UINT32                          bitSpare                : 21;


    /* ��������*/
    MMC_LMM_ACTION_TYPE_ENUM_UINT32     enActionType;

    /* CN_ACCEPT, CN_REJECT��������������Ӧ�Ľ�� */
    MMC_LMM_RSLT_TYPE_ENUM_UINT32       ulActRst;


    /* ����ҵ��ʱ������:��ATTACH, RAU, DETACHʱ��Ч */
    MMC_LMM_DOMAIN_ENUM_UINT32          ulReqDomain;

    /* ��������ͣ���ATTACH, TAU, DETACHʱ��Ч��������Ӧ�Ľ�� */
    MMC_LMM_DOMAIN_ENUM_UINT32          ulRstDomain;

    /*  �� MT DETACHʱ��Ч */
    MMC_LMM_MT_DETACH_TYPE_ENUM_UINT32  ulMtDetachType;


    /* local detach���ͣ�������detachʱ��Ч */
    MMC_LMM_GU_LOCAL_DETACH_TYPE_ENUM_UINT32   ulLocalDetachType;

    /* UE����detach ����*/
    MMC_LMM_MO_DETACH_TYPE_ENUM_UINT32  ulMoDetachType;


    /* �����·���ԭ�� */
    NAS_LMM_CN_CAUSE_ENUM_UINT8         ucCnCause;

    /* GPRS update status */
    MMC_LMM_GPRS_UPDATE_STATUS_ENUM_UINT8 ucGprsUpdateStatus;

    /* RAI �Ƿ�ı� */
    VOS_UINT8                           ucRaiChangFlg;

    /* MM update status */
    MMC_LMM_CS_UPDATE_STATUS_ENUM_UINT8    ucCsUpdateStatus;

    /* LAI �Ƿ�ı� */
    VOS_UINT8                           ucLaiChangFlg;

    VOS_UINT8                           aucRsv[3];

    /* ATTACH��RAUʧ�ܳ��Դ��� */
    VOS_UINT32                          ulAttemptCount;

} MMC_LMM_ACTION_RESULT_REQ_STRU;


/*****************************************************************************
 �ṹ��    : LMM_MMC_ERR_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LMM_MMC_ERR_IND_STRU�����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    VOS_UINT8                           aucRsv[4];

} LMM_MMC_ERR_IND_STRU;



/*****************************************************************************
 �ṹ��    : MMC_LMM_REL_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MMC_LMM_REL_REQ_STRU�����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    VOS_UINT8                           aucRsv[4];
}MMC_LMM_REL_REQ_STRU;


/*****************************************************************************
 �ṹ��    : LMM_MMC_SERVICE_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LMM_MMC_SERVICE_IND_STRU�����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    VOS_UINT8                           aucRsv[4];
} LMM_MMC_EPS_SERVICE_IND_STRU;

/*****************************************************************************
 �ṹ����: LMM_MMC_SUSPEND_IND_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��:LMM->MMC
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    MMC_LMM_SYS_CHNG_DIR_ENUM_UINT32    ulSysChngDir;                           /* ��ϵͳ���� */
    MMC_LMM_SYS_CHNG_TYPE_ENUM_UINT32   ulSysChngType;                          /* ��ϵͳ������� */

} LMM_MMC_SUSPEND_IND_STRU;

/*****************************************************************************
 �ṹ����: MMC_LMM_DEACT_REQ_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��:
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;
} MMC_LMM_SUSPEND_REQ_STRU;

/*****************************************************************************
 �ṹ����: MMC_LMM_RESUME_NOTIFY_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��:
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;
} MMC_LMM_RESUME_NOTIFY_STRU;

/*****************************************************************************
 �ṹ����: MMC_LMM_SUSPEND_RSP_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��:
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    /* ִ�н��*/
    MMC_LMM_RESULT_ID_ENUM_UINT32          ulRst;

} MMC_LMM_SUSPEND_RSP_STRU;


/*****************************************************************************
 �ṹ����: LMM_MMC_SUSPEND_CNF_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��:
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;               /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    /* ִ�н��*/
    MMC_LMM_RESULT_ID_ENUM_UINT32          ulRst;

} LMM_MMC_SUSPEND_CNF_STRU;


/*****************************************************************************
 �ṹ����: LMM_MMC_RESUME_IND_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��:
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    VOS_UINT8                           aucRsv[4];
} LMM_MMC_RESUME_IND_STRU;


/*****************************************************************************
 �ṹ����: LMM_MMC_STATUS_IND_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��:
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    VOS_UINT32                          bitOpConnState  : 1;
    VOS_UINT32                          bitSpare        : 31;

    /* ״̬��������� */
    MMC_LMM_STATUS_TYPE_ENUM_UINT32     ulStatusType;
    MMC_LMM_CONN_STATE_ENUM_UINT32      ulConnState;

} LMM_MMC_STATUS_IND_STRU;



/*****************************************************************************
 �ṹ����: MMC_LMM_SYS_CFG_REQ_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��:
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    /* ��Ȼ��AT�����Ȼͬʱ����RAT��BAND����˴���bitop��Ȼͬʱ��1�� */
    VOS_UINT32                          bitOpRat:1;
    VOS_UINT32                          bitOpBand:1;
    VOS_UINT32                          bitSpare:30;

    NAS_RRC_USER_SET_FREQ_BAND_STRU     stBand;                                 /* Ƶ�� */
    RRMM_RAT_PRIO_ENUM_UINT8            aucRatPrioList[RRMM_RAT_TYPE_BUTT];     /* ��ģ�����ȼ� */

    MMC_LMM_UTRAN_MODE_ENUM_UINT8       enUtranMode;                            /* ��ǰUTRAN�Ĺ���ģʽ:0---FDD 1---TDD */

    /*Modify by sunbing 49683 for CL multimode 2014-01-09 begin*/
    VOS_UINT8                           aucReserved[2];                         /* �ֽڶ��� */
    /*Modify by sunbing 49683 for CL multimode 2014-01-09 begin*/
} MMC_LMM_SYS_CFG_REQ_STRU;



/*****************************************************************************
 �ṹ��    :  MMC_LMM_SYS_CFG_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    MMC_LMM_RESULT_ID_ENUM_UINT32          ulRst;
}LMM_MMC_SYS_CFG_CNF_STRU;


/*****************************************************************************
 �ṹ����: MMC_LMM_USIM_STATUS_REQ_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��:
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    MMC_LMM_USIM_STATUS_ENUM_UINT32     ulUsimState;

} MMC_LMM_USIM_STATUS_REQ_STRU;


/*****************************************************************************
 �ṹ����: LMM_MMC_USIM_STATUS_CNF_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��:
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    VOS_UINT8                           aucRsv[4];

} LMM_MMC_USIM_STATUS_CNF_STRU;

/*****************************************************************************
 �ṹ����: LMM_MMC_TIN_TYPE_IND_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��:
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;
    MMC_LMM_TIN_TYPE_ENUM_UINT32        ulTinType;
} LMM_MMC_TIN_TYPE_IND_STRU;
/* ע��/����״̬�ϱ�����MMC��ɾ��ע��/����״̬��ش��� */
/*****************************************************************************
 �ṹ����: MMC_LMM_USER_PLMN_END_NOTIFY_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��:  ע��״̬�ϱ���Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    VOS_UINT8                           aucRsv[4];
} MMC_LMM_USER_PLMN_END_NOTIFY_STRU;
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;
    VOS_UINT32                          bitOpT3412  :1;
    VOS_UINT32                          bitOpT3423  :1;

    VOS_UINT32                          bitOpT3402  :1;
    VOS_UINT32                          bitOpRsv    :29;

    LMM_MMC_TIMER_STATE_ENUM_UINT32     enT3412State;
    LMM_MMC_TIMER_STATE_ENUM_UINT32     enT3423State;

    LMM_MMC_TIMER_STATE_ENUM_UINT32     enT3402State;
}LMM_MMC_TIMER_STATE_NOTIFY_STRU;


/*****************************************************************************
 �ṹ����: MMC_LMM_UE_OOC_STATUS_NOTIFY_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��:  MMCͨ������Ϣ֪ͨLMM���������������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;
}MMC_LMM_UE_OOC_STATUS_NOTIFY_STRU;

/*****************************************************************************
 �ṹ����: NAS_GUMM_INFO_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��:
*****************************************************************************/
typedef struct
{
    union
    {
        NAS_GUMM_PTMSI_STRU             stPtmsi;
        NAS_GUMM_PTMSI_SIGNATURE_STRU   stPtmsiSignature;
        NAS_GUMM_UMTS_CONTEXT_STRU      stSecuContext;
        MMC_LMM_LAI_STRU                stLai;
        MMC_LMM_RAI_STRU                stRAI;
        MMC_LMM_TMSI_STATUS_TYPE_ENUM_UINT32             ulTmsiStatus;
    }u;

} NAS_GUMM_INFO_STRU;


/****************************************************************************
 �ṹ����: NAS_LMM_INFO_STRU
 Э����:
 ASN.1���� :
 �ṹ˵��:
 *****************************************************************************/
typedef struct
{
    union
    {
        NAS_LMM_GUTI_STRU               stGuti;
        MMC_LMM_PLMN_ID_STRU            stPlmn;
        NAS_LMM_TAI_LIST_STRU           stForbRoamTaiList;
        NAS_LMM_TAI_LIST_STRU           stForbRposTaiList;
        MMC_LMM_PLMN_LIST_STRU          stCsDomainUnAvailPlmnList;
    }u;

} NAS_LMM_INFO_STRU;




/*****************************************************************************
 �ṹ����: MMC_LMM_PUB_INFO_STRU
 ????:
 ASN.1??:
 ????:
*****************************************************************************/
typedef struct
{
    union
    {
        MMC_LMM_TIN_TYPE_ENUM_UINT32    ulTinType;
        MMC_LMM_EPLMN_STRU              stEplmnList;
        MMC_LMM_PLMN_ID_STRU            stHplmn;
        MMC_LMM_PLMN_LIST_STRU          stForbiddenPlmnList;
        MMC_LMM_PLMN_LIST_STRU          stForbiddenPlmnListForGPRS;
        MMC_LMM_PLMN_LIST_STRU          stEHplmnList;
    }u;

} MMC_LMM_PUB_INFO_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32                ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                                ulOpId;
    MMC_LMM_DISABLE_LTE_REASON_ENUM_UINT32    enDisableLteReason;
} MMC_LMM_DISABLE_LTE_NOTIFY_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32                ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                                ulOpId;
} MMC_LMM_ENABLE_LTE_NOTIFY_STRU;

/*****************************************************************************
 �ṹ����: MMC_LMM_CS_CONN_STATUS_NOTIFY_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��:ID_MM_LMM_CONN_STATUS_NOTIFY_STRU
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;
    VOS_UINT8                           ucCsRrConnStatusFlg;                    /* CS��RR�����Ƿ����,VOS_FALSE:������,VOS_TRUE:���� */
    VOS_UINT8                           ucCsEmergencyConnStatusFlg;             /* ����������·�Ƿ����,VOS_TRUE:���ڣ�VOS_FALSE������ */
    VOS_UINT8                           aucReserved[2];
} MMC_LMM_CS_CONN_STATUS_NOTIFY_STRU;


/*****************************************************************************
 �ṹ��    : MMC_LMM_SUSPEND_REL_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MMC_LMM_SUSPEND_REL_REQ_STRU �����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    VOS_UINT8                           aucRsv[4];
} MMC_LMM_SUSPEND_REL_REQ_STRU;


typedef struct
{
    VOS_MSG_HEADER                                         /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;           /*_H2ASN_Skip*/
    MMC_LMM_UTRAN_MODE_ENUM_UINT8       enUtranMode;       /* UTRAN�Ĺ���ģʽ*/
    VOS_UINT8                           aucRsv[3];
} MMC_LMM_UTRAN_MODE_REQ_STRU;
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
}LMM_MMC_UTRAN_MODE_CNF_STRU;


typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    VOS_UINT8                           aucRsv[4];
} LMM_MMC_SUSPEND_REL_CNF_STRU;



/*****************************************************************************
 ö����    : LMM_MMC_RAT_CHANGE_CAUSE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  :
*****************************************************************************/
enum LMM_MMC_SUSPEND_INFO_CHANGE_TYPE_ENUM
{
    LMM_MMC_SUSPEND_RAT_INFO_CHANGE   = 0,     /* CSFB���ض��������RAT�����ı�*/
    LMM_MMC_SUSPEND_INFO_CHANGE_BUTT
};
typedef VOS_UINT32  LMM_MMC_SUSPEND_INFO_CHANGE_TYPE_ENUM_UINT32;

/*****************************************************************************
 ö����    : LMM_MMC_RAT_CHANGE_CAUSE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  :
*****************************************************************************/
enum LMM_MMC_RAT_CHANGE_TYPE_ENUM
{
    LMM_MMC_RAT_CHANGE_G2W   = 0,
    LMM_MMC_RAT_CHANGE_W2G   = 1,
    LMM_MMC_RAT_CHANGE_TYPE_BUTT
};
typedef VOS_UINT32  LMM_MMC_RAT_CHANGE_TYPE_ENUM_UINT32;


/*****************************************************************************
 �ṹ����   : LMM_MMC_RAT_CHANGE_IND_STRU
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : LMM_MMC_RAT_CHANGE_IND_STRU����֪ͨLMM�ײ�Ľ��뼼�������仯
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;


    LMM_MMC_SUSPEND_INFO_CHANGE_TYPE_ENUM_UINT32  ulInfoType;/*��Ϣ������� : CSFB_REDIR_RAT_CHANGE;*/
    LMM_MMC_RAT_CHANGE_TYPE_ENUM_UINT32 ulRatChangeType;/* ö�٣�����ֵ��U2G, G2U*/
    VOS_UINT8                           aucRsv[4];      /* Ԥ�� */
}LMM_MMC_SUSPEND_INFO_CHANGE_NOTIFY_STRU;
typedef struct
{
    VOS_MSG_HEADER                                                /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32                ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                                bitOpRac   :1;
    VOS_UINT32                                bitSpare   :31;

    MMC_LMM_PLMN_ID_STRU                      stPlmnId;
    VOS_UINT32                                ulCellId;
    VOS_UINT16                                usLac;
    VOS_UINT8                                 ucRac;
    VOS_UINT8                                 ucRsv1;
} MMC_LMM_WCDMA_SYS_INFO_IND_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32                ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                                bitOpRac   :1;
    VOS_UINT32                                bitSpare   :31;

    MMC_LMM_PLMN_ID_STRU                      stPlmnId;
    VOS_UINT32                                ulCellId;
    VOS_UINT16                                usLac;
    VOS_UINT8                                 ucRac;
    VOS_UINT8                                 ucRsv1;
} MMC_LMM_GSM_SYS_INFO_IND_STRU;

/* lihong00150010 ims begin */
/*****************************************************************************
 �ṹ��    : LMM_MMC_EMC_PDP_STATUS_NOTIFY_STRU
 �ṹ˵��  : ֪ͨMMC�������ص�״̬
  1.��    ��   : 2013��12��03��
    ��    ��   : lihong00150010
    �޸�����   : �½�
 *****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32                ulMsgId;            /*_H2ASN_Skip*/

    VOS_UINT8                                 ucIsEmcPdpActive;   /* VOS_TRUE:��ʾ�������ؼ��VOS_FALSE:��ʾ��������δ���� */
    VOS_UINT8                                 aucRsv[3];
} LMM_MMC_EMC_PDP_STATUS_NOTIFY_STRU;
/* lihong00150010 ims end */

/*****************************************************************************
 �ṹ����: MMC_LMM_LTE_SYS_INFO_IND_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��:
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    /* ��ǰС����ϵͳ��Ϣ: PLMN_LIST, TAC, CELLID, С��״̬�� */
    MMC_LMM_SYS_INFO_STRU               stLteSysInfo;

} MMC_LMM_LTE_SYS_INFO_IND_STRU;

/*****************************************************************************
 �ṹ����: MMC_LMM_OTHER_MODEM_INFO_NOTIFY_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��:
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    MMC_LMM_MSG_ID_ENUM_UINT32  ulMsgId;
    VOS_UINT32                  bitOpCurrCampPlmnId:1;
    VOS_UINT32                  bitSpare:31;
    MMC_LMM_PLMN_ID_STRU        stCurrCampPlmnId;
}MMC_LMM_OTHER_MODEM_INFO_NOTIFY_STRU;


typedef struct
{
    MSG_HEADER_STRU                                 stMsgHeader;                /*_H2ASN_Skip*/
    MMC_LMM_SESSION_TYPE_ENUM_UINT8                 enSessionType;
    VOS_UINT8                                       aucReserved[3];
}MMC_LMM_BEGIN_SESSION_NOTIFY_STRU;
typedef struct
{
    MSG_HEADER_STRU                                 stMsgHeader;                /*_H2ASN_Skip*/
    MMC_LMM_SESSION_TYPE_ENUM_UINT8                 enSessionType;
    VOS_UINT8                                       aucReserved[3];
}MMC_LMM_END_SESSION_NOTIFY_STRU;


/*****************************************************************************
 �ṹ����: MMC_LMM_IMS_VOICE_CAP_NOTIFY_REQ_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��:
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;

    MMC_LMM_IMS_VOICE_CAP_ENUM_UINT8    enImsVoiceCap;
    VOS_UINT8                           aucRsv[3];
} MMC_LMM_IMS_VOICE_CAP_CHANGE_NOTIFY_STRU;


/*****************************************************************************
 �ṹ��    : LMM_MMC_EMERGENCY_NUM_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCategory;
    VOS_UINT8                           ucEmcNumLen;    /*���������볤�ȣ���aucEmcNum����Ч����*/
    VOS_UINT8                           aucEmcNum[LMM_MMC_EMERGENCY_NUM_MAX_LEN];
} LMM_MMC_EMERGENCY_NUM_STRU;

/*****************************************************************************
 �ṹ��    : LMM_MMC_INFO_CHANGE_NOTIFY_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32              ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                              ulOpId;
    /*VOS_UINT32                              bitOpEmcNumList : 1;
    VOS_UINT32                              bitOpImsVoPS    : 1;
    VOS_UINT32                              bitOpEmcBS      : 1;
    VOS_UINT32                              bitOpLteCsCap   : 1;
    VOS_UINT32                              bitSpare        : 29;*/

    VOS_UINT8                               ucEmergencyNumAmount;
    VOS_UINT8                               aucReserved[3];
    LMM_MMC_EMERGENCY_NUM_STRU              astEmergencyNumList[LMM_MMC_EMERGENCY_NUM_LIST_MAX_RECORDS];

    LMM_MMC_NW_IMS_VOICE_ENUM_UINT32        enNwImsVoPS;
    LMM_MMC_NW_EMC_BS_ENUM_UINT32           enNwEmcBS;
    LMM_MMC_LTE_CS_CAPBILITY_ENUM_UINT32    enLteCsCap ;
} LMM_MMC_INFO_CHANGE_NOTIFY_STRU;

/*****************************************************************************
 �ṹ��    : LMM_MMC_SIM_AUTH_FAIL_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����Ȩʧ��LMM֪ͨMMC�ӿ� 20141103add
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    MMC_LMM_MSG_ID_ENUM_UINT32              ulMsgId;

    LMM_MMC_SIM_AUTH_FAIL_ENUM_UINT16       enSimAuthFailValue;  /*����Ȩʧ�ܷ��ص�ʧ��ԭ��ֵ*/
    LMM_MMC_SRV_DOMAIN_ENUM_UINT8           enSrvDomain;         /*������*/
    VOS_UINT8                               ucRsv;
} LMM_MMC_SIM_AUTH_FAIL_IND_STRU;

/*****************************************************************************
 �ṹ��    : LMM_MMC_SEARCHED_PLMN_INFO_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32              ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                              ulTaiNum;           /*LRRC�ϱ�TAI����*/
    NAS_LMM_TAI_STRU                        stTaiList[LMM_MMC_MAX_SEARCHED_TAI_NUM];    /*LRRC�ϱ�TAI�б�*/
} LMM_MMC_SEARCHED_PLMN_INFO_IND_STRU;

/*****************************************************************************
 �ṹ��    : MMC_LMM_CELL_SIGN_REPORT_NOTIFY_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ID_MMC_LMM_CELL_SIGN_REPORT_NOTIFY��Ӧ�Ľṹ��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    MMC_LMM_MSG_ID_ENUM_UINT32              ulMsgId;
    VOS_UINT8                               ucMinRptTimerInterval;              /* ʱ������Ϊ0ʱ:RSSI�仯�ﵽ����ֵʱ�����ϱ������޵�ȡֵ���� */
    VOS_UINT8                               ucSignThreshold;                    /* ����ֵ��Ϊ0ʱ:���֮ǰû�и������֪ͨ����Чֵ(1-5dB)���������NV����ֵ��
                                                                                   ���֮ǰ�������֪ͨ����Чֵ���������Ȼ���ϴε���Чֵ */
    VOS_UINT8                               aucReserve[2];
} MMC_LMM_CELL_SIGN_REPORT_NOTIFY_STRU;

/*****************************************************************************
 �ṹ��    : LMM_MMC_CQI_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LTE�µ��ŵ�����,�������ֱַ�����Ӵ�CQI�Ϳ��CQI
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usRI;                               /* RIֵ,1ʱ��ausCQI[0]��Ч��2ʱausCQI[0]��ausCQI[1]����Ч */
    VOS_UINT8                               aucRes[2];
    VOS_UINT16                              ausCQI[2];                          /* channel quality indicator */
} LMM_MMC_CQI_INFO_STRU;

/*****************************************************************************
 �ṹ��    : LMM_MMC_CELL_SIGN_REPORT_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ID_LMM_MMC_CELL_SIGN_REPORT_IND��Ӧ�Ľṹ�壬LTE�µ�Rssi��Rsrp��Rsrq,CQI
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    MMC_LMM_MSG_ID_ENUM_UINT32              ulMsgId;
    VOS_INT16                               sRssi;                              /* received signal strength indicator */
    VOS_INT16                               sRsd;                               /* ����ֶ�*/
    VOS_INT16                               sRsrp;                              /* reference signal receive power   ��Χ��(-141,-44), 99Ϊ��Ч */
    VOS_INT16                               sRsrq;                              /* reference signal receive quality ��Χ��(-40, -6) , 99Ϊ��Ч */
    VOS_INT32                               lSinr;                              /* signal to interference plus noise ratio */
    LMM_MMC_CQI_INFO_STRU                   stCQI;                              /* channel quality indicator */
} LMM_MMC_CELL_SIGN_REPORT_IND_STRU;

/*****************************************************************************
 �ṹ��    : LMM_MMC_T3402_LEN_NOTIFY_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : AT&T��������������Ϣ��֪ͨMMC3402��ʱ��ʱ��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    MMC_LMM_MSG_ID_ENUM_UINT32              ulMsgId;

    VOS_UINT32                              ulOpId;
    VOS_UINT32                              ulT3402Len;   /* 3402��ʱ��ʱ������λ:���� */
} LMM_MMC_T3402_LEN_NOTIFY_STRU;
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32              ulMsgId;                            /*_H2ASN_Skip*/
    MMC_LMM_VOICE_DOMAIN_ENUM_UINT32        enVoiceDomain;                      /* ������ѡ�� */
} MMC_LMM_VOICE_DOMAIN_CHANGE_IND_STRU;

/*****************************************************************************
 ��������: LMM_MMC_EUTRAN_NOT_ALLOW_NOTIFY_STRU
 Э����:
 ASN.1 ����:
 ����˵��: 4Gδ������������������Ϣ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    MMC_LMM_MSG_ID_ENUM_UINT32  ulMsgId;

    VOS_UINT32                  ulOpId;
    VOS_UINT32                  ulTimerLen;/*LTE�����õ�ʱ������λ��*/
    VOS_UINT8                   ucNetWorkTriggerFlag; /*0 ����û�д�extCause��1�������extCause*/
    VOS_UINT8                   ucPlmnNum;  /*Я��PLMN����*/
    VOS_UINT8                   aucReserved[2];
    MMC_LMM_PLMN_ID_STRU        astPlmnIdList[MMC_LMM_MAX_EUTRAN_NOT_ALLOW_PLMN_NUM];
}LMM_MMC_EUTRAN_NOT_ALLOW_NOTIFY_STRU;

/*****************************************************************************
 �ṹ��    : MMC_LMM_BG_SEARCH_HRPD_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ID_MMC_LMM_BG_SEARCH_HRPD_REQ��Ӧ�Ľṹ�壬LTE�±�������HRPD
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32              ulMsgId;        /*_H2ASN_Skip*/

    VOS_UINT32                              ulOpId;
    VOS_UINT8                               aucRsv[4];
}MMC_LMM_BG_SEARCH_HRPD_REQ_STRU;

/*****************************************************************************
 �ṹ��    : LMM_MMC_HRPD_SUBNET_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : HRPD��SubnetID
*****************************************************************************/
typedef struct
{
    VOS_UINT8                               aucSubnetId[LMM_MMC_HRPD_SUBNET_MAX_LEN];
    VOS_UINT16                              usBandClass;
    VOS_UINT16                              usFreq;
}LMM_MMC_HRPD_SYS_STRU;

/*****************************************************************************
 �ṹ��    : MMC_LMM_BG_SEARCH_HRPD_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ID_LMM_MMC_BG_SEARCH_HRPD_CNF��Ӧ�Ľṹ�壬LTE�±�������HRPD�Ļظ���Ϣ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                      /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32              ulMsgId;    /*_H2ASN_Skip*/
    VOS_UINT32                              ulOpId;

    MMC_LMM_BG_SRCH_RLT_ENUM_UINT32         enRlst;
    VOS_UINT8                               ucHrpdSysNum;
    VOS_UINT8                               aucRsv[3];
    LMM_MMC_HRPD_SYS_STRU                   astHrpdSysList[LMM_MMC_BG_HRPD_MAX_SYS_NUM];
}LMM_MMC_BG_SEARCH_HRPD_CNF_STRU;

/*****************************************************************************
 �ṹ��    : MMC_LMM_STOP_BG_SEARCH_HRPD_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ID_MMC_LMM_STOP_BG_SEARCH_HRPD_REQ��Ӧ�Ľṹ��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                      /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32              ulMsgId;    /*_H2ASN_Skip*/

    VOS_UINT32                              ulOpId;
    VOS_UINT8                               aucRsv[4];
}MMC_LMM_STOP_BG_SEARCH_HRPD_REQ_STRU;

/*****************************************************************************
 �ṹ��    : LMM_MMC_STOP_BG_SEARCH_HRPD_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ID_LMM_MMC_STOP_BG_SEARCH_HRPD_CNF��Ӧ�Ľṹ��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                      /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32              ulMsgId;    /*_H2ASN_Skip*/

    VOS_UINT32                              ulOpId;
    VOS_UINT8                               aucRsv[4];
}LMM_MMC_STOP_BG_SEARCH_HRPD_CNF_STRU;

/*****************************************************************************
 ��������: Nas_GetGuInfo
 Э����:
 ASN.1 ����:
 ����˵��:
*****************************************************************************/
extern MMC_LMM_RESULT_ID_ENUM_UINT32  Nas_GetGuInfo
(
    NAS_GUMM_INFO_TYPE_ENUM_UINT32  ulInfoType,
    NAS_GUMM_INFO_STRU *            pstGuInfo
);



/*****************************************************************************
 ��������: Nas_GetLteInfo
 Э����:
 ASN.1 ����:
 ����˵��:
*****************************************************************************/

extern MMC_LMM_RESULT_ID_ENUM_UINT32  Nas_GetLteInfo
(
    NAS_LMM_INFO_TYPE_ENUM_UINT32  ulInfoType,
    NAS_LMM_INFO_STRU             *pstLmmInfo
);

/*****************************************************************************
 ��������: Nas_GetPubInfo
 Э����:
 ASN.1 ����:
 ����˵��:
*****************************************************************************/
extern MMC_LMM_RESULT_ID_ENUM_UINT32 Nas_GetPubInfo
(
    MMC_LMM_INFO_TYPE_ENUM_UINT32    ulInfoType,
    MMC_LMM_PUB_INFO_STRU           *pPubInfo
);


/*****************************************************************************
 ��������: Nas_PlmnIdIsForbid
 ����˵��:
*****************************************************************************/
MMC_LMM_PLMN_CTRL_ENUM_UINT32  Nas_PlmnIdIsForbid
(
    MMC_LMM_PLMN_ID_STRU     *pstPlmn
);


/*****************************************************************************
 ��������: NAS_MM_PidInit
 ����˵��: LMM PID��ʼ������������MM FID��ʼ��ʱ����
*****************************************************************************/
VOS_UINT32  NAS_MM_PidInit (    enum VOS_INIT_PHASE_DEFINE ip );

/*****************************************************************************
 ��������: NAS_MM_PidMsgEntry
 ����˵��: LMM��Ϣ��ں���������MM FID��ʼ��ʱ����
*****************************************************************************/
extern void        NAS_MM_PidMsgEntry( MsgBlock *pMsg);

/*****************************************************************************
 ��������: LTE_MsgHook
 ����˵��: LTE��Ϣ��ȡ����
*****************************************************************************/
extern VOS_UINT32 LTE_MsgHook( VOS_VOID *pMsg );

/*****************************************************************************
 ��������: Nas_GetEutraUeCap
 Э����:
 ASN.1 ����:
 ����˵��:
*****************************************************************************/
extern MMC_LMM_RESULT_ID_ENUM_UINT32  Nas_GetEutraUeCap
(
    MMC_LMM_PLMN_ID_STRU stPlmnId,
    VOS_UINT16 *pusEUeCapDataLen,
    VOS_UINT8 *pucEUeCapData
);

typedef struct
{
    MMC_LMM_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_MsgChoice_Export MMC_LMM_MSG_ID_ENUM_UINT32*/
    VOS_UINT8                           aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          MMC_LMM_MSG_ID_ENUM_UINT32
    ****************************************************************************/
}MMC_LMM_INTERFACE_MSG_DATA;
/*_H2ASN_Length UINT32*/


typedef struct
{
    VOS_MSG_HEADER
    MMC_LMM_INTERFACE_MSG_DATA           stMsgData;
} MmcLmmInterface_MSG;







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

#endif /* end of MmcLmmInterface.h */

















